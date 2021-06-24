<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common code क्रम Freescale MMA955x Intelligent Sensor Platक्रमm drivers
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश "mma9551_core.h"

/* Command masks क्रम mailbox ग_लिखो command */
#घोषणा MMA9551_CMD_READ_VERSION_INFO	0x00
#घोषणा MMA9551_CMD_READ_CONFIG		0x10
#घोषणा MMA9551_CMD_WRITE_CONFIG	0x20
#घोषणा MMA9551_CMD_READ_STATUS		0x30

/* Mailbox पढ़ो command */
#घोषणा MMA9551_RESPONSE_COCO		BIT(7)

/* Error-Status codes वापसed in mailbox पढ़ो command */
#घोषणा MMA9551_MCI_ERROR_NONE			0x00
#घोषणा MMA9551_MCI_ERROR_PARAM			0x04
#घोषणा MMA9551_MCI_INVALID_COUNT		0x19
#घोषणा MMA9551_MCI_ERROR_COMMAND		0x1C
#घोषणा MMA9551_MCI_ERROR_INVALID_LENGTH	0x21
#घोषणा MMA9551_MCI_ERROR_FIFO_BUSY		0x22
#घोषणा MMA9551_MCI_ERROR_FIFO_ALLOCATED	0x23
#घोषणा MMA9551_MCI_ERROR_FIFO_OVERSIZE		0x24

/* GPIO Application */
#घोषणा MMA9551_GPIO_POL_MSB		0x08
#घोषणा MMA9551_GPIO_POL_LSB		0x09

/* Sleep/Wake application */
#घोषणा MMA9551_SLEEP_CFG		0x06
#घोषणा MMA9551_SLEEP_CFG_SNCEN		BIT(0)
#घोषणा MMA9551_SLEEP_CFG_FLEEN		BIT(1)
#घोषणा MMA9551_SLEEP_CFG_SCHEN		BIT(2)

/* AFE application */
#घोषणा MMA9551_AFE_X_ACCEL_REG		0x00
#घोषणा MMA9551_AFE_Y_ACCEL_REG		0x02
#घोषणा MMA9551_AFE_Z_ACCEL_REG		0x04

/* Reset/Suspend/Clear application */
#घोषणा MMA9551_RSC_RESET		0x00
#घोषणा MMA9551_RSC_OFFSET(mask)	(3 - (ffs(mask) - 1) / 8)
#घोषणा MMA9551_RSC_VAL(mask)		(mask >> (((ffs(mask) - 1) / 8) * 8))

/*
 * A response is composed of:
 * - control रेजिस्टरs: MB0-3
 * - data रेजिस्टरs: MB4-31
 *
 * A request is composed of:
 * - mbox to ग_लिखो to (always 0)
 * - control रेजिस्टरs: MB1-4
 * - data रेजिस्टरs: MB5-31
 */
#घोषणा MMA9551_MAILBOX_CTRL_REGS	4
#घोषणा MMA9551_MAX_MAILBOX_DATA_REGS	28
#घोषणा MMA9551_MAILBOX_REGS		32

#घोषणा MMA9551_I2C_READ_RETRIES	5
#घोषणा MMA9551_I2C_READ_DELAY	50	/* us */

काष्ठा mma9551_mbox_request अणु
	u8 start_mbox;		/* Always 0. */
	u8 app_id;
	/*
	 * See Section 5.3.1 of the MMA955xL Software Reference Manual.
	 *
	 * Bit 7: reserved, always 0
	 * Bits 6-4: command
	 * Bits 3-0: upper bits of रेजिस्टर offset
	 */
	u8 cmd_off;
	u8 lower_off;
	u8 nbytes;
	u8 buf[MMA9551_MAX_MAILBOX_DATA_REGS - 1];
पूर्ण __packed;

काष्ठा mma9551_mbox_response अणु
	u8 app_id;
	/*
	 * See Section 5.3.3 of the MMA955xL Software Reference Manual.
	 *
	 * Bit 7: COCO
	 * Bits 6-0: Error code.
	 */
	u8 coco_err;
	u8 nbytes;
	u8 req_bytes;
	u8 buf[MMA9551_MAX_MAILBOX_DATA_REGS];
पूर्ण __packed;

काष्ठा mma9551_version_info अणु
	__be32 device_id;
	u8 rom_version[2];
	u8 fw_version[2];
	u8 hw_version[2];
	u8 fw_build[2];
पूर्ण;

अटल पूर्णांक mma9551_transfer(काष्ठा i2c_client *client,
			    u8 app_id, u8 command, u16 offset,
			    u8 *inbytes, पूर्णांक num_inbytes,
			    u8 *outbytes, पूर्णांक num_outbytes)
अणु
	काष्ठा mma9551_mbox_request req;
	काष्ठा mma9551_mbox_response rsp;
	काष्ठा i2c_msg in, out;
	u8 req_len, err_code;
	पूर्णांक ret, retries;

	अगर (offset >= 1 << 12) अणु
		dev_err(&client->dev, "register offset too large\n");
		वापस -EINVAL;
	पूर्ण

	req_len = 1 + MMA9551_MAILBOX_CTRL_REGS + num_inbytes;
	req.start_mbox = 0;
	req.app_id = app_id;
	req.cmd_off = command | (offset >> 8);
	req.lower_off = offset;

	अगर (command == MMA9551_CMD_WRITE_CONFIG)
		req.nbytes = num_inbytes;
	अन्यथा
		req.nbytes = num_outbytes;
	अगर (num_inbytes)
		स_नकल(req.buf, inbytes, num_inbytes);

	out.addr = client->addr;
	out.flags = 0;
	out.len = req_len;
	out.buf = (u8 *)&req;

	ret = i2c_transfer(client->adapter, &out, 1);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "i2c write failed\n");
		वापस ret;
	पूर्ण

	retries = MMA9551_I2C_READ_RETRIES;
	करो अणु
		udelay(MMA9551_I2C_READ_DELAY);

		in.addr = client->addr;
		in.flags = I2C_M_RD;
		in.len = माप(rsp);
		in.buf = (u8 *)&rsp;

		ret = i2c_transfer(client->adapter, &in, 1);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "i2c read failed\n");
			वापस ret;
		पूर्ण

		अगर (rsp.coco_err & MMA9551_RESPONSE_COCO)
			अवरोध;
	पूर्ण जबतक (--retries > 0);

	अगर (retries == 0) अणु
		dev_err(&client->dev,
			"timed out while waiting for command response\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (rsp.app_id != app_id) अणु
		dev_err(&client->dev,
			"app_id mismatch in response got %02x expected %02x\n",
			rsp.app_id, app_id);
		वापस -EINVAL;
	पूर्ण

	err_code = rsp.coco_err & ~MMA9551_RESPONSE_COCO;
	अगर (err_code != MMA9551_MCI_ERROR_NONE) अणु
		dev_err(&client->dev, "read returned error %x\n", err_code);
		वापस -EINVAL;
	पूर्ण

	अगर (rsp.nbytes != rsp.req_bytes) अणु
		dev_err(&client->dev,
			"output length mismatch got %d expected %d\n",
			rsp.nbytes, rsp.req_bytes);
		वापस -EINVAL;
	पूर्ण

	अगर (num_outbytes)
		स_नकल(outbytes, rsp.buf, num_outbytes);

	वापस 0;
पूर्ण

/**
 * mma9551_पढ़ो_config_byte() - पढ़ो 1 configuration byte
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @val:	Poपूर्णांकer to store value पढ़ो
 *
 * Read one configuration byte from the device using MMA955xL command क्रमmat.
 * Commands to the MMA955xL platक्रमm consist of a ग_लिखो followed
 * by one or more पढ़ोs.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_पढ़ो_config_byte(काष्ठा i2c_client *client, u8 app_id,
			     u16 reg, u8 *val)
अणु
	वापस mma9551_transfer(client, app_id, MMA9551_CMD_READ_CONFIG,
				reg, शून्य, 0, val, 1);
पूर्ण
EXPORT_SYMBOL(mma9551_पढ़ो_config_byte);

/**
 * mma9551_ग_लिखो_config_byte() - ग_लिखो 1 configuration byte
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @val:	Value to ग_लिखो
 *
 * Write one configuration byte from the device using MMA955xL command क्रमmat.
 * Commands to the MMA955xL platक्रमm consist of a ग_लिखो followed by one or
 * more पढ़ोs.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_ग_लिखो_config_byte(काष्ठा i2c_client *client, u8 app_id,
			      u16 reg, u8 val)
अणु
	वापस mma9551_transfer(client, app_id, MMA9551_CMD_WRITE_CONFIG, reg,
				&val, 1, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(mma9551_ग_लिखो_config_byte);

/**
 * mma9551_पढ़ो_status_byte() - पढ़ो 1 status byte
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @val:	Poपूर्णांकer to store value पढ़ो
 *
 * Read one status byte from the device using MMA955xL command क्रमmat.
 * Commands to the MMA955xL platक्रमm consist of a ग_लिखो followed by one or
 * more पढ़ोs.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_पढ़ो_status_byte(काष्ठा i2c_client *client, u8 app_id,
			     u16 reg, u8 *val)
अणु
	वापस mma9551_transfer(client, app_id, MMA9551_CMD_READ_STATUS,
				reg, शून्य, 0, val, 1);
पूर्ण
EXPORT_SYMBOL(mma9551_पढ़ो_status_byte);

/**
 * mma9551_पढ़ो_config_word() - पढ़ो 1 config word
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @val:	Poपूर्णांकer to store value पढ़ो
 *
 * Read one configuration word from the device using MMA955xL command क्रमmat.
 * Commands to the MMA955xL platक्रमm consist of a ग_लिखो followed by one or
 * more पढ़ोs.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_पढ़ो_config_word(काष्ठा i2c_client *client, u8 app_id,
			     u16 reg, u16 *val)
अणु
	पूर्णांक ret;
	__be16 v;

	ret = mma9551_transfer(client, app_id, MMA9551_CMD_READ_CONFIG,
			       reg, शून्य, 0, (u8 *)&v, 2);
	*val = be16_to_cpu(v);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mma9551_पढ़ो_config_word);

/**
 * mma9551_ग_लिखो_config_word() - ग_लिखो 1 config word
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @val:	Value to ग_लिखो
 *
 * Write one configuration word from the device using MMA955xL command क्रमmat.
 * Commands to the MMA955xL platक्रमm consist of a ग_लिखो followed by one or
 * more पढ़ोs.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_ग_लिखो_config_word(काष्ठा i2c_client *client, u8 app_id,
			      u16 reg, u16 val)
अणु
	__be16 v = cpu_to_be16(val);

	वापस mma9551_transfer(client, app_id, MMA9551_CMD_WRITE_CONFIG, reg,
				(u8 *)&v, 2, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(mma9551_ग_लिखो_config_word);

/**
 * mma9551_पढ़ो_status_word() - पढ़ो 1 status word
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @val:	Poपूर्णांकer to store value पढ़ो
 *
 * Read one status word from the device using MMA955xL command क्रमmat.
 * Commands to the MMA955xL platक्रमm consist of a ग_लिखो followed by one or
 * more पढ़ोs.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_पढ़ो_status_word(काष्ठा i2c_client *client, u8 app_id,
			     u16 reg, u16 *val)
अणु
	पूर्णांक ret;
	__be16 v;

	ret = mma9551_transfer(client, app_id, MMA9551_CMD_READ_STATUS,
			       reg, शून्य, 0, (u8 *)&v, 2);
	*val = be16_to_cpu(v);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mma9551_पढ़ो_status_word);

/**
 * mma9551_पढ़ो_config_words() - पढ़ो multiple config words
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @len:	Length of array to पढ़ो (in words)
 * @buf:	Array of words to पढ़ो
 *
 * Read multiple configuration रेजिस्टरs (word-sized रेजिस्टरs).
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_पढ़ो_config_words(काष्ठा i2c_client *client, u8 app_id,
			      u16 reg, u8 len, u16 *buf)
अणु
	पूर्णांक ret, i;
	__be16 be_buf[MMA9551_MAX_MAILBOX_DATA_REGS / 2];

	अगर (len > ARRAY_SIZE(be_buf)) अणु
		dev_err(&client->dev, "Invalid buffer size %d\n", len);
		वापस -EINVAL;
	पूर्ण

	ret = mma9551_transfer(client, app_id, MMA9551_CMD_READ_CONFIG,
			       reg, शून्य, 0, (u8 *)be_buf, len * माप(u16));
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < len; i++)
		buf[i] = be16_to_cpu(be_buf[i]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mma9551_पढ़ो_config_words);

/**
 * mma9551_पढ़ो_status_words() - पढ़ो multiple status words
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @len:	Length of array to पढ़ो (in words)
 * @buf:	Array of words to पढ़ो
 *
 * Read multiple status रेजिस्टरs (word-sized रेजिस्टरs).
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_पढ़ो_status_words(काष्ठा i2c_client *client, u8 app_id,
			      u16 reg, u8 len, u16 *buf)
अणु
	पूर्णांक ret, i;
	__be16 be_buf[MMA9551_MAX_MAILBOX_DATA_REGS / 2];

	अगर (len > ARRAY_SIZE(be_buf)) अणु
		dev_err(&client->dev, "Invalid buffer size %d\n", len);
		वापस -EINVAL;
	पूर्ण

	ret = mma9551_transfer(client, app_id, MMA9551_CMD_READ_STATUS,
			       reg, शून्य, 0, (u8 *)be_buf, len * माप(u16));
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < len; i++)
		buf[i] = be16_to_cpu(be_buf[i]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mma9551_पढ़ो_status_words);

/**
 * mma9551_ग_लिखो_config_words() - ग_लिखो multiple config words
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @len:	Length of array to ग_लिखो (in words)
 * @buf:	Array of words to ग_लिखो
 *
 * Write multiple configuration रेजिस्टरs (word-sized रेजिस्टरs).
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_ग_लिखो_config_words(काष्ठा i2c_client *client, u8 app_id,
			       u16 reg, u8 len, u16 *buf)
अणु
	पूर्णांक i;
	__be16 be_buf[(MMA9551_MAX_MAILBOX_DATA_REGS - 1) / 2];

	अगर (len > ARRAY_SIZE(be_buf)) अणु
		dev_err(&client->dev, "Invalid buffer size %d\n", len);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < len; i++)
		be_buf[i] = cpu_to_be16(buf[i]);

	वापस mma9551_transfer(client, app_id, MMA9551_CMD_WRITE_CONFIG,
				reg, (u8 *)be_buf, len * माप(u16), शून्य, 0);
पूर्ण
EXPORT_SYMBOL(mma9551_ग_लिखो_config_words);

/**
 * mma9551_update_config_bits() - update bits in रेजिस्टर
 * @client:	I2C client
 * @app_id:	Application ID
 * @reg:	Application रेजिस्टर
 * @mask:	Mask क्रम the bits to update
 * @val:	Value of the bits to update
 *
 * Update bits in the given रेजिस्टर using a bit mask.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_update_config_bits(काष्ठा i2c_client *client, u8 app_id,
			       u16 reg, u8 mask, u8 val)
अणु
	पूर्णांक ret;
	u8 पंचांगp, orig;

	ret = mma9551_पढ़ो_config_byte(client, app_id, reg, &orig);
	अगर (ret < 0)
		वापस ret;

	पंचांगp = orig & ~mask;
	पंचांगp |= val & mask;

	अगर (पंचांगp == orig)
		वापस 0;

	वापस mma9551_ग_लिखो_config_byte(client, app_id, reg, पंचांगp);
पूर्ण
EXPORT_SYMBOL(mma9551_update_config_bits);

/**
 * mma9551_gpio_config() - configure gpio
 * @client:	I2C client
 * @pin:	GPIO pin to configure
 * @app_id:	Application ID
 * @bitnum:	Bit number of status रेजिस्टर being asचिन्हित to the GPIO pin.
 * @polarity:	The polarity parameter is described in section 6.2.2, page 66,
 *		of the Software Reference Manual.  Basically, polarity=0 means
 *		the पूर्णांकerrupt line has the same value as the selected bit,
 *		जबतक polarity=1 means the line is inverted.
 *
 * Assign a bit from an applicationै s status रेजिस्टर to a specअगरic GPIO pin.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_gpio_config(काष्ठा i2c_client *client, क्रमागत mma9551_gpio_pin pin,
			u8 app_id, u8 bitnum, पूर्णांक polarity)
अणु
	u8 reg, pol_mask, pol_val;
	पूर्णांक ret;

	अगर (pin > mma9551_gpio_max) अणु
		dev_err(&client->dev, "bad GPIO pin\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Pin 6 is configured by regs 0x00 and 0x01, pin 7 by 0x02 and
	 * 0x03, and so on.
	 */
	reg = pin * 2;

	ret = mma9551_ग_लिखो_config_byte(client, MMA9551_APPID_GPIO,
					reg, app_id);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "error setting GPIO app_id\n");
		वापस ret;
	पूर्ण

	ret = mma9551_ग_लिखो_config_byte(client, MMA9551_APPID_GPIO,
					reg + 1, bitnum);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "error setting GPIO bit number\n");
		वापस ret;
	पूर्ण

	चयन (pin) अणु
	हाल mma9551_gpio6:
		reg = MMA9551_GPIO_POL_LSB;
		pol_mask = 1 << 6;
		अवरोध;
	हाल mma9551_gpio7:
		reg = MMA9551_GPIO_POL_LSB;
		pol_mask = 1 << 7;
		अवरोध;
	हाल mma9551_gpio8:
		reg = MMA9551_GPIO_POL_MSB;
		pol_mask = 1 << 0;
		अवरोध;
	हाल mma9551_gpio9:
		reg = MMA9551_GPIO_POL_MSB;
		pol_mask = 1 << 1;
		अवरोध;
	पूर्ण
	pol_val = polarity ? pol_mask : 0;

	ret = mma9551_update_config_bits(client, MMA9551_APPID_GPIO, reg,
					 pol_mask, pol_val);
	अगर (ret < 0)
		dev_err(&client->dev, "error setting GPIO polarity\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mma9551_gpio_config);

/**
 * mma9551_पढ़ो_version() - पढ़ो device version inक्रमmation
 * @client:	I2C client
 *
 * Read version inक्रमmation and prपूर्णांक device id and firmware version.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_पढ़ो_version(काष्ठा i2c_client *client)
अणु
	काष्ठा mma9551_version_info info;
	पूर्णांक ret;

	ret = mma9551_transfer(client, MMA9551_APPID_VERSION, 0x00, 0x00,
			       शून्य, 0, (u8 *)&info, माप(info));
	अगर (ret < 0)
		वापस ret;

	dev_info(&client->dev, "device ID 0x%x, firmware version %02x.%02x\n",
		 be32_to_cpu(info.device_id), info.fw_version[0],
		 info.fw_version[1]);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mma9551_पढ़ो_version);

/**
 * mma9551_set_device_state() - sets HW घातer mode
 * @client:	I2C client
 * @enable:	Use true to घातer on device, false to cause the device
 *		to enter sleep.
 *
 * Set घातer on/off क्रम device using the Sleep/Wake Application.
 * When enable is true, घातer on chip and enable करोze mode.
 * When enable is false, enter sleep mode (device reमुख्यs in the
 * lowest-घातer mode).
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_set_device_state(काष्ठा i2c_client *client, bool enable)
अणु
	वापस mma9551_update_config_bits(client, MMA9551_APPID_SLEEP_WAKE,
					  MMA9551_SLEEP_CFG,
					  MMA9551_SLEEP_CFG_SNCEN |
					  MMA9551_SLEEP_CFG_FLEEN |
					  MMA9551_SLEEP_CFG_SCHEN,
					  enable ? MMA9551_SLEEP_CFG_SCHEN |
					  MMA9551_SLEEP_CFG_FLEEN :
					  MMA9551_SLEEP_CFG_SNCEN);
पूर्ण
EXPORT_SYMBOL(mma9551_set_device_state);

/**
 * mma9551_set_घातer_state() - sets runसमय PM state
 * @client:	I2C client
 * @on:		Use true to घातer on device, false to घातer off
 *
 * Resume or suspend the device using Runसमय PM.
 * The device will suspend after the स्वतःsuspend delay.
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_set_घातer_state(काष्ठा i2c_client *client, bool on)
अणु
#अगर_घोषित CONFIG_PM
	पूर्णांक ret;

	अगर (on)
		ret = pm_runसमय_get_sync(&client->dev);
	अन्यथा अणु
		pm_runसमय_mark_last_busy(&client->dev);
		ret = pm_runसमय_put_स्वतःsuspend(&client->dev);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"failed to change power state to %d\n", on);
		अगर (on)
			pm_runसमय_put_noidle(&client->dev);

		वापस ret;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mma9551_set_घातer_state);

/**
 * mma9551_sleep() - sleep
 * @freq:	Application frequency
 *
 * Firmware applications run at a certain frequency on the
 * device. Sleep क्रम one application cycle to make sure the
 * application had समय to run once and initialize set values.
 */
व्योम mma9551_sleep(पूर्णांक freq)
अणु
	पूर्णांक sleep_val = 1000 / freq;

	अगर (sleep_val < 20)
		usleep_range(sleep_val * 1000, 20000);
	अन्यथा
		msleep_पूर्णांकerruptible(sleep_val);
पूर्ण
EXPORT_SYMBOL(mma9551_sleep);

/**
 * mma9551_पढ़ो_accel_chan() - पढ़ो accelerometer channel
 * @client:	I2C client
 * @chan:	IIO channel
 * @val:	Poपूर्णांकer to the accelerometer value पढ़ो
 * @val2:	Unused
 *
 * Read accelerometer value क्रम the specअगरied channel.
 *
 * Locking note: This function must be called with the device lock held.
 * Locking is not handled inside the function. Callers should ensure they
 * serialize access to the HW.
 *
 * Returns: IIO_VAL_INT on success, negative value on failure.
 */
पूर्णांक mma9551_पढ़ो_accel_chan(काष्ठा i2c_client *client,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    पूर्णांक *val, पूर्णांक *val2)
अणु
	u16 reg_addr;
	s16 raw_accel;
	पूर्णांक ret;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_X:
		reg_addr = MMA9551_AFE_X_ACCEL_REG;
		अवरोध;
	हाल IIO_MOD_Y:
		reg_addr = MMA9551_AFE_Y_ACCEL_REG;
		अवरोध;
	हाल IIO_MOD_Z:
		reg_addr = MMA9551_AFE_Z_ACCEL_REG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = mma9551_set_घातer_state(client, true);
	अगर (ret < 0)
		वापस ret;

	ret = mma9551_पढ़ो_status_word(client, MMA9551_APPID_AFE,
				       reg_addr, &raw_accel);
	अगर (ret < 0)
		जाओ out_घातeroff;

	*val = raw_accel;

	ret = IIO_VAL_INT;

out_घातeroff:
	mma9551_set_घातer_state(client, false);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mma9551_पढ़ो_accel_chan);

/**
 * mma9551_पढ़ो_accel_scale() - पढ़ो accelerometer scale
 * @val:	Poपूर्णांकer to the accelerometer scale (पूर्णांक value)
 * @val2:	Poपूर्णांकer to the accelerometer scale (micro value)
 *
 * Read accelerometer scale.
 *
 * Returns: IIO_VAL_INT_PLUS_MICRO.
 */
पूर्णांक mma9551_पढ़ो_accel_scale(पूर्णांक *val, पूर्णांक *val2)
अणु
	*val = 0;
	*val2 = 2440;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण
EXPORT_SYMBOL(mma9551_पढ़ो_accel_scale);

/**
 * mma9551_app_reset() - reset application
 * @client:	I2C client
 * @app_mask:	Application to reset
 *
 * Reset the given application (using the Reset/Suspend/Clear
 * Control Application)
 *
 * Returns: 0 on success, negative value on failure.
 */
पूर्णांक mma9551_app_reset(काष्ठा i2c_client *client, u32 app_mask)
अणु
	वापस mma9551_ग_लिखो_config_byte(client, MMA9551_APPID_RSC,
					 MMA9551_RSC_RESET +
					 MMA9551_RSC_OFFSET(app_mask),
					 MMA9551_RSC_VAL(app_mask));
पूर्ण
EXPORT_SYMBOL(mma9551_app_reset);

MODULE_AUTHOR("Irina Tirdea <irina.tirdea@intel.com>");
MODULE_AUTHOR("Vlad Dogaru <vlad.dogaru@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MMA955xL sensors core");
