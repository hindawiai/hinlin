<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtl_core.h"
#समावेश "r8192E_hw.h"
#समावेश "r8192E_cmdpkt.h"

bool rtl92e_send_cmd_pkt(काष्ठा net_device *dev, u32 type, स्थिर व्योम *data,
			 u32 len)
अणु
	bool				rt_status = true;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u16				frag_length = 0, frag_offset = 0;
	काष्ठा sk_buff		*skb;
	अचिन्हित अक्षर		*seg_ptr;
	काष्ठा cb_desc *tcb_desc;
	u8				bLastIniPkt;

	काष्ठा tx_fwinfo_8190pci *pTxFwInfo = शून्य;

	RT_TRACE(COMP_CMDPKT, "%s(),buffer_len is %d\n", __func__, len);

	करो अणु
		अगर ((len - frag_offset) > CMDPACKET_FRAG_SIZE) अणु
			frag_length = CMDPACKET_FRAG_SIZE;
			bLastIniPkt = 0;

		पूर्ण अन्यथा अणु
			frag_length = (u16)(len - frag_offset);
			bLastIniPkt = 1;
		पूर्ण

		अगर (type == DESC_PACKET_TYPE_NORMAL)
			skb = dev_alloc_skb(frag_length +
					    priv->rtllib->tx_headroom + 4);
		अन्यथा
			skb = dev_alloc_skb(frag_length + 4);

		अगर (!skb) अणु
			rt_status = false;
			जाओ Failed;
		पूर्ण

		स_नकल((अचिन्हित अक्षर *)(skb->cb), &dev, माप(dev));
		tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
		tcb_desc->queue_index = TXCMD_QUEUE;
		tcb_desc->bCmdOrInit = type;
		tcb_desc->bLastIniPkt = bLastIniPkt;

		अगर (type == DESC_PACKET_TYPE_NORMAL) अणु
			tcb_desc->pkt_size = frag_length;

			seg_ptr = skb_put(skb, priv->rtllib->tx_headroom);
			pTxFwInfo = (काष्ठा tx_fwinfo_8190pci *)seg_ptr;
			स_रखो(pTxFwInfo, 0, माप(काष्ठा tx_fwinfo_8190pci));
			स_रखो(pTxFwInfo, 0x12, 8);
		पूर्ण अन्यथा अणु
			tcb_desc->txbuf_size = (u16)frag_length;
		पूर्ण

		seg_ptr = skb_put(skb, frag_length);
		स_नकल(seg_ptr, data, (u32)frag_length);

		अगर (type == DESC_PACKET_TYPE_INIT &&
		    (!priv->rtllib->check_nic_enough_desc(dev, TXCMD_QUEUE) ||
		     (!skb_queue_empty(&priv->rtllib->skb_रुकोQ[TXCMD_QUEUE])) ||
		     (priv->rtllib->queue_stop))) अणु
			skb_queue_tail(&priv->rtllib->skb_रुकोQ[TXCMD_QUEUE],
				       skb);
		पूर्ण अन्यथा अणु
			priv->rtllib->sofपंचांगac_hard_start_xmit(skb, dev);
		पूर्ण

		data += frag_length;
		frag_offset += frag_length;

	पूर्ण जबतक (frag_offset < len);

	rtl92e_ग_लिखोb(dev, TPPoll, TPPoll_CQ);
Failed:
	वापस rt_status;
पूर्ण
