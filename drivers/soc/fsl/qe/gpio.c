<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * QUICC Engine GPIOs
 *
 * Copyright (c) MontaVista Software, Inc. 2008.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/gpio/driver.h>
/* FIXME: needed क्रम gpio_to_chip() get rid of this */
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <soc/fsl/qe/qe.h>

काष्ठा qe_gpio_chip अणु
	काष्ठा of_mm_gpio_chip mm_gc;
	spinlock_t lock;

	अचिन्हित दीर्घ pin_flags[QE_PIO_PINS];
#घोषणा QE_PIN_REQUESTED 0

	/* shaकरोwed data रेजिस्टर to clear/set bits safely */
	u32 cpdata;

	/* saved_regs used to restore dedicated functions */
	काष्ठा qe_pio_regs saved_regs;
पूर्ण;

अटल व्योम qe_gpio_save_regs(काष्ठा of_mm_gpio_chip *mm_gc)
अणु
	काष्ठा qe_gpio_chip *qe_gc =
		container_of(mm_gc, काष्ठा qe_gpio_chip, mm_gc);
	काष्ठा qe_pio_regs __iomem *regs = mm_gc->regs;

	qe_gc->cpdata = ioपढ़ो32be(&regs->cpdata);
	qe_gc->saved_regs.cpdata = qe_gc->cpdata;
	qe_gc->saved_regs.cpdir1 = ioपढ़ो32be(&regs->cpdir1);
	qe_gc->saved_regs.cpdir2 = ioपढ़ो32be(&regs->cpdir2);
	qe_gc->saved_regs.cppar1 = ioपढ़ो32be(&regs->cppar1);
	qe_gc->saved_regs.cppar2 = ioपढ़ो32be(&regs->cppar2);
	qe_gc->saved_regs.cpodr = ioपढ़ो32be(&regs->cpodr);
पूर्ण

अटल पूर्णांक qe_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा qe_pio_regs __iomem *regs = mm_gc->regs;
	u32 pin_mask = 1 << (QE_PIO_PINS - 1 - gpio);

	वापस !!(ioपढ़ो32be(&regs->cpdata) & pin_mask);
पूर्ण

अटल व्योम qe_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा qe_gpio_chip *qe_gc = gpiochip_get_data(gc);
	काष्ठा qe_pio_regs __iomem *regs = mm_gc->regs;
	अचिन्हित दीर्घ flags;
	u32 pin_mask = 1 << (QE_PIO_PINS - 1 - gpio);

	spin_lock_irqsave(&qe_gc->lock, flags);

	अगर (val)
		qe_gc->cpdata |= pin_mask;
	अन्यथा
		qe_gc->cpdata &= ~pin_mask;

	ioग_लिखो32be(qe_gc->cpdata, &regs->cpdata);

	spin_unlock_irqrestore(&qe_gc->lock, flags);
पूर्ण

अटल व्योम qe_gpio_set_multiple(काष्ठा gpio_chip *gc,
				 अचिन्हित दीर्घ *mask, अचिन्हित दीर्घ *bits)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा qe_gpio_chip *qe_gc = gpiochip_get_data(gc);
	काष्ठा qe_pio_regs __iomem *regs = mm_gc->regs;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&qe_gc->lock, flags);

	क्रम (i = 0; i < gc->ngpio; i++) अणु
		अगर (*mask == 0)
			अवरोध;
		अगर (__test_and_clear_bit(i, mask)) अणु
			अगर (test_bit(i, bits))
				qe_gc->cpdata |= (1U << (QE_PIO_PINS - 1 - i));
			अन्यथा
				qe_gc->cpdata &= ~(1U << (QE_PIO_PINS - 1 - i));
		पूर्ण
	पूर्ण

	ioग_लिखो32be(qe_gc->cpdata, &regs->cpdata);

	spin_unlock_irqrestore(&qe_gc->lock, flags);
पूर्ण

अटल पूर्णांक qe_gpio_dir_in(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा qe_gpio_chip *qe_gc = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qe_gc->lock, flags);

	__par_io_config_pin(mm_gc->regs, gpio, QE_PIO_सूची_IN, 0, 0, 0);

	spin_unlock_irqrestore(&qe_gc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक qe_gpio_dir_out(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक gpio, पूर्णांक val)
अणु
	काष्ठा of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	काष्ठा qe_gpio_chip *qe_gc = gpiochip_get_data(gc);
	अचिन्हित दीर्घ flags;

	qe_gpio_set(gc, gpio, val);

	spin_lock_irqsave(&qe_gc->lock, flags);

	__par_io_config_pin(mm_gc->regs, gpio, QE_PIO_सूची_OUT, 0, 0, 0);

	spin_unlock_irqrestore(&qe_gc->lock, flags);

	वापस 0;
पूर्ण

काष्ठा qe_pin अणु
	/*
	 * The qe_gpio_chip name is unक्रमtunate, we should change that to
	 * something like qe_pio_controller. Someday.
	 */
	काष्ठा qe_gpio_chip *controller;
	पूर्णांक num;
पूर्ण;

/**
 * qe_pin_request - Request a QE pin
 * @np:		device node to get a pin from
 * @index:	index of a pin in the device tree
 * Context:	non-atomic
 *
 * This function वापस qe_pin so that you could use it with the rest of
 * the QE Pin Multiplexing API.
 */
काष्ठा qe_pin *qe_pin_request(काष्ठा device_node *np, पूर्णांक index)
अणु
	काष्ठा qe_pin *qe_pin;
	काष्ठा gpio_chip *gc;
	काष्ठा qe_gpio_chip *qe_gc;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	qe_pin = kzalloc(माप(*qe_pin), GFP_KERNEL);
	अगर (!qe_pin) अणु
		pr_debug("%s: can't allocate memory\n", __func__);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	err = of_get_gpio(np, index);
	अगर (err < 0)
		जाओ err0;
	gc = gpio_to_chip(err);
	अगर (WARN_ON(!gc)) अणु
		err = -ENODEV;
		जाओ err0;
	पूर्ण

	अगर (!of_device_is_compatible(gc->of_node, "fsl,mpc8323-qe-pario-bank")) अणु
		pr_debug("%s: tried to get a non-qe pin\n", __func__);
		err = -EINVAL;
		जाओ err0;
	पूर्ण

	qe_gc = gpiochip_get_data(gc);

	spin_lock_irqsave(&qe_gc->lock, flags);

	err -= gc->base;
	अगर (test_and_set_bit(QE_PIN_REQUESTED, &qe_gc->pin_flags[err]) == 0) अणु
		qe_pin->controller = qe_gc;
		qe_pin->num = err;
		err = 0;
	पूर्ण अन्यथा अणु
		err = -EBUSY;
	पूर्ण

	spin_unlock_irqrestore(&qe_gc->lock, flags);

	अगर (!err)
		वापस qe_pin;
err0:
	kमुक्त(qe_pin);
	pr_debug("%s failed with status %d\n", __func__, err);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(qe_pin_request);

/**
 * qe_pin_मुक्त - Free a pin
 * @qe_pin:	poपूर्णांकer to the qe_pin काष्ठाure
 * Context:	any
 *
 * This function मुक्तs the qe_pin काष्ठाure and makes a pin available
 * क्रम further qe_pin_request() calls.
 */
व्योम qe_pin_मुक्त(काष्ठा qe_pin *qe_pin)
अणु
	काष्ठा qe_gpio_chip *qe_gc = qe_pin->controller;
	अचिन्हित दीर्घ flags;
	स्थिर पूर्णांक pin = qe_pin->num;

	spin_lock_irqsave(&qe_gc->lock, flags);
	test_and_clear_bit(QE_PIN_REQUESTED, &qe_gc->pin_flags[pin]);
	spin_unlock_irqrestore(&qe_gc->lock, flags);

	kमुक्त(qe_pin);
पूर्ण
EXPORT_SYMBOL(qe_pin_मुक्त);

/**
 * qe_pin_set_dedicated - Revert a pin to a dedicated peripheral function mode
 * @qe_pin:	poपूर्णांकer to the qe_pin काष्ठाure
 * Context:	any
 *
 * This function resets a pin to a dedicated peripheral function that
 * has been set up by the firmware.
 */
व्योम qe_pin_set_dedicated(काष्ठा qe_pin *qe_pin)
अणु
	काष्ठा qe_gpio_chip *qe_gc = qe_pin->controller;
	काष्ठा qe_pio_regs __iomem *regs = qe_gc->mm_gc.regs;
	काष्ठा qe_pio_regs *sregs = &qe_gc->saved_regs;
	पूर्णांक pin = qe_pin->num;
	u32 mask1 = 1 << (QE_PIO_PINS - (pin + 1));
	u32 mask2 = 0x3 << (QE_PIO_PINS - (pin % (QE_PIO_PINS / 2) + 1) * 2);
	bool second_reg = pin > (QE_PIO_PINS / 2) - 1;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qe_gc->lock, flags);

	अगर (second_reg) अणु
		qe_clrsetbits_be32(&regs->cpdir2, mask2,
				   sregs->cpdir2 & mask2);
		qe_clrsetbits_be32(&regs->cppar2, mask2,
				   sregs->cppar2 & mask2);
	पूर्ण अन्यथा अणु
		qe_clrsetbits_be32(&regs->cpdir1, mask2,
				   sregs->cpdir1 & mask2);
		qe_clrsetbits_be32(&regs->cppar1, mask2,
				   sregs->cppar1 & mask2);
	पूर्ण

	अगर (sregs->cpdata & mask1)
		qe_gc->cpdata |= mask1;
	अन्यथा
		qe_gc->cpdata &= ~mask1;

	ioग_लिखो32be(qe_gc->cpdata, &regs->cpdata);
	qe_clrsetbits_be32(&regs->cpodr, mask1, sregs->cpodr & mask1);

	spin_unlock_irqrestore(&qe_gc->lock, flags);
पूर्ण
EXPORT_SYMBOL(qe_pin_set_dedicated);

/**
 * qe_pin_set_gpio - Set a pin to the GPIO mode
 * @qe_pin:	poपूर्णांकer to the qe_pin काष्ठाure
 * Context:	any
 *
 * This function sets a pin to the GPIO mode.
 */
व्योम qe_pin_set_gpio(काष्ठा qe_pin *qe_pin)
अणु
	काष्ठा qe_gpio_chip *qe_gc = qe_pin->controller;
	काष्ठा qe_pio_regs __iomem *regs = qe_gc->mm_gc.regs;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qe_gc->lock, flags);

	/* Let's make it input by शेष, GPIO API is able to change that. */
	__par_io_config_pin(regs, qe_pin->num, QE_PIO_सूची_IN, 0, 0, 0);

	spin_unlock_irqrestore(&qe_gc->lock, flags);
पूर्ण
EXPORT_SYMBOL(qe_pin_set_gpio);

अटल पूर्णांक __init qe_add_gpiochips(व्योम)
अणु
	काष्ठा device_node *np;

	क्रम_each_compatible_node(np, शून्य, "fsl,mpc8323-qe-pario-bank") अणु
		पूर्णांक ret;
		काष्ठा qe_gpio_chip *qe_gc;
		काष्ठा of_mm_gpio_chip *mm_gc;
		काष्ठा gpio_chip *gc;

		qe_gc = kzalloc(माप(*qe_gc), GFP_KERNEL);
		अगर (!qe_gc) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		spin_lock_init(&qe_gc->lock);

		mm_gc = &qe_gc->mm_gc;
		gc = &mm_gc->gc;

		mm_gc->save_regs = qe_gpio_save_regs;
		gc->ngpio = QE_PIO_PINS;
		gc->direction_input = qe_gpio_dir_in;
		gc->direction_output = qe_gpio_dir_out;
		gc->get = qe_gpio_get;
		gc->set = qe_gpio_set;
		gc->set_multiple = qe_gpio_set_multiple;

		ret = of_mm_gpiochip_add_data(np, mm_gc, qe_gc);
		अगर (ret)
			जाओ err;
		जारी;
err:
		pr_err("%pOF: registration failed with status %d\n",
		       np, ret);
		kमुक्त(qe_gc);
		/* try others anyway */
	पूर्ण
	वापस 0;
पूर्ण
arch_initcall(qe_add_gpiochips);
