<शैली गुरु>
/*
 * arch/arm/mach-orion5x/irq.c
 *
 * Core IRQ functions क्रम Marvell Orion System On Chip
 *
 * Maपूर्णांकainer: Tzachi Perelstein <tzachi@marvell.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <plat/orion-gpपन.स>
#समावेश <plat/irq.h>
#समावेश <यंत्र/exception.h>
#समावेश "bridge-regs.h"
#समावेश "common.h"

अटल पूर्णांक __initdata gpio0_irqs[4] = अणु
	IRQ_ORION5X_GPIO_0_7,
	IRQ_ORION5X_GPIO_8_15,
	IRQ_ORION5X_GPIO_16_23,
	IRQ_ORION5X_GPIO_24_31,
पूर्ण;

अटल यंत्रlinkage व्योम
__exception_irq_entry orion5x_legacy_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 stat;

	stat = पढ़ोl_relaxed(MAIN_IRQ_CAUSE);
	stat &= पढ़ोl_relaxed(MAIN_IRQ_MASK);
	अगर (stat) अणु
		अचिन्हित पूर्णांक hwirq = 1 + __fls(stat);
		handle_IRQ(hwirq, regs);
		वापस;
	पूर्ण
पूर्ण

व्योम __init orion5x_init_irq(व्योम)
अणु
	orion_irq_init(1, MAIN_IRQ_MASK);

	set_handle_irq(orion5x_legacy_handle_irq);

	/*
	 * Initialize gpiolib क्रम GPIOs 0-31.
	 */
	orion_gpio_init(शून्य, 0, 32, GPIO_VIRT_BASE, 0,
			IRQ_ORION5X_GPIO_START, gpio0_irqs);
पूर्ण
