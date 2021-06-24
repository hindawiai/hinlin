<शैली गुरु>
/*
 * Xtensa built-in पूर्णांकerrupt controller
 *
 * Copyright (C) 2002 - 2013 Tensilica, Inc.
 * Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Chris Zankel <chris@zankel.net>
 * Kevin Chea
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>

अचिन्हित पूर्णांक cached_irq_mask;

/*
 * Device Tree IRQ specअगरier translation function which works with one or
 * two cell bindings. First cell value maps directly to the hwirq number.
 * Second cell अगर present specअगरies whether hwirq number is बाह्यal (1) or
 * पूर्णांकernal (0).
 */
अटल पूर्णांक xtensa_pic_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
		काष्ठा device_node *ctrlr,
		स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
		अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	वापस xtensa_irq_करोमुख्य_xlate(पूर्णांकspec, पूर्णांकsize,
			पूर्णांकspec[0], पूर्णांकspec[0],
			out_hwirq, out_type);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops xtensa_irq_करोमुख्य_ops = अणु
	.xlate = xtensa_pic_irq_करोमुख्य_xlate,
	.map = xtensa_irq_map,
पूर्ण;

अटल व्योम xtensa_irq_mask(काष्ठा irq_data *d)
अणु
	cached_irq_mask &= ~(1 << d->hwirq);
	xtensa_set_sr(cached_irq_mask, पूर्णांकenable);
पूर्ण

अटल व्योम xtensa_irq_unmask(काष्ठा irq_data *d)
अणु
	cached_irq_mask |= 1 << d->hwirq;
	xtensa_set_sr(cached_irq_mask, पूर्णांकenable);
पूर्ण

अटल व्योम xtensa_irq_enable(काष्ठा irq_data *d)
अणु
	xtensa_irq_unmask(d);
पूर्ण

अटल व्योम xtensa_irq_disable(काष्ठा irq_data *d)
अणु
	xtensa_irq_mask(d);
पूर्ण

अटल व्योम xtensa_irq_ack(काष्ठा irq_data *d)
अणु
	xtensa_set_sr(1 << d->hwirq, पूर्णांकclear);
पूर्ण

अटल पूर्णांक xtensa_irq_retrigger(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1u << d->hwirq;

	अगर (WARN_ON(mask & ~XCHAL_INTTYPE_MASK_SOFTWARE))
		वापस 0;
	xtensa_set_sr(mask, पूर्णांकset);
	वापस 1;
पूर्ण

अटल काष्ठा irq_chip xtensa_irq_chip = अणु
	.name		= "xtensa",
	.irq_enable	= xtensa_irq_enable,
	.irq_disable	= xtensa_irq_disable,
	.irq_mask	= xtensa_irq_mask,
	.irq_unmask	= xtensa_irq_unmask,
	.irq_ack	= xtensa_irq_ack,
	.irq_retrigger	= xtensa_irq_retrigger,
पूर्ण;

पूर्णांक __init xtensa_pic_init_legacy(काष्ठा device_node *पूर्णांकerrupt_parent)
अणु
	काष्ठा irq_करोमुख्य *root_करोमुख्य =
		irq_करोमुख्य_add_legacy(शून्य, NR_IRQS - 1, 1, 0,
				&xtensa_irq_करोमुख्य_ops, &xtensa_irq_chip);
	irq_set_शेष_host(root_करोमुख्य);
	वापस 0;
पूर्ण

अटल पूर्णांक __init xtensa_pic_init(काष्ठा device_node *np,
		काष्ठा device_node *पूर्णांकerrupt_parent)
अणु
	काष्ठा irq_करोमुख्य *root_करोमुख्य =
		irq_करोमुख्य_add_linear(np, NR_IRQS, &xtensa_irq_करोमुख्य_ops,
				&xtensa_irq_chip);
	irq_set_शेष_host(root_करोमुख्य);
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(xtensa_irq_chip, "cdns,xtensa-pic", xtensa_pic_init);
