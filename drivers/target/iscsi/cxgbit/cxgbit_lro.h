<शैली गुरु>
/*
 * Copyright (c) 2016 Chelsio Communications, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 */

#अगर_अघोषित	__CXGBIT_LRO_H__
#घोषणा	__CXGBIT_LRO_H__

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>

#घोषणा LRO_FLUSH_LEN_MAX	65535

काष्ठा cxgbit_lro_cb अणु
	काष्ठा cxgbit_sock *csk;
	u32 pdu_totallen;
	u32 offset;
	u8 pdu_idx;
	bool complete;
पूर्ण;

क्रमागत cxgbit_pducb_flags अणु
	PDUCBF_RX_HDR		= (1 << 0), /* received pdu header */
	PDUCBF_RX_DATA		= (1 << 1), /* received pdu payload */
	PDUCBF_RX_STATUS	= (1 << 2), /* received ddp status */
	PDUCBF_RX_DATA_DDPD	= (1 << 3), /* pdu payload ddp'd */
	PDUCBF_RX_DDP_CMP	= (1 << 4), /* ddp completion */
	PDUCBF_RX_HCRC_ERR	= (1 << 5), /* header digest error */
	PDUCBF_RX_DCRC_ERR	= (1 << 6), /* data digest error */
पूर्ण;

काष्ठा cxgbit_lro_pdu_cb अणु
	u8 flags;
	u8 frags;
	u8 hfrag_idx;
	u8 nr_dfrags;
	u8 dfrag_idx;
	bool complete;
	u32 seq;
	u32 pdulen;
	u32 hlen;
	u32 dlen;
	u32 करोffset;
	u32 ddigest;
	व्योम *hdr;
पूर्ण;

#घोषणा LRO_SKB_MAX_HEADROOM  \
		(माप(काष्ठा cxgbit_lro_cb) + \
		 (MAX_SKB_FRAGS * माप(काष्ठा cxgbit_lro_pdu_cb)))

#घोषणा LRO_SKB_MIN_HEADROOM  \
		(माप(काष्ठा cxgbit_lro_cb) + \
		 माप(काष्ठा cxgbit_lro_pdu_cb))

#घोषणा cxgbit_skb_lro_cb(skb)	((काष्ठा cxgbit_lro_cb *)skb->data)
#घोषणा cxgbit_skb_lro_pdu_cb(skb, i)	\
	((काष्ठा cxgbit_lro_pdu_cb *)(skb->data + माप(काष्ठा cxgbit_lro_cb) \
		+ (i * माप(काष्ठा cxgbit_lro_pdu_cb))))

#घोषणा CPL_RX_ISCSI_DDP_STATUS_DDP_SHIFT	16 /* ddp'able */
#घोषणा CPL_RX_ISCSI_DDP_STATUS_PAD_SHIFT	19 /* pad error */
#घोषणा CPL_RX_ISCSI_DDP_STATUS_HCRC_SHIFT	20 /* hcrc error */
#घोषणा CPL_RX_ISCSI_DDP_STATUS_DCRC_SHIFT	21 /* dcrc error */

#पूर्ण_अगर	/*__CXGBIT_LRO_H_*/
