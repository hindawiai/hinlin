<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Freescale i.MX6 SoCs
 *
 * Copyright (C) 2013 Kosagi
 *		https://www.kosagi.com
 *
 * Author: Sean Cross <xobs@kosagi.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/mfd/syscon/imx7-iomuxc-gpr.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/resource.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reset.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "pcie-designware.h"

#घोषणा IMX8MQ_GPR_PCIE_REF_USE_PAD		BIT(9)
#घोषणा IMX8MQ_GPR_PCIE_CLK_REQ_OVERRIDE_EN	BIT(10)
#घोषणा IMX8MQ_GPR_PCIE_CLK_REQ_OVERRIDE	BIT(11)
#घोषणा IMX8MQ_GPR12_PCIE2_CTRL_DEVICE_TYPE	GENMASK(11, 8)
#घोषणा IMX8MQ_PCIE2_BASE_ADDR			0x33c00000

#घोषणा to_imx6_pcie(x)	dev_get_drvdata((x)->dev)

क्रमागत imx6_pcie_variants अणु
	IMX6Q,
	IMX6SX,
	IMX6QP,
	IMX7D,
	IMX8MQ,
पूर्ण;

#घोषणा IMX6_PCIE_FLAG_IMX6_PHY			BIT(0)
#घोषणा IMX6_PCIE_FLAG_IMX6_SPEED_CHANGE	BIT(1)
#घोषणा IMX6_PCIE_FLAG_SUPPORTS_SUSPEND		BIT(2)

काष्ठा imx6_pcie_drvdata अणु
	क्रमागत imx6_pcie_variants variant;
	u32 flags;
	पूर्णांक dbi_length;
पूर्ण;

काष्ठा imx6_pcie अणु
	काष्ठा dw_pcie		*pci;
	पूर्णांक			reset_gpio;
	bool			gpio_active_high;
	काष्ठा clk		*pcie_bus;
	काष्ठा clk		*pcie_phy;
	काष्ठा clk		*pcie_inbound_axi;
	काष्ठा clk		*pcie;
	काष्ठा clk		*pcie_aux;
	काष्ठा regmap		*iomuxc_gpr;
	u32			controller_id;
	काष्ठा reset_control	*pciephy_reset;
	काष्ठा reset_control	*apps_reset;
	काष्ठा reset_control	*turnoff_reset;
	u32			tx_deemph_gen1;
	u32			tx_deemph_gen2_3p5db;
	u32			tx_deemph_gen2_6db;
	u32			tx_swing_full;
	u32			tx_swing_low;
	काष्ठा regulator	*vpcie;
	व्योम __iomem		*phy_base;

	/* घातer करोमुख्य क्रम pcie */
	काष्ठा device		*pd_pcie;
	/* घातer करोमुख्य क्रम pcie phy */
	काष्ठा device		*pd_pcie_phy;
	स्थिर काष्ठा imx6_pcie_drvdata *drvdata;
पूर्ण;

/* Parameters क्रम the रुकोing क्रम PCIe PHY PLL to lock on i.MX7 */
#घोषणा PHY_PLL_LOCK_WAIT_USLEEP_MAX	200
#घोषणा PHY_PLL_LOCK_WAIT_TIMEOUT	(2000 * PHY_PLL_LOCK_WAIT_USLEEP_MAX)

/* PCIe Port Logic रेजिस्टरs (memory-mapped) */
#घोषणा PL_OFFSET 0x700

#घोषणा PCIE_PHY_CTRL (PL_OFFSET + 0x114)
#घोषणा PCIE_PHY_CTRL_DATA(x)		FIELD_PREP(GENMASK(15, 0), (x))
#घोषणा PCIE_PHY_CTRL_CAP_ADR		BIT(16)
#घोषणा PCIE_PHY_CTRL_CAP_DAT		BIT(17)
#घोषणा PCIE_PHY_CTRL_WR		BIT(18)
#घोषणा PCIE_PHY_CTRL_RD		BIT(19)

#घोषणा PCIE_PHY_STAT (PL_OFFSET + 0x110)
#घोषणा PCIE_PHY_STAT_ACK		BIT(16)

/* PHY रेजिस्टरs (not memory-mapped) */
#घोषणा PCIE_PHY_ATEOVRD			0x10
#घोषणा  PCIE_PHY_ATEOVRD_EN			BIT(2)
#घोषणा  PCIE_PHY_ATEOVRD_REF_CLKDIV_SHIFT	0
#घोषणा  PCIE_PHY_ATEOVRD_REF_CLKDIV_MASK	0x1

#घोषणा PCIE_PHY_MPLL_OVRD_IN_LO		0x11
#घोषणा  PCIE_PHY_MPLL_MULTIPLIER_SHIFT		2
#घोषणा  PCIE_PHY_MPLL_MULTIPLIER_MASK		0x7f
#घोषणा  PCIE_PHY_MPLL_MULTIPLIER_OVRD		BIT(9)

#घोषणा PCIE_PHY_RX_ASIC_OUT 0x100D
#घोषणा PCIE_PHY_RX_ASIC_OUT_VALID	(1 << 0)

/* iMX7 PCIe PHY रेजिस्टरs */
#घोषणा PCIE_PHY_CMN_REG4		0x14
/* These are probably the bits that *aren't* DCC_FB_EN */
#घोषणा PCIE_PHY_CMN_REG4_DCC_FB_EN	0x29

#घोषणा PCIE_PHY_CMN_REG15	        0x54
#घोषणा PCIE_PHY_CMN_REG15_DLY_4	BIT(2)
#घोषणा PCIE_PHY_CMN_REG15_PLL_PD	BIT(5)
#घोषणा PCIE_PHY_CMN_REG15_OVRD_PLL_PD	BIT(7)

#घोषणा PCIE_PHY_CMN_REG24		0x90
#घोषणा PCIE_PHY_CMN_REG24_RX_EQ	BIT(6)
#घोषणा PCIE_PHY_CMN_REG24_RX_EQ_SEL	BIT(3)

#घोषणा PCIE_PHY_CMN_REG26		0x98
#घोषणा PCIE_PHY_CMN_REG26_ATT_MODE	0xBC

#घोषणा PHY_RX_OVRD_IN_LO 0x1005
#घोषणा PHY_RX_OVRD_IN_LO_RX_DATA_EN		BIT(5)
#घोषणा PHY_RX_OVRD_IN_LO_RX_PLL_EN		BIT(3)

अटल पूर्णांक pcie_phy_poll_ack(काष्ठा imx6_pcie *imx6_pcie, bool exp_val)
अणु
	काष्ठा dw_pcie *pci = imx6_pcie->pci;
	bool val;
	u32 max_iterations = 10;
	u32 रुको_counter = 0;

	करो अणु
		val = dw_pcie_पढ़ोl_dbi(pci, PCIE_PHY_STAT) &
			PCIE_PHY_STAT_ACK;
		रुको_counter++;

		अगर (val == exp_val)
			वापस 0;

		udelay(1);
	पूर्ण जबतक (रुको_counter < max_iterations);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक pcie_phy_रुको_ack(काष्ठा imx6_pcie *imx6_pcie, पूर्णांक addr)
अणु
	काष्ठा dw_pcie *pci = imx6_pcie->pci;
	u32 val;
	पूर्णांक ret;

	val = PCIE_PHY_CTRL_DATA(addr);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, val);

	val |= PCIE_PHY_CTRL_CAP_ADR;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, val);

	ret = pcie_phy_poll_ack(imx6_pcie, true);
	अगर (ret)
		वापस ret;

	val = PCIE_PHY_CTRL_DATA(addr);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, val);

	वापस pcie_phy_poll_ack(imx6_pcie, false);
पूर्ण

/* Read from the 16-bit PCIe PHY control रेजिस्टरs (not memory-mapped) */
अटल पूर्णांक pcie_phy_पढ़ो(काष्ठा imx6_pcie *imx6_pcie, पूर्णांक addr, u16 *data)
अणु
	काष्ठा dw_pcie *pci = imx6_pcie->pci;
	u32 phy_ctl;
	पूर्णांक ret;

	ret = pcie_phy_रुको_ack(imx6_pcie, addr);
	अगर (ret)
		वापस ret;

	/* निश्चित Read संकेत */
	phy_ctl = PCIE_PHY_CTRL_RD;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, phy_ctl);

	ret = pcie_phy_poll_ack(imx6_pcie, true);
	अगर (ret)
		वापस ret;

	*data = dw_pcie_पढ़ोl_dbi(pci, PCIE_PHY_STAT);

	/* deनिश्चित Read संकेत */
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, 0x00);

	वापस pcie_phy_poll_ack(imx6_pcie, false);
पूर्ण

अटल पूर्णांक pcie_phy_ग_लिखो(काष्ठा imx6_pcie *imx6_pcie, पूर्णांक addr, u16 data)
अणु
	काष्ठा dw_pcie *pci = imx6_pcie->pci;
	u32 var;
	पूर्णांक ret;

	/* ग_लिखो addr */
	/* cap addr */
	ret = pcie_phy_रुको_ack(imx6_pcie, addr);
	अगर (ret)
		वापस ret;

	var = PCIE_PHY_CTRL_DATA(data);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, var);

	/* capture data */
	var |= PCIE_PHY_CTRL_CAP_DAT;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, var);

	ret = pcie_phy_poll_ack(imx6_pcie, true);
	अगर (ret)
		वापस ret;

	/* deनिश्चित cap data */
	var = PCIE_PHY_CTRL_DATA(data);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, var);

	/* रुको क्रम ack de-निश्चितion */
	ret = pcie_phy_poll_ack(imx6_pcie, false);
	अगर (ret)
		वापस ret;

	/* निश्चित wr संकेत */
	var = PCIE_PHY_CTRL_WR;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, var);

	/* रुको क्रम ack */
	ret = pcie_phy_poll_ack(imx6_pcie, true);
	अगर (ret)
		वापस ret;

	/* deनिश्चित wr संकेत */
	var = PCIE_PHY_CTRL_DATA(data);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, var);

	/* रुको क्रम ack de-निश्चितion */
	ret = pcie_phy_poll_ack(imx6_pcie, false);
	अगर (ret)
		वापस ret;

	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PHY_CTRL, 0x0);

	वापस 0;
पूर्ण

अटल व्योम imx6_pcie_reset_phy(काष्ठा imx6_pcie *imx6_pcie)
अणु
	u16 पंचांगp;

	अगर (!(imx6_pcie->drvdata->flags & IMX6_PCIE_FLAG_IMX6_PHY))
		वापस;

	pcie_phy_पढ़ो(imx6_pcie, PHY_RX_OVRD_IN_LO, &पंचांगp);
	पंचांगp |= (PHY_RX_OVRD_IN_LO_RX_DATA_EN |
		PHY_RX_OVRD_IN_LO_RX_PLL_EN);
	pcie_phy_ग_लिखो(imx6_pcie, PHY_RX_OVRD_IN_LO, पंचांगp);

	usleep_range(2000, 3000);

	pcie_phy_पढ़ो(imx6_pcie, PHY_RX_OVRD_IN_LO, &पंचांगp);
	पंचांगp &= ~(PHY_RX_OVRD_IN_LO_RX_DATA_EN |
		  PHY_RX_OVRD_IN_LO_RX_PLL_EN);
	pcie_phy_ग_लिखो(imx6_pcie, PHY_RX_OVRD_IN_LO, पंचांगp);
पूर्ण

#अगर_घोषित CONFIG_ARM
/*  Added क्रम PCI पात handling */
अटल पूर्णांक imx6q_pcie_पात_handler(अचिन्हित दीर्घ addr,
		अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc = inकाष्ठाion_poपूर्णांकer(regs);
	अचिन्हित दीर्घ instr = *(अचिन्हित दीर्घ *)pc;
	पूर्णांक reg = (instr >> 12) & 15;

	/*
	 * If the inकाष्ठाion being executed was a पढ़ो,
	 * make it look like it पढ़ो all-ones.
	 */
	अगर ((instr & 0x0c100000) == 0x04100000) अणु
		अचिन्हित दीर्घ val;

		अगर (instr & 0x00400000)
			val = 255;
		अन्यथा
			val = -1;

		regs->uregs[reg] = val;
		regs->ARM_pc += 4;
		वापस 0;
	पूर्ण

	अगर ((instr & 0x0e100090) == 0x00100090) अणु
		regs->uregs[reg] = -1;
		regs->ARM_pc += 4;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक imx6_pcie_attach_pd(काष्ठा device *dev)
अणु
	काष्ठा imx6_pcie *imx6_pcie = dev_get_drvdata(dev);
	काष्ठा device_link *link;

	/* Do nothing when in a single घातer करोमुख्य */
	अगर (dev->pm_करोमुख्य)
		वापस 0;

	imx6_pcie->pd_pcie = dev_pm_करोमुख्य_attach_by_name(dev, "pcie");
	अगर (IS_ERR(imx6_pcie->pd_pcie))
		वापस PTR_ERR(imx6_pcie->pd_pcie);
	/* Do nothing when घातer करोमुख्य missing */
	अगर (!imx6_pcie->pd_pcie)
		वापस 0;
	link = device_link_add(dev, imx6_pcie->pd_pcie,
			DL_FLAG_STATELESS |
			DL_FLAG_PM_RUNTIME |
			DL_FLAG_RPM_ACTIVE);
	अगर (!link) अणु
		dev_err(dev, "Failed to add device_link to pcie pd.\n");
		वापस -EINVAL;
	पूर्ण

	imx6_pcie->pd_pcie_phy = dev_pm_करोमुख्य_attach_by_name(dev, "pcie_phy");
	अगर (IS_ERR(imx6_pcie->pd_pcie_phy))
		वापस PTR_ERR(imx6_pcie->pd_pcie_phy);

	link = device_link_add(dev, imx6_pcie->pd_pcie_phy,
			DL_FLAG_STATELESS |
			DL_FLAG_PM_RUNTIME |
			DL_FLAG_RPM_ACTIVE);
	अगर (!link) अणु
		dev_err(dev, "Failed to add device_link to pcie_phy pd.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx6_pcie_निश्चित_core_reset(काष्ठा imx6_pcie *imx6_pcie)
अणु
	काष्ठा device *dev = imx6_pcie->pci->dev;

	चयन (imx6_pcie->drvdata->variant) अणु
	हाल IMX7D:
	हाल IMX8MQ:
		reset_control_निश्चित(imx6_pcie->pciephy_reset);
		reset_control_निश्चित(imx6_pcie->apps_reset);
		अवरोध;
	हाल IMX6SX:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6SX_GPR12_PCIE_TEST_POWERDOWN,
				   IMX6SX_GPR12_PCIE_TEST_POWERDOWN);
		/* Force PCIe PHY reset */
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR5,
				   IMX6SX_GPR5_PCIE_BTNRST_RESET,
				   IMX6SX_GPR5_PCIE_BTNRST_RESET);
		अवरोध;
	हाल IMX6QP:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR1,
				   IMX6Q_GPR1_PCIE_SW_RST,
				   IMX6Q_GPR1_PCIE_SW_RST);
		अवरोध;
	हाल IMX6Q:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR1,
				   IMX6Q_GPR1_PCIE_TEST_PD, 1 << 18);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR1,
				   IMX6Q_GPR1_PCIE_REF_CLK_EN, 0 << 16);
		अवरोध;
	पूर्ण

	अगर (imx6_pcie->vpcie && regulator_is_enabled(imx6_pcie->vpcie) > 0) अणु
		पूर्णांक ret = regulator_disable(imx6_pcie->vpcie);

		अगर (ret)
			dev_err(dev, "failed to disable vpcie regulator: %d\n",
				ret);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक imx6_pcie_grp_offset(स्थिर काष्ठा imx6_pcie *imx6_pcie)
अणु
	WARN_ON(imx6_pcie->drvdata->variant != IMX8MQ);
	वापस imx6_pcie->controller_id == 1 ? IOMUXC_GPR16 : IOMUXC_GPR14;
पूर्ण

अटल पूर्णांक imx6_pcie_enable_ref_clk(काष्ठा imx6_pcie *imx6_pcie)
अणु
	काष्ठा dw_pcie *pci = imx6_pcie->pci;
	काष्ठा device *dev = pci->dev;
	अचिन्हित पूर्णांक offset;
	पूर्णांक ret = 0;

	चयन (imx6_pcie->drvdata->variant) अणु
	हाल IMX6SX:
		ret = clk_prepare_enable(imx6_pcie->pcie_inbound_axi);
		अगर (ret) अणु
			dev_err(dev, "unable to enable pcie_axi clock\n");
			अवरोध;
		पूर्ण

		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6SX_GPR12_PCIE_TEST_POWERDOWN, 0);
		अवरोध;
	हाल IMX6QP:
	हाल IMX6Q:
		/* घातer up core phy and enable ref घड़ी */
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR1,
				   IMX6Q_GPR1_PCIE_TEST_PD, 0 << 18);
		/*
		 * the async reset input need ref घड़ी to sync पूर्णांकernally,
		 * when the ref घड़ी comes after reset, पूर्णांकernal synced
		 * reset समय is too लघु, cannot meet the requirement.
		 * add one ~10us delay here.
		 */
		usleep_range(10, 100);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR1,
				   IMX6Q_GPR1_PCIE_REF_CLK_EN, 1 << 16);
		अवरोध;
	हाल IMX7D:
		अवरोध;
	हाल IMX8MQ:
		ret = clk_prepare_enable(imx6_pcie->pcie_aux);
		अगर (ret) अणु
			dev_err(dev, "unable to enable pcie_aux clock\n");
			अवरोध;
		पूर्ण

		offset = imx6_pcie_grp_offset(imx6_pcie);
		/*
		 * Set the over ride low and enabled
		 * make sure that REF_CLK is turned on.
		 */
		regmap_update_bits(imx6_pcie->iomuxc_gpr, offset,
				   IMX8MQ_GPR_PCIE_CLK_REQ_OVERRIDE,
				   0);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, offset,
				   IMX8MQ_GPR_PCIE_CLK_REQ_OVERRIDE_EN,
				   IMX8MQ_GPR_PCIE_CLK_REQ_OVERRIDE_EN);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम imx7d_pcie_रुको_क्रम_phy_pll_lock(काष्ठा imx6_pcie *imx6_pcie)
अणु
	u32 val;
	काष्ठा device *dev = imx6_pcie->pci->dev;

	अगर (regmap_पढ़ो_poll_समयout(imx6_pcie->iomuxc_gpr,
				     IOMUXC_GPR22, val,
				     val & IMX7D_GPR22_PCIE_PHY_PLL_LOCKED,
				     PHY_PLL_LOCK_WAIT_USLEEP_MAX,
				     PHY_PLL_LOCK_WAIT_TIMEOUT))
		dev_err(dev, "PCIe PLL lock timeout\n");
पूर्ण

अटल व्योम imx6_pcie_deनिश्चित_core_reset(काष्ठा imx6_pcie *imx6_pcie)
अणु
	काष्ठा dw_pcie *pci = imx6_pcie->pci;
	काष्ठा device *dev = pci->dev;
	पूर्णांक ret;

	अगर (imx6_pcie->vpcie && !regulator_is_enabled(imx6_pcie->vpcie)) अणु
		ret = regulator_enable(imx6_pcie->vpcie);
		अगर (ret) अणु
			dev_err(dev, "failed to enable vpcie regulator: %d\n",
				ret);
			वापस;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(imx6_pcie->pcie_phy);
	अगर (ret) अणु
		dev_err(dev, "unable to enable pcie_phy clock\n");
		जाओ err_pcie_phy;
	पूर्ण

	ret = clk_prepare_enable(imx6_pcie->pcie_bus);
	अगर (ret) अणु
		dev_err(dev, "unable to enable pcie_bus clock\n");
		जाओ err_pcie_bus;
	पूर्ण

	ret = clk_prepare_enable(imx6_pcie->pcie);
	अगर (ret) अणु
		dev_err(dev, "unable to enable pcie clock\n");
		जाओ err_pcie;
	पूर्ण

	ret = imx6_pcie_enable_ref_clk(imx6_pcie);
	अगर (ret) अणु
		dev_err(dev, "unable to enable pcie ref clock\n");
		जाओ err_ref_clk;
	पूर्ण

	/* allow the घड़ीs to stabilize */
	usleep_range(200, 500);

	/* Some boards करोn't have PCIe reset GPIO. */
	अगर (gpio_is_valid(imx6_pcie->reset_gpio)) अणु
		gpio_set_value_cansleep(imx6_pcie->reset_gpio,
					imx6_pcie->gpio_active_high);
		msleep(100);
		gpio_set_value_cansleep(imx6_pcie->reset_gpio,
					!imx6_pcie->gpio_active_high);
	पूर्ण

	चयन (imx6_pcie->drvdata->variant) अणु
	हाल IMX8MQ:
		reset_control_deनिश्चित(imx6_pcie->pciephy_reset);
		अवरोध;
	हाल IMX7D:
		reset_control_deनिश्चित(imx6_pcie->pciephy_reset);

		/* Workaround क्रम ERR010728, failure of PCI-e PLL VCO to
		 * oscillate, especially when cold.  This turns off "Duty-cycle
		 * Corrector" and other mysterious unकरोcumented things.
		 */
		अगर (likely(imx6_pcie->phy_base)) अणु
			/* De-निश्चित DCC_FB_EN */
			ग_लिखोl(PCIE_PHY_CMN_REG4_DCC_FB_EN,
			       imx6_pcie->phy_base + PCIE_PHY_CMN_REG4);
			/* Assert RX_EQS and RX_EQS_SEL */
			ग_लिखोl(PCIE_PHY_CMN_REG24_RX_EQ_SEL
				| PCIE_PHY_CMN_REG24_RX_EQ,
			       imx6_pcie->phy_base + PCIE_PHY_CMN_REG24);
			/* Assert ATT_MODE */
			ग_लिखोl(PCIE_PHY_CMN_REG26_ATT_MODE,
			       imx6_pcie->phy_base + PCIE_PHY_CMN_REG26);
		पूर्ण अन्यथा अणु
			dev_warn(dev, "Unable to apply ERR010728 workaround. DT missing fsl,imx7d-pcie-phy phandle ?\n");
		पूर्ण

		imx7d_pcie_रुको_क्रम_phy_pll_lock(imx6_pcie);
		अवरोध;
	हाल IMX6SX:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR5,
				   IMX6SX_GPR5_PCIE_BTNRST_RESET, 0);
		अवरोध;
	हाल IMX6QP:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR1,
				   IMX6Q_GPR1_PCIE_SW_RST, 0);

		usleep_range(200, 500);
		अवरोध;
	हाल IMX6Q:		/* Nothing to करो */
		अवरोध;
	पूर्ण

	वापस;

err_ref_clk:
	clk_disable_unprepare(imx6_pcie->pcie);
err_pcie:
	clk_disable_unprepare(imx6_pcie->pcie_bus);
err_pcie_bus:
	clk_disable_unprepare(imx6_pcie->pcie_phy);
err_pcie_phy:
	अगर (imx6_pcie->vpcie && regulator_is_enabled(imx6_pcie->vpcie) > 0) अणु
		ret = regulator_disable(imx6_pcie->vpcie);
		अगर (ret)
			dev_err(dev, "failed to disable vpcie regulator: %d\n",
				ret);
	पूर्ण
पूर्ण

अटल व्योम imx6_pcie_configure_type(काष्ठा imx6_pcie *imx6_pcie)
अणु
	अचिन्हित पूर्णांक mask, val;

	अगर (imx6_pcie->drvdata->variant == IMX8MQ &&
	    imx6_pcie->controller_id == 1) अणु
		mask   = IMX8MQ_GPR12_PCIE2_CTRL_DEVICE_TYPE;
		val    = FIELD_PREP(IMX8MQ_GPR12_PCIE2_CTRL_DEVICE_TYPE,
				    PCI_EXP_TYPE_ROOT_PORT);
	पूर्ण अन्यथा अणु
		mask = IMX6Q_GPR12_DEVICE_TYPE;
		val  = FIELD_PREP(IMX6Q_GPR12_DEVICE_TYPE,
				  PCI_EXP_TYPE_ROOT_PORT);
	पूर्ण

	regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12, mask, val);
पूर्ण

अटल व्योम imx6_pcie_init_phy(काष्ठा imx6_pcie *imx6_pcie)
अणु
	चयन (imx6_pcie->drvdata->variant) अणु
	हाल IMX8MQ:
		/*
		 * TODO: Currently this code assumes बाह्यal
		 * oscillator is being used
		 */
		regmap_update_bits(imx6_pcie->iomuxc_gpr,
				   imx6_pcie_grp_offset(imx6_pcie),
				   IMX8MQ_GPR_PCIE_REF_USE_PAD,
				   IMX8MQ_GPR_PCIE_REF_USE_PAD);
		अवरोध;
	हाल IMX7D:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX7D_GPR12_PCIE_PHY_REFCLK_SEL, 0);
		अवरोध;
	हाल IMX6SX:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6SX_GPR12_PCIE_RX_EQ_MASK,
				   IMX6SX_GPR12_PCIE_RX_EQ_2);
		fallthrough;
	शेष:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6Q_GPR12_PCIE_CTL_2, 0 << 10);

		/* configure स्थिरant input संकेत to the pcie ctrl and phy */
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6Q_GPR12_LOS_LEVEL, 9 << 4);

		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_DEEMPH_GEN1,
				   imx6_pcie->tx_deemph_gen1 << 0);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_DEEMPH_GEN2_3P5DB,
				   imx6_pcie->tx_deemph_gen2_3p5db << 6);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_DEEMPH_GEN2_6DB,
				   imx6_pcie->tx_deemph_gen2_6db << 12);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_SWING_FULL,
				   imx6_pcie->tx_swing_full << 18);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR8,
				   IMX6Q_GPR8_TX_SWING_LOW,
				   imx6_pcie->tx_swing_low << 25);
		अवरोध;
	पूर्ण

	imx6_pcie_configure_type(imx6_pcie);
पूर्ण

अटल पूर्णांक imx6_setup_phy_mpll(काष्ठा imx6_pcie *imx6_pcie)
अणु
	अचिन्हित दीर्घ phy_rate = clk_get_rate(imx6_pcie->pcie_phy);
	पूर्णांक mult, भाग;
	u16 val;

	अगर (!(imx6_pcie->drvdata->flags & IMX6_PCIE_FLAG_IMX6_PHY))
		वापस 0;

	चयन (phy_rate) अणु
	हाल 125000000:
		/*
		 * The शेष settings of the MPLL are क्रम a 125MHz input
		 * घड़ी, so no need to reconfigure anything in that हाल.
		 */
		वापस 0;
	हाल 100000000:
		mult = 25;
		भाग = 0;
		अवरोध;
	हाल 200000000:
		mult = 25;
		भाग = 1;
		अवरोध;
	शेष:
		dev_err(imx6_pcie->pci->dev,
			"Unsupported PHY reference clock rate %lu\n", phy_rate);
		वापस -EINVAL;
	पूर्ण

	pcie_phy_पढ़ो(imx6_pcie, PCIE_PHY_MPLL_OVRD_IN_LO, &val);
	val &= ~(PCIE_PHY_MPLL_MULTIPLIER_MASK <<
		 PCIE_PHY_MPLL_MULTIPLIER_SHIFT);
	val |= mult << PCIE_PHY_MPLL_MULTIPLIER_SHIFT;
	val |= PCIE_PHY_MPLL_MULTIPLIER_OVRD;
	pcie_phy_ग_लिखो(imx6_pcie, PCIE_PHY_MPLL_OVRD_IN_LO, val);

	pcie_phy_पढ़ो(imx6_pcie, PCIE_PHY_ATEOVRD, &val);
	val &= ~(PCIE_PHY_ATEOVRD_REF_CLKDIV_MASK <<
		 PCIE_PHY_ATEOVRD_REF_CLKDIV_SHIFT);
	val |= भाग << PCIE_PHY_ATEOVRD_REF_CLKDIV_SHIFT;
	val |= PCIE_PHY_ATEOVRD_EN;
	pcie_phy_ग_लिखो(imx6_pcie, PCIE_PHY_ATEOVRD, val);

	वापस 0;
पूर्ण

अटल पूर्णांक imx6_pcie_रुको_क्रम_speed_change(काष्ठा imx6_pcie *imx6_pcie)
अणु
	काष्ठा dw_pcie *pci = imx6_pcie->pci;
	काष्ठा device *dev = pci->dev;
	u32 पंचांगp;
	अचिन्हित पूर्णांक retries;

	क्रम (retries = 0; retries < 200; retries++) अणु
		पंचांगp = dw_pcie_पढ़ोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
		/* Test अगर the speed change finished. */
		अगर (!(पंचांगp & PORT_LOGIC_SPEED_CHANGE))
			वापस 0;
		usleep_range(100, 1000);
	पूर्ण

	dev_err(dev, "Speed change timeout\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम imx6_pcie_ltssm_enable(काष्ठा device *dev)
अणु
	काष्ठा imx6_pcie *imx6_pcie = dev_get_drvdata(dev);

	चयन (imx6_pcie->drvdata->variant) अणु
	हाल IMX6Q:
	हाल IMX6SX:
	हाल IMX6QP:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6Q_GPR12_PCIE_CTL_2,
				   IMX6Q_GPR12_PCIE_CTL_2);
		अवरोध;
	हाल IMX7D:
	हाल IMX8MQ:
		reset_control_deनिश्चित(imx6_pcie->apps_reset);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक imx6_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा imx6_pcie *imx6_pcie = to_imx6_pcie(pci);
	काष्ठा device *dev = pci->dev;
	u8 offset = dw_pcie_find_capability(pci, PCI_CAP_ID_EXP);
	u32 पंचांगp;
	पूर्णांक ret;

	/*
	 * Force Gen1 operation when starting the link.  In हाल the link is
	 * started in Gen2 mode, there is a possibility the devices on the
	 * bus will not be detected at all.  This happens with PCIe चयनes.
	 */
	पंचांगp = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_EXP_LNKCAP);
	पंचांगp &= ~PCI_EXP_LNKCAP_SLS;
	पंचांगp |= PCI_EXP_LNKCAP_SLS_2_5GB;
	dw_pcie_ग_लिखोl_dbi(pci, offset + PCI_EXP_LNKCAP, पंचांगp);

	/* Start LTSSM. */
	imx6_pcie_ltssm_enable(dev);

	ret = dw_pcie_रुको_क्रम_link(pci);
	अगर (ret)
		जाओ err_reset_phy;

	अगर (pci->link_gen == 2) अणु
		/* Allow Gen2 mode after the link is up. */
		पंचांगp = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_EXP_LNKCAP);
		पंचांगp &= ~PCI_EXP_LNKCAP_SLS;
		पंचांगp |= PCI_EXP_LNKCAP_SLS_5_0GB;
		dw_pcie_ग_लिखोl_dbi(pci, offset + PCI_EXP_LNKCAP, पंचांगp);

		/*
		 * Start Directed Speed Change so the best possible
		 * speed both link partners support can be negotiated.
		 */
		पंचांगp = dw_pcie_पढ़ोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
		पंचांगp |= PORT_LOGIC_SPEED_CHANGE;
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, पंचांगp);

		अगर (imx6_pcie->drvdata->flags &
		    IMX6_PCIE_FLAG_IMX6_SPEED_CHANGE) अणु
			/*
			 * On i.MX7, सूचीECT_SPEED_CHANGE behaves dअगरferently
			 * from i.MX6 family when no link speed transition
			 * occurs and we go Gen1 -> yep, Gen1. The dअगरference
			 * is that, in such हाल, it will not be cleared by HW
			 * which will cause the following code to report false
			 * failure.
			 */

			ret = imx6_pcie_रुको_क्रम_speed_change(imx6_pcie);
			अगर (ret) अणु
				dev_err(dev, "Failed to bring link up!\n");
				जाओ err_reset_phy;
			पूर्ण
		पूर्ण

		/* Make sure link training is finished as well! */
		ret = dw_pcie_रुको_क्रम_link(pci);
		अगर (ret) अणु
			dev_err(dev, "Failed to bring link up!\n");
			जाओ err_reset_phy;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(dev, "Link: Gen2 disabled\n");
	पूर्ण

	पंचांगp = dw_pcie_पढ़ोw_dbi(pci, offset + PCI_EXP_LNKSTA);
	dev_info(dev, "Link up, Gen%i\n", पंचांगp & PCI_EXP_LNKSTA_CLS);
	वापस 0;

err_reset_phy:
	dev_dbg(dev, "PHY DEBUG_R0=0x%08x DEBUG_R1=0x%08x\n",
		dw_pcie_पढ़ोl_dbi(pci, PCIE_PORT_DEBUG0),
		dw_pcie_पढ़ोl_dbi(pci, PCIE_PORT_DEBUG1));
	imx6_pcie_reset_phy(imx6_pcie);
	वापस ret;
पूर्ण

अटल पूर्णांक imx6_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा imx6_pcie *imx6_pcie = to_imx6_pcie(pci);

	imx6_pcie_निश्चित_core_reset(imx6_pcie);
	imx6_pcie_init_phy(imx6_pcie);
	imx6_pcie_deनिश्चित_core_reset(imx6_pcie);
	imx6_setup_phy_mpll(imx6_pcie);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops imx6_pcie_host_ops = अणु
	.host_init = imx6_pcie_host_init,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.start_link = imx6_pcie_start_link,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम imx6_pcie_ltssm_disable(काष्ठा device *dev)
अणु
	काष्ठा imx6_pcie *imx6_pcie = dev_get_drvdata(dev);

	चयन (imx6_pcie->drvdata->variant) अणु
	हाल IMX6SX:
	हाल IMX6QP:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6Q_GPR12_PCIE_CTL_2, 0);
		अवरोध;
	हाल IMX7D:
		reset_control_निश्चित(imx6_pcie->apps_reset);
		अवरोध;
	शेष:
		dev_err(dev, "ltssm_disable not supported\n");
	पूर्ण
पूर्ण

अटल व्योम imx6_pcie_pm_turnoff(काष्ठा imx6_pcie *imx6_pcie)
अणु
	काष्ठा device *dev = imx6_pcie->pci->dev;

	/* Some variants have a turnoff reset in DT */
	अगर (imx6_pcie->turnoff_reset) अणु
		reset_control_निश्चित(imx6_pcie->turnoff_reset);
		reset_control_deनिश्चित(imx6_pcie->turnoff_reset);
		जाओ pm_turnoff_sleep;
	पूर्ण

	/* Others poke directly at IOMUXC रेजिस्टरs */
	चयन (imx6_pcie->drvdata->variant) अणु
	हाल IMX6SX:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				IMX6SX_GPR12_PCIE_PM_TURN_OFF,
				IMX6SX_GPR12_PCIE_PM_TURN_OFF);
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				IMX6SX_GPR12_PCIE_PM_TURN_OFF, 0);
		अवरोध;
	शेष:
		dev_err(dev, "PME_Turn_Off not implemented\n");
		वापस;
	पूर्ण

	/*
	 * Components with an upstream port must respond to
	 * PME_Turn_Off with PME_TO_Ack but we can't check.
	 *
	 * The standard recommends a 1-10ms समयout after which to
	 * proceed anyway as अगर acks were received.
	 */
pm_turnoff_sleep:
	usleep_range(1000, 10000);
पूर्ण

अटल व्योम imx6_pcie_clk_disable(काष्ठा imx6_pcie *imx6_pcie)
अणु
	clk_disable_unprepare(imx6_pcie->pcie);
	clk_disable_unprepare(imx6_pcie->pcie_phy);
	clk_disable_unprepare(imx6_pcie->pcie_bus);

	चयन (imx6_pcie->drvdata->variant) अणु
	हाल IMX6SX:
		clk_disable_unprepare(imx6_pcie->pcie_inbound_axi);
		अवरोध;
	हाल IMX7D:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX7D_GPR12_PCIE_PHY_REFCLK_SEL,
				   IMX7D_GPR12_PCIE_PHY_REFCLK_SEL);
		अवरोध;
	हाल IMX8MQ:
		clk_disable_unprepare(imx6_pcie->pcie_aux);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक imx6_pcie_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा imx6_pcie *imx6_pcie = dev_get_drvdata(dev);

	अगर (!(imx6_pcie->drvdata->flags & IMX6_PCIE_FLAG_SUPPORTS_SUSPEND))
		वापस 0;

	imx6_pcie_pm_turnoff(imx6_pcie);
	imx6_pcie_clk_disable(imx6_pcie);
	imx6_pcie_ltssm_disable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक imx6_pcie_resume_noirq(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा imx6_pcie *imx6_pcie = dev_get_drvdata(dev);
	काष्ठा pcie_port *pp = &imx6_pcie->pci->pp;

	अगर (!(imx6_pcie->drvdata->flags & IMX6_PCIE_FLAG_SUPPORTS_SUSPEND))
		वापस 0;

	imx6_pcie_निश्चित_core_reset(imx6_pcie);
	imx6_pcie_init_phy(imx6_pcie);
	imx6_pcie_deनिश्चित_core_reset(imx6_pcie);
	dw_pcie_setup_rc(pp);

	ret = imx6_pcie_start_link(imx6_pcie->pci);
	अगर (ret < 0)
		dev_info(dev, "pcie link is down after resume.\n");

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops imx6_pcie_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(imx6_pcie_suspend_noirq,
				      imx6_pcie_resume_noirq)
पूर्ण;

अटल पूर्णांक imx6_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_pcie *pci;
	काष्ठा imx6_pcie *imx6_pcie;
	काष्ठा device_node *np;
	काष्ठा resource *dbi_base;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक ret;
	u16 val;

	imx6_pcie = devm_kzalloc(dev, माप(*imx6_pcie), GFP_KERNEL);
	अगर (!imx6_pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;
	pci->pp.ops = &imx6_pcie_host_ops;

	imx6_pcie->pci = pci;
	imx6_pcie->drvdata = of_device_get_match_data(dev);

	/* Find the PHY अगर one is defined, only imx7d uses it */
	np = of_parse_phandle(node, "fsl,imx7d-pcie-phy", 0);
	अगर (np) अणु
		काष्ठा resource res;

		ret = of_address_to_resource(np, 0, &res);
		अगर (ret) अणु
			dev_err(dev, "Unable to map PCIe PHY\n");
			वापस ret;
		पूर्ण
		imx6_pcie->phy_base = devm_ioremap_resource(dev, &res);
		अगर (IS_ERR(imx6_pcie->phy_base)) अणु
			dev_err(dev, "Unable to map PCIe PHY\n");
			वापस PTR_ERR(imx6_pcie->phy_base);
		पूर्ण
	पूर्ण

	dbi_base = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pci->dbi_base = devm_ioremap_resource(dev, dbi_base);
	अगर (IS_ERR(pci->dbi_base))
		वापस PTR_ERR(pci->dbi_base);

	/* Fetch GPIOs */
	imx6_pcie->reset_gpio = of_get_named_gpio(node, "reset-gpio", 0);
	imx6_pcie->gpio_active_high = of_property_पढ़ो_bool(node,
						"reset-gpio-active-high");
	अगर (gpio_is_valid(imx6_pcie->reset_gpio)) अणु
		ret = devm_gpio_request_one(dev, imx6_pcie->reset_gpio,
				imx6_pcie->gpio_active_high ?
					GPIOF_OUT_INIT_HIGH :
					GPIOF_OUT_INIT_LOW,
				"PCIe reset");
		अगर (ret) अणु
			dev_err(dev, "unable to get reset gpio\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (imx6_pcie->reset_gpio == -EPROBE_DEFER) अणु
		वापस imx6_pcie->reset_gpio;
	पूर्ण

	/* Fetch घड़ीs */
	imx6_pcie->pcie_phy = devm_clk_get(dev, "pcie_phy");
	अगर (IS_ERR(imx6_pcie->pcie_phy))
		वापस dev_err_probe(dev, PTR_ERR(imx6_pcie->pcie_phy),
				     "pcie_phy clock source missing or invalid\n");

	imx6_pcie->pcie_bus = devm_clk_get(dev, "pcie_bus");
	अगर (IS_ERR(imx6_pcie->pcie_bus))
		वापस dev_err_probe(dev, PTR_ERR(imx6_pcie->pcie_bus),
				     "pcie_bus clock source missing or invalid\n");

	imx6_pcie->pcie = devm_clk_get(dev, "pcie");
	अगर (IS_ERR(imx6_pcie->pcie))
		वापस dev_err_probe(dev, PTR_ERR(imx6_pcie->pcie),
				     "pcie clock source missing or invalid\n");

	चयन (imx6_pcie->drvdata->variant) अणु
	हाल IMX6SX:
		imx6_pcie->pcie_inbound_axi = devm_clk_get(dev,
							   "pcie_inbound_axi");
		अगर (IS_ERR(imx6_pcie->pcie_inbound_axi))
			वापस dev_err_probe(dev, PTR_ERR(imx6_pcie->pcie_inbound_axi),
					     "pcie_inbound_axi clock missing or invalid\n");
		अवरोध;
	हाल IMX8MQ:
		imx6_pcie->pcie_aux = devm_clk_get(dev, "pcie_aux");
		अगर (IS_ERR(imx6_pcie->pcie_aux))
			वापस dev_err_probe(dev, PTR_ERR(imx6_pcie->pcie_aux),
					     "pcie_aux clock source missing or invalid\n");
		fallthrough;
	हाल IMX7D:
		अगर (dbi_base->start == IMX8MQ_PCIE2_BASE_ADDR)
			imx6_pcie->controller_id = 1;

		imx6_pcie->pciephy_reset = devm_reset_control_get_exclusive(dev,
									    "pciephy");
		अगर (IS_ERR(imx6_pcie->pciephy_reset)) अणु
			dev_err(dev, "Failed to get PCIEPHY reset control\n");
			वापस PTR_ERR(imx6_pcie->pciephy_reset);
		पूर्ण

		imx6_pcie->apps_reset = devm_reset_control_get_exclusive(dev,
									 "apps");
		अगर (IS_ERR(imx6_pcie->apps_reset)) अणु
			dev_err(dev, "Failed to get PCIE APPS reset control\n");
			वापस PTR_ERR(imx6_pcie->apps_reset);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Grab turnoff reset */
	imx6_pcie->turnoff_reset = devm_reset_control_get_optional_exclusive(dev, "turnoff");
	अगर (IS_ERR(imx6_pcie->turnoff_reset)) अणु
		dev_err(dev, "Failed to get TURNOFF reset control\n");
		वापस PTR_ERR(imx6_pcie->turnoff_reset);
	पूर्ण

	/* Grab GPR config रेजिस्टर range */
	imx6_pcie->iomuxc_gpr =
		 syscon_regmap_lookup_by_compatible("fsl,imx6q-iomuxc-gpr");
	अगर (IS_ERR(imx6_pcie->iomuxc_gpr)) अणु
		dev_err(dev, "unable to find iomuxc registers\n");
		वापस PTR_ERR(imx6_pcie->iomuxc_gpr);
	पूर्ण

	/* Grab PCIe PHY Tx Settings */
	अगर (of_property_पढ़ो_u32(node, "fsl,tx-deemph-gen1",
				 &imx6_pcie->tx_deemph_gen1))
		imx6_pcie->tx_deemph_gen1 = 0;

	अगर (of_property_पढ़ो_u32(node, "fsl,tx-deemph-gen2-3p5db",
				 &imx6_pcie->tx_deemph_gen2_3p5db))
		imx6_pcie->tx_deemph_gen2_3p5db = 0;

	अगर (of_property_पढ़ो_u32(node, "fsl,tx-deemph-gen2-6db",
				 &imx6_pcie->tx_deemph_gen2_6db))
		imx6_pcie->tx_deemph_gen2_6db = 20;

	अगर (of_property_पढ़ो_u32(node, "fsl,tx-swing-full",
				 &imx6_pcie->tx_swing_full))
		imx6_pcie->tx_swing_full = 127;

	अगर (of_property_पढ़ो_u32(node, "fsl,tx-swing-low",
				 &imx6_pcie->tx_swing_low))
		imx6_pcie->tx_swing_low = 127;

	/* Limit link speed */
	pci->link_gen = 1;
	ret = of_property_पढ़ो_u32(node, "fsl,max-link-speed", &pci->link_gen);

	imx6_pcie->vpcie = devm_regulator_get_optional(&pdev->dev, "vpcie");
	अगर (IS_ERR(imx6_pcie->vpcie)) अणु
		अगर (PTR_ERR(imx6_pcie->vpcie) != -ENODEV)
			वापस PTR_ERR(imx6_pcie->vpcie);
		imx6_pcie->vpcie = शून्य;
	पूर्ण

	platक्रमm_set_drvdata(pdev, imx6_pcie);

	ret = imx6_pcie_attach_pd(dev);
	अगर (ret)
		वापस ret;

	ret = dw_pcie_host_init(&pci->pp);
	अगर (ret < 0)
		वापस ret;

	अगर (pci_msi_enabled()) अणु
		u8 offset = dw_pcie_find_capability(pci, PCI_CAP_ID_MSI);
		val = dw_pcie_पढ़ोw_dbi(pci, offset + PCI_MSI_FLAGS);
		val |= PCI_MSI_FLAGS_ENABLE;
		dw_pcie_ग_लिखोw_dbi(pci, offset + PCI_MSI_FLAGS, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx6_pcie_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx6_pcie *imx6_pcie = platक्रमm_get_drvdata(pdev);

	/* bring करोwn link, so bootloader माला_लो clean state in हाल of reboot */
	imx6_pcie_निश्चित_core_reset(imx6_pcie);
पूर्ण

अटल स्थिर काष्ठा imx6_pcie_drvdata drvdata[] = अणु
	[IMX6Q] = अणु
		.variant = IMX6Q,
		.flags = IMX6_PCIE_FLAG_IMX6_PHY |
			 IMX6_PCIE_FLAG_IMX6_SPEED_CHANGE,
		.dbi_length = 0x200,
	पूर्ण,
	[IMX6SX] = अणु
		.variant = IMX6SX,
		.flags = IMX6_PCIE_FLAG_IMX6_PHY |
			 IMX6_PCIE_FLAG_IMX6_SPEED_CHANGE |
			 IMX6_PCIE_FLAG_SUPPORTS_SUSPEND,
	पूर्ण,
	[IMX6QP] = अणु
		.variant = IMX6QP,
		.flags = IMX6_PCIE_FLAG_IMX6_PHY |
			 IMX6_PCIE_FLAG_IMX6_SPEED_CHANGE,
	पूर्ण,
	[IMX7D] = अणु
		.variant = IMX7D,
		.flags = IMX6_PCIE_FLAG_SUPPORTS_SUSPEND,
	पूर्ण,
	[IMX8MQ] = अणु
		.variant = IMX8MQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx6_pcie_of_match[] = अणु
	अणु .compatible = "fsl,imx6q-pcie",  .data = &drvdata[IMX6Q],  पूर्ण,
	अणु .compatible = "fsl,imx6sx-pcie", .data = &drvdata[IMX6SX], पूर्ण,
	अणु .compatible = "fsl,imx6qp-pcie", .data = &drvdata[IMX6QP], पूर्ण,
	अणु .compatible = "fsl,imx7d-pcie",  .data = &drvdata[IMX7D],  पूर्ण,
	अणु .compatible = "fsl,imx8mq-pcie", .data = &drvdata[IMX8MQ], पूर्ण ,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver imx6_pcie_driver = अणु
	.driver = अणु
		.name	= "imx6q-pcie",
		.of_match_table = imx6_pcie_of_match,
		.suppress_bind_attrs = true,
		.pm = &imx6_pcie_pm_ops,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
	.probe    = imx6_pcie_probe,
	.shutकरोwn = imx6_pcie_shutकरोwn,
पूर्ण;

अटल व्योम imx6_pcie_quirk(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_bus *bus = dev->bus;
	काष्ठा pcie_port *pp = bus->sysdata;

	/* Bus parent is the PCI bridge, its parent is this platक्रमm driver */
	अगर (!bus->dev.parent || !bus->dev.parent->parent)
		वापस;

	/* Make sure we only quirk devices associated with this driver */
	अगर (bus->dev.parent->parent->driver != &imx6_pcie_driver.driver)
		वापस;

	अगर (pci_is_root_bus(bus)) अणु
		काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
		काष्ठा imx6_pcie *imx6_pcie = to_imx6_pcie(pci);

		/*
		 * Limit config length to aव्योम the kernel पढ़ोing beyond
		 * the रेजिस्टर set and causing an पात on i.MX 6Quad
		 */
		अगर (imx6_pcie->drvdata->dbi_length) अणु
			dev->cfg_size = imx6_pcie->drvdata->dbi_length;
			dev_info(&dev->dev, "Limiting cfg_size to %d\n",
					dev->cfg_size);
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_CLASS_HEADER(PCI_VENDOR_ID_SYNOPSYS, 0xabcd,
			PCI_CLASS_BRIDGE_PCI, 8, imx6_pcie_quirk);

अटल पूर्णांक __init imx6_pcie_init(व्योम)
अणु
#अगर_घोषित CONFIG_ARM
	/*
	 * Since probe() can be deferred we need to make sure that
	 * hook_fault_code is not called after __init memory is मुक्तd
	 * by kernel and since imx6q_pcie_पात_handler() is a no-op,
	 * we can install the handler here without risking it
	 * accessing some uninitialized driver state.
	 */
	hook_fault_code(8, imx6q_pcie_पात_handler, SIGBUS, 0,
			"external abort on non-linefetch");
#पूर्ण_अगर

	वापस platक्रमm_driver_रेजिस्टर(&imx6_pcie_driver);
पूर्ण
device_initcall(imx6_pcie_init);
