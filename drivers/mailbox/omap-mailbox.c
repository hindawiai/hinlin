<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OMAP mailbox driver
 *
 * Copyright (C) 2006-2009 Nokia Corporation. All rights reserved.
 * Copyright (C) 2013-2021 Texas Instruments Incorporated - https://www.ti.com
 *
 * Contact: Hiroshi DOYU <Hiroshi.DOYU@nokia.com>
 *          Suman Anna <s-anna@ti.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/omap-mailbox.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/mailbox_client.h>

#समावेश "mailbox.h"

#घोषणा MAILBOX_REVISION		0x000
#घोषणा MAILBOX_MESSAGE(m)		(0x040 + 4 * (m))
#घोषणा MAILBOX_FIFOSTATUS(m)		(0x080 + 4 * (m))
#घोषणा MAILBOX_MSGSTATUS(m)		(0x0c0 + 4 * (m))

#घोषणा OMAP2_MAILBOX_IRQSTATUS(u)	(0x100 + 8 * (u))
#घोषणा OMAP2_MAILBOX_IRQENABLE(u)	(0x104 + 8 * (u))

#घोषणा OMAP4_MAILBOX_IRQSTATUS(u)	(0x104 + 0x10 * (u))
#घोषणा OMAP4_MAILBOX_IRQENABLE(u)	(0x108 + 0x10 * (u))
#घोषणा OMAP4_MAILBOX_IRQENABLE_CLR(u)	(0x10c + 0x10 * (u))

#घोषणा MAILBOX_IRQSTATUS(type, u)	(type ? OMAP4_MAILBOX_IRQSTATUS(u) : \
						OMAP2_MAILBOX_IRQSTATUS(u))
#घोषणा MAILBOX_IRQENABLE(type, u)	(type ? OMAP4_MAILBOX_IRQENABLE(u) : \
						OMAP2_MAILBOX_IRQENABLE(u))
#घोषणा MAILBOX_IRQDISABLE(type, u)	(type ? OMAP4_MAILBOX_IRQENABLE_CLR(u) \
						: OMAP2_MAILBOX_IRQENABLE(u))

#घोषणा MAILBOX_IRQ_NEWMSG(m)		(1 << (2 * (m)))
#घोषणा MAILBOX_IRQ_NOTFULL(m)		(1 << (2 * (m) + 1))

/* Interrupt रेजिस्टर configuration types */
#घोषणा MBOX_INTR_CFG_TYPE1		0
#घोषणा MBOX_INTR_CFG_TYPE2		1

काष्ठा omap_mbox_fअगरo अणु
	अचिन्हित दीर्घ msg;
	अचिन्हित दीर्घ fअगरo_stat;
	अचिन्हित दीर्घ msg_stat;
	अचिन्हित दीर्घ irqenable;
	अचिन्हित दीर्घ irqstatus;
	अचिन्हित दीर्घ irqdisable;
	u32 पूर्णांकr_bit;
पूर्ण;

काष्ठा omap_mbox_queue अणु
	spinlock_t		lock;
	काष्ठा kfअगरo		fअगरo;
	काष्ठा work_काष्ठा	work;
	काष्ठा omap_mbox	*mbox;
	bool full;
पूर्ण;

काष्ठा omap_mbox_match_data अणु
	u32 पूर्णांकr_type;
पूर्ण;

काष्ठा omap_mbox_device अणु
	काष्ठा device *dev;
	काष्ठा mutex cfg_lock;
	व्योम __iomem *mbox_base;
	u32 *irq_ctx;
	u32 num_users;
	u32 num_fअगरos;
	u32 पूर्णांकr_type;
	काष्ठा omap_mbox **mboxes;
	काष्ठा mbox_controller controller;
	काष्ठा list_head elem;
पूर्ण;

काष्ठा omap_mbox_fअगरo_info अणु
	पूर्णांक tx_id;
	पूर्णांक tx_usr;
	पूर्णांक tx_irq;

	पूर्णांक rx_id;
	पूर्णांक rx_usr;
	पूर्णांक rx_irq;

	स्थिर अक्षर *name;
	bool send_no_irq;
पूर्ण;

काष्ठा omap_mbox अणु
	स्थिर अक्षर		*name;
	पूर्णांक			irq;
	काष्ठा omap_mbox_queue	*rxq;
	काष्ठा device		*dev;
	काष्ठा omap_mbox_device *parent;
	काष्ठा omap_mbox_fअगरo	tx_fअगरo;
	काष्ठा omap_mbox_fअगरo	rx_fअगरo;
	u32			पूर्णांकr_type;
	काष्ठा mbox_chan	*chan;
	bool			send_no_irq;
पूर्ण;

/* global variables क्रम the mailbox devices */
अटल DEFINE_MUTEX(omap_mbox_devices_lock);
अटल LIST_HEAD(omap_mbox_devices);

अटल अचिन्हित पूर्णांक mbox_kfअगरo_size = CONFIG_OMAP_MBOX_KFIFO_SIZE;
module_param(mbox_kfअगरo_size, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(mbox_kfअगरo_size, "Size of omap's mailbox kfifo (bytes)");

अटल काष्ठा omap_mbox *mbox_chan_to_omap_mbox(काष्ठा mbox_chan *chan)
अणु
	अगर (!chan || !chan->con_priv)
		वापस शून्य;

	वापस (काष्ठा omap_mbox *)chan->con_priv;
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक mbox_पढ़ो_reg(काष्ठा omap_mbox_device *mdev, माप_प्रकार ofs)
अणु
	वापस __raw_पढ़ोl(mdev->mbox_base + ofs);
पूर्ण

अटल अंतरभूत
व्योम mbox_ग_लिखो_reg(काष्ठा omap_mbox_device *mdev, u32 val, माप_प्रकार ofs)
अणु
	__raw_ग_लिखोl(val, mdev->mbox_base + ofs);
पूर्ण

/* Mailbox FIFO handle functions */
अटल u32 mbox_fअगरo_पढ़ो(काष्ठा omap_mbox *mbox)
अणु
	काष्ठा omap_mbox_fअगरo *fअगरo = &mbox->rx_fअगरo;

	वापस mbox_पढ़ो_reg(mbox->parent, fअगरo->msg);
पूर्ण

अटल व्योम mbox_fअगरo_ग_लिखो(काष्ठा omap_mbox *mbox, u32 msg)
अणु
	काष्ठा omap_mbox_fअगरo *fअगरo = &mbox->tx_fअगरo;

	mbox_ग_लिखो_reg(mbox->parent, msg, fअगरo->msg);
पूर्ण

अटल पूर्णांक mbox_fअगरo_empty(काष्ठा omap_mbox *mbox)
अणु
	काष्ठा omap_mbox_fअगरo *fअगरo = &mbox->rx_fअगरo;

	वापस (mbox_पढ़ो_reg(mbox->parent, fअगरo->msg_stat) == 0);
पूर्ण

अटल पूर्णांक mbox_fअगरo_full(काष्ठा omap_mbox *mbox)
अणु
	काष्ठा omap_mbox_fअगरo *fअगरo = &mbox->tx_fअगरo;

	वापस mbox_पढ़ो_reg(mbox->parent, fअगरo->fअगरo_stat);
पूर्ण

/* Mailbox IRQ handle functions */
अटल व्योम ack_mbox_irq(काष्ठा omap_mbox *mbox, omap_mbox_irq_t irq)
अणु
	काष्ठा omap_mbox_fअगरo *fअगरo = (irq == IRQ_TX) ?
				&mbox->tx_fअगरo : &mbox->rx_fअगरo;
	u32 bit = fअगरo->पूर्णांकr_bit;
	u32 irqstatus = fअगरo->irqstatus;

	mbox_ग_लिखो_reg(mbox->parent, bit, irqstatus);

	/* Flush posted ग_लिखो क्रम irq status to aव्योम spurious पूर्णांकerrupts */
	mbox_पढ़ो_reg(mbox->parent, irqstatus);
पूर्ण

अटल पूर्णांक is_mbox_irq(काष्ठा omap_mbox *mbox, omap_mbox_irq_t irq)
अणु
	काष्ठा omap_mbox_fअगरo *fअगरo = (irq == IRQ_TX) ?
				&mbox->tx_fअगरo : &mbox->rx_fअगरo;
	u32 bit = fअगरo->पूर्णांकr_bit;
	u32 irqenable = fअगरo->irqenable;
	u32 irqstatus = fअगरo->irqstatus;

	u32 enable = mbox_पढ़ो_reg(mbox->parent, irqenable);
	u32 status = mbox_पढ़ो_reg(mbox->parent, irqstatus);

	वापस (पूर्णांक)(enable & status & bit);
पूर्ण

अटल व्योम _omap_mbox_enable_irq(काष्ठा omap_mbox *mbox, omap_mbox_irq_t irq)
अणु
	u32 l;
	काष्ठा omap_mbox_fअगरo *fअगरo = (irq == IRQ_TX) ?
				&mbox->tx_fअगरo : &mbox->rx_fअगरo;
	u32 bit = fअगरo->पूर्णांकr_bit;
	u32 irqenable = fअगरo->irqenable;

	l = mbox_पढ़ो_reg(mbox->parent, irqenable);
	l |= bit;
	mbox_ग_लिखो_reg(mbox->parent, l, irqenable);
पूर्ण

अटल व्योम _omap_mbox_disable_irq(काष्ठा omap_mbox *mbox, omap_mbox_irq_t irq)
अणु
	काष्ठा omap_mbox_fअगरo *fअगरo = (irq == IRQ_TX) ?
				&mbox->tx_fअगरo : &mbox->rx_fअगरo;
	u32 bit = fअगरo->पूर्णांकr_bit;
	u32 irqdisable = fअगरo->irqdisable;

	/*
	 * Read and update the पूर्णांकerrupt configuration रेजिस्टर क्रम pre-OMAP4.
	 * OMAP4 and later SoCs have a dedicated पूर्णांकerrupt disabling रेजिस्टर.
	 */
	अगर (!mbox->पूर्णांकr_type)
		bit = mbox_पढ़ो_reg(mbox->parent, irqdisable) & ~bit;

	mbox_ग_लिखो_reg(mbox->parent, bit, irqdisable);
पूर्ण

व्योम omap_mbox_enable_irq(काष्ठा mbox_chan *chan, omap_mbox_irq_t irq)
अणु
	काष्ठा omap_mbox *mbox = mbox_chan_to_omap_mbox(chan);

	अगर (WARN_ON(!mbox))
		वापस;

	_omap_mbox_enable_irq(mbox, irq);
पूर्ण
EXPORT_SYMBOL(omap_mbox_enable_irq);

व्योम omap_mbox_disable_irq(काष्ठा mbox_chan *chan, omap_mbox_irq_t irq)
अणु
	काष्ठा omap_mbox *mbox = mbox_chan_to_omap_mbox(chan);

	अगर (WARN_ON(!mbox))
		वापस;

	_omap_mbox_disable_irq(mbox, irq);
पूर्ण
EXPORT_SYMBOL(omap_mbox_disable_irq);

/*
 * Message receiver(workqueue)
 */
अटल व्योम mbox_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा omap_mbox_queue *mq =
			container_of(work, काष्ठा omap_mbox_queue, work);
	mbox_msg_t data;
	u32 msg;
	पूर्णांक len;

	जबतक (kfअगरo_len(&mq->fअगरo) >= माप(msg)) अणु
		len = kfअगरo_out(&mq->fअगरo, (अचिन्हित अक्षर *)&msg, माप(msg));
		WARN_ON(len != माप(msg));
		data = msg;

		mbox_chan_received_data(mq->mbox->chan, (व्योम *)data);
		spin_lock_irq(&mq->lock);
		अगर (mq->full) अणु
			mq->full = false;
			_omap_mbox_enable_irq(mq->mbox, IRQ_RX);
		पूर्ण
		spin_unlock_irq(&mq->lock);
	पूर्ण
पूर्ण

/*
 * Mailbox पूर्णांकerrupt handler
 */
अटल व्योम __mbox_tx_पूर्णांकerrupt(काष्ठा omap_mbox *mbox)
अणु
	_omap_mbox_disable_irq(mbox, IRQ_TX);
	ack_mbox_irq(mbox, IRQ_TX);
	mbox_chan_txकरोne(mbox->chan, 0);
पूर्ण

अटल व्योम __mbox_rx_पूर्णांकerrupt(काष्ठा omap_mbox *mbox)
अणु
	काष्ठा omap_mbox_queue *mq = mbox->rxq;
	u32 msg;
	पूर्णांक len;

	जबतक (!mbox_fअगरo_empty(mbox)) अणु
		अगर (unlikely(kfअगरo_avail(&mq->fअगरo) < माप(msg))) अणु
			_omap_mbox_disable_irq(mbox, IRQ_RX);
			mq->full = true;
			जाओ nomem;
		पूर्ण

		msg = mbox_fअगरo_पढ़ो(mbox);

		len = kfअगरo_in(&mq->fअगरo, (अचिन्हित अक्षर *)&msg, माप(msg));
		WARN_ON(len != माप(msg));
	पूर्ण

	/* no more messages in the fअगरo. clear IRQ source. */
	ack_mbox_irq(mbox, IRQ_RX);
nomem:
	schedule_work(&mbox->rxq->work);
पूर्ण

अटल irqवापस_t mbox_पूर्णांकerrupt(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा omap_mbox *mbox = p;

	अगर (is_mbox_irq(mbox, IRQ_TX))
		__mbox_tx_पूर्णांकerrupt(mbox);

	अगर (is_mbox_irq(mbox, IRQ_RX))
		__mbox_rx_पूर्णांकerrupt(mbox);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा omap_mbox_queue *mbox_queue_alloc(काष्ठा omap_mbox *mbox,
					व्योम (*work)(काष्ठा work_काष्ठा *))
अणु
	काष्ठा omap_mbox_queue *mq;

	अगर (!work)
		वापस शून्य;

	mq = kzalloc(माप(*mq), GFP_KERNEL);
	अगर (!mq)
		वापस शून्य;

	spin_lock_init(&mq->lock);

	अगर (kfअगरo_alloc(&mq->fअगरo, mbox_kfअगरo_size, GFP_KERNEL))
		जाओ error;

	INIT_WORK(&mq->work, work);
	वापस mq;

error:
	kमुक्त(mq);
	वापस शून्य;
पूर्ण

अटल व्योम mbox_queue_मुक्त(काष्ठा omap_mbox_queue *q)
अणु
	kfअगरo_मुक्त(&q->fअगरo);
	kमुक्त(q);
पूर्ण

अटल पूर्णांक omap_mbox_startup(काष्ठा omap_mbox *mbox)
अणु
	पूर्णांक ret = 0;
	काष्ठा omap_mbox_queue *mq;

	mq = mbox_queue_alloc(mbox, mbox_rx_work);
	अगर (!mq)
		वापस -ENOMEM;
	mbox->rxq = mq;
	mq->mbox = mbox;

	ret = request_irq(mbox->irq, mbox_पूर्णांकerrupt, IRQF_SHARED,
			  mbox->name, mbox);
	अगर (unlikely(ret)) अणु
		pr_err("failed to register mailbox interrupt:%d\n", ret);
		जाओ fail_request_irq;
	पूर्ण

	अगर (mbox->send_no_irq)
		mbox->chan->txकरोne_method = TXDONE_BY_ACK;

	_omap_mbox_enable_irq(mbox, IRQ_RX);

	वापस 0;

fail_request_irq:
	mbox_queue_मुक्त(mbox->rxq);
	वापस ret;
पूर्ण

अटल व्योम omap_mbox_fini(काष्ठा omap_mbox *mbox)
अणु
	_omap_mbox_disable_irq(mbox, IRQ_RX);
	मुक्त_irq(mbox->irq, mbox);
	flush_work(&mbox->rxq->work);
	mbox_queue_मुक्त(mbox->rxq);
पूर्ण

अटल काष्ठा omap_mbox *omap_mbox_device_find(काष्ठा omap_mbox_device *mdev,
					       स्थिर अक्षर *mbox_name)
अणु
	काष्ठा omap_mbox *_mbox, *mbox = शून्य;
	काष्ठा omap_mbox **mboxes = mdev->mboxes;
	पूर्णांक i;

	अगर (!mboxes)
		वापस शून्य;

	क्रम (i = 0; (_mbox = mboxes[i]); i++) अणु
		अगर (!म_भेद(_mbox->name, mbox_name)) अणु
			mbox = _mbox;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस mbox;
पूर्ण

काष्ठा mbox_chan *omap_mbox_request_channel(काष्ठा mbox_client *cl,
					    स्थिर अक्षर *chan_name)
अणु
	काष्ठा device *dev = cl->dev;
	काष्ठा omap_mbox *mbox = शून्य;
	काष्ठा omap_mbox_device *mdev;
	काष्ठा mbox_chan *chan;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	अगर (dev->of_node) अणु
		pr_err("%s: please use mbox_request_channel(), this API is supported only for OMAP non-DT usage\n",
		       __func__);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	mutex_lock(&omap_mbox_devices_lock);
	list_क्रम_each_entry(mdev, &omap_mbox_devices, elem) अणु
		mbox = omap_mbox_device_find(mdev, chan_name);
		अगर (mbox)
			अवरोध;
	पूर्ण
	mutex_unlock(&omap_mbox_devices_lock);

	अगर (!mbox || !mbox->chan)
		वापस ERR_PTR(-ENOENT);

	chan = mbox->chan;
	spin_lock_irqsave(&chan->lock, flags);
	chan->msg_मुक्त = 0;
	chan->msg_count = 0;
	chan->active_req = शून्य;
	chan->cl = cl;
	init_completion(&chan->tx_complete);
	spin_unlock_irqrestore(&chan->lock, flags);

	ret = chan->mbox->ops->startup(chan);
	अगर (ret) अणु
		pr_err("Unable to startup the chan (%d)\n", ret);
		mbox_मुक्त_channel(chan);
		chan = ERR_PTR(ret);
	पूर्ण

	वापस chan;
पूर्ण
EXPORT_SYMBOL(omap_mbox_request_channel);

अटल काष्ठा class omap_mbox_class = अणु .name = "mbox", पूर्ण;

अटल पूर्णांक omap_mbox_रेजिस्टर(काष्ठा omap_mbox_device *mdev)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा omap_mbox **mboxes;

	अगर (!mdev || !mdev->mboxes)
		वापस -EINVAL;

	mboxes = mdev->mboxes;
	क्रम (i = 0; mboxes[i]; i++) अणु
		काष्ठा omap_mbox *mbox = mboxes[i];

		mbox->dev = device_create(&omap_mbox_class, mdev->dev,
					0, mbox, "%s", mbox->name);
		अगर (IS_ERR(mbox->dev)) अणु
			ret = PTR_ERR(mbox->dev);
			जाओ err_out;
		पूर्ण
	पूर्ण

	mutex_lock(&omap_mbox_devices_lock);
	list_add(&mdev->elem, &omap_mbox_devices);
	mutex_unlock(&omap_mbox_devices_lock);

	ret = devm_mbox_controller_रेजिस्टर(mdev->dev, &mdev->controller);

err_out:
	अगर (ret) अणु
		जबतक (i--)
			device_unरेजिस्टर(mboxes[i]->dev);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक omap_mbox_unरेजिस्टर(काष्ठा omap_mbox_device *mdev)
अणु
	पूर्णांक i;
	काष्ठा omap_mbox **mboxes;

	अगर (!mdev || !mdev->mboxes)
		वापस -EINVAL;

	mutex_lock(&omap_mbox_devices_lock);
	list_del(&mdev->elem);
	mutex_unlock(&omap_mbox_devices_lock);

	mboxes = mdev->mboxes;
	क्रम (i = 0; mboxes[i]; i++)
		device_unरेजिस्टर(mboxes[i]->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_mbox_chan_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा omap_mbox *mbox = mbox_chan_to_omap_mbox(chan);
	काष्ठा omap_mbox_device *mdev = mbox->parent;
	पूर्णांक ret = 0;

	mutex_lock(&mdev->cfg_lock);
	pm_runसमय_get_sync(mdev->dev);
	ret = omap_mbox_startup(mbox);
	अगर (ret)
		pm_runसमय_put_sync(mdev->dev);
	mutex_unlock(&mdev->cfg_lock);
	वापस ret;
पूर्ण

अटल व्योम omap_mbox_chan_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा omap_mbox *mbox = mbox_chan_to_omap_mbox(chan);
	काष्ठा omap_mbox_device *mdev = mbox->parent;

	mutex_lock(&mdev->cfg_lock);
	omap_mbox_fini(mbox);
	pm_runसमय_put_sync(mdev->dev);
	mutex_unlock(&mdev->cfg_lock);
पूर्ण

अटल पूर्णांक omap_mbox_chan_send_noirq(काष्ठा omap_mbox *mbox, u32 msg)
अणु
	पूर्णांक ret = -EBUSY;

	अगर (!mbox_fअगरo_full(mbox)) अणु
		_omap_mbox_enable_irq(mbox, IRQ_RX);
		mbox_fअगरo_ग_लिखो(mbox, msg);
		ret = 0;
		_omap_mbox_disable_irq(mbox, IRQ_RX);

		/* we must पढ़ो and ack the पूर्णांकerrupt directly from here */
		mbox_fअगरo_पढ़ो(mbox);
		ack_mbox_irq(mbox, IRQ_RX);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक omap_mbox_chan_send(काष्ठा omap_mbox *mbox, u32 msg)
अणु
	पूर्णांक ret = -EBUSY;

	अगर (!mbox_fअगरo_full(mbox)) अणु
		mbox_fअगरo_ग_लिखो(mbox, msg);
		ret = 0;
	पूर्ण

	/* always enable the पूर्णांकerrupt */
	_omap_mbox_enable_irq(mbox, IRQ_TX);
	वापस ret;
पूर्ण

अटल पूर्णांक omap_mbox_chan_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा omap_mbox *mbox = mbox_chan_to_omap_mbox(chan);
	पूर्णांक ret;
	u32 msg = omap_mbox_message(data);

	अगर (!mbox)
		वापस -EINVAL;

	अगर (mbox->send_no_irq)
		ret = omap_mbox_chan_send_noirq(mbox, msg);
	अन्यथा
		ret = omap_mbox_chan_send(mbox, msg);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops omap_mbox_chan_ops = अणु
	.startup        = omap_mbox_chan_startup,
	.send_data      = omap_mbox_chan_send_data,
	.shutकरोwn       = omap_mbox_chan_shutकरोwn,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक omap_mbox_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_mbox_device *mdev = dev_get_drvdata(dev);
	u32 usr, fअगरo, reg;

	अगर (pm_runसमय_status_suspended(dev))
		वापस 0;

	क्रम (fअगरo = 0; fअगरo < mdev->num_fअगरos; fअगरo++) अणु
		अगर (mbox_पढ़ो_reg(mdev, MAILBOX_MSGSTATUS(fअगरo))) अणु
			dev_err(mdev->dev, "fifo %d has unexpected unread messages\n",
				fअगरo);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	क्रम (usr = 0; usr < mdev->num_users; usr++) अणु
		reg = MAILBOX_IRQENABLE(mdev->पूर्णांकr_type, usr);
		mdev->irq_ctx[usr] = mbox_पढ़ो_reg(mdev, reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_mbox_resume(काष्ठा device *dev)
अणु
	काष्ठा omap_mbox_device *mdev = dev_get_drvdata(dev);
	u32 usr, reg;

	अगर (pm_runसमय_status_suspended(dev))
		वापस 0;

	क्रम (usr = 0; usr < mdev->num_users; usr++) अणु
		reg = MAILBOX_IRQENABLE(mdev->पूर्णांकr_type, usr);
		mbox_ग_लिखो_reg(mdev, mdev->irq_ctx[usr], reg);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops omap_mbox_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(omap_mbox_suspend, omap_mbox_resume)
पूर्ण;

अटल स्थिर काष्ठा omap_mbox_match_data omap2_data = अणु MBOX_INTR_CFG_TYPE1 पूर्ण;
अटल स्थिर काष्ठा omap_mbox_match_data omap4_data = अणु MBOX_INTR_CFG_TYPE2 पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_mailbox_of_match[] = अणु
	अणु
		.compatible	= "ti,omap2-mailbox",
		.data		= &omap2_data,
	पूर्ण,
	अणु
		.compatible	= "ti,omap3-mailbox",
		.data		= &omap2_data,
	पूर्ण,
	अणु
		.compatible	= "ti,omap4-mailbox",
		.data		= &omap4_data,
	पूर्ण,
	अणु
		.compatible	= "ti,am654-mailbox",
		.data		= &omap4_data,
	पूर्ण,
	अणु
		.compatible	= "ti,am64-mailbox",
		.data		= &omap4_data,
	पूर्ण,
	अणु
		/* end */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_mailbox_of_match);

अटल काष्ठा mbox_chan *omap_mbox_of_xlate(काष्ठा mbox_controller *controller,
					    स्थिर काष्ठा of_phandle_args *sp)
अणु
	phandle phandle = sp->args[0];
	काष्ठा device_node *node;
	काष्ठा omap_mbox_device *mdev;
	काष्ठा omap_mbox *mbox;

	mdev = container_of(controller, काष्ठा omap_mbox_device, controller);
	अगर (WARN_ON(!mdev))
		वापस ERR_PTR(-EINVAL);

	node = of_find_node_by_phandle(phandle);
	अगर (!node) अणु
		pr_err("%s: could not find node phandle 0x%x\n",
		       __func__, phandle);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	mbox = omap_mbox_device_find(mdev, node->name);
	of_node_put(node);
	वापस mbox ? mbox->chan : ERR_PTR(-ENOENT);
पूर्ण

अटल पूर्णांक omap_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *mem;
	पूर्णांक ret;
	काष्ठा mbox_chan *chnls;
	काष्ठा omap_mbox **list, *mbox, *mboxblk;
	काष्ठा omap_mbox_fअगरo_info *finfo, *finfoblk;
	काष्ठा omap_mbox_device *mdev;
	काष्ठा omap_mbox_fअगरo *fअगरo;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *child;
	स्थिर काष्ठा omap_mbox_match_data *match_data;
	u32 पूर्णांकr_type, info_count;
	u32 num_users, num_fअगरos;
	u32 पंचांगp[3];
	u32 l;
	पूर्णांक i;

	अगर (!node) अणु
		pr_err("%s: only DT-based devices are supported\n", __func__);
		वापस -ENODEV;
	पूर्ण

	match_data = of_device_get_match_data(&pdev->dev);
	अगर (!match_data)
		वापस -ENODEV;
	पूर्णांकr_type = match_data->पूर्णांकr_type;

	अगर (of_property_पढ़ो_u32(node, "ti,mbox-num-users", &num_users))
		वापस -ENODEV;

	अगर (of_property_पढ़ो_u32(node, "ti,mbox-num-fifos", &num_fअगरos))
		वापस -ENODEV;

	info_count = of_get_available_child_count(node);
	अगर (!info_count) अणु
		dev_err(&pdev->dev, "no available mbox devices found\n");
		वापस -ENODEV;
	पूर्ण

	finfoblk = devm_kसुस्मृति(&pdev->dev, info_count, माप(*finfoblk),
				GFP_KERNEL);
	अगर (!finfoblk)
		वापस -ENOMEM;

	finfo = finfoblk;
	child = शून्य;
	क्रम (i = 0; i < info_count; i++, finfo++) अणु
		child = of_get_next_available_child(node, child);
		ret = of_property_पढ़ो_u32_array(child, "ti,mbox-tx", पंचांगp,
						 ARRAY_SIZE(पंचांगp));
		अगर (ret)
			वापस ret;
		finfo->tx_id = पंचांगp[0];
		finfo->tx_irq = पंचांगp[1];
		finfo->tx_usr = पंचांगp[2];

		ret = of_property_पढ़ो_u32_array(child, "ti,mbox-rx", पंचांगp,
						 ARRAY_SIZE(पंचांगp));
		अगर (ret)
			वापस ret;
		finfo->rx_id = पंचांगp[0];
		finfo->rx_irq = पंचांगp[1];
		finfo->rx_usr = पंचांगp[2];

		finfo->name = child->name;

		अगर (of_find_property(child, "ti,mbox-send-noirq", शून्य))
			finfo->send_no_irq = true;

		अगर (finfo->tx_id >= num_fअगरos || finfo->rx_id >= num_fअगरos ||
		    finfo->tx_usr >= num_users || finfo->rx_usr >= num_users)
			वापस -EINVAL;
	पूर्ण

	mdev = devm_kzalloc(&pdev->dev, माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mdev->mbox_base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(mdev->mbox_base))
		वापस PTR_ERR(mdev->mbox_base);

	mdev->irq_ctx = devm_kसुस्मृति(&pdev->dev, num_users, माप(u32),
				     GFP_KERNEL);
	अगर (!mdev->irq_ctx)
		वापस -ENOMEM;

	/* allocate one extra क्रम marking end of list */
	list = devm_kसुस्मृति(&pdev->dev, info_count + 1, माप(*list),
			    GFP_KERNEL);
	अगर (!list)
		वापस -ENOMEM;

	chnls = devm_kसुस्मृति(&pdev->dev, info_count + 1, माप(*chnls),
			     GFP_KERNEL);
	अगर (!chnls)
		वापस -ENOMEM;

	mboxblk = devm_kसुस्मृति(&pdev->dev, info_count, माप(*mbox),
			       GFP_KERNEL);
	अगर (!mboxblk)
		वापस -ENOMEM;

	mbox = mboxblk;
	finfo = finfoblk;
	क्रम (i = 0; i < info_count; i++, finfo++) अणु
		fअगरo = &mbox->tx_fअगरo;
		fअगरo->msg = MAILBOX_MESSAGE(finfo->tx_id);
		fअगरo->fअगरo_stat = MAILBOX_FIFOSTATUS(finfo->tx_id);
		fअगरo->पूर्णांकr_bit = MAILBOX_IRQ_NOTFULL(finfo->tx_id);
		fअगरo->irqenable = MAILBOX_IRQENABLE(पूर्णांकr_type, finfo->tx_usr);
		fअगरo->irqstatus = MAILBOX_IRQSTATUS(पूर्णांकr_type, finfo->tx_usr);
		fअगरo->irqdisable = MAILBOX_IRQDISABLE(पूर्णांकr_type, finfo->tx_usr);

		fअगरo = &mbox->rx_fअगरo;
		fअगरo->msg = MAILBOX_MESSAGE(finfo->rx_id);
		fअगरo->msg_stat =  MAILBOX_MSGSTATUS(finfo->rx_id);
		fअगरo->पूर्णांकr_bit = MAILBOX_IRQ_NEWMSG(finfo->rx_id);
		fअगरo->irqenable = MAILBOX_IRQENABLE(पूर्णांकr_type, finfo->rx_usr);
		fअगरo->irqstatus = MAILBOX_IRQSTATUS(पूर्णांकr_type, finfo->rx_usr);
		fअगरo->irqdisable = MAILBOX_IRQDISABLE(पूर्णांकr_type, finfo->rx_usr);

		mbox->send_no_irq = finfo->send_no_irq;
		mbox->पूर्णांकr_type = पूर्णांकr_type;

		mbox->parent = mdev;
		mbox->name = finfo->name;
		mbox->irq = platक्रमm_get_irq(pdev, finfo->tx_irq);
		अगर (mbox->irq < 0)
			वापस mbox->irq;
		mbox->chan = &chnls[i];
		chnls[i].con_priv = mbox;
		list[i] = mbox++;
	पूर्ण

	mutex_init(&mdev->cfg_lock);
	mdev->dev = &pdev->dev;
	mdev->num_users = num_users;
	mdev->num_fअगरos = num_fअगरos;
	mdev->पूर्णांकr_type = पूर्णांकr_type;
	mdev->mboxes = list;

	/*
	 * OMAP/K3 Mailbox IP करोes not have a Tx-Done IRQ, but rather a Tx-Ready
	 * IRQ and is needed to run the Tx state machine
	 */
	mdev->controller.txकरोne_irq = true;
	mdev->controller.dev = mdev->dev;
	mdev->controller.ops = &omap_mbox_chan_ops;
	mdev->controller.chans = chnls;
	mdev->controller.num_chans = info_count;
	mdev->controller.of_xlate = omap_mbox_of_xlate;
	ret = omap_mbox_रेजिस्टर(mdev);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, mdev);
	pm_runसमय_enable(mdev->dev);

	ret = pm_runसमय_get_sync(mdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(mdev->dev);
		जाओ unरेजिस्टर;
	पूर्ण

	/*
	 * just prपूर्णांक the raw revision रेजिस्टर, the क्रमmat is not
	 * unअगरorm across all SoCs
	 */
	l = mbox_पढ़ो_reg(mdev, MAILBOX_REVISION);
	dev_info(mdev->dev, "omap mailbox rev 0x%x\n", l);

	ret = pm_runसमय_put_sync(mdev->dev);
	अगर (ret < 0 && ret != -ENOSYS)
		जाओ unरेजिस्टर;

	devm_kमुक्त(&pdev->dev, finfoblk);
	वापस 0;

unरेजिस्टर:
	pm_runसमय_disable(mdev->dev);
	omap_mbox_unरेजिस्टर(mdev);
	वापस ret;
पूर्ण

अटल पूर्णांक omap_mbox_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_mbox_device *mdev = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(mdev->dev);
	omap_mbox_unरेजिस्टर(mdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_mbox_driver = अणु
	.probe	= omap_mbox_probe,
	.हटाओ	= omap_mbox_हटाओ,
	.driver	= अणु
		.name = "omap-mailbox",
		.pm = &omap_mbox_pm_ops,
		.of_match_table = of_match_ptr(omap_mailbox_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init omap_mbox_init(व्योम)
अणु
	पूर्णांक err;

	err = class_रेजिस्टर(&omap_mbox_class);
	अगर (err)
		वापस err;

	/* kfअगरo size sanity check: alignment and minimal size */
	mbox_kfअगरo_size = ALIGN(mbox_kfअगरo_size, माप(u32));
	mbox_kfअगरo_size = max_t(अचिन्हित पूर्णांक, mbox_kfअगरo_size, माप(u32));

	err = platक्रमm_driver_रेजिस्टर(&omap_mbox_driver);
	अगर (err)
		class_unरेजिस्टर(&omap_mbox_class);

	वापस err;
पूर्ण
subsys_initcall(omap_mbox_init);

अटल व्योम __निकास omap_mbox_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_mbox_driver);
	class_unरेजिस्टर(&omap_mbox_class);
पूर्ण
module_निकास(omap_mbox_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("omap mailbox: interrupt driven messaging");
MODULE_AUTHOR("Toshihiro Kobayashi");
MODULE_AUTHOR("Hiroshi DOYU");
