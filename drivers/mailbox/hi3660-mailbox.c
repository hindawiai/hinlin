<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-2018 Hisilicon Limited.
// Copyright (c) 2017-2018 Linaro Limited.

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "mailbox.h"

#घोषणा MBOX_CHAN_MAX			32

#घोषणा MBOX_RX				0x0
#घोषणा MBOX_TX				0x1

#घोषणा MBOX_BASE(mbox, ch)		((mbox)->base + ((ch) * 0x40))
#घोषणा MBOX_SRC_REG			0x00
#घोषणा MBOX_DST_REG			0x04
#घोषणा MBOX_DCLR_REG			0x08
#घोषणा MBOX_DSTAT_REG			0x0c
#घोषणा MBOX_MODE_REG			0x10
#घोषणा MBOX_IMASK_REG			0x14
#घोषणा MBOX_ICLR_REG			0x18
#घोषणा MBOX_SEND_REG			0x1c
#घोषणा MBOX_DATA_REG			0x20

#घोषणा MBOX_IPC_LOCK_REG		0xa00
#घोषणा MBOX_IPC_UNLOCK			0x1acce551

#घोषणा MBOX_AUTOMATIC_ACK		1

#घोषणा MBOX_STATE_IDLE			BIT(4)
#घोषणा MBOX_STATE_READY		BIT(5)
#घोषणा MBOX_STATE_ACK			BIT(7)

#घोषणा MBOX_MSG_LEN			8

/**
 * Hi3660 mailbox channel inक्रमmation
 *
 * A channel can be used क्रम TX or RX, it can trigger remote
 * processor पूर्णांकerrupt to notअगरy remote processor and can receive
 * पूर्णांकerrupt अगर has incoming message.
 *
 * @dst_irq:	Interrupt vector क्रम remote processor
 * @ack_irq:	Interrupt vector क्रम local processor
 */
काष्ठा hi3660_chan_info अणु
	अचिन्हित पूर्णांक dst_irq;
	अचिन्हित पूर्णांक ack_irq;
पूर्ण;

/**
 * Hi3660 mailbox controller data
 *
 * Mailbox controller includes 32 channels and can allocate
 * channel क्रम message transferring.
 *
 * @dev:	Device to which it is attached
 * @base:	Base address of the रेजिस्टर mapping region
 * @chan:	Representation of channels in mailbox controller
 * @mchan:	Representation of channel info
 * @controller:	Representation of a communication channel controller
 */
काष्ठा hi3660_mbox अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा mbox_chan chan[MBOX_CHAN_MAX];
	काष्ठा hi3660_chan_info mchan[MBOX_CHAN_MAX];
	काष्ठा mbox_controller controller;
पूर्ण;

अटल काष्ठा hi3660_mbox *to_hi3660_mbox(काष्ठा mbox_controller *mbox)
अणु
	वापस container_of(mbox, काष्ठा hi3660_mbox, controller);
पूर्ण

अटल पूर्णांक hi3660_mbox_check_state(काष्ठा mbox_chan *chan)
अणु
	अचिन्हित दीर्घ ch = (अचिन्हित दीर्घ)chan->con_priv;
	काष्ठा hi3660_mbox *mbox = to_hi3660_mbox(chan->mbox);
	काष्ठा hi3660_chan_info *mchan = &mbox->mchan[ch];
	व्योम __iomem *base = MBOX_BASE(mbox, ch);
	अचिन्हित दीर्घ val;
	अचिन्हित पूर्णांक ret;

	/* Mailbox is पढ़ोy to use */
	अगर (पढ़ोl(base + MBOX_MODE_REG) & MBOX_STATE_READY)
		वापस 0;

	/* Wait क्रम acknowledge from remote */
	ret = पढ़ोx_poll_समयout_atomic(पढ़ोl, base + MBOX_MODE_REG,
			val, (val & MBOX_STATE_ACK), 1000, 300000);
	अगर (ret) अणु
		dev_err(mbox->dev, "%s: timeout for receiving ack\n", __func__);
		वापस ret;
	पूर्ण

	/* clear ack state, mailbox will get back to पढ़ोy state */
	ग_लिखोl(BIT(mchan->ack_irq), base + MBOX_ICLR_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक hi3660_mbox_unlock(काष्ठा mbox_chan *chan)
अणु
	काष्ठा hi3660_mbox *mbox = to_hi3660_mbox(chan->mbox);
	अचिन्हित पूर्णांक val, retry = 3;

	करो अणु
		ग_लिखोl(MBOX_IPC_UNLOCK, mbox->base + MBOX_IPC_LOCK_REG);

		val = पढ़ोl(mbox->base + MBOX_IPC_LOCK_REG);
		अगर (!val)
			अवरोध;

		udelay(10);
	पूर्ण जबतक (retry--);

	अगर (val)
		dev_err(mbox->dev, "%s: failed to unlock mailbox\n", __func__);

	वापस (!val) ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक hi3660_mbox_acquire_channel(काष्ठा mbox_chan *chan)
अणु
	अचिन्हित दीर्घ ch = (अचिन्हित दीर्घ)chan->con_priv;
	काष्ठा hi3660_mbox *mbox = to_hi3660_mbox(chan->mbox);
	काष्ठा hi3660_chan_info *mchan = &mbox->mchan[ch];
	व्योम __iomem *base = MBOX_BASE(mbox, ch);
	अचिन्हित पूर्णांक val, retry;

	क्रम (retry = 10; retry; retry--) अणु
		/* Check अगर channel is in idle state */
		अगर (पढ़ोl(base + MBOX_MODE_REG) & MBOX_STATE_IDLE) अणु
			ग_लिखोl(BIT(mchan->ack_irq), base + MBOX_SRC_REG);

			/* Check ack bit has been set successfully */
			val = पढ़ोl(base + MBOX_SRC_REG);
			अगर (val & BIT(mchan->ack_irq))
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!retry)
		dev_err(mbox->dev, "%s: failed to acquire channel\n", __func__);

	वापस retry ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक hi3660_mbox_startup(काष्ठा mbox_chan *chan)
अणु
	पूर्णांक ret;

	ret = hi3660_mbox_unlock(chan);
	अगर (ret)
		वापस ret;

	ret = hi3660_mbox_acquire_channel(chan);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक hi3660_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *msg)
अणु
	अचिन्हित दीर्घ ch = (अचिन्हित दीर्घ)chan->con_priv;
	काष्ठा hi3660_mbox *mbox = to_hi3660_mbox(chan->mbox);
	काष्ठा hi3660_chan_info *mchan = &mbox->mchan[ch];
	व्योम __iomem *base = MBOX_BASE(mbox, ch);
	u32 *buf = msg;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = hi3660_mbox_check_state(chan);
	अगर (ret)
		वापस ret;

	/* Clear mask क्रम destination पूर्णांकerrupt */
	ग_लिखोl_relaxed(~BIT(mchan->dst_irq), base + MBOX_IMASK_REG);

	/* Config destination क्रम पूर्णांकerrupt vector */
	ग_लिखोl_relaxed(BIT(mchan->dst_irq), base + MBOX_DST_REG);

	/* Automatic acknowledge mode */
	ग_लिखोl_relaxed(MBOX_AUTOMATIC_ACK, base + MBOX_MODE_REG);

	/* Fill message data */
	क्रम (i = 0; i < MBOX_MSG_LEN; i++)
		ग_लिखोl_relaxed(buf[i], base + MBOX_DATA_REG + i * 4);

	/* Trigger data transferring */
	ग_लिखोl(BIT(mchan->ack_irq), base + MBOX_SEND_REG);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops hi3660_mbox_ops = अणु
	.startup	= hi3660_mbox_startup,
	.send_data	= hi3660_mbox_send_data,
पूर्ण;

अटल काष्ठा mbox_chan *hi3660_mbox_xlate(काष्ठा mbox_controller *controller,
					   स्थिर काष्ठा of_phandle_args *spec)
अणु
	काष्ठा hi3660_mbox *mbox = to_hi3660_mbox(controller);
	काष्ठा hi3660_chan_info *mchan;
	अचिन्हित पूर्णांक ch = spec->args[0];

	अगर (ch >= MBOX_CHAN_MAX) अणु
		dev_err(mbox->dev, "Invalid channel idx %d\n", ch);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mchan = &mbox->mchan[ch];
	mchan->dst_irq = spec->args[1];
	mchan->ack_irq = spec->args[2];

	वापस &mbox->chan[ch];
पूर्ण

अटल स्थिर काष्ठा of_device_id hi3660_mbox_of_match[] = अणु
	अणु .compatible = "hisilicon,hi3660-mbox", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, hi3660_mbox_of_match);

अटल पूर्णांक hi3660_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hi3660_mbox *mbox;
	काष्ठा mbox_chan *chan;
	काष्ठा resource *res;
	अचिन्हित दीर्घ ch;
	पूर्णांक err;

	mbox = devm_kzalloc(dev, माप(*mbox), GFP_KERNEL);
	अगर (!mbox)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mbox->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(mbox->base))
		वापस PTR_ERR(mbox->base);

	mbox->dev = dev;
	mbox->controller.dev = dev;
	mbox->controller.chans = mbox->chan;
	mbox->controller.num_chans = MBOX_CHAN_MAX;
	mbox->controller.ops = &hi3660_mbox_ops;
	mbox->controller.of_xlate = hi3660_mbox_xlate;

	/* Initialize mailbox channel data */
	chan = mbox->chan;
	क्रम (ch = 0; ch < MBOX_CHAN_MAX; ch++)
		chan[ch].con_priv = (व्योम *)ch;

	err = devm_mbox_controller_रेजिस्टर(dev, &mbox->controller);
	अगर (err) अणु
		dev_err(dev, "Failed to register mailbox %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mbox);
	dev_info(dev, "Mailbox enabled\n");
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hi3660_mbox_driver = अणु
	.probe  = hi3660_mbox_probe,
	.driver = अणु
		.name = "hi3660-mbox",
		.of_match_table = hi3660_mbox_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hi3660_mbox_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&hi3660_mbox_driver);
पूर्ण
core_initcall(hi3660_mbox_init);

अटल व्योम __निकास hi3660_mbox_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hi3660_mbox_driver);
पूर्ण
module_निकास(hi3660_mbox_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hisilicon Hi3660 Mailbox Controller");
MODULE_AUTHOR("Leo Yan <leo.yan@linaro.org>");
