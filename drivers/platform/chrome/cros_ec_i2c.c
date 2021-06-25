<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// I2C पूर्णांकerface क्रम ChromeOS Embedded Controller
//
// Copyright (C) 2012 Google, Inc

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "cros_ec.h"

/*
 * Request क्रमmat क्रम protocol v3
 * byte 0	0xda (EC_COMMAND_PROTOCOL_3)
 * byte 1-8	काष्ठा ec_host_request
 * byte 10-	response data
 */
काष्ठा ec_host_request_i2c अणु
	/* Always 0xda to backward compatible with v2 काष्ठा */
	uपूर्णांक8_t  command_protocol;
	काष्ठा ec_host_request ec_request;
पूर्ण __packed;


/*
 * Response क्रमmat क्रम protocol v3
 * byte 0	result code
 * byte 1	packet_length
 * byte 2-9	काष्ठा ec_host_response
 * byte 10-	response data
 */
काष्ठा ec_host_response_i2c अणु
	uपूर्णांक8_t result;
	uपूर्णांक8_t packet_length;
	काष्ठा ec_host_response ec_response;
पूर्ण __packed;

अटल अंतरभूत काष्ठा cros_ec_device *to_ec_dev(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस i2c_get_clientdata(client);
पूर्ण

अटल पूर्णांक cros_ec_pkt_xfer_i2c(काष्ठा cros_ec_device *ec_dev,
				काष्ठा cros_ec_command *msg)
अणु
	काष्ठा i2c_client *client = ec_dev->priv;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i;
	पूर्णांक packet_len;
	u8 *out_buf = शून्य;
	u8 *in_buf = शून्य;
	u8 sum;
	काष्ठा i2c_msg i2c_msg[2];
	काष्ठा ec_host_response *ec_response;
	काष्ठा ec_host_request_i2c *ec_request_i2c;
	काष्ठा ec_host_response_i2c *ec_response_i2c;
	पूर्णांक request_header_size = माप(काष्ठा ec_host_request_i2c);
	पूर्णांक response_header_size = माप(काष्ठा ec_host_response_i2c);

	i2c_msg[0].addr = client->addr;
	i2c_msg[0].flags = 0;
	i2c_msg[1].addr = client->addr;
	i2c_msg[1].flags = I2C_M_RD;

	packet_len = msg->insize + response_header_size;
	BUG_ON(packet_len > ec_dev->din_size);
	in_buf = ec_dev->din;
	i2c_msg[1].len = packet_len;
	i2c_msg[1].buf = (अक्षर *) in_buf;

	packet_len = msg->outsize + request_header_size;
	BUG_ON(packet_len > ec_dev->करोut_size);
	out_buf = ec_dev->करोut;
	i2c_msg[0].len = packet_len;
	i2c_msg[0].buf = (अक्षर *) out_buf;

	/* create request data */
	ec_request_i2c = (काष्ठा ec_host_request_i2c *) out_buf;
	ec_request_i2c->command_protocol = EC_COMMAND_PROTOCOL_3;

	ec_dev->करोut++;
	ret = cros_ec_prepare_tx(ec_dev, msg);
	ec_dev->करोut--;

	/* send command to EC and पढ़ो answer */
	ret = i2c_transfer(client->adapter, i2c_msg, 2);
	अगर (ret < 0) अणु
		dev_dbg(ec_dev->dev, "i2c transfer failed: %d\n", ret);
		जाओ करोne;
	पूर्ण अन्यथा अगर (ret != 2) अणु
		dev_err(ec_dev->dev, "failed to get response: %d\n", ret);
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	ec_response_i2c = (काष्ठा ec_host_response_i2c *) in_buf;
	msg->result = ec_response_i2c->result;
	ec_response = &ec_response_i2c->ec_response;

	चयन (msg->result) अणु
	हाल EC_RES_SUCCESS:
		अवरोध;
	हाल EC_RES_IN_PROGRESS:
		ret = -EAGAIN;
		dev_dbg(ec_dev->dev, "command 0x%02x in progress\n",
			msg->command);
		जाओ करोne;

	शेष:
		dev_dbg(ec_dev->dev, "command 0x%02x returned %d\n",
			msg->command, msg->result);
		/*
		 * When we send v3 request to v2 ec, ec won't recognize the
		 * 0xda (EC_COMMAND_PROTOCOL_3) and will वापस with status
		 * EC_RES_INVALID_COMMAND with zero data length.
		 *
		 * In हाल of invalid command क्रम v3 protocol the data length
		 * will be at least माप(काष्ठा ec_host_response)
		 */
		अगर (ec_response_i2c->result == EC_RES_INVALID_COMMAND &&
		    ec_response_i2c->packet_length == 0) अणु
			ret = -EPROTONOSUPPORT;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (ec_response_i2c->packet_length < माप(काष्ठा ec_host_response)) अणु
		dev_err(ec_dev->dev,
			"response of %u bytes too short; not a full header\n",
			ec_response_i2c->packet_length);
		ret = -EBADMSG;
		जाओ करोne;
	पूर्ण

	अगर (msg->insize < ec_response->data_len) अणु
		dev_err(ec_dev->dev,
			"response data size is too large: expected %u, got %u\n",
			msg->insize,
			ec_response->data_len);
		ret = -EMSGSIZE;
		जाओ करोne;
	पूर्ण

	/* copy response packet payload and compute checksum */
	sum = 0;
	क्रम (i = 0; i < माप(काष्ठा ec_host_response); i++)
		sum += ((u8 *)ec_response)[i];

	स_नकल(msg->data,
	       in_buf + response_header_size,
	       ec_response->data_len);
	क्रम (i = 0; i < ec_response->data_len; i++)
		sum += msg->data[i];

	/* All bytes should sum to zero */
	अगर (sum) अणु
		dev_err(ec_dev->dev, "bad packet checksum\n");
		ret = -EBADMSG;
		जाओ करोne;
	पूर्ण

	ret = ec_response->data_len;

करोne:
	अगर (msg->command == EC_CMD_REBOOT_EC)
		msleep(EC_REBOOT_DELAY_MS);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_cmd_xfer_i2c(काष्ठा cros_ec_device *ec_dev,
				काष्ठा cros_ec_command *msg)
अणु
	काष्ठा i2c_client *client = ec_dev->priv;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i;
	पूर्णांक len;
	पूर्णांक packet_len;
	u8 *out_buf = शून्य;
	u8 *in_buf = शून्य;
	u8 sum;
	काष्ठा i2c_msg i2c_msg[2];

	i2c_msg[0].addr = client->addr;
	i2c_msg[0].flags = 0;
	i2c_msg[1].addr = client->addr;
	i2c_msg[1].flags = I2C_M_RD;

	/*
	 * allocate larger packet (one byte क्रम checksum, one byte क्रम
	 * length, and one क्रम result code)
	 */
	packet_len = msg->insize + 3;
	in_buf = kzalloc(packet_len, GFP_KERNEL);
	अगर (!in_buf)
		जाओ करोne;
	i2c_msg[1].len = packet_len;
	i2c_msg[1].buf = (अक्षर *)in_buf;

	/*
	 * allocate larger packet (one byte क्रम checksum, one क्रम
	 * command code, one क्रम length, and one क्रम command version)
	 */
	packet_len = msg->outsize + 4;
	out_buf = kzalloc(packet_len, GFP_KERNEL);
	अगर (!out_buf)
		जाओ करोne;
	i2c_msg[0].len = packet_len;
	i2c_msg[0].buf = (अक्षर *)out_buf;

	out_buf[0] = EC_CMD_VERSION0 + msg->version;
	out_buf[1] = msg->command;
	out_buf[2] = msg->outsize;

	/* copy message payload and compute checksum */
	sum = out_buf[0] + out_buf[1] + out_buf[2];
	क्रम (i = 0; i < msg->outsize; i++) अणु
		out_buf[3 + i] = msg->data[i];
		sum += out_buf[3 + i];
	पूर्ण
	out_buf[3 + msg->outsize] = sum;

	/* send command to EC and पढ़ो answer */
	ret = i2c_transfer(client->adapter, i2c_msg, 2);
	अगर (ret < 0) अणु
		dev_err(ec_dev->dev, "i2c transfer failed: %d\n", ret);
		जाओ करोne;
	पूर्ण अन्यथा अगर (ret != 2) अणु
		dev_err(ec_dev->dev, "failed to get response: %d\n", ret);
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	/* check response error code */
	msg->result = i2c_msg[1].buf[0];
	ret = cros_ec_check_result(ec_dev, msg);
	अगर (ret)
		जाओ करोne;

	len = in_buf[1];
	अगर (len > msg->insize) अणु
		dev_err(ec_dev->dev, "packet too long (%d bytes, expected %d)",
			len, msg->insize);
		ret = -ENOSPC;
		जाओ करोne;
	पूर्ण

	/* copy response packet payload and compute checksum */
	sum = in_buf[0] + in_buf[1];
	क्रम (i = 0; i < len; i++) अणु
		msg->data[i] = in_buf[2 + i];
		sum += in_buf[2 + i];
	पूर्ण
	dev_dbg(ec_dev->dev, "packet: %*ph, sum = %02x\n",
		i2c_msg[1].len, in_buf, sum);
	अगर (sum != in_buf[2 + len]) अणु
		dev_err(ec_dev->dev, "bad packet checksum\n");
		ret = -EBADMSG;
		जाओ करोne;
	पूर्ण

	ret = len;
करोne:
	kमुक्त(in_buf);
	kमुक्त(out_buf);
	अगर (msg->command == EC_CMD_REBOOT_EC)
		msleep(EC_REBOOT_DELAY_MS);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *dev_id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा cros_ec_device *ec_dev = शून्य;
	पूर्णांक err;

	ec_dev = devm_kzalloc(dev, माप(*ec_dev), GFP_KERNEL);
	अगर (!ec_dev)
		वापस -ENOMEM;

	i2c_set_clientdata(client, ec_dev);
	ec_dev->dev = dev;
	ec_dev->priv = client;
	ec_dev->irq = client->irq;
	ec_dev->cmd_xfer = cros_ec_cmd_xfer_i2c;
	ec_dev->pkt_xfer = cros_ec_pkt_xfer_i2c;
	ec_dev->phys_name = client->adapter->name;
	ec_dev->din_size = माप(काष्ठा ec_host_response_i2c) +
			   माप(काष्ठा ec_response_get_protocol_info);
	ec_dev->करोut_size = माप(काष्ठा ec_host_request_i2c);

	err = cros_ec_रेजिस्टर(ec_dev);
	अगर (err) अणु
		dev_err(dev, "cannot register EC\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cros_ec_device *ec_dev = i2c_get_clientdata(client);

	वापस cros_ec_unरेजिस्टर(ec_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cros_ec_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_device *ec_dev = to_ec_dev(dev);

	वापस cros_ec_suspend(ec_dev);
पूर्ण

अटल पूर्णांक cros_ec_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा cros_ec_device *ec_dev = to_ec_dev(dev);

	वापस cros_ec_resume(ec_dev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops cros_ec_i2c_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(cros_ec_i2c_suspend, cros_ec_i2c_resume)
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cros_ec_i2c_of_match[] = अणु
	अणु .compatible = "google,cros-ec-i2c", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cros_ec_i2c_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id cros_ec_i2c_id[] = अणु
	अणु "cros-ec-i2c", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cros_ec_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cros_ec_i2c_acpi_id[] = अणु
	अणु "GOOG0008", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cros_ec_i2c_acpi_id);
#पूर्ण_अगर

अटल काष्ठा i2c_driver cros_ec_driver = अणु
	.driver	= अणु
		.name	= "cros-ec-i2c",
		.acpi_match_table = ACPI_PTR(cros_ec_i2c_acpi_id),
		.of_match_table = of_match_ptr(cros_ec_i2c_of_match),
		.pm	= &cros_ec_i2c_pm_ops,
	पूर्ण,
	.probe		= cros_ec_i2c_probe,
	.हटाओ		= cros_ec_i2c_हटाओ,
	.id_table	= cros_ec_i2c_id,
पूर्ण;

module_i2c_driver(cros_ec_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("I2C interface for ChromeOS Embedded Controller");
