<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2001 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 *
 * Copyright (C) 2001 Ralf Baechle
 * Copyright (C) 2005  MIPS Technologies, Inc.	All rights reserved.
 *	Author: Maciej W. Rozycki <macro@mips.com>
 *
 * This file define the irq handler क्रम MIPS CPU पूर्णांकerrupts.
 */

/*
 * Almost all MIPS CPUs define 8 पूर्णांकerrupt sources.  They are typically
 * level triggered (i.e., cannot be cleared from CPU; must be cleared from
 * device).
 *
 * The first two are software पूर्णांकerrupts (i.e. not exposed as pins) which
 * may be used क्रम IPIs in multi-thपढ़ोed single-core प्रणालीs.
 *
 * The last one is usually the CPU समयr पूर्णांकerrupt अगर the counter रेजिस्टर
 * is present, or क्रम old CPUs with an बाह्यal FPU by convention it's the
 * FPU exception पूर्णांकerrupt.
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/setup.h>

अटल काष्ठा irq_करोमुख्य *irq_करोमुख्य;
अटल काष्ठा irq_करोमुख्य *ipi_करोमुख्य;

अटल अंतरभूत व्योम unmask_mips_irq(काष्ठा irq_data *d)
अणु
	set_c0_status(IE_SW0 << d->hwirq);
	irq_enable_hazard();
पूर्ण

अटल अंतरभूत व्योम mask_mips_irq(काष्ठा irq_data *d)
अणु
	clear_c0_status(IE_SW0 << d->hwirq);
	irq_disable_hazard();
पूर्ण

अटल काष्ठा irq_chip mips_cpu_irq_controller = अणु
	.name		= "MIPS",
	.irq_ack	= mask_mips_irq,
	.irq_mask	= mask_mips_irq,
	.irq_mask_ack	= mask_mips_irq,
	.irq_unmask	= unmask_mips_irq,
	.irq_eoi	= unmask_mips_irq,
	.irq_disable	= mask_mips_irq,
	.irq_enable	= unmask_mips_irq,
पूर्ण;

/*
 * Basically the same as above but taking care of all the MT stuff
 */

अटल अचिन्हित पूर्णांक mips_mt_cpu_irq_startup(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक vpflags = dvpe();

	clear_c0_cause(C_SW0 << d->hwirq);
	evpe(vpflags);
	unmask_mips_irq(d);
	वापस 0;
पूर्ण

/*
 * While we ack the पूर्णांकerrupt पूर्णांकerrupts are disabled and thus we करोn't need
 * to deal with concurrency issues.  Same क्रम mips_cpu_irq_end.
 */
अटल व्योम mips_mt_cpu_irq_ack(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक vpflags = dvpe();
	clear_c0_cause(C_SW0 << d->hwirq);
	evpe(vpflags);
	mask_mips_irq(d);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_IPI

अटल व्योम mips_mt_send_ipi(काष्ठा irq_data *d, अचिन्हित पूर्णांक cpu)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	पूर्णांक vpflags;

	local_irq_save(flags);

	/* We can only send IPIs to VPEs within the local core */
	WARN_ON(!cpus_are_siblings(smp_processor_id(), cpu));

	vpflags = dvpe();
	settc(cpu_vpe_id(&cpu_data[cpu]));
	ग_लिखो_vpe_c0_cause(पढ़ो_vpe_c0_cause() | (C_SW0 << hwirq));
	evpe(vpflags);

	local_irq_restore(flags);
पूर्ण

#पूर्ण_अगर /* CONFIG_GENERIC_IRQ_IPI */

अटल काष्ठा irq_chip mips_mt_cpu_irq_controller = अणु
	.name		= "MIPS",
	.irq_startup	= mips_mt_cpu_irq_startup,
	.irq_ack	= mips_mt_cpu_irq_ack,
	.irq_mask	= mask_mips_irq,
	.irq_mask_ack	= mips_mt_cpu_irq_ack,
	.irq_unmask	= unmask_mips_irq,
	.irq_eoi	= unmask_mips_irq,
	.irq_disable	= mask_mips_irq,
	.irq_enable	= unmask_mips_irq,
#अगर_घोषित CONFIG_GENERIC_IRQ_IPI
	.ipi_send_single = mips_mt_send_ipi,
#पूर्ण_अगर
पूर्ण;

यंत्रlinkage व्योम __weak plat_irq_dispatch(व्योम)
अणु
	अचिन्हित दीर्घ pending = पढ़ो_c0_cause() & पढ़ो_c0_status() & ST0_IM;
	अचिन्हित पूर्णांक virq;
	पूर्णांक irq;

	अगर (!pending) अणु
		spurious_पूर्णांकerrupt();
		वापस;
	पूर्ण

	pending >>= CAUSEB_IP;
	जबतक (pending) अणु
		irq = fls(pending) - 1;
		अगर (IS_ENABLED(CONFIG_GENERIC_IRQ_IPI) && irq < 2)
			virq = irq_linear_revmap(ipi_करोमुख्य, irq);
		अन्यथा
			virq = irq_linear_revmap(irq_करोमुख्य, irq);
		करो_IRQ(virq);
		pending &= ~BIT(irq);
	पूर्ण
पूर्ण

अटल पूर्णांक mips_cpu_पूर्णांकc_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			     irq_hw_number_t hw)
अणु
	काष्ठा irq_chip *chip;

	अगर (hw < 2 && cpu_has_mipsmt) अणु
		/* Software पूर्णांकerrupts are used क्रम MT/CMT IPI */
		chip = &mips_mt_cpu_irq_controller;
	पूर्ण अन्यथा अणु
		chip = &mips_cpu_irq_controller;
	पूर्ण

	अगर (cpu_has_vपूर्णांक)
		set_vi_handler(hw, plat_irq_dispatch);

	irq_set_chip_and_handler(irq, chip, handle_percpu_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mips_cpu_पूर्णांकc_irq_करोमुख्य_ops = अणु
	.map = mips_cpu_पूर्णांकc_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

#अगर_घोषित CONFIG_GENERIC_IRQ_IPI

काष्ठा cpu_ipi_करोमुख्य_state अणु
	DECLARE_BITMAP(allocated, 2);
पूर्ण;

अटल पूर्णांक mips_cpu_ipi_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
			      अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा cpu_ipi_करोमुख्य_state *state = करोमुख्य->host_data;
	अचिन्हित पूर्णांक i, hwirq;
	पूर्णांक ret;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		hwirq = find_first_zero_bit(state->allocated, 2);
		अगर (hwirq == 2)
			वापस -EBUSY;
		biपंचांगap_set(state->allocated, hwirq, 1);

		ret = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq,
						    &mips_mt_cpu_irq_controller,
						    शून्य);
		अगर (ret)
			वापस ret;

		ret = irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य->parent, virq + i, hwirq,
						    &mips_mt_cpu_irq_controller,
						    शून्य);

		अगर (ret)
			वापस ret;

		ret = irq_set_irq_type(virq + i, IRQ_TYPE_LEVEL_HIGH);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mips_cpu_ipi_match(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *node,
			      क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	bool is_ipi;

	चयन (bus_token) अणु
	हाल DOMAIN_BUS_IPI:
		is_ipi = d->bus_token == bus_token;
		वापस (!node || (to_of_node(d->fwnode) == node)) && is_ipi;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mips_cpu_ipi_chip_ops = अणु
	.alloc	= mips_cpu_ipi_alloc,
	.match	= mips_cpu_ipi_match,
पूर्ण;

अटल व्योम mips_cpu_रेजिस्टर_ipi_करोमुख्य(काष्ठा device_node *of_node)
अणु
	काष्ठा cpu_ipi_करोमुख्य_state *ipi_करोमुख्य_state;

	ipi_करोमुख्य_state = kzalloc(माप(*ipi_करोमुख्य_state), GFP_KERNEL);
	ipi_करोमुख्य = irq_करोमुख्य_add_hierarchy(irq_करोमुख्य,
					      IRQ_DOMAIN_FLAG_IPI_SINGLE,
					      2, of_node,
					      &mips_cpu_ipi_chip_ops,
					      ipi_करोमुख्य_state);
	अगर (!ipi_करोमुख्य)
		panic("Failed to add MIPS CPU IPI domain");
	irq_करोमुख्य_update_bus_token(ipi_करोमुख्य, DOMAIN_BUS_IPI);
पूर्ण

#अन्यथा /* !CONFIG_GENERIC_IRQ_IPI */

अटल अंतरभूत व्योम mips_cpu_रेजिस्टर_ipi_करोमुख्य(काष्ठा device_node *of_node) अणुपूर्ण

#पूर्ण_अगर /* !CONFIG_GENERIC_IRQ_IPI */

अटल व्योम __init __mips_cpu_irq_init(काष्ठा device_node *of_node)
अणु
	/* Mask पूर्णांकerrupts. */
	clear_c0_status(ST0_IM);
	clear_c0_cause(CAUSEF_IP);

	irq_करोमुख्य = irq_करोमुख्य_add_legacy(of_node, 8, MIPS_CPU_IRQ_BASE, 0,
					   &mips_cpu_पूर्णांकc_irq_करोमुख्य_ops,
					   शून्य);
	अगर (!irq_करोमुख्य)
		panic("Failed to add irqdomain for MIPS CPU");

	/*
	 * Only proceed to रेजिस्टर the software पूर्णांकerrupt IPI implementation
	 * क्रम CPUs which implement the MIPS MT (multi-thपढ़ोing) ASE.
	 */
	अगर (cpu_has_mipsmt)
		mips_cpu_रेजिस्टर_ipi_करोमुख्य(of_node);
पूर्ण

व्योम __init mips_cpu_irq_init(व्योम)
अणु
	__mips_cpu_irq_init(शून्य);
पूर्ण

पूर्णांक __init mips_cpu_irq_of_init(काष्ठा device_node *of_node,
				काष्ठा device_node *parent)
अणु
	__mips_cpu_irq_init(of_node);
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(cpu_पूर्णांकc, "mti,cpu-interrupt-controller", mips_cpu_irq_of_init);
