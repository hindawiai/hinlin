<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2012 Samsung Electronics Co., Ltd
//              http://www.samsung.com

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/samsung/core.h>
#समावेश <linux/mfd/samsung/irq.h>
#समावेश <linux/mfd/samsung/s2mpa01.h>
#समावेश <linux/mfd/samsung/s2mps11.h>
#समावेश <linux/mfd/samsung/s2mps13.h>
#समावेश <linux/mfd/samsung/s2mps14.h>
#समावेश <linux/mfd/samsung/s2mps15.h>
#समावेश <linux/mfd/samsung/s2mpu02.h>
#समावेश <linux/mfd/samsung/s5m8763.h>
#समावेश <linux/mfd/samsung/s5m8767.h>
#समावेश <linux/regmap.h>

अटल स्थिर काष्ठा mfd_cell s5m8751_devs[] = अणु
	अणु .name = "s5m8751-pmic", पूर्ण,
	अणु .name = "s5m-charger", पूर्ण,
	अणु .name = "s5m8751-codec", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell s5m8763_devs[] = अणु
	अणु .name = "s5m8763-pmic", पूर्ण,
	अणु .name = "s5m-rtc", पूर्ण,
	अणु .name = "s5m-charger", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell s5m8767_devs[] = अणु
	अणु .name = "s5m8767-pmic", पूर्ण,
	अणु .name = "s5m-rtc", पूर्ण,
	अणु
		.name = "s5m8767-clk",
		.of_compatible = "samsung,s5m8767-clk",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell s2mps11_devs[] = अणु
	अणु .name = "s2mps11-regulator", पूर्ण,
	अणु .name = "s2mps14-rtc", पूर्ण,
	अणु
		.name = "s2mps11-clk",
		.of_compatible = "samsung,s2mps11-clk",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell s2mps13_devs[] = अणु
	अणु .name = "s2mps13-regulator", पूर्ण,
	अणु .name = "s2mps13-rtc", पूर्ण,
	अणु
		.name = "s2mps13-clk",
		.of_compatible = "samsung,s2mps13-clk",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell s2mps14_devs[] = अणु
	अणु .name = "s2mps14-regulator", पूर्ण,
	अणु .name = "s2mps14-rtc", पूर्ण,
	अणु
		.name = "s2mps14-clk",
		.of_compatible = "samsung,s2mps14-clk",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell s2mps15_devs[] = अणु
	अणु .name = "s2mps15-regulator", पूर्ण,
	अणु .name = "s2mps15-rtc", पूर्ण,
	अणु
		.name = "s2mps13-clk",
		.of_compatible = "samsung,s2mps13-clk",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell s2mpa01_devs[] = अणु
	अणु .name = "s2mpa01-pmic", पूर्ण,
	अणु .name = "s2mps14-rtc", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell s2mpu02_devs[] = अणु
	अणु .name = "s2mpu02-regulator", पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sec_dt_match[] = अणु
	अणु
		.compatible = "samsung,s5m8767-pmic",
		.data = (व्योम *)S5M8767X,
	पूर्ण, अणु
		.compatible = "samsung,s2mps11-pmic",
		.data = (व्योम *)S2MPS11X,
	पूर्ण, अणु
		.compatible = "samsung,s2mps13-pmic",
		.data = (व्योम *)S2MPS13X,
	पूर्ण, अणु
		.compatible = "samsung,s2mps14-pmic",
		.data = (व्योम *)S2MPS14X,
	पूर्ण, अणु
		.compatible = "samsung,s2mps15-pmic",
		.data = (व्योम *)S2MPS15X,
	पूर्ण, अणु
		.compatible = "samsung,s2mpa01-pmic",
		.data = (व्योम *)S2MPA01,
	पूर्ण, अणु
		.compatible = "samsung,s2mpu02-pmic",
		.data = (व्योम *)S2MPU02,
	पूर्ण, अणु
		/* Sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sec_dt_match);
#पूर्ण_अगर

अटल bool s2mpa01_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल S2MPA01_REG_INT1M:
	हाल S2MPA01_REG_INT2M:
	हाल S2MPA01_REG_INT3M:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool s2mps11_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल S2MPS11_REG_INT1M:
	हाल S2MPS11_REG_INT2M:
	हाल S2MPS11_REG_INT3M:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool s2mpu02_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल S2MPU02_REG_INT1M:
	हाल S2MPU02_REG_INT2M:
	हाल S2MPU02_REG_INT3M:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool s5m8763_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल S5M8763_REG_IRQM1:
	हाल S5M8763_REG_IRQM2:
	हाल S5M8763_REG_IRQM3:
	हाल S5M8763_REG_IRQM4:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config sec_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा regmap_config s2mpa01_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S2MPA01_REG_LDO_OVCB4,
	.अस्थिर_reg = s2mpa01_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config s2mps11_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S2MPS11_REG_L38CTRL,
	.अस्थिर_reg = s2mps11_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config s2mps13_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S2MPS13_REG_LDODSCH5,
	.अस्थिर_reg = s2mps11_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config s2mps14_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S2MPS14_REG_LDODSCH3,
	.अस्थिर_reg = s2mps11_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config s2mps15_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S2MPS15_REG_LDODSCH4,
	.अस्थिर_reg = s2mps11_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config s2mpu02_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S2MPU02_REG_DVSDATA,
	.अस्थिर_reg = s2mpu02_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config s5m8763_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S5M8763_REG_LBCNFG2,
	.अस्थिर_reg = s5m8763_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config s5m8767_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = S5M8767_REG_LDO28CTRL,
	.अस्थिर_reg = s2mps11_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल व्योम sec_pmic_dump_rev(काष्ठा sec_pmic_dev *sec_pmic)
अणु
	अचिन्हित पूर्णांक val;

	/* For each device type, the REG_ID is always the first रेजिस्टर */
	अगर (!regmap_पढ़ो(sec_pmic->regmap_pmic, S2MPS11_REG_ID, &val))
		dev_dbg(sec_pmic->dev, "Revision: 0x%x\n", val);
पूर्ण

अटल व्योम sec_pmic_configure(काष्ठा sec_pmic_dev *sec_pmic)
अणु
	पूर्णांक err;

	अगर (sec_pmic->device_type != S2MPS13X)
		वापस;

	अगर (sec_pmic->pdata->disable_wrstbi) अणु
		/*
		 * If WRSTBI pin is pulled करोwn this feature must be disabled
		 * because each Suspend to RAM will trigger buck voltage reset
		 * to शेष values.
		 */
		err = regmap_update_bits(sec_pmic->regmap_pmic,
					 S2MPS13_REG_WRSTBI,
					 S2MPS13_REG_WRSTBI_MASK, 0x0);
		अगर (err)
			dev_warn(sec_pmic->dev,
				 "Cannot initialize WRSTBI config: %d\n",
				 err);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_OF
/*
 * Only the common platक्रमm data elements क्रम s5m8767 are parsed here from the
 * device tree. Other sub-modules of s5m8767 such as pmic, rtc , अक्षरger and
 * others have to parse their own platक्रमm data elements from device tree.
 *
 * The s5m8767 platक्रमm data काष्ठाure is instantiated here and the drivers क्रम
 * the sub-modules need not instantiate another instance जबतक parsing their
 * platक्रमm data.
 */
अटल काष्ठा sec_platक्रमm_data *
sec_pmic_i2c_parse_dt_pdata(काष्ठा device *dev)
अणु
	काष्ठा sec_platक्रमm_data *pd;

	pd = devm_kzalloc(dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * ToDo: the 'wakeup' member in the platक्रमm data is more of a linux
	 * specfic inक्रमmation. Hence, there is no binding क्रम that yet and
	 * not parsed here.
	 */

	pd->manual_घातeroff = of_property_पढ़ो_bool(dev->of_node,
						"samsung,s2mps11-acokb-ground");
	pd->disable_wrstbi = of_property_पढ़ो_bool(dev->of_node,
						"samsung,s2mps11-wrstbi-ground");
	वापस pd;
पूर्ण
#अन्यथा
अटल काष्ठा sec_platक्रमm_data *
sec_pmic_i2c_parse_dt_pdata(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ sec_i2c_get_driver_data(काष्ठा i2c_client *i2c,
						स्थिर काष्ठा i2c_device_id *id)
अणु
#अगर_घोषित CONFIG_OF
	अगर (i2c->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(sec_dt_match, i2c->dev.of_node);
		वापस (अचिन्हित दीर्घ)match->data;
	पूर्ण
#पूर्ण_अगर
	वापस id->driver_data;
पूर्ण

अटल पूर्णांक sec_pmic_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा sec_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	स्थिर काष्ठा regmap_config *regmap;
	स्थिर काष्ठा mfd_cell *sec_devs;
	काष्ठा sec_pmic_dev *sec_pmic;
	अचिन्हित दीर्घ device_type;
	पूर्णांक ret, num_sec_devs;

	sec_pmic = devm_kzalloc(&i2c->dev, माप(काष्ठा sec_pmic_dev),
				GFP_KERNEL);
	अगर (sec_pmic == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, sec_pmic);
	sec_pmic->dev = &i2c->dev;
	sec_pmic->i2c = i2c;
	sec_pmic->irq = i2c->irq;
	device_type = sec_i2c_get_driver_data(i2c, id);

	अगर (sec_pmic->dev->of_node) अणु
		pdata = sec_pmic_i2c_parse_dt_pdata(sec_pmic->dev);
		अगर (IS_ERR(pdata)) अणु
			ret = PTR_ERR(pdata);
			वापस ret;
		पूर्ण
		pdata->device_type = device_type;
	पूर्ण
	अगर (pdata) अणु
		sec_pmic->device_type = pdata->device_type;
		sec_pmic->irq_base = pdata->irq_base;
		sec_pmic->wakeup = pdata->wakeup;
		sec_pmic->pdata = pdata;
	पूर्ण

	चयन (sec_pmic->device_type) अणु
	हाल S2MPA01:
		regmap = &s2mpa01_regmap_config;
		अवरोध;
	हाल S2MPS11X:
		regmap = &s2mps11_regmap_config;
		अवरोध;
	हाल S2MPS13X:
		regmap = &s2mps13_regmap_config;
		अवरोध;
	हाल S2MPS14X:
		regmap = &s2mps14_regmap_config;
		अवरोध;
	हाल S2MPS15X:
		regmap = &s2mps15_regmap_config;
		अवरोध;
	हाल S5M8763X:
		regmap = &s5m8763_regmap_config;
		अवरोध;
	हाल S5M8767X:
		regmap = &s5m8767_regmap_config;
		अवरोध;
	हाल S2MPU02:
		regmap = &s2mpu02_regmap_config;
		अवरोध;
	शेष:
		regmap = &sec_regmap_config;
		अवरोध;
	पूर्ण

	sec_pmic->regmap_pmic = devm_regmap_init_i2c(i2c, regmap);
	अगर (IS_ERR(sec_pmic->regmap_pmic)) अणु
		ret = PTR_ERR(sec_pmic->regmap_pmic);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (pdata && pdata->cfg_pmic_irq)
		pdata->cfg_pmic_irq();

	sec_irq_init(sec_pmic);

	pm_runसमय_set_active(sec_pmic->dev);

	चयन (sec_pmic->device_type) अणु
	हाल S5M8751X:
		sec_devs = s5m8751_devs;
		num_sec_devs = ARRAY_SIZE(s5m8751_devs);
		अवरोध;
	हाल S5M8763X:
		sec_devs = s5m8763_devs;
		num_sec_devs = ARRAY_SIZE(s5m8763_devs);
		अवरोध;
	हाल S5M8767X:
		sec_devs = s5m8767_devs;
		num_sec_devs = ARRAY_SIZE(s5m8767_devs);
		अवरोध;
	हाल S2MPA01:
		sec_devs = s2mpa01_devs;
		num_sec_devs = ARRAY_SIZE(s2mpa01_devs);
		अवरोध;
	हाल S2MPS11X:
		sec_devs = s2mps11_devs;
		num_sec_devs = ARRAY_SIZE(s2mps11_devs);
		अवरोध;
	हाल S2MPS13X:
		sec_devs = s2mps13_devs;
		num_sec_devs = ARRAY_SIZE(s2mps13_devs);
		अवरोध;
	हाल S2MPS14X:
		sec_devs = s2mps14_devs;
		num_sec_devs = ARRAY_SIZE(s2mps14_devs);
		अवरोध;
	हाल S2MPS15X:
		sec_devs = s2mps15_devs;
		num_sec_devs = ARRAY_SIZE(s2mps15_devs);
		अवरोध;
	हाल S2MPU02:
		sec_devs = s2mpu02_devs;
		num_sec_devs = ARRAY_SIZE(s2mpu02_devs);
		अवरोध;
	शेष:
		dev_err(&i2c->dev, "Unsupported device type (%lu)\n",
			sec_pmic->device_type);
		वापस -ENODEV;
	पूर्ण
	ret = devm_mfd_add_devices(sec_pmic->dev, -1, sec_devs, num_sec_devs,
				   शून्य, 0, शून्य);
	अगर (ret)
		वापस ret;

	device_init_wakeup(sec_pmic->dev, sec_pmic->wakeup);
	sec_pmic_configure(sec_pmic);
	sec_pmic_dump_rev(sec_pmic);

	वापस ret;
पूर्ण

अटल व्योम sec_pmic_shutकरोwn(काष्ठा i2c_client *i2c)
अणु
	काष्ठा sec_pmic_dev *sec_pmic = i2c_get_clientdata(i2c);
	अचिन्हित पूर्णांक reg, mask;

	अगर (!sec_pmic->pdata->manual_घातeroff)
		वापस;

	चयन (sec_pmic->device_type) अणु
	हाल S2MPS11X:
		reg = S2MPS11_REG_CTRL1;
		mask = S2MPS11_CTRL1_PWRHOLD_MASK;
		अवरोध;
	शेष:
		/*
		 * Currently only one board with S2MPS11 needs this, so just
		 * ignore the rest.
		 */
		dev_warn(sec_pmic->dev,
			"Unsupported device %lu for manual power off\n",
			sec_pmic->device_type);
		वापस;
	पूर्ण

	regmap_update_bits(sec_pmic->regmap_pmic, reg, mask, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sec_pmic_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा sec_pmic_dev *sec_pmic = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(sec_pmic->irq);
	/*
	 * PMIC IRQ must be disabled during suspend क्रम RTC alarm
	 * to work properly.
	 * When device is woken up from suspend, an
	 * पूर्णांकerrupt occurs beक्रमe resuming I2C bus controller.
	 * The पूर्णांकerrupt is handled by regmap_irq_thपढ़ो which tries
	 * to पढ़ो RTC रेजिस्टरs. This पढ़ो fails (I2C is still
	 * suspended) and RTC Alarm पूर्णांकerrupt is disabled.
	 */
	disable_irq(sec_pmic->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक sec_pmic_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा sec_pmic_dev *sec_pmic = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(sec_pmic->irq);
	enable_irq(sec_pmic->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(sec_pmic_pm_ops, sec_pmic_suspend, sec_pmic_resume);

अटल स्थिर काष्ठा i2c_device_id sec_pmic_id[] = अणु
	अणु "sec_pmic", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sec_pmic_id);

अटल काष्ठा i2c_driver sec_pmic_driver = अणु
	.driver = अणु
		   .name = "sec_pmic",
		   .pm = &sec_pmic_pm_ops,
		   .of_match_table = of_match_ptr(sec_dt_match),
	पूर्ण,
	.probe = sec_pmic_probe,
	.shutकरोwn = sec_pmic_shutकरोwn,
	.id_table = sec_pmic_id,
पूर्ण;
module_i2c_driver(sec_pmic_driver);

MODULE_AUTHOR("Sangbeom Kim <sbkim73@samsung.com>");
MODULE_DESCRIPTION("Core support for the S5M MFD");
MODULE_LICENSE("GPL");
