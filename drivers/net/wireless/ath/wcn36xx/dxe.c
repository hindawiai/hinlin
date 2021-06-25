<शैली गुरु>
/*
 * Copyright (c) 2013 Eugene Krasnikov <k.eugene.e@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* DXE - DMA transfer engine
 * we have 2 channels(High prio and Low prio) क्रम TX and 2 channels क्रम RX.
 * through low channels data packets are transfered
 * through high channels managment packets are transfered
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/soc/qcom/smem_state.h>
#समावेश "wcn36xx.h"
#समावेश "txrx.h"

अटल व्योम wcn36xx_ccu_ग_लिखो_रेजिस्टर(काष्ठा wcn36xx *wcn, पूर्णांक addr, पूर्णांक data)
अणु
	wcn36xx_dbg(WCN36XX_DBG_DXE,
		    "wcn36xx_ccu_write_register: addr=%x, data=%x\n",
		    addr, data);

	ग_लिखोl(data, wcn->ccu_base + addr);
पूर्ण

अटल व्योम wcn36xx_dxe_ग_लिखो_रेजिस्टर(काष्ठा wcn36xx *wcn, पूर्णांक addr, पूर्णांक data)
अणु
	wcn36xx_dbg(WCN36XX_DBG_DXE,
		    "wcn36xx_dxe_write_register: addr=%x, data=%x\n",
		    addr, data);

	ग_लिखोl(data, wcn->dxe_base + addr);
पूर्ण

अटल व्योम wcn36xx_dxe_पढ़ो_रेजिस्टर(काष्ठा wcn36xx *wcn, पूर्णांक addr, पूर्णांक *data)
अणु
	*data = पढ़ोl(wcn->dxe_base + addr);

	wcn36xx_dbg(WCN36XX_DBG_DXE,
		    "wcn36xx_dxe_read_register: addr=%x, data=%x\n",
		    addr, *data);
पूर्ण

अटल व्योम wcn36xx_dxe_मुक्त_ctl_block(काष्ठा wcn36xx_dxe_ch *ch)
अणु
	काष्ठा wcn36xx_dxe_ctl *ctl = ch->head_blk_ctl, *next;
	पूर्णांक i;

	क्रम (i = 0; i < ch->desc_num && ctl; i++) अणु
		next = ctl->next;
		kमुक्त(ctl);
		ctl = next;
	पूर्ण
पूर्ण

अटल पूर्णांक wcn36xx_dxe_allocate_ctl_block(काष्ठा wcn36xx_dxe_ch *ch)
अणु
	काष्ठा wcn36xx_dxe_ctl *prev_ctl = शून्य;
	काष्ठा wcn36xx_dxe_ctl *cur_ctl = शून्य;
	पूर्णांक i;

	spin_lock_init(&ch->lock);
	क्रम (i = 0; i < ch->desc_num; i++) अणु
		cur_ctl = kzalloc(माप(*cur_ctl), GFP_KERNEL);
		अगर (!cur_ctl)
			जाओ out_fail;

		cur_ctl->ctl_blk_order = i;
		अगर (i == 0) अणु
			ch->head_blk_ctl = cur_ctl;
			ch->tail_blk_ctl = cur_ctl;
		पूर्ण अन्यथा अगर (ch->desc_num - 1 == i) अणु
			prev_ctl->next = cur_ctl;
			cur_ctl->next = ch->head_blk_ctl;
		पूर्ण अन्यथा अणु
			prev_ctl->next = cur_ctl;
		पूर्ण
		prev_ctl = cur_ctl;
	पूर्ण

	वापस 0;

out_fail:
	wcn36xx_dxe_मुक्त_ctl_block(ch);
	वापस -ENOMEM;
पूर्ण

पूर्णांक wcn36xx_dxe_alloc_ctl_blks(काष्ठा wcn36xx *wcn)
अणु
	पूर्णांक ret;

	wcn->dxe_tx_l_ch.ch_type = WCN36XX_DXE_CH_TX_L;
	wcn->dxe_tx_h_ch.ch_type = WCN36XX_DXE_CH_TX_H;
	wcn->dxe_rx_l_ch.ch_type = WCN36XX_DXE_CH_RX_L;
	wcn->dxe_rx_h_ch.ch_type = WCN36XX_DXE_CH_RX_H;

	wcn->dxe_tx_l_ch.desc_num = WCN36XX_DXE_CH_DESC_NUMB_TX_L;
	wcn->dxe_tx_h_ch.desc_num = WCN36XX_DXE_CH_DESC_NUMB_TX_H;
	wcn->dxe_rx_l_ch.desc_num = WCN36XX_DXE_CH_DESC_NUMB_RX_L;
	wcn->dxe_rx_h_ch.desc_num = WCN36XX_DXE_CH_DESC_NUMB_RX_H;

	wcn->dxe_tx_l_ch.dxe_wq =  WCN36XX_DXE_WQ_TX_L;
	wcn->dxe_tx_h_ch.dxe_wq =  WCN36XX_DXE_WQ_TX_H;

	wcn->dxe_tx_l_ch.ctrl_bd = WCN36XX_DXE_CTRL_TX_L_BD;
	wcn->dxe_tx_h_ch.ctrl_bd = WCN36XX_DXE_CTRL_TX_H_BD;

	wcn->dxe_tx_l_ch.ctrl_skb = WCN36XX_DXE_CTRL_TX_L_SKB;
	wcn->dxe_tx_h_ch.ctrl_skb = WCN36XX_DXE_CTRL_TX_H_SKB;

	wcn->dxe_tx_l_ch.reg_ctrl = WCN36XX_DXE_REG_CTL_TX_L;
	wcn->dxe_tx_h_ch.reg_ctrl = WCN36XX_DXE_REG_CTL_TX_H;

	wcn->dxe_tx_l_ch.def_ctrl = WCN36XX_DXE_CH_DEFAULT_CTL_TX_L;
	wcn->dxe_tx_h_ch.def_ctrl = WCN36XX_DXE_CH_DEFAULT_CTL_TX_H;

	/* DXE control block allocation */
	ret = wcn36xx_dxe_allocate_ctl_block(&wcn->dxe_tx_l_ch);
	अगर (ret)
		जाओ out_err;
	ret = wcn36xx_dxe_allocate_ctl_block(&wcn->dxe_tx_h_ch);
	अगर (ret)
		जाओ out_err;
	ret = wcn36xx_dxe_allocate_ctl_block(&wcn->dxe_rx_l_ch);
	अगर (ret)
		जाओ out_err;
	ret = wcn36xx_dxe_allocate_ctl_block(&wcn->dxe_rx_h_ch);
	अगर (ret)
		जाओ out_err;

	/* Initialize SMSM state  Clear TX Enable RING EMPTY STATE */
	ret = qcom_smem_state_update_bits(wcn->tx_enable_state,
					  WCN36XX_SMSM_WLAN_TX_ENABLE |
					  WCN36XX_SMSM_WLAN_TX_RINGS_EMPTY,
					  WCN36XX_SMSM_WLAN_TX_RINGS_EMPTY);
	अगर (ret)
		जाओ out_err;

	वापस 0;

out_err:
	wcn36xx_err("Failed to allocate DXE control blocks\n");
	wcn36xx_dxe_मुक्त_ctl_blks(wcn);
	वापस -ENOMEM;
पूर्ण

व्योम wcn36xx_dxe_मुक्त_ctl_blks(काष्ठा wcn36xx *wcn)
अणु
	wcn36xx_dxe_मुक्त_ctl_block(&wcn->dxe_tx_l_ch);
	wcn36xx_dxe_मुक्त_ctl_block(&wcn->dxe_tx_h_ch);
	wcn36xx_dxe_मुक्त_ctl_block(&wcn->dxe_rx_l_ch);
	wcn36xx_dxe_मुक्त_ctl_block(&wcn->dxe_rx_h_ch);
पूर्ण

अटल पूर्णांक wcn36xx_dxe_init_descs(काष्ठा device *dev, काष्ठा wcn36xx_dxe_ch *wcn_ch)
अणु
	काष्ठा wcn36xx_dxe_desc *cur_dxe = शून्य;
	काष्ठा wcn36xx_dxe_desc *prev_dxe = शून्य;
	काष्ठा wcn36xx_dxe_ctl *cur_ctl = शून्य;
	माप_प्रकार size;
	पूर्णांक i;

	size = wcn_ch->desc_num * माप(काष्ठा wcn36xx_dxe_desc);
	wcn_ch->cpu_addr = dma_alloc_coherent(dev, size, &wcn_ch->dma_addr,
					      GFP_KERNEL);
	अगर (!wcn_ch->cpu_addr)
		वापस -ENOMEM;

	cur_dxe = (काष्ठा wcn36xx_dxe_desc *)wcn_ch->cpu_addr;
	cur_ctl = wcn_ch->head_blk_ctl;

	क्रम (i = 0; i < wcn_ch->desc_num; i++) अणु
		cur_ctl->desc = cur_dxe;
		cur_ctl->desc_phy_addr = wcn_ch->dma_addr +
			i * माप(काष्ठा wcn36xx_dxe_desc);

		चयन (wcn_ch->ch_type) अणु
		हाल WCN36XX_DXE_CH_TX_L:
			cur_dxe->ctrl = WCN36XX_DXE_CTRL_TX_L;
			cur_dxe->dst_addr_l = WCN36XX_DXE_WQ_TX_L;
			अवरोध;
		हाल WCN36XX_DXE_CH_TX_H:
			cur_dxe->ctrl = WCN36XX_DXE_CTRL_TX_H;
			cur_dxe->dst_addr_l = WCN36XX_DXE_WQ_TX_H;
			अवरोध;
		हाल WCN36XX_DXE_CH_RX_L:
			cur_dxe->ctrl = WCN36XX_DXE_CTRL_RX_L;
			cur_dxe->src_addr_l = WCN36XX_DXE_WQ_RX_L;
			अवरोध;
		हाल WCN36XX_DXE_CH_RX_H:
			cur_dxe->ctrl = WCN36XX_DXE_CTRL_RX_H;
			cur_dxe->src_addr_l = WCN36XX_DXE_WQ_RX_H;
			अवरोध;
		पूर्ण
		अगर (0 == i) अणु
			cur_dxe->phy_next_l = 0;
		पूर्ण अन्यथा अगर ((0 < i) && (i < wcn_ch->desc_num - 1)) अणु
			prev_dxe->phy_next_l =
				cur_ctl->desc_phy_addr;
		पूर्ण अन्यथा अगर (i == (wcn_ch->desc_num - 1)) अणु
			prev_dxe->phy_next_l =
				cur_ctl->desc_phy_addr;
			cur_dxe->phy_next_l =
				wcn_ch->head_blk_ctl->desc_phy_addr;
		पूर्ण
		cur_ctl = cur_ctl->next;
		prev_dxe = cur_dxe;
		cur_dxe++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wcn36xx_dxe_deinit_descs(काष्ठा device *dev, काष्ठा wcn36xx_dxe_ch *wcn_ch)
अणु
	माप_प्रकार size;

	size = wcn_ch->desc_num * माप(काष्ठा wcn36xx_dxe_desc);
	dma_मुक्त_coherent(dev, size,wcn_ch->cpu_addr, wcn_ch->dma_addr);
पूर्ण

अटल व्योम wcn36xx_dxe_init_tx_bd(काष्ठा wcn36xx_dxe_ch *ch,
				   काष्ठा wcn36xx_dxe_mem_pool *pool)
अणु
	पूर्णांक i, chunk_size = pool->chunk_size;
	dma_addr_t bd_phy_addr = pool->phy_addr;
	व्योम *bd_cpu_addr = pool->virt_addr;
	काष्ठा wcn36xx_dxe_ctl *cur = ch->head_blk_ctl;

	क्रम (i = 0; i < ch->desc_num; i++) अणु
		/* Only every second dxe needs a bd poपूर्णांकer,
		   the other will poपूर्णांक to the skb data */
		अगर (!(i & 1)) अणु
			cur->bd_phy_addr = bd_phy_addr;
			cur->bd_cpu_addr = bd_cpu_addr;
			bd_phy_addr += chunk_size;
			bd_cpu_addr += chunk_size;
		पूर्ण अन्यथा अणु
			cur->bd_phy_addr = 0;
			cur->bd_cpu_addr = शून्य;
		पूर्ण
		cur = cur->next;
	पूर्ण
पूर्ण

अटल पूर्णांक wcn36xx_dxe_enable_ch_पूर्णांक(काष्ठा wcn36xx *wcn, u16 wcn_ch)
अणु
	पूर्णांक reg_data = 0;

	wcn36xx_dxe_पढ़ो_रेजिस्टर(wcn,
				  WCN36XX_DXE_INT_MASK_REG,
				  &reg_data);

	reg_data |= wcn_ch;

	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
				   WCN36XX_DXE_INT_MASK_REG,
				   (पूर्णांक)reg_data);
	वापस 0;
पूर्ण

अटल पूर्णांक wcn36xx_dxe_fill_skb(काष्ठा device *dev,
				काष्ठा wcn36xx_dxe_ctl *ctl,
				gfp_t gfp)
अणु
	काष्ठा wcn36xx_dxe_desc *dxe = ctl->desc;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(WCN36XX_PKT_SIZE, gfp);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	dxe->dst_addr_l = dma_map_single(dev,
					 skb_tail_poपूर्णांकer(skb),
					 WCN36XX_PKT_SIZE,
					 DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, dxe->dst_addr_l)) अणु
		dev_err(dev, "unable to map skb\n");
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण
	ctl->skb = skb;

	वापस 0;
पूर्ण

अटल पूर्णांक wcn36xx_dxe_ch_alloc_skb(काष्ठा wcn36xx *wcn,
				    काष्ठा wcn36xx_dxe_ch *wcn_ch)
अणु
	पूर्णांक i;
	काष्ठा wcn36xx_dxe_ctl *cur_ctl = शून्य;

	cur_ctl = wcn_ch->head_blk_ctl;

	क्रम (i = 0; i < wcn_ch->desc_num; i++) अणु
		wcn36xx_dxe_fill_skb(wcn->dev, cur_ctl, GFP_KERNEL);
		cur_ctl = cur_ctl->next;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wcn36xx_dxe_ch_मुक्त_skbs(काष्ठा wcn36xx *wcn,
				     काष्ठा wcn36xx_dxe_ch *wcn_ch)
अणु
	काष्ठा wcn36xx_dxe_ctl *cur = wcn_ch->head_blk_ctl;
	पूर्णांक i;

	क्रम (i = 0; i < wcn_ch->desc_num; i++) अणु
		kमुक्त_skb(cur->skb);
		cur = cur->next;
	पूर्ण
पूर्ण

व्योम wcn36xx_dxe_tx_ack_ind(काष्ठा wcn36xx *wcn, u32 status)
अणु
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wcn->dxe_lock, flags);
	skb = wcn->tx_ack_skb;
	wcn->tx_ack_skb = शून्य;
	del_समयr(&wcn->tx_ack_समयr);
	spin_unlock_irqrestore(&wcn->dxe_lock, flags);

	अगर (!skb) अणु
		wcn36xx_warn("Spurious TX complete indication\n");
		वापस;
	पूर्ण

	info = IEEE80211_SKB_CB(skb);

	अगर (status == 1)
		info->flags |= IEEE80211_TX_STAT_ACK;
	अन्यथा
		info->flags &= ~IEEE80211_TX_STAT_ACK;

	wcn36xx_dbg(WCN36XX_DBG_DXE, "dxe tx ack status: %d\n", status);

	ieee80211_tx_status_irqsafe(wcn->hw, skb);
	ieee80211_wake_queues(wcn->hw);
पूर्ण

अटल व्योम wcn36xx_dxe_tx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा wcn36xx *wcn = from_समयr(wcn, t, tx_ack_समयr);
	काष्ठा ieee80211_tx_info *info;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;

	/* TX Timeout */
	wcn36xx_dbg(WCN36XX_DBG_DXE, "TX timeout\n");

	spin_lock_irqsave(&wcn->dxe_lock, flags);
	skb = wcn->tx_ack_skb;
	wcn->tx_ack_skb = शून्य;
	spin_unlock_irqrestore(&wcn->dxe_lock, flags);

	अगर (!skb)
		वापस;

	info = IEEE80211_SKB_CB(skb);
	info->flags &= ~IEEE80211_TX_STAT_ACK;
	info->flags &= ~IEEE80211_TX_STAT_NOACK_TRANSMITTED;

	ieee80211_tx_status_irqsafe(wcn->hw, skb);
	ieee80211_wake_queues(wcn->hw);
पूर्ण

अटल व्योम reap_tx_dxes(काष्ठा wcn36xx *wcn, काष्ठा wcn36xx_dxe_ch *ch)
अणु
	काष्ठा wcn36xx_dxe_ctl *ctl;
	काष्ठा ieee80211_tx_info *info;
	अचिन्हित दीर्घ flags;

	/*
	 * Make at least one loop of करो-जबतक because in हाल ring is
	 * completely full head and tail are poपूर्णांकing to the same element
	 * and जबतक-करो will not make any cycles.
	 */
	spin_lock_irqsave(&ch->lock, flags);
	ctl = ch->tail_blk_ctl;
	करो अणु
		अगर (READ_ONCE(ctl->desc->ctrl) & WCN36xx_DXE_CTRL_VLD)
			अवरोध;

		अगर (ctl->skb &&
		    READ_ONCE(ctl->desc->ctrl) & WCN36xx_DXE_CTRL_EOP) अणु
			dma_unmap_single(wcn->dev, ctl->desc->src_addr_l,
					 ctl->skb->len, DMA_TO_DEVICE);
			info = IEEE80211_SKB_CB(ctl->skb);
			अगर (!(info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS)) अणु
				/* Keep frame until TX status comes */
				ieee80211_मुक्त_txskb(wcn->hw, ctl->skb);
			पूर्ण

			अगर (wcn->queues_stopped) अणु
				wcn->queues_stopped = false;
				ieee80211_wake_queues(wcn->hw);
			पूर्ण

			ctl->skb = शून्य;
		पूर्ण
		ctl = ctl->next;
	पूर्ण जबतक (ctl != ch->head_blk_ctl);

	ch->tail_blk_ctl = ctl;
	spin_unlock_irqrestore(&ch->lock, flags);
पूर्ण

अटल irqवापस_t wcn36xx_irq_tx_complete(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा wcn36xx *wcn = (काष्ठा wcn36xx *)dev;
	पूर्णांक पूर्णांक_src, पूर्णांक_reason;
	bool transmitted = false;

	wcn36xx_dxe_पढ़ो_रेजिस्टर(wcn, WCN36XX_DXE_INT_SRC_RAW_REG, &पूर्णांक_src);

	अगर (पूर्णांक_src & WCN36XX_INT_MASK_CHAN_TX_H) अणु
		wcn36xx_dxe_पढ़ो_रेजिस्टर(wcn,
					  WCN36XX_DXE_CH_STATUS_REG_ADDR_TX_H,
					  &पूर्णांक_reason);

		wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
					   WCN36XX_DXE_0_INT_CLR,
					   WCN36XX_INT_MASK_CHAN_TX_H);

		अगर (पूर्णांक_reason & WCN36XX_CH_STAT_INT_ERR_MASK ) अणु
			wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
						   WCN36XX_DXE_0_INT_ERR_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_H);

			wcn36xx_err("DXE IRQ reported error: 0x%x in high TX channel\n",
					पूर्णांक_src);
		पूर्ण

		अगर (पूर्णांक_reason & WCN36XX_CH_STAT_INT_DONE_MASK) अणु
			wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
						   WCN36XX_DXE_0_INT_DONE_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_H);
		पूर्ण

		अगर (पूर्णांक_reason & WCN36XX_CH_STAT_INT_ED_MASK) अणु
			wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
						   WCN36XX_DXE_0_INT_ED_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_H);
		पूर्ण

		wcn36xx_dbg(WCN36XX_DBG_DXE, "dxe tx ready high, reason %08x\n",
			    पूर्णांक_reason);

		अगर (पूर्णांक_reason & (WCN36XX_CH_STAT_INT_DONE_MASK |
				  WCN36XX_CH_STAT_INT_ED_MASK)) अणु
			reap_tx_dxes(wcn, &wcn->dxe_tx_h_ch);
			transmitted = true;
		पूर्ण
	पूर्ण

	अगर (पूर्णांक_src & WCN36XX_INT_MASK_CHAN_TX_L) अणु
		wcn36xx_dxe_पढ़ो_रेजिस्टर(wcn,
					  WCN36XX_DXE_CH_STATUS_REG_ADDR_TX_L,
					  &पूर्णांक_reason);

		wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
					   WCN36XX_DXE_0_INT_CLR,
					   WCN36XX_INT_MASK_CHAN_TX_L);


		अगर (पूर्णांक_reason & WCN36XX_CH_STAT_INT_ERR_MASK ) अणु
			wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
						   WCN36XX_DXE_0_INT_ERR_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_L);

			wcn36xx_err("DXE IRQ reported error: 0x%x in low TX channel\n",
					पूर्णांक_src);
		पूर्ण

		अगर (पूर्णांक_reason & WCN36XX_CH_STAT_INT_DONE_MASK) अणु
			wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
						   WCN36XX_DXE_0_INT_DONE_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_L);
		पूर्ण

		अगर (पूर्णांक_reason & WCN36XX_CH_STAT_INT_ED_MASK) अणु
			wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
						   WCN36XX_DXE_0_INT_ED_CLR,
						   WCN36XX_INT_MASK_CHAN_TX_L);
		पूर्ण

		wcn36xx_dbg(WCN36XX_DBG_DXE, "dxe tx ready low, reason %08x\n",
			    पूर्णांक_reason);

		अगर (पूर्णांक_reason & (WCN36XX_CH_STAT_INT_DONE_MASK |
				  WCN36XX_CH_STAT_INT_ED_MASK)) अणु
			reap_tx_dxes(wcn, &wcn->dxe_tx_l_ch);
			transmitted = true;
		पूर्ण
	पूर्ण

	spin_lock(&wcn->dxe_lock);
	अगर (wcn->tx_ack_skb && transmitted) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(wcn->tx_ack_skb);

		/* TX complete, no need to रुको क्रम 802.11 ack indication */
		अगर (info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS &&
		    info->flags & IEEE80211_TX_CTL_NO_ACK) अणु
			info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;
			del_समयr(&wcn->tx_ack_समयr);
			ieee80211_tx_status_irqsafe(wcn->hw, wcn->tx_ack_skb);
			wcn->tx_ack_skb = शून्य;
			ieee80211_wake_queues(wcn->hw);
		पूर्ण
	पूर्ण
	spin_unlock(&wcn->dxe_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t wcn36xx_irq_rx_पढ़ोy(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा wcn36xx *wcn = (काष्ठा wcn36xx *)dev;

	wcn36xx_dxe_rx_frame(wcn);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wcn36xx_dxe_request_irqs(काष्ठा wcn36xx *wcn)
अणु
	पूर्णांक ret;

	ret = request_irq(wcn->tx_irq, wcn36xx_irq_tx_complete,
			  IRQF_TRIGGER_HIGH, "wcn36xx_tx", wcn);
	अगर (ret) अणु
		wcn36xx_err("failed to alloc tx irq\n");
		जाओ out_err;
	पूर्ण

	ret = request_irq(wcn->rx_irq, wcn36xx_irq_rx_पढ़ोy, IRQF_TRIGGER_HIGH,
			  "wcn36xx_rx", wcn);
	अगर (ret) अणु
		wcn36xx_err("failed to alloc rx irq\n");
		जाओ out_txirq;
	पूर्ण

	enable_irq_wake(wcn->rx_irq);

	वापस 0;

out_txirq:
	मुक्त_irq(wcn->tx_irq, wcn);
out_err:
	वापस ret;

पूर्ण

अटल पूर्णांक wcn36xx_rx_handle_packets(काष्ठा wcn36xx *wcn,
				     काष्ठा wcn36xx_dxe_ch *ch,
				     u32 ctrl,
				     u32 en_mask,
				     u32 पूर्णांक_mask,
				     u32 status_reg)
अणु
	काष्ठा wcn36xx_dxe_desc *dxe;
	काष्ठा wcn36xx_dxe_ctl *ctl;
	dma_addr_t  dma_addr;
	काष्ठा sk_buff *skb;
	u32 पूर्णांक_reason;
	पूर्णांक ret;

	wcn36xx_dxe_पढ़ो_रेजिस्टर(wcn, status_reg, &पूर्णांक_reason);
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn, WCN36XX_DXE_0_INT_CLR, पूर्णांक_mask);

	अगर (पूर्णांक_reason & WCN36XX_CH_STAT_INT_ERR_MASK) अणु
		wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
					   WCN36XX_DXE_0_INT_ERR_CLR,
					   पूर्णांक_mask);

		wcn36xx_err("DXE IRQ reported error on RX channel\n");
	पूर्ण

	अगर (पूर्णांक_reason & WCN36XX_CH_STAT_INT_DONE_MASK)
		wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
					   WCN36XX_DXE_0_INT_DONE_CLR,
					   पूर्णांक_mask);

	अगर (पूर्णांक_reason & WCN36XX_CH_STAT_INT_ED_MASK)
		wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
					   WCN36XX_DXE_0_INT_ED_CLR,
					   पूर्णांक_mask);

	अगर (!(पूर्णांक_reason & (WCN36XX_CH_STAT_INT_DONE_MASK |
			    WCN36XX_CH_STAT_INT_ED_MASK)))
		वापस 0;

	spin_lock(&ch->lock);

	ctl = ch->head_blk_ctl;
	dxe = ctl->desc;

	जबतक (!(READ_ONCE(dxe->ctrl) & WCN36xx_DXE_CTRL_VLD)) अणु
		skb = ctl->skb;
		dma_addr = dxe->dst_addr_l;
		ret = wcn36xx_dxe_fill_skb(wcn->dev, ctl, GFP_ATOMIC);
		अगर (0 == ret) अणु
			/* new skb allocation ok. Use the new one and queue
			 * the old one to network प्रणाली.
			 */
			dma_unmap_single(wcn->dev, dma_addr, WCN36XX_PKT_SIZE,
					DMA_FROM_DEVICE);
			wcn36xx_rx_skb(wcn, skb);
		पूर्ण /* अन्यथा keep old skb not submitted and use it क्रम rx DMA */

		dxe->ctrl = ctrl;
		ctl = ctl->next;
		dxe = ctl->desc;
	पूर्ण
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn, WCN36XX_DXE_ENCH_ADDR, en_mask);

	ch->head_blk_ctl = ctl;

	spin_unlock(&ch->lock);

	वापस 0;
पूर्ण

व्योम wcn36xx_dxe_rx_frame(काष्ठा wcn36xx *wcn)
अणु
	पूर्णांक पूर्णांक_src;

	wcn36xx_dxe_पढ़ो_रेजिस्टर(wcn, WCN36XX_DXE_INT_SRC_RAW_REG, &पूर्णांक_src);

	/* RX_LOW_PRI */
	अगर (पूर्णांक_src & WCN36XX_DXE_INT_CH1_MASK)
		wcn36xx_rx_handle_packets(wcn, &wcn->dxe_rx_l_ch,
					  WCN36XX_DXE_CTRL_RX_L,
					  WCN36XX_DXE_INT_CH1_MASK,
					  WCN36XX_INT_MASK_CHAN_RX_L,
					  WCN36XX_DXE_CH_STATUS_REG_ADDR_RX_L);

	/* RX_HIGH_PRI */
	अगर (पूर्णांक_src & WCN36XX_DXE_INT_CH3_MASK)
		wcn36xx_rx_handle_packets(wcn, &wcn->dxe_rx_h_ch,
					  WCN36XX_DXE_CTRL_RX_H,
					  WCN36XX_DXE_INT_CH3_MASK,
					  WCN36XX_INT_MASK_CHAN_RX_H,
					  WCN36XX_DXE_CH_STATUS_REG_ADDR_RX_H);

	अगर (!पूर्णांक_src)
		wcn36xx_warn("No DXE interrupt pending\n");
पूर्ण

पूर्णांक wcn36xx_dxe_allocate_mem_pools(काष्ठा wcn36xx *wcn)
अणु
	माप_प्रकार s;
	व्योम *cpu_addr;

	/* Allocate BD headers क्रम MGMT frames */

	/* Where this come from ask QC */
	wcn->mgmt_mem_pool.chunk_size =	WCN36XX_BD_CHUNK_SIZE +
		16 - (WCN36XX_BD_CHUNK_SIZE % 8);

	s = wcn->mgmt_mem_pool.chunk_size * WCN36XX_DXE_CH_DESC_NUMB_TX_H;
	cpu_addr = dma_alloc_coherent(wcn->dev, s,
				      &wcn->mgmt_mem_pool.phy_addr,
				      GFP_KERNEL);
	अगर (!cpu_addr)
		जाओ out_err;

	wcn->mgmt_mem_pool.virt_addr = cpu_addr;

	/* Allocate BD headers क्रम DATA frames */

	/* Where this come from ask QC */
	wcn->data_mem_pool.chunk_size = WCN36XX_BD_CHUNK_SIZE +
		16 - (WCN36XX_BD_CHUNK_SIZE % 8);

	s = wcn->data_mem_pool.chunk_size * WCN36XX_DXE_CH_DESC_NUMB_TX_L;
	cpu_addr = dma_alloc_coherent(wcn->dev, s,
				      &wcn->data_mem_pool.phy_addr,
				      GFP_KERNEL);
	अगर (!cpu_addr)
		जाओ out_err;

	wcn->data_mem_pool.virt_addr = cpu_addr;

	वापस 0;

out_err:
	wcn36xx_dxe_मुक्त_mem_pools(wcn);
	wcn36xx_err("Failed to allocate BD mempool\n");
	वापस -ENOMEM;
पूर्ण

व्योम wcn36xx_dxe_मुक्त_mem_pools(काष्ठा wcn36xx *wcn)
अणु
	अगर (wcn->mgmt_mem_pool.virt_addr)
		dma_मुक्त_coherent(wcn->dev, wcn->mgmt_mem_pool.chunk_size *
				  WCN36XX_DXE_CH_DESC_NUMB_TX_H,
				  wcn->mgmt_mem_pool.virt_addr,
				  wcn->mgmt_mem_pool.phy_addr);

	अगर (wcn->data_mem_pool.virt_addr) अणु
		dma_मुक्त_coherent(wcn->dev, wcn->data_mem_pool.chunk_size *
				  WCN36XX_DXE_CH_DESC_NUMB_TX_L,
				  wcn->data_mem_pool.virt_addr,
				  wcn->data_mem_pool.phy_addr);
	पूर्ण
पूर्ण

पूर्णांक wcn36xx_dxe_tx_frame(काष्ठा wcn36xx *wcn,
			 काष्ठा wcn36xx_vअगर *vअगर_priv,
			 काष्ठा wcn36xx_tx_bd *bd,
			 काष्ठा sk_buff *skb,
			 bool is_low)
अणु
	काष्ठा wcn36xx_dxe_desc *desc_bd, *desc_skb;
	काष्ठा wcn36xx_dxe_ctl *ctl_bd, *ctl_skb;
	काष्ठा wcn36xx_dxe_ch *ch = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ch = is_low ? &wcn->dxe_tx_l_ch : &wcn->dxe_tx_h_ch;

	spin_lock_irqsave(&ch->lock, flags);
	ctl_bd = ch->head_blk_ctl;
	ctl_skb = ctl_bd->next;

	/*
	 * If skb is not null that means that we reached the tail of the ring
	 * hence ring is full. Stop queues to let mac80211 back off until ring
	 * has an empty slot again.
	 */
	अगर (शून्य != ctl_skb->skb) अणु
		ieee80211_stop_queues(wcn->hw);
		wcn->queues_stopped = true;
		spin_unlock_irqrestore(&ch->lock, flags);
		वापस -EBUSY;
	पूर्ण

	अगर (unlikely(ctl_skb->bd_cpu_addr)) अणु
		wcn36xx_err("bd_cpu_addr cannot be NULL for skb DXE\n");
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	desc_bd = ctl_bd->desc;
	desc_skb = ctl_skb->desc;

	ctl_bd->skb = शून्य;

	/* ग_लिखो buffer descriptor */
	स_नकल(ctl_bd->bd_cpu_addr, bd, माप(*bd));

	/* Set source address of the BD we send */
	desc_bd->src_addr_l = ctl_bd->bd_phy_addr;
	desc_bd->dst_addr_l = ch->dxe_wq;
	desc_bd->fr_len = माप(काष्ठा wcn36xx_tx_bd);

	wcn36xx_dbg(WCN36XX_DBG_DXE, "DXE TX\n");

	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP, "DESC1 >>> ",
			 (अक्षर *)desc_bd, माप(*desc_bd));
	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP,
			 "BD   >>> ", (अक्षर *)ctl_bd->bd_cpu_addr,
			 माप(काष्ठा wcn36xx_tx_bd));

	desc_skb->src_addr_l = dma_map_single(wcn->dev,
					      skb->data,
					      skb->len,
					      DMA_TO_DEVICE);
	अगर (dma_mapping_error(wcn->dev, desc_skb->src_addr_l)) अणु
		dev_err(wcn->dev, "unable to DMA map src_addr_l\n");
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	ctl_skb->skb = skb;
	desc_skb->dst_addr_l = ch->dxe_wq;
	desc_skb->fr_len = ctl_skb->skb->len;

	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP, "DESC2 >>> ",
			 (अक्षर *)desc_skb, माप(*desc_skb));
	wcn36xx_dbg_dump(WCN36XX_DBG_DXE_DUMP, "SKB   >>> ",
			 (अक्षर *)ctl_skb->skb->data, ctl_skb->skb->len);

	/* Move the head of the ring to the next empty descriptor */
	 ch->head_blk_ctl = ctl_skb->next;

	/* Commit all previous ग_लिखोs and set descriptors to VALID */
	wmb();
	desc_skb->ctrl = ch->ctrl_skb;
	wmb();
	desc_bd->ctrl = ch->ctrl_bd;

	/*
	 * When connected and trying to send data frame chip can be in sleep
	 * mode and writing to the रेजिस्टर will not wake up the chip. Instead
	 * notअगरy chip about new frame through SMSM bus.
	 */
	अगर (is_low &&  vअगर_priv->pw_state == WCN36XX_BMPS) अणु
		qcom_smem_state_update_bits(wcn->tx_rings_empty_state,
					    WCN36XX_SMSM_WLAN_TX_ENABLE,
					    WCN36XX_SMSM_WLAN_TX_ENABLE);
	पूर्ण अन्यथा अणु
		/* indicate End Of Packet and generate पूर्णांकerrupt on descriptor
		 * करोne.
		 */
		wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
			ch->reg_ctrl, ch->def_ctrl);
	पूर्ण

	ret = 0;
unlock:
	spin_unlock_irqrestore(&ch->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_dxe_init(काष्ठा wcn36xx *wcn)
अणु
	पूर्णांक reg_data = 0, ret;

	reg_data = WCN36XX_DXE_REG_RESET;
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn, WCN36XX_DXE_REG_CSR_RESET, reg_data);

	/* Select channels क्रम rx avail and xfer करोne पूर्णांकerrupts... */
	reg_data = (WCN36XX_DXE_INT_CH3_MASK | WCN36XX_DXE_INT_CH1_MASK) << 16 |
		    WCN36XX_DXE_INT_CH0_MASK | WCN36XX_DXE_INT_CH4_MASK;
	अगर (wcn->is_pronto)
		wcn36xx_ccu_ग_लिखो_रेजिस्टर(wcn, WCN36XX_CCU_DXE_INT_SELECT_PRONTO, reg_data);
	अन्यथा
		wcn36xx_ccu_ग_लिखो_रेजिस्टर(wcn, WCN36XX_CCU_DXE_INT_SELECT_RIVA, reg_data);

	/***************************************/
	/* Init descriptors क्रम TX LOW channel */
	/***************************************/
	ret = wcn36xx_dxe_init_descs(wcn->dev, &wcn->dxe_tx_l_ch);
	अगर (ret) अणु
		dev_err(wcn->dev, "Error allocating descriptor\n");
		वापस ret;
	पूर्ण
	wcn36xx_dxe_init_tx_bd(&wcn->dxe_tx_l_ch, &wcn->data_mem_pool);

	/* Write channel head to a NEXT रेजिस्टर */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDR_TX_L,
		wcn->dxe_tx_l_ch.head_blk_ctl->desc_phy_addr);

	/* Program DMA destination addr क्रम TX LOW */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
		WCN36XX_DXE_CH_DEST_ADDR_TX_L,
		WCN36XX_DXE_WQ_TX_L);

	wcn36xx_dxe_पढ़ो_रेजिस्टर(wcn, WCN36XX_DXE_REG_CH_EN, &reg_data);
	wcn36xx_dxe_enable_ch_पूर्णांक(wcn, WCN36XX_INT_MASK_CHAN_TX_L);

	/***************************************/
	/* Init descriptors क्रम TX HIGH channel */
	/***************************************/
	ret = wcn36xx_dxe_init_descs(wcn->dev, &wcn->dxe_tx_h_ch);
	अगर (ret) अणु
		dev_err(wcn->dev, "Error allocating descriptor\n");
		जाओ out_err_txh_ch;
	पूर्ण

	wcn36xx_dxe_init_tx_bd(&wcn->dxe_tx_h_ch, &wcn->mgmt_mem_pool);

	/* Write channel head to a NEXT रेजिस्टर */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDR_TX_H,
		wcn->dxe_tx_h_ch.head_blk_ctl->desc_phy_addr);

	/* Program DMA destination addr क्रम TX HIGH */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
		WCN36XX_DXE_CH_DEST_ADDR_TX_H,
		WCN36XX_DXE_WQ_TX_H);

	wcn36xx_dxe_पढ़ो_रेजिस्टर(wcn, WCN36XX_DXE_REG_CH_EN, &reg_data);

	/* Enable channel पूर्णांकerrupts */
	wcn36xx_dxe_enable_ch_पूर्णांक(wcn, WCN36XX_INT_MASK_CHAN_TX_H);

	/***************************************/
	/* Init descriptors क्रम RX LOW channel */
	/***************************************/
	ret = wcn36xx_dxe_init_descs(wcn->dev, &wcn->dxe_rx_l_ch);
	अगर (ret) अणु
		dev_err(wcn->dev, "Error allocating descriptor\n");
		जाओ out_err_rxl_ch;
	पूर्ण


	/* For RX we need to pपुनः_स्मृतिated buffers */
	wcn36xx_dxe_ch_alloc_skb(wcn, &wcn->dxe_rx_l_ch);

	/* Write channel head to a NEXT रेजिस्टर */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDR_RX_L,
		wcn->dxe_rx_l_ch.head_blk_ctl->desc_phy_addr);

	/* Write DMA source address */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
		WCN36XX_DXE_CH_SRC_ADDR_RX_L,
		WCN36XX_DXE_WQ_RX_L);

	/* Program pपुनः_स्मृतिated destination address */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
		WCN36XX_DXE_CH_DEST_ADDR_RX_L,
		wcn->dxe_rx_l_ch.head_blk_ctl->desc->phy_next_l);

	/* Enable शेष control रेजिस्टरs */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
		WCN36XX_DXE_REG_CTL_RX_L,
		WCN36XX_DXE_CH_DEFAULT_CTL_RX_L);

	/* Enable channel पूर्णांकerrupts */
	wcn36xx_dxe_enable_ch_पूर्णांक(wcn, WCN36XX_INT_MASK_CHAN_RX_L);

	/***************************************/
	/* Init descriptors क्रम RX HIGH channel */
	/***************************************/
	ret = wcn36xx_dxe_init_descs(wcn->dev, &wcn->dxe_rx_h_ch);
	अगर (ret) अणु
		dev_err(wcn->dev, "Error allocating descriptor\n");
		जाओ out_err_rxh_ch;
	पूर्ण

	/* For RX we need to prealocat buffers */
	wcn36xx_dxe_ch_alloc_skb(wcn, &wcn->dxe_rx_h_ch);

	/* Write chanel head to a NEXT रेजिस्टर */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn, WCN36XX_DXE_CH_NEXT_DESC_ADDR_RX_H,
		wcn->dxe_rx_h_ch.head_blk_ctl->desc_phy_addr);

	/* Write DMA source address */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
		WCN36XX_DXE_CH_SRC_ADDR_RX_H,
		WCN36XX_DXE_WQ_RX_H);

	/* Program pपुनः_स्मृतिated destination address */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
		WCN36XX_DXE_CH_DEST_ADDR_RX_H,
		 wcn->dxe_rx_h_ch.head_blk_ctl->desc->phy_next_l);

	/* Enable शेष control रेजिस्टरs */
	wcn36xx_dxe_ग_लिखो_रेजिस्टर(wcn,
		WCN36XX_DXE_REG_CTL_RX_H,
		WCN36XX_DXE_CH_DEFAULT_CTL_RX_H);

	/* Enable channel पूर्णांकerrupts */
	wcn36xx_dxe_enable_ch_पूर्णांक(wcn, WCN36XX_INT_MASK_CHAN_RX_H);

	ret = wcn36xx_dxe_request_irqs(wcn);
	अगर (ret < 0)
		जाओ out_err_irq;

	समयr_setup(&wcn->tx_ack_समयr, wcn36xx_dxe_tx_समयr, 0);

	वापस 0;

out_err_irq:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_rx_h_ch);
out_err_rxh_ch:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_rx_l_ch);
out_err_rxl_ch:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_tx_h_ch);
out_err_txh_ch:
	wcn36xx_dxe_deinit_descs(wcn->dev, &wcn->dxe_tx_l_ch);

	वापस ret;
पूर्ण

व्योम wcn36xx_dxe_deinit(काष्ठा wcn36xx *wcn)
अणु
	मुक्त_irq(wcn->tx_irq, wcn);
	मुक्त_irq(wcn->rx_irq, wcn);
	del_समयr(&wcn->tx_ack_समयr);

	अगर (wcn->tx_ack_skb) अणु
		ieee80211_tx_status_irqsafe(wcn->hw, wcn->tx_ack_skb);
		wcn->tx_ack_skb = शून्य;
	पूर्ण

	wcn36xx_dxe_ch_मुक्त_skbs(wcn, &wcn->dxe_rx_l_ch);
	wcn36xx_dxe_ch_मुक्त_skbs(wcn, &wcn->dxe_rx_h_ch);
पूर्ण
