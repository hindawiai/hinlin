<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * New driver क्रम Marvell Yukon 2 chipset.
 * Based on earlier sk98lin, and skge driver.
 *
 * This driver पूर्णांकentionally करोes not support all the features
 * of the original driver such as link fail-over and link management because
 * those should be करोne at higher levels.
 *
 * Copyright (C) 2005 Stephen Hemminger <shemminger@osdl.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/crc32.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/slab.h>
#समावेश <net/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/in.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/mii.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/dmi.h>

#समावेश <यंत्र/irq.h>

#समावेश "sky2.h"

#घोषणा DRV_NAME		"sky2"
#घोषणा DRV_VERSION		"1.30"

/*
 * The Yukon II chipset takes 64 bit command blocks (called list elements)
 * that are organized पूर्णांकo three (receive, transmit, status) dअगरferent rings
 * similar to Tigon3.
 */

#घोषणा RX_LE_SIZE	    	1024
#घोषणा RX_LE_BYTES		(RX_LE_SIZE*माप(काष्ठा sky2_rx_le))
#घोषणा RX_MAX_PENDING		(RX_LE_SIZE/6 - 2)
#घोषणा RX_DEF_PENDING		RX_MAX_PENDING

/* This is the worst हाल number of transmit list elements क्रम a single skb:
 * VLAN:GSO + CKSUM + Data + skb_frags * DMA
 */
#घोषणा MAX_SKB_TX_LE	(2 + (माप(dma_addr_t)/माप(u32))*(MAX_SKB_FRAGS+1))
#घोषणा TX_MIN_PENDING		(MAX_SKB_TX_LE+1)
#घोषणा TX_MAX_PENDING		1024
#घोषणा TX_DEF_PENDING		63

#घोषणा TX_WATCHDOG		(5 * HZ)
#घोषणा NAPI_WEIGHT		64
#घोषणा PHY_RETRIES		1000

#घोषणा SKY2_EEPROM_MAGIC	0x9955aabb

#घोषणा RING_NEXT(x, s)	(((x)+1) & ((s)-1))

अटल स्थिर u32 शेष_msg =
    NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK
    | NETIF_MSG_TIMER | NETIF_MSG_TX_ERR | NETIF_MSG_RX_ERR
    | NETIF_MSG_IFUP | NETIF_MSG_IFDOWN;

अटल पूर्णांक debug = -1;		/* शेषs above */
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

अटल पूर्णांक copyअवरोध __पढ़ो_mostly = 128;
module_param(copyअवरोध, पूर्णांक, 0);
MODULE_PARM_DESC(copyअवरोध, "Receive copy threshold");

अटल पूर्णांक disable_msi = -1;
module_param(disable_msi, पूर्णांक, 0);
MODULE_PARM_DESC(disable_msi, "Disable Message Signaled Interrupt (MSI)");

अटल पूर्णांक legacy_pme = 0;
module_param(legacy_pme, पूर्णांक, 0);
MODULE_PARM_DESC(legacy_pme, "Legacy power management");

अटल स्थिर काष्ठा pci_device_id sky2_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SYSKONNECT, 0x9000) पूर्ण, /* SK-9Sxx */
	अणु PCI_DEVICE(PCI_VENDOR_ID_SYSKONNECT, 0x9E00) पूर्ण, /* SK-9Exx */
	अणु PCI_DEVICE(PCI_VENDOR_ID_SYSKONNECT, 0x9E01) पूर्ण, /* SK-9E21M */
	अणु PCI_DEVICE(PCI_VENDOR_ID_DLINK, 0x4b00) पूर्ण,	/* DGE-560T */
	अणु PCI_DEVICE(PCI_VENDOR_ID_DLINK, 0x4001) पूर्ण, 	/* DGE-550SX */
	अणु PCI_DEVICE(PCI_VENDOR_ID_DLINK, 0x4B02) पूर्ण,	/* DGE-560SX */
	अणु PCI_DEVICE(PCI_VENDOR_ID_DLINK, 0x4B03) पूर्ण,	/* DGE-550T */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4340) पूर्ण, /* 88E8021 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4341) पूर्ण, /* 88E8022 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4342) पूर्ण, /* 88E8061 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4343) पूर्ण, /* 88E8062 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4344) पूर्ण, /* 88E8021 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4345) पूर्ण, /* 88E8022 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4346) पूर्ण, /* 88E8061 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4347) पूर्ण, /* 88E8062 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4350) पूर्ण, /* 88E8035 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4351) पूर्ण, /* 88E8036 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4352) पूर्ण, /* 88E8038 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4353) पूर्ण, /* 88E8039 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4354) पूर्ण, /* 88E8040 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4355) पूर्ण, /* 88E8040T */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4356) पूर्ण, /* 88EC033 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4357) पूर्ण, /* 88E8042 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x435A) पूर्ण, /* 88E8048 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4360) पूर्ण, /* 88E8052 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4361) पूर्ण, /* 88E8050 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4362) पूर्ण, /* 88E8053 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4363) पूर्ण, /* 88E8055 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4364) पूर्ण, /* 88E8056 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4365) पूर्ण, /* 88E8070 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4366) पूर्ण, /* 88EC036 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4367) पूर्ण, /* 88EC032 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4368) पूर्ण, /* 88EC034 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4369) पूर्ण, /* 88EC042 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x436A) पूर्ण, /* 88E8058 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x436B) पूर्ण, /* 88E8071 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x436C) पूर्ण, /* 88E8072 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x436D) पूर्ण, /* 88E8055 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4370) पूर्ण, /* 88E8075 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4380) पूर्ण, /* 88E8057 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4381) पूर्ण, /* 88E8059 */
	अणु PCI_DEVICE(PCI_VENDOR_ID_MARVELL, 0x4382) पूर्ण, /* 88E8079 */
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, sky2_id_table);

/* Aव्योम conditionals by using array */
अटल स्थिर अचिन्हित txqaddr[] = अणु Q_XA1, Q_XA2 पूर्ण;
अटल स्थिर अचिन्हित rxqaddr[] = अणु Q_R1, Q_R2 पूर्ण;
अटल स्थिर u32 portirq_msk[] = अणु Y2_IS_PORT_1, Y2_IS_PORT_2 पूर्ण;

अटल व्योम sky2_set_multicast(काष्ठा net_device *dev);
अटल irqवापस_t sky2_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);

/* Access to PHY via serial पूर्णांकerconnect */
अटल पूर्णांक gm_phy_ग_लिखो(काष्ठा sky2_hw *hw, अचिन्हित port, u16 reg, u16 val)
अणु
	पूर्णांक i;

	gma_ग_लिखो16(hw, port, GM_SMI_DATA, val);
	gma_ग_लिखो16(hw, port, GM_SMI_CTRL,
		    GM_SMI_CT_PHY_AD(PHY_ADDR_MARV) | GM_SMI_CT_REG_AD(reg));

	क्रम (i = 0; i < PHY_RETRIES; i++) अणु
		u16 ctrl = gma_पढ़ो16(hw, port, GM_SMI_CTRL);
		अगर (ctrl == 0xffff)
			जाओ io_error;

		अगर (!(ctrl & GM_SMI_CT_BUSY))
			वापस 0;

		udelay(10);
	पूर्ण

	dev_warn(&hw->pdev->dev, "%s: phy write timeout\n", hw->dev[port]->name);
	वापस -ETIMEDOUT;

io_error:
	dev_err(&hw->pdev->dev, "%s: phy I/O error\n", hw->dev[port]->name);
	वापस -EIO;
पूर्ण

अटल पूर्णांक __gm_phy_पढ़ो(काष्ठा sky2_hw *hw, अचिन्हित port, u16 reg, u16 *val)
अणु
	पूर्णांक i;

	gma_ग_लिखो16(hw, port, GM_SMI_CTRL, GM_SMI_CT_PHY_AD(PHY_ADDR_MARV)
		    | GM_SMI_CT_REG_AD(reg) | GM_SMI_CT_OP_RD);

	क्रम (i = 0; i < PHY_RETRIES; i++) अणु
		u16 ctrl = gma_पढ़ो16(hw, port, GM_SMI_CTRL);
		अगर (ctrl == 0xffff)
			जाओ io_error;

		अगर (ctrl & GM_SMI_CT_RD_VAL) अणु
			*val = gma_पढ़ो16(hw, port, GM_SMI_DATA);
			वापस 0;
		पूर्ण

		udelay(10);
	पूर्ण

	dev_warn(&hw->pdev->dev, "%s: phy read timeout\n", hw->dev[port]->name);
	वापस -ETIMEDOUT;
io_error:
	dev_err(&hw->pdev->dev, "%s: phy I/O error\n", hw->dev[port]->name);
	वापस -EIO;
पूर्ण

अटल अंतरभूत u16 gm_phy_पढ़ो(काष्ठा sky2_hw *hw, अचिन्हित port, u16 reg)
अणु
	u16 v = 0;
	__gm_phy_पढ़ो(hw, port, reg, &v);
	वापस v;
पूर्ण


अटल व्योम sky2_घातer_on(काष्ठा sky2_hw *hw)
अणु
	/* चयन घातer to VCC (WA क्रम VAUX problem) */
	sky2_ग_लिखो8(hw, B0_POWER_CTRL,
		    PC_VAUX_ENA | PC_VCC_ENA | PC_VAUX_OFF | PC_VCC_ON);

	/* disable Core Clock Division, */
	sky2_ग_लिखो32(hw, B2_Y2_CLK_CTRL, Y2_CLK_DIV_DIS);

	अगर (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev > CHIP_REV_YU_XL_A1)
		/* enable bits are inverted */
		sky2_ग_लिखो8(hw, B2_Y2_CLK_GATE,
			    Y2_PCI_CLK_LNK1_DIS | Y2_COR_CLK_LNK1_DIS |
			    Y2_CLK_GAT_LNK1_DIS | Y2_PCI_CLK_LNK2_DIS |
			    Y2_COR_CLK_LNK2_DIS | Y2_CLK_GAT_LNK2_DIS);
	अन्यथा
		sky2_ग_लिखो8(hw, B2_Y2_CLK_GATE, 0);

	अगर (hw->flags & SKY2_HW_ADV_POWER_CTL) अणु
		u32 reg;

		sky2_pci_ग_लिखो32(hw, PCI_DEV_REG3, 0);

		reg = sky2_pci_पढ़ो32(hw, PCI_DEV_REG4);
		/* set all bits to 0 except bits 15..12 and 8 */
		reg &= P_ASPM_CONTROL_MSK;
		sky2_pci_ग_लिखो32(hw, PCI_DEV_REG4, reg);

		reg = sky2_pci_पढ़ो32(hw, PCI_DEV_REG5);
		/* set all bits to 0 except bits 28 & 27 */
		reg &= P_CTL_TIM_VMAIN_AV_MSK;
		sky2_pci_ग_लिखो32(hw, PCI_DEV_REG5, reg);

		sky2_pci_ग_लिखो32(hw, PCI_CFG_REG_1, 0);

		sky2_ग_लिखो16(hw, B0_CTST, Y2_HW_WOL_ON);

		/* Enable workaround क्रम dev 4.107 on Yukon-Ultra & Extreme */
		reg = sky2_पढ़ो32(hw, B2_GP_IO);
		reg |= GLB_GPIO_STAT_RACE_DIS;
		sky2_ग_लिखो32(hw, B2_GP_IO, reg);

		sky2_पढ़ो32(hw, B2_GP_IO);
	पूर्ण

	/* Turn on "driver loaded" LED */
	sky2_ग_लिखो16(hw, B0_CTST, Y2_LED_STAT_ON);
पूर्ण

अटल व्योम sky2_घातer_aux(काष्ठा sky2_hw *hw)
अणु
	अगर (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev > CHIP_REV_YU_XL_A1)
		sky2_ग_लिखो8(hw, B2_Y2_CLK_GATE, 0);
	अन्यथा
		/* enable bits are inverted */
		sky2_ग_लिखो8(hw, B2_Y2_CLK_GATE,
			    Y2_PCI_CLK_LNK1_DIS | Y2_COR_CLK_LNK1_DIS |
			    Y2_CLK_GAT_LNK1_DIS | Y2_PCI_CLK_LNK2_DIS |
			    Y2_COR_CLK_LNK2_DIS | Y2_CLK_GAT_LNK2_DIS);

	/* चयन घातer to VAUX अगर supported and PME from D3cold */
	अगर ( (sky2_पढ़ो32(hw, B0_CTST) & Y2_VAUX_AVAIL) &&
	     pci_pme_capable(hw->pdev, PCI_D3cold))
		sky2_ग_लिखो8(hw, B0_POWER_CTRL,
			    (PC_VAUX_ENA | PC_VCC_ENA |
			     PC_VAUX_ON | PC_VCC_OFF));

	/* turn off "driver loaded LED" */
	sky2_ग_लिखो16(hw, B0_CTST, Y2_LED_STAT_OFF);
पूर्ण

अटल व्योम sky2_gmac_reset(काष्ठा sky2_hw *hw, अचिन्हित port)
अणु
	u16 reg;

	/* disable all GMAC IRQ's */
	sky2_ग_लिखो8(hw, SK_REG(port, GMAC_IRQ_MSK), 0);

	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H1, 0);	/* clear MC hash */
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H2, 0);
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H3, 0);
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H4, 0);

	reg = gma_पढ़ो16(hw, port, GM_RX_CTRL);
	reg |= GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA;
	gma_ग_लिखो16(hw, port, GM_RX_CTRL, reg);
पूर्ण

/* flow control to advertise bits */
अटल स्थिर u16 copper_fc_adv[] = अणु
	[FC_NONE]	= 0,
	[FC_TX]		= PHY_M_AN_ASP,
	[FC_RX]		= PHY_M_AN_PC,
	[FC_BOTH]	= PHY_M_AN_PC | PHY_M_AN_ASP,
पूर्ण;

/* flow control to advertise bits when using 1000BaseX */
अटल स्थिर u16 fiber_fc_adv[] = अणु
	[FC_NONE] = PHY_M_P_NO_PAUSE_X,
	[FC_TX]   = PHY_M_P_ASYM_MD_X,
	[FC_RX]	  = PHY_M_P_SYM_MD_X,
	[FC_BOTH] = PHY_M_P_BOTH_MD_X,
पूर्ण;

/* flow control to GMA disable bits */
अटल स्थिर u16 gm_fc_disable[] = अणु
	[FC_NONE] = GM_GPCR_FC_RX_DIS | GM_GPCR_FC_TX_DIS,
	[FC_TX]	  = GM_GPCR_FC_RX_DIS,
	[FC_RX]	  = GM_GPCR_FC_TX_DIS,
	[FC_BOTH] = 0,
पूर्ण;


अटल व्योम sky2_phy_init(काष्ठा sky2_hw *hw, अचिन्हित port)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(hw->dev[port]);
	u16 ctrl, ct1000, adv, pg, ledctrl, leकरोver, reg;

	अगर ( (sky2->flags & SKY2_FLAG_AUTO_SPEED) &&
	    !(hw->flags & SKY2_HW_NEWER_PHY)) अणु
		u16 ectrl = gm_phy_पढ़ो(hw, port, PHY_MARV_EXT_CTRL);

		ectrl &= ~(PHY_M_EC_M_DSC_MSK | PHY_M_EC_S_DSC_MSK |
			   PHY_M_EC_MAC_S_MSK);
		ectrl |= PHY_M_EC_MAC_S(MAC_TX_CLK_25_MHZ);

		/* on PHY 88E1040 Rev.D0 (and newer) करोwnshअगरt control changed */
		अगर (hw->chip_id == CHIP_ID_YUKON_EC)
			/* set करोwnshअगरt counter to 3x and enable करोwnshअगरt */
			ectrl |= PHY_M_EC_DSC_2(2) | PHY_M_EC_DOWN_S_ENA;
		अन्यथा
			/* set master & slave करोwnshअगरt counter to 1x */
			ectrl |= PHY_M_EC_M_DSC(0) | PHY_M_EC_S_DSC(1);

		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_CTRL, ectrl);
	पूर्ण

	ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_PHY_CTRL);
	अगर (sky2_is_copper(hw)) अणु
		अगर (!(hw->flags & SKY2_HW_GIGABIT)) अणु
			/* enable स्वतःmatic crossover */
			ctrl |= PHY_M_PC_MDI_XMODE(PHY_M_PC_ENA_AUTO) >> 1;

			अगर (hw->chip_id == CHIP_ID_YUKON_FE_P &&
			    hw->chip_rev == CHIP_REV_YU_FE2_A0) अणु
				u16 spec;

				/* Enable Class A driver क्रम FE+ A0 */
				spec = gm_phy_पढ़ो(hw, port, PHY_MARV_FE_SPEC_2);
				spec |= PHY_M_FESC_SEL_CL_A;
				gm_phy_ग_लिखो(hw, port, PHY_MARV_FE_SPEC_2, spec);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* disable energy detect */
			ctrl &= ~PHY_M_PC_EN_DET_MSK;

			/* enable स्वतःmatic crossover */
			ctrl |= PHY_M_PC_MDI_XMODE(PHY_M_PC_ENA_AUTO);

			/* करोwnshअगरt on PHY 88E1112 and 88E1149 is changed */
			अगर ( (sky2->flags & SKY2_FLAG_AUTO_SPEED) &&
			     (hw->flags & SKY2_HW_NEWER_PHY)) अणु
				/* set करोwnshअगरt counter to 3x and enable करोwnshअगरt */
				ctrl &= ~PHY_M_PC_DSC_MSK;
				ctrl |= PHY_M_PC_DSC(2) | PHY_M_PC_DOWN_S_ENA;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* workaround क्रम deviation #4.88 (CRC errors) */
		/* disable Automatic Crossover */

		ctrl &= ~PHY_M_PC_MDIX_MSK;
	पूर्ण

	gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL, ctrl);

	/* special setup क्रम PHY 88E1112 Fiber */
	अगर (hw->chip_id == CHIP_ID_YUKON_XL && (hw->flags & SKY2_HW_FIBRE_PHY)) अणु
		pg = gm_phy_पढ़ो(hw, port, PHY_MARV_EXT_ADR);

		/* Fiber: select 1000BASE-X only mode MAC Specअगरic Ctrl Reg. */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 2);
		ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_PHY_CTRL);
		ctrl &= ~PHY_M_MAC_MD_MSK;
		ctrl |= PHY_M_MAC_MODE_SEL(PHY_M_MAC_MD_1000BX);
		gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL, ctrl);

		अगर (hw->pmd_type  == 'P') अणु
			/* select page 1 to access Fiber रेजिस्टरs */
			gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 1);

			/* क्रम SFP-module set SIGDET polarity to low */
			ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_PHY_CTRL);
			ctrl |= PHY_M_FIB_SIGD_POL;
			gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL, ctrl);
		पूर्ण

		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, pg);
	पूर्ण

	ctrl = PHY_CT_RESET;
	ct1000 = 0;
	adv = PHY_AN_CSMA;
	reg = 0;

	अगर (sky2->flags & SKY2_FLAG_AUTO_SPEED) अणु
		अगर (sky2_is_copper(hw)) अणु
			अगर (sky2->advertising & ADVERTISED_1000baseT_Full)
				ct1000 |= PHY_M_1000C_AFD;
			अगर (sky2->advertising & ADVERTISED_1000baseT_Half)
				ct1000 |= PHY_M_1000C_AHD;
			अगर (sky2->advertising & ADVERTISED_100baseT_Full)
				adv |= PHY_M_AN_100_FD;
			अगर (sky2->advertising & ADVERTISED_100baseT_Half)
				adv |= PHY_M_AN_100_HD;
			अगर (sky2->advertising & ADVERTISED_10baseT_Full)
				adv |= PHY_M_AN_10_FD;
			अगर (sky2->advertising & ADVERTISED_10baseT_Half)
				adv |= PHY_M_AN_10_HD;

		पूर्ण अन्यथा अणु	/* special defines क्रम FIBER (88E1040S only) */
			अगर (sky2->advertising & ADVERTISED_1000baseT_Full)
				adv |= PHY_M_AN_1000X_AFD;
			अगर (sky2->advertising & ADVERTISED_1000baseT_Half)
				adv |= PHY_M_AN_1000X_AHD;
		पूर्ण

		/* Restart Auto-negotiation */
		ctrl |= PHY_CT_ANE | PHY_CT_RE_CFG;
	पूर्ण अन्यथा अणु
		/* क्रमced speed/duplex settings */
		ct1000 = PHY_M_1000C_MSE;

		/* Disable स्वतः update क्रम duplex flow control and duplex */
		reg |= GM_GPCR_AU_DUP_DIS | GM_GPCR_AU_SPD_DIS;

		चयन (sky2->speed) अणु
		हाल SPEED_1000:
			ctrl |= PHY_CT_SP1000;
			reg |= GM_GPCR_SPEED_1000;
			अवरोध;
		हाल SPEED_100:
			ctrl |= PHY_CT_SP100;
			reg |= GM_GPCR_SPEED_100;
			अवरोध;
		पूर्ण

		अगर (sky2->duplex == DUPLEX_FULL) अणु
			reg |= GM_GPCR_DUP_FULL;
			ctrl |= PHY_CT_DUP_MD;
		पूर्ण अन्यथा अगर (sky2->speed < SPEED_1000)
			sky2->flow_mode = FC_NONE;
	पूर्ण

	अगर (sky2->flags & SKY2_FLAG_AUTO_PAUSE) अणु
		अगर (sky2_is_copper(hw))
			adv |= copper_fc_adv[sky2->flow_mode];
		अन्यथा
			adv |= fiber_fc_adv[sky2->flow_mode];
	पूर्ण अन्यथा अणु
		reg |= GM_GPCR_AU_FCT_DIS;
 		reg |= gm_fc_disable[sky2->flow_mode];

		/* Forward छोड़ो packets to GMAC? */
		अगर (sky2->flow_mode & FC_RX)
			sky2_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_ON);
		अन्यथा
			sky2_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);
	पूर्ण

	gma_ग_लिखो16(hw, port, GM_GP_CTRL, reg);

	अगर (hw->flags & SKY2_HW_GIGABIT)
		gm_phy_ग_लिखो(hw, port, PHY_MARV_1000T_CTRL, ct1000);

	gm_phy_ग_लिखो(hw, port, PHY_MARV_AUNE_ADV, adv);
	gm_phy_ग_लिखो(hw, port, PHY_MARV_CTRL, ctrl);

	/* Setup Phy LED's */
	ledctrl = PHY_M_LED_PULS_DUR(PULS_170MS);
	leकरोver = 0;

	चयन (hw->chip_id) अणु
	हाल CHIP_ID_YUKON_FE:
		/* on 88E3082 these bits are at 11..9 (shअगरted left) */
		ledctrl |= PHY_M_LED_BLINK_RT(BLINK_84MS) << 1;

		ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_FE_LED_PAR);

		/* delete ACT LED control bits */
		ctrl &= ~PHY_M_FELP_LED1_MSK;
		/* change ACT LED control to blink mode */
		ctrl |= PHY_M_FELP_LED1_CTRL(LED_PAR_CTRL_ACT_BL);
		gm_phy_ग_लिखो(hw, port, PHY_MARV_FE_LED_PAR, ctrl);
		अवरोध;

	हाल CHIP_ID_YUKON_FE_P:
		/* Enable Link Partner Next Page */
		ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_PHY_CTRL);
		ctrl |= PHY_M_PC_ENA_LIP_NP;

		/* disable Energy Detect and enable scrambler */
		ctrl &= ~(PHY_M_PC_ENA_ENE_DT | PHY_M_PC_DIS_SCRAMB);
		gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL, ctrl);

		/* set LED2 -> ACT, LED1 -> LINK, LED0 -> SPEED */
		ctrl = PHY_M_FELP_LED2_CTRL(LED_PAR_CTRL_ACT_BL) |
			PHY_M_FELP_LED1_CTRL(LED_PAR_CTRL_LINK) |
			PHY_M_FELP_LED0_CTRL(LED_PAR_CTRL_SPEED);

		gm_phy_ग_लिखो(hw, port, PHY_MARV_FE_LED_PAR, ctrl);
		अवरोध;

	हाल CHIP_ID_YUKON_XL:
		pg = gm_phy_पढ़ो(hw, port, PHY_MARV_EXT_ADR);

		/* select page 3 to access LED control रेजिस्टर */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 3);

		/* set LED Function Control रेजिस्टर */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL,
			     (PHY_M_LEDC_LOS_CTRL(1) |	/* LINK/ACT */
			      PHY_M_LEDC_INIT_CTRL(7) |	/* 10 Mbps */
			      PHY_M_LEDC_STA1_CTRL(7) |	/* 100 Mbps */
			      PHY_M_LEDC_STA0_CTRL(7)));	/* 1000 Mbps */

		/* set Polarity Control रेजिस्टर */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_STAT,
			     (PHY_M_POLC_LS1_P_MIX(4) |
			      PHY_M_POLC_IS0_P_MIX(4) |
			      PHY_M_POLC_LOS_CTRL(2) |
			      PHY_M_POLC_INIT_CTRL(2) |
			      PHY_M_POLC_STA1_CTRL(2) |
			      PHY_M_POLC_STA0_CTRL(2)));

		/* restore page रेजिस्टर */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, pg);
		अवरोध;

	हाल CHIP_ID_YUKON_EC_U:
	हाल CHIP_ID_YUKON_EX:
	हाल CHIP_ID_YUKON_SUPR:
		pg = gm_phy_पढ़ो(hw, port, PHY_MARV_EXT_ADR);

		/* select page 3 to access LED control रेजिस्टर */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 3);

		/* set LED Function Control रेजिस्टर */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL,
			     (PHY_M_LEDC_LOS_CTRL(1) |	/* LINK/ACT */
			      PHY_M_LEDC_INIT_CTRL(8) |	/* 10 Mbps */
			      PHY_M_LEDC_STA1_CTRL(7) |	/* 100 Mbps */
			      PHY_M_LEDC_STA0_CTRL(7)));/* 1000 Mbps */

		/* set Blink Rate in LED Timer Control Register */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_INT_MASK,
			     ledctrl | PHY_M_LED_BLINK_RT(BLINK_84MS));
		/* restore page रेजिस्टर */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, pg);
		अवरोध;

	शेष:
		/* set Tx LED (LED_TX) to blink mode on Rx OR Tx activity */
		ledctrl |= PHY_M_LED_BLINK_RT(BLINK_84MS) | PHY_M_LEDC_TX_CTRL;

		/* turn off the Rx LED (LED_RX) */
		leकरोver |= PHY_M_LED_MO_RX(MO_LED_OFF);
	पूर्ण

	अगर (hw->chip_id == CHIP_ID_YUKON_EC_U || hw->chip_id == CHIP_ID_YUKON_UL_2) अणु
		/* apply fixes in PHY AFE */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 255);

		/* increase dअगरferential संकेत amplitude in 10BASE-T */
		gm_phy_ग_लिखो(hw, port, 0x18, 0xaa99);
		gm_phy_ग_लिखो(hw, port, 0x17, 0x2011);

		अगर (hw->chip_id == CHIP_ID_YUKON_EC_U) अणु
			/* fix क्रम IEEE A/B Symmetry failure in 1000BASE-T */
			gm_phy_ग_लिखो(hw, port, 0x18, 0xa204);
			gm_phy_ग_लिखो(hw, port, 0x17, 0x2002);
		पूर्ण

		/* set page रेजिस्टर to 0 */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 0);
	पूर्ण अन्यथा अगर (hw->chip_id == CHIP_ID_YUKON_FE_P &&
		   hw->chip_rev == CHIP_REV_YU_FE2_A0) अणु
		/* apply workaround क्रम पूर्णांकegrated resistors calibration */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_PAGE_ADDR, 17);
		gm_phy_ग_लिखो(hw, port, PHY_MARV_PAGE_DATA, 0x3f60);
	पूर्ण अन्यथा अगर (hw->chip_id == CHIP_ID_YUKON_OPT && hw->chip_rev == 0) अणु
		/* apply fixes in PHY AFE */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 0x00ff);

		/* apply RDAC termination workaround */
		gm_phy_ग_लिखो(hw, port, 24, 0x2800);
		gm_phy_ग_लिखो(hw, port, 23, 0x2001);

		/* set page रेजिस्टर back to 0 */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 0);
	पूर्ण अन्यथा अगर (hw->chip_id != CHIP_ID_YUKON_EX &&
		   hw->chip_id < CHIP_ID_YUKON_SUPR) अणु
		/* no effect on Yukon-XL */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_LED_CTRL, ledctrl);

		अगर (!(sky2->flags & SKY2_FLAG_AUTO_SPEED) ||
		    sky2->speed == SPEED_100) अणु
			/* turn on 100 Mbps LED (LED_LINK100) */
			leकरोver |= PHY_M_LED_MO_100(MO_LED_ON);
		पूर्ण

		अगर (leकरोver)
			gm_phy_ग_लिखो(hw, port, PHY_MARV_LED_OVER, leकरोver);

	पूर्ण अन्यथा अगर (hw->chip_id == CHIP_ID_YUKON_PRM &&
		   (sky2_पढ़ो8(hw, B2_MAC_CFG) & 0xf) == 0x7) अणु
		पूर्णांक i;
		/* This a phy रेजिस्टर setup workaround copied from venकरोr driver. */
		अटल स्थिर काष्ठा अणु
			u16 reg, val;
		पूर्ण eee_afe[] = अणु
			अणु 0x156, 0x58ce पूर्ण,
			अणु 0x153, 0x99eb पूर्ण,
			अणु 0x141, 0x8064 पूर्ण,
			/* अणु 0x155, 0x130b पूर्ण,*/
			अणु 0x000, 0x0000 पूर्ण,
			अणु 0x151, 0x8433 पूर्ण,
			अणु 0x14b, 0x8c44 पूर्ण,
			अणु 0x14c, 0x0f90 पूर्ण,
			अणु 0x14f, 0x39aa पूर्ण,
			/* अणु 0x154, 0x2f39 पूर्ण,*/
			अणु 0x14d, 0xba33 पूर्ण,
			अणु 0x144, 0x0048 पूर्ण,
			अणु 0x152, 0x2010 पूर्ण,
			/* अणु 0x158, 0x1223 पूर्ण,*/
			अणु 0x140, 0x4444 पूर्ण,
			अणु 0x154, 0x2f3b पूर्ण,
			अणु 0x158, 0xb203 पूर्ण,
			अणु 0x157, 0x2029 पूर्ण,
		पूर्ण;

		/* Start Workaround क्रम OptimaEEE Rev.Z0 */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 0x00fb);

		gm_phy_ग_लिखो(hw, port,  1, 0x4099);
		gm_phy_ग_लिखो(hw, port,  3, 0x1120);
		gm_phy_ग_लिखो(hw, port, 11, 0x113c);
		gm_phy_ग_लिखो(hw, port, 14, 0x8100);
		gm_phy_ग_लिखो(hw, port, 15, 0x112a);
		gm_phy_ग_लिखो(hw, port, 17, 0x1008);

		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 0x00fc);
		gm_phy_ग_लिखो(hw, port,  1, 0x20b0);

		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 0x00ff);

		क्रम (i = 0; i < ARRAY_SIZE(eee_afe); i++) अणु
			/* apply AFE settings */
			gm_phy_ग_लिखो(hw, port, 17, eee_afe[i].val);
			gm_phy_ग_लिखो(hw, port, 16, eee_afe[i].reg | 1u<<13);
		पूर्ण

		/* End Workaround क्रम OptimaEEE */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 0);

		/* Enable 10Base-Te (EEE) */
		अगर (hw->chip_id >= CHIP_ID_YUKON_PRM) अणु
			reg = gm_phy_पढ़ो(hw, port, PHY_MARV_EXT_CTRL);
			gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_CTRL,
				     reg | PHY_M_10B_TE_ENABLE);
		पूर्ण
	पूर्ण

	/* Enable phy पूर्णांकerrupt on स्वतः-negotiation complete (or link up) */
	अगर (sky2->flags & SKY2_FLAG_AUTO_SPEED)
		gm_phy_ग_लिखो(hw, port, PHY_MARV_INT_MASK, PHY_M_IS_AN_COMPL);
	अन्यथा
		gm_phy_ग_लिखो(hw, port, PHY_MARV_INT_MASK, PHY_M_DEF_MSK);
पूर्ण

अटल स्थिर u32 phy_घातer[] = अणु PCI_Y2_PHY1_POWD, PCI_Y2_PHY2_POWD पूर्ण;
अटल स्थिर u32 coma_mode[] = अणु PCI_Y2_PHY1_COMA, PCI_Y2_PHY2_COMA पूर्ण;

अटल व्योम sky2_phy_घातer_up(काष्ठा sky2_hw *hw, अचिन्हित port)
अणु
	u32 reg1;

	sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
	reg1 = sky2_pci_पढ़ो32(hw, PCI_DEV_REG1);
	reg1 &= ~phy_घातer[port];

	अगर (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev > CHIP_REV_YU_XL_A1)
		reg1 |= coma_mode[port];

	sky2_pci_ग_लिखो32(hw, PCI_DEV_REG1, reg1);
	sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	sky2_pci_पढ़ो32(hw, PCI_DEV_REG1);

	अगर (hw->chip_id == CHIP_ID_YUKON_FE)
		gm_phy_ग_लिखो(hw, port, PHY_MARV_CTRL, PHY_CT_ANE);
	अन्यथा अगर (hw->flags & SKY2_HW_ADV_POWER_CTL)
		sky2_ग_लिखो8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_CLR);
पूर्ण

अटल व्योम sky2_phy_घातer_करोwn(काष्ठा sky2_hw *hw, अचिन्हित port)
अणु
	u32 reg1;
	u16 ctrl;

	/* release GPHY Control reset */
	sky2_ग_लिखो8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_CLR);

	/* release GMAC reset */
	sky2_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_RST_CLR);

	अगर (hw->flags & SKY2_HW_NEWER_PHY) अणु
		/* select page 2 to access MAC control रेजिस्टर */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 2);

		ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_PHY_CTRL);
		/* allow GMII Power Down */
		ctrl &= ~PHY_M_MAC_GMIF_PUP;
		gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL, ctrl);

		/* set page रेजिस्टर back to 0 */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 0);
	पूर्ण

	/* setup General Purpose Control Register */
	gma_ग_लिखो16(hw, port, GM_GP_CTRL,
		    GM_GPCR_FL_PASS | GM_GPCR_SPEED_100 |
		    GM_GPCR_AU_DUP_DIS | GM_GPCR_AU_FCT_DIS |
		    GM_GPCR_AU_SPD_DIS);

	अगर (hw->chip_id != CHIP_ID_YUKON_EC) अणु
		अगर (hw->chip_id == CHIP_ID_YUKON_EC_U) अणु
			/* select page 2 to access MAC control रेजिस्टर */
			gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 2);

			ctrl = gm_phy_पढ़ो(hw, port, PHY_MARV_PHY_CTRL);
			/* enable Power Down */
			ctrl |= PHY_M_PC_POW_D_ENA;
			gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL, ctrl);

			/* set page रेजिस्टर back to 0 */
			gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 0);
		पूर्ण

		/* set IEEE compatible Power Down Mode (dev. #4.99) */
		gm_phy_ग_लिखो(hw, port, PHY_MARV_CTRL, PHY_CT_PDOWN);
	पूर्ण

	sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
	reg1 = sky2_pci_पढ़ो32(hw, PCI_DEV_REG1);
	reg1 |= phy_घातer[port];		/* set PHY to PowerDown/COMA Mode */
	sky2_pci_ग_लिखो32(hw, PCI_DEV_REG1, reg1);
	sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
पूर्ण

/* configure IPG according to used link speed */
अटल व्योम sky2_set_ipg(काष्ठा sky2_port *sky2)
अणु
	u16 reg;

	reg = gma_पढ़ो16(sky2->hw, sky2->port, GM_SERIAL_MODE);
	reg &= ~GM_SMOD_IPG_MSK;
	अगर (sky2->speed > SPEED_100)
		reg |= IPG_DATA_VAL(IPG_DATA_DEF_1000);
	अन्यथा
		reg |= IPG_DATA_VAL(IPG_DATA_DEF_10_100);
	gma_ग_लिखो16(sky2->hw, sky2->port, GM_SERIAL_MODE, reg);
पूर्ण

/* Enable Rx/Tx */
अटल व्योम sky2_enable_rx_tx(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	u16 reg;

	reg = gma_पढ़ो16(hw, port, GM_GP_CTRL);
	reg |= GM_GPCR_RX_ENA | GM_GPCR_TX_ENA;
	gma_ग_लिखो16(hw, port, GM_GP_CTRL, reg);
पूर्ण

/* Force a renegotiation */
अटल व्योम sky2_phy_reinit(काष्ठा sky2_port *sky2)
अणु
	spin_lock_bh(&sky2->phy_lock);
	sky2_phy_init(sky2->hw, sky2->port);
	sky2_enable_rx_tx(sky2);
	spin_unlock_bh(&sky2->phy_lock);
पूर्ण

/* Put device in state to listen क्रम Wake On Lan */
अटल व्योम sky2_wol_init(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	क्रमागत flow_control save_mode;
	u16 ctrl;

	/* Bring hardware out of reset */
	sky2_ग_लिखो16(hw, B0_CTST, CS_RST_CLR);
	sky2_ग_लिखो16(hw, SK_REG(port, GMAC_LINK_CTRL), GMLC_RST_CLR);

	sky2_ग_लिखो8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_CLR);
	sky2_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_RST_CLR);

	/* Force to 10/100
	 * sky2_reset will re-enable on resume
	 */
	save_mode = sky2->flow_mode;
	ctrl = sky2->advertising;

	sky2->advertising &= ~(ADVERTISED_1000baseT_Half|ADVERTISED_1000baseT_Full);
	sky2->flow_mode = FC_NONE;

	spin_lock_bh(&sky2->phy_lock);
	sky2_phy_घातer_up(hw, port);
	sky2_phy_init(hw, port);
	spin_unlock_bh(&sky2->phy_lock);

	sky2->flow_mode = save_mode;
	sky2->advertising = ctrl;

	/* Set GMAC to no flow control and स्वतः update क्रम speed/duplex */
	gma_ग_लिखो16(hw, port, GM_GP_CTRL,
		    GM_GPCR_FC_TX_DIS|GM_GPCR_TX_ENA|GM_GPCR_RX_ENA|
		    GM_GPCR_DUP_FULL|GM_GPCR_FC_RX_DIS|GM_GPCR_AU_FCT_DIS);

	/* Set WOL address */
	स_नकल_toio(hw->regs + WOL_REGS(port, WOL_MAC_ADDR),
		    sky2->netdev->dev_addr, ETH_ALEN);

	/* Turn on appropriate WOL control bits */
	sky2_ग_लिखो16(hw, WOL_REGS(port, WOL_CTRL_STAT), WOL_CTL_CLEAR_RESULT);
	ctrl = 0;
	अगर (sky2->wol & WAKE_PHY)
		ctrl |= WOL_CTL_ENA_PME_ON_LINK_CHG|WOL_CTL_ENA_LINK_CHG_UNIT;
	अन्यथा
		ctrl |= WOL_CTL_DIS_PME_ON_LINK_CHG|WOL_CTL_DIS_LINK_CHG_UNIT;

	अगर (sky2->wol & WAKE_MAGIC)
		ctrl |= WOL_CTL_ENA_PME_ON_MAGIC_PKT|WOL_CTL_ENA_MAGIC_PKT_UNIT;
	अन्यथा
		ctrl |= WOL_CTL_DIS_PME_ON_MAGIC_PKT|WOL_CTL_DIS_MAGIC_PKT_UNIT;

	ctrl |= WOL_CTL_DIS_PME_ON_PATTERN|WOL_CTL_DIS_PATTERN_UNIT;
	sky2_ग_लिखो16(hw, WOL_REGS(port, WOL_CTRL_STAT), ctrl);

	/* Disable PiG firmware */
	sky2_ग_लिखो16(hw, B0_CTST, Y2_HW_WOL_OFF);

	/* Needed by some broken BIOSes, use PCI rather than PCI-e क्रम WOL */
	अगर (legacy_pme) अणु
		u32 reg1 = sky2_pci_पढ़ो32(hw, PCI_DEV_REG1);
		reg1 |= PCI_Y2_PME_LEGACY;
		sky2_pci_ग_लिखो32(hw, PCI_DEV_REG1, reg1);
	पूर्ण

	/* block receiver */
	sky2_ग_लिखो8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_SET);
	sky2_पढ़ो32(hw, B0_CTST);
पूर्ण

अटल व्योम sky2_set_tx_stfwd(काष्ठा sky2_hw *hw, अचिन्हित port)
अणु
	काष्ठा net_device *dev = hw->dev[port];

	अगर ( (hw->chip_id == CHIP_ID_YUKON_EX &&
	      hw->chip_rev != CHIP_REV_YU_EX_A0) ||
	     hw->chip_id >= CHIP_ID_YUKON_FE_P) अणु
		/* Yukon-Extreme B0 and further Extreme devices */
		sky2_ग_लिखो32(hw, SK_REG(port, TX_GMF_CTRL_T), TX_STFW_ENA);
	पूर्ण अन्यथा अगर (dev->mtu > ETH_DATA_LEN) अणु
		/* set Tx GMAC FIFO Almost Empty Threshold */
		sky2_ग_लिखो32(hw, SK_REG(port, TX_GMF_AE_THR),
			     (ECU_JUMBO_WM << 16) | ECU_AE_THR);

		sky2_ग_लिखो32(hw, SK_REG(port, TX_GMF_CTRL_T), TX_STFW_DIS);
	पूर्ण अन्यथा
		sky2_ग_लिखो32(hw, SK_REG(port, TX_GMF_CTRL_T), TX_STFW_ENA);
पूर्ण

अटल व्योम sky2_mac_init(काष्ठा sky2_hw *hw, अचिन्हित port)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(hw->dev[port]);
	u16 reg;
	u32 rx_reg;
	पूर्णांक i;
	स्थिर u8 *addr = hw->dev[port]->dev_addr;

	sky2_ग_लिखो8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_SET);
	sky2_ग_लिखो8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_CLR);

	sky2_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_RST_CLR);

	अगर (hw->chip_id == CHIP_ID_YUKON_XL &&
	    hw->chip_rev == CHIP_REV_YU_XL_A0 &&
	    port == 1) अणु
		/* WA DEV_472 -- looks like crossed wires on port 2 */
		/* clear GMAC 1 Control reset */
		sky2_ग_लिखो8(hw, SK_REG(0, GMAC_CTRL), GMC_RST_CLR);
		करो अणु
			sky2_ग_लिखो8(hw, SK_REG(1, GMAC_CTRL), GMC_RST_SET);
			sky2_ग_लिखो8(hw, SK_REG(1, GMAC_CTRL), GMC_RST_CLR);
		पूर्ण जबतक (gm_phy_पढ़ो(hw, 1, PHY_MARV_ID0) != PHY_MARV_ID0_VAL ||
			 gm_phy_पढ़ो(hw, 1, PHY_MARV_ID1) != PHY_MARV_ID1_Y2 ||
			 gm_phy_पढ़ो(hw, 1, PHY_MARV_INT_MASK) != 0);
	पूर्ण

	sky2_पढ़ो16(hw, SK_REG(port, GMAC_IRQ_SRC));

	/* Enable Transmit FIFO Underrun */
	sky2_ग_लिखो8(hw, SK_REG(port, GMAC_IRQ_MSK), GMAC_DEF_MSK);

	spin_lock_bh(&sky2->phy_lock);
	sky2_phy_घातer_up(hw, port);
	sky2_phy_init(hw, port);
	spin_unlock_bh(&sky2->phy_lock);

	/* MIB clear */
	reg = gma_पढ़ो16(hw, port, GM_PHY_ADDR);
	gma_ग_लिखो16(hw, port, GM_PHY_ADDR, reg | GM_PAR_MIB_CLR);

	क्रम (i = GM_MIB_CNT_BASE; i <= GM_MIB_CNT_END; i += 4)
		gma_पढ़ो16(hw, port, i);
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
		    TX_IPG_JAM_DATA(TX_IPG_JAM_DEF) |
		    TX_BACK_OFF_LIM(TX_BOF_LIM_DEF));

	/* serial mode रेजिस्टर */
	reg = DATA_BLIND_VAL(DATA_BLIND_DEF) |
		GM_SMOD_VLAN_ENA | IPG_DATA_VAL(IPG_DATA_DEF_1000);

	अगर (hw->dev[port]->mtu > ETH_DATA_LEN)
		reg |= GM_SMOD_JUMBO_ENA;

	अगर (hw->chip_id == CHIP_ID_YUKON_EC_U &&
	    hw->chip_rev == CHIP_REV_YU_EC_U_B1)
		reg |= GM_NEW_FLOW_CTRL;

	gma_ग_लिखो16(hw, port, GM_SERIAL_MODE, reg);

	/* भव address क्रम data */
	gma_set_addr(hw, port, GM_SRC_ADDR_2L, addr);

	/* physical address: used क्रम छोड़ो frames */
	gma_set_addr(hw, port, GM_SRC_ADDR_1L, addr);

	/* ignore counter overflows */
	gma_ग_लिखो16(hw, port, GM_TX_IRQ_MSK, 0);
	gma_ग_लिखो16(hw, port, GM_RX_IRQ_MSK, 0);
	gma_ग_लिखो16(hw, port, GM_TR_IRQ_MSK, 0);

	/* Configure Rx MAC FIFO */
	sky2_ग_लिखो8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_CLR);
	rx_reg = GMF_OPER_ON | GMF_RX_F_FL_ON;
	अगर (hw->chip_id == CHIP_ID_YUKON_EX ||
	    hw->chip_id == CHIP_ID_YUKON_FE_P)
		rx_reg |= GMF_RX_OVER_ON;

	sky2_ग_लिखो32(hw, SK_REG(port, RX_GMF_CTRL_T), rx_reg);

	अगर (hw->chip_id == CHIP_ID_YUKON_XL) अणु
		/* Hardware errata - clear flush mask */
		sky2_ग_लिखो16(hw, SK_REG(port, RX_GMF_FL_MSK), 0);
	पूर्ण अन्यथा अणु
		/* Flush Rx MAC FIFO on any flow control or error */
		sky2_ग_लिखो16(hw, SK_REG(port, RX_GMF_FL_MSK), GMR_FS_ANY_ERR);
	पूर्ण

	/* Set threshold to 0xa (64 bytes) + 1 to workaround छोड़ो bug  */
	reg = RX_GMF_FL_THR_DEF + 1;
	/* Another magic mystery workaround from sk98lin */
	अगर (hw->chip_id == CHIP_ID_YUKON_FE_P &&
	    hw->chip_rev == CHIP_REV_YU_FE2_A0)
		reg = 0x178;
	sky2_ग_लिखो16(hw, SK_REG(port, RX_GMF_FL_THR), reg);

	/* Configure Tx MAC FIFO */
	sky2_ग_लिखो8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_RST_CLR);
	sky2_ग_लिखो16(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_OPER_ON);

	/* On chips without ram buffer, छोड़ो is controlled by MAC level */
	अगर (!(hw->flags & SKY2_HW_RAM_BUFFER)) अणु
		/* Pause threshold is scaled by 8 in bytes */
		अगर (hw->chip_id == CHIP_ID_YUKON_FE_P &&
		    hw->chip_rev == CHIP_REV_YU_FE2_A0)
			reg = 1568 / 8;
		अन्यथा
			reg = 1024 / 8;
		sky2_ग_लिखो16(hw, SK_REG(port, RX_GMF_UP_THR), reg);
		sky2_ग_लिखो16(hw, SK_REG(port, RX_GMF_LP_THR), 768 / 8);

		sky2_set_tx_stfwd(hw, port);
	पूर्ण

	अगर (hw->chip_id == CHIP_ID_YUKON_FE_P &&
	    hw->chip_rev == CHIP_REV_YU_FE2_A0) अणु
		/* disable dynamic watermark */
		reg = sky2_पढ़ो16(hw, SK_REG(port, TX_GMF_EA));
		reg &= ~TX_DYN_WM_ENA;
		sky2_ग_लिखो16(hw, SK_REG(port, TX_GMF_EA), reg);
	पूर्ण
पूर्ण

/* Assign Ram Buffer allocation to queue */
अटल व्योम sky2_ramset(काष्ठा sky2_hw *hw, u16 q, u32 start, u32 space)
अणु
	u32 end;

	/* convert from K bytes to qwords used क्रम hw रेजिस्टर */
	start *= 1024/8;
	space *= 1024/8;
	end = start + space - 1;

	sky2_ग_लिखो8(hw, RB_ADDR(q, RB_CTRL), RB_RST_CLR);
	sky2_ग_लिखो32(hw, RB_ADDR(q, RB_START), start);
	sky2_ग_लिखो32(hw, RB_ADDR(q, RB_END), end);
	sky2_ग_लिखो32(hw, RB_ADDR(q, RB_WP), start);
	sky2_ग_लिखो32(hw, RB_ADDR(q, RB_RP), start);

	अगर (q == Q_R1 || q == Q_R2) अणु
		u32 tp = space - space/4;

		/* On receive queue's set the thresholds
		 * give receiver priority when > 3/4 full
		 * send छोड़ो when करोwn to 2K
		 */
		sky2_ग_लिखो32(hw, RB_ADDR(q, RB_RX_UTHP), tp);
		sky2_ग_लिखो32(hw, RB_ADDR(q, RB_RX_LTHP), space/2);

		tp = space - 8192/8;
		sky2_ग_लिखो32(hw, RB_ADDR(q, RB_RX_UTPP), tp);
		sky2_ग_लिखो32(hw, RB_ADDR(q, RB_RX_LTPP), space/4);
	पूर्ण अन्यथा अणु
		/* Enable store & क्रमward on Tx queue's because
		 * Tx FIFO is only 1K on Yukon
		 */
		sky2_ग_लिखो8(hw, RB_ADDR(q, RB_CTRL), RB_ENA_STFWD);
	पूर्ण

	sky2_ग_लिखो8(hw, RB_ADDR(q, RB_CTRL), RB_ENA_OP_MD);
	sky2_पढ़ो8(hw, RB_ADDR(q, RB_CTRL));
पूर्ण

/* Setup Bus Memory Interface */
अटल व्योम sky2_qset(काष्ठा sky2_hw *hw, u16 q)
अणु
	sky2_ग_लिखो32(hw, Q_ADDR(q, Q_CSR), BMU_CLR_RESET);
	sky2_ग_लिखो32(hw, Q_ADDR(q, Q_CSR), BMU_OPER_INIT);
	sky2_ग_लिखो32(hw, Q_ADDR(q, Q_CSR), BMU_FIFO_OP_ON);
	sky2_ग_लिखो32(hw, Q_ADDR(q, Q_WM),  BMU_WM_DEFAULT);
पूर्ण

/* Setup prefetch unit रेजिस्टरs. This is the पूर्णांकerface between
 * hardware and driver list elements
 */
अटल व्योम sky2_prefetch_init(काष्ठा sky2_hw *hw, u32 qaddr,
			       dma_addr_t addr, u32 last)
अणु
	sky2_ग_लिखो32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL), PREF_UNIT_RST_SET);
	sky2_ग_लिखो32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL), PREF_UNIT_RST_CLR);
	sky2_ग_लिखो32(hw, Y2_QADDR(qaddr, PREF_UNIT_ADDR_HI), upper_32_bits(addr));
	sky2_ग_लिखो32(hw, Y2_QADDR(qaddr, PREF_UNIT_ADDR_LO), lower_32_bits(addr));
	sky2_ग_लिखो16(hw, Y2_QADDR(qaddr, PREF_UNIT_LAST_IDX), last);
	sky2_ग_लिखो32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL), PREF_UNIT_OP_ON);

	sky2_पढ़ो32(hw, Y2_QADDR(qaddr, PREF_UNIT_CTRL));
पूर्ण

अटल अंतरभूत काष्ठा sky2_tx_le *get_tx_le(काष्ठा sky2_port *sky2, u16 *slot)
अणु
	काष्ठा sky2_tx_le *le = sky2->tx_le + *slot;

	*slot = RING_NEXT(*slot, sky2->tx_ring_size);
	le->ctrl = 0;
	वापस le;
पूर्ण

अटल व्योम tx_init(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_tx_le *le;

	sky2->tx_prod = sky2->tx_cons = 0;
	sky2->tx_tcpsum = 0;
	sky2->tx_last_mss = 0;
	netdev_reset_queue(sky2->netdev);

	le = get_tx_le(sky2, &sky2->tx_prod);
	le->addr = 0;
	le->opcode = OP_ADDR64 | HW_OWNER;
	sky2->tx_last_upper = 0;
पूर्ण

/* Update chip's next poपूर्णांकer */
अटल अंतरभूत व्योम sky2_put_idx(काष्ठा sky2_hw *hw, अचिन्हित q, u16 idx)
अणु
	/* Make sure ग_लिखो' to descriptors are complete beक्रमe we tell hardware */
	wmb();
	sky2_ग_लिखो16(hw, Y2_QADDR(q, PREF_UNIT_PUT_IDX), idx);
पूर्ण


अटल अंतरभूत काष्ठा sky2_rx_le *sky2_next_rx(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_rx_le *le = sky2->rx_le + sky2->rx_put;
	sky2->rx_put = RING_NEXT(sky2->rx_put, RX_LE_SIZE);
	le->ctrl = 0;
	वापस le;
पूर्ण

अटल अचिन्हित sky2_get_rx_threshold(काष्ठा sky2_port *sky2)
अणु
	अचिन्हित size;

	/* Space needed क्रम frame data + headers rounded up */
	size = roundup(sky2->netdev->mtu + ETH_HLEN + VLAN_HLEN, 8);

	/* Stopping poपूर्णांक क्रम hardware truncation */
	वापस (size - 8) / माप(u32);
पूर्ण

अटल अचिन्हित sky2_get_rx_data_size(काष्ठा sky2_port *sky2)
अणु
	काष्ठा rx_ring_info *re;
	अचिन्हित size;

	/* Space needed क्रम frame data + headers rounded up */
	size = roundup(sky2->netdev->mtu + ETH_HLEN + VLAN_HLEN, 8);

	sky2->rx_nfrags = size >> PAGE_SHIFT;
	BUG_ON(sky2->rx_nfrags > ARRAY_SIZE(re->frag_addr));

	/* Compute residue after pages */
	size -= sky2->rx_nfrags << PAGE_SHIFT;

	/* Optimize to handle small packets and headers */
	अगर (size < copyअवरोध)
		size = copyअवरोध;
	अगर (size < ETH_HLEN)
		size = ETH_HLEN;

	वापस size;
पूर्ण

/* Build description to hardware क्रम one receive segment */
अटल व्योम sky2_rx_add(काष्ठा sky2_port *sky2, u8 op,
			dma_addr_t map, अचिन्हित len)
अणु
	काष्ठा sky2_rx_le *le;

	अगर (माप(dma_addr_t) > माप(u32)) अणु
		le = sky2_next_rx(sky2);
		le->addr = cpu_to_le32(upper_32_bits(map));
		le->opcode = OP_ADDR64 | HW_OWNER;
	पूर्ण

	le = sky2_next_rx(sky2);
	le->addr = cpu_to_le32(lower_32_bits(map));
	le->length = cpu_to_le16(len);
	le->opcode = op | HW_OWNER;
पूर्ण

/* Build description to hardware क्रम one possibly fragmented skb */
अटल व्योम sky2_rx_submit(काष्ठा sky2_port *sky2,
			   स्थिर काष्ठा rx_ring_info *re)
अणु
	पूर्णांक i;

	sky2_rx_add(sky2, OP_PACKET, re->data_addr, sky2->rx_data_size);

	क्रम (i = 0; i < skb_shinfo(re->skb)->nr_frags; i++)
		sky2_rx_add(sky2, OP_BUFFER, re->frag_addr[i], PAGE_SIZE);
पूर्ण


अटल पूर्णांक sky2_rx_map_skb(काष्ठा pci_dev *pdev, काष्ठा rx_ring_info *re,
			    अचिन्हित size)
अणु
	काष्ठा sk_buff *skb = re->skb;
	पूर्णांक i;

	re->data_addr = dma_map_single(&pdev->dev, skb->data, size,
				       DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&pdev->dev, re->data_addr))
		जाओ mapping_error;

	dma_unmap_len_set(re, data_size, size);

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		re->frag_addr[i] = skb_frag_dma_map(&pdev->dev, frag, 0,
						    skb_frag_size(frag),
						    DMA_FROM_DEVICE);

		अगर (dma_mapping_error(&pdev->dev, re->frag_addr[i]))
			जाओ map_page_error;
	पूर्ण
	वापस 0;

map_page_error:
	जबतक (--i >= 0) अणु
		dma_unmap_page(&pdev->dev, re->frag_addr[i],
			       skb_frag_size(&skb_shinfo(skb)->frags[i]),
			       DMA_FROM_DEVICE);
	पूर्ण

	dma_unmap_single(&pdev->dev, re->data_addr,
			 dma_unmap_len(re, data_size), DMA_FROM_DEVICE);

mapping_error:
	अगर (net_ratelimit())
		dev_warn(&pdev->dev, "%s: rx mapping error\n",
			 skb->dev->name);
	वापस -EIO;
पूर्ण

अटल व्योम sky2_rx_unmap_skb(काष्ठा pci_dev *pdev, काष्ठा rx_ring_info *re)
अणु
	काष्ठा sk_buff *skb = re->skb;
	पूर्णांक i;

	dma_unmap_single(&pdev->dev, re->data_addr,
			 dma_unmap_len(re, data_size), DMA_FROM_DEVICE);

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++)
		dma_unmap_page(&pdev->dev, re->frag_addr[i],
			       skb_frag_size(&skb_shinfo(skb)->frags[i]),
			       DMA_FROM_DEVICE);
पूर्ण

/* Tell chip where to start receive checksum.
 * Actually has two checksums, but set both same to aव्योम possible byte
 * order problems.
 */
अटल व्योम rx_set_checksum(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_rx_le *le = sky2_next_rx(sky2);

	le->addr = cpu_to_le32((ETH_HLEN << 16) | ETH_HLEN);
	le->ctrl = 0;
	le->opcode = OP_TCPSTART | HW_OWNER;

	sky2_ग_लिखो32(sky2->hw,
		     Q_ADDR(rxqaddr[sky2->port], Q_CSR),
		     (sky2->netdev->features & NETIF_F_RXCSUM)
		     ? BMU_ENA_RX_CHKSUM : BMU_DIS_RX_CHKSUM);
पूर्ण

/* Enable/disable receive hash calculation (RSS) */
अटल व्योम rx_set_rss(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	पूर्णांक i, nkeys = 4;

	/* Supports IPv6 and other modes */
	अगर (hw->flags & SKY2_HW_NEW_LE) अणु
		nkeys = 10;
		sky2_ग_लिखो32(hw, SK_REG(sky2->port, RSS_CFG), HASH_ALL);
	पूर्ण

	/* Program RSS initial values */
	अगर (features & NETIF_F_RXHASH) अणु
		u32 rss_key[10];

		netdev_rss_key_fill(rss_key, माप(rss_key));
		क्रम (i = 0; i < nkeys; i++)
			sky2_ग_लिखो32(hw, SK_REG(sky2->port, RSS_KEY + i * 4),
				     rss_key[i]);

		/* Need to turn on (unकरोcumented) flag to make hashing work  */
		sky2_ग_लिखो32(hw, SK_REG(sky2->port, RX_GMF_CTRL_T),
			     RX_STFW_ENA);

		sky2_ग_लिखो32(hw, Q_ADDR(rxqaddr[sky2->port], Q_CSR),
			     BMU_ENA_RX_RSS_HASH);
	पूर्ण अन्यथा
		sky2_ग_लिखो32(hw, Q_ADDR(rxqaddr[sky2->port], Q_CSR),
			     BMU_DIS_RX_RSS_HASH);
पूर्ण

/*
 * The RX Stop command will not work क्रम Yukon-2 अगर the BMU करोes not
 * reach the end of packet and since we can't make sure that we have
 * incoming data, we must reset the BMU जबतक it is not करोing a DMA
 * transfer. Since it is possible that the RX path is still active,
 * the RX RAM buffer will be stopped first, so any possible incoming
 * data will not trigger a DMA. After the RAM buffer is stopped, the
 * BMU is polled until any DMA in progress is ended and only then it
 * will be reset.
 */
अटल व्योम sky2_rx_stop(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित rxq = rxqaddr[sky2->port];
	पूर्णांक i;

	/* disable the RAM Buffer receive queue */
	sky2_ग_लिखो8(hw, RB_ADDR(rxq, RB_CTRL), RB_DIS_OP_MD);

	क्रम (i = 0; i < 0xffff; i++)
		अगर (sky2_पढ़ो8(hw, RB_ADDR(rxq, Q_RSL))
		    == sky2_पढ़ो8(hw, RB_ADDR(rxq, Q_RL)))
			जाओ stopped;

	netdev_warn(sky2->netdev, "receiver stop failed\n");
stopped:
	sky2_ग_लिखो32(hw, Q_ADDR(rxq, Q_CSR), BMU_RST_SET | BMU_FIFO_RST);

	/* reset the Rx prefetch unit */
	sky2_ग_लिखो32(hw, Y2_QADDR(rxq, PREF_UNIT_CTRL), PREF_UNIT_RST_SET);
पूर्ण

/* Clean out receive buffer area, assumes receiver hardware stopped */
अटल व्योम sky2_rx_clean(काष्ठा sky2_port *sky2)
अणु
	अचिन्हित i;

	अगर (sky2->rx_le)
		स_रखो(sky2->rx_le, 0, RX_LE_BYTES);

	क्रम (i = 0; i < sky2->rx_pending; i++) अणु
		काष्ठा rx_ring_info *re = sky2->rx_ring + i;

		अगर (re->skb) अणु
			sky2_rx_unmap_skb(sky2->hw->pdev, re);
			kमुक्त_skb(re->skb);
			re->skb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/* Basic MII support */
अटल पूर्णांक sky2_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	पूर्णांक err = -EOPNOTSUPP;

	अगर (!netअगर_running(dev))
		वापस -ENODEV;	/* Phy still in reset */

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = PHY_ADDR_MARV;

		fallthrough;
	हाल SIOCGMIIREG: अणु
		u16 val = 0;

		spin_lock_bh(&sky2->phy_lock);
		err = __gm_phy_पढ़ो(hw, sky2->port, data->reg_num & 0x1f, &val);
		spin_unlock_bh(&sky2->phy_lock);

		data->val_out = val;
		अवरोध;
	पूर्ण

	हाल SIOCSMIIREG:
		spin_lock_bh(&sky2->phy_lock);
		err = gm_phy_ग_लिखो(hw, sky2->port, data->reg_num & 0x1f,
				   data->val_in);
		spin_unlock_bh(&sky2->phy_lock);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

#घोषणा SKY2_VLAN_OFFLOADS (NETIF_F_IP_CSUM | NETIF_F_SG | NETIF_F_TSO)

अटल व्योम sky2_vlan_mode(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	u16 port = sky2->port;

	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		sky2_ग_लिखो32(hw, SK_REG(port, RX_GMF_CTRL_T),
			     RX_VLAN_STRIP_ON);
	अन्यथा
		sky2_ग_लिखो32(hw, SK_REG(port, RX_GMF_CTRL_T),
			     RX_VLAN_STRIP_OFF);

	अगर (features & NETIF_F_HW_VLAN_CTAG_TX) अणु
		sky2_ग_लिखो32(hw, SK_REG(port, TX_GMF_CTRL_T),
			     TX_VLAN_TAG_ON);

		dev->vlan_features |= SKY2_VLAN_OFFLOADS;
	पूर्ण अन्यथा अणु
		sky2_ग_लिखो32(hw, SK_REG(port, TX_GMF_CTRL_T),
			     TX_VLAN_TAG_OFF);

		/* Can't करो transmit offload of vlan without hw vlan */
		dev->vlan_features &= ~SKY2_VLAN_OFFLOADS;
	पूर्ण
पूर्ण

/* Amount of required worst हाल padding in rx buffer */
अटल अंतरभूत अचिन्हित sky2_rx_pad(स्थिर काष्ठा sky2_hw *hw)
अणु
	वापस (hw->flags & SKY2_HW_RAM_BUFFER) ? 8 : 2;
पूर्ण

/*
 * Allocate an skb क्रम receiving. If the MTU is large enough
 * make the skb non-linear with a fragment list of pages.
 */
अटल काष्ठा sk_buff *sky2_rx_alloc(काष्ठा sky2_port *sky2, gfp_t gfp)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	skb = __netdev_alloc_skb(sky2->netdev,
				 sky2->rx_data_size + sky2_rx_pad(sky2->hw),
				 gfp);
	अगर (!skb)
		जाओ nomem;

	अगर (sky2->hw->flags & SKY2_HW_RAM_BUFFER) अणु
		अचिन्हित अक्षर *start;
		/*
		 * Workaround क्रम a bug in FIFO that cause hang
		 * अगर the FIFO अगर the receive buffer is not 64 byte aligned.
		 * The buffer वापसed from netdev_alloc_skb is
		 * aligned except अगर slab debugging is enabled.
		 */
		start = PTR_ALIGN(skb->data, 8);
		skb_reserve(skb, start - skb->data);
	पूर्ण अन्यथा
		skb_reserve(skb, NET_IP_ALIGN);

	क्रम (i = 0; i < sky2->rx_nfrags; i++) अणु
		काष्ठा page *page = alloc_page(gfp);

		अगर (!page)
			जाओ मुक्त_partial;
		skb_fill_page_desc(skb, i, page, 0, PAGE_SIZE);
	पूर्ण

	वापस skb;
मुक्त_partial:
	kमुक्त_skb(skb);
nomem:
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम sky2_rx_update(काष्ठा sky2_port *sky2, अचिन्हित rxq)
अणु
	sky2_put_idx(sky2->hw, rxq, sky2->rx_put);
पूर्ण

अटल पूर्णांक sky2_alloc_rx_skbs(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित i;

	sky2->rx_data_size = sky2_get_rx_data_size(sky2);

	/* Fill Rx ring */
	क्रम (i = 0; i < sky2->rx_pending; i++) अणु
		काष्ठा rx_ring_info *re = sky2->rx_ring + i;

		re->skb = sky2_rx_alloc(sky2, GFP_KERNEL);
		अगर (!re->skb)
			वापस -ENOMEM;

		अगर (sky2_rx_map_skb(hw->pdev, re, sky2->rx_data_size)) अणु
			dev_kमुक्त_skb(re->skb);
			re->skb = शून्य;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Setup receiver buffer pool.
 * Normal हाल this ends up creating one list element क्रम skb
 * in the receive ring. Worst हाल अगर using large MTU and each
 * allocation falls on a dअगरferent 64 bit region, that results
 * in 6 list elements per ring entry.
 * One element is used क्रम checksum enable/disable, and one
 * extra to aव्योम wrap.
 */
अटल व्योम sky2_rx_start(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	काष्ठा rx_ring_info *re;
	अचिन्हित rxq = rxqaddr[sky2->port];
	अचिन्हित i, thresh;

	sky2->rx_put = sky2->rx_next = 0;
	sky2_qset(hw, rxq);

	/* On PCI express lowering the watermark gives better perक्रमmance */
	अगर (pci_is_pcie(hw->pdev))
		sky2_ग_लिखो32(hw, Q_ADDR(rxq, Q_WM), BMU_WM_PEX);

	/* These chips have no ram buffer?
	 * MAC Rx RAM Read is controlled by hardware
	 */
	अगर (hw->chip_id == CHIP_ID_YUKON_EC_U &&
	    hw->chip_rev > CHIP_REV_YU_EC_U_A0)
		sky2_ग_लिखो32(hw, Q_ADDR(rxq, Q_TEST), F_M_RX_RAM_DIS);

	sky2_prefetch_init(hw, rxq, sky2->rx_le_map, RX_LE_SIZE - 1);

	अगर (!(hw->flags & SKY2_HW_NEW_LE))
		rx_set_checksum(sky2);

	अगर (!(hw->flags & SKY2_HW_RSS_BROKEN))
		rx_set_rss(sky2->netdev, sky2->netdev->features);

	/* submit Rx ring */
	क्रम (i = 0; i < sky2->rx_pending; i++) अणु
		re = sky2->rx_ring + i;
		sky2_rx_submit(sky2, re);
	पूर्ण

	/*
	 * The receiver hangs अगर it receives frames larger than the
	 * packet buffer. As a workaround, truncate oversize frames, but
	 * the रेजिस्टर is limited to 9 bits, so अगर you करो frames > 2052
	 * you better get the MTU right!
	 */
	thresh = sky2_get_rx_threshold(sky2);
	अगर (thresh > 0x1ff)
		sky2_ग_लिखो32(hw, SK_REG(sky2->port, RX_GMF_CTRL_T), RX_TRUNC_OFF);
	अन्यथा अणु
		sky2_ग_लिखो16(hw, SK_REG(sky2->port, RX_GMF_TR_THR), thresh);
		sky2_ग_लिखो32(hw, SK_REG(sky2->port, RX_GMF_CTRL_T), RX_TRUNC_ON);
	पूर्ण

	/* Tell chip about available buffers */
	sky2_rx_update(sky2, rxq);

	अगर (hw->chip_id == CHIP_ID_YUKON_EX ||
	    hw->chip_id == CHIP_ID_YUKON_SUPR) अणु
		/*
		 * Disable flushing of non ASF packets;
		 * must be करोne after initializing the BMUs;
		 * drivers without ASF support should करो this too, otherwise
		 * it may happen that they cannot run on ASF devices;
		 * remember that the MAC FIFO isn't reset during initialization.
		 */
		sky2_ग_लिखो32(hw, SK_REG(sky2->port, RX_GMF_CTRL_T), RX_MACSEC_FLUSH_OFF);
	पूर्ण

	अगर (hw->chip_id >= CHIP_ID_YUKON_SUPR) अणु
		/* Enable RX Home Address & Routing Header checksum fix */
		sky2_ग_लिखो16(hw, SK_REG(sky2->port, RX_GMF_FL_CTRL),
			     RX_IPV6_SA_MOB_ENA | RX_IPV6_DA_MOB_ENA);

		/* Enable TX Home Address & Routing Header checksum fix */
		sky2_ग_लिखो32(hw, Q_ADDR(txqaddr[sky2->port], Q_TEST),
			     TBMU_TEST_HOME_ADD_FIX_EN | TBMU_TEST_ROUTING_ADD_FIX_EN);
	पूर्ण
पूर्ण

अटल पूर्णांक sky2_alloc_buffers(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;

	/* must be घातer of 2 */
	sky2->tx_le = dma_alloc_coherent(&hw->pdev->dev,
					 sky2->tx_ring_size * माप(काष्ठा sky2_tx_le),
					 &sky2->tx_le_map, GFP_KERNEL);
	अगर (!sky2->tx_le)
		जाओ nomem;

	sky2->tx_ring = kसुस्मृति(sky2->tx_ring_size, माप(काष्ठा tx_ring_info),
				GFP_KERNEL);
	अगर (!sky2->tx_ring)
		जाओ nomem;

	sky2->rx_le = dma_alloc_coherent(&hw->pdev->dev, RX_LE_BYTES,
					 &sky2->rx_le_map, GFP_KERNEL);
	अगर (!sky2->rx_le)
		जाओ nomem;

	sky2->rx_ring = kसुस्मृति(sky2->rx_pending, माप(काष्ठा rx_ring_info),
				GFP_KERNEL);
	अगर (!sky2->rx_ring)
		जाओ nomem;

	वापस sky2_alloc_rx_skbs(sky2);
nomem:
	वापस -ENOMEM;
पूर्ण

अटल व्योम sky2_मुक्त_buffers(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;

	sky2_rx_clean(sky2);

	अगर (sky2->rx_le) अणु
		dma_मुक्त_coherent(&hw->pdev->dev, RX_LE_BYTES, sky2->rx_le,
				  sky2->rx_le_map);
		sky2->rx_le = शून्य;
	पूर्ण
	अगर (sky2->tx_le) अणु
		dma_मुक्त_coherent(&hw->pdev->dev,
				  sky2->tx_ring_size * माप(काष्ठा sky2_tx_le),
				  sky2->tx_le, sky2->tx_le_map);
		sky2->tx_le = शून्य;
	पूर्ण
	kमुक्त(sky2->tx_ring);
	kमुक्त(sky2->rx_ring);

	sky2->tx_ring = शून्य;
	sky2->rx_ring = शून्य;
पूर्ण

अटल व्योम sky2_hw_up(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	u32 ramsize;
	पूर्णांक cap;
	काष्ठा net_device *otherdev = hw->dev[sky2->port^1];

	tx_init(sky2);

	/*
 	 * On dual port PCI-X card, there is an problem where status
	 * can be received out of order due to split transactions
	 */
	अगर (otherdev && netअगर_running(otherdev) &&
 	    (cap = pci_find_capability(hw->pdev, PCI_CAP_ID_PCIX))) अणु
 		u16 cmd;

		cmd = sky2_pci_पढ़ो16(hw, cap + PCI_X_CMD);
 		cmd &= ~PCI_X_CMD_MAX_SPLIT;
 		sky2_pci_ग_लिखो16(hw, cap + PCI_X_CMD, cmd);
	पूर्ण

	sky2_mac_init(hw, port);

	/* Register is number of 4K blocks on पूर्णांकernal RAM buffer. */
	ramsize = sky2_पढ़ो8(hw, B2_E_0) * 4;
	अगर (ramsize > 0) अणु
		u32 rxspace;

		netdev_dbg(sky2->netdev, "ram buffer %dK\n", ramsize);
		अगर (ramsize < 16)
			rxspace = ramsize / 2;
		अन्यथा
			rxspace = 8 + (2*(ramsize - 16))/3;

		sky2_ramset(hw, rxqaddr[port], 0, rxspace);
		sky2_ramset(hw, txqaddr[port], rxspace, ramsize - rxspace);

		/* Make sure SyncQ is disabled */
		sky2_ग_लिखो8(hw, RB_ADDR(port == 0 ? Q_XS1 : Q_XS2, RB_CTRL),
			    RB_RST_SET);
	पूर्ण

	sky2_qset(hw, txqaddr[port]);

	/* This is copied from sk98lin 10.0.5.3; no one tells me about erratta's */
	अगर (hw->chip_id == CHIP_ID_YUKON_EX && hw->chip_rev == CHIP_REV_YU_EX_B0)
		sky2_ग_लिखो32(hw, Q_ADDR(txqaddr[port], Q_TEST), F_TX_CHK_AUTO_OFF);

	/* Set almost empty threshold */
	अगर (hw->chip_id == CHIP_ID_YUKON_EC_U &&
	    hw->chip_rev == CHIP_REV_YU_EC_U_A0)
		sky2_ग_लिखो16(hw, Q_ADDR(txqaddr[port], Q_AL), ECU_TXFF_LEV);

	sky2_prefetch_init(hw, txqaddr[port], sky2->tx_le_map,
			   sky2->tx_ring_size - 1);

	sky2_vlan_mode(sky2->netdev, sky2->netdev->features);
	netdev_update_features(sky2->netdev);

	sky2_rx_start(sky2);
पूर्ण

/* Setup device IRQ and enable napi to process */
अटल पूर्णांक sky2_setup_irq(काष्ठा sky2_hw *hw, स्थिर अक्षर *name)
अणु
	काष्ठा pci_dev *pdev = hw->pdev;
	पूर्णांक err;

	err = request_irq(pdev->irq, sky2_पूर्णांकr,
			  (hw->flags & SKY2_HW_USE_MSI) ? 0 : IRQF_SHARED,
			  name, hw);
	अगर (err)
		dev_err(&pdev->dev, "cannot assign irq %d\n", pdev->irq);
	अन्यथा अणु
		hw->flags |= SKY2_HW_IRQ_SETUP;

		napi_enable(&hw->napi);
		sky2_ग_लिखो32(hw, B0_IMSK, Y2_IS_BASE);
		sky2_पढ़ो32(hw, B0_IMSK);
	पूर्ण

	वापस err;
पूर्ण


/* Bring up network पूर्णांकerface. */
अटल पूर्णांक sky2_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	u32 imask;
	पूर्णांक err;

	netअगर_carrier_off(dev);

	err = sky2_alloc_buffers(sky2);
	अगर (err)
		जाओ err_out;

	/* With single port, IRQ is setup when device is brought up */
	अगर (hw->ports == 1 && (err = sky2_setup_irq(hw, dev->name)))
		जाओ err_out;

	sky2_hw_up(sky2);

	/* Enable पूर्णांकerrupts from phy/mac क्रम port */
	imask = sky2_पढ़ो32(hw, B0_IMSK);

	अगर (hw->chip_id == CHIP_ID_YUKON_OPT ||
	    hw->chip_id == CHIP_ID_YUKON_PRM ||
	    hw->chip_id == CHIP_ID_YUKON_OP_2)
		imask |= Y2_IS_PHY_QLNK;	/* enable PHY Quick Link */

	imask |= portirq_msk[port];
	sky2_ग_लिखो32(hw, B0_IMSK, imask);
	sky2_पढ़ो32(hw, B0_IMSK);

	netअगर_info(sky2, अगरup, dev, "enabling interface\n");

	वापस 0;

err_out:
	sky2_मुक्त_buffers(sky2);
	वापस err;
पूर्ण

/* Modular subtraction in ring */
अटल अंतरभूत पूर्णांक tx_inuse(स्थिर काष्ठा sky2_port *sky2)
अणु
	वापस (sky2->tx_prod - sky2->tx_cons) & (sky2->tx_ring_size - 1);
पूर्ण

/* Number of list elements available क्रम next tx */
अटल अंतरभूत पूर्णांक tx_avail(स्थिर काष्ठा sky2_port *sky2)
अणु
	वापस sky2->tx_pending - tx_inuse(sky2);
पूर्ण

/* Estimate of number of transmit list elements required */
अटल अचिन्हित tx_le_req(स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित count;

	count = (skb_shinfo(skb)->nr_frags + 1)
		* (माप(dma_addr_t) / माप(u32));

	अगर (skb_is_gso(skb))
		++count;
	अन्यथा अगर (माप(dma_addr_t) == माप(u32))
		++count;	/* possible vlan */

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		++count;

	वापस count;
पूर्ण

अटल व्योम sky2_tx_unmap(काष्ठा pci_dev *pdev, काष्ठा tx_ring_info *re)
अणु
	अगर (re->flags & TX_MAP_SINGLE)
		dma_unmap_single(&pdev->dev, dma_unmap_addr(re, mapaddr),
				 dma_unmap_len(re, maplen), DMA_TO_DEVICE);
	अन्यथा अगर (re->flags & TX_MAP_PAGE)
		dma_unmap_page(&pdev->dev, dma_unmap_addr(re, mapaddr),
			       dma_unmap_len(re, maplen), DMA_TO_DEVICE);
	re->flags = 0;
पूर्ण

/*
 * Put one packet in ring क्रम transmit.
 * A single packet can generate multiple list elements, and
 * the number of ring elements will probably be less than the number
 * of list elements used.
 */
अटल netdev_tx_t sky2_xmit_frame(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	काष्ठा sky2_tx_le *le = शून्य;
	काष्ठा tx_ring_info *re;
	अचिन्हित i, len;
	dma_addr_t mapping;
	u32 upper;
	u16 slot;
	u16 mss;
	u8 ctrl;

 	अगर (unlikely(tx_avail(sky2) < tx_le_req(skb)))
  		वापस NETDEV_TX_BUSY;

	len = skb_headlen(skb);
	mapping = dma_map_single(&hw->pdev->dev, skb->data, len,
				 DMA_TO_DEVICE);

	अगर (dma_mapping_error(&hw->pdev->dev, mapping))
		जाओ mapping_error;

	slot = sky2->tx_prod;
	netअगर_prपूर्णांकk(sky2, tx_queued, KERN_DEBUG, dev,
		     "tx queued, slot %u, len %d\n", slot, skb->len);

	/* Send high bits अगर needed */
	upper = upper_32_bits(mapping);
	अगर (upper != sky2->tx_last_upper) अणु
		le = get_tx_le(sky2, &slot);
		le->addr = cpu_to_le32(upper);
		sky2->tx_last_upper = upper;
		le->opcode = OP_ADDR64 | HW_OWNER;
	पूर्ण

	/* Check क्रम TCP Segmentation Offload */
	mss = skb_shinfo(skb)->gso_size;
	अगर (mss != 0) अणु

		अगर (!(hw->flags & SKY2_HW_NEW_LE))
			mss += ETH_HLEN + ip_hdrlen(skb) + tcp_hdrlen(skb);

  		अगर (mss != sky2->tx_last_mss) अणु
			le = get_tx_le(sky2, &slot);
  			le->addr = cpu_to_le32(mss);

			अगर (hw->flags & SKY2_HW_NEW_LE)
				le->opcode = OP_MSS | HW_OWNER;
			अन्यथा
				le->opcode = OP_LRGLEN | HW_OWNER;
			sky2->tx_last_mss = mss;
		पूर्ण
	पूर्ण

	ctrl = 0;

	/* Add VLAN tag, can piggyback on LRGLEN or ADDR64 */
	अगर (skb_vlan_tag_present(skb)) अणु
		अगर (!le) अणु
			le = get_tx_le(sky2, &slot);
			le->addr = 0;
			le->opcode = OP_VLAN|HW_OWNER;
		पूर्ण अन्यथा
			le->opcode |= OP_VLAN;
		le->length = cpu_to_be16(skb_vlan_tag_get(skb));
		ctrl |= INS_VLAN;
	पूर्ण

	/* Handle TCP checksum offload */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		/* On Yukon EX (some versions) encoding change. */
 		अगर (hw->flags & SKY2_HW_AUTO_TX_SUM)
 			ctrl |= CALSUM;	/* स्वतः checksum */
		अन्यथा अणु
			स्थिर अचिन्हित offset = skb_transport_offset(skb);
			u32 tcpsum;

			tcpsum = offset << 16;			/* sum start */
			tcpsum |= offset + skb->csum_offset;	/* sum ग_लिखो */

			ctrl |= CALSUM | WR_SUM | INIT_SUM | LOCK_SUM;
			अगर (ip_hdr(skb)->protocol == IPPROTO_UDP)
				ctrl |= UDPTCP;

			अगर (tcpsum != sky2->tx_tcpsum) अणु
				sky2->tx_tcpsum = tcpsum;

				le = get_tx_le(sky2, &slot);
				le->addr = cpu_to_le32(tcpsum);
				le->length = 0;	/* initial checksum value */
				le->ctrl = 1;	/* one packet */
				le->opcode = OP_TCPLISW | HW_OWNER;
			पूर्ण
		पूर्ण
	पूर्ण

	re = sky2->tx_ring + slot;
	re->flags = TX_MAP_SINGLE;
	dma_unmap_addr_set(re, mapaddr, mapping);
	dma_unmap_len_set(re, maplen, len);

	le = get_tx_le(sky2, &slot);
	le->addr = cpu_to_le32(lower_32_bits(mapping));
	le->length = cpu_to_le16(len);
	le->ctrl = ctrl;
	le->opcode = mss ? (OP_LARGESEND | HW_OWNER) : (OP_PACKET | HW_OWNER);


	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		mapping = skb_frag_dma_map(&hw->pdev->dev, frag, 0,
					   skb_frag_size(frag), DMA_TO_DEVICE);

		अगर (dma_mapping_error(&hw->pdev->dev, mapping))
			जाओ mapping_unwind;

		upper = upper_32_bits(mapping);
		अगर (upper != sky2->tx_last_upper) अणु
			le = get_tx_le(sky2, &slot);
			le->addr = cpu_to_le32(upper);
			sky2->tx_last_upper = upper;
			le->opcode = OP_ADDR64 | HW_OWNER;
		पूर्ण

		re = sky2->tx_ring + slot;
		re->flags = TX_MAP_PAGE;
		dma_unmap_addr_set(re, mapaddr, mapping);
		dma_unmap_len_set(re, maplen, skb_frag_size(frag));

		le = get_tx_le(sky2, &slot);
		le->addr = cpu_to_le32(lower_32_bits(mapping));
		le->length = cpu_to_le16(skb_frag_size(frag));
		le->ctrl = ctrl;
		le->opcode = OP_BUFFER | HW_OWNER;
	पूर्ण

	re->skb = skb;
	le->ctrl |= EOP;

	sky2->tx_prod = slot;

	अगर (tx_avail(sky2) <= MAX_SKB_TX_LE)
		netअगर_stop_queue(dev);

	netdev_sent_queue(dev, skb->len);
	sky2_put_idx(hw, txqaddr[sky2->port], sky2->tx_prod);

	वापस NETDEV_TX_OK;

mapping_unwind:
	क्रम (i = sky2->tx_prod; i != slot; i = RING_NEXT(i, sky2->tx_ring_size)) अणु
		re = sky2->tx_ring + i;

		sky2_tx_unmap(hw->pdev, re);
	पूर्ण

mapping_error:
	अगर (net_ratelimit())
		dev_warn(&hw->pdev->dev, "%s: tx mapping error\n", dev->name);
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/*
 * Free ring elements from starting at tx_cons until "done"
 *
 * NB:
 *  1. The hardware will tell us about partial completion of multi-part
 *     buffers so make sure not to मुक्त skb to early.
 *  2. This may run in parallel start_xmit because the it only
 *     looks at the tail of the queue of FIFO (tx_cons), not
 *     the head (tx_prod)
 */
अटल व्योम sky2_tx_complete(काष्ठा sky2_port *sky2, u16 करोne)
अणु
	काष्ठा net_device *dev = sky2->netdev;
	u16 idx;
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;

	BUG_ON(करोne >= sky2->tx_ring_size);

	क्रम (idx = sky2->tx_cons; idx != करोne;
	     idx = RING_NEXT(idx, sky2->tx_ring_size)) अणु
		काष्ठा tx_ring_info *re = sky2->tx_ring + idx;
		काष्ठा sk_buff *skb = re->skb;

		sky2_tx_unmap(sky2->hw->pdev, re);

		अगर (skb) अणु
			netअगर_prपूर्णांकk(sky2, tx_करोne, KERN_DEBUG, dev,
				     "tx done %u\n", idx);

			pkts_compl++;
			bytes_compl += skb->len;

			re->skb = शून्य;
			dev_kमुक्त_skb_any(skb);

			sky2->tx_next = RING_NEXT(idx, sky2->tx_ring_size);
		पूर्ण
	पूर्ण

	sky2->tx_cons = idx;
	smp_mb();

	netdev_completed_queue(dev, pkts_compl, bytes_compl);

	u64_stats_update_begin(&sky2->tx_stats.syncp);
	sky2->tx_stats.packets += pkts_compl;
	sky2->tx_stats.bytes += bytes_compl;
	u64_stats_update_end(&sky2->tx_stats.syncp);
पूर्ण

अटल व्योम sky2_tx_reset(काष्ठा sky2_hw *hw, अचिन्हित port)
अणु
	/* Disable Force Sync bit and Enable Alloc bit */
	sky2_ग_लिखो8(hw, SK_REG(port, TXA_CTRL),
		    TXA_DIS_FSYNC | TXA_DIS_ALLOC | TXA_STOP_RC);

	/* Stop Interval Timer and Limit Counter of Tx Arbiter */
	sky2_ग_लिखो32(hw, SK_REG(port, TXA_ITI_INI), 0L);
	sky2_ग_लिखो32(hw, SK_REG(port, TXA_LIM_INI), 0L);

	/* Reset the PCI FIFO of the async Tx queue */
	sky2_ग_लिखो32(hw, Q_ADDR(txqaddr[port], Q_CSR),
		     BMU_RST_SET | BMU_FIFO_RST);

	/* Reset the Tx prefetch units */
	sky2_ग_लिखो32(hw, Y2_QADDR(txqaddr[port], PREF_UNIT_CTRL),
		     PREF_UNIT_RST_SET);

	sky2_ग_लिखो32(hw, RB_ADDR(txqaddr[port], RB_CTRL), RB_RST_SET);
	sky2_ग_लिखो8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_RST_SET);

	sky2_पढ़ो32(hw, B0_CTST);
पूर्ण

अटल व्योम sky2_hw_करोwn(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	u16 ctrl;

	/* Force flow control off */
	sky2_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);

	/* Stop transmitter */
	sky2_ग_लिखो32(hw, Q_ADDR(txqaddr[port], Q_CSR), BMU_STOP);
	sky2_पढ़ो32(hw, Q_ADDR(txqaddr[port], Q_CSR));

	sky2_ग_लिखो32(hw, RB_ADDR(txqaddr[port], RB_CTRL),
		     RB_RST_SET | RB_DIS_OP_MD);

	ctrl = gma_पढ़ो16(hw, port, GM_GP_CTRL);
	ctrl &= ~(GM_GPCR_TX_ENA | GM_GPCR_RX_ENA);
	gma_ग_लिखो16(hw, port, GM_GP_CTRL, ctrl);

	sky2_ग_लिखो8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_SET);

	/* Workaround shared GMAC reset */
	अगर (!(hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev == 0 &&
	      port == 0 && hw->dev[1] && netअगर_running(hw->dev[1])))
		sky2_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_RST_SET);

	sky2_ग_लिखो8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_RST_SET);

	/* Force any delayed status पूर्णांकerrupt and NAPI */
	sky2_ग_लिखो32(hw, STAT_LEV_TIMER_CNT, 0);
	sky2_ग_लिखो32(hw, STAT_TX_TIMER_CNT, 0);
	sky2_ग_लिखो32(hw, STAT_ISR_TIMER_CNT, 0);
	sky2_पढ़ो8(hw, STAT_ISR_TIMER_CTRL);

	sky2_rx_stop(sky2);

	spin_lock_bh(&sky2->phy_lock);
	sky2_phy_घातer_करोwn(hw, port);
	spin_unlock_bh(&sky2->phy_lock);

	sky2_tx_reset(hw, port);

	/* Free any pending frames stuck in HW queue */
	sky2_tx_complete(sky2, sky2->tx_prod);
पूर्ण

/* Network shutकरोwn */
अटल पूर्णांक sky2_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;

	/* Never really got started! */
	अगर (!sky2->tx_le)
		वापस 0;

	netअगर_info(sky2, अगरकरोwn, dev, "disabling interface\n");

	अगर (hw->ports == 1) अणु
		sky2_ग_लिखो32(hw, B0_IMSK, 0);
		sky2_पढ़ो32(hw, B0_IMSK);

		napi_disable(&hw->napi);
		मुक्त_irq(hw->pdev->irq, hw);
		hw->flags &= ~SKY2_HW_IRQ_SETUP;
	पूर्ण अन्यथा अणु
		u32 imask;

		/* Disable port IRQ */
		imask  = sky2_पढ़ो32(hw, B0_IMSK);
		imask &= ~portirq_msk[sky2->port];
		sky2_ग_लिखो32(hw, B0_IMSK, imask);
		sky2_पढ़ो32(hw, B0_IMSK);

		synchronize_irq(hw->pdev->irq);
		napi_synchronize(&hw->napi);
	पूर्ण

	sky2_hw_करोwn(sky2);

	sky2_मुक्त_buffers(sky2);

	वापस 0;
पूर्ण

अटल u16 sky2_phy_speed(स्थिर काष्ठा sky2_hw *hw, u16 aux)
अणु
	अगर (hw->flags & SKY2_HW_FIBRE_PHY)
		वापस SPEED_1000;

	अगर (!(hw->flags & SKY2_HW_GIGABIT)) अणु
		अगर (aux & PHY_M_PS_SPEED_100)
			वापस SPEED_100;
		अन्यथा
			वापस SPEED_10;
	पूर्ण

	चयन (aux & PHY_M_PS_SPEED_MSK) अणु
	हाल PHY_M_PS_SPEED_1000:
		वापस SPEED_1000;
	हाल PHY_M_PS_SPEED_100:
		वापस SPEED_100;
	शेष:
		वापस SPEED_10;
	पूर्ण
पूर्ण

अटल व्योम sky2_link_up(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	अटल स्थिर अक्षर *fc_name[] = अणु
		[FC_NONE]	= "none",
		[FC_TX]		= "tx",
		[FC_RX]		= "rx",
		[FC_BOTH]	= "both",
	पूर्ण;

	sky2_set_ipg(sky2);

	sky2_enable_rx_tx(sky2);

	gm_phy_ग_लिखो(hw, port, PHY_MARV_INT_MASK, PHY_M_DEF_MSK);

	netअगर_carrier_on(sky2->netdev);

	mod_समयr(&hw->watchकरोg_समयr, jअगरfies + 1);

	/* Turn on link LED */
	sky2_ग_लिखो8(hw, SK_REG(port, LNK_LED_REG),
		    LINKLED_ON | LINKLED_BLINK_OFF | LINKLED_LINKSYNC_OFF);

	netअगर_info(sky2, link, sky2->netdev,
		   "Link is up at %d Mbps, %s duplex, flow control %s\n",
		   sky2->speed,
		   sky2->duplex == DUPLEX_FULL ? "full" : "half",
		   fc_name[sky2->flow_status]);
पूर्ण

अटल व्योम sky2_link_करोwn(काष्ठा sky2_port *sky2)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	u16 reg;

	gm_phy_ग_लिखो(hw, port, PHY_MARV_INT_MASK, 0);

	reg = gma_पढ़ो16(hw, port, GM_GP_CTRL);
	reg &= ~(GM_GPCR_RX_ENA | GM_GPCR_TX_ENA);
	gma_ग_लिखो16(hw, port, GM_GP_CTRL, reg);

	netअगर_carrier_off(sky2->netdev);

	/* Turn off link LED */
	sky2_ग_लिखो8(hw, SK_REG(port, LNK_LED_REG), LINKLED_OFF);

	netअगर_info(sky2, link, sky2->netdev, "Link is down\n");

	sky2_phy_init(hw, port);
पूर्ण

अटल क्रमागत flow_control sky2_flow(पूर्णांक rx, पूर्णांक tx)
अणु
	अगर (rx)
		वापस tx ? FC_BOTH : FC_RX;
	अन्यथा
		वापस tx ? FC_TX : FC_NONE;
पूर्ण

अटल पूर्णांक sky2_स्वतःneg_करोne(काष्ठा sky2_port *sky2, u16 aux)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	u16 advert, lpa;

	advert = gm_phy_पढ़ो(hw, port, PHY_MARV_AUNE_ADV);
	lpa = gm_phy_पढ़ो(hw, port, PHY_MARV_AUNE_LP);
	अगर (lpa & PHY_M_AN_RF) अणु
		netdev_err(sky2->netdev, "remote fault\n");
		वापस -1;
	पूर्ण

	अगर (!(aux & PHY_M_PS_SPDUP_RES)) अणु
		netdev_err(sky2->netdev, "speed/duplex mismatch\n");
		वापस -1;
	पूर्ण

	sky2->speed = sky2_phy_speed(hw, aux);
	sky2->duplex = (aux & PHY_M_PS_FULL_DUP) ? DUPLEX_FULL : DUPLEX_HALF;

	/* Since the छोड़ो result bits seem to in dअगरferent positions on
	 * dअगरferent chips. look at रेजिस्टरs.
	 */
	अगर (hw->flags & SKY2_HW_FIBRE_PHY) अणु
		/* Shअगरt क्रम bits in fiber PHY */
		advert &= ~(ADVERTISE_PAUSE_CAP|ADVERTISE_PAUSE_ASYM);
		lpa &= ~(LPA_PAUSE_CAP|LPA_PAUSE_ASYM);

		अगर (advert & ADVERTISE_1000XPAUSE)
			advert |= ADVERTISE_PAUSE_CAP;
		अगर (advert & ADVERTISE_1000XPSE_ASYM)
			advert |= ADVERTISE_PAUSE_ASYM;
		अगर (lpa & LPA_1000XPAUSE)
			lpa |= LPA_PAUSE_CAP;
		अगर (lpa & LPA_1000XPAUSE_ASYM)
			lpa |= LPA_PAUSE_ASYM;
	पूर्ण

	sky2->flow_status = FC_NONE;
	अगर (advert & ADVERTISE_PAUSE_CAP) अणु
		अगर (lpa & LPA_PAUSE_CAP)
			sky2->flow_status = FC_BOTH;
		अन्यथा अगर (advert & ADVERTISE_PAUSE_ASYM)
			sky2->flow_status = FC_RX;
	पूर्ण अन्यथा अगर (advert & ADVERTISE_PAUSE_ASYM) अणु
		अगर ((lpa & LPA_PAUSE_CAP) && (lpa & LPA_PAUSE_ASYM))
			sky2->flow_status = FC_TX;
	पूर्ण

	अगर (sky2->duplex == DUPLEX_HALF && sky2->speed < SPEED_1000 &&
	    !(hw->chip_id == CHIP_ID_YUKON_EC_U || hw->chip_id == CHIP_ID_YUKON_EX))
		sky2->flow_status = FC_NONE;

	अगर (sky2->flow_status & FC_TX)
		sky2_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_ON);
	अन्यथा
		sky2_ग_लिखो8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);

	वापस 0;
पूर्ण

/* Interrupt from PHY */
अटल व्योम sky2_phy_पूर्णांकr(काष्ठा sky2_hw *hw, अचिन्हित port)
अणु
	काष्ठा net_device *dev = hw->dev[port];
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	u16 istatus, phystat;

	अगर (!netअगर_running(dev))
		वापस;

	spin_lock(&sky2->phy_lock);
	istatus = gm_phy_पढ़ो(hw, port, PHY_MARV_INT_STAT);
	phystat = gm_phy_पढ़ो(hw, port, PHY_MARV_PHY_STAT);

	netअगर_info(sky2, पूर्णांकr, sky2->netdev, "phy interrupt status 0x%x 0x%x\n",
		   istatus, phystat);

	अगर (istatus & PHY_M_IS_AN_COMPL) अणु
		अगर (sky2_स्वतःneg_करोne(sky2, phystat) == 0 &&
		    !netअगर_carrier_ok(dev))
			sky2_link_up(sky2);
		जाओ out;
	पूर्ण

	अगर (istatus & PHY_M_IS_LSP_CHANGE)
		sky2->speed = sky2_phy_speed(hw, phystat);

	अगर (istatus & PHY_M_IS_DUP_CHANGE)
		sky2->duplex =
		    (phystat & PHY_M_PS_FULL_DUP) ? DUPLEX_FULL : DUPLEX_HALF;

	अगर (istatus & PHY_M_IS_LST_CHANGE) अणु
		अगर (phystat & PHY_M_PS_LINK_UP)
			sky2_link_up(sky2);
		अन्यथा
			sky2_link_करोwn(sky2);
	पूर्ण
out:
	spin_unlock(&sky2->phy_lock);
पूर्ण

/* Special quick link पूर्णांकerrupt (Yukon-2 Optima only) */
अटल व्योम sky2_qlink_पूर्णांकr(काष्ठा sky2_hw *hw)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(hw->dev[0]);
	u32 imask;
	u16 phy;

	/* disable irq */
	imask = sky2_पढ़ो32(hw, B0_IMSK);
	imask &= ~Y2_IS_PHY_QLNK;
	sky2_ग_लिखो32(hw, B0_IMSK, imask);

	/* reset PHY Link Detect */
	phy = sky2_pci_पढ़ो16(hw, PSM_CONFIG_REG4);
	sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
	sky2_pci_ग_लिखो16(hw, PSM_CONFIG_REG4, phy | 1);
	sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

	sky2_link_up(sky2);
पूर्ण

/* Transmit समयout is only called अगर we are running, carrier is up
 * and tx queue is full (stopped).
 */
अटल व्योम sky2_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;

	netअगर_err(sky2, समयr, dev, "tx timeout\n");

	netdev_prपूर्णांकk(KERN_DEBUG, dev, "transmit ring %u .. %u report=%u done=%u\n",
		      sky2->tx_cons, sky2->tx_prod,
		      sky2_पढ़ो16(hw, sky2->port == 0 ? STAT_TXA1_RIDX : STAT_TXA2_RIDX),
		      sky2_पढ़ो16(hw, Q_ADDR(txqaddr[sky2->port], Q_DONE)));

	/* can't restart safely under softirq */
	schedule_work(&hw->restart_work);
पूर्ण

अटल पूर्णांक sky2_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	पूर्णांक err;
	u16 ctl, mode;
	u32 imask;

	अगर (!netअगर_running(dev)) अणु
		dev->mtu = new_mtu;
		netdev_update_features(dev);
		वापस 0;
	पूर्ण

	imask = sky2_पढ़ो32(hw, B0_IMSK);
	sky2_ग_लिखो32(hw, B0_IMSK, 0);
	sky2_पढ़ो32(hw, B0_IMSK);

	netअगर_trans_update(dev);	/* prevent tx समयout */
	napi_disable(&hw->napi);
	netअगर_tx_disable(dev);

	synchronize_irq(hw->pdev->irq);

	अगर (!(hw->flags & SKY2_HW_RAM_BUFFER))
		sky2_set_tx_stfwd(hw, port);

	ctl = gma_पढ़ो16(hw, port, GM_GP_CTRL);
	gma_ग_लिखो16(hw, port, GM_GP_CTRL, ctl & ~GM_GPCR_RX_ENA);
	sky2_rx_stop(sky2);
	sky2_rx_clean(sky2);

	dev->mtu = new_mtu;
	netdev_update_features(dev);

	mode = DATA_BLIND_VAL(DATA_BLIND_DEF) |	GM_SMOD_VLAN_ENA;
	अगर (sky2->speed > SPEED_100)
		mode |= IPG_DATA_VAL(IPG_DATA_DEF_1000);
	अन्यथा
		mode |= IPG_DATA_VAL(IPG_DATA_DEF_10_100);

	अगर (dev->mtu > ETH_DATA_LEN)
		mode |= GM_SMOD_JUMBO_ENA;

	gma_ग_लिखो16(hw, port, GM_SERIAL_MODE, mode);

	sky2_ग_लिखो8(hw, RB_ADDR(rxqaddr[port], RB_CTRL), RB_ENA_OP_MD);

	err = sky2_alloc_rx_skbs(sky2);
	अगर (!err)
		sky2_rx_start(sky2);
	अन्यथा
		sky2_rx_clean(sky2);
	sky2_ग_लिखो32(hw, B0_IMSK, imask);

	sky2_पढ़ो32(hw, B0_Y2_SP_LISR);
	napi_enable(&hw->napi);

	अगर (err)
		dev_बंद(dev);
	अन्यथा अणु
		gma_ग_लिखो16(hw, port, GM_GP_CTRL, ctl);

		netअगर_wake_queue(dev);
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत bool needs_copy(स्थिर काष्ठा rx_ring_info *re,
			      अचिन्हित length)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	/* Some architectures need the IP header to be aligned */
	अगर (!IS_ALIGNED(re->data_addr + ETH_HLEN, माप(u32)))
		वापस true;
#पूर्ण_अगर
	वापस length < copyअवरोध;
पूर्ण

/* For small just reuse existing skb क्रम next receive */
अटल काष्ठा sk_buff *receive_copy(काष्ठा sky2_port *sky2,
				    स्थिर काष्ठा rx_ring_info *re,
				    अचिन्हित length)
अणु
	काष्ठा sk_buff *skb;

	skb = netdev_alloc_skb_ip_align(sky2->netdev, length);
	अगर (likely(skb)) अणु
		dma_sync_single_क्रम_cpu(&sky2->hw->pdev->dev, re->data_addr,
					length, DMA_FROM_DEVICE);
		skb_copy_from_linear_data(re->skb, skb->data, length);
		skb->ip_summed = re->skb->ip_summed;
		skb->csum = re->skb->csum;
		skb_copy_hash(skb, re->skb);
		__vlan_hwaccel_copy_tag(skb, re->skb);

		dma_sync_single_क्रम_device(&sky2->hw->pdev->dev,
					   re->data_addr, length,
					   DMA_FROM_DEVICE);
		__vlan_hwaccel_clear_tag(re->skb);
		skb_clear_hash(re->skb);
		re->skb->ip_summed = CHECKSUM_NONE;
		skb_put(skb, length);
	पूर्ण
	वापस skb;
पूर्ण

/* Adjust length of skb with fragments to match received data */
अटल व्योम skb_put_frags(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hdr_space,
			  अचिन्हित पूर्णांक length)
अणु
	पूर्णांक i, num_frags;
	अचिन्हित पूर्णांक size;

	/* put header पूर्णांकo skb */
	size = min(length, hdr_space);
	skb->tail += size;
	skb->len += size;
	length -= size;

	num_frags = skb_shinfo(skb)->nr_frags;
	क्रम (i = 0; i < num_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		अगर (length == 0) अणु
			/* करोn't need this page */
			__skb_frag_unref(frag);
			--skb_shinfo(skb)->nr_frags;
		पूर्ण अन्यथा अणु
			size = min(length, (अचिन्हित) PAGE_SIZE);

			skb_frag_size_set(frag, size);
			skb->data_len += size;
			skb->truesize += PAGE_SIZE;
			skb->len += size;
			length -= size;
		पूर्ण
	पूर्ण
पूर्ण

/* Normal packet - take skb from ring element and put in a new one  */
अटल काष्ठा sk_buff *receive_new(काष्ठा sky2_port *sky2,
				   काष्ठा rx_ring_info *re,
				   अचिन्हित पूर्णांक length)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rx_ring_info nre;
	अचिन्हित hdr_space = sky2->rx_data_size;

	nre.skb = sky2_rx_alloc(sky2, GFP_ATOMIC);
	अगर (unlikely(!nre.skb))
		जाओ nobuf;

	अगर (sky2_rx_map_skb(sky2->hw->pdev, &nre, hdr_space))
		जाओ nomap;

	skb = re->skb;
	sky2_rx_unmap_skb(sky2->hw->pdev, re);
	prefetch(skb->data);
	*re = nre;

	अगर (skb_shinfo(skb)->nr_frags)
		skb_put_frags(skb, hdr_space, length);
	अन्यथा
		skb_put(skb, length);
	वापस skb;

nomap:
	dev_kमुक्त_skb(nre.skb);
nobuf:
	वापस शून्य;
पूर्ण

/*
 * Receive one packet.
 * For larger packets, get new buffer.
 */
अटल काष्ठा sk_buff *sky2_receive(काष्ठा net_device *dev,
				    u16 length, u32 status)
अणु
 	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा rx_ring_info *re = sky2->rx_ring + sky2->rx_next;
	काष्ठा sk_buff *skb = शून्य;
	u16 count = (status & GMR_FS_LEN) >> 16;

	netअगर_prपूर्णांकk(sky2, rx_status, KERN_DEBUG, dev,
		     "rx slot %u status 0x%x len %d\n",
		     sky2->rx_next, status, length);

	sky2->rx_next = (sky2->rx_next + 1) % sky2->rx_pending;
	prefetch(sky2->rx_ring + sky2->rx_next);

	अगर (skb_vlan_tag_present(re->skb))
		count -= VLAN_HLEN;	/* Account क्रम vlan tag */

	/* This chip has hardware problems that generates bogus status.
	 * So करो only marginal checking and expect higher level protocols
	 * to handle crap frames.
	 */
	अगर (sky2->hw->chip_id == CHIP_ID_YUKON_FE_P &&
	    sky2->hw->chip_rev == CHIP_REV_YU_FE2_A0 &&
	    length != count)
		जाओ okay;

	अगर (status & GMR_FS_ANY_ERR)
		जाओ error;

	अगर (!(status & GMR_FS_RX_OK))
		जाओ resubmit;

	/* अगर length reported by DMA करोes not match PHY, packet was truncated */
	अगर (length != count)
		जाओ error;

okay:
	अगर (needs_copy(re, length))
		skb = receive_copy(sky2, re, length);
	अन्यथा
		skb = receive_new(sky2, re, length);

	dev->stats.rx_dropped += (skb == शून्य);

resubmit:
	sky2_rx_submit(sky2, re);

	वापस skb;

error:
	++dev->stats.rx_errors;

	अगर (net_ratelimit())
		netअगर_info(sky2, rx_err, dev,
			   "rx error, status 0x%x length %d\n", status, length);

	जाओ resubmit;
पूर्ण

/* Transmit complete */
अटल अंतरभूत व्योम sky2_tx_करोne(काष्ठा net_device *dev, u16 last)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	अगर (netअगर_running(dev)) अणु
		sky2_tx_complete(sky2, last);

		/* Wake unless it's detached, and called e.g. from sky2_बंद() */
		अगर (tx_avail(sky2) > MAX_SKB_TX_LE + 4)
			netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sky2_skb_rx(स्थिर काष्ठा sky2_port *sky2,
			       काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed == CHECKSUM_NONE)
		netअगर_receive_skb(skb);
	अन्यथा
		napi_gro_receive(&sky2->hw->napi, skb);
पूर्ण

अटल अंतरभूत व्योम sky2_rx_करोne(काष्ठा sky2_hw *hw, अचिन्हित port,
				अचिन्हित packets, अचिन्हित bytes)
अणु
	काष्ठा net_device *dev = hw->dev[port];
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	अगर (packets == 0)
		वापस;

	u64_stats_update_begin(&sky2->rx_stats.syncp);
	sky2->rx_stats.packets += packets;
	sky2->rx_stats.bytes += bytes;
	u64_stats_update_end(&sky2->rx_stats.syncp);

	sky2->last_rx = jअगरfies;
	sky2_rx_update(netdev_priv(dev), rxqaddr[port]);
पूर्ण

अटल व्योम sky2_rx_checksum(काष्ठा sky2_port *sky2, u32 status)
अणु
	/* If this happens then driver assuming wrong क्रमmat क्रम chip type */
	BUG_ON(sky2->hw->flags & SKY2_HW_NEW_LE);

	/* Both checksum counters are programmed to start at
	 * the same offset, so unless there is a problem they
	 * should match. This failure is an early indication that
	 * hardware receive checksumming won't work.
	 */
	अगर (likely((u16)(status >> 16) == (u16)status)) अणु
		काष्ठा sk_buff *skb = sky2->rx_ring[sky2->rx_next].skb;
		skb->ip_summed = CHECKSUM_COMPLETE;
		skb->csum = le16_to_cpu(status);
	पूर्ण अन्यथा अणु
		dev_notice(&sky2->hw->pdev->dev,
			   "%s: receive checksum problem (status = %#x)\n",
			   sky2->netdev->name, status);

		/* Disable checksum offload
		 * It will be reenabled on next nकरो_set_features, but अगर it's
		 * really broken, will get disabled again
		 */
		sky2->netdev->features &= ~NETIF_F_RXCSUM;
		sky2_ग_लिखो32(sky2->hw, Q_ADDR(rxqaddr[sky2->port], Q_CSR),
			     BMU_DIS_RX_CHKSUM);
	पूर्ण
पूर्ण

अटल व्योम sky2_rx_tag(काष्ठा sky2_port *sky2, u16 length)
अणु
	काष्ठा sk_buff *skb;

	skb = sky2->rx_ring[sky2->rx_next].skb;
	__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), be16_to_cpu(length));
पूर्ण

अटल व्योम sky2_rx_hash(काष्ठा sky2_port *sky2, u32 status)
अणु
	काष्ठा sk_buff *skb;

	skb = sky2->rx_ring[sky2->rx_next].skb;
	skb_set_hash(skb, le32_to_cpu(status), PKT_HASH_TYPE_L3);
पूर्ण

/* Process status response ring */
अटल पूर्णांक sky2_status_पूर्णांकr(काष्ठा sky2_hw *hw, पूर्णांक to_करो, u16 idx)
अणु
	पूर्णांक work_करोne = 0;
	अचिन्हित पूर्णांक total_bytes[2] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक total_packets[2] = अणु 0 पूर्ण;

	अगर (to_करो <= 0)
		वापस work_करोne;

	rmb();
	करो अणु
		काष्ठा sky2_port *sky2;
		काष्ठा sky2_status_le *le  = hw->st_le + hw->st_idx;
		अचिन्हित port;
		काष्ठा net_device *dev;
		काष्ठा sk_buff *skb;
		u32 status;
		u16 length;
		u8 opcode = le->opcode;

		अगर (!(opcode & HW_OWNER))
			अवरोध;

		hw->st_idx = RING_NEXT(hw->st_idx, hw->st_size);

		port = le->css & CSS_LINK_BIT;
		dev = hw->dev[port];
		sky2 = netdev_priv(dev);
		length = le16_to_cpu(le->length);
		status = le32_to_cpu(le->status);

		le->opcode = 0;
		चयन (opcode & ~HW_OWNER) अणु
		हाल OP_RXSTAT:
			total_packets[port]++;
			total_bytes[port] += length;

			skb = sky2_receive(dev, length, status);
			अगर (!skb)
				अवरोध;

			/* This chip reports checksum status dअगरferently */
			अगर (hw->flags & SKY2_HW_NEW_LE) अणु
				अगर ((dev->features & NETIF_F_RXCSUM) &&
				    (le->css & (CSS_ISIPV4 | CSS_ISIPV6)) &&
				    (le->css & CSS_TCPUDPCSOK))
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				अन्यथा
					skb->ip_summed = CHECKSUM_NONE;
			पूर्ण

			skb->protocol = eth_type_trans(skb, dev);
			sky2_skb_rx(sky2, skb);

			/* Stop after net poll weight */
			अगर (++work_करोne >= to_करो)
				जाओ निकास_loop;
			अवरोध;

		हाल OP_RXVLAN:
			sky2_rx_tag(sky2, length);
			अवरोध;

		हाल OP_RXCHKSVLAN:
			sky2_rx_tag(sky2, length);
			fallthrough;
		हाल OP_RXCHKS:
			अगर (likely(dev->features & NETIF_F_RXCSUM))
				sky2_rx_checksum(sky2, status);
			अवरोध;

		हाल OP_RSS_HASH:
			sky2_rx_hash(sky2, status);
			अवरोध;

		हाल OP_TXINDEXLE:
			/* TX index reports status क्रम both ports */
			sky2_tx_करोne(hw->dev[0], status & 0xfff);
			अगर (hw->dev[1])
				sky2_tx_करोne(hw->dev[1],
				     ((status >> 24) & 0xff)
					     | (u16)(length & 0xf) << 8);
			अवरोध;

		शेष:
			अगर (net_ratelimit())
				pr_warn("unknown status opcode 0x%x\n", opcode);
		पूर्ण
	पूर्ण जबतक (hw->st_idx != idx);

	/* Fully processed status ring so clear irq */
	sky2_ग_लिखो32(hw, STAT_CTRL, SC_STAT_CLR_IRQ);

निकास_loop:
	sky2_rx_करोne(hw, 0, total_packets[0], total_bytes[0]);
	sky2_rx_करोne(hw, 1, total_packets[1], total_bytes[1]);

	वापस work_करोne;
पूर्ण

अटल व्योम sky2_hw_error(काष्ठा sky2_hw *hw, अचिन्हित port, u32 status)
अणु
	काष्ठा net_device *dev = hw->dev[port];

	अगर (net_ratelimit())
		netdev_info(dev, "hw error interrupt status 0x%x\n", status);

	अगर (status & Y2_IS_PAR_RD1) अणु
		अगर (net_ratelimit())
			netdev_err(dev, "ram data read parity error\n");
		/* Clear IRQ */
		sky2_ग_लिखो16(hw, RAM_BUFFER(port, B3_RI_CTRL), RI_CLR_RD_PERR);
	पूर्ण

	अगर (status & Y2_IS_PAR_WR1) अणु
		अगर (net_ratelimit())
			netdev_err(dev, "ram data write parity error\n");

		sky2_ग_लिखो16(hw, RAM_BUFFER(port, B3_RI_CTRL), RI_CLR_WR_PERR);
	पूर्ण

	अगर (status & Y2_IS_PAR_MAC1) अणु
		अगर (net_ratelimit())
			netdev_err(dev, "MAC parity error\n");
		sky2_ग_लिखो8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_CLI_TX_PE);
	पूर्ण

	अगर (status & Y2_IS_PAR_RX1) अणु
		अगर (net_ratelimit())
			netdev_err(dev, "RX parity error\n");
		sky2_ग_लिखो32(hw, Q_ADDR(rxqaddr[port], Q_CSR), BMU_CLR_IRQ_PAR);
	पूर्ण

	अगर (status & Y2_IS_TCP_TXA1) अणु
		अगर (net_ratelimit())
			netdev_err(dev, "TCP segmentation error\n");
		sky2_ग_लिखो32(hw, Q_ADDR(txqaddr[port], Q_CSR), BMU_CLR_IRQ_TCP);
	पूर्ण
पूर्ण

अटल व्योम sky2_hw_पूर्णांकr(काष्ठा sky2_hw *hw)
अणु
	काष्ठा pci_dev *pdev = hw->pdev;
	u32 status = sky2_पढ़ो32(hw, B0_HWE_ISRC);
	u32 hwmsk = sky2_पढ़ो32(hw, B0_HWE_IMSK);

	status &= hwmsk;

	अगर (status & Y2_IS_TIST_OV)
		sky2_ग_लिखो8(hw, GMAC_TI_ST_CTRL, GMT_ST_CLR_IRQ);

	अगर (status & (Y2_IS_MST_ERR | Y2_IS_IRQ_STAT)) अणु
		u16 pci_err;

		sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		pci_err = sky2_pci_पढ़ो16(hw, PCI_STATUS);
		अगर (net_ratelimit())
			dev_err(&pdev->dev, "PCI hardware error (0x%x)\n",
			        pci_err);

		sky2_pci_ग_लिखो16(hw, PCI_STATUS,
				      pci_err | PCI_STATUS_ERROR_BITS);
		sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	पूर्ण

	अगर (status & Y2_IS_PCI_EXP) अणु
		/* PCI-Express uncorrectable Error occurred */
		u32 err;

		sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		err = sky2_पढ़ो32(hw, Y2_CFG_AER + PCI_ERR_UNCOR_STATUS);
		sky2_ग_लिखो32(hw, Y2_CFG_AER + PCI_ERR_UNCOR_STATUS,
			     0xfffffffful);
		अगर (net_ratelimit())
			dev_err(&pdev->dev, "PCI Express error (0x%x)\n", err);

		sky2_पढ़ो32(hw, Y2_CFG_AER + PCI_ERR_UNCOR_STATUS);
		sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	पूर्ण

	अगर (status & Y2_HWE_L1_MASK)
		sky2_hw_error(hw, 0, status);
	status >>= 8;
	अगर (status & Y2_HWE_L1_MASK)
		sky2_hw_error(hw, 1, status);
पूर्ण

अटल व्योम sky2_mac_पूर्णांकr(काष्ठा sky2_hw *hw, अचिन्हित port)
अणु
	काष्ठा net_device *dev = hw->dev[port];
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	u8 status = sky2_पढ़ो8(hw, SK_REG(port, GMAC_IRQ_SRC));

	netअगर_info(sky2, पूर्णांकr, dev, "mac interrupt status 0x%x\n", status);

	अगर (status & GM_IS_RX_CO_OV)
		gma_पढ़ो16(hw, port, GM_RX_IRQ_SRC);

	अगर (status & GM_IS_TX_CO_OV)
		gma_पढ़ो16(hw, port, GM_TX_IRQ_SRC);

	अगर (status & GM_IS_RX_FF_OR) अणु
		++dev->stats.rx_fअगरo_errors;
		sky2_ग_लिखो8(hw, SK_REG(port, RX_GMF_CTRL_T), GMF_CLI_RX_FO);
	पूर्ण

	अगर (status & GM_IS_TX_FF_UR) अणु
		++dev->stats.tx_fअगरo_errors;
		sky2_ग_लिखो8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_CLI_TX_FU);
	पूर्ण
पूर्ण

/* This should never happen it is a bug. */
अटल व्योम sky2_le_error(काष्ठा sky2_hw *hw, अचिन्हित port, u16 q)
अणु
	काष्ठा net_device *dev = hw->dev[port];
	u16 idx = sky2_पढ़ो16(hw, Y2_QADDR(q, PREF_UNIT_GET_IDX));

	dev_err(&hw->pdev->dev, "%s: descriptor error q=%#x get=%u put=%u\n",
		dev->name, (अचिन्हित) q, (अचिन्हित) idx,
		(अचिन्हित) sky2_पढ़ो16(hw, Y2_QADDR(q, PREF_UNIT_PUT_IDX)));

	sky2_ग_लिखो32(hw, Q_ADDR(q, Q_CSR), BMU_CLR_IRQ_CHK);
पूर्ण

अटल पूर्णांक sky2_rx_hung(काष्ठा net_device *dev)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	अचिन्हित rxq = rxqaddr[port];
	u32 mac_rp = sky2_पढ़ो32(hw, SK_REG(port, RX_GMF_RP));
	u8 mac_lev = sky2_पढ़ो8(hw, SK_REG(port, RX_GMF_RLEV));
	u8 fअगरo_rp = sky2_पढ़ो8(hw, Q_ADDR(rxq, Q_RP));
	u8 fअगरo_lev = sky2_पढ़ो8(hw, Q_ADDR(rxq, Q_RL));

	/* If idle and MAC or PCI is stuck */
	अगर (sky2->check.last == sky2->last_rx &&
	    ((mac_rp == sky2->check.mac_rp &&
	      mac_lev != 0 && mac_lev >= sky2->check.mac_lev) ||
	     /* Check अगर the PCI RX hang */
	     (fअगरo_rp == sky2->check.fअगरo_rp &&
	      fअगरo_lev != 0 && fअगरo_lev >= sky2->check.fअगरo_lev))) अणु
		netdev_prपूर्णांकk(KERN_DEBUG, dev,
			      "hung mac %d:%d fifo %d (%d:%d)\n",
			      mac_lev, mac_rp, fअगरo_lev,
			      fअगरo_rp, sky2_पढ़ो8(hw, Q_ADDR(rxq, Q_WP)));
		वापस 1;
	पूर्ण अन्यथा अणु
		sky2->check.last = sky2->last_rx;
		sky2->check.mac_rp = mac_rp;
		sky2->check.mac_lev = mac_lev;
		sky2->check.fअगरo_rp = fअगरo_rp;
		sky2->check.fअगरo_lev = fअगरo_lev;
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम sky2_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा sky2_hw *hw = from_समयr(hw, t, watchकरोg_समयr);

	/* Check क्रम lost IRQ once a second */
	अगर (sky2_पढ़ो32(hw, B0_ISRC)) अणु
		napi_schedule(&hw->napi);
	पूर्ण अन्यथा अणु
		पूर्णांक i, active = 0;

		क्रम (i = 0; i < hw->ports; i++) अणु
			काष्ठा net_device *dev = hw->dev[i];
			अगर (!netअगर_running(dev))
				जारी;
			++active;

			/* For chips with Rx FIFO, check अगर stuck */
			अगर ((hw->flags & SKY2_HW_RAM_BUFFER) &&
			     sky2_rx_hung(dev)) अणु
				netdev_info(dev, "receiver hang detected\n");
				schedule_work(&hw->restart_work);
				वापस;
			पूर्ण
		पूर्ण

		अगर (active == 0)
			वापस;
	पूर्ण

	mod_समयr(&hw->watchकरोg_समयr, round_jअगरfies(jअगरfies + HZ));
पूर्ण

/* Hardware/software error handling */
अटल व्योम sky2_err_पूर्णांकr(काष्ठा sky2_hw *hw, u32 status)
अणु
	अगर (net_ratelimit())
		dev_warn(&hw->pdev->dev, "error interrupt status=%#x\n", status);

	अगर (status & Y2_IS_HW_ERR)
		sky2_hw_पूर्णांकr(hw);

	अगर (status & Y2_IS_IRQ_MAC1)
		sky2_mac_पूर्णांकr(hw, 0);

	अगर (status & Y2_IS_IRQ_MAC2)
		sky2_mac_पूर्णांकr(hw, 1);

	अगर (status & Y2_IS_CHK_RX1)
		sky2_le_error(hw, 0, Q_R1);

	अगर (status & Y2_IS_CHK_RX2)
		sky2_le_error(hw, 1, Q_R2);

	अगर (status & Y2_IS_CHK_TXA1)
		sky2_le_error(hw, 0, Q_XA1);

	अगर (status & Y2_IS_CHK_TXA2)
		sky2_le_error(hw, 1, Q_XA2);
पूर्ण

अटल पूर्णांक sky2_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक work_limit)
अणु
	काष्ठा sky2_hw *hw = container_of(napi, काष्ठा sky2_hw, napi);
	u32 status = sky2_पढ़ो32(hw, B0_Y2_SP_EISR);
	पूर्णांक work_करोne = 0;
	u16 idx;

	अगर (unlikely(status & Y2_IS_ERROR))
		sky2_err_पूर्णांकr(hw, status);

	अगर (status & Y2_IS_IRQ_PHY1)
		sky2_phy_पूर्णांकr(hw, 0);

	अगर (status & Y2_IS_IRQ_PHY2)
		sky2_phy_पूर्णांकr(hw, 1);

	अगर (status & Y2_IS_PHY_QLNK)
		sky2_qlink_पूर्णांकr(hw);

	जबतक ((idx = sky2_पढ़ो16(hw, STAT_PUT_IDX)) != hw->st_idx) अणु
		work_करोne += sky2_status_पूर्णांकr(hw, work_limit - work_करोne, idx);

		अगर (work_करोne >= work_limit)
			जाओ करोne;
	पूर्ण

	napi_complete_करोne(napi, work_करोne);
	sky2_पढ़ो32(hw, B0_Y2_SP_LISR);
करोne:

	वापस work_करोne;
पूर्ण

अटल irqवापस_t sky2_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sky2_hw *hw = dev_id;
	u32 status;

	/* Reading this mask पूर्णांकerrupts as side effect */
	status = sky2_पढ़ो32(hw, B0_Y2_SP_ISRC2);
	अगर (status == 0 || status == ~0) अणु
		sky2_ग_लिखो32(hw, B0_Y2_SP_ICR, 2);
		वापस IRQ_NONE;
	पूर्ण

	prefetch(&hw->st_le[hw->st_idx]);

	napi_schedule(&hw->napi);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम sky2_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	napi_schedule(&sky2->hw->napi);
पूर्ण
#पूर्ण_अगर

/* Chip पूर्णांकernal frequency क्रम घड़ी calculations */
अटल u32 sky2_mhz(स्थिर काष्ठा sky2_hw *hw)
अणु
	चयन (hw->chip_id) अणु
	हाल CHIP_ID_YUKON_EC:
	हाल CHIP_ID_YUKON_EC_U:
	हाल CHIP_ID_YUKON_EX:
	हाल CHIP_ID_YUKON_SUPR:
	हाल CHIP_ID_YUKON_UL_2:
	हाल CHIP_ID_YUKON_OPT:
	हाल CHIP_ID_YUKON_PRM:
	हाल CHIP_ID_YUKON_OP_2:
		वापस 125;

	हाल CHIP_ID_YUKON_FE:
		वापस 100;

	हाल CHIP_ID_YUKON_FE_P:
		वापस 50;

	हाल CHIP_ID_YUKON_XL:
		वापस 156;

	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत u32 sky2_us2clk(स्थिर काष्ठा sky2_hw *hw, u32 us)
अणु
	वापस sky2_mhz(hw) * us;
पूर्ण

अटल अंतरभूत u32 sky2_clk2us(स्थिर काष्ठा sky2_hw *hw, u32 clk)
अणु
	वापस clk / sky2_mhz(hw);
पूर्ण


अटल पूर्णांक sky2_init(काष्ठा sky2_hw *hw)
अणु
	u8 t8;

	/* Enable all घड़ीs and check क्रम bad PCI access */
	sky2_pci_ग_लिखो32(hw, PCI_DEV_REG3, 0);

	sky2_ग_लिखो8(hw, B0_CTST, CS_RST_CLR);

	hw->chip_id = sky2_पढ़ो8(hw, B2_CHIP_ID);
	hw->chip_rev = (sky2_पढ़ो8(hw, B2_MAC_CFG) & CFG_CHIP_R_MSK) >> 4;

	चयन (hw->chip_id) अणु
	हाल CHIP_ID_YUKON_XL:
		hw->flags = SKY2_HW_GIGABIT | SKY2_HW_NEWER_PHY;
		अगर (hw->chip_rev < CHIP_REV_YU_XL_A2)
			hw->flags |= SKY2_HW_RSS_BROKEN;
		अवरोध;

	हाल CHIP_ID_YUKON_EC_U:
		hw->flags = SKY2_HW_GIGABIT
			| SKY2_HW_NEWER_PHY
			| SKY2_HW_ADV_POWER_CTL;
		अवरोध;

	हाल CHIP_ID_YUKON_EX:
		hw->flags = SKY2_HW_GIGABIT
			| SKY2_HW_NEWER_PHY
			| SKY2_HW_NEW_LE
			| SKY2_HW_ADV_POWER_CTL
			| SKY2_HW_RSS_CHKSUM;

		/* New transmit checksum */
		अगर (hw->chip_rev != CHIP_REV_YU_EX_B0)
			hw->flags |= SKY2_HW_AUTO_TX_SUM;
		अवरोध;

	हाल CHIP_ID_YUKON_EC:
		/* This rev is really old, and requires untested workarounds */
		अगर (hw->chip_rev == CHIP_REV_YU_EC_A1) अणु
			dev_err(&hw->pdev->dev, "unsupported revision Yukon-EC rev A1\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		hw->flags = SKY2_HW_GIGABIT | SKY2_HW_RSS_BROKEN;
		अवरोध;

	हाल CHIP_ID_YUKON_FE:
		hw->flags = SKY2_HW_RSS_BROKEN;
		अवरोध;

	हाल CHIP_ID_YUKON_FE_P:
		hw->flags = SKY2_HW_NEWER_PHY
			| SKY2_HW_NEW_LE
			| SKY2_HW_AUTO_TX_SUM
			| SKY2_HW_ADV_POWER_CTL;

		/* The workaround क्रम status conflicts VLAN tag detection. */
		अगर (hw->chip_rev == CHIP_REV_YU_FE2_A0)
			hw->flags |= SKY2_HW_VLAN_BROKEN | SKY2_HW_RSS_CHKSUM;
		अवरोध;

	हाल CHIP_ID_YUKON_SUPR:
		hw->flags = SKY2_HW_GIGABIT
			| SKY2_HW_NEWER_PHY
			| SKY2_HW_NEW_LE
			| SKY2_HW_AUTO_TX_SUM
			| SKY2_HW_ADV_POWER_CTL;

		अगर (hw->chip_rev == CHIP_REV_YU_SU_A0)
			hw->flags |= SKY2_HW_RSS_CHKSUM;
		अवरोध;

	हाल CHIP_ID_YUKON_UL_2:
		hw->flags = SKY2_HW_GIGABIT
			| SKY2_HW_ADV_POWER_CTL;
		अवरोध;

	हाल CHIP_ID_YUKON_OPT:
	हाल CHIP_ID_YUKON_PRM:
	हाल CHIP_ID_YUKON_OP_2:
		hw->flags = SKY2_HW_GIGABIT
			| SKY2_HW_NEW_LE
			| SKY2_HW_ADV_POWER_CTL;
		अवरोध;

	शेष:
		dev_err(&hw->pdev->dev, "unsupported chip type 0x%x\n",
			hw->chip_id);
		वापस -EOPNOTSUPP;
	पूर्ण

	hw->pmd_type = sky2_पढ़ो8(hw, B2_PMD_TYP);
	अगर (hw->pmd_type == 'L' || hw->pmd_type == 'S' || hw->pmd_type == 'P')
		hw->flags |= SKY2_HW_FIBRE_PHY;

	hw->ports = 1;
	t8 = sky2_पढ़ो8(hw, B2_Y2_HW_RES);
	अगर ((t8 & CFG_DUAL_MAC_MSK) == CFG_DUAL_MAC_MSK) अणु
		अगर (!(sky2_पढ़ो8(hw, B2_Y2_CLK_GATE) & Y2_STATUS_LNK2_INAC))
			++hw->ports;
	पूर्ण

	अगर (sky2_पढ़ो8(hw, B2_E_0))
		hw->flags |= SKY2_HW_RAM_BUFFER;

	वापस 0;
पूर्ण

अटल व्योम sky2_reset(काष्ठा sky2_hw *hw)
अणु
	काष्ठा pci_dev *pdev = hw->pdev;
	u16 status;
	पूर्णांक i;
	u32 hwe_mask = Y2_HWE_ALL_MASK;

	/* disable ASF */
	अगर (hw->chip_id == CHIP_ID_YUKON_EX
	    || hw->chip_id == CHIP_ID_YUKON_SUPR) अणु
		sky2_ग_लिखो32(hw, CPU_WDOG, 0);
		status = sky2_पढ़ो16(hw, HCU_CCSR);
		status &= ~(HCU_CCSR_AHB_RST | HCU_CCSR_CPU_RST_MODE |
			    HCU_CCSR_UC_STATE_MSK);
		/*
		 * CPU घड़ी भागider shouldn't be used because
		 * - ASF firmware may malfunction
		 * - Yukon-Supreme: Parallel FLASH करोesn't support भागided घड़ीs
		 */
		status &= ~HCU_CCSR_CPU_CLK_DIVIDE_MSK;
		sky2_ग_लिखो16(hw, HCU_CCSR, status);
		sky2_ग_लिखो32(hw, CPU_WDOG, 0);
	पूर्ण अन्यथा
		sky2_ग_लिखो8(hw, B28_Y2_ASF_STAT_CMD, Y2_ASF_RESET);
	sky2_ग_लिखो16(hw, B0_CTST, Y2_ASF_DISABLE);

	/* करो a SW reset */
	sky2_ग_लिखो8(hw, B0_CTST, CS_RST_SET);
	sky2_ग_लिखो8(hw, B0_CTST, CS_RST_CLR);

	/* allow ग_लिखोs to PCI config */
	sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);

	/* clear PCI errors, अगर any */
	status = sky2_pci_पढ़ो16(hw, PCI_STATUS);
	status |= PCI_STATUS_ERROR_BITS;
	sky2_pci_ग_लिखो16(hw, PCI_STATUS, status);

	sky2_ग_लिखो8(hw, B0_CTST, CS_MRST_CLR);

	अगर (pci_is_pcie(pdev)) अणु
		sky2_ग_लिखो32(hw, Y2_CFG_AER + PCI_ERR_UNCOR_STATUS,
			     0xfffffffful);

		/* If error bit is stuck on ignore it */
		अगर (sky2_पढ़ो32(hw, B0_HWE_ISRC) & Y2_IS_PCI_EXP)
			dev_info(&pdev->dev, "ignoring stuck error report bit\n");
		अन्यथा
			hwe_mask |= Y2_IS_PCI_EXP;
	पूर्ण

	sky2_घातer_on(hw);
	sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

	क्रम (i = 0; i < hw->ports; i++) अणु
		sky2_ग_लिखो8(hw, SK_REG(i, GMAC_LINK_CTRL), GMLC_RST_SET);
		sky2_ग_लिखो8(hw, SK_REG(i, GMAC_LINK_CTRL), GMLC_RST_CLR);

		अगर (hw->chip_id == CHIP_ID_YUKON_EX ||
		    hw->chip_id == CHIP_ID_YUKON_SUPR)
			sky2_ग_लिखो16(hw, SK_REG(i, GMAC_CTRL),
				     GMC_BYP_MACSECRX_ON | GMC_BYP_MACSECTX_ON
				     | GMC_BYP_RETR_ON);

	पूर्ण

	अगर (hw->chip_id == CHIP_ID_YUKON_SUPR && hw->chip_rev > CHIP_REV_YU_SU_B0) अणु
		/* enable MACSec घड़ी gating */
		sky2_pci_ग_लिखो32(hw, PCI_DEV_REG3, P_CLK_MACSEC_DIS);
	पूर्ण

	अगर (hw->chip_id == CHIP_ID_YUKON_OPT ||
	    hw->chip_id == CHIP_ID_YUKON_PRM ||
	    hw->chip_id == CHIP_ID_YUKON_OP_2) अणु
		u16 reg;

		अगर (hw->chip_id == CHIP_ID_YUKON_OPT && hw->chip_rev == 0) अणु
			/* disable PCI-E PHY घातer करोwn (set PHY reg 0x80, bit 7 */
			sky2_ग_लिखो32(hw, Y2_PEX_PHY_DATA, (0x80UL << 16) | (1 << 7));

			/* set PHY Link Detect Timer to 1.1 second (11x 100ms) */
			reg = 10;

			/* re-enable PEX PM in PEX PHY debug reg. 8 (clear bit 12) */
			sky2_ग_लिखो32(hw, Y2_PEX_PHY_DATA, PEX_DB_ACCESS | (0x08UL << 16));
		पूर्ण अन्यथा अणु
			/* set PHY Link Detect Timer to 0.4 second (4x 100ms) */
			reg = 3;
		पूर्ण

		reg <<= PSM_CONFIG_REG4_TIMER_PHY_LINK_DETECT_BASE;
		reg |= PSM_CONFIG_REG4_RST_PHY_LINK_DETECT;

		/* reset PHY Link Detect */
		sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		sky2_pci_ग_लिखो16(hw, PSM_CONFIG_REG4, reg);

		/* check अगर PSMv2 was running beक्रमe */
		reg = sky2_pci_पढ़ो16(hw, PSM_CONFIG_REG3);
		अगर (reg & PCI_EXP_LNKCTL_ASPMC)
			/* restore the PCIe Link Control रेजिस्टर */
			sky2_pci_ग_लिखो16(hw, pdev->pcie_cap + PCI_EXP_LNKCTL,
					 reg);

		अगर (hw->chip_id == CHIP_ID_YUKON_PRM &&
			hw->chip_rev == CHIP_REV_YU_PRM_A0) अणु
			/* change PHY Interrupt polarity to low active */
			reg = sky2_पढ़ो16(hw, GPHY_CTRL);
			sky2_ग_लिखो16(hw, GPHY_CTRL, reg | GPC_INTPOL);

			/* adapt HW क्रम low active PHY Interrupt */
			reg = sky2_पढ़ो16(hw, Y2_CFG_SPC + PCI_LDO_CTRL);
			sky2_ग_लिखो16(hw, Y2_CFG_SPC + PCI_LDO_CTRL, reg | PHY_M_UNDOC1);
		पूर्ण

		sky2_ग_लिखो8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

		/* re-enable PEX PM in PEX PHY debug reg. 8 (clear bit 12) */
		sky2_ग_लिखो32(hw, Y2_PEX_PHY_DATA, PEX_DB_ACCESS | (0x08UL << 16));
	पूर्ण

	/* Clear I2C IRQ noise */
	sky2_ग_लिखो32(hw, B2_I2C_IRQ, 1);

	/* turn off hardware समयr (unused) */
	sky2_ग_लिखो8(hw, B2_TI_CTRL, TIM_STOP);
	sky2_ग_लिखो8(hw, B2_TI_CTRL, TIM_CLR_IRQ);

	/* Turn off descriptor polling */
	sky2_ग_लिखो32(hw, B28_DPT_CTRL, DPT_STOP);

	/* Turn off receive बारtamp */
	sky2_ग_लिखो8(hw, GMAC_TI_ST_CTRL, GMT_ST_STOP);
	sky2_ग_लिखो8(hw, GMAC_TI_ST_CTRL, GMT_ST_CLR_IRQ);

	/* enable the Tx Arbiters */
	क्रम (i = 0; i < hw->ports; i++)
		sky2_ग_लिखो8(hw, SK_REG(i, TXA_CTRL), TXA_ENA_ARB);

	/* Initialize ram पूर्णांकerface */
	क्रम (i = 0; i < hw->ports; i++) अणु
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_CTRL), RI_RST_CLR);

		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_WTO_R1), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_WTO_XA1), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_WTO_XS1), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_RTO_R1), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_RTO_XA1), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_RTO_XS1), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_WTO_R2), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_WTO_XA2), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_WTO_XS2), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_RTO_R2), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_RTO_XA2), SK_RI_TO_53);
		sky2_ग_लिखो8(hw, RAM_BUFFER(i, B3_RI_RTO_XS2), SK_RI_TO_53);
	पूर्ण

	sky2_ग_लिखो32(hw, B0_HWE_IMSK, hwe_mask);

	क्रम (i = 0; i < hw->ports; i++)
		sky2_gmac_reset(hw, i);

	स_रखो(hw->st_le, 0, hw->st_size * माप(काष्ठा sky2_status_le));
	hw->st_idx = 0;

	sky2_ग_लिखो32(hw, STAT_CTRL, SC_STAT_RST_SET);
	sky2_ग_लिखो32(hw, STAT_CTRL, SC_STAT_RST_CLR);

	sky2_ग_लिखो32(hw, STAT_LIST_ADDR_LO, hw->st_dma);
	sky2_ग_लिखो32(hw, STAT_LIST_ADDR_HI, (u64) hw->st_dma >> 32);

	/* Set the list last index */
	sky2_ग_लिखो16(hw, STAT_LAST_IDX, hw->st_size - 1);

	sky2_ग_लिखो16(hw, STAT_TX_IDX_TH, 10);
	sky2_ग_लिखो8(hw, STAT_FIFO_WM, 16);

	/* set Status-FIFO ISR watermark */
	अगर (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev == 0)
		sky2_ग_लिखो8(hw, STAT_FIFO_ISR_WM, 4);
	अन्यथा
		sky2_ग_लिखो8(hw, STAT_FIFO_ISR_WM, 16);

	sky2_ग_लिखो32(hw, STAT_TX_TIMER_INI, sky2_us2clk(hw, 1000));
	sky2_ग_लिखो32(hw, STAT_ISR_TIMER_INI, sky2_us2clk(hw, 20));
	sky2_ग_लिखो32(hw, STAT_LEV_TIMER_INI, sky2_us2clk(hw, 100));

	/* enable status unit */
	sky2_ग_लिखो32(hw, STAT_CTRL, SC_STAT_OP_ON);

	sky2_ग_लिखो8(hw, STAT_TX_TIMER_CTRL, TIM_START);
	sky2_ग_लिखो8(hw, STAT_LEV_TIMER_CTRL, TIM_START);
	sky2_ग_लिखो8(hw, STAT_ISR_TIMER_CTRL, TIM_START);
पूर्ण

/* Take device करोwn (offline).
 * Equivalent to करोing dev_stop() but this करोes not
 * inक्रमm upper layers of the transition.
 */
अटल व्योम sky2_detach(काष्ठा net_device *dev)
अणु
	अगर (netअगर_running(dev)) अणु
		netअगर_tx_lock(dev);
		netअगर_device_detach(dev);	/* stop txq */
		netअगर_tx_unlock(dev);
		sky2_बंद(dev);
	पूर्ण
पूर्ण

/* Bring device back after करोing sky2_detach */
अटल पूर्णांक sky2_reattach(काष्ठा net_device *dev)
अणु
	पूर्णांक err = 0;

	अगर (netअगर_running(dev)) अणु
		err = sky2_खोलो(dev);
		अगर (err) अणु
			netdev_info(dev, "could not restart %d\n", err);
			dev_बंद(dev);
		पूर्ण अन्यथा अणु
			netअगर_device_attach(dev);
			sky2_set_multicast(dev);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम sky2_all_करोwn(काष्ठा sky2_hw *hw)
अणु
	पूर्णांक i;

	अगर (hw->flags & SKY2_HW_IRQ_SETUP) अणु
		sky2_ग_लिखो32(hw, B0_IMSK, 0);
		sky2_पढ़ो32(hw, B0_IMSK);

		synchronize_irq(hw->pdev->irq);
		napi_disable(&hw->napi);
	पूर्ण

	क्रम (i = 0; i < hw->ports; i++) अणु
		काष्ठा net_device *dev = hw->dev[i];
		काष्ठा sky2_port *sky2 = netdev_priv(dev);

		अगर (!netअगर_running(dev))
			जारी;

		netअगर_carrier_off(dev);
		netअगर_tx_disable(dev);
		sky2_hw_करोwn(sky2);
	पूर्ण
पूर्ण

अटल व्योम sky2_all_up(काष्ठा sky2_hw *hw)
अणु
	u32 imask = Y2_IS_BASE;
	पूर्णांक i;

	क्रम (i = 0; i < hw->ports; i++) अणु
		काष्ठा net_device *dev = hw->dev[i];
		काष्ठा sky2_port *sky2 = netdev_priv(dev);

		अगर (!netअगर_running(dev))
			जारी;

		sky2_hw_up(sky2);
		sky2_set_multicast(dev);
		imask |= portirq_msk[i];
		netअगर_wake_queue(dev);
	पूर्ण

	अगर (hw->flags & SKY2_HW_IRQ_SETUP) अणु
		sky2_ग_लिखो32(hw, B0_IMSK, imask);
		sky2_पढ़ो32(hw, B0_IMSK);
		sky2_पढ़ो32(hw, B0_Y2_SP_LISR);
		napi_enable(&hw->napi);
	पूर्ण
पूर्ण

अटल व्योम sky2_restart(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sky2_hw *hw = container_of(work, काष्ठा sky2_hw, restart_work);

	rtnl_lock();

	sky2_all_करोwn(hw);
	sky2_reset(hw);
	sky2_all_up(hw);

	rtnl_unlock();
पूर्ण

अटल अंतरभूत u8 sky2_wol_supported(स्थिर काष्ठा sky2_hw *hw)
अणु
	वापस sky2_is_copper(hw) ? (WAKE_PHY | WAKE_MAGIC) : 0;
पूर्ण

अटल व्योम sky2_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	स्थिर काष्ठा sky2_port *sky2 = netdev_priv(dev);

	wol->supported = sky2_wol_supported(sky2->hw);
	wol->wolopts = sky2->wol;
पूर्ण

अटल पूर्णांक sky2_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	bool enable_wakeup = false;
	पूर्णांक i;

	अगर ((wol->wolopts & ~sky2_wol_supported(sky2->hw)) ||
	    !device_can_wakeup(&hw->pdev->dev))
		वापस -EOPNOTSUPP;

	sky2->wol = wol->wolopts;

	क्रम (i = 0; i < hw->ports; i++) अणु
		काष्ठा net_device *dev = hw->dev[i];
		काष्ठा sky2_port *sky2 = netdev_priv(dev);

		अगर (sky2->wol)
			enable_wakeup = true;
	पूर्ण
	device_set_wakeup_enable(&hw->pdev->dev, enable_wakeup);

	वापस 0;
पूर्ण

अटल u32 sky2_supported_modes(स्थिर काष्ठा sky2_hw *hw)
अणु
	अगर (sky2_is_copper(hw)) अणु
		u32 modes = SUPPORTED_10baseT_Half
			| SUPPORTED_10baseT_Full
			| SUPPORTED_100baseT_Half
			| SUPPORTED_100baseT_Full;

		अगर (hw->flags & SKY2_HW_GIGABIT)
			modes |= SUPPORTED_1000baseT_Half
				| SUPPORTED_1000baseT_Full;
		वापस modes;
	पूर्ण अन्यथा
		वापस SUPPORTED_1000baseT_Half
			| SUPPORTED_1000baseT_Full;
पूर्ण

अटल पूर्णांक sky2_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	u32 supported, advertising;

	supported = sky2_supported_modes(hw);
	cmd->base.phy_address = PHY_ADDR_MARV;
	अगर (sky2_is_copper(hw)) अणु
		cmd->base.port = PORT_TP;
		cmd->base.speed = sky2->speed;
		supported |=  SUPPORTED_Autoneg | SUPPORTED_TP;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_1000;
		cmd->base.port = PORT_FIBRE;
		supported |=  SUPPORTED_Autoneg | SUPPORTED_FIBRE;
	पूर्ण

	advertising = sky2->advertising;
	cmd->base.स्वतःneg = (sky2->flags & SKY2_FLAG_AUTO_SPEED)
		? AUTONEG_ENABLE : AUTONEG_DISABLE;
	cmd->base.duplex = sky2->duplex;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक sky2_set_link_ksettings(काष्ठा net_device *dev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	स्थिर काष्ठा sky2_hw *hw = sky2->hw;
	u32 supported = sky2_supported_modes(hw);
	u32 new_advertising;

	ethtool_convert_link_mode_to_legacy_u32(&new_advertising,
						cmd->link_modes.advertising);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (new_advertising & ~supported)
			वापस -EINVAL;

		अगर (sky2_is_copper(hw))
			sky2->advertising = new_advertising |
					    ADVERTISED_TP |
					    ADVERTISED_Autoneg;
		अन्यथा
			sky2->advertising = new_advertising |
					    ADVERTISED_FIBRE |
					    ADVERTISED_Autoneg;

		sky2->flags |= SKY2_FLAG_AUTO_SPEED;
		sky2->duplex = -1;
		sky2->speed = -1;
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

		sky2->speed = speed;
		sky2->duplex = cmd->base.duplex;
		sky2->flags &= ~SKY2_FLAG_AUTO_SPEED;
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		sky2_phy_reinit(sky2);
		sky2_set_multicast(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sky2_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(sky2->hw->pdev),
		माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा sky2_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	u16 offset;
पूर्ण sky2_stats[] = अणु
	अणु "tx_bytes",	   GM_TXO_OK_HI पूर्ण,
	अणु "rx_bytes",	   GM_RXO_OK_HI पूर्ण,
	अणु "tx_broadcast",  GM_TXF_BC_OK पूर्ण,
	अणु "rx_broadcast",  GM_RXF_BC_OK पूर्ण,
	अणु "tx_multicast",  GM_TXF_MC_OK पूर्ण,
	अणु "rx_multicast",  GM_RXF_MC_OK पूर्ण,
	अणु "tx_unicast",    GM_TXF_UC_OK पूर्ण,
	अणु "rx_unicast",    GM_RXF_UC_OK पूर्ण,
	अणु "tx_mac_pause",  GM_TXF_MPAUSE पूर्ण,
	अणु "rx_mac_pause",  GM_RXF_MPAUSE पूर्ण,
	अणु "collisions",    GM_TXF_COL पूर्ण,
	अणु "late_collision",GM_TXF_LAT_COL पूर्ण,
	अणु "aborted", 	   GM_TXF_ABO_COL पूर्ण,
	अणु "single_collisions", GM_TXF_SNG_COL पूर्ण,
	अणु "multi_collisions", GM_TXF_MUL_COL पूर्ण,

	अणु "rx_short",      GM_RXF_SHT पूर्ण,
	अणु "rx_runt", 	   GM_RXE_FRAG पूर्ण,
	अणु "rx_64_byte_packets", GM_RXF_64B पूर्ण,
	अणु "rx_65_to_127_byte_packets", GM_RXF_127B पूर्ण,
	अणु "rx_128_to_255_byte_packets", GM_RXF_255B पूर्ण,
	अणु "rx_256_to_511_byte_packets", GM_RXF_511B पूर्ण,
	अणु "rx_512_to_1023_byte_packets", GM_RXF_1023B पूर्ण,
	अणु "rx_1024_to_1518_byte_packets", GM_RXF_1518B पूर्ण,
	अणु "rx_1518_to_max_byte_packets", GM_RXF_MAX_SZ पूर्ण,
	अणु "rx_too_long",   GM_RXF_LNG_ERR पूर्ण,
	अणु "rx_fifo_overflow", GM_RXE_FIFO_OV पूर्ण,
	अणु "rx_jabber",     GM_RXF_JAB_PKT पूर्ण,
	अणु "rx_fcs_error",   GM_RXF_FCS_ERR पूर्ण,

	अणु "tx_64_byte_packets", GM_TXF_64B पूर्ण,
	अणु "tx_65_to_127_byte_packets", GM_TXF_127B पूर्ण,
	अणु "tx_128_to_255_byte_packets", GM_TXF_255B पूर्ण,
	अणु "tx_256_to_511_byte_packets", GM_TXF_511B पूर्ण,
	अणु "tx_512_to_1023_byte_packets", GM_TXF_1023B पूर्ण,
	अणु "tx_1024_to_1518_byte_packets", GM_TXF_1518B पूर्ण,
	अणु "tx_1519_to_max_byte_packets", GM_TXF_MAX_SZ पूर्ण,
	अणु "tx_fifo_underrun", GM_TXE_FIFO_UR पूर्ण,
पूर्ण;

अटल u32 sky2_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(netdev);
	वापस sky2->msg_enable;
पूर्ण

अटल पूर्णांक sky2_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	अगर (!netअगर_running(dev) || !(sky2->flags & SKY2_FLAG_AUTO_SPEED))
		वापस -EINVAL;

	sky2_phy_reinit(sky2);
	sky2_set_multicast(dev);

	वापस 0;
पूर्ण

अटल व्योम sky2_phy_stats(काष्ठा sky2_port *sky2, u64 * data, अचिन्हित count)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	पूर्णांक i;

	data[0] = get_stats64(hw, port, GM_TXO_OK_LO);
	data[1] = get_stats64(hw, port, GM_RXO_OK_LO);

	क्रम (i = 2; i < count; i++)
		data[i] = get_stats32(hw, port, sky2_stats[i].offset);
पूर्ण

अटल व्योम sky2_set_msglevel(काष्ठा net_device *netdev, u32 value)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(netdev);
	sky2->msg_enable = value;
पूर्ण

अटल पूर्णांक sky2_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(sky2_stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम sky2_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *stats, u64 * data)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	sky2_phy_stats(sky2, data, ARRAY_SIZE(sky2_stats));
पूर्ण

अटल व्योम sky2_get_strings(काष्ठा net_device *dev, u32 stringset, u8 * data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(sky2_stats); i++)
			स_नकल(data + i * ETH_GSTRING_LEN,
			       sky2_stats[i].name, ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sky2_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	स्थिर काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, ETH_ALEN);
	स_नकल_toio(hw->regs + B2_MAC_1 + port * 8,
		    dev->dev_addr, ETH_ALEN);
	स_नकल_toio(hw->regs + B2_MAC_2 + port * 8,
		    dev->dev_addr, ETH_ALEN);

	/* भव address क्रम data */
	gma_set_addr(hw, port, GM_SRC_ADDR_2L, dev->dev_addr);

	/* physical address: used क्रम छोड़ो frames */
	gma_set_addr(hw, port, GM_SRC_ADDR_1L, dev->dev_addr);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sky2_add_filter(u8 filter[8], स्थिर u8 *addr)
अणु
	u32 bit;

	bit = ether_crc(ETH_ALEN, addr) & 63;
	filter[bit >> 3] |= 1 << (bit & 7);
पूर्ण

अटल व्योम sky2_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	काष्ठा netdev_hw_addr *ha;
	u16 reg;
	u8 filter[8];
	पूर्णांक rx_छोड़ो;
	अटल स्थिर u8 छोड़ो_mc_addr[ETH_ALEN] = अणु 0x1, 0x80, 0xc2, 0x0, 0x0, 0x1 पूर्ण;

	rx_छोड़ो = (sky2->flow_status == FC_RX || sky2->flow_status == FC_BOTH);
	स_रखो(filter, 0, माप(filter));

	reg = gma_पढ़ो16(hw, port, GM_RX_CTRL);
	reg |= GM_RXCR_UCF_ENA;

	अगर (dev->flags & IFF_PROMISC)	/* promiscuous */
		reg &= ~(GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA);
	अन्यथा अगर (dev->flags & IFF_ALLMULTI)
		स_रखो(filter, 0xff, माप(filter));
	अन्यथा अगर (netdev_mc_empty(dev) && !rx_छोड़ो)
		reg &= ~GM_RXCR_MCF_ENA;
	अन्यथा अणु
		reg |= GM_RXCR_MCF_ENA;

		अगर (rx_छोड़ो)
			sky2_add_filter(filter, छोड़ो_mc_addr);

		netdev_क्रम_each_mc_addr(ha, dev)
			sky2_add_filter(filter, ha->addr);
	पूर्ण

	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H1,
		    (u16) filter[0] | ((u16) filter[1] << 8));
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H2,
		    (u16) filter[2] | ((u16) filter[3] << 8));
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H3,
		    (u16) filter[4] | ((u16) filter[5] << 8));
	gma_ग_लिखो16(hw, port, GM_MC_ADDR_H4,
		    (u16) filter[6] | ((u16) filter[7] << 8));

	gma_ग_लिखो16(hw, port, GM_RX_CTRL, reg);
पूर्ण

अटल व्योम sky2_get_stats(काष्ठा net_device *dev,
			   काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	अचिन्हित पूर्णांक start;
	u64 _bytes, _packets;

	करो अणु
		start = u64_stats_fetch_begin_irq(&sky2->rx_stats.syncp);
		_bytes = sky2->rx_stats.bytes;
		_packets = sky2->rx_stats.packets;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&sky2->rx_stats.syncp, start));

	stats->rx_packets = _packets;
	stats->rx_bytes = _bytes;

	करो अणु
		start = u64_stats_fetch_begin_irq(&sky2->tx_stats.syncp);
		_bytes = sky2->tx_stats.bytes;
		_packets = sky2->tx_stats.packets;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&sky2->tx_stats.syncp, start));

	stats->tx_packets = _packets;
	stats->tx_bytes = _bytes;

	stats->multicast = get_stats32(hw, port, GM_RXF_MC_OK)
		+ get_stats32(hw, port, GM_RXF_BC_OK);

	stats->collisions = get_stats32(hw, port, GM_TXF_COL);

	stats->rx_length_errors = get_stats32(hw, port, GM_RXF_LNG_ERR);
	stats->rx_crc_errors = get_stats32(hw, port, GM_RXF_FCS_ERR);
	stats->rx_frame_errors = get_stats32(hw, port, GM_RXF_SHT)
		+ get_stats32(hw, port, GM_RXE_FRAG);
	stats->rx_over_errors = get_stats32(hw, port, GM_RXE_FIFO_OV);

	stats->rx_dropped = dev->stats.rx_dropped;
	stats->rx_fअगरo_errors = dev->stats.rx_fअगरo_errors;
	stats->tx_fअगरo_errors = dev->stats.tx_fअगरo_errors;
पूर्ण

/* Can have one global because blinking is controlled by
 * ethtool and that is always under RTNL mutex
 */
अटल व्योम sky2_led(काष्ठा sky2_port *sky2, क्रमागत led_mode mode)
अणु
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;

	spin_lock_bh(&sky2->phy_lock);
	अगर (hw->chip_id == CHIP_ID_YUKON_EC_U ||
	    hw->chip_id == CHIP_ID_YUKON_EX ||
	    hw->chip_id == CHIP_ID_YUKON_SUPR) अणु
		u16 pg;
		pg = gm_phy_पढ़ो(hw, port, PHY_MARV_EXT_ADR);
		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, 3);

		चयन (mode) अणु
		हाल MO_LED_OFF:
			gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL,
				     PHY_M_LEDC_LOS_CTRL(8) |
				     PHY_M_LEDC_INIT_CTRL(8) |
				     PHY_M_LEDC_STA1_CTRL(8) |
				     PHY_M_LEDC_STA0_CTRL(8));
			अवरोध;
		हाल MO_LED_ON:
			gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL,
				     PHY_M_LEDC_LOS_CTRL(9) |
				     PHY_M_LEDC_INIT_CTRL(9) |
				     PHY_M_LEDC_STA1_CTRL(9) |
				     PHY_M_LEDC_STA0_CTRL(9));
			अवरोध;
		हाल MO_LED_BLINK:
			gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL,
				     PHY_M_LEDC_LOS_CTRL(0xa) |
				     PHY_M_LEDC_INIT_CTRL(0xa) |
				     PHY_M_LEDC_STA1_CTRL(0xa) |
				     PHY_M_LEDC_STA0_CTRL(0xa));
			अवरोध;
		हाल MO_LED_NORM:
			gm_phy_ग_लिखो(hw, port, PHY_MARV_PHY_CTRL,
				     PHY_M_LEDC_LOS_CTRL(1) |
				     PHY_M_LEDC_INIT_CTRL(8) |
				     PHY_M_LEDC_STA1_CTRL(7) |
				     PHY_M_LEDC_STA0_CTRL(7));
		पूर्ण

		gm_phy_ग_लिखो(hw, port, PHY_MARV_EXT_ADR, pg);
	पूर्ण अन्यथा
		gm_phy_ग_लिखो(hw, port, PHY_MARV_LED_OVER,
				     PHY_M_LED_MO_DUP(mode) |
				     PHY_M_LED_MO_10(mode) |
				     PHY_M_LED_MO_100(mode) |
				     PHY_M_LED_MO_1000(mode) |
				     PHY_M_LED_MO_RX(mode) |
				     PHY_M_LED_MO_TX(mode));

	spin_unlock_bh(&sky2->phy_lock);
पूर्ण

/* blink LED's क्रम finding board */
अटल पूर्णांक sky2_set_phys_id(काष्ठा net_device *dev,
			    क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		वापस 1;	/* cycle on/off once per second */
	हाल ETHTOOL_ID_INACTIVE:
		sky2_led(sky2, MO_LED_NORM);
		अवरोध;
	हाल ETHTOOL_ID_ON:
		sky2_led(sky2, MO_LED_ON);
		अवरोध;
	हाल ETHTOOL_ID_OFF:
		sky2_led(sky2, MO_LED_OFF);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sky2_get_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	चयन (sky2->flow_mode) अणु
	हाल FC_NONE:
		ecmd->tx_छोड़ो = ecmd->rx_छोड़ो = 0;
		अवरोध;
	हाल FC_TX:
		ecmd->tx_छोड़ो = 1, ecmd->rx_छोड़ो = 0;
		अवरोध;
	हाल FC_RX:
		ecmd->tx_छोड़ो = 0, ecmd->rx_छोड़ो = 1;
		अवरोध;
	हाल FC_BOTH:
		ecmd->tx_छोड़ो = ecmd->rx_छोड़ो = 1;
	पूर्ण

	ecmd->स्वतःneg = (sky2->flags & SKY2_FLAG_AUTO_PAUSE)
		? AUTONEG_ENABLE : AUTONEG_DISABLE;
पूर्ण

अटल पूर्णांक sky2_set_छोड़ोparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_छोड़ोparam *ecmd)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	अगर (ecmd->स्वतःneg == AUTONEG_ENABLE)
		sky2->flags |= SKY2_FLAG_AUTO_PAUSE;
	अन्यथा
		sky2->flags &= ~SKY2_FLAG_AUTO_PAUSE;

	sky2->flow_mode = sky2_flow(ecmd->rx_छोड़ो, ecmd->tx_छोड़ो);

	अगर (netअगर_running(dev))
		sky2_phy_reinit(sky2);

	वापस 0;
पूर्ण

अटल पूर्णांक sky2_get_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;

	अगर (sky2_पढ़ो8(hw, STAT_TX_TIMER_CTRL) == TIM_STOP)
		ecmd->tx_coalesce_usecs = 0;
	अन्यथा अणु
		u32 clks = sky2_पढ़ो32(hw, STAT_TX_TIMER_INI);
		ecmd->tx_coalesce_usecs = sky2_clk2us(hw, clks);
	पूर्ण
	ecmd->tx_max_coalesced_frames = sky2_पढ़ो16(hw, STAT_TX_IDX_TH);

	अगर (sky2_पढ़ो8(hw, STAT_LEV_TIMER_CTRL) == TIM_STOP)
		ecmd->rx_coalesce_usecs = 0;
	अन्यथा अणु
		u32 clks = sky2_पढ़ो32(hw, STAT_LEV_TIMER_INI);
		ecmd->rx_coalesce_usecs = sky2_clk2us(hw, clks);
	पूर्ण
	ecmd->rx_max_coalesced_frames = sky2_पढ़ो8(hw, STAT_FIFO_WM);

	अगर (sky2_पढ़ो8(hw, STAT_ISR_TIMER_CTRL) == TIM_STOP)
		ecmd->rx_coalesce_usecs_irq = 0;
	अन्यथा अणु
		u32 clks = sky2_पढ़ो32(hw, STAT_ISR_TIMER_INI);
		ecmd->rx_coalesce_usecs_irq = sky2_clk2us(hw, clks);
	पूर्ण

	ecmd->rx_max_coalesced_frames_irq = sky2_पढ़ो8(hw, STAT_FIFO_ISR_WM);

	वापस 0;
पूर्ण

/* Note: this affect both ports */
अटल पूर्णांक sky2_set_coalesce(काष्ठा net_device *dev,
			     काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	स्थिर u32 पंचांगax = sky2_clk2us(hw, 0x0ffffff);

	अगर (ecmd->tx_coalesce_usecs > पंचांगax ||
	    ecmd->rx_coalesce_usecs > पंचांगax ||
	    ecmd->rx_coalesce_usecs_irq > पंचांगax)
		वापस -EINVAL;

	अगर (ecmd->tx_max_coalesced_frames >= sky2->tx_ring_size-1)
		वापस -EINVAL;
	अगर (ecmd->rx_max_coalesced_frames > RX_MAX_PENDING)
		वापस -EINVAL;
	अगर (ecmd->rx_max_coalesced_frames_irq > RX_MAX_PENDING)
		वापस -EINVAL;

	अगर (ecmd->tx_coalesce_usecs == 0)
		sky2_ग_लिखो8(hw, STAT_TX_TIMER_CTRL, TIM_STOP);
	अन्यथा अणु
		sky2_ग_लिखो32(hw, STAT_TX_TIMER_INI,
			     sky2_us2clk(hw, ecmd->tx_coalesce_usecs));
		sky2_ग_लिखो8(hw, STAT_TX_TIMER_CTRL, TIM_START);
	पूर्ण
	sky2_ग_लिखो16(hw, STAT_TX_IDX_TH, ecmd->tx_max_coalesced_frames);

	अगर (ecmd->rx_coalesce_usecs == 0)
		sky2_ग_लिखो8(hw, STAT_LEV_TIMER_CTRL, TIM_STOP);
	अन्यथा अणु
		sky2_ग_लिखो32(hw, STAT_LEV_TIMER_INI,
			     sky2_us2clk(hw, ecmd->rx_coalesce_usecs));
		sky2_ग_लिखो8(hw, STAT_LEV_TIMER_CTRL, TIM_START);
	पूर्ण
	sky2_ग_लिखो8(hw, STAT_FIFO_WM, ecmd->rx_max_coalesced_frames);

	अगर (ecmd->rx_coalesce_usecs_irq == 0)
		sky2_ग_लिखो8(hw, STAT_ISR_TIMER_CTRL, TIM_STOP);
	अन्यथा अणु
		sky2_ग_लिखो32(hw, STAT_ISR_TIMER_INI,
			     sky2_us2clk(hw, ecmd->rx_coalesce_usecs_irq));
		sky2_ग_लिखो8(hw, STAT_ISR_TIMER_CTRL, TIM_START);
	पूर्ण
	sky2_ग_लिखो8(hw, STAT_FIFO_ISR_WM, ecmd->rx_max_coalesced_frames_irq);
	वापस 0;
पूर्ण

/*
 * Hardware is limited to min of 128 and max of 2048 क्रम ring size
 * and  rounded up to next घातer of two
 * to aव्योम भागision in modulus calculation
 */
अटल अचिन्हित दीर्घ roundup_ring_size(अचिन्हित दीर्घ pending)
अणु
	वापस max(128ul, roundup_घात_of_two(pending+1));
पूर्ण

अटल व्योम sky2_get_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	ering->rx_max_pending = RX_MAX_PENDING;
	ering->tx_max_pending = TX_MAX_PENDING;

	ering->rx_pending = sky2->rx_pending;
	ering->tx_pending = sky2->tx_pending;
पूर्ण

अटल पूर्णांक sky2_set_ringparam(काष्ठा net_device *dev,
			      काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	अगर (ering->rx_pending > RX_MAX_PENDING ||
	    ering->rx_pending < 8 ||
	    ering->tx_pending < TX_MIN_PENDING ||
	    ering->tx_pending > TX_MAX_PENDING)
		वापस -EINVAL;

	sky2_detach(dev);

	sky2->rx_pending = ering->rx_pending;
	sky2->tx_pending = ering->tx_pending;
	sky2->tx_ring_size = roundup_ring_size(sky2->tx_pending);

	वापस sky2_reattach(dev);
पूर्ण

अटल पूर्णांक sky2_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस 0x4000;
पूर्ण

अटल पूर्णांक sky2_reg_access_ok(काष्ठा sky2_hw *hw, अचिन्हित पूर्णांक b)
अणु
	/* This complicated चयन statement is to make sure and
	 * only access regions that are unreserved.
	 * Some blocks are only valid on dual port cards.
	 */
	चयन (b) अणु
	/* second port */
	हाल 5:		/* Tx Arbiter 2 */
	हाल 9:		/* RX2 */
	हाल 14 ... 15:	/* TX2 */
	हाल 17: हाल 19: /* Ram Buffer 2 */
	हाल 22 ... 23: /* Tx Ram Buffer 2 */
	हाल 25:	/* Rx MAC Fअगरo 1 */
	हाल 27:	/* Tx MAC Fअगरo 2 */
	हाल 31:	/* GPHY 2 */
	हाल 40 ... 47: /* Pattern Ram 2 */
	हाल 52: हाल 54: /* TCP Segmentation 2 */
	हाल 112 ... 116: /* GMAC 2 */
		वापस hw->ports > 1;

	हाल 0:		/* Control */
	हाल 2:		/* Mac address */
	हाल 4:		/* Tx Arbiter 1 */
	हाल 7:		/* PCI express reg */
	हाल 8:		/* RX1 */
	हाल 12 ... 13: /* TX1 */
	हाल 16: हाल 18:/* Rx Ram Buffer 1 */
	हाल 20 ... 21: /* Tx Ram Buffer 1 */
	हाल 24:	/* Rx MAC Fअगरo 1 */
	हाल 26:	/* Tx MAC Fअगरo 1 */
	हाल 28 ... 29: /* Descriptor and status unit */
	हाल 30:	/* GPHY 1*/
	हाल 32 ... 39: /* Pattern Ram 1 */
	हाल 48: हाल 50: /* TCP Segmentation 1 */
	हाल 56 ... 60:	/* PCI space */
	हाल 80 ... 84:	/* GMAC 1 */
		वापस 1;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Returns copy of control रेजिस्टर region
 * Note: ethtool_get_regs always provides full size (16k) buffer
 */
अटल व्योम sky2_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			  व्योम *p)
अणु
	स्थिर काष्ठा sky2_port *sky2 = netdev_priv(dev);
	स्थिर व्योम __iomem *io = sky2->hw->regs;
	अचिन्हित पूर्णांक b;

	regs->version = 1;

	क्रम (b = 0; b < 128; b++) अणु
		/* skip poisonous diagnostic ram region in block 3 */
		अगर (b == 3)
			स_नकल_fromio(p + 0x10, io + 0x10, 128 - 0x10);
		अन्यथा अगर (sky2_reg_access_ok(sky2->hw, b))
			स_नकल_fromio(p, io, 128);
		अन्यथा
			स_रखो(p, 0, 128);

		p += 128;
		io += 128;
	पूर्ण
पूर्ण

अटल पूर्णांक sky2_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	u16 reg2;

	reg2 = sky2_pci_पढ़ो16(hw, PCI_DEV_REG2);
	वापस 1 << ( ((reg2 & PCI_VPD_ROM_SZ) >> 14) + 8);
पूर्ण

अटल पूर्णांक sky2_vpd_रुको(स्थिर काष्ठा sky2_hw *hw, पूर्णांक cap, u16 busy)
अणु
	अचिन्हित दीर्घ start = jअगरfies;

	जबतक ( (sky2_pci_पढ़ो16(hw, cap + PCI_VPD_ADDR) & PCI_VPD_ADDR_F) == busy) अणु
		/* Can take up to 10.6 ms क्रम ग_लिखो */
		अगर (समय_after(jअगरfies, start + HZ/4)) अणु
			dev_err(&hw->pdev->dev, "VPD cycle timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sky2_vpd_पढ़ो(काष्ठा sky2_hw *hw, पूर्णांक cap, व्योम *data,
			 u16 offset, माप_प्रकार length)
अणु
	पूर्णांक rc = 0;

	जबतक (length > 0) अणु
		u32 val;

		sky2_pci_ग_लिखो16(hw, cap + PCI_VPD_ADDR, offset);
		rc = sky2_vpd_रुको(hw, cap, 0);
		अगर (rc)
			अवरोध;

		val = sky2_pci_पढ़ो32(hw, cap + PCI_VPD_DATA);

		स_नकल(data, &val, min(माप(val), length));
		offset += माप(u32);
		data += माप(u32);
		length -= माप(u32);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक sky2_vpd_ग_लिखो(काष्ठा sky2_hw *hw, पूर्णांक cap, स्थिर व्योम *data,
			  u16 offset, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;

	क्रम (i = 0; i < length; i += माप(u32)) अणु
		u32 val = *(u32 *)(data + i);

		sky2_pci_ग_लिखो32(hw, cap + PCI_VPD_DATA, val);
		sky2_pci_ग_लिखो32(hw, cap + PCI_VPD_ADDR, offset | PCI_VPD_ADDR_F);

		rc = sky2_vpd_रुको(hw, cap, PCI_VPD_ADDR_F);
		अगर (rc)
			अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक sky2_get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
			   u8 *data)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	पूर्णांक cap = pci_find_capability(sky2->hw->pdev, PCI_CAP_ID_VPD);

	अगर (!cap)
		वापस -EINVAL;

	eeprom->magic = SKY2_EEPROM_MAGIC;

	वापस sky2_vpd_पढ़ो(sky2->hw, cap, data, eeprom->offset, eeprom->len);
पूर्ण

अटल पूर्णांक sky2_set_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
			   u8 *data)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	पूर्णांक cap = pci_find_capability(sky2->hw->pdev, PCI_CAP_ID_VPD);

	अगर (!cap)
		वापस -EINVAL;

	अगर (eeprom->magic != SKY2_EEPROM_MAGIC)
		वापस -EINVAL;

	/* Partial ग_लिखोs not supported */
	अगर ((eeprom->offset & 3) || (eeprom->len & 3))
		वापस -EINVAL;

	वापस sky2_vpd_ग_लिखो(sky2->hw, cap, data, eeprom->offset, eeprom->len);
पूर्ण

अटल netdev_features_t sky2_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	स्थिर काष्ठा sky2_port *sky2 = netdev_priv(dev);
	स्थिर काष्ठा sky2_hw *hw = sky2->hw;

	/* In order to करो Jumbo packets on these chips, need to turn off the
	 * transmit store/क्रमward. Thereक्रमe checksum offload won't work.
	 */
	अगर (dev->mtu > ETH_DATA_LEN && hw->chip_id == CHIP_ID_YUKON_EC_U) अणु
		netdev_info(dev, "checksum offload not possible with jumbo frames\n");
		features &= ~(NETIF_F_TSO | NETIF_F_SG | NETIF_F_CSUM_MASK);
	पूर्ण

	/* Some hardware requires receive checksum क्रम RSS to work. */
	अगर ( (features & NETIF_F_RXHASH) &&
	     !(features & NETIF_F_RXCSUM) &&
	     (sky2->hw->flags & SKY2_HW_RSS_CHKSUM)) अणु
		netdev_info(dev, "receive hashing forces receive checksum\n");
		features |= NETIF_F_RXCSUM;
	पूर्ण

	वापस features;
पूर्ण

अटल पूर्णांक sky2_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा sky2_port *sky2 = netdev_priv(dev);
	netdev_features_t changed = dev->features ^ features;

	अगर ((changed & NETIF_F_RXCSUM) &&
	    !(sky2->hw->flags & SKY2_HW_NEW_LE)) अणु
		sky2_ग_लिखो32(sky2->hw,
			     Q_ADDR(rxqaddr[sky2->port], Q_CSR),
			     (features & NETIF_F_RXCSUM)
			     ? BMU_ENA_RX_CHKSUM : BMU_DIS_RX_CHKSUM);
	पूर्ण

	अगर (changed & NETIF_F_RXHASH)
		rx_set_rss(dev, features);

	अगर (changed & (NETIF_F_HW_VLAN_CTAG_TX|NETIF_F_HW_VLAN_CTAG_RX))
		sky2_vlan_mode(dev, features);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sky2_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_RX_USECS_IRQ |
				     ETHTOOL_COALESCE_RX_MAX_FRAMES_IRQ,
	.get_drvinfo	= sky2_get_drvinfo,
	.get_wol	= sky2_get_wol,
	.set_wol	= sky2_set_wol,
	.get_msglevel	= sky2_get_msglevel,
	.set_msglevel	= sky2_set_msglevel,
	.nway_reset	= sky2_nway_reset,
	.get_regs_len	= sky2_get_regs_len,
	.get_regs	= sky2_get_regs,
	.get_link	= ethtool_op_get_link,
	.get_eeprom_len	= sky2_get_eeprom_len,
	.get_eeprom	= sky2_get_eeprom,
	.set_eeprom	= sky2_set_eeprom,
	.get_strings	= sky2_get_strings,
	.get_coalesce	= sky2_get_coalesce,
	.set_coalesce	= sky2_set_coalesce,
	.get_ringparam	= sky2_get_ringparam,
	.set_ringparam	= sky2_set_ringparam,
	.get_छोड़ोparam = sky2_get_छोड़ोparam,
	.set_छोड़ोparam = sky2_set_छोड़ोparam,
	.set_phys_id	= sky2_set_phys_id,
	.get_sset_count = sky2_get_sset_count,
	.get_ethtool_stats = sky2_get_ethtool_stats,
	.get_link_ksettings = sky2_get_link_ksettings,
	.set_link_ksettings = sky2_set_link_ksettings,
पूर्ण;

#अगर_घोषित CONFIG_SKY2_DEBUG

अटल काष्ठा dentry *sky2_debug;


/*
 * Read and parse the first part of Vital Product Data
 */
#घोषणा VPD_SIZE	128
#घोषणा VPD_MAGIC	0x82

अटल स्थिर काष्ठा vpd_tag अणु
	अक्षर tag[2];
	अक्षर *label;
पूर्ण vpd_tags[] = अणु
	अणु "PN",	"Part Number" पूर्ण,
	अणु "EC", "Engineering Level" पूर्ण,
	अणु "MN", "Manufacturer" पूर्ण,
	अणु "SN", "Serial Number" पूर्ण,
	अणु "YA", "Asset Tag" पूर्ण,
	अणु "VL", "First Error Log Message" पूर्ण,
	अणु "VF", "Second Error Log Message" पूर्ण,
	अणु "VB", "Boot Agent ROM Configuration" पूर्ण,
	अणु "VE", "EFI UNDI Configuration" पूर्ण,
पूर्ण;

अटल व्योम sky2_show_vpd(काष्ठा seq_file *seq, काष्ठा sky2_hw *hw)
अणु
	माप_प्रकार vpd_size;
	loff_t offs;
	u8 len;
	अचिन्हित अक्षर *buf;
	u16 reg2;

	reg2 = sky2_pci_पढ़ो16(hw, PCI_DEV_REG2);
	vpd_size = 1 << ( ((reg2 & PCI_VPD_ROM_SZ) >> 14) + 8);

	seq_म_लिखो(seq, "%s Product Data\n", pci_name(hw->pdev));
	buf = kदो_स्मृति(vpd_size, GFP_KERNEL);
	अगर (!buf) अणु
		seq_माला_दो(seq, "no memory!\n");
		वापस;
	पूर्ण

	अगर (pci_पढ़ो_vpd(hw->pdev, 0, vpd_size, buf) < 0) अणु
		seq_माला_दो(seq, "VPD read failed\n");
		जाओ out;
	पूर्ण

	अगर (buf[0] != VPD_MAGIC) अणु
		seq_म_लिखो(seq, "VPD tag mismatch: %#x\n", buf[0]);
		जाओ out;
	पूर्ण
	len = buf[1];
	अगर (len == 0 || len > vpd_size - 4) अणु
		seq_म_लिखो(seq, "Invalid id length: %d\n", len);
		जाओ out;
	पूर्ण

	seq_म_लिखो(seq, "%.*s\n", len, buf + 3);
	offs = len + 3;

	जबतक (offs < vpd_size - 4) अणु
		पूर्णांक i;

		अगर (!स_भेद("RW", buf + offs, 2))	/* end marker */
			अवरोध;
		len = buf[offs + 2];
		अगर (offs + len + 3 >= vpd_size)
			अवरोध;

		क्रम (i = 0; i < ARRAY_SIZE(vpd_tags); i++) अणु
			अगर (!स_भेद(vpd_tags[i].tag, buf + offs, 2)) अणु
				seq_म_लिखो(seq, " %s: %.*s\n",
					   vpd_tags[i].label, len, buf + offs + 3);
				अवरोध;
			पूर्ण
		पूर्ण
		offs += len + 3;
	पूर्ण
out:
	kमुक्त(buf);
पूर्ण

अटल पूर्णांक sky2_debug_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा net_device *dev = seq->निजी;
	स्थिर काष्ठा sky2_port *sky2 = netdev_priv(dev);
	काष्ठा sky2_hw *hw = sky2->hw;
	अचिन्हित port = sky2->port;
	अचिन्हित idx, last;
	पूर्णांक sop;

	sky2_show_vpd(seq, hw);

	seq_म_लिखो(seq, "\nIRQ src=%x mask=%x control=%x\n",
		   sky2_पढ़ो32(hw, B0_ISRC),
		   sky2_पढ़ो32(hw, B0_IMSK),
		   sky2_पढ़ो32(hw, B0_Y2_SP_ICR));

	अगर (!netअगर_running(dev)) अणु
		seq_माला_दो(seq, "network not running\n");
		वापस 0;
	पूर्ण

	napi_disable(&hw->napi);
	last = sky2_पढ़ो16(hw, STAT_PUT_IDX);

	seq_म_लिखो(seq, "Status ring %u\n", hw->st_size);
	अगर (hw->st_idx == last)
		seq_माला_दो(seq, "Status ring (empty)\n");
	अन्यथा अणु
		seq_माला_दो(seq, "Status ring\n");
		क्रम (idx = hw->st_idx; idx != last && idx < hw->st_size;
		     idx = RING_NEXT(idx, hw->st_size)) अणु
			स्थिर काष्ठा sky2_status_le *le = hw->st_le + idx;
			seq_म_लिखो(seq, "[%d] %#x %d %#x\n",
				   idx, le->opcode, le->length, le->status);
		पूर्ण
		seq_माला_दो(seq, "\n");
	पूर्ण

	seq_म_लिखो(seq, "Tx ring pending=%u...%u report=%d done=%d\n",
		   sky2->tx_cons, sky2->tx_prod,
		   sky2_पढ़ो16(hw, port == 0 ? STAT_TXA1_RIDX : STAT_TXA2_RIDX),
		   sky2_पढ़ो16(hw, Q_ADDR(txqaddr[port], Q_DONE)));

	/* Dump contents of tx ring */
	sop = 1;
	क्रम (idx = sky2->tx_next; idx != sky2->tx_prod && idx < sky2->tx_ring_size;
	     idx = RING_NEXT(idx, sky2->tx_ring_size)) अणु
		स्थिर काष्ठा sky2_tx_le *le = sky2->tx_le + idx;
		u32 a = le32_to_cpu(le->addr);

		अगर (sop)
			seq_म_लिखो(seq, "%u:", idx);
		sop = 0;

		चयन (le->opcode & ~HW_OWNER) अणु
		हाल OP_ADDR64:
			seq_म_लिखो(seq, " %#x:", a);
			अवरोध;
		हाल OP_LRGLEN:
			seq_म_लिखो(seq, " mtu=%d", a);
			अवरोध;
		हाल OP_VLAN:
			seq_म_लिखो(seq, " vlan=%d", be16_to_cpu(le->length));
			अवरोध;
		हाल OP_TCPLISW:
			seq_म_लिखो(seq, " csum=%#x", a);
			अवरोध;
		हाल OP_LARGESEND:
			seq_म_लिखो(seq, " tso=%#x(%d)", a, le16_to_cpu(le->length));
			अवरोध;
		हाल OP_PACKET:
			seq_म_लिखो(seq, " %#x(%d)", a, le16_to_cpu(le->length));
			अवरोध;
		हाल OP_BUFFER:
			seq_म_लिखो(seq, " frag=%#x(%d)", a, le16_to_cpu(le->length));
			अवरोध;
		शेष:
			seq_म_लिखो(seq, " op=%#x,%#x(%d)", le->opcode,
				   a, le16_to_cpu(le->length));
		पूर्ण

		अगर (le->ctrl & EOP) अणु
			seq_अ_दो(seq, '\n');
			sop = 1;
		पूर्ण
	पूर्ण

	seq_म_लिखो(seq, "\nRx ring hw get=%d put=%d last=%d\n",
		   sky2_पढ़ो16(hw, Y2_QADDR(rxqaddr[port], PREF_UNIT_GET_IDX)),
		   sky2_पढ़ो16(hw, Y2_QADDR(rxqaddr[port], PREF_UNIT_PUT_IDX)),
		   sky2_पढ़ो16(hw, Y2_QADDR(rxqaddr[port], PREF_UNIT_LAST_IDX)));

	sky2_पढ़ो32(hw, B0_Y2_SP_LISR);
	napi_enable(&hw->napi);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(sky2_debug);

/*
 * Use network device events to create/हटाओ/नाम
 * debugfs file entries
 */
अटल पूर्णांक sky2_device_event(काष्ठा notअगरier_block *unused,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा sky2_port *sky2 = netdev_priv(dev);

	अगर (dev->netdev_ops->nकरो_खोलो != sky2_खोलो || !sky2_debug)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_CHANGENAME:
		अगर (sky2->debugfs) अणु
			sky2->debugfs = debugfs_नाम(sky2_debug, sky2->debugfs,
						       sky2_debug, dev->name);
		पूर्ण
		अवरोध;

	हाल NETDEV_GOING_DOWN:
		अगर (sky2->debugfs) अणु
			netdev_prपूर्णांकk(KERN_DEBUG, dev, "remove debugfs\n");
			debugfs_हटाओ(sky2->debugfs);
			sky2->debugfs = शून्य;
		पूर्ण
		अवरोध;

	हाल NETDEV_UP:
		sky2->debugfs = debugfs_create_file(dev->name, 0444,
						    sky2_debug, dev,
						    &sky2_debug_fops);
		अगर (IS_ERR(sky2->debugfs))
			sky2->debugfs = शून्य;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block sky2_notअगरier = अणु
	.notअगरier_call = sky2_device_event,
पूर्ण;


अटल __init व्योम sky2_debug_init(व्योम)
अणु
	काष्ठा dentry *ent;

	ent = debugfs_create_dir("sky2", शून्य);
	अगर (!ent || IS_ERR(ent))
		वापस;

	sky2_debug = ent;
	रेजिस्टर_netdevice_notअगरier(&sky2_notअगरier);
पूर्ण

अटल __निकास व्योम sky2_debug_cleanup(व्योम)
अणु
	अगर (sky2_debug) अणु
		unरेजिस्टर_netdevice_notअगरier(&sky2_notअगरier);
		debugfs_हटाओ(sky2_debug);
		sky2_debug = शून्य;
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा sky2_debug_init()
#घोषणा sky2_debug_cleanup()
#पूर्ण_अगर

/* Two copies of network device operations to handle special हाल of
 * not allowing netpoll on second port
 */
अटल स्थिर काष्ठा net_device_ops sky2_netdev_ops[2] = अणु
  अणु
	.nकरो_खोलो		= sky2_खोलो,
	.nकरो_stop		= sky2_बंद,
	.nकरो_start_xmit		= sky2_xmit_frame,
	.nकरो_करो_ioctl		= sky2_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= sky2_set_mac_address,
	.nकरो_set_rx_mode	= sky2_set_multicast,
	.nकरो_change_mtu		= sky2_change_mtu,
	.nकरो_fix_features	= sky2_fix_features,
	.nकरो_set_features	= sky2_set_features,
	.nकरो_tx_समयout		= sky2_tx_समयout,
	.nकरो_get_stats64	= sky2_get_stats,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= sky2_netpoll,
#पूर्ण_अगर
  पूर्ण,
  अणु
	.nकरो_खोलो		= sky2_खोलो,
	.nकरो_stop		= sky2_बंद,
	.nकरो_start_xmit		= sky2_xmit_frame,
	.nकरो_करो_ioctl		= sky2_ioctl,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= sky2_set_mac_address,
	.nकरो_set_rx_mode	= sky2_set_multicast,
	.nकरो_change_mtu		= sky2_change_mtu,
	.nकरो_fix_features	= sky2_fix_features,
	.nकरो_set_features	= sky2_set_features,
	.nकरो_tx_समयout		= sky2_tx_समयout,
	.nकरो_get_stats64	= sky2_get_stats,
  पूर्ण,
पूर्ण;

/* Initialize network device */
अटल काष्ठा net_device *sky2_init_netdev(काष्ठा sky2_hw *hw, अचिन्हित port,
					   पूर्णांक highmem, पूर्णांक wol)
अणु
	काष्ठा sky2_port *sky2;
	काष्ठा net_device *dev = alloc_etherdev(माप(*sky2));
	पूर्णांक ret;

	अगर (!dev)
		वापस शून्य;

	SET_NETDEV_DEV(dev, &hw->pdev->dev);
	dev->irq = hw->pdev->irq;
	dev->ethtool_ops = &sky2_ethtool_ops;
	dev->watchकरोg_समयo = TX_WATCHDOG;
	dev->netdev_ops = &sky2_netdev_ops[port];

	sky2 = netdev_priv(dev);
	sky2->netdev = dev;
	sky2->hw = hw;
	sky2->msg_enable = netअगर_msg_init(debug, शेष_msg);

	u64_stats_init(&sky2->tx_stats.syncp);
	u64_stats_init(&sky2->rx_stats.syncp);

	/* Auto speed and flow control */
	sky2->flags = SKY2_FLAG_AUTO_SPEED | SKY2_FLAG_AUTO_PAUSE;
	अगर (hw->chip_id != CHIP_ID_YUKON_XL)
		dev->hw_features |= NETIF_F_RXCSUM;

	sky2->flow_mode = FC_BOTH;

	sky2->duplex = -1;
	sky2->speed = -1;
	sky2->advertising = sky2_supported_modes(hw);
	sky2->wol = wol;

	spin_lock_init(&sky2->phy_lock);

	sky2->tx_pending = TX_DEF_PENDING;
	sky2->tx_ring_size = roundup_ring_size(TX_DEF_PENDING);
	sky2->rx_pending = RX_DEF_PENDING;

	hw->dev[port] = dev;

	sky2->port = port;

	dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_SG | NETIF_F_TSO;

	अगर (highmem)
		dev->features |= NETIF_F_HIGHDMA;

	/* Enable receive hashing unless hardware is known broken */
	अगर (!(hw->flags & SKY2_HW_RSS_BROKEN))
		dev->hw_features |= NETIF_F_RXHASH;

	अगर (!(hw->flags & SKY2_HW_VLAN_BROKEN)) अणु
		dev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_HW_VLAN_CTAG_RX;
		dev->vlan_features |= SKY2_VLAN_OFFLOADS;
	पूर्ण

	dev->features |= dev->hw_features;

	/* MTU range: 60 - 1500 or 9000 */
	dev->min_mtu = ETH_ZLEN;
	अगर (hw->chip_id == CHIP_ID_YUKON_FE ||
	    hw->chip_id == CHIP_ID_YUKON_FE_P)
		dev->max_mtu = ETH_DATA_LEN;
	अन्यथा
		dev->max_mtu = ETH_JUMBO_MTU;

	/* try to get mac address in the following order:
	 * 1) from device tree data
	 * 2) from पूर्णांकernal रेजिस्टरs set by bootloader
	 */
	ret = of_get_mac_address(hw->pdev->dev.of_node, dev->dev_addr);
	अगर (ret)
		स_नकल_fromio(dev->dev_addr, hw->regs + B2_MAC_1 + port * 8,
			      ETH_ALEN);

	/* अगर the address is invalid, use a अक्रमom value */
	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		काष्ठा sockaddr sa = अणु AF_UNSPEC पूर्ण;

		dev_warn(&hw->pdev->dev, "Invalid MAC address, defaulting to random\n");
		eth_hw_addr_अक्रमom(dev);
		स_नकल(sa.sa_data, dev->dev_addr, ETH_ALEN);
		अगर (sky2_set_mac_address(dev, &sa))
			dev_warn(&hw->pdev->dev, "Failed to set MAC address.\n");
	पूर्ण

	वापस dev;
पूर्ण

अटल व्योम sky2_show_addr(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा sky2_port *sky2 = netdev_priv(dev);

	netअगर_info(sky2, probe, dev, "addr %pM\n", dev->dev_addr);
पूर्ण

/* Handle software पूर्णांकerrupt used during MSI test */
अटल irqवापस_t sky2_test_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sky2_hw *hw = dev_id;
	u32 status = sky2_पढ़ो32(hw, B0_Y2_SP_ISRC2);

	अगर (status == 0)
		वापस IRQ_NONE;

	अगर (status & Y2_IS_IRQ_SW) अणु
		hw->flags |= SKY2_HW_USE_MSI;
		wake_up(&hw->msi_रुको);
		sky2_ग_लिखो8(hw, B0_CTST, CS_CL_SW_IRQ);
	पूर्ण
	sky2_ग_लिखो32(hw, B0_Y2_SP_ICR, 2);

	वापस IRQ_HANDLED;
पूर्ण

/* Test पूर्णांकerrupt path by क्रमcing a a software IRQ */
अटल पूर्णांक sky2_test_msi(काष्ठा sky2_hw *hw)
अणु
	काष्ठा pci_dev *pdev = hw->pdev;
	पूर्णांक err;

	init_रुकोqueue_head(&hw->msi_रुको);

	err = request_irq(pdev->irq, sky2_test_पूर्णांकr, 0, DRV_NAME, hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot assign irq %d\n", pdev->irq);
		वापस err;
	पूर्ण

	sky2_ग_लिखो32(hw, B0_IMSK, Y2_IS_IRQ_SW);

	sky2_ग_लिखो8(hw, B0_CTST, CS_ST_SW_IRQ);
	sky2_पढ़ो8(hw, B0_CTST);

	रुको_event_समयout(hw->msi_रुको, (hw->flags & SKY2_HW_USE_MSI), HZ/10);

	अगर (!(hw->flags & SKY2_HW_USE_MSI)) अणु
		/* MSI test failed, go back to INTx mode */
		dev_info(&pdev->dev, "No interrupt generated using MSI, "
			 "switching to INTx mode.\n");

		err = -EOPNOTSUPP;
		sky2_ग_लिखो8(hw, B0_CTST, CS_CL_SW_IRQ);
	पूर्ण

	sky2_ग_लिखो32(hw, B0_IMSK, 0);
	sky2_पढ़ो32(hw, B0_IMSK);

	मुक्त_irq(pdev->irq, hw);

	वापस err;
पूर्ण

/* This driver supports yukon2 chipset only */
अटल स्थिर अक्षर *sky2_name(u8 chipid, अक्षर *buf, पूर्णांक sz)
अणु
	स्थिर अक्षर *name[] = अणु
		"XL",		/* 0xb3 */
		"EC Ultra", 	/* 0xb4 */
		"Extreme",	/* 0xb5 */
		"EC",		/* 0xb6 */
		"FE",		/* 0xb7 */
		"FE+",		/* 0xb8 */
		"Supreme",	/* 0xb9 */
		"UL 2",		/* 0xba */
		"Unknown",	/* 0xbb */
		"Optima",	/* 0xbc */
		"OptimaEEE",    /* 0xbd */
		"Optima 2",	/* 0xbe */
	पूर्ण;

	अगर (chipid >= CHIP_ID_YUKON_XL && chipid <= CHIP_ID_YUKON_OP_2)
		snम_लिखो(buf, sz, "%s", name[chipid - CHIP_ID_YUKON_XL]);
	अन्यथा
		snम_लिखो(buf, sz, "(chip %#x)", chipid);
	वापस buf;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id msi_blacklist[] = अणु
	अणु
		.ident = "Dell Inspiron 1545",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 1545"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Gateway P-79",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Gateway"),
			DMI_MATCH(DMI_PRODUCT_NAME, "P-79"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ASUS P5W DH Deluxe",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTEK COMPUTER INC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "P5W DH Deluxe"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ASUS P6T",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "P6T"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ASUS P6X",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "P6X"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक sky2_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev, *dev1;
	काष्ठा sky2_hw *hw;
	पूर्णांक err, using_dac = 0, wol_शेष;
	u32 reg;
	अक्षर buf1[16];

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		जाओ err_out;
	पूर्ण

	/* Get configuration inक्रमmation
	 * Note: only regular PCI config access once to test क्रम HW issues
	 *       other PCI access through shared memory क्रम speed and to
	 *	 aव्योम MMCONFIG problems.
	 */
	err = pci_पढ़ो_config_dword(pdev, PCI_DEV_REG2, &reg);
	अगर (err) अणु
		dev_err(&pdev->dev, "PCI read config failed\n");
		जाओ err_out_disable;
	पूर्ण

	अगर (~reg == 0) अणु
		dev_err(&pdev->dev, "PCI configuration read error\n");
		err = -EIO;
		जाओ err_out_disable;
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot obtain PCI resources\n");
		जाओ err_out_disable;
	पूर्ण

	pci_set_master(pdev);

	अगर (माप(dma_addr_t) > माप(u32) &&
	    !(err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64)))) अणु
		using_dac = 1;
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(64));
		अगर (err < 0) अणु
			dev_err(&pdev->dev, "unable to obtain 64 bit DMA "
				"for consistent allocations\n");
			जाओ err_out_मुक्त_regions;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "no usable DMA configuration\n");
			जाओ err_out_मुक्त_regions;
		पूर्ण
	पूर्ण


#अगर_घोषित __BIG_ENDIAN
	/* The sk98lin venकरोr driver uses hardware byte swapping but
	 * this driver uses software swapping.
	 */
	reg &= ~PCI_REV_DESC;
	err = pci_ग_लिखो_config_dword(pdev, PCI_DEV_REG2, reg);
	अगर (err) अणु
		dev_err(&pdev->dev, "PCI write config failed\n");
		जाओ err_out_मुक्त_regions;
	पूर्ण
#पूर्ण_अगर

	wol_शेष = device_may_wakeup(&pdev->dev) ? WAKE_MAGIC : 0;

	err = -ENOMEM;

	hw = kzalloc(माप(*hw) + म_माप(DRV_NAME "@pci:")
		     + म_माप(pci_name(pdev)) + 1, GFP_KERNEL);
	अगर (!hw)
		जाओ err_out_मुक्त_regions;

	hw->pdev = pdev;
	प्र_लिखो(hw->irq_name, DRV_NAME "@pci:%s", pci_name(pdev));

	hw->regs = ioremap(pci_resource_start(pdev, 0), 0x4000);
	अगर (!hw->regs) अणु
		dev_err(&pdev->dev, "cannot map device registers\n");
		जाओ err_out_मुक्त_hw;
	पूर्ण

	err = sky2_init(hw);
	अगर (err)
		जाओ err_out_iounmap;

	/* ring क्रम status responses */
	hw->st_size = hw->ports * roundup_घात_of_two(3*RX_MAX_PENDING + TX_MAX_PENDING);
	hw->st_le = dma_alloc_coherent(&pdev->dev,
				       hw->st_size * माप(काष्ठा sky2_status_le),
				       &hw->st_dma, GFP_KERNEL);
	अगर (!hw->st_le) अणु
		err = -ENOMEM;
		जाओ err_out_reset;
	पूर्ण

	dev_info(&pdev->dev, "Yukon-2 %s chip revision %d\n",
		 sky2_name(hw->chip_id, buf1, माप(buf1)), hw->chip_rev);

	sky2_reset(hw);

	dev = sky2_init_netdev(hw, 0, using_dac, wol_शेष);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_pci;
	पूर्ण

	अगर (disable_msi == -1)
		disable_msi = !!dmi_check_प्रणाली(msi_blacklist);

	अगर (!disable_msi && pci_enable_msi(pdev) == 0) अणु
		err = sky2_test_msi(hw);
		अगर (err) अणु
 			pci_disable_msi(pdev);
			अगर (err != -EOPNOTSUPP)
				जाओ err_out_मुक्त_netdev;
		पूर्ण
 	पूर्ण

	netअगर_napi_add(dev, &hw->napi, sky2_poll, NAPI_WEIGHT);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot register net device\n");
		जाओ err_out_मुक्त_netdev;
	पूर्ण

	netअगर_carrier_off(dev);

	sky2_show_addr(dev);

	अगर (hw->ports > 1) अणु
		dev1 = sky2_init_netdev(hw, 1, using_dac, wol_शेष);
		अगर (!dev1) अणु
			err = -ENOMEM;
			जाओ err_out_unरेजिस्टर;
		पूर्ण

		err = रेजिस्टर_netdev(dev1);
		अगर (err) अणु
			dev_err(&pdev->dev, "cannot register second net device\n");
			जाओ err_out_मुक्त_dev1;
		पूर्ण

		err = sky2_setup_irq(hw, hw->irq_name);
		अगर (err)
			जाओ err_out_unरेजिस्टर_dev1;

		sky2_show_addr(dev1);
	पूर्ण

	समयr_setup(&hw->watchकरोg_समयr, sky2_watchकरोg, 0);
	INIT_WORK(&hw->restart_work, sky2_restart);

	pci_set_drvdata(pdev, hw);
	pdev->d3hot_delay = 300;

	वापस 0;

err_out_unरेजिस्टर_dev1:
	unरेजिस्टर_netdev(dev1);
err_out_मुक्त_dev1:
	मुक्त_netdev(dev1);
err_out_unरेजिस्टर:
	unरेजिस्टर_netdev(dev);
err_out_मुक्त_netdev:
	अगर (hw->flags & SKY2_HW_USE_MSI)
		pci_disable_msi(pdev);
	मुक्त_netdev(dev);
err_out_मुक्त_pci:
	dma_मुक्त_coherent(&pdev->dev,
			  hw->st_size * माप(काष्ठा sky2_status_le),
			  hw->st_le, hw->st_dma);
err_out_reset:
	sky2_ग_लिखो8(hw, B0_CTST, CS_RST_SET);
err_out_iounmap:
	iounmap(hw->regs);
err_out_मुक्त_hw:
	kमुक्त(hw);
err_out_मुक्त_regions:
	pci_release_regions(pdev);
err_out_disable:
	pci_disable_device(pdev);
err_out:
	वापस err;
पूर्ण

अटल व्योम sky2_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sky2_hw *hw = pci_get_drvdata(pdev);
	पूर्णांक i;

	अगर (!hw)
		वापस;

	del_समयr_sync(&hw->watchकरोg_समयr);
	cancel_work_sync(&hw->restart_work);

	क्रम (i = hw->ports-1; i >= 0; --i)
		unरेजिस्टर_netdev(hw->dev[i]);

	sky2_ग_लिखो32(hw, B0_IMSK, 0);
	sky2_पढ़ो32(hw, B0_IMSK);

	sky2_घातer_aux(hw);

	sky2_ग_लिखो8(hw, B0_CTST, CS_RST_SET);
	sky2_पढ़ो8(hw, B0_CTST);

	अगर (hw->ports > 1) अणु
		napi_disable(&hw->napi);
		मुक्त_irq(pdev->irq, hw);
	पूर्ण

	अगर (hw->flags & SKY2_HW_USE_MSI)
		pci_disable_msi(pdev);
	dma_मुक्त_coherent(&pdev->dev,
			  hw->st_size * माप(काष्ठा sky2_status_le),
			  hw->st_le, hw->st_dma);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	क्रम (i = hw->ports-1; i >= 0; --i)
		मुक्त_netdev(hw->dev[i]);

	iounmap(hw->regs);
	kमुक्त(hw);
पूर्ण

अटल पूर्णांक sky2_suspend(काष्ठा device *dev)
अणु
	काष्ठा sky2_hw *hw = dev_get_drvdata(dev);
	पूर्णांक i;

	अगर (!hw)
		वापस 0;

	del_समयr_sync(&hw->watchकरोg_समयr);
	cancel_work_sync(&hw->restart_work);

	rtnl_lock();

	sky2_all_करोwn(hw);
	क्रम (i = 0; i < hw->ports; i++) अणु
		काष्ठा net_device *dev = hw->dev[i];
		काष्ठा sky2_port *sky2 = netdev_priv(dev);

		अगर (sky2->wol)
			sky2_wol_init(sky2);
	पूर्ण

	sky2_घातer_aux(hw);
	rtnl_unlock();

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sky2_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा sky2_hw *hw = pci_get_drvdata(pdev);
	पूर्णांक err;

	अगर (!hw)
		वापस 0;

	/* Re-enable all घड़ीs */
	err = pci_ग_लिखो_config_dword(pdev, PCI_DEV_REG3, 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "PCI write config failed\n");
		जाओ out;
	पूर्ण

	rtnl_lock();
	sky2_reset(hw);
	sky2_all_up(hw);
	rtnl_unlock();

	वापस 0;
out:

	dev_err(&pdev->dev, "resume failed (%d)\n", err);
	pci_disable_device(pdev);
	वापस err;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sky2_pm_ops, sky2_suspend, sky2_resume);
#घोषणा SKY2_PM_OPS (&sky2_pm_ops)

#अन्यथा

#घोषणा SKY2_PM_OPS शून्य
#पूर्ण_अगर

अटल व्योम sky2_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sky2_hw *hw = pci_get_drvdata(pdev);
	पूर्णांक port;

	क्रम (port = 0; port < hw->ports; port++) अणु
		काष्ठा net_device *ndev = hw->dev[port];

		rtnl_lock();
		अगर (netअगर_running(ndev)) अणु
			dev_बंद(ndev);
			netअगर_device_detach(ndev);
		पूर्ण
		rtnl_unlock();
	पूर्ण
	sky2_suspend(&pdev->dev);
	pci_wake_from_d3(pdev, device_may_wakeup(&pdev->dev));
	pci_set_घातer_state(pdev, PCI_D3hot);
पूर्ण

अटल काष्ठा pci_driver sky2_driver = अणु
	.name = DRV_NAME,
	.id_table = sky2_id_table,
	.probe = sky2_probe,
	.हटाओ = sky2_हटाओ,
	.shutकरोwn = sky2_shutकरोwn,
	.driver.pm = SKY2_PM_OPS,
पूर्ण;

अटल पूर्णांक __init sky2_init_module(व्योम)
अणु
	pr_info("driver version " DRV_VERSION "\n");

	sky2_debug_init();
	वापस pci_रेजिस्टर_driver(&sky2_driver);
पूर्ण

अटल व्योम __निकास sky2_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sky2_driver);
	sky2_debug_cleanup();
पूर्ण

module_init(sky2_init_module);
module_निकास(sky2_cleanup_module);

MODULE_DESCRIPTION("Marvell Yukon 2 Gigabit Ethernet driver");
MODULE_AUTHOR("Stephen Hemminger <shemminger@linux-foundation.org>");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
