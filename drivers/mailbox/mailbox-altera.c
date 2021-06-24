<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright Altera Corporation (C) 2013-2014. All rights reserved
 */

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRIVER_NAME	"altera-mailbox"

#घोषणा MAILBOX_CMD_REG			0x00
#घोषणा MAILBOX_PTR_REG			0x04
#घोषणा MAILBOX_STS_REG			0x08
#घोषणा MAILBOX_INTMASK_REG		0x0C

#घोषणा INT_PENDING_MSK			0x1
#घोषणा INT_SPACE_MSK			0x2

#घोषणा STS_PENDING_MSK			0x1
#घोषणा STS_FULL_MSK			0x2
#घोषणा STS_FULL_OFT			0x1

#घोषणा MBOX_PENDING(status)	(((status) & STS_PENDING_MSK))
#घोषणा MBOX_FULL(status)	(((status) & STS_FULL_MSK) >> STS_FULL_OFT)

क्रमागत altera_mbox_msg अणु
	MBOX_CMD = 0,
	MBOX_PTR,
पूर्ण;

#घोषणा MBOX_POLLING_MS		5	/* polling पूर्णांकerval 5ms */

काष्ठा altera_mbox अणु
	bool is_sender;		/* 1-sender, 0-receiver */
	bool पूर्णांकr_mode;
	पूर्णांक irq;
	व्योम __iomem *mbox_base;
	काष्ठा device *dev;
	काष्ठा mbox_controller controller;

	/* If the controller supports only RX polling mode */
	काष्ठा समयr_list rxpoll_समयr;
	काष्ठा mbox_chan *chan;
पूर्ण;

अटल काष्ठा altera_mbox *mbox_chan_to_altera_mbox(काष्ठा mbox_chan *chan)
अणु
	अगर (!chan || !chan->con_priv)
		वापस शून्य;

	वापस (काष्ठा altera_mbox *)chan->con_priv;
पूर्ण

अटल अंतरभूत पूर्णांक altera_mbox_full(काष्ठा altera_mbox *mbox)
अणु
	u32 status;

	status = पढ़ोl_relaxed(mbox->mbox_base + MAILBOX_STS_REG);
	वापस MBOX_FULL(status);
पूर्ण

अटल अंतरभूत पूर्णांक altera_mbox_pending(काष्ठा altera_mbox *mbox)
अणु
	u32 status;

	status = पढ़ोl_relaxed(mbox->mbox_base + MAILBOX_STS_REG);
	वापस MBOX_PENDING(status);
पूर्ण

अटल व्योम altera_mbox_rx_पूर्णांकmask(काष्ठा altera_mbox *mbox, bool enable)
अणु
	u32 mask;

	mask = पढ़ोl_relaxed(mbox->mbox_base + MAILBOX_INTMASK_REG);
	अगर (enable)
		mask |= INT_PENDING_MSK;
	अन्यथा
		mask &= ~INT_PENDING_MSK;
	ग_लिखोl_relaxed(mask, mbox->mbox_base + MAILBOX_INTMASK_REG);
पूर्ण

अटल व्योम altera_mbox_tx_पूर्णांकmask(काष्ठा altera_mbox *mbox, bool enable)
अणु
	u32 mask;

	mask = पढ़ोl_relaxed(mbox->mbox_base + MAILBOX_INTMASK_REG);
	अगर (enable)
		mask |= INT_SPACE_MSK;
	अन्यथा
		mask &= ~INT_SPACE_MSK;
	ग_लिखोl_relaxed(mask, mbox->mbox_base + MAILBOX_INTMASK_REG);
पूर्ण

अटल bool altera_mbox_is_sender(काष्ठा altera_mbox *mbox)
अणु
	u32 reg;
	/* Write a magic number to PTR रेजिस्टर and पढ़ो back this रेजिस्टर.
	 * This रेजिस्टर is पढ़ो-ग_लिखो अगर it is a sender.
	 */
	#घोषणा MBOX_MAGIC	0xA5A5AA55
	ग_लिखोl_relaxed(MBOX_MAGIC, mbox->mbox_base + MAILBOX_PTR_REG);
	reg = पढ़ोl_relaxed(mbox->mbox_base + MAILBOX_PTR_REG);
	अगर (reg == MBOX_MAGIC) अणु
		/* Clear to 0 */
		ग_लिखोl_relaxed(0, mbox->mbox_base + MAILBOX_PTR_REG);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम altera_mbox_rx_data(काष्ठा mbox_chan *chan)
अणु
	काष्ठा altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);
	u32 data[2];

	अगर (altera_mbox_pending(mbox)) अणु
		data[MBOX_PTR] =
			पढ़ोl_relaxed(mbox->mbox_base + MAILBOX_PTR_REG);
		data[MBOX_CMD] =
			पढ़ोl_relaxed(mbox->mbox_base + MAILBOX_CMD_REG);
		mbox_chan_received_data(chan, (व्योम *)data);
	पूर्ण
पूर्ण

अटल व्योम altera_mbox_poll_rx(काष्ठा समयr_list *t)
अणु
	काष्ठा altera_mbox *mbox = from_समयr(mbox, t, rxpoll_समयr);

	altera_mbox_rx_data(mbox->chan);

	mod_समयr(&mbox->rxpoll_समयr,
		  jअगरfies + msecs_to_jअगरfies(MBOX_POLLING_MS));
पूर्ण

अटल irqवापस_t altera_mbox_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा mbox_chan *chan = (काष्ठा mbox_chan *)p;
	काष्ठा altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	altera_mbox_tx_पूर्णांकmask(mbox, false);
	mbox_chan_txकरोne(chan, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t altera_mbox_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा mbox_chan *chan = (काष्ठा mbox_chan *)p;

	altera_mbox_rx_data(chan);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक altera_mbox_startup_sender(काष्ठा mbox_chan *chan)
अणु
	पूर्णांक ret;
	काष्ठा altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	अगर (mbox->पूर्णांकr_mode) अणु
		ret = request_irq(mbox->irq, altera_mbox_tx_पूर्णांकerrupt, 0,
				  DRIVER_NAME, chan);
		अगर (unlikely(ret)) अणु
			dev_err(mbox->dev,
				"failed to register mailbox interrupt:%d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक altera_mbox_startup_receiver(काष्ठा mbox_chan *chan)
अणु
	पूर्णांक ret;
	काष्ठा altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	अगर (mbox->पूर्णांकr_mode) अणु
		ret = request_irq(mbox->irq, altera_mbox_rx_पूर्णांकerrupt, 0,
				  DRIVER_NAME, chan);
		अगर (unlikely(ret)) अणु
			mbox->पूर्णांकr_mode = false;
			जाओ polling; /* use polling अगर failed */
		पूर्ण

		altera_mbox_rx_पूर्णांकmask(mbox, true);
		वापस 0;
	पूर्ण

polling:
	/* Setup polling समयr */
	mbox->chan = chan;
	समयr_setup(&mbox->rxpoll_समयr, altera_mbox_poll_rx, 0);
	mod_समयr(&mbox->rxpoll_समयr,
		  jअगरfies + msecs_to_jअगरfies(MBOX_POLLING_MS));

	वापस 0;
पूर्ण

अटल पूर्णांक altera_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);
	u32 *udata = (u32 *)data;

	अगर (!mbox || !data)
		वापस -EINVAL;
	अगर (!mbox->is_sender) अणु
		dev_warn(mbox->dev,
			 "failed to send. This is receiver mailbox.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (altera_mbox_full(mbox))
		वापस -EBUSY;

	/* Enable पूर्णांकerrupt beक्रमe send */
	अगर (mbox->पूर्णांकr_mode)
		altera_mbox_tx_पूर्णांकmask(mbox, true);

	/* Poपूर्णांकer रेजिस्टर must ग_लिखो beक्रमe command रेजिस्टर */
	ग_लिखोl_relaxed(udata[MBOX_PTR], mbox->mbox_base + MAILBOX_PTR_REG);
	ग_लिखोl_relaxed(udata[MBOX_CMD], mbox->mbox_base + MAILBOX_CMD_REG);

	वापस 0;
पूर्ण

अटल bool altera_mbox_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	/* Return false अगर mailbox is full */
	वापस altera_mbox_full(mbox) ? false : true;
पूर्ण

अटल bool altera_mbox_peek_data(काष्ठा mbox_chan *chan)
अणु
	काष्ठा altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	वापस altera_mbox_pending(mbox) ? true : false;
पूर्ण

अटल पूर्णांक altera_mbox_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);
	पूर्णांक ret = 0;

	अगर (!mbox)
		वापस -EINVAL;

	अगर (mbox->is_sender)
		ret = altera_mbox_startup_sender(chan);
	अन्यथा
		ret = altera_mbox_startup_receiver(chan);

	वापस ret;
पूर्ण

अटल व्योम altera_mbox_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	अगर (mbox->पूर्णांकr_mode) अणु
		/* Unmask all पूर्णांकerrupt masks */
		ग_लिखोl_relaxed(~0, mbox->mbox_base + MAILBOX_INTMASK_REG);
		मुक्त_irq(mbox->irq, chan);
	पूर्ण अन्यथा अगर (!mbox->is_sender) अणु
		del_समयr_sync(&mbox->rxpoll_समयr);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops altera_mbox_ops = अणु
	.send_data = altera_mbox_send_data,
	.startup = altera_mbox_startup,
	.shutकरोwn = altera_mbox_shutकरोwn,
	.last_tx_करोne = altera_mbox_last_tx_करोne,
	.peek_data = altera_mbox_peek_data,
पूर्ण;

अटल पूर्णांक altera_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altera_mbox *mbox;
	काष्ठा resource	*regs;
	काष्ठा mbox_chan *chans;
	पूर्णांक ret;

	mbox = devm_kzalloc(&pdev->dev, माप(*mbox),
			    GFP_KERNEL);
	अगर (!mbox)
		वापस -ENOMEM;

	/* Allocated one channel */
	chans = devm_kzalloc(&pdev->dev, माप(*chans), GFP_KERNEL);
	अगर (!chans)
		वापस -ENOMEM;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	mbox->mbox_base = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(mbox->mbox_base))
		वापस PTR_ERR(mbox->mbox_base);

	/* Check is it a sender or receiver? */
	mbox->is_sender = altera_mbox_is_sender(mbox);

	mbox->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mbox->irq >= 0)
		mbox->पूर्णांकr_mode = true;

	mbox->dev = &pdev->dev;

	/* Hardware supports only one channel. */
	chans[0].con_priv = mbox;
	mbox->controller.dev = mbox->dev;
	mbox->controller.num_chans = 1;
	mbox->controller.chans = chans;
	mbox->controller.ops = &altera_mbox_ops;

	अगर (mbox->is_sender) अणु
		अगर (mbox->पूर्णांकr_mode) अणु
			mbox->controller.txकरोne_irq = true;
		पूर्ण अन्यथा अणु
			mbox->controller.txकरोne_poll = true;
			mbox->controller.txpoll_period = MBOX_POLLING_MS;
		पूर्ण
	पूर्ण

	ret = devm_mbox_controller_रेजिस्टर(&pdev->dev, &mbox->controller);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Register mailbox failed\n");
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mbox);
err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id altera_mbox_match[] = अणु
	अणु .compatible = "altr,mailbox-1.0" पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, altera_mbox_match);

अटल काष्ठा platक्रमm_driver altera_mbox_driver = अणु
	.probe	= altera_mbox_probe,
	.driver	= अणु
		.name	= DRIVER_NAME,
		.of_match_table	= altera_mbox_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(altera_mbox_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Altera mailbox specific functions");
MODULE_AUTHOR("Ley Foon Tan <lftan@altera.com>");
MODULE_ALIAS("platform:altera-mailbox");
