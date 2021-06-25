<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 OKI SEMICONDUCTOR Co., LTD.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#घोषणा IOH_EDGE_FALLING	0
#घोषणा IOH_EDGE_RISING		BIT(0)
#घोषणा IOH_LEVEL_L		BIT(1)
#घोषणा IOH_LEVEL_H		(BIT(0) | BIT(1))
#घोषणा IOH_EDGE_BOTH		BIT(2)
#घोषणा IOH_IM_MASK		(BIT(0) | BIT(1) | BIT(2))

#घोषणा IOH_IRQ_BASE		0

काष्ठा ioh_reg_comn अणु
	u32	ien;
	u32	istatus;
	u32	idisp;
	u32	iclr;
	u32	imask;
	u32	imaskclr;
	u32	po;
	u32	pi;
	u32	pm;
	u32	im_0;
	u32	im_1;
	u32	reserved;
पूर्ण;

काष्ठा ioh_regs अणु
	काष्ठा ioh_reg_comn regs[8];
	u32 reserve1[16];
	u32 ioh_sel_reg[4];
	u32 reserve2[11];
	u32 srst;
पूर्ण;

/**
 * काष्ठा ioh_gpio_reg_data - The रेजिस्टर store data.
 * @ien_reg:	To store contents of पूर्णांकerrupt enable रेजिस्टर.
 * @imask_reg:	To store contents of पूर्णांकerrupt mask regist
 * @po_reg:	To store contents of PO रेजिस्टर.
 * @pm_reg:	To store contents of PM रेजिस्टर.
 * @im0_reg:	To store contents of पूर्णांकerrupt mode regist0
 * @im1_reg:	To store contents of पूर्णांकerrupt mode regist1
 * @use_sel_reg: To store contents of GPIO_USE_SEL0~3
 */
काष्ठा ioh_gpio_reg_data अणु
	u32 ien_reg;
	u32 imask_reg;
	u32 po_reg;
	u32 pm_reg;
	u32 im0_reg;
	u32 im1_reg;
	u32 use_sel_reg;
पूर्ण;

/**
 * काष्ठा ioh_gpio - GPIO निजी data काष्ठाure.
 * @base:			PCI base address of Memory mapped I/O रेजिस्टर.
 * @reg:			Memory mapped IOH GPIO रेजिस्टर list.
 * @dev:			Poपूर्णांकer to device काष्ठाure.
 * @gpio:			Data क्रम GPIO infraकाष्ठाure.
 * @ioh_gpio_reg:		Memory mapped Register data is saved here
 *				when suspend.
 * @gpio_use_sel:		Save GPIO_USE_SEL1~4 रेजिस्टर क्रम PM
 * @ch:				Indicate GPIO channel
 * @irq_base:		Save base of IRQ number क्रम पूर्णांकerrupt
 * @spinlock:		Used क्रम रेजिस्टर access protection
 */
काष्ठा ioh_gpio अणु
	व्योम __iomem *base;
	काष्ठा ioh_regs __iomem *reg;
	काष्ठा device *dev;
	काष्ठा gpio_chip gpio;
	काष्ठा ioh_gpio_reg_data ioh_gpio_reg;
	u32 gpio_use_sel;
	पूर्णांक ch;
	पूर्णांक irq_base;
	spinlock_t spinlock;
पूर्ण;

अटल स्थिर पूर्णांक num_ports[] = अणु6, 12, 16, 16, 15, 16, 16, 12पूर्ण;

अटल व्योम ioh_gpio_set(काष्ठा gpio_chip *gpio, अचिन्हित nr, पूर्णांक val)
अणु
	u32 reg_val;
	काष्ठा ioh_gpio *chip =	gpiochip_get_data(gpio);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	reg_val = ioपढ़ो32(&chip->reg->regs[chip->ch].po);
	अगर (val)
		reg_val |= (1 << nr);
	अन्यथा
		reg_val &= ~(1 << nr);

	ioग_लिखो32(reg_val, &chip->reg->regs[chip->ch].po);
	spin_unlock_irqrestore(&chip->spinlock, flags);
पूर्ण

अटल पूर्णांक ioh_gpio_get(काष्ठा gpio_chip *gpio, अचिन्हित nr)
अणु
	काष्ठा ioh_gpio *chip =	gpiochip_get_data(gpio);

	वापस !!(ioपढ़ो32(&chip->reg->regs[chip->ch].pi) & (1 << nr));
पूर्ण

अटल पूर्णांक ioh_gpio_direction_output(काष्ठा gpio_chip *gpio, अचिन्हित nr,
				     पूर्णांक val)
अणु
	काष्ठा ioh_gpio *chip =	gpiochip_get_data(gpio);
	u32 pm;
	u32 reg_val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	pm = ioपढ़ो32(&chip->reg->regs[chip->ch].pm) &
					((1 << num_ports[chip->ch]) - 1);
	pm |= (1 << nr);
	ioग_लिखो32(pm, &chip->reg->regs[chip->ch].pm);

	reg_val = ioपढ़ो32(&chip->reg->regs[chip->ch].po);
	अगर (val)
		reg_val |= (1 << nr);
	अन्यथा
		reg_val &= ~(1 << nr);
	ioग_लिखो32(reg_val, &chip->reg->regs[chip->ch].po);

	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ioh_gpio_direction_input(काष्ठा gpio_chip *gpio, अचिन्हित nr)
अणु
	काष्ठा ioh_gpio *chip =	gpiochip_get_data(gpio);
	u32 pm;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	pm = ioपढ़ो32(&chip->reg->regs[chip->ch].pm) &
				((1 << num_ports[chip->ch]) - 1);
	pm &= ~(1 << nr);
	ioग_लिखो32(pm, &chip->reg->regs[chip->ch].pm);
	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
/*
 * Save रेजिस्टर configuration and disable पूर्णांकerrupts.
 */
अटल व्योम ioh_gpio_save_reg_conf(काष्ठा ioh_gpio *chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i ++, chip++) अणु
		chip->ioh_gpio_reg.po_reg =
					ioपढ़ो32(&chip->reg->regs[chip->ch].po);
		chip->ioh_gpio_reg.pm_reg =
					ioपढ़ो32(&chip->reg->regs[chip->ch].pm);
		chip->ioh_gpio_reg.ien_reg =
				       ioपढ़ो32(&chip->reg->regs[chip->ch].ien);
		chip->ioh_gpio_reg.imask_reg =
				     ioपढ़ो32(&chip->reg->regs[chip->ch].imask);
		chip->ioh_gpio_reg.im0_reg =
				      ioपढ़ो32(&chip->reg->regs[chip->ch].im_0);
		chip->ioh_gpio_reg.im1_reg =
				      ioपढ़ो32(&chip->reg->regs[chip->ch].im_1);
		अगर (i < 4)
			chip->ioh_gpio_reg.use_sel_reg =
					   ioपढ़ो32(&chip->reg->ioh_sel_reg[i]);
	पूर्ण
पूर्ण

/*
 * This function restores the रेजिस्टर configuration of the GPIO device.
 */
अटल व्योम ioh_gpio_restore_reg_conf(काष्ठा ioh_gpio *chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i ++, chip++) अणु
		ioग_लिखो32(chip->ioh_gpio_reg.po_reg,
			  &chip->reg->regs[chip->ch].po);
		ioग_लिखो32(chip->ioh_gpio_reg.pm_reg,
			  &chip->reg->regs[chip->ch].pm);
		ioग_लिखो32(chip->ioh_gpio_reg.ien_reg,
			  &chip->reg->regs[chip->ch].ien);
		ioग_लिखो32(chip->ioh_gpio_reg.imask_reg,
			  &chip->reg->regs[chip->ch].imask);
		ioग_लिखो32(chip->ioh_gpio_reg.im0_reg,
			  &chip->reg->regs[chip->ch].im_0);
		ioग_लिखो32(chip->ioh_gpio_reg.im1_reg,
			  &chip->reg->regs[chip->ch].im_1);
		अगर (i < 4)
			ioग_लिखो32(chip->ioh_gpio_reg.use_sel_reg,
				  &chip->reg->ioh_sel_reg[i]);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ioh_gpio_to_irq(काष्ठा gpio_chip *gpio, अचिन्हित offset)
अणु
	काष्ठा ioh_gpio *chip = gpiochip_get_data(gpio);
	वापस chip->irq_base + offset;
पूर्ण

अटल व्योम ioh_gpio_setup(काष्ठा ioh_gpio *chip, पूर्णांक num_port)
अणु
	काष्ठा gpio_chip *gpio = &chip->gpio;

	gpio->label = dev_name(chip->dev);
	gpio->owner = THIS_MODULE;
	gpio->direction_input = ioh_gpio_direction_input;
	gpio->get = ioh_gpio_get;
	gpio->direction_output = ioh_gpio_direction_output;
	gpio->set = ioh_gpio_set;
	gpio->dbg_show = शून्य;
	gpio->base = -1;
	gpio->ngpio = num_port;
	gpio->can_sleep = false;
	gpio->to_irq = ioh_gpio_to_irq;
पूर्ण

अटल पूर्णांक ioh_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	u32 im;
	व्योम __iomem *im_reg;
	u32 ien;
	u32 im_pos;
	पूर्णांक ch;
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक irq = d->irq;
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ioh_gpio *chip = gc->निजी;

	ch = irq - chip->irq_base;
	अगर (irq <= chip->irq_base + 7) अणु
		im_reg = &chip->reg->regs[chip->ch].im_0;
		im_pos = ch;
	पूर्ण अन्यथा अणु
		im_reg = &chip->reg->regs[chip->ch].im_1;
		im_pos = ch - 8;
	पूर्ण
	dev_dbg(chip->dev, "%s:irq=%d type=%d ch=%d pos=%d type=%d\n",
		__func__, irq, type, ch, im_pos, type);

	spin_lock_irqsave(&chip->spinlock, flags);

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		val = IOH_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		val = IOH_EDGE_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		val = IOH_EDGE_BOTH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		val = IOH_LEVEL_H;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		val = IOH_LEVEL_L;
		अवरोध;
	हाल IRQ_TYPE_PROBE:
		जाओ end;
	शेष:
		dev_warn(chip->dev, "%s: unknown type(%dd)",
			__func__, type);
		जाओ end;
	पूर्ण

	/* Set पूर्णांकerrupt mode */
	im = ioपढ़ो32(im_reg) & ~(IOH_IM_MASK << (im_pos * 4));
	ioग_लिखो32(im | (val << (im_pos * 4)), im_reg);

	/* iclr */
	ioग_लिखो32(BIT(ch), &chip->reg->regs[chip->ch].iclr);

	/* IMASKCLR */
	ioग_लिखो32(BIT(ch), &chip->reg->regs[chip->ch].imaskclr);

	/* Enable पूर्णांकerrupt */
	ien = ioपढ़ो32(&chip->reg->regs[chip->ch].ien);
	ioग_लिखो32(ien | BIT(ch), &chip->reg->regs[chip->ch].ien);
end:
	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण

अटल व्योम ioh_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ioh_gpio *chip = gc->निजी;

	ioग_लिखो32(1 << (d->irq - chip->irq_base),
		  &chip->reg->regs[chip->ch].imaskclr);
पूर्ण

अटल व्योम ioh_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ioh_gpio *chip = gc->निजी;

	ioग_लिखो32(1 << (d->irq - chip->irq_base),
		  &chip->reg->regs[chip->ch].imask);
पूर्ण

अटल व्योम ioh_irq_disable(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ioh_gpio *chip = gc->निजी;
	अचिन्हित दीर्घ flags;
	u32 ien;

	spin_lock_irqsave(&chip->spinlock, flags);
	ien = ioपढ़ो32(&chip->reg->regs[chip->ch].ien);
	ien &= ~(1 << (d->irq - chip->irq_base));
	ioग_लिखो32(ien, &chip->reg->regs[chip->ch].ien);
	spin_unlock_irqrestore(&chip->spinlock, flags);
पूर्ण

अटल व्योम ioh_irq_enable(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा ioh_gpio *chip = gc->निजी;
	अचिन्हित दीर्घ flags;
	u32 ien;

	spin_lock_irqsave(&chip->spinlock, flags);
	ien = ioपढ़ो32(&chip->reg->regs[chip->ch].ien);
	ien |= 1 << (d->irq - chip->irq_base);
	ioग_लिखो32(ien, &chip->reg->regs[chip->ch].ien);
	spin_unlock_irqrestore(&chip->spinlock, flags);
पूर्ण

अटल irqवापस_t ioh_gpio_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ioh_gpio *chip = dev_id;
	u32 reg_val;
	पूर्णांक i, j;
	पूर्णांक ret = IRQ_NONE;

	क्रम (i = 0; i < 8; i++, chip++) अणु
		reg_val = ioपढ़ो32(&chip->reg->regs[i].istatus);
		क्रम (j = 0; j < num_ports[i]; j++) अणु
			अगर (reg_val & BIT(j)) अणु
				dev_dbg(chip->dev,
					"%s:[%d]:irq=%d status=0x%x\n",
					__func__, j, irq, reg_val);
				ioग_लिखो32(BIT(j),
					  &chip->reg->regs[chip->ch].iclr);
				generic_handle_irq(chip->irq_base + j);
				ret = IRQ_HANDLED;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ioh_gpio_alloc_generic_chip(काष्ठा ioh_gpio *chip,
				       अचिन्हित पूर्णांक irq_start,
				       अचिन्हित पूर्णांक num)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	पूर्णांक rv;

	gc = devm_irq_alloc_generic_chip(chip->dev, "ioh_gpio", 1, irq_start,
					 chip->base, handle_simple_irq);
	अगर (!gc)
		वापस -ENOMEM;

	gc->निजी = chip;
	ct = gc->chip_types;

	ct->chip.irq_mask = ioh_irq_mask;
	ct->chip.irq_unmask = ioh_irq_unmask;
	ct->chip.irq_set_type = ioh_irq_type;
	ct->chip.irq_disable = ioh_irq_disable;
	ct->chip.irq_enable = ioh_irq_enable;

	rv = devm_irq_setup_generic_chip(chip->dev, gc, IRQ_MSK(num),
					 IRQ_GC_INIT_MASK_CACHE,
					 IRQ_NOREQUEST | IRQ_NOPROBE, 0);

	वापस rv;
पूर्ण

अटल पूर्णांक ioh_gpio_probe(काष्ठा pci_dev *pdev,
				    स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक ret;
	पूर्णांक i, j;
	काष्ठा ioh_gpio *chip;
	व्योम __iomem *base;
	व्योम *chip_save;
	पूर्णांक irq_base;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s : pci_enable_device failed", __func__);
		जाओ err_pci_enable;
	पूर्ण

	ret = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pci_request_regions failed-%d", ret);
		जाओ err_request_regions;
	पूर्ण

	base = pci_iomap(pdev, 1, 0);
	अगर (!base) अणु
		dev_err(&pdev->dev, "%s : pci_iomap failed", __func__);
		ret = -ENOMEM;
		जाओ err_iomap;
	पूर्ण

	chip_save = kसुस्मृति(8, माप(*chip), GFP_KERNEL);
	अगर (chip_save == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_kzalloc;
	पूर्ण

	chip = chip_save;
	क्रम (i = 0; i < 8; i++, chip++) अणु
		chip->dev = &pdev->dev;
		chip->base = base;
		chip->reg = chip->base;
		chip->ch = i;
		spin_lock_init(&chip->spinlock);
		ioh_gpio_setup(chip, num_ports[i]);
		ret = gpiochip_add_data(&chip->gpio, chip);
		अगर (ret) अणु
			dev_err(&pdev->dev, "IOH gpio: Failed to register GPIO\n");
			जाओ err_gpiochip_add;
		पूर्ण
	पूर्ण

	chip = chip_save;
	क्रम (j = 0; j < 8; j++, chip++) अणु
		irq_base = devm_irq_alloc_descs(&pdev->dev, -1, IOH_IRQ_BASE,
						num_ports[j], NUMA_NO_NODE);
		अगर (irq_base < 0) अणु
			dev_warn(&pdev->dev,
				"ml_ioh_gpio: Failed to get IRQ base num\n");
			ret = irq_base;
			जाओ err_gpiochip_add;
		पूर्ण
		chip->irq_base = irq_base;

		ret = ioh_gpio_alloc_generic_chip(chip,
						  irq_base, num_ports[j]);
		अगर (ret)
			जाओ err_gpiochip_add;
	पूर्ण

	chip = chip_save;
	ret = devm_request_irq(&pdev->dev, pdev->irq, ioh_gpio_handler,
			       IRQF_SHARED, KBUILD_MODNAME, chip);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev,
			"%s request_irq failed\n", __func__);
		जाओ err_gpiochip_add;
	पूर्ण

	pci_set_drvdata(pdev, chip);

	वापस 0;

err_gpiochip_add:
	chip = chip_save;
	जबतक (--i >= 0) अणु
		gpiochip_हटाओ(&chip->gpio);
		chip++;
	पूर्ण
	kमुक्त(chip_save);

err_kzalloc:
	pci_iounmap(pdev, base);

err_iomap:
	pci_release_regions(pdev);

err_request_regions:
	pci_disable_device(pdev);

err_pci_enable:

	dev_err(&pdev->dev, "%s Failed returns %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम ioh_gpio_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा ioh_gpio *chip = pci_get_drvdata(pdev);
	व्योम *chip_save;

	chip_save = chip;

	क्रम (i = 0; i < 8; i++, chip++)
		gpiochip_हटाओ(&chip->gpio);

	chip = chip_save;
	pci_iounmap(pdev, chip->base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kमुक्त(chip);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ioh_gpio_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	s32 ret;
	काष्ठा ioh_gpio *chip = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->spinlock, flags);
	ioh_gpio_save_reg_conf(chip);
	spin_unlock_irqrestore(&chip->spinlock, flags);

	ret = pci_save_state(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pci_save_state Failed-%d\n", ret);
		वापस ret;
	पूर्ण
	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, PCI_D0);
	ret = pci_enable_wake(pdev, PCI_D0, 1);
	अगर (ret)
		dev_err(&pdev->dev, "pci_enable_wake Failed -%d\n", ret);

	वापस 0;
पूर्ण

अटल पूर्णांक ioh_gpio_resume(काष्ठा pci_dev *pdev)
अणु
	s32 ret;
	काष्ठा ioh_gpio *chip = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	ret = pci_enable_wake(pdev, PCI_D0, 0);

	pci_set_घातer_state(pdev, PCI_D0);
	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "pci_enable_device Failed-%d ", ret);
		वापस ret;
	पूर्ण
	pci_restore_state(pdev);

	spin_lock_irqsave(&chip->spinlock, flags);
	ioग_लिखो32(0x01, &chip->reg->srst);
	ioग_लिखो32(0x00, &chip->reg->srst);
	ioh_gpio_restore_reg_conf(chip);
	spin_unlock_irqrestore(&chip->spinlock, flags);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ioh_gpio_suspend शून्य
#घोषणा ioh_gpio_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id ioh_gpio_pcidev_id[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ROHM, 0x802E) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ioh_gpio_pcidev_id);

अटल काष्ठा pci_driver ioh_gpio_driver = अणु
	.name = "ml_ioh_gpio",
	.id_table = ioh_gpio_pcidev_id,
	.probe = ioh_gpio_probe,
	.हटाओ = ioh_gpio_हटाओ,
	.suspend = ioh_gpio_suspend,
	.resume = ioh_gpio_resume
पूर्ण;

module_pci_driver(ioh_gpio_driver);

MODULE_DESCRIPTION("OKI SEMICONDUCTOR ML-IOH series GPIO Driver");
MODULE_LICENSE("GPL");
