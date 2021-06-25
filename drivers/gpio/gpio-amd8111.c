<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GPIO driver क्रम AMD 8111 south bridges
 *
 * Copyright (c) 2012 Dmitry Eremin-Solenikov
 *
 * Based on the AMD RNG driver:
 * Copyright 2005 (c) MontaVista Software, Inc.
 * with the majority of the code coming from:
 *
 * Hardware driver क्रम the Intel/AMD/VIA Ranकरोm Number Generators (RNG)
 * (c) Copyright 2003 Red Hat Inc <jgarzik@redhat.com>
 *
 * derived from
 *
 * Hardware driver क्रम the AMD 768 Ranकरोm Number Generator (RNG)
 * (c) Copyright 2001 Red Hat Inc
 *
 * derived from
 *
 * Hardware driver क्रम Intel i810 Ranकरोm Number Generator (RNG)
 * Copyright 2000,2001 Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2000,2001 Philipp Rumpf <prumpf@mandrakesoft.com>
 */
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>

#घोषणा PMBASE_OFFSET 0xb0
#घोषणा PMBASE_SIZE   0x30

#घोषणा AMD_REG_GPIO(i) (0x10 + (i))

#घोषणा AMD_GPIO_LTCH_STS	0x40 /* Latch status, w1 */
#घोषणा AMD_GPIO_RTIN		0x20 /* Real Time in, ro */
#घोषणा AMD_GPIO_DEBOUNCE	0x10 /* Debounce, rw */
#घोषणा AMD_GPIO_MODE_MASK	0x0c /* Pin Mode Select, rw */
#घोषणा AMD_GPIO_MODE_IN	0x00
#घोषणा AMD_GPIO_MODE_OUT	0x04
/* Enable alternative (e.g. clkout, IRQ, etc) function of the pin */
#घोषणा AMD_GPIO_MODE_ALTFN	0x08 /* Or 0x09 */
#घोषणा AMD_GPIO_X_MASK		0x03 /* In/Out specअगरic, rw */
#घोषणा AMD_GPIO_X_IN_ACTIVEHI	0x01 /* Active High */
#घोषणा AMD_GPIO_X_IN_LATCH	0x02 /* Latched version is selected */
#घोषणा AMD_GPIO_X_OUT_LOW	0x00
#घोषणा AMD_GPIO_X_OUT_HI	0x01
#घोषणा AMD_GPIO_X_OUT_CLK0	0x02
#घोषणा AMD_GPIO_X_OUT_CLK1	0x03

/*
 * Data क्रम PCI driver पूर्णांकerface
 *
 * This data only exists क्रम exporting the supported
 * PCI ids via MODULE_DEVICE_TABLE.  We करो not actually
 * रेजिस्टर a pci_driver, because someone अन्यथा might one day
 * want to रेजिस्टर another driver on the same PCI id.
 */
अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_8111_SMBUS), 0 पूर्ण,
	अणु 0, पूर्ण,	/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_tbl);

काष्ठा amd_gpio अणु
	काष्ठा gpio_chip	chip;
	u32			pmbase;
	व्योम __iomem		*pm;
	काष्ठा pci_dev		*pdev;
	spinlock_t		lock; /* guards hw रेजिस्टरs and orig table */
	u8			orig[32];
पूर्ण;

अटल पूर्णांक amd_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा amd_gpio *agp = gpiochip_get_data(chip);

	agp->orig[offset] = ioपढ़ो8(agp->pm + AMD_REG_GPIO(offset)) &
		(AMD_GPIO_DEBOUNCE | AMD_GPIO_MODE_MASK | AMD_GPIO_X_MASK);

	dev_dbg(&agp->pdev->dev, "Requested gpio %d, data %x\n", offset, agp->orig[offset]);

	वापस 0;
पूर्ण

अटल व्योम amd_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा amd_gpio *agp = gpiochip_get_data(chip);

	dev_dbg(&agp->pdev->dev, "Freed gpio %d, data %x\n", offset, agp->orig[offset]);

	ioग_लिखो8(agp->orig[offset], agp->pm + AMD_REG_GPIO(offset));
पूर्ण

अटल व्योम amd_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा amd_gpio *agp = gpiochip_get_data(chip);
	u8 temp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&agp->lock, flags);
	temp = ioपढ़ो8(agp->pm + AMD_REG_GPIO(offset));
	temp = (temp & AMD_GPIO_DEBOUNCE) | AMD_GPIO_MODE_OUT | (value ? AMD_GPIO_X_OUT_HI : AMD_GPIO_X_OUT_LOW);
	ioग_लिखो8(temp, agp->pm + AMD_REG_GPIO(offset));
	spin_unlock_irqrestore(&agp->lock, flags);

	dev_dbg(&agp->pdev->dev, "Setting gpio %d, value %d, reg=%02x\n", offset, !!value, temp);
पूर्ण

अटल पूर्णांक amd_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा amd_gpio *agp = gpiochip_get_data(chip);
	u8 temp;

	temp = ioपढ़ो8(agp->pm + AMD_REG_GPIO(offset));

	dev_dbg(&agp->pdev->dev, "Getting gpio %d, reg=%02x\n", offset, temp);

	वापस (temp & AMD_GPIO_RTIN) ? 1 : 0;
पूर्ण

अटल पूर्णांक amd_gpio_dirout(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा amd_gpio *agp = gpiochip_get_data(chip);
	u8 temp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&agp->lock, flags);
	temp = ioपढ़ो8(agp->pm + AMD_REG_GPIO(offset));
	temp = (temp & AMD_GPIO_DEBOUNCE) | AMD_GPIO_MODE_OUT | (value ? AMD_GPIO_X_OUT_HI : AMD_GPIO_X_OUT_LOW);
	ioग_लिखो8(temp, agp->pm + AMD_REG_GPIO(offset));
	spin_unlock_irqrestore(&agp->lock, flags);

	dev_dbg(&agp->pdev->dev, "Dirout gpio %d, value %d, reg=%02x\n", offset, !!value, temp);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_gpio_dirin(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा amd_gpio *agp = gpiochip_get_data(chip);
	u8 temp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&agp->lock, flags);
	temp = ioपढ़ो8(agp->pm + AMD_REG_GPIO(offset));
	temp = (temp & AMD_GPIO_DEBOUNCE) | AMD_GPIO_MODE_IN;
	ioग_लिखो8(temp, agp->pm + AMD_REG_GPIO(offset));
	spin_unlock_irqrestore(&agp->lock, flags);

	dev_dbg(&agp->pdev->dev, "Dirin gpio %d, reg=%02x\n", offset, temp);

	वापस 0;
पूर्ण

अटल काष्ठा amd_gpio gp = अणु
	.chip = अणु
		.label		= "AMD GPIO",
		.owner		= THIS_MODULE,
		.base		= -1,
		.ngpio		= 32,
		.request	= amd_gpio_request,
		.मुक्त		= amd_gpio_मुक्त,
		.set		= amd_gpio_set,
		.get		= amd_gpio_get,
		.direction_output = amd_gpio_dirout,
		.direction_input = amd_gpio_dirin,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init amd_gpio_init(व्योम)
अणु
	पूर्णांक err = -ENODEV;
	काष्ठा pci_dev *pdev = शून्य;
	स्थिर काष्ठा pci_device_id *ent;

	/* We look क्रम our device - AMD South Bridge
	 * I करोn't know about a प्रणाली with two such bridges,
	 * so we can assume that there is max. one device.
	 *
	 * We can't use plain pci_driver mechanism,
	 * as the device is really a multiple function device,
	 * मुख्य driver that binds to the pci_device is an smbus
	 * driver and have to find & bind to the device this way.
	 */
	क्रम_each_pci_dev(pdev) अणु
		ent = pci_match_id(pci_tbl, pdev);
		अगर (ent)
			जाओ found;
	पूर्ण
	/* Device not found. */
	जाओ out;

found:
	err = pci_पढ़ो_config_dword(pdev, 0x58, &gp.pmbase);
	अगर (err)
		जाओ out;
	err = -EIO;
	gp.pmbase &= 0x0000FF00;
	अगर (gp.pmbase == 0)
		जाओ out;
	अगर (!devm_request_region(&pdev->dev, gp.pmbase + PMBASE_OFFSET,
		PMBASE_SIZE, "AMD GPIO")) अणु
		dev_err(&pdev->dev, "AMD GPIO region 0x%x already in use!\n",
			gp.pmbase + PMBASE_OFFSET);
		err = -EBUSY;
		जाओ out;
	पूर्ण
	gp.pm = ioport_map(gp.pmbase + PMBASE_OFFSET, PMBASE_SIZE);
	अगर (!gp.pm) अणु
		dev_err(&pdev->dev, "Couldn't map io port into io memory\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	gp.pdev = pdev;
	gp.chip.parent = &pdev->dev;

	spin_lock_init(&gp.lock);

	dev_info(&pdev->dev, "AMD-8111 GPIO detected\n");
	err = gpiochip_add_data(&gp.chip, &gp);
	अगर (err) अणु
		dev_err(&pdev->dev, "GPIO registering failed (%d)\n", err);
		ioport_unmap(gp.pm);
		जाओ out;
	पूर्ण
out:
	वापस err;
पूर्ण

अटल व्योम __निकास amd_gpio_निकास(व्योम)
अणु
	gpiochip_हटाओ(&gp.chip);
	ioport_unmap(gp.pm);
पूर्ण

module_init(amd_gpio_init);
module_निकास(amd_gpio_निकास);

MODULE_AUTHOR("The Linux Kernel team");
MODULE_DESCRIPTION("GPIO driver for AMD chipsets");
MODULE_LICENSE("GPL");
