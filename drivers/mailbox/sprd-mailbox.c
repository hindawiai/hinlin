<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Spपढ़ोtrum mailbox driver
 *
 * Copyright (c) 2020 Spपढ़ोtrum Communications Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>

#घोषणा SPRD_MBOX_ID		0x0
#घोषणा SPRD_MBOX_MSG_LOW	0x4
#घोषणा SPRD_MBOX_MSG_HIGH	0x8
#घोषणा SPRD_MBOX_TRIGGER	0xc
#घोषणा SPRD_MBOX_FIFO_RST	0x10
#घोषणा SPRD_MBOX_FIFO_STS	0x14
#घोषणा SPRD_MBOX_IRQ_STS	0x18
#घोषणा SPRD_MBOX_IRQ_MSK	0x1c
#घोषणा SPRD_MBOX_LOCK		0x20
#घोषणा SPRD_MBOX_FIFO_DEPTH	0x24

/* Bit and mask definition क्रम inbox's SPRD_MBOX_FIFO_STS रेजिस्टर */
#घोषणा SPRD_INBOX_FIFO_DELIVER_MASK		GENMASK(23, 16)
#घोषणा SPRD_INBOX_FIFO_OVERLOW_MASK		GENMASK(15, 8)
#घोषणा SPRD_INBOX_FIFO_DELIVER_SHIFT		16
#घोषणा SPRD_INBOX_FIFO_BUSY_MASK		GENMASK(7, 0)

/* Bit and mask definition क्रम SPRD_MBOX_IRQ_STS रेजिस्टर */
#घोषणा SPRD_MBOX_IRQ_CLR			BIT(0)

/* Bit and mask definition क्रम outbox's SPRD_MBOX_FIFO_STS रेजिस्टर */
#घोषणा SPRD_OUTBOX_FIFO_FULL			BIT(2)
#घोषणा SPRD_OUTBOX_FIFO_WR_SHIFT		16
#घोषणा SPRD_OUTBOX_FIFO_RD_SHIFT		24
#घोषणा SPRD_OUTBOX_FIFO_POS_MASK		GENMASK(7, 0)

/* Bit and mask definition क्रम inbox's SPRD_MBOX_IRQ_MSK रेजिस्टर */
#घोषणा SPRD_INBOX_FIFO_BLOCK_IRQ		BIT(0)
#घोषणा SPRD_INBOX_FIFO_OVERFLOW_IRQ		BIT(1)
#घोषणा SPRD_INBOX_FIFO_DELIVER_IRQ		BIT(2)
#घोषणा SPRD_INBOX_FIFO_IRQ_MASK		GENMASK(2, 0)

/* Bit and mask definition क्रम outbox's SPRD_MBOX_IRQ_MSK रेजिस्टर */
#घोषणा SPRD_OUTBOX_FIFO_NOT_EMPTY_IRQ		BIT(0)
#घोषणा SPRD_OUTBOX_FIFO_IRQ_MASK		GENMASK(4, 0)

#घोषणा SPRD_OUTBOX_BASE_SPAN			0x1000
#घोषणा SPRD_MBOX_CHAN_MAX			8
#घोषणा SPRD_SUPP_INBOX_ID_SC9863A		7

काष्ठा sprd_mbox_priv अणु
	काष्ठा mbox_controller	mbox;
	काष्ठा device		*dev;
	व्योम __iomem		*inbox_base;
	व्योम __iomem		*outbox_base;
	/*  Base रेजिस्टर address क्रम supplementary outbox */
	व्योम __iomem		*supp_base;
	काष्ठा clk		*clk;
	u32			outbox_fअगरo_depth;

	काष्ठा mutex		lock;
	u32			refcnt;
	काष्ठा mbox_chan	chan[SPRD_MBOX_CHAN_MAX];
पूर्ण;

अटल काष्ठा sprd_mbox_priv *to_sprd_mbox_priv(काष्ठा mbox_controller *mbox)
अणु
	वापस container_of(mbox, काष्ठा sprd_mbox_priv, mbox);
पूर्ण

अटल u32 sprd_mbox_get_fअगरo_len(काष्ठा sprd_mbox_priv *priv, u32 fअगरo_sts)
अणु
	u32 wr_pos = (fअगरo_sts >> SPRD_OUTBOX_FIFO_WR_SHIFT) &
		SPRD_OUTBOX_FIFO_POS_MASK;
	u32 rd_pos = (fअगरo_sts >> SPRD_OUTBOX_FIFO_RD_SHIFT) &
		SPRD_OUTBOX_FIFO_POS_MASK;
	u32 fअगरo_len;

	/*
	 * If the पढ़ो poपूर्णांकer is equal with ग_लिखो poपूर्णांकer, which means the fअगरo
	 * is full or empty.
	 */
	अगर (wr_pos == rd_pos) अणु
		अगर (fअगरo_sts & SPRD_OUTBOX_FIFO_FULL)
			fअगरo_len = priv->outbox_fअगरo_depth;
		अन्यथा
			fअगरo_len = 0;
	पूर्ण अन्यथा अगर (wr_pos > rd_pos) अणु
		fअगरo_len = wr_pos - rd_pos;
	पूर्ण अन्यथा अणु
		fअगरo_len = priv->outbox_fअगरo_depth - rd_pos + wr_pos;
	पूर्ण

	वापस fअगरo_len;
पूर्ण

अटल irqवापस_t करो_outbox_isr(व्योम __iomem *base, काष्ठा sprd_mbox_priv *priv)
अणु
	काष्ठा mbox_chan *chan;
	u32 fअगरo_sts, fअगरo_len, msg[2];
	पूर्णांक i, id;

	fअगरo_sts = पढ़ोl(base + SPRD_MBOX_FIFO_STS);

	fअगरo_len = sprd_mbox_get_fअगरo_len(priv, fअगरo_sts);
	अगर (!fअगरo_len) अणु
		dev_warn_ratelimited(priv->dev, "spurious outbox interrupt\n");
		वापस IRQ_NONE;
	पूर्ण

	क्रम (i = 0; i < fअगरo_len; i++) अणु
		msg[0] = पढ़ोl(base + SPRD_MBOX_MSG_LOW);
		msg[1] = पढ़ोl(base + SPRD_MBOX_MSG_HIGH);
		id = पढ़ोl(base + SPRD_MBOX_ID);

		chan = &priv->chan[id];
		अगर (chan->cl)
			mbox_chan_received_data(chan, (व्योम *)msg);
		अन्यथा
			dev_warn_ratelimited(priv->dev,
				    "message's been dropped at ch[%d]\n", id);

		/* Trigger to update outbox FIFO poपूर्णांकer */
		ग_लिखोl(0x1, base + SPRD_MBOX_TRIGGER);
	पूर्ण

	/* Clear irq status after पढ़ोing all message. */
	ग_लिखोl(SPRD_MBOX_IRQ_CLR, base + SPRD_MBOX_IRQ_STS);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sprd_mbox_outbox_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sprd_mbox_priv *priv = data;

	वापस करो_outbox_isr(priv->outbox_base, priv);
पूर्ण

अटल irqवापस_t sprd_mbox_supp_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sprd_mbox_priv *priv = data;

	वापस करो_outbox_isr(priv->supp_base, priv);
पूर्ण

अटल irqवापस_t sprd_mbox_inbox_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sprd_mbox_priv *priv = data;
	काष्ठा mbox_chan *chan;
	u32 fअगरo_sts, send_sts, busy, id;

	fअगरo_sts = पढ़ोl(priv->inbox_base + SPRD_MBOX_FIFO_STS);

	/* Get the inbox data delivery status */
	send_sts = (fअगरo_sts & SPRD_INBOX_FIFO_DELIVER_MASK) >>
		SPRD_INBOX_FIFO_DELIVER_SHIFT;
	अगर (!send_sts) अणु
		dev_warn_ratelimited(priv->dev, "spurious inbox interrupt\n");
		वापस IRQ_NONE;
	पूर्ण

	जबतक (send_sts) अणु
		id = __ffs(send_sts);
		send_sts &= (send_sts - 1);

		chan = &priv->chan[id];

		/*
		 * Check अगर the message was fetched by remote target, अगर yes,
		 * that means the transmission has been completed.
		 */
		busy = fअगरo_sts & SPRD_INBOX_FIFO_BUSY_MASK;
		अगर (!(busy & BIT(id)))
			mbox_chan_txकरोne(chan, 0);
	पूर्ण

	/* Clear FIFO delivery and overflow status */
	ग_लिखोl(fअगरo_sts &
	       (SPRD_INBOX_FIFO_DELIVER_MASK | SPRD_INBOX_FIFO_OVERLOW_MASK),
	       priv->inbox_base + SPRD_MBOX_FIFO_RST);

	/* Clear irq status */
	ग_लिखोl(SPRD_MBOX_IRQ_CLR, priv->inbox_base + SPRD_MBOX_IRQ_STS);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sprd_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *msg)
अणु
	काष्ठा sprd_mbox_priv *priv = to_sprd_mbox_priv(chan->mbox);
	अचिन्हित दीर्घ id = (अचिन्हित दीर्घ)chan->con_priv;
	u32 *data = msg;

	/* Write data पूर्णांकo inbox FIFO, and only support 8 bytes every समय */
	ग_लिखोl(data[0], priv->inbox_base + SPRD_MBOX_MSG_LOW);
	ग_लिखोl(data[1], priv->inbox_base + SPRD_MBOX_MSG_HIGH);

	/* Set target core id */
	ग_लिखोl(id, priv->inbox_base + SPRD_MBOX_ID);

	/* Trigger remote request */
	ग_लिखोl(0x1, priv->inbox_base + SPRD_MBOX_TRIGGER);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_mbox_flush(काष्ठा mbox_chan *chan, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा sprd_mbox_priv *priv = to_sprd_mbox_priv(chan->mbox);
	अचिन्हित दीर्घ id = (अचिन्हित दीर्घ)chan->con_priv;
	u32 busy;

	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		busy = पढ़ोl(priv->inbox_base + SPRD_MBOX_FIFO_STS) &
			SPRD_INBOX_FIFO_BUSY_MASK;
		अगर (!(busy & BIT(id))) अणु
			mbox_chan_txकरोne(chan, 0);
			वापस 0;
		पूर्ण

		udelay(1);
	पूर्ण

	वापस -ETIME;
पूर्ण

अटल पूर्णांक sprd_mbox_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sprd_mbox_priv *priv = to_sprd_mbox_priv(chan->mbox);
	u32 val;

	mutex_lock(&priv->lock);
	अगर (priv->refcnt++ == 0) अणु
		/* Select outbox FIFO mode and reset the outbox FIFO status */
		ग_लिखोl(0x0, priv->outbox_base + SPRD_MBOX_FIFO_RST);

		/* Enable inbox FIFO overflow and delivery पूर्णांकerrupt */
		val = पढ़ोl(priv->inbox_base + SPRD_MBOX_IRQ_MSK);
		val &= ~(SPRD_INBOX_FIFO_OVERFLOW_IRQ | SPRD_INBOX_FIFO_DELIVER_IRQ);
		ग_लिखोl(val, priv->inbox_base + SPRD_MBOX_IRQ_MSK);

		/* Enable outbox FIFO not empty पूर्णांकerrupt */
		val = पढ़ोl(priv->outbox_base + SPRD_MBOX_IRQ_MSK);
		val &= ~SPRD_OUTBOX_FIFO_NOT_EMPTY_IRQ;
		ग_लिखोl(val, priv->outbox_base + SPRD_MBOX_IRQ_MSK);

		/* Enable supplementary outbox as the fundamental one */
		अगर (priv->supp_base) अणु
			ग_लिखोl(0x0, priv->supp_base + SPRD_MBOX_FIFO_RST);
			val = पढ़ोl(priv->supp_base + SPRD_MBOX_IRQ_MSK);
			val &= ~SPRD_OUTBOX_FIFO_NOT_EMPTY_IRQ;
			ग_लिखोl(val, priv->supp_base + SPRD_MBOX_IRQ_MSK);
		पूर्ण
	पूर्ण
	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल व्योम sprd_mbox_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा sprd_mbox_priv *priv = to_sprd_mbox_priv(chan->mbox);

	mutex_lock(&priv->lock);
	अगर (--priv->refcnt == 0) अणु
		/* Disable inbox & outbox पूर्णांकerrupt */
		ग_लिखोl(SPRD_INBOX_FIFO_IRQ_MASK, priv->inbox_base + SPRD_MBOX_IRQ_MSK);
		ग_लिखोl(SPRD_OUTBOX_FIFO_IRQ_MASK, priv->outbox_base + SPRD_MBOX_IRQ_MSK);

		अगर (priv->supp_base)
			ग_लिखोl(SPRD_OUTBOX_FIFO_IRQ_MASK,
			       priv->supp_base + SPRD_MBOX_IRQ_MSK);
	पूर्ण
	mutex_unlock(&priv->lock);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops sprd_mbox_ops = अणु
	.send_data	= sprd_mbox_send_data,
	.flush		= sprd_mbox_flush,
	.startup	= sprd_mbox_startup,
	.shutकरोwn	= sprd_mbox_shutकरोwn,
पूर्ण;

अटल व्योम sprd_mbox_disable(व्योम *data)
अणु
	काष्ठा sprd_mbox_priv *priv = data;

	clk_disable_unprepare(priv->clk);
पूर्ण

अटल पूर्णांक sprd_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sprd_mbox_priv *priv;
	पूर्णांक ret, inbox_irq, outbox_irq, supp_irq;
	अचिन्हित दीर्घ id, supp;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	mutex_init(&priv->lock);

	/*
	 * Unisoc mailbox uses an inbox to send messages to the target
	 * core, and uses (an) outbox(es) to receive messages from other
	 * cores.
	 *
	 * Thus in general the mailbox controller supplies 2 dअगरferent
	 * रेजिस्टर addresses and IRQ numbers क्रम inbox and outbox.
	 *
	 * If necessary, a supplementary inbox could be enabled optionally
	 * with an independent FIFO and an extra पूर्णांकerrupt.
	 */
	priv->inbox_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->inbox_base))
		वापस PTR_ERR(priv->inbox_base);

	priv->outbox_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(priv->outbox_base))
		वापस PTR_ERR(priv->outbox_base);

	priv->clk = devm_clk_get(dev, "enable");
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to get mailbox clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, sprd_mbox_disable, priv);
	अगर (ret) अणु
		dev_err(dev, "failed to add mailbox disable action\n");
		वापस ret;
	पूर्ण

	inbox_irq = platक्रमm_get_irq_byname(pdev, "inbox");
	अगर (inbox_irq < 0)
		वापस inbox_irq;

	ret = devm_request_irq(dev, inbox_irq, sprd_mbox_inbox_isr,
			       IRQF_NO_SUSPEND, dev_name(dev), priv);
	अगर (ret) अणु
		dev_err(dev, "failed to request inbox IRQ: %d\n", ret);
		वापस ret;
	पूर्ण

	outbox_irq = platक्रमm_get_irq_byname(pdev, "outbox");
	अगर (outbox_irq < 0)
		वापस outbox_irq;

	ret = devm_request_irq(dev, outbox_irq, sprd_mbox_outbox_isr,
			       IRQF_NO_SUSPEND, dev_name(dev), priv);
	अगर (ret) अणु
		dev_err(dev, "failed to request outbox IRQ: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Supplementary outbox IRQ is optional */
	supp_irq = platक्रमm_get_irq_byname(pdev, "supp-outbox");
	अगर (supp_irq > 0) अणु
		ret = devm_request_irq(dev, supp_irq, sprd_mbox_supp_isr,
				       IRQF_NO_SUSPEND, dev_name(dev), priv);
		अगर (ret) अणु
			dev_err(dev, "failed to request outbox IRQ: %d\n", ret);
			वापस ret;
		पूर्ण

		supp = (अचिन्हित दीर्घ) of_device_get_match_data(dev);
		अगर (!supp) अणु
			dev_err(dev, "no supplementary outbox specified\n");
			वापस -ENODEV;
		पूर्ण
		priv->supp_base = priv->outbox_base + (SPRD_OUTBOX_BASE_SPAN * supp);
	पूर्ण

	/* Get the शेष outbox FIFO depth */
	priv->outbox_fअगरo_depth =
		पढ़ोl(priv->outbox_base + SPRD_MBOX_FIFO_DEPTH) + 1;
	priv->mbox.dev = dev;
	priv->mbox.chans = &priv->chan[0];
	priv->mbox.num_chans = SPRD_MBOX_CHAN_MAX;
	priv->mbox.ops = &sprd_mbox_ops;
	priv->mbox.txकरोne_irq = true;

	क्रम (id = 0; id < SPRD_MBOX_CHAN_MAX; id++)
		priv->chan[id].con_priv = (व्योम *)id;

	ret = devm_mbox_controller_रेजिस्टर(dev, &priv->mbox);
	अगर (ret) अणु
		dev_err(dev, "failed to register mailbox: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_mbox_of_match[] = अणु
	अणु .compatible = "sprd,sc9860-mailbox" पूर्ण,
	अणु .compatible = "sprd,sc9863a-mailbox",
	  .data = (व्योम *)SPRD_SUPP_INBOX_ID_SC9863A पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_mbox_of_match);

अटल काष्ठा platक्रमm_driver sprd_mbox_driver = अणु
	.driver = अणु
		.name = "sprd-mailbox",
		.of_match_table = sprd_mbox_of_match,
	पूर्ण,
	.probe	= sprd_mbox_probe,
पूर्ण;
module_platक्रमm_driver(sprd_mbox_driver);

MODULE_AUTHOR("Baolin Wang <baolin.wang@unisoc.com>");
MODULE_DESCRIPTION("Spreadtrum mailbox driver");
MODULE_LICENSE("GPL v2");
