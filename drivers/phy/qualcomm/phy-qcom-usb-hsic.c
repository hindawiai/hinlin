<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * Copyright (C) 2016 Linaro Ltd
 */
#समावेश <linux/module.h>
#समावेश <linux/ulpi/driver.h>
#समावेश <linux/ulpi/regs.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/pinctrl-state.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>

#घोषणा ULPI_HSIC_CFG		0x30
#घोषणा ULPI_HSIC_IO_CAL	0x33

काष्ठा qcom_usb_hsic_phy अणु
	काष्ठा ulpi *ulpi;
	काष्ठा phy *phy;
	काष्ठा pinctrl *pctl;
	काष्ठा clk *phy_clk;
	काष्ठा clk *cal_clk;
	काष्ठा clk *cal_sleep_clk;
पूर्ण;

अटल पूर्णांक qcom_usb_hsic_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा qcom_usb_hsic_phy *uphy = phy_get_drvdata(phy);
	काष्ठा ulpi *ulpi = uphy->ulpi;
	काष्ठा pinctrl_state *pins_शेष;
	पूर्णांक ret;

	ret = clk_prepare_enable(uphy->phy_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(uphy->cal_clk);
	अगर (ret)
		जाओ err_cal;

	ret = clk_prepare_enable(uphy->cal_sleep_clk);
	अगर (ret)
		जाओ err_sleep;

	/* Set periodic calibration पूर्णांकerval to ~2.048sec in HSIC_IO_CAL_REG */
	ret = ulpi_ग_लिखो(ulpi, ULPI_HSIC_IO_CAL, 0xff);
	अगर (ret)
		जाओ err_ulpi;

	/* Enable periodic IO calibration in HSIC_CFG रेजिस्टर */
	ret = ulpi_ग_लिखो(ulpi, ULPI_HSIC_CFG, 0xa8);
	अगर (ret)
		जाओ err_ulpi;

	/* Configure pins क्रम HSIC functionality */
	pins_शेष = pinctrl_lookup_state(uphy->pctl, PINCTRL_STATE_DEFAULT);
	अगर (IS_ERR(pins_शेष))
		वापस PTR_ERR(pins_शेष);

	ret = pinctrl_select_state(uphy->pctl, pins_शेष);
	अगर (ret)
		जाओ err_ulpi;

	 /* Enable HSIC mode in HSIC_CFG रेजिस्टर */
	ret = ulpi_ग_लिखो(ulpi, ULPI_SET(ULPI_HSIC_CFG), 0x01);
	अगर (ret)
		जाओ err_ulpi;

	/* Disable स्वतः-resume */
	ret = ulpi_ग_लिखो(ulpi, ULPI_CLR(ULPI_IFC_CTRL),
			 ULPI_IFC_CTRL_AUTORESUME);
	अगर (ret)
		जाओ err_ulpi;

	वापस ret;
err_ulpi:
	clk_disable_unprepare(uphy->cal_sleep_clk);
err_sleep:
	clk_disable_unprepare(uphy->cal_clk);
err_cal:
	clk_disable_unprepare(uphy->phy_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_usb_hsic_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा qcom_usb_hsic_phy *uphy = phy_get_drvdata(phy);

	clk_disable_unprepare(uphy->cal_sleep_clk);
	clk_disable_unprepare(uphy->cal_clk);
	clk_disable_unprepare(uphy->phy_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops qcom_usb_hsic_phy_ops = अणु
	.घातer_on = qcom_usb_hsic_phy_घातer_on,
	.घातer_off = qcom_usb_hsic_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक qcom_usb_hsic_phy_probe(काष्ठा ulpi *ulpi)
अणु
	काष्ठा qcom_usb_hsic_phy *uphy;
	काष्ठा phy_provider *p;
	काष्ठा clk *clk;

	uphy = devm_kzalloc(&ulpi->dev, माप(*uphy), GFP_KERNEL);
	अगर (!uphy)
		वापस -ENOMEM;
	ulpi_set_drvdata(ulpi, uphy);

	uphy->ulpi = ulpi;
	uphy->pctl = devm_pinctrl_get(&ulpi->dev);
	अगर (IS_ERR(uphy->pctl))
		वापस PTR_ERR(uphy->pctl);

	uphy->phy_clk = clk = devm_clk_get(&ulpi->dev, "phy");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	uphy->cal_clk = clk = devm_clk_get(&ulpi->dev, "cal");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	uphy->cal_sleep_clk = clk = devm_clk_get(&ulpi->dev, "cal_sleep");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	uphy->phy = devm_phy_create(&ulpi->dev, ulpi->dev.of_node,
				    &qcom_usb_hsic_phy_ops);
	अगर (IS_ERR(uphy->phy))
		वापस PTR_ERR(uphy->phy);
	phy_set_drvdata(uphy->phy, uphy);

	p = devm_of_phy_provider_रेजिस्टर(&ulpi->dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(p);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_usb_hsic_phy_match[] = अणु
	अणु .compatible = "qcom,usb-hsic-phy", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_usb_hsic_phy_match);

अटल काष्ठा ulpi_driver qcom_usb_hsic_phy_driver = अणु
	.probe = qcom_usb_hsic_phy_probe,
	.driver = अणु
		.name = "qcom_usb_hsic_phy",
		.of_match_table = qcom_usb_hsic_phy_match,
	पूर्ण,
पूर्ण;
module_ulpi_driver(qcom_usb_hsic_phy_driver);

MODULE_DESCRIPTION("Qualcomm USB HSIC phy");
MODULE_LICENSE("GPL v2");
