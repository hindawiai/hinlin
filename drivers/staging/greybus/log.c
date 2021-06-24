<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus driver क्रम the log protocol
 *
 * Copyright 2016 Google Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sizes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/greybus.h>

काष्ठा gb_log अणु
	काष्ठा gb_connection *connection;
पूर्ण;

अटल पूर्णांक gb_log_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा device *dev = &connection->bundle->dev;
	काष्ठा gb_log_send_log_request *receive;
	u16 len;

	अगर (op->type != GB_LOG_TYPE_SEND_LOG) अणु
		dev_err(dev, "unknown request type 0x%02x\n", op->type);
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy size of payload */
	अगर (op->request->payload_size < माप(*receive)) अणु
		dev_err(dev, "log request too small (%zu < %zu)\n",
			op->request->payload_size, माप(*receive));
		वापस -EINVAL;
	पूर्ण
	receive = op->request->payload;
	len = le16_to_cpu(receive->len);
	अगर (len != (op->request->payload_size - माप(*receive))) अणु
		dev_err(dev, "log request wrong size %d vs %zu\n", len,
			(op->request->payload_size - माप(*receive)));
		वापस -EINVAL;
	पूर्ण
	अगर (len == 0) अणु
		dev_err(dev, "log request of 0 bytes?\n");
		वापस -EINVAL;
	पूर्ण

	अगर (len > GB_LOG_MAX_LEN) अणु
		dev_err(dev, "log request too big: %d\n", len);
		वापस -EINVAL;
	पूर्ण

	/* Ensure the buffer is 0 terminated */
	receive->msg[len - 1] = '\0';

	/*
	 * Prपूर्णांक with dev_dbg() so that it can be easily turned off using
	 * dynamic debugging (and prevent any DoS)
	 */
	dev_dbg(dev, "%s", receive->msg);

	वापस 0;
पूर्ण

अटल पूर्णांक gb_log_probe(काष्ठा gb_bundle *bundle,
			स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_connection *connection;
	काष्ठा gb_log *log;
	पूर्णांक retval;

	अगर (bundle->num_cports != 1)
		वापस -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	अगर (cport_desc->protocol_id != GREYBUS_PROTOCOL_LOG)
		वापस -ENODEV;

	log = kzalloc(माप(*log), GFP_KERNEL);
	अगर (!log)
		वापस -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_log_request_handler);
	अगर (IS_ERR(connection)) अणु
		retval = PTR_ERR(connection);
		जाओ error_मुक्त;
	पूर्ण

	log->connection = connection;
	greybus_set_drvdata(bundle, log);

	retval = gb_connection_enable(connection);
	अगर (retval)
		जाओ error_connection_destroy;

	वापस 0;

error_connection_destroy:
	gb_connection_destroy(connection);
error_मुक्त:
	kमुक्त(log);
	वापस retval;
पूर्ण

अटल व्योम gb_log_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_log *log = greybus_get_drvdata(bundle);
	काष्ठा gb_connection *connection = log->connection;

	gb_connection_disable(connection);
	gb_connection_destroy(connection);

	kमुक्त(log);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_log_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_LOG) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(greybus, gb_log_id_table);

अटल काष्ठा greybus_driver gb_log_driver = अणु
	.name           = "log",
	.probe          = gb_log_probe,
	.disconnect     = gb_log_disconnect,
	.id_table       = gb_log_id_table,
पूर्ण;
module_greybus_driver(gb_log_driver);

MODULE_LICENSE("GPL v2");
