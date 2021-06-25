<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम tps65090 घातer management chip.
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.

 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/tps65090.h>

#घोषणा MAX_CTRL_READ_TRIES	5
#घोषणा MAX_FET_ENABLE_TRIES	1000

#घोषणा CTRL_EN_BIT		0 /* Regulator enable bit, active high */
#घोषणा CTRL_WT_BIT		2 /* Regulator रुको समय 0 bit */
#घोषणा CTRL_PG_BIT		4 /* Regulator घातer good bit, 1=good */
#घोषणा CTRL_TO_BIT		7 /* Regulator समयout bit, 1=रुको */

#घोषणा MAX_OVERCURRENT_WAIT	3 /* Overcurrent रुको must be <= this */

/**
 * काष्ठा tps65090_regulator - Per-regulator data क्रम a tps65090 regulator
 *
 * @dev: Poपूर्णांकer to our device.
 * @desc: The काष्ठा regulator_desc क्रम the regulator.
 * @rdev: The काष्ठा regulator_dev क्रम the regulator.
 * @overcurrent_रुको_valid: True अगर overcurrent_रुको is valid.
 * @overcurrent_रुको: For FETs, the value to put in the WTFET bitfield.
 */

काष्ठा tps65090_regulator अणु
	काष्ठा device		*dev;
	काष्ठा regulator_desc	*desc;
	काष्ठा regulator_dev	*rdev;
	bool			overcurrent_रुको_valid;
	पूर्णांक			overcurrent_रुको;
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65090_ext_control_ops = अणु
पूर्ण;

/**
 * tps65090_reg_set_overcurrent_रुको - Setup overcurrent रुको
 *
 * This will set the overcurrent रुको समय based on what's in the regulator
 * info.
 *
 * @ri:		Overall regulator data
 * @rdev:	Regulator device
 *
 * Return: 0 अगर no error, non-zero अगर there was an error writing the रेजिस्टर.
 */
अटल पूर्णांक tps65090_reg_set_overcurrent_रुको(काष्ठा tps65090_regulator *ri,
					     काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				 MAX_OVERCURRENT_WAIT << CTRL_WT_BIT,
				 ri->overcurrent_रुको << CTRL_WT_BIT);
	अगर (ret) अणु
		dev_err(&rdev->dev, "Error updating overcurrent wait %#x\n",
			rdev->desc->enable_reg);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * tps65090_try_enable_fet - Try to enable a FET
 *
 * @rdev:	Regulator device
 *
 * Return: 0 अगर ok, -ENOTRECOVERABLE अगर the FET घातer good bit did not get
 * set, or some other -ve value अगर another error occurred (e.g. i2c error)
 */
अटल पूर्णांक tps65090_try_enable_fet(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक control;
	पूर्णांक ret, i;

	ret = regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				 rdev->desc->enable_mask,
				 rdev->desc->enable_mask);
	अगर (ret < 0) अणु
		dev_err(&rdev->dev, "Error in updating reg %#x\n",
			rdev->desc->enable_reg);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < MAX_CTRL_READ_TRIES; i++) अणु
		ret = regmap_पढ़ो(rdev->regmap, rdev->desc->enable_reg,
				  &control);
		अगर (ret < 0)
			वापस ret;

		अगर (!(control & BIT(CTRL_TO_BIT)))
			अवरोध;

		usleep_range(1000, 1500);
	पूर्ण
	अगर (!(control & BIT(CTRL_PG_BIT)))
		वापस -ENOTRECOVERABLE;

	वापस 0;
पूर्ण

/**
 * tps65090_fet_enable - Enable a FET, trying a few बार अगर it fails
 *
 * Some versions of the tps65090 have issues when turning on the FETs.
 * This function goes through several steps to ensure the best chance of the
 * FET going on.  Specअगरically:
 * - We'll make sure that we bump the "overcurrent wait" to the maximum, which
 *   increases the chances that we'll turn on properly.
 * - We'll retry turning the FET on multiple बार (turning off in between).
 *
 * @rdev:	Regulator device
 *
 * Return: 0 अगर ok, non-zero अगर it fails.
 */
अटल पूर्णांक tps65090_fet_enable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret, tries;

	/*
	 * Try enabling multiple बार until we succeed since someबार the
	 * first try बार out.
	 */
	tries = 0;
	जबतक (true) अणु
		ret = tps65090_try_enable_fet(rdev);
		अगर (!ret)
			अवरोध;
		अगर (ret != -ENOTRECOVERABLE || tries == MAX_FET_ENABLE_TRIES)
			जाओ err;

		/* Try turning the FET off (and then on again) */
		ret = regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
					 rdev->desc->enable_mask, 0);
		अगर (ret)
			जाओ err;

		tries++;
	पूर्ण

	अगर (tries)
		dev_warn(&rdev->dev, "reg %#x enable ok after %d tries\n",
			 rdev->desc->enable_reg, tries);

	वापस 0;
err:
	dev_warn(&rdev->dev, "reg %#x enable failed\n", rdev->desc->enable_reg);
	WARN_ON(1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops tps65090_reg_control_ops = अणु
	.enable		= regulator_enable_regmap,
	.disable	= regulator_disable_regmap,
	.is_enabled	= regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65090_fet_control_ops = अणु
	.enable		= tps65090_fet_enable,
	.disable	= regulator_disable_regmap,
	.is_enabled	= regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65090_lकरो_ops = अणु
पूर्ण;

#घोषणा tps65090_REG_DESC(_id, _sname, _en_reg, _en_bits, _nvolt, _volt, _ops) \
अणु							\
	.name = "TPS65090_RAILS"#_id,			\
	.supply_name = _sname,				\
	.id = TPS65090_REGULATOR_##_id,			\
	.n_voltages = _nvolt,				\
	.ops = &_ops,					\
	.fixed_uV = _volt,				\
	.enable_reg = _en_reg,				\
	.enable_val = _en_bits,				\
	.enable_mask = _en_bits,			\
	.type = REGULATOR_VOLTAGE,			\
	.owner = THIS_MODULE,				\
पूर्ण

#घोषणा tps65090_REG_FIXEDV(_id, _sname, en_reg, _en_bits, _volt, _ops) \
	tps65090_REG_DESC(_id, _sname, en_reg, _en_bits, 1, _volt, _ops)

#घोषणा tps65090_REG_SWITCH(_id, _sname, en_reg, _en_bits, _ops) \
	tps65090_REG_DESC(_id, _sname, en_reg, _en_bits, 0, 0, _ops)

अटल काष्ठा regulator_desc tps65090_regulator_desc[] = अणु
	tps65090_REG_FIXEDV(DCDC1, "vsys1",   0x0C, BIT(CTRL_EN_BIT), 5000000,
			    tps65090_reg_control_ops),
	tps65090_REG_FIXEDV(DCDC2, "vsys2",   0x0D, BIT(CTRL_EN_BIT), 3300000,
			    tps65090_reg_control_ops),
	tps65090_REG_SWITCH(DCDC3, "vsys3",   0x0E, BIT(CTRL_EN_BIT),
			    tps65090_reg_control_ops),

	tps65090_REG_SWITCH(FET1,  "infet1",  0x0F,
			    BIT(CTRL_EN_BIT) | BIT(CTRL_PG_BIT),
			    tps65090_fet_control_ops),
	tps65090_REG_SWITCH(FET2,  "infet2",  0x10,
			    BIT(CTRL_EN_BIT) | BIT(CTRL_PG_BIT),
			    tps65090_fet_control_ops),
	tps65090_REG_SWITCH(FET3,  "infet3",  0x11,
			    BIT(CTRL_EN_BIT) | BIT(CTRL_PG_BIT),
			    tps65090_fet_control_ops),
	tps65090_REG_SWITCH(FET4,  "infet4",  0x12,
			    BIT(CTRL_EN_BIT) | BIT(CTRL_PG_BIT),
			    tps65090_fet_control_ops),
	tps65090_REG_SWITCH(FET5,  "infet5",  0x13,
			    BIT(CTRL_EN_BIT) | BIT(CTRL_PG_BIT),
			    tps65090_fet_control_ops),
	tps65090_REG_SWITCH(FET6,  "infet6",  0x14,
			    BIT(CTRL_EN_BIT) | BIT(CTRL_PG_BIT),
			    tps65090_fet_control_ops),
	tps65090_REG_SWITCH(FET7,  "infet7",  0x15,
			    BIT(CTRL_EN_BIT) | BIT(CTRL_PG_BIT),
			    tps65090_fet_control_ops),

	tps65090_REG_FIXEDV(LDO1,  "vsys-l1", 0, 0, 5000000,
			    tps65090_lकरो_ops),
	tps65090_REG_FIXEDV(LDO2,  "vsys-l2", 0, 0, 3300000,
			    tps65090_lकरो_ops),
पूर्ण;

अटल अंतरभूत bool is_dcdc(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल TPS65090_REGULATOR_DCDC1:
	हाल TPS65090_REGULATOR_DCDC2:
	हाल TPS65090_REGULATOR_DCDC3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक tps65090_config_ext_control(
	काष्ठा tps65090_regulator *ri, bool enable)
अणु
	पूर्णांक ret;
	काष्ठा device *parent = ri->dev->parent;
	अचिन्हित पूर्णांक reg_en_reg = ri->desc->enable_reg;

	अगर (enable)
		ret = tps65090_set_bits(parent, reg_en_reg, 1);
	अन्यथा
		ret =  tps65090_clr_bits(parent, reg_en_reg, 1);
	अगर (ret < 0)
		dev_err(ri->dev, "Error in updating reg 0x%x\n", reg_en_reg);
	वापस ret;
पूर्ण

अटल पूर्णांक tps65090_regulator_disable_ext_control(
		काष्ठा tps65090_regulator *ri,
		काष्ठा tps65090_regulator_plat_data *tps_pdata)
अणु
	पूर्णांक ret = 0;
	काष्ठा device *parent = ri->dev->parent;
	अचिन्हित पूर्णांक reg_en_reg = ri->desc->enable_reg;

	/*
	 * First enable output क्रम पूर्णांकernal control अगर require.
	 * And then disable बाह्यal control.
	 */
	अगर (tps_pdata->reg_init_data->स्थिरraपूर्णांकs.always_on ||
			tps_pdata->reg_init_data->स्थिरraपूर्णांकs.boot_on) अणु
		ret =  tps65090_set_bits(parent, reg_en_reg, 0);
		अगर (ret < 0) अणु
			dev_err(ri->dev, "Error in set reg 0x%x\n", reg_en_reg);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस tps65090_config_ext_control(ri, false);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा of_regulator_match tps65090_matches[] = अणु
	अणु .name = "dcdc1", पूर्ण,
	अणु .name = "dcdc2", पूर्ण,
	अणु .name = "dcdc3", पूर्ण,
	अणु .name = "fet1",  पूर्ण,
	अणु .name = "fet2",  पूर्ण,
	अणु .name = "fet3",  पूर्ण,
	अणु .name = "fet4",  पूर्ण,
	अणु .name = "fet5",  पूर्ण,
	अणु .name = "fet6",  पूर्ण,
	अणु .name = "fet7",  पूर्ण,
	अणु .name = "ldo1",  पूर्ण,
	अणु .name = "ldo2",  पूर्ण,
पूर्ण;

अटल काष्ठा tps65090_platक्रमm_data *tps65090_parse_dt_reg_data(
		काष्ठा platक्रमm_device *pdev,
		काष्ठा of_regulator_match **tps65090_reg_matches)
अणु
	काष्ठा tps65090_platक्रमm_data *tps65090_pdata;
	काष्ठा device_node *np = pdev->dev.parent->of_node;
	काष्ठा device_node *regulators;
	पूर्णांक idx = 0, ret;
	काष्ठा tps65090_regulator_plat_data *reg_pdata;

	tps65090_pdata = devm_kzalloc(&pdev->dev, माप(*tps65090_pdata),
				GFP_KERNEL);
	अगर (!tps65090_pdata)
		वापस ERR_PTR(-ENOMEM);

	reg_pdata = devm_kसुस्मृति(&pdev->dev,
				 TPS65090_REGULATOR_MAX, माप(*reg_pdata),
				 GFP_KERNEL);
	अगर (!reg_pdata)
		वापस ERR_PTR(-ENOMEM);

	regulators = of_get_child_by_name(np, "regulators");
	अगर (!regulators) अणु
		dev_err(&pdev->dev, "regulator node not found\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	ret = of_regulator_match(&pdev->dev, regulators, tps65090_matches,
			ARRAY_SIZE(tps65090_matches));
	of_node_put(regulators);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Error parsing regulator init data: %d\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	*tps65090_reg_matches = tps65090_matches;
	क्रम (idx = 0; idx < ARRAY_SIZE(tps65090_matches); idx++) अणु
		काष्ठा regulator_init_data *ri_data;
		काष्ठा tps65090_regulator_plat_data *rpdata;
		काष्ठा device_node *np;

		rpdata = &reg_pdata[idx];
		ri_data = tps65090_matches[idx].init_data;
		अगर (!ri_data)
			जारी;

		np = tps65090_matches[idx].of_node;
		अगर (!np)
			जारी;

		rpdata->reg_init_data = ri_data;
		rpdata->enable_ext_control = of_property_पढ़ो_bool(np,
						"ti,enable-ext-control");
		अगर (rpdata->enable_ext_control) अणु
			क्रमागत gpiod_flags gflags;

			अगर (ri_data->स्थिरraपूर्णांकs.always_on ||
			    ri_data->स्थिरraपूर्णांकs.boot_on)
				gflags = GPIOD_OUT_HIGH;
			अन्यथा
				gflags = GPIOD_OUT_LOW;
			gflags |= GPIOD_FLAGS_BIT_NONEXCLUSIVE;

			rpdata->gpiod = devm_fwnode_gpiod_get(
							&pdev->dev,
							of_fwnode_handle(np),
							"dcdc-ext-control",
							gflags,
							"tps65090");
			अगर (PTR_ERR(rpdata->gpiod) == -ENOENT) अणु
				dev_err(&pdev->dev,
					"could not find DCDC external control GPIO\n");
				rpdata->gpiod = शून्य;
			पूर्ण अन्यथा अगर (IS_ERR(rpdata->gpiod))
				वापस ERR_CAST(rpdata->gpiod);
		पूर्ण

		अगर (of_property_पढ़ो_u32(np, "ti,overcurrent-wait",
					 &rpdata->overcurrent_रुको) == 0)
			rpdata->overcurrent_रुको_valid = true;

		tps65090_pdata->reg_pdata[idx] = rpdata;
	पूर्ण
	वापस tps65090_pdata;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा tps65090_platक्रमm_data *tps65090_parse_dt_reg_data(
			काष्ठा platक्रमm_device *pdev,
			काष्ठा of_regulator_match **tps65090_reg_matches)
अणु
	*tps65090_reg_matches = शून्य;
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tps65090_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65090 *tps65090_mfd = dev_get_drvdata(pdev->dev.parent);
	काष्ठा tps65090_regulator *ri = शून्य;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा tps65090_regulator_plat_data *tps_pdata;
	काष्ठा tps65090_regulator *pmic;
	काष्ठा tps65090_platक्रमm_data *tps65090_pdata;
	काष्ठा of_regulator_match *tps65090_reg_matches = शून्य;
	पूर्णांक num;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "Probing regulator\n");

	tps65090_pdata = dev_get_platdata(pdev->dev.parent);
	अगर (!tps65090_pdata && tps65090_mfd->dev->of_node)
		tps65090_pdata = tps65090_parse_dt_reg_data(pdev,
					&tps65090_reg_matches);
	अगर (IS_ERR_OR_शून्य(tps65090_pdata)) अणु
		dev_err(&pdev->dev, "Platform data missing\n");
		वापस tps65090_pdata ? PTR_ERR(tps65090_pdata) : -EINVAL;
	पूर्ण

	pmic = devm_kसुस्मृति(&pdev->dev,
			    TPS65090_REGULATOR_MAX, माप(*pmic),
			    GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	क्रम (num = 0; num < TPS65090_REGULATOR_MAX; num++) अणु
		tps_pdata = tps65090_pdata->reg_pdata[num];

		ri = &pmic[num];
		ri->dev = &pdev->dev;
		ri->desc = &tps65090_regulator_desc[num];
		अगर (tps_pdata) अणु
			ri->overcurrent_रुको_valid =
				tps_pdata->overcurrent_रुको_valid;
			ri->overcurrent_रुको = tps_pdata->overcurrent_रुको;
		पूर्ण

		/*
		 * TPS5090 DCDC support the control from बाह्यal digital input.
		 * Configure it as per platक्रमm data.
		 */
		अगर (tps_pdata && is_dcdc(num) && tps_pdata->reg_init_data) अणु
			अगर (tps_pdata->enable_ext_control) अणु
				config.ena_gpiod = tps_pdata->gpiod;
				ri->desc->ops = &tps65090_ext_control_ops;
			पूर्ण अन्यथा अणु
				ret = tps65090_regulator_disable_ext_control(
						ri, tps_pdata);
				अगर (ret < 0) अणु
					dev_err(&pdev->dev,
						"failed disable ext control\n");
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण

		config.dev = pdev->dev.parent;
		config.driver_data = ri;
		config.regmap = tps65090_mfd->rmap;
		अगर (tps_pdata)
			config.init_data = tps_pdata->reg_init_data;
		अन्यथा
			config.init_data = शून्य;
		अगर (tps65090_reg_matches)
			config.of_node = tps65090_reg_matches[num].of_node;
		अन्यथा
			config.of_node = शून्य;

		/*
		 * Hand the GPIO descriptor management over to the regulator
		 * core, हटाओ it from devres management.
		 */
		अगर (config.ena_gpiod)
			devm_gpiod_unhinge(&pdev->dev, config.ena_gpiod);
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, ri->desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				ri->desc->name);
			वापस PTR_ERR(rdev);
		पूर्ण
		ri->rdev = rdev;

		अगर (ri->overcurrent_रुको_valid) अणु
			ret = tps65090_reg_set_overcurrent_रुको(ri, rdev);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		/* Enable बाह्यal control अगर it is require */
		अगर (tps_pdata && is_dcdc(num) && tps_pdata->reg_init_data &&
				tps_pdata->enable_ext_control) अणु
			ret = tps65090_config_ext_control(ri, true);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, pmic);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tps65090_regulator_driver = अणु
	.driver	= अणु
		.name	= "tps65090-pmic",
	पूर्ण,
	.probe		= tps65090_regulator_probe,
पूर्ण;

अटल पूर्णांक __init tps65090_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps65090_regulator_driver);
पूर्ण
subsys_initcall(tps65090_regulator_init);

अटल व्योम __निकास tps65090_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tps65090_regulator_driver);
पूर्ण
module_निकास(tps65090_regulator_निकास);

MODULE_DESCRIPTION("tps65090 regulator driver");
MODULE_AUTHOR("Venu Byravarasu <vbyravarasu@nvidia.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:tps65090-pmic");
