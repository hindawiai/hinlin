<शैली गुरु>
#अगर_अघोषित LLC_IF_H
#घोषणा LLC_IF_H
/*
 * Copyright (c) 1997 by Procom Technology,Inc.
 * 		 2001 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
/* Defines LLC पूर्णांकerface to network layer */
/* Available primitives */
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/llc.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/llc.h>

#घोषणा LLC_DATAUNIT_PRIM	1
#घोषणा LLC_CONN_PRIM		2
#घोषणा LLC_DATA_PRIM		3
#घोषणा LLC_DISC_PRIM		4
#घोषणा LLC_RESET_PRIM		5
#घोषणा LLC_FLOWCONTROL_PRIM	6 /* Not supported at this समय */
#घोषणा LLC_DISABLE_PRIM	7
#घोषणा LLC_XID_PRIM		8
#घोषणा LLC_TEST_PRIM		9
#घोषणा LLC_SAP_ACTIVATION     10
#घोषणा LLC_SAP_DEACTIVATION   11

#घोषणा LLC_NBR_PRIMITIVES     11

#घोषणा LLC_IND			1
#घोषणा LLC_CONFIRM		2

/* Primitive type */
#घोषणा LLC_PRIM_TYPE_REQ	1
#घोषणा LLC_PRIM_TYPE_IND	2
#घोषणा LLC_PRIM_TYPE_RESP	3
#घोषणा LLC_PRIM_TYPE_CONFIRM	4

/* Reset reasons, remote entity or local LLC */
#घोषणा LLC_RESET_REASON_REMOTE	1
#घोषणा LLC_RESET_REASON_LOCAL	2

/* Disconnect reasons */
#घोषणा LLC_DISC_REASON_RX_DM_RSP_PDU	0
#घोषणा LLC_DISC_REASON_RX_DISC_CMD_PDU	1
#घोषणा LLC_DISC_REASON_ACK_TMR_EXP	2

/* Confirm reasons */
#घोषणा LLC_STATUS_CONN		0 /* connect confirm & reset confirm */
#घोषणा LLC_STATUS_DISC		1 /* connect confirm & reset confirm */
#घोषणा LLC_STATUS_FAILED	2 /* connect confirm & reset confirm */
#घोषणा LLC_STATUS_IMPOSSIBLE	3 /* connect confirm */
#घोषणा LLC_STATUS_RECEIVED	4 /* data conn */
#घोषणा LLC_STATUS_REMOTE_BUSY	5 /* data conn */
#घोषणा LLC_STATUS_REFUSE	6 /* data conn */
#घोषणा LLC_STATUS_CONFLICT	7 /* disconnect conn */
#घोषणा LLC_STATUS_RESET_DONE	8 /*  */

पूर्णांक llc_establish_connection(काष्ठा sock *sk, u8 *lmac, u8 *dmac, u8 dsap);
पूर्णांक llc_build_and_send_pkt(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक llc_send_disc(काष्ठा sock *sk);
#पूर्ण_अगर /* LLC_IF_H */
