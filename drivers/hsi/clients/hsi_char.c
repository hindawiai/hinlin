<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HSI अक्षरacter device driver, implements the अक्षरacter device
 * पूर्णांकerface.
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 *
 * Contact: Andras Domokos <andras.करोmokos@nokia.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/रुको.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/hsi/hsi.h>
#समावेश <linux/hsi/hsi_अक्षर.h>

#घोषणा HSC_DEVS		16 /* Num of channels */
#घोषणा HSC_MSGS		4

#घोषणा HSC_RXBREAK		0

#घोषणा HSC_ID_BITS		6
#घोषणा HSC_PORT_ID_BITS	4
#घोषणा HSC_ID_MASK		3
#घोषणा HSC_PORT_ID_MASK	3
#घोषणा HSC_CH_MASK		0xf

/*
 * We support up to 4 controllers that can have up to 4
 * ports, which should currently be more than enough.
 */
#घोषणा HSC_BASEMINOR(id, port_id) \
		((((id) & HSC_ID_MASK) << HSC_ID_BITS) | \
		(((port_id) & HSC_PORT_ID_MASK) << HSC_PORT_ID_BITS))

क्रमागत अणु
	HSC_CH_OPEN,
	HSC_CH_READ,
	HSC_CH_WRITE,
	HSC_CH_WLINE,
पूर्ण;

क्रमागत अणु
	HSC_RX,
	HSC_TX,
पूर्ण;

काष्ठा hsc_client_data;
/**
 * काष्ठा hsc_channel - hsi_अक्षर पूर्णांकernal channel data
 * @ch: channel number
 * @flags: Keeps state of the channel (खोलो/बंद, पढ़ोing, writing)
 * @मुक्त_msgs_list: List of मुक्त HSI messages/requests
 * @rx_msgs_queue: List of pending RX requests
 * @tx_msgs_queue: List of pending TX requests
 * @lock: Serialize access to the lists
 * @cl: reference to the associated hsi_client
 * @cl_data: reference to the client data that this channels beदीर्घs to
 * @rx_रुको: RX requests रुको queue
 * @tx_रुको: TX requests रुको queue
 */
काष्ठा hsc_channel अणु
	अचिन्हित पूर्णांक		ch;
	अचिन्हित दीर्घ		flags;
	काष्ठा list_head	मुक्त_msgs_list;
	काष्ठा list_head	rx_msgs_queue;
	काष्ठा list_head	tx_msgs_queue;
	spinlock_t		lock;
	काष्ठा hsi_client	*cl;
	काष्ठा hsc_client_data *cl_data;
	रुको_queue_head_t	rx_रुको;
	रुको_queue_head_t	tx_रुको;
पूर्ण;

/**
 * काष्ठा hsc_client_data - hsi_अक्षर पूर्णांकernal client data
 * @cdev: Characther device associated to the hsi_client
 * @lock: Lock to serialize खोलो/बंद access
 * @flags: Keeps track of port state (rx hwअवरोध armed)
 * @usecnt: Use count क्रम claiming the HSI port (mutex रक्षित)
 * @cl: Referece to the HSI client
 * @channels: Array of channels accessible by the client
 */
काष्ठा hsc_client_data अणु
	काष्ठा cdev		cdev;
	काष्ठा mutex		lock;
	अचिन्हित दीर्घ		flags;
	अचिन्हित पूर्णांक		usecnt;
	काष्ठा hsi_client	*cl;
	काष्ठा hsc_channel	channels[HSC_DEVS];
पूर्ण;

/* Stores the major number dynamically allocated क्रम hsi_अक्षर */
अटल अचिन्हित पूर्णांक hsc_major;
/* Maximum buffer size that hsi_अक्षर will accept from userspace */
अटल अचिन्हित पूर्णांक max_data_size = 0x1000;
module_param(max_data_size, uपूर्णांक, 0);
MODULE_PARM_DESC(max_data_size, "max पढ़ो/ग_लिखो data size [4,8..65536] (^2)");

अटल व्योम hsc_add_tail(काष्ठा hsc_channel *channel, काष्ठा hsi_msg *msg,
							काष्ठा list_head *queue)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&channel->lock, flags);
	list_add_tail(&msg->link, queue);
	spin_unlock_irqrestore(&channel->lock, flags);
पूर्ण

अटल काष्ठा hsi_msg *hsc_get_first_msg(काष्ठा hsc_channel *channel,
							काष्ठा list_head *queue)
अणु
	काष्ठा hsi_msg *msg = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&channel->lock, flags);

	अगर (list_empty(queue))
		जाओ out;

	msg = list_first_entry(queue, काष्ठा hsi_msg, link);
	list_del(&msg->link);
out:
	spin_unlock_irqrestore(&channel->lock, flags);

	वापस msg;
पूर्ण

अटल अंतरभूत व्योम hsc_msg_मुक्त(काष्ठा hsi_msg *msg)
अणु
	kमुक्त(sg_virt(msg->sgt.sgl));
	hsi_मुक्त_msg(msg);
पूर्ण

अटल व्योम hsc_मुक्त_list(काष्ठा list_head *list)
अणु
	काष्ठा hsi_msg *msg, *पंचांगp;

	list_क्रम_each_entry_safe(msg, पंचांगp, list, link) अणु
		list_del(&msg->link);
		hsc_msg_मुक्त(msg);
	पूर्ण
पूर्ण

अटल व्योम hsc_reset_list(काष्ठा hsc_channel *channel, काष्ठा list_head *l)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);

	spin_lock_irqsave(&channel->lock, flags);
	list_splice_init(l, &list);
	spin_unlock_irqrestore(&channel->lock, flags);

	hsc_मुक्त_list(&list);
पूर्ण

अटल अंतरभूत काष्ठा hsi_msg *hsc_msg_alloc(अचिन्हित पूर्णांक alloc_size)
अणु
	काष्ठा hsi_msg *msg;
	व्योम *buf;

	msg = hsi_alloc_msg(1, GFP_KERNEL);
	अगर (!msg)
		जाओ out;
	buf = kदो_स्मृति(alloc_size, GFP_KERNEL);
	अगर (!buf) अणु
		hsi_मुक्त_msg(msg);
		जाओ out;
	पूर्ण
	sg_init_one(msg->sgt.sgl, buf, alloc_size);
	/* Ignore false positive, due to sg poपूर्णांकer handling */
	kmemleak_ignore(buf);

	वापस msg;
out:
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक hsc_msgs_alloc(काष्ठा hsc_channel *channel)
अणु
	काष्ठा hsi_msg *msg;
	पूर्णांक i;

	क्रम (i = 0; i < HSC_MSGS; i++) अणु
		msg = hsc_msg_alloc(max_data_size);
		अगर (!msg)
			जाओ out;
		msg->channel = channel->ch;
		list_add_tail(&msg->link, &channel->मुक्त_msgs_list);
	पूर्ण

	वापस 0;
out:
	hsc_मुक्त_list(&channel->मुक्त_msgs_list);

	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hsc_msg_len_get(काष्ठा hsi_msg *msg)
अणु
	वापस msg->sgt.sgl->length;
पूर्ण

अटल अंतरभूत व्योम hsc_msg_len_set(काष्ठा hsi_msg *msg, अचिन्हित पूर्णांक len)
अणु
	msg->sgt.sgl->length = len;
पूर्ण

अटल व्योम hsc_rx_completed(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsc_client_data *cl_data = hsi_client_drvdata(msg->cl);
	काष्ठा hsc_channel *channel = cl_data->channels + msg->channel;

	अगर (test_bit(HSC_CH_READ, &channel->flags)) अणु
		hsc_add_tail(channel, msg, &channel->rx_msgs_queue);
		wake_up(&channel->rx_रुको);
	पूर्ण अन्यथा अणु
		hsc_add_tail(channel, msg, &channel->मुक्त_msgs_list);
	पूर्ण
पूर्ण

अटल व्योम hsc_rx_msg_deकाष्ठाor(काष्ठा hsi_msg *msg)
अणु
	msg->status = HSI_STATUS_ERROR;
	hsc_msg_len_set(msg, 0);
	hsc_rx_completed(msg);
पूर्ण

अटल व्योम hsc_tx_completed(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsc_client_data *cl_data = hsi_client_drvdata(msg->cl);
	काष्ठा hsc_channel *channel = cl_data->channels + msg->channel;

	अगर (test_bit(HSC_CH_WRITE, &channel->flags)) अणु
		hsc_add_tail(channel, msg, &channel->tx_msgs_queue);
		wake_up(&channel->tx_रुको);
	पूर्ण अन्यथा अणु
		hsc_add_tail(channel, msg, &channel->मुक्त_msgs_list);
	पूर्ण
पूर्ण

अटल व्योम hsc_tx_msg_deकाष्ठाor(काष्ठा hsi_msg *msg)
अणु
	msg->status = HSI_STATUS_ERROR;
	hsc_msg_len_set(msg, 0);
	hsc_tx_completed(msg);
पूर्ण

अटल व्योम hsc_अवरोध_req_deकाष्ठाor(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsc_client_data *cl_data = hsi_client_drvdata(msg->cl);

	hsi_मुक्त_msg(msg);
	clear_bit(HSC_RXBREAK, &cl_data->flags);
पूर्ण

अटल व्योम hsc_अवरोध_received(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsc_client_data *cl_data = hsi_client_drvdata(msg->cl);
	काष्ठा hsc_channel *channel = cl_data->channels;
	पूर्णांक i, ret;

	/* Broadcast HWBREAK on all channels */
	क्रम (i = 0; i < HSC_DEVS; i++, channel++) अणु
		काष्ठा hsi_msg *msg2;

		अगर (!test_bit(HSC_CH_READ, &channel->flags))
			जारी;
		msg2 = hsc_get_first_msg(channel, &channel->मुक्त_msgs_list);
		अगर (!msg2)
			जारी;
		clear_bit(HSC_CH_READ, &channel->flags);
		hsc_msg_len_set(msg2, 0);
		msg2->status = HSI_STATUS_COMPLETED;
		hsc_add_tail(channel, msg2, &channel->rx_msgs_queue);
		wake_up(&channel->rx_रुको);
	पूर्ण
	hsi_flush(msg->cl);
	ret = hsi_async_पढ़ो(msg->cl, msg);
	अगर (ret < 0)
		hsc_अवरोध_req_deकाष्ठाor(msg);
पूर्ण

अटल पूर्णांक hsc_अवरोध_request(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsc_client_data *cl_data = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *msg;
	पूर्णांक ret;

	अगर (test_and_set_bit(HSC_RXBREAK, &cl_data->flags))
		वापस -EBUSY;

	msg = hsi_alloc_msg(0, GFP_KERNEL);
	अगर (!msg) अणु
		clear_bit(HSC_RXBREAK, &cl_data->flags);
		वापस -ENOMEM;
	पूर्ण
	msg->अवरोध_frame = 1;
	msg->complete = hsc_अवरोध_received;
	msg->deकाष्ठाor = hsc_अवरोध_req_deकाष्ठाor;
	ret = hsi_async_पढ़ो(cl, msg);
	अगर (ret < 0)
		hsc_अवरोध_req_deकाष्ठाor(msg);

	वापस ret;
पूर्ण

अटल पूर्णांक hsc_अवरोध_send(काष्ठा hsi_client *cl)
अणु
	काष्ठा hsi_msg *msg;
	पूर्णांक ret;

	msg = hsi_alloc_msg(0, GFP_ATOMIC);
	अगर (!msg)
		वापस -ENOMEM;
	msg->अवरोध_frame = 1;
	msg->complete = hsi_मुक्त_msg;
	msg->deकाष्ठाor = hsi_मुक्त_msg;
	ret = hsi_async_ग_लिखो(cl, msg);
	अगर (ret < 0)
		hsi_मुक्त_msg(msg);

	वापस ret;
पूर्ण

अटल पूर्णांक hsc_rx_set(काष्ठा hsi_client *cl, काष्ठा hsc_rx_config *rxc)
अणु
	काष्ठा hsi_config पंचांगp;
	पूर्णांक ret;

	अगर ((rxc->mode != HSI_MODE_STREAM) && (rxc->mode != HSI_MODE_FRAME))
		वापस -EINVAL;
	अगर ((rxc->channels == 0) || (rxc->channels > HSC_DEVS))
		वापस -EINVAL;
	अगर (rxc->channels & (rxc->channels - 1))
		वापस -EINVAL;
	अगर ((rxc->flow != HSI_FLOW_SYNC) && (rxc->flow != HSI_FLOW_PIPE))
		वापस -EINVAL;
	पंचांगp = cl->rx_cfg;
	cl->rx_cfg.mode = rxc->mode;
	cl->rx_cfg.num_hw_channels = rxc->channels;
	cl->rx_cfg.flow = rxc->flow;
	ret = hsi_setup(cl);
	अगर (ret < 0) अणु
		cl->rx_cfg = पंचांगp;
		वापस ret;
	पूर्ण
	अगर (rxc->mode == HSI_MODE_FRAME)
		hsc_अवरोध_request(cl);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम hsc_rx_get(काष्ठा hsi_client *cl, काष्ठा hsc_rx_config *rxc)
अणु
	rxc->mode = cl->rx_cfg.mode;
	rxc->channels = cl->rx_cfg.num_hw_channels;
	rxc->flow = cl->rx_cfg.flow;
पूर्ण

अटल पूर्णांक hsc_tx_set(काष्ठा hsi_client *cl, काष्ठा hsc_tx_config *txc)
अणु
	काष्ठा hsi_config पंचांगp;
	पूर्णांक ret;

	अगर ((txc->mode != HSI_MODE_STREAM) && (txc->mode != HSI_MODE_FRAME))
		वापस -EINVAL;
	अगर ((txc->channels == 0) || (txc->channels > HSC_DEVS))
		वापस -EINVAL;
	अगर (txc->channels & (txc->channels - 1))
		वापस -EINVAL;
	अगर ((txc->arb_mode != HSI_ARB_RR) && (txc->arb_mode != HSI_ARB_PRIO))
		वापस -EINVAL;
	पंचांगp = cl->tx_cfg;
	cl->tx_cfg.mode = txc->mode;
	cl->tx_cfg.num_hw_channels = txc->channels;
	cl->tx_cfg.speed = txc->speed;
	cl->tx_cfg.arb_mode = txc->arb_mode;
	ret = hsi_setup(cl);
	अगर (ret < 0) अणु
		cl->tx_cfg = पंचांगp;
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम hsc_tx_get(काष्ठा hsi_client *cl, काष्ठा hsc_tx_config *txc)
अणु
	txc->mode = cl->tx_cfg.mode;
	txc->channels = cl->tx_cfg.num_hw_channels;
	txc->speed = cl->tx_cfg.speed;
	txc->arb_mode = cl->tx_cfg.arb_mode;
पूर्ण

अटल sमाप_प्रकार hsc_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार len,
						loff_t *ppos __maybe_unused)
अणु
	काष्ठा hsc_channel *channel = file->निजी_data;
	काष्ठा hsi_msg *msg;
	sमाप_प्रकार ret;

	अगर (len == 0)
		वापस 0;
	अगर (!IS_ALIGNED(len, माप(u32)))
		वापस -EINVAL;
	अगर (len > max_data_size)
		len = max_data_size;
	अगर (channel->ch >= channel->cl->rx_cfg.num_hw_channels)
		वापस -ECHRNG;
	अगर (test_and_set_bit(HSC_CH_READ, &channel->flags))
		वापस -EBUSY;
	msg = hsc_get_first_msg(channel, &channel->मुक्त_msgs_list);
	अगर (!msg) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण
	hsc_msg_len_set(msg, len);
	msg->complete = hsc_rx_completed;
	msg->deकाष्ठाor = hsc_rx_msg_deकाष्ठाor;
	ret = hsi_async_पढ़ो(channel->cl, msg);
	अगर (ret < 0) अणु
		hsc_add_tail(channel, msg, &channel->मुक्त_msgs_list);
		जाओ out;
	पूर्ण

	ret = रुको_event_पूर्णांकerruptible(channel->rx_रुको,
					!list_empty(&channel->rx_msgs_queue));
	अगर (ret < 0) अणु
		clear_bit(HSC_CH_READ, &channel->flags);
		hsi_flush(channel->cl);
		वापस -EINTR;
	पूर्ण

	msg = hsc_get_first_msg(channel, &channel->rx_msgs_queue);
	अगर (msg) अणु
		अगर (msg->status != HSI_STATUS_ERROR) अणु
			ret = copy_to_user((व्योम __user *)buf,
			sg_virt(msg->sgt.sgl), hsc_msg_len_get(msg));
			अगर (ret)
				ret = -EFAULT;
			अन्यथा
				ret = hsc_msg_len_get(msg);
		पूर्ण अन्यथा अणु
			ret = -EIO;
		पूर्ण
		hsc_add_tail(channel, msg, &channel->मुक्त_msgs_list);
	पूर्ण
out:
	clear_bit(HSC_CH_READ, &channel->flags);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार hsc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार len,
						loff_t *ppos __maybe_unused)
अणु
	काष्ठा hsc_channel *channel = file->निजी_data;
	काष्ठा hsi_msg *msg;
	sमाप_प्रकार ret;

	अगर ((len == 0) || !IS_ALIGNED(len, माप(u32)))
		वापस -EINVAL;
	अगर (len > max_data_size)
		len = max_data_size;
	अगर (channel->ch >= channel->cl->tx_cfg.num_hw_channels)
		वापस -ECHRNG;
	अगर (test_and_set_bit(HSC_CH_WRITE, &channel->flags))
		वापस -EBUSY;
	msg = hsc_get_first_msg(channel, &channel->मुक्त_msgs_list);
	अगर (!msg) अणु
		clear_bit(HSC_CH_WRITE, &channel->flags);
		वापस -ENOSPC;
	पूर्ण
	अगर (copy_from_user(sg_virt(msg->sgt.sgl), (व्योम __user *)buf, len)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	hsc_msg_len_set(msg, len);
	msg->complete = hsc_tx_completed;
	msg->deकाष्ठाor = hsc_tx_msg_deकाष्ठाor;
	ret = hsi_async_ग_लिखो(channel->cl, msg);
	अगर (ret < 0)
		जाओ out;

	ret = रुको_event_पूर्णांकerruptible(channel->tx_रुको,
					!list_empty(&channel->tx_msgs_queue));
	अगर (ret < 0) अणु
		clear_bit(HSC_CH_WRITE, &channel->flags);
		hsi_flush(channel->cl);
		वापस -EINTR;
	पूर्ण

	msg = hsc_get_first_msg(channel, &channel->tx_msgs_queue);
	अगर (msg) अणु
		अगर (msg->status == HSI_STATUS_ERROR)
			ret = -EIO;
		अन्यथा
			ret = hsc_msg_len_get(msg);

		hsc_add_tail(channel, msg, &channel->मुक्त_msgs_list);
	पूर्ण
out:
	clear_bit(HSC_CH_WRITE, &channel->flags);

	वापस ret;
पूर्ण

अटल दीर्घ hsc_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hsc_channel *channel = file->निजी_data;
	अचिन्हित पूर्णांक state;
	काष्ठा hsc_rx_config rxc;
	काष्ठा hsc_tx_config txc;
	दीर्घ ret = 0;

	चयन (cmd) अणु
	हाल HSC_RESET:
		hsi_flush(channel->cl);
		अवरोध;
	हाल HSC_SET_PM:
		अगर (copy_from_user(&state, (व्योम __user *)arg, माप(state)))
			वापस -EFAULT;
		अगर (state == HSC_PM_DISABLE) अणु
			अगर (test_and_set_bit(HSC_CH_WLINE, &channel->flags))
				वापस -EINVAL;
			ret = hsi_start_tx(channel->cl);
		पूर्ण अन्यथा अगर (state == HSC_PM_ENABLE) अणु
			अगर (!test_and_clear_bit(HSC_CH_WLINE, &channel->flags))
				वापस -EINVAL;
			ret = hsi_stop_tx(channel->cl);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल HSC_SEND_BREAK:
		वापस hsc_अवरोध_send(channel->cl);
	हाल HSC_SET_RX:
		अगर (copy_from_user(&rxc, (व्योम __user *)arg, माप(rxc)))
			वापस -EFAULT;
		वापस hsc_rx_set(channel->cl, &rxc);
	हाल HSC_GET_RX:
		hsc_rx_get(channel->cl, &rxc);
		अगर (copy_to_user((व्योम __user *)arg, &rxc, माप(rxc)))
			वापस -EFAULT;
		अवरोध;
	हाल HSC_SET_TX:
		अगर (copy_from_user(&txc, (व्योम __user *)arg, माप(txc)))
			वापस -EFAULT;
		वापस hsc_tx_set(channel->cl, &txc);
	हाल HSC_GET_TX:
		hsc_tx_get(channel->cl, &txc);
		अगर (copy_to_user((व्योम __user *)arg, &txc, माप(txc)))
			वापस -EFAULT;
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम __hsc_port_release(काष्ठा hsc_client_data *cl_data)
अणु
	BUG_ON(cl_data->usecnt == 0);

	अगर (--cl_data->usecnt == 0) अणु
		hsi_flush(cl_data->cl);
		hsi_release_port(cl_data->cl);
	पूर्ण
पूर्ण

अटल पूर्णांक hsc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा hsc_client_data *cl_data;
	काष्ठा hsc_channel *channel;
	पूर्णांक ret = 0;

	pr_debug("open, minor = %d\n", iminor(inode));

	cl_data = container_of(inode->i_cdev, काष्ठा hsc_client_data, cdev);
	mutex_lock(&cl_data->lock);
	channel = cl_data->channels + (iminor(inode) & HSC_CH_MASK);

	अगर (test_and_set_bit(HSC_CH_OPEN, &channel->flags)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	/*
	 * Check अगर we have alपढ़ोy claimed the port associated to the HSI
	 * client. If not then try to claim it, अन्यथा increase its refcount
	 */
	अगर (cl_data->usecnt == 0) अणु
		ret = hsi_claim_port(cl_data->cl, 0);
		अगर (ret < 0)
			जाओ out;
		hsi_setup(cl_data->cl);
	पूर्ण
	cl_data->usecnt++;

	ret = hsc_msgs_alloc(channel);
	अगर (ret < 0) अणु
		__hsc_port_release(cl_data);
		जाओ out;
	पूर्ण

	file->निजी_data = channel;
	mutex_unlock(&cl_data->lock);

	वापस ret;
out:
	mutex_unlock(&cl_data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hsc_release(काष्ठा inode *inode __maybe_unused, काष्ठा file *file)
अणु
	काष्ठा hsc_channel *channel = file->निजी_data;
	काष्ठा hsc_client_data *cl_data = channel->cl_data;

	mutex_lock(&cl_data->lock);
	file->निजी_data = शून्य;
	अगर (test_and_clear_bit(HSC_CH_WLINE, &channel->flags))
		hsi_stop_tx(channel->cl);
	__hsc_port_release(cl_data);
	hsc_reset_list(channel, &channel->rx_msgs_queue);
	hsc_reset_list(channel, &channel->tx_msgs_queue);
	hsc_reset_list(channel, &channel->मुक्त_msgs_list);
	clear_bit(HSC_CH_READ, &channel->flags);
	clear_bit(HSC_CH_WRITE, &channel->flags);
	clear_bit(HSC_CH_OPEN, &channel->flags);
	wake_up(&channel->rx_रुको);
	wake_up(&channel->tx_रुको);
	mutex_unlock(&cl_data->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations hsc_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= hsc_पढ़ो,
	.ग_लिखो		= hsc_ग_लिखो,
	.unlocked_ioctl	= hsc_ioctl,
	.खोलो		= hsc_खोलो,
	.release	= hsc_release,
पूर्ण;

अटल व्योम hsc_channel_init(काष्ठा hsc_channel *channel)
अणु
	init_रुकोqueue_head(&channel->rx_रुको);
	init_रुकोqueue_head(&channel->tx_रुको);
	spin_lock_init(&channel->lock);
	INIT_LIST_HEAD(&channel->मुक्त_msgs_list);
	INIT_LIST_HEAD(&channel->rx_msgs_queue);
	INIT_LIST_HEAD(&channel->tx_msgs_queue);
पूर्ण

अटल पूर्णांक hsc_probe(काष्ठा device *dev)
अणु
	स्थिर अक्षर devname[] = "hsi_char";
	काष्ठा hsc_client_data *cl_data;
	काष्ठा hsc_channel *channel;
	काष्ठा hsi_client *cl = to_hsi_client(dev);
	अचिन्हित पूर्णांक hsc_baseminor;
	dev_t hsc_dev;
	पूर्णांक ret;
	पूर्णांक i;

	cl_data = kzalloc(माप(*cl_data), GFP_KERNEL);
	अगर (!cl_data)
		वापस -ENOMEM;

	hsc_baseminor = HSC_BASEMINOR(hsi_id(cl), hsi_port_id(cl));
	अगर (!hsc_major) अणु
		ret = alloc_chrdev_region(&hsc_dev, hsc_baseminor,
						HSC_DEVS, devname);
		अगर (ret == 0)
			hsc_major = MAJOR(hsc_dev);
	पूर्ण अन्यथा अणु
		hsc_dev = MKDEV(hsc_major, hsc_baseminor);
		ret = रेजिस्टर_chrdev_region(hsc_dev, HSC_DEVS, devname);
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(dev, "Device %s allocation failed %d\n",
					hsc_major ? "minor" : "major", ret);
		जाओ out1;
	पूर्ण
	mutex_init(&cl_data->lock);
	hsi_client_set_drvdata(cl, cl_data);
	cdev_init(&cl_data->cdev, &hsc_fops);
	cl_data->cdev.owner = THIS_MODULE;
	cl_data->cl = cl;
	क्रम (i = 0, channel = cl_data->channels; i < HSC_DEVS; i++, channel++) अणु
		hsc_channel_init(channel);
		channel->ch = i;
		channel->cl = cl;
		channel->cl_data = cl_data;
	पूर्ण

	/* 1 hsi client -> N अक्षर devices (one क्रम each channel) */
	ret = cdev_add(&cl_data->cdev, hsc_dev, HSC_DEVS);
	अगर (ret) अणु
		dev_err(dev, "Could not add char device %d\n", ret);
		जाओ out2;
	पूर्ण

	वापस 0;
out2:
	unरेजिस्टर_chrdev_region(hsc_dev, HSC_DEVS);
out1:
	kमुक्त(cl_data);

	वापस ret;
पूर्ण

अटल पूर्णांक hsc_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा hsi_client *cl = to_hsi_client(dev);
	काष्ठा hsc_client_data *cl_data = hsi_client_drvdata(cl);
	dev_t hsc_dev = cl_data->cdev.dev;

	cdev_del(&cl_data->cdev);
	unरेजिस्टर_chrdev_region(hsc_dev, HSC_DEVS);
	hsi_client_set_drvdata(cl, शून्य);
	kमुक्त(cl_data);

	वापस 0;
पूर्ण

अटल काष्ठा hsi_client_driver hsc_driver = अणु
	.driver = अणु
		.name	= "hsi_char",
		.owner	= THIS_MODULE,
		.probe	= hsc_probe,
		.हटाओ	= hsc_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hsc_init(व्योम)
अणु
	पूर्णांक ret;

	अगर ((max_data_size < 4) || (max_data_size > 0x10000) ||
		(max_data_size & (max_data_size - 1))) अणु
		pr_err("Invalid max read/write data size\n");
		वापस -EINVAL;
	पूर्ण

	ret = hsi_रेजिस्टर_client_driver(&hsc_driver);
	अगर (ret) अणु
		pr_err("Error while registering HSI/SSI driver %d\n", ret);
		वापस ret;
	पूर्ण

	pr_info("HSI/SSI char device loaded\n");

	वापस 0;
पूर्ण
module_init(hsc_init);

अटल व्योम __निकास hsc_निकास(व्योम)
अणु
	hsi_unरेजिस्टर_client_driver(&hsc_driver);
	pr_info("HSI char device removed\n");
पूर्ण
module_निकास(hsc_निकास);

MODULE_AUTHOR("Andras Domokos <andras.domokos@nokia.com>");
MODULE_ALIAS("hsi:hsi_char");
MODULE_DESCRIPTION("HSI character device");
MODULE_LICENSE("GPL v2");
