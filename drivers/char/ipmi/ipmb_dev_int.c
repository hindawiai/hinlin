<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * IPMB driver to receive a request and send a response
 *
 * Copyright (C) 2019 Mellanox Techologies, Ltd.
 *
 * This was inspired by Brendan Higgins' ipmi-bmc-bt-i2c driver.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

#घोषणा MAX_MSG_LEN		240
#घोषणा IPMB_REQUEST_LEN_MIN	7
#घोषणा NETFN_RSP_BIT_MASK	0x4
#घोषणा REQUEST_QUEUE_MAX_LEN	256

#घोषणा IPMB_MSG_LEN_IDX	0
#घोषणा RQ_SA_8BIT_IDX		1
#घोषणा NETFN_LUN_IDX		2

#घोषणा GET_7BIT_ADDR(addr_8bit)	(addr_8bit >> 1)
#घोषणा GET_8BIT_ADDR(addr_7bit)	((addr_7bit << 1) & 0xff)

#घोषणा IPMB_MSG_PAYLOAD_LEN_MAX (MAX_MSG_LEN - IPMB_REQUEST_LEN_MIN - 1)

#घोषणा SMBUS_MSG_HEADER_LENGTH	2
#घोषणा SMBUS_MSG_IDX_OFFSET	(SMBUS_MSG_HEADER_LENGTH + 1)

काष्ठा ipmb_msg अणु
	u8 len;
	u8 rs_sa;
	u8 netfn_rs_lun;
	u8 checksum1;
	u8 rq_sa;
	u8 rq_seq_rq_lun;
	u8 cmd;
	u8 payload[IPMB_MSG_PAYLOAD_LEN_MAX];
	/* checksum2 is included in payload */
पूर्ण __packed;

काष्ठा ipmb_request_elem अणु
	काष्ठा list_head list;
	काष्ठा ipmb_msg request;
पूर्ण;

काष्ठा ipmb_dev अणु
	काष्ठा i2c_client *client;
	काष्ठा miscdevice miscdev;
	काष्ठा ipmb_msg request;
	काष्ठा list_head request_queue;
	atomic_t request_queue_len;
	माप_प्रकार msg_idx;
	spinlock_t lock;
	रुको_queue_head_t रुको_queue;
	काष्ठा mutex file_mutex;
	bool is_i2c_protocol;
पूर्ण;

अटल अंतरभूत काष्ठा ipmb_dev *to_ipmb_dev(काष्ठा file *file)
अणु
	वापस container_of(file->निजी_data, काष्ठा ipmb_dev, miscdev);
पूर्ण

अटल sमाप_प्रकार ipmb_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा ipmb_dev *ipmb_dev = to_ipmb_dev(file);
	काष्ठा ipmb_request_elem *queue_elem;
	काष्ठा ipmb_msg msg;
	sमाप_प्रकार ret = 0;

	स_रखो(&msg, 0, माप(msg));

	spin_lock_irq(&ipmb_dev->lock);

	जबतक (list_empty(&ipmb_dev->request_queue)) अणु
		spin_unlock_irq(&ipmb_dev->lock);

		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		ret = रुको_event_पूर्णांकerruptible(ipmb_dev->रुको_queue,
				!list_empty(&ipmb_dev->request_queue));
		अगर (ret)
			वापस ret;

		spin_lock_irq(&ipmb_dev->lock);
	पूर्ण

	queue_elem = list_first_entry(&ipmb_dev->request_queue,
					काष्ठा ipmb_request_elem, list);
	स_नकल(&msg, &queue_elem->request, माप(msg));
	list_del(&queue_elem->list);
	kमुक्त(queue_elem);
	atomic_dec(&ipmb_dev->request_queue_len);

	spin_unlock_irq(&ipmb_dev->lock);

	count = min_t(माप_प्रकार, count, msg.len + 1);
	अगर (copy_to_user(buf, &msg, count))
		ret = -EFAULT;

	वापस ret < 0 ? ret : count;
पूर्ण

अटल पूर्णांक ipmb_i2c_ग_लिखो(काष्ठा i2c_client *client, u8 *msg, u8 addr)
अणु
	काष्ठा i2c_msg i2c_msg;

	/*
	 * subtract 1 byte (rq_sa) from the length of the msg passed to
	 * raw i2c_transfer
	 */
	i2c_msg.len = msg[IPMB_MSG_LEN_IDX] - 1;

	/* Assign message to buffer except first 2 bytes (length and address) */
	i2c_msg.buf = msg + 2;

	i2c_msg.addr = addr;
	i2c_msg.flags = client->flags & I2C_CLIENT_PEC;

	वापस i2c_transfer(client->adapter, &i2c_msg, 1);
पूर्ण

अटल sमाप_प्रकार ipmb_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ipmb_dev *ipmb_dev = to_ipmb_dev(file);
	u8 rq_sa, netf_rq_lun, msg_len;
	काष्ठा i2c_client *temp_client;
	u8 msg[MAX_MSG_LEN];
	sमाप_प्रकार ret;

	अगर (count > माप(msg))
		वापस -EINVAL;

	अगर (copy_from_user(&msg, buf, count))
		वापस -EFAULT;

	अगर (count < msg[0])
		वापस -EINVAL;

	rq_sa = GET_7BIT_ADDR(msg[RQ_SA_8BIT_IDX]);
	netf_rq_lun = msg[NETFN_LUN_IDX];

	/* Check i2c block transfer vs smbus */
	अगर (ipmb_dev->is_i2c_protocol) अणु
		ret = ipmb_i2c_ग_लिखो(ipmb_dev->client, msg, rq_sa);
		वापस (ret == 1) ? count : ret;
	पूर्ण

	/*
	 * subtract rq_sa and netf_rq_lun from the length of the msg. Fill the
	 * temporary client. Note that its use is an exception क्रम IPMI.
	 */
	msg_len = msg[IPMB_MSG_LEN_IDX] - SMBUS_MSG_HEADER_LENGTH;
	temp_client = kmemdup(ipmb_dev->client, माप(*temp_client), GFP_KERNEL);
	अगर (!temp_client)
		वापस -ENOMEM;

	temp_client->addr = rq_sa;

	ret = i2c_smbus_ग_लिखो_block_data(temp_client, netf_rq_lun, msg_len,
					 msg + SMBUS_MSG_IDX_OFFSET);
	kमुक्त(temp_client);

	वापस ret < 0 ? ret : count;
पूर्ण

अटल __poll_t ipmb_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा ipmb_dev *ipmb_dev = to_ipmb_dev(file);
	__poll_t mask = EPOLLOUT;

	mutex_lock(&ipmb_dev->file_mutex);
	poll_रुको(file, &ipmb_dev->रुको_queue, रुको);

	अगर (atomic_पढ़ो(&ipmb_dev->request_queue_len))
		mask |= EPOLLIN;
	mutex_unlock(&ipmb_dev->file_mutex);

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations ipmb_fops = अणु
	.owner	= THIS_MODULE,
	.पढ़ो	= ipmb_पढ़ो,
	.ग_लिखो	= ipmb_ग_लिखो,
	.poll	= ipmb_poll,
पूर्ण;

/* Called with ipmb_dev->lock held. */
अटल व्योम ipmb_handle_request(काष्ठा ipmb_dev *ipmb_dev)
अणु
	काष्ठा ipmb_request_elem *queue_elem;

	अगर (atomic_पढ़ो(&ipmb_dev->request_queue_len) >=
			REQUEST_QUEUE_MAX_LEN)
		वापस;

	queue_elem = kदो_स्मृति(माप(*queue_elem), GFP_ATOMIC);
	अगर (!queue_elem)
		वापस;

	स_नकल(&queue_elem->request, &ipmb_dev->request,
		माप(काष्ठा ipmb_msg));
	list_add(&queue_elem->list, &ipmb_dev->request_queue);
	atomic_inc(&ipmb_dev->request_queue_len);
	wake_up_all(&ipmb_dev->रुको_queue);
पूर्ण

अटल u8 ipmb_verअगरy_checksum1(काष्ठा ipmb_dev *ipmb_dev, u8 rs_sa)
अणु
	/* The 8 lsb of the sum is 0 when the checksum is valid */
	वापस (rs_sa + ipmb_dev->request.netfn_rs_lun +
		ipmb_dev->request.checksum1);
पूर्ण

/*
 * Verअगरy अगर message has proper ipmb header with minimum length
 * and correct checksum byte.
 */
अटल bool is_ipmb_msg(काष्ठा ipmb_dev *ipmb_dev, u8 rs_sa)
अणु
	अगर ((ipmb_dev->msg_idx >= IPMB_REQUEST_LEN_MIN) &&
	   (!ipmb_verअगरy_checksum1(ipmb_dev, rs_sa)))
		वापस true;

	वापस false;
पूर्ण

/*
 * The IPMB protocol only supports I2C Writes so there is no need
 * to support I2C_SLAVE_READ* events.
 * This i2c callback function only monitors IPMB request messages
 * and adds them in a queue, so that they can be handled by
 * receive_ipmb_request.
 */
अटल पूर्णांक ipmb_slave_cb(काष्ठा i2c_client *client,
			क्रमागत i2c_slave_event event, u8 *val)
अणु
	काष्ठा ipmb_dev *ipmb_dev = i2c_get_clientdata(client);
	u8 *buf = (u8 *)&ipmb_dev->request;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipmb_dev->lock, flags);
	चयन (event) अणु
	हाल I2C_SLAVE_WRITE_REQUESTED:
		स_रखो(&ipmb_dev->request, 0, माप(ipmb_dev->request));
		ipmb_dev->msg_idx = 0;

		/*
		 * At index 0, ipmb_msg stores the length of msg,
		 * skip it क्रम now.
		 * The len will be populated once the whole
		 * buf is populated.
		 *
		 * The I2C bus driver's responsibility is to pass the
		 * data bytes to the backend driver; it करोes not
		 * क्रमward the i2c slave address.
		 * Since the first byte in the IPMB message is the
		 * address of the responder, it is the responsibility
		 * of the IPMB driver to क्रमmat the message properly.
		 * So this driver prepends the address of the responder
		 * to the received i2c data beक्रमe the request message
		 * is handled in userland.
		 */
		buf[++ipmb_dev->msg_idx] = GET_8BIT_ADDR(client->addr);
		अवरोध;

	हाल I2C_SLAVE_WRITE_RECEIVED:
		अगर (ipmb_dev->msg_idx >= माप(काष्ठा ipmb_msg) - 1)
			अवरोध;

		buf[++ipmb_dev->msg_idx] = *val;
		अवरोध;

	हाल I2C_SLAVE_STOP:
		ipmb_dev->request.len = ipmb_dev->msg_idx;
		अगर (is_ipmb_msg(ipmb_dev, GET_8BIT_ADDR(client->addr)))
			ipmb_handle_request(ipmb_dev);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ipmb_dev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ipmb_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ipmb_dev *ipmb_dev;
	पूर्णांक ret;

	ipmb_dev = devm_kzalloc(&client->dev, माप(*ipmb_dev),
					GFP_KERNEL);
	अगर (!ipmb_dev)
		वापस -ENOMEM;

	spin_lock_init(&ipmb_dev->lock);
	init_रुकोqueue_head(&ipmb_dev->रुको_queue);
	atomic_set(&ipmb_dev->request_queue_len, 0);
	INIT_LIST_HEAD(&ipmb_dev->request_queue);

	mutex_init(&ipmb_dev->file_mutex);

	ipmb_dev->miscdev.minor = MISC_DYNAMIC_MINOR;

	ipmb_dev->miscdev.name = devm_kaप्र_लिखो(&client->dev, GFP_KERNEL,
						"%s%d", "ipmb-",
						client->adapter->nr);
	ipmb_dev->miscdev.fops = &ipmb_fops;
	ipmb_dev->miscdev.parent = &client->dev;
	ret = misc_रेजिस्टर(&ipmb_dev->miscdev);
	अगर (ret)
		वापस ret;

	ipmb_dev->is_i2c_protocol
		= device_property_पढ़ो_bool(&client->dev, "i2c-protocol");

	ipmb_dev->client = client;
	i2c_set_clientdata(client, ipmb_dev);
	ret = i2c_slave_रेजिस्टर(client, ipmb_slave_cb);
	अगर (ret) अणु
		misc_deरेजिस्टर(&ipmb_dev->miscdev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipmb_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ipmb_dev *ipmb_dev = i2c_get_clientdata(client);

	i2c_slave_unरेजिस्टर(client);
	misc_deरेजिस्टर(&ipmb_dev->miscdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ipmb_id[] = अणु
	अणु "ipmb-dev", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ipmb_id);

अटल स्थिर काष्ठा acpi_device_id acpi_ipmb_id[] = अणु
	अणु "IPMB0001", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, acpi_ipmb_id);

अटल काष्ठा i2c_driver ipmb_driver = अणु
	.driver = अणु
		.name = "ipmb-dev",
		.acpi_match_table = ACPI_PTR(acpi_ipmb_id),
	पूर्ण,
	.probe = ipmb_probe,
	.हटाओ = ipmb_हटाओ,
	.id_table = ipmb_id,
पूर्ण;
module_i2c_driver(ipmb_driver);

MODULE_AUTHOR("Mellanox Technologies");
MODULE_DESCRIPTION("IPMB driver");
MODULE_LICENSE("GPL v2");
