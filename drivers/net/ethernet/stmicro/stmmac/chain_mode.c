<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  Specialised functions क्रम managing Chained mode

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
	अचिन्हित पूर्णांक bmax, des2;
	अचिन्हित पूर्णांक i = 1, len;
	काष्ठा dma_desc *desc;

	desc = tx_q->dma_tx + entry;

	अगर (priv->plat->enh_desc)
		bmax = BUF_SIZE_8KiB;
	अन्यथा
		bmax = BUF_SIZE_2KiB;

	len = nopaged_len - bmax;

	des2 = dma_map_single(priv->device, skb->data,
			      bmax, DMA_TO_DEVICE);
	desc->des2 = cpu_to_le32(des2);
	अगर (dma_mapping_error(priv->device, des2))
		वापस -1;
	tx_q->tx_skbuff_dma[entry].buf = des2;
	tx_q->tx_skbuff_dma[entry].len = bmax;
	/* करो not बंद the descriptor and करो not set own bit */
	sपंचांगmac_prepare_tx_desc(priv, desc, 1, bmax, csum, STMMAC_CHAIN_MODE,
			0, false, skb->len);

	जबतक (len != 0) अणु
		tx_q->tx_skbuff[entry] = शून्य;
		entry = STMMAC_GET_ENTRY(entry, priv->dma_tx_size);
		desc = tx_q->dma_tx + entry;

		अगर (len > bmax) अणु
			des2 = dma_map_single(priv->device,
					      (skb->data + bmax * i),
					      bmax, DMA_TO_DEVICE);
			desc->des2 = cpu_to_le32(des2);
			अगर (dma_mapping_error(priv->device, des2))
				वापस -1;
			tx_q->tx_skbuff_dma[entry].buf = des2;
			tx_q->tx_skbuff_dma[entry].len = bmax;
			sपंचांगmac_prepare_tx_desc(priv, desc, 0, bmax, csum,
					STMMAC_CHAIN_MODE, 1, false, skb->len);
			len -= bmax;
			i++;
		पूर्ण अन्यथा अणु
			des2 = dma_map_single(priv->device,
					      (skb->data + bmax * i), len,
					      DMA_TO_DEVICE);
			desc->des2 = cpu_to_le32(des2);
			अगर (dma_mapping_error(priv->device, des2))
				वापस -1;
			tx_q->tx_skbuff_dma[entry].buf = des2;
			tx_q->tx_skbuff_dma[entry].len = len;
			/* last descriptor can be set now */
			sपंचांगmac_prepare_tx_desc(priv, desc, 0, len, csum,
					STMMAC_CHAIN_MODE, 1, true, skb->len);
			len = 0;
		पूर्ण
	पूर्ण

	tx_q->cur_tx = entry;

	वापस entry;
पूर्ण

अटल अचिन्हित पूर्णांक is_jumbo_frm(पूर्णांक len, पूर्णांक enh_desc)
अणु
	अचिन्हित पूर्णांक ret = 0;

	अगर ((enh_desc && (len > BUF_SIZE_8KiB)) ||
	    (!enh_desc && (len > BUF_SIZE_2KiB))) अणु
		ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम init_dma_chain(व्योम *des, dma_addr_t phy_addr,
				  अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक extend_desc)
अणु
	/*
	 * In chained mode the des3 poपूर्णांकs to the next element in the ring.
	 * The latest element has to poपूर्णांक to the head.
	 */
	पूर्णांक i;
	dma_addr_t dma_phy = phy_addr;

	अगर (extend_desc) अणु
		काष्ठा dma_extended_desc *p = (काष्ठा dma_extended_desc *)des;
		क्रम (i = 0; i < (size - 1); i++) अणु
			dma_phy += माप(काष्ठा dma_extended_desc);
			p->basic.des3 = cpu_to_le32((अचिन्हित पूर्णांक)dma_phy);
			p++;
		पूर्ण
		p->basic.des3 = cpu_to_le32((अचिन्हित पूर्णांक)phy_addr);

	पूर्ण अन्यथा अणु
		काष्ठा dma_desc *p = (काष्ठा dma_desc *)des;
		क्रम (i = 0; i < (size - 1); i++) अणु
			dma_phy += माप(काष्ठा dma_desc);
			p->des3 = cpu_to_le32((अचिन्हित पूर्णांक)dma_phy);
			p++;
		पूर्ण
		p->des3 = cpu_to_le32((अचिन्हित पूर्णांक)phy_addr);
	पूर्ण
पूर्ण

अटल व्योम refill_desc3(व्योम *priv_ptr, काष्ठा dma_desc *p)
अणु
	काष्ठा sपंचांगmac_rx_queue *rx_q = (काष्ठा sपंचांगmac_rx_queue *)priv_ptr;
	काष्ठा sपंचांगmac_priv *priv = rx_q->priv_data;

	अगर (priv->hwts_rx_en && !priv->extend_desc)
		/* NOTE: Device will overग_लिखो des3 with बारtamp value अगर
		 * 1588-2002 समय stamping is enabled, hence reinitialize it
		 * to keep explicit chaining in the descriptor.
		 */
		p->des3 = cpu_to_le32((अचिन्हित पूर्णांक)(rx_q->dma_rx_phy +
				      (((rx_q->dirty_rx) + 1) %
				       priv->dma_rx_size) *
				      माप(काष्ठा dma_desc)));
पूर्ण

अटल व्योम clean_desc3(व्योम *priv_ptr, काष्ठा dma_desc *p)
अणु
	काष्ठा sपंचांगmac_tx_queue *tx_q = (काष्ठा sपंचांगmac_tx_queue *)priv_ptr;
	काष्ठा sपंचांगmac_priv *priv = tx_q->priv_data;
	अचिन्हित पूर्णांक entry = tx_q->dirty_tx;

	अगर (tx_q->tx_skbuff_dma[entry].last_segment && !priv->extend_desc &&
	    priv->hwts_tx_en)
		/* NOTE: Device will overग_लिखो des3 with बारtamp value अगर
		 * 1588-2002 समय stamping is enabled, hence reinitialize it
		 * to keep explicit chaining in the descriptor.
		 */
		p->des3 = cpu_to_le32((अचिन्हित पूर्णांक)((tx_q->dma_tx_phy +
				      ((tx_q->dirty_tx + 1) %
				       priv->dma_tx_size))
				      * माप(काष्ठा dma_desc)));
पूर्ण

स्थिर काष्ठा sपंचांगmac_mode_ops chain_mode_ops = अणु
	.init = init_dma_chain,
	.is_jumbo_frm = is_jumbo_frm,
	.jumbo_frm = jumbo_frm,
	.refill_desc3 = refill_desc3,
	.clean_desc3 = clean_desc3,
पूर्ण;
