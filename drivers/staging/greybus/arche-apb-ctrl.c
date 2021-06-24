<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Arche Platक्रमm driver to control APB.
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spinlock.h>
#समावेश "arche_platform.h"

अटल व्योम apb_bootret_deनिश्चित(काष्ठा device *dev);

काष्ठा arche_apb_ctrl_drvdata अणु
	/* Control GPIO संकेतs to and from AP <=> AP Bridges */
	काष्ठा gpio_desc *resetn;
	काष्ठा gpio_desc *boot_ret;
	काष्ठा gpio_desc *pwroff;
	काष्ठा gpio_desc *wake_in;
	काष्ठा gpio_desc *wake_out;
	काष्ठा gpio_desc *pwrdn;

	क्रमागत arche_platक्रमm_state state;
	bool init_disabled;

	काष्ठा regulator *vcore;
	काष्ठा regulator *vio;

	काष्ठा gpio_desc *clk_en;
	काष्ठा clk *clk;

	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pin_शेष;

	/* V2: SPI Bus control  */
	काष्ठा gpio_desc *spi_en;
	bool spi_en_polarity_high;
पूर्ण;

/*
 * Note that these low level api's are active high
 */
अटल अंतरभूत व्योम deनिश्चित_reset(काष्ठा gpio_desc *gpio)
अणु
	gpiod_set_raw_value(gpio, 1);
पूर्ण

अटल अंतरभूत व्योम निश्चित_reset(काष्ठा gpio_desc *gpio)
अणु
	gpiod_set_raw_value(gpio, 0);
पूर्ण

/*
 * Note: Please करो not modअगरy the below sequence, as it is as per the spec
 */
अटल पूर्णांक coldboot_seq(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा arche_apb_ctrl_drvdata *apb = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (apb->init_disabled ||
	    apb->state == ARCHE_PLATFORM_STATE_ACTIVE)
		वापस 0;

	/* Hold APB in reset state */
	निश्चित_reset(apb->resetn);

	अगर (apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING && apb->spi_en)
		devm_gpiod_put(dev, apb->spi_en);

	/* Enable घातer to APB */
	अगर (!IS_ERR(apb->vcore)) अणु
		ret = regulator_enable(apb->vcore);
		अगर (ret) अणु
			dev_err(dev, "failed to enable core regulator\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(apb->vio)) अणु
		ret = regulator_enable(apb->vio);
		अगर (ret) अणु
			dev_err(dev, "failed to enable IO regulator\n");
			वापस ret;
		पूर्ण
	पूर्ण

	apb_bootret_deनिश्चित(dev);

	/* On DB3 घड़ी was not mandatory */
	अगर (apb->clk_en)
		gpiod_set_value(apb->clk_en, 1);

	usleep_range(100, 200);

	/* deनिश्चित reset to APB : Active-low संकेत */
	deनिश्चित_reset(apb->resetn);

	apb->state = ARCHE_PLATFORM_STATE_ACTIVE;

	वापस 0;
पूर्ण

अटल पूर्णांक fw_flashing_seq(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा arche_apb_ctrl_drvdata *apb = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (apb->init_disabled ||
	    apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING)
		वापस 0;

	ret = regulator_enable(apb->vcore);
	अगर (ret) अणु
		dev_err(dev, "failed to enable core regulator\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(apb->vio);
	अगर (ret) अणु
		dev_err(dev, "failed to enable IO regulator\n");
		वापस ret;
	पूर्ण

	अगर (apb->spi_en) अणु
		अचिन्हित दीर्घ flags;

		अगर (apb->spi_en_polarity_high)
			flags = GPIOD_OUT_HIGH;
		अन्यथा
			flags = GPIOD_OUT_LOW;

		apb->spi_en = devm_gpiod_get(dev, "spi-en", flags);
		अगर (IS_ERR(apb->spi_en)) अणु
			ret = PTR_ERR(apb->spi_en);
			dev_err(dev, "Failed requesting SPI bus en GPIO: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* क्रम flashing device should be in reset state */
	निश्चित_reset(apb->resetn);
	apb->state = ARCHE_PLATFORM_STATE_FW_FLASHING;

	वापस 0;
पूर्ण

अटल पूर्णांक standby_boot_seq(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा arche_apb_ctrl_drvdata *apb = platक्रमm_get_drvdata(pdev);

	अगर (apb->init_disabled)
		वापस 0;

	/*
	 * Even अगर it is in OFF state,
	 * then we करो not want to change the state
	 */
	अगर (apb->state == ARCHE_PLATFORM_STATE_STANDBY ||
	    apb->state == ARCHE_PLATFORM_STATE_OFF)
		वापस 0;

	अगर (apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING && apb->spi_en)
		devm_gpiod_put(dev, apb->spi_en);

	/*
	 * As per WDM spec, करो nothing
	 *
	 * Pasted from WDM spec,
	 *  - A falling edge on POWEROFF_L is detected (a)
	 *  - WDM enters standby mode, but no output संकेतs are changed
	 */

	/* TODO: POWEROFF_L is input to WDM module  */
	apb->state = ARCHE_PLATFORM_STATE_STANDBY;
	वापस 0;
पूर्ण

अटल व्योम घातeroff_seq(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा arche_apb_ctrl_drvdata *apb = platक्रमm_get_drvdata(pdev);

	अगर (apb->init_disabled || apb->state == ARCHE_PLATFORM_STATE_OFF)
		वापस;

	अगर (apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING && apb->spi_en)
		devm_gpiod_put(dev, apb->spi_en);

	/* disable the घड़ी */
	अगर (apb->clk_en)
		gpiod_set_value(apb->clk_en, 0);

	अगर (!IS_ERR(apb->vcore) && regulator_is_enabled(apb->vcore) > 0)
		regulator_disable(apb->vcore);

	अगर (!IS_ERR(apb->vio) && regulator_is_enabled(apb->vio) > 0)
		regulator_disable(apb->vio);

	/* As part of निकास, put APB back in reset state */
	निश्चित_reset(apb->resetn);
	apb->state = ARCHE_PLATFORM_STATE_OFF;

	/* TODO: May have to send an event to SVC about this निकास */
पूर्ण

अटल व्योम apb_bootret_deनिश्चित(काष्ठा device *dev)
अणु
	काष्ठा arche_apb_ctrl_drvdata *apb = dev_get_drvdata(dev);

	gpiod_set_value(apb->boot_ret, 0);
पूर्ण

पूर्णांक apb_ctrl_coldboot(काष्ठा device *dev)
अणु
	वापस coldboot_seq(to_platक्रमm_device(dev));
पूर्ण

पूर्णांक apb_ctrl_fw_flashing(काष्ठा device *dev)
अणु
	वापस fw_flashing_seq(to_platक्रमm_device(dev));
पूर्ण

पूर्णांक apb_ctrl_standby_boot(काष्ठा device *dev)
अणु
	वापस standby_boot_seq(to_platक्रमm_device(dev));
पूर्ण

व्योम apb_ctrl_घातeroff(काष्ठा device *dev)
अणु
	घातeroff_seq(to_platक्रमm_device(dev));
पूर्ण

अटल sमाप_प्रकार state_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा arche_apb_ctrl_drvdata *apb = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret = 0;
	bool is_disabled;

	अगर (sysfs_streq(buf, "off")) अणु
		अगर (apb->state == ARCHE_PLATFORM_STATE_OFF)
			वापस count;

		घातeroff_seq(pdev);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "active")) अणु
		अगर (apb->state == ARCHE_PLATFORM_STATE_ACTIVE)
			वापस count;

		घातeroff_seq(pdev);
		is_disabled = apb->init_disabled;
		apb->init_disabled = false;
		ret = coldboot_seq(pdev);
		अगर (ret)
			apb->init_disabled = is_disabled;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "standby")) अणु
		अगर (apb->state == ARCHE_PLATFORM_STATE_STANDBY)
			वापस count;

		ret = standby_boot_seq(pdev);
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "fw_flashing")) अणु
		अगर (apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING)
			वापस count;

		/*
		 * First we want to make sure we घातer off everything
		 * and then enter FW flashing state
		 */
		घातeroff_seq(pdev);
		ret = fw_flashing_seq(pdev);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown state\n");
		ret = -EINVAL;
	पूर्ण

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार state_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arche_apb_ctrl_drvdata *apb = dev_get_drvdata(dev);

	चयन (apb->state) अणु
	हाल ARCHE_PLATFORM_STATE_OFF:
		वापस प्र_लिखो(buf, "off%s\n",
				apb->init_disabled ? ",disabled" : "");
	हाल ARCHE_PLATFORM_STATE_ACTIVE:
		वापस प्र_लिखो(buf, "active\n");
	हाल ARCHE_PLATFORM_STATE_STANDBY:
		वापस प्र_लिखो(buf, "standby\n");
	हाल ARCHE_PLATFORM_STATE_FW_FLASHING:
		वापस प्र_लिखो(buf, "fw_flashing\n");
	शेष:
		वापस प्र_लिखो(buf, "unknown state\n");
	पूर्ण
पूर्ण

अटल DEVICE_ATTR_RW(state);

अटल पूर्णांक apb_ctrl_get_devtree_data(काष्ठा platक्रमm_device *pdev,
				     काष्ठा arche_apb_ctrl_drvdata *apb)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	apb->resetn = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(apb->resetn)) अणु
		ret = PTR_ERR(apb->resetn);
		dev_err(dev, "Failed requesting reset GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	apb->boot_ret = devm_gpiod_get(dev, "boot-ret", GPIOD_OUT_LOW);
	अगर (IS_ERR(apb->boot_ret)) अणु
		ret = PTR_ERR(apb->boot_ret);
		dev_err(dev, "Failed requesting bootret GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	/* It's not mandatory to support घातer management पूर्णांकerface */
	apb->pwroff = devm_gpiod_get_optional(dev, "pwr-off", GPIOD_IN);
	अगर (IS_ERR(apb->pwroff)) अणु
		ret = PTR_ERR(apb->pwroff);
		dev_err(dev, "Failed requesting pwroff_n GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Do not make घड़ी mandatory as of now (क्रम DB3) */
	apb->clk_en = devm_gpiod_get_optional(dev, "clock-en", GPIOD_OUT_LOW);
	अगर (IS_ERR(apb->clk_en)) अणु
		ret = PTR_ERR(apb->clk_en);
		dev_err(dev, "Failed requesting APB clock en GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	apb->pwrdn = devm_gpiod_get(dev, "pwr-down", GPIOD_OUT_LOW);
	अगर (IS_ERR(apb->pwrdn)) अणु
		ret = PTR_ERR(apb->pwrdn);
		dev_warn(dev, "Failed requesting power down GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Regulators are optional, as we may have fixed supply coming in */
	apb->vcore = devm_regulator_get(dev, "vcore");
	अगर (IS_ERR(apb->vcore))
		dev_warn(dev, "no core regulator found\n");

	apb->vio = devm_regulator_get(dev, "vio");
	अगर (IS_ERR(apb->vio))
		dev_warn(dev, "no IO regulator found\n");

	apb->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (IS_ERR(apb->pinctrl)) अणु
		dev_err(&pdev->dev, "could not get pinctrl handle\n");
		वापस PTR_ERR(apb->pinctrl);
	पूर्ण
	apb->pin_शेष = pinctrl_lookup_state(apb->pinctrl, "default");
	अगर (IS_ERR(apb->pin_शेष)) अणु
		dev_err(&pdev->dev, "could not get default pin state\n");
		वापस PTR_ERR(apb->pin_शेष);
	पूर्ण

	/* Only applicable क्रम platक्रमm >= V2 */
	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "gb,spi-en-active-high"))
		apb->spi_en_polarity_high = true;

	वापस 0;
पूर्ण

अटल पूर्णांक arche_apb_ctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा arche_apb_ctrl_drvdata *apb;
	काष्ठा device *dev = &pdev->dev;

	apb = devm_kzalloc(&pdev->dev, माप(*apb), GFP_KERNEL);
	अगर (!apb)
		वापस -ENOMEM;

	ret = apb_ctrl_get_devtree_data(pdev, apb);
	अगर (ret) अणु
		dev_err(dev, "failed to get apb devicetree data %d\n", ret);
		वापस ret;
	पूर्ण

	/* Initially set APB to OFF state */
	apb->state = ARCHE_PLATFORM_STATE_OFF;
	/* Check whether device needs to be enabled on boot */
	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "arche,init-disable"))
		apb->init_disabled = true;

	platक्रमm_set_drvdata(pdev, apb);

	/* Create sysfs पूर्णांकerface to allow user to change state dynamically */
	ret = device_create_file(dev, &dev_attr_state);
	अगर (ret) अणु
		dev_err(dev, "failed to create state file in sysfs\n");
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "Device registered successfully\n");
	वापस 0;
पूर्ण

अटल पूर्णांक arche_apb_ctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	device_हटाओ_file(&pdev->dev, &dev_attr_state);
	घातeroff_seq(pdev);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused arche_apb_ctrl_suspend(काष्ठा device *dev)
अणु
	/*
	 * If timing profile permits, we may shutकरोwn bridge
	 * completely
	 *
	 * TODO: sequence ??
	 *
	 * Also, need to make sure we meet precondition क्रम unipro suspend
	 * Precondition: Definition ???
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused arche_apb_ctrl_resume(काष्ठा device *dev)
अणु
	/*
	 * Atleast क्रम ES2 we have to meet the delay requirement between
	 * unipro चयन and AP bridge init, depending on whether bridge is in
	 * OFF state or standby state.
	 *
	 * Based on whether bridge is in standby or OFF state we may have to
	 * निश्चित multiple संकेतs. Please refer to WDM spec, क्रम more info.
	 *
	 */
	वापस 0;
पूर्ण

अटल व्योम arche_apb_ctrl_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	apb_ctrl_घातeroff(&pdev->dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(arche_apb_ctrl_pm_ops, arche_apb_ctrl_suspend,
			 arche_apb_ctrl_resume);

अटल स्थिर काष्ठा of_device_id arche_apb_ctrl_of_match[] = अणु
	अणु .compatible = "usbffff,2", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver arche_apb_ctrl_device_driver = अणु
	.probe		= arche_apb_ctrl_probe,
	.हटाओ		= arche_apb_ctrl_हटाओ,
	.shutकरोwn	= arche_apb_ctrl_shutकरोwn,
	.driver		= अणु
		.name	= "arche-apb-ctrl",
		.pm	= &arche_apb_ctrl_pm_ops,
		.of_match_table = arche_apb_ctrl_of_match,
	पूर्ण
पूर्ण;

पूर्णांक __init arche_apb_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&arche_apb_ctrl_device_driver);
पूर्ण

व्योम __निकास arche_apb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&arche_apb_ctrl_device_driver);
पूर्ण
