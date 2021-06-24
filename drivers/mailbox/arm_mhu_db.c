<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013-2015 Fujitsu Semiconductor Ltd.
 * Copyright (C) 2015 Linaro Ltd.
 * Based on ARM MHU driver by Jassi Brar <jaswinder.singh@linaro.org>
 * Copyright (C) 2020 ARM Ltd.
 */

#समावेश <linux/amba/bus.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#घोषणा INTR_STAT_OFS	0x0
#घोषणा INTR_SET_OFS	0x8
#घोषणा INTR_CLR_OFS	0x10

#घोषणा MHU_LP_OFFSET	0x0
#घोषणा MHU_HP_OFFSET	0x20
#घोषणा MHU_SEC_OFFSET	0x200
#घोषणा TX_REG_OFFSET	0x100

#घोषणा MHU_CHANS	3	/* Secure, Non-Secure High and Low Priority */
#घोषणा MHU_CHAN_MAX	20	/* Max channels to save on unused RAM */
#घोषणा MHU_NUM_DOORBELLS	32

काष्ठा mhu_db_link अणु
	अचिन्हित पूर्णांक irq;
	व्योम __iomem *tx_reg;
	व्योम __iomem *rx_reg;
पूर्ण;

काष्ठा arm_mhu अणु
	व्योम __iomem *base;
	काष्ठा mhu_db_link mlink[MHU_CHANS];
	काष्ठा mbox_controller mbox;
	काष्ठा device *dev;
पूर्ण;

/**
 * ARM MHU Mailbox allocated channel inक्रमmation
 *
 * @mhu: Poपूर्णांकer to parent mailbox device
 * @pchan: Physical channel within which this करोorbell resides in
 * @करोorbell: करोorbell number pertaining to this channel
 */
काष्ठा mhu_db_channel अणु
	काष्ठा arm_mhu *mhu;
	अचिन्हित पूर्णांक pchan;
	अचिन्हित पूर्णांक करोorbell;
पूर्ण;

अटल अंतरभूत काष्ठा mbox_chan *
mhu_db_mbox_to_channel(काष्ठा mbox_controller *mbox, अचिन्हित पूर्णांक pchan,
		       अचिन्हित पूर्णांक करोorbell)
अणु
	पूर्णांक i;
	काष्ठा mhu_db_channel *chan_info;

	क्रम (i = 0; i < mbox->num_chans; i++) अणु
		chan_info = mbox->chans[i].con_priv;
		अगर (chan_info && chan_info->pchan == pchan &&
		    chan_info->करोorbell == करोorbell)
			वापस &mbox->chans[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम mhu_db_mbox_clear_irq(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhu_db_channel *chan_info = chan->con_priv;
	व्योम __iomem *base = chan_info->mhu->mlink[chan_info->pchan].rx_reg;

	ग_लिखोl_relaxed(BIT(chan_info->करोorbell), base + INTR_CLR_OFS);
पूर्ण

अटल अचिन्हित पूर्णांक mhu_db_mbox_irq_to_pchan_num(काष्ठा arm_mhu *mhu, पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक pchan;

	क्रम (pchan = 0; pchan < MHU_CHANS; pchan++)
		अगर (mhu->mlink[pchan].irq == irq)
			अवरोध;
	वापस pchan;
पूर्ण

अटल काष्ठा mbox_chan *
mhu_db_mbox_irq_to_channel(काष्ठा arm_mhu *mhu, अचिन्हित पूर्णांक pchan)
अणु
	अचिन्हित दीर्घ bits;
	अचिन्हित पूर्णांक करोorbell;
	काष्ठा mbox_chan *chan = शून्य;
	काष्ठा mbox_controller *mbox = &mhu->mbox;
	व्योम __iomem *base = mhu->mlink[pchan].rx_reg;

	bits = पढ़ोl_relaxed(base + INTR_STAT_OFS);
	अगर (!bits)
		/* No IRQs fired in specअगरied physical channel */
		वापस शून्य;

	/* An IRQ has fired, find the associated channel */
	क्रम (करोorbell = 0; bits; करोorbell++) अणु
		अगर (!test_and_clear_bit(करोorbell, &bits))
			जारी;

		chan = mhu_db_mbox_to_channel(mbox, pchan, करोorbell);
		अगर (chan)
			अवरोध;
		dev_err(mbox->dev,
			"Channel not registered: pchan: %d doorbell: %d\n",
			pchan, करोorbell);
	पूर्ण

	वापस chan;
पूर्ण

अटल irqवापस_t mhu_db_mbox_rx_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mbox_chan *chan;
	काष्ठा arm_mhu *mhu = data;
	अचिन्हित पूर्णांक pchan = mhu_db_mbox_irq_to_pchan_num(mhu, irq);

	जबतक (शून्य != (chan = mhu_db_mbox_irq_to_channel(mhu, pchan))) अणु
		mbox_chan_received_data(chan, शून्य);
		mhu_db_mbox_clear_irq(chan);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल bool mhu_db_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhu_db_channel *chan_info = chan->con_priv;
	व्योम __iomem *base = chan_info->mhu->mlink[chan_info->pchan].tx_reg;

	अगर (पढ़ोl_relaxed(base + INTR_STAT_OFS) & BIT(chan_info->करोorbell))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक mhu_db_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा mhu_db_channel *chan_info = chan->con_priv;
	व्योम __iomem *base = chan_info->mhu->mlink[chan_info->pchan].tx_reg;

	/* Send event to co-processor */
	ग_लिखोl_relaxed(BIT(chan_info->करोorbell), base + INTR_SET_OFS);

	वापस 0;
पूर्ण

अटल पूर्णांक mhu_db_startup(काष्ठा mbox_chan *chan)
अणु
	mhu_db_mbox_clear_irq(chan);
	वापस 0;
पूर्ण

अटल व्योम mhu_db_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा mhu_db_channel *chan_info = chan->con_priv;
	काष्ठा mbox_controller *mbox = &chan_info->mhu->mbox;
	पूर्णांक i;

	क्रम (i = 0; i < mbox->num_chans; i++)
		अगर (chan == &mbox->chans[i])
			अवरोध;

	अगर (mbox->num_chans == i) अणु
		dev_warn(mbox->dev, "Request to free non-existent channel\n");
		वापस;
	पूर्ण

	/* Reset channel */
	mhu_db_mbox_clear_irq(chan);
	devm_kमुक्त(mbox->dev, chan->con_priv);
	chan->con_priv = शून्य;
पूर्ण

अटल काष्ठा mbox_chan *mhu_db_mbox_xlate(काष्ठा mbox_controller *mbox,
					   स्थिर काष्ठा of_phandle_args *spec)
अणु
	काष्ठा arm_mhu *mhu = dev_get_drvdata(mbox->dev);
	काष्ठा mhu_db_channel *chan_info;
	काष्ठा mbox_chan *chan;
	अचिन्हित पूर्णांक pchan = spec->args[0];
	अचिन्हित पूर्णांक करोorbell = spec->args[1];
	पूर्णांक i;

	/* Bounds checking */
	अगर (pchan >= MHU_CHANS || करोorbell >= MHU_NUM_DOORBELLS) अणु
		dev_err(mbox->dev,
			"Invalid channel requested pchan: %d doorbell: %d\n",
			pchan, करोorbell);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Is requested channel मुक्त? */
	chan = mhu_db_mbox_to_channel(mbox, pchan, करोorbell);
	अगर (chan) अणु
		dev_err(mbox->dev, "Channel in use: pchan: %d doorbell: %d\n",
			pchan, करोorbell);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	/* Find the first मुक्त slot */
	क्रम (i = 0; i < mbox->num_chans; i++)
		अगर (!mbox->chans[i].con_priv)
			अवरोध;

	अगर (mbox->num_chans == i) अणु
		dev_err(mbox->dev, "No free channels left\n");
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	chan = &mbox->chans[i];

	chan_info = devm_kzalloc(mbox->dev, माप(*chan_info), GFP_KERNEL);
	अगर (!chan_info)
		वापस ERR_PTR(-ENOMEM);

	chan_info->mhu = mhu;
	chan_info->pchan = pchan;
	chan_info->करोorbell = करोorbell;

	chan->con_priv = chan_info;

	dev_dbg(mbox->dev, "mbox: created channel phys: %d doorbell: %d\n",
		pchan, करोorbell);

	वापस chan;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops mhu_db_ops = अणु
	.send_data = mhu_db_send_data,
	.startup = mhu_db_startup,
	.shutकरोwn = mhu_db_shutकरोwn,
	.last_tx_करोne = mhu_db_last_tx_करोne,
पूर्ण;

अटल पूर्णांक mhu_db_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	u32 cell_count;
	पूर्णांक i, err, max_chans;
	काष्ठा arm_mhu *mhu;
	काष्ठा mbox_chan *chans;
	काष्ठा device *dev = &adev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक mhu_reg[MHU_CHANS] = अणु
		MHU_LP_OFFSET, MHU_HP_OFFSET, MHU_SEC_OFFSET,
	पूर्ण;

	अगर (!of_device_is_compatible(np, "arm,mhu-doorbell"))
		वापस -ENODEV;

	err = of_property_पढ़ो_u32(np, "#mbox-cells", &cell_count);
	अगर (err) अणु
		dev_err(dev, "failed to read #mbox-cells in '%pOF'\n", np);
		वापस err;
	पूर्ण

	अगर (cell_count == 2) अणु
		max_chans = MHU_CHAN_MAX;
	पूर्ण अन्यथा अणु
		dev_err(dev, "incorrect value of #mbox-cells in '%pOF'\n", np);
		वापस -EINVAL;
	पूर्ण

	mhu = devm_kzalloc(dev, माप(*mhu), GFP_KERNEL);
	अगर (!mhu)
		वापस -ENOMEM;

	mhu->base = devm_ioremap_resource(dev, &adev->res);
	अगर (IS_ERR(mhu->base))
		वापस PTR_ERR(mhu->base);

	chans = devm_kसुस्मृति(dev, max_chans, माप(*chans), GFP_KERNEL);
	अगर (!chans)
		वापस -ENOMEM;

	mhu->dev = dev;
	mhu->mbox.dev = dev;
	mhu->mbox.chans = chans;
	mhu->mbox.num_chans = max_chans;
	mhu->mbox.txकरोne_irq = false;
	mhu->mbox.txकरोne_poll = true;
	mhu->mbox.txpoll_period = 1;

	mhu->mbox.of_xlate = mhu_db_mbox_xlate;
	amba_set_drvdata(adev, mhu);

	mhu->mbox.ops = &mhu_db_ops;

	err = devm_mbox_controller_रेजिस्टर(dev, &mhu->mbox);
	अगर (err) अणु
		dev_err(dev, "Failed to register mailboxes %d\n", err);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < MHU_CHANS; i++) अणु
		पूर्णांक irq = mhu->mlink[i].irq = adev->irq[i];

		अगर (irq <= 0) अणु
			dev_dbg(dev, "No IRQ found for Channel %d\n", i);
			जारी;
		पूर्ण

		mhu->mlink[i].rx_reg = mhu->base + mhu_reg[i];
		mhu->mlink[i].tx_reg = mhu->mlink[i].rx_reg + TX_REG_OFFSET;

		err = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
						mhu_db_mbox_rx_handler,
						IRQF_ONESHOT, "mhu_db_link", mhu);
		अगर (err) अणु
			dev_err(dev, "Can't claim IRQ %d\n", irq);
			mbox_controller_unरेजिस्टर(&mhu->mbox);
			वापस err;
		पूर्ण
	पूर्ण

	dev_info(dev, "ARM MHU Doorbell mailbox registered\n");
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

अटल काष्ठा amba_driver arm_mhu_db_driver = अणु
	.drv = अणु
		.name	= "mhu-doorbell",
	पूर्ण,
	.id_table	= mhu_ids,
	.probe		= mhu_db_probe,
पूर्ण;
module_amba_driver(arm_mhu_db_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ARM MHU Doorbell Driver");
MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
