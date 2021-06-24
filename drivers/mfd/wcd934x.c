<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019, Linaro Limited

#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/wcd934x/रेजिस्टरs.h>
#समावेश <linux/mfd/wcd934x/wcd934x.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slimbus.h>

अटल स्थिर काष्ठा mfd_cell wcd934x_devices[] = अणु
	अणु
		.name = "wcd934x-codec",
	पूर्ण, अणु
		.name = "wcd934x-gpio",
		.of_compatible = "qcom,wcd9340-gpio",
	पूर्ण, अणु
		.name = "wcd934x-soundwire",
		.of_compatible = "qcom,soundwire-v1.3.0",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq wcd934x_irqs[] = अणु
	[WCD934X_IRQ_SLIMBUS] = अणु
		.reg_offset = 0,
		.mask = BIT(0),
		.type = अणु
			.type_reg_offset = 0,
			.types_supported = IRQ_TYPE_EDGE_BOTH,
			.type_reg_mask  = BIT(0),
			.type_level_low_val = BIT(0),
			.type_level_high_val = BIT(0),
			.type_falling_val = 0,
			.type_rising_val = 0,
		पूर्ण,
	पूर्ण,
	[WCD934X_IRQ_SOUNDWIRE] = अणु
		.reg_offset = 2,
		.mask = BIT(4),
		.type = अणु
			.type_reg_offset = 2,
			.types_supported = IRQ_TYPE_EDGE_BOTH,
			.type_reg_mask  = BIT(4),
			.type_level_low_val = BIT(4),
			.type_level_high_val = BIT(4),
			.type_falling_val = 0,
			.type_rising_val = 0,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip wcd934x_regmap_irq_chip = अणु
	.name = "wcd934x_irq",
	.status_base = WCD934X_INTR_PIN1_STATUS0,
	.mask_base = WCD934X_INTR_PIN1_MASK0,
	.ack_base = WCD934X_INTR_PIN1_CLEAR0,
	.type_base = WCD934X_INTR_LEVEL0,
	.num_type_reg = 4,
	.type_in_mask = false,
	.num_regs = 4,
	.irqs = wcd934x_irqs,
	.num_irqs = ARRAY_SIZE(wcd934x_irqs),
पूर्ण;

अटल bool wcd934x_is_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WCD934X_INTR_PIN1_STATUS0...WCD934X_INTR_PIN2_CLEAR3:
	हाल WCD934X_SWR_AHB_BRIDGE_RD_DATA_0:
	हाल WCD934X_SWR_AHB_BRIDGE_RD_DATA_1:
	हाल WCD934X_SWR_AHB_BRIDGE_RD_DATA_2:
	हाल WCD934X_SWR_AHB_BRIDGE_RD_DATA_3:
	हाल WCD934X_SWR_AHB_BRIDGE_ACCESS_STATUS:
	हाल WCD934X_ANA_MBHC_RESULT_3:
	हाल WCD934X_ANA_MBHC_RESULT_2:
	हाल WCD934X_ANA_MBHC_RESULT_1:
	हाल WCD934X_ANA_MBHC_MECH:
	हाल WCD934X_ANA_MBHC_ELECT:
	हाल WCD934X_ANA_MBHC_ZDET:
	हाल WCD934X_ANA_MICB2:
	हाल WCD934X_ANA_RCO:
	हाल WCD934X_ANA_BIAS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg wcd934x_ranges[] = अणु
	अणु	.name = "WCD934X",
		.range_min =  0x0,
		.range_max =  WCD934X_MAX_REGISTER,
		.selector_reg = WCD934X_SEL_REGISTER,
		.selector_mask = WCD934X_SEL_MASK,
		.selector_shअगरt = WCD934X_SEL_SHIFT,
		.winकरोw_start = WCD934X_WINDOW_START,
		.winकरोw_len = WCD934X_WINDOW_LENGTH,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_config wcd934x_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = 0xffff,
	.can_multi_ग_लिखो = true,
	.ranges = wcd934x_ranges,
	.num_ranges = ARRAY_SIZE(wcd934x_ranges),
	.अस्थिर_reg = wcd934x_is_अस्थिर_रेजिस्टर,
पूर्ण;

अटल पूर्णांक wcd934x_bring_up(काष्ठा wcd934x_ddata *ddata)
अणु
	काष्ठा regmap *regmap = ddata->regmap;
	u16 id_minor, id_major;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(regmap, WCD934X_CHIP_TIER_CTRL_CHIP_ID_BYTE0,
			       (u8 *)&id_minor, माप(u16));
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_पढ़ो(regmap, WCD934X_CHIP_TIER_CTRL_CHIP_ID_BYTE2,
			       (u8 *)&id_major, माप(u16));
	अगर (ret)
		वापस ret;

	dev_info(ddata->dev, "WCD934x chip id major 0x%x, minor 0x%x\n",
		 id_major, id_minor);

	regmap_ग_लिखो(regmap, WCD934X_CODEC_RPM_RST_CTL, 0x01);
	regmap_ग_लिखो(regmap, WCD934X_SIDO_NEW_VOUT_A_STARTUP, 0x19);
	regmap_ग_लिखो(regmap, WCD934X_SIDO_NEW_VOUT_D_STARTUP, 0x15);
	/* Add 1msec delay क्रम VOUT to settle */
	usleep_range(1000, 1100);
	regmap_ग_लिखो(regmap, WCD934X_CODEC_RPM_PWR_CDC_DIG_HM_CTL, 0x5);
	regmap_ग_लिखो(regmap, WCD934X_CODEC_RPM_PWR_CDC_DIG_HM_CTL, 0x7);
	regmap_ग_लिखो(regmap, WCD934X_CODEC_RPM_RST_CTL, 0x3);
	regmap_ग_लिखो(regmap, WCD934X_CODEC_RPM_RST_CTL, 0x7);
	regmap_ग_लिखो(regmap, WCD934X_CODEC_RPM_PWR_CDC_DIG_HM_CTL, 0x3);

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_slim_status_up(काष्ठा slim_device *sdev)
अणु
	काष्ठा device *dev = &sdev->dev;
	काष्ठा wcd934x_ddata *ddata;
	पूर्णांक ret;

	ddata = dev_get_drvdata(dev);

	ddata->regmap = regmap_init_slimbus(sdev, &wcd934x_regmap_config);
	अगर (IS_ERR(ddata->regmap)) अणु
		dev_err(dev, "Error allocating slim regmap\n");
		वापस PTR_ERR(ddata->regmap);
	पूर्ण

	ret = wcd934x_bring_up(ddata);
	अगर (ret) अणु
		dev_err(dev, "Failed to bring up WCD934X: err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_regmap_add_irq_chip(dev, ddata->regmap, ddata->irq,
				       IRQF_TRIGGER_HIGH, 0,
				       &wcd934x_regmap_irq_chip,
				       &ddata->irq_data);
	अगर (ret) अणु
		dev_err(dev, "Failed to add IRQ chip: err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mfd_add_devices(dev, PLATFORM_DEVID_AUTO, wcd934x_devices,
			      ARRAY_SIZE(wcd934x_devices), शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(dev, "Failed to add child devices: err = %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wcd934x_slim_status(काष्ठा slim_device *sdev,
			       क्रमागत slim_device_status status)
अणु
	चयन (status) अणु
	हाल SLIM_DEVICE_STATUS_UP:
		वापस wcd934x_slim_status_up(sdev);
	हाल SLIM_DEVICE_STATUS_DOWN:
		mfd_हटाओ_devices(&sdev->dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcd934x_slim_probe(काष्ठा slim_device *sdev)
अणु
	काष्ठा device *dev = &sdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा wcd934x_ddata *ddata;
	पूर्णांक reset_gpio, ret;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस	-ENOMEM;

	ddata->irq = of_irq_get(np, 0);
	अगर (ddata->irq < 0)
		वापस dev_err_probe(ddata->dev, ddata->irq,
				     "Failed to get IRQ\n");

	reset_gpio = of_get_named_gpio(np, "reset-gpios", 0);
	अगर (reset_gpio < 0) अणु
		dev_err(dev, "Failed to get reset gpio: err = %d\n",
			reset_gpio);
		वापस reset_gpio;
	पूर्ण

	ddata->extclk = devm_clk_get(dev, "extclk");
	अगर (IS_ERR(ddata->extclk)) अणु
		dev_err(dev, "Failed to get extclk");
		वापस PTR_ERR(ddata->extclk);
	पूर्ण

	ddata->supplies[0].supply = "vdd-buck";
	ddata->supplies[1].supply = "vdd-buck-sido";
	ddata->supplies[2].supply = "vdd-tx";
	ddata->supplies[3].supply = "vdd-rx";
	ddata->supplies[4].supply = "vdd-io";

	ret = regulator_bulk_get(dev, WCD934X_MAX_SUPPLY, ddata->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to get supplies: err = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(WCD934X_MAX_SUPPLY, ddata->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable supplies: err = %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * For WCD934X, it takes about 600us क्रम the Vout_A and
	 * Vout_D to be पढ़ोy after BUCK_SIDO is घातered up.
	 * SYS_RST_N shouldn't be pulled high during this समय
	 */
	usleep_range(600, 650);
	gpio_direction_output(reset_gpio, 0);
	msleep(20);
	gpio_set_value(reset_gpio, 1);
	msleep(20);

	ddata->dev = dev;
	dev_set_drvdata(dev, ddata);

	वापस 0;
पूर्ण

अटल व्योम wcd934x_slim_हटाओ(काष्ठा slim_device *sdev)
अणु
	काष्ठा wcd934x_ddata *ddata = dev_get_drvdata(&sdev->dev);

	regulator_bulk_disable(WCD934X_MAX_SUPPLY, ddata->supplies);
	mfd_हटाओ_devices(&sdev->dev);
पूर्ण

अटल स्थिर काष्ठा slim_device_id wcd934x_slim_id[] = अणु
	अणु SLIM_MANF_ID_QCOM, SLIM_PROD_CODE_WCD9340,
	  SLIM_DEV_IDX_WCD9340, SLIM_DEV_INSTANCE_ID_WCD9340 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा slim_driver wcd934x_slim_driver = अणु
	.driver = अणु
		.name = "wcd934x-slim",
	पूर्ण,
	.probe = wcd934x_slim_probe,
	.हटाओ = wcd934x_slim_हटाओ,
	.device_status = wcd934x_slim_status,
	.id_table = wcd934x_slim_id,
पूर्ण;

module_slim_driver(wcd934x_slim_driver);
MODULE_DESCRIPTION("WCD934X slim driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("slim:217:250:*");
MODULE_AUTHOR("Srinivas Kandagatla <srinivas.kandagatla@linaro.org>");
