<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tps65910.c  --  TI TPS6591x chip family multi-function driver
 *
 * Copyright 2010 Texas Instruments Inc.
 *
 * Author: Graeme Gregory <gg@slimlogic.co.uk>
 * Author: Jorge Eduarकरो Candelaria <jedu@slimlogic.co.uk>
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/tps65910.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

अटल स्थिर काष्ठा resource rtc_resources[] = अणु
	अणु
		.start  = TPS65910_IRQ_RTC_ALARM,
		.end    = TPS65910_IRQ_RTC_ALARM,
		.flags  = IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा mfd_cell tps65910s[] = अणु
	अणु
		.name = "tps65910-gpio",
	पूर्ण,
	अणु
		.name = "tps65910-pmic",
	पूर्ण,
	अणु
		.name = "tps65910-rtc",
		.num_resources = ARRAY_SIZE(rtc_resources),
		.resources = &rtc_resources[0],
	पूर्ण,
	अणु
		.name = "tps65910-power",
	पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा regmap_irq tps65911_irqs[] = अणु
	/* INT_STS */
	[TPS65911_IRQ_PWRHOLD_F] = अणु
		.mask = INT_MSK_PWRHOLD_F_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65911_IRQ_VBAT_VMHI] = अणु
		.mask = INT_MSK_VMBHI_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65911_IRQ_PWRON] = अणु
		.mask = INT_MSK_PWRON_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65911_IRQ_PWRON_LP] = अणु
		.mask = INT_MSK_PWRON_LP_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65911_IRQ_PWRHOLD_R] = अणु
		.mask = INT_MSK_PWRHOLD_R_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65911_IRQ_HOTDIE] = अणु
		.mask = INT_MSK_HOTDIE_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65911_IRQ_RTC_ALARM] = अणु
		.mask = INT_MSK_RTC_ALARM_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65911_IRQ_RTC_PERIOD] = अणु
		.mask = INT_MSK_RTC_PERIOD_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,

	/* INT_STS2 */
	[TPS65911_IRQ_GPIO0_R] = अणु
		.mask = INT_MSK2_GPIO0_R_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,
	[TPS65911_IRQ_GPIO0_F] = अणु
		.mask = INT_MSK2_GPIO0_F_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,
	[TPS65911_IRQ_GPIO1_R] = अणु
		.mask = INT_MSK2_GPIO1_R_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,
	[TPS65911_IRQ_GPIO1_F] = अणु
		.mask = INT_MSK2_GPIO1_F_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,
	[TPS65911_IRQ_GPIO2_R] = अणु
		.mask = INT_MSK2_GPIO2_R_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,
	[TPS65911_IRQ_GPIO2_F] = अणु
		.mask = INT_MSK2_GPIO2_F_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,
	[TPS65911_IRQ_GPIO3_R] = अणु
		.mask = INT_MSK2_GPIO3_R_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,
	[TPS65911_IRQ_GPIO3_F] = अणु
		.mask = INT_MSK2_GPIO3_F_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,

	/* INT_STS2 */
	[TPS65911_IRQ_GPIO4_R] = अणु
		.mask = INT_MSK3_GPIO4_R_IT_MSK_MASK,
		.reg_offset = 2,
	पूर्ण,
	[TPS65911_IRQ_GPIO4_F] = अणु
		.mask = INT_MSK3_GPIO4_F_IT_MSK_MASK,
		.reg_offset = 2,
	पूर्ण,
	[TPS65911_IRQ_GPIO5_R] = अणु
		.mask = INT_MSK3_GPIO5_R_IT_MSK_MASK,
		.reg_offset = 2,
	पूर्ण,
	[TPS65911_IRQ_GPIO5_F] = अणु
		.mask = INT_MSK3_GPIO5_F_IT_MSK_MASK,
		.reg_offset = 2,
	पूर्ण,
	[TPS65911_IRQ_WTCHDG] = अणु
		.mask = INT_MSK3_WTCHDG_IT_MSK_MASK,
		.reg_offset = 2,
	पूर्ण,
	[TPS65911_IRQ_VMBCH2_H] = अणु
		.mask = INT_MSK3_VMBCH2_H_IT_MSK_MASK,
		.reg_offset = 2,
	पूर्ण,
	[TPS65911_IRQ_VMBCH2_L] = अणु
		.mask = INT_MSK3_VMBCH2_L_IT_MSK_MASK,
		.reg_offset = 2,
	पूर्ण,
	[TPS65911_IRQ_PWRDN] = अणु
		.mask = INT_MSK3_PWRDN_IT_MSK_MASK,
		.reg_offset = 2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq tps65910_irqs[] = अणु
	/* INT_STS */
	[TPS65910_IRQ_VBAT_VMBDCH] = अणु
		.mask = TPS65910_INT_MSK_VMBDCH_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65910_IRQ_VBAT_VMHI] = अणु
		.mask = TPS65910_INT_MSK_VMBHI_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65910_IRQ_PWRON] = अणु
		.mask = TPS65910_INT_MSK_PWRON_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65910_IRQ_PWRON_LP] = अणु
		.mask = TPS65910_INT_MSK_PWRON_LP_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65910_IRQ_PWRHOLD] = अणु
		.mask = TPS65910_INT_MSK_PWRHOLD_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65910_IRQ_HOTDIE] = अणु
		.mask = TPS65910_INT_MSK_HOTDIE_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65910_IRQ_RTC_ALARM] = अणु
		.mask = TPS65910_INT_MSK_RTC_ALARM_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,
	[TPS65910_IRQ_RTC_PERIOD] = अणु
		.mask = TPS65910_INT_MSK_RTC_PERIOD_IT_MSK_MASK,
		.reg_offset = 0,
	पूर्ण,

	/* INT_STS2 */
	[TPS65910_IRQ_GPIO_R] = अणु
		.mask = TPS65910_INT_MSK2_GPIO0_F_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,
	[TPS65910_IRQ_GPIO_F] = अणु
		.mask = TPS65910_INT_MSK2_GPIO0_R_IT_MSK_MASK,
		.reg_offset = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा regmap_irq_chip tps65911_irq_chip = अणु
	.name = "tps65910",
	.irqs = tps65911_irqs,
	.num_irqs = ARRAY_SIZE(tps65911_irqs),
	.num_regs = 3,
	.irq_reg_stride = 2,
	.status_base = TPS65910_INT_STS,
	.mask_base = TPS65910_INT_MSK,
	.ack_base = TPS65910_INT_STS,
पूर्ण;

अटल काष्ठा regmap_irq_chip tps65910_irq_chip = अणु
	.name = "tps65910",
	.irqs = tps65910_irqs,
	.num_irqs = ARRAY_SIZE(tps65910_irqs),
	.num_regs = 2,
	.irq_reg_stride = 2,
	.status_base = TPS65910_INT_STS,
	.mask_base = TPS65910_INT_MSK,
	.ack_base = TPS65910_INT_STS,
पूर्ण;

अटल पूर्णांक tps65910_irq_init(काष्ठा tps65910 *tps65910, पूर्णांक irq,
		    काष्ठा tps65910_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;
	अटल काष्ठा regmap_irq_chip *tps6591x_irqs_chip;

	अगर (!irq) अणु
		dev_warn(tps65910->dev, "No interrupt support, no core IRQ\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata) अणु
		dev_warn(tps65910->dev, "No interrupt support, no pdata\n");
		वापस -EINVAL;
	पूर्ण

	चयन (tps65910_chip_id(tps65910)) अणु
	हाल TPS65910:
		tps6591x_irqs_chip = &tps65910_irq_chip;
		अवरोध;
	हाल TPS65911:
		tps6591x_irqs_chip = &tps65911_irq_chip;
		अवरोध;
	पूर्ण

	tps65910->chip_irq = irq;
	ret = devm_regmap_add_irq_chip(tps65910->dev, tps65910->regmap,
				       tps65910->chip_irq,
				       IRQF_ONESHOT, pdata->irq_base,
				       tps6591x_irqs_chip, &tps65910->irq_data);
	अगर (ret < 0) अणु
		dev_warn(tps65910->dev, "Failed to add irq_chip %d\n", ret);
		tps65910->chip_irq = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा tps65910 *tps65910 = dev_get_drvdata(dev);

	/*
	 * Caching all regulator रेजिस्टरs.
	 * All regualator रेजिस्टर address range is same क्रम
	 * TPS65910 and TPS65911
	 */
	अगर ((reg >= TPS65910_VIO) && (reg <= TPS65910_VDAC)) अणु
		/* Check क्रम non-existing रेजिस्टर */
		अगर (tps65910_chip_id(tps65910) == TPS65910)
			अगर ((reg == TPS65911_VDDCTRL_OP) ||
				(reg == TPS65911_VDDCTRL_SR))
				वापस true;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_config tps65910_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_reg = is_अस्थिर_reg,
	.max_रेजिस्टर = TPS65910_MAX_REGISTER - 1,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक tps65910_ck32k_init(काष्ठा tps65910 *tps65910,
					काष्ठा tps65910_board *pmic_pdata)
अणु
	पूर्णांक ret;

	अगर (!pmic_pdata->en_ck32k_xtal)
		वापस 0;

	ret = regmap_clear_bits(tps65910->regmap, TPS65910_DEVCTRL,
				DEVCTRL_CK32K_CTRL_MASK);
	अगर (ret < 0) अणु
		dev_err(tps65910->dev, "clear ck32k_ctrl failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65910_sleepinit(काष्ठा tps65910 *tps65910,
		काष्ठा tps65910_board *pmic_pdata)
अणु
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (!pmic_pdata->en_dev_slp)
		वापस 0;

	dev = tps65910->dev;

	/* enabling SLEEP device state */
	ret = regmap_set_bits(tps65910->regmap, TPS65910_DEVCTRL,
			      DEVCTRL_DEV_SLP_MASK);
	अगर (ret < 0) अणु
		dev_err(dev, "set dev_slp failed: %d\n", ret);
		जाओ err_sleep_init;
	पूर्ण

	अगर (pmic_pdata->slp_keepon.therm_keepon) अणु
		ret = regmap_set_bits(tps65910->regmap,
				      TPS65910_SLEEP_KEEP_RES_ON,
				      SLEEP_KEEP_RES_ON_THERM_KEEPON_MASK);
		अगर (ret < 0) अणु
			dev_err(dev, "set therm_keepon failed: %d\n", ret);
			जाओ disable_dev_slp;
		पूर्ण
	पूर्ण

	अगर (pmic_pdata->slp_keepon.clkout32k_keepon) अणु
		ret = regmap_set_bits(tps65910->regmap,
				      TPS65910_SLEEP_KEEP_RES_ON,
				      SLEEP_KEEP_RES_ON_CLKOUT32K_KEEPON_MASK);
		अगर (ret < 0) अणु
			dev_err(dev, "set clkout32k_keepon failed: %d\n", ret);
			जाओ disable_dev_slp;
		पूर्ण
	पूर्ण

	अगर (pmic_pdata->slp_keepon.i2chs_keepon) अणु
		ret = regmap_set_bits(tps65910->regmap,
				      TPS65910_SLEEP_KEEP_RES_ON,
				      SLEEP_KEEP_RES_ON_I2CHS_KEEPON_MASK);
		अगर (ret < 0) अणु
			dev_err(dev, "set i2chs_keepon failed: %d\n", ret);
			जाओ disable_dev_slp;
		पूर्ण
	पूर्ण

	वापस 0;

disable_dev_slp:
	regmap_clear_bits(tps65910->regmap, TPS65910_DEVCTRL,
			  DEVCTRL_DEV_SLP_MASK);

err_sleep_init:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tps65910_of_match[] = अणु
	अणु .compatible = "ti,tps65910", .data = (व्योम *)TPS65910पूर्ण,
	अणु .compatible = "ti,tps65911", .data = (व्योम *)TPS65911पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा tps65910_board *tps65910_parse_dt(काष्ठा i2c_client *client,
						अचिन्हित दीर्घ *chip_id)
अणु
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा tps65910_board *board_info;
	अचिन्हित पूर्णांक prop;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	match = of_match_device(tps65910_of_match, &client->dev);
	अगर (!match) अणु
		dev_err(&client->dev, "Failed to find matching dt id\n");
		वापस शून्य;
	पूर्ण

	*chip_id  = (अचिन्हित दीर्घ)match->data;

	board_info = devm_kzalloc(&client->dev, माप(*board_info),
			GFP_KERNEL);
	अगर (!board_info)
		वापस शून्य;

	ret = of_property_पढ़ो_u32(np, "ti,vmbch-threshold", &prop);
	अगर (!ret)
		board_info->vmbch_threshold = prop;

	ret = of_property_पढ़ो_u32(np, "ti,vmbch2-threshold", &prop);
	अगर (!ret)
		board_info->vmbch2_threshold = prop;

	prop = of_property_पढ़ो_bool(np, "ti,en-ck32k-xtal");
	board_info->en_ck32k_xtal = prop;

	prop = of_property_पढ़ो_bool(np, "ti,sleep-enable");
	board_info->en_dev_slp = prop;

	prop = of_property_पढ़ो_bool(np, "ti,sleep-keep-therm");
	board_info->slp_keepon.therm_keepon = prop;

	prop = of_property_पढ़ो_bool(np, "ti,sleep-keep-ck32k");
	board_info->slp_keepon.clkout32k_keepon = prop;

	prop = of_property_पढ़ो_bool(np, "ti,sleep-keep-hsclk");
	board_info->slp_keepon.i2chs_keepon = prop;

	board_info->irq = client->irq;
	board_info->irq_base = -1;
	board_info->pm_off = of_property_पढ़ो_bool(np,
			"ti,system-power-controller");

	वापस board_info;
पूर्ण
#अन्यथा
अटल अंतरभूत
काष्ठा tps65910_board *tps65910_parse_dt(काष्ठा i2c_client *client,
					 अचिन्हित दीर्घ *chip_id)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा i2c_client *tps65910_i2c_client;
अटल व्योम tps65910_घातer_off(व्योम)
अणु
	काष्ठा tps65910 *tps65910;

	tps65910 = dev_get_drvdata(&tps65910_i2c_client->dev);

	/*
	 * The PWR_OFF bit needs to be set separately, beक्रमe transitioning
	 * to the OFF state. It enables the "sequential" घातer-off mode on
	 * TPS65911, it's a NO-OP on TPS65910.
	 */
	अगर (regmap_set_bits(tps65910->regmap, TPS65910_DEVCTRL,
			    DEVCTRL_PWR_OFF_MASK) < 0)
		वापस;

	regmap_update_bits(tps65910->regmap, TPS65910_DEVCTRL,
			   DEVCTRL_DEV_OFF_MASK | DEVCTRL_DEV_ON_MASK,
			   DEVCTRL_DEV_OFF_MASK);
पूर्ण

अटल पूर्णांक tps65910_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tps65910 *tps65910;
	काष्ठा tps65910_board *pmic_plat_data;
	काष्ठा tps65910_board *of_pmic_plat_data = शून्य;
	काष्ठा tps65910_platक्रमm_data *init_data;
	अचिन्हित दीर्घ chip_id = id->driver_data;
	पूर्णांक ret;

	pmic_plat_data = dev_get_platdata(&i2c->dev);

	अगर (!pmic_plat_data && i2c->dev.of_node) अणु
		pmic_plat_data = tps65910_parse_dt(i2c, &chip_id);
		of_pmic_plat_data = pmic_plat_data;
	पूर्ण

	अगर (!pmic_plat_data)
		वापस -EINVAL;

	init_data = devm_kzalloc(&i2c->dev, माप(*init_data), GFP_KERNEL);
	अगर (init_data == शून्य)
		वापस -ENOMEM;

	tps65910 = devm_kzalloc(&i2c->dev, माप(*tps65910), GFP_KERNEL);
	अगर (tps65910 == शून्य)
		वापस -ENOMEM;

	tps65910->of_plat_data = of_pmic_plat_data;
	i2c_set_clientdata(i2c, tps65910);
	tps65910->dev = &i2c->dev;
	tps65910->i2c_client = i2c;
	tps65910->id = chip_id;

	/* Work around silicon erratum SWCZ010: the tps65910 may miss the
	 * first I2C transfer. So issue a dummy transfer beक्रमe the first
	 * real transfer.
	 */
	i2c_master_send(i2c, "", 1);
	tps65910->regmap = devm_regmap_init_i2c(i2c, &tps65910_regmap_config);
	अगर (IS_ERR(tps65910->regmap)) अणु
		ret = PTR_ERR(tps65910->regmap);
		dev_err(&i2c->dev, "regmap initialization failed: %d\n", ret);
		वापस ret;
	पूर्ण

	init_data->irq = pmic_plat_data->irq;
	init_data->irq_base = pmic_plat_data->irq_base;

	tps65910_irq_init(tps65910, init_data->irq, init_data);
	tps65910_ck32k_init(tps65910, pmic_plat_data);
	tps65910_sleepinit(tps65910, pmic_plat_data);

	अगर (pmic_plat_data->pm_off && !pm_घातer_off) अणु
		tps65910_i2c_client = i2c;
		pm_घातer_off = tps65910_घातer_off;
	पूर्ण

	ret = devm_mfd_add_devices(tps65910->dev, -1,
				   tps65910s, ARRAY_SIZE(tps65910s),
				   शून्य, 0,
				   regmap_irq_get_करोमुख्य(tps65910->irq_data));
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "mfd_add_devices failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps65910_i2c_id[] = अणु
       अणु "tps65910", TPS65910 पूर्ण,
       अणु "tps65911", TPS65911 पूर्ण,
       अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver tps65910_i2c_driver = अणु
	.driver = अणु
		   .name = "tps65910",
		   .of_match_table = of_match_ptr(tps65910_of_match),
	पूर्ण,
	.probe = tps65910_i2c_probe,
	.id_table = tps65910_i2c_id,
पूर्ण;

अटल पूर्णांक __init tps65910_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&tps65910_i2c_driver);
पूर्ण
/* init early so consumer devices can complete प्रणाली boot */
subsys_initcall(tps65910_i2c_init);
