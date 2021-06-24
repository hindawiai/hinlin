<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

    bt8xx GPIO abuser

    Copyright (C) 2008 Michael Buesch <m@bues.ch>

    Please करो _only_ contact the people listed _above_ with issues related to this driver.
    All the other people listed below are not related to this driver. Their names
    are only here, because this driver is derived from the bt848 driver.


    Derived from the bt848 driver:

    Copyright (C) 1996,97,98 Ralph  Metzler
			   & Marcus Metzler
    (c) 1999-2002 Gerd Knorr

    some v4l2 code lines are taken from Justin's bttv2 driver which is
    (c) 2000 Justin Schoeman

    V4L1 removal from:
    (c) 2005-2006 Nickolay V. Shmyrev

    Fixes to be fully V4L2 compliant by
    (c) 2006 Mauro Carvalho Chehab

    Cropping and overscan support
    Copyright (C) 2005, 2006 Michael H. Schimek
    Sponsored by OPQ Systems AB

*/

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/slab.h>

/* Steal the hardware definitions from the bttv driver. */
#समावेश "../media/pci/bt8xx/bt848.h"


#घोषणा BT8XXGPIO_NR_GPIOS		24 /* We have 24 GPIO pins */


काष्ठा bt8xxgpio अणु
	spinlock_t lock;

	व्योम __iomem *mmio;
	काष्ठा pci_dev *pdev;
	काष्ठा gpio_chip gpio;

#अगर_घोषित CONFIG_PM
	u32 saved_outen;
	u32 saved_data;
#पूर्ण_अगर
पूर्ण;

#घोषणा bgग_लिखो(dat, adr)	ग_लिखोl((dat), bg->mmio+(adr))
#घोषणा bgपढ़ो(adr)		पढ़ोl(bg->mmio+(adr))


अटल पूर्णांक modparam_gpiobase = -1/* dynamic */;
module_param_named(gpiobase, modparam_gpiobase, पूर्णांक, 0444);
MODULE_PARM_DESC(gpiobase, "The GPIO number base. -1 means dynamic, which is the default.");


अटल पूर्णांक bt8xxgpio_gpio_direction_input(काष्ठा gpio_chip *gpio, अचिन्हित nr)
अणु
	काष्ठा bt8xxgpio *bg = gpiochip_get_data(gpio);
	अचिन्हित दीर्घ flags;
	u32 outen, data;

	spin_lock_irqsave(&bg->lock, flags);

	data = bgपढ़ो(BT848_GPIO_DATA);
	data &= ~(1 << nr);
	bgग_लिखो(data, BT848_GPIO_DATA);

	outen = bgपढ़ो(BT848_GPIO_OUT_EN);
	outen &= ~(1 << nr);
	bgग_लिखो(outen, BT848_GPIO_OUT_EN);

	spin_unlock_irqrestore(&bg->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक bt8xxgpio_gpio_get(काष्ठा gpio_chip *gpio, अचिन्हित nr)
अणु
	काष्ठा bt8xxgpio *bg = gpiochip_get_data(gpio);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&bg->lock, flags);
	val = bgपढ़ो(BT848_GPIO_DATA);
	spin_unlock_irqrestore(&bg->lock, flags);

	वापस !!(val & (1 << nr));
पूर्ण

अटल पूर्णांक bt8xxgpio_gpio_direction_output(काष्ठा gpio_chip *gpio,
					अचिन्हित nr, पूर्णांक val)
अणु
	काष्ठा bt8xxgpio *bg = gpiochip_get_data(gpio);
	अचिन्हित दीर्घ flags;
	u32 outen, data;

	spin_lock_irqsave(&bg->lock, flags);

	outen = bgपढ़ो(BT848_GPIO_OUT_EN);
	outen |= (1 << nr);
	bgग_लिखो(outen, BT848_GPIO_OUT_EN);

	data = bgपढ़ो(BT848_GPIO_DATA);
	अगर (val)
		data |= (1 << nr);
	अन्यथा
		data &= ~(1 << nr);
	bgग_लिखो(data, BT848_GPIO_DATA);

	spin_unlock_irqrestore(&bg->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम bt8xxgpio_gpio_set(काष्ठा gpio_chip *gpio,
			    अचिन्हित nr, पूर्णांक val)
अणु
	काष्ठा bt8xxgpio *bg = gpiochip_get_data(gpio);
	अचिन्हित दीर्घ flags;
	u32 data;

	spin_lock_irqsave(&bg->lock, flags);

	data = bgपढ़ो(BT848_GPIO_DATA);
	अगर (val)
		data |= (1 << nr);
	अन्यथा
		data &= ~(1 << nr);
	bgग_लिखो(data, BT848_GPIO_DATA);

	spin_unlock_irqrestore(&bg->lock, flags);
पूर्ण

अटल व्योम bt8xxgpio_gpio_setup(काष्ठा bt8xxgpio *bg)
अणु
	काष्ठा gpio_chip *c = &bg->gpio;

	c->label = dev_name(&bg->pdev->dev);
	c->owner = THIS_MODULE;
	c->direction_input = bt8xxgpio_gpio_direction_input;
	c->get = bt8xxgpio_gpio_get;
	c->direction_output = bt8xxgpio_gpio_direction_output;
	c->set = bt8xxgpio_gpio_set;
	c->dbg_show = शून्य;
	c->base = modparam_gpiobase;
	c->ngpio = BT8XXGPIO_NR_GPIOS;
	c->can_sleep = false;
पूर्ण

अटल पूर्णांक bt8xxgpio_probe(काष्ठा pci_dev *dev,
			स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा bt8xxgpio *bg;
	पूर्णांक err;

	bg = devm_kzalloc(&dev->dev, माप(काष्ठा bt8xxgpio), GFP_KERNEL);
	अगर (!bg)
		वापस -ENOMEM;

	bg->pdev = dev;
	spin_lock_init(&bg->lock);

	err = pci_enable_device(dev);
	अगर (err) अणु
		dev_err(&dev->dev, "can't enable device.\n");
		वापस err;
	पूर्ण
	अगर (!devm_request_mem_region(&dev->dev, pci_resource_start(dev, 0),
				pci_resource_len(dev, 0),
				"bt8xxgpio")) अणु
		dev_warn(&dev->dev, "can't request iomem (0x%llx).\n",
		       (अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev, 0));
		err = -EBUSY;
		जाओ err_disable;
	पूर्ण
	pci_set_master(dev);
	pci_set_drvdata(dev, bg);

	bg->mmio = devm_ioremap(&dev->dev, pci_resource_start(dev, 0), 0x1000);
	अगर (!bg->mmio) अणु
		dev_err(&dev->dev, "ioremap() failed\n");
		err = -EIO;
		जाओ err_disable;
	पूर्ण

	/* Disable पूर्णांकerrupts */
	bgग_लिखो(0, BT848_INT_MASK);

	/* gpio init */
	bgग_लिखो(0, BT848_GPIO_DMA_CTL);
	bgग_लिखो(0, BT848_GPIO_REG_INP);
	bgग_लिखो(0, BT848_GPIO_OUT_EN);

	bt8xxgpio_gpio_setup(bg);
	err = gpiochip_add_data(&bg->gpio, bg);
	अगर (err) अणु
		dev_err(&dev->dev, "failed to register GPIOs\n");
		जाओ err_disable;
	पूर्ण

	वापस 0;

err_disable:
	pci_disable_device(dev);

	वापस err;
पूर्ण

अटल व्योम bt8xxgpio_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा bt8xxgpio *bg = pci_get_drvdata(pdev);

	gpiochip_हटाओ(&bg->gpio);

	bgग_लिखो(0, BT848_INT_MASK);
	bgग_लिखो(~0x0, BT848_INT_STAT);
	bgग_लिखो(0x0, BT848_GPIO_OUT_EN);

	pci_disable_device(pdev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bt8xxgpio_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	काष्ठा bt8xxgpio *bg = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bg->lock, flags);

	bg->saved_outen = bgपढ़ो(BT848_GPIO_OUT_EN);
	bg->saved_data = bgपढ़ो(BT848_GPIO_DATA);

	bgग_लिखो(0, BT848_INT_MASK);
	bgग_लिखो(~0x0, BT848_INT_STAT);
	bgग_लिखो(0x0, BT848_GPIO_OUT_EN);

	spin_unlock_irqrestore(&bg->lock, flags);

	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, pci_choose_state(pdev, state));

	वापस 0;
पूर्ण

अटल पूर्णांक bt8xxgpio_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा bt8xxgpio *bg = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	pci_set_घातer_state(pdev, PCI_D0);
	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;
	pci_restore_state(pdev);

	spin_lock_irqsave(&bg->lock, flags);

	bgग_लिखो(0, BT848_INT_MASK);
	bgग_लिखो(0, BT848_GPIO_DMA_CTL);
	bgग_लिखो(0, BT848_GPIO_REG_INP);
	bgग_लिखो(bg->saved_outen, BT848_GPIO_OUT_EN);
	bgग_लिखो(bg->saved_data & bg->saved_outen,
		BT848_GPIO_DATA);

	spin_unlock_irqrestore(&bg->lock, flags);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा bt8xxgpio_suspend शून्य
#घोषणा bt8xxgpio_resume शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा pci_device_id bt8xxgpio_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROOKTREE, PCI_DEVICE_ID_BT848) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROOKTREE, PCI_DEVICE_ID_BT849) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROOKTREE, PCI_DEVICE_ID_BT878) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_BROOKTREE, PCI_DEVICE_ID_BT879) पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, bt8xxgpio_pci_tbl);

अटल काष्ठा pci_driver bt8xxgpio_pci_driver = अणु
	.name		= "bt8xxgpio",
	.id_table	= bt8xxgpio_pci_tbl,
	.probe		= bt8xxgpio_probe,
	.हटाओ		= bt8xxgpio_हटाओ,
	.suspend	= bt8xxgpio_suspend,
	.resume		= bt8xxgpio_resume,
पूर्ण;

module_pci_driver(bt8xxgpio_pci_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael Buesch");
MODULE_DESCRIPTION("Abuse a BT8xx framegrabber card as generic GPIO card");
