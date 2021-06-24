<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rWTM BIU Mailbox driver क्रम Armada 37xx
 *
 * Author: Marek Behथजn <kabel@kernel.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/armada-37xx-rwपंचांग-mailbox.h>

#घोषणा DRIVER_NAME	"armada-37xx-rwtm-mailbox"

/* relative to rWTM BIU Mailbox Registers */
#घोषणा RWTM_MBOX_PARAM(i)		(0x0 + ((i) << 2))
#घोषणा RWTM_MBOX_COMMAND		0x40
#घोषणा RWTM_MBOX_RETURN_STATUS		0x80
#घोषणा RWTM_MBOX_STATUS(i)		(0x84 + ((i) << 2))
#घोषणा RWTM_MBOX_FIFO_STATUS		0xc4
#घोषणा FIFO_STS_RDY			0x100
#घोषणा FIFO_STS_CNTR_MASK		0x7
#घोषणा FIFO_STS_CNTR_MAX		4

#घोषणा RWTM_HOST_INT_RESET		0xc8
#घोषणा RWTM_HOST_INT_MASK		0xcc
#घोषणा SP_CMD_COMPLETE			BIT(0)
#घोषणा SP_CMD_QUEUE_FULL_ACCESS	BIT(17)
#घोषणा SP_CMD_QUEUE_FULL		BIT(18)

काष्ठा a37xx_mbox अणु
	काष्ठा device *dev;
	काष्ठा mbox_controller controller;
	व्योम __iomem *base;
	पूर्णांक irq;
पूर्ण;

अटल व्योम a37xx_mbox_receive(काष्ठा mbox_chan *chan)
अणु
	काष्ठा a37xx_mbox *mbox = chan->con_priv;
	काष्ठा armada_37xx_rwपंचांग_rx_msg rx_msg;
	पूर्णांक i;

	rx_msg.retval = पढ़ोl(mbox->base + RWTM_MBOX_RETURN_STATUS);
	क्रम (i = 0; i < 16; ++i)
		rx_msg.status[i] = पढ़ोl(mbox->base + RWTM_MBOX_STATUS(i));

	mbox_chan_received_data(chan, &rx_msg);
पूर्ण

अटल irqवापस_t a37xx_mbox_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mbox_chan *chan = data;
	काष्ठा a37xx_mbox *mbox = chan->con_priv;
	u32 reg;

	reg = पढ़ोl(mbox->base + RWTM_HOST_INT_RESET);

	अगर (reg & SP_CMD_COMPLETE)
		a37xx_mbox_receive(chan);

	अगर (reg & (SP_CMD_QUEUE_FULL_ACCESS | SP_CMD_QUEUE_FULL))
		dev_err(mbox->dev, "Secure processor command queue full\n");

	ग_लिखोl(reg, mbox->base + RWTM_HOST_INT_RESET);
	अगर (reg)
		mbox_chan_txकरोne(chan, 0);

	वापस reg ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक a37xx_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा a37xx_mbox *mbox = chan->con_priv;
	काष्ठा armada_37xx_rwपंचांग_tx_msg *msg = data;
	पूर्णांक i;
	u32 reg;

	अगर (!data)
		वापस -EINVAL;

	reg = पढ़ोl(mbox->base + RWTM_MBOX_FIFO_STATUS);
	अगर (!(reg & FIFO_STS_RDY))
		dev_warn(mbox->dev, "Secure processor not ready\n");

	अगर ((reg & FIFO_STS_CNTR_MASK) >= FIFO_STS_CNTR_MAX) अणु
		dev_err(mbox->dev, "Secure processor command queue full\n");
		वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < 16; ++i)
		ग_लिखोl(msg->args[i], mbox->base + RWTM_MBOX_PARAM(i));
	ग_लिखोl(msg->command, mbox->base + RWTM_MBOX_COMMAND);

	वापस 0;
पूर्ण

अटल पूर्णांक a37xx_mbox_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा a37xx_mbox *mbox = chan->con_priv;
	u32 reg;
	पूर्णांक ret;

	ret = devm_request_irq(mbox->dev, mbox->irq, a37xx_mbox_irq_handler, 0,
			       DRIVER_NAME, chan);
	अगर (ret < 0) अणु
		dev_err(mbox->dev, "Cannot request irq\n");
		वापस ret;
	पूर्ण

	/* enable IRQ generation */
	reg = पढ़ोl(mbox->base + RWTM_HOST_INT_MASK);
	reg &= ~(SP_CMD_COMPLETE | SP_CMD_QUEUE_FULL_ACCESS | SP_CMD_QUEUE_FULL);
	ग_लिखोl(reg, mbox->base + RWTM_HOST_INT_MASK);

	वापस 0;
पूर्ण

अटल व्योम a37xx_mbox_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	u32 reg;
	काष्ठा a37xx_mbox *mbox = chan->con_priv;

	/* disable पूर्णांकerrupt generation */
	reg = पढ़ोl(mbox->base + RWTM_HOST_INT_MASK);
	reg |= SP_CMD_COMPLETE | SP_CMD_QUEUE_FULL_ACCESS | SP_CMD_QUEUE_FULL;
	ग_लिखोl(reg, mbox->base + RWTM_HOST_INT_MASK);

	devm_मुक्त_irq(mbox->dev, mbox->irq, chan);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops a37xx_mbox_ops = अणु
	.send_data	= a37xx_mbox_send_data,
	.startup	= a37xx_mbox_startup,
	.shutकरोwn	= a37xx_mbox_shutकरोwn,
पूर्ण;

अटल पूर्णांक armada_37xx_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा a37xx_mbox *mbox;
	काष्ठा mbox_chan *chans;
	पूर्णांक ret;

	mbox = devm_kzalloc(&pdev->dev, माप(*mbox), GFP_KERNEL);
	अगर (!mbox)
		वापस -ENOMEM;

	/* Allocated one channel */
	chans = devm_kzalloc(&pdev->dev, माप(*chans), GFP_KERNEL);
	अगर (!chans)
		वापस -ENOMEM;

	mbox->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mbox->base))
		वापस PTR_ERR(mbox->base);

	mbox->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mbox->irq < 0)
		वापस mbox->irq;

	mbox->dev = &pdev->dev;

	/* Hardware supports only one channel. */
	chans[0].con_priv = mbox;
	mbox->controller.dev = mbox->dev;
	mbox->controller.num_chans = 1;
	mbox->controller.chans = chans;
	mbox->controller.ops = &a37xx_mbox_ops;
	mbox->controller.txकरोne_irq = true;

	ret = devm_mbox_controller_रेजिस्टर(mbox->dev, &mbox->controller);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register mailbox controller\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mbox);
	वापस ret;
पूर्ण


अटल स्थिर काष्ठा of_device_id armada_37xx_mbox_match[] = अणु
	अणु .compatible = "marvell,armada-3700-rwtm-mailbox" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, armada_37xx_mbox_match);

अटल काष्ठा platक्रमm_driver armada_37xx_mbox_driver = अणु
	.probe	= armada_37xx_mbox_probe,
	.driver	= अणु
		.name		= DRIVER_NAME,
		.of_match_table	= armada_37xx_mbox_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(armada_37xx_mbox_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("rWTM BIU Mailbox driver for Armada 37xx");
MODULE_AUTHOR("Marek Behun <kabel@kernel.org>");
