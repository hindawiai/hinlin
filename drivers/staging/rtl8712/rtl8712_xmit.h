<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित _RTL8712_XMIT_H_
#घोषणा _RTL8712_XMIT_H_

#घोषणा HWXMIT_ENTRY	4

#घोषणा VO_QUEUE_INX	0
#घोषणा VI_QUEUE_INX	1
#घोषणा BE_QUEUE_INX	2
#घोषणा BK_QUEUE_INX	3
#घोषणा TS_QUEUE_INX	4
#घोषणा MGT_QUEUE_INX	5
#घोषणा BMC_QUEUE_INX	6
#घोषणा BCN_QUEUE_INX	7

#घोषणा HW_QUEUE_ENTRY	8

#घोषणा TXDESC_SIZE 32
#घोषणा TXDESC_OFFSET TXDESC_SIZE

#घोषणा NR_AMSDU_XMITFRAME 8
#घोषणा NR_TXAGG_XMITFRAME 8

#घोषणा MAX_AMSDU_XMITBUF_SZ 8704
#घोषणा MAX_TXAGG_XMITBUF_SZ 16384 /*16k*/

#घोषणा tx_cmd tx_desc

/*
 *defined क्रम TX DESC Operation
 */

#घोषणा MAX_TID (15)

/*OFFSET 0*/
#घोषणा OFFSET_SZ (0)
#घोषणा OFFSET_SHT (16)
#घोषणा OWN	BIT(31)
#घोषणा FSG	BIT(27)
#घोषणा LSG	BIT(26)
#घोषणा TYPE_SHT (24)
#घोषणा TYPE_MSK (0x03000000)

/*OFFSET 4*/
#घोषणा PKT_OFFSET_SZ (0)
#घोषणा QSEL_SHT (8)
#घोषणा HWPC BIT(31)

/*OFFSET 8*/
#घोषणा BMC BIT(7)
#घोषणा BK BIT(30)
#घोषणा AGG_EN BIT(29)
#घोषणा RTS_RC_SHT (16)

/*OFFSET 12*/
#घोषणा SEQ_SHT (16)

/*OFFSET 16*/
#घोषणा TXBW BIT(18)

/*OFFSET 20*/
#घोषणा DISFB BIT(15)
#घोषणा RSVD6_MSK (0x00E00000)
#घोषणा RSVD6_SHT (21)

काष्ठा tx_desc अणु
	/*DWORD 0*/
	__le32 txdw0;
	__le32 txdw1;
	__le32 txdw2;
	__le32 txdw3;
	__le32 txdw4;
	__le32 txdw5;
	__le32 txdw6;
	__le32 txdw7;
पूर्ण;

जोड़ txdesc अणु
	काष्ठा tx_desc txdesc;
	अचिन्हित पूर्णांक value[TXDESC_SIZE >> 2];
पूर्ण;

पूर्णांक r8712_xmitframe_complete(काष्ठा _adapter *padapter,
			     काष्ठा xmit_priv *pxmitpriv,
			     काष्ठा xmit_buf *pxmitbuf);
व्योम r8712_करो_queue_select(काष्ठा _adapter *padapter,
			   काष्ठा pkt_attrib *pattrib);

#अगर_घोषित CONFIG_R8712_TX_AGGR
व्योम r8712_xmitframe_aggr_1st(काष्ठा xmit_buf *pxmitbuf,
			      काष्ठा xmit_frame *pxmitframe);
व्योम r8712_dump_aggr_xframe(काष्ठा xmit_buf *pxmitbuf,
			    काष्ठा xmit_frame *pxmitframe);
#पूर्ण_अगर

#पूर्ण_अगर
