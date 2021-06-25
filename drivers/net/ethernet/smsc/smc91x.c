<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * smc91x.c
 * This is a driver क्रम SMSC's 91C9x/91C1xx single-chip Ethernet devices.
 *
 * Copyright (C) 1996 by Erik Stahlman
 * Copyright (C) 2001 Standard Microप्रणालीs Corporation
 *	Developed by Simple Network Magic Corporation
 * Copyright (C) 2003 Monta Vista Software, Inc.
 *	Unअगरied SMC91x driver by Nicolas Pitre
 *
 * Arguments:
 * 	io	= क्रम the base address
 *	irq	= क्रम the IRQ
 *	noरुको	= 0 क्रम normal रुको states, 1 eliminates additional रुको states
 *
 * original author:
 * 	Erik Stahlman <erik@vt.edu>
 *
 * hardware multicast code:
 *    Peter Cammaert <pc@denkart.be>
 *
 * contributors:
 * 	Daris A Nevil <dnevil@snmc.com>
 *      Nicolas Pitre <nico@fluxnic.net>
 *	Russell King <rmk@arm.linux.org.uk>
 *
 * History:
 *   08/20/00  Arnalकरो Melo       fix kमुक्त(skb) in smc_hardware_send_packet
 *   12/15/00  Christian Jullien  fix "Warning: kfree_skb on hard IRQ"
 *   03/16/01  Daris A Nevil      modअगरied smc9194.c क्रम use with LAN91C111
 *   08/22/01  Scott Anderson     merge changes from smc9194 to smc91111
 *   08/21/01  Pramod B Bhardwaj  added support क्रम RevB of LAN91C111
 *   12/20/01  Jeff Sutherland    initial port to Xscale PXA with DMA support
 *   04/07/03  Nicolas Pitre      unअगरied SMC91x driver, समाप्तed irq races,
 *                                more bus असलtraction, big cleanup, etc.
 *   29/09/03  Russell King       - add driver model support
 *                                - ethtool support
 *                                - convert to use generic MII पूर्णांकerface
 *                                - add link up/करोwn notअगरication
 *                                - करोn't try to handle full negotiation in
 *                                  smc_phy_configure
 *                                - clean up (and fix stack overrun) in PHY
 *                                  MII पढ़ो/ग_लिखो functions
 *   22/09/04  Nicolas Pitre      big update (see commit log क्रम details)
 */
अटल स्थिर अक्षर version[] =
	"smc91x.c: v1.1, sep 22 2004 by Nicolas Pitre <nico@fluxnic.net>";

/* Debugging level */
#अगर_अघोषित SMC_DEBUG
#घोषणा SMC_DEBUG		0
#पूर्ण_अगर


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/crc32.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <यंत्र/पन.स>

#समावेश "smc91x.h"

#अगर defined(CONFIG_ASSABET_NEPONSET)
#समावेश <mach/assabet.h>
#समावेश <mach/neponset.h>
#पूर्ण_अगर

#अगर_अघोषित SMC_NOWAIT
# define SMC_NOWAIT		0
#पूर्ण_अगर
अटल पूर्णांक noरुको = SMC_NOWAIT;
module_param(noरुको, पूर्णांक, 0400);
MODULE_PARM_DESC(noरुको, "set to 1 for no wait state");

/*
 * Transmit समयout, शेष 5 seconds.
 */
अटल पूर्णांक watchकरोg = 1000;
module_param(watchकरोg, पूर्णांक, 0400);
MODULE_PARM_DESC(watchकरोg, "transmit timeout in milliseconds");

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:smc91x");

/*
 * The पूर्णांकernal workings of the driver.  If you are changing anything
 * here with the SMC stuff, you should have the datasheet and know
 * what you are करोing.
 */
#घोषणा CARDNAME "smc91x"

/*
 * Use घातer-करोwn feature of the chip
 */
#घोषणा POWER_DOWN		1

/*
 * Wait समय क्रम memory to be मुक्त.  This probably shouldn't be
 * tuned that much, as रुकोing क्रम this means nothing अन्यथा happens
 * in the प्रणाली
 */
#घोषणा MEMORY_WAIT_TIME	16

/*
 * The maximum number of processing loops allowed क्रम each call to the
 * IRQ handler.
 */
#घोषणा MAX_IRQ_LOOPS		8

/*
 * This selects whether TX packets are sent one by one to the SMC91x पूर्णांकernal
 * memory and throttled until transmission completes.  This may prevent
 * RX overruns a litle by keeping much of the memory मुक्त क्रम RX packets
 * but to the expense of reduced TX throughput and increased IRQ overhead.
 * Note this is not a cure क्रम a too slow data bus or too high IRQ latency.
 */
#घोषणा THROTTLE_TX_PKTS	0

/*
 * The MII घड़ी high/low बार.  2x this number gives the MII घड़ी period
 * in microseconds. (was 50, but this gives 6.4ms क्रम each MII transaction!)
 */
#घोषणा MII_DELAY		1

#घोषणा DBG(n, dev, fmt, ...)					\
	करो अणु							\
		अगर (SMC_DEBUG >= (n))				\
			netdev_dbg(dev, fmt, ##__VA_ARGS__);	\
	पूर्ण जबतक (0)

#घोषणा PRINTK(dev, fmt, ...)					\
	करो अणु							\
		अगर (SMC_DEBUG > 0)				\
			netdev_info(dev, fmt, ##__VA_ARGS__);	\
		अन्यथा						\
			netdev_dbg(dev, fmt, ##__VA_ARGS__);	\
	पूर्ण जबतक (0)

#अगर SMC_DEBUG > 3
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
अटल अंतरभूत व्योम PRINT_PKT(u_अक्षर *buf, पूर्णांक length) अणु पूर्ण
#पूर्ण_अगर


/* this enables an पूर्णांकerrupt in the पूर्णांकerrupt mask रेजिस्टर */
#घोषणा SMC_ENABLE_INT(lp, x) करो अणु					\
	अचिन्हित अक्षर mask;						\
	अचिन्हित दीर्घ smc_enable_flags;					\
	spin_lock_irqsave(&lp->lock, smc_enable_flags);			\
	mask = SMC_GET_INT_MASK(lp);					\
	mask |= (x);							\
	SMC_SET_INT_MASK(lp, mask);					\
	spin_unlock_irqrestore(&lp->lock, smc_enable_flags);		\
पूर्ण जबतक (0)

/* this disables an पूर्णांकerrupt from the पूर्णांकerrupt mask रेजिस्टर */
#घोषणा SMC_DISABLE_INT(lp, x) करो अणु					\
	अचिन्हित अक्षर mask;						\
	अचिन्हित दीर्घ smc_disable_flags;				\
	spin_lock_irqsave(&lp->lock, smc_disable_flags);		\
	mask = SMC_GET_INT_MASK(lp);					\
	mask &= ~(x);							\
	SMC_SET_INT_MASK(lp, mask);					\
	spin_unlock_irqrestore(&lp->lock, smc_disable_flags);		\
पूर्ण जबतक (0)

/*
 * Wait जबतक MMU is busy.  This is usually in the order of a few nanosecs
 * अगर at all, but let's aव्योम deadlocking the प्रणाली अगर the hardware
 * decides to go south.
 */
#घोषणा SMC_WAIT_MMU_BUSY(lp) करो अणु					\
	अगर (unlikely(SMC_GET_MMU_CMD(lp) & MC_BUSY)) अणु		\
		अचिन्हित दीर्घ समयout = jअगरfies + 2;			\
		जबतक (SMC_GET_MMU_CMD(lp) & MC_BUSY) अणु		\
			अगर (समय_after(jअगरfies, समयout)) अणु		\
				netdev_dbg(dev, "timeout %s line %d\n",	\
					   __खाता__, __LINE__);		\
				अवरोध;					\
			पूर्ण						\
			cpu_relax();					\
		पूर्ण							\
	पूर्ण								\
पूर्ण जबतक (0)


/*
 * this करोes a soft reset on the device
 */
अटल व्योम smc_reset(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित पूर्णांक ctl, cfg;
	काष्ठा sk_buff *pending_skb;

	DBG(2, dev, "%s\n", __func__);

	/* Disable all पूर्णांकerrupts, block TX tasklet */
	spin_lock_irq(&lp->lock);
	SMC_SELECT_BANK(lp, 2);
	SMC_SET_INT_MASK(lp, 0);
	pending_skb = lp->pending_tx_skb;
	lp->pending_tx_skb = शून्य;
	spin_unlock_irq(&lp->lock);

	/* मुक्त any pending tx skb */
	अगर (pending_skb) अणु
		dev_kमुक्त_skb(pending_skb);
		dev->stats.tx_errors++;
		dev->stats.tx_पातed_errors++;
	पूर्ण

	/*
	 * This resets the रेजिस्टरs mostly to शेषs, but करोesn't
	 * affect EEPROM.  That seems unnecessary
	 */
	SMC_SELECT_BANK(lp, 0);
	SMC_SET_RCR(lp, RCR_SOFTRST);

	/*
	 * Setup the Configuration Register
	 * This is necessary because the CONFIG_REG is not affected
	 * by a soft reset
	 */
	SMC_SELECT_BANK(lp, 1);

	cfg = CONFIG_DEFAULT;

	/*
	 * Setup क्रम fast accesses अगर requested.  If the card/प्रणाली
	 * can't handle it then there will be no recovery except क्रम
	 * a hard reset or घातer cycle
	 */
	अगर (lp->cfg.flags & SMC91X_NOWAIT)
		cfg |= CONFIG_NO_WAIT;

	/*
	 * Release from possible घातer-करोwn state
	 * Configuration रेजिस्टर is not affected by Soft Reset
	 */
	cfg |= CONFIG_EPH_POWER_EN;

	SMC_SET_CONFIG(lp, cfg);

	/* this should छोड़ो enough क्रम the chip to be happy */
	/*
	 * elaborate?  What करोes the chip _need_? --jgarzik
	 *
	 * This seems to be unकरोcumented, but something the original
	 * driver(s) have always करोne.  Suspect unकरोcumented timing
	 * info/determined empirically. --rmk
	 */
	udelay(1);

	/* Disable transmit and receive functionality */
	SMC_SELECT_BANK(lp, 0);
	SMC_SET_RCR(lp, RCR_CLEAR);
	SMC_SET_TCR(lp, TCR_CLEAR);

	SMC_SELECT_BANK(lp, 1);
	ctl = SMC_GET_CTL(lp) | CTL_LE_ENABLE;

	/*
	 * Set the control रेजिस्टर to स्वतःmatically release successfully
	 * transmitted packets, to make the best use out of our limited
	 * memory
	 */
	अगर(!THROTTLE_TX_PKTS)
		ctl |= CTL_AUTO_RELEASE;
	अन्यथा
		ctl &= ~CTL_AUTO_RELEASE;
	SMC_SET_CTL(lp, ctl);

	/* Reset the MMU */
	SMC_SELECT_BANK(lp, 2);
	SMC_SET_MMU_CMD(lp, MC_RESET);
	SMC_WAIT_MMU_BUSY(lp);
पूर्ण

/*
 * Enable Interrupts, Receive, and Transmit
 */
अटल व्योम smc_enable(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	पूर्णांक mask;

	DBG(2, dev, "%s\n", __func__);

	/* see the header file क्रम options in TCR/RCR DEFAULT */
	SMC_SELECT_BANK(lp, 0);
	SMC_SET_TCR(lp, lp->tcr_cur_mode);
	SMC_SET_RCR(lp, lp->rcr_cur_mode);

	SMC_SELECT_BANK(lp, 1);
	SMC_SET_MAC_ADDR(lp, dev->dev_addr);

	/* now, enable पूर्णांकerrupts */
	mask = IM_EPH_INT|IM_RX_OVRN_INT|IM_RCV_INT;
	अगर (lp->version >= (CHIP_91100 << 4))
		mask |= IM_MDINT;
	SMC_SELECT_BANK(lp, 2);
	SMC_SET_INT_MASK(lp, mask);

	/*
	 * From this poपूर्णांक the रेजिस्टर bank must _NOT_ be चयनed away
	 * to something अन्यथा than bank 2 without proper locking against
	 * races with any tasklet or पूर्णांकerrupt handlers until smc_shutकरोwn()
	 * or smc_reset() is called.
	 */
पूर्ण

/*
 * this माला_दो the device in an inactive state
 */
अटल व्योम smc_shutकरोwn(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	काष्ठा sk_buff *pending_skb;

	DBG(2, dev, "%s: %s\n", CARDNAME, __func__);

	/* no more पूर्णांकerrupts क्रम me */
	spin_lock_irq(&lp->lock);
	SMC_SELECT_BANK(lp, 2);
	SMC_SET_INT_MASK(lp, 0);
	pending_skb = lp->pending_tx_skb;
	lp->pending_tx_skb = शून्य;
	spin_unlock_irq(&lp->lock);
	dev_kमुक्त_skb(pending_skb);

	/* and tell the card to stay away from that nasty outside world */
	SMC_SELECT_BANK(lp, 0);
	SMC_SET_RCR(lp, RCR_CLEAR);
	SMC_SET_TCR(lp, TCR_CLEAR);

#अगर_घोषित POWER_DOWN
	/* finally, shut the chip करोwn */
	SMC_SELECT_BANK(lp, 1);
	SMC_SET_CONFIG(lp, SMC_GET_CONFIG(lp) & ~CONFIG_EPH_POWER_EN);
#पूर्ण_अगर
पूर्ण

/*
 * This is the procedure to handle the receipt of a packet.
 */
अटल अंतरभूत व्योम  smc_rcv(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित पूर्णांक packet_number, status, packet_len;

	DBG(3, dev, "%s\n", __func__);

	packet_number = SMC_GET_RXFIFO(lp);
	अगर (unlikely(packet_number & RXFIFO_REMPTY)) अणु
		PRINTK(dev, "smc_rcv with nothing on FIFO.\n");
		वापस;
	पूर्ण

	/* पढ़ो from start of packet */
	SMC_SET_PTR(lp, PTR_READ | PTR_RCV | PTR_AUTOINC);

	/* First two words are status and packet length */
	SMC_GET_PKT_HDR(lp, status, packet_len);
	packet_len &= 0x07ff;  /* mask off top bits */
	DBG(2, dev, "RX PNR 0x%x STATUS 0x%04x LENGTH 0x%04x (%d)\n",
	    packet_number, status, packet_len, packet_len);

	back:
	अगर (unlikely(packet_len < 6 || status & RS_ERRORS)) अणु
		अगर (status & RS_TOOLONG && packet_len <= (1514 + 4 + 6)) अणु
			/* accept VLAN packets */
			status &= ~RS_TOOLONG;
			जाओ back;
		पूर्ण
		अगर (packet_len < 6) अणु
			/* bloody hardware */
			netdev_err(dev, "fubar (rxlen %u status %x\n",
				   packet_len, status);
			status |= RS_TOOSHORT;
		पूर्ण
		SMC_WAIT_MMU_BUSY(lp);
		SMC_SET_MMU_CMD(lp, MC_RELEASE);
		dev->stats.rx_errors++;
		अगर (status & RS_ALGNERR)
			dev->stats.rx_frame_errors++;
		अगर (status & (RS_TOOSHORT | RS_TOOLONG))
			dev->stats.rx_length_errors++;
		अगर (status & RS_BADCRC)
			dev->stats.rx_crc_errors++;
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *skb;
		अचिन्हित अक्षर *data;
		अचिन्हित पूर्णांक data_len;

		/* set multicast stats */
		अगर (status & RS_MULTICAST)
			dev->stats.multicast++;

		/*
		 * Actual payload is packet_len - 6 (or 5 अगर odd byte).
		 * We want skb_reserve(2) and the final ctrl word
		 * (2 bytes, possibly containing the payload odd byte).
		 * Furthermore, we add 2 bytes to allow rounding up to
		 * multiple of 4 bytes on 32 bit buses.
		 * Hence packet_len - 6 + 2 + 2 + 2.
		 */
		skb = netdev_alloc_skb(dev, packet_len);
		अगर (unlikely(skb == शून्य)) अणु
			SMC_WAIT_MMU_BUSY(lp);
			SMC_SET_MMU_CMD(lp, MC_RELEASE);
			dev->stats.rx_dropped++;
			वापस;
		पूर्ण

		/* Align IP header to 32 bits */
		skb_reserve(skb, 2);

		/* BUG: the LAN91C111 rev A never sets this bit. Force it. */
		अगर (lp->version == 0x90)
			status |= RS_ODDFRAME;

		/*
		 * If odd length: packet_len - 5,
		 * otherwise packet_len - 6.
		 * With the trailing ctrl byte it's packet_len - 4.
		 */
		data_len = packet_len - ((status & RS_ODDFRAME) ? 5 : 6);
		data = skb_put(skb, data_len);
		SMC_PULL_DATA(lp, data, packet_len - 4);

		SMC_WAIT_MMU_BUSY(lp);
		SMC_SET_MMU_CMD(lp, MC_RELEASE);

		PRINT_PKT(data, packet_len - 4);

		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += data_len;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * On SMP we have the following problem:
 *
 * 	A = smc_hardware_send_pkt()
 * 	B = smc_hard_start_xmit()
 * 	C = smc_पूर्णांकerrupt()
 *
 * A and B can never be executed simultaneously.  However, at least on UP,
 * it is possible (and even desirable) क्रम C to पूर्णांकerrupt execution of
 * A or B in order to have better RX reliability and aव्योम overruns.
 * C, just like A and B, must have exclusive access to the chip and
 * each of them must lock against any other concurrent access.
 * Unक्रमtunately this is not possible to have C suspend execution of A or
 * B taking place on another CPU. On UP this is no an issue since A and B
 * are run from softirq context and C from hard IRQ context, and there is
 * no other CPU where concurrent access can happen.
 * If ever there is a way to क्रमce at least B and C to always be executed
 * on the same CPU then we could use पढ़ो/ग_लिखो locks to protect against
 * any other concurrent access and C would always पूर्णांकerrupt B. But lअगरe
 * isn't that easy in a SMP world...
 */
#घोषणा smc_special_trylock(lock, flags)				\
(अणु									\
	पूर्णांक __ret;							\
	local_irq_save(flags);						\
	__ret = spin_trylock(lock);					\
	अगर (!__ret)							\
		local_irq_restore(flags);				\
	__ret;								\
पूर्ण)
#घोषणा smc_special_lock(lock, flags)		spin_lock_irqsave(lock, flags)
#घोषणा smc_special_unlock(lock, flags) 	spin_unlock_irqrestore(lock, flags)
#अन्यथा
#घोषणा smc_special_trylock(lock, flags)	((व्योम)flags, true)
#घोषणा smc_special_lock(lock, flags)   	करो अणु flags = 0; पूर्ण जबतक (0)
#घोषणा smc_special_unlock(lock, flags)	करो अणु flags = 0; पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * This is called to actually send a packet to the chip.
 */
अटल व्योम smc_hardware_send_pkt(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा smc_local *lp = from_tasklet(lp, t, tx_task);
	काष्ठा net_device *dev = lp->dev;
	व्योम __iomem *ioaddr = lp->base;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक packet_no, len;
	अचिन्हित अक्षर *buf;
	अचिन्हित दीर्घ flags;

	DBG(3, dev, "%s\n", __func__);

	अगर (!smc_special_trylock(&lp->lock, flags)) अणु
		netअगर_stop_queue(dev);
		tasklet_schedule(&lp->tx_task);
		वापस;
	पूर्ण

	skb = lp->pending_tx_skb;
	अगर (unlikely(!skb)) अणु
		smc_special_unlock(&lp->lock, flags);
		वापस;
	पूर्ण
	lp->pending_tx_skb = शून्य;

	packet_no = SMC_GET_AR(lp);
	अगर (unlikely(packet_no & AR_FAILED)) अणु
		netdev_err(dev, "Memory allocation failed.\n");
		dev->stats.tx_errors++;
		dev->stats.tx_fअगरo_errors++;
		smc_special_unlock(&lp->lock, flags);
		जाओ करोne;
	पूर्ण

	/* poपूर्णांक to the beginning of the packet */
	SMC_SET_PN(lp, packet_no);
	SMC_SET_PTR(lp, PTR_AUTOINC);

	buf = skb->data;
	len = skb->len;
	DBG(2, dev, "TX PNR 0x%x LENGTH 0x%04x (%d) BUF 0x%p\n",
	    packet_no, len, len, buf);
	PRINT_PKT(buf, len);

	/*
	 * Send the packet length (+6 क्रम status words, length, and ctl.
	 * The card will pad to 64 bytes with zeroes अगर packet is too small.
	 */
	SMC_PUT_PKT_HDR(lp, 0, len + 6);

	/* send the actual data */
	SMC_PUSH_DATA(lp, buf, len & ~1);

	/* Send final ctl word with the last byte अगर there is one */
	SMC_outw(lp, ((len & 1) ? (0x2000 | buf[len - 1]) : 0), ioaddr,
		 DATA_REG(lp));

	/*
	 * If THROTTLE_TX_PKTS is set, we stop the queue here. This will
	 * have the effect of having at most one packet queued क्रम TX
	 * in the chip's memory at all समय.
	 *
	 * If THROTTLE_TX_PKTS is not set then the queue is stopped only
	 * when memory allocation (MC_ALLOC) करोes not succeed right away.
	 */
	अगर (THROTTLE_TX_PKTS)
		netअगर_stop_queue(dev);

	/* queue the packet क्रम TX */
	SMC_SET_MMU_CMD(lp, MC_ENQUEUE);
	smc_special_unlock(&lp->lock, flags);

	netअगर_trans_update(dev);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;

	SMC_ENABLE_INT(lp, IM_TX_INT | IM_TX_EMPTY_INT);

करोne:	अगर (!THROTTLE_TX_PKTS)
		netअगर_wake_queue(dev);

	dev_consume_skb_any(skb);
पूर्ण

/*
 * Since I am not sure अगर I will have enough room in the chip's ram
 * to store the packet, I call this routine which either sends it
 * now, or set the card to generates an पूर्णांकerrupt when पढ़ोy
 * क्रम the packet.
 */
अटल netdev_tx_t
smc_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित पूर्णांक numPages, poll_count, status;
	अचिन्हित दीर्घ flags;

	DBG(3, dev, "%s\n", __func__);

	BUG_ON(lp->pending_tx_skb != शून्य);

	/*
	 * The MMU wants the number of pages to be the number of 256 bytes
	 * 'pages', minus 1 (since a packet can't ever have 0 pages :))
	 *
	 * The 91C111 ignores the size bits, but earlier models करोn't.
	 *
	 * Pkt size क्रम allocating is data length +6 (क्रम additional status
	 * words, length and ctl)
	 *
	 * If odd size then last byte is included in ctl word.
	 */
	numPages = ((skb->len & ~1) + (6 - 1)) >> 8;
	अगर (unlikely(numPages > 7)) अणु
		netdev_warn(dev, "Far too big packet error.\n");
		dev->stats.tx_errors++;
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	smc_special_lock(&lp->lock, flags);

	/* now, try to allocate the memory */
	SMC_SET_MMU_CMD(lp, MC_ALLOC | numPages);

	/*
	 * Poll the chip क्रम a लघु amount of समय in हाल the
	 * allocation succeeds quickly.
	 */
	poll_count = MEMORY_WAIT_TIME;
	करो अणु
		status = SMC_GET_INT(lp);
		अगर (status & IM_ALLOC_INT) अणु
			SMC_ACK_INT(lp, IM_ALLOC_INT);
  			अवरोध;
		पूर्ण
   	पूर्ण जबतक (--poll_count);

	smc_special_unlock(&lp->lock, flags);

	lp->pending_tx_skb = skb;
   	अगर (!poll_count) अणु
		/* oh well, रुको until the chip finds memory later */
		netअगर_stop_queue(dev);
		DBG(2, dev, "TX memory allocation deferred.\n");
		SMC_ENABLE_INT(lp, IM_ALLOC_INT);
   	पूर्ण अन्यथा अणु
		/*
		 * Allocation succeeded: push packet to the chip's own memory
		 * immediately.
		 */
		smc_hardware_send_pkt(&lp->tx_task);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * This handles a TX पूर्णांकerrupt, which is only called when:
 * - a TX error occurred, or
 * - CTL_AUTO_RELEASE is not set and TX of a packet completed.
 */
अटल व्योम smc_tx(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित पूर्णांक saved_packet, packet_no, tx_status;
	अचिन्हित पूर्णांक pkt_len __always_unused;

	DBG(3, dev, "%s\n", __func__);

	/* If the TX FIFO is empty then nothing to करो */
	packet_no = SMC_GET_TXFIFO(lp);
	अगर (unlikely(packet_no & TXFIFO_TEMPTY)) अणु
		PRINTK(dev, "smc_tx with nothing on FIFO.\n");
		वापस;
	पूर्ण

	/* select packet to पढ़ो from */
	saved_packet = SMC_GET_PN(lp);
	SMC_SET_PN(lp, packet_no);

	/* पढ़ो the first word (status word) from this packet */
	SMC_SET_PTR(lp, PTR_AUTOINC | PTR_READ);
	SMC_GET_PKT_HDR(lp, tx_status, pkt_len);
	DBG(2, dev, "TX STATUS 0x%04x PNR 0x%02x\n",
	    tx_status, packet_no);

	अगर (!(tx_status & ES_TX_SUC))
		dev->stats.tx_errors++;

	अगर (tx_status & ES_LOSTCARR)
		dev->stats.tx_carrier_errors++;

	अगर (tx_status & (ES_LATCOL | ES_16COL)) अणु
		PRINTK(dev, "%s occurred on last xmit\n",
		       (tx_status & ES_LATCOL) ?
			"late collision" : "too many collisions");
		dev->stats.tx_winकरोw_errors++;
		अगर (!(dev->stats.tx_winकरोw_errors & 63) && net_ratelimit()) अणु
			netdev_info(dev, "unexpectedly large number of bad collisions. Please check duplex setting.\n");
		पूर्ण
	पूर्ण

	/* समाप्त the packet */
	SMC_WAIT_MMU_BUSY(lp);
	SMC_SET_MMU_CMD(lp, MC_FREEPKT);

	/* Don't restore Packet Number Reg until busy bit is cleared */
	SMC_WAIT_MMU_BUSY(lp);
	SMC_SET_PN(lp, saved_packet);

	/* re-enable transmit */
	SMC_SELECT_BANK(lp, 0);
	SMC_SET_TCR(lp, lp->tcr_cur_mode);
	SMC_SELECT_BANK(lp, 2);
पूर्ण


/*---PHY CONTROL AND CONFIGURATION-----------------------------------------*/

अटल व्योम smc_mii_out(काष्ठा net_device *dev, अचिन्हित पूर्णांक val, पूर्णांक bits)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित पूर्णांक mii_reg, mask;

	mii_reg = SMC_GET_MII(lp) & ~(MII_MCLK | MII_MDOE | MII_MDO);
	mii_reg |= MII_MDOE;

	क्रम (mask = 1 << (bits - 1); mask; mask >>= 1) अणु
		अगर (val & mask)
			mii_reg |= MII_MDO;
		अन्यथा
			mii_reg &= ~MII_MDO;

		SMC_SET_MII(lp, mii_reg);
		udelay(MII_DELAY);
		SMC_SET_MII(lp, mii_reg | MII_MCLK);
		udelay(MII_DELAY);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक smc_mii_in(काष्ठा net_device *dev, पूर्णांक bits)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित पूर्णांक mii_reg, mask, val;

	mii_reg = SMC_GET_MII(lp) & ~(MII_MCLK | MII_MDOE | MII_MDO);
	SMC_SET_MII(lp, mii_reg);

	क्रम (mask = 1 << (bits - 1), val = 0; mask; mask >>= 1) अणु
		अगर (SMC_GET_MII(lp) & MII_MDI)
			val |= mask;

		SMC_SET_MII(lp, mii_reg);
		udelay(MII_DELAY);
		SMC_SET_MII(lp, mii_reg | MII_MCLK);
		udelay(MII_DELAY);
	पूर्ण

	वापस val;
पूर्ण

/*
 * Reads a रेजिस्टर from the MII Management serial पूर्णांकerface
 */
अटल पूर्णांक smc_phy_पढ़ो(काष्ठा net_device *dev, पूर्णांक phyaddr, पूर्णांक phyreg)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित पूर्णांक phydata;

	SMC_SELECT_BANK(lp, 3);

	/* Idle - 32 ones */
	smc_mii_out(dev, 0xffffffff, 32);

	/* Start code (01) + पढ़ो (10) + phyaddr + phyreg */
	smc_mii_out(dev, 6 << 10 | phyaddr << 5 | phyreg, 14);

	/* Turnaround (2bits) + phydata */
	phydata = smc_mii_in(dev, 18);

	/* Return to idle state */
	SMC_SET_MII(lp, SMC_GET_MII(lp) & ~(MII_MCLK|MII_MDOE|MII_MDO));

	DBG(3, dev, "%s: phyaddr=0x%x, phyreg=0x%x, phydata=0x%x\n",
	    __func__, phyaddr, phyreg, phydata);

	SMC_SELECT_BANK(lp, 2);
	वापस phydata;
पूर्ण

/*
 * Writes a रेजिस्टर to the MII Management serial पूर्णांकerface
 */
अटल व्योम smc_phy_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phyaddr, पूर्णांक phyreg,
			  पूर्णांक phydata)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;

	SMC_SELECT_BANK(lp, 3);

	/* Idle - 32 ones */
	smc_mii_out(dev, 0xffffffff, 32);

	/* Start code (01) + ग_लिखो (01) + phyaddr + phyreg + turnaround + phydata */
	smc_mii_out(dev, 5 << 28 | phyaddr << 23 | phyreg << 18 | 2 << 16 | phydata, 32);

	/* Return to idle state */
	SMC_SET_MII(lp, SMC_GET_MII(lp) & ~(MII_MCLK|MII_MDOE|MII_MDO));

	DBG(3, dev, "%s: phyaddr=0x%x, phyreg=0x%x, phydata=0x%x\n",
	    __func__, phyaddr, phyreg, phydata);

	SMC_SELECT_BANK(lp, 2);
पूर्ण

/*
 * Finds and reports the PHY address
 */
अटल व्योम smc_phy_detect(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	पूर्णांक phyaddr;

	DBG(2, dev, "%s\n", __func__);

	lp->phy_type = 0;

	/*
	 * Scan all 32 PHY addresses अगर necessary, starting at
	 * PHY#1 to PHY#31, and then PHY#0 last.
	 */
	क्रम (phyaddr = 1; phyaddr < 33; ++phyaddr) अणु
		अचिन्हित पूर्णांक id1, id2;

		/* Read the PHY identअगरiers */
		id1 = smc_phy_पढ़ो(dev, phyaddr & 31, MII_PHYSID1);
		id2 = smc_phy_पढ़ो(dev, phyaddr & 31, MII_PHYSID2);

		DBG(3, dev, "phy_id1=0x%x, phy_id2=0x%x\n",
		    id1, id2);

		/* Make sure it is a valid identअगरier */
		अगर (id1 != 0x0000 && id1 != 0xffff && id1 != 0x8000 &&
		    id2 != 0x0000 && id2 != 0xffff && id2 != 0x8000) अणु
			/* Save the PHY's address */
			lp->mii.phy_id = phyaddr & 31;
			lp->phy_type = id1 << 16 | id2;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Sets the PHY to a configuration as determined by the user
 */
अटल पूर्णांक smc_phy_fixed(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	पूर्णांक phyaddr = lp->mii.phy_id;
	पूर्णांक bmcr, cfg1;

	DBG(3, dev, "%s\n", __func__);

	/* Enter Link Disable state */
	cfg1 = smc_phy_पढ़ो(dev, phyaddr, PHY_CFG1_REG);
	cfg1 |= PHY_CFG1_LNKDIS;
	smc_phy_ग_लिखो(dev, phyaddr, PHY_CFG1_REG, cfg1);

	/*
	 * Set our fixed capabilities
	 * Disable स्वतः-negotiation
	 */
	bmcr = 0;

	अगर (lp->ctl_rfduplx)
		bmcr |= BMCR_FULLDPLX;

	अगर (lp->ctl_rspeed == 100)
		bmcr |= BMCR_SPEED100;

	/* Write our capabilities to the phy control रेजिस्टर */
	smc_phy_ग_लिखो(dev, phyaddr, MII_BMCR, bmcr);

	/* Re-Configure the Receive/Phy Control रेजिस्टर */
	SMC_SELECT_BANK(lp, 0);
	SMC_SET_RPC(lp, lp->rpc_cur_mode);
	SMC_SELECT_BANK(lp, 2);

	वापस 1;
पूर्ण

/**
 * smc_phy_reset - reset the phy
 * @dev: net device
 * @phy: phy address
 *
 * Issue a software reset क्रम the specअगरied PHY and
 * रुको up to 100ms क्रम the reset to complete.  We should
 * not access the PHY क्रम 50ms after issuing the reset.
 *
 * The समय to रुको appears to be dependent on the PHY.
 *
 * Must be called with lp->lock locked.
 */
अटल पूर्णांक smc_phy_reset(काष्ठा net_device *dev, पूर्णांक phy)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक bmcr;
	पूर्णांक समयout;

	smc_phy_ग_लिखो(dev, phy, MII_BMCR, BMCR_RESET);

	क्रम (समयout = 2; समयout; समयout--) अणु
		spin_unlock_irq(&lp->lock);
		msleep(50);
		spin_lock_irq(&lp->lock);

		bmcr = smc_phy_पढ़ो(dev, phy, MII_BMCR);
		अगर (!(bmcr & BMCR_RESET))
			अवरोध;
	पूर्ण

	वापस bmcr & BMCR_RESET;
पूर्ण

/**
 * smc_phy_घातerकरोwn - घातerकरोwn phy
 * @dev: net device
 *
 * Power करोwn the specअगरied PHY
 */
अटल व्योम smc_phy_घातerकरोwn(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	अचिन्हित पूर्णांक bmcr;
	पूर्णांक phy = lp->mii.phy_id;

	अगर (lp->phy_type == 0)
		वापस;

	/* We need to ensure that no calls to smc_phy_configure are
	   pending.
	*/
	cancel_work_sync(&lp->phy_configure);

	bmcr = smc_phy_पढ़ो(dev, phy, MII_BMCR);
	smc_phy_ग_लिखो(dev, phy, MII_BMCR, bmcr | BMCR_PDOWN);
पूर्ण

/**
 * smc_phy_check_media - check the media status and adjust TCR
 * @dev: net device
 * @init: set true क्रम initialisation
 *
 * Select duplex mode depending on negotiation state.  This
 * also updates our carrier state.
 */
अटल व्योम smc_phy_check_media(काष्ठा net_device *dev, पूर्णांक init)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;

	अगर (mii_check_media(&lp->mii, netअगर_msg_link(lp), init)) अणु
		/* duplex state has changed */
		अगर (lp->mii.full_duplex) अणु
			lp->tcr_cur_mode |= TCR_SWFDUP;
		पूर्ण अन्यथा अणु
			lp->tcr_cur_mode &= ~TCR_SWFDUP;
		पूर्ण

		SMC_SELECT_BANK(lp, 0);
		SMC_SET_TCR(lp, lp->tcr_cur_mode);
	पूर्ण
पूर्ण

/*
 * Configures the specअगरied PHY through the MII management पूर्णांकerface
 * using Autonegotiation.
 * Calls smc_phy_fixed() अगर the user has requested a certain config.
 * If RPC ANEG bit is set, the media selection is dependent purely on
 * the selection by the MII (either in the MII BMCR reg or the result
 * of स्वतःnegotiation.)  If the RPC ANEG bit is cleared, the selection
 * is controlled by the RPC SPEED and RPC DPLX bits.
 */
अटल व्योम smc_phy_configure(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_local *lp =
		container_of(work, काष्ठा smc_local, phy_configure);
	काष्ठा net_device *dev = lp->dev;
	व्योम __iomem *ioaddr = lp->base;
	पूर्णांक phyaddr = lp->mii.phy_id;
	पूर्णांक my_phy_caps; /* My PHY capabilities */
	पूर्णांक my_ad_caps; /* My Advertised capabilities */

	DBG(3, dev, "smc_program_phy()\n");

	spin_lock_irq(&lp->lock);

	/*
	 * We should not be called अगर phy_type is zero.
	 */
	अगर (lp->phy_type == 0)
		जाओ smc_phy_configure_निकास;

	अगर (smc_phy_reset(dev, phyaddr)) अणु
		netdev_info(dev, "PHY reset timed out\n");
		जाओ smc_phy_configure_निकास;
	पूर्ण

	/*
	 * Enable PHY Interrupts (क्रम रेजिस्टर 18)
	 * Interrupts listed here are disabled
	 */
	smc_phy_ग_लिखो(dev, phyaddr, PHY_MASK_REG,
		PHY_INT_LOSSSYNC | PHY_INT_CWRD | PHY_INT_SSD |
		PHY_INT_ESD | PHY_INT_RPOL | PHY_INT_JAB |
		PHY_INT_SPDDET | PHY_INT_DPLXDET);

	/* Configure the Receive/Phy Control रेजिस्टर */
	SMC_SELECT_BANK(lp, 0);
	SMC_SET_RPC(lp, lp->rpc_cur_mode);

	/* If the user requested no स्वतः neg, then go set his request */
	अगर (lp->mii.क्रमce_media) अणु
		smc_phy_fixed(dev);
		जाओ smc_phy_configure_निकास;
	पूर्ण

	/* Copy our capabilities from MII_BMSR to MII_ADVERTISE */
	my_phy_caps = smc_phy_पढ़ो(dev, phyaddr, MII_BMSR);

	अगर (!(my_phy_caps & BMSR_ANEGCAPABLE)) अणु
		netdev_info(dev, "Auto negotiation NOT supported\n");
		smc_phy_fixed(dev);
		जाओ smc_phy_configure_निकास;
	पूर्ण

	my_ad_caps = ADVERTISE_CSMA; /* I am CSMA capable */

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
	smc_phy_ग_लिखो(dev, phyaddr, MII_ADVERTISE, my_ad_caps);
	lp->mii.advertising = my_ad_caps;

	/*
	 * Read the रेजिस्टर back.  Without this, it appears that when
	 * स्वतः-negotiation is restarted, someबार it isn't पढ़ोy and
	 * the link करोes not come up.
	 */
	smc_phy_पढ़ो(dev, phyaddr, MII_ADVERTISE);

	DBG(2, dev, "phy caps=%x\n", my_phy_caps);
	DBG(2, dev, "phy advertised caps=%x\n", my_ad_caps);

	/* Restart स्वतः-negotiation process in order to advertise my caps */
	smc_phy_ग_लिखो(dev, phyaddr, MII_BMCR, BMCR_ANENABLE | BMCR_ANRESTART);

	smc_phy_check_media(dev, 1);

smc_phy_configure_निकास:
	SMC_SELECT_BANK(lp, 2);
	spin_unlock_irq(&lp->lock);
पूर्ण

/*
 * smc_phy_पूर्णांकerrupt
 *
 * Purpose:  Handle पूर्णांकerrupts relating to PHY रेजिस्टर 18. This is
 *  called from the "hard" पूर्णांकerrupt handler under our निजी spinlock.
 */
अटल व्योम smc_phy_पूर्णांकerrupt(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	पूर्णांक phyaddr = lp->mii.phy_id;
	पूर्णांक phy18;

	DBG(2, dev, "%s\n", __func__);

	अगर (lp->phy_type == 0)
		वापस;

	क्रम(;;) अणु
		smc_phy_check_media(dev, 0);

		/* Read PHY Register 18, Status Output */
		phy18 = smc_phy_पढ़ो(dev, phyaddr, PHY_INT_REG);
		अगर ((phy18 & PHY_INT_INT) == 0)
			अवरोध;
	पूर्ण
पूर्ण

/*--- END PHY CONTROL AND CONFIGURATION-------------------------------------*/

अटल व्योम smc_10bt_check_media(काष्ठा net_device *dev, पूर्णांक init)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित पूर्णांक old_carrier, new_carrier;

	old_carrier = netअगर_carrier_ok(dev) ? 1 : 0;

	SMC_SELECT_BANK(lp, 0);
	new_carrier = (SMC_GET_EPH_STATUS(lp) & ES_LINK_OK) ? 1 : 0;
	SMC_SELECT_BANK(lp, 2);

	अगर (init || (old_carrier != new_carrier)) अणु
		अगर (!new_carrier) अणु
			netअगर_carrier_off(dev);
		पूर्ण अन्यथा अणु
			netअगर_carrier_on(dev);
		पूर्ण
		अगर (netअगर_msg_link(lp))
			netdev_info(dev, "link %s\n",
				    new_carrier ? "up" : "down");
	पूर्ण
पूर्ण

अटल व्योम smc_eph_पूर्णांकerrupt(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित पूर्णांक ctl;

	smc_10bt_check_media(dev, 0);

	SMC_SELECT_BANK(lp, 1);
	ctl = SMC_GET_CTL(lp);
	SMC_SET_CTL(lp, ctl & ~CTL_LE_ENABLE);
	SMC_SET_CTL(lp, ctl);
	SMC_SELECT_BANK(lp, 2);
पूर्ण

/*
 * This is the मुख्य routine of the driver, to handle the device when
 * it needs some attention.
 */
अटल irqवापस_t smc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	पूर्णांक status, mask, समयout, card_stats;
	पूर्णांक saved_poपूर्णांकer;

	DBG(3, dev, "%s\n", __func__);

	spin_lock(&lp->lock);

	/* A preamble may be used when there is a potential race
	 * between the पूर्णांकerruptible transmit functions and this
	 * ISR. */
	SMC_INTERRUPT_PREAMBLE;

	saved_poपूर्णांकer = SMC_GET_PTR(lp);
	mask = SMC_GET_INT_MASK(lp);
	SMC_SET_INT_MASK(lp, 0);

	/* set a समयout value, so I करोn't stay here क्रमever */
	समयout = MAX_IRQ_LOOPS;

	करो अणु
		status = SMC_GET_INT(lp);

		DBG(2, dev, "INT 0x%02x MASK 0x%02x MEM 0x%04x FIFO 0x%04x\n",
		    status, mask,
		    (अणु पूर्णांक meminfo; SMC_SELECT_BANK(lp, 0);
		       meminfo = SMC_GET_MIR(lp);
		       SMC_SELECT_BANK(lp, 2); meminfo; पूर्ण),
		    SMC_GET_FIFO(lp));

		status &= mask;
		अगर (!status)
			अवरोध;

		अगर (status & IM_TX_INT) अणु
			/* करो this beक्रमe RX as it will मुक्त memory quickly */
			DBG(3, dev, "TX int\n");
			smc_tx(dev);
			SMC_ACK_INT(lp, IM_TX_INT);
			अगर (THROTTLE_TX_PKTS)
				netअगर_wake_queue(dev);
		पूर्ण अन्यथा अगर (status & IM_RCV_INT) अणु
			DBG(3, dev, "RX irq\n");
			smc_rcv(dev);
		पूर्ण अन्यथा अगर (status & IM_ALLOC_INT) अणु
			DBG(3, dev, "Allocation irq\n");
			tasklet_hi_schedule(&lp->tx_task);
			mask &= ~IM_ALLOC_INT;
		पूर्ण अन्यथा अगर (status & IM_TX_EMPTY_INT) अणु
			DBG(3, dev, "TX empty\n");
			mask &= ~IM_TX_EMPTY_INT;

			/* update stats */
			SMC_SELECT_BANK(lp, 0);
			card_stats = SMC_GET_COUNTER(lp);
			SMC_SELECT_BANK(lp, 2);

			/* single collisions */
			dev->stats.collisions += card_stats & 0xF;
			card_stats >>= 4;

			/* multiple collisions */
			dev->stats.collisions += card_stats & 0xF;
		पूर्ण अन्यथा अगर (status & IM_RX_OVRN_INT) अणु
			DBG(1, dev, "RX overrun (EPH_ST 0x%04x)\n",
			    (अणु पूर्णांक eph_st; SMC_SELECT_BANK(lp, 0);
			       eph_st = SMC_GET_EPH_STATUS(lp);
			       SMC_SELECT_BANK(lp, 2); eph_st; पूर्ण));
			SMC_ACK_INT(lp, IM_RX_OVRN_INT);
			dev->stats.rx_errors++;
			dev->stats.rx_fअगरo_errors++;
		पूर्ण अन्यथा अगर (status & IM_EPH_INT) अणु
			smc_eph_पूर्णांकerrupt(dev);
		पूर्ण अन्यथा अगर (status & IM_MDINT) अणु
			SMC_ACK_INT(lp, IM_MDINT);
			smc_phy_पूर्णांकerrupt(dev);
		पूर्ण अन्यथा अगर (status & IM_ERCV_INT) अणु
			SMC_ACK_INT(lp, IM_ERCV_INT);
			PRINTK(dev, "UNSUPPORTED: ERCV INTERRUPT\n");
		पूर्ण
	पूर्ण जबतक (--समयout);

	/* restore रेजिस्टर states */
	SMC_SET_PTR(lp, saved_poपूर्णांकer);
	SMC_SET_INT_MASK(lp, mask);
	spin_unlock(&lp->lock);

#अगर_अघोषित CONFIG_NET_POLL_CONTROLLER
	अगर (समयout == MAX_IRQ_LOOPS)
		PRINTK(dev, "spurious interrupt (mask = 0x%02x)\n",
		       mask);
#पूर्ण_अगर
	DBG(3, dev, "Interrupt done (%d loops)\n",
	    MAX_IRQ_LOOPS - समयout);

	/*
	 * We वापस IRQ_HANDLED unconditionally here even अगर there was
	 * nothing to करो.  There is a possibility that a packet might
	 * get enqueued पूर्णांकo the chip right after TX_EMPTY_INT is उठाओd
	 * but just beक्रमe the CPU acknowledges the IRQ.
	 * Better take an unneeded IRQ in some occasions than complexअगरying
	 * the code क्रम all हालs.
	 */
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling receive - used by netconsole and other diagnostic tools
 * to allow network i/o with पूर्णांकerrupts disabled.
 */
अटल व्योम smc_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	smc_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/* Our watchकरोg समयd out. Called by the networking layer */
अटल व्योम smc_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	पूर्णांक status, mask, eph_st, meminfo, fअगरo;

	DBG(2, dev, "%s\n", __func__);

	spin_lock_irq(&lp->lock);
	status = SMC_GET_INT(lp);
	mask = SMC_GET_INT_MASK(lp);
	fअगरo = SMC_GET_FIFO(lp);
	SMC_SELECT_BANK(lp, 0);
	eph_st = SMC_GET_EPH_STATUS(lp);
	meminfo = SMC_GET_MIR(lp);
	SMC_SELECT_BANK(lp, 2);
	spin_unlock_irq(&lp->lock);
	PRINTK(dev, "TX timeout (INT 0x%02x INTMASK 0x%02x MEM 0x%04x FIFO 0x%04x EPH_ST 0x%04x)\n",
	       status, mask, meminfo, fअगरo, eph_st);

	smc_reset(dev);
	smc_enable(dev);

	/*
	 * Reconfiguring the PHY करोesn't seem like a bad idea here, but
	 * smc_phy_configure() calls msleep() which calls schedule_समयout()
	 * which calls schedule().  Hence we use a work queue.
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
अटल व्योम smc_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;
	अचिन्हित अक्षर multicast_table[8];
	पूर्णांक update_multicast = 0;

	DBG(2, dev, "%s\n", __func__);

	अगर (dev->flags & IFF_PROMISC) अणु
		DBG(2, dev, "RCR_PRMS\n");
		lp->rcr_cur_mode |= RCR_PRMS;
	पूर्ण

/* BUG?  I never disable promiscuous mode अगर multicasting was turned on.
   Now, I turn off promiscuous mode, but I करोn't करो anything to multicasting
   when promiscuous mode is turned on.
*/

	/*
	 * Here, I am setting this to accept all multicast packets.
	 * I करोn't need to zero the multicast table, because the flag is
	 * checked beक्रमe the table is
	 */
	अन्यथा अगर (dev->flags & IFF_ALLMULTI || netdev_mc_count(dev) > 16) अणु
		DBG(2, dev, "RCR_ALMUL\n");
		lp->rcr_cur_mode |= RCR_ALMUL;
	पूर्ण

	/*
	 * This sets the पूर्णांकernal hardware table to filter out unwanted
	 * multicast packets beक्रमe they take up memory.
	 *
	 * The SMC chip uses a hash table where the high 6 bits of the CRC of
	 * address are the offset पूर्णांकo the table.  If that bit is 1, then the
	 * multicast packet is accepted.  Otherwise, it's dropped silently.
	 *
	 * To use the 6 bits as an offset पूर्णांकo the table, the high 3 bits are
	 * the number of the 8 bit रेजिस्टर, जबतक the low 3 bits are the bit
	 * within that रेजिस्टर.
	 */
	अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;

		/* table क्रम flipping the order of 3 bits */
		अटल स्थिर अचिन्हित अक्षर invert3[] = अणु0, 4, 2, 6, 1, 5, 3, 7पूर्ण;

		/* start with a table of all zeros: reject all */
		स_रखो(multicast_table, 0, माप(multicast_table));

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			पूर्णांक position;

			/* only use the low order bits */
			position = crc32_le(~0, ha->addr, 6) & 0x3f;

			/* करो some messy swapping to put the bit in the right spot */
			multicast_table[invert3[position&7]] |=
				(1<<invert3[(position>>3)&7]);
		पूर्ण

		/* be sure I get rid of flags I might have set */
		lp->rcr_cur_mode &= ~(RCR_PRMS | RCR_ALMUL);

		/* now, the table can be loaded पूर्णांकo the chipset */
		update_multicast = 1;
	पूर्ण अन्यथा  अणु
		DBG(2, dev, "~(RCR_PRMS|RCR_ALMUL)\n");
		lp->rcr_cur_mode &= ~(RCR_PRMS | RCR_ALMUL);

		/*
		 * since I'm disabling all multicast entirely, I need to
		 * clear the multicast list
		 */
		स_रखो(multicast_table, 0, माप(multicast_table));
		update_multicast = 1;
	पूर्ण

	spin_lock_irq(&lp->lock);
	SMC_SELECT_BANK(lp, 0);
	SMC_SET_RCR(lp, lp->rcr_cur_mode);
	अगर (update_multicast) अणु
		SMC_SELECT_BANK(lp, 3);
		SMC_SET_MCAST(lp, multicast_table);
	पूर्ण
	SMC_SELECT_BANK(lp, 2);
	spin_unlock_irq(&lp->lock);
पूर्ण


/*
 * Open and Initialize the board
 *
 * Set up everything, reset the card, etc..
 */
अटल पूर्णांक
smc_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);

	DBG(2, dev, "%s\n", __func__);

	/* Setup the शेष Register Modes */
	lp->tcr_cur_mode = TCR_DEFAULT;
	lp->rcr_cur_mode = RCR_DEFAULT;
	lp->rpc_cur_mode = RPC_DEFAULT |
				lp->cfg.leda << RPC_LSXA_SHFT |
				lp->cfg.ledb << RPC_LSXB_SHFT;

	/*
	 * If we are not using a MII पूर्णांकerface, we need to
	 * monitor our own carrier संकेत to detect faults.
	 */
	अगर (lp->phy_type == 0)
		lp->tcr_cur_mode |= TCR_MON_CSN;

	/* reset the hardware */
	smc_reset(dev);
	smc_enable(dev);

	/* Configure the PHY, initialize the link state */
	अगर (lp->phy_type != 0)
		smc_phy_configure(&lp->phy_configure);
	अन्यथा अणु
		spin_lock_irq(&lp->lock);
		smc_10bt_check_media(dev, 1);
		spin_unlock_irq(&lp->lock);
	पूर्ण

	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

/*
 * smc_बंद
 *
 * this makes the board clean up everything that it can
 * and not talk to the outside world.   Caused by
 * an 'ifconfig ethX down'
 */
अटल पूर्णांक smc_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);

	DBG(2, dev, "%s\n", __func__);

	netअगर_stop_queue(dev);
	netअगर_carrier_off(dev);

	/* clear everything */
	smc_shutकरोwn(dev);
	tasklet_समाप्त(&lp->tx_task);
	smc_phy_घातerकरोwn(dev);
	वापस 0;
पूर्ण

/*
 * Ethtool support
 */
अटल पूर्णांक
smc_ethtool_get_link_ksettings(काष्ठा net_device *dev,
			       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);

	अगर (lp->phy_type != 0) अणु
		spin_lock_irq(&lp->lock);
		mii_ethtool_get_link_ksettings(&lp->mii, cmd);
		spin_unlock_irq(&lp->lock);
	पूर्ण अन्यथा अणु
		u32 supported = SUPPORTED_10baseT_Half |
				 SUPPORTED_10baseT_Full |
				 SUPPORTED_TP | SUPPORTED_AUI;

		अगर (lp->ctl_rspeed == 10)
			cmd->base.speed = SPEED_10;
		अन्यथा अगर (lp->ctl_rspeed == 100)
			cmd->base.speed = SPEED_100;

		cmd->base.स्वतःneg = AUTONEG_DISABLE;
		cmd->base.port = 0;
		cmd->base.duplex = lp->tcr_cur_mode & TCR_SWFDUP ?
			DUPLEX_FULL : DUPLEX_HALF;

		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported, supported);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
smc_ethtool_set_link_ksettings(काष्ठा net_device *dev,
			       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	पूर्णांक ret;

	अगर (lp->phy_type != 0) अणु
		spin_lock_irq(&lp->lock);
		ret = mii_ethtool_set_link_ksettings(&lp->mii, cmd);
		spin_unlock_irq(&lp->lock);
	पूर्ण अन्यथा अणु
		अगर (cmd->base.स्वतःneg != AUTONEG_DISABLE ||
		    cmd->base.speed != SPEED_10 ||
		    (cmd->base.duplex != DUPLEX_HALF &&
		     cmd->base.duplex != DUPLEX_FULL) ||
		    (cmd->base.port != PORT_TP && cmd->base.port != PORT_AUI))
			वापस -EINVAL;

//		lp->port = cmd->base.port;
		lp->ctl_rfduplx = cmd->base.duplex == DUPLEX_FULL;

//		अगर (netअगर_running(dev))
//			smc_set_port(dev);

		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
smc_ethtool_getdrvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, CARDNAME, माप(info->driver));
	strlcpy(info->version, version, माप(info->version));
	strlcpy(info->bus_info, dev_name(dev->dev.parent),
		माप(info->bus_info));
पूर्ण

अटल पूर्णांक smc_ethtool_nwayreset(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	पूर्णांक ret = -EINVAL;

	अगर (lp->phy_type != 0) अणु
		spin_lock_irq(&lp->lock);
		ret = mii_nway_restart(&lp->mii);
		spin_unlock_irq(&lp->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 smc_ethtool_geपंचांगsglevel(काष्ठा net_device *dev)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	वापस lp->msg_enable;
पूर्ण

अटल व्योम smc_ethtool_seपंचांगsglevel(काष्ठा net_device *dev, u32 level)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	lp->msg_enable = level;
पूर्ण

अटल पूर्णांक smc_ग_लिखो_eeprom_word(काष्ठा net_device *dev, u16 addr, u16 word)
अणु
	u16 ctl;
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;

	spin_lock_irq(&lp->lock);
	/* load word पूर्णांकo GP रेजिस्टर */
	SMC_SELECT_BANK(lp, 1);
	SMC_SET_GP(lp, word);
	/* set the address to put the data in EEPROM */
	SMC_SELECT_BANK(lp, 2);
	SMC_SET_PTR(lp, addr);
	/* tell it to ग_लिखो */
	SMC_SELECT_BANK(lp, 1);
	ctl = SMC_GET_CTL(lp);
	SMC_SET_CTL(lp, ctl | (CTL_EEPROM_SELECT | CTL_STORE));
	/* रुको क्रम it to finish */
	करो अणु
		udelay(1);
	पूर्ण जबतक (SMC_GET_CTL(lp) & CTL_STORE);
	/* clean up */
	SMC_SET_CTL(lp, ctl);
	SMC_SELECT_BANK(lp, 2);
	spin_unlock_irq(&lp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक smc_पढ़ो_eeprom_word(काष्ठा net_device *dev, u16 addr, u16 *word)
अणु
	u16 ctl;
	काष्ठा smc_local *lp = netdev_priv(dev);
	व्योम __iomem *ioaddr = lp->base;

	spin_lock_irq(&lp->lock);
	/* set the EEPROM address to get the data from */
	SMC_SELECT_BANK(lp, 2);
	SMC_SET_PTR(lp, addr | PTR_READ);
	/* tell it to load */
	SMC_SELECT_BANK(lp, 1);
	SMC_SET_GP(lp, 0xffff);	/* init to known */
	ctl = SMC_GET_CTL(lp);
	SMC_SET_CTL(lp, ctl | (CTL_EEPROM_SELECT | CTL_RELOAD));
	/* रुको क्रम it to finish */
	करो अणु
		udelay(1);
	पूर्ण जबतक (SMC_GET_CTL(lp) & CTL_RELOAD);
	/* पढ़ो word from GP रेजिस्टर */
	*word = SMC_GET_GP(lp);
	/* clean up */
	SMC_SET_CTL(lp, ctl);
	SMC_SELECT_BANK(lp, 2);
	spin_unlock_irq(&lp->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक smc_ethtool_geteeprom_len(काष्ठा net_device *dev)
अणु
	वापस 0x23 * 2;
पूर्ण

अटल पूर्णांक smc_ethtool_geteeprom(काष्ठा net_device *dev,
		काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	पूर्णांक i;
	पूर्णांक imax;

	DBG(1, dev, "Reading %d bytes at %d(0x%x)\n",
		eeprom->len, eeprom->offset, eeprom->offset);
	imax = smc_ethtool_geteeprom_len(dev);
	क्रम (i = 0; i < eeprom->len; i += 2) अणु
		पूर्णांक ret;
		u16 wbuf;
		पूर्णांक offset = i + eeprom->offset;
		अगर (offset > imax)
			अवरोध;
		ret = smc_पढ़ो_eeprom_word(dev, offset >> 1, &wbuf);
		अगर (ret != 0)
			वापस ret;
		DBG(2, dev, "Read 0x%x from 0x%x\n", wbuf, offset >> 1);
		data[i] = (wbuf >> 8) & 0xff;
		data[i+1] = wbuf & 0xff;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smc_ethtool_seteeprom(काष्ठा net_device *dev,
		काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	पूर्णांक i;
	पूर्णांक imax;

	DBG(1, dev, "Writing %d bytes to %d(0x%x)\n",
	    eeprom->len, eeprom->offset, eeprom->offset);
	imax = smc_ethtool_geteeprom_len(dev);
	क्रम (i = 0; i < eeprom->len; i += 2) अणु
		पूर्णांक ret;
		u16 wbuf;
		पूर्णांक offset = i + eeprom->offset;
		अगर (offset > imax)
			अवरोध;
		wbuf = (data[i] << 8) | data[i + 1];
		DBG(2, dev, "Writing 0x%x to 0x%x\n", wbuf, offset >> 1);
		ret = smc_ग_लिखो_eeprom_word(dev, offset >> 1, wbuf);
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा ethtool_ops smc_ethtool_ops = अणु
	.get_drvinfo	= smc_ethtool_getdrvinfo,

	.get_msglevel	= smc_ethtool_geपंचांगsglevel,
	.set_msglevel	= smc_ethtool_seपंचांगsglevel,
	.nway_reset	= smc_ethtool_nwayreset,
	.get_link	= ethtool_op_get_link,
	.get_eeprom_len = smc_ethtool_geteeprom_len,
	.get_eeprom	= smc_ethtool_geteeprom,
	.set_eeprom	= smc_ethtool_seteeprom,
	.get_link_ksettings	= smc_ethtool_get_link_ksettings,
	.set_link_ksettings	= smc_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops smc_netdev_ops = अणु
	.nकरो_खोलो		= smc_खोलो,
	.nकरो_stop		= smc_बंद,
	.nकरो_start_xmit		= smc_hard_start_xmit,
	.nकरो_tx_समयout		= smc_समयout,
	.nकरो_set_rx_mode	= smc_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= smc_poll_controller,
#पूर्ण_अगर
पूर्ण;

/*
 * smc_findirq
 *
 * This routine has a simple purpose -- make the SMC chip generate an
 * पूर्णांकerrupt, so an स्वतः-detect routine can detect it, and find the IRQ,
 */
/*
 * करोes this still work?
 *
 * I just deleted स्वतः_irq.c, since it was never built...
 *   --jgarzik
 */
अटल पूर्णांक smc_findirq(काष्ठा smc_local *lp)
अणु
	व्योम __iomem *ioaddr = lp->base;
	पूर्णांक समयout = 20;
	अचिन्हित दीर्घ cookie;

	DBG(2, lp->dev, "%s: %s\n", CARDNAME, __func__);

	cookie = probe_irq_on();

	/*
	 * What I try to करो here is trigger an ALLOC_INT. This is करोne
	 * by allocating a small chunk of memory, which will give an पूर्णांकerrupt
	 * when करोne.
	 */
	/* enable ALLOCation पूर्णांकerrupts ONLY */
	SMC_SELECT_BANK(lp, 2);
	SMC_SET_INT_MASK(lp, IM_ALLOC_INT);

	/*
 	 * Allocate 512 bytes of memory.  Note that the chip was just
	 * reset so all the memory is available
	 */
	SMC_SET_MMU_CMD(lp, MC_ALLOC | 1);

	/*
	 * Wait until positive that the पूर्णांकerrupt has been generated
	 */
	करो अणु
		पूर्णांक पूर्णांक_status;
		udelay(10);
		पूर्णांक_status = SMC_GET_INT(lp);
		अगर (पूर्णांक_status & IM_ALLOC_INT)
			अवरोध;		/* got the पूर्णांकerrupt */
	पूर्ण जबतक (--समयout);

	/*
	 * there is really nothing that I can करो here अगर समयout fails,
	 * as स्वतःirq_report will वापस a 0 anyway, which is what I
	 * want in this हाल.   Plus, the clean up is needed in both
	 * हालs.
	 */

	/* and disable all पूर्णांकerrupts again */
	SMC_SET_INT_MASK(lp, 0);

	/* and वापस what I found */
	वापस probe_irq_off(cookie);
पूर्ण

/*
 * Function: smc_probe(अचिन्हित दीर्घ ioaddr)
 *
 * Purpose:
 *	Tests to see अगर a given ioaddr poपूर्णांकs to an SMC91x chip.
 *	Returns a 0 on success
 *
 * Algorithm:
 *	(1) see अगर the high byte of BANK_SELECT is 0x33
 * 	(2) compare the ioaddr with the base रेजिस्टर's address
 *	(3) see अगर I recognize the chip ID in the appropriate रेजिस्टर
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
अटल पूर्णांक smc_probe(काष्ठा net_device *dev, व्योम __iomem *ioaddr,
		     अचिन्हित दीर्घ irq_flags)
अणु
	काष्ठा smc_local *lp = netdev_priv(dev);
	पूर्णांक retval;
	अचिन्हित पूर्णांक val, revision_रेजिस्टर;
	स्थिर अक्षर *version_string;

	DBG(2, dev, "%s: %s\n", CARDNAME, __func__);

	/* First, see अगर the high byte is 0x33 */
	val = SMC_CURRENT_BANK(lp);
	DBG(2, dev, "%s: bank signature probe returned 0x%04x\n",
	    CARDNAME, val);
	अगर ((val & 0xFF00) != 0x3300) अणु
		अगर ((val & 0xFF) == 0x33) अणु
			netdev_warn(dev,
				    "%s: Detected possible byte-swapped interface at IOADDR %p\n",
				    CARDNAME, ioaddr);
		पूर्ण
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण

	/*
	 * The above MIGHT indicate a device, but I need to ग_लिखो to
	 * further test this.
	 */
	SMC_SELECT_BANK(lp, 0);
	val = SMC_CURRENT_BANK(lp);
	अगर ((val & 0xFF00) != 0x3300) अणु
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण

	/*
	 * well, we've alपढ़ोy written once, so hopefully another
	 * समय won't hurt.  This समय, I need to चयन the bank
	 * रेजिस्टर to bank 1, so I can access the base address
	 * रेजिस्टर
	 */
	SMC_SELECT_BANK(lp, 1);
	val = SMC_GET_BASE(lp);
	val = ((val & 0x1F00) >> 3) << SMC_IO_SHIFT;
	अगर (((अचिन्हित दीर्घ)ioaddr & (0x3e0 << SMC_IO_SHIFT)) != val) अणु
		netdev_warn(dev, "%s: IOADDR %p doesn't match configuration (%x).\n",
			    CARDNAME, ioaddr, val);
	पूर्ण

	/*
	 * check अगर the revision रेजिस्टर is something that I
	 * recognize.  These might need to be added to later,
	 * as future revisions could be added.
	 */
	SMC_SELECT_BANK(lp, 3);
	revision_रेजिस्टर = SMC_GET_REV(lp);
	DBG(2, dev, "%s: revision = 0x%04x\n", CARDNAME, revision_रेजिस्टर);
	version_string = chip_ids[ (revision_रेजिस्टर >> 4) & 0xF];
	अगर (!version_string || (revision_रेजिस्टर & 0xff00) != 0x3300) अणु
		/* I करोn't recognize this chip, so... */
		netdev_warn(dev, "%s: IO %p: Unrecognized revision register 0x%04x, Contact author.\n",
			    CARDNAME, ioaddr, revision_रेजिस्टर);

		retval = -ENODEV;
		जाओ err_out;
	पूर्ण

	/* At this poपूर्णांक I'll assume that the chip is an SMC91x. */
	pr_info_once("%s\n", version);

	/* fill in some of the fields */
	dev->base_addr = (अचिन्हित दीर्घ)ioaddr;
	lp->base = ioaddr;
	lp->version = revision_रेजिस्टर & 0xff;
	spin_lock_init(&lp->lock);

	/* Get the MAC address */
	SMC_SELECT_BANK(lp, 1);
	SMC_GET_MAC_ADDR(lp, dev->dev_addr);

	/* now, reset the chip, and put it पूर्णांकo a known state */
	smc_reset(dev);

	/*
	 * If dev->irq is 0, then the device has to be banged on to see
	 * what the IRQ is.
	 *
	 * This banging करोesn't always detect the IRQ, क्रम unknown reasons.
	 * a workaround is to reset the chip and try again.
	 *
	 * Interestingly, the DOS packet driver *SETS* the IRQ on the card to
	 * be what is requested on the command line.   I करोn't करो that, mostly
	 * because the card that I have uses a non-standard method of accessing
	 * the IRQs, and because this _should_ work in most configurations.
	 *
	 * Specअगरying an IRQ is करोne with the assumption that the user knows
	 * what (s)he is करोing.  No checking is करोne!!!!
	 */
	अगर (dev->irq < 1) अणु
		पूर्णांक trials;

		trials = 3;
		जबतक (trials--) अणु
			dev->irq = smc_findirq(lp);
			अगर (dev->irq)
				अवरोध;
			/* kick the card and try again */
			smc_reset(dev);
		पूर्ण
	पूर्ण
	अगर (dev->irq == 0) अणु
		netdev_warn(dev, "Couldn't autodetect your IRQ. Use irq=xx.\n");
		retval = -ENODEV;
		जाओ err_out;
	पूर्ण
	dev->irq = irq_canonicalize(dev->irq);

	dev->watchकरोg_समयo = msecs_to_jअगरfies(watchकरोg);
	dev->netdev_ops = &smc_netdev_ops;
	dev->ethtool_ops = &smc_ethtool_ops;

	tasklet_setup(&lp->tx_task, smc_hardware_send_pkt);
	INIT_WORK(&lp->phy_configure, smc_phy_configure);
	lp->dev = dev;
	lp->mii.phy_id_mask = 0x1f;
	lp->mii.reg_num_mask = 0x1f;
	lp->mii.क्रमce_media = 0;
	lp->mii.full_duplex = 0;
	lp->mii.dev = dev;
	lp->mii.mdio_पढ़ो = smc_phy_पढ़ो;
	lp->mii.mdio_ग_लिखो = smc_phy_ग_लिखो;

	/*
	 * Locate the phy, अगर any.
	 */
	अगर (lp->version >= (CHIP_91100 << 4))
		smc_phy_detect(dev);

	/* then shut everything करोwn to save घातer */
	smc_shutकरोwn(dev);
	smc_phy_घातerकरोwn(dev);

	/* Set शेष parameters */
	lp->msg_enable = NETIF_MSG_LINK;
	lp->ctl_rfduplx = 0;
	lp->ctl_rspeed = 10;

	अगर (lp->version >= (CHIP_91100 << 4)) अणु
		lp->ctl_rfduplx = 1;
		lp->ctl_rspeed = 100;
	पूर्ण

	/* Grab the IRQ */
	retval = request_irq(dev->irq, smc_पूर्णांकerrupt, irq_flags, dev->name, dev);
      	अगर (retval)
      		जाओ err_out;

#अगर_घोषित CONFIG_ARCH_PXA
#  अगरdef SMC_USE_PXA_DMA
	lp->cfg.flags |= SMC91X_USE_DMA;
#  endअगर
	अगर (lp->cfg.flags & SMC91X_USE_DMA) अणु
		dma_cap_mask_t mask;

		dma_cap_zero(mask);
		dma_cap_set(DMA_SLAVE, mask);
		lp->dma_chan = dma_request_channel(mask, शून्य, शून्य);
	पूर्ण
#पूर्ण_अगर

	retval = रेजिस्टर_netdev(dev);
	अगर (retval == 0) अणु
		/* now, prपूर्णांक out the card info, in a लघु क्रमmat.. */
		netdev_info(dev, "%s (rev %d) at %p IRQ %d",
			    version_string, revision_रेजिस्टर & 0x0f,
			    lp->base, dev->irq);

		अगर (lp->dma_chan)
			pr_cont(" DMA %p", lp->dma_chan);

		pr_cont("%s%s\n",
			lp->cfg.flags & SMC91X_NOWAIT ? " [nowait]" : "",
			THROTTLE_TX_PKTS ? " [throttle_tx]" : "");

		अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
			netdev_warn(dev, "Invalid ethernet MAC address. Please set using ifconfig\n");
		पूर्ण अन्यथा अणु
			/* Prपूर्णांक the Ethernet address */
			netdev_info(dev, "Ethernet addr: %pM\n",
				    dev->dev_addr);
		पूर्ण

		अगर (lp->phy_type == 0) अणु
			PRINTK(dev, "No PHY found\n");
		पूर्ण अन्यथा अगर ((lp->phy_type & 0xfffffff0) == 0x0016f840) अणु
			PRINTK(dev, "PHY LAN83C183 (LAN91C111 Internal)\n");
		पूर्ण अन्यथा अगर ((lp->phy_type & 0xfffffff0) == 0x02821c50) अणु
			PRINTK(dev, "PHY LAN83C180\n");
		पूर्ण
	पूर्ण

err_out:
#अगर_घोषित CONFIG_ARCH_PXA
	अगर (retval && lp->dma_chan)
		dma_release_channel(lp->dma_chan);
#पूर्ण_अगर
	वापस retval;
पूर्ण

अटल पूर्णांक smc_enable_device(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा smc_local *lp = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर ecor, ecsr;
	व्योम __iomem *addr;
	काष्ठा resource * res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "smc91x-attrib");
	अगर (!res)
		वापस 0;

	/*
	 * Map the attribute space.  This is overसमाप्त, but clean.
	 */
	addr = ioremap(res->start, ATTRIB_SIZE);
	अगर (!addr)
		वापस -ENOMEM;

	/*
	 * Reset the device.  We must disable IRQs around this
	 * since a reset causes the IRQ line become active.
	 */
	local_irq_save(flags);
	ecor = पढ़ोb(addr + (ECOR << SMC_IO_SHIFT)) & ~ECOR_RESET;
	ग_लिखोb(ecor | ECOR_RESET, addr + (ECOR << SMC_IO_SHIFT));
	पढ़ोb(addr + (ECOR << SMC_IO_SHIFT));

	/*
	 * Wait 100us क्रम the chip to reset.
	 */
	udelay(100);

	/*
	 * The device will ignore all ग_लिखोs to the enable bit जबतक
	 * reset is निश्चितed, even अगर the reset bit is cleared in the
	 * same ग_लिखो.  Must clear reset first, then enable the device.
	 */
	ग_लिखोb(ecor, addr + (ECOR << SMC_IO_SHIFT));
	ग_लिखोb(ecor | ECOR_ENABLE, addr + (ECOR << SMC_IO_SHIFT));

	/*
	 * Set the appropriate byte/word mode.
	 */
	ecsr = पढ़ोb(addr + (ECSR << SMC_IO_SHIFT)) & ~ECSR_IOIS8;
	अगर (!SMC_16BIT(lp))
		ecsr |= ECSR_IOIS8;
	ग_लिखोb(ecsr, addr + (ECSR << SMC_IO_SHIFT));
	local_irq_restore(flags);

	iounmap(addr);

	/*
	 * Wait क्रम the chip to wake up.  We could poll the control
	 * रेजिस्टर in the मुख्य रेजिस्टर space, but that isn't mapped
	 * yet.  We know this is going to take 750us.
	 */
	msleep(1);

	वापस 0;
पूर्ण

अटल पूर्णांक smc_request_attrib(काष्ठा platक्रमm_device *pdev,
			      काष्ठा net_device *ndev)
अणु
	काष्ठा resource * res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "smc91x-attrib");
	काष्ठा smc_local *lp __maybe_unused = netdev_priv(ndev);

	अगर (!res)
		वापस 0;

	अगर (!request_mem_region(res->start, ATTRIB_SIZE, CARDNAME))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम smc_release_attrib(काष्ठा platक्रमm_device *pdev,
			       काष्ठा net_device *ndev)
अणु
	काष्ठा resource * res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "smc91x-attrib");
	काष्ठा smc_local *lp __maybe_unused = netdev_priv(ndev);

	अगर (res)
		release_mem_region(res->start, ATTRIB_SIZE);
पूर्ण

अटल अंतरभूत व्योम smc_request_datacs(काष्ठा platक्रमm_device *pdev, काष्ठा net_device *ndev)
अणु
	अगर (SMC_CAN_USE_DATACS) अणु
		काष्ठा resource * res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "smc91x-data32");
		काष्ठा smc_local *lp = netdev_priv(ndev);

		अगर (!res)
			वापस;

		अगर(!request_mem_region(res->start, SMC_DATA_EXTENT, CARDNAME)) अणु
			netdev_info(ndev, "%s: failed to request datacs memory region.\n",
				    CARDNAME);
			वापस;
		पूर्ण

		lp->datacs = ioremap(res->start, SMC_DATA_EXTENT);
	पूर्ण
पूर्ण

अटल व्योम smc_release_datacs(काष्ठा platक्रमm_device *pdev, काष्ठा net_device *ndev)
अणु
	अगर (SMC_CAN_USE_DATACS) अणु
		काष्ठा smc_local *lp = netdev_priv(ndev);
		काष्ठा resource * res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "smc91x-data32");

		अगर (lp->datacs)
			iounmap(lp->datacs);

		lp->datacs = शून्य;

		अगर (res)
			release_mem_region(res->start, SMC_DATA_EXTENT);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा acpi_device_id smc91x_acpi_match[] = अणु
	अणु "LNRO0003", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, smc91x_acpi_match);

#अगर IS_BUILTIN(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id smc91x_match[] = अणु
	अणु .compatible = "smsc,lan91c94", पूर्ण,
	अणु .compatible = "smsc,lan91c111", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, smc91x_match);

/**
 * try_toggle_control_gpio - configure a gpio अगर it exists
 * @dev: net device
 * @desc: where to store the GPIO descriptor, अगर it exists
 * @name: name of the GPIO in DT
 * @index: index of the GPIO in DT
 * @value: set the GPIO to this value
 * @nsdelay: delay beक्रमe setting the GPIO
 */
अटल पूर्णांक try_toggle_control_gpio(काष्ठा device *dev,
				   काष्ठा gpio_desc **desc,
				   स्थिर अक्षर *name, पूर्णांक index,
				   पूर्णांक value, अचिन्हित पूर्णांक nsdelay)
अणु
	काष्ठा gpio_desc *gpio;
	क्रमागत gpiod_flags flags = value ? GPIOD_OUT_LOW : GPIOD_OUT_HIGH;

	gpio = devm_gpiod_get_index_optional(dev, name, index, flags);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	अगर (gpio) अणु
		अगर (nsdelay)
			usleep_range(nsdelay, 2 * nsdelay);
		gpiod_set_value_cansleep(gpio, value);
	पूर्ण
	*desc = gpio;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * smc_init(व्योम)
 *   Input parameters:
 *	dev->base_addr == 0, try to find all possible locations
 *	dev->base_addr > 0x1ff, this is the address to check
 *	dev->base_addr == <anything अन्यथा>, वापस failure code
 *
 *   Output:
 *	0 --> there is a device
 *	anything अन्यथा, error
 */
अटल पूर्णांक smc_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा smc91x_platdata *pd = dev_get_platdata(&pdev->dev);
	स्थिर काष्ठा of_device_id *match = शून्य;
	काष्ठा smc_local *lp;
	काष्ठा net_device *ndev;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक __iomem *addr;
	अचिन्हित दीर्घ irq_flags = SMC_IRQ_FLAGS;
	अचिन्हित दीर्घ irq_resflags;
	पूर्णांक ret;

	ndev = alloc_etherdev(माप(काष्ठा smc_local));
	अगर (!ndev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	SET_NETDEV_DEV(ndev, &pdev->dev);

	/* get configuration from platक्रमm data, only allow use of
	 * bus width अगर both SMC_CAN_USE_xxx and SMC91X_USE_xxx are set.
	 */

	lp = netdev_priv(ndev);
	lp->cfg.flags = 0;

	अगर (pd) अणु
		स_नकल(&lp->cfg, pd, माप(lp->cfg));
		lp->io_shअगरt = SMC91X_IO_SHIFT(lp->cfg.flags);

		अगर (!SMC_8BIT(lp) && !SMC_16BIT(lp)) अणु
			dev_err(&pdev->dev,
				"at least one of 8-bit or 16-bit access support is required.\n");
			ret = -ENXIO;
			जाओ out_मुक्त_netdev;
		पूर्ण
	पूर्ण

#अगर IS_BUILTIN(CONFIG_OF)
	match = of_match_device(of_match_ptr(smc91x_match), &pdev->dev);
	अगर (match) अणु
		u32 val;

		/* Optional pwrdwn GPIO configured? */
		ret = try_toggle_control_gpio(&pdev->dev, &lp->घातer_gpio,
					      "power", 0, 0, 100);
		अगर (ret)
			जाओ out_मुक्त_netdev;

		/*
		 * Optional reset GPIO configured? Minimum 100 ns reset needed
		 * according to LAN91C96 datasheet page 14.
		 */
		ret = try_toggle_control_gpio(&pdev->dev, &lp->reset_gpio,
					      "reset", 0, 0, 100);
		अगर (ret)
			जाओ out_मुक्त_netdev;

		/*
		 * Need to रुको क्रम optional EEPROM to load, max 750 us according
		 * to LAN91C96 datasheet page 55.
		 */
		अगर (lp->reset_gpio)
			usleep_range(750, 1000);

		/* Combination of IO widths supported, शेष to 16-bit */
		अगर (!device_property_पढ़ो_u32(&pdev->dev, "reg-io-width",
					      &val)) अणु
			अगर (val & 1)
				lp->cfg.flags |= SMC91X_USE_8BIT;
			अगर ((val == 0) || (val & 2))
				lp->cfg.flags |= SMC91X_USE_16BIT;
			अगर (val & 4)
				lp->cfg.flags |= SMC91X_USE_32BIT;
		पूर्ण अन्यथा अणु
			lp->cfg.flags |= SMC91X_USE_16BIT;
		पूर्ण
		अगर (!device_property_पढ़ो_u32(&pdev->dev, "reg-shift",
					      &val))
			lp->io_shअगरt = val;
		lp->cfg.pxa_u16_align4 =
			device_property_पढ़ो_bool(&pdev->dev, "pxa-u16-align4");
	पूर्ण
#पूर्ण_अगर

	अगर (!pd && !match) अणु
		lp->cfg.flags |= (SMC_CAN_USE_8BIT)  ? SMC91X_USE_8BIT  : 0;
		lp->cfg.flags |= (SMC_CAN_USE_16BIT) ? SMC91X_USE_16BIT : 0;
		lp->cfg.flags |= (SMC_CAN_USE_32BIT) ? SMC91X_USE_32BIT : 0;
		lp->cfg.flags |= (noरुको) ? SMC91X_NOWAIT : 0;
	पूर्ण

	अगर (!lp->cfg.leda && !lp->cfg.ledb) अणु
		lp->cfg.leda = RPC_LSA_DEFAULT;
		lp->cfg.ledb = RPC_LSB_DEFAULT;
	पूर्ण

	ndev->dma = (अचिन्हित अक्षर)-1;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "smc91x-regs");
	अगर (!res)
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENODEV;
		जाओ out_मुक्त_netdev;
	पूर्ण


	अगर (!request_mem_region(res->start, SMC_IO_EXTENT, CARDNAME)) अणु
		ret = -EBUSY;
		जाओ out_मुक्त_netdev;
	पूर्ण

	ndev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ndev->irq < 0) अणु
		ret = ndev->irq;
		जाओ out_release_io;
	पूर्ण
	/*
	 * If this platक्रमm करोes not specअगरy any special irqflags, or अगर
	 * the resource supplies a trigger, override the irqflags with
	 * the trigger flags from the resource.
	 */
	irq_resflags = irqd_get_trigger_type(irq_get_irq_data(ndev->irq));
	अगर (irq_flags == -1 || irq_resflags & IRQF_TRIGGER_MASK)
		irq_flags = irq_resflags & IRQF_TRIGGER_MASK;

	ret = smc_request_attrib(pdev, ndev);
	अगर (ret)
		जाओ out_release_io;
#अगर defined(CONFIG_ASSABET_NEPONSET)
	अगर (machine_is_assabet() && machine_has_neponset())
		neponset_ncr_set(NCR_ENET_OSC_EN);
#पूर्ण_अगर
	platक्रमm_set_drvdata(pdev, ndev);
	ret = smc_enable_device(pdev);
	अगर (ret)
		जाओ out_release_attrib;

	addr = ioremap(res->start, SMC_IO_EXTENT);
	अगर (!addr) अणु
		ret = -ENOMEM;
		जाओ out_release_attrib;
	पूर्ण

#अगर_घोषित CONFIG_ARCH_PXA
	अणु
		काष्ठा smc_local *lp = netdev_priv(ndev);
		lp->device = &pdev->dev;
		lp->physaddr = res->start;

	पूर्ण
#पूर्ण_अगर

	ret = smc_probe(ndev, addr, irq_flags);
	अगर (ret != 0)
		जाओ out_iounmap;

	smc_request_datacs(pdev, ndev);

	वापस 0;

 out_iounmap:
	iounmap(addr);
 out_release_attrib:
	smc_release_attrib(pdev, ndev);
 out_release_io:
	release_mem_region(res->start, SMC_IO_EXTENT);
 out_मुक्त_netdev:
	मुक्त_netdev(ndev);
 out:
	pr_info("%s: not found (%d).\n", CARDNAME, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक smc_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा smc_local *lp = netdev_priv(ndev);
	काष्ठा resource *res;

	unरेजिस्टर_netdev(ndev);

	मुक्त_irq(ndev->irq, ndev);

#अगर_घोषित CONFIG_ARCH_PXA
	अगर (lp->dma_chan)
		dma_release_channel(lp->dma_chan);
#पूर्ण_अगर
	iounmap(lp->base);

	smc_release_datacs(pdev,ndev);
	smc_release_attrib(pdev,ndev);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "smc91x-regs");
	अगर (!res)
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, SMC_IO_EXTENT);

	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक smc_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);

	अगर (ndev) अणु
		अगर (netअगर_running(ndev)) अणु
			netअगर_device_detach(ndev);
			smc_shutकरोwn(ndev);
			smc_phy_घातerकरोwn(ndev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smc_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);

	अगर (ndev) अणु
		काष्ठा smc_local *lp = netdev_priv(ndev);
		smc_enable_device(pdev);
		अगर (netअगर_running(ndev)) अणु
			smc_reset(ndev);
			smc_enable(ndev);
			अगर (lp->phy_type != 0)
				smc_phy_configure(&lp->phy_configure);
			netअगर_device_attach(ndev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops smc_drv_pm_ops = अणु
	.suspend	= smc_drv_suspend,
	.resume		= smc_drv_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver smc_driver = अणु
	.probe		= smc_drv_probe,
	.हटाओ		= smc_drv_हटाओ,
	.driver		= अणु
		.name	= CARDNAME,
		.pm	= &smc_drv_pm_ops,
		.of_match_table   = of_match_ptr(smc91x_match),
		.acpi_match_table = smc91x_acpi_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(smc_driver);
