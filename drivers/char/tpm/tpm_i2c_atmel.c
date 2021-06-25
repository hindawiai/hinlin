<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ATMEL I2C TPM AT97SC3204T
 *
 * Copyright (C) 2012 V Lab Technologies
 *  Teddy Reed <teddy@prosauce.org>
 * Copyright (C) 2013, Obsidian Research Corp.
 *  Jason Gunthorpe <jgunthorpe@obsidianresearch.com>
 * Device driver क्रम ATMEL I2C TPMs.
 *
 * Teddy Reed determined the basic I2C command flow, unlike other I2C TPM
 * devices the raw TCG क्रमmatted TPM command data is written via I2C and then
 * raw TCG क्रमmatted TPM command data is वापसed via I2C.
 *
 * TGC status/locality/etc functions seen in the LPC implementation करो not
 * seem to be present.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश "tpm.h"

#घोषणा I2C_DRIVER_NAME "tpm_i2c_atmel"

#घोषणा TPM_I2C_SHORT_TIMEOUT  750     /* ms */
#घोषणा TPM_I2C_LONG_TIMEOUT   2000    /* 2 sec */

#घोषणा ATMEL_STS_OK 1

काष्ठा priv_data अणु
	माप_प्रकार len;
	/* This is the amount we पढ़ो on the first try. 25 was chosen to fit a
	 * fair number of पढ़ो responses in the buffer so a 2nd retry can be
	 * aव्योमed in small message हालs. */
	u8 buffer[माप(काष्ठा tpm_header) + 25];
पूर्ण;

अटल पूर्णांक i2c_aपंचांगel_send(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा priv_data *priv = dev_get_drvdata(&chip->dev);
	काष्ठा i2c_client *client = to_i2c_client(chip->dev.parent);
	s32 status;

	priv->len = 0;

	अगर (len <= 2)
		वापस -EIO;

	status = i2c_master_send(client, buf, len);

	dev_dbg(&chip->dev,
		"%s(buf=%*ph len=%0zx) -> sts=%d\n", __func__,
		(पूर्णांक)min_t(माप_प्रकार, 64, len), buf, len, status);

	अगर (status < 0)
		वापस status;

	/* The upper layer करोes not support incomplete sends. */
	अगर (status != len)
		वापस -E2BIG;

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_aपंचांगel_recv(काष्ठा tpm_chip *chip, u8 *buf, माप_प्रकार count)
अणु
	काष्ठा priv_data *priv = dev_get_drvdata(&chip->dev);
	काष्ठा i2c_client *client = to_i2c_client(chip->dev.parent);
	काष्ठा tpm_header *hdr = (काष्ठा tpm_header *)priv->buffer;
	u32 expected_len;
	पूर्णांक rc;

	अगर (priv->len == 0)
		वापस -EIO;

	/* Get the message size from the message header, अगर we didn't get the
	 * whole message in पढ़ो_status then we need to re-पढ़ो the
	 * message. */
	expected_len = be32_to_cpu(hdr->length);
	अगर (expected_len > count)
		वापस -ENOMEM;

	अगर (priv->len >= expected_len) अणु
		dev_dbg(&chip->dev,
			"%s early(buf=%*ph count=%0zx) -> ret=%d\n", __func__,
			(पूर्णांक)min_t(माप_प्रकार, 64, expected_len), buf, count,
			expected_len);
		स_नकल(buf, priv->buffer, expected_len);
		वापस expected_len;
	पूर्ण

	rc = i2c_master_recv(client, buf, expected_len);
	dev_dbg(&chip->dev,
		"%s reread(buf=%*ph count=%0zx) -> ret=%d\n", __func__,
		(पूर्णांक)min_t(माप_प्रकार, 64, expected_len), buf, count,
		expected_len);
	वापस rc;
पूर्ण

अटल व्योम i2c_aपंचांगel_cancel(काष्ठा tpm_chip *chip)
अणु
	dev_err(&chip->dev, "TPM operation cancellation was requested, but is not supported");
पूर्ण

अटल u8 i2c_aपंचांगel_पढ़ो_status(काष्ठा tpm_chip *chip)
अणु
	काष्ठा priv_data *priv = dev_get_drvdata(&chip->dev);
	काष्ठा i2c_client *client = to_i2c_client(chip->dev.parent);
	पूर्णांक rc;

	/* The TPM fails the I2C पढ़ो until it is पढ़ोy, so we करो the entire
	 * transfer here and buffer it locally. This way the common code can
	 * properly handle the समयouts. */
	priv->len = 0;
	स_रखो(priv->buffer, 0, माप(priv->buffer));


	/* Once the TPM has completed the command the command reमुख्यs पढ़ोable
	 * until another command is issued. */
	rc = i2c_master_recv(client, priv->buffer, माप(priv->buffer));
	dev_dbg(&chip->dev,
		"%s: sts=%d", __func__, rc);
	अगर (rc <= 0)
		वापस 0;

	priv->len = rc;

	वापस ATMEL_STS_OK;
पूर्ण

अटल bool i2c_aपंचांगel_req_canceled(काष्ठा tpm_chip *chip, u8 status)
अणु
	वापस false;
पूर्ण

अटल स्थिर काष्ठा tpm_class_ops i2c_aपंचांगel = अणु
	.flags = TPM_OPS_AUTO_STARTUP,
	.status = i2c_aपंचांगel_पढ़ो_status,
	.recv = i2c_aपंचांगel_recv,
	.send = i2c_aपंचांगel_send,
	.cancel = i2c_aपंचांगel_cancel,
	.req_complete_mask = ATMEL_STS_OK,
	.req_complete_val = ATMEL_STS_OK,
	.req_canceled = i2c_aपंचांगel_req_canceled,
पूर्ण;

अटल पूर्णांक i2c_aपंचांगel_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tpm_chip *chip;
	काष्ठा device *dev = &client->dev;
	काष्ठा priv_data *priv;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	chip = tpmm_chip_alloc(dev, &i2c_aपंचांगel);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	priv = devm_kzalloc(dev, माप(काष्ठा priv_data), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Default समयouts */
	chip->समयout_a = msecs_to_jअगरfies(TPM_I2C_SHORT_TIMEOUT);
	chip->समयout_b = msecs_to_jअगरfies(TPM_I2C_LONG_TIMEOUT);
	chip->समयout_c = msecs_to_jअगरfies(TPM_I2C_SHORT_TIMEOUT);
	chip->समयout_d = msecs_to_jअगरfies(TPM_I2C_SHORT_TIMEOUT);

	dev_set_drvdata(&chip->dev, priv);

	/* There is no known way to probe क्रम this device, and all version
	 * inक्रमmation seems to be पढ़ो via TPM commands. Thus we rely on the
	 * TPM startup process in the common code to detect the device. */

	वापस tpm_chip_रेजिस्टर(chip);
पूर्ण

अटल पूर्णांक i2c_aपंचांगel_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &(client->dev);
	काष्ठा tpm_chip *chip = dev_get_drvdata(dev);
	tpm_chip_unरेजिस्टर(chip);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id i2c_aपंचांगel_id[] = अणु
	अणुI2C_DRIVER_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, i2c_aपंचांगel_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id i2c_aपंचांगel_of_match[] = अणु
	अणु.compatible = "atmel,at97sc3204t"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_aपंचांगel_of_match);
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(i2c_aपंचांगel_pm_ops, tpm_pm_suspend, tpm_pm_resume);

अटल काष्ठा i2c_driver i2c_aपंचांगel_driver = अणु
	.id_table = i2c_aपंचांगel_id,
	.probe = i2c_aपंचांगel_probe,
	.हटाओ = i2c_aपंचांगel_हटाओ,
	.driver = अणु
		.name = I2C_DRIVER_NAME,
		.pm = &i2c_aपंचांगel_pm_ops,
		.of_match_table = of_match_ptr(i2c_aपंचांगel_of_match),
	पूर्ण,
पूर्ण;

module_i2c_driver(i2c_aपंचांगel_driver);

MODULE_AUTHOR("Jason Gunthorpe <jgunthorpe@obsidianresearch.com>");
MODULE_DESCRIPTION("Atmel TPM I2C Driver");
MODULE_LICENSE("GPL");
