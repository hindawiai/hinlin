<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * I2C bridge driver क्रम the Greybus "generic" I2C module.
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/greybus.h>

#समावेश "gbphy.h"

काष्ठा gb_i2c_device अणु
	काष्ठा gb_connection	*connection;
	काष्ठा gbphy_device	*gbphy_dev;

	u32			functionality;

	काष्ठा i2c_adapter	adapter;
पूर्ण;

/*
 * Map Greybus i2c functionality bits पूर्णांकo Linux ones
 */
अटल u32 gb_i2c_functionality_map(u32 gb_i2c_functionality)
अणु
	वापस gb_i2c_functionality;	/* All bits the same क्रम now */
पूर्ण

/*
 * Do initial setup of the i2c device.  This includes verअगरying we
 * can support it (based on the protocol version it advertises).
 * If that's OK, we get and cached its functionality bits.
 *
 * Note: gb_i2c_dev->connection is assumed to have been valid.
 */
अटल पूर्णांक gb_i2c_device_setup(काष्ठा gb_i2c_device *gb_i2c_dev)
अणु
	काष्ठा gb_i2c_functionality_response response;
	u32 functionality;
	पूर्णांक ret;

	ret = gb_operation_sync(gb_i2c_dev->connection,
				GB_I2C_TYPE_FUNCTIONALITY,
				शून्य, 0, &response, माप(response));
	अगर (ret)
		वापस ret;

	functionality = le32_to_cpu(response.functionality);
	gb_i2c_dev->functionality = gb_i2c_functionality_map(functionality);

	वापस 0;
पूर्ण

/*
 * Map Linux i2c_msg flags पूर्णांकo Greybus i2c transfer op flags.
 */
अटल u16 gb_i2c_transfer_op_flags_map(u16 flags)
अणु
	वापस flags;	/* All flags the same क्रम now */
पूर्ण

अटल व्योम
gb_i2c_fill_transfer_op(काष्ठा gb_i2c_transfer_op *op, काष्ठा i2c_msg *msg)
अणु
	u16 flags = gb_i2c_transfer_op_flags_map(msg->flags);

	op->addr = cpu_to_le16(msg->addr);
	op->flags = cpu_to_le16(flags);
	op->size = cpu_to_le16(msg->len);
पूर्ण

अटल काष्ठा gb_operation *
gb_i2c_operation_create(काष्ठा gb_connection *connection,
			काष्ठा i2c_msg *msgs, u32 msg_count)
अणु
	काष्ठा gb_i2c_device *gb_i2c_dev = gb_connection_get_data(connection);
	काष्ठा gb_i2c_transfer_request *request;
	काष्ठा gb_operation *operation;
	काष्ठा gb_i2c_transfer_op *op;
	काष्ठा i2c_msg *msg;
	u32 data_out_size = 0;
	u32 data_in_size = 0;
	माप_प्रकार request_size;
	व्योम *data;
	u16 op_count;
	u32 i;

	अगर (msg_count > (u32)U16_MAX) अणु
		dev_err(&gb_i2c_dev->gbphy_dev->dev, "msg_count (%u) too big\n",
			msg_count);
		वापस शून्य;
	पूर्ण
	op_count = (u16)msg_count;

	/*
	 * In addition to space क्रम all message descriptors we need
	 * to have enough to hold all outbound message data.
	 */
	msg = msgs;
	क्रम (i = 0; i < msg_count; i++, msg++)
		अगर (msg->flags & I2C_M_RD)
			data_in_size += (u32)msg->len;
		अन्यथा
			data_out_size += (u32)msg->len;

	request_size = माप(*request);
	request_size += msg_count * माप(*op);
	request_size += data_out_size;

	/* Response consists only of incoming data */
	operation = gb_operation_create(connection, GB_I2C_TYPE_TRANSFER,
					request_size, data_in_size, GFP_KERNEL);
	अगर (!operation)
		वापस शून्य;

	request = operation->request->payload;
	request->op_count = cpu_to_le16(op_count);
	/* Fill in the ops array */
	op = &request->ops[0];
	msg = msgs;
	क्रम (i = 0; i < msg_count; i++)
		gb_i2c_fill_transfer_op(op++, msg++);

	अगर (!data_out_size)
		वापस operation;

	/* Copy over the outgoing data; it starts after the last op */
	data = op;
	msg = msgs;
	क्रम (i = 0; i < msg_count; i++) अणु
		अगर (!(msg->flags & I2C_M_RD)) अणु
			स_नकल(data, msg->buf, msg->len);
			data += msg->len;
		पूर्ण
		msg++;
	पूर्ण

	वापस operation;
पूर्ण

अटल व्योम gb_i2c_decode_response(काष्ठा i2c_msg *msgs, u32 msg_count,
				   काष्ठा gb_i2c_transfer_response *response)
अणु
	काष्ठा i2c_msg *msg = msgs;
	u8 *data;
	u32 i;

	अगर (!response)
		वापस;
	data = response->data;
	क्रम (i = 0; i < msg_count; i++) अणु
		अगर (msg->flags & I2C_M_RD) अणु
			स_नकल(msg->buf, data, msg->len);
			data += msg->len;
		पूर्ण
		msg++;
	पूर्ण
पूर्ण

/*
 * Some i2c transfer operations वापस results that are expected.
 */
अटल bool gb_i2c_expected_transfer_error(पूर्णांक त्रुटि_सं)
अणु
	वापस त्रुटि_सं == -EAGAIN || त्रुटि_सं == -ENODEV;
पूर्ण

अटल पूर्णांक gb_i2c_transfer_operation(काष्ठा gb_i2c_device *gb_i2c_dev,
				     काष्ठा i2c_msg *msgs, u32 msg_count)
अणु
	काष्ठा gb_connection *connection = gb_i2c_dev->connection;
	काष्ठा device *dev = &gb_i2c_dev->gbphy_dev->dev;
	काष्ठा gb_operation *operation;
	पूर्णांक ret;

	operation = gb_i2c_operation_create(connection, msgs, msg_count);
	अगर (!operation)
		वापस -ENOMEM;

	ret = gbphy_runसमय_get_sync(gb_i2c_dev->gbphy_dev);
	अगर (ret)
		जाओ निकास_operation_put;

	ret = gb_operation_request_send_sync(operation);
	अगर (!ret) अणु
		काष्ठा gb_i2c_transfer_response *response;

		response = operation->response->payload;
		gb_i2c_decode_response(msgs, msg_count, response);
		ret = msg_count;
	पूर्ण अन्यथा अगर (!gb_i2c_expected_transfer_error(ret)) अणु
		dev_err(dev, "transfer operation failed (%d)\n", ret);
	पूर्ण

	gbphy_runसमय_put_स्वतःsuspend(gb_i2c_dev->gbphy_dev);

निकास_operation_put:
	gb_operation_put(operation);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_i2c_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			      पूर्णांक msg_count)
अणु
	काष्ठा gb_i2c_device *gb_i2c_dev;

	gb_i2c_dev = i2c_get_adapdata(adap);

	वापस gb_i2c_transfer_operation(gb_i2c_dev, msgs, msg_count);
पूर्ण

अटल u32 gb_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा gb_i2c_device *gb_i2c_dev = i2c_get_adapdata(adap);

	वापस gb_i2c_dev->functionality;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm gb_i2c_algorithm = अणु
	.master_xfer	= gb_i2c_master_xfer,
	.functionality	= gb_i2c_functionality,
पूर्ण;

अटल पूर्णांक gb_i2c_probe(काष्ठा gbphy_device *gbphy_dev,
			स्थिर काष्ठा gbphy_device_id *id)
अणु
	काष्ठा gb_connection *connection;
	काष्ठा gb_i2c_device *gb_i2c_dev;
	काष्ठा i2c_adapter *adapter;
	पूर्णांक ret;

	gb_i2c_dev = kzalloc(माप(*gb_i2c_dev), GFP_KERNEL);
	अगर (!gb_i2c_dev)
		वापस -ENOMEM;

	connection =
		gb_connection_create(gbphy_dev->bundle,
				     le16_to_cpu(gbphy_dev->cport_desc->id),
				     शून्य);
	अगर (IS_ERR(connection)) अणु
		ret = PTR_ERR(connection);
		जाओ निकास_i2cdev_मुक्त;
	पूर्ण

	gb_i2c_dev->connection = connection;
	gb_connection_set_data(connection, gb_i2c_dev);
	gb_i2c_dev->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, gb_i2c_dev);

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ निकास_connection_destroy;

	ret = gb_i2c_device_setup(gb_i2c_dev);
	अगर (ret)
		जाओ निकास_connection_disable;

	/* Looks good; up our i2c adapter */
	adapter = &gb_i2c_dev->adapter;
	adapter->owner = THIS_MODULE;
	adapter->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	adapter->algo = &gb_i2c_algorithm;

	adapter->dev.parent = &gbphy_dev->dev;
	snम_लिखो(adapter->name, माप(adapter->name), "Greybus i2c adapter");
	i2c_set_adapdata(adapter, gb_i2c_dev);

	ret = i2c_add_adapter(adapter);
	अगर (ret)
		जाओ निकास_connection_disable;

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);
	वापस 0;

निकास_connection_disable:
	gb_connection_disable(connection);
निकास_connection_destroy:
	gb_connection_destroy(connection);
निकास_i2cdev_मुक्त:
	kमुक्त(gb_i2c_dev);

	वापस ret;
पूर्ण

अटल व्योम gb_i2c_हटाओ(काष्ठा gbphy_device *gbphy_dev)
अणु
	काष्ठा gb_i2c_device *gb_i2c_dev = gb_gbphy_get_data(gbphy_dev);
	काष्ठा gb_connection *connection = gb_i2c_dev->connection;
	पूर्णांक ret;

	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		gbphy_runसमय_get_noresume(gbphy_dev);

	i2c_del_adapter(&gb_i2c_dev->adapter);
	gb_connection_disable(connection);
	gb_connection_destroy(connection);
	kमुक्त(gb_i2c_dev);
पूर्ण

अटल स्थिर काष्ठा gbphy_device_id gb_i2c_id_table[] = अणु
	अणु GBPHY_PROTOCOL(GREYBUS_PROTOCOL_I2C) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(gbphy, gb_i2c_id_table);

अटल काष्ठा gbphy_driver i2c_driver = अणु
	.name		= "i2c",
	.probe		= gb_i2c_probe,
	.हटाओ		= gb_i2c_हटाओ,
	.id_table	= gb_i2c_id_table,
पूर्ण;

module_gbphy_driver(i2c_driver);
MODULE_LICENSE("GPL v2");
