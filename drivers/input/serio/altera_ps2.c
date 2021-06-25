<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Altera University Program PS2 controller driver
 *
 * Copyright (C) 2008 Thomas Chou <thomas@wytron.com.tw>
 *
 * Based on sa1111ps2.c, which is:
 * Copyright (C) 2002 Russell King
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#घोषणा DRV_NAME "altera_ps2"

काष्ठा ps2अगर अणु
	काष्ठा serio *io;
	व्योम __iomem *base;
पूर्ण;

/*
 * Read all bytes रुकोing in the PS2 port.  There should be
 * at the most one, but we loop क्रम safety.
 */
अटल irqवापस_t altera_ps2_rxपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ps2अगर *ps2अगर = dev_id;
	अचिन्हित पूर्णांक status;
	irqवापस_t handled = IRQ_NONE;

	जबतक ((status = पढ़ोl(ps2अगर->base)) & 0xffff0000) अणु
		serio_पूर्णांकerrupt(ps2अगर->io, status & 0xff, 0);
		handled = IRQ_HANDLED;
	पूर्ण

	वापस handled;
पूर्ण

/*
 * Write a byte to the PS2 port.
 */
अटल पूर्णांक altera_ps2_ग_लिखो(काष्ठा serio *io, अचिन्हित अक्षर val)
अणु
	काष्ठा ps2अगर *ps2अगर = io->port_data;

	ग_लिखोl(val, ps2अगर->base);
	वापस 0;
पूर्ण

अटल पूर्णांक altera_ps2_खोलो(काष्ठा serio *io)
अणु
	काष्ठा ps2अगर *ps2अगर = io->port_data;

	/* clear fअगरo */
	जबतक (पढ़ोl(ps2अगर->base) & 0xffff0000)
		/* empty */;

	ग_लिखोl(1, ps2अगर->base + 4); /* enable rx irq */
	वापस 0;
पूर्ण

अटल व्योम altera_ps2_बंद(काष्ठा serio *io)
अणु
	काष्ठा ps2अगर *ps2अगर = io->port_data;

	ग_लिखोl(0, ps2अगर->base + 4); /* disable rx irq */
पूर्ण

/*
 * Add one device to this driver.
 */
अटल पूर्णांक altera_ps2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ps2अगर *ps2अगर;
	काष्ठा resource *res;
	काष्ठा serio *serio;
	पूर्णांक error, irq;

	ps2अगर = devm_kzalloc(&pdev->dev, माप(काष्ठा ps2अगर), GFP_KERNEL);
	अगर (!ps2अगर)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ps2अगर->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ps2अगर->base))
		वापस PTR_ERR(ps2अगर->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	error = devm_request_irq(&pdev->dev, irq, altera_ps2_rxपूर्णांक, 0,
				 pdev->name, ps2अगर);
	अगर (error) अणु
		dev_err(&pdev->dev, "could not request IRQ %d\n", irq);
		वापस error;
	पूर्ण

	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!serio)
		वापस -ENOMEM;

	serio->id.type		= SERIO_8042;
	serio->ग_लिखो		= altera_ps2_ग_लिखो;
	serio->खोलो		= altera_ps2_खोलो;
	serio->बंद		= altera_ps2_बंद;
	strlcpy(serio->name, dev_name(&pdev->dev), माप(serio->name));
	strlcpy(serio->phys, dev_name(&pdev->dev), माप(serio->phys));
	serio->port_data	= ps2अगर;
	serio->dev.parent	= &pdev->dev;
	ps2अगर->io		= serio;

	dev_info(&pdev->dev, "base %p, irq %d\n", ps2अगर->base, irq);

	serio_रेजिस्टर_port(ps2अगर->io);
	platक्रमm_set_drvdata(pdev, ps2अगर);

	वापस 0;
पूर्ण

/*
 * Remove one device from this driver.
 */
अटल पूर्णांक altera_ps2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ps2अगर *ps2अगर = platक्रमm_get_drvdata(pdev);

	serio_unरेजिस्टर_port(ps2अगर->io);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id altera_ps2_match[] = अणु
	अणु .compatible = "ALTR,ps2-1.0", पूर्ण,
	अणु .compatible = "altr,ps2-1.0", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altera_ps2_match);
#पूर्ण_अगर /* CONFIG_OF */

/*
 * Our device driver काष्ठाure
 */
अटल काष्ठा platक्रमm_driver altera_ps2_driver = अणु
	.probe		= altera_ps2_probe,
	.हटाओ		= altera_ps2_हटाओ,
	.driver	= अणु
		.name	= DRV_NAME,
		.of_match_table = of_match_ptr(altera_ps2_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(altera_ps2_driver);

MODULE_DESCRIPTION("Altera University Program PS2 controller driver");
MODULE_AUTHOR("Thomas Chou <thomas@wytron.com.tw>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
