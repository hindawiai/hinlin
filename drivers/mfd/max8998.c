<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max8998.c - mfd core driver क्रम the Maxim 8998
//
//  Copyright (C) 2009-2010 Samsung Electronics
//  Kyungmin Park <kyungmin.park@samsung.com>
//  Marek Szyprowski <m.szyprowski@samsung.com>

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max8998.h>
#समावेश <linux/mfd/max8998-निजी.h>

#घोषणा RTC_I2C_ADDR		(0x0c >> 1)

अटल स्थिर काष्ठा mfd_cell max8998_devs[] = अणु
	अणु
		.name = "max8998-pmic",
	पूर्ण, अणु
		.name = "max8998-rtc",
	पूर्ण, अणु
		.name = "max8998-battery",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell lp3974_devs[] = अणु
	अणु
		.name = "lp3974-pmic",
	पूर्ण, अणु
		.name = "lp3974-rtc",
	पूर्ण,
पूर्ण;

पूर्णांक max8998_पढ़ो_reg(काष्ठा i2c_client *i2c, u8 reg, u8 *dest)
अणु
	काष्ठा max8998_dev *max8998 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8998->iolock);
	ret = i2c_smbus_पढ़ो_byte_data(i2c, reg);
	mutex_unlock(&max8998->iolock);
	अगर (ret < 0)
		वापस ret;

	ret &= 0xff;
	*dest = ret;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(max8998_पढ़ो_reg);

पूर्णांक max8998_bulk_पढ़ो(काष्ठा i2c_client *i2c, u8 reg, पूर्णांक count, u8 *buf)
अणु
	काष्ठा max8998_dev *max8998 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8998->iolock);
	ret = i2c_smbus_पढ़ो_i2c_block_data(i2c, reg, count, buf);
	mutex_unlock(&max8998->iolock);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(max8998_bulk_पढ़ो);

पूर्णांक max8998_ग_लिखो_reg(काष्ठा i2c_client *i2c, u8 reg, u8 value)
अणु
	काष्ठा max8998_dev *max8998 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8998->iolock);
	ret = i2c_smbus_ग_लिखो_byte_data(i2c, reg, value);
	mutex_unlock(&max8998->iolock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(max8998_ग_लिखो_reg);

पूर्णांक max8998_bulk_ग_लिखो(काष्ठा i2c_client *i2c, u8 reg, पूर्णांक count, u8 *buf)
अणु
	काष्ठा max8998_dev *max8998 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8998->iolock);
	ret = i2c_smbus_ग_लिखो_i2c_block_data(i2c, reg, count, buf);
	mutex_unlock(&max8998->iolock);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(max8998_bulk_ग_लिखो);

पूर्णांक max8998_update_reg(काष्ठा i2c_client *i2c, u8 reg, u8 val, u8 mask)
अणु
	काष्ठा max8998_dev *max8998 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8998->iolock);
	ret = i2c_smbus_पढ़ो_byte_data(i2c, reg);
	अगर (ret >= 0) अणु
		u8 old_val = ret & 0xff;
		u8 new_val = (val & mask) | (old_val & (~mask));
		ret = i2c_smbus_ग_लिखो_byte_data(i2c, reg, new_val);
	पूर्ण
	mutex_unlock(&max8998->iolock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(max8998_update_reg);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max8998_dt_match[] = अणु
	अणु .compatible = "maxim,max8998", .data = (व्योम *)TYPE_MAX8998 पूर्ण,
	अणु .compatible = "national,lp3974", .data = (व्योम *)TYPE_LP3974 पूर्ण,
	अणु .compatible = "ti,lp3974", .data = (व्योम *)TYPE_LP3974 पूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

/*
 * Only the common platक्रमm data elements क्रम max8998 are parsed here from the
 * device tree. Other sub-modules of max8998 such as pmic, rtc and others have
 * to parse their own platक्रमm data elements from device tree.
 *
 * The max8998 platक्रमm data काष्ठाure is instantiated here and the drivers क्रम
 * the sub-modules need not instantiate another instance जबतक parsing their
 * platक्रमm data.
 */
अटल काष्ठा max8998_platक्रमm_data *max8998_i2c_parse_dt_pdata(
							काष्ठा device *dev)
अणु
	काष्ठा max8998_platक्रमm_data *pd;

	pd = devm_kzalloc(dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस ERR_PTR(-ENOMEM);

	pd->ono = irq_of_parse_and_map(dev->of_node, 1);

	/*
	 * ToDo: the 'wakeup' member in the platक्रमm data is more of a linux
	 * specfic inक्रमmation. Hence, there is no binding क्रम that yet and
	 * not parsed here.
	 */
	वापस pd;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ max8998_i2c_get_driver_data(काष्ठा i2c_client *i2c,
						स्थिर काष्ठा i2c_device_id *id)
अणु
	अगर (IS_ENABLED(CONFIG_OF) && i2c->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;
		match = of_match_node(max8998_dt_match, i2c->dev.of_node);
		वापस (अचिन्हित दीर्घ)match->data;
	पूर्ण

	वापस id->driver_data;
पूर्ण

अटल पूर्णांक max8998_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max8998_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा max8998_dev *max8998;
	पूर्णांक ret = 0;

	max8998 = devm_kzalloc(&i2c->dev, माप(काष्ठा max8998_dev),
				GFP_KERNEL);
	अगर (max8998 == शून्य)
		वापस -ENOMEM;

	अगर (IS_ENABLED(CONFIG_OF) && i2c->dev.of_node) अणु
		pdata = max8998_i2c_parse_dt_pdata(&i2c->dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	i2c_set_clientdata(i2c, max8998);
	max8998->dev = &i2c->dev;
	max8998->i2c = i2c;
	max8998->irq = i2c->irq;
	max8998->type = max8998_i2c_get_driver_data(i2c, id);
	max8998->pdata = pdata;
	अगर (pdata) अणु
		max8998->ono = pdata->ono;
		max8998->irq_base = pdata->irq_base;
		max8998->wakeup = pdata->wakeup;
	पूर्ण
	mutex_init(&max8998->iolock);

	max8998->rtc = i2c_new_dummy_device(i2c->adapter, RTC_I2C_ADDR);
	अगर (IS_ERR(max8998->rtc)) अणु
		dev_err(&i2c->dev, "Failed to allocate I2C device for RTC\n");
		वापस PTR_ERR(max8998->rtc);
	पूर्ण
	i2c_set_clientdata(max8998->rtc, max8998);

	max8998_irq_init(max8998);

	pm_runसमय_set_active(max8998->dev);

	चयन (max8998->type) अणु
	हाल TYPE_LP3974:
		ret = mfd_add_devices(max8998->dev, -1,
				      lp3974_devs, ARRAY_SIZE(lp3974_devs),
				      शून्य, 0, शून्य);
		अवरोध;
	हाल TYPE_MAX8998:
		ret = mfd_add_devices(max8998->dev, -1,
				      max8998_devs, ARRAY_SIZE(max8998_devs),
				      शून्य, 0, शून्य);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret < 0)
		जाओ err;

	device_init_wakeup(max8998->dev, max8998->wakeup);

	वापस ret;

err:
	mfd_हटाओ_devices(max8998->dev);
	max8998_irq_निकास(max8998);
	i2c_unरेजिस्टर_device(max8998->rtc);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max8998_i2c_id[] = अणु
	अणु "max8998", TYPE_MAX8998 पूर्ण,
	अणु "lp3974", TYPE_LP3974पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक max8998_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max8998_dev *max8998 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		irq_set_irq_wake(max8998->irq, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक max8998_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max8998_dev *max8998 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		irq_set_irq_wake(max8998->irq, 0);
	/*
	 * In LP3974, अगर IRQ रेजिस्टरs are not "read & clear"
	 * when it's set during sleep, the पूर्णांकerrupt becomes
	 * disabled.
	 */
	वापस max8998_irq_resume(i2c_get_clientdata(i2c));
पूर्ण

काष्ठा max8998_reg_dump अणु
	u8	addr;
	u8	val;
पूर्ण;
#घोषणा SAVE_ITEM(x)	अणु .addr = (x), .val = 0x0, पूर्ण
अटल काष्ठा max8998_reg_dump max8998_dump[] = अणु
	SAVE_ITEM(MAX8998_REG_IRQM1),
	SAVE_ITEM(MAX8998_REG_IRQM2),
	SAVE_ITEM(MAX8998_REG_IRQM3),
	SAVE_ITEM(MAX8998_REG_IRQM4),
	SAVE_ITEM(MAX8998_REG_STATUSM1),
	SAVE_ITEM(MAX8998_REG_STATUSM2),
	SAVE_ITEM(MAX8998_REG_CHGR1),
	SAVE_ITEM(MAX8998_REG_CHGR2),
	SAVE_ITEM(MAX8998_REG_LDO_ACTIVE_DISCHARGE1),
	SAVE_ITEM(MAX8998_REG_LDO_ACTIVE_DISCHARGE1),
	SAVE_ITEM(MAX8998_REG_BUCK_ACTIVE_DISCHARGE3),
	SAVE_ITEM(MAX8998_REG_ONOFF1),
	SAVE_ITEM(MAX8998_REG_ONOFF2),
	SAVE_ITEM(MAX8998_REG_ONOFF3),
	SAVE_ITEM(MAX8998_REG_ONOFF4),
	SAVE_ITEM(MAX8998_REG_BUCK1_VOLTAGE1),
	SAVE_ITEM(MAX8998_REG_BUCK1_VOLTAGE2),
	SAVE_ITEM(MAX8998_REG_BUCK1_VOLTAGE3),
	SAVE_ITEM(MAX8998_REG_BUCK1_VOLTAGE4),
	SAVE_ITEM(MAX8998_REG_BUCK2_VOLTAGE1),
	SAVE_ITEM(MAX8998_REG_BUCK2_VOLTAGE2),
	SAVE_ITEM(MAX8998_REG_LDO2_LDO3),
	SAVE_ITEM(MAX8998_REG_LDO4),
	SAVE_ITEM(MAX8998_REG_LDO5),
	SAVE_ITEM(MAX8998_REG_LDO6),
	SAVE_ITEM(MAX8998_REG_LDO7),
	SAVE_ITEM(MAX8998_REG_LDO8_LDO9),
	SAVE_ITEM(MAX8998_REG_LDO10_LDO11),
	SAVE_ITEM(MAX8998_REG_LDO12),
	SAVE_ITEM(MAX8998_REG_LDO13),
	SAVE_ITEM(MAX8998_REG_LDO14),
	SAVE_ITEM(MAX8998_REG_LDO15),
	SAVE_ITEM(MAX8998_REG_LDO16),
	SAVE_ITEM(MAX8998_REG_LDO17),
	SAVE_ITEM(MAX8998_REG_BKCHR),
	SAVE_ITEM(MAX8998_REG_LBCNFG1),
	SAVE_ITEM(MAX8998_REG_LBCNFG2),
पूर्ण;
/* Save रेजिस्टरs beक्रमe hibernation */
अटल पूर्णांक max8998_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(max8998_dump); i++)
		max8998_पढ़ो_reg(i2c, max8998_dump[i].addr,
				&max8998_dump[i].val);

	वापस 0;
पूर्ण

/* Restore रेजिस्टरs after hibernation */
अटल पूर्णांक max8998_restore(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(max8998_dump); i++)
		max8998_ग_लिखो_reg(i2c, max8998_dump[i].addr,
				max8998_dump[i].val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops max8998_pm = अणु
	.suspend = max8998_suspend,
	.resume = max8998_resume,
	.मुक्तze = max8998_मुक्तze,
	.restore = max8998_restore,
पूर्ण;

अटल काष्ठा i2c_driver max8998_i2c_driver = अणु
	.driver = अणु
		   .name = "max8998",
		   .pm = &max8998_pm,
		   .suppress_bind_attrs = true,
		   .of_match_table = of_match_ptr(max8998_dt_match),
	पूर्ण,
	.probe = max8998_i2c_probe,
	.id_table = max8998_i2c_id,
पूर्ण;

अटल पूर्णांक __init max8998_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&max8998_i2c_driver);
पूर्ण
/* init early so consumer devices can complete प्रणाली boot */
subsys_initcall(max8998_i2c_init);
