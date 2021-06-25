<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/common/locomo.c
 *
 * Sharp LoCoMo support
 *
 * This file contains all generic LoCoMo support.
 *
 * All initialization functions provided here are पूर्णांकended to be called
 * from machine specअगरic code with proper arguments when required.
 *
 * Based on sa1111.c
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/hardware/locomo.h>

/* LoCoMo Interrupts */
#घोषणा IRQ_LOCOMO_KEY		(0)
#घोषणा IRQ_LOCOMO_GPIO		(1)
#घोषणा IRQ_LOCOMO_LT		(2)
#घोषणा IRQ_LOCOMO_SPI		(3)

/* M62332 output channel selection */
#घोषणा M62332_EVR_CH	1	/* M62332 volume channel number  */
				/*   0 : CH.1 , 1 : CH. 2        */
/* DAC send data */
#घोषणा	M62332_SLAVE_ADDR	0x4e	/* Slave address  */
#घोषणा	M62332_W_BIT		0x00	/* W bit (0 only) */
#घोषणा	M62332_SUB_ADDR		0x00	/* Sub address    */
#घोषणा	M62332_A_BIT		0x00	/* A bit (0 only) */

/* DAC setup and hold बार (expressed in us) */
#घोषणा DAC_BUS_FREE_TIME	5	/*   4.7 us */
#घोषणा DAC_START_SETUP_TIME	5	/*   4.7 us */
#घोषणा DAC_STOP_SETUP_TIME	4	/*   4.0 us */
#घोषणा DAC_START_HOLD_TIME	5	/*   4.7 us */
#घोषणा DAC_SCL_LOW_HOLD_TIME	5	/*   4.7 us */
#घोषणा DAC_SCL_HIGH_HOLD_TIME	4	/*   4.0 us */
#घोषणा DAC_DATA_SETUP_TIME	1	/*   250 ns */
#घोषणा DAC_DATA_HOLD_TIME	1	/*   300 ns */
#घोषणा DAC_LOW_SETUP_TIME	1	/*   300 ns */
#घोषणा DAC_HIGH_SETUP_TIME	1	/*  1000 ns */

/* the following is the overall data क्रम the locomo chip */
काष्ठा locomo अणु
	काष्ठा device *dev;
	अचिन्हित दीर्घ phys;
	अचिन्हित पूर्णांक irq;
	पूर्णांक irq_base;
	spinlock_t lock;
	व्योम __iomem *base;
#अगर_घोषित CONFIG_PM
	व्योम *saved_state;
#पूर्ण_अगर
पूर्ण;

काष्ठा locomo_dev_info अणु
	अचिन्हित दीर्घ	offset;
	अचिन्हित दीर्घ	length;
	अचिन्हित पूर्णांक	devid;
	अचिन्हित पूर्णांक	irq[1];
	स्थिर अक्षर *	name;
पूर्ण;

/* All the locomo devices.  If offset is non-zero, the mapbase क्रम the
 * locomo_dev will be set to the chip base plus offset.  If offset is
 * zero, then the mapbase क्रम the locomo_dev will be set to zero.  An
 * offset of zero means the device only uses GPIOs or other helper
 * functions inside this file */
अटल काष्ठा locomo_dev_info locomo_devices[] = अणु
	अणु
		.devid 		= LOCOMO_DEVID_KEYBOARD,
		.irq		= अणु IRQ_LOCOMO_KEY पूर्ण,
		.name		= "locomo-keyboard",
		.offset		= LOCOMO_KEYBOARD,
		.length		= 16,
	पूर्ण,
	अणु
		.devid		= LOCOMO_DEVID_FRONTLIGHT,
		.irq		= अणुपूर्ण,
		.name		= "locomo-frontlight",
		.offset		= LOCOMO_FRONTLIGHT,
		.length		= 8,

	पूर्ण,
	अणु
		.devid		= LOCOMO_DEVID_BACKLIGHT,
		.irq		= अणुपूर्ण,
		.name		= "locomo-backlight",
		.offset		= LOCOMO_BACKLIGHT,
		.length		= 8,
	पूर्ण,
	अणु
		.devid		= LOCOMO_DEVID_AUDIO,
		.irq		= अणुपूर्ण,
		.name		= "locomo-audio",
		.offset		= LOCOMO_AUDIO,
		.length		= 4,
	पूर्ण,
	अणु
		.devid		= LOCOMO_DEVID_LED,
		.irq 		= अणुपूर्ण,
		.name		= "locomo-led",
		.offset		= LOCOMO_LED,
		.length		= 8,
	पूर्ण,
	अणु
		.devid		= LOCOMO_DEVID_UART,
		.irq		= अणुपूर्ण,
		.name		= "locomo-uart",
		.offset		= 0,
		.length		= 0,
	पूर्ण,
	अणु
		.devid		= LOCOMO_DEVID_SPI,
		.irq		= अणुपूर्ण,
		.name		= "locomo-spi",
		.offset		= LOCOMO_SPI,
		.length		= 0x30,
	पूर्ण,
पूर्ण;

अटल व्योम locomo_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा locomo *lchip = irq_desc_get_handler_data(desc);
	पूर्णांक req, i;

	/* Acknowledge the parent IRQ */
	desc->irq_data.chip->irq_ack(&desc->irq_data);

	/* check why this पूर्णांकerrupt was generated */
	req = locomo_पढ़ोl(lchip->base + LOCOMO_ICR) & 0x0f00;

	अगर (req) अणु
		अचिन्हित पूर्णांक irq;

		/* generate the next पूर्णांकerrupt(s) */
		irq = lchip->irq_base;
		क्रम (i = 0; i <= 3; i++, irq++) अणु
			अगर (req & (0x0100 << i)) अणु
				generic_handle_irq(irq);
			पूर्ण

		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम locomo_ack_irq(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम locomo_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा locomo *lchip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक r;
	r = locomo_पढ़ोl(lchip->base + LOCOMO_ICR);
	r &= ~(0x0010 << (d->irq - lchip->irq_base));
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_ICR);
पूर्ण

अटल व्योम locomo_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा locomo *lchip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक r;
	r = locomo_पढ़ोl(lchip->base + LOCOMO_ICR);
	r |= (0x0010 << (d->irq - lchip->irq_base));
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_ICR);
पूर्ण

अटल काष्ठा irq_chip locomo_chip = अणु
	.name		= "LOCOMO",
	.irq_ack	= locomo_ack_irq,
	.irq_mask	= locomo_mask_irq,
	.irq_unmask	= locomo_unmask_irq,
पूर्ण;

अटल व्योम locomo_setup_irq(काष्ठा locomo *lchip)
अणु
	पूर्णांक irq = lchip->irq_base;

	/*
	 * Install handler क्रम IRQ_LOCOMO_HW.
	 */
	irq_set_irq_type(lchip->irq, IRQ_TYPE_EDGE_FALLING);
	irq_set_chained_handler_and_data(lchip->irq, locomo_handler, lchip);

	/* Install handlers क्रम IRQ_LOCOMO_* */
	क्रम ( ; irq <= lchip->irq_base + 3; irq++) अणु
		irq_set_chip_and_handler(irq, &locomo_chip, handle_level_irq);
		irq_set_chip_data(irq, lchip);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण
पूर्ण


अटल व्योम locomo_dev_release(काष्ठा device *_dev)
अणु
	काष्ठा locomo_dev *dev = LOCOMO_DEV(_dev);

	kमुक्त(dev);
पूर्ण

अटल पूर्णांक
locomo_init_one_child(काष्ठा locomo *lchip, काष्ठा locomo_dev_info *info)
अणु
	काष्ठा locomo_dev *dev;
	पूर्णांक ret;

	dev = kzalloc(माप(काष्ठा locomo_dev), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * If the parent device has a DMA mask associated with it,
	 * propagate it करोwn to the children.
	 */
	अगर (lchip->dev->dma_mask) अणु
		dev->dma_mask = *lchip->dev->dma_mask;
		dev->dev.dma_mask = &dev->dma_mask;
	पूर्ण

	dev_set_name(&dev->dev, "%s", info->name);
	dev->devid	 = info->devid;
	dev->dev.parent  = lchip->dev;
	dev->dev.bus     = &locomo_bus_type;
	dev->dev.release = locomo_dev_release;
	dev->dev.coherent_dma_mask = lchip->dev->coherent_dma_mask;

	अगर (info->offset)
		dev->mapbase = lchip->base + info->offset;
	अन्यथा
		dev->mapbase = 0;
	dev->length = info->length;

	dev->irq[0] = (lchip->irq_base == NO_IRQ) ?
			NO_IRQ : lchip->irq_base + info->irq[0];

	ret = device_रेजिस्टर(&dev->dev);
	अगर (ret) अणु
 out:
		kमुक्त(dev);
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM

काष्ठा locomo_save_data अणु
	u16	LCM_GPO;
	u16	LCM_SPICT;
	u16	LCM_GPE;
	u16	LCM_ASD;
	u16	LCM_SPIMD;
पूर्ण;

अटल पूर्णांक locomo_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा locomo *lchip = platक्रमm_get_drvdata(dev);
	काष्ठा locomo_save_data *save;
	अचिन्हित दीर्घ flags;

	save = kदो_स्मृति(माप(काष्ठा locomo_save_data), GFP_KERNEL);
	अगर (!save)
		वापस -ENOMEM;

	lchip->saved_state = save;

	spin_lock_irqsave(&lchip->lock, flags);

	save->LCM_GPO     = locomo_पढ़ोl(lchip->base + LOCOMO_GPO);	/* GPIO */
	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_GPO);
	save->LCM_SPICT   = locomo_पढ़ोl(lchip->base + LOCOMO_SPI + LOCOMO_SPICT);	/* SPI */
	locomo_ग_लिखोl(0x40, lchip->base + LOCOMO_SPI + LOCOMO_SPICT);
	save->LCM_GPE     = locomo_पढ़ोl(lchip->base + LOCOMO_GPE);	/* GPIO */
	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_GPE);
	save->LCM_ASD     = locomo_पढ़ोl(lchip->base + LOCOMO_ASD);	/* ADSTART */
	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_ASD);
	save->LCM_SPIMD   = locomo_पढ़ोl(lchip->base + LOCOMO_SPI + LOCOMO_SPIMD);	/* SPI */
	locomo_ग_लिखोl(0x3C14, lchip->base + LOCOMO_SPI + LOCOMO_SPIMD);

	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_PAIF);
	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_DAC);
	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_BACKLIGHT + LOCOMO_TC);

	अगर ((locomo_पढ़ोl(lchip->base + LOCOMO_LED + LOCOMO_LPT0) & 0x88) && (locomo_पढ़ोl(lchip->base + LOCOMO_LED + LOCOMO_LPT1) & 0x88))
		locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_C32K); 	/* CLK32 off */
	अन्यथा
		/* 18MHz alपढ़ोy enabled, so no रुको */
		locomo_ग_लिखोl(0xc1, lchip->base + LOCOMO_C32K); 	/* CLK32 on */

	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_TADC);		/* 18MHz घड़ी off*/
	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_AUDIO + LOCOMO_ACC);			/* 22MHz/24MHz घड़ी off */
	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_FRONTLIGHT + LOCOMO_ALS);			/* FL */

	spin_unlock_irqrestore(&lchip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक locomo_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा locomo *lchip = platक्रमm_get_drvdata(dev);
	काष्ठा locomo_save_data *save;
	अचिन्हित दीर्घ r;
	अचिन्हित दीर्घ flags;

	save = lchip->saved_state;
	अगर (!save)
		वापस 0;

	spin_lock_irqsave(&lchip->lock, flags);

	locomo_ग_लिखोl(save->LCM_GPO, lchip->base + LOCOMO_GPO);
	locomo_ग_लिखोl(save->LCM_SPICT, lchip->base + LOCOMO_SPI + LOCOMO_SPICT);
	locomo_ग_लिखोl(save->LCM_GPE, lchip->base + LOCOMO_GPE);
	locomo_ग_लिखोl(save->LCM_ASD, lchip->base + LOCOMO_ASD);
	locomo_ग_लिखोl(save->LCM_SPIMD, lchip->base + LOCOMO_SPI + LOCOMO_SPIMD);

	locomo_ग_लिखोl(0x00, lchip->base + LOCOMO_C32K);
	locomo_ग_लिखोl(0x90, lchip->base + LOCOMO_TADC);

	locomo_ग_लिखोl(0, lchip->base + LOCOMO_KEYBOARD + LOCOMO_KSC);
	r = locomo_पढ़ोl(lchip->base + LOCOMO_KEYBOARD + LOCOMO_KIC);
	r &= 0xFEFF;
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_KEYBOARD + LOCOMO_KIC);
	locomo_ग_लिखोl(0x1, lchip->base + LOCOMO_KEYBOARD + LOCOMO_KCMD);

	spin_unlock_irqrestore(&lchip->lock, flags);

	lchip->saved_state = शून्य;
	kमुक्त(save);

	वापस 0;
पूर्ण
#पूर्ण_अगर


/**
 *	locomo_probe - probe क्रम a single LoCoMo chip.
 *	@phys_addr: physical address of device.
 *
 *	Probe क्रम a LoCoMo chip.  This must be called
 *	beक्रमe any other locomo-specअगरic code.
 *
 *	Returns:
 *	%-ENODEV	device not found.
 *	%-EBUSY		physical address alपढ़ोy marked in-use.
 *	%0		successful.
 */
अटल पूर्णांक
__locomo_probe(काष्ठा device *me, काष्ठा resource *mem, पूर्णांक irq)
अणु
	काष्ठा locomo_platक्रमm_data *pdata = me->platक्रमm_data;
	काष्ठा locomo *lchip;
	अचिन्हित दीर्घ r;
	पूर्णांक i, ret = -ENODEV;

	lchip = kzalloc(माप(काष्ठा locomo), GFP_KERNEL);
	अगर (!lchip)
		वापस -ENOMEM;

	spin_lock_init(&lchip->lock);

	lchip->dev = me;
	dev_set_drvdata(lchip->dev, lchip);

	lchip->phys = mem->start;
	lchip->irq = irq;
	lchip->irq_base = (pdata) ? pdata->irq_base : NO_IRQ;

	/*
	 * Map the whole region.  This also maps the
	 * रेजिस्टरs क्रम our children.
	 */
	lchip->base = ioremap(mem->start, PAGE_SIZE);
	अगर (!lchip->base) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* locomo initialize */
	locomo_ग_लिखोl(0, lchip->base + LOCOMO_ICR);
	/* KEYBOARD */
	locomo_ग_लिखोl(0, lchip->base + LOCOMO_KEYBOARD + LOCOMO_KIC);

	/* GPIO */
	locomo_ग_लिखोl(0, lchip->base + LOCOMO_GPO);
	locomo_ग_लिखोl((LOCOMO_GPIO(1) | LOCOMO_GPIO(2) | LOCOMO_GPIO(13) | LOCOMO_GPIO(14))
			, lchip->base + LOCOMO_GPE);
	locomo_ग_लिखोl((LOCOMO_GPIO(1) | LOCOMO_GPIO(2) | LOCOMO_GPIO(13) | LOCOMO_GPIO(14))
			, lchip->base + LOCOMO_GPD);
	locomo_ग_लिखोl(0, lchip->base + LOCOMO_GIE);

	/* Frontlight */
	locomo_ग_लिखोl(0, lchip->base + LOCOMO_FRONTLIGHT + LOCOMO_ALS);
	locomo_ग_लिखोl(0, lchip->base + LOCOMO_FRONTLIGHT + LOCOMO_ALD);

	/* Longसमय समयr */
	locomo_ग_लिखोl(0, lchip->base + LOCOMO_LTINT);
	/* SPI */
	locomo_ग_लिखोl(0, lchip->base + LOCOMO_SPI + LOCOMO_SPIIE);

	locomo_ग_लिखोl(6 + 8 + 320 + 30 - 10, lchip->base + LOCOMO_ASD);
	r = locomo_पढ़ोl(lchip->base + LOCOMO_ASD);
	r |= 0x8000;
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_ASD);

	locomo_ग_लिखोl(6 + 8 + 320 + 30 - 10 - 128 + 4, lchip->base + LOCOMO_HSD);
	r = locomo_पढ़ोl(lchip->base + LOCOMO_HSD);
	r |= 0x8000;
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_HSD);

	locomo_ग_लिखोl(128 / 8, lchip->base + LOCOMO_HSC);

	/* XON */
	locomo_ग_लिखोl(0x80, lchip->base + LOCOMO_TADC);
	udelay(1000);
	/* CLK9MEN */
	r = locomo_पढ़ोl(lchip->base + LOCOMO_TADC);
	r |= 0x10;
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_TADC);
	udelay(100);

	/* init DAC */
	r = locomo_पढ़ोl(lchip->base + LOCOMO_DAC);
	r |= LOCOMO_DAC_SCLOEB | LOCOMO_DAC_SDAOEB;
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_DAC);

	r = locomo_पढ़ोl(lchip->base + LOCOMO_VER);
	prपूर्णांकk(KERN_INFO "LoCoMo Chip: %lu%lu\n", (r >> 8), (r & 0xff));

	/*
	 * The पूर्णांकerrupt controller must be initialised beक्रमe any
	 * other device to ensure that the पूर्णांकerrupts are available.
	 */
	अगर (lchip->irq != NO_IRQ && lchip->irq_base != NO_IRQ)
		locomo_setup_irq(lchip);

	क्रम (i = 0; i < ARRAY_SIZE(locomo_devices); i++)
		locomo_init_one_child(lchip, &locomo_devices[i]);
	वापस 0;

 out:
	kमुक्त(lchip);
	वापस ret;
पूर्ण

अटल पूर्णांक locomo_हटाओ_child(काष्ठा device *dev, व्योम *data)
अणु
	device_unरेजिस्टर(dev);
	वापस 0;
पूर्ण 

अटल व्योम __locomo_हटाओ(काष्ठा locomo *lchip)
अणु
	device_क्रम_each_child(lchip->dev, शून्य, locomo_हटाओ_child);

	अगर (lchip->irq != NO_IRQ) अणु
		irq_set_chained_handler_and_data(lchip->irq, शून्य, शून्य);
	पूर्ण

	iounmap(lchip->base);
	kमुक्त(lchip);
पूर्ण

अटल पूर्णांक locomo_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा resource *mem;
	पूर्णांक irq;

	mem = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!mem)
		वापस -EINVAL;
	irq = platक्रमm_get_irq(dev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	वापस __locomo_probe(&dev->dev, mem, irq);
पूर्ण

अटल पूर्णांक locomo_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा locomo *lchip = platक्रमm_get_drvdata(dev);

	अगर (lchip) अणु
		__locomo_हटाओ(lchip);
		platक्रमm_set_drvdata(dev, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Not sure अगर this should be on the प्रणाली bus or not yet.
 *	We really want some way to रेजिस्टर a प्रणाली device at
 *	the per-machine level, and then have this driver pick
 *	up the रेजिस्टरed devices.
 */
अटल काष्ठा platक्रमm_driver locomo_device_driver = अणु
	.probe		= locomo_probe,
	.हटाओ		= locomo_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= locomo_suspend,
	.resume		= locomo_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= "locomo",
	पूर्ण,
पूर्ण;

/*
 *	Get the parent device driver (us) काष्ठाure
 *	from a child function device
 */
अटल अंतरभूत काष्ठा locomo *locomo_chip_driver(काष्ठा locomo_dev *ldev)
अणु
	वापस (काष्ठा locomo *)dev_get_drvdata(ldev->dev.parent);
पूर्ण

व्योम locomo_gpio_set_dir(काष्ठा device *dev, अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक dir)
अणु
	काष्ठा locomo *lchip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक r;

	अगर (!lchip)
		वापस;

	spin_lock_irqsave(&lchip->lock, flags);

	r = locomo_पढ़ोl(lchip->base + LOCOMO_GPD);
	अगर (dir)
		r |= bits;
	अन्यथा
		r &= ~bits;
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_GPD);

	r = locomo_पढ़ोl(lchip->base + LOCOMO_GPE);
	अगर (dir)
		r |= bits;
	अन्यथा
		r &= ~bits;
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_GPE);

	spin_unlock_irqrestore(&lchip->lock, flags);
पूर्ण
EXPORT_SYMBOL(locomo_gpio_set_dir);

पूर्णांक locomo_gpio_पढ़ो_level(काष्ठा device *dev, अचिन्हित पूर्णांक bits)
अणु
	काष्ठा locomo *lchip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret;

	अगर (!lchip)
		वापस -ENODEV;

	spin_lock_irqsave(&lchip->lock, flags);
	ret = locomo_पढ़ोl(lchip->base + LOCOMO_GPL);
	spin_unlock_irqrestore(&lchip->lock, flags);

	ret &= bits;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(locomo_gpio_पढ़ो_level);

पूर्णांक locomo_gpio_पढ़ो_output(काष्ठा device *dev, अचिन्हित पूर्णांक bits)
अणु
	काष्ठा locomo *lchip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret;

	अगर (!lchip)
		वापस -ENODEV;

	spin_lock_irqsave(&lchip->lock, flags);
	ret = locomo_पढ़ोl(lchip->base + LOCOMO_GPO);
	spin_unlock_irqrestore(&lchip->lock, flags);

	ret &= bits;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(locomo_gpio_पढ़ो_output);

व्योम locomo_gpio_ग_लिखो(काष्ठा device *dev, अचिन्हित पूर्णांक bits, अचिन्हित पूर्णांक set)
अणु
	काष्ठा locomo *lchip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक r;

	अगर (!lchip)
		वापस;

	spin_lock_irqsave(&lchip->lock, flags);

	r = locomo_पढ़ोl(lchip->base + LOCOMO_GPO);
	अगर (set)
		r |= bits;
	अन्यथा
		r &= ~bits;
	locomo_ग_लिखोl(r, lchip->base + LOCOMO_GPO);

	spin_unlock_irqrestore(&lchip->lock, flags);
पूर्ण
EXPORT_SYMBOL(locomo_gpio_ग_लिखो);

अटल व्योम locomo_m62332_sendbit(व्योम *mapbase, पूर्णांक bit)
अणु
	अचिन्हित पूर्णांक r;

	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SCLOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	udelay(DAC_DATA_HOLD_TIME);	/* 300 nsec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SCLOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	udelay(DAC_SCL_LOW_HOLD_TIME);	/* 4.7 usec */

	अगर (bit & 1) अणु
		r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
		r |=  LOCOMO_DAC_SDAOEB;
		locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
		udelay(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	पूर्ण अन्यथा अणु
		r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
		r &=  ~(LOCOMO_DAC_SDAOEB);
		locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
		udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	पूर्ण

	udelay(DAC_DATA_SETUP_TIME);	/* 250 nsec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r |=  LOCOMO_DAC_SCLOEB;
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udelay(DAC_SCL_HIGH_HOLD_TIME);	/*  4.0 usec */
पूर्ण

व्योम locomo_m62332_senddata(काष्ठा locomo_dev *ldev, अचिन्हित पूर्णांक dac_data, पूर्णांक channel)
अणु
	काष्ठा locomo *lchip = locomo_chip_driver(ldev);
	पूर्णांक i;
	अचिन्हित अक्षर data;
	अचिन्हित पूर्णांक r;
	व्योम *mapbase = lchip->base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lchip->lock, flags);

	/* Start */
	udelay(DAC_BUS_FREE_TIME);	/* 5.0 usec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r |=  LOCOMO_DAC_SCLOEB | LOCOMO_DAC_SDAOEB;
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udelay(DAC_SCL_HIGH_HOLD_TIME);	/* 4.0 usec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SDAOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_START_HOLD_TIME);	/* 5.0 usec */
	udelay(DAC_DATA_HOLD_TIME);	/* 300 nsec */

	/* Send slave address and W bit (LSB is W bit) */
	data = (M62332_SLAVE_ADDR << 1) | M62332_W_BIT;
	क्रम (i = 1; i <= 8; i++) अणु
		locomo_m62332_sendbit(mapbase, data >> (8 - i));
	पूर्ण

	/* Check A bit */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SCLOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	udelay(DAC_SCL_LOW_HOLD_TIME);	/* 4.7 usec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SDAOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r |=  LOCOMO_DAC_SCLOEB;
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udelay(DAC_SCL_HIGH_HOLD_TIME);	/* 4.7 usec */
	अगर (locomo_पढ़ोl(mapbase + LOCOMO_DAC) & LOCOMO_DAC_SDAOEB) अणु	/* High is error */
		prपूर्णांकk(KERN_WARNING "locomo: m62332_senddata Error 1\n");
		जाओ out;
	पूर्ण

	/* Send Sub address (LSB is channel select) */
	/*    channel = 0 : ch1 select              */
	/*            = 1 : ch2 select              */
	data = M62332_SUB_ADDR + channel;
	क्रम (i = 1; i <= 8; i++) अणु
		locomo_m62332_sendbit(mapbase, data >> (8 - i));
	पूर्ण

	/* Check A bit */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SCLOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	udelay(DAC_SCL_LOW_HOLD_TIME);	/* 4.7 usec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SDAOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r |=  LOCOMO_DAC_SCLOEB;
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udelay(DAC_SCL_HIGH_HOLD_TIME);	/* 4.7 usec */
	अगर (locomo_पढ़ोl(mapbase + LOCOMO_DAC) & LOCOMO_DAC_SDAOEB) अणु	/* High is error */
		prपूर्णांकk(KERN_WARNING "locomo: m62332_senddata Error 2\n");
		जाओ out;
	पूर्ण

	/* Send DAC data */
	क्रम (i = 1; i <= 8; i++) अणु
		locomo_m62332_sendbit(mapbase, dac_data >> (8 - i));
	पूर्ण

	/* Check A bit */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SCLOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	udelay(DAC_SCL_LOW_HOLD_TIME);	/* 4.7 usec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SDAOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r |=  LOCOMO_DAC_SCLOEB;
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udelay(DAC_SCL_HIGH_HOLD_TIME);	/* 4.7 usec */
	अगर (locomo_पढ़ोl(mapbase + LOCOMO_DAC) & LOCOMO_DAC_SDAOEB) अणु	/* High is error */
		prपूर्णांकk(KERN_WARNING "locomo: m62332_senddata Error 3\n");
	पूर्ण

out:
	/* stop */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r &=  ~(LOCOMO_DAC_SCLOEB);
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 300 nsec */
	udelay(DAC_SCL_LOW_HOLD_TIME);	/* 4.7 usec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r |=  LOCOMO_DAC_SCLOEB;
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udelay(DAC_SCL_HIGH_HOLD_TIME);	/* 4 usec */
	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r |=  LOCOMO_DAC_SDAOEB;
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udelay(DAC_SCL_HIGH_HOLD_TIME);	/* 4 usec */

	r = locomo_पढ़ोl(mapbase + LOCOMO_DAC);
	r |=  LOCOMO_DAC_SCLOEB | LOCOMO_DAC_SDAOEB;
	locomo_ग_लिखोl(r, mapbase + LOCOMO_DAC);
	udelay(DAC_LOW_SETUP_TIME);	/* 1000 nsec */
	udelay(DAC_SCL_LOW_HOLD_TIME);	/* 4.7 usec */

	spin_unlock_irqrestore(&lchip->lock, flags);
पूर्ण
EXPORT_SYMBOL(locomo_m62332_senddata);

/*
 *	Frontlight control
 */

व्योम locomo_frontlight_set(काष्ठा locomo_dev *dev, पूर्णांक duty, पूर्णांक vr, पूर्णांक bpwf)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा locomo *lchip = locomo_chip_driver(dev);

	अगर (vr)
		locomo_gpio_ग_लिखो(dev->dev.parent, LOCOMO_GPIO_FL_VR, 1);
	अन्यथा
		locomo_gpio_ग_लिखो(dev->dev.parent, LOCOMO_GPIO_FL_VR, 0);

	spin_lock_irqsave(&lchip->lock, flags);
	locomo_ग_लिखोl(bpwf, lchip->base + LOCOMO_FRONTLIGHT + LOCOMO_ALS);
	udelay(100);
	locomo_ग_लिखोl(duty, lchip->base + LOCOMO_FRONTLIGHT + LOCOMO_ALD);
	locomo_ग_लिखोl(bpwf | LOCOMO_ALC_EN, lchip->base + LOCOMO_FRONTLIGHT + LOCOMO_ALS);
	spin_unlock_irqrestore(&lchip->lock, flags);
पूर्ण
EXPORT_SYMBOL(locomo_frontlight_set);

/*
 *	LoCoMo "Register Access Bus."
 *
 *	We model this as a regular bus type, and hang devices directly
 *	off this.
 */
अटल पूर्णांक locomo_match(काष्ठा device *_dev, काष्ठा device_driver *_drv)
अणु
	काष्ठा locomo_dev *dev = LOCOMO_DEV(_dev);
	काष्ठा locomo_driver *drv = LOCOMO_DRV(_drv);

	वापस dev->devid == drv->devid;
पूर्ण

अटल पूर्णांक locomo_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा locomo_dev *ldev = LOCOMO_DEV(dev);
	काष्ठा locomo_driver *drv = LOCOMO_DRV(dev->driver);
	पूर्णांक ret = -ENODEV;

	अगर (drv->probe)
		ret = drv->probe(ldev);
	वापस ret;
पूर्ण

अटल पूर्णांक locomo_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा locomo_dev *ldev = LOCOMO_DEV(dev);
	काष्ठा locomo_driver *drv = LOCOMO_DRV(dev->driver);

	अगर (drv->हटाओ)
		drv->हटाओ(ldev);
	वापस 0;
पूर्ण

काष्ठा bus_type locomo_bus_type = अणु
	.name		= "locomo-bus",
	.match		= locomo_match,
	.probe		= locomo_bus_probe,
	.हटाओ		= locomo_bus_हटाओ,
पूर्ण;

पूर्णांक locomo_driver_रेजिस्टर(काष्ठा locomo_driver *driver)
अणु
	driver->drv.bus = &locomo_bus_type;
	वापस driver_रेजिस्टर(&driver->drv);
पूर्ण
EXPORT_SYMBOL(locomo_driver_रेजिस्टर);

व्योम locomo_driver_unरेजिस्टर(काष्ठा locomo_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->drv);
पूर्ण
EXPORT_SYMBOL(locomo_driver_unरेजिस्टर);

अटल पूर्णांक __init locomo_init(व्योम)
अणु
	पूर्णांक ret = bus_रेजिस्टर(&locomo_bus_type);
	अगर (ret == 0)
		platक्रमm_driver_रेजिस्टर(&locomo_device_driver);
	वापस ret;
पूर्ण

अटल व्योम __निकास locomo_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&locomo_device_driver);
	bus_unरेजिस्टर(&locomo_bus_type);
पूर्ण

module_init(locomo_init);
module_निकास(locomo_निकास);

MODULE_DESCRIPTION("Sharp LoCoMo core driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Lenz <lenz@cs.wisc.edu>");
