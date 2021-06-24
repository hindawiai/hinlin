<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* NXP PCF50633 Power Management Unit (PMU) driver
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Author: Harald Welte <laक्रमge@खोलोmoko.org>
 * 	   Balaji Rao <balajirrao@खोलोmoko.org>
 * All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/err.h>

#समावेश <linux/mfd/pcf50633/core.h>

/* Read a block of up to 32 regs  */
पूर्णांक pcf50633_पढ़ो_block(काष्ठा pcf50633 *pcf, u8 reg,
					पूर्णांक nr_regs, u8 *data)
अणु
	पूर्णांक ret;

	ret = regmap_raw_पढ़ो(pcf->regmap, reg, data, nr_regs);
	अगर (ret != 0)
		वापस ret;

	वापस nr_regs;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_पढ़ो_block);

/* Write a block of up to 32 regs  */
पूर्णांक pcf50633_ग_लिखो_block(काष्ठा pcf50633 *pcf , u8 reg,
					पूर्णांक nr_regs, u8 *data)
अणु
	वापस regmap_raw_ग_लिखो(pcf->regmap, reg, data, nr_regs);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_ग_लिखो_block);

u8 pcf50633_reg_पढ़ो(काष्ठा pcf50633 *pcf, u8 reg)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pcf->regmap, reg, &val);
	अगर (ret < 0)
		वापस -1;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_reg_पढ़ो);

पूर्णांक pcf50633_reg_ग_लिखो(काष्ठा pcf50633 *pcf, u8 reg, u8 val)
अणु
	वापस regmap_ग_लिखो(pcf->regmap, reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_reg_ग_लिखो);

पूर्णांक pcf50633_reg_set_bit_mask(काष्ठा pcf50633 *pcf, u8 reg, u8 mask, u8 val)
अणु
	वापस regmap_update_bits(pcf->regmap, reg, mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_reg_set_bit_mask);

पूर्णांक pcf50633_reg_clear_bits(काष्ठा pcf50633 *pcf, u8 reg, u8 val)
अणु
	वापस regmap_update_bits(pcf->regmap, reg, val, 0);
पूर्ण
EXPORT_SYMBOL_GPL(pcf50633_reg_clear_bits);

/* sysfs attributes */
अटल sमाप_प्रकार show_dump_regs(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा pcf50633 *pcf = dev_get_drvdata(dev);
	u8 dump[16];
	पूर्णांक n, n1, idx = 0;
	अक्षर *buf1 = buf;
	अटल u8 address_no_पढ़ो[] = अणु /* must be ascending */
		PCF50633_REG_INT1,
		PCF50633_REG_INT2,
		PCF50633_REG_INT3,
		PCF50633_REG_INT4,
		PCF50633_REG_INT5,
		0 /* terminator */
	पूर्ण;

	क्रम (n = 0; n < 256; n += माप(dump)) अणु
		क्रम (n1 = 0; n1 < माप(dump); n1++)
			अगर (n == address_no_पढ़ो[idx]) अणु
				idx++;
				dump[n1] = 0x00;
			पूर्ण अन्यथा
				dump[n1] = pcf50633_reg_पढ़ो(pcf, n + n1);

		buf1 += प्र_लिखो(buf1, "%*ph\n", (पूर्णांक)माप(dump), dump);
	पूर्ण

	वापस buf1 - buf;
पूर्ण
अटल DEVICE_ATTR(dump_regs, 0400, show_dump_regs, शून्य);

अटल sमाप_प्रकार show_resume_reason(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcf50633 *pcf = dev_get_drvdata(dev);
	पूर्णांक n;

	n = प्र_लिखो(buf, "%02x%02x%02x%02x%02x\n",
				pcf->resume_reason[0],
				pcf->resume_reason[1],
				pcf->resume_reason[2],
				pcf->resume_reason[3],
				pcf->resume_reason[4]);

	वापस n;
पूर्ण
अटल DEVICE_ATTR(resume_reason, 0400, show_resume_reason, शून्य);

अटल काष्ठा attribute *pcf_sysfs_entries[] = अणु
	&dev_attr_dump_regs.attr,
	&dev_attr_resume_reason.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group pcf_attr_group = अणु
	.name	= शून्य,			/* put in device directory */
	.attrs	= pcf_sysfs_entries,
पूर्ण;

अटल व्योम
pcf50633_client_dev_रेजिस्टर(काष्ठा pcf50633 *pcf, स्थिर अक्षर *name,
						काष्ठा platक्रमm_device **pdev)
अणु
	पूर्णांक ret;

	*pdev = platक्रमm_device_alloc(name, -1);
	अगर (!*pdev) अणु
		dev_err(pcf->dev, "Failed to allocate %s\n", name);
		वापस;
	पूर्ण

	(*pdev)->dev.parent = pcf->dev;

	ret = platक्रमm_device_add(*pdev);
	अगर (ret) अणु
		dev_err(pcf->dev, "Failed to register %s: %d\n", name, ret);
		platक्रमm_device_put(*pdev);
		*pdev = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pcf50633_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pcf50633 *pcf = i2c_get_clientdata(client);

	वापस pcf50633_irq_suspend(pcf);
पूर्ण

अटल पूर्णांक pcf50633_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pcf50633 *pcf = i2c_get_clientdata(client);

	वापस pcf50633_irq_resume(pcf);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pcf50633_pm, pcf50633_suspend, pcf50633_resume);

अटल स्थिर काष्ठा regmap_config pcf50633_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक pcf50633_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *ids)
अणु
	काष्ठा pcf50633 *pcf;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा pcf50633_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	पूर्णांक i, j, ret;
	पूर्णांक version, variant;

	अगर (!client->irq) अणु
		dev_err(&client->dev, "Missing IRQ\n");
		वापस -ENOENT;
	पूर्ण

	pcf = devm_kzalloc(&client->dev, माप(*pcf), GFP_KERNEL);
	अगर (!pcf)
		वापस -ENOMEM;

	i2c_set_clientdata(client, pcf);
	pcf->dev = &client->dev;
	pcf->pdata = pdata;

	mutex_init(&pcf->lock);

	pcf->regmap = devm_regmap_init_i2c(client, &pcf50633_regmap_config);
	अगर (IS_ERR(pcf->regmap)) अणु
		ret = PTR_ERR(pcf->regmap);
		dev_err(pcf->dev, "Failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	version = pcf50633_reg_पढ़ो(pcf, 0);
	variant = pcf50633_reg_पढ़ो(pcf, 1);
	अगर (version < 0 || variant < 0) अणु
		dev_err(pcf->dev, "Unable to probe pcf50633\n");
		ret = -ENODEV;
		वापस ret;
	पूर्ण

	dev_info(pcf->dev, "Probed device version %d variant %d\n",
							version, variant);

	pcf50633_irq_init(pcf, client->irq);

	/* Create sub devices */
	pcf50633_client_dev_रेजिस्टर(pcf, "pcf50633-input", &pcf->input_pdev);
	pcf50633_client_dev_रेजिस्टर(pcf, "pcf50633-rtc", &pcf->rtc_pdev);
	pcf50633_client_dev_रेजिस्टर(pcf, "pcf50633-mbc", &pcf->mbc_pdev);
	pcf50633_client_dev_रेजिस्टर(pcf, "pcf50633-adc", &pcf->adc_pdev);
	pcf50633_client_dev_रेजिस्टर(pcf, "pcf50633-backlight", &pcf->bl_pdev);


	क्रम (i = 0; i < PCF50633_NUM_REGULATORS; i++) अणु
		pdev = platक्रमm_device_alloc("pcf50633-regulator", i);
		अगर (!pdev) अणु
			ret = -ENOMEM;
			जाओ err2;
		पूर्ण

		pdev->dev.parent = pcf->dev;
		ret = platक्रमm_device_add_data(pdev, &pdata->reg_init_data[i],
					       माप(pdata->reg_init_data[i]));
		अगर (ret)
			जाओ err;

		ret = platक्रमm_device_add(pdev);
		अगर (ret)
			जाओ err;

		pcf->regulator_pdev[i] = pdev;
	पूर्ण

	ret = sysfs_create_group(&client->dev.kobj, &pcf_attr_group);
	अगर (ret)
		dev_warn(pcf->dev, "error creating sysfs entries\n");

	अगर (pdata->probe_करोne)
		pdata->probe_करोne(pcf);

	वापस 0;

err:
	platक्रमm_device_put(pdev);
err2:
	क्रम (j = 0; j < i; j++)
		platक्रमm_device_put(pcf->regulator_pdev[j]);

	वापस ret;
पूर्ण

अटल पूर्णांक pcf50633_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pcf50633 *pcf = i2c_get_clientdata(client);
	पूर्णांक i;

	sysfs_हटाओ_group(&client->dev.kobj, &pcf_attr_group);
	pcf50633_irq_मुक्त(pcf);

	platक्रमm_device_unरेजिस्टर(pcf->input_pdev);
	platक्रमm_device_unरेजिस्टर(pcf->rtc_pdev);
	platक्रमm_device_unरेजिस्टर(pcf->mbc_pdev);
	platक्रमm_device_unरेजिस्टर(pcf->adc_pdev);
	platक्रमm_device_unरेजिस्टर(pcf->bl_pdev);

	क्रम (i = 0; i < PCF50633_NUM_REGULATORS; i++)
		platक्रमm_device_unरेजिस्टर(pcf->regulator_pdev[i]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcf50633_id_table[] = अणु
	अणु"pcf50633", 0x73पूर्ण,
	अणु/* end of list */पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcf50633_id_table);

अटल काष्ठा i2c_driver pcf50633_driver = अणु
	.driver = अणु
		.name	= "pcf50633",
		.pm	= &pcf50633_pm,
	पूर्ण,
	.id_table = pcf50633_id_table,
	.probe = pcf50633_probe,
	.हटाओ = pcf50633_हटाओ,
पूर्ण;

अटल पूर्णांक __init pcf50633_init(व्योम)
अणु
	वापस i2c_add_driver(&pcf50633_driver);
पूर्ण

अटल व्योम __निकास pcf50633_निकास(व्योम)
अणु
	i2c_del_driver(&pcf50633_driver);
पूर्ण

MODULE_DESCRIPTION("I2C chip driver for NXP PCF50633 PMU");
MODULE_AUTHOR("Harald Welte <laforge@openmoko.org>");
MODULE_LICENSE("GPL");

subsys_initcall(pcf50633_init);
module_निकास(pcf50633_निकास);
