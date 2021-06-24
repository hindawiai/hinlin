<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004-2013 Synopsys, Inc. (www.synopsys.com)
 *
 * Driver क्रम the ARC EMAC 10100 (hardware revision 5)
 *
 * Contributors:
 *		Amit Bhor
 *		Sameer Dhavale
 *		Vineet Gupta
 */

#समावेश <linux/crc32.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश "emac.h"

अटल व्योम arc_emac_restart(काष्ठा net_device *ndev);

/**
 * arc_emac_tx_avail - Return the number of available slots in the tx ring.
 * @priv: Poपूर्णांकer to ARC EMAC निजी data काष्ठाure.
 *
 * वापसs: the number of slots available क्रम transmission in tx the ring.
 */
अटल अंतरभूत पूर्णांक arc_emac_tx_avail(काष्ठा arc_emac_priv *priv)
अणु
	वापस (priv->txbd_dirty + TX_BD_NUM - priv->txbd_curr - 1) % TX_BD_NUM;
पूर्ण

/**
 * arc_emac_adjust_link - Adjust the PHY link duplex.
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure.
 *
 * This function is called to change the duplex setting after स्वतः negotiation
 * is करोne by the PHY.
 */
अटल व्योम arc_emac_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phy_dev = ndev->phydev;
	अचिन्हित पूर्णांक reg, state_changed = 0;

	अगर (priv->link != phy_dev->link) अणु
		priv->link = phy_dev->link;
		state_changed = 1;
	पूर्ण

	अगर (priv->speed != phy_dev->speed) अणु
		priv->speed = phy_dev->speed;
		state_changed = 1;
		अगर (priv->set_mac_speed)
			priv->set_mac_speed(priv, priv->speed);
	पूर्ण

	अगर (priv->duplex != phy_dev->duplex) अणु
		reg = arc_reg_get(priv, R_CTRL);

		अगर (phy_dev->duplex == DUPLEX_FULL)
			reg |= ENFL_MASK;
		अन्यथा
			reg &= ~ENFL_MASK;

		arc_reg_set(priv, R_CTRL, reg);
		priv->duplex = phy_dev->duplex;
		state_changed = 1;
	पूर्ण

	अगर (state_changed)
		phy_prपूर्णांक_status(phy_dev);
पूर्ण

/**
 * arc_emac_get_drvinfo - Get EMAC driver inक्रमmation.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure.
 * @info:	Poपूर्णांकer to ethtool_drvinfo काष्ठाure.
 *
 * This implements ethtool command क्रम getting the driver inक्रमmation.
 * Issue "ethtool -i ethX" under linux prompt to execute this function.
 */
अटल व्योम arc_emac_get_drvinfo(काष्ठा net_device *ndev,
				 काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);

	strlcpy(info->driver, priv->drv_name, माप(info->driver));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops arc_emac_ethtool_ops = अणु
	.get_drvinfo	= arc_emac_get_drvinfo,
	.get_link	= ethtool_op_get_link,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

#घोषणा FIRST_OR_LAST_MASK	(FIRST_MASK | LAST_MASK)

/**
 * arc_emac_tx_clean - clears processed by EMAC Tx BDs.
 * @ndev:	Poपूर्णांकer to the network device.
 */
अटल व्योम arc_emac_tx_clean(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < TX_BD_NUM; i++) अणु
		अचिन्हित पूर्णांक *txbd_dirty = &priv->txbd_dirty;
		काष्ठा arc_emac_bd *txbd = &priv->txbd[*txbd_dirty];
		काष्ठा buffer_state *tx_buff = &priv->tx_buff[*txbd_dirty];
		काष्ठा sk_buff *skb = tx_buff->skb;
		अचिन्हित पूर्णांक info = le32_to_cpu(txbd->info);

		अगर ((info & FOR_EMAC) || !txbd->data || !skb)
			अवरोध;

		अगर (unlikely(info & (DROP | DEFR | LTCL | UFLO))) अणु
			stats->tx_errors++;
			stats->tx_dropped++;

			अगर (info & DEFR)
				stats->tx_carrier_errors++;

			अगर (info & LTCL)
				stats->collisions++;

			अगर (info & UFLO)
				stats->tx_fअगरo_errors++;
		पूर्ण अन्यथा अगर (likely(info & FIRST_OR_LAST_MASK)) अणु
			stats->tx_packets++;
			stats->tx_bytes += skb->len;
		पूर्ण

		dma_unmap_single(&ndev->dev, dma_unmap_addr(tx_buff, addr),
				 dma_unmap_len(tx_buff, len), DMA_TO_DEVICE);

		/* वापस the sk_buff to प्रणाली */
		dev_consume_skb_irq(skb);

		txbd->data = 0;
		txbd->info = 0;
		tx_buff->skb = शून्य;

		*txbd_dirty = (*txbd_dirty + 1) % TX_BD_NUM;
	पूर्ण

	/* Ensure that txbd_dirty is visible to tx() beक्रमe checking
	 * क्रम queue stopped.
	 */
	smp_mb();

	अगर (netअगर_queue_stopped(ndev) && arc_emac_tx_avail(priv))
		netअगर_wake_queue(ndev);
पूर्ण

/**
 * arc_emac_rx - processing of Rx packets.
 * @ndev:	Poपूर्णांकer to the network device.
 * @budget:	How many BDs to process on 1 call.
 *
 * वापसs:	Number of processed BDs
 *
 * Iterate through Rx BDs and deliver received packages to upper layer.
 */
अटल पूर्णांक arc_emac_rx(काष्ठा net_device *ndev, पूर्णांक budget)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक work_करोne;

	क्रम (work_करोne = 0; work_करोne < budget; work_करोne++) अणु
		अचिन्हित पूर्णांक *last_rx_bd = &priv->last_rx_bd;
		काष्ठा net_device_stats *stats = &ndev->stats;
		काष्ठा buffer_state *rx_buff = &priv->rx_buff[*last_rx_bd];
		काष्ठा arc_emac_bd *rxbd = &priv->rxbd[*last_rx_bd];
		अचिन्हित पूर्णांक pktlen, info = le32_to_cpu(rxbd->info);
		काष्ठा sk_buff *skb;
		dma_addr_t addr;

		अगर (unlikely((info & OWN_MASK) == FOR_EMAC))
			अवरोध;

		/* Make a note that we saw a packet at this BD.
		 * So next समय, driver starts from this + 1
		 */
		*last_rx_bd = (*last_rx_bd + 1) % RX_BD_NUM;

		अगर (unlikely((info & FIRST_OR_LAST_MASK) !=
			     FIRST_OR_LAST_MASK)) अणु
			/* We pre-allocate buffers of MTU size so incoming
			 * packets won't be split/chained.
			 */
			अगर (net_ratelimit())
				netdev_err(ndev, "incomplete packet received\n");

			/* Return ownership to EMAC */
			rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);
			stats->rx_errors++;
			stats->rx_length_errors++;
			जारी;
		पूर्ण

		/* Prepare the BD क्रम next cycle. netअगर_receive_skb()
		 * only अगर new skb was allocated and mapped to aव्योम holes
		 * in the RX fअगरo.
		 */
		skb = netdev_alloc_skb_ip_align(ndev, EMAC_BUFFER_SIZE);
		अगर (unlikely(!skb)) अणु
			अगर (net_ratelimit())
				netdev_err(ndev, "cannot allocate skb\n");
			/* Return ownership to EMAC */
			rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);
			stats->rx_errors++;
			stats->rx_dropped++;
			जारी;
		पूर्ण

		addr = dma_map_single(&ndev->dev, (व्योम *)skb->data,
				      EMAC_BUFFER_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&ndev->dev, addr)) अणु
			अगर (net_ratelimit())
				netdev_err(ndev, "cannot map dma buffer\n");
			dev_kमुक्त_skb(skb);
			/* Return ownership to EMAC */
			rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);
			stats->rx_errors++;
			stats->rx_dropped++;
			जारी;
		पूर्ण

		/* unmap previosly mapped skb */
		dma_unmap_single(&ndev->dev, dma_unmap_addr(rx_buff, addr),
				 dma_unmap_len(rx_buff, len), DMA_FROM_DEVICE);

		pktlen = info & LEN_MASK;
		stats->rx_packets++;
		stats->rx_bytes += pktlen;
		skb_put(rx_buff->skb, pktlen);
		rx_buff->skb->dev = ndev;
		rx_buff->skb->protocol = eth_type_trans(rx_buff->skb, ndev);

		netअगर_receive_skb(rx_buff->skb);

		rx_buff->skb = skb;
		dma_unmap_addr_set(rx_buff, addr, addr);
		dma_unmap_len_set(rx_buff, len, EMAC_BUFFER_SIZE);

		rxbd->data = cpu_to_le32(addr);

		/* Make sure poपूर्णांकer to data buffer is set */
		wmb();

		/* Return ownership to EMAC */
		rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);
	पूर्ण

	वापस work_करोne;
पूर्ण

/**
 * arc_emac_rx_miss_handle - handle R_MISS रेजिस्टर
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure.
 */
अटल व्योम arc_emac_rx_miss_handle(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	अचिन्हित पूर्णांक miss;

	miss = arc_reg_get(priv, R_MISS);
	अगर (miss) अणु
		stats->rx_errors += miss;
		stats->rx_missed_errors += miss;
		priv->rx_missed_errors += miss;
	पूर्ण
पूर्ण

/**
 * arc_emac_rx_stall_check - check RX stall
 * @ndev:	Poपूर्णांकer to the net_device काष्ठाure.
 * @budget:	How many BDs requested to process on 1 call.
 * @work_करोne:	How many BDs processed
 *
 * Under certain conditions EMAC stop reception of incoming packets and
 * continuously increment R_MISS रेजिस्टर instead of saving data पूर्णांकo
 * provided buffer. This function detect that condition and restart
 * EMAC.
 */
अटल व्योम arc_emac_rx_stall_check(काष्ठा net_device *ndev,
				    पूर्णांक budget, अचिन्हित पूर्णांक work_करोne)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	काष्ठा arc_emac_bd *rxbd;

	अगर (work_करोne)
		priv->rx_missed_errors = 0;

	अगर (priv->rx_missed_errors && budget) अणु
		rxbd = &priv->rxbd[priv->last_rx_bd];
		अगर (le32_to_cpu(rxbd->info) & FOR_EMAC) अणु
			arc_emac_restart(ndev);
			priv->rx_missed_errors = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * arc_emac_poll - NAPI poll handler.
 * @napi:	Poपूर्णांकer to napi_काष्ठा काष्ठाure.
 * @budget:	How many BDs to process on 1 call.
 *
 * वापसs:	Number of processed BDs
 */
अटल पूर्णांक arc_emac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा net_device *ndev = napi->dev;
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक work_करोne;

	arc_emac_tx_clean(ndev);
	arc_emac_rx_miss_handle(ndev);

	work_करोne = arc_emac_rx(ndev, budget);
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		arc_reg_or(priv, R_ENABLE, RXINT_MASK | TXINT_MASK);
	पूर्ण

	arc_emac_rx_stall_check(ndev, budget, work_करोne);

	वापस work_करोne;
पूर्ण

/**
 * arc_emac_पूर्णांकr - Global पूर्णांकerrupt handler क्रम EMAC.
 * @irq:		irq number.
 * @dev_instance:	device instance.
 *
 * वापसs: IRQ_HANDLED क्रम all हालs.
 *
 * ARC EMAC has only 1 पूर्णांकerrupt line, and depending on bits उठाओd in
 * STATUS रेजिस्टर we may tell what is a reason क्रम पूर्णांकerrupt to fire.
 */
अटल irqवापस_t arc_emac_पूर्णांकr(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *ndev = dev_instance;
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	अचिन्हित पूर्णांक status;

	status = arc_reg_get(priv, R_STATUS);
	status &= ~MDIO_MASK;

	/* Reset all flags except "MDIO complete" */
	arc_reg_set(priv, R_STATUS, status);

	अगर (status & (RXINT_MASK | TXINT_MASK)) अणु
		अगर (likely(napi_schedule_prep(&priv->napi))) अणु
			arc_reg_clr(priv, R_ENABLE, RXINT_MASK | TXINT_MASK);
			__napi_schedule(&priv->napi);
		पूर्ण
	पूर्ण

	अगर (status & ERR_MASK) अणु
		/* MSER/RXCR/RXFR/RXFL पूर्णांकerrupt fires on corresponding
		 * 8-bit error counter overrun.
		 */

		अगर (status & MSER_MASK) अणु
			stats->rx_missed_errors += 0x100;
			stats->rx_errors += 0x100;
			priv->rx_missed_errors += 0x100;
			napi_schedule(&priv->napi);
		पूर्ण

		अगर (status & RXCR_MASK) अणु
			stats->rx_crc_errors += 0x100;
			stats->rx_errors += 0x100;
		पूर्ण

		अगर (status & RXFR_MASK) अणु
			stats->rx_frame_errors += 0x100;
			stats->rx_errors += 0x100;
		पूर्ण

		अगर (status & RXFL_MASK) अणु
			stats->rx_over_errors += 0x100;
			stats->rx_errors += 0x100;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम arc_emac_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	arc_emac_पूर्णांकr(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/**
 * arc_emac_खोलो - Open the network device.
 * @ndev:	Poपूर्णांकer to the network device.
 *
 * वापसs: 0, on success or non-zero error value on failure.
 *
 * This function sets the MAC address, requests and enables an IRQ
 * क्रम the EMAC device and starts the Tx queue.
 * It also connects to the phy device.
 */
अटल पूर्णांक arc_emac_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phy_dev = ndev->phydev;
	पूर्णांक i;

	phy_dev->स्वतःneg = AUTONEG_ENABLE;
	phy_dev->speed = 0;
	phy_dev->duplex = 0;
	linkmode_and(phy_dev->advertising, phy_dev->advertising,
		     phy_dev->supported);

	priv->last_rx_bd = 0;

	/* Allocate and set buffers क्रम Rx BD's */
	क्रम (i = 0; i < RX_BD_NUM; i++) अणु
		dma_addr_t addr;
		अचिन्हित पूर्णांक *last_rx_bd = &priv->last_rx_bd;
		काष्ठा arc_emac_bd *rxbd = &priv->rxbd[*last_rx_bd];
		काष्ठा buffer_state *rx_buff = &priv->rx_buff[*last_rx_bd];

		rx_buff->skb = netdev_alloc_skb_ip_align(ndev,
							 EMAC_BUFFER_SIZE);
		अगर (unlikely(!rx_buff->skb))
			वापस -ENOMEM;

		addr = dma_map_single(&ndev->dev, (व्योम *)rx_buff->skb->data,
				      EMAC_BUFFER_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&ndev->dev, addr)) अणु
			netdev_err(ndev, "cannot dma map\n");
			dev_kमुक्त_skb(rx_buff->skb);
			वापस -ENOMEM;
		पूर्ण
		dma_unmap_addr_set(rx_buff, addr, addr);
		dma_unmap_len_set(rx_buff, len, EMAC_BUFFER_SIZE);

		rxbd->data = cpu_to_le32(addr);

		/* Make sure poपूर्णांकer to data buffer is set */
		wmb();

		/* Return ownership to EMAC */
		rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);

		*last_rx_bd = (*last_rx_bd + 1) % RX_BD_NUM;
	पूर्ण

	priv->txbd_curr = 0;
	priv->txbd_dirty = 0;

	/* Clean Tx BD's */
	स_रखो(priv->txbd, 0, TX_RING_SZ);

	/* Initialize logical address filter */
	arc_reg_set(priv, R_LAFL, 0);
	arc_reg_set(priv, R_LAFH, 0);

	/* Set BD ring poपूर्णांकers क्रम device side */
	arc_reg_set(priv, R_RX_RING, (अचिन्हित पूर्णांक)priv->rxbd_dma);
	arc_reg_set(priv, R_TX_RING, (अचिन्हित पूर्णांक)priv->txbd_dma);

	/* Enable पूर्णांकerrupts */
	arc_reg_set(priv, R_ENABLE, RXINT_MASK | TXINT_MASK | ERR_MASK);

	/* Set CONTROL */
	arc_reg_set(priv, R_CTRL,
		    (RX_BD_NUM << 24) |	/* RX BD table length */
		    (TX_BD_NUM << 16) |	/* TX BD table length */
		    TXRN_MASK | RXRN_MASK);

	napi_enable(&priv->napi);

	/* Enable EMAC */
	arc_reg_or(priv, R_CTRL, EN_MASK);

	phy_start(ndev->phydev);

	netअगर_start_queue(ndev);

	वापस 0;
पूर्ण

/**
 * arc_emac_set_rx_mode - Change the receive filtering mode.
 * @ndev:	Poपूर्णांकer to the network device.
 *
 * This function enables/disables promiscuous or all-multicast mode
 * and updates the multicast filtering list of the network device.
 */
अटल व्योम arc_emac_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);

	अगर (ndev->flags & IFF_PROMISC) अणु
		arc_reg_or(priv, R_CTRL, PROM_MASK);
	पूर्ण अन्यथा अणु
		arc_reg_clr(priv, R_CTRL, PROM_MASK);

		अगर (ndev->flags & IFF_ALLMULTI) अणु
			arc_reg_set(priv, R_LAFL, ~0);
			arc_reg_set(priv, R_LAFH, ~0);
		पूर्ण अन्यथा अगर (ndev->flags & IFF_MULTICAST) अणु
			काष्ठा netdev_hw_addr *ha;
			अचिन्हित पूर्णांक filter[2] = अणु 0, 0 पूर्ण;
			पूर्णांक bit;

			netdev_क्रम_each_mc_addr(ha, ndev) अणु
				bit = ether_crc_le(ETH_ALEN, ha->addr) >> 26;
				filter[bit >> 5] |= 1 << (bit & 31);
			पूर्ण

			arc_reg_set(priv, R_LAFL, filter[0]);
			arc_reg_set(priv, R_LAFH, filter[1]);
		पूर्ण अन्यथा अणु
			arc_reg_set(priv, R_LAFL, 0);
			arc_reg_set(priv, R_LAFH, 0);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * arc_मुक्त_tx_queue - मुक्त skb from tx queue
 * @ndev:	Poपूर्णांकer to the network device.
 *
 * This function must be called जबतक EMAC disable
 */
अटल व्योम arc_मुक्त_tx_queue(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < TX_BD_NUM; i++) अणु
		काष्ठा arc_emac_bd *txbd = &priv->txbd[i];
		काष्ठा buffer_state *tx_buff = &priv->tx_buff[i];

		अगर (tx_buff->skb) अणु
			dma_unmap_single(&ndev->dev,
					 dma_unmap_addr(tx_buff, addr),
					 dma_unmap_len(tx_buff, len),
					 DMA_TO_DEVICE);

			/* वापस the sk_buff to प्रणाली */
			dev_kमुक्त_skb_irq(tx_buff->skb);
		पूर्ण

		txbd->info = 0;
		txbd->data = 0;
		tx_buff->skb = शून्य;
	पूर्ण
पूर्ण

/**
 * arc_मुक्त_rx_queue - मुक्त skb from rx queue
 * @ndev:	Poपूर्णांकer to the network device.
 *
 * This function must be called जबतक EMAC disable
 */
अटल व्योम arc_मुक्त_rx_queue(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < RX_BD_NUM; i++) अणु
		काष्ठा arc_emac_bd *rxbd = &priv->rxbd[i];
		काष्ठा buffer_state *rx_buff = &priv->rx_buff[i];

		अगर (rx_buff->skb) अणु
			dma_unmap_single(&ndev->dev,
					 dma_unmap_addr(rx_buff, addr),
					 dma_unmap_len(rx_buff, len),
					 DMA_FROM_DEVICE);

			/* वापस the sk_buff to प्रणाली */
			dev_kमुक्त_skb_irq(rx_buff->skb);
		पूर्ण

		rxbd->info = 0;
		rxbd->data = 0;
		rx_buff->skb = शून्य;
	पूर्ण
पूर्ण

/**
 * arc_emac_stop - Close the network device.
 * @ndev:	Poपूर्णांकer to the network device.
 *
 * This function stops the Tx queue, disables पूर्णांकerrupts and मुक्तs the IRQ क्रम
 * the EMAC device.
 * It also disconnects the PHY device associated with the EMAC device.
 */
अटल पूर्णांक arc_emac_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);

	napi_disable(&priv->napi);
	netअगर_stop_queue(ndev);

	phy_stop(ndev->phydev);

	/* Disable पूर्णांकerrupts */
	arc_reg_clr(priv, R_ENABLE, RXINT_MASK | TXINT_MASK | ERR_MASK);

	/* Disable EMAC */
	arc_reg_clr(priv, R_CTRL, EN_MASK);

	/* Return the sk_buff to प्रणाली */
	arc_मुक्त_tx_queue(ndev);
	arc_मुक्त_rx_queue(ndev);

	वापस 0;
पूर्ण

/**
 * arc_emac_stats - Get प्रणाली network statistics.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure.
 *
 * Returns the address of the device statistics काष्ठाure.
 * Statistics are updated in पूर्णांकerrupt handler.
 */
अटल काष्ठा net_device_stats *arc_emac_stats(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	अचिन्हित दीर्घ miss, rxerr;
	u8 rxcrc, rxfram, rxoflow;

	rxerr = arc_reg_get(priv, R_RXERR);
	miss = arc_reg_get(priv, R_MISS);

	rxcrc = rxerr;
	rxfram = rxerr >> 8;
	rxoflow = rxerr >> 16;

	stats->rx_errors += miss;
	stats->rx_errors += rxcrc + rxfram + rxoflow;

	stats->rx_over_errors += rxoflow;
	stats->rx_frame_errors += rxfram;
	stats->rx_crc_errors += rxcrc;
	stats->rx_missed_errors += miss;

	वापस stats;
पूर्ण

/**
 * arc_emac_tx - Starts the data transmission.
 * @skb:	sk_buff poपूर्णांकer that contains data to be Transmitted.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure.
 *
 * वापसs: NETDEV_TX_OK, on success
 *		NETDEV_TX_BUSY, अगर any of the descriptors are not मुक्त.
 *
 * This function is invoked from upper layers to initiate transmission.
 */
अटल netdev_tx_t arc_emac_tx(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक len, *txbd_curr = &priv->txbd_curr;
	काष्ठा net_device_stats *stats = &ndev->stats;
	__le32 *info = &priv->txbd[*txbd_curr].info;
	dma_addr_t addr;

	अगर (skb_padto(skb, ETH_ZLEN))
		वापस NETDEV_TX_OK;

	len = max_t(अचिन्हित पूर्णांक, ETH_ZLEN, skb->len);

	अगर (unlikely(!arc_emac_tx_avail(priv))) अणु
		netअगर_stop_queue(ndev);
		netdev_err(ndev, "BUG! Tx Ring full when queue awake!\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	addr = dma_map_single(&ndev->dev, (व्योम *)skb->data, len,
			      DMA_TO_DEVICE);

	अगर (unlikely(dma_mapping_error(&ndev->dev, addr))) अणु
		stats->tx_dropped++;
		stats->tx_errors++;
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	dma_unmap_addr_set(&priv->tx_buff[*txbd_curr], addr, addr);
	dma_unmap_len_set(&priv->tx_buff[*txbd_curr], len, len);

	priv->txbd[*txbd_curr].data = cpu_to_le32(addr);

	/* Make sure poपूर्णांकer to data buffer is set */
	wmb();

	skb_tx_बारtamp(skb);

	*info = cpu_to_le32(FOR_EMAC | FIRST_OR_LAST_MASK | len);

	/* Make sure info word is set */
	wmb();

	priv->tx_buff[*txbd_curr].skb = skb;

	/* Increment index to poपूर्णांक to the next BD */
	*txbd_curr = (*txbd_curr + 1) % TX_BD_NUM;

	/* Ensure that tx_clean() sees the new txbd_curr beक्रमe
	 * checking the queue status. This prevents an unneeded wake
	 * of the queue in tx_clean().
	 */
	smp_mb();

	अगर (!arc_emac_tx_avail(priv)) अणु
		netअगर_stop_queue(ndev);
		/* Refresh tx_dirty */
		smp_mb();
		अगर (arc_emac_tx_avail(priv))
			netअगर_start_queue(ndev);
	पूर्ण

	arc_reg_set(priv, R_STATUS, TXPL_MASK);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम arc_emac_set_address_पूर्णांकernal(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक addr_low, addr_hi;

	addr_low = le32_to_cpu(*(__le32 *)&ndev->dev_addr[0]);
	addr_hi = le16_to_cpu(*(__le16 *)&ndev->dev_addr[4]);

	arc_reg_set(priv, R_ADDRL, addr_low);
	arc_reg_set(priv, R_ADDRH, addr_hi);
पूर्ण

/**
 * arc_emac_set_address - Set the MAC address क्रम this device.
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure.
 * @p:		6 byte Address to be written as MAC address.
 *
 * This function copies the HW address from the sockaddr काष्ठाure to the
 * net_device काष्ठाure and updates the address in HW.
 *
 * वापसs:	-EBUSY अगर the net device is busy or 0 अगर the address is set
 *		successfully.
 */
अटल पूर्णांक arc_emac_set_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;

	अगर (netअगर_running(ndev))
		वापस -EBUSY;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(ndev->dev_addr, addr->sa_data, ndev->addr_len);

	arc_emac_set_address_पूर्णांकernal(ndev);

	वापस 0;
पूर्ण

/**
 * arc_emac_restart - Restart EMAC
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure.
 *
 * This function करो hardware reset of EMAC in order to restore
 * network packets reception.
 */
अटल व्योम arc_emac_restart(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	पूर्णांक i;

	अगर (net_ratelimit())
		netdev_warn(ndev, "restarting stalled EMAC\n");

	netअगर_stop_queue(ndev);

	/* Disable पूर्णांकerrupts */
	arc_reg_clr(priv, R_ENABLE, RXINT_MASK | TXINT_MASK | ERR_MASK);

	/* Disable EMAC */
	arc_reg_clr(priv, R_CTRL, EN_MASK);

	/* Return the sk_buff to प्रणाली */
	arc_मुक्त_tx_queue(ndev);

	/* Clean Tx BD's */
	priv->txbd_curr = 0;
	priv->txbd_dirty = 0;
	स_रखो(priv->txbd, 0, TX_RING_SZ);

	क्रम (i = 0; i < RX_BD_NUM; i++) अणु
		काष्ठा arc_emac_bd *rxbd = &priv->rxbd[i];
		अचिन्हित पूर्णांक info = le32_to_cpu(rxbd->info);

		अगर (!(info & FOR_EMAC)) अणु
			stats->rx_errors++;
			stats->rx_dropped++;
		पूर्ण
		/* Return ownership to EMAC */
		rxbd->info = cpu_to_le32(FOR_EMAC | EMAC_BUFFER_SIZE);
	पूर्ण
	priv->last_rx_bd = 0;

	/* Make sure info is visible to EMAC beक्रमe enable */
	wmb();

	/* Enable पूर्णांकerrupts */
	arc_reg_set(priv, R_ENABLE, RXINT_MASK | TXINT_MASK | ERR_MASK);

	/* Enable EMAC */
	arc_reg_or(priv, R_CTRL, EN_MASK);

	netअगर_start_queue(ndev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops arc_emac_netdev_ops = अणु
	.nकरो_खोलो		= arc_emac_खोलो,
	.nकरो_stop		= arc_emac_stop,
	.nकरो_start_xmit		= arc_emac_tx,
	.nकरो_set_mac_address	= arc_emac_set_address,
	.nकरो_get_stats		= arc_emac_stats,
	.nकरो_set_rx_mode	= arc_emac_set_rx_mode,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= arc_emac_poll_controller,
#पूर्ण_अगर
पूर्ण;

पूर्णांक arc_emac_probe(काष्ठा net_device *ndev, पूर्णांक पूर्णांकerface)
अणु
	काष्ठा device *dev = ndev->dev.parent;
	काष्ठा resource res_regs;
	काष्ठा device_node *phy_node;
	काष्ठा phy_device *phydev = शून्य;
	काष्ठा arc_emac_priv *priv;
	अचिन्हित पूर्णांक id, घड़ी_frequency, irq;
	पूर्णांक err;

	/* Get PHY from device tree */
	phy_node = of_parse_phandle(dev->of_node, "phy", 0);
	अगर (!phy_node) अणु
		dev_err(dev, "failed to retrieve phy description from device tree\n");
		वापस -ENODEV;
	पूर्ण

	/* Get EMAC रेजिस्टरs base address from device tree */
	err = of_address_to_resource(dev->of_node, 0, &res_regs);
	अगर (err) अणु
		dev_err(dev, "failed to retrieve registers base from device tree\n");
		err = -ENODEV;
		जाओ out_put_node;
	पूर्ण

	/* Get IRQ from device tree */
	irq = irq_of_parse_and_map(dev->of_node, 0);
	अगर (!irq) अणु
		dev_err(dev, "failed to retrieve <irq> value from device tree\n");
		err = -ENODEV;
		जाओ out_put_node;
	पूर्ण

	ndev->netdev_ops = &arc_emac_netdev_ops;
	ndev->ethtool_ops = &arc_emac_ethtool_ops;
	ndev->watchकरोg_समयo = TX_TIMEOUT;

	priv = netdev_priv(ndev);
	priv->dev = dev;

	priv->regs = devm_ioremap_resource(dev, &res_regs);
	अगर (IS_ERR(priv->regs)) अणु
		err = PTR_ERR(priv->regs);
		जाओ out_put_node;
	पूर्ण

	dev_dbg(dev, "Registers base address is 0x%p\n", priv->regs);

	अगर (priv->clk) अणु
		err = clk_prepare_enable(priv->clk);
		अगर (err) अणु
			dev_err(dev, "failed to enable clock\n");
			जाओ out_put_node;
		पूर्ण

		घड़ी_frequency = clk_get_rate(priv->clk);
	पूर्ण अन्यथा अणु
		/* Get CPU घड़ी frequency from device tree */
		अगर (of_property_पढ़ो_u32(dev->of_node, "clock-frequency",
					 &घड़ी_frequency)) अणु
			dev_err(dev, "failed to retrieve <clock-frequency> from device tree\n");
			err = -EINVAL;
			जाओ out_put_node;
		पूर्ण
	पूर्ण

	id = arc_reg_get(priv, R_ID);

	/* Check क्रम EMAC revision 5 or 7, magic number */
	अगर (!(id == 0x0005fd02 || id == 0x0007fd02)) अणु
		dev_err(dev, "ARC EMAC not detected, id=0x%x\n", id);
		err = -ENODEV;
		जाओ out_clken;
	पूर्ण
	dev_info(dev, "ARC EMAC detected with id: 0x%x\n", id);

	/* Set poll rate so that it polls every 1 ms */
	arc_reg_set(priv, R_POLLRATE, घड़ी_frequency / 1000000);

	ndev->irq = irq;
	dev_info(dev, "IRQ is %d\n", ndev->irq);

	/* Register पूर्णांकerrupt handler क्रम device */
	err = devm_request_irq(dev, ndev->irq, arc_emac_पूर्णांकr, 0,
			       ndev->name, ndev);
	अगर (err) अणु
		dev_err(dev, "could not allocate IRQ\n");
		जाओ out_clken;
	पूर्ण

	/* Get MAC address from device tree */
	err = of_get_mac_address(dev->of_node, ndev->dev_addr);
	अगर (err)
		eth_hw_addr_अक्रमom(ndev);

	arc_emac_set_address_पूर्णांकernal(ndev);
	dev_info(dev, "MAC address is now %pM\n", ndev->dev_addr);

	/* Do 1 allocation instead of 2 separate ones क्रम Rx and Tx BD rings */
	priv->rxbd = dmam_alloc_coherent(dev, RX_RING_SZ + TX_RING_SZ,
					 &priv->rxbd_dma, GFP_KERNEL);

	अगर (!priv->rxbd) अणु
		dev_err(dev, "failed to allocate data buffers\n");
		err = -ENOMEM;
		जाओ out_clken;
	पूर्ण

	priv->txbd = priv->rxbd + RX_BD_NUM;

	priv->txbd_dma = priv->rxbd_dma + RX_RING_SZ;
	dev_dbg(dev, "EMAC Device addr: Rx Ring [0x%x], Tx Ring[%x]\n",
		(अचिन्हित पूर्णांक)priv->rxbd_dma, (अचिन्हित पूर्णांक)priv->txbd_dma);

	err = arc_mdio_probe(priv);
	अगर (err) अणु
		dev_err(dev, "failed to probe MII bus\n");
		जाओ out_clken;
	पूर्ण

	phydev = of_phy_connect(ndev, phy_node, arc_emac_adjust_link, 0,
				पूर्णांकerface);
	अगर (!phydev) अणु
		dev_err(dev, "of_phy_connect() failed\n");
		err = -ENODEV;
		जाओ out_mdio;
	पूर्ण

	dev_info(dev, "connected to %s phy with id 0x%x\n",
		 phydev->drv->name, phydev->phy_id);

	netअगर_napi_add(ndev, &priv->napi, arc_emac_poll, ARC_EMAC_NAPI_WEIGHT);

	err = रेजिस्टर_netdev(ndev);
	अगर (err) अणु
		dev_err(dev, "failed to register network device\n");
		जाओ out_netअगर_api;
	पूर्ण

	of_node_put(phy_node);
	वापस 0;

out_netअगर_api:
	netअगर_napi_del(&priv->napi);
	phy_disconnect(phydev);
out_mdio:
	arc_mdio_हटाओ(priv);
out_clken:
	अगर (priv->clk)
		clk_disable_unprepare(priv->clk);
out_put_node:
	of_node_put(phy_node);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(arc_emac_probe);

पूर्णांक arc_emac_हटाओ(काष्ठा net_device *ndev)
अणु
	काष्ठा arc_emac_priv *priv = netdev_priv(ndev);

	phy_disconnect(ndev->phydev);
	arc_mdio_हटाओ(priv);
	unरेजिस्टर_netdev(ndev);
	netअगर_napi_del(&priv->napi);

	अगर (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(arc_emac_हटाओ);

MODULE_AUTHOR("Alexey Brodkin <abrodkin@synopsys.com>");
MODULE_DESCRIPTION("ARC EMAC driver");
MODULE_LICENSE("GPL");
