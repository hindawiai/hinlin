<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel SST generic IPC Support
 *
 * Copyright (C) 2015, Intel Corporation. All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/asound.h>

#समावेश "sst-dsp.h"
#समावेश "sst-dsp-priv.h"
#समावेश "sst-ipc.h"

/* IPC message समयout (msecs) */
#घोषणा IPC_TIMEOUT_MSECS	300

#घोषणा IPC_EMPTY_LIST_SIZE	8

/* locks held by caller */
अटल काष्ठा ipc_message *msg_get_empty(काष्ठा sst_generic_ipc *ipc)
अणु
	काष्ठा ipc_message *msg = शून्य;

	अगर (!list_empty(&ipc->empty_list)) अणु
		msg = list_first_entry(&ipc->empty_list, काष्ठा ipc_message,
			list);
		list_del(&msg->list);
	पूर्ण

	वापस msg;
पूर्ण

अटल पूर्णांक tx_रुको_करोne(काष्ठा sst_generic_ipc *ipc,
	काष्ठा ipc_message *msg, काष्ठा sst_ipc_message *reply)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* रुको क्रम DSP completion (in all हालs aपंचांग inc pending) */
	ret = रुको_event_समयout(msg->रुकोq, msg->complete,
		msecs_to_jअगरfies(IPC_TIMEOUT_MSECS));

	spin_lock_irqsave(&ipc->dsp->spinlock, flags);
	अगर (ret == 0) अणु
		अगर (ipc->ops.shim_dbg != शून्य)
			ipc->ops.shim_dbg(ipc, "message timeout");

		list_del(&msg->list);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु

		/* copy the data वापसed from DSP */
		अगर (reply) अणु
			reply->header = msg->rx.header;
			अगर (reply->data)
				स_नकल(reply->data, msg->rx.data, msg->rx.size);
		पूर्ण
		ret = msg->त्रुटि_सं;
	पूर्ण

	list_add_tail(&msg->list, &ipc->empty_list);
	spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक ipc_tx_message(काष्ठा sst_generic_ipc *ipc,
	काष्ठा sst_ipc_message request,
	काष्ठा sst_ipc_message *reply, पूर्णांक रुको)
अणु
	काष्ठा ipc_message *msg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipc->dsp->spinlock, flags);

	msg = msg_get_empty(ipc);
	अगर (msg == शून्य) अणु
		spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	msg->tx.header = request.header;
	msg->tx.size = request.size;
	msg->rx.header = 0;
	msg->rx.size = reply ? reply->size : 0;
	msg->रुको = रुको;
	msg->त्रुटि_सं = 0;
	msg->pending = false;
	msg->complete = false;

	अगर ((request.size) && (ipc->ops.tx_data_copy != शून्य))
		ipc->ops.tx_data_copy(msg, request.data, request.size);

	list_add_tail(&msg->list, &ipc->tx_list);
	schedule_work(&ipc->kwork);
	spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);

	अगर (रुको)
		वापस tx_रुको_करोne(ipc, msg, reply);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक msg_empty_list_init(काष्ठा sst_generic_ipc *ipc)
अणु
	पूर्णांक i;

	ipc->msg = kसुस्मृति(IPC_EMPTY_LIST_SIZE, माप(काष्ठा ipc_message),
			   GFP_KERNEL);
	अगर (ipc->msg == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < IPC_EMPTY_LIST_SIZE; i++) अणु
		ipc->msg[i].tx.data = kzalloc(ipc->tx_data_max_size, GFP_KERNEL);
		अगर (ipc->msg[i].tx.data == शून्य)
			जाओ मुक्त_mem;

		ipc->msg[i].rx.data = kzalloc(ipc->rx_data_max_size, GFP_KERNEL);
		अगर (ipc->msg[i].rx.data == शून्य) अणु
			kमुक्त(ipc->msg[i].tx.data);
			जाओ मुक्त_mem;
		पूर्ण

		init_रुकोqueue_head(&ipc->msg[i].रुकोq);
		list_add(&ipc->msg[i].list, &ipc->empty_list);
	पूर्ण

	वापस 0;

मुक्त_mem:
	जबतक (i > 0) अणु
		kमुक्त(ipc->msg[i-1].tx.data);
		kमुक्त(ipc->msg[i-1].rx.data);
		--i;
	पूर्ण
	kमुक्त(ipc->msg);

	वापस -ENOMEM;
पूर्ण

अटल व्योम ipc_tx_msgs(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sst_generic_ipc *ipc =
		container_of(work, काष्ठा sst_generic_ipc, kwork);
	काष्ठा ipc_message *msg;

	spin_lock_irq(&ipc->dsp->spinlock);

	जबतक (!list_empty(&ipc->tx_list) && !ipc->pending) अणु
		/* अगर the DSP is busy, we will TX messages after IRQ.
		 * also postpone अगर we are in the middle of processing
		 * completion irq
		 */
		अगर (ipc->ops.is_dsp_busy && ipc->ops.is_dsp_busy(ipc->dsp)) अणु
			dev_dbg(ipc->dev, "ipc_tx_msgs dsp busy\n");
			अवरोध;
		पूर्ण

		msg = list_first_entry(&ipc->tx_list, काष्ठा ipc_message, list);
		list_move(&msg->list, &ipc->rx_list);

		अगर (ipc->ops.tx_msg != शून्य)
			ipc->ops.tx_msg(ipc, msg);
	पूर्ण

	spin_unlock_irq(&ipc->dsp->spinlock);
पूर्ण

पूर्णांक sst_ipc_tx_message_रुको(काष्ठा sst_generic_ipc *ipc,
	काष्ठा sst_ipc_message request, काष्ठा sst_ipc_message *reply)
अणु
	पूर्णांक ret;

	/*
	 * DSP maybe in lower घातer active state, so
	 * check अगर the DSP supports DSP lp On method
	 * अगर so invoke that beक्रमe sending IPC
	 */
	अगर (ipc->ops.check_dsp_lp_on)
		अगर (ipc->ops.check_dsp_lp_on(ipc->dsp, true))
			वापस -EIO;

	ret = ipc_tx_message(ipc, request, reply, 1);

	अगर (ipc->ops.check_dsp_lp_on)
		अगर (ipc->ops.check_dsp_lp_on(ipc->dsp, false))
			वापस -EIO;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sst_ipc_tx_message_रुको);

पूर्णांक sst_ipc_tx_message_noरुको(काष्ठा sst_generic_ipc *ipc,
	काष्ठा sst_ipc_message request)
अणु
	वापस ipc_tx_message(ipc, request, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sst_ipc_tx_message_noरुको);

पूर्णांक sst_ipc_tx_message_nopm(काष्ठा sst_generic_ipc *ipc,
	काष्ठा sst_ipc_message request, काष्ठा sst_ipc_message *reply)
अणु
	वापस ipc_tx_message(ipc, request, reply, 1);
पूर्ण
EXPORT_SYMBOL_GPL(sst_ipc_tx_message_nopm);

काष्ठा ipc_message *sst_ipc_reply_find_msg(काष्ठा sst_generic_ipc *ipc,
	u64 header)
अणु
	काष्ठा ipc_message *msg;
	u64 mask;

	अगर (ipc->ops.reply_msg_match != शून्य)
		header = ipc->ops.reply_msg_match(header, &mask);
	अन्यथा
		mask = (u64)-1;

	अगर (list_empty(&ipc->rx_list)) अणु
		dev_err(ipc->dev, "error: rx list empty but received 0x%llx\n",
			header);
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(msg, &ipc->rx_list, list) अणु
		अगर ((msg->tx.header & mask) == header)
			वापस msg;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(sst_ipc_reply_find_msg);

/* locks held by caller */
व्योम sst_ipc_tx_msg_reply_complete(काष्ठा sst_generic_ipc *ipc,
	काष्ठा ipc_message *msg)
अणु
	msg->complete = true;

	अगर (!msg->रुको)
		list_add_tail(&msg->list, &ipc->empty_list);
	अन्यथा
		wake_up(&msg->रुकोq);
पूर्ण
EXPORT_SYMBOL_GPL(sst_ipc_tx_msg_reply_complete);

पूर्णांक sst_ipc_init(काष्ठा sst_generic_ipc *ipc)
अणु
	पूर्णांक ret;

	INIT_LIST_HEAD(&ipc->tx_list);
	INIT_LIST_HEAD(&ipc->rx_list);
	INIT_LIST_HEAD(&ipc->empty_list);
	init_रुकोqueue_head(&ipc->रुको_txq);

	ret = msg_empty_list_init(ipc);
	अगर (ret < 0)
		वापस -ENOMEM;

	INIT_WORK(&ipc->kwork, ipc_tx_msgs);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sst_ipc_init);

व्योम sst_ipc_fini(काष्ठा sst_generic_ipc *ipc)
अणु
	पूर्णांक i;

	cancel_work_sync(&ipc->kwork);

	अगर (ipc->msg) अणु
		क्रम (i = 0; i < IPC_EMPTY_LIST_SIZE; i++) अणु
			kमुक्त(ipc->msg[i].tx.data);
			kमुक्त(ipc->msg[i].rx.data);
		पूर्ण
		kमुक्त(ipc->msg);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sst_ipc_fini);

/* Module inक्रमmation */
MODULE_AUTHOR("Jin Yao");
MODULE_DESCRIPTION("Intel SST IPC generic");
MODULE_LICENSE("GPL v2");
