<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम NEC VR4100 series General-purpose I/O Unit.
 *
 *  Copyright (C) 2002 MontaVista Software Inc.
 *	Author: Yoichi Yuasa <source@mvista.com>
 *  Copyright (C) 2003-2009  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/vr41xx/giu.h>
#समावेश <यंत्र/vr41xx/irq.h>
#समावेश <यंत्र/vr41xx/vr41xx.h>

MODULE_AUTHOR("Yoichi Yuasa <yuasa@linux-mips.org>");
MODULE_DESCRIPTION("NEC VR4100 series General-purpose I/O Unit driver");
MODULE_LICENSE("GPL");

#घोषणा GIUIOSELL	0x00
#घोषणा GIUIOSELH	0x02
#घोषणा GIUPIODL	0x04
#घोषणा GIUPIODH	0x06
#घोषणा GIUINTSTATL	0x08
#घोषणा GIUINTSTATH	0x0a
#घोषणा GIUINTENL	0x0c
#घोषणा GIUINTENH	0x0e
#घोषणा GIUINTTYPL	0x10
#घोषणा GIUINTTYPH	0x12
#घोषणा GIUINTALSELL	0x14
#घोषणा GIUINTALSELH	0x16
#घोषणा GIUINTHTSELL	0x18
#घोषणा GIUINTHTSELH	0x1a
#घोषणा GIUPODATL	0x1c
#घोषणा GIUPODATEN	0x1c
#घोषणा GIUPODATH	0x1e
 #घोषणा PIOEN0		0x0100
 #घोषणा PIOEN1		0x0200
#घोषणा GIUPODAT	0x1e
#घोषणा GIUFEDGEINHL	0x20
#घोषणा GIUFEDGEINHH	0x22
#घोषणा GIUREDGEINHL	0x24
#घोषणा GIUREDGEINHH	0x26

#घोषणा GIUUSEUPDN	0x1e0
#घोषणा GIUTERMUPDN	0x1e2

#घोषणा GPIO_HAS_PULLUPDOWN_IO		0x0001
#घोषणा GPIO_HAS_OUTPUT_ENABLE		0x0002
#घोषणा GPIO_HAS_INTERRUPT_EDGE_SELECT	0x0100

क्रमागत अणु
	GPIO_INPUT,
	GPIO_OUTPUT,
पूर्ण;

अटल DEFINE_SPINLOCK(giu_lock);
अटल अचिन्हित दीर्घ giu_flags;

अटल व्योम __iomem *giu_base;
अटल काष्ठा gpio_chip vr41xx_gpio_chip;

#घोषणा giu_पढ़ो(offset)		पढ़ोw(giu_base + (offset))
#घोषणा giu_ग_लिखो(offset, value)	ग_लिखोw((value), giu_base + (offset))

#घोषणा GPIO_PIN_OF_IRQ(irq)	((irq) - GIU_IRQ_BASE)
#घोषणा GIUINT_HIGH_OFFSET	16
#घोषणा GIUINT_HIGH_MAX		32

अटल अंतरभूत u16 giu_set(u16 offset, u16 set)
अणु
	u16 data;

	data = giu_पढ़ो(offset);
	data |= set;
	giu_ग_लिखो(offset, data);

	वापस data;
पूर्ण

अटल अंतरभूत u16 giu_clear(u16 offset, u16 clear)
अणु
	u16 data;

	data = giu_पढ़ो(offset);
	data &= ~clear;
	giu_ग_लिखो(offset, data);

	वापस data;
पूर्ण

अटल व्योम ack_giuपूर्णांक_low(काष्ठा irq_data *d)
अणु
	giu_ग_लिखो(GIUINTSTATL, 1 << GPIO_PIN_OF_IRQ(d->irq));
पूर्ण

अटल व्योम mask_giuपूर्णांक_low(काष्ठा irq_data *d)
अणु
	giu_clear(GIUINTENL, 1 << GPIO_PIN_OF_IRQ(d->irq));
पूर्ण

अटल व्योम mask_ack_giuपूर्णांक_low(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक pin;

	pin = GPIO_PIN_OF_IRQ(d->irq);
	giu_clear(GIUINTENL, 1 << pin);
	giu_ग_लिखो(GIUINTSTATL, 1 << pin);
पूर्ण

अटल व्योम unmask_giuपूर्णांक_low(काष्ठा irq_data *d)
अणु
	giu_set(GIUINTENL, 1 << GPIO_PIN_OF_IRQ(d->irq));
पूर्ण

अटल अचिन्हित पूर्णांक startup_giuपूर्णांक(काष्ठा irq_data *data)
अणु
	पूर्णांक ret;

	ret = gpiochip_lock_as_irq(&vr41xx_gpio_chip, irqd_to_hwirq(data));
	अगर (ret) अणु
		dev_err(vr41xx_gpio_chip.parent,
			"unable to lock HW IRQ %lu for IRQ\n",
			data->hwirq);
		वापस ret;
	पूर्ण

	/* Satisfy the .enable semantics by unmasking the line */
	unmask_giuपूर्णांक_low(data);
	वापस 0;
पूर्ण

अटल व्योम shutकरोwn_giuपूर्णांक(काष्ठा irq_data *data)
अणु
	mask_giuपूर्णांक_low(data);
	gpiochip_unlock_as_irq(&vr41xx_gpio_chip, data->hwirq);
पूर्ण

अटल काष्ठा irq_chip giuपूर्णांक_low_irq_chip = अणु
	.name		= "GIUINTL",
	.irq_ack	= ack_giuपूर्णांक_low,
	.irq_mask	= mask_giuपूर्णांक_low,
	.irq_mask_ack	= mask_ack_giuपूर्णांक_low,
	.irq_unmask	= unmask_giuपूर्णांक_low,
	.irq_startup	= startup_giuपूर्णांक,
	.irq_shutकरोwn	= shutकरोwn_giuपूर्णांक,
पूर्ण;

अटल व्योम ack_giuपूर्णांक_high(काष्ठा irq_data *d)
अणु
	giu_ग_लिखो(GIUINTSTATH,
		  1 << (GPIO_PIN_OF_IRQ(d->irq) - GIUINT_HIGH_OFFSET));
पूर्ण

अटल व्योम mask_giuपूर्णांक_high(काष्ठा irq_data *d)
अणु
	giu_clear(GIUINTENH, 1 << (GPIO_PIN_OF_IRQ(d->irq) - GIUINT_HIGH_OFFSET));
पूर्ण

अटल व्योम mask_ack_giuपूर्णांक_high(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक pin;

	pin = GPIO_PIN_OF_IRQ(d->irq) - GIUINT_HIGH_OFFSET;
	giu_clear(GIUINTENH, 1 << pin);
	giu_ग_लिखो(GIUINTSTATH, 1 << pin);
पूर्ण

अटल व्योम unmask_giuपूर्णांक_high(काष्ठा irq_data *d)
अणु
	giu_set(GIUINTENH, 1 << (GPIO_PIN_OF_IRQ(d->irq) - GIUINT_HIGH_OFFSET));
पूर्ण

अटल काष्ठा irq_chip giuपूर्णांक_high_irq_chip = अणु
	.name		= "GIUINTH",
	.irq_ack	= ack_giuपूर्णांक_high,
	.irq_mask	= mask_giuपूर्णांक_high,
	.irq_mask_ack	= mask_ack_giuपूर्णांक_high,
	.irq_unmask	= unmask_giuपूर्णांक_high,
पूर्ण;

अटल पूर्णांक giu_get_irq(अचिन्हित पूर्णांक irq)
अणु
	u16 pendl, pendh, maskl, maskh;
	पूर्णांक i;

	pendl = giu_पढ़ो(GIUINTSTATL);
	pendh = giu_पढ़ो(GIUINTSTATH);
	maskl = giu_पढ़ो(GIUINTENL);
	maskh = giu_पढ़ो(GIUINTENH);

	maskl &= pendl;
	maskh &= pendh;

	अगर (maskl) अणु
		क्रम (i = 0; i < 16; i++) अणु
			अगर (maskl & (1 << i))
				वापस GIU_IRQ(i);
		पूर्ण
	पूर्ण अन्यथा अगर (maskh) अणु
		क्रम (i = 0; i < 16; i++) अणु
			अगर (maskh & (1 << i))
				वापस GIU_IRQ(i + GIUINT_HIGH_OFFSET);
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_ERR "spurious GIU interrupt: %04x(%04x),%04x(%04x)\n",
	       maskl, pendl, maskh, pendh);

	atomic_inc(&irq_err_count);

	वापस -EINVAL;
पूर्ण

व्योम vr41xx_set_irq_trigger(अचिन्हित पूर्णांक pin, irq_trigger_t trigger,
			    irq_संकेत_t संकेत)
अणु
	u16 mask;

	अगर (pin < GIUINT_HIGH_OFFSET) अणु
		mask = 1 << pin;
		अगर (trigger != IRQ_TRIGGER_LEVEL) अणु
			giu_set(GIUINTTYPL, mask);
			अगर (संकेत == IRQ_SIGNAL_HOLD)
				giu_set(GIUINTHTSELL, mask);
			अन्यथा
				giu_clear(GIUINTHTSELL, mask);
			अगर (giu_flags & GPIO_HAS_INTERRUPT_EDGE_SELECT) अणु
				चयन (trigger) अणु
				हाल IRQ_TRIGGER_EDGE_FALLING:
					giu_set(GIUFEDGEINHL, mask);
					giu_clear(GIUREDGEINHL, mask);
					अवरोध;
				हाल IRQ_TRIGGER_EDGE_RISING:
					giu_clear(GIUFEDGEINHL, mask);
					giu_set(GIUREDGEINHL, mask);
					अवरोध;
				शेष:
					giu_set(GIUFEDGEINHL, mask);
					giu_set(GIUREDGEINHL, mask);
					अवरोध;
				पूर्ण
			पूर्ण
			irq_set_chip_and_handler(GIU_IRQ(pin),
						 &giuपूर्णांक_low_irq_chip,
						 handle_edge_irq);
		पूर्ण अन्यथा अणु
			giu_clear(GIUINTTYPL, mask);
			giu_clear(GIUINTHTSELL, mask);
			irq_set_chip_and_handler(GIU_IRQ(pin),
						 &giuपूर्णांक_low_irq_chip,
						 handle_level_irq);
		पूर्ण
		giu_ग_लिखो(GIUINTSTATL, mask);
	पूर्ण अन्यथा अगर (pin < GIUINT_HIGH_MAX) अणु
		mask = 1 << (pin - GIUINT_HIGH_OFFSET);
		अगर (trigger != IRQ_TRIGGER_LEVEL) अणु
			giu_set(GIUINTTYPH, mask);
			अगर (संकेत == IRQ_SIGNAL_HOLD)
				giu_set(GIUINTHTSELH, mask);
			अन्यथा
				giu_clear(GIUINTHTSELH, mask);
			अगर (giu_flags & GPIO_HAS_INTERRUPT_EDGE_SELECT) अणु
				चयन (trigger) अणु
				हाल IRQ_TRIGGER_EDGE_FALLING:
					giu_set(GIUFEDGEINHH, mask);
					giu_clear(GIUREDGEINHH, mask);
					अवरोध;
				हाल IRQ_TRIGGER_EDGE_RISING:
					giu_clear(GIUFEDGEINHH, mask);
					giu_set(GIUREDGEINHH, mask);
					अवरोध;
				शेष:
					giu_set(GIUFEDGEINHH, mask);
					giu_set(GIUREDGEINHH, mask);
					अवरोध;
				पूर्ण
			पूर्ण
			irq_set_chip_and_handler(GIU_IRQ(pin),
						 &giuपूर्णांक_high_irq_chip,
						 handle_edge_irq);
		पूर्ण अन्यथा अणु
			giu_clear(GIUINTTYPH, mask);
			giu_clear(GIUINTHTSELH, mask);
			irq_set_chip_and_handler(GIU_IRQ(pin),
						 &giuपूर्णांक_high_irq_chip,
						 handle_level_irq);
		पूर्ण
		giu_ग_लिखो(GIUINTSTATH, mask);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vr41xx_set_irq_trigger);

व्योम vr41xx_set_irq_level(अचिन्हित पूर्णांक pin, irq_level_t level)
अणु
	u16 mask;

	अगर (pin < GIUINT_HIGH_OFFSET) अणु
		mask = 1 << pin;
		अगर (level == IRQ_LEVEL_HIGH)
			giu_set(GIUINTALSELL, mask);
		अन्यथा
			giu_clear(GIUINTALSELL, mask);
		giu_ग_लिखो(GIUINTSTATL, mask);
	पूर्ण अन्यथा अगर (pin < GIUINT_HIGH_MAX) अणु
		mask = 1 << (pin - GIUINT_HIGH_OFFSET);
		अगर (level == IRQ_LEVEL_HIGH)
			giu_set(GIUINTALSELH, mask);
		अन्यथा
			giu_clear(GIUINTALSELH, mask);
		giu_ग_लिखो(GIUINTSTATH, mask);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vr41xx_set_irq_level);

अटल पूर्णांक giu_set_direction(काष्ठा gpio_chip *chip, अचिन्हित pin, पूर्णांक dir)
अणु
	u16 offset, mask, reg;
	अचिन्हित दीर्घ flags;

	अगर (pin >= chip->ngpio)
		वापस -EINVAL;

	अगर (pin < 16) अणु
		offset = GIUIOSELL;
		mask = 1 << pin;
	पूर्ण अन्यथा अगर (pin < 32) अणु
		offset = GIUIOSELH;
		mask = 1 << (pin - 16);
	पूर्ण अन्यथा अणु
		अगर (giu_flags & GPIO_HAS_OUTPUT_ENABLE) अणु
			offset = GIUPODATEN;
			mask = 1 << (pin - 32);
		पूर्ण अन्यथा अणु
			चयन (pin) अणु
			हाल 48:
				offset = GIUPODATH;
				mask = PIOEN0;
				अवरोध;
			हाल 49:
				offset = GIUPODATH;
				mask = PIOEN1;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&giu_lock, flags);

	reg = giu_पढ़ो(offset);
	अगर (dir == GPIO_OUTPUT)
		reg |= mask;
	अन्यथा
		reg &= ~mask;
	giu_ग_लिखो(offset, reg);

	spin_unlock_irqrestore(&giu_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक vr41xx_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित pin)
अणु
	u16 reg, mask;

	अगर (pin >= chip->ngpio)
		वापस -EINVAL;

	अगर (pin < 16) अणु
		reg = giu_पढ़ो(GIUPIODL);
		mask = 1 << pin;
	पूर्ण अन्यथा अगर (pin < 32) अणु
		reg = giu_पढ़ो(GIUPIODH);
		mask = 1 << (pin - 16);
	पूर्ण अन्यथा अगर (pin < 48) अणु
		reg = giu_पढ़ो(GIUPODATL);
		mask = 1 << (pin - 32);
	पूर्ण अन्यथा अणु
		reg = giu_पढ़ो(GIUPODATH);
		mask = 1 << (pin - 48);
	पूर्ण

	अगर (reg & mask)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम vr41xx_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित pin,
			    पूर्णांक value)
अणु
	u16 offset, mask, reg;
	अचिन्हित दीर्घ flags;

	अगर (pin >= chip->ngpio)
		वापस;

	अगर (pin < 16) अणु
		offset = GIUPIODL;
		mask = 1 << pin;
	पूर्ण अन्यथा अगर (pin < 32) अणु
		offset = GIUPIODH;
		mask = 1 << (pin - 16);
	पूर्ण अन्यथा अगर (pin < 48) अणु
		offset = GIUPODATL;
		mask = 1 << (pin - 32);
	पूर्ण अन्यथा अणु
		offset = GIUPODATH;
		mask = 1 << (pin - 48);
	पूर्ण

	spin_lock_irqsave(&giu_lock, flags);

	reg = giu_पढ़ो(offset);
	अगर (value)
		reg |= mask;
	अन्यथा
		reg &= ~mask;
	giu_ग_लिखो(offset, reg);

	spin_unlock_irqrestore(&giu_lock, flags);
पूर्ण


अटल पूर्णांक vr41xx_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस giu_set_direction(chip, offset, GPIO_INPUT);
पूर्ण

अटल पूर्णांक vr41xx_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				पूर्णांक value)
अणु
	vr41xx_gpio_set(chip, offset, value);

	वापस giu_set_direction(chip, offset, GPIO_OUTPUT);
पूर्ण

अटल पूर्णांक vr41xx_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अगर (offset >= chip->ngpio)
		वापस -EINVAL;

	वापस GIU_IRQ_BASE + offset;
पूर्ण

अटल काष्ठा gpio_chip vr41xx_gpio_chip = अणु
	.label			= "vr41xx",
	.owner			= THIS_MODULE,
	.direction_input	= vr41xx_gpio_direction_input,
	.get			= vr41xx_gpio_get,
	.direction_output	= vr41xx_gpio_direction_output,
	.set			= vr41xx_gpio_set,
	.to_irq			= vr41xx_gpio_to_irq,
पूर्ण;

अटल पूर्णांक giu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक trigger, i, pin;
	काष्ठा irq_chip *chip;
	पूर्णांक irq;

	चयन (pdev->id) अणु
	हाल GPIO_50PINS_PULLUPDOWN:
		giu_flags = GPIO_HAS_PULLUPDOWN_IO;
		vr41xx_gpio_chip.ngpio = 50;
		अवरोध;
	हाल GPIO_36PINS:
		vr41xx_gpio_chip.ngpio = 36;
		अवरोध;
	हाल GPIO_48PINS_EDGE_SELECT:
		giu_flags = GPIO_HAS_INTERRUPT_EDGE_SELECT;
		vr41xx_gpio_chip.ngpio = 48;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "GIU: unknown ID %d\n", pdev->id);
		वापस -ENODEV;
	पूर्ण

	giu_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(giu_base))
		वापस PTR_ERR(giu_base);

	vr41xx_gpio_chip.parent = &pdev->dev;

	अगर (gpiochip_add_data(&vr41xx_gpio_chip, शून्य))
		वापस -ENODEV;

	giu_ग_लिखो(GIUINTENL, 0);
	giu_ग_लिखो(GIUINTENH, 0);

	trigger = giu_पढ़ो(GIUINTTYPH) << 16;
	trigger |= giu_पढ़ो(GIUINTTYPL);
	क्रम (i = GIU_IRQ_BASE; i <= GIU_IRQ_LAST; i++) अणु
		pin = GPIO_PIN_OF_IRQ(i);
		अगर (pin < GIUINT_HIGH_OFFSET)
			chip = &giuपूर्णांक_low_irq_chip;
		अन्यथा
			chip = &giuपूर्णांक_high_irq_chip;

		अगर (trigger & (1 << pin))
			irq_set_chip_and_handler(i, chip, handle_edge_irq);
		अन्यथा
			irq_set_chip_and_handler(i, chip, handle_level_irq);

	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0 || irq >= nr_irqs)
		वापस -EBUSY;

	वापस cascade_irq(irq, giu_get_irq);
पूर्ण

अटल पूर्णांक giu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (giu_base) अणु
		giu_base = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver giu_device_driver = अणु
	.probe		= giu_probe,
	.हटाओ		= giu_हटाओ,
	.driver		= अणु
		.name	= "GIU",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(giu_device_driver);
