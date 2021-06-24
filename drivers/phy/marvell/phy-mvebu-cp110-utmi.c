<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2021 Marvell
 *
 * Authors:
 *   Konstantin Porotchkin <kostap@marvell.com>
 *
 * Marvell CP110 UTMI PHY driver
 */

#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/usb/otg.h>

#घोषणा UTMI_PHY_PORTS				2

/* CP110 UTMI रेजिस्टर macro definetions */
#घोषणा SYSCON_USB_CFG_REG			0x420
#घोषणा   USB_CFG_DEVICE_EN_MASK		BIT(0)
#घोषणा   USB_CFG_DEVICE_MUX_OFFSET		1
#घोषणा   USB_CFG_DEVICE_MUX_MASK		BIT(1)
#घोषणा   USB_CFG_PLL_MASK			BIT(25)

#घोषणा SYSCON_UTMI_CFG_REG(id)			(0x440 + (id) * 4)
#घोषणा   UTMI_PHY_CFG_PU_MASK			BIT(5)

#घोषणा UTMI_PLL_CTRL_REG			0x0
#घोषणा   PLL_REFDIV_OFFSET			0
#घोषणा   PLL_REFDIV_MASK			GENMASK(6, 0)
#घोषणा   PLL_REFDIV_VAL			0x5
#घोषणा   PLL_FBDIV_OFFSET			16
#घोषणा   PLL_FBDIV_MASK			GENMASK(24, 16)
#घोषणा   PLL_FBDIV_VAL				0x60
#घोषणा   PLL_SEL_LPFR_MASK			GENMASK(29, 28)
#घोषणा   PLL_RDY				BIT(31)
#घोषणा UTMI_CAL_CTRL_REG			0x8
#घोषणा   IMPCAL_VTH_OFFSET			8
#घोषणा   IMPCAL_VTH_MASK			GENMASK(10, 8)
#घोषणा   IMPCAL_VTH_VAL			0x7
#घोषणा   IMPCAL_DONE				BIT(23)
#घोषणा   PLLCAL_DONE				BIT(31)
#घोषणा UTMI_TX_CH_CTRL_REG			0xC
#घोषणा   DRV_EN_LS_OFFSET			12
#घोषणा   DRV_EN_LS_MASK			GENMASK(15, 12)
#घोषणा   IMP_SEL_LS_OFFSET			16
#घोषणा   IMP_SEL_LS_MASK			GENMASK(19, 16)
#घोषणा   TX_AMP_OFFSET				20
#घोषणा   TX_AMP_MASK				GENMASK(22, 20)
#घोषणा   TX_AMP_VAL				0x4
#घोषणा UTMI_RX_CH_CTRL0_REG			0x14
#घोषणा   SQ_DET_EN				BIT(15)
#घोषणा   SQ_ANA_DTC_SEL			BIT(28)
#घोषणा UTMI_RX_CH_CTRL1_REG			0x18
#घोषणा   SQ_AMP_CAL_OFFSET			0
#घोषणा   SQ_AMP_CAL_MASK			GENMASK(2, 0)
#घोषणा   SQ_AMP_CAL_VAL			1
#घोषणा   SQ_AMP_CAL_EN				BIT(3)
#घोषणा UTMI_CTRL_STATUS0_REG			0x24
#घोषणा   SUSPENDM				BIT(22)
#घोषणा   TEST_SEL				BIT(25)
#घोषणा UTMI_CHGDTC_CTRL_REG			0x38
#घोषणा   VDAT_OFFSET				8
#घोषणा   VDAT_MASK				GENMASK(9, 8)
#घोषणा   VDAT_VAL				1
#घोषणा   VSRC_OFFSET				10
#घोषणा   VSRC_MASK				GENMASK(11, 10)
#घोषणा   VSRC_VAL				1

#घोषणा PLL_LOCK_DELAY_US			10000
#घोषणा PLL_LOCK_TIMEOUT_US			1000000

#घोषणा PORT_REGS(p)				((p)->priv->regs + (p)->id * 0x1000)

/**
 * काष्ठा mvebu_cp110_uपंचांगi - PHY driver data
 *
 * @regs: PHY रेजिस्टरs
 * @syscom: Regmap with प्रणाली controller रेजिस्टरs
 * @dev: device driver handle
 * @caps: PHY capabilities
 */
काष्ठा mvebu_cp110_uपंचांगi अणु
	व्योम __iomem *regs;
	काष्ठा regmap *syscon;
	काष्ठा device *dev;
	स्थिर काष्ठा phy_ops *ops;
पूर्ण;

/**
 * काष्ठा mvebu_cp110_uपंचांगi_port - PHY port data
 *
 * @priv: PHY driver data
 * @id: PHY port ID
 * @dr_mode: PHY connection: USB_DR_MODE_HOST or USB_DR_MODE_PERIPHERAL
 */
काष्ठा mvebu_cp110_uपंचांगi_port अणु
	काष्ठा mvebu_cp110_uपंचांगi *priv;
	u32 id;
	क्रमागत usb_dr_mode dr_mode;
पूर्ण;

अटल व्योम mvebu_cp110_uपंचांगi_port_setup(काष्ठा mvebu_cp110_uपंचांगi_port *port)
अणु
	u32 reg;

	/*
	 * Setup PLL.
	 * The reference घड़ी is the frequency of quartz resonator
	 * connected to pins REFCLK_XIN and REFCLK_XOUT of the SoC.
	 * Register init values are matching the 40MHz शेष घड़ी.
	 * The crystal used क्रम all platक्रमm boards is now 25MHz.
	 * See the functional specअगरication क्रम details.
	 */
	reg = पढ़ोl(PORT_REGS(port) + UTMI_PLL_CTRL_REG);
	reg &= ~(PLL_REFDIV_MASK | PLL_FBDIV_MASK | PLL_SEL_LPFR_MASK);
	reg |= (PLL_REFDIV_VAL << PLL_REFDIV_OFFSET) |
	       (PLL_FBDIV_VAL << PLL_FBDIV_OFFSET);
	ग_लिखोl(reg, PORT_REGS(port) + UTMI_PLL_CTRL_REG);

	/* Impedance Calibration Threshold Setting */
	reg = पढ़ोl(PORT_REGS(port) + UTMI_CAL_CTRL_REG);
	reg &= ~IMPCAL_VTH_MASK;
	reg |= IMPCAL_VTH_VAL << IMPCAL_VTH_OFFSET;
	ग_लिखोl(reg, PORT_REGS(port) + UTMI_CAL_CTRL_REG);

	/* Set LS TX driver strength coarse control */
	reg = पढ़ोl(PORT_REGS(port) + UTMI_TX_CH_CTRL_REG);
	reg &= ~TX_AMP_MASK;
	reg |= TX_AMP_VAL << TX_AMP_OFFSET;
	ग_लिखोl(reg, PORT_REGS(port) + UTMI_TX_CH_CTRL_REG);

	/* Disable SQ and enable analog squelch detect */
	reg = पढ़ोl(PORT_REGS(port) + UTMI_RX_CH_CTRL0_REG);
	reg &= ~SQ_DET_EN;
	reg |= SQ_ANA_DTC_SEL;
	ग_लिखोl(reg, PORT_REGS(port) + UTMI_RX_CH_CTRL0_REG);

	/*
	 * Set External squelch calibration number and
	 * enable the External squelch calibration
	 */
	reg = पढ़ोl(PORT_REGS(port) + UTMI_RX_CH_CTRL1_REG);
	reg &= ~SQ_AMP_CAL_MASK;
	reg |= (SQ_AMP_CAL_VAL << SQ_AMP_CAL_OFFSET) | SQ_AMP_CAL_EN;
	ग_लिखोl(reg, PORT_REGS(port) + UTMI_RX_CH_CTRL1_REG);

	/*
	 * Set Control VDAT Reference Voltage - 0.325V and
	 * Control VSRC Reference Voltage - 0.6V
	 */
	reg = पढ़ोl(PORT_REGS(port) + UTMI_CHGDTC_CTRL_REG);
	reg &= ~(VDAT_MASK | VSRC_MASK);
	reg |= (VDAT_VAL << VDAT_OFFSET) | (VSRC_VAL << VSRC_OFFSET);
	ग_लिखोl(reg, PORT_REGS(port) + UTMI_CHGDTC_CTRL_REG);
पूर्ण

अटल पूर्णांक mvebu_cp110_uपंचांगi_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_cp110_uपंचांगi_port *port = phy_get_drvdata(phy);
	काष्ठा mvebu_cp110_uपंचांगi *uपंचांगi = port->priv;
	पूर्णांक i;

	/* Power करोwn UTMI PHY port */
	regmap_clear_bits(uपंचांगi->syscon, SYSCON_UTMI_CFG_REG(port->id),
			  UTMI_PHY_CFG_PU_MASK);

	क्रम (i = 0; i < UTMI_PHY_PORTS; i++) अणु
		पूर्णांक test = regmap_test_bits(uपंचांगi->syscon,
					    SYSCON_UTMI_CFG_REG(i),
					    UTMI_PHY_CFG_PU_MASK);
		/* skip PLL shutकरोwn अगर there are active UTMI PHY ports */
		अगर (test != 0)
			वापस 0;
	पूर्ण

	/* PLL Power करोwn अगर all UTMI PHYs are करोwn */
	regmap_clear_bits(uपंचांगi->syscon, SYSCON_USB_CFG_REG, USB_CFG_PLL_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_cp110_uपंचांगi_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_cp110_uपंचांगi_port *port = phy_get_drvdata(phy);
	काष्ठा mvebu_cp110_uपंचांगi *uपंचांगi = port->priv;
	काष्ठा device *dev = &phy->dev;
	पूर्णांक ret;
	u32 reg;

	/* It is necessary to घातer off UTMI beक्रमe configuration */
	ret = mvebu_cp110_uपंचांगi_phy_घातer_off(phy);
	अगर (ret) अणु
		dev_err(dev, "UTMI power OFF before power ON failed\n");
		वापस ret;
	पूर्ण

	/*
	 * If UTMI port is connected to USB Device controller,
	 * configure the USB MUX prior to UTMI PHY initialization.
	 * The single USB device controller can be connected
	 * to UTMI0 or to UTMI1 PHY port, but not to both.
	 */
	अगर (port->dr_mode == USB_DR_MODE_PERIPHERAL) अणु
		regmap_update_bits(uपंचांगi->syscon, SYSCON_USB_CFG_REG,
				   USB_CFG_DEVICE_EN_MASK | USB_CFG_DEVICE_MUX_MASK,
				   USB_CFG_DEVICE_EN_MASK |
				   (port->id << USB_CFG_DEVICE_MUX_OFFSET));
	पूर्ण

	/* Set Test suspendm mode and enable Test UTMI select */
	reg = पढ़ोl(PORT_REGS(port) + UTMI_CTRL_STATUS0_REG);
	reg |= SUSPENDM | TEST_SEL;
	ग_लिखोl(reg, PORT_REGS(port) + UTMI_CTRL_STATUS0_REG);

	/* Wait क्रम UTMI घातer करोwn */
	mdelay(1);

	/* PHY port setup first */
	mvebu_cp110_uपंचांगi_port_setup(port);

	/* Power UP UTMI PHY */
	regmap_set_bits(uपंचांगi->syscon, SYSCON_UTMI_CFG_REG(port->id),
			UTMI_PHY_CFG_PU_MASK);

	/* Disable Test UTMI select */
	reg = पढ़ोl(PORT_REGS(port) + UTMI_CTRL_STATUS0_REG);
	reg &= ~TEST_SEL;
	ग_लिखोl(reg, PORT_REGS(port) + UTMI_CTRL_STATUS0_REG);

	/* Wait क्रम impedance calibration */
	ret = पढ़ोl_poll_समयout(PORT_REGS(port) + UTMI_CAL_CTRL_REG, reg,
				 reg & IMPCAL_DONE,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dev, "Failed to end UTMI impedance calibration\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम PLL calibration */
	ret = पढ़ोl_poll_समयout(PORT_REGS(port) + UTMI_CAL_CTRL_REG, reg,
				 reg & PLLCAL_DONE,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dev, "Failed to end UTMI PLL calibration\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम PLL पढ़ोy */
	ret = पढ़ोl_poll_समयout(PORT_REGS(port) + UTMI_PLL_CTRL_REG, reg,
				 reg & PLL_RDY,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dev, "PLL is not ready\n");
		वापस ret;
	पूर्ण

	/* PLL Power up */
	regmap_set_bits(uपंचांगi->syscon, SYSCON_USB_CFG_REG, USB_CFG_PLL_MASK);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops mvebu_cp110_uपंचांगi_phy_ops = अणु
	.घातer_on = mvebu_cp110_uपंचांगi_phy_घातer_on,
	.घातer_off = mvebu_cp110_uपंचांगi_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mvebu_cp110_uपंचांगi_of_match[] = अणु
	अणु .compatible = "marvell,cp110-utmi-phy" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mvebu_cp110_uपंचांगi_of_match);

अटल पूर्णांक mvebu_cp110_uपंचांगi_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mvebu_cp110_uपंचांगi *uपंचांगi;
	काष्ठा phy_provider *provider;
	काष्ठा device_node *child;
	u32 usb_devices = 0;

	uपंचांगi = devm_kzalloc(dev, माप(*uपंचांगi), GFP_KERNEL);
	अगर (!uपंचांगi)
		वापस -ENOMEM;

	uपंचांगi->dev = dev;

	/* Get प्रणाली controller region */
	uपंचांगi->syscon = syscon_regmap_lookup_by_phandle(dev->of_node,
						       "marvell,system-controller");
	अगर (IS_ERR(uपंचांगi->syscon)) अणु
		dev_err(dev, "Missing UTMI system controller\n");
		वापस PTR_ERR(uपंचांगi->syscon);
	पूर्ण

	/* Get UTMI memory region */
	uपंचांगi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(uपंचांगi->regs))
		वापस PTR_ERR(uपंचांगi->regs);

	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		काष्ठा mvebu_cp110_uपंचांगi_port *port;
		काष्ठा phy *phy;
		पूर्णांक ret;
		u32 port_id;

		ret = of_property_पढ़ो_u32(child, "reg", &port_id);
		अगर ((ret < 0) || (port_id >= UTMI_PHY_PORTS)) अणु
			dev_err(dev,
				"invalid 'reg' property on child %pOF\n",
				child);
			जारी;
		पूर्ण

		port = devm_kzalloc(dev, माप(*port), GFP_KERNEL);
		अगर (!port) अणु
			of_node_put(child);
			वापस -ENOMEM;
		पूर्ण

		port->dr_mode = of_usb_get_dr_mode_by_phy(child, -1);
		अगर ((port->dr_mode != USB_DR_MODE_HOST) &&
		    (port->dr_mode != USB_DR_MODE_PERIPHERAL)) अणु
			dev_err(&pdev->dev,
				"Missing dual role setting of the port%d, will use HOST mode\n",
				port_id);
			port->dr_mode = USB_DR_MODE_HOST;
		पूर्ण

		अगर (port->dr_mode == USB_DR_MODE_PERIPHERAL) अणु
			usb_devices++;
			अगर (usb_devices > 1) अणु
				dev_err(dev,
					"Single USB device allowed! Port%d will use HOST mode\n",
					port_id);
				port->dr_mode = USB_DR_MODE_HOST;
			पूर्ण
		पूर्ण

		/* Retrieve PHY capabilities */
		uपंचांगi->ops = &mvebu_cp110_uपंचांगi_phy_ops;

		/* Instantiate the PHY */
		phy = devm_phy_create(dev, child, uपंचांगi->ops);
		अगर (IS_ERR(phy)) अणु
			dev_err(dev, "Failed to create the UTMI PHY\n");
			of_node_put(child);
			वापस PTR_ERR(phy);
		पूर्ण

		port->priv = uपंचांगi;
		port->id = port_id;
		phy_set_drvdata(phy, port);

		/* Ensure the PHY is घातered off */
		mvebu_cp110_uपंचांगi_phy_घातer_off(phy);
	पूर्ण

	dev_set_drvdata(dev, uपंचांगi);
	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल काष्ठा platक्रमm_driver mvebu_cp110_uपंचांगi_driver = अणु
	.probe	= mvebu_cp110_uपंचांगi_phy_probe,
	.driver	= अणु
		.name		= "mvebu-cp110-utmi-phy",
		.of_match_table	= mvebu_cp110_uपंचांगi_of_match,
	 पूर्ण,
पूर्ण;
module_platक्रमm_driver(mvebu_cp110_uपंचांगi_driver);

MODULE_AUTHOR("Konstatin Porotchkin <kostap@marvell.com>");
MODULE_DESCRIPTION("Marvell Armada CP110 UTMI PHY driver");
MODULE_LICENSE("GPL v2");
