<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>

#घोषणा RT4801_REG_VOP	0x00
#घोषणा RT4801_REG_VON	0x01
#घोषणा RT4801_REG_APPS	0x03

#घोषणा VOUT_MASK	0x1F

#घोषणा MIN_UV		4000000
#घोषणा STEP_UV		100000
#घोषणा MAX_UV		6000000
#घोषणा N_VOLTAGES	((MAX_UV - MIN_UV) / STEP_UV + 1)

#घोषणा DSV_OUT_POS	0
#घोषणा DSV_OUT_NEG	1
#घोषणा DSV_OUT_MAX	2

#घोषणा DSVP_ENABLE	BIT(0)
#घोषणा DSVN_ENABLE	BIT(1)
#घोषणा DSVALL_ENABLE	(DSVP_ENABLE | DSVN_ENABLE)

काष्ठा rt4801_priv अणु
	काष्ठा device *dev;
	काष्ठा gpio_descs *enable_gpios;
	अचिन्हित पूर्णांक enable_flag;
	अचिन्हित पूर्णांक volt_sel[DSV_OUT_MAX];
पूर्ण;

अटल पूर्णांक rt4801_set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक selector)
अणु
	काष्ठा rt4801_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev), ret;

	अगर (priv->enable_flag & BIT(id)) अणु
		ret = regulator_set_voltage_sel_regmap(rdev, selector);
		अगर (ret)
			वापस ret;
	पूर्ण

	priv->volt_sel[id] = selector;
	वापस 0;
पूर्ण

अटल पूर्णांक rt4801_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rt4801_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);

	अगर (priv->enable_flag & BIT(id))
		वापस regulator_get_voltage_sel_regmap(rdev);

	वापस priv->volt_sel[id];
पूर्ण

अटल पूर्णांक rt4801_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rt4801_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा gpio_descs *gpios = priv->enable_gpios;
	पूर्णांक id = rdev_get_id(rdev), ret;

	अगर (!gpios || gpios->ndescs <= id) अणु
		dev_warn(&rdev->dev, "no dedicated gpio can control\n");
		जाओ bypass_gpio;
	पूर्ण

	gpiod_set_value(gpios->desc[id], 1);

bypass_gpio:
	ret = regmap_ग_लिखो(rdev->regmap, rdev->desc->vsel_reg, priv->volt_sel[id]);
	अगर (ret)
		वापस ret;

	priv->enable_flag |= BIT(id);
	वापस 0;
पूर्ण

अटल पूर्णांक rt4801_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rt4801_priv *priv = rdev_get_drvdata(rdev);
	काष्ठा gpio_descs *gpios = priv->enable_gpios;
	पूर्णांक id = rdev_get_id(rdev);

	अगर (!gpios || gpios->ndescs <= id) अणु
		dev_warn(&rdev->dev, "no dedicated gpio can control\n");
		जाओ bypass_gpio;
	पूर्ण

	gpiod_set_value(gpios->desc[id], 0);

bypass_gpio:
	priv->enable_flag &= ~BIT(id);
	वापस 0;
पूर्ण

अटल पूर्णांक rt4801_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rt4801_priv *priv = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);

	वापस !!(priv->enable_flag & BIT(id));
पूर्ण

अटल स्थिर काष्ठा regulator_ops rt4801_regulator_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = rt4801_set_voltage_sel,
	.get_voltage_sel = rt4801_get_voltage_sel,
	.enable = rt4801_enable,
	.disable = rt4801_disable,
	.is_enabled = rt4801_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc rt4801_regulator_descs[] = अणु
	अणु
		.name = "DSVP",
		.ops = &rt4801_regulator_ops,
		.of_match = of_match_ptr("DSVP"),
		.type = REGULATOR_VOLTAGE,
		.id = DSV_OUT_POS,
		.min_uV = MIN_UV,
		.uV_step = STEP_UV,
		.n_voltages = N_VOLTAGES,
		.owner = THIS_MODULE,
		.vsel_reg = RT4801_REG_VOP,
		.vsel_mask = VOUT_MASK,
	पूर्ण,
	अणु
		.name = "DSVN",
		.ops = &rt4801_regulator_ops,
		.of_match = of_match_ptr("DSVN"),
		.type = REGULATOR_VOLTAGE,
		.id = DSV_OUT_NEG,
		.min_uV = MIN_UV,
		.uV_step = STEP_UV,
		.n_voltages = N_VOLTAGES,
		.owner = THIS_MODULE,
		.vsel_reg = RT4801_REG_VON,
		.vsel_mask = VOUT_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt4801_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = RT4801_REG_APPS,
पूर्ण;

अटल पूर्णांक rt4801_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rt4801_priv *priv;
	काष्ठा regmap *regmap;
	पूर्णांक i;

	priv = devm_kzalloc(&i2c->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &i2c->dev;
	/* bootloader will on, driver only reconfigure enable to all output high */
	priv->enable_flag = DSVALL_ENABLE;

	regmap = devm_regmap_init_i2c(i2c, &rt4801_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&i2c->dev, "Failed to init regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	priv->enable_gpios = devm_gpiod_get_array_optional(&i2c->dev, "enable", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->enable_gpios)) अणु
		dev_err(&i2c->dev, "Failed to get gpios\n");
		वापस PTR_ERR(priv->enable_gpios);
	पूर्ण

	क्रम (i = 0; i < DSV_OUT_MAX; i++) अणु
		स्थिर काष्ठा regulator_desc *desc = rt4801_regulator_descs + i;
		काष्ठा regulator_config config = अणु .dev = &i2c->dev, .driver_data = priv,
						   .regmap = regmap, पूर्ण;
		काष्ठा regulator_dev *rdev;
		अचिन्हित पूर्णांक val;
		पूर्णांक ret;

		/* initialize volt_sel variable */
		ret = regmap_पढ़ो(regmap, desc->vsel_reg, &val);
		अगर (ret)
			वापस ret;

		priv->volt_sel[i] = val & desc->vsel_mask;

		rdev = devm_regulator_रेजिस्टर(&i2c->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&i2c->dev, "Failed to register [%d] regulator\n", i);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused rt4801_of_id[] = अणु
	अणु .compatible = "richtek,rt4801", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rt4801_of_id);

अटल काष्ठा i2c_driver rt4801_driver = अणु
	.driver = अणु
		.name = "rt4801",
		.of_match_table = of_match_ptr(rt4801_of_id),
	पूर्ण,
	.probe_new = rt4801_probe,
पूर्ण;
module_i2c_driver(rt4801_driver);

MODULE_AUTHOR("ChiYuan Hwang <cy_huang@richtek.com>");
MODULE_DESCRIPTION("Richtek RT4801 Display Bias Driver");
MODULE_LICENSE("GPL v2");
