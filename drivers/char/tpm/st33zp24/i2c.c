<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STMicroelectronics TPM I2C Linux driver क्रम TPM ST33ZP24
 * Copyright (C) 2009 - 2016 STMicroelectronics
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/acpi.h>
#समावेश <linux/tpm.h>
#समावेश <linux/platक्रमm_data/st33zp24.h>

#समावेश "../tpm.h"
#समावेश "st33zp24.h"

#घोषणा TPM_DUMMY_BYTE			0xAA

काष्ठा st33zp24_i2c_phy अणु
	काष्ठा i2c_client *client;
	u8 buf[ST33ZP24_बफ_मानE + 1];
	पूर्णांक io_lpcpd;
पूर्ण;

/*
 * ग_लिखो8_reg
 * Send byte to the TIS रेजिस्टर according to the ST33ZP24 I2C protocol.
 * @param: tpm_रेजिस्टर, the tpm tis रेजिस्टर where the data should be written
 * @param: tpm_data, the tpm_data to ग_लिखो inside the tpm_रेजिस्टर
 * @param: tpm_size, The length of the data
 * @वापस: Returns negative त्रुटि_सं, or अन्यथा the number of bytes written.
 */
अटल पूर्णांक ग_लिखो8_reg(व्योम *phy_id, u8 tpm_रेजिस्टर, u8 *tpm_data, पूर्णांक tpm_size)
अणु
	काष्ठा st33zp24_i2c_phy *phy = phy_id;

	phy->buf[0] = tpm_रेजिस्टर;
	स_नकल(phy->buf + 1, tpm_data, tpm_size);
	वापस i2c_master_send(phy->client, phy->buf, tpm_size + 1);
पूर्ण /* ग_लिखो8_reg() */

/*
 * पढ़ो8_reg
 * Recv byte from the TIS रेजिस्टर according to the ST33ZP24 I2C protocol.
 * @param: tpm_रेजिस्टर, the tpm tis रेजिस्टर where the data should be पढ़ो
 * @param: tpm_data, the TPM response
 * @param: tpm_size, tpm TPM response size to पढ़ो.
 * @वापस: number of byte पढ़ो successfully: should be one अगर success.
 */
अटल पूर्णांक पढ़ो8_reg(व्योम *phy_id, u8 tpm_रेजिस्टर, u8 *tpm_data, पूर्णांक tpm_size)
अणु
	काष्ठा st33zp24_i2c_phy *phy = phy_id;
	u8 status = 0;
	u8 data;

	data = TPM_DUMMY_BYTE;
	status = ग_लिखो8_reg(phy, tpm_रेजिस्टर, &data, 1);
	अगर (status == 2)
		status = i2c_master_recv(phy->client, tpm_data, tpm_size);
	वापस status;
पूर्ण /* पढ़ो8_reg() */

/*
 * st33zp24_i2c_send
 * Send byte to the TIS रेजिस्टर according to the ST33ZP24 I2C protocol.
 * @param: phy_id, the phy description
 * @param: tpm_रेजिस्टर, the tpm tis रेजिस्टर where the data should be written
 * @param: tpm_data, the tpm_data to ग_लिखो inside the tpm_रेजिस्टर
 * @param: tpm_size, the length of the data
 * @वापस: number of byte written successfully: should be one अगर success.
 */
अटल पूर्णांक st33zp24_i2c_send(व्योम *phy_id, u8 tpm_रेजिस्टर, u8 *tpm_data,
			     पूर्णांक tpm_size)
अणु
	वापस ग_लिखो8_reg(phy_id, tpm_रेजिस्टर | TPM_WRITE_सूचीECTION, tpm_data,
			  tpm_size);
पूर्ण

/*
 * st33zp24_i2c_recv
 * Recv byte from the TIS रेजिस्टर according to the ST33ZP24 I2C protocol.
 * @param: phy_id, the phy description
 * @param: tpm_रेजिस्टर, the tpm tis रेजिस्टर where the data should be पढ़ो
 * @param: tpm_data, the TPM response
 * @param: tpm_size, tpm TPM response size to पढ़ो.
 * @वापस: number of byte पढ़ो successfully: should be one अगर success.
 */
अटल पूर्णांक st33zp24_i2c_recv(व्योम *phy_id, u8 tpm_रेजिस्टर, u8 *tpm_data,
			     पूर्णांक tpm_size)
अणु
	वापस पढ़ो8_reg(phy_id, tpm_रेजिस्टर, tpm_data, tpm_size);
पूर्ण

अटल स्थिर काष्ठा st33zp24_phy_ops i2c_phy_ops = अणु
	.send = st33zp24_i2c_send,
	.recv = st33zp24_i2c_recv,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params lpcpd_gpios = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_st33zp24_gpios[] = अणु
	अणु "lpcpd-gpios", &lpcpd_gpios, 1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक st33zp24_i2c_acpi_request_resources(काष्ठा i2c_client *client)
अणु
	काष्ठा tpm_chip *chip = i2c_get_clientdata(client);
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	काष्ठा st33zp24_i2c_phy *phy = tpm_dev->phy_id;
	काष्ठा gpio_desc *gpiod_lpcpd;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;

	ret = devm_acpi_dev_add_driver_gpios(dev, acpi_st33zp24_gpios);
	अगर (ret)
		वापस ret;

	/* Get LPCPD GPIO from ACPI */
	gpiod_lpcpd = devm_gpiod_get(dev, "lpcpd", GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpiod_lpcpd)) अणु
		dev_err(&client->dev,
			"Failed to retrieve lpcpd-gpios from acpi.\n");
		phy->io_lpcpd = -1;
		/*
		 * lpcpd pin is not specअगरied. This is not an issue as
		 * घातer management can be also managed by TPM specअगरic
		 * commands. So leave with a success status code.
		 */
		वापस 0;
	पूर्ण

	phy->io_lpcpd = desc_to_gpio(gpiod_lpcpd);

	वापस 0;
पूर्ण

अटल पूर्णांक st33zp24_i2c_of_request_resources(काष्ठा i2c_client *client)
अणु
	काष्ठा tpm_chip *chip = i2c_get_clientdata(client);
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	काष्ठा st33zp24_i2c_phy *phy = tpm_dev->phy_id;
	काष्ठा device_node *pp;
	पूर्णांक gpio;
	पूर्णांक ret;

	pp = client->dev.of_node;
	अगर (!pp) अणु
		dev_err(&client->dev, "No platform data\n");
		वापस -ENODEV;
	पूर्ण

	/* Get GPIO from device tree */
	gpio = of_get_named_gpio(pp, "lpcpd-gpios", 0);
	अगर (gpio < 0) अणु
		dev_err(&client->dev,
			"Failed to retrieve lpcpd-gpios from dts.\n");
		phy->io_lpcpd = -1;
		/*
		 * lpcpd pin is not specअगरied. This is not an issue as
		 * घातer management can be also managed by TPM specअगरic
		 * commands. So leave with a success status code.
		 */
		वापस 0;
	पूर्ण
	/* GPIO request and configuration */
	ret = devm_gpio_request_one(&client->dev, gpio,
			GPIOF_OUT_INIT_HIGH, "TPM IO LPCPD");
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to request lpcpd pin\n");
		वापस -ENODEV;
	पूर्ण
	phy->io_lpcpd = gpio;

	वापस 0;
पूर्ण

अटल पूर्णांक st33zp24_i2c_request_resources(काष्ठा i2c_client *client)
अणु
	काष्ठा tpm_chip *chip = i2c_get_clientdata(client);
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	काष्ठा st33zp24_i2c_phy *phy = tpm_dev->phy_id;
	काष्ठा st33zp24_platक्रमm_data *pdata;
	पूर्णांक ret;

	pdata = client->dev.platक्रमm_data;
	अगर (!pdata) अणु
		dev_err(&client->dev, "No platform data\n");
		वापस -ENODEV;
	पूर्ण

	/* store क्रम late use */
	phy->io_lpcpd = pdata->io_lpcpd;

	अगर (gpio_is_valid(pdata->io_lpcpd)) अणु
		ret = devm_gpio_request_one(&client->dev,
				pdata->io_lpcpd, GPIOF_OUT_INIT_HIGH,
				"TPM IO_LPCPD");
		अगर (ret) अणु
			dev_err(&client->dev, "Failed to request lpcpd pin\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * st33zp24_i2c_probe initialize the TPM device
 * @param: client, the i2c_client description (TPM I2C description).
 * @param: id, the i2c_device_id काष्ठा.
 * @वापस: 0 in हाल of success.
 *	 -1 in other हाल.
 */
अटल पूर्णांक st33zp24_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा st33zp24_platक्रमm_data *pdata;
	काष्ठा st33zp24_i2c_phy *phy;

	अगर (!client) अणु
		pr_info("%s: i2c client is NULL. Device not accessible.\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_info(&client->dev, "client not i2c capable\n");
		वापस -ENODEV;
	पूर्ण

	phy = devm_kzalloc(&client->dev, माप(काष्ठा st33zp24_i2c_phy),
			   GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->client = client;

	pdata = client->dev.platक्रमm_data;
	अगर (!pdata && client->dev.of_node) अणु
		ret = st33zp24_i2c_of_request_resources(client);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (pdata) अणु
		ret = st33zp24_i2c_request_resources(client);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (ACPI_HANDLE(&client->dev)) अणु
		ret = st33zp24_i2c_acpi_request_resources(client);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस st33zp24_probe(phy, &i2c_phy_ops, &client->dev, client->irq,
			      phy->io_lpcpd);
पूर्ण

/*
 * st33zp24_i2c_हटाओ हटाओ the TPM device
 * @param: client, the i2c_client description (TPM I2C description).
 * @वापस: 0 in हाल of success.
 */
अटल पूर्णांक st33zp24_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tpm_chip *chip = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = st33zp24_हटाओ(chip);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id st33zp24_i2c_id[] = अणु
	अणुTPM_ST33_I2C, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, st33zp24_i2c_id);

अटल स्थिर काष्ठा of_device_id of_st33zp24_i2c_match[] = अणु
	अणु .compatible = "st,st33zp24-i2c", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_st33zp24_i2c_match);

अटल स्थिर काष्ठा acpi_device_id st33zp24_i2c_acpi_match[] = अणु
	अणु"SMO3324"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, st33zp24_i2c_acpi_match);

अटल SIMPLE_DEV_PM_OPS(st33zp24_i2c_ops, st33zp24_pm_suspend,
			 st33zp24_pm_resume);

अटल काष्ठा i2c_driver st33zp24_i2c_driver = अणु
	.driver = अणु
		.name = TPM_ST33_I2C,
		.pm = &st33zp24_i2c_ops,
		.of_match_table = of_match_ptr(of_st33zp24_i2c_match),
		.acpi_match_table = ACPI_PTR(st33zp24_i2c_acpi_match),
	पूर्ण,
	.probe = st33zp24_i2c_probe,
	.हटाओ = st33zp24_i2c_हटाओ,
	.id_table = st33zp24_i2c_id
पूर्ण;

module_i2c_driver(st33zp24_i2c_driver);

MODULE_AUTHOR("TPM support (TPMsupport@list.st.com)");
MODULE_DESCRIPTION("STM TPM 1.2 I2C ST33 Driver");
MODULE_VERSION("1.3.0");
MODULE_LICENSE("GPL");
