<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2012 MIPS Technologies, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) "irq-mips-gic: " fmt

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_address.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/traps.h>

#समावेश <dt-bindings/पूर्णांकerrupt-controller/mips-gic.h>

#घोषणा GIC_MAX_INTRS		256
#घोषणा GIC_MAX_LONGS		BITS_TO_LONGS(GIC_MAX_INTRS)

/* Add 2 to convert GIC CPU pin to core पूर्णांकerrupt */
#घोषणा GIC_CPU_PIN_OFFSET	2

/* Mapped पूर्णांकerrupt to pin X, then GIC will generate the vector (X+1). */
#घोषणा GIC_PIN_TO_VEC_OFFSET	1

/* Convert between local/shared IRQ number and GIC HW IRQ number. */
#घोषणा GIC_LOCAL_HWIRQ_BASE	0
#घोषणा GIC_LOCAL_TO_HWIRQ(x)	(GIC_LOCAL_HWIRQ_BASE + (x))
#घोषणा GIC_HWIRQ_TO_LOCAL(x)	((x) - GIC_LOCAL_HWIRQ_BASE)
#घोषणा GIC_SHARED_HWIRQ_BASE	GIC_NUM_LOCAL_INTRS
#घोषणा GIC_SHARED_TO_HWIRQ(x)	(GIC_SHARED_HWIRQ_BASE + (x))
#घोषणा GIC_HWIRQ_TO_SHARED(x)	((x) - GIC_SHARED_HWIRQ_BASE)

व्योम __iomem *mips_gic_base;

अटल DEFINE_PER_CPU_READ_MOSTLY(अचिन्हित दीर्घ[GIC_MAX_LONGS], pcpu_masks);

अटल DEFINE_SPINLOCK(gic_lock);
अटल काष्ठा irq_करोमुख्य *gic_irq_करोमुख्य;
अटल काष्ठा irq_करोमुख्य *gic_ipi_करोमुख्य;
अटल पूर्णांक gic_shared_पूर्णांकrs;
अटल अचिन्हित पूर्णांक gic_cpu_pin;
अटल अचिन्हित पूर्णांक समयr_cpu_pin;
अटल काष्ठा irq_chip gic_level_irq_controller, gic_edge_irq_controller;
अटल DECLARE_BITMAP(ipi_resrv, GIC_MAX_INTRS);
अटल DECLARE_BITMAP(ipi_available, GIC_MAX_INTRS);

अटल काष्ठा gic_all_vpes_chip_data अणु
	u32	map;
	bool	mask;
पूर्ण gic_all_vpes_chip_data[GIC_NUM_LOCAL_INTRS];

अटल व्योम gic_clear_pcpu_masks(अचिन्हित पूर्णांक पूर्णांकr)
अणु
	अचिन्हित पूर्णांक i;

	/* Clear the पूर्णांकerrupt's bit in all pcpu_masks */
	क्रम_each_possible_cpu(i)
		clear_bit(पूर्णांकr, per_cpu_ptr(pcpu_masks, i));
पूर्ण

अटल bool gic_local_irq_is_routable(पूर्णांक पूर्णांकr)
अणु
	u32 vpe_ctl;

	/* All local पूर्णांकerrupts are routable in EIC mode. */
	अगर (cpu_has_veic)
		वापस true;

	vpe_ctl = पढ़ो_gic_vl_ctl();
	चयन (पूर्णांकr) अणु
	हाल GIC_LOCAL_INT_TIMER:
		वापस vpe_ctl & GIC_VX_CTL_TIMER_ROUTABLE;
	हाल GIC_LOCAL_INT_PERFCTR:
		वापस vpe_ctl & GIC_VX_CTL_PERFCNT_ROUTABLE;
	हाल GIC_LOCAL_INT_FDC:
		वापस vpe_ctl & GIC_VX_CTL_FDC_ROUTABLE;
	हाल GIC_LOCAL_INT_SWINT0:
	हाल GIC_LOCAL_INT_SWINT1:
		वापस vpe_ctl & GIC_VX_CTL_SWINT_ROUTABLE;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल व्योम gic_bind_eic_पूर्णांकerrupt(पूर्णांक irq, पूर्णांक set)
अणु
	/* Convert irq vector # to hw पूर्णांक # */
	irq -= GIC_PIN_TO_VEC_OFFSET;

	/* Set irq to use shaकरोw set */
	ग_लिखो_gic_vl_eic_shaकरोw_set(irq, set);
पूर्ण

अटल व्योम gic_send_ipi(काष्ठा irq_data *d, अचिन्हित पूर्णांक cpu)
अणु
	irq_hw_number_t hwirq = GIC_HWIRQ_TO_SHARED(irqd_to_hwirq(d));

	ग_लिखो_gic_wedge(GIC_WEDGE_RW | hwirq);
पूर्ण

पूर्णांक gic_get_c0_compare_पूर्णांक(व्योम)
अणु
	अगर (!gic_local_irq_is_routable(GIC_LOCAL_INT_TIMER))
		वापस MIPS_CPU_IRQ_BASE + cp0_compare_irq;
	वापस irq_create_mapping(gic_irq_करोमुख्य,
				  GIC_LOCAL_TO_HWIRQ(GIC_LOCAL_INT_TIMER));
पूर्ण

पूर्णांक gic_get_c0_perfcount_पूर्णांक(व्योम)
अणु
	अगर (!gic_local_irq_is_routable(GIC_LOCAL_INT_PERFCTR)) अणु
		/* Is the perक्रमmance counter shared with the समयr? */
		अगर (cp0_perfcount_irq < 0)
			वापस -1;
		वापस MIPS_CPU_IRQ_BASE + cp0_perfcount_irq;
	पूर्ण
	वापस irq_create_mapping(gic_irq_करोमुख्य,
				  GIC_LOCAL_TO_HWIRQ(GIC_LOCAL_INT_PERFCTR));
पूर्ण

पूर्णांक gic_get_c0_fdc_पूर्णांक(व्योम)
अणु
	अगर (!gic_local_irq_is_routable(GIC_LOCAL_INT_FDC)) अणु
		/* Is the FDC IRQ even present? */
		अगर (cp0_fdc_irq < 0)
			वापस -1;
		वापस MIPS_CPU_IRQ_BASE + cp0_fdc_irq;
	पूर्ण

	वापस irq_create_mapping(gic_irq_करोमुख्य,
				  GIC_LOCAL_TO_HWIRQ(GIC_LOCAL_INT_FDC));
पूर्ण

अटल व्योम gic_handle_shared_पूर्णांक(bool chained)
अणु
	अचिन्हित पूर्णांक पूर्णांकr, virq;
	अचिन्हित दीर्घ *pcpu_mask;
	DECLARE_BITMAP(pending, GIC_MAX_INTRS);

	/* Get per-cpu biपंचांगaps */
	pcpu_mask = this_cpu_ptr(pcpu_masks);

	अगर (mips_cm_is64)
		__ioपढ़ो64_copy(pending, addr_gic_pend(),
				DIV_ROUND_UP(gic_shared_पूर्णांकrs, 64));
	अन्यथा
		__ioपढ़ो32_copy(pending, addr_gic_pend(),
				DIV_ROUND_UP(gic_shared_पूर्णांकrs, 32));

	biपंचांगap_and(pending, pending, pcpu_mask, gic_shared_पूर्णांकrs);

	क्रम_each_set_bit(पूर्णांकr, pending, gic_shared_पूर्णांकrs) अणु
		virq = irq_linear_revmap(gic_irq_करोमुख्य,
					 GIC_SHARED_TO_HWIRQ(पूर्णांकr));
		अगर (chained)
			generic_handle_irq(virq);
		अन्यथा
			करो_IRQ(virq);
	पूर्ण
पूर्ण

अटल व्योम gic_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक पूर्णांकr = GIC_HWIRQ_TO_SHARED(d->hwirq);

	ग_लिखो_gic_rmask(पूर्णांकr);
	gic_clear_pcpu_masks(पूर्णांकr);
पूर्ण

अटल व्योम gic_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक पूर्णांकr = GIC_HWIRQ_TO_SHARED(d->hwirq);
	अचिन्हित पूर्णांक cpu;

	ग_लिखो_gic_smask(पूर्णांकr);

	gic_clear_pcpu_masks(पूर्णांकr);
	cpu = cpumask_first(irq_data_get_effective_affinity_mask(d));
	set_bit(पूर्णांकr, per_cpu_ptr(pcpu_masks, cpu));
पूर्ण

अटल व्योम gic_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = GIC_HWIRQ_TO_SHARED(d->hwirq);

	ग_लिखो_gic_wedge(irq);
पूर्ण

अटल पूर्णांक gic_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक irq, pol, trig, dual;
	अचिन्हित दीर्घ flags;

	irq = GIC_HWIRQ_TO_SHARED(d->hwirq);

	spin_lock_irqsave(&gic_lock, flags);
	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_FALLING:
		pol = GIC_POL_FALLING_EDGE;
		trig = GIC_TRIG_EDGE;
		dual = GIC_DUAL_SINGLE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		pol = GIC_POL_RISING_EDGE;
		trig = GIC_TRIG_EDGE;
		dual = GIC_DUAL_SINGLE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		pol = 0; /* Doesn't matter */
		trig = GIC_TRIG_EDGE;
		dual = GIC_DUAL_DUAL;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		pol = GIC_POL_ACTIVE_LOW;
		trig = GIC_TRIG_LEVEL;
		dual = GIC_DUAL_SINGLE;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
	शेष:
		pol = GIC_POL_ACTIVE_HIGH;
		trig = GIC_TRIG_LEVEL;
		dual = GIC_DUAL_SINGLE;
		अवरोध;
	पूर्ण

	change_gic_pol(irq, pol);
	change_gic_trig(irq, trig);
	change_gic_dual(irq, dual);

	अगर (trig == GIC_TRIG_EDGE)
		irq_set_chip_handler_name_locked(d, &gic_edge_irq_controller,
						 handle_edge_irq, शून्य);
	अन्यथा
		irq_set_chip_handler_name_locked(d, &gic_level_irq_controller,
						 handle_level_irq, शून्य);
	spin_unlock_irqrestore(&gic_lock, flags);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक gic_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *cpumask,
			    bool क्रमce)
अणु
	अचिन्हित पूर्णांक irq = GIC_HWIRQ_TO_SHARED(d->hwirq);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cpu;

	cpu = cpumask_first_and(cpumask, cpu_online_mask);
	अगर (cpu >= NR_CPUS)
		वापस -EINVAL;

	/* Assumption : cpumask refers to a single CPU */
	spin_lock_irqsave(&gic_lock, flags);

	/* Re-route this IRQ */
	ग_लिखो_gic_map_vp(irq, BIT(mips_cm_vp_id(cpu)));

	/* Update the pcpu_masks */
	gic_clear_pcpu_masks(irq);
	अगर (पढ़ो_gic_mask(irq))
		set_bit(irq, per_cpu_ptr(pcpu_masks, cpu));

	irq_data_update_effective_affinity(d, cpumask_of(cpu));
	spin_unlock_irqrestore(&gic_lock, flags);

	वापस IRQ_SET_MASK_OK;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip gic_level_irq_controller = अणु
	.name			=	"MIPS GIC",
	.irq_mask		=	gic_mask_irq,
	.irq_unmask		=	gic_unmask_irq,
	.irq_set_type		=	gic_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	=	gic_set_affinity,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा irq_chip gic_edge_irq_controller = अणु
	.name			=	"MIPS GIC",
	.irq_ack		=	gic_ack_irq,
	.irq_mask		=	gic_mask_irq,
	.irq_unmask		=	gic_unmask_irq,
	.irq_set_type		=	gic_set_type,
#अगर_घोषित CONFIG_SMP
	.irq_set_affinity	=	gic_set_affinity,
#पूर्ण_अगर
	.ipi_send_single	=	gic_send_ipi,
पूर्ण;

अटल व्योम gic_handle_local_पूर्णांक(bool chained)
अणु
	अचिन्हित दीर्घ pending, masked;
	अचिन्हित पूर्णांक पूर्णांकr, virq;

	pending = पढ़ो_gic_vl_pend();
	masked = पढ़ो_gic_vl_mask();

	biपंचांगap_and(&pending, &pending, &masked, GIC_NUM_LOCAL_INTRS);

	क्रम_each_set_bit(पूर्णांकr, &pending, GIC_NUM_LOCAL_INTRS) अणु
		virq = irq_linear_revmap(gic_irq_करोमुख्य,
					 GIC_LOCAL_TO_HWIRQ(पूर्णांकr));
		अगर (chained)
			generic_handle_irq(virq);
		अन्यथा
			करो_IRQ(virq);
	पूर्ण
पूर्ण

अटल व्योम gic_mask_local_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक पूर्णांकr = GIC_HWIRQ_TO_LOCAL(d->hwirq);

	ग_लिखो_gic_vl_rmask(BIT(पूर्णांकr));
पूर्ण

अटल व्योम gic_unmask_local_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक पूर्णांकr = GIC_HWIRQ_TO_LOCAL(d->hwirq);

	ग_लिखो_gic_vl_smask(BIT(पूर्णांकr));
पूर्ण

अटल काष्ठा irq_chip gic_local_irq_controller = अणु
	.name			=	"MIPS GIC Local",
	.irq_mask		=	gic_mask_local_irq,
	.irq_unmask		=	gic_unmask_local_irq,
पूर्ण;

अटल व्योम gic_mask_local_irq_all_vpes(काष्ठा irq_data *d)
अणु
	काष्ठा gic_all_vpes_chip_data *cd;
	अचिन्हित दीर्घ flags;
	पूर्णांक पूर्णांकr, cpu;

	पूर्णांकr = GIC_HWIRQ_TO_LOCAL(d->hwirq);
	cd = irq_data_get_irq_chip_data(d);
	cd->mask = false;

	spin_lock_irqsave(&gic_lock, flags);
	क्रम_each_online_cpu(cpu) अणु
		ग_लिखो_gic_vl_other(mips_cm_vp_id(cpu));
		ग_लिखो_gic_vo_rmask(BIT(पूर्णांकr));
	पूर्ण
	spin_unlock_irqrestore(&gic_lock, flags);
पूर्ण

अटल व्योम gic_unmask_local_irq_all_vpes(काष्ठा irq_data *d)
अणु
	काष्ठा gic_all_vpes_chip_data *cd;
	अचिन्हित दीर्घ flags;
	पूर्णांक पूर्णांकr, cpu;

	पूर्णांकr = GIC_HWIRQ_TO_LOCAL(d->hwirq);
	cd = irq_data_get_irq_chip_data(d);
	cd->mask = true;

	spin_lock_irqsave(&gic_lock, flags);
	क्रम_each_online_cpu(cpu) अणु
		ग_लिखो_gic_vl_other(mips_cm_vp_id(cpu));
		ग_लिखो_gic_vo_smask(BIT(पूर्णांकr));
	पूर्ण
	spin_unlock_irqrestore(&gic_lock, flags);
पूर्ण

अटल व्योम gic_all_vpes_irq_cpu_online(काष्ठा irq_data *d)
अणु
	काष्ठा gic_all_vpes_chip_data *cd;
	अचिन्हित पूर्णांक पूर्णांकr;

	पूर्णांकr = GIC_HWIRQ_TO_LOCAL(d->hwirq);
	cd = irq_data_get_irq_chip_data(d);

	ग_लिखो_gic_vl_map(mips_gic_vx_map_reg(पूर्णांकr), cd->map);
	अगर (cd->mask)
		ग_लिखो_gic_vl_smask(BIT(पूर्णांकr));
पूर्ण

अटल काष्ठा irq_chip gic_all_vpes_local_irq_controller = अणु
	.name			= "MIPS GIC Local",
	.irq_mask		= gic_mask_local_irq_all_vpes,
	.irq_unmask		= gic_unmask_local_irq_all_vpes,
	.irq_cpu_online		= gic_all_vpes_irq_cpu_online,
पूर्ण;

अटल व्योम __gic_irq_dispatch(व्योम)
अणु
	gic_handle_local_पूर्णांक(false);
	gic_handle_shared_पूर्णांक(false);
पूर्ण

अटल व्योम gic_irq_dispatch(काष्ठा irq_desc *desc)
अणु
	gic_handle_local_पूर्णांक(true);
	gic_handle_shared_पूर्णांक(true);
पूर्ण

अटल पूर्णांक gic_shared_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				     irq_hw_number_t hw, अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक पूर्णांकr = GIC_HWIRQ_TO_SHARED(hw);
	काष्ठा irq_data *data;
	अचिन्हित दीर्घ flags;

	data = irq_get_irq_data(virq);

	spin_lock_irqsave(&gic_lock, flags);
	ग_लिखो_gic_map_pin(पूर्णांकr, GIC_MAP_PIN_MAP_TO_PIN | gic_cpu_pin);
	ग_लिखो_gic_map_vp(पूर्णांकr, BIT(mips_cm_vp_id(cpu)));
	irq_data_update_effective_affinity(data, cpumask_of(cpu));
	spin_unlock_irqrestore(&gic_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक gic_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
				स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				irq_hw_number_t *out_hwirq,
				अचिन्हित पूर्णांक *out_type)
अणु
	अगर (पूर्णांकsize != 3)
		वापस -EINVAL;

	अगर (पूर्णांकspec[0] == GIC_SHARED)
		*out_hwirq = GIC_SHARED_TO_HWIRQ(पूर्णांकspec[1]);
	अन्यथा अगर (पूर्णांकspec[0] == GIC_LOCAL)
		*out_hwirq = GIC_LOCAL_TO_HWIRQ(पूर्णांकspec[1]);
	अन्यथा
		वापस -EINVAL;
	*out_type = पूर्णांकspec[2] & IRQ_TYPE_SENSE_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक gic_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			      irq_hw_number_t hwirq)
अणु
	काष्ठा gic_all_vpes_chip_data *cd;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक पूर्णांकr;
	पूर्णांक err, cpu;
	u32 map;

	अगर (hwirq >= GIC_SHARED_HWIRQ_BASE) अणु
		/* verअगरy that shared irqs करोn't conflict with an IPI irq */
		अगर (test_bit(GIC_HWIRQ_TO_SHARED(hwirq), ipi_resrv))
			वापस -EBUSY;

		err = irq_करोमुख्य_set_hwirq_and_chip(d, virq, hwirq,
						    &gic_level_irq_controller,
						    शून्य);
		अगर (err)
			वापस err;

		irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(virq)));
		वापस gic_shared_irq_करोमुख्य_map(d, virq, hwirq, 0);
	पूर्ण

	पूर्णांकr = GIC_HWIRQ_TO_LOCAL(hwirq);
	map = GIC_MAP_PIN_MAP_TO_PIN | gic_cpu_pin;

	चयन (पूर्णांकr) अणु
	हाल GIC_LOCAL_INT_TIMER:
		/* CONFIG_MIPS_CMP workaround (see __gic_init) */
		map = GIC_MAP_PIN_MAP_TO_PIN | समयr_cpu_pin;
		fallthrough;
	हाल GIC_LOCAL_INT_PERFCTR:
	हाल GIC_LOCAL_INT_FDC:
		/*
		 * HACK: These are all really percpu पूर्णांकerrupts, but
		 * the rest of the MIPS kernel code करोes not use the
		 * percpu IRQ API क्रम them.
		 */
		cd = &gic_all_vpes_chip_data[पूर्णांकr];
		cd->map = map;
		err = irq_करोमुख्य_set_hwirq_and_chip(d, virq, hwirq,
						    &gic_all_vpes_local_irq_controller,
						    cd);
		अगर (err)
			वापस err;

		irq_set_handler(virq, handle_percpu_irq);
		अवरोध;

	शेष:
		err = irq_करोमुख्य_set_hwirq_and_chip(d, virq, hwirq,
						    &gic_local_irq_controller,
						    शून्य);
		अगर (err)
			वापस err;

		irq_set_handler(virq, handle_percpu_devid_irq);
		irq_set_percpu_devid(virq);
		अवरोध;
	पूर्ण

	अगर (!gic_local_irq_is_routable(पूर्णांकr))
		वापस -EPERM;

	spin_lock_irqsave(&gic_lock, flags);
	क्रम_each_online_cpu(cpu) अणु
		ग_लिखो_gic_vl_other(mips_cm_vp_id(cpu));
		ग_लिखो_gic_vo_map(mips_gic_vx_map_reg(पूर्णांकr), map);
	पूर्ण
	spin_unlock_irqrestore(&gic_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक gic_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा irq_fwspec *fwspec = arg;
	irq_hw_number_t hwirq;

	अगर (fwspec->param[0] == GIC_SHARED)
		hwirq = GIC_SHARED_TO_HWIRQ(fwspec->param[1]);
	अन्यथा
		hwirq = GIC_LOCAL_TO_HWIRQ(fwspec->param[1]);

	वापस gic_irq_करोमुख्य_map(d, virq, hwirq);
पूर्ण

व्योम gic_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			 अचिन्हित पूर्णांक nr_irqs)
अणु
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops gic_irq_करोमुख्य_ops = अणु
	.xlate = gic_irq_करोमुख्य_xlate,
	.alloc = gic_irq_करोमुख्य_alloc,
	.मुक्त = gic_irq_करोमुख्य_मुक्त,
	.map = gic_irq_करोमुख्य_map,
पूर्ण;

अटल पूर्णांक gic_ipi_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *ctrlr,
				स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				irq_hw_number_t *out_hwirq,
				अचिन्हित पूर्णांक *out_type)
अणु
	/*
	 * There's nothing to translate here. hwirq is dynamically allocated and
	 * the irq type is always edge triggered.
	 * */
	*out_hwirq = 0;
	*out_type = IRQ_TYPE_EDGE_RISING;

	वापस 0;
पूर्ण

अटल पूर्णांक gic_ipi_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा cpumask *ipimask = arg;
	irq_hw_number_t hwirq, base_hwirq;
	पूर्णांक cpu, ret, i;

	base_hwirq = find_first_bit(ipi_available, gic_shared_पूर्णांकrs);
	अगर (base_hwirq == gic_shared_पूर्णांकrs)
		वापस -ENOMEM;

	/* check that we have enough space */
	क्रम (i = base_hwirq; i < nr_irqs; i++) अणु
		अगर (!test_bit(i, ipi_available))
			वापस -EBUSY;
	पूर्ण
	biपंचांगap_clear(ipi_available, base_hwirq, nr_irqs);

	/* map the hwirq क्रम each cpu consecutively */
	i = 0;
	क्रम_each_cpu(cpu, ipimask) अणु
		hwirq = GIC_SHARED_TO_HWIRQ(base_hwirq + i);

		ret = irq_करोमुख्य_set_hwirq_and_chip(d, virq + i, hwirq,
						    &gic_edge_irq_controller,
						    शून्य);
		अगर (ret)
			जाओ error;

		ret = irq_करोमुख्य_set_hwirq_and_chip(d->parent, virq + i, hwirq,
						    &gic_edge_irq_controller,
						    शून्य);
		अगर (ret)
			जाओ error;

		ret = irq_set_irq_type(virq + i, IRQ_TYPE_EDGE_RISING);
		अगर (ret)
			जाओ error;

		ret = gic_shared_irq_करोमुख्य_map(d, virq + i, hwirq, cpu);
		अगर (ret)
			जाओ error;

		i++;
	पूर्ण

	वापस 0;
error:
	biपंचांगap_set(ipi_available, base_hwirq, nr_irqs);
	वापस ret;
पूर्ण

अटल व्योम gic_ipi_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				अचिन्हित पूर्णांक nr_irqs)
अणु
	irq_hw_number_t base_hwirq;
	काष्ठा irq_data *data;

	data = irq_get_irq_data(virq);
	अगर (!data)
		वापस;

	base_hwirq = GIC_HWIRQ_TO_SHARED(irqd_to_hwirq(data));
	biपंचांगap_set(ipi_available, base_hwirq, nr_irqs);
पूर्ण

अटल पूर्णांक gic_ipi_करोमुख्य_match(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *node,
				क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	bool is_ipi;

	चयन (bus_token) अणु
	हाल DOMAIN_BUS_IPI:
		is_ipi = d->bus_token == bus_token;
		वापस (!node || to_of_node(d->fwnode) == node) && is_ipi;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops gic_ipi_करोमुख्य_ops = अणु
	.xlate = gic_ipi_करोमुख्य_xlate,
	.alloc = gic_ipi_करोमुख्य_alloc,
	.मुक्त = gic_ipi_करोमुख्य_मुक्त,
	.match = gic_ipi_करोमुख्य_match,
पूर्ण;

अटल पूर्णांक gic_cpu_startup(अचिन्हित पूर्णांक cpu)
अणु
	/* Enable or disable EIC */
	change_gic_vl_ctl(GIC_VX_CTL_EIC,
			  cpu_has_veic ? GIC_VX_CTL_EIC : 0);

	/* Clear all local IRQ masks (ie. disable all local पूर्णांकerrupts) */
	ग_लिखो_gic_vl_rmask(~0);

	/* Invoke irq_cpu_online callbacks to enable desired पूर्णांकerrupts */
	irq_cpu_online();

	वापस 0;
पूर्ण

अटल पूर्णांक __init gic_of_init(काष्ठा device_node *node,
			      काष्ठा device_node *parent)
अणु
	अचिन्हित पूर्णांक cpu_vec, i, gicconfig, v[2], num_ipis;
	अचिन्हित दीर्घ reserved;
	phys_addr_t gic_base;
	काष्ठा resource res;
	माप_प्रकार gic_len;

	/* Find the first available CPU vector. */
	i = 0;
	reserved = (C_SW0 | C_SW1) >> __ffs(C_SW0);
	जबतक (!of_property_पढ़ो_u32_index(node, "mti,reserved-cpu-vectors",
					   i++, &cpu_vec))
		reserved |= BIT(cpu_vec);

	cpu_vec = find_first_zero_bit(&reserved, hweight_दीर्घ(ST0_IM));
	अगर (cpu_vec == hweight_दीर्घ(ST0_IM)) अणु
		pr_err("No CPU vectors available\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_address_to_resource(node, 0, &res)) अणु
		/*
		 * Probe the CM क्रम the GIC base address अगर not specअगरied
		 * in the device-tree.
		 */
		अगर (mips_cm_present()) अणु
			gic_base = पढ़ो_gcr_gic_base() &
				~CM_GCR_GIC_BASE_GICEN;
			gic_len = 0x20000;
			pr_warn("Using inherited base address %pa\n",
				&gic_base);
		पूर्ण अन्यथा अणु
			pr_err("Failed to get memory range\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		gic_base = res.start;
		gic_len = resource_size(&res);
	पूर्ण

	अगर (mips_cm_present()) अणु
		ग_लिखो_gcr_gic_base(gic_base | CM_GCR_GIC_BASE_GICEN);
		/* Ensure GIC region is enabled beक्रमe trying to access it */
		__sync();
	पूर्ण

	mips_gic_base = ioremap(gic_base, gic_len);

	gicconfig = पढ़ो_gic_config();
	gic_shared_पूर्णांकrs = gicconfig & GIC_CONFIG_NUMINTERRUPTS;
	gic_shared_पूर्णांकrs >>= __ffs(GIC_CONFIG_NUMINTERRUPTS);
	gic_shared_पूर्णांकrs = (gic_shared_पूर्णांकrs + 1) * 8;

	अगर (cpu_has_veic) अणु
		/* Always use vector 1 in EIC mode */
		gic_cpu_pin = 0;
		समयr_cpu_pin = gic_cpu_pin;
		set_vi_handler(gic_cpu_pin + GIC_PIN_TO_VEC_OFFSET,
			       __gic_irq_dispatch);
	पूर्ण अन्यथा अणु
		gic_cpu_pin = cpu_vec - GIC_CPU_PIN_OFFSET;
		irq_set_chained_handler(MIPS_CPU_IRQ_BASE + cpu_vec,
					gic_irq_dispatch);
		/*
		 * With the CMP implementation of SMP (deprecated), other CPUs
		 * are started by the bootloader and put पूर्णांकo a समयr based
		 * रुकोing poll loop. We must not re-route those CPU's local
		 * समयr पूर्णांकerrupts as the रुको inकाष्ठाion will never finish,
		 * so just handle whatever CPU पूर्णांकerrupt it is routed to by
		 * शेष.
		 *
		 * This workaround should be हटाओd when CMP support is
		 * dropped.
		 */
		अगर (IS_ENABLED(CONFIG_MIPS_CMP) &&
		    gic_local_irq_is_routable(GIC_LOCAL_INT_TIMER)) अणु
			समयr_cpu_pin = पढ़ो_gic_vl_समयr_map() & GIC_MAP_PIN_MAP;
			irq_set_chained_handler(MIPS_CPU_IRQ_BASE +
						GIC_CPU_PIN_OFFSET +
						समयr_cpu_pin,
						gic_irq_dispatch);
		पूर्ण अन्यथा अणु
			समयr_cpu_pin = gic_cpu_pin;
		पूर्ण
	पूर्ण

	gic_irq_करोमुख्य = irq_करोमुख्य_add_simple(node, GIC_NUM_LOCAL_INTRS +
					       gic_shared_पूर्णांकrs, 0,
					       &gic_irq_करोमुख्य_ops, शून्य);
	अगर (!gic_irq_करोमुख्य) अणु
		pr_err("Failed to add IRQ domain");
		वापस -ENXIO;
	पूर्ण

	gic_ipi_करोमुख्य = irq_करोमुख्य_add_hierarchy(gic_irq_करोमुख्य,
						  IRQ_DOMAIN_FLAG_IPI_PER_CPU,
						  GIC_NUM_LOCAL_INTRS + gic_shared_पूर्णांकrs,
						  node, &gic_ipi_करोमुख्य_ops, शून्य);
	अगर (!gic_ipi_करोमुख्य) अणु
		pr_err("Failed to add IPI domain");
		वापस -ENXIO;
	पूर्ण

	irq_करोमुख्य_update_bus_token(gic_ipi_करोमुख्य, DOMAIN_BUS_IPI);

	अगर (node &&
	    !of_property_पढ़ो_u32_array(node, "mti,reserved-ipi-vectors", v, 2)) अणु
		biपंचांगap_set(ipi_resrv, v[0], v[1]);
	पूर्ण अन्यथा अणु
		/*
		 * Reserve 2 पूर्णांकerrupts per possible CPU/VP क्रम use as IPIs,
		 * meeting the requirements of arch/mips SMP.
		 */
		num_ipis = 2 * num_possible_cpus();
		biपंचांगap_set(ipi_resrv, gic_shared_पूर्णांकrs - num_ipis, num_ipis);
	पूर्ण

	biपंचांगap_copy(ipi_available, ipi_resrv, GIC_MAX_INTRS);

	board_bind_eic_पूर्णांकerrupt = &gic_bind_eic_पूर्णांकerrupt;

	/* Setup शेषs */
	क्रम (i = 0; i < gic_shared_पूर्णांकrs; i++) अणु
		change_gic_pol(i, GIC_POL_ACTIVE_HIGH);
		change_gic_trig(i, GIC_TRIG_LEVEL);
		ग_लिखो_gic_rmask(i);
	पूर्ण

	वापस cpuhp_setup_state(CPUHP_AP_IRQ_MIPS_GIC_STARTING,
				 "irqchip/mips/gic:starting",
				 gic_cpu_startup, शून्य);
पूर्ण
IRQCHIP_DECLARE(mips_gic, "mti,gic", gic_of_init);
