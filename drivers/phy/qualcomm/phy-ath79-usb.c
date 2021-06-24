<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Atheros AR71XX/9XXX USB PHY driver
 *
 * Copyright (C) 2015-2018 Alban Bedel <albeu@मुक्त.fr>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/reset.h>

काष्ठा ath79_usb_phy अणु
	काष्ठा reset_control *reset;
	/* The suspend override logic is inverted, hence the no prefix
	 * to make the code a bit easier to understand.
	 */
	काष्ठा reset_control *no_suspend_override;
पूर्ण;

अटल पूर्णांक ath79_usb_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा ath79_usb_phy *priv = phy_get_drvdata(phy);
	पूर्णांक err = 0;

	अगर (priv->no_suspend_override) अणु
		err = reset_control_निश्चित(priv->no_suspend_override);
		अगर (err)
			वापस err;
	पूर्ण

	err = reset_control_deनिश्चित(priv->reset);
	अगर (err && priv->no_suspend_override)
		reset_control_deनिश्चित(priv->no_suspend_override);

	वापस err;
पूर्ण

अटल पूर्णांक ath79_usb_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा ath79_usb_phy *priv = phy_get_drvdata(phy);
	पूर्णांक err = 0;

	err = reset_control_निश्चित(priv->reset);
	अगर (err)
		वापस err;

	अगर (priv->no_suspend_override) अणु
		err = reset_control_deनिश्चित(priv->no_suspend_override);
		अगर (err)
			reset_control_deनिश्चित(priv->reset);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा phy_ops ath79_usb_phy_ops = अणु
	.घातer_on	= ath79_usb_phy_घातer_on,
	.घातer_off	= ath79_usb_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक ath79_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath79_usb_phy *priv;
	काष्ठा phy *phy;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->reset = devm_reset_control_get(&pdev->dev, "phy");
	अगर (IS_ERR(priv->reset))
		वापस PTR_ERR(priv->reset);

	priv->no_suspend_override = devm_reset_control_get_optional(
		&pdev->dev, "usb-suspend-override");
	अगर (IS_ERR(priv->no_suspend_override))
		वापस PTR_ERR(priv->no_suspend_override);

	phy = devm_phy_create(&pdev->dev, शून्य, &ath79_usb_phy_ops);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	phy_set_drvdata(phy, priv);

	वापस PTR_ERR_OR_ZERO(devm_of_phy_provider_रेजिस्टर(
				&pdev->dev, of_phy_simple_xlate));
पूर्ण

अटल स्थिर काष्ठा of_device_id ath79_usb_phy_of_match[] = अणु
	अणु .compatible = "qca,ar7100-usb-phy" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ath79_usb_phy_of_match);

अटल काष्ठा platक्रमm_driver ath79_usb_phy_driver = अणु
	.probe	= ath79_usb_phy_probe,
	.driver = अणु
		.of_match_table	= ath79_usb_phy_of_match,
		.name		= "ath79-usb-phy",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(ath79_usb_phy_driver);

MODULE_DESCRIPTION("ATH79 USB PHY driver");
MODULE_AUTHOR("Alban Bedel <albeu@free.fr>");
MODULE_LICENSE("GPL");
