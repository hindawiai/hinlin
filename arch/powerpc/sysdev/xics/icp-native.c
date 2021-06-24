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
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/dbell.h>

काष्ठा icp_ipl अणु
	जोड़ अणु
		u32 word;
		u8 bytes[4];
	पूर्ण xirr_poll;
	जोड़ अणु
		u32 word;
		u8 bytes[4];
	पूर्ण xirr;
	u32 dummy;
	जोड़ अणु
		u32 word;
		u8 bytes[4];
	पूर्ण qirr;
	u32 link_a;
	u32 link_b;
	u32 link_c;
पूर्ण;

अटल काष्ठा icp_ipl __iomem *icp_native_regs[NR_CPUS];

अटल अंतरभूत अचिन्हित पूर्णांक icp_native_get_xirr(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित पूर्णांक xirr;

	/* Handled an पूर्णांकerrupt latched by KVM */
	xirr = kvmppc_get_xics_latch();
	अगर (xirr)
		वापस xirr;

	वापस in_be32(&icp_native_regs[cpu]->xirr.word);
पूर्ण

अटल अंतरभूत व्योम icp_native_set_xirr(अचिन्हित पूर्णांक value)
अणु
	पूर्णांक cpu = smp_processor_id();

	out_be32(&icp_native_regs[cpu]->xirr.word, value);
पूर्ण

अटल अंतरभूत व्योम icp_native_set_cppr(u8 value)
अणु
	पूर्णांक cpu = smp_processor_id();

	out_8(&icp_native_regs[cpu]->xirr.bytes[0], value);
पूर्ण

अटल अंतरभूत व्योम icp_native_set_qirr(पूर्णांक n_cpu, u8 value)
अणु
	out_8(&icp_native_regs[n_cpu]->qirr.bytes[0], value);
पूर्ण

अटल व्योम icp_native_set_cpu_priority(अचिन्हित अक्षर cppr)
अणु
	xics_set_base_cppr(cppr);
	icp_native_set_cppr(cppr);
	iosync();
पूर्ण

व्योम icp_native_eoi(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक hw_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);

	iosync();
	icp_native_set_xirr((xics_pop_cppr() << 24) | hw_irq);
पूर्ण

अटल व्योम icp_native_tearकरोwn_cpu(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	/* Clear any pending IPI */
	icp_native_set_qirr(cpu, 0xff);
पूर्ण

अटल व्योम icp_native_flush_ipi(व्योम)
अणु
	/* We take the ipi irq but and never वापस so we
	 * need to EOI the IPI, but want to leave our priority 0
	 *
	 * should we check all the other पूर्णांकerrupts too?
	 * should we be flagging idle loop instead?
	 * or creating some task to be scheduled?
	 */

	icp_native_set_xirr((0x00 << 24) | XICS_IPI);
पूर्ण

अटल अचिन्हित पूर्णांक icp_native_get_irq(व्योम)
अणु
	अचिन्हित पूर्णांक xirr = icp_native_get_xirr();
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
	icp_native_set_xirr(xirr);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम icp_native_cause_ipi(पूर्णांक cpu)
अणु
	kvmppc_set_host_ipi(cpu);
	icp_native_set_qirr(cpu, IPI_PRIORITY);
पूर्ण

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
व्योम icp_native_cause_ipi_rm(पूर्णांक cpu)
अणु
	/*
	 * Currently not used to send IPIs to another CPU
	 * on the same core. Only caller is KVM real mode.
	 * Need the physical address of the XICS to be
	 * previously saved in kvm_hstate in the paca.
	 */
	व्योम __iomem *xics_phys;

	/*
	 * Just like the cause_ipi functions, it is required to
	 * include a full barrier beक्रमe causing the IPI.
	 */
	xics_phys = paca_ptrs[cpu]->kvm_hstate.xics_phys;
	mb();
	__raw_rm_ग_लिखोb(IPI_PRIORITY, xics_phys + XICS_MFRR);
पूर्ण
#पूर्ण_अगर

/*
 * Called when an पूर्णांकerrupt is received on an off-line CPU to
 * clear the पूर्णांकerrupt, so that the CPU can go back to nap mode.
 */
व्योम icp_native_flush_पूर्णांकerrupt(व्योम)
अणु
	अचिन्हित पूर्णांक xirr = icp_native_get_xirr();
	अचिन्हित पूर्णांक vec = xirr & 0x00ffffff;

	अगर (vec == XICS_IRQ_SPURIOUS)
		वापस;
	अगर (vec == XICS_IPI) अणु
		/* Clear pending IPI */
		पूर्णांक cpu = smp_processor_id();
		kvmppc_clear_host_ipi(cpu);
		icp_native_set_qirr(cpu, 0xff);
	पूर्ण अन्यथा अणु
		pr_err("XICS: hw interrupt 0x%x to offline cpu, disabling\n",
		       vec);
		xics_mask_unknown_vec(vec);
	पूर्ण
	/* EOI the पूर्णांकerrupt */
	icp_native_set_xirr(xirr);
पूर्ण

व्योम xics_wake_cpu(पूर्णांक cpu)
अणु
	icp_native_set_qirr(cpu, IPI_PRIORITY);
पूर्ण
EXPORT_SYMBOL_GPL(xics_wake_cpu);

अटल irqवापस_t icp_native_ipi_action(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक cpu = smp_processor_id();

	kvmppc_clear_host_ipi(cpu);
	icp_native_set_qirr(cpu, 0xff);

	वापस smp_ipi_demux();
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल पूर्णांक __init icp_native_map_one_cpu(पूर्णांक hw_id, अचिन्हित दीर्घ addr,
					 अचिन्हित दीर्घ size)
अणु
	अक्षर *rname;
	पूर्णांक i, cpu = -1;

	/* This may look gross but it's good enough for now, we don't quite
	 * have a hard -> linux processor id matching.
	 */
	क्रम_each_possible_cpu(i) अणु
		अगर (!cpu_present(i))
			जारी;
		अगर (hw_id == get_hard_smp_processor_id(i)) अणु
			cpu = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Fail, skip that CPU. Don't print, it's normal, some XICS come up
	 * with way more entries in there than you have CPUs
	 */
	अगर (cpu == -1)
		वापस 0;

	rname = kaप्र_लिखो(GFP_KERNEL, "CPU %d [0x%x] Interrupt Presentation",
			  cpu, hw_id);

	अगर (!request_mem_region(addr, size, rname)) अणु
		pr_warn("icp_native: Could not reserve ICP MMIO for CPU %d, interrupt server #0x%x\n",
			cpu, hw_id);
		वापस -EBUSY;
	पूर्ण

	icp_native_regs[cpu] = ioremap(addr, size);
	kvmppc_set_xics_phys(cpu, addr);
	अगर (!icp_native_regs[cpu]) अणु
		pr_warn("icp_native: Failed ioremap for CPU %d, interrupt server #0x%x, addr %#lx\n",
			cpu, hw_id, addr);
		release_mem_region(addr, size);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init icp_native_init_one_node(काष्ठा device_node *np,
					   अचिन्हित पूर्णांक *indx)
अणु
	अचिन्हित पूर्णांक ilen;
	स्थिर __be32 *ireg;
	पूर्णांक i;
	पूर्णांक reg_tuple_size;
	पूर्णांक num_servers = 0;

	/* This code करोes the theorically broken assumption that the पूर्णांकerrupt
	 * server numbers are the same as the hard CPU numbers.
	 * This happens to be the हाल so far but we are playing with fire...
	 * should be fixed one of these days. -BenH.
	 */
	ireg = of_get_property(np, "ibm,interrupt-server-ranges", &ilen);

	/* Do that ever happen ? we'll know soon enough... but even good'old
	 * f80 करोes have that property ..
	 */
	WARN_ON((ireg == शून्य) || (ilen != 2*माप(u32)));

	अगर (ireg) अणु
		*indx = of_पढ़ो_number(ireg, 1);
		अगर (ilen >= 2*माप(u32))
			num_servers = of_पढ़ो_number(ireg + 1, 1);
	पूर्ण

	ireg = of_get_property(np, "reg", &ilen);
	अगर (!ireg) अणु
		pr_err("icp_native: Can't find interrupt reg property");
		वापस -1;
	पूर्ण

	reg_tuple_size = (of_n_addr_cells(np) + of_n_size_cells(np)) * 4;
	अगर (((ilen % reg_tuple_size) != 0)
	    || (num_servers && (num_servers != (ilen / reg_tuple_size)))) अणु
		pr_err("icp_native: ICP reg len (%d) != num servers (%d)",
		       ilen / reg_tuple_size, num_servers);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < (ilen / reg_tuple_size); i++) अणु
		काष्ठा resource r;
		पूर्णांक err;

		err = of_address_to_resource(np, i, &r);
		अगर (err) अणु
			pr_err("icp_native: Could not translate ICP MMIO"
			       " for interrupt server 0x%x (%d)\n", *indx, err);
			वापस -1;
		पूर्ण

		अगर (icp_native_map_one_cpu(*indx, r.start, resource_size(&r)))
			वापस -1;

		(*indx)++;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा icp_ops icp_native_ops = अणु
	.get_irq	= icp_native_get_irq,
	.eoi		= icp_native_eoi,
	.set_priority	= icp_native_set_cpu_priority,
	.tearकरोwn_cpu	= icp_native_tearकरोwn_cpu,
	.flush_ipi	= icp_native_flush_ipi,
#अगर_घोषित CONFIG_SMP
	.ipi_action	= icp_native_ipi_action,
	.cause_ipi	= icp_native_cause_ipi,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init icp_native_init(व्योम)
अणु
	काष्ठा device_node *np;
	u32 indx = 0;
	पूर्णांक found = 0;

	क्रम_each_compatible_node(np, शून्य, "ibm,ppc-xicp")
		अगर (icp_native_init_one_node(np, &indx) == 0)
			found = 1;
	अगर (!found) अणु
		क्रम_each_node_by_type(np,
			"PowerPC-External-Interrupt-Presentation") अणु
				अगर (icp_native_init_one_node(np, &indx) == 0)
					found = 1;
		पूर्ण
	पूर्ण

	अगर (found == 0)
		वापस -ENODEV;

	icp_ops = &icp_native_ops;

	वापस 0;
पूर्ण
