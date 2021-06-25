<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * Copyright (C) 2016 Linaro Ltd
 */
#समावेश <linux/module.h>
#समावेश <linux/ulpi/driver.h>
#समावेश <linux/ulpi/regs.h>
#समावेश <linux/clk.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/reset.h>
#समावेश <linux/extcon.h>
#समावेश <linux/notअगरier.h>

#घोषणा ULPI_PWR_CLK_MNG_REG		0x88
# define ULPI_PWR_OTG_COMP_DISABLE	BIT(0)

#घोषणा ULPI_MISC_A			0x96
# define ULPI_MISC_A_VBUSVLDEXTSEL	BIT(1)
# define ULPI_MISC_A_VBUSVLDEXT		BIT(0)


काष्ठा ulpi_seq अणु
	u8 addr;
	u8 val;
पूर्ण;

काष्ठा qcom_usb_hs_phy अणु
	काष्ठा ulpi *ulpi;
	काष्ठा phy *phy;
	काष्ठा clk *ref_clk;
	काष्ठा clk *sleep_clk;
	काष्ठा regulator *v1p8;
	काष्ठा regulator *v3p3;
	काष्ठा reset_control *reset;
	काष्ठा ulpi_seq *init_seq;
	काष्ठा extcon_dev *vbus_edev;
	काष्ठा notअगरier_block vbus_notअगरy;
पूर्ण;

अटल पूर्णांक qcom_usb_hs_phy_set_mode(काष्ठा phy *phy,
				    क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा qcom_usb_hs_phy *uphy = phy_get_drvdata(phy);
	u8 addr;
	पूर्णांक ret;

	अगर (!uphy->vbus_edev) अणु
		u8 val = 0;

		चयन (mode) अणु
		हाल PHY_MODE_USB_OTG:
		हाल PHY_MODE_USB_HOST:
			val |= ULPI_INT_IDGRD;
			fallthrough;
		हाल PHY_MODE_USB_DEVICE:
			val |= ULPI_INT_SESS_VALID;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		ret = ulpi_ग_लिखो(uphy->ulpi, ULPI_USB_INT_EN_RISE, val);
		अगर (ret)
			वापस ret;
		ret = ulpi_ग_लिखो(uphy->ulpi, ULPI_USB_INT_EN_FALL, val);
	पूर्ण अन्यथा अणु
		चयन (mode) अणु
		हाल PHY_MODE_USB_OTG:
		हाल PHY_MODE_USB_DEVICE:
			addr = ULPI_SET(ULPI_MISC_A);
			अवरोध;
		हाल PHY_MODE_USB_HOST:
			addr = ULPI_CLR(ULPI_MISC_A);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = ulpi_ग_लिखो(uphy->ulpi, ULPI_SET(ULPI_PWR_CLK_MNG_REG),
				 ULPI_PWR_OTG_COMP_DISABLE);
		अगर (ret)
			वापस ret;
		ret = ulpi_ग_लिखो(uphy->ulpi, addr, ULPI_MISC_A_VBUSVLDEXTSEL);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
qcom_usb_hs_phy_vbus_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			      व्योम *ptr)
अणु
	काष्ठा qcom_usb_hs_phy *uphy;
	u8 addr;

	uphy = container_of(nb, काष्ठा qcom_usb_hs_phy, vbus_notअगरy);

	अगर (event)
		addr = ULPI_SET(ULPI_MISC_A);
	अन्यथा
		addr = ULPI_CLR(ULPI_MISC_A);

	वापस ulpi_ग_लिखो(uphy->ulpi, addr, ULPI_MISC_A_VBUSVLDEXT);
पूर्ण

अटल पूर्णांक qcom_usb_hs_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा qcom_usb_hs_phy *uphy = phy_get_drvdata(phy);
	काष्ठा ulpi *ulpi = uphy->ulpi;
	स्थिर काष्ठा ulpi_seq *seq;
	पूर्णांक ret, state;

	ret = clk_prepare_enable(uphy->ref_clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(uphy->sleep_clk);
	अगर (ret)
		जाओ err_sleep;

	ret = regulator_set_load(uphy->v1p8, 50000);
	अगर (ret < 0)
		जाओ err_1p8;

	ret = regulator_enable(uphy->v1p8);
	अगर (ret)
		जाओ err_1p8;

	ret = regulator_set_voltage_triplet(uphy->v3p3, 3050000, 3300000,
					    3300000);
	अगर (ret)
		जाओ err_3p3;

	ret = regulator_set_load(uphy->v3p3, 50000);
	अगर (ret < 0)
		जाओ err_3p3;

	ret = regulator_enable(uphy->v3p3);
	अगर (ret)
		जाओ err_3p3;

	क्रम (seq = uphy->init_seq; seq->addr; seq++) अणु
		ret = ulpi_ग_लिखो(ulpi, ULPI_EXT_VENDOR_SPECIFIC + seq->addr,
				 seq->val);
		अगर (ret)
			जाओ err_ulpi;
	पूर्ण

	अगर (uphy->reset) अणु
		ret = reset_control_reset(uphy->reset);
		अगर (ret)
			जाओ err_ulpi;
	पूर्ण

	अगर (uphy->vbus_edev) अणु
		state = extcon_get_state(uphy->vbus_edev, EXTCON_USB);
		/* setup initial state */
		qcom_usb_hs_phy_vbus_notअगरier(&uphy->vbus_notअगरy, state,
					      uphy->vbus_edev);
		ret = extcon_रेजिस्टर_notअगरier(uphy->vbus_edev, EXTCON_USB,
					       &uphy->vbus_notअगरy);
		अगर (ret)
			जाओ err_ulpi;
	पूर्ण

	वापस 0;
err_ulpi:
	regulator_disable(uphy->v3p3);
err_3p3:
	regulator_disable(uphy->v1p8);
err_1p8:
	clk_disable_unprepare(uphy->sleep_clk);
err_sleep:
	clk_disable_unprepare(uphy->ref_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_usb_hs_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा qcom_usb_hs_phy *uphy = phy_get_drvdata(phy);

	अगर (uphy->vbus_edev)
		extcon_unरेजिस्टर_notअगरier(uphy->vbus_edev, EXTCON_USB,
					   &uphy->vbus_notअगरy);
	regulator_disable(uphy->v3p3);
	regulator_disable(uphy->v1p8);
	clk_disable_unprepare(uphy->sleep_clk);
	clk_disable_unprepare(uphy->ref_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops qcom_usb_hs_phy_ops = अणु
	.घातer_on = qcom_usb_hs_phy_घातer_on,
	.घातer_off = qcom_usb_hs_phy_घातer_off,
	.set_mode = qcom_usb_hs_phy_set_mode,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक qcom_usb_hs_phy_probe(काष्ठा ulpi *ulpi)
अणु
	काष्ठा qcom_usb_hs_phy *uphy;
	काष्ठा phy_provider *p;
	काष्ठा clk *clk;
	काष्ठा regulator *reg;
	काष्ठा reset_control *reset;
	पूर्णांक size;
	पूर्णांक ret;

	uphy = devm_kzalloc(&ulpi->dev, माप(*uphy), GFP_KERNEL);
	अगर (!uphy)
		वापस -ENOMEM;
	ulpi_set_drvdata(ulpi, uphy);
	uphy->ulpi = ulpi;

	size = of_property_count_u8_elems(ulpi->dev.of_node, "qcom,init-seq");
	अगर (size < 0)
		size = 0;
	uphy->init_seq = devm_kदो_स्मृति_array(&ulpi->dev, (size / 2) + 1,
					   माप(*uphy->init_seq), GFP_KERNEL);
	अगर (!uphy->init_seq)
		वापस -ENOMEM;
	ret = of_property_पढ़ो_u8_array(ulpi->dev.of_node, "qcom,init-seq",
					(u8 *)uphy->init_seq, size);
	अगर (ret && size)
		वापस ret;
	/* NUL terminate */
	uphy->init_seq[size / 2].addr = uphy->init_seq[size / 2].val = 0;

	uphy->ref_clk = clk = devm_clk_get(&ulpi->dev, "ref");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	uphy->sleep_clk = clk = devm_clk_get(&ulpi->dev, "sleep");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	uphy->v1p8 = reg = devm_regulator_get(&ulpi->dev, "v1p8");
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	uphy->v3p3 = reg = devm_regulator_get(&ulpi->dev, "v3p3");
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	uphy->reset = reset = devm_reset_control_get(&ulpi->dev, "por");
	अगर (IS_ERR(reset)) अणु
		अगर (PTR_ERR(reset) == -EPROBE_DEFER)
			वापस PTR_ERR(reset);
		uphy->reset = शून्य;
	पूर्ण

	uphy->phy = devm_phy_create(&ulpi->dev, ulpi->dev.of_node,
				    &qcom_usb_hs_phy_ops);
	अगर (IS_ERR(uphy->phy))
		वापस PTR_ERR(uphy->phy);

	uphy->vbus_edev = extcon_get_edev_by_phandle(&ulpi->dev, 0);
	अगर (IS_ERR(uphy->vbus_edev)) अणु
		अगर (PTR_ERR(uphy->vbus_edev) != -ENODEV)
			वापस PTR_ERR(uphy->vbus_edev);
		uphy->vbus_edev = शून्य;
	पूर्ण

	uphy->vbus_notअगरy.notअगरier_call = qcom_usb_hs_phy_vbus_notअगरier;
	phy_set_drvdata(uphy->phy, uphy);

	p = devm_of_phy_provider_रेजिस्टर(&ulpi->dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(p);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_usb_hs_phy_match[] = अणु
	अणु .compatible = "qcom,usb-hs-phy", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_usb_hs_phy_match);

अटल काष्ठा ulpi_driver qcom_usb_hs_phy_driver = अणु
	.probe = qcom_usb_hs_phy_probe,
	.driver = अणु
		.name = "qcom_usb_hs_phy",
		.of_match_table = qcom_usb_hs_phy_match,
	पूर्ण,
पूर्ण;
module_ulpi_driver(qcom_usb_hs_phy_driver);

MODULE_DESCRIPTION("Qualcomm USB HS phy");
MODULE_LICENSE("GPL v2");
