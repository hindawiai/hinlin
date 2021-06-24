<शैली गुरु>
/*
 * Xtensa MX पूर्णांकerrupt distributor
 *
 * Copyright (C) 2002 - 2013 Tensilica, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/mxregs.h>

#घोषणा HW_IRQ_IPI_COUNT 2
#घोषणा HW_IRQ_MX_BASE 2
#घोषणा HW_IRQ_EXTERN_BASE 3

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, cached_irq_mask);

अटल पूर्णांक xtensa_mx_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		irq_hw_number_t hw)
अणु
	अगर (hw < HW_IRQ_IPI_COUNT) अणु
		काष्ठा irq_chip *irq_chip = d->host_data;
		irq_set_chip_and_handler_name(irq, irq_chip,
				handle_percpu_irq, "ipi");
		irq_set_status_flags(irq, IRQ_LEVEL);
		वापस 0;
	पूर्ण
	irqd_set_single_target(irq_desc_get_irq_data(irq_to_desc(irq)));
	वापस xtensa_irq_map(d, irq, hw);
पूर्ण

/*
 * Device Tree IRQ specअगरier translation function which works with one or
 * two cell bindings. First cell value maps directly to the hwirq number.
 * Second cell अगर present specअगरies whether hwirq number is बाह्यal (1) or
 * पूर्णांकernal (0).
 */
अटल पूर्णांक xtensa_mx_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
		काष्ठा device_node *ctrlr,
		स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
		अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	वापस xtensa_irq_करोमुख्य_xlate(पूर्णांकspec, पूर्णांकsize,
			पूर्णांकspec[0], पूर्णांकspec[0] + HW_IRQ_EXTERN_BASE,
			out_hwirq, out_type);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops xtensa_mx_irq_करोमुख्य_ops = अणु
	.xlate = xtensa_mx_irq_करोमुख्य_xlate,
	.map = xtensa_mx_irq_map,
पूर्ण;

व्योम secondary_init_irq(व्योम)
अणु
	__this_cpu_ग_लिखो(cached_irq_mask,
			XCHAL_INTTYPE_MASK_EXTERN_EDGE |
			XCHAL_INTTYPE_MASK_EXTERN_LEVEL);
	xtensa_set_sr(XCHAL_INTTYPE_MASK_EXTERN_EDGE |
			XCHAL_INTTYPE_MASK_EXTERN_LEVEL, पूर्णांकenable);
पूर्ण

अटल व्योम xtensa_mx_irq_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1u << d->hwirq;

	अगर (mask & (XCHAL_INTTYPE_MASK_EXTERN_EDGE |
		    XCHAL_INTTYPE_MASK_EXTERN_LEVEL)) अणु
		अचिन्हित पूर्णांक ext_irq = xtensa_get_ext_irq_no(d->hwirq);

		अगर (ext_irq >= HW_IRQ_MX_BASE) अणु
			set_er(1u << (ext_irq - HW_IRQ_MX_BASE), MIENG);
			वापस;
		पूर्ण
	पूर्ण
	mask = __this_cpu_पढ़ो(cached_irq_mask) & ~mask;
	__this_cpu_ग_लिखो(cached_irq_mask, mask);
	xtensa_set_sr(mask, पूर्णांकenable);
पूर्ण

अटल व्योम xtensa_mx_irq_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1u << d->hwirq;

	अगर (mask & (XCHAL_INTTYPE_MASK_EXTERN_EDGE |
		    XCHAL_INTTYPE_MASK_EXTERN_LEVEL)) अणु
		अचिन्हित पूर्णांक ext_irq = xtensa_get_ext_irq_no(d->hwirq);

		अगर (ext_irq >= HW_IRQ_MX_BASE) अणु
			set_er(1u << (ext_irq - HW_IRQ_MX_BASE), MIENGSET);
			वापस;
		पूर्ण
	पूर्ण
	mask |= __this_cpu_पढ़ो(cached_irq_mask);
	__this_cpu_ग_लिखो(cached_irq_mask, mask);
	xtensa_set_sr(mask, पूर्णांकenable);
पूर्ण

अटल व्योम xtensa_mx_irq_enable(काष्ठा irq_data *d)
अणु
	xtensa_mx_irq_unmask(d);
पूर्ण

अटल व्योम xtensa_mx_irq_disable(काष्ठा irq_data *d)
अणु
	xtensa_mx_irq_mask(d);
पूर्ण

अटल व्योम xtensa_mx_irq_ack(काष्ठा irq_data *d)
अणु
	xtensa_set_sr(1 << d->hwirq, पूर्णांकclear);
पूर्ण

अटल पूर्णांक xtensa_mx_irq_retrigger(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1u << d->hwirq;

	अगर (WARN_ON(mask & ~XCHAL_INTTYPE_MASK_SOFTWARE))
		वापस 0;
	xtensa_set_sr(mask, पूर्णांकset);
	वापस 1;
पूर्ण

अटल पूर्णांक xtensa_mx_irq_set_affinity(काष्ठा irq_data *d,
		स्थिर काष्ठा cpumask *dest, bool क्रमce)
अणु
	पूर्णांक cpu = cpumask_any_and(dest, cpu_online_mask);
	अचिन्हित mask = 1u << cpu;

	set_er(mask, MIROUT(d->hwirq - HW_IRQ_MX_BASE));
	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	वापस 0;

पूर्ण

अटल काष्ठा irq_chip xtensa_mx_irq_chip = अणु
	.name		= "xtensa-mx",
	.irq_enable	= xtensa_mx_irq_enable,
	.irq_disable	= xtensa_mx_irq_disable,
	.irq_mask	= xtensa_mx_irq_mask,
	.irq_unmask	= xtensa_mx_irq_unmask,
	.irq_ack	= xtensa_mx_irq_ack,
	.irq_retrigger	= xtensa_mx_irq_retrigger,
	.irq_set_affinity = xtensa_mx_irq_set_affinity,
पूर्ण;

पूर्णांक __init xtensa_mx_init_legacy(काष्ठा device_node *पूर्णांकerrupt_parent)
अणु
	काष्ठा irq_करोमुख्य *root_करोमुख्य =
		irq_करोमुख्य_add_legacy(शून्य, NR_IRQS - 1, 1, 0,
				&xtensa_mx_irq_करोमुख्य_ops,
				&xtensa_mx_irq_chip);
	irq_set_शेष_host(root_करोमुख्य);
	secondary_init_irq();
	वापस 0;
पूर्ण

अटल पूर्णांक __init xtensa_mx_init(काष्ठा device_node *np,
		काष्ठा device_node *पूर्णांकerrupt_parent)
अणु
	काष्ठा irq_करोमुख्य *root_करोमुख्य =
		irq_करोमुख्य_add_linear(np, NR_IRQS, &xtensa_mx_irq_करोमुख्य_ops,
				&xtensa_mx_irq_chip);
	irq_set_शेष_host(root_करोमुख्य);
	secondary_init_irq();
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(xtensa_mx_irq_chip, "cdns,xtensa-mx", xtensa_mx_init);
