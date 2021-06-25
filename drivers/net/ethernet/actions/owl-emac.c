<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Actions Semi Owl SoCs Ethernet MAC driver
 *
 * Copyright (c) 2012 Actions Semi Inc.
 * Copyright (c) 2021 Cristian Ciocaltea <cristian.ciocaltea@gmail.com>
 */

#समावेश <linux/circ_buf.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/reset.h>

#समावेश "owl-emac.h"

#घोषणा OWL_EMAC_DEFAULT_MSG_ENABLE	(NETIF_MSG_DRV | \
					 NETIF_MSG_PROBE | \
					 NETIF_MSG_LINK)

अटल u32 owl_emac_reg_पढ़ो(काष्ठा owl_emac_priv *priv, u32 reg)
अणु
	वापस पढ़ोl(priv->base + reg);
पूर्ण

अटल व्योम owl_emac_reg_ग_लिखो(काष्ठा owl_emac_priv *priv, u32 reg, u32 data)
अणु
	ग_लिखोl(data, priv->base + reg);
पूर्ण

अटल u32 owl_emac_reg_update(काष्ठा owl_emac_priv *priv,
			       u32 reg, u32 mask, u32 val)
अणु
	u32 data, old_val;

	data = owl_emac_reg_पढ़ो(priv, reg);
	old_val = data & mask;

	data &= ~mask;
	data |= val & mask;

	owl_emac_reg_ग_लिखो(priv, reg, data);

	वापस old_val;
पूर्ण

अटल व्योम owl_emac_reg_set(काष्ठा owl_emac_priv *priv, u32 reg, u32 bits)
अणु
	owl_emac_reg_update(priv, reg, bits, bits);
पूर्ण

अटल व्योम owl_emac_reg_clear(काष्ठा owl_emac_priv *priv, u32 reg, u32 bits)
अणु
	owl_emac_reg_update(priv, reg, bits, 0);
पूर्ण

अटल काष्ठा device *owl_emac_get_dev(काष्ठा owl_emac_priv *priv)
अणु
	वापस priv->netdev->dev.parent;
पूर्ण

अटल व्योम owl_emac_irq_enable(काष्ठा owl_emac_priv *priv)
अणु
	/* Enable all पूर्णांकerrupts except TU.
	 *
	 * Note the NIE and AIE bits shall also be set in order to actually
	 * enable the selected पूर्णांकerrupts.
	 */
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR7,
			   OWL_EMAC_BIT_MAC_CSR7_NIE |
			   OWL_EMAC_BIT_MAC_CSR7_AIE |
			   OWL_EMAC_BIT_MAC_CSR7_ALL_NOT_TUE);
पूर्ण

अटल व्योम owl_emac_irq_disable(काष्ठा owl_emac_priv *priv)
अणु
	/* Disable all पूर्णांकerrupts.
	 *
	 * WARNING: Unset only the NIE and AIE bits in CSR7 to workaround an
	 * unexpected side effect (MAC hardware bug?!) where some bits in the
	 * status रेजिस्टर (CSR5) are cleared स्वतःmatically beक्रमe being able
	 * to पढ़ो them via owl_emac_irq_clear().
	 */
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR7,
			   OWL_EMAC_BIT_MAC_CSR7_ALL_NOT_TUE);
पूर्ण

अटल u32 owl_emac_irq_status(काष्ठा owl_emac_priv *priv)
अणु
	वापस owl_emac_reg_पढ़ो(priv, OWL_EMAC_REG_MAC_CSR5);
पूर्ण

अटल u32 owl_emac_irq_clear(काष्ठा owl_emac_priv *priv)
अणु
	u32 val = owl_emac_irq_status(priv);

	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR5, val);

	वापस val;
पूर्ण

अटल dma_addr_t owl_emac_dma_map_rx(काष्ठा owl_emac_priv *priv,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dev = owl_emac_get_dev(priv);

	/* Buffer poपूर्णांकer क्रम the RX DMA descriptor must be word aligned. */
	वापस dma_map_single(dev, skb_tail_poपूर्णांकer(skb),
			      skb_tailroom(skb), DMA_FROM_DEVICE);
पूर्ण

अटल व्योम owl_emac_dma_unmap_rx(काष्ठा owl_emac_priv *priv,
				  काष्ठा sk_buff *skb, dma_addr_t dma_addr)
अणु
	काष्ठा device *dev = owl_emac_get_dev(priv);

	dma_unmap_single(dev, dma_addr, skb_tailroom(skb), DMA_FROM_DEVICE);
पूर्ण

अटल dma_addr_t owl_emac_dma_map_tx(काष्ठा owl_emac_priv *priv,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dev = owl_emac_get_dev(priv);

	वापस dma_map_single(dev, skb->data, skb_headlen(skb), DMA_TO_DEVICE);
पूर्ण

अटल व्योम owl_emac_dma_unmap_tx(काष्ठा owl_emac_priv *priv,
				  काष्ठा sk_buff *skb, dma_addr_t dma_addr)
अणु
	काष्ठा device *dev = owl_emac_get_dev(priv);

	dma_unmap_single(dev, dma_addr, skb_headlen(skb), DMA_TO_DEVICE);
पूर्ण

अटल अचिन्हित पूर्णांक owl_emac_ring_num_unused(काष्ठा owl_emac_ring *ring)
अणु
	वापस CIRC_SPACE(ring->head, ring->tail, ring->size);
पूर्ण

अटल अचिन्हित पूर्णांक owl_emac_ring_get_next(काष्ठा owl_emac_ring *ring,
					   अचिन्हित पूर्णांक cur)
अणु
	वापस (cur + 1) & (ring->size - 1);
पूर्ण

अटल व्योम owl_emac_ring_push_head(काष्ठा owl_emac_ring *ring)
अणु
	ring->head = owl_emac_ring_get_next(ring, ring->head);
पूर्ण

अटल व्योम owl_emac_ring_pop_tail(काष्ठा owl_emac_ring *ring)
अणु
	ring->tail = owl_emac_ring_get_next(ring, ring->tail);
पूर्ण

अटल काष्ठा sk_buff *owl_emac_alloc_skb(काष्ठा net_device *netdev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक offset;

	skb = netdev_alloc_skb(netdev, OWL_EMAC_RX_FRAME_MAX_LEN +
			       OWL_EMAC_SKB_RESERVE);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* Ensure 4 bytes DMA alignment. */
	offset = ((uपूर्णांकptr_t)skb->data) & (OWL_EMAC_SKB_ALIGN - 1);
	अगर (unlikely(offset))
		skb_reserve(skb, OWL_EMAC_SKB_ALIGN - offset);

	वापस skb;
पूर्ण

अटल पूर्णांक owl_emac_ring_prepare_rx(काष्ठा owl_emac_priv *priv)
अणु
	काष्ठा owl_emac_ring *ring = &priv->rx_ring;
	काष्ठा device *dev = owl_emac_get_dev(priv);
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा owl_emac_ring_desc *desc;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	पूर्णांक i;

	क्रम (i = 0; i < ring->size; i++) अणु
		skb = owl_emac_alloc_skb(netdev);
		अगर (!skb)
			वापस -ENOMEM;

		dma_addr = owl_emac_dma_map_rx(priv, skb);
		अगर (dma_mapping_error(dev, dma_addr)) अणु
			dev_kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण

		desc = &ring->descs[i];
		desc->status = OWL_EMAC_BIT_RDES0_OWN;
		desc->control = skb_tailroom(skb) & OWL_EMAC_MSK_RDES1_RBS1;
		desc->buf_addr = dma_addr;
		desc->reserved = 0;

		ring->skbs[i] = skb;
		ring->skbs_dma[i] = dma_addr;
	पूर्ण

	desc->control |= OWL_EMAC_BIT_RDES1_RER;

	ring->head = 0;
	ring->tail = 0;

	वापस 0;
पूर्ण

अटल व्योम owl_emac_ring_prepare_tx(काष्ठा owl_emac_priv *priv)
अणु
	काष्ठा owl_emac_ring *ring = &priv->tx_ring;
	काष्ठा owl_emac_ring_desc *desc;
	पूर्णांक i;

	क्रम (i = 0; i < ring->size; i++) अणु
		desc = &ring->descs[i];

		desc->status = 0;
		desc->control = OWL_EMAC_BIT_TDES1_IC;
		desc->buf_addr = 0;
		desc->reserved = 0;
	पूर्ण

	desc->control |= OWL_EMAC_BIT_TDES1_TER;

	स_रखो(ring->skbs_dma, 0, माप(dma_addr_t) * ring->size);

	ring->head = 0;
	ring->tail = 0;
पूर्ण

अटल व्योम owl_emac_ring_unprepare_rx(काष्ठा owl_emac_priv *priv)
अणु
	काष्ठा owl_emac_ring *ring = &priv->rx_ring;
	पूर्णांक i;

	क्रम (i = 0; i < ring->size; i++) अणु
		ring->descs[i].status = 0;

		अगर (!ring->skbs_dma[i])
			जारी;

		owl_emac_dma_unmap_rx(priv, ring->skbs[i], ring->skbs_dma[i]);
		ring->skbs_dma[i] = 0;

		dev_kमुक्त_skb(ring->skbs[i]);
		ring->skbs[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम owl_emac_ring_unprepare_tx(काष्ठा owl_emac_priv *priv)
अणु
	काष्ठा owl_emac_ring *ring = &priv->tx_ring;
	पूर्णांक i;

	क्रम (i = 0; i < ring->size; i++) अणु
		ring->descs[i].status = 0;

		अगर (!ring->skbs_dma[i])
			जारी;

		owl_emac_dma_unmap_tx(priv, ring->skbs[i], ring->skbs_dma[i]);
		ring->skbs_dma[i] = 0;

		dev_kमुक्त_skb(ring->skbs[i]);
		ring->skbs[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक owl_emac_ring_alloc(काष्ठा device *dev, काष्ठा owl_emac_ring *ring,
			       अचिन्हित पूर्णांक size)
अणु
	ring->descs = dmam_alloc_coherent(dev,
					  माप(काष्ठा owl_emac_ring_desc) * size,
					  &ring->descs_dma, GFP_KERNEL);
	अगर (!ring->descs)
		वापस -ENOMEM;

	ring->skbs = devm_kसुस्मृति(dev, size, माप(काष्ठा sk_buff *),
				  GFP_KERNEL);
	अगर (!ring->skbs)
		वापस -ENOMEM;

	ring->skbs_dma = devm_kसुस्मृति(dev, size, माप(dma_addr_t),
				      GFP_KERNEL);
	अगर (!ring->skbs_dma)
		वापस -ENOMEM;

	ring->size = size;

	वापस 0;
पूर्ण

अटल व्योम owl_emac_dma_cmd_resume_rx(काष्ठा owl_emac_priv *priv)
अणु
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR2,
			   OWL_EMAC_VAL_MAC_CSR2_RPD);
पूर्ण

अटल व्योम owl_emac_dma_cmd_resume_tx(काष्ठा owl_emac_priv *priv)
अणु
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR1,
			   OWL_EMAC_VAL_MAC_CSR1_TPD);
पूर्ण

अटल u32 owl_emac_dma_cmd_set_tx(काष्ठा owl_emac_priv *priv, u32 status)
अणु
	वापस owl_emac_reg_update(priv, OWL_EMAC_REG_MAC_CSR6,
				   OWL_EMAC_BIT_MAC_CSR6_ST, status);
पूर्ण

अटल u32 owl_emac_dma_cmd_start_tx(काष्ठा owl_emac_priv *priv)
अणु
	वापस owl_emac_dma_cmd_set_tx(priv, ~0);
पूर्ण

अटल u32 owl_emac_dma_cmd_set(काष्ठा owl_emac_priv *priv, u32 status)
अणु
	वापस owl_emac_reg_update(priv, OWL_EMAC_REG_MAC_CSR6,
				   OWL_EMAC_MSK_MAC_CSR6_STSR, status);
पूर्ण

अटल u32 owl_emac_dma_cmd_start(काष्ठा owl_emac_priv *priv)
अणु
	वापस owl_emac_dma_cmd_set(priv, ~0);
पूर्ण

अटल u32 owl_emac_dma_cmd_stop(काष्ठा owl_emac_priv *priv)
अणु
	वापस owl_emac_dma_cmd_set(priv, 0);
पूर्ण

अटल व्योम owl_emac_set_hw_mac_addr(काष्ठा net_device *netdev)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);
	u8 *mac_addr = netdev->dev_addr;
	u32 addr_high, addr_low;

	addr_high = mac_addr[0] << 8 | mac_addr[1];
	addr_low = mac_addr[2] << 24 | mac_addr[3] << 16 |
		   mac_addr[4] << 8 | mac_addr[5];

	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR17, addr_high);
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR16, addr_low);
पूर्ण

अटल व्योम owl_emac_update_link_state(काष्ठा owl_emac_priv *priv)
अणु
	u32 val, status;

	अगर (priv->छोड़ो) अणु
		val = OWL_EMAC_BIT_MAC_CSR20_FCE | OWL_EMAC_BIT_MAC_CSR20_TUE;
		val |= OWL_EMAC_BIT_MAC_CSR20_TPE | OWL_EMAC_BIT_MAC_CSR20_RPE;
		val |= OWL_EMAC_BIT_MAC_CSR20_BPE;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	/* Update flow control. */
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR20, val);

	val = (priv->speed == SPEED_100) ? OWL_EMAC_VAL_MAC_CSR6_SPEED_100M :
					   OWL_EMAC_VAL_MAC_CSR6_SPEED_10M;
	val <<= OWL_EMAC_OFF_MAC_CSR6_SPEED;

	अगर (priv->duplex == DUPLEX_FULL)
		val |= OWL_EMAC_BIT_MAC_CSR6_FD;

	spin_lock_bh(&priv->lock);

	/* Temporarily stop DMA TX & RX. */
	status = owl_emac_dma_cmd_stop(priv);

	/* Update operation modes. */
	owl_emac_reg_update(priv, OWL_EMAC_REG_MAC_CSR6,
			    OWL_EMAC_MSK_MAC_CSR6_SPEED |
			    OWL_EMAC_BIT_MAC_CSR6_FD, val);

	/* Restore DMA TX & RX status. */
	owl_emac_dma_cmd_set(priv, status);

	spin_unlock_bh(&priv->lock);
पूर्ण

अटल व्योम owl_emac_adjust_link(काष्ठा net_device *netdev)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);
	काष्ठा phy_device *phydev = netdev->phydev;
	bool state_changed = false;

	अगर (phydev->link) अणु
		अगर (!priv->link) अणु
			priv->link = phydev->link;
			state_changed = true;
		पूर्ण

		अगर (priv->speed != phydev->speed) अणु
			priv->speed = phydev->speed;
			state_changed = true;
		पूर्ण

		अगर (priv->duplex != phydev->duplex) अणु
			priv->duplex = phydev->duplex;
			state_changed = true;
		पूर्ण

		अगर (priv->छोड़ो != phydev->छोड़ो) अणु
			priv->छोड़ो = phydev->छोड़ो;
			state_changed = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->link) अणु
			priv->link = phydev->link;
			state_changed = true;
		पूर्ण
	पूर्ण

	अगर (state_changed) अणु
		अगर (phydev->link)
			owl_emac_update_link_state(priv);

		अगर (netअगर_msg_link(priv))
			phy_prपूर्णांक_status(phydev);
	पूर्ण
पूर्ण

अटल irqवापस_t owl_emac_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);

	अगर (netअगर_running(netdev)) अणु
		owl_emac_irq_disable(priv);
		napi_schedule(&priv->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम owl_emac_ether_addr_push(u8 **dst, स्थिर u8 *src)
अणु
	u32 *a = (u32 *)(*dst);
	स्थिर u16 *b = (स्थिर u16 *)src;

	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];

	*dst += 12;
पूर्ण

अटल व्योम
owl_emac_setup_frame_prepare(काष्ठा owl_emac_priv *priv, काष्ठा sk_buff *skb)
अणु
	स्थिर u8 bcast_addr[] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	स्थिर u8 *mac_addr = priv->netdev->dev_addr;
	u8 *frame;
	पूर्णांक i;

	skb_put(skb, OWL_EMAC_SETUP_FRAME_LEN);

	frame = skb->data;
	स_रखो(frame, 0, skb->len);

	owl_emac_ether_addr_push(&frame, mac_addr);
	owl_emac_ether_addr_push(&frame, bcast_addr);

	/* Fill multicast addresses. */
	WARN_ON(priv->mcaddr_list.count >= OWL_EMAC_MAX_MULTICAST_ADDRS);
	क्रम (i = 0; i < priv->mcaddr_list.count; i++) अणु
		mac_addr = priv->mcaddr_list.addrs[i];
		owl_emac_ether_addr_push(&frame, mac_addr);
	पूर्ण
पूर्ण

/* The setup frame is a special descriptor which is used to provide physical
 * addresses (i.e. mac, broadcast and multicast) to the MAC hardware क्रम
 * filtering purposes. To be recognized as a setup frame, the TDES1_SET bit
 * must be set in the TX descriptor control field.
 */
अटल पूर्णांक owl_emac_setup_frame_xmit(काष्ठा owl_emac_priv *priv)
अणु
	काष्ठा owl_emac_ring *ring = &priv->tx_ring;
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा owl_emac_ring_desc *desc;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक tx_head;
	u32 status, control;
	dma_addr_t dma_addr;
	पूर्णांक ret;

	skb = owl_emac_alloc_skb(netdev);
	अगर (!skb)
		वापस -ENOMEM;

	owl_emac_setup_frame_prepare(priv, skb);

	dma_addr = owl_emac_dma_map_tx(priv, skb);
	अगर (dma_mapping_error(owl_emac_get_dev(priv), dma_addr)) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_skb;
	पूर्ण

	spin_lock_bh(&priv->lock);

	tx_head = ring->head;
	desc = &ring->descs[tx_head];

	status = READ_ONCE(desc->status);
	control = READ_ONCE(desc->control);
	dma_rmb(); /* Ensure data has been पढ़ो beक्रमe used. */

	अगर (unlikely(status & OWL_EMAC_BIT_TDES0_OWN) ||
	    !owl_emac_ring_num_unused(ring)) अणु
		spin_unlock_bh(&priv->lock);
		owl_emac_dma_unmap_tx(priv, skb, dma_addr);
		ret = -EBUSY;
		जाओ err_मुक्त_skb;
	पूर्ण

	ring->skbs[tx_head] = skb;
	ring->skbs_dma[tx_head] = dma_addr;

	control &= OWL_EMAC_BIT_TDES1_IC | OWL_EMAC_BIT_TDES1_TER; /* Maपूर्णांकain bits */
	control |= OWL_EMAC_BIT_TDES1_SET;
	control |= OWL_EMAC_MSK_TDES1_TBS1 & skb->len;

	WRITE_ONCE(desc->control, control);
	WRITE_ONCE(desc->buf_addr, dma_addr);
	dma_wmb(); /* Flush descriptor beक्रमe changing ownership. */
	WRITE_ONCE(desc->status, OWL_EMAC_BIT_TDES0_OWN);

	owl_emac_ring_push_head(ring);

	/* Temporarily enable DMA TX. */
	status = owl_emac_dma_cmd_start_tx(priv);

	/* Trigger setup frame processing. */
	owl_emac_dma_cmd_resume_tx(priv);

	/* Restore DMA TX status. */
	owl_emac_dma_cmd_set_tx(priv, status);

	/* Stop regular TX until setup frame is processed. */
	netअगर_stop_queue(netdev);

	spin_unlock_bh(&priv->lock);

	वापस 0;

err_मुक्त_skb:
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल netdev_tx_t owl_emac_nकरो_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *netdev)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);
	काष्ठा device *dev = owl_emac_get_dev(priv);
	काष्ठा owl_emac_ring *ring = &priv->tx_ring;
	काष्ठा owl_emac_ring_desc *desc;
	अचिन्हित पूर्णांक tx_head;
	u32 status, control;
	dma_addr_t dma_addr;

	dma_addr = owl_emac_dma_map_tx(priv, skb);
	अगर (dma_mapping_error(dev, dma_addr)) अणु
		dev_err_ratelimited(&netdev->dev, "TX DMA mapping failed\n");
		dev_kमुक्त_skb(skb);
		netdev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	spin_lock_bh(&priv->lock);

	tx_head = ring->head;
	desc = &ring->descs[tx_head];

	status = READ_ONCE(desc->status);
	control = READ_ONCE(desc->control);
	dma_rmb(); /* Ensure data has been पढ़ो beक्रमe used. */

	अगर (!owl_emac_ring_num_unused(ring) ||
	    unlikely(status & OWL_EMAC_BIT_TDES0_OWN)) अणु
		netअगर_stop_queue(netdev);
		spin_unlock_bh(&priv->lock);

		dev_dbg_ratelimited(&netdev->dev, "TX buffer full, status=0x%08x\n",
				    owl_emac_irq_status(priv));
		owl_emac_dma_unmap_tx(priv, skb, dma_addr);
		netdev->stats.tx_dropped++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	ring->skbs[tx_head] = skb;
	ring->skbs_dma[tx_head] = dma_addr;

	control &= OWL_EMAC_BIT_TDES1_IC | OWL_EMAC_BIT_TDES1_TER; /* Maपूर्णांकain bits */
	control |= OWL_EMAC_BIT_TDES1_FS | OWL_EMAC_BIT_TDES1_LS;
	control |= OWL_EMAC_MSK_TDES1_TBS1 & skb->len;

	WRITE_ONCE(desc->control, control);
	WRITE_ONCE(desc->buf_addr, dma_addr);
	dma_wmb(); /* Flush descriptor beक्रमe changing ownership. */
	WRITE_ONCE(desc->status, OWL_EMAC_BIT_TDES0_OWN);

	owl_emac_dma_cmd_resume_tx(priv);
	owl_emac_ring_push_head(ring);

	/* FIXME: The transmission is currently restricted to a single frame
	 * at a समय as a workaround क्रम a MAC hardware bug that causes अक्रमom
	 * मुक्तze of the TX queue processor.
	 */
	netअगर_stop_queue(netdev);

	spin_unlock_bh(&priv->lock);

	वापस NETDEV_TX_OK;
पूर्ण

अटल bool owl_emac_tx_complete_tail(काष्ठा owl_emac_priv *priv)
अणु
	काष्ठा owl_emac_ring *ring = &priv->tx_ring;
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा owl_emac_ring_desc *desc;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक tx_tail;
	u32 status;

	tx_tail = ring->tail;
	desc = &ring->descs[tx_tail];

	status = READ_ONCE(desc->status);
	dma_rmb(); /* Ensure data has been पढ़ो beक्रमe used. */

	अगर (status & OWL_EMAC_BIT_TDES0_OWN)
		वापस false;

	/* Check क्रम errors. */
	अगर (status & OWL_EMAC_BIT_TDES0_ES) अणु
		dev_dbg_ratelimited(&netdev->dev,
				    "TX complete error status: 0x%08x\n",
				    status);

		netdev->stats.tx_errors++;

		अगर (status & OWL_EMAC_BIT_TDES0_UF)
			netdev->stats.tx_fअगरo_errors++;

		अगर (status & OWL_EMAC_BIT_TDES0_EC)
			netdev->stats.tx_पातed_errors++;

		अगर (status & OWL_EMAC_BIT_TDES0_LC)
			netdev->stats.tx_winकरोw_errors++;

		अगर (status & OWL_EMAC_BIT_TDES0_NC)
			netdev->stats.tx_heartbeat_errors++;

		अगर (status & OWL_EMAC_BIT_TDES0_LO)
			netdev->stats.tx_carrier_errors++;
	पूर्ण अन्यथा अणु
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += ring->skbs[tx_tail]->len;
	पूर्ण

	/* Some collisions occurred, but pkt has been transmitted. */
	अगर (status & OWL_EMAC_BIT_TDES0_DE)
		netdev->stats.collisions++;

	skb = ring->skbs[tx_tail];
	owl_emac_dma_unmap_tx(priv, skb, ring->skbs_dma[tx_tail]);
	dev_kमुक्त_skb(skb);

	ring->skbs[tx_tail] = शून्य;
	ring->skbs_dma[tx_tail] = 0;

	owl_emac_ring_pop_tail(ring);

	अगर (unlikely(netअगर_queue_stopped(netdev)))
		netअगर_wake_queue(netdev);

	वापस true;
पूर्ण

अटल व्योम owl_emac_tx_complete(काष्ठा owl_emac_priv *priv)
अणु
	काष्ठा owl_emac_ring *ring = &priv->tx_ring;
	काष्ठा net_device *netdev = priv->netdev;
	अचिन्हित पूर्णांक tx_next;
	u32 status;

	spin_lock(&priv->lock);

	जबतक (ring->tail != ring->head) अणु
		अगर (!owl_emac_tx_complete_tail(priv))
			अवरोध;
	पूर्ण

	/* FIXME: This is a workaround क्रम a MAC hardware bug not clearing
	 * (someबार) the OWN bit क्रम a transmitted frame descriptor.
	 *
	 * At this poपूर्णांक, when TX queue is full, the tail descriptor has the
	 * OWN bit set, which normally means the frame has not been processed
	 * or transmitted yet. But अगर there is at least one descriptor in the
	 * queue having the OWN bit cleared, we can safely assume the tail
	 * frame has been also processed by the MAC hardware.
	 *
	 * If that's the case, let's क्रमce the frame completion by manually
	 * clearing the OWN bit.
	 */
	अगर (unlikely(!owl_emac_ring_num_unused(ring))) अणु
		tx_next = ring->tail;

		जबतक ((tx_next = owl_emac_ring_get_next(ring, tx_next)) != ring->head) अणु
			status = READ_ONCE(ring->descs[tx_next].status);
			dma_rmb(); /* Ensure data has been पढ़ो beक्रमe used. */

			अगर (status & OWL_EMAC_BIT_TDES0_OWN)
				जारी;

			netdev_dbg(netdev, "Found uncleared TX desc OWN bit\n");

			status = READ_ONCE(ring->descs[ring->tail].status);
			dma_rmb(); /* Ensure data has been पढ़ो beक्रमe used. */
			status &= ~OWL_EMAC_BIT_TDES0_OWN;
			WRITE_ONCE(ring->descs[ring->tail].status, status);

			owl_emac_tx_complete_tail(priv);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक owl_emac_rx_process(काष्ठा owl_emac_priv *priv, पूर्णांक budget)
अणु
	काष्ठा owl_emac_ring *ring = &priv->rx_ring;
	काष्ठा device *dev = owl_emac_get_dev(priv);
	काष्ठा net_device *netdev = priv->netdev;
	काष्ठा owl_emac_ring_desc *desc;
	काष्ठा sk_buff *curr_skb, *new_skb;
	dma_addr_t curr_dma, new_dma;
	अचिन्हित पूर्णांक rx_tail, len;
	u32 status;
	पूर्णांक recv = 0;

	जबतक (recv < budget) अणु
		spin_lock(&priv->lock);

		rx_tail = ring->tail;
		desc = &ring->descs[rx_tail];

		status = READ_ONCE(desc->status);
		dma_rmb(); /* Ensure data has been पढ़ो beक्रमe used. */

		अगर (status & OWL_EMAC_BIT_RDES0_OWN) अणु
			spin_unlock(&priv->lock);
			अवरोध;
		पूर्ण

		curr_skb = ring->skbs[rx_tail];
		curr_dma = ring->skbs_dma[rx_tail];
		owl_emac_ring_pop_tail(ring);

		spin_unlock(&priv->lock);

		अगर (status & (OWL_EMAC_BIT_RDES0_DE | OWL_EMAC_BIT_RDES0_RF |
		    OWL_EMAC_BIT_RDES0_TL | OWL_EMAC_BIT_RDES0_CS |
		    OWL_EMAC_BIT_RDES0_DB | OWL_EMAC_BIT_RDES0_CE |
		    OWL_EMAC_BIT_RDES0_ZERO)) अणु
			dev_dbg_ratelimited(&netdev->dev,
					    "RX desc error status: 0x%08x\n",
					    status);

			अगर (status & OWL_EMAC_BIT_RDES0_DE)
				netdev->stats.rx_over_errors++;

			अगर (status & (OWL_EMAC_BIT_RDES0_RF | OWL_EMAC_BIT_RDES0_DB))
				netdev->stats.rx_frame_errors++;

			अगर (status & OWL_EMAC_BIT_RDES0_TL)
				netdev->stats.rx_length_errors++;

			अगर (status & OWL_EMAC_BIT_RDES0_CS)
				netdev->stats.collisions++;

			अगर (status & OWL_EMAC_BIT_RDES0_CE)
				netdev->stats.rx_crc_errors++;

			अगर (status & OWL_EMAC_BIT_RDES0_ZERO)
				netdev->stats.rx_fअगरo_errors++;

			जाओ drop_skb;
		पूर्ण

		len = (status & OWL_EMAC_MSK_RDES0_FL) >> OWL_EMAC_OFF_RDES0_FL;
		अगर (unlikely(len > OWL_EMAC_RX_FRAME_MAX_LEN)) अणु
			netdev->stats.rx_length_errors++;
			netdev_err(netdev, "invalid RX frame len: %u\n", len);
			जाओ drop_skb;
		पूर्ण

		/* Prepare new skb beक्रमe receiving the current one. */
		new_skb = owl_emac_alloc_skb(netdev);
		अगर (unlikely(!new_skb))
			जाओ drop_skb;

		new_dma = owl_emac_dma_map_rx(priv, new_skb);
		अगर (dma_mapping_error(dev, new_dma)) अणु
			dev_kमुक्त_skb(new_skb);
			netdev_err(netdev, "RX DMA mapping failed\n");
			जाओ drop_skb;
		पूर्ण

		owl_emac_dma_unmap_rx(priv, curr_skb, curr_dma);

		skb_put(curr_skb, len - ETH_FCS_LEN);
		curr_skb->ip_summed = CHECKSUM_NONE;
		curr_skb->protocol = eth_type_trans(curr_skb, netdev);
		curr_skb->dev = netdev;

		netअगर_receive_skb(curr_skb);

		netdev->stats.rx_packets++;
		netdev->stats.rx_bytes += len;
		recv++;
		जाओ push_skb;

drop_skb:
		netdev->stats.rx_dropped++;
		netdev->stats.rx_errors++;
		/* Reuse the current skb. */
		new_skb = curr_skb;
		new_dma = curr_dma;

push_skb:
		spin_lock(&priv->lock);

		ring->skbs[ring->head] = new_skb;
		ring->skbs_dma[ring->head] = new_dma;

		WRITE_ONCE(desc->buf_addr, new_dma);
		dma_wmb(); /* Flush descriptor beक्रमe changing ownership. */
		WRITE_ONCE(desc->status, OWL_EMAC_BIT_RDES0_OWN);

		owl_emac_ring_push_head(ring);

		spin_unlock(&priv->lock);
	पूर्ण

	वापस recv;
पूर्ण

अटल पूर्णांक owl_emac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक work_करोne = 0, ru_cnt = 0, recv;
	अटल पूर्णांक tx_err_cnt, rx_err_cnt;
	काष्ठा owl_emac_priv *priv;
	u32 status, proc_status;

	priv = container_of(napi, काष्ठा owl_emac_priv, napi);

	जबतक ((status = owl_emac_irq_clear(priv)) &
	       (OWL_EMAC_BIT_MAC_CSR5_NIS | OWL_EMAC_BIT_MAC_CSR5_AIS)) अणु
		recv = 0;

		/* TX setup frame उठाओs ETI instead of TI. */
		अगर (status & (OWL_EMAC_BIT_MAC_CSR5_TI | OWL_EMAC_BIT_MAC_CSR5_ETI)) अणु
			owl_emac_tx_complete(priv);
			tx_err_cnt = 0;

			/* Count MAC पूर्णांकernal RX errors. */
			proc_status = status & OWL_EMAC_MSK_MAC_CSR5_RS;
			proc_status >>= OWL_EMAC_OFF_MAC_CSR5_RS;
			अगर (proc_status == OWL_EMAC_VAL_MAC_CSR5_RS_DATA ||
			    proc_status == OWL_EMAC_VAL_MAC_CSR5_RS_CDES ||
			    proc_status == OWL_EMAC_VAL_MAC_CSR5_RS_FDES)
				rx_err_cnt++;
		पूर्ण

		अगर (status & OWL_EMAC_BIT_MAC_CSR5_RI) अणु
			recv = owl_emac_rx_process(priv, budget - work_करोne);
			rx_err_cnt = 0;

			/* Count MAC पूर्णांकernal TX errors. */
			proc_status = status & OWL_EMAC_MSK_MAC_CSR5_TS;
			proc_status >>= OWL_EMAC_OFF_MAC_CSR5_TS;
			अगर (proc_status == OWL_EMAC_VAL_MAC_CSR5_TS_DATA ||
			    proc_status == OWL_EMAC_VAL_MAC_CSR5_TS_CDES)
				tx_err_cnt++;
		पूर्ण अन्यथा अगर (status & OWL_EMAC_BIT_MAC_CSR5_RU) अणु
			/* MAC AHB is in suspended state, will वापस to RX
			 * descriptor processing when the host changes ownership
			 * of the descriptor and either an RX poll demand CMD is
			 * issued or a new frame is recognized by the MAC AHB.
			 */
			अगर (++ru_cnt == 2)
				owl_emac_dma_cmd_resume_rx(priv);

			recv = owl_emac_rx_process(priv, budget - work_करोne);

			/* Guard against too many RU पूर्णांकerrupts. */
			अगर (ru_cnt > 3)
				अवरोध;
		पूर्ण

		work_करोne += recv;
		अगर (work_करोne >= budget)
			अवरोध;
	पूर्ण

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		owl_emac_irq_enable(priv);
	पूर्ण

	/* Reset MAC when getting too many पूर्णांकernal TX or RX errors. */
	अगर (tx_err_cnt > 10 || rx_err_cnt > 10) अणु
		netdev_dbg(priv->netdev, "%s error status: 0x%08x\n",
			   tx_err_cnt > 10 ? "TX" : "RX", status);
		rx_err_cnt = 0;
		tx_err_cnt = 0;
		schedule_work(&priv->mac_reset_task);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल व्योम owl_emac_mdio_घड़ी_enable(काष्ठा owl_emac_priv *priv)
अणु
	u32 val;

	/* Enable MDC घड़ी generation by adjusting CLKDIV according to
	 * the venकरोr implementation of the original driver.
	 */
	val = owl_emac_reg_पढ़ो(priv, OWL_EMAC_REG_MAC_CSR10);
	val &= OWL_EMAC_MSK_MAC_CSR10_CLKDIV;
	val |= OWL_EMAC_VAL_MAC_CSR10_CLKDIV_128 << OWL_EMAC_OFF_MAC_CSR10_CLKDIV;

	val |= OWL_EMAC_BIT_MAC_CSR10_SB;
	val |= OWL_EMAC_VAL_MAC_CSR10_OPCODE_CDS << OWL_EMAC_OFF_MAC_CSR10_OPCODE;
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR10, val);
पूर्ण

अटल व्योम owl_emac_core_hw_reset(काष्ठा owl_emac_priv *priv)
अणु
	/* Trigger hardware reset. */
	reset_control_निश्चित(priv->reset);
	usleep_range(10, 20);
	reset_control_deनिश्चित(priv->reset);
	usleep_range(100, 200);
पूर्ण

अटल पूर्णांक owl_emac_core_sw_reset(काष्ठा owl_emac_priv *priv)
अणु
	u32 val;
	पूर्णांक ret;

	/* Trigger software reset. */
	owl_emac_reg_set(priv, OWL_EMAC_REG_MAC_CSR0, OWL_EMAC_BIT_MAC_CSR0_SWR);
	ret = पढ़ोl_poll_समयout(priv->base + OWL_EMAC_REG_MAC_CSR0,
				 val, !(val & OWL_EMAC_BIT_MAC_CSR0_SWR),
				 OWL_EMAC_POLL_DELAY_USEC,
				 OWL_EMAC_RESET_POLL_TIMEOUT_USEC);
	अगर (ret)
		वापस ret;

	अगर (priv->phy_mode == PHY_INTERFACE_MODE_RMII) अणु
		/* Enable RMII and use the 50MHz rmii clk as output to PHY. */
		val = 0;
	पूर्ण अन्यथा अणु
		/* Enable SMII and use the 125MHz rmii clk as output to PHY.
		 * Additionally set SMII SYNC delay to 4 half cycle.
		 */
		val = 0x04 << OWL_EMAC_OFF_MAC_CTRL_SSDC;
		val |= OWL_EMAC_BIT_MAC_CTRL_RSIS;
	पूर्ण
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CTRL, val);

	/* MDC is disabled after reset. */
	owl_emac_mdio_घड़ी_enable(priv);

	/* Set FIFO छोड़ो & restart threshold levels. */
	val = 0x40 << OWL_EMAC_OFF_MAC_CSR19_FPTL;
	val |= 0x10 << OWL_EMAC_OFF_MAC_CSR19_FRTL;
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR19, val);

	/* Set flow control छोड़ो quanta समय to ~100 ms. */
	val = 0x4FFF << OWL_EMAC_OFF_MAC_CSR18_PQT;
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR18, val);

	/* Setup पूर्णांकerrupt mitigation. */
	val = 7 << OWL_EMAC_OFF_MAC_CSR11_NRP;
	val |= 4 << OWL_EMAC_OFF_MAC_CSR11_RT;
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR11, val);

	/* Set RX/TX rings base addresses. */
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR3,
			   (u32)(priv->rx_ring.descs_dma));
	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR4,
			   (u32)(priv->tx_ring.descs_dma));

	/* Setup initial operation mode. */
	val = OWL_EMAC_VAL_MAC_CSR6_SPEED_100M << OWL_EMAC_OFF_MAC_CSR6_SPEED;
	val |= OWL_EMAC_BIT_MAC_CSR6_FD;
	owl_emac_reg_update(priv, OWL_EMAC_REG_MAC_CSR6,
			    OWL_EMAC_MSK_MAC_CSR6_SPEED |
			    OWL_EMAC_BIT_MAC_CSR6_FD, val);
	owl_emac_reg_clear(priv, OWL_EMAC_REG_MAC_CSR6,
			   OWL_EMAC_BIT_MAC_CSR6_PR | OWL_EMAC_BIT_MAC_CSR6_PM);

	priv->link = 0;
	priv->speed = SPEED_UNKNOWN;
	priv->duplex = DUPLEX_UNKNOWN;
	priv->छोड़ो = 0;
	priv->mcaddr_list.count = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक owl_emac_enable(काष्ठा net_device *netdev, bool start_phy)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);
	पूर्णांक ret;

	owl_emac_dma_cmd_stop(priv);
	owl_emac_irq_disable(priv);
	owl_emac_irq_clear(priv);

	owl_emac_ring_prepare_tx(priv);
	ret = owl_emac_ring_prepare_rx(priv);
	अगर (ret)
		जाओ err_unprep;

	ret = owl_emac_core_sw_reset(priv);
	अगर (ret) अणु
		netdev_err(netdev, "failed to soft reset MAC core: %d\n", ret);
		जाओ err_unprep;
	पूर्ण

	owl_emac_set_hw_mac_addr(netdev);
	owl_emac_setup_frame_xmit(priv);

	netdev_reset_queue(netdev);
	napi_enable(&priv->napi);

	owl_emac_irq_enable(priv);
	owl_emac_dma_cmd_start(priv);

	अगर (start_phy)
		phy_start(netdev->phydev);

	netअगर_start_queue(netdev);

	वापस 0;

err_unprep:
	owl_emac_ring_unprepare_rx(priv);
	owl_emac_ring_unprepare_tx(priv);

	वापस ret;
पूर्ण

अटल व्योम owl_emac_disable(काष्ठा net_device *netdev, bool stop_phy)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);

	owl_emac_dma_cmd_stop(priv);
	owl_emac_irq_disable(priv);

	netअगर_stop_queue(netdev);
	napi_disable(&priv->napi);

	अगर (stop_phy)
		phy_stop(netdev->phydev);

	owl_emac_ring_unprepare_rx(priv);
	owl_emac_ring_unprepare_tx(priv);
पूर्ण

अटल पूर्णांक owl_emac_nकरो_खोलो(काष्ठा net_device *netdev)
अणु
	वापस owl_emac_enable(netdev, true);
पूर्ण

अटल पूर्णांक owl_emac_nकरो_stop(काष्ठा net_device *netdev)
अणु
	owl_emac_disable(netdev, true);

	वापस 0;
पूर्ण

अटल व्योम owl_emac_set_multicast(काष्ठा net_device *netdev, पूर्णांक count)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक index = 0;

	अगर (count <= 0) अणु
		priv->mcaddr_list.count = 0;
		वापस;
	पूर्ण

	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		अगर (!is_multicast_ether_addr(ha->addr))
			जारी;

		WARN_ON(index >= OWL_EMAC_MAX_MULTICAST_ADDRS);
		ether_addr_copy(priv->mcaddr_list.addrs[index++], ha->addr);
	पूर्ण

	priv->mcaddr_list.count = index;

	owl_emac_setup_frame_xmit(priv);
पूर्ण

अटल व्योम owl_emac_nकरो_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);
	u32 status, val = 0;
	पूर्णांक mcast_count = 0;

	अगर (netdev->flags & IFF_PROMISC) अणु
		val = OWL_EMAC_BIT_MAC_CSR6_PR;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_ALLMULTI) अणु
		val = OWL_EMAC_BIT_MAC_CSR6_PM;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_MULTICAST) अणु
		mcast_count = netdev_mc_count(netdev);

		अगर (mcast_count > OWL_EMAC_MAX_MULTICAST_ADDRS) अणु
			val = OWL_EMAC_BIT_MAC_CSR6_PM;
			mcast_count = 0;
		पूर्ण
	पूर्ण

	spin_lock_bh(&priv->lock);

	/* Temporarily stop DMA TX & RX. */
	status = owl_emac_dma_cmd_stop(priv);

	/* Update operation modes. */
	owl_emac_reg_update(priv, OWL_EMAC_REG_MAC_CSR6,
			    OWL_EMAC_BIT_MAC_CSR6_PR | OWL_EMAC_BIT_MAC_CSR6_PM,
			    val);

	/* Restore DMA TX & RX status. */
	owl_emac_dma_cmd_set(priv, status);

	spin_unlock_bh(&priv->lock);

	/* Set/reset multicast addr list. */
	owl_emac_set_multicast(netdev, mcast_count);
पूर्ण

अटल पूर्णांक owl_emac_nकरो_set_mac_addr(काष्ठा net_device *netdev, व्योम *addr)
अणु
	काष्ठा sockaddr *skaddr = addr;

	अगर (!is_valid_ether_addr(skaddr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	स_नकल(netdev->dev_addr, skaddr->sa_data, netdev->addr_len);
	owl_emac_set_hw_mac_addr(netdev);

	वापस owl_emac_setup_frame_xmit(netdev_priv(netdev));
पूर्ण

अटल पूर्णांक owl_emac_nकरो_करो_ioctl(काष्ठा net_device *netdev,
				 काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	अगर (!netअगर_running(netdev))
		वापस -EINVAL;

	वापस phy_mii_ioctl(netdev->phydev, req, cmd);
पूर्ण

अटल व्योम owl_emac_nकरो_tx_समयout(काष्ठा net_device *netdev,
				    अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);

	schedule_work(&priv->mac_reset_task);
पूर्ण

अटल व्योम owl_emac_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा owl_emac_priv *priv;

	priv = container_of(work, काष्ठा owl_emac_priv, mac_reset_task);

	netdev_dbg(priv->netdev, "resetting MAC\n");
	owl_emac_disable(priv->netdev, false);
	owl_emac_enable(priv->netdev, false);
पूर्ण

अटल काष्ठा net_device_stats *
owl_emac_nकरो_get_stats(काष्ठा net_device *netdev)
अणु
	/* FIXME: If possible, try to get stats from MAC hardware रेजिस्टरs
	 * instead of tracking them manually in the driver.
	 */

	वापस &netdev->stats;
पूर्ण

अटल स्थिर काष्ठा net_device_ops owl_emac_netdev_ops = अणु
	.nकरो_खोलो		= owl_emac_nकरो_खोलो,
	.nकरो_stop		= owl_emac_nकरो_stop,
	.nकरो_start_xmit		= owl_emac_nकरो_start_xmit,
	.nकरो_set_rx_mode	= owl_emac_nकरो_set_rx_mode,
	.nकरो_set_mac_address	= owl_emac_nकरो_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= owl_emac_nकरो_करो_ioctl,
	.nकरो_tx_समयout         = owl_emac_nकरो_tx_समयout,
	.nकरो_get_stats		= owl_emac_nकरो_get_stats,
पूर्ण;

अटल व्योम owl_emac_ethtool_get_drvinfo(काष्ठा net_device *dev,
					 काष्ठा ethtool_drvinfo *info)
अणु
	strscpy(info->driver, OWL_EMAC_DRVNAME, माप(info->driver));
पूर्ण

अटल u32 owl_emac_ethtool_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम owl_emac_ethtool_set_msglevel(काष्ठा net_device *ndev, u32 val)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(ndev);

	priv->msg_enable = val;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops owl_emac_ethtool_ops = अणु
	.get_drvinfo		= owl_emac_ethtool_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
	.get_msglevel		= owl_emac_ethtool_get_msglevel,
	.set_msglevel		= owl_emac_ethtool_set_msglevel,
पूर्ण;

अटल पूर्णांक owl_emac_mdio_रुको(काष्ठा owl_emac_priv *priv)
अणु
	u32 val;

	/* Wait जबतक data transfer is in progress. */
	वापस पढ़ोl_poll_समयout(priv->base + OWL_EMAC_REG_MAC_CSR10,
				  val, !(val & OWL_EMAC_BIT_MAC_CSR10_SB),
				  OWL_EMAC_POLL_DELAY_USEC,
				  OWL_EMAC_MDIO_POLL_TIMEOUT_USEC);
पूर्ण

अटल पूर्णांक owl_emac_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum)
अणु
	काष्ठा owl_emac_priv *priv = bus->priv;
	u32 data, पंचांगp;
	पूर्णांक ret;

	अगर (regnum & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	data = OWL_EMAC_BIT_MAC_CSR10_SB;
	data |= OWL_EMAC_VAL_MAC_CSR10_OPCODE_RD << OWL_EMAC_OFF_MAC_CSR10_OPCODE;

	पंचांगp = addr << OWL_EMAC_OFF_MAC_CSR10_PHYADD;
	data |= पंचांगp & OWL_EMAC_MSK_MAC_CSR10_PHYADD;

	पंचांगp = regnum << OWL_EMAC_OFF_MAC_CSR10_REGADD;
	data |= पंचांगp & OWL_EMAC_MSK_MAC_CSR10_REGADD;

	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR10, data);

	ret = owl_emac_mdio_रुको(priv);
	अगर (ret)
		वापस ret;

	data = owl_emac_reg_पढ़ो(priv, OWL_EMAC_REG_MAC_CSR10);
	data &= OWL_EMAC_MSK_MAC_CSR10_DATA;

	वापस data;
पूर्ण

अटल पूर्णांक
owl_emac_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum, u16 val)
अणु
	काष्ठा owl_emac_priv *priv = bus->priv;
	u32 data, पंचांगp;

	अगर (regnum & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	data = OWL_EMAC_BIT_MAC_CSR10_SB;
	data |= OWL_EMAC_VAL_MAC_CSR10_OPCODE_WR << OWL_EMAC_OFF_MAC_CSR10_OPCODE;

	पंचांगp = addr << OWL_EMAC_OFF_MAC_CSR10_PHYADD;
	data |= पंचांगp & OWL_EMAC_MSK_MAC_CSR10_PHYADD;

	पंचांगp = regnum << OWL_EMAC_OFF_MAC_CSR10_REGADD;
	data |= पंचांगp & OWL_EMAC_MSK_MAC_CSR10_REGADD;

	data |= val & OWL_EMAC_MSK_MAC_CSR10_DATA;

	owl_emac_reg_ग_लिखो(priv, OWL_EMAC_REG_MAC_CSR10, data);

	वापस owl_emac_mdio_रुको(priv);
पूर्ण

अटल पूर्णांक owl_emac_mdio_init(काष्ठा net_device *netdev)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);
	काष्ठा device *dev = owl_emac_get_dev(priv);
	काष्ठा device_node *mdio_node;
	पूर्णांक ret;

	mdio_node = of_get_child_by_name(dev->of_node, "mdio");
	अगर (!mdio_node)
		वापस -ENODEV;

	अगर (!of_device_is_available(mdio_node)) अणु
		ret = -ENODEV;
		जाओ err_put_node;
	पूर्ण

	priv->mii = devm_mdiobus_alloc(dev);
	अगर (!priv->mii) अणु
		ret = -ENOMEM;
		जाओ err_put_node;
	पूर्ण

	snम_लिखो(priv->mii->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));
	priv->mii->name = "owl-emac-mdio";
	priv->mii->parent = dev;
	priv->mii->पढ़ो = owl_emac_mdio_पढ़ो;
	priv->mii->ग_लिखो = owl_emac_mdio_ग_लिखो;
	priv->mii->phy_mask = ~0; /* Mask out all PHYs from स्वतः probing. */
	priv->mii->priv = priv;

	ret = devm_of_mdiobus_रेजिस्टर(dev, priv->mii, mdio_node);

err_put_node:
	of_node_put(mdio_node);
	वापस ret;
पूर्ण

अटल पूर्णांक owl_emac_phy_init(काष्ठा net_device *netdev)
अणु
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);
	काष्ठा device *dev = owl_emac_get_dev(priv);
	काष्ठा phy_device *phy;

	phy = of_phy_get_and_connect(netdev, dev->of_node,
				     owl_emac_adjust_link);
	अगर (!phy)
		वापस -ENODEV;

	phy_set_sym_छोड़ो(phy, true, true, true);

	अगर (netअगर_msg_link(priv))
		phy_attached_info(phy);

	वापस 0;
पूर्ण

अटल व्योम owl_emac_get_mac_addr(काष्ठा net_device *netdev)
अणु
	काष्ठा device *dev = netdev->dev.parent;
	पूर्णांक ret;

	ret = eth_platक्रमm_get_mac_address(dev, netdev->dev_addr);
	अगर (!ret && is_valid_ether_addr(netdev->dev_addr))
		वापस;

	eth_hw_addr_अक्रमom(netdev);
	dev_warn(dev, "using random MAC address %pM\n", netdev->dev_addr);
पूर्ण

अटल __maybe_unused पूर्णांक owl_emac_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);

	disable_irq(netdev->irq);

	अगर (netअगर_running(netdev)) अणु
		owl_emac_disable(netdev, true);
		netअगर_device_detach(netdev);
	पूर्ण

	clk_bulk_disable_unprepare(OWL_EMAC_NCLKS, priv->clks);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक owl_emac_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा owl_emac_priv *priv = netdev_priv(netdev);
	पूर्णांक ret;

	ret = clk_bulk_prepare_enable(OWL_EMAC_NCLKS, priv->clks);
	अगर (ret)
		वापस ret;

	अगर (netअगर_running(netdev)) अणु
		owl_emac_core_hw_reset(priv);
		owl_emac_core_sw_reset(priv);

		ret = owl_emac_enable(netdev, true);
		अगर (ret) अणु
			clk_bulk_disable_unprepare(OWL_EMAC_NCLKS, priv->clks);
			वापस ret;
		पूर्ण

		netअगर_device_attach(netdev);
	पूर्ण

	enable_irq(netdev->irq);

	वापस 0;
पूर्ण

अटल व्योम owl_emac_clk_disable_unprepare(व्योम *data)
अणु
	काष्ठा owl_emac_priv *priv = data;

	clk_bulk_disable_unprepare(OWL_EMAC_NCLKS, priv->clks);
पूर्ण

अटल पूर्णांक owl_emac_clk_set_rate(काष्ठा owl_emac_priv *priv)
अणु
	काष्ठा device *dev = owl_emac_get_dev(priv);
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	चयन (priv->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RMII:
		rate = 50000000;
		अवरोध;

	हाल PHY_INTERFACE_MODE_SMII:
		rate = 125000000;
		अवरोध;

	शेष:
		dev_err(dev, "unsupported phy interface mode %d\n",
			priv->phy_mode);
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = clk_set_rate(priv->clks[OWL_EMAC_CLK_RMII].clk, rate);
	अगर (ret)
		dev_err(dev, "failed to set RMII clock rate: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक owl_emac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *netdev;
	काष्ठा owl_emac_priv *priv;
	पूर्णांक ret, i;

	netdev = devm_alloc_etherdev(dev, माप(*priv));
	अगर (!netdev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, netdev);
	SET_NETDEV_DEV(netdev, dev);

	priv = netdev_priv(netdev);
	priv->netdev = netdev;
	priv->msg_enable = netअगर_msg_init(-1, OWL_EMAC_DEFAULT_MSG_ENABLE);

	ret = of_get_phy_mode(dev->of_node, &priv->phy_mode);
	अगर (ret) अणु
		dev_err(dev, "failed to get phy mode: %d\n", ret);
		वापस ret;
	पूर्ण

	spin_lock_init(&priv->lock);

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(dev, "unsupported DMA mask\n");
		वापस ret;
	पूर्ण

	ret = owl_emac_ring_alloc(dev, &priv->rx_ring, OWL_EMAC_RX_RING_SIZE);
	अगर (ret)
		वापस ret;

	ret = owl_emac_ring_alloc(dev, &priv->tx_ring, OWL_EMAC_TX_RING_SIZE);
	अगर (ret)
		वापस ret;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	netdev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (netdev->irq < 0)
		वापस netdev->irq;

	ret = devm_request_irq(dev, netdev->irq, owl_emac_handle_irq,
			       IRQF_SHARED, netdev->name, netdev);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq: %d\n", netdev->irq);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < OWL_EMAC_NCLKS; i++)
		priv->clks[i].id = owl_emac_clk_names[i];

	ret = devm_clk_bulk_get(dev, OWL_EMAC_NCLKS, priv->clks);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(OWL_EMAC_NCLKS, priv->clks);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, owl_emac_clk_disable_unprepare, priv);
	अगर (ret)
		वापस ret;

	ret = owl_emac_clk_set_rate(priv);
	अगर (ret)
		वापस ret;

	priv->reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(priv->reset))
		वापस dev_err_probe(dev, PTR_ERR(priv->reset),
				     "failed to get reset control");

	owl_emac_get_mac_addr(netdev);

	owl_emac_core_hw_reset(priv);
	owl_emac_mdio_घड़ी_enable(priv);

	ret = owl_emac_mdio_init(netdev);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize MDIO bus\n");
		वापस ret;
	पूर्ण

	ret = owl_emac_phy_init(netdev);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize PHY\n");
		वापस ret;
	पूर्ण

	INIT_WORK(&priv->mac_reset_task, owl_emac_reset_task);

	netdev->min_mtu = OWL_EMAC_MTU_MIN;
	netdev->max_mtu = OWL_EMAC_MTU_MAX;
	netdev->watchकरोg_समयo = OWL_EMAC_TX_TIMEOUT;
	netdev->netdev_ops = &owl_emac_netdev_ops;
	netdev->ethtool_ops = &owl_emac_ethtool_ops;
	netअगर_napi_add(netdev, &priv->napi, owl_emac_poll, NAPI_POLL_WEIGHT);

	ret = devm_रेजिस्टर_netdev(dev, netdev);
	अगर (ret) अणु
		netअगर_napi_del(&priv->napi);
		phy_disconnect(netdev->phydev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक owl_emac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा owl_emac_priv *priv = platक्रमm_get_drvdata(pdev);

	netअगर_napi_del(&priv->napi);
	phy_disconnect(priv->netdev->phydev);
	cancel_work_sync(&priv->mac_reset_task);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id owl_emac_of_match[] = अणु
	अणु .compatible = "actions,owl-emac", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, owl_emac_of_match);

अटल SIMPLE_DEV_PM_OPS(owl_emac_pm_ops,
			 owl_emac_suspend, owl_emac_resume);

अटल काष्ठा platक्रमm_driver owl_emac_driver = अणु
	.driver = अणु
		.name = OWL_EMAC_DRVNAME,
		.of_match_table = owl_emac_of_match,
		.pm = &owl_emac_pm_ops,
	पूर्ण,
	.probe = owl_emac_probe,
	.हटाओ = owl_emac_हटाओ,
पूर्ण;
module_platक्रमm_driver(owl_emac_driver);

MODULE_DESCRIPTION("Actions Semi Owl SoCs Ethernet MAC Driver");
MODULE_AUTHOR("Actions Semi Inc.");
MODULE_AUTHOR("Cristian Ciocaltea <cristian.ciocaltea@gmail.com>");
MODULE_LICENSE("GPL");
