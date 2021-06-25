<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/plat-pxa/gpio.c
 *
 *  Generic PXA GPIO handling
 *
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 */
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/slab.h>

/*
 * We handle the GPIOs by banks, each bank covers up to 32 GPIOs with
 * one set of रेजिस्टरs. The रेजिस्टर offsets are organized below:
 *
 *           GPLR    GPDR    GPSR    GPCR    GRER    GFER    GEDR
 * BANK 0 - 0x0000  0x000C  0x0018  0x0024  0x0030  0x003C  0x0048
 * BANK 1 - 0x0004  0x0010  0x001C  0x0028  0x0034  0x0040  0x004C
 * BANK 2 - 0x0008  0x0014  0x0020  0x002C  0x0038  0x0044  0x0050
 *
 * BANK 3 - 0x0100  0x010C  0x0118  0x0124  0x0130  0x013C  0x0148
 * BANK 4 - 0x0104  0x0110  0x011C  0x0128  0x0134  0x0140  0x014C
 * BANK 5 - 0x0108  0x0114  0x0120  0x012C  0x0138  0x0144  0x0150
 *
 * BANK 6 - 0x0200  0x020C  0x0218  0x0224  0x0230  0x023C  0x0248
 *
 * NOTE:
 *   BANK 3 is only available on PXA27x and later processors.
 *   BANK 4 and 5 are only available on PXA935, PXA1928
 *   BANK 6 is only available on PXA1928
 */

#घोषणा GPLR_OFFSET	0x00
#घोषणा GPDR_OFFSET	0x0C
#घोषणा GPSR_OFFSET	0x18
#घोषणा GPCR_OFFSET	0x24
#घोषणा GRER_OFFSET	0x30
#घोषणा GFER_OFFSET	0x3C
#घोषणा GEDR_OFFSET	0x48
#घोषणा GAFR_OFFSET	0x54
#घोषणा ED_MASK_OFFSET	0x9C	/* GPIO edge detection क्रम AP side */

#घोषणा BANK_OFF(n)	(((n) / 3) << 8) + (((n) % 3) << 2)

पूर्णांक pxa_last_gpio;
अटल पूर्णांक irq_base;

काष्ठा pxa_gpio_bank अणु
	व्योम __iomem	*regbase;
	अचिन्हित दीर्घ	irq_mask;
	अचिन्हित दीर्घ	irq_edge_rise;
	अचिन्हित दीर्घ	irq_edge_fall;

#अगर_घोषित CONFIG_PM
	अचिन्हित दीर्घ	saved_gplr;
	अचिन्हित दीर्घ	saved_gpdr;
	अचिन्हित दीर्घ	saved_grer;
	अचिन्हित दीर्घ	saved_gfer;
#पूर्ण_अगर
पूर्ण;

काष्ठा pxa_gpio_chip अणु
	काष्ठा device *dev;
	काष्ठा gpio_chip chip;
	काष्ठा pxa_gpio_bank *banks;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;

	पूर्णांक irq0;
	पूर्णांक irq1;
	पूर्णांक (*set_wake)(अचिन्हित पूर्णांक gpio, अचिन्हित पूर्णांक on);
पूर्ण;

क्रमागत pxa_gpio_type अणु
	PXA25X_GPIO = 0,
	PXA26X_GPIO,
	PXA27X_GPIO,
	PXA3XX_GPIO,
	PXA93X_GPIO,
	MMP_GPIO = 0x10,
	MMP2_GPIO,
	PXA1928_GPIO,
पूर्ण;

काष्ठा pxa_gpio_id अणु
	क्रमागत pxa_gpio_type	type;
	पूर्णांक			gpio_nums;
पूर्ण;

अटल DEFINE_SPINLOCK(gpio_lock);
अटल काष्ठा pxa_gpio_chip *pxa_gpio_chip;
अटल क्रमागत pxa_gpio_type gpio_type;

अटल काष्ठा pxa_gpio_id pxa25x_id = अणु
	.type		= PXA25X_GPIO,
	.gpio_nums	= 85,
पूर्ण;

अटल काष्ठा pxa_gpio_id pxa26x_id = अणु
	.type		= PXA26X_GPIO,
	.gpio_nums	= 90,
पूर्ण;

अटल काष्ठा pxa_gpio_id pxa27x_id = अणु
	.type		= PXA27X_GPIO,
	.gpio_nums	= 121,
पूर्ण;

अटल काष्ठा pxa_gpio_id pxa3xx_id = अणु
	.type		= PXA3XX_GPIO,
	.gpio_nums	= 128,
पूर्ण;

अटल काष्ठा pxa_gpio_id pxa93x_id = अणु
	.type		= PXA93X_GPIO,
	.gpio_nums	= 192,
पूर्ण;

अटल काष्ठा pxa_gpio_id mmp_id = अणु
	.type		= MMP_GPIO,
	.gpio_nums	= 128,
पूर्ण;

अटल काष्ठा pxa_gpio_id mmp2_id = अणु
	.type		= MMP2_GPIO,
	.gpio_nums	= 192,
पूर्ण;

अटल काष्ठा pxa_gpio_id pxa1928_id = अणु
	.type		= PXA1928_GPIO,
	.gpio_nums	= 224,
पूर्ण;

#घोषणा क्रम_each_gpio_bank(i, b, pc)					\
	क्रम (i = 0, b = pc->banks; i <= pxa_last_gpio; i += 32, b++)

अटल अंतरभूत काष्ठा pxa_gpio_chip *chip_to_pxachip(काष्ठा gpio_chip *c)
अणु
	काष्ठा pxa_gpio_chip *pxa_chip = gpiochip_get_data(c);

	वापस pxa_chip;
पूर्ण

अटल अंतरभूत व्योम __iomem *gpio_bank_base(काष्ठा gpio_chip *c, पूर्णांक gpio)
अणु
	काष्ठा pxa_gpio_chip *p = gpiochip_get_data(c);
	काष्ठा pxa_gpio_bank *bank = p->banks + (gpio / 32);

	वापस bank->regbase;
पूर्ण

अटल अंतरभूत काष्ठा pxa_gpio_bank *gpio_to_pxabank(काष्ठा gpio_chip *c,
						    अचिन्हित gpio)
अणु
	वापस chip_to_pxachip(c)->banks + gpio / 32;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_is_pxa_type(पूर्णांक type)
अणु
	वापस (type & MMP_GPIO) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_is_mmp_type(पूर्णांक type)
अणु
	वापस (type & MMP_GPIO) != 0;
पूर्ण

/* GPIO86/87/88/89 on PXA26x have their direction bits in PXA_GPDR(2 inverted,
 * as well as their Alternate Function value being '1' क्रम GPIO in GAFRx.
 */
अटल अंतरभूत पूर्णांक __gpio_is_inverted(पूर्णांक gpio)
अणु
	अगर ((gpio_type == PXA26X_GPIO) && (gpio > 85))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * On PXA25x and PXA27x, GAFRx and GPDRx together decide the alternate
 * function of a GPIO, and GPDRx cannot be altered once configured. It
 * is attributed as "occupied" here (I know this terminology isn't
 * accurate, you are welcome to propose a better one :-)
 */
अटल अंतरभूत पूर्णांक __gpio_is_occupied(काष्ठा pxa_gpio_chip *pchip, अचिन्हित gpio)
अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ gafr = 0, gpdr = 0;
	पूर्णांक ret, af = 0, dir = 0;

	base = gpio_bank_base(&pchip->chip, gpio);
	gpdr = पढ़ोl_relaxed(base + GPDR_OFFSET);

	चयन (gpio_type) अणु
	हाल PXA25X_GPIO:
	हाल PXA26X_GPIO:
	हाल PXA27X_GPIO:
		gafr = पढ़ोl_relaxed(base + GAFR_OFFSET);
		af = (gafr >> ((gpio & 0xf) * 2)) & 0x3;
		dir = gpdr & GPIO_bit(gpio);

		अगर (__gpio_is_inverted(gpio))
			ret = (af != 1) || (dir == 0);
		अन्यथा
			ret = (af != 0) || (dir != 0);
		अवरोध;
	शेष:
		ret = gpdr & GPIO_bit(gpio);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक pxa_irq_to_gpio(पूर्णांक irq)
अणु
	काष्ठा pxa_gpio_chip *pchip = pxa_gpio_chip;
	पूर्णांक irq_gpio0;

	irq_gpio0 = irq_find_mapping(pchip->irqकरोमुख्य, 0);
	अगर (irq_gpio0 > 0)
		वापस irq - irq_gpio0;

	वापस irq_gpio0;
पूर्ण

अटल bool pxa_gpio_has_pinctrl(व्योम)
अणु
	चयन (gpio_type) अणु
	हाल PXA3XX_GPIO:
	हाल MMP2_GPIO:
		वापस false;

	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक pxa_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pxa_gpio_chip *pchip = chip_to_pxachip(chip);

	वापस irq_find_mapping(pchip->irqकरोमुख्य, offset);
पूर्ण

अटल पूर्णांक pxa_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	व्योम __iomem *base = gpio_bank_base(chip, offset);
	uपूर्णांक32_t value, mask = GPIO_bit(offset);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (pxa_gpio_has_pinctrl()) अणु
		ret = pinctrl_gpio_direction_input(chip->base + offset);
		अगर (ret)
			वापस ret;
	पूर्ण

	spin_lock_irqsave(&gpio_lock, flags);

	value = पढ़ोl_relaxed(base + GPDR_OFFSET);
	अगर (__gpio_is_inverted(chip->base + offset))
		value |= mask;
	अन्यथा
		value &= ~mask;
	ग_लिखोl_relaxed(value, base + GPDR_OFFSET);

	spin_unlock_irqrestore(&gpio_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa_gpio_direction_output(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	व्योम __iomem *base = gpio_bank_base(chip, offset);
	uपूर्णांक32_t पंचांगp, mask = GPIO_bit(offset);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ग_लिखोl_relaxed(mask, base + (value ? GPSR_OFFSET : GPCR_OFFSET));

	अगर (pxa_gpio_has_pinctrl()) अणु
		ret = pinctrl_gpio_direction_output(chip->base + offset);
		अगर (ret)
			वापस ret;
	पूर्ण

	spin_lock_irqsave(&gpio_lock, flags);

	पंचांगp = पढ़ोl_relaxed(base + GPDR_OFFSET);
	अगर (__gpio_is_inverted(chip->base + offset))
		पंचांगp &= ~mask;
	अन्यथा
		पंचांगp |= mask;
	ग_लिखोl_relaxed(पंचांगp, base + GPDR_OFFSET);

	spin_unlock_irqrestore(&gpio_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	व्योम __iomem *base = gpio_bank_base(chip, offset);
	u32 gplr = पढ़ोl_relaxed(base + GPLR_OFFSET);

	वापस !!(gplr & GPIO_bit(offset));
पूर्ण

अटल व्योम pxa_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	व्योम __iomem *base = gpio_bank_base(chip, offset);

	ग_लिखोl_relaxed(GPIO_bit(offset),
		       base + (value ? GPSR_OFFSET : GPCR_OFFSET));
पूर्ण

#अगर_घोषित CONFIG_OF_GPIO
अटल पूर्णांक pxa_gpio_of_xlate(काष्ठा gpio_chip *gc,
			     स्थिर काष्ठा of_phandle_args *gpiospec,
			     u32 *flags)
अणु
	अगर (gpiospec->args[0] > pxa_last_gpio)
		वापस -EINVAL;

	अगर (flags)
		*flags = gpiospec->args[1];

	वापस gpiospec->args[0];
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक pxa_init_gpio_chip(काष्ठा pxa_gpio_chip *pchip, पूर्णांक ngpio,
			      काष्ठा device_node *np, व्योम __iomem *regbase)
अणु
	पूर्णांक i, gpio, nbanks = DIV_ROUND_UP(ngpio, 32);
	काष्ठा pxa_gpio_bank *bank;

	pchip->banks = devm_kसुस्मृति(pchip->dev, nbanks, माप(*pchip->banks),
				    GFP_KERNEL);
	अगर (!pchip->banks)
		वापस -ENOMEM;

	pchip->chip.label = "gpio-pxa";
	pchip->chip.direction_input  = pxa_gpio_direction_input;
	pchip->chip.direction_output = pxa_gpio_direction_output;
	pchip->chip.get = pxa_gpio_get;
	pchip->chip.set = pxa_gpio_set;
	pchip->chip.to_irq = pxa_gpio_to_irq;
	pchip->chip.ngpio = ngpio;
	pchip->chip.request = gpiochip_generic_request;
	pchip->chip.मुक्त = gpiochip_generic_मुक्त;

#अगर_घोषित CONFIG_OF_GPIO
	pchip->chip.of_node = np;
	pchip->chip.of_xlate = pxa_gpio_of_xlate;
	pchip->chip.of_gpio_n_cells = 2;
#पूर्ण_अगर

	क्रम (i = 0, gpio = 0; i < nbanks; i++, gpio += 32) अणु
		bank = pchip->banks + i;
		bank->regbase = regbase + BANK_OFF(i);
	पूर्ण

	वापस gpiochip_add_data(&pchip->chip, pchip);
पूर्ण

/* Update only those GRERx and GFERx edge detection रेजिस्टर bits अगर those
 * bits are set in c->irq_mask
 */
अटल अंतरभूत व्योम update_edge_detect(काष्ठा pxa_gpio_bank *c)
अणु
	uपूर्णांक32_t grer, gfer;

	grer = पढ़ोl_relaxed(c->regbase + GRER_OFFSET) & ~c->irq_mask;
	gfer = पढ़ोl_relaxed(c->regbase + GFER_OFFSET) & ~c->irq_mask;
	grer |= c->irq_edge_rise & c->irq_mask;
	gfer |= c->irq_edge_fall & c->irq_mask;
	ग_लिखोl_relaxed(grer, c->regbase + GRER_OFFSET);
	ग_लिखोl_relaxed(gfer, c->regbase + GFER_OFFSET);
पूर्ण

अटल पूर्णांक pxa_gpio_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा pxa_gpio_chip *pchip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(d);
	काष्ठा pxa_gpio_bank *c = gpio_to_pxabank(&pchip->chip, gpio);
	अचिन्हित दीर्घ gpdr, mask = GPIO_bit(gpio);

	अगर (type == IRQ_TYPE_PROBE) अणु
		/* Don't mess with enabled GPIOs using preconfigured edges or
		 * GPIOs set to alternate function or to output during probe
		 */
		अगर ((c->irq_edge_rise | c->irq_edge_fall) & GPIO_bit(gpio))
			वापस 0;

		अगर (__gpio_is_occupied(pchip, gpio))
			वापस 0;

		type = IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING;
	पूर्ण

	gpdr = पढ़ोl_relaxed(c->regbase + GPDR_OFFSET);

	अगर (__gpio_is_inverted(gpio))
		ग_लिखोl_relaxed(gpdr | mask,  c->regbase + GPDR_OFFSET);
	अन्यथा
		ग_लिखोl_relaxed(gpdr & ~mask, c->regbase + GPDR_OFFSET);

	अगर (type & IRQ_TYPE_EDGE_RISING)
		c->irq_edge_rise |= mask;
	अन्यथा
		c->irq_edge_rise &= ~mask;

	अगर (type & IRQ_TYPE_EDGE_FALLING)
		c->irq_edge_fall |= mask;
	अन्यथा
		c->irq_edge_fall &= ~mask;

	update_edge_detect(c);

	pr_debug("%s: IRQ%d (GPIO%d) - edge%s%s\n", __func__, d->irq, gpio,
		((type & IRQ_TYPE_EDGE_RISING)  ? " rising"  : ""),
		((type & IRQ_TYPE_EDGE_FALLING) ? " falling" : ""));
	वापस 0;
पूर्ण

अटल irqवापस_t pxa_gpio_demux_handler(पूर्णांक in_irq, व्योम *d)
अणु
	पूर्णांक loop, gpio, n, handled = 0;
	अचिन्हित दीर्घ gedr;
	काष्ठा pxa_gpio_chip *pchip = d;
	काष्ठा pxa_gpio_bank *c;

	करो अणु
		loop = 0;
		क्रम_each_gpio_bank(gpio, c, pchip) अणु
			gedr = पढ़ोl_relaxed(c->regbase + GEDR_OFFSET);
			gedr = gedr & c->irq_mask;
			ग_लिखोl_relaxed(gedr, c->regbase + GEDR_OFFSET);

			क्रम_each_set_bit(n, &gedr, BITS_PER_LONG) अणु
				loop = 1;

				generic_handle_irq(
					irq_find_mapping(pchip->irqकरोमुख्य,
							 gpio + n));
			पूर्ण
		पूर्ण
		handled += loop;
	पूर्ण जबतक (loop);

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल irqवापस_t pxa_gpio_direct_handler(पूर्णांक in_irq, व्योम *d)
अणु
	काष्ठा pxa_gpio_chip *pchip = d;

	अगर (in_irq == pchip->irq0) अणु
		generic_handle_irq(irq_find_mapping(pchip->irqकरोमुख्य, 0));
	पूर्ण अन्यथा अगर (in_irq == pchip->irq1) अणु
		generic_handle_irq(irq_find_mapping(pchip->irqकरोमुख्य, 1));
	पूर्ण अन्यथा अणु
		pr_err("%s() unknown irq %d\n", __func__, in_irq);
		वापस IRQ_NONE;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pxa_ack_muxed_gpio(काष्ठा irq_data *d)
अणु
	काष्ठा pxa_gpio_chip *pchip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(d);
	व्योम __iomem *base = gpio_bank_base(&pchip->chip, gpio);

	ग_लिखोl_relaxed(GPIO_bit(gpio), base + GEDR_OFFSET);
पूर्ण

अटल व्योम pxa_mask_muxed_gpio(काष्ठा irq_data *d)
अणु
	काष्ठा pxa_gpio_chip *pchip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(d);
	काष्ठा pxa_gpio_bank *b = gpio_to_pxabank(&pchip->chip, gpio);
	व्योम __iomem *base = gpio_bank_base(&pchip->chip, gpio);
	uपूर्णांक32_t grer, gfer;

	b->irq_mask &= ~GPIO_bit(gpio);

	grer = पढ़ोl_relaxed(base + GRER_OFFSET) & ~GPIO_bit(gpio);
	gfer = पढ़ोl_relaxed(base + GFER_OFFSET) & ~GPIO_bit(gpio);
	ग_लिखोl_relaxed(grer, base + GRER_OFFSET);
	ग_लिखोl_relaxed(gfer, base + GFER_OFFSET);
पूर्ण

अटल पूर्णांक pxa_gpio_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा pxa_gpio_chip *pchip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(d);

	अगर (pchip->set_wake)
		वापस pchip->set_wake(gpio, on);
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम pxa_unmask_muxed_gpio(काष्ठा irq_data *d)
अणु
	काष्ठा pxa_gpio_chip *pchip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक gpio = irqd_to_hwirq(d);
	काष्ठा pxa_gpio_bank *c = gpio_to_pxabank(&pchip->chip, gpio);

	c->irq_mask |= GPIO_bit(gpio);
	update_edge_detect(c);
पूर्ण

अटल काष्ठा irq_chip pxa_muxed_gpio_chip = अणु
	.name		= "GPIO",
	.irq_ack	= pxa_ack_muxed_gpio,
	.irq_mask	= pxa_mask_muxed_gpio,
	.irq_unmask	= pxa_unmask_muxed_gpio,
	.irq_set_type	= pxa_gpio_irq_type,
	.irq_set_wake	= pxa_gpio_set_wake,
पूर्ण;

अटल पूर्णांक pxa_gpio_nums(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	काष्ठा pxa_gpio_id *pxa_id = (काष्ठा pxa_gpio_id *)id->driver_data;
	पूर्णांक count = 0;

	चयन (pxa_id->type) अणु
	हाल PXA25X_GPIO:
	हाल PXA26X_GPIO:
	हाल PXA27X_GPIO:
	हाल PXA3XX_GPIO:
	हाल PXA93X_GPIO:
	हाल MMP_GPIO:
	हाल MMP2_GPIO:
	हाल PXA1928_GPIO:
		gpio_type = pxa_id->type;
		count = pxa_id->gpio_nums - 1;
		अवरोध;
	शेष:
		count = -EINVAL;
		अवरोध;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक pxa_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			      irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(irq, &pxa_muxed_gpio_chip,
				 handle_edge_irq);
	irq_set_chip_data(irq, d->host_data);
	irq_set_noprobe(irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pxa_irq_करोमुख्य_ops = अणु
	.map	= pxa_irq_करोमुख्य_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pxa_gpio_dt_ids[] = अणु
	अणु .compatible = "intel,pxa25x-gpio",	.data = &pxa25x_id, पूर्ण,
	अणु .compatible = "intel,pxa26x-gpio",	.data = &pxa26x_id, पूर्ण,
	अणु .compatible = "intel,pxa27x-gpio",	.data = &pxa27x_id, पूर्ण,
	अणु .compatible = "intel,pxa3xx-gpio",	.data = &pxa3xx_id, पूर्ण,
	अणु .compatible = "marvell,pxa93x-gpio",	.data = &pxa93x_id, पूर्ण,
	अणु .compatible = "marvell,mmp-gpio",	.data = &mmp_id, पूर्ण,
	अणु .compatible = "marvell,mmp2-gpio",	.data = &mmp2_id, पूर्ण,
	अणु .compatible = "marvell,pxa1928-gpio",	.data = &pxa1928_id, पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक pxa_gpio_probe_dt(काष्ठा platक्रमm_device *pdev,
			     काष्ठा pxa_gpio_chip *pchip)
अणु
	पूर्णांक nr_gpios;
	स्थिर काष्ठा pxa_gpio_id *gpio_id;

	gpio_id = of_device_get_match_data(&pdev->dev);
	gpio_type = gpio_id->type;

	nr_gpios = gpio_id->gpio_nums;
	pxa_last_gpio = nr_gpios - 1;

	irq_base = devm_irq_alloc_descs(&pdev->dev, -1, 0, nr_gpios, 0);
	अगर (irq_base < 0) अणु
		dev_err(&pdev->dev, "Failed to allocate IRQ numbers\n");
		वापस irq_base;
	पूर्ण
	वापस irq_base;
पूर्ण
#अन्यथा
#घोषणा pxa_gpio_probe_dt(pdev, pchip)		(-1)
#पूर्ण_अगर

अटल पूर्णांक pxa_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa_gpio_chip *pchip;
	काष्ठा pxa_gpio_bank *c;
	काष्ठा clk *clk;
	काष्ठा pxa_gpio_platक्रमm_data *info;
	व्योम __iomem *gpio_reg_base;
	पूर्णांक gpio, ret;
	पूर्णांक irq0 = 0, irq1 = 0, irq_mux;

	pchip = devm_kzalloc(&pdev->dev, माप(*pchip), GFP_KERNEL);
	अगर (!pchip)
		वापस -ENOMEM;
	pchip->dev = &pdev->dev;

	info = dev_get_platdata(&pdev->dev);
	अगर (info) अणु
		irq_base = info->irq_base;
		अगर (irq_base <= 0)
			वापस -EINVAL;
		pxa_last_gpio = pxa_gpio_nums(pdev);
		pchip->set_wake = info->gpio_set_wake;
	पूर्ण अन्यथा अणु
		irq_base = pxa_gpio_probe_dt(pdev, pchip);
		अगर (irq_base < 0)
			वापस -EINVAL;
	पूर्ण

	अगर (!pxa_last_gpio)
		वापस -EINVAL;

	pchip->irqकरोमुख्य = irq_करोमुख्य_add_legacy(pdev->dev.of_node,
						 pxa_last_gpio + 1, irq_base,
						 0, &pxa_irq_करोमुख्य_ops, pchip);
	अगर (!pchip->irqकरोमुख्य)
		वापस -ENOMEM;

	irq0 = platक्रमm_get_irq_byname_optional(pdev, "gpio0");
	irq1 = platक्रमm_get_irq_byname_optional(pdev, "gpio1");
	irq_mux = platक्रमm_get_irq_byname(pdev, "gpio_mux");
	अगर ((irq0 > 0 && irq1 <= 0) || (irq0 <= 0 && irq1 > 0)
		|| (irq_mux <= 0))
		वापस -EINVAL;

	pchip->irq0 = irq0;
	pchip->irq1 = irq1;

	gpio_reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(gpio_reg_base))
		वापस PTR_ERR(gpio_reg_base);

	clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "Error %ld to get gpio clock\n",
			PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण
	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		clk_put(clk);
		वापस ret;
	पूर्ण

	/* Initialize GPIO chips */
	ret = pxa_init_gpio_chip(pchip, pxa_last_gpio + 1, pdev->dev.of_node,
				 gpio_reg_base);
	अगर (ret) अणु
		clk_put(clk);
		वापस ret;
	पूर्ण

	/* clear all GPIO edge detects */
	क्रम_each_gpio_bank(gpio, c, pchip) अणु
		ग_लिखोl_relaxed(0, c->regbase + GFER_OFFSET);
		ग_लिखोl_relaxed(0, c->regbase + GRER_OFFSET);
		ग_लिखोl_relaxed(~0, c->regbase + GEDR_OFFSET);
		/* unmask GPIO edge detect क्रम AP side */
		अगर (gpio_is_mmp_type(gpio_type))
			ग_लिखोl_relaxed(~0, c->regbase + ED_MASK_OFFSET);
	पूर्ण

	अगर (irq0 > 0) अणु
		ret = devm_request_irq(&pdev->dev,
				       irq0, pxa_gpio_direct_handler, 0,
				       "gpio-0", pchip);
		अगर (ret)
			dev_err(&pdev->dev, "request of gpio0 irq failed: %d\n",
				ret);
	पूर्ण
	अगर (irq1 > 0) अणु
		ret = devm_request_irq(&pdev->dev,
				       irq1, pxa_gpio_direct_handler, 0,
				       "gpio-1", pchip);
		अगर (ret)
			dev_err(&pdev->dev, "request of gpio1 irq failed: %d\n",
				ret);
	पूर्ण
	ret = devm_request_irq(&pdev->dev,
			       irq_mux, pxa_gpio_demux_handler, 0,
				       "gpio-mux", pchip);
	अगर (ret)
		dev_err(&pdev->dev, "request of gpio-mux irq failed: %d\n",
				ret);

	pxa_gpio_chip = pchip;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id gpio_id_table[] = अणु
	अणु "pxa25x-gpio",	(अचिन्हित दीर्घ)&pxa25x_id पूर्ण,
	अणु "pxa26x-gpio",	(अचिन्हित दीर्घ)&pxa26x_id पूर्ण,
	अणु "pxa27x-gpio",	(अचिन्हित दीर्घ)&pxa27x_id पूर्ण,
	अणु "pxa3xx-gpio",	(अचिन्हित दीर्घ)&pxa3xx_id पूर्ण,
	अणु "pxa93x-gpio",	(अचिन्हित दीर्घ)&pxa93x_id पूर्ण,
	अणु "mmp-gpio",		(अचिन्हित दीर्घ)&mmp_id पूर्ण,
	अणु "mmp2-gpio",		(अचिन्हित दीर्घ)&mmp2_id पूर्ण,
	अणु "pxa1928-gpio",	(अचिन्हित दीर्घ)&pxa1928_id पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver pxa_gpio_driver = अणु
	.probe		= pxa_gpio_probe,
	.driver		= अणु
		.name	= "pxa-gpio",
		.of_match_table = of_match_ptr(pxa_gpio_dt_ids),
	पूर्ण,
	.id_table	= gpio_id_table,
पूर्ण;

अटल पूर्णांक __init pxa_gpio_legacy_init(व्योम)
अणु
	अगर (of_have_populated_dt())
		वापस 0;

	वापस platक्रमm_driver_रेजिस्टर(&pxa_gpio_driver);
पूर्ण
postcore_initcall(pxa_gpio_legacy_init);

अटल पूर्णांक __init pxa_gpio_dt_init(व्योम)
अणु
	अगर (of_have_populated_dt())
		वापस platक्रमm_driver_रेजिस्टर(&pxa_gpio_driver);

	वापस 0;
पूर्ण
device_initcall(pxa_gpio_dt_init);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pxa_gpio_suspend(व्योम)
अणु
	काष्ठा pxa_gpio_chip *pchip = pxa_gpio_chip;
	काष्ठा pxa_gpio_bank *c;
	पूर्णांक gpio;

	अगर (!pchip)
		वापस 0;

	क्रम_each_gpio_bank(gpio, c, pchip) अणु
		c->saved_gplr = पढ़ोl_relaxed(c->regbase + GPLR_OFFSET);
		c->saved_gpdr = पढ़ोl_relaxed(c->regbase + GPDR_OFFSET);
		c->saved_grer = पढ़ोl_relaxed(c->regbase + GRER_OFFSET);
		c->saved_gfer = पढ़ोl_relaxed(c->regbase + GFER_OFFSET);

		/* Clear GPIO transition detect bits */
		ग_लिखोl_relaxed(0xffffffff, c->regbase + GEDR_OFFSET);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pxa_gpio_resume(व्योम)
अणु
	काष्ठा pxa_gpio_chip *pchip = pxa_gpio_chip;
	काष्ठा pxa_gpio_bank *c;
	पूर्णांक gpio;

	अगर (!pchip)
		वापस;

	क्रम_each_gpio_bank(gpio, c, pchip) अणु
		/* restore level with set/clear */
		ग_लिखोl_relaxed(c->saved_gplr, c->regbase + GPSR_OFFSET);
		ग_लिखोl_relaxed(~c->saved_gplr, c->regbase + GPCR_OFFSET);

		ग_लिखोl_relaxed(c->saved_grer, c->regbase + GRER_OFFSET);
		ग_लिखोl_relaxed(c->saved_gfer, c->regbase + GFER_OFFSET);
		ग_लिखोl_relaxed(c->saved_gpdr, c->regbase + GPDR_OFFSET);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा pxa_gpio_suspend	शून्य
#घोषणा pxa_gpio_resume		शून्य
#पूर्ण_अगर

अटल काष्ठा syscore_ops pxa_gpio_syscore_ops = अणु
	.suspend	= pxa_gpio_suspend,
	.resume		= pxa_gpio_resume,
पूर्ण;

अटल पूर्णांक __init pxa_gpio_sysinit(व्योम)
अणु
	रेजिस्टर_syscore_ops(&pxa_gpio_syscore_ops);
	वापस 0;
पूर्ण
postcore_initcall(pxa_gpio_sysinit);
