<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support code क्रम the SCOOP पूर्णांकerface found on various Sharp PDAs
 *
 * Copyright (c) 2004 Riअक्षरd Purdie
 *
 *	Based on code written by Sharp/Lineo क्रम 2.4 kernels
 */

#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/hardware/scoop.h>

/* PCMCIA to Scoop linkage

   There is no easy way to link multiple scoop devices पूर्णांकo one
   single entity क्रम the pxa2xx_pcmcia device so this काष्ठाure
   is used which is setup by the platक्रमm code.

   This file is never modular so this symbol is always
   accessile to the board support files.
*/
काष्ठा scoop_pcmcia_config *platक्रमm_scoop_config;
EXPORT_SYMBOL(platक्रमm_scoop_config);

काष्ठा  scoop_dev अणु
	व्योम __iomem *base;
	काष्ठा gpio_chip gpio;
	spinlock_t scoop_lock;
	अचिन्हित लघु suspend_clr;
	अचिन्हित लघु suspend_set;
	u32 scoop_gpwr;
पूर्ण;

व्योम reset_scoop(काष्ठा device *dev)
अणु
	काष्ठा scoop_dev *sdev = dev_get_drvdata(dev);

	ioग_लिखो16(0x0100, sdev->base + SCOOP_MCR);  /* 00 */
	ioग_लिखो16(0x0000, sdev->base + SCOOP_CDR);  /* 04 */
	ioग_लिखो16(0x0000, sdev->base + SCOOP_CCR);  /* 10 */
	ioग_लिखो16(0x0000, sdev->base + SCOOP_IMR);  /* 18 */
	ioग_लिखो16(0x00FF, sdev->base + SCOOP_IRM);  /* 14 */
	ioग_लिखो16(0x0000, sdev->base + SCOOP_ISR);  /* 1C */
	ioग_लिखो16(0x0000, sdev->base + SCOOP_IRM);
पूर्ण

अटल व्योम __scoop_gpio_set(काष्ठा scoop_dev *sdev,
			अचिन्हित offset, पूर्णांक value)
अणु
	अचिन्हित लघु gpwr;

	gpwr = ioपढ़ो16(sdev->base + SCOOP_GPWR);
	अगर (value)
		gpwr |= 1 << (offset + 1);
	अन्यथा
		gpwr &= ~(1 << (offset + 1));
	ioग_लिखो16(gpwr, sdev->base + SCOOP_GPWR);
पूर्ण

अटल व्योम scoop_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा scoop_dev *sdev = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sdev->scoop_lock, flags);

	__scoop_gpio_set(sdev, offset, value);

	spin_unlock_irqrestore(&sdev->scoop_lock, flags);
पूर्ण

अटल पूर्णांक scoop_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा scoop_dev *sdev = gpiochip_get_data(chip);

	/* XXX: I'm unsure, but it seems so */
	वापस !!(ioपढ़ो16(sdev->base + SCOOP_GPRR) & (1 << (offset + 1)));
पूर्ण

अटल पूर्णांक scoop_gpio_direction_input(काष्ठा gpio_chip *chip,
			अचिन्हित offset)
अणु
	काष्ठा scoop_dev *sdev = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु gpcr;

	spin_lock_irqsave(&sdev->scoop_lock, flags);

	gpcr = ioपढ़ो16(sdev->base + SCOOP_GPCR);
	gpcr &= ~(1 << (offset + 1));
	ioग_लिखो16(gpcr, sdev->base + SCOOP_GPCR);

	spin_unlock_irqrestore(&sdev->scoop_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक scoop_gpio_direction_output(काष्ठा gpio_chip *chip,
			अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा scoop_dev *sdev = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु gpcr;

	spin_lock_irqsave(&sdev->scoop_lock, flags);

	__scoop_gpio_set(sdev, offset, value);

	gpcr = ioपढ़ो16(sdev->base + SCOOP_GPCR);
	gpcr |= 1 << (offset + 1);
	ioग_लिखो16(gpcr, sdev->base + SCOOP_GPCR);

	spin_unlock_irqrestore(&sdev->scoop_lock, flags);

	वापस 0;
पूर्ण

अचिन्हित लघु पढ़ो_scoop_reg(काष्ठा device *dev, अचिन्हित लघु reg)
अणु
	काष्ठा scoop_dev *sdev = dev_get_drvdata(dev);
	वापस ioपढ़ो16(sdev->base + reg);
पूर्ण

व्योम ग_लिखो_scoop_reg(काष्ठा device *dev, अचिन्हित लघु reg, अचिन्हित लघु data)
अणु
	काष्ठा scoop_dev *sdev = dev_get_drvdata(dev);
	ioग_लिखो16(data, sdev->base + reg);
पूर्ण

EXPORT_SYMBOL(reset_scoop);
EXPORT_SYMBOL(पढ़ो_scoop_reg);
EXPORT_SYMBOL(ग_लिखो_scoop_reg);

#अगर_घोषित CONFIG_PM
अटल व्योम check_scoop_reg(काष्ठा scoop_dev *sdev)
अणु
	अचिन्हित लघु mcr;

	mcr = ioपढ़ो16(sdev->base + SCOOP_MCR);
	अगर ((mcr & 0x100) == 0)
		ioग_लिखो16(0x0101, sdev->base + SCOOP_MCR);
पूर्ण

अटल पूर्णांक scoop_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा scoop_dev *sdev = platक्रमm_get_drvdata(dev);

	check_scoop_reg(sdev);
	sdev->scoop_gpwr = ioपढ़ो16(sdev->base + SCOOP_GPWR);
	ioग_लिखो16((sdev->scoop_gpwr & ~sdev->suspend_clr) | sdev->suspend_set, sdev->base + SCOOP_GPWR);

	वापस 0;
पूर्ण

अटल पूर्णांक scoop_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा scoop_dev *sdev = platक्रमm_get_drvdata(dev);

	check_scoop_reg(sdev);
	ioग_लिखो16(sdev->scoop_gpwr, sdev->base + SCOOP_GPWR);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा scoop_suspend	शून्य
#घोषणा scoop_resume	शून्य
#पूर्ण_अगर

अटल पूर्णांक scoop_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा scoop_dev *devptr;
	काष्ठा scoop_config *inf;
	काष्ठा resource *mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	पूर्णांक ret;

	अगर (!mem)
		वापस -EINVAL;

	devptr = kzalloc(माप(काष्ठा scoop_dev), GFP_KERNEL);
	अगर (!devptr)
		वापस -ENOMEM;

	spin_lock_init(&devptr->scoop_lock);

	inf = pdev->dev.platक्रमm_data;
	devptr->base = ioremap(mem->start, resource_size(mem));

	अगर (!devptr->base) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	platक्रमm_set_drvdata(pdev, devptr);

	prपूर्णांकk("Sharp Scoop Device found at 0x%08x -> 0x%8p\n",(अचिन्हित पूर्णांक)mem->start, devptr->base);

	ioग_लिखो16(0x0140, devptr->base + SCOOP_MCR);
	reset_scoop(&pdev->dev);
	ioग_लिखो16(0x0000, devptr->base + SCOOP_CPR);
	ioग_लिखो16(inf->io_dir & 0xffff, devptr->base + SCOOP_GPCR);
	ioग_लिखो16(inf->io_out & 0xffff, devptr->base + SCOOP_GPWR);

	devptr->suspend_clr = inf->suspend_clr;
	devptr->suspend_set = inf->suspend_set;

	devptr->gpio.base = -1;

	अगर (inf->gpio_base != 0) अणु
		devptr->gpio.label = dev_name(&pdev->dev);
		devptr->gpio.base = inf->gpio_base;
		devptr->gpio.ngpio = 12; /* PA11 = 0, PA12 = 1, etc. up to PA22 = 11 */
		devptr->gpio.set = scoop_gpio_set;
		devptr->gpio.get = scoop_gpio_get;
		devptr->gpio.direction_input = scoop_gpio_direction_input;
		devptr->gpio.direction_output = scoop_gpio_direction_output;

		ret = gpiochip_add_data(&devptr->gpio, devptr);
		अगर (ret)
			जाओ err_gpio;
	पूर्ण

	वापस 0;

err_gpio:
	platक्रमm_set_drvdata(pdev, शून्य);
err_ioremap:
	iounmap(devptr->base);
	kमुक्त(devptr);

	वापस ret;
पूर्ण

अटल पूर्णांक scoop_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा scoop_dev *sdev = platक्रमm_get_drvdata(pdev);

	अगर (!sdev)
		वापस -EINVAL;

	अगर (sdev->gpio.base != -1)
		gpiochip_हटाओ(&sdev->gpio);

	platक्रमm_set_drvdata(pdev, शून्य);
	iounmap(sdev->base);
	kमुक्त(sdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver scoop_driver = अणु
	.probe		= scoop_probe,
	.हटाओ		= scoop_हटाओ,
	.suspend	= scoop_suspend,
	.resume		= scoop_resume,
	.driver		= अणु
		.name	= "sharp-scoop",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init scoop_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&scoop_driver);
पूर्ण

subsys_initcall(scoop_init);
