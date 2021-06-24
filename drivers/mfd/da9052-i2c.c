<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * I2C access क्रम DA9052 PMICs.
 *
 * Copyright(c) 2011 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/reg.h>

#अगर_घोषित CONFIG_OF
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#पूर्ण_अगर

/* I2C safe रेजिस्टर check */
अटल अंतरभूत bool i2c_safe_reg(अचिन्हित अक्षर reg)
अणु
	चयन (reg) अणु
	हाल DA9052_STATUS_A_REG:
	हाल DA9052_STATUS_B_REG:
	हाल DA9052_STATUS_C_REG:
	हाल DA9052_STATUS_D_REG:
	हाल DA9052_ADC_RES_L_REG:
	हाल DA9052_ADC_RES_H_REG:
	हाल DA9052_VDD_RES_REG:
	हाल DA9052_ICHG_AV_REG:
	हाल DA9052_TBAT_RES_REG:
	हाल DA9052_ADCIN4_RES_REG:
	हाल DA9052_ADCIN5_RES_REG:
	हाल DA9052_ADCIN6_RES_REG:
	हाल DA9052_TJUNC_RES_REG:
	हाल DA9052_TSI_X_MSB_REG:
	हाल DA9052_TSI_Y_MSB_REG:
	हाल DA9052_TSI_LSB_REG:
	हाल DA9052_TSI_Z_MSB_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * There is an issue with DA9052 and DA9053_AA/BA/BB PMIC where the PMIC
 * माला_लो lockup up or fails to respond following a प्रणाली reset.
 * This fix is to follow any पढ़ो or ग_लिखो with a dummy पढ़ो to a safe
 * रेजिस्टर.
 */
अटल पूर्णांक da9052_i2c_fix(काष्ठा da9052 *da9052, अचिन्हित अक्षर reg)
अणु
	पूर्णांक val;

	चयन (da9052->chip_id) अणु
	हाल DA9052:
	हाल DA9053_AA:
	हाल DA9053_BA:
	हाल DA9053_BB:
		/* A dummy पढ़ो to a safe रेजिस्टर address. */
		अगर (!i2c_safe_reg(reg))
			वापस regmap_पढ़ो(da9052->regmap,
					   DA9052_PARK_REGISTER,
					   &val);
		अवरोध;
	हाल DA9053_BC:
	शेष:
		/*
		 * For other chips parking of I2C रेजिस्टर
		 * to a safe place is not required.
		 */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * According to errata item 24, multiग_लिखो mode should be aव्योमed
 * in order to prevent रेजिस्टर data corruption after घातer-करोwn.
 */
अटल पूर्णांक da9052_i2c_disable_multiग_लिखो(काष्ठा da9052 *da9052)
अणु
	पूर्णांक reg_val, ret;

	ret = regmap_पढ़ो(da9052->regmap, DA9052_CONTROL_B_REG, &reg_val);
	अगर (ret < 0)
		वापस ret;

	अगर (!(reg_val & DA9052_CONTROL_B_WRITEMODE)) अणु
		reg_val |= DA9052_CONTROL_B_WRITEMODE;
		ret = regmap_ग_लिखो(da9052->regmap, DA9052_CONTROL_B_REG,
				   reg_val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da9052_i2c_id[] = अणु
	अणु"da9052", DA9052पूर्ण,
	अणु"da9053-aa", DA9053_AAपूर्ण,
	अणु"da9053-ba", DA9053_BAपूर्ण,
	अणु"da9053-bb", DA9053_BBपूर्ण,
	अणु"da9053-bc", DA9053_BCपूर्ण,
	अणुपूर्ण
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id dialog_dt_ids[] = अणु
	अणु .compatible = "dlg,da9052", .data = &da9052_i2c_id[0] पूर्ण,
	अणु .compatible = "dlg,da9053-aa", .data = &da9052_i2c_id[1] पूर्ण,
	अणु .compatible = "dlg,da9053-ba", .data = &da9052_i2c_id[2] पूर्ण,
	अणु .compatible = "dlg,da9053-bb", .data = &da9052_i2c_id[3] पूर्ण,
	अणु .compatible = "dlg,da9053-bc", .data = &da9052_i2c_id[4] पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक da9052_i2c_probe(काष्ठा i2c_client *client,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da9052 *da9052;
	पूर्णांक ret;

	da9052 = devm_kzalloc(&client->dev, माप(काष्ठा da9052), GFP_KERNEL);
	अगर (!da9052)
		वापस -ENOMEM;

	da9052->dev = &client->dev;
	da9052->chip_irq = client->irq;
	da9052->fix_io = da9052_i2c_fix;

	i2c_set_clientdata(client, da9052);

	da9052->regmap = devm_regmap_init_i2c(client, &da9052_regmap_config);
	अगर (IS_ERR(da9052->regmap)) अणु
		ret = PTR_ERR(da9052->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = da9052_i2c_disable_multiग_लिखो(da9052);
	अगर (ret < 0)
		वापस ret;

#अगर_घोषित CONFIG_OF
	अगर (!id) अणु
		काष्ठा device_node *np = client->dev.of_node;
		स्थिर काष्ठा of_device_id *deviceid;

		deviceid = of_match_node(dialog_dt_ids, np);
		id = deviceid->data;
	पूर्ण
#पूर्ण_अगर

	अगर (!id) अणु
		ret = -ENODEV;
		dev_err(&client->dev, "id is null.\n");
		वापस ret;
	पूर्ण

	वापस da9052_device_init(da9052, id->driver_data);
पूर्ण

अटल पूर्णांक da9052_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा da9052 *da9052 = i2c_get_clientdata(client);

	da9052_device_निकास(da9052);
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver da9052_i2c_driver = अणु
	.probe = da9052_i2c_probe,
	.हटाओ = da9052_i2c_हटाओ,
	.id_table = da9052_i2c_id,
	.driver = अणु
		.name = "da9052",
#अगर_घोषित CONFIG_OF
		.of_match_table = dialog_dt_ids,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init da9052_i2c_init(व्योम)
अणु
	पूर्णांक ret;

	ret = i2c_add_driver(&da9052_i2c_driver);
	अगर (ret != 0) अणु
		pr_err("DA9052 I2C registration failed %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(da9052_i2c_init);

अटल व्योम __निकास da9052_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&da9052_i2c_driver);
पूर्ण
module_निकास(da9052_i2c_निकास);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("I2C driver for Dialog DA9052 PMIC");
MODULE_LICENSE("GPL");
