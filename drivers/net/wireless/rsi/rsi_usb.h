<शैली गुरु>
/*
 * @section LICENSE
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __RSI_USB_INTF__
#घोषणा __RSI_USB_INTF__

#समावेश <linux/usb.h>
#समावेश "rsi_main.h"
#समावेश "rsi_common.h"

#घोषणा RSI_USB_VENDOR_ID	0x1618
#घोषणा RSI_USB_PID_9113	0x9113
#घोषणा RSI_USB_PID_9116	0x9116

#घोषणा USB_INTERNAL_REG_1           0x25000
#घोषणा RSI_USB_READY_MAGIC_NUM      0xab
#घोषणा FW_STATUS_REG                0x41050012
#घोषणा RSI_TA_HOLD_REG              0x22000844
#घोषणा RSI_FW_WDT_DISABLE_REQ	     0x69

#घोषणा USB_VENDOR_REGISTER_READ     0x15
#घोषणा USB_VENDOR_REGISTER_WRITE    0x16
#घोषणा RSI_USB_TX_HEAD_ROOM         128

#घोषणा MAX_RX_URBS                  2
#घोषणा MAX_BULK_EP                  8
#घोषणा WLAN_EP                      1
#घोषणा BT_EP                        2

#घोषणा RSI_USB_BUF_SIZE	     4096
#घोषणा RSI_USB_CTRL_BUF_SIZE	     0x04

काष्ठा rx_usb_ctrl_block अणु
	u8 *data;
	काष्ठा urb *rx_urb;
	काष्ठा sk_buff *rx_skb;
	u8 ep_num;
पूर्ण;

काष्ठा rsi_91x_usbdev अणु
	व्योम *priv;
	काष्ठा rsi_thपढ़ो rx_thपढ़ो;
	u8 endpoपूर्णांक;
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *pfunction;
	काष्ठा rx_usb_ctrl_block rx_cb[MAX_RX_URBS];
	u8 *tx_buffer;
	__le16 bulkin_size[MAX_BULK_EP];
	u8 bulkin_endpoपूर्णांक_addr[MAX_BULK_EP];
	__le16 bulkout_size[MAX_BULK_EP];
	u8 bulkout_endpoपूर्णांक_addr[MAX_BULK_EP];
	u32 tx_blk_size;
	u8 ग_लिखो_fail;
	काष्ठा sk_buff_head rx_q;
पूर्ण;

अटल अंतरभूत पूर्णांक rsi_usb_check_queue_status(काष्ठा rsi_hw *adapter, u8 q_num)
अणु
	/* In USB, there isn't any need to check the queue status */
	वापस QUEUE_NOT_FULL;
पूर्ण

अटल अंतरभूत पूर्णांक rsi_usb_event_समयout(काष्ठा rsi_hw *adapter)
अणु
	वापस EVENT_WAIT_FOREVER;
पूर्ण

व्योम rsi_usb_rx_thपढ़ो(काष्ठा rsi_common *common);
#पूर्ण_अगर
