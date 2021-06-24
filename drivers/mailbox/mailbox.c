<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mailbox: Common code क्रम Mailbox controllers and users
 *
 * Copyright (C) 2013-2014 Linaro Ltd.
 * Author: Jassi Brar <jassisinghbrar@gmail.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/mailbox_controller.h>

#समावेश "mailbox.h"

अटल LIST_HEAD(mbox_cons);
अटल DEFINE_MUTEX(con_mutex);

अटल पूर्णांक add_to_rbuf(काष्ठा mbox_chan *chan, व्योम *mssg)
अणु
	पूर्णांक idx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);

	/* See अगर there is any space left */
	अगर (chan->msg_count == MBOX_TX_QUEUE_LEN) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस -ENOBUFS;
	पूर्ण

	idx = chan->msg_मुक्त;
	chan->msg_data[idx] = mssg;
	chan->msg_count++;

	अगर (idx == MBOX_TX_QUEUE_LEN - 1)
		chan->msg_मुक्त = 0;
	अन्यथा
		chan->msg_मुक्त++;

	spin_unlock_irqrestore(&chan->lock, flags);

	वापस idx;
पूर्ण

अटल व्योम msg_submit(काष्ठा mbox_chan *chan)
अणु
	अचिन्हित count, idx;
	अचिन्हित दीर्घ flags;
	व्योम *data;
	पूर्णांक err = -EBUSY;

	spin_lock_irqsave(&chan->lock, flags);

	अगर (!chan->msg_count || chan->active_req)
		जाओ निकास;

	count = chan->msg_count;
	idx = chan->msg_मुक्त;
	अगर (idx >= count)
		idx -= count;
	अन्यथा
		idx += MBOX_TX_QUEUE_LEN - count;

	data = chan->msg_data[idx];

	अगर (chan->cl->tx_prepare)
		chan->cl->tx_prepare(chan->cl, data);
	/* Try to submit a message to the MBOX controller */
	err = chan->mbox->ops->send_data(chan, data);
	अगर (!err) अणु
		chan->active_req = data;
		chan->msg_count--;
	पूर्ण
निकास:
	spin_unlock_irqrestore(&chan->lock, flags);

	/* kick start the समयr immediately to aव्योम delays */
	अगर (!err && (chan->txकरोne_method & TXDONE_BY_POLL)) अणु
		/* but only अगर not alपढ़ोy active */
		अगर (!hrसमयr_active(&chan->mbox->poll_hrt))
			hrसमयr_start(&chan->mbox->poll_hrt, 0, HRTIMER_MODE_REL);
	पूर्ण
पूर्ण

अटल व्योम tx_tick(काष्ठा mbox_chan *chan, पूर्णांक r)
अणु
	अचिन्हित दीर्घ flags;
	व्योम *mssg;

	spin_lock_irqsave(&chan->lock, flags);
	mssg = chan->active_req;
	chan->active_req = शून्य;
	spin_unlock_irqrestore(&chan->lock, flags);

	/* Submit next message */
	msg_submit(chan);

	अगर (!mssg)
		वापस;

	/* Notअगरy the client */
	अगर (chan->cl->tx_करोne)
		chan->cl->tx_करोne(chan->cl, mssg, r);

	अगर (r != -ETIME && chan->cl->tx_block)
		complete(&chan->tx_complete);
पूर्ण

अटल क्रमागत hrसमयr_restart txकरोne_hrसमयr(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा mbox_controller *mbox =
		container_of(hrसमयr, काष्ठा mbox_controller, poll_hrt);
	bool txकरोne, resched = false;
	पूर्णांक i;

	क्रम (i = 0; i < mbox->num_chans; i++) अणु
		काष्ठा mbox_chan *chan = &mbox->chans[i];

		अगर (chan->active_req && chan->cl) अणु
			resched = true;
			txकरोne = chan->mbox->ops->last_tx_करोne(chan);
			अगर (txकरोne)
				tx_tick(chan, 0);
		पूर्ण
	पूर्ण

	अगर (resched) अणु
		hrसमयr_क्रमward_now(hrसमयr, ms_to_kसमय(mbox->txpoll_period));
		वापस HRTIMER_RESTART;
	पूर्ण
	वापस HRTIMER_NORESTART;
पूर्ण

/**
 * mbox_chan_received_data - A way क्रम controller driver to push data
 *				received from remote to the upper layer.
 * @chan: Poपूर्णांकer to the mailbox channel on which RX happened.
 * @mssg: Client specअगरic message typecasted as व्योम *
 *
 * After startup and beक्रमe shutकरोwn any data received on the chan
 * is passed on to the API via atomic mbox_chan_received_data().
 * The controller should ACK the RX only after this call वापसs.
 */
व्योम mbox_chan_received_data(काष्ठा mbox_chan *chan, व्योम *mssg)
अणु
	/* No buffering the received data */
	अगर (chan->cl->rx_callback)
		chan->cl->rx_callback(chan->cl, mssg);
पूर्ण
EXPORT_SYMBOL_GPL(mbox_chan_received_data);

/**
 * mbox_chan_txकरोne - A way क्रम controller driver to notअगरy the
 *			framework that the last TX has completed.
 * @chan: Poपूर्णांकer to the mailbox chan on which TX happened.
 * @r: Status of last TX - OK or ERROR
 *
 * The controller that has IRQ क्रम TX ACK calls this atomic API
 * to tick the TX state machine. It works only अगर txकरोne_irq
 * is set by the controller.
 */
व्योम mbox_chan_txकरोne(काष्ठा mbox_chan *chan, पूर्णांक r)
अणु
	अगर (unlikely(!(chan->txकरोne_method & TXDONE_BY_IRQ))) अणु
		dev_err(chan->mbox->dev,
		       "Controller can't run the TX ticker\n");
		वापस;
	पूर्ण

	tx_tick(chan, r);
पूर्ण
EXPORT_SYMBOL_GPL(mbox_chan_txकरोne);

/**
 * mbox_client_txकरोne - The way क्रम a client to run the TX state machine.
 * @chan: Mailbox channel asचिन्हित to this client.
 * @r: Success status of last transmission.
 *
 * The client/protocol had received some 'ACK' packet and it notअगरies
 * the API that the last packet was sent successfully. This only works
 * अगर the controller can't sense TX-Done.
 */
व्योम mbox_client_txकरोne(काष्ठा mbox_chan *chan, पूर्णांक r)
अणु
	अगर (unlikely(!(chan->txकरोne_method & TXDONE_BY_ACK))) अणु
		dev_err(chan->mbox->dev, "Client can't run the TX ticker\n");
		वापस;
	पूर्ण

	tx_tick(chan, r);
पूर्ण
EXPORT_SYMBOL_GPL(mbox_client_txकरोne);

/**
 * mbox_client_peek_data - A way क्रम client driver to pull data
 *			received from remote by the controller.
 * @chan: Mailbox channel asचिन्हित to this client.
 *
 * A poke to controller driver क्रम any received data.
 * The data is actually passed onto client via the
 * mbox_chan_received_data()
 * The call can be made from atomic context, so the controller's
 * implementation of peek_data() must not sleep.
 *
 * Return: True, अगर controller has, and is going to push after this,
 *          some data.
 *         False, अगर controller करोesn't have any data to be पढ़ो.
 */
bool mbox_client_peek_data(काष्ठा mbox_chan *chan)
अणु
	अगर (chan->mbox->ops->peek_data)
		वापस chan->mbox->ops->peek_data(chan);

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(mbox_client_peek_data);

/**
 * mbox_send_message -	For client to submit a message to be
 *				sent to the remote.
 * @chan: Mailbox channel asचिन्हित to this client.
 * @mssg: Client specअगरic message typecasted.
 *
 * For client to submit data to the controller destined क्रम a remote
 * processor. If the client had set 'tx_block', the call will वापस
 * either when the remote receives the data or when 'tx_tout' millisecs
 * run out.
 *  In non-blocking mode, the requests are buffered by the API and a
 * non-negative token is वापसed क्रम each queued request. If the request
 * is not queued, a negative token is वापसed. Upon failure or successful
 * TX, the API calls 'tx_done' from atomic context, from which the client
 * could submit yet another request.
 * The poपूर्णांकer to message should be preserved until it is sent
 * over the chan, i.e, tx_करोne() is made.
 * This function could be called from atomic context as it simply
 * queues the data and वापसs a token against the request.
 *
 * Return: Non-negative पूर्णांकeger क्रम successful submission (non-blocking mode)
 *	or transmission over chan (blocking mode).
 *	Negative value denotes failure.
 */
पूर्णांक mbox_send_message(काष्ठा mbox_chan *chan, व्योम *mssg)
अणु
	पूर्णांक t;

	अगर (!chan || !chan->cl)
		वापस -EINVAL;

	t = add_to_rbuf(chan, mssg);
	अगर (t < 0) अणु
		dev_err(chan->mbox->dev, "Try increasing MBOX_TX_QUEUE_LEN\n");
		वापस t;
	पूर्ण

	msg_submit(chan);

	अगर (chan->cl->tx_block) अणु
		अचिन्हित दीर्घ रुको;
		पूर्णांक ret;

		अगर (!chan->cl->tx_tout) /* रुको क्रमever */
			रुको = msecs_to_jअगरfies(3600000);
		अन्यथा
			रुको = msecs_to_jअगरfies(chan->cl->tx_tout);

		ret = रुको_क्रम_completion_समयout(&chan->tx_complete, रुको);
		अगर (ret == 0) अणु
			t = -ETIME;
			tx_tick(chan, t);
		पूर्ण
	पूर्ण

	वापस t;
पूर्ण
EXPORT_SYMBOL_GPL(mbox_send_message);

/**
 * mbox_flush - flush a mailbox channel
 * @chan: mailbox channel to flush
 * @समयout: समय, in milliseconds, to allow the flush operation to succeed
 *
 * Mailbox controllers that need to work in atomic context can implement the
 * ->flush() callback to busy loop until a transmission has been completed.
 * The implementation must call mbox_chan_txकरोne() upon success. Clients can
 * call the mbox_flush() function at any समय after mbox_send_message() to
 * flush the transmission. After the function वापसs success, the mailbox
 * transmission is guaranteed to have completed.
 *
 * Returns: 0 on success or a negative error code on failure.
 */
पूर्णांक mbox_flush(काष्ठा mbox_chan *chan, अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret;

	अगर (!chan->mbox->ops->flush)
		वापस -ENOTSUPP;

	ret = chan->mbox->ops->flush(chan, समयout);
	अगर (ret < 0)
		tx_tick(chan, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mbox_flush);

/**
 * mbox_request_channel - Request a mailbox channel.
 * @cl: Identity of the client requesting the channel.
 * @index: Index of mailbox specअगरier in 'mboxes' property.
 *
 * The Client specअगरies its requirements and capabilities जबतक asking क्रम
 * a mailbox channel. It can't be called from atomic context.
 * The channel is exclusively allocated and can't be used by another
 * client beक्रमe the owner calls mbox_मुक्त_channel.
 * After assignment, any packet received on this channel will be
 * handed over to the client via the 'rx_callback'.
 * The framework holds reference to the client, so the mbox_client
 * काष्ठाure shouldn't be modअगरied until the mbox_मुक्त_channel वापसs.
 *
 * Return: Poपूर्णांकer to the channel asचिन्हित to the client अगर successful.
 *		ERR_PTR क्रम request failure.
 */
काष्ठा mbox_chan *mbox_request_channel(काष्ठा mbox_client *cl, पूर्णांक index)
अणु
	काष्ठा device *dev = cl->dev;
	काष्ठा mbox_controller *mbox;
	काष्ठा of_phandle_args spec;
	काष्ठा mbox_chan *chan;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!dev || !dev->of_node) अणु
		pr_debug("%s: No owner device node\n", __func__);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	mutex_lock(&con_mutex);

	अगर (of_parse_phandle_with_args(dev->of_node, "mboxes",
				       "#mbox-cells", index, &spec)) अणु
		dev_dbg(dev, "%s: can't parse \"mboxes\" property\n", __func__);
		mutex_unlock(&con_mutex);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	chan = ERR_PTR(-EPROBE_DEFER);
	list_क्रम_each_entry(mbox, &mbox_cons, node)
		अगर (mbox->dev->of_node == spec.np) अणु
			chan = mbox->of_xlate(mbox, &spec);
			अगर (!IS_ERR(chan))
				अवरोध;
		पूर्ण

	of_node_put(spec.np);

	अगर (IS_ERR(chan)) अणु
		mutex_unlock(&con_mutex);
		वापस chan;
	पूर्ण

	अगर (chan->cl || !try_module_get(mbox->dev->driver->owner)) अणु
		dev_dbg(dev, "%s: mailbox not free\n", __func__);
		mutex_unlock(&con_mutex);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	spin_lock_irqsave(&chan->lock, flags);
	chan->msg_मुक्त = 0;
	chan->msg_count = 0;
	chan->active_req = शून्य;
	chan->cl = cl;
	init_completion(&chan->tx_complete);

	अगर (chan->txकरोne_method	== TXDONE_BY_POLL && cl->knows_txकरोne)
		chan->txकरोne_method = TXDONE_BY_ACK;

	spin_unlock_irqrestore(&chan->lock, flags);

	अगर (chan->mbox->ops->startup) अणु
		ret = chan->mbox->ops->startup(chan);

		अगर (ret) अणु
			dev_err(dev, "Unable to startup the chan (%d)\n", ret);
			mbox_मुक्त_channel(chan);
			chan = ERR_PTR(ret);
		पूर्ण
	पूर्ण

	mutex_unlock(&con_mutex);
	वापस chan;
पूर्ण
EXPORT_SYMBOL_GPL(mbox_request_channel);

काष्ठा mbox_chan *mbox_request_channel_byname(काष्ठा mbox_client *cl,
					      स्थिर अक्षर *name)
अणु
	काष्ठा device_node *np = cl->dev->of_node;
	काष्ठा property *prop;
	स्थिर अक्षर *mbox_name;
	पूर्णांक index = 0;

	अगर (!np) अणु
		dev_err(cl->dev, "%s() currently only supports DT\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!of_get_property(np, "mbox-names", शून्य)) अणु
		dev_err(cl->dev,
			"%s() requires an \"mbox-names\" property\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	of_property_क्रम_each_string(np, "mbox-names", prop, mbox_name) अणु
		अगर (!म_भेदन(name, mbox_name, म_माप(name)))
			वापस mbox_request_channel(cl, index);
		index++;
	पूर्ण

	dev_err(cl->dev, "%s() could not locate channel named \"%s\"\n",
		__func__, name);
	वापस ERR_PTR(-EINVAL);
पूर्ण
EXPORT_SYMBOL_GPL(mbox_request_channel_byname);

/**
 * mbox_मुक्त_channel - The client relinquishes control of a mailbox
 *			channel by this call.
 * @chan: The mailbox channel to be मुक्तd.
 */
व्योम mbox_मुक्त_channel(काष्ठा mbox_chan *chan)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!chan || !chan->cl)
		वापस;

	अगर (chan->mbox->ops->shutकरोwn)
		chan->mbox->ops->shutकरोwn(chan);

	/* The queued TX requests are simply पातed, no callbacks are made */
	spin_lock_irqsave(&chan->lock, flags);
	chan->cl = शून्य;
	chan->active_req = शून्य;
	अगर (chan->txकरोne_method == TXDONE_BY_ACK)
		chan->txकरोne_method = TXDONE_BY_POLL;

	module_put(chan->mbox->dev->driver->owner);
	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mbox_मुक्त_channel);

अटल काष्ठा mbox_chan *
of_mbox_index_xlate(काष्ठा mbox_controller *mbox,
		    स्थिर काष्ठा of_phandle_args *sp)
अणु
	पूर्णांक ind = sp->args[0];

	अगर (ind >= mbox->num_chans)
		वापस ERR_PTR(-EINVAL);

	वापस &mbox->chans[ind];
पूर्ण

/**
 * mbox_controller_रेजिस्टर - Register the mailbox controller
 * @mbox:	Poपूर्णांकer to the mailbox controller.
 *
 * The controller driver रेजिस्टरs its communication channels
 */
पूर्णांक mbox_controller_रेजिस्टर(काष्ठा mbox_controller *mbox)
अणु
	पूर्णांक i, txकरोne;

	/* Sanity check */
	अगर (!mbox || !mbox->dev || !mbox->ops || !mbox->num_chans)
		वापस -EINVAL;

	अगर (mbox->txकरोne_irq)
		txकरोne = TXDONE_BY_IRQ;
	अन्यथा अगर (mbox->txकरोne_poll)
		txकरोne = TXDONE_BY_POLL;
	अन्यथा /* It has to be ACK then */
		txकरोne = TXDONE_BY_ACK;

	अगर (txकरोne == TXDONE_BY_POLL) अणु

		अगर (!mbox->ops->last_tx_करोne) अणु
			dev_err(mbox->dev, "last_tx_done method is absent\n");
			वापस -EINVAL;
		पूर्ण

		hrसमयr_init(&mbox->poll_hrt, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL);
		mbox->poll_hrt.function = txकरोne_hrसमयr;
	पूर्ण

	क्रम (i = 0; i < mbox->num_chans; i++) अणु
		काष्ठा mbox_chan *chan = &mbox->chans[i];

		chan->cl = शून्य;
		chan->mbox = mbox;
		chan->txकरोne_method = txकरोne;
		spin_lock_init(&chan->lock);
	पूर्ण

	अगर (!mbox->of_xlate)
		mbox->of_xlate = of_mbox_index_xlate;

	mutex_lock(&con_mutex);
	list_add_tail(&mbox->node, &mbox_cons);
	mutex_unlock(&con_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mbox_controller_रेजिस्टर);

/**
 * mbox_controller_unरेजिस्टर - Unरेजिस्टर the mailbox controller
 * @mbox:	Poपूर्णांकer to the mailbox controller.
 */
व्योम mbox_controller_unरेजिस्टर(काष्ठा mbox_controller *mbox)
अणु
	पूर्णांक i;

	अगर (!mbox)
		वापस;

	mutex_lock(&con_mutex);

	list_del(&mbox->node);

	क्रम (i = 0; i < mbox->num_chans; i++)
		mbox_मुक्त_channel(&mbox->chans[i]);

	अगर (mbox->txकरोne_poll)
		hrसमयr_cancel(&mbox->poll_hrt);

	mutex_unlock(&con_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mbox_controller_unरेजिस्टर);

अटल व्योम __devm_mbox_controller_unरेजिस्टर(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा mbox_controller **mbox = res;

	mbox_controller_unरेजिस्टर(*mbox);
पूर्ण

अटल पूर्णांक devm_mbox_controller_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा mbox_controller **mbox = res;

	अगर (WARN_ON(!mbox || !*mbox))
		वापस 0;

	वापस *mbox == data;
पूर्ण

/**
 * devm_mbox_controller_रेजिस्टर() - managed mbox_controller_रेजिस्टर()
 * @dev: device owning the mailbox controller being रेजिस्टरed
 * @mbox: mailbox controller being रेजिस्टरed
 *
 * This function adds a device-managed resource that will make sure that the
 * mailbox controller, which is रेजिस्टरed using mbox_controller_रेजिस्टर()
 * as part of this function, will be unरेजिस्टरed aदीर्घ with the rest of
 * device-managed resources upon driver probe failure or driver removal.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक devm_mbox_controller_रेजिस्टर(काष्ठा device *dev,
				  काष्ठा mbox_controller *mbox)
अणु
	काष्ठा mbox_controller **ptr;
	पूर्णांक err;

	ptr = devres_alloc(__devm_mbox_controller_unरेजिस्टर, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	err = mbox_controller_रेजिस्टर(mbox);
	अगर (err < 0) अणु
		devres_मुक्त(ptr);
		वापस err;
	पूर्ण

	devres_add(dev, ptr);
	*ptr = mbox;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_mbox_controller_रेजिस्टर);

/**
 * devm_mbox_controller_unरेजिस्टर() - managed mbox_controller_unरेजिस्टर()
 * @dev: device owning the mailbox controller being unरेजिस्टरed
 * @mbox: mailbox controller being unरेजिस्टरed
 *
 * This function unरेजिस्टरs the mailbox controller and हटाओs the device-
 * managed resource that was set up to स्वतःmatically unरेजिस्टर the mailbox
 * controller on driver probe failure or driver removal. It's typically not
 * necessary to call this function.
 */
व्योम devm_mbox_controller_unरेजिस्टर(काष्ठा device *dev, काष्ठा mbox_controller *mbox)
अणु
	WARN_ON(devres_release(dev, __devm_mbox_controller_unरेजिस्टर,
			       devm_mbox_controller_match, mbox));
पूर्ण
EXPORT_SYMBOL_GPL(devm_mbox_controller_unरेजिस्टर);
