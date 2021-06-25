<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * meth.c -- O2 Builtin 10/100 Ethernet driver
 *
 * Copyright (C) 2001-2003 Ilya Volynets
 */
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/device.h> /* काष्ठा device, et al */
#समावेश <linux/netdevice.h>   /* काष्ठा device, and other headers */
#समावेश <linux/etherdevice.h> /* eth_type_trans */
#समावेश <linux/ip.h>          /* काष्ठा iphdr */
#समावेश <linux/tcp.h>         /* काष्ठा tcphdr */
#समावेश <linux/skbuff.h>
#समावेश <linux/mii.h>         /* MII definitions */
#समावेश <linux/crc32.h>

#समावेश <यंत्र/ip32/mace.h>
#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>

#समावेश <यंत्र/पन.स>

#समावेश "meth.h"

#अगर_अघोषित MFE_DEBUG
#घोषणा MFE_DEBUG 0
#पूर्ण_अगर

#अगर MFE_DEBUG>=1
#घोषणा DPRINTK(str,args...) prपूर्णांकk(KERN_DEBUG "meth: %s: " str, __func__ , ## args)
#घोषणा MFE_RX_DEBUG 2
#अन्यथा
#घोषणा DPRINTK(str,args...)
#घोषणा MFE_RX_DEBUG 0
#पूर्ण_अगर


अटल स्थिर अक्षर *meth_str="SGI O2 Fast Ethernet";

/* The maximum समय रुकोed (in jअगरfies) beक्रमe assuming a Tx failed. (400ms) */
#घोषणा TX_TIMEOUT (400*HZ/1000)

अटल पूर्णांक समयout = TX_TIMEOUT;
module_param(समयout, पूर्णांक, 0);

/*
 * Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
 * MACE Ethernet uses a 64 element hash table based on the Ethernet CRC.
 */
#घोषणा METH_MCF_LIMIT 32

/*
 * This काष्ठाure is निजी to each device. It is used to pass
 * packets in and out, so there is place क्रम a packet
 */
काष्ठा meth_निजी अणु
	काष्ठा platक्रमm_device *pdev;

	/* in-memory copy of MAC Control रेजिस्टर */
	u64 mac_ctrl;

	/* in-memory copy of DMA Control रेजिस्टर */
	अचिन्हित दीर्घ dma_ctrl;
	/* address of PHY, used by mdio_* functions, initialized in mdio_probe */
	अचिन्हित दीर्घ phy_addr;
	tx_packet *tx_ring;
	dma_addr_t tx_ring_dma;
	काष्ठा sk_buff *tx_skbs[TX_RING_ENTRIES];
	dma_addr_t tx_skb_dmas[TX_RING_ENTRIES];
	अचिन्हित दीर्घ tx_पढ़ो, tx_ग_लिखो, tx_count;

	rx_packet *rx_ring[RX_RING_ENTRIES];
	dma_addr_t rx_ring_dmas[RX_RING_ENTRIES];
	काष्ठा sk_buff *rx_skbs[RX_RING_ENTRIES];
	अचिन्हित दीर्घ rx_ग_लिखो;

	/* Multicast filter. */
	u64 mcast_filter;

	spinlock_t meth_lock;
पूर्ण;

अटल व्योम meth_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल irqवापस_t meth_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

/* global, initialized in ip32-setup.c */
अक्षर o2meth_eaddr[8]=अणु0,0,0,0,0,0,0,0पूर्ण;

अटल अंतरभूत व्योम load_eaddr(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	u64 macaddr;

	DPRINTK("Loading MAC Address: %pM\n", dev->dev_addr);
	macaddr = 0;
	क्रम (i = 0; i < 6; i++)
		macaddr |= (u64)dev->dev_addr[i] << ((5 - i) * 8);

	mace->eth.mac_addr = macaddr;
पूर्ण

/*
 * Waits क्रम BUSY status of mdio bus to clear
 */
#घोषणा WAIT_FOR_PHY(___rval)					\
	जबतक ((___rval = mace->eth.phy_data) & MDIO_BUSY) अणु	\
		udelay(25);					\
	पूर्ण
/*पढ़ो phy रेजिस्टर, वापस value पढ़ो */
अटल अचिन्हित दीर्घ mdio_पढ़ो(काष्ठा meth_निजी *priv, अचिन्हित दीर्घ phyreg)
अणु
	अचिन्हित दीर्घ rval;
	WAIT_FOR_PHY(rval);
	mace->eth.phy_regs = (priv->phy_addr << 5) | (phyreg & 0x1f);
	udelay(25);
	mace->eth.phy_trans_go = 1;
	udelay(25);
	WAIT_FOR_PHY(rval);
	वापस rval & MDIO_DATA_MASK;
पूर्ण

अटल पूर्णांक mdio_probe(काष्ठा meth_निजी *priv)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ p2, p3, flags;
	/* check अगर phy is detected alपढ़ोy */
	अगर(priv->phy_addr>=0&&priv->phy_addr<32)
		वापस 0;
	spin_lock_irqsave(&priv->meth_lock, flags);
	क्रम (i=0;i<32;++i)अणु
		priv->phy_addr=i;
		p2=mdio_पढ़ो(priv,2);
		p3=mdio_पढ़ो(priv,3);
#अगर MFE_DEBUG>=2
		चयन ((p2<<12)|(p3>>4))अणु
		हाल PHY_QS6612X:
			DPRINTK("PHY is QS6612X\n");
			अवरोध;
		हाल PHY_ICS1889:
			DPRINTK("PHY is ICS1889\n");
			अवरोध;
		हाल PHY_ICS1890:
			DPRINTK("PHY is ICS1890\n");
			अवरोध;
		हाल PHY_DP83840:
			DPRINTK("PHY is DP83840\n");
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		अगर(p2!=0xffff&&p2!=0x0000)अणु
			DPRINTK("PHY code: %x\n",(p2<<12)|(p3>>4));
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->meth_lock, flags);
	अगर(priv->phy_addr<32) अणु
		वापस 0;
	पूर्ण
	DPRINTK("Oopsie! PHY is not known!\n");
	priv->phy_addr=-1;
	वापस -ENODEV;
पूर्ण

अटल व्योम meth_check_link(काष्ठा net_device *dev)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ mii_advertising = mdio_पढ़ो(priv, 4);
	अचिन्हित दीर्घ mii_partner = mdio_पढ़ो(priv, 5);
	अचिन्हित दीर्घ negotiated = mii_advertising & mii_partner;
	अचिन्हित दीर्घ duplex, speed;

	अगर (mii_partner == 0xffff)
		वापस;

	speed = (negotiated & 0x0380) ? METH_100MBIT : 0;
	duplex = ((negotiated & 0x0100) || (negotiated & 0x01C0) == 0x0040) ?
		 METH_PHY_FDX : 0;

	अगर ((priv->mac_ctrl & METH_PHY_FDX) ^ duplex) अणु
		DPRINTK("Setting %s-duplex\n", duplex ? "full" : "half");
		अगर (duplex)
			priv->mac_ctrl |= METH_PHY_FDX;
		अन्यथा
			priv->mac_ctrl &= ~METH_PHY_FDX;
		mace->eth.mac_ctrl = priv->mac_ctrl;
	पूर्ण

	अगर ((priv->mac_ctrl & METH_100MBIT) ^ speed) अणु
		DPRINTK("Setting %dMbs mode\n", speed ? 100 : 10);
		अगर (duplex)
			priv->mac_ctrl |= METH_100MBIT;
		अन्यथा
			priv->mac_ctrl &= ~METH_100MBIT;
		mace->eth.mac_ctrl = priv->mac_ctrl;
	पूर्ण
पूर्ण


अटल पूर्णांक meth_init_tx_ring(काष्ठा meth_निजी *priv)
अणु
	/* Init TX ring */
	priv->tx_ring = dma_alloc_coherent(&priv->pdev->dev,
			TX_RING_BUFFER_SIZE, &priv->tx_ring_dma, GFP_ATOMIC);
	अगर (!priv->tx_ring)
		वापस -ENOMEM;

	priv->tx_count = priv->tx_पढ़ो = priv->tx_ग_लिखो = 0;
	mace->eth.tx_ring_base = priv->tx_ring_dma;
	/* Now init skb save area */
	स_रखो(priv->tx_skbs, 0, माप(priv->tx_skbs));
	स_रखो(priv->tx_skb_dmas, 0, माप(priv->tx_skb_dmas));
	वापस 0;
पूर्ण

अटल पूर्णांक meth_init_rx_ring(काष्ठा meth_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RX_RING_ENTRIES; i++) अणु
		priv->rx_skbs[i] = alloc_skb(METH_RX_BUFF_SIZE, 0);
		/* 8byte status vector + 3quad padding + 2byte padding,
		 * to put data on 64bit aligned boundary */
		skb_reserve(priv->rx_skbs[i],METH_RX_HEAD);
		priv->rx_ring[i]=(rx_packet*)(priv->rx_skbs[i]->head);
		/* I'll need to re-sync it after each RX */
		priv->rx_ring_dmas[i] =
			dma_map_single(&priv->pdev->dev, priv->rx_ring[i],
				       METH_RX_BUFF_SIZE, DMA_FROM_DEVICE);
		mace->eth.rx_fअगरo = priv->rx_ring_dmas[i];
	पूर्ण
        priv->rx_ग_लिखो = 0;
	वापस 0;
पूर्ण
अटल व्योम meth_मुक्त_tx_ring(काष्ठा meth_निजी *priv)
अणु
	पूर्णांक i;

	/* Remove any pending skb */
	क्रम (i = 0; i < TX_RING_ENTRIES; i++) अणु
		dev_kमुक्त_skb(priv->tx_skbs[i]);
		priv->tx_skbs[i] = शून्य;
	पूर्ण
	dma_मुक्त_coherent(&priv->pdev->dev, TX_RING_BUFFER_SIZE, priv->tx_ring,
	                  priv->tx_ring_dma);
पूर्ण

/* Presumes RX DMA engine is stopped, and RX fअगरo ring is reset */
अटल व्योम meth_मुक्त_rx_ring(काष्ठा meth_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RX_RING_ENTRIES; i++) अणु
		dma_unmap_single(&priv->pdev->dev, priv->rx_ring_dmas[i],
				 METH_RX_BUFF_SIZE, DMA_FROM_DEVICE);
		priv->rx_ring[i] = 0;
		priv->rx_ring_dmas[i] = 0;
		kमुक्त_skb(priv->rx_skbs[i]);
	पूर्ण
पूर्ण

पूर्णांक meth_reset(काष्ठा net_device *dev)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);

	/* Reset card */
	mace->eth.mac_ctrl = SGI_MAC_RESET;
	udelay(1);
	mace->eth.mac_ctrl = 0;
	udelay(25);

	/* Load ethernet address */
	load_eaddr(dev);
	/* Should load some "errata", but later */

	/* Check क्रम device */
	अगर (mdio_probe(priv) < 0) अणु
		DPRINTK("Unable to find PHY\n");
		वापस -ENODEV;
	पूर्ण

	/* Initial mode: 10 | Half-duplex | Accept normal packets */
	priv->mac_ctrl = METH_ACCEPT_MCAST | METH_DEFAULT_IPG;
	अगर (dev->flags & IFF_PROMISC)
		priv->mac_ctrl |= METH_PROMISC;
	mace->eth.mac_ctrl = priv->mac_ctrl;

	/* Autonegotiate speed and duplex mode */
	meth_check_link(dev);

	/* Now set dma control, but करोn't enable DMA, yet */
	priv->dma_ctrl = (4 << METH_RX_OFFSET_SHIFT) |
			 (RX_RING_ENTRIES << METH_RX_DEPTH_SHIFT);
	mace->eth.dma_ctrl = priv->dma_ctrl;

	वापस 0;
पूर्ण

/*============End Helper Routines=====================*/

/*
 * Open and बंद
 */
अटल पूर्णांक meth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);
	पूर्णांक ret;

	priv->phy_addr = -1;    /* No PHY is known yet... */

	/* Initialize the hardware */
	ret = meth_reset(dev);
	अगर (ret < 0)
		वापस ret;

	/* Allocate the ring buffers */
	ret = meth_init_tx_ring(priv);
	अगर (ret < 0)
		वापस ret;
	ret = meth_init_rx_ring(priv);
	अगर (ret < 0)
		जाओ out_मुक्त_tx_ring;

	ret = request_irq(dev->irq, meth_पूर्णांकerrupt, 0, meth_str, dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: Can't get irq %d\n", dev->name, dev->irq);
		जाओ out_मुक्त_rx_ring;
	पूर्ण

	/* Start DMA */
	priv->dma_ctrl |= METH_DMA_TX_EN | /*METH_DMA_TX_INT_EN |*/
			  METH_DMA_RX_EN | METH_DMA_RX_INT_EN;
	mace->eth.dma_ctrl = priv->dma_ctrl;

	DPRINTK("About to start queue\n");
	netअगर_start_queue(dev);

	वापस 0;

out_मुक्त_rx_ring:
	meth_मुक्त_rx_ring(priv);
out_मुक्त_tx_ring:
	meth_मुक्त_tx_ring(priv);

	वापस ret;
पूर्ण

अटल पूर्णांक meth_release(काष्ठा net_device *dev)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);

	DPRINTK("Stopping queue\n");
	netअगर_stop_queue(dev); /* can't transmit any more */
	/* shut करोwn DMA */
	priv->dma_ctrl &= ~(METH_DMA_TX_EN | METH_DMA_TX_INT_EN |
			    METH_DMA_RX_EN | METH_DMA_RX_INT_EN);
	mace->eth.dma_ctrl = priv->dma_ctrl;
	मुक्त_irq(dev->irq, dev);
	meth_मुक्त_tx_ring(priv);
	meth_मुक्त_rx_ring(priv);

	वापस 0;
पूर्ण

/*
 * Receive a packet: retrieve, encapsulate and pass over to upper levels
 */
अटल व्योम meth_rx(काष्ठा net_device* dev, अचिन्हित दीर्घ पूर्णांक_status)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ status, flags;
	काष्ठा meth_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ fअगरo_rptr = (पूर्णांक_status & METH_INT_RX_RPTR_MASK) >> 8;

	spin_lock_irqsave(&priv->meth_lock, flags);
	priv->dma_ctrl &= ~METH_DMA_RX_INT_EN;
	mace->eth.dma_ctrl = priv->dma_ctrl;
	spin_unlock_irqrestore(&priv->meth_lock, flags);

	अगर (पूर्णांक_status & METH_INT_RX_UNDERFLOW) अणु
		fअगरo_rptr = (fअगरo_rptr - 1) & 0x0f;
	पूर्ण
	जबतक (priv->rx_ग_लिखो != fअगरo_rptr) अणु
		dma_unmap_single(&priv->pdev->dev,
				 priv->rx_ring_dmas[priv->rx_ग_लिखो],
				 METH_RX_BUFF_SIZE, DMA_FROM_DEVICE);
		status = priv->rx_ring[priv->rx_ग_लिखो]->status.raw;
#अगर MFE_DEBUG
		अगर (!(status & METH_RX_ST_VALID)) अणु
			DPRINTK("Not received? status=%016lx\n",status);
		पूर्ण
#पूर्ण_अगर
		अगर ((!(status & METH_RX_STATUS_ERRORS)) && (status & METH_RX_ST_VALID)) अणु
			पूर्णांक len = (status & 0xffff) - 4; /* omit CRC */
			/* length sanity check */
			अगर (len < 60 || len > 1518) अणु
				prपूर्णांकk(KERN_DEBUG "%s: bogus packet size: %ld, status=%#2Lx.\n",
				       dev->name, priv->rx_ग_लिखो,
				       priv->rx_ring[priv->rx_ग_लिखो]->status.raw);
				dev->stats.rx_errors++;
				dev->stats.rx_length_errors++;
				skb = priv->rx_skbs[priv->rx_ग_लिखो];
			पूर्ण अन्यथा अणु
				skb = alloc_skb(METH_RX_BUFF_SIZE, GFP_ATOMIC);
				अगर (!skb) अणु
					/* Ouch! No memory! Drop packet on the न्यूनमान */
					DPRINTK("No mem: dropping packet\n");
					dev->stats.rx_dropped++;
					skb = priv->rx_skbs[priv->rx_ग_लिखो];
				पूर्ण अन्यथा अणु
					काष्ठा sk_buff *skb_c = priv->rx_skbs[priv->rx_ग_लिखो];
					/* 8byte status vector + 3quad padding + 2byte padding,
					 * to put data on 64bit aligned boundary */
					skb_reserve(skb, METH_RX_HEAD);
					/* Write metadata, and then pass to the receive level */
					skb_put(skb_c, len);
					priv->rx_skbs[priv->rx_ग_लिखो] = skb;
					skb_c->protocol = eth_type_trans(skb_c, dev);
					dev->stats.rx_packets++;
					dev->stats.rx_bytes += len;
					netअगर_rx(skb_c);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			dev->stats.rx_errors++;
			skb=priv->rx_skbs[priv->rx_ग_लिखो];
#अगर MFE_DEBUG>0
			prपूर्णांकk(KERN_WARNING "meth: RX error: status=0x%016lx\n",status);
			अगर(status&METH_RX_ST_RCV_CODE_VIOLATION)
				prपूर्णांकk(KERN_WARNING "Receive Code Violation\n");
			अगर(status&METH_RX_ST_CRC_ERR)
				prपूर्णांकk(KERN_WARNING "CRC error\n");
			अगर(status&METH_RX_ST_INV_PREAMBLE_CTX)
				prपूर्णांकk(KERN_WARNING "Invalid Preamble Context\n");
			अगर(status&METH_RX_ST_LONG_EVT_SEEN)
				prपूर्णांकk(KERN_WARNING "Long Event Seen...\n");
			अगर(status&METH_RX_ST_BAD_PACKET)
				prपूर्णांकk(KERN_WARNING "Bad Packet\n");
			अगर(status&METH_RX_ST_CARRIER_EVT_SEEN)
				prपूर्णांकk(KERN_WARNING "Carrier Event Seen\n");
#पूर्ण_अगर
		पूर्ण
		priv->rx_ring[priv->rx_ग_लिखो] = (rx_packet*)skb->head;
		priv->rx_ring[priv->rx_ग_लिखो]->status.raw = 0;
		priv->rx_ring_dmas[priv->rx_ग_लिखो] =
			dma_map_single(&priv->pdev->dev,
				       priv->rx_ring[priv->rx_ग_लिखो],
				       METH_RX_BUFF_SIZE, DMA_FROM_DEVICE);
		mace->eth.rx_fअगरo = priv->rx_ring_dmas[priv->rx_ग_लिखो];
		ADVANCE_RX_PTR(priv->rx_ग_लिखो);
	पूर्ण
	spin_lock_irqsave(&priv->meth_lock, flags);
	/* In हाल there was underflow, and Rx DMA was disabled */
	priv->dma_ctrl |= METH_DMA_RX_INT_EN | METH_DMA_RX_EN;
	mace->eth.dma_ctrl = priv->dma_ctrl;
	mace->eth.पूर्णांक_stat = METH_INT_RX_THRESHOLD;
	spin_unlock_irqrestore(&priv->meth_lock, flags);
पूर्ण

अटल पूर्णांक meth_tx_full(काष्ठा net_device *dev)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);

	वापस priv->tx_count >= TX_RING_ENTRIES - 1;
पूर्ण

अटल व्योम meth_tx_cleanup(काष्ठा net_device* dev, अचिन्हित दीर्घ पूर्णांक_status)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ status, flags;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ rptr = (पूर्णांक_status&TX_INFO_RPTR) >> 16;

	spin_lock_irqsave(&priv->meth_lock, flags);

	/* Stop DMA notअगरication */
	priv->dma_ctrl &= ~(METH_DMA_TX_INT_EN);
	mace->eth.dma_ctrl = priv->dma_ctrl;

	जबतक (priv->tx_पढ़ो != rptr) अणु
		skb = priv->tx_skbs[priv->tx_पढ़ो];
		status = priv->tx_ring[priv->tx_पढ़ो].header.raw;
#अगर MFE_DEBUG>=1
		अगर (priv->tx_पढ़ो == priv->tx_ग_लिखो)
			DPRINTK("Auchi! tx_read=%d,tx_write=%d,rptr=%d?\n", priv->tx_पढ़ो, priv->tx_ग_लिखो,rptr);
#पूर्ण_अगर
		अगर (status & METH_TX_ST_DONE) अणु
			अगर (status & METH_TX_ST_SUCCESS)अणु
				dev->stats.tx_packets++;
				dev->stats.tx_bytes += skb->len;
			पूर्ण अन्यथा अणु
				dev->stats.tx_errors++;
#अगर MFE_DEBUG>=1
				DPRINTK("TX error: status=%016lx <",status);
				अगर(status & METH_TX_ST_SUCCESS)
					prपूर्णांकk(" SUCCESS");
				अगर(status & METH_TX_ST_TOOLONG)
					prपूर्णांकk(" TOOLONG");
				अगर(status & METH_TX_ST_UNDERRUN)
					prपूर्णांकk(" UNDERRUN");
				अगर(status & METH_TX_ST_EXCCOLL)
					prपूर्णांकk(" EXCCOLL");
				अगर(status & METH_TX_ST_DEFER)
					prपूर्णांकk(" DEFER");
				अगर(status & METH_TX_ST_LATECOLL)
					prपूर्णांकk(" LATECOLL");
				prपूर्णांकk(" >\n");
#पूर्ण_अगर
			पूर्ण
		पूर्ण अन्यथा अणु
			DPRINTK("RPTR points us here, but packet not done?\n");
			अवरोध;
		पूर्ण
		dev_consume_skb_irq(skb);
		priv->tx_skbs[priv->tx_पढ़ो] = शून्य;
		priv->tx_ring[priv->tx_पढ़ो].header.raw = 0;
		priv->tx_पढ़ो = (priv->tx_पढ़ो+1)&(TX_RING_ENTRIES-1);
		priv->tx_count--;
	पूर्ण

	/* wake up queue अगर it was stopped */
	अगर (netअगर_queue_stopped(dev) && !meth_tx_full(dev)) अणु
		netअगर_wake_queue(dev);
	पूर्ण

	mace->eth.पूर्णांक_stat = METH_INT_TX_EMPTY | METH_INT_TX_PKT;
	spin_unlock_irqrestore(&priv->meth_lock, flags);
पूर्ण

अटल व्योम meth_error(काष्ठा net_device* dev, अचिन्हित status)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	prपूर्णांकk(KERN_WARNING "meth: error status: 0x%08x\n",status);
	/* check क्रम errors too... */
	अगर (status & (METH_INT_TX_LINK_FAIL))
		prपूर्णांकk(KERN_WARNING "meth: link failure\n");
	/* Should I करो full reset in this हाल? */
	अगर (status & (METH_INT_MEM_ERROR))
		prपूर्णांकk(KERN_WARNING "meth: memory error\n");
	अगर (status & (METH_INT_TX_ABORT))
		prपूर्णांकk(KERN_WARNING "meth: aborted\n");
	अगर (status & (METH_INT_RX_OVERFLOW))
		prपूर्णांकk(KERN_WARNING "meth: Rx overflow\n");
	अगर (status & (METH_INT_RX_UNDERFLOW)) अणु
		prपूर्णांकk(KERN_WARNING "meth: Rx underflow\n");
		spin_lock_irqsave(&priv->meth_lock, flags);
		mace->eth.पूर्णांक_stat = METH_INT_RX_UNDERFLOW;
		/* more underflow पूर्णांकerrupts will be delivered,
		 * effectively throwing us पूर्णांकo an infinite loop.
		 *  Thus I stop processing Rx in this हाल. */
		priv->dma_ctrl &= ~METH_DMA_RX_EN;
		mace->eth.dma_ctrl = priv->dma_ctrl;
		DPRINTK("Disabled meth Rx DMA temporarily\n");
		spin_unlock_irqrestore(&priv->meth_lock, flags);
	पूर्ण
	mace->eth.पूर्णांक_stat = METH_INT_ERROR;
पूर्ण

/*
 * The typical पूर्णांकerrupt entry poपूर्णांक
 */
अटल irqवापस_t meth_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा meth_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ status;

	status = mace->eth.पूर्णांक_stat;
	जबतक (status & 0xff) अणु
		/* First handle errors - अगर we get Rx underflow,
		 * Rx DMA will be disabled, and Rx handler will reenable
		 * it. I करोn't think it's possible to get Rx underflow,
		 * without getting Rx पूर्णांकerrupt */
		अगर (status & METH_INT_ERROR) अणु
			meth_error(dev, status);
		पूर्ण
		अगर (status & (METH_INT_TX_EMPTY | METH_INT_TX_PKT)) अणु
			/* a transmission is over: मुक्त the skb */
			meth_tx_cleanup(dev, status);
		पूर्ण
		अगर (status & METH_INT_RX_THRESHOLD) अणु
			अगर (!(priv->dma_ctrl & METH_DMA_RX_INT_EN))
				अवरोध;
			/* send it to meth_rx क्रम handling */
			meth_rx(dev, status);
		पूर्ण
		status = mace->eth.पूर्णांक_stat;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Transmits packets that fit पूर्णांकo TX descriptor (are <=120B)
 */
अटल व्योम meth_tx_लघु_prepare(काष्ठा meth_निजी *priv,
				  काष्ठा sk_buff *skb)
अणु
	tx_packet *desc = &priv->tx_ring[priv->tx_ग_लिखो];
	पूर्णांक len = (skb->len < ETH_ZLEN) ? ETH_ZLEN : skb->len;

	desc->header.raw = METH_TX_CMD_INT_EN | (len-1) | ((128-len) << 16);
	/* maybe I should set whole thing to 0 first... */
	skb_copy_from_linear_data(skb, desc->data.dt + (120 - len), skb->len);
	अगर (skb->len < len)
		स_रखो(desc->data.dt + 120 - len + skb->len, 0, len-skb->len);
पूर्ण
#घोषणा TX_CATBUF1 BIT(25)
अटल व्योम meth_tx_1page_prepare(काष्ठा meth_निजी *priv,
				  काष्ठा sk_buff *skb)
अणु
	tx_packet *desc = &priv->tx_ring[priv->tx_ग_लिखो];
	व्योम *buffer_data = (व्योम *)(((अचिन्हित दीर्घ)skb->data + 7) & ~7);
	पूर्णांक unaligned_len = (पूर्णांक)((अचिन्हित दीर्घ)buffer_data - (अचिन्हित दीर्घ)skb->data);
	पूर्णांक buffer_len = skb->len - unaligned_len;
	dma_addr_t catbuf;

	desc->header.raw = METH_TX_CMD_INT_EN | TX_CATBUF1 | (skb->len - 1);

	/* unaligned part */
	अगर (unaligned_len) अणु
		skb_copy_from_linear_data(skb, desc->data.dt + (120 - unaligned_len),
			      unaligned_len);
		desc->header.raw |= (128 - unaligned_len) << 16;
	पूर्ण

	/* first page */
	catbuf = dma_map_single(&priv->pdev->dev, buffer_data, buffer_len,
				DMA_TO_DEVICE);
	desc->data.cat_buf[0].क्रमm.start_addr = catbuf >> 3;
	desc->data.cat_buf[0].क्रमm.len = buffer_len - 1;
पूर्ण
#घोषणा TX_CATBUF2 BIT(26)
अटल व्योम meth_tx_2page_prepare(काष्ठा meth_निजी *priv,
				  काष्ठा sk_buff *skb)
अणु
	tx_packet *desc = &priv->tx_ring[priv->tx_ग_लिखो];
	व्योम *buffer1_data = (व्योम *)(((अचिन्हित दीर्घ)skb->data + 7) & ~7);
	व्योम *buffer2_data = (व्योम *)PAGE_ALIGN((अचिन्हित दीर्घ)skb->data);
	पूर्णांक unaligned_len = (पूर्णांक)((अचिन्हित दीर्घ)buffer1_data - (अचिन्हित दीर्घ)skb->data);
	पूर्णांक buffer1_len = (पूर्णांक)((अचिन्हित दीर्घ)buffer2_data - (अचिन्हित दीर्घ)buffer1_data);
	पूर्णांक buffer2_len = skb->len - buffer1_len - unaligned_len;
	dma_addr_t catbuf1, catbuf2;

	desc->header.raw = METH_TX_CMD_INT_EN | TX_CATBUF1 | TX_CATBUF2| (skb->len - 1);
	/* unaligned part */
	अगर (unaligned_len)अणु
		skb_copy_from_linear_data(skb, desc->data.dt + (120 - unaligned_len),
			      unaligned_len);
		desc->header.raw |= (128 - unaligned_len) << 16;
	पूर्ण

	/* first page */
	catbuf1 = dma_map_single(&priv->pdev->dev, buffer1_data, buffer1_len,
				 DMA_TO_DEVICE);
	desc->data.cat_buf[0].क्रमm.start_addr = catbuf1 >> 3;
	desc->data.cat_buf[0].क्रमm.len = buffer1_len - 1;
	/* second page */
	catbuf2 = dma_map_single(&priv->pdev->dev, buffer2_data, buffer2_len,
				 DMA_TO_DEVICE);
	desc->data.cat_buf[1].क्रमm.start_addr = catbuf2 >> 3;
	desc->data.cat_buf[1].क्रमm.len = buffer2_len - 1;
पूर्ण

अटल व्योम meth_add_to_tx_ring(काष्ठा meth_निजी *priv, काष्ठा sk_buff *skb)
अणु
	/* Remember the skb, so we can मुक्त it at पूर्णांकerrupt समय */
	priv->tx_skbs[priv->tx_ग_लिखो] = skb;
	अगर (skb->len <= 120) अणु
		/* Whole packet fits पूर्णांकo descriptor */
		meth_tx_लघु_prepare(priv, skb);
	पूर्ण अन्यथा अगर (PAGE_ALIGN((अचिन्हित दीर्घ)skb->data) !=
		   PAGE_ALIGN((अचिन्हित दीर्घ)skb->data + skb->len - 1)) अणु
		/* Packet crosses page boundary */
		meth_tx_2page_prepare(priv, skb);
	पूर्ण अन्यथा अणु
		/* Packet is in one page */
		meth_tx_1page_prepare(priv, skb);
	पूर्ण
	priv->tx_ग_लिखो = (priv->tx_ग_लिखो + 1) & (TX_RING_ENTRIES - 1);
	mace->eth.tx_info = priv->tx_ग_लिखो;
	priv->tx_count++;
पूर्ण

/*
 * Transmit a packet (called by the kernel)
 */
अटल netdev_tx_t meth_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->meth_lock, flags);
	/* Stop DMA notअगरication */
	priv->dma_ctrl &= ~(METH_DMA_TX_INT_EN);
	mace->eth.dma_ctrl = priv->dma_ctrl;

	meth_add_to_tx_ring(priv, skb);
	netअगर_trans_update(dev); /* save the बारtamp */

	/* If TX ring is full, tell the upper layer to stop sending packets */
	अगर (meth_tx_full(dev)) अणु
	        prपूर्णांकk(KERN_DEBUG "TX full: stopping\n");
		netअगर_stop_queue(dev);
	पूर्ण

	/* Restart DMA notअगरication */
	priv->dma_ctrl |= METH_DMA_TX_INT_EN;
	mace->eth.dma_ctrl = priv->dma_ctrl;

	spin_unlock_irqrestore(&priv->meth_lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * Deal with a transmit समयout.
 */
अटल व्योम meth_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	prपूर्णांकk(KERN_WARNING "%s: transmit timed out\n", dev->name);

	/* Protect against concurrent rx पूर्णांकerrupts */
	spin_lock_irqsave(&priv->meth_lock,flags);

	/* Try to reset the पूर्णांकerface. */
	meth_reset(dev);

	dev->stats.tx_errors++;

	/* Clear all rings */
	meth_मुक्त_tx_ring(priv);
	meth_मुक्त_rx_ring(priv);
	meth_init_tx_ring(priv);
	meth_init_rx_ring(priv);

	/* Restart dma */
	priv->dma_ctrl |= METH_DMA_TX_EN | METH_DMA_RX_EN | METH_DMA_RX_INT_EN;
	mace->eth.dma_ctrl = priv->dma_ctrl;

	/* Enable पूर्णांकerrupt */
	spin_unlock_irqrestore(&priv->meth_lock, flags);

	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण

/*
 * Ioctl commands
 */
अटल पूर्णांक meth_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	/* XXX Not yet implemented */
	चयन(cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम meth_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा meth_निजी *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue(dev);
	spin_lock_irqsave(&priv->meth_lock, flags);
	priv->mac_ctrl &= ~METH_PROMISC;

	अगर (dev->flags & IFF_PROMISC) अणु
		priv->mac_ctrl |= METH_PROMISC;
		priv->mcast_filter = 0xffffffffffffffffUL;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > METH_MCF_LIMIT) ||
		   (dev->flags & IFF_ALLMULTI)) अणु
		priv->mac_ctrl |= METH_ACCEPT_AMCAST;
		priv->mcast_filter = 0xffffffffffffffffUL;
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		priv->mac_ctrl |= METH_ACCEPT_MCAST;

		netdev_क्रम_each_mc_addr(ha, dev)
			set_bit((ether_crc(ETH_ALEN, ha->addr) >> 26),
			        (अस्थिर अचिन्हित दीर्घ *)&priv->mcast_filter);
	पूर्ण

	/* Write the changes to the chip रेजिस्टरs. */
	mace->eth.mac_ctrl = priv->mac_ctrl;
	mace->eth.mcast_filter = priv->mcast_filter;

	/* Done! */
	spin_unlock_irqrestore(&priv->meth_lock, flags);
	netअगर_wake_queue(dev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops meth_netdev_ops = अणु
	.nकरो_खोलो		= meth_खोलो,
	.nकरो_stop		= meth_release,
	.nकरो_start_xmit		= meth_tx,
	.nकरो_करो_ioctl		= meth_ioctl,
	.nकरो_tx_समयout		= meth_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_set_rx_mode    	= meth_set_rx_mode,
पूर्ण;

/*
 * The init function.
 */
अटल पूर्णांक meth_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा meth_निजी *priv;
	पूर्णांक err;

	dev = alloc_etherdev(माप(काष्ठा meth_निजी));
	अगर (!dev)
		वापस -ENOMEM;

	dev->netdev_ops		= &meth_netdev_ops;
	dev->watchकरोg_समयo	= समयout;
	dev->irq		= MACE_ETHERNET_IRQ;
	dev->base_addr		= (अचिन्हित दीर्घ)&mace->eth;
	स_नकल(dev->dev_addr, o2meth_eaddr, ETH_ALEN);

	priv = netdev_priv(dev);
	priv->pdev = pdev;
	spin_lock_init(&priv->meth_lock);
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: SGI MACE Ethernet rev. %d\n",
	       dev->name, (अचिन्हित पूर्णांक)(mace->eth.mac_ctrl >> 29));
	वापस 0;
पूर्ण

अटल पूर्णांक meth_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver meth_driver = अणु
	.probe	= meth_probe,
	.हटाओ	= meth_हटाओ,
	.driver = अणु
		.name	= "meth",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(meth_driver);

MODULE_AUTHOR("Ilya Volynets <ilya@theIlya.com>");
MODULE_DESCRIPTION("SGI O2 Builtin Fast Ethernet driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:meth");
