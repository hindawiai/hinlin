<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#अगर_अघोषित _GDM_USB_H_
#घोषणा _GDM_USB_H_

#समावेश <linux/types.h>
#समावेश <linux/usb.h>
#समावेश <linux/list.h>
#समावेश <linux/समय.स>

#समावेश "gdm_endian.h"
#समावेश "hci_packet.h"

#घोषणा PM_NORMAL 0
#घोषणा PM_SUSPEND 1
#घोषणा AUTO_SUSPEND_TIMER 5000 /* ms */

#घोषणा RX_BUF_SIZE		(1024 * 32)
#घोषणा TX_BUF_SIZE		(1024 * 32)
#घोषणा SDU_BUF_SIZE	2048
#घोषणा MAX_SDU_SIZE	(1024 * 30)
#घोषणा MAX_PACKET_IN_MULTI_SDU	256

#घोषणा VID_GCT			0x1076
#घोषणा PID_GDM7240		0x8000
#घोषणा PID_GDM7243		0x9000

#घोषणा NETWORK_INTERFACE 1
#घोषणा USB_SC_SCSI 0x06
#घोषणा USB_PR_BULK 0x50

#घोषणा MAX_NUM_SDU_BUF	64

काष्ठा usb_tx अणु
	काष्ठा list_head list;
	काष्ठा urb *urb;
	u8 *buf;
	u32 len;
	व्योम (*callback)(व्योम *cb_data);
	व्योम *cb_data;
	काष्ठा tx_cxt *tx;
	u8 is_sdu;
पूर्ण;

काष्ठा usb_tx_sdu अणु
	काष्ठा list_head list;
	u8 *buf;
	u32 len;
	व्योम (*callback)(व्योम *cb_data);
	व्योम *cb_data;
पूर्ण;

काष्ठा usb_rx अणु
	काष्ठा list_head to_host_list;
	काष्ठा list_head मुक्त_list;
	काष्ठा list_head rx_submit_list;
	काष्ठा rx_cxt	*rx;
	काष्ठा urb *urb;
	u8 *buf;
	पूर्णांक (*callback)(व्योम *cb_data, व्योम *data, पूर्णांक len, पूर्णांक context);
	व्योम *cb_data;
	व्योम *index;
पूर्ण;

काष्ठा tx_cxt अणु
	काष्ठा list_head sdu_list;
	काष्ठा list_head hci_list;
	काष्ठा list_head मुक्त_list;
	u32 avail_count;
	spinlock_t lock;
पूर्ण;

काष्ठा rx_cxt अणु
	काष्ठा list_head to_host_list;
	काष्ठा list_head rx_submit_list;
	काष्ठा list_head मुक्त_list;
	u32	avail_count;
	spinlock_t to_host_lock;
	spinlock_t rx_lock;
	spinlock_t submit_lock;
पूर्ण;

काष्ठा lte_udev अणु
	काष्ठा usb_device *usbdev;
	काष्ठा tx_cxt tx;
	काष्ठा rx_cxt rx;
	काष्ठा delayed_work work_tx;
	काष्ठा delayed_work work_rx;
	u8 gdm_ed;
	u8 send_complete;
	u8 tx_stop;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक (*rx_cb)(व्योम *cb_data, व्योम *data, पूर्णांक len, पूर्णांक context);
	पूर्णांक usb_state;
	u8 request_mac_addr;
पूर्ण;

#पूर्ण_अगर /* _GDM_USB_H_ */
