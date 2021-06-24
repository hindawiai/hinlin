<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2018 John Crispin <john@phrozen.org>
 *
 * Based on code from
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

काष्ठा ipq4019_usb_phy अणु
	काष्ठा device		*dev;
	काष्ठा phy		*phy;
	व्योम __iomem		*base;
	काष्ठा reset_control	*por_rst;
	काष्ठा reset_control	*srअगर_rst;
पूर्ण;

अटल पूर्णांक ipq4019_ss_phy_घातer_off(काष्ठा phy *_phy)
अणु
	काष्ठा ipq4019_usb_phy *phy = phy_get_drvdata(_phy);

	reset_control_निश्चित(phy->por_rst);
	msleep(10);

	वापस 0;
पूर्ण

अटल पूर्णांक ipq4019_ss_phy_घातer_on(काष्ठा phy *_phy)
अणु
	काष्ठा ipq4019_usb_phy *phy = phy_get_drvdata(_phy);

	ipq4019_ss_phy_घातer_off(_phy);

	reset_control_deनिश्चित(phy->por_rst);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ipq4019_usb_ss_phy_ops = अणु
	.घातer_on	= ipq4019_ss_phy_घातer_on,
	.घातer_off	= ipq4019_ss_phy_घातer_off,
पूर्ण;

अटल पूर्णांक ipq4019_hs_phy_घातer_off(काष्ठा phy *_phy)
अणु
	काष्ठा ipq4019_usb_phy *phy = phy_get_drvdata(_phy);

	reset_control_निश्चित(phy->por_rst);
	msleep(10);

	reset_control_निश्चित(phy->srअगर_rst);
	msleep(10);

	वापस 0;
पूर्ण

अटल पूर्णांक ipq4019_hs_phy_घातer_on(काष्ठा phy *_phy)
अणु
	काष्ठा ipq4019_usb_phy *phy = phy_get_drvdata(_phy);

	ipq4019_hs_phy_घातer_off(_phy);

	reset_control_deनिश्चित(phy->srअगर_rst);
	msleep(10);

	reset_control_deनिश्चित(phy->por_rst);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ipq4019_usb_hs_phy_ops = अणु
	.घातer_on	= ipq4019_hs_phy_घातer_on,
	.घातer_off	= ipq4019_hs_phy_घातer_off,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ipq4019_usb_phy_of_match[] = अणु
	अणु .compatible = "qcom,usb-hs-ipq4019-phy", .data = &ipq4019_usb_hs_phy_opsपूर्ण,
	अणु .compatible = "qcom,usb-ss-ipq4019-phy", .data = &ipq4019_usb_ss_phy_opsपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ipq4019_usb_phy_of_match);

अटल पूर्णांक ipq4019_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	काष्ठा ipq4019_usb_phy *phy;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->dev = &pdev->dev;
	phy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy->base)) अणु
		dev_err(dev, "failed to remap register memory\n");
		वापस PTR_ERR(phy->base);
	पूर्ण

	phy->por_rst = devm_reset_control_get(phy->dev, "por_rst");
	अगर (IS_ERR(phy->por_rst)) अणु
		अगर (PTR_ERR(phy->por_rst) != -EPROBE_DEFER)
			dev_err(dev, "POR reset is missing\n");
		वापस PTR_ERR(phy->por_rst);
	पूर्ण

	phy->srअगर_rst = devm_reset_control_get_optional(phy->dev, "srif_rst");
	अगर (IS_ERR(phy->srअगर_rst))
		वापस PTR_ERR(phy->srअगर_rst);

	phy->phy = devm_phy_create(dev, शून्य, of_device_get_match_data(dev));
	अगर (IS_ERR(phy->phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(phy->phy);
	पूर्ण
	phy_set_drvdata(phy->phy, phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver ipq4019_usb_phy_driver = अणु
	.probe	= ipq4019_usb_phy_probe,
	.driver = अणु
		.of_match_table	= ipq4019_usb_phy_of_match,
		.name  = "ipq4019-usb-phy",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(ipq4019_usb_phy_driver);

MODULE_DESCRIPTION("QCOM/IPQ4019 USB phy driver");
MODULE_AUTHOR("John Crispin <john@phrozen.org>");
MODULE_LICENSE("GPL v2");
