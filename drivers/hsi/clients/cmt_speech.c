<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cmt_speech.c - HSI CMT speech driver
 *
 * Copyright (C) 2008,2009,2010 Nokia Corporation. All rights reserved.
 *
 * Contact: Kai Vehmanen <kai.vehmanen@nokia.com>
 * Original author: Peter Ujfalusi <peter.ujfalusi@nokia.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/hsi/hsi.h>
#समावेश <linux/hsi/ssi_protocol.h>
#समावेश <linux/hsi/cs-protocol.h>

#घोषणा CS_MMAP_SIZE	PAGE_SIZE

काष्ठा अक्षर_queue अणु
	काष्ठा list_head	list;
	u32			msg;
पूर्ण;

काष्ठा cs_अक्षर अणु
	अचिन्हित पूर्णांक		खोलोed;
	काष्ठा hsi_client	*cl;
	काष्ठा cs_hsi_अगरace	*hi;
	काष्ठा list_head	अक्षरdev_queue;
	काष्ठा list_head	dataind_queue;
	पूर्णांक			dataind_pending;
	/* mmap things */
	अचिन्हित दीर्घ		mmap_base;
	अचिन्हित दीर्घ		mmap_size;
	spinlock_t		lock;
	काष्ठा fasync_काष्ठा	*async_queue;
	रुको_queue_head_t	रुको;
	/* hsi channel ids */
	पूर्णांक                     channel_id_cmd;
	पूर्णांक                     channel_id_data;
पूर्ण;

#घोषणा SSI_CHANNEL_STATE_READING	1
#घोषणा SSI_CHANNEL_STATE_WRITING	(1 << 1)
#घोषणा SSI_CHANNEL_STATE_POLL		(1 << 2)
#घोषणा SSI_CHANNEL_STATE_ERROR		(1 << 3)

#घोषणा TARGET_MASK			0xf000000
#घोषणा TARGET_REMOTE			(1 << CS_DOMAIN_SHIFT)
#घोषणा TARGET_LOCAL			0

/* Number of pre-allocated commands buffers */
#घोषणा CS_MAX_CMDS		        4

/*
 * During data transfers, transactions must be handled
 * within 20ms (fixed value in cmtspeech HSI protocol)
 */
#घोषणा CS_QOS_LATENCY_FOR_DATA_USEC	20000

/* Timeout to रुको क्रम pending HSI transfers to complete */
#घोषणा CS_HSI_TRANSFER_TIMEOUT_MS      500


#घोषणा RX_PTR_BOUNDARY_SHIFT		8
#घोषणा RX_PTR_MAX_SHIFT		(RX_PTR_BOUNDARY_SHIFT + \
						CS_MAX_BUFFERS_SHIFT)
काष्ठा cs_hsi_अगरace अणु
	काष्ठा hsi_client		*cl;
	काष्ठा hsi_client		*master;

	अचिन्हित पूर्णांक			अगरace_state;
	अचिन्हित पूर्णांक			wakeline_state;
	अचिन्हित पूर्णांक			control_state;
	अचिन्हित पूर्णांक			data_state;

	/* state exposed to application */
	काष्ठा cs_mmap_config_block	*mmap_cfg;

	अचिन्हित दीर्घ			mmap_base;
	अचिन्हित दीर्घ			mmap_size;

	अचिन्हित पूर्णांक			rx_slot;
	अचिन्हित पूर्णांक			tx_slot;

	/* note: क्रम security reasons, we करो not trust the contents of
	 * mmap_cfg, but instead duplicate the variables here */
	अचिन्हित पूर्णांक			buf_size;
	अचिन्हित पूर्णांक			rx_bufs;
	अचिन्हित पूर्णांक			tx_bufs;
	अचिन्हित पूर्णांक			rx_ptr_boundary;
	अचिन्हित पूर्णांक			rx_offsets[CS_MAX_BUFFERS];
	अचिन्हित पूर्णांक			tx_offsets[CS_MAX_BUFFERS];

	/* size of aligned memory blocks */
	अचिन्हित पूर्णांक			slot_size;
	अचिन्हित पूर्णांक			flags;

	काष्ठा list_head		cmdqueue;

	काष्ठा hsi_msg			*data_rx_msg;
	काष्ठा hsi_msg			*data_tx_msg;
	रुको_queue_head_t		dataरुको;

	काष्ठा pm_qos_request           pm_qos_req;

	spinlock_t			lock;
पूर्ण;

अटल काष्ठा cs_अक्षर cs_अक्षर_data;

अटल व्योम cs_hsi_पढ़ो_on_control(काष्ठा cs_hsi_अगरace *hi);
अटल व्योम cs_hsi_पढ़ो_on_data(काष्ठा cs_hsi_अगरace *hi);

अटल अंतरभूत व्योम rx_ptr_shअगरt_too_big(व्योम)
अणु
	BUILD_BUG_ON((1LLU << RX_PTR_MAX_SHIFT) > अच_पूर्णांक_उच्च);
पूर्ण

अटल व्योम cs_notअगरy(u32 message, काष्ठा list_head *head)
अणु
	काष्ठा अक्षर_queue *entry;

	spin_lock(&cs_अक्षर_data.lock);

	अगर (!cs_अक्षर_data.खोलोed) अणु
		spin_unlock(&cs_अक्षर_data.lock);
		जाओ out;
	पूर्ण

	entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	अगर (!entry) अणु
		dev_err(&cs_अक्षर_data.cl->device,
			"Can't allocate new entry for the queue.\n");
		spin_unlock(&cs_अक्षर_data.lock);
		जाओ out;
	पूर्ण

	entry->msg = message;
	list_add_tail(&entry->list, head);

	spin_unlock(&cs_अक्षर_data.lock);

	wake_up_पूर्णांकerruptible(&cs_अक्षर_data.रुको);
	समाप्त_fasync(&cs_अक्षर_data.async_queue, SIGIO, POLL_IN);

out:
	वापस;
पूर्ण

अटल u32 cs_pop_entry(काष्ठा list_head *head)
अणु
	काष्ठा अक्षर_queue *entry;
	u32 data;

	entry = list_entry(head->next, काष्ठा अक्षर_queue, list);
	data = entry->msg;
	list_del(&entry->list);
	kमुक्त(entry);

	वापस data;
पूर्ण

अटल व्योम cs_notअगरy_control(u32 message)
अणु
	cs_notअगरy(message, &cs_अक्षर_data.अक्षरdev_queue);
पूर्ण

अटल व्योम cs_notअगरy_data(u32 message, पूर्णांक maxlength)
अणु
	cs_notअगरy(message, &cs_अक्षर_data.dataind_queue);

	spin_lock(&cs_अक्षर_data.lock);
	cs_अक्षर_data.dataind_pending++;
	जबतक (cs_अक्षर_data.dataind_pending > maxlength &&
				!list_empty(&cs_अक्षर_data.dataind_queue)) अणु
		dev_dbg(&cs_अक्षर_data.cl->device, "data notification "
		"queue overrun (%u entries)\n", cs_अक्षर_data.dataind_pending);

		cs_pop_entry(&cs_अक्षर_data.dataind_queue);
		cs_अक्षर_data.dataind_pending--;
	पूर्ण
	spin_unlock(&cs_अक्षर_data.lock);
पूर्ण

अटल अंतरभूत व्योम cs_set_cmd(काष्ठा hsi_msg *msg, u32 cmd)
अणु
	u32 *data = sg_virt(msg->sgt.sgl);
	*data = cmd;
पूर्ण

अटल अंतरभूत u32 cs_get_cmd(काष्ठा hsi_msg *msg)
अणु
	u32 *data = sg_virt(msg->sgt.sgl);
	वापस *data;
पूर्ण

अटल व्योम cs_release_cmd(काष्ठा hsi_msg *msg)
अणु
	काष्ठा cs_hsi_अगरace *hi = msg->context;

	list_add_tail(&msg->link, &hi->cmdqueue);
पूर्ण

अटल व्योम cs_cmd_deकाष्ठाor(काष्ठा hsi_msg *msg)
अणु
	काष्ठा cs_hsi_अगरace *hi = msg->context;

	spin_lock(&hi->lock);

	dev_dbg(&cs_अक्षर_data.cl->device, "control cmd destructor\n");

	अगर (hi->अगरace_state != CS_STATE_CLOSED)
		dev_err(&hi->cl->device, "Cmd flushed while driver active\n");

	अगर (msg->ttype == HSI_MSG_READ)
		hi->control_state &=
			~(SSI_CHANNEL_STATE_POLL | SSI_CHANNEL_STATE_READING);
	अन्यथा अगर (msg->ttype == HSI_MSG_WRITE &&
			hi->control_state & SSI_CHANNEL_STATE_WRITING)
		hi->control_state &= ~SSI_CHANNEL_STATE_WRITING;

	cs_release_cmd(msg);

	spin_unlock(&hi->lock);
पूर्ण

अटल काष्ठा hsi_msg *cs_claim_cmd(काष्ठा cs_hsi_अगरace* ssi)
अणु
	काष्ठा hsi_msg *msg;

	BUG_ON(list_empty(&ssi->cmdqueue));

	msg = list_first_entry(&ssi->cmdqueue, काष्ठा hsi_msg, link);
	list_del(&msg->link);
	msg->deकाष्ठाor = cs_cmd_deकाष्ठाor;

	वापस msg;
पूर्ण

अटल व्योम cs_मुक्त_cmds(काष्ठा cs_hsi_अगरace *ssi)
अणु
	काष्ठा hsi_msg *msg, *पंचांगp;

	list_क्रम_each_entry_safe(msg, पंचांगp, &ssi->cmdqueue, link) अणु
		list_del(&msg->link);
		msg->deकाष्ठाor = शून्य;
		kमुक्त(sg_virt(msg->sgt.sgl));
		hsi_मुक्त_msg(msg);
	पूर्ण
पूर्ण

अटल पूर्णांक cs_alloc_cmds(काष्ठा cs_hsi_अगरace *hi)
अणु
	काष्ठा hsi_msg *msg;
	u32 *buf;
	अचिन्हित पूर्णांक i;

	INIT_LIST_HEAD(&hi->cmdqueue);

	क्रम (i = 0; i < CS_MAX_CMDS; i++) अणु
		msg = hsi_alloc_msg(1, GFP_KERNEL);
		अगर (!msg)
			जाओ out;
		buf = kदो_स्मृति(माप(*buf), GFP_KERNEL);
		अगर (!buf) अणु
			hsi_मुक्त_msg(msg);
			जाओ out;
		पूर्ण
		sg_init_one(msg->sgt.sgl, buf, माप(*buf));
		msg->channel = cs_अक्षर_data.channel_id_cmd;
		msg->context = hi;
		list_add_tail(&msg->link, &hi->cmdqueue);
	पूर्ण

	वापस 0;

out:
	cs_मुक्त_cmds(hi);
	वापस -ENOMEM;
पूर्ण

अटल व्योम cs_hsi_data_deकाष्ठाor(काष्ठा hsi_msg *msg)
अणु
	काष्ठा cs_hsi_अगरace *hi = msg->context;
	स्थिर अक्षर *dir = (msg->ttype == HSI_MSG_READ) ? "TX" : "RX";

	dev_dbg(&cs_अक्षर_data.cl->device, "Freeing data %s message\n", dir);

	spin_lock(&hi->lock);
	अगर (hi->अगरace_state != CS_STATE_CLOSED)
		dev_err(&cs_अक्षर_data.cl->device,
				"Data %s flush while device active\n", dir);
	अगर (msg->ttype == HSI_MSG_READ)
		hi->data_state &=
			~(SSI_CHANNEL_STATE_POLL | SSI_CHANNEL_STATE_READING);
	अन्यथा
		hi->data_state &= ~SSI_CHANNEL_STATE_WRITING;

	msg->status = HSI_STATUS_COMPLETED;
	अगर (unlikely(रुकोqueue_active(&hi->dataरुको)))
		wake_up_पूर्णांकerruptible(&hi->dataरुको);

	spin_unlock(&hi->lock);
पूर्ण

अटल पूर्णांक cs_hsi_alloc_data(काष्ठा cs_hsi_अगरace *hi)
अणु
	काष्ठा hsi_msg *txmsg, *rxmsg;
	पूर्णांक res = 0;

	rxmsg = hsi_alloc_msg(1, GFP_KERNEL);
	अगर (!rxmsg) अणु
		res = -ENOMEM;
		जाओ out1;
	पूर्ण
	rxmsg->channel = cs_अक्षर_data.channel_id_data;
	rxmsg->deकाष्ठाor = cs_hsi_data_deकाष्ठाor;
	rxmsg->context = hi;

	txmsg = hsi_alloc_msg(1, GFP_KERNEL);
	अगर (!txmsg) अणु
		res = -ENOMEM;
		जाओ out2;
	पूर्ण
	txmsg->channel = cs_अक्षर_data.channel_id_data;
	txmsg->deकाष्ठाor = cs_hsi_data_deकाष्ठाor;
	txmsg->context = hi;

	hi->data_rx_msg = rxmsg;
	hi->data_tx_msg = txmsg;

	वापस 0;

out2:
	hsi_मुक्त_msg(rxmsg);
out1:
	वापस res;
पूर्ण

अटल व्योम cs_hsi_मुक्त_data_msg(काष्ठा hsi_msg *msg)
अणु
	WARN_ON(msg->status != HSI_STATUS_COMPLETED &&
					msg->status != HSI_STATUS_ERROR);
	hsi_मुक्त_msg(msg);
पूर्ण

अटल व्योम cs_hsi_मुक्त_data(काष्ठा cs_hsi_अगरace *hi)
अणु
	cs_hsi_मुक्त_data_msg(hi->data_rx_msg);
	cs_hsi_मुक्त_data_msg(hi->data_tx_msg);
पूर्ण

अटल अंतरभूत व्योम __cs_hsi_error_pre(काष्ठा cs_hsi_अगरace *hi,
					काष्ठा hsi_msg *msg, स्थिर अक्षर *info,
					अचिन्हित पूर्णांक *state)
अणु
	spin_lock(&hi->lock);
	dev_err(&hi->cl->device, "HSI %s error, msg %d, state %u\n",
		info, msg->status, *state);
पूर्ण

अटल अंतरभूत व्योम __cs_hsi_error_post(काष्ठा cs_hsi_अगरace *hi)
अणु
	spin_unlock(&hi->lock);
पूर्ण

अटल अंतरभूत व्योम __cs_hsi_error_पढ़ो_bits(अचिन्हित पूर्णांक *state)
अणु
	*state |= SSI_CHANNEL_STATE_ERROR;
	*state &= ~(SSI_CHANNEL_STATE_READING | SSI_CHANNEL_STATE_POLL);
पूर्ण

अटल अंतरभूत व्योम __cs_hsi_error_ग_लिखो_bits(अचिन्हित पूर्णांक *state)
अणु
	*state |= SSI_CHANNEL_STATE_ERROR;
	*state &= ~SSI_CHANNEL_STATE_WRITING;
पूर्ण

अटल व्योम cs_hsi_control_पढ़ो_error(काष्ठा cs_hsi_अगरace *hi,
							काष्ठा hsi_msg *msg)
अणु
	__cs_hsi_error_pre(hi, msg, "control read", &hi->control_state);
	cs_release_cmd(msg);
	__cs_hsi_error_पढ़ो_bits(&hi->control_state);
	__cs_hsi_error_post(hi);
पूर्ण

अटल व्योम cs_hsi_control_ग_लिखो_error(काष्ठा cs_hsi_अगरace *hi,
							काष्ठा hsi_msg *msg)
अणु
	__cs_hsi_error_pre(hi, msg, "control write", &hi->control_state);
	cs_release_cmd(msg);
	__cs_hsi_error_ग_लिखो_bits(&hi->control_state);
	__cs_hsi_error_post(hi);

पूर्ण

अटल व्योम cs_hsi_data_पढ़ो_error(काष्ठा cs_hsi_अगरace *hi, काष्ठा hsi_msg *msg)
अणु
	__cs_hsi_error_pre(hi, msg, "data read", &hi->data_state);
	__cs_hsi_error_पढ़ो_bits(&hi->data_state);
	__cs_hsi_error_post(hi);
पूर्ण

अटल व्योम cs_hsi_data_ग_लिखो_error(काष्ठा cs_hsi_अगरace *hi,
							काष्ठा hsi_msg *msg)
अणु
	__cs_hsi_error_pre(hi, msg, "data write", &hi->data_state);
	__cs_hsi_error_ग_लिखो_bits(&hi->data_state);
	__cs_hsi_error_post(hi);
पूर्ण

अटल व्योम cs_hsi_पढ़ो_on_control_complete(काष्ठा hsi_msg *msg)
अणु
	u32 cmd = cs_get_cmd(msg);
	काष्ठा cs_hsi_अगरace *hi = msg->context;

	spin_lock(&hi->lock);
	hi->control_state &= ~SSI_CHANNEL_STATE_READING;
	अगर (msg->status == HSI_STATUS_ERROR) अणु
		dev_err(&hi->cl->device, "Control RX error detected\n");
		spin_unlock(&hi->lock);
		cs_hsi_control_पढ़ो_error(hi, msg);
		जाओ out;
	पूर्ण
	dev_dbg(&hi->cl->device, "Read on control: %08X\n", cmd);
	cs_release_cmd(msg);
	अगर (hi->flags & CS_FEAT_TSTAMP_RX_CTRL) अणु
		काष्ठा बारpec64 tspec;
		काष्ठा cs_बारtamp *tstamp =
			&hi->mmap_cfg->tstamp_rx_ctrl;

		kसमय_get_ts64(&tspec);

		tstamp->tv_sec = (__u32) tspec.tv_sec;
		tstamp->tv_nsec = (__u32) tspec.tv_nsec;
	पूर्ण
	spin_unlock(&hi->lock);

	cs_notअगरy_control(cmd);

out:
	cs_hsi_पढ़ो_on_control(hi);
पूर्ण

अटल व्योम cs_hsi_peek_on_control_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा cs_hsi_अगरace *hi = msg->context;
	पूर्णांक ret;

	अगर (msg->status == HSI_STATUS_ERROR) अणु
		dev_err(&hi->cl->device, "Control peek RX error detected\n");
		cs_hsi_control_पढ़ो_error(hi, msg);
		वापस;
	पूर्ण

	WARN_ON(!(hi->control_state & SSI_CHANNEL_STATE_READING));

	dev_dbg(&hi->cl->device, "Peek on control complete, reading\n");
	msg->sgt.nents = 1;
	msg->complete = cs_hsi_पढ़ो_on_control_complete;
	ret = hsi_async_पढ़ो(hi->cl, msg);
	अगर (ret)
		cs_hsi_control_पढ़ो_error(hi, msg);
पूर्ण

अटल व्योम cs_hsi_पढ़ो_on_control(काष्ठा cs_hsi_अगरace *hi)
अणु
	काष्ठा hsi_msg *msg;
	पूर्णांक ret;

	spin_lock(&hi->lock);
	अगर (hi->control_state & SSI_CHANNEL_STATE_READING) अणु
		dev_err(&hi->cl->device, "Control read already pending (%d)\n",
			hi->control_state);
		spin_unlock(&hi->lock);
		वापस;
	पूर्ण
	अगर (hi->control_state & SSI_CHANNEL_STATE_ERROR) अणु
		dev_err(&hi->cl->device, "Control read error (%d)\n",
			hi->control_state);
		spin_unlock(&hi->lock);
		वापस;
	पूर्ण
	hi->control_state |= SSI_CHANNEL_STATE_READING;
	dev_dbg(&hi->cl->device, "Issuing RX on control\n");
	msg = cs_claim_cmd(hi);
	spin_unlock(&hi->lock);

	msg->sgt.nents = 0;
	msg->complete = cs_hsi_peek_on_control_complete;
	ret = hsi_async_पढ़ो(hi->cl, msg);
	अगर (ret)
		cs_hsi_control_पढ़ो_error(hi, msg);
पूर्ण

अटल व्योम cs_hsi_ग_लिखो_on_control_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा cs_hsi_अगरace *hi = msg->context;
	अगर (msg->status == HSI_STATUS_COMPLETED) अणु
		spin_lock(&hi->lock);
		hi->control_state &= ~SSI_CHANNEL_STATE_WRITING;
		cs_release_cmd(msg);
		spin_unlock(&hi->lock);
	पूर्ण अन्यथा अगर (msg->status == HSI_STATUS_ERROR) अणु
		cs_hsi_control_ग_लिखो_error(hi, msg);
	पूर्ण अन्यथा अणु
		dev_err(&hi->cl->device,
			"unexpected status in control write callback %d\n",
			msg->status);
	पूर्ण
पूर्ण

अटल पूर्णांक cs_hsi_ग_लिखो_on_control(काष्ठा cs_hsi_अगरace *hi, u32 message)
अणु
	काष्ठा hsi_msg *msg;
	पूर्णांक ret;

	spin_lock(&hi->lock);
	अगर (hi->control_state & SSI_CHANNEL_STATE_ERROR) अणु
		spin_unlock(&hi->lock);
		वापस -EIO;
	पूर्ण
	अगर (hi->control_state & SSI_CHANNEL_STATE_WRITING) अणु
		dev_err(&hi->cl->device,
			"Write still pending on control channel.\n");
		spin_unlock(&hi->lock);
		वापस -EBUSY;
	पूर्ण
	hi->control_state |= SSI_CHANNEL_STATE_WRITING;
	msg = cs_claim_cmd(hi);
	spin_unlock(&hi->lock);

	cs_set_cmd(msg, message);
	msg->sgt.nents = 1;
	msg->complete = cs_hsi_ग_लिखो_on_control_complete;
	dev_dbg(&hi->cl->device,
		"Sending control message %08X\n", message);
	ret = hsi_async_ग_लिखो(hi->cl, msg);
	अगर (ret) अणु
		dev_err(&hi->cl->device,
			"async_write failed with %d\n", ret);
		cs_hsi_control_ग_लिखो_error(hi, msg);
	पूर्ण

	/*
	 * Make sure control पढ़ो is always pending when issuing
	 * new control ग_लिखोs. This is needed as the controller
	 * may flush our messages अगर e.g. the peer device reboots
	 * unexpectedly (and we cannot directly resubmit a new पढ़ो from
	 * the message deकाष्ठाor; see cs_cmd_deकाष्ठाor()).
	 */
	अगर (!(hi->control_state & SSI_CHANNEL_STATE_READING)) अणु
		dev_err(&hi->cl->device, "Restarting control reads\n");
		cs_hsi_पढ़ो_on_control(hi);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cs_hsi_पढ़ो_on_data_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा cs_hsi_अगरace *hi = msg->context;
	u32 payload;

	अगर (unlikely(msg->status == HSI_STATUS_ERROR)) अणु
		cs_hsi_data_पढ़ो_error(hi, msg);
		वापस;
	पूर्ण

	spin_lock(&hi->lock);
	WARN_ON(!(hi->data_state & SSI_CHANNEL_STATE_READING));
	hi->data_state &= ~SSI_CHANNEL_STATE_READING;
	payload = CS_RX_DATA_RECEIVED;
	payload |= hi->rx_slot;
	hi->rx_slot++;
	hi->rx_slot %= hi->rx_ptr_boundary;
	/* expose current rx ptr in mmap area */
	hi->mmap_cfg->rx_ptr = hi->rx_slot;
	अगर (unlikely(रुकोqueue_active(&hi->dataरुको)))
		wake_up_पूर्णांकerruptible(&hi->dataरुको);
	spin_unlock(&hi->lock);

	cs_notअगरy_data(payload, hi->rx_bufs);
	cs_hsi_पढ़ो_on_data(hi);
पूर्ण

अटल व्योम cs_hsi_peek_on_data_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा cs_hsi_अगरace *hi = msg->context;
	u32 *address;
	पूर्णांक ret;

	अगर (unlikely(msg->status == HSI_STATUS_ERROR)) अणु
		cs_hsi_data_पढ़ो_error(hi, msg);
		वापस;
	पूर्ण
	अगर (unlikely(hi->अगरace_state != CS_STATE_CONFIGURED)) अणु
		dev_err(&hi->cl->device, "Data received in invalid state\n");
		cs_hsi_data_पढ़ो_error(hi, msg);
		वापस;
	पूर्ण

	spin_lock(&hi->lock);
	WARN_ON(!(hi->data_state & SSI_CHANNEL_STATE_POLL));
	hi->data_state &= ~SSI_CHANNEL_STATE_POLL;
	hi->data_state |= SSI_CHANNEL_STATE_READING;
	spin_unlock(&hi->lock);

	address = (u32 *)(hi->mmap_base +
				hi->rx_offsets[hi->rx_slot % hi->rx_bufs]);
	sg_init_one(msg->sgt.sgl, address, hi->buf_size);
	msg->sgt.nents = 1;
	msg->complete = cs_hsi_पढ़ो_on_data_complete;
	ret = hsi_async_पढ़ो(hi->cl, msg);
	अगर (ret)
		cs_hsi_data_पढ़ो_error(hi, msg);
पूर्ण

/*
 * Read/ग_लिखो transaction is ongoing. Returns false अगर in
 * SSI_CHANNEL_STATE_POLL state.
 */
अटल अंतरभूत पूर्णांक cs_state_xfer_active(अचिन्हित पूर्णांक state)
अणु
	वापस (state & SSI_CHANNEL_STATE_WRITING) ||
		(state & SSI_CHANNEL_STATE_READING);
पूर्ण

/*
 * No pending पढ़ो/ग_लिखोs
 */
अटल अंतरभूत पूर्णांक cs_state_idle(अचिन्हित पूर्णांक state)
अणु
	वापस !(state & ~SSI_CHANNEL_STATE_ERROR);
पूर्ण

अटल व्योम cs_hsi_पढ़ो_on_data(काष्ठा cs_hsi_अगरace *hi)
अणु
	काष्ठा hsi_msg *rxmsg;
	पूर्णांक ret;

	spin_lock(&hi->lock);
	अगर (hi->data_state &
		(SSI_CHANNEL_STATE_READING | SSI_CHANNEL_STATE_POLL)) अणु
		dev_dbg(&hi->cl->device, "Data read already pending (%u)\n",
			hi->data_state);
		spin_unlock(&hi->lock);
		वापस;
	पूर्ण
	hi->data_state |= SSI_CHANNEL_STATE_POLL;
	spin_unlock(&hi->lock);

	rxmsg = hi->data_rx_msg;
	sg_init_one(rxmsg->sgt.sgl, (व्योम *)hi->mmap_base, 0);
	rxmsg->sgt.nents = 0;
	rxmsg->complete = cs_hsi_peek_on_data_complete;

	ret = hsi_async_पढ़ो(hi->cl, rxmsg);
	अगर (ret)
		cs_hsi_data_पढ़ो_error(hi, rxmsg);
पूर्ण

अटल व्योम cs_hsi_ग_लिखो_on_data_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा cs_hsi_अगरace *hi = msg->context;

	अगर (msg->status == HSI_STATUS_COMPLETED) अणु
		spin_lock(&hi->lock);
		hi->data_state &= ~SSI_CHANNEL_STATE_WRITING;
		अगर (unlikely(रुकोqueue_active(&hi->dataरुको)))
			wake_up_पूर्णांकerruptible(&hi->dataरुको);
		spin_unlock(&hi->lock);
	पूर्ण अन्यथा अणु
		cs_hsi_data_ग_लिखो_error(hi, msg);
	पूर्ण
पूर्ण

अटल पूर्णांक cs_hsi_ग_लिखो_on_data(काष्ठा cs_hsi_अगरace *hi, अचिन्हित पूर्णांक slot)
अणु
	u32 *address;
	काष्ठा hsi_msg *txmsg;
	पूर्णांक ret;

	spin_lock(&hi->lock);
	अगर (hi->अगरace_state != CS_STATE_CONFIGURED) अणु
		dev_err(&hi->cl->device, "Not configured, aborting\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	अगर (hi->data_state & SSI_CHANNEL_STATE_ERROR) अणु
		dev_err(&hi->cl->device, "HSI error, aborting\n");
		ret = -EIO;
		जाओ error;
	पूर्ण
	अगर (hi->data_state & SSI_CHANNEL_STATE_WRITING) अणु
		dev_err(&hi->cl->device, "Write pending on data channel.\n");
		ret = -EBUSY;
		जाओ error;
	पूर्ण
	hi->data_state |= SSI_CHANNEL_STATE_WRITING;
	spin_unlock(&hi->lock);

	hi->tx_slot = slot;
	address = (u32 *)(hi->mmap_base + hi->tx_offsets[hi->tx_slot]);
	txmsg = hi->data_tx_msg;
	sg_init_one(txmsg->sgt.sgl, address, hi->buf_size);
	txmsg->complete = cs_hsi_ग_लिखो_on_data_complete;
	ret = hsi_async_ग_लिखो(hi->cl, txmsg);
	अगर (ret)
		cs_hsi_data_ग_लिखो_error(hi, txmsg);

	वापस ret;

error:
	spin_unlock(&hi->lock);
	अगर (ret == -EIO)
		cs_hsi_data_ग_लिखो_error(hi, hi->data_tx_msg);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक cs_hsi_get_state(काष्ठा cs_hsi_अगरace *hi)
अणु
	वापस hi->अगरace_state;
पूर्ण

अटल पूर्णांक cs_hsi_command(काष्ठा cs_hsi_अगरace *hi, u32 cmd)
अणु
	पूर्णांक ret = 0;

	local_bh_disable();
	चयन (cmd & TARGET_MASK) अणु
	हाल TARGET_REMOTE:
		ret = cs_hsi_ग_लिखो_on_control(hi, cmd);
		अवरोध;
	हाल TARGET_LOCAL:
		अगर ((cmd & CS_CMD_MASK) == CS_TX_DATA_READY)
			ret = cs_hsi_ग_लिखो_on_data(hi, cmd & CS_PARAM_MASK);
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	local_bh_enable();

	वापस ret;
पूर्ण

अटल व्योम cs_hsi_set_wakeline(काष्ठा cs_hsi_अगरace *hi, bool new_state)
अणु
	पूर्णांक change = 0;

	spin_lock_bh(&hi->lock);
	अगर (hi->wakeline_state != new_state) अणु
		hi->wakeline_state = new_state;
		change = 1;
		dev_dbg(&hi->cl->device, "setting wake line to %d (%p)\n",
			new_state, hi->cl);
	पूर्ण
	spin_unlock_bh(&hi->lock);

	अगर (change) अणु
		अगर (new_state)
			ssip_slave_start_tx(hi->master);
		अन्यथा
			ssip_slave_stop_tx(hi->master);
	पूर्ण

	dev_dbg(&hi->cl->device, "wake line set to %d (%p)\n",
		new_state, hi->cl);
पूर्ण

अटल व्योम set_buffer_sizes(काष्ठा cs_hsi_अगरace *hi, पूर्णांक rx_bufs, पूर्णांक tx_bufs)
अणु
	hi->rx_bufs = rx_bufs;
	hi->tx_bufs = tx_bufs;
	hi->mmap_cfg->rx_bufs = rx_bufs;
	hi->mmap_cfg->tx_bufs = tx_bufs;

	अगर (hi->flags & CS_FEAT_ROLLING_RX_COUNTER) अणु
		/*
		 * For more robust overrun detection, let the rx
		 * poपूर्णांकer run in range 0..'boundary-1'. Boundary
		 * is a multiple of rx_bufs, and limited in max size
		 * by RX_PTR_MAX_SHIFT to allow क्रम fast ptr-dअगरf
		 * calculation.
		 */
		hi->rx_ptr_boundary = (rx_bufs << RX_PTR_BOUNDARY_SHIFT);
		hi->mmap_cfg->rx_ptr_boundary = hi->rx_ptr_boundary;
	पूर्ण अन्यथा अणु
		hi->rx_ptr_boundary = hi->rx_bufs;
	पूर्ण
पूर्ण

अटल पूर्णांक check_buf_params(काष्ठा cs_hsi_अगरace *hi,
					स्थिर काष्ठा cs_buffer_config *buf_cfg)
अणु
	माप_प्रकार buf_size_aligned = L1_CACHE_ALIGN(buf_cfg->buf_size) *
					(buf_cfg->rx_bufs + buf_cfg->tx_bufs);
	माप_प्रकार ctrl_size_aligned = L1_CACHE_ALIGN(माप(*hi->mmap_cfg));
	पूर्णांक r = 0;

	अगर (buf_cfg->rx_bufs > CS_MAX_BUFFERS ||
					buf_cfg->tx_bufs > CS_MAX_BUFFERS) अणु
		r = -EINVAL;
	पूर्ण अन्यथा अगर ((buf_size_aligned + ctrl_size_aligned) >= hi->mmap_size) अणु
		dev_err(&hi->cl->device, "No space for the requested buffer "
			"configuration\n");
		r = -ENOBUFS;
	पूर्ण

	वापस r;
पूर्ण

/**
 * Block until pending data transfers have completed.
 */
अटल पूर्णांक cs_hsi_data_sync(काष्ठा cs_hsi_अगरace *hi)
अणु
	पूर्णांक r = 0;

	spin_lock_bh(&hi->lock);

	अगर (!cs_state_xfer_active(hi->data_state)) अणु
		dev_dbg(&hi->cl->device, "hsi_data_sync break, idle\n");
		जाओ out;
	पूर्ण

	क्रम (;;) अणु
		पूर्णांक s;
		DEFINE_WAIT(रुको);
		अगर (!cs_state_xfer_active(hi->data_state))
			जाओ out;
		अगर (संकेत_pending(current)) अणु
			r = -ERESTARTSYS;
			जाओ out;
		पूर्ण
		/**
		 * prepare_to_रुको must be called with hi->lock held
		 * so that callbacks can check क्रम रुकोqueue_active()
		 */
		prepare_to_रुको(&hi->dataरुको, &रुको, TASK_INTERRUPTIBLE);
		spin_unlock_bh(&hi->lock);
		s = schedule_समयout(
			msecs_to_jअगरfies(CS_HSI_TRANSFER_TIMEOUT_MS));
		spin_lock_bh(&hi->lock);
		finish_रुको(&hi->dataरुको, &रुको);
		अगर (!s) अणु
			dev_dbg(&hi->cl->device,
				"hsi_data_sync timeout after %d ms\n",
				CS_HSI_TRANSFER_TIMEOUT_MS);
			r = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	spin_unlock_bh(&hi->lock);
	dev_dbg(&hi->cl->device, "hsi_data_sync done with res %d\n", r);

	वापस r;
पूर्ण

अटल व्योम cs_hsi_data_enable(काष्ठा cs_hsi_अगरace *hi,
					काष्ठा cs_buffer_config *buf_cfg)
अणु
	अचिन्हित पूर्णांक data_start, i;

	BUG_ON(hi->buf_size == 0);

	set_buffer_sizes(hi, buf_cfg->rx_bufs, buf_cfg->tx_bufs);

	hi->slot_size = L1_CACHE_ALIGN(hi->buf_size);
	dev_dbg(&hi->cl->device,
			"setting slot size to %u, buf size %u, align %u\n",
			hi->slot_size, hi->buf_size, L1_CACHE_BYTES);

	data_start = L1_CACHE_ALIGN(माप(*hi->mmap_cfg));
	dev_dbg(&hi->cl->device,
			"setting data start at %u, cfg block %u, align %u\n",
			data_start, माप(*hi->mmap_cfg), L1_CACHE_BYTES);

	क्रम (i = 0; i < hi->mmap_cfg->rx_bufs; i++) अणु
		hi->rx_offsets[i] = data_start + i * hi->slot_size;
		hi->mmap_cfg->rx_offsets[i] = hi->rx_offsets[i];
		dev_dbg(&hi->cl->device, "DL buf #%u at %u\n",
					i, hi->rx_offsets[i]);
	पूर्ण
	क्रम (i = 0; i < hi->mmap_cfg->tx_bufs; i++) अणु
		hi->tx_offsets[i] = data_start +
			(i + hi->mmap_cfg->rx_bufs) * hi->slot_size;
		hi->mmap_cfg->tx_offsets[i] = hi->tx_offsets[i];
		dev_dbg(&hi->cl->device, "UL buf #%u at %u\n",
					i, hi->rx_offsets[i]);
	पूर्ण

	hi->अगरace_state = CS_STATE_CONFIGURED;
पूर्ण

अटल व्योम cs_hsi_data_disable(काष्ठा cs_hsi_अगरace *hi, पूर्णांक old_state)
अणु
	अगर (old_state == CS_STATE_CONFIGURED) अणु
		dev_dbg(&hi->cl->device,
			"closing data channel with slot size 0\n");
		hi->अगरace_state = CS_STATE_OPENED;
	पूर्ण
पूर्ण

अटल पूर्णांक cs_hsi_buf_config(काष्ठा cs_hsi_अगरace *hi,
					काष्ठा cs_buffer_config *buf_cfg)
अणु
	पूर्णांक r = 0;
	अचिन्हित पूर्णांक old_state = hi->अगरace_state;

	spin_lock_bh(&hi->lock);
	/* Prevent new transactions during buffer reconfig */
	अगर (old_state == CS_STATE_CONFIGURED)
		hi->अगरace_state = CS_STATE_OPENED;
	spin_unlock_bh(&hi->lock);

	/*
	 * make sure that no non-zero data पढ़ोs are ongoing beक्रमe
	 * proceeding to change the buffer layout
	 */
	r = cs_hsi_data_sync(hi);
	अगर (r < 0)
		वापस r;

	WARN_ON(cs_state_xfer_active(hi->data_state));

	spin_lock_bh(&hi->lock);
	r = check_buf_params(hi, buf_cfg);
	अगर (r < 0)
		जाओ error;

	hi->buf_size = buf_cfg->buf_size;
	hi->mmap_cfg->buf_size = hi->buf_size;
	hi->flags = buf_cfg->flags;

	hi->rx_slot = 0;
	hi->tx_slot = 0;
	hi->slot_size = 0;

	अगर (hi->buf_size)
		cs_hsi_data_enable(hi, buf_cfg);
	अन्यथा
		cs_hsi_data_disable(hi, old_state);

	spin_unlock_bh(&hi->lock);

	अगर (old_state != hi->अगरace_state) अणु
		अगर (hi->अगरace_state == CS_STATE_CONFIGURED) अणु
			cpu_latency_qos_add_request(&hi->pm_qos_req,
				CS_QOS_LATENCY_FOR_DATA_USEC);
			local_bh_disable();
			cs_hsi_पढ़ो_on_data(hi);
			local_bh_enable();
		पूर्ण अन्यथा अगर (old_state == CS_STATE_CONFIGURED) अणु
			cpu_latency_qos_हटाओ_request(&hi->pm_qos_req);
		पूर्ण
	पूर्ण
	वापस r;

error:
	spin_unlock_bh(&hi->lock);
	वापस r;
पूर्ण

अटल पूर्णांक cs_hsi_start(काष्ठा cs_hsi_अगरace **hi, काष्ठा hsi_client *cl,
			अचिन्हित दीर्घ mmap_base, अचिन्हित दीर्घ mmap_size)
अणु
	पूर्णांक err = 0;
	काष्ठा cs_hsi_अगरace *hsi_अगर = kzalloc(माप(*hsi_अगर), GFP_KERNEL);

	dev_dbg(&cl->device, "cs_hsi_start\n");

	अगर (!hsi_अगर) अणु
		err = -ENOMEM;
		जाओ leave0;
	पूर्ण
	spin_lock_init(&hsi_अगर->lock);
	hsi_अगर->cl = cl;
	hsi_अगर->अगरace_state = CS_STATE_CLOSED;
	hsi_अगर->mmap_cfg = (काष्ठा cs_mmap_config_block *)mmap_base;
	hsi_अगर->mmap_base = mmap_base;
	hsi_अगर->mmap_size = mmap_size;
	स_रखो(hsi_अगर->mmap_cfg, 0, माप(*hsi_अगर->mmap_cfg));
	init_रुकोqueue_head(&hsi_अगर->dataरुको);
	err = cs_alloc_cmds(hsi_अगर);
	अगर (err < 0) अणु
		dev_err(&cl->device, "Unable to alloc HSI messages\n");
		जाओ leave1;
	पूर्ण
	err = cs_hsi_alloc_data(hsi_अगर);
	अगर (err < 0) अणु
		dev_err(&cl->device, "Unable to alloc HSI messages for data\n");
		जाओ leave2;
	पूर्ण
	err = hsi_claim_port(cl, 1);
	अगर (err < 0) अणु
		dev_err(&cl->device,
				"Could not open, HSI port already claimed\n");
		जाओ leave3;
	पूर्ण
	hsi_अगर->master = ssip_slave_get_master(cl);
	अगर (IS_ERR(hsi_अगर->master)) अणु
		err = PTR_ERR(hsi_अगर->master);
		dev_err(&cl->device, "Could not get HSI master client\n");
		जाओ leave4;
	पूर्ण
	अगर (!ssip_slave_running(hsi_अगर->master)) अणु
		err = -ENODEV;
		dev_err(&cl->device,
				"HSI port not initialized\n");
		जाओ leave4;
	पूर्ण

	hsi_अगर->अगरace_state = CS_STATE_OPENED;
	local_bh_disable();
	cs_hsi_पढ़ो_on_control(hsi_अगर);
	local_bh_enable();

	dev_dbg(&cl->device, "cs_hsi_start...done\n");

	BUG_ON(!hi);
	*hi = hsi_अगर;

	वापस 0;

leave4:
	hsi_release_port(cl);
leave3:
	cs_hsi_मुक्त_data(hsi_अगर);
leave2:
	cs_मुक्त_cmds(hsi_अगर);
leave1:
	kमुक्त(hsi_अगर);
leave0:
	dev_dbg(&cl->device, "cs_hsi_start...done/error\n\n");

	वापस err;
पूर्ण

अटल व्योम cs_hsi_stop(काष्ठा cs_hsi_अगरace *hi)
अणु
	dev_dbg(&hi->cl->device, "cs_hsi_stop\n");
	cs_hsi_set_wakeline(hi, 0);
	ssip_slave_put_master(hi->master);

	/* hsi_release_port() needs to be called with CS_STATE_CLOSED */
	hi->अगरace_state = CS_STATE_CLOSED;
	hsi_release_port(hi->cl);

	/*
	 * hsi_release_port() should flush out all the pending
	 * messages, so cs_state_idle() should be true क्रम both
	 * control and data channels.
	 */
	WARN_ON(!cs_state_idle(hi->control_state));
	WARN_ON(!cs_state_idle(hi->data_state));

	अगर (cpu_latency_qos_request_active(&hi->pm_qos_req))
		cpu_latency_qos_हटाओ_request(&hi->pm_qos_req);

	spin_lock_bh(&hi->lock);
	cs_hsi_मुक्त_data(hi);
	cs_मुक्त_cmds(hi);
	spin_unlock_bh(&hi->lock);
	kमुक्त(hi);
पूर्ण

अटल vm_fault_t cs_अक्षर_vma_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा cs_अक्षर *csdata = vmf->vma->vm_निजी_data;
	काष्ठा page *page;

	page = virt_to_page(csdata->mmap_base);
	get_page(page);
	vmf->page = page;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा cs_अक्षर_vm_ops = अणु
	.fault	= cs_अक्षर_vma_fault,
पूर्ण;

अटल पूर्णांक cs_अक्षर_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा cs_अक्षर *csdata = file->निजी_data;

	अगर (fasync_helper(fd, file, on, &csdata->async_queue) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल __poll_t cs_अक्षर_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा cs_अक्षर *csdata = file->निजी_data;
	__poll_t ret = 0;

	poll_रुको(file, &cs_अक्षर_data.रुको, रुको);
	spin_lock_bh(&csdata->lock);
	अगर (!list_empty(&csdata->अक्षरdev_queue))
		ret = EPOLLIN | EPOLLRDNORM;
	अन्यथा अगर (!list_empty(&csdata->dataind_queue))
		ret = EPOLLIN | EPOLLRDNORM;
	spin_unlock_bh(&csdata->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार cs_अक्षर_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
								loff_t *unused)
अणु
	काष्ठा cs_अक्षर *csdata = file->निजी_data;
	u32 data;
	sमाप_प्रकार retval;

	अगर (count < माप(data))
		वापस -EINVAL;

	क्रम (;;) अणु
		DEFINE_WAIT(रुको);

		spin_lock_bh(&csdata->lock);
		अगर (!list_empty(&csdata->अक्षरdev_queue)) अणु
			data = cs_pop_entry(&csdata->अक्षरdev_queue);
		पूर्ण अन्यथा अगर (!list_empty(&csdata->dataind_queue)) अणु
			data = cs_pop_entry(&csdata->dataind_queue);
			csdata->dataind_pending--;
		पूर्ण अन्यथा अणु
			data = 0;
		पूर्ण
		spin_unlock_bh(&csdata->lock);

		अगर (data)
			अवरोध;
		अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			जाओ out;
		पूर्ण अन्यथा अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			जाओ out;
		पूर्ण
		prepare_to_रुको_exclusive(&csdata->रुको, &रुको,
						TASK_INTERRUPTIBLE);
		schedule();
		finish_रुको(&csdata->रुको, &रुको);
	पूर्ण

	retval = put_user(data, (u32 __user *)buf);
	अगर (!retval)
		retval = माप(data);

out:
	वापस retval;
पूर्ण

अटल sमाप_प्रकार cs_अक्षर_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *unused)
अणु
	काष्ठा cs_अक्षर *csdata = file->निजी_data;
	u32 data;
	पूर्णांक err;
	sमाप_प्रकार	retval;

	अगर (count < माप(data))
		वापस -EINVAL;

	अगर (get_user(data, (u32 __user *)buf))
		retval = -EFAULT;
	अन्यथा
		retval = count;

	err = cs_hsi_command(csdata->hi, data);
	अगर (err < 0)
		retval = err;

	वापस retval;
पूर्ण

अटल दीर्घ cs_अक्षर_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा cs_अक्षर *csdata = file->निजी_data;
	पूर्णांक r = 0;

	चयन (cmd) अणु
	हाल CS_GET_STATE: अणु
		अचिन्हित पूर्णांक state;

		state = cs_hsi_get_state(csdata->hi);
		अगर (copy_to_user((व्योम __user *)arg, &state, माप(state)))
			r = -EFAULT;

		अवरोध;
	पूर्ण
	हाल CS_SET_WAKELINE: अणु
		अचिन्हित पूर्णांक state;

		अगर (copy_from_user(&state, (व्योम __user *)arg, माप(state))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (state > 1) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		cs_hsi_set_wakeline(csdata->hi, !!state);

		अवरोध;
	पूर्ण
	हाल CS_GET_IF_VERSION: अणु
		अचिन्हित पूर्णांक अगरver = CS_IF_VERSION;

		अगर (copy_to_user((व्योम __user *)arg, &अगरver, माप(अगरver)))
			r = -EFAULT;

		अवरोध;
	पूर्ण
	हाल CS_CONFIG_BUFS: अणु
		काष्ठा cs_buffer_config buf_cfg;

		अगर (copy_from_user(&buf_cfg, (व्योम __user *)arg,
							माप(buf_cfg)))
			r = -EFAULT;
		अन्यथा
			r = cs_hsi_buf_config(csdata->hi, &buf_cfg);

		अवरोध;
	पूर्ण
	शेष:
		r = -ENOTTY;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक cs_अक्षर_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_end < vma->vm_start)
		वापस -EINVAL;

	अगर (vma_pages(vma) != 1)
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_DONTDUMP | VM_DONTEXPAND;
	vma->vm_ops = &cs_अक्षर_vm_ops;
	vma->vm_निजी_data = file->निजी_data;

	वापस 0;
पूर्ण

अटल पूर्णांक cs_अक्षर_खोलो(काष्ठा inode *unused, काष्ठा file *file)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ p;

	spin_lock_bh(&cs_अक्षर_data.lock);
	अगर (cs_अक्षर_data.खोलोed) अणु
		ret = -EBUSY;
		spin_unlock_bh(&cs_अक्षर_data.lock);
		जाओ out1;
	पूर्ण
	cs_अक्षर_data.खोलोed = 1;
	cs_अक्षर_data.dataind_pending = 0;
	spin_unlock_bh(&cs_अक्षर_data.lock);

	p = get_zeroed_page(GFP_KERNEL);
	अगर (!p) अणु
		ret = -ENOMEM;
		जाओ out2;
	पूर्ण

	ret = cs_hsi_start(&cs_अक्षर_data.hi, cs_अक्षर_data.cl, p, CS_MMAP_SIZE);
	अगर (ret) अणु
		dev_err(&cs_अक्षर_data.cl->device, "Unable to initialize HSI\n");
		जाओ out3;
	पूर्ण

	/* these are only used in release so lock not needed */
	cs_अक्षर_data.mmap_base = p;
	cs_अक्षर_data.mmap_size = CS_MMAP_SIZE;

	file->निजी_data = &cs_अक्षर_data;

	वापस 0;

out3:
	मुक्त_page(p);
out2:
	spin_lock_bh(&cs_अक्षर_data.lock);
	cs_अक्षर_data.खोलोed = 0;
	spin_unlock_bh(&cs_अक्षर_data.lock);
out1:
	वापस ret;
पूर्ण

अटल व्योम cs_मुक्त_अक्षर_queue(काष्ठा list_head *head)
अणु
	काष्ठा अक्षर_queue *entry;
	काष्ठा list_head *cursor, *next;

	अगर (!list_empty(head)) अणु
		list_क्रम_each_safe(cursor, next, head) अणु
			entry = list_entry(cursor, काष्ठा अक्षर_queue, list);
			list_del(&entry->list);
			kमुक्त(entry);
		पूर्ण
	पूर्ण

पूर्ण

अटल पूर्णांक cs_अक्षर_release(काष्ठा inode *unused, काष्ठा file *file)
अणु
	काष्ठा cs_अक्षर *csdata = file->निजी_data;

	cs_hsi_stop(csdata->hi);
	spin_lock_bh(&csdata->lock);
	csdata->hi = शून्य;
	मुक्त_page(csdata->mmap_base);
	cs_मुक्त_अक्षर_queue(&csdata->अक्षरdev_queue);
	cs_मुक्त_अक्षर_queue(&csdata->dataind_queue);
	csdata->खोलोed = 0;
	spin_unlock_bh(&csdata->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations cs_अक्षर_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= cs_अक्षर_पढ़ो,
	.ग_लिखो		= cs_अक्षर_ग_लिखो,
	.poll		= cs_अक्षर_poll,
	.unlocked_ioctl	= cs_अक्षर_ioctl,
	.mmap		= cs_अक्षर_mmap,
	.खोलो		= cs_अक्षर_खोलो,
	.release	= cs_अक्षर_release,
	.fasync		= cs_अक्षर_fasync,
पूर्ण;

अटल काष्ठा miscdevice cs_अक्षर_miscdev = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "cmt_speech",
	.fops	= &cs_अक्षर_fops
पूर्ण;

अटल पूर्णांक cs_hsi_client_probe(काष्ठा device *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा hsi_client *cl = to_hsi_client(dev);

	dev_dbg(dev, "hsi_client_probe\n");
	init_रुकोqueue_head(&cs_अक्षर_data.रुको);
	spin_lock_init(&cs_अक्षर_data.lock);
	cs_अक्षर_data.खोलोed = 0;
	cs_अक्षर_data.cl = cl;
	cs_अक्षर_data.hi = शून्य;
	INIT_LIST_HEAD(&cs_अक्षर_data.अक्षरdev_queue);
	INIT_LIST_HEAD(&cs_अक्षर_data.dataind_queue);

	cs_अक्षर_data.channel_id_cmd = hsi_get_channel_id_by_name(cl,
		"speech-control");
	अगर (cs_अक्षर_data.channel_id_cmd < 0) अणु
		err = cs_अक्षर_data.channel_id_cmd;
		dev_err(dev, "Could not get cmd channel (%d)\n", err);
		वापस err;
	पूर्ण

	cs_अक्षर_data.channel_id_data = hsi_get_channel_id_by_name(cl,
		"speech-data");
	अगर (cs_अक्षर_data.channel_id_data < 0) अणु
		err = cs_अक्षर_data.channel_id_data;
		dev_err(dev, "Could not get data channel (%d)\n", err);
		वापस err;
	पूर्ण

	err = misc_रेजिस्टर(&cs_अक्षर_miscdev);
	अगर (err)
		dev_err(dev, "Failed to register: %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक cs_hsi_client_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा cs_hsi_अगरace *hi;

	dev_dbg(dev, "hsi_client_remove\n");
	misc_deरेजिस्टर(&cs_अक्षर_miscdev);
	spin_lock_bh(&cs_अक्षर_data.lock);
	hi = cs_अक्षर_data.hi;
	cs_अक्षर_data.hi = शून्य;
	spin_unlock_bh(&cs_अक्षर_data.lock);
	अगर (hi)
		cs_hsi_stop(hi);

	वापस 0;
पूर्ण

अटल काष्ठा hsi_client_driver cs_hsi_driver = अणु
	.driver = अणु
		.name	= "cmt-speech",
		.owner	= THIS_MODULE,
		.probe	= cs_hsi_client_probe,
		.हटाओ	= cs_hsi_client_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cs_अक्षर_init(व्योम)
अणु
	pr_info("CMT speech driver added\n");
	वापस hsi_रेजिस्टर_client_driver(&cs_hsi_driver);
पूर्ण
module_init(cs_अक्षर_init);

अटल व्योम __निकास cs_अक्षर_निकास(व्योम)
अणु
	hsi_unरेजिस्टर_client_driver(&cs_hsi_driver);
	pr_info("CMT speech driver removed\n");
पूर्ण
module_निकास(cs_अक्षर_निकास);

MODULE_ALIAS("hsi:cmt-speech");
MODULE_AUTHOR("Kai Vehmanen <kai.vehmanen@nokia.com>");
MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@nokia.com>");
MODULE_DESCRIPTION("CMT speech driver");
MODULE_LICENSE("GPL v2");
