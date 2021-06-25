<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: usbpipe.h
 *
 * Purpose:
 *
 * Author: Warren Hsu
 *
 * Date: Mar. 30, 2005
 *
 */

#अगर_अघोषित __USBPIPE_H__
#घोषणा __USBPIPE_H__

#समावेश "device.h"

काष्ठा vnt_पूर्णांकerrupt_data अणु
	u8 tsr0;
	u8 pkt0;
	u16 समय0;
	u8 tsr1;
	u8 pkt1;
	u16 समय1;
	u8 tsr2;
	u8 pkt2;
	u16 समय2;
	u8 tsr3;
	u8 pkt3;
	u16 समय3;
	__le64 tsf;
	u8 isr0;
	u8 isr1;
	u8 rts_success;
	u8 rts_fail;
	u8 ack_fail;
	u8 fcs_err;
	u8 sw[2];
पूर्ण __packed;

काष्ठा vnt_tx_usb_header अणु
	u8 type;
	u8 pkt_no;
	__le16 tx_byte_count;
पूर्ण __packed;

#घोषणा VNT_REG_BLOCK_SIZE	64

पूर्णांक vnt_control_out(काष्ठा vnt_निजी *priv, u8 request, u16 value,
		    u16 index, u16 length, स्थिर u8 *buffer);
पूर्णांक vnt_control_in(काष्ठा vnt_निजी *priv, u8 request, u16 value,
		   u16 index, u16 length,  u8 *buffer);

पूर्णांक vnt_control_out_u8(काष्ठा vnt_निजी *priv, u8 reg, u8 ref_off, u8 data);
पूर्णांक vnt_control_in_u8(काष्ठा vnt_निजी *priv, u8 reg, u8 reg_off, u8 *data);

पूर्णांक vnt_control_out_blocks(काष्ठा vnt_निजी *priv,
			   u16 block, u8 reg, u16 len, स्थिर u8 *data);

पूर्णांक vnt_start_पूर्णांकerrupt_urb(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_submit_rx_urb(काष्ठा vnt_निजी *priv, काष्ठा vnt_rcb *rcb);
पूर्णांक vnt_tx_context(काष्ठा vnt_निजी *priv,
		   काष्ठा vnt_usb_send_context *context,
		   काष्ठा sk_buff *skb);

#पूर्ण_अगर /* __USBPIPE_H__ */
