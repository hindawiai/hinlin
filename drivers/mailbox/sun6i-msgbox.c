<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2017-2019 Samuel Holland <samuel@sholland.org>

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/spinlock.h>

#घोषणा NUM_CHANS		8

#घोषणा CTRL_REG(n)		(0x0000 + 0x4 * ((n) / 4))
#घोषणा CTRL_RX(n)		BIT(0 + 8 * ((n) % 4))
#घोषणा CTRL_TX(n)		BIT(4 + 8 * ((n) % 4))

#घोषणा REMOTE_IRQ_EN_REG	0x0040
#घोषणा REMOTE_IRQ_STAT_REG	0x0050
#घोषणा LOCAL_IRQ_EN_REG	0x0060
#घोषणा LOCAL_IRQ_STAT_REG	0x0070

#घोषणा RX_IRQ(n)		BIT(0 + 2 * (n))
#घोषणा RX_IRQ_MASK		0x5555
#घोषणा TX_IRQ(n)		BIT(1 + 2 * (n))
#घोषणा TX_IRQ_MASK		0xaaaa

#घोषणा FIFO_STAT_REG(n)	(0x0100 + 0x4 * (n))
#घोषणा FIFO_STAT_MASK		GENMASK(0, 0)

#घोषणा MSG_STAT_REG(n)		(0x0140 + 0x4 * (n))
#घोषणा MSG_STAT_MASK		GENMASK(2, 0)

#घोषणा MSG_DATA_REG(n)		(0x0180 + 0x4 * (n))

#घोषणा mbox_dbg(mbox, ...)	dev_dbg((mbox)->controller.dev, __VA_ARGS__)

काष्ठा sun6i_msgbox अणु
	काष्ठा mbox_controller controller;
	काष्ठा clk *clk;
	spinlock_t lock;
	व्योम __iomem *regs;
पूर्ण;

अटल bool sun6i_msgbox_last_tx_करोne(काष्ठा mbox_chan *chan);
अटल bool sun6i_msgbox_peek_data(काष्ठा mbox_chan *chan);

अटल अंतरभूत पूर्णांक channel_number(काष्ठा mbox_chan *chan)
अणु
	वापस chan - chan->mbox->chans;
पूर्ण

अटल अंतरभूत काष्ठा sun6i_msgbox *to_sun6i_msgbox(काष्ठा mbox_chan *chan)
अणु
	वापस chan->con_priv;
पूर्ण

अटल irqवापस_t sun6i_msgbox_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun6i_msgbox *mbox = dev_id;
	uपूर्णांक32_t status;
	पूर्णांक n;

	/* Only examine channels that are currently enabled. */
	status = पढ़ोl(mbox->regs + LOCAL_IRQ_EN_REG) &
		 पढ़ोl(mbox->regs + LOCAL_IRQ_STAT_REG);

	अगर (!(status & RX_IRQ_MASK))
		वापस IRQ_NONE;

	क्रम (n = 0; n < NUM_CHANS; ++n) अणु
		काष्ठा mbox_chan *chan = &mbox->controller.chans[n];

		अगर (!(status & RX_IRQ(n)))
			जारी;

		जबतक (sun6i_msgbox_peek_data(chan)) अणु
			uपूर्णांक32_t msg = पढ़ोl(mbox->regs + MSG_DATA_REG(n));

			mbox_dbg(mbox, "Channel %d received 0x%08x\n", n, msg);
			mbox_chan_received_data(chan, &msg);
		पूर्ण

		/* The IRQ can be cleared only once the FIFO is empty. */
		ग_लिखोl(RX_IRQ(n), mbox->regs + LOCAL_IRQ_STAT_REG);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun6i_msgbox_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	पूर्णांक n = channel_number(chan);
	uपूर्णांक32_t msg = *(uपूर्णांक32_t *)data;

	/* Using a channel backwards माला_लो the hardware पूर्णांकo a bad state. */
	अगर (WARN_ON_ONCE(!(पढ़ोl(mbox->regs + CTRL_REG(n)) & CTRL_TX(n))))
		वापस 0;

	ग_लिखोl(msg, mbox->regs + MSG_DATA_REG(n));
	mbox_dbg(mbox, "Channel %d sent 0x%08x\n", n, msg);

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_msgbox_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	पूर्णांक n = channel_number(chan);

	/* The coprocessor is responsible क्रम setting channel directions. */
	अगर (पढ़ोl(mbox->regs + CTRL_REG(n)) & CTRL_RX(n)) अणु
		/* Flush the receive FIFO. */
		जबतक (sun6i_msgbox_peek_data(chan))
			पढ़ोl(mbox->regs + MSG_DATA_REG(n));
		ग_लिखोl(RX_IRQ(n), mbox->regs + LOCAL_IRQ_STAT_REG);

		/* Enable the receive IRQ. */
		spin_lock(&mbox->lock);
		ग_लिखोl(पढ़ोl(mbox->regs + LOCAL_IRQ_EN_REG) | RX_IRQ(n),
		       mbox->regs + LOCAL_IRQ_EN_REG);
		spin_unlock(&mbox->lock);
	पूर्ण

	mbox_dbg(mbox, "Channel %d startup complete\n", n);

	वापस 0;
पूर्ण

अटल व्योम sun6i_msgbox_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	पूर्णांक n = channel_number(chan);

	अगर (पढ़ोl(mbox->regs + CTRL_REG(n)) & CTRL_RX(n)) अणु
		/* Disable the receive IRQ. */
		spin_lock(&mbox->lock);
		ग_लिखोl(पढ़ोl(mbox->regs + LOCAL_IRQ_EN_REG) & ~RX_IRQ(n),
		       mbox->regs + LOCAL_IRQ_EN_REG);
		spin_unlock(&mbox->lock);

		/* Attempt to flush the FIFO until the IRQ is cleared. */
		करो अणु
			जबतक (sun6i_msgbox_peek_data(chan))
				पढ़ोl(mbox->regs + MSG_DATA_REG(n));
			ग_लिखोl(RX_IRQ(n), mbox->regs + LOCAL_IRQ_STAT_REG);
		पूर्ण जबतक (पढ़ोl(mbox->regs + LOCAL_IRQ_STAT_REG) & RX_IRQ(n));
	पूर्ण

	mbox_dbg(mbox, "Channel %d shutdown complete\n", n);
पूर्ण

अटल bool sun6i_msgbox_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	पूर्णांक n = channel_number(chan);

	/*
	 * The hardware allows snooping on the remote user's IRQ statuses.
	 * We consider a message to be acknowledged only once the receive IRQ
	 * क्रम that channel is cleared. Since the receive IRQ क्रम a channel
	 * cannot be cleared until the FIFO क्रम that channel is empty, this
	 * ensures that the message has actually been पढ़ो. It also gives the
	 * recipient an opportunity to perक्रमm minimal processing beक्रमe
	 * acknowledging the message.
	 */
	वापस !(पढ़ोl(mbox->regs + REMOTE_IRQ_STAT_REG) & RX_IRQ(n));
पूर्ण

अटल bool sun6i_msgbox_peek_data(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sun6i_msgbox *mbox = to_sun6i_msgbox(chan);
	पूर्णांक n = channel_number(chan);

	वापस पढ़ोl(mbox->regs + MSG_STAT_REG(n)) & MSG_STAT_MASK;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops sun6i_msgbox_chan_ops = अणु
	.send_data    = sun6i_msgbox_send_data,
	.startup      = sun6i_msgbox_startup,
	.shutकरोwn     = sun6i_msgbox_shutकरोwn,
	.last_tx_करोne = sun6i_msgbox_last_tx_करोne,
	.peek_data    = sun6i_msgbox_peek_data,
पूर्ण;

अटल पूर्णांक sun6i_msgbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mbox_chan *chans;
	काष्ठा reset_control *reset;
	काष्ठा resource *res;
	काष्ठा sun6i_msgbox *mbox;
	पूर्णांक i, ret;

	mbox = devm_kzalloc(dev, माप(*mbox), GFP_KERNEL);
	अगर (!mbox)
		वापस -ENOMEM;

	chans = devm_kसुस्मृति(dev, NUM_CHANS, माप(*chans), GFP_KERNEL);
	अगर (!chans)
		वापस -ENOMEM;

	क्रम (i = 0; i < NUM_CHANS; ++i)
		chans[i].con_priv = mbox;

	mbox->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(mbox->clk)) अणु
		ret = PTR_ERR(mbox->clk);
		dev_err(dev, "Failed to get clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(mbox->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(reset)) अणु
		ret = PTR_ERR(reset);
		dev_err(dev, "Failed to get reset control: %d\n", ret);
		जाओ err_disable_unprepare;
	पूर्ण

	/*
	 * NOTE: We rely on platक्रमm firmware to preconfigure the channel
	 * directions, and we share this hardware block with other firmware
	 * that runs concurrently with Linux (e.g. a trusted monitor).
	 *
	 * Thereक्रमe, we करो *not* निश्चित the reset line अगर probing fails or
	 * when removing the device.
	 */
	ret = reset_control_deनिश्चित(reset);
	अगर (ret) अणु
		dev_err(dev, "Failed to deassert reset: %d\n", ret);
		जाओ err_disable_unprepare;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENODEV;
		जाओ err_disable_unprepare;
	पूर्ण

	mbox->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mbox->regs)) अणु
		ret = PTR_ERR(mbox->regs);
		dev_err(dev, "Failed to map MMIO resource: %d\n", ret);
		जाओ err_disable_unprepare;
	पूर्ण

	/* Disable all IRQs क्रम this end of the msgbox. */
	ग_लिखोl(0, mbox->regs + LOCAL_IRQ_EN_REG);

	ret = devm_request_irq(dev, irq_of_parse_and_map(dev->of_node, 0),
			       sun6i_msgbox_irq, 0, dev_name(dev), mbox);
	अगर (ret) अणु
		dev_err(dev, "Failed to register IRQ handler: %d\n", ret);
		जाओ err_disable_unprepare;
	पूर्ण

	mbox->controller.dev           = dev;
	mbox->controller.ops           = &sun6i_msgbox_chan_ops;
	mbox->controller.chans         = chans;
	mbox->controller.num_chans     = NUM_CHANS;
	mbox->controller.txकरोne_irq    = false;
	mbox->controller.txकरोne_poll   = true;
	mbox->controller.txpoll_period = 5;

	spin_lock_init(&mbox->lock);
	platक्रमm_set_drvdata(pdev, mbox);

	ret = mbox_controller_रेजिस्टर(&mbox->controller);
	अगर (ret) अणु
		dev_err(dev, "Failed to register controller: %d\n", ret);
		जाओ err_disable_unprepare;
	पूर्ण

	वापस 0;

err_disable_unprepare:
	clk_disable_unprepare(mbox->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sun6i_msgbox_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun6i_msgbox *mbox = platक्रमm_get_drvdata(pdev);

	mbox_controller_unरेजिस्टर(&mbox->controller);
	/* See the comment in sun6i_msgbox_probe about the reset line. */
	clk_disable_unprepare(mbox->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun6i_msgbox_of_match[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-msgbox", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun6i_msgbox_of_match);

अटल काष्ठा platक्रमm_driver sun6i_msgbox_driver = अणु
	.driver = अणु
		.name = "sun6i-msgbox",
		.of_match_table = sun6i_msgbox_of_match,
	पूर्ण,
	.probe  = sun6i_msgbox_probe,
	.हटाओ = sun6i_msgbox_हटाओ,
पूर्ण;
module_platक्रमm_driver(sun6i_msgbox_driver);

MODULE_AUTHOR("Samuel Holland <samuel@sholland.org>");
MODULE_DESCRIPTION("Allwinner sun6i/sun8i/sun9i/sun50i Message Box");
MODULE_LICENSE("GPL v2");
