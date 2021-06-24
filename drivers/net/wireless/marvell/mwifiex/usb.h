<शैली गुरु>
/*
 * This file contains definitions क्रम mwअगरiex USB पूर्णांकerface driver.
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#अगर_अघोषित _MWIFIEX_USB_H
#घोषणा _MWIFIEX_USB_H

#समावेश <linux/completion.h>
#समावेश <linux/usb.h>

#घोषणा USB8XXX_VID		0x1286

#घोषणा USB8766_PID_1		0x2041
#घोषणा USB8766_PID_2		0x2042
#घोषणा USB8797_PID_1		0x2043
#घोषणा USB8797_PID_2		0x2044
#घोषणा USB8801_PID_1		0x2049
#घोषणा USB8801_PID_2		0x204a
#घोषणा USB8997_PID_1		0x2052
#घोषणा USB8997_PID_2		0x204e


#घोषणा USB8XXX_FW_DNLD		1
#घोषणा USB8XXX_FW_READY	2
#घोषणा USB8XXX_FW_MAX_RETRY	3

#घोषणा MWIFIEX_TX_DATA_PORT	2
#घोषणा MWIFIEX_TX_DATA_URB	6
#घोषणा MWIFIEX_RX_DATA_URB	6
#घोषणा MWIFIEX_USB_TIMEOUT	100

#घोषणा USB8766_DEFAULT_FW_NAME	"mrvl/usb8766_uapsta.bin"
#घोषणा USB8797_DEFAULT_FW_NAME	"mrvl/usb8797_uapsta.bin"
#घोषणा USB8801_DEFAULT_FW_NAME	"mrvl/usb8801_uapsta.bin"
#घोषणा USB8997_DEFAULT_FW_NAME	"mrvl/usbusb8997_combo_v4.bin"

#घोषणा FW_DNLD_TX_BUF_SIZE	620
#घोषणा FW_DNLD_RX_BUF_SIZE	2048
#घोषणा FW_HAS_LAST_BLOCK	0x00000004
#घोषणा FW_CMD_7		0x00000007

#घोषणा FW_DATA_XMIT_SIZE \
	(माप(काष्ठा fw_header) + dlen + माप(u32))

काष्ठा urb_context अणु
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा sk_buff *skb;
	काष्ठा urb *urb;
	u8 ep;
पूर्ण;

#घोषणा MWIFIEX_USB_TX_AGGR_TMO_MIN	1
#घोषणा MWIFIEX_USB_TX_AGGR_TMO_MAX	4

काष्ठा tx_aggr_पंचांगr_cnxt अणु
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा usb_tx_data_port *port;
	काष्ठा समयr_list hold_समयr;
	bool is_hold_समयr_set;
	u32 hold_पंचांगo_msecs;
पूर्ण;

काष्ठा usb_tx_aggr अणु
	काष्ठा sk_buff_head aggr_list;
	पूर्णांक aggr_len;
	पूर्णांक aggr_num;
	काष्ठा tx_aggr_पंचांगr_cnxt समयr_cnxt;
पूर्ण;

काष्ठा usb_tx_data_port अणु
	u8 tx_data_ep;
	u8 block_status;
	atomic_t tx_data_urb_pending;
	पूर्णांक tx_data_ix;
	काष्ठा urb_context tx_data_list[MWIFIEX_TX_DATA_URB];
	/* usb tx aggregation*/
	काष्ठा usb_tx_aggr tx_aggr;
	काष्ठा sk_buff *skb_aggr[MWIFIEX_TX_DATA_URB];
	/* lock क्रम protect tx aggregation data path*/
	spinlock_t tx_aggr_lock;
पूर्ण;

काष्ठा usb_card_rec अणु
	काष्ठा mwअगरiex_adapter *adapter;
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा completion fw_करोne;
	u8 rx_cmd_ep;
	काष्ठा urb_context rx_cmd;
	atomic_t rx_cmd_urb_pending;
	काष्ठा urb_context rx_data_list[MWIFIEX_RX_DATA_URB];
	u8 usb_boot_state;
	u8 rx_data_ep;
	atomic_t rx_data_urb_pending;
	u8 tx_cmd_ep;
	atomic_t tx_cmd_urb_pending;
	पूर्णांक bulk_out_maxpktsize;
	काष्ठा urb_context tx_cmd;
	u8 mc_resync_flag;
	काष्ठा usb_tx_data_port port[MWIFIEX_TX_DATA_PORT];
	पूर्णांक rx_cmd_ep_type;
	u8 rx_cmd_पूर्णांकerval;
	पूर्णांक tx_cmd_ep_type;
	u8 tx_cmd_पूर्णांकerval;
पूर्ण;

काष्ठा fw_header अणु
	__le32 dnld_cmd;
	__le32 base_addr;
	__le32 data_len;
	__le32 crc;
पूर्ण;

काष्ठा fw_sync_header अणु
	__le32 cmd;
	__le32 seq_num;
पूर्ण __packed;

काष्ठा fw_data अणु
	काष्ठा fw_header fw_hdr;
	__le32 seq_num;
	u8 data[1];
पूर्ण __packed;

#पूर्ण_अगर /*_MWIFIEX_USB_H */
