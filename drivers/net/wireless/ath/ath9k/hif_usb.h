<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
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

#अगर_अघोषित HTC_USB_H
#घोषणा HTC_USB_H

/* old firmware images */
#घोषणा FIRMWARE_AR7010_1_1     "htc_7010.fw"
#घोषणा FIRMWARE_AR9271         "htc_9271.fw"

/* supported Major FW version */
#घोषणा MAJOR_VERSION_REQ 1
#घोषणा MINOR_VERSION_REQ 3
/* minimal and maximal supported Minor FW version. */
#घोषणा FIRMWARE_MINOR_IDX_MAX  4
#घोषणा FIRMWARE_MINOR_IDX_MIN  3
#घोषणा HTC_FW_PATH	"ath9k_htc"

#घोषणा HTC_9271_MODULE_FW  HTC_FW_PATH "/htc_9271-" \
			__stringअगरy(MAJOR_VERSION_REQ) \
			"." __stringअगरy(FIRMWARE_MINOR_IDX_MAX) ".0.fw"
#घोषणा HTC_7010_MODULE_FW  HTC_FW_PATH "/htc_7010-" \
			__stringअगरy(MAJOR_VERSION_REQ) \
			"." __stringअगरy(FIRMWARE_MINOR_IDX_MAX) ".0.fw"

बाह्य पूर्णांक htc_use_dev_fw;

#घोषणा IS_AR7010_DEVICE(_v) (((_v) == AR9280_USB) || ((_v) == AR9287_USB))

#घोषणा AR9271_FIRMWARE       0x501000
#घोषणा AR9271_FIRMWARE_TEXT  0x903000
#घोषणा AR7010_FIRMWARE_TEXT  0x906000

#घोषणा FIRMWARE_DOWNLOAD       0x30
#घोषणा FIRMWARE_DOWNLOAD_COMP  0x31

#घोषणा ATH_USB_RX_STREAM_MODE_TAG 0x4e00
#घोषणा ATH_USB_TX_STREAM_MODE_TAG 0x697e

/* FIXME: Verअगरy these numbers (with Winकरोws) */
#घोषणा MAX_TX_URB_NUM  8
#घोषणा MAX_TX_BUF_NUM  256
#घोषणा MAX_TX_BUF_SIZE 32768
#घोषणा MAX_TX_AGGR_NUM 20

#घोषणा MAX_RX_URB_NUM  8
#घोषणा MAX_RX_BUF_SIZE 16384
#घोषणा MAX_PKT_NUM_IN_TRANSFER 10

#घोषणा MAX_REG_OUT_URB_NUM  1
#घोषणा MAX_REG_IN_URB_NUM   64

#घोषणा MAX_REG_IN_BUF_SIZE 64

/* USB Endpoपूर्णांक definition */
#घोषणा USB_WLAN_TX_PIPE  1
#घोषणा USB_WLAN_RX_PIPE  2
#घोषणा USB_REG_IN_PIPE   3
#घोषणा USB_REG_OUT_PIPE  4

#घोषणा USB_MSG_TIMEOUT 1000 /* (ms) */

#घोषणा HIF_USB_MAX_RXPIPES 2
#घोषणा HIF_USB_MAX_TXPIPES 4

काष्ठा tx_buf अणु
	u8 *buf;
	u16 len;
	u16 offset;
	काष्ठा urb *urb;
	काष्ठा sk_buff_head skb_queue;
	काष्ठा hअगर_device_usb *hअगर_dev;
	काष्ठा list_head list;
पूर्ण;

काष्ठा rx_buf अणु
	काष्ठा sk_buff *skb;
	काष्ठा hअगर_device_usb *hअगर_dev;
पूर्ण;

#घोषणा HIF_USB_TX_STOP  BIT(0)
#घोषणा HIF_USB_TX_FLUSH BIT(1)

काष्ठा hअगर_usb_tx अणु
	u8 flags;
	u8 tx_buf_cnt;
	u16 tx_skb_cnt;
	काष्ठा sk_buff_head tx_skb_queue;
	काष्ठा list_head tx_buf;
	काष्ठा list_head tx_pending;
	spinlock_t tx_lock;
पूर्ण;

काष्ठा cmd_buf अणु
	काष्ठा sk_buff *skb;
	काष्ठा hअगर_device_usb *hअगर_dev;
पूर्ण;

#घोषणा HIF_USB_START BIT(0)
#घोषणा HIF_USB_READY BIT(1)

काष्ठा hअगर_device_usb अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	स्थिर काष्ठा usb_device_id *usb_device_id;
	स्थिर व्योम *fw_data;
	माप_प्रकार fw_size;
	काष्ठा completion fw_करोne;
	काष्ठा htc_target *htc_handle;
	काष्ठा hअगर_usb_tx tx;
	काष्ठा usb_anchor regout_submitted;
	काष्ठा usb_anchor rx_submitted;
	काष्ठा usb_anchor reg_in_submitted;
	काष्ठा usb_anchor mgmt_submitted;
	काष्ठा sk_buff *reमुख्य_skb;
	अक्षर fw_name[32];
	पूर्णांक fw_minor_index;
	पूर्णांक rx_reमुख्य_len;
	पूर्णांक rx_pkt_len;
	पूर्णांक rx_transfer_len;
	पूर्णांक rx_pad_len;
	spinlock_t rx_lock;
	u8 flags; /* HIF_USB_* */
पूर्ण;

पूर्णांक ath9k_hअगर_usb_init(व्योम);
व्योम ath9k_hअगर_usb_निकास(व्योम);
व्योम ath9k_hअगर_usb_dealloc_urbs(काष्ठा hअगर_device_usb *hअगर_dev);

#पूर्ण_अगर /* HTC_USB_H */
