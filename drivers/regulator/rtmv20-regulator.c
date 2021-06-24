<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>

#घोषणा RTMV20_REG_DEVINFO	0x00
#घोषणा RTMV20_REG_PULSEDELAY	0x01
#घोषणा RTMV20_REG_PULSEWIDTH	0x03
#घोषणा RTMV20_REG_LDCTRL1	0x05
#घोषणा RTMV20_REG_ESPULSEWIDTH	0x06
#घोषणा RTMV20_REG_ESLDCTRL1	0x08
#घोषणा RTMV20_REG_LBP		0x0A
#घोषणा RTMV20_REG_LDCTRL2	0x0B
#घोषणा RTMV20_REG_FSIN1CTRL1	0x0D
#घोषणा RTMV20_REG_FSIN1CTRL3	0x0F
#घोषणा RTMV20_REG_FSIN2CTRL1	0x10
#घोषणा RTMV20_REG_FSIN2CTRL3	0x12
#घोषणा RTMV20_REG_ENCTRL	0x13
#घोषणा RTMV20_REG_STRBVSYNDLYL 0x29
#घोषणा RTMV20_REG_LसूचीQ	0x30
#घोषणा RTMV20_REG_LDSTAT	0x40
#घोषणा RTMV20_REG_LDMASK	0x50
#घोषणा RTMV20_MAX_REGS		(RTMV20_REG_LDMASK + 1)

#घोषणा RTMV20_VID_MASK		GENMASK(7, 4)
#घोषणा RICHTEK_VID		0x80
#घोषणा RTMV20_LDCURR_MASK	GENMASK(7, 0)
#घोषणा RTMV20_DELAY_MASK	GENMASK(9, 0)
#घोषणा RTMV20_WIDTH_MASK	GENMASK(13, 0)
#घोषणा RTMV20_WIDTH2_MASK	GENMASK(7, 0)
#घोषणा RTMV20_LBPLVL_MASK	GENMASK(3, 0)
#घोषणा RTMV20_LBPEN_MASK	BIT(7)
#घोषणा RTMV20_STROBEPOL_MASK	BIT(1)
#घोषणा RTMV20_VSYNPOL_MASK	BIT(1)
#घोषणा RTMV20_FSINEN_MASK	BIT(7)
#घोषणा RTMV20_ESEN_MASK	BIT(6)
#घोषणा RTMV20_FSINOUT_MASK	BIT(2)
#घोषणा LDENABLE_MASK		(BIT(3) | BIT(0))

#घोषणा OTPEVT_MASK		BIT(4)
#घोषणा SHORTEVT_MASK		BIT(3)
#घोषणा OPENEVT_MASK		BIT(2)
#घोषणा LBPEVT_MASK		BIT(1)
#घोषणा OCPEVT_MASK		BIT(0)
#घोषणा FAILEVT_MASK		(SHORTEVT_MASK | OPENEVT_MASK | LBPEVT_MASK)

#घोषणा RTMV20_LSW_MINUA	0
#घोषणा RTMV20_LSW_MAXUA	6000000
#घोषणा RTMV20_LSW_STEPUA	30000

#घोषणा RTMV20_LSW_DEFAULTUA	3000000

#घोषणा RTMV20_I2CRDY_TIMEUS	200
#घोषणा RTMV20_CSRDY_TIMEUS	2000

काष्ठा rपंचांगv20_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regulator_dev *rdev;
पूर्ण;

अटल पूर्णांक rपंचांगv20_lsw_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rपंचांगv20_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	gpiod_set_value(priv->enable_gpio, 1);

	/* Wait क्रम I2C can be accessed */
	usleep_range(RTMV20_I2CRDY_TIMEUS, RTMV20_I2CRDY_TIMEUS + 100);

	/* HW re-enable, disable cache only and sync regcache here */
	regcache_cache_only(priv->regmap, false);
	ret = regcache_sync(priv->regmap);
	अगर (ret)
		वापस ret;

	वापस regulator_enable_regmap(rdev);
पूर्ण

अटल पूर्णांक rपंचांगv20_lsw_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rपंचांगv20_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	ret = regulator_disable_regmap(rdev);
	अगर (ret)
		वापस ret;

	/* Mark the regcache as dirty and cache only beक्रमe HW disabled */
	regcache_cache_only(priv->regmap, true);
	regcache_mark_dirty(priv->regmap);

	gpiod_set_value(priv->enable_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rपंचांगv20_lsw_set_current_limit(काष्ठा regulator_dev *rdev, पूर्णांक min_uA,
					पूर्णांक max_uA)
अणु
	पूर्णांक sel;

	अगर (min_uA > RTMV20_LSW_MAXUA || max_uA < RTMV20_LSW_MINUA)
		वापस -EINVAL;

	अगर (max_uA > RTMV20_LSW_MAXUA)
		max_uA = RTMV20_LSW_MAXUA;

	sel = (max_uA - RTMV20_LSW_MINUA) / RTMV20_LSW_STEPUA;

	/* Ensure the selected setting is still in range */
	अगर ((sel * RTMV20_LSW_STEPUA + RTMV20_LSW_MINUA) < min_uA)
		वापस -EINVAL;

	sel <<= ffs(rdev->desc->csel_mask) - 1;

	वापस regmap_update_bits(rdev->regmap, rdev->desc->csel_reg,
				  rdev->desc->csel_mask, sel);
पूर्ण

अटल पूर्णांक rपंचांगv20_lsw_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->csel_reg, &val);
	अगर (ret)
		वापस ret;

	val &= rdev->desc->csel_mask;
	val >>= ffs(rdev->desc->csel_mask) - 1;

	वापस val * RTMV20_LSW_STEPUA + RTMV20_LSW_MINUA;
पूर्ण

अटल स्थिर काष्ठा regulator_ops rपंचांगv20_regulator_ops = अणु
	.set_current_limit = rपंचांगv20_lsw_set_current_limit,
	.get_current_limit = rपंचांगv20_lsw_get_current_limit,
	.enable = rपंचांगv20_lsw_enable,
	.disable = rपंचांगv20_lsw_disable,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc rपंचांगv20_lsw_desc = अणु
	.name = "rtmv20,lsw",
	.of_match = of_match_ptr("lsw"),
	.type = REGULATOR_CURRENT,
	.owner = THIS_MODULE,
	.ops = &rपंचांगv20_regulator_ops,
	.csel_reg = RTMV20_REG_LDCTRL1,
	.csel_mask = RTMV20_LDCURR_MASK,
	.enable_reg = RTMV20_REG_ENCTRL,
	.enable_mask = LDENABLE_MASK,
	.enable_समय = RTMV20_CSRDY_TIMEUS,
पूर्ण;

अटल irqवापस_t rपंचांगv20_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rपंचांगv20_priv *priv = data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->regmap, RTMV20_REG_LसूचीQ, &val);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to get irq flags\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर (val & OTPEVT_MASK)
		regulator_notअगरier_call_chain(priv->rdev, REGULATOR_EVENT_OVER_TEMP, शून्य);

	अगर (val & OCPEVT_MASK)
		regulator_notअगरier_call_chain(priv->rdev, REGULATOR_EVENT_OVER_CURRENT, शून्य);

	अगर (val & FAILEVT_MASK)
		regulator_notअगरier_call_chain(priv->rdev, REGULATOR_EVENT_FAIL, शून्य);

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 clamp_to_selector(u32 val, u32 min, u32 max, u32 step)
अणु
	u32 retval = clamp_val(val, min, max);

	वापस (retval - min) / step;
पूर्ण

अटल पूर्णांक rपंचांगv20_properties_init(काष्ठा rपंचांगv20_priv *priv)
अणु
	स्थिर काष्ठा अणु
		स्थिर अक्षर *name;
		u32 def;
		u32 min;
		u32 max;
		u32 step;
		u32 addr;
		u32 mask;
	पूर्ण props[] = अणु
		अणु "richtek,ld-pulse-delay-us", 0, 0, 100000, 100, RTMV20_REG_PULSEDELAY,
			RTMV20_DELAY_MASK पूर्ण,
		अणु "richtek,ld-pulse-width-us", 1200, 0, 10000, 1, RTMV20_REG_PULSEWIDTH,
			RTMV20_WIDTH_MASK पूर्ण,
		अणु "richtek,fsin1-delay-us", 23000, 0, 100000, 100, RTMV20_REG_FSIN1CTRL1,
			RTMV20_DELAY_MASK पूर्ण,
		अणु "richtek,fsin1-width-us", 160, 40, 10000, 40, RTMV20_REG_FSIN1CTRL3,
			RTMV20_WIDTH2_MASK पूर्ण,
		अणु "richtek,fsin2-delay-us", 23000, 0, 100000, 100, RTMV20_REG_FSIN2CTRL1,
			RTMV20_DELAY_MASK पूर्ण,
		अणु "richtek,fsin2-width-us", 160, 40, 10000, 40, RTMV20_REG_FSIN2CTRL3,
			RTMV20_WIDTH2_MASK पूर्ण,
		अणु "richtek,es-pulse-width-us", 1200, 0, 10000, 1, RTMV20_REG_ESPULSEWIDTH,
			RTMV20_WIDTH_MASK पूर्ण,
		अणु "richtek,es-ld-current-microamp", 3000000, 0, 6000000, 30000,
			RTMV20_REG_ESLDCTRL1, RTMV20_LDCURR_MASK पूर्ण,
		अणु "richtek,lbp-level-microvolt", 2700000, 2400000, 3700000, 100000, RTMV20_REG_LBP,
			RTMV20_LBPLVL_MASK पूर्ण,
		अणु "richtek,lbp-enable", 0, 0, 1, 1, RTMV20_REG_LBP, RTMV20_LBPEN_MASK पूर्ण,
		अणु "richtek,strobe-polarity-high", 1, 0, 1, 1, RTMV20_REG_LDCTRL2,
			RTMV20_STROBEPOL_MASK पूर्ण,
		अणु "richtek,vsync-polarity-high", 1, 0, 1, 1, RTMV20_REG_LDCTRL2,
			RTMV20_VSYNPOL_MASK पूर्ण,
		अणु "richtek,fsin-enable", 0, 0, 1, 1, RTMV20_REG_ENCTRL, RTMV20_FSINEN_MASK पूर्ण,
		अणु "richtek,fsin-output", 0, 0, 1, 1, RTMV20_REG_ENCTRL, RTMV20_FSINOUT_MASK पूर्ण,
		अणु "richtek,es-enable", 0, 0, 1, 1, RTMV20_REG_ENCTRL, RTMV20_ESEN_MASK पूर्ण,
	पूर्ण;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(props); i++) अणु
		__be16 bval16;
		u16 val16;
		u32 temp;
		पूर्णांक signअगरicant_bit = fls(props[i].mask);
		पूर्णांक shअगरt = ffs(props[i].mask) - 1;

		अगर (props[i].max > 1) अणु
			ret = device_property_पढ़ो_u32(priv->dev, props[i].name, &temp);
			अगर (ret)
				temp = props[i].def;
		पूर्ण अन्यथा
			temp = device_property_पढ़ो_bool(priv->dev, props[i].name);

		temp = clamp_to_selector(temp, props[i].min, props[i].max, props[i].step);

		/* If signअगरicant bit is over 8, two byte access, others one */
		अगर (signअगरicant_bit > 8) अणु
			ret = regmap_raw_पढ़ो(priv->regmap, props[i].addr, &bval16, माप(bval16));
			अगर (ret)
				वापस ret;

			val16 = be16_to_cpu(bval16);
			val16 &= ~props[i].mask;
			val16 |= (temp << shअगरt);
			bval16 = cpu_to_be16(val16);

			ret = regmap_raw_ग_लिखो(priv->regmap, props[i].addr, &bval16,
					       माप(bval16));
		पूर्ण अन्यथा अणु
			ret = regmap_update_bits(priv->regmap, props[i].addr, props[i].mask,
						 temp << shअगरt);
		पूर्ण

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rपंचांगv20_check_chip_exist(काष्ठा rपंचांगv20_priv *priv)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->regmap, RTMV20_REG_DEVINFO, &val);
	अगर (ret)
		वापस ret;

	अगर ((val & RTMV20_VID_MASK) != RICHTEK_VID)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल bool rपंचांगv20_is_accessible_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RTMV20_REG_DEVINFO ... RTMV20_REG_STRBVSYNDLYL:
	हाल RTMV20_REG_LसूचीQ:
	हाल RTMV20_REG_LDSTAT:
	हाल RTMV20_REG_LDMASK:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool rपंचांगv20_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg == RTMV20_REG_LसूचीQ || reg == RTMV20_REG_LDSTAT)
		वापस true;
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config rपंचांगv20_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = RTMV20_REG_LDMASK,
	.num_reg_शेषs_raw = RTMV20_MAX_REGS,

	.ग_लिखोable_reg = rपंचांगv20_is_accessible_reg,
	.पढ़ोable_reg = rपंचांगv20_is_accessible_reg,
	.अस्थिर_reg = rपंचांगv20_is_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक rपंचांगv20_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rपंचांगv20_priv *priv;
	काष्ठा regulator_config config = अणुपूर्ण;
	पूर्णांक ret;

	priv = devm_kzalloc(&i2c->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &i2c->dev;

	/* Beक्रमe regmap रेजिस्टर, configure HW enable to make I2C accessible */
	priv->enable_gpio = devm_gpiod_get(&i2c->dev, "enable", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->enable_gpio)) अणु
		dev_err(&i2c->dev, "Failed to get enable gpio\n");
		वापस PTR_ERR(priv->enable_gpio);
	पूर्ण

	/* Wait क्रम I2C can be accessed */
	usleep_range(RTMV20_I2CRDY_TIMEUS, RTMV20_I2CRDY_TIMEUS + 100);

	priv->regmap = devm_regmap_init_i2c(i2c, &rपंचांगv20_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(&i2c->dev, "Failed to allocate register map\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	ret = rपंचांगv20_check_chip_exist(priv);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Chip vendor info is not matched\n");
		वापस ret;
	पूर्ण

	ret = rपंचांगv20_properties_init(priv);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to init properties\n");
		वापस ret;
	पूर्ण

	/*
	 * keep in shutकरोwn mode to minimize the current consumption
	 * and also mark regcache as dirty
	 */
	regcache_cache_only(priv->regmap, true);
	regcache_mark_dirty(priv->regmap);
	gpiod_set_value(priv->enable_gpio, 0);

	config.dev = &i2c->dev;
	config.regmap = priv->regmap;
	config.driver_data = priv;
	priv->rdev = devm_regulator_रेजिस्टर(&i2c->dev, &rपंचांगv20_lsw_desc, &config);
	अगर (IS_ERR(priv->rdev)) अणु
		dev_err(&i2c->dev, "Failed to register regulator\n");
		वापस PTR_ERR(priv->rdev);
	पूर्ण

	/* Unmask all events beक्रमe IRQ रेजिस्टरed */
	ret = regmap_ग_लिखो(priv->regmap, RTMV20_REG_LDMASK, 0);
	अगर (ret)
		वापस ret;

	वापस devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य, rपंचांगv20_irq_handler,
					 IRQF_ONESHOT, dev_name(&i2c->dev), priv);
पूर्ण

अटल पूर्णांक __maybe_unused rपंचांगv20_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	/*
	 * When प्रणाली suspend, disable irq to prevent पूर्णांकerrupt trigger
	 * during I2C bus suspend
	 */
	disable_irq(i2c->irq);
	अगर (device_may_wakeup(dev))
		enable_irq_wake(i2c->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rपंचांगv20_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	/* Enable irq after I2C bus alपढ़ोy resume */
	enable_irq(i2c->irq);
	अगर (device_may_wakeup(dev))
		disable_irq_wake(i2c->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rपंचांगv20_pm, rपंचांगv20_suspend, rपंचांगv20_resume);

अटल स्थिर काष्ठा of_device_id __maybe_unused rपंचांगv20_of_id[] = अणु
	अणु .compatible = "richtek,rtmv20", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rपंचांगv20_of_id);

अटल काष्ठा i2c_driver rपंचांगv20_driver = अणु
	.driver = अणु
		.name = "rtmv20",
		.of_match_table = of_match_ptr(rपंचांगv20_of_id),
		.pm = &rपंचांगv20_pm,
	पूर्ण,
	.probe_new = rपंचांगv20_probe,
पूर्ण;
module_i2c_driver(rपंचांगv20_driver);

MODULE_AUTHOR("ChiYuan Huang <cy_huang@richtek.com>");
MODULE_DESCRIPTION("Richtek RTMV20 Regulator Driver");
MODULE_LICENSE("GPL v2");
