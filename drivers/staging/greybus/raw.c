<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus driver क्रम the Raw protocol
 *
 * Copyright 2015 Google Inc.
 * Copyright 2015 Linaro Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sizes.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/idr.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/greybus.h>

काष्ठा gb_raw अणु
	काष्ठा gb_connection *connection;

	काष्ठा list_head list;
	पूर्णांक list_data;
	काष्ठा mutex list_lock;
	dev_t dev;
	काष्ठा cdev cdev;
	काष्ठा device *device;
पूर्ण;

काष्ठा raw_data अणु
	काष्ठा list_head entry;
	u32 len;
	u8 data[];
पूर्ण;

अटल काष्ठा class *raw_class;
अटल पूर्णांक raw_major;
अटल स्थिर काष्ठा file_operations raw_fops;
अटल DEFINE_IDA(minors);

/* Number of minor devices this driver supports */
#घोषणा NUM_MINORS	256

/* Maximum size of any one send data buffer we support */
#घोषणा MAX_PACKET_SIZE	(PAGE_SIZE * 2)

/*
 * Maximum size of the data in the receive buffer we allow beक्रमe we start to
 * drop messages on the न्यूनमान
 */
#घोषणा MAX_DATA_SIZE	(MAX_PACKET_SIZE * 8)

/*
 * Add the raw data message to the list of received messages.
 */
अटल पूर्णांक receive_data(काष्ठा gb_raw *raw, u32 len, u8 *data)
अणु
	काष्ठा raw_data *raw_data;
	काष्ठा device *dev = &raw->connection->bundle->dev;
	पूर्णांक retval = 0;

	अगर (len > MAX_PACKET_SIZE) अणु
		dev_err(dev, "Too big of a data packet, rejected\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&raw->list_lock);
	अगर ((raw->list_data + len) > MAX_DATA_SIZE) अणु
		dev_err(dev, "Too much data in receive buffer, now dropping packets\n");
		retval = -EINVAL;
		जाओ निकास;
	पूर्ण

	raw_data = kदो_स्मृति(माप(*raw_data) + len, GFP_KERNEL);
	अगर (!raw_data) अणु
		retval = -ENOMEM;
		जाओ निकास;
	पूर्ण

	raw->list_data += len;
	raw_data->len = len;
	स_नकल(&raw_data->data[0], data, len);

	list_add_tail(&raw_data->entry, &raw->list);
निकास:
	mutex_unlock(&raw->list_lock);
	वापस retval;
पूर्ण

अटल पूर्णांक gb_raw_request_handler(काष्ठा gb_operation *op)
अणु
	काष्ठा gb_connection *connection = op->connection;
	काष्ठा device *dev = &connection->bundle->dev;
	काष्ठा gb_raw *raw = greybus_get_drvdata(connection->bundle);
	काष्ठा gb_raw_send_request *receive;
	u32 len;

	अगर (op->type != GB_RAW_TYPE_SEND) अणु
		dev_err(dev, "unknown request type 0x%02x\n", op->type);
		वापस -EINVAL;
	पूर्ण

	/* Verअगरy size of payload */
	अगर (op->request->payload_size < माप(*receive)) अणु
		dev_err(dev, "raw receive request too small (%zu < %zu)\n",
			op->request->payload_size, माप(*receive));
		वापस -EINVAL;
	पूर्ण
	receive = op->request->payload;
	len = le32_to_cpu(receive->len);
	अगर (len != (पूर्णांक)(op->request->payload_size - माप(__le32))) अणु
		dev_err(dev, "raw receive request wrong size %d vs %d\n", len,
			(पूर्णांक)(op->request->payload_size - माप(__le32)));
		वापस -EINVAL;
	पूर्ण
	अगर (len == 0) अणु
		dev_err(dev, "raw receive request of 0 bytes?\n");
		वापस -EINVAL;
	पूर्ण

	वापस receive_data(raw, len, receive->data);
पूर्ण

अटल पूर्णांक gb_raw_send(काष्ठा gb_raw *raw, u32 len, स्थिर अक्षर __user *data)
अणु
	काष्ठा gb_connection *connection = raw->connection;
	काष्ठा gb_raw_send_request *request;
	पूर्णांक retval;

	request = kदो_स्मृति(len + माप(*request), GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	अगर (copy_from_user(&request->data[0], data, len)) अणु
		kमुक्त(request);
		वापस -EFAULT;
	पूर्ण

	request->len = cpu_to_le32(len);

	retval = gb_operation_sync(connection, GB_RAW_TYPE_SEND,
				   request, len + माप(*request),
				   शून्य, 0);

	kमुक्त(request);
	वापस retval;
पूर्ण

अटल पूर्णांक gb_raw_probe(काष्ठा gb_bundle *bundle,
			स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_connection *connection;
	काष्ठा gb_raw *raw;
	पूर्णांक retval;
	पूर्णांक minor;

	अगर (bundle->num_cports != 1)
		वापस -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	अगर (cport_desc->protocol_id != GREYBUS_PROTOCOL_RAW)
		वापस -ENODEV;

	raw = kzalloc(माप(*raw), GFP_KERNEL);
	अगर (!raw)
		वापस -ENOMEM;

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_raw_request_handler);
	अगर (IS_ERR(connection)) अणु
		retval = PTR_ERR(connection);
		जाओ error_मुक्त;
	पूर्ण

	INIT_LIST_HEAD(&raw->list);
	mutex_init(&raw->list_lock);

	raw->connection = connection;
	greybus_set_drvdata(bundle, raw);

	minor = ida_simple_get(&minors, 0, 0, GFP_KERNEL);
	अगर (minor < 0) अणु
		retval = minor;
		जाओ error_connection_destroy;
	पूर्ण

	raw->dev = MKDEV(raw_major, minor);
	cdev_init(&raw->cdev, &raw_fops);

	retval = gb_connection_enable(connection);
	अगर (retval)
		जाओ error_हटाओ_ida;

	retval = cdev_add(&raw->cdev, raw->dev, 1);
	अगर (retval)
		जाओ error_connection_disable;

	raw->device = device_create(raw_class, &connection->bundle->dev,
				    raw->dev, raw, "gb!raw%d", minor);
	अगर (IS_ERR(raw->device)) अणु
		retval = PTR_ERR(raw->device);
		जाओ error_del_cdev;
	पूर्ण

	वापस 0;

error_del_cdev:
	cdev_del(&raw->cdev);

error_connection_disable:
	gb_connection_disable(connection);

error_हटाओ_ida:
	ida_simple_हटाओ(&minors, minor);

error_connection_destroy:
	gb_connection_destroy(connection);

error_मुक्त:
	kमुक्त(raw);
	वापस retval;
पूर्ण

अटल व्योम gb_raw_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_raw *raw = greybus_get_drvdata(bundle);
	काष्ठा gb_connection *connection = raw->connection;
	काष्ठा raw_data *raw_data;
	काष्ठा raw_data *temp;

	// FIXME - handle removing a connection when the अक्षर device node is खोलो.
	device_destroy(raw_class, raw->dev);
	cdev_del(&raw->cdev);
	gb_connection_disable(connection);
	ida_simple_हटाओ(&minors, MINOR(raw->dev));
	gb_connection_destroy(connection);

	mutex_lock(&raw->list_lock);
	list_क्रम_each_entry_safe(raw_data, temp, &raw->list, entry) अणु
		list_del(&raw_data->entry);
		kमुक्त(raw_data);
	पूर्ण
	mutex_unlock(&raw->list_lock);

	kमुक्त(raw);
पूर्ण

/*
 * Character device node पूर्णांकerfaces.
 *
 * Note, we are using पढ़ो/ग_लिखो to only allow a single पढ़ो/ग_लिखो per message.
 * This means क्रम पढ़ो(), you have to provide a big enough buffer क्रम the full
 * message to be copied पूर्णांकo.  If the buffer isn't big enough, the पढ़ो() will
 * fail with -ENOSPC.
 */

अटल पूर्णांक raw_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा cdev *cdev = inode->i_cdev;
	काष्ठा gb_raw *raw = container_of(cdev, काष्ठा gb_raw, cdev);

	file->निजी_data = raw;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार raw_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा gb_raw *raw = file->निजी_data;
	पूर्णांक retval;

	अगर (!count)
		वापस 0;

	अगर (count > MAX_PACKET_SIZE)
		वापस -E2BIG;

	retval = gb_raw_send(raw, count, buf);
	अगर (retval)
		वापस retval;

	वापस count;
पूर्ण

अटल sमाप_प्रकार raw_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा gb_raw *raw = file->निजी_data;
	पूर्णांक retval = 0;
	काष्ठा raw_data *raw_data;

	mutex_lock(&raw->list_lock);
	अगर (list_empty(&raw->list))
		जाओ निकास;

	raw_data = list_first_entry(&raw->list, काष्ठा raw_data, entry);
	अगर (raw_data->len > count) अणु
		retval = -ENOSPC;
		जाओ निकास;
	पूर्ण

	अगर (copy_to_user(buf, &raw_data->data[0], raw_data->len)) अणु
		retval = -EFAULT;
		जाओ निकास;
	पूर्ण

	list_del(&raw_data->entry);
	raw->list_data -= raw_data->len;
	retval = raw_data->len;
	kमुक्त(raw_data);

निकास:
	mutex_unlock(&raw->list_lock);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations raw_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= raw_ग_लिखो,
	.पढ़ो		= raw_पढ़ो,
	.खोलो		= raw_खोलो,
	.llseek		= noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा greybus_bundle_id gb_raw_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_RAW) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(greybus, gb_raw_id_table);

अटल काष्ठा greybus_driver gb_raw_driver = अणु
	.name		= "raw",
	.probe		= gb_raw_probe,
	.disconnect	= gb_raw_disconnect,
	.id_table	= gb_raw_id_table,
पूर्ण;

अटल पूर्णांक raw_init(व्योम)
अणु
	dev_t dev;
	पूर्णांक retval;

	raw_class = class_create(THIS_MODULE, "gb_raw");
	अगर (IS_ERR(raw_class)) अणु
		retval = PTR_ERR(raw_class);
		जाओ error_class;
	पूर्ण

	retval = alloc_chrdev_region(&dev, 0, NUM_MINORS, "gb_raw");
	अगर (retval < 0)
		जाओ error_chrdev;

	raw_major = MAJOR(dev);

	retval = greybus_रेजिस्टर(&gb_raw_driver);
	अगर (retval)
		जाओ error_gb;

	वापस 0;

error_gb:
	unरेजिस्टर_chrdev_region(dev, NUM_MINORS);
error_chrdev:
	class_destroy(raw_class);
error_class:
	वापस retval;
पूर्ण
module_init(raw_init);

अटल व्योम __निकास raw_निकास(व्योम)
अणु
	greybus_deरेजिस्टर(&gb_raw_driver);
	unरेजिस्टर_chrdev_region(MKDEV(raw_major, 0), NUM_MINORS);
	class_destroy(raw_class);
	ida_destroy(&minors);
पूर्ण
module_निकास(raw_निकास);

MODULE_LICENSE("GPL v2");
