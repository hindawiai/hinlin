<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * New driver क्रम Marvell Yukon chipset and SysKonnect Gigabit
 * Ethernet adapters. Based on earlier sk98lin, e100 and
 * FreeBSD अगर_sk drivers.
 *
 * This driver पूर्णांकentionally करोes not support all the features
 * of the original driver such as link fail-over and link management because
 * those should be करोne at higher levels.
 *
 * Copyright (C) 2004, 2005 Stephen Hemminger <shemminger@osdl.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/delay.h>
#समावेश <linux/crc32.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mii.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmi.h>
#समावेश <linux/prefetch.h>
#समावेश <यंत्र/irq.h>

#समावेश "skge.h"

#घोषणा DRV_NAME		"skge"
#घोषणा DRV_VERSION		"1.14"

#घोषणा DEFAULT_TX_RING_SIZE	128
#घोषणा DEFAULT_RX_RING_SIZE	512
#घोषणा MAX_TX_RING_SIZE	1024
#घोषणा TX_LOW_WATER		(MAX_SKB_FRAGS + 1)
#घोषणा MAX_RX_RING_SIZE	4096
#घोषणा RX_COPY_THRESHOLD	128
#घोषणा RX_BUF_SIZE		1536
#घोषणा PHY_RETRIES	        1000
#घोषणा ETH_JUMBO_MTU		9000
#घोषणा TX_WATCHDOG		(5 * HZ)
#घोषणा NAPI_WEIGHT		64
#घोषणा BLINK_MS		250
#घोषणा LINK_HZ			HZ

#घोषणा SKGE_EEPROM_MAGIC	0x9933aabb


MODULE_DESCRIPTION("SysKonnect Gigabit Ethernet driver");
MODULE_AUTHOR("Stephen Hemminger <shemminger@linux-foundation.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

अटल स्थिर u32 शेष_msg = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
				NETIF_MSG_LINK | NETIF_MSG_IFUP |
				NETIF_MSG_IFDOWN);

अटल पूर्णांक debug = -1;	/* शेषs above */
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

अटल स्थिर काष्ठा pci_device_id skge_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_3COM, 0x1700) पूर्ण,	  /* 3Com 3C940 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_3COM, 0x80EB) पूर्ण,	  /* 3Com 3C940B */
#अगर_घोषित CONFIG_SKGE_GENESIS
	अणु PCI_DEVICE(PCI_VENDOR_ID_SYSKONNECT, 0x4300) पूर्ण, /* SK-9xx */
#पूर्ण_अगर
	अणु PCI_DEVICE(PCI_VENDOR_ID_SYSKONNECT, 0x4320) पूर्ण, /* SK-98xx V2.0 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_DLINK, 0x4b01) पूर्ण,	  /* D-Link DGE-530T (rev.B) */
	अणु PCI_DEVICE(PCI_VENDOR_ID_DLINK, 0x4c00) पूर्ण,	  /* D-Link DGE-530T */
	अणु PCI_DEVICE(PCI_VENDOR_ID_DLINK, 0x4302) पूर्ण,	  /* D-Link DGE-530T Rev C1 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4320) पूर्ण,	  /* Marvell Yukon 88E8001/8003/8010 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x5005) पूर्ण,	  /* Belkin */
	अणु PCI_DEVICE(PCI_VENDOR_ID_CNET, 0x434E) पूर्ण, 	  /* CNet PowerG-2000 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_LINKSYS, 0x1064) पूर्ण,	  /* Linksys EG1064 v2 */
	अणु PCI_VENDOR_ID_LINKSYS, 0x1032, PCI_ANY_ID, 0x0015 पूर्ण, /* Linksys EG1032 v2 */
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, skge_id_table);

अटल पूर्णांक skge_up(काष्ठा net_device *dev);
अटल पूर्णांक skge_करोwn(काष्ठा net_device *dev);
अटल व्योम skge_phy_reset(काष्ठा skge_port *skge);
अटल व्योम skge_tx_clean(काष्ठा net_device *dev);
अटल पूर्णांक xm_phy_ग_लिखो(काष्ठा skge_hw *hw, पूर्णांक port, u16 reg, u16 val);
अटल पूर्णांक gm_phy_ग_लिखो(काष्ठा skge_hw *hw, पूर्णांक port, u16 reg, u16 val);
अटल व्योम genesis_get_stats(काष्ठा skge_port *skge, u64 *data);
अटल व्योम yukon_get_stats(काष्ठा skge_port *skge, u64 *data);
अटल व्योम yukon_init(काष्ठा skge_hw *hw, पूर्णांक port);
अटल व्योम genesis_mac_init(काष्ठा skge_hw *hw, पूर्णांक port);
अटल व्योम genesis_link_up(काष्ठा skge_port *skge);
अटल व्योम skge_set_multicast(काष्ठा net_device *dev);
अटल irqवापस_t skge_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);

/* Aव्योम conditionals by using array */
अटल स्थिर पूर्णांक txqaddr[] = अणु Q_XA1, Q_XA2 पूर्ण;
अटल स्थिर पूर्णांक rxqaddr[] = अणु Q_R1, Q_R2 पूर्ण;
अटल स्थिर u32 rxirqmask[] = अणु IS_R1_F, IS_R2_F पूर्ण;
अटल स्थिर u32 txirqmask[] = अणु IS_XA1_F, IS_XA2_F पूर्ण;
अटल स्थिर u32 napimask[] = अणु IS_R1_F|IS_XA1_F, IS_R2_F|IS_XA2_F पूर्ण;
अटल स्थिर u32 porपंचांगask[] = अणु IS_PORT_1, IS_PORT_2 पूर्ण;

अटल अंतरभूत bool is_genesis(स्थिर काष्ठा skge_hw *hw)
अणु
#अगर_घोषित CONFIG_SKGE_GENESIS
	वापस hw->chip_id == CHIP_ID_GENESIS;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक skge_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस 0x4000;
पूर्ण

/*
 * Returns copy of whole control रेजिस्टर region
 * Note: skip RAM address रेजिस्टर because accessing it will
 * 	 cause bus hangs!
 */
अटल व्योम skge_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			  व्योम *p)
अणु
	स्थिर काष्ठा skge_port *skge = netdev_priv(dev);
	स्थिर व्योम __iomem *io = skge->hw->regs;

	regs->version = 1;
	स_रखो(p, 0, regs->len);
	स_नकल_fromio(p, io, B3_RAM_ADDR);

	अगर (regs->len > B3_RI_WTO_R1) अणु
		स_नकल_fromio(p + B3_RI_WTO_R1, io + B3_RI_WTO_R1,
			      regs->len - B3_RI_WTO_R1);
	पूर्ण
पूर्ण

/* Wake on Lan only supported on Yukon chips with rev 1 or above */
अटल u32 wol_supported(स्थिर काष्ठा skge_hw *hw)
अणु
	अगर (is_genesis(hw))
		वापस 0;

	अगर (hw->chip_id == CHIP_ID_YUKON && hw->chip_rev == 0)
		वापस 0;

	वापस WAKE_MAGIC | WAKE_PHY;
पूर्ण

अटल व्योम skge_wol_init(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	u16 ctrl;

	skge_ग_लिखो16(hw, B0_CTST, CS_RST_CLR);
	skge_ग_लिखो16(hw, SK_REG(port, GMAC_LINK_CTRL), GMLC_RST_CLR);

	/* Turn on Vaux */
	skge_ग_लिखो8(hw, B0_POWER_CTRL,
		    PC_VAUX_ENA | PC_VCC_ENA | PC_VAUX_ON | PC_VCC_OFF);

	/* WA code क्रम COMA mode -- clear PHY reset */
	अगर (hw->chip_id == CHIP_ID_YUKON_LITE &&
	    hw->chip_rev >= CHIP_REV_YU_LITE_A3) अणु
		u32 reg = skge_पढ़ो32(hw, B2_GP_IO);
		reg |= GP_सूची_9;
		reg &= ~GP_IO_9;
		skge_ग_लिखो32(hw, B2_GP_IO, reg);
	पूर्ण

	skge_ग_लिखो32(hw, SK_REG(port, GPHY_CTRL),
		     GPC_DIS_SLEEP |
		     GPC_HWCFG_M_3 | GPC_HWCFG_M_2 | GPC_HWCFG_M_1 | GPC_HWCFG_M_0 |
		     GPC_ANEG_1 | GPC_RST_SET);

	skge_ग_लिखो32(hw, SK_REG(port, GPHY_CTRL),
		     GPC_DIS_SLEEP |
		     GPC_HWCFG_M_3 | GPC_HWCFG_M_2 | GPC_HWCFG_M_1 | GPC_HWCFG_M_0 |
		     GPC_ANEG_1 | GPC_RST_CLR);

	skge_ग_लिखो32(hw, SK_REG(port, GMAC_CTRL), GMC_RST_CLR);

	/* Force to 10/100 skge_reset will re-enable on resume	 */
	gm_phy_ग_लिखो(hw, port, PHY_MARV_AUNE_ADV,
		     (PHY_AN_100FULL | PHY_AN_100HALF |
		      PHY_AN_10FULL | PHY_AN_10HALF | PHY_AN_CSMA));
	/* no 1000 HD/FD */
	gm_phy_ग_लिखो(hw, port, PHY_MARV_1000T_CTRL, 0);
	gm_phy_ग_लिखो(hw, port, PHY_MARV_CTRL,
		     PHY_CT_RESET | PHY_CT_SPS_LSB | PHY_CT_ANE |
		     PHY_CT_RE_CFG | PHY_CT_DUP_MD);


	/* Set GMAC to no flow control and स्वतः update क्रम speed/duplex */
	gma_ग_लिखो16(hw, port, GM_GP_CTRL,
		    GM_GPCR_FC_TX_DIS|GM_GPCR_TX_ENA|GM_GPCR_RX_ENA|
		    GM_GPCR_DUP_FULL|GM_GPCR_FC_RX_DIS|GM_GPCR_AU_FCT_DIS);

	/* Set WOL address */
	स_नकल_toio(hw->regs + WOL_REGS(port, WOL_MAC_ADDR),
		    skge->netdev->dev_addr, ETH_ALEN);

	/* Turn on appropriate WOL control bits */
	skge_ग_लिखो16(hw, WOL_REGS(port, WOL_CTRL_STAT), WOL_CTL_CLEAR_RESULT);
	ctrl = 0;
	अगर (skge->wol & WAKE_PHY)
		ctrl |= WOL_CTL_ENA_PME_ON_LINK_CHG|WOL_CTL_ENA_LINK_CHG_UNIT;
	अन्यथा
		ctrl |= WOL_CTL_DIS_PME_ON_LINK_CHG|WOL_CTL_DIS_LINK_CHG_UNIT;

	अगर (skge->wol & WAKE_MAGIC)
		ctrl |= WOL_CTL_ENA_PME_ON_MAGIC_PKT|WOL_CTL_ENA_MAGIC_PKT_UNIT;
	अन्यथा
		ctrl |= WOL_CTL_DIS_PME_ON_MAGIC_PKT|WOL_CTL_DIS_MAGIC_PKT_UNIT;

	ctrl |= WOL_CTL_DIS_PME_ON_PATTERN|WOL_CTL_DIS_PATTERN_UNIT;
	skge_ग_लिखो16(hw, WOL_REGS(port, WOL_CTRL_STAT), ctrl);

	/* block receiver */
	skge_ग_लिखो8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_SET);
पूर्ण

अटल व्योम skge_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	wol->supported = wol_supported(skge->hw);
	wol->wolopts = skge->wol;
पूर्ण

अटल पूर्णांक skge_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;

	अगर ((wol->wolopts & ~wol_supported(hw)) ||
	    !device_can_wakeup(&hw->pdev->dev))
		वापस -EOPNOTSUPP;

	skge->wol = wol->wolopts;

	device_set_wakeup_enable(&hw->pdev->dev, skge->wol);

	वापस 0;
पूर्ण

/* Determine supported/advertised modes based on hardware.
 * Note: ethtool ADVERTISED_xxx == SUPPORTED_xxx
 */
अटल u32 skge_supported_modes(स्थिर काष्ठा skge_hw *hw)
अणु
	u32 supported;

	अगर (hw->copper) अणु
		supported = (SUPPORTED_10baseT_Half |
			     SUPPORTED_10baseT_Full |
			     SUPPORTED_100baseT_Half |
			     SUPPORTED_100baseT_Full |
			     SUPPORTED_1000baseT_Half |
			     SUPPORTED_1000baseT_Full |
			     SUPPORTED_Autoneg |
			     SUPPORTED_TP);

		अगर (is_genesis(hw))
			supported &= ~(SUPPORTED_10baseT_Half |
				       SUPPORTED_10baseT_Full |
				       SUPPORTED_100baseT_Half |
				       SUPPORTED_100baseT_Full);

		अन्यथा अगर (hw->chip_id == CHIP_ID_YUKON)
			supported &= ~SUPPORTED_1000baseT_Half;
	पूर्ण अन्यथा
		supported = (SUPPORTED_1000baseT_Full |
			     SUPPORTED_1000baseT_Half |
			     SUPPORTED_FIBRE |
			     SUPPORTED_Autoneg);

	वापस supported;
पूर्ण

अटल पूर्णांक skge_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	u32 supported, advertising;

	supported = skge_supported_modes(hw);

	अगर (hw->copper) अणु
		cmd->base.port = PORT_TP;
		cmd->base.phy_address = hw->phy_addr;
	पूर्ण अन्यथा
		cmd->base.port = PORT_FIBRE;

	advertising = skge->advertising;
	cmd->base.स्वतःneg = skge->स्वतःneg;
	cmd->base.speed = skge->speed;
	cmd->base.duplex = skge->duplex;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक skge_set_link_ksettings(काष्ठा net_device *dev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	स्थिर काष्ठा skge_hw *hw = skge->hw;
	u32 supported = skge_supported_modes(hw);
	पूर्णांक err = 0;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		advertising = supported;
		skge->duplex = -1;
		skge->speed = -1;
	पूर्ण अन्यथा अणु
		u32 setting;
		u32 speed = cmd->base.speed;

		चयन (speed) अणु
		हाल SPEED_1000:
			अगर (cmd->base.duplex == DUPLEX_FULL)
				setting = SUPPORTED_1000baseT_Full;
			अन्यथा अगर (cmd->base.duplex == DUPLEX_HALF)
				setting = SUPPORTED_1000baseT_Half;
			अन्यथा
				वापस -EINVAL;
			अवरोध;
		हाल SPEED_100:
			अगर (cmd->base.duplex == DUPLEX_FULL)
				setting = SUPPORTED_100baseT_Full;
			अन्यथा अगर (cmd->base.duplex == DUPLEX_HALF)
				setting = SUPPORTED_100baseT_Half;
			अन्यथा
				वापस -EINVAL;
			अवरोध;

		हाल SPEED_10:
			अगर (cmd->base.duplex == DUPLEX_FULL)
				setting = SUPPORTED_10baseT_Full;
			अन्यथा अगर (cmd->base.duplex == DUPLEX_HALF)
				setting = SUPPORTED_10baseT_Half;
			अन्यथा
				वापस -EINVAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर ((setting & supported) == 0)
			वापस -EINVAL;

		skge->speed = speed;
		skge->duplex = cmd->base.duplex;
	पूर्ण

	skge->स्वतःneg = cmd->base.स्वतःneg;
	skge->advertising = advertising;

	अगर (netअगर_running(dev)) अणु
		skge_करोwn(dev);
		err = skge_up(dev);
		अगर (err) अणु
			dev_बंद(dev);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम skge_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(skge->hw->pdev),
		माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा skge_stat अणु
	अक्षर 	   name[ETH_GSTRING_LEN];
	u16	   xmac_offset;
	u16	   gma_offset;
पूर्ण skge_stats[] = अणु
	अणु "tx_bytes",		XM_TXO_OK_HI,  GM_TXO_OK_HI पूर्ण,
	अणु "rx_bytes",		XM_RXO_OK_HI,  GM_RXO_OK_HI पूर्ण,

	अणु "tx_broadcast",	XM_TXF_BC_OK,  GM_TXF_BC_OK पूर्ण,
	अणु "rx_broadcast",	XM_RXF_BC_OK,  GM_RXF_BC_OK पूर्ण,
	अणु "tx_multicast",	XM_TXF_MC_OK,  GM_TXF_MC_OK पूर्ण,
	अणु "rx_multicast",	XM_RXF_MC_OK,  GM_RXF_MC_OK पूर्ण,
	अणु "tx_unicast",		XM_TXF_UC_OK,  GM_TXF_UC_OK पूर्ण,
	अणु "rx_unicast",		XM_RXF_UC_OK,  GM_RXF_UC_OK पूर्ण,
	अणु "tx_mac_pause",	XM_TXF_MPAUSE, GM_TXF_MPAUSE पूर्ण,
	अणु "rx_mac_pause",	XM_RXF_MPAUSE, GM_RXF_MPAUSE पूर्ण,

	अणु "collisions",		XM_TXF_SNG_COL, GM_TXF_SNG_COL पूर्ण,
	अणु "multi_collisions",	XM_TXF_MUL_COL, GM_TXF_MUL_COL पूर्ण,
	अणु "aborted",		XM_TXF_ABO_COL, GM_TXF_ABO_COL पूर्ण,
	अणु "late_collision",	XM_TXF_LAT_COL, GM_TXF_LAT_COL पूर्ण,
	अणु "fifo_underrun",	XM_TXE_FIFO_UR, GM_TXE_FIFO_UR पूर्ण,
	अणु "fifo_overflow",	XM_RXE_FIFO_OV, GM_RXE_FIFO_OV पूर्ण,

	अणु "rx_toolong",		XM_RXF_LNG_ERR, GM_RXF_LNG_ERR पूर्ण,
	अणु "rx_jabber",		XM_RXF_JAB_PKT, GM_RXF_JAB_PKT पूर्ण,
	अणु "rx_runt",		XM_RXE_RUNT, 	GM_RXE_FRAG पूर्ण,
	अणु "rx_too_long",	XM_RXF_LNG_ERR, GM_RXF_LNG_ERR पूर्ण,
	अणु "rx_fcs_error",	XM_RXF_FCS_ERR, GM_RXF_FCS_ERR पूर्ण,
पूर्ण;

अटल पूर्णांक skge_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(skge_stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम skge_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	अगर (is_genesis(skge->hw))
		genesis_get_stats(skge, data);
	अन्यथा
		yukon_get_stats(skge, data);
पूर्ण

/* Use hardware MIB variables क्रम critical path statistics and
 * transmit feedback not reported at पूर्णांकerrupt.
 * Other errors are accounted क्रम in पूर्णांकerrupt handler.
 */
अटल काष्ठा net_device_stats *skge_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	u64 data[ARRAY_SIZE(skge_stats)];

	अगर (is_genesis(skge->hw))
		genesis_get_stats(skge, data);
	अन्यथा
		yukon_get_stats(skge, data);

	dev->stats.tx_bytes = data[0];
	dev->stats.rx_bytes = data[1];
	dev->stats.tx_packets = data[2] + data[4] + data[6];
	dev->stats.rx_packets = data[3] + data[5] + data[7];
	dev->stats.multicast = data[3] + data[5];
	dev->stats.collisions = data[10];
	dev->stats.tx_पातed_errors = data[12];

	वापस &dev->stats;
पूर्ण

अटल व्योम skge_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(skge_stats); i++)
			स_नकल(data + i * ETH_GSTRING_LEN,
			       skge_stats[i].name, ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम skge_get_ring_param(काष्ठा net_device *dev,
				काष्ठा ethtool_ringparam *p)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	p->rx_max_pending = MAX_RX_RING_SIZE;
	p->tx_max_pending = MAX_TX_RING_SIZE;

	p->rx_pending = skge->rx_ring.count;
	p->tx_pending = skge->tx_ring.count;
पूर्ण

अटल पूर्णांक skge_set_ring_param(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *p)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	पूर्णांक err = 0;

	अगर (p->rx_pending == 0 || p->rx_pending > MAX_RX_RING_SIZE ||
	    p->tx_pending < TX_LOW_WATER || p->tx_pending > MAX_TX_RING_SIZE)
		वापस -EINVAL;

	skge->rx_ring.count = p->rx_pending;
	skge->tx_ring.count = p->tx_pending;

	अगर (netअगर_running(dev)) अणु
		skge_करोwn(dev);
		err = skge_up(dev);
		अगर (err)
			dev_बंद(dev);
	पूर्ण

	वापस err;
पूर्ण

अटल u32 skge_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा skge_port *skge = netdev_priv(netdev);
	वापस skge->msg_enable;
पूर्ण

अटल व्योम skge_set_msglevel(काष्ठा net_device *netdev, u32 value)
अणु
	काष्ठा skge_port *skge = netdev_priv(netdev);
	skge->msg_enable = value;
पूर्ण

अटल पूर्णांक skge_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	अगर (skge->स्वतःneg != AUTONEG_ENABLE || !netअगर_running(dev))
		वापस -EINVAL;

	skge_phy_reset(skge);
	वापस 0;
पूर्ण

अटल व्योम skge_get_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	ecmd->rx_छोड़ो = ((skge->flow_control == FLOW_MODE_SYMMETRIC) ||
			  (skge->flow_control == FLOW_MODE_SYM_OR_REM));
	ecmd->tx_छोड़ो = (ecmd->rx_छोड़ो ||
			  (skge->flow_control == FLOW_MODE_LOC_SEND));

	ecmd->स्वतःneg = ecmd->rx_छोड़ो || ecmd->tx_छोड़ो;
पूर्ण

अटल पूर्णांक skge_set_छोड़ोparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा ethtool_छोड़ोparam old;
	पूर्णांक err = 0;

	skge_get_छोड़ोparam(dev, &old);

	अगर (ecmd->स्वतःneg != old.स्वतःneg)
		skge->flow_control = ecmd->स्वतःneg ? FLOW_MODE_NONE : FLOW_MODE_SYMMETRIC;
	अन्यथा अणु
		अगर (ecmd->rx_छोड़ो && ecmd->tx_छोड़ो)
			skge->flow_control = FLOW_MODE_SYMMETRIC;
		अन्यथा अगर (ecmd->rx_छोड़ो && !ecmd->tx_छोड़ो)
			skge->flow_control = FLOW_MODE_SYM_OR_REM;
		अन्यथा अगर (!ecmd->rx_छोड़ो && ecmd->tx_छोड़ो)
			skge->flow_control = FLOW_MODE_LOC_SEND;
		अन्यथा
			skge->flow_control = FLOW_MODE_NONE;
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		skge_करोwn(dev);
		err = skge_up(dev);
		अगर (err) अणु
			dev_बंद(dev);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Chip पूर्णांकernal frequency क्रम घड़ी calculations */
अटल अंतरभूत u32 hwkhz(स्थिर काष्ठा skge_hw *hw)
अणु
	वापस is_genesis(hw) ? 53125 : 78125;
पूर्ण

/* Chip HZ to microseconds */
अटल अंतरभूत u32 skge_clk2usec(स्थिर काष्ठा skge_hw *hw, u32 ticks)
अणु
	वापस (ticks * 1000) / hwkhz(hw);
पूर्ण

/* Microseconds to chip HZ */
अटल अंतरभूत u32 skge_usecs2clk(स्थिर काष्ठा skge_hw *hw, u32 usec)
अणु
	वापस hwkhz(hw) * usec / 1000;
पूर्ण

अटल पूर्णांक skge_get_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;

	ecmd->rx_coalesce_usecs = 0;
	ecmd->tx_coalesce_usecs = 0;

	अगर (skge_पढ़ो32(hw, B2_IRQM_CTRL) & TIM_START) अणु
		u32 delay = skge_clk2usec(hw, skge_पढ़ो32(hw, B2_IRQM_INI));
		u32 msk = skge_पढ़ो32(hw, B2_IRQM_MSK);

		अगर (msk & rxirqmask[port])
			ecmd->rx_coalesce_usecs = delay;
		अगर (msk & txirqmask[port])
			ecmd->tx_coalesce_usecs = delay;
	पूर्ण

	वापस 0;
पूर्ण

/* Note: पूर्णांकerrupt समयr is per board, but can turn on/off per port */
अटल पूर्णांक skge_set_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	u32 msk = skge_पढ़ो32(hw, B2_IRQM_MSK);
	u32 delay = 25;

	अगर (ecmd->rx_coalesce_usecs == 0)
		msk &= ~rxirqmask[port];
	अन्यथा अगर (ecmd->rx_coalesce_usecs < 25 ||
		 ecmd->rx_coalesce_usecs > 33333)
		वापस -EINVAL;
	अन्यथा अणु
		msk |= rxirqmask[port];
		delay = ecmd->rx_coalesce_usecs;
	पूर्ण

	अगर (ecmd->tx_coalesce_usecs == 0)
		msk &= ~txirqmask[port];
	अन्यथा अगर (ecmd->tx_coalesce_usecs < 25 ||
		 ecmd->tx_coalesce_usecs > 33333)
		वापस -EINVAL;
	अन्यथा अणु
		msk |= txirqmask[port];
		delay = min(delay, ecmd->rx_coalesce_usecs);
	पूर्ण

	skge_ग_लिखो32(hw, B2_IRQM_MSK, msk);
	अगर (msk == 0)
		skge_ग_लिखो32(hw, B2_IRQM_CTRL, TIM_STOP);
	अन्यथा अणु
		skge_ग_लिखो32(hw, B2_IRQM_INI, skge_usecs2clk(hw, delay));
		skge_ग_लिखो32(hw, B2_IRQM_CTRL, TIM_START);
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत led_mode अणु LED_MODE_OFF, LED_MODE_ON, LED_MODE_TST पूर्ण;
अटल व्योम skge_led(काष्ठा skge_port *skge, क्रमागत led_mode mode)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;

	spin_lock_bh(&hw->phy_lock);
	अगर (is_genesis(hw)) अणु
		चयन (mode) अणु
		हाल LED_MODE_OFF:
			अगर (hw->phy_type == SK_PHY_BCOM)
				xm_phy_ग_लिखो(hw, port, PHY_BCOM_P_EXT_CTRL, PHY_B_PEC_LED_OFF);
			अन्यथा अणु
				skge_ग_लिखो32(hw, SK_REG(port, TX_LED_VAL), 0);
				skge_ग_लिखो8(hw, SK_REG(port, TX_LED_CTRL), LED_T_OFF);
			पूर्ण
			skge_ग_लिखो8(hw, SK_REG(port, LNK_LED_REG), LINKLED_OFF);
			skge_ग_लिखो32(hw, SK_REG(port, RX_LED_VAL), 0);
			skge_ग_लिखो8(hw, SK_REG(port, RX_LED_CTRL), LED_T_OFF);
			अवरोध;

		हाल LED_MODE_ON:
			skge_ग_लिखो8(hw, SK_REG(port, LNK_LED_REG), LINKLED_ON);
			skge_ग_लिखो8(hw, SK_REG(port, LNK_LED_REG), LINKLED_LINKSYNC_ON);

			skge_ग_लिखो8(hw, SK_REG(port, RX_LED_CTRL), LED_START);
			skge_ग_लिखो8(hw, SK_REG(port, TX_LED_CTRL), LED_START);

			अवरोध;

		हाल LED_MODE_TST:
			skge_ग_लिखो8(hw, SK_REG(port, RX_LED_TST), LED_T_ON);
			skge_ग_लिखो32(hw, SK_REG(port, RX_LED_VAL), 100);
			skge_ग_लिखो8(hw, SK_REG(port, RX_LED_CTRL), LED_START);

			अगर (hw->phy_type == SK_PHY_BCOM)
				xm_phy_ग_लिखो(hw, port, PHY_BCOM_P_EXT_CTRL, PHY_B_PEC_LED_ON);
			अन्यथा अणु
				skge_ग_लिखो8(hw, SK_REG(port, TX_LED_TST), LED_T_ON);
				skge_ग_लिखो32(hw, SK_REG(port, TX_LED_VAL), 100);
				skge_ग_लिखो8(hw, SK_REG(port, TX_LED_CTRL), LED_START);
			पूर्ण

		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (mode) अणु
		हाल LED_MODE_OFF:
			gm_phy_ग_लिखो(hw, port, PHY_MARV_LED_CTRL, 0);
			gm_phy_ग_लिखो(hw, port, PHY_MARV_LED_OVER,
				     PHY_M_LED_MO_DUP(MO_LED_OFF)  |
				     PHY_M_LED_MO_10(MO_LED_OFF)   |
				     PHY_M_LED_MO_100(MO_LED_OFF)  |
				     PHY_M_LED_MO_1000(MO_LED_OFF) |
				     PHY_M_LED_MO_RX(MO_LED_OFF));
			अवरोध;
		हाल LED_MODE_ON:
			gm_phy_ग_लिखो(hw, port, PHY_MARV_LED_CTRL,
				     PHY_M_LED_PULS_DUR(PULS_170MS) |
				     PHY_M_LED_BLINK_RT(BLINK_84MS) |
				     PHY_M_LEDC_TX_CTRL |
				     PHY_M_LEDC_DP_CTRL);

			gm_phy_ग_लिखो(hw, port, PHY_MARV_LED_OVER,
				     PHY_M_LED_MO_RX(MO_LED_OFF) |
				     (skge->speed == SPEED_100 ?
				      PHY_M_LED_MO_100(MO_LED_ON) : 0));
			अवरोध;
		हाल LED_MODE_TST:
			gm_phy_ग_लिखो(hw, port, PHY_MARV_LED_CTRL, 0);
			gm_phy_ग_लिखो(hw, port, PHY_MARV_LED_OVER,
				     PHY_M_LED_MO_DUP(MO_LED_ON)  |
				     PHY_M_LED_MO_10(MO_LED_ON)   |
				     PHY_M_LED_MO_100(MO_LED_ON)  |
				     PHY_M_LED_MO_1000(MO_LED_ON) |
				     PHY_M_LED_MO_RX(MO_LED_ON));
		पूर्ण
	पूर्ण
	spin_unlock_bh(&hw->phy_lock);
पूर्ण

/* blink LED's क्रम finding board */
अटल पूर्णांक skge_set_phys_id(काष्ठा net_device *dev,
			    क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		वापस 2;	/* cycle on/off twice per second */

	हाल ETHTOOL_ID_ON:
		skge_led(skge, LED_MODE_TST);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		skge_led(skge, LED_MODE_OFF);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		/* back to regular LED state */
		skge_led(skge, netअगर_running(dev) ? LED_MODE_ON : LED_MODE_OFF);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक skge_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	u32 reg2;

	pci_पढ़ो_config_dword(skge->hw->pdev, PCI_DEV_REG2, &reg2);
	वापस 1 << (((reg2 & PCI_VPD_ROM_SZ) >> 14) + 8);
पूर्ण

अटल u32 skge_vpd_पढ़ो(काष्ठा pci_dev *pdev, पूर्णांक cap, u16 offset)
अणु
	u32 val;

	pci_ग_लिखो_config_word(pdev, cap + PCI_VPD_ADDR, offset);

	करो अणु
		pci_पढ़ो_config_word(pdev, cap + PCI_VPD_ADDR, &offset);
	पूर्ण जबतक (!(offset & PCI_VPD_ADDR_F));

	pci_पढ़ो_config_dword(pdev, cap + PCI_VPD_DATA, &val);
	वापस val;
पूर्ण

अटल व्योम skge_vpd_ग_लिखो(काष्ठा pci_dev *pdev, पूर्णांक cap, u16 offset, u32 val)
अणु
	pci_ग_लिखो_config_dword(pdev, cap + PCI_VPD_DATA, val);
	pci_ग_लिखो_config_word(pdev, cap + PCI_VPD_ADDR,
			      offset | PCI_VPD_ADDR_F);

	करो अणु
		pci_पढ़ो_config_word(pdev, cap + PCI_VPD_ADDR, &offset);
	पूर्ण जबतक (offset & PCI_VPD_ADDR_F);
पूर्ण

अटल पूर्णांक skge_get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
			   u8 *data)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा pci_dev *pdev = skge->hw->pdev;
	पूर्णांक cap = pci_find_capability(pdev, PCI_CAP_ID_VPD);
	पूर्णांक length = eeprom->len;
	u16 offset = eeprom->offset;

	अगर (!cap)
		वापस -EINVAL;

	eeprom->magic = SKGE_EEPROM_MAGIC;

	जबतक (length > 0) अणु
		u32 val = skge_vpd_पढ़ो(pdev, cap, offset);
		पूर्णांक n = min_t(पूर्णांक, length, माप(val));

		स_नकल(data, &val, n);
		length -= n;
		data += n;
		offset += n;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक skge_set_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
			   u8 *data)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा pci_dev *pdev = skge->hw->pdev;
	पूर्णांक cap = pci_find_capability(pdev, PCI_CAP_ID_VPD);
	पूर्णांक length = eeprom->len;
	u16 offset = eeprom->offset;

	अगर (!cap)
		वापस -EINVAL;

	अगर (eeprom->magic != SKGE_EEPROM_MAGIC)
		वापस -EINVAL;

	जबतक (length > 0) अणु
		u32 val;
		पूर्णांक n = min_t(पूर्णांक, length, माप(val));

		अगर (n < माप(val))
			val = skge_vpd_पढ़ो(pdev, cap, offset);
		स_नकल(&val, data, n);

		skge_vpd_ग_लिखो(pdev, cap, offset, val);

		length -= n;
		data += n;
		offset += n;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops skge_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
	.get_drvinfo	= skge_get_drvinfo,
	.get_regs_len	= skge_get_regs_len,
	.get_regs	= skge_get_regs,
	.get_wol	= skge_get_wol,
	.set_wol	= skge_set_wol,
	.get_msglevel	= skge_get_msglevel,
	.set_msglevel	= skge_set_msglevel,
	.nway_reset	= skge_nway_reset,
	.get_link	= ethtool_op_get_link,
	.get_eeprom_len	= skge_get_eeprom_len,
	.get_eeprom	= skge_get_eeprom,
	.set_eeprom	= skge_set_eeprom,
	.get_ringparam	= skge_get_ring_param,
	.set_ringparam	= skge_set_ring_param,
	.get_छोड़ोparam = skge_get_छोड़ोparam,
	.set_छोड़ोparam = skge_set_छोड़ोparam,
	.get_coalesce	= skge_get_coalesce,
	.set_coalesce	= skge_set_coalesce,
	.get_strings	= skge_get_strings,
	.set_phys_id	= skge_set_phys_id,
	.get_sset_count = skge_get_sset_count,
	.get_ethtool_stats = skge_get_ethtool_stats,
	.get_link_ksettings = skge_get_link_ksettings,
	.set_link_ksettings = skge_set_link_ksettings,
पूर्ण;

/*
 * Allocate ring elements and chain them together
 * One-to-one association of board descriptors with ring elements
 */
अटल पूर्णांक skge_ring_alloc(काष्ठा skge_ring *ring, व्योम *vaddr, u32 base)
अणु
	काष्ठा skge_tx_desc *d;
	काष्ठा skge_element *e;
	पूर्णांक i;

	ring->start = kसुस्मृति(ring->count, माप(*e), GFP_KERNEL);
	अगर (!ring->start)
		वापस -ENOMEM;

	क्रम (i = 0, e = ring->start, d = vaddr; i < ring->count; i++, e++, d++) अणु
		e->desc = d;
		अगर (i == ring->count - 1) अणु
			e->next = ring->start;
			d->next_offset = base;
		पूर्ण अन्यथा अणु
			e->next = e + 1;
			d->next_offset = base + (i+1) * माप(*d);
		पूर्ण
	पूर्ण
	ring->to_use = ring->to_clean = ring->start;

	वापस 0;
पूर्ण

/* Allocate and setup a new buffer क्रम receiving */
अटल पूर्णांक skge_rx_setup(काष्ठा skge_port *skge, काष्ठा skge_element *e,
			 काष्ठा sk_buff *skb, अचिन्हित पूर्णांक bufsize)
अणु
	काष्ठा skge_rx_desc *rd = e->desc;
	dma_addr_t map;

	map = dma_map_single(&skge->hw->pdev->dev, skb->data, bufsize,
			     DMA_FROM_DEVICE);

	अगर (dma_mapping_error(&skge->hw->pdev->dev, map))
		वापस -1;

	rd->dma_lo = lower_32_bits(map);
	rd->dma_hi = upper_32_bits(map);
	e->skb = skb;
	rd->csum1_start = ETH_HLEN;
	rd->csum2_start = ETH_HLEN;
	rd->csum1 = 0;
	rd->csum2 = 0;

	wmb();

	rd->control = BMU_OWN | BMU_STF | BMU_IRQ_खातापूर्ण | BMU_TCP_CHECK | bufsize;
	dma_unmap_addr_set(e, mapaddr, map);
	dma_unmap_len_set(e, maplen, bufsize);
	वापस 0;
पूर्ण

/* Resume receiving using existing skb,
 * Note: DMA address is not changed by chip.
 * 	 MTU not changed जबतक receiver active.
 */
अटल अंतरभूत व्योम skge_rx_reuse(काष्ठा skge_element *e, अचिन्हित पूर्णांक size)
अणु
	काष्ठा skge_rx_desc *rd = e->desc;

	rd->csum2 = 0;
	rd->csum2_start = ETH_HLEN;

	wmb();

	rd->control = BMU_OWN | BMU_STF | BMU_IRQ_खातापूर्ण | BMU_TCP_CHECK | size;
पूर्ण


/* Free all  buffers in receive ring, assumes receiver stopped */
अटल व्योम skge_rx_clean(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	काष्ठा skge_ring *ring = &skge->rx_ring;
	काष्ठा skge_element *e;

	e = ring->start;
	करो अणु
		काष्ठा skge_rx_desc *rd = e->desc;
		rd->control = 0;
		अगर (e->skb) अणु
			dma_unmap_single(&hw->pdev->dev,
					 dma_unmap_addr(e, mapaddr),
					 dma_unmap_len(e, maplen),
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(e->skb);
			e->skb = शून्य;
		पूर्ण
	पूर्ण जबतक ((e = e->next) != ring->start);
पूर्ण


/* Allocate buffers क्रम receive ring
 * For receive:  to_clean is next received frame.
 */
अटल पूर्णांक skge_rx_fill(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_ring *ring = &skge->rx_ring;
	काष्ठा skge_element *e;

	e = ring->start;
	करो अणु
		काष्ठा sk_buff *skb;

		skb = __netdev_alloc_skb(dev, skge->rx_buf_size + NET_IP_ALIGN,
					 GFP_KERNEL);
		अगर (!skb)
			वापस -ENOMEM;

		skb_reserve(skb, NET_IP_ALIGN);
		अगर (skge_rx_setup(skge, e, skb, skge->rx_buf_size) < 0) अणु
			dev_kमुक्त_skb(skb);
			वापस -EIO;
		पूर्ण
	पूर्ण जबतक ((e = e->next) != ring->start);

	ring->to_clean = ring->start;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *skge_छोड़ो(क्रमागत छोड़ो_status status)
अणु
	चयन (status) अणु
	हाल FLOW_STAT_NONE:
		वापस "none";
	हाल FLOW_STAT_REM_SEND:
		वापस "rx only";
	हाल FLOW_STAT_LOC_SEND:
		वापस "tx_only";
	हाल FLOW_STAT_SYMMETRIC:		/* Both station may send PAUSE */
		वापस "both";
	शेष:
		वापस "indeterminated";
	पूर्ण
पूर्ण


अटल व्योम skge_link_up(काष्ठा skge_port *skge)
अणु
	skge_ग_लिखो8(skge->hw, SK_REG(skge->port, LNK_LED_REG),
		    LED_BLK_OFF|LED_SYNC_OFF|LED_REG_ON);

	netअगर_carrier_on(skge->netdev);
	netअगर_wake_queue(skge->netdev);

	netअगर_info(skge, link, skge->netdev,
		   "Link is up at %d Mbps, %s duplex, flow control %s\n",
		   skge->speed,
		   skge->duplex == DUPLEX_FULL ? "full" : "half",
		   skge_छोड़ो(skge->flow_status));
पूर्ण

अटल व्योम skge_link_करोwn(काष्ठा skge_port *skge)
अणु
	skge_ग_लिखो8(skge->hw, SK_REG(skge->port, LNK_LED_REG), LED_REG_OFF);
	netअगर_carrier_off(skge->netdev);
	netअगर_stop_queue(skge->netdev);

	netअगर_info(skge, link, skge->netdev, "Link is down\n");
पूर्ण

अटल व्योम xm_link_करोwn(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	काष्ठा net_device *dev = hw->dev[port];
	काष्ठा skge_port *skge = netdev_priv(dev);

	xm_ग_लिखो16(hw, port, XM_IMSK, XM_IMSK_DISABLE);

	अगर (netअगर_carrier_ok(dev))
		skge_link_करोwn(skge);
पूर्ण

अटल पूर्णांक __xm_phy_पढ़ो(काष्ठा skge_hw *hw, पूर्णांक port, u16 reg, u16 *val)
अणु
	पूर्णांक i;

	xm_ग_लिखो16(hw, port, XM_PHY_ADDR, reg | hw->phy_addr);
	*val = xm_पढ़ो16(hw, port, XM_PHY_DATA);

	अगर (hw->phy_type == SK_PHY_XMAC)
		जाओ पढ़ोy;

	क्रम (i = 0; i < PHY_RETRIES; i++) अणु
		अगर (xm_पढ़ो16(hw, port, XM_MMU_CMD) & XM_MMU_PHY_RDY)
			जाओ पढ़ोy;
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
 पढ़ोy:
	*val = xm_पढ़ो16(hw, port, XM_PHY_DATA);

	वापस 0;
पूर्ण

अटल u16 xm_phy_पढ़ो(काष्ठा skge_hw *hw, पूर्णांक port, u16 reg)
अणु
	u16 v = 0;
	अगर (__xm_phy_पढ़ो(hw, port, reg, &v))
		pr_warn("%s: phy read timed out\n", hw->dev[port]->name);
	वापस v;
पूर्ण

अटल पूर्णांक xm_phy_ग_लिखो(काष्ठा skge_hw *hw, पूर्णांक port, u16 reg, u16 val)
अणु
	पूर्णांक i;

	xm_ग_लिखो16(hw, port, XM_PHY_ADDR, reg | hw->phy_addr);
	क्रम (i = 0; i < PHY_RETRIES; i++) अणु
		अगर (!(xm_पढ़ो16(hw, port, XM_MMU_CMD) & XM_MMU_PHY_BUSY))
			जाओ पढ़ोy;
		udelay(1);
	पूर्ण
	वापस -EIO;

 पढ़ोy:
	xm_ग_लिखो16(hw, port, XM_PHY_DATA, val);
	क्रम (i = 0; i < PHY_RETRIES; i++) अणु
		अगर (!(xm_पढ़ो16(hw, port, XM_MMU_CMD) & XM_MMU_PHY_BUSY))
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम genesis_init(काष्ठा skge_hw *hw)
अणु
	/* set blink source counter */
	skge_ग_लिखो32(hw, B2_BSC_INI, (SK_BLK_DUR * SK_FACT_53) / 100);
	skge_ग_लिखो8(hw, B2_BSC_CTRL, BSC_START);

	/* configure mac arbiter */
	skge_ग_लिखो16(hw, B3_MA_TO_CTRL, MA_RST_CLR);

	/* configure mac arbiter समयout values */
	skge_ग_लिखो8(hw, B3_MA_TOINI_RX1, SK_MAC_TO_53);
	skge_ग_लिखो8(hw, B3_MA_TOINI_RX2, SK_MAC_TO_53);
	skge_ग_लिखो8(hw, B3_MA_TOINI_TX1, SK_MAC_TO_53);
	skge_ग_लिखो8(hw, B3_MA_TOINI_TX2, SK_MAC_TO_53);

	skge_ग_लिखो8(hw, B3_MA_RCINI_RX1, 0);
	skge_ग_लिखो8(hw, B3_MA_RCINI_RX2, 0);
	skge_ग_लिखो8(hw, B3_MA_RCINI_TX1, 0);
	skge_ग_लिखो8(hw, B3_MA_RCINI_TX2, 0);

	/* configure packet arbiter समयout */
	skge_ग_लिखो16(hw, B3_PA_CTRL, PA_RST_CLR);
	skge_ग_लिखो16(hw, B3_PA_TOINI_RX1, SK_PKT_TO_MAX);
	skge_ग_लिखो16(hw, B3_PA_TOINI_TX1, SK_PKT_TO_MAX);
	skge_ग_लिखो16(hw, B3_PA_TOINI_RX2, SK_PKT_TO_MAX);
	skge_ग_लिखो16(hw, B3_PA_TOINI_TX2, SK_PKT_TO_MAX);
पूर्ण

अटल व्योम genesis_reset(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	अटल स्थिर u8 zero[8]  = अणु 0 पूर्ण;
	u32 reg;

	skge_ग_लिखो8(hw, SK_REG(port, GMAC_IRQ_MSK), 0);

	/* reset the statistics module */
	xm_ग_लिखो32(hw, port, XM_GP_PORT, XM_GP_RES_STAT);
	xm_ग_लिखो16(hw, port, XM_IMSK, XM_IMSK_DISABLE);
	xm_ग_लिखो32(hw, port, XM_MODE, 0);		/* clear Mode Reg */
	xm_ग_लिखो16(hw, port, XM_TX_CMD, 0);	/* reset TX CMD Reg */
	xm_ग_लिखो16(hw, port, XM_RX_CMD, 0);	/* reset RX CMD Reg */

	/* disable Broadcom PHY IRQ */
	अगर (hw->phy_type == SK_PHY_BCOM)
		xm_ग_लिखो16(hw, port, PHY_BCOM_INT_MASK, 0xffff);

	xm_outhash(hw, port, XM_HSM, zero);

	/* Flush TX and RX fअगरo */
	reg = xm_पढ़ो32(hw, port, XM_MODE);
	xm_ग_लिखो32(hw, port, XM_MODE, reg | XM_MD_FTF);
	xm_ग_लिखो32(hw, port, XM_MODE, reg | XM_MD_FRF);
पूर्ण

/* Convert mode to MII values  */
अटल स्थिर u16 phy_छोड़ो_map[] = अणु
	[FLOW_MODE_NONE] =	0,
	[FLOW_MODE_LOC_SEND] =	PHY_AN_PAUSE_ASYM,
	[FLOW_MODE_SYMMETRIC] = PHY_AN_PAUSE_CAP,
	[FLOW_MODE_SYM_OR_REM]  = PHY_AN_PAUSE_CAP | PHY_AN_PAUSE_ASYM,
पूर्ण;

/* special defines क्रम FIBER (88E1011S only) */
अटल स्थिर u16 fiber_छोड़ो_map[] = अणु
	[FLOW_MODE_NONE]	= PHY_X_P_NO_PAUSE,
	[FLOW_MODE_LOC_SEND]	= PHY_X_P_ASYM_MD,
	[FLOW_MODE_SYMMETRIC]	= PHY_X_P_SYM_MD,
	[FLOW_MODE_SYM_OR_REM]	= PHY_X_P_BOTH_MD,
पूर्ण;


/* Check status of Broadcom phy link */
अटल व्योम bcom_check_link(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	काष्ठा net_device *dev = hw->dev[port];
	काष्ठा skge_port *skge = netdev_priv(dev);
	u16 status;

	/* पढ़ो twice because of latch */
	xm_phy_पढ़ो(hw, port, PHY_BCOM_STAT);
	status = xm_phy_पढ़ो(hw, port, PHY_BCOM_STAT);

	अगर ((status & PHY_ST_LSYNC) == 0) अणु
		xm_link_करोwn(hw, port);
		वापस;
	पूर्ण

	अगर (skge->स्वतःneg == AUTONEG_ENABLE) अणु
		u16 lpa, aux;

		अगर (!(status & PHY_ST_AN_OVER))
			वापस;

		lpa = xm_phy_पढ़ो(hw, port, PHY_XMAC_AUNE_LP);
		अगर (lpa & PHY_B_AN_RF) अणु
			netdev_notice(dev, "remote fault\n");
			वापस;
		पूर्ण

		aux = xm_phy_पढ़ो(hw, port, PHY_BCOM_AUX_STAT);

		/* Check Duplex mismatch */
		चयन (aux & PHY_B_AS_AN_RES_MSK) अणु
		हाल PHY_B_RES_1000FD:
			skge->duplex = DUPLEX_FULL;
			अवरोध;
		हाल PHY_B_RES_1000HD:
			skge->duplex = DUPLEX_HALF;
			अवरोध;
		शेष:
			netdev_notice(dev, "duplex mismatch\n");
			वापस;
		पूर्ण

		/* We are using IEEE 802.3z/D5.0 Table 37-4 */
		चयन (aux & PHY_B_AS_PAUSE_MSK) अणु
		हाल PHY_B_AS_PAUSE_MSK:
			skge->flow_status = FLOW_STAT_SYMMETRIC;
			अवरोध;
		हाल PHY_B_AS_PRR:
			skge->flow_status = FLOW_STAT_REM_SEND;
			अवरोध;
		हाल PHY_B_AS_PRT:
			skge->flow_status = FLOW_STAT_LOC_SEND;
			अवरोध;
		शेष:
			skge->flow_status = FLOW_STAT_NONE;
		पूर्ण
		skge->speed = SPEED_1000;
	पूर्ण

	अगर (!netअगर_carrier_ok(dev))
		genesis_link_up(skge);
पूर्ण

/* Broadcom 5400 only supports giagabit! SysKonnect did not put an additional
 * Phy on क्रम 100 or 10Mbit operation
 */
अटल व्योम bcom_phy_init(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	पूर्णांक i;
	u16 id1, r, ext, ctl;

	/* magic workaround patterns क्रम Broadcom */
	अटल स्थिर काष्ठा अणु
		u16 reg;
		u16 val;
	पूर्ण A1hack[] = अणु
		अणु 0x18, 0x0c20 पूर्ण, अणु 0x17, 0x0012 पूर्ण, अणु 0x15, 0x1104 पूर्ण,
		अणु 0x17, 0x0013 पूर्ण, अणु 0x15, 0x0404 पूर्ण, अणु 0x17, 0x8006 पूर्ण,
		अणु 0x15, 0x0132 पूर्ण, अणु 0x17, 0x8006 पूर्ण, अणु 0x15, 0x0232 पूर्ण,
		अणु 0x17, 0x800D पूर्ण, अणु 0x15, 0x000F पूर्ण, अणु 0x18, 0x0420 पूर्ण,
	पूर्ण, C0hack[] = अणु
		अणु 0x18, 0x0c20 पूर्ण, अणु 0x17, 0x0012 पूर्ण, अणु 0x15, 0x1204 पूर्ण,
		अणु 0x17, 0x0013 पूर्ण, अणु 0x15, 0x0A04 पूर्ण, अणु 0x18, 0x0420 पूर्ण,
	पूर्ण;

	/* पढ़ो Id from बाह्यal PHY (all have the same address) */
	id1 = xm_phy_पढ़ो(hw, port, PHY_XMAC_ID1);

	/* Optimize MDIO transfer by suppressing preamble. */
	r = xm_पढ़ो16(hw, port, XM_MMU_CMD);
	r |=  XM_MMU_NO_PRE;
	xm_ग_लिखो16(hw, port, XM_MMU_CMD, r);

	चयन (id1) अणु
	हाल PHY_BCOM_ID1_C0:
		/*
		 * Workaround BCOM Errata क्रम the C0 type.
		 * Write magic patterns to reserved रेजिस्टरs.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(C0hack); i++)
			xm_phy_ग_लिखो(hw, port,
				     C0hack[i].reg, C0hack[i].val);

		अवरोध;
	हाल PHY_BCOM_ID1_A1:
		/*
		 * Workaround BCOM Errata क्रम the A1 type.
		 * Write magic patterns to reserved रेजिस्टरs.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(A1hack); i++)
			xm_phy_ग_लिखो(hw, port,
				     A1hack[i].reg, A1hack[i].val);
		अवरोध;
	पूर्ण

	/*
	 * Workaround BCOM Errata (#10523) क्रम all BCom PHYs.
	 * Disable Power Management after reset.
	 */
	r = xm_phy_पढ़ो(hw, port, PHY_BCOM_AUX_CTRL);
	r |= PHY_B_AC_DIS_PM;
	xm_phy_ग_लिखो(hw, port, PHY_BCOM_AUX_CTRL, r);

	/* Dummy पढ़ो */
	xm_पढ़ो16(hw, port, XM_ISRC);

	ext = PHY_B_PEC_EN_LTR; /* enable tx led */
	ctl = PHY_CT_SP1000;	/* always 1000mbit */

	अगर (skge->स्वतःneg == AUTONEG_ENABLE) अणु
		/*
		 * Workaround BCOM Errata #1 क्रम the C5 type.
		 * 1000Base-T Link Acquisition Failure in Slave Mode
		 * Set Repeater/DTE bit 10 of the 1000Base-T Control Register
		 */
		u16 adv = PHY_B_1000C_RD;
		अगर (skge->advertising & ADVERTISED_1000baseT_Half)
			adv |= PHY_B_1000C_AHD;
		अगर (skge->advertising & ADVERTISED_1000baseT_Full)
			adv |= PHY_B_1000C_AFD;
		xm_phy_ग_लिखो(hw, port, PHY_BCOM_1000T_CTRL, adv);

		ctl |= PHY_CT_ANE | PHY_CT_RE_CFG;
	पूर्ण अन्यथा अणु
		अगर (skge->duplex == DUPLEX_FULL)
			ctl |= PHY_CT_DUP_MD;
		/* Force to slave */
		xm_phy_ग_लिखो(hw, port, PHY_BCOM_1000T_CTRL, PHY_B_1000C_MSE);
	पूर्ण

	/* Set स्वतःnegotiation छोड़ो parameters */
	xm_phy_ग_लिखो(hw, port, PHY_BCOM_AUNE_ADV,
		     phy_छोड़ो_map[skge->flow_control] | PHY_AN_CSMA);

	/* Handle Jumbo frames */
	अगर (hw->dev[port]->mtu > ETH_DATA_LEN) अणु
		xm_phy_ग_लिखो(hw, port, PHY_BCOM_AUX_CTRL,
			     PHY_B_AC_TX_TST | PHY_B_AC_LONG_PACK);

		ext |= PHY_B_PEC_HIGH_LA;

	पूर्ण

	xm_phy_ग_लिखो(hw, port, PHY_BCOM_P_EXT_CTRL, ext);
	xm_phy_ग_लिखो(hw, port, PHY_BCOM_CTRL, ctl);

	/* Use link status change पूर्णांकerrupt */
	xm_phy_ग_लिखो(hw, port, PHY_BCOM_INT_MASK, PHY_B_DEF_MSK);
पूर्ण

अटल व्योम xm_phy_init(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	u16 ctrl = 0;

	अगर (skge->स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (skge->advertising & ADVERTISED_1000baseT_Half)
			ctrl |= PHY_X_AN_HD;
		अगर (skge->advertising & ADVERTISED_1000baseT_Full)
			ctrl |= PHY_X_AN_FD;

		ctrl |= fiber_छोड़ो_map[skge->flow_control];

		xm_phy_ग_लिखो(hw, port, PHY_XMAC_AUNE_ADV, ctrl);

		/* Restart Auto-negotiation */
		ctrl = PHY_CT_ANE | PHY_CT_RE_CFG;
	पूर्ण अन्यथा अणु
		/* Set DuplexMode in Config रेजिस्टर */
		अगर (skge->duplex == DUPLEX_FULL)
			ctrl |= PHY_CT_DUP_MD;
		/*
		 * Do NOT enable Auto-negotiation here. This would hold
		 * the link करोwn because no IDLEs are transmitted
		 */
	पूर्ण

	xm_phy_ग_लिखो(hw, port, PHY_XMAC_CTRL, ctrl);

	/* Poll PHY क्रम status changes */
	mod_समयr(&skge->link_समयr, jअगरfies + LINK_HZ);
पूर्ण

अटल पूर्णांक xm_check_link(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	u16 status;

	/* पढ़ो twice because of latch */
	xm_phy_पढ़ो(hw, port, PHY_XMAC_STAT);
	status = xm_phy_पढ़ो(hw, port, PHY_XMAC_STAT);

	अगर ((status & PHY_ST_LSYNC) == 0) अणु
		xm_link_करोwn(hw, port);
		वापस 0;
	पूर्ण

	अगर (skge->स्वतःneg == AUTONEG_ENABLE) अणु
		u16 lpa, res;

		अगर (!(status & PHY_ST_AN_OVER))
			वापस 0;

		lpa = xm_phy_पढ़ो(hw, port, PHY_XMAC_AUNE_LP);
		अगर (lpa & PHY_B_AN_RF) अणु
			netdev_notice(dev, "remote fault\n");
			वापस 0;
		पूर्ण

		res = xm_phy_पढ़ो(hw, port, PHY_XMAC_RES_ABI);

		/* Check Duplex mismatch */
		चयन (res & (PHY_X_RS_HD | PHY_X_RS_FD)) अणु
		हाल PHY_X_RS_FD:
			skge->duplex = DUPLEX_FULL;
			अवरोध;
		हाल PHY_X_RS_HD:
			skge->duplex = DUPLEX_HALF;
			अवरोध;
		शेष:
			netdev_notice(dev, "duplex mismatch\n");
			वापस 0;
		पूर्ण

		/* We are using IEEE 802.3z/D5.0 Table 37-4 */
		अगर ((skge->flow_control == FLOW_MODE_SYMMETRIC ||
		     skge->flow_control == FLOW_MODE_SYM_OR_REM) &&
		    (lpa & PHY_X_P_SYM_MD))
			skge->flow_status = FLOW_STAT_SYMMETRIC;
		अन्यथा अगर (skge->flow_control == FLOW_MODE_SYM_OR_REM &&
			 (lpa & PHY_X_RS_PAUSE) == PHY_X_P_ASYM_MD)
			/* Enable PAUSE receive, disable PAUSE transmit */
			skge->flow_status  = FLOW_STAT_REM_SEND;
		अन्यथा अगर (skge->flow_control == FLOW_MODE_LOC_SEND &&
			 (lpa & PHY_X_RS_PAUSE) == PHY_X_P_BOTH_MD)
			/* Disable PAUSE receive, enable PAUSE transmit */
			skge->flow_status = FLOW_STAT_LOC_SEND;
		अन्यथा
			skge->flow_status = FLOW_STAT_NONE;

		skge->speed = SPEED_1000;
	पूर्ण

	अगर (!netअगर_carrier_ok(dev))
		genesis_link_up(skge);
	वापस 1;
पूर्ण

/* Poll to check क्रम link coming up.
 *
 * Since पूर्णांकernal PHY is wired to a level triggered pin, can't
 * get an पूर्णांकerrupt when carrier is detected, need to poll क्रम
 * link coming up.
 */
अटल व्योम xm_link_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा skge_port *skge = from_समयr(skge, t, link_समयr);
	काष्ठा net_device *dev = skge->netdev;
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_running(dev))
		वापस;

	spin_lock_irqsave(&hw->phy_lock, flags);

	/*
	 * Verअगरy that the link by checking GPIO रेजिस्टर three बार.
	 * This pin has the संकेत from the link_sync pin connected to it.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		अगर (xm_पढ़ो16(hw, port, XM_GP_PORT) & XM_GP_INP_ASS)
			जाओ link_करोwn;
	पूर्ण

	/* Re-enable पूर्णांकerrupt to detect link करोwn */
	अगर (xm_check_link(dev)) अणु
		u16 msk = xm_पढ़ो16(hw, port, XM_IMSK);
		msk &= ~XM_IS_INP_ASS;
		xm_ग_लिखो16(hw, port, XM_IMSK, msk);
		xm_पढ़ो16(hw, port, XM_ISRC);
	पूर्ण अन्यथा अणु
link_करोwn:
		mod_समयr(&skge->link_समयr,
			  round_jअगरfies(jअगरfies + LINK_HZ));
	पूर्ण
	spin_unlock_irqrestore(&hw->phy_lock, flags);
पूर्ण

अटल व्योम genesis_mac_init(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	काष्ठा net_device *dev = hw->dev[port];
	काष्ठा skge_port *skge = netdev_priv(dev);
	पूर्णांक jumbo = hw->dev[port]->mtu > ETH_DATA_LEN;
	पूर्णांक i;
	u32 r;
	अटल स्थिर u8 zero[6]  = अणु 0 पूर्ण;

	क्रम (i = 0; i < 10; i++) अणु
		skge_ग_लिखो16(hw, SK_REG(port, TX_MFF_CTRL1),
			     MFF_SET_MAC_RST);
		अगर (skge_पढ़ो16(hw, SK_REG(port, TX_MFF_CTRL1)) & MFF_SET_MAC_RST)
			जाओ reset_ok;
		udelay(1);
	पूर्ण

	netdev_warn(dev, "genesis reset failed\n");

 reset_ok:
	/* Unreset the XMAC. */
	skge_ग_लिखो16(hw, SK_REG(port, TX_MFF_CTRL1), MFF_CLR_MAC_RST);

	/*
	 * Perक्रमm additional initialization क्रम बाह्यal PHYs,
	 * namely क्रम the 1000baseTX cards that use the XMAC's
	 * GMII mode.
	 */
	अगर (hw->phy_type != SK_PHY_XMAC) अणु
		/* Take बाह्यal Phy out of reset */
		r = skge_पढ़ो32(hw, B2_GP_IO);
		अगर (port == 0)
			r |= GP_सूची_0|GP_IO_0;
		अन्यथा
			r |= GP_सूची_2|GP_IO_2;

		skge_ग_लिखो32(hw, B2_GP_IO, r);

		/* Enable GMII पूर्णांकerface */
		xm_ग_लिखो16(hw, port, XM_HW_CFG, XM_HW_GMII_MD);
	पूर्ण


	चयन (hw->phy_type) अणु
	हाल SK_PHY_XMAC:
		xm_phy_init(skge);
		अवरोध;
	हाल SK_PHY_BCOM:
		bcom_phy_init(skge);
		bcom_check_link(hw, port);
	पूर्ण

	/* Set Station Address */
	xm_outaddr(hw, port, XM_SA, dev->dev_addr);

	/* We करोn't use match addresses so clear */
	क्रम (i = 1; i < 16; i++)
		xm_outaddr(hw, port, XM_EXM(i), zero);

	/* Clear MIB counters */
	xm_ग_लिखो16(hw, port, XM_STAT_CMD,
			XM_SC_CLR_RXC | XM_SC_CLR_TXC);
	/* Clear two बार according to Errata #3 */
	xm_ग_लिखो16(hw, port, XM_STAT_CMD,
			XM_SC_CLR_RXC | XM_SC_CLR_TXC);

	/* configure Rx High Water Mark (XM_RX_HI_WM) */
	xm_ग_लिखो16(hw, port, XM_RX_HI_WM, 1450);

	/* We करोn't need the FCS appended to the packet. */
	r = XM_RX_LENERR_OK | XM_RX_STRIP_FCS;
	अगर (jumbo)
		r |= XM_RX_BIG_PK_OK;

	अगर (skge->duplex == DUPLEX_HALF) अणु
		/*
		 * If in manual half duplex mode the other side might be in
		 * full duplex mode, so ignore अगर a carrier extension is not seen
		 * on frames received
		 */
		r |= XM_RX_DIS_CEXT;
	पूर्ण
	xm_ग_लिखो16(hw, port, XM_RX_CMD, r);

	/* We want लघु frames padded to 60 bytes. */
	xm_ग_लिखो16(hw, port, XM_TX_CMD, XM_TX_AUTO_PAD);

	/* Increase threshold क्रम jumbo frames on dual port */
	अगर (hw->ports > 1 && jumbo)
		xm_ग_लिखो16(hw, port, XM_TX_THR, 1020);
	अन्यथा
		xm_ग_लिखो16(hw, port, XM_TX_THR, 512);

	/*
	 * Enable the reception of all error frames. This is
	 * a necessary evil due to the design of the XMAC. The
	 * XMAC's receive FIFO is only 8K in size, however jumbo
	 * frames can be up to 9000 bytes in length. When bad
	 * frame filtering is enabled, the XMAC's RX FIFO operates
	 * in 'store and forward' mode. For this to work, the
	 * entire frame has to fit पूर्णांकo the FIFO, but that means
	 * that jumbo frames larger than 8192 bytes will be
	 * truncated. Disabling all bad frame filtering causes
	 * the RX FIFO to operate in streaming mode, in which
	 * हाल the XMAC will start transferring frames out of the
	 * RX FIFO as soon as the FIFO threshold is reached.
	 */
	xm_ग_लिखो32(hw, port, XM_MODE, XM_DEF_MODE);


	/*
	 * Initialize the Receive Counter Event Mask (XM_RX_EV_MSK)
	 *	- Enable all bits excepting 'Octets Rx OK Low CntOv'
	 *	  and 'Octets Rx OK Hi Cnt Ov'.
	 */
	xm_ग_लिखो32(hw, port, XM_RX_EV_MSK, XMR_DEF_MSK);

	/*
	 * Initialize the Transmit Counter Event Mask (XM_TX_EV_MSK)
	 *	- Enable all bits excepting 'Octets Tx OK Low CntOv'
	 *	  and 'Octets Tx OK Hi Cnt Ov'.
	 */
	xm_ग_लिखो32(hw, port, XM_TX_EV_MSK, XMT_DEF_MSK);

	/* Configure MAC arbiter */
	skge_ग_लिखो16(hw, B3_MA_TO_CTRL, MA_RST_CLR);

	/* configure समयout values */
	skge_ग_लिखो8(hw, B3_MA_TOINI_RX1, 72);
	skge_ग_लिखो8(hw, B3_MA_TOINI_RX2, 72);
	skge_ग_लिखो8(hw, B3_MA_TOINI_TX1, 72);
	skge_ग_लिखो8(hw, B3_MA_TOINI_TX2, 72);

	skge_ग_लिखो8(hw, B3_MA_RCINI_RX1, 0);
	skge_ग_लिखो8(hw, B3_MA_RCINI_RX2, 0);
	skge_ग_लिखो8(hw, B3_MA_RCINI_TX1, 0);
	skge_ग_लिखो8(hw, B3_MA_RCINI_TX2, 0);

	/* Configure Rx MAC FIFO */
	skge_ग_लिखो8(hw, SK_REG(port, RX_MFF_CTRL2), MFF_RST_CLR);
	skge_ग_लिखो16(hw, SK_REG(port, RX_MFF_CTRL1), MFF_ENA_TIM_PAT);
	skge_ग_लिखो8(hw, SK_REG(port, RX_MFF_CTRL2), MFF_ENA_OP_MD);

	/* Configure Tx MAC FIFO */
	skge_ग_लिखो8(hw, SK_REG(port, TX_MFF_CTRL2), MFF_RST_CLR);
	skge_ग_लिखो16(hw, SK_REG(port, TX_MFF_CTRL1), MFF_TX_CTRL_DEF);
	skge_ग_लिखो8(hw, SK_REG(port, TX_MFF_CTRL2), MFF_ENA_OP_MD);

	अगर (jumbo) अणु
		/* Enable frame flushing अगर jumbo frames used */
		skge_ग_लिखो16(hw, SK_REG(port, RX_MFF_CTRL1), MFF_ENA_FLUSH);
	पूर्ण अन्यथा अणु
		/* enable समयout समयrs अगर normal frames */
		skge_ग_लिखो16(hw, B3_PA_CTRL,
			     (port == 0) ? PA_ENA_TO_TX1 : PA_ENA_TO_TX2);
	पूर्ण
पूर्ण

अटल व्योम genesis_stop(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	अचिन्हित retries = 1000;
	u16 cmd;

	/* Disable Tx and Rx */
	cmd = xm_पढ़ो16(hw, port, XM_MMU_CMD);
	cmd &= ~(XM_MMU_ENA_RX | XM_MMU_ENA_TX);
	xm_ग_लिखो16(hw, port, XM_MMU_CMD, cmd);

	genesis_reset(hw, port);

	/* Clear Tx packet arbiter समयout IRQ */
	skge_ग_लिखो16(hw, B3_PA_CTRL,
		     port == 0 ? PA_CLR_TO_TX1 : PA_CLR_TO_TX2);

	/* Reset the MAC */
	skge_ग_लिखो16(hw, SK_REG(port, TX_MFF_CTRL1), MFF_CLR_MAC_RST);
	करो अणु
		skge_ग_लिखो16(hw, SK_REG(port, TX_MFF_CTRL1), MFF_SET_MAC_RST);
		अगर (!(skge_पढ़ो16(hw, SK_REG(port, TX_MFF_CTRL1)) & MFF_SET_MAC_RST))
			अवरोध;
	पूर्ण जबतक (--retries > 0);

	/* For बाह्यal PHYs there must be special handling */
	अगर (hw->phy_type != SK_PHY_XMAC) अणु
		u32 reg = skge_पढ़ो32(hw, B2_GP_IO);
		अगर (port == 0) अणु
			reg |= GP_सूची_0;
			reg &= ~GP_IO_0;
		पूर्ण अन्यथा अणु
			reg |= GP_सूची_2;
			reg &= ~GP_IO_2;
		पूर्ण
		skge_ग_लिखो32(hw, B2_GP_IO, reg);
		skge_पढ़ो32(hw, B2_GP_IO);
	पूर्ण

	xm_ग_लिखो16(hw, port, XM_MMU_CMD,
			xm_पढ़ो16(hw, port, XM_MMU_CMD)
			& ~(XM_MMU_ENA_RX | XM_MMU_ENA_TX));

	xm_पढ़ो16(hw, port, XM_MMU_CMD);
पूर्ण


अटल व्योम genesis_get_stats(काष्ठा skge_port *skge, u64 *data)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	पूर्णांक i;
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;

	xm_ग_लिखो16(hw, port,
			XM_STAT_CMD, XM_SC_SNP_TXC | XM_SC_SNP_RXC);

	/* रुको क्रम update to complete */
	जबतक (xm_पढ़ो16(hw, port, XM_STAT_CMD)
	       & (XM_SC_SNP_TXC | XM_SC_SNP_RXC)) अणु
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
		udelay(10);
	पूर्ण

	/* special हाल क्रम 64 bit octet counter */
	data[0] = (u64) xm_पढ़ो32(hw, port, XM_TXO_OK_HI) << 32
		| xm_पढ़ो32(hw, port, XM_TXO_OK_LO);
	data[1] = (u64) xm_पढ़ो32(hw, port, XM_RXO_OK_HI) << 32
		| xm_पढ़ो32(hw, port, XM_RXO_OK_LO);

	क्रम (i = 2; i < ARRAY_SIZE(skge_stats); i++)
		data[i] = xm_पढ़ो32(hw, port, skge_stats[i].xmac_offset);
पूर्ण

अटल व्योम genesis_mac_पूर्णांकr(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	काष्ठा net_device *dev = hw->dev[port];
	काष्ठा skge_port *skge = netdev_priv(dev);
	u16 status = xm_पढ़ो16(hw, port, XM_ISRC);

	netअगर_prपूर्णांकk(skge, पूर्णांकr, KERN_DEBUG, skge->netdev,
		     "mac interrupt status 0x%x\n", status);

	अगर (hw->phy_type == SK_PHY_XMAC && (status & XM_IS_INP_ASS)) अणु
		xm_link_करोwn(hw, port);
		mod_समयr(&skge->link_समयr, jअगरfies + 1);
	पूर्ण

	अगर (status & XM_IS_TXF_UR) अणु
		xm_ग_लिखो32(hw, port, XM_MODE, XM_MD_FTF);
		++dev->stats.tx_fअगरo_errors;
	पूर्ण
पूर्ण

अटल व्योम genesis_link_up(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	u16 cmd, msk;
	u32 mode;

	cmd = xm_पढ़ो16(hw, port, XM_MMU_CMD);

	/*
	 * enabling छोड़ो frame reception is required क्रम 1000BT
	 * because the XMAC is not reset अगर the link is going करोwn
	 */
	अगर (skge->flow_status == FLOW_STAT_NONE ||
	    skge->flow_status == FLOW_STAT_LOC_SEND)
		/* Disable Pause Frame Reception */
		cmd |= XM_MMU_IGN_PF;
	अन्यथा
		/* Enable Pause Frame Reception */
		cmd &= ~XM_MMU_IGN_PF;

	xm_ग_लिखो16(hw, port, XM_MMU_CMD, cmd);

	mode = xm_पढ़ो32(hw, port, XM_MODE);
	अगर (skge->flow_status == FLOW_STAT_SYMMETRIC ||
	    skge->flow_status == FLOW_STAT_LOC_SEND) अणु
		/*
		 * Configure Pause Frame Generation
		 * Use पूर्णांकernal and बाह्यal Pause Frame Generation.
		 * Sending छोड़ो frames is edge triggered.
		 * Send a Pause frame with the maximum छोड़ो समय अगर
		 * पूर्णांकernal oder बाह्यal FIFO full condition occurs.
		 * Send a zero छोड़ो समय frame to re-start transmission.
		 */
		/* XM_PAUSE_DA = '010000C28001' (शेष) */
		/* XM_MAC_PTIME = 0xffff (maximum) */
		/* remember this value is defined in big endian (!) */
		xm_ग_लिखो16(hw, port, XM_MAC_PTIME, 0xffff);

		mode |= XM_PAUSE_MODE;
		skge_ग_लिखो16(hw, SK_REG(port, RX_MFF_CTRL1), MFF_ENA_PAUSE);
	पूर्ण अन्यथा अणु
		/*
		 * disable छोड़ो frame generation is required क्रम 1000BT
		 * because the XMAC is not reset अगर the link is going करोwn
		 */
		/* Disable Pause Mode in Mode Register */
		mode &= ~XM_PAUSE_MODE;

		skge_ग_लिखो16(hw, SK_REG(port, RX_MFF_CTRL1), MFF_DIS_PAUSE);
	पूर्ण

	xm_ग_लिखो32(hw, port, XM_MODE, mode);

	/* Turn on detection of Tx underrun */
	msk = xm_पढ़ो16(hw, port, XM_IMSK);
	msk &= ~XM_IS_TXF_UR;
	xm_ग_लिखो16(hw, port, XM_IMSK, msk);

	xm_पढ़ो16(hw, port, XM_ISRC);

	/* get MMU Command Reg. */
	cmd = xm_पढ़ो16(hw, port, XM_MMU_CMD);
	अगर (hw->phy_type != SK_PHY_XMAC && skge->duplex == DUPLEX_FULL)
		cmd |= XM_MMU_GMII_FD;

	/*
	 * Workaround BCOM Errata (#10523) क्रम all BCom Phys
	 * Enable Power Management after link up
	 */
	अगर (hw->phy_type == SK_PHY_BCOM) अणु
		xm_phy_ग_लिखो(hw, port, PHY_BCOM_AUX_CTRL,
			     xm_phy_पढ़ो(hw, port, PHY_BCOM_AUX_CTRL)
			     & ~PHY_B_AC_DIS_PM);
		xm_phy_ग_लिखो(hw, port, PHY_BCOM_INT_MASK, PHY_B_DEF_MSK);
	पूर्ण

	/* enable Rx/Tx */
	xm_ग_लिखो16(hw, port, XM_MMU_CMD,
			cmd | XM_MMU_ENA_RX | XM_MMU_ENA_TX);
	skge_link_up(skge);
पूर्ण


अटल अंतरभूत व्योम bcom_phy_पूर्णांकr(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	u16 isrc;

	isrc = xm_phy_पढ़ो(hw, port, PHY_BCOM_INT_STAT);
	netअगर_prपूर्णांकk(skge, पूर्णांकr, KERN_DEBUG, skge->netdev,
		     "phy interrupt status 0x%x\n", isrc);

	अगर (isrc & PHY_B_IS_PSE)
		pr_err("%s: uncorrectable pair swap error\n",
		       hw->dev[port]->name);

	/* Workaround BCom Errata:
	 *	enable and disable loopback mode अगर "NO HCD" occurs.
	 */
	अगर (isrc & PHY_B_IS_NO_HDCL) अणु
		u16 ctrl = xm_phy_पढ़ो(hw, port, PHY_BCOM_CTRL);
		xm_phy_ग_लिखो(hw, port, PHY_BCOM_CTRL,
				  ctrl | PHY_CT_LOOP);
		xm_phy_ग_लिखो(hw, port, PHY_BCOM_CTRL,
				  ctrl & ~PHY_CT_LOOP);
	पूर्ण

	अगर (isrc & (PHY_B_IS_AN_PR | PHY_B_IS_LST_CHANGE))
		bcom_check_link(hw, port);

पूर्ण

अटल पूर्णांक gm_phy_ग_लिखो(काष्ठा skge_hw *hw, पूर्णांक port, u16 reg, u16 val)
अणु
	पूर्णांक i;

	gma_ग_लिखो16(hw, port, GM_SMI_DATA, val);
	gma_ग_लिखो16(hw, port, GM_SMI_CTRL,
			 GM_SMI_CT_PHY_AD(hw->phy_addr) | GM_SMI_CT_REG_AD(reg));
	क्रम (i = 0; i < PHY_RETRIES; i++) अणु
		udelay(1);

		अगर (!(gma_पढ़ो16(hw, port, GM_SMI_CTRL) & GM_SMI_CT_BUSY))
			वापस 0;
	पूर्ण

	pr_warn("%s: phy write timeout\n", hw->dev[port]->name);
	वापस -EIO;
पूर्ण

अटल पूर्णांक __gm_phy_पढ़ो(काष्ठा skge_hw *hw, पूर्णांक port, u16 reg, u16 *val)
अणु
	पूर्णांक i;

	gma_ग_लिखो16(hw, port, GM_SMI_CTRL,
			 GM_SMI_CT_PHY_AD(hw->phy_addr)
			 | GM_SMI_CT_REG_AD(reg) | GM_SMI_CT_OP_RD);

	क्रम (i = 0; i < PHY_RETRIES; i++) अणु
		udelay(1);
		अगर (gma_पढ़ो16(hw, port, GM_SMI_CTRL) & GM_SMI_CT_RD_VAL)
			जाओ पढ़ोy;
	पूर्ण

	वापस -ETIMEDOUT;
 पढ़ोy:
	*val = gma_पढ़ो16(hw, port, GM_SMI_DATA);
	वापस 0;
पूर्ण

अटल u16 gm_phy_पढ़ो(काष्ठा skge_hw *hw, पूर्णांक port, u16 reg)
अणु
	u16 v = 0;
	अगर (__gm_phy_पढ़ो(hw, port, reg, &v))
		pr_warn("%s: phy read timeout\n", hw->dev[port]->name);
	वापस v;
पूर्ण

/* Marvell Phy Initialization */
अटल व्योम yukon_init(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	काष्ठा skge_port *skge = netdev_priv(hw->dev[port]);
	u16 ctrl, ct1000, adv;

	अगर (skge->स्वतःneg == AUTONEG_ENABLE) अणु
		u16 ectrl = gm_phy_पढ़ो(hw, port, PHY_MARV_EXT_CTRL);

		ectrl &= ~(PHY_M_EC_M_DSC_MSK | PHY_M_EC_S_DSC_MSK |
			  PHY_M_EC_MAC_S_MSK);
		ectrl |= PHY_M_EC_MAC_S(MAC_TX_CLK_25_MHZ);

		ectrl |= PHY_M_EC_M_DSC(0) | PHY_M_EC_S_DSC(1);

		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_CTRL, ectrl);
	पूर्ण

	ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_CTRL);
	अगर (skge->स्वतःneg == AUTONEG_DISABLE)
		ctrl &= ~PHY_CT_ANE;

	ctrl |= PHY_CT_RESET;
	gm_phy_ग_लिखो(hw, port, PHY_MARV_CTRL, ctrl);

	ctrl = 0;
	ct1000 = 0;
	adv = PHY_AN_CSMA;

	अगर (skge->स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (hw->copper) अणु
			अगर (skge->advertising & ADVERTISED_1000baseT_Full)
				ct1000 |= PHY_M_1000C_AFD;
			अगर (skge->advertising & ADVERTISED_1000baseT_Half)
				ct1000 |= PHY_M_1000C_AHD;
			अगर (skge->advertising & ADVERTISED_100baseT_Full)
				adv |= PHY_M_AN_100_FD;
			अगर (skge->advertising & ADVERTISED_100baseT_Half)
				adv |= PHY_M_AN_100_HD;
			अगर (skge->advertising & ADVERTISED_10baseT_Full)
				adv |= PHY_M_AN_10_FD;
			अगर (skge->advertising & ADVERTISED_10baseT_Half)
				adv |= PHY_M_AN_10_HD;

			/* Set Flow-control capabilities */
			adv |= phy_छोड़ो_map[skge->flow_control];
		पूर्ण अन्यथा अणु
			अगर (skge->advertising & ADVERTISED_1000baseT_Full)
				adv |= PHY_M_AN_1000X_AFD;
			अगर (skge->advertising & ADVERTISED_1000baseT_Half)
				adv |= PHY_M_AN_1000X_AHD;

			adv |= fiber_छोड़ो_map[skge->flow_control];
		पूर्ण

		/* Restart Auto-negotiation */
		ctrl |= PHY_CT_ANE | PHY_CT_RE_CFG;
	पूर्ण अन्यथा अणु
		/* क्रमced speed/duplex settings */
		ct1000 = PHY_M_1000C_MSE;

		अगर (skge->duplex == DUPLEX_FULL)
			ctrl |= PHY_CT_DUP_MD;

		चयन (skge->speed) अणु
		हाल SPEED_1000:
			ctrl |= PHY_CT_SP1000;
			अवरोध;
		हाल SPEED_100:
			ctrl |= PHY_CT_SP100;
			अवरोध;
		पूर्ण

		ctrl |= PHY_CT_RESET;
	पूर्ण

	gm_phy_ग_लिखो(hw, port, PHY_MARV_1000T_CTRL, ct1000);

	gm_phy_ग_लिखो(hw, port, PHY_MARV_AUNE_ADV, adv);
	gm_phy_ग_लिखो(hw, port, PHY_MARV_CTRL, ctrl);

	/* Enable phy पूर्णांकerrupt on स्वतःnegotiation complete (or link up) */
	अगर (skge->स्वतःneg == AUTONEG_ENABLE)
		gm_phy_ग_लिखो(hw, port, PHY_MARV_INT_MASK, PHY_M_IS_AN_MSK);
	अन्यथा
		gm_phy_ग_लिखो(hw, port, PHY_MARV_INT_MASK, PHY_M_IS_DEF_MSK);
पूर्ण

अटल व्योम yukon_reset(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	gm_phy_ग_लिखो(hw, port, PHY_MARV_INT_MASK, 0);/* disable PHY IRQs */
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H1, 0);	/* clear MC hash */
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H2, 0);
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H3, 0);
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H4, 0);

	gma_ग_लिखो16(hw, port, GM_RX_CTRL,
			 gma_पढ़ो16(hw, port, GM_RX_CTRL)
			 | GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA);
पूर्ण

/* Apparently, early versions of Yukon-Lite had wrong chip_id? */
अटल पूर्णांक is_yukon_lite_a0(काष्ठा skge_hw *hw)
अणु
	u32 reg;
	पूर्णांक ret;

	अगर (hw->chip_id != CHIP_ID_YUKON)
		वापस 0;

	reg = skge_पढ़ो32(hw, B2_FAR);
	skge_ग_लिखो8(hw, B2_FAR + 3, 0xff);
	ret = (skge_पढ़ो8(hw, B2_FAR + 3) != 0);
	skge_ग_लिखो32(hw, B2_FAR, reg);
	वापस ret;
पूर्ण

अटल व्योम yukon_mac_init(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	काष्ठा skge_port *skge = netdev_priv(hw->dev[port]);
	पूर्णांक i;
	u32 reg;
	स्थिर u8 *addr = hw->dev[port]->dev_addr;

	/* WA code क्रम COMA mode -- set PHY reset */
	अगर (hw->chip_id == CHIP_ID_YUKON_LITE &&
	    hw->chip_rev >= CHIP_REV_YU_LITE_A3) अणु
		reg = skge_पढ़ो32(hw, B2_GP_IO);
		reg |= GP_सूची_9 | GP_IO_9;
		skge_ग_लिखो32(hw, B2_GP_IO, reg);
	पूर्ण

	/* hard reset */
	skge_ग_लिखो32(hw, SK_REG(port, GPHY_CTRL), GPC_RST_SET);
	skge_ग_लिखो32(hw, SK_REG(port, GMAC_CTRL), GMC_RST_SET);

	/* WA code क्रम COMA mode -- clear PHY reset */
	अगर (hw->chip_id == CHIP_ID_YUKON_LITE &&
	    hw->chip_rev >= CHIP_REV_YU_LITE_A3) अणु
		reg = skge_पढ़ो32(hw, B2_GP_IO);
		reg |= GP_सूची_9;
		reg &= ~GP_IO_9;
		skge_ग_लिखो32(hw, B2_GP_IO, reg);
	पूर्ण

	/* Set hardware config mode */
	reg = GPC_INT_POL_HI | GPC_DIS_FC | GPC_DIS_SLEEP |
		GPC_ENA_XC | GPC_ANEG_ADV_ALL_M | GPC_ENA_PAUSE;
	reg |= hw->copper ? GPC_HWCFG_GMII_COP : GPC_HWCFG_GMII_FIB;

	/* Clear GMC reset */
	skge_ग_लिखो32(hw, SK_REG(port, GPHY_CTRL), reg | GPC_RST_SET);
	skge_ग_लिखो32(hw, SK_REG(port, GPHY_CTRL), reg | GPC_RST_CLR);
	skge_ग_लिखो32(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_ON | GMC_RST_CLR);

	अगर (skge->स्वतःneg == AUTONEG_DISABLE) अणु
		reg = GM_GPCR_AU_ALL_DIS;
		gma_ग_लिखो16(hw, port, GM_GP_CTRL,
				 gma_पढ़ो16(hw, port, GM_GP_CTRL) | reg);

		चयन (skge->speed) अणु
		हाल SPEED_1000:
			reg &= ~GM_GPCR_SPEED_100;
			reg |= GM_GPCR_SPEED_1000;
			अवरोध;
		हाल SPEED_100:
			reg &= ~GM_GPCR_SPEED_1000;
			reg |= GM_GPCR_SPEED_100;
			अवरोध;
		हाल SPEED_10:
			reg &= ~(GM_GPCR_SPEED_1000 | GM_GPCR_SPEED_100);
			अवरोध;
		पूर्ण

		अगर (skge->duplex == DUPLEX_FULL)
			reg |= GM_GPCR_DUP_FULL;
	पूर्ण अन्यथा
		reg = GM_GPCR_SPEED_1000 | GM_GPCR_SPEED_100 | GM_GPCR_DUP_FULL;

	चयन (skge->flow_control) अणु
	हाल FLOW_MODE_NONE:
		skge_ग_लिखो32(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);
		reg |= GM_GPCR_FC_TX_DIS | GM_GPCR_FC_RX_DIS | GM_GPCR_AU_FCT_DIS;
		अवरोध;
	हाल FLOW_MODE_LOC_SEND:
		/* disable Rx flow-control */
		reg |= GM_GPCR_FC_RX_DIS | GM_GPCR_AU_FCT_DIS;
		अवरोध;
	हाल FLOW_MODE_SYMMETRIC:
	हाल FLOW_MODE_SYM_OR_REM:
		/* enable Tx & Rx flow-control */
		अवरोध;
	पूर्ण

	gma_ग_लिखो16(hw, port, GM_GP_CTRL, reg);
	skge_पढ़ो16(hw, SK_REG(port, GMAC_IRQ_SRC));

	yukon_init(hw, port);

	/* MIB clear */
	reg = gma_पढ़ो16(hw, port, GM_PHY_ADDR);
	gma_ग_लिखो16(hw, port, GM_PHY_ADDR, reg | GM_PAR_MIB_CLR);

	क्रम (i = 0; i < GM_MIB_CNT_SIZE; i++)
		gma_पढ़ो16(hw, port, GM_MIB_CNT_BASE + 8*i);
	gma_ग_लिखो16(hw, port, GM_PHY_ADDR, reg);

	/* transmit control */
	gma_ग_लिखो16(hw, port, GM_TX_CTRL, TX_COL_THR(TX_COL_DEF));

	/* receive control reg: unicast + multicast + no FCS  */
	gma_ग_लिखो16(hw, port, GM_RX_CTRL,
			 GM_RXCR_UCF_ENA | GM_RXCR_CRC_DIS | GM_RXCR_MCF_ENA);

	/* transmit flow control */
	gma_ग_लिखो16(hw, port, GM_TX_FLOW_CTRL, 0xffff);

	/* transmit parameter */
	gma_ग_लिखो16(hw, port, GM_TX_PARAM,
			 TX_JAM_LEN_VAL(TX_JAM_LEN_DEF) |
			 TX_JAM_IPG_VAL(TX_JAM_IPG_DEF) |
			 TX_IPG_JAM_DATA(TX_IPG_JAM_DEF));

	/* configure the Serial Mode Register */
	reg = DATA_BLIND_VAL(DATA_BLIND_DEF)
		| GM_SMOD_VLAN_ENA
		| IPG_DATA_VAL(IPG_DATA_DEF);

	अगर (hw->dev[port]->mtu > ETH_DATA_LEN)
		reg |= GM_SMOD_JUMBO_ENA;

	gma_ग_लिखो16(hw, port, GM_SERIAL_MODE, reg);

	/* physical address: used क्रम छोड़ो frames */
	gma_set_addr(hw, port, GM_SRC_ADDR_1L, addr);
	/* भव address क्रम data */
	gma_set_addr(hw, port, GM_SRC_ADDR_2L, addr);

	/* enable पूर्णांकerrupt mask क्रम counter overflows */
	gma_ग_लिखो16(hw, port, GM_TX_IRQ_MSK, 0);
	gma_ग_लिखो16(hw, port, GM_RX_IRQ_MSK, 0);
	gma_ग_लिखो16(hw, port, GM_TR_IRQ_MSK, 0);

	/* Initialize Mac Fअगरo */

	/* Configure Rx MAC FIFO */
	skge_ग_लिखो16(hw, SK_REG(port, RX_GMF_FL_MSK), RX_FF_FL_DEF_MSK);
	reg = GMF_OPER_ON | GMF_RX_F_FL_ON;

	/* disable Rx GMAC FIFO Flush क्रम YUKON-Lite Rev. A0 only */
	अगर (is_yukon_lite_a0(hw))
		reg &= ~GMF_RX_F_FL_ON;

	skge_ग_लिखो8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_CLR);
	skge_ग_लिखो16(hw, SK_REG(port, RX_GMF_CTRL_T), reg);
	/*
	 * because Pause Packet Truncation in GMAC is not working
	 * we have to increase the Flush Threshold to 64 bytes
	 * in order to flush छोड़ो packets in Rx FIFO on Yukon-1
	 */
	skge_ग_लिखो16(hw, SK_REG(port, RX_GMF_FL_THR), RX_GMF_FL_THR_DEF+1);

	/* Configure Tx MAC FIFO */
	skge_ग_लिखो8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_RST_CLR);
	skge_ग_लिखो16(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_OPER_ON);
पूर्ण

/* Go पूर्णांकo घातer करोwn mode */
अटल व्योम yukon_suspend(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	u16 ctrl;

	ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_PHY_CTRL);
	ctrl |= PHY_M_PC_POL_R_DIS;
	gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL, ctrl);

	ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_CTRL);
	ctrl |= PHY_CT_RESET;
	gm_phy_ग_लिखो(hw, port, PHY_MARV_CTRL, ctrl);

	/* चयन IEEE compatible घातer करोwn mode on */
	ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_CTRL);
	ctrl |= PHY_CT_PDOWN;
	gm_phy_ग_लिखो(hw, port, PHY_MARV_CTRL, ctrl);
पूर्ण

अटल व्योम yukon_stop(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;

	skge_ग_लिखो8(hw, SK_REG(port, GMAC_IRQ_MSK), 0);
	yukon_reset(hw, port);

	gma_ग_लिखो16(hw, port, GM_GP_CTRL,
			 gma_पढ़ो16(hw, port, GM_GP_CTRL)
			 & ~(GM_GPCR_TX_ENA|GM_GPCR_RX_ENA));
	gma_पढ़ो16(hw, port, GM_GP_CTRL);

	yukon_suspend(hw, port);

	/* set GPHY Control reset */
	skge_ग_लिखो8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_SET);
	skge_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_RST_SET);
पूर्ण

अटल व्योम yukon_get_stats(काष्ठा skge_port *skge, u64 *data)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	पूर्णांक i;

	data[0] = (u64) gma_पढ़ो32(hw, port, GM_TXO_OK_HI) << 32
		| gma_पढ़ो32(hw, port, GM_TXO_OK_LO);
	data[1] = (u64) gma_पढ़ो32(hw, port, GM_RXO_OK_HI) << 32
		| gma_पढ़ो32(hw, port, GM_RXO_OK_LO);

	क्रम (i = 2; i < ARRAY_SIZE(skge_stats); i++)
		data[i] = gma_पढ़ो32(hw, port,
					  skge_stats[i].gma_offset);
पूर्ण

अटल व्योम yukon_mac_पूर्णांकr(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	काष्ठा net_device *dev = hw->dev[port];
	काष्ठा skge_port *skge = netdev_priv(dev);
	u8 status = skge_पढ़ो8(hw, SK_REG(port, GMAC_IRQ_SRC));

	netअगर_prपूर्णांकk(skge, पूर्णांकr, KERN_DEBUG, skge->netdev,
		     "mac interrupt status 0x%x\n", status);

	अगर (status & GM_IS_RX_FF_OR) अणु
		++dev->stats.rx_fअगरo_errors;
		skge_ग_लिखो8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_CLI_RX_FO);
	पूर्ण

	अगर (status & GM_IS_TX_FF_UR) अणु
		++dev->stats.tx_fअगरo_errors;
		skge_ग_लिखो8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_CLI_TX_FU);
	पूर्ण

पूर्ण

अटल u16 yukon_speed(स्थिर काष्ठा skge_hw *hw, u16 aux)
अणु
	चयन (aux & PHY_M_PS_SPEED_MSK) अणु
	हाल PHY_M_PS_SPEED_1000:
		वापस SPEED_1000;
	हाल PHY_M_PS_SPEED_100:
		वापस SPEED_100;
	शेष:
		वापस SPEED_10;
	पूर्ण
पूर्ण

अटल व्योम yukon_link_up(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	u16 reg;

	/* Enable Transmit FIFO Underrun */
	skge_ग_लिखो8(hw, SK_REG(port, GMAC_IRQ_MSK), GMAC_DEF_MSK);

	reg = gma_पढ़ो16(hw, port, GM_GP_CTRL);
	अगर (skge->duplex == DUPLEX_FULL || skge->स्वतःneg == AUTONEG_ENABLE)
		reg |= GM_GPCR_DUP_FULL;

	/* enable Rx/Tx */
	reg |= GM_GPCR_RX_ENA | GM_GPCR_TX_ENA;
	gma_ग_लिखो16(hw, port, GM_GP_CTRL, reg);

	gm_phy_ग_लिखो(hw, port, PHY_MARV_INT_MASK, PHY_M_IS_DEF_MSK);
	skge_link_up(skge);
पूर्ण

अटल व्योम yukon_link_करोwn(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	u16 ctrl;

	ctrl = gma_पढ़ो16(hw, port, GM_GP_CTRL);
	ctrl &= ~(GM_GPCR_RX_ENA | GM_GPCR_TX_ENA);
	gma_ग_लिखो16(hw, port, GM_GP_CTRL, ctrl);

	अगर (skge->flow_status == FLOW_STAT_REM_SEND) अणु
		ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_AUNE_ADV);
		ctrl |= PHY_M_AN_ASP;
		/* restore Asymmetric Pause bit */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_AUNE_ADV, ctrl);
	पूर्ण

	skge_link_करोwn(skge);

	yukon_init(hw, port);
पूर्ण

अटल व्योम yukon_phy_पूर्णांकr(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	स्थिर अक्षर *reason = शून्य;
	u16 istatus, phystat;

	istatus = gm_phy_पढ़ो(hw, port, PHY_MARV_INT_STAT);
	phystat = gm_phy_पढ़ो(hw, port, PHY_MARV_PHY_STAT);

	netअगर_prपूर्णांकk(skge, पूर्णांकr, KERN_DEBUG, skge->netdev,
		     "phy interrupt status 0x%x 0x%x\n", istatus, phystat);

	अगर (istatus & PHY_M_IS_AN_COMPL) अणु
		अगर (gm_phy_पढ़ो(hw, port, PHY_MARV_AUNE_LP)
		    & PHY_M_AN_RF) अणु
			reason = "remote fault";
			जाओ failed;
		पूर्ण

		अगर (gm_phy_पढ़ो(hw, port, PHY_MARV_1000T_STAT) & PHY_B_1000S_MSF) अणु
			reason = "master/slave fault";
			जाओ failed;
		पूर्ण

		अगर (!(phystat & PHY_M_PS_SPDUP_RES)) अणु
			reason = "speed/duplex";
			जाओ failed;
		पूर्ण

		skge->duplex = (phystat & PHY_M_PS_FULL_DUP)
			? DUPLEX_FULL : DUPLEX_HALF;
		skge->speed = yukon_speed(hw, phystat);

		/* We are using IEEE 802.3z/D5.0 Table 37-4 */
		चयन (phystat & PHY_M_PS_PAUSE_MSK) अणु
		हाल PHY_M_PS_PAUSE_MSK:
			skge->flow_status = FLOW_STAT_SYMMETRIC;
			अवरोध;
		हाल PHY_M_PS_RX_P_EN:
			skge->flow_status = FLOW_STAT_REM_SEND;
			अवरोध;
		हाल PHY_M_PS_TX_P_EN:
			skge->flow_status = FLOW_STAT_LOC_SEND;
			अवरोध;
		शेष:
			skge->flow_status = FLOW_STAT_NONE;
		पूर्ण

		अगर (skge->flow_status == FLOW_STAT_NONE ||
		    (skge->speed < SPEED_1000 && skge->duplex == DUPLEX_HALF))
			skge_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);
		अन्यथा
			skge_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_ON);
		yukon_link_up(skge);
		वापस;
	पूर्ण

	अगर (istatus & PHY_M_IS_LSP_CHANGE)
		skge->speed = yukon_speed(hw, phystat);

	अगर (istatus & PHY_M_IS_DUP_CHANGE)
		skge->duplex = (phystat & PHY_M_PS_FULL_DUP) ? DUPLEX_FULL : DUPLEX_HALF;
	अगर (istatus & PHY_M_IS_LST_CHANGE) अणु
		अगर (phystat & PHY_M_PS_LINK_UP)
			yukon_link_up(skge);
		अन्यथा
			yukon_link_करोwn(skge);
	पूर्ण
	वापस;
 failed:
	pr_err("%s: autonegotiation failed (%s)\n", skge->netdev->name, reason);

	/* XXX restart स्वतःnegotiation? */
पूर्ण

अटल व्योम skge_phy_reset(काष्ठा skge_port *skge)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	काष्ठा net_device *dev = hw->dev[port];

	netअगर_stop_queue(skge->netdev);
	netअगर_carrier_off(skge->netdev);

	spin_lock_bh(&hw->phy_lock);
	अगर (is_genesis(hw)) अणु
		genesis_reset(hw, port);
		genesis_mac_init(hw, port);
	पूर्ण अन्यथा अणु
		yukon_reset(hw, port);
		yukon_init(hw, port);
	पूर्ण
	spin_unlock_bh(&hw->phy_lock);

	skge_set_multicast(dev);
पूर्ण

/* Basic MII support */
अटल पूर्णांक skge_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक err = -EOPNOTSUPP;

	अगर (!netअगर_running(dev))
		वापस -ENODEV;	/* Phy still in reset */

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = hw->phy_addr;

		fallthrough;
	हाल SIOCGMIIREG: अणु
		u16 val = 0;
		spin_lock_bh(&hw->phy_lock);

		अगर (is_genesis(hw))
			err = __xm_phy_पढ़ो(hw, skge->port, data->reg_num & 0x1f, &val);
		अन्यथा
			err = __gm_phy_पढ़ो(hw, skge->port, data->reg_num & 0x1f, &val);
		spin_unlock_bh(&hw->phy_lock);
		data->val_out = val;
		अवरोध;
	पूर्ण

	हाल SIOCSMIIREG:
		spin_lock_bh(&hw->phy_lock);
		अगर (is_genesis(hw))
			err = xm_phy_ग_लिखो(hw, skge->port, data->reg_num & 0x1f,
				   data->val_in);
		अन्यथा
			err = gm_phy_ग_लिखो(hw, skge->port, data->reg_num & 0x1f,
				   data->val_in);
		spin_unlock_bh(&hw->phy_lock);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम skge_ramset(काष्ठा skge_hw *hw, u16 q, u32 start, माप_प्रकार len)
अणु
	u32 end;

	start /= 8;
	len /= 8;
	end = start + len - 1;

	skge_ग_लिखो8(hw, RB_ADDR(q, RB_CTRL), RB_RST_CLR);
	skge_ग_लिखो32(hw, RB_ADDR(q, RB_START), start);
	skge_ग_लिखो32(hw, RB_ADDR(q, RB_WP), start);
	skge_ग_लिखो32(hw, RB_ADDR(q, RB_RP), start);
	skge_ग_लिखो32(hw, RB_ADDR(q, RB_END), end);

	अगर (q == Q_R1 || q == Q_R2) अणु
		/* Set thresholds on receive queue's */
		skge_ग_लिखो32(hw, RB_ADDR(q, RB_RX_UTPP),
			     start + (2*len)/3);
		skge_ग_लिखो32(hw, RB_ADDR(q, RB_RX_LTPP),
			     start + (len/3));
	पूर्ण अन्यथा अणु
		/* Enable store & क्रमward on Tx queue's because
		 * Tx FIFO is only 4K on Genesis and 1K on Yukon
		 */
		skge_ग_लिखो8(hw, RB_ADDR(q, RB_CTRL), RB_ENA_STFWD);
	पूर्ण

	skge_ग_लिखो8(hw, RB_ADDR(q, RB_CTRL), RB_ENA_OP_MD);
पूर्ण

/* Setup Bus Memory Interface */
अटल व्योम skge_qset(काष्ठा skge_port *skge, u16 q,
		      स्थिर काष्ठा skge_element *e)
अणु
	काष्ठा skge_hw *hw = skge->hw;
	u32 watermark = 0x600;
	u64 base = skge->dma + (e->desc - skge->mem);

	/* optimization to reduce winकरोw on 32bit/33mhz */
	अगर ((skge_पढ़ो16(hw, B0_CTST) & (CS_BUS_CLOCK | CS_BUS_SLOT_SZ)) == 0)
		watermark /= 2;

	skge_ग_लिखो32(hw, Q_ADDR(q, Q_CSR), CSR_CLR_RESET);
	skge_ग_लिखो32(hw, Q_ADDR(q, Q_F), watermark);
	skge_ग_लिखो32(hw, Q_ADDR(q, Q_DA_H), (u32)(base >> 32));
	skge_ग_लिखो32(hw, Q_ADDR(q, Q_DA_L), (u32)base);
पूर्ण

अटल पूर्णांक skge_up(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	u32 chunk, ram_addr;
	माप_प्रकार rx_size, tx_size;
	पूर्णांक err;

	अगर (!is_valid_ether_addr(dev->dev_addr))
		वापस -EINVAL;

	netअगर_info(skge, अगरup, skge->netdev, "enabling interface\n");

	अगर (dev->mtu > RX_BUF_SIZE)
		skge->rx_buf_size = dev->mtu + ETH_HLEN;
	अन्यथा
		skge->rx_buf_size = RX_BUF_SIZE;


	rx_size = skge->rx_ring.count * माप(काष्ठा skge_rx_desc);
	tx_size = skge->tx_ring.count * माप(काष्ठा skge_tx_desc);
	skge->mem_size = tx_size + rx_size;
	skge->mem = dma_alloc_coherent(&hw->pdev->dev, skge->mem_size,
				       &skge->dma, GFP_KERNEL);
	अगर (!skge->mem)
		वापस -ENOMEM;

	BUG_ON(skge->dma & 7);

	अगर (upper_32_bits(skge->dma) != upper_32_bits(skge->dma + skge->mem_size)) अणु
		dev_err(&hw->pdev->dev, "dma_alloc_coherent region crosses 4G boundary\n");
		err = -EINVAL;
		जाओ मुक्त_pci_mem;
	पूर्ण

	err = skge_ring_alloc(&skge->rx_ring, skge->mem, skge->dma);
	अगर (err)
		जाओ मुक्त_pci_mem;

	err = skge_rx_fill(dev);
	अगर (err)
		जाओ मुक्त_rx_ring;

	err = skge_ring_alloc(&skge->tx_ring, skge->mem + rx_size,
			      skge->dma + rx_size);
	अगर (err)
		जाओ मुक्त_rx_ring;

	अगर (hw->ports == 1) अणु
		err = request_irq(hw->pdev->irq, skge_पूर्णांकr, IRQF_SHARED,
				  dev->name, hw);
		अगर (err) अणु
			netdev_err(dev, "Unable to allocate interrupt %d error: %d\n",
				   hw->pdev->irq, err);
			जाओ मुक्त_tx_ring;
		पूर्ण
	पूर्ण

	/* Initialize MAC */
	netअगर_carrier_off(dev);
	spin_lock_bh(&hw->phy_lock);
	अगर (is_genesis(hw))
		genesis_mac_init(hw, port);
	अन्यथा
		yukon_mac_init(hw, port);
	spin_unlock_bh(&hw->phy_lock);

	/* Configure RAMbuffers - equally between ports and tx/rx */
	chunk = (hw->ram_size  - hw->ram_offset) / (hw->ports * 2);
	ram_addr = hw->ram_offset + 2 * chunk * port;

	skge_ramset(hw, rxqaddr[port], ram_addr, chunk);
	skge_qset(skge, rxqaddr[port], skge->rx_ring.to_clean);

	BUG_ON(skge->tx_ring.to_use != skge->tx_ring.to_clean);
	skge_ramset(hw, txqaddr[port], ram_addr+chunk, chunk);
	skge_qset(skge, txqaddr[port], skge->tx_ring.to_use);

	/* Start receiver BMU */
	wmb();
	skge_ग_लिखो8(hw, Q_ADDR(rxqaddr[port], Q_CSR), CSR_START | CSR_IRQ_CL_F);
	skge_led(skge, LED_MODE_ON);

	spin_lock_irq(&hw->hw_lock);
	hw->पूर्णांकr_mask |= porपंचांगask[port];
	skge_ग_लिखो32(hw, B0_IMSK, hw->पूर्णांकr_mask);
	skge_पढ़ो32(hw, B0_IMSK);
	spin_unlock_irq(&hw->hw_lock);

	napi_enable(&skge->napi);

	skge_set_multicast(dev);

	वापस 0;

 मुक्त_tx_ring:
	kमुक्त(skge->tx_ring.start);
 मुक्त_rx_ring:
	skge_rx_clean(skge);
	kमुक्त(skge->rx_ring.start);
 मुक्त_pci_mem:
	dma_मुक्त_coherent(&hw->pdev->dev, skge->mem_size, skge->mem,
			  skge->dma);
	skge->mem = शून्य;

	वापस err;
पूर्ण

/* stop receiver */
अटल व्योम skge_rx_stop(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	skge_ग_लिखो8(hw, Q_ADDR(rxqaddr[port], Q_CSR), CSR_STOP);
	skge_ग_लिखो32(hw, RB_ADDR(port ? Q_R2 : Q_R1, RB_CTRL),
		     RB_RST_SET|RB_DIS_OP_MD);
	skge_ग_लिखो32(hw, Q_ADDR(rxqaddr[port], Q_CSR), CSR_SET_RESET);
पूर्ण

अटल पूर्णांक skge_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;

	अगर (!skge->mem)
		वापस 0;

	netअगर_info(skge, अगरकरोwn, skge->netdev, "disabling interface\n");

	netअगर_tx_disable(dev);

	अगर (is_genesis(hw) && hw->phy_type == SK_PHY_XMAC)
		del_समयr_sync(&skge->link_समयr);

	napi_disable(&skge->napi);
	netअगर_carrier_off(dev);

	spin_lock_irq(&hw->hw_lock);
	hw->पूर्णांकr_mask &= ~porपंचांगask[port];
	skge_ग_लिखो32(hw, B0_IMSK, (hw->ports == 1) ? 0 : hw->पूर्णांकr_mask);
	skge_पढ़ो32(hw, B0_IMSK);
	spin_unlock_irq(&hw->hw_lock);

	अगर (hw->ports == 1)
		मुक्त_irq(hw->pdev->irq, hw);

	skge_ग_लिखो8(skge->hw, SK_REG(skge->port, LNK_LED_REG), LED_REG_OFF);
	अगर (is_genesis(hw))
		genesis_stop(skge);
	अन्यथा
		yukon_stop(skge);

	/* Stop transmitter */
	skge_ग_लिखो8(hw, Q_ADDR(txqaddr[port], Q_CSR), CSR_STOP);
	skge_ग_लिखो32(hw, RB_ADDR(txqaddr[port], RB_CTRL),
		     RB_RST_SET|RB_DIS_OP_MD);


	/* Disable Force Sync bit and Enable Alloc bit */
	skge_ग_लिखो8(hw, SK_REG(port, TXA_CTRL),
		    TXA_DIS_FSYNC | TXA_DIS_ALLOC | TXA_STOP_RC);

	/* Stop Interval Timer and Limit Counter of Tx Arbiter */
	skge_ग_लिखो32(hw, SK_REG(port, TXA_ITI_INI), 0L);
	skge_ग_लिखो32(hw, SK_REG(port, TXA_LIM_INI), 0L);

	/* Reset PCI FIFO */
	skge_ग_लिखो32(hw, Q_ADDR(txqaddr[port], Q_CSR), CSR_SET_RESET);
	skge_ग_लिखो32(hw, RB_ADDR(txqaddr[port], RB_CTRL), RB_RST_SET);

	/* Reset the RAM Buffer async Tx queue */
	skge_ग_लिखो8(hw, RB_ADDR(port == 0 ? Q_XA1 : Q_XA2, RB_CTRL), RB_RST_SET);

	skge_rx_stop(hw, port);

	अगर (is_genesis(hw)) अणु
		skge_ग_लिखो8(hw, SK_REG(port, TX_MFF_CTRL2), MFF_RST_SET);
		skge_ग_लिखो8(hw, SK_REG(port, RX_MFF_CTRL2), MFF_RST_SET);
	पूर्ण अन्यथा अणु
		skge_ग_लिखो8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_SET);
		skge_ग_लिखो8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_RST_SET);
	पूर्ण

	skge_led(skge, LED_MODE_OFF);

	netअगर_tx_lock_bh(dev);
	skge_tx_clean(dev);
	netअगर_tx_unlock_bh(dev);

	skge_rx_clean(skge);

	kमुक्त(skge->rx_ring.start);
	kमुक्त(skge->tx_ring.start);
	dma_मुक्त_coherent(&hw->pdev->dev, skge->mem_size, skge->mem,
			  skge->dma);
	skge->mem = शून्य;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक skge_avail(स्थिर काष्ठा skge_ring *ring)
अणु
	smp_mb();
	वापस ((ring->to_clean > ring->to_use) ? 0 : ring->count)
		+ (ring->to_clean - ring->to_use) - 1;
पूर्ण

अटल netdev_tx_t skge_xmit_frame(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	काष्ठा skge_element *e;
	काष्ठा skge_tx_desc *td;
	पूर्णांक i;
	u32 control, len;
	dma_addr_t map;

	अगर (skb_padto(skb, ETH_ZLEN))
		वापस NETDEV_TX_OK;

	अगर (unlikely(skge_avail(&skge->tx_ring) < skb_shinfo(skb)->nr_frags + 1))
		वापस NETDEV_TX_BUSY;

	e = skge->tx_ring.to_use;
	td = e->desc;
	BUG_ON(td->control & BMU_OWN);
	e->skb = skb;
	len = skb_headlen(skb);
	map = dma_map_single(&hw->pdev->dev, skb->data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&hw->pdev->dev, map))
		जाओ mapping_error;

	dma_unmap_addr_set(e, mapaddr, map);
	dma_unmap_len_set(e, maplen, len);

	td->dma_lo = lower_32_bits(map);
	td->dma_hi = upper_32_bits(map);

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		स्थिर पूर्णांक offset = skb_checksum_start_offset(skb);

		/* This seems backwards, but it is what the sk98lin
		 * करोes.  Looks like hardware is wrong?
		 */
		अगर (ipip_hdr(skb)->protocol == IPPROTO_UDP &&
		    hw->chip_rev == 0 && hw->chip_id == CHIP_ID_YUKON)
			control = BMU_TCP_CHECK;
		अन्यथा
			control = BMU_UDP_CHECK;

		td->csum_offs = 0;
		td->csum_start = offset;
		td->csum_ग_लिखो = offset + skb->csum_offset;
	पूर्ण अन्यथा
		control = BMU_CHECK;

	अगर (!skb_shinfo(skb)->nr_frags) /* single buffer i.e. no fragments */
		control |= BMU_खातापूर्ण | BMU_IRQ_खातापूर्ण;
	अन्यथा अणु
		काष्ठा skge_tx_desc *tf = td;

		control |= BMU_STFWD;
		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

			map = skb_frag_dma_map(&hw->pdev->dev, frag, 0,
					       skb_frag_size(frag), DMA_TO_DEVICE);
			अगर (dma_mapping_error(&hw->pdev->dev, map))
				जाओ mapping_unwind;

			e = e->next;
			e->skb = skb;
			tf = e->desc;
			BUG_ON(tf->control & BMU_OWN);

			tf->dma_lo = lower_32_bits(map);
			tf->dma_hi = upper_32_bits(map);
			dma_unmap_addr_set(e, mapaddr, map);
			dma_unmap_len_set(e, maplen, skb_frag_size(frag));

			tf->control = BMU_OWN | BMU_SW | control | skb_frag_size(frag);
		पूर्ण
		tf->control |= BMU_खातापूर्ण | BMU_IRQ_खातापूर्ण;
	पूर्ण
	/* Make sure all the descriptors written */
	wmb();
	td->control = BMU_OWN | BMU_SW | BMU_STF | control | len;
	wmb();

	netdev_sent_queue(dev, skb->len);

	skge_ग_लिखो8(hw, Q_ADDR(txqaddr[skge->port], Q_CSR), CSR_START);

	netअगर_prपूर्णांकk(skge, tx_queued, KERN_DEBUG, skge->netdev,
		     "tx queued, slot %td, len %d\n",
		     e - skge->tx_ring.start, skb->len);

	skge->tx_ring.to_use = e->next;
	smp_wmb();

	अगर (skge_avail(&skge->tx_ring) <= TX_LOW_WATER) अणु
		netdev_dbg(dev, "transmit queue full\n");
		netअगर_stop_queue(dev);
	पूर्ण

	वापस NETDEV_TX_OK;

mapping_unwind:
	e = skge->tx_ring.to_use;
	dma_unmap_single(&hw->pdev->dev, dma_unmap_addr(e, mapaddr),
			 dma_unmap_len(e, maplen), DMA_TO_DEVICE);
	जबतक (i-- > 0) अणु
		e = e->next;
		dma_unmap_page(&hw->pdev->dev, dma_unmap_addr(e, mapaddr),
			       dma_unmap_len(e, maplen), DMA_TO_DEVICE);
	पूर्ण

mapping_error:
	अगर (net_ratelimit())
		dev_warn(&hw->pdev->dev, "%s: tx mapping error\n", dev->name);
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण


/* Free resources associated with this reing element */
अटल अंतरभूत व्योम skge_tx_unmap(काष्ठा pci_dev *pdev, काष्ठा skge_element *e,
				 u32 control)
अणु
	/* skb header vs. fragment */
	अगर (control & BMU_STF)
		dma_unmap_single(&pdev->dev, dma_unmap_addr(e, mapaddr),
				 dma_unmap_len(e, maplen), DMA_TO_DEVICE);
	अन्यथा
		dma_unmap_page(&pdev->dev, dma_unmap_addr(e, mapaddr),
			       dma_unmap_len(e, maplen), DMA_TO_DEVICE);
पूर्ण

/* Free all buffers in transmit ring */
अटल व्योम skge_tx_clean(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_element *e;

	क्रम (e = skge->tx_ring.to_clean; e != skge->tx_ring.to_use; e = e->next) अणु
		काष्ठा skge_tx_desc *td = e->desc;

		skge_tx_unmap(skge->hw->pdev, e, td->control);

		अगर (td->control & BMU_खातापूर्ण)
			dev_kमुक्त_skb(e->skb);
		td->control = 0;
	पूर्ण

	netdev_reset_queue(dev);
	skge->tx_ring.to_clean = e;
पूर्ण

अटल व्योम skge_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	netअगर_prपूर्णांकk(skge, समयr, KERN_DEBUG, skge->netdev, "tx timeout\n");

	skge_ग_लिखो8(skge->hw, Q_ADDR(txqaddr[skge->port], Q_CSR), CSR_STOP);
	skge_tx_clean(dev);
	netअगर_wake_queue(dev);
पूर्ण

अटल पूर्णांक skge_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	पूर्णांक err;

	अगर (!netअगर_running(dev)) अणु
		dev->mtu = new_mtu;
		वापस 0;
	पूर्ण

	skge_करोwn(dev);

	dev->mtu = new_mtu;

	err = skge_up(dev);
	अगर (err)
		dev_बंद(dev);

	वापस err;
पूर्ण

अटल स्थिर u8 छोड़ो_mc_addr[ETH_ALEN] = अणु 0x1, 0x80, 0xc2, 0x0, 0x0, 0x1 पूर्ण;

अटल व्योम genesis_add_filter(u8 filter[8], स्थिर u8 *addr)
अणु
	u32 crc, bit;

	crc = ether_crc_le(ETH_ALEN, addr);
	bit = ~crc & 0x3f;
	filter[bit/8] |= 1 << (bit%8);
पूर्ण

अटल व्योम genesis_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	काष्ठा netdev_hw_addr *ha;
	u32 mode;
	u8 filter[8];

	mode = xm_पढ़ो32(hw, port, XM_MODE);
	mode |= XM_MD_ENA_HASH;
	अगर (dev->flags & IFF_PROMISC)
		mode |= XM_MD_ENA_PROM;
	अन्यथा
		mode &= ~XM_MD_ENA_PROM;

	अगर (dev->flags & IFF_ALLMULTI)
		स_रखो(filter, 0xff, माप(filter));
	अन्यथा अणु
		स_रखो(filter, 0, माप(filter));

		अगर (skge->flow_status == FLOW_STAT_REM_SEND ||
		    skge->flow_status == FLOW_STAT_SYMMETRIC)
			genesis_add_filter(filter, छोड़ो_mc_addr);

		netdev_क्रम_each_mc_addr(ha, dev)
			genesis_add_filter(filter, ha->addr);
	पूर्ण

	xm_ग_लिखो32(hw, port, XM_MODE, mode);
	xm_outhash(hw, port, XM_HSM, filter);
पूर्ण

अटल व्योम yukon_add_filter(u8 filter[8], स्थिर u8 *addr)
अणु
	u32 bit = ether_crc(ETH_ALEN, addr) & 0x3f;

	filter[bit / 8] |= 1 << (bit % 8);
पूर्ण

अटल व्योम yukon_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	पूर्णांक port = skge->port;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक rx_छोड़ो = (skge->flow_status == FLOW_STAT_REM_SEND ||
			skge->flow_status == FLOW_STAT_SYMMETRIC);
	u16 reg;
	u8 filter[8];

	स_रखो(filter, 0, माप(filter));

	reg = gma_पढ़ो16(hw, port, GM_RX_CTRL);
	reg |= GM_RXCR_UCF_ENA;

	अगर (dev->flags & IFF_PROMISC) 		/* promiscuous */
		reg &= ~(GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA);
	अन्यथा अगर (dev->flags & IFF_ALLMULTI)	/* all multicast */
		स_रखो(filter, 0xff, माप(filter));
	अन्यथा अगर (netdev_mc_empty(dev) && !rx_छोड़ो)/* no multicast */
		reg &= ~GM_RXCR_MCF_ENA;
	अन्यथा अणु
		reg |= GM_RXCR_MCF_ENA;

		अगर (rx_छोड़ो)
			yukon_add_filter(filter, छोड़ो_mc_addr);

		netdev_क्रम_each_mc_addr(ha, dev)
			yukon_add_filter(filter, ha->addr);
	पूर्ण


	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H1,
			 (u16)filter[0] | ((u16)filter[1] << 8));
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H2,
			 (u16)filter[2] | ((u16)filter[3] << 8));
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H3,
			 (u16)filter[4] | ((u16)filter[5] << 8));
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H4,
			 (u16)filter[6] | ((u16)filter[7] << 8));

	gma_ग_लिखो16(hw, port, GM_RX_CTRL, reg);
पूर्ण

अटल अंतरभूत u16 phy_length(स्थिर काष्ठा skge_hw *hw, u32 status)
अणु
	अगर (is_genesis(hw))
		वापस status >> XMR_FS_LEN_SHIFT;
	अन्यथा
		वापस status >> GMR_FS_LEN_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक bad_phy_status(स्थिर काष्ठा skge_hw *hw, u32 status)
अणु
	अगर (is_genesis(hw))
		वापस (status & (XMR_FS_ERR | XMR_FS_2L_VLAN)) != 0;
	अन्यथा
		वापस (status & GMR_FS_ANY_ERR) ||
			(status & GMR_FS_RX_OK) == 0;
पूर्ण

अटल व्योम skge_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	अगर (is_genesis(skge->hw))
		genesis_set_multicast(dev);
	अन्यथा
		yukon_set_multicast(dev);

पूर्ण


/* Get receive buffer from descriptor.
 * Handles copy of small buffers and पुनः_स्मृतिation failures
 */
अटल काष्ठा sk_buff *skge_rx_get(काष्ठा net_device *dev,
				   काष्ठा skge_element *e,
				   u32 control, u32 status, u16 csum)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	u16 len = control & BMU_BBC;

	netअगर_prपूर्णांकk(skge, rx_status, KERN_DEBUG, skge->netdev,
		     "rx slot %td status 0x%x len %d\n",
		     e - skge->rx_ring.start, status, len);

	अगर (len > skge->rx_buf_size)
		जाओ error;

	अगर ((control & (BMU_खातापूर्ण|BMU_STF)) != (BMU_STF|BMU_खातापूर्ण))
		जाओ error;

	अगर (bad_phy_status(skge->hw, status))
		जाओ error;

	अगर (phy_length(skge->hw, status) != len)
		जाओ error;

	अगर (len < RX_COPY_THRESHOLD) अणु
		skb = netdev_alloc_skb_ip_align(dev, len);
		अगर (!skb)
			जाओ resubmit;

		dma_sync_single_क्रम_cpu(&skge->hw->pdev->dev,
					dma_unmap_addr(e, mapaddr),
					dma_unmap_len(e, maplen),
					DMA_FROM_DEVICE);
		skb_copy_from_linear_data(e->skb, skb->data, len);
		dma_sync_single_क्रम_device(&skge->hw->pdev->dev,
					   dma_unmap_addr(e, mapaddr),
					   dma_unmap_len(e, maplen),
					   DMA_FROM_DEVICE);
		skge_rx_reuse(e, skge->rx_buf_size);
	पूर्ण अन्यथा अणु
		काष्ठा skge_element ee;
		काष्ठा sk_buff *nskb;

		nskb = netdev_alloc_skb_ip_align(dev, skge->rx_buf_size);
		अगर (!nskb)
			जाओ resubmit;

		ee = *e;

		skb = ee.skb;
		prefetch(skb->data);

		अगर (skge_rx_setup(skge, e, nskb, skge->rx_buf_size) < 0) अणु
			dev_kमुक्त_skb(nskb);
			जाओ resubmit;
		पूर्ण

		dma_unmap_single(&skge->hw->pdev->dev,
				 dma_unmap_addr(&ee, mapaddr),
				 dma_unmap_len(&ee, maplen), DMA_FROM_DEVICE);
	पूर्ण

	skb_put(skb, len);

	अगर (dev->features & NETIF_F_RXCSUM) अणु
		skb->csum = le16_to_cpu(csum);
		skb->ip_summed = CHECKSUM_COMPLETE;
	पूर्ण

	skb->protocol = eth_type_trans(skb, dev);

	वापस skb;
error:

	netअगर_prपूर्णांकk(skge, rx_err, KERN_DEBUG, skge->netdev,
		     "rx err, slot %td control 0x%x status 0x%x\n",
		     e - skge->rx_ring.start, control, status);

	अगर (is_genesis(skge->hw)) अणु
		अगर (status & (XMR_FS_RUNT|XMR_FS_LNG_ERR))
			dev->stats.rx_length_errors++;
		अगर (status & XMR_FS_FRA_ERR)
			dev->stats.rx_frame_errors++;
		अगर (status & XMR_FS_FCS_ERR)
			dev->stats.rx_crc_errors++;
	पूर्ण अन्यथा अणु
		अगर (status & (GMR_FS_LONG_ERR|GMR_FS_UN_SIZE))
			dev->stats.rx_length_errors++;
		अगर (status & GMR_FS_FRAGMENT)
			dev->stats.rx_frame_errors++;
		अगर (status & GMR_FS_CRC_ERR)
			dev->stats.rx_crc_errors++;
	पूर्ण

resubmit:
	skge_rx_reuse(e, skge->rx_buf_size);
	वापस शून्य;
पूर्ण

/* Free all buffers in Tx ring which are no दीर्घer owned by device */
अटल व्योम skge_tx_करोne(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_ring *ring = &skge->tx_ring;
	काष्ठा skge_element *e;
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;

	skge_ग_लिखो8(skge->hw, Q_ADDR(txqaddr[skge->port], Q_CSR), CSR_IRQ_CL_F);

	क्रम (e = ring->to_clean; e != ring->to_use; e = e->next) अणु
		u32 control = ((स्थिर काष्ठा skge_tx_desc *) e->desc)->control;

		अगर (control & BMU_OWN)
			अवरोध;

		skge_tx_unmap(skge->hw->pdev, e, control);

		अगर (control & BMU_खातापूर्ण) अणु
			netअगर_prपूर्णांकk(skge, tx_करोne, KERN_DEBUG, skge->netdev,
				     "tx done slot %td\n",
				     e - skge->tx_ring.start);

			pkts_compl++;
			bytes_compl += e->skb->len;

			dev_consume_skb_any(e->skb);
		पूर्ण
	पूर्ण
	netdev_completed_queue(dev, pkts_compl, bytes_compl);
	skge->tx_ring.to_clean = e;

	/* Can run lockless until we need to synchronize to restart queue. */
	smp_mb();

	अगर (unlikely(netअगर_queue_stopped(dev) &&
		     skge_avail(&skge->tx_ring) > TX_LOW_WATER)) अणु
		netअगर_tx_lock(dev);
		अगर (unlikely(netअगर_queue_stopped(dev) &&
			     skge_avail(&skge->tx_ring) > TX_LOW_WATER)) अणु
			netअगर_wake_queue(dev);

		पूर्ण
		netअगर_tx_unlock(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक skge_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा skge_port *skge = container_of(napi, काष्ठा skge_port, napi);
	काष्ठा net_device *dev = skge->netdev;
	काष्ठा skge_hw *hw = skge->hw;
	काष्ठा skge_ring *ring = &skge->rx_ring;
	काष्ठा skge_element *e;
	पूर्णांक work_करोne = 0;

	skge_tx_करोne(dev);

	skge_ग_लिखो8(hw, Q_ADDR(rxqaddr[skge->port], Q_CSR), CSR_IRQ_CL_F);

	क्रम (e = ring->to_clean; prefetch(e->next), work_करोne < budget; e = e->next) अणु
		काष्ठा skge_rx_desc *rd = e->desc;
		काष्ठा sk_buff *skb;
		u32 control;

		rmb();
		control = rd->control;
		अगर (control & BMU_OWN)
			अवरोध;

		skb = skge_rx_get(dev, e, control, rd->status, rd->csum2);
		अगर (likely(skb)) अणु
			napi_gro_receive(napi, skb);
			++work_करोne;
		पूर्ण
	पूर्ण
	ring->to_clean = e;

	/* restart receiver */
	wmb();
	skge_ग_लिखो8(hw, Q_ADDR(rxqaddr[skge->port], Q_CSR), CSR_START);

	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&hw->hw_lock, flags);
		hw->पूर्णांकr_mask |= napimask[skge->port];
		skge_ग_लिखो32(hw, B0_IMSK, hw->पूर्णांकr_mask);
		skge_पढ़ो32(hw, B0_IMSK);
		spin_unlock_irqrestore(&hw->hw_lock, flags);
	पूर्ण

	वापस work_करोne;
पूर्ण

/* Parity errors seem to happen when Genesis is connected to a चयन
 * with no other ports present. Heartbeat error??
 */
अटल व्योम skge_mac_parity(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	काष्ठा net_device *dev = hw->dev[port];

	++dev->stats.tx_heartbeat_errors;

	अगर (is_genesis(hw))
		skge_ग_लिखो16(hw, SK_REG(port, TX_MFF_CTRL1),
			     MFF_CLR_PERR);
	अन्यथा
		/* HW-Bug #8: cleared by GMF_CLI_TX_FC instead of GMF_CLI_TX_PE */
		skge_ग_लिखो8(hw, SK_REG(port, TX_GMF_CTRL_T),
			    (hw->chip_id == CHIP_ID_YUKON && hw->chip_rev == 0)
			    ? GMF_CLI_TX_FC : GMF_CLI_TX_PE);
पूर्ण

अटल व्योम skge_mac_पूर्णांकr(काष्ठा skge_hw *hw, पूर्णांक port)
अणु
	अगर (is_genesis(hw))
		genesis_mac_पूर्णांकr(hw, port);
	अन्यथा
		yukon_mac_पूर्णांकr(hw, port);
पूर्ण

/* Handle device specअगरic framing and समयout पूर्णांकerrupts */
अटल व्योम skge_error_irq(काष्ठा skge_hw *hw)
अणु
	काष्ठा pci_dev *pdev = hw->pdev;
	u32 hwstatus = skge_पढ़ो32(hw, B0_HWE_ISRC);

	अगर (is_genesis(hw)) अणु
		/* clear xmac errors */
		अगर (hwstatus & (IS_NO_STAT_M1|IS_NO_TIST_M1))
			skge_ग_लिखो16(hw, RX_MFF_CTRL1, MFF_CLR_INSTAT);
		अगर (hwstatus & (IS_NO_STAT_M2|IS_NO_TIST_M2))
			skge_ग_लिखो16(hw, RX_MFF_CTRL2, MFF_CLR_INSTAT);
	पूर्ण अन्यथा अणु
		/* Timestamp (unused) overflow */
		अगर (hwstatus & IS_IRQ_TIST_OV)
			skge_ग_लिखो8(hw, GMAC_TI_ST_CTRL, GMT_ST_CLR_IRQ);
	पूर्ण

	अगर (hwstatus & IS_RAM_RD_PAR) अणु
		dev_err(&pdev->dev, "Ram read data parity error\n");
		skge_ग_लिखो16(hw, B3_RI_CTRL, RI_CLR_RD_PERR);
	पूर्ण

	अगर (hwstatus & IS_RAM_WR_PAR) अणु
		dev_err(&pdev->dev, "Ram write data parity error\n");
		skge_ग_लिखो16(hw, B3_RI_CTRL, RI_CLR_WR_PERR);
	पूर्ण

	अगर (hwstatus & IS_M1_PAR_ERR)
		skge_mac_parity(hw, 0);

	अगर (hwstatus & IS_M2_PAR_ERR)
		skge_mac_parity(hw, 1);

	अगर (hwstatus & IS_R1_PAR_ERR) अणु
		dev_err(&pdev->dev, "%s: receive queue parity error\n",
			hw->dev[0]->name);
		skge_ग_लिखो32(hw, B0_R1_CSR, CSR_IRQ_CL_P);
	पूर्ण

	अगर (hwstatus & IS_R2_PAR_ERR) अणु
		dev_err(&pdev->dev, "%s: receive queue parity error\n",
			hw->dev[1]->name);
		skge_ग_लिखो32(hw, B0_R2_CSR, CSR_IRQ_CL_P);
	पूर्ण

	अगर (hwstatus & (IS_IRQ_MST_ERR|IS_IRQ_STAT)) अणु
		u16 pci_status, pci_cmd;

		pci_पढ़ो_config_word(pdev, PCI_COMMAND, &pci_cmd);
		pci_पढ़ो_config_word(pdev, PCI_STATUS, &pci_status);

		dev_err(&pdev->dev, "PCI error cmd=%#x status=%#x\n",
			pci_cmd, pci_status);

		/* Write the error bits back to clear them. */
		pci_status &= PCI_STATUS_ERROR_BITS;
		skge_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		pci_ग_लिखो_config_word(pdev, PCI_COMMAND,
				      pci_cmd | PCI_COMMAND_SERR | PCI_COMMAND_PARITY);
		pci_ग_लिखो_config_word(pdev, PCI_STATUS, pci_status);
		skge_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

		/* अगर error still set then just ignore it */
		hwstatus = skge_पढ़ो32(hw, B0_HWE_ISRC);
		अगर (hwstatus & IS_IRQ_STAT) अणु
			dev_warn(&hw->pdev->dev, "unable to clear error (so ignoring them)\n");
			hw->पूर्णांकr_mask &= ~IS_HW_ERR;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Interrupt from PHY are handled in tasklet (softirq)
 * because accessing phy रेजिस्टरs requires spin रुको which might
 * cause excess पूर्णांकerrupt latency.
 */
अटल व्योम skge_extirq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा skge_hw *hw = from_tasklet(hw, t, phy_task);
	पूर्णांक port;

	क्रम (port = 0; port < hw->ports; port++) अणु
		काष्ठा net_device *dev = hw->dev[port];

		अगर (netअगर_running(dev)) अणु
			काष्ठा skge_port *skge = netdev_priv(dev);

			spin_lock(&hw->phy_lock);
			अगर (!is_genesis(hw))
				yukon_phy_पूर्णांकr(skge);
			अन्यथा अगर (hw->phy_type == SK_PHY_BCOM)
				bcom_phy_पूर्णांकr(skge);
			spin_unlock(&hw->phy_lock);
		पूर्ण
	पूर्ण

	spin_lock_irq(&hw->hw_lock);
	hw->पूर्णांकr_mask |= IS_EXT_REG;
	skge_ग_लिखो32(hw, B0_IMSK, hw->पूर्णांकr_mask);
	skge_पढ़ो32(hw, B0_IMSK);
	spin_unlock_irq(&hw->hw_lock);
पूर्ण

अटल irqवापस_t skge_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा skge_hw *hw = dev_id;
	u32 status;
	पूर्णांक handled = 0;

	spin_lock(&hw->hw_lock);
	/* Reading this रेजिस्टर masks IRQ */
	status = skge_पढ़ो32(hw, B0_SP_ISRC);
	अगर (status == 0 || status == ~0)
		जाओ out;

	handled = 1;
	status &= hw->पूर्णांकr_mask;
	अगर (status & IS_EXT_REG) अणु
		hw->पूर्णांकr_mask &= ~IS_EXT_REG;
		tasklet_schedule(&hw->phy_task);
	पूर्ण

	अगर (status & (IS_XA1_F|IS_R1_F)) अणु
		काष्ठा skge_port *skge = netdev_priv(hw->dev[0]);
		hw->पूर्णांकr_mask &= ~(IS_XA1_F|IS_R1_F);
		napi_schedule(&skge->napi);
	पूर्ण

	अगर (status & IS_PA_TO_TX1)
		skge_ग_लिखो16(hw, B3_PA_CTRL, PA_CLR_TO_TX1);

	अगर (status & IS_PA_TO_RX1) अणु
		++hw->dev[0]->stats.rx_over_errors;
		skge_ग_लिखो16(hw, B3_PA_CTRL, PA_CLR_TO_RX1);
	पूर्ण


	अगर (status & IS_MAC1)
		skge_mac_पूर्णांकr(hw, 0);

	अगर (hw->dev[1]) अणु
		काष्ठा skge_port *skge = netdev_priv(hw->dev[1]);

		अगर (status & (IS_XA2_F|IS_R2_F)) अणु
			hw->पूर्णांकr_mask &= ~(IS_XA2_F|IS_R2_F);
			napi_schedule(&skge->napi);
		पूर्ण

		अगर (status & IS_PA_TO_RX2) अणु
			++hw->dev[1]->stats.rx_over_errors;
			skge_ग_लिखो16(hw, B3_PA_CTRL, PA_CLR_TO_RX2);
		पूर्ण

		अगर (status & IS_PA_TO_TX2)
			skge_ग_लिखो16(hw, B3_PA_CTRL, PA_CLR_TO_TX2);

		अगर (status & IS_MAC2)
			skge_mac_पूर्णांकr(hw, 1);
	पूर्ण

	अगर (status & IS_HW_ERR)
		skge_error_irq(hw);
out:
	skge_ग_लिखो32(hw, B0_IMSK, hw->पूर्णांकr_mask);
	skge_पढ़ो32(hw, B0_IMSK);
	spin_unlock(&hw->hw_lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम skge_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);

	disable_irq(dev->irq);
	skge_पूर्णांकr(dev->irq, skge->hw);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक skge_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा skge_port *skge = netdev_priv(dev);
	काष्ठा skge_hw *hw = skge->hw;
	अचिन्हित port = skge->port;
	स्थिर काष्ठा sockaddr *addr = p;
	u16 ctrl;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, ETH_ALEN);

	अगर (!netअगर_running(dev)) अणु
		स_नकल_toio(hw->regs + B2_MAC_1 + port*8, dev->dev_addr, ETH_ALEN);
		स_नकल_toio(hw->regs + B2_MAC_2 + port*8, dev->dev_addr, ETH_ALEN);
	पूर्ण अन्यथा अणु
		/* disable Rx */
		spin_lock_bh(&hw->phy_lock);
		ctrl = gma_पढ़ो16(hw, port, GM_GP_CTRL);
		gma_ग_लिखो16(hw, port, GM_GP_CTRL, ctrl & ~GM_GPCR_RX_ENA);

		स_नकल_toio(hw->regs + B2_MAC_1 + port*8, dev->dev_addr, ETH_ALEN);
		स_नकल_toio(hw->regs + B2_MAC_2 + port*8, dev->dev_addr, ETH_ALEN);

		अगर (is_genesis(hw))
			xm_outaddr(hw, port, XM_SA, dev->dev_addr);
		अन्यथा अणु
			gma_set_addr(hw, port, GM_SRC_ADDR_1L, dev->dev_addr);
			gma_set_addr(hw, port, GM_SRC_ADDR_2L, dev->dev_addr);
		पूर्ण

		gma_ग_लिखो16(hw, port, GM_GP_CTRL, ctrl);
		spin_unlock_bh(&hw->phy_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा अणु
	u8 id;
	स्थिर अक्षर *name;
पूर्ण skge_chips[] = अणु
	अणु CHIP_ID_GENESIS,	"Genesis" पूर्ण,
	अणु CHIP_ID_YUKON,	 "Yukon" पूर्ण,
	अणु CHIP_ID_YUKON_LITE,	 "Yukon-Lite"पूर्ण,
	अणु CHIP_ID_YUKON_LP,	 "Yukon-LP"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *skge_board_name(स्थिर काष्ठा skge_hw *hw)
अणु
	पूर्णांक i;
	अटल अक्षर buf[16];

	क्रम (i = 0; i < ARRAY_SIZE(skge_chips); i++)
		अगर (skge_chips[i].id == hw->chip_id)
			वापस skge_chips[i].name;

	snम_लिखो(buf, माप(buf), "chipid 0x%x", hw->chip_id);
	वापस buf;
पूर्ण


/*
 * Setup the board data काष्ठाure, but करोn't bring up
 * the port(s)
 */
अटल पूर्णांक skge_reset(काष्ठा skge_hw *hw)
अणु
	u32 reg;
	u16 ctst, pci_status;
	u8 t8, mac_cfg, pmd_type;
	पूर्णांक i;

	ctst = skge_पढ़ो16(hw, B0_CTST);

	/* करो a SW reset */
	skge_ग_लिखो8(hw, B0_CTST, CS_RST_SET);
	skge_ग_लिखो8(hw, B0_CTST, CS_RST_CLR);

	/* clear PCI errors, अगर any */
	skge_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
	skge_ग_लिखो8(hw, B2_TST_CTRL2, 0);

	pci_पढ़ो_config_word(hw->pdev, PCI_STATUS, &pci_status);
	pci_ग_लिखो_config_word(hw->pdev, PCI_STATUS,
			      pci_status | PCI_STATUS_ERROR_BITS);
	skge_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	skge_ग_लिखो8(hw, B0_CTST, CS_MRST_CLR);

	/* restore CLK_RUN bits (क्रम Yukon-Lite) */
	skge_ग_लिखो16(hw, B0_CTST,
		     ctst & (CS_CLK_RUN_HOT|CS_CLK_RUN_RST|CS_CLK_RUN_ENA));

	hw->chip_id = skge_पढ़ो8(hw, B2_CHIP_ID);
	hw->phy_type = skge_पढ़ो8(hw, B2_E_1) & 0xf;
	pmd_type = skge_पढ़ो8(hw, B2_PMD_TYP);
	hw->copper = (pmd_type == 'T' || pmd_type == '1');

	चयन (hw->chip_id) अणु
	हाल CHIP_ID_GENESIS:
#अगर_घोषित CONFIG_SKGE_GENESIS
		चयन (hw->phy_type) अणु
		हाल SK_PHY_XMAC:
			hw->phy_addr = PHY_ADDR_XMAC;
			अवरोध;
		हाल SK_PHY_BCOM:
			hw->phy_addr = PHY_ADDR_BCOM;
			अवरोध;
		शेष:
			dev_err(&hw->pdev->dev, "unsupported phy type 0x%x\n",
			       hw->phy_type);
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
#अन्यथा
		dev_err(&hw->pdev->dev, "Genesis chip detected but not configured\n");
		वापस -EOPNOTSUPP;
#पूर्ण_अगर

	हाल CHIP_ID_YUKON:
	हाल CHIP_ID_YUKON_LITE:
	हाल CHIP_ID_YUKON_LP:
		अगर (hw->phy_type < SK_PHY_MARV_COPPER && pmd_type != 'S')
			hw->copper = 1;

		hw->phy_addr = PHY_ADDR_MARV;
		अवरोध;

	शेष:
		dev_err(&hw->pdev->dev, "unsupported chip type 0x%x\n",
		       hw->chip_id);
		वापस -EOPNOTSUPP;
	पूर्ण

	mac_cfg = skge_पढ़ो8(hw, B2_MAC_CFG);
	hw->ports = (mac_cfg & CFG_SNG_MAC) ? 1 : 2;
	hw->chip_rev = (mac_cfg & CFG_CHIP_R_MSK) >> 4;

	/* पढ़ो the adapters RAM size */
	t8 = skge_पढ़ो8(hw, B2_E_0);
	अगर (is_genesis(hw)) अणु
		अगर (t8 == 3) अणु
			/* special हाल: 4 x 64k x 36, offset = 0x80000 */
			hw->ram_size = 0x100000;
			hw->ram_offset = 0x80000;
		पूर्ण अन्यथा
			hw->ram_size = t8 * 512;
	पूर्ण अन्यथा अगर (t8 == 0)
		hw->ram_size = 0x20000;
	अन्यथा
		hw->ram_size = t8 * 4096;

	hw->पूर्णांकr_mask = IS_HW_ERR;

	/* Use PHY IRQ क्रम all but fiber based Genesis board */
	अगर (!(is_genesis(hw) && hw->phy_type == SK_PHY_XMAC))
		hw->पूर्णांकr_mask |= IS_EXT_REG;

	अगर (is_genesis(hw))
		genesis_init(hw);
	अन्यथा अणु
		/* चयन घातer to VCC (WA क्रम VAUX problem) */
		skge_ग_लिखो8(hw, B0_POWER_CTRL,
			    PC_VAUX_ENA | PC_VCC_ENA | PC_VAUX_OFF | PC_VCC_ON);

		/* aव्योम boards with stuck Hardware error bits */
		अगर ((skge_पढ़ो32(hw, B0_ISRC) & IS_HW_ERR) &&
		    (skge_पढ़ो32(hw, B0_HWE_ISRC) & IS_IRQ_SENSOR)) अणु
			dev_warn(&hw->pdev->dev, "stuck hardware sensor bit\n");
			hw->पूर्णांकr_mask &= ~IS_HW_ERR;
		पूर्ण

		/* Clear PHY COMA */
		skge_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		pci_पढ़ो_config_dword(hw->pdev, PCI_DEV_REG1, &reg);
		reg &= ~PCI_PHY_COMA;
		pci_ग_लिखो_config_dword(hw->pdev, PCI_DEV_REG1, reg);
		skge_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);


		क्रम (i = 0; i < hw->ports; i++) अणु
			skge_ग_लिखो16(hw, SK_REG(i, GMAC_LINK_CTRL), GMLC_RST_SET);
			skge_ग_लिखो16(hw, SK_REG(i, GMAC_LINK_CTRL), GMLC_RST_CLR);
		पूर्ण
	पूर्ण

	/* turn off hardware समयr (unused) */
	skge_ग_लिखो8(hw, B2_TI_CTRL, TIM_STOP);
	skge_ग_लिखो8(hw, B2_TI_CTRL, TIM_CLR_IRQ);
	skge_ग_लिखो8(hw, B0_LED, LED_STAT_ON);

	/* enable the Tx Arbiters */
	क्रम (i = 0; i < hw->ports; i++)
		skge_ग_लिखो8(hw, SK_REG(i, TXA_CTRL), TXA_ENA_ARB);

	/* Initialize ram पूर्णांकerface */
	skge_ग_लिखो16(hw, B3_RI_CTRL, RI_RST_CLR);

	skge_ग_लिखो8(hw, B3_RI_WTO_R1, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_WTO_XA1, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_WTO_XS1, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_RTO_R1, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_RTO_XA1, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_RTO_XS1, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_WTO_R2, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_WTO_XA2, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_WTO_XS2, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_RTO_R2, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_RTO_XA2, SK_RI_TO_53);
	skge_ग_लिखो8(hw, B3_RI_RTO_XS2, SK_RI_TO_53);

	skge_ग_लिखो32(hw, B0_HWE_IMSK, IS_ERR_MSK);

	/* Set पूर्णांकerrupt moderation क्रम Transmit only
	 * Receive पूर्णांकerrupts aव्योमed by NAPI
	 */
	skge_ग_लिखो32(hw, B2_IRQM_MSK, IS_XA1_F|IS_XA2_F);
	skge_ग_लिखो32(hw, B2_IRQM_INI, skge_usecs2clk(hw, 100));
	skge_ग_लिखो32(hw, B2_IRQM_CTRL, TIM_START);

	/* Leave irq disabled until first port is brought up. */
	skge_ग_लिखो32(hw, B0_IMSK, 0);

	क्रम (i = 0; i < hw->ports; i++) अणु
		अगर (is_genesis(hw))
			genesis_reset(hw, i);
		अन्यथा
			yukon_reset(hw, i);
	पूर्ण

	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_SKGE_DEBUG

अटल काष्ठा dentry *skge_debug;

अटल पूर्णांक skge_debug_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net_device *dev = seq->निजी;
	स्थिर काष्ठा skge_port *skge = netdev_priv(dev);
	स्थिर काष्ठा skge_hw *hw = skge->hw;
	स्थिर काष्ठा skge_element *e;

	अगर (!netअगर_running(dev))
		वापस -ENETDOWN;

	seq_म_लिखो(seq, "IRQ src=%x mask=%x\n", skge_पढ़ो32(hw, B0_ISRC),
		   skge_पढ़ो32(hw, B0_IMSK));

	seq_म_लिखो(seq, "Tx Ring: (%d)\n", skge_avail(&skge->tx_ring));
	क्रम (e = skge->tx_ring.to_clean; e != skge->tx_ring.to_use; e = e->next) अणु
		स्थिर काष्ठा skge_tx_desc *t = e->desc;
		seq_म_लिखो(seq, "%#x dma=%#x%08x %#x csum=%#x/%x/%x\n",
			   t->control, t->dma_hi, t->dma_lo, t->status,
			   t->csum_offs, t->csum_ग_लिखो, t->csum_start);
	पूर्ण

	seq_माला_दो(seq, "\nRx Ring:\n");
	क्रम (e = skge->rx_ring.to_clean; ; e = e->next) अणु
		स्थिर काष्ठा skge_rx_desc *r = e->desc;

		अगर (r->control & BMU_OWN)
			अवरोध;

		seq_म_लिखो(seq, "%#x dma=%#x%08x %#x %#x csum=%#x/%x\n",
			   r->control, r->dma_hi, r->dma_lo, r->status,
			   r->बारtamp, r->csum1, r->csum1_start);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(skge_debug);

/*
 * Use network device events to create/हटाओ/नाम
 * debugfs file entries
 */
अटल पूर्णांक skge_device_event(काष्ठा notअगरier_block *unused,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा skge_port *skge;

	अगर (dev->netdev_ops->nकरो_खोलो != &skge_up || !skge_debug)
		जाओ करोne;

	skge = netdev_priv(dev);
	चयन (event) अणु
	हाल NETDEV_CHANGENAME:
		अगर (skge->debugfs)
			skge->debugfs = debugfs_नाम(skge_debug,
						       skge->debugfs,
						       skge_debug, dev->name);
		अवरोध;

	हाल NETDEV_GOING_DOWN:
		debugfs_हटाओ(skge->debugfs);
		skge->debugfs = शून्य;
		अवरोध;

	हाल NETDEV_UP:
		skge->debugfs = debugfs_create_file(dev->name, 0444, skge_debug,
						    dev, &skge_debug_fops);
		अवरोध;
	पूर्ण

करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block skge_notअगरier = अणु
	.notअगरier_call = skge_device_event,
पूर्ण;


अटल __init व्योम skge_debug_init(व्योम)
अणु
	skge_debug = debugfs_create_dir("skge", शून्य);

	रेजिस्टर_netdevice_notअगरier(&skge_notअगरier);
पूर्ण

अटल __निकास व्योम skge_debug_cleanup(व्योम)
अणु
	अगर (skge_debug) अणु
		unरेजिस्टर_netdevice_notअगरier(&skge_notअगरier);
		debugfs_हटाओ(skge_debug);
		skge_debug = शून्य;
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा skge_debug_init()
#घोषणा skge_debug_cleanup()
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops skge_netdev_ops = अणु
	.nकरो_खोलो		= skge_up,
	.nकरो_stop		= skge_करोwn,
	.nकरो_start_xmit		= skge_xmit_frame,
	.nकरो_करो_ioctl		= skge_ioctl,
	.nकरो_get_stats		= skge_get_stats,
	.nकरो_tx_समयout		= skge_tx_समयout,
	.nकरो_change_mtu		= skge_change_mtu,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= skge_set_multicast,
	.nकरो_set_mac_address	= skge_set_mac_address,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= skge_netpoll,
#पूर्ण_अगर
पूर्ण;


/* Initialize network device */
अटल काष्ठा net_device *skge_devinit(काष्ठा skge_hw *hw, पूर्णांक port,
				       पूर्णांक highmem)
अणु
	काष्ठा skge_port *skge;
	काष्ठा net_device *dev = alloc_etherdev(माप(*skge));

	अगर (!dev)
		वापस शून्य;

	SET_NETDEV_DEV(dev, &hw->pdev->dev);
	dev->netdev_ops = &skge_netdev_ops;
	dev->ethtool_ops = &skge_ethtool_ops;
	dev->watchकरोg_समयo = TX_WATCHDOG;
	dev->irq = hw->pdev->irq;

	/* MTU range: 60 - 9000 */
	dev->min_mtu = ETH_ZLEN;
	dev->max_mtu = ETH_JUMBO_MTU;

	अगर (highmem)
		dev->features |= NETIF_F_HIGHDMA;

	skge = netdev_priv(dev);
	netअगर_napi_add(dev, &skge->napi, skge_poll, NAPI_WEIGHT);
	skge->netdev = dev;
	skge->hw = hw;
	skge->msg_enable = netअगर_msg_init(debug, शेष_msg);

	skge->tx_ring.count = DEFAULT_TX_RING_SIZE;
	skge->rx_ring.count = DEFAULT_RX_RING_SIZE;

	/* Auto speed and flow control */
	skge->स्वतःneg = AUTONEG_ENABLE;
	skge->flow_control = FLOW_MODE_SYM_OR_REM;
	skge->duplex = -1;
	skge->speed = -1;
	skge->advertising = skge_supported_modes(hw);

	अगर (device_can_wakeup(&hw->pdev->dev)) अणु
		skge->wol = wol_supported(hw) & WAKE_MAGIC;
		device_set_wakeup_enable(&hw->pdev->dev, skge->wol);
	पूर्ण

	hw->dev[port] = dev;

	skge->port = port;

	/* Only used क्रम Genesis XMAC */
	अगर (is_genesis(hw))
		समयr_setup(&skge->link_समयr, xm_link_समयr, 0);
	अन्यथा अणु
		dev->hw_features = NETIF_F_IP_CSUM | NETIF_F_SG |
		                   NETIF_F_RXCSUM;
		dev->features |= dev->hw_features;
	पूर्ण

	/* पढ़ो the mac address */
	स_नकल_fromio(dev->dev_addr, hw->regs + B2_MAC_1 + port*8, ETH_ALEN);

	वापस dev;
पूर्ण

अटल व्योम skge_show_addr(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा skge_port *skge = netdev_priv(dev);

	netअगर_info(skge, probe, skge->netdev, "addr %pM\n", dev->dev_addr);
पूर्ण

अटल पूर्णांक only_32bit_dma;

अटल पूर्णांक skge_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev, *dev1;
	काष्ठा skge_hw *hw;
	पूर्णांक err, using_dac = 0;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		जाओ err_out;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot obtain PCI resources\n");
		जाओ err_out_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	अगर (!only_32bit_dma && !dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
		using_dac = 1;
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64));
	पूर्ण अन्यथा अगर (!(err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32)))) अणु
		using_dac = 0;
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	पूर्ण

	अगर (err) अणु
		dev_err(&pdev->dev, "no usable DMA configuration\n");
		जाओ err_out_मुक्त_regions;
	पूर्ण

#अगर_घोषित __BIG_ENDIAN
	/* byte swap descriptors in hardware */
	अणु
		u32 reg;

		pci_पढ़ो_config_dword(pdev, PCI_DEV_REG2, &reg);
		reg |= PCI_REV_DESC;
		pci_ग_लिखो_config_dword(pdev, PCI_DEV_REG2, reg);
	पूर्ण
#पूर्ण_अगर

	err = -ENOMEM;
	/* space क्रम skge@pci:0000:04:00.0 */
	hw = kzalloc(माप(*hw) + म_माप(DRV_NAME "@pci:")
		     + म_माप(pci_name(pdev)) + 1, GFP_KERNEL);
	अगर (!hw)
		जाओ err_out_मुक्त_regions;

	प्र_लिखो(hw->irq_name, DRV_NAME "@pci:%s", pci_name(pdev));

	hw->pdev = pdev;
	spin_lock_init(&hw->hw_lock);
	spin_lock_init(&hw->phy_lock);
	tasklet_setup(&hw->phy_task, skge_extirq);

	hw->regs = ioremap(pci_resource_start(pdev, 0), 0x4000);
	अगर (!hw->regs) अणु
		dev_err(&pdev->dev, "cannot map device registers\n");
		जाओ err_out_मुक्त_hw;
	पूर्ण

	err = skge_reset(hw);
	अगर (err)
		जाओ err_out_iounmap;

	pr_info("%s addr 0x%llx irq %d chip %s rev %d\n",
		DRV_VERSION,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 0), pdev->irq,
		skge_board_name(hw), hw->chip_rev);

	dev = skge_devinit(hw, 0, using_dac);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out_led_off;
	पूर्ण

	/* Some motherboards are broken and has zero in ROM. */
	अगर (!is_valid_ether_addr(dev->dev_addr))
		dev_warn(&pdev->dev, "bad (zero?) ethernet address in rom\n");

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot register net device\n");
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	skge_show_addr(dev);

	अगर (hw->ports > 1) अणु
		dev1 = skge_devinit(hw, 1, using_dac);
		अगर (!dev1) अणु
			err = -ENOMEM;
			जाओ err_out_unरेजिस्टर;
		पूर्ण

		err = रेजिस्टर_netdev(dev1);
		अगर (err) अणु
			dev_err(&pdev->dev, "cannot register second net device\n");
			जाओ err_out_मुक्त_dev1;
		पूर्ण

		err = request_irq(pdev->irq, skge_पूर्णांकr, IRQF_SHARED,
				  hw->irq_name, hw);
		अगर (err) अणु
			dev_err(&pdev->dev, "cannot assign irq %d\n",
				pdev->irq);
			जाओ err_out_unरेजिस्टर_dev1;
		पूर्ण

		skge_show_addr(dev1);
	पूर्ण
	pci_set_drvdata(pdev, hw);

	वापस 0;

err_out_unरेजिस्टर_dev1:
	unरेजिस्टर_netdev(dev1);
err_out_मुक्त_dev1:
	मुक्त_netdev(dev1);
err_out_unरेजिस्टर:
	unरेजिस्टर_netdev(dev);
err_out_मुक्त_netdev:
	मुक्त_netdev(dev);
err_out_led_off:
	skge_ग_लिखो16(hw, B0_LED, LED_STAT_OFF);
err_out_iounmap:
	iounmap(hw->regs);
err_out_मुक्त_hw:
	kमुक्त(hw);
err_out_मुक्त_regions:
	pci_release_regions(pdev);
err_out_disable_pdev:
	pci_disable_device(pdev);
err_out:
	वापस err;
पूर्ण

अटल व्योम skge_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा skge_hw *hw  = pci_get_drvdata(pdev);
	काष्ठा net_device *dev0, *dev1;

	अगर (!hw)
		वापस;

	dev1 = hw->dev[1];
	अगर (dev1)
		unरेजिस्टर_netdev(dev1);
	dev0 = hw->dev[0];
	unरेजिस्टर_netdev(dev0);

	tasklet_समाप्त(&hw->phy_task);

	spin_lock_irq(&hw->hw_lock);
	hw->पूर्णांकr_mask = 0;

	अगर (hw->ports > 1) अणु
		skge_ग_लिखो32(hw, B0_IMSK, 0);
		skge_पढ़ो32(hw, B0_IMSK);
	पूर्ण
	spin_unlock_irq(&hw->hw_lock);

	skge_ग_लिखो16(hw, B0_LED, LED_STAT_OFF);
	skge_ग_लिखो8(hw, B0_CTST, CS_RST_SET);

	अगर (hw->ports > 1)
		मुक्त_irq(pdev->irq, hw);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	अगर (dev1)
		मुक्त_netdev(dev1);
	मुक्त_netdev(dev0);

	iounmap(hw->regs);
	kमुक्त(hw);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक skge_suspend(काष्ठा device *dev)
अणु
	काष्ठा skge_hw *hw  = dev_get_drvdata(dev);
	पूर्णांक i;

	अगर (!hw)
		वापस 0;

	क्रम (i = 0; i < hw->ports; i++) अणु
		काष्ठा net_device *dev = hw->dev[i];
		काष्ठा skge_port *skge = netdev_priv(dev);

		अगर (netअगर_running(dev))
			skge_करोwn(dev);

		अगर (skge->wol)
			skge_wol_init(skge);
	पूर्ण

	skge_ग_लिखो32(hw, B0_IMSK, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक skge_resume(काष्ठा device *dev)
अणु
	काष्ठा skge_hw *hw  = dev_get_drvdata(dev);
	पूर्णांक i, err;

	अगर (!hw)
		वापस 0;

	err = skge_reset(hw);
	अगर (err)
		जाओ out;

	क्रम (i = 0; i < hw->ports; i++) अणु
		काष्ठा net_device *dev = hw->dev[i];

		अगर (netअगर_running(dev)) अणु
			err = skge_up(dev);

			अगर (err) अणु
				netdev_err(dev, "could not up: %d\n", err);
				dev_बंद(dev);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस err;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(skge_pm_ops, skge_suspend, skge_resume);
#घोषणा SKGE_PM_OPS (&skge_pm_ops)

#अन्यथा

#घोषणा SKGE_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल व्योम skge_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा skge_hw *hw  = pci_get_drvdata(pdev);
	पूर्णांक i;

	अगर (!hw)
		वापस;

	क्रम (i = 0; i < hw->ports; i++) अणु
		काष्ठा net_device *dev = hw->dev[i];
		काष्ठा skge_port *skge = netdev_priv(dev);

		अगर (skge->wol)
			skge_wol_init(skge);
	पूर्ण

	pci_wake_from_d3(pdev, device_may_wakeup(&pdev->dev));
	pci_set_घातer_state(pdev, PCI_D3hot);
पूर्ण

अटल काष्ठा pci_driver skge_driver = अणु
	.name =         DRV_NAME,
	.id_table =     skge_id_table,
	.probe =        skge_probe,
	.हटाओ =       skge_हटाओ,
	.shutकरोwn =	skge_shutकरोwn,
	.driver.pm =	SKGE_PM_OPS,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id skge_32bit_dma_boards[] = अणु
	अणु
		.ident = "Gigabyte nForce boards",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Gigabyte Technology Co"),
			DMI_MATCH(DMI_BOARD_NAME, "nForce"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ASUS P5NSLI",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "P5NSLI")
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "FUJITSU SIEMENS A8NE-FM",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTek Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "A8NE-FM")
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init skge_init_module(व्योम)
अणु
	अगर (dmi_check_प्रणाली(skge_32bit_dma_boards))
		only_32bit_dma = 1;
	skge_debug_init();
	वापस pci_रेजिस्टर_driver(&skge_driver);
पूर्ण

अटल व्योम __निकास skge_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&skge_driver);
	skge_debug_cleanup();
पूर्ण

module_init(skge_init_module);
module_निकास(skge_cleanup_module);
