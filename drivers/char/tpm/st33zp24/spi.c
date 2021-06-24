<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STMicroelectronics TPM SPI Linux driver क्रम TPM ST33ZP24
 * Copyright (C) 2009 - 2016 STMicroelectronics
 */

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/acpi.h>
#समावेश <linux/tpm.h>
#समावेश <linux/platक्रमm_data/st33zp24.h>

#समावेश "../tpm.h"
#समावेश "st33zp24.h"

#घोषणा TPM_DATA_FIFO           0x24
#घोषणा TPM_INTF_CAPABILITY     0x14

#घोषणा TPM_DUMMY_BYTE		0x00

#घोषणा MAX_SPI_LATENCY		15
#घोषणा LOCALITY0		0

#घोषणा ST33ZP24_OK					0x5A
#घोषणा ST33ZP24_UNDEFINED_ERR				0x80
#घोषणा ST33ZP24_BADLOCALITY				0x81
#घोषणा ST33ZP24_TISREGISTER_UNKNOWN			0x82
#घोषणा ST33ZP24_LOCALITY_NOT_ACTIVATED			0x83
#घोषणा ST33ZP24_HASH_END_BEFORE_HASH_START		0x84
#घोषणा ST33ZP24_BAD_COMMAND_ORDER			0x85
#घोषणा ST33ZP24_INCORECT_RECEIVED_LENGTH		0x86
#घोषणा ST33ZP24_TPM_FIFO_OVERFLOW			0x89
#घोषणा ST33ZP24_UNEXPECTED_READ_FIFO			0x8A
#घोषणा ST33ZP24_UNEXPECTED_WRITE_FIFO			0x8B
#घोषणा ST33ZP24_CMDRDY_SET_WHEN_PROCESSING_HASH_END	0x90
#घोषणा ST33ZP24_DUMMY_BYTES				0x00

/*
 * TPM command can be up to 2048 byte, A TPM response can be up to
 * 1024 byte.
 * Between command and response, there are latency byte (up to 15
 * usually on st33zp24 2 are enough).
 *
 * Overall when sending a command and expecting an answer we need अगर
 * worst हाल:
 * 2048 (क्रम the TPM command) + 1024 (क्रम the TPM answer).  We need
 * some latency byte beक्रमe the answer is available (max 15).
 * We have 2048 + 1024 + 15.
 */
#घोषणा ST33ZP24_SPI_BUFFER_SIZE (ST33ZP24_बफ_मानE + (ST33ZP24_बफ_मानE / 2) +\
				  MAX_SPI_LATENCY)


काष्ठा st33zp24_spi_phy अणु
	काष्ठा spi_device *spi_device;

	u8 tx_buf[ST33ZP24_SPI_BUFFER_SIZE];
	u8 rx_buf[ST33ZP24_SPI_BUFFER_SIZE];

	पूर्णांक io_lpcpd;
	पूर्णांक latency;
पूर्ण;

अटल पूर्णांक st33zp24_status_to_त्रुटि_सं(u8 code)
अणु
	चयन (code) अणु
	हाल ST33ZP24_OK:
		वापस 0;
	हाल ST33ZP24_UNDEFINED_ERR:
	हाल ST33ZP24_BADLOCALITY:
	हाल ST33ZP24_TISREGISTER_UNKNOWN:
	हाल ST33ZP24_LOCALITY_NOT_ACTIVATED:
	हाल ST33ZP24_HASH_END_BEFORE_HASH_START:
	हाल ST33ZP24_BAD_COMMAND_ORDER:
	हाल ST33ZP24_UNEXPECTED_READ_FIFO:
	हाल ST33ZP24_UNEXPECTED_WRITE_FIFO:
	हाल ST33ZP24_CMDRDY_SET_WHEN_PROCESSING_HASH_END:
		वापस -EPROTO;
	हाल ST33ZP24_INCORECT_RECEIVED_LENGTH:
	हाल ST33ZP24_TPM_FIFO_OVERFLOW:
		वापस -EMSGSIZE;
	हाल ST33ZP24_DUMMY_BYTES:
		वापस -ENOSYS;
	पूर्ण
	वापस code;
पूर्ण

/*
 * st33zp24_spi_send
 * Send byte to the TIS रेजिस्टर according to the ST33ZP24 SPI protocol.
 * @param: phy_id, the phy description
 * @param: tpm_रेजिस्टर, the tpm tis रेजिस्टर where the data should be written
 * @param: tpm_data, the tpm_data to ग_लिखो inside the tpm_रेजिस्टर
 * @param: tpm_size, The length of the data
 * @वापस: should be zero अगर success अन्यथा a negative error code.
 */
अटल पूर्णांक st33zp24_spi_send(व्योम *phy_id, u8 tpm_रेजिस्टर, u8 *tpm_data,
			     पूर्णांक tpm_size)
अणु
	पूर्णांक total_length = 0, ret = 0;
	काष्ठा st33zp24_spi_phy *phy = phy_id;
	काष्ठा spi_device *dev = phy->spi_device;
	काष्ठा spi_transfer spi_xfer = अणु
		.tx_buf = phy->tx_buf,
		.rx_buf = phy->rx_buf,
	पूर्ण;

	/* Pre-Header */
	phy->tx_buf[total_length++] = TPM_WRITE_सूचीECTION | LOCALITY0;
	phy->tx_buf[total_length++] = tpm_रेजिस्टर;

	अगर (tpm_size > 0 && tpm_रेजिस्टर == TPM_DATA_FIFO) अणु
		phy->tx_buf[total_length++] = tpm_size >> 8;
		phy->tx_buf[total_length++] = tpm_size;
	पूर्ण

	स_नकल(&phy->tx_buf[total_length], tpm_data, tpm_size);
	total_length += tpm_size;

	स_रखो(&phy->tx_buf[total_length], TPM_DUMMY_BYTE, phy->latency);

	spi_xfer.len = total_length + phy->latency;

	ret = spi_sync_transfer(dev, &spi_xfer, 1);
	अगर (ret == 0)
		ret = phy->rx_buf[total_length + phy->latency - 1];

	वापस st33zp24_status_to_त्रुटि_सं(ret);
पूर्ण /* st33zp24_spi_send() */

/*
 * st33zp24_spi_पढ़ो8_recv
 * Recv byte from the TIS रेजिस्टर according to the ST33ZP24 SPI protocol.
 * @param: phy_id, the phy description
 * @param: tpm_रेजिस्टर, the tpm tis रेजिस्टर where the data should be पढ़ो
 * @param: tpm_data, the TPM response
 * @param: tpm_size, tpm TPM response size to पढ़ो.
 * @वापस: should be zero अगर success अन्यथा a negative error code.
 */
अटल पूर्णांक st33zp24_spi_पढ़ो8_reg(व्योम *phy_id, u8 tpm_रेजिस्टर, u8 *tpm_data,
				  पूर्णांक tpm_size)
अणु
	पूर्णांक total_length = 0, ret;
	काष्ठा st33zp24_spi_phy *phy = phy_id;
	काष्ठा spi_device *dev = phy->spi_device;
	काष्ठा spi_transfer spi_xfer = अणु
		.tx_buf = phy->tx_buf,
		.rx_buf = phy->rx_buf,
	पूर्ण;

	/* Pre-Header */
	phy->tx_buf[total_length++] = LOCALITY0;
	phy->tx_buf[total_length++] = tpm_रेजिस्टर;

	स_रखो(&phy->tx_buf[total_length], TPM_DUMMY_BYTE,
	       phy->latency + tpm_size);

	spi_xfer.len = total_length + phy->latency + tpm_size;

	/* header + status byte + size of the data + status byte */
	ret = spi_sync_transfer(dev, &spi_xfer, 1);
	अगर (tpm_size > 0 && ret == 0) अणु
		ret = phy->rx_buf[total_length + phy->latency - 1];

		स_नकल(tpm_data, phy->rx_buf + total_length + phy->latency,
		       tpm_size);
	पूर्ण

	वापस ret;
पूर्ण /* st33zp24_spi_पढ़ो8_reg() */

/*
 * st33zp24_spi_recv
 * Recv byte from the TIS रेजिस्टर according to the ST33ZP24 SPI protocol.
 * @param: phy_id, the phy description
 * @param: tpm_रेजिस्टर, the tpm tis रेजिस्टर where the data should be पढ़ो
 * @param: tpm_data, the TPM response
 * @param: tpm_size, tpm TPM response size to पढ़ो.
 * @वापस: number of byte पढ़ो successfully: should be one अगर success.
 */
अटल पूर्णांक st33zp24_spi_recv(व्योम *phy_id, u8 tpm_रेजिस्टर, u8 *tpm_data,
			     पूर्णांक tpm_size)
अणु
	पूर्णांक ret;

	ret = st33zp24_spi_पढ़ो8_reg(phy_id, tpm_रेजिस्टर, tpm_data, tpm_size);
	अगर (!st33zp24_status_to_त्रुटि_सं(ret))
		वापस tpm_size;
	वापस ret;
पूर्ण /* st33zp24_spi_recv() */

अटल पूर्णांक st33zp24_spi_evaluate_latency(व्योम *phy_id)
अणु
	काष्ठा st33zp24_spi_phy *phy = phy_id;
	पूर्णांक latency = 1, status = 0;
	u8 data = 0;

	जबतक (!status && latency < MAX_SPI_LATENCY) अणु
		phy->latency = latency;
		status = st33zp24_spi_पढ़ो8_reg(phy_id, TPM_INTF_CAPABILITY,
						&data, 1);
		latency++;
	पूर्ण
	अगर (status < 0)
		वापस status;
	अगर (latency == MAX_SPI_LATENCY)
		वापस -ENODEV;

	वापस latency - 1;
पूर्ण /* evaluate_latency() */

अटल स्थिर काष्ठा st33zp24_phy_ops spi_phy_ops = अणु
	.send = st33zp24_spi_send,
	.recv = st33zp24_spi_recv,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params lpcpd_gpios = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_st33zp24_gpios[] = अणु
	अणु "lpcpd-gpios", &lpcpd_gpios, 1 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक st33zp24_spi_acpi_request_resources(काष्ठा spi_device *spi_dev)
अणु
	काष्ठा tpm_chip *chip = spi_get_drvdata(spi_dev);
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	काष्ठा st33zp24_spi_phy *phy = tpm_dev->phy_id;
	काष्ठा gpio_desc *gpiod_lpcpd;
	काष्ठा device *dev = &spi_dev->dev;
	पूर्णांक ret;

	ret = devm_acpi_dev_add_driver_gpios(dev, acpi_st33zp24_gpios);
	अगर (ret)
		वापस ret;

	/* Get LPCPD GPIO from ACPI */
	gpiod_lpcpd = devm_gpiod_get(dev, "lpcpd", GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpiod_lpcpd)) अणु
		dev_err(dev, "Failed to retrieve lpcpd-gpios from acpi.\n");
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

अटल पूर्णांक st33zp24_spi_of_request_resources(काष्ठा spi_device *spi_dev)
अणु
	काष्ठा tpm_chip *chip = spi_get_drvdata(spi_dev);
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	काष्ठा st33zp24_spi_phy *phy = tpm_dev->phy_id;
	काष्ठा device_node *pp;
	पूर्णांक gpio;
	पूर्णांक ret;

	pp = spi_dev->dev.of_node;
	अगर (!pp) अणु
		dev_err(&spi_dev->dev, "No platform data\n");
		वापस -ENODEV;
	पूर्ण

	/* Get GPIO from device tree */
	gpio = of_get_named_gpio(pp, "lpcpd-gpios", 0);
	अगर (gpio < 0) अणु
		dev_err(&spi_dev->dev,
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
	ret = devm_gpio_request_one(&spi_dev->dev, gpio,
			GPIOF_OUT_INIT_HIGH, "TPM IO LPCPD");
	अगर (ret) अणु
		dev_err(&spi_dev->dev, "Failed to request lpcpd pin\n");
		वापस -ENODEV;
	पूर्ण
	phy->io_lpcpd = gpio;

	वापस 0;
पूर्ण

अटल पूर्णांक st33zp24_spi_request_resources(काष्ठा spi_device *dev)
अणु
	काष्ठा tpm_chip *chip = spi_get_drvdata(dev);
	काष्ठा st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	काष्ठा st33zp24_spi_phy *phy = tpm_dev->phy_id;
	काष्ठा st33zp24_platक्रमm_data *pdata;
	पूर्णांक ret;

	pdata = dev->dev.platक्रमm_data;
	अगर (!pdata) अणु
		dev_err(&dev->dev, "No platform data\n");
		वापस -ENODEV;
	पूर्ण

	/* store क्रम late use */
	phy->io_lpcpd = pdata->io_lpcpd;

	अगर (gpio_is_valid(pdata->io_lpcpd)) अणु
		ret = devm_gpio_request_one(&dev->dev,
				pdata->io_lpcpd, GPIOF_OUT_INIT_HIGH,
				"TPM IO_LPCPD");
		अगर (ret) अणु
			dev_err(&dev->dev, "%s : reset gpio_request failed\n",
				__खाता__);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * st33zp24_spi_probe initialize the TPM device
 * @param: dev, the spi_device description (TPM SPI description).
 * @वापस: 0 in हाल of success.
 *	 or a negative value describing the error.
 */
अटल पूर्णांक st33zp24_spi_probe(काष्ठा spi_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा st33zp24_platक्रमm_data *pdata;
	काष्ठा st33zp24_spi_phy *phy;

	/* Check SPI platक्रमm functionnalities */
	अगर (!dev) अणु
		pr_info("%s: dev is NULL. Device is not accessible.\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	phy = devm_kzalloc(&dev->dev, माप(काष्ठा st33zp24_spi_phy),
			   GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->spi_device = dev;

	pdata = dev->dev.platक्रमm_data;
	अगर (!pdata && dev->dev.of_node) अणु
		ret = st33zp24_spi_of_request_resources(dev);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (pdata) अणु
		ret = st33zp24_spi_request_resources(dev);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (ACPI_HANDLE(&dev->dev)) अणु
		ret = st33zp24_spi_acpi_request_resources(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	phy->latency = st33zp24_spi_evaluate_latency(phy);
	अगर (phy->latency <= 0)
		वापस -ENODEV;

	वापस st33zp24_probe(phy, &spi_phy_ops, &dev->dev, dev->irq,
			      phy->io_lpcpd);
पूर्ण

/*
 * st33zp24_spi_हटाओ हटाओ the TPM device
 * @param: client, the spi_device description (TPM SPI description).
 * @वापस: 0 in हाल of success.
 */
अटल पूर्णांक st33zp24_spi_हटाओ(काष्ठा spi_device *dev)
अणु
	काष्ठा tpm_chip *chip = spi_get_drvdata(dev);
	पूर्णांक ret;

	ret = st33zp24_हटाओ(chip);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id st33zp24_spi_id[] = अणु
	अणुTPM_ST33_SPI, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, st33zp24_spi_id);

अटल स्थिर काष्ठा of_device_id of_st33zp24_spi_match[] = अणु
	अणु .compatible = "st,st33zp24-spi", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_st33zp24_spi_match);

अटल स्थिर काष्ठा acpi_device_id st33zp24_spi_acpi_match[] = अणु
	अणु"SMO3324"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, st33zp24_spi_acpi_match);

अटल SIMPLE_DEV_PM_OPS(st33zp24_spi_ops, st33zp24_pm_suspend,
			 st33zp24_pm_resume);

अटल काष्ठा spi_driver st33zp24_spi_driver = अणु
	.driver = अणु
		.name = TPM_ST33_SPI,
		.pm = &st33zp24_spi_ops,
		.of_match_table = of_match_ptr(of_st33zp24_spi_match),
		.acpi_match_table = ACPI_PTR(st33zp24_spi_acpi_match),
	पूर्ण,
	.probe = st33zp24_spi_probe,
	.हटाओ = st33zp24_spi_हटाओ,
	.id_table = st33zp24_spi_id,
पूर्ण;

module_spi_driver(st33zp24_spi_driver);

MODULE_AUTHOR("TPM support (TPMsupport@list.st.com)");
MODULE_DESCRIPTION("STM TPM 1.2 SPI ST33 Driver");
MODULE_VERSION("1.3.0");
MODULE_LICENSE("GPL");
