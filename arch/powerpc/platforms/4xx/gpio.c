<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PPC4xx gpio driver
 *
 * Copyright (c) 2008 Harris Corporation
 * Copyright (c) 2008 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix
 * Copyright (c) MontaVista Software, Inc. 2008.
 *
 * Author: Steve Falco <sfalco@harris.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#घोषणा GPIO_MASK(gpio)		(0x80000000 >> (gpio))
#घोषणा GPIO_MASK2(gpio)	(0xc0000000 >> ((gpio) * 2))

/* Physical GPIO रेजिस्टर layout */
काष्ठा ppc4xx_gpio अणु
	__be32 or;
	__be32 tcr;
	__be32 osrl;
	__be32 osrh;
	__be32 tsrl;
	__be32 tsrh;
	__be32 odr;
	__be32 ir;
	__be32 rr1;
	__be32 rr2;
	__be32 rr3;
	__be32 reserved1;
	__be32 isr1l;
	__be32 isr1h;
	__be32 isr2l;
	__be32 isr2h;
	__be32 isr3l;
	__be32 isr3h;
पूर्ण;

काष्ठा ppc4xx_gpio_chip अणु
	काष्ठा of_mm_gpio_chip mm_gc;
	spinlock_t lock;
पूर्ण;

/*
 * GPIO LIB API implementation क्रम GPIOs
 *
 * There are a maximum of 32 gpios in each gpio controller.
 */

अटल पूर्णांक ppc4xx_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा ppc4xx_gpio __iomem *regs = mm_gc->regs;

	वापस !!(in_be32(&regs->ir) & GPIO_MASK(gpio));
पूर्ण

अटल अंतरभूत व्योम
__ppc4xx_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा ppc4xx_gpio __iomem *regs = mm_gc->regs;

	अगर (val)
		setbits32(&regs->or, GPIO_MASK(gpio));
	अन्यथा
		clrbits32(&regs->or, GPIO_MASK(gpio));
पूर्ण

अटल व्योम
ppc4xx_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा ppc4xx_gpio_chip *chip = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);

	__ppc4xx_gpio_set(gc, gpio, val);

	spin_unlock_irqrestore(&chip->lock, flags);

	pr_debug("%s: gpio: %d val: %d\n", __func__, gpio, val);
पूर्ण

अटल पूर्णांक ppc4xx_gpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा ppc4xx_gpio_chip *chip = gpiochip_get_data(gc);
	काष्ठा ppc4xx_gpio __iomem *regs = mm_gc->regs;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);

	/* Disable खोलो-drain function */
	clrbits32(&regs->odr, GPIO_MASK(gpio));

	/* Float the pin */
	clrbits32(&regs->tcr, GPIO_MASK(gpio));

	/* Bits 0-15 use TSRL/OSRL, bits 16-31 use TSRH/OSRH */
	अगर (gpio < 16) अणु
		clrbits32(&regs->osrl, GPIO_MASK2(gpio));
		clrbits32(&regs->tsrl, GPIO_MASK2(gpio));
	पूर्ण अन्यथा अणु
		clrbits32(&regs->osrh, GPIO_MASK2(gpio));
		clrbits32(&regs->tsrh, GPIO_MASK2(gpio));
	पूर्ण

	spin_unlock_irqrestore(&chip->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
ppc4xx_gpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा ppc4xx_gpio_chip *chip = gpiochip_get_data(gc);
	काष्ठा ppc4xx_gpio __iomem *regs = mm_gc->regs;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);

	/* First set initial value */
	__ppc4xx_gpio_set(gc, gpio, val);

	/* Disable खोलो-drain function */
	clrbits32(&regs->odr, GPIO_MASK(gpio));

	/* Drive the pin */
	setbits32(&regs->tcr, GPIO_MASK(gpio));

	/* Bits 0-15 use TSRL, bits 16-31 use TSRH */
	अगर (gpio < 16) अणु
		clrbits32(&regs->osrl, GPIO_MASK2(gpio));
		clrbits32(&regs->tsrl, GPIO_MASK2(gpio));
	पूर्ण अन्यथा अणु
		clrbits32(&regs->osrh, GPIO_MASK2(gpio));
		clrbits32(&regs->tsrh, GPIO_MASK2(gpio));
	पूर्ण

	spin_unlock_irqrestore(&chip->lock, flags);

	pr_debug("%s: gpio: %d val: %d\n", __func__, gpio, val);

	वापस 0;
पूर्ण

अटल पूर्णांक __init ppc4xx_add_gpiochips(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम_each_compatible_node(np, शून्य, "ibm,ppc4xx-gpio") अणु
		पूर्णांक ret;
		काष्ठा ppc4xx_gpio_chip *ppc4xx_gc;
		काष्ठा of_mm_gpio_chip *mm_gc;
		काष्ठा gpio_chip *gc;

		ppc4xx_gc = kzalloc(माप(*ppc4xx_gc), GFP_KERNEL);
		अगर (!ppc4xx_gc) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		spin_lock_init(&ppc4xx_gc->lock);

		mm_gc = &ppc4xx_gc->mm_gc;
		gc = &mm_gc->gc;

		gc->ngpio = 32;
		gc->direction_input = ppc4xx_gpio_dir_in;
		gc->direction_output = ppc4xx_gpio_dir_out;
		gc->get = ppc4xx_gpio_get;
		gc->set = ppc4xx_gpio_set;

		ret = of_mm_gpiochip_add_data(np, mm_gc, ppc4xx_gc);
		अगर (ret)
			जाओ err;
		जारी;
err:
		pr_err("%pOF: registration failed with status %d\n", np, ret);
		kमुक्त(ppc4xx_gc);
		/* try others anyway */
	पूर्ण
	वापस 0;
पूर्ण
arch_initcall(ppc4xx_add_gpiochips);
