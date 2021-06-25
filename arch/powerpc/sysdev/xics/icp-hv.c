<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 IBM Corporation.
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
#समावेश <यंत्र/hvcall.h>

अटल अंतरभूत अचिन्हित पूर्णांक icp_hv_get_xirr(अचिन्हित अक्षर cppr)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;
	अचिन्हित पूर्णांक ret = XICS_IRQ_SPURIOUS;

	rc = plpar_hcall(H_XIRR, retbuf, cppr);
	अगर (rc == H_SUCCESS) अणु
		ret = (अचिन्हित पूर्णांक)retbuf[0];
	पूर्ण अन्यथा अणु
		pr_err("%s: bad return code xirr cppr=0x%x returned %ld\n",
			__func__, cppr, rc);
		WARN_ON_ONCE(1);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम icp_hv_set_cppr(u8 value)
अणु
	दीर्घ rc = plpar_hcall_norets(H_CPPR, value);
	अगर (rc != H_SUCCESS) अणु
		pr_err("%s: bad return code cppr cppr=0x%x returned %ld\n",
			__func__, value, rc);
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम icp_hv_set_xirr(अचिन्हित पूर्णांक value)
अणु
	दीर्घ rc = plpar_hcall_norets(H_EOI, value);
	अगर (rc != H_SUCCESS) अणु
		pr_err("%s: bad return code eoi xirr=0x%x returned %ld\n",
			__func__, value, rc);
		WARN_ON_ONCE(1);
		icp_hv_set_cppr(value >> 24);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम icp_hv_set_qirr(पूर्णांक n_cpu , u8 value)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(n_cpu);
	दीर्घ rc;

	/* Make sure all previous accesses are ordered beक्रमe IPI sending */
	mb();
	rc = plpar_hcall_norets(H_IPI, hw_cpu, value);
	अगर (rc != H_SUCCESS) अणु
		pr_err("%s: bad return code qirr cpu=%d hw_cpu=%d mfrr=0x%x "
			"returned %ld\n", __func__, n_cpu, hw_cpu, value, rc);
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल व्योम icp_hv_eoi(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);

	iosync();
	icp_hv_set_xirr((xics_pop_cppr() << 24) | hw_irq);
पूर्ण

अटल व्योम icp_hv_tearकरोwn_cpu(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	/* Clear any pending IPI */
	icp_hv_set_qirr(cpu, 0xff);
पूर्ण

अटल व्योम icp_hv_flush_ipi(व्योम)
अणु
	/* We take the ipi irq but and never वापस so we
	 * need to EOI the IPI, but want to leave our priority 0
	 *
	 * should we check all the other पूर्णांकerrupts too?
	 * should we be flagging idle loop instead?
	 * or creating some task to be scheduled?
	 */

	icp_hv_set_xirr((0x00 << 24) | XICS_IPI);
पूर्ण

अटल अचिन्हित पूर्णांक icp_hv_get_irq(व्योम)
अणु
	अचिन्हित पूर्णांक xirr = icp_hv_get_xirr(xics_cppr_top());
	अचिन्हित पूर्णांक vec = xirr & 0x00ffffff;
	अचिन्हित पूर्णांक irq;

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
	icp_hv_set_xirr(xirr);

	वापस 0;
पूर्ण

अटल व्योम icp_hv_set_cpu_priority(अचिन्हित अक्षर cppr)
अणु
	xics_set_base_cppr(cppr);
	icp_hv_set_cppr(cppr);
	iosync();
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम icp_hv_cause_ipi(पूर्णांक cpu)
अणु
	icp_hv_set_qirr(cpu, IPI_PRIORITY);
पूर्ण

अटल irqवापस_t icp_hv_ipi_action(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक cpu = smp_processor_id();

	icp_hv_set_qirr(cpu, 0xff);

	वापस smp_ipi_demux();
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल स्थिर काष्ठा icp_ops icp_hv_ops = अणु
	.get_irq	= icp_hv_get_irq,
	.eoi		= icp_hv_eoi,
	.set_priority	= icp_hv_set_cpu_priority,
	.tearकरोwn_cpu	= icp_hv_tearकरोwn_cpu,
	.flush_ipi	= icp_hv_flush_ipi,
#अगर_घोषित CONFIG_SMP
	.ipi_action	= icp_hv_ipi_action,
	.cause_ipi	= icp_hv_cause_ipi,
#पूर्ण_अगर
पूर्ण;

पूर्णांक icp_hv_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "ibm,ppc-xicp");
	अगर (!np)
		np = of_find_node_by_type(शून्य,
				    "PowerPC-External-Interrupt-Presentation");
	अगर (!np)
		वापस -ENODEV;

	icp_ops = &icp_hv_ops;

	of_node_put(np);
	वापस 0;
पूर्ण

