<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * smc911x.c
 * This is a driver क्रम SMSC's LAN911अणु5,6,7,8पूर्ण single-chip Ethernet devices.
 *
 * Copyright (C) 2005 Sensoria Corp
 *	   Derived from the unअगरied SMC91x driver by Nicolas Pitre
 *	   and the smsc911x.c reference driver by SMSC
 *
 * Arguments:
 *	 watchकरोg  = TX watchकरोg समयout
 *	 tx_fअगरo_kb = Size of TX FIFO in KB
 *
 * History:
 *	  04/16/05	Dustin McIntire		 Initial version
 */
अटल स्थिर अक्षर version[] =
	 "smc911x.c: v1.0 04-16-2005 by Dustin McIntire <dustin@sensoria.com>\n";

/* Debugging options */
#घोषणा ENABLE_SMC_DEBUG_RX		0
#घोषणा ENABLE_SMC_DEBUG_TX		0
#घोषणा ENABLE_SMC_DEBUG_DMA		0
#घोषणा ENABLE_SMC_DEBUG_PKTS		0
#घोषणा ENABLE_SMC_DEBUG_MISC		0
#घोषणा ENABLE_SMC_DEBUG_FUNC		0

#घोषणा SMC_DEBUG_RX		((ENABLE_SMC_DEBUG_RX	? 1 : 0) << 0)
#घोषणा SMC_DEBUG_TX		((ENABLE_SMC_DEBUG_TX	? 1 : 0) << 1)
#घोषणा SMC_DEBUG_DMA		((ENABLE_SMC_DEBUG_DMA	? 1 : 0) << 2)
#घोषणा SMC_DEBUG_PKTS		((ENABLE_SMC_DEBUG_PKTS ? 1 : 0) << 3)
#घोषणा SMC_DEBUG_MISC		((ENABLE_SMC_DEBUG_MISC ? 1 : 0) << 4)
#घोषणा SMC_DEBUG_FUNC		((ENABLE_SMC_DEBUG_FUNC ? 1 : 0) << 5)

#अगर_अघोषित SMC_DEBUG
#घोषणा SMC_DEBUG	 ( SMC_DEBUG_RX	  | \
			   SMC_DEBUG_TX	  | \
			   SMC_DEBUG_DMA  | \
			   SMC_DEBUG_PKTS | \
			   SMC_DEBUG_MISC | \
			   SMC_DEBUG_FUNC   \
			 )
#पूर्ण_अगर

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/crc32.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/dmaengine.h>

#समावेश <यंत्र/पन.स>

#समावेश "smc911x.h"

/*
 * Transmit समयout, शेष 5 seconds.
 */
अटल पूर्णांक watchकरोg = 5000;
module_param(watchकरोg, पूर्णांक, 0400);
MODULE_PARM_DESC(watchकरोg, "transmit timeout in milliseconds");

अटल पूर्णांक tx_fअगरo_kb=8;
module_param(tx_fअगरo_kb, पूर्णांक, 0400);
MODULE_PARM_DESC(tx_fअगरo_kb,"transmit FIFO size in KB (1<x<15)(default=8)");

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:smc911x");

/*
 * The पूर्णांकernal workings of the driver.  If you are changing anything
 * here with the SMC stuff, you should have the datasheet and know
 * what you are करोing.
 */
#घोषणा CARDNAME "smc911x"

/*
 * Use घातer-करोwn feature of the chip
 */
#घोषणा POWER_DOWN		 1

#अगर SMC_DEBUG > 0
#घोषणा DBG(n, dev, args...)			 \
	करो अणु					 \
		अगर (SMC_DEBUG & (n))		 \
			netdev_dbg(dev, args);	 \
	पूर्ण जबतक (0)

#घोषणा PRINTK(dev, args...)   netdev_info(dev, args)
#अन्यथा
#घोषणा DBG(n, dev, args...)			 \
	जबतक (0) अणु				 \
		netdev_dbg(dev, args);		 \
	पूर्ण
#घोषणा PRINTK(dev, args...)   netdev_dbg(dev, args)
#पूर्ण_अगर

#अगर SMC_DEBUG_PKTS > 0
अटल व्योम PRINT_PKT(u_अक्षर *buf, पूर्णांक length)
अणु
	पूर्णांक i;
	पूर्णांक reमुख्यder;
	पूर्णांक lines;

	lines = length / 16;
	reमुख्यder = length % 16;

	क्रम (i = 0; i < lines ; i ++) अणु
		पूर्णांक cur;
		prपूर्णांकk(KERN_DEBUG);
		क्रम (cur = 0; cur < 8; cur++) अणु
			u_अक्षर a, b;
			a = *buf++;
			b = *buf++;
			pr_cont("%02x%02x ", a, b);
		पूर्ण
		pr_cont("\n");
	पूर्ण
	prपूर्णांकk(KERN_DEBUG);
	क्रम (i = 0; i < reमुख्यder/2 ; i++) अणु
		u_अक्षर a, b;
		a = *buf++;
		b = *buf++;
		pr_cont("%02x%02x ", a, b);
	पूर्ण
	pr_cont("\n");
पूर्ण
#अन्यथा
#घोषणा PRINT_PKT(x...)  करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर


/* this enables an पूर्णांकerrupt in the पूर्णांकerrupt mask रेजिस्टर */
#घोषणा SMC_ENABLE_INT(lp, x) करो अणु			\
	अचिन्हित पूर्णांक  __mask;				\
	__mask = SMC_GET_INT_EN((lp));			\
	__mask |= (x);					\
	SMC_SET_INT_EN((lp), __mask);			\
पूर्ण जबतक (0)

/* this disables an पूर्णांकerrupt from the पूर्णांकerrupt mask रेजिस्टर */
#घोषणा SMC_DISABLE_INT(lp, x) करो अणु			\
	अचिन्हित पूर्णांक  __mask;				\
	__mask = SMC_GET_INT_EN((lp));			\
	__mask &= ~(x);					\
	SMC_SET_INT_EN((lp), __mask);			\
पूर्ण जबतक (0)

/*
 * this करोes a soft reset on the device
 */
अटल व्योम smc911x_reset(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक reg, समयout=0, resets=1, irq_cfg;
	अचिन्हित दीर्घ flags;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	/*	 Take out of PM setting first */
	अगर ((SMC_GET_PMT_CTRL(lp) & PMT_CTRL_READY_) == 0) अणु
		/* Write to the bytetest will take out of घातerकरोwn */
		SMC_SET_BYTE_TEST(lp, 0);
		समयout=10;
		करो अणु
			udelay(10);
			reg = SMC_GET_PMT_CTRL(lp) & PMT_CTRL_READY_;
		पूर्ण जबतक (--समयout && !reg);
		अगर (समयout == 0) अणु
			PRINTK(dev, "smc911x_reset timeout waiting for PM restore\n");
			वापस;
		पूर्ण
	पूर्ण

	/* Disable all पूर्णांकerrupts */
	spin_lock_irqsave(&lp->lock, flags);
	SMC_SET_INT_EN(lp, 0);
	spin_unlock_irqrestore(&lp->lock, flags);

	जबतक (resets--) अणु
		SMC_SET_HW_CFG(lp, HW_CFG_SRST_);
		समयout=10;
		करो अणु
			udelay(10);
			reg = SMC_GET_HW_CFG(lp);
			/* If chip indicates reset समयout then try again */
			अगर (reg & HW_CFG_SRST_TO_) अणु
				PRINTK(dev, "chip reset timeout, retrying...\n");
				resets++;
				अवरोध;
			पूर्ण
		पूर्ण जबतक (--समयout && (reg & HW_CFG_SRST_));
	पूर्ण
	अगर (समयout == 0) अणु
		PRINTK(dev, "smc911x_reset timeout waiting for reset\n");
		वापस;
	पूर्ण

	/* make sure EEPROM has finished loading beक्रमe setting GPIO_CFG */
	समयout=1000;
	जबतक (--समयout && (SMC_GET_E2P_CMD(lp) & E2P_CMD_EPC_BUSY_))
		udelay(10);

	अगर (समयout == 0)अणु
		PRINTK(dev, "smc911x_reset timeout waiting for EEPROM busy\n");
		वापस;
	पूर्ण

	/* Initialize पूर्णांकerrupts */
	SMC_SET_INT_EN(lp, 0);
	SMC_ACK_INT(lp, -1);

	/* Reset the FIFO level and flow control settings */
	SMC_SET_HW_CFG(lp, (lp->tx_fअगरo_kb & 0xF) << 16);
//TODO: Figure out what appropriate छोड़ो समय is
	SMC_SET_FLOW(lp, FLOW_FCPT_ | FLOW_FCEN_);
	SMC_SET_AFC_CFG(lp, lp->afc_cfg);


	/* Set to LED outमाला_दो */
	SMC_SET_GPIO_CFG(lp, 0x70070000);

	/*
	 * Deनिश्चित IRQ क्रम 1*10us क्रम edge type पूर्णांकerrupts
	 * and drive IRQ pin push-pull
	 */
	irq_cfg = (1 << 24) | INT_CFG_IRQ_EN_ | INT_CFG_IRQ_TYPE_;
#अगर_घोषित SMC_DYNAMIC_BUS_CONFIG
	अगर (lp->cfg.irq_polarity)
		irq_cfg |= INT_CFG_IRQ_POL_;
#पूर्ण_अगर
	SMC_SET_IRQ_CFG(lp, irq_cfg);

	/* clear anything saved */
	अगर (lp->pending_tx_skb != शून्य) अणु
		dev_kमुक्त_skb (lp->pending_tx_skb);
		lp->pending_tx_skb = शून्य;
		dev->stats.tx_errors++;
		dev->stats.tx_पातed_errors++;
	पूर्ण
पूर्ण

/*
 * Enable Interrupts, Receive, and Transmit
 */
अटल व्योम smc911x_enable(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित mask, cfg, cr;
	अचिन्हित दीर्घ flags;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	spin_lock_irqsave(&lp->lock, flags);

	SMC_SET_MAC_ADDR(lp, dev->dev_addr);

	/* Enable TX */
	cfg = SMC_GET_HW_CFG(lp);
	cfg &= HW_CFG_TX_FIF_SZ_ | 0xFFF;
	cfg |= HW_CFG_SF_;
	SMC_SET_HW_CFG(lp, cfg);
	SMC_SET_FIFO_TDA(lp, 0xFF);
	/* Update TX stats on every 64 packets received or every 1 sec */
	SMC_SET_FIFO_TSL(lp, 64);
	SMC_SET_GPT_CFG(lp, GPT_CFG_TIMER_EN_ | 10000);

	SMC_GET_MAC_CR(lp, cr);
	cr |= MAC_CR_TXEN_ | MAC_CR_HBDIS_;
	SMC_SET_MAC_CR(lp, cr);
	SMC_SET_TX_CFG(lp, TX_CFG_TX_ON_);

	/* Add 2 byte padding to start of packets */
	SMC_SET_RX_CFG(lp, (2<<8) & RX_CFG_RXDOFF_);

	/* Turn on receiver and enable RX */
	अगर (cr & MAC_CR_RXEN_)
		DBG(SMC_DEBUG_RX, dev, "Receiver already enabled\n");

	SMC_SET_MAC_CR(lp, cr | MAC_CR_RXEN_);

	/* Interrupt on every received packet */
	SMC_SET_FIFO_RSA(lp, 0x01);
	SMC_SET_FIFO_RSL(lp, 0x00);

	/* now, enable पूर्णांकerrupts */
	mask = INT_EN_TDFA_EN_ | INT_EN_TSFL_EN_ | INT_EN_RSFL_EN_ |
		INT_EN_GPT_INT_EN_ | INT_EN_RXDFH_INT_EN_ | INT_EN_RXE_EN_ |
		INT_EN_PHY_INT_EN_;
	अगर (IS_REV_A(lp->revision))
		mask|=INT_EN_RDFL_EN_;
	अन्यथा अणु
		mask|=INT_EN_RDFO_EN_;
	पूर्ण
	SMC_ENABLE_INT(lp, mask);

	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

/*
 * this माला_दो the device in an inactive state
 */
अटल व्योम smc911x_shutकरोwn(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित cr;
	अचिन्हित दीर्घ flags;

	DBG(SMC_DEBUG_FUNC, dev, "%s: --> %s\n", CARDNAME, __func__);

	/* Disable IRQ's */
	SMC_SET_INT_EN(lp, 0);

	/* Turn of Rx and TX */
	spin_lock_irqsave(&lp->lock, flags);
	SMC_GET_MAC_CR(lp, cr);
	cr &= ~(MAC_CR_TXEN_ | MAC_CR_RXEN_ | MAC_CR_HBDIS_);
	SMC_SET_MAC_CR(lp, cr);
	SMC_SET_TX_CFG(lp, TX_CFG_STOP_TX_);
	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

अटल अंतरभूत व्योम smc911x_drop_pkt(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक fअगरo_count, समयout, reg;

	DBG(SMC_DEBUG_FUNC | SMC_DEBUG_RX, dev, "%s: --> %s\n",
	    CARDNAME, __func__);
	fअगरo_count = SMC_GET_RX_FIFO_INF(lp) & 0xFFFF;
	अगर (fअगरo_count <= 4) अणु
		/* Manually dump the packet data */
		जबतक (fअगरo_count--)
			SMC_GET_RX_FIFO(lp);
	पूर्ण अन्यथा	 अणु
		/* Fast क्रमward through the bad packet */
		SMC_SET_RX_DP_CTRL(lp, RX_DP_CTRL_FFWD_BUSY_);
		समयout=50;
		करो अणु
			udelay(10);
			reg = SMC_GET_RX_DP_CTRL(lp) & RX_DP_CTRL_FFWD_BUSY_;
		पूर्ण जबतक (--समयout && reg);
		अगर (समयout == 0) अणु
			PRINTK(dev, "timeout waiting for RX fast forward\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This is the procedure to handle the receipt of a packet.
 * It should be called after checking क्रम packet presence in
 * the RX status FIFO.	 It must be called with the spin lock
 * alपढ़ोy held.
 */
अटल अंतरभूत व्योम	 smc911x_rcv(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक pkt_len, status;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *data;

	DBG(SMC_DEBUG_FUNC | SMC_DEBUG_RX, dev, "--> %s\n",
	    __func__);
	status = SMC_GET_RX_STS_FIFO(lp);
	DBG(SMC_DEBUG_RX, dev, "Rx pkt len %d status 0x%08x\n",
	    (status & 0x3fff0000) >> 16, status & 0xc000ffff);
	pkt_len = (status & RX_STS_PKT_LEN_) >> 16;
	अगर (status & RX_STS_ES_) अणु
		/* Deal with a bad packet */
		dev->stats.rx_errors++;
		अगर (status & RX_STS_CRC_ERR_)
			dev->stats.rx_crc_errors++;
		अन्यथा अणु
			अगर (status & RX_STS_LEN_ERR_)
				dev->stats.rx_length_errors++;
			अगर (status & RX_STS_MCAST_)
				dev->stats.multicast++;
		पूर्ण
		/* Remove the bad packet data from the RX FIFO */
		smc911x_drop_pkt(dev);
	पूर्ण अन्यथा अणु
		/* Receive a valid packet */
		/* Alloc a buffer with extra room क्रम DMA alignment */
		skb = netdev_alloc_skb(dev, pkt_len+32);
		अगर (unlikely(skb == शून्य)) अणु
			PRINTK(dev, "Low memory, rcvd packet dropped.\n");
			dev->stats.rx_dropped++;
			smc911x_drop_pkt(dev);
			वापस;
		पूर्ण
		/* Align IP header to 32 bits
		 * Note that the device is configured to add a 2
		 * byte padding to the packet start, so we really
		 * want to ग_लिखो to the orignal data poपूर्णांकer */
		data = skb->data;
		skb_reserve(skb, 2);
		skb_put(skb,pkt_len-4);
#अगर_घोषित SMC_USE_DMA
		अणु
		अचिन्हित पूर्णांक fअगरo;
		/* Lower the FIFO threshold अगर possible */
		fअगरo = SMC_GET_FIFO_INT(lp);
		अगर (fअगरo & 0xFF) fअगरo--;
		DBG(SMC_DEBUG_RX, dev, "Setting RX stat FIFO threshold to %d\n",
		    fअगरo & 0xff);
		SMC_SET_FIFO_INT(lp, fअगरo);
		/* Setup RX DMA */
		SMC_SET_RX_CFG(lp, RX_CFG_RX_END_ALGN16_ | ((2<<8) & RX_CFG_RXDOFF_));
		lp->rxdma_active = 1;
		lp->current_rx_skb = skb;
		SMC_PULL_DATA(lp, data, (pkt_len+2+15) & ~15);
		/* Packet processing deferred to DMA RX पूर्णांकerrupt */
		पूर्ण
#अन्यथा
		SMC_SET_RX_CFG(lp, RX_CFG_RX_END_ALGN4_ | ((2<<8) & RX_CFG_RXDOFF_));
		SMC_PULL_DATA(lp, data, pkt_len+2+3);

		DBG(SMC_DEBUG_PKTS, dev, "Received packet\n");
		PRINT_PKT(data, ((pkt_len - 4) <= 64) ? pkt_len - 4 : 64);
		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += pkt_len-4;
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * This is called to actually send a packet to the chip.
 */
अटल व्योम smc911x_hardware_send_pkt(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक cmdA, cmdB, len;
	अचिन्हित अक्षर *buf;

	DBG(SMC_DEBUG_FUNC | SMC_DEBUG_TX, dev, "--> %s\n", __func__);
	BUG_ON(lp->pending_tx_skb == शून्य);

	skb = lp->pending_tx_skb;
	lp->pending_tx_skb = शून्य;

	/* cmdA अणु25:24] data alignment [20:16] start offset [10:0] buffer length */
	/* cmdB अणु31:16] pkt tag [10:0] length */
#अगर_घोषित SMC_USE_DMA
	/* 16 byte buffer alignment mode */
	buf = (अक्षर*)((u32)(skb->data) & ~0xF);
	len = (skb->len + 0xF + ((u32)skb->data & 0xF)) & ~0xF;
	cmdA = (1<<24) | (((u32)skb->data & 0xF)<<16) |
			TX_CMD_A_INT_FIRST_SEG_ | TX_CMD_A_INT_LAST_SEG_ |
			skb->len;
#अन्यथा
	buf = (अक्षर *)((uपूर्णांकptr_t)skb->data & ~0x3);
	len = (skb->len + 3 + ((uपूर्णांकptr_t)skb->data & 3)) & ~0x3;
	cmdA = (((uपूर्णांकptr_t)skb->data & 0x3) << 16) |
			TX_CMD_A_INT_FIRST_SEG_ | TX_CMD_A_INT_LAST_SEG_ |
			skb->len;
#पूर्ण_अगर
	/* tag is packet length so we can use this in stats update later */
	cmdB = (skb->len  << 16) | (skb->len & 0x7FF);

	DBG(SMC_DEBUG_TX, dev, "TX PKT LENGTH 0x%04x (%d) BUF 0x%p CMDA 0x%08x CMDB 0x%08x\n",
	    len, len, buf, cmdA, cmdB);
	SMC_SET_TX_FIFO(lp, cmdA);
	SMC_SET_TX_FIFO(lp, cmdB);

	DBG(SMC_DEBUG_PKTS, dev, "Transmitted packet\n");
	PRINT_PKT(buf, len <= 64 ? len : 64);

	/* Send pkt via PIO or DMA */
#अगर_घोषित SMC_USE_DMA
	lp->current_tx_skb = skb;
	SMC_PUSH_DATA(lp, buf, len);
	/* DMA complete IRQ will मुक्त buffer and set jअगरfies */
#अन्यथा
	SMC_PUSH_DATA(lp, buf, len);
	netअगर_trans_update(dev);
	dev_kमुक्त_skb_irq(skb);
#पूर्ण_अगर
	अगर (!lp->tx_throttle) अणु
		netअगर_wake_queue(dev);
	पूर्ण
	SMC_ENABLE_INT(lp, INT_EN_TDFA_EN_ | INT_EN_TSFL_EN_);
पूर्ण

/*
 * Since I am not sure अगर I will have enough room in the chip's ram
 * to store the packet, I call this routine which either sends it
 * now, or set the card to generates an पूर्णांकerrupt when पढ़ोy
 * क्रम the packet.
 */
अटल netdev_tx_t
smc911x_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक मुक्त;
	अचिन्हित दीर्घ flags;

	DBG(SMC_DEBUG_FUNC | SMC_DEBUG_TX, dev, "--> %s\n",
	    __func__);

	spin_lock_irqsave(&lp->lock, flags);

	BUG_ON(lp->pending_tx_skb != शून्य);

	मुक्त = SMC_GET_TX_FIFO_INF(lp) & TX_FIFO_INF_TDFREE_;
	DBG(SMC_DEBUG_TX, dev, "TX free space %d\n", मुक्त);

	/* Turn off the flow when running out of space in FIFO */
	अगर (मुक्त <= SMC911X_TX_FIFO_LOW_THRESHOLD) अणु
		DBG(SMC_DEBUG_TX, dev, "Disabling data flow due to low FIFO space (%d)\n",
		    मुक्त);
		/* Reenable when at least 1 packet of size MTU present */
		SMC_SET_FIFO_TDA(lp, (SMC911X_TX_FIFO_LOW_THRESHOLD)/64);
		lp->tx_throttle = 1;
		netअगर_stop_queue(dev);
	पूर्ण

	/* Drop packets when we run out of space in TX FIFO
	 * Account क्रम overhead required क्रम:
	 *
	 *	  Tx command words			 8 bytes
	 *	  Start offset				 15 bytes
	 *	  End padding				 15 bytes
	 */
	अगर (unlikely(मुक्त < (skb->len + 8 + 15 + 15))) अणु
		netdev_warn(dev, "No Tx free space %d < %d\n",
			    मुक्त, skb->len);
		lp->pending_tx_skb = शून्य;
		dev->stats.tx_errors++;
		dev->stats.tx_dropped++;
		spin_unlock_irqrestore(&lp->lock, flags);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

#अगर_घोषित SMC_USE_DMA
	अणु
		/* If the DMA is alपढ़ोy running then defer this packet Tx until
		 * the DMA IRQ starts it
		 */
		अगर (lp->txdma_active) अणु
			DBG(SMC_DEBUG_TX | SMC_DEBUG_DMA, dev, "Tx DMA running, deferring packet\n");
			lp->pending_tx_skb = skb;
			netअगर_stop_queue(dev);
			spin_unlock_irqrestore(&lp->lock, flags);
			वापस NETDEV_TX_OK;
		पूर्ण अन्यथा अणु
			DBG(SMC_DEBUG_TX | SMC_DEBUG_DMA, dev, "Activating Tx DMA\n");
			lp->txdma_active = 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	lp->pending_tx_skb = skb;
	smc911x_hardware_send_pkt(dev);
	spin_unlock_irqrestore(&lp->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * This handles a TX status पूर्णांकerrupt, which is only called when:
 * - a TX error occurred, or
 * - TX of a packet completed.
 */
अटल व्योम smc911x_tx(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक tx_status;

	DBG(SMC_DEBUG_FUNC | SMC_DEBUG_TX, dev, "--> %s\n",
	    __func__);

	/* Collect the TX status */
	जबतक (((SMC_GET_TX_FIFO_INF(lp) & TX_FIFO_INF_TSUSED_) >> 16) != 0) अणु
		DBG(SMC_DEBUG_TX, dev, "Tx stat FIFO used 0x%04x\n",
		    (SMC_GET_TX_FIFO_INF(lp) & TX_FIFO_INF_TSUSED_) >> 16);
		tx_status = SMC_GET_TX_STS_FIFO(lp);
		dev->stats.tx_packets++;
		dev->stats.tx_bytes+=tx_status>>16;
		DBG(SMC_DEBUG_TX, dev, "Tx FIFO tag 0x%04x status 0x%04x\n",
		    (tx_status & 0xffff0000) >> 16,
		    tx_status & 0x0000ffff);
		/* count Tx errors, but ignore lost carrier errors when in
		 * full-duplex mode */
		अगर ((tx_status & TX_STS_ES_) && !(lp->ctl_rfduplx &&
		    !(tx_status & 0x00000306))) अणु
			dev->stats.tx_errors++;
		पूर्ण
		अगर (tx_status & TX_STS_MANY_COLL_) अणु
			dev->stats.collisions+=16;
			dev->stats.tx_पातed_errors++;
		पूर्ण अन्यथा अणु
			dev->stats.collisions+=(tx_status & TX_STS_COLL_CNT_) >> 3;
		पूर्ण
		/* carrier error only has meaning क्रम half-duplex communication */
		अगर ((tx_status & (TX_STS_LOC_ | TX_STS_NO_CARR_)) &&
		    !lp->ctl_rfduplx) अणु
			dev->stats.tx_carrier_errors++;
		पूर्ण
		अगर (tx_status & TX_STS_LATE_COLL_) अणु
			dev->stats.collisions++;
			dev->stats.tx_पातed_errors++;
		पूर्ण
	पूर्ण
पूर्ण


/*---PHY CONTROL AND CONFIGURATION-----------------------------------------*/
/*
 * Reads a रेजिस्टर from the MII Management serial पूर्णांकerface
 */

अटल पूर्णांक smc911x_phy_पढ़ो(काष्ठा net_device *dev, पूर्णांक phyaddr, पूर्णांक phyreg)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक phydata;

	SMC_GET_MII(lp, phyreg, phyaddr, phydata);

	DBG(SMC_DEBUG_MISC, dev, "%s: phyaddr=0x%x, phyreg=0x%02x, phydata=0x%04x\n",
	    __func__, phyaddr, phyreg, phydata);
	वापस phydata;
पूर्ण


/*
 * Writes a रेजिस्टर to the MII Management serial पूर्णांकerface
 */
अटल व्योम smc911x_phy_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phyaddr, पूर्णांक phyreg,
			पूर्णांक phydata)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);

	DBG(SMC_DEBUG_MISC, dev, "%s: phyaddr=0x%x, phyreg=0x%x, phydata=0x%x\n",
	    __func__, phyaddr, phyreg, phydata);

	SMC_SET_MII(lp, phyreg, phyaddr, phydata);
पूर्ण

/*
 * Finds and reports the PHY address (115 and 117 have बाह्यal
 * PHY पूर्णांकerface 118 has पूर्णांकernal only
 */
अटल व्योम smc911x_phy_detect(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक phyaddr;
	अचिन्हित पूर्णांक cfg, id1, id2;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	lp->phy_type = 0;

	/*
	 * Scan all 32 PHY addresses अगर necessary, starting at
	 * PHY#1 to PHY#31, and then PHY#0 last.
	 */
	चयन(lp->version) अणु
		हाल CHIP_9115:
		हाल CHIP_9117:
		हाल CHIP_9215:
		हाल CHIP_9217:
			cfg = SMC_GET_HW_CFG(lp);
			अगर (cfg & HW_CFG_EXT_PHY_DET_) अणु
				cfg &= ~HW_CFG_PHY_CLK_SEL_;
				cfg |= HW_CFG_PHY_CLK_SEL_CLK_DIS_;
				SMC_SET_HW_CFG(lp, cfg);
				udelay(10); /* Wait क्रम घड़ीs to stop */

				cfg |= HW_CFG_EXT_PHY_EN_;
				SMC_SET_HW_CFG(lp, cfg);
				udelay(10); /* Wait क्रम घड़ीs to stop */

				cfg &= ~HW_CFG_PHY_CLK_SEL_;
				cfg |= HW_CFG_PHY_CLK_SEL_EXT_PHY_;
				SMC_SET_HW_CFG(lp, cfg);
				udelay(10); /* Wait क्रम घड़ीs to stop */

				cfg |= HW_CFG_SMI_SEL_;
				SMC_SET_HW_CFG(lp, cfg);

				क्रम (phyaddr = 1; phyaddr < 32; ++phyaddr) अणु

					/* Read the PHY identअगरiers */
					SMC_GET_PHY_ID1(lp, phyaddr & 31, id1);
					SMC_GET_PHY_ID2(lp, phyaddr & 31, id2);

					/* Make sure it is a valid identअगरier */
					अगर (id1 != 0x0000 && id1 != 0xffff &&
					    id1 != 0x8000 && id2 != 0x0000 &&
					    id2 != 0xffff && id2 != 0x8000) अणु
						/* Save the PHY's address */
						lp->mii.phy_id = phyaddr & 31;
						lp->phy_type = id1 << 16 | id2;
						अवरोध;
					पूर्ण
				पूर्ण
				अगर (phyaddr < 32)
					/* Found an बाह्यal PHY */
					अवरोध;
			पूर्ण
			fallthrough;
		शेष:
			/* Internal media only */
			SMC_GET_PHY_ID1(lp, 1, id1);
			SMC_GET_PHY_ID2(lp, 1, id2);
			/* Save the PHY's address */
			lp->mii.phy_id = 1;
			lp->phy_type = id1 << 16 | id2;
	पूर्ण

	DBG(SMC_DEBUG_MISC, dev, "phy_id1=0x%x, phy_id2=0x%x phyaddr=0x%x\n",
	    id1, id2, lp->mii.phy_id);
पूर्ण

/*
 * Sets the PHY to a configuration as determined by the user.
 * Called with spin_lock held.
 */
अटल पूर्णांक smc911x_phy_fixed(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक phyaddr = lp->mii.phy_id;
	पूर्णांक bmcr;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	/* Enter Link Disable state */
	SMC_GET_PHY_BMCR(lp, phyaddr, bmcr);
	bmcr |= BMCR_PDOWN;
	SMC_SET_PHY_BMCR(lp, phyaddr, bmcr);

	/*
	 * Set our fixed capabilities
	 * Disable स्वतः-negotiation
	 */
	bmcr &= ~BMCR_ANENABLE;
	अगर (lp->ctl_rfduplx)
		bmcr |= BMCR_FULLDPLX;

	अगर (lp->ctl_rspeed == 100)
		bmcr |= BMCR_SPEED100;

	/* Write our capabilities to the phy control रेजिस्टर */
	SMC_SET_PHY_BMCR(lp, phyaddr, bmcr);

	/* Re-Configure the Receive/Phy Control रेजिस्टर */
	bmcr &= ~BMCR_PDOWN;
	SMC_SET_PHY_BMCR(lp, phyaddr, bmcr);

	वापस 1;
पूर्ण

/**
 * smc911x_phy_reset - reset the phy
 * @dev: net device
 * @phy: phy address
 *
 * Issue a software reset क्रम the specअगरied PHY and
 * रुको up to 100ms क्रम the reset to complete.	 We should
 * not access the PHY क्रम 50ms after issuing the reset.
 *
 * The समय to रुको appears to be dependent on the PHY.
 *
 */
अटल पूर्णांक smc911x_phy_reset(काष्ठा net_device *dev, पूर्णांक phy)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक समयout;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक reg;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s()\n", __func__);

	spin_lock_irqsave(&lp->lock, flags);
	reg = SMC_GET_PMT_CTRL(lp);
	reg &= ~0xfffff030;
	reg |= PMT_CTRL_PHY_RST_;
	SMC_SET_PMT_CTRL(lp, reg);
	spin_unlock_irqrestore(&lp->lock, flags);
	क्रम (समयout = 2; समयout; समयout--) अणु
		msleep(50);
		spin_lock_irqsave(&lp->lock, flags);
		reg = SMC_GET_PMT_CTRL(lp);
		spin_unlock_irqrestore(&lp->lock, flags);
		अगर (!(reg & PMT_CTRL_PHY_RST_)) अणु
			/* extra delay required because the phy may
			 * not be completed with its reset
			 * when PHY_BCR_RESET_ is cleared. 256us
			 * should suffice, but use 500us to be safe
			 */
			udelay(500);
		अवरोध;
		पूर्ण
	पूर्ण

	वापस reg & PMT_CTRL_PHY_RST_;
पूर्ण

/**
 * smc911x_phy_घातerकरोwn - घातerकरोwn phy
 * @dev: net device
 * @phy: phy address
 *
 * Power करोwn the specअगरied PHY
 */
अटल व्योम smc911x_phy_घातerकरोwn(काष्ठा net_device *dev, पूर्णांक phy)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक bmcr;

	/* Enter Link Disable state */
	SMC_GET_PHY_BMCR(lp, phy, bmcr);
	bmcr |= BMCR_PDOWN;
	SMC_SET_PHY_BMCR(lp, phy, bmcr);
पूर्ण

/**
 * smc911x_phy_check_media - check the media status and adjust BMCR
 * @dev: net device
 * @init: set true क्रम initialisation
 *
 * Select duplex mode depending on negotiation state.	This
 * also updates our carrier state.
 */
अटल व्योम smc911x_phy_check_media(काष्ठा net_device *dev, पूर्णांक init)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक phyaddr = lp->mii.phy_id;
	अचिन्हित पूर्णांक bmcr, cr;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	अगर (mii_check_media(&lp->mii, netअगर_msg_link(lp), init)) अणु
		/* duplex state has changed */
		SMC_GET_PHY_BMCR(lp, phyaddr, bmcr);
		SMC_GET_MAC_CR(lp, cr);
		अगर (lp->mii.full_duplex) अणु
			DBG(SMC_DEBUG_MISC, dev, "Configuring for full-duplex mode\n");
			bmcr |= BMCR_FULLDPLX;
			cr |= MAC_CR_RCVOWN_;
		पूर्ण अन्यथा अणु
			DBG(SMC_DEBUG_MISC, dev, "Configuring for half-duplex mode\n");
			bmcr &= ~BMCR_FULLDPLX;
			cr &= ~MAC_CR_RCVOWN_;
		पूर्ण
		SMC_SET_PHY_BMCR(lp, phyaddr, bmcr);
		SMC_SET_MAC_CR(lp, cr);
	पूर्ण
पूर्ण

/*
 * Configures the specअगरied PHY through the MII management पूर्णांकerface
 * using Autonegotiation.
 * Calls smc911x_phy_fixed() अगर the user has requested a certain config.
 * If RPC ANEG bit is set, the media selection is dependent purely on
 * the selection by the MII (either in the MII BMCR reg or the result
 * of स्वतःnegotiation.)  If the RPC ANEG bit is cleared, the selection
 * is controlled by the RPC SPEED and RPC DPLX bits.
 */
अटल व्योम smc911x_phy_configure(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc911x_local *lp = container_of(work, काष्ठा smc911x_local,
						phy_configure);
	काष्ठा net_device *dev = lp->netdev;
	पूर्णांक phyaddr = lp->mii.phy_id;
	पूर्णांक my_phy_caps; /* My PHY capabilities */
	पूर्णांक my_ad_caps; /* My Advertised capabilities */
	पूर्णांक status __always_unused;
	अचिन्हित दीर्घ flags;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s()\n", __func__);

	/*
	 * We should not be called अगर phy_type is zero.
	 */
	अगर (lp->phy_type == 0)
		वापस;

	अगर (smc911x_phy_reset(dev, phyaddr)) अणु
		netdev_info(dev, "PHY reset timed out\n");
		वापस;
	पूर्ण
	spin_lock_irqsave(&lp->lock, flags);

	/*
	 * Enable PHY Interrupts (क्रम रेजिस्टर 18)
	 * Interrupts listed here are enabled
	 */
	SMC_SET_PHY_INT_MASK(lp, phyaddr, PHY_INT_MASK_ENERGY_ON_ |
		 PHY_INT_MASK_ANEG_COMP_ | PHY_INT_MASK_REMOTE_FAULT_ |
		 PHY_INT_MASK_LINK_DOWN_);

	/* If the user requested no स्वतः neg, then go set his request */
	अगर (lp->mii.क्रमce_media) अणु
		smc911x_phy_fixed(dev);
		जाओ smc911x_phy_configure_निकास;
	पूर्ण

	/* Copy our capabilities from MII_BMSR to MII_ADVERTISE */
	SMC_GET_PHY_BMSR(lp, phyaddr, my_phy_caps);
	अगर (!(my_phy_caps & BMSR_ANEGCAPABLE)) अणु
		netdev_info(dev, "Auto negotiation NOT supported\n");
		smc911x_phy_fixed(dev);
		जाओ smc911x_phy_configure_निकास;
	पूर्ण

	/* CSMA capable w/ both छोड़ोs */
	my_ad_caps = ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;

	अगर (my_phy_caps & BMSR_100BASE4)
		my_ad_caps |= ADVERTISE_100BASE4;
	अगर (my_phy_caps & BMSR_100FULL)
		my_ad_caps |= ADVERTISE_100FULL;
	अगर (my_phy_caps & BMSR_100HALF)
		my_ad_caps |= ADVERTISE_100HALF;
	अगर (my_phy_caps & BMSR_10FULL)
		my_ad_caps |= ADVERTISE_10FULL;
	अगर (my_phy_caps & BMSR_10HALF)
		my_ad_caps |= ADVERTISE_10HALF;

	/* Disable capabilities not selected by our user */
	अगर (lp->ctl_rspeed != 100)
		my_ad_caps &= ~(ADVERTISE_100BASE4|ADVERTISE_100FULL|ADVERTISE_100HALF);

	अगर (!lp->ctl_rfduplx)
		my_ad_caps &= ~(ADVERTISE_100FULL|ADVERTISE_10FULL);

	/* Update our Auto-Neg Advertisement Register */
	SMC_SET_PHY_MII_ADV(lp, phyaddr, my_ad_caps);
	lp->mii.advertising = my_ad_caps;

	/*
	 * Read the रेजिस्टर back.	 Without this, it appears that when
	 * स्वतः-negotiation is restarted, someबार it isn't पढ़ोy and
	 * the link करोes not come up.
	 */
	udelay(10);
	SMC_GET_PHY_MII_ADV(lp, phyaddr, status);

	DBG(SMC_DEBUG_MISC, dev, "phy caps=0x%04x\n", my_phy_caps);
	DBG(SMC_DEBUG_MISC, dev, "phy advertised caps=0x%04x\n", my_ad_caps);

	/* Restart स्वतः-negotiation process in order to advertise my caps */
	SMC_SET_PHY_BMCR(lp, phyaddr, BMCR_ANENABLE | BMCR_ANRESTART);

	smc911x_phy_check_media(dev, 1);

smc911x_phy_configure_निकास:
	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण

/*
 * smc911x_phy_पूर्णांकerrupt
 *
 * Purpose:  Handle पूर्णांकerrupts relating to PHY रेजिस्टर 18. This is
 *	 called from the "hard" पूर्णांकerrupt handler under our निजी spinlock.
 */
अटल व्योम smc911x_phy_पूर्णांकerrupt(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक phyaddr = lp->mii.phy_id;
	पूर्णांक status __always_unused;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	अगर (lp->phy_type == 0)
		वापस;

	smc911x_phy_check_media(dev, 0);
	/* पढ़ो to clear status bits */
	SMC_GET_PHY_INT_SRC(lp, phyaddr,status);
	DBG(SMC_DEBUG_MISC, dev, "PHY interrupt status 0x%04x\n",
	    status & 0xffff);
	DBG(SMC_DEBUG_MISC, dev, "AFC_CFG 0x%08x\n",
	    SMC_GET_AFC_CFG(lp));
पूर्ण

/*--- END PHY CONTROL AND CONFIGURATION-------------------------------------*/

/*
 * This is the मुख्य routine of the driver, to handle the device when
 * it needs some attention.
 */
अटल irqवापस_t smc911x_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक status, mask, समयout;
	अचिन्हित पूर्णांक rx_overrun=0, cr, pkts;
	अचिन्हित दीर्घ flags;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	spin_lock_irqsave(&lp->lock, flags);

	/* Spurious पूर्णांकerrupt check */
	अगर ((SMC_GET_IRQ_CFG(lp) & (INT_CFG_IRQ_INT_ | INT_CFG_IRQ_EN_)) !=
		(INT_CFG_IRQ_INT_ | INT_CFG_IRQ_EN_)) अणु
		spin_unlock_irqrestore(&lp->lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	mask = SMC_GET_INT_EN(lp);
	SMC_SET_INT_EN(lp, 0);

	/* set a समयout value, so I करोn't stay here क्रमever */
	समयout = 8;


	करो अणु
		status = SMC_GET_INT(lp);

		DBG(SMC_DEBUG_MISC, dev, "INT 0x%08x MASK 0x%08x OUTSIDE MASK 0x%08x\n",
		    status, mask, status & ~mask);

		status &= mask;
		अगर (!status)
			अवरोध;

		/* Handle SW पूर्णांकerrupt condition */
		अगर (status & INT_STS_SW_INT_) अणु
			SMC_ACK_INT(lp, INT_STS_SW_INT_);
			mask &= ~INT_EN_SW_INT_EN_;
		पूर्ण
		/* Handle various error conditions */
		अगर (status & INT_STS_RXE_) अणु
			SMC_ACK_INT(lp, INT_STS_RXE_);
			dev->stats.rx_errors++;
		पूर्ण
		अगर (status & INT_STS_RXDFH_INT_) अणु
			SMC_ACK_INT(lp, INT_STS_RXDFH_INT_);
			dev->stats.rx_dropped+=SMC_GET_RX_DROP(lp);
		 पूर्ण
		/* Unकरोcumented पूर्णांकerrupt-what is the right thing to करो here? */
		अगर (status & INT_STS_RXDF_INT_) अणु
			SMC_ACK_INT(lp, INT_STS_RXDF_INT_);
		पूर्ण

		/* Rx Data FIFO exceeds set level */
		अगर (status & INT_STS_RDFL_) अणु
			अगर (IS_REV_A(lp->revision)) अणु
				rx_overrun=1;
				SMC_GET_MAC_CR(lp, cr);
				cr &= ~MAC_CR_RXEN_;
				SMC_SET_MAC_CR(lp, cr);
				DBG(SMC_DEBUG_RX, dev, "RX overrun\n");
				dev->stats.rx_errors++;
				dev->stats.rx_fअगरo_errors++;
			पूर्ण
			SMC_ACK_INT(lp, INT_STS_RDFL_);
		पूर्ण
		अगर (status & INT_STS_RDFO_) अणु
			अगर (!IS_REV_A(lp->revision)) अणु
				SMC_GET_MAC_CR(lp, cr);
				cr &= ~MAC_CR_RXEN_;
				SMC_SET_MAC_CR(lp, cr);
				rx_overrun=1;
				DBG(SMC_DEBUG_RX, dev, "RX overrun\n");
				dev->stats.rx_errors++;
				dev->stats.rx_fअगरo_errors++;
			पूर्ण
			SMC_ACK_INT(lp, INT_STS_RDFO_);
		पूर्ण
		/* Handle receive condition */
		अगर ((status & INT_STS_RSFL_) || rx_overrun) अणु
			अचिन्हित पूर्णांक fअगरo;
			DBG(SMC_DEBUG_RX, dev, "RX irq\n");
			fअगरo = SMC_GET_RX_FIFO_INF(lp);
			pkts = (fअगरo & RX_FIFO_INF_RXSUSED_) >> 16;
			DBG(SMC_DEBUG_RX, dev, "Rx FIFO pkts %d, bytes %d\n",
			    pkts, fअगरo & 0xFFFF);
			अगर (pkts != 0) अणु
#अगर_घोषित SMC_USE_DMA
				अचिन्हित पूर्णांक fअगरo;
				अगर (lp->rxdma_active)अणु
					DBG(SMC_DEBUG_RX | SMC_DEBUG_DMA, dev,
					    "RX DMA active\n");
					/* The DMA is alपढ़ोy running so up the IRQ threshold */
					fअगरo = SMC_GET_FIFO_INT(lp) & ~0xFF;
					fअगरo |= pkts & 0xFF;
					DBG(SMC_DEBUG_RX, dev,
					    "Setting RX stat FIFO threshold to %d\n",
					    fअगरo & 0xff);
					SMC_SET_FIFO_INT(lp, fअगरo);
				पूर्ण अन्यथा
#पूर्ण_अगर
				smc911x_rcv(dev);
			पूर्ण
			SMC_ACK_INT(lp, INT_STS_RSFL_);
		पूर्ण
		/* Handle transmit FIFO available */
		अगर (status & INT_STS_TDFA_) अणु
			DBG(SMC_DEBUG_TX, dev, "TX data FIFO space available irq\n");
			SMC_SET_FIFO_TDA(lp, 0xFF);
			lp->tx_throttle = 0;
#अगर_घोषित SMC_USE_DMA
			अगर (!lp->txdma_active)
#पूर्ण_अगर
				netअगर_wake_queue(dev);
			SMC_ACK_INT(lp, INT_STS_TDFA_);
		पूर्ण
		/* Handle transmit करोne condition */
#अगर 1
		अगर (status & (INT_STS_TSFL_ | INT_STS_GPT_INT_)) अणु
			DBG(SMC_DEBUG_TX | SMC_DEBUG_MISC, dev,
			    "Tx stat FIFO limit (%d) /GPT irq\n",
			    (SMC_GET_FIFO_INT(lp) & 0x00ff0000) >> 16);
			smc911x_tx(dev);
			SMC_SET_GPT_CFG(lp, GPT_CFG_TIMER_EN_ | 10000);
			SMC_ACK_INT(lp, INT_STS_TSFL_);
			SMC_ACK_INT(lp, INT_STS_TSFL_ | INT_STS_GPT_INT_);
		पूर्ण
#अन्यथा
		अगर (status & INT_STS_TSFL_) अणु
			DBG(SMC_DEBUG_TX, dev, "TX status FIFO limit (%d) irq\n", ?);
			smc911x_tx(dev);
			SMC_ACK_INT(lp, INT_STS_TSFL_);
		पूर्ण

		अगर (status & INT_STS_GPT_INT_) अणु
			DBG(SMC_DEBUG_RX, dev, "IRQ_CFG 0x%08x FIFO_INT 0x%08x RX_CFG 0x%08x\n",
			    SMC_GET_IRQ_CFG(lp),
			    SMC_GET_FIFO_INT(lp),
			    SMC_GET_RX_CFG(lp));
			DBG(SMC_DEBUG_RX, dev, "Rx Stat FIFO Used 0x%02x Data FIFO Used 0x%04x Stat FIFO 0x%08x\n",
			    (SMC_GET_RX_FIFO_INF(lp) & 0x00ff0000) >> 16,
			    SMC_GET_RX_FIFO_INF(lp) & 0xffff,
			    SMC_GET_RX_STS_FIFO_PEEK(lp));
			SMC_SET_GPT_CFG(lp, GPT_CFG_TIMER_EN_ | 10000);
			SMC_ACK_INT(lp, INT_STS_GPT_INT_);
		पूर्ण
#पूर्ण_अगर

		/* Handle PHY पूर्णांकerrupt condition */
		अगर (status & INT_STS_PHY_INT_) अणु
			DBG(SMC_DEBUG_MISC, dev, "PHY irq\n");
			smc911x_phy_पूर्णांकerrupt(dev);
			SMC_ACK_INT(lp, INT_STS_PHY_INT_);
		पूर्ण
	पूर्ण जबतक (--समयout);

	/* restore mask state */
	SMC_SET_INT_EN(lp, mask);

	DBG(SMC_DEBUG_MISC, dev, "Interrupt done (%d loops)\n",
	    8-समयout);

	spin_unlock_irqrestore(&lp->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित SMC_USE_DMA
अटल व्योम
smc911x_tx_dma_irq(व्योम *data)
अणु
	काष्ठा smc911x_local *lp = data;
	काष्ठा net_device *dev = lp->netdev;
	काष्ठा sk_buff *skb = lp->current_tx_skb;
	अचिन्हित दीर्घ flags;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	DBG(SMC_DEBUG_TX | SMC_DEBUG_DMA, dev, "TX DMA irq handler\n");
	BUG_ON(skb == शून्य);
	dma_unmap_single(lp->dev, tx_dmabuf, tx_dmalen, DMA_TO_DEVICE);
	netअगर_trans_update(dev);
	dev_kमुक्त_skb_irq(skb);
	lp->current_tx_skb = शून्य;
	अगर (lp->pending_tx_skb != शून्य)
		smc911x_hardware_send_pkt(dev);
	अन्यथा अणु
		DBG(SMC_DEBUG_TX | SMC_DEBUG_DMA, dev,
		    "No pending Tx packets. DMA disabled\n");
		spin_lock_irqsave(&lp->lock, flags);
		lp->txdma_active = 0;
		अगर (!lp->tx_throttle) अणु
			netअगर_wake_queue(dev);
		पूर्ण
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण

	DBG(SMC_DEBUG_TX | SMC_DEBUG_DMA, dev,
	    "TX DMA irq completed\n");
पूर्ण
अटल व्योम
smc911x_rx_dma_irq(व्योम *data)
अणु
	काष्ठा smc911x_local *lp = data;
	काष्ठा net_device *dev = lp->netdev;
	काष्ठा sk_buff *skb = lp->current_rx_skb;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pkts;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);
	DBG(SMC_DEBUG_RX | SMC_DEBUG_DMA, dev, "RX DMA irq handler\n");
	dma_unmap_single(lp->dev, rx_dmabuf, rx_dmalen, DMA_FROM_DEVICE);
	BUG_ON(skb == शून्य);
	lp->current_rx_skb = शून्य;
	PRINT_PKT(skb->data, skb->len);
	skb->protocol = eth_type_trans(skb, dev);
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += skb->len;
	netअगर_rx(skb);

	spin_lock_irqsave(&lp->lock, flags);
	pkts = (SMC_GET_RX_FIFO_INF(lp) & RX_FIFO_INF_RXSUSED_) >> 16;
	अगर (pkts != 0) अणु
		smc911x_rcv(dev);
	पूर्णअन्यथा अणु
		lp->rxdma_active = 0;
	पूर्ण
	spin_unlock_irqrestore(&lp->lock, flags);
	DBG(SMC_DEBUG_RX | SMC_DEBUG_DMA, dev,
	    "RX DMA irq completed. DMA RX FIFO PKTS %d\n",
	    pkts);
पूर्ण
#पूर्ण_अगर	 /* SMC_USE_DMA */

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling receive - used by netconsole and other diagnostic tools
 * to allow network i/o with पूर्णांकerrupts disabled.
 */
अटल व्योम smc911x_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	smc911x_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/* Our watchकरोg समयd out. Called by the networking layer */
अटल व्योम smc911x_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक status, mask;
	अचिन्हित दीर्घ flags;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	spin_lock_irqsave(&lp->lock, flags);
	status = SMC_GET_INT(lp);
	mask = SMC_GET_INT_EN(lp);
	spin_unlock_irqrestore(&lp->lock, flags);
	DBG(SMC_DEBUG_MISC, dev, "INT 0x%02x MASK 0x%02x\n",
	    status, mask);

	/* Dump the current TX FIFO contents and restart */
	mask = SMC_GET_TX_CFG(lp);
	SMC_SET_TX_CFG(lp, mask | TX_CFG_TXS_DUMP_ | TX_CFG_TXD_DUMP_);
	/*
	 * Reconfiguring the PHY करोesn't seem like a bad idea here, but
	 * smc911x_phy_configure() calls msleep() which calls schedule_समयout()
	 * which calls schedule().	 Hence we use a work queue.
	 */
	अगर (lp->phy_type != 0)
		schedule_work(&lp->phy_configure);

	/* We can accept TX packets again */
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);
पूर्ण

/*
 * This routine will, depending on the values passed to it,
 * either make it accept multicast packets, go पूर्णांकo
 * promiscuous mode (क्रम TCPDUMP and cousins) or accept
 * a select set of multicast packets
 */
अटल व्योम smc911x_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक multicast_table[2];
	अचिन्हित पूर्णांक mcr, update_multicast = 0;
	अचिन्हित दीर्घ flags;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	spin_lock_irqsave(&lp->lock, flags);
	SMC_GET_MAC_CR(lp, mcr);
	spin_unlock_irqrestore(&lp->lock, flags);

	अगर (dev->flags & IFF_PROMISC) अणु

		DBG(SMC_DEBUG_MISC, dev, "RCR_PRMS\n");
		mcr |= MAC_CR_PRMS_;
	पूर्ण
	/*
	 * Here, I am setting this to accept all multicast packets.
	 * I करोn't need to zero the multicast table, because the flag is
	 * checked beक्रमe the table is
	 */
	अन्यथा अगर (dev->flags & IFF_ALLMULTI || netdev_mc_count(dev) > 16) अणु
		DBG(SMC_DEBUG_MISC, dev, "RCR_ALMUL\n");
		mcr |= MAC_CR_MCPAS_;
	पूर्ण

	/*
	 * This sets the पूर्णांकernal hardware table to filter out unwanted
	 * multicast packets beक्रमe they take up memory.
	 *
	 * The SMC chip uses a hash table where the high 6 bits of the CRC of
	 * address are the offset पूर्णांकo the table.	If that bit is 1, then the
	 * multicast packet is accepted.  Otherwise, it's dropped silently.
	 *
	 * To use the 6 bits as an offset पूर्णांकo the table, the high 1 bit is
	 * the number of the 32 bit रेजिस्टर, जबतक the low 5 bits are the bit
	 * within that रेजिस्टर.
	 */
	अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;

		/* Set the Hash perfec mode */
		mcr |= MAC_CR_HPFILT_;

		/* start with a table of all zeros: reject all */
		स_रखो(multicast_table, 0, माप(multicast_table));

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			u32 position;

			/* upper 6 bits are used as hash index */
			position = ether_crc(ETH_ALEN, ha->addr)>>26;

			multicast_table[position>>5] |= 1 << (position&0x1f);
		पूर्ण

		/* be sure I get rid of flags I might have set */
		mcr &= ~(MAC_CR_PRMS_ | MAC_CR_MCPAS_);

		/* now, the table can be loaded पूर्णांकo the chipset */
		update_multicast = 1;
	पूर्ण अन्यथा	 अणु
		DBG(SMC_DEBUG_MISC, dev, "~(MAC_CR_PRMS_|MAC_CR_MCPAS_)\n");
		mcr &= ~(MAC_CR_PRMS_ | MAC_CR_MCPAS_);

		/*
		 * since I'm disabling all multicast entirely, I need to
		 * clear the multicast list
		 */
		स_रखो(multicast_table, 0, माप(multicast_table));
		update_multicast = 1;
	पूर्ण

	spin_lock_irqsave(&lp->lock, flags);
	SMC_SET_MAC_CR(lp, mcr);
	अगर (update_multicast) अणु
		DBG(SMC_DEBUG_MISC, dev,
		    "update mcast hash table 0x%08x 0x%08x\n",
		    multicast_table[0], multicast_table[1]);
		SMC_SET_HASHL(lp, multicast_table[0]);
		SMC_SET_HASHH(lp, multicast_table[1]);
	पूर्ण
	spin_unlock_irqrestore(&lp->lock, flags);
पूर्ण


/*
 * Open and Initialize the board
 *
 * Set up everything, reset the card, etc..
 */
अटल पूर्णांक
smc911x_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	/* reset the hardware */
	smc911x_reset(dev);

	/* Configure the PHY, initialize the link state */
	smc911x_phy_configure(&lp->phy_configure);

	/* Turn on Tx + Rx */
	smc911x_enable(dev);

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

/*
 * smc911x_बंद
 *
 * this makes the board clean up everything that it can
 * and not talk to the outside world.	 Caused by
 * an 'ifconfig ethX down'
 */
अटल पूर्णांक smc911x_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	netअगर_stop_queue(dev);
	netअगर_carrier_off(dev);

	/* clear everything */
	smc911x_shutकरोwn(dev);

	अगर (lp->phy_type != 0) अणु
		/* We need to ensure that no calls to
		 * smc911x_phy_configure are pending.
		 */
		cancel_work_sync(&lp->phy_configure);
		smc911x_phy_घातerकरोwn(dev, lp->mii.phy_id);
	पूर्ण

	अगर (lp->pending_tx_skb) अणु
		dev_kमुक्त_skb(lp->pending_tx_skb);
		lp->pending_tx_skb = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Ethtool support
 */
अटल पूर्णांक
smc911x_ethtool_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक status;
	अचिन्हित दीर्घ flags;
	u32 supported;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	अगर (lp->phy_type != 0) अणु
		spin_lock_irqsave(&lp->lock, flags);
		mii_ethtool_get_link_ksettings(&lp->mii, cmd);
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण अन्यथा अणु
		supported = SUPPORTED_10baseT_Half |
				SUPPORTED_10baseT_Full |
				SUPPORTED_TP | SUPPORTED_AUI;

		अगर (lp->ctl_rspeed == 10)
			cmd->base.speed = SPEED_10;
		अन्यथा अगर (lp->ctl_rspeed == 100)
			cmd->base.speed = SPEED_100;

		cmd->base.स्वतःneg = AUTONEG_DISABLE;
		cmd->base.port = 0;
		SMC_GET_PHY_SPECIAL(lp, lp->mii.phy_id, status);
		cmd->base.duplex =
			(status & (PHY_SPECIAL_SPD_10FULL_ | PHY_SPECIAL_SPD_100FULL_)) ?
				DUPLEX_FULL : DUPLEX_HALF;

		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported, supported);

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
smc911x_ethtool_set_link_ksettings(काष्ठा net_device *dev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (lp->phy_type != 0) अणु
		spin_lock_irqsave(&lp->lock, flags);
		ret = mii_ethtool_set_link_ksettings(&lp->mii, cmd);
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण अन्यथा अणु
		अगर (cmd->base.स्वतःneg != AUTONEG_DISABLE ||
		    cmd->base.speed != SPEED_10 ||
		    (cmd->base.duplex != DUPLEX_HALF &&
		     cmd->base.duplex != DUPLEX_FULL) ||
		    (cmd->base.port != PORT_TP &&
		     cmd->base.port != PORT_AUI))
			वापस -EINVAL;

		lp->ctl_rfduplx = cmd->base.duplex == DUPLEX_FULL;

		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
smc911x_ethtool_getdrvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, CARDNAME, माप(info->driver));
	strlcpy(info->version, version, माप(info->version));
	strlcpy(info->bus_info, dev_name(dev->dev.parent),
		माप(info->bus_info));
पूर्ण

अटल पूर्णांक smc911x_ethtool_nwayreset(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक ret = -EINVAL;
	अचिन्हित दीर्घ flags;

	अगर (lp->phy_type != 0) अणु
		spin_lock_irqsave(&lp->lock, flags);
		ret = mii_nway_restart(&lp->mii);
		spin_unlock_irqrestore(&lp->lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 smc911x_ethtool_geपंचांगsglevel(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	वापस lp->msg_enable;
पूर्ण

अटल व्योम smc911x_ethtool_seपंचांगsglevel(काष्ठा net_device *dev, u32 level)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	lp->msg_enable = level;
पूर्ण

अटल पूर्णांक smc911x_ethtool_getregslen(काष्ठा net_device *dev)
अणु
	/* System regs + MAC regs + PHY regs */
	वापस (((E2P_CMD - ID_REV)/4 + 1) +
			(WUCSR - MAC_CR)+1 + 32) * माप(u32);
पूर्ण

अटल व्योम smc911x_ethtool_getregs(काष्ठा net_device *dev,
										 काष्ठा ethtool_regs* regs, व्योम *buf)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	u32 reg,i,j=0;
	u32 *data = (u32*)buf;

	regs->version = lp->version;
	क्रम(i=ID_REV;i<=E2P_CMD;i+=4) अणु
		data[j++] = SMC_inl(lp, i);
	पूर्ण
	क्रम(i=MAC_CR;i<=WUCSR;i++) अणु
		spin_lock_irqsave(&lp->lock, flags);
		SMC_GET_MAC_CSR(lp, i, reg);
		spin_unlock_irqrestore(&lp->lock, flags);
		data[j++] = reg;
	पूर्ण
	क्रम(i=0;i<=31;i++) अणु
		spin_lock_irqsave(&lp->lock, flags);
		SMC_GET_MII(lp, i, lp->mii.phy_id, reg);
		spin_unlock_irqrestore(&lp->lock, flags);
		data[j++] = reg & 0xFFFF;
	पूर्ण
पूर्ण

अटल पूर्णांक smc911x_ethtool_रुको_eeprom_पढ़ोy(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक समयout;
	पूर्णांक e2p_cmd;

	e2p_cmd = SMC_GET_E2P_CMD(lp);
	क्रम(समयout=10;(e2p_cmd & E2P_CMD_EPC_BUSY_) && समयout; समयout--) अणु
		अगर (e2p_cmd & E2P_CMD_EPC_TIMEOUT_) अणु
			PRINTK(dev, "%s timeout waiting for EEPROM to respond\n",
			       __func__);
			वापस -EFAULT;
		पूर्ण
		mdelay(1);
		e2p_cmd = SMC_GET_E2P_CMD(lp);
	पूर्ण
	अगर (समयout == 0) अणु
		PRINTK(dev, "%s timeout waiting for EEPROM CMD not busy\n",
		       __func__);
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक smc911x_ethtool_ग_लिखो_eeprom_cmd(काष्ठा net_device *dev,
													पूर्णांक cmd, पूर्णांक addr)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक ret;

	अगर ((ret = smc911x_ethtool_रुको_eeprom_पढ़ोy(dev))!=0)
		वापस ret;
	SMC_SET_E2P_CMD(lp, E2P_CMD_EPC_BUSY_ |
		((cmd) & (0x7<<28)) |
		((addr) & 0xFF));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक smc911x_ethtool_पढ़ो_eeprom_byte(काष्ठा net_device *dev,
													u8 *data)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक ret;

	अगर ((ret = smc911x_ethtool_रुको_eeprom_पढ़ोy(dev))!=0)
		वापस ret;
	*data = SMC_GET_E2P_DATA(lp);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक smc911x_ethtool_ग_लिखो_eeprom_byte(काष्ठा net_device *dev,
													 u8 data)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक ret;

	अगर ((ret = smc911x_ethtool_रुको_eeprom_पढ़ोy(dev))!=0)
		वापस ret;
	SMC_SET_E2P_DATA(lp, data);
	वापस 0;
पूर्ण

अटल पूर्णांक smc911x_ethtool_geteeprom(काष्ठा net_device *dev,
									  काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	u8 eebuf[SMC911X_EEPROM_LEN];
	पूर्णांक i, ret;

	क्रम(i=0;i<SMC911X_EEPROM_LEN;i++) अणु
		अगर ((ret=smc911x_ethtool_ग_लिखो_eeprom_cmd(dev, E2P_CMD_EPC_CMD_READ_, i ))!=0)
			वापस ret;
		अगर ((ret=smc911x_ethtool_पढ़ो_eeprom_byte(dev, &eebuf[i]))!=0)
			वापस ret;
		पूर्ण
	स_नकल(data, eebuf+eeprom->offset, eeprom->len);
	वापस 0;
पूर्ण

अटल पूर्णांक smc911x_ethtool_seteeprom(काष्ठा net_device *dev,
									   काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	पूर्णांक i, ret;

	/* Enable erase */
	अगर ((ret=smc911x_ethtool_ग_लिखो_eeprom_cmd(dev, E2P_CMD_EPC_CMD_EWEN_, 0 ))!=0)
		वापस ret;
	क्रम(i=eeprom->offset;i<(eeprom->offset+eeprom->len);i++) अणु
		/* erase byte */
		अगर ((ret=smc911x_ethtool_ग_लिखो_eeprom_cmd(dev, E2P_CMD_EPC_CMD_ERASE_, i ))!=0)
			वापस ret;
		/* ग_लिखो byte */
		अगर ((ret=smc911x_ethtool_ग_लिखो_eeprom_byte(dev, *data))!=0)
			 वापस ret;
		अगर ((ret=smc911x_ethtool_ग_लिखो_eeprom_cmd(dev, E2P_CMD_EPC_CMD_WRITE_, i ))!=0)
			वापस ret;
		पूर्ण
	 वापस 0;
पूर्ण

अटल पूर्णांक smc911x_ethtool_geteeprom_len(काष्ठा net_device *dev)
अणु
	 वापस SMC911X_EEPROM_LEN;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops smc911x_ethtool_ops = अणु
	.get_drvinfo	 = smc911x_ethtool_getdrvinfo,
	.get_msglevel	 = smc911x_ethtool_geपंचांगsglevel,
	.set_msglevel	 = smc911x_ethtool_seपंचांगsglevel,
	.nway_reset = smc911x_ethtool_nwayreset,
	.get_link	 = ethtool_op_get_link,
	.get_regs_len	 = smc911x_ethtool_getregslen,
	.get_regs	 = smc911x_ethtool_getregs,
	.get_eeprom_len = smc911x_ethtool_geteeprom_len,
	.get_eeprom = smc911x_ethtool_geteeprom,
	.set_eeprom = smc911x_ethtool_seteeprom,
	.get_link_ksettings	 = smc911x_ethtool_get_link_ksettings,
	.set_link_ksettings	 = smc911x_ethtool_set_link_ksettings,
पूर्ण;

/*
 * smc911x_findirq
 *
 * This routine has a simple purpose -- make the SMC chip generate an
 * पूर्णांकerrupt, so an स्वतः-detect routine can detect it, and find the IRQ,
 */
अटल पूर्णांक smc911x_findirq(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक समयout = 20;
	अचिन्हित दीर्घ cookie;

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	cookie = probe_irq_on();

	/*
	 * Force a SW पूर्णांकerrupt
	 */

	SMC_SET_INT_EN(lp, INT_EN_SW_INT_EN_);

	/*
	 * Wait until positive that the पूर्णांकerrupt has been generated
	 */
	करो अणु
		पूर्णांक पूर्णांक_status;
		udelay(10);
		पूर्णांक_status = SMC_GET_INT_EN(lp);
		अगर (पूर्णांक_status & INT_EN_SW_INT_EN_)
			 अवरोध;		/* got the पूर्णांकerrupt */
	पूर्ण जबतक (--समयout);

	/*
	 * there is really nothing that I can करो here अगर समयout fails,
	 * as स्वतःirq_report will वापस a 0 anyway, which is what I
	 * want in this हाल.	 Plus, the clean up is needed in both
	 * हालs.
	 */

	/* and disable all पूर्णांकerrupts again */
	SMC_SET_INT_EN(lp, 0);

	/* and वापस what I found */
	वापस probe_irq_off(cookie);
पूर्ण

अटल स्थिर काष्ठा net_device_ops smc911x_netdev_ops = अणु
	.nकरो_खोलो		= smc911x_खोलो,
	.nकरो_stop		= smc911x_बंद,
	.nकरो_start_xmit		= smc911x_hard_start_xmit,
	.nकरो_tx_समयout		= smc911x_समयout,
	.nकरो_set_rx_mode	= smc911x_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= smc911x_poll_controller,
#पूर्ण_अगर
पूर्ण;

/*
 * Function: smc911x_probe(अचिन्हित दीर्घ ioaddr)
 *
 * Purpose:
 *	 Tests to see अगर a given ioaddr poपूर्णांकs to an SMC911x chip.
 *	 Returns a 0 on success
 *
 * Algorithm:
 *	 (1) see अगर the endian word is OK
 *	 (1) see अगर I recognize the chip ID in the appropriate रेजिस्टर
 *
 * Here I करो typical initialization tasks.
 *
 * o  Initialize the काष्ठाure अगर needed
 * o  prपूर्णांक out my vanity message अगर not करोne so alपढ़ोy
 * o  prपूर्णांक out what type of hardware is detected
 * o  prपूर्णांक out the ethernet address
 * o  find the IRQ
 * o  set up my निजी data
 * o  configure the dev काष्ठाure with my subroutines
 * o  actually GRAB the irq.
 * o  GRAB the region
 */
अटल पूर्णांक smc911x_probe(काष्ठा net_device *dev)
अणु
	काष्ठा smc911x_local *lp = netdev_priv(dev);
	पूर्णांक i, retval;
	अचिन्हित पूर्णांक val, chip_id, revision;
	स्थिर अक्षर *version_string;
	अचिन्हित दीर्घ irq_flags;
#अगर_घोषित SMC_USE_DMA
	काष्ठा dma_slave_config	config;
	dma_cap_mask_t mask;
#पूर्ण_अगर

	DBG(SMC_DEBUG_FUNC, dev, "--> %s\n", __func__);

	/* First, see अगर the endian word is recognized */
	val = SMC_GET_BYTE_TEST(lp);
	DBG(SMC_DEBUG_MISC, dev, "%s: endian probe returned 0x%04x\n",
	    CARDNAME, val);
	अगर (val != 0x87654321) अणु
		netdev_err(dev, "Invalid chip endian 0x%08x\n", val);
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण

	/*
	 * check अगर the revision रेजिस्टर is something that I
	 * recognize.	These might need to be added to later,
	 * as future revisions could be added.
	 */
	chip_id = SMC_GET_PN(lp);
	DBG(SMC_DEBUG_MISC, dev, "%s: id probe returned 0x%04x\n",
	    CARDNAME, chip_id);
	क्रम(i=0;chip_ids[i].id != 0; i++) अणु
		अगर (chip_ids[i].id == chip_id) अवरोध;
	पूर्ण
	अगर (!chip_ids[i].id) अणु
		netdev_err(dev, "Unknown chip ID %04x\n", chip_id);
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण
	version_string = chip_ids[i].name;

	revision = SMC_GET_REV(lp);
	DBG(SMC_DEBUG_MISC, dev, "%s: revision = 0x%04x\n", CARDNAME, revision);

	/* At this poपूर्णांक I'll assume that the chip is an SMC911x. */
	DBG(SMC_DEBUG_MISC, dev, "%s: Found a %s\n",
	    CARDNAME, chip_ids[i].name);

	/* Validate the TX FIFO size requested */
	अगर ((tx_fअगरo_kb < 2) || (tx_fअगरo_kb > 14)) अणु
		netdev_err(dev, "Invalid TX FIFO size requested %d\n",
			   tx_fअगरo_kb);
		retval = -EINVAL;
		जाओ err_out;
	पूर्ण

	/* fill in some of the fields */
	lp->version = chip_ids[i].id;
	lp->revision = revision;
	lp->tx_fअगरo_kb = tx_fअगरo_kb;
	/* Reverse calculate the RX FIFO size from the TX */
	lp->tx_fअगरo_size=(lp->tx_fअगरo_kb<<10) - 512;
	lp->rx_fअगरo_size= ((0x4000 - 512 - lp->tx_fअगरo_size) / 16) * 15;

	/* Set the स्वतःmatic flow control values */
	चयन(lp->tx_fअगरo_kb) अणु
		/*
		 *	 AFC_HI is about ((Rx Data Fअगरo Size)*2/3)/64
		 *	 AFC_LO is AFC_HI/2
		 *	 BACK_DUR is about 5uS*(AFC_LO) rounded करोwn
		 */
		हाल 2:/* 13440 Rx Data Fअगरo Size */
			lp->afc_cfg=0x008C46AF;अवरोध;
		हाल 3:/* 12480 Rx Data Fअगरo Size */
			lp->afc_cfg=0x0082419F;अवरोध;
		हाल 4:/* 11520 Rx Data Fअगरo Size */
			lp->afc_cfg=0x00783C9F;अवरोध;
		हाल 5:/* 10560 Rx Data Fअगरo Size */
			lp->afc_cfg=0x006E374F;अवरोध;
		हाल 6:/* 9600 Rx Data Fअगरo Size */
			lp->afc_cfg=0x0064328F;अवरोध;
		हाल 7:/* 8640 Rx Data Fअगरo Size */
			lp->afc_cfg=0x005A2D7F;अवरोध;
		हाल 8:/* 7680 Rx Data Fअगरo Size */
			lp->afc_cfg=0x0050287F;अवरोध;
		हाल 9:/* 6720 Rx Data Fअगरo Size */
			lp->afc_cfg=0x0046236F;अवरोध;
		हाल 10:/* 5760 Rx Data Fअगरo Size */
			lp->afc_cfg=0x003C1E6F;अवरोध;
		हाल 11:/* 4800 Rx Data Fअगरo Size */
			lp->afc_cfg=0x0032195F;अवरोध;
		/*
		 *	 AFC_HI is ~1520 bytes less than RX Data Fअगरo Size
		 *	 AFC_LO is AFC_HI/2
		 *	 BACK_DUR is about 5uS*(AFC_LO) rounded करोwn
		 */
		हाल 12:/* 3840 Rx Data Fअगरo Size */
			lp->afc_cfg=0x0024124F;अवरोध;
		हाल 13:/* 2880 Rx Data Fअगरo Size */
			lp->afc_cfg=0x0015073F;अवरोध;
		हाल 14:/* 1920 Rx Data Fअगरo Size */
			lp->afc_cfg=0x0006032F;अवरोध;
		 शेष:
			 PRINTK(dev, "ERROR -- no AFC_CFG setting found");
			 अवरोध;
	पूर्ण

	DBG(SMC_DEBUG_MISC | SMC_DEBUG_TX | SMC_DEBUG_RX, dev,
	    "%s: tx_fifo %d rx_fifo %d afc_cfg 0x%08x\n", CARDNAME,
	    lp->tx_fअगरo_size, lp->rx_fअगरo_size, lp->afc_cfg);

	spin_lock_init(&lp->lock);

	/* Get the MAC address */
	SMC_GET_MAC_ADDR(lp, dev->dev_addr);

	/* now, reset the chip, and put it पूर्णांकo a known state */
	smc911x_reset(dev);

	/*
	 * If dev->irq is 0, then the device has to be banged on to see
	 * what the IRQ is.
	 *
	 * Specअगरying an IRQ is करोne with the assumption that the user knows
	 * what (s)he is करोing.  No checking is करोne!!!!
	 */
	अगर (dev->irq < 1) अणु
		पूर्णांक trials;

		trials = 3;
		जबतक (trials--) अणु
			dev->irq = smc911x_findirq(dev);
			अगर (dev->irq)
				अवरोध;
			/* kick the card and try again */
			smc911x_reset(dev);
		पूर्ण
	पूर्ण
	अगर (dev->irq == 0) अणु
		netdev_warn(dev, "Couldn't autodetect your IRQ. Use irq=xx.\n");
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण
	dev->irq = irq_canonicalize(dev->irq);

	dev->netdev_ops = &smc911x_netdev_ops;
	dev->watchकरोg_समयo = msecs_to_jअगरfies(watchकरोg);
	dev->ethtool_ops = &smc911x_ethtool_ops;

	INIT_WORK(&lp->phy_configure, smc911x_phy_configure);
	lp->mii.phy_id_mask = 0x1f;
	lp->mii.reg_num_mask = 0x1f;
	lp->mii.क्रमce_media = 0;
	lp->mii.full_duplex = 0;
	lp->mii.dev = dev;
	lp->mii.mdio_पढ़ो = smc911x_phy_पढ़ो;
	lp->mii.mdio_ग_लिखो = smc911x_phy_ग_लिखो;

	/*
	 * Locate the phy, अगर any.
	 */
	smc911x_phy_detect(dev);

	/* Set शेष parameters */
	lp->msg_enable = NETIF_MSG_LINK;
	lp->ctl_rfduplx = 1;
	lp->ctl_rspeed = 100;

#अगर_घोषित SMC_DYNAMIC_BUS_CONFIG
	irq_flags = lp->cfg.irq_flags;
#अन्यथा
	irq_flags = IRQF_SHARED | SMC_IRQ_SENSE;
#पूर्ण_अगर

	/* Grab the IRQ */
	retval = request_irq(dev->irq, smc911x_पूर्णांकerrupt,
			     irq_flags, dev->name, dev);
	अगर (retval)
		जाओ err_out;

#अगर_घोषित SMC_USE_DMA

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	lp->rxdma = dma_request_channel(mask, शून्य, शून्य);
	lp->txdma = dma_request_channel(mask, शून्य, शून्य);
	lp->rxdma_active = 0;
	lp->txdma_active = 0;

	स_रखो(&config, 0, माप(config));
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	config.src_addr = lp->physaddr + RX_DATA_FIFO;
	config.dst_addr = lp->physaddr + TX_DATA_FIFO;
	config.src_maxburst = 32;
	config.dst_maxburst = 32;
	retval = dmaengine_slave_config(lp->rxdma, &config);
	अगर (retval) अणु
		dev_err(lp->dev, "dma rx channel configuration failed: %d\n",
			retval);
		जाओ err_out;
	पूर्ण
	retval = dmaengine_slave_config(lp->txdma, &config);
	अगर (retval) अणु
		dev_err(lp->dev, "dma tx channel configuration failed: %d\n",
			retval);
		जाओ err_out;
	पूर्ण
#पूर्ण_अगर

	retval = रेजिस्टर_netdev(dev);
	अगर (retval == 0) अणु
		/* now, prपूर्णांक out the card info, in a लघु क्रमmat.. */
		netdev_info(dev, "%s (rev %d) at %#lx IRQ %d",
			    version_string, lp->revision,
			    dev->base_addr, dev->irq);

#अगर_घोषित SMC_USE_DMA
		अगर (lp->rxdma)
			pr_cont(" RXDMA %p", lp->rxdma);

		अगर (lp->txdma)
			pr_cont(" TXDMA %p", lp->txdma);
#पूर्ण_अगर
		pr_cont("\n");
		अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
			netdev_warn(dev, "Invalid ethernet MAC address. Please set using ifconfig\n");
		पूर्ण अन्यथा अणु
			/* Prपूर्णांक the Ethernet address */
			netdev_info(dev, "Ethernet addr: %pM\n",
				    dev->dev_addr);
		पूर्ण

		अगर (lp->phy_type == 0) अणु
			PRINTK(dev, "No PHY found\n");
		पूर्ण अन्यथा अगर ((lp->phy_type & ~0xff) == LAN911X_INTERNAL_PHY_ID) अणु
			PRINTK(dev, "LAN911x Internal PHY\n");
		पूर्ण अन्यथा अणु
			PRINTK(dev, "External PHY 0x%08x\n", lp->phy_type);
		पूर्ण
	पूर्ण

err_out:
#अगर_घोषित SMC_USE_DMA
	अगर (retval) अणु
		अगर (lp->rxdma)
			dma_release_channel(lp->rxdma);
		अगर (lp->txdma)
			dma_release_channel(lp->txdma);
	पूर्ण
#पूर्ण_अगर
	वापस retval;
पूर्ण

/*
 * smc911x_drv_probe(व्योम)
 *
 *	  Output:
 *	 0 --> there is a device
 *	 anything अन्यथा, error
 */
अटल पूर्णांक smc911x_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev;
	काष्ठा resource *res;
	काष्ठा smc911x_local *lp;
	व्योम __iomem *addr;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/*
	 * Request the regions.
	 */
	अगर (!request_mem_region(res->start, SMC911X_IO_EXTENT, CARDNAME)) अणु
		 ret = -EBUSY;
		 जाओ out;
	पूर्ण

	ndev = alloc_etherdev(माप(काष्ठा smc911x_local));
	अगर (!ndev) अणु
		ret = -ENOMEM;
		जाओ release_1;
	पूर्ण
	SET_NETDEV_DEV(ndev, &pdev->dev);

	ndev->dma = (अचिन्हित अक्षर)-1;
	ndev->irq = platक्रमm_get_irq(pdev, 0);
	lp = netdev_priv(ndev);
	lp->netdev = ndev;
#अगर_घोषित SMC_DYNAMIC_BUS_CONFIG
	अणु
		काष्ठा smc911x_platdata *pd = dev_get_platdata(&pdev->dev);
		अगर (!pd) अणु
			ret = -EINVAL;
			जाओ release_both;
		पूर्ण
		स_नकल(&lp->cfg, pd, माप(lp->cfg));
	पूर्ण
#पूर्ण_अगर

	addr = ioremap(res->start, SMC911X_IO_EXTENT);
	अगर (!addr) अणु
		ret = -ENOMEM;
		जाओ release_both;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ndev);
	lp->base = addr;
	ndev->base_addr = res->start;
	ret = smc911x_probe(ndev);
	अगर (ret != 0) अणु
		iounmap(addr);
release_both:
		मुक्त_netdev(ndev);
release_1:
		release_mem_region(res->start, SMC911X_IO_EXTENT);
out:
		pr_info("%s: not found (%d).\n", CARDNAME, ret);
	पूर्ण
#अगर_घोषित SMC_USE_DMA
	अन्यथा अणु
		lp->physaddr = res->start;
		lp->dev = &pdev->dev;
	पूर्ण
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक smc911x_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा smc911x_local *lp = netdev_priv(ndev);
	काष्ठा resource *res;

	DBG(SMC_DEBUG_FUNC, ndev, "--> %s\n", __func__);

	unरेजिस्टर_netdev(ndev);

	मुक्त_irq(ndev->irq, ndev);

#अगर_घोषित SMC_USE_DMA
	अणु
		अगर (lp->rxdma)
			dma_release_channel(lp->rxdma);
		अगर (lp->txdma)
			dma_release_channel(lp->txdma);
	पूर्ण
#पूर्ण_अगर
	iounmap(lp->base);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, SMC911X_IO_EXTENT);

	मुक्त_netdev(ndev);
	वापस 0;
पूर्ण

अटल पूर्णांक smc911x_drv_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(dev);
	काष्ठा smc911x_local *lp = netdev_priv(ndev);

	DBG(SMC_DEBUG_FUNC, ndev, "--> %s\n", __func__);
	अगर (ndev) अणु
		अगर (netअगर_running(ndev)) अणु
			netअगर_device_detach(ndev);
			smc911x_shutकरोwn(ndev);
#अगर POWER_DOWN
			/* Set D2 - Energy detect only setting */
			SMC_SET_PMT_CTRL(lp, 2<<12);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smc911x_drv_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(dev);

	DBG(SMC_DEBUG_FUNC, ndev, "--> %s\n", __func__);
	अगर (ndev) अणु
		काष्ठा smc911x_local *lp = netdev_priv(ndev);

		अगर (netअगर_running(ndev)) अणु
			smc911x_reset(ndev);
			अगर (lp->phy_type != 0)
				smc911x_phy_configure(&lp->phy_configure);
			smc911x_enable(ndev);
			netअगर_device_attach(ndev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver smc911x_driver = अणु
	.probe		 = smc911x_drv_probe,
	.हटाओ	 = smc911x_drv_हटाओ,
	.suspend	 = smc911x_drv_suspend,
	.resume	 = smc911x_drv_resume,
	.driver	 = अणु
		.name	 = CARDNAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(smc911x_driver);
