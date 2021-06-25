<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hisilicon's Hi6220 mailbox driver
 *
 * Copyright (c) 2015 Hisilicon Limited.
 * Copyright (c) 2015 Linaro Limited.
 *
 * Author: Leo Yan <leo.yan@linaro.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा MBOX_CHAN_MAX			32

#घोषणा MBOX_TX				0x1

/* Mailbox message length: 8 words */
#घोषणा MBOX_MSG_LEN			8

/* Mailbox Registers */
#घोषणा MBOX_OFF(m)			(0x40 * (m))
#घोषणा MBOX_MODE_REG(m)		(MBOX_OFF(m) + 0x0)
#घोषणा MBOX_DATA_REG(m)		(MBOX_OFF(m) + 0x4)

#घोषणा MBOX_STATE_MASK			(0xF << 4)
#घोषणा MBOX_STATE_IDLE			(0x1 << 4)
#घोषणा MBOX_STATE_TX			(0x2 << 4)
#घोषणा MBOX_STATE_RX			(0x4 << 4)
#घोषणा MBOX_STATE_ACK			(0x8 << 4)
#घोषणा MBOX_ACK_CONFIG_MASK		(0x1 << 0)
#घोषणा MBOX_ACK_AUTOMATIC		(0x1 << 0)
#घोषणा MBOX_ACK_IRQ			(0x0 << 0)

/* IPC रेजिस्टरs */
#घोषणा ACK_INT_RAW_REG(i)		((i) + 0x400)
#घोषणा ACK_INT_MSK_REG(i)		((i) + 0x404)
#घोषणा ACK_INT_STAT_REG(i)		((i) + 0x408)
#घोषणा ACK_INT_CLR_REG(i)		((i) + 0x40c)
#घोषणा ACK_INT_ENA_REG(i)		((i) + 0x500)
#घोषणा ACK_INT_DIS_REG(i)		((i) + 0x504)
#घोषणा DST_INT_RAW_REG(i)		((i) + 0x420)


काष्ठा hi6220_mbox_chan अणु

	/*
	 * Description क्रम channel's hardware info:
	 *  - direction: tx or rx
	 *  - dst irq: peer core's irq number
	 *  - ack irq: local irq number
	 *  - slot number
	 */
	अचिन्हित पूर्णांक dir, dst_irq, ack_irq;
	अचिन्हित पूर्णांक slot;

	काष्ठा hi6220_mbox *parent;
पूर्ण;

काष्ठा hi6220_mbox अणु
	काष्ठा device *dev;

	पूर्णांक irq;

	/* flag of enabling tx's irq mode */
	bool tx_irq_mode;

	/* region क्रम ipc event */
	व्योम __iomem *ipc;

	/* region क्रम mailbox */
	व्योम __iomem *base;

	अचिन्हित पूर्णांक chan_num;
	काष्ठा hi6220_mbox_chan *mchan;

	व्योम *irq_map_chan[MBOX_CHAN_MAX];
	काष्ठा mbox_chan *chan;
	काष्ठा mbox_controller controller;
पूर्ण;

अटल व्योम mbox_set_state(काष्ठा hi6220_mbox *mbox,
			   अचिन्हित पूर्णांक slot, u32 val)
अणु
	u32 status;

	status = पढ़ोl(mbox->base + MBOX_MODE_REG(slot));
	status = (status & ~MBOX_STATE_MASK) | val;
	ग_लिखोl(status, mbox->base + MBOX_MODE_REG(slot));
पूर्ण

अटल व्योम mbox_set_mode(काष्ठा hi6220_mbox *mbox,
			  अचिन्हित पूर्णांक slot, u32 val)
अणु
	u32 mode;

	mode = पढ़ोl(mbox->base + MBOX_MODE_REG(slot));
	mode = (mode & ~MBOX_ACK_CONFIG_MASK) | val;
	ग_लिखोl(mode, mbox->base + MBOX_MODE_REG(slot));
पूर्ण

अटल bool hi6220_mbox_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा hi6220_mbox_chan *mchan = chan->con_priv;
	काष्ठा hi6220_mbox *mbox = mchan->parent;
	u32 state;

	/* Only set idle state क्रम polling mode */
	BUG_ON(mbox->tx_irq_mode);

	state = पढ़ोl(mbox->base + MBOX_MODE_REG(mchan->slot));
	वापस ((state & MBOX_STATE_MASK) == MBOX_STATE_IDLE);
पूर्ण

अटल पूर्णांक hi6220_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *msg)
अणु
	काष्ठा hi6220_mbox_chan *mchan = chan->con_priv;
	काष्ठा hi6220_mbox *mbox = mchan->parent;
	अचिन्हित पूर्णांक slot = mchan->slot;
	u32 *buf = msg;
	पूर्णांक i;

	/* indicate as a TX channel */
	mchan->dir = MBOX_TX;

	mbox_set_state(mbox, slot, MBOX_STATE_TX);

	अगर (mbox->tx_irq_mode)
		mbox_set_mode(mbox, slot, MBOX_ACK_IRQ);
	अन्यथा
		mbox_set_mode(mbox, slot, MBOX_ACK_AUTOMATIC);

	क्रम (i = 0; i < MBOX_MSG_LEN; i++)
		ग_लिखोl(buf[i], mbox->base + MBOX_DATA_REG(slot) + i * 4);

	/* trigger remote request */
	ग_लिखोl(BIT(mchan->dst_irq), DST_INT_RAW_REG(mbox->ipc));
	वापस 0;
पूर्ण

अटल irqवापस_t hi6220_mbox_पूर्णांकerrupt(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा hi6220_mbox *mbox = p;
	काष्ठा hi6220_mbox_chan *mchan;
	काष्ठा mbox_chan *chan;
	अचिन्हित पूर्णांक state, पूर्णांकr_bit, i;
	u32 msg[MBOX_MSG_LEN];

	state = पढ़ोl(ACK_INT_STAT_REG(mbox->ipc));
	अगर (!state) अणु
		dev_warn(mbox->dev, "%s: spurious interrupt\n",
			 __func__);
		वापस IRQ_HANDLED;
	पूर्ण

	जबतक (state) अणु
		पूर्णांकr_bit = __ffs(state);
		state &= (state - 1);

		chan = mbox->irq_map_chan[पूर्णांकr_bit];
		अगर (!chan) अणु
			dev_warn(mbox->dev, "%s: unexpected irq vector %d\n",
				 __func__, पूर्णांकr_bit);
			जारी;
		पूर्ण

		mchan = chan->con_priv;
		अगर (mchan->dir == MBOX_TX)
			mbox_chan_txकरोne(chan, 0);
		अन्यथा अणु
			क्रम (i = 0; i < MBOX_MSG_LEN; i++)
				msg[i] = पढ़ोl(mbox->base +
					MBOX_DATA_REG(mchan->slot) + i * 4);

			mbox_chan_received_data(chan, (व्योम *)msg);
		पूर्ण

		/* clear IRQ source */
		ग_लिखोl(BIT(mchan->ack_irq), ACK_INT_CLR_REG(mbox->ipc));
		mbox_set_state(mbox, mchan->slot, MBOX_STATE_IDLE);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hi6220_mbox_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा hi6220_mbox_chan *mchan = chan->con_priv;
	काष्ठा hi6220_mbox *mbox = mchan->parent;

	mchan->dir = 0;

	/* enable पूर्णांकerrupt */
	ग_लिखोl(BIT(mchan->ack_irq), ACK_INT_ENA_REG(mbox->ipc));
	वापस 0;
पूर्ण

अटल व्योम hi6220_mbox_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा hi6220_mbox_chan *mchan = chan->con_priv;
	काष्ठा hi6220_mbox *mbox = mchan->parent;

	/* disable पूर्णांकerrupt */
	ग_लिखोl(BIT(mchan->ack_irq), ACK_INT_DIS_REG(mbox->ipc));
	mbox->irq_map_chan[mchan->ack_irq] = शून्य;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops hi6220_mbox_ops = अणु
	.send_data    = hi6220_mbox_send_data,
	.startup      = hi6220_mbox_startup,
	.shutकरोwn     = hi6220_mbox_shutकरोwn,
	.last_tx_करोne = hi6220_mbox_last_tx_करोne,
पूर्ण;

अटल काष्ठा mbox_chan *hi6220_mbox_xlate(काष्ठा mbox_controller *controller,
					   स्थिर काष्ठा of_phandle_args *spec)
अणु
	काष्ठा hi6220_mbox *mbox = dev_get_drvdata(controller->dev);
	काष्ठा hi6220_mbox_chan *mchan;
	काष्ठा mbox_chan *chan;
	अचिन्हित पूर्णांक i = spec->args[0];
	अचिन्हित पूर्णांक dst_irq = spec->args[1];
	अचिन्हित पूर्णांक ack_irq = spec->args[2];

	/* Bounds checking */
	अगर (i >= mbox->chan_num || dst_irq >= mbox->chan_num ||
	    ack_irq >= mbox->chan_num) अणु
		dev_err(mbox->dev,
			"Invalid channel idx %d dst_irq %d ack_irq %d\n",
			i, dst_irq, ack_irq);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Is requested channel मुक्त? */
	chan = &mbox->chan[i];
	अगर (mbox->irq_map_chan[ack_irq] == (व्योम *)chan) अणु
		dev_err(mbox->dev, "Channel in use\n");
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	mchan = chan->con_priv;
	mchan->dst_irq = dst_irq;
	mchan->ack_irq = ack_irq;

	mbox->irq_map_chan[ack_irq] = (व्योम *)chan;
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा of_device_id hi6220_mbox_of_match[] = अणु
	अणु .compatible = "hisilicon,hi6220-mbox", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hi6220_mbox_of_match);

अटल पूर्णांक hi6220_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hi6220_mbox *mbox;
	काष्ठा resource *res;
	पूर्णांक i, err;

	mbox = devm_kzalloc(dev, माप(*mbox), GFP_KERNEL);
	अगर (!mbox)
		वापस -ENOMEM;

	mbox->dev = dev;
	mbox->chan_num = MBOX_CHAN_MAX;
	mbox->mchan = devm_kसुस्मृति(dev,
		mbox->chan_num, माप(*mbox->mchan), GFP_KERNEL);
	अगर (!mbox->mchan)
		वापस -ENOMEM;

	mbox->chan = devm_kसुस्मृति(dev,
		mbox->chan_num, माप(*mbox->chan), GFP_KERNEL);
	अगर (!mbox->chan)
		वापस -ENOMEM;

	mbox->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mbox->irq < 0)
		वापस mbox->irq;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mbox->ipc = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(mbox->ipc)) अणु
		dev_err(dev, "ioremap ipc failed\n");
		वापस PTR_ERR(mbox->ipc);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	mbox->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(mbox->base)) अणु
		dev_err(dev, "ioremap buffer failed\n");
		वापस PTR_ERR(mbox->base);
	पूर्ण

	err = devm_request_irq(dev, mbox->irq, hi6220_mbox_पूर्णांकerrupt, 0,
			dev_name(dev), mbox);
	अगर (err) अणु
		dev_err(dev, "Failed to register a mailbox IRQ handler: %d\n",
			err);
		वापस -ENODEV;
	पूर्ण

	mbox->controller.dev = dev;
	mbox->controller.chans = &mbox->chan[0];
	mbox->controller.num_chans = mbox->chan_num;
	mbox->controller.ops = &hi6220_mbox_ops;
	mbox->controller.of_xlate = hi6220_mbox_xlate;

	क्रम (i = 0; i < mbox->chan_num; i++) अणु
		mbox->chan[i].con_priv = &mbox->mchan[i];
		mbox->irq_map_chan[i] = शून्य;

		mbox->mchan[i].parent = mbox;
		mbox->mchan[i].slot   = i;
	पूर्ण

	/* mask and clear all पूर्णांकerrupt vectors */
	ग_लिखोl(0x0,  ACK_INT_MSK_REG(mbox->ipc));
	ग_लिखोl(~0x0, ACK_INT_CLR_REG(mbox->ipc));

	/* use पूर्णांकerrupt क्रम tx's ack */
	अगर (of_find_property(node, "hi6220,mbox-tx-noirq", शून्य))
		mbox->tx_irq_mode = false;
	अन्यथा
		mbox->tx_irq_mode = true;

	अगर (mbox->tx_irq_mode)
		mbox->controller.txकरोne_irq = true;
	अन्यथा अणु
		mbox->controller.txकरोne_poll = true;
		mbox->controller.txpoll_period = 5;
	पूर्ण

	err = devm_mbox_controller_रेजिस्टर(dev, &mbox->controller);
	अगर (err) अणु
		dev_err(dev, "Failed to register mailbox %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mbox);
	dev_info(dev, "Mailbox enabled\n");
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hi6220_mbox_driver = अणु
	.driver = अणु
		.name = "hi6220-mbox",
		.of_match_table = hi6220_mbox_of_match,
	पूर्ण,
	.probe	= hi6220_mbox_probe,
पूर्ण;

अटल पूर्णांक __init hi6220_mbox_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hi6220_mbox_driver);
पूर्ण
core_initcall(hi6220_mbox_init);

अटल व्योम __निकास hi6220_mbox_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hi6220_mbox_driver);
पूर्ण
module_निकास(hi6220_mbox_निकास);

MODULE_AUTHOR("Leo Yan <leo.yan@linaro.org>");
MODULE_DESCRIPTION("Hi6220 mailbox driver");
MODULE_LICENSE("GPL v2");
