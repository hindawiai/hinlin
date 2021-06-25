<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#अगर_अघोषित _GDM_MUX_H_
#घोषणा _GDM_MUX_H_

#समावेश <linux/types.h>
#समावेश <linux/usb.h>
#समावेश <linux/list.h>

#समावेश "gdm_tty.h"

#घोषणा PM_NORMAL 0
#घोषणा PM_SUSPEND 1

#घोषणा USB_RT_ACM          (USB_TYPE_CLASS | USB_RECIP_INTERFACE)

#घोषणा START_FLAG 0xA512485A
#घोषणा MUX_HEADER_SIZE 14
#घोषणा MUX_TX_MAX_SIZE (1024 * 10)
#घोषणा MUX_RX_MAX_SIZE (1024 * 30)
#घोषणा AT_PKT_TYPE 0xF011
#घोषणा DM_PKT_TYPE 0xF010

#घोषणा RETRY_TIMER 30 /* msec */

काष्ठा mux_pkt_header अणु
	__le32 start_flag;
	__le32 seq_num;
	__le32 payload_size;
	__le16 packet_type;
	अचिन्हित अक्षर data[];
पूर्ण;

काष्ठा mux_tx अणु
	काष्ठा urb *urb;
	u8 *buf;
	पूर्णांक  len;
	व्योम (*callback)(व्योम *cb_data);
	व्योम *cb_data;
पूर्ण;

काष्ठा mux_rx अणु
	काष्ठा list_head मुक्त_list;
	काष्ठा list_head rx_submit_list;
	काष्ठा list_head to_host_list;
	काष्ठा urb *urb;
	u8 *buf;
	व्योम *mux_dev;
	u32 offset;
	u32 len;
	पूर्णांक (*callback)(व्योम *data,
			पूर्णांक len,
			पूर्णांक tty_index,
			काष्ठा tty_dev *tty_dev,
			पूर्णांक complete);
पूर्ण;

काष्ठा rx_cxt अणु
	काष्ठा list_head to_host_list;
	काष्ठा list_head rx_submit_list;
	काष्ठा list_head rx_मुक्त_list;
	spinlock_t to_host_lock;
	spinlock_t submit_list_lock;
	spinlock_t मुक्त_list_lock;
पूर्ण;

काष्ठा mux_dev अणु
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *control_पूर्णांकf;
	काष्ठा usb_पूर्णांकerface *data_पूर्णांकf;
	काष्ठा rx_cxt	rx;
	काष्ठा delayed_work work_rx;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक usb_state;
	पूर्णांक (*rx_cb)(व्योम *data,
		     पूर्णांक len,
		     पूर्णांक tty_index,
		     काष्ठा tty_dev *tty_dev,
		     पूर्णांक complete);
	spinlock_t ग_लिखो_lock;
	काष्ठा tty_dev *tty_dev;
पूर्ण;

#पूर्ण_अगर /* _GDM_MUX_H_ */
