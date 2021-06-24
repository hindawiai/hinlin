<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STi Mailbox
 *
 * Copyright (C) 2015 ST Microelectronics
 *
 * Author: Lee Jones <lee.jones@linaro.org> क्रम ST Microelectronics
 *
 * Based on the original driver written by;
 *   Alexandre Torgue, Olivier Lebreton and Loic Pallardy
 */

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "mailbox.h"

#घोषणा STI_MBOX_INST_MAX	4      /* RAM saving: Max supported instances */
#घोषणा STI_MBOX_CHAN_MAX	20     /* RAM saving: Max supported channels  */

#घोषणा STI_IRQ_VAL_OFFSET	0x04   /* Read पूर्णांकerrupt status	              */
#घोषणा STI_IRQ_SET_OFFSET	0x24   /* Generate a Tx channel पूर्णांकerrupt     */
#घोषणा STI_IRQ_CLR_OFFSET	0x44   /* Clear pending Rx पूर्णांकerrupts	      */
#घोषणा STI_ENA_VAL_OFFSET	0x64   /* Read enable status		      */
#घोषणा STI_ENA_SET_OFFSET	0x84   /* Enable a channel		      */
#घोषणा STI_ENA_CLR_OFFSET	0xa4   /* Disable a channel		      */

#घोषणा MBOX_BASE(mdev, inst)   ((mdev)->base + ((inst) * 4))

/**
 * STi Mailbox device data
 *
 * An IP Mailbox is currently composed of 4 instances
 * Each instance is currently composed of 32 channels
 * This means that we have 128 channels per Mailbox
 * A channel an be used क्रम TX or RX
 *
 * @dev:	Device to which it is attached
 * @mbox:	Representation of a communication channel controller
 * @base:	Base address of the रेजिस्टर mapping region
 * @name:	Name of the mailbox
 * @enabled:	Local copy of enabled channels
 * @lock:	Mutex protecting enabled status
 */
काष्ठा sti_mbox_device अणु
	काष्ठा device		*dev;
	काष्ठा mbox_controller	*mbox;
	व्योम __iomem		*base;
	स्थिर अक्षर		*name;
	u32			enabled[STI_MBOX_INST_MAX];
	spinlock_t		lock;
पूर्ण;

/**
 * STi Mailbox platक्रमm specअगरic configuration
 *
 * @num_inst:	Maximum number of instances in one HW Mailbox
 * @num_chan:	Maximum number of channel per instance
 */
काष्ठा sti_mbox_pdata अणु
	अचिन्हित पूर्णांक		num_inst;
	अचिन्हित पूर्णांक		num_chan;
पूर्ण;

/**
 * STi Mailbox allocated channel inक्रमmation
 *
 * @mdev:	Poपूर्णांकer to parent Mailbox device
 * @instance:	Instance number channel resides in
 * @channel:	Channel number pertaining to this container
 */
काष्ठा sti_channel अणु
	काष्ठा sti_mbox_device	*mdev;
	अचिन्हित पूर्णांक		instance;
	अचिन्हित पूर्णांक		channel;
पूर्ण;

अटल अंतरभूत bool sti_mbox_channel_is_enabled(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sti_channel *chan_info = chan->con_priv;
	काष्ठा sti_mbox_device *mdev = chan_info->mdev;
	अचिन्हित पूर्णांक instance = chan_info->instance;
	अचिन्हित पूर्णांक channel = chan_info->channel;

	वापस mdev->enabled[instance] & BIT(channel);
पूर्ण

अटल अंतरभूत
काष्ठा mbox_chan *sti_mbox_to_channel(काष्ठा mbox_controller *mbox,
				      अचिन्हित पूर्णांक instance,
				      अचिन्हित पूर्णांक channel)
अणु
	काष्ठा sti_channel *chan_info;
	पूर्णांक i;

	क्रम (i = 0; i < mbox->num_chans; i++) अणु
		chan_info = mbox->chans[i].con_priv;
		अगर (chan_info &&
		    chan_info->instance == instance &&
		    chan_info->channel == channel)
			वापस &mbox->chans[i];
	पूर्ण

	dev_err(mbox->dev,
		"Channel not registered: instance: %d channel: %d\n",
		instance, channel);

	वापस शून्य;
पूर्ण

अटल व्योम sti_mbox_enable_channel(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sti_channel *chan_info = chan->con_priv;
	काष्ठा sti_mbox_device *mdev = chan_info->mdev;
	अचिन्हित पूर्णांक instance = chan_info->instance;
	अचिन्हित पूर्णांक channel = chan_info->channel;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base = MBOX_BASE(mdev, instance);

	spin_lock_irqsave(&mdev->lock, flags);
	mdev->enabled[instance] |= BIT(channel);
	ग_लिखोl_relaxed(BIT(channel), base + STI_ENA_SET_OFFSET);
	spin_unlock_irqrestore(&mdev->lock, flags);
पूर्ण

अटल व्योम sti_mbox_disable_channel(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sti_channel *chan_info = chan->con_priv;
	काष्ठा sti_mbox_device *mdev = chan_info->mdev;
	अचिन्हित पूर्णांक instance = chan_info->instance;
	अचिन्हित पूर्णांक channel = chan_info->channel;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *base = MBOX_BASE(mdev, instance);

	spin_lock_irqsave(&mdev->lock, flags);
	mdev->enabled[instance] &= ~BIT(channel);
	ग_लिखोl_relaxed(BIT(channel), base + STI_ENA_CLR_OFFSET);
	spin_unlock_irqrestore(&mdev->lock, flags);
पूर्ण

अटल व्योम sti_mbox_clear_irq(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sti_channel *chan_info = chan->con_priv;
	काष्ठा sti_mbox_device *mdev = chan_info->mdev;
	अचिन्हित पूर्णांक instance = chan_info->instance;
	अचिन्हित पूर्णांक channel = chan_info->channel;
	व्योम __iomem *base = MBOX_BASE(mdev, instance);

	ग_लिखोl_relaxed(BIT(channel), base + STI_IRQ_CLR_OFFSET);
पूर्ण

अटल काष्ठा mbox_chan *sti_mbox_irq_to_channel(काष्ठा sti_mbox_device *mdev,
						 अचिन्हित पूर्णांक instance)
अणु
	काष्ठा mbox_controller *mbox = mdev->mbox;
	काष्ठा mbox_chan *chan = शून्य;
	अचिन्हित पूर्णांक channel;
	अचिन्हित दीर्घ bits;
	व्योम __iomem *base = MBOX_BASE(mdev, instance);

	bits = पढ़ोl_relaxed(base + STI_IRQ_VAL_OFFSET);
	अगर (!bits)
		/* No IRQs fired in specअगरied instance */
		वापस शून्य;

	/* An IRQ has fired, find the associated channel */
	क्रम (channel = 0; bits; channel++) अणु
		अगर (!test_and_clear_bit(channel, &bits))
			जारी;

		chan = sti_mbox_to_channel(mbox, instance, channel);
		अगर (chan) अणु
			dev_dbg(mbox->dev,
				"IRQ fired on instance: %d channel: %d\n",
				instance, channel);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस chan;
पूर्ण

अटल irqवापस_t sti_mbox_thपढ़ो_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sti_mbox_device *mdev = data;
	काष्ठा sti_mbox_pdata *pdata = dev_get_platdata(mdev->dev);
	काष्ठा mbox_chan *chan;
	अचिन्हित पूर्णांक instance;

	क्रम (instance = 0; instance < pdata->num_inst; instance++) अणु
keep_looking:
		chan = sti_mbox_irq_to_channel(mdev, instance);
		अगर (!chan)
			जारी;

		mbox_chan_received_data(chan, शून्य);
		sti_mbox_clear_irq(chan);
		sti_mbox_enable_channel(chan);
		जाओ keep_looking;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sti_mbox_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sti_mbox_device *mdev = data;
	काष्ठा sti_mbox_pdata *pdata = dev_get_platdata(mdev->dev);
	काष्ठा sti_channel *chan_info;
	काष्ठा mbox_chan *chan;
	अचिन्हित पूर्णांक instance;
	पूर्णांक ret = IRQ_NONE;

	क्रम (instance = 0; instance < pdata->num_inst; instance++) अणु
		chan = sti_mbox_irq_to_channel(mdev, instance);
		अगर (!chan)
			जारी;
		chan_info = chan->con_priv;

		अगर (!sti_mbox_channel_is_enabled(chan)) अणु
			dev_warn(mdev->dev,
				 "Unexpected IRQ: %s\n"
				 "  instance: %d: channel: %d [enabled: %x]\n",
				 mdev->name, chan_info->instance,
				 chan_info->channel, mdev->enabled[instance]);

			/* Only handle IRQ अगर no other valid IRQs were found */
			अगर (ret == IRQ_NONE)
				ret = IRQ_HANDLED;
			जारी;
		पूर्ण

		sti_mbox_disable_channel(chan);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	अगर (ret == IRQ_NONE)
		dev_err(mdev->dev, "Spurious IRQ - was a channel requested?\n");

	वापस ret;
पूर्ण

अटल bool sti_mbox_tx_is_पढ़ोy(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sti_channel *chan_info = chan->con_priv;
	काष्ठा sti_mbox_device *mdev = chan_info->mdev;
	अचिन्हित पूर्णांक instance = chan_info->instance;
	अचिन्हित पूर्णांक channel = chan_info->channel;
	व्योम __iomem *base = MBOX_BASE(mdev, instance);

	अगर (!(पढ़ोl_relaxed(base + STI_ENA_VAL_OFFSET) & BIT(channel))) अणु
		dev_dbg(mdev->dev, "Mbox: %s: inst: %d, chan: %d disabled\n",
			mdev->name, instance, channel);
		वापस false;
	पूर्ण

	अगर (पढ़ोl_relaxed(base + STI_IRQ_VAL_OFFSET) & BIT(channel)) अणु
		dev_dbg(mdev->dev, "Mbox: %s: inst: %d, chan: %d not ready\n",
			mdev->name, instance, channel);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक sti_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा sti_channel *chan_info = chan->con_priv;
	काष्ठा sti_mbox_device *mdev = chan_info->mdev;
	अचिन्हित पूर्णांक instance = chan_info->instance;
	अचिन्हित पूर्णांक channel = chan_info->channel;
	व्योम __iomem *base = MBOX_BASE(mdev, instance);

	/* Send event to co-processor */
	ग_लिखोl_relaxed(BIT(channel), base + STI_IRQ_SET_OFFSET);

	dev_dbg(mdev->dev,
		"Sent via Mailbox %s: instance: %d channel: %d\n",
		mdev->name, instance, channel);

	वापस 0;
पूर्ण

अटल पूर्णांक sti_mbox_startup_chan(काष्ठा mbox_chan *chan)
अणु
	sti_mbox_clear_irq(chan);
	sti_mbox_enable_channel(chan);

	वापस 0;
पूर्ण

अटल व्योम sti_mbox_shutकरोwn_chan(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sti_channel *chan_info = chan->con_priv;
	काष्ठा mbox_controller *mbox = chan_info->mdev->mbox;
	पूर्णांक i;

	क्रम (i = 0; i < mbox->num_chans; i++)
		अगर (chan == &mbox->chans[i])
			अवरोध;

	अगर (mbox->num_chans == i) अणु
		dev_warn(mbox->dev, "Request to free non-existent channel\n");
		वापस;
	पूर्ण

	/* Reset channel */
	sti_mbox_disable_channel(chan);
	sti_mbox_clear_irq(chan);
	chan->con_priv = शून्य;
पूर्ण

अटल काष्ठा mbox_chan *sti_mbox_xlate(काष्ठा mbox_controller *mbox,
					स्थिर काष्ठा of_phandle_args *spec)
अणु
	काष्ठा sti_mbox_device *mdev = dev_get_drvdata(mbox->dev);
	काष्ठा sti_mbox_pdata *pdata = dev_get_platdata(mdev->dev);
	काष्ठा sti_channel *chan_info;
	काष्ठा mbox_chan *chan = शून्य;
	अचिन्हित पूर्णांक instance  = spec->args[0];
	अचिन्हित पूर्णांक channel   = spec->args[1];
	पूर्णांक i;

	/* Bounds checking */
	अगर (instance >= pdata->num_inst || channel  >= pdata->num_chan) अणु
		dev_err(mbox->dev,
			"Invalid channel requested instance: %d channel: %d\n",
			instance, channel);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	क्रम (i = 0; i < mbox->num_chans; i++) अणु
		chan_info = mbox->chans[i].con_priv;

		/* Is requested channel मुक्त? */
		अगर (chan_info &&
		    mbox->dev == chan_info->mdev->dev &&
		    instance == chan_info->instance &&
		    channel == chan_info->channel) अणु

			dev_err(mbox->dev, "Channel in use\n");
			वापस ERR_PTR(-EBUSY);
		पूर्ण

		/*
		 * Find the first मुक्त slot, then जारी checking
		 * to see अगर requested channel is in use
		 */
		अगर (!chan && !chan_info)
			chan = &mbox->chans[i];
	पूर्ण

	अगर (!chan) अणु
		dev_err(mbox->dev, "No free channels left\n");
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	chan_info = devm_kzalloc(mbox->dev, माप(*chan_info), GFP_KERNEL);
	अगर (!chan_info)
		वापस ERR_PTR(-ENOMEM);

	chan_info->mdev		= mdev;
	chan_info->instance	= instance;
	chan_info->channel	= channel;

	chan->con_priv = chan_info;

	dev_info(mbox->dev,
		 "Mbox: %s: Created channel: instance: %d channel: %d\n",
		 mdev->name, instance, channel);

	वापस chan;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops sti_mbox_ops = अणु
	.startup	= sti_mbox_startup_chan,
	.shutकरोwn	= sti_mbox_shutकरोwn_chan,
	.send_data	= sti_mbox_send_data,
	.last_tx_करोne	= sti_mbox_tx_is_पढ़ोy,
पूर्ण;

अटल स्थिर काष्ठा sti_mbox_pdata mbox_stih407_pdata = अणु
	.num_inst	= 4,
	.num_chan	= 32,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sti_mailbox_match[] = अणु
	अणु
		.compatible = "st,stih407-mailbox",
		.data = (व्योम *)&mbox_stih407_pdata
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sti_mailbox_match);

अटल पूर्णांक sti_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा mbox_controller *mbox;
	काष्ठा sti_mbox_device *mdev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mbox_chan *chans;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक ret;

	match = of_match_device(sti_mailbox_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "No configuration found\n");
		वापस -ENODEV;
	पूर्ण
	pdev->dev.platक्रमm_data = (काष्ठा sti_mbox_pdata *) match->data;

	mdev = devm_kzalloc(&pdev->dev, माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, mdev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mdev->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mdev->base))
		वापस PTR_ERR(mdev->base);

	ret = of_property_पढ़ो_string(np, "mbox-name", &mdev->name);
	अगर (ret)
		mdev->name = np->full_name;

	mbox = devm_kzalloc(&pdev->dev, माप(*mbox), GFP_KERNEL);
	अगर (!mbox)
		वापस -ENOMEM;

	chans = devm_kसुस्मृति(&pdev->dev,
			     STI_MBOX_CHAN_MAX, माप(*chans), GFP_KERNEL);
	अगर (!chans)
		वापस -ENOMEM;

	mdev->dev		= &pdev->dev;
	mdev->mbox		= mbox;

	spin_lock_init(&mdev->lock);

	/* STi Mailbox करोes not have a Tx-Done or Tx-Ready IRQ */
	mbox->txकरोne_irq	= false;
	mbox->txकरोne_poll	= true;
	mbox->txpoll_period	= 100;
	mbox->ops		= &sti_mbox_ops;
	mbox->dev		= mdev->dev;
	mbox->of_xlate		= sti_mbox_xlate;
	mbox->chans		= chans;
	mbox->num_chans		= STI_MBOX_CHAN_MAX;

	ret = devm_mbox_controller_रेजिस्टर(&pdev->dev, mbox);
	अगर (ret)
		वापस ret;

	/* It's okay क्रम Tx Mailboxes to not supply IRQs */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_info(&pdev->dev,
			 "%s: Registered Tx only Mailbox\n", mdev->name);
		वापस 0;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq,
					sti_mbox_irq_handler,
					sti_mbox_thपढ़ो_handler,
					IRQF_ONESHOT, mdev->name, mdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't claim IRQ %d\n", irq);
		वापस -EINVAL;
	पूर्ण

	dev_info(&pdev->dev, "%s: Registered Tx/Rx Mailbox\n", mdev->name);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sti_mbox_driver = अणु
	.probe = sti_mbox_probe,
	.driver = अणु
		.name = "sti-mailbox",
		.of_match_table = sti_mailbox_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sti_mbox_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("STMicroelectronics Mailbox Controller");
MODULE_AUTHOR("Lee Jones <lee.jones@linaro.org");
MODULE_ALIAS("platform:mailbox-sti");
