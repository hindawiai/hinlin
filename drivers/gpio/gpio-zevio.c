<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO controller in LSI ZEVIO SoCs.
 *
 * Author: Fabian Vogt <fabian@ritter-vogt.de>
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/driver.h>

/*
 * Memory layout:
 * This chip has four gpio sections, each controls 8 GPIOs.
 * Bit 0 in section 0 is GPIO 0, bit 2 in section 1 is GPIO 10.
 * Disclaimer: Reverse engineered!
 * For more inक्रमmation refer to:
 * http://hackspire.unsads.com/wiki/index.php/Memory-mapped_I/O_ports#90000000_-_General_Purpose_I.2FO_.28GPIO.29
 *
 * 0x00-0x3F: Section 0
 *     +0x00: Masked पूर्णांकerrupt status (पढ़ो-only)
 *     +0x04: R: Interrupt status W: Reset पूर्णांकerrupt status
 *     +0x08: R: Interrupt mask W: Mask पूर्णांकerrupt
 *     +0x0C: W: Unmask पूर्णांकerrupt (ग_लिखो-only)
 *     +0x10: Direction: I/O=1/0
 *     +0x14: Output
 *     +0x18: Input (पढ़ो-only)
 *     +0x20: R: Level पूर्णांकerrupt W: Set as level पूर्णांकerrupt
 * 0x40-0x7F: Section 1
 * 0x80-0xBF: Section 2
 * 0xC0-0xFF: Section 3
 */

#घोषणा ZEVIO_GPIO_SECTION_SIZE			0x40

/* Offsets to various रेजिस्टरs */
#घोषणा ZEVIO_GPIO_INT_MASKED_STATUS	0x00
#घोषणा ZEVIO_GPIO_INT_STATUS		0x04
#घोषणा ZEVIO_GPIO_INT_UNMASK		0x08
#घोषणा ZEVIO_GPIO_INT_MASK		0x0C
#घोषणा ZEVIO_GPIO_सूचीECTION		0x10
#घोषणा ZEVIO_GPIO_OUTPUT		0x14
#घोषणा ZEVIO_GPIO_INPUT			0x18
#घोषणा ZEVIO_GPIO_INT_STICKY		0x20

/* Bit number of GPIO in its section */
#घोषणा ZEVIO_GPIO_BIT(gpio) (gpio&7)

काष्ठा zevio_gpio अणु
	spinlock_t		lock;
	काष्ठा of_mm_gpio_chip	chip;
पूर्ण;

अटल अंतरभूत u32 zevio_gpio_port_get(काष्ठा zevio_gpio *c, अचिन्हित pin,
					अचिन्हित port_offset)
अणु
	अचिन्हित section_offset = ((pin >> 3) & 3)*ZEVIO_GPIO_SECTION_SIZE;
	वापस पढ़ोl(IOMEM(c->chip.regs + section_offset + port_offset));
पूर्ण

अटल अंतरभूत व्योम zevio_gpio_port_set(काष्ठा zevio_gpio *c, अचिन्हित pin,
					अचिन्हित port_offset, u32 val)
अणु
	अचिन्हित section_offset = ((pin >> 3) & 3)*ZEVIO_GPIO_SECTION_SIZE;
	ग_लिखोl(val, IOMEM(c->chip.regs + section_offset + port_offset));
पूर्ण

/* Functions क्रम काष्ठा gpio_chip */
अटल पूर्णांक zevio_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा zevio_gpio *controller = gpiochip_get_data(chip);
	u32 val, dir;

	spin_lock(&controller->lock);
	dir = zevio_gpio_port_get(controller, pin, ZEVIO_GPIO_सूचीECTION);
	अगर (dir & BIT(ZEVIO_GPIO_BIT(pin)))
		val = zevio_gpio_port_get(controller, pin, ZEVIO_GPIO_INPUT);
	अन्यथा
		val = zevio_gpio_port_get(controller, pin, ZEVIO_GPIO_OUTPUT);
	spin_unlock(&controller->lock);

	वापस (val >> ZEVIO_GPIO_BIT(pin)) & 0x1;
पूर्ण

अटल व्योम zevio_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित pin, पूर्णांक value)
अणु
	काष्ठा zevio_gpio *controller = gpiochip_get_data(chip);
	u32 val;

	spin_lock(&controller->lock);
	val = zevio_gpio_port_get(controller, pin, ZEVIO_GPIO_OUTPUT);
	अगर (value)
		val |= BIT(ZEVIO_GPIO_BIT(pin));
	अन्यथा
		val &= ~BIT(ZEVIO_GPIO_BIT(pin));

	zevio_gpio_port_set(controller, pin, ZEVIO_GPIO_OUTPUT, val);
	spin_unlock(&controller->lock);
पूर्ण

अटल पूर्णांक zevio_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	काष्ठा zevio_gpio *controller = gpiochip_get_data(chip);
	u32 val;

	spin_lock(&controller->lock);

	val = zevio_gpio_port_get(controller, pin, ZEVIO_GPIO_सूचीECTION);
	val |= BIT(ZEVIO_GPIO_BIT(pin));
	zevio_gpio_port_set(controller, pin, ZEVIO_GPIO_सूचीECTION, val);

	spin_unlock(&controller->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक zevio_gpio_direction_output(काष्ठा gpio_chip *chip,
				       अचिन्हित pin, पूर्णांक value)
अणु
	काष्ठा zevio_gpio *controller = gpiochip_get_data(chip);
	u32 val;

	spin_lock(&controller->lock);
	val = zevio_gpio_port_get(controller, pin, ZEVIO_GPIO_OUTPUT);
	अगर (value)
		val |= BIT(ZEVIO_GPIO_BIT(pin));
	अन्यथा
		val &= ~BIT(ZEVIO_GPIO_BIT(pin));

	zevio_gpio_port_set(controller, pin, ZEVIO_GPIO_OUTPUT, val);
	val = zevio_gpio_port_get(controller, pin, ZEVIO_GPIO_सूचीECTION);
	val &= ~BIT(ZEVIO_GPIO_BIT(pin));
	zevio_gpio_port_set(controller, pin, ZEVIO_GPIO_सूचीECTION, val);

	spin_unlock(&controller->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक zevio_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	/*
	 * TODO: Implement IRQs.
	 * Not implemented yet due to weird lockups
	 */

	वापस -ENXIO;
पूर्ण

अटल स्थिर काष्ठा gpio_chip zevio_gpio_chip = अणु
	.direction_input	= zevio_gpio_direction_input,
	.direction_output	= zevio_gpio_direction_output,
	.set			= zevio_gpio_set,
	.get			= zevio_gpio_get,
	.to_irq			= zevio_gpio_to_irq,
	.base			= 0,
	.owner			= THIS_MODULE,
	.ngpio			= 32,
	.of_gpio_n_cells	= 2,
पूर्ण;

/* Initialization */
अटल पूर्णांक zevio_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zevio_gpio *controller;
	पूर्णांक status, i;

	controller = devm_kzalloc(&pdev->dev, माप(*controller), GFP_KERNEL);
	अगर (!controller)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, controller);

	/* Copy our reference */
	controller->chip.gc = zevio_gpio_chip;
	controller->chip.gc.parent = &pdev->dev;

	status = of_mm_gpiochip_add_data(pdev->dev.of_node,
					 &(controller->chip),
					 controller);
	अगर (status) अणु
		dev_err(&pdev->dev, "failed to add gpiochip: %d\n", status);
		वापस status;
	पूर्ण

	spin_lock_init(&controller->lock);

	/* Disable पूर्णांकerrupts, they only cause errors */
	क्रम (i = 0; i < controller->chip.gc.ngpio; i += 8)
		zevio_gpio_port_set(controller, i, ZEVIO_GPIO_INT_MASK, 0xFF);

	dev_dbg(controller->chip.gc.parent, "ZEVIO GPIO controller set up!\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id zevio_gpio_of_match[] = अणु
	अणु .compatible = "lsi,zevio-gpio", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver zevio_gpio_driver = अणु
	.driver		= अणु
		.name	= "gpio-zevio",
		.of_match_table = zevio_gpio_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= zevio_gpio_probe,
पूर्ण;
builtin_platक्रमm_driver(zevio_gpio_driver);
