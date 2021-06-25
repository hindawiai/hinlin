<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * JMicron JMC2x0 series PCIe Ethernet Linux Device Driver
 *
 * Copyright 2008 JMicron Technology Corporation
 * https://www.jmicron.com/
 * Copyright (c) 2009 - 2010 Guo-Fu Tseng <cooldavid@cooldavid.org>
 *
 * Author: Guo-Fu Tseng <cooldavid@cooldavid.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/slab.h>
#समावेश <net/ip6_checksum.h>
#समावेश "jme.h"

अटल पूर्णांक क्रमce_pseuकरोhp = -1;
अटल पूर्णांक no_pseuकरोhp = -1;
अटल पूर्णांक no_extplug = -1;
module_param(क्रमce_pseuकरोhp, पूर्णांक, 0);
MODULE_PARM_DESC(क्रमce_pseuकरोhp,
	"Enable pseudo hot-plug feature manually by driver instead of BIOS.");
module_param(no_pseuकरोhp, पूर्णांक, 0);
MODULE_PARM_DESC(no_pseuकरोhp, "Disable pseudo hot-plug feature.");
module_param(no_extplug, पूर्णांक, 0);
MODULE_PARM_DESC(no_extplug,
	"Do not use external plug signal for pseudo hot-plug.");

अटल पूर्णांक
jme_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy, पूर्णांक reg)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	पूर्णांक i, val, again = (reg == MII_BMSR) ? 1 : 0;

पढ़ो_again:
	jग_लिखो32(jme, JME_SMI, SMI_OP_REQ |
				smi_phy_addr(phy) |
				smi_reg_addr(reg));

	wmb();
	क्रम (i = JME_PHY_TIMEOUT * 50 ; i > 0 ; --i) अणु
		udelay(20);
		val = jपढ़ो32(jme, JME_SMI);
		अगर ((val & SMI_OP_REQ) == 0)
			अवरोध;
	पूर्ण

	अगर (i == 0) अणु
		pr_err("phy(%d) read timeout : %d\n", phy, reg);
		वापस 0;
	पूर्ण

	अगर (again--)
		जाओ पढ़ो_again;

	वापस (val & SMI_DATA_MASK) >> SMI_DATA_SHIFT;
पूर्ण

अटल व्योम
jme_mdio_ग_लिखो(काष्ठा net_device *netdev,
				पूर्णांक phy, पूर्णांक reg, पूर्णांक val)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	पूर्णांक i;

	jग_लिखो32(jme, JME_SMI, SMI_OP_WRITE | SMI_OP_REQ |
		((val << SMI_DATA_SHIFT) & SMI_DATA_MASK) |
		smi_phy_addr(phy) | smi_reg_addr(reg));

	wmb();
	क्रम (i = JME_PHY_TIMEOUT * 50 ; i > 0 ; --i) अणु
		udelay(20);
		अगर ((jपढ़ो32(jme, JME_SMI) & SMI_OP_REQ) == 0)
			अवरोध;
	पूर्ण

	अगर (i == 0)
		pr_err("phy(%d) write timeout : %d\n", phy, reg);
पूर्ण

अटल अंतरभूत व्योम
jme_reset_phy_processor(काष्ठा jme_adapter *jme)
अणु
	u32 val;

	jme_mdio_ग_लिखो(jme->dev,
			jme->mii_अगर.phy_id,
			MII_ADVERTISE, ADVERTISE_ALL |
			ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);

	अगर (jme->pdev->device == PCI_DEVICE_ID_JMICRON_JMC250)
		jme_mdio_ग_लिखो(jme->dev,
				jme->mii_अगर.phy_id,
				MII_CTRL1000,
				ADVERTISE_1000FULL | ADVERTISE_1000HALF);

	val = jme_mdio_पढ़ो(jme->dev,
				jme->mii_अगर.phy_id,
				MII_BMCR);

	jme_mdio_ग_लिखो(jme->dev,
			jme->mii_अगर.phy_id,
			MII_BMCR, val | BMCR_RESET);
पूर्ण

अटल व्योम
jme_setup_wakeup_frame(काष्ठा jme_adapter *jme,
		       स्थिर u32 *mask, u32 crc, पूर्णांक fnr)
अणु
	पूर्णांक i;

	/*
	 * Setup CRC pattern
	 */
	jग_लिखो32(jme, JME_WFOI, WFOI_CRC_SEL | (fnr & WFOI_FRAME_SEL));
	wmb();
	jग_लिखो32(jme, JME_WFODP, crc);
	wmb();

	/*
	 * Setup Mask
	 */
	क्रम (i = 0 ; i < WAKEUP_FRAME_MASK_DWNR ; ++i) अणु
		jग_लिखो32(jme, JME_WFOI,
				((i << WFOI_MASK_SHIFT) & WFOI_MASK_SEL) |
				(fnr & WFOI_FRAME_SEL));
		wmb();
		jग_लिखो32(jme, JME_WFODP, mask[i]);
		wmb();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
jme_mac_rxclk_off(काष्ठा jme_adapter *jme)
अणु
	jme->reg_gpreg1 |= GPREG1_RXCLKOFF;
	jग_लिखो32f(jme, JME_GPREG1, jme->reg_gpreg1);
पूर्ण

अटल अंतरभूत व्योम
jme_mac_rxclk_on(काष्ठा jme_adapter *jme)
अणु
	jme->reg_gpreg1 &= ~GPREG1_RXCLKOFF;
	jग_लिखो32f(jme, JME_GPREG1, jme->reg_gpreg1);
पूर्ण

अटल अंतरभूत व्योम
jme_mac_txclk_off(काष्ठा jme_adapter *jme)
अणु
	jme->reg_ghc &= ~(GHC_TO_CLK_SRC | GHC_TXMAC_CLK_SRC);
	jग_लिखो32f(jme, JME_GHC, jme->reg_ghc);
पूर्ण

अटल अंतरभूत व्योम
jme_mac_txclk_on(काष्ठा jme_adapter *jme)
अणु
	u32 speed = jme->reg_ghc & GHC_SPEED;
	अगर (speed == GHC_SPEED_1000M)
		jme->reg_ghc |= GHC_TO_CLK_GPHY | GHC_TXMAC_CLK_GPHY;
	अन्यथा
		jme->reg_ghc |= GHC_TO_CLK_PCIE | GHC_TXMAC_CLK_PCIE;
	jग_लिखो32f(jme, JME_GHC, jme->reg_ghc);
पूर्ण

अटल अंतरभूत व्योम
jme_reset_ghc_speed(काष्ठा jme_adapter *jme)
अणु
	jme->reg_ghc &= ~(GHC_SPEED | GHC_DPX);
	jग_लिखो32f(jme, JME_GHC, jme->reg_ghc);
पूर्ण

अटल अंतरभूत व्योम
jme_reset_250A2_workaround(काष्ठा jme_adapter *jme)
अणु
	jme->reg_gpreg1 &= ~(GPREG1_HALFMODEPATCH |
			     GPREG1_RSSPATCH);
	jग_लिखो32(jme, JME_GPREG1, jme->reg_gpreg1);
पूर्ण

अटल अंतरभूत व्योम
jme_निश्चित_ghc_reset(काष्ठा jme_adapter *jme)
अणु
	jme->reg_ghc |= GHC_SWRST;
	jग_लिखो32f(jme, JME_GHC, jme->reg_ghc);
पूर्ण

अटल अंतरभूत व्योम
jme_clear_ghc_reset(काष्ठा jme_adapter *jme)
अणु
	jme->reg_ghc &= ~GHC_SWRST;
	jग_लिखो32f(jme, JME_GHC, jme->reg_ghc);
पूर्ण

अटल व्योम
jme_reset_mac_processor(काष्ठा jme_adapter *jme)
अणु
	अटल स्थिर u32 mask[WAKEUP_FRAME_MASK_DWNR] = अणु0, 0, 0, 0पूर्ण;
	u32 crc = 0xCDCDCDCD;
	u32 gpreg0;
	पूर्णांक i;

	jme_reset_ghc_speed(jme);
	jme_reset_250A2_workaround(jme);

	jme_mac_rxclk_on(jme);
	jme_mac_txclk_on(jme);
	udelay(1);
	jme_निश्चित_ghc_reset(jme);
	udelay(1);
	jme_mac_rxclk_off(jme);
	jme_mac_txclk_off(jme);
	udelay(1);
	jme_clear_ghc_reset(jme);
	udelay(1);
	jme_mac_rxclk_on(jme);
	jme_mac_txclk_on(jme);
	udelay(1);
	jme_mac_rxclk_off(jme);
	jme_mac_txclk_off(jme);

	jग_लिखो32(jme, JME_RXDBA_LO, 0x00000000);
	jग_लिखो32(jme, JME_RXDBA_HI, 0x00000000);
	jग_लिखो32(jme, JME_RXQDC, 0x00000000);
	jग_लिखो32(jme, JME_RXNDA, 0x00000000);
	jग_लिखो32(jme, JME_TXDBA_LO, 0x00000000);
	jग_लिखो32(jme, JME_TXDBA_HI, 0x00000000);
	jग_लिखो32(jme, JME_TXQDC, 0x00000000);
	jग_लिखो32(jme, JME_TXNDA, 0x00000000);

	jग_लिखो32(jme, JME_RXMCHT_LO, 0x00000000);
	jग_लिखो32(jme, JME_RXMCHT_HI, 0x00000000);
	क्रम (i = 0 ; i < WAKEUP_FRAME_NR ; ++i)
		jme_setup_wakeup_frame(jme, mask, crc, i);
	अगर (jme->fpgaver)
		gpreg0 = GPREG0_DEFAULT | GPREG0_LNKINTPOLL;
	अन्यथा
		gpreg0 = GPREG0_DEFAULT;
	jग_लिखो32(jme, JME_GPREG0, gpreg0);
पूर्ण

अटल अंतरभूत व्योम
jme_clear_pm_enable_wol(काष्ठा jme_adapter *jme)
अणु
	jग_लिखो32(jme, JME_PMCS, PMCS_STMASK | jme->reg_pmcs);
पूर्ण

अटल अंतरभूत व्योम
jme_clear_pm_disable_wol(काष्ठा jme_adapter *jme)
अणु
	jग_लिखो32(jme, JME_PMCS, PMCS_STMASK);
पूर्ण

अटल पूर्णांक
jme_reload_eeprom(काष्ठा jme_adapter *jme)
अणु
	u32 val;
	पूर्णांक i;

	val = jपढ़ो32(jme, JME_SMBCSR);

	अगर (val & SMBCSR_EEPROMD) अणु
		val |= SMBCSR_CNACK;
		jग_लिखो32(jme, JME_SMBCSR, val);
		val |= SMBCSR_RELOAD;
		jग_लिखो32(jme, JME_SMBCSR, val);
		mdelay(12);

		क्रम (i = JME_EEPROM_RELOAD_TIMEOUT; i > 0; --i) अणु
			mdelay(1);
			अगर ((jपढ़ो32(jme, JME_SMBCSR) & SMBCSR_RELOAD) == 0)
				अवरोध;
		पूर्ण

		अगर (i == 0) अणु
			pr_err("eeprom reload timeout\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
jme_load_macaddr(काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	अचिन्हित अक्षर macaddr[ETH_ALEN];
	u32 val;

	spin_lock_bh(&jme->macaddr_lock);
	val = jपढ़ो32(jme, JME_RXUMA_LO);
	macaddr[0] = (val >>  0) & 0xFF;
	macaddr[1] = (val >>  8) & 0xFF;
	macaddr[2] = (val >> 16) & 0xFF;
	macaddr[3] = (val >> 24) & 0xFF;
	val = jपढ़ो32(jme, JME_RXUMA_HI);
	macaddr[4] = (val >>  0) & 0xFF;
	macaddr[5] = (val >>  8) & 0xFF;
	स_नकल(netdev->dev_addr, macaddr, ETH_ALEN);
	spin_unlock_bh(&jme->macaddr_lock);
पूर्ण

अटल अंतरभूत व्योम
jme_set_rx_pcc(काष्ठा jme_adapter *jme, पूर्णांक p)
अणु
	चयन (p) अणु
	हाल PCC_OFF:
		jग_लिखो32(jme, JME_PCCRX0,
			((PCC_OFF_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_OFF_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		अवरोध;
	हाल PCC_P1:
		jग_लिखो32(jme, JME_PCCRX0,
			((PCC_P1_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_P1_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		अवरोध;
	हाल PCC_P2:
		jग_लिखो32(jme, JME_PCCRX0,
			((PCC_P2_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_P2_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		अवरोध;
	हाल PCC_P3:
		jग_लिखो32(jme, JME_PCCRX0,
			((PCC_P3_TO << PCCRXTO_SHIFT) & PCCRXTO_MASK) |
			((PCC_P3_CNT << PCCRX_SHIFT) & PCCRX_MASK));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	wmb();

	अगर (!(test_bit(JME_FLAG_POLL, &jme->flags)))
		netअगर_info(jme, rx_status, jme->dev, "Switched to PCC_P%d\n", p);
पूर्ण

अटल व्योम
jme_start_irq(काष्ठा jme_adapter *jme)
अणु
	रेजिस्टर काष्ठा dynpcc_info *dpi = &(jme->dpi);

	jme_set_rx_pcc(jme, PCC_P1);
	dpi->cur		= PCC_P1;
	dpi->attempt		= PCC_P1;
	dpi->cnt		= 0;

	jग_लिखो32(jme, JME_PCCTX,
			((PCC_TX_TO << PCCTXTO_SHIFT) & PCCTXTO_MASK) |
			((PCC_TX_CNT << PCCTX_SHIFT) & PCCTX_MASK) |
			PCCTXQ0_EN
		);

	/*
	 * Enable Interrupts
	 */
	jग_लिखो32(jme, JME_IENS, INTR_ENABLE);
पूर्ण

अटल अंतरभूत व्योम
jme_stop_irq(काष्ठा jme_adapter *jme)
अणु
	/*
	 * Disable Interrupts
	 */
	jग_लिखो32f(jme, JME_IENC, INTR_ENABLE);
पूर्ण

अटल u32
jme_linkstat_from_phy(काष्ठा jme_adapter *jme)
अणु
	u32 phylink, bmsr;

	phylink = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, 17);
	bmsr = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, MII_BMSR);
	अगर (bmsr & BMSR_ANCOMP)
		phylink |= PHY_LINK_AUTONEG_COMPLETE;

	वापस phylink;
पूर्ण

अटल अंतरभूत व्योम
jme_set_phyfअगरo_5level(काष्ठा jme_adapter *jme)
अणु
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, 27, 0x0004);
पूर्ण

अटल अंतरभूत व्योम
jme_set_phyfअगरo_8level(काष्ठा jme_adapter *jme)
अणु
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, 27, 0x0000);
पूर्ण

अटल पूर्णांक
jme_check_link(काष्ठा net_device *netdev, पूर्णांक testonly)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	u32 phylink, cnt = JME_SPDRSV_TIMEOUT, bmcr;
	अक्षर linkmsg[64];
	पूर्णांक rc = 0;

	linkmsg[0] = '\0';

	अगर (jme->fpgaver)
		phylink = jme_linkstat_from_phy(jme);
	अन्यथा
		phylink = jपढ़ो32(jme, JME_PHY_LINK);

	अगर (phylink & PHY_LINK_UP) अणु
		अगर (!(phylink & PHY_LINK_AUTONEG_COMPLETE)) अणु
			/*
			 * If we did not enable AN
			 * Speed/Duplex Info should be obtained from SMI
			 */
			phylink = PHY_LINK_UP;

			bmcr = jme_mdio_पढ़ो(jme->dev,
						jme->mii_अगर.phy_id,
						MII_BMCR);

			phylink |= ((bmcr & BMCR_SPEED1000) &&
					(bmcr & BMCR_SPEED100) == 0) ?
					PHY_LINK_SPEED_1000M :
					(bmcr & BMCR_SPEED100) ?
					PHY_LINK_SPEED_100M :
					PHY_LINK_SPEED_10M;

			phylink |= (bmcr & BMCR_FULLDPLX) ?
					 PHY_LINK_DUPLEX : 0;

			म_जोड़ो(linkmsg, "Forced: ");
		पूर्ण अन्यथा अणु
			/*
			 * Keep polling क्रम speed/duplex resolve complete
			 */
			जबतक (!(phylink & PHY_LINK_SPEEDDPU_RESOLVED) &&
				--cnt) अणु

				udelay(1);

				अगर (jme->fpgaver)
					phylink = jme_linkstat_from_phy(jme);
				अन्यथा
					phylink = jपढ़ो32(jme, JME_PHY_LINK);
			पूर्ण
			अगर (!cnt)
				pr_err("Waiting speed resolve timeout\n");

			म_जोड़ो(linkmsg, "ANed: ");
		पूर्ण

		अगर (jme->phylink == phylink) अणु
			rc = 1;
			जाओ out;
		पूर्ण
		अगर (testonly)
			जाओ out;

		jme->phylink = phylink;

		/*
		 * The speed/duplex setting of jme->reg_ghc alपढ़ोy cleared
		 * by jme_reset_mac_processor()
		 */
		चयन (phylink & PHY_LINK_SPEED_MASK) अणु
		हाल PHY_LINK_SPEED_10M:
			jme->reg_ghc |= GHC_SPEED_10M;
			म_जोड़ो(linkmsg, "10 Mbps, ");
			अवरोध;
		हाल PHY_LINK_SPEED_100M:
			jme->reg_ghc |= GHC_SPEED_100M;
			म_जोड़ो(linkmsg, "100 Mbps, ");
			अवरोध;
		हाल PHY_LINK_SPEED_1000M:
			jme->reg_ghc |= GHC_SPEED_1000M;
			म_जोड़ो(linkmsg, "1000 Mbps, ");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (phylink & PHY_LINK_DUPLEX) अणु
			jग_लिखो32(jme, JME_TXMCS, TXMCS_DEFAULT);
			jग_लिखो32(jme, JME_TXTRHD, TXTRHD_FULLDUPLEX);
			jme->reg_ghc |= GHC_DPX;
		पूर्ण अन्यथा अणु
			jग_लिखो32(jme, JME_TXMCS, TXMCS_DEFAULT |
						TXMCS_BACKOFF |
						TXMCS_CARRIERSENSE |
						TXMCS_COLLISION);
			jग_लिखो32(jme, JME_TXTRHD, TXTRHD_HALFDUPLEX);
		पूर्ण

		jग_लिखो32(jme, JME_GHC, jme->reg_ghc);

		अगर (is_buggy250(jme->pdev->device, jme->chiprev)) अणु
			jme->reg_gpreg1 &= ~(GPREG1_HALFMODEPATCH |
					     GPREG1_RSSPATCH);
			अगर (!(phylink & PHY_LINK_DUPLEX))
				jme->reg_gpreg1 |= GPREG1_HALFMODEPATCH;
			चयन (phylink & PHY_LINK_SPEED_MASK) अणु
			हाल PHY_LINK_SPEED_10M:
				jme_set_phyfअगरo_8level(jme);
				jme->reg_gpreg1 |= GPREG1_RSSPATCH;
				अवरोध;
			हाल PHY_LINK_SPEED_100M:
				jme_set_phyfअगरo_5level(jme);
				jme->reg_gpreg1 |= GPREG1_RSSPATCH;
				अवरोध;
			हाल PHY_LINK_SPEED_1000M:
				jme_set_phyfअगरo_8level(jme);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		jग_लिखो32(jme, JME_GPREG1, jme->reg_gpreg1);

		म_जोड़ो(linkmsg, (phylink & PHY_LINK_DUPLEX) ?
					"Full-Duplex, " :
					"Half-Duplex, ");
		म_जोड़ो(linkmsg, (phylink & PHY_LINK_MDI_STAT) ?
					"MDI-X" :
					"MDI");
		netअगर_info(jme, link, jme->dev, "Link is up at %s\n", linkmsg);
		netअगर_carrier_on(netdev);
	पूर्ण अन्यथा अणु
		अगर (testonly)
			जाओ out;

		netअगर_info(jme, link, jme->dev, "Link is down\n");
		jme->phylink = 0;
		netअगर_carrier_off(netdev);
	पूर्ण

out:
	वापस rc;
पूर्ण

अटल पूर्णांक
jme_setup_tx_resources(काष्ठा jme_adapter *jme)
अणु
	काष्ठा jme_ring *txring = &(jme->txring[0]);

	txring->alloc = dma_alloc_coherent(&(jme->pdev->dev),
				   TX_RING_ALLOC_SIZE(jme->tx_ring_size),
				   &(txring->dmaalloc),
				   GFP_ATOMIC);

	अगर (!txring->alloc)
		जाओ err_set_null;

	/*
	 * 16 Bytes align
	 */
	txring->desc		= (व्योम *)ALIGN((अचिन्हित दीर्घ)(txring->alloc),
						RING_DESC_ALIGN);
	txring->dma		= ALIGN(txring->dmaalloc, RING_DESC_ALIGN);
	txring->next_to_use	= 0;
	atomic_set(&txring->next_to_clean, 0);
	atomic_set(&txring->nr_मुक्त, jme->tx_ring_size);

	txring->bufinf		= kसुस्मृति(jme->tx_ring_size,
						माप(काष्ठा jme_buffer_info),
						GFP_ATOMIC);
	अगर (unlikely(!(txring->bufinf)))
		जाओ err_मुक्त_txring;

	वापस 0;

err_मुक्त_txring:
	dma_मुक्त_coherent(&(jme->pdev->dev),
			  TX_RING_ALLOC_SIZE(jme->tx_ring_size),
			  txring->alloc,
			  txring->dmaalloc);

err_set_null:
	txring->desc = शून्य;
	txring->dmaalloc = 0;
	txring->dma = 0;
	txring->bufinf = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल व्योम
jme_मुक्त_tx_resources(काष्ठा jme_adapter *jme)
अणु
	पूर्णांक i;
	काष्ठा jme_ring *txring = &(jme->txring[0]);
	काष्ठा jme_buffer_info *txbi;

	अगर (txring->alloc) अणु
		अगर (txring->bufinf) अणु
			क्रम (i = 0 ; i < jme->tx_ring_size ; ++i) अणु
				txbi = txring->bufinf + i;
				अगर (txbi->skb) अणु
					dev_kमुक्त_skb(txbi->skb);
					txbi->skb = शून्य;
				पूर्ण
				txbi->mapping		= 0;
				txbi->len		= 0;
				txbi->nr_desc		= 0;
				txbi->start_xmit	= 0;
			पूर्ण
			kमुक्त(txring->bufinf);
		पूर्ण

		dma_मुक्त_coherent(&(jme->pdev->dev),
				  TX_RING_ALLOC_SIZE(jme->tx_ring_size),
				  txring->alloc,
				  txring->dmaalloc);

		txring->alloc		= शून्य;
		txring->desc		= शून्य;
		txring->dmaalloc	= 0;
		txring->dma		= 0;
		txring->bufinf		= शून्य;
	पूर्ण
	txring->next_to_use	= 0;
	atomic_set(&txring->next_to_clean, 0);
	atomic_set(&txring->nr_मुक्त, 0);
पूर्ण

अटल अंतरभूत व्योम
jme_enable_tx_engine(काष्ठा jme_adapter *jme)
अणु
	/*
	 * Select Queue 0
	 */
	jग_लिखो32(jme, JME_TXCS, TXCS_DEFAULT | TXCS_SELECT_QUEUE0);
	wmb();

	/*
	 * Setup TX Queue 0 DMA Bass Address
	 */
	jग_लिखो32(jme, JME_TXDBA_LO, (__u64)jme->txring[0].dma & 0xFFFFFFFFUL);
	jग_लिखो32(jme, JME_TXDBA_HI, (__u64)(jme->txring[0].dma) >> 32);
	jग_लिखो32(jme, JME_TXNDA, (__u64)jme->txring[0].dma & 0xFFFFFFFFUL);

	/*
	 * Setup TX Descptor Count
	 */
	jग_लिखो32(jme, JME_TXQDC, jme->tx_ring_size);

	/*
	 * Enable TX Engine
	 */
	wmb();
	jग_लिखो32f(jme, JME_TXCS, jme->reg_txcs |
				TXCS_SELECT_QUEUE0 |
				TXCS_ENABLE);

	/*
	 * Start घड़ी क्रम TX MAC Processor
	 */
	jme_mac_txclk_on(jme);
पूर्ण

अटल अंतरभूत व्योम
jme_disable_tx_engine(काष्ठा jme_adapter *jme)
अणु
	पूर्णांक i;
	u32 val;

	/*
	 * Disable TX Engine
	 */
	jग_लिखो32(jme, JME_TXCS, jme->reg_txcs | TXCS_SELECT_QUEUE0);
	wmb();

	val = jपढ़ो32(jme, JME_TXCS);
	क्रम (i = JME_TX_DISABLE_TIMEOUT ; (val & TXCS_ENABLE) && i > 0 ; --i) अणु
		mdelay(1);
		val = jपढ़ो32(jme, JME_TXCS);
		rmb();
	पूर्ण

	अगर (!i)
		pr_err("Disable TX engine timeout\n");

	/*
	 * Stop घड़ी क्रम TX MAC Processor
	 */
	jme_mac_txclk_off(jme);
पूर्ण

अटल व्योम
jme_set_clean_rxdesc(काष्ठा jme_adapter *jme, पूर्णांक i)
अणु
	काष्ठा jme_ring *rxring = &(jme->rxring[0]);
	रेजिस्टर काष्ठा rxdesc *rxdesc = rxring->desc;
	काष्ठा jme_buffer_info *rxbi = rxring->bufinf;
	rxdesc += i;
	rxbi += i;

	rxdesc->dw[0] = 0;
	rxdesc->dw[1] = 0;
	rxdesc->desc1.bufaddrh	= cpu_to_le32((__u64)rxbi->mapping >> 32);
	rxdesc->desc1.bufaddrl	= cpu_to_le32(
					(__u64)rxbi->mapping & 0xFFFFFFFFUL);
	rxdesc->desc1.datalen	= cpu_to_le16(rxbi->len);
	अगर (jme->dev->features & NETIF_F_HIGHDMA)
		rxdesc->desc1.flags = RXFLAG_64BIT;
	wmb();
	rxdesc->desc1.flags	|= RXFLAG_OWN | RXFLAG_INT;
पूर्ण

अटल पूर्णांक
jme_make_new_rx_buf(काष्ठा jme_adapter *jme, पूर्णांक i)
अणु
	काष्ठा jme_ring *rxring = &(jme->rxring[0]);
	काष्ठा jme_buffer_info *rxbi = rxring->bufinf + i;
	काष्ठा sk_buff *skb;
	dma_addr_t mapping;

	skb = netdev_alloc_skb(jme->dev,
		jme->dev->mtu + RX_EXTRA_LEN);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	mapping = pci_map_page(jme->pdev, virt_to_page(skb->data),
			       offset_in_page(skb->data), skb_tailroom(skb),
			       PCI_DMA_FROMDEVICE);
	अगर (unlikely(pci_dma_mapping_error(jme->pdev, mapping))) अणु
		dev_kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	अगर (likely(rxbi->mapping))
		pci_unmap_page(jme->pdev, rxbi->mapping,
			       rxbi->len, PCI_DMA_FROMDEVICE);

	rxbi->skb = skb;
	rxbi->len = skb_tailroom(skb);
	rxbi->mapping = mapping;
	वापस 0;
पूर्ण

अटल व्योम
jme_मुक्त_rx_buf(काष्ठा jme_adapter *jme, पूर्णांक i)
अणु
	काष्ठा jme_ring *rxring = &(jme->rxring[0]);
	काष्ठा jme_buffer_info *rxbi = rxring->bufinf;
	rxbi += i;

	अगर (rxbi->skb) अणु
		pci_unmap_page(jme->pdev,
				 rxbi->mapping,
				 rxbi->len,
				 PCI_DMA_FROMDEVICE);
		dev_kमुक्त_skb(rxbi->skb);
		rxbi->skb = शून्य;
		rxbi->mapping = 0;
		rxbi->len = 0;
	पूर्ण
पूर्ण

अटल व्योम
jme_मुक्त_rx_resources(काष्ठा jme_adapter *jme)
अणु
	पूर्णांक i;
	काष्ठा jme_ring *rxring = &(jme->rxring[0]);

	अगर (rxring->alloc) अणु
		अगर (rxring->bufinf) अणु
			क्रम (i = 0 ; i < jme->rx_ring_size ; ++i)
				jme_मुक्त_rx_buf(jme, i);
			kमुक्त(rxring->bufinf);
		पूर्ण

		dma_मुक्त_coherent(&(jme->pdev->dev),
				  RX_RING_ALLOC_SIZE(jme->rx_ring_size),
				  rxring->alloc,
				  rxring->dmaalloc);
		rxring->alloc    = शून्य;
		rxring->desc     = शून्य;
		rxring->dmaalloc = 0;
		rxring->dma      = 0;
		rxring->bufinf   = शून्य;
	पूर्ण
	rxring->next_to_use   = 0;
	atomic_set(&rxring->next_to_clean, 0);
पूर्ण

अटल पूर्णांक
jme_setup_rx_resources(काष्ठा jme_adapter *jme)
अणु
	पूर्णांक i;
	काष्ठा jme_ring *rxring = &(jme->rxring[0]);

	rxring->alloc = dma_alloc_coherent(&(jme->pdev->dev),
				   RX_RING_ALLOC_SIZE(jme->rx_ring_size),
				   &(rxring->dmaalloc),
				   GFP_ATOMIC);
	अगर (!rxring->alloc)
		जाओ err_set_null;

	/*
	 * 16 Bytes align
	 */
	rxring->desc		= (व्योम *)ALIGN((अचिन्हित दीर्घ)(rxring->alloc),
						RING_DESC_ALIGN);
	rxring->dma		= ALIGN(rxring->dmaalloc, RING_DESC_ALIGN);
	rxring->next_to_use	= 0;
	atomic_set(&rxring->next_to_clean, 0);

	rxring->bufinf		= kसुस्मृति(jme->rx_ring_size,
						माप(काष्ठा jme_buffer_info),
						GFP_ATOMIC);
	अगर (unlikely(!(rxring->bufinf)))
		जाओ err_मुक्त_rxring;

	/*
	 * Initiallize Receive Descriptors
	 */
	क्रम (i = 0 ; i < jme->rx_ring_size ; ++i) अणु
		अगर (unlikely(jme_make_new_rx_buf(jme, i))) अणु
			jme_मुक्त_rx_resources(jme);
			वापस -ENOMEM;
		पूर्ण

		jme_set_clean_rxdesc(jme, i);
	पूर्ण

	वापस 0;

err_मुक्त_rxring:
	dma_मुक्त_coherent(&(jme->pdev->dev),
			  RX_RING_ALLOC_SIZE(jme->rx_ring_size),
			  rxring->alloc,
			  rxring->dmaalloc);
err_set_null:
	rxring->desc = शून्य;
	rxring->dmaalloc = 0;
	rxring->dma = 0;
	rxring->bufinf = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम
jme_enable_rx_engine(काष्ठा jme_adapter *jme)
अणु
	/*
	 * Select Queue 0
	 */
	jग_लिखो32(jme, JME_RXCS, jme->reg_rxcs |
				RXCS_QUEUESEL_Q0);
	wmb();

	/*
	 * Setup RX DMA Bass Address
	 */
	jग_लिखो32(jme, JME_RXDBA_LO, (__u64)(jme->rxring[0].dma) & 0xFFFFFFFFUL);
	jग_लिखो32(jme, JME_RXDBA_HI, (__u64)(jme->rxring[0].dma) >> 32);
	jग_लिखो32(jme, JME_RXNDA, (__u64)(jme->rxring[0].dma) & 0xFFFFFFFFUL);

	/*
	 * Setup RX Descriptor Count
	 */
	jग_लिखो32(jme, JME_RXQDC, jme->rx_ring_size);

	/*
	 * Setup Unicast Filter
	 */
	jme_set_unicastaddr(jme->dev);
	jme_set_multi(jme->dev);

	/*
	 * Enable RX Engine
	 */
	wmb();
	jग_लिखो32f(jme, JME_RXCS, jme->reg_rxcs |
				RXCS_QUEUESEL_Q0 |
				RXCS_ENABLE |
				RXCS_QST);

	/*
	 * Start घड़ी क्रम RX MAC Processor
	 */
	jme_mac_rxclk_on(jme);
पूर्ण

अटल अंतरभूत व्योम
jme_restart_rx_engine(काष्ठा jme_adapter *jme)
अणु
	/*
	 * Start RX Engine
	 */
	jग_लिखो32(jme, JME_RXCS, jme->reg_rxcs |
				RXCS_QUEUESEL_Q0 |
				RXCS_ENABLE |
				RXCS_QST);
पूर्ण

अटल अंतरभूत व्योम
jme_disable_rx_engine(काष्ठा jme_adapter *jme)
अणु
	पूर्णांक i;
	u32 val;

	/*
	 * Disable RX Engine
	 */
	jग_लिखो32(jme, JME_RXCS, jme->reg_rxcs);
	wmb();

	val = jपढ़ो32(jme, JME_RXCS);
	क्रम (i = JME_RX_DISABLE_TIMEOUT ; (val & RXCS_ENABLE) && i > 0 ; --i) अणु
		mdelay(1);
		val = jपढ़ो32(jme, JME_RXCS);
		rmb();
	पूर्ण

	अगर (!i)
		pr_err("Disable RX engine timeout\n");

	/*
	 * Stop घड़ी क्रम RX MAC Processor
	 */
	jme_mac_rxclk_off(jme);
पूर्ण

अटल u16
jme_udpsum(काष्ठा sk_buff *skb)
अणु
	u16 csum = 0xFFFFu;

	अगर (skb->len < (ETH_HLEN + माप(काष्ठा iphdr)))
		वापस csum;
	अगर (skb->protocol != htons(ETH_P_IP))
		वापस csum;
	skb_set_network_header(skb, ETH_HLEN);
	अगर ((ip_hdr(skb)->protocol != IPPROTO_UDP) ||
	    (skb->len < (ETH_HLEN +
			(ip_hdr(skb)->ihl << 2) +
			माप(काष्ठा udphdr)))) अणु
		skb_reset_network_header(skb);
		वापस csum;
	पूर्ण
	skb_set_transport_header(skb,
			ETH_HLEN + (ip_hdr(skb)->ihl << 2));
	csum = udp_hdr(skb)->check;
	skb_reset_transport_header(skb);
	skb_reset_network_header(skb);

	वापस csum;
पूर्ण

अटल पूर्णांक
jme_rxsum_ok(काष्ठा jme_adapter *jme, u16 flags, काष्ठा sk_buff *skb)
अणु
	अगर (!(flags & (RXWBFLAG_TCPON | RXWBFLAG_UDPON | RXWBFLAG_IPV4)))
		वापस false;

	अगर (unlikely((flags & (RXWBFLAG_MF | RXWBFLAG_TCPON | RXWBFLAG_TCPCS))
			== RXWBFLAG_TCPON)) अणु
		अगर (flags & RXWBFLAG_IPV4)
			netअगर_err(jme, rx_err, jme->dev, "TCP Checksum error\n");
		वापस false;
	पूर्ण

	अगर (unlikely((flags & (RXWBFLAG_MF | RXWBFLAG_UDPON | RXWBFLAG_UDPCS))
			== RXWBFLAG_UDPON) && jme_udpsum(skb)) अणु
		अगर (flags & RXWBFLAG_IPV4)
			netअगर_err(jme, rx_err, jme->dev, "UDP Checksum error\n");
		वापस false;
	पूर्ण

	अगर (unlikely((flags & (RXWBFLAG_IPV4 | RXWBFLAG_IPCS))
			== RXWBFLAG_IPV4)) अणु
		netअगर_err(jme, rx_err, jme->dev, "IPv4 Checksum error\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
jme_alloc_and_feed_skb(काष्ठा jme_adapter *jme, पूर्णांक idx)
अणु
	काष्ठा jme_ring *rxring = &(jme->rxring[0]);
	काष्ठा rxdesc *rxdesc = rxring->desc;
	काष्ठा jme_buffer_info *rxbi = rxring->bufinf;
	काष्ठा sk_buff *skb;
	पूर्णांक framesize;

	rxdesc += idx;
	rxbi += idx;

	skb = rxbi->skb;
	pci_dma_sync_single_क्रम_cpu(jme->pdev,
					rxbi->mapping,
					rxbi->len,
					PCI_DMA_FROMDEVICE);

	अगर (unlikely(jme_make_new_rx_buf(jme, idx))) अणु
		pci_dma_sync_single_क्रम_device(jme->pdev,
						rxbi->mapping,
						rxbi->len,
						PCI_DMA_FROMDEVICE);

		++(NET_STAT(jme).rx_dropped);
	पूर्ण अन्यथा अणु
		framesize = le16_to_cpu(rxdesc->descwb.framesize)
				- RX_PREPAD_SIZE;

		skb_reserve(skb, RX_PREPAD_SIZE);
		skb_put(skb, framesize);
		skb->protocol = eth_type_trans(skb, jme->dev);

		अगर (jme_rxsum_ok(jme, le16_to_cpu(rxdesc->descwb.flags), skb))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		अन्यथा
			skb_checksum_none_निश्चित(skb);

		अगर (rxdesc->descwb.flags & cpu_to_le16(RXWBFLAG_TAGON)) अणु
			u16 vid = le16_to_cpu(rxdesc->descwb.vlan);

			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
			NET_STAT(jme).rx_bytes += 4;
		पूर्ण
		jme->jme_rx(skb);

		अगर ((rxdesc->descwb.flags & cpu_to_le16(RXWBFLAG_DEST)) ==
		    cpu_to_le16(RXWBFLAG_DEST_MUL))
			++(NET_STAT(jme).multicast);

		NET_STAT(jme).rx_bytes += framesize;
		++(NET_STAT(jme).rx_packets);
	पूर्ण

	jme_set_clean_rxdesc(jme, idx);

पूर्ण

अटल पूर्णांक
jme_process_receive(काष्ठा jme_adapter *jme, पूर्णांक limit)
अणु
	काष्ठा jme_ring *rxring = &(jme->rxring[0]);
	काष्ठा rxdesc *rxdesc;
	पूर्णांक i, j, ccnt, desccnt, mask = jme->rx_ring_mask;

	अगर (unlikely(!atomic_dec_and_test(&jme->rx_cleaning)))
		जाओ out_inc;

	अगर (unlikely(atomic_पढ़ो(&jme->link_changing) != 1))
		जाओ out_inc;

	अगर (unlikely(!netअगर_carrier_ok(jme->dev)))
		जाओ out_inc;

	i = atomic_पढ़ो(&rxring->next_to_clean);
	जबतक (limit > 0) अणु
		rxdesc = rxring->desc;
		rxdesc += i;

		अगर ((rxdesc->descwb.flags & cpu_to_le16(RXWBFLAG_OWN)) ||
		!(rxdesc->descwb.desccnt & RXWBDCNT_WBCPL))
			जाओ out;
		--limit;

		rmb();
		desccnt = rxdesc->descwb.desccnt & RXWBDCNT_DCNT;

		अगर (unlikely(desccnt > 1 ||
		rxdesc->descwb.errstat & RXWBERR_ALLERR)) अणु

			अगर (rxdesc->descwb.errstat & RXWBERR_CRCERR)
				++(NET_STAT(jme).rx_crc_errors);
			अन्यथा अगर (rxdesc->descwb.errstat & RXWBERR_OVERUN)
				++(NET_STAT(jme).rx_fअगरo_errors);
			अन्यथा
				++(NET_STAT(jme).rx_errors);

			अगर (desccnt > 1)
				limit -= desccnt - 1;

			क्रम (j = i, ccnt = desccnt ; ccnt-- ; ) अणु
				jme_set_clean_rxdesc(jme, j);
				j = (j + 1) & (mask);
			पूर्ण

		पूर्ण अन्यथा अणु
			jme_alloc_and_feed_skb(jme, i);
		पूर्ण

		i = (i + desccnt) & (mask);
	पूर्ण

out:
	atomic_set(&rxring->next_to_clean, i);

out_inc:
	atomic_inc(&jme->rx_cleaning);

	वापस limit > 0 ? limit : 0;

पूर्ण

अटल व्योम
jme_attempt_pcc(काष्ठा dynpcc_info *dpi, पूर्णांक aपंचांगp)
अणु
	अगर (likely(aपंचांगp == dpi->cur)) अणु
		dpi->cnt = 0;
		वापस;
	पूर्ण

	अगर (dpi->attempt == aपंचांगp) अणु
		++(dpi->cnt);
	पूर्ण अन्यथा अणु
		dpi->attempt = aपंचांगp;
		dpi->cnt = 0;
	पूर्ण

पूर्ण

अटल व्योम
jme_dynamic_pcc(काष्ठा jme_adapter *jme)
अणु
	रेजिस्टर काष्ठा dynpcc_info *dpi = &(jme->dpi);

	अगर ((NET_STAT(jme).rx_bytes - dpi->last_bytes) > PCC_P3_THRESHOLD)
		jme_attempt_pcc(dpi, PCC_P3);
	अन्यथा अगर ((NET_STAT(jme).rx_packets - dpi->last_pkts) > PCC_P2_THRESHOLD ||
		 dpi->पूर्णांकr_cnt > PCC_INTR_THRESHOLD)
		jme_attempt_pcc(dpi, PCC_P2);
	अन्यथा
		jme_attempt_pcc(dpi, PCC_P1);

	अगर (unlikely(dpi->attempt != dpi->cur && dpi->cnt > 5)) अणु
		अगर (dpi->attempt < dpi->cur)
			tasklet_schedule(&jme->rxclean_task);
		jme_set_rx_pcc(jme, dpi->attempt);
		dpi->cur = dpi->attempt;
		dpi->cnt = 0;
	पूर्ण
पूर्ण

अटल व्योम
jme_start_pcc_समयr(काष्ठा jme_adapter *jme)
अणु
	काष्ठा dynpcc_info *dpi = &(jme->dpi);
	dpi->last_bytes		= NET_STAT(jme).rx_bytes;
	dpi->last_pkts		= NET_STAT(jme).rx_packets;
	dpi->पूर्णांकr_cnt		= 0;
	jग_लिखो32(jme, JME_TMCSR,
		TMCSR_EN | ((0xFFFFFF - PCC_INTERVAL_US) & TMCSR_CNT));
पूर्ण

अटल अंतरभूत व्योम
jme_stop_pcc_समयr(काष्ठा jme_adapter *jme)
अणु
	jग_लिखो32(jme, JME_TMCSR, 0);
पूर्ण

अटल व्योम
jme_shutकरोwn_nic(काष्ठा jme_adapter *jme)
अणु
	u32 phylink;

	phylink = jme_linkstat_from_phy(jme);

	अगर (!(phylink & PHY_LINK_UP)) अणु
		/*
		 * Disable all पूर्णांकerrupt beक्रमe issue समयr
		 */
		jme_stop_irq(jme);
		jग_लिखो32(jme, JME_TIMER2, TMCSR_EN | 0xFFFFFE);
	पूर्ण
पूर्ण

अटल व्योम
jme_pcc_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा jme_adapter *jme = from_tasklet(jme, t, pcc_task);
	काष्ठा net_device *netdev = jme->dev;

	अगर (unlikely(test_bit(JME_FLAG_SHUTDOWN, &jme->flags))) अणु
		jme_shutकरोwn_nic(jme);
		वापस;
	पूर्ण

	अगर (unlikely(!netअगर_carrier_ok(netdev) ||
		(atomic_पढ़ो(&jme->link_changing) != 1)
	)) अणु
		jme_stop_pcc_समयr(jme);
		वापस;
	पूर्ण

	अगर (!(test_bit(JME_FLAG_POLL, &jme->flags)))
		jme_dynamic_pcc(jme);

	jme_start_pcc_समयr(jme);
पूर्ण

अटल अंतरभूत व्योम
jme_polling_mode(काष्ठा jme_adapter *jme)
अणु
	jme_set_rx_pcc(jme, PCC_OFF);
पूर्ण

अटल अंतरभूत व्योम
jme_पूर्णांकerrupt_mode(काष्ठा jme_adapter *jme)
अणु
	jme_set_rx_pcc(jme, PCC_P1);
पूर्ण

अटल अंतरभूत पूर्णांक
jme_pseuकरो_hotplug_enabled(काष्ठा jme_adapter *jme)
अणु
	u32 apmc;
	apmc = jपढ़ो32(jme, JME_APMC);
	वापस apmc & JME_APMC_PSEUDO_HP_EN;
पूर्ण

अटल व्योम
jme_start_shutकरोwn_समयr(काष्ठा jme_adapter *jme)
अणु
	u32 apmc;

	apmc = jपढ़ो32(jme, JME_APMC) | JME_APMC_PCIE_SD_EN;
	apmc &= ~JME_APMC_EPIEN_CTRL;
	अगर (!no_extplug) अणु
		jग_लिखो32f(jme, JME_APMC, apmc | JME_APMC_EPIEN_CTRL_EN);
		wmb();
	पूर्ण
	jग_लिखो32f(jme, JME_APMC, apmc);

	jग_लिखो32f(jme, JME_TIMER2, 0);
	set_bit(JME_FLAG_SHUTDOWN, &jme->flags);
	jग_लिखो32(jme, JME_TMCSR,
		TMCSR_EN | ((0xFFFFFF - APMC_PHP_SHUTDOWN_DELAY) & TMCSR_CNT));
पूर्ण

अटल व्योम
jme_stop_shutकरोwn_समयr(काष्ठा jme_adapter *jme)
अणु
	u32 apmc;

	jग_लिखो32f(jme, JME_TMCSR, 0);
	jग_लिखो32f(jme, JME_TIMER2, 0);
	clear_bit(JME_FLAG_SHUTDOWN, &jme->flags);

	apmc = jपढ़ो32(jme, JME_APMC);
	apmc &= ~(JME_APMC_PCIE_SD_EN | JME_APMC_EPIEN_CTRL);
	jग_लिखो32f(jme, JME_APMC, apmc | JME_APMC_EPIEN_CTRL_DIS);
	wmb();
	jग_लिखो32f(jme, JME_APMC, apmc);
पूर्ण

अटल व्योम jme_link_change_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा jme_adapter *jme = container_of(work, काष्ठा jme_adapter, linkch_task);
	काष्ठा net_device *netdev = jme->dev;
	पूर्णांक rc;

	जबतक (!atomic_dec_and_test(&jme->link_changing)) अणु
		atomic_inc(&jme->link_changing);
		netअगर_info(jme, पूर्णांकr, jme->dev, "Get link change lock failed\n");
		जबतक (atomic_पढ़ो(&jme->link_changing) != 1)
			netअगर_info(jme, पूर्णांकr, jme->dev, "Waiting link change lock\n");
	पूर्ण

	अगर (jme_check_link(netdev, 1) && jme->old_mtu == netdev->mtu)
		जाओ out;

	jme->old_mtu = netdev->mtu;
	netअगर_stop_queue(netdev);
	अगर (jme_pseuकरो_hotplug_enabled(jme))
		jme_stop_shutकरोwn_समयr(jme);

	jme_stop_pcc_समयr(jme);
	tasklet_disable(&jme->txclean_task);
	tasklet_disable(&jme->rxclean_task);
	tasklet_disable(&jme->rxempty_task);

	अगर (netअगर_carrier_ok(netdev)) अणु
		jme_disable_rx_engine(jme);
		jme_disable_tx_engine(jme);
		jme_reset_mac_processor(jme);
		jme_मुक्त_rx_resources(jme);
		jme_मुक्त_tx_resources(jme);

		अगर (test_bit(JME_FLAG_POLL, &jme->flags))
			jme_polling_mode(jme);

		netअगर_carrier_off(netdev);
	पूर्ण

	jme_check_link(netdev, 0);
	अगर (netअगर_carrier_ok(netdev)) अणु
		rc = jme_setup_rx_resources(jme);
		अगर (rc) अणु
			pr_err("Allocating resources for RX error, Device STOPPED!\n");
			जाओ out_enable_tasklet;
		पूर्ण

		rc = jme_setup_tx_resources(jme);
		अगर (rc) अणु
			pr_err("Allocating resources for TX error, Device STOPPED!\n");
			जाओ err_out_मुक्त_rx_resources;
		पूर्ण

		jme_enable_rx_engine(jme);
		jme_enable_tx_engine(jme);

		netअगर_start_queue(netdev);

		अगर (test_bit(JME_FLAG_POLL, &jme->flags))
			jme_पूर्णांकerrupt_mode(jme);

		jme_start_pcc_समयr(jme);
	पूर्ण अन्यथा अगर (jme_pseuकरो_hotplug_enabled(jme)) अणु
		jme_start_shutकरोwn_समयr(jme);
	पूर्ण

	जाओ out_enable_tasklet;

err_out_मुक्त_rx_resources:
	jme_मुक्त_rx_resources(jme);
out_enable_tasklet:
	tasklet_enable(&jme->txclean_task);
	tasklet_enable(&jme->rxclean_task);
	tasklet_enable(&jme->rxempty_task);
out:
	atomic_inc(&jme->link_changing);
पूर्ण

अटल व्योम
jme_rx_clean_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा jme_adapter *jme = from_tasklet(jme, t, rxclean_task);
	काष्ठा dynpcc_info *dpi = &(jme->dpi);

	jme_process_receive(jme, jme->rx_ring_size);
	++(dpi->पूर्णांकr_cnt);

पूर्ण

अटल पूर्णांक
jme_poll(JME_NAPI_HOLDER(holder), JME_NAPI_WEIGHT(budget))
अणु
	काष्ठा jme_adapter *jme = jme_napi_priv(holder);
	पूर्णांक rest;

	rest = jme_process_receive(jme, JME_NAPI_WEIGHT_VAL(budget));

	जबतक (atomic_पढ़ो(&jme->rx_empty) > 0) अणु
		atomic_dec(&jme->rx_empty);
		++(NET_STAT(jme).rx_dropped);
		jme_restart_rx_engine(jme);
	पूर्ण
	atomic_inc(&jme->rx_empty);

	अगर (rest) अणु
		JME_RX_COMPLETE(netdev, holder);
		jme_पूर्णांकerrupt_mode(jme);
	पूर्ण

	JME_NAPI_WEIGHT_SET(budget, rest);
	वापस JME_NAPI_WEIGHT_VAL(budget) - rest;
पूर्ण

अटल व्योम
jme_rx_empty_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा jme_adapter *jme = from_tasklet(jme, t, rxempty_task);

	अगर (unlikely(atomic_पढ़ो(&jme->link_changing) != 1))
		वापस;

	अगर (unlikely(!netअगर_carrier_ok(jme->dev)))
		वापस;

	netअगर_info(jme, rx_status, jme->dev, "RX Queue Full!\n");

	jme_rx_clean_tasklet(&jme->rxclean_task);

	जबतक (atomic_पढ़ो(&jme->rx_empty) > 0) अणु
		atomic_dec(&jme->rx_empty);
		++(NET_STAT(jme).rx_dropped);
		jme_restart_rx_engine(jme);
	पूर्ण
	atomic_inc(&jme->rx_empty);
पूर्ण

अटल व्योम
jme_wake_queue_अगर_stopped(काष्ठा jme_adapter *jme)
अणु
	काष्ठा jme_ring *txring = &(jme->txring[0]);

	smp_wmb();
	अगर (unlikely(netअगर_queue_stopped(jme->dev) &&
	atomic_पढ़ो(&txring->nr_मुक्त) >= (jme->tx_wake_threshold))) अणु
		netअगर_info(jme, tx_करोne, jme->dev, "TX Queue Waked\n");
		netअगर_wake_queue(jme->dev);
	पूर्ण

पूर्ण

अटल व्योम jme_tx_clean_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा jme_adapter *jme = from_tasklet(jme, t, txclean_task);
	काष्ठा jme_ring *txring = &(jme->txring[0]);
	काष्ठा txdesc *txdesc = txring->desc;
	काष्ठा jme_buffer_info *txbi = txring->bufinf, *ctxbi, *ttxbi;
	पूर्णांक i, j, cnt = 0, max, err, mask;

	tx_dbg(jme, "Into txclean\n");

	अगर (unlikely(!atomic_dec_and_test(&jme->tx_cleaning)))
		जाओ out;

	अगर (unlikely(atomic_पढ़ो(&jme->link_changing) != 1))
		जाओ out;

	अगर (unlikely(!netअगर_carrier_ok(jme->dev)))
		जाओ out;

	max = jme->tx_ring_size - atomic_पढ़ो(&txring->nr_मुक्त);
	mask = jme->tx_ring_mask;

	क्रम (i = atomic_पढ़ो(&txring->next_to_clean) ; cnt < max ; ) अणु

		ctxbi = txbi + i;

		अगर (likely(ctxbi->skb &&
		!(txdesc[i].descwb.flags & TXWBFLAG_OWN))) अणु

			tx_dbg(jme, "txclean: %d+%d@%lu\n",
			       i, ctxbi->nr_desc, jअगरfies);

			err = txdesc[i].descwb.flags & TXWBFLAG_ALLERR;

			क्रम (j = 1 ; j < ctxbi->nr_desc ; ++j) अणु
				ttxbi = txbi + ((i + j) & (mask));
				txdesc[(i + j) & (mask)].dw[0] = 0;

				pci_unmap_page(jme->pdev,
						 ttxbi->mapping,
						 ttxbi->len,
						 PCI_DMA_TODEVICE);

				ttxbi->mapping = 0;
				ttxbi->len = 0;
			पूर्ण

			dev_kमुक्त_skb(ctxbi->skb);

			cnt += ctxbi->nr_desc;

			अगर (unlikely(err)) अणु
				++(NET_STAT(jme).tx_carrier_errors);
			पूर्ण अन्यथा अणु
				++(NET_STAT(jme).tx_packets);
				NET_STAT(jme).tx_bytes += ctxbi->len;
			पूर्ण

			ctxbi->skb = शून्य;
			ctxbi->len = 0;
			ctxbi->start_xmit = 0;

		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण

		i = (i + ctxbi->nr_desc) & mask;

		ctxbi->nr_desc = 0;
	पूर्ण

	tx_dbg(jme, "txclean: done %d@%lu\n", i, jअगरfies);
	atomic_set(&txring->next_to_clean, i);
	atomic_add(cnt, &txring->nr_मुक्त);

	jme_wake_queue_अगर_stopped(jme);

out:
	atomic_inc(&jme->tx_cleaning);
पूर्ण

अटल व्योम
jme_पूर्णांकr_msi(काष्ठा jme_adapter *jme, u32 पूर्णांकrstat)
अणु
	/*
	 * Disable पूर्णांकerrupt
	 */
	jग_लिखो32f(jme, JME_IENC, INTR_ENABLE);

	अगर (पूर्णांकrstat & (INTR_LINKCH | INTR_SWINTR)) अणु
		/*
		 * Link change event is critical
		 * all other events are ignored
		 */
		jग_लिखो32(jme, JME_IEVE, पूर्णांकrstat);
		schedule_work(&jme->linkch_task);
		जाओ out_reenable;
	पूर्ण

	अगर (पूर्णांकrstat & INTR_TMINTR) अणु
		jग_लिखो32(jme, JME_IEVE, INTR_TMINTR);
		tasklet_schedule(&jme->pcc_task);
	पूर्ण

	अगर (पूर्णांकrstat & (INTR_PCCTXTO | INTR_PCCTX)) अणु
		jग_लिखो32(jme, JME_IEVE, INTR_PCCTXTO | INTR_PCCTX | INTR_TX0);
		tasklet_schedule(&jme->txclean_task);
	पूर्ण

	अगर ((पूर्णांकrstat & (INTR_PCCRX0TO | INTR_PCCRX0 | INTR_RX0EMP))) अणु
		jग_लिखो32(jme, JME_IEVE, (पूर्णांकrstat & (INTR_PCCRX0TO |
						     INTR_PCCRX0 |
						     INTR_RX0EMP)) |
					INTR_RX0);
	पूर्ण

	अगर (test_bit(JME_FLAG_POLL, &jme->flags)) अणु
		अगर (पूर्णांकrstat & INTR_RX0EMP)
			atomic_inc(&jme->rx_empty);

		अगर ((पूर्णांकrstat & (INTR_PCCRX0TO | INTR_PCCRX0 | INTR_RX0EMP))) अणु
			अगर (likely(JME_RX_SCHEDULE_PREP(jme))) अणु
				jme_polling_mode(jme);
				JME_RX_SCHEDULE(jme);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (पूर्णांकrstat & INTR_RX0EMP) अणु
			atomic_inc(&jme->rx_empty);
			tasklet_hi_schedule(&jme->rxempty_task);
		पूर्ण अन्यथा अगर (पूर्णांकrstat & (INTR_PCCRX0TO | INTR_PCCRX0)) अणु
			tasklet_hi_schedule(&jme->rxclean_task);
		पूर्ण
	पूर्ण

out_reenable:
	/*
	 * Re-enable पूर्णांकerrupt
	 */
	jग_लिखो32f(jme, JME_IENS, INTR_ENABLE);
पूर्ण

अटल irqवापस_t
jme_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *netdev = dev_id;
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	u32 पूर्णांकrstat;

	पूर्णांकrstat = jपढ़ो32(jme, JME_IEVE);

	/*
	 * Check अगर it's really an पूर्णांकerrupt क्रम us
	 */
	अगर (unlikely((पूर्णांकrstat & INTR_ENABLE) == 0))
		वापस IRQ_NONE;

	/*
	 * Check अगर the device still exist
	 */
	अगर (unlikely(पूर्णांकrstat == ~((typeof(पूर्णांकrstat))0)))
		वापस IRQ_NONE;

	jme_पूर्णांकr_msi(jme, पूर्णांकrstat);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
jme_msi(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *netdev = dev_id;
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	u32 पूर्णांकrstat;

	पूर्णांकrstat = jपढ़ो32(jme, JME_IEVE);

	jme_पूर्णांकr_msi(jme, पूर्णांकrstat);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
jme_reset_link(काष्ठा jme_adapter *jme)
अणु
	jग_लिखो32(jme, JME_TMCSR, TMCSR_SWIT);
पूर्ण

अटल व्योम
jme_restart_an(काष्ठा jme_adapter *jme)
अणु
	u32 bmcr;

	spin_lock_bh(&jme->phy_lock);
	bmcr = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, MII_BMCR);
	bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, MII_BMCR, bmcr);
	spin_unlock_bh(&jme->phy_lock);
पूर्ण

अटल पूर्णांक
jme_request_irq(काष्ठा jme_adapter *jme)
अणु
	पूर्णांक rc;
	काष्ठा net_device *netdev = jme->dev;
	irq_handler_t handler = jme_पूर्णांकr;
	पूर्णांक irq_flags = IRQF_SHARED;

	अगर (!pci_enable_msi(jme->pdev)) अणु
		set_bit(JME_FLAG_MSI, &jme->flags);
		handler = jme_msi;
		irq_flags = 0;
	पूर्ण

	rc = request_irq(jme->pdev->irq, handler, irq_flags, netdev->name,
			  netdev);
	अगर (rc) अणु
		netdev_err(netdev,
			   "Unable to request %s interrupt (return: %d)\n",
			   test_bit(JME_FLAG_MSI, &jme->flags) ? "MSI" : "INTx",
			   rc);

		अगर (test_bit(JME_FLAG_MSI, &jme->flags)) अणु
			pci_disable_msi(jme->pdev);
			clear_bit(JME_FLAG_MSI, &jme->flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev->irq = jme->pdev->irq;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम
jme_मुक्त_irq(काष्ठा jme_adapter *jme)
अणु
	मुक्त_irq(jme->pdev->irq, jme->dev);
	अगर (test_bit(JME_FLAG_MSI, &jme->flags)) अणु
		pci_disable_msi(jme->pdev);
		clear_bit(JME_FLAG_MSI, &jme->flags);
		jme->dev->irq = jme->pdev->irq;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
jme_new_phy_on(काष्ठा jme_adapter *jme)
अणु
	u32 reg;

	reg = jपढ़ो32(jme, JME_PHY_PWR);
	reg &= ~(PHY_PWR_DWN1SEL | PHY_PWR_DWN1SW |
		 PHY_PWR_DWN2 | PHY_PWR_CLKSEL);
	jग_लिखो32(jme, JME_PHY_PWR, reg);

	pci_पढ़ो_config_dword(jme->pdev, PCI_PRIV_PE1, &reg);
	reg &= ~PE1_GPREG0_PBG;
	reg |= PE1_GPREG0_ENBG;
	pci_ग_लिखो_config_dword(jme->pdev, PCI_PRIV_PE1, reg);
पूर्ण

अटल अंतरभूत व्योम
jme_new_phy_off(काष्ठा jme_adapter *jme)
अणु
	u32 reg;

	reg = jपढ़ो32(jme, JME_PHY_PWR);
	reg |= PHY_PWR_DWN1SEL | PHY_PWR_DWN1SW |
	       PHY_PWR_DWN2 | PHY_PWR_CLKSEL;
	jग_लिखो32(jme, JME_PHY_PWR, reg);

	pci_पढ़ो_config_dword(jme->pdev, PCI_PRIV_PE1, &reg);
	reg &= ~PE1_GPREG0_PBG;
	reg |= PE1_GPREG0_PDD3COLD;
	pci_ग_लिखो_config_dword(jme->pdev, PCI_PRIV_PE1, reg);
पूर्ण

अटल अंतरभूत व्योम
jme_phy_on(काष्ठा jme_adapter *jme)
अणु
	u32 bmcr;

	bmcr = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, MII_BMCR);
	bmcr &= ~BMCR_PDOWN;
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, MII_BMCR, bmcr);

	अगर (new_phy_घातer_ctrl(jme->chip_मुख्य_rev))
		jme_new_phy_on(jme);
पूर्ण

अटल अंतरभूत व्योम
jme_phy_off(काष्ठा jme_adapter *jme)
अणु
	u32 bmcr;

	bmcr = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, MII_BMCR);
	bmcr |= BMCR_PDOWN;
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, MII_BMCR, bmcr);

	अगर (new_phy_घातer_ctrl(jme->chip_मुख्य_rev))
		jme_new_phy_off(jme);
पूर्ण

अटल पूर्णांक
jme_phy_specreg_पढ़ो(काष्ठा jme_adapter *jme, u32 specreg)
अणु
	u32 phy_addr;

	phy_addr = JM_PHY_SPEC_REG_READ | specreg;
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, JM_PHY_SPEC_ADDR_REG,
			phy_addr);
	वापस jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id,
			JM_PHY_SPEC_DATA_REG);
पूर्ण

अटल व्योम
jme_phy_specreg_ग_लिखो(काष्ठा jme_adapter *jme, u32 ext_reg, u32 phy_data)
अणु
	u32 phy_addr;

	phy_addr = JM_PHY_SPEC_REG_WRITE | ext_reg;
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, JM_PHY_SPEC_DATA_REG,
			phy_data);
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, JM_PHY_SPEC_ADDR_REG,
			phy_addr);
पूर्ण

अटल पूर्णांक
jme_phy_calibration(काष्ठा jme_adapter *jme)
अणु
	u32 ctrl1000, phy_data;

	jme_phy_off(jme);
	jme_phy_on(jme);
	/*  Enabel PHY test mode 1 */
	ctrl1000 = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, MII_CTRL1000);
	ctrl1000 &= ~PHY_GAD_TEST_MODE_MSK;
	ctrl1000 |= PHY_GAD_TEST_MODE_1;
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, MII_CTRL1000, ctrl1000);

	phy_data = jme_phy_specreg_पढ़ो(jme, JM_PHY_EXT_COMM_2_REG);
	phy_data &= ~JM_PHY_EXT_COMM_2_CALI_MODE_0;
	phy_data |= JM_PHY_EXT_COMM_2_CALI_LATCH |
			JM_PHY_EXT_COMM_2_CALI_ENABLE;
	jme_phy_specreg_ग_लिखो(jme, JM_PHY_EXT_COMM_2_REG, phy_data);
	msleep(20);
	phy_data = jme_phy_specreg_पढ़ो(jme, JM_PHY_EXT_COMM_2_REG);
	phy_data &= ~(JM_PHY_EXT_COMM_2_CALI_ENABLE |
			JM_PHY_EXT_COMM_2_CALI_MODE_0 |
			JM_PHY_EXT_COMM_2_CALI_LATCH);
	jme_phy_specreg_ग_लिखो(jme, JM_PHY_EXT_COMM_2_REG, phy_data);

	/*  Disable PHY test mode */
	ctrl1000 = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, MII_CTRL1000);
	ctrl1000 &= ~PHY_GAD_TEST_MODE_MSK;
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, MII_CTRL1000, ctrl1000);
	वापस 0;
पूर्ण

अटल पूर्णांक
jme_phy_setEA(काष्ठा jme_adapter *jme)
अणु
	u32 phy_comm0 = 0, phy_comm1 = 0;
	u8 nic_ctrl;

	pci_पढ़ो_config_byte(jme->pdev, PCI_PRIV_SHARE_NICCTRL, &nic_ctrl);
	अगर ((nic_ctrl & 0x3) == JME_FLAG_PHYEA_ENABLE)
		वापस 0;

	चयन (jme->pdev->device) अणु
	हाल PCI_DEVICE_ID_JMICRON_JMC250:
		अगर (((jme->chip_मुख्य_rev == 5) &&
			((jme->chip_sub_rev == 0) || (jme->chip_sub_rev == 1) ||
			(jme->chip_sub_rev == 3))) ||
			(jme->chip_मुख्य_rev >= 6)) अणु
			phy_comm0 = 0x008A;
			phy_comm1 = 0x4109;
		पूर्ण
		अगर ((jme->chip_मुख्य_rev == 3) &&
			((jme->chip_sub_rev == 1) || (jme->chip_sub_rev == 2)))
			phy_comm0 = 0xE088;
		अवरोध;
	हाल PCI_DEVICE_ID_JMICRON_JMC260:
		अगर (((jme->chip_मुख्य_rev == 5) &&
			((jme->chip_sub_rev == 0) || (jme->chip_sub_rev == 1) ||
			(jme->chip_sub_rev == 3))) ||
			(jme->chip_मुख्य_rev >= 6)) अणु
			phy_comm0 = 0x008A;
			phy_comm1 = 0x4109;
		पूर्ण
		अगर ((jme->chip_मुख्य_rev == 3) &&
			((jme->chip_sub_rev == 1) || (jme->chip_sub_rev == 2)))
			phy_comm0 = 0xE088;
		अगर ((jme->chip_मुख्य_rev == 2) && (jme->chip_sub_rev == 0))
			phy_comm0 = 0x608A;
		अगर ((jme->chip_मुख्य_rev == 2) && (jme->chip_sub_rev == 2))
			phy_comm0 = 0x408A;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	अगर (phy_comm0)
		jme_phy_specreg_ग_लिखो(jme, JM_PHY_EXT_COMM_0_REG, phy_comm0);
	अगर (phy_comm1)
		jme_phy_specreg_ग_लिखो(jme, JM_PHY_EXT_COMM_1_REG, phy_comm1);

	वापस 0;
पूर्ण

अटल पूर्णांक
jme_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	पूर्णांक rc;

	jme_clear_pm_disable_wol(jme);
	JME_NAPI_ENABLE(jme);

	tasklet_setup(&jme->txclean_task, jme_tx_clean_tasklet);
	tasklet_setup(&jme->rxclean_task, jme_rx_clean_tasklet);
	tasklet_setup(&jme->rxempty_task, jme_rx_empty_tasklet);

	rc = jme_request_irq(jme);
	अगर (rc)
		जाओ err_out;

	jme_start_irq(jme);

	jme_phy_on(jme);
	अगर (test_bit(JME_FLAG_SSET, &jme->flags))
		jme_set_link_ksettings(netdev, &jme->old_cmd);
	अन्यथा
		jme_reset_phy_processor(jme);
	jme_phy_calibration(jme);
	jme_phy_setEA(jme);
	jme_reset_link(jme);

	वापस 0;

err_out:
	netअगर_stop_queue(netdev);
	netअगर_carrier_off(netdev);
	वापस rc;
पूर्ण

अटल व्योम
jme_set_100m_half(काष्ठा jme_adapter *jme)
अणु
	u32 bmcr, पंचांगp;

	jme_phy_on(jme);
	bmcr = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, MII_BMCR);
	पंचांगp = bmcr & ~(BMCR_ANENABLE | BMCR_SPEED100 |
		       BMCR_SPEED1000 | BMCR_FULLDPLX);
	पंचांगp |= BMCR_SPEED100;

	अगर (bmcr != पंचांगp)
		jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, MII_BMCR, पंचांगp);

	अगर (jme->fpgaver)
		jग_लिखो32(jme, JME_GHC, GHC_SPEED_100M | GHC_LINK_POLL);
	अन्यथा
		jग_लिखो32(jme, JME_GHC, GHC_SPEED_100M);
पूर्ण

#घोषणा JME_WAIT_LINK_TIME 2000 /* 2000ms */
अटल व्योम
jme_रुको_link(काष्ठा jme_adapter *jme)
अणु
	u32 phylink, to = JME_WAIT_LINK_TIME;

	msleep(1000);
	phylink = jme_linkstat_from_phy(jme);
	जबतक (!(phylink & PHY_LINK_UP) && (to -= 10) > 0) अणु
		usleep_range(10000, 11000);
		phylink = jme_linkstat_from_phy(jme);
	पूर्ण
पूर्ण

अटल व्योम
jme_घातersave_phy(काष्ठा jme_adapter *jme)
अणु
	अगर (jme->reg_pmcs && device_may_wakeup(&jme->pdev->dev)) अणु
		jme_set_100m_half(jme);
		अगर (jme->reg_pmcs & (PMCS_LFEN | PMCS_LREN))
			jme_रुको_link(jme);
		jme_clear_pm_enable_wol(jme);
	पूर्ण अन्यथा अणु
		jme_phy_off(jme);
	पूर्ण
पूर्ण

अटल पूर्णांक
jme_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	netअगर_stop_queue(netdev);
	netअगर_carrier_off(netdev);

	jme_stop_irq(jme);
	jme_मुक्त_irq(jme);

	JME_NAPI_DISABLE(jme);

	cancel_work_sync(&jme->linkch_task);
	tasklet_समाप्त(&jme->txclean_task);
	tasklet_समाप्त(&jme->rxclean_task);
	tasklet_समाप्त(&jme->rxempty_task);

	jme_disable_rx_engine(jme);
	jme_disable_tx_engine(jme);
	jme_reset_mac_processor(jme);
	jme_मुक्त_rx_resources(jme);
	jme_मुक्त_tx_resources(jme);
	jme->phylink = 0;
	jme_phy_off(jme);

	वापस 0;
पूर्ण

अटल पूर्णांक
jme_alloc_txdesc(काष्ठा jme_adapter *jme,
			काष्ठा sk_buff *skb)
अणु
	काष्ठा jme_ring *txring = &(jme->txring[0]);
	पूर्णांक idx, nr_alloc, mask = jme->tx_ring_mask;

	idx = txring->next_to_use;
	nr_alloc = skb_shinfo(skb)->nr_frags + 2;

	अगर (unlikely(atomic_पढ़ो(&txring->nr_मुक्त) < nr_alloc))
		वापस -1;

	atomic_sub(nr_alloc, &txring->nr_मुक्त);

	txring->next_to_use = (txring->next_to_use + nr_alloc) & mask;

	वापस idx;
पूर्ण

अटल पूर्णांक
jme_fill_tx_map(काष्ठा pci_dev *pdev,
		काष्ठा txdesc *txdesc,
		काष्ठा jme_buffer_info *txbi,
		काष्ठा page *page,
		u32 page_offset,
		u32 len,
		bool hidma)
अणु
	dma_addr_t dmaaddr;

	dmaaddr = pci_map_page(pdev,
				page,
				page_offset,
				len,
				PCI_DMA_TODEVICE);

	अगर (unlikely(pci_dma_mapping_error(pdev, dmaaddr)))
		वापस -EINVAL;

	pci_dma_sync_single_क्रम_device(pdev,
				       dmaaddr,
				       len,
				       PCI_DMA_TODEVICE);

	txdesc->dw[0] = 0;
	txdesc->dw[1] = 0;
	txdesc->desc2.flags	= TXFLAG_OWN;
	txdesc->desc2.flags	|= (hidma) ? TXFLAG_64BIT : 0;
	txdesc->desc2.datalen	= cpu_to_le16(len);
	txdesc->desc2.bufaddrh	= cpu_to_le32((__u64)dmaaddr >> 32);
	txdesc->desc2.bufaddrl	= cpu_to_le32(
					(__u64)dmaaddr & 0xFFFFFFFFUL);

	txbi->mapping = dmaaddr;
	txbi->len = len;
	वापस 0;
पूर्ण

अटल व्योम jme_drop_tx_map(काष्ठा jme_adapter *jme, पूर्णांक startidx, पूर्णांक count)
अणु
	काष्ठा jme_ring *txring = &(jme->txring[0]);
	काष्ठा jme_buffer_info *txbi = txring->bufinf, *ctxbi;
	पूर्णांक mask = jme->tx_ring_mask;
	पूर्णांक j;

	क्रम (j = 0 ; j < count ; j++) अणु
		ctxbi = txbi + ((startidx + j + 2) & (mask));
		pci_unmap_page(jme->pdev,
				ctxbi->mapping,
				ctxbi->len,
				PCI_DMA_TODEVICE);

		ctxbi->mapping = 0;
		ctxbi->len = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
jme_map_tx_skb(काष्ठा jme_adapter *jme, काष्ठा sk_buff *skb, पूर्णांक idx)
अणु
	काष्ठा jme_ring *txring = &(jme->txring[0]);
	काष्ठा txdesc *txdesc = txring->desc, *ctxdesc;
	काष्ठा jme_buffer_info *txbi = txring->bufinf, *ctxbi;
	bool hidma = jme->dev->features & NETIF_F_HIGHDMA;
	पूर्णांक i, nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक mask = jme->tx_ring_mask;
	u32 len;
	पूर्णांक ret = 0;

	क्रम (i = 0 ; i < nr_frags ; ++i) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		ctxdesc = txdesc + ((idx + i + 2) & (mask));
		ctxbi = txbi + ((idx + i + 2) & (mask));

		ret = jme_fill_tx_map(jme->pdev, ctxdesc, ctxbi,
				      skb_frag_page(frag), skb_frag_off(frag),
				      skb_frag_size(frag), hidma);
		अगर (ret) अणु
			jme_drop_tx_map(jme, idx, i);
			जाओ out;
		पूर्ण
	पूर्ण

	len = skb_is_nonlinear(skb) ? skb_headlen(skb) : skb->len;
	ctxdesc = txdesc + ((idx + 1) & (mask));
	ctxbi = txbi + ((idx + 1) & (mask));
	ret = jme_fill_tx_map(jme->pdev, ctxdesc, ctxbi, virt_to_page(skb->data),
			offset_in_page(skb->data), len, hidma);
	अगर (ret)
		jme_drop_tx_map(jme, idx, i);

out:
	वापस ret;

पूर्ण


अटल पूर्णांक
jme_tx_tso(काष्ठा sk_buff *skb, __le16 *mss, u8 *flags)
अणु
	*mss = cpu_to_le16(skb_shinfo(skb)->gso_size << TXDESC_MSS_SHIFT);
	अगर (*mss) अणु
		*flags |= TXFLAG_LSEN;

		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			काष्ठा iphdr *iph = ip_hdr(skb);

			iph->check = 0;
			tcp_hdr(skb)->check = ~csum_tcpudp_magic(iph->saddr,
								iph->daddr, 0,
								IPPROTO_TCP,
								0);
		पूर्ण अन्यथा अणु
			tcp_v6_gso_csum_prep(skb);
		पूर्ण

		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम
jme_tx_csum(काष्ठा jme_adapter *jme, काष्ठा sk_buff *skb, u8 *flags)
अणु
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		u8 ip_proto;

		चयन (skb->protocol) अणु
		हाल htons(ETH_P_IP):
			ip_proto = ip_hdr(skb)->protocol;
			अवरोध;
		हाल htons(ETH_P_IPV6):
			ip_proto = ipv6_hdr(skb)->nexthdr;
			अवरोध;
		शेष:
			ip_proto = 0;
			अवरोध;
		पूर्ण

		चयन (ip_proto) अणु
		हाल IPPROTO_TCP:
			*flags |= TXFLAG_TCPCS;
			अवरोध;
		हाल IPPROTO_UDP:
			*flags |= TXFLAG_UDPCS;
			अवरोध;
		शेष:
			netअगर_err(jme, tx_err, jme->dev, "Error upper layer protocol\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
jme_tx_vlan(काष्ठा sk_buff *skb, __le16 *vlan, u8 *flags)
अणु
	अगर (skb_vlan_tag_present(skb)) अणु
		*flags |= TXFLAG_TAGON;
		*vlan = cpu_to_le16(skb_vlan_tag_get(skb));
	पूर्ण
पूर्ण

अटल पूर्णांक
jme_fill_tx_desc(काष्ठा jme_adapter *jme, काष्ठा sk_buff *skb, पूर्णांक idx)
अणु
	काष्ठा jme_ring *txring = &(jme->txring[0]);
	काष्ठा txdesc *txdesc;
	काष्ठा jme_buffer_info *txbi;
	u8 flags;
	पूर्णांक ret = 0;

	txdesc = (काष्ठा txdesc *)txring->desc + idx;
	txbi = txring->bufinf + idx;

	txdesc->dw[0] = 0;
	txdesc->dw[1] = 0;
	txdesc->dw[2] = 0;
	txdesc->dw[3] = 0;
	txdesc->desc1.pktsize = cpu_to_le16(skb->len);
	/*
	 * Set OWN bit at final.
	 * When kernel transmit faster than NIC.
	 * And NIC trying to send this descriptor beक्रमe we tell
	 * it to start sending this TX queue.
	 * Other fields are alपढ़ोy filled correctly.
	 */
	wmb();
	flags = TXFLAG_OWN | TXFLAG_INT;
	/*
	 * Set checksum flags जबतक not tso
	 */
	अगर (jme_tx_tso(skb, &txdesc->desc1.mss, &flags))
		jme_tx_csum(jme, skb, &flags);
	jme_tx_vlan(skb, &txdesc->desc1.vlan, &flags);
	ret = jme_map_tx_skb(jme, skb, idx);
	अगर (ret)
		वापस ret;

	txdesc->desc1.flags = flags;
	/*
	 * Set tx buffer info after telling NIC to send
	 * For better tx_clean timing
	 */
	wmb();
	txbi->nr_desc = skb_shinfo(skb)->nr_frags + 2;
	txbi->skb = skb;
	txbi->len = skb->len;
	txbi->start_xmit = jअगरfies;
	अगर (!txbi->start_xmit)
		txbi->start_xmit = (0UL-1);

	वापस 0;
पूर्ण

अटल व्योम
jme_stop_queue_अगर_full(काष्ठा jme_adapter *jme)
अणु
	काष्ठा jme_ring *txring = &(jme->txring[0]);
	काष्ठा jme_buffer_info *txbi = txring->bufinf;
	पूर्णांक idx = atomic_पढ़ो(&txring->next_to_clean);

	txbi += idx;

	smp_wmb();
	अगर (unlikely(atomic_पढ़ो(&txring->nr_मुक्त) < (MAX_SKB_FRAGS+2))) अणु
		netअगर_stop_queue(jme->dev);
		netअगर_info(jme, tx_queued, jme->dev, "TX Queue Paused\n");
		smp_wmb();
		अगर (atomic_पढ़ो(&txring->nr_मुक्त)
			>= (jme->tx_wake_threshold)) अणु
			netअगर_wake_queue(jme->dev);
			netअगर_info(jme, tx_queued, jme->dev, "TX Queue Fast Waked\n");
		पूर्ण
	पूर्ण

	अगर (unlikely(txbi->start_xmit &&
			(jअगरfies - txbi->start_xmit) >= TX_TIMEOUT &&
			txbi->skb)) अणु
		netअगर_stop_queue(jme->dev);
		netअगर_info(jme, tx_queued, jme->dev,
			   "TX Queue Stopped %d@%lu\n", idx, jअगरfies);
	पूर्ण
पूर्ण

/*
 * This function is alपढ़ोy रक्षित by netअगर_tx_lock()
 */

अटल netdev_tx_t
jme_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	पूर्णांक idx;

	अगर (unlikely(skb_is_gso(skb) && skb_cow_head(skb, 0))) अणु
		dev_kमुक्त_skb_any(skb);
		++(NET_STAT(jme).tx_dropped);
		वापस NETDEV_TX_OK;
	पूर्ण

	idx = jme_alloc_txdesc(jme, skb);

	अगर (unlikely(idx < 0)) अणु
		netअगर_stop_queue(netdev);
		netअगर_err(jme, tx_err, jme->dev,
			  "BUG! Tx ring full when queue awake!\n");

		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (jme_fill_tx_desc(jme, skb, idx))
		वापस NETDEV_TX_OK;

	jग_लिखो32(jme, JME_TXCS, jme->reg_txcs |
				TXCS_SELECT_QUEUE0 |
				TXCS_QUEUE0S |
				TXCS_ENABLE);

	tx_dbg(jme, "xmit: %d+%d@%lu\n",
	       idx, skb_shinfo(skb)->nr_frags + 2, jअगरfies);
	jme_stop_queue_अगर_full(jme);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम
jme_set_unicastaddr(काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	u32 val;

	val = (netdev->dev_addr[3] & 0xff) << 24 |
	      (netdev->dev_addr[2] & 0xff) << 16 |
	      (netdev->dev_addr[1] & 0xff) <<  8 |
	      (netdev->dev_addr[0] & 0xff);
	jग_लिखो32(jme, JME_RXUMA_LO, val);
	val = (netdev->dev_addr[5] & 0xff) << 8 |
	      (netdev->dev_addr[4] & 0xff);
	jग_लिखो32(jme, JME_RXUMA_HI, val);
पूर्ण

अटल पूर्णांक
jme_set_macaddr(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	spin_lock_bh(&jme->macaddr_lock);
	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	jme_set_unicastaddr(netdev);
	spin_unlock_bh(&jme->macaddr_lock);

	वापस 0;
पूर्ण

अटल व्योम
jme_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	u32 mc_hash[2] = अणुपूर्ण;

	spin_lock_bh(&jme->rxmcs_lock);

	jme->reg_rxmcs |= RXMCS_BRDFRAME | RXMCS_UNIFRAME;

	अगर (netdev->flags & IFF_PROMISC) अणु
		jme->reg_rxmcs |= RXMCS_ALLFRAME;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_ALLMULTI) अणु
		jme->reg_rxmcs |= RXMCS_ALLMULFRAME;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_MULTICAST) अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक bit_nr;

		jme->reg_rxmcs |= RXMCS_MULFRAME | RXMCS_MULFILTERED;
		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			bit_nr = ether_crc(ETH_ALEN, ha->addr) & 0x3F;
			mc_hash[bit_nr >> 5] |= 1 << (bit_nr & 0x1F);
		पूर्ण

		jग_लिखो32(jme, JME_RXMCHT_LO, mc_hash[0]);
		jग_लिखो32(jme, JME_RXMCHT_HI, mc_hash[1]);
	पूर्ण

	wmb();
	jग_लिखो32(jme, JME_RXMCS, jme->reg_rxmcs);

	spin_unlock_bh(&jme->rxmcs_lock);
पूर्ण

अटल पूर्णांक
jme_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	netdev->mtu = new_mtu;
	netdev_update_features(netdev);

	jme_restart_rx_engine(jme);
	jme_reset_link(jme);

	वापस 0;
पूर्ण

अटल व्योम
jme_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	jme->phylink = 0;
	jme_reset_phy_processor(jme);
	अगर (test_bit(JME_FLAG_SSET, &jme->flags))
		jme_set_link_ksettings(netdev, &jme->old_cmd);

	/*
	 * Force to Reset the link again
	 */
	jme_reset_link(jme);
पूर्ण

अटल व्योम
jme_get_drvinfo(काष्ठा net_device *netdev,
		     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(jme->pdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक
jme_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस JME_REG_LEN;
पूर्ण

अटल व्योम
mmapio_स_नकल(काष्ठा jme_adapter *jme, u32 *p, u32 reg, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < len ; i += 4)
		p[i >> 2] = jपढ़ो32(jme, reg + i);
पूर्ण

अटल व्योम
mdio_स_नकल(काष्ठा jme_adapter *jme, u32 *p, पूर्णांक reg_nr)
अणु
	पूर्णांक i;
	u16 *p16 = (u16 *)p;

	क्रम (i = 0 ; i < reg_nr ; ++i)
		p16[i] = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, i);
पूर्ण

अटल व्योम
jme_get_regs(काष्ठा net_device *netdev, काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	u32 *p32 = (u32 *)p;

	स_रखो(p, 0xFF, JME_REG_LEN);

	regs->version = 1;
	mmapio_स_नकल(jme, p32, JME_MAC, JME_MAC_LEN);

	p32 += 0x100 >> 2;
	mmapio_स_नकल(jme, p32, JME_PHY, JME_PHY_LEN);

	p32 += 0x100 >> 2;
	mmapio_स_नकल(jme, p32, JME_MISC, JME_MISC_LEN);

	p32 += 0x100 >> 2;
	mmapio_स_नकल(jme, p32, JME_RSS, JME_RSS_LEN);

	p32 += 0x100 >> 2;
	mdio_स_नकल(jme, p32, JME_PHY_REG_NR);
पूर्ण

अटल पूर्णांक
jme_get_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	ecmd->tx_coalesce_usecs = PCC_TX_TO;
	ecmd->tx_max_coalesced_frames = PCC_TX_CNT;

	अगर (test_bit(JME_FLAG_POLL, &jme->flags)) अणु
		ecmd->use_adaptive_rx_coalesce = false;
		ecmd->rx_coalesce_usecs = 0;
		ecmd->rx_max_coalesced_frames = 0;
		वापस 0;
	पूर्ण

	ecmd->use_adaptive_rx_coalesce = true;

	चयन (jme->dpi.cur) अणु
	हाल PCC_P1:
		ecmd->rx_coalesce_usecs = PCC_P1_TO;
		ecmd->rx_max_coalesced_frames = PCC_P1_CNT;
		अवरोध;
	हाल PCC_P2:
		ecmd->rx_coalesce_usecs = PCC_P2_TO;
		ecmd->rx_max_coalesced_frames = PCC_P2_CNT;
		अवरोध;
	हाल PCC_P3:
		ecmd->rx_coalesce_usecs = PCC_P3_TO;
		ecmd->rx_max_coalesced_frames = PCC_P3_CNT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
jme_set_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	काष्ठा dynpcc_info *dpi = &(jme->dpi);

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	अगर (ecmd->use_adaptive_rx_coalesce &&
	    test_bit(JME_FLAG_POLL, &jme->flags)) अणु
		clear_bit(JME_FLAG_POLL, &jme->flags);
		jme->jme_rx = netअगर_rx;
		dpi->cur		= PCC_P1;
		dpi->attempt		= PCC_P1;
		dpi->cnt		= 0;
		jme_set_rx_pcc(jme, PCC_P1);
		jme_पूर्णांकerrupt_mode(jme);
	पूर्ण अन्यथा अगर (!(ecmd->use_adaptive_rx_coalesce) &&
		   !(test_bit(JME_FLAG_POLL, &jme->flags))) अणु
		set_bit(JME_FLAG_POLL, &jme->flags);
		jme->jme_rx = netअगर_receive_skb;
		jme_पूर्णांकerrupt_mode(jme);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
jme_get_छोड़ोparam(काष्ठा net_device *netdev,
			काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	u32 val;

	ecmd->tx_छोड़ो = (jme->reg_txpfc & TXPFC_PF_EN) != 0;
	ecmd->rx_छोड़ो = (jme->reg_rxmcs & RXMCS_FLOWCTRL) != 0;

	spin_lock_bh(&jme->phy_lock);
	val = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, MII_ADVERTISE);
	spin_unlock_bh(&jme->phy_lock);

	ecmd->स्वतःneg =
		(val & (ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM)) != 0;
पूर्ण

अटल पूर्णांक
jme_set_छोड़ोparam(काष्ठा net_device *netdev,
			काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	u32 val;

	अगर (((jme->reg_txpfc & TXPFC_PF_EN) != 0) ^
		(ecmd->tx_छोड़ो != 0)) अणु

		अगर (ecmd->tx_छोड़ो)
			jme->reg_txpfc |= TXPFC_PF_EN;
		अन्यथा
			jme->reg_txpfc &= ~TXPFC_PF_EN;

		jग_लिखो32(jme, JME_TXPFC, jme->reg_txpfc);
	पूर्ण

	spin_lock_bh(&jme->rxmcs_lock);
	अगर (((jme->reg_rxmcs & RXMCS_FLOWCTRL) != 0) ^
		(ecmd->rx_छोड़ो != 0)) अणु

		अगर (ecmd->rx_छोड़ो)
			jme->reg_rxmcs |= RXMCS_FLOWCTRL;
		अन्यथा
			jme->reg_rxmcs &= ~RXMCS_FLOWCTRL;

		jग_लिखो32(jme, JME_RXMCS, jme->reg_rxmcs);
	पूर्ण
	spin_unlock_bh(&jme->rxmcs_lock);

	spin_lock_bh(&jme->phy_lock);
	val = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, MII_ADVERTISE);
	अगर (((val & (ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM)) != 0) ^
		(ecmd->स्वतःneg != 0)) अणु

		अगर (ecmd->स्वतःneg)
			val |= (ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);
		अन्यथा
			val &= ~(ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);

		jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id,
				MII_ADVERTISE, val);
	पूर्ण
	spin_unlock_bh(&jme->phy_lock);

	वापस 0;
पूर्ण

अटल व्योम
jme_get_wol(काष्ठा net_device *netdev,
		काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	wol->supported = WAKE_MAGIC | WAKE_PHY;

	wol->wolopts = 0;

	अगर (jme->reg_pmcs & (PMCS_LFEN | PMCS_LREN))
		wol->wolopts |= WAKE_PHY;

	अगर (jme->reg_pmcs & PMCS_MFEN)
		wol->wolopts |= WAKE_MAGIC;

पूर्ण

अटल पूर्णांक
jme_set_wol(काष्ठा net_device *netdev,
		काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	अगर (wol->wolopts & (WAKE_MAGICSECURE |
				WAKE_UCAST |
				WAKE_MCAST |
				WAKE_BCAST |
				WAKE_ARP))
		वापस -EOPNOTSUPP;

	jme->reg_pmcs = 0;

	अगर (wol->wolopts & WAKE_PHY)
		jme->reg_pmcs |= PMCS_LFEN | PMCS_LREN;

	अगर (wol->wolopts & WAKE_MAGIC)
		jme->reg_pmcs |= PMCS_MFEN;

	वापस 0;
पूर्ण

अटल पूर्णांक
jme_get_link_ksettings(काष्ठा net_device *netdev,
		       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	spin_lock_bh(&jme->phy_lock);
	mii_ethtool_get_link_ksettings(&jme->mii_अगर, cmd);
	spin_unlock_bh(&jme->phy_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
jme_set_link_ksettings(काष्ठा net_device *netdev,
		       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	पूर्णांक rc, fdc = 0;

	अगर (cmd->base.speed == SPEED_1000 &&
	    cmd->base.स्वतःneg != AUTONEG_ENABLE)
		वापस -EINVAL;

	/*
	 * Check If user changed duplex only जबतक क्रमce_media.
	 * Hardware would not generate link change पूर्णांकerrupt.
	 */
	अगर (jme->mii_अगर.क्रमce_media &&
	    cmd->base.स्वतःneg != AUTONEG_ENABLE &&
	    (jme->mii_अगर.full_duplex != cmd->base.duplex))
		fdc = 1;

	spin_lock_bh(&jme->phy_lock);
	rc = mii_ethtool_set_link_ksettings(&jme->mii_अगर, cmd);
	spin_unlock_bh(&jme->phy_lock);

	अगर (!rc) अणु
		अगर (fdc)
			jme_reset_link(jme);
		jme->old_cmd = *cmd;
		set_bit(JME_FLAG_SSET, &jme->flags);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
jme_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	पूर्णांक rc;
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	काष्ठा mii_ioctl_data *mii_data = अगर_mii(rq);
	अचिन्हित पूर्णांक duplex_chg;

	अगर (cmd == SIOCSMIIREG) अणु
		u16 val = mii_data->val_in;
		अगर (!(val & (BMCR_RESET|BMCR_ANENABLE)) &&
		    (val & BMCR_SPEED1000))
			वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&jme->phy_lock);
	rc = generic_mii_ioctl(&jme->mii_अगर, mii_data, cmd, &duplex_chg);
	spin_unlock_bh(&jme->phy_lock);

	अगर (!rc && (cmd == SIOCSMIIREG)) अणु
		अगर (duplex_chg)
			jme_reset_link(jme);
		jme_get_link_ksettings(netdev, &jme->old_cmd);
		set_bit(JME_FLAG_SSET, &jme->flags);
	पूर्ण

	वापस rc;
पूर्ण

अटल u32
jme_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	वापस jपढ़ो32(jme, JME_PHY_LINK) & PHY_LINK_UP;
पूर्ण

अटल u32
jme_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	वापस jme->msg_enable;
पूर्ण

अटल व्योम
jme_set_msglevel(काष्ठा net_device *netdev, u32 value)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	jme->msg_enable = value;
पूर्ण

अटल netdev_features_t
jme_fix_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	अगर (netdev->mtu > 1900)
		features &= ~(NETIF_F_ALL_TSO | NETIF_F_CSUM_MASK);
	वापस features;
पूर्ण

अटल पूर्णांक
jme_set_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	spin_lock_bh(&jme->rxmcs_lock);
	अगर (features & NETIF_F_RXCSUM)
		jme->reg_rxmcs |= RXMCS_CHECKSUM;
	अन्यथा
		jme->reg_rxmcs &= ~RXMCS_CHECKSUM;
	jग_लिखो32(jme, JME_RXMCS, jme->reg_rxmcs);
	spin_unlock_bh(&jme->rxmcs_lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम jme_netpoll(काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	jme_पूर्णांकr(dev->irq, dev);
	local_irq_restore(flags);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
jme_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	jme_restart_an(jme);
	वापस 0;
पूर्ण

अटल u8
jme_smb_पढ़ो(काष्ठा jme_adapter *jme, अचिन्हित पूर्णांक addr)
अणु
	u32 val;
	पूर्णांक to;

	val = jपढ़ो32(jme, JME_SMBCSR);
	to = JME_SMB_BUSY_TIMEOUT;
	जबतक ((val & SMBCSR_BUSY) && --to) अणु
		msleep(1);
		val = jपढ़ो32(jme, JME_SMBCSR);
	पूर्ण
	अगर (!to) अणु
		netअगर_err(jme, hw, jme->dev, "SMB Bus Busy\n");
		वापस 0xFF;
	पूर्ण

	jग_लिखो32(jme, JME_SMBINTF,
		((addr << SMBINTF_HWADDR_SHIFT) & SMBINTF_HWADDR) |
		SMBINTF_HWRWN_READ |
		SMBINTF_HWCMD);

	val = jपढ़ो32(jme, JME_SMBINTF);
	to = JME_SMB_BUSY_TIMEOUT;
	जबतक ((val & SMBINTF_HWCMD) && --to) अणु
		msleep(1);
		val = jपढ़ो32(jme, JME_SMBINTF);
	पूर्ण
	अगर (!to) अणु
		netअगर_err(jme, hw, jme->dev, "SMB Bus Busy\n");
		वापस 0xFF;
	पूर्ण

	वापस (val & SMBINTF_HWDATR) >> SMBINTF_HWDATR_SHIFT;
पूर्ण

अटल व्योम
jme_smb_ग_लिखो(काष्ठा jme_adapter *jme, अचिन्हित पूर्णांक addr, u8 data)
अणु
	u32 val;
	पूर्णांक to;

	val = jपढ़ो32(jme, JME_SMBCSR);
	to = JME_SMB_BUSY_TIMEOUT;
	जबतक ((val & SMBCSR_BUSY) && --to) अणु
		msleep(1);
		val = jपढ़ो32(jme, JME_SMBCSR);
	पूर्ण
	अगर (!to) अणु
		netअगर_err(jme, hw, jme->dev, "SMB Bus Busy\n");
		वापस;
	पूर्ण

	jग_लिखो32(jme, JME_SMBINTF,
		((data << SMBINTF_HWDATW_SHIFT) & SMBINTF_HWDATW) |
		((addr << SMBINTF_HWADDR_SHIFT) & SMBINTF_HWADDR) |
		SMBINTF_HWRWN_WRITE |
		SMBINTF_HWCMD);

	val = jपढ़ो32(jme, JME_SMBINTF);
	to = JME_SMB_BUSY_TIMEOUT;
	जबतक ((val & SMBINTF_HWCMD) && --to) अणु
		msleep(1);
		val = jपढ़ो32(jme, JME_SMBINTF);
	पूर्ण
	अगर (!to) अणु
		netअगर_err(jme, hw, jme->dev, "SMB Bus Busy\n");
		वापस;
	पूर्ण

	mdelay(2);
पूर्ण

अटल पूर्णांक
jme_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	u32 val;
	val = jपढ़ो32(jme, JME_SMBCSR);
	वापस (val & SMBCSR_EEPROMD) ? JME_SMB_LEN : 0;
पूर्ण

अटल पूर्णांक
jme_get_eeprom(काष्ठा net_device *netdev,
		काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	पूर्णांक i, offset = eeprom->offset, len = eeprom->len;

	/*
	 * ethtool will check the boundary क्रम us
	 */
	eeprom->magic = JME_EEPROM_MAGIC;
	क्रम (i = 0 ; i < len ; ++i)
		data[i] = jme_smb_पढ़ो(jme, i + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक
jme_set_eeprom(काष्ठा net_device *netdev,
		काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा jme_adapter *jme = netdev_priv(netdev);
	पूर्णांक i, offset = eeprom->offset, len = eeprom->len;

	अगर (eeprom->magic != JME_EEPROM_MAGIC)
		वापस -EINVAL;

	/*
	 * ethtool will check the boundary क्रम us
	 */
	क्रम (i = 0 ; i < len ; ++i)
		jme_smb_ग_लिखो(jme, i + offset, data[i]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops jme_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_drvinfo            = jme_get_drvinfo,
	.get_regs_len		= jme_get_regs_len,
	.get_regs		= jme_get_regs,
	.get_coalesce		= jme_get_coalesce,
	.set_coalesce		= jme_set_coalesce,
	.get_छोड़ोparam		= jme_get_छोड़ोparam,
	.set_छोड़ोparam		= jme_set_छोड़ोparam,
	.get_wol		= jme_get_wol,
	.set_wol		= jme_set_wol,
	.get_link		= jme_get_link,
	.get_msglevel           = jme_get_msglevel,
	.set_msglevel           = jme_set_msglevel,
	.nway_reset             = jme_nway_reset,
	.get_eeprom_len		= jme_get_eeprom_len,
	.get_eeprom		= jme_get_eeprom,
	.set_eeprom		= jme_set_eeprom,
	.get_link_ksettings	= jme_get_link_ksettings,
	.set_link_ksettings	= jme_set_link_ksettings,
पूर्ण;

अटल पूर्णांक
jme_pci_dma64(काष्ठा pci_dev *pdev)
अणु
	अगर (pdev->device == PCI_DEVICE_ID_JMICRON_JMC250 &&
	    !pci_set_dma_mask(pdev, DMA_BIT_MASK(64)))
		अगर (!pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64)))
			वापस 1;

	अगर (pdev->device == PCI_DEVICE_ID_JMICRON_JMC250 &&
	    !pci_set_dma_mask(pdev, DMA_BIT_MASK(40)))
		अगर (!pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(40)))
			वापस 1;

	अगर (!pci_set_dma_mask(pdev, DMA_BIT_MASK(32)))
		अगर (!pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32)))
			वापस 0;

	वापस -1;
पूर्ण

अटल अंतरभूत व्योम
jme_phy_init(काष्ठा jme_adapter *jme)
अणु
	u16 reg26;

	reg26 = jme_mdio_पढ़ो(jme->dev, jme->mii_अगर.phy_id, 26);
	jme_mdio_ग_लिखो(jme->dev, jme->mii_अगर.phy_id, 26, reg26 | 0x1000);
पूर्ण

अटल अंतरभूत व्योम
jme_check_hw_ver(काष्ठा jme_adapter *jme)
अणु
	u32 chipmode;

	chipmode = jपढ़ो32(jme, JME_CHIPMODE);

	jme->fpgaver = (chipmode & CM_FPGAVER_MASK) >> CM_FPGAVER_SHIFT;
	jme->chiprev = (chipmode & CM_CHIPREV_MASK) >> CM_CHIPREV_SHIFT;
	jme->chip_मुख्य_rev = jme->chiprev & 0xF;
	jme->chip_sub_rev = (jme->chiprev >> 4) & 0xF;
पूर्ण

अटल स्थिर काष्ठा net_device_ops jme_netdev_ops = अणु
	.nकरो_खोलो		= jme_खोलो,
	.nकरो_stop		= jme_बंद,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= jme_ioctl,
	.nकरो_start_xmit		= jme_start_xmit,
	.nकरो_set_mac_address	= jme_set_macaddr,
	.nकरो_set_rx_mode	= jme_set_multi,
	.nकरो_change_mtu		= jme_change_mtu,
	.nकरो_tx_समयout		= jme_tx_समयout,
	.nकरो_fix_features       = jme_fix_features,
	.nकरो_set_features       = jme_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= jme_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक
jme_init_one(काष्ठा pci_dev *pdev,
	     स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक rc = 0, using_dac, i;
	काष्ठा net_device *netdev;
	काष्ठा jme_adapter *jme;
	u16 bmcr, bmsr;
	u32 apmc;

	/*
	 * set up PCI device basics
	 */
	pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 |
			       PCIE_LINK_STATE_CLKPM);

	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		pr_err("Cannot enable PCI device\n");
		जाओ err_out;
	पूर्ण

	using_dac = jme_pci_dma64(pdev);
	अगर (using_dac < 0) अणु
		pr_err("Cannot set PCI DMA Mask\n");
		rc = -EIO;
		जाओ err_out_disable_pdev;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		pr_err("No PCI resource region found\n");
		rc = -ENOMEM;
		जाओ err_out_disable_pdev;
	पूर्ण

	rc = pci_request_regions(pdev, DRV_NAME);
	अगर (rc) अणु
		pr_err("Cannot obtain PCI resource region\n");
		जाओ err_out_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	/*
	 * alloc and init net device
	 */
	netdev = alloc_etherdev(माप(*jme));
	अगर (!netdev) अणु
		rc = -ENOMEM;
		जाओ err_out_release_regions;
	पूर्ण
	netdev->netdev_ops = &jme_netdev_ops;
	netdev->ethtool_ops		= &jme_ethtool_ops;
	netdev->watchकरोg_समयo		= TX_TIMEOUT;
	netdev->hw_features		=	NETIF_F_IP_CSUM |
						NETIF_F_IPV6_CSUM |
						NETIF_F_SG |
						NETIF_F_TSO |
						NETIF_F_TSO6 |
						NETIF_F_RXCSUM;
	netdev->features		=	NETIF_F_IP_CSUM |
						NETIF_F_IPV6_CSUM |
						NETIF_F_SG |
						NETIF_F_TSO |
						NETIF_F_TSO6 |
						NETIF_F_HW_VLAN_CTAG_TX |
						NETIF_F_HW_VLAN_CTAG_RX;
	अगर (using_dac)
		netdev->features	|=	NETIF_F_HIGHDMA;

	/* MTU range: 1280 - 9202*/
	netdev->min_mtu = IPV6_MIN_MTU;
	netdev->max_mtu = MAX_ETHERNET_JUMBO_PACKET_SIZE - ETH_HLEN;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_drvdata(pdev, netdev);

	/*
	 * init adapter info
	 */
	jme = netdev_priv(netdev);
	jme->pdev = pdev;
	jme->dev = netdev;
	jme->jme_rx = netअगर_rx;
	jme->old_mtu = netdev->mtu = 1500;
	jme->phylink = 0;
	jme->tx_ring_size = 1 << 10;
	jme->tx_ring_mask = jme->tx_ring_size - 1;
	jme->tx_wake_threshold = 1 << 9;
	jme->rx_ring_size = 1 << 9;
	jme->rx_ring_mask = jme->rx_ring_size - 1;
	jme->msg_enable = JME_DEF_MSG_ENABLE;
	jme->regs = ioremap(pci_resource_start(pdev, 0),
			     pci_resource_len(pdev, 0));
	अगर (!(jme->regs)) अणु
		pr_err("Mapping PCI resource region error\n");
		rc = -ENOMEM;
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	अगर (no_pseuकरोhp) अणु
		apmc = jपढ़ो32(jme, JME_APMC) & ~JME_APMC_PSEUDO_HP_EN;
		jग_लिखो32(jme, JME_APMC, apmc);
	पूर्ण अन्यथा अगर (क्रमce_pseuकरोhp) अणु
		apmc = jपढ़ो32(jme, JME_APMC) | JME_APMC_PSEUDO_HP_EN;
		jग_लिखो32(jme, JME_APMC, apmc);
	पूर्ण

	NETIF_NAPI_SET(netdev, &jme->napi, jme_poll, NAPI_POLL_WEIGHT)

	spin_lock_init(&jme->phy_lock);
	spin_lock_init(&jme->macaddr_lock);
	spin_lock_init(&jme->rxmcs_lock);

	atomic_set(&jme->link_changing, 1);
	atomic_set(&jme->rx_cleaning, 1);
	atomic_set(&jme->tx_cleaning, 1);
	atomic_set(&jme->rx_empty, 1);

	tasklet_setup(&jme->pcc_task, jme_pcc_tasklet);
	INIT_WORK(&jme->linkch_task, jme_link_change_work);
	jme->dpi.cur = PCC_P1;

	jme->reg_ghc = 0;
	jme->reg_rxcs = RXCS_DEFAULT;
	jme->reg_rxmcs = RXMCS_DEFAULT;
	jme->reg_txpfc = 0;
	jme->reg_pmcs = PMCS_MFEN;
	jme->reg_gpreg1 = GPREG1_DEFAULT;

	अगर (jme->reg_rxmcs & RXMCS_CHECKSUM)
		netdev->features |= NETIF_F_RXCSUM;

	/*
	 * Get Max Read Req Size from PCI Config Space
	 */
	pci_पढ़ो_config_byte(pdev, PCI_DCSR_MRRS, &jme->mrrs);
	jme->mrrs &= PCI_DCSR_MRRS_MASK;
	चयन (jme->mrrs) अणु
	हाल MRRS_128B:
		jme->reg_txcs = TXCS_DEFAULT | TXCS_DMASIZE_128B;
		अवरोध;
	हाल MRRS_256B:
		jme->reg_txcs = TXCS_DEFAULT | TXCS_DMASIZE_256B;
		अवरोध;
	शेष:
		jme->reg_txcs = TXCS_DEFAULT | TXCS_DMASIZE_512B;
		अवरोध;
	पूर्ण

	/*
	 * Must check beक्रमe reset_mac_processor
	 */
	jme_check_hw_ver(jme);
	jme->mii_अगर.dev = netdev;
	अगर (jme->fpgaver) अणु
		jme->mii_अगर.phy_id = 0;
		क्रम (i = 1 ; i < 32 ; ++i) अणु
			bmcr = jme_mdio_पढ़ो(netdev, i, MII_BMCR);
			bmsr = jme_mdio_पढ़ो(netdev, i, MII_BMSR);
			अगर (bmcr != 0xFFFFU && (bmcr != 0 || bmsr != 0)) अणु
				jme->mii_अगर.phy_id = i;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!jme->mii_अगर.phy_id) अणु
			rc = -EIO;
			pr_err("Can not find phy_id\n");
			जाओ err_out_unmap;
		पूर्ण

		jme->reg_ghc |= GHC_LINK_POLL;
	पूर्ण अन्यथा अणु
		jme->mii_अगर.phy_id = 1;
	पूर्ण
	अगर (pdev->device == PCI_DEVICE_ID_JMICRON_JMC250)
		jme->mii_अगर.supports_gmii = true;
	अन्यथा
		jme->mii_अगर.supports_gmii = false;
	jme->mii_अगर.phy_id_mask = 0x1F;
	jme->mii_अगर.reg_num_mask = 0x1F;
	jme->mii_अगर.mdio_पढ़ो = jme_mdio_पढ़ो;
	jme->mii_अगर.mdio_ग_लिखो = jme_mdio_ग_लिखो;

	jme_clear_pm_disable_wol(jme);
	device_init_wakeup(&pdev->dev, true);

	jme_set_phyfअगरo_5level(jme);
	jme->pcirev = pdev->revision;
	अगर (!jme->fpgaver)
		jme_phy_init(jme);
	jme_phy_off(jme);

	/*
	 * Reset MAC processor and reload EEPROM क्रम MAC Address
	 */
	jme_reset_mac_processor(jme);
	rc = jme_reload_eeprom(jme);
	अगर (rc) अणु
		pr_err("Reload eeprom for reading MAC Address error\n");
		जाओ err_out_unmap;
	पूर्ण
	jme_load_macaddr(netdev);

	/*
	 * Tell stack that we are not पढ़ोy to work until खोलो()
	 */
	netअगर_carrier_off(netdev);

	rc = रेजिस्टर_netdev(netdev);
	अगर (rc) अणु
		pr_err("Cannot register net device\n");
		जाओ err_out_unmap;
	पूर्ण

	netअगर_info(jme, probe, jme->dev, "%s%s chiprev:%x pcirev:%x macaddr:%pM\n",
		   (jme->pdev->device == PCI_DEVICE_ID_JMICRON_JMC250) ?
		   "JMC250 Gigabit Ethernet" :
		   (jme->pdev->device == PCI_DEVICE_ID_JMICRON_JMC260) ?
		   "JMC260 Fast Ethernet" : "Unknown",
		   (jme->fpgaver != 0) ? " (FPGA)" : "",
		   (jme->fpgaver != 0) ? jme->fpgaver : jme->chiprev,
		   jme->pcirev, netdev->dev_addr);

	वापस 0;

err_out_unmap:
	iounmap(jme->regs);
err_out_मुक्त_netdev:
	मुक्त_netdev(netdev);
err_out_release_regions:
	pci_release_regions(pdev);
err_out_disable_pdev:
	pci_disable_device(pdev);
err_out:
	वापस rc;
पूर्ण

अटल व्योम
jme_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	unरेजिस्टर_netdev(netdev);
	iounmap(jme->regs);
	मुक्त_netdev(netdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

पूर्ण

अटल व्योम
jme_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	jme_घातersave_phy(jme);
	pci_pme_active(pdev, true);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक
jme_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	अगर (!netअगर_running(netdev))
		वापस 0;

	atomic_dec(&jme->link_changing);

	netअगर_device_detach(netdev);
	netअगर_stop_queue(netdev);
	jme_stop_irq(jme);

	tasklet_disable(&jme->txclean_task);
	tasklet_disable(&jme->rxclean_task);
	tasklet_disable(&jme->rxempty_task);

	अगर (netअगर_carrier_ok(netdev)) अणु
		अगर (test_bit(JME_FLAG_POLL, &jme->flags))
			jme_polling_mode(jme);

		jme_stop_pcc_समयr(jme);
		jme_disable_rx_engine(jme);
		jme_disable_tx_engine(jme);
		jme_reset_mac_processor(jme);
		jme_मुक्त_rx_resources(jme);
		jme_मुक्त_tx_resources(jme);
		netअगर_carrier_off(netdev);
		jme->phylink = 0;
	पूर्ण

	tasklet_enable(&jme->txclean_task);
	tasklet_enable(&jme->rxclean_task);
	tasklet_enable(&jme->rxempty_task);

	jme_घातersave_phy(jme);

	वापस 0;
पूर्ण

अटल पूर्णांक
jme_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा jme_adapter *jme = netdev_priv(netdev);

	अगर (!netअगर_running(netdev))
		वापस 0;

	jme_clear_pm_disable_wol(jme);
	jme_phy_on(jme);
	अगर (test_bit(JME_FLAG_SSET, &jme->flags))
		jme_set_link_ksettings(netdev, &jme->old_cmd);
	अन्यथा
		jme_reset_phy_processor(jme);
	jme_phy_calibration(jme);
	jme_phy_setEA(jme);
	netअगर_device_attach(netdev);

	atomic_inc(&jme->link_changing);

	jme_reset_link(jme);

	jme_start_irq(jme);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(jme_pm_ops, jme_suspend, jme_resume);
#घोषणा JME_PM_OPS (&jme_pm_ops)

#अन्यथा

#घोषणा JME_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id jme_pci_tbl[] = अणु
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMC250) पूर्ण,
	अणु PCI_VDEVICE(JMICRON, PCI_DEVICE_ID_JMICRON_JMC260) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा pci_driver jme_driver = अणु
	.name           = DRV_NAME,
	.id_table       = jme_pci_tbl,
	.probe          = jme_init_one,
	.हटाओ         = jme_हटाओ_one,
	.shutकरोwn       = jme_shutकरोwn,
	.driver.pm	= JME_PM_OPS,
पूर्ण;

अटल पूर्णांक __init
jme_init_module(व्योम)
अणु
	pr_info("JMicron JMC2XX ethernet driver version %s\n", DRV_VERSION);
	वापस pci_रेजिस्टर_driver(&jme_driver);
पूर्ण

अटल व्योम __निकास
jme_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&jme_driver);
पूर्ण

module_init(jme_init_module);
module_निकास(jme_cleanup_module);

MODULE_AUTHOR("Guo-Fu Tseng <cooldavid@cooldavid.org>");
MODULE_DESCRIPTION("JMicron JMC2x0 PCI Express Ethernet driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_DEVICE_TABLE(pci, jme_pci_tbl);
