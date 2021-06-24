<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * APM X-Gene SLIMpro MailBox Driver
 *
 * Copyright (c) 2015, Applied Micro Circuits Corporation
 * Author: Feng Kan fkan@apm.com
 */
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा MBOX_CON_NAME			"slimpro-mbox"
#घोषणा MBOX_REG_SET_OFFSET		0x1000
#घोषणा MBOX_CNT			8
#घोषणा MBOX_STATUS_AVAIL_MASK		BIT(16)
#घोषणा MBOX_STATUS_ACK_MASK		BIT(0)

/* Configuration and Status Registers */
#घोषणा REG_DB_IN		0x00
#घोषणा REG_DB_DIN0		0x04
#घोषणा REG_DB_DIN1		0x08
#घोषणा REG_DB_OUT		0x10
#घोषणा REG_DB_DOUT0		0x14
#घोषणा REG_DB_DOUT1		0x18
#घोषणा REG_DB_STAT		0x20
#घोषणा REG_DB_STATMASK		0x24

/**
 * X-Gene SlimPRO mailbox channel inक्रमmation
 *
 * @dev:	Device to which it is attached
 * @chan:	Poपूर्णांकer to mailbox communication channel
 * @reg:	Base address to access channel रेजिस्टरs
 * @irq:	Interrupt number of the channel
 * @rx_msg:	Received message storage
 */
काष्ठा slimpro_mbox_chan अणु
	काष्ठा device		*dev;
	काष्ठा mbox_chan	*chan;
	व्योम __iomem		*reg;
	पूर्णांक			irq;
	u32			rx_msg[3];
पूर्ण;

/**
 * X-Gene SlimPRO Mailbox controller data
 *
 * X-Gene SlimPRO Mailbox controller has 8 communication channels.
 * Each channel has a separate IRQ number asचिन्हित to it.
 *
 * @mb_ctrl:	Representation of the communication channel controller
 * @mc:		Array of SlimPRO mailbox channels of the controller
 * @chans:	Array of mailbox communication channels
 *
 */
काष्ठा slimpro_mbox अणु
	काष्ठा mbox_controller		mb_ctrl;
	काष्ठा slimpro_mbox_chan	mc[MBOX_CNT];
	काष्ठा mbox_chan		chans[MBOX_CNT];
पूर्ण;

अटल व्योम mb_chan_send_msg(काष्ठा slimpro_mbox_chan *mb_chan, u32 *msg)
अणु
	ग_लिखोl(msg[1], mb_chan->reg + REG_DB_DOUT0);
	ग_लिखोl(msg[2], mb_chan->reg + REG_DB_DOUT1);
	ग_लिखोl(msg[0], mb_chan->reg + REG_DB_OUT);
पूर्ण

अटल व्योम mb_chan_recv_msg(काष्ठा slimpro_mbox_chan *mb_chan)
अणु
	mb_chan->rx_msg[1] = पढ़ोl(mb_chan->reg + REG_DB_DIN0);
	mb_chan->rx_msg[2] = पढ़ोl(mb_chan->reg + REG_DB_DIN1);
	mb_chan->rx_msg[0] = पढ़ोl(mb_chan->reg + REG_DB_IN);
पूर्ण

अटल पूर्णांक mb_chan_status_ack(काष्ठा slimpro_mbox_chan *mb_chan)
अणु
	u32 val = पढ़ोl(mb_chan->reg + REG_DB_STAT);

	अगर (val & MBOX_STATUS_ACK_MASK) अणु
		ग_लिखोl(MBOX_STATUS_ACK_MASK, mb_chan->reg + REG_DB_STAT);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mb_chan_status_avail(काष्ठा slimpro_mbox_chan *mb_chan)
अणु
	u32 val = पढ़ोl(mb_chan->reg + REG_DB_STAT);

	अगर (val & MBOX_STATUS_AVAIL_MASK) अणु
		mb_chan_recv_msg(mb_chan);
		ग_लिखोl(MBOX_STATUS_AVAIL_MASK, mb_chan->reg + REG_DB_STAT);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t slimpro_mbox_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा slimpro_mbox_chan *mb_chan = id;

	अगर (mb_chan_status_ack(mb_chan))
		mbox_chan_txकरोne(mb_chan->chan, 0);

	अगर (mb_chan_status_avail(mb_chan))
		mbox_chan_received_data(mb_chan->chan, mb_chan->rx_msg);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक slimpro_mbox_send_data(काष्ठा mbox_chan *chan, व्योम *msg)
अणु
	काष्ठा slimpro_mbox_chan *mb_chan = chan->con_priv;

	mb_chan_send_msg(mb_chan, msg);
	वापस 0;
पूर्ण

अटल पूर्णांक slimpro_mbox_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा slimpro_mbox_chan *mb_chan = chan->con_priv;
	पूर्णांक rc;
	u32 val;

	rc = devm_request_irq(mb_chan->dev, mb_chan->irq, slimpro_mbox_irq, 0,
			      MBOX_CON_NAME, mb_chan);
	अगर (unlikely(rc)) अणु
		dev_err(mb_chan->dev, "failed to register mailbox interrupt %d\n",
			mb_chan->irq);
		वापस rc;
	पूर्ण

	/* Enable HW पूर्णांकerrupt */
	ग_लिखोl(MBOX_STATUS_ACK_MASK | MBOX_STATUS_AVAIL_MASK,
	       mb_chan->reg + REG_DB_STAT);
	/* Unmask करोorbell status पूर्णांकerrupt */
	val = पढ़ोl(mb_chan->reg + REG_DB_STATMASK);
	val &= ~(MBOX_STATUS_ACK_MASK | MBOX_STATUS_AVAIL_MASK);
	ग_लिखोl(val, mb_chan->reg + REG_DB_STATMASK);

	वापस 0;
पूर्ण

अटल व्योम slimpro_mbox_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा slimpro_mbox_chan *mb_chan = chan->con_priv;
	u32 val;

	/* Mask करोorbell status पूर्णांकerrupt */
	val = पढ़ोl(mb_chan->reg + REG_DB_STATMASK);
	val |= (MBOX_STATUS_ACK_MASK | MBOX_STATUS_AVAIL_MASK);
	ग_लिखोl(val, mb_chan->reg + REG_DB_STATMASK);

	devm_मुक्त_irq(mb_chan->dev, mb_chan->irq, mb_chan);
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops slimpro_mbox_ops = अणु
	.send_data = slimpro_mbox_send_data,
	.startup = slimpro_mbox_startup,
	.shutकरोwn = slimpro_mbox_shutकरोwn,
पूर्ण;

अटल पूर्णांक slimpro_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा slimpro_mbox *ctx;
	काष्ठा resource *regs;
	व्योम __iomem *mb_base;
	पूर्णांक rc;
	पूर्णांक i;

	ctx = devm_kzalloc(&pdev->dev, माप(काष्ठा slimpro_mbox), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ctx);

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mb_base = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(mb_base))
		वापस PTR_ERR(mb_base);

	/* Setup mailbox links */
	क्रम (i = 0; i < MBOX_CNT; i++) अणु
		ctx->mc[i].irq = platक्रमm_get_irq(pdev, i);
		अगर (ctx->mc[i].irq < 0) अणु
			अगर (i == 0) अणु
				dev_err(&pdev->dev, "no available IRQ\n");
				वापस -EINVAL;
			पूर्ण
			dev_info(&pdev->dev, "no IRQ for channel %d\n", i);
			अवरोध;
		पूर्ण

		ctx->mc[i].dev = &pdev->dev;
		ctx->mc[i].reg = mb_base + i * MBOX_REG_SET_OFFSET;
		ctx->mc[i].chan = &ctx->chans[i];
		ctx->chans[i].con_priv = &ctx->mc[i];
	पूर्ण

	/* Setup mailbox controller */
	ctx->mb_ctrl.dev = &pdev->dev;
	ctx->mb_ctrl.chans = ctx->chans;
	ctx->mb_ctrl.txकरोne_irq = true;
	ctx->mb_ctrl.ops = &slimpro_mbox_ops;
	ctx->mb_ctrl.num_chans = i;

	rc = devm_mbox_controller_रेजिस्टर(&pdev->dev, &ctx->mb_ctrl);
	अगर (rc) अणु
		dev_err(&pdev->dev,
			"APM X-Gene SLIMpro MailBox register failed:%d\n", rc);
		वापस rc;
	पूर्ण

	dev_info(&pdev->dev, "APM X-Gene SLIMpro MailBox registered\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id slimpro_of_match[] = अणु
	अणु.compatible = "apm,xgene-slimpro-mbox" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, slimpro_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id slimpro_acpi_ids[] = अणु
	अणु"APMC0D01", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, slimpro_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver slimpro_mbox_driver = अणु
	.probe	= slimpro_mbox_probe,
	.driver	= अणु
		.name = "xgene-slimpro-mbox",
		.of_match_table = of_match_ptr(slimpro_of_match),
		.acpi_match_table = ACPI_PTR(slimpro_acpi_ids)
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init slimpro_mbox_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&slimpro_mbox_driver);
पूर्ण

अटल व्योम __निकास slimpro_mbox_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&slimpro_mbox_driver);
पूर्ण

subsys_initcall(slimpro_mbox_init);
module_निकास(slimpro_mbox_निकास);

MODULE_DESCRIPTION("APM X-Gene SLIMpro Mailbox Driver");
MODULE_LICENSE("GPL");
