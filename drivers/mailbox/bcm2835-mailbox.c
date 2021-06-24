<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2010,2015 Broadcom
 *  Copyright (C) 2013-2014 Lubomir Rपूर्णांकel
 *  Copyright (C) 2013 Craig McGeachie
 *
 * Parts of the driver are based on:
 *  - arch/arm/mach-bcm2708/vcio.c file written by Gray Girling that was
 *    obtained from branch "rpi-3.6.y" of git://github.com/raspberrypi/
 *    linux.git
 *  - drivers/mailbox/bcm2835-ipc.c by Lubomir Rपूर्णांकel at
 *    https://github.com/hackerspace/rpi-linux/blob/lr-raspberry-pi/drivers/
 *    mailbox/bcm2835-ipc.c
 *  - करोcumentation available on the following web site:
 *    https://github.com/raspberrypi/firmware/wiki/Mailbox-property-पूर्णांकerface
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

/* Mailboxes */
#घोषणा ARM_0_MAIL0	0x00
#घोषणा ARM_0_MAIL1	0x20

/*
 * Mailbox रेजिस्टरs. We basically only support mailbox 0 & 1. We
 * deliver to the VC in mailbox 1, it delivers to us in mailbox 0. See
 * BCM2835-ARM-Peripherals.pdf section 1.3 क्रम an explanation about
 * the placement of memory barriers.
 */
#घोषणा MAIL0_RD	(ARM_0_MAIL0 + 0x00)
#घोषणा MAIL0_POL	(ARM_0_MAIL0 + 0x10)
#घोषणा MAIL0_STA	(ARM_0_MAIL0 + 0x18)
#घोषणा MAIL0_CNF	(ARM_0_MAIL0 + 0x1C)
#घोषणा MAIL1_WRT	(ARM_0_MAIL1 + 0x00)
#घोषणा MAIL1_STA	(ARM_0_MAIL1 + 0x18)

/* Status रेजिस्टर: FIFO state. */
#घोषणा ARM_MS_FULL		BIT(31)
#घोषणा ARM_MS_EMPTY		BIT(30)

/* Configuration रेजिस्टर: Enable पूर्णांकerrupts. */
#घोषणा ARM_MC_IHAVEDATAIRQEN	BIT(0)

काष्ठा bcm2835_mbox अणु
	व्योम __iomem *regs;
	spinlock_t lock;
	काष्ठा mbox_controller controller;
पूर्ण;

अटल काष्ठा bcm2835_mbox *bcm2835_link_mbox(काष्ठा mbox_chan *link)
अणु
	वापस container_of(link->mbox, काष्ठा bcm2835_mbox, controller);
पूर्ण

अटल irqवापस_t bcm2835_mbox_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm2835_mbox *mbox = dev_id;
	काष्ठा device *dev = mbox->controller.dev;
	काष्ठा mbox_chan *link = &mbox->controller.chans[0];

	जबतक (!(पढ़ोl(mbox->regs + MAIL0_STA) & ARM_MS_EMPTY)) अणु
		u32 msg = पढ़ोl(mbox->regs + MAIL0_RD);
		dev_dbg(dev, "Reply 0x%08X\n", msg);
		mbox_chan_received_data(link, &msg);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm2835_send_data(काष्ठा mbox_chan *link, व्योम *data)
अणु
	काष्ठा bcm2835_mbox *mbox = bcm2835_link_mbox(link);
	u32 msg = *(u32 *)data;

	spin_lock(&mbox->lock);
	ग_लिखोl(msg, mbox->regs + MAIL1_WRT);
	dev_dbg(mbox->controller.dev, "Request 0x%08X\n", msg);
	spin_unlock(&mbox->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_startup(काष्ठा mbox_chan *link)
अणु
	काष्ठा bcm2835_mbox *mbox = bcm2835_link_mbox(link);

	/* Enable the पूर्णांकerrupt on data reception */
	ग_लिखोl(ARM_MC_IHAVEDATAIRQEN, mbox->regs + MAIL0_CNF);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_shutकरोwn(काष्ठा mbox_chan *link)
अणु
	काष्ठा bcm2835_mbox *mbox = bcm2835_link_mbox(link);

	ग_लिखोl(0, mbox->regs + MAIL0_CNF);
पूर्ण

अटल bool bcm2835_last_tx_करोne(काष्ठा mbox_chan *link)
अणु
	काष्ठा bcm2835_mbox *mbox = bcm2835_link_mbox(link);
	bool ret;

	spin_lock(&mbox->lock);
	ret = !(पढ़ोl(mbox->regs + MAIL1_STA) & ARM_MS_FULL);
	spin_unlock(&mbox->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mbox_chan_ops bcm2835_mbox_chan_ops = अणु
	.send_data	= bcm2835_send_data,
	.startup	= bcm2835_startup,
	.shutकरोwn	= bcm2835_shutकरोwn,
	.last_tx_करोne	= bcm2835_last_tx_करोne
पूर्ण;

अटल काष्ठा mbox_chan *bcm2835_mbox_index_xlate(काष्ठा mbox_controller *mbox,
		    स्थिर काष्ठा of_phandle_args *sp)
अणु
	अगर (sp->args_count != 0)
		वापस ERR_PTR(-EINVAL);

	वापस &mbox->chans[0];
पूर्ण

अटल पूर्णांक bcm2835_mbox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret = 0;
	काष्ठा resource *iomem;
	काष्ठा bcm2835_mbox *mbox;

	mbox = devm_kzalloc(dev, माप(*mbox), GFP_KERNEL);
	अगर (mbox == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&mbox->lock);

	ret = devm_request_irq(dev, irq_of_parse_and_map(dev->of_node, 0),
			       bcm2835_mbox_irq, 0, dev_name(dev), mbox);
	अगर (ret) अणु
		dev_err(dev, "Failed to register a mailbox IRQ handler: %d\n",
			ret);
		वापस -ENODEV;
	पूर्ण

	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mbox->regs = devm_ioremap_resource(&pdev->dev, iomem);
	अगर (IS_ERR(mbox->regs)) अणु
		ret = PTR_ERR(mbox->regs);
		dev_err(&pdev->dev, "Failed to remap mailbox regs: %d\n", ret);
		वापस ret;
	पूर्ण

	mbox->controller.txकरोne_poll = true;
	mbox->controller.txpoll_period = 5;
	mbox->controller.ops = &bcm2835_mbox_chan_ops;
	mbox->controller.of_xlate = &bcm2835_mbox_index_xlate;
	mbox->controller.dev = dev;
	mbox->controller.num_chans = 1;
	mbox->controller.chans = devm_kzalloc(dev,
		माप(*mbox->controller.chans), GFP_KERNEL);
	अगर (!mbox->controller.chans)
		वापस -ENOMEM;

	ret = devm_mbox_controller_रेजिस्टर(dev, &mbox->controller);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, mbox);
	dev_info(dev, "mailbox enabled\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835_mbox_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-mbox", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_mbox_of_match);

अटल काष्ठा platक्रमm_driver bcm2835_mbox_driver = अणु
	.driver = अणु
		.name = "bcm2835-mbox",
		.of_match_table = bcm2835_mbox_of_match,
	पूर्ण,
	.probe		= bcm2835_mbox_probe,
पूर्ण;
module_platक्रमm_driver(bcm2835_mbox_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("BCM2835 mailbox IPC driver");
MODULE_LICENSE("GPL v2");
