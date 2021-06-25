<शैली गुरु>
/*
 * arch/arm/mach-mv78xx0/irq.c
 *
 * MV78xx0 IRQ handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/exception.h>
#समावेश <plat/orion-gpपन.स>
#समावेश <plat/irq.h>
#समावेश "bridge-regs.h"
#समावेश "common.h"

अटल पूर्णांक __initdata gpio0_irqs[4] = अणु
	IRQ_MV78XX0_GPIO_0_7,
	IRQ_MV78XX0_GPIO_8_15,
	IRQ_MV78XX0_GPIO_16_23,
	IRQ_MV78XX0_GPIO_24_31,
पूर्ण;

अटल व्योम __iomem *mv78xx0_irq_base = IRQ_VIRT_BASE;

अटल यंत्रlinkage व्योम
__exception_irq_entry mv78xx0_legacy_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 stat;

	stat = पढ़ोl_relaxed(mv78xx0_irq_base + IRQ_CAUSE_LOW_OFF);
	stat &= पढ़ोl_relaxed(mv78xx0_irq_base + IRQ_MASK_LOW_OFF);
	अगर (stat) अणु
		अचिन्हित पूर्णांक hwirq = __fls(stat);
		handle_IRQ(hwirq, regs);
		वापस;
	पूर्ण
	stat = पढ़ोl_relaxed(mv78xx0_irq_base + IRQ_CAUSE_HIGH_OFF);
	stat &= पढ़ोl_relaxed(mv78xx0_irq_base + IRQ_MASK_HIGH_OFF);
	अगर (stat) अणु
		अचिन्हित पूर्णांक hwirq = 32 + __fls(stat);
		handle_IRQ(hwirq, regs);
		वापस;
	पूर्ण
	stat = पढ़ोl_relaxed(mv78xx0_irq_base + IRQ_CAUSE_ERR_OFF);
	stat &= पढ़ोl_relaxed(mv78xx0_irq_base + IRQ_MASK_ERR_OFF);
	अगर (stat) अणु
		अचिन्हित पूर्णांक hwirq = 64 + __fls(stat);
		handle_IRQ(hwirq, regs);
		वापस;
	पूर्ण
पूर्ण

व्योम __init mv78xx0_init_irq(व्योम)
अणु
	orion_irq_init(0, IRQ_VIRT_BASE + IRQ_MASK_LOW_OFF);
	orion_irq_init(32, IRQ_VIRT_BASE + IRQ_MASK_HIGH_OFF);
	orion_irq_init(64, IRQ_VIRT_BASE + IRQ_MASK_ERR_OFF);

	set_handle_irq(mv78xx0_legacy_handle_irq);

	/*
	 * Initialize gpiolib क्रम GPIOs 0-31.  (The GPIO पूर्णांकerrupt mask
	 * रेजिस्टरs क्रम core #1 are at an offset of 0x18 from those of
	 * core #0.)
	 */
	orion_gpio_init(शून्य, 0, 32, GPIO_VIRT_BASE,
			mv78xx0_core_index() ? 0x18 : 0,
			IRQ_MV78XX0_GPIO_START, gpio0_irqs);
पूर्ण
