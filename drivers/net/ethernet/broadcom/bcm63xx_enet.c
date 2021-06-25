<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम BCM963xx builtin Ethernet mac
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/err.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <bcm63xx_dev_enet.h>
#समावेश "bcm63xx_enet.h"

अटल अक्षर bcm_enet_driver_name[] = "bcm63xx_enet";

अटल पूर्णांक copyअवरोध __पढ़ो_mostly = 128;
module_param(copyअवरोध, पूर्णांक, 0);
MODULE_PARM_DESC(copyअवरोध, "Receive copy threshold");

/* io रेजिस्टरs memory shared between all devices */
अटल व्योम __iomem *bcm_enet_shared_base[3];

/*
 * io helpers to access mac रेजिस्टरs
 */
अटल अंतरभूत u32 enet_पढ़ोl(काष्ठा bcm_enet_priv *priv, u32 off)
अणु
	वापस bcm_पढ़ोl(priv->base + off);
पूर्ण

अटल अंतरभूत व्योम enet_ग_लिखोl(काष्ठा bcm_enet_priv *priv,
			       u32 val, u32 off)
अणु
	bcm_ग_लिखोl(val, priv->base + off);
पूर्ण

/*
 * io helpers to access चयन रेजिस्टरs
 */
अटल अंतरभूत u32 enetsw_पढ़ोl(काष्ठा bcm_enet_priv *priv, u32 off)
अणु
	वापस bcm_पढ़ोl(priv->base + off);
पूर्ण

अटल अंतरभूत व्योम enetsw_ग_लिखोl(काष्ठा bcm_enet_priv *priv,
				 u32 val, u32 off)
अणु
	bcm_ग_लिखोl(val, priv->base + off);
पूर्ण

अटल अंतरभूत u16 enetsw_पढ़ोw(काष्ठा bcm_enet_priv *priv, u32 off)
अणु
	वापस bcm_पढ़ोw(priv->base + off);
पूर्ण

अटल अंतरभूत व्योम enetsw_ग_लिखोw(काष्ठा bcm_enet_priv *priv,
				 u16 val, u32 off)
अणु
	bcm_ग_लिखोw(val, priv->base + off);
पूर्ण

अटल अंतरभूत u8 enetsw_पढ़ोb(काष्ठा bcm_enet_priv *priv, u32 off)
अणु
	वापस bcm_पढ़ोb(priv->base + off);
पूर्ण

अटल अंतरभूत व्योम enetsw_ग_लिखोb(काष्ठा bcm_enet_priv *priv,
				 u8 val, u32 off)
अणु
	bcm_ग_लिखोb(val, priv->base + off);
पूर्ण


/* io helpers to access shared रेजिस्टरs */
अटल अंतरभूत u32 enet_dma_पढ़ोl(काष्ठा bcm_enet_priv *priv, u32 off)
अणु
	वापस bcm_पढ़ोl(bcm_enet_shared_base[0] + off);
पूर्ण

अटल अंतरभूत व्योम enet_dma_ग_लिखोl(काष्ठा bcm_enet_priv *priv,
				       u32 val, u32 off)
अणु
	bcm_ग_लिखोl(val, bcm_enet_shared_base[0] + off);
पूर्ण

अटल अंतरभूत u32 enet_dmac_पढ़ोl(काष्ठा bcm_enet_priv *priv, u32 off, पूर्णांक chan)
अणु
	वापस bcm_पढ़ोl(bcm_enet_shared_base[1] +
		bcm63xx_enetdmacreg(off) + chan * priv->dma_chan_width);
पूर्ण

अटल अंतरभूत व्योम enet_dmac_ग_लिखोl(काष्ठा bcm_enet_priv *priv,
				       u32 val, u32 off, पूर्णांक chan)
अणु
	bcm_ग_लिखोl(val, bcm_enet_shared_base[1] +
		bcm63xx_enetdmacreg(off) + chan * priv->dma_chan_width);
पूर्ण

अटल अंतरभूत u32 enet_dmas_पढ़ोl(काष्ठा bcm_enet_priv *priv, u32 off, पूर्णांक chan)
अणु
	वापस bcm_पढ़ोl(bcm_enet_shared_base[2] + off + chan * priv->dma_chan_width);
पूर्ण

अटल अंतरभूत व्योम enet_dmas_ग_लिखोl(काष्ठा bcm_enet_priv *priv,
				       u32 val, u32 off, पूर्णांक chan)
अणु
	bcm_ग_लिखोl(val, bcm_enet_shared_base[2] + off + chan * priv->dma_chan_width);
पूर्ण

/*
 * ग_लिखो given data पूर्णांकo mii रेजिस्टर and रुको क्रम transfer to end
 * with समयout (average measured transfer समय is 25us)
 */
अटल पूर्णांक करो_mdio_op(काष्ठा bcm_enet_priv *priv, अचिन्हित पूर्णांक data)
अणु
	पूर्णांक limit;

	/* make sure mii पूर्णांकerrupt status is cleared */
	enet_ग_लिखोl(priv, ENET_IR_MII, ENET_IR_REG);

	enet_ग_लिखोl(priv, data, ENET_MIIDATA_REG);
	wmb();

	/* busy रुको on mii पूर्णांकerrupt bit, with समयout */
	limit = 1000;
	करो अणु
		अगर (enet_पढ़ोl(priv, ENET_IR_REG) & ENET_IR_MII)
			अवरोध;
		udelay(1);
	पूर्ण जबतक (limit-- > 0);

	वापस (limit < 0) ? 1 : 0;
पूर्ण

/*
 * MII पूर्णांकernal पढ़ो callback
 */
अटल पूर्णांक bcm_enet_mdio_पढ़ो(काष्ठा bcm_enet_priv *priv, पूर्णांक mii_id,
			      पूर्णांक regnum)
अणु
	u32 पंचांगp, val;

	पंचांगp = regnum << ENET_MIIDATA_REG_SHIFT;
	पंचांगp |= 0x2 << ENET_MIIDATA_TA_SHIFT;
	पंचांगp |= mii_id << ENET_MIIDATA_PHYID_SHIFT;
	पंचांगp |= ENET_MIIDATA_OP_READ_MASK;

	अगर (करो_mdio_op(priv, पंचांगp))
		वापस -1;

	val = enet_पढ़ोl(priv, ENET_MIIDATA_REG);
	val &= 0xffff;
	वापस val;
पूर्ण

/*
 * MII पूर्णांकernal ग_लिखो callback
 */
अटल पूर्णांक bcm_enet_mdio_ग_लिखो(काष्ठा bcm_enet_priv *priv, पूर्णांक mii_id,
			       पूर्णांक regnum, u16 value)
अणु
	u32 पंचांगp;

	पंचांगp = (value & 0xffff) << ENET_MIIDATA_DATA_SHIFT;
	पंचांगp |= 0x2 << ENET_MIIDATA_TA_SHIFT;
	पंचांगp |= regnum << ENET_MIIDATA_REG_SHIFT;
	पंचांगp |= mii_id << ENET_MIIDATA_PHYID_SHIFT;
	पंचांगp |= ENET_MIIDATA_OP_WRITE_MASK;

	(व्योम)करो_mdio_op(priv, पंचांगp);
	वापस 0;
पूर्ण

/*
 * MII पढ़ो callback from phylib
 */
अटल पूर्णांक bcm_enet_mdio_पढ़ो_phylib(काष्ठा mii_bus *bus, पूर्णांक mii_id,
				     पूर्णांक regnum)
अणु
	वापस bcm_enet_mdio_पढ़ो(bus->priv, mii_id, regnum);
पूर्ण

/*
 * MII ग_लिखो callback from phylib
 */
अटल पूर्णांक bcm_enet_mdio_ग_लिखो_phylib(काष्ठा mii_bus *bus, पूर्णांक mii_id,
				      पूर्णांक regnum, u16 value)
अणु
	वापस bcm_enet_mdio_ग_लिखो(bus->priv, mii_id, regnum, value);
पूर्ण

/*
 * MII पढ़ो callback from mii core
 */
अटल पूर्णांक bcm_enet_mdio_पढ़ो_mii(काष्ठा net_device *dev, पूर्णांक mii_id,
				  पूर्णांक regnum)
अणु
	वापस bcm_enet_mdio_पढ़ो(netdev_priv(dev), mii_id, regnum);
पूर्ण

/*
 * MII ग_लिखो callback from mii core
 */
अटल व्योम bcm_enet_mdio_ग_लिखो_mii(काष्ठा net_device *dev, पूर्णांक mii_id,
				    पूर्णांक regnum, पूर्णांक value)
अणु
	bcm_enet_mdio_ग_लिखो(netdev_priv(dev), mii_id, regnum, value);
पूर्ण

/*
 * refill rx queue
 */
अटल पूर्णांक bcm_enet_refill_rx(काष्ठा net_device *dev, bool napi_mode)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);

	जबतक (priv->rx_desc_count < priv->rx_ring_size) अणु
		काष्ठा bcm_enet_desc *desc;
		पूर्णांक desc_idx;
		u32 len_stat;

		desc_idx = priv->rx_dirty_desc;
		desc = &priv->rx_desc_cpu[desc_idx];

		अगर (!priv->rx_buf[desc_idx]) अणु
			व्योम *buf;

			अगर (likely(napi_mode))
				buf = napi_alloc_frag(priv->rx_frag_size);
			अन्यथा
				buf = netdev_alloc_frag(priv->rx_frag_size);
			अगर (unlikely(!buf))
				अवरोध;
			priv->rx_buf[desc_idx] = buf;
			desc->address = dma_map_single(&priv->pdev->dev,
						       buf + priv->rx_buf_offset,
						       priv->rx_buf_size,
						       DMA_FROM_DEVICE);
		पूर्ण

		len_stat = priv->rx_buf_size << DMADESC_LENGTH_SHIFT;
		len_stat |= DMADESC_OWNER_MASK;
		अगर (priv->rx_dirty_desc == priv->rx_ring_size - 1) अणु
			len_stat |= (DMADESC_WRAP_MASK >> priv->dma_desc_shअगरt);
			priv->rx_dirty_desc = 0;
		पूर्ण अन्यथा अणु
			priv->rx_dirty_desc++;
		पूर्ण
		wmb();
		desc->len_stat = len_stat;

		priv->rx_desc_count++;

		/* tell dma engine we allocated one buffer */
		अगर (priv->dma_has_sram)
			enet_dma_ग_लिखोl(priv, 1, ENETDMA_BUFALLOC_REG(priv->rx_chan));
		अन्यथा
			enet_dmac_ग_लिखोl(priv, 1, ENETDMAC_BUFALLOC, priv->rx_chan);
	पूर्ण

	/* If rx ring is still empty, set a समयr to try allocating
	 * again at a later समय. */
	अगर (priv->rx_desc_count == 0 && netअगर_running(dev)) अणु
		dev_warn(&priv->pdev->dev, "unable to refill rx ring\n");
		priv->rx_समयout.expires = jअगरfies + HZ;
		add_समयr(&priv->rx_समयout);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * समयr callback to defer refill rx queue in हाल we're OOM
 */
अटल व्योम bcm_enet_refill_rx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bcm_enet_priv *priv = from_समयr(priv, t, rx_समयout);
	काष्ठा net_device *dev = priv->net_dev;

	spin_lock(&priv->rx_lock);
	bcm_enet_refill_rx(dev, false);
	spin_unlock(&priv->rx_lock);
पूर्ण

/*
 * extract packet from rx queue
 */
अटल पूर्णांक bcm_enet_receive_queue(काष्ठा net_device *dev, पूर्णांक budget)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा list_head rx_list;
	काष्ठा device *kdev;
	पूर्णांक processed;

	priv = netdev_priv(dev);
	INIT_LIST_HEAD(&rx_list);
	kdev = &priv->pdev->dev;
	processed = 0;

	/* करोn't scan ring further than number of refilled
	 * descriptor */
	अगर (budget > priv->rx_desc_count)
		budget = priv->rx_desc_count;

	करो अणु
		काष्ठा bcm_enet_desc *desc;
		काष्ठा sk_buff *skb;
		पूर्णांक desc_idx;
		u32 len_stat;
		अचिन्हित पूर्णांक len;
		व्योम *buf;

		desc_idx = priv->rx_curr_desc;
		desc = &priv->rx_desc_cpu[desc_idx];

		/* make sure we actually पढ़ो the descriptor status at
		 * each loop */
		rmb();

		len_stat = desc->len_stat;

		/* अवरोध अगर dma ownership beदीर्घs to hw */
		अगर (len_stat & DMADESC_OWNER_MASK)
			अवरोध;

		processed++;
		priv->rx_curr_desc++;
		अगर (priv->rx_curr_desc == priv->rx_ring_size)
			priv->rx_curr_desc = 0;

		/* अगर the packet करोes not have start of packet _and_
		 * end of packet flag set, then just recycle it */
		अगर ((len_stat & (DMADESC_ESOP_MASK >> priv->dma_desc_shअगरt)) !=
			(DMADESC_ESOP_MASK >> priv->dma_desc_shअगरt)) अणु
			dev->stats.rx_dropped++;
			जारी;
		पूर्ण

		/* recycle packet अगर it's marked as bad */
		अगर (!priv->enet_is_sw &&
		    unlikely(len_stat & DMADESC_ERR_MASK)) अणु
			dev->stats.rx_errors++;

			अगर (len_stat & DMADESC_OVSIZE_MASK)
				dev->stats.rx_length_errors++;
			अगर (len_stat & DMADESC_CRC_MASK)
				dev->stats.rx_crc_errors++;
			अगर (len_stat & DMADESC_UNDER_MASK)
				dev->stats.rx_frame_errors++;
			अगर (len_stat & DMADESC_OV_MASK)
				dev->stats.rx_fअगरo_errors++;
			जारी;
		पूर्ण

		/* valid packet */
		buf = priv->rx_buf[desc_idx];
		len = (len_stat & DMADESC_LENGTH_MASK) >> DMADESC_LENGTH_SHIFT;
		/* करोn't include FCS */
		len -= 4;

		अगर (len < copyअवरोध) अणु
			skb = napi_alloc_skb(&priv->napi, len);
			अगर (unlikely(!skb)) अणु
				/* क्रमget packet, just rearm desc */
				dev->stats.rx_dropped++;
				जारी;
			पूर्ण

			dma_sync_single_क्रम_cpu(kdev, desc->address,
						len, DMA_FROM_DEVICE);
			स_नकल(skb->data, buf + priv->rx_buf_offset, len);
			dma_sync_single_क्रम_device(kdev, desc->address,
						   len, DMA_FROM_DEVICE);
		पूर्ण अन्यथा अणु
			dma_unmap_single(kdev, desc->address,
					 priv->rx_buf_size, DMA_FROM_DEVICE);
			priv->rx_buf[desc_idx] = शून्य;

			skb = build_skb(buf, priv->rx_frag_size);
			अगर (unlikely(!skb)) अणु
				skb_मुक्त_frag(buf);
				dev->stats.rx_dropped++;
				जारी;
			पूर्ण
			skb_reserve(skb, priv->rx_buf_offset);
		पूर्ण

		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, dev);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += len;
		list_add_tail(&skb->list, &rx_list);

	पूर्ण जबतक (processed < budget);

	netअगर_receive_skb_list(&rx_list);
	priv->rx_desc_count -= processed;

	अगर (processed || !priv->rx_desc_count) अणु
		bcm_enet_refill_rx(dev, true);

		/* kick rx dma */
		enet_dmac_ग_लिखोl(priv, priv->dma_chan_en_mask,
					 ENETDMAC_CHANCFG, priv->rx_chan);
	पूर्ण

	वापस processed;
पूर्ण


/*
 * try to or क्रमce reclaim of transmitted buffers
 */
अटल पूर्णांक bcm_enet_tx_reclaim(काष्ठा net_device *dev, पूर्णांक क्रमce)
अणु
	काष्ठा bcm_enet_priv *priv;
	अचिन्हित पूर्णांक bytes;
	पूर्णांक released;

	priv = netdev_priv(dev);
	bytes = 0;
	released = 0;

	जबतक (priv->tx_desc_count < priv->tx_ring_size) अणु
		काष्ठा bcm_enet_desc *desc;
		काष्ठा sk_buff *skb;

		/* We run in a bh and fight against start_xmit, which
		 * is called with bh disabled  */
		spin_lock(&priv->tx_lock);

		desc = &priv->tx_desc_cpu[priv->tx_dirty_desc];

		अगर (!क्रमce && (desc->len_stat & DMADESC_OWNER_MASK)) अणु
			spin_unlock(&priv->tx_lock);
			अवरोध;
		पूर्ण

		/* ensure other field of the descriptor were not पढ़ो
		 * beक्रमe we checked ownership */
		rmb();

		skb = priv->tx_skb[priv->tx_dirty_desc];
		priv->tx_skb[priv->tx_dirty_desc] = शून्य;
		dma_unmap_single(&priv->pdev->dev, desc->address, skb->len,
				 DMA_TO_DEVICE);

		priv->tx_dirty_desc++;
		अगर (priv->tx_dirty_desc == priv->tx_ring_size)
			priv->tx_dirty_desc = 0;
		priv->tx_desc_count++;

		spin_unlock(&priv->tx_lock);

		अगर (desc->len_stat & DMADESC_UNDER_MASK)
			dev->stats.tx_errors++;

		bytes += skb->len;
		dev_kमुक्त_skb(skb);
		released++;
	पूर्ण

	netdev_completed_queue(dev, released, bytes);

	अगर (netअगर_queue_stopped(dev) && released)
		netअगर_wake_queue(dev);

	वापस released;
पूर्ण

/*
 * poll func, called by network core
 */
अटल पूर्णांक bcm_enet_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा net_device *dev;
	पूर्णांक rx_work_करोne;

	priv = container_of(napi, काष्ठा bcm_enet_priv, napi);
	dev = priv->net_dev;

	/* ack पूर्णांकerrupts */
	enet_dmac_ग_लिखोl(priv, priv->dma_chan_पूर्णांक_mask,
			 ENETDMAC_IR, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, priv->dma_chan_पूर्णांक_mask,
			 ENETDMAC_IR, priv->tx_chan);

	/* reclaim sent skb */
	bcm_enet_tx_reclaim(dev, 0);

	spin_lock(&priv->rx_lock);
	rx_work_करोne = bcm_enet_receive_queue(dev, budget);
	spin_unlock(&priv->rx_lock);

	अगर (rx_work_करोne >= budget) अणु
		/* rx queue is not yet empty/clean */
		वापस rx_work_करोne;
	पूर्ण

	/* no more packet in rx/tx queue, हटाओ device from poll
	 * queue */
	napi_complete_करोne(napi, rx_work_करोne);

	/* restore rx/tx पूर्णांकerrupt */
	enet_dmac_ग_लिखोl(priv, priv->dma_chan_पूर्णांक_mask,
			 ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, priv->dma_chan_पूर्णांक_mask,
			 ENETDMAC_IRMASK, priv->tx_chan);

	वापस rx_work_करोne;
पूर्ण

/*
 * mac पूर्णांकerrupt handler
 */
अटल irqवापस_t bcm_enet_isr_mac(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev;
	काष्ठा bcm_enet_priv *priv;
	u32 stat;

	dev = dev_id;
	priv = netdev_priv(dev);

	stat = enet_पढ़ोl(priv, ENET_IR_REG);
	अगर (!(stat & ENET_IR_MIB))
		वापस IRQ_NONE;

	/* clear & mask पूर्णांकerrupt */
	enet_ग_लिखोl(priv, ENET_IR_MIB, ENET_IR_REG);
	enet_ग_लिखोl(priv, 0, ENET_IRMASK_REG);

	/* पढ़ो mib रेजिस्टरs in workqueue */
	schedule_work(&priv->mib_update_task);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * rx/tx dma पूर्णांकerrupt handler
 */
अटल irqवापस_t bcm_enet_isr_dma(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev;
	काष्ठा bcm_enet_priv *priv;

	dev = dev_id;
	priv = netdev_priv(dev);

	/* mask rx/tx पूर्णांकerrupts */
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->tx_chan);

	napi_schedule(&priv->napi);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * tx request callback
 */
अटल netdev_tx_t
bcm_enet_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा bcm_enet_desc *desc;
	u32 len_stat;
	netdev_tx_t ret;

	priv = netdev_priv(dev);

	/* lock against tx reclaim */
	spin_lock(&priv->tx_lock);

	/* make sure  the tx hw queue  is not full,  should not happen
	 * since we stop queue beक्रमe it's the हाल */
	अगर (unlikely(!priv->tx_desc_count)) अणु
		netअगर_stop_queue(dev);
		dev_err(&priv->pdev->dev, "xmit called with no tx desc "
			"available?\n");
		ret = NETDEV_TX_BUSY;
		जाओ out_unlock;
	पूर्ण

	/* pad small packets sent on a चयन device */
	अगर (priv->enet_is_sw && skb->len < 64) अणु
		पूर्णांक needed = 64 - skb->len;
		अक्षर *data;

		अगर (unlikely(skb_tailroom(skb) < needed)) अणु
			काष्ठा sk_buff *nskb;

			nskb = skb_copy_expand(skb, 0, needed, GFP_ATOMIC);
			अगर (!nskb) अणु
				ret = NETDEV_TX_BUSY;
				जाओ out_unlock;
			पूर्ण
			dev_kमुक्त_skb(skb);
			skb = nskb;
		पूर्ण
		data = skb_put_zero(skb, needed);
	पूर्ण

	/* poपूर्णांक to the next available desc */
	desc = &priv->tx_desc_cpu[priv->tx_curr_desc];
	priv->tx_skb[priv->tx_curr_desc] = skb;

	/* fill descriptor */
	desc->address = dma_map_single(&priv->pdev->dev, skb->data, skb->len,
				       DMA_TO_DEVICE);

	len_stat = (skb->len << DMADESC_LENGTH_SHIFT) & DMADESC_LENGTH_MASK;
	len_stat |= (DMADESC_ESOP_MASK >> priv->dma_desc_shअगरt) |
		DMADESC_APPEND_CRC |
		DMADESC_OWNER_MASK;

	priv->tx_curr_desc++;
	अगर (priv->tx_curr_desc == priv->tx_ring_size) अणु
		priv->tx_curr_desc = 0;
		len_stat |= (DMADESC_WRAP_MASK >> priv->dma_desc_shअगरt);
	पूर्ण
	priv->tx_desc_count--;

	/* dma might be alपढ़ोy polling, make sure we update desc
	 * fields in correct order */
	wmb();
	desc->len_stat = len_stat;
	wmb();

	netdev_sent_queue(dev, skb->len);

	/* kick tx dma */
	अगर (!netdev_xmit_more() || !priv->tx_desc_count)
		enet_dmac_ग_लिखोl(priv, priv->dma_chan_en_mask,
				 ENETDMAC_CHANCFG, priv->tx_chan);

	/* stop queue अगर no more desc available */
	अगर (!priv->tx_desc_count)
		netअगर_stop_queue(dev);

	dev->stats.tx_bytes += skb->len;
	dev->stats.tx_packets++;
	ret = NETDEV_TX_OK;

out_unlock:
	spin_unlock(&priv->tx_lock);
	वापस ret;
पूर्ण

/*
 * Change the पूर्णांकerface's mac address.
 */
अटल पूर्णांक bcm_enet_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा sockaddr *addr = p;
	u32 val;

	priv = netdev_priv(dev);
	स_नकल(dev->dev_addr, addr->sa_data, ETH_ALEN);

	/* use perfect match रेजिस्टर 0 to store my mac address */
	val = (dev->dev_addr[2] << 24) | (dev->dev_addr[3] << 16) |
		(dev->dev_addr[4] << 8) | dev->dev_addr[5];
	enet_ग_लिखोl(priv, val, ENET_PML_REG(0));

	val = (dev->dev_addr[0] << 8 | dev->dev_addr[1]);
	val |= ENET_PMH_DATAVALID_MASK;
	enet_ग_लिखोl(priv, val, ENET_PMH_REG(0));

	वापस 0;
पूर्ण

/*
 * Change rx mode (promiscuous/allmulti) and update multicast list
 */
अटल व्योम bcm_enet_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा netdev_hw_addr *ha;
	u32 val;
	पूर्णांक i;

	priv = netdev_priv(dev);

	val = enet_पढ़ोl(priv, ENET_RXCFG_REG);

	अगर (dev->flags & IFF_PROMISC)
		val |= ENET_RXCFG_PROMISC_MASK;
	अन्यथा
		val &= ~ENET_RXCFG_PROMISC_MASK;

	/* only 3 perfect match रेजिस्टरs left, first one is used क्रम
	 * own mac address */
	अगर ((dev->flags & IFF_ALLMULTI) || netdev_mc_count(dev) > 3)
		val |= ENET_RXCFG_ALLMCAST_MASK;
	अन्यथा
		val &= ~ENET_RXCFG_ALLMCAST_MASK;

	/* no need to set perfect match रेजिस्टरs अगर we catch all
	 * multicast */
	अगर (val & ENET_RXCFG_ALLMCAST_MASK) अणु
		enet_ग_लिखोl(priv, val, ENET_RXCFG_REG);
		वापस;
	पूर्ण

	i = 0;
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		u8 *dmi_addr;
		u32 पंचांगp;

		अगर (i == 3)
			अवरोध;
		/* update perfect match रेजिस्टरs */
		dmi_addr = ha->addr;
		पंचांगp = (dmi_addr[2] << 24) | (dmi_addr[3] << 16) |
			(dmi_addr[4] << 8) | dmi_addr[5];
		enet_ग_लिखोl(priv, पंचांगp, ENET_PML_REG(i + 1));

		पंचांगp = (dmi_addr[0] << 8 | dmi_addr[1]);
		पंचांगp |= ENET_PMH_DATAVALID_MASK;
		enet_ग_लिखोl(priv, पंचांगp, ENET_PMH_REG(i++ + 1));
	पूर्ण

	क्रम (; i < 3; i++) अणु
		enet_ग_लिखोl(priv, 0, ENET_PML_REG(i + 1));
		enet_ग_लिखोl(priv, 0, ENET_PMH_REG(i + 1));
	पूर्ण

	enet_ग_लिखोl(priv, val, ENET_RXCFG_REG);
पूर्ण

/*
 * set mac duplex parameters
 */
अटल व्योम bcm_enet_set_duplex(काष्ठा bcm_enet_priv *priv, पूर्णांक fullduplex)
अणु
	u32 val;

	val = enet_पढ़ोl(priv, ENET_TXCTL_REG);
	अगर (fullduplex)
		val |= ENET_TXCTL_FD_MASK;
	अन्यथा
		val &= ~ENET_TXCTL_FD_MASK;
	enet_ग_लिखोl(priv, val, ENET_TXCTL_REG);
पूर्ण

/*
 * set mac flow control parameters
 */
अटल व्योम bcm_enet_set_flow(काष्ठा bcm_enet_priv *priv, पूर्णांक rx_en, पूर्णांक tx_en)
अणु
	u32 val;

	/* rx flow control (छोड़ो frame handling) */
	val = enet_पढ़ोl(priv, ENET_RXCFG_REG);
	अगर (rx_en)
		val |= ENET_RXCFG_ENFLOW_MASK;
	अन्यथा
		val &= ~ENET_RXCFG_ENFLOW_MASK;
	enet_ग_लिखोl(priv, val, ENET_RXCFG_REG);

	अगर (!priv->dma_has_sram)
		वापस;

	/* tx flow control (छोड़ो frame generation) */
	val = enet_dma_पढ़ोl(priv, ENETDMA_CFG_REG);
	अगर (tx_en)
		val |= ENETDMA_CFG_FLOWCH_MASK(priv->rx_chan);
	अन्यथा
		val &= ~ENETDMA_CFG_FLOWCH_MASK(priv->rx_chan);
	enet_dma_ग_लिखोl(priv, val, ENETDMA_CFG_REG);
पूर्ण

/*
 * link changed callback (from phylib)
 */
अटल व्योम bcm_enet_adjust_phy_link(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा phy_device *phydev;
	पूर्णांक status_changed;

	priv = netdev_priv(dev);
	phydev = dev->phydev;
	status_changed = 0;

	अगर (priv->old_link != phydev->link) अणु
		status_changed = 1;
		priv->old_link = phydev->link;
	पूर्ण

	/* reflect duplex change in mac configuration */
	अगर (phydev->link && phydev->duplex != priv->old_duplex) अणु
		bcm_enet_set_duplex(priv,
				    (phydev->duplex == DUPLEX_FULL) ? 1 : 0);
		status_changed = 1;
		priv->old_duplex = phydev->duplex;
	पूर्ण

	/* enable flow control अगर remote advertise it (trust phylib to
	 * check that duplex is full */
	अगर (phydev->link && phydev->छोड़ो != priv->old_छोड़ो) अणु
		पूर्णांक rx_छोड़ो_en, tx_छोड़ो_en;

		अगर (phydev->छोड़ो) अणु
			/* छोड़ो was advertised by lpa and us */
			rx_छोड़ो_en = 1;
			tx_छोड़ो_en = 1;
		पूर्ण अन्यथा अगर (!priv->छोड़ो_स्वतः) अणु
			/* छोड़ो setting overridden by user */
			rx_छोड़ो_en = priv->छोड़ो_rx;
			tx_छोड़ो_en = priv->छोड़ो_tx;
		पूर्ण अन्यथा अणु
			rx_छोड़ो_en = 0;
			tx_छोड़ो_en = 0;
		पूर्ण

		bcm_enet_set_flow(priv, rx_छोड़ो_en, tx_छोड़ो_en);
		status_changed = 1;
		priv->old_छोड़ो = phydev->छोड़ो;
	पूर्ण

	अगर (status_changed) अणु
		pr_info("%s: link %s", dev->name, phydev->link ?
			"UP" : "DOWN");
		अगर (phydev->link)
			pr_cont(" - %d/%s - flow control %s", phydev->speed,
			       DUPLEX_FULL == phydev->duplex ? "full" : "half",
			       phydev->छोड़ो == 1 ? "rx&tx" : "off");

		pr_cont("\n");
	पूर्ण
पूर्ण

/*
 * link changed callback (अगर phylib is not used)
 */
अटल व्योम bcm_enet_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	bcm_enet_set_duplex(priv, priv->क्रमce_duplex_full);
	bcm_enet_set_flow(priv, priv->छोड़ो_rx, priv->छोड़ो_tx);
	netअगर_carrier_on(dev);

	pr_info("%s: link forced UP - %d/%s - flow control %s/%s\n",
		dev->name,
		priv->क्रमce_speed_100 ? 100 : 10,
		priv->क्रमce_duplex_full ? "full" : "half",
		priv->छोड़ो_rx ? "rx" : "off",
		priv->छोड़ो_tx ? "tx" : "off");
पूर्ण

अटल व्योम bcm_enet_मुक्त_rx_buf_ring(काष्ठा device *kdev, काष्ठा bcm_enet_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->rx_ring_size; i++) अणु
		काष्ठा bcm_enet_desc *desc;

		अगर (!priv->rx_buf[i])
			जारी;

		desc = &priv->rx_desc_cpu[i];
		dma_unmap_single(kdev, desc->address, priv->rx_buf_size,
				 DMA_FROM_DEVICE);
		skb_मुक्त_frag(priv->rx_buf[i]);
	पूर्ण
	kमुक्त(priv->rx_buf);
पूर्ण

/*
 * खोलो callback, allocate dma rings & buffers and start rx operation
 */
अटल पूर्णांक bcm_enet_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा sockaddr addr;
	काष्ठा device *kdev;
	काष्ठा phy_device *phydev;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक size;
	अक्षर phy_id[MII_BUS_ID_SIZE + 3];
	व्योम *p;
	u32 val;

	priv = netdev_priv(dev);
	kdev = &priv->pdev->dev;

	अगर (priv->has_phy) अणु
		/* connect to PHY */
		snम_लिखो(phy_id, माप(phy_id), PHY_ID_FMT,
			 priv->mii_bus->id, priv->phy_id);

		phydev = phy_connect(dev, phy_id, bcm_enet_adjust_phy_link,
				     PHY_INTERFACE_MODE_MII);

		अगर (IS_ERR(phydev)) अणु
			dev_err(kdev, "could not attach to PHY\n");
			वापस PTR_ERR(phydev);
		पूर्ण

		/* mask with MAC supported features */
		phy_support_sym_छोड़ो(phydev);
		phy_set_max_speed(phydev, SPEED_100);
		phy_set_sym_छोड़ो(phydev, priv->छोड़ो_rx, priv->छोड़ो_rx,
				  priv->छोड़ो_स्वतः);

		phy_attached_info(phydev);

		priv->old_link = 0;
		priv->old_duplex = -1;
		priv->old_छोड़ो = -1;
	पूर्ण अन्यथा अणु
		phydev = शून्य;
	पूर्ण

	/* mask all पूर्णांकerrupts and request them */
	enet_ग_लिखोl(priv, 0, ENET_IRMASK_REG);
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->tx_chan);

	ret = request_irq(dev->irq, bcm_enet_isr_mac, 0, dev->name, dev);
	अगर (ret)
		जाओ out_phy_disconnect;

	ret = request_irq(priv->irq_rx, bcm_enet_isr_dma, 0,
			  dev->name, dev);
	अगर (ret)
		जाओ out_मुक्तirq;

	ret = request_irq(priv->irq_tx, bcm_enet_isr_dma,
			  0, dev->name, dev);
	अगर (ret)
		जाओ out_मुक्तirq_rx;

	/* initialize perfect match रेजिस्टरs */
	क्रम (i = 0; i < 4; i++) अणु
		enet_ग_लिखोl(priv, 0, ENET_PML_REG(i));
		enet_ग_लिखोl(priv, 0, ENET_PMH_REG(i));
	पूर्ण

	/* ग_लिखो device mac address */
	स_नकल(addr.sa_data, dev->dev_addr, ETH_ALEN);
	bcm_enet_set_mac_address(dev, &addr);

	/* allocate rx dma ring */
	size = priv->rx_ring_size * माप(काष्ठा bcm_enet_desc);
	p = dma_alloc_coherent(kdev, size, &priv->rx_desc_dma, GFP_KERNEL);
	अगर (!p) अणु
		ret = -ENOMEM;
		जाओ out_मुक्तirq_tx;
	पूर्ण

	priv->rx_desc_alloc_size = size;
	priv->rx_desc_cpu = p;

	/* allocate tx dma ring */
	size = priv->tx_ring_size * माप(काष्ठा bcm_enet_desc);
	p = dma_alloc_coherent(kdev, size, &priv->tx_desc_dma, GFP_KERNEL);
	अगर (!p) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_rx_ring;
	पूर्ण

	priv->tx_desc_alloc_size = size;
	priv->tx_desc_cpu = p;

	priv->tx_skb = kसुस्मृति(priv->tx_ring_size, माप(काष्ठा sk_buff *),
			       GFP_KERNEL);
	अगर (!priv->tx_skb) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_tx_ring;
	पूर्ण

	priv->tx_desc_count = priv->tx_ring_size;
	priv->tx_dirty_desc = 0;
	priv->tx_curr_desc = 0;
	spin_lock_init(&priv->tx_lock);

	/* init & fill rx ring with buffers */
	priv->rx_buf = kसुस्मृति(priv->rx_ring_size, माप(व्योम *),
			       GFP_KERNEL);
	अगर (!priv->rx_buf) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_tx_skb;
	पूर्ण

	priv->rx_desc_count = 0;
	priv->rx_dirty_desc = 0;
	priv->rx_curr_desc = 0;

	/* initialize flow control buffer allocation */
	अगर (priv->dma_has_sram)
		enet_dma_ग_लिखोl(priv, ENETDMA_BUFALLOC_FORCE_MASK | 0,
				ENETDMA_BUFALLOC_REG(priv->rx_chan));
	अन्यथा
		enet_dmac_ग_लिखोl(priv, ENETDMA_BUFALLOC_FORCE_MASK | 0,
				ENETDMAC_BUFALLOC, priv->rx_chan);

	अगर (bcm_enet_refill_rx(dev, false)) अणु
		dev_err(kdev, "cannot allocate rx buffer queue\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* ग_लिखो rx & tx ring addresses */
	अगर (priv->dma_has_sram) अणु
		enet_dmas_ग_लिखोl(priv, priv->rx_desc_dma,
				 ENETDMAS_RSTART_REG, priv->rx_chan);
		enet_dmas_ग_लिखोl(priv, priv->tx_desc_dma,
			 ENETDMAS_RSTART_REG, priv->tx_chan);
	पूर्ण अन्यथा अणु
		enet_dmac_ग_लिखोl(priv, priv->rx_desc_dma,
				ENETDMAC_RSTART, priv->rx_chan);
		enet_dmac_ग_लिखोl(priv, priv->tx_desc_dma,
				ENETDMAC_RSTART, priv->tx_chan);
	पूर्ण

	/* clear reमुख्यing state ram क्रम rx & tx channel */
	अगर (priv->dma_has_sram) अणु
		enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM2_REG, priv->rx_chan);
		enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM2_REG, priv->tx_chan);
		enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM3_REG, priv->rx_chan);
		enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM3_REG, priv->tx_chan);
		enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM4_REG, priv->rx_chan);
		enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM4_REG, priv->tx_chan);
	पूर्ण अन्यथा अणु
		enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_FC, priv->rx_chan);
		enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_FC, priv->tx_chan);
	पूर्ण

	/* set max rx/tx length */
	enet_ग_लिखोl(priv, priv->hw_mtu, ENET_RXMAXLEN_REG);
	enet_ग_लिखोl(priv, priv->hw_mtu, ENET_TXMAXLEN_REG);

	/* set dma maximum burst len */
	enet_dmac_ग_लिखोl(priv, priv->dma_maxburst,
			 ENETDMAC_MAXBURST, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, priv->dma_maxburst,
			 ENETDMAC_MAXBURST, priv->tx_chan);

	/* set correct transmit fअगरo watermark */
	enet_ग_लिखोl(priv, BCMENET_TX_FIFO_TRESH, ENET_TXWMARK_REG);

	/* set flow control low/high threshold to 1/3 / 2/3 */
	अगर (priv->dma_has_sram) अणु
		val = priv->rx_ring_size / 3;
		enet_dma_ग_लिखोl(priv, val, ENETDMA_FLOWCL_REG(priv->rx_chan));
		val = (priv->rx_ring_size * 2) / 3;
		enet_dma_ग_लिखोl(priv, val, ENETDMA_FLOWCH_REG(priv->rx_chan));
	पूर्ण अन्यथा अणु
		enet_dmac_ग_लिखोl(priv, 5, ENETDMAC_FC, priv->rx_chan);
		enet_dmac_ग_लिखोl(priv, priv->rx_ring_size, ENETDMAC_LEN, priv->rx_chan);
		enet_dmac_ग_लिखोl(priv, priv->tx_ring_size, ENETDMAC_LEN, priv->tx_chan);
	पूर्ण

	/* all set, enable mac and पूर्णांकerrupts, start dma engine and
	 * kick rx dma channel */
	wmb();
	val = enet_पढ़ोl(priv, ENET_CTL_REG);
	val |= ENET_CTL_ENABLE_MASK;
	enet_ग_लिखोl(priv, val, ENET_CTL_REG);
	अगर (priv->dma_has_sram)
		enet_dma_ग_लिखोl(priv, ENETDMA_CFG_EN_MASK, ENETDMA_CFG_REG);
	enet_dmac_ग_लिखोl(priv, priv->dma_chan_en_mask,
			 ENETDMAC_CHANCFG, priv->rx_chan);

	/* watch "mib counters about to overflow" पूर्णांकerrupt */
	enet_ग_लिखोl(priv, ENET_IR_MIB, ENET_IR_REG);
	enet_ग_लिखोl(priv, ENET_IR_MIB, ENET_IRMASK_REG);

	/* watch "packet transferred" पूर्णांकerrupt in rx and tx */
	enet_dmac_ग_लिखोl(priv, priv->dma_chan_पूर्णांक_mask,
			 ENETDMAC_IR, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, priv->dma_chan_पूर्णांक_mask,
			 ENETDMAC_IR, priv->tx_chan);

	/* make sure we enable napi beक्रमe rx पूर्णांकerrupt  */
	napi_enable(&priv->napi);

	enet_dmac_ग_लिखोl(priv, priv->dma_chan_पूर्णांक_mask,
			 ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, priv->dma_chan_पूर्णांक_mask,
			 ENETDMAC_IRMASK, priv->tx_chan);

	अगर (phydev)
		phy_start(phydev);
	अन्यथा
		bcm_enet_adjust_link(dev);

	netअगर_start_queue(dev);
	वापस 0;

out:
	bcm_enet_मुक्त_rx_buf_ring(kdev, priv);

out_मुक्त_tx_skb:
	kमुक्त(priv->tx_skb);

out_मुक्त_tx_ring:
	dma_मुक्त_coherent(kdev, priv->tx_desc_alloc_size,
			  priv->tx_desc_cpu, priv->tx_desc_dma);

out_मुक्त_rx_ring:
	dma_मुक्त_coherent(kdev, priv->rx_desc_alloc_size,
			  priv->rx_desc_cpu, priv->rx_desc_dma);

out_मुक्तirq_tx:
	मुक्त_irq(priv->irq_tx, dev);

out_मुक्तirq_rx:
	मुक्त_irq(priv->irq_rx, dev);

out_मुक्तirq:
	मुक्त_irq(dev->irq, dev);

out_phy_disconnect:
	अगर (phydev)
		phy_disconnect(phydev);

	वापस ret;
पूर्ण

/*
 * disable mac
 */
अटल व्योम bcm_enet_disable_mac(काष्ठा bcm_enet_priv *priv)
अणु
	पूर्णांक limit;
	u32 val;

	val = enet_पढ़ोl(priv, ENET_CTL_REG);
	val |= ENET_CTL_DISABLE_MASK;
	enet_ग_लिखोl(priv, val, ENET_CTL_REG);

	limit = 1000;
	करो अणु
		u32 val;

		val = enet_पढ़ोl(priv, ENET_CTL_REG);
		अगर (!(val & ENET_CTL_DISABLE_MASK))
			अवरोध;
		udelay(1);
	पूर्ण जबतक (limit--);
पूर्ण

/*
 * disable dma in given channel
 */
अटल व्योम bcm_enet_disable_dma(काष्ठा bcm_enet_priv *priv, पूर्णांक chan)
अणु
	पूर्णांक limit;

	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_CHANCFG, chan);

	limit = 1000;
	करो अणु
		u32 val;

		val = enet_dmac_पढ़ोl(priv, ENETDMAC_CHANCFG, chan);
		अगर (!(val & ENETDMAC_CHANCFG_EN_MASK))
			अवरोध;
		udelay(1);
	पूर्ण जबतक (limit--);
पूर्ण

/*
 * stop callback
 */
अटल पूर्णांक bcm_enet_stop(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा device *kdev;

	priv = netdev_priv(dev);
	kdev = &priv->pdev->dev;

	netअगर_stop_queue(dev);
	napi_disable(&priv->napi);
	अगर (priv->has_phy)
		phy_stop(dev->phydev);
	del_समयr_sync(&priv->rx_समयout);

	/* mask all पूर्णांकerrupts */
	enet_ग_लिखोl(priv, 0, ENET_IRMASK_REG);
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->tx_chan);

	/* make sure no mib update is scheduled */
	cancel_work_sync(&priv->mib_update_task);

	/* disable dma & mac */
	bcm_enet_disable_dma(priv, priv->tx_chan);
	bcm_enet_disable_dma(priv, priv->rx_chan);
	bcm_enet_disable_mac(priv);

	/* क्रमce reclaim of all tx buffers */
	bcm_enet_tx_reclaim(dev, 1);

	/* मुक्त the rx buffer ring */
	bcm_enet_मुक्त_rx_buf_ring(kdev, priv);

	/* मुक्त reमुख्यing allocated memory */
	kमुक्त(priv->tx_skb);
	dma_मुक्त_coherent(kdev, priv->rx_desc_alloc_size,
			  priv->rx_desc_cpu, priv->rx_desc_dma);
	dma_मुक्त_coherent(kdev, priv->tx_desc_alloc_size,
			  priv->tx_desc_cpu, priv->tx_desc_dma);
	मुक्त_irq(priv->irq_tx, dev);
	मुक्त_irq(priv->irq_rx, dev);
	मुक्त_irq(dev->irq, dev);

	/* release phy */
	अगर (priv->has_phy)
		phy_disconnect(dev->phydev);

	/* reset BQL after क्रमced tx reclaim to prevent kernel panic */
	netdev_reset_queue(dev);

	वापस 0;
पूर्ण

/*
 * ethtool callbacks
 */
काष्ठा bcm_enet_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
	पूर्णांक mib_reg;
पूर्ण;

#घोषणा GEN_STAT(m) माप(((काष्ठा bcm_enet_priv *)0)->m),		\
		     दुरत्व(काष्ठा bcm_enet_priv, m)
#घोषणा DEV_STAT(m) माप(((काष्ठा net_device_stats *)0)->m),		\
		     दुरत्व(काष्ठा net_device_stats, m)

अटल स्थिर काष्ठा bcm_enet_stats bcm_enet_gstrings_stats[] = अणु
	अणु "rx_packets", DEV_STAT(rx_packets), -1 पूर्ण,
	अणु "tx_packets",	DEV_STAT(tx_packets), -1 पूर्ण,
	अणु "rx_bytes", DEV_STAT(rx_bytes), -1 पूर्ण,
	अणु "tx_bytes", DEV_STAT(tx_bytes), -1 पूर्ण,
	अणु "rx_errors", DEV_STAT(rx_errors), -1 पूर्ण,
	अणु "tx_errors", DEV_STAT(tx_errors), -1 पूर्ण,
	अणु "rx_dropped",	DEV_STAT(rx_dropped), -1 पूर्ण,
	अणु "tx_dropped",	DEV_STAT(tx_dropped), -1 पूर्ण,

	अणु "rx_good_octets", GEN_STAT(mib.rx_gd_octets), ETH_MIB_RX_GD_OCTETSपूर्ण,
	अणु "rx_good_pkts", GEN_STAT(mib.rx_gd_pkts), ETH_MIB_RX_GD_PKTS पूर्ण,
	अणु "rx_broadcast", GEN_STAT(mib.rx_brdcast), ETH_MIB_RX_BRDCAST पूर्ण,
	अणु "rx_multicast", GEN_STAT(mib.rx_mult), ETH_MIB_RX_MULT पूर्ण,
	अणु "rx_64_octets", GEN_STAT(mib.rx_64), ETH_MIB_RX_64 पूर्ण,
	अणु "rx_65_127_oct", GEN_STAT(mib.rx_65_127), ETH_MIB_RX_65_127 पूर्ण,
	अणु "rx_128_255_oct", GEN_STAT(mib.rx_128_255), ETH_MIB_RX_128_255 पूर्ण,
	अणु "rx_256_511_oct", GEN_STAT(mib.rx_256_511), ETH_MIB_RX_256_511 पूर्ण,
	अणु "rx_512_1023_oct", GEN_STAT(mib.rx_512_1023), ETH_MIB_RX_512_1023 पूर्ण,
	अणु "rx_1024_max_oct", GEN_STAT(mib.rx_1024_max), ETH_MIB_RX_1024_MAX पूर्ण,
	अणु "rx_jabber", GEN_STAT(mib.rx_jab), ETH_MIB_RX_JAB पूर्ण,
	अणु "rx_oversize", GEN_STAT(mib.rx_ovr), ETH_MIB_RX_OVR पूर्ण,
	अणु "rx_fragment", GEN_STAT(mib.rx_frag), ETH_MIB_RX_FRAG पूर्ण,
	अणु "rx_dropped",	GEN_STAT(mib.rx_drop), ETH_MIB_RX_DROP पूर्ण,
	अणु "rx_crc_align", GEN_STAT(mib.rx_crc_align), ETH_MIB_RX_CRC_ALIGN पूर्ण,
	अणु "rx_undersize", GEN_STAT(mib.rx_und), ETH_MIB_RX_UND पूर्ण,
	अणु "rx_crc", GEN_STAT(mib.rx_crc), ETH_MIB_RX_CRC पूर्ण,
	अणु "rx_align", GEN_STAT(mib.rx_align), ETH_MIB_RX_ALIGN पूर्ण,
	अणु "rx_symbol_error", GEN_STAT(mib.rx_sym), ETH_MIB_RX_SYM पूर्ण,
	अणु "rx_pause", GEN_STAT(mib.rx_छोड़ो), ETH_MIB_RX_PAUSE पूर्ण,
	अणु "rx_control", GEN_STAT(mib.rx_cntrl), ETH_MIB_RX_CNTRL पूर्ण,

	अणु "tx_good_octets", GEN_STAT(mib.tx_gd_octets), ETH_MIB_TX_GD_OCTETS पूर्ण,
	अणु "tx_good_pkts", GEN_STAT(mib.tx_gd_pkts), ETH_MIB_TX_GD_PKTS पूर्ण,
	अणु "tx_broadcast", GEN_STAT(mib.tx_brdcast), ETH_MIB_TX_BRDCAST पूर्ण,
	अणु "tx_multicast", GEN_STAT(mib.tx_mult), ETH_MIB_TX_MULT पूर्ण,
	अणु "tx_64_oct", GEN_STAT(mib.tx_64), ETH_MIB_TX_64 पूर्ण,
	अणु "tx_65_127_oct", GEN_STAT(mib.tx_65_127), ETH_MIB_TX_65_127 पूर्ण,
	अणु "tx_128_255_oct", GEN_STAT(mib.tx_128_255), ETH_MIB_TX_128_255 पूर्ण,
	अणु "tx_256_511_oct", GEN_STAT(mib.tx_256_511), ETH_MIB_TX_256_511 पूर्ण,
	अणु "tx_512_1023_oct", GEN_STAT(mib.tx_512_1023), ETH_MIB_TX_512_1023पूर्ण,
	अणु "tx_1024_max_oct", GEN_STAT(mib.tx_1024_max), ETH_MIB_TX_1024_MAX पूर्ण,
	अणु "tx_jabber", GEN_STAT(mib.tx_jab), ETH_MIB_TX_JAB पूर्ण,
	अणु "tx_oversize", GEN_STAT(mib.tx_ovr), ETH_MIB_TX_OVR पूर्ण,
	अणु "tx_fragment", GEN_STAT(mib.tx_frag), ETH_MIB_TX_FRAG पूर्ण,
	अणु "tx_underrun", GEN_STAT(mib.tx_underrun), ETH_MIB_TX_UNDERRUN पूर्ण,
	अणु "tx_collisions", GEN_STAT(mib.tx_col), ETH_MIB_TX_COL पूर्ण,
	अणु "tx_single_collision", GEN_STAT(mib.tx_1_col), ETH_MIB_TX_1_COL पूर्ण,
	अणु "tx_multiple_collision", GEN_STAT(mib.tx_m_col), ETH_MIB_TX_M_COL पूर्ण,
	अणु "tx_excess_collision", GEN_STAT(mib.tx_ex_col), ETH_MIB_TX_EX_COL पूर्ण,
	अणु "tx_late_collision", GEN_STAT(mib.tx_late), ETH_MIB_TX_LATE पूर्ण,
	अणु "tx_deferred", GEN_STAT(mib.tx_def), ETH_MIB_TX_DEF पूर्ण,
	अणु "tx_carrier_sense", GEN_STAT(mib.tx_crs), ETH_MIB_TX_CRS पूर्ण,
	अणु "tx_pause", GEN_STAT(mib.tx_छोड़ो), ETH_MIB_TX_PAUSE पूर्ण,

पूर्ण;

#घोषणा BCM_ENET_STATS_LEN	ARRAY_SIZE(bcm_enet_gstrings_stats)

अटल स्थिर u32 unused_mib_regs[] = अणु
	ETH_MIB_TX_ALL_OCTETS,
	ETH_MIB_TX_ALL_PKTS,
	ETH_MIB_RX_ALL_OCTETS,
	ETH_MIB_RX_ALL_PKTS,
पूर्ण;


अटल व्योम bcm_enet_get_drvinfo(काष्ठा net_device *netdev,
				 काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, bcm_enet_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, "bcm63xx", माप(drvinfo->bus_info));
पूर्ण

अटल पूर्णांक bcm_enet_get_sset_count(काष्ठा net_device *netdev,
					पूर्णांक string_set)
अणु
	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		वापस BCM_ENET_STATS_LEN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम bcm_enet_get_strings(काष्ठा net_device *netdev,
				 u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < BCM_ENET_STATS_LEN; i++) अणु
			स_नकल(data + i * ETH_GSTRING_LEN,
			       bcm_enet_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम update_mib_counters(काष्ठा bcm_enet_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BCM_ENET_STATS_LEN; i++) अणु
		स्थिर काष्ठा bcm_enet_stats *s;
		u32 val;
		अक्षर *p;

		s = &bcm_enet_gstrings_stats[i];
		अगर (s->mib_reg == -1)
			जारी;

		val = enet_पढ़ोl(priv, ENET_MIB_REG(s->mib_reg));
		p = (अक्षर *)priv + s->stat_offset;

		अगर (s->माप_stat == माप(u64))
			*(u64 *)p += val;
		अन्यथा
			*(u32 *)p += val;
	पूर्ण

	/* also empty unused mib counters to make sure mib counter
	 * overflow पूर्णांकerrupt is cleared */
	क्रम (i = 0; i < ARRAY_SIZE(unused_mib_regs); i++)
		(व्योम)enet_पढ़ोl(priv, ENET_MIB_REG(unused_mib_regs[i]));
पूर्ण

अटल व्योम bcm_enet_update_mib_counters_defer(काष्ठा work_काष्ठा *t)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = container_of(t, काष्ठा bcm_enet_priv, mib_update_task);
	mutex_lock(&priv->mib_update_lock);
	update_mib_counters(priv);
	mutex_unlock(&priv->mib_update_lock);

	/* reenable mib पूर्णांकerrupt */
	अगर (netअगर_running(priv->net_dev))
		enet_ग_लिखोl(priv, ENET_IR_MIB, ENET_IRMASK_REG);
पूर्ण

अटल व्योम bcm_enet_get_ethtool_stats(काष्ठा net_device *netdev,
				       काष्ठा ethtool_stats *stats,
				       u64 *data)
अणु
	काष्ठा bcm_enet_priv *priv;
	पूर्णांक i;

	priv = netdev_priv(netdev);

	mutex_lock(&priv->mib_update_lock);
	update_mib_counters(priv);

	क्रम (i = 0; i < BCM_ENET_STATS_LEN; i++) अणु
		स्थिर काष्ठा bcm_enet_stats *s;
		अक्षर *p;

		s = &bcm_enet_gstrings_stats[i];
		अगर (s->mib_reg == -1)
			p = (अक्षर *)&netdev->stats;
		अन्यथा
			p = (अक्षर *)priv;
		p += s->stat_offset;
		data[i] = (s->माप_stat == माप(u64)) ?
			*(u64 *)p : *(u32 *)p;
	पूर्ण
	mutex_unlock(&priv->mib_update_lock);
पूर्ण

अटल पूर्णांक bcm_enet_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	अगर (priv->has_phy)
		वापस phy_ethtool_nway_reset(dev);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक bcm_enet_get_link_ksettings(काष्ठा net_device *dev,
				       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा bcm_enet_priv *priv;
	u32 supported, advertising;

	priv = netdev_priv(dev);

	अगर (priv->has_phy) अणु
		अगर (!dev->phydev)
			वापस -ENODEV;

		phy_ethtool_ksettings_get(dev->phydev, cmd);

		वापस 0;
	पूर्ण अन्यथा अणु
		cmd->base.स्वतःneg = 0;
		cmd->base.speed = (priv->क्रमce_speed_100) ?
			SPEED_100 : SPEED_10;
		cmd->base.duplex = (priv->क्रमce_duplex_full) ?
			DUPLEX_FULL : DUPLEX_HALF;
		supported = ADVERTISED_10baseT_Half |
			ADVERTISED_10baseT_Full |
			ADVERTISED_100baseT_Half |
			ADVERTISED_100baseT_Full;
		advertising = 0;
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported, supported);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.advertising, advertising);
		cmd->base.port = PORT_MII;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bcm_enet_set_link_ksettings(काष्ठा net_device *dev,
				       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	अगर (priv->has_phy) अणु
		अगर (!dev->phydev)
			वापस -ENODEV;
		वापस phy_ethtool_ksettings_set(dev->phydev, cmd);
	पूर्ण अन्यथा अणु

		अगर (cmd->base.स्वतःneg ||
		    (cmd->base.speed != SPEED_100 &&
		     cmd->base.speed != SPEED_10) ||
		    cmd->base.port != PORT_MII)
			वापस -EINVAL;

		priv->क्रमce_speed_100 =
			(cmd->base.speed == SPEED_100) ? 1 : 0;
		priv->क्रमce_duplex_full =
			(cmd->base.duplex == DUPLEX_FULL) ? 1 : 0;

		अगर (netअगर_running(dev))
			bcm_enet_adjust_link(dev);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम bcm_enet_get_ringparam(काष्ठा net_device *dev,
				   काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);

	/* rx/tx ring is actually only limited by memory */
	ering->rx_max_pending = 8192;
	ering->tx_max_pending = 8192;
	ering->rx_pending = priv->rx_ring_size;
	ering->tx_pending = priv->tx_ring_size;
पूर्ण

अटल पूर्णांक bcm_enet_set_ringparam(काष्ठा net_device *dev,
				  काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bcm_enet_priv *priv;
	पूर्णांक was_running;

	priv = netdev_priv(dev);

	was_running = 0;
	अगर (netअगर_running(dev)) अणु
		bcm_enet_stop(dev);
		was_running = 1;
	पूर्ण

	priv->rx_ring_size = ering->rx_pending;
	priv->tx_ring_size = ering->tx_pending;

	अगर (was_running) अणु
		पूर्णांक err;

		err = bcm_enet_खोलो(dev);
		अगर (err)
			dev_बंद(dev);
		अन्यथा
			bcm_enet_set_multicast_list(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bcm_enet_get_छोड़ोparam(काष्ठा net_device *dev,
				    काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	ecmd->स्वतःneg = priv->छोड़ो_स्वतः;
	ecmd->rx_छोड़ो = priv->छोड़ो_rx;
	ecmd->tx_छोड़ो = priv->छोड़ो_tx;
पूर्ण

अटल पूर्णांक bcm_enet_set_छोड़ोparam(काष्ठा net_device *dev,
				   काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);

	अगर (priv->has_phy) अणु
		अगर (ecmd->स्वतःneg && (ecmd->rx_छोड़ो != ecmd->tx_छोड़ो)) अणु
			/* asymetric छोड़ो mode not supported,
			 * actually possible but पूर्णांकegrated PHY has RO
			 * asym_छोड़ो bit */
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* no छोड़ो स्वतःneg on direct mii connection */
		अगर (ecmd->स्वतःneg)
			वापस -EINVAL;
	पूर्ण

	priv->छोड़ो_स्वतः = ecmd->स्वतःneg;
	priv->छोड़ो_rx = ecmd->rx_छोड़ो;
	priv->छोड़ो_tx = ecmd->tx_छोड़ो;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bcm_enet_ethtool_ops = अणु
	.get_strings		= bcm_enet_get_strings,
	.get_sset_count		= bcm_enet_get_sset_count,
	.get_ethtool_stats      = bcm_enet_get_ethtool_stats,
	.nway_reset		= bcm_enet_nway_reset,
	.get_drvinfo		= bcm_enet_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_ringparam		= bcm_enet_get_ringparam,
	.set_ringparam		= bcm_enet_set_ringparam,
	.get_छोड़ोparam		= bcm_enet_get_छोड़ोparam,
	.set_छोड़ोparam		= bcm_enet_set_छोड़ोparam,
	.get_link_ksettings	= bcm_enet_get_link_ksettings,
	.set_link_ksettings	= bcm_enet_set_link_ksettings,
पूर्ण;

अटल पूर्णांक bcm_enet_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	अगर (priv->has_phy) अणु
		अगर (!dev->phydev)
			वापस -ENODEV;
		वापस phy_mii_ioctl(dev->phydev, rq, cmd);
	पूर्ण अन्यथा अणु
		काष्ठा mii_अगर_info mii;

		mii.dev = dev;
		mii.mdio_पढ़ो = bcm_enet_mdio_पढ़ो_mii;
		mii.mdio_ग_लिखो = bcm_enet_mdio_ग_लिखो_mii;
		mii.phy_id = 0;
		mii.phy_id_mask = 0x3f;
		mii.reg_num_mask = 0x1f;
		वापस generic_mii_ioctl(&mii, अगर_mii(rq), cmd, शून्य);
	पूर्ण
पूर्ण

/*
 * adjust mtu, can't be called जबतक device is running
 */
अटल पूर्णांक bcm_enet_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा bcm_enet_priv *priv = netdev_priv(dev);
	पूर्णांक actual_mtu = new_mtu;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	/* add ethernet header + vlan tag size */
	actual_mtu += VLAN_ETH_HLEN;

	/*
	 * setup maximum size beक्रमe we get overflow mark in
	 * descriptor, note that this will not prevent reception of
	 * big frames, they will be split पूर्णांकo multiple buffers
	 * anyway
	 */
	priv->hw_mtu = actual_mtu;

	/*
	 * align rx buffer size to dma burst len, account FCS since
	 * it's appended
	 */
	priv->rx_buf_size = ALIGN(actual_mtu + ETH_FCS_LEN,
				  priv->dma_maxburst * 4);

	priv->rx_frag_size = SKB_DATA_ALIGN(priv->rx_buf_offset + priv->rx_buf_size) +
					    SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

/*
 * preinit hardware to allow mii operation जबतक device is करोwn
 */
अटल व्योम bcm_enet_hw_preinit(काष्ठा bcm_enet_priv *priv)
अणु
	u32 val;
	पूर्णांक limit;

	/* make sure mac is disabled */
	bcm_enet_disable_mac(priv);

	/* soft reset mac */
	val = ENET_CTL_SRESET_MASK;
	enet_ग_लिखोl(priv, val, ENET_CTL_REG);
	wmb();

	limit = 1000;
	करो अणु
		val = enet_पढ़ोl(priv, ENET_CTL_REG);
		अगर (!(val & ENET_CTL_SRESET_MASK))
			अवरोध;
		udelay(1);
	पूर्ण जबतक (limit--);

	/* select correct mii पूर्णांकerface */
	val = enet_पढ़ोl(priv, ENET_CTL_REG);
	अगर (priv->use_बाह्यal_mii)
		val |= ENET_CTL_EPHYSEL_MASK;
	अन्यथा
		val &= ~ENET_CTL_EPHYSEL_MASK;
	enet_ग_लिखोl(priv, val, ENET_CTL_REG);

	/* turn on mdc घड़ी */
	enet_ग_लिखोl(priv, (0x1f << ENET_MIISC_MDCFREQDIV_SHIFT) |
		    ENET_MIISC_PREAMBLEEN_MASK, ENET_MIISC_REG);

	/* set mib counters to self-clear when पढ़ो */
	val = enet_पढ़ोl(priv, ENET_MIBCTL_REG);
	val |= ENET_MIBCTL_RDCLEAR_MASK;
	enet_ग_लिखोl(priv, val, ENET_MIBCTL_REG);
पूर्ण

अटल स्थिर काष्ठा net_device_ops bcm_enet_ops = अणु
	.nकरो_खोलो		= bcm_enet_खोलो,
	.nकरो_stop		= bcm_enet_stop,
	.nकरो_start_xmit		= bcm_enet_start_xmit,
	.nकरो_set_mac_address	= bcm_enet_set_mac_address,
	.nकरो_set_rx_mode	= bcm_enet_set_multicast_list,
	.nकरो_करो_ioctl		= bcm_enet_ioctl,
	.nकरो_change_mtu		= bcm_enet_change_mtu,
पूर्ण;

/*
 * allocate netdevice, request रेजिस्टर memory and रेजिस्टर device.
 */
अटल पूर्णांक bcm_enet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा net_device *dev;
	काष्ठा bcm63xx_enet_platक्रमm_data *pd;
	काष्ठा resource *res_irq, *res_irq_rx, *res_irq_tx;
	काष्ठा mii_bus *bus;
	पूर्णांक i, ret;

	अगर (!bcm_enet_shared_base[0])
		वापस -EPROBE_DEFER;

	res_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	res_irq_rx = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 1);
	res_irq_tx = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 2);
	अगर (!res_irq || !res_irq_rx || !res_irq_tx)
		वापस -ENODEV;

	dev = alloc_etherdev(माप(*priv));
	अगर (!dev)
		वापस -ENOMEM;
	priv = netdev_priv(dev);

	priv->enet_is_sw = false;
	priv->dma_maxburst = BCMENET_DMA_MAXBURST;
	priv->rx_buf_offset = NET_SKB_PAD;

	ret = bcm_enet_change_mtu(dev, dev->mtu);
	अगर (ret)
		जाओ out;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ out;
	पूर्ण

	dev->irq = priv->irq = res_irq->start;
	priv->irq_rx = res_irq_rx->start;
	priv->irq_tx = res_irq_tx->start;

	priv->mac_clk = devm_clk_get(&pdev->dev, "enet");
	अगर (IS_ERR(priv->mac_clk)) अणु
		ret = PTR_ERR(priv->mac_clk);
		जाओ out;
	पूर्ण
	ret = clk_prepare_enable(priv->mac_clk);
	अगर (ret)
		जाओ out;

	/* initialize शेष and fetch platक्रमm data */
	priv->rx_ring_size = BCMENET_DEF_RX_DESC;
	priv->tx_ring_size = BCMENET_DEF_TX_DESC;

	pd = dev_get_platdata(&pdev->dev);
	अगर (pd) अणु
		स_नकल(dev->dev_addr, pd->mac_addr, ETH_ALEN);
		priv->has_phy = pd->has_phy;
		priv->phy_id = pd->phy_id;
		priv->has_phy_पूर्णांकerrupt = pd->has_phy_पूर्णांकerrupt;
		priv->phy_पूर्णांकerrupt = pd->phy_पूर्णांकerrupt;
		priv->use_बाह्यal_mii = !pd->use_पूर्णांकernal_phy;
		priv->छोड़ो_स्वतः = pd->छोड़ो_स्वतः;
		priv->छोड़ो_rx = pd->छोड़ो_rx;
		priv->छोड़ो_tx = pd->छोड़ो_tx;
		priv->क्रमce_duplex_full = pd->क्रमce_duplex_full;
		priv->क्रमce_speed_100 = pd->क्रमce_speed_100;
		priv->dma_chan_en_mask = pd->dma_chan_en_mask;
		priv->dma_chan_पूर्णांक_mask = pd->dma_chan_पूर्णांक_mask;
		priv->dma_chan_width = pd->dma_chan_width;
		priv->dma_has_sram = pd->dma_has_sram;
		priv->dma_desc_shअगरt = pd->dma_desc_shअगरt;
		priv->rx_chan = pd->rx_chan;
		priv->tx_chan = pd->tx_chan;
	पूर्ण

	अगर (priv->has_phy && !priv->use_बाह्यal_mii) अणु
		/* using पूर्णांकernal PHY, enable घड़ी */
		priv->phy_clk = devm_clk_get(&pdev->dev, "ephy");
		अगर (IS_ERR(priv->phy_clk)) अणु
			ret = PTR_ERR(priv->phy_clk);
			priv->phy_clk = शून्य;
			जाओ out_disable_clk_mac;
		पूर्ण
		ret = clk_prepare_enable(priv->phy_clk);
		अगर (ret)
			जाओ out_disable_clk_mac;
	पूर्ण

	/* करो minimal hardware init to be able to probe mii bus */
	bcm_enet_hw_preinit(priv);

	/* MII bus registration */
	अगर (priv->has_phy) अणु

		priv->mii_bus = mdiobus_alloc();
		अगर (!priv->mii_bus) अणु
			ret = -ENOMEM;
			जाओ out_uninit_hw;
		पूर्ण

		bus = priv->mii_bus;
		bus->name = "bcm63xx_enet MII bus";
		bus->parent = &pdev->dev;
		bus->priv = priv;
		bus->पढ़ो = bcm_enet_mdio_पढ़ो_phylib;
		bus->ग_लिखो = bcm_enet_mdio_ग_लिखो_phylib;
		प्र_लिखो(bus->id, "%s-%d", pdev->name, pdev->id);

		/* only probe bus where we think the PHY is, because
		 * the mdio पढ़ो operation वापस 0 instead of 0xffff
		 * अगर a slave is not present on hw */
		bus->phy_mask = ~(1 << priv->phy_id);

		अगर (priv->has_phy_पूर्णांकerrupt)
			bus->irq[priv->phy_id] = priv->phy_पूर्णांकerrupt;

		ret = mdiobus_रेजिस्टर(bus);
		अगर (ret) अणु
			dev_err(&pdev->dev, "unable to register mdio bus\n");
			जाओ out_मुक्त_mdio;
		पूर्ण
	पूर्ण अन्यथा अणु

		/* run platक्रमm code to initialize PHY device */
		अगर (pd && pd->mii_config &&
		    pd->mii_config(dev, 1, bcm_enet_mdio_पढ़ो_mii,
				   bcm_enet_mdio_ग_लिखो_mii)) अणु
			dev_err(&pdev->dev, "unable to configure mdio bus\n");
			जाओ out_uninit_hw;
		पूर्ण
	पूर्ण

	spin_lock_init(&priv->rx_lock);

	/* init rx समयout (used क्रम oom) */
	समयr_setup(&priv->rx_समयout, bcm_enet_refill_rx_समयr, 0);

	/* init the mib update lock&work */
	mutex_init(&priv->mib_update_lock);
	INIT_WORK(&priv->mib_update_task, bcm_enet_update_mib_counters_defer);

	/* zero mib counters */
	क्रम (i = 0; i < ENET_MIB_REG_COUNT; i++)
		enet_ग_लिखोl(priv, 0, ENET_MIB_REG(i));

	/* रेजिस्टर netdevice */
	dev->netdev_ops = &bcm_enet_ops;
	netअगर_napi_add(dev, &priv->napi, bcm_enet_poll, 16);

	dev->ethtool_ops = &bcm_enet_ethtool_ops;
	/* MTU range: 46 - 2028 */
	dev->min_mtu = ETH_ZLEN - ETH_HLEN;
	dev->max_mtu = BCMENET_MAX_MTU - VLAN_ETH_HLEN;
	SET_NETDEV_DEV(dev, &pdev->dev);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ out_unरेजिस्टर_mdio;

	netअगर_carrier_off(dev);
	platक्रमm_set_drvdata(pdev, dev);
	priv->pdev = pdev;
	priv->net_dev = dev;

	वापस 0;

out_unरेजिस्टर_mdio:
	अगर (priv->mii_bus)
		mdiobus_unरेजिस्टर(priv->mii_bus);

out_मुक्त_mdio:
	अगर (priv->mii_bus)
		mdiobus_मुक्त(priv->mii_bus);

out_uninit_hw:
	/* turn off mdc घड़ी */
	enet_ग_लिखोl(priv, 0, ENET_MIISC_REG);
	clk_disable_unprepare(priv->phy_clk);

out_disable_clk_mac:
	clk_disable_unprepare(priv->mac_clk);
out:
	मुक्त_netdev(dev);
	वापस ret;
पूर्ण


/*
 * निकास func, stops hardware and unरेजिस्टरs netdevice
 */
अटल पूर्णांक bcm_enet_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा net_device *dev;

	/* stop netdevice */
	dev = platक्रमm_get_drvdata(pdev);
	priv = netdev_priv(dev);
	unरेजिस्टर_netdev(dev);

	/* turn off mdc घड़ी */
	enet_ग_लिखोl(priv, 0, ENET_MIISC_REG);

	अगर (priv->has_phy) अणु
		mdiobus_unरेजिस्टर(priv->mii_bus);
		mdiobus_मुक्त(priv->mii_bus);
	पूर्ण अन्यथा अणु
		काष्ठा bcm63xx_enet_platक्रमm_data *pd;

		pd = dev_get_platdata(&pdev->dev);
		अगर (pd && pd->mii_config)
			pd->mii_config(dev, 0, bcm_enet_mdio_पढ़ो_mii,
				       bcm_enet_mdio_ग_लिखो_mii);
	पूर्ण

	/* disable hw block घड़ीs */
	clk_disable_unprepare(priv->phy_clk);
	clk_disable_unprepare(priv->mac_clk);

	मुक्त_netdev(dev);
	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver bcm63xx_enet_driver = अणु
	.probe	= bcm_enet_probe,
	.हटाओ	= bcm_enet_हटाओ,
	.driver	= अणु
		.name	= "bcm63xx_enet",
		.owner  = THIS_MODULE,
	पूर्ण,
पूर्ण;

/*
 * चयन mii access callbacks
 */
अटल पूर्णांक bcmenet_sw_mdio_पढ़ो(काष्ठा bcm_enet_priv *priv,
				पूर्णांक ext, पूर्णांक phy_id, पूर्णांक location)
अणु
	u32 reg;
	पूर्णांक ret;

	spin_lock_bh(&priv->enetsw_mdio_lock);
	enetsw_ग_लिखोl(priv, 0, ENETSW_MDIOC_REG);

	reg = ENETSW_MDIOC_RD_MASK |
		(phy_id << ENETSW_MDIOC_PHYID_SHIFT) |
		(location << ENETSW_MDIOC_REG_SHIFT);

	अगर (ext)
		reg |= ENETSW_MDIOC_EXT_MASK;

	enetsw_ग_लिखोl(priv, reg, ENETSW_MDIOC_REG);
	udelay(50);
	ret = enetsw_पढ़ोw(priv, ENETSW_MDIOD_REG);
	spin_unlock_bh(&priv->enetsw_mdio_lock);
	वापस ret;
पूर्ण

अटल व्योम bcmenet_sw_mdio_ग_लिखो(काष्ठा bcm_enet_priv *priv,
				 पूर्णांक ext, पूर्णांक phy_id, पूर्णांक location,
				 uपूर्णांक16_t data)
अणु
	u32 reg;

	spin_lock_bh(&priv->enetsw_mdio_lock);
	enetsw_ग_लिखोl(priv, 0, ENETSW_MDIOC_REG);

	reg = ENETSW_MDIOC_WR_MASK |
		(phy_id << ENETSW_MDIOC_PHYID_SHIFT) |
		(location << ENETSW_MDIOC_REG_SHIFT);

	अगर (ext)
		reg |= ENETSW_MDIOC_EXT_MASK;

	reg |= data;

	enetsw_ग_लिखोl(priv, reg, ENETSW_MDIOC_REG);
	udelay(50);
	spin_unlock_bh(&priv->enetsw_mdio_lock);
पूर्ण

अटल अंतरभूत पूर्णांक bcm_enet_port_is_rgmii(पूर्णांक portid)
अणु
	वापस portid >= ENETSW_RGMII_PORT0;
पूर्ण

/*
 * enet sw PHY polling
 */
अटल व्योम swphy_poll_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bcm_enet_priv *priv = from_समयr(priv, t, swphy_poll);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < priv->num_ports; i++) अणु
		काष्ठा bcm63xx_enetsw_port *port;
		पूर्णांक val, j, up, advertise, lpa, speed, duplex, media;
		पूर्णांक बाह्यal_phy = bcm_enet_port_is_rgmii(i);
		u8 override;

		port = &priv->used_ports[i];
		अगर (!port->used)
			जारी;

		अगर (port->bypass_link)
			जारी;

		/* dummy पढ़ो to clear */
		क्रम (j = 0; j < 2; j++)
			val = bcmenet_sw_mdio_पढ़ो(priv, बाह्यal_phy,
						   port->phy_id, MII_BMSR);

		अगर (val == 0xffff)
			जारी;

		up = (val & BMSR_LSTATUS) ? 1 : 0;
		अगर (!(up ^ priv->sw_port_link[i]))
			जारी;

		priv->sw_port_link[i] = up;

		/* link changed */
		अगर (!up) अणु
			dev_info(&priv->pdev->dev, "link DOWN on %s\n",
				 port->name);
			enetsw_ग_लिखोb(priv, ENETSW_PORTOV_ENABLE_MASK,
				      ENETSW_PORTOV_REG(i));
			enetsw_ग_लिखोb(priv, ENETSW_PTCTRL_RXDIS_MASK |
				      ENETSW_PTCTRL_TXDIS_MASK,
				      ENETSW_PTCTRL_REG(i));
			जारी;
		पूर्ण

		advertise = bcmenet_sw_mdio_पढ़ो(priv, बाह्यal_phy,
						 port->phy_id, MII_ADVERTISE);

		lpa = bcmenet_sw_mdio_पढ़ो(priv, बाह्यal_phy, port->phy_id,
					   MII_LPA);

		/* figure out media and duplex from advertise and LPA values */
		media = mii_nway_result(lpa & advertise);
		duplex = (media & ADVERTISE_FULL) ? 1 : 0;

		अगर (media & (ADVERTISE_100FULL | ADVERTISE_100HALF))
			speed = 100;
		अन्यथा
			speed = 10;

		अगर (val & BMSR_ESTATEN) अणु
			advertise = bcmenet_sw_mdio_पढ़ो(priv, बाह्यal_phy,
						port->phy_id, MII_CTRL1000);

			lpa = bcmenet_sw_mdio_पढ़ो(priv, बाह्यal_phy,
						port->phy_id, MII_STAT1000);

			अगर (advertise & (ADVERTISE_1000FULL | ADVERTISE_1000HALF)
					&& lpa & (LPA_1000FULL | LPA_1000HALF)) अणु
				speed = 1000;
				duplex = (lpa & LPA_1000FULL);
			पूर्ण
		पूर्ण

		dev_info(&priv->pdev->dev,
			 "link UP on %s, %dMbps, %s-duplex\n",
			 port->name, speed, duplex ? "full" : "half");

		override = ENETSW_PORTOV_ENABLE_MASK |
			ENETSW_PORTOV_LINKUP_MASK;

		अगर (speed == 1000)
			override |= ENETSW_IMPOV_1000_MASK;
		अन्यथा अगर (speed == 100)
			override |= ENETSW_IMPOV_100_MASK;
		अगर (duplex)
			override |= ENETSW_IMPOV_FDX_MASK;

		enetsw_ग_लिखोb(priv, override, ENETSW_PORTOV_REG(i));
		enetsw_ग_लिखोb(priv, 0, ENETSW_PTCTRL_REG(i));
	पूर्ण

	priv->swphy_poll.expires = jअगरfies + HZ;
	add_समयr(&priv->swphy_poll);
पूर्ण

/*
 * खोलो callback, allocate dma rings & buffers and start rx operation
 */
अटल पूर्णांक bcm_enetsw_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा device *kdev;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक size;
	व्योम *p;
	u32 val;

	priv = netdev_priv(dev);
	kdev = &priv->pdev->dev;

	/* mask all पूर्णांकerrupts and request them */
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->tx_chan);

	ret = request_irq(priv->irq_rx, bcm_enet_isr_dma,
			  0, dev->name, dev);
	अगर (ret)
		जाओ out_मुक्तirq;

	अगर (priv->irq_tx != -1) अणु
		ret = request_irq(priv->irq_tx, bcm_enet_isr_dma,
				  0, dev->name, dev);
		अगर (ret)
			जाओ out_मुक्तirq_rx;
	पूर्ण

	/* allocate rx dma ring */
	size = priv->rx_ring_size * माप(काष्ठा bcm_enet_desc);
	p = dma_alloc_coherent(kdev, size, &priv->rx_desc_dma, GFP_KERNEL);
	अगर (!p) अणु
		dev_err(kdev, "cannot allocate rx ring %u\n", size);
		ret = -ENOMEM;
		जाओ out_मुक्तirq_tx;
	पूर्ण

	priv->rx_desc_alloc_size = size;
	priv->rx_desc_cpu = p;

	/* allocate tx dma ring */
	size = priv->tx_ring_size * माप(काष्ठा bcm_enet_desc);
	p = dma_alloc_coherent(kdev, size, &priv->tx_desc_dma, GFP_KERNEL);
	अगर (!p) अणु
		dev_err(kdev, "cannot allocate tx ring\n");
		ret = -ENOMEM;
		जाओ out_मुक्त_rx_ring;
	पूर्ण

	priv->tx_desc_alloc_size = size;
	priv->tx_desc_cpu = p;

	priv->tx_skb = kसुस्मृति(priv->tx_ring_size, माप(काष्ठा sk_buff *),
			       GFP_KERNEL);
	अगर (!priv->tx_skb) अणु
		dev_err(kdev, "cannot allocate tx skb queue\n");
		ret = -ENOMEM;
		जाओ out_मुक्त_tx_ring;
	पूर्ण

	priv->tx_desc_count = priv->tx_ring_size;
	priv->tx_dirty_desc = 0;
	priv->tx_curr_desc = 0;
	spin_lock_init(&priv->tx_lock);

	/* init & fill rx ring with buffers */
	priv->rx_buf = kसुस्मृति(priv->rx_ring_size, माप(व्योम *),
			       GFP_KERNEL);
	अगर (!priv->rx_buf) अणु
		dev_err(kdev, "cannot allocate rx buffer queue\n");
		ret = -ENOMEM;
		जाओ out_मुक्त_tx_skb;
	पूर्ण

	priv->rx_desc_count = 0;
	priv->rx_dirty_desc = 0;
	priv->rx_curr_desc = 0;

	/* disable all ports */
	क्रम (i = 0; i < priv->num_ports; i++) अणु
		enetsw_ग_लिखोb(priv, ENETSW_PORTOV_ENABLE_MASK,
			      ENETSW_PORTOV_REG(i));
		enetsw_ग_लिखोb(priv, ENETSW_PTCTRL_RXDIS_MASK |
			      ENETSW_PTCTRL_TXDIS_MASK,
			      ENETSW_PTCTRL_REG(i));

		priv->sw_port_link[i] = 0;
	पूर्ण

	/* reset mib */
	val = enetsw_पढ़ोb(priv, ENETSW_GMCR_REG);
	val |= ENETSW_GMCR_RST_MIB_MASK;
	enetsw_ग_लिखोb(priv, val, ENETSW_GMCR_REG);
	mdelay(1);
	val &= ~ENETSW_GMCR_RST_MIB_MASK;
	enetsw_ग_लिखोb(priv, val, ENETSW_GMCR_REG);
	mdelay(1);

	/* क्रमce CPU port state */
	val = enetsw_पढ़ोb(priv, ENETSW_IMPOV_REG);
	val |= ENETSW_IMPOV_FORCE_MASK | ENETSW_IMPOV_LINKUP_MASK;
	enetsw_ग_लिखोb(priv, val, ENETSW_IMPOV_REG);

	/* enable चयन क्रमward engine */
	val = enetsw_पढ़ोb(priv, ENETSW_SWMODE_REG);
	val |= ENETSW_SWMODE_FWD_EN_MASK;
	enetsw_ग_लिखोb(priv, val, ENETSW_SWMODE_REG);

	/* enable jumbo on all ports */
	enetsw_ग_लिखोl(priv, 0x1ff, ENETSW_JMBCTL_PORT_REG);
	enetsw_ग_लिखोw(priv, 9728, ENETSW_JMBCTL_MAXSIZE_REG);

	/* initialize flow control buffer allocation */
	enet_dma_ग_लिखोl(priv, ENETDMA_BUFALLOC_FORCE_MASK | 0,
			ENETDMA_BUFALLOC_REG(priv->rx_chan));

	अगर (bcm_enet_refill_rx(dev, false)) अणु
		dev_err(kdev, "cannot allocate rx buffer queue\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* ग_लिखो rx & tx ring addresses */
	enet_dmas_ग_लिखोl(priv, priv->rx_desc_dma,
			 ENETDMAS_RSTART_REG, priv->rx_chan);
	enet_dmas_ग_लिखोl(priv, priv->tx_desc_dma,
			 ENETDMAS_RSTART_REG, priv->tx_chan);

	/* clear reमुख्यing state ram क्रम rx & tx channel */
	enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM2_REG, priv->rx_chan);
	enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM2_REG, priv->tx_chan);
	enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM3_REG, priv->rx_chan);
	enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM3_REG, priv->tx_chan);
	enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM4_REG, priv->rx_chan);
	enet_dmas_ग_लिखोl(priv, 0, ENETDMAS_SRAM4_REG, priv->tx_chan);

	/* set dma maximum burst len */
	enet_dmac_ग_लिखोl(priv, priv->dma_maxburst,
			 ENETDMAC_MAXBURST, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, priv->dma_maxburst,
			 ENETDMAC_MAXBURST, priv->tx_chan);

	/* set flow control low/high threshold to 1/3 / 2/3 */
	val = priv->rx_ring_size / 3;
	enet_dma_ग_लिखोl(priv, val, ENETDMA_FLOWCL_REG(priv->rx_chan));
	val = (priv->rx_ring_size * 2) / 3;
	enet_dma_ग_लिखोl(priv, val, ENETDMA_FLOWCH_REG(priv->rx_chan));

	/* all set, enable mac and पूर्णांकerrupts, start dma engine and
	 * kick rx dma channel
	 */
	wmb();
	enet_dma_ग_लिखोl(priv, ENETDMA_CFG_EN_MASK, ENETDMA_CFG_REG);
	enet_dmac_ग_लिखोl(priv, ENETDMAC_CHANCFG_EN_MASK,
			 ENETDMAC_CHANCFG, priv->rx_chan);

	/* watch "packet transferred" पूर्णांकerrupt in rx and tx */
	enet_dmac_ग_लिखोl(priv, ENETDMAC_IR_PKTDONE_MASK,
			 ENETDMAC_IR, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, ENETDMAC_IR_PKTDONE_MASK,
			 ENETDMAC_IR, priv->tx_chan);

	/* make sure we enable napi beक्रमe rx पूर्णांकerrupt  */
	napi_enable(&priv->napi);

	enet_dmac_ग_लिखोl(priv, ENETDMAC_IR_PKTDONE_MASK,
			 ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, ENETDMAC_IR_PKTDONE_MASK,
			 ENETDMAC_IRMASK, priv->tx_chan);

	netअगर_carrier_on(dev);
	netअगर_start_queue(dev);

	/* apply override config क्रम bypass_link ports here. */
	क्रम (i = 0; i < priv->num_ports; i++) अणु
		काष्ठा bcm63xx_enetsw_port *port;
		u8 override;
		port = &priv->used_ports[i];
		अगर (!port->used)
			जारी;

		अगर (!port->bypass_link)
			जारी;

		override = ENETSW_PORTOV_ENABLE_MASK |
			ENETSW_PORTOV_LINKUP_MASK;

		चयन (port->क्रमce_speed) अणु
		हाल 1000:
			override |= ENETSW_IMPOV_1000_MASK;
			अवरोध;
		हाल 100:
			override |= ENETSW_IMPOV_100_MASK;
			अवरोध;
		हाल 10:
			अवरोध;
		शेष:
			pr_warn("invalid forced speed on port %s: assume 10\n",
			       port->name);
			अवरोध;
		पूर्ण

		अगर (port->क्रमce_duplex_full)
			override |= ENETSW_IMPOV_FDX_MASK;


		enetsw_ग_लिखोb(priv, override, ENETSW_PORTOV_REG(i));
		enetsw_ग_लिखोb(priv, 0, ENETSW_PTCTRL_REG(i));
	पूर्ण

	/* start phy polling समयr */
	समयr_setup(&priv->swphy_poll, swphy_poll_समयr, 0);
	mod_समयr(&priv->swphy_poll, jअगरfies);
	वापस 0;

out:
	bcm_enet_मुक्त_rx_buf_ring(kdev, priv);

out_मुक्त_tx_skb:
	kमुक्त(priv->tx_skb);

out_मुक्त_tx_ring:
	dma_मुक्त_coherent(kdev, priv->tx_desc_alloc_size,
			  priv->tx_desc_cpu, priv->tx_desc_dma);

out_मुक्त_rx_ring:
	dma_मुक्त_coherent(kdev, priv->rx_desc_alloc_size,
			  priv->rx_desc_cpu, priv->rx_desc_dma);

out_मुक्तirq_tx:
	अगर (priv->irq_tx != -1)
		मुक्त_irq(priv->irq_tx, dev);

out_मुक्तirq_rx:
	मुक्त_irq(priv->irq_rx, dev);

out_मुक्तirq:
	वापस ret;
पूर्ण

/* stop callback */
अटल पूर्णांक bcm_enetsw_stop(काष्ठा net_device *dev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा device *kdev;

	priv = netdev_priv(dev);
	kdev = &priv->pdev->dev;

	del_समयr_sync(&priv->swphy_poll);
	netअगर_stop_queue(dev);
	napi_disable(&priv->napi);
	del_समयr_sync(&priv->rx_समयout);

	/* mask all पूर्णांकerrupts */
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_ग_लिखोl(priv, 0, ENETDMAC_IRMASK, priv->tx_chan);

	/* disable dma & mac */
	bcm_enet_disable_dma(priv, priv->tx_chan);
	bcm_enet_disable_dma(priv, priv->rx_chan);

	/* क्रमce reclaim of all tx buffers */
	bcm_enet_tx_reclaim(dev, 1);

	/* मुक्त the rx buffer ring */
	bcm_enet_मुक्त_rx_buf_ring(kdev, priv);

	/* मुक्त reमुख्यing allocated memory */
	kमुक्त(priv->tx_skb);
	dma_मुक्त_coherent(kdev, priv->rx_desc_alloc_size,
			  priv->rx_desc_cpu, priv->rx_desc_dma);
	dma_मुक्त_coherent(kdev, priv->tx_desc_alloc_size,
			  priv->tx_desc_cpu, priv->tx_desc_dma);
	अगर (priv->irq_tx != -1)
		मुक्त_irq(priv->irq_tx, dev);
	मुक्त_irq(priv->irq_rx, dev);

	/* reset BQL after क्रमced tx reclaim to prevent kernel panic */
	netdev_reset_queue(dev);

	वापस 0;
पूर्ण

/* try to sort out phy बाह्यal status by walking the used_port field
 * in the bcm_enet_priv काष्ठाure. in हाल the phy address is not
 * asचिन्हित to any physical port on the चयन, assume it is बाह्यal
 * (and yell at the user).
 */
अटल पूर्णांक bcm_enetsw_phy_is_बाह्यal(काष्ठा bcm_enet_priv *priv, पूर्णांक phy_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_ports; ++i) अणु
		अगर (!priv->used_ports[i].used)
			जारी;
		अगर (priv->used_ports[i].phy_id == phy_id)
			वापस bcm_enet_port_is_rgmii(i);
	पूर्ण

	prपूर्णांकk_once(KERN_WARNING  "bcm63xx_enet: could not find a used port with phy_id %i, assuming phy is external\n",
		    phy_id);
	वापस 1;
पूर्ण

/* can't use bcmenet_sw_mdio_पढ़ो directly as we need to sort out
 * बाह्यal/पूर्णांकernal status of the given phy_id first.
 */
अटल पूर्णांक bcm_enetsw_mii_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id,
				    पूर्णांक location)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	वापस bcmenet_sw_mdio_पढ़ो(priv,
				    bcm_enetsw_phy_is_बाह्यal(priv, phy_id),
				    phy_id, location);
पूर्ण

/* can't use bcmenet_sw_mdio_ग_लिखो directly as we need to sort out
 * बाह्यal/पूर्णांकernal status of the given phy_id first.
 */
अटल व्योम bcm_enetsw_mii_mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id,
				      पूर्णांक location,
				      पूर्णांक val)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	bcmenet_sw_mdio_ग_लिखो(priv, bcm_enetsw_phy_is_बाह्यal(priv, phy_id),
			      phy_id, location, val);
पूर्ण

अटल पूर्णांक bcm_enetsw_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा mii_अगर_info mii;

	mii.dev = dev;
	mii.mdio_पढ़ो = bcm_enetsw_mii_mdio_पढ़ो;
	mii.mdio_ग_लिखो = bcm_enetsw_mii_mdio_ग_लिखो;
	mii.phy_id = 0;
	mii.phy_id_mask = 0x3f;
	mii.reg_num_mask = 0x1f;
	वापस generic_mii_ioctl(&mii, अगर_mii(rq), cmd, शून्य);

पूर्ण

अटल स्थिर काष्ठा net_device_ops bcm_enetsw_ops = अणु
	.nकरो_खोलो		= bcm_enetsw_खोलो,
	.nकरो_stop		= bcm_enetsw_stop,
	.nकरो_start_xmit		= bcm_enet_start_xmit,
	.nकरो_change_mtu		= bcm_enet_change_mtu,
	.nकरो_करो_ioctl		= bcm_enetsw_ioctl,
पूर्ण;


अटल स्थिर काष्ठा bcm_enet_stats bcm_enetsw_gstrings_stats[] = अणु
	अणु "rx_packets", DEV_STAT(rx_packets), -1 पूर्ण,
	अणु "tx_packets",	DEV_STAT(tx_packets), -1 पूर्ण,
	अणु "rx_bytes", DEV_STAT(rx_bytes), -1 पूर्ण,
	अणु "tx_bytes", DEV_STAT(tx_bytes), -1 पूर्ण,
	अणु "rx_errors", DEV_STAT(rx_errors), -1 पूर्ण,
	अणु "tx_errors", DEV_STAT(tx_errors), -1 पूर्ण,
	अणु "rx_dropped",	DEV_STAT(rx_dropped), -1 पूर्ण,
	अणु "tx_dropped",	DEV_STAT(tx_dropped), -1 पूर्ण,

	अणु "tx_good_octets", GEN_STAT(mib.tx_gd_octets), ETHSW_MIB_RX_GD_OCT पूर्ण,
	अणु "tx_unicast", GEN_STAT(mib.tx_unicast), ETHSW_MIB_RX_BRDCAST पूर्ण,
	अणु "tx_broadcast", GEN_STAT(mib.tx_brdcast), ETHSW_MIB_RX_BRDCAST पूर्ण,
	अणु "tx_multicast", GEN_STAT(mib.tx_mult), ETHSW_MIB_RX_MULT पूर्ण,
	अणु "tx_64_octets", GEN_STAT(mib.tx_64), ETHSW_MIB_RX_64 पूर्ण,
	अणु "tx_65_127_oct", GEN_STAT(mib.tx_65_127), ETHSW_MIB_RX_65_127 पूर्ण,
	अणु "tx_128_255_oct", GEN_STAT(mib.tx_128_255), ETHSW_MIB_RX_128_255 पूर्ण,
	अणु "tx_256_511_oct", GEN_STAT(mib.tx_256_511), ETHSW_MIB_RX_256_511 पूर्ण,
	अणु "tx_512_1023_oct", GEN_STAT(mib.tx_512_1023), ETHSW_MIB_RX_512_1023पूर्ण,
	अणु "tx_1024_1522_oct", GEN_STAT(mib.tx_1024_max),
	  ETHSW_MIB_RX_1024_1522 पूर्ण,
	अणु "tx_1523_2047_oct", GEN_STAT(mib.tx_1523_2047),
	  ETHSW_MIB_RX_1523_2047 पूर्ण,
	अणु "tx_2048_4095_oct", GEN_STAT(mib.tx_2048_4095),
	  ETHSW_MIB_RX_2048_4095 पूर्ण,
	अणु "tx_4096_8191_oct", GEN_STAT(mib.tx_4096_8191),
	  ETHSW_MIB_RX_4096_8191 पूर्ण,
	अणु "tx_8192_9728_oct", GEN_STAT(mib.tx_8192_9728),
	  ETHSW_MIB_RX_8192_9728 पूर्ण,
	अणु "tx_oversize", GEN_STAT(mib.tx_ovr), ETHSW_MIB_RX_OVR पूर्ण,
	अणु "tx_oversize_drop", GEN_STAT(mib.tx_ovr), ETHSW_MIB_RX_OVR_DISC पूर्ण,
	अणु "tx_dropped",	GEN_STAT(mib.tx_drop), ETHSW_MIB_RX_DROP पूर्ण,
	अणु "tx_undersize", GEN_STAT(mib.tx_underrun), ETHSW_MIB_RX_UND पूर्ण,
	अणु "tx_pause", GEN_STAT(mib.tx_छोड़ो), ETHSW_MIB_RX_PAUSE पूर्ण,

	अणु "rx_good_octets", GEN_STAT(mib.rx_gd_octets), ETHSW_MIB_TX_ALL_OCT पूर्ण,
	अणु "rx_broadcast", GEN_STAT(mib.rx_brdcast), ETHSW_MIB_TX_BRDCAST पूर्ण,
	अणु "rx_multicast", GEN_STAT(mib.rx_mult), ETHSW_MIB_TX_MULT पूर्ण,
	अणु "rx_unicast", GEN_STAT(mib.rx_unicast), ETHSW_MIB_TX_MULT पूर्ण,
	अणु "rx_pause", GEN_STAT(mib.rx_छोड़ो), ETHSW_MIB_TX_PAUSE पूर्ण,
	अणु "rx_dropped", GEN_STAT(mib.rx_drop), ETHSW_MIB_TX_DROP_PKTS पूर्ण,

पूर्ण;

#घोषणा BCM_ENETSW_STATS_LEN	\
	(माप(bcm_enetsw_gstrings_stats) / माप(काष्ठा bcm_enet_stats))

अटल व्योम bcm_enetsw_get_strings(काष्ठा net_device *netdev,
				   u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < BCM_ENETSW_STATS_LEN; i++) अणु
			स_नकल(data + i * ETH_GSTRING_LEN,
			       bcm_enetsw_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_enetsw_get_sset_count(काष्ठा net_device *netdev,
				     पूर्णांक string_set)
अणु
	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		वापस BCM_ENETSW_STATS_LEN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम bcm_enetsw_get_drvinfo(काष्ठा net_device *netdev,
				   काष्ठा ethtool_drvinfo *drvinfo)
अणु
	म_नकलन(drvinfo->driver, bcm_enet_driver_name, माप(drvinfo->driver));
	म_नकलन(drvinfo->bus_info, "bcm63xx", माप(drvinfo->bus_info));
पूर्ण

अटल व्योम bcm_enetsw_get_ethtool_stats(काष्ठा net_device *netdev,
					 काष्ठा ethtool_stats *stats,
					 u64 *data)
अणु
	काष्ठा bcm_enet_priv *priv;
	पूर्णांक i;

	priv = netdev_priv(netdev);

	क्रम (i = 0; i < BCM_ENETSW_STATS_LEN; i++) अणु
		स्थिर काष्ठा bcm_enet_stats *s;
		u32 lo, hi;
		अक्षर *p;
		पूर्णांक reg;

		s = &bcm_enetsw_gstrings_stats[i];

		reg = s->mib_reg;
		अगर (reg == -1)
			जारी;

		lo = enetsw_पढ़ोl(priv, ENETSW_MIB_REG(reg));
		p = (अक्षर *)priv + s->stat_offset;

		अगर (s->माप_stat == माप(u64)) अणु
			hi = enetsw_पढ़ोl(priv, ENETSW_MIB_REG(reg + 1));
			*(u64 *)p = ((u64)hi << 32 | lo);
		पूर्ण अन्यथा अणु
			*(u32 *)p = lo;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < BCM_ENETSW_STATS_LEN; i++) अणु
		स्थिर काष्ठा bcm_enet_stats *s;
		अक्षर *p;

		s = &bcm_enetsw_gstrings_stats[i];

		अगर (s->mib_reg == -1)
			p = (अक्षर *)&netdev->stats + s->stat_offset;
		अन्यथा
			p = (अक्षर *)priv + s->stat_offset;

		data[i] = (s->माप_stat == माप(u64)) ?
			*(u64 *)p : *(u32 *)p;
	पूर्ण
पूर्ण

अटल व्योम bcm_enetsw_get_ringparam(काष्ठा net_device *dev,
				     काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bcm_enet_priv *priv;

	priv = netdev_priv(dev);

	/* rx/tx ring is actually only limited by memory */
	ering->rx_max_pending = 8192;
	ering->tx_max_pending = 8192;
	ering->rx_mini_max_pending = 0;
	ering->rx_jumbo_max_pending = 0;
	ering->rx_pending = priv->rx_ring_size;
	ering->tx_pending = priv->tx_ring_size;
पूर्ण

अटल पूर्णांक bcm_enetsw_set_ringparam(काष्ठा net_device *dev,
				    काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bcm_enet_priv *priv;
	पूर्णांक was_running;

	priv = netdev_priv(dev);

	was_running = 0;
	अगर (netअगर_running(dev)) अणु
		bcm_enetsw_stop(dev);
		was_running = 1;
	पूर्ण

	priv->rx_ring_size = ering->rx_pending;
	priv->tx_ring_size = ering->tx_pending;

	अगर (was_running) अणु
		पूर्णांक err;

		err = bcm_enetsw_खोलो(dev);
		अगर (err)
			dev_बंद(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bcm_enetsw_ethtool_ops = अणु
	.get_strings		= bcm_enetsw_get_strings,
	.get_sset_count		= bcm_enetsw_get_sset_count,
	.get_ethtool_stats      = bcm_enetsw_get_ethtool_stats,
	.get_drvinfo		= bcm_enetsw_get_drvinfo,
	.get_ringparam		= bcm_enetsw_get_ringparam,
	.set_ringparam		= bcm_enetsw_set_ringparam,
पूर्ण;

/* allocate netdevice, request रेजिस्टर memory and रेजिस्टर device. */
अटल पूर्णांक bcm_enetsw_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा net_device *dev;
	काष्ठा bcm63xx_enetsw_platक्रमm_data *pd;
	काष्ठा resource *res_mem;
	पूर्णांक ret, irq_rx, irq_tx;

	अगर (!bcm_enet_shared_base[0])
		वापस -EPROBE_DEFER;

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq_rx = platक्रमm_get_irq(pdev, 0);
	irq_tx = platक्रमm_get_irq(pdev, 1);
	अगर (!res_mem || irq_rx < 0)
		वापस -ENODEV;

	ret = 0;
	dev = alloc_etherdev(माप(*priv));
	अगर (!dev)
		वापस -ENOMEM;
	priv = netdev_priv(dev);

	/* initialize शेष and fetch platक्रमm data */
	priv->enet_is_sw = true;
	priv->irq_rx = irq_rx;
	priv->irq_tx = irq_tx;
	priv->rx_ring_size = BCMENET_DEF_RX_DESC;
	priv->tx_ring_size = BCMENET_DEF_TX_DESC;
	priv->dma_maxburst = BCMENETSW_DMA_MAXBURST;
	priv->rx_buf_offset = NET_SKB_PAD + NET_IP_ALIGN;

	pd = dev_get_platdata(&pdev->dev);
	अगर (pd) अणु
		स_नकल(dev->dev_addr, pd->mac_addr, ETH_ALEN);
		स_नकल(priv->used_ports, pd->used_ports,
		       माप(pd->used_ports));
		priv->num_ports = pd->num_ports;
		priv->dma_has_sram = pd->dma_has_sram;
		priv->dma_chan_en_mask = pd->dma_chan_en_mask;
		priv->dma_chan_पूर्णांक_mask = pd->dma_chan_पूर्णांक_mask;
		priv->dma_chan_width = pd->dma_chan_width;
	पूर्ण

	ret = bcm_enet_change_mtu(dev, dev->mtu);
	अगर (ret)
		जाओ out;

	priv->base = devm_ioremap_resource(&pdev->dev, res_mem);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ out;
	पूर्ण

	priv->mac_clk = devm_clk_get(&pdev->dev, "enetsw");
	अगर (IS_ERR(priv->mac_clk)) अणु
		ret = PTR_ERR(priv->mac_clk);
		जाओ out;
	पूर्ण
	ret = clk_prepare_enable(priv->mac_clk);
	अगर (ret)
		जाओ out;

	priv->rx_chan = 0;
	priv->tx_chan = 1;
	spin_lock_init(&priv->rx_lock);

	/* init rx समयout (used क्रम oom) */
	समयr_setup(&priv->rx_समयout, bcm_enet_refill_rx_समयr, 0);

	/* रेजिस्टर netdevice */
	dev->netdev_ops = &bcm_enetsw_ops;
	netअगर_napi_add(dev, &priv->napi, bcm_enet_poll, 16);
	dev->ethtool_ops = &bcm_enetsw_ethtool_ops;
	SET_NETDEV_DEV(dev, &pdev->dev);

	spin_lock_init(&priv->enetsw_mdio_lock);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ out_disable_clk;

	netअगर_carrier_off(dev);
	platक्रमm_set_drvdata(pdev, dev);
	priv->pdev = pdev;
	priv->net_dev = dev;

	वापस 0;

out_disable_clk:
	clk_disable_unprepare(priv->mac_clk);
out:
	मुक्त_netdev(dev);
	वापस ret;
पूर्ण


/* निकास func, stops hardware and unरेजिस्टरs netdevice */
अटल पूर्णांक bcm_enetsw_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_enet_priv *priv;
	काष्ठा net_device *dev;

	/* stop netdevice */
	dev = platक्रमm_get_drvdata(pdev);
	priv = netdev_priv(dev);
	unरेजिस्टर_netdev(dev);

	clk_disable_unprepare(priv->mac_clk);

	मुक्त_netdev(dev);
	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver bcm63xx_enetsw_driver = अणु
	.probe	= bcm_enetsw_probe,
	.हटाओ	= bcm_enetsw_हटाओ,
	.driver	= अणु
		.name	= "bcm63xx_enetsw",
		.owner  = THIS_MODULE,
	पूर्ण,
पूर्ण;

/* reserve & remap memory space shared between all macs */
अटल पूर्णांक bcm_enet_shared_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *p[3];
	अचिन्हित पूर्णांक i;

	स_रखो(bcm_enet_shared_base, 0, माप(bcm_enet_shared_base));

	क्रम (i = 0; i < 3; i++) अणु
		p[i] = devm_platक्रमm_ioremap_resource(pdev, i);
		अगर (IS_ERR(p[i]))
			वापस PTR_ERR(p[i]);
	पूर्ण

	स_नकल(bcm_enet_shared_base, p, माप(bcm_enet_shared_base));

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_enet_shared_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

/* this "shared" driver is needed because both macs share a single
 * address space
 */
काष्ठा platक्रमm_driver bcm63xx_enet_shared_driver = अणु
	.probe	= bcm_enet_shared_probe,
	.हटाओ	= bcm_enet_shared_हटाओ,
	.driver	= अणु
		.name	= "bcm63xx_enet_shared",
		.owner  = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
	&bcm63xx_enet_shared_driver,
	&bcm63xx_enet_driver,
	&bcm63xx_enetsw_driver,
पूर्ण;

/* entry poपूर्णांक */
अटल पूर्णांक __init bcm_enet_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण

अटल व्योम __निकास bcm_enet_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण


module_init(bcm_enet_init);
module_निकास(bcm_enet_निकास);

MODULE_DESCRIPTION("BCM63xx internal ethernet mac driver");
MODULE_AUTHOR("Maxime Bizon <mbizon@freebox.fr>");
MODULE_LICENSE("GPL");
