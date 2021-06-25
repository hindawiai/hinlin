<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017-2018 SiFive
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 */

#घोषणा pr_fmt(fmt) "riscv-intc: " fmt
#समावेश <linux/atomic.h>
#समावेश <linux/bits.h>
#समावेश <linux/cpu.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/smp.h>

अटल काष्ठा irq_करोमुख्य *पूर्णांकc_करोमुख्य;

अटल यंत्रlinkage व्योम riscv_पूर्णांकc_irq(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ cause = regs->cause & ~CAUSE_IRQ_FLAG;

	अगर (unlikely(cause >= BITS_PER_LONG))
		panic("unexpected interrupt cause");

	चयन (cause) अणु
#अगर_घोषित CONFIG_SMP
	हाल RV_IRQ_SOFT:
		/*
		 * We only use software पूर्णांकerrupts to pass IPIs, so अगर a
		 * non-SMP प्रणाली माला_लो one, then we करोn't know what to करो.
		 */
		handle_IPI(regs);
		अवरोध;
#पूर्ण_अगर
	शेष:
		handle_करोमुख्य_irq(पूर्णांकc_करोमुख्य, cause, regs);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * On RISC-V प्रणालीs local पूर्णांकerrupts are masked or unmasked by writing
 * the SIE (Supervisor Interrupt Enable) CSR.  As CSRs can only be written
 * on the local hart, these functions can only be called on the hart that
 * corresponds to the IRQ chip.
 */

अटल व्योम riscv_पूर्णांकc_irq_mask(काष्ठा irq_data *d)
अणु
	csr_clear(CSR_IE, BIT(d->hwirq));
पूर्ण

अटल व्योम riscv_पूर्णांकc_irq_unmask(काष्ठा irq_data *d)
अणु
	csr_set(CSR_IE, BIT(d->hwirq));
पूर्ण

अटल पूर्णांक riscv_पूर्णांकc_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	csr_set(CSR_IE, BIT(RV_IRQ_SOFT));
	वापस 0;
पूर्ण

अटल पूर्णांक riscv_पूर्णांकc_cpu_dying(अचिन्हित पूर्णांक cpu)
अणु
	csr_clear(CSR_IE, BIT(RV_IRQ_SOFT));
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip riscv_पूर्णांकc_chip = अणु
	.name = "RISC-V INTC",
	.irq_mask = riscv_पूर्णांकc_irq_mask,
	.irq_unmask = riscv_पूर्णांकc_irq_unmask,
पूर्ण;

अटल पूर्णांक riscv_पूर्णांकc_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				 irq_hw_number_t hwirq)
अणु
	irq_set_percpu_devid(irq);
	irq_करोमुख्य_set_info(d, irq, hwirq, &riscv_पूर्णांकc_chip, d->host_data,
			    handle_percpu_devid_irq, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops riscv_पूर्णांकc_करोमुख्य_ops = अणु
	.map	= riscv_पूर्णांकc_करोमुख्य_map,
	.xlate	= irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक __init riscv_पूर्णांकc_init(काष्ठा device_node *node,
				  काष्ठा device_node *parent)
अणु
	पूर्णांक rc, hartid;

	hartid = riscv_of_parent_hartid(node);
	अगर (hartid < 0) अणु
		pr_warn("unable to find hart id for %pOF\n", node);
		वापस 0;
	पूर्ण

	/*
	 * The DT will have one INTC DT node under each CPU (or HART)
	 * DT node so riscv_पूर्णांकc_init() function will be called once
	 * क्रम each INTC DT node. We only need to करो INTC initialization
	 * क्रम the INTC DT node beदीर्घing to boot CPU (or boot HART).
	 */
	अगर (riscv_hartid_to_cpuid(hartid) != smp_processor_id())
		वापस 0;

	पूर्णांकc_करोमुख्य = irq_करोमुख्य_add_linear(node, BITS_PER_LONG,
					    &riscv_पूर्णांकc_करोमुख्य_ops, शून्य);
	अगर (!पूर्णांकc_करोमुख्य) अणु
		pr_err("unable to add IRQ domain\n");
		वापस -ENXIO;
	पूर्ण

	rc = set_handle_irq(&riscv_पूर्णांकc_irq);
	अगर (rc) अणु
		pr_err("failed to set irq handler\n");
		वापस rc;
	पूर्ण

	cpuhp_setup_state(CPUHP_AP_IRQ_RISCV_STARTING,
			  "irqchip/riscv/intc:starting",
			  riscv_पूर्णांकc_cpu_starting,
			  riscv_पूर्णांकc_cpu_dying);

	pr_info("%d local interrupts mapped\n", BITS_PER_LONG);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(riscv, "riscv,cpu-intc", riscv_पूर्णांकc_init);
