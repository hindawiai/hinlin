<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright The Asahi Linux Contributors
 *
 * Based on irq-lpc32xx:
 *   Copyright 2015-2016 Vladimir Zapolskiy <vz@mleia.com>
 * Based on irq-bcm2836:
 *   Copyright 2015 Broadcom
 */

/*
 * AIC is a fairly simple पूर्णांकerrupt controller with the following features:
 *
 * - 896 level-triggered hardware IRQs
 *   - Single mask bit per IRQ
 *   - Per-IRQ affinity setting
 *   - Automatic masking on event delivery (स्वतः-ack)
 *   - Software triggering (ORed with hw line)
 * - 2 per-CPU IPIs (meant as "self" and "other", but they are
 *   पूर्णांकerchangeable अगर not symmetric)
 * - Automatic prioritization (single event/ack रेजिस्टर per CPU, lower IRQs =
 *   higher priority)
 * - Automatic masking on ack
 * - Default "this CPU" रेजिस्टर view and explicit per-CPU views
 *
 * In addition, this driver also handles FIQs, as these are routed to the same
 * IRQ vector. These are used क्रम Fast IPIs (TODO), the ARMv8 समयr IRQs, and
 * perक्रमmance counters (TODO).
 *
 * Implementation notes:
 *
 * - This driver creates two IRQ करोमुख्यs, one क्रम HW IRQs and पूर्णांकernal FIQs,
 *   and one क्रम IPIs.
 * - Since Linux needs more than 2 IPIs, we implement a software IRQ controller
 *   and funnel all IPIs पूर्णांकo one per-CPU IPI (the second "self" IPI is unused).
 * - FIQ hwirq numbers are asचिन्हित after true hwirqs, and are per-cpu.
 * - DT bindings use 3-cell क्रमm (like GIC):
 *   - <0 nr flags> - hwirq #nr
 *   - <1 nr flags> - FIQ #nr
 *     - nr=0  Physical HV समयr
 *     - nr=1  Virtual HV समयr
 *     - nr=2  Physical guest समयr
 *     - nr=3  Virtual guest समयr
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bits.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/virt.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/apple-aic.h>

/*
 * AIC रेजिस्टरs (MMIO)
 */

#घोषणा AIC_INFO		0x0004
#घोषणा AIC_INFO_NR_HW		GENMASK(15, 0)

#घोषणा AIC_CONFIG		0x0010

#घोषणा AIC_WHOAMI		0x2000
#घोषणा AIC_EVENT		0x2004
#घोषणा AIC_EVENT_TYPE		GENMASK(31, 16)
#घोषणा AIC_EVENT_NUM		GENMASK(15, 0)

#घोषणा AIC_EVENT_TYPE_HW	1
#घोषणा AIC_EVENT_TYPE_IPI	4
#घोषणा AIC_EVENT_IPI_OTHER	1
#घोषणा AIC_EVENT_IPI_SELF	2

#घोषणा AIC_IPI_SEND		0x2008
#घोषणा AIC_IPI_ACK		0x200c
#घोषणा AIC_IPI_MASK_SET	0x2024
#घोषणा AIC_IPI_MASK_CLR	0x2028

#घोषणा AIC_IPI_SEND_CPU(cpu)	BIT(cpu)

#घोषणा AIC_IPI_OTHER		BIT(0)
#घोषणा AIC_IPI_SELF		BIT(31)

#घोषणा AIC_TARGET_CPU		0x3000
#घोषणा AIC_SW_SET		0x4000
#घोषणा AIC_SW_CLR		0x4080
#घोषणा AIC_MASK_SET		0x4100
#घोषणा AIC_MASK_CLR		0x4180

#घोषणा AIC_CPU_IPI_SET(cpu)	(0x5008 + ((cpu) << 7))
#घोषणा AIC_CPU_IPI_CLR(cpu)	(0x500c + ((cpu) << 7))
#घोषणा AIC_CPU_IPI_MASK_SET(cpu) (0x5024 + ((cpu) << 7))
#घोषणा AIC_CPU_IPI_MASK_CLR(cpu) (0x5028 + ((cpu) << 7))

#घोषणा MASK_REG(x)		(4 * ((x) >> 5))
#घोषणा MASK_BIT(x)		BIT((x) & GENMASK(4, 0))

/*
 * IMP-DEF sysregs that control FIQ sources
 * Note: sysreg-based IPIs are not supported yet.
 */

/* Core PMC control रेजिस्टर */
#घोषणा SYS_IMP_APL_PMCR0_EL1		sys_reg(3, 1, 15, 0, 0)
#घोषणा PMCR0_IMODE			GENMASK(10, 8)
#घोषणा PMCR0_IMODE_OFF			0
#घोषणा PMCR0_IMODE_PMI			1
#घोषणा PMCR0_IMODE_AIC			2
#घोषणा PMCR0_IMODE_HALT		3
#घोषणा PMCR0_IMODE_FIQ			4
#घोषणा PMCR0_IACT			BIT(11)

/* IPI request रेजिस्टरs */
#घोषणा SYS_IMP_APL_IPI_RR_LOCAL_EL1	sys_reg(3, 5, 15, 0, 0)
#घोषणा SYS_IMP_APL_IPI_RR_GLOBAL_EL1	sys_reg(3, 5, 15, 0, 1)
#घोषणा IPI_RR_CPU			GENMASK(7, 0)
/* Cluster only used क्रम the GLOBAL रेजिस्टर */
#घोषणा IPI_RR_CLUSTER			GENMASK(23, 16)
#घोषणा IPI_RR_TYPE			GENMASK(29, 28)
#घोषणा IPI_RR_IMMEDIATE		0
#घोषणा IPI_RR_RETRACT			1
#घोषणा IPI_RR_DEFERRED			2
#घोषणा IPI_RR_NOWAKE			3

/* IPI status रेजिस्टर */
#घोषणा SYS_IMP_APL_IPI_SR_EL1		sys_reg(3, 5, 15, 1, 1)
#घोषणा IPI_SR_PENDING			BIT(0)

/* Guest समयr FIQ enable रेजिस्टर */
#घोषणा SYS_IMP_APL_VM_TMR_FIQ_ENA_EL2	sys_reg(3, 5, 15, 1, 3)
#घोषणा VM_TMR_FIQ_ENABLE_V		BIT(0)
#घोषणा VM_TMR_FIQ_ENABLE_P		BIT(1)

/* Deferred IPI countकरोwn रेजिस्टर */
#घोषणा SYS_IMP_APL_IPI_CR_EL1		sys_reg(3, 5, 15, 3, 1)

/* Uncore PMC control रेजिस्टर */
#घोषणा SYS_IMP_APL_UPMCR0_EL1		sys_reg(3, 7, 15, 0, 4)
#घोषणा UPMCR0_IMODE			GENMASK(18, 16)
#घोषणा UPMCR0_IMODE_OFF		0
#घोषणा UPMCR0_IMODE_AIC		2
#घोषणा UPMCR0_IMODE_HALT		3
#घोषणा UPMCR0_IMODE_FIQ		4

/* Uncore PMC status रेजिस्टर */
#घोषणा SYS_IMP_APL_UPMSR_EL1		sys_reg(3, 7, 15, 6, 4)
#घोषणा UPMSR_IACT			BIT(0)

#घोषणा AIC_NR_FIQ		4
#घोषणा AIC_NR_SWIPI		32

/*
 * FIQ hwirq index definitions: FIQ sources use the DT binding defines
 * directly, except that समयrs are special. At the irqchip level, the
 * two समयr types are represented by their access method: _EL0 रेजिस्टरs
 * or _EL02 रेजिस्टरs. In the DT binding, the समयrs are represented
 * by their purpose (HV or guest). This mapping is क्रम when the kernel is
 * running at EL2 (with VHE). When the kernel is running at EL1, the
 * mapping dअगरfers and aic_irq_करोमुख्य_translate() perक्रमms the remapping.
 */

#घोषणा AIC_TMR_EL0_PHYS	AIC_TMR_HV_PHYS
#घोषणा AIC_TMR_EL0_VIRT	AIC_TMR_HV_VIRT
#घोषणा AIC_TMR_EL02_PHYS	AIC_TMR_GUEST_PHYS
#घोषणा AIC_TMR_EL02_VIRT	AIC_TMR_GUEST_VIRT

काष्ठा aic_irq_chip अणु
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *hw_करोमुख्य;
	काष्ठा irq_करोमुख्य *ipi_करोमुख्य;
	पूर्णांक nr_hw;
	पूर्णांक ipi_hwirq;
पूर्ण;

अटल DEFINE_PER_CPU(uपूर्णांक32_t, aic_fiq_unmasked);

अटल DEFINE_PER_CPU(atomic_t, aic_vipi_flag);
अटल DEFINE_PER_CPU(atomic_t, aic_vipi_enable);

अटल काष्ठा aic_irq_chip *aic_irqc;

अटल व्योम aic_handle_ipi(काष्ठा pt_regs *regs);

अटल u32 aic_ic_पढ़ो(काष्ठा aic_irq_chip *ic, u32 reg)
अणु
	वापस पढ़ोl_relaxed(ic->base + reg);
पूर्ण

अटल व्योम aic_ic_ग_लिखो(काष्ठा aic_irq_chip *ic, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, ic->base + reg);
पूर्ण

/*
 * IRQ irqchip
 */

अटल व्योम aic_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा aic_irq_chip *ic = irq_data_get_irq_chip_data(d);

	aic_ic_ग_लिखो(ic, AIC_MASK_SET + MASK_REG(irqd_to_hwirq(d)),
		     MASK_BIT(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम aic_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा aic_irq_chip *ic = irq_data_get_irq_chip_data(d);

	aic_ic_ग_लिखो(ic, AIC_MASK_CLR + MASK_REG(d->hwirq),
		     MASK_BIT(irqd_to_hwirq(d)));
पूर्ण

अटल व्योम aic_irq_eoi(काष्ठा irq_data *d)
अणु
	/*
	 * Reading the पूर्णांकerrupt reason स्वतःmatically acknowledges and masks
	 * the IRQ, so we just unmask it here अगर needed.
	 */
	अगर (!irqd_irq_disabled(d) && !irqd_irq_masked(d))
		aic_irq_unmask(d);
पूर्ण

अटल व्योम __exception_irq_entry aic_handle_irq(काष्ठा pt_regs *regs)
अणु
	काष्ठा aic_irq_chip *ic = aic_irqc;
	u32 event, type, irq;

	करो अणु
		/*
		 * We cannot use a relaxed पढ़ो here, as पढ़ोs from DMA buffers
		 * need to be ordered after the IRQ fires.
		 */
		event = पढ़ोl(ic->base + AIC_EVENT);
		type = FIELD_GET(AIC_EVENT_TYPE, event);
		irq = FIELD_GET(AIC_EVENT_NUM, event);

		अगर (type == AIC_EVENT_TYPE_HW)
			handle_करोमुख्य_irq(aic_irqc->hw_करोमुख्य, irq, regs);
		अन्यथा अगर (type == AIC_EVENT_TYPE_IPI && irq == 1)
			aic_handle_ipi(regs);
		अन्यथा अगर (event != 0)
			pr_err_ratelimited("Unknown IRQ event %d, %d\n", type, irq);
	पूर्ण जबतक (event);

	/*
	 * vGIC मुख्यtenance पूर्णांकerrupts end up here too, so we need to check
	 * क्रम them separately. This should never trigger अगर KVM is working
	 * properly, because it will have alपढ़ोy taken care of clearing it
	 * on guest निकास beक्रमe this handler runs.
	 */
	अगर (is_kernel_in_hyp_mode() && (पढ़ो_sysreg_s(SYS_ICH_HCR_EL2) & ICH_HCR_EN) &&
		पढ़ो_sysreg_s(SYS_ICH_MISR_EL2) != 0) अणु
		pr_err_ratelimited("vGIC IRQ fired and not handled by KVM, disabling.\n");
		sysreg_clear_set_s(SYS_ICH_HCR_EL2, ICH_HCR_EN, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक aic_irq_set_affinity(काष्ठा irq_data *d,
				स्थिर काष्ठा cpumask *mask_val, bool क्रमce)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	काष्ठा aic_irq_chip *ic = irq_data_get_irq_chip_data(d);
	पूर्णांक cpu;

	अगर (क्रमce)
		cpu = cpumask_first(mask_val);
	अन्यथा
		cpu = cpumask_any_and(mask_val, cpu_online_mask);

	aic_ic_ग_लिखो(ic, AIC_TARGET_CPU + hwirq * 4, BIT(cpu));
	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल पूर्णांक aic_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	/*
	 * Some IRQs (e.g. MSIs) implicitly have edge semantics, and we करोn't
	 * have a way to find out the type of any given IRQ, so just allow both.
	 */
	वापस (type == IRQ_TYPE_LEVEL_HIGH || type == IRQ_TYPE_EDGE_RISING) ? 0 : -EINVAL;
पूर्ण

अटल काष्ठा irq_chip aic_chip = अणु
	.name = "AIC",
	.irq_mask = aic_irq_mask,
	.irq_unmask = aic_irq_unmask,
	.irq_eoi = aic_irq_eoi,
	.irq_set_affinity = aic_irq_set_affinity,
	.irq_set_type = aic_irq_set_type,
पूर्ण;

/*
 * FIQ irqchip
 */

अटल अचिन्हित दीर्घ aic_fiq_get_idx(काष्ठा irq_data *d)
अणु
	काष्ठा aic_irq_chip *ic = irq_data_get_irq_chip_data(d);

	वापस irqd_to_hwirq(d) - ic->nr_hw;
पूर्ण

अटल व्योम aic_fiq_set_mask(काष्ठा irq_data *d)
अणु
	/* Only the guest समयrs have real mask bits, unक्रमtunately. */
	चयन (aic_fiq_get_idx(d)) अणु
	हाल AIC_TMR_EL02_PHYS:
		sysreg_clear_set_s(SYS_IMP_APL_VM_TMR_FIQ_ENA_EL2, VM_TMR_FIQ_ENABLE_P, 0);
		isb();
		अवरोध;
	हाल AIC_TMR_EL02_VIRT:
		sysreg_clear_set_s(SYS_IMP_APL_VM_TMR_FIQ_ENA_EL2, VM_TMR_FIQ_ENABLE_V, 0);
		isb();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम aic_fiq_clear_mask(काष्ठा irq_data *d)
अणु
	चयन (aic_fiq_get_idx(d)) अणु
	हाल AIC_TMR_EL02_PHYS:
		sysreg_clear_set_s(SYS_IMP_APL_VM_TMR_FIQ_ENA_EL2, 0, VM_TMR_FIQ_ENABLE_P);
		isb();
		अवरोध;
	हाल AIC_TMR_EL02_VIRT:
		sysreg_clear_set_s(SYS_IMP_APL_VM_TMR_FIQ_ENA_EL2, 0, VM_TMR_FIQ_ENABLE_V);
		isb();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम aic_fiq_mask(काष्ठा irq_data *d)
अणु
	aic_fiq_set_mask(d);
	__this_cpu_and(aic_fiq_unmasked, ~BIT(aic_fiq_get_idx(d)));
पूर्ण

अटल व्योम aic_fiq_unmask(काष्ठा irq_data *d)
अणु
	aic_fiq_clear_mask(d);
	__this_cpu_or(aic_fiq_unmasked, BIT(aic_fiq_get_idx(d)));
पूर्ण

अटल व्योम aic_fiq_eoi(काष्ठा irq_data *d)
अणु
	/* We mask to ack (where we can), so we need to unmask at EOI. */
	अगर (__this_cpu_पढ़ो(aic_fiq_unmasked) & BIT(aic_fiq_get_idx(d)))
		aic_fiq_clear_mask(d);
पूर्ण

#घोषणा TIMER_FIRING(x)                                                        \
	(((x) & (ARCH_TIMER_CTRL_ENABLE | ARCH_TIMER_CTRL_IT_MASK |            \
		 ARCH_TIMER_CTRL_IT_STAT)) ==                                  \
	 (ARCH_TIMER_CTRL_ENABLE | ARCH_TIMER_CTRL_IT_STAT))

अटल व्योम __exception_irq_entry aic_handle_fiq(काष्ठा pt_regs *regs)
अणु
	/*
	 * It would be really nice अगर we had a प्रणाली रेजिस्टर that lets us get
	 * the FIQ source state without having to peek करोwn पूर्णांकo sources...
	 * but such a रेजिस्टर करोes not seem to exist.
	 *
	 * So, we have these potential sources to test क्रम:
	 *  - Fast IPIs (not yet used)
	 *  - The 4 समयrs (CNTP, CNTV क्रम each of HV and guest)
	 *  - Per-core PMCs (not yet supported)
	 *  - Per-cluster uncore PMCs (not yet supported)
	 *
	 * Since not dealing with any of these results in a FIQ storm,
	 * we check क्रम everything here, even things we करोn't support yet.
	 */

	अगर (पढ़ो_sysreg_s(SYS_IMP_APL_IPI_SR_EL1) & IPI_SR_PENDING) अणु
		pr_err_ratelimited("Fast IPI fired. Acking.\n");
		ग_लिखो_sysreg_s(IPI_SR_PENDING, SYS_IMP_APL_IPI_SR_EL1);
	पूर्ण

	अगर (TIMER_FIRING(पढ़ो_sysreg(cntp_ctl_el0)))
		handle_करोमुख्य_irq(aic_irqc->hw_करोमुख्य,
				  aic_irqc->nr_hw + AIC_TMR_EL0_PHYS, regs);

	अगर (TIMER_FIRING(पढ़ो_sysreg(cntv_ctl_el0)))
		handle_करोमुख्य_irq(aic_irqc->hw_करोमुख्य,
				  aic_irqc->nr_hw + AIC_TMR_EL0_VIRT, regs);

	अगर (is_kernel_in_hyp_mode()) अणु
		uपूर्णांक64_t enabled = पढ़ो_sysreg_s(SYS_IMP_APL_VM_TMR_FIQ_ENA_EL2);

		अगर ((enabled & VM_TMR_FIQ_ENABLE_P) &&
		    TIMER_FIRING(पढ़ो_sysreg_s(SYS_CNTP_CTL_EL02)))
			handle_करोमुख्य_irq(aic_irqc->hw_करोमुख्य,
					  aic_irqc->nr_hw + AIC_TMR_EL02_PHYS, regs);

		अगर ((enabled & VM_TMR_FIQ_ENABLE_V) &&
		    TIMER_FIRING(पढ़ो_sysreg_s(SYS_CNTV_CTL_EL02)))
			handle_करोमुख्य_irq(aic_irqc->hw_करोमुख्य,
					  aic_irqc->nr_hw + AIC_TMR_EL02_VIRT, regs);
	पूर्ण

	अगर ((पढ़ो_sysreg_s(SYS_IMP_APL_PMCR0_EL1) & (PMCR0_IMODE | PMCR0_IACT)) ==
			(FIELD_PREP(PMCR0_IMODE, PMCR0_IMODE_FIQ) | PMCR0_IACT)) अणु
		/*
		 * Not supported yet, let's figure out how to handle this when
		 * we implement these proprietary perक्रमmance counters. For now,
		 * just mask it and move on.
		 */
		pr_err_ratelimited("PMC FIQ fired. Masking.\n");
		sysreg_clear_set_s(SYS_IMP_APL_PMCR0_EL1, PMCR0_IMODE | PMCR0_IACT,
				   FIELD_PREP(PMCR0_IMODE, PMCR0_IMODE_OFF));
	पूर्ण

	अगर (FIELD_GET(UPMCR0_IMODE, पढ़ो_sysreg_s(SYS_IMP_APL_UPMCR0_EL1)) == UPMCR0_IMODE_FIQ &&
			(पढ़ो_sysreg_s(SYS_IMP_APL_UPMSR_EL1) & UPMSR_IACT)) अणु
		/* Same story with uncore PMCs */
		pr_err_ratelimited("Uncore PMC FIQ fired. Masking.\n");
		sysreg_clear_set_s(SYS_IMP_APL_UPMCR0_EL1, UPMCR0_IMODE,
				   FIELD_PREP(UPMCR0_IMODE, UPMCR0_IMODE_OFF));
	पूर्ण
पूर्ण

अटल पूर्णांक aic_fiq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	वापस (type == IRQ_TYPE_LEVEL_HIGH) ? 0 : -EINVAL;
पूर्ण

अटल काष्ठा irq_chip fiq_chip = अणु
	.name = "AIC-FIQ",
	.irq_mask = aic_fiq_mask,
	.irq_unmask = aic_fiq_unmask,
	.irq_ack = aic_fiq_set_mask,
	.irq_eoi = aic_fiq_eoi,
	.irq_set_type = aic_fiq_set_type,
पूर्ण;

/*
 * Main IRQ करोमुख्य
 */

अटल पूर्णांक aic_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *id, अचिन्हित पूर्णांक irq,
			      irq_hw_number_t hw)
अणु
	काष्ठा aic_irq_chip *ic = id->host_data;

	अगर (hw < ic->nr_hw) अणु
		irq_करोमुख्य_set_info(id, irq, hw, &aic_chip, id->host_data,
				    handle_fasteoi_irq, शून्य, शून्य);
		irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(irq)));
	पूर्ण अन्यथा अणु
		irq_set_percpu_devid(irq);
		irq_करोमुख्य_set_info(id, irq, hw, &fiq_chip, id->host_data,
				    handle_percpu_devid_irq, शून्य, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aic_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *id,
				    काष्ठा irq_fwspec *fwspec,
				    अचिन्हित दीर्घ *hwirq,
				    अचिन्हित पूर्णांक *type)
अणु
	काष्ठा aic_irq_chip *ic = id->host_data;

	अगर (fwspec->param_count != 3 || !is_of_node(fwspec->fwnode))
		वापस -EINVAL;

	चयन (fwspec->param[0]) अणु
	हाल AIC_IRQ:
		अगर (fwspec->param[1] >= ic->nr_hw)
			वापस -EINVAL;
		*hwirq = fwspec->param[1];
		अवरोध;
	हाल AIC_FIQ:
		अगर (fwspec->param[1] >= AIC_NR_FIQ)
			वापस -EINVAL;
		*hwirq = ic->nr_hw + fwspec->param[1];

		/*
		 * In EL1 the non-redirected रेजिस्टरs are the guest's,
		 * not EL2's, so remap the hwirqs to match.
		 */
		अगर (!is_kernel_in_hyp_mode()) अणु
			चयन (fwspec->param[1]) अणु
			हाल AIC_TMR_GUEST_PHYS:
				*hwirq = ic->nr_hw + AIC_TMR_EL0_PHYS;
				अवरोध;
			हाल AIC_TMR_GUEST_VIRT:
				*hwirq = ic->nr_hw + AIC_TMR_EL0_VIRT;
				अवरोध;
			हाल AIC_TMR_HV_PHYS:
			हाल AIC_TMR_HV_VIRT:
				वापस -ENOENT;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक aic_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	अचिन्हित पूर्णांक type = IRQ_TYPE_NONE;
	काष्ठा irq_fwspec *fwspec = arg;
	irq_hw_number_t hwirq;
	पूर्णांक i, ret;

	ret = aic_irq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		ret = aic_irq_करोमुख्य_map(करोमुख्य, virq + i, hwirq + i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम aic_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq + i);

		irq_set_handler(virq + i, शून्य);
		irq_करोमुख्य_reset_irq_data(d);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops aic_irq_करोमुख्य_ops = अणु
	.translate	= aic_irq_करोमुख्य_translate,
	.alloc		= aic_irq_करोमुख्य_alloc,
	.मुक्त		= aic_irq_करोमुख्य_मुक्त,
पूर्ण;

/*
 * IPI irqchip
 */

अटल व्योम aic_ipi_mask(काष्ठा irq_data *d)
अणु
	u32 irq_bit = BIT(irqd_to_hwirq(d));

	/* No specअगरic ordering requirements needed here. */
	atomic_andnot(irq_bit, this_cpu_ptr(&aic_vipi_enable));
पूर्ण

अटल व्योम aic_ipi_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा aic_irq_chip *ic = irq_data_get_irq_chip_data(d);
	u32 irq_bit = BIT(irqd_to_hwirq(d));

	atomic_or(irq_bit, this_cpu_ptr(&aic_vipi_enable));

	/*
	 * The atomic_or() above must complete beक्रमe the atomic_पढ़ो()
	 * below to aव्योम racing aic_ipi_send_mask().
	 */
	smp_mb__after_atomic();

	/*
	 * If a pending vIPI was unmasked, उठाओ a HW IPI to ourselves.
	 * No barriers needed here since this is a self-IPI.
	 */
	अगर (atomic_पढ़ो(this_cpu_ptr(&aic_vipi_flag)) & irq_bit)
		aic_ic_ग_लिखो(ic, AIC_IPI_SEND, AIC_IPI_SEND_CPU(smp_processor_id()));
पूर्ण

अटल व्योम aic_ipi_send_mask(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask)
अणु
	काष्ठा aic_irq_chip *ic = irq_data_get_irq_chip_data(d);
	u32 irq_bit = BIT(irqd_to_hwirq(d));
	u32 send = 0;
	पूर्णांक cpu;
	अचिन्हित दीर्घ pending;

	क्रम_each_cpu(cpu, mask) अणु
		/*
		 * This sequence is the mirror of the one in aic_ipi_unmask();
		 * see the comment there. Additionally, release semantics
		 * ensure that the vIPI flag set is ordered after any shared
		 * memory accesses that precede it. This thereक्रमe also pairs
		 * with the atomic_fetch_andnot in aic_handle_ipi().
		 */
		pending = atomic_fetch_or_release(irq_bit, per_cpu_ptr(&aic_vipi_flag, cpu));

		/*
		 * The atomic_fetch_or_release() above must complete beक्रमe the
		 * atomic_पढ़ो() below to aव्योम racing aic_ipi_unmask().
		 */
		smp_mb__after_atomic();

		अगर (!(pending & irq_bit) &&
		    (atomic_पढ़ो(per_cpu_ptr(&aic_vipi_enable, cpu)) & irq_bit))
			send |= AIC_IPI_SEND_CPU(cpu);
	पूर्ण

	/*
	 * The flag ग_लिखोs must complete beक्रमe the physical IPI is issued
	 * to another CPU. This is implied by the control dependency on
	 * the result of atomic_पढ़ो_acquire() above, which is itself
	 * alपढ़ोy ordered after the vIPI flag ग_लिखो.
	 */
	अगर (send)
		aic_ic_ग_लिखो(ic, AIC_IPI_SEND, send);
पूर्ण

अटल काष्ठा irq_chip ipi_chip = अणु
	.name = "AIC-IPI",
	.irq_mask = aic_ipi_mask,
	.irq_unmask = aic_ipi_unmask,
	.ipi_send_mask = aic_ipi_send_mask,
पूर्ण;

/*
 * IPI IRQ करोमुख्य
 */

अटल व्योम aic_handle_ipi(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ enabled, firing;

	/*
	 * Ack the IPI. We need to order this after the AIC event पढ़ो, but
	 * that is enक्रमced by normal MMIO ordering guarantees.
	 */
	aic_ic_ग_लिखो(aic_irqc, AIC_IPI_ACK, AIC_IPI_OTHER);

	/*
	 * The mask पढ़ो करोes not need to be ordered. Only we can change
	 * our own mask anyway, so no races are possible here, as दीर्घ as
	 * we are properly in the पूर्णांकerrupt handler (which is covered by
	 * the barrier that is part of the top-level AIC handler's पढ़ोl()).
	 */
	enabled = atomic_पढ़ो(this_cpu_ptr(&aic_vipi_enable));

	/*
	 * Clear the IPIs we are about to handle. This pairs with the
	 * atomic_fetch_or_release() in aic_ipi_send_mask(), and needs to be
	 * ordered after the aic_ic_ग_लिखो() above (to aव्योम dropping vIPIs) and
	 * beक्रमe IPI handling code (to aव्योम races handling vIPIs beक्रमe they
	 * are संकेतed). The क्रमmer is taken care of by the release semantics
	 * of the ग_लिखो portion, जबतक the latter is taken care of by the
	 * acquire semantics of the पढ़ो portion.
	 */
	firing = atomic_fetch_andnot(enabled, this_cpu_ptr(&aic_vipi_flag)) & enabled;

	क्रम_each_set_bit(i, &firing, AIC_NR_SWIPI)
		handle_करोमुख्य_irq(aic_irqc->ipi_करोमुख्य, i, regs);

	/*
	 * No ordering needed here; at worst this just changes the timing of
	 * when the next IPI will be delivered.
	 */
	aic_ic_ग_लिखो(aic_irqc, AIC_IPI_MASK_CLR, AIC_IPI_OTHER);
पूर्ण

अटल पूर्णांक aic_ipi_alloc(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			 अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		irq_set_percpu_devid(virq + i);
		irq_करोमुख्य_set_info(d, virq + i, i, &ipi_chip, d->host_data,
				    handle_percpu_devid_irq, शून्य, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम aic_ipi_मुक्त(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	/* Not मुक्तing IPIs */
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops aic_ipi_करोमुख्य_ops = अणु
	.alloc = aic_ipi_alloc,
	.मुक्त = aic_ipi_मुक्त,
पूर्ण;

अटल पूर्णांक aic_init_smp(काष्ठा aic_irq_chip *irqc, काष्ठा device_node *node)
अणु
	काष्ठा irq_करोमुख्य *ipi_करोमुख्य;
	पूर्णांक base_ipi;

	ipi_करोमुख्य = irq_करोमुख्य_create_linear(irqc->hw_करोमुख्य->fwnode, AIC_NR_SWIPI,
					      &aic_ipi_करोमुख्य_ops, irqc);
	अगर (WARN_ON(!ipi_करोमुख्य))
		वापस -ENODEV;

	ipi_करोमुख्य->flags |= IRQ_DOMAIN_FLAG_IPI_SINGLE;
	irq_करोमुख्य_update_bus_token(ipi_करोमुख्य, DOMAIN_BUS_IPI);

	base_ipi = __irq_करोमुख्य_alloc_irqs(ipi_करोमुख्य, -1, AIC_NR_SWIPI,
					   NUMA_NO_NODE, शून्य, false, शून्य);

	अगर (WARN_ON(!base_ipi)) अणु
		irq_करोमुख्य_हटाओ(ipi_करोमुख्य);
		वापस -ENODEV;
	पूर्ण

	set_smp_ipi_range(base_ipi, AIC_NR_SWIPI);

	irqc->ipi_करोमुख्य = ipi_करोमुख्य;

	वापस 0;
पूर्ण

अटल पूर्णांक aic_init_cpu(अचिन्हित पूर्णांक cpu)
अणु
	/* Mask all hard-wired per-CPU IRQ/FIQ sources */

	/* Pending Fast IPI FIQs */
	ग_लिखो_sysreg_s(IPI_SR_PENDING, SYS_IMP_APL_IPI_SR_EL1);

	/* Timer FIQs */
	sysreg_clear_set(cntp_ctl_el0, 0, ARCH_TIMER_CTRL_IT_MASK);
	sysreg_clear_set(cntv_ctl_el0, 0, ARCH_TIMER_CTRL_IT_MASK);

	/* EL2-only (VHE mode) IRQ sources */
	अगर (is_kernel_in_hyp_mode()) अणु
		/* Guest समयrs */
		sysreg_clear_set_s(SYS_IMP_APL_VM_TMR_FIQ_ENA_EL2,
				   VM_TMR_FIQ_ENABLE_V | VM_TMR_FIQ_ENABLE_P, 0);

		/* vGIC मुख्यtenance IRQ */
		sysreg_clear_set_s(SYS_ICH_HCR_EL2, ICH_HCR_EN, 0);
	पूर्ण

	/* PMC FIQ */
	sysreg_clear_set_s(SYS_IMP_APL_PMCR0_EL1, PMCR0_IMODE | PMCR0_IACT,
			   FIELD_PREP(PMCR0_IMODE, PMCR0_IMODE_OFF));

	/* Uncore PMC FIQ */
	sysreg_clear_set_s(SYS_IMP_APL_UPMCR0_EL1, UPMCR0_IMODE,
			   FIELD_PREP(UPMCR0_IMODE, UPMCR0_IMODE_OFF));

	/* Commit all of the above */
	isb();

	/*
	 * Make sure the kernel's idea of logical CPU order is the same as AIC's
	 * If we ever end up with a mismatch here, we will have to पूर्णांकroduce
	 * a mapping table similar to what other irqchip drivers करो.
	 */
	WARN_ON(aic_ic_पढ़ो(aic_irqc, AIC_WHOAMI) != smp_processor_id());

	/*
	 * Always keep IPIs unmasked at the hardware level (except स्वतः-masking
	 * by AIC during processing). We manage masks at the vIPI level.
	 */
	aic_ic_ग_लिखो(aic_irqc, AIC_IPI_ACK, AIC_IPI_SELF | AIC_IPI_OTHER);
	aic_ic_ग_लिखो(aic_irqc, AIC_IPI_MASK_SET, AIC_IPI_SELF);
	aic_ic_ग_लिखो(aic_irqc, AIC_IPI_MASK_CLR, AIC_IPI_OTHER);

	/* Initialize the local mask state */
	__this_cpu_ग_लिखो(aic_fiq_unmasked, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __init aic_of_ic_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	पूर्णांक i;
	व्योम __iomem *regs;
	u32 info;
	काष्ठा aic_irq_chip *irqc;

	regs = of_iomap(node, 0);
	अगर (WARN_ON(!regs))
		वापस -EIO;

	irqc = kzalloc(माप(*irqc), GFP_KERNEL);
	अगर (!irqc)
		वापस -ENOMEM;

	aic_irqc = irqc;
	irqc->base = regs;

	info = aic_ic_पढ़ो(irqc, AIC_INFO);
	irqc->nr_hw = FIELD_GET(AIC_INFO_NR_HW, info);

	irqc->hw_करोमुख्य = irq_करोमुख्य_create_linear(of_node_to_fwnode(node),
						   irqc->nr_hw + AIC_NR_FIQ,
						   &aic_irq_करोमुख्य_ops, irqc);
	अगर (WARN_ON(!irqc->hw_करोमुख्य)) अणु
		iounmap(irqc->base);
		kमुक्त(irqc);
		वापस -ENODEV;
	पूर्ण

	irq_करोमुख्य_update_bus_token(irqc->hw_करोमुख्य, DOMAIN_BUS_WIRED);

	अगर (aic_init_smp(irqc, node)) अणु
		irq_करोमुख्य_हटाओ(irqc->hw_करोमुख्य);
		iounmap(irqc->base);
		kमुक्त(irqc);
		वापस -ENODEV;
	पूर्ण

	set_handle_irq(aic_handle_irq);
	set_handle_fiq(aic_handle_fiq);

	क्रम (i = 0; i < BITS_TO_U32(irqc->nr_hw); i++)
		aic_ic_ग_लिखो(irqc, AIC_MASK_SET + i * 4, U32_MAX);
	क्रम (i = 0; i < BITS_TO_U32(irqc->nr_hw); i++)
		aic_ic_ग_लिखो(irqc, AIC_SW_CLR + i * 4, U32_MAX);
	क्रम (i = 0; i < irqc->nr_hw; i++)
		aic_ic_ग_लिखो(irqc, AIC_TARGET_CPU + i * 4, 1);

	अगर (!is_kernel_in_hyp_mode())
		pr_info("Kernel running in EL1, mapping interrupts");

	cpuhp_setup_state(CPUHP_AP_IRQ_APPLE_AIC_STARTING,
			  "irqchip/apple-aic/ipi:starting",
			  aic_init_cpu, शून्य);

	pr_info("Initialized with %d IRQs, %d FIQs, %d vIPIs\n",
		irqc->nr_hw, AIC_NR_FIQ, AIC_NR_SWIPI);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(apple_m1_aic, "apple,aic", aic_of_ic_init);
