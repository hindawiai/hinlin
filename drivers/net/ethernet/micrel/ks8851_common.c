<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/net/ethernet/micrel/ks8851.c
 *
 * Copyright 2009 Simtec Electronics
 *	http://www.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/cache.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mii.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>

#समावेश "ks8851.h"

/**
 * ks8851_lock - रेजिस्टर access lock
 * @ks: The chip state
 * @flags: Spinlock flags
 *
 * Claim chip रेजिस्टर access lock
 */
अटल व्योम ks8851_lock(काष्ठा ks8851_net *ks, अचिन्हित दीर्घ *flags)
अणु
	ks->lock(ks, flags);
पूर्ण

/**
 * ks8851_unlock - रेजिस्टर access unlock
 * @ks: The chip state
 * @flags: Spinlock flags
 *
 * Release chip रेजिस्टर access lock
 */
अटल व्योम ks8851_unlock(काष्ठा ks8851_net *ks, अचिन्हित दीर्घ *flags)
अणु
	ks->unlock(ks, flags);
पूर्ण

/**
 * ks8851_wrreg16 - ग_लिखो 16bit रेजिस्टर value to chip
 * @ks: The chip state
 * @reg: The रेजिस्टर address
 * @val: The value to ग_लिखो
 *
 * Issue a ग_लिखो to put the value @val पूर्णांकo the रेजिस्टर specअगरied in @reg.
 */
अटल व्योम ks8851_wrreg16(काष्ठा ks8851_net *ks, अचिन्हित पूर्णांक reg,
			   अचिन्हित पूर्णांक val)
अणु
	ks->wrreg16(ks, reg, val);
पूर्ण

/**
 * ks8851_rdreg16 - पढ़ो 16 bit रेजिस्टर from device
 * @ks: The chip inक्रमmation
 * @reg: The रेजिस्टर address
 *
 * Read a 16bit रेजिस्टर from the chip, वापसing the result
 */
अटल अचिन्हित पूर्णांक ks8851_rdreg16(काष्ठा ks8851_net *ks,
				   अचिन्हित पूर्णांक reg)
अणु
	वापस ks->rdreg16(ks, reg);
पूर्ण

/**
 * ks8851_soft_reset - issue one of the soft reset to the device
 * @ks: The device state.
 * @op: The bit(s) to set in the GRR
 *
 * Issue the relevant soft-reset command to the device's GRR रेजिस्टर
 * specअगरied by @op.
 *
 * Note, the delays are in there as a caution to ensure that the reset
 * has समय to take effect and then complete. Since the datasheet करोes
 * not currently specअगरy the exact sequence, we have chosen something
 * that seems to work with our device.
 */
अटल व्योम ks8851_soft_reset(काष्ठा ks8851_net *ks, अचिन्हित op)
अणु
	ks8851_wrreg16(ks, KS_GRR, op);
	mdelay(1);	/* रुको a लघु समय to effect reset */
	ks8851_wrreg16(ks, KS_GRR, 0);
	mdelay(1);	/* रुको क्रम condition to clear */
पूर्ण

/**
 * ks8851_set_घातermode - set घातer mode of the device
 * @ks: The device state
 * @pwrmode: The घातer mode value to ग_लिखो to KS_PMECR.
 *
 * Change the घातer mode of the chip.
 */
अटल व्योम ks8851_set_घातermode(काष्ठा ks8851_net *ks, अचिन्हित pwrmode)
अणु
	अचिन्हित pmecr;

	netअगर_dbg(ks, hw, ks->netdev, "setting power mode %d\n", pwrmode);

	pmecr = ks8851_rdreg16(ks, KS_PMECR);
	pmecr &= ~PMECR_PM_MASK;
	pmecr |= pwrmode;

	ks8851_wrreg16(ks, KS_PMECR, pmecr);
पूर्ण

/**
 * ks8851_ग_लिखो_mac_addr - ग_लिखो mac address to device रेजिस्टरs
 * @dev: The network device
 *
 * Update the KS8851 MAC address रेजिस्टरs from the address in @dev.
 *
 * This call assumes that the chip is not running, so there is no need to
 * shutकरोwn the RXQ process whilst setting this.
*/
अटल पूर्णांक ks8851_ग_लिखो_mac_addr(काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	u16 val;
	पूर्णांक i;

	ks8851_lock(ks, &flags);

	/*
	 * Wake up chip in हाल it was घातered off when stopped; otherwise,
	 * the first ग_लिखो to the MAC address करोes not take effect.
	 */
	ks8851_set_घातermode(ks, PMECR_PM_NORMAL);

	क्रम (i = 0; i < ETH_ALEN; i += 2) अणु
		val = (dev->dev_addr[i] << 8) | dev->dev_addr[i + 1];
		ks8851_wrreg16(ks, KS_MAR(i), val);
	पूर्ण

	अगर (!netअगर_running(dev))
		ks8851_set_घातermode(ks, PMECR_PM_SOFTDOWN);

	ks8851_unlock(ks, &flags);

	वापस 0;
पूर्ण

/**
 * ks8851_पढ़ो_mac_addr - पढ़ो mac address from device रेजिस्टरs
 * @dev: The network device
 *
 * Update our copy of the KS8851 MAC address from the रेजिस्टरs of @dev.
*/
अटल व्योम ks8851_पढ़ो_mac_addr(काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	u16 reg;
	पूर्णांक i;

	ks8851_lock(ks, &flags);

	क्रम (i = 0; i < ETH_ALEN; i += 2) अणु
		reg = ks8851_rdreg16(ks, KS_MAR(i));
		dev->dev_addr[i] = reg >> 8;
		dev->dev_addr[i + 1] = reg & 0xff;
	पूर्ण

	ks8851_unlock(ks, &flags);
पूर्ण

/**
 * ks8851_init_mac - initialise the mac address
 * @ks: The device काष्ठाure
 * @np: The device node poपूर्णांकer
 *
 * Get or create the initial mac address क्रम the device and then set that
 * पूर्णांकo the station address रेजिस्टर. A mac address supplied in the device
 * tree takes precedence. Otherwise, अगर there is an EEPROM present, then
 * we try that. If no valid mac address is found we use eth_अक्रमom_addr()
 * to create a new one.
 */
अटल व्योम ks8851_init_mac(काष्ठा ks8851_net *ks, काष्ठा device_node *np)
अणु
	काष्ठा net_device *dev = ks->netdev;
	पूर्णांक ret;

	ret = of_get_mac_address(np, dev->dev_addr);
	अगर (!ret) अणु
		ks8851_ग_लिखो_mac_addr(dev);
		वापस;
	पूर्ण

	अगर (ks->rc_ccr & CCR_EEPROM) अणु
		ks8851_पढ़ो_mac_addr(dev);
		अगर (is_valid_ether_addr(dev->dev_addr))
			वापस;

		netdev_err(ks->netdev, "invalid mac address read %pM\n",
				dev->dev_addr);
	पूर्ण

	eth_hw_addr_अक्रमom(dev);
	ks8851_ग_लिखो_mac_addr(dev);
पूर्ण

/**
 * ks8851_dbg_dumpkkt - dump initial packet contents to debug
 * @ks: The device state
 * @rxpkt: The data क्रम the received packet
 *
 * Dump the initial data from the packet to dev_dbg().
 */
अटल व्योम ks8851_dbg_dumpkkt(काष्ठा ks8851_net *ks, u8 *rxpkt)
अणु
	netdev_dbg(ks->netdev,
		   "pkt %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x\n",
		   rxpkt[4], rxpkt[5], rxpkt[6], rxpkt[7],
		   rxpkt[8], rxpkt[9], rxpkt[10], rxpkt[11],
		   rxpkt[12], rxpkt[13], rxpkt[14], rxpkt[15]);
पूर्ण

/**
 * ks8851_rx_skb - receive skbuff
 * @ks: The device state.
 * @skb: The skbuff
 */
अटल व्योम ks8851_rx_skb(काष्ठा ks8851_net *ks, काष्ठा sk_buff *skb)
अणु
	ks->rx_skb(ks, skb);
पूर्ण

/**
 * ks8851_rx_pkts - receive packets from the host
 * @ks: The device inक्रमmation.
 *
 * This is called from the IRQ work queue when the प्रणाली detects that there
 * are packets in the receive queue. Find out how many packets there are and
 * पढ़ो them from the FIFO.
 */
अटल व्योम ks8851_rx_pkts(काष्ठा ks8851_net *ks)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित rxfc;
	अचिन्हित rxlen;
	अचिन्हित rxstat;
	u8 *rxpkt;

	rxfc = (ks8851_rdreg16(ks, KS_RXFCTR) >> 8) & 0xff;

	netअगर_dbg(ks, rx_status, ks->netdev,
		  "%s: %d packets\n", __func__, rxfc);

	/* Currently we're issuing a पढ़ो per packet, but we could possibly
	 * improve the code by issuing a single पढ़ो, getting the receive
	 * header, allocating the packet and then पढ़ोing the packet data
	 * out in one go.
	 *
	 * This क्रमm of operation would require us to hold the SPI bus'
	 * chipselect low during the entie transaction to aव्योम any
	 * reset to the data stream coming from the chip.
	 */

	क्रम (; rxfc != 0; rxfc--) अणु
		rxstat = ks8851_rdreg16(ks, KS_RXFHSR);
		rxlen = ks8851_rdreg16(ks, KS_RXFHBCR) & RXFHBCR_CNT_MASK;

		netअगर_dbg(ks, rx_status, ks->netdev,
			  "rx: stat 0x%04x, len 0x%04x\n", rxstat, rxlen);

		/* the length of the packet includes the 32bit CRC */

		/* set dma पढ़ो address */
		ks8851_wrreg16(ks, KS_RXFDPR, RXFDPR_RXFPAI | 0x00);

		/* start DMA access */
		ks8851_wrreg16(ks, KS_RXQCR, ks->rc_rxqcr | RXQCR_SDA);

		अगर (rxlen > 4) अणु
			अचिन्हित पूर्णांक rxalign;

			rxlen -= 4;
			rxalign = ALIGN(rxlen, 4);
			skb = netdev_alloc_skb_ip_align(ks->netdev, rxalign);
			अगर (skb) अणु

				/* 4 bytes of status header + 4 bytes of
				 * garbage: we put them beक्रमe ethernet
				 * header, so that they are copied,
				 * but ignored.
				 */

				rxpkt = skb_put(skb, rxlen) - 8;

				ks->rdfअगरo(ks, rxpkt, rxalign + 8);

				अगर (netअगर_msg_pktdata(ks))
					ks8851_dbg_dumpkkt(ks, rxpkt);

				skb->protocol = eth_type_trans(skb, ks->netdev);
				ks8851_rx_skb(ks, skb);

				ks->netdev->stats.rx_packets++;
				ks->netdev->stats.rx_bytes += rxlen;
			पूर्ण
		पूर्ण

		/* end DMA access and dequeue packet */
		ks8851_wrreg16(ks, KS_RXQCR, ks->rc_rxqcr | RXQCR_RRXEF);
	पूर्ण
पूर्ण

/**
 * ks8851_irq - IRQ handler क्रम dealing with पूर्णांकerrupt requests
 * @irq: IRQ number
 * @_ks: cookie
 *
 * This handler is invoked when the IRQ line निश्चितs to find out what happened.
 * As we cannot allow ourselves to sleep in HARसूचीQ context, this handler runs
 * in thपढ़ो context.
 *
 * Read the पूर्णांकerrupt status, work out what needs to be करोne and then clear
 * any of the पूर्णांकerrupts that are not needed.
 */
अटल irqवापस_t ks8851_irq(पूर्णांक irq, व्योम *_ks)
अणु
	काष्ठा ks8851_net *ks = _ks;
	अचिन्हित handled = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;

	ks8851_lock(ks, &flags);

	status = ks8851_rdreg16(ks, KS_ISR);

	netअगर_dbg(ks, पूर्णांकr, ks->netdev,
		  "%s: status 0x%04x\n", __func__, status);

	अगर (status & IRQ_LCI)
		handled |= IRQ_LCI;

	अगर (status & IRQ_LDI) अणु
		u16 pmecr = ks8851_rdreg16(ks, KS_PMECR);
		pmecr &= ~PMECR_WKEVT_MASK;
		ks8851_wrreg16(ks, KS_PMECR, pmecr | PMECR_WKEVT_LINK);

		handled |= IRQ_LDI;
	पूर्ण

	अगर (status & IRQ_RXPSI)
		handled |= IRQ_RXPSI;

	अगर (status & IRQ_TXI) अणु
		handled |= IRQ_TXI;

		/* no lock here, tx queue should have been stopped */

		/* update our idea of how much tx space is available to the
		 * प्रणाली */
		ks->tx_space = ks8851_rdreg16(ks, KS_TXMIR);

		netअगर_dbg(ks, पूर्णांकr, ks->netdev,
			  "%s: txspace %d\n", __func__, ks->tx_space);
	पूर्ण

	अगर (status & IRQ_RXI)
		handled |= IRQ_RXI;

	अगर (status & IRQ_SPIBEI) अणु
		netdev_err(ks->netdev, "%s: spi bus error\n", __func__);
		handled |= IRQ_SPIBEI;
	पूर्ण

	ks8851_wrreg16(ks, KS_ISR, handled);

	अगर (status & IRQ_RXI) अणु
		/* the datasheet says to disable the rx पूर्णांकerrupt during
		 * packet पढ़ो-out, however we're masking the पूर्णांकerrupt
		 * from the device so करो not bother masking just the RX
		 * from the device. */

		ks8851_rx_pkts(ks);
	पूर्ण

	/* अगर something stopped the rx process, probably due to wanting
	 * to change the rx settings, then करो something about restarting
	 * it. */
	अगर (status & IRQ_RXPSI) अणु
		काष्ठा ks8851_rxctrl *rxc = &ks->rxctrl;

		/* update the multicast hash table */
		ks8851_wrreg16(ks, KS_MAHTR0, rxc->mchash[0]);
		ks8851_wrreg16(ks, KS_MAHTR1, rxc->mchash[1]);
		ks8851_wrreg16(ks, KS_MAHTR2, rxc->mchash[2]);
		ks8851_wrreg16(ks, KS_MAHTR3, rxc->mchash[3]);

		ks8851_wrreg16(ks, KS_RXCR2, rxc->rxcr2);
		ks8851_wrreg16(ks, KS_RXCR1, rxc->rxcr1);
	पूर्ण

	ks8851_unlock(ks, &flags);

	अगर (status & IRQ_LCI)
		mii_check_link(&ks->mii);

	अगर (status & IRQ_TXI)
		netअगर_wake_queue(ks->netdev);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ks8851_flush_tx_work - flush outstanding TX work
 * @ks: The device state
 */
अटल व्योम ks8851_flush_tx_work(काष्ठा ks8851_net *ks)
अणु
	अगर (ks->flush_tx_work)
		ks->flush_tx_work(ks);
पूर्ण

/**
 * ks8851_net_खोलो - खोलो network device
 * @dev: The network device being खोलोed.
 *
 * Called when the network device is marked active, such as a user executing
 * 'ifconfig up' on the device.
 */
अटल पूर्णांक ks8851_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = request_thपढ़ोed_irq(dev->irq, शून्य, ks8851_irq,
				   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				   dev->name, ks);
	अगर (ret < 0) अणु
		netdev_err(dev, "failed to get irq\n");
		वापस ret;
	पूर्ण

	/* lock the card, even अगर we may not actually be करोing anything
	 * अन्यथा at the moment */
	ks8851_lock(ks, &flags);

	netअगर_dbg(ks, अगरup, ks->netdev, "opening\n");

	/* bring chip out of any घातer saving mode it was in */
	ks8851_set_घातermode(ks, PMECR_PM_NORMAL);

	/* issue a soft reset to the RX/TX QMU to put it पूर्णांकo a known
	 * state. */
	ks8851_soft_reset(ks, GRR_QMU);

	/* setup transmission parameters */

	ks8851_wrreg16(ks, KS_TXCR, (TXCR_TXE | /* enable transmit process */
				     TXCR_TXPE | /* pad to min length */
				     TXCR_TXCRC | /* add CRC */
				     TXCR_TXFCE)); /* enable flow control */

	/* स्वतः-increment tx data, reset tx poपूर्णांकer */
	ks8851_wrreg16(ks, KS_TXFDPR, TXFDPR_TXFPAI);

	/* setup receiver control */

	ks8851_wrreg16(ks, KS_RXCR1, (RXCR1_RXPAFMA | /*  from mac filter */
				      RXCR1_RXFCE | /* enable flow control */
				      RXCR1_RXBE | /* broadcast enable */
				      RXCR1_RXUE | /* unicast enable */
				      RXCR1_RXE)); /* enable rx block */

	/* transfer entire frames out in one go */
	ks8851_wrreg16(ks, KS_RXCR2, RXCR2_SRDBL_FRAME);

	/* set receive counter समयouts */
	ks8851_wrreg16(ks, KS_RXDTTR, 1000); /* 1ms after first frame to IRQ */
	ks8851_wrreg16(ks, KS_RXDBCTR, 4096); /* >4Kbytes in buffer to IRQ */
	ks8851_wrreg16(ks, KS_RXFCTR, 10);  /* 10 frames to IRQ */

	ks->rc_rxqcr = (RXQCR_RXFCTE |  /* IRQ on frame count exceeded */
			RXQCR_RXDBCTE | /* IRQ on byte count exceeded */
			RXQCR_RXDTTE);  /* IRQ on समय exceeded */

	ks8851_wrreg16(ks, KS_RXQCR, ks->rc_rxqcr);

	/* clear then enable पूर्णांकerrupts */
	ks8851_wrreg16(ks, KS_ISR, ks->rc_ier);
	ks8851_wrreg16(ks, KS_IER, ks->rc_ier);

	netअगर_start_queue(ks->netdev);

	netअगर_dbg(ks, अगरup, ks->netdev, "network device up\n");

	ks8851_unlock(ks, &flags);
	mii_check_link(&ks->mii);
	वापस 0;
पूर्ण

/**
 * ks8851_net_stop - बंद network device
 * @dev: The device being बंदd.
 *
 * Called to बंद करोwn a network device which has been active. Cancell any
 * work, shutकरोwn the RX and TX process and then place the chip पूर्णांकo a low
 * घातer state whilst it is not being used.
 */
अटल पूर्णांक ks8851_net_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	netअगर_info(ks, अगरकरोwn, dev, "shutting down\n");

	netअगर_stop_queue(dev);

	ks8851_lock(ks, &flags);
	/* turn off the IRQs and ack any outstanding */
	ks8851_wrreg16(ks, KS_IER, 0x0000);
	ks8851_wrreg16(ks, KS_ISR, 0xffff);
	ks8851_unlock(ks, &flags);

	/* stop any outstanding work */
	ks8851_flush_tx_work(ks);
	flush_work(&ks->rxctrl_work);

	ks8851_lock(ks, &flags);
	/* shutकरोwn RX process */
	ks8851_wrreg16(ks, KS_RXCR1, 0x0000);

	/* shutकरोwn TX process */
	ks8851_wrreg16(ks, KS_TXCR, 0x0000);

	/* set घातermode to soft घातer करोwn to save घातer */
	ks8851_set_घातermode(ks, PMECR_PM_SOFTDOWN);
	ks8851_unlock(ks, &flags);

	/* ensure any queued tx buffers are dumped */
	जबतक (!skb_queue_empty(&ks->txq)) अणु
		काष्ठा sk_buff *txb = skb_dequeue(&ks->txq);

		netअगर_dbg(ks, अगरकरोwn, ks->netdev,
			  "%s: freeing txb %p\n", __func__, txb);

		dev_kमुक्त_skb(txb);
	पूर्ण

	मुक्त_irq(dev->irq, ks);

	वापस 0;
पूर्ण

/**
 * ks8851_start_xmit - transmit packet
 * @skb: The buffer to transmit
 * @dev: The device used to transmit the packet.
 *
 * Called by the network layer to transmit the @skb. Queue the packet क्रम
 * the device and schedule the necessary work to transmit the packet when
 * it is मुक्त.
 *
 * We करो this to firstly aव्योम sleeping with the network device locked,
 * and secondly so we can round up more than one packet to transmit which
 * means we can try and aव्योम generating too many transmit करोne पूर्णांकerrupts.
 */
अटल netdev_tx_t ks8851_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);

	वापस ks->start_xmit(skb, dev);
पूर्ण

/**
 * ks8851_rxctrl_work - work handler to change rx mode
 * @work: The work काष्ठाure this beदीर्घs to.
 *
 * Lock the device and issue the necessary changes to the receive mode from
 * the network device layer. This is करोne so that we can करो this without
 * having to sleep whilst holding the network device lock.
 *
 * Since the recommendation from Micrel is that the RXQ is shutकरोwn whilst the
 * receive parameters are programmed, we issue a ग_लिखो to disable the RXQ and
 * then रुको क्रम the पूर्णांकerrupt handler to be triggered once the RXQ shutकरोwn is
 * complete. The पूर्णांकerrupt handler then ग_लिखोs the new values पूर्णांकo the chip.
 */
अटल व्योम ks8851_rxctrl_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ks8851_net *ks = container_of(work, काष्ठा ks8851_net, rxctrl_work);
	अचिन्हित दीर्घ flags;

	ks8851_lock(ks, &flags);

	/* need to shutकरोwn RXQ beक्रमe modअगरying filter parameters */
	ks8851_wrreg16(ks, KS_RXCR1, 0x00);

	ks8851_unlock(ks, &flags);
पूर्ण

अटल व्योम ks8851_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	काष्ठा ks8851_rxctrl rxctrl;

	स_रखो(&rxctrl, 0, माप(rxctrl));

	अगर (dev->flags & IFF_PROMISC) अणु
		/* पूर्णांकerface to receive everything */

		rxctrl.rxcr1 = RXCR1_RXAE | RXCR1_RXINVF;
	पूर्ण अन्यथा अगर (dev->flags & IFF_ALLMULTI) अणु
		/* accept all multicast packets */

		rxctrl.rxcr1 = (RXCR1_RXME | RXCR1_RXAE |
				RXCR1_RXPAFMA | RXCR1_RXMAFMA);
	पूर्ण अन्यथा अगर (dev->flags & IFF_MULTICAST && !netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;
		u32 crc;

		/* accept some multicast */

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			crc = ether_crc(ETH_ALEN, ha->addr);
			crc >>= (32 - 6);  /* get top six bits */

			rxctrl.mchash[crc >> 4] |= (1 << (crc & 0xf));
		पूर्ण

		rxctrl.rxcr1 = RXCR1_RXME | RXCR1_RXPAFMA;
	पूर्ण अन्यथा अणु
		/* just accept broadcast / unicast */
		rxctrl.rxcr1 = RXCR1_RXPAFMA;
	पूर्ण

	rxctrl.rxcr1 |= (RXCR1_RXUE | /* unicast enable */
			 RXCR1_RXBE | /* broadcast enable */
			 RXCR1_RXE | /* RX process enable */
			 RXCR1_RXFCE); /* enable flow control */

	rxctrl.rxcr2 |= RXCR2_SRDBL_FRAME;

	/* schedule work to करो the actual set of the data अगर needed */

	spin_lock(&ks->statelock);

	अगर (स_भेद(&rxctrl, &ks->rxctrl, माप(rxctrl)) != 0) अणु
		स_नकल(&ks->rxctrl, &rxctrl, माप(ks->rxctrl));
		schedule_work(&ks->rxctrl_work);
	पूर्ण

	spin_unlock(&ks->statelock);
पूर्ण

अटल पूर्णांक ks8851_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = addr;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	अगर (!is_valid_ether_addr(sa->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, sa->sa_data, ETH_ALEN);
	वापस ks8851_ग_लिखो_mac_addr(dev);
पूर्ण

अटल पूर्णांक ks8851_net_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	वापस generic_mii_ioctl(&ks->mii, अगर_mii(req), cmd, शून्य);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ks8851_netdev_ops = अणु
	.nकरो_खोलो		= ks8851_net_खोलो,
	.nकरो_stop		= ks8851_net_stop,
	.nकरो_करो_ioctl		= ks8851_net_ioctl,
	.nकरो_start_xmit		= ks8851_start_xmit,
	.nकरो_set_mac_address	= ks8851_set_mac_address,
	.nकरो_set_rx_mode	= ks8851_set_rx_mode,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

/* ethtool support */

अटल व्योम ks8851_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *di)
अणु
	strlcpy(di->driver, "KS8851", माप(di->driver));
	strlcpy(di->version, "1.00", माप(di->version));
	strlcpy(di->bus_info, dev_name(dev->dev.parent), माप(di->bus_info));
पूर्ण

अटल u32 ks8851_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	वापस ks->msg_enable;
पूर्ण

अटल व्योम ks8851_set_msglevel(काष्ठा net_device *dev, u32 to)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	ks->msg_enable = to;
पूर्ण

अटल पूर्णांक ks8851_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);

	mii_ethtool_get_link_ksettings(&ks->mii, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक ks8851_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	वापस mii_ethtool_set_link_ksettings(&ks->mii, cmd);
पूर्ण

अटल u32 ks8851_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	वापस mii_link_ok(&ks->mii);
पूर्ण

अटल पूर्णांक ks8851_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	वापस mii_nway_restart(&ks->mii);
पूर्ण

/* EEPROM support */

अटल व्योम ks8851_eeprom_regपढ़ो(काष्ठा eeprom_93cx6 *ee)
अणु
	काष्ठा ks8851_net *ks = ee->data;
	अचिन्हित val;

	val = ks8851_rdreg16(ks, KS_EEPCR);

	ee->reg_data_out = (val & EEPCR_EESB) ? 1 : 0;
	ee->reg_data_घड़ी = (val & EEPCR_EESCK) ? 1 : 0;
	ee->reg_chip_select = (val & EEPCR_EECS) ? 1 : 0;
पूर्ण

अटल व्योम ks8851_eeprom_regग_लिखो(काष्ठा eeprom_93cx6 *ee)
अणु
	काष्ठा ks8851_net *ks = ee->data;
	अचिन्हित val = EEPCR_EESA;	/* शेष - eeprom access on */

	अगर (ee->drive_data)
		val |= EEPCR_EESRWA;
	अगर (ee->reg_data_in)
		val |= EEPCR_EEDO;
	अगर (ee->reg_data_घड़ी)
		val |= EEPCR_EESCK;
	अगर (ee->reg_chip_select)
		val |= EEPCR_EECS;

	ks8851_wrreg16(ks, KS_EEPCR, val);
पूर्ण

/**
 * ks8851_eeprom_claim - claim device EEPROM and activate the पूर्णांकerface
 * @ks: The network device state.
 *
 * Check क्रम the presence of an EEPROM, and then activate software access
 * to the device.
 */
अटल पूर्णांक ks8851_eeprom_claim(काष्ठा ks8851_net *ks)
अणु
	/* start with घड़ी low, cs high */
	ks8851_wrreg16(ks, KS_EEPCR, EEPCR_EESA | EEPCR_EECS);
	वापस 0;
पूर्ण

/**
 * ks8851_eeprom_release - release the EEPROM पूर्णांकerface
 * @ks: The device state
 *
 * Release the software access to the device EEPROM
 */
अटल व्योम ks8851_eeprom_release(काष्ठा ks8851_net *ks)
अणु
	अचिन्हित val = ks8851_rdreg16(ks, KS_EEPCR);

	ks8851_wrreg16(ks, KS_EEPCR, val & ~EEPCR_EESA);
पूर्ण

#घोषणा KS_EEPROM_MAGIC (0x00008851)

अटल पूर्णांक ks8851_set_eeprom(काष्ठा net_device *dev,
			     काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	पूर्णांक offset = ee->offset;
	अचिन्हित दीर्घ flags;
	पूर्णांक len = ee->len;
	u16 पंचांगp;

	/* currently only support byte writing */
	अगर (len != 1)
		वापस -EINVAL;

	अगर (ee->magic != KS_EEPROM_MAGIC)
		वापस -EINVAL;

	अगर (!(ks->rc_ccr & CCR_EEPROM))
		वापस -ENOENT;

	ks8851_lock(ks, &flags);

	ks8851_eeprom_claim(ks);

	eeprom_93cx6_wren(&ks->eeprom, true);

	/* ethtool currently only supports writing bytes, which means
	 * we have to पढ़ो/modअगरy/ग_लिखो our 16bit EEPROMs */

	eeprom_93cx6_पढ़ो(&ks->eeprom, offset/2, &पंचांगp);

	अगर (offset & 1) अणु
		पंचांगp &= 0xff;
		पंचांगp |= *data << 8;
	पूर्ण अन्यथा अणु
		पंचांगp &= 0xff00;
		पंचांगp |= *data;
	पूर्ण

	eeprom_93cx6_ग_लिखो(&ks->eeprom, offset/2, पंचांगp);
	eeprom_93cx6_wren(&ks->eeprom, false);

	ks8851_eeprom_release(ks);
	ks8851_unlock(ks, &flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ks8851_get_eeprom(काष्ठा net_device *dev,
			     काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	पूर्णांक offset = ee->offset;
	अचिन्हित दीर्घ flags;
	पूर्णांक len = ee->len;

	/* must be 2 byte aligned */
	अगर (len & 1 || offset & 1)
		वापस -EINVAL;

	अगर (!(ks->rc_ccr & CCR_EEPROM))
		वापस -ENOENT;

	ks8851_lock(ks, &flags);

	ks8851_eeprom_claim(ks);

	ee->magic = KS_EEPROM_MAGIC;

	eeprom_93cx6_multiपढ़ो(&ks->eeprom, offset/2, (__le16 *)data, len/2);
	ks8851_eeprom_release(ks);
	ks8851_unlock(ks, &flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ks8851_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);

	/* currently, we assume it is an 93C46 attached, so वापस 128 */
	वापस ks->rc_ccr & CCR_EEPROM ? 128 : 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ks8851_ethtool_ops = अणु
	.get_drvinfo	= ks8851_get_drvinfo,
	.get_msglevel	= ks8851_get_msglevel,
	.set_msglevel	= ks8851_set_msglevel,
	.get_link	= ks8851_get_link,
	.nway_reset	= ks8851_nway_reset,
	.get_eeprom_len	= ks8851_get_eeprom_len,
	.get_eeprom	= ks8851_get_eeprom,
	.set_eeprom	= ks8851_set_eeprom,
	.get_link_ksettings = ks8851_get_link_ksettings,
	.set_link_ksettings = ks8851_set_link_ksettings,
पूर्ण;

/* MII पूर्णांकerface controls */

/**
 * ks8851_phy_reg - convert MII रेजिस्टर पूर्णांकo a KS8851 रेजिस्टर
 * @reg: MII रेजिस्टर number.
 *
 * Return the KS8851 रेजिस्टर number क्रम the corresponding MII PHY रेजिस्टर
 * अगर possible. Return zero अगर the MII रेजिस्टर has no direct mapping to the
 * KS8851 रेजिस्टर set.
 */
अटल पूर्णांक ks8851_phy_reg(पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MII_BMCR:
		वापस KS_P1MBCR;
	हाल MII_BMSR:
		वापस KS_P1MBSR;
	हाल MII_PHYSID1:
		वापस KS_PHY1ILR;
	हाल MII_PHYSID2:
		वापस KS_PHY1IHR;
	हाल MII_ADVERTISE:
		वापस KS_P1ANAR;
	हाल MII_LPA:
		वापस KS_P1ANLPR;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ks8851_phy_पढ़ो_common(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक reg)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक result;
	पूर्णांक ksreg;

	ksreg = ks8851_phy_reg(reg);
	अगर (ksreg < 0)
		वापस ksreg;

	ks8851_lock(ks, &flags);
	result = ks8851_rdreg16(ks, ksreg);
	ks8851_unlock(ks, &flags);

	वापस result;
पूर्ण

/**
 * ks8851_phy_पढ़ो - MII पूर्णांकerface PHY रेजिस्टर पढ़ो.
 * @dev: The network device the PHY is on.
 * @phy_addr: Address of PHY (ignored as we only have one)
 * @reg: The रेजिस्टर to पढ़ो.
 *
 * This call पढ़ोs data from the PHY रेजिस्टर specअगरied in @reg. Since the
 * device करोes not support all the MII रेजिस्टरs, the non-existent values
 * are always वापसed as zero.
 *
 * We वापस zero क्रम unsupported रेजिस्टरs as the MII code करोes not check
 * the value वापसed क्रम any error status, and simply वापसs it to the
 * caller. The mii-tool that the driver was tested with takes any -ve error
 * as real PHY capabilities, thus displaying incorrect data to the user.
 */
अटल पूर्णांक ks8851_phy_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_addr, पूर्णांक reg)
अणु
	पूर्णांक ret;

	ret = ks8851_phy_पढ़ो_common(dev, phy_addr, reg);
	अगर (ret < 0)
		वापस 0x0;	/* no error वापस allowed, so use zero */

	वापस ret;
पूर्ण

अटल व्योम ks8851_phy_ग_लिखो(काष्ठा net_device *dev,
			     पूर्णांक phy, पूर्णांक reg, पूर्णांक value)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ksreg;

	ksreg = ks8851_phy_reg(reg);
	अगर (ksreg >= 0) अणु
		ks8851_lock(ks, &flags);
		ks8851_wrreg16(ks, ksreg, value);
		ks8851_unlock(ks, &flags);
	पूर्ण
पूर्ण

अटल पूर्णांक ks8851_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा ks8851_net *ks = bus->priv;

	अगर (phy_id != 0)
		वापस -EOPNOTSUPP;

	/* KS8851 PHY ID रेजिस्टरs are swapped in HW, swap them back. */
	अगर (reg == MII_PHYSID1)
		reg = MII_PHYSID2;
	अन्यथा अगर (reg == MII_PHYSID2)
		reg = MII_PHYSID1;

	वापस ks8851_phy_पढ़ो_common(ks->netdev, phy_id, reg);
पूर्ण

अटल पूर्णांक ks8851_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg, u16 val)
अणु
	काष्ठा ks8851_net *ks = bus->priv;

	ks8851_phy_ग_लिखो(ks->netdev, phy_id, reg, val);
	वापस 0;
पूर्ण

/**
 * ks8851_पढ़ो_selftest - पढ़ो the selftest memory info.
 * @ks: The device state
 *
 * Read and check the TX/RX memory selftest inक्रमmation.
 */
अटल पूर्णांक ks8851_पढ़ो_selftest(काष्ठा ks8851_net *ks)
अणु
	अचिन्हित both_करोne = MBIR_TXMBF | MBIR_RXMBF;
	पूर्णांक ret = 0;
	अचिन्हित rd;

	rd = ks8851_rdreg16(ks, KS_MBIR);

	अगर ((rd & both_करोne) != both_करोne) अणु
		netdev_warn(ks->netdev, "Memory selftest not finished\n");
		वापस 0;
	पूर्ण

	अगर (rd & MBIR_TXMBFA) अणु
		netdev_err(ks->netdev, "TX memory selftest fail\n");
		ret |= 1;
	पूर्ण

	अगर (rd & MBIR_RXMBFA) अणु
		netdev_err(ks->netdev, "RX memory selftest fail\n");
		ret |= 2;
	पूर्ण

	वापस 0;
पूर्ण

/* driver bus management functions */

#अगर_घोषित CONFIG_PM_SLEEP

पूर्णांक ks8851_suspend(काष्ठा device *dev)
अणु
	काष्ठा ks8851_net *ks = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = ks->netdev;

	अगर (netअगर_running(netdev)) अणु
		netअगर_device_detach(netdev);
		ks8851_net_stop(netdev);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ks8851_resume(काष्ठा device *dev)
अणु
	काष्ठा ks8851_net *ks = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = ks->netdev;

	अगर (netअगर_running(netdev)) अणु
		ks8851_net_खोलो(netdev);
		netअगर_device_attach(netdev);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ks8851_रेजिस्टर_mdiobus(काष्ठा ks8851_net *ks, काष्ठा device *dev)
अणु
	काष्ठा mii_bus *mii_bus;
	पूर्णांक ret;

	mii_bus = mdiobus_alloc();
	अगर (!mii_bus)
		वापस -ENOMEM;

	mii_bus->name = "ks8851_eth_mii";
	mii_bus->पढ़ो = ks8851_mdio_पढ़ो;
	mii_bus->ग_लिखो = ks8851_mdio_ग_लिखो;
	mii_bus->priv = ks;
	mii_bus->parent = dev;
	mii_bus->phy_mask = ~((u32)BIT(0));
	snम_लिखो(mii_bus->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));

	ret = mdiobus_रेजिस्टर(mii_bus);
	अगर (ret)
		जाओ err_mdiobus_रेजिस्टर;

	ks->mii_bus = mii_bus;

	वापस 0;

err_mdiobus_रेजिस्टर:
	mdiobus_मुक्त(mii_bus);
	वापस ret;
पूर्ण

अटल व्योम ks8851_unरेजिस्टर_mdiobus(काष्ठा ks8851_net *ks)
अणु
	mdiobus_unरेजिस्टर(ks->mii_bus);
	mdiobus_मुक्त(ks->mii_bus);
पूर्ण

पूर्णांक ks8851_probe_common(काष्ठा net_device *netdev, काष्ठा device *dev,
			पूर्णांक msg_en)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(netdev);
	अचिन्हित cider;
	पूर्णांक gpio;
	पूर्णांक ret;

	ks->netdev = netdev;
	ks->tx_space = 6144;

	gpio = of_get_named_gpio_flags(dev->of_node, "reset-gpios", 0, शून्य);
	अगर (gpio == -EPROBE_DEFER)
		वापस gpio;

	ks->gpio = gpio;
	अगर (gpio_is_valid(gpio)) अणु
		ret = devm_gpio_request_one(dev, gpio,
					    GPIOF_OUT_INIT_LOW, "ks8851_rst_n");
		अगर (ret) अणु
			dev_err(dev, "reset gpio request failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ks->vdd_io = devm_regulator_get(dev, "vdd-io");
	अगर (IS_ERR(ks->vdd_io)) अणु
		ret = PTR_ERR(ks->vdd_io);
		जाओ err_reg_io;
	पूर्ण

	ret = regulator_enable(ks->vdd_io);
	अगर (ret) अणु
		dev_err(dev, "regulator vdd_io enable fail: %d\n", ret);
		जाओ err_reg_io;
	पूर्ण

	ks->vdd_reg = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(ks->vdd_reg)) अणु
		ret = PTR_ERR(ks->vdd_reg);
		जाओ err_reg;
	पूर्ण

	ret = regulator_enable(ks->vdd_reg);
	अगर (ret) अणु
		dev_err(dev, "regulator vdd enable fail: %d\n", ret);
		जाओ err_reg;
	पूर्ण

	अगर (gpio_is_valid(gpio)) अणु
		usleep_range(10000, 11000);
		gpio_set_value(gpio, 1);
	पूर्ण

	spin_lock_init(&ks->statelock);

	INIT_WORK(&ks->rxctrl_work, ks8851_rxctrl_work);

	SET_NETDEV_DEV(netdev, dev);

	/* setup EEPROM state */
	ks->eeprom.data = ks;
	ks->eeprom.width = PCI_EEPROM_WIDTH_93C46;
	ks->eeprom.रेजिस्टर_पढ़ो = ks8851_eeprom_regपढ़ो;
	ks->eeprom.रेजिस्टर_ग_लिखो = ks8851_eeprom_regग_लिखो;

	/* setup mii state */
	ks->mii.dev		= netdev;
	ks->mii.phy_id		= 1;
	ks->mii.phy_id_mask	= 1;
	ks->mii.reg_num_mask	= 0xf;
	ks->mii.mdio_पढ़ो	= ks8851_phy_पढ़ो;
	ks->mii.mdio_ग_लिखो	= ks8851_phy_ग_लिखो;

	dev_info(dev, "message enable is %d\n", msg_en);

	ret = ks8851_रेजिस्टर_mdiobus(ks, dev);
	अगर (ret)
		जाओ err_mdio;

	/* set the शेष message enable */
	ks->msg_enable = netअगर_msg_init(msg_en, NETIF_MSG_DRV |
						NETIF_MSG_PROBE |
						NETIF_MSG_LINK);

	skb_queue_head_init(&ks->txq);

	netdev->ethtool_ops = &ks8851_ethtool_ops;

	dev_set_drvdata(dev, ks);

	netअगर_carrier_off(ks->netdev);
	netdev->अगर_port = IF_PORT_100BASET;
	netdev->netdev_ops = &ks8851_netdev_ops;

	/* issue a global soft reset to reset the device. */
	ks8851_soft_reset(ks, GRR_GSR);

	/* simple check क्रम a valid chip being connected to the bus */
	cider = ks8851_rdreg16(ks, KS_CIDER);
	अगर ((cider & ~CIDER_REV_MASK) != CIDER_ID) अणु
		dev_err(dev, "failed to read device ID\n");
		ret = -ENODEV;
		जाओ err_id;
	पूर्ण

	/* cache the contents of the CCR रेजिस्टर क्रम EEPROM, etc. */
	ks->rc_ccr = ks8851_rdreg16(ks, KS_CCR);

	ks8851_पढ़ो_selftest(ks);
	ks8851_init_mac(ks, dev->of_node);

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret) अणु
		dev_err(dev, "failed to register network device\n");
		जाओ err_id;
	पूर्ण

	netdev_info(netdev, "revision %d, MAC %pM, IRQ %d, %s EEPROM\n",
		    CIDER_REV_GET(cider), netdev->dev_addr, netdev->irq,
		    ks->rc_ccr & CCR_EEPROM ? "has" : "no");

	वापस 0;

err_id:
	ks8851_unरेजिस्टर_mdiobus(ks);
err_mdio:
	अगर (gpio_is_valid(gpio))
		gpio_set_value(gpio, 0);
	regulator_disable(ks->vdd_reg);
err_reg:
	regulator_disable(ks->vdd_io);
err_reg_io:
	वापस ret;
पूर्ण

पूर्णांक ks8851_हटाओ_common(काष्ठा device *dev)
अणु
	काष्ठा ks8851_net *priv = dev_get_drvdata(dev);

	ks8851_unरेजिस्टर_mdiobus(priv);

	अगर (netअगर_msg_drv(priv))
		dev_info(dev, "remove\n");

	unरेजिस्टर_netdev(priv->netdev);
	अगर (gpio_is_valid(priv->gpio))
		gpio_set_value(priv->gpio, 0);
	regulator_disable(priv->vdd_reg);
	regulator_disable(priv->vdd_io);

	वापस 0;
पूर्ण
