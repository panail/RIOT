/*
 * Copyright (C) 2016 Patrick Naili <stpanail@stud.h-da.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       firmware update
 *
 * @author      Patrick Naili <stpanail@stud.h-da.de>
 * @}
 */

#include "firmware_update.h"

#include "periph/pm.h"
#include "net/sock/udp.h"
#include "firmware/simple.h"
#include "net/sock/util.h"
#include "log.h"
#include "net/nanocoap.h"
#include "net/nanocoap_sock.h"
#include "liblwm2m.h"



static char _firmware_uri[URI_MAX_LENGTH];


static ssize_t get_block(sock_udp_ep_t *remote, char* path, unsigned num, sock_udp_ep_t *local,firmware_simple_update_t *_state);
static int _download_firmware(void);

static int _download_firmware(void)
{
	firmware_simple_update_t _state;
	char path[128];
    char hostport[SOCK_HOSTPORT_MAXLEN];
    sock_udp_ep_t remote;
    printf("%s\n",_firmware_uri);
    if (sock_urlsplit(_firmware_uri, hostport, path) < 0) {
        LOG_ERROR("ota: Unable to parse url1\n");
        return -1;
    }
    if (sock_udp_str2ep(&remote, hostport) < 0) {
        LOG_ERROR("ota: Unable to parse url\n");
        return -1;
    }
	int more = 1;
	unsigned blknum = 0;
	sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
	local.port = 12346;
	while (more) {
		more = get_block(&remote,path, blknum, &local,&_state);
		if(more < 0) {
			LOG_ERROR("ota: error fetching block: %d\n", more);
			return more;
		}
		if (more == 0) {
			break;
		}
		blknum++;
	}
    if (firmware_simple_finish(&_state) != 0) {
        return -1;
    }
    else{
    	pm_reboot();
    	return 0;
    }
}

static ssize_t get_block(sock_udp_ep_t *remote, char* path, unsigned num, sock_udp_ep_t *local,firmware_simple_update_t *_state){
    uint8_t buf[128];
    coap_pkt_t pkt;
    uint8_t *pktpos = buf;
    pkt.hdr = (coap_hdr_t*)buf;
    pktpos += coap_build_hdr(pkt.hdr, COAP_REQ, NULL, 0, COAP_METHOD_GET, num);
    pktpos += coap_opt_put_uri_path(pktpos, 0, path);
    pktpos += coap_put_option_block2(pktpos, COAP_OPT_URI_PATH, num, 2, 0);
    pkt.payload = pktpos;
    pkt.payload_len = 0;

    int res = nanocoap_request(&pkt, local, remote, sizeof(buf) );
    if (res > 0){
    	coap_block1_t block2;
    	coap_get_block2(&pkt, &block2);

    	if (block2.offset == 0) {
    		firmware_simple_init(_state);
    	}

        if (_state->state == FIRMWARE_UPDATE_IDLE) {
            res = -1;
        }
        else {
			if (block2.offset == _state->writer.offset) {
				printf("offset %u\n",block2.offset);
				res = firmware_simple_putbytes(_state, pkt.payload,pkt.payload_len);
			} else {
				LOG_INFO(
						"get_block(): ignoring already received block\n");
				res = 0;
			}
		}

        if (res) {
            _state->state = FIRMWARE_UPDATE_IDLE;
            LOG_INFO("coap_ota_handler(): unexpected packet\n");
            return -1;
        }
        return block2.more;

    }
    return -1;

}




void firmware_update_download(char* uri){
	strcpy(_firmware_uri, uri);
	_download_firmware();

}

