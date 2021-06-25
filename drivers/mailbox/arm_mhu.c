<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013-2015 Fujitsu Semiconductor Ltd.
 * Copyright (C) 2015 Linaro Ltd.
 * Author: Jassi Brar <jaswinder.singh@linaro.org>
 */

#समावेश <linux/amba/bus.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>

#घोषणा INTR_STAT_OFS	0x0
#घोषणा INTR_SET_OFS	0x8
#घोषणा INTR_CLR_OFS	0x10

#घोषणा MHU_LP_OFFSET	0x0
#घोषणा MHU_HP_OFFSET	0x20
#घोषणा MHU_SEC_OFFSET	0x200
#घोषणा TX_REG_OFFSET	0x100

#घोषणा MHU_CHANS	3

काष्ठा mhu_link अणु
	अचिन्हित irq;
	व्योम __iomem *tx_reg;
	व्योम __iomem *rx_reg;
पूर्ण;

काष्ठा arm_mhu अणु
	व्योम __iomem *base;
	काष्ठा mhu_link mlink[MHU_CHANS];
	काष्ठा mbox_chan chan[MHU_CHANS];
	काष्ठा mbox_controller mbox;
पूर्ण;

अटल irqवापस_t mhu_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा mbox_chan *chan = p;
	काष्ठा mhu_link *mlink = chan->con_priv;
	u32 val;

	val = पढ़ोl_relaxed(mlink->rx_reg + INTR_STAT_OFS);
	अगर (!val)
		वापस IRQ_NONE;

	mbox_chan_received_data(chan, (व्योम *)&val);

	ग_लिखोl_relaxed(val, mlink->rx_reg + INTR_CLR_OFS);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool mhu_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhu_link *mlink = chan->con_priv;
	u32 val = पढ़ोl_relaxed(mlink->tx_reg + INTR_STAT_OFS);

	वापस (val == 0);
पूर्ण

अटल पूर्णांक mhu_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा mhu_link *mlink = chan->con_priv;
	u32 *arg = data;

	ग_लिखोl_relaxed(*arg, mlink->tx_reg + INTR_SET_OFS);

	वापस 0;
पूर्ण

अटल पूर्णांक mhu_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhu_link *mlink = chan->con_priv;
	u32 val;
	पूर्णांक ret;

	val = पढ़ोl_relaxed(mlink->tx_reg + INTR_STAT_OFS);
	ग_लिखोl_relaxed(val, mlink->tx_reg + INTR_CLR_OFS);

	ret = request_irq(mlink->irq, mhu_rx_पूर्णांकerrupt,
			  IRQF_SHARED, "mhu_link", chan);
	अगर (ret) अणु
		dev_err(chan->mbox->dev,
			"Unable to acquire IRQ %d\n", mlink->irq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mhu_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhu_link *mlink = chan->con_priv;

	मुक्त_irq(mlink->irq, chan);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops mhu_ops = अणु
	.send_data = mhu_send_data,
	.startup = mhu_startup,
	.shutकरोwn = mhu_shutकरोwn,
	.last_tx_करोne = mhu_last_tx_करोne,
पूर्ण;

अटल पूर्णांक mhu_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक i, err;
	काष्ठा arm_mhu *mhu;
	काष्ठा device *dev = &adev->dev;
	पूर्णांक mhu_reg[MHU_CHANS] = अणुMHU_LP_OFFSET, MHU_HP_OFFSET, MHU_SEC_OFFSETपूर्ण;

	अगर (!of_device_is_compatible(dev->of_node, "arm,mhu"))
		वापस -ENODEV;

	/* Allocate memory क्रम device */
	mhu = devm_kzalloc(dev, माप(*mhu), GFP_KERNEL);
	अगर (!mhu)
		वापस -ENOMEM;

	mhu->base = devm_ioremap_resource(dev, &adev->res);
	अगर (IS_ERR(mhu->base)) अणु
		dev_err(dev, "ioremap failed\n");
		वापस PTR_ERR(mhu->base);
	पूर्ण

	क्रम (i = 0; i < MHU_CHANS; i++) अणु
		mhu->chan[i].con_priv = &mhu->mlink[i];
		mhu->mlink[i].irq = adev->irq[i];
		mhu->mlink[i].rx_reg = mhu->base + mhu_reg[i];
		mhu->mlink[i].tx_reg = mhu->mlink[i].rx_reg + TX_REG_OFFSET;
	पूर्ण

	mhu->mbox.dev = dev;
	mhu->mbox.chans = &mhu->chan[0];
	mhu->mbox.num_chans = MHU_CHANS;
	mhu->mbox.ops = &mhu_ops;
	mhu->mbox.txकरोne_irq = false;
	mhu->mbox.txकरोne_poll = true;
	mhu->mbox.txpoll_period = 1;

	amba_set_drvdata(adev, mhu);

	err = devm_mbox_controller_रेजिस्टर(dev, &mhu->mbox);
	अगर (err) अणु
		dev_err(dev, "Failed to register mailboxes %d\n", err);
		वापस err;
	पूर्ण

	dev_info(dev, "ARM MHU Mailbox registered\n");
	वापस 0;
पूर्ण

अटल काष्ठा amba_id mhu_ids[] = अणु
	अणु
		.id	= 0x1bb098,
		.mask	= 0xffffff,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(amba, mhu_ids);

अटल काष्ठा amba_driver arm_mhu_driver = अणु
	.drv = अणु
		.name	= "mhu",
	पूर्ण,
	.id_table	= mhu_ids,
	.probe		= mhu_probe,
पूर्ण;
module_amba_driver(arm_mhu_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ARM MHU Driver");
MODULE_AUTHOR("Jassi Brar <jassisinghbrar@gmail.com>");
