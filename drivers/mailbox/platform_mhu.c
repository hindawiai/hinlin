<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 BayLibre SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Synchronised with arm_mhu.c from :
 * Copyright (C) 2013-2015 Fujitsu Semiconductor Ltd.
 * Copyright (C) 2015 Linaro Ltd.
 * Author: Jassi Brar <jaswinder.singh@linaro.org>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mailbox_controller.h>

#घोषणा INTR_SET_OFS	0x0
#घोषणा INTR_STAT_OFS	0x4
#घोषणा INTR_CLR_OFS	0x8

#घोषणा MHU_SEC_OFFSET	0x0
#घोषणा MHU_LP_OFFSET	0xc
#घोषणा MHU_HP_OFFSET	0x18
#घोषणा TX_REG_OFFSET	0x24

#घोषणा MHU_CHANS	3

काष्ठा platक्रमm_mhu_link अणु
	पूर्णांक irq;
	व्योम __iomem *tx_reg;
	व्योम __iomem *rx_reg;
पूर्ण;

काष्ठा platक्रमm_mhu अणु
	व्योम __iomem *base;
	काष्ठा platक्रमm_mhu_link mlink[MHU_CHANS];
	काष्ठा mbox_chan chan[MHU_CHANS];
	काष्ठा mbox_controller mbox;
पूर्ण;

अटल irqवापस_t platक्रमm_mhu_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा mbox_chan *chan = p;
	काष्ठा platक्रमm_mhu_link *mlink = chan->con_priv;
	u32 val;

	val = पढ़ोl_relaxed(mlink->rx_reg + INTR_STAT_OFS);
	अगर (!val)
		वापस IRQ_NONE;

	mbox_chan_received_data(chan, (व्योम *)&val);

	ग_लिखोl_relaxed(val, mlink->rx_reg + INTR_CLR_OFS);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool platक्रमm_mhu_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा platक्रमm_mhu_link *mlink = chan->con_priv;
	u32 val = पढ़ोl_relaxed(mlink->tx_reg + INTR_STAT_OFS);

	वापस (val == 0);
पूर्ण

अटल पूर्णांक platक्रमm_mhu_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा platक्रमm_mhu_link *mlink = chan->con_priv;
	u32 *arg = data;

	ग_लिखोl_relaxed(*arg, mlink->tx_reg + INTR_SET_OFS);

	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_mhu_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा platक्रमm_mhu_link *mlink = chan->con_priv;
	u32 val;
	पूर्णांक ret;

	val = पढ़ोl_relaxed(mlink->tx_reg + INTR_STAT_OFS);
	ग_लिखोl_relaxed(val, mlink->tx_reg + INTR_CLR_OFS);

	ret = request_irq(mlink->irq, platक्रमm_mhu_rx_पूर्णांकerrupt,
			  IRQF_SHARED, "platform_mhu_link", chan);
	अगर (ret) अणु
		dev_err(chan->mbox->dev,
			"Unable to acquire IRQ %d\n", mlink->irq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम platक्रमm_mhu_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा platक्रमm_mhu_link *mlink = chan->con_priv;

	मुक्त_irq(mlink->irq, chan);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops platक्रमm_mhu_ops = अणु
	.send_data = platक्रमm_mhu_send_data,
	.startup = platक्रमm_mhu_startup,
	.shutकरोwn = platक्रमm_mhu_shutकरोwn,
	.last_tx_करोne = platक्रमm_mhu_last_tx_करोne,
पूर्ण;

अटल पूर्णांक platक्रमm_mhu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, err;
	काष्ठा platक्रमm_mhu *mhu;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक platक्रमm_mhu_reg[MHU_CHANS] = अणु
		MHU_SEC_OFFSET, MHU_LP_OFFSET, MHU_HP_OFFSET
	पूर्ण;

	/* Allocate memory क्रम device */
	mhu = devm_kzalloc(dev, माप(*mhu), GFP_KERNEL);
	अगर (!mhu)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mhu->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(mhu->base)) अणु
		dev_err(dev, "ioremap failed\n");
		वापस PTR_ERR(mhu->base);
	पूर्ण

	क्रम (i = 0; i < MHU_CHANS; i++) अणु
		mhu->chan[i].con_priv = &mhu->mlink[i];
		mhu->mlink[i].irq = platक्रमm_get_irq(pdev, i);
		अगर (mhu->mlink[i].irq < 0) अणु
			dev_err(dev, "failed to get irq%d\n", i);
			वापस mhu->mlink[i].irq;
		पूर्ण
		mhu->mlink[i].rx_reg = mhu->base + platक्रमm_mhu_reg[i];
		mhu->mlink[i].tx_reg = mhu->mlink[i].rx_reg + TX_REG_OFFSET;
	पूर्ण

	mhu->mbox.dev = dev;
	mhu->mbox.chans = &mhu->chan[0];
	mhu->mbox.num_chans = MHU_CHANS;
	mhu->mbox.ops = &platक्रमm_mhu_ops;
	mhu->mbox.txकरोne_irq = false;
	mhu->mbox.txकरोne_poll = true;
	mhu->mbox.txpoll_period = 1;

	platक्रमm_set_drvdata(pdev, mhu);

	err = devm_mbox_controller_रेजिस्टर(dev, &mhu->mbox);
	अगर (err) अणु
		dev_err(dev, "Failed to register mailboxes %d\n", err);
		वापस err;
	पूर्ण

	dev_info(dev, "Platform MHU Mailbox registered\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id platक्रमm_mhu_dt_ids[] = अणु
	अणु .compatible = "amlogic,meson-gxbb-mhu", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, platक्रमm_mhu_dt_ids);

अटल काष्ठा platक्रमm_driver platक्रमm_mhu_driver = अणु
	.probe	= platक्रमm_mhu_probe,
	.driver = अणु
		.name = "platform-mhu",
		.of_match_table	= platक्रमm_mhu_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(platक्रमm_mhu_driver);

MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:platform-mhu");
MODULE_DESCRIPTION("Platform MHU Driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
