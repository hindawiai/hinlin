<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011-12 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <यंत्र/irq.h>

#घोषणा NR_CPU_IRQS	32	/* number of irq lines coming in */
#घोषणा TIMER0_IRQ	3	/* Fixed by ISA */

/*
 * Early Hardware specअगरic Interrupt setup
 * -Platक्रमm independent, needed क्रम each CPU (not foldable पूर्णांकo init_IRQ)
 * -Called very early (start_kernel -> setup_arch -> setup_processor)
 *
 * what it करोes ?
 * -Optionally, setup the High priority Interrupts as Level 2 IRQs
 */
व्योम arc_init_IRQ(व्योम)
अणु
	अचिन्हित पूर्णांक level_mask = 0, i;

       /* Is समयr high priority Interrupt (Level2 in ARCompact jargon) */
	level_mask |= IS_ENABLED(CONFIG_ARC_COMPACT_IRQ_LEVELS) << TIMER0_IRQ;

	/*
	 * Write to रेजिस्टर, even अगर no LV2 IRQs configured to reset it
	 * in हाल bootloader had mucked with it
	 */
	ग_लिखो_aux_reg(AUX_IRQ_LEV, level_mask);

	अगर (level_mask)
		pr_info("Level-2 interrupts bitset %x\n", level_mask);

	/*
	 * Disable all IRQ lines so faulty बाह्यal hardware won't
	 * trigger पूर्णांकerrupt that kernel is not पढ़ोy to handle.
	 */
	क्रम (i = TIMER0_IRQ; i < NR_CPU_IRQS; i++) अणु
		अचिन्हित पूर्णांक ienb;

		ienb = पढ़ो_aux_reg(AUX_IENABLE);
		ienb &= ~(1 << i);
		ग_लिखो_aux_reg(AUX_IENABLE, ienb);
	पूर्ण
पूर्ण

/*
 * ARC700 core includes a simple on-chip पूर्णांकc supporting
 * -per IRQ enable/disable
 * -2 levels of पूर्णांकerrupts (high/low)
 * -all पूर्णांकerrupts being level triggered
 *
 * To reduce platक्रमm code, we assume all IRQs directly hooked-up पूर्णांकo पूर्णांकc.
 * Platक्रमms with बाह्यal पूर्णांकc, hence cascaded IRQs, are मुक्त to over-ride
 * below, per IRQ.
 */

अटल व्योम arc_irq_mask(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक ienb;

	ienb = पढ़ो_aux_reg(AUX_IENABLE);
	ienb &= ~(1 << data->hwirq);
	ग_लिखो_aux_reg(AUX_IENABLE, ienb);
पूर्ण

अटल व्योम arc_irq_unmask(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक ienb;

	ienb = पढ़ो_aux_reg(AUX_IENABLE);
	ienb |= (1 << data->hwirq);
	ग_लिखो_aux_reg(AUX_IENABLE, ienb);
पूर्ण

अटल काष्ठा irq_chip onchip_पूर्णांकc = अणु
	.name           = "ARC In-core Intc",
	.irq_mask	= arc_irq_mask,
	.irq_unmask	= arc_irq_unmask,
पूर्ण;

अटल पूर्णांक arc_पूर्णांकc_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			       irq_hw_number_t hw)
अणु
	चयन (hw) अणु
	हाल TIMER0_IRQ:
		irq_set_percpu_devid(irq);
		irq_set_chip_and_handler(irq, &onchip_पूर्णांकc, handle_percpu_irq);
		अवरोध;
	शेष:
		irq_set_chip_and_handler(irq, &onchip_पूर्णांकc, handle_level_irq);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops arc_पूर्णांकc_करोमुख्य_ops = अणु
	.xlate = irq_करोमुख्य_xlate_onecell,
	.map = arc_पूर्णांकc_करोमुख्य_map,
पूर्ण;

अटल पूर्णांक __init
init_onchip_IRQ(काष्ठा device_node *पूर्णांकc, काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *root_करोमुख्य;

	अगर (parent)
		panic("DeviceTree incore intc not a root irq controller\n");

	root_करोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc, NR_CPU_IRQS,
					    &arc_पूर्णांकc_करोमुख्य_ops, शून्य);
	अगर (!root_करोमुख्य)
		panic("root irq domain not avail\n");

	/*
	 * Needed क्रम primary करोमुख्य lookup to succeed
	 * This is a primary irqchip, and can never have a parent
	 */
	irq_set_शेष_host(root_करोमुख्य);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(arc_पूर्णांकc, "snps,arc700-intc", init_onchip_IRQ);

/*
 * arch_local_irq_enable - Enable पूर्णांकerrupts.
 *
 * 1. Explicitly called to re-enable पूर्णांकerrupts
 * 2. Implicitly called from spin_unlock_irq, ग_लिखो_unlock_irq etc
 *    which maybe in hard ISR itself
 *
 * Semantics of this function change depending on where it is called from:
 *
 * -If called from hard-ISR, it must not invert पूर्णांकerrupt priorities
 *  e.g. suppose TIMER is high priority (Level 2) IRQ
 *    Time hard-ISR, समयr_पूर्णांकerrupt( ) calls spin_unlock_irq several बार.
 *    Here local_irq_enable( ) shd not re-enable lower priority पूर्णांकerrupts
 * -If called from soft-ISR, it must re-enable all पूर्णांकerrupts
 *    soft ISR are low prioity jobs which can be very slow, thus all IRQs
 *    must be enabled जबतक they run.
 *    Now hardware context wise we may still be in L2 ISR (not करोne rtie)
 *    still we must re-enable both L1 and L2 IRQs
 *  Another twist is prev scenario with flow being
 *     L1 ISR ==> पूर्णांकerrupted by L2 ISR  ==> L2 soft ISR
 *     here we must not re-enable Ll as prev Ll Interrupt's h/w context will get
 *     over-written (this is deficiency in ARC700 Interrupt mechanism)
 */

#अगर_घोषित CONFIG_ARC_COMPACT_IRQ_LEVELS	/* Complex version क्रम 2 IRQ levels */

व्योम arch_local_irq_enable(व्योम)
अणु
	अचिन्हित दीर्घ flags = arch_local_save_flags();

	अगर (flags & STATUS_A2_MASK)
		flags |= STATUS_E2_MASK;
	अन्यथा अगर (flags & STATUS_A1_MASK)
		flags |= STATUS_E1_MASK;

	arch_local_irq_restore(flags);
पूर्ण

EXPORT_SYMBOL(arch_local_irq_enable);
#पूर्ण_अगर
