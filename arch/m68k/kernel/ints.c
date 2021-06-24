<शैली गुरु>
/*
 * linux/arch/m68k/kernel/पूर्णांकs.c -- Linux/m68k general पूर्णांकerrupt handling code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/irq_regs.h>

#अगर_घोषित CONFIG_Q40
#समावेश <यंत्र/q40पूर्णांकs.h>
#पूर्ण_अगर

बाह्य u32 स्वतः_irqhandler_fixup[];
बाह्य u16 user_irqvec_fixup[];

अटल पूर्णांक m68k_first_user_vec;

अटल काष्ठा irq_chip स्वतः_irq_chip = अणु
	.name		= "auto",
	.irq_startup	= m68k_irq_startup,
	.irq_shutकरोwn	= m68k_irq_shutकरोwn,
पूर्ण;

अटल काष्ठा irq_chip user_irq_chip = अणु
	.name		= "user",
	.irq_startup	= m68k_irq_startup,
	.irq_shutकरोwn	= m68k_irq_shutकरोwn,
पूर्ण;

/*
 * व्योम init_IRQ(व्योम)
 *
 * Parameters:	None
 *
 * Returns:	Nothing
 *
 * This function should be called during kernel startup to initialize
 * the IRQ handling routines.
 */

व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = IRQ_AUTO_1; i <= IRQ_AUTO_7; i++)
		irq_set_chip_and_handler(i, &स्वतः_irq_chip, handle_simple_irq);

	mach_init_IRQ();
पूर्ण

/**
 * m68k_setup_स्वतः_पूर्णांकerrupt
 * @handler: called from स्वतः vector पूर्णांकerrupts
 *
 * setup the handler to be called from स्वतः vector पूर्णांकerrupts instead of the
 * standard करो_IRQ(), it will be called with irq numbers in the range
 * from IRQ_AUTO_1 - IRQ_AUTO_7.
 */
व्योम __init m68k_setup_स्वतः_पूर्णांकerrupt(व्योम (*handler)(अचिन्हित पूर्णांक, काष्ठा pt_regs *))
अणु
	अगर (handler)
		*स्वतः_irqhandler_fixup = (u32)handler;
	flush_icache();
पूर्ण

/**
 * m68k_setup_user_पूर्णांकerrupt
 * @vec: first user vector पूर्णांकerrupt to handle
 * @cnt: number of active user vector पूर्णांकerrupts
 *
 * setup user vector पूर्णांकerrupts, this includes activating the specअगरied range
 * of पूर्णांकerrupts, only then these पूर्णांकerrupts can be requested (note: this is
 * dअगरferent from स्वतः vector पूर्णांकerrupts).
 */
व्योम __init m68k_setup_user_पूर्णांकerrupt(अचिन्हित पूर्णांक vec, अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक i;

	BUG_ON(IRQ_USER + cnt > NR_IRQS);
	m68k_first_user_vec = vec;
	क्रम (i = 0; i < cnt; i++)
		irq_set_chip_and_handler(i, &user_irq_chip, handle_simple_irq);
	*user_irqvec_fixup = vec - IRQ_USER;
	flush_icache();
पूर्ण

/**
 * m68k_setup_irq_controller
 * @chip: irq chip which controls specअगरied irq
 * @handle: flow handler which handles specअगरied irq
 * @irq: first irq to be managed by the controller
 * @cnt: number of irqs to be managed by the controller
 *
 * Change the controller क्रम the specअगरied range of irq, which will be used to
 * manage these irq. स्वतः/user irq alपढ़ोy have a शेष controller, which can
 * be changed as well, but the controller probably should use m68k_irq_startup/
 * m68k_irq_shutकरोwn.
 */
व्योम m68k_setup_irq_controller(काष्ठा irq_chip *chip,
			       irq_flow_handler_t handle, अचिन्हित पूर्णांक irq,
			       अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cnt; i++) अणु
		irq_set_chip(irq + i, chip);
		अगर (handle)
			irq_set_handler(irq + i, handle);
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक m68k_irq_startup_irq(अचिन्हित पूर्णांक irq)
अणु
	अगर (irq <= IRQ_AUTO_7)
		vectors[VEC_SPUR + irq] = स्वतः_पूर्णांकhandler;
	अन्यथा
		vectors[m68k_first_user_vec + irq - IRQ_USER] = user_पूर्णांकhandler;
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक m68k_irq_startup(काष्ठा irq_data *data)
अणु
	वापस m68k_irq_startup_irq(data->irq);
पूर्ण

व्योम m68k_irq_shutकरोwn(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	अगर (irq <= IRQ_AUTO_7)
		vectors[VEC_SPUR + irq] = bad_पूर्णांकhandler;
	अन्यथा
		vectors[m68k_first_user_vec + irq - IRQ_USER] = bad_पूर्णांकhandler;
पूर्ण


अचिन्हित पूर्णांक irq_canonicalize(अचिन्हित पूर्णांक irq)
अणु
#अगर_घोषित CONFIG_Q40
	अगर (MACH_IS_Q40 && irq == 11)
		irq = 10;
#पूर्ण_अगर
	वापस irq;
पूर्ण

EXPORT_SYMBOL(irq_canonicalize);


यंत्रlinkage व्योम handle_badपूर्णांक(काष्ठा pt_regs *regs)
अणु
	atomic_inc(&irq_err_count);
	pr_warn("unexpected interrupt from %u\n", regs->vector);
पूर्ण
