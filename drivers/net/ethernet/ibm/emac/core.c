<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/ethernet/ibm/emac/core.c
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller.
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Copyright (c) 2004, 2005 Zultys Technologies.
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *
 * Based on original work by
 * 	Matt Porter <mporter@kernel.crashing.org>
 *	(c) 2003 Benjamin Herrenschmidt <benh@kernel.crashing.org>
 *      Armin Kuster <akuster@mvista.com>
 * 	Johnnie Peters <jpeters@mvista.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/crc32.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/bitops.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/dcr-regs.h>

#समावेश "core.h"

/*
 * Lack of dma_unmap_???? calls is पूर्णांकentional.
 *
 * API-correct usage requires additional support state inक्रमmation to be
 * मुख्यtained क्रम every RX and TX buffer descriptor (BD). Unक्रमtunately, due to
 * EMAC design (e.g. TX buffer passed from network stack can be split पूर्णांकo
 * several BDs, dma_map_single/dma_map_page can be used to map particular BD),
 * मुख्यtaining such inक्रमmation will add additional overhead.
 * Current DMA API implementation क्रम 4xx processors only ensures cache coherency
 * and dma_unmap_???? routines are empty and are likely to stay this way.
 * I decided to omit dma_unmap_??? calls because I करोn't want to add additional
 * complनिकासy just क्रम the sake of following some असलtract API, when it करोesn't
 * add any real benefit to the driver. I understand that this decision maybe
 * controversial, but I really tried to make code API-correct and efficient
 * at the same समय and didn't come up with code I liked :(.                --ebs
 */

#घोषणा DRV_NAME        "emac"
#घोषणा DRV_VERSION     "3.54"
#घोषणा DRV_DESC        "PPC 4xx OCP EMAC driver"

MODULE_DESCRIPTION(DRV_DESC);
MODULE_AUTHOR
    ("Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>");
MODULE_LICENSE("GPL");

/* minimum number of मुक्त TX descriptors required to wake up TX process */
#घोषणा EMAC_TX_WAKEUP_THRESH		(NUM_TX_BUFF / 4)

/* If packet size is less than this number, we allocate small skb and copy packet
 * contents पूर्णांकo it instead of just sending original big skb up
 */
#घोषणा EMAC_RX_COPY_THRESH		CONFIG_IBM_EMAC_RX_COPY_THRESHOLD

/* Since multiple EMACs share MDIO lines in various ways, we need
 * to aव्योम re-using the same PHY ID in हालs where the arch didn't
 * setup precise phy_map entries
 *
 * XXX This is something that needs to be reworked as we can have multiple
 * EMAC "sets" (multiple ASICs containing several EMACs) though we can
 * probably require in that हाल to have explicit PHY IDs in the device-tree
 */
अटल u32 busy_phy_map;
अटल DEFINE_MUTEX(emac_phy_map_lock);

/* This is the रुको queue used to रुको on any event related to probe, that
 * is discovery of MALs, other EMACs, ZMII/RGMIIs, etc...
 */
अटल DECLARE_WAIT_QUEUE_HEAD(emac_probe_रुको);

/* Having stable पूर्णांकerface names is a करोomed idea. However, it would be nice
 * अगर we didn't have completely random interface names at boot too :-) It's
 * just a matter of making everybody's lअगरe easier. Since we are करोing
 * thपढ़ोed probing, it's a bit harder though. The base idea here is that
 * we make up a list of all emacs in the device-tree beक्रमe we रेजिस्टर the
 * driver. Every emac will then रुको क्रम the previous one in the list to
 * initialize beक्रमe itself. We should also keep that list ordered by
 * cell_index.
 * That list is only 4 entries दीर्घ, meaning that additional EMACs करोn't
 * get ordering guarantees unless EMAC_BOOT_LIST_SIZE is increased.
 */

#घोषणा EMAC_BOOT_LIST_SIZE	4
अटल काष्ठा device_node *emac_boot_list[EMAC_BOOT_LIST_SIZE];

/* How दीर्घ should I रुको क्रम dependent devices ? */
#घोषणा EMAC_PROBE_DEP_TIMEOUT	(HZ * 5)

/* I करोn't want to litter प्रणाली log with समयout errors
 * when we have brain-damaged PHY.
 */
अटल अंतरभूत व्योम emac_report_समयout_error(काष्ठा emac_instance *dev,
					     स्थिर अक्षर *error)
अणु
	अगर (emac_has_feature(dev, EMAC_FTR_440GX_PHY_CLK_FIX |
				  EMAC_FTR_460EX_PHY_CLK_FIX |
				  EMAC_FTR_440EP_PHY_CLK_FIX))
		DBG(dev, "%s" NL, error);
	अन्यथा अगर (net_ratelimit())
		prपूर्णांकk(KERN_ERR "%pOF: %s\n", dev->ofdev->dev.of_node, error);
पूर्ण

/* EMAC PHY घड़ी workaround:
 * 440EP/440GR has more sane SDR0_MFR रेजिस्टर implementation than 440GX,
 * which allows controlling each EMAC घड़ी
 */
अटल अंतरभूत व्योम emac_rx_clk_tx(काष्ठा emac_instance *dev)
अणु
#अगर_घोषित CONFIG_PPC_DCR_NATIVE
	अगर (emac_has_feature(dev, EMAC_FTR_440EP_PHY_CLK_FIX))
		dcri_clrset(SDR0, SDR0_MFR,
			    0, SDR0_MFR_ECS >> dev->cell_index);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम emac_rx_clk_शेष(काष्ठा emac_instance *dev)
अणु
#अगर_घोषित CONFIG_PPC_DCR_NATIVE
	अगर (emac_has_feature(dev, EMAC_FTR_440EP_PHY_CLK_FIX))
		dcri_clrset(SDR0, SDR0_MFR,
			    SDR0_MFR_ECS >> dev->cell_index, 0);
#पूर्ण_अगर
पूर्ण

/* PHY polling पूर्णांकervals */
#घोषणा PHY_POLL_LINK_ON	HZ
#घोषणा PHY_POLL_LINK_OFF	(HZ / 5)

/* Graceful stop समयouts in us.
 * We should allow up to 1 frame समय (full-duplex, ignoring collisions)
 */
#घोषणा STOP_TIMEOUT_10		1230
#घोषणा STOP_TIMEOUT_100	124
#घोषणा STOP_TIMEOUT_1000	13
#घोषणा STOP_TIMEOUT_1000_JUMBO	73

अटल अचिन्हित अक्षर शेष_mcast_addr[] = अणु
	0x01, 0x80, 0xC2, 0x00, 0x00, 0x01
पूर्ण;

/* Please, keep in sync with काष्ठा ibm_emac_stats/ibm_emac_error_stats */
अटल स्थिर अक्षर emac_stats_keys[EMAC_ETHTOOL_STATS_COUNT][ETH_GSTRING_LEN] = अणु
	"rx_packets", "rx_bytes", "tx_packets", "tx_bytes", "rx_packets_csum",
	"tx_packets_csum", "tx_undo", "rx_dropped_stack", "rx_dropped_oom",
	"rx_dropped_error", "rx_dropped_resize", "rx_dropped_mtu",
	"rx_stopped", "rx_bd_errors", "rx_bd_overrun", "rx_bd_bad_packet",
	"rx_bd_runt_packet", "rx_bd_short_event", "rx_bd_alignment_error",
	"rx_bd_bad_fcs", "rx_bd_packet_too_long", "rx_bd_out_of_range",
	"rx_bd_in_range", "rx_parity", "rx_fifo_overrun", "rx_overrun",
	"rx_bad_packet", "rx_runt_packet", "rx_short_event",
	"rx_alignment_error", "rx_bad_fcs", "rx_packet_too_long",
	"rx_out_of_range", "rx_in_range", "tx_dropped", "tx_bd_errors",
	"tx_bd_bad_fcs", "tx_bd_carrier_loss", "tx_bd_excessive_deferral",
	"tx_bd_excessive_collisions", "tx_bd_late_collision",
	"tx_bd_multple_collisions", "tx_bd_single_collision",
	"tx_bd_underrun", "tx_bd_sqe", "tx_parity", "tx_underrun", "tx_sqe",
	"tx_errors"
पूर्ण;

अटल irqवापस_t emac_irq(पूर्णांक irq, व्योम *dev_instance);
अटल व्योम emac_clean_tx_ring(काष्ठा emac_instance *dev);
अटल व्योम __emac_set_multicast_list(काष्ठा emac_instance *dev);

अटल अंतरभूत पूर्णांक emac_phy_supports_gige(पूर्णांक phy_mode)
अणु
	वापस  phy_पूर्णांकerface_mode_is_rgmii(phy_mode) ||
		phy_mode == PHY_INTERFACE_MODE_GMII ||
		phy_mode == PHY_INTERFACE_MODE_SGMII ||
		phy_mode == PHY_INTERFACE_MODE_TBI ||
		phy_mode == PHY_INTERFACE_MODE_RTBI;
पूर्ण

अटल अंतरभूत पूर्णांक emac_phy_gpcs(पूर्णांक phy_mode)
अणु
	वापस  phy_mode == PHY_INTERFACE_MODE_SGMII ||
		phy_mode == PHY_INTERFACE_MODE_TBI ||
		phy_mode == PHY_INTERFACE_MODE_RTBI;
पूर्ण

अटल अंतरभूत व्योम emac_tx_enable(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	u32 r;

	DBG(dev, "tx_enable" NL);

	r = in_be32(&p->mr0);
	अगर (!(r & EMAC_MR0_TXE))
		out_be32(&p->mr0, r | EMAC_MR0_TXE);
पूर्ण

अटल व्योम emac_tx_disable(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	u32 r;

	DBG(dev, "tx_disable" NL);

	r = in_be32(&p->mr0);
	अगर (r & EMAC_MR0_TXE) अणु
		पूर्णांक n = dev->stop_समयout;
		out_be32(&p->mr0, r & ~EMAC_MR0_TXE);
		जबतक (!(in_be32(&p->mr0) & EMAC_MR0_TXI) && n) अणु
			udelay(1);
			--n;
		पूर्ण
		अगर (unlikely(!n))
			emac_report_समयout_error(dev, "TX disable timeout");
	पूर्ण
पूर्ण

अटल व्योम emac_rx_enable(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	u32 r;

	अगर (unlikely(test_bit(MAL_COMMAC_RX_STOPPED, &dev->commac.flags)))
		जाओ out;

	DBG(dev, "rx_enable" NL);

	r = in_be32(&p->mr0);
	अगर (!(r & EMAC_MR0_RXE)) अणु
		अगर (unlikely(!(r & EMAC_MR0_RXI))) अणु
			/* Wait अगर previous async disable is still in progress */
			पूर्णांक n = dev->stop_समयout;
			जबतक (!(r = in_be32(&p->mr0) & EMAC_MR0_RXI) && n) अणु
				udelay(1);
				--n;
			पूर्ण
			अगर (unlikely(!n))
				emac_report_समयout_error(dev,
							  "RX disable timeout");
		पूर्ण
		out_be32(&p->mr0, r | EMAC_MR0_RXE);
	पूर्ण
 out:
	;
पूर्ण

अटल व्योम emac_rx_disable(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	u32 r;

	DBG(dev, "rx_disable" NL);

	r = in_be32(&p->mr0);
	अगर (r & EMAC_MR0_RXE) अणु
		पूर्णांक n = dev->stop_समयout;
		out_be32(&p->mr0, r & ~EMAC_MR0_RXE);
		जबतक (!(in_be32(&p->mr0) & EMAC_MR0_RXI) && n) अणु
			udelay(1);
			--n;
		पूर्ण
		अगर (unlikely(!n))
			emac_report_समयout_error(dev, "RX disable timeout");
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम emac_netअगर_stop(काष्ठा emac_instance *dev)
अणु
	netअगर_tx_lock_bh(dev->ndev);
	netअगर_addr_lock(dev->ndev);
	dev->no_mcast = 1;
	netअगर_addr_unlock(dev->ndev);
	netअगर_tx_unlock_bh(dev->ndev);
	netअगर_trans_update(dev->ndev);	/* prevent tx समयout */
	mal_poll_disable(dev->mal, &dev->commac);
	netअगर_tx_disable(dev->ndev);
पूर्ण

अटल अंतरभूत व्योम emac_netअगर_start(काष्ठा emac_instance *dev)
अणु
	netअगर_tx_lock_bh(dev->ndev);
	netअगर_addr_lock(dev->ndev);
	dev->no_mcast = 0;
	अगर (dev->mcast_pending && netअगर_running(dev->ndev))
		__emac_set_multicast_list(dev);
	netअगर_addr_unlock(dev->ndev);
	netअगर_tx_unlock_bh(dev->ndev);

	netअगर_wake_queue(dev->ndev);

	/* NOTE: unconditional netअगर_wake_queue is only appropriate
	 * so दीर्घ as all callers are assured to have मुक्त tx slots
	 * (taken from tg3... though the हाल where that is wrong is
	 *  not terribly harmful)
	 */
	mal_poll_enable(dev->mal, &dev->commac);
पूर्ण

अटल अंतरभूत व्योम emac_rx_disable_async(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	u32 r;

	DBG(dev, "rx_disable_async" NL);

	r = in_be32(&p->mr0);
	अगर (r & EMAC_MR0_RXE)
		out_be32(&p->mr0, r & ~EMAC_MR0_RXE);
पूर्ण

अटल पूर्णांक emac_reset(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	पूर्णांक n = 20;
	bool __maybe_unused try_पूर्णांकernal_घड़ी = false;

	DBG(dev, "reset" NL);

	अगर (!dev->reset_failed) अणु
		/* 40x erratum suggests stopping RX channel beक्रमe reset,
		 * we stop TX as well
		 */
		emac_rx_disable(dev);
		emac_tx_disable(dev);
	पूर्ण

#अगर_घोषित CONFIG_PPC_DCR_NATIVE
करो_retry:
	/*
	 * PPC460EX/GT Embedded Processor Advanced User's Manual
	 * section 28.10.1 Mode Register 0 (EMACx_MR0) states:
	 * Note: The PHY must provide a TX Clk in order to perक्रमm a soft reset
	 * of the EMAC. If none is present, select the पूर्णांकernal घड़ी
	 * (SDR0_ETH_CFG[EMACx_PHY_CLK] = 1).
	 * After a soft reset, select the बाह्यal घड़ी.
	 *
	 * The AR8035-A PHY Meraki MR24 करोes not provide a TX Clk अगर the
	 * ethernet cable is not attached. This causes the reset to समयout
	 * and the PHY detection code in emac_init_phy() is unable to
	 * communicate and detect the AR8035-A PHY. As a result, the emac
	 * driver bails out early and the user has no ethernet.
	 * In order to stay compatible with existing configurations, the
	 * driver will temporarily चयन to the पूर्णांकernal घड़ी, after
	 * the first reset fails.
	 */
	अगर (emac_has_feature(dev, EMAC_FTR_460EX_PHY_CLK_FIX)) अणु
		अगर (try_पूर्णांकernal_घड़ी || (dev->phy_address == 0xffffffff &&
					   dev->phy_map == 0xffffffff)) अणु
			/* No PHY: select पूर्णांकernal loop घड़ी beक्रमe reset */
			dcri_clrset(SDR0, SDR0_ETH_CFG,
				    0, SDR0_ETH_CFG_ECS << dev->cell_index);
		पूर्ण अन्यथा अणु
			/* PHY present: select बाह्यal घड़ी beक्रमe reset */
			dcri_clrset(SDR0, SDR0_ETH_CFG,
				    SDR0_ETH_CFG_ECS << dev->cell_index, 0);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	out_be32(&p->mr0, EMAC_MR0_SRST);
	जबतक ((in_be32(&p->mr0) & EMAC_MR0_SRST) && n)
		--n;

#अगर_घोषित CONFIG_PPC_DCR_NATIVE
	अगर (emac_has_feature(dev, EMAC_FTR_460EX_PHY_CLK_FIX)) अणु
		अगर (!n && !try_पूर्णांकernal_घड़ी) अणु
			/* first attempt has समयd out. */
			n = 20;
			try_पूर्णांकernal_घड़ी = true;
			जाओ करो_retry;
		पूर्ण

		अगर (try_पूर्णांकernal_घड़ी || (dev->phy_address == 0xffffffff &&
					   dev->phy_map == 0xffffffff)) अणु
			/* No PHY: restore बाह्यal घड़ी source after reset */
			dcri_clrset(SDR0, SDR0_ETH_CFG,
				    SDR0_ETH_CFG_ECS << dev->cell_index, 0);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (n) अणु
		dev->reset_failed = 0;
		वापस 0;
	पूर्ण अन्यथा अणु
		emac_report_समयout_error(dev, "reset timeout");
		dev->reset_failed = 1;
		वापस -ETIMEDOUT;
	पूर्ण
पूर्ण

अटल व्योम emac_hash_mc(काष्ठा emac_instance *dev)
अणु
	स्थिर पूर्णांक regs = EMAC_XAHT_REGS(dev);
	u32 *gaht_base = emac_gaht_base(dev);
	u32 gaht_temp[EMAC_XAHT_MAX_REGS];
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;

	DBG(dev, "hash_mc %d" NL, netdev_mc_count(dev->ndev));

	स_रखो(gaht_temp, 0, माप (gaht_temp));

	netdev_क्रम_each_mc_addr(ha, dev->ndev) अणु
		पूर्णांक slot, reg, mask;
		DBG2(dev, "mc %pM" NL, ha->addr);

		slot = EMAC_XAHT_CRC_TO_SLOT(dev,
					     ether_crc(ETH_ALEN, ha->addr));
		reg = EMAC_XAHT_SLOT_TO_REG(dev, slot);
		mask = EMAC_XAHT_SLOT_TO_MASK(dev, slot);

		gaht_temp[reg] |= mask;
	पूर्ण

	क्रम (i = 0; i < regs; i++)
		out_be32(gaht_base + i, gaht_temp[i]);
पूर्ण

अटल अंतरभूत u32 emac_अगरf2rmr(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	u32 r;

	r = EMAC_RMR_SP | EMAC_RMR_SFCS | EMAC_RMR_IAE | EMAC_RMR_BAE;

	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4))
	    r |= EMAC4_RMR_BASE;
	अन्यथा
	    r |= EMAC_RMR_BASE;

	अगर (ndev->flags & IFF_PROMISC)
		r |= EMAC_RMR_PME;
	अन्यथा अगर (ndev->flags & IFF_ALLMULTI ||
			 (netdev_mc_count(ndev) > EMAC_XAHT_SLOTS(dev)))
		r |= EMAC_RMR_PMME;
	अन्यथा अगर (!netdev_mc_empty(ndev))
		r |= EMAC_RMR_MAE;

	अगर (emac_has_feature(dev, EMAC_APM821XX_REQ_JUMBO_FRAME_SIZE)) अणु
		r &= ~EMAC4_RMR_MJS_MASK;
		r |= EMAC4_RMR_MJS(ndev->mtu);
	पूर्ण

	वापस r;
पूर्ण

अटल u32 __emac_calc_base_mr1(काष्ठा emac_instance *dev, पूर्णांक tx_size, पूर्णांक rx_size)
अणु
	u32 ret = EMAC_MR1_VLE | EMAC_MR1_IST | EMAC_MR1_TR0_MULT;

	DBG2(dev, "__emac_calc_base_mr1" NL);

	चयन(tx_size) अणु
	हाल 2048:
		ret |= EMAC_MR1_TFS_2K;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: Unknown Tx FIFO size %d\n",
		       dev->ndev->name, tx_size);
	पूर्ण

	चयन(rx_size) अणु
	हाल 16384:
		ret |= EMAC_MR1_RFS_16K;
		अवरोध;
	हाल 4096:
		ret |= EMAC_MR1_RFS_4K;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: Unknown Rx FIFO size %d\n",
		       dev->ndev->name, rx_size);
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 __emac4_calc_base_mr1(काष्ठा emac_instance *dev, पूर्णांक tx_size, पूर्णांक rx_size)
अणु
	u32 ret = EMAC_MR1_VLE | EMAC_MR1_IST | EMAC4_MR1_TR |
		EMAC4_MR1_OBCI(dev->opb_bus_freq / 1000000);

	DBG2(dev, "__emac4_calc_base_mr1" NL);

	चयन(tx_size) अणु
	हाल 16384:
		ret |= EMAC4_MR1_TFS_16K;
		अवरोध;
	हाल 8192:
		ret |= EMAC4_MR1_TFS_8K;
		अवरोध;
	हाल 4096:
		ret |= EMAC4_MR1_TFS_4K;
		अवरोध;
	हाल 2048:
		ret |= EMAC4_MR1_TFS_2K;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: Unknown Tx FIFO size %d\n",
		       dev->ndev->name, tx_size);
	पूर्ण

	चयन(rx_size) अणु
	हाल 16384:
		ret |= EMAC4_MR1_RFS_16K;
		अवरोध;
	हाल 8192:
		ret |= EMAC4_MR1_RFS_8K;
		अवरोध;
	हाल 4096:
		ret |= EMAC4_MR1_RFS_4K;
		अवरोध;
	हाल 2048:
		ret |= EMAC4_MR1_RFS_2K;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "%s: Unknown Rx FIFO size %d\n",
		       dev->ndev->name, rx_size);
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 emac_calc_base_mr1(काष्ठा emac_instance *dev, पूर्णांक tx_size, पूर्णांक rx_size)
अणु
	वापस emac_has_feature(dev, EMAC_FTR_EMAC4) ?
		__emac4_calc_base_mr1(dev, tx_size, rx_size) :
		__emac_calc_base_mr1(dev, tx_size, rx_size);
पूर्ण

अटल अंतरभूत u32 emac_calc_trtr(काष्ठा emac_instance *dev, अचिन्हित पूर्णांक size)
अणु
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4))
		वापस ((size >> 6) - 1) << EMAC_TRTR_SHIFT_EMAC4;
	अन्यथा
		वापस ((size >> 6) - 1) << EMAC_TRTR_SHIFT;
पूर्ण

अटल अंतरभूत u32 emac_calc_rwmr(काष्ठा emac_instance *dev,
				 अचिन्हित पूर्णांक low, अचिन्हित पूर्णांक high)
अणु
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4))
		वापस (low << 22) | ( (high & 0x3ff) << 6);
	अन्यथा
		वापस (low << 23) | ( (high & 0x1ff) << 7);
पूर्ण

अटल पूर्णांक emac_configure(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	काष्ठा net_device *ndev = dev->ndev;
	पूर्णांक tx_size, rx_size, link = netअगर_carrier_ok(dev->ndev);
	u32 r, mr1 = 0;

	DBG(dev, "configure" NL);

	अगर (!link) अणु
		out_be32(&p->mr1, in_be32(&p->mr1)
			 | EMAC_MR1_FDE | EMAC_MR1_ILE);
		udelay(100);
	पूर्ण अन्यथा अगर (emac_reset(dev) < 0)
		वापस -ETIMEDOUT;

	अगर (emac_has_feature(dev, EMAC_FTR_HAS_TAH))
		tah_reset(dev->tah_dev);

	DBG(dev, " link = %d duplex = %d, pause = %d, asym_pause = %d\n",
	    link, dev->phy.duplex, dev->phy.छोड़ो, dev->phy.asym_छोड़ो);

	/* Default fअगरo sizes */
	tx_size = dev->tx_fअगरo_size;
	rx_size = dev->rx_fअगरo_size;

	/* No link, क्रमce loopback */
	अगर (!link)
		mr1 = EMAC_MR1_FDE | EMAC_MR1_ILE;

	/* Check क्रम full duplex */
	अन्यथा अगर (dev->phy.duplex == DUPLEX_FULL)
		mr1 |= EMAC_MR1_FDE | EMAC_MR1_MWSW_001;

	/* Adjust fअगरo sizes, mr1 and समयouts based on link speed */
	dev->stop_समयout = STOP_TIMEOUT_10;
	चयन (dev->phy.speed) अणु
	हाल SPEED_1000:
		अगर (emac_phy_gpcs(dev->phy.mode)) अणु
			mr1 |= EMAC_MR1_MF_1000GPCS | EMAC_MR1_MF_IPPA(
				(dev->phy.gpcs_address != 0xffffffff) ?
				 dev->phy.gpcs_address : dev->phy.address);

			/* Put some arbitrary OUI, Manuf & Rev IDs so we can
			 * identअगरy this GPCS PHY later.
			 */
			out_be32(&p->u1.emac4.ipcr, 0xdeadbeef);
		पूर्ण अन्यथा
			mr1 |= EMAC_MR1_MF_1000;

		/* Extended fअगरo sizes */
		tx_size = dev->tx_fअगरo_size_gige;
		rx_size = dev->rx_fअगरo_size_gige;

		अगर (dev->ndev->mtu > ETH_DATA_LEN) अणु
			अगर (emac_has_feature(dev, EMAC_FTR_EMAC4))
				mr1 |= EMAC4_MR1_JPSM;
			अन्यथा
				mr1 |= EMAC_MR1_JPSM;
			dev->stop_समयout = STOP_TIMEOUT_1000_JUMBO;
		पूर्ण अन्यथा
			dev->stop_समयout = STOP_TIMEOUT_1000;
		अवरोध;
	हाल SPEED_100:
		mr1 |= EMAC_MR1_MF_100;
		dev->stop_समयout = STOP_TIMEOUT_100;
		अवरोध;
	शेष: /* make gcc happy */
		अवरोध;
	पूर्ण

	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII))
		rgmii_set_speed(dev->rgmii_dev, dev->rgmii_port,
				dev->phy.speed);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII))
		zmii_set_speed(dev->zmii_dev, dev->zmii_port, dev->phy.speed);

	/* on 40x erratum क्रमces us to NOT use पूर्णांकegrated flow control,
	 * let's hope it works on 44x ;)
	 */
	अगर (!emac_has_feature(dev, EMAC_FTR_NO_FLOW_CONTROL_40x) &&
	    dev->phy.duplex == DUPLEX_FULL) अणु
		अगर (dev->phy.छोड़ो)
			mr1 |= EMAC_MR1_EIFC | EMAC_MR1_APP;
		अन्यथा अगर (dev->phy.asym_छोड़ो)
			mr1 |= EMAC_MR1_APP;
	पूर्ण

	/* Add base settings & fअगरo sizes & program MR1 */
	mr1 |= emac_calc_base_mr1(dev, tx_size, rx_size);
	out_be32(&p->mr1, mr1);

	/* Set inभागidual MAC address */
	out_be32(&p->iahr, (ndev->dev_addr[0] << 8) | ndev->dev_addr[1]);
	out_be32(&p->ialr, (ndev->dev_addr[2] << 24) |
		 (ndev->dev_addr[3] << 16) | (ndev->dev_addr[4] << 8) |
		 ndev->dev_addr[5]);

	/* VLAN Tag Protocol ID */
	out_be32(&p->vtpid, 0x8100);

	/* Receive mode रेजिस्टर */
	r = emac_अगरf2rmr(ndev);
	अगर (r & EMAC_RMR_MAE)
		emac_hash_mc(dev);
	out_be32(&p->rmr, r);

	/* FIFOs thresholds */
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4))
		r = EMAC4_TMR1((dev->mal_burst_size / dev->fअगरo_entry_size) + 1,
			       tx_size / 2 / dev->fअगरo_entry_size);
	अन्यथा
		r = EMAC_TMR1((dev->mal_burst_size / dev->fअगरo_entry_size) + 1,
			      tx_size / 2 / dev->fअगरo_entry_size);
	out_be32(&p->पंचांगr1, r);
	out_be32(&p->trtr, emac_calc_trtr(dev, tx_size / 2));

	/* PAUSE frame is sent when RX FIFO reaches its high-water mark,
	   there should be still enough space in FIFO to allow the our link
	   partner समय to process this frame and also समय to send PAUSE
	   frame itself.

	   Here is the worst हाल scenario क्रम the RX FIFO "headroom"
	   (from "The Switch Book") (100Mbps, without preamble, पूर्णांकer-frame gap):

	   1) One maximum-length frame on TX                    1522 bytes
	   2) One PAUSE frame समय                                64 bytes
	   3) PAUSE frame decode समय allowance                   64 bytes
	   4) One maximum-length frame on RX                    1522 bytes
	   5) Round-trip propagation delay of the link (100Mb)    15 bytes
	   ----------
	   3187 bytes

	   I chose to set high-water mark to RX_FIFO_SIZE / 4 (1024 bytes)
	   low-water mark  to RX_FIFO_SIZE / 8 (512 bytes)
	 */
	r = emac_calc_rwmr(dev, rx_size / 8 / dev->fअगरo_entry_size,
			   rx_size / 4 / dev->fअगरo_entry_size);
	out_be32(&p->rwmr, r);

	/* Set PAUSE समयr to the maximum */
	out_be32(&p->ptr, 0xffff);

	/* IRQ sources */
	r = EMAC_ISR_OVR | EMAC_ISR_BP | EMAC_ISR_SE |
		EMAC_ISR_ALE | EMAC_ISR_BFCS | EMAC_ISR_PTLE | EMAC_ISR_ORE |
		EMAC_ISR_IRE | EMAC_ISR_TE;
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4))
	    r |= EMAC4_ISR_TXPE | EMAC4_ISR_RXPE /* | EMAC4_ISR_TXUE |
						  EMAC4_ISR_RXOE | */;
	out_be32(&p->iser,  r);

	/* We need to take GPCS PHY out of isolate mode after EMAC reset */
	अगर (emac_phy_gpcs(dev->phy.mode)) अणु
		अगर (dev->phy.gpcs_address != 0xffffffff)
			emac_mii_reset_gpcs(&dev->phy);
		अन्यथा
			emac_mii_reset_phy(&dev->phy);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम emac_reinitialize(काष्ठा emac_instance *dev)
अणु
	DBG(dev, "reinitialize" NL);

	emac_netअगर_stop(dev);
	अगर (!emac_configure(dev)) अणु
		emac_tx_enable(dev);
		emac_rx_enable(dev);
	पूर्ण
	emac_netअगर_start(dev);
पूर्ण

अटल व्योम emac_full_tx_reset(काष्ठा emac_instance *dev)
अणु
	DBG(dev, "full_tx_reset" NL);

	emac_tx_disable(dev);
	mal_disable_tx_channel(dev->mal, dev->mal_tx_chan);
	emac_clean_tx_ring(dev);
	dev->tx_cnt = dev->tx_slot = dev->ack_slot = 0;

	emac_configure(dev);

	mal_enable_tx_channel(dev->mal, dev->mal_tx_chan);
	emac_tx_enable(dev);
	emac_rx_enable(dev);
पूर्ण

अटल व्योम emac_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा emac_instance *dev = container_of(work, काष्ठा emac_instance, reset_work);

	DBG(dev, "reset_work" NL);

	mutex_lock(&dev->link_lock);
	अगर (dev->खोलोed) अणु
		emac_netअगर_stop(dev);
		emac_full_tx_reset(dev);
		emac_netअगर_start(dev);
	पूर्ण
	mutex_unlock(&dev->link_lock);
पूर्ण

अटल व्योम emac_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	DBG(dev, "tx_timeout" NL);

	schedule_work(&dev->reset_work);
पूर्ण


अटल अंतरभूत पूर्णांक emac_phy_करोne(काष्ठा emac_instance *dev, u32 stacr)
अणु
	पूर्णांक करोne = !!(stacr & EMAC_STACR_OC);

	अगर (emac_has_feature(dev, EMAC_FTR_STACR_OC_INVERT))
		करोne = !करोne;

	वापस करोne;
पूर्ण;

अटल पूर्णांक __emac_mdio_पढ़ो(काष्ठा emac_instance *dev, u8 id, u8 reg)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	u32 r = 0;
	पूर्णांक n, err = -ETIMEDOUT;

	mutex_lock(&dev->mdio_lock);

	DBG2(dev, "mdio_read(%02x,%02x)" NL, id, reg);

	/* Enable proper MDIO port */
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII))
		zmii_get_mdio(dev->zmii_dev, dev->zmii_port);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII))
		rgmii_get_mdio(dev->rgmii_dev, dev->rgmii_port);

	/* Wait क्रम management पूर्णांकerface to become idle */
	n = 20;
	जबतक (!emac_phy_करोne(dev, in_be32(&p->stacr))) अणु
		udelay(1);
		अगर (!--n) अणु
			DBG2(dev, " -> timeout wait idle\n");
			जाओ bail;
		पूर्ण
	पूर्ण

	/* Issue पढ़ो command */
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4))
		r = EMAC4_STACR_BASE(dev->opb_bus_freq);
	अन्यथा
		r = EMAC_STACR_BASE(dev->opb_bus_freq);
	अगर (emac_has_feature(dev, EMAC_FTR_STACR_OC_INVERT))
		r |= EMAC_STACR_OC;
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_NEW_STACR))
		r |= EMACX_STACR_STAC_READ;
	अन्यथा
		r |= EMAC_STACR_STAC_READ;
	r |= (reg & EMAC_STACR_PRA_MASK)
		| ((id & EMAC_STACR_PCDA_MASK) << EMAC_STACR_PCDA_SHIFT);
	out_be32(&p->stacr, r);

	/* Wait क्रम पढ़ो to complete */
	n = 200;
	जबतक (!emac_phy_करोne(dev, (r = in_be32(&p->stacr)))) अणु
		udelay(1);
		अगर (!--n) अणु
			DBG2(dev, " -> timeout wait complete\n");
			जाओ bail;
		पूर्ण
	पूर्ण

	अगर (unlikely(r & EMAC_STACR_PHYE)) अणु
		DBG(dev, "mdio_read(%02x, %02x) failed" NL, id, reg);
		err = -EREMOTEIO;
		जाओ bail;
	पूर्ण

	r = ((r >> EMAC_STACR_PHYD_SHIFT) & EMAC_STACR_PHYD_MASK);

	DBG2(dev, "mdio_read -> %04x" NL, r);
	err = 0;
 bail:
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII))
		rgmii_put_mdio(dev->rgmii_dev, dev->rgmii_port);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII))
		zmii_put_mdio(dev->zmii_dev, dev->zmii_port);
	mutex_unlock(&dev->mdio_lock);

	वापस err == 0 ? r : err;
पूर्ण

अटल व्योम __emac_mdio_ग_लिखो(काष्ठा emac_instance *dev, u8 id, u8 reg,
			      u16 val)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	u32 r = 0;
	पूर्णांक n;

	mutex_lock(&dev->mdio_lock);

	DBG2(dev, "mdio_write(%02x,%02x,%04x)" NL, id, reg, val);

	/* Enable proper MDIO port */
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII))
		zmii_get_mdio(dev->zmii_dev, dev->zmii_port);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII))
		rgmii_get_mdio(dev->rgmii_dev, dev->rgmii_port);

	/* Wait क्रम management पूर्णांकerface to be idle */
	n = 20;
	जबतक (!emac_phy_करोne(dev, in_be32(&p->stacr))) अणु
		udelay(1);
		अगर (!--n) अणु
			DBG2(dev, " -> timeout wait idle\n");
			जाओ bail;
		पूर्ण
	पूर्ण

	/* Issue ग_लिखो command */
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4))
		r = EMAC4_STACR_BASE(dev->opb_bus_freq);
	अन्यथा
		r = EMAC_STACR_BASE(dev->opb_bus_freq);
	अगर (emac_has_feature(dev, EMAC_FTR_STACR_OC_INVERT))
		r |= EMAC_STACR_OC;
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_NEW_STACR))
		r |= EMACX_STACR_STAC_WRITE;
	अन्यथा
		r |= EMAC_STACR_STAC_WRITE;
	r |= (reg & EMAC_STACR_PRA_MASK) |
		((id & EMAC_STACR_PCDA_MASK) << EMAC_STACR_PCDA_SHIFT) |
		(val << EMAC_STACR_PHYD_SHIFT);
	out_be32(&p->stacr, r);

	/* Wait क्रम ग_लिखो to complete */
	n = 200;
	जबतक (!emac_phy_करोne(dev, in_be32(&p->stacr))) अणु
		udelay(1);
		अगर (!--n) अणु
			DBG2(dev, " -> timeout wait complete\n");
			जाओ bail;
		पूर्ण
	पूर्ण
 bail:
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII))
		rgmii_put_mdio(dev->rgmii_dev, dev->rgmii_port);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII))
		zmii_put_mdio(dev->zmii_dev, dev->zmii_port);
	mutex_unlock(&dev->mdio_lock);
पूर्ण

अटल पूर्णांक emac_mdio_पढ़ो(काष्ठा net_device *ndev, पूर्णांक id, पूर्णांक reg)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	पूर्णांक res;

	res = __emac_mdio_पढ़ो((dev->mdio_instance &&
				dev->phy.gpcs_address != id) ?
				dev->mdio_instance : dev,
			       (u8) id, (u8) reg);
	वापस res;
पूर्ण

अटल व्योम emac_mdio_ग_लिखो(काष्ठा net_device *ndev, पूर्णांक id, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	__emac_mdio_ग_लिखो((dev->mdio_instance &&
			   dev->phy.gpcs_address != id) ?
			   dev->mdio_instance : dev,
			  (u8) id, (u8) reg, (u16) val);
पूर्ण

/* Tx lock BH */
अटल व्योम __emac_set_multicast_list(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	u32 rmr = emac_अगरf2rmr(dev->ndev);

	DBG(dev, "__multicast %08x" NL, rmr);

	/* I decided to relax रेजिस्टर access rules here to aव्योम
	 * full EMAC reset.
	 *
	 * There is a real problem with EMAC4 core अगर we use MWSW_001 bit
	 * in MR1 रेजिस्टर and करो a full EMAC reset.
	 * One TX BD status update is delayed and, after EMAC reset, it
	 * never happens, resulting in TX hung (it'll be recovered by TX
	 * समयout handler eventually, but this is just gross).
	 * So we either have to करो full TX reset or try to cheat here :)
	 *
	 * The only required change is to RX mode रेजिस्टर, so I *think* all
	 * we need is just to stop RX channel. This seems to work on all
	 * tested SoCs.                                                --ebs
	 *
	 * If we need the full reset, we might just trigger the workqueue
	 * and करो it async... a bit nasty but should work --BenH
	 */
	dev->mcast_pending = 0;
	emac_rx_disable(dev);
	अगर (rmr & EMAC_RMR_MAE)
		emac_hash_mc(dev);
	out_be32(&p->rmr, rmr);
	emac_rx_enable(dev);
पूर्ण

/* Tx lock BH */
अटल व्योम emac_set_multicast_list(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	DBG(dev, "multicast" NL);

	BUG_ON(!netअगर_running(dev->ndev));

	अगर (dev->no_mcast) अणु
		dev->mcast_pending = 1;
		वापस;
	पूर्ण

	mutex_lock(&dev->link_lock);
	__emac_set_multicast_list(dev);
	mutex_unlock(&dev->link_lock);
पूर्ण

अटल पूर्णांक emac_set_mac_address(काष्ठा net_device *ndev, व्योम *sa)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	काष्ठा sockaddr *addr = sa;
	काष्ठा emac_regs __iomem *p = dev->emacp;

	अगर (!is_valid_ether_addr(addr->sa_data))
	       वापस -EADDRNOTAVAIL;

	mutex_lock(&dev->link_lock);

	स_नकल(ndev->dev_addr, addr->sa_data, ndev->addr_len);

	emac_rx_disable(dev);
	emac_tx_disable(dev);
	out_be32(&p->iahr, (ndev->dev_addr[0] << 8) | ndev->dev_addr[1]);
	out_be32(&p->ialr, (ndev->dev_addr[2] << 24) |
		(ndev->dev_addr[3] << 16) | (ndev->dev_addr[4] << 8) |
		ndev->dev_addr[5]);
	emac_tx_enable(dev);
	emac_rx_enable(dev);

	mutex_unlock(&dev->link_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक emac_resize_rx_ring(काष्ठा emac_instance *dev, पूर्णांक new_mtu)
अणु
	पूर्णांक rx_sync_size = emac_rx_sync_size(new_mtu);
	पूर्णांक rx_skb_size = emac_rx_skb_size(new_mtu);
	पूर्णांक i, ret = 0;
	पूर्णांक mr1_jumbo_bit_change = 0;

	mutex_lock(&dev->link_lock);
	emac_netअगर_stop(dev);
	emac_rx_disable(dev);
	mal_disable_rx_channel(dev->mal, dev->mal_rx_chan);

	अगर (dev->rx_sg_skb) अणु
		++dev->estats.rx_dropped_resize;
		dev_kमुक्त_skb(dev->rx_sg_skb);
		dev->rx_sg_skb = शून्य;
	पूर्ण

	/* Make a first pass over RX ring and mark BDs पढ़ोy, dropping
	 * non-processed packets on the way. We need this as a separate pass
	 * to simplअगरy error recovery in the हाल of allocation failure later.
	 */
	क्रम (i = 0; i < NUM_RX_BUFF; ++i) अणु
		अगर (dev->rx_desc[i].ctrl & MAL_RX_CTRL_FIRST)
			++dev->estats.rx_dropped_resize;

		dev->rx_desc[i].data_len = 0;
		dev->rx_desc[i].ctrl = MAL_RX_CTRL_EMPTY |
		    (i == (NUM_RX_BUFF - 1) ? MAL_RX_CTRL_WRAP : 0);
	पूर्ण

	/* Reallocate RX ring only अगर bigger skb buffers are required */
	अगर (rx_skb_size <= dev->rx_skb_size)
		जाओ skip;

	/* Second pass, allocate new skbs */
	क्रम (i = 0; i < NUM_RX_BUFF; ++i) अणु
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(dev->ndev, rx_skb_size);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ oom;
		पूर्ण

		BUG_ON(!dev->rx_skb[i]);
		dev_kमुक्त_skb(dev->rx_skb[i]);

		dev->rx_desc[i].data_ptr =
		    dma_map_single(&dev->ofdev->dev, skb->data - NET_IP_ALIGN,
				   rx_sync_size, DMA_FROM_DEVICE)
				   + NET_IP_ALIGN;
		dev->rx_skb[i] = skb;
	पूर्ण
 skip:
	/* Check अगर we need to change "Jumbo" bit in MR1 */
	अगर (emac_has_feature(dev, EMAC_APM821XX_REQ_JUMBO_FRAME_SIZE)) अणु
		mr1_jumbo_bit_change = (new_mtu > ETH_DATA_LEN) ||
				(dev->ndev->mtu > ETH_DATA_LEN);
	पूर्ण अन्यथा अणु
		mr1_jumbo_bit_change = (new_mtu > ETH_DATA_LEN) ^
				(dev->ndev->mtu > ETH_DATA_LEN);
	पूर्ण

	अगर (mr1_jumbo_bit_change) अणु
		/* This is to prevent starting RX channel in emac_rx_enable() */
		set_bit(MAL_COMMAC_RX_STOPPED, &dev->commac.flags);

		dev->ndev->mtu = new_mtu;
		emac_full_tx_reset(dev);
	पूर्ण

	mal_set_rcbs(dev->mal, dev->mal_rx_chan, emac_rx_size(new_mtu));
 oom:
	/* Restart RX */
	clear_bit(MAL_COMMAC_RX_STOPPED, &dev->commac.flags);
	dev->rx_slot = 0;
	mal_enable_rx_channel(dev->mal, dev->mal_rx_chan);
	emac_rx_enable(dev);
	emac_netअगर_start(dev);
	mutex_unlock(&dev->link_lock);

	वापस ret;
पूर्ण

/* Process ctx, rtnl_lock semaphore */
अटल पूर्णांक emac_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	पूर्णांक ret = 0;

	DBG(dev, "change_mtu(%d)" NL, new_mtu);

	अगर (netअगर_running(ndev)) अणु
		/* Check अगर we really need to reinitialize RX ring */
		अगर (emac_rx_skb_size(ndev->mtu) != emac_rx_skb_size(new_mtu))
			ret = emac_resize_rx_ring(dev, new_mtu);
	पूर्ण

	अगर (!ret) अणु
		ndev->mtu = new_mtu;
		dev->rx_skb_size = emac_rx_skb_size(new_mtu);
		dev->rx_sync_size = emac_rx_sync_size(new_mtu);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम emac_clean_tx_ring(काष्ठा emac_instance *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_TX_BUFF; ++i) अणु
		अगर (dev->tx_skb[i]) अणु
			dev_kमुक्त_skb(dev->tx_skb[i]);
			dev->tx_skb[i] = शून्य;
			अगर (dev->tx_desc[i].ctrl & MAL_TX_CTRL_READY)
				++dev->estats.tx_dropped;
		पूर्ण
		dev->tx_desc[i].ctrl = 0;
		dev->tx_desc[i].data_ptr = 0;
	पूर्ण
पूर्ण

अटल व्योम emac_clean_rx_ring(काष्ठा emac_instance *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_RX_BUFF; ++i)
		अगर (dev->rx_skb[i]) अणु
			dev->rx_desc[i].ctrl = 0;
			dev_kमुक्त_skb(dev->rx_skb[i]);
			dev->rx_skb[i] = शून्य;
			dev->rx_desc[i].data_ptr = 0;
		पूर्ण

	अगर (dev->rx_sg_skb) अणु
		dev_kमुक्त_skb(dev->rx_sg_skb);
		dev->rx_sg_skb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
__emac_prepare_rx_skb(काष्ठा sk_buff *skb, काष्ठा emac_instance *dev, पूर्णांक slot)
अणु
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	dev->rx_skb[slot] = skb;
	dev->rx_desc[slot].data_len = 0;

	dev->rx_desc[slot].data_ptr =
	    dma_map_single(&dev->ofdev->dev, skb->data - NET_IP_ALIGN,
			   dev->rx_sync_size, DMA_FROM_DEVICE) + NET_IP_ALIGN;
	wmb();
	dev->rx_desc[slot].ctrl = MAL_RX_CTRL_EMPTY |
	    (slot == (NUM_RX_BUFF - 1) ? MAL_RX_CTRL_WRAP : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
emac_alloc_rx_skb(काष्ठा emac_instance *dev, पूर्णांक slot)
अणु
	काष्ठा sk_buff *skb;

	skb = __netdev_alloc_skb_ip_align(dev->ndev, dev->rx_skb_size,
					  GFP_KERNEL);

	वापस __emac_prepare_rx_skb(skb, dev, slot);
पूर्ण

अटल पूर्णांक
emac_alloc_rx_skb_napi(काष्ठा emac_instance *dev, पूर्णांक slot)
अणु
	काष्ठा sk_buff *skb;

	skb = napi_alloc_skb(&dev->mal->napi, dev->rx_skb_size);

	वापस __emac_prepare_rx_skb(skb, dev, slot);
पूर्ण

अटल व्योम emac_prपूर्णांक_link_status(काष्ठा emac_instance *dev)
अणु
	अगर (netअगर_carrier_ok(dev->ndev))
		prपूर्णांकk(KERN_INFO "%s: link is up, %d %s%s\n",
		       dev->ndev->name, dev->phy.speed,
		       dev->phy.duplex == DUPLEX_FULL ? "FDX" : "HDX",
		       dev->phy.छोड़ो ? ", pause enabled" :
		       dev->phy.asym_छोड़ो ? ", asymmetric pause enabled" : "");
	अन्यथा
		prपूर्णांकk(KERN_INFO "%s: link is down\n", dev->ndev->name);
पूर्ण

/* Process ctx, rtnl_lock semaphore */
अटल पूर्णांक emac_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	पूर्णांक err, i;

	DBG(dev, "open" NL);

	/* Setup error IRQ handler */
	err = request_irq(dev->emac_irq, emac_irq, 0, "EMAC", dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to request IRQ %d\n",
		       ndev->name, dev->emac_irq);
		वापस err;
	पूर्ण

	/* Allocate RX ring */
	क्रम (i = 0; i < NUM_RX_BUFF; ++i)
		अगर (emac_alloc_rx_skb(dev, i)) अणु
			prपूर्णांकk(KERN_ERR "%s: failed to allocate RX ring\n",
			       ndev->name);
			जाओ oom;
		पूर्ण

	dev->tx_cnt = dev->tx_slot = dev->ack_slot = dev->rx_slot = 0;
	clear_bit(MAL_COMMAC_RX_STOPPED, &dev->commac.flags);
	dev->rx_sg_skb = शून्य;

	mutex_lock(&dev->link_lock);
	dev->खोलोed = 1;

	/* Start PHY polling now.
	 */
	अगर (dev->phy.address >= 0) अणु
		पूर्णांक link_poll_पूर्णांकerval;
		अगर (dev->phy.def->ops->poll_link(&dev->phy)) अणु
			dev->phy.def->ops->पढ़ो_link(&dev->phy);
			emac_rx_clk_शेष(dev);
			netअगर_carrier_on(dev->ndev);
			link_poll_पूर्णांकerval = PHY_POLL_LINK_ON;
		पूर्ण अन्यथा अणु
			emac_rx_clk_tx(dev);
			netअगर_carrier_off(dev->ndev);
			link_poll_पूर्णांकerval = PHY_POLL_LINK_OFF;
		पूर्ण
		dev->link_polling = 1;
		wmb();
		schedule_delayed_work(&dev->link_work, link_poll_पूर्णांकerval);
		emac_prपूर्णांक_link_status(dev);
	पूर्ण अन्यथा
		netअगर_carrier_on(dev->ndev);

	/* Required क्रम Pause packet support in EMAC */
	dev_mc_add_global(ndev, शेष_mcast_addr);

	emac_configure(dev);
	mal_poll_add(dev->mal, &dev->commac);
	mal_enable_tx_channel(dev->mal, dev->mal_tx_chan);
	mal_set_rcbs(dev->mal, dev->mal_rx_chan, emac_rx_size(ndev->mtu));
	mal_enable_rx_channel(dev->mal, dev->mal_rx_chan);
	emac_tx_enable(dev);
	emac_rx_enable(dev);
	emac_netअगर_start(dev);

	mutex_unlock(&dev->link_lock);

	वापस 0;
 oom:
	emac_clean_rx_ring(dev);
	मुक्त_irq(dev->emac_irq, dev);

	वापस -ENOMEM;
पूर्ण

/* BHs disabled */
#अगर 0
अटल पूर्णांक emac_link_dअगरfers(काष्ठा emac_instance *dev)
अणु
	u32 r = in_be32(&dev->emacp->mr1);

	पूर्णांक duplex = r & EMAC_MR1_FDE ? DUPLEX_FULL : DUPLEX_HALF;
	पूर्णांक speed, छोड़ो, asym_छोड़ो;

	अगर (r & EMAC_MR1_MF_1000)
		speed = SPEED_1000;
	अन्यथा अगर (r & EMAC_MR1_MF_100)
		speed = SPEED_100;
	अन्यथा
		speed = SPEED_10;

	चयन (r & (EMAC_MR1_EIFC | EMAC_MR1_APP)) अणु
	हाल (EMAC_MR1_EIFC | EMAC_MR1_APP):
		छोड़ो = 1;
		asym_छोड़ो = 0;
		अवरोध;
	हाल EMAC_MR1_APP:
		छोड़ो = 0;
		asym_छोड़ो = 1;
		अवरोध;
	शेष:
		छोड़ो = asym_छोड़ो = 0;
	पूर्ण
	वापस speed != dev->phy.speed || duplex != dev->phy.duplex ||
	    छोड़ो != dev->phy.छोड़ो || asym_छोड़ो != dev->phy.asym_छोड़ो;
पूर्ण
#पूर्ण_अगर

अटल व्योम emac_link_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा emac_instance *dev =
		container_of(to_delayed_work(work),
			     काष्ठा emac_instance, link_work);
	पूर्णांक link_poll_पूर्णांकerval;

	mutex_lock(&dev->link_lock);
	DBG2(dev, "link timer" NL);

	अगर (!dev->खोलोed)
		जाओ bail;

	अगर (dev->phy.def->ops->poll_link(&dev->phy)) अणु
		अगर (!netअगर_carrier_ok(dev->ndev)) अणु
			emac_rx_clk_शेष(dev);
			/* Get new link parameters */
			dev->phy.def->ops->पढ़ो_link(&dev->phy);

			netअगर_carrier_on(dev->ndev);
			emac_netअगर_stop(dev);
			emac_full_tx_reset(dev);
			emac_netअगर_start(dev);
			emac_prपूर्णांक_link_status(dev);
		पूर्ण
		link_poll_पूर्णांकerval = PHY_POLL_LINK_ON;
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(dev->ndev)) अणु
			emac_rx_clk_tx(dev);
			netअगर_carrier_off(dev->ndev);
			netअगर_tx_disable(dev->ndev);
			emac_reinitialize(dev);
			emac_prपूर्णांक_link_status(dev);
		पूर्ण
		link_poll_पूर्णांकerval = PHY_POLL_LINK_OFF;
	पूर्ण
	schedule_delayed_work(&dev->link_work, link_poll_पूर्णांकerval);
 bail:
	mutex_unlock(&dev->link_lock);
पूर्ण

अटल व्योम emac_क्रमce_link_update(काष्ठा emac_instance *dev)
अणु
	netअगर_carrier_off(dev->ndev);
	smp_rmb();
	अगर (dev->link_polling) अणु
		cancel_delayed_work_sync(&dev->link_work);
		अगर (dev->link_polling)
			schedule_delayed_work(&dev->link_work,  PHY_POLL_LINK_OFF);
	पूर्ण
पूर्ण

/* Process ctx, rtnl_lock semaphore */
अटल पूर्णांक emac_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	DBG(dev, "close" NL);

	अगर (dev->phy.address >= 0) अणु
		dev->link_polling = 0;
		cancel_delayed_work_sync(&dev->link_work);
	पूर्ण
	mutex_lock(&dev->link_lock);
	emac_netअगर_stop(dev);
	dev->खोलोed = 0;
	mutex_unlock(&dev->link_lock);

	emac_rx_disable(dev);
	emac_tx_disable(dev);
	mal_disable_rx_channel(dev->mal, dev->mal_rx_chan);
	mal_disable_tx_channel(dev->mal, dev->mal_tx_chan);
	mal_poll_del(dev->mal, &dev->commac);

	emac_clean_tx_ring(dev);
	emac_clean_rx_ring(dev);

	मुक्त_irq(dev->emac_irq, dev);

	netअगर_carrier_off(ndev);

	वापस 0;
पूर्ण

अटल अंतरभूत u16 emac_tx_csum(काष्ठा emac_instance *dev,
			       काष्ठा sk_buff *skb)
अणु
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_TAH) &&
		(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		++dev->stats.tx_packets_csum;
		वापस EMAC_TX_CTRL_TAH_CSUM;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत netdev_tx_t emac_xmit_finish(काष्ठा emac_instance *dev, पूर्णांक len)
अणु
	काष्ठा emac_regs __iomem *p = dev->emacp;
	काष्ठा net_device *ndev = dev->ndev;

	/* Send the packet out. If the अगर makes a signअगरicant perf
	 * dअगरference, then we can store the TMR0 value in "dev"
	 * instead
	 */
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4))
		out_be32(&p->पंचांगr0, EMAC4_TMR0_XMIT);
	अन्यथा
		out_be32(&p->पंचांगr0, EMAC_TMR0_XMIT);

	अगर (unlikely(++dev->tx_cnt == NUM_TX_BUFF)) अणु
		netअगर_stop_queue(ndev);
		DBG2(dev, "stopped TX queue" NL);
	पूर्ण

	netअगर_trans_update(ndev);
	++dev->stats.tx_packets;
	dev->stats.tx_bytes += len;

	वापस NETDEV_TX_OK;
पूर्ण

/* Tx lock BH */
अटल netdev_tx_t emac_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	अचिन्हित पूर्णांक len = skb->len;
	पूर्णांक slot;

	u16 ctrl = EMAC_TX_CTRL_GFCS | EMAC_TX_CTRL_GP | MAL_TX_CTRL_READY |
	    MAL_TX_CTRL_LAST | emac_tx_csum(dev, skb);

	slot = dev->tx_slot++;
	अगर (dev->tx_slot == NUM_TX_BUFF) अणु
		dev->tx_slot = 0;
		ctrl |= MAL_TX_CTRL_WRAP;
	पूर्ण

	DBG2(dev, "xmit(%u) %d" NL, len, slot);

	dev->tx_skb[slot] = skb;
	dev->tx_desc[slot].data_ptr = dma_map_single(&dev->ofdev->dev,
						     skb->data, len,
						     DMA_TO_DEVICE);
	dev->tx_desc[slot].data_len = (u16) len;
	wmb();
	dev->tx_desc[slot].ctrl = ctrl;

	वापस emac_xmit_finish(dev, len);
पूर्ण

अटल अंतरभूत पूर्णांक emac_xmit_split(काष्ठा emac_instance *dev, पूर्णांक slot,
				  u32 pd, पूर्णांक len, पूर्णांक last, u16 base_ctrl)
अणु
	जबतक (1) अणु
		u16 ctrl = base_ctrl;
		पूर्णांक chunk = min(len, MAL_MAX_TX_SIZE);
		len -= chunk;

		slot = (slot + 1) % NUM_TX_BUFF;

		अगर (last && !len)
			ctrl |= MAL_TX_CTRL_LAST;
		अगर (slot == NUM_TX_BUFF - 1)
			ctrl |= MAL_TX_CTRL_WRAP;

		dev->tx_skb[slot] = शून्य;
		dev->tx_desc[slot].data_ptr = pd;
		dev->tx_desc[slot].data_len = (u16) chunk;
		dev->tx_desc[slot].ctrl = ctrl;
		++dev->tx_cnt;

		अगर (!len)
			अवरोध;

		pd += chunk;
	पूर्ण
	वापस slot;
पूर्ण

/* Tx lock BH disabled (SG version क्रम TAH equipped EMACs) */
अटल netdev_tx_t
emac_start_xmit_sg(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक len = skb->len, chunk;
	पूर्णांक slot, i;
	u16 ctrl;
	u32 pd;

	/* This is common "fast" path */
	अगर (likely(!nr_frags && len <= MAL_MAX_TX_SIZE))
		वापस emac_start_xmit(skb, ndev);

	len -= skb->data_len;

	/* Note, this is only an *estimation*, we can still run out of empty
	 * slots because of the additional fragmentation पूर्णांकo
	 * MAL_MAX_TX_SIZE-sized chunks
	 */
	अगर (unlikely(dev->tx_cnt + nr_frags + mal_tx_chunks(len) > NUM_TX_BUFF))
		जाओ stop_queue;

	ctrl = EMAC_TX_CTRL_GFCS | EMAC_TX_CTRL_GP | MAL_TX_CTRL_READY |
	    emac_tx_csum(dev, skb);
	slot = dev->tx_slot;

	/* skb data */
	dev->tx_skb[slot] = शून्य;
	chunk = min(len, MAL_MAX_TX_SIZE);
	dev->tx_desc[slot].data_ptr = pd =
	    dma_map_single(&dev->ofdev->dev, skb->data, len, DMA_TO_DEVICE);
	dev->tx_desc[slot].data_len = (u16) chunk;
	len -= chunk;
	अगर (unlikely(len))
		slot = emac_xmit_split(dev, slot, pd + chunk, len, !nr_frags,
				       ctrl);
	/* skb fragments */
	क्रम (i = 0; i < nr_frags; ++i) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		len = skb_frag_size(frag);

		अगर (unlikely(dev->tx_cnt + mal_tx_chunks(len) >= NUM_TX_BUFF))
			जाओ unकरो_frame;

		pd = skb_frag_dma_map(&dev->ofdev->dev, frag, 0, len,
				      DMA_TO_DEVICE);

		slot = emac_xmit_split(dev, slot, pd, len, i == nr_frags - 1,
				       ctrl);
	पूर्ण

	DBG2(dev, "xmit_sg(%u) %d - %d" NL, skb->len, dev->tx_slot, slot);

	/* Attach skb to the last slot so we करोn't release it too early */
	dev->tx_skb[slot] = skb;

	/* Send the packet out */
	अगर (dev->tx_slot == NUM_TX_BUFF - 1)
		ctrl |= MAL_TX_CTRL_WRAP;
	wmb();
	dev->tx_desc[dev->tx_slot].ctrl = ctrl;
	dev->tx_slot = (slot + 1) % NUM_TX_BUFF;

	वापस emac_xmit_finish(dev, skb->len);

 unकरो_frame:
	/* Well, too bad. Our previous estimation was overly optimistic.
	 * Unकरो everything.
	 */
	जबतक (slot != dev->tx_slot) अणु
		dev->tx_desc[slot].ctrl = 0;
		--dev->tx_cnt;
		अगर (--slot < 0)
			slot = NUM_TX_BUFF - 1;
	पूर्ण
	++dev->estats.tx_unकरो;

 stop_queue:
	netअगर_stop_queue(ndev);
	DBG2(dev, "stopped TX queue" NL);
	वापस NETDEV_TX_BUSY;
पूर्ण

/* Tx lock BHs */
अटल व्योम emac_parse_tx_error(काष्ठा emac_instance *dev, u16 ctrl)
अणु
	काष्ठा emac_error_stats *st = &dev->estats;

	DBG(dev, "BD TX error %04x" NL, ctrl);

	++st->tx_bd_errors;
	अगर (ctrl & EMAC_TX_ST_BFCS)
		++st->tx_bd_bad_fcs;
	अगर (ctrl & EMAC_TX_ST_LCS)
		++st->tx_bd_carrier_loss;
	अगर (ctrl & EMAC_TX_ST_ED)
		++st->tx_bd_excessive_deferral;
	अगर (ctrl & EMAC_TX_ST_EC)
		++st->tx_bd_excessive_collisions;
	अगर (ctrl & EMAC_TX_ST_LC)
		++st->tx_bd_late_collision;
	अगर (ctrl & EMAC_TX_ST_MC)
		++st->tx_bd_multple_collisions;
	अगर (ctrl & EMAC_TX_ST_SC)
		++st->tx_bd_single_collision;
	अगर (ctrl & EMAC_TX_ST_UR)
		++st->tx_bd_underrun;
	अगर (ctrl & EMAC_TX_ST_SQE)
		++st->tx_bd_sqe;
पूर्ण

अटल व्योम emac_poll_tx(व्योम *param)
अणु
	काष्ठा emac_instance *dev = param;
	u32 bad_mask;

	DBG2(dev, "poll_tx, %d %d" NL, dev->tx_cnt, dev->ack_slot);

	अगर (emac_has_feature(dev, EMAC_FTR_HAS_TAH))
		bad_mask = EMAC_IS_BAD_TX_TAH;
	अन्यथा
		bad_mask = EMAC_IS_BAD_TX;

	netअगर_tx_lock_bh(dev->ndev);
	अगर (dev->tx_cnt) अणु
		u16 ctrl;
		पूर्णांक slot = dev->ack_slot, n = 0;
	again:
		ctrl = dev->tx_desc[slot].ctrl;
		अगर (!(ctrl & MAL_TX_CTRL_READY)) अणु
			काष्ठा sk_buff *skb = dev->tx_skb[slot];
			++n;

			अगर (skb) अणु
				dev_kमुक्त_skb(skb);
				dev->tx_skb[slot] = शून्य;
			पूर्ण
			slot = (slot + 1) % NUM_TX_BUFF;

			अगर (unlikely(ctrl & bad_mask))
				emac_parse_tx_error(dev, ctrl);

			अगर (--dev->tx_cnt)
				जाओ again;
		पूर्ण
		अगर (n) अणु
			dev->ack_slot = slot;
			अगर (netअगर_queue_stopped(dev->ndev) &&
			    dev->tx_cnt < EMAC_TX_WAKEUP_THRESH)
				netअगर_wake_queue(dev->ndev);

			DBG2(dev, "tx %d pkts" NL, n);
		पूर्ण
	पूर्ण
	netअगर_tx_unlock_bh(dev->ndev);
पूर्ण

अटल अंतरभूत व्योम emac_recycle_rx_skb(काष्ठा emac_instance *dev, पूर्णांक slot,
				       पूर्णांक len)
अणु
	काष्ठा sk_buff *skb = dev->rx_skb[slot];

	DBG2(dev, "recycle %d %d" NL, slot, len);

	अगर (len)
		dma_map_single(&dev->ofdev->dev, skb->data - NET_IP_ALIGN,
			       SKB_DATA_ALIGN(len + NET_IP_ALIGN),
			       DMA_FROM_DEVICE);

	dev->rx_desc[slot].data_len = 0;
	wmb();
	dev->rx_desc[slot].ctrl = MAL_RX_CTRL_EMPTY |
	    (slot == (NUM_RX_BUFF - 1) ? MAL_RX_CTRL_WRAP : 0);
पूर्ण

अटल व्योम emac_parse_rx_error(काष्ठा emac_instance *dev, u16 ctrl)
अणु
	काष्ठा emac_error_stats *st = &dev->estats;

	DBG(dev, "BD RX error %04x" NL, ctrl);

	++st->rx_bd_errors;
	अगर (ctrl & EMAC_RX_ST_OE)
		++st->rx_bd_overrun;
	अगर (ctrl & EMAC_RX_ST_BP)
		++st->rx_bd_bad_packet;
	अगर (ctrl & EMAC_RX_ST_RP)
		++st->rx_bd_runt_packet;
	अगर (ctrl & EMAC_RX_ST_SE)
		++st->rx_bd_लघु_event;
	अगर (ctrl & EMAC_RX_ST_AE)
		++st->rx_bd_alignment_error;
	अगर (ctrl & EMAC_RX_ST_BFCS)
		++st->rx_bd_bad_fcs;
	अगर (ctrl & EMAC_RX_ST_PTL)
		++st->rx_bd_packet_too_दीर्घ;
	अगर (ctrl & EMAC_RX_ST_ORE)
		++st->rx_bd_out_of_range;
	अगर (ctrl & EMAC_RX_ST_IRE)
		++st->rx_bd_in_range;
पूर्ण

अटल अंतरभूत व्योम emac_rx_csum(काष्ठा emac_instance *dev,
				काष्ठा sk_buff *skb, u16 ctrl)
अणु
#अगर_घोषित CONFIG_IBM_EMAC_TAH
	अगर (!ctrl && dev->tah_dev) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		++dev->stats.rx_packets_csum;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक emac_rx_sg_append(काष्ठा emac_instance *dev, पूर्णांक slot)
अणु
	अगर (likely(dev->rx_sg_skb != शून्य)) अणु
		पूर्णांक len = dev->rx_desc[slot].data_len;
		पूर्णांक tot_len = dev->rx_sg_skb->len + len;

		अगर (unlikely(tot_len + NET_IP_ALIGN > dev->rx_skb_size)) अणु
			++dev->estats.rx_dropped_mtu;
			dev_kमुक्त_skb(dev->rx_sg_skb);
			dev->rx_sg_skb = शून्य;
		पूर्ण अन्यथा अणु
			स_नकल(skb_tail_poपूर्णांकer(dev->rx_sg_skb),
					 dev->rx_skb[slot]->data, len);
			skb_put(dev->rx_sg_skb, len);
			emac_recycle_rx_skb(dev, slot, len);
			वापस 0;
		पूर्ण
	पूर्ण
	emac_recycle_rx_skb(dev, slot, 0);
	वापस -1;
पूर्ण

/* NAPI poll context */
अटल पूर्णांक emac_poll_rx(व्योम *param, पूर्णांक budget)
अणु
	काष्ठा emac_instance *dev = param;
	पूर्णांक slot = dev->rx_slot, received = 0;

	DBG2(dev, "poll_rx(%d)" NL, budget);

 again:
	जबतक (budget > 0) अणु
		पूर्णांक len;
		काष्ठा sk_buff *skb;
		u16 ctrl = dev->rx_desc[slot].ctrl;

		अगर (ctrl & MAL_RX_CTRL_EMPTY)
			अवरोध;

		skb = dev->rx_skb[slot];
		mb();
		len = dev->rx_desc[slot].data_len;

		अगर (unlikely(!MAL_IS_SINGLE_RX(ctrl)))
			जाओ sg;

		ctrl &= EMAC_BAD_RX_MASK;
		अगर (unlikely(ctrl && ctrl != EMAC_RX_TAH_BAD_CSUM)) अणु
			emac_parse_rx_error(dev, ctrl);
			++dev->estats.rx_dropped_error;
			emac_recycle_rx_skb(dev, slot, 0);
			len = 0;
			जाओ next;
		पूर्ण

		अगर (len < ETH_HLEN) अणु
			++dev->estats.rx_dropped_stack;
			emac_recycle_rx_skb(dev, slot, len);
			जाओ next;
		पूर्ण

		अगर (len && len < EMAC_RX_COPY_THRESH) अणु
			काष्ठा sk_buff *copy_skb;

			copy_skb = napi_alloc_skb(&dev->mal->napi, len);
			अगर (unlikely(!copy_skb))
				जाओ oom;

			स_नकल(copy_skb->data - NET_IP_ALIGN,
			       skb->data - NET_IP_ALIGN,
			       len + NET_IP_ALIGN);
			emac_recycle_rx_skb(dev, slot, len);
			skb = copy_skb;
		पूर्ण अन्यथा अगर (unlikely(emac_alloc_rx_skb_napi(dev, slot)))
			जाओ oom;

		skb_put(skb, len);
	push_packet:
		skb->protocol = eth_type_trans(skb, dev->ndev);
		emac_rx_csum(dev, skb, ctrl);

		अगर (unlikely(netअगर_receive_skb(skb) == NET_RX_DROP))
			++dev->estats.rx_dropped_stack;
	next:
		++dev->stats.rx_packets;
	skip:
		dev->stats.rx_bytes += len;
		slot = (slot + 1) % NUM_RX_BUFF;
		--budget;
		++received;
		जारी;
	sg:
		अगर (ctrl & MAL_RX_CTRL_FIRST) अणु
			BUG_ON(dev->rx_sg_skb);
			अगर (unlikely(emac_alloc_rx_skb_napi(dev, slot))) अणु
				DBG(dev, "rx OOM %d" NL, slot);
				++dev->estats.rx_dropped_oom;
				emac_recycle_rx_skb(dev, slot, 0);
			पूर्ण अन्यथा अणु
				dev->rx_sg_skb = skb;
				skb_put(skb, len);
			पूर्ण
		पूर्ण अन्यथा अगर (!emac_rx_sg_append(dev, slot) &&
			   (ctrl & MAL_RX_CTRL_LAST)) अणु

			skb = dev->rx_sg_skb;
			dev->rx_sg_skb = शून्य;

			ctrl &= EMAC_BAD_RX_MASK;
			अगर (unlikely(ctrl && ctrl != EMAC_RX_TAH_BAD_CSUM)) अणु
				emac_parse_rx_error(dev, ctrl);
				++dev->estats.rx_dropped_error;
				dev_kमुक्त_skb(skb);
				len = 0;
			पूर्ण अन्यथा
				जाओ push_packet;
		पूर्ण
		जाओ skip;
	oom:
		DBG(dev, "rx OOM %d" NL, slot);
		/* Drop the packet and recycle skb */
		++dev->estats.rx_dropped_oom;
		emac_recycle_rx_skb(dev, slot, 0);
		जाओ next;
	पूर्ण

	अगर (received) अणु
		DBG2(dev, "rx %d BDs" NL, received);
		dev->rx_slot = slot;
	पूर्ण

	अगर (unlikely(budget && test_bit(MAL_COMMAC_RX_STOPPED, &dev->commac.flags))) अणु
		mb();
		अगर (!(dev->rx_desc[slot].ctrl & MAL_RX_CTRL_EMPTY)) अणु
			DBG2(dev, "rx restart" NL);
			received = 0;
			जाओ again;
		पूर्ण

		अगर (dev->rx_sg_skb) अणु
			DBG2(dev, "dropping partial rx packet" NL);
			++dev->estats.rx_dropped_error;
			dev_kमुक्त_skb(dev->rx_sg_skb);
			dev->rx_sg_skb = शून्य;
		पूर्ण

		clear_bit(MAL_COMMAC_RX_STOPPED, &dev->commac.flags);
		mal_enable_rx_channel(dev->mal, dev->mal_rx_chan);
		emac_rx_enable(dev);
		dev->rx_slot = 0;
	पूर्ण
	वापस received;
पूर्ण

/* NAPI poll context */
अटल पूर्णांक emac_peek_rx(व्योम *param)
अणु
	काष्ठा emac_instance *dev = param;

	वापस !(dev->rx_desc[dev->rx_slot].ctrl & MAL_RX_CTRL_EMPTY);
पूर्ण

/* NAPI poll context */
अटल पूर्णांक emac_peek_rx_sg(व्योम *param)
अणु
	काष्ठा emac_instance *dev = param;

	पूर्णांक slot = dev->rx_slot;
	जबतक (1) अणु
		u16 ctrl = dev->rx_desc[slot].ctrl;
		अगर (ctrl & MAL_RX_CTRL_EMPTY)
			वापस 0;
		अन्यथा अगर (ctrl & MAL_RX_CTRL_LAST)
			वापस 1;

		slot = (slot + 1) % NUM_RX_BUFF;

		/* I'm just being paranoid here :) */
		अगर (unlikely(slot == dev->rx_slot))
			वापस 0;
	पूर्ण
पूर्ण

/* Hard IRQ */
अटल व्योम emac_rxde(व्योम *param)
अणु
	काष्ठा emac_instance *dev = param;

	++dev->estats.rx_stopped;
	emac_rx_disable_async(dev);
पूर्ण

/* Hard IRQ */
अटल irqवापस_t emac_irq(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा emac_instance *dev = dev_instance;
	काष्ठा emac_regs __iomem *p = dev->emacp;
	काष्ठा emac_error_stats *st = &dev->estats;
	u32 isr;

	spin_lock(&dev->lock);

	isr = in_be32(&p->isr);
	out_be32(&p->isr, isr);

	DBG(dev, "isr = %08x" NL, isr);

	अगर (isr & EMAC4_ISR_TXPE)
		++st->tx_parity;
	अगर (isr & EMAC4_ISR_RXPE)
		++st->rx_parity;
	अगर (isr & EMAC4_ISR_TXUE)
		++st->tx_underrun;
	अगर (isr & EMAC4_ISR_RXOE)
		++st->rx_fअगरo_overrun;
	अगर (isr & EMAC_ISR_OVR)
		++st->rx_overrun;
	अगर (isr & EMAC_ISR_BP)
		++st->rx_bad_packet;
	अगर (isr & EMAC_ISR_RP)
		++st->rx_runt_packet;
	अगर (isr & EMAC_ISR_SE)
		++st->rx_लघु_event;
	अगर (isr & EMAC_ISR_ALE)
		++st->rx_alignment_error;
	अगर (isr & EMAC_ISR_BFCS)
		++st->rx_bad_fcs;
	अगर (isr & EMAC_ISR_PTLE)
		++st->rx_packet_too_दीर्घ;
	अगर (isr & EMAC_ISR_ORE)
		++st->rx_out_of_range;
	अगर (isr & EMAC_ISR_IRE)
		++st->rx_in_range;
	अगर (isr & EMAC_ISR_SQE)
		++st->tx_sqe;
	अगर (isr & EMAC_ISR_TE)
		++st->tx_errors;

	spin_unlock(&dev->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा net_device_stats *emac_stats(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	काष्ठा emac_stats *st = &dev->stats;
	काष्ठा emac_error_stats *est = &dev->estats;
	काष्ठा net_device_stats *nst = &ndev->stats;
	अचिन्हित दीर्घ flags;

	DBG2(dev, "stats" NL);

	/* Compute "legacy" statistics */
	spin_lock_irqsave(&dev->lock, flags);
	nst->rx_packets = (अचिन्हित दीर्घ)st->rx_packets;
	nst->rx_bytes = (अचिन्हित दीर्घ)st->rx_bytes;
	nst->tx_packets = (अचिन्हित दीर्घ)st->tx_packets;
	nst->tx_bytes = (अचिन्हित दीर्घ)st->tx_bytes;
	nst->rx_dropped = (अचिन्हित दीर्घ)(est->rx_dropped_oom +
					  est->rx_dropped_error +
					  est->rx_dropped_resize +
					  est->rx_dropped_mtu);
	nst->tx_dropped = (अचिन्हित दीर्घ)est->tx_dropped;

	nst->rx_errors = (अचिन्हित दीर्घ)est->rx_bd_errors;
	nst->rx_fअगरo_errors = (अचिन्हित दीर्घ)(est->rx_bd_overrun +
					      est->rx_fअगरo_overrun +
					      est->rx_overrun);
	nst->rx_frame_errors = (अचिन्हित दीर्घ)(est->rx_bd_alignment_error +
					       est->rx_alignment_error);
	nst->rx_crc_errors = (अचिन्हित दीर्घ)(est->rx_bd_bad_fcs +
					     est->rx_bad_fcs);
	nst->rx_length_errors = (अचिन्हित दीर्घ)(est->rx_bd_runt_packet +
						est->rx_bd_लघु_event +
						est->rx_bd_packet_too_दीर्घ +
						est->rx_bd_out_of_range +
						est->rx_bd_in_range +
						est->rx_runt_packet +
						est->rx_लघु_event +
						est->rx_packet_too_दीर्घ +
						est->rx_out_of_range +
						est->rx_in_range);

	nst->tx_errors = (अचिन्हित दीर्घ)(est->tx_bd_errors + est->tx_errors);
	nst->tx_fअगरo_errors = (अचिन्हित दीर्घ)(est->tx_bd_underrun +
					      est->tx_underrun);
	nst->tx_carrier_errors = (अचिन्हित दीर्घ)est->tx_bd_carrier_loss;
	nst->collisions = (अचिन्हित दीर्घ)(est->tx_bd_excessive_deferral +
					  est->tx_bd_excessive_collisions +
					  est->tx_bd_late_collision +
					  est->tx_bd_multple_collisions);
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस nst;
पूर्ण

अटल काष्ठा mal_commac_ops emac_commac_ops = अणु
	.poll_tx = &emac_poll_tx,
	.poll_rx = &emac_poll_rx,
	.peek_rx = &emac_peek_rx,
	.rxde = &emac_rxde,
पूर्ण;

अटल काष्ठा mal_commac_ops emac_commac_sg_ops = अणु
	.poll_tx = &emac_poll_tx,
	.poll_rx = &emac_poll_rx,
	.peek_rx = &emac_peek_rx_sg,
	.rxde = &emac_rxde,
पूर्ण;

/* Ethtool support */
अटल पूर्णांक emac_ethtool_get_link_ksettings(काष्ठा net_device *ndev,
					   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	u32 supported, advertising;

	supported = dev->phy.features;
	cmd->base.port = PORT_MII;
	cmd->base.phy_address = dev->phy.address;

	mutex_lock(&dev->link_lock);
	advertising = dev->phy.advertising;
	cmd->base.स्वतःneg = dev->phy.स्वतःneg;
	cmd->base.speed = dev->phy.speed;
	cmd->base.duplex = dev->phy.duplex;
	mutex_unlock(&dev->link_lock);

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक
emac_ethtool_set_link_ksettings(काष्ठा net_device *ndev,
				स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	u32 f = dev->phy.features;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	DBG(dev, "set_settings(%d, %d, %d, 0x%08x)" NL,
	    cmd->base.स्वतःneg, cmd->base.speed, cmd->base.duplex, advertising);

	/* Basic sanity checks */
	अगर (dev->phy.address < 0)
		वापस -EOPNOTSUPP;
	अगर (cmd->base.स्वतःneg != AUTONEG_ENABLE &&
	    cmd->base.स्वतःneg != AUTONEG_DISABLE)
		वापस -EINVAL;
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE && advertising == 0)
		वापस -EINVAL;
	अगर (cmd->base.duplex != DUPLEX_HALF && cmd->base.duplex != DUPLEX_FULL)
		वापस -EINVAL;

	अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE) अणु
		चयन (cmd->base.speed) अणु
		हाल SPEED_10:
			अगर (cmd->base.duplex == DUPLEX_HALF &&
			    !(f & SUPPORTED_10baseT_Half))
				वापस -EINVAL;
			अगर (cmd->base.duplex == DUPLEX_FULL &&
			    !(f & SUPPORTED_10baseT_Full))
				वापस -EINVAL;
			अवरोध;
		हाल SPEED_100:
			अगर (cmd->base.duplex == DUPLEX_HALF &&
			    !(f & SUPPORTED_100baseT_Half))
				वापस -EINVAL;
			अगर (cmd->base.duplex == DUPLEX_FULL &&
			    !(f & SUPPORTED_100baseT_Full))
				वापस -EINVAL;
			अवरोध;
		हाल SPEED_1000:
			अगर (cmd->base.duplex == DUPLEX_HALF &&
			    !(f & SUPPORTED_1000baseT_Half))
				वापस -EINVAL;
			अगर (cmd->base.duplex == DUPLEX_FULL &&
			    !(f & SUPPORTED_1000baseT_Full))
				वापस -EINVAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		mutex_lock(&dev->link_lock);
		dev->phy.def->ops->setup_क्रमced(&dev->phy, cmd->base.speed,
						cmd->base.duplex);
		mutex_unlock(&dev->link_lock);

	पूर्ण अन्यथा अणु
		अगर (!(f & SUPPORTED_Autoneg))
			वापस -EINVAL;

		mutex_lock(&dev->link_lock);
		dev->phy.def->ops->setup_aneg(&dev->phy,
					      (advertising & f) |
					      (dev->phy.advertising &
					       (ADVERTISED_Pause |
						ADVERTISED_Asym_Pause)));
		mutex_unlock(&dev->link_lock);
	पूर्ण
	emac_क्रमce_link_update(dev);

	वापस 0;
पूर्ण

अटल व्योम emac_ethtool_get_ringparam(काष्ठा net_device *ndev,
				       काष्ठा ethtool_ringparam *rp)
अणु
	rp->rx_max_pending = rp->rx_pending = NUM_RX_BUFF;
	rp->tx_max_pending = rp->tx_pending = NUM_TX_BUFF;
पूर्ण

अटल व्योम emac_ethtool_get_छोड़ोparam(काष्ठा net_device *ndev,
					काष्ठा ethtool_छोड़ोparam *pp)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	mutex_lock(&dev->link_lock);
	अगर ((dev->phy.features & SUPPORTED_Autoneg) &&
	    (dev->phy.advertising & (ADVERTISED_Pause | ADVERTISED_Asym_Pause)))
		pp->स्वतःneg = 1;

	अगर (dev->phy.duplex == DUPLEX_FULL) अणु
		अगर (dev->phy.छोड़ो)
			pp->rx_छोड़ो = pp->tx_छोड़ो = 1;
		अन्यथा अगर (dev->phy.asym_छोड़ो)
			pp->tx_छोड़ो = 1;
	पूर्ण
	mutex_unlock(&dev->link_lock);
पूर्ण

अटल पूर्णांक emac_get_regs_len(काष्ठा emac_instance *dev)
अणु
		वापस माप(काष्ठा emac_ethtool_regs_subhdr) +
			माप(काष्ठा emac_regs);
पूर्ण

अटल पूर्णांक emac_ethtool_get_regs_len(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	पूर्णांक size;

	size = माप(काष्ठा emac_ethtool_regs_hdr) +
		emac_get_regs_len(dev) + mal_get_regs_len(dev->mal);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII))
		size += zmii_get_regs_len(dev->zmii_dev);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII))
		size += rgmii_get_regs_len(dev->rgmii_dev);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_TAH))
		size += tah_get_regs_len(dev->tah_dev);

	वापस size;
पूर्ण

अटल व्योम *emac_dump_regs(काष्ठा emac_instance *dev, व्योम *buf)
अणु
	काष्ठा emac_ethtool_regs_subhdr *hdr = buf;

	hdr->index = dev->cell_index;
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4SYNC)) अणु
		hdr->version = EMAC4SYNC_ETHTOOL_REGS_VER;
	पूर्ण अन्यथा अगर (emac_has_feature(dev, EMAC_FTR_EMAC4)) अणु
		hdr->version = EMAC4_ETHTOOL_REGS_VER;
	पूर्ण अन्यथा अणु
		hdr->version = EMAC_ETHTOOL_REGS_VER;
	पूर्ण
	स_नकल_fromio(hdr + 1, dev->emacp, माप(काष्ठा emac_regs));
	वापस (व्योम *)(hdr + 1) + माप(काष्ठा emac_regs);
पूर्ण

अटल व्योम emac_ethtool_get_regs(काष्ठा net_device *ndev,
				  काष्ठा ethtool_regs *regs, व्योम *buf)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	काष्ठा emac_ethtool_regs_hdr *hdr = buf;

	hdr->components = 0;
	buf = hdr + 1;

	buf = mal_dump_regs(dev->mal, buf);
	buf = emac_dump_regs(dev, buf);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII)) अणु
		hdr->components |= EMAC_ETHTOOL_REGS_ZMII;
		buf = zmii_dump_regs(dev->zmii_dev, buf);
	पूर्ण
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII)) अणु
		hdr->components |= EMAC_ETHTOOL_REGS_RGMII;
		buf = rgmii_dump_regs(dev->rgmii_dev, buf);
	पूर्ण
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_TAH)) अणु
		hdr->components |= EMAC_ETHTOOL_REGS_TAH;
		buf = tah_dump_regs(dev->tah_dev, buf);
	पूर्ण
पूर्ण

अटल पूर्णांक emac_ethtool_nway_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	पूर्णांक res = 0;

	DBG(dev, "nway_reset" NL);

	अगर (dev->phy.address < 0)
		वापस -EOPNOTSUPP;

	mutex_lock(&dev->link_lock);
	अगर (!dev->phy.स्वतःneg) अणु
		res = -EINVAL;
		जाओ out;
	पूर्ण

	dev->phy.def->ops->setup_aneg(&dev->phy, dev->phy.advertising);
 out:
	mutex_unlock(&dev->link_lock);
	emac_क्रमce_link_update(dev);
	वापस res;
पूर्ण

अटल पूर्णांक emac_ethtool_get_sset_count(काष्ठा net_device *ndev, पूर्णांक stringset)
अणु
	अगर (stringset == ETH_SS_STATS)
		वापस EMAC_ETHTOOL_STATS_COUNT;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल व्योम emac_ethtool_get_strings(काष्ठा net_device *ndev, u32 stringset,
				     u8 * buf)
अणु
	अगर (stringset == ETH_SS_STATS)
		स_नकल(buf, &emac_stats_keys, माप(emac_stats_keys));
पूर्ण

अटल व्योम emac_ethtool_get_ethtool_stats(काष्ठा net_device *ndev,
					   काष्ठा ethtool_stats *estats,
					   u64 * पंचांगp_stats)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	स_नकल(पंचांगp_stats, &dev->stats, माप(dev->stats));
	पंचांगp_stats += माप(dev->stats) / माप(u64);
	स_नकल(पंचांगp_stats, &dev->estats, माप(dev->estats));
पूर्ण

अटल व्योम emac_ethtool_get_drvinfo(काष्ठा net_device *ndev,
				     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	strlcpy(info->driver, "ibm_emac", माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	snम_लिखो(info->bus_info, माप(info->bus_info), "PPC 4xx EMAC-%d %pOF",
		 dev->cell_index, dev->ofdev->dev.of_node);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops emac_ethtool_ops = अणु
	.get_drvinfo = emac_ethtool_get_drvinfo,

	.get_regs_len = emac_ethtool_get_regs_len,
	.get_regs = emac_ethtool_get_regs,

	.nway_reset = emac_ethtool_nway_reset,

	.get_ringparam = emac_ethtool_get_ringparam,
	.get_छोड़ोparam = emac_ethtool_get_छोड़ोparam,

	.get_strings = emac_ethtool_get_strings,
	.get_sset_count = emac_ethtool_get_sset_count,
	.get_ethtool_stats = emac_ethtool_get_ethtool_stats,

	.get_link = ethtool_op_get_link,
	.get_link_ksettings = emac_ethtool_get_link_ksettings,
	.set_link_ksettings = emac_ethtool_set_link_ksettings,
पूर्ण;

अटल पूर्णांक emac_ioctl(काष्ठा net_device *ndev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);

	DBG(dev, "ioctl %08x" NL, cmd);

	अगर (dev->phy.address < 0)
		वापस -EOPNOTSUPP;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = dev->phy.address;
		fallthrough;
	हाल SIOCGMIIREG:
		data->val_out = emac_mdio_पढ़ो(ndev, dev->phy.address,
					       data->reg_num);
		वापस 0;

	हाल SIOCSMIIREG:
		emac_mdio_ग_लिखो(ndev, dev->phy.address, data->reg_num,
				data->val_in);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

काष्ठा emac_depentry अणु
	u32			phandle;
	काष्ठा device_node	*node;
	काष्ठा platक्रमm_device	*ofdev;
	व्योम			*drvdata;
पूर्ण;

#घोषणा	EMAC_DEP_MAL_IDX	0
#घोषणा	EMAC_DEP_ZMII_IDX	1
#घोषणा	EMAC_DEP_RGMII_IDX	2
#घोषणा	EMAC_DEP_TAH_IDX	3
#घोषणा	EMAC_DEP_MDIO_IDX	4
#घोषणा	EMAC_DEP_PREV_IDX	5
#घोषणा	EMAC_DEP_COUNT		6

अटल पूर्णांक emac_check_deps(काष्ठा emac_instance *dev,
			   काष्ठा emac_depentry *deps)
अणु
	पूर्णांक i, there = 0;
	काष्ठा device_node *np;

	क्रम (i = 0; i < EMAC_DEP_COUNT; i++) अणु
		/* no dependency on that item, allright */
		अगर (deps[i].phandle == 0) अणु
			there++;
			जारी;
		पूर्ण
		/* special हाल क्रम blist as the dependency might go away */
		अगर (i == EMAC_DEP_PREV_IDX) अणु
			np = *(dev->blist - 1);
			अगर (np == शून्य) अणु
				deps[i].phandle = 0;
				there++;
				जारी;
			पूर्ण
			अगर (deps[i].node == शून्य)
				deps[i].node = of_node_get(np);
		पूर्ण
		अगर (deps[i].node == शून्य)
			deps[i].node = of_find_node_by_phandle(deps[i].phandle);
		अगर (deps[i].node == शून्य)
			जारी;
		अगर (deps[i].ofdev == शून्य)
			deps[i].ofdev = of_find_device_by_node(deps[i].node);
		अगर (deps[i].ofdev == शून्य)
			जारी;
		अगर (deps[i].drvdata == शून्य)
			deps[i].drvdata = platक्रमm_get_drvdata(deps[i].ofdev);
		अगर (deps[i].drvdata != शून्य)
			there++;
	पूर्ण
	वापस there == EMAC_DEP_COUNT;
पूर्ण

अटल व्योम emac_put_deps(काष्ठा emac_instance *dev)
अणु
	platक्रमm_device_put(dev->mal_dev);
	platक्रमm_device_put(dev->zmii_dev);
	platक्रमm_device_put(dev->rgmii_dev);
	platक्रमm_device_put(dev->mdio_dev);
	platक्रमm_device_put(dev->tah_dev);
पूर्ण

अटल पूर्णांक emac_of_bus_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			      व्योम *data)
अणु
	/* We are only पूर्णांकereted in device addition */
	अगर (action == BUS_NOTIFY_BOUND_DRIVER)
		wake_up_all(&emac_probe_रुको);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block emac_of_bus_notअगरier = अणु
	.notअगरier_call = emac_of_bus_notअगरy
पूर्ण;

अटल पूर्णांक emac_रुको_deps(काष्ठा emac_instance *dev)
अणु
	काष्ठा emac_depentry deps[EMAC_DEP_COUNT];
	पूर्णांक i, err;

	स_रखो(&deps, 0, माप(deps));

	deps[EMAC_DEP_MAL_IDX].phandle = dev->mal_ph;
	deps[EMAC_DEP_ZMII_IDX].phandle = dev->zmii_ph;
	deps[EMAC_DEP_RGMII_IDX].phandle = dev->rgmii_ph;
	अगर (dev->tah_ph)
		deps[EMAC_DEP_TAH_IDX].phandle = dev->tah_ph;
	अगर (dev->mdio_ph)
		deps[EMAC_DEP_MDIO_IDX].phandle = dev->mdio_ph;
	अगर (dev->blist && dev->blist > emac_boot_list)
		deps[EMAC_DEP_PREV_IDX].phandle = 0xffffffffu;
	bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type, &emac_of_bus_notअगरier);
	रुको_event_समयout(emac_probe_रुको,
			   emac_check_deps(dev, deps),
			   EMAC_PROBE_DEP_TIMEOUT);
	bus_unरेजिस्टर_notअगरier(&platक्रमm_bus_type, &emac_of_bus_notअगरier);
	err = emac_check_deps(dev, deps) ? 0 : -ENODEV;
	क्रम (i = 0; i < EMAC_DEP_COUNT; i++) अणु
		of_node_put(deps[i].node);
		अगर (err)
			platक्रमm_device_put(deps[i].ofdev);
	पूर्ण
	अगर (err == 0) अणु
		dev->mal_dev = deps[EMAC_DEP_MAL_IDX].ofdev;
		dev->zmii_dev = deps[EMAC_DEP_ZMII_IDX].ofdev;
		dev->rgmii_dev = deps[EMAC_DEP_RGMII_IDX].ofdev;
		dev->tah_dev = deps[EMAC_DEP_TAH_IDX].ofdev;
		dev->mdio_dev = deps[EMAC_DEP_MDIO_IDX].ofdev;
	पूर्ण
	platक्रमm_device_put(deps[EMAC_DEP_PREV_IDX].ofdev);
	वापस err;
पूर्ण

अटल पूर्णांक emac_पढ़ो_uपूर्णांक_prop(काष्ठा device_node *np, स्थिर अक्षर *name,
			       u32 *val, पूर्णांक fatal)
अणु
	पूर्णांक len;
	स्थिर u32 *prop = of_get_property(np, name, &len);
	अगर (prop == शून्य || len < माप(u32)) अणु
		अगर (fatal)
			prपूर्णांकk(KERN_ERR "%pOF: missing %s property\n",
			       np, name);
		वापस -ENODEV;
	पूर्ण
	*val = *prop;
	वापस 0;
पूर्ण

अटल व्योम emac_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	काष्ठा phy_device *phy = dev->phy_dev;

	dev->phy.स्वतःneg = phy->स्वतःneg;
	dev->phy.speed = phy->speed;
	dev->phy.duplex = phy->duplex;
	dev->phy.छोड़ो = phy->छोड़ो;
	dev->phy.asym_छोड़ो = phy->asym_छोड़ो;
	ethtool_convert_link_mode_to_legacy_u32(&dev->phy.advertising,
						phy->advertising);
पूर्ण

अटल पूर्णांक emac_mii_bus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum)
अणु
	पूर्णांक ret = emac_mdio_पढ़ो(bus->priv, addr, regnum);
	/* This is a workaround क्रम घातered करोwn ports/phys.
	 * In the wild, this was seen on the Cisco Meraki MX60(W).
	 * This hardware disables ports as part of the hanकरोff
	 * procedure. Accessing the ports will lead to errors
	 * (-ETIMEDOUT, -EREMOTEIO) that करो more harm than good.
	 */
	वापस ret < 0 ? 0xffff : ret;
पूर्ण

अटल पूर्णांक emac_mii_bus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr,
			      पूर्णांक regnum, u16 val)
अणु
	emac_mdio_ग_लिखो(bus->priv, addr, regnum, val);
	वापस 0;
पूर्ण

अटल पूर्णांक emac_mii_bus_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा emac_instance *dev = netdev_priv(bus->priv);

	वापस emac_reset(dev);
पूर्ण

अटल पूर्णांक emac_mdio_phy_start_aneg(काष्ठा mii_phy *phy,
				    काष्ठा phy_device *phy_dev)
अणु
	phy_dev->स्वतःneg = phy->स्वतःneg;
	phy_dev->speed = phy->speed;
	phy_dev->duplex = phy->duplex;
	ethtool_convert_legacy_u32_to_link_mode(phy_dev->advertising,
						phy->advertising);
	वापस phy_start_aneg(phy_dev);
पूर्ण

अटल पूर्णांक emac_mdio_setup_aneg(काष्ठा mii_phy *phy, u32 advertise)
अणु
	काष्ठा net_device *ndev = phy->dev;
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	phy->स्वतःneg = AUTONEG_ENABLE;
	phy->advertising = advertise;
	वापस emac_mdio_phy_start_aneg(phy, dev->phy_dev);
पूर्ण

अटल पूर्णांक emac_mdio_setup_क्रमced(काष्ठा mii_phy *phy, पूर्णांक speed, पूर्णांक fd)
अणु
	काष्ठा net_device *ndev = phy->dev;
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	phy->स्वतःneg = AUTONEG_DISABLE;
	phy->speed = speed;
	phy->duplex = fd;
	वापस emac_mdio_phy_start_aneg(phy, dev->phy_dev);
पूर्ण

अटल पूर्णांक emac_mdio_poll_link(काष्ठा mii_phy *phy)
अणु
	काष्ठा net_device *ndev = phy->dev;
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	पूर्णांक res;

	res = phy_पढ़ो_status(dev->phy_dev);
	अगर (res) अणु
		dev_err(&dev->ofdev->dev, "link update failed (%d).", res);
		वापस ethtool_op_get_link(ndev);
	पूर्ण

	वापस dev->phy_dev->link;
पूर्ण

अटल पूर्णांक emac_mdio_पढ़ो_link(काष्ठा mii_phy *phy)
अणु
	काष्ठा net_device *ndev = phy->dev;
	काष्ठा emac_instance *dev = netdev_priv(ndev);
	काष्ठा phy_device *phy_dev = dev->phy_dev;
	पूर्णांक res;

	res = phy_पढ़ो_status(phy_dev);
	अगर (res)
		वापस res;

	phy->speed = phy_dev->speed;
	phy->duplex = phy_dev->duplex;
	phy->छोड़ो = phy_dev->छोड़ो;
	phy->asym_छोड़ो = phy_dev->asym_छोड़ो;
	वापस 0;
पूर्ण

अटल पूर्णांक emac_mdio_init_phy(काष्ठा mii_phy *phy)
अणु
	काष्ठा net_device *ndev = phy->dev;
	काष्ठा emac_instance *dev = netdev_priv(ndev);

	phy_start(dev->phy_dev);
	वापस phy_init_hw(dev->phy_dev);
पूर्ण

अटल स्थिर काष्ठा mii_phy_ops emac_dt_mdio_phy_ops = अणु
	.init		= emac_mdio_init_phy,
	.setup_aneg	= emac_mdio_setup_aneg,
	.setup_क्रमced	= emac_mdio_setup_क्रमced,
	.poll_link	= emac_mdio_poll_link,
	.पढ़ो_link	= emac_mdio_पढ़ो_link,
पूर्ण;

अटल पूर्णांक emac_dt_mdio_probe(काष्ठा emac_instance *dev)
अणु
	काष्ठा device_node *mii_np;
	पूर्णांक res;

	mii_np = of_get_child_by_name(dev->ofdev->dev.of_node, "mdio");
	अगर (!mii_np) अणु
		dev_err(&dev->ofdev->dev, "no mdio definition found.");
		वापस -ENODEV;
	पूर्ण

	अगर (!of_device_is_available(mii_np)) अणु
		res = -ENODEV;
		जाओ put_node;
	पूर्ण

	dev->mii_bus = devm_mdiobus_alloc(&dev->ofdev->dev);
	अगर (!dev->mii_bus) अणु
		res = -ENOMEM;
		जाओ put_node;
	पूर्ण

	dev->mii_bus->priv = dev->ndev;
	dev->mii_bus->parent = dev->ndev->dev.parent;
	dev->mii_bus->name = "emac_mdio";
	dev->mii_bus->पढ़ो = &emac_mii_bus_पढ़ो;
	dev->mii_bus->ग_लिखो = &emac_mii_bus_ग_लिखो;
	dev->mii_bus->reset = &emac_mii_bus_reset;
	snम_लिखो(dev->mii_bus->id, MII_BUS_ID_SIZE, "%s", dev->ofdev->name);
	res = of_mdiobus_रेजिस्टर(dev->mii_bus, mii_np);
	अगर (res) अणु
		dev_err(&dev->ofdev->dev, "cannot register MDIO bus %s (%d)",
			dev->mii_bus->name, res);
	पूर्ण

 put_node:
	of_node_put(mii_np);
	वापस res;
पूर्ण

अटल पूर्णांक emac_dt_phy_connect(काष्ठा emac_instance *dev,
			       काष्ठा device_node *phy_handle)
अणु
	dev->phy.def = devm_kzalloc(&dev->ofdev->dev, माप(*dev->phy.def),
				    GFP_KERNEL);
	अगर (!dev->phy.def)
		वापस -ENOMEM;

	dev->phy_dev = of_phy_connect(dev->ndev, phy_handle, &emac_adjust_link,
				      0, dev->phy_mode);
	अगर (!dev->phy_dev) अणु
		dev_err(&dev->ofdev->dev, "failed to connect to PHY.\n");
		वापस -ENODEV;
	पूर्ण

	dev->phy.def->phy_id = dev->phy_dev->drv->phy_id;
	dev->phy.def->phy_id_mask = dev->phy_dev->drv->phy_id_mask;
	dev->phy.def->name = dev->phy_dev->drv->name;
	dev->phy.def->ops = &emac_dt_mdio_phy_ops;
	ethtool_convert_link_mode_to_legacy_u32(&dev->phy.features,
						dev->phy_dev->supported);
	dev->phy.address = dev->phy_dev->mdio.addr;
	dev->phy.mode = dev->phy_dev->पूर्णांकerface;
	वापस 0;
पूर्ण

अटल पूर्णांक emac_dt_phy_probe(काष्ठा emac_instance *dev)
अणु
	काष्ठा device_node *np = dev->ofdev->dev.of_node;
	काष्ठा device_node *phy_handle;
	पूर्णांक res = 1;

	phy_handle = of_parse_phandle(np, "phy-handle", 0);

	अगर (phy_handle) अणु
		res = emac_dt_mdio_probe(dev);
		अगर (!res) अणु
			res = emac_dt_phy_connect(dev, phy_handle);
			अगर (res)
				mdiobus_unरेजिस्टर(dev->mii_bus);
		पूर्ण
	पूर्ण

	of_node_put(phy_handle);
	वापस res;
पूर्ण

अटल पूर्णांक emac_init_phy(काष्ठा emac_instance *dev)
अणु
	काष्ठा device_node *np = dev->ofdev->dev.of_node;
	काष्ठा net_device *ndev = dev->ndev;
	u32 phy_map, adv;
	पूर्णांक i;

	dev->phy.dev = ndev;
	dev->phy.mode = dev->phy_mode;

	/* PHY-less configuration. */
	अगर ((dev->phy_address == 0xffffffff && dev->phy_map == 0xffffffff) ||
	    of_phy_is_fixed_link(np)) अणु
		emac_reset(dev);

		/* PHY-less configuration. */
		dev->phy.address = -1;
		dev->phy.features = SUPPORTED_MII;
		अगर (emac_phy_supports_gige(dev->phy_mode))
			dev->phy.features |= SUPPORTED_1000baseT_Full;
		अन्यथा
			dev->phy.features |= SUPPORTED_100baseT_Full;
		dev->phy.छोड़ो = 1;

		अगर (of_phy_is_fixed_link(np)) अणु
			पूर्णांक res = emac_dt_mdio_probe(dev);

			अगर (res)
				वापस res;

			res = of_phy_रेजिस्टर_fixed_link(np);
			dev->phy_dev = of_phy_find_device(np);
			अगर (res || !dev->phy_dev) अणु
				mdiobus_unरेजिस्टर(dev->mii_bus);
				वापस res ? res : -EINVAL;
			पूर्ण
			emac_adjust_link(dev->ndev);
			put_device(&dev->phy_dev->mdio.dev);
		पूर्ण
		वापस 0;
	पूर्ण

	mutex_lock(&emac_phy_map_lock);
	phy_map = dev->phy_map | busy_phy_map;

	DBG(dev, "PHY maps %08x %08x" NL, dev->phy_map, busy_phy_map);

	dev->phy.mdio_पढ़ो = emac_mdio_पढ़ो;
	dev->phy.mdio_ग_लिखो = emac_mdio_ग_लिखो;

	/* Enable पूर्णांकernal घड़ी source */
#अगर_घोषित CONFIG_PPC_DCR_NATIVE
	अगर (emac_has_feature(dev, EMAC_FTR_440GX_PHY_CLK_FIX))
		dcri_clrset(SDR0, SDR0_MFR, 0, SDR0_MFR_ECS);
#पूर्ण_अगर
	/* PHY घड़ी workaround */
	emac_rx_clk_tx(dev);

	/* Enable पूर्णांकernal घड़ी source on 440GX*/
#अगर_घोषित CONFIG_PPC_DCR_NATIVE
	अगर (emac_has_feature(dev, EMAC_FTR_440GX_PHY_CLK_FIX))
		dcri_clrset(SDR0, SDR0_MFR, 0, SDR0_MFR_ECS);
#पूर्ण_अगर
	/* Configure EMAC with शेषs so we can at least use MDIO
	 * This is needed mostly क्रम 440GX
	 */
	अगर (emac_phy_gpcs(dev->phy.mode)) अणु
		/* XXX
		 * Make GPCS PHY address equal to EMAC index.
		 * We probably should take पूर्णांकo account busy_phy_map
		 * and/or phy_map here.
		 *
		 * Note that the busy_phy_map is currently global
		 * जबतक it should probably be per-ASIC...
		 */
		dev->phy.gpcs_address = dev->gpcs_address;
		अगर (dev->phy.gpcs_address == 0xffffffff)
			dev->phy.address = dev->cell_index;
	पूर्ण

	emac_configure(dev);

	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII)) अणु
		पूर्णांक res = emac_dt_phy_probe(dev);

		चयन (res) अणु
		हाल 1:
			/* No phy-handle property configured.
			 * Continue with the existing phy probe
			 * and setup code.
			 */
			अवरोध;

		हाल 0:
			mutex_unlock(&emac_phy_map_lock);
			जाओ init_phy;

		शेष:
			mutex_unlock(&emac_phy_map_lock);
			dev_err(&dev->ofdev->dev, "failed to attach dt phy (%d).\n",
				res);
			वापस res;
		पूर्ण
	पूर्ण

	अगर (dev->phy_address != 0xffffffff)
		phy_map = ~(1 << dev->phy_address);

	क्रम (i = 0; i < 0x20; phy_map >>= 1, ++i)
		अगर (!(phy_map & 1)) अणु
			पूर्णांक r;
			busy_phy_map |= 1 << i;

			/* Quick check अगर there is a PHY at the address */
			r = emac_mdio_पढ़ो(dev->ndev, i, MII_BMCR);
			अगर (r == 0xffff || r < 0)
				जारी;
			अगर (!emac_mii_phy_probe(&dev->phy, i))
				अवरोध;
		पूर्ण

	/* Enable बाह्यal घड़ी source */
#अगर_घोषित CONFIG_PPC_DCR_NATIVE
	अगर (emac_has_feature(dev, EMAC_FTR_440GX_PHY_CLK_FIX))
		dcri_clrset(SDR0, SDR0_MFR, SDR0_MFR_ECS, 0);
#पूर्ण_अगर
	mutex_unlock(&emac_phy_map_lock);
	अगर (i == 0x20) अणु
		prपूर्णांकk(KERN_WARNING "%pOF: can't find PHY!\n", np);
		वापस -ENXIO;
	पूर्ण

 init_phy:
	/* Init PHY */
	अगर (dev->phy.def->ops->init)
		dev->phy.def->ops->init(&dev->phy);

	/* Disable any PHY features not supported by the platक्रमm */
	dev->phy.def->features &= ~dev->phy_feat_exc;
	dev->phy.features &= ~dev->phy_feat_exc;

	/* Setup initial link parameters */
	अगर (dev->phy.features & SUPPORTED_Autoneg) अणु
		adv = dev->phy.features;
		अगर (!emac_has_feature(dev, EMAC_FTR_NO_FLOW_CONTROL_40x))
			adv |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;
		/* Restart स्वतःnegotiation */
		dev->phy.def->ops->setup_aneg(&dev->phy, adv);
	पूर्ण अन्यथा अणु
		u32 f = dev->phy.def->features;
		पूर्णांक speed = SPEED_10, fd = DUPLEX_HALF;

		/* Select highest supported speed/duplex */
		अगर (f & SUPPORTED_1000baseT_Full) अणु
			speed = SPEED_1000;
			fd = DUPLEX_FULL;
		पूर्ण अन्यथा अगर (f & SUPPORTED_1000baseT_Half)
			speed = SPEED_1000;
		अन्यथा अगर (f & SUPPORTED_100baseT_Full) अणु
			speed = SPEED_100;
			fd = DUPLEX_FULL;
		पूर्ण अन्यथा अगर (f & SUPPORTED_100baseT_Half)
			speed = SPEED_100;
		अन्यथा अगर (f & SUPPORTED_10baseT_Full)
			fd = DUPLEX_FULL;

		/* Force link parameters */
		dev->phy.def->ops->setup_क्रमced(&dev->phy, speed, fd);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक emac_init_config(काष्ठा emac_instance *dev)
अणु
	काष्ठा device_node *np = dev->ofdev->dev.of_node;
	स्थिर व्योम *p;
	पूर्णांक err;

	/* Read config from device-tree */
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "mal-device", &dev->mal_ph, 1))
		वापस -ENXIO;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "mal-tx-channel", &dev->mal_tx_chan, 1))
		वापस -ENXIO;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "mal-rx-channel", &dev->mal_rx_chan, 1))
		वापस -ENXIO;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "cell-index", &dev->cell_index, 1))
		वापस -ENXIO;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "max-frame-size", &dev->max_mtu, 0))
		dev->max_mtu = ETH_DATA_LEN;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "rx-fifo-size", &dev->rx_fअगरo_size, 0))
		dev->rx_fअगरo_size = 2048;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "tx-fifo-size", &dev->tx_fअगरo_size, 0))
		dev->tx_fअगरo_size = 2048;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "rx-fifo-size-gige", &dev->rx_fअगरo_size_gige, 0))
		dev->rx_fअगरo_size_gige = dev->rx_fअगरo_size;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "tx-fifo-size-gige", &dev->tx_fअगरo_size_gige, 0))
		dev->tx_fअगरo_size_gige = dev->tx_fअगरo_size;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "phy-address", &dev->phy_address, 0))
		dev->phy_address = 0xffffffff;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "phy-map", &dev->phy_map, 0))
		dev->phy_map = 0xffffffff;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "gpcs-address", &dev->gpcs_address, 0))
		dev->gpcs_address = 0xffffffff;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np->parent, "clock-frequency", &dev->opb_bus_freq, 1))
		वापस -ENXIO;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "tah-device", &dev->tah_ph, 0))
		dev->tah_ph = 0;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "tah-channel", &dev->tah_port, 0))
		dev->tah_port = 0;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "mdio-device", &dev->mdio_ph, 0))
		dev->mdio_ph = 0;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "zmii-device", &dev->zmii_ph, 0))
		dev->zmii_ph = 0;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "zmii-channel", &dev->zmii_port, 0))
		dev->zmii_port = 0xffffffff;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "rgmii-device", &dev->rgmii_ph, 0))
		dev->rgmii_ph = 0;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "rgmii-channel", &dev->rgmii_port, 0))
		dev->rgmii_port = 0xffffffff;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "fifo-entry-size", &dev->fअगरo_entry_size, 0))
		dev->fअगरo_entry_size = 16;
	अगर (emac_पढ़ो_uपूर्णांक_prop(np, "mal-burst-size", &dev->mal_burst_size, 0))
		dev->mal_burst_size = 256;

	/* PHY mode needs some decoding */
	err = of_get_phy_mode(np, &dev->phy_mode);
	अगर (err)
		dev->phy_mode = PHY_INTERFACE_MODE_NA;

	/* Check EMAC version */
	अगर (of_device_is_compatible(np, "ibm,emac4sync")) अणु
		dev->features |= (EMAC_FTR_EMAC4 | EMAC_FTR_EMAC4SYNC);
		अगर (of_device_is_compatible(np, "ibm,emac-460ex") ||
		    of_device_is_compatible(np, "ibm,emac-460gt"))
			dev->features |= EMAC_FTR_460EX_PHY_CLK_FIX;
		अगर (of_device_is_compatible(np, "ibm,emac-405ex") ||
		    of_device_is_compatible(np, "ibm,emac-405exr"))
			dev->features |= EMAC_FTR_440EP_PHY_CLK_FIX;
		अगर (of_device_is_compatible(np, "ibm,emac-apm821xx")) अणु
			dev->features |= (EMAC_APM821XX_REQ_JUMBO_FRAME_SIZE |
					  EMAC_FTR_APM821XX_NO_HALF_DUPLEX |
					  EMAC_FTR_460EX_PHY_CLK_FIX);
		पूर्ण
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "ibm,emac4")) अणु
		dev->features |= EMAC_FTR_EMAC4;
		अगर (of_device_is_compatible(np, "ibm,emac-440gx"))
			dev->features |= EMAC_FTR_440GX_PHY_CLK_FIX;
	पूर्ण अन्यथा अणु
		अगर (of_device_is_compatible(np, "ibm,emac-440ep") ||
		    of_device_is_compatible(np, "ibm,emac-440gr"))
			dev->features |= EMAC_FTR_440EP_PHY_CLK_FIX;
		अगर (of_device_is_compatible(np, "ibm,emac-405ez")) अणु
#अगर_घोषित CONFIG_IBM_EMAC_NO_FLOW_CTRL
			dev->features |= EMAC_FTR_NO_FLOW_CONTROL_40x;
#अन्यथा
			prपूर्णांकk(KERN_ERR "%pOF: Flow control not disabled!\n",
					np);
			वापस -ENXIO;
#पूर्ण_अगर
		पूर्ण

	पूर्ण

	/* Fixup some feature bits based on the device tree */
	अगर (of_get_property(np, "has-inverted-stacr-oc", शून्य))
		dev->features |= EMAC_FTR_STACR_OC_INVERT;
	अगर (of_get_property(np, "has-new-stacr-staopc", शून्य))
		dev->features |= EMAC_FTR_HAS_NEW_STACR;

	/* CAB lacks the appropriate properties */
	अगर (of_device_is_compatible(np, "ibm,emac-axon"))
		dev->features |= EMAC_FTR_HAS_NEW_STACR |
			EMAC_FTR_STACR_OC_INVERT;

	/* Enable TAH/ZMII/RGMII features as found */
	अगर (dev->tah_ph != 0) अणु
#अगर_घोषित CONFIG_IBM_EMAC_TAH
		dev->features |= EMAC_FTR_HAS_TAH;
#अन्यथा
		prपूर्णांकk(KERN_ERR "%pOF: TAH support not enabled !\n", np);
		वापस -ENXIO;
#पूर्ण_अगर
	पूर्ण

	अगर (dev->zmii_ph != 0) अणु
#अगर_घोषित CONFIG_IBM_EMAC_ZMII
		dev->features |= EMAC_FTR_HAS_ZMII;
#अन्यथा
		prपूर्णांकk(KERN_ERR "%pOF: ZMII support not enabled !\n", np);
		वापस -ENXIO;
#पूर्ण_अगर
	पूर्ण

	अगर (dev->rgmii_ph != 0) अणु
#अगर_घोषित CONFIG_IBM_EMAC_RGMII
		dev->features |= EMAC_FTR_HAS_RGMII;
#अन्यथा
		prपूर्णांकk(KERN_ERR "%pOF: RGMII support not enabled !\n", np);
		वापस -ENXIO;
#पूर्ण_अगर
	पूर्ण

	/* Read MAC-address */
	p = of_get_property(np, "local-mac-address", शून्य);
	अगर (p == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't find local-mac-address property\n",
		       np);
		वापस -ENXIO;
	पूर्ण
	स_नकल(dev->ndev->dev_addr, p, ETH_ALEN);

	/* IAHT and GAHT filter parameterization */
	अगर (emac_has_feature(dev, EMAC_FTR_EMAC4SYNC)) अणु
		dev->xaht_slots_shअगरt = EMAC4SYNC_XAHT_SLOTS_SHIFT;
		dev->xaht_width_shअगरt = EMAC4SYNC_XAHT_WIDTH_SHIFT;
	पूर्ण अन्यथा अणु
		dev->xaht_slots_shअगरt = EMAC4_XAHT_SLOTS_SHIFT;
		dev->xaht_width_shअगरt = EMAC4_XAHT_WIDTH_SHIFT;
	पूर्ण

	/* This should never happen */
	अगर (WARN_ON(EMAC_XAHT_REGS(dev) > EMAC_XAHT_MAX_REGS))
		वापस -ENXIO;

	DBG(dev, "features     : 0x%08x / 0x%08x\n", dev->features, EMAC_FTRS_POSSIBLE);
	DBG(dev, "tx_fifo_size : %d (%d gige)\n", dev->tx_fअगरo_size, dev->tx_fअगरo_size_gige);
	DBG(dev, "rx_fifo_size : %d (%d gige)\n", dev->rx_fअगरo_size, dev->rx_fअगरo_size_gige);
	DBG(dev, "max_mtu      : %d\n", dev->max_mtu);
	DBG(dev, "OPB freq     : %d\n", dev->opb_bus_freq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops emac_netdev_ops = अणु
	.nकरो_खोलो		= emac_खोलो,
	.nकरो_stop		= emac_बंद,
	.nकरो_get_stats		= emac_stats,
	.nकरो_set_rx_mode	= emac_set_multicast_list,
	.nकरो_करो_ioctl		= emac_ioctl,
	.nकरो_tx_समयout		= emac_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= emac_set_mac_address,
	.nकरो_start_xmit		= emac_start_xmit,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops emac_gige_netdev_ops = अणु
	.nकरो_खोलो		= emac_खोलो,
	.nकरो_stop		= emac_बंद,
	.nकरो_get_stats		= emac_stats,
	.nकरो_set_rx_mode	= emac_set_multicast_list,
	.nकरो_करो_ioctl		= emac_ioctl,
	.nकरो_tx_समयout		= emac_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= emac_set_mac_address,
	.nकरो_start_xmit		= emac_start_xmit_sg,
	.nकरो_change_mtu		= emac_change_mtu,
पूर्ण;

अटल पूर्णांक emac_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा net_device *ndev;
	काष्ठा emac_instance *dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा device_node **blist = शून्य;
	पूर्णांक err, i;

	/* Skip unused/unwired EMACS.  We leave the check क्रम an unused
	 * property here क्रम now, but new flat device trees should set a
	 * status property to "disabled" instead.
	 */
	अगर (of_get_property(np, "unused", शून्य) || !of_device_is_available(np))
		वापस -ENODEV;

	/* Find ourselves in the bootlist अगर we are there */
	क्रम (i = 0; i < EMAC_BOOT_LIST_SIZE; i++)
		अगर (emac_boot_list[i] == np)
			blist = &emac_boot_list[i];

	/* Allocate our net_device काष्ठाure */
	err = -ENOMEM;
	ndev = alloc_etherdev(माप(काष्ठा emac_instance));
	अगर (!ndev)
		जाओ err_gone;

	dev = netdev_priv(ndev);
	dev->ndev = ndev;
	dev->ofdev = ofdev;
	dev->blist = blist;
	SET_NETDEV_DEV(ndev, &ofdev->dev);

	/* Initialize some embedded data काष्ठाures */
	mutex_init(&dev->mdio_lock);
	mutex_init(&dev->link_lock);
	spin_lock_init(&dev->lock);
	INIT_WORK(&dev->reset_work, emac_reset_work);

	/* Init various config data based on device-tree */
	err = emac_init_config(dev);
	अगर (err)
		जाओ err_मुक्त;

	/* Get पूर्णांकerrupts. EMAC irq is mandatory, WOL irq is optional */
	dev->emac_irq = irq_of_parse_and_map(np, 0);
	dev->wol_irq = irq_of_parse_and_map(np, 1);
	अगर (!dev->emac_irq) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't map main interrupt\n", np);
		err = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण
	ndev->irq = dev->emac_irq;

	/* Map EMAC regs */
	// TODO : platक्रमm_get_resource() and devm_ioremap_resource()
	dev->emacp = of_iomap(np, 0);
	अगर (dev->emacp == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't map device registers!\n", np);
		err = -ENOMEM;
		जाओ err_irq_unmap;
	पूर्ण

	/* Wait क्रम dependent devices */
	err = emac_रुको_deps(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR
		       "%pOF: Timeout waiting for dependent devices\n", np);
		/*  display more info about what's missing ? */
		जाओ err_reg_unmap;
	पूर्ण
	dev->mal = platक्रमm_get_drvdata(dev->mal_dev);
	अगर (dev->mdio_dev != शून्य)
		dev->mdio_instance = platक्रमm_get_drvdata(dev->mdio_dev);

	/* Register with MAL */
	dev->commac.ops = &emac_commac_ops;
	dev->commac.dev = dev;
	dev->commac.tx_chan_mask = MAL_CHAN_MASK(dev->mal_tx_chan);
	dev->commac.rx_chan_mask = MAL_CHAN_MASK(dev->mal_rx_chan);
	err = mal_रेजिस्टर_commac(dev->mal, &dev->commac);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%pOF: failed to register with mal %pOF!\n",
		       np, dev->mal_dev->dev.of_node);
		जाओ err_rel_deps;
	पूर्ण
	dev->rx_skb_size = emac_rx_skb_size(ndev->mtu);
	dev->rx_sync_size = emac_rx_sync_size(ndev->mtu);

	/* Get poपूर्णांकers to BD rings */
	dev->tx_desc =
	    dev->mal->bd_virt + mal_tx_bd_offset(dev->mal, dev->mal_tx_chan);
	dev->rx_desc =
	    dev->mal->bd_virt + mal_rx_bd_offset(dev->mal, dev->mal_rx_chan);

	DBG(dev, "tx_desc %p" NL, dev->tx_desc);
	DBG(dev, "rx_desc %p" NL, dev->rx_desc);

	/* Clean rings */
	स_रखो(dev->tx_desc, 0, NUM_TX_BUFF * माप(काष्ठा mal_descriptor));
	स_रखो(dev->rx_desc, 0, NUM_RX_BUFF * माप(काष्ठा mal_descriptor));
	स_रखो(dev->tx_skb, 0, NUM_TX_BUFF * माप(काष्ठा sk_buff *));
	स_रखो(dev->rx_skb, 0, NUM_RX_BUFF * माप(काष्ठा sk_buff *));

	/* Attach to ZMII, अगर needed */
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII) &&
	    (err = zmii_attach(dev->zmii_dev, dev->zmii_port, &dev->phy_mode)) != 0)
		जाओ err_unreg_commac;

	/* Attach to RGMII, अगर needed */
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII) &&
	    (err = rgmii_attach(dev->rgmii_dev, dev->rgmii_port, dev->phy_mode)) != 0)
		जाओ err_detach_zmii;

	/* Attach to TAH, अगर needed */
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_TAH) &&
	    (err = tah_attach(dev->tah_dev, dev->tah_port)) != 0)
		जाओ err_detach_rgmii;

	/* Set some link शेषs beक्रमe we can find out real parameters */
	dev->phy.speed = SPEED_100;
	dev->phy.duplex = DUPLEX_FULL;
	dev->phy.स्वतःneg = AUTONEG_DISABLE;
	dev->phy.छोड़ो = dev->phy.asym_छोड़ो = 0;
	dev->stop_समयout = STOP_TIMEOUT_100;
	INIT_DELAYED_WORK(&dev->link_work, emac_link_समयr);

	/* Some SoCs like APM821xx करोes not support Half Duplex mode. */
	अगर (emac_has_feature(dev, EMAC_FTR_APM821XX_NO_HALF_DUPLEX)) अणु
		dev->phy_feat_exc = (SUPPORTED_1000baseT_Half |
				     SUPPORTED_100baseT_Half |
				     SUPPORTED_10baseT_Half);
	पूर्ण

	/* Find PHY अगर any */
	err = emac_init_phy(dev);
	अगर (err != 0)
		जाओ err_detach_tah;

	अगर (dev->tah_dev) अणु
		ndev->hw_features = NETIF_F_IP_CSUM | NETIF_F_SG;
		ndev->features |= ndev->hw_features | NETIF_F_RXCSUM;
	पूर्ण
	ndev->watchकरोg_समयo = 5 * HZ;
	अगर (emac_phy_supports_gige(dev->phy_mode)) अणु
		ndev->netdev_ops = &emac_gige_netdev_ops;
		dev->commac.ops = &emac_commac_sg_ops;
	पूर्ण अन्यथा
		ndev->netdev_ops = &emac_netdev_ops;
	ndev->ethtool_ops = &emac_ethtool_ops;

	/* MTU range: 46 - 1500 or whatever is in OF */
	ndev->min_mtu = EMAC_MIN_MTU;
	ndev->max_mtu = dev->max_mtu;

	netअगर_carrier_off(ndev);

	err = रेजिस्टर_netdev(ndev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "%pOF: failed to register net device (%d)!\n",
		       np, err);
		जाओ err_detach_tah;
	पूर्ण

	/* Set our drvdata last as we करोn't want them visible until we are
	 * fully initialized
	 */
	wmb();
	platक्रमm_set_drvdata(ofdev, dev);

	/* There's a new kid in town ! Let's tell everybody */
	wake_up_all(&emac_probe_रुको);


	prपूर्णांकk(KERN_INFO "%s: EMAC-%d %pOF, MAC %pM\n",
	       ndev->name, dev->cell_index, np, ndev->dev_addr);

	अगर (dev->phy_mode == PHY_INTERFACE_MODE_SGMII)
		prपूर्णांकk(KERN_NOTICE "%s: in SGMII mode\n", ndev->name);

	अगर (dev->phy.address >= 0)
		prपूर्णांकk("%s: found %s PHY (0x%02x)\n", ndev->name,
		       dev->phy.def->name, dev->phy.address);

	/* Lअगरe is good */
	वापस 0;

	/* I have a bad feeling about this ... */

 err_detach_tah:
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_TAH))
		tah_detach(dev->tah_dev, dev->tah_port);
 err_detach_rgmii:
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII))
		rgmii_detach(dev->rgmii_dev, dev->rgmii_port);
 err_detach_zmii:
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII))
		zmii_detach(dev->zmii_dev, dev->zmii_port);
 err_unreg_commac:
	mal_unरेजिस्टर_commac(dev->mal, &dev->commac);
 err_rel_deps:
	emac_put_deps(dev);
 err_reg_unmap:
	iounmap(dev->emacp);
 err_irq_unmap:
	अगर (dev->wol_irq)
		irq_dispose_mapping(dev->wol_irq);
	अगर (dev->emac_irq)
		irq_dispose_mapping(dev->emac_irq);
 err_मुक्त:
	मुक्त_netdev(ndev);
 err_gone:
	/* अगर we were on the bootlist, हटाओ us as we won't show up and
	 * wake up all रुकोers to notअगरy them in हाल they were रुकोing
	 * on us
	 */
	अगर (blist) अणु
		*blist = शून्य;
		wake_up_all(&emac_probe_रुको);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक emac_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा emac_instance *dev = platक्रमm_get_drvdata(ofdev);

	DBG(dev, "remove" NL);

	unरेजिस्टर_netdev(dev->ndev);

	cancel_work_sync(&dev->reset_work);

	अगर (emac_has_feature(dev, EMAC_FTR_HAS_TAH))
		tah_detach(dev->tah_dev, dev->tah_port);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_RGMII))
		rgmii_detach(dev->rgmii_dev, dev->rgmii_port);
	अगर (emac_has_feature(dev, EMAC_FTR_HAS_ZMII))
		zmii_detach(dev->zmii_dev, dev->zmii_port);

	अगर (dev->phy_dev)
		phy_disconnect(dev->phy_dev);

	अगर (dev->mii_bus)
		mdiobus_unरेजिस्टर(dev->mii_bus);

	busy_phy_map &= ~(1 << dev->phy.address);
	DBG(dev, "busy_phy_map now %#x" NL, busy_phy_map);

	mal_unरेजिस्टर_commac(dev->mal, &dev->commac);
	emac_put_deps(dev);

	iounmap(dev->emacp);

	अगर (dev->wol_irq)
		irq_dispose_mapping(dev->wol_irq);
	अगर (dev->emac_irq)
		irq_dispose_mapping(dev->emac_irq);

	मुक्त_netdev(dev->ndev);

	वापस 0;
पूर्ण

/* XXX Features in here should be replaced by properties... */
अटल स्थिर काष्ठा of_device_id emac_match[] =
अणु
	अणु
		.type		= "network",
		.compatible	= "ibm,emac",
	पूर्ण,
	अणु
		.type		= "network",
		.compatible	= "ibm,emac4",
	पूर्ण,
	अणु
		.type		= "network",
		.compatible	= "ibm,emac4sync",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, emac_match);

अटल काष्ठा platक्रमm_driver emac_driver = अणु
	.driver = अणु
		.name = "emac",
		.of_match_table = emac_match,
	पूर्ण,
	.probe = emac_probe,
	.हटाओ = emac_हटाओ,
पूर्ण;

अटल व्योम __init emac_make_bootlist(व्योम)
अणु
	काष्ठा device_node *np = शून्य;
	पूर्णांक j, max, i = 0;
	पूर्णांक cell_indices[EMAC_BOOT_LIST_SIZE];

	/* Collect EMACs */
	जबतक((np = of_find_all_nodes(np)) != शून्य) अणु
		स्थिर u32 *idx;

		अगर (of_match_node(emac_match, np) == शून्य)
			जारी;
		अगर (of_get_property(np, "unused", शून्य))
			जारी;
		idx = of_get_property(np, "cell-index", शून्य);
		अगर (idx == शून्य)
			जारी;
		cell_indices[i] = *idx;
		emac_boot_list[i++] = of_node_get(np);
		अगर (i >= EMAC_BOOT_LIST_SIZE) अणु
			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण
	max = i;

	/* Bubble sort them (करोh, what a creative algorithm :-) */
	क्रम (i = 0; max > 1 && (i < (max - 1)); i++)
		क्रम (j = i; j < max; j++) अणु
			अगर (cell_indices[i] > cell_indices[j]) अणु
				swap(emac_boot_list[i], emac_boot_list[j]);
				swap(cell_indices[i], cell_indices[j]);
			पूर्ण
		पूर्ण
पूर्ण

अटल पूर्णांक __init emac_init(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk(KERN_INFO DRV_DESC ", version " DRV_VERSION "\n");

	/* Build EMAC boot list */
	emac_make_bootlist();

	/* Init submodules */
	rc = mal_init();
	अगर (rc)
		जाओ err;
	rc = zmii_init();
	अगर (rc)
		जाओ err_mal;
	rc = rgmii_init();
	अगर (rc)
		जाओ err_zmii;
	rc = tah_init();
	अगर (rc)
		जाओ err_rgmii;
	rc = platक्रमm_driver_रेजिस्टर(&emac_driver);
	अगर (rc)
		जाओ err_tah;

	वापस 0;

 err_tah:
	tah_निकास();
 err_rgmii:
	rgmii_निकास();
 err_zmii:
	zmii_निकास();
 err_mal:
	mal_निकास();
 err:
	वापस rc;
पूर्ण

अटल व्योम __निकास emac_निकास(व्योम)
अणु
	पूर्णांक i;

	platक्रमm_driver_unरेजिस्टर(&emac_driver);

	tah_निकास();
	rgmii_निकास();
	zmii_निकास();
	mal_निकास();

	/* Destroy EMAC boot list */
	क्रम (i = 0; i < EMAC_BOOT_LIST_SIZE; i++)
		of_node_put(emac_boot_list[i]);
पूर्ण

module_init(emac_init);
module_निकास(emac_निकास);
