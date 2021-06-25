<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 LAPIS Semiconductor Co., Ltd.
 */
#समावेश <linux/bits.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#घोषणा PCH_EDGE_FALLING	0
#घोषणा PCH_EDGE_RISING		1
#घोषणा PCH_LEVEL_L		2
#घोषणा PCH_LEVEL_H		3
#घोषणा PCH_EDGE_BOTH		4
#घोषणा PCH_IM_MASK		GENMASK(2, 0)

#घोषणा PCH_IRQ_BASE		24

काष्ठा pch_regs अणु
	u32	ien;
	u32	istatus;
	u32	idisp;
	u32	iclr;
	u32	imask;
	u32	imaskclr;
	u32	po;
	u32	pi;
	u32	pm;
	u32	im0;
	u32	im1;
	u32	reserved[3];
	u32	gpio_use_sel;
	u32	reset;
पूर्ण;

क्रमागत pch_type_t अणु
	INTEL_EG20T_PCH,
	OKISEMI_ML7223m_IOH, /* LAPIS Semiconductor ML7223 IOH PCIe Bus-m */
	OKISEMI_ML7223n_IOH  /* LAPIS Semiconductor ML7223 IOH PCIe Bus-n */
पूर्ण;

/* Specअगरies number of GPIO PINS */
अटल पूर्णांक gpio_pins[] = अणु
	[INTEL_EG20T_PCH] = 12,
	[OKISEMI_ML7223m_IOH] = 8,
	[OKISEMI_ML7223n_IOH] = 8,
पूर्ण;

/**
 * काष्ठा pch_gpio_reg_data - The रेजिस्टर store data.
 * @ien_reg:	To store contents of IEN रेजिस्टर.
 * @imask_reg:	To store contents of IMASK रेजिस्टर.
 * @po_reg:	To store contents of PO रेजिस्टर.
 * @pm_reg:	To store contents of PM रेजिस्टर.
 * @im0_reg:	To store contents of IM0 रेजिस्टर.
 * @im1_reg:	To store contents of IM1 रेजिस्टर.
 * @gpio_use_sel_reg : To store contents of GPIO_USE_SEL रेजिस्टर.
 *		       (Only ML7223 Bus-n)
 */
काष्ठा pch_gpio_reg_data अणु
	u32 ien_reg;
	u32 imask_reg;
	u32 po_reg;
	u32 pm_reg;
	u32 im0_reg;
	u32 im1_reg;
	u32 gpio_use_sel_reg;
पूर्ण;

/**
 * काष्ठा pch_gpio - GPIO निजी data काष्ठाure.
 * @base:			PCI base address of Memory mapped I/O रेजिस्टर.
 * @reg:			Memory mapped PCH GPIO रेजिस्टर list.
 * @dev:			Poपूर्णांकer to device काष्ठाure.
 * @gpio:			Data क्रम GPIO infraकाष्ठाure.
 * @pch_gpio_reg:		Memory mapped Register data is saved here
 *				when suspend.
 * @lock:			Used क्रम रेजिस्टर access protection
 * @irq_base:		Save base of IRQ number क्रम पूर्णांकerrupt
 * @ioh:		IOH ID
 * @spinlock:		Used क्रम रेजिस्टर access protection
 */
काष्ठा pch_gpio अणु
	व्योम __iomem *base;
	काष्ठा pch_regs __iomem *reg;
	काष्ठा device *dev;
	काष्ठा gpio_chip gpio;
	काष्ठा pch_gpio_reg_data pch_gpio_reg;
	पूर्णांक irq_base;
	क्रमागत pch_type_t ioh;
	spinlock_t spinlock;
पूर्ण;

अटल व्योम pch_gpio_set(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr, पूर्णांक val)
अणु
	u32 reg_val;
	काष्ठा pch_gpio *chip =	gpiochip_get_data(gpio);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	reg_val = ioपढ़ो32(&chip->reg->po);
	अगर (val)
		reg_val |= BIT(nr);
	अन्यथा
		reg_val &= ~BIT(nr);

	ioग_लिखो32(reg_val, &chip->reg->po);
	spin_unlock_irqrestore(&chip->spinlock, flags);
पूर्ण

अटल पूर्णांक pch_gpio_get(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा pch_gpio *chip =	gpiochip_get_data(gpio);

	वापस !!(ioपढ़ो32(&chip->reg->pi) & BIT(nr));
पूर्ण

अटल पूर्णांक pch_gpio_direction_output(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr,
				     पूर्णांक val)
अणु
	काष्ठा pch_gpio *chip =	gpiochip_get_data(gpio);
	u32 pm;
	u32 reg_val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);

	reg_val = ioपढ़ो32(&chip->reg->po);
	अगर (val)
		reg_val |= BIT(nr);
	अन्यथा
		reg_val &= ~BIT(nr);
	ioग_लिखो32(reg_val, &chip->reg->po);

	pm = ioपढ़ो32(&chip->reg->pm);
	pm &= BIT(gpio_pins[chip->ioh]) - 1;
	pm |= BIT(nr);
	ioग_लिखो32(pm, &chip->reg->pm);

	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक pch_gpio_direction_input(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा pch_gpio *chip =	gpiochip_get_data(gpio);
	u32 pm;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	pm = ioपढ़ो32(&chip->reg->pm);
	pm &= BIT(gpio_pins[chip->ioh]) - 1;
	pm &= ~BIT(nr);
	ioग_लिखो32(pm, &chip->reg->pm);
	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण

/*
 * Save रेजिस्टर configuration and disable पूर्णांकerrupts.
 */
अटल व्योम __maybe_unused pch_gpio_save_reg_conf(काष्ठा pch_gpio *chip)
अणु
	chip->pch_gpio_reg.ien_reg = ioपढ़ो32(&chip->reg->ien);
	chip->pch_gpio_reg.imask_reg = ioपढ़ो32(&chip->reg->imask);
	chip->pch_gpio_reg.po_reg = ioपढ़ो32(&chip->reg->po);
	chip->pch_gpio_reg.pm_reg = ioपढ़ो32(&chip->reg->pm);
	chip->pch_gpio_reg.im0_reg = ioपढ़ो32(&chip->reg->im0);
	अगर (chip->ioh == INTEL_EG20T_PCH)
		chip->pch_gpio_reg.im1_reg = ioपढ़ो32(&chip->reg->im1);
	अगर (chip->ioh == OKISEMI_ML7223n_IOH)
		chip->pch_gpio_reg.gpio_use_sel_reg = ioपढ़ो32(&chip->reg->gpio_use_sel);
पूर्ण

/*
 * This function restores the रेजिस्टर configuration of the GPIO device.
 */
अटल व्योम __maybe_unused pch_gpio_restore_reg_conf(काष्ठा pch_gpio *chip)
अणु
	ioग_लिखो32(chip->pch_gpio_reg.ien_reg, &chip->reg->ien);
	ioग_लिखो32(chip->pch_gpio_reg.imask_reg, &chip->reg->imask);
	/* to store contents of PO रेजिस्टर */
	ioग_लिखो32(chip->pch_gpio_reg.po_reg, &chip->reg->po);
	/* to store contents of PM रेजिस्टर */
	ioग_लिखो32(chip->pch_gpio_reg.pm_reg, &chip->reg->pm);
	ioग_लिखो32(chip->pch_gpio_reg.im0_reg, &chip->reg->im0);
	अगर (chip->ioh == INTEL_EG20T_PCH)
		ioग_लिखो32(chip->pch_gpio_reg.im1_reg, &chip->reg->im1);
	अगर (chip->ioh == OKISEMI_ML7223n_IOH)
		ioग_लिखो32(chip->pch_gpio_reg.gpio_use_sel_reg, &chip->reg->gpio_use_sel);
पूर्ण

अटल पूर्णांक pch_gpio_to_irq(काष्ठा gpio_chip *gpio, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा pch_gpio *chip = gpiochip_get_data(gpio);

	वापस chip->irq_base + offset;
पूर्ण

अटल व्योम pch_gpio_setup(काष्ठा pch_gpio *chip)
अणु
	काष्ठा gpio_chip *gpio = &chip->gpio;

	gpio->label = dev_name(chip->dev);
	gpio->parent = chip->dev;
	gpio->owner = THIS_MODULE;
	gpio->direction_input = pch_gpio_direction_input;
	gpio->get = pch_gpio_get;
	gpio->direction_output = pch_gpio_direction_output;
	gpio->set = pch_gpio_set;
	gpio->base = -1;
	gpio->ngpio = gpio_pins[chip->ioh];
	gpio->can_sleep = false;
	gpio->to_irq = pch_gpio_to_irq;
पूर्ण

अटल पूर्णांक pch_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pch_gpio *chip = gc->निजी;
	u32 im, im_pos, val;
	u32 __iomem *im_reg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ch, irq = d->irq;

	ch = irq - chip->irq_base;
	अगर (irq < chip->irq_base + 8) अणु
		im_reg = &chip->reg->im0;
		im_pos = ch - 0;
	पूर्ण अन्यथा अणु
		im_reg = &chip->reg->im1;
		im_pos = ch - 8;
	पूर्ण
	dev_dbg(chip->dev, "irq=%d type=%d ch=%d pos=%d\n", irq, type, ch, im_pos);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		val = PCH_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		val = PCH_EDGE_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		val = PCH_EDGE_BOTH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		val = PCH_LEVEL_H;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		val = PCH_LEVEL_L;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&chip->spinlock, flags);

	/* Set पूर्णांकerrupt mode */
	im = ioपढ़ो32(im_reg) & ~(PCH_IM_MASK << (im_pos * 4));
	ioग_लिखो32(im | (val << (im_pos * 4)), im_reg);

	/* And the handler */
	अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(d, handle_level_irq);
	अन्यथा अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);

	spin_unlock_irqrestore(&chip->spinlock, flags);
	वापस 0;
पूर्ण

अटल व्योम pch_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pch_gpio *chip = gc->निजी;

	ioग_लिखो32(BIT(d->irq - chip->irq_base), &chip->reg->imaskclr);
पूर्ण

अटल व्योम pch_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pch_gpio *chip = gc->निजी;

	ioग_लिखो32(BIT(d->irq - chip->irq_base), &chip->reg->imask);
पूर्ण

अटल व्योम pch_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा pch_gpio *chip = gc->निजी;

	ioग_लिखो32(BIT(d->irq - chip->irq_base), &chip->reg->iclr);
पूर्ण

अटल irqवापस_t pch_gpio_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pch_gpio *chip = dev_id;
	अचिन्हित दीर्घ reg_val = ioपढ़ो32(&chip->reg->istatus);
	पूर्णांक i;

	dev_vdbg(chip->dev, "irq=%d  status=0x%lx\n", irq, reg_val);

	reg_val &= BIT(gpio_pins[chip->ioh]) - 1;

	क्रम_each_set_bit(i, &reg_val, gpio_pins[chip->ioh])
		generic_handle_irq(chip->irq_base + i);

	वापस IRQ_RETVAL(reg_val);
पूर्ण

अटल पूर्णांक pch_gpio_alloc_generic_chip(काष्ठा pch_gpio *chip,
				       अचिन्हित पूर्णांक irq_start,
				       अचिन्हित पूर्णांक num)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	पूर्णांक rv;

	gc = devm_irq_alloc_generic_chip(chip->dev, "pch_gpio", 1, irq_start,
					 chip->base, handle_simple_irq);
	अगर (!gc)
		वापस -ENOMEM;

	gc->निजी = chip;
	ct = gc->chip_types;

	ct->chip.irq_ack = pch_irq_ack;
	ct->chip.irq_mask = pch_irq_mask;
	ct->chip.irq_unmask = pch_irq_unmask;
	ct->chip.irq_set_type = pch_irq_type;

	rv = devm_irq_setup_generic_chip(chip->dev, gc, IRQ_MSK(num),
					 IRQ_GC_INIT_MASK_CACHE,
					 IRQ_NOREQUEST | IRQ_NOPROBE, 0);

	वापस rv;
पूर्ण

अटल पूर्णांक pch_gpio_probe(काष्ठा pci_dev *pdev,
				    स्थिर काष्ठा pci_device_id *id)
अणु
	s32 ret;
	काष्ठा pch_gpio *chip;
	पूर्णांक irq_base;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	chip->dev = &pdev->dev;
	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pci_enable_device FAILED");
		वापस ret;
	पूर्ण

	ret = pcim_iomap_regions(pdev, BIT(1), KBUILD_MODNAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pci_request_regions FAILED-%d", ret);
		वापस ret;
	पूर्ण

	chip->base = pcim_iomap_table(pdev)[1];

	अगर (pdev->device == 0x8803)
		chip->ioh = INTEL_EG20T_PCH;
	अन्यथा अगर (pdev->device == 0x8014)
		chip->ioh = OKISEMI_ML7223m_IOH;
	अन्यथा अगर (pdev->device == 0x8043)
		chip->ioh = OKISEMI_ML7223n_IOH;

	chip->reg = chip->base;
	pci_set_drvdata(pdev, chip);
	spin_lock_init(&chip->spinlock);
	pch_gpio_setup(chip);

	ret = devm_gpiochip_add_data(&pdev->dev, &chip->gpio, chip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "PCH gpio: Failed to register GPIO\n");
		वापस ret;
	पूर्ण

	irq_base = devm_irq_alloc_descs(&pdev->dev, -1, 0,
					gpio_pins[chip->ioh], NUMA_NO_NODE);
	अगर (irq_base < 0) अणु
		dev_warn(&pdev->dev, "PCH gpio: Failed to get IRQ base num\n");
		chip->irq_base = -1;
		वापस 0;
	पूर्ण
	chip->irq_base = irq_base;

	/* Mask all पूर्णांकerrupts, but enable them */
	ioग_लिखो32(BIT(gpio_pins[chip->ioh]) - 1, &chip->reg->imask);
	ioग_लिखो32(BIT(gpio_pins[chip->ioh]) - 1, &chip->reg->ien);

	ret = devm_request_irq(&pdev->dev, pdev->irq, pch_gpio_handler,
			       IRQF_SHARED, KBUILD_MODNAME, chip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request_irq failed\n");
		वापस ret;
	पूर्ण

	वापस pch_gpio_alloc_generic_chip(chip, irq_base, gpio_pins[chip->ioh]);
पूर्ण

अटल पूर्णांक __maybe_unused pch_gpio_suspend(काष्ठा device *dev)
अणु
	काष्ठा pch_gpio *chip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	pch_gpio_save_reg_conf(chip);
	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pch_gpio_resume(काष्ठा device *dev)
अणु
	काष्ठा pch_gpio *chip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	ioग_लिखो32(0x01, &chip->reg->reset);
	ioग_लिखो32(0x00, &chip->reg->reset);
	pch_gpio_restore_reg_conf(chip);
	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pch_gpio_pm_ops, pch_gpio_suspend, pch_gpio_resume);

अटल स्थिर काष्ठा pci_device_id pch_gpio_pcidev_id[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x8803) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x8014) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x8043) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x8803) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pch_gpio_pcidev_id);

अटल काष्ठा pci_driver pch_gpio_driver = अणु
	.name = "pch_gpio",
	.id_table = pch_gpio_pcidev_id,
	.probe = pch_gpio_probe,
	.driver = अणु
		.pm = &pch_gpio_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(pch_gpio_driver);

MODULE_DESCRIPTION("PCH GPIO PCI Driver");
MODULE_LICENSE("GPL v2");
