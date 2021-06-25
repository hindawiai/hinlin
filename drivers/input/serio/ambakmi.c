<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/input/serio/ambakmi.c
 *
 *  Copyright (C) 2000-2003 Deep Blue Solutions Ltd.
 *  Copyright (C) 2002 Russell King.
 */
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/amba/kmi.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#घोषणा KMI_BASE	(kmi->base)

काष्ठा amba_kmi_port अणु
	काष्ठा serio		*io;
	काष्ठा clk		*clk;
	व्योम __iomem		*base;
	अचिन्हित पूर्णांक		irq;
	अचिन्हित पूर्णांक		भागisor;
	अचिन्हित पूर्णांक		खोलो;
पूर्ण;

अटल irqवापस_t amba_kmi_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा amba_kmi_port *kmi = dev_id;
	अचिन्हित पूर्णांक status = पढ़ोb(KMIIR);
	पूर्णांक handled = IRQ_NONE;

	जबतक (status & KMIIR_RXINTR) अणु
		serio_पूर्णांकerrupt(kmi->io, पढ़ोb(KMIDATA), 0);
		status = पढ़ोb(KMIIR);
		handled = IRQ_HANDLED;
	पूर्ण

	वापस handled;
पूर्ण

अटल पूर्णांक amba_kmi_ग_लिखो(काष्ठा serio *io, अचिन्हित अक्षर val)
अणु
	काष्ठा amba_kmi_port *kmi = io->port_data;
	अचिन्हित पूर्णांक समयleft = 10000; /* समयout in 100ms */

	जबतक ((पढ़ोb(KMISTAT) & KMISTAT_TXEMPTY) == 0 && --समयleft)
		udelay(10);

	अगर (समयleft)
		ग_लिखोb(val, KMIDATA);

	वापस समयleft ? 0 : SERIO_TIMEOUT;
पूर्ण

अटल पूर्णांक amba_kmi_खोलो(काष्ठा serio *io)
अणु
	काष्ठा amba_kmi_port *kmi = io->port_data;
	अचिन्हित पूर्णांक भागisor;
	पूर्णांक ret;

	ret = clk_prepare_enable(kmi->clk);
	अगर (ret)
		जाओ out;

	भागisor = clk_get_rate(kmi->clk) / 8000000 - 1;
	ग_लिखोb(भागisor, KMICLKDIV);
	ग_लिखोb(KMICR_EN, KMICR);

	ret = request_irq(kmi->irq, amba_kmi_पूर्णांक, IRQF_SHARED, "kmi-pl050",
			  kmi);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "kmi: failed to claim IRQ%d\n", kmi->irq);
		ग_लिखोb(0, KMICR);
		जाओ clk_disable;
	पूर्ण

	ग_लिखोb(KMICR_EN | KMICR_RXINTREN, KMICR);

	वापस 0;

 clk_disable:
	clk_disable_unprepare(kmi->clk);
 out:
	वापस ret;
पूर्ण

अटल व्योम amba_kmi_बंद(काष्ठा serio *io)
अणु
	काष्ठा amba_kmi_port *kmi = io->port_data;

	ग_लिखोb(0, KMICR);

	मुक्त_irq(kmi->irq, kmi);
	clk_disable_unprepare(kmi->clk);
पूर्ण

अटल पूर्णांक amba_kmi_probe(काष्ठा amba_device *dev,
	स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा amba_kmi_port *kmi;
	काष्ठा serio *io;
	पूर्णांक ret;

	ret = amba_request_regions(dev, शून्य);
	अगर (ret)
		वापस ret;

	kmi = kzalloc(माप(काष्ठा amba_kmi_port), GFP_KERNEL);
	io = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!kmi || !io) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण


	io->id.type	= SERIO_8042;
	io->ग_लिखो	= amba_kmi_ग_लिखो;
	io->खोलो	= amba_kmi_खोलो;
	io->बंद	= amba_kmi_बंद;
	strlcpy(io->name, dev_name(&dev->dev), माप(io->name));
	strlcpy(io->phys, dev_name(&dev->dev), माप(io->phys));
	io->port_data	= kmi;
	io->dev.parent	= &dev->dev;

	kmi->io		= io;
	kmi->base	= ioremap(dev->res.start, resource_size(&dev->res));
	अगर (!kmi->base) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	kmi->clk = clk_get(&dev->dev, "KMIREFCLK");
	अगर (IS_ERR(kmi->clk)) अणु
		ret = PTR_ERR(kmi->clk);
		जाओ unmap;
	पूर्ण

	kmi->irq = dev->irq[0];
	amba_set_drvdata(dev, kmi);

	serio_रेजिस्टर_port(kmi->io);
	वापस 0;

 unmap:
	iounmap(kmi->base);
 out:
	kमुक्त(kmi);
	kमुक्त(io);
	amba_release_regions(dev);
	वापस ret;
पूर्ण

अटल व्योम amba_kmi_हटाओ(काष्ठा amba_device *dev)
अणु
	काष्ठा amba_kmi_port *kmi = amba_get_drvdata(dev);

	serio_unरेजिस्टर_port(kmi->io);
	clk_put(kmi->clk);
	iounmap(kmi->base);
	kमुक्त(kmi);
	amba_release_regions(dev);
पूर्ण

अटल पूर्णांक __maybe_unused amba_kmi_resume(काष्ठा device *dev)
अणु
	काष्ठा amba_kmi_port *kmi = dev_get_drvdata(dev);

	/* kick the serio layer to rescan this port */
	serio_reconnect(kmi->io);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(amba_kmi_dev_pm_ops, शून्य, amba_kmi_resume);

अटल स्थिर काष्ठा amba_id amba_kmi_idtable[] = अणु
	अणु
		.id	= 0x00041050,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(amba, amba_kmi_idtable);

अटल काष्ठा amba_driver ambakmi_driver = अणु
	.drv		= अणु
		.name	= "kmi-pl050",
		.owner	= THIS_MODULE,
		.pm	= &amba_kmi_dev_pm_ops,
	पूर्ण,
	.id_table	= amba_kmi_idtable,
	.probe		= amba_kmi_probe,
	.हटाओ		= amba_kmi_हटाओ,
पूर्ण;

module_amba_driver(ambakmi_driver);

MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("AMBA KMI controller driver");
MODULE_LICENSE("GPL");
