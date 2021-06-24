<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Poweroff & reset driver क्रम Actions Semi ATC260x PMICs
 *
 * Copyright (c) 2020 Cristian Ciocaltea <cristian.ciocaltea@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/mfd/atc260x/core.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

काष्ठा atc260x_pwrc अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा notअगरier_block restart_nb;
	पूर्णांक (*करो_घातeroff)(स्थिर काष्ठा atc260x_pwrc *pwrc, bool restart);
पूर्ण;

/* Global variable needed only क्रम pm_घातer_off */
अटल काष्ठा atc260x_pwrc *atc260x_pwrc_data;

अटल पूर्णांक atc2603c_करो_घातeroff(स्थिर काष्ठा atc260x_pwrc *pwrc, bool restart)
अणु
	पूर्णांक ret, deep_sleep = 0;
	uपूर्णांक reg_mask, reg_val;

	/* S4-Deep Sleep Mode is NOT available क्रम WALL/USB घातer */
	अगर (!restart && !घातer_supply_is_प्रणाली_supplied()) अणु
		deep_sleep = 1;
		dev_info(pwrc->dev, "Enabling S4-Deep Sleep Mode");
	पूर्ण

	/* Update wakeup sources */
	reg_val = ATC2603C_PMU_SYS_CTL0_ONOFF_LONG_WK_EN |
		  (restart ? ATC2603C_PMU_SYS_CTL0_RESET_WK_EN
			   : ATC2603C_PMU_SYS_CTL0_ONOFF_SHORT_WK_EN);

	ret = regmap_update_bits(pwrc->regmap, ATC2603C_PMU_SYS_CTL0,
				 ATC2603C_PMU_SYS_CTL0_WK_ALL, reg_val);
	अगर (ret)
		dev_warn(pwrc->dev, "failed to write SYS_CTL0: %d\n", ret);

	/* Update घातer mode */
	reg_mask = ATC2603C_PMU_SYS_CTL3_EN_S2 | ATC2603C_PMU_SYS_CTL3_EN_S3;

	ret = regmap_update_bits(pwrc->regmap, ATC2603C_PMU_SYS_CTL3, reg_mask,
				 deep_sleep ? 0 : ATC2603C_PMU_SYS_CTL3_EN_S3);
	अगर (ret) अणु
		dev_err(pwrc->dev, "failed to write SYS_CTL3: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Trigger घातeroff / restart sequence */
	reg_mask = restart ? ATC2603C_PMU_SYS_CTL0_RESTART_EN
			   : ATC2603C_PMU_SYS_CTL1_EN_S1;
	reg_val = restart ? ATC2603C_PMU_SYS_CTL0_RESTART_EN : 0;

	ret = regmap_update_bits(pwrc->regmap,
				 restart ? ATC2603C_PMU_SYS_CTL0 : ATC2603C_PMU_SYS_CTL1,
				 reg_mask, reg_val);
	अगर (ret) अणु
		dev_err(pwrc->dev, "failed to write SYS_CTL%d: %d\n",
			restart ? 0 : 1, ret);
		वापस ret;
	पूर्ण

	/* Wait क्रम trigger completion */
	mdelay(200);

	वापस 0;
पूर्ण

अटल पूर्णांक atc2609a_करो_घातeroff(स्थिर काष्ठा atc260x_pwrc *pwrc, bool restart)
अणु
	पूर्णांक ret, deep_sleep = 0;
	uपूर्णांक reg_mask, reg_val;

	/* S4-Deep Sleep Mode is NOT available क्रम WALL/USB घातer */
	अगर (!restart && !घातer_supply_is_प्रणाली_supplied()) अणु
		deep_sleep = 1;
		dev_info(pwrc->dev, "Enabling S4-Deep Sleep Mode");
	पूर्ण

	/* Update wakeup sources */
	reg_val = ATC2609A_PMU_SYS_CTL0_ONOFF_LONG_WK_EN |
		  (restart ? ATC2609A_PMU_SYS_CTL0_RESET_WK_EN
			   : ATC2609A_PMU_SYS_CTL0_ONOFF_SHORT_WK_EN);

	ret = regmap_update_bits(pwrc->regmap, ATC2609A_PMU_SYS_CTL0,
				 ATC2609A_PMU_SYS_CTL0_WK_ALL, reg_val);
	अगर (ret)
		dev_warn(pwrc->dev, "failed to write SYS_CTL0: %d\n", ret);

	/* Update घातer mode */
	reg_mask = ATC2609A_PMU_SYS_CTL3_EN_S2 | ATC2609A_PMU_SYS_CTL3_EN_S3;

	ret = regmap_update_bits(pwrc->regmap, ATC2609A_PMU_SYS_CTL3, reg_mask,
				 deep_sleep ? 0 : ATC2609A_PMU_SYS_CTL3_EN_S3);
	अगर (ret) अणु
		dev_err(pwrc->dev, "failed to write SYS_CTL3: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Trigger घातeroff / restart sequence */
	reg_mask = restart ? ATC2609A_PMU_SYS_CTL0_RESTART_EN
			   : ATC2609A_PMU_SYS_CTL1_EN_S1;
	reg_val = restart ? ATC2609A_PMU_SYS_CTL0_RESTART_EN : 0;

	ret = regmap_update_bits(pwrc->regmap,
				 restart ? ATC2609A_PMU_SYS_CTL0 : ATC2609A_PMU_SYS_CTL1,
				 reg_mask, reg_val);
	अगर (ret) अणु
		dev_err(pwrc->dev, "failed to write SYS_CTL%d: %d\n",
			restart ? 0 : 1, ret);
		वापस ret;
	पूर्ण

	/* Wait क्रम trigger completion */
	mdelay(200);

	वापस 0;
पूर्ण

अटल पूर्णांक atc2603c_init(स्थिर काष्ठा atc260x_pwrc *pwrc)
अणु
	पूर्णांक ret;

	/*
	 * Delay transition from S2/S3 to S1 in order to aव्योम
	 * DDR init failure in Bootloader.
	 */
	ret = regmap_update_bits(pwrc->regmap, ATC2603C_PMU_SYS_CTL3,
				 ATC2603C_PMU_SYS_CTL3_S2S3TOS1_TIMER_EN,
				 ATC2603C_PMU_SYS_CTL3_S2S3TOS1_TIMER_EN);
	अगर (ret)
		dev_warn(pwrc->dev, "failed to write SYS_CTL3: %d\n", ret);

	/* Set wakeup sources */
	ret = regmap_update_bits(pwrc->regmap, ATC2603C_PMU_SYS_CTL0,
				 ATC2603C_PMU_SYS_CTL0_WK_ALL,
				 ATC2603C_PMU_SYS_CTL0_HDSW_WK_EN |
				 ATC2603C_PMU_SYS_CTL0_ONOFF_LONG_WK_EN);
	अगर (ret)
		dev_warn(pwrc->dev, "failed to write SYS_CTL0: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक atc2609a_init(स्थिर काष्ठा atc260x_pwrc *pwrc)
अणु
	पूर्णांक ret;

	/* Set wakeup sources */
	ret = regmap_update_bits(pwrc->regmap, ATC2609A_PMU_SYS_CTL0,
				 ATC2609A_PMU_SYS_CTL0_WK_ALL,
				 ATC2609A_PMU_SYS_CTL0_HDSW_WK_EN |
				 ATC2609A_PMU_SYS_CTL0_ONOFF_LONG_WK_EN);
	अगर (ret)
		dev_warn(pwrc->dev, "failed to write SYS_CTL0: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम atc260x_pwrc_pm_handler(व्योम)
अणु
	atc260x_pwrc_data->करो_घातeroff(atc260x_pwrc_data, false);

	WARN_ONCE(1, "Unable to power off system\n");
पूर्ण

अटल पूर्णांक atc260x_pwrc_restart_handler(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा atc260x_pwrc *pwrc = container_of(nb, काष्ठा atc260x_pwrc,
						 restart_nb);
	pwrc->करो_घातeroff(pwrc, true);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक atc260x_pwrc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा atc260x *atc260x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा atc260x_pwrc *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	priv->regmap = atc260x->regmap;
	priv->restart_nb.notअगरier_call = atc260x_pwrc_restart_handler;
	priv->restart_nb.priority = 192;

	चयन (atc260x->ic_type) अणु
	हाल ATC2603C:
		priv->करो_घातeroff = atc2603c_करो_घातeroff;
		ret = atc2603c_init(priv);
		अवरोध;
	हाल ATC2609A:
		priv->करो_घातeroff = atc2609a_करो_घातeroff;
		ret = atc2609a_init(priv);
		अवरोध;
	शेष:
		dev_err(priv->dev,
			"Poweroff not supported for ATC260x PMIC type: %u\n",
			atc260x->ic_type);
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	अगर (!pm_घातer_off) अणु
		atc260x_pwrc_data = priv;
		pm_घातer_off = atc260x_pwrc_pm_handler;
	पूर्ण अन्यथा अणु
		dev_warn(priv->dev, "Poweroff callback already assigned\n");
	पूर्ण

	ret = रेजिस्टर_restart_handler(&priv->restart_nb);
	अगर (ret)
		dev_err(priv->dev, "failed to register restart handler: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक atc260x_pwrc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा atc260x_pwrc *priv = platक्रमm_get_drvdata(pdev);

	अगर (atc260x_pwrc_data == priv) अणु
		pm_घातer_off = शून्य;
		atc260x_pwrc_data = शून्य;
	पूर्ण

	unरेजिस्टर_restart_handler(&priv->restart_nb);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver atc260x_pwrc_driver = अणु
	.probe = atc260x_pwrc_probe,
	.हटाओ = atc260x_pwrc_हटाओ,
	.driver = अणु
		.name = "atc260x-pwrc",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(atc260x_pwrc_driver);

MODULE_DESCRIPTION("Poweroff & reset driver for ATC260x PMICs");
MODULE_AUTHOR("Cristian Ciocaltea <cristian.ciocaltea@gmail.com>");
MODULE_LICENSE("GPL");
