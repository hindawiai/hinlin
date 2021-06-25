<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* $Id: sungem.c,v 1.44.2.22 2002/03/13 01:18:12 davem Exp $
 * sungem.c: Sun GEM ethernet driver.
 *
 * Copyright (C) 2000, 2001, 2002, 2003 David S. Miller (davem@redhat.com)
 *
 * Support क्रम Apple GMAC and assorted PHYs, WOL, Power Management
 * (C) 2001,2002,2003 Benjamin Herrenscmidt (benh@kernel.crashing.org)
 * (C) 2004,2005 Benjamin Herrenscmidt, IBM Corp.
 *
 * NAPI and NETPOLL support
 * (C) 2004 by Eric Lemoine (eric.lemoine@gmail.com)
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mm.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>

#अगर_घोषित CONFIG_SPARC
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#पूर्ण_अगर

#समावेश <linux/sungem_phy.h>
#समावेश "sungem.h"

#घोषणा STRIP_FCS

#घोषणा DEFAULT_MSG	(NETIF_MSG_DRV		| \
			 NETIF_MSG_PROBE	| \
			 NETIF_MSG_LINK)

#घोषणा ADVERTISE_MASK	(SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full | \
			 SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full | \
			 SUPPORTED_1000baseT_Half | SUPPORTED_1000baseT_Full | \
			 SUPPORTED_Pause | SUPPORTED_Autoneg)

#घोषणा DRV_NAME	"sungem"
#घोषणा DRV_VERSION	"1.0"
#घोषणा DRV_AUTHOR	"David S. Miller <davem@redhat.com>"

अटल अक्षर version[] =
        DRV_NAME ".c:v" DRV_VERSION " " DRV_AUTHOR "\n";

MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION("Sun GEM Gbit ethernet driver");
MODULE_LICENSE("GPL");

#घोषणा GEM_MODULE_NAME	"gem"

अटल स्थिर काष्ठा pci_device_id gem_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_SUN, PCI_DEVICE_ID_SUN_GEM,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,

	/* These models only dअगरfer from the original GEM in
	 * that their tx/rx fअगरos are of a dअगरferent size and
	 * they only support 10/100 speeds. -DaveM
	 *
	 * Apple's GMAC करोes support gigabit on machines with
	 * the BCM54xx PHYs. -BenH
	 */
	अणु PCI_VENDOR_ID_SUN, PCI_DEVICE_ID_SUN_RIO_GEM,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_UNI_N_GMAC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_UNI_N_GMACP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_UNI_N_GMAC2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_K2_GMAC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_SH_SUNGEM,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_IPID2_GMAC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UL पूर्ण,
	अणु0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, gem_pci_tbl);

अटल u16 __sungem_phy_पढ़ो(काष्ठा gem *gp, पूर्णांक phy_addr, पूर्णांक reg)
अणु
	u32 cmd;
	पूर्णांक limit = 10000;

	cmd  = (1 << 30);
	cmd |= (2 << 28);
	cmd |= (phy_addr << 23) & MIF_FRAME_PHYAD;
	cmd |= (reg << 18) & MIF_FRAME_REGAD;
	cmd |= (MIF_FRAME_TAMSB);
	ग_लिखोl(cmd, gp->regs + MIF_FRAME);

	जबतक (--limit) अणु
		cmd = पढ़ोl(gp->regs + MIF_FRAME);
		अगर (cmd & MIF_FRAME_TALSB)
			अवरोध;

		udelay(10);
	पूर्ण

	अगर (!limit)
		cmd = 0xffff;

	वापस cmd & MIF_FRAME_DATA;
पूर्ण

अटल अंतरभूत पूर्णांक _sungem_phy_पढ़ो(काष्ठा net_device *dev, पूर्णांक mii_id, पूर्णांक reg)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	वापस __sungem_phy_पढ़ो(gp, mii_id, reg);
पूर्ण

अटल अंतरभूत u16 sungem_phy_पढ़ो(काष्ठा gem *gp, पूर्णांक reg)
अणु
	वापस __sungem_phy_पढ़ो(gp, gp->mii_phy_addr, reg);
पूर्ण

अटल व्योम __sungem_phy_ग_लिखो(काष्ठा gem *gp, पूर्णांक phy_addr, पूर्णांक reg, u16 val)
अणु
	u32 cmd;
	पूर्णांक limit = 10000;

	cmd  = (1 << 30);
	cmd |= (1 << 28);
	cmd |= (phy_addr << 23) & MIF_FRAME_PHYAD;
	cmd |= (reg << 18) & MIF_FRAME_REGAD;
	cmd |= (MIF_FRAME_TAMSB);
	cmd |= (val & MIF_FRAME_DATA);
	ग_लिखोl(cmd, gp->regs + MIF_FRAME);

	जबतक (limit--) अणु
		cmd = पढ़ोl(gp->regs + MIF_FRAME);
		अगर (cmd & MIF_FRAME_TALSB)
			अवरोध;

		udelay(10);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम _sungem_phy_ग_लिखो(काष्ठा net_device *dev, पूर्णांक mii_id, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	__sungem_phy_ग_लिखो(gp, mii_id, reg, val & 0xffff);
पूर्ण

अटल अंतरभूत व्योम sungem_phy_ग_लिखो(काष्ठा gem *gp, पूर्णांक reg, u16 val)
अणु
	__sungem_phy_ग_लिखो(gp, gp->mii_phy_addr, reg, val);
पूर्ण

अटल अंतरभूत व्योम gem_enable_पूर्णांकs(काष्ठा gem *gp)
अणु
	/* Enable all पूर्णांकerrupts but TXDONE */
	ग_लिखोl(GREG_STAT_TXDONE, gp->regs + GREG_IMASK);
पूर्ण

अटल अंतरभूत व्योम gem_disable_पूर्णांकs(काष्ठा gem *gp)
अणु
	/* Disable all पूर्णांकerrupts, including TXDONE */
	ग_लिखोl(GREG_STAT_NAPI | GREG_STAT_TXDONE, gp->regs + GREG_IMASK);
	(व्योम)पढ़ोl(gp->regs + GREG_IMASK); /* ग_लिखो posting */
पूर्ण

अटल व्योम gem_get_cell(काष्ठा gem *gp)
अणु
	BUG_ON(gp->cell_enabled < 0);
	gp->cell_enabled++;
#अगर_घोषित CONFIG_PPC_PMAC
	अगर (gp->cell_enabled == 1) अणु
		mb();
		pmac_call_feature(PMAC_FTR_GMAC_ENABLE, gp->of_node, 0, 1);
		udelay(10);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */
पूर्ण

/* Turn off the chip's घड़ी */
अटल व्योम gem_put_cell(काष्ठा gem *gp)
अणु
	BUG_ON(gp->cell_enabled <= 0);
	gp->cell_enabled--;
#अगर_घोषित CONFIG_PPC_PMAC
	अगर (gp->cell_enabled == 0) अणु
		mb();
		pmac_call_feature(PMAC_FTR_GMAC_ENABLE, gp->of_node, 0, 0);
		udelay(10);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */
पूर्ण

अटल अंतरभूत व्योम gem_netअगर_stop(काष्ठा gem *gp)
अणु
	netअगर_trans_update(gp->dev);	/* prevent tx समयout */
	napi_disable(&gp->napi);
	netअगर_tx_disable(gp->dev);
पूर्ण

अटल अंतरभूत व्योम gem_netअगर_start(काष्ठा gem *gp)
अणु
	/* NOTE: unconditional netअगर_wake_queue is only
	 * appropriate so दीर्घ as all callers are assured to
	 * have मुक्त tx slots.
	 */
	netअगर_wake_queue(gp->dev);
	napi_enable(&gp->napi);
पूर्ण

अटल व्योम gem_schedule_reset(काष्ठा gem *gp)
अणु
	gp->reset_task_pending = 1;
	schedule_work(&gp->reset_task);
पूर्ण

अटल व्योम gem_handle_mअगर_event(काष्ठा gem *gp, u32 reg_val, u32 changed_bits)
अणु
	अगर (netअगर_msg_पूर्णांकr(gp))
		prपूर्णांकk(KERN_DEBUG "%s: mif interrupt\n", gp->dev->name);
पूर्ण

अटल पूर्णांक gem_pcs_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा gem *gp, u32 gem_status)
अणु
	u32 pcs_istat = पढ़ोl(gp->regs + PCS_ISTAT);
	u32 pcs_miistat;

	अगर (netअगर_msg_पूर्णांकr(gp))
		prपूर्णांकk(KERN_DEBUG "%s: pcs interrupt, pcs_istat: 0x%x\n",
			gp->dev->name, pcs_istat);

	अगर (!(pcs_istat & PCS_ISTAT_LSC)) अणु
		netdev_err(dev, "PCS irq but no link status change???\n");
		वापस 0;
	पूर्ण

	/* The link status bit latches on zero, so you must
	 * पढ़ो it twice in such a हाल to see a transition
	 * to the link being up.
	 */
	pcs_miistat = पढ़ोl(gp->regs + PCS_MIISTAT);
	अगर (!(pcs_miistat & PCS_MIISTAT_LS))
		pcs_miistat |=
			(पढ़ोl(gp->regs + PCS_MIISTAT) &
			 PCS_MIISTAT_LS);

	अगर (pcs_miistat & PCS_MIISTAT_ANC) अणु
		/* The remote-fault indication is only valid
		 * when स्वतःneg has completed.
		 */
		अगर (pcs_miistat & PCS_MIISTAT_RF)
			netdev_info(dev, "PCS AutoNEG complete, RemoteFault\n");
		अन्यथा
			netdev_info(dev, "PCS AutoNEG complete\n");
	पूर्ण

	अगर (pcs_miistat & PCS_MIISTAT_LS) अणु
		netdev_info(dev, "PCS link is now up\n");
		netअगर_carrier_on(gp->dev);
	पूर्ण अन्यथा अणु
		netdev_info(dev, "PCS link is now down\n");
		netअगर_carrier_off(gp->dev);
		/* If this happens and the link समयr is not running,
		 * reset so we re-negotiate.
		 */
		अगर (!समयr_pending(&gp->link_समयr))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gem_txmac_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा gem *gp, u32 gem_status)
अणु
	u32 txmac_stat = पढ़ोl(gp->regs + MAC_TXSTAT);

	अगर (netअगर_msg_पूर्णांकr(gp))
		prपूर्णांकk(KERN_DEBUG "%s: txmac interrupt, txmac_stat: 0x%x\n",
			gp->dev->name, txmac_stat);

	/* Defer समयr expiration is quite normal,
	 * करोn't even log the event.
	 */
	अगर ((txmac_stat & MAC_TXSTAT_DTE) &&
	    !(txmac_stat & ~MAC_TXSTAT_DTE))
		वापस 0;

	अगर (txmac_stat & MAC_TXSTAT_URUN) अणु
		netdev_err(dev, "TX MAC xmit underrun\n");
		dev->stats.tx_fअगरo_errors++;
	पूर्ण

	अगर (txmac_stat & MAC_TXSTAT_MPE) अणु
		netdev_err(dev, "TX MAC max packet size error\n");
		dev->stats.tx_errors++;
	पूर्ण

	/* The rest are all हालs of one of the 16-bit TX
	 * counters expiring.
	 */
	अगर (txmac_stat & MAC_TXSTAT_NCE)
		dev->stats.collisions += 0x10000;

	अगर (txmac_stat & MAC_TXSTAT_ECE) अणु
		dev->stats.tx_पातed_errors += 0x10000;
		dev->stats.collisions += 0x10000;
	पूर्ण

	अगर (txmac_stat & MAC_TXSTAT_LCE) अणु
		dev->stats.tx_पातed_errors += 0x10000;
		dev->stats.collisions += 0x10000;
	पूर्ण

	/* We करो not keep track of MAC_TXSTAT_FCE and
	 * MAC_TXSTAT_PCE events.
	 */
	वापस 0;
पूर्ण

/* When we get a RX fअगरo overflow, the RX unit in GEM is probably hung
 * so we करो the following.
 *
 * If any part of the reset goes wrong, we वापस 1 and that causes the
 * whole chip to be reset.
 */
अटल पूर्णांक gem_rxmac_reset(काष्ठा gem *gp)
अणु
	काष्ठा net_device *dev = gp->dev;
	पूर्णांक limit, i;
	u64 desc_dma;
	u32 val;

	/* First, reset & disable MAC RX. */
	ग_लिखोl(MAC_RXRST_CMD, gp->regs + MAC_RXRST);
	क्रम (limit = 0; limit < 5000; limit++) अणु
		अगर (!(पढ़ोl(gp->regs + MAC_RXRST) & MAC_RXRST_CMD))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (limit == 5000) अणु
		netdev_err(dev, "RX MAC will not reset, resetting whole chip\n");
		वापस 1;
	पूर्ण

	ग_लिखोl(gp->mac_rx_cfg & ~MAC_RXCFG_ENAB,
	       gp->regs + MAC_RXCFG);
	क्रम (limit = 0; limit < 5000; limit++) अणु
		अगर (!(पढ़ोl(gp->regs + MAC_RXCFG) & MAC_RXCFG_ENAB))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (limit == 5000) अणु
		netdev_err(dev, "RX MAC will not disable, resetting whole chip\n");
		वापस 1;
	पूर्ण

	/* Second, disable RX DMA. */
	ग_लिखोl(0, gp->regs + RXDMA_CFG);
	क्रम (limit = 0; limit < 5000; limit++) अणु
		अगर (!(पढ़ोl(gp->regs + RXDMA_CFG) & RXDMA_CFG_ENABLE))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (limit == 5000) अणु
		netdev_err(dev, "RX DMA will not disable, resetting whole chip\n");
		वापस 1;
	पूर्ण

	mdelay(5);

	/* Execute RX reset command. */
	ग_लिखोl(gp->swrst_base | GREG_SWRST_RXRST,
	       gp->regs + GREG_SWRST);
	क्रम (limit = 0; limit < 5000; limit++) अणु
		अगर (!(पढ़ोl(gp->regs + GREG_SWRST) & GREG_SWRST_RXRST))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (limit == 5000) अणु
		netdev_err(dev, "RX reset command will not execute, resetting whole chip\n");
		वापस 1;
	पूर्ण

	/* Refresh the RX ring. */
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा gem_rxd *rxd = &gp->init_block->rxd[i];

		अगर (gp->rx_skbs[i] == शून्य) अणु
			netdev_err(dev, "Parts of RX ring empty, resetting whole chip\n");
			वापस 1;
		पूर्ण

		rxd->status_word = cpu_to_le64(RXDCTRL_FRESH(gp));
	पूर्ण
	gp->rx_new = gp->rx_old = 0;

	/* Now we must reprogram the rest of RX unit. */
	desc_dma = (u64) gp->gblock_dvma;
	desc_dma += (INIT_BLOCK_TX_RING_SIZE * माप(काष्ठा gem_txd));
	ग_लिखोl(desc_dma >> 32, gp->regs + RXDMA_DBHI);
	ग_लिखोl(desc_dma & 0xffffffff, gp->regs + RXDMA_DBLOW);
	ग_लिखोl(RX_RING_SIZE - 4, gp->regs + RXDMA_KICK);
	val = (RXDMA_CFG_BASE | (RX_OFFSET << 10) |
	       (ETH_HLEN << 13) | RXDMA_CFG_FTHRESH_128);
	ग_लिखोl(val, gp->regs + RXDMA_CFG);
	अगर (पढ़ोl(gp->regs + GREG_BIFCFG) & GREG_BIFCFG_M66EN)
		ग_लिखोl(((5 & RXDMA_BLANK_IPKTS) |
			((8 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
	अन्यथा
		ग_लिखोl(((5 & RXDMA_BLANK_IPKTS) |
			((4 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
	val  = (((gp->rx_छोड़ो_off / 64) << 0) & RXDMA_PTHRESH_OFF);
	val |= (((gp->rx_छोड़ो_on / 64) << 12) & RXDMA_PTHRESH_ON);
	ग_लिखोl(val, gp->regs + RXDMA_PTHRESH);
	val = पढ़ोl(gp->regs + RXDMA_CFG);
	ग_लिखोl(val | RXDMA_CFG_ENABLE, gp->regs + RXDMA_CFG);
	ग_लिखोl(MAC_RXSTAT_RCV, gp->regs + MAC_RXMASK);
	val = पढ़ोl(gp->regs + MAC_RXCFG);
	ग_लिखोl(val | MAC_RXCFG_ENAB, gp->regs + MAC_RXCFG);

	वापस 0;
पूर्ण

अटल पूर्णांक gem_rxmac_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा gem *gp, u32 gem_status)
अणु
	u32 rxmac_stat = पढ़ोl(gp->regs + MAC_RXSTAT);
	पूर्णांक ret = 0;

	अगर (netअगर_msg_पूर्णांकr(gp))
		prपूर्णांकk(KERN_DEBUG "%s: rxmac interrupt, rxmac_stat: 0x%x\n",
			gp->dev->name, rxmac_stat);

	अगर (rxmac_stat & MAC_RXSTAT_OFLW) अणु
		u32 smac = पढ़ोl(gp->regs + MAC_SMACHINE);

		netdev_err(dev, "RX MAC fifo overflow smac[%08x]\n", smac);
		dev->stats.rx_over_errors++;
		dev->stats.rx_fअगरo_errors++;

		ret = gem_rxmac_reset(gp);
	पूर्ण

	अगर (rxmac_stat & MAC_RXSTAT_ACE)
		dev->stats.rx_frame_errors += 0x10000;

	अगर (rxmac_stat & MAC_RXSTAT_CCE)
		dev->stats.rx_crc_errors += 0x10000;

	अगर (rxmac_stat & MAC_RXSTAT_LCE)
		dev->stats.rx_length_errors += 0x10000;

	/* We करो not track MAC_RXSTAT_FCE and MAC_RXSTAT_VCE
	 * events.
	 */
	वापस ret;
पूर्ण

अटल पूर्णांक gem_mac_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा gem *gp, u32 gem_status)
अणु
	u32 mac_cstat = पढ़ोl(gp->regs + MAC_CSTAT);

	अगर (netअगर_msg_पूर्णांकr(gp))
		prपूर्णांकk(KERN_DEBUG "%s: mac interrupt, mac_cstat: 0x%x\n",
			gp->dev->name, mac_cstat);

	/* This पूर्णांकerrupt is just क्रम छोड़ो frame and छोड़ो
	 * tracking.  It is useful क्रम diagnostics and debug
	 * but probably by शेष we will mask these events.
	 */
	अगर (mac_cstat & MAC_CSTAT_PS)
		gp->छोड़ो_entered++;

	अगर (mac_cstat & MAC_CSTAT_PRCV)
		gp->छोड़ो_last_समय_recvd = (mac_cstat >> 16);

	वापस 0;
पूर्ण

अटल पूर्णांक gem_mअगर_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा gem *gp, u32 gem_status)
अणु
	u32 mअगर_status = पढ़ोl(gp->regs + MIF_STATUS);
	u32 reg_val, changed_bits;

	reg_val = (mअगर_status & MIF_STATUS_DATA) >> 16;
	changed_bits = (mअगर_status & MIF_STATUS_STAT);

	gem_handle_mअगर_event(gp, reg_val, changed_bits);

	वापस 0;
पूर्ण

अटल पूर्णांक gem_pci_पूर्णांकerrupt(काष्ठा net_device *dev, काष्ठा gem *gp, u32 gem_status)
अणु
	u32 pci_estat = पढ़ोl(gp->regs + GREG_PCIESTAT);

	अगर (gp->pdev->venकरोr == PCI_VENDOR_ID_SUN &&
	    gp->pdev->device == PCI_DEVICE_ID_SUN_GEM) अणु
		netdev_err(dev, "PCI error [%04x]", pci_estat);

		अगर (pci_estat & GREG_PCIESTAT_BADACK)
			pr_cont(" <No ACK64# during ABS64 cycle>");
		अगर (pci_estat & GREG_PCIESTAT_DTRTO)
			pr_cont(" <Delayed transaction timeout>");
		अगर (pci_estat & GREG_PCIESTAT_OTHER)
			pr_cont(" <other>");
		pr_cont("\n");
	पूर्ण अन्यथा अणु
		pci_estat |= GREG_PCIESTAT_OTHER;
		netdev_err(dev, "PCI error\n");
	पूर्ण

	अगर (pci_estat & GREG_PCIESTAT_OTHER) अणु
		पूर्णांक pci_errs;

		/* Interrogate PCI config space क्रम the
		 * true cause.
		 */
		pci_errs = pci_status_get_and_clear_errors(gp->pdev);
		netdev_err(dev, "PCI status errors[%04x]\n", pci_errs);
		अगर (pci_errs & PCI_STATUS_PARITY)
			netdev_err(dev, "PCI parity error detected\n");
		अगर (pci_errs & PCI_STATUS_SIG_TARGET_ABORT)
			netdev_err(dev, "PCI target abort\n");
		अगर (pci_errs & PCI_STATUS_REC_TARGET_ABORT)
			netdev_err(dev, "PCI master acks target abort\n");
		अगर (pci_errs & PCI_STATUS_REC_MASTER_ABORT)
			netdev_err(dev, "PCI master abort\n");
		अगर (pci_errs & PCI_STATUS_SIG_SYSTEM_ERROR)
			netdev_err(dev, "PCI system error SERR#\n");
		अगर (pci_errs & PCI_STATUS_DETECTED_PARITY)
			netdev_err(dev, "PCI parity error\n");
	पूर्ण

	/* For all PCI errors, we should reset the chip. */
	वापस 1;
पूर्ण

/* All non-normal पूर्णांकerrupt conditions get serviced here.
 * Returns non-zero अगर we should just निकास the पूर्णांकerrupt
 * handler right now (ie. अगर we reset the card which invalidates
 * all of the other original irq status bits).
 */
अटल पूर्णांक gem_abnormal_irq(काष्ठा net_device *dev, काष्ठा gem *gp, u32 gem_status)
अणु
	अगर (gem_status & GREG_STAT_RXNOBUF) अणु
		/* Frame arrived, no मुक्त RX buffers available. */
		अगर (netअगर_msg_rx_err(gp))
			prपूर्णांकk(KERN_DEBUG "%s: no buffer for rx frame\n",
				gp->dev->name);
		dev->stats.rx_dropped++;
	पूर्ण

	अगर (gem_status & GREG_STAT_RXTAGERR) अणु
		/* corrupt RX tag framing */
		अगर (netअगर_msg_rx_err(gp))
			prपूर्णांकk(KERN_DEBUG "%s: corrupt rx tag framing\n",
				gp->dev->name);
		dev->stats.rx_errors++;

		वापस 1;
	पूर्ण

	अगर (gem_status & GREG_STAT_PCS) अणु
		अगर (gem_pcs_पूर्णांकerrupt(dev, gp, gem_status))
			वापस 1;
	पूर्ण

	अगर (gem_status & GREG_STAT_TXMAC) अणु
		अगर (gem_txmac_पूर्णांकerrupt(dev, gp, gem_status))
			वापस 1;
	पूर्ण

	अगर (gem_status & GREG_STAT_RXMAC) अणु
		अगर (gem_rxmac_पूर्णांकerrupt(dev, gp, gem_status))
			वापस 1;
	पूर्ण

	अगर (gem_status & GREG_STAT_MAC) अणु
		अगर (gem_mac_पूर्णांकerrupt(dev, gp, gem_status))
			वापस 1;
	पूर्ण

	अगर (gem_status & GREG_STAT_MIF) अणु
		अगर (gem_mअगर_पूर्णांकerrupt(dev, gp, gem_status))
			वापस 1;
	पूर्ण

	अगर (gem_status & GREG_STAT_PCIERR) अणु
		अगर (gem_pci_पूर्णांकerrupt(dev, gp, gem_status))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल __अंतरभूत__ व्योम gem_tx(काष्ठा net_device *dev, काष्ठा gem *gp, u32 gem_status)
अणु
	पूर्णांक entry, limit;

	entry = gp->tx_old;
	limit = ((gem_status & GREG_STAT_TXNR) >> GREG_STAT_TXNR_SHIFT);
	जबतक (entry != limit) अणु
		काष्ठा sk_buff *skb;
		काष्ठा gem_txd *txd;
		dma_addr_t dma_addr;
		u32 dma_len;
		पूर्णांक frag;

		अगर (netअगर_msg_tx_करोne(gp))
			prपूर्णांकk(KERN_DEBUG "%s: tx done, slot %d\n",
				gp->dev->name, entry);
		skb = gp->tx_skbs[entry];
		अगर (skb_shinfo(skb)->nr_frags) अणु
			पूर्णांक last = entry + skb_shinfo(skb)->nr_frags;
			पूर्णांक walk = entry;
			पूर्णांक incomplete = 0;

			last &= (TX_RING_SIZE - 1);
			क्रम (;;) अणु
				walk = NEXT_TX(walk);
				अगर (walk == limit)
					incomplete = 1;
				अगर (walk == last)
					अवरोध;
			पूर्ण
			अगर (incomplete)
				अवरोध;
		पूर्ण
		gp->tx_skbs[entry] = शून्य;
		dev->stats.tx_bytes += skb->len;

		क्रम (frag = 0; frag <= skb_shinfo(skb)->nr_frags; frag++) अणु
			txd = &gp->init_block->txd[entry];

			dma_addr = le64_to_cpu(txd->buffer);
			dma_len = le64_to_cpu(txd->control_word) & TXDCTRL_BUFSZ;

			dma_unmap_page(&gp->pdev->dev, dma_addr, dma_len,
				       DMA_TO_DEVICE);
			entry = NEXT_TX(entry);
		पूर्ण

		dev->stats.tx_packets++;
		dev_consume_skb_any(skb);
	पूर्ण
	gp->tx_old = entry;

	/* Need to make the tx_old update visible to gem_start_xmit()
	 * beक्रमe checking क्रम netअगर_queue_stopped().  Without the
	 * memory barrier, there is a small possibility that gem_start_xmit()
	 * will miss it and cause the queue to be stopped क्रमever.
	 */
	smp_mb();

	अगर (unlikely(netअगर_queue_stopped(dev) &&
		     TX_BUFFS_AVAIL(gp) > (MAX_SKB_FRAGS + 1))) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, 0);

		__netअगर_tx_lock(txq, smp_processor_id());
		अगर (netअगर_queue_stopped(dev) &&
		    TX_BUFFS_AVAIL(gp) > (MAX_SKB_FRAGS + 1))
			netअगर_wake_queue(dev);
		__netअगर_tx_unlock(txq);
	पूर्ण
पूर्ण

अटल __अंतरभूत__ व्योम gem_post_rxds(काष्ठा gem *gp, पूर्णांक limit)
अणु
	पूर्णांक cluster_start, curr, count, kick;

	cluster_start = curr = (gp->rx_new & ~(4 - 1));
	count = 0;
	kick = -1;
	dma_wmb();
	जबतक (curr != limit) अणु
		curr = NEXT_RX(curr);
		अगर (++count == 4) अणु
			काष्ठा gem_rxd *rxd =
				&gp->init_block->rxd[cluster_start];
			क्रम (;;) अणु
				rxd->status_word = cpu_to_le64(RXDCTRL_FRESH(gp));
				rxd++;
				cluster_start = NEXT_RX(cluster_start);
				अगर (cluster_start == curr)
					अवरोध;
			पूर्ण
			kick = curr;
			count = 0;
		पूर्ण
	पूर्ण
	अगर (kick >= 0) अणु
		mb();
		ग_लिखोl(kick, gp->regs + RXDMA_KICK);
	पूर्ण
पूर्ण

#घोषणा ALIGNED_RX_SKB_ADDR(addr) \
        ((((अचिन्हित दीर्घ)(addr) + (64UL - 1UL)) & ~(64UL - 1UL)) - (अचिन्हित दीर्घ)(addr))
अटल __अंतरभूत__ काष्ठा sk_buff *gem_alloc_skb(काष्ठा net_device *dev, पूर्णांक size,
						gfp_t gfp_flags)
अणु
	काष्ठा sk_buff *skb = alloc_skb(size + 64, gfp_flags);

	अगर (likely(skb)) अणु
		अचिन्हित दीर्घ offset = ALIGNED_RX_SKB_ADDR(skb->data);
		skb_reserve(skb, offset);
	पूर्ण
	वापस skb;
पूर्ण

अटल पूर्णांक gem_rx(काष्ठा gem *gp, पूर्णांक work_to_करो)
अणु
	काष्ठा net_device *dev = gp->dev;
	पूर्णांक entry, drops, work_करोne = 0;
	u32 करोne;

	अगर (netअगर_msg_rx_status(gp))
		prपूर्णांकk(KERN_DEBUG "%s: rx interrupt, done: %d, rx_new: %d\n",
			gp->dev->name, पढ़ोl(gp->regs + RXDMA_DONE), gp->rx_new);

	entry = gp->rx_new;
	drops = 0;
	करोne = पढ़ोl(gp->regs + RXDMA_DONE);
	क्रम (;;) अणु
		काष्ठा gem_rxd *rxd = &gp->init_block->rxd[entry];
		काष्ठा sk_buff *skb;
		u64 status = le64_to_cpu(rxd->status_word);
		dma_addr_t dma_addr;
		पूर्णांक len;

		अगर ((status & RXDCTRL_OWN) != 0)
			अवरोध;

		अगर (work_करोne >= RX_RING_SIZE || work_करोne >= work_to_करो)
			अवरोध;

		/* When writing back RX descriptor, GEM ग_लिखोs status
		 * then buffer address, possibly in separate transactions.
		 * If we करोn't रुको क्रम the chip to ग_लिखो both, we could
		 * post a new buffer to this descriptor then have GEM spam
		 * on the buffer address.  We sync on the RX completion
		 * रेजिस्टर to prevent this from happening.
		 */
		अगर (entry == करोne) अणु
			करोne = पढ़ोl(gp->regs + RXDMA_DONE);
			अगर (entry == करोne)
				अवरोध;
		पूर्ण

		/* We can now account क्रम the work we're about to करो */
		work_करोne++;

		skb = gp->rx_skbs[entry];

		len = (status & RXDCTRL_BUFSZ) >> 16;
		अगर ((len < ETH_ZLEN) || (status & RXDCTRL_BAD)) अणु
			dev->stats.rx_errors++;
			अगर (len < ETH_ZLEN)
				dev->stats.rx_length_errors++;
			अगर (len & RXDCTRL_BAD)
				dev->stats.rx_crc_errors++;

			/* We'll just वापस it to GEM. */
		drop_it:
			dev->stats.rx_dropped++;
			जाओ next;
		पूर्ण

		dma_addr = le64_to_cpu(rxd->buffer);
		अगर (len > RX_COPY_THRESHOLD) अणु
			काष्ठा sk_buff *new_skb;

			new_skb = gem_alloc_skb(dev, RX_BUF_ALLOC_SIZE(gp), GFP_ATOMIC);
			अगर (new_skb == शून्य) अणु
				drops++;
				जाओ drop_it;
			पूर्ण
			dma_unmap_page(&gp->pdev->dev, dma_addr,
				       RX_BUF_ALLOC_SIZE(gp), DMA_FROM_DEVICE);
			gp->rx_skbs[entry] = new_skb;
			skb_put(new_skb, (gp->rx_buf_sz + RX_OFFSET));
			rxd->buffer = cpu_to_le64(dma_map_page(&gp->pdev->dev,
							       virt_to_page(new_skb->data),
							       offset_in_page(new_skb->data),
							       RX_BUF_ALLOC_SIZE(gp),
							       DMA_FROM_DEVICE));
			skb_reserve(new_skb, RX_OFFSET);

			/* Trim the original skb क्रम the netअगर. */
			skb_trim(skb, len);
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *copy_skb = netdev_alloc_skb(dev, len + 2);

			अगर (copy_skb == शून्य) अणु
				drops++;
				जाओ drop_it;
			पूर्ण

			skb_reserve(copy_skb, 2);
			skb_put(copy_skb, len);
			dma_sync_single_क्रम_cpu(&gp->pdev->dev, dma_addr, len,
						DMA_FROM_DEVICE);
			skb_copy_from_linear_data(skb, copy_skb->data, len);
			dma_sync_single_क्रम_device(&gp->pdev->dev, dma_addr,
						   len, DMA_FROM_DEVICE);

			/* We'll reuse the original ring buffer. */
			skb = copy_skb;
		पूर्ण

		अगर (likely(dev->features & NETIF_F_RXCSUM)) अणु
			__sum16 csum;

			csum = (__क्रमce __sum16)htons((status & RXDCTRL_TCPCSUM) ^ 0xffff);
			skb->csum = csum_unfold(csum);
			skb->ip_summed = CHECKSUM_COMPLETE;
		पूर्ण
		skb->protocol = eth_type_trans(skb, gp->dev);

		napi_gro_receive(&gp->napi, skb);

		dev->stats.rx_packets++;
		dev->stats.rx_bytes += len;

	next:
		entry = NEXT_RX(entry);
	पूर्ण

	gem_post_rxds(gp, entry);

	gp->rx_new = entry;

	अगर (drops)
		netdev_info(gp->dev, "Memory squeeze, deferring packet\n");

	वापस work_करोne;
पूर्ण

अटल पूर्णांक gem_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा gem *gp = container_of(napi, काष्ठा gem, napi);
	काष्ठा net_device *dev = gp->dev;
	पूर्णांक work_करोne;

	work_करोne = 0;
	करो अणु
		/* Handle anomalies */
		अगर (unlikely(gp->status & GREG_STAT_ABNORMAL)) अणु
			काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, 0);
			पूर्णांक reset;

			/* We run the abnormal पूर्णांकerrupt handling code with
			 * the Tx lock. It only resets the Rx portion of the
			 * chip, but we need to guard it against DMA being
			 * restarted by the link poll समयr
			 */
			__netअगर_tx_lock(txq, smp_processor_id());
			reset = gem_abnormal_irq(dev, gp, gp->status);
			__netअगर_tx_unlock(txq);
			अगर (reset) अणु
				gem_schedule_reset(gp);
				napi_complete(napi);
				वापस work_करोne;
			पूर्ण
		पूर्ण

		/* Run TX completion thपढ़ो */
		gem_tx(dev, gp, gp->status);

		/* Run RX thपढ़ो. We करोn't use any locking here,
		 * code willing to करो bad things - like cleaning the
		 * rx ring - must call napi_disable(), which
		 * schedule_समयout()'s अगर polling is alपढ़ोy disabled.
		 */
		work_करोne += gem_rx(gp, budget - work_करोne);

		अगर (work_करोne >= budget)
			वापस work_करोne;

		gp->status = पढ़ोl(gp->regs + GREG_STAT);
	पूर्ण जबतक (gp->status & GREG_STAT_NAPI);

	napi_complete_करोne(napi, work_करोne);
	gem_enable_पूर्णांकs(gp);

	वापस work_करोne;
पूर्ण

अटल irqवापस_t gem_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा gem *gp = netdev_priv(dev);

	अगर (napi_schedule_prep(&gp->napi)) अणु
		u32 gem_status = पढ़ोl(gp->regs + GREG_STAT);

		अगर (unlikely(gem_status == 0)) अणु
			napi_enable(&gp->napi);
			वापस IRQ_NONE;
		पूर्ण
		अगर (netअगर_msg_पूर्णांकr(gp))
			prपूर्णांकk(KERN_DEBUG "%s: gem_interrupt() gem_status: 0x%x\n",
			       gp->dev->name, gem_status);

		gp->status = gem_status;
		gem_disable_पूर्णांकs(gp);
		__napi_schedule(&gp->napi);
	पूर्ण

	/* If polling was disabled at the समय we received that
	 * पूर्णांकerrupt, we may वापस IRQ_HANDLED here जबतक we
	 * should वापस IRQ_NONE. No big deal...
	 */
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम gem_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	disable_irq(gp->pdev->irq);
	gem_पूर्णांकerrupt(gp->pdev->irq, dev);
	enable_irq(gp->pdev->irq);
पूर्ण
#पूर्ण_अगर

अटल व्योम gem_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	netdev_err(dev, "transmit timed out, resetting\n");

	netdev_err(dev, "TX_STATE[%08x:%08x:%08x]\n",
		   पढ़ोl(gp->regs + TXDMA_CFG),
		   पढ़ोl(gp->regs + MAC_TXSTAT),
		   पढ़ोl(gp->regs + MAC_TXCFG));
	netdev_err(dev, "RX_STATE[%08x:%08x:%08x]\n",
		   पढ़ोl(gp->regs + RXDMA_CFG),
		   पढ़ोl(gp->regs + MAC_RXSTAT),
		   पढ़ोl(gp->regs + MAC_RXCFG));

	gem_schedule_reset(gp);
पूर्ण

अटल __अंतरभूत__ पूर्णांक gem_पूर्णांकme(पूर्णांक entry)
अणु
	/* Algorithm: IRQ every 1/2 of descriptors. */
	अगर (!(entry & ((TX_RING_SIZE>>1)-1)))
		वापस 1;

	वापस 0;
पूर्ण

अटल netdev_tx_t gem_start_xmit(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	पूर्णांक entry;
	u64 ctrl;

	ctrl = 0;
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		स्थिर u64 csum_start_off = skb_checksum_start_offset(skb);
		स्थिर u64 csum_stuff_off = csum_start_off + skb->csum_offset;

		ctrl = (TXDCTRL_CENAB |
			(csum_start_off << 15) |
			(csum_stuff_off << 21));
	पूर्ण

	अगर (unlikely(TX_BUFFS_AVAIL(gp) <= (skb_shinfo(skb)->nr_frags + 1))) अणु
		/* This is a hard error, log it. */
		अगर (!netअगर_queue_stopped(dev)) अणु
			netअगर_stop_queue(dev);
			netdev_err(dev, "BUG! Tx Ring full when queue awake!\n");
		पूर्ण
		वापस NETDEV_TX_BUSY;
	पूर्ण

	entry = gp->tx_new;
	gp->tx_skbs[entry] = skb;

	अगर (skb_shinfo(skb)->nr_frags == 0) अणु
		काष्ठा gem_txd *txd = &gp->init_block->txd[entry];
		dma_addr_t mapping;
		u32 len;

		len = skb->len;
		mapping = dma_map_page(&gp->pdev->dev,
				       virt_to_page(skb->data),
				       offset_in_page(skb->data),
				       len, DMA_TO_DEVICE);
		ctrl |= TXDCTRL_SOF | TXDCTRL_खातापूर्ण | len;
		अगर (gem_पूर्णांकme(entry))
			ctrl |= TXDCTRL_INTME;
		txd->buffer = cpu_to_le64(mapping);
		dma_wmb();
		txd->control_word = cpu_to_le64(ctrl);
		entry = NEXT_TX(entry);
	पूर्ण अन्यथा अणु
		काष्ठा gem_txd *txd;
		u32 first_len;
		u64 पूर्णांकme;
		dma_addr_t first_mapping;
		पूर्णांक frag, first_entry = entry;

		पूर्णांकme = 0;
		अगर (gem_पूर्णांकme(entry))
			पूर्णांकme |= TXDCTRL_INTME;

		/* We must give this initial chunk to the device last.
		 * Otherwise we could race with the device.
		 */
		first_len = skb_headlen(skb);
		first_mapping = dma_map_page(&gp->pdev->dev,
					     virt_to_page(skb->data),
					     offset_in_page(skb->data),
					     first_len, DMA_TO_DEVICE);
		entry = NEXT_TX(entry);

		क्रम (frag = 0; frag < skb_shinfo(skb)->nr_frags; frag++) अणु
			स्थिर skb_frag_t *this_frag = &skb_shinfo(skb)->frags[frag];
			u32 len;
			dma_addr_t mapping;
			u64 this_ctrl;

			len = skb_frag_size(this_frag);
			mapping = skb_frag_dma_map(&gp->pdev->dev, this_frag,
						   0, len, DMA_TO_DEVICE);
			this_ctrl = ctrl;
			अगर (frag == skb_shinfo(skb)->nr_frags - 1)
				this_ctrl |= TXDCTRL_खातापूर्ण;

			txd = &gp->init_block->txd[entry];
			txd->buffer = cpu_to_le64(mapping);
			dma_wmb();
			txd->control_word = cpu_to_le64(this_ctrl | len);

			अगर (gem_पूर्णांकme(entry))
				पूर्णांकme |= TXDCTRL_INTME;

			entry = NEXT_TX(entry);
		पूर्ण
		txd = &gp->init_block->txd[first_entry];
		txd->buffer = cpu_to_le64(first_mapping);
		dma_wmb();
		txd->control_word =
			cpu_to_le64(ctrl | TXDCTRL_SOF | पूर्णांकme | first_len);
	पूर्ण

	gp->tx_new = entry;
	अगर (unlikely(TX_BUFFS_AVAIL(gp) <= (MAX_SKB_FRAGS + 1))) अणु
		netअगर_stop_queue(dev);

		/* netअगर_stop_queue() must be करोne beक्रमe checking
		 * checking tx index in TX_BUFFS_AVAIL() below, because
		 * in gem_tx(), we update tx_old beक्रमe checking क्रम
		 * netअगर_queue_stopped().
		 */
		smp_mb();
		अगर (TX_BUFFS_AVAIL(gp) > (MAX_SKB_FRAGS + 1))
			netअगर_wake_queue(dev);
	पूर्ण
	अगर (netअगर_msg_tx_queued(gp))
		prपूर्णांकk(KERN_DEBUG "%s: tx queued, slot %d, skblen %d\n",
		       dev->name, entry, skb->len);
	mb();
	ग_लिखोl(gp->tx_new, gp->regs + TXDMA_KICK);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम gem_pcs_reset(काष्ठा gem *gp)
अणु
	पूर्णांक limit;
	u32 val;

	/* Reset PCS unit. */
	val = पढ़ोl(gp->regs + PCS_MIICTRL);
	val |= PCS_MIICTRL_RST;
	ग_लिखोl(val, gp->regs + PCS_MIICTRL);

	limit = 32;
	जबतक (पढ़ोl(gp->regs + PCS_MIICTRL) & PCS_MIICTRL_RST) अणु
		udelay(100);
		अगर (limit-- <= 0)
			अवरोध;
	पूर्ण
	अगर (limit < 0)
		netdev_warn(gp->dev, "PCS reset bit would not clear\n");
पूर्ण

अटल व्योम gem_pcs_reinit_adv(काष्ठा gem *gp)
अणु
	u32 val;

	/* Make sure PCS is disabled जबतक changing advertisement
	 * configuration.
	 */
	val = पढ़ोl(gp->regs + PCS_CFG);
	val &= ~(PCS_CFG_ENABLE | PCS_CFG_TO);
	ग_लिखोl(val, gp->regs + PCS_CFG);

	/* Advertise all capabilities except asymmetric
	 * छोड़ो.
	 */
	val = पढ़ोl(gp->regs + PCS_MIIADV);
	val |= (PCS_MIIADV_FD | PCS_MIIADV_HD |
		PCS_MIIADV_SP | PCS_MIIADV_AP);
	ग_लिखोl(val, gp->regs + PCS_MIIADV);

	/* Enable and restart स्वतः-negotiation, disable wrapback/loopback,
	 * and re-enable PCS.
	 */
	val = पढ़ोl(gp->regs + PCS_MIICTRL);
	val |= (PCS_MIICTRL_RAN | PCS_MIICTRL_ANE);
	val &= ~PCS_MIICTRL_WB;
	ग_लिखोl(val, gp->regs + PCS_MIICTRL);

	val = पढ़ोl(gp->regs + PCS_CFG);
	val |= PCS_CFG_ENABLE;
	ग_लिखोl(val, gp->regs + PCS_CFG);

	/* Make sure serialink loopback is off.  The meaning
	 * of this bit is logically inverted based upon whether
	 * you are in Serialink or SERDES mode.
	 */
	val = पढ़ोl(gp->regs + PCS_SCTRL);
	अगर (gp->phy_type == phy_serialink)
		val &= ~PCS_SCTRL_LOOP;
	अन्यथा
		val |= PCS_SCTRL_LOOP;
	ग_लिखोl(val, gp->regs + PCS_SCTRL);
पूर्ण

#घोषणा STOP_TRIES 32

अटल व्योम gem_reset(काष्ठा gem *gp)
अणु
	पूर्णांक limit;
	u32 val;

	/* Make sure we won't get any more पूर्णांकerrupts */
	ग_लिखोl(0xffffffff, gp->regs + GREG_IMASK);

	/* Reset the chip */
	ग_लिखोl(gp->swrst_base | GREG_SWRST_TXRST | GREG_SWRST_RXRST,
	       gp->regs + GREG_SWRST);

	limit = STOP_TRIES;

	करो अणु
		udelay(20);
		val = पढ़ोl(gp->regs + GREG_SWRST);
		अगर (limit-- <= 0)
			अवरोध;
	पूर्ण जबतक (val & (GREG_SWRST_TXRST | GREG_SWRST_RXRST));

	अगर (limit < 0)
		netdev_err(gp->dev, "SW reset is ghetto\n");

	अगर (gp->phy_type == phy_serialink || gp->phy_type == phy_serdes)
		gem_pcs_reinit_adv(gp);
पूर्ण

अटल व्योम gem_start_dma(काष्ठा gem *gp)
अणु
	u32 val;

	/* We are पढ़ोy to rock, turn everything on. */
	val = पढ़ोl(gp->regs + TXDMA_CFG);
	ग_लिखोl(val | TXDMA_CFG_ENABLE, gp->regs + TXDMA_CFG);
	val = पढ़ोl(gp->regs + RXDMA_CFG);
	ग_लिखोl(val | RXDMA_CFG_ENABLE, gp->regs + RXDMA_CFG);
	val = पढ़ोl(gp->regs + MAC_TXCFG);
	ग_लिखोl(val | MAC_TXCFG_ENAB, gp->regs + MAC_TXCFG);
	val = पढ़ोl(gp->regs + MAC_RXCFG);
	ग_लिखोl(val | MAC_RXCFG_ENAB, gp->regs + MAC_RXCFG);

	(व्योम) पढ़ोl(gp->regs + MAC_RXCFG);
	udelay(100);

	gem_enable_पूर्णांकs(gp);

	ग_लिखोl(RX_RING_SIZE - 4, gp->regs + RXDMA_KICK);
पूर्ण

/* DMA won't be actually stopped beक्रमe about 4ms tho ...
 */
अटल व्योम gem_stop_dma(काष्ठा gem *gp)
अणु
	u32 val;

	/* We are करोne rocking, turn everything off. */
	val = पढ़ोl(gp->regs + TXDMA_CFG);
	ग_लिखोl(val & ~TXDMA_CFG_ENABLE, gp->regs + TXDMA_CFG);
	val = पढ़ोl(gp->regs + RXDMA_CFG);
	ग_लिखोl(val & ~RXDMA_CFG_ENABLE, gp->regs + RXDMA_CFG);
	val = पढ़ोl(gp->regs + MAC_TXCFG);
	ग_लिखोl(val & ~MAC_TXCFG_ENAB, gp->regs + MAC_TXCFG);
	val = पढ़ोl(gp->regs + MAC_RXCFG);
	ग_लिखोl(val & ~MAC_RXCFG_ENAB, gp->regs + MAC_RXCFG);

	(व्योम) पढ़ोl(gp->regs + MAC_RXCFG);

	/* Need to रुको a bit ... करोne by the caller */
पूर्ण


// XXX dbl check what that function should करो when called on PCS PHY
अटल व्योम gem_begin_स्वतः_negotiation(काष्ठा gem *gp,
				       स्थिर काष्ठा ethtool_link_ksettings *ep)
अणु
	u32 advertise, features;
	पूर्णांक स्वतःneg;
	पूर्णांक speed;
	पूर्णांक duplex;
	u32 advertising;

	अगर (ep)
		ethtool_convert_link_mode_to_legacy_u32(
			&advertising, ep->link_modes.advertising);

	अगर (gp->phy_type != phy_mii_mdio0 &&
     	    gp->phy_type != phy_mii_mdio1)
     	    	जाओ non_mii;

	/* Setup advertise */
	अगर (found_mii_phy(gp))
		features = gp->phy_mii.def->features;
	अन्यथा
		features = 0;

	advertise = features & ADVERTISE_MASK;
	अगर (gp->phy_mii.advertising != 0)
		advertise &= gp->phy_mii.advertising;

	स्वतःneg = gp->want_स्वतःneg;
	speed = gp->phy_mii.speed;
	duplex = gp->phy_mii.duplex;

	/* Setup link parameters */
	अगर (!ep)
		जाओ start_aneg;
	अगर (ep->base.स्वतःneg == AUTONEG_ENABLE) अणु
		advertise = advertising;
		स्वतःneg = 1;
	पूर्ण अन्यथा अणु
		स्वतःneg = 0;
		speed = ep->base.speed;
		duplex = ep->base.duplex;
	पूर्ण

start_aneg:
	/* Sanitize settings based on PHY capabilities */
	अगर ((features & SUPPORTED_Autoneg) == 0)
		स्वतःneg = 0;
	अगर (speed == SPEED_1000 &&
	    !(features & (SUPPORTED_1000baseT_Half | SUPPORTED_1000baseT_Full)))
		speed = SPEED_100;
	अगर (speed == SPEED_100 &&
	    !(features & (SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full)))
		speed = SPEED_10;
	अगर (duplex == DUPLEX_FULL &&
	    !(features & (SUPPORTED_1000baseT_Full |
	    		  SUPPORTED_100baseT_Full |
	    		  SUPPORTED_10baseT_Full)))
	    	duplex = DUPLEX_HALF;
	अगर (speed == 0)
		speed = SPEED_10;

	/* If we are asleep, we करोn't try to actually setup the PHY, we
	 * just store the settings
	 */
	अगर (!netअगर_device_present(gp->dev)) अणु
		gp->phy_mii.स्वतःneg = gp->want_स्वतःneg = स्वतःneg;
		gp->phy_mii.speed = speed;
		gp->phy_mii.duplex = duplex;
		वापस;
	पूर्ण

	/* Configure PHY & start aneg */
	gp->want_स्वतःneg = स्वतःneg;
	अगर (स्वतःneg) अणु
		अगर (found_mii_phy(gp))
			gp->phy_mii.def->ops->setup_aneg(&gp->phy_mii, advertise);
		gp->lstate = link_aneg;
	पूर्ण अन्यथा अणु
		अगर (found_mii_phy(gp))
			gp->phy_mii.def->ops->setup_क्रमced(&gp->phy_mii, speed, duplex);
		gp->lstate = link_क्रमce_ok;
	पूर्ण

non_mii:
	gp->समयr_ticks = 0;
	mod_समयr(&gp->link_समयr, jअगरfies + ((12 * HZ) / 10));
पूर्ण

/* A link-up condition has occurred, initialize and enable the
 * rest of the chip.
 */
अटल पूर्णांक gem_set_link_modes(काष्ठा gem *gp)
अणु
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(gp->dev, 0);
	पूर्णांक full_duplex, speed, छोड़ो;
	u32 val;

	full_duplex = 0;
	speed = SPEED_10;
	छोड़ो = 0;

	अगर (found_mii_phy(gp)) अणु
	    	अगर (gp->phy_mii.def->ops->पढ़ो_link(&gp->phy_mii))
	    		वापस 1;
		full_duplex = (gp->phy_mii.duplex == DUPLEX_FULL);
		speed = gp->phy_mii.speed;
		छोड़ो = gp->phy_mii.छोड़ो;
	पूर्ण अन्यथा अगर (gp->phy_type == phy_serialink ||
	    	   gp->phy_type == phy_serdes) अणु
		u32 pcs_lpa = पढ़ोl(gp->regs + PCS_MIILP);

		अगर ((pcs_lpa & PCS_MIIADV_FD) || gp->phy_type == phy_serdes)
			full_duplex = 1;
		speed = SPEED_1000;
	पूर्ण

	netअगर_info(gp, link, gp->dev, "Link is up at %d Mbps, %s-duplex\n",
		   speed, (full_duplex ? "full" : "half"));


	/* We take the tx queue lock to aव्योम collisions between
	 * this code, the tx path and the NAPI-driven error path
	 */
	__netअगर_tx_lock(txq, smp_processor_id());

	val = (MAC_TXCFG_EIPG0 | MAC_TXCFG_NGU);
	अगर (full_duplex) अणु
		val |= (MAC_TXCFG_ICS | MAC_TXCFG_ICOLL);
	पूर्ण अन्यथा अणु
		/* MAC_TXCFG_NBO must be zero. */
	पूर्ण
	ग_लिखोl(val, gp->regs + MAC_TXCFG);

	val = (MAC_XIFCFG_OE | MAC_XIFCFG_LLED);
	अगर (!full_duplex &&
	    (gp->phy_type == phy_mii_mdio0 ||
	     gp->phy_type == phy_mii_mdio1)) अणु
		val |= MAC_XIFCFG_DISE;
	पूर्ण अन्यथा अगर (full_duplex) अणु
		val |= MAC_XIFCFG_FLED;
	पूर्ण

	अगर (speed == SPEED_1000)
		val |= (MAC_XIFCFG_GMII);

	ग_लिखोl(val, gp->regs + MAC_XIFCFG);

	/* If gigabit and half-duplex, enable carrier extension
	 * mode.  Else, disable it.
	 */
	अगर (speed == SPEED_1000 && !full_duplex) अणु
		val = पढ़ोl(gp->regs + MAC_TXCFG);
		ग_लिखोl(val | MAC_TXCFG_TCE, gp->regs + MAC_TXCFG);

		val = पढ़ोl(gp->regs + MAC_RXCFG);
		ग_लिखोl(val | MAC_RXCFG_RCE, gp->regs + MAC_RXCFG);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(gp->regs + MAC_TXCFG);
		ग_लिखोl(val & ~MAC_TXCFG_TCE, gp->regs + MAC_TXCFG);

		val = पढ़ोl(gp->regs + MAC_RXCFG);
		ग_लिखोl(val & ~MAC_RXCFG_RCE, gp->regs + MAC_RXCFG);
	पूर्ण

	अगर (gp->phy_type == phy_serialink ||
	    gp->phy_type == phy_serdes) अणु
 		u32 pcs_lpa = पढ़ोl(gp->regs + PCS_MIILP);

		अगर (pcs_lpa & (PCS_MIIADV_SP | PCS_MIIADV_AP))
			छोड़ो = 1;
	पूर्ण

	अगर (!full_duplex)
		ग_लिखोl(512, gp->regs + MAC_STIME);
	अन्यथा
		ग_लिखोl(64, gp->regs + MAC_STIME);
	val = पढ़ोl(gp->regs + MAC_MCCFG);
	अगर (छोड़ो)
		val |= (MAC_MCCFG_SPE | MAC_MCCFG_RPE);
	अन्यथा
		val &= ~(MAC_MCCFG_SPE | MAC_MCCFG_RPE);
	ग_लिखोl(val, gp->regs + MAC_MCCFG);

	gem_start_dma(gp);

	__netअगर_tx_unlock(txq);

	अगर (netअगर_msg_link(gp)) अणु
		अगर (छोड़ो) अणु
			netdev_info(gp->dev,
				    "Pause is enabled (rxfifo: %d off: %d on: %d)\n",
				    gp->rx_fअगरo_sz,
				    gp->rx_छोड़ो_off,
				    gp->rx_छोड़ो_on);
		पूर्ण अन्यथा अणु
			netdev_info(gp->dev, "Pause is disabled\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gem_mdio_link_not_up(काष्ठा gem *gp)
अणु
	चयन (gp->lstate) अणु
	हाल link_क्रमce_ret:
		netअगर_info(gp, link, gp->dev,
			   "Autoneg failed again, keeping forced mode\n");
		gp->phy_mii.def->ops->setup_क्रमced(&gp->phy_mii,
			gp->last_क्रमced_speed, DUPLEX_HALF);
		gp->समयr_ticks = 5;
		gp->lstate = link_क्रमce_ok;
		वापस 0;
	हाल link_aneg:
		/* We try क्रमced modes after a failed aneg only on PHYs that करोn't
		 * have "magic_aneg" bit set, which means they पूर्णांकernally करो the
		 * जबतक क्रमced-mode thingy. On these, we just restart aneg
		 */
		अगर (gp->phy_mii.def->magic_aneg)
			वापस 1;
		netअगर_info(gp, link, gp->dev, "switching to forced 100bt\n");
		/* Try क्रमced modes. */
		gp->phy_mii.def->ops->setup_क्रमced(&gp->phy_mii, SPEED_100,
			DUPLEX_HALF);
		gp->समयr_ticks = 5;
		gp->lstate = link_क्रमce_try;
		वापस 0;
	हाल link_क्रमce_try:
		/* Downgrade from 100 to 10 Mbps अगर necessary.
		 * If alपढ़ोy at 10Mbps, warn user about the
		 * situation every 10 ticks.
		 */
		अगर (gp->phy_mii.speed == SPEED_100) अणु
			gp->phy_mii.def->ops->setup_क्रमced(&gp->phy_mii, SPEED_10,
				DUPLEX_HALF);
			gp->समयr_ticks = 5;
			netअगर_info(gp, link, gp->dev,
				   "switching to forced 10bt\n");
			वापस 0;
		पूर्ण अन्यथा
			वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम gem_link_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा gem *gp = from_समयr(gp, t, link_समयr);
	काष्ठा net_device *dev = gp->dev;
	पूर्णांक restart_aneg = 0;

	/* There's no point doing anything if we're going to be reset */
	अगर (gp->reset_task_pending)
		वापस;

	अगर (gp->phy_type == phy_serialink ||
	    gp->phy_type == phy_serdes) अणु
		u32 val = पढ़ोl(gp->regs + PCS_MIISTAT);

		अगर (!(val & PCS_MIISTAT_LS))
			val = पढ़ोl(gp->regs + PCS_MIISTAT);

		अगर ((val & PCS_MIISTAT_LS) != 0) अणु
			अगर (gp->lstate == link_up)
				जाओ restart;

			gp->lstate = link_up;
			netअगर_carrier_on(dev);
			(व्योम)gem_set_link_modes(gp);
		पूर्ण
		जाओ restart;
	पूर्ण
	अगर (found_mii_phy(gp) && gp->phy_mii.def->ops->poll_link(&gp->phy_mii)) अणु
		/* Ok, here we got a link. If we had it due to a क्रमced
		 * fallback, and we were configured क्रम स्वतःneg, we करो
		 * retry a लघु स्वतःneg pass. If you know your hub is
		 * broken, use ethtool ;)
		 */
		अगर (gp->lstate == link_क्रमce_try && gp->want_स्वतःneg) अणु
			gp->lstate = link_क्रमce_ret;
			gp->last_क्रमced_speed = gp->phy_mii.speed;
			gp->समयr_ticks = 5;
			अगर (netअगर_msg_link(gp))
				netdev_info(dev,
					    "Got link after fallback, retrying autoneg once...\n");
			gp->phy_mii.def->ops->setup_aneg(&gp->phy_mii, gp->phy_mii.advertising);
		पूर्ण अन्यथा अगर (gp->lstate != link_up) अणु
			gp->lstate = link_up;
			netअगर_carrier_on(dev);
			अगर (gem_set_link_modes(gp))
				restart_aneg = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If the link was previously up, we restart the
		 * whole process
		 */
		अगर (gp->lstate == link_up) अणु
			gp->lstate = link_करोwn;
			netअगर_info(gp, link, dev, "Link down\n");
			netअगर_carrier_off(dev);
			gem_schedule_reset(gp);
			/* The reset task will restart the समयr */
			वापस;
		पूर्ण अन्यथा अगर (++gp->समयr_ticks > 10) अणु
			अगर (found_mii_phy(gp))
				restart_aneg = gem_mdio_link_not_up(gp);
			अन्यथा
				restart_aneg = 1;
		पूर्ण
	पूर्ण
	अगर (restart_aneg) अणु
		gem_begin_स्वतः_negotiation(gp, शून्य);
		वापस;
	पूर्ण
restart:
	mod_समयr(&gp->link_समयr, jअगरfies + ((12 * HZ) / 10));
पूर्ण

अटल व्योम gem_clean_rings(काष्ठा gem *gp)
अणु
	काष्ठा gem_init_block *gb = gp->init_block;
	काष्ठा sk_buff *skb;
	पूर्णांक i;
	dma_addr_t dma_addr;

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा gem_rxd *rxd;

		rxd = &gb->rxd[i];
		अगर (gp->rx_skbs[i] != शून्य) अणु
			skb = gp->rx_skbs[i];
			dma_addr = le64_to_cpu(rxd->buffer);
			dma_unmap_page(&gp->pdev->dev, dma_addr,
				       RX_BUF_ALLOC_SIZE(gp),
				       DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(skb);
			gp->rx_skbs[i] = शून्य;
		पूर्ण
		rxd->status_word = 0;
		dma_wmb();
		rxd->buffer = 0;
	पूर्ण

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		अगर (gp->tx_skbs[i] != शून्य) अणु
			काष्ठा gem_txd *txd;
			पूर्णांक frag;

			skb = gp->tx_skbs[i];
			gp->tx_skbs[i] = शून्य;

			क्रम (frag = 0; frag <= skb_shinfo(skb)->nr_frags; frag++) अणु
				पूर्णांक ent = i & (TX_RING_SIZE - 1);

				txd = &gb->txd[ent];
				dma_addr = le64_to_cpu(txd->buffer);
				dma_unmap_page(&gp->pdev->dev, dma_addr,
					       le64_to_cpu(txd->control_word) &
					       TXDCTRL_BUFSZ, DMA_TO_DEVICE);

				अगर (frag != skb_shinfo(skb)->nr_frags)
					i++;
			पूर्ण
			dev_kमुक्त_skb_any(skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gem_init_rings(काष्ठा gem *gp)
अणु
	काष्ठा gem_init_block *gb = gp->init_block;
	काष्ठा net_device *dev = gp->dev;
	पूर्णांक i;
	dma_addr_t dma_addr;

	gp->rx_new = gp->rx_old = gp->tx_new = gp->tx_old = 0;

	gem_clean_rings(gp);

	gp->rx_buf_sz = max(dev->mtu + ETH_HLEN + VLAN_HLEN,
			    (अचिन्हित)VLAN_ETH_FRAME_LEN);

	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		काष्ठा sk_buff *skb;
		काष्ठा gem_rxd *rxd = &gb->rxd[i];

		skb = gem_alloc_skb(dev, RX_BUF_ALLOC_SIZE(gp), GFP_KERNEL);
		अगर (!skb) अणु
			rxd->buffer = 0;
			rxd->status_word = 0;
			जारी;
		पूर्ण

		gp->rx_skbs[i] = skb;
		skb_put(skb, (gp->rx_buf_sz + RX_OFFSET));
		dma_addr = dma_map_page(&gp->pdev->dev,
					virt_to_page(skb->data),
					offset_in_page(skb->data),
					RX_BUF_ALLOC_SIZE(gp),
					DMA_FROM_DEVICE);
		rxd->buffer = cpu_to_le64(dma_addr);
		dma_wmb();
		rxd->status_word = cpu_to_le64(RXDCTRL_FRESH(gp));
		skb_reserve(skb, RX_OFFSET);
	पूर्ण

	क्रम (i = 0; i < TX_RING_SIZE; i++) अणु
		काष्ठा gem_txd *txd = &gb->txd[i];

		txd->control_word = 0;
		dma_wmb();
		txd->buffer = 0;
	पूर्ण
	wmb();
पूर्ण

/* Init PHY पूर्णांकerface and start link poll state machine */
अटल व्योम gem_init_phy(काष्ठा gem *gp)
अणु
	u32 mअगरcfg;

	/* Revert MIF CFG setting करोne on stop_phy */
	mअगरcfg = पढ़ोl(gp->regs + MIF_CFG);
	mअगरcfg &= ~MIF_CFG_BBMODE;
	ग_लिखोl(mअगरcfg, gp->regs + MIF_CFG);

	अगर (gp->pdev->venकरोr == PCI_VENDOR_ID_APPLE) अणु
		पूर्णांक i;

		/* Those delays sucks, the HW seems to love them though, I'll
		 * seriously consider अवरोधing some locks here to be able
		 * to schedule instead
		 */
		क्रम (i = 0; i < 3; i++) अणु
#अगर_घोषित CONFIG_PPC_PMAC
			pmac_call_feature(PMAC_FTR_GMAC_PHY_RESET, gp->of_node, 0, 0);
			msleep(20);
#पूर्ण_अगर
			/* Some PHYs used by apple have problem getting back to us,
			 * we करो an additional reset here
			 */
			sungem_phy_ग_लिखो(gp, MII_BMCR, BMCR_RESET);
			msleep(20);
			अगर (sungem_phy_पढ़ो(gp, MII_BMCR) != 0xffff)
				अवरोध;
			अगर (i == 2)
				netdev_warn(gp->dev, "GMAC PHY not responding !\n");
		पूर्ण
	पूर्ण

	अगर (gp->pdev->venकरोr == PCI_VENDOR_ID_SUN &&
	    gp->pdev->device == PCI_DEVICE_ID_SUN_GEM) अणु
		u32 val;

		/* Init datapath mode रेजिस्टर. */
		अगर (gp->phy_type == phy_mii_mdio0 ||
		    gp->phy_type == phy_mii_mdio1) अणु
			val = PCS_DMODE_MGM;
		पूर्ण अन्यथा अगर (gp->phy_type == phy_serialink) अणु
			val = PCS_DMODE_SM | PCS_DMODE_GMOE;
		पूर्ण अन्यथा अणु
			val = PCS_DMODE_ESM;
		पूर्ण

		ग_लिखोl(val, gp->regs + PCS_DMODE);
	पूर्ण

	अगर (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1) अणु
		/* Reset and detect MII PHY */
		sungem_phy_probe(&gp->phy_mii, gp->mii_phy_addr);

		/* Init PHY */
		अगर (gp->phy_mii.def && gp->phy_mii.def->ops->init)
			gp->phy_mii.def->ops->init(&gp->phy_mii);
	पूर्ण अन्यथा अणु
		gem_pcs_reset(gp);
		gem_pcs_reinit_adv(gp);
	पूर्ण

	/* Default aneg parameters */
	gp->समयr_ticks = 0;
	gp->lstate = link_करोwn;
	netअगर_carrier_off(gp->dev);

	/* Prपूर्णांक things out */
	अगर (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1)
		netdev_info(gp->dev, "Found %s PHY\n",
			    gp->phy_mii.def ? gp->phy_mii.def->name : "no");

	gem_begin_स्वतः_negotiation(gp, शून्य);
पूर्ण

अटल व्योम gem_init_dma(काष्ठा gem *gp)
अणु
	u64 desc_dma = (u64) gp->gblock_dvma;
	u32 val;

	val = (TXDMA_CFG_BASE | (0x7ff << 10) | TXDMA_CFG_PMODE);
	ग_लिखोl(val, gp->regs + TXDMA_CFG);

	ग_लिखोl(desc_dma >> 32, gp->regs + TXDMA_DBHI);
	ग_लिखोl(desc_dma & 0xffffffff, gp->regs + TXDMA_DBLOW);
	desc_dma += (INIT_BLOCK_TX_RING_SIZE * माप(काष्ठा gem_txd));

	ग_लिखोl(0, gp->regs + TXDMA_KICK);

	val = (RXDMA_CFG_BASE | (RX_OFFSET << 10) |
	       (ETH_HLEN << 13) | RXDMA_CFG_FTHRESH_128);
	ग_लिखोl(val, gp->regs + RXDMA_CFG);

	ग_लिखोl(desc_dma >> 32, gp->regs + RXDMA_DBHI);
	ग_लिखोl(desc_dma & 0xffffffff, gp->regs + RXDMA_DBLOW);

	ग_लिखोl(RX_RING_SIZE - 4, gp->regs + RXDMA_KICK);

	val  = (((gp->rx_छोड़ो_off / 64) << 0) & RXDMA_PTHRESH_OFF);
	val |= (((gp->rx_छोड़ो_on / 64) << 12) & RXDMA_PTHRESH_ON);
	ग_लिखोl(val, gp->regs + RXDMA_PTHRESH);

	अगर (पढ़ोl(gp->regs + GREG_BIFCFG) & GREG_BIFCFG_M66EN)
		ग_लिखोl(((5 & RXDMA_BLANK_IPKTS) |
			((8 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
	अन्यथा
		ग_लिखोl(((5 & RXDMA_BLANK_IPKTS) |
			((4 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
पूर्ण

अटल u32 gem_setup_multicast(काष्ठा gem *gp)
अणु
	u32 rxcfg = 0;
	पूर्णांक i;

	अगर ((gp->dev->flags & IFF_ALLMULTI) ||
	    (netdev_mc_count(gp->dev) > 256)) अणु
	    	क्रम (i=0; i<16; i++)
			ग_लिखोl(0xffff, gp->regs + MAC_HASH0 + (i << 2));
		rxcfg |= MAC_RXCFG_HFE;
	पूर्ण अन्यथा अगर (gp->dev->flags & IFF_PROMISC) अणु
		rxcfg |= MAC_RXCFG_PROM;
	पूर्ण अन्यथा अणु
		u16 hash_table[16];
		u32 crc;
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक i;

		स_रखो(hash_table, 0, माप(hash_table));
		netdev_क्रम_each_mc_addr(ha, gp->dev) अणु
			crc = ether_crc_le(6, ha->addr);
			crc >>= 24;
			hash_table[crc >> 4] |= 1 << (15 - (crc & 0xf));
		पूर्ण
	    	क्रम (i=0; i<16; i++)
			ग_लिखोl(hash_table[i], gp->regs + MAC_HASH0 + (i << 2));
		rxcfg |= MAC_RXCFG_HFE;
	पूर्ण

	वापस rxcfg;
पूर्ण

अटल व्योम gem_init_mac(काष्ठा gem *gp)
अणु
	अचिन्हित अक्षर *e = &gp->dev->dev_addr[0];

	ग_लिखोl(0x1bf0, gp->regs + MAC_SNDPAUSE);

	ग_लिखोl(0x00, gp->regs + MAC_IPG0);
	ग_लिखोl(0x08, gp->regs + MAC_IPG1);
	ग_लिखोl(0x04, gp->regs + MAC_IPG2);
	ग_लिखोl(0x40, gp->regs + MAC_STIME);
	ग_लिखोl(0x40, gp->regs + MAC_MINFSZ);

	/* Ethernet payload + header + FCS + optional VLAN tag. */
	ग_लिखोl(0x20000000 | (gp->rx_buf_sz + 4), gp->regs + MAC_MAXFSZ);

	ग_लिखोl(0x07, gp->regs + MAC_PASIZE);
	ग_लिखोl(0x04, gp->regs + MAC_JAMSIZE);
	ग_लिखोl(0x10, gp->regs + MAC_ATTLIM);
	ग_लिखोl(0x8808, gp->regs + MAC_MCTYPE);

	ग_लिखोl((e[5] | (e[4] << 8)) & 0x3ff, gp->regs + MAC_RANDSEED);

	ग_लिखोl((e[4] << 8) | e[5], gp->regs + MAC_ADDR0);
	ग_लिखोl((e[2] << 8) | e[3], gp->regs + MAC_ADDR1);
	ग_लिखोl((e[0] << 8) | e[1], gp->regs + MAC_ADDR2);

	ग_लिखोl(0, gp->regs + MAC_ADDR3);
	ग_लिखोl(0, gp->regs + MAC_ADDR4);
	ग_लिखोl(0, gp->regs + MAC_ADDR5);

	ग_लिखोl(0x0001, gp->regs + MAC_ADDR6);
	ग_लिखोl(0xc200, gp->regs + MAC_ADDR7);
	ग_लिखोl(0x0180, gp->regs + MAC_ADDR8);

	ग_लिखोl(0, gp->regs + MAC_AFILT0);
	ग_लिखोl(0, gp->regs + MAC_AFILT1);
	ग_लिखोl(0, gp->regs + MAC_AFILT2);
	ग_लिखोl(0, gp->regs + MAC_AF21MSK);
	ग_लिखोl(0, gp->regs + MAC_AF0MSK);

	gp->mac_rx_cfg = gem_setup_multicast(gp);
#अगर_घोषित STRIP_FCS
	gp->mac_rx_cfg |= MAC_RXCFG_SFCS;
#पूर्ण_अगर
	ग_लिखोl(0, gp->regs + MAC_NCOLL);
	ग_लिखोl(0, gp->regs + MAC_FASUCC);
	ग_लिखोl(0, gp->regs + MAC_ECOLL);
	ग_लिखोl(0, gp->regs + MAC_LCOLL);
	ग_लिखोl(0, gp->regs + MAC_DTIMER);
	ग_लिखोl(0, gp->regs + MAC_PATMPS);
	ग_लिखोl(0, gp->regs + MAC_RFCTR);
	ग_लिखोl(0, gp->regs + MAC_LERR);
	ग_लिखोl(0, gp->regs + MAC_AERR);
	ग_लिखोl(0, gp->regs + MAC_FCSERR);
	ग_लिखोl(0, gp->regs + MAC_RXCVERR);

	/* Clear RX/TX/MAC/XIF config, we will set these up and enable
	 * them once a link is established.
	 */
	ग_लिखोl(0, gp->regs + MAC_TXCFG);
	ग_लिखोl(gp->mac_rx_cfg, gp->regs + MAC_RXCFG);
	ग_लिखोl(0, gp->regs + MAC_MCCFG);
	ग_लिखोl(0, gp->regs + MAC_XIFCFG);

	/* Setup MAC पूर्णांकerrupts.  We want to get all of the पूर्णांकeresting
	 * counter expiration events, but we करो not want to hear about
	 * normal rx/tx as the DMA engine tells us that.
	 */
	ग_लिखोl(MAC_TXSTAT_XMIT, gp->regs + MAC_TXMASK);
	ग_लिखोl(MAC_RXSTAT_RCV, gp->regs + MAC_RXMASK);

	/* Don't enable even the PAUSE पूर्णांकerrupts क्रम now, we
	 * make no use of those events other than to record them.
	 */
	ग_लिखोl(0xffffffff, gp->regs + MAC_MCMASK);

	/* Don't enable GEM's WOL in normal operations
	 */
	अगर (gp->has_wol)
		ग_लिखोl(0, gp->regs + WOL_WAKECSR);
पूर्ण

अटल व्योम gem_init_छोड़ो_thresholds(काष्ठा gem *gp)
अणु
       	u32 cfg;

	/* Calculate छोड़ो thresholds.  Setting the OFF threshold to the
	 * full RX fअगरo size effectively disables PAUSE generation which
	 * is what we करो क्रम 10/100 only GEMs which have FIFOs too small
	 * to make real gains from PAUSE.
	 */
	अगर (gp->rx_fअगरo_sz <= (2 * 1024)) अणु
		gp->rx_छोड़ो_off = gp->rx_छोड़ो_on = gp->rx_fअगरo_sz;
	पूर्ण अन्यथा अणु
		पूर्णांक max_frame = (gp->rx_buf_sz + 4 + 64) & ~63;
		पूर्णांक off = (gp->rx_fअगरo_sz - (max_frame * 2));
		पूर्णांक on = off - max_frame;

		gp->rx_छोड़ो_off = off;
		gp->rx_छोड़ो_on = on;
	पूर्ण


	/* Configure the chip "burst" DMA mode & enable some
	 * HW bug fixes on Apple version
	 */
       	cfg  = 0;
       	अगर (gp->pdev->venकरोr == PCI_VENDOR_ID_APPLE)
		cfg |= GREG_CFG_RONPAULBIT | GREG_CFG_ENBUG2FIX;
#अगर !defined(CONFIG_SPARC64) && !defined(CONFIG_ALPHA)
       	cfg |= GREG_CFG_IBURST;
#पूर्ण_अगर
       	cfg |= ((31 << 1) & GREG_CFG_TXDMALIM);
       	cfg |= ((31 << 6) & GREG_CFG_RXDMALIM);
       	ग_लिखोl(cfg, gp->regs + GREG_CFG);

	/* If Infinite Burst didn't stick, then use dअगरferent
	 * thresholds (and Apple bug fixes करोn't exist)
	 */
	अगर (!(पढ़ोl(gp->regs + GREG_CFG) & GREG_CFG_IBURST)) अणु
		cfg = ((2 << 1) & GREG_CFG_TXDMALIM);
		cfg |= ((8 << 6) & GREG_CFG_RXDMALIM);
		ग_लिखोl(cfg, gp->regs + GREG_CFG);
	पूर्ण
पूर्ण

अटल पूर्णांक gem_check_invariants(काष्ठा gem *gp)
अणु
	काष्ठा pci_dev *pdev = gp->pdev;
	u32 mअगर_cfg;

	/* On Apple's sungem, we can't rely on रेजिस्टरs as the chip
	 * was been घातered करोwn by the firmware. The PHY is looked
	 * up later on.
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_APPLE) अणु
		gp->phy_type = phy_mii_mdio0;
		gp->tx_fअगरo_sz = पढ़ोl(gp->regs + TXDMA_FSZ) * 64;
		gp->rx_fअगरo_sz = पढ़ोl(gp->regs + RXDMA_FSZ) * 64;
		gp->swrst_base = 0;

		mअगर_cfg = पढ़ोl(gp->regs + MIF_CFG);
		mअगर_cfg &= ~(MIF_CFG_PSELECT|MIF_CFG_POLL|MIF_CFG_BBMODE|MIF_CFG_MDI1);
		mअगर_cfg |= MIF_CFG_MDI0;
		ग_लिखोl(mअगर_cfg, gp->regs + MIF_CFG);
		ग_लिखोl(PCS_DMODE_MGM, gp->regs + PCS_DMODE);
		ग_लिखोl(MAC_XIFCFG_OE, gp->regs + MAC_XIFCFG);

		/* We hard-code the PHY address so we can properly bring it out of
		 * reset later on, we can't really probe it at this poपूर्णांक, though
		 * that isn't an issue.
		 */
		अगर (gp->pdev->device == PCI_DEVICE_ID_APPLE_K2_GMAC)
			gp->mii_phy_addr = 1;
		अन्यथा
			gp->mii_phy_addr = 0;

		वापस 0;
	पूर्ण

	mअगर_cfg = पढ़ोl(gp->regs + MIF_CFG);

	अगर (pdev->venकरोr == PCI_VENDOR_ID_SUN &&
	    pdev->device == PCI_DEVICE_ID_SUN_RIO_GEM) अणु
		/* One of the MII PHYs _must_ be present
		 * as this chip has no gigabit PHY.
		 */
		अगर ((mअगर_cfg & (MIF_CFG_MDI0 | MIF_CFG_MDI1)) == 0) अणु
			pr_err("RIO GEM lacks MII phy, mif_cfg[%08x]\n",
			       mअगर_cfg);
			वापस -1;
		पूर्ण
	पूर्ण

	/* Determine initial PHY पूर्णांकerface type guess.  MDIO1 is the
	 * बाह्यal PHY and thus takes precedence over MDIO0.
	 */

	अगर (mअगर_cfg & MIF_CFG_MDI1) अणु
		gp->phy_type = phy_mii_mdio1;
		mअगर_cfg |= MIF_CFG_PSELECT;
		ग_लिखोl(mअगर_cfg, gp->regs + MIF_CFG);
	पूर्ण अन्यथा अगर (mअगर_cfg & MIF_CFG_MDI0) अणु
		gp->phy_type = phy_mii_mdio0;
		mअगर_cfg &= ~MIF_CFG_PSELECT;
		ग_लिखोl(mअगर_cfg, gp->regs + MIF_CFG);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_SPARC
		स्थिर अक्षर *p;

		p = of_get_property(gp->of_node, "shared-pins", शून्य);
		अगर (p && !म_भेद(p, "serdes"))
			gp->phy_type = phy_serdes;
		अन्यथा
#पूर्ण_अगर
			gp->phy_type = phy_serialink;
	पूर्ण
	अगर (gp->phy_type == phy_mii_mdio1 ||
	    gp->phy_type == phy_mii_mdio0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 32; i++) अणु
			gp->mii_phy_addr = i;
			अगर (sungem_phy_पढ़ो(gp, MII_BMCR) != 0xffff)
				अवरोध;
		पूर्ण
		अगर (i == 32) अणु
			अगर (pdev->device != PCI_DEVICE_ID_SUN_GEM) अणु
				pr_err("RIO MII phy will not respond\n");
				वापस -1;
			पूर्ण
			gp->phy_type = phy_serdes;
		पूर्ण
	पूर्ण

	/* Fetch the FIFO configurations now too. */
	gp->tx_fअगरo_sz = पढ़ोl(gp->regs + TXDMA_FSZ) * 64;
	gp->rx_fअगरo_sz = पढ़ोl(gp->regs + RXDMA_FSZ) * 64;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_SUN) अणु
		अगर (pdev->device == PCI_DEVICE_ID_SUN_GEM) अणु
			अगर (gp->tx_fअगरo_sz != (9 * 1024) ||
			    gp->rx_fअगरo_sz != (20 * 1024)) अणु
				pr_err("GEM has bogus fifo sizes tx(%d) rx(%d)\n",
				       gp->tx_fअगरo_sz, gp->rx_fअगरo_sz);
				वापस -1;
			पूर्ण
			gp->swrst_base = 0;
		पूर्ण अन्यथा अणु
			अगर (gp->tx_fअगरo_sz != (2 * 1024) ||
			    gp->rx_fअगरo_sz != (2 * 1024)) अणु
				pr_err("RIO GEM has bogus fifo sizes tx(%d) rx(%d)\n",
				       gp->tx_fअगरo_sz, gp->rx_fअगरo_sz);
				वापस -1;
			पूर्ण
			gp->swrst_base = (64 / 4) << GREG_SWRST_CACHE_SHIFT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gem_reinit_chip(काष्ठा gem *gp)
अणु
	/* Reset the chip */
	gem_reset(gp);

	/* Make sure पूर्णांकs are disabled */
	gem_disable_पूर्णांकs(gp);

	/* Allocate & setup ring buffers */
	gem_init_rings(gp);

	/* Configure छोड़ो thresholds */
	gem_init_छोड़ो_thresholds(gp);

	/* Init DMA & MAC engines */
	gem_init_dma(gp);
	gem_init_mac(gp);
पूर्ण


अटल व्योम gem_stop_phy(काष्ठा gem *gp, पूर्णांक wol)
अणु
	u32 mअगरcfg;

	/* Let the chip settle करोwn a bit, it seems that helps
	 * क्रम sleep mode on some models
	 */
	msleep(10);

	/* Make sure we aren't polling PHY status change. We
	 * करोn't currently use that feature though
	 */
	mअगरcfg = पढ़ोl(gp->regs + MIF_CFG);
	mअगरcfg &= ~MIF_CFG_POLL;
	ग_लिखोl(mअगरcfg, gp->regs + MIF_CFG);

	अगर (wol && gp->has_wol) अणु
		अचिन्हित अक्षर *e = &gp->dev->dev_addr[0];
		u32 csr;

		/* Setup wake-on-lan क्रम MAGIC packet */
		ग_लिखोl(MAC_RXCFG_HFE | MAC_RXCFG_SFCS | MAC_RXCFG_ENAB,
		       gp->regs + MAC_RXCFG);
		ग_लिखोl((e[4] << 8) | e[5], gp->regs + WOL_MATCH0);
		ग_लिखोl((e[2] << 8) | e[3], gp->regs + WOL_MATCH1);
		ग_लिखोl((e[0] << 8) | e[1], gp->regs + WOL_MATCH2);

		ग_लिखोl(WOL_MCOUNT_N | WOL_MCOUNT_M, gp->regs + WOL_MCOUNT);
		csr = WOL_WAKECSR_ENABLE;
		अगर ((पढ़ोl(gp->regs + MAC_XIFCFG) & MAC_XIFCFG_GMII) == 0)
			csr |= WOL_WAKECSR_MII;
		ग_लिखोl(csr, gp->regs + WOL_WAKECSR);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, gp->regs + MAC_RXCFG);
		(व्योम)पढ़ोl(gp->regs + MAC_RXCFG);
		/* Machine sleep will die in strange ways अगर we
		 * करोnt रुको a bit here, looks like the chip takes
		 * some समय to really shut करोwn
		 */
		msleep(10);
	पूर्ण

	ग_लिखोl(0, gp->regs + MAC_TXCFG);
	ग_लिखोl(0, gp->regs + MAC_XIFCFG);
	ग_लिखोl(0, gp->regs + TXDMA_CFG);
	ग_लिखोl(0, gp->regs + RXDMA_CFG);

	अगर (!wol) अणु
		gem_reset(gp);
		ग_लिखोl(MAC_TXRST_CMD, gp->regs + MAC_TXRST);
		ग_लिखोl(MAC_RXRST_CMD, gp->regs + MAC_RXRST);

		अगर (found_mii_phy(gp) && gp->phy_mii.def->ops->suspend)
			gp->phy_mii.def->ops->suspend(&gp->phy_mii);

		/* According to Apple, we must set the MDIO pins to this begnign
		 * state or we may 1) eat more current, 2) damage some PHYs
		 */
		ग_लिखोl(mअगरcfg | MIF_CFG_BBMODE, gp->regs + MIF_CFG);
		ग_लिखोl(0, gp->regs + MIF_BBCLK);
		ग_लिखोl(0, gp->regs + MIF_BBDATA);
		ग_लिखोl(0, gp->regs + MIF_BBOENAB);
		ग_लिखोl(MAC_XIFCFG_GMII | MAC_XIFCFG_LBCK, gp->regs + MAC_XIFCFG);
		(व्योम) पढ़ोl(gp->regs + MAC_XIFCFG);
	पूर्ण
पूर्ण

अटल पूर्णांक gem_करो_start(काष्ठा net_device *dev)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	पूर्णांक rc;

	pci_set_master(gp->pdev);

	/* Init & setup chip hardware */
	gem_reinit_chip(gp);

	/* An पूर्णांकerrupt might come in handy */
	rc = request_irq(gp->pdev->irq, gem_पूर्णांकerrupt,
			 IRQF_SHARED, dev->name, (व्योम *)dev);
	अगर (rc) अणु
		netdev_err(dev, "failed to request irq !\n");

		gem_reset(gp);
		gem_clean_rings(gp);
		gem_put_cell(gp);
		वापस rc;
	पूर्ण

	/* Mark us as attached again अगर we come from resume(), this has
	 * no effect अगर we weren't detached and needs to be करोne now.
	 */
	netअगर_device_attach(dev);

	/* Restart NAPI & queues */
	gem_netअगर_start(gp);

	/* Detect & init PHY, start स्वतःneg etc... this will
	 * eventually result in starting DMA operations when
	 * the link is up
	 */
	gem_init_phy(gp);

	वापस 0;
पूर्ण

अटल व्योम gem_करो_stop(काष्ठा net_device *dev, पूर्णांक wol)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	/* Stop NAPI and stop tx queue */
	gem_netअगर_stop(gp);

	/* Make sure पूर्णांकs are disabled. We करोn't care about
	 * synchronizing as NAPI is disabled, thus a stray
	 * पूर्णांकerrupt will करो nothing bad (our irq handler
	 * just schedules NAPI)
	 */
	gem_disable_पूर्णांकs(gp);

	/* Stop the link समयr */
	del_समयr_sync(&gp->link_समयr);

	/* We cannot cancel the reset task जबतक holding the
	 * rtnl lock, we'd get an A->B / B->A deadlock stituation
	 * अगर we did. This is not an issue however as the reset
	 * task is synchronized vs. us (rtnl_lock) and will करो
	 * nothing अगर the device is करोwn or suspended. We करो
	 * still clear reset_task_pending to aव्योम a spurrious
	 * reset later on in हाल we करो resume beक्रमe it माला_लो
	 * scheduled.
	 */
	gp->reset_task_pending = 0;

	/* If we are going to sleep with WOL */
	gem_stop_dma(gp);
	msleep(10);
	अगर (!wol)
		gem_reset(gp);
	msleep(10);

	/* Get rid of rings */
	gem_clean_rings(gp);

	/* No irq needed anymore */
	मुक्त_irq(gp->pdev->irq, (व्योम *) dev);

	/* Shut the PHY करोwn eventually and setup WOL */
	gem_stop_phy(gp, wol);
पूर्ण

अटल व्योम gem_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gem *gp = container_of(work, काष्ठा gem, reset_task);

	/* Lock out the network stack (essentially shield ourselves
	 * against a racing खोलो, बंद, control call, or suspend
	 */
	rtnl_lock();

	/* Skip the reset task अगर suspended or बंदd, or अगर it's
	 * been cancelled by gem_करो_stop (see comment there)
	 */
	अगर (!netअगर_device_present(gp->dev) ||
	    !netअगर_running(gp->dev) ||
	    !gp->reset_task_pending) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	/* Stop the link समयr */
	del_समयr_sync(&gp->link_समयr);

	/* Stop NAPI and tx */
	gem_netअगर_stop(gp);

	/* Reset the chip & rings */
	gem_reinit_chip(gp);
	अगर (gp->lstate == link_up)
		gem_set_link_modes(gp);

	/* Restart NAPI and Tx */
	gem_netअगर_start(gp);

	/* We are back ! */
	gp->reset_task_pending = 0;

	/* If the link is not up, restart स्वतःneg, अन्यथा restart the
	 * polling समयr
	 */
	अगर (gp->lstate != link_up)
		gem_begin_स्वतः_negotiation(gp, शून्य);
	अन्यथा
		mod_समयr(&gp->link_समयr, jअगरfies + ((12 * HZ) / 10));

	rtnl_unlock();
पूर्ण

अटल पूर्णांक gem_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	पूर्णांक rc;

	/* We allow खोलो जबतक suspended, we just करो nothing,
	 * the chip will be initialized in resume()
	 */
	अगर (netअगर_device_present(dev)) अणु
		/* Enable the cell */
		gem_get_cell(gp);

		/* Make sure PCI access and bus master are enabled */
		rc = pci_enable_device(gp->pdev);
		अगर (rc) अणु
			netdev_err(dev, "Failed to enable chip on PCI bus !\n");

			/* Put cell and क्रमget it क्रम now, it will be considered
			 *as still asleep, a new sleep cycle may bring it back
			 */
			gem_put_cell(gp);
			वापस -ENXIO;
		पूर्ण
		वापस gem_करो_start(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gem_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	अगर (netअगर_device_present(dev)) अणु
		gem_करो_stop(dev, 0);

		/* Make sure bus master is disabled */
		pci_disable_device(gp->pdev);

		/* Cell not needed neither अगर no WOL */
		अगर (!gp->asleep_wol)
			gem_put_cell(gp);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gem_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा gem *gp = netdev_priv(dev);

	/* Lock the network stack first to aव्योम racing with खोलो/बंद,
	 * reset task and setting calls
	 */
	rtnl_lock();

	/* Not running, mark ourselves non-present, no need क्रम
	 * a lock here
	 */
	अगर (!netअगर_running(dev)) अणु
		netअगर_device_detach(dev);
		rtnl_unlock();
		वापस 0;
	पूर्ण
	netdev_info(dev, "suspending, WakeOnLan %s\n",
		    (gp->wake_on_lan && netअगर_running(dev)) ?
		    "enabled" : "disabled");

	/* Tell the network stack we're gone. gem_करो_stop() below will
	 * synchronize with TX, stop NAPI etc...
	 */
	netअगर_device_detach(dev);

	/* Switch off chip, remember WOL setting */
	gp->asleep_wol = !!gp->wake_on_lan;
	gem_करो_stop(dev, gp->asleep_wol);

	/* Cell not needed neither अगर no WOL */
	अगर (!gp->asleep_wol)
		gem_put_cell(gp);

	/* Unlock the network stack */
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gem_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा gem *gp = netdev_priv(dev);

	/* See locking comment in gem_suspend */
	rtnl_lock();

	/* Not running, mark ourselves present, no need क्रम
	 * a lock here
	 */
	अगर (!netअगर_running(dev)) अणु
		netअगर_device_attach(dev);
		rtnl_unlock();
		वापस 0;
	पूर्ण

	/* Enable the cell */
	gem_get_cell(gp);

	/* Restart chip. If that fails there isn't much we can करो, we
	 * leave things stopped.
	 */
	gem_करो_start(dev);

	/* If we had WOL enabled, the cell घड़ी was never turned off during
	 * sleep, so we end up beeing unbalanced. Fix that here
	 */
	अगर (gp->asleep_wol)
		gem_put_cell(gp);

	/* Unlock the network stack */
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *gem_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	/* I have seen this being called जबतक the PM was in progress,
	 * so we shield against this. Let's also not poke at रेजिस्टरs
	 * जबतक the reset task is going on.
	 *
	 * TODO: Move stats collection अन्यथाwhere (link समयr ?) and
	 * make this a nop to aव्योम all those synchro issues
	 */
	अगर (!netअगर_device_present(dev) || !netअगर_running(dev))
		जाओ bail;

	/* Better safe than sorry... */
	अगर (WARN_ON(!gp->cell_enabled))
		जाओ bail;

	dev->stats.rx_crc_errors += पढ़ोl(gp->regs + MAC_FCSERR);
	ग_लिखोl(0, gp->regs + MAC_FCSERR);

	dev->stats.rx_frame_errors += पढ़ोl(gp->regs + MAC_AERR);
	ग_लिखोl(0, gp->regs + MAC_AERR);

	dev->stats.rx_length_errors += पढ़ोl(gp->regs + MAC_LERR);
	ग_लिखोl(0, gp->regs + MAC_LERR);

	dev->stats.tx_पातed_errors += पढ़ोl(gp->regs + MAC_ECOLL);
	dev->stats.collisions +=
		(पढ़ोl(gp->regs + MAC_ECOLL) + पढ़ोl(gp->regs + MAC_LCOLL));
	ग_लिखोl(0, gp->regs + MAC_ECOLL);
	ग_लिखोl(0, gp->regs + MAC_LCOLL);
 bail:
	वापस &dev->stats;
पूर्ण

अटल पूर्णांक gem_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा sockaddr *macaddr = (काष्ठा sockaddr *) addr;
	काष्ठा gem *gp = netdev_priv(dev);
	अचिन्हित अक्षर *e = &dev->dev_addr[0];

	अगर (!is_valid_ether_addr(macaddr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, macaddr->sa_data, dev->addr_len);

	/* We'll just catch it later when the device is up'd or resumed */
	अगर (!netअगर_running(dev) || !netअगर_device_present(dev))
		वापस 0;

	/* Better safe than sorry... */
	अगर (WARN_ON(!gp->cell_enabled))
		वापस 0;

	ग_लिखोl((e[4] << 8) | e[5], gp->regs + MAC_ADDR0);
	ग_लिखोl((e[2] << 8) | e[3], gp->regs + MAC_ADDR1);
	ग_लिखोl((e[0] << 8) | e[1], gp->regs + MAC_ADDR2);

	वापस 0;
पूर्ण

अटल व्योम gem_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	u32 rxcfg, rxcfg_new;
	पूर्णांक limit = 10000;

	अगर (!netअगर_running(dev) || !netअगर_device_present(dev))
		वापस;

	/* Better safe than sorry... */
	अगर (gp->reset_task_pending || WARN_ON(!gp->cell_enabled))
		वापस;

	rxcfg = पढ़ोl(gp->regs + MAC_RXCFG);
	rxcfg_new = gem_setup_multicast(gp);
#अगर_घोषित STRIP_FCS
	rxcfg_new |= MAC_RXCFG_SFCS;
#पूर्ण_अगर
	gp->mac_rx_cfg = rxcfg_new;

	ग_लिखोl(rxcfg & ~MAC_RXCFG_ENAB, gp->regs + MAC_RXCFG);
	जबतक (पढ़ोl(gp->regs + MAC_RXCFG) & MAC_RXCFG_ENAB) अणु
		अगर (!limit--)
			अवरोध;
		udelay(10);
	पूर्ण

	rxcfg &= ~(MAC_RXCFG_PROM | MAC_RXCFG_HFE);
	rxcfg |= rxcfg_new;

	ग_लिखोl(rxcfg, gp->regs + MAC_RXCFG);
पूर्ण

/* Jumbo-grams करोn't seem to work :-( */
#घोषणा GEM_MIN_MTU	ETH_MIN_MTU
#अगर 1
#घोषणा GEM_MAX_MTU	ETH_DATA_LEN
#अन्यथा
#घोषणा GEM_MAX_MTU	9000
#पूर्ण_अगर

अटल पूर्णांक gem_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	dev->mtu = new_mtu;

	/* We'll just catch it later when the device is up'd or resumed */
	अगर (!netअगर_running(dev) || !netअगर_device_present(dev))
		वापस 0;

	/* Better safe than sorry... */
	अगर (WARN_ON(!gp->cell_enabled))
		वापस 0;

	gem_netअगर_stop(gp);
	gem_reinit_chip(gp);
	अगर (gp->lstate == link_up)
		gem_set_link_modes(gp);
	gem_netअगर_start(gp);

	वापस 0;
पूर्ण

अटल व्योम gem_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(gp->pdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक gem_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	u32 supported, advertising;

	अगर (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1) अणु
		अगर (gp->phy_mii.def)
			supported = gp->phy_mii.def->features;
		अन्यथा
			supported = (SUPPORTED_10baseT_Half |
					  SUPPORTED_10baseT_Full);

		/* XXX hardcoded stuff क्रम now */
		cmd->base.port = PORT_MII;
		cmd->base.phy_address = 0; /* XXX fixed PHYAD */

		/* Return current PHY settings */
		cmd->base.स्वतःneg = gp->want_स्वतःneg;
		cmd->base.speed = gp->phy_mii.speed;
		cmd->base.duplex = gp->phy_mii.duplex;
		advertising = gp->phy_mii.advertising;

		/* If we started with a क्रमced mode, we करोn't have a शेष
		 * advertise set, we need to वापस something sensible so
		 * userland can re-enable स्वतःneg properly.
		 */
		अगर (advertising == 0)
			advertising = supported;
	पूर्ण अन्यथा अणु // XXX PCS ?
		supported =
			(SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
			 SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
			 SUPPORTED_Autoneg);
		advertising = supported;
		cmd->base.speed = 0;
		cmd->base.duplex = 0;
		cmd->base.port = 0;
		cmd->base.phy_address = 0;
		cmd->base.स्वतःneg = 0;

		/* serdes means usually a Fibre connector, with most fixed */
		अगर (gp->phy_type == phy_serdes) अणु
			cmd->base.port = PORT_FIBRE;
			supported = (SUPPORTED_1000baseT_Half |
				SUPPORTED_1000baseT_Full |
				SUPPORTED_FIBRE | SUPPORTED_Autoneg |
				SUPPORTED_Pause | SUPPORTED_Asym_Pause);
			advertising = supported;
			अगर (gp->lstate == link_up)
				cmd->base.speed = SPEED_1000;
			cmd->base.duplex = DUPLEX_FULL;
			cmd->base.स्वतःneg = 1;
		पूर्ण
	पूर्ण

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक gem_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	/* Verअगरy the settings we care about. */
	अगर (cmd->base.स्वतःneg != AUTONEG_ENABLE &&
	    cmd->base.स्वतःneg != AUTONEG_DISABLE)
		वापस -EINVAL;

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE &&
	    advertising == 0)
		वापस -EINVAL;

	अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE &&
	    ((speed != SPEED_1000 &&
	      speed != SPEED_100 &&
	      speed != SPEED_10) ||
	     (cmd->base.duplex != DUPLEX_HALF &&
	      cmd->base.duplex != DUPLEX_FULL)))
		वापस -EINVAL;

	/* Apply settings and restart link process. */
	अगर (netअगर_device_present(gp->dev)) अणु
		del_समयr_sync(&gp->link_समयr);
		gem_begin_स्वतः_negotiation(gp, cmd);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gem_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	अगर (!gp->want_स्वतःneg)
		वापस -EINVAL;

	/* Restart link process  */
	अगर (netअगर_device_present(gp->dev)) अणु
		del_समयr_sync(&gp->link_समयr);
		gem_begin_स्वतः_negotiation(gp, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 gem_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	वापस gp->msg_enable;
पूर्ण

अटल व्योम gem_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	gp->msg_enable = value;
पूर्ण


/* Add more when I understand how to program the chip */
/* like WAKE_UCAST | WAKE_MCAST | WAKE_BCAST */

#घोषणा WOL_SUPPORTED_MASK	(WAKE_MAGIC)

अटल व्योम gem_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	/* Add more when I understand how to program the chip */
	अगर (gp->has_wol) अणु
		wol->supported = WOL_SUPPORTED_MASK;
		wol->wolopts = gp->wake_on_lan;
	पूर्ण अन्यथा अणु
		wol->supported = 0;
		wol->wolopts = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक gem_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा gem *gp = netdev_priv(dev);

	अगर (!gp->has_wol)
		वापस -EOPNOTSUPP;
	gp->wake_on_lan = wol->wolopts & WOL_SUPPORTED_MASK;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops gem_ethtool_ops = अणु
	.get_drvinfo		= gem_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.nway_reset		= gem_nway_reset,
	.get_msglevel		= gem_get_msglevel,
	.set_msglevel		= gem_set_msglevel,
	.get_wol		= gem_get_wol,
	.set_wol		= gem_set_wol,
	.get_link_ksettings	= gem_get_link_ksettings,
	.set_link_ksettings	= gem_set_link_ksettings,
पूर्ण;

अटल पूर्णांक gem_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा gem *gp = netdev_priv(dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	पूर्णांक rc = -EOPNOTSUPP;

	/* For SIOCGMIIREG and SIOCSMIIREG the core checks क्रम us that
	 * netअगर_device_present() is true and holds rtnl_lock क्रम us
	 * so we have nothing to worry about
	 */

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:		/* Get address of MII PHY in use. */
		data->phy_id = gp->mii_phy_addr;
		fallthrough;

	हाल SIOCGMIIREG:		/* Read MII PHY रेजिस्टर. */
		data->val_out = __sungem_phy_पढ़ो(gp, data->phy_id & 0x1f,
					   data->reg_num & 0x1f);
		rc = 0;
		अवरोध;

	हाल SIOCSMIIREG:		/* Write MII PHY रेजिस्टर. */
		__sungem_phy_ग_लिखो(gp, data->phy_id & 0x1f, data->reg_num & 0x1f,
			    data->val_in);
		rc = 0;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

#अगर (!defined(CONFIG_SPARC) && !defined(CONFIG_PPC_PMAC))
/* Fetch MAC address from vital product data of PCI ROM. */
अटल पूर्णांक find_eth_addr_in_vpd(व्योम __iomem *rom_base, पूर्णांक len, अचिन्हित अक्षर *dev_addr)
अणु
	पूर्णांक this_offset;

	क्रम (this_offset = 0x20; this_offset < len; this_offset++) अणु
		व्योम __iomem *p = rom_base + this_offset;
		पूर्णांक i;

		अगर (पढ़ोb(p + 0) != 0x90 ||
		    पढ़ोb(p + 1) != 0x00 ||
		    पढ़ोb(p + 2) != 0x09 ||
		    पढ़ोb(p + 3) != 0x4e ||
		    पढ़ोb(p + 4) != 0x41 ||
		    पढ़ोb(p + 5) != 0x06)
			जारी;

		this_offset += 6;
		p += 6;

		क्रम (i = 0; i < 6; i++)
			dev_addr[i] = पढ़ोb(p + i);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम get_gem_mac_nonobp(काष्ठा pci_dev *pdev, अचिन्हित अक्षर *dev_addr)
अणु
	माप_प्रकार size;
	व्योम __iomem *p = pci_map_rom(pdev, &size);

	अगर (p) अणु
		पूर्णांक found;

		found = पढ़ोb(p) == 0x55 &&
			पढ़ोb(p + 1) == 0xaa &&
			find_eth_addr_in_vpd(p, (64 * 1024), dev_addr);
		pci_unmap_rom(pdev, p);
		अगर (found)
			वापस;
	पूर्ण

	/* Sun MAC prefix then 3 अक्रमom bytes. */
	dev_addr[0] = 0x08;
	dev_addr[1] = 0x00;
	dev_addr[2] = 0x20;
	get_अक्रमom_bytes(dev_addr + 3, 3);
पूर्ण
#पूर्ण_अगर /* not Sparc and not PPC */

अटल पूर्णांक gem_get_device_address(काष्ठा gem *gp)
अणु
#अगर defined(CONFIG_SPARC) || defined(CONFIG_PPC_PMAC)
	काष्ठा net_device *dev = gp->dev;
	स्थिर अचिन्हित अक्षर *addr;

	addr = of_get_property(gp->of_node, "local-mac-address", शून्य);
	अगर (addr == शून्य) अणु
#अगर_घोषित CONFIG_SPARC
		addr = idprom->id_ethaddr;
#अन्यथा
		prपूर्णांकk("\n");
		pr_err("%s: can't get mac-address\n", dev->name);
		वापस -1;
#पूर्ण_अगर
	पूर्ण
	स_नकल(dev->dev_addr, addr, ETH_ALEN);
#अन्यथा
	get_gem_mac_nonobp(gp->pdev, gp->dev->dev_addr);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम gem_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		काष्ठा gem *gp = netdev_priv(dev);

		unरेजिस्टर_netdev(dev);

		/* Ensure reset task is truly gone */
		cancel_work_sync(&gp->reset_task);

		/* Free resources */
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा gem_init_block),
				  gp->init_block, gp->gblock_dvma);
		iounmap(gp->regs);
		pci_release_regions(pdev);
		मुक्त_netdev(dev);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops gem_netdev_ops = अणु
	.nकरो_खोलो		= gem_खोलो,
	.nकरो_stop		= gem_बंद,
	.nकरो_start_xmit		= gem_start_xmit,
	.nकरो_get_stats		= gem_get_stats,
	.nकरो_set_rx_mode	= gem_set_multicast,
	.nकरो_करो_ioctl		= gem_ioctl,
	.nकरो_tx_समयout		= gem_tx_समयout,
	.nकरो_change_mtu		= gem_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address    = gem_set_mac_address,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller    = gem_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक gem_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित दीर्घ gemreg_base, gemreg_len;
	काष्ठा net_device *dev;
	काष्ठा gem *gp;
	पूर्णांक err, pci_using_dac;

	prपूर्णांकk_once(KERN_INFO "%s", version);

	/* Apple gmac note: during probe, the chip is घातered up by
	 * the arch code to allow the code below to work (and to let
	 * the chip be probed on the config space. It won't stay घातered
	 * up until the पूर्णांकerface is brought up however, so we can't rely
	 * on रेजिस्टर configuration करोne at this poपूर्णांक.
	 */
	err = pci_enable_device(pdev);
	अगर (err) अणु
		pr_err("Cannot enable MMIO operation, aborting\n");
		वापस err;
	पूर्ण
	pci_set_master(pdev);

	/* Configure DMA attributes. */

	/* All of the GEM करोcumentation states that 64-bit DMA addressing
	 * is fully supported and should work just fine.  However the
	 * front end क्रम RIO based GEMs is dअगरferent and only supports
	 * 32-bit addressing.
	 *
	 * For now we assume the various PPC GEMs are 32-bit only as well.
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_SUN &&
	    pdev->device == PCI_DEVICE_ID_SUN_GEM &&
	    !dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			pr_err("No usable DMA configuration, aborting\n");
			जाओ err_disable_device;
		पूर्ण
		pci_using_dac = 0;
	पूर्ण

	gemreg_base = pci_resource_start(pdev, 0);
	gemreg_len = pci_resource_len(pdev, 0);

	अगर ((pci_resource_flags(pdev, 0) & IORESOURCE_IO) != 0) अणु
		pr_err("Cannot find proper PCI device base address, aborting\n");
		err = -ENODEV;
		जाओ err_disable_device;
	पूर्ण

	dev = alloc_etherdev(माप(*gp));
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_disable_device;
	पूर्ण
	SET_NETDEV_DEV(dev, &pdev->dev);

	gp = netdev_priv(dev);

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		pr_err("Cannot obtain PCI resources, aborting\n");
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	gp->pdev = pdev;
	gp->dev = dev;

	gp->msg_enable = DEFAULT_MSG;

	समयr_setup(&gp->link_समयr, gem_link_समयr, 0);

	INIT_WORK(&gp->reset_task, gem_reset_task);

	gp->lstate = link_करोwn;
	gp->समयr_ticks = 0;
	netअगर_carrier_off(dev);

	gp->regs = ioremap(gemreg_base, gemreg_len);
	अगर (!gp->regs) अणु
		pr_err("Cannot map device registers, aborting\n");
		err = -EIO;
		जाओ err_out_मुक्त_res;
	पूर्ण

	/* On Apple, we want a reference to the Open Firmware device-tree
	 * node. We use it क्रम घड़ी control.
	 */
#अगर defined(CONFIG_PPC_PMAC) || defined(CONFIG_SPARC)
	gp->of_node = pci_device_to_OF_node(pdev);
#पूर्ण_अगर

	/* Only Apple version supports WOL afaik */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_APPLE)
		gp->has_wol = 1;

	/* Make sure cell is enabled */
	gem_get_cell(gp);

	/* Make sure everything is stopped and in init state */
	gem_reset(gp);

	/* Fill up the mii_phy काष्ठाure (even अगर we won't use it) */
	gp->phy_mii.dev = dev;
	gp->phy_mii.mdio_पढ़ो = _sungem_phy_पढ़ो;
	gp->phy_mii.mdio_ग_लिखो = _sungem_phy_ग_लिखो;
#अगर_घोषित CONFIG_PPC_PMAC
	gp->phy_mii.platक्रमm_data = gp->of_node;
#पूर्ण_अगर
	/* By शेष, we start with स्वतःneg */
	gp->want_स्वतःneg = 1;

	/* Check fअगरo sizes, PHY type, etc... */
	अगर (gem_check_invariants(gp)) अणु
		err = -ENODEV;
		जाओ err_out_iounmap;
	पूर्ण

	/* It is guaranteed that the वापसed buffer will be at least
	 * PAGE_SIZE aligned.
	 */
	gp->init_block = dma_alloc_coherent(&pdev->dev, माप(काष्ठा gem_init_block),
					    &gp->gblock_dvma, GFP_KERNEL);
	अगर (!gp->init_block) अणु
		pr_err("Cannot allocate init block, aborting\n");
		err = -ENOMEM;
		जाओ err_out_iounmap;
	पूर्ण

	err = gem_get_device_address(gp);
	अगर (err)
		जाओ err_out_मुक्त_consistent;

	dev->netdev_ops = &gem_netdev_ops;
	netअगर_napi_add(dev, &gp->napi, gem_poll, 64);
	dev->ethtool_ops = &gem_ethtool_ops;
	dev->watchकरोg_समयo = 5 * HZ;
	dev->dma = 0;

	/* Set that now, in हाल PM kicks in now */
	pci_set_drvdata(pdev, dev);

	/* We can करो scatter/gather and HW checksum */
	dev->hw_features = NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_RXCSUM;
	dev->features = dev->hw_features;
	अगर (pci_using_dac)
		dev->features |= NETIF_F_HIGHDMA;

	/* MTU range: 68 - 1500 (Jumbo mode is broken) */
	dev->min_mtu = GEM_MIN_MTU;
	dev->max_mtu = GEM_MAX_MTU;

	/* Register with kernel */
	अगर (रेजिस्टर_netdev(dev)) अणु
		pr_err("Cannot register net device, aborting\n");
		err = -ENOMEM;
		जाओ err_out_मुक्त_consistent;
	पूर्ण

	/* Unकरो the get_cell with appropriate locking (we could use
	 * nकरो_init/uninit but that would be even more clumsy imho)
	 */
	rtnl_lock();
	gem_put_cell(gp);
	rtnl_unlock();

	netdev_info(dev, "Sun GEM (PCI) 10/100/1000BaseT Ethernet %pM\n",
		    dev->dev_addr);
	वापस 0;

err_out_मुक्त_consistent:
	gem_हटाओ_one(pdev);
err_out_iounmap:
	gem_put_cell(gp);
	iounmap(gp->regs);

err_out_मुक्त_res:
	pci_release_regions(pdev);

err_out_मुक्त_netdev:
	मुक्त_netdev(dev);
err_disable_device:
	pci_disable_device(pdev);
	वापस err;

पूर्ण

अटल SIMPLE_DEV_PM_OPS(gem_pm_ops, gem_suspend, gem_resume);

अटल काष्ठा pci_driver gem_driver = अणु
	.name		= GEM_MODULE_NAME,
	.id_table	= gem_pci_tbl,
	.probe		= gem_init_one,
	.हटाओ		= gem_हटाओ_one,
	.driver.pm	= &gem_pm_ops,
पूर्ण;

module_pci_driver(gem_driver);
