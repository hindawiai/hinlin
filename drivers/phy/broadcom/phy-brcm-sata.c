<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom SATA3 AHCI Controller PHY Driver
 *
 * Copyright (C) 2016 Broadcom
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा SATA_PCB_BANK_OFFSET				0x23c
#घोषणा SATA_PCB_REG_OFFSET(ofs)			((ofs) * 4)

#घोषणा MAX_PORTS					2

/* Register offset between PHYs in PCB space */
#घोषणा SATA_PCB_REG_28NM_SPACE_SIZE			0x1000

/* The older SATA PHY रेजिस्टरs duplicated per port रेजिस्टरs within the map,
 * rather than having a separate map per port.
 */
#घोषणा SATA_PCB_REG_40NM_SPACE_SIZE			0x10

/* Register offset between PHYs in PHY control space */
#घोषणा SATA_PHY_CTRL_REG_28NM_SPACE_SIZE		0x8

क्रमागत brcm_sata_phy_version अणु
	BRCM_SATA_PHY_STB_16NM,
	BRCM_SATA_PHY_STB_28NM,
	BRCM_SATA_PHY_STB_40NM,
	BRCM_SATA_PHY_IPROC_NS2,
	BRCM_SATA_PHY_IPROC_NSP,
	BRCM_SATA_PHY_IPROC_SR,
	BRCM_SATA_PHY_DSL_28NM,
पूर्ण;

क्रमागत brcm_sata_phy_rxaeq_mode अणु
	RXAEQ_MODE_OFF = 0,
	RXAEQ_MODE_AUTO,
	RXAEQ_MODE_MANUAL,
पूर्ण;

अटल क्रमागत brcm_sata_phy_rxaeq_mode rxaeq_to_val(स्थिर अक्षर *m)
अणु
	अगर (!म_भेद(m, "auto"))
		वापस RXAEQ_MODE_AUTO;
	अन्यथा अगर (!म_भेद(m, "manual"))
		वापस RXAEQ_MODE_MANUAL;
	अन्यथा
		वापस RXAEQ_MODE_OFF;
पूर्ण

काष्ठा brcm_sata_port अणु
	पूर्णांक portnum;
	काष्ठा phy *phy;
	काष्ठा brcm_sata_phy *phy_priv;
	bool ssc_en;
	क्रमागत brcm_sata_phy_rxaeq_mode rxaeq_mode;
	u32 rxaeq_val;
	u32 tx_amplitude_val;
पूर्ण;

काष्ठा brcm_sata_phy अणु
	काष्ठा device *dev;
	व्योम __iomem *phy_base;
	व्योम __iomem *ctrl_base;
	क्रमागत brcm_sata_phy_version version;

	काष्ठा brcm_sata_port phys[MAX_PORTS];
पूर्ण;

क्रमागत sata_phy_regs अणु
	BLOCK0_REG_BANK				= 0x000,
	BLOCK0_XGXSSTATUS			= 0x81,
	BLOCK0_XGXSSTATUS_PLL_LOCK		= BIT(12),
	BLOCK0_SPARE				= 0x8d,
	BLOCK0_SPARE_OOB_CLK_SEL_MASK		= 0x3,
	BLOCK0_SPARE_OOB_CLK_SEL_REFBY2		= 0x1,

	BLOCK1_REG_BANK				= 0x10,
	BLOCK1_TEST_TX				= 0x83,
	BLOCK1_TEST_TX_AMP_SHIFT		= 12,

	PLL_REG_BANK_0				= 0x050,
	PLL_REG_BANK_0_PLLCONTROL_0		= 0x81,
	PLLCONTROL_0_FREQ_DET_RESTART		= BIT(13),
	PLLCONTROL_0_FREQ_MONITOR		= BIT(12),
	PLLCONTROL_0_SEQ_START			= BIT(15),
	PLL_CAP_CHARGE_TIME			= 0x83,
	PLL_VCO_CAL_THRESH			= 0x84,
	PLL_CAP_CONTROL				= 0x85,
	PLL_FREQ_DET_TIME			= 0x86,
	PLL_ACTRL2				= 0x8b,
	PLL_ACTRL2_SELDIV_MASK			= 0x1f,
	PLL_ACTRL2_SELDIV_SHIFT			= 9,
	PLL_ACTRL6				= 0x86,

	PLL1_REG_BANK				= 0x060,
	PLL1_ACTRL2				= 0x82,
	PLL1_ACTRL3				= 0x83,
	PLL1_ACTRL4				= 0x84,
	PLL1_ACTRL5				= 0x85,
	PLL1_ACTRL6				= 0x86,
	PLL1_ACTRL7				= 0x87,
	PLL1_ACTRL8				= 0x88,

	TX_REG_BANK				= 0x070,
	TX_ACTRL0				= 0x80,
	TX_ACTRL0_TXPOL_FLIP			= BIT(6),
	TX_ACTRL5				= 0x85,
	TX_ACTRL5_SSC_EN			= BIT(11),

	AEQRX_REG_BANK_0			= 0xd0,
	AEQ_CONTROL1				= 0x81,
	AEQ_CONTROL1_ENABLE			= BIT(2),
	AEQ_CONTROL1_FREEZE			= BIT(3),
	AEQ_FRC_EQ				= 0x83,
	AEQ_FRC_EQ_FORCE			= BIT(0),
	AEQ_FRC_EQ_FORCE_VAL			= BIT(1),
	AEQ_RFZ_FRC_VAL				= BIT(8),
	AEQRX_REG_BANK_1			= 0xe0,
	AEQRX_SLCAL0_CTRL0			= 0x82,
	AEQRX_SLCAL1_CTRL0			= 0x86,

	OOB_REG_BANK				= 0x150,
	OOB1_REG_BANK				= 0x160,
	OOB_CTRL1				= 0x80,
	OOB_CTRL1_BURST_MAX_MASK		= 0xf,
	OOB_CTRL1_BURST_MAX_SHIFT		= 12,
	OOB_CTRL1_BURST_MIN_MASK		= 0xf,
	OOB_CTRL1_BURST_MIN_SHIFT		= 8,
	OOB_CTRL1_WAKE_IDLE_MAX_MASK		= 0xf,
	OOB_CTRL1_WAKE_IDLE_MAX_SHIFT		= 4,
	OOB_CTRL1_WAKE_IDLE_MIN_MASK		= 0xf,
	OOB_CTRL1_WAKE_IDLE_MIN_SHIFT		= 0,
	OOB_CTRL2				= 0x81,
	OOB_CTRL2_SEL_ENA_SHIFT			= 15,
	OOB_CTRL2_SEL_ENA_RC_SHIFT		= 14,
	OOB_CTRL2_RESET_IDLE_MAX_MASK		= 0x3f,
	OOB_CTRL2_RESET_IDLE_MAX_SHIFT		= 8,
	OOB_CTRL2_BURST_CNT_MASK		= 0x3,
	OOB_CTRL2_BURST_CNT_SHIFT		= 6,
	OOB_CTRL2_RESET_IDLE_MIN_MASK		= 0x3f,
	OOB_CTRL2_RESET_IDLE_MIN_SHIFT		= 0,

	TXPMD_REG_BANK				= 0x1a0,
	TXPMD_CONTROL1				= 0x81,
	TXPMD_CONTROL1_TX_SSC_EN_FRC		= BIT(0),
	TXPMD_CONTROL1_TX_SSC_EN_FRC_VAL	= BIT(1),
	TXPMD_TX_FREQ_CTRL_CONTROL1		= 0x82,
	TXPMD_TX_FREQ_CTRL_CONTROL2		= 0x83,
	TXPMD_TX_FREQ_CTRL_CONTROL2_FMIN_MASK	= 0x3ff,
	TXPMD_TX_FREQ_CTRL_CONTROL3		= 0x84,
	TXPMD_TX_FREQ_CTRL_CONTROL3_FMAX_MASK	= 0x3ff,

	RXPMD_REG_BANK				= 0x1c0,
	RXPMD_RX_CDR_CONTROL1			= 0x81,
	RXPMD_RX_PPM_VAL_MASK			= 0x1ff,
	RXPMD_RXPMD_EN_FRC			= BIT(12),
	RXPMD_RXPMD_EN_FRC_VAL			= BIT(13),
	RXPMD_RX_CDR_CDR_PROP_BW		= 0x82,
	RXPMD_G_CDR_PROP_BW_MASK		= 0x7,
	RXPMD_G1_CDR_PROP_BW_SHIFT		= 0,
	RXPMD_G2_CDR_PROP_BW_SHIFT		= 3,
	RXPMD_G3_CDR_PROB_BW_SHIFT		= 6,
	RXPMD_RX_CDR_CDR_ACQ_INTEG_BW		= 0x83,
	RXPMD_G_CDR_ACQ_INT_BW_MASK		= 0x7,
	RXPMD_G1_CDR_ACQ_INT_BW_SHIFT		= 0,
	RXPMD_G2_CDR_ACQ_INT_BW_SHIFT		= 3,
	RXPMD_G3_CDR_ACQ_INT_BW_SHIFT		= 6,
	RXPMD_RX_CDR_CDR_LOCK_INTEG_BW		= 0x84,
	RXPMD_G_CDR_LOCK_INT_BW_MASK		= 0x7,
	RXPMD_G1_CDR_LOCK_INT_BW_SHIFT		= 0,
	RXPMD_G2_CDR_LOCK_INT_BW_SHIFT		= 3,
	RXPMD_G3_CDR_LOCK_INT_BW_SHIFT		= 6,
	RXPMD_RX_FREQ_MON_CONTROL1		= 0x87,
	RXPMD_MON_CORRECT_EN			= BIT(8),
	RXPMD_MON_MARGIN_VAL_MASK		= 0xff,
पूर्ण;

क्रमागत sata_phy_ctrl_regs अणु
	PHY_CTRL_1				= 0x0,
	PHY_CTRL_1_RESET			= BIT(0),
पूर्ण;

अटल अंतरभूत व्योम __iomem *brcm_sata_ctrl_base(काष्ठा brcm_sata_port *port)
अणु
	काष्ठा brcm_sata_phy *priv = port->phy_priv;
	u32 size = 0;

	चयन (priv->version) अणु
	हाल BRCM_SATA_PHY_IPROC_NS2:
		size = SATA_PHY_CTRL_REG_28NM_SPACE_SIZE;
		अवरोध;
	शेष:
		dev_err(priv->dev, "invalid phy version\n");
		अवरोध;
	पूर्ण

	वापस priv->ctrl_base + (port->portnum * size);
पूर्ण

अटल व्योम brcm_sata_phy_wr(काष्ठा brcm_sata_port *port, u32 bank,
			     u32 ofs, u32 msk, u32 value)
अणु
	काष्ठा brcm_sata_phy *priv = port->phy_priv;
	व्योम __iomem *pcb_base = priv->phy_base;
	u32 पंचांगp;

	अगर (priv->version == BRCM_SATA_PHY_STB_40NM)
		bank += (port->portnum * SATA_PCB_REG_40NM_SPACE_SIZE);
	अन्यथा
		pcb_base += (port->portnum * SATA_PCB_REG_28NM_SPACE_SIZE);

	ग_लिखोl(bank, pcb_base + SATA_PCB_BANK_OFFSET);
	पंचांगp = पढ़ोl(pcb_base + SATA_PCB_REG_OFFSET(ofs));
	पंचांगp = (पंचांगp & msk) | value;
	ग_लिखोl(पंचांगp, pcb_base + SATA_PCB_REG_OFFSET(ofs));
पूर्ण

अटल u32 brcm_sata_phy_rd(काष्ठा brcm_sata_port *port, u32 bank, u32 ofs)
अणु
	काष्ठा brcm_sata_phy *priv = port->phy_priv;
	व्योम __iomem *pcb_base = priv->phy_base;

	अगर (priv->version == BRCM_SATA_PHY_STB_40NM)
		bank += (port->portnum * SATA_PCB_REG_40NM_SPACE_SIZE);
	अन्यथा
		pcb_base += (port->portnum * SATA_PCB_REG_28NM_SPACE_SIZE);

	ग_लिखोl(bank, pcb_base + SATA_PCB_BANK_OFFSET);
	वापस पढ़ोl(pcb_base + SATA_PCB_REG_OFFSET(ofs));
पूर्ण

/* These शेषs were अक्षरacterized by H/W group */
#घोषणा STB_FMIN_VAL_DEFAULT	0x3df
#घोषणा STB_FMAX_VAL_DEFAULT	0x3df
#घोषणा STB_FMAX_VAL_SSC	0x83

अटल व्योम brcm_stb_sata_ssc_init(काष्ठा brcm_sata_port *port)
अणु
	काष्ठा brcm_sata_phy *priv = port->phy_priv;
	u32 पंचांगp;

	/* override the TX spपढ़ो spectrum setting */
	पंचांगp = TXPMD_CONTROL1_TX_SSC_EN_FRC_VAL | TXPMD_CONTROL1_TX_SSC_EN_FRC;
	brcm_sata_phy_wr(port, TXPMD_REG_BANK, TXPMD_CONTROL1, ~पंचांगp, पंचांगp);

	/* set fixed min freq */
	brcm_sata_phy_wr(port, TXPMD_REG_BANK, TXPMD_TX_FREQ_CTRL_CONTROL2,
			 ~TXPMD_TX_FREQ_CTRL_CONTROL2_FMIN_MASK,
			 STB_FMIN_VAL_DEFAULT);

	/* set fixed max freq depending on SSC config */
	अगर (port->ssc_en) अणु
		dev_info(priv->dev, "enabling SSC on port%d\n", port->portnum);
		पंचांगp = STB_FMAX_VAL_SSC;
	पूर्ण अन्यथा अणु
		पंचांगp = STB_FMAX_VAL_DEFAULT;
	पूर्ण

	brcm_sata_phy_wr(port, TXPMD_REG_BANK, TXPMD_TX_FREQ_CTRL_CONTROL3,
			  ~TXPMD_TX_FREQ_CTRL_CONTROL3_FMAX_MASK, पंचांगp);
पूर्ण

#घोषणा AEQ_FRC_EQ_VAL_SHIFT	2
#घोषणा AEQ_FRC_EQ_VAL_MASK	0x3f

अटल पूर्णांक brcm_stb_sata_rxaeq_init(काष्ठा brcm_sata_port *port)
अणु
	u32 पंचांगp = 0, reg = 0;

	चयन (port->rxaeq_mode) अणु
	हाल RXAEQ_MODE_OFF:
		वापस 0;

	हाल RXAEQ_MODE_AUTO:
		reg = AEQ_CONTROL1;
		पंचांगp = AEQ_CONTROL1_ENABLE | AEQ_CONTROL1_FREEZE;
		अवरोध;

	हाल RXAEQ_MODE_MANUAL:
		reg = AEQ_FRC_EQ;
		पंचांगp = AEQ_FRC_EQ_FORCE | AEQ_FRC_EQ_FORCE_VAL;
		अगर (port->rxaeq_val > AEQ_FRC_EQ_VAL_MASK)
			वापस -EINVAL;
		पंचांगp |= port->rxaeq_val << AEQ_FRC_EQ_VAL_SHIFT;
		अवरोध;
	पूर्ण

	brcm_sata_phy_wr(port, AEQRX_REG_BANK_0, reg, ~पंचांगp, पंचांगp);
	brcm_sata_phy_wr(port, AEQRX_REG_BANK_1, reg, ~पंचांगp, पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_stb_sata_init(काष्ठा brcm_sata_port *port)
अणु
	brcm_stb_sata_ssc_init(port);

	वापस brcm_stb_sata_rxaeq_init(port);
पूर्ण

अटल पूर्णांक brcm_stb_sata_16nm_ssc_init(काष्ठा brcm_sata_port *port)
अणु
	u32 पंचांगp, value;

	/* Reduce CP tail current to 1/16th of its शेष value */
	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL6, 0, 0x141);

	/* Turn off CP tail current boost */
	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL8, 0, 0xc006);

	/* Set a specअगरic AEQ equalizer value */
	पंचांगp = AEQ_FRC_EQ_FORCE_VAL | AEQ_FRC_EQ_FORCE;
	brcm_sata_phy_wr(port, AEQRX_REG_BANK_0, AEQ_FRC_EQ,
			 ~(पंचांगp | AEQ_RFZ_FRC_VAL |
			   AEQ_FRC_EQ_VAL_MASK << AEQ_FRC_EQ_VAL_SHIFT),
			 पंचांगp | 32 << AEQ_FRC_EQ_VAL_SHIFT);

	/* Set RX PPM val center frequency */
	अगर (port->ssc_en)
		value = 0x52;
	अन्यथा
		value = 0;
	brcm_sata_phy_wr(port, RXPMD_REG_BANK, RXPMD_RX_CDR_CONTROL1,
			 ~RXPMD_RX_PPM_VAL_MASK, value);

	/* Set proportional loop bandwith Gen1/2/3 */
	पंचांगp = RXPMD_G_CDR_PROP_BW_MASK << RXPMD_G1_CDR_PROP_BW_SHIFT |
	      RXPMD_G_CDR_PROP_BW_MASK << RXPMD_G2_CDR_PROP_BW_SHIFT |
	      RXPMD_G_CDR_PROP_BW_MASK << RXPMD_G3_CDR_PROB_BW_SHIFT;
	अगर (port->ssc_en)
		value = 2 << RXPMD_G1_CDR_PROP_BW_SHIFT |
			2 << RXPMD_G2_CDR_PROP_BW_SHIFT |
			2 << RXPMD_G3_CDR_PROB_BW_SHIFT;
	अन्यथा
		value = 1 << RXPMD_G1_CDR_PROP_BW_SHIFT |
			1 << RXPMD_G2_CDR_PROP_BW_SHIFT |
			1 << RXPMD_G3_CDR_PROB_BW_SHIFT;
	brcm_sata_phy_wr(port, RXPMD_REG_BANK, RXPMD_RX_CDR_CDR_PROP_BW, ~पंचांगp,
			 value);

	/* Set CDR पूर्णांकegral loop acquisition bandwidth क्रम Gen1/2/3 */
	पंचांगp = RXPMD_G_CDR_ACQ_INT_BW_MASK << RXPMD_G1_CDR_ACQ_INT_BW_SHIFT |
	      RXPMD_G_CDR_ACQ_INT_BW_MASK << RXPMD_G2_CDR_ACQ_INT_BW_SHIFT |
	      RXPMD_G_CDR_ACQ_INT_BW_MASK << RXPMD_G3_CDR_ACQ_INT_BW_SHIFT;
	अगर (port->ssc_en)
		value = 1 << RXPMD_G1_CDR_ACQ_INT_BW_SHIFT |
			1 << RXPMD_G2_CDR_ACQ_INT_BW_SHIFT |
			1 << RXPMD_G3_CDR_ACQ_INT_BW_SHIFT;
	अन्यथा
		value = 0;
	brcm_sata_phy_wr(port, RXPMD_REG_BANK, RXPMD_RX_CDR_CDR_ACQ_INTEG_BW,
			 ~पंचांगp, value);

	/* Set CDR पूर्णांकegral loop locking bandwidth to 1 क्रम Gen 1/2/3 */
	पंचांगp = RXPMD_G_CDR_LOCK_INT_BW_MASK << RXPMD_G1_CDR_LOCK_INT_BW_SHIFT |
	      RXPMD_G_CDR_LOCK_INT_BW_MASK << RXPMD_G2_CDR_LOCK_INT_BW_SHIFT |
	      RXPMD_G_CDR_LOCK_INT_BW_MASK << RXPMD_G3_CDR_LOCK_INT_BW_SHIFT;
	अगर (port->ssc_en)
		value = 1 << RXPMD_G1_CDR_LOCK_INT_BW_SHIFT |
			1 << RXPMD_G2_CDR_LOCK_INT_BW_SHIFT |
			1 << RXPMD_G3_CDR_LOCK_INT_BW_SHIFT;
	अन्यथा
		value = 0;
	brcm_sata_phy_wr(port, RXPMD_REG_BANK, RXPMD_RX_CDR_CDR_LOCK_INTEG_BW,
			 ~पंचांगp, value);

	/* Set no guard band and clamp CDR */
	पंचांगp = RXPMD_MON_CORRECT_EN | RXPMD_MON_MARGIN_VAL_MASK;
	अगर (port->ssc_en)
		value = 0x51;
	अन्यथा
		value = 0;
	brcm_sata_phy_wr(port, RXPMD_REG_BANK, RXPMD_RX_FREQ_MON_CONTROL1,
			 ~पंचांगp, RXPMD_MON_CORRECT_EN | value);

	पंचांगp = GENMASK(15, 12);
	चयन (port->tx_amplitude_val) अणु
	हाल 400:
		value = BIT(12) | BIT(13);
		अवरोध;
	हाल 500:
		value = BIT(13);
		अवरोध;
	हाल 600:
		value = BIT(12);
		अवरोध;
	हाल 800:
		value = 0;
		अवरोध;
	शेष:
		value = पंचांगp;
		अवरोध;
	पूर्ण

	अगर (value != पंचांगp)
		brcm_sata_phy_wr(port, BLOCK1_REG_BANK, BLOCK1_TEST_TX, ~पंचांगp,
				 value);

	/* Turn on/off SSC */
	brcm_sata_phy_wr(port, TX_REG_BANK, TX_ACTRL5, ~TX_ACTRL5_SSC_EN,
			 port->ssc_en ? TX_ACTRL5_SSC_EN : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_stb_sata_16nm_init(काष्ठा brcm_sata_port *port)
अणु
	वापस brcm_stb_sata_16nm_ssc_init(port);
पूर्ण

/* NS2 SATA PLL1 शेषs were अक्षरacterized by H/W group */
#घोषणा NS2_PLL1_ACTRL2_MAGIC	0x1df8
#घोषणा NS2_PLL1_ACTRL3_MAGIC	0x2b00
#घोषणा NS2_PLL1_ACTRL4_MAGIC	0x8824

अटल पूर्णांक brcm_ns2_sata_init(काष्ठा brcm_sata_port *port)
अणु
	पूर्णांक try;
	अचिन्हित पूर्णांक val;
	व्योम __iomem *ctrl_base = brcm_sata_ctrl_base(port);
	काष्ठा device *dev = port->phy_priv->dev;

	/* Configure OOB control */
	val = 0x0;
	val |= (0xc << OOB_CTRL1_BURST_MAX_SHIFT);
	val |= (0x4 << OOB_CTRL1_BURST_MIN_SHIFT);
	val |= (0x9 << OOB_CTRL1_WAKE_IDLE_MAX_SHIFT);
	val |= (0x3 << OOB_CTRL1_WAKE_IDLE_MIN_SHIFT);
	brcm_sata_phy_wr(port, OOB_REG_BANK, OOB_CTRL1, 0x0, val);
	val = 0x0;
	val |= (0x1b << OOB_CTRL2_RESET_IDLE_MAX_SHIFT);
	val |= (0x2 << OOB_CTRL2_BURST_CNT_SHIFT);
	val |= (0x9 << OOB_CTRL2_RESET_IDLE_MIN_SHIFT);
	brcm_sata_phy_wr(port, OOB_REG_BANK, OOB_CTRL2, 0x0, val);

	/* Configure PHY PLL रेजिस्टर bank 1 */
	val = NS2_PLL1_ACTRL2_MAGIC;
	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL2, 0x0, val);
	val = NS2_PLL1_ACTRL3_MAGIC;
	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL3, 0x0, val);
	val = NS2_PLL1_ACTRL4_MAGIC;
	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL4, 0x0, val);

	/* Configure PHY BLOCK0 रेजिस्टर bank */
	/* Set oob_clk_sel to refclk/2 */
	brcm_sata_phy_wr(port, BLOCK0_REG_BANK, BLOCK0_SPARE,
			 ~BLOCK0_SPARE_OOB_CLK_SEL_MASK,
			 BLOCK0_SPARE_OOB_CLK_SEL_REFBY2);

	/* Strobe PHY reset using PHY control रेजिस्टर */
	ग_लिखोl(PHY_CTRL_1_RESET, ctrl_base + PHY_CTRL_1);
	mdelay(1);
	ग_लिखोl(0x0, ctrl_base + PHY_CTRL_1);
	mdelay(1);

	/* Wait क्रम PHY PLL lock by polling pll_lock bit */
	try = 50;
	जबतक (try) अणु
		val = brcm_sata_phy_rd(port, BLOCK0_REG_BANK,
					BLOCK0_XGXSSTATUS);
		अगर (val & BLOCK0_XGXSSTATUS_PLL_LOCK)
			अवरोध;
		msleep(20);
		try--;
	पूर्ण
	अगर (!try) अणु
		/* PLL did not lock; give up */
		dev_err(dev, "port%d PLL did not lock\n", port->portnum);
		वापस -ETIMEDOUT;
	पूर्ण

	dev_dbg(dev, "port%d initialized\n", port->portnum);

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_nsp_sata_init(काष्ठा brcm_sata_port *port)
अणु
	काष्ठा device *dev = port->phy_priv->dev;
	अचिन्हित पूर्णांक oob_bank;
	अचिन्हित पूर्णांक val, try;

	/* Configure OOB control */
	अगर (port->portnum == 0)
		oob_bank = OOB_REG_BANK;
	अन्यथा अगर (port->portnum == 1)
		oob_bank = OOB1_REG_BANK;
	अन्यथा
		वापस -EINVAL;

	val = 0x0;
	val |= (0x0f << OOB_CTRL1_BURST_MAX_SHIFT);
	val |= (0x06 << OOB_CTRL1_BURST_MIN_SHIFT);
	val |= (0x0f << OOB_CTRL1_WAKE_IDLE_MAX_SHIFT);
	val |= (0x06 << OOB_CTRL1_WAKE_IDLE_MIN_SHIFT);
	brcm_sata_phy_wr(port, oob_bank, OOB_CTRL1, 0x0, val);

	val = 0x0;
	val |= (0x2e << OOB_CTRL2_RESET_IDLE_MAX_SHIFT);
	val |= (0x02 << OOB_CTRL2_BURST_CNT_SHIFT);
	val |= (0x16 << OOB_CTRL2_RESET_IDLE_MIN_SHIFT);
	brcm_sata_phy_wr(port, oob_bank, OOB_CTRL2, 0x0, val);


	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_ACTRL2,
		~(PLL_ACTRL2_SELDIV_MASK << PLL_ACTRL2_SELDIV_SHIFT),
		0x0c << PLL_ACTRL2_SELDIV_SHIFT);

	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_CAP_CONTROL,
						0xff0, 0x4f0);

	val = PLLCONTROL_0_FREQ_DET_RESTART | PLLCONTROL_0_FREQ_MONITOR;
	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_REG_BANK_0_PLLCONTROL_0,
								~val, val);
	val = PLLCONTROL_0_SEQ_START;
	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_REG_BANK_0_PLLCONTROL_0,
								~val, 0);
	mdelay(10);
	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_REG_BANK_0_PLLCONTROL_0,
								~val, val);

	/* Wait क्रम pll_seq_करोne bit */
	try = 50;
	जबतक (--try) अणु
		val = brcm_sata_phy_rd(port, BLOCK0_REG_BANK,
					BLOCK0_XGXSSTATUS);
		अगर (val & BLOCK0_XGXSSTATUS_PLL_LOCK)
			अवरोध;
		msleep(20);
	पूर्ण
	अगर (!try) अणु
		/* PLL did not lock; give up */
		dev_err(dev, "port%d PLL did not lock\n", port->portnum);
		वापस -ETIMEDOUT;
	पूर्ण

	dev_dbg(dev, "port%d initialized\n", port->portnum);

	वापस 0;
पूर्ण

/* SR PHY PLL0 रेजिस्टरs */
#घोषणा SR_PLL0_ACTRL6_MAGIC			0xa

/* SR PHY PLL1 रेजिस्टरs */
#घोषणा SR_PLL1_ACTRL2_MAGIC			0x32
#घोषणा SR_PLL1_ACTRL3_MAGIC			0x2
#घोषणा SR_PLL1_ACTRL4_MAGIC			0x3e8

अटल पूर्णांक brcm_sr_sata_init(काष्ठा brcm_sata_port *port)
अणु
	काष्ठा device *dev = port->phy_priv->dev;
	अचिन्हित पूर्णांक val, try;

	/* Configure PHY PLL रेजिस्टर bank 1 */
	val = SR_PLL1_ACTRL2_MAGIC;
	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL2, 0x0, val);
	val = SR_PLL1_ACTRL3_MAGIC;
	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL3, 0x0, val);
	val = SR_PLL1_ACTRL4_MAGIC;
	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL4, 0x0, val);

	/* Configure PHY PLL रेजिस्टर bank 0 */
	val = SR_PLL0_ACTRL6_MAGIC;
	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_ACTRL6, 0x0, val);

	/* Wait क्रम PHY PLL lock by polling pll_lock bit */
	try = 50;
	करो अणु
		val = brcm_sata_phy_rd(port, BLOCK0_REG_BANK,
					BLOCK0_XGXSSTATUS);
		अगर (val & BLOCK0_XGXSSTATUS_PLL_LOCK)
			अवरोध;
		msleep(20);
		try--;
	पूर्ण जबतक (try);

	अगर ((val & BLOCK0_XGXSSTATUS_PLL_LOCK) == 0) अणु
		/* PLL did not lock; give up */
		dev_err(dev, "port%d PLL did not lock\n", port->portnum);
		वापस -ETIMEDOUT;
	पूर्ण

	/* Invert Tx polarity */
	brcm_sata_phy_wr(port, TX_REG_BANK, TX_ACTRL0,
			 ~TX_ACTRL0_TXPOL_FLIP, TX_ACTRL0_TXPOL_FLIP);

	/* Configure OOB control to handle 100MHz reference घड़ी */
	val = ((0xc << OOB_CTRL1_BURST_MAX_SHIFT) |
		(0x4 << OOB_CTRL1_BURST_MIN_SHIFT) |
		(0x8 << OOB_CTRL1_WAKE_IDLE_MAX_SHIFT) |
		(0x3 << OOB_CTRL1_WAKE_IDLE_MIN_SHIFT));
	brcm_sata_phy_wr(port, OOB_REG_BANK, OOB_CTRL1, 0x0, val);
	val = ((0x1b << OOB_CTRL2_RESET_IDLE_MAX_SHIFT) |
		(0x2 << OOB_CTRL2_BURST_CNT_SHIFT) |
		(0x9 << OOB_CTRL2_RESET_IDLE_MIN_SHIFT));
	brcm_sata_phy_wr(port, OOB_REG_BANK, OOB_CTRL2, 0x0, val);

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_dsl_sata_init(काष्ठा brcm_sata_port *port)
अणु
	काष्ठा device *dev = port->phy_priv->dev;
	अचिन्हित पूर्णांक try;
	u32 पंचांगp;

	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL7, 0, 0x873);

	brcm_sata_phy_wr(port, PLL1_REG_BANK, PLL1_ACTRL6, 0, 0xc000);

	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_REG_BANK_0_PLLCONTROL_0,
			 0, 0x3089);
	usleep_range(1000, 2000);

	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_REG_BANK_0_PLLCONTROL_0,
			 0, 0x3088);
	usleep_range(1000, 2000);

	brcm_sata_phy_wr(port, AEQRX_REG_BANK_1, AEQRX_SLCAL0_CTRL0,
			 0, 0x3000);

	brcm_sata_phy_wr(port, AEQRX_REG_BANK_1, AEQRX_SLCAL1_CTRL0,
			 0, 0x3000);
	usleep_range(1000, 2000);

	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_CAP_CHARGE_TIME, 0, 0x32);

	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_VCO_CAL_THRESH, 0, 0xa);

	brcm_sata_phy_wr(port, PLL_REG_BANK_0, PLL_FREQ_DET_TIME, 0, 0x64);
	usleep_range(1000, 2000);

	/* Acquire PLL lock */
	try = 50;
	जबतक (try) अणु
		पंचांगp = brcm_sata_phy_rd(port, BLOCK0_REG_BANK,
				       BLOCK0_XGXSSTATUS);
		अगर (पंचांगp & BLOCK0_XGXSSTATUS_PLL_LOCK)
			अवरोध;
		msleep(20);
		try--;
	पूर्ण

	अगर (!try) अणु
		/* PLL did not lock; give up */
		dev_err(dev, "port%d PLL did not lock\n", port->portnum);
		वापस -ETIMEDOUT;
	पूर्ण

	dev_dbg(dev, "port%d initialized\n", port->portnum);

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_sata_phy_init(काष्ठा phy *phy)
अणु
	पूर्णांक rc;
	काष्ठा brcm_sata_port *port = phy_get_drvdata(phy);

	चयन (port->phy_priv->version) अणु
	हाल BRCM_SATA_PHY_STB_16NM:
		rc = brcm_stb_sata_16nm_init(port);
		अवरोध;
	हाल BRCM_SATA_PHY_STB_28NM:
	हाल BRCM_SATA_PHY_STB_40NM:
		rc = brcm_stb_sata_init(port);
		अवरोध;
	हाल BRCM_SATA_PHY_IPROC_NS2:
		rc = brcm_ns2_sata_init(port);
		अवरोध;
	हाल BRCM_SATA_PHY_IPROC_NSP:
		rc = brcm_nsp_sata_init(port);
		अवरोध;
	हाल BRCM_SATA_PHY_IPROC_SR:
		rc = brcm_sr_sata_init(port);
		अवरोध;
	हाल BRCM_SATA_PHY_DSL_28NM:
		rc = brcm_dsl_sata_init(port);
		अवरोध;
	शेष:
		rc = -ENODEV;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम brcm_stb_sata_calibrate(काष्ठा brcm_sata_port *port)
अणु
	u32 पंचांगp = BIT(8);

	brcm_sata_phy_wr(port, RXPMD_REG_BANK, RXPMD_RX_FREQ_MON_CONTROL1,
			 ~पंचांगp, पंचांगp);
पूर्ण

अटल पूर्णांक brcm_sata_phy_calibrate(काष्ठा phy *phy)
अणु
	काष्ठा brcm_sata_port *port = phy_get_drvdata(phy);
	पूर्णांक rc = -EOPNOTSUPP;

	चयन (port->phy_priv->version) अणु
	हाल BRCM_SATA_PHY_STB_28NM:
	हाल BRCM_SATA_PHY_STB_40NM:
		brcm_stb_sata_calibrate(port);
		rc = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_ops = अणु
	.init		= brcm_sata_phy_init,
	.calibrate	= brcm_sata_phy_calibrate,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id brcm_sata_phy_of_match[] = अणु
	अणु .compatible	= "brcm,bcm7216-sata-phy",
	  .data = (व्योम *)BRCM_SATA_PHY_STB_16NM पूर्ण,
	अणु .compatible	= "brcm,bcm7445-sata-phy",
	  .data = (व्योम *)BRCM_SATA_PHY_STB_28NM पूर्ण,
	अणु .compatible	= "brcm,bcm7425-sata-phy",
	  .data = (व्योम *)BRCM_SATA_PHY_STB_40NM पूर्ण,
	अणु .compatible	= "brcm,iproc-ns2-sata-phy",
	  .data = (व्योम *)BRCM_SATA_PHY_IPROC_NS2 पूर्ण,
	अणु .compatible = "brcm,iproc-nsp-sata-phy",
	  .data = (व्योम *)BRCM_SATA_PHY_IPROC_NSP पूर्ण,
	अणु .compatible	= "brcm,iproc-sr-sata-phy",
	  .data = (व्योम *)BRCM_SATA_PHY_IPROC_SR पूर्ण,
	अणु .compatible	= "brcm,bcm63138-sata-phy",
	  .data = (व्योम *)BRCM_SATA_PHY_DSL_28NM पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, brcm_sata_phy_of_match);

अटल पूर्णांक brcm_sata_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *rxaeq_mode;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn = dev->of_node, *child;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा brcm_sata_phy *priv;
	काष्ठा phy_provider *provider;
	पूर्णांक ret, count = 0;

	अगर (of_get_child_count(dn) == 0)
		वापस -ENODEV;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	dev_set_drvdata(dev, priv);
	priv->dev = dev;

	priv->phy_base = devm_platक्रमm_ioremap_resource_byname(pdev, "phy");
	अगर (IS_ERR(priv->phy_base))
		वापस PTR_ERR(priv->phy_base);

	of_id = of_match_node(brcm_sata_phy_of_match, dn);
	अगर (of_id)
		priv->version = (क्रमागत brcm_sata_phy_version)of_id->data;
	अन्यथा
		priv->version = BRCM_SATA_PHY_STB_28NM;

	अगर (priv->version == BRCM_SATA_PHY_IPROC_NS2) अणु
		priv->ctrl_base = devm_platक्रमm_ioremap_resource_byname(pdev, "phy-ctrl");
		अगर (IS_ERR(priv->ctrl_base))
			वापस PTR_ERR(priv->ctrl_base);
	पूर्ण

	क्रम_each_available_child_of_node(dn, child) अणु
		अचिन्हित पूर्णांक id;
		काष्ठा brcm_sata_port *port;

		अगर (of_property_पढ़ो_u32(child, "reg", &id)) अणु
			dev_err(dev, "missing reg property in node %pOFn\n",
					child);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		अगर (id >= MAX_PORTS) अणु
			dev_err(dev, "invalid reg: %u\n", id);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण
		अगर (priv->phys[id].phy) अणु
			dev_err(dev, "already registered port %u\n", id);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		port = &priv->phys[id];
		port->portnum = id;
		port->phy_priv = priv;
		port->phy = devm_phy_create(dev, child, &phy_ops);
		port->rxaeq_mode = RXAEQ_MODE_OFF;
		अगर (!of_property_पढ़ो_string(child, "brcm,rxaeq-mode",
					     &rxaeq_mode))
			port->rxaeq_mode = rxaeq_to_val(rxaeq_mode);
		अगर (port->rxaeq_mode == RXAEQ_MODE_MANUAL)
			of_property_पढ़ो_u32(child, "brcm,rxaeq-value",
					     &port->rxaeq_val);

		of_property_पढ़ो_u32(child, "brcm,tx-amplitude-millivolt",
				     &port->tx_amplitude_val);

		port->ssc_en = of_property_पढ़ो_bool(child, "brcm,enable-ssc");
		अगर (IS_ERR(port->phy)) अणु
			dev_err(dev, "failed to create PHY\n");
			ret = PTR_ERR(port->phy);
			जाओ put_child;
		पूर्ण

		phy_set_drvdata(port->phy, port);
		count++;
	पूर्ण

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "could not register PHY provider\n");
		वापस PTR_ERR(provider);
	पूर्ण

	dev_info(dev, "registered %d port(s)\n", count);

	वापस 0;
put_child:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver brcm_sata_phy_driver = अणु
	.probe	= brcm_sata_phy_probe,
	.driver	= अणु
		.of_match_table	= brcm_sata_phy_of_match,
		.name		= "brcm-sata-phy",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(brcm_sata_phy_driver);

MODULE_DESCRIPTION("Broadcom SATA PHY driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marc Carino");
MODULE_AUTHOR("Brian Norris");
MODULE_ALIAS("platform:phy-brcm-sata");
