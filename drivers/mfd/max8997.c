<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max8997.c - mfd core driver क्रम the Maxim 8966 and 8997
//
// Copyright (C) 2011 Samsung Electronics
// MyungJoo Ham <myungjoo.ham@samsung.com>
//
// This driver is based on max8998.c

#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max8997.h>
#समावेश <linux/mfd/max8997-निजी.h>

#घोषणा I2C_ADDR_PMIC	(0xCC >> 1)
#घोषणा I2C_ADDR_MUIC	(0x4A >> 1)
#घोषणा I2C_ADDR_BATTERY	(0x6C >> 1)
#घोषणा I2C_ADDR_RTC	(0x0C >> 1)
#घोषणा I2C_ADDR_HAPTIC	(0x90 >> 1)

अटल स्थिर काष्ठा mfd_cell max8997_devs[] = अणु
	अणु .name = "max8997-pmic", पूर्ण,
	अणु .name = "max8997-rtc", पूर्ण,
	अणु .name = "max8997-battery", पूर्ण,
	अणु .name = "max8997-haptic", पूर्ण,
	अणु .name = "max8997-muic", पूर्ण,
	अणु .name = "max8997-led", .id = 1 पूर्ण,
	अणु .name = "max8997-led", .id = 2 पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max8997_pmic_dt_match[] = अणु
	अणु .compatible = "maxim,max8997-pmic", .data = (व्योम *)TYPE_MAX8997 पूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

पूर्णांक max8997_पढ़ो_reg(काष्ठा i2c_client *i2c, u8 reg, u8 *dest)
अणु
	काष्ठा max8997_dev *max8997 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8997->iolock);
	ret = i2c_smbus_पढ़ो_byte_data(i2c, reg);
	mutex_unlock(&max8997->iolock);
	अगर (ret < 0)
		वापस ret;

	ret &= 0xff;
	*dest = ret;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max8997_पढ़ो_reg);

पूर्णांक max8997_bulk_पढ़ो(काष्ठा i2c_client *i2c, u8 reg, पूर्णांक count, u8 *buf)
अणु
	काष्ठा max8997_dev *max8997 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8997->iolock);
	ret = i2c_smbus_पढ़ो_i2c_block_data(i2c, reg, count, buf);
	mutex_unlock(&max8997->iolock);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max8997_bulk_पढ़ो);

पूर्णांक max8997_ग_लिखो_reg(काष्ठा i2c_client *i2c, u8 reg, u8 value)
अणु
	काष्ठा max8997_dev *max8997 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8997->iolock);
	ret = i2c_smbus_ग_लिखो_byte_data(i2c, reg, value);
	mutex_unlock(&max8997->iolock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(max8997_ग_लिखो_reg);

पूर्णांक max8997_bulk_ग_लिखो(काष्ठा i2c_client *i2c, u8 reg, पूर्णांक count, u8 *buf)
अणु
	काष्ठा max8997_dev *max8997 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8997->iolock);
	ret = i2c_smbus_ग_लिखो_i2c_block_data(i2c, reg, count, buf);
	mutex_unlock(&max8997->iolock);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(max8997_bulk_ग_लिखो);

पूर्णांक max8997_update_reg(काष्ठा i2c_client *i2c, u8 reg, u8 val, u8 mask)
अणु
	काष्ठा max8997_dev *max8997 = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	mutex_lock(&max8997->iolock);
	ret = i2c_smbus_पढ़ो_byte_data(i2c, reg);
	अगर (ret >= 0) अणु
		u8 old_val = ret & 0xff;
		u8 new_val = (val & mask) | (old_val & (~mask));
		ret = i2c_smbus_ग_लिखो_byte_data(i2c, reg, new_val);
	पूर्ण
	mutex_unlock(&max8997->iolock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(max8997_update_reg);

/*
 * Only the common platक्रमm data elements क्रम max8997 are parsed here from the
 * device tree. Other sub-modules of max8997 such as pmic, rtc and others have
 * to parse their own platक्रमm data elements from device tree.
 *
 * The max8997 platक्रमm data काष्ठाure is instantiated here and the drivers क्रम
 * the sub-modules need not instantiate another instance जबतक parsing their
 * platक्रमm data.
 */
अटल काष्ठा max8997_platक्रमm_data *max8997_i2c_parse_dt_pdata(
					काष्ठा device *dev)
अणु
	काष्ठा max8997_platक्रमm_data *pd;

	pd = devm_kzalloc(dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस ERR_PTR(-ENOMEM);

	pd->ono = irq_of_parse_and_map(dev->of_node, 1);

	वापस pd;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ max8997_i2c_get_driver_data(काष्ठा i2c_client *i2c,
						स्थिर काष्ठा i2c_device_id *id)
अणु
	अगर (IS_ENABLED(CONFIG_OF) && i2c->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;
		match = of_match_node(max8997_pmic_dt_match, i2c->dev.of_node);
		वापस (अचिन्हित दीर्घ)match->data;
	पूर्ण
	वापस id->driver_data;
पूर्ण

अटल पूर्णांक max8997_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max8997_dev *max8997;
	काष्ठा max8997_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	पूर्णांक ret = 0;

	max8997 = devm_kzalloc(&i2c->dev, माप(काष्ठा max8997_dev),
				GFP_KERNEL);
	अगर (max8997 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, max8997);
	max8997->dev = &i2c->dev;
	max8997->i2c = i2c;
	max8997->type = max8997_i2c_get_driver_data(i2c, id);
	max8997->irq = i2c->irq;

	अगर (IS_ENABLED(CONFIG_OF) && max8997->dev->of_node) अणु
		pdata = max8997_i2c_parse_dt_pdata(max8997->dev);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण

	अगर (!pdata)
		वापस ret;

	max8997->pdata = pdata;
	max8997->ono = pdata->ono;

	mutex_init(&max8997->iolock);

	max8997->rtc = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_RTC);
	अगर (IS_ERR(max8997->rtc)) अणु
		dev_err(max8997->dev, "Failed to allocate I2C device for RTC\n");
		वापस PTR_ERR(max8997->rtc);
	पूर्ण
	i2c_set_clientdata(max8997->rtc, max8997);

	max8997->haptic = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_HAPTIC);
	अगर (IS_ERR(max8997->haptic)) अणु
		dev_err(max8997->dev, "Failed to allocate I2C device for Haptic\n");
		ret = PTR_ERR(max8997->haptic);
		जाओ err_i2c_haptic;
	पूर्ण
	i2c_set_clientdata(max8997->haptic, max8997);

	max8997->muic = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_MUIC);
	अगर (IS_ERR(max8997->muic)) अणु
		dev_err(max8997->dev, "Failed to allocate I2C device for MUIC\n");
		ret = PTR_ERR(max8997->muic);
		जाओ err_i2c_muic;
	पूर्ण
	i2c_set_clientdata(max8997->muic, max8997);

	pm_runसमय_set_active(max8997->dev);

	max8997_irq_init(max8997);

	ret = mfd_add_devices(max8997->dev, -1, max8997_devs,
			ARRAY_SIZE(max8997_devs),
			शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(max8997->dev, "failed to add MFD devices %d\n", ret);
		जाओ err_mfd;
	पूर्ण

	/*
	 * TODO: enable others (flash, muic, rtc, battery, ...) and
	 * check the वापस value
	 */

	/* MAX8997 has a घातer button input. */
	device_init_wakeup(max8997->dev, true);

	वापस ret;

err_mfd:
	mfd_हटाओ_devices(max8997->dev);
	i2c_unरेजिस्टर_device(max8997->muic);
err_i2c_muic:
	i2c_unरेजिस्टर_device(max8997->haptic);
err_i2c_haptic:
	i2c_unरेजिस्टर_device(max8997->rtc);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max8997_i2c_id[] = अणु
	अणु "max8997", TYPE_MAX8997 पूर्ण,
	अणु "max8966", TYPE_MAX8966 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल u8 max8997_dumpaddr_pmic[] = अणु
	MAX8997_REG_INT1MSK,
	MAX8997_REG_INT2MSK,
	MAX8997_REG_INT3MSK,
	MAX8997_REG_INT4MSK,
	MAX8997_REG_MAINCON1,
	MAX8997_REG_MAINCON2,
	MAX8997_REG_BUCKRAMP,
	MAX8997_REG_BUCK1CTRL,
	MAX8997_REG_BUCK1DVS1,
	MAX8997_REG_BUCK1DVS2,
	MAX8997_REG_BUCK1DVS3,
	MAX8997_REG_BUCK1DVS4,
	MAX8997_REG_BUCK1DVS5,
	MAX8997_REG_BUCK1DVS6,
	MAX8997_REG_BUCK1DVS7,
	MAX8997_REG_BUCK1DVS8,
	MAX8997_REG_BUCK2CTRL,
	MAX8997_REG_BUCK2DVS1,
	MAX8997_REG_BUCK2DVS2,
	MAX8997_REG_BUCK2DVS3,
	MAX8997_REG_BUCK2DVS4,
	MAX8997_REG_BUCK2DVS5,
	MAX8997_REG_BUCK2DVS6,
	MAX8997_REG_BUCK2DVS7,
	MAX8997_REG_BUCK2DVS8,
	MAX8997_REG_BUCK3CTRL,
	MAX8997_REG_BUCK3DVS,
	MAX8997_REG_BUCK4CTRL,
	MAX8997_REG_BUCK4DVS,
	MAX8997_REG_BUCK5CTRL,
	MAX8997_REG_BUCK5DVS1,
	MAX8997_REG_BUCK5DVS2,
	MAX8997_REG_BUCK5DVS3,
	MAX8997_REG_BUCK5DVS4,
	MAX8997_REG_BUCK5DVS5,
	MAX8997_REG_BUCK5DVS6,
	MAX8997_REG_BUCK5DVS7,
	MAX8997_REG_BUCK5DVS8,
	MAX8997_REG_BUCK6CTRL,
	MAX8997_REG_BUCK6BPSKIPCTRL,
	MAX8997_REG_BUCK7CTRL,
	MAX8997_REG_BUCK7DVS,
	MAX8997_REG_LDO1CTRL,
	MAX8997_REG_LDO2CTRL,
	MAX8997_REG_LDO3CTRL,
	MAX8997_REG_LDO4CTRL,
	MAX8997_REG_LDO5CTRL,
	MAX8997_REG_LDO6CTRL,
	MAX8997_REG_LDO7CTRL,
	MAX8997_REG_LDO8CTRL,
	MAX8997_REG_LDO9CTRL,
	MAX8997_REG_LDO10CTRL,
	MAX8997_REG_LDO11CTRL,
	MAX8997_REG_LDO12CTRL,
	MAX8997_REG_LDO13CTRL,
	MAX8997_REG_LDO14CTRL,
	MAX8997_REG_LDO15CTRL,
	MAX8997_REG_LDO16CTRL,
	MAX8997_REG_LDO17CTRL,
	MAX8997_REG_LDO18CTRL,
	MAX8997_REG_LDO21CTRL,
	MAX8997_REG_MBCCTRL1,
	MAX8997_REG_MBCCTRL2,
	MAX8997_REG_MBCCTRL3,
	MAX8997_REG_MBCCTRL4,
	MAX8997_REG_MBCCTRL5,
	MAX8997_REG_MBCCTRL6,
	MAX8997_REG_OTPCGHCVS,
	MAX8997_REG_SAFEOUTCTRL,
	MAX8997_REG_LBCNFG1,
	MAX8997_REG_LBCNFG2,
	MAX8997_REG_BBCCTRL,

	MAX8997_REG_FLASH1_CUR,
	MAX8997_REG_FLASH2_CUR,
	MAX8997_REG_MOVIE_CUR,
	MAX8997_REG_GSMB_CUR,
	MAX8997_REG_BOOST_CNTL,
	MAX8997_REG_LEN_CNTL,
	MAX8997_REG_FLASH_CNTL,
	MAX8997_REG_WDT_CNTL,
	MAX8997_REG_MAXFLASH1,
	MAX8997_REG_MAXFLASH2,
	MAX8997_REG_FLASHSTATUSMASK,

	MAX8997_REG_GPIOCNTL1,
	MAX8997_REG_GPIOCNTL2,
	MAX8997_REG_GPIOCNTL3,
	MAX8997_REG_GPIOCNTL4,
	MAX8997_REG_GPIOCNTL5,
	MAX8997_REG_GPIOCNTL6,
	MAX8997_REG_GPIOCNTL7,
	MAX8997_REG_GPIOCNTL8,
	MAX8997_REG_GPIOCNTL9,
	MAX8997_REG_GPIOCNTL10,
	MAX8997_REG_GPIOCNTL11,
	MAX8997_REG_GPIOCNTL12,

	MAX8997_REG_LDO1CONFIG,
	MAX8997_REG_LDO2CONFIG,
	MAX8997_REG_LDO3CONFIG,
	MAX8997_REG_LDO4CONFIG,
	MAX8997_REG_LDO5CONFIG,
	MAX8997_REG_LDO6CONFIG,
	MAX8997_REG_LDO7CONFIG,
	MAX8997_REG_LDO8CONFIG,
	MAX8997_REG_LDO9CONFIG,
	MAX8997_REG_LDO10CONFIG,
	MAX8997_REG_LDO11CONFIG,
	MAX8997_REG_LDO12CONFIG,
	MAX8997_REG_LDO13CONFIG,
	MAX8997_REG_LDO14CONFIG,
	MAX8997_REG_LDO15CONFIG,
	MAX8997_REG_LDO16CONFIG,
	MAX8997_REG_LDO17CONFIG,
	MAX8997_REG_LDO18CONFIG,
	MAX8997_REG_LDO21CONFIG,

	MAX8997_REG_DVSOKTIMER1,
	MAX8997_REG_DVSOKTIMER2,
	MAX8997_REG_DVSOKTIMER4,
	MAX8997_REG_DVSOKTIMER5,
पूर्ण;

अटल u8 max8997_dumpaddr_muic[] = अणु
	MAX8997_MUIC_REG_INTMASK1,
	MAX8997_MUIC_REG_INTMASK2,
	MAX8997_MUIC_REG_INTMASK3,
	MAX8997_MUIC_REG_CDETCTRL,
	MAX8997_MUIC_REG_CONTROL1,
	MAX8997_MUIC_REG_CONTROL2,
	MAX8997_MUIC_REG_CONTROL3,
पूर्ण;

अटल u8 max8997_dumpaddr_haptic[] = अणु
	MAX8997_HAPTIC_REG_CONF1,
	MAX8997_HAPTIC_REG_CONF2,
	MAX8997_HAPTIC_REG_DRVCONF,
	MAX8997_HAPTIC_REG_CYCLECONF1,
	MAX8997_HAPTIC_REG_CYCLECONF2,
	MAX8997_HAPTIC_REG_SIGCONF1,
	MAX8997_HAPTIC_REG_SIGCONF2,
	MAX8997_HAPTIC_REG_SIGCONF3,
	MAX8997_HAPTIC_REG_SIGCONF4,
	MAX8997_HAPTIC_REG_SIGDC1,
	MAX8997_HAPTIC_REG_SIGDC2,
	MAX8997_HAPTIC_REG_SIGPWMDC1,
	MAX8997_HAPTIC_REG_SIGPWMDC2,
	MAX8997_HAPTIC_REG_SIGPWMDC3,
	MAX8997_HAPTIC_REG_SIGPWMDC4,
पूर्ण;

अटल पूर्णांक max8997_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max8997_dev *max8997 = i2c_get_clientdata(i2c);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(max8997_dumpaddr_pmic); i++)
		max8997_पढ़ो_reg(i2c, max8997_dumpaddr_pmic[i],
				&max8997->reg_dump[i]);

	क्रम (i = 0; i < ARRAY_SIZE(max8997_dumpaddr_muic); i++)
		max8997_पढ़ो_reg(i2c, max8997_dumpaddr_muic[i],
				&max8997->reg_dump[i + MAX8997_REG_PMIC_END]);

	क्रम (i = 0; i < ARRAY_SIZE(max8997_dumpaddr_haptic); i++)
		max8997_पढ़ो_reg(i2c, max8997_dumpaddr_haptic[i],
				&max8997->reg_dump[i + MAX8997_REG_PMIC_END +
				MAX8997_MUIC_REG_END]);

	वापस 0;
पूर्ण

अटल पूर्णांक max8997_restore(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max8997_dev *max8997 = i2c_get_clientdata(i2c);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(max8997_dumpaddr_pmic); i++)
		max8997_ग_लिखो_reg(i2c, max8997_dumpaddr_pmic[i],
				max8997->reg_dump[i]);

	क्रम (i = 0; i < ARRAY_SIZE(max8997_dumpaddr_muic); i++)
		max8997_ग_लिखो_reg(i2c, max8997_dumpaddr_muic[i],
				max8997->reg_dump[i + MAX8997_REG_PMIC_END]);

	क्रम (i = 0; i < ARRAY_SIZE(max8997_dumpaddr_haptic); i++)
		max8997_ग_लिखो_reg(i2c, max8997_dumpaddr_haptic[i],
				max8997->reg_dump[i + MAX8997_REG_PMIC_END +
				MAX8997_MUIC_REG_END]);

	वापस 0;
पूर्ण

अटल पूर्णांक max8997_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max8997_dev *max8997 = i2c_get_clientdata(i2c);

	disable_irq(max8997->irq);
	अगर (device_may_wakeup(dev))
		irq_set_irq_wake(max8997->irq, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक max8997_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max8997_dev *max8997 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		irq_set_irq_wake(max8997->irq, 0);
	enable_irq(max8997->irq);
	वापस max8997_irq_resume(max8997);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops max8997_pm = अणु
	.suspend = max8997_suspend,
	.resume = max8997_resume,
	.मुक्तze = max8997_मुक्तze,
	.restore = max8997_restore,
पूर्ण;

अटल काष्ठा i2c_driver max8997_i2c_driver = अणु
	.driver = अणु
		   .name = "max8997",
		   .pm = &max8997_pm,
		   .suppress_bind_attrs = true,
		   .of_match_table = of_match_ptr(max8997_pmic_dt_match),
	पूर्ण,
	.probe = max8997_i2c_probe,
	.id_table = max8997_i2c_id,
पूर्ण;

अटल पूर्णांक __init max8997_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&max8997_i2c_driver);
पूर्ण
/* init early so consumer devices can complete प्रणाली boot */
subsys_initcall(max8997_i2c_init);
