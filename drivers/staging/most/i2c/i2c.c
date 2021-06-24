<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * i2c.c - Hardware Dependent Module क्रम I2C Interface
 *
 * Copyright (C) 2013-2015, Microchip Technology Germany II GmbH & Co. KG
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/most.h>

क्रमागत अणु CH_RX, CH_TX, NUM_CHANNELS पूर्ण;

#घोषणा MAX_BUFFERS_CONTROL 32
#घोषणा MAX_BUF_SIZE_CONTROL 256

/**
 * list_first_mbo - get the first mbo from a list
 * @ptr:	the list head to take the mbo from.
 */
#घोषणा list_first_mbo(ptr) \
	list_first_entry(ptr, काष्ठा mbo, list)

अटल अचिन्हित पूर्णांक polling_rate;
module_param(polling_rate, uपूर्णांक, 0644);
MODULE_PARM_DESC(polling_rate, "Polling rate [Hz]. Default = 0 (use IRQ)");

काष्ठा hdm_i2c अणु
	काष्ठा most_पूर्णांकerface most_अगरace;
	काष्ठा most_channel_capability capabilities[NUM_CHANNELS];
	काष्ठा i2c_client *client;
	काष्ठा rx अणु
		काष्ठा delayed_work dwork;
		काष्ठा list_head list;
		bool पूर्णांक_disabled;
		अचिन्हित पूर्णांक delay;
	पूर्ण rx;
	अक्षर name[64];
पूर्ण;

#घोषणा to_hdm(अगरace) container_of(अगरace, काष्ठा hdm_i2c, most_अगरace)

अटल irqवापस_t most_irq_handler(पूर्णांक, व्योम *);
अटल व्योम pending_rx_work(काष्ठा work_काष्ठा *);

/**
 * configure_channel - called from MOST core to configure a channel
 * @अगरace: पूर्णांकerface the channel beदीर्घs to
 * @channel: channel to be configured
 * @channel_config: काष्ठाure that holds the configuration inक्रमmation
 *
 * Return 0 on success, negative on failure.
 *
 * Receives configuration inक्रमmation from MOST core and initialize the
 * corresponding channel.
 */
अटल पूर्णांक configure_channel(काष्ठा most_पूर्णांकerface *most_अगरace,
			     पूर्णांक ch_idx,
			     काष्ठा most_channel_config *channel_config)
अणु
	पूर्णांक ret;
	काष्ठा hdm_i2c *dev = to_hdm(most_अगरace);
	अचिन्हित पूर्णांक delay, pr;

	BUG_ON(ch_idx < 0 || ch_idx >= NUM_CHANNELS);

	अगर (channel_config->data_type != MOST_CH_CONTROL) अणु
		pr_err("bad data type for channel %d\n", ch_idx);
		वापस -EPERM;
	पूर्ण

	अगर (channel_config->direction != dev->capabilities[ch_idx].direction) अणु
		pr_err("bad direction for channel %d\n", ch_idx);
		वापस -EPERM;
	पूर्ण

	अगर (channel_config->direction == MOST_CH_RX) अणु
		अगर (!polling_rate) अणु
			अगर (dev->client->irq <= 0) अणु
				pr_err("bad irq: %d\n", dev->client->irq);
				वापस -ENOENT;
			पूर्ण
			dev->rx.पूर्णांक_disabled = false;
			ret = request_irq(dev->client->irq, most_irq_handler, 0,
					  dev->client->name, dev);
			अगर (ret) अणु
				pr_err("request_irq(%d) failed: %d\n",
				       dev->client->irq, ret);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			delay = msecs_to_jअगरfies(MSEC_PER_SEC / polling_rate);
			dev->rx.delay = delay ? delay : 1;
			pr = MSEC_PER_SEC / jअगरfies_to_msecs(dev->rx.delay);
			pr_info("polling rate is %u Hz\n", pr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * enqueue - called from MOST core to enqueue a buffer क्रम data transfer
 * @अगरace: पूर्णांकended पूर्णांकerface
 * @channel: ID of the channel the buffer is पूर्णांकended क्रम
 * @mbo: poपूर्णांकer to the buffer object
 *
 * Return 0 on success, negative on failure.
 *
 * Transmit the data over I2C अगर it is a "write" request or push the buffer पूर्णांकo
 * list अगर it is an "read" request
 */
अटल पूर्णांक enqueue(काष्ठा most_पूर्णांकerface *most_अगरace,
		   पूर्णांक ch_idx, काष्ठा mbo *mbo)
अणु
	काष्ठा hdm_i2c *dev = to_hdm(most_अगरace);
	पूर्णांक ret;

	BUG_ON(ch_idx < 0 || ch_idx >= NUM_CHANNELS);

	अगर (ch_idx == CH_RX) अणु
		/* RX */
		अगर (!polling_rate)
			disable_irq(dev->client->irq);
		cancel_delayed_work_sync(&dev->rx.dwork);
		list_add_tail(&mbo->list, &dev->rx.list);
		अगर (dev->rx.पूर्णांक_disabled || polling_rate)
			pending_rx_work(&dev->rx.dwork.work);
		अगर (!polling_rate)
			enable_irq(dev->client->irq);
	पूर्ण अन्यथा अणु
		/* TX */
		ret = i2c_master_send(dev->client, mbo->virt_address,
				      mbo->buffer_length);
		अगर (ret <= 0) अणु
			mbo->processed_length = 0;
			mbo->status = MBO_E_INVAL;
		पूर्ण अन्यथा अणु
			mbo->processed_length = mbo->buffer_length;
			mbo->status = MBO_SUCCESS;
		पूर्ण
		mbo->complete(mbo);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * poison_channel - called from MOST core to poison buffers of a channel
 * @अगरace: poपूर्णांकer to the पूर्णांकerface the channel to be poisoned beदीर्घs to
 * @channel_id: corresponding channel ID
 *
 * Return 0 on success, negative on failure.
 *
 * If channel direction is RX, complete the buffers in list with
 * status MBO_E_CLOSE
 */
अटल पूर्णांक poison_channel(काष्ठा most_पूर्णांकerface *most_अगरace,
			  पूर्णांक ch_idx)
अणु
	काष्ठा hdm_i2c *dev = to_hdm(most_अगरace);
	काष्ठा mbo *mbo;

	BUG_ON(ch_idx < 0 || ch_idx >= NUM_CHANNELS);

	अगर (ch_idx == CH_RX) अणु
		अगर (!polling_rate)
			मुक्त_irq(dev->client->irq, dev);
		cancel_delayed_work_sync(&dev->rx.dwork);

		जबतक (!list_empty(&dev->rx.list)) अणु
			mbo = list_first_mbo(&dev->rx.list);
			list_del(&mbo->list);

			mbo->processed_length = 0;
			mbo->status = MBO_E_CLOSE;
			mbo->complete(mbo);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम करो_rx_work(काष्ठा hdm_i2c *dev)
अणु
	काष्ठा mbo *mbo;
	अचिन्हित अक्षर msg[MAX_BUF_SIZE_CONTROL];
	पूर्णांक ret;
	u16 pml, data_size;

	/* Read PML (2 bytes) */
	ret = i2c_master_recv(dev->client, msg, 2);
	अगर (ret <= 0) अणु
		pr_err("Failed to receive PML\n");
		वापस;
	पूर्ण

	pml = (msg[0] << 8) | msg[1];
	अगर (!pml)
		वापस;

	data_size = pml + 2;

	/* Read the whole message, including PML */
	ret = i2c_master_recv(dev->client, msg, data_size);
	अगर (ret <= 0) अणु
		pr_err("Failed to receive a Port Message\n");
		वापस;
	पूर्ण

	mbo = list_first_mbo(&dev->rx.list);
	list_del(&mbo->list);

	mbo->processed_length = min(data_size, mbo->buffer_length);
	स_नकल(mbo->virt_address, msg, mbo->processed_length);
	mbo->status = MBO_SUCCESS;
	mbo->complete(mbo);
पूर्ण

/**
 * pending_rx_work - Read pending messages through I2C
 * @work: definition of this work item
 *
 * Invoked by the Interrupt Service Routine, most_irq_handler()
 */
अटल व्योम pending_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdm_i2c *dev = container_of(work, काष्ठा hdm_i2c, rx.dwork.work);

	अगर (list_empty(&dev->rx.list))
		वापस;

	करो_rx_work(dev);

	अगर (polling_rate) अणु
		schedule_delayed_work(&dev->rx.dwork, dev->rx.delay);
	पूर्ण अन्यथा अणु
		dev->rx.पूर्णांक_disabled = false;
		enable_irq(dev->client->irq);
	पूर्ण
पूर्ण

/*
 * most_irq_handler - Interrupt Service Routine
 * @irq: irq number
 * @_dev: निजी data
 *
 * Schedules a delayed work
 *
 * By शेष the पूर्णांकerrupt line behavior is Active Low. Once an पूर्णांकerrupt is
 * generated by the device, until driver clears the पूर्णांकerrupt (by पढ़ोing
 * the PMP message), device keeps the पूर्णांकerrupt line in low state. Since i2c
 * पढ़ो is करोne in work queue, the पूर्णांकerrupt line must be disabled temporarily
 * to aव्योम ISR being called repeatedly. Re-enable the पूर्णांकerrupt in workqueue,
 * after पढ़ोing the message.
 *
 * Note: If we use the पूर्णांकerrupt line in Falling edge mode, there is a
 * possibility to miss पूर्णांकerrupts when ISR is getting executed.
 *
 */
अटल irqवापस_t most_irq_handler(पूर्णांक irq, व्योम *_dev)
अणु
	काष्ठा hdm_i2c *dev = _dev;

	disable_irq_nosync(irq);
	dev->rx.पूर्णांक_disabled = true;
	schedule_delayed_work(&dev->rx.dwork, 0);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * i2c_probe - i2c probe handler
 * @client: i2c client device काष्ठाure
 * @id: i2c client device id
 *
 * Return 0 on success, negative on failure.
 *
 * Register the i2c client device as a MOST पूर्णांकerface
 */
अटल पूर्णांक i2c_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा hdm_i2c *dev;
	पूर्णांक ret, i;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* ID क्रमmat: i2c-<bus>-<address> */
	snम_लिखो(dev->name, माप(dev->name), "i2c-%d-%04x",
		 client->adapter->nr, client->addr);

	क्रम (i = 0; i < NUM_CHANNELS; i++) अणु
		dev->capabilities[i].data_type = MOST_CH_CONTROL;
		dev->capabilities[i].num_buffers_packet = MAX_BUFFERS_CONTROL;
		dev->capabilities[i].buffer_size_packet = MAX_BUF_SIZE_CONTROL;
	पूर्ण
	dev->capabilities[CH_RX].direction = MOST_CH_RX;
	dev->capabilities[CH_RX].name_suffix = "rx";
	dev->capabilities[CH_TX].direction = MOST_CH_TX;
	dev->capabilities[CH_TX].name_suffix = "tx";

	dev->most_अगरace.पूर्णांकerface = ITYPE_I2C;
	dev->most_अगरace.description = dev->name;
	dev->most_अगरace.num_channels = NUM_CHANNELS;
	dev->most_अगरace.channel_vector = dev->capabilities;
	dev->most_अगरace.configure = configure_channel;
	dev->most_अगरace.enqueue = enqueue;
	dev->most_अगरace.poison_channel = poison_channel;

	INIT_LIST_HEAD(&dev->rx.list);

	INIT_DELAYED_WORK(&dev->rx.dwork, pending_rx_work);

	dev->client = client;
	i2c_set_clientdata(client, dev);

	ret = most_रेजिस्टर_पूर्णांकerface(&dev->most_अगरace);
	अगर (ret) अणु
		pr_err("Failed to register i2c as a MOST interface\n");
		kमुक्त(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * i2c_हटाओ - i2c हटाओ handler
 * @client: i2c client device काष्ठाure
 *
 * Return 0 on success.
 *
 * Unरेजिस्टर the i2c client device as a MOST पूर्णांकerface
 */
अटल पूर्णांक i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा hdm_i2c *dev = i2c_get_clientdata(client);

	most_deरेजिस्टर_पूर्णांकerface(&dev->most_अगरace);
	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id i2c_id[] = अणु
	अणु "most_i2c", 0 पूर्ण,
	अणु पूर्ण, /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(i2c, i2c_id);

अटल काष्ठा i2c_driver i2c_driver = अणु
	.driver = अणु
		.name = "hdm_i2c",
	पूर्ण,
	.probe = i2c_probe,
	.हटाओ = i2c_हटाओ,
	.id_table = i2c_id,
पूर्ण;

module_i2c_driver(i2c_driver);

MODULE_AUTHOR("Andrey Shvetsov <andrey.shvetsov@k2l.de>");
MODULE_DESCRIPTION("I2C Hardware Dependent Module");
MODULE_LICENSE("GPL");
