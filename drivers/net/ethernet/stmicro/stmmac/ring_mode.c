<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  Specialised functions क्रम managing Ring mode

  Copyright(C) 2011  STMicroelectronics Ltd

  It defines all the functions used to handle the normal/enhanced
  descriptors in हाल of the DMA is configured to work in chained or
  in ring mode.


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश "stmmac.h"

अटल पूर्णांक jumbo_frm(व्योम *p, काष्ठा sk_buff *skb, पूर्णांक csum)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = (काष्ठा sपंचांगmac_tx_queue *)p;
	अचिन्हित पूर्णांक nopaged_len = skb_headlen(skb);
	काष्ठा sपंचांगmac_priv *priv = tx_q->priv_data;
	अचिन्हित पूर्णांक entry = tx_q->cur_tx;
	अचिन्हित पूर्णांक bmax, len, des2;
	काष्ठा dma_desc *desc;

	अगर (priv->extend_desc)
		desc = (काष्ठा dma_desc *)(tx_q->dma_etx + entry);
	अन्यथा
		desc = tx_q->dma_tx + entry;

	अगर (priv->plat->enh_desc)
		bmax = BUF_SIZE_8KiB;
	अन्यथा
		bmax = BUF_SIZE_2KiB;

	len = nopaged_len - bmax;

	अगर (nopaged_len > BUF_SIZE_8KiB) अणु

		des2 = dma_map_single(priv->device, skb->data, bmax,
				      DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		अगर (dma_mapping_error(priv->device, des2))
			वापस -1;

		tx_q->tx_skbuff_dma[entry].buf = des2;
		tx_q->tx_skbuff_dma[entry].len = bmax;
		tx_q->tx_skbuff_dma[entry].is_jumbo = true;

		desc->des3 = cpu_to_le32(des2 + BUF_SIZE_4KiB);
		sपंचांगmac_prepare_tx_desc(priv, desc, 1, bmax, csum,
				STMMAC_RING_MODE, 0, false, skb->len);
		tx_q->tx_skbuff[entry] = शून्य;
		entry = STMMAC_GET_ENTRY(entry, priv->dma_tx_size);

		अगर (priv->extend_desc)
			desc = (काष्ठा dma_desc *)(tx_q->dma_etx + entry);
		अन्यथा
			desc = tx_q->dma_tx + entry;

		des2 = dma_map_single(priv->device, skb->data + bmax, len,
				      DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		अगर (dma_mapping_error(priv->device, des2))
			वापस -1;
		tx_q->tx_skbuff_dma[entry].buf = des2;
		tx_q->tx_skbuff_dma[entry].len = len;
		tx_q->tx_skbuff_dma[entry].is_jumbo = true;

		desc->des3 = cpu_to_le32(des2 + BUF_SIZE_4KiB);
		sपंचांगmac_prepare_tx_desc(priv, desc, 0, len, csum,
				STMMAC_RING_MODE, 1, !skb_is_nonlinear(skb),
				skb->len);
	पूर्ण अन्यथा अणु
		des2 = dma_map_single(priv->device, skb->data,
				      nopaged_len, DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		अगर (dma_mapping_error(priv->device, des2))
			वापस -1;
		tx_q->tx_skbuff_dma[entry].buf = des2;
		tx_q->tx_skbuff_dma[entry].len = nopaged_len;
		tx_q->tx_skbuff_dma[entry].is_jumbo = true;
		desc->des3 = cpu_to_le32(des2 + BUF_SIZE_4KiB);
		sपंचांगmac_prepare_tx_desc(priv, desc, 1, nopaged_len, csum,
				STMMAC_RING_MODE, 0, !skb_is_nonlinear(skb),
				skb->len);
	पूर्ण

	tx_q->cur_tx = entry;

	वापस entry;
पूर्ण

अटल अचिन्हित पूर्णांक is_jumbo_frm(पूर्णांक len, पूर्णांक enh_desc)
अणु
	अचिन्हित पूर्णांक ret = 0;

	अगर (len >= BUF_SIZE_4KiB)
		ret = 1;

	वापस ret;
पूर्ण

अटल व्योम refill_desc3(व्योम *priv_ptr, काष्ठा dma_desc *p)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = priv_ptr;
	काष्ठा sपंचांगmac_priv *priv = rx_q->priv_data;

	/* Fill DES3 in हाल of RING mode */
	अगर (priv->dma_buf_sz == BUF_SIZE_16KiB)
		p->des3 = cpu_to_le32(le32_to_cpu(p->des2) + BUF_SIZE_8KiB);
पूर्ण

/* In ring mode we need to fill the desc3 because it is used as buffer */
अटल व्योम init_desc3(काष्ठा dma_desc *p)
अणु
	p->des3 = cpu_to_le32(le32_to_cpu(p->des2) + BUF_SIZE_8KiB);
पूर्ण

अटल व्योम clean_desc3(व्योम *priv_ptr, काष्ठा dma_desc *p)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = (काष्ठा sपंचांगmac_tx_queue *)priv_ptr;
	काष्ठा sपंचांगmac_priv *priv = tx_q->priv_data;
	अचिन्हित पूर्णांक entry = tx_q->dirty_tx;

	/* des3 is only used क्रम jumbo frames tx or समय stamping */
	अगर (unlikely(tx_q->tx_skbuff_dma[entry].is_jumbo ||
		     (tx_q->tx_skbuff_dma[entry].last_segment &&
		      !priv->extend_desc && priv->hwts_tx_en)))
		p->des3 = 0;
पूर्ण

अटल पूर्णांक set_16kib_bfsize(पूर्णांक mtu)
अणु
	पूर्णांक ret = 0;
	अगर (unlikely(mtu > BUF_SIZE_8KiB))
		ret = BUF_SIZE_16KiB;
	वापस ret;
पूर्ण

स्थिर काष्ठा sपंचांगmac_mode_ops ring_mode_ops = अणु
	.is_jumbo_frm = is_jumbo_frm,
	.jumbo_frm = jumbo_frm,
	.refill_desc3 = refill_desc3,
	.init_desc3 = init_desc3,
	.clean_desc3 = clean_desc3,
	.set_16kib_bfsize = set_16kib_bfsize,
पूर्ण;
