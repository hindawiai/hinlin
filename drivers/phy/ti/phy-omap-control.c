<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * omap-control-phy.c - The PHY part of control module.
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/phy/omap_control_phy.h>

/**
 * omap_control_pcie_pcs - set the PCS delay count
 * @dev: the control module device
 * @delay: 8 bit delay value
 */
व्योम omap_control_pcie_pcs(काष्ठा device *dev, u8 delay)
अणु
	u32 val;
	काष्ठा omap_control_phy	*control_phy;

	अगर (IS_ERR(dev) || !dev) अणु
		pr_err("%s: invalid device\n", __func__);
		वापस;
	पूर्ण

	control_phy = dev_get_drvdata(dev);
	अगर (!control_phy) अणु
		dev_err(dev, "%s: invalid control phy device\n", __func__);
		वापस;
	पूर्ण

	अगर (control_phy->type != OMAP_CTRL_TYPE_PCIE) अणु
		dev_err(dev, "%s: unsupported operation\n", __func__);
		वापस;
	पूर्ण

	val = पढ़ोl(control_phy->pcie_pcs);
	val &= ~(OMAP_CTRL_PCIE_PCS_MASK <<
		OMAP_CTRL_PCIE_PCS_DELAY_COUNT_SHIFT);
	val |= (delay << OMAP_CTRL_PCIE_PCS_DELAY_COUNT_SHIFT);
	ग_लिखोl(val, control_phy->pcie_pcs);
पूर्ण
EXPORT_SYMBOL_GPL(omap_control_pcie_pcs);

/**
 * omap_control_phy_घातer - घातer on/off the phy using control module reg
 * @dev: the control module device
 * @on: 0 or 1, based on घातering on or off the PHY
 */
व्योम omap_control_phy_घातer(काष्ठा device *dev, पूर्णांक on)
अणु
	u32 val;
	अचिन्हित दीर्घ rate;
	काष्ठा omap_control_phy	*control_phy;

	अगर (IS_ERR(dev) || !dev) अणु
		pr_err("%s: invalid device\n", __func__);
		वापस;
	पूर्ण

	control_phy = dev_get_drvdata(dev);
	अगर (!control_phy) अणु
		dev_err(dev, "%s: invalid control phy device\n", __func__);
		वापस;
	पूर्ण

	अगर (control_phy->type == OMAP_CTRL_TYPE_OTGHS)
		वापस;

	val = पढ़ोl(control_phy->घातer);

	चयन (control_phy->type) अणु
	हाल OMAP_CTRL_TYPE_USB2:
		अगर (on)
			val &= ~OMAP_CTRL_DEV_PHY_PD;
		अन्यथा
			val |= OMAP_CTRL_DEV_PHY_PD;
		अवरोध;

	हाल OMAP_CTRL_TYPE_PCIE:
	हाल OMAP_CTRL_TYPE_PIPE3:
		rate = clk_get_rate(control_phy->sys_clk);
		rate = rate/1000000;

		अगर (on) अणु
			val &= ~(OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_CMD_MASK |
				OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_MASK);
			val |= OMAP_CTRL_PIPE3_PHY_TX_RX_POWERON <<
				OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_CMD_SHIFT;
			val |= rate <<
				OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_SHIFT;
		पूर्ण अन्यथा अणु
			val &= ~OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_CMD_MASK;
			val |= OMAP_CTRL_PIPE3_PHY_TX_RX_POWEROFF <<
				OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_CMD_SHIFT;
		पूर्ण
		अवरोध;

	हाल OMAP_CTRL_TYPE_DRA7USB2:
		अगर (on)
			val &= ~OMAP_CTRL_USB2_PHY_PD;
		अन्यथा
			val |= OMAP_CTRL_USB2_PHY_PD;
		अवरोध;

	हाल OMAP_CTRL_TYPE_AM437USB2:
		अगर (on) अणु
			val &= ~(AM437X_CTRL_USB2_PHY_PD |
					AM437X_CTRL_USB2_OTG_PD);
			val |= (AM437X_CTRL_USB2_OTGVDET_EN |
					AM437X_CTRL_USB2_OTGSESSEND_EN);
		पूर्ण अन्यथा अणु
			val &= ~(AM437X_CTRL_USB2_OTGVDET_EN |
					AM437X_CTRL_USB2_OTGSESSEND_EN);
			val |= (AM437X_CTRL_USB2_PHY_PD |
					 AM437X_CTRL_USB2_OTG_PD);
		पूर्ण
		अवरोध;
	शेष:
		dev_err(dev, "%s: type %d not recognized\n",
			__func__, control_phy->type);
		अवरोध;
	पूर्ण

	ग_लिखोl(val, control_phy->घातer);
पूर्ण
EXPORT_SYMBOL_GPL(omap_control_phy_घातer);

/**
 * omap_control_usb_host_mode - set AVALID, VBUSVALID and ID pin in grounded
 * @ctrl_phy: काष्ठा omap_control_phy *
 *
 * Writes to the mailbox रेजिस्टर to notअगरy the usb core that a usb
 * device has been connected.
 */
अटल व्योम omap_control_usb_host_mode(काष्ठा omap_control_phy *ctrl_phy)
अणु
	u32 val;

	val = पढ़ोl(ctrl_phy->otghs_control);
	val &= ~(OMAP_CTRL_DEV_IDDIG | OMAP_CTRL_DEV_SESSEND);
	val |= OMAP_CTRL_DEV_AVALID | OMAP_CTRL_DEV_VBUSVALID;
	ग_लिखोl(val, ctrl_phy->otghs_control);
पूर्ण

/**
 * omap_control_usb_device_mode - set AVALID, VBUSVALID and ID pin in high
 * impedance
 * @ctrl_phy: काष्ठा omap_control_phy *
 *
 * Writes to the mailbox रेजिस्टर to notअगरy the usb core that it has been
 * connected to a usb host.
 */
अटल व्योम omap_control_usb_device_mode(काष्ठा omap_control_phy *ctrl_phy)
अणु
	u32 val;

	val = पढ़ोl(ctrl_phy->otghs_control);
	val &= ~OMAP_CTRL_DEV_SESSEND;
	val |= OMAP_CTRL_DEV_IDDIG | OMAP_CTRL_DEV_AVALID |
		OMAP_CTRL_DEV_VBUSVALID;
	ग_लिखोl(val, ctrl_phy->otghs_control);
पूर्ण

/**
 * omap_control_usb_set_sessionend - Enable SESSIONEND and IDIG to high
 * impedance
 * @ctrl_phy: काष्ठा omap_control_phy *
 *
 * Writes to the mailbox रेजिस्टर to notअगरy the usb core it's now in
 * disconnected state.
 */
अटल व्योम omap_control_usb_set_sessionend(काष्ठा omap_control_phy *ctrl_phy)
अणु
	u32 val;

	val = पढ़ोl(ctrl_phy->otghs_control);
	val &= ~(OMAP_CTRL_DEV_AVALID | OMAP_CTRL_DEV_VBUSVALID);
	val |= OMAP_CTRL_DEV_IDDIG | OMAP_CTRL_DEV_SESSEND;
	ग_लिखोl(val, ctrl_phy->otghs_control);
पूर्ण

/**
 * omap_control_usb_set_mode - Calls to functions to set USB in one of host mode
 * or device mode or to denote disconnected state
 * @dev: the control module device
 * @mode: The mode to which usb should be configured
 *
 * This is an API to ग_लिखो to the mailbox रेजिस्टर to notअगरy the usb core that
 * a usb device has been connected.
 */
व्योम omap_control_usb_set_mode(काष्ठा device *dev,
	क्रमागत omap_control_usb_mode mode)
अणु
	काष्ठा omap_control_phy	*ctrl_phy;

	अगर (IS_ERR(dev) || !dev)
		वापस;

	ctrl_phy = dev_get_drvdata(dev);
	अगर (!ctrl_phy) अणु
		dev_err(dev, "Invalid control phy device\n");
		वापस;
	पूर्ण

	अगर (ctrl_phy->type != OMAP_CTRL_TYPE_OTGHS)
		वापस;

	चयन (mode) अणु
	हाल USB_MODE_HOST:
		omap_control_usb_host_mode(ctrl_phy);
		अवरोध;
	हाल USB_MODE_DEVICE:
		omap_control_usb_device_mode(ctrl_phy);
		अवरोध;
	हाल USB_MODE_DISCONNECT:
		omap_control_usb_set_sessionend(ctrl_phy);
		अवरोध;
	शेष:
		dev_vdbg(dev, "invalid omap control usb mode\n");
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(omap_control_usb_set_mode);

अटल स्थिर क्रमागत omap_control_phy_type otghs_data = OMAP_CTRL_TYPE_OTGHS;
अटल स्थिर क्रमागत omap_control_phy_type usb2_data = OMAP_CTRL_TYPE_USB2;
अटल स्थिर क्रमागत omap_control_phy_type pipe3_data = OMAP_CTRL_TYPE_PIPE3;
अटल स्थिर क्रमागत omap_control_phy_type pcie_data = OMAP_CTRL_TYPE_PCIE;
अटल स्थिर क्रमागत omap_control_phy_type dra7usb2_data = OMAP_CTRL_TYPE_DRA7USB2;
अटल स्थिर क्रमागत omap_control_phy_type am437usb2_data = OMAP_CTRL_TYPE_AM437USB2;

अटल स्थिर काष्ठा of_device_id omap_control_phy_id_table[] = अणु
	अणु
		.compatible = "ti,control-phy-otghs",
		.data = &otghs_data,
	पूर्ण,
	अणु
		.compatible = "ti,control-phy-usb2",
		.data = &usb2_data,
	पूर्ण,
	अणु
		.compatible = "ti,control-phy-pipe3",
		.data = &pipe3_data,
	पूर्ण,
	अणु
		.compatible = "ti,control-phy-pcie",
		.data = &pcie_data,
	पूर्ण,
	अणु
		.compatible = "ti,control-phy-usb2-dra7",
		.data = &dra7usb2_data,
	पूर्ण,
	अणु
		.compatible = "ti,control-phy-usb2-am437",
		.data = &am437usb2_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_control_phy_id_table);

अटल पूर्णांक omap_control_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा omap_control_phy *control_phy;

	of_id = of_match_device(omap_control_phy_id_table, &pdev->dev);
	अगर (!of_id)
		वापस -EINVAL;

	control_phy = devm_kzalloc(&pdev->dev, माप(*control_phy),
		GFP_KERNEL);
	अगर (!control_phy)
		वापस -ENOMEM;

	control_phy->dev = &pdev->dev;
	control_phy->type = *(क्रमागत omap_control_phy_type *)of_id->data;

	अगर (control_phy->type == OMAP_CTRL_TYPE_OTGHS) अणु
		control_phy->otghs_control =
			devm_platक्रमm_ioremap_resource_byname(pdev, "otghs_control");
		अगर (IS_ERR(control_phy->otghs_control))
			वापस PTR_ERR(control_phy->otghs_control);
	पूर्ण अन्यथा अणु
		control_phy->घातer =
			devm_platक्रमm_ioremap_resource_byname(pdev, "power");
		अगर (IS_ERR(control_phy->घातer)) अणु
			dev_err(&pdev->dev, "Couldn't get power register\n");
			वापस PTR_ERR(control_phy->घातer);
		पूर्ण
	पूर्ण

	अगर (control_phy->type == OMAP_CTRL_TYPE_PIPE3 ||
	    control_phy->type == OMAP_CTRL_TYPE_PCIE) अणु
		control_phy->sys_clk = devm_clk_get(control_phy->dev,
			"sys_clkin");
		अगर (IS_ERR(control_phy->sys_clk)) अणु
			pr_err("%s: unable to get sys_clkin\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (control_phy->type == OMAP_CTRL_TYPE_PCIE) अणु
		control_phy->pcie_pcs =
			devm_platक्रमm_ioremap_resource_byname(pdev, "pcie_pcs");
		अगर (IS_ERR(control_phy->pcie_pcs))
			वापस PTR_ERR(control_phy->pcie_pcs);
	पूर्ण

	dev_set_drvdata(control_phy->dev, control_phy);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_control_phy_driver = अणु
	.probe		= omap_control_phy_probe,
	.driver		= अणु
		.name	= "omap-control-phy",
		.of_match_table = omap_control_phy_id_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init omap_control_phy_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_control_phy_driver);
पूर्ण
subsys_initcall(omap_control_phy_init);

अटल व्योम __निकास omap_control_phy_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_control_phy_driver);
पूर्ण
module_निकास(omap_control_phy_निकास);

MODULE_ALIAS("platform:omap_control_phy");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_DESCRIPTION("OMAP Control Module PHY Driver");
MODULE_LICENSE("GPL v2");
