<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2021 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश "bcm4908_enet.h"
#समावेश "unimac.h"

#घोषणा ENET_DMA_CH_RX_CFG			ENET_DMA_CH0_CFG
#घोषणा ENET_DMA_CH_TX_CFG			ENET_DMA_CH1_CFG
#घोषणा ENET_DMA_CH_RX_STATE_RAM		ENET_DMA_CH0_STATE_RAM
#घोषणा ENET_DMA_CH_TX_STATE_RAM		ENET_DMA_CH1_STATE_RAM

#घोषणा ENET_TX_BDS_NUM				200
#घोषणा ENET_RX_BDS_NUM				200
#घोषणा ENET_RX_BDS_NUM_MAX			8192

#घोषणा ENET_DMA_INT_DEFAULTS			(ENET_DMA_CH_CFG_INT_DONE | \
						 ENET_DMA_CH_CFG_INT_NO_DESC | \
						 ENET_DMA_CH_CFG_INT_BUFF_DONE)
#घोषणा ENET_DMA_MAX_BURST_LEN			8 /* in 64 bit words */

#घोषणा ENET_MTU_MAX				ETH_DATA_LEN /* Is it possible to support 2044? */
#घोषणा BRCM_MAX_TAG_LEN			6
#घोषणा ENET_MAX_ETH_OVERHEAD			(ETH_HLEN + BRCM_MAX_TAG_LEN + VLAN_HLEN + \
						 ETH_FCS_LEN + 4) /* 32 */

काष्ठा bcm4908_enet_dma_ring_bd अणु
	__le32 ctl;
	__le32 addr;
पूर्ण __packed;

काष्ठा bcm4908_enet_dma_ring_slot अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;
	dma_addr_t dma_addr;
पूर्ण;

काष्ठा bcm4908_enet_dma_ring अणु
	पूर्णांक is_tx;
	पूर्णांक पढ़ो_idx;
	पूर्णांक ग_लिखो_idx;
	पूर्णांक length;
	u16 cfg_block;
	u16 st_ram_block;
	काष्ठा napi_काष्ठा napi;

	जोड़ अणु
		व्योम *cpu_addr;
		काष्ठा bcm4908_enet_dma_ring_bd *buf_desc;
	पूर्ण;
	dma_addr_t dma_addr;

	काष्ठा bcm4908_enet_dma_ring_slot *slots;
पूर्ण;

काष्ठा bcm4908_enet अणु
	काष्ठा device *dev;
	काष्ठा net_device *netdev;
	व्योम __iomem *base;
	पूर्णांक irq_tx;

	काष्ठा bcm4908_enet_dma_ring tx_ring;
	काष्ठा bcm4908_enet_dma_ring rx_ring;
पूर्ण;

/***
 * R/W ops
 */

अटल u32 enet_पढ़ो(काष्ठा bcm4908_enet *enet, u16 offset)
अणु
	वापस पढ़ोl(enet->base + offset);
पूर्ण

अटल व्योम enet_ग_लिखो(काष्ठा bcm4908_enet *enet, u16 offset, u32 value)
अणु
	ग_लिखोl(value, enet->base + offset);
पूर्ण

अटल व्योम enet_maskset(काष्ठा bcm4908_enet *enet, u16 offset, u32 mask, u32 set)
अणु
	u32 val;

	WARN_ON(set & ~mask);

	val = enet_पढ़ो(enet, offset);
	val = (val & ~mask) | (set & mask);
	enet_ग_लिखो(enet, offset, val);
पूर्ण

अटल व्योम enet_set(काष्ठा bcm4908_enet *enet, u16 offset, u32 set)
अणु
	enet_maskset(enet, offset, set, set);
पूर्ण

अटल u32 enet_umac_पढ़ो(काष्ठा bcm4908_enet *enet, u16 offset)
अणु
	वापस enet_पढ़ो(enet, ENET_UNIMAC + offset);
पूर्ण

अटल व्योम enet_umac_ग_लिखो(काष्ठा bcm4908_enet *enet, u16 offset, u32 value)
अणु
	enet_ग_लिखो(enet, ENET_UNIMAC + offset, value);
पूर्ण

अटल व्योम enet_umac_set(काष्ठा bcm4908_enet *enet, u16 offset, u32 set)
अणु
	enet_set(enet, ENET_UNIMAC + offset, set);
पूर्ण

/***
 * Helpers
 */

अटल व्योम bcm4908_enet_set_mtu(काष्ठा bcm4908_enet *enet, पूर्णांक mtu)
अणु
	enet_umac_ग_लिखो(enet, UMAC_MAX_FRAME_LEN, mtu + ENET_MAX_ETH_OVERHEAD);
पूर्ण

/***
 * DMA ring ops
 */

अटल व्योम bcm4908_enet_dma_ring_पूर्णांकrs_on(काष्ठा bcm4908_enet *enet,
					   काष्ठा bcm4908_enet_dma_ring *ring)
अणु
	enet_ग_लिखो(enet, ring->cfg_block + ENET_DMA_CH_CFG_INT_MASK, ENET_DMA_INT_DEFAULTS);
पूर्ण

अटल व्योम bcm4908_enet_dma_ring_पूर्णांकrs_off(काष्ठा bcm4908_enet *enet,
					    काष्ठा bcm4908_enet_dma_ring *ring)
अणु
	enet_ग_लिखो(enet, ring->cfg_block + ENET_DMA_CH_CFG_INT_MASK, 0);
पूर्ण

अटल व्योम bcm4908_enet_dma_ring_पूर्णांकrs_ack(काष्ठा bcm4908_enet *enet,
					    काष्ठा bcm4908_enet_dma_ring *ring)
अणु
	enet_ग_लिखो(enet, ring->cfg_block + ENET_DMA_CH_CFG_INT_STAT, ENET_DMA_INT_DEFAULTS);
पूर्ण

/***
 * DMA
 */

अटल पूर्णांक bcm4908_dma_alloc_buf_descs(काष्ठा bcm4908_enet *enet,
				       काष्ठा bcm4908_enet_dma_ring *ring)
अणु
	पूर्णांक size = ring->length * माप(काष्ठा bcm4908_enet_dma_ring_bd);
	काष्ठा device *dev = enet->dev;

	ring->cpu_addr = dma_alloc_coherent(dev, size, &ring->dma_addr, GFP_KERNEL);
	अगर (!ring->cpu_addr)
		वापस -ENOMEM;

	अगर (((uपूर्णांकptr_t)ring->cpu_addr) & (0x40 - 1)) अणु
		dev_err(dev, "Invalid DMA ring alignment\n");
		जाओ err_मुक्त_buf_descs;
	पूर्ण

	ring->slots = kzalloc(ring->length * माप(*ring->slots), GFP_KERNEL);
	अगर (!ring->slots)
		जाओ err_मुक्त_buf_descs;

	ring->पढ़ो_idx = 0;
	ring->ग_लिखो_idx = 0;

	वापस 0;

err_मुक्त_buf_descs:
	dma_मुक्त_coherent(dev, size, ring->cpu_addr, ring->dma_addr);
	ring->cpu_addr = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल व्योम bcm4908_enet_dma_मुक्त(काष्ठा bcm4908_enet *enet)
अणु
	काष्ठा bcm4908_enet_dma_ring *tx_ring = &enet->tx_ring;
	काष्ठा bcm4908_enet_dma_ring *rx_ring = &enet->rx_ring;
	काष्ठा device *dev = enet->dev;
	पूर्णांक size;

	size = rx_ring->length * माप(काष्ठा bcm4908_enet_dma_ring_bd);
	अगर (rx_ring->cpu_addr)
		dma_मुक्त_coherent(dev, size, rx_ring->cpu_addr, rx_ring->dma_addr);
	kमुक्त(rx_ring->slots);

	size = tx_ring->length * माप(काष्ठा bcm4908_enet_dma_ring_bd);
	अगर (tx_ring->cpu_addr)
		dma_मुक्त_coherent(dev, size, tx_ring->cpu_addr, tx_ring->dma_addr);
	kमुक्त(tx_ring->slots);
पूर्ण

अटल पूर्णांक bcm4908_enet_dma_alloc(काष्ठा bcm4908_enet *enet)
अणु
	काष्ठा bcm4908_enet_dma_ring *tx_ring = &enet->tx_ring;
	काष्ठा bcm4908_enet_dma_ring *rx_ring = &enet->rx_ring;
	काष्ठा device *dev = enet->dev;
	पूर्णांक err;

	tx_ring->length = ENET_TX_BDS_NUM;
	tx_ring->is_tx = 1;
	tx_ring->cfg_block = ENET_DMA_CH_TX_CFG;
	tx_ring->st_ram_block = ENET_DMA_CH_TX_STATE_RAM;
	err = bcm4908_dma_alloc_buf_descs(enet, tx_ring);
	अगर (err) अणु
		dev_err(dev, "Failed to alloc TX buf descriptors: %d\n", err);
		वापस err;
	पूर्ण

	rx_ring->length = ENET_RX_BDS_NUM;
	rx_ring->is_tx = 0;
	rx_ring->cfg_block = ENET_DMA_CH_RX_CFG;
	rx_ring->st_ram_block = ENET_DMA_CH_RX_STATE_RAM;
	err = bcm4908_dma_alloc_buf_descs(enet, rx_ring);
	अगर (err) अणु
		dev_err(dev, "Failed to alloc RX buf descriptors: %d\n", err);
		bcm4908_enet_dma_मुक्त(enet);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bcm4908_enet_dma_reset(काष्ठा bcm4908_enet *enet)
अणु
	काष्ठा bcm4908_enet_dma_ring *rings[] = अणु &enet->rx_ring, &enet->tx_ring पूर्ण;
	पूर्णांक i;

	/* Disable the DMA controller and channel */
	क्रम (i = 0; i < ARRAY_SIZE(rings); i++)
		enet_ग_लिखो(enet, rings[i]->cfg_block + ENET_DMA_CH_CFG, 0);
	enet_maskset(enet, ENET_DMA_CONTROLLER_CFG, ENET_DMA_CTRL_CFG_MASTER_EN, 0);

	/* Reset channels state */
	क्रम (i = 0; i < ARRAY_SIZE(rings); i++) अणु
		काष्ठा bcm4908_enet_dma_ring *ring = rings[i];

		enet_ग_लिखो(enet, ring->st_ram_block + ENET_DMA_CH_STATE_RAM_BASE_DESC_PTR, 0);
		enet_ग_लिखो(enet, ring->st_ram_block + ENET_DMA_CH_STATE_RAM_STATE_DATA, 0);
		enet_ग_लिखो(enet, ring->st_ram_block + ENET_DMA_CH_STATE_RAM_DESC_LEN_STATUS, 0);
		enet_ग_लिखो(enet, ring->st_ram_block + ENET_DMA_CH_STATE_RAM_DESC_BASE_BUFPTR, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक bcm4908_enet_dma_alloc_rx_buf(काष्ठा bcm4908_enet *enet, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा bcm4908_enet_dma_ring_bd *buf_desc = &enet->rx_ring.buf_desc[idx];
	काष्ठा bcm4908_enet_dma_ring_slot *slot = &enet->rx_ring.slots[idx];
	काष्ठा device *dev = enet->dev;
	u32 पंचांगp;
	पूर्णांक err;

	slot->len = ENET_MTU_MAX + ENET_MAX_ETH_OVERHEAD;

	slot->skb = netdev_alloc_skb(enet->netdev, slot->len);
	अगर (!slot->skb)
		वापस -ENOMEM;

	slot->dma_addr = dma_map_single(dev, slot->skb->data, slot->len, DMA_FROM_DEVICE);
	err = dma_mapping_error(dev, slot->dma_addr);
	अगर (err) अणु
		dev_err(dev, "Failed to map DMA buffer: %d\n", err);
		kमुक्त_skb(slot->skb);
		slot->skb = शून्य;
		वापस err;
	पूर्ण

	पंचांगp = slot->len << DMA_CTL_LEN_DESC_BUFLENGTH_SHIFT;
	पंचांगp |= DMA_CTL_STATUS_OWN;
	अगर (idx == enet->rx_ring.length - 1)
		पंचांगp |= DMA_CTL_STATUS_WRAP;
	buf_desc->ctl = cpu_to_le32(पंचांगp);
	buf_desc->addr = cpu_to_le32(slot->dma_addr);

	वापस 0;
पूर्ण

अटल व्योम bcm4908_enet_dma_ring_init(काष्ठा bcm4908_enet *enet,
				       काष्ठा bcm4908_enet_dma_ring *ring)
अणु
	पूर्णांक reset_channel = 0; /* We support only 1 मुख्य channel (with TX and RX) */
	पूर्णांक reset_subch = ring->is_tx ? 1 : 0;

	/* Reset the DMA channel */
	enet_ग_लिखो(enet, ENET_DMA_CTRL_CHANNEL_RESET, BIT(reset_channel * 2 + reset_subch));
	enet_ग_लिखो(enet, ENET_DMA_CTRL_CHANNEL_RESET, 0);

	enet_ग_लिखो(enet, ring->cfg_block + ENET_DMA_CH_CFG, 0);
	enet_ग_लिखो(enet, ring->cfg_block + ENET_DMA_CH_CFG_MAX_BURST, ENET_DMA_MAX_BURST_LEN);
	enet_ग_लिखो(enet, ring->cfg_block + ENET_DMA_CH_CFG_INT_MASK, 0);

	enet_ग_लिखो(enet, ring->st_ram_block + ENET_DMA_CH_STATE_RAM_BASE_DESC_PTR,
		   (uपूर्णांक32_t)ring->dma_addr);
पूर्ण

अटल व्योम bcm4908_enet_dma_uninit(काष्ठा bcm4908_enet *enet)
अणु
	काष्ठा bcm4908_enet_dma_ring *rx_ring = &enet->rx_ring;
	काष्ठा bcm4908_enet_dma_ring_slot *slot;
	काष्ठा device *dev = enet->dev;
	पूर्णांक i;

	क्रम (i = rx_ring->length - 1; i >= 0; i--) अणु
		slot = &rx_ring->slots[i];
		अगर (!slot->skb)
			जारी;
		dma_unmap_single(dev, slot->dma_addr, slot->len, DMA_FROM_DEVICE);
		kमुक्त_skb(slot->skb);
		slot->skb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm4908_enet_dma_init(काष्ठा bcm4908_enet *enet)
अणु
	काष्ठा bcm4908_enet_dma_ring *rx_ring = &enet->rx_ring;
	काष्ठा device *dev = enet->dev;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < rx_ring->length; i++) अणु
		err = bcm4908_enet_dma_alloc_rx_buf(enet, i);
		अगर (err) अणु
			dev_err(dev, "Failed to alloc RX buffer: %d\n", err);
			bcm4908_enet_dma_uninit(enet);
			वापस err;
		पूर्ण
	पूर्ण

	bcm4908_enet_dma_ring_init(enet, &enet->tx_ring);
	bcm4908_enet_dma_ring_init(enet, &enet->rx_ring);

	वापस 0;
पूर्ण

अटल व्योम bcm4908_enet_dma_tx_ring_enable(काष्ठा bcm4908_enet *enet,
					    काष्ठा bcm4908_enet_dma_ring *ring)
अणु
	enet_ग_लिखो(enet, ring->cfg_block + ENET_DMA_CH_CFG, ENET_DMA_CH_CFG_ENABLE);
पूर्ण

अटल व्योम bcm4908_enet_dma_tx_ring_disable(काष्ठा bcm4908_enet *enet,
					     काष्ठा bcm4908_enet_dma_ring *ring)
अणु
	enet_ग_लिखो(enet, ring->cfg_block + ENET_DMA_CH_CFG, 0);
पूर्ण

अटल व्योम bcm4908_enet_dma_rx_ring_enable(काष्ठा bcm4908_enet *enet,
					    काष्ठा bcm4908_enet_dma_ring *ring)
अणु
	enet_set(enet, ring->cfg_block + ENET_DMA_CH_CFG, ENET_DMA_CH_CFG_ENABLE);
पूर्ण

अटल व्योम bcm4908_enet_dma_rx_ring_disable(काष्ठा bcm4908_enet *enet,
					     काष्ठा bcm4908_enet_dma_ring *ring)
अणु
	अचिन्हित दीर्घ deadline;
	u32 पंचांगp;

	enet_maskset(enet, ring->cfg_block + ENET_DMA_CH_CFG, ENET_DMA_CH_CFG_ENABLE, 0);

	deadline = jअगरfies + usecs_to_jअगरfies(2000);
	करो अणु
		पंचांगp = enet_पढ़ो(enet, ring->cfg_block + ENET_DMA_CH_CFG);
		अगर (!(पंचांगp & ENET_DMA_CH_CFG_ENABLE))
			वापस;
		enet_maskset(enet, ring->cfg_block + ENET_DMA_CH_CFG, ENET_DMA_CH_CFG_ENABLE, 0);
		usleep_range(10, 30);
	पूर्ण जबतक (!समय_after_eq(jअगरfies, deadline));

	dev_warn(enet->dev, "Timeout waiting for DMA TX stop\n");
पूर्ण

/***
 * Ethernet driver
 */

अटल व्योम bcm4908_enet_gmac_init(काष्ठा bcm4908_enet *enet)
अणु
	u32 cmd;

	bcm4908_enet_set_mtu(enet, enet->netdev->mtu);

	cmd = enet_umac_पढ़ो(enet, UMAC_CMD);
	enet_umac_ग_लिखो(enet, UMAC_CMD, cmd | CMD_SW_RESET);
	enet_umac_ग_लिखो(enet, UMAC_CMD, cmd & ~CMD_SW_RESET);

	enet_set(enet, ENET_FLUSH, ENET_FLUSH_RXFIFO_FLUSH | ENET_FLUSH_TXFIFO_FLUSH);
	enet_maskset(enet, ENET_FLUSH, ENET_FLUSH_RXFIFO_FLUSH | ENET_FLUSH_TXFIFO_FLUSH, 0);

	enet_set(enet, ENET_MIB_CTRL, ENET_MIB_CTRL_CLR_MIB);
	enet_maskset(enet, ENET_MIB_CTRL, ENET_MIB_CTRL_CLR_MIB, 0);

	cmd = enet_umac_पढ़ो(enet, UMAC_CMD);
	cmd &= ~(CMD_SPEED_MASK << CMD_SPEED_SHIFT);
	cmd &= ~CMD_TX_EN;
	cmd &= ~CMD_RX_EN;
	cmd |= CMD_SPEED_1000 << CMD_SPEED_SHIFT;
	enet_umac_ग_लिखो(enet, UMAC_CMD, cmd);

	enet_maskset(enet, ENET_GMAC_STATUS,
		     ENET_GMAC_STATUS_ETH_SPEED_MASK |
		     ENET_GMAC_STATUS_HD |
		     ENET_GMAC_STATUS_AUTO_CFG_EN |
		     ENET_GMAC_STATUS_LINK_UP,
		     ENET_GMAC_STATUS_ETH_SPEED_1000 |
		     ENET_GMAC_STATUS_AUTO_CFG_EN |
		     ENET_GMAC_STATUS_LINK_UP);
पूर्ण

अटल irqवापस_t bcm4908_enet_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm4908_enet *enet = dev_id;
	काष्ठा bcm4908_enet_dma_ring *ring;

	ring = (irq == enet->irq_tx) ? &enet->tx_ring : &enet->rx_ring;

	bcm4908_enet_dma_ring_पूर्णांकrs_off(enet, ring);
	bcm4908_enet_dma_ring_पूर्णांकrs_ack(enet, ring);

	napi_schedule(&ring->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm4908_enet_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा bcm4908_enet *enet = netdev_priv(netdev);
	काष्ठा bcm4908_enet_dma_ring *tx_ring = &enet->tx_ring;
	काष्ठा bcm4908_enet_dma_ring *rx_ring = &enet->rx_ring;
	काष्ठा device *dev = enet->dev;
	पूर्णांक err;

	err = request_irq(netdev->irq, bcm4908_enet_irq_handler, 0, "enet", enet);
	अगर (err) अणु
		dev_err(dev, "Failed to request IRQ %d: %d\n", netdev->irq, err);
		वापस err;
	पूर्ण

	अगर (enet->irq_tx > 0) अणु
		err = request_irq(enet->irq_tx, bcm4908_enet_irq_handler, 0,
				  "tx", enet);
		अगर (err) अणु
			dev_err(dev, "Failed to request IRQ %d: %d\n",
				enet->irq_tx, err);
			मुक्त_irq(netdev->irq, enet);
			वापस err;
		पूर्ण
	पूर्ण

	bcm4908_enet_gmac_init(enet);
	bcm4908_enet_dma_reset(enet);
	bcm4908_enet_dma_init(enet);

	enet_umac_set(enet, UMAC_CMD, CMD_TX_EN | CMD_RX_EN);

	enet_set(enet, ENET_DMA_CONTROLLER_CFG, ENET_DMA_CTRL_CFG_MASTER_EN);
	enet_maskset(enet, ENET_DMA_CONTROLLER_CFG, ENET_DMA_CTRL_CFG_FLOWC_CH1_EN, 0);

	अगर (enet->irq_tx > 0) अणु
		napi_enable(&tx_ring->napi);
		bcm4908_enet_dma_ring_पूर्णांकrs_ack(enet, tx_ring);
		bcm4908_enet_dma_ring_पूर्णांकrs_on(enet, tx_ring);
	पूर्ण

	bcm4908_enet_dma_rx_ring_enable(enet, rx_ring);
	napi_enable(&rx_ring->napi);
	netअगर_carrier_on(netdev);
	netअगर_start_queue(netdev);
	bcm4908_enet_dma_ring_पूर्णांकrs_ack(enet, rx_ring);
	bcm4908_enet_dma_ring_पूर्णांकrs_on(enet, rx_ring);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm4908_enet_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा bcm4908_enet *enet = netdev_priv(netdev);
	काष्ठा bcm4908_enet_dma_ring *tx_ring = &enet->tx_ring;
	काष्ठा bcm4908_enet_dma_ring *rx_ring = &enet->rx_ring;

	netअगर_stop_queue(netdev);
	netअगर_carrier_off(netdev);
	napi_disable(&rx_ring->napi);
	napi_disable(&tx_ring->napi);

	bcm4908_enet_dma_rx_ring_disable(enet, &enet->rx_ring);
	bcm4908_enet_dma_tx_ring_disable(enet, &enet->tx_ring);

	bcm4908_enet_dma_uninit(enet);

	मुक्त_irq(enet->irq_tx, enet);
	मुक्त_irq(enet->netdev->irq, enet);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm4908_enet_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा bcm4908_enet *enet = netdev_priv(netdev);
	काष्ठा bcm4908_enet_dma_ring *ring = &enet->tx_ring;
	काष्ठा bcm4908_enet_dma_ring_slot *slot;
	काष्ठा device *dev = enet->dev;
	काष्ठा bcm4908_enet_dma_ring_bd *buf_desc;
	पूर्णांक मुक्त_buf_descs;
	u32 पंचांगp;

	/* Free transmitted skbs */
	अगर (enet->irq_tx < 0 &&
	    !(le32_to_cpu(ring->buf_desc[ring->पढ़ो_idx].ctl) & DMA_CTL_STATUS_OWN))
		napi_schedule(&enet->tx_ring.napi);

	/* Don't use the last empty buf descriptor */
	अगर (ring->पढ़ो_idx <= ring->ग_लिखो_idx)
		मुक्त_buf_descs = ring->पढ़ो_idx - ring->ग_लिखो_idx + ring->length;
	अन्यथा
		मुक्त_buf_descs = ring->पढ़ो_idx - ring->ग_लिखो_idx;
	अगर (मुक्त_buf_descs < 2) अणु
		netअगर_stop_queue(netdev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* Hardware हटाओs OWN bit after sending data */
	buf_desc = &ring->buf_desc[ring->ग_लिखो_idx];
	अगर (unlikely(le32_to_cpu(buf_desc->ctl) & DMA_CTL_STATUS_OWN)) अणु
		netअगर_stop_queue(netdev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	slot = &ring->slots[ring->ग_लिखो_idx];
	slot->skb = skb;
	slot->len = skb->len;
	slot->dma_addr = dma_map_single(dev, skb->data, skb->len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, slot->dma_addr)))
		वापस NETDEV_TX_BUSY;

	पंचांगp = skb->len << DMA_CTL_LEN_DESC_BUFLENGTH_SHIFT;
	पंचांगp |= DMA_CTL_STATUS_OWN;
	पंचांगp |= DMA_CTL_STATUS_SOP;
	पंचांगp |= DMA_CTL_STATUS_EOP;
	पंचांगp |= DMA_CTL_STATUS_APPEND_CRC;
	अगर (ring->ग_लिखो_idx + 1 == ring->length - 1)
		पंचांगp |= DMA_CTL_STATUS_WRAP;

	buf_desc->addr = cpu_to_le32((uपूर्णांक32_t)slot->dma_addr);
	buf_desc->ctl = cpu_to_le32(पंचांगp);

	bcm4908_enet_dma_tx_ring_enable(enet, &enet->tx_ring);

	अगर (++ring->ग_लिखो_idx == ring->length - 1)
		ring->ग_लिखो_idx = 0;
	enet->netdev->stats.tx_bytes += skb->len;
	enet->netdev->stats.tx_packets++;

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक bcm4908_enet_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक weight)
अणु
	काष्ठा bcm4908_enet_dma_ring *rx_ring = container_of(napi, काष्ठा bcm4908_enet_dma_ring, napi);
	काष्ठा bcm4908_enet *enet = container_of(rx_ring, काष्ठा bcm4908_enet, rx_ring);
	काष्ठा device *dev = enet->dev;
	पूर्णांक handled = 0;

	जबतक (handled < weight) अणु
		काष्ठा bcm4908_enet_dma_ring_bd *buf_desc;
		काष्ठा bcm4908_enet_dma_ring_slot slot;
		u32 ctl;
		पूर्णांक len;
		पूर्णांक err;

		buf_desc = &enet->rx_ring.buf_desc[enet->rx_ring.पढ़ो_idx];
		ctl = le32_to_cpu(buf_desc->ctl);
		अगर (ctl & DMA_CTL_STATUS_OWN)
			अवरोध;

		slot = enet->rx_ring.slots[enet->rx_ring.पढ़ो_idx];

		/* Provide new buffer beक्रमe unpinning the old one */
		err = bcm4908_enet_dma_alloc_rx_buf(enet, enet->rx_ring.पढ़ो_idx);
		अगर (err)
			अवरोध;

		अगर (++enet->rx_ring.पढ़ो_idx == enet->rx_ring.length)
			enet->rx_ring.पढ़ो_idx = 0;

		len = (ctl & DMA_CTL_LEN_DESC_BUFLENGTH) >> DMA_CTL_LEN_DESC_BUFLENGTH_SHIFT;

		अगर (len < ETH_ZLEN ||
		    (ctl & (DMA_CTL_STATUS_SOP | DMA_CTL_STATUS_EOP)) != (DMA_CTL_STATUS_SOP | DMA_CTL_STATUS_EOP)) अणु
			kमुक्त_skb(slot.skb);
			enet->netdev->stats.rx_dropped++;
			अवरोध;
		पूर्ण

		dma_unmap_single(dev, slot.dma_addr, slot.len, DMA_FROM_DEVICE);

		skb_put(slot.skb, len - ETH_FCS_LEN);
		slot.skb->protocol = eth_type_trans(slot.skb, enet->netdev);
		netअगर_receive_skb(slot.skb);

		enet->netdev->stats.rx_packets++;
		enet->netdev->stats.rx_bytes += len;

		handled++;
	पूर्ण

	अगर (handled < weight) अणु
		napi_complete_करोne(napi, handled);
		bcm4908_enet_dma_ring_पूर्णांकrs_on(enet, rx_ring);
	पूर्ण

	/* Hardware could disable ring अगर it run out of descriptors */
	bcm4908_enet_dma_rx_ring_enable(enet, &enet->rx_ring);

	वापस handled;
पूर्ण

अटल पूर्णांक bcm4908_enet_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक weight)
अणु
	काष्ठा bcm4908_enet_dma_ring *tx_ring = container_of(napi, काष्ठा bcm4908_enet_dma_ring, napi);
	काष्ठा bcm4908_enet *enet = container_of(tx_ring, काष्ठा bcm4908_enet, tx_ring);
	काष्ठा bcm4908_enet_dma_ring_bd *buf_desc;
	काष्ठा bcm4908_enet_dma_ring_slot *slot;
	काष्ठा device *dev = enet->dev;
	अचिन्हित पूर्णांक bytes = 0;
	पूर्णांक handled = 0;

	जबतक (handled < weight && tx_ring->पढ़ो_idx != tx_ring->ग_लिखो_idx) अणु
		buf_desc = &tx_ring->buf_desc[tx_ring->पढ़ो_idx];
		अगर (le32_to_cpu(buf_desc->ctl) & DMA_CTL_STATUS_OWN)
			अवरोध;
		slot = &tx_ring->slots[tx_ring->पढ़ो_idx];

		dma_unmap_single(dev, slot->dma_addr, slot->len, DMA_TO_DEVICE);
		dev_kमुक्त_skb(slot->skb);
		bytes += slot->len;
		अगर (++tx_ring->पढ़ो_idx == tx_ring->length)
			tx_ring->पढ़ो_idx = 0;

		handled++;
	पूर्ण

	अगर (handled < weight) अणु
		napi_complete_करोne(napi, handled);
		bcm4908_enet_dma_ring_पूर्णांकrs_on(enet, tx_ring);
	पूर्ण

	अगर (netअगर_queue_stopped(enet->netdev))
		netअगर_wake_queue(enet->netdev);

	वापस handled;
पूर्ण

अटल पूर्णांक bcm4908_enet_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा bcm4908_enet *enet = netdev_priv(netdev);

	bcm4908_enet_set_mtu(enet, new_mtu);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops bcm4908_enet_netdev_ops = अणु
	.nकरो_खोलो = bcm4908_enet_खोलो,
	.nकरो_stop = bcm4908_enet_stop,
	.nकरो_start_xmit = bcm4908_enet_start_xmit,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_change_mtu = bcm4908_enet_change_mtu,
पूर्ण;

अटल पूर्णांक bcm4908_enet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *netdev;
	काष्ठा bcm4908_enet *enet;
	पूर्णांक err;

	netdev = devm_alloc_etherdev(dev, माप(*enet));
	अगर (!netdev)
		वापस -ENOMEM;

	enet = netdev_priv(netdev);
	enet->dev = dev;
	enet->netdev = netdev;

	enet->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(enet->base)) अणु
		dev_err(dev, "Failed to map registers: %ld\n", PTR_ERR(enet->base));
		वापस PTR_ERR(enet->base);
	पूर्ण

	netdev->irq = platक्रमm_get_irq_byname(pdev, "rx");
	अगर (netdev->irq < 0)
		वापस netdev->irq;

	enet->irq_tx = platक्रमm_get_irq_byname(pdev, "tx");

	dma_set_coherent_mask(dev, DMA_BIT_MASK(32));

	err = bcm4908_enet_dma_alloc(enet);
	अगर (err)
		वापस err;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	err = of_get_mac_address(dev->of_node, netdev->dev_addr);
	अगर (err)
		eth_hw_addr_अक्रमom(netdev);
	netdev->netdev_ops = &bcm4908_enet_netdev_ops;
	netdev->min_mtu = ETH_ZLEN;
	netdev->mtu = ETH_DATA_LEN;
	netdev->max_mtu = ENET_MTU_MAX;
	netअगर_tx_napi_add(netdev, &enet->tx_ring.napi, bcm4908_enet_poll_tx, NAPI_POLL_WEIGHT);
	netअगर_napi_add(netdev, &enet->rx_ring.napi, bcm4908_enet_poll_rx, NAPI_POLL_WEIGHT);

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		bcm4908_enet_dma_मुक्त(enet);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, enet);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm4908_enet_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm4908_enet *enet = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_netdev(enet->netdev);
	netअगर_napi_del(&enet->rx_ring.napi);
	netअगर_napi_del(&enet->tx_ring.napi);
	bcm4908_enet_dma_मुक्त(enet);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm4908_enet_of_match[] = अणु
	अणु .compatible = "brcm,bcm4908-enet"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm4908_enet_driver = अणु
	.driver = अणु
		.name = "bcm4908_enet",
		.of_match_table = bcm4908_enet_of_match,
	पूर्ण,
	.probe	= bcm4908_enet_probe,
	.हटाओ = bcm4908_enet_हटाओ,
पूर्ण;
module_platक्रमm_driver(bcm4908_enet_driver);

MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, bcm4908_enet_of_match);
