<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/irq.c
 *
 *  Generic PXA IRQ handling
 *
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/exception.h>

#समावेश <mach/hardware.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

#घोषणा ICIP			(0x000)
#घोषणा ICMR			(0x004)
#घोषणा ICLR			(0x008)
#घोषणा ICFR			(0x00c)
#घोषणा ICPR			(0x010)
#घोषणा ICCR			(0x014)
#घोषणा ICHP			(0x018)
#घोषणा IPR(i)			(((i) < 32) ? (0x01c + ((i) << 2)) :		\
				((i) < 64) ? (0x0b0 + (((i) - 32) << 2)) :	\
				      (0x144 + (((i) - 64) << 2)))
#घोषणा ICHP_VAL_IRQ		(1 << 31)
#घोषणा ICHP_IRQ(i)		(((i) >> 16) & 0x7fff)
#घोषणा IPR_VALID		(1 << 31)

#घोषणा MAX_INTERNAL_IRQS	128

/*
 * This is क्रम peripheral IRQs पूर्णांकernal to the PXA chip.
 */

अटल व्योम __iomem *pxa_irq_base;
अटल पूर्णांक pxa_पूर्णांकernal_irq_nr;
अटल bool cpu_has_ipr;
अटल काष्ठा irq_करोमुख्य *pxa_irq_करोमुख्य;

अटल अंतरभूत व्योम __iomem *irq_base(पूर्णांक i)
अणु
	अटल अचिन्हित दीर्घ phys_base_offset[] = अणु
		0x0,
		0x9c,
		0x130,
	पूर्ण;

	वापस pxa_irq_base + phys_base_offset[i];
पूर्ण

व्योम pxa_mask_irq(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = irq_data_get_irq_chip_data(d);
	irq_hw_number_t irq = irqd_to_hwirq(d);
	uपूर्णांक32_t icmr = __raw_पढ़ोl(base + ICMR);

	icmr &= ~BIT(irq & 0x1f);
	__raw_ग_लिखोl(icmr, base + ICMR);
पूर्ण

व्योम pxa_unmask_irq(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = irq_data_get_irq_chip_data(d);
	irq_hw_number_t irq = irqd_to_hwirq(d);
	uपूर्णांक32_t icmr = __raw_पढ़ोl(base + ICMR);

	icmr |= BIT(irq & 0x1f);
	__raw_ग_लिखोl(icmr, base + ICMR);
पूर्ण

अटल काष्ठा irq_chip pxa_पूर्णांकernal_irq_chip = अणु
	.name		= "SC",
	.irq_ack	= pxa_mask_irq,
	.irq_mask	= pxa_mask_irq,
	.irq_unmask	= pxa_unmask_irq,
पूर्ण;

यंत्रlinkage व्योम __exception_irq_entry icip_handle_irq(काष्ठा pt_regs *regs)
अणु
	uपूर्णांक32_t icip, icmr, mask;

	करो अणु
		icip = __raw_पढ़ोl(pxa_irq_base + ICIP);
		icmr = __raw_पढ़ोl(pxa_irq_base + ICMR);
		mask = icip & icmr;

		अगर (mask == 0)
			अवरोध;

		handle_IRQ(PXA_IRQ(fls(mask) - 1), regs);
	पूर्ण जबतक (1);
पूर्ण

यंत्रlinkage व्योम __exception_irq_entry ichp_handle_irq(काष्ठा pt_regs *regs)
अणु
	uपूर्णांक32_t ichp;

	करो अणु
		__यंत्र__ __अस्थिर__("mrc p6, 0, %0, c5, c0, 0\n": "=r"(ichp));

		अगर ((ichp & ICHP_VAL_IRQ) == 0)
			अवरोध;

		handle_IRQ(PXA_IRQ(ICHP_IRQ(ichp)), regs);
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक pxa_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
		       irq_hw_number_t hw)
अणु
	व्योम __iomem *base = irq_base(hw / 32);

	/* initialize पूर्णांकerrupt priority */
	अगर (cpu_has_ipr)
		__raw_ग_लिखोl(hw | IPR_VALID, pxa_irq_base + IPR(hw));

	irq_set_chip_and_handler(virq, &pxa_पूर्णांकernal_irq_chip,
				 handle_level_irq);
	irq_set_chip_data(virq, base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pxa_irq_ops = अणु
	.map    = pxa_irq_map,
	.xlate  = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल __init व्योम
pxa_init_irq_common(काष्ठा device_node *node, पूर्णांक irq_nr,
		    पूर्णांक (*fn)(काष्ठा irq_data *, अचिन्हित पूर्णांक))
अणु
	पूर्णांक n;

	pxa_पूर्णांकernal_irq_nr = irq_nr;
	pxa_irq_करोमुख्य = irq_करोमुख्य_add_legacy(node, irq_nr,
					       PXA_IRQ(0), 0,
					       &pxa_irq_ops, शून्य);
	अगर (!pxa_irq_करोमुख्य)
		panic("Unable to add PXA IRQ domain\n");
	irq_set_शेष_host(pxa_irq_करोमुख्य);

	क्रम (n = 0; n < irq_nr; n += 32) अणु
		व्योम __iomem *base = irq_base(n >> 5);

		__raw_ग_लिखोl(0, base + ICMR);	/* disable all IRQs */
		__raw_ग_लिखोl(0, base + ICLR);	/* all IRQs are IRQ, not FIQ */
	पूर्ण
	/* only unmasked पूर्णांकerrupts kick us out of idle */
	__raw_ग_लिखोl(1, irq_base(0) + ICCR);

	pxa_पूर्णांकernal_irq_chip.irq_set_wake = fn;
पूर्ण

व्योम __init pxa_init_irq(पूर्णांक irq_nr, पूर्णांक (*fn)(काष्ठा irq_data *, अचिन्हित पूर्णांक))
अणु
	BUG_ON(irq_nr > MAX_INTERNAL_IRQS);

	pxa_irq_base = io_p2v(0x40d00000);
	cpu_has_ipr = !cpu_is_pxa25x();
	pxa_init_irq_common(शून्य, irq_nr, fn);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल अचिन्हित दीर्घ saved_icmr[MAX_INTERNAL_IRQS/32];
अटल अचिन्हित दीर्घ saved_ipr[MAX_INTERNAL_IRQS];

अटल पूर्णांक pxa_irq_suspend(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DIV_ROUND_UP(pxa_पूर्णांकernal_irq_nr, 32); i++) अणु
		व्योम __iomem *base = irq_base(i);

		saved_icmr[i] = __raw_पढ़ोl(base + ICMR);
		__raw_ग_लिखोl(0, base + ICMR);
	पूर्ण

	अगर (cpu_has_ipr) अणु
		क्रम (i = 0; i < pxa_पूर्णांकernal_irq_nr; i++)
			saved_ipr[i] = __raw_पढ़ोl(pxa_irq_base + IPR(i));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pxa_irq_resume(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DIV_ROUND_UP(pxa_पूर्णांकernal_irq_nr, 32); i++) अणु
		व्योम __iomem *base = irq_base(i);

		__raw_ग_लिखोl(saved_icmr[i], base + ICMR);
		__raw_ग_लिखोl(0, base + ICLR);
	पूर्ण

	अगर (cpu_has_ipr)
		क्रम (i = 0; i < pxa_पूर्णांकernal_irq_nr; i++)
			__raw_ग_लिखोl(saved_ipr[i], pxa_irq_base + IPR(i));

	__raw_ग_लिखोl(1, pxa_irq_base + ICCR);
पूर्ण
#अन्यथा
#घोषणा pxa_irq_suspend		शून्य
#घोषणा pxa_irq_resume		शून्य
#पूर्ण_अगर

काष्ठा syscore_ops pxa_irq_syscore_ops = अणु
	.suspend	= pxa_irq_suspend,
	.resume		= pxa_irq_resume,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id पूर्णांकc_ids[] __initस्थिर = अणु
	अणु .compatible = "marvell,pxa-intc", पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम __init pxa_dt_irq_init(पूर्णांक (*fn)(काष्ठा irq_data *, अचिन्हित पूर्णांक))
अणु
	काष्ठा device_node *node;
	काष्ठा resource res;
	पूर्णांक ret;

	node = of_find_matching_node(शून्य, पूर्णांकc_ids);
	अगर (!node) अणु
		pr_err("Failed to find interrupt controller in arch-pxa\n");
		वापस;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "marvell,intc-nr-irqs",
				   &pxa_पूर्णांकernal_irq_nr);
	अगर (ret) अणु
		pr_err("Not found marvell,intc-nr-irqs property\n");
		वापस;
	पूर्ण

	ret = of_address_to_resource(node, 0, &res);
	अगर (ret < 0) अणु
		pr_err("No registers defined for node\n");
		वापस;
	पूर्ण
	pxa_irq_base = io_p2v(res.start);

	अगर (of_find_property(node, "marvell,intc-priority", शून्य))
		cpu_has_ipr = 1;

	ret = irq_alloc_descs(-1, 0, pxa_पूर्णांकernal_irq_nr, 0);
	अगर (ret < 0) अणु
		pr_err("Failed to allocate IRQ numbers\n");
		वापस;
	पूर्ण

	pxa_init_irq_common(node, pxa_पूर्णांकernal_irq_nr, fn);
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */
