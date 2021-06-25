<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD CS5535/CS5536 GPIO driver
 * Copyright (C) 2006  Advanced Micro Devices, Inc.
 * Copyright (C) 2007-2009  Andres Salomon <dilinger@collabora.co.uk>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/cs5535.h>
#समावेश <यंत्र/msr.h>

#घोषणा DRV_NAME "cs5535-gpio"

/*
 * Some GPIO pins
 *  31-29,23 : reserved (always mask out)
 *  28       : Power Button
 *  26       : PME#
 *  22-16    : LPC
 *  14,15    : SMBus
 *  9,8      : UART1
 *  7        : PCI INTB
 *  3,4      : UART2/DDC
 *  2        : IDE_IRQ0
 *  1        : AC_BEEP
 *  0        : PCI INTA
 *
 * If a mask was not specअगरied, allow all except
 * reserved and Power Button
 */
#घोषणा GPIO_DEFAULT_MASK 0x0F7FFFFF

अटल uदीर्घ mask = GPIO_DEFAULT_MASK;
module_param_named(mask, mask, uदीर्घ, 0444);
MODULE_PARM_DESC(mask, "GPIO channel mask.");

/*
 * FIXME: convert this singleton driver to use the state container
 * design pattern, see Documentation/driver-api/driver-model/design-patterns.rst
 */
अटल काष्ठा cs5535_gpio_chip अणु
	काष्ठा gpio_chip chip;
	resource_माप_प्रकार base;

	काष्ठा platक्रमm_device *pdev;
	spinlock_t lock;
पूर्ण cs5535_gpio_chip;

/*
 * The CS5535/CS5536 GPIOs support a number of extra features not defined
 * by the gpio_chip API, so these are exported.  For a full list of the
 * रेजिस्टरs, see include/linux/cs5535.h.
 */

अटल व्योम errata_outl(काष्ठा cs5535_gpio_chip *chip, u32 val,
		अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ addr = chip->base + 0x80 + reg;

	/*
	 * According to the CS5536 errata (#36), after suspend
	 * a ग_लिखो to the high bank GPIO रेजिस्टर will clear all
	 * non-selected bits; the recommended workaround is a
	 * पढ़ो-modअगरy-ग_लिखो operation.
	 *
	 * Don't apply this errata to the edge status GPIOs, as writing
	 * to their lower bits will clear them.
	 */
	अगर (reg != GPIO_POSITIVE_EDGE_STS && reg != GPIO_NEGATIVE_EDGE_STS) अणु
		अगर (val & 0xffff)
			val |= (inl(addr) & 0xffff); /* ignore the high bits */
		अन्यथा
			val |= (inl(addr) ^ (val >> 16));
	पूर्ण
	outl(val, addr);
पूर्ण

अटल व्योम __cs5535_gpio_set(काष्ठा cs5535_gpio_chip *chip, अचिन्हित offset,
		अचिन्हित पूर्णांक reg)
अणु
	अगर (offset < 16)
		/* low bank रेजिस्टर */
		outl(1 << offset, chip->base + reg);
	अन्यथा
		/* high bank रेजिस्टर */
		errata_outl(chip, 1 << (offset - 16), reg);
पूर्ण

व्योम cs5535_gpio_set(अचिन्हित offset, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	__cs5535_gpio_set(chip, offset, reg);
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_gpio_set);

अटल व्योम __cs5535_gpio_clear(काष्ठा cs5535_gpio_chip *chip, अचिन्हित offset,
		अचिन्हित पूर्णांक reg)
अणु
	अगर (offset < 16)
		/* low bank रेजिस्टर */
		outl(1 << (offset + 16), chip->base + reg);
	अन्यथा
		/* high bank रेजिस्टर */
		errata_outl(chip, 1 << offset, reg);
पूर्ण

व्योम cs5535_gpio_clear(अचिन्हित offset, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	__cs5535_gpio_clear(chip, offset, reg);
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_gpio_clear);

पूर्णांक cs5535_gpio_isset(अचिन्हित offset, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	अचिन्हित दीर्घ flags;
	दीर्घ val;

	spin_lock_irqsave(&chip->lock, flags);
	अगर (offset < 16)
		/* low bank रेजिस्टर */
		val = inl(chip->base + reg);
	अन्यथा अणु
		/* high bank रेजिस्टर */
		val = inl(chip->base + 0x80 + reg);
		offset -= 16;
	पूर्ण
	spin_unlock_irqrestore(&chip->lock, flags);

	वापस (val & (1 << offset)) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_gpio_isset);

पूर्णांक cs5535_gpio_set_irq(अचिन्हित group, अचिन्हित irq)
अणु
	uपूर्णांक32_t lo, hi;

	अगर (group > 7 || irq > 15)
		वापस -EINVAL;

	rdmsr(MSR_PIC_ZSEL_HIGH, lo, hi);

	lo &= ~(0xF << (group * 4));
	lo |= (irq & 0xF) << (group * 4);

	wrmsr(MSR_PIC_ZSEL_HIGH, lo, hi);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_gpio_set_irq);

व्योम cs5535_gpio_setup_event(अचिन्हित offset, पूर्णांक pair, पूर्णांक pme)
अणु
	काष्ठा cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	uपूर्णांक32_t shअगरt = (offset % 8) * 4;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t val;

	अगर (offset >= 24)
		offset = GPIO_MAP_W;
	अन्यथा अगर (offset >= 16)
		offset = GPIO_MAP_Z;
	अन्यथा अगर (offset >= 8)
		offset = GPIO_MAP_Y;
	अन्यथा
		offset = GPIO_MAP_X;

	spin_lock_irqsave(&chip->lock, flags);
	val = inl(chip->base + offset);

	/* Clear whatever was there beक्रमe */
	val &= ~(0xF << shअगरt);

	/* Set the new value */
	val |= ((pair & 7) << shअगरt);

	/* Set the PME bit अगर this is a PME event */
	अगर (pme)
		val |= (1 << (shअगरt + 3));

	outl(val, chip->base + offset);
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(cs5535_gpio_setup_event);

/*
 * Generic gpio_chip API support.
 */

अटल पूर्णांक chip_gpio_request(काष्ठा gpio_chip *c, अचिन्हित offset)
अणु
	काष्ठा cs5535_gpio_chip *chip = gpiochip_get_data(c);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);

	/* check अगर this pin is available */
	अगर ((mask & (1 << offset)) == 0) अणु
		dev_info(&chip->pdev->dev,
			"pin %u is not available (check mask)\n", offset);
		spin_unlock_irqrestore(&chip->lock, flags);
		वापस -EINVAL;
	पूर्ण

	/* disable output aux 1 & 2 on this pin */
	__cs5535_gpio_clear(chip, offset, GPIO_OUTPUT_AUX1);
	__cs5535_gpio_clear(chip, offset, GPIO_OUTPUT_AUX2);

	/* disable input aux 1 on this pin */
	__cs5535_gpio_clear(chip, offset, GPIO_INPUT_AUX1);

	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक chip_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस cs5535_gpio_isset(offset, GPIO_READ_BACK);
पूर्ण

अटल व्योम chip_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	अगर (val)
		cs5535_gpio_set(offset, GPIO_OUTPUT_VAL);
	अन्यथा
		cs5535_gpio_clear(offset, GPIO_OUTPUT_VAL);
पूर्ण

अटल पूर्णांक chip_direction_input(काष्ठा gpio_chip *c, अचिन्हित offset)
अणु
	काष्ठा cs5535_gpio_chip *chip = gpiochip_get_data(c);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	__cs5535_gpio_set(chip, offset, GPIO_INPUT_ENABLE);
	__cs5535_gpio_clear(chip, offset, GPIO_OUTPUT_ENABLE);
	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक chip_direction_output(काष्ठा gpio_chip *c, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा cs5535_gpio_chip *chip = gpiochip_get_data(c);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);

	__cs5535_gpio_set(chip, offset, GPIO_INPUT_ENABLE);
	__cs5535_gpio_set(chip, offset, GPIO_OUTPUT_ENABLE);
	अगर (val)
		__cs5535_gpio_set(chip, offset, GPIO_OUTPUT_VAL);
	अन्यथा
		__cs5535_gpio_clear(chip, offset, GPIO_OUTPUT_VAL);

	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर cs5535_gpio_names[] = अणु
	"GPIO0", "GPIO1", "GPIO2", "GPIO3",
	"GPIO4", "GPIO5", "GPIO6", "GPIO7",
	"GPIO8", "GPIO9", "GPIO10", "GPIO11",
	"GPIO12", "GPIO13", "GPIO14", "GPIO15",
	"GPIO16", "GPIO17", "GPIO18", "GPIO19",
	"GPIO20", "GPIO21", "GPIO22", शून्य,
	"GPIO24", "GPIO25", "GPIO26", "GPIO27",
	"GPIO28", शून्य, शून्य, शून्य,
पूर्ण;

अटल काष्ठा cs5535_gpio_chip cs5535_gpio_chip = अणु
	.chip = अणु
		.owner = THIS_MODULE,
		.label = DRV_NAME,

		.base = 0,
		.ngpio = 32,
		.names = cs5535_gpio_names,
		.request = chip_gpio_request,

		.get = chip_gpio_get,
		.set = chip_gpio_set,

		.direction_input = chip_direction_input,
		.direction_output = chip_direction_output,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cs5535_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक err = -EIO;
	uदीर्घ mask_orig = mask;

	/* There are two ways to get the GPIO base address; one is by
	 * fetching it from MSR_LBAR_GPIO, the other is by पढ़ोing the
	 * PCI BAR info.  The latter method is easier (especially across
	 * dअगरferent architectures), so we'll stick with that क्रम now.  If
	 * it turns out to be unreliable in the face of crappy BIOSes, we
	 * can always go back to using MSRs.. */

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		वापस err;
	पूर्ण

	अगर (!devm_request_region(&pdev->dev, res->start, resource_size(res),
				 pdev->name)) अणु
		dev_err(&pdev->dev, "can't request region\n");
		वापस err;
	पूर्ण

	/* set up the driver-specअगरic काष्ठा */
	cs5535_gpio_chip.base = res->start;
	cs5535_gpio_chip.pdev = pdev;
	spin_lock_init(&cs5535_gpio_chip.lock);

	dev_info(&pdev->dev, "reserved resource region %pR\n", res);

	/* mask out reserved pins */
	mask &= 0x1F7FFFFF;

	/* करो not allow pin 28, Power Button, as there's special handling
	 * in the PMC needed. (note 12, p. 48) */
	mask &= ~(1 << 28);

	अगर (mask_orig != mask)
		dev_info(&pdev->dev, "mask changed from 0x%08lX to 0x%08lX\n",
				mask_orig, mask);

	/* finally, रेजिस्टर with the generic GPIO API */
	वापस devm_gpiochip_add_data(&pdev->dev, &cs5535_gpio_chip.chip,
				      &cs5535_gpio_chip);
पूर्ण

अटल काष्ठा platक्रमm_driver cs5535_gpio_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = cs5535_gpio_probe,
पूर्ण;

module_platक्रमm_driver(cs5535_gpio_driver);

MODULE_AUTHOR("Andres Salomon <dilinger@queued.net>");
MODULE_DESCRIPTION("AMD CS5535/CS5536 GPIO driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
