<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OLPC serio driver क्रम multiplexed input from Marvell MMP security processor
 *
 * Copyright (C) 2011-2013 One Laptop Per Child
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/serपन.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

/*
 * The OLPC XO-1.75 and XO-4 laptops करो not have a hardware PS/2 controller.
 * Instead, the OLPC firmware runs a bit-banging PS/2 implementation on an
 * otherwise-unused slow processor which is included in the Marvell MMP2/MMP3
 * SoC, known as the "Security Processor" (SP) or "Wireless Trusted Module"
 * (WTM). This firmware then reports its results via the WTM रेजिस्टरs,
 * which we पढ़ो from the Application Processor (AP, i.e. मुख्य CPU) in this
 * driver.
 *
 * On the hardware side we have a PS/2 mouse and an AT keyboard, the data
 * is multiplexed through this प्रणाली. We create a serio port क्रम each one,
 * and demultiplex the data accordingly.
 */

/* WTM रेजिस्टर offsets */
#घोषणा SECURE_PROCESSOR_COMMAND	0x40
#घोषणा COMMAND_RETURN_STATUS		0x80
#घोषणा COMMAND_FIFO_STATUS		0xc4
#घोषणा PJ_RST_INTERRUPT		0xc8
#घोषणा PJ_INTERRUPT_MASK		0xcc

/*
 * The upper byte of SECURE_PROCESSOR_COMMAND and COMMAND_RETURN_STATUS is
 * used to identअगरy which port (device) is being talked to. The lower byte
 * is the data being sent/received.
 */
#घोषणा PORT_MASK	0xff00
#घोषणा DATA_MASK	0x00ff
#घोषणा PORT_SHIFT	8
#घोषणा KEYBOARD_PORT	0
#घोषणा TOUCHPAD_PORT	1

/* COMMAND_FIFO_STATUS */
#घोषणा CMD_CNTR_MASK		0x7 /* Number of pending/unprocessed commands */
#घोषणा MAX_PENDING_CMDS	4   /* from device specs */

/* PJ_RST_INTERRUPT */
#घोषणा SP_COMMAND_COMPLETE_RESET	0x1

/* PJ_INTERRUPT_MASK */
#घोषणा INT_0	(1 << 0)

/* COMMAND_FIFO_STATUS */
#घोषणा CMD_STS_MASK	0x100

काष्ठा olpc_apsp अणु
	काष्ठा device *dev;
	काष्ठा serio *kbio;
	काष्ठा serio *padio;
	व्योम __iomem *base;
	पूर्णांक खोलो_count;
	पूर्णांक irq;
पूर्ण;

अटल पूर्णांक olpc_apsp_ग_लिखो(काष्ठा serio *port, अचिन्हित अक्षर val)
अणु
	काष्ठा olpc_apsp *priv = port->port_data;
	अचिन्हित पूर्णांक i;
	u32 which = 0;

	अगर (port == priv->padio)
		which = TOUCHPAD_PORT << PORT_SHIFT;
	अन्यथा
		which = KEYBOARD_PORT << PORT_SHIFT;

	dev_dbg(priv->dev, "olpc_apsp_write which=%x val=%x\n", which, val);
	क्रम (i = 0; i < 50; i++) अणु
		u32 sts = पढ़ोl(priv->base + COMMAND_FIFO_STATUS);
		अगर ((sts & CMD_CNTR_MASK) < MAX_PENDING_CMDS) अणु
			ग_लिखोl(which | val,
			       priv->base + SECURE_PROCESSOR_COMMAND);
			वापस 0;
		पूर्ण
		/* SP busy. This has not been seen in practice. */
		mdelay(1);
	पूर्ण

	dev_dbg(priv->dev, "olpc_apsp_write timeout, status=%x\n",
		पढ़ोl(priv->base + COMMAND_FIFO_STATUS));

	वापस -ETIMEDOUT;
पूर्ण

अटल irqवापस_t olpc_apsp_rx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा olpc_apsp *priv = dev_id;
	अचिन्हित पूर्णांक w, पंचांगp;
	काष्ठा serio *serio;

	/*
	 * Write 1 to PJ_RST_INTERRUPT to acknowledge and clear the पूर्णांकerrupt
	 * Write 0xff00 to SECURE_PROCESSOR_COMMAND.
	 */
	पंचांगp = पढ़ोl(priv->base + PJ_RST_INTERRUPT);
	अगर (!(पंचांगp & SP_COMMAND_COMPLETE_RESET)) अणु
		dev_warn(priv->dev, "spurious interrupt?\n");
		वापस IRQ_NONE;
	पूर्ण

	w = पढ़ोl(priv->base + COMMAND_RETURN_STATUS);
	dev_dbg(priv->dev, "olpc_apsp_rx %x\n", w);

	अगर (w >> PORT_SHIFT == KEYBOARD_PORT)
		serio = priv->kbio;
	अन्यथा
		serio = priv->padio;

	serio_पूर्णांकerrupt(serio, w & DATA_MASK, 0);

	/* Ack and clear पूर्णांकerrupt */
	ग_लिखोl(पंचांगp | SP_COMMAND_COMPLETE_RESET, priv->base + PJ_RST_INTERRUPT);
	ग_लिखोl(PORT_MASK, priv->base + SECURE_PROCESSOR_COMMAND);

	pm_wakeup_event(priv->dev, 1000);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक olpc_apsp_खोलो(काष्ठा serio *port)
अणु
	काष्ठा olpc_apsp *priv = port->port_data;
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित दीर्घ l;

	अगर (priv->खोलो_count++ == 0) अणु
		l = पढ़ोl(priv->base + COMMAND_FIFO_STATUS);
		अगर (!(l & CMD_STS_MASK)) अणु
			dev_err(priv->dev, "SP cannot accept commands.\n");
			वापस -EIO;
		पूर्ण

		/* Enable पूर्णांकerrupt 0 by clearing its bit */
		पंचांगp = पढ़ोl(priv->base + PJ_INTERRUPT_MASK);
		ग_लिखोl(पंचांगp & ~INT_0, priv->base + PJ_INTERRUPT_MASK);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम olpc_apsp_बंद(काष्ठा serio *port)
अणु
	काष्ठा olpc_apsp *priv = port->port_data;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (--priv->खोलो_count == 0) अणु
		/* Disable पूर्णांकerrupt 0 */
		पंचांगp = पढ़ोl(priv->base + PJ_INTERRUPT_MASK);
		ग_लिखोl(पंचांगp | INT_0, priv->base + PJ_INTERRUPT_MASK);
	पूर्ण
पूर्ण

अटल पूर्णांक olpc_apsp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा serio *kb_serio, *pad_serio;
	काष्ठा olpc_apsp *priv;
	काष्ठा resource *res;
	पूर्णांक error;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा olpc_apsp), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->base)) अणु
		dev_err(&pdev->dev, "Failed to map WTM registers\n");
		वापस PTR_ERR(priv->base);
	पूर्ण

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq < 0)
		वापस priv->irq;

	/* KEYBOARD */
	kb_serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!kb_serio)
		वापस -ENOMEM;
	kb_serio->id.type	= SERIO_8042_XL;
	kb_serio->ग_लिखो		= olpc_apsp_ग_लिखो;
	kb_serio->खोलो		= olpc_apsp_खोलो;
	kb_serio->बंद		= olpc_apsp_बंद;
	kb_serio->port_data	= priv;
	kb_serio->dev.parent	= &pdev->dev;
	strlcpy(kb_serio->name, "sp keyboard", माप(kb_serio->name));
	strlcpy(kb_serio->phys, "sp/serio0", माप(kb_serio->phys));
	priv->kbio		= kb_serio;
	serio_रेजिस्टर_port(kb_serio);

	/* TOUCHPAD */
	pad_serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!pad_serio) अणु
		error = -ENOMEM;
		जाओ err_pad;
	पूर्ण
	pad_serio->id.type	= SERIO_8042;
	pad_serio->ग_लिखो	= olpc_apsp_ग_लिखो;
	pad_serio->खोलो		= olpc_apsp_खोलो;
	pad_serio->बंद	= olpc_apsp_बंद;
	pad_serio->port_data	= priv;
	pad_serio->dev.parent	= &pdev->dev;
	strlcpy(pad_serio->name, "sp touchpad", माप(pad_serio->name));
	strlcpy(pad_serio->phys, "sp/serio1", माप(pad_serio->phys));
	priv->padio		= pad_serio;
	serio_रेजिस्टर_port(pad_serio);

	error = request_irq(priv->irq, olpc_apsp_rx, 0, "olpc-apsp", priv);
	अगर (error) अणु
		dev_err(&pdev->dev, "Failed to request IRQ\n");
		जाओ err_irq;
	पूर्ण

	device_init_wakeup(priv->dev, 1);
	platक्रमm_set_drvdata(pdev, priv);

	dev_dbg(&pdev->dev, "probed successfully.\n");
	वापस 0;

err_irq:
	serio_unरेजिस्टर_port(pad_serio);
err_pad:
	serio_unरेजिस्टर_port(kb_serio);
	वापस error;
पूर्ण

अटल पूर्णांक olpc_apsp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा olpc_apsp *priv = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(priv->irq, priv);

	serio_unरेजिस्टर_port(priv->kbio);
	serio_unरेजिस्टर_port(priv->padio);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id olpc_apsp_dt_ids[] = अणु
	अणु .compatible = "olpc,ap-sp", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, olpc_apsp_dt_ids);

अटल काष्ठा platक्रमm_driver olpc_apsp_driver = अणु
	.probe		= olpc_apsp_probe,
	.हटाओ		= olpc_apsp_हटाओ,
	.driver		= अणु
		.name	= "olpc-apsp",
		.of_match_table = olpc_apsp_dt_ids,
	पूर्ण,
पूर्ण;

MODULE_DESCRIPTION("OLPC AP-SP serio driver");
MODULE_LICENSE("GPL");
module_platक्रमm_driver(olpc_apsp_driver);
