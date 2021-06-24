<शैली गुरु>
/*
 * पूर्णांकc2.c  -- support क्रम the 2nd INTC controller of the 525x
 *
 * (C) Copyright 2012, Steven King <sfking@fdwdc.com>
 * (C) Copyright 2009, Greg Ungerer <gerg@snapgear.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>

अटल व्योम पूर्णांकc2_irq_gpio_mask(काष्ठा irq_data *d)
अणु
	u32 imr = पढ़ोl(MCFSIM2_GPIOINTENABLE);
	u32 type = irqd_get_trigger_type(d);
	पूर्णांक irq = d->irq - MCF_IRQ_GPIO0;

	अगर (type & IRQ_TYPE_EDGE_RISING)
		imr &= ~(0x001 << irq);
	अगर (type & IRQ_TYPE_EDGE_FALLING)
		imr &= ~(0x100 << irq);
	ग_लिखोl(imr, MCFSIM2_GPIOINTENABLE);
पूर्ण

अटल व्योम पूर्णांकc2_irq_gpio_unmask(काष्ठा irq_data *d)
अणु
	u32 imr = पढ़ोl(MCFSIM2_GPIOINTENABLE);
	u32 type = irqd_get_trigger_type(d);
	पूर्णांक irq = d->irq - MCF_IRQ_GPIO0;

	अगर (type & IRQ_TYPE_EDGE_RISING)
		imr |= (0x001 << irq);
	अगर (type & IRQ_TYPE_EDGE_FALLING)
		imr |= (0x100 << irq);
	ग_लिखोl(imr, MCFSIM2_GPIOINTENABLE);
पूर्ण

अटल व्योम पूर्णांकc2_irq_gpio_ack(काष्ठा irq_data *d)
अणु
	u32 imr = 0;
	u32 type = irqd_get_trigger_type(d);
	पूर्णांक irq = d->irq - MCF_IRQ_GPIO0;

	अगर (type & IRQ_TYPE_EDGE_RISING)
		imr |= (0x001 << irq);
	अगर (type & IRQ_TYPE_EDGE_FALLING)
		imr |= (0x100 << irq);
	ग_लिखोl(imr, MCFSIM2_GPIOINTCLEAR);
पूर्ण

अटल पूर्णांक पूर्णांकc2_irq_gpio_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक f)
अणु
	अगर (f & ~IRQ_TYPE_EDGE_BOTH)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip पूर्णांकc2_irq_gpio_chip = अणु
	.name		= "CF-INTC2",
	.irq_mask	= पूर्णांकc2_irq_gpio_mask,
	.irq_unmask	= पूर्णांकc2_irq_gpio_unmask,
	.irq_ack	= पूर्णांकc2_irq_gpio_ack,
	.irq_set_type	= पूर्णांकc2_irq_gpio_set_type,
पूर्ण;

अटल पूर्णांक __init mcf_पूर्णांकc2_init(व्योम)
अणु
	पूर्णांक irq;

	/* set the पूर्णांकerrupt base क्रम the second पूर्णांकerrupt controller */
	ग_लिखोl(MCFINTC2_VECBASE, MCFINTC2_INTBASE);

	/* GPIO पूर्णांकerrupt sources */
	क्रम (irq = MCF_IRQ_GPIO0; (irq <= MCF_IRQ_GPIO6); irq++) अणु
		irq_set_chip(irq, &पूर्णांकc2_irq_gpio_chip);
		irq_set_handler(irq, handle_edge_irq);
	पूर्ण

	वापस 0;
पूर्ण

arch_initcall(mcf_पूर्णांकc2_init);
