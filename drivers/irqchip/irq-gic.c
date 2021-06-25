<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 ARM Limited, All Rights Reserved.
 *
 * Interrupt architecture क्रम the GIC:
 *
 * o There is one Interrupt Distributor, which receives पूर्णांकerrupts
 *   from प्रणाली devices and sends them to the Interrupt Controllers.
 *
 * o There is one CPU Interface per CPU, which sends पूर्णांकerrupts sent
 *   by the Distributor, and पूर्णांकerrupts generated locally, to the
 *   associated CPU. The base address of the CPU पूर्णांकerface is usually
 *   aliased so that the same address poपूर्णांकs to dअगरferent chips depending
 *   on the CPU it is accessed from.
 *
 * Note that IRQs 0-31 are special - they are local to each CPU.
 * As such, the enable set/clear, pending set/clear and active bit
 * रेजिस्टरs are banked per-cpu क्रम these sources.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/acpi.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqchip/arm-gic.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/virt.h>

#समावेश "irq-gic-common.h"

#अगर_घोषित CONFIG_ARM64
#समावेश <यंत्र/cpufeature.h>

अटल व्योम gic_check_cpu_features(व्योम)
अणु
	WARN_TAINT_ONCE(this_cpu_has_cap(ARM64_HAS_SYSREG_GIC_CPUIF),
			TAINT_CPU_OUT_OF_SPEC,
			"GICv3 system registers enabled, broken firmware!\n");
पूर्ण
#अन्यथा
#घोषणा gic_check_cpu_features()	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

जोड़ gic_base अणु
	व्योम __iomem *common_base;
	व्योम __percpu * __iomem *percpu_base;
पूर्ण;

काष्ठा gic_chip_data अणु
	काष्ठा irq_chip chip;
	जोड़ gic_base dist_base;
	जोड़ gic_base cpu_base;
	व्योम __iomem *raw_dist_base;
	व्योम __iomem *raw_cpu_base;
	u32 percpu_offset;
#अगर defined(CONFIG_CPU_PM) || defined(CONFIG_ARM_GIC_PM)
	u32 saved_spi_enable[DIV_ROUND_UP(1020, 32)];
	u32 saved_spi_active[DIV_ROUND_UP(1020, 32)];
	u32 saved_spi_conf[DIV_ROUND_UP(1020, 16)];
	u32 saved_spi_target[DIV_ROUND_UP(1020, 4)];
	u32 __percpu *saved_ppi_enable;
	u32 __percpu *saved_ppi_active;
	u32 __percpu *saved_ppi_conf;
#पूर्ण_अगर
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक gic_irqs;
पूर्ण;

#अगर_घोषित CONFIG_BL_SWITCHER

अटल DEFINE_RAW_SPINLOCK(cpu_map_lock);

#घोषणा gic_lock_irqsave(f)		\
	raw_spin_lock_irqsave(&cpu_map_lock, (f))
#घोषणा gic_unlock_irqrestore(f)	\
	raw_spin_unlock_irqrestore(&cpu_map_lock, (f))

#घोषणा gic_lock()			raw_spin_lock(&cpu_map_lock)
#घोषणा gic_unlock()			raw_spin_unlock(&cpu_map_lock)

#अन्यथा

#घोषणा gic_lock_irqsave(f)		करो अणु (व्योम)(f); पूर्ण जबतक(0)
#घोषणा gic_unlock_irqrestore(f)	करो अणु (व्योम)(f); पूर्ण जबतक(0)

#घोषणा gic_lock()			करो अणु पूर्ण जबतक(0)
#घोषणा gic_unlock()			करो अणु पूर्ण जबतक(0)

#पूर्ण_अगर

/*
 * The GIC mapping of CPU पूर्णांकerfaces करोes not necessarily match
 * the logical CPU numbering.  Let's use a mapping as वापसed
 * by the GIC itself.
 */
#घोषणा NR_GIC_CPU_IF 8
अटल u8 gic_cpu_map[NR_GIC_CPU_IF] __पढ़ो_mostly;

अटल DEFINE_STATIC_KEY_TRUE(supports_deactivate_key);

अटल काष्ठा gic_chip_data gic_data[CONFIG_ARM_GIC_MAX_NR] __पढ़ो_mostly;

अटल काष्ठा gic_kvm_info gic_v2_kvm_info;

अटल DEFINE_PER_CPU(u32, sgi_पूर्णांकid);

#अगर_घोषित CONFIG_GIC_NON_BANKED
अटल DEFINE_STATIC_KEY_FALSE(frankengic_key);

अटल व्योम enable_frankengic(व्योम)
अणु
	अटल_branch_enable(&frankengic_key);
पूर्ण

अटल अंतरभूत व्योम __iomem *__get_base(जोड़ gic_base *base)
अणु
	अगर (अटल_branch_unlikely(&frankengic_key))
		वापस raw_cpu_पढ़ो(*base->percpu_base);

	वापस base->common_base;
पूर्ण

#घोषणा gic_data_dist_base(d)	__get_base(&(d)->dist_base)
#घोषणा gic_data_cpu_base(d)	__get_base(&(d)->cpu_base)
#अन्यथा
#घोषणा gic_data_dist_base(d)	((d)->dist_base.common_base)
#घोषणा gic_data_cpu_base(d)	((d)->cpu_base.common_base)
#घोषणा enable_frankengic()	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल अंतरभूत व्योम __iomem *gic_dist_base(काष्ठा irq_data *d)
अणु
	काष्ठा gic_chip_data *gic_data = irq_data_get_irq_chip_data(d);
	वापस gic_data_dist_base(gic_data);
पूर्ण

अटल अंतरभूत व्योम __iomem *gic_cpu_base(काष्ठा irq_data *d)
अणु
	काष्ठा gic_chip_data *gic_data = irq_data_get_irq_chip_data(d);
	वापस gic_data_cpu_base(gic_data);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक gic_irq(काष्ठा irq_data *d)
अणु
	वापस d->hwirq;
पूर्ण

अटल अंतरभूत bool cascading_gic_irq(काष्ठा irq_data *d)
अणु
	व्योम *data = irq_data_get_irq_handler_data(d);

	/*
	 * If handler_data is set, this is a cascading पूर्णांकerrupt, and
	 * it cannot possibly be क्रमwarded.
	 */
	वापस data != शून्य;
पूर्ण

/*
 * Routines to acknowledge, disable and enable पूर्णांकerrupts
 */
अटल व्योम gic_poke_irq(काष्ठा irq_data *d, u32 offset)
अणु
	u32 mask = 1 << (gic_irq(d) % 32);
	ग_लिखोl_relaxed(mask, gic_dist_base(d) + offset + (gic_irq(d) / 32) * 4);
पूर्ण

अटल पूर्णांक gic_peek_irq(काष्ठा irq_data *d, u32 offset)
अणु
	u32 mask = 1 << (gic_irq(d) % 32);
	वापस !!(पढ़ोl_relaxed(gic_dist_base(d) + offset + (gic_irq(d) / 32) * 4) & mask);
पूर्ण

अटल व्योम gic_mask_irq(काष्ठा irq_data *d)
अणु
	gic_poke_irq(d, GIC_DIST_ENABLE_CLEAR);
पूर्ण

अटल व्योम gic_eoimode1_mask_irq(काष्ठा irq_data *d)
अणु
	gic_mask_irq(d);
	/*
	 * When masking a क्रमwarded पूर्णांकerrupt, make sure it is
	 * deactivated as well.
	 *
	 * This ensures that an पूर्णांकerrupt that is getting
	 * disabled/masked will not get "stuck", because there is
	 * noone to deactivate it (guest is being terminated).
	 */
	अगर (irqd_is_क्रमwarded_to_vcpu(d))
		gic_poke_irq(d, GIC_DIST_ACTIVE_CLEAR);
पूर्ण

अटल व्योम gic_unmask_irq(काष्ठा irq_data *d)
अणु
	gic_poke_irq(d, GIC_DIST_ENABLE_SET);
पूर्ण

अटल व्योम gic_eoi_irq(काष्ठा irq_data *d)
अणु
	u32 hwirq = gic_irq(d);

	अगर (hwirq < 16)
		hwirq = this_cpu_पढ़ो(sgi_पूर्णांकid);

	ग_लिखोl_relaxed(hwirq, gic_cpu_base(d) + GIC_CPU_EOI);
पूर्ण

अटल व्योम gic_eoimode1_eoi_irq(काष्ठा irq_data *d)
अणु
	u32 hwirq = gic_irq(d);

	/* Do not deactivate an IRQ क्रमwarded to a vcpu. */
	अगर (irqd_is_क्रमwarded_to_vcpu(d))
		वापस;

	अगर (hwirq < 16)
		hwirq = this_cpu_पढ़ो(sgi_पूर्णांकid);

	ग_लिखोl_relaxed(hwirq, gic_cpu_base(d) + GIC_CPU_DEACTIVATE);
पूर्ण

अटल पूर्णांक gic_irq_set_irqchip_state(काष्ठा irq_data *d,
				     क्रमागत irqchip_irq_state which, bool val)
अणु
	u32 reg;

	चयन (which) अणु
	हाल IRQCHIP_STATE_PENDING:
		reg = val ? GIC_DIST_PENDING_SET : GIC_DIST_PENDING_CLEAR;
		अवरोध;

	हाल IRQCHIP_STATE_ACTIVE:
		reg = val ? GIC_DIST_ACTIVE_SET : GIC_DIST_ACTIVE_CLEAR;
		अवरोध;

	हाल IRQCHIP_STATE_MASKED:
		reg = val ? GIC_DIST_ENABLE_CLEAR : GIC_DIST_ENABLE_SET;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	gic_poke_irq(d, reg);
	वापस 0;
पूर्ण

अटल पूर्णांक gic_irq_get_irqchip_state(काष्ठा irq_data *d,
				      क्रमागत irqchip_irq_state which, bool *val)
अणु
	चयन (which) अणु
	हाल IRQCHIP_STATE_PENDING:
		*val = gic_peek_irq(d, GIC_DIST_PENDING_SET);
		अवरोध;

	हाल IRQCHIP_STATE_ACTIVE:
		*val = gic_peek_irq(d, GIC_DIST_ACTIVE_SET);
		अवरोध;

	हाल IRQCHIP_STATE_MASKED:
		*val = !gic_peek_irq(d, GIC_DIST_ENABLE_SET);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gic_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	व्योम __iomem *base = gic_dist_base(d);
	अचिन्हित पूर्णांक gicirq = gic_irq(d);
	पूर्णांक ret;

	/* Interrupt configuration क्रम SGIs can't be changed */
	अगर (gicirq < 16)
		वापस type != IRQ_TYPE_EDGE_RISING ? -EINVAL : 0;

	/* SPIs have restrictions on the supported types */
	अगर (gicirq >= 32 && type != IRQ_TYPE_LEVEL_HIGH &&
			    type != IRQ_TYPE_EDGE_RISING)
		वापस -EINVAL;

	ret = gic_configure_irq(gicirq, type, base + GIC_DIST_CONFIG, शून्य);
	अगर (ret && gicirq < 32) अणु
		/* Misconfigured PPIs are usually not fatal */
		pr_warn("GIC: PPI%d is secure or misconfigured\n", gicirq - 16);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gic_irq_set_vcpu_affinity(काष्ठा irq_data *d, व्योम *vcpu)
अणु
	/* Only पूर्णांकerrupts on the primary GIC can be क्रमwarded to a vcpu. */
	अगर (cascading_gic_irq(d) || gic_irq(d) < 16)
		वापस -EINVAL;

	अगर (vcpu)
		irqd_set_क्रमwarded_to_vcpu(d);
	अन्यथा
		irqd_clr_क्रमwarded_to_vcpu(d);
	वापस 0;
पूर्ण

अटल पूर्णांक gic_retrigger(काष्ठा irq_data *data)
अणु
	वापस !gic_irq_set_irqchip_state(data, IRQCHIP_STATE_PENDING, true);
पूर्ण

अटल व्योम __exception_irq_entry gic_handle_irq(काष्ठा pt_regs *regs)
अणु
	u32 irqstat, irqnr;
	काष्ठा gic_chip_data *gic = &gic_data[0];
	व्योम __iomem *cpu_base = gic_data_cpu_base(gic);

	करो अणु
		irqstat = पढ़ोl_relaxed(cpu_base + GIC_CPU_INTACK);
		irqnr = irqstat & GICC_IAR_INT_ID_MASK;

		अगर (unlikely(irqnr >= 1020))
			अवरोध;

		अगर (अटल_branch_likely(&supports_deactivate_key))
			ग_लिखोl_relaxed(irqstat, cpu_base + GIC_CPU_EOI);
		isb();

		/*
		 * Ensure any shared data written by the CPU sending the IPI
		 * is पढ़ो after we've पढ़ो the ACK रेजिस्टर on the GIC.
		 *
		 * Pairs with the ग_लिखो barrier in gic_ipi_send_mask
		 */
		अगर (irqnr <= 15) अणु
			smp_rmb();

			/*
			 * The GIC encodes the source CPU in GICC_IAR,
			 * leading to the deactivation to fail अगर not
			 * written back as is to GICC_EOI.  Stash the INTID
			 * away क्रम gic_eoi_irq() to ग_लिखो back.  This only
			 * works because we करोn't nest SGIs...
			 */
			this_cpu_ग_लिखो(sgi_पूर्णांकid, irqstat);
		पूर्ण

		handle_करोमुख्य_irq(gic->करोमुख्य, irqnr, regs);
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम gic_handle_cascade_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा gic_chip_data *chip_data = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq, gic_irq;
	अचिन्हित दीर्घ status;

	chained_irq_enter(chip, desc);

	status = पढ़ोl_relaxed(gic_data_cpu_base(chip_data) + GIC_CPU_INTACK);

	gic_irq = (status & GICC_IAR_INT_ID_MASK);
	अगर (gic_irq == GICC_INT_SPURIOUS)
		जाओ out;

	cascade_irq = irq_find_mapping(chip_data->करोमुख्य, gic_irq);
	अगर (unlikely(gic_irq < 32 || gic_irq > 1020)) अणु
		handle_bad_irq(desc);
	पूर्ण अन्यथा अणु
		isb();
		generic_handle_irq(cascade_irq);
	पूर्ण

 out:
	chained_irq_निकास(chip, desc);
पूर्ण

अटल स्थिर काष्ठा irq_chip gic_chip = अणु
	.irq_mask		= gic_mask_irq,
	.irq_unmask		= gic_unmask_irq,
	.irq_eoi		= gic_eoi_irq,
	.irq_set_type		= gic_set_type,
	.irq_retrigger          = gic_retrigger,
	.irq_get_irqchip_state	= gic_irq_get_irqchip_state,
	.irq_set_irqchip_state	= gic_irq_set_irqchip_state,
	.flags			= IRQCHIP_SET_TYPE_MASKED |
				  IRQCHIP_SKIP_SET_WAKE |
				  IRQCHIP_MASK_ON_SUSPEND,
पूर्ण;

व्योम __init gic_cascade_irq(अचिन्हित पूर्णांक gic_nr, अचिन्हित पूर्णांक irq)
अणु
	BUG_ON(gic_nr >= CONFIG_ARM_GIC_MAX_NR);
	irq_set_chained_handler_and_data(irq, gic_handle_cascade_irq,
					 &gic_data[gic_nr]);
पूर्ण

अटल u8 gic_get_cpumask(काष्ठा gic_chip_data *gic)
अणु
	व्योम __iomem *base = gic_data_dist_base(gic);
	u32 mask, i;

	क्रम (i = mask = 0; i < 32; i += 4) अणु
		mask = पढ़ोl_relaxed(base + GIC_DIST_TARGET + i);
		mask |= mask >> 16;
		mask |= mask >> 8;
		अगर (mask)
			अवरोध;
	पूर्ण

	अगर (!mask && num_possible_cpus() > 1)
		pr_crit("GIC CPU mask not found - kernel will fail to boot.\n");

	वापस mask;
पूर्ण

अटल bool gic_check_gicv2(व्योम __iomem *base)
अणु
	u32 val = पढ़ोl_relaxed(base + GIC_CPU_IDENT);
	वापस (val & 0xff0fff) == 0x02043B;
पूर्ण

अटल व्योम gic_cpu_अगर_up(काष्ठा gic_chip_data *gic)
अणु
	व्योम __iomem *cpu_base = gic_data_cpu_base(gic);
	u32 bypass = 0;
	u32 mode = 0;
	पूर्णांक i;

	अगर (gic == &gic_data[0] && अटल_branch_likely(&supports_deactivate_key))
		mode = GIC_CPU_CTRL_EOImodeNS;

	अगर (gic_check_gicv2(cpu_base))
		क्रम (i = 0; i < 4; i++)
			ग_लिखोl_relaxed(0, cpu_base + GIC_CPU_ACTIVEPRIO + i * 4);

	/*
	* Preserve bypass disable bits to be written back later
	*/
	bypass = पढ़ोl(cpu_base + GIC_CPU_CTRL);
	bypass &= GICC_DIS_BYPASS_MASK;

	ग_लिखोl_relaxed(bypass | mode | GICC_ENABLE, cpu_base + GIC_CPU_CTRL);
पूर्ण


अटल व्योम gic_dist_init(काष्ठा gic_chip_data *gic)
अणु
	अचिन्हित पूर्णांक i;
	u32 cpumask;
	अचिन्हित पूर्णांक gic_irqs = gic->gic_irqs;
	व्योम __iomem *base = gic_data_dist_base(gic);

	ग_लिखोl_relaxed(GICD_DISABLE, base + GIC_DIST_CTRL);

	/*
	 * Set all global पूर्णांकerrupts to this CPU only.
	 */
	cpumask = gic_get_cpumask(gic);
	cpumask |= cpumask << 8;
	cpumask |= cpumask << 16;
	क्रम (i = 32; i < gic_irqs; i += 4)
		ग_लिखोl_relaxed(cpumask, base + GIC_DIST_TARGET + i * 4 / 4);

	gic_dist_config(base, gic_irqs, शून्य);

	ग_लिखोl_relaxed(GICD_ENABLE, base + GIC_DIST_CTRL);
पूर्ण

अटल पूर्णांक gic_cpu_init(काष्ठा gic_chip_data *gic)
अणु
	व्योम __iomem *dist_base = gic_data_dist_base(gic);
	व्योम __iomem *base = gic_data_cpu_base(gic);
	अचिन्हित पूर्णांक cpu_mask, cpu = smp_processor_id();
	पूर्णांक i;

	/*
	 * Setting up the CPU map is only relevant क्रम the primary GIC
	 * because any nested/secondary GICs करो not directly पूर्णांकerface
	 * with the CPU(s).
	 */
	अगर (gic == &gic_data[0]) अणु
		/*
		 * Get what the GIC says our CPU mask is.
		 */
		अगर (WARN_ON(cpu >= NR_GIC_CPU_IF))
			वापस -EINVAL;

		gic_check_cpu_features();
		cpu_mask = gic_get_cpumask(gic);
		gic_cpu_map[cpu] = cpu_mask;

		/*
		 * Clear our mask from the other map entries in हाल they're
		 * still undefined.
		 */
		क्रम (i = 0; i < NR_GIC_CPU_IF; i++)
			अगर (i != cpu)
				gic_cpu_map[i] &= ~cpu_mask;
	पूर्ण

	gic_cpu_config(dist_base, 32, शून्य);

	ग_लिखोl_relaxed(GICC_INT_PRI_THRESHOLD, base + GIC_CPU_PRIMASK);
	gic_cpu_अगर_up(gic);

	वापस 0;
पूर्ण

पूर्णांक gic_cpu_अगर_करोwn(अचिन्हित पूर्णांक gic_nr)
अणु
	व्योम __iomem *cpu_base;
	u32 val = 0;

	अगर (gic_nr >= CONFIG_ARM_GIC_MAX_NR)
		वापस -EINVAL;

	cpu_base = gic_data_cpu_base(&gic_data[gic_nr]);
	val = पढ़ोl(cpu_base + GIC_CPU_CTRL);
	val &= ~GICC_ENABLE;
	ग_लिखोl_relaxed(val, cpu_base + GIC_CPU_CTRL);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_CPU_PM) || defined(CONFIG_ARM_GIC_PM)
/*
 * Saves the GIC distributor रेजिस्टरs during suspend or idle.  Must be called
 * with पूर्णांकerrupts disabled but beक्रमe घातering करोwn the GIC.  After calling
 * this function, no पूर्णांकerrupts will be delivered by the GIC, and another
 * platक्रमm-specअगरic wakeup source must be enabled.
 */
व्योम gic_dist_save(काष्ठा gic_chip_data *gic)
अणु
	अचिन्हित पूर्णांक gic_irqs;
	व्योम __iomem *dist_base;
	पूर्णांक i;

	अगर (WARN_ON(!gic))
		वापस;

	gic_irqs = gic->gic_irqs;
	dist_base = gic_data_dist_base(gic);

	अगर (!dist_base)
		वापस;

	क्रम (i = 0; i < DIV_ROUND_UP(gic_irqs, 16); i++)
		gic->saved_spi_conf[i] =
			पढ़ोl_relaxed(dist_base + GIC_DIST_CONFIG + i * 4);

	क्रम (i = 0; i < DIV_ROUND_UP(gic_irqs, 4); i++)
		gic->saved_spi_target[i] =
			पढ़ोl_relaxed(dist_base + GIC_DIST_TARGET + i * 4);

	क्रम (i = 0; i < DIV_ROUND_UP(gic_irqs, 32); i++)
		gic->saved_spi_enable[i] =
			पढ़ोl_relaxed(dist_base + GIC_DIST_ENABLE_SET + i * 4);

	क्रम (i = 0; i < DIV_ROUND_UP(gic_irqs, 32); i++)
		gic->saved_spi_active[i] =
			पढ़ोl_relaxed(dist_base + GIC_DIST_ACTIVE_SET + i * 4);
पूर्ण

/*
 * Restores the GIC distributor रेजिस्टरs during resume or when coming out of
 * idle.  Must be called beक्रमe enabling पूर्णांकerrupts.  If a level पूर्णांकerrupt
 * that occurred जबतक the GIC was suspended is still present, it will be
 * handled normally, but any edge पूर्णांकerrupts that occurred will not be seen by
 * the GIC and need to be handled by the platक्रमm-specअगरic wakeup source.
 */
व्योम gic_dist_restore(काष्ठा gic_chip_data *gic)
अणु
	अचिन्हित पूर्णांक gic_irqs;
	अचिन्हित पूर्णांक i;
	व्योम __iomem *dist_base;

	अगर (WARN_ON(!gic))
		वापस;

	gic_irqs = gic->gic_irqs;
	dist_base = gic_data_dist_base(gic);

	अगर (!dist_base)
		वापस;

	ग_लिखोl_relaxed(GICD_DISABLE, dist_base + GIC_DIST_CTRL);

	क्रम (i = 0; i < DIV_ROUND_UP(gic_irqs, 16); i++)
		ग_लिखोl_relaxed(gic->saved_spi_conf[i],
			dist_base + GIC_DIST_CONFIG + i * 4);

	क्रम (i = 0; i < DIV_ROUND_UP(gic_irqs, 4); i++)
		ग_लिखोl_relaxed(GICD_INT_DEF_PRI_X4,
			dist_base + GIC_DIST_PRI + i * 4);

	क्रम (i = 0; i < DIV_ROUND_UP(gic_irqs, 4); i++)
		ग_लिखोl_relaxed(gic->saved_spi_target[i],
			dist_base + GIC_DIST_TARGET + i * 4);

	क्रम (i = 0; i < DIV_ROUND_UP(gic_irqs, 32); i++) अणु
		ग_लिखोl_relaxed(GICD_INT_EN_CLR_X32,
			dist_base + GIC_DIST_ENABLE_CLEAR + i * 4);
		ग_लिखोl_relaxed(gic->saved_spi_enable[i],
			dist_base + GIC_DIST_ENABLE_SET + i * 4);
	पूर्ण

	क्रम (i = 0; i < DIV_ROUND_UP(gic_irqs, 32); i++) अणु
		ग_लिखोl_relaxed(GICD_INT_EN_CLR_X32,
			dist_base + GIC_DIST_ACTIVE_CLEAR + i * 4);
		ग_लिखोl_relaxed(gic->saved_spi_active[i],
			dist_base + GIC_DIST_ACTIVE_SET + i * 4);
	पूर्ण

	ग_लिखोl_relaxed(GICD_ENABLE, dist_base + GIC_DIST_CTRL);
पूर्ण

व्योम gic_cpu_save(काष्ठा gic_chip_data *gic)
अणु
	पूर्णांक i;
	u32 *ptr;
	व्योम __iomem *dist_base;
	व्योम __iomem *cpu_base;

	अगर (WARN_ON(!gic))
		वापस;

	dist_base = gic_data_dist_base(gic);
	cpu_base = gic_data_cpu_base(gic);

	अगर (!dist_base || !cpu_base)
		वापस;

	ptr = raw_cpu_ptr(gic->saved_ppi_enable);
	क्रम (i = 0; i < DIV_ROUND_UP(32, 32); i++)
		ptr[i] = पढ़ोl_relaxed(dist_base + GIC_DIST_ENABLE_SET + i * 4);

	ptr = raw_cpu_ptr(gic->saved_ppi_active);
	क्रम (i = 0; i < DIV_ROUND_UP(32, 32); i++)
		ptr[i] = पढ़ोl_relaxed(dist_base + GIC_DIST_ACTIVE_SET + i * 4);

	ptr = raw_cpu_ptr(gic->saved_ppi_conf);
	क्रम (i = 0; i < DIV_ROUND_UP(32, 16); i++)
		ptr[i] = पढ़ोl_relaxed(dist_base + GIC_DIST_CONFIG + i * 4);

पूर्ण

व्योम gic_cpu_restore(काष्ठा gic_chip_data *gic)
अणु
	पूर्णांक i;
	u32 *ptr;
	व्योम __iomem *dist_base;
	व्योम __iomem *cpu_base;

	अगर (WARN_ON(!gic))
		वापस;

	dist_base = gic_data_dist_base(gic);
	cpu_base = gic_data_cpu_base(gic);

	अगर (!dist_base || !cpu_base)
		वापस;

	ptr = raw_cpu_ptr(gic->saved_ppi_enable);
	क्रम (i = 0; i < DIV_ROUND_UP(32, 32); i++) अणु
		ग_लिखोl_relaxed(GICD_INT_EN_CLR_X32,
			       dist_base + GIC_DIST_ENABLE_CLEAR + i * 4);
		ग_लिखोl_relaxed(ptr[i], dist_base + GIC_DIST_ENABLE_SET + i * 4);
	पूर्ण

	ptr = raw_cpu_ptr(gic->saved_ppi_active);
	क्रम (i = 0; i < DIV_ROUND_UP(32, 32); i++) अणु
		ग_लिखोl_relaxed(GICD_INT_EN_CLR_X32,
			       dist_base + GIC_DIST_ACTIVE_CLEAR + i * 4);
		ग_लिखोl_relaxed(ptr[i], dist_base + GIC_DIST_ACTIVE_SET + i * 4);
	पूर्ण

	ptr = raw_cpu_ptr(gic->saved_ppi_conf);
	क्रम (i = 0; i < DIV_ROUND_UP(32, 16); i++)
		ग_लिखोl_relaxed(ptr[i], dist_base + GIC_DIST_CONFIG + i * 4);

	क्रम (i = 0; i < DIV_ROUND_UP(32, 4); i++)
		ग_लिखोl_relaxed(GICD_INT_DEF_PRI_X4,
					dist_base + GIC_DIST_PRI + i * 4);

	ग_लिखोl_relaxed(GICC_INT_PRI_THRESHOLD, cpu_base + GIC_CPU_PRIMASK);
	gic_cpu_अगर_up(gic);
पूर्ण

अटल पूर्णांक gic_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd,	व्योम *v)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CONFIG_ARM_GIC_MAX_NR; i++) अणु
		चयन (cmd) अणु
		हाल CPU_PM_ENTER:
			gic_cpu_save(&gic_data[i]);
			अवरोध;
		हाल CPU_PM_ENTER_FAILED:
		हाल CPU_PM_EXIT:
			gic_cpu_restore(&gic_data[i]);
			अवरोध;
		हाल CPU_CLUSTER_PM_ENTER:
			gic_dist_save(&gic_data[i]);
			अवरोध;
		हाल CPU_CLUSTER_PM_ENTER_FAILED:
		हाल CPU_CLUSTER_PM_EXIT:
			gic_dist_restore(&gic_data[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block gic_notअगरier_block = अणु
	.notअगरier_call = gic_notअगरier,
पूर्ण;

अटल पूर्णांक gic_pm_init(काष्ठा gic_chip_data *gic)
अणु
	gic->saved_ppi_enable = __alloc_percpu(DIV_ROUND_UP(32, 32) * 4,
		माप(u32));
	अगर (WARN_ON(!gic->saved_ppi_enable))
		वापस -ENOMEM;

	gic->saved_ppi_active = __alloc_percpu(DIV_ROUND_UP(32, 32) * 4,
		माप(u32));
	अगर (WARN_ON(!gic->saved_ppi_active))
		जाओ मुक्त_ppi_enable;

	gic->saved_ppi_conf = __alloc_percpu(DIV_ROUND_UP(32, 16) * 4,
		माप(u32));
	अगर (WARN_ON(!gic->saved_ppi_conf))
		जाओ मुक्त_ppi_active;

	अगर (gic == &gic_data[0])
		cpu_pm_रेजिस्टर_notअगरier(&gic_notअगरier_block);

	वापस 0;

मुक्त_ppi_active:
	मुक्त_percpu(gic->saved_ppi_active);
मुक्त_ppi_enable:
	मुक्त_percpu(gic->saved_ppi_enable);

	वापस -ENOMEM;
पूर्ण
#अन्यथा
अटल पूर्णांक gic_pm_init(काष्ठा gic_chip_data *gic)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक gic_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask_val,
			    bool क्रमce)
अणु
	व्योम __iomem *reg = gic_dist_base(d) + GIC_DIST_TARGET + gic_irq(d);
	अचिन्हित पूर्णांक cpu;

	अगर (!क्रमce)
		cpu = cpumask_any_and(mask_val, cpu_online_mask);
	अन्यथा
		cpu = cpumask_first(mask_val);

	अगर (cpu >= NR_GIC_CPU_IF || cpu >= nr_cpu_ids)
		वापस -EINVAL;

	ग_लिखोb_relaxed(gic_cpu_map[cpu], reg);
	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	वापस IRQ_SET_MASK_OK_DONE;
पूर्ण

अटल व्योम gic_ipi_send_mask(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags, map = 0;

	अगर (unlikely(nr_cpu_ids == 1)) अणु
		/* Only one CPU? let's करो a self-IPI... */
		ग_लिखोl_relaxed(2 << 24 | d->hwirq,
			       gic_data_dist_base(&gic_data[0]) + GIC_DIST_SOFTINT);
		वापस;
	पूर्ण

	gic_lock_irqsave(flags);

	/* Convert our logical CPU mask पूर्णांकo a physical one. */
	क्रम_each_cpu(cpu, mask)
		map |= gic_cpu_map[cpu];

	/*
	 * Ensure that stores to Normal memory are visible to the
	 * other CPUs beक्रमe they observe us issuing the IPI.
	 */
	dmb(ishst);

	/* this always happens on GIC0 */
	ग_लिखोl_relaxed(map << 16 | d->hwirq, gic_data_dist_base(&gic_data[0]) + GIC_DIST_SOFTINT);

	gic_unlock_irqrestore(flags);
पूर्ण

अटल पूर्णांक gic_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	gic_cpu_init(&gic_data[0]);
	वापस 0;
पूर्ण

अटल __init व्योम gic_smp_init(व्योम)
अणु
	काष्ठा irq_fwspec sgi_fwspec = अणु
		.fwnode		= gic_data[0].करोमुख्य->fwnode,
		.param_count	= 1,
	पूर्ण;
	पूर्णांक base_sgi;

	cpuhp_setup_state_nocalls(CPUHP_AP_IRQ_GIC_STARTING,
				  "irqchip/arm/gic:starting",
				  gic_starting_cpu, शून्य);

	base_sgi = __irq_करोमुख्य_alloc_irqs(gic_data[0].करोमुख्य, -1, 8,
					   NUMA_NO_NODE, &sgi_fwspec,
					   false, शून्य);
	अगर (WARN_ON(base_sgi <= 0))
		वापस;

	set_smp_ipi_range(base_sgi, 8);
पूर्ण
#अन्यथा
#घोषणा gic_smp_init()		करो अणु पूर्ण जबतक(0)
#घोषणा gic_set_affinity	शून्य
#घोषणा gic_ipi_send_mask	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_BL_SWITCHER
/*
 * gic_send_sgi - send a SGI directly to given CPU पूर्णांकerface number
 *
 * cpu_id: the ID क्रम the destination CPU पूर्णांकerface
 * irq: the IPI number to send a SGI क्रम
 */
व्योम gic_send_sgi(अचिन्हित पूर्णांक cpu_id, अचिन्हित पूर्णांक irq)
अणु
	BUG_ON(cpu_id >= NR_GIC_CPU_IF);
	cpu_id = 1 << cpu_id;
	/* this always happens on GIC0 */
	ग_लिखोl_relaxed((cpu_id << 16) | irq, gic_data_dist_base(&gic_data[0]) + GIC_DIST_SOFTINT);
पूर्ण

/*
 * gic_get_cpu_id - get the CPU पूर्णांकerface ID क्रम the specअगरied CPU
 *
 * @cpu: the logical CPU number to get the GIC ID क्रम.
 *
 * Return the CPU पूर्णांकerface ID क्रम the given logical CPU number,
 * or -1 अगर the CPU number is too large or the पूर्णांकerface ID is
 * unknown (more than one bit set).
 */
पूर्णांक gic_get_cpu_id(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक cpu_bit;

	अगर (cpu >= NR_GIC_CPU_IF)
		वापस -1;
	cpu_bit = gic_cpu_map[cpu];
	अगर (cpu_bit & (cpu_bit - 1))
		वापस -1;
	वापस __ffs(cpu_bit);
पूर्ण

/*
 * gic_migrate_target - migrate IRQs to another CPU पूर्णांकerface
 *
 * @new_cpu_id: the CPU target ID to migrate IRQs to
 *
 * Migrate all peripheral पूर्णांकerrupts with a target matching the current CPU
 * to the पूर्णांकerface corresponding to @new_cpu_id.  The CPU पूर्णांकerface mapping
 * is also updated.  Tarमाला_लो to other CPU पूर्णांकerfaces are unchanged.
 * This must be called with IRQs locally disabled.
 */
व्योम gic_migrate_target(अचिन्हित पूर्णांक new_cpu_id)
अणु
	अचिन्हित पूर्णांक cur_cpu_id, gic_irqs, gic_nr = 0;
	व्योम __iomem *dist_base;
	पूर्णांक i, ror_val, cpu = smp_processor_id();
	u32 val, cur_target_mask, active_mask;

	BUG_ON(gic_nr >= CONFIG_ARM_GIC_MAX_NR);

	dist_base = gic_data_dist_base(&gic_data[gic_nr]);
	अगर (!dist_base)
		वापस;
	gic_irqs = gic_data[gic_nr].gic_irqs;

	cur_cpu_id = __ffs(gic_cpu_map[cpu]);
	cur_target_mask = 0x01010101 << cur_cpu_id;
	ror_val = (cur_cpu_id - new_cpu_id) & 31;

	gic_lock();

	/* Update the target पूर्णांकerface क्रम this logical CPU */
	gic_cpu_map[cpu] = 1 << new_cpu_id;

	/*
	 * Find all the peripheral पूर्णांकerrupts targeting the current
	 * CPU पूर्णांकerface and migrate them to the new CPU पूर्णांकerface.
	 * We skip DIST_TARGET 0 to 7 as they are पढ़ो-only.
	 */
	क्रम (i = 8; i < DIV_ROUND_UP(gic_irqs, 4); i++) अणु
		val = पढ़ोl_relaxed(dist_base + GIC_DIST_TARGET + i * 4);
		active_mask = val & cur_target_mask;
		अगर (active_mask) अणु
			val &= ~active_mask;
			val |= ror32(active_mask, ror_val);
			ग_लिखोl_relaxed(val, dist_base + GIC_DIST_TARGET + i*4);
		पूर्ण
	पूर्ण

	gic_unlock();

	/*
	 * Now let's migrate and clear any potential SGIs that might be
	 * pending क्रम us (cur_cpu_id).  Since GIC_DIST_SGI_PENDING_SET
	 * is a banked रेजिस्टर, we can only क्रमward the SGI using
	 * GIC_DIST_SOFTINT.  The original SGI source is lost but Linux
	 * करोesn't use that inक्रमmation anyway.
	 *
	 * For the same reason we करो not adjust SGI source inक्रमmation
	 * क्रम previously sent SGIs by us to other CPUs either.
	 */
	क्रम (i = 0; i < 16; i += 4) अणु
		पूर्णांक j;
		val = पढ़ोl_relaxed(dist_base + GIC_DIST_SGI_PENDING_SET + i);
		अगर (!val)
			जारी;
		ग_लिखोl_relaxed(val, dist_base + GIC_DIST_SGI_PENDING_CLEAR + i);
		क्रम (j = i; j < i + 4; j++) अणु
			अगर (val & 0xff)
				ग_लिखोl_relaxed((1 << (new_cpu_id + 16)) | j,
						dist_base + GIC_DIST_SOFTINT);
			val >>= 8;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * gic_get_sgir_physaddr - get the physical address क्रम the SGI रेजिस्टर
 *
 * Return the physical address of the SGI रेजिस्टर to be used
 * by some early assembly code when the kernel is not yet available.
 */
अटल अचिन्हित दीर्घ gic_dist_physaddr;

अचिन्हित दीर्घ gic_get_sgir_physaddr(व्योम)
अणु
	अगर (!gic_dist_physaddr)
		वापस 0;
	वापस gic_dist_physaddr + GIC_DIST_SOFTINT;
पूर्ण

अटल व्योम __init gic_init_physaddr(काष्ठा device_node *node)
अणु
	काष्ठा resource res;
	अगर (of_address_to_resource(node, 0, &res) == 0) अणु
		gic_dist_physaddr = res.start;
		pr_info("GIC physical location is %#lx\n", gic_dist_physaddr);
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा gic_init_physaddr(node)  करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक gic_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hw)
अणु
	काष्ठा gic_chip_data *gic = d->host_data;
	काष्ठा irq_data *irqd = irq_desc_get_irq_data(irq_to_desc(irq));

	चयन (hw) अणु
	हाल 0 ... 31:
		irq_set_percpu_devid(irq);
		irq_करोमुख्य_set_info(d, irq, hw, &gic->chip, d->host_data,
				    handle_percpu_devid_irq, शून्य, शून्य);
		अवरोध;
	शेष:
		irq_करोमुख्य_set_info(d, irq, hw, &gic->chip, d->host_data,
				    handle_fasteoi_irq, शून्य, शून्य);
		irq_set_probe(irq);
		irqd_set_single_target(irqd);
		अवरोध;
	पूर्ण

	/* Prevents SW retriggers which mess up the ACK/EOI ordering */
	irqd_set_handle_enक्रमce_irqctx(irqd);
	वापस 0;
पूर्ण

अटल व्योम gic_irq_करोमुख्य_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
पूर्ण

अटल पूर्णांक gic_irq_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				    काष्ठा irq_fwspec *fwspec,
				    अचिन्हित दीर्घ *hwirq,
				    अचिन्हित पूर्णांक *type)
अणु
	अगर (fwspec->param_count == 1 && fwspec->param[0] < 16) अणु
		*hwirq = fwspec->param[0];
		*type = IRQ_TYPE_EDGE_RISING;
		वापस 0;
	पूर्ण

	अगर (is_of_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count < 3)
			वापस -EINVAL;

		चयन (fwspec->param[0]) अणु
		हाल 0:			/* SPI */
			*hwirq = fwspec->param[1] + 32;
			अवरोध;
		हाल 1:			/* PPI */
			*hwirq = fwspec->param[1] + 16;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;

		/* Make it clear that broken DTs are... broken */
		WARN_ON(*type == IRQ_TYPE_NONE);
		वापस 0;
	पूर्ण

	अगर (is_fwnode_irqchip(fwspec->fwnode)) अणु
		अगर(fwspec->param_count != 2)
			वापस -EINVAL;

		*hwirq = fwspec->param[0];
		*type = fwspec->param[1];

		WARN_ON(*type == IRQ_TYPE_NONE);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gic_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	पूर्णांक i, ret;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type = IRQ_TYPE_NONE;
	काष्ठा irq_fwspec *fwspec = arg;

	ret = gic_irq_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++) अणु
		ret = gic_irq_करोमुख्य_map(करोमुख्य, virq + i, hwirq + i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops gic_irq_करोमुख्य_hierarchy_ops = अणु
	.translate = gic_irq_करोमुख्य_translate,
	.alloc = gic_irq_करोमुख्य_alloc,
	.मुक्त = irq_करोमुख्य_मुक्त_irqs_top,
पूर्ण;

अटल स्थिर काष्ठा irq_करोमुख्य_ops gic_irq_करोमुख्य_ops = अणु
	.map = gic_irq_करोमुख्य_map,
	.unmap = gic_irq_करोमुख्य_unmap,
पूर्ण;

अटल व्योम gic_init_chip(काष्ठा gic_chip_data *gic, काष्ठा device *dev,
			  स्थिर अक्षर *name, bool use_eoimode1)
अणु
	/* Initialize irq_chip */
	gic->chip = gic_chip;
	gic->chip.name = name;
	gic->chip.parent_device = dev;

	अगर (use_eoimode1) अणु
		gic->chip.irq_mask = gic_eoimode1_mask_irq;
		gic->chip.irq_eoi = gic_eoimode1_eoi_irq;
		gic->chip.irq_set_vcpu_affinity = gic_irq_set_vcpu_affinity;
	पूर्ण

	अगर (gic == &gic_data[0]) अणु
		gic->chip.irq_set_affinity = gic_set_affinity;
		gic->chip.ipi_send_mask = gic_ipi_send_mask;
	पूर्ण
पूर्ण

अटल पूर्णांक gic_init_bases(काष्ठा gic_chip_data *gic,
			  काष्ठा fwnode_handle *handle)
अणु
	पूर्णांक gic_irqs, ret;

	अगर (IS_ENABLED(CONFIG_GIC_NON_BANKED) && gic->percpu_offset) अणु
		/* Frankein-GIC without banked रेजिस्टरs... */
		अचिन्हित पूर्णांक cpu;

		gic->dist_base.percpu_base = alloc_percpu(व्योम __iomem *);
		gic->cpu_base.percpu_base = alloc_percpu(व्योम __iomem *);
		अगर (WARN_ON(!gic->dist_base.percpu_base ||
			    !gic->cpu_base.percpu_base)) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण

		क्रम_each_possible_cpu(cpu) अणु
			u32 mpidr = cpu_logical_map(cpu);
			u32 core_id = MPIDR_AFFINITY_LEVEL(mpidr, 0);
			अचिन्हित दीर्घ offset = gic->percpu_offset * core_id;
			*per_cpu_ptr(gic->dist_base.percpu_base, cpu) =
				gic->raw_dist_base + offset;
			*per_cpu_ptr(gic->cpu_base.percpu_base, cpu) =
				gic->raw_cpu_base + offset;
		पूर्ण

		enable_frankengic();
	पूर्ण अन्यथा अणु
		/* Normal, sane GIC... */
		WARN(gic->percpu_offset,
		     "GIC_NON_BANKED not enabled, ignoring %08x offset!",
		     gic->percpu_offset);
		gic->dist_base.common_base = gic->raw_dist_base;
		gic->cpu_base.common_base = gic->raw_cpu_base;
	पूर्ण

	/*
	 * Find out how many पूर्णांकerrupts are supported.
	 * The GIC only supports up to 1020 पूर्णांकerrupt sources.
	 */
	gic_irqs = पढ़ोl_relaxed(gic_data_dist_base(gic) + GIC_DIST_CTR) & 0x1f;
	gic_irqs = (gic_irqs + 1) * 32;
	अगर (gic_irqs > 1020)
		gic_irqs = 1020;
	gic->gic_irqs = gic_irqs;

	अगर (handle) अणु		/* DT/ACPI */
		gic->करोमुख्य = irq_करोमुख्य_create_linear(handle, gic_irqs,
						       &gic_irq_करोमुख्य_hierarchy_ops,
						       gic);
	पूर्ण अन्यथा अणु		/* Legacy support */
		/*
		 * For primary GICs, skip over SGIs.
		 * No secondary GIC support whatsoever.
		 */
		पूर्णांक irq_base;

		gic_irqs -= 16; /* calculate # of irqs to allocate */

		irq_base = irq_alloc_descs(16, 16, gic_irqs,
					   numa_node_id());
		अगर (irq_base < 0) अणु
			WARN(1, "Cannot allocate irq_descs @ IRQ16, assuming pre-allocated\n");
			irq_base = 16;
		पूर्ण

		gic->करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, gic_irqs, irq_base,
						    16, &gic_irq_करोमुख्य_ops, gic);
	पूर्ण

	अगर (WARN_ON(!gic->करोमुख्य)) अणु
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	gic_dist_init(gic);
	ret = gic_cpu_init(gic);
	अगर (ret)
		जाओ error;

	ret = gic_pm_init(gic);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	अगर (IS_ENABLED(CONFIG_GIC_NON_BANKED) && gic->percpu_offset) अणु
		मुक्त_percpu(gic->dist_base.percpu_base);
		मुक्त_percpu(gic->cpu_base.percpu_base);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init __gic_init_bases(काष्ठा gic_chip_data *gic,
				   काष्ठा fwnode_handle *handle)
अणु
	अक्षर *name;
	पूर्णांक i, ret;

	अगर (WARN_ON(!gic || gic->करोमुख्य))
		वापस -EINVAL;

	अगर (gic == &gic_data[0]) अणु
		/*
		 * Initialize the CPU पूर्णांकerface map to all CPUs.
		 * It will be refined as each CPU probes its ID.
		 * This is only necessary क्रम the primary GIC.
		 */
		क्रम (i = 0; i < NR_GIC_CPU_IF; i++)
			gic_cpu_map[i] = 0xff;

		set_handle_irq(gic_handle_irq);
		अगर (अटल_branch_likely(&supports_deactivate_key))
			pr_info("GIC: Using split EOI/Deactivate mode\n");
	पूर्ण

	अगर (अटल_branch_likely(&supports_deactivate_key) && gic == &gic_data[0]) अणु
		name = kaप्र_लिखो(GFP_KERNEL, "GICv2");
		gic_init_chip(gic, शून्य, name, true);
	पूर्ण अन्यथा अणु
		name = kaप्र_लिखो(GFP_KERNEL, "GIC-%d", (पूर्णांक)(gic-&gic_data[0]));
		gic_init_chip(gic, शून्य, name, false);
	पूर्ण

	ret = gic_init_bases(gic, handle);
	अगर (ret)
		kमुक्त(name);
	अन्यथा अगर (gic == &gic_data[0])
		gic_smp_init();

	वापस ret;
पूर्ण

व्योम __init gic_init(व्योम __iomem *dist_base, व्योम __iomem *cpu_base)
अणु
	काष्ठा gic_chip_data *gic;

	/*
	 * Non-DT/ACPI प्रणालीs won't run a hypervisor, so let's not
	 * bother with these...
	 */
	अटल_branch_disable(&supports_deactivate_key);

	gic = &gic_data[0];
	gic->raw_dist_base = dist_base;
	gic->raw_cpu_base = cpu_base;

	__gic_init_bases(gic, शून्य);
पूर्ण

अटल व्योम gic_tearकरोwn(काष्ठा gic_chip_data *gic)
अणु
	अगर (WARN_ON(!gic))
		वापस;

	अगर (gic->raw_dist_base)
		iounmap(gic->raw_dist_base);
	अगर (gic->raw_cpu_base)
		iounmap(gic->raw_cpu_base);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक gic_cnt __initdata;
अटल bool gicv2_क्रमce_probe;

अटल पूर्णांक __init gicv2_क्रमce_probe_cfg(अक्षर *buf)
अणु
	वापस strtobool(buf, &gicv2_क्रमce_probe);
पूर्ण
early_param("irqchip.gicv2_force_probe", gicv2_क्रमce_probe_cfg);

अटल bool gic_check_eoimode(काष्ठा device_node *node, व्योम __iomem **base)
अणु
	काष्ठा resource cpuअगर_res;

	of_address_to_resource(node, 1, &cpuअगर_res);

	अगर (!is_hyp_mode_available())
		वापस false;
	अगर (resource_size(&cpuअगर_res) < SZ_8K) अणु
		व्योम __iomem *alt;
		/*
		 * Check क्रम a stupid firmware that only exposes the
		 * first page of a GICv2.
		 */
		अगर (!gic_check_gicv2(*base))
			वापस false;

		अगर (!gicv2_क्रमce_probe) अणु
			pr_warn("GIC: GICv2 detected, but range too small and irqchip.gicv2_force_probe not set\n");
			वापस false;
		पूर्ण

		alt = ioremap(cpuअगर_res.start, SZ_8K);
		अगर (!alt)
			वापस false;
		अगर (!gic_check_gicv2(alt + SZ_4K)) अणु
			/*
			 * The first page was that of a GICv2, and
			 * the second was *something*. Let's trust it
			 * to be a GICv2, and update the mapping.
			 */
			pr_warn("GIC: GICv2 at %pa, but range is too small (broken DT?), assuming 8kB\n",
				&cpuअगर_res.start);
			iounmap(*base);
			*base = alt;
			वापस true;
		पूर्ण

		/*
		 * We detected *two* initial GICv2 pages in a
		 * row. Could be a GICv2 aliased over two 64kB
		 * pages. Update the resource, map the iospace, and
		 * pray.
		 */
		iounmap(alt);
		alt = ioremap(cpuअगर_res.start, SZ_128K);
		अगर (!alt)
			वापस false;
		pr_warn("GIC: Aliased GICv2 at %pa, trying to find the canonical range over 128kB\n",
			&cpuअगर_res.start);
		cpuअगर_res.end = cpuअगर_res.start + SZ_128K -1;
		iounmap(*base);
		*base = alt;
	पूर्ण
	अगर (resource_size(&cpuअगर_res) == SZ_128K) अणु
		/*
		 * Verअगरy that we have the first 4kB of a GICv2
		 * aliased over the first 64kB by checking the
		 * GICC_IIDR रेजिस्टर on both ends.
		 */
		अगर (!gic_check_gicv2(*base) ||
		    !gic_check_gicv2(*base + 0xf000))
			वापस false;

		/*
		 * Move the base up by 60kB, so that we have a 8kB
		 * contiguous region, which allows us to use GICC_सूची
		 * at its normal offset. Please pass me that bucket.
		 */
		*base += 0xf000;
		cpuअगर_res.start += 0xf000;
		pr_warn("GIC: Adjusting CPU interface base to %pa\n",
			&cpuअगर_res.start);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक gic_of_setup(काष्ठा gic_chip_data *gic, काष्ठा device_node *node)
अणु
	अगर (!gic || !node)
		वापस -EINVAL;

	gic->raw_dist_base = of_iomap(node, 0);
	अगर (WARN(!gic->raw_dist_base, "unable to map gic dist registers\n"))
		जाओ error;

	gic->raw_cpu_base = of_iomap(node, 1);
	अगर (WARN(!gic->raw_cpu_base, "unable to map gic cpu registers\n"))
		जाओ error;

	अगर (of_property_पढ़ो_u32(node, "cpu-offset", &gic->percpu_offset))
		gic->percpu_offset = 0;

	वापस 0;

error:
	gic_tearकरोwn(gic);

	वापस -ENOMEM;
पूर्ण

पूर्णांक gic_of_init_child(काष्ठा device *dev, काष्ठा gic_chip_data **gic, पूर्णांक irq)
अणु
	पूर्णांक ret;

	अगर (!dev || !dev->of_node || !gic || !irq)
		वापस -EINVAL;

	*gic = devm_kzalloc(dev, माप(**gic), GFP_KERNEL);
	अगर (!*gic)
		वापस -ENOMEM;

	gic_init_chip(*gic, dev, dev->of_node->name, false);

	ret = gic_of_setup(*gic, dev->of_node);
	अगर (ret)
		वापस ret;

	ret = gic_init_bases(*gic, &dev->of_node->fwnode);
	अगर (ret) अणु
		gic_tearकरोwn(*gic);
		वापस ret;
	पूर्ण

	irq_set_chained_handler_and_data(irq, gic_handle_cascade_irq, *gic);

	वापस 0;
पूर्ण

अटल व्योम __init gic_of_setup_kvm_info(काष्ठा device_node *node)
अणु
	पूर्णांक ret;
	काष्ठा resource *vctrl_res = &gic_v2_kvm_info.vctrl;
	काष्ठा resource *vcpu_res = &gic_v2_kvm_info.vcpu;

	gic_v2_kvm_info.type = GIC_V2;

	gic_v2_kvm_info.मुख्यt_irq = irq_of_parse_and_map(node, 0);
	अगर (!gic_v2_kvm_info.मुख्यt_irq)
		वापस;

	ret = of_address_to_resource(node, 2, vctrl_res);
	अगर (ret)
		वापस;

	ret = of_address_to_resource(node, 3, vcpu_res);
	अगर (ret)
		वापस;

	अगर (अटल_branch_likely(&supports_deactivate_key))
		gic_set_kvm_info(&gic_v2_kvm_info);
पूर्ण

पूर्णांक __init
gic_of_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	काष्ठा gic_chip_data *gic;
	पूर्णांक irq, ret;

	अगर (WARN_ON(!node))
		वापस -ENODEV;

	अगर (WARN_ON(gic_cnt >= CONFIG_ARM_GIC_MAX_NR))
		वापस -EINVAL;

	gic = &gic_data[gic_cnt];

	ret = gic_of_setup(gic, node);
	अगर (ret)
		वापस ret;

	/*
	 * Disable split EOI/Deactivate अगर either HYP is not available
	 * or the CPU पूर्णांकerface is too small.
	 */
	अगर (gic_cnt == 0 && !gic_check_eoimode(node, &gic->raw_cpu_base))
		अटल_branch_disable(&supports_deactivate_key);

	ret = __gic_init_bases(gic, &node->fwnode);
	अगर (ret) अणु
		gic_tearकरोwn(gic);
		वापस ret;
	पूर्ण

	अगर (!gic_cnt) अणु
		gic_init_physaddr(node);
		gic_of_setup_kvm_info(node);
	पूर्ण

	अगर (parent) अणु
		irq = irq_of_parse_and_map(node, 0);
		gic_cascade_irq(gic_cnt, irq);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_ARM_GIC_V2M))
		gicv2m_init(&node->fwnode, gic_data[gic_cnt].करोमुख्य);

	gic_cnt++;
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(gic_400, "arm,gic-400", gic_of_init);
IRQCHIP_DECLARE(arm11mp_gic, "arm,arm11mp-gic", gic_of_init);
IRQCHIP_DECLARE(arm1176jzf_dc_gic, "arm,arm1176jzf-devchip-gic", gic_of_init);
IRQCHIP_DECLARE(cortex_a15_gic, "arm,cortex-a15-gic", gic_of_init);
IRQCHIP_DECLARE(cortex_a9_gic, "arm,cortex-a9-gic", gic_of_init);
IRQCHIP_DECLARE(cortex_a7_gic, "arm,cortex-a7-gic", gic_of_init);
IRQCHIP_DECLARE(msm_8660_qgic, "qcom,msm-8660-qgic", gic_of_init);
IRQCHIP_DECLARE(msm_qgic2, "qcom,msm-qgic2", gic_of_init);
IRQCHIP_DECLARE(pl390, "arm,pl390", gic_of_init);
#अन्यथा
पूर्णांक gic_of_init_child(काष्ठा device *dev, काष्ठा gic_chip_data **gic, पूर्णांक irq)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल काष्ठा
अणु
	phys_addr_t cpu_phys_base;
	u32 मुख्यt_irq;
	पूर्णांक मुख्यt_irq_mode;
	phys_addr_t vctrl_base;
	phys_addr_t vcpu_base;
पूर्ण acpi_data __initdata;

अटल पूर्णांक __init
gic_acpi_parse_madt_cpu(जोड़ acpi_subtable_headers *header,
			स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_पूर्णांकerrupt *processor;
	phys_addr_t gic_cpu_base;
	अटल पूर्णांक cpu_base_asचिन्हित;

	processor = (काष्ठा acpi_madt_generic_पूर्णांकerrupt *)header;

	अगर (BAD_MADT_GICC_ENTRY(processor, end))
		वापस -EINVAL;

	/*
	 * There is no support क्रम non-banked GICv1/2 रेजिस्टर in ACPI spec.
	 * All CPU पूर्णांकerface addresses have to be the same.
	 */
	gic_cpu_base = processor->base_address;
	अगर (cpu_base_asचिन्हित && gic_cpu_base != acpi_data.cpu_phys_base)
		वापस -EINVAL;

	acpi_data.cpu_phys_base = gic_cpu_base;
	acpi_data.मुख्यt_irq = processor->vgic_पूर्णांकerrupt;
	acpi_data.मुख्यt_irq_mode = (processor->flags & ACPI_MADT_VGIC_IRQ_MODE) ?
				    ACPI_EDGE_SENSITIVE : ACPI_LEVEL_SENSITIVE;
	acpi_data.vctrl_base = processor->gich_base_address;
	acpi_data.vcpu_base = processor->gicv_base_address;

	cpu_base_asचिन्हित = 1;
	वापस 0;
पूर्ण

/* The things you have to करो to just *count* something... */
अटल पूर्णांक __init acpi_dummy_func(जोड़ acpi_subtable_headers *header,
				  स्थिर अचिन्हित दीर्घ end)
अणु
	वापस 0;
पूर्ण

अटल bool __init acpi_gic_redist_is_present(व्योम)
अणु
	वापस acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR,
				     acpi_dummy_func, 0) > 0;
पूर्ण

अटल bool __init gic_validate_dist(काष्ठा acpi_subtable_header *header,
				     काष्ठा acpi_probe_entry *ape)
अणु
	काष्ठा acpi_madt_generic_distributor *dist;
	dist = (काष्ठा acpi_madt_generic_distributor *)header;

	वापस (dist->version == ape->driver_data &&
		(dist->version != ACPI_MADT_GIC_VERSION_NONE ||
		 !acpi_gic_redist_is_present()));
पूर्ण

#घोषणा ACPI_GICV2_DIST_MEM_SIZE	(SZ_4K)
#घोषणा ACPI_GIC_CPU_IF_MEM_SIZE	(SZ_8K)
#घोषणा ACPI_GICV2_VCTRL_MEM_SIZE	(SZ_4K)
#घोषणा ACPI_GICV2_VCPU_MEM_SIZE	(SZ_8K)

अटल व्योम __init gic_acpi_setup_kvm_info(व्योम)
अणु
	पूर्णांक irq;
	काष्ठा resource *vctrl_res = &gic_v2_kvm_info.vctrl;
	काष्ठा resource *vcpu_res = &gic_v2_kvm_info.vcpu;

	gic_v2_kvm_info.type = GIC_V2;

	अगर (!acpi_data.vctrl_base)
		वापस;

	vctrl_res->flags = IORESOURCE_MEM;
	vctrl_res->start = acpi_data.vctrl_base;
	vctrl_res->end = vctrl_res->start + ACPI_GICV2_VCTRL_MEM_SIZE - 1;

	अगर (!acpi_data.vcpu_base)
		वापस;

	vcpu_res->flags = IORESOURCE_MEM;
	vcpu_res->start = acpi_data.vcpu_base;
	vcpu_res->end = vcpu_res->start + ACPI_GICV2_VCPU_MEM_SIZE - 1;

	irq = acpi_रेजिस्टर_gsi(शून्य, acpi_data.मुख्यt_irq,
				acpi_data.मुख्यt_irq_mode,
				ACPI_ACTIVE_HIGH);
	अगर (irq <= 0)
		वापस;

	gic_v2_kvm_info.मुख्यt_irq = irq;

	gic_set_kvm_info(&gic_v2_kvm_info);
पूर्ण

अटल पूर्णांक __init gic_v2_acpi_init(जोड़ acpi_subtable_headers *header,
				   स्थिर अचिन्हित दीर्घ end)
अणु
	काष्ठा acpi_madt_generic_distributor *dist;
	काष्ठा fwnode_handle *करोमुख्य_handle;
	काष्ठा gic_chip_data *gic = &gic_data[0];
	पूर्णांक count, ret;

	/* Collect CPU base addresses */
	count = acpi_table_parse_madt(ACPI_MADT_TYPE_GENERIC_INTERRUPT,
				      gic_acpi_parse_madt_cpu, 0);
	अगर (count <= 0) अणु
		pr_err("No valid GICC entries exist\n");
		वापस -EINVAL;
	पूर्ण

	gic->raw_cpu_base = ioremap(acpi_data.cpu_phys_base, ACPI_GIC_CPU_IF_MEM_SIZE);
	अगर (!gic->raw_cpu_base) अणु
		pr_err("Unable to map GICC registers\n");
		वापस -ENOMEM;
	पूर्ण

	dist = (काष्ठा acpi_madt_generic_distributor *)header;
	gic->raw_dist_base = ioremap(dist->base_address,
				     ACPI_GICV2_DIST_MEM_SIZE);
	अगर (!gic->raw_dist_base) अणु
		pr_err("Unable to map GICD registers\n");
		gic_tearकरोwn(gic);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Disable split EOI/Deactivate अगर HYP is not available. ACPI
	 * guarantees that we'll always have a GICv2, so the CPU
	 * पूर्णांकerface will always be the right size.
	 */
	अगर (!is_hyp_mode_available())
		अटल_branch_disable(&supports_deactivate_key);

	/*
	 * Initialize GIC instance zero (no multi-GIC support).
	 */
	करोमुख्य_handle = irq_करोमुख्य_alloc_fwnode(&dist->base_address);
	अगर (!करोमुख्य_handle) अणु
		pr_err("Unable to allocate domain handle\n");
		gic_tearकरोwn(gic);
		वापस -ENOMEM;
	पूर्ण

	ret = __gic_init_bases(gic, करोमुख्य_handle);
	अगर (ret) अणु
		pr_err("Failed to initialise GIC\n");
		irq_करोमुख्य_मुक्त_fwnode(करोमुख्य_handle);
		gic_tearकरोwn(gic);
		वापस ret;
	पूर्ण

	acpi_set_irq_model(ACPI_IRQ_MODEL_GIC, करोमुख्य_handle);

	अगर (IS_ENABLED(CONFIG_ARM_GIC_V2M))
		gicv2m_init(शून्य, gic_data[0].करोमुख्य);

	अगर (अटल_branch_likely(&supports_deactivate_key))
		gic_acpi_setup_kvm_info();

	वापस 0;
पूर्ण
IRQCHIP_ACPI_DECLARE(gic_v2, ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR,
		     gic_validate_dist, ACPI_MADT_GIC_VERSION_V2,
		     gic_v2_acpi_init);
IRQCHIP_ACPI_DECLARE(gic_v2_maybe, ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR,
		     gic_validate_dist, ACPI_MADT_GIC_VERSION_NONE,
		     gic_v2_acpi_init);
#पूर्ण_अगर
