<शैली गुरु>
/*
 * arch/arm/mach-करोve/irq.c
 *
 * Dove IRQ handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/exception.h>

#समावेश <plat/irq.h>
#समावेश <plat/orion-gpपन.स>

#समावेश "pm.h"
#समावेश "bridge-regs.h"
#समावेश "common.h"

अटल पूर्णांक __initdata gpio0_irqs[4] = अणु
	IRQ_DOVE_GPIO_0_7,
	IRQ_DOVE_GPIO_8_15,
	IRQ_DOVE_GPIO_16_23,
	IRQ_DOVE_GPIO_24_31,
पूर्ण;

अटल पूर्णांक __initdata gpio1_irqs[4] = अणु
	IRQ_DOVE_HIGH_GPIO,
	0,
	0,
	0,
पूर्ण;

अटल पूर्णांक __initdata gpio2_irqs[4] = अणु
	0,
	0,
	0,
	0,
पूर्ण;

अटल व्योम __iomem *करोve_irq_base = IRQ_VIRT_BASE;

अटल यंत्रlinkage व्योम
__exception_irq_entry करोve_legacy_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 stat;

	stat = पढ़ोl_relaxed(करोve_irq_base + IRQ_CAUSE_LOW_OFF);
	stat &= पढ़ोl_relaxed(करोve_irq_base + IRQ_MASK_LOW_OFF);
	अगर (stat) अणु
		अचिन्हित पूर्णांक hwirq = 1 + __fls(stat);
		handle_IRQ(hwirq, regs);
		वापस;
	पूर्ण
	stat = पढ़ोl_relaxed(करोve_irq_base + IRQ_CAUSE_HIGH_OFF);
	stat &= पढ़ोl_relaxed(करोve_irq_base + IRQ_MASK_HIGH_OFF);
	अगर (stat) अणु
		अचिन्हित पूर्णांक hwirq = 33 + __fls(stat);
		handle_IRQ(hwirq, regs);
		वापस;
	पूर्ण
पूर्ण

व्योम __init करोve_init_irq(व्योम)
अणु
	orion_irq_init(1, IRQ_VIRT_BASE + IRQ_MASK_LOW_OFF);
	orion_irq_init(33, IRQ_VIRT_BASE + IRQ_MASK_HIGH_OFF);

	set_handle_irq(करोve_legacy_handle_irq);

	/*
	 * Initialize gpiolib क्रम GPIOs 0-71.
	 */
	orion_gpio_init(शून्य, 0, 32, DOVE_GPIO_LO_VIRT_BASE, 0,
			IRQ_DOVE_GPIO_START, gpio0_irqs);

	orion_gpio_init(शून्य, 32, 32, DOVE_GPIO_HI_VIRT_BASE, 0,
			IRQ_DOVE_GPIO_START + 32, gpio1_irqs);

	orion_gpio_init(शून्य, 64, 8, DOVE_GPIO2_VIRT_BASE, 0,
			IRQ_DOVE_GPIO_START + 64, gpio2_irqs);
पूर्ण
