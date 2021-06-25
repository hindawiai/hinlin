<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Expose an I2C passthrough to the ChromeOS EC.
//
// Copyright (C) 2013 Google, Inc.

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा I2C_MAX_RETRIES 3

/**
 * काष्ठा ec_i2c_device - Driver data क्रम I2C tunnel
 *
 * @dev: Device node
 * @adap: I2C adapter
 * @ec: Poपूर्णांकer to EC device
 * @remote_bus: The EC bus number we tunnel to on the other side.
 * @request_buf: Buffer क्रम transmitting data; we expect most transfers to fit.
 * @response_buf: Buffer क्रम receiving data; we expect most transfers to fit.
 */

काष्ठा ec_i2c_device अणु
	काष्ठा device *dev;
	काष्ठा i2c_adapter adap;
	काष्ठा cros_ec_device *ec;

	u16 remote_bus;

	u8 request_buf[256];
	u8 response_buf[256];
पूर्ण;

/**
 * ec_i2c_count_message - Count bytes needed क्रम ec_i2c_स्थिरruct_message
 *
 * @i2c_msgs: The i2c messages to पढ़ो
 * @num: The number of i2c messages.
 *
 * Returns the number of bytes the messages will take up.
 */
अटल पूर्णांक ec_i2c_count_message(स्थिर काष्ठा i2c_msg i2c_msgs[], पूर्णांक num)
अणु
	पूर्णांक i;
	पूर्णांक size;

	size = माप(काष्ठा ec_params_i2c_passthru);
	size += num * माप(काष्ठा ec_params_i2c_passthru_msg);
	क्रम (i = 0; i < num; i++)
		अगर (!(i2c_msgs[i].flags & I2C_M_RD))
			size += i2c_msgs[i].len;

	वापस size;
पूर्ण

/**
 * ec_i2c_स्थिरruct_message - स्थिरruct a message to go to the EC
 *
 * This function effectively stuffs the standard i2c_msg क्रमmat of Linux पूर्णांकo
 * a क्रमmat that the EC understands.
 *
 * @buf: The buffer to fill.  We assume that the buffer is big enough.
 * @i2c_msgs: The i2c messages to पढ़ो.
 * @num: The number of i2c messages.
 * @bus_num: The remote bus number we want to talk to.
 *
 * Returns 0 or a negative error number.
 */
अटल पूर्णांक ec_i2c_स्थिरruct_message(u8 *buf, स्थिर काष्ठा i2c_msg i2c_msgs[],
				    पूर्णांक num, u16 bus_num)
अणु
	काष्ठा ec_params_i2c_passthru *params;
	u8 *out_data;
	पूर्णांक i;

	out_data = buf + माप(काष्ठा ec_params_i2c_passthru) +
		   num * माप(काष्ठा ec_params_i2c_passthru_msg);

	params = (काष्ठा ec_params_i2c_passthru *)buf;
	params->port = bus_num;
	params->num_msgs = num;
	क्रम (i = 0; i < num; i++) अणु
		स्थिर काष्ठा i2c_msg *i2c_msg = &i2c_msgs[i];
		काष्ठा ec_params_i2c_passthru_msg *msg = &params->msg[i];

		msg->len = i2c_msg->len;
		msg->addr_flags = i2c_msg->addr;

		अगर (i2c_msg->flags & I2C_M_TEN)
			वापस -EINVAL;

		अगर (i2c_msg->flags & I2C_M_RD) अणु
			msg->addr_flags |= EC_I2C_FLAG_READ;
		पूर्ण अन्यथा अणु
			स_नकल(out_data, i2c_msg->buf, msg->len);
			out_data += msg->len;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ec_i2c_count_response - Count bytes needed क्रम ec_i2c_parse_response
 *
 * @i2c_msgs: The i2c messages to to fill up.
 * @num: The number of i2c messages expected.
 *
 * Returns the number of response bytes expeced.
 */
अटल पूर्णांक ec_i2c_count_response(काष्ठा i2c_msg i2c_msgs[], पूर्णांक num)
अणु
	पूर्णांक size;
	पूर्णांक i;

	size = माप(काष्ठा ec_response_i2c_passthru);
	क्रम (i = 0; i < num; i++)
		अगर (i2c_msgs[i].flags & I2C_M_RD)
			size += i2c_msgs[i].len;

	वापस size;
पूर्ण

/**
 * ec_i2c_parse_response - Parse a response from the EC
 *
 * We'll take the EC's response and copy it back पूर्णांकo msgs.
 *
 * @buf: The buffer to parse.
 * @i2c_msgs: The i2c messages to to fill up.
 * @num: The number of i2c messages; will be modअगरied to include the actual
 *	 number received.
 *
 * Returns 0 or a negative error number.
 */
अटल पूर्णांक ec_i2c_parse_response(स्थिर u8 *buf, काष्ठा i2c_msg i2c_msgs[],
				 पूर्णांक *num)
अणु
	स्थिर काष्ठा ec_response_i2c_passthru *resp;
	स्थिर u8 *in_data;
	पूर्णांक i;

	in_data = buf + माप(काष्ठा ec_response_i2c_passthru);

	resp = (स्थिर काष्ठा ec_response_i2c_passthru *)buf;
	अगर (resp->i2c_status & EC_I2C_STATUS_TIMEOUT)
		वापस -ETIMEDOUT;
	अन्यथा अगर (resp->i2c_status & EC_I2C_STATUS_NAK)
		वापस -ENXIO;
	अन्यथा अगर (resp->i2c_status & EC_I2C_STATUS_ERROR)
		वापस -EIO;

	/* Other side could send us back fewer messages, but not more */
	अगर (resp->num_msgs > *num)
		वापस -EPROTO;
	*num = resp->num_msgs;

	क्रम (i = 0; i < *num; i++) अणु
		काष्ठा i2c_msg *i2c_msg = &i2c_msgs[i];

		अगर (i2c_msgs[i].flags & I2C_M_RD) अणु
			स_नकल(i2c_msg->buf, in_data, i2c_msg->len);
			in_data += i2c_msg->len;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ec_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg i2c_msgs[],
		       पूर्णांक num)
अणु
	काष्ठा ec_i2c_device *bus = adap->algo_data;
	काष्ठा device *dev = bus->dev;
	स्थिर u16 bus_num = bus->remote_bus;
	पूर्णांक request_len;
	पूर्णांक response_len;
	पूर्णांक alloc_size;
	पूर्णांक result;
	काष्ठा cros_ec_command *msg;

	request_len = ec_i2c_count_message(i2c_msgs, num);
	अगर (request_len < 0) अणु
		dev_warn(dev, "Error constructing message %d\n", request_len);
		वापस request_len;
	पूर्ण

	response_len = ec_i2c_count_response(i2c_msgs, num);
	अगर (response_len < 0) अणु
		/* Unexpected; no errors should come when शून्य response */
		dev_warn(dev, "Error preparing response %d\n", response_len);
		वापस response_len;
	पूर्ण

	alloc_size = max(request_len, response_len);
	msg = kदो_स्मृति(माप(*msg) + alloc_size, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	result = ec_i2c_स्थिरruct_message(msg->data, i2c_msgs, num, bus_num);
	अगर (result) अणु
		dev_err(dev, "Error constructing EC i2c message %d\n", result);
		जाओ निकास;
	पूर्ण

	msg->version = 0;
	msg->command = EC_CMD_I2C_PASSTHRU;
	msg->outsize = request_len;
	msg->insize = response_len;

	result = cros_ec_cmd_xfer_status(bus->ec, msg);
	अगर (result < 0) अणु
		dev_err(dev, "Error transferring EC i2c message %d\n", result);
		जाओ निकास;
	पूर्ण

	result = ec_i2c_parse_response(msg->data, i2c_msgs, &num);
	अगर (result < 0)
		जाओ निकास;

	/* Indicate success by saying how many messages were sent */
	result = num;
निकास:
	kमुक्त(msg);
	वापस result;
पूर्ण

अटल u32 ec_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm ec_i2c_algorithm = अणु
	.master_xfer	= ec_i2c_xfer,
	.functionality	= ec_i2c_functionality,
पूर्ण;

अटल पूर्णांक ec_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ec_i2c_device *bus = शून्य;
	u32 remote_bus;
	पूर्णांक err;

	अगर (!ec->cmd_xfer) अणु
		dev_err(dev, "Missing sendrecv\n");
		वापस -EINVAL;
	पूर्ण

	bus = devm_kzalloc(dev, माप(*bus), GFP_KERNEL);
	अगर (bus == शून्य)
		वापस -ENOMEM;

	err = device_property_पढ़ो_u32(dev, "google,remote-bus", &remote_bus);
	अगर (err) अणु
		dev_err(dev, "Couldn't read remote-bus property\n");
		वापस err;
	पूर्ण
	bus->remote_bus = remote_bus;

	bus->ec = ec;
	bus->dev = dev;

	bus->adap.owner = THIS_MODULE;
	strlcpy(bus->adap.name, "cros-ec-i2c-tunnel", माप(bus->adap.name));
	bus->adap.algo = &ec_i2c_algorithm;
	bus->adap.algo_data = bus;
	bus->adap.dev.parent = &pdev->dev;
	bus->adap.dev.of_node = pdev->dev.of_node;
	bus->adap.retries = I2C_MAX_RETRIES;
	ACPI_COMPANION_SET(&bus->adap.dev, ACPI_COMPANION(&pdev->dev));

	err = i2c_add_adapter(&bus->adap);
	अगर (err)
		वापस err;
	platक्रमm_set_drvdata(pdev, bus);

	वापस err;
पूर्ण

अटल पूर्णांक ec_i2c_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ec_i2c_device *bus = platक्रमm_get_drvdata(dev);

	i2c_del_adapter(&bus->adap);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cros_ec_i2c_of_match[] = अणु
	अणु .compatible = "google,cros-ec-i2c-tunnel" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cros_ec_i2c_of_match);

अटल स्थिर काष्ठा acpi_device_id cros_ec_i2c_tunnel_acpi_id[] = अणु
	अणु "GOOG0012", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cros_ec_i2c_tunnel_acpi_id);

अटल काष्ठा platक्रमm_driver ec_i2c_tunnel_driver = अणु
	.probe = ec_i2c_probe,
	.हटाओ = ec_i2c_हटाओ,
	.driver = अणु
		.name = "cros-ec-i2c-tunnel",
		.acpi_match_table = ACPI_PTR(cros_ec_i2c_tunnel_acpi_id),
		.of_match_table = of_match_ptr(cros_ec_i2c_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ec_i2c_tunnel_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("EC I2C tunnel driver");
MODULE_ALIAS("platform:cros-ec-i2c-tunnel");
