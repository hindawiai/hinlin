<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dwmac-sun8i.c - Allwinner sun8i DWMAC specअगरic glue layer
 *
 * Copyright (C) 2017 Corentin Labbe <clabbe.montjoie@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mdio-mux.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac.h"
#समावेश "stmmac_platform.h"

/* General notes on dwmac-sun8i:
 * Locking: no locking is necessary in this file because all necessary locking
 *		is करोne in the "stmmac files"
 */

/* काष्ठा emac_variant - Describe dwmac-sun8i hardware variant
 * @शेष_syscon_value:	The शेष value of the EMAC रेजिस्टर in syscon
 *				This value is used क्रम disabling properly EMAC
 *				and used as a good starting value in हाल of the
 *				boot process(uboot) leave some stuff.
 * @syscon_field		reg_field क्रम the syscon's gmac रेजिस्टर
 * @soc_has_पूर्णांकernal_phy:	Does the MAC embed an पूर्णांकernal PHY
 * @support_mii:		Does the MAC handle MII
 * @support_rmii:		Does the MAC handle RMII
 * @support_rgmii:		Does the MAC handle RGMII
 *
 * @rx_delay_max:		Maximum raw value क्रम RX delay chain
 * @tx_delay_max:		Maximum raw value क्रम TX delay chain
 *				These two also indicate the biपंचांगask क्रम
 *				the RX and TX delay chain रेजिस्टरs. A
 *				value of zero indicates this is not supported.
 */
काष्ठा emac_variant अणु
	u32 शेष_syscon_value;
	स्थिर काष्ठा reg_field *syscon_field;
	bool soc_has_पूर्णांकernal_phy;
	bool support_mii;
	bool support_rmii;
	bool support_rgmii;
	u8 rx_delay_max;
	u8 tx_delay_max;
पूर्ण;

/* काष्ठा sunxi_priv_data - hold all sunxi निजी data
 * @tx_clk:	reference to MAC TX घड़ी
 * @ephy_clk:	reference to the optional EPHY घड़ी क्रम the पूर्णांकernal PHY
 * @regulator:	reference to the optional regulator
 * @rst_ephy:	reference to the optional EPHY reset क्रम the पूर्णांकernal PHY
 * @variant:	reference to the current board variant
 * @regmap:	regmap क्रम using the syscon
 * @पूर्णांकernal_phy_घातered: Does the पूर्णांकernal PHY is enabled
 * @use_पूर्णांकernal_phy: Is the पूर्णांकernal PHY selected क्रम use
 * @mux_handle:	Internal poपूर्णांकer used by mdio-mux lib
 */
काष्ठा sunxi_priv_data अणु
	काष्ठा clk *tx_clk;
	काष्ठा clk *ephy_clk;
	काष्ठा regulator *regulator;
	काष्ठा reset_control *rst_ephy;
	स्थिर काष्ठा emac_variant *variant;
	काष्ठा regmap_field *regmap_field;
	bool पूर्णांकernal_phy_घातered;
	bool use_पूर्णांकernal_phy;
	व्योम *mux_handle;
पूर्ण;

/* EMAC घड़ी रेजिस्टर @ 0x30 in the "system control" address range */
अटल स्थिर काष्ठा reg_field sun8i_syscon_reg_field = अणु
	.reg = 0x30,
	.lsb = 0,
	.msb = 31,
पूर्ण;

/* EMAC घड़ी रेजिस्टर @ 0x164 in the CCU address range */
अटल स्थिर काष्ठा reg_field sun8i_ccu_reg_field = अणु
	.reg = 0x164,
	.lsb = 0,
	.msb = 31,
पूर्ण;

अटल स्थिर काष्ठा emac_variant emac_variant_h3 = अणु
	.शेष_syscon_value = 0x58000,
	.syscon_field = &sun8i_syscon_reg_field,
	.soc_has_पूर्णांकernal_phy = true,
	.support_mii = true,
	.support_rmii = true,
	.support_rgmii = true,
	.rx_delay_max = 31,
	.tx_delay_max = 7,
पूर्ण;

अटल स्थिर काष्ठा emac_variant emac_variant_v3s = अणु
	.शेष_syscon_value = 0x38000,
	.syscon_field = &sun8i_syscon_reg_field,
	.soc_has_पूर्णांकernal_phy = true,
	.support_mii = true
पूर्ण;

अटल स्थिर काष्ठा emac_variant emac_variant_a83t = अणु
	.शेष_syscon_value = 0,
	.syscon_field = &sun8i_syscon_reg_field,
	.soc_has_पूर्णांकernal_phy = false,
	.support_mii = true,
	.support_rgmii = true,
	.rx_delay_max = 31,
	.tx_delay_max = 7,
पूर्ण;

अटल स्थिर काष्ठा emac_variant emac_variant_r40 = अणु
	.शेष_syscon_value = 0,
	.syscon_field = &sun8i_ccu_reg_field,
	.support_mii = true,
	.support_rgmii = true,
	.rx_delay_max = 7,
पूर्ण;

अटल स्थिर काष्ठा emac_variant emac_variant_a64 = अणु
	.शेष_syscon_value = 0,
	.syscon_field = &sun8i_syscon_reg_field,
	.soc_has_पूर्णांकernal_phy = false,
	.support_mii = true,
	.support_rmii = true,
	.support_rgmii = true,
	.rx_delay_max = 31,
	.tx_delay_max = 7,
पूर्ण;

अटल स्थिर काष्ठा emac_variant emac_variant_h6 = अणु
	.शेष_syscon_value = 0x50000,
	.syscon_field = &sun8i_syscon_reg_field,
	/* The "Internal PHY" of H6 is not on the die. It's on the
	 * co-packaged AC200 chip instead.
	 */
	.soc_has_पूर्णांकernal_phy = false,
	.support_mii = true,
	.support_rmii = true,
	.support_rgmii = true,
	.rx_delay_max = 31,
	.tx_delay_max = 7,
पूर्ण;

#घोषणा EMAC_BASIC_CTL0 0x00
#घोषणा EMAC_BASIC_CTL1 0x04
#घोषणा EMAC_INT_STA    0x08
#घोषणा EMAC_INT_EN     0x0C
#घोषणा EMAC_TX_CTL0    0x10
#घोषणा EMAC_TX_CTL1    0x14
#घोषणा EMAC_TX_FLOW_CTL        0x1C
#घोषणा EMAC_TX_DESC_LIST 0x20
#घोषणा EMAC_RX_CTL0    0x24
#घोषणा EMAC_RX_CTL1    0x28
#घोषणा EMAC_RX_DESC_LIST 0x34
#घोषणा EMAC_RX_FRM_FLT 0x38
#घोषणा EMAC_MDIO_CMD   0x48
#घोषणा EMAC_MDIO_DATA  0x4C
#घोषणा EMAC_MACADDR_HI(reg) (0x50 + (reg) * 8)
#घोषणा EMAC_MACADDR_LO(reg) (0x54 + (reg) * 8)
#घोषणा EMAC_TX_DMA_STA 0xB0
#घोषणा EMAC_TX_CUR_DESC        0xB4
#घोषणा EMAC_TX_CUR_BUF 0xB8
#घोषणा EMAC_RX_DMA_STA 0xC0
#घोषणा EMAC_RX_CUR_DESC        0xC4
#घोषणा EMAC_RX_CUR_BUF 0xC8

/* Use in EMAC_BASIC_CTL0 */
#घोषणा EMAC_DUPLEX_FULL	BIT(0)
#घोषणा EMAC_LOOPBACK		BIT(1)
#घोषणा EMAC_SPEED_1000 0
#घोषणा EMAC_SPEED_100 (0x03 << 2)
#घोषणा EMAC_SPEED_10 (0x02 << 2)

/* Use in EMAC_BASIC_CTL1 */
#घोषणा EMAC_BURSTLEN_SHIFT		24

/* Used in EMAC_RX_FRM_FLT */
#घोषणा EMAC_FRM_FLT_RXALL              BIT(0)
#घोषणा EMAC_FRM_FLT_CTL                BIT(13)
#घोषणा EMAC_FRM_FLT_MULTICAST          BIT(16)

/* Used in RX_CTL1*/
#घोषणा EMAC_RX_MD              BIT(1)
#घोषणा EMAC_RX_TH_MASK		GENMASK(5, 4)
#घोषणा EMAC_RX_TH_32		0
#घोषणा EMAC_RX_TH_64		(0x1 << 4)
#घोषणा EMAC_RX_TH_96		(0x2 << 4)
#घोषणा EMAC_RX_TH_128		(0x3 << 4)
#घोषणा EMAC_RX_DMA_EN  BIT(30)
#घोषणा EMAC_RX_DMA_START       BIT(31)

/* Used in TX_CTL1*/
#घोषणा EMAC_TX_MD              BIT(1)
#घोषणा EMAC_TX_NEXT_FRM        BIT(2)
#घोषणा EMAC_TX_TH_MASK		GENMASK(10, 8)
#घोषणा EMAC_TX_TH_64		0
#घोषणा EMAC_TX_TH_128		(0x1 << 8)
#घोषणा EMAC_TX_TH_192		(0x2 << 8)
#घोषणा EMAC_TX_TH_256		(0x3 << 8)
#घोषणा EMAC_TX_DMA_EN  BIT(30)
#घोषणा EMAC_TX_DMA_START       BIT(31)

/* Used in RX_CTL0 */
#घोषणा EMAC_RX_RECEIVER_EN             BIT(31)
#घोषणा EMAC_RX_DO_CRC BIT(27)
#घोषणा EMAC_RX_FLOW_CTL_EN             BIT(16)

/* Used in TX_CTL0 */
#घोषणा EMAC_TX_TRANSMITTER_EN  BIT(31)

/* Used in EMAC_TX_FLOW_CTL */
#घोषणा EMAC_TX_FLOW_CTL_EN             BIT(0)

/* Used in EMAC_INT_STA */
#घोषणा EMAC_TX_INT             BIT(0)
#घोषणा EMAC_TX_DMA_STOP_INT    BIT(1)
#घोषणा EMAC_TX_BUF_UA_INT      BIT(2)
#घोषणा EMAC_TX_TIMEOUT_INT     BIT(3)
#घोषणा EMAC_TX_UNDERFLOW_INT   BIT(4)
#घोषणा EMAC_TX_EARLY_INT       BIT(5)
#घोषणा EMAC_RX_INT             BIT(8)
#घोषणा EMAC_RX_BUF_UA_INT      BIT(9)
#घोषणा EMAC_RX_DMA_STOP_INT    BIT(10)
#घोषणा EMAC_RX_TIMEOUT_INT     BIT(11)
#घोषणा EMAC_RX_OVERFLOW_INT    BIT(12)
#घोषणा EMAC_RX_EARLY_INT       BIT(13)
#घोषणा EMAC_RGMII_STA_INT      BIT(16)

#घोषणा EMAC_INT_MSK_COMMON	EMAC_RGMII_STA_INT
#घोषणा EMAC_INT_MSK_TX		(EMAC_TX_INT | \
				 EMAC_TX_DMA_STOP_INT | \
				 EMAC_TX_BUF_UA_INT | \
				 EMAC_TX_TIMEOUT_INT | \
				 EMAC_TX_UNDERFLOW_INT | \
				 EMAC_TX_EARLY_INT |\
				 EMAC_INT_MSK_COMMON)
#घोषणा EMAC_INT_MSK_RX		(EMAC_RX_INT | \
				 EMAC_RX_BUF_UA_INT | \
				 EMAC_RX_DMA_STOP_INT | \
				 EMAC_RX_TIMEOUT_INT | \
				 EMAC_RX_OVERFLOW_INT | \
				 EMAC_RX_EARLY_INT | \
				 EMAC_INT_MSK_COMMON)

#घोषणा MAC_ADDR_TYPE_DST BIT(31)

/* H3 specअगरic bits क्रम EPHY */
#घोषणा H3_EPHY_ADDR_SHIFT	20
#घोषणा H3_EPHY_CLK_SEL		BIT(18) /* 1: 24MHz, 0: 25MHz */
#घोषणा H3_EPHY_LED_POL		BIT(17) /* 1: active low, 0: active high */
#घोषणा H3_EPHY_SHUTDOWN	BIT(16) /* 1: shutकरोwn, 0: घातer up */
#घोषणा H3_EPHY_SELECT		BIT(15) /* 1: पूर्णांकernal PHY, 0: बाह्यal PHY */
#घोषणा H3_EPHY_MUX_MASK	(H3_EPHY_SHUTDOWN | H3_EPHY_SELECT)
#घोषणा DWMAC_SUN8I_MDIO_MUX_INTERNAL_ID	1
#घोषणा DWMAC_SUN8I_MDIO_MUX_EXTERNAL_ID	2

/* H3/A64 specअगरic bits */
#घोषणा SYSCON_RMII_EN		BIT(13) /* 1: enable RMII (overrides EPIT) */

/* Generic प्रणाली control EMAC_CLK bits */
#घोषणा SYSCON_ETXDC_SHIFT		10
#घोषणा SYSCON_ERXDC_SHIFT		5
/* EMAC PHY Interface Type */
#घोषणा SYSCON_EPIT			BIT(2) /* 1: RGMII, 0: MII */
#घोषणा SYSCON_ETCS_MASK		GENMASK(1, 0)
#घोषणा SYSCON_ETCS_MII		0x0
#घोषणा SYSCON_ETCS_EXT_GMII	0x1
#घोषणा SYSCON_ETCS_INT_GMII	0x2

/* sun8i_dwmac_dma_reset() - reset the EMAC
 * Called from sपंचांगmac via sपंचांगmac_dma_ops->reset
 */
अटल पूर्णांक sun8i_dwmac_dma_reset(व्योम __iomem *ioaddr)
अणु
	ग_लिखोl(0, ioaddr + EMAC_RX_CTL1);
	ग_लिखोl(0, ioaddr + EMAC_TX_CTL1);
	ग_लिखोl(0, ioaddr + EMAC_RX_FRM_FLT);
	ग_लिखोl(0, ioaddr + EMAC_RX_DESC_LIST);
	ग_लिखोl(0, ioaddr + EMAC_TX_DESC_LIST);
	ग_लिखोl(0, ioaddr + EMAC_INT_EN);
	ग_लिखोl(0x1FFFFFF, ioaddr + EMAC_INT_STA);
	वापस 0;
पूर्ण

/* sun8i_dwmac_dma_init() - initialize the EMAC
 * Called from sपंचांगmac via sपंचांगmac_dma_ops->init
 */
अटल व्योम sun8i_dwmac_dma_init(व्योम __iomem *ioaddr,
				 काष्ठा sपंचांगmac_dma_cfg *dma_cfg, पूर्णांक atds)
अणु
	ग_लिखोl(EMAC_RX_INT | EMAC_TX_INT, ioaddr + EMAC_INT_EN);
	ग_लिखोl(0x1FFFFFF, ioaddr + EMAC_INT_STA);
पूर्ण

अटल व्योम sun8i_dwmac_dma_init_rx(व्योम __iomem *ioaddr,
				    काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
				    dma_addr_t dma_rx_phy, u32 chan)
अणु
	/* Write RX descriptors address */
	ग_लिखोl(lower_32_bits(dma_rx_phy), ioaddr + EMAC_RX_DESC_LIST);
पूर्ण

अटल व्योम sun8i_dwmac_dma_init_tx(व्योम __iomem *ioaddr,
				    काष्ठा sपंचांगmac_dma_cfg *dma_cfg,
				    dma_addr_t dma_tx_phy, u32 chan)
अणु
	/* Write TX descriptors address */
	ग_लिखोl(lower_32_bits(dma_tx_phy), ioaddr + EMAC_TX_DESC_LIST);
पूर्ण

/* sun8i_dwmac_dump_regs() - Dump EMAC address space
 * Called from sपंचांगmac_dma_ops->dump_regs
 * Used क्रम ethtool
 */
अटल व्योम sun8i_dwmac_dump_regs(व्योम __iomem *ioaddr, u32 *reg_space)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0xC8; i += 4) अणु
		अगर (i == 0x32 || i == 0x3C)
			जारी;
		reg_space[i / 4] = पढ़ोl(ioaddr + i);
	पूर्ण
पूर्ण

/* sun8i_dwmac_dump_mac_regs() - Dump EMAC address space
 * Called from sपंचांगmac_ops->dump_regs
 * Used क्रम ethtool
 */
अटल व्योम sun8i_dwmac_dump_mac_regs(काष्ठा mac_device_info *hw,
				      u32 *reg_space)
अणु
	पूर्णांक i;
	व्योम __iomem *ioaddr = hw->pcsr;

	क्रम (i = 0; i < 0xC8; i += 4) अणु
		अगर (i == 0x32 || i == 0x3C)
			जारी;
		reg_space[i / 4] = पढ़ोl(ioaddr + i);
	पूर्ण
पूर्ण

अटल व्योम sun8i_dwmac_enable_dma_irq(व्योम __iomem *ioaddr, u32 chan,
				       bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + EMAC_INT_EN);

	अगर (rx)
		value |= EMAC_RX_INT;
	अगर (tx)
		value |= EMAC_TX_INT;

	ग_लिखोl(value, ioaddr + EMAC_INT_EN);
पूर्ण

अटल व्योम sun8i_dwmac_disable_dma_irq(व्योम __iomem *ioaddr, u32 chan,
					bool rx, bool tx)
अणु
	u32 value = पढ़ोl(ioaddr + EMAC_INT_EN);

	अगर (rx)
		value &= ~EMAC_RX_INT;
	अगर (tx)
		value &= ~EMAC_TX_INT;

	ग_लिखोl(value, ioaddr + EMAC_INT_EN);
पूर्ण

अटल व्योम sun8i_dwmac_dma_start_tx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 v;

	v = पढ़ोl(ioaddr + EMAC_TX_CTL1);
	v |= EMAC_TX_DMA_START;
	v |= EMAC_TX_DMA_EN;
	ग_लिखोl(v, ioaddr + EMAC_TX_CTL1);
पूर्ण

अटल व्योम sun8i_dwmac_enable_dma_transmission(व्योम __iomem *ioaddr)
अणु
	u32 v;

	v = पढ़ोl(ioaddr + EMAC_TX_CTL1);
	v |= EMAC_TX_DMA_START;
	v |= EMAC_TX_DMA_EN;
	ग_लिखोl(v, ioaddr + EMAC_TX_CTL1);
पूर्ण

अटल व्योम sun8i_dwmac_dma_stop_tx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 v;

	v = पढ़ोl(ioaddr + EMAC_TX_CTL1);
	v &= ~EMAC_TX_DMA_EN;
	ग_लिखोl(v, ioaddr + EMAC_TX_CTL1);
पूर्ण

अटल व्योम sun8i_dwmac_dma_start_rx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 v;

	v = पढ़ोl(ioaddr + EMAC_RX_CTL1);
	v |= EMAC_RX_DMA_START;
	v |= EMAC_RX_DMA_EN;
	ग_लिखोl(v, ioaddr + EMAC_RX_CTL1);
पूर्ण

अटल व्योम sun8i_dwmac_dma_stop_rx(व्योम __iomem *ioaddr, u32 chan)
अणु
	u32 v;

	v = पढ़ोl(ioaddr + EMAC_RX_CTL1);
	v &= ~EMAC_RX_DMA_EN;
	ग_लिखोl(v, ioaddr + EMAC_RX_CTL1);
पूर्ण

अटल पूर्णांक sun8i_dwmac_dma_पूर्णांकerrupt(व्योम __iomem *ioaddr,
				     काष्ठा sपंचांगmac_extra_stats *x, u32 chan,
				     u32 dir)
अणु
	u32 v;
	पूर्णांक ret = 0;

	v = पढ़ोl(ioaddr + EMAC_INT_STA);

	अगर (dir == DMA_सूची_RX)
		v &= EMAC_INT_MSK_RX;
	अन्यथा अगर (dir == DMA_सूची_TX)
		v &= EMAC_INT_MSK_TX;

	अगर (v & EMAC_TX_INT) अणु
		ret |= handle_tx;
		x->tx_normal_irq_n++;
	पूर्ण

	अगर (v & EMAC_TX_DMA_STOP_INT)
		x->tx_process_stopped_irq++;

	अगर (v & EMAC_TX_BUF_UA_INT)
		x->tx_process_stopped_irq++;

	अगर (v & EMAC_TX_TIMEOUT_INT)
		ret |= tx_hard_error;

	अगर (v & EMAC_TX_UNDERFLOW_INT) अणु
		ret |= tx_hard_error;
		x->tx_undeflow_irq++;
	पूर्ण

	अगर (v & EMAC_TX_EARLY_INT)
		x->tx_early_irq++;

	अगर (v & EMAC_RX_INT) अणु
		ret |= handle_rx;
		x->rx_normal_irq_n++;
	पूर्ण

	अगर (v & EMAC_RX_BUF_UA_INT)
		x->rx_buf_unav_irq++;

	अगर (v & EMAC_RX_DMA_STOP_INT)
		x->rx_process_stopped_irq++;

	अगर (v & EMAC_RX_TIMEOUT_INT)
		ret |= tx_hard_error;

	अगर (v & EMAC_RX_OVERFLOW_INT) अणु
		ret |= tx_hard_error;
		x->rx_overflow_irq++;
	पूर्ण

	अगर (v & EMAC_RX_EARLY_INT)
		x->rx_early_irq++;

	अगर (v & EMAC_RGMII_STA_INT)
		x->irq_rgmii_n++;

	ग_लिखोl(v, ioaddr + EMAC_INT_STA);

	वापस ret;
पूर्ण

अटल व्योम sun8i_dwmac_dma_operation_mode_rx(व्योम __iomem *ioaddr, पूर्णांक mode,
					      u32 channel, पूर्णांक fअगरosz, u8 qmode)
अणु
	u32 v;

	v = पढ़ोl(ioaddr + EMAC_RX_CTL1);
	अगर (mode == SF_DMA_MODE) अणु
		v |= EMAC_RX_MD;
	पूर्ण अन्यथा अणु
		v &= ~EMAC_RX_MD;
		v &= ~EMAC_RX_TH_MASK;
		अगर (mode < 32)
			v |= EMAC_RX_TH_32;
		अन्यथा अगर (mode < 64)
			v |= EMAC_RX_TH_64;
		अन्यथा अगर (mode < 96)
			v |= EMAC_RX_TH_96;
		अन्यथा अगर (mode < 128)
			v |= EMAC_RX_TH_128;
	पूर्ण
	ग_लिखोl(v, ioaddr + EMAC_RX_CTL1);
पूर्ण

अटल व्योम sun8i_dwmac_dma_operation_mode_tx(व्योम __iomem *ioaddr, पूर्णांक mode,
					      u32 channel, पूर्णांक fअगरosz, u8 qmode)
अणु
	u32 v;

	v = पढ़ोl(ioaddr + EMAC_TX_CTL1);
	अगर (mode == SF_DMA_MODE) अणु
		v |= EMAC_TX_MD;
		/* Unकरोcumented bit (called TX_NEXT_FRM in BSP), the original
		 * comment is
		 * "Operating on second frame increase the perक्रमmance
		 * especially when transmit store-and-क्रमward is used."
		 */
		v |= EMAC_TX_NEXT_FRM;
	पूर्ण अन्यथा अणु
		v &= ~EMAC_TX_MD;
		v &= ~EMAC_TX_TH_MASK;
		अगर (mode < 64)
			v |= EMAC_TX_TH_64;
		अन्यथा अगर (mode < 128)
			v |= EMAC_TX_TH_128;
		अन्यथा अगर (mode < 192)
			v |= EMAC_TX_TH_192;
		अन्यथा अगर (mode < 256)
			v |= EMAC_TX_TH_256;
	पूर्ण
	ग_लिखोl(v, ioaddr + EMAC_TX_CTL1);
पूर्ण

अटल स्थिर काष्ठा sपंचांगmac_dma_ops sun8i_dwmac_dma_ops = अणु
	.reset = sun8i_dwmac_dma_reset,
	.init = sun8i_dwmac_dma_init,
	.init_rx_chan = sun8i_dwmac_dma_init_rx,
	.init_tx_chan = sun8i_dwmac_dma_init_tx,
	.dump_regs = sun8i_dwmac_dump_regs,
	.dma_rx_mode = sun8i_dwmac_dma_operation_mode_rx,
	.dma_tx_mode = sun8i_dwmac_dma_operation_mode_tx,
	.enable_dma_transmission = sun8i_dwmac_enable_dma_transmission,
	.enable_dma_irq = sun8i_dwmac_enable_dma_irq,
	.disable_dma_irq = sun8i_dwmac_disable_dma_irq,
	.start_tx = sun8i_dwmac_dma_start_tx,
	.stop_tx = sun8i_dwmac_dma_stop_tx,
	.start_rx = sun8i_dwmac_dma_start_rx,
	.stop_rx = sun8i_dwmac_dma_stop_rx,
	.dma_पूर्णांकerrupt = sun8i_dwmac_dma_पूर्णांकerrupt,
पूर्ण;

अटल पूर्णांक sun8i_dwmac_घातer_पूर्णांकernal_phy(काष्ठा sपंचांगmac_priv *priv);

अटल पूर्णांक sun8i_dwmac_init(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sunxi_priv_data *gmac = priv;
	पूर्णांक ret;

	अगर (gmac->regulator) अणु
		ret = regulator_enable(gmac->regulator);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Fail to enable regulator\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(gmac->tx_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not enable AHB clock\n");
		जाओ err_disable_regulator;
	पूर्ण

	अगर (gmac->use_पूर्णांकernal_phy) अणु
		ret = sun8i_dwmac_घातer_पूर्णांकernal_phy(netdev_priv(ndev));
		अगर (ret)
			जाओ err_disable_clk;
	पूर्ण

	वापस 0;

err_disable_clk:
	clk_disable_unprepare(gmac->tx_clk);
err_disable_regulator:
	अगर (gmac->regulator)
		regulator_disable(gmac->regulator);

	वापस ret;
पूर्ण

अटल व्योम sun8i_dwmac_core_init(काष्ठा mac_device_info *hw,
				  काष्ठा net_device *dev)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 v;

	v = (8 << EMAC_BURSTLEN_SHIFT); /* burst len */
	ग_लिखोl(v, ioaddr + EMAC_BASIC_CTL1);
पूर्ण

अटल व्योम sun8i_dwmac_set_mac(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 t, r;

	t = पढ़ोl(ioaddr + EMAC_TX_CTL0);
	r = पढ़ोl(ioaddr + EMAC_RX_CTL0);
	अगर (enable) अणु
		t |= EMAC_TX_TRANSMITTER_EN;
		r |= EMAC_RX_RECEIVER_EN;
	पूर्ण अन्यथा अणु
		t &= ~EMAC_TX_TRANSMITTER_EN;
		r &= ~EMAC_RX_RECEIVER_EN;
	पूर्ण
	ग_लिखोl(t, ioaddr + EMAC_TX_CTL0);
	ग_लिखोl(r, ioaddr + EMAC_RX_CTL0);
पूर्ण

/* Set MAC address at slot reg_n
 * All slot > 0 need to be enabled with MAC_ADDR_TYPE_DST
 * If addr is शून्य, clear the slot
 */
अटल व्योम sun8i_dwmac_set_umac_addr(काष्ठा mac_device_info *hw,
				      अचिन्हित अक्षर *addr,
				      अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 v;

	अगर (!addr) अणु
		ग_लिखोl(0, ioaddr + EMAC_MACADDR_HI(reg_n));
		वापस;
	पूर्ण

	sपंचांगmac_set_mac_addr(ioaddr, addr, EMAC_MACADDR_HI(reg_n),
			    EMAC_MACADDR_LO(reg_n));
	अगर (reg_n > 0) अणु
		v = पढ़ोl(ioaddr + EMAC_MACADDR_HI(reg_n));
		v |= MAC_ADDR_TYPE_DST;
		ग_लिखोl(v, ioaddr + EMAC_MACADDR_HI(reg_n));
	पूर्ण
पूर्ण

अटल व्योम sun8i_dwmac_get_umac_addr(काष्ठा mac_device_info *hw,
				      अचिन्हित अक्षर *addr,
				      अचिन्हित पूर्णांक reg_n)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;

	sपंचांगmac_get_mac_addr(ioaddr, addr, EMAC_MACADDR_HI(reg_n),
			    EMAC_MACADDR_LO(reg_n));
पूर्ण

/* caution this function must वापस non 0 to work */
अटल पूर्णांक sun8i_dwmac_rx_ipc_enable(काष्ठा mac_device_info *hw)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 v;

	v = पढ़ोl(ioaddr + EMAC_RX_CTL0);
	v |= EMAC_RX_DO_CRC;
	ग_लिखोl(v, ioaddr + EMAC_RX_CTL0);

	वापस 1;
पूर्ण

अटल व्योम sun8i_dwmac_set_filter(काष्ठा mac_device_info *hw,
				   काष्ठा net_device *dev)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 v;
	पूर्णांक i = 1;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक macaddrs = netdev_uc_count(dev) + netdev_mc_count(dev) + 1;

	v = EMAC_FRM_FLT_CTL;

	अगर (dev->flags & IFF_PROMISC) अणु
		v = EMAC_FRM_FLT_RXALL;
	पूर्ण अन्यथा अगर (dev->flags & IFF_ALLMULTI) अणु
		v |= EMAC_FRM_FLT_MULTICAST;
	पूर्ण अन्यथा अगर (macaddrs <= hw->unicast_filter_entries) अणु
		अगर (!netdev_mc_empty(dev)) अणु
			netdev_क्रम_each_mc_addr(ha, dev) अणु
				sun8i_dwmac_set_umac_addr(hw, ha->addr, i);
				i++;
			पूर्ण
		पूर्ण
		अगर (!netdev_uc_empty(dev)) अणु
			netdev_क्रम_each_uc_addr(ha, dev) अणु
				sun8i_dwmac_set_umac_addr(hw, ha->addr, i);
				i++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(पढ़ोl(ioaddr + EMAC_RX_FRM_FLT) & EMAC_FRM_FLT_RXALL))
			netdev_info(dev, "Too many address, switching to promiscuous\n");
		v = EMAC_FRM_FLT_RXALL;
	पूर्ण

	/* Disable unused address filter slots */
	जबतक (i < hw->unicast_filter_entries)
		sun8i_dwmac_set_umac_addr(hw, शून्य, i++);

	ग_लिखोl(v, ioaddr + EMAC_RX_FRM_FLT);
पूर्ण

अटल व्योम sun8i_dwmac_flow_ctrl(काष्ठा mac_device_info *hw,
				  अचिन्हित पूर्णांक duplex, अचिन्हित पूर्णांक fc,
				  अचिन्हित पूर्णांक छोड़ो_समय, u32 tx_cnt)
अणु
	व्योम __iomem *ioaddr = hw->pcsr;
	u32 v;

	v = पढ़ोl(ioaddr + EMAC_RX_CTL0);
	अगर (fc == FLOW_AUTO)
		v |= EMAC_RX_FLOW_CTL_EN;
	अन्यथा
		v &= ~EMAC_RX_FLOW_CTL_EN;
	ग_लिखोl(v, ioaddr + EMAC_RX_CTL0);

	v = पढ़ोl(ioaddr + EMAC_TX_FLOW_CTL);
	अगर (fc == FLOW_AUTO)
		v |= EMAC_TX_FLOW_CTL_EN;
	अन्यथा
		v &= ~EMAC_TX_FLOW_CTL_EN;
	ग_लिखोl(v, ioaddr + EMAC_TX_FLOW_CTL);
पूर्ण

अटल पूर्णांक sun8i_dwmac_reset(काष्ठा sपंचांगmac_priv *priv)
अणु
	u32 v;
	पूर्णांक err;

	v = पढ़ोl(priv->ioaddr + EMAC_BASIC_CTL1);
	ग_लिखोl(v | 0x01, priv->ioaddr + EMAC_BASIC_CTL1);

	/* The समयout was previoulsy set to 10ms, but some board (OrangePI0)
	 * need more अगर no cable plugged. 100ms seems OK
	 */
	err = पढ़ोl_poll_समयout(priv->ioaddr + EMAC_BASIC_CTL1, v,
				 !(v & 0x01), 100, 100000);

	अगर (err) अणु
		dev_err(priv->device, "EMAC reset timeout\n");
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/* Search in mdio-mux node क्रम पूर्णांकernal PHY node and get its clk/reset */
अटल पूर्णांक get_ephy_nodes(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा sunxi_priv_data *gmac = priv->plat->bsp_priv;
	काष्ठा device_node *mdio_mux, *iphynode;
	काष्ठा device_node *mdio_पूर्णांकernal;
	पूर्णांक ret;

	mdio_mux = of_get_child_by_name(priv->device->of_node, "mdio-mux");
	अगर (!mdio_mux) अणु
		dev_err(priv->device, "Cannot get mdio-mux node\n");
		वापस -ENODEV;
	पूर्ण

	mdio_पूर्णांकernal = of_get_compatible_child(mdio_mux,
						"allwinner,sun8i-h3-mdio-internal");
	of_node_put(mdio_mux);
	अगर (!mdio_पूर्णांकernal) अणु
		dev_err(priv->device, "Cannot get internal_mdio node\n");
		वापस -ENODEV;
	पूर्ण

	/* Seek क्रम पूर्णांकernal PHY */
	क्रम_each_child_of_node(mdio_पूर्णांकernal, iphynode) अणु
		gmac->ephy_clk = of_clk_get(iphynode, 0);
		अगर (IS_ERR(gmac->ephy_clk))
			जारी;
		gmac->rst_ephy = of_reset_control_get_exclusive(iphynode, शून्य);
		अगर (IS_ERR(gmac->rst_ephy)) अणु
			ret = PTR_ERR(gmac->rst_ephy);
			अगर (ret == -EPROBE_DEFER) अणु
				of_node_put(iphynode);
				of_node_put(mdio_पूर्णांकernal);
				वापस ret;
			पूर्ण
			जारी;
		पूर्ण
		dev_info(priv->device, "Found internal PHY node\n");
		of_node_put(iphynode);
		of_node_put(mdio_पूर्णांकernal);
		वापस 0;
	पूर्ण

	of_node_put(mdio_पूर्णांकernal);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक sun8i_dwmac_घातer_पूर्णांकernal_phy(काष्ठा sपंचांगmac_priv *priv)
अणु
	काष्ठा sunxi_priv_data *gmac = priv->plat->bsp_priv;
	पूर्णांक ret;

	अगर (gmac->पूर्णांकernal_phy_घातered) अणु
		dev_warn(priv->device, "Internal PHY already powered\n");
		वापस 0;
	पूर्ण

	dev_info(priv->device, "Powering internal PHY\n");
	ret = clk_prepare_enable(gmac->ephy_clk);
	अगर (ret) अणु
		dev_err(priv->device, "Cannot enable internal PHY\n");
		वापस ret;
	पूर्ण

	/* Make sure the EPHY is properly reseted, as U-Boot may leave
	 * it at deनिश्चितed state, and thus it may fail to reset EMAC.
	 *
	 * This assumes the driver has exclusive access to the EPHY reset.
	 */
	ret = reset_control_reset(gmac->rst_ephy);
	अगर (ret) अणु
		dev_err(priv->device, "Cannot reset internal PHY\n");
		clk_disable_unprepare(gmac->ephy_clk);
		वापस ret;
	पूर्ण

	gmac->पूर्णांकernal_phy_घातered = true;

	वापस 0;
पूर्ण

अटल व्योम sun8i_dwmac_unघातer_पूर्णांकernal_phy(काष्ठा sunxi_priv_data *gmac)
अणु
	अगर (!gmac->पूर्णांकernal_phy_घातered)
		वापस;

	clk_disable_unprepare(gmac->ephy_clk);
	reset_control_निश्चित(gmac->rst_ephy);
	gmac->पूर्णांकernal_phy_घातered = false;
पूर्ण

/* MDIO multiplexing चयन function
 * This function is called by the mdio-mux layer when it thinks the mdio bus
 * multiplexer needs to चयन.
 * 'current_child' is the current value of the mux रेजिस्टर
 * 'desired_child' is the value of the 'reg' property of the target child MDIO
 * node.
 * The first समय this function is called, current_child == -1.
 * If current_child == desired_child, then the mux is alपढ़ोy set to the
 * correct bus.
 */
अटल पूर्णांक mdio_mux_syscon_चयन_fn(पूर्णांक current_child, पूर्णांक desired_child,
				     व्योम *data)
अणु
	काष्ठा sपंचांगmac_priv *priv = data;
	काष्ठा sunxi_priv_data *gmac = priv->plat->bsp_priv;
	u32 reg, val;
	पूर्णांक ret = 0;

	अगर (current_child ^ desired_child) अणु
		regmap_field_पढ़ो(gmac->regmap_field, &reg);
		चयन (desired_child) अणु
		हाल DWMAC_SUN8I_MDIO_MUX_INTERNAL_ID:
			dev_info(priv->device, "Switch mux to internal PHY");
			val = (reg & ~H3_EPHY_MUX_MASK) | H3_EPHY_SELECT;
			gmac->use_पूर्णांकernal_phy = true;
			अवरोध;
		हाल DWMAC_SUN8I_MDIO_MUX_EXTERNAL_ID:
			dev_info(priv->device, "Switch mux to external PHY");
			val = (reg & ~H3_EPHY_MUX_MASK) | H3_EPHY_SHUTDOWN;
			gmac->use_पूर्णांकernal_phy = false;
			अवरोध;
		शेष:
			dev_err(priv->device, "Invalid child ID %x\n",
				desired_child);
			वापस -EINVAL;
		पूर्ण
		regmap_field_ग_लिखो(gmac->regmap_field, val);
		अगर (gmac->use_पूर्णांकernal_phy) अणु
			ret = sun8i_dwmac_घातer_पूर्णांकernal_phy(priv);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			sun8i_dwmac_unघातer_पूर्णांकernal_phy(gmac);
		पूर्ण
		/* After changing syscon value, the MAC need reset or it will
		 * use the last value (and so the last PHY set).
		 */
		ret = sun8i_dwmac_reset(priv);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sun8i_dwmac_रेजिस्टर_mdio_mux(काष्ठा sपंचांगmac_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा device_node *mdio_mux;
	काष्ठा sunxi_priv_data *gmac = priv->plat->bsp_priv;

	mdio_mux = of_get_child_by_name(priv->device->of_node, "mdio-mux");
	अगर (!mdio_mux)
		वापस -ENODEV;

	ret = mdio_mux_init(priv->device, mdio_mux, mdio_mux_syscon_चयन_fn,
			    &gmac->mux_handle, priv, priv->mii);
	वापस ret;
पूर्ण

अटल पूर्णांक sun8i_dwmac_set_syscon(काष्ठा device *dev,
				  काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	काष्ठा sunxi_priv_data *gmac = plat->bsp_priv;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक ret;
	u32 reg, val;

	ret = regmap_field_पढ़ो(gmac->regmap_field, &val);
	अगर (ret) अणु
		dev_err(dev, "Fail to read from regmap field.\n");
		वापस ret;
	पूर्ण

	reg = gmac->variant->शेष_syscon_value;
	अगर (reg != val)
		dev_warn(dev,
			 "Current syscon value is not the default %x (expect %x)\n",
			 val, reg);

	अगर (gmac->variant->soc_has_पूर्णांकernal_phy) अणु
		अगर (of_property_पढ़ो_bool(node, "allwinner,leds-active-low"))
			reg |= H3_EPHY_LED_POL;
		अन्यथा
			reg &= ~H3_EPHY_LED_POL;

		/* Force EPHY xtal frequency to 24MHz. */
		reg |= H3_EPHY_CLK_SEL;

		ret = of_mdio_parse_addr(dev, plat->phy_node);
		अगर (ret < 0) अणु
			dev_err(dev, "Could not parse MDIO addr\n");
			वापस ret;
		पूर्ण
		/* of_mdio_parse_addr वापसs a valid (0 ~ 31) PHY
		 * address. No need to mask it again.
		 */
		reg |= 1 << H3_EPHY_ADDR_SHIFT;
	पूर्ण अन्यथा अणु
		/* For SoCs without पूर्णांकernal PHY the PHY selection bit should be
		 * set to 0 (बाह्यal PHY).
		 */
		reg &= ~H3_EPHY_SELECT;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(node, "allwinner,tx-delay-ps", &val)) अणु
		अगर (val % 100) अणु
			dev_err(dev, "tx-delay must be a multiple of 100\n");
			वापस -EINVAL;
		पूर्ण
		val /= 100;
		dev_dbg(dev, "set tx-delay to %x\n", val);
		अगर (val <= gmac->variant->tx_delay_max) अणु
			reg &= ~(gmac->variant->tx_delay_max <<
				 SYSCON_ETXDC_SHIFT);
			reg |= (val << SYSCON_ETXDC_SHIFT);
		पूर्ण अन्यथा अणु
			dev_err(dev, "Invalid TX clock delay: %d\n",
				val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!of_property_पढ़ो_u32(node, "allwinner,rx-delay-ps", &val)) अणु
		अगर (val % 100) अणु
			dev_err(dev, "rx-delay must be a multiple of 100\n");
			वापस -EINVAL;
		पूर्ण
		val /= 100;
		dev_dbg(dev, "set rx-delay to %x\n", val);
		अगर (val <= gmac->variant->rx_delay_max) अणु
			reg &= ~(gmac->variant->rx_delay_max <<
				 SYSCON_ERXDC_SHIFT);
			reg |= (val << SYSCON_ERXDC_SHIFT);
		पूर्ण अन्यथा अणु
			dev_err(dev, "Invalid RX clock delay: %d\n",
				val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Clear पूर्णांकerface mode bits */
	reg &= ~(SYSCON_ETCS_MASK | SYSCON_EPIT);
	अगर (gmac->variant->support_rmii)
		reg &= ~SYSCON_RMII_EN;

	चयन (plat->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_MII:
		/* शेष */
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		reg |= SYSCON_EPIT | SYSCON_ETCS_INT_GMII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		reg |= SYSCON_RMII_EN | SYSCON_ETCS_EXT_GMII;
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported interface mode: %s",
			phy_modes(plat->पूर्णांकerface));
		वापस -EINVAL;
	पूर्ण

	regmap_field_ग_लिखो(gmac->regmap_field, reg);

	वापस 0;
पूर्ण

अटल व्योम sun8i_dwmac_unset_syscon(काष्ठा sunxi_priv_data *gmac)
अणु
	u32 reg = gmac->variant->शेष_syscon_value;

	regmap_field_ग_लिखो(gmac->regmap_field, reg);
पूर्ण

अटल व्योम sun8i_dwmac_निकास(काष्ठा platक्रमm_device *pdev, व्योम *priv)
अणु
	काष्ठा sunxi_priv_data *gmac = priv;

	अगर (gmac->variant->soc_has_पूर्णांकernal_phy)
		sun8i_dwmac_unघातer_पूर्णांकernal_phy(gmac);

	clk_disable_unprepare(gmac->tx_clk);

	अगर (gmac->regulator)
		regulator_disable(gmac->regulator);
पूर्ण

अटल व्योम sun8i_dwmac_set_mac_loopback(व्योम __iomem *ioaddr, bool enable)
अणु
	u32 value = पढ़ोl(ioaddr + EMAC_BASIC_CTL0);

	अगर (enable)
		value |= EMAC_LOOPBACK;
	अन्यथा
		value &= ~EMAC_LOOPBACK;

	ग_लिखोl(value, ioaddr + EMAC_BASIC_CTL0);
पूर्ण

अटल स्थिर काष्ठा sपंचांगmac_ops sun8i_dwmac_ops = अणु
	.core_init = sun8i_dwmac_core_init,
	.set_mac = sun8i_dwmac_set_mac,
	.dump_regs = sun8i_dwmac_dump_mac_regs,
	.rx_ipc = sun8i_dwmac_rx_ipc_enable,
	.set_filter = sun8i_dwmac_set_filter,
	.flow_ctrl = sun8i_dwmac_flow_ctrl,
	.set_umac_addr = sun8i_dwmac_set_umac_addr,
	.get_umac_addr = sun8i_dwmac_get_umac_addr,
	.set_mac_loopback = sun8i_dwmac_set_mac_loopback,
पूर्ण;

अटल काष्ठा mac_device_info *sun8i_dwmac_setup(व्योम *ppriv)
अणु
	काष्ठा mac_device_info *mac;
	काष्ठा sपंचांगmac_priv *priv = ppriv;

	mac = devm_kzalloc(priv->device, माप(*mac), GFP_KERNEL);
	अगर (!mac)
		वापस शून्य;

	mac->pcsr = priv->ioaddr;
	mac->mac = &sun8i_dwmac_ops;
	mac->dma = &sun8i_dwmac_dma_ops;

	priv->dev->priv_flags |= IFF_UNICAST_FLT;

	/* The loopback bit seems to be re-set when link change
	 * Simply mask it each समय
	 * Speed 10/100/1000 are set in BIT(2)/BIT(3)
	 */
	mac->link.speed_mask = GENMASK(3, 2) | EMAC_LOOPBACK;
	mac->link.speed10 = EMAC_SPEED_10;
	mac->link.speed100 = EMAC_SPEED_100;
	mac->link.speed1000 = EMAC_SPEED_1000;
	mac->link.duplex = EMAC_DUPLEX_FULL;
	mac->mii.addr = EMAC_MDIO_CMD;
	mac->mii.data = EMAC_MDIO_DATA;
	mac->mii.reg_shअगरt = 4;
	mac->mii.reg_mask = GENMASK(8, 4);
	mac->mii.addr_shअगरt = 12;
	mac->mii.addr_mask = GENMASK(16, 12);
	mac->mii.clk_csr_shअगरt = 20;
	mac->mii.clk_csr_mask = GENMASK(22, 20);
	mac->unicast_filter_entries = 8;

	/* Synopsys Id is not available */
	priv->synopsys_id = 0;

	वापस mac;
पूर्ण

अटल काष्ठा regmap *sun8i_dwmac_get_syscon_from_dev(काष्ठा device_node *node)
अणु
	काष्ठा device_node *syscon_node;
	काष्ठा platक्रमm_device *syscon_pdev;
	काष्ठा regmap *regmap = शून्य;

	syscon_node = of_parse_phandle(node, "syscon", 0);
	अगर (!syscon_node)
		वापस ERR_PTR(-ENODEV);

	syscon_pdev = of_find_device_by_node(syscon_node);
	अगर (!syscon_pdev) अणु
		/* platक्रमm device might not be probed yet */
		regmap = ERR_PTR(-EPROBE_DEFER);
		जाओ out_put_node;
	पूर्ण

	/* If no regmap is found then the other device driver is at fault */
	regmap = dev_get_regmap(&syscon_pdev->dev, शून्य);
	अगर (!regmap)
		regmap = ERR_PTR(-EINVAL);

	platक्रमm_device_put(syscon_pdev);
out_put_node:
	of_node_put(syscon_node);
	वापस regmap;
पूर्ण

अटल पूर्णांक sun8i_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा sunxi_priv_data *gmac;
	काष्ठा device *dev = &pdev->dev;
	phy_पूर्णांकerface_t पूर्णांकerface;
	पूर्णांक ret;
	काष्ठा sपंचांगmac_priv *priv;
	काष्ठा net_device *ndev;
	काष्ठा regmap *regmap;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	gmac = devm_kzalloc(dev, माप(*gmac), GFP_KERNEL);
	अगर (!gmac)
		वापस -ENOMEM;

	gmac->variant = of_device_get_match_data(&pdev->dev);
	अगर (!gmac->variant) अणु
		dev_err(&pdev->dev, "Missing dwmac-sun8i variant\n");
		वापस -EINVAL;
	पूर्ण

	gmac->tx_clk = devm_clk_get(dev, "stmmaceth");
	अगर (IS_ERR(gmac->tx_clk)) अणु
		dev_err(dev, "Could not get TX clock\n");
		वापस PTR_ERR(gmac->tx_clk);
	पूर्ण

	/* Optional regulator क्रम PHY */
	gmac->regulator = devm_regulator_get_optional(dev, "phy");
	अगर (IS_ERR(gmac->regulator)) अणु
		अगर (PTR_ERR(gmac->regulator) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_info(dev, "No regulator found\n");
		gmac->regulator = शून्य;
	पूर्ण

	/* The "GMAC clock control" रेजिस्टर might be located in the
	 * CCU address range (on the R40), or the प्रणाली control address
	 * range (on most other sun8i and later SoCs).
	 *
	 * The क्रमmer controls most अगर not all घड़ीs in the SoC. The
	 * latter has an SoC identअगरication रेजिस्टर, and on some SoCs,
	 * controls to map device specअगरic SRAM to either the पूर्णांकended
	 * peripheral, or the CPU address space.
	 *
	 * In either हाल, there should be a coordinated and restricted
	 * method of accessing the रेजिस्टर needed here. This is करोne by
	 * having the device export a custom regmap, instead of a generic
	 * syscon, which grants all access to all रेजिस्टरs.
	 *
	 * To support old device trees, we fall back to using the syscon
	 * पूर्णांकerface अगर possible.
	 */
	regmap = sun8i_dwmac_get_syscon_from_dev(pdev->dev.of_node);
	अगर (IS_ERR(regmap))
		regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							 "syscon");
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&pdev->dev, "Unable to map syscon: %d\n", ret);
		वापस ret;
	पूर्ण

	gmac->regmap_field = devm_regmap_field_alloc(dev, regmap,
						     *gmac->variant->syscon_field);
	अगर (IS_ERR(gmac->regmap_field)) अणु
		ret = PTR_ERR(gmac->regmap_field);
		dev_err(dev, "Unable to map syscon register: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_get_phy_mode(dev->of_node, &पूर्णांकerface);
	अगर (ret)
		वापस -EINVAL;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	/* platक्रमm data specअगरying hardware features and callbacks.
	 * hardware features were copied from Allwinner drivers.
	 */
	plat_dat->पूर्णांकerface = पूर्णांकerface;
	plat_dat->rx_coe = STMMAC_RX_COE_TYPE2;
	plat_dat->tx_coe = 1;
	plat_dat->has_sun8i = true;
	plat_dat->bsp_priv = gmac;
	plat_dat->init = sun8i_dwmac_init;
	plat_dat->निकास = sun8i_dwmac_निकास;
	plat_dat->setup = sun8i_dwmac_setup;
	plat_dat->tx_fअगरo_size = 4096;
	plat_dat->rx_fअगरo_size = 16384;

	ret = sun8i_dwmac_set_syscon(&pdev->dev, plat_dat);
	अगर (ret)
		जाओ dwmac_deconfig;

	ret = sun8i_dwmac_init(pdev, plat_dat->bsp_priv);
	अगर (ret)
		जाओ dwmac_syscon;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ dwmac_निकास;

	ndev = dev_get_drvdata(&pdev->dev);
	priv = netdev_priv(ndev);

	/* The mux must be रेजिस्टरed after parent MDIO
	 * so after sपंचांगmac_dvr_probe()
	 */
	अगर (gmac->variant->soc_has_पूर्णांकernal_phy) अणु
		ret = get_ephy_nodes(priv);
		अगर (ret)
			जाओ dwmac_हटाओ;
		ret = sun8i_dwmac_रेजिस्टर_mdio_mux(priv);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to register mux\n");
			जाओ dwmac_mux;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = sun8i_dwmac_reset(priv);
		अगर (ret)
			जाओ dwmac_हटाओ;
	पूर्ण

	वापस 0;

dwmac_mux:
	reset_control_put(gmac->rst_ephy);
	clk_put(gmac->ephy_clk);
dwmac_हटाओ:
	sपंचांगmac_dvr_हटाओ(&pdev->dev);
dwmac_निकास:
	sun8i_dwmac_निकास(pdev, gmac);
dwmac_syscon:
	sun8i_dwmac_unset_syscon(gmac);
dwmac_deconfig:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल पूर्णांक sun8i_dwmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	काष्ठा sunxi_priv_data *gmac = priv->plat->bsp_priv;

	अगर (gmac->variant->soc_has_पूर्णांकernal_phy) अणु
		mdio_mux_uninit(gmac->mux_handle);
		sun8i_dwmac_unघातer_पूर्णांकernal_phy(gmac);
		reset_control_put(gmac->rst_ephy);
		clk_put(gmac->ephy_clk);
	पूर्ण

	sपंचांगmac_pltfr_हटाओ(pdev);
	sun8i_dwmac_unset_syscon(gmac);

	वापस 0;
पूर्ण

अटल व्योम sun8i_dwmac_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);
	काष्ठा sunxi_priv_data *gmac = priv->plat->bsp_priv;

	sun8i_dwmac_निकास(pdev, gmac);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun8i_dwmac_match[] = अणु
	अणु .compatible = "allwinner,sun8i-h3-emac",
		.data = &emac_variant_h3 पूर्ण,
	अणु .compatible = "allwinner,sun8i-v3s-emac",
		.data = &emac_variant_v3s पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-emac",
		.data = &emac_variant_a83t पूर्ण,
	अणु .compatible = "allwinner,sun8i-r40-gmac",
		.data = &emac_variant_r40 पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-emac",
		.data = &emac_variant_a64 पूर्ण,
	अणु .compatible = "allwinner,sun50i-h6-emac",
		.data = &emac_variant_h6 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun8i_dwmac_match);

अटल काष्ठा platक्रमm_driver sun8i_dwmac_driver = अणु
	.probe  = sun8i_dwmac_probe,
	.हटाओ = sun8i_dwmac_हटाओ,
	.shutकरोwn = sun8i_dwmac_shutकरोwn,
	.driver = अणु
		.name           = "dwmac-sun8i",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = sun8i_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun8i_dwmac_driver);

MODULE_AUTHOR("Corentin Labbe <clabbe.montjoie@gmail.com>");
MODULE_DESCRIPTION("Allwinner sun8i DWMAC specific glue layer");
MODULE_LICENSE("GPL");
