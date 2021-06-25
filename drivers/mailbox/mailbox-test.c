<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 ST Microelectronics
 *
 * Author: Lee Jones <lee.jones@linaro.org>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/संकेत.स>

#घोषणा MBOX_MAX_SIG_LEN	8
#घोषणा MBOX_MAX_MSG_LEN	128
#घोषणा MBOX_BYTES_PER_LINE	16
#घोषणा MBOX_HEXDUMP_LINE_LEN	((MBOX_BYTES_PER_LINE * 4) + 2)
#घोषणा MBOX_HEXDUMP_MAX_LEN	(MBOX_HEXDUMP_LINE_LEN *		\
				 (MBOX_MAX_MSG_LEN / MBOX_BYTES_PER_LINE))

अटल bool mbox_data_पढ़ोy;

काष्ठा mbox_test_device अणु
	काष्ठा device		*dev;
	व्योम __iomem		*tx_mmio;
	व्योम __iomem		*rx_mmio;
	काष्ठा mbox_chan	*tx_channel;
	काष्ठा mbox_chan	*rx_channel;
	अक्षर			*rx_buffer;
	अक्षर			*संकेत;
	अक्षर			*message;
	spinlock_t		lock;
	रुको_queue_head_t	रुकोq;
	काष्ठा fasync_काष्ठा	*async_queue;
	काष्ठा dentry		*root_debugfs_dir;
पूर्ण;

अटल sमाप_प्रकार mbox_test_संकेत_ग_लिखो(काष्ठा file *filp,
				       स्थिर अक्षर __user *userbuf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mbox_test_device *tdev = filp->निजी_data;

	अगर (!tdev->tx_channel) अणु
		dev_err(tdev->dev, "Channel cannot do Tx\n");
		वापस -EINVAL;
	पूर्ण

	अगर (count > MBOX_MAX_SIG_LEN) अणु
		dev_err(tdev->dev,
			"Signal length %zd greater than max allowed %d\n",
			count, MBOX_MAX_SIG_LEN);
		वापस -EINVAL;
	पूर्ण

	/* Only allocate memory अगर we need to */
	अगर (!tdev->संकेत) अणु
		tdev->संकेत = kzalloc(MBOX_MAX_SIG_LEN, GFP_KERNEL);
		अगर (!tdev->संकेत)
			वापस -ENOMEM;
	पूर्ण

	अगर (copy_from_user(tdev->संकेत, userbuf, count)) अणु
		kमुक्त(tdev->संकेत);
		tdev->संकेत = शून्य;
		वापस -EFAULT;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations mbox_test_संकेत_ops = अणु
	.ग_लिखो	= mbox_test_संकेत_ग_लिखो,
	.खोलो	= simple_खोलो,
	.llseek	= generic_file_llseek,
पूर्ण;

अटल पूर्णांक mbox_test_message_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	काष्ठा mbox_test_device *tdev = filp->निजी_data;

	वापस fasync_helper(fd, filp, on, &tdev->async_queue);
पूर्ण

अटल sमाप_प्रकार mbox_test_message_ग_लिखो(काष्ठा file *filp,
				       स्थिर अक्षर __user *userbuf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mbox_test_device *tdev = filp->निजी_data;
	व्योम *data;
	पूर्णांक ret;

	अगर (!tdev->tx_channel) अणु
		dev_err(tdev->dev, "Channel cannot do Tx\n");
		वापस -EINVAL;
	पूर्ण

	अगर (count > MBOX_MAX_MSG_LEN) अणु
		dev_err(tdev->dev,
			"Message length %zd greater than max allowed %d\n",
			count, MBOX_MAX_MSG_LEN);
		वापस -EINVAL;
	पूर्ण

	tdev->message = kzalloc(MBOX_MAX_MSG_LEN, GFP_KERNEL);
	अगर (!tdev->message)
		वापस -ENOMEM;

	ret = copy_from_user(tdev->message, userbuf, count);
	अगर (ret) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/*
	 * A separate संकेत is only of use अगर there is
	 * MMIO to subsequently pass the message through
	 */
	अगर (tdev->tx_mmio && tdev->संकेत) अणु
		prपूर्णांक_hex_dump_bytes("Client: Sending: Signal: ", DUMP_PREFIX_ADDRESS,
				     tdev->संकेत, MBOX_MAX_SIG_LEN);

		data = tdev->संकेत;
	पूर्ण अन्यथा
		data = tdev->message;

	prपूर्णांक_hex_dump_bytes("Client: Sending: Message: ", DUMP_PREFIX_ADDRESS,
			     tdev->message, MBOX_MAX_MSG_LEN);

	ret = mbox_send_message(tdev->tx_channel, data);
	अगर (ret < 0)
		dev_err(tdev->dev, "Failed to send message via mailbox\n");

out:
	kमुक्त(tdev->संकेत);
	kमुक्त(tdev->message);
	tdev->संकेत = शून्य;

	वापस ret < 0 ? ret : count;
पूर्ण

अटल bool mbox_test_message_data_पढ़ोy(काष्ठा mbox_test_device *tdev)
अणु
	bool data_पढ़ोy;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tdev->lock, flags);
	data_पढ़ोy = mbox_data_पढ़ोy;
	spin_unlock_irqrestore(&tdev->lock, flags);

	वापस data_पढ़ोy;
पूर्ण

अटल sमाप_प्रकार mbox_test_message_पढ़ो(काष्ठा file *filp, अक्षर __user *userbuf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mbox_test_device *tdev = filp->निजी_data;
	अचिन्हित दीर्घ flags;
	अक्षर *touser, *ptr;
	पूर्णांक l = 0;
	पूर्णांक ret;

	DECLARE_WAITQUEUE(रुको, current);

	touser = kzalloc(MBOX_HEXDUMP_MAX_LEN + 1, GFP_KERNEL);
	अगर (!touser)
		वापस -ENOMEM;

	अगर (!tdev->rx_channel) अणु
		ret = snम_लिखो(touser, 20, "<NO RX CAPABILITY>\n");
		ret = simple_पढ़ो_from_buffer(userbuf, count, ppos,
					      touser, ret);
		जाओ kमुक्त_err;
	पूर्ण

	add_रुको_queue(&tdev->रुकोq, &रुको);

	करो अणु
		__set_current_state(TASK_INTERRUPTIBLE);

		अगर (mbox_test_message_data_पढ़ोy(tdev))
			अवरोध;

		अगर (filp->f_flags & O_NONBLOCK) अणु
			ret = -EAGAIN;
			जाओ रुकोq_err;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			जाओ रुकोq_err;
		पूर्ण
		schedule();

	पूर्ण जबतक (1);

	spin_lock_irqsave(&tdev->lock, flags);

	ptr = tdev->rx_buffer;
	जबतक (l < MBOX_HEXDUMP_MAX_LEN) अणु
		hex_dump_to_buffer(ptr,
				   MBOX_BYTES_PER_LINE,
				   MBOX_BYTES_PER_LINE, 1, touser + l,
				   MBOX_HEXDUMP_LINE_LEN, true);

		ptr += MBOX_BYTES_PER_LINE;
		l += MBOX_HEXDUMP_LINE_LEN;
		*(touser + (l - 1)) = '\n';
	पूर्ण
	*(touser + l) = '\0';

	स_रखो(tdev->rx_buffer, 0, MBOX_MAX_MSG_LEN);
	mbox_data_पढ़ोy = false;

	spin_unlock_irqrestore(&tdev->lock, flags);

	ret = simple_पढ़ो_from_buffer(userbuf, count, ppos, touser, MBOX_HEXDUMP_MAX_LEN);
रुकोq_err:
	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&tdev->रुकोq, &रुको);
kमुक्त_err:
	kमुक्त(touser);
	वापस ret;
पूर्ण

अटल __poll_t
mbox_test_message_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा mbox_test_device *tdev = filp->निजी_data;

	poll_रुको(filp, &tdev->रुकोq, रुको);

	अगर (mbox_test_message_data_पढ़ोy(tdev))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mbox_test_message_ops = अणु
	.ग_लिखो	= mbox_test_message_ग_लिखो,
	.पढ़ो	= mbox_test_message_पढ़ो,
	.fasync	= mbox_test_message_fasync,
	.poll	= mbox_test_message_poll,
	.खोलो	= simple_खोलो,
	.llseek	= generic_file_llseek,
पूर्ण;

अटल पूर्णांक mbox_test_add_debugfs(काष्ठा platक्रमm_device *pdev,
				 काष्ठा mbox_test_device *tdev)
अणु
	अगर (!debugfs_initialized())
		वापस 0;

	tdev->root_debugfs_dir = debugfs_create_dir(dev_name(&pdev->dev), शून्य);
	अगर (!tdev->root_debugfs_dir) अणु
		dev_err(&pdev->dev, "Failed to create Mailbox debugfs\n");
		वापस -EINVAL;
	पूर्ण

	debugfs_create_file("message", 0600, tdev->root_debugfs_dir,
			    tdev, &mbox_test_message_ops);

	debugfs_create_file("signal", 0200, tdev->root_debugfs_dir,
			    tdev, &mbox_test_संकेत_ops);

	वापस 0;
पूर्ण

अटल व्योम mbox_test_receive_message(काष्ठा mbox_client *client, व्योम *message)
अणु
	काष्ठा mbox_test_device *tdev = dev_get_drvdata(client->dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tdev->lock, flags);
	अगर (tdev->rx_mmio) अणु
		स_नकल_fromio(tdev->rx_buffer, tdev->rx_mmio, MBOX_MAX_MSG_LEN);
		prपूर्णांक_hex_dump_bytes("Client: Received [MMIO]: ", DUMP_PREFIX_ADDRESS,
				     tdev->rx_buffer, MBOX_MAX_MSG_LEN);
	पूर्ण अन्यथा अगर (message) अणु
		prपूर्णांक_hex_dump_bytes("Client: Received [API]: ", DUMP_PREFIX_ADDRESS,
				     message, MBOX_MAX_MSG_LEN);
		स_नकल(tdev->rx_buffer, message, MBOX_MAX_MSG_LEN);
	पूर्ण
	mbox_data_पढ़ोy = true;
	spin_unlock_irqrestore(&tdev->lock, flags);

	wake_up_पूर्णांकerruptible(&tdev->रुकोq);

	समाप्त_fasync(&tdev->async_queue, SIGIO, POLL_IN);
पूर्ण

अटल व्योम mbox_test_prepare_message(काष्ठा mbox_client *client, व्योम *message)
अणु
	काष्ठा mbox_test_device *tdev = dev_get_drvdata(client->dev);

	अगर (tdev->tx_mmio) अणु
		अगर (tdev->संकेत)
			स_नकल_toio(tdev->tx_mmio, tdev->message, MBOX_MAX_MSG_LEN);
		अन्यथा
			स_नकल_toio(tdev->tx_mmio, message, MBOX_MAX_MSG_LEN);
	पूर्ण
पूर्ण

अटल व्योम mbox_test_message_sent(काष्ठा mbox_client *client,
				   व्योम *message, पूर्णांक r)
अणु
	अगर (r)
		dev_warn(client->dev,
			 "Client: Message could not be sent: %d\n", r);
	अन्यथा
		dev_info(client->dev,
			 "Client: Message sent\n");
पूर्ण

अटल काष्ठा mbox_chan *
mbox_test_request_channel(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name)
अणु
	काष्ठा mbox_client *client;
	काष्ठा mbox_chan *channel;

	client = devm_kzalloc(&pdev->dev, माप(*client), GFP_KERNEL);
	अगर (!client)
		वापस ERR_PTR(-ENOMEM);

	client->dev		= &pdev->dev;
	client->rx_callback	= mbox_test_receive_message;
	client->tx_prepare	= mbox_test_prepare_message;
	client->tx_करोne		= mbox_test_message_sent;
	client->tx_block	= true;
	client->knows_txकरोne	= false;
	client->tx_tout		= 500;

	channel = mbox_request_channel_byname(client, name);
	अगर (IS_ERR(channel)) अणु
		dev_warn(&pdev->dev, "Failed to request %s channel\n", name);
		वापस शून्य;
	पूर्ण

	वापस channel;
पूर्ण

अटल पूर्णांक mbox_test_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mbox_test_device *tdev;
	काष्ठा resource *res;
	resource_माप_प्रकार size;
	पूर्णांक ret;

	tdev = devm_kzalloc(&pdev->dev, माप(*tdev), GFP_KERNEL);
	अगर (!tdev)
		वापस -ENOMEM;

	/* It's okay क्रम MMIO to be शून्य */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tdev->tx_mmio = devm_ioremap_resource(&pdev->dev, res);
	अगर (PTR_ERR(tdev->tx_mmio) == -EBUSY) अणु
		/* अगर reserved area in SRAM, try just ioremap */
		size = resource_size(res);
		tdev->tx_mmio = devm_ioremap(&pdev->dev, res->start, size);
	पूर्ण अन्यथा अगर (IS_ERR(tdev->tx_mmio)) अणु
		tdev->tx_mmio = शून्य;
	पूर्ण

	/* If specअगरied, second reg entry is Rx MMIO */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	tdev->rx_mmio = devm_ioremap_resource(&pdev->dev, res);
	अगर (PTR_ERR(tdev->rx_mmio) == -EBUSY) अणु
		size = resource_size(res);
		tdev->rx_mmio = devm_ioremap(&pdev->dev, res->start, size);
	पूर्ण अन्यथा अगर (IS_ERR(tdev->rx_mmio)) अणु
		tdev->rx_mmio = tdev->tx_mmio;
	पूर्ण

	tdev->tx_channel = mbox_test_request_channel(pdev, "tx");
	tdev->rx_channel = mbox_test_request_channel(pdev, "rx");

	अगर (!tdev->tx_channel && !tdev->rx_channel)
		वापस -EPROBE_DEFER;

	/* If Rx is not specअगरied but has Rx MMIO, then Rx = Tx */
	अगर (!tdev->rx_channel && (tdev->rx_mmio != tdev->tx_mmio))
		tdev->rx_channel = tdev->tx_channel;

	tdev->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, tdev);

	spin_lock_init(&tdev->lock);

	अगर (tdev->rx_channel) अणु
		tdev->rx_buffer = devm_kzalloc(&pdev->dev,
					       MBOX_MAX_MSG_LEN, GFP_KERNEL);
		अगर (!tdev->rx_buffer)
			वापस -ENOMEM;
	पूर्ण

	ret = mbox_test_add_debugfs(pdev, tdev);
	अगर (ret)
		वापस ret;

	init_रुकोqueue_head(&tdev->रुकोq);
	dev_info(&pdev->dev, "Successfully registered\n");

	वापस 0;
पूर्ण

अटल पूर्णांक mbox_test_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mbox_test_device *tdev = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(tdev->root_debugfs_dir);

	अगर (tdev->tx_channel)
		mbox_मुक्त_channel(tdev->tx_channel);
	अगर (tdev->rx_channel)
		mbox_मुक्त_channel(tdev->rx_channel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mbox_test_match[] = अणु
	अणु .compatible = "mailbox-test" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mbox_test_match);

अटल काष्ठा platक्रमm_driver mbox_test_driver = अणु
	.driver = अणु
		.name = "mailbox_test",
		.of_match_table = mbox_test_match,
	पूर्ण,
	.probe  = mbox_test_probe,
	.हटाओ = mbox_test_हटाओ,
पूर्ण;
module_platक्रमm_driver(mbox_test_driver);

MODULE_DESCRIPTION("Generic Mailbox Testing Facility");
MODULE_AUTHOR("Lee Jones <lee.jones@linaro.org");
MODULE_LICENSE("GPL v2");
