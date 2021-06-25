<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016 IBM Corporation.
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/kvm_ppc.h>

अटल व्योम icp_opal_tearकरोwn_cpu(व्योम)
अणु
	पूर्णांक hw_cpu = hard_smp_processor_id();

	/* Clear any pending IPI */
	opal_पूर्णांक_set_mfrr(hw_cpu, 0xff);
पूर्ण

अटल व्योम icp_opal_flush_ipi(व्योम)
अणु
	/*
	 * We take the ipi irq but and never वापस so we need to EOI the IPI,
	 * but want to leave our priority 0.
	 *
	 * Should we check all the other पूर्णांकerrupts too?
	 * Should we be flagging idle loop instead?
	 * Or creating some task to be scheduled?
	 */
	अगर (opal_पूर्णांक_eoi((0x00 << 24) | XICS_IPI) > 0)
		क्रमce_बाह्यal_irq_replay();
पूर्ण

अटल अचिन्हित पूर्णांक icp_opal_get_xirr(व्योम)
अणु
	अचिन्हित पूर्णांक kvm_xirr;
	__be32 hw_xirr;
	पूर्णांक64_t rc;

	/* Handle an पूर्णांकerrupt latched by KVM first */
	kvm_xirr = kvmppc_get_xics_latch();
	अगर (kvm_xirr)
		वापस kvm_xirr;

	/* Then ask OPAL */
	rc = opal_पूर्णांक_get_xirr(&hw_xirr, false);
	अगर (rc < 0)
		वापस 0;
	वापस be32_to_cpu(hw_xirr);
पूर्ण

अटल अचिन्हित पूर्णांक icp_opal_get_irq(व्योम)
अणु
	अचिन्हित पूर्णांक xirr;
	अचिन्हित पूर्णांक vec;
	अचिन्हित पूर्णांक irq;

	xirr = icp_opal_get_xirr();
	vec = xirr & 0x00ffffff;
	अगर (vec == XICS_IRQ_SPURIOUS)
		वापस 0;

	irq = irq_find_mapping(xics_host, vec);
	अगर (likely(irq)) अणु
		xics_push_cppr(vec);
		वापस irq;
	पूर्ण

	/* We करोn't have a linux mapping, so have rtas mask it. */
	xics_mask_unknown_vec(vec);

	/* We might learn about it later, so EOI it */
	अगर (opal_पूर्णांक_eoi(xirr) > 0)
		क्रमce_बाह्यal_irq_replay();

	वापस 0;
पूर्ण

अटल व्योम icp_opal_set_cpu_priority(अचिन्हित अक्षर cppr)
अणु
	/*
	 * Here be dragons. The caller has asked to allow only IPI's and not
	 * बाह्यal पूर्णांकerrupts. But OPAL XIVE करोesn't support that. So instead
	 * of allowing no पूर्णांकerrupts allow all. That's still not right, but
	 * currently the only caller who करोes this is xics_migrate_irqs_away()
	 * and it works in that हाल.
	 */
	अगर (cppr >= DEFAULT_PRIORITY)
		cppr = LOWEST_PRIORITY;

	xics_set_base_cppr(cppr);
	opal_पूर्णांक_set_cppr(cppr);
	iosync();
पूर्ण

अटल व्योम icp_opal_eoi(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	पूर्णांक64_t rc;

	iosync();
	rc = opal_पूर्णांक_eoi((xics_pop_cppr() << 24) | hw_irq);

	/*
	 * EOI tells us whether there are more पूर्णांकerrupts to fetch.
	 *
	 * Some HW implementations might not be able to send us another
	 * बाह्यal पूर्णांकerrupt in that हाल, so we क्रमce a replay.
	 */
	अगर (rc > 0)
		क्रमce_बाह्यal_irq_replay();
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम icp_opal_cause_ipi(पूर्णांक cpu)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);

	kvmppc_set_host_ipi(cpu);
	opal_पूर्णांक_set_mfrr(hw_cpu, IPI_PRIORITY);
पूर्ण

अटल irqवापस_t icp_opal_ipi_action(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक cpu = smp_processor_id();

	kvmppc_clear_host_ipi(cpu);
	opal_पूर्णांक_set_mfrr(get_hard_smp_processor_id(cpu), 0xff);

	वापस smp_ipi_demux();
पूर्ण

/*
 * Called when an पूर्णांकerrupt is received on an off-line CPU to
 * clear the पूर्णांकerrupt, so that the CPU can go back to nap mode.
 */
व्योम icp_opal_flush_पूर्णांकerrupt(व्योम)
अणु
	अचिन्हित पूर्णांक xirr;
	अचिन्हित पूर्णांक vec;

	करो अणु
		xirr = icp_opal_get_xirr();
		vec = xirr & 0x00ffffff;
		अगर (vec == XICS_IRQ_SPURIOUS)
			अवरोध;
		अगर (vec == XICS_IPI) अणु
			/* Clear pending IPI */
			पूर्णांक cpu = smp_processor_id();
			kvmppc_clear_host_ipi(cpu);
			opal_पूर्णांक_set_mfrr(get_hard_smp_processor_id(cpu), 0xff);
		पूर्ण अन्यथा अणु
			pr_err("XICS: hw interrupt 0x%x to offline cpu, "
			       "disabling\n", vec);
			xics_mask_unknown_vec(vec);
		पूर्ण

		/* EOI the पूर्णांकerrupt */
	पूर्ण जबतक (opal_पूर्णांक_eoi(xirr) > 0);
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल स्थिर काष्ठा icp_ops icp_opal_ops = अणु
	.get_irq	= icp_opal_get_irq,
	.eoi		= icp_opal_eoi,
	.set_priority	= icp_opal_set_cpu_priority,
	.tearकरोwn_cpu	= icp_opal_tearकरोwn_cpu,
	.flush_ipi	= icp_opal_flush_ipi,
#अगर_घोषित CONFIG_SMP
	.ipi_action	= icp_opal_ipi_action,
	.cause_ipi	= icp_opal_cause_ipi,
#पूर्ण_अगर
पूर्ण;

पूर्णांक icp_opal_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "ibm,opal-intc");
	अगर (!np)
		वापस -ENODEV;

	icp_ops = &icp_opal_ops;

	prपूर्णांकk("XICS: Using OPAL ICP fallbacks\n");

	वापस 0;
पूर्ण

