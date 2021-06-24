<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments' Message Manager Driver
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - https://www.ti.com/
 *	Nishanth Menon
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/ti/ti-msgmgr.h>

#घोषणा Q_DATA_OFFSET(proxy, queue, reg)	\
		     ((0x10000 * (proxy)) + (0x80 * (queue)) + ((reg) * 4))
#घोषणा Q_STATE_OFFSET(queue)			((queue) * 0x4)
#घोषणा Q_STATE_ENTRY_COUNT_MASK		(0xFFF000)

#घोषणा SPROXY_THREAD_OFFSET(tid) (0x1000 * (tid))
#घोषणा SPROXY_THREAD_DATA_OFFSET(tid, reg) \
	(SPROXY_THREAD_OFFSET(tid) + ((reg) * 0x4) + 0x4)

#घोषणा SPROXY_THREAD_STATUS_OFFSET(tid) (SPROXY_THREAD_OFFSET(tid))

#घोषणा SPROXY_THREAD_STATUS_COUNT_MASK (0xFF)

#घोषणा SPROXY_THREAD_CTRL_OFFSET(tid) (0x1000 + SPROXY_THREAD_OFFSET(tid))
#घोषणा SPROXY_THREAD_CTRL_सूची_MASK (0x1 << 31)

/**
 * काष्ठा ti_msgmgr_valid_queue_desc - SoC valid queues meant क्रम this processor
 * @queue_id:	Queue Number क्रम this path
 * @proxy_id:	Proxy ID representing the processor in SoC
 * @is_tx:	Is this a receive path?
 */
काष्ठा ti_msgmgr_valid_queue_desc अणु
	u8 queue_id;
	u8 proxy_id;
	bool is_tx;
पूर्ण;

/**
 * काष्ठा ti_msgmgr_desc - Description of message manager पूर्णांकegration
 * @queue_count:	Number of Queues
 * @max_message_size:	Message size in bytes
 * @max_messages:	Number of messages
 * @data_first_reg:	First data रेजिस्टर क्रम proxy data region
 * @data_last_reg:	Last data रेजिस्टर क्रम proxy data region
 * @status_cnt_mask:	Mask क्रम getting the status value
 * @status_err_mask:	Mask क्रम getting the error value, अगर applicable
 * @tx_polled:		Do I need to use polled mechanism क्रम tx
 * @tx_poll_समयout_ms: Timeout in ms अगर polled
 * @valid_queues:	List of Valid queues that the processor can access
 * @data_region_name:	Name of the proxy data region
 * @status_region_name:	Name of the proxy status region
 * @ctrl_region_name:	Name of the proxy control region
 * @num_valid_queues:	Number of valid queues
 * @is_sproxy:		Is this an Secure Proxy instance?
 *
 * This काष्ठाure is used in of match data to describe how पूर्णांकegration
 * क्रम a specअगरic compatible SoC is करोne.
 */
काष्ठा ti_msgmgr_desc अणु
	u8 queue_count;
	u8 max_message_size;
	u8 max_messages;
	u8 data_first_reg;
	u8 data_last_reg;
	u32 status_cnt_mask;
	u32 status_err_mask;
	bool tx_polled;
	पूर्णांक tx_poll_समयout_ms;
	स्थिर काष्ठा ti_msgmgr_valid_queue_desc *valid_queues;
	स्थिर अक्षर *data_region_name;
	स्थिर अक्षर *status_region_name;
	स्थिर अक्षर *ctrl_region_name;
	पूर्णांक num_valid_queues;
	bool is_sproxy;
पूर्ण;

/**
 * काष्ठा ti_queue_inst - Description of a queue instance
 * @name:	Queue Name
 * @queue_id:	Queue Identअगरier as mapped on SoC
 * @proxy_id:	Proxy Identअगरier as mapped on SoC
 * @irq:	IRQ क्रम Rx Queue
 * @is_tx:	'true' if transmit queue, else, 'false'
 * @queue_buff_start: First रेजिस्टर of Data Buffer
 * @queue_buff_end: Last (or confirmation) रेजिस्टर of Data buffer
 * @queue_state: Queue status रेजिस्टर
 * @queue_ctrl: Queue Control रेजिस्टर
 * @chan:	Mailbox channel
 * @rx_buff:	Receive buffer poपूर्णांकer allocated at probe, max_message_size
 */
काष्ठा ti_queue_inst अणु
	अक्षर name[30];
	u8 queue_id;
	u8 proxy_id;
	पूर्णांक irq;
	bool is_tx;
	व्योम __iomem *queue_buff_start;
	व्योम __iomem *queue_buff_end;
	व्योम __iomem *queue_state;
	व्योम __iomem *queue_ctrl;
	काष्ठा mbox_chan *chan;
	u32 *rx_buff;
पूर्ण;

/**
 * काष्ठा ti_msgmgr_inst - Description of a Message Manager Instance
 * @dev:	device poपूर्णांकer corresponding to the Message Manager instance
 * @desc:	Description of the SoC पूर्णांकegration
 * @queue_proxy_region:	Queue proxy region where queue buffers are located
 * @queue_state_debug_region:	Queue status रेजिस्टर regions
 * @queue_ctrl_region:	Queue Control रेजिस्टर regions
 * @num_valid_queues:	Number of valid queues defined क्रम the processor
 *		Note: other queues are probably reserved क्रम other processors
 *		in the SoC.
 * @qinsts:	Array of valid Queue Instances क्रम the Processor
 * @mbox:	Mailbox Controller
 * @chans:	Array क्रम channels corresponding to the Queue Instances.
 */
काष्ठा ti_msgmgr_inst अणु
	काष्ठा device *dev;
	स्थिर काष्ठा ti_msgmgr_desc *desc;
	व्योम __iomem *queue_proxy_region;
	व्योम __iomem *queue_state_debug_region;
	व्योम __iomem *queue_ctrl_region;
	u8 num_valid_queues;
	काष्ठा ti_queue_inst *qinsts;
	काष्ठा mbox_controller mbox;
	काष्ठा mbox_chan *chans;
पूर्ण;

/**
 * ti_msgmgr_queue_get_num_messages() - Get the number of pending messages
 * @d:		Description of message manager
 * @qinst:	Queue instance क्रम which we check the number of pending messages
 *
 * Return: number of messages pending in the queue (0 == no pending messages)
 */
अटल अंतरभूत पूर्णांक
ti_msgmgr_queue_get_num_messages(स्थिर काष्ठा ti_msgmgr_desc *d,
				 काष्ठा ti_queue_inst *qinst)
अणु
	u32 val;
	u32 status_cnt_mask = d->status_cnt_mask;

	/*
	 * We cannot use relaxed operation here - update may happen
	 * real-समय.
	 */
	val = पढ़ोl(qinst->queue_state) & status_cnt_mask;
	val >>= __ffs(status_cnt_mask);

	वापस val;
पूर्ण

/**
 * ti_msgmgr_queue_is_error() - Check to see अगर there is queue error
 * @d:		Description of message manager
 * @qinst:	Queue instance क्रम which we check the number of pending messages
 *
 * Return: true अगर error, अन्यथा false
 */
अटल अंतरभूत bool ti_msgmgr_queue_is_error(स्थिर काष्ठा ti_msgmgr_desc *d,
					    काष्ठा ti_queue_inst *qinst)
अणु
	u32 val;

	/* Msgmgr has no error detection */
	अगर (!d->is_sproxy)
		वापस false;

	/*
	 * We cannot use relaxed operation here - update may happen
	 * real-समय.
	 */
	val = पढ़ोl(qinst->queue_state) & d->status_err_mask;

	वापस val ? true : false;
पूर्ण

/**
 * ti_msgmgr_queue_rx_पूर्णांकerrupt() - Interrupt handler क्रम receive Queue
 * @irq:	Interrupt number
 * @p:		Channel Poपूर्णांकer
 *
 * Return: -EINVAL अगर there is no instance
 * IRQ_NONE अगर the पूर्णांकerrupt is not ours.
 * IRQ_HANDLED अगर the rx पूर्णांकerrupt was successfully handled.
 */
अटल irqवापस_t ti_msgmgr_queue_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा mbox_chan *chan = p;
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा ti_msgmgr_inst *inst = dev_get_drvdata(dev);
	काष्ठा ti_queue_inst *qinst = chan->con_priv;
	स्थिर काष्ठा ti_msgmgr_desc *desc;
	पूर्णांक msg_count, num_words;
	काष्ठा ti_msgmgr_message message;
	व्योम __iomem *data_reg;
	u32 *word_data;

	अगर (WARN_ON(!inst)) अणु
		dev_err(dev, "no platform drv data??\n");
		वापस -EINVAL;
	पूर्ण

	/* Do I have an invalid पूर्णांकerrupt source? */
	अगर (qinst->is_tx) अणु
		dev_err(dev, "Cannot handle rx interrupt on tx channel %s\n",
			qinst->name);
		वापस IRQ_NONE;
	पूर्ण

	desc = inst->desc;
	अगर (ti_msgmgr_queue_is_error(desc, qinst)) अणु
		dev_err(dev, "Error on Rx channel %s\n", qinst->name);
		वापस IRQ_NONE;
	पूर्ण

	/* Do I actually have messages to पढ़ो? */
	msg_count = ti_msgmgr_queue_get_num_messages(desc, qinst);
	अगर (!msg_count) अणु
		/* Shared IRQ? */
		dev_dbg(dev, "Spurious event - 0 pending data!\n");
		वापस IRQ_NONE;
	पूर्ण

	/*
	 * I have no idea about the protocol being used to communicate with the
	 * remote producer - 0 could be valid data, so I won't make a judgement
	 * of how many bytes I should be पढ़ोing. Let the client figure this
	 * out.. I just पढ़ो the full message and pass it on..
	 */
	message.len = desc->max_message_size;
	message.buf = (u8 *)qinst->rx_buff;

	/*
	 * NOTE about रेजिस्टर access involved here:
	 * the hardware block is implemented with 32bit access operations and no
	 * support क्रम data splitting.  We करोn't want the hardware to misbehave
	 * with sub 32bit access - For example: अगर the last रेजिस्टर पढ़ो is
	 * split पूर्णांकo byte wise access, it can result in the queue getting
	 * stuck or indeterminate behavior. An out of order पढ़ो operation may
	 * result in weird data results as well.
	 * Hence, we करो not use स_नकल_fromio or __ioपढ़ो32_copy here, instead
	 * we depend on पढ़ोl क्रम the purpose.
	 *
	 * Also note that the final रेजिस्टर पढ़ो स्वतःmatically marks the
	 * queue message as पढ़ो.
	 */
	क्रम (data_reg = qinst->queue_buff_start, word_data = qinst->rx_buff,
	     num_words = (desc->max_message_size / माप(u32));
	     num_words; num_words--, data_reg += माप(u32), word_data++)
		*word_data = पढ़ोl(data_reg);

	/*
	 * Last रेजिस्टर पढ़ो स्वतःmatically clears the IRQ अगर only 1 message
	 * is pending - so send the data up the stack..
	 * NOTE: Client is expected to be as optimal as possible, since
	 * we invoke the handler in IRQ context.
	 */
	mbox_chan_received_data(chan, (व्योम *)&message);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ti_msgmgr_queue_peek_data() - Peek to see अगर there are any rx messages.
 * @chan:	Channel Poपूर्णांकer
 *
 * Return: 'true' if there is pending rx data, 'false' अगर there is none.
 */
अटल bool ti_msgmgr_queue_peek_data(काष्ठा mbox_chan *chan)
अणु
	काष्ठा ti_queue_inst *qinst = chan->con_priv;
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा ti_msgmgr_inst *inst = dev_get_drvdata(dev);
	स्थिर काष्ठा ti_msgmgr_desc *desc = inst->desc;
	पूर्णांक msg_count;

	अगर (qinst->is_tx)
		वापस false;

	अगर (ti_msgmgr_queue_is_error(desc, qinst)) अणु
		dev_err(dev, "Error on channel %s\n", qinst->name);
		वापस false;
	पूर्ण

	msg_count = ti_msgmgr_queue_get_num_messages(desc, qinst);

	वापस msg_count ? true : false;
पूर्ण

/**
 * ti_msgmgr_last_tx_करोne() - See अगर all the tx messages are sent
 * @chan:	Channel poपूर्णांकer
 *
 * Return: 'true' is no pending tx data, 'false' अगर there are any.
 */
अटल bool ti_msgmgr_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा ti_queue_inst *qinst = chan->con_priv;
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा ti_msgmgr_inst *inst = dev_get_drvdata(dev);
	स्थिर काष्ठा ti_msgmgr_desc *desc = inst->desc;
	पूर्णांक msg_count;

	अगर (!qinst->is_tx)
		वापस false;

	अगर (ti_msgmgr_queue_is_error(desc, qinst)) अणु
		dev_err(dev, "Error on channel %s\n", qinst->name);
		वापस false;
	पूर्ण

	msg_count = ti_msgmgr_queue_get_num_messages(desc, qinst);

	अगर (desc->is_sproxy) अणु
		/* In secure proxy, msg_count indicates how many we can send */
		वापस msg_count ? true : false;
	पूर्ण

	/* अगर we have any messages pending.. */
	वापस msg_count ? false : true;
पूर्ण

/**
 * ti_msgmgr_send_data() - Send data
 * @chan:	Channel Poपूर्णांकer
 * @data:	ti_msgmgr_message * Message Poपूर्णांकer
 *
 * Return: 0 अगर all goes good, अन्यथा appropriate error messages.
 */
अटल पूर्णांक ti_msgmgr_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा ti_msgmgr_inst *inst = dev_get_drvdata(dev);
	स्थिर काष्ठा ti_msgmgr_desc *desc;
	काष्ठा ti_queue_inst *qinst = chan->con_priv;
	पूर्णांक num_words, trail_bytes;
	काष्ठा ti_msgmgr_message *message = data;
	व्योम __iomem *data_reg;
	u32 *word_data;

	अगर (WARN_ON(!inst)) अणु
		dev_err(dev, "no platform drv data??\n");
		वापस -EINVAL;
	पूर्ण
	desc = inst->desc;

	अगर (ti_msgmgr_queue_is_error(desc, qinst)) अणु
		dev_err(dev, "Error on channel %s\n", qinst->name);
		वापस false;
	पूर्ण

	अगर (desc->max_message_size < message->len) अणु
		dev_err(dev, "Queue %s message length %zu > max %d\n",
			qinst->name, message->len, desc->max_message_size);
		वापस -EINVAL;
	पूर्ण

	/* NOTE: Constraपूर्णांकs similar to rx path exists here as well */
	क्रम (data_reg = qinst->queue_buff_start,
	     num_words = message->len / माप(u32),
	     word_data = (u32 *)message->buf;
	     num_words; num_words--, data_reg += माप(u32), word_data++)
		ग_लिखोl(*word_data, data_reg);

	trail_bytes = message->len % माप(u32);
	अगर (trail_bytes) अणु
		u32 data_trail = *word_data;

		/* Ensure all unused data is 0 */
		data_trail &= 0xFFFFFFFF >> (8 * (माप(u32) - trail_bytes));
		ग_लिखोl(data_trail, data_reg);
		data_reg++;
	पूर्ण
	/*
	 * 'data_reg' indicates next रेजिस्टर to ग_लिखो. If we did not alपढ़ोy
	 * ग_लिखो on tx complete reg(last reg), we must करो so क्रम transmit
	 */
	अगर (data_reg <= qinst->queue_buff_end)
		ग_लिखोl(0, qinst->queue_buff_end);

	वापस 0;
पूर्ण

/**
 *  ti_msgmgr_queue_rx_irq_req() - RX IRQ request
 *  @dev:	device poपूर्णांकer
 *  @d:		descriptor क्रम ti_msgmgr
 *  @qinst:	Queue instance
 *  @chan:	Channel poपूर्णांकer
 */
अटल पूर्णांक ti_msgmgr_queue_rx_irq_req(काष्ठा device *dev,
				      स्थिर काष्ठा ti_msgmgr_desc *d,
				      काष्ठा ti_queue_inst *qinst,
				      काष्ठा mbox_chan *chan)
अणु
	पूर्णांक ret = 0;
	अक्षर of_rx_irq_name[7];
	काष्ठा device_node *np;

	snम_लिखो(of_rx_irq_name, माप(of_rx_irq_name),
		 "rx_%03d", d->is_sproxy ? qinst->proxy_id : qinst->queue_id);

	/* Get the IRQ अगर not found */
	अगर (qinst->irq < 0) अणु
		np = of_node_get(dev->of_node);
		अगर (!np)
			वापस -ENODATA;
		qinst->irq = of_irq_get_byname(np, of_rx_irq_name);
		of_node_put(np);

		अगर (qinst->irq < 0) अणु
			dev_err(dev,
				"QID %d PID %d:No IRQ[%s]: %d\n",
				qinst->queue_id, qinst->proxy_id,
				of_rx_irq_name, qinst->irq);
			वापस qinst->irq;
		पूर्ण
	पूर्ण

	/* With the expectation that the IRQ might be shared in SoC */
	ret = request_irq(qinst->irq, ti_msgmgr_queue_rx_पूर्णांकerrupt,
			  IRQF_SHARED, qinst->name, chan);
	अगर (ret) अणु
		dev_err(dev, "Unable to get IRQ %d on %s(res=%d)\n",
			qinst->irq, qinst->name, ret);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ti_msgmgr_queue_startup() - Startup queue
 * @chan:	Channel poपूर्णांकer
 *
 * Return: 0 अगर all goes good, अन्यथा वापस corresponding error message
 */
अटल पूर्णांक ti_msgmgr_queue_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा ti_msgmgr_inst *inst = dev_get_drvdata(dev);
	काष्ठा ti_queue_inst *qinst = chan->con_priv;
	स्थिर काष्ठा ti_msgmgr_desc *d = inst->desc;
	पूर्णांक ret;
	पूर्णांक msg_count;

	/*
	 * If sproxy is starting and can send messages, we are a Tx thपढ़ो,
	 * अन्यथा Rx
	 */
	अगर (d->is_sproxy) अणु
		qinst->is_tx = (पढ़ोl(qinst->queue_ctrl) &
				SPROXY_THREAD_CTRL_सूची_MASK) ? false : true;

		msg_count = ti_msgmgr_queue_get_num_messages(d, qinst);

		अगर (!msg_count && qinst->is_tx) अणु
			dev_err(dev, "%s: Cannot transmit with 0 credits!\n",
				qinst->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!qinst->is_tx) अणु
		/* Allocate usage buffer क्रम rx */
		qinst->rx_buff = kzalloc(d->max_message_size, GFP_KERNEL);
		अगर (!qinst->rx_buff)
			वापस -ENOMEM;
		/* Request IRQ */
		ret = ti_msgmgr_queue_rx_irq_req(dev, d, qinst, chan);
		अगर (ret) अणु
			kमुक्त(qinst->rx_buff);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ti_msgmgr_queue_shutकरोwn() - Shutकरोwn the queue
 * @chan:	Channel poपूर्णांकer
 */
अटल व्योम ti_msgmgr_queue_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा ti_queue_inst *qinst = chan->con_priv;

	अगर (!qinst->is_tx) अणु
		मुक्त_irq(qinst->irq, chan);
		kमुक्त(qinst->rx_buff);
	पूर्ण
पूर्ण

/**
 * ti_msgmgr_of_xlate() - Translation of phandle to queue
 * @mbox:	Mailbox controller
 * @p:		phandle poपूर्णांकer
 *
 * Return: Mailbox channel corresponding to the queue, अन्यथा वापस error
 * poपूर्णांकer.
 */
अटल काष्ठा mbox_chan *ti_msgmgr_of_xlate(काष्ठा mbox_controller *mbox,
					    स्थिर काष्ठा of_phandle_args *p)
अणु
	काष्ठा ti_msgmgr_inst *inst;
	पूर्णांक req_qid, req_pid;
	काष्ठा ti_queue_inst *qinst;
	स्थिर काष्ठा ti_msgmgr_desc *d;
	पूर्णांक i, ncells;

	inst = container_of(mbox, काष्ठा ti_msgmgr_inst, mbox);
	अगर (WARN_ON(!inst))
		वापस ERR_PTR(-EINVAL);

	d = inst->desc;

	अगर (d->is_sproxy)
		ncells = 1;
	अन्यथा
		ncells = 2;
	अगर (p->args_count != ncells) अणु
		dev_err(inst->dev, "Invalid arguments in dt[%d]. Must be %d\n",
			p->args_count, ncells);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (ncells == 1) अणु
		req_qid = 0;
		req_pid = p->args[0];
	पूर्ण अन्यथा अणु
		req_qid = p->args[0];
		req_pid = p->args[1];
	पूर्ण

	अगर (d->is_sproxy) अणु
		अगर (req_pid >= d->num_valid_queues)
			जाओ err;
		qinst = &inst->qinsts[req_pid];
		वापस qinst->chan;
	पूर्ण

	क्रम (qinst = inst->qinsts, i = 0; i < inst->num_valid_queues;
	     i++, qinst++) अणु
		अगर (req_qid == qinst->queue_id && req_pid == qinst->proxy_id)
			वापस qinst->chan;
	पूर्ण

err:
	dev_err(inst->dev, "Queue ID %d, Proxy ID %d is wrong on %pOFn\n",
		req_qid, req_pid, p->np);
	वापस ERR_PTR(-ENOENT);
पूर्ण

/**
 * ti_msgmgr_queue_setup() - Setup data काष्ठाures क्रम each queue instance
 * @idx:	index of the queue
 * @dev:	poपूर्णांकer to the message manager device
 * @np:		poपूर्णांकer to the of node
 * @inst:	Queue instance poपूर्णांकer
 * @d:		Message Manager instance description data
 * @qd:		Queue description data
 * @qinst:	Queue instance poपूर्णांकer
 * @chan:	poपूर्णांकer to mailbox channel
 *
 * Return: 0 अगर all went well, अन्यथा वापस corresponding error
 */
अटल पूर्णांक ti_msgmgr_queue_setup(पूर्णांक idx, काष्ठा device *dev,
				 काष्ठा device_node *np,
				 काष्ठा ti_msgmgr_inst *inst,
				 स्थिर काष्ठा ti_msgmgr_desc *d,
				 स्थिर काष्ठा ti_msgmgr_valid_queue_desc *qd,
				 काष्ठा ti_queue_inst *qinst,
				 काष्ठा mbox_chan *chan)
अणु
	अक्षर *dir;

	qinst->proxy_id = qd->proxy_id;
	qinst->queue_id = qd->queue_id;

	अगर (qinst->queue_id > d->queue_count) अणु
		dev_err(dev, "Queue Data [idx=%d] queuid %d > %d\n",
			idx, qinst->queue_id, d->queue_count);
		वापस -दुस्फल;
	पूर्ण

	अगर (d->is_sproxy) अणु
		qinst->queue_buff_start = inst->queue_proxy_region +
		    SPROXY_THREAD_DATA_OFFSET(qinst->proxy_id,
					      d->data_first_reg);
		qinst->queue_buff_end = inst->queue_proxy_region +
		    SPROXY_THREAD_DATA_OFFSET(qinst->proxy_id,
					      d->data_last_reg);
		qinst->queue_state = inst->queue_state_debug_region +
		    SPROXY_THREAD_STATUS_OFFSET(qinst->proxy_id);
		qinst->queue_ctrl = inst->queue_ctrl_region +
		    SPROXY_THREAD_CTRL_OFFSET(qinst->proxy_id);

		/* XXX: DONOT पढ़ो रेजिस्टरs here!.. Some may be unusable */
		dir = "thr";
		snम_लिखो(qinst->name, माप(qinst->name), "%s %s_%03d",
			 dev_name(dev), dir, qinst->proxy_id);
	पूर्ण अन्यथा अणु
		qinst->queue_buff_start = inst->queue_proxy_region +
		    Q_DATA_OFFSET(qinst->proxy_id, qinst->queue_id,
				  d->data_first_reg);
		qinst->queue_buff_end = inst->queue_proxy_region +
		    Q_DATA_OFFSET(qinst->proxy_id, qinst->queue_id,
				  d->data_last_reg);
		qinst->queue_state =
		    inst->queue_state_debug_region +
		    Q_STATE_OFFSET(qinst->queue_id);
		qinst->is_tx = qd->is_tx;
		dir = qinst->is_tx ? "tx" : "rx";
		snम_लिखो(qinst->name, माप(qinst->name), "%s %s_%03d_%03d",
			 dev_name(dev), dir, qinst->queue_id, qinst->proxy_id);
	पूर्ण

	qinst->chan = chan;

	/* Setup an error value क्रम IRQ - Lazy allocation */
	qinst->irq = -EINVAL;

	chan->con_priv = qinst;

	dev_dbg(dev, "[%d] qidx=%d pidx=%d irq=%d q_s=%p q_e = %p\n",
		idx, qinst->queue_id, qinst->proxy_id, qinst->irq,
		qinst->queue_buff_start, qinst->queue_buff_end);
	वापस 0;
पूर्ण

/* Queue operations */
अटल स्थिर काष्ठा mbox_chan_ops ti_msgmgr_chan_ops = अणु
	.startup = ti_msgmgr_queue_startup,
	.shutकरोwn = ti_msgmgr_queue_shutकरोwn,
	.peek_data = ti_msgmgr_queue_peek_data,
	.last_tx_करोne = ti_msgmgr_last_tx_करोne,
	.send_data = ti_msgmgr_send_data,
पूर्ण;

/* Keystone K2G SoC पूर्णांकegration details */
अटल स्थिर काष्ठा ti_msgmgr_valid_queue_desc k2g_valid_queues[] = अणु
	अणु.queue_id = 0, .proxy_id = 0, .is_tx = true,पूर्ण,
	अणु.queue_id = 1, .proxy_id = 0, .is_tx = true,पूर्ण,
	अणु.queue_id = 2, .proxy_id = 0, .is_tx = true,पूर्ण,
	अणु.queue_id = 3, .proxy_id = 0, .is_tx = true,पूर्ण,
	अणु.queue_id = 5, .proxy_id = 2, .is_tx = false,पूर्ण,
	अणु.queue_id = 56, .proxy_id = 1, .is_tx = true,पूर्ण,
	अणु.queue_id = 57, .proxy_id = 2, .is_tx = false,पूर्ण,
	अणु.queue_id = 58, .proxy_id = 3, .is_tx = true,पूर्ण,
	अणु.queue_id = 59, .proxy_id = 4, .is_tx = true,पूर्ण,
	अणु.queue_id = 60, .proxy_id = 5, .is_tx = true,पूर्ण,
	अणु.queue_id = 61, .proxy_id = 6, .is_tx = true,पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ti_msgmgr_desc k2g_desc = अणु
	.queue_count = 64,
	.max_message_size = 64,
	.max_messages = 128,
	.data_region_name = "queue_proxy_region",
	.status_region_name = "queue_state_debug_region",
	.data_first_reg = 16,
	.data_last_reg = 31,
	.status_cnt_mask = Q_STATE_ENTRY_COUNT_MASK,
	.tx_polled = false,
	.valid_queues = k2g_valid_queues,
	.num_valid_queues = ARRAY_SIZE(k2g_valid_queues),
	.is_sproxy = false,
पूर्ण;

अटल स्थिर काष्ठा ti_msgmgr_desc am654_desc = अणु
	.queue_count = 190,
	.num_valid_queues = 190,
	.max_message_size = 60,
	.data_region_name = "target_data",
	.status_region_name = "rt",
	.ctrl_region_name = "scfg",
	.data_first_reg = 0,
	.data_last_reg = 14,
	.status_cnt_mask = SPROXY_THREAD_STATUS_COUNT_MASK,
	.tx_polled = false,
	.is_sproxy = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_msgmgr_of_match[] = अणु
	अणु.compatible = "ti,k2g-message-manager", .data = &k2g_descपूर्ण,
	अणु.compatible = "ti,am654-secure-proxy", .data = &am654_descपूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, ti_msgmgr_of_match);

अटल पूर्णांक ti_msgmgr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा device_node *np;
	काष्ठा resource *res;
	स्थिर काष्ठा ti_msgmgr_desc *desc;
	काष्ठा ti_msgmgr_inst *inst;
	काष्ठा ti_queue_inst *qinst;
	काष्ठा mbox_controller *mbox;
	काष्ठा mbox_chan *chans;
	पूर्णांक queue_count;
	पूर्णांक i;
	पूर्णांक ret = -EINVAL;
	स्थिर काष्ठा ti_msgmgr_valid_queue_desc *queue_desc;

	अगर (!dev->of_node) अणु
		dev_err(dev, "no OF information\n");
		वापस -EINVAL;
	पूर्ण
	np = dev->of_node;

	of_id = of_match_device(ti_msgmgr_of_match, dev);
	अगर (!of_id) अणु
		dev_err(dev, "OF data missing\n");
		वापस -EINVAL;
	पूर्ण
	desc = of_id->data;

	inst = devm_kzalloc(dev, माप(*inst), GFP_KERNEL);
	अगर (!inst)
		वापस -ENOMEM;

	inst->dev = dev;
	inst->desc = desc;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   desc->data_region_name);
	inst->queue_proxy_region = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(inst->queue_proxy_region))
		वापस PTR_ERR(inst->queue_proxy_region);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   desc->status_region_name);
	inst->queue_state_debug_region = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(inst->queue_state_debug_region))
		वापस PTR_ERR(inst->queue_state_debug_region);

	अगर (desc->is_sproxy) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   desc->ctrl_region_name);
		inst->queue_ctrl_region = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(inst->queue_ctrl_region))
			वापस PTR_ERR(inst->queue_ctrl_region);
	पूर्ण

	dev_dbg(dev, "proxy region=%p, queue_state=%p\n",
		inst->queue_proxy_region, inst->queue_state_debug_region);

	queue_count = desc->num_valid_queues;
	अगर (!queue_count || queue_count > desc->queue_count) अणु
		dev_crit(dev, "Invalid Number of queues %d. Max %d\n",
			 queue_count, desc->queue_count);
		वापस -दुस्फल;
	पूर्ण
	inst->num_valid_queues = queue_count;

	qinst = devm_kसुस्मृति(dev, queue_count, माप(*qinst), GFP_KERNEL);
	अगर (!qinst)
		वापस -ENOMEM;
	inst->qinsts = qinst;

	chans = devm_kसुस्मृति(dev, queue_count, माप(*chans), GFP_KERNEL);
	अगर (!chans)
		वापस -ENOMEM;
	inst->chans = chans;

	अगर (desc->is_sproxy) अणु
		काष्ठा ti_msgmgr_valid_queue_desc sproxy_desc;

		/* All proxies may be valid in Secure Proxy instance */
		क्रम (i = 0; i < queue_count; i++, qinst++, chans++) अणु
			sproxy_desc.queue_id = 0;
			sproxy_desc.proxy_id = i;
			ret = ti_msgmgr_queue_setup(i, dev, np, inst,
						    desc, &sproxy_desc, qinst,
						    chans);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Only Some proxies are valid in Message Manager */
		क्रम (i = 0, queue_desc = desc->valid_queues;
		     i < queue_count; i++, qinst++, chans++, queue_desc++) अणु
			ret = ti_msgmgr_queue_setup(i, dev, np, inst,
						    desc, queue_desc, qinst,
						    chans);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	mbox = &inst->mbox;
	mbox->dev = dev;
	mbox->ops = &ti_msgmgr_chan_ops;
	mbox->chans = inst->chans;
	mbox->num_chans = inst->num_valid_queues;
	mbox->txकरोne_irq = false;
	mbox->txकरोne_poll = desc->tx_polled;
	अगर (desc->tx_polled)
		mbox->txpoll_period = desc->tx_poll_समयout_ms;
	mbox->of_xlate = ti_msgmgr_of_xlate;

	platक्रमm_set_drvdata(pdev, inst);
	ret = devm_mbox_controller_रेजिस्टर(dev, mbox);
	अगर (ret)
		dev_err(dev, "Failed to register mbox_controller(%d)\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver ti_msgmgr_driver = अणु
	.probe = ti_msgmgr_probe,
	.driver = अणु
		   .name = "ti-msgmgr",
		   .of_match_table = of_match_ptr(ti_msgmgr_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_msgmgr_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI message manager driver");
MODULE_AUTHOR("Nishanth Menon");
MODULE_ALIAS("platform:ti-msgmgr");
