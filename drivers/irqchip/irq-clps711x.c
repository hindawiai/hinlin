<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  CLPS711X IRQ driver
 *
 *  Copyright (C) 2013 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/irq.h>

#घोषणा CLPS711X_INTSR1	(0x0240)
#घोषणा CLPS711X_INTMR1	(0x0280)
#घोषणा CLPS711X_BLEOI	(0x0600)
#घोषणा CLPS711X_MCEOI	(0x0640)
#घोषणा CLPS711X_TEOI	(0x0680)
#घोषणा CLPS711X_TC1EOI	(0x06c0)
#घोषणा CLPS711X_TC2EOI	(0x0700)
#घोषणा CLPS711X_RTCEOI	(0x0740)
#घोषणा CLPS711X_UMSEOI	(0x0780)
#घोषणा CLPS711X_COEOI	(0x07c0)
#घोषणा CLPS711X_INTSR2	(0x1240)
#घोषणा CLPS711X_INTMR2	(0x1280)
#घोषणा CLPS711X_SRXखातापूर्ण	(0x1600)
#घोषणा CLPS711X_KBDEOI	(0x1700)
#घोषणा CLPS711X_INTSR3	(0x2240)
#घोषणा CLPS711X_INTMR3	(0x2280)

अटल स्थिर काष्ठा अणु
#घोषणा CLPS711X_FLAG_EN	(1 << 0)
#घोषणा CLPS711X_FLAG_FIQ	(1 << 1)
	अचिन्हित पूर्णांक	flags;
	phys_addr_t	eoi;
पूर्ण clps711x_irqs[] = अणु
	[1]	= अणु CLPS711X_FLAG_FIQ, CLPS711X_BLEOI, पूर्ण,
	[3]	= अणु CLPS711X_FLAG_FIQ, CLPS711X_MCEOI, पूर्ण,
	[4]	= अणु CLPS711X_FLAG_EN, CLPS711X_COEOI, पूर्ण,
	[5]	= अणु CLPS711X_FLAG_EN, पूर्ण,
	[6]	= अणु CLPS711X_FLAG_EN, पूर्ण,
	[7]	= अणु CLPS711X_FLAG_EN, पूर्ण,
	[8]	= अणु CLPS711X_FLAG_EN, CLPS711X_TC1EOI, पूर्ण,
	[9]	= अणु CLPS711X_FLAG_EN, CLPS711X_TC2EOI, पूर्ण,
	[10]	= अणु CLPS711X_FLAG_EN, CLPS711X_RTCEOI, पूर्ण,
	[11]	= अणु CLPS711X_FLAG_EN, CLPS711X_TEOI, पूर्ण,
	[12]	= अणु CLPS711X_FLAG_EN, पूर्ण,
	[13]	= अणु CLPS711X_FLAG_EN, पूर्ण,
	[14]	= अणु CLPS711X_FLAG_EN, CLPS711X_UMSEOI, पूर्ण,
	[15]	= अणु CLPS711X_FLAG_EN, CLPS711X_SRXखातापूर्ण, पूर्ण,
	[16]	= अणु CLPS711X_FLAG_EN, CLPS711X_KBDEOI, पूर्ण,
	[17]	= अणु CLPS711X_FLAG_EN, पूर्ण,
	[18]	= अणु CLPS711X_FLAG_EN, पूर्ण,
	[28]	= अणु CLPS711X_FLAG_EN, पूर्ण,
	[29]	= अणु CLPS711X_FLAG_EN, पूर्ण,
	[32]	= अणु CLPS711X_FLAG_FIQ, पूर्ण,
पूर्ण;

अटल काष्ठा अणु
	व्योम __iomem		*base;
	व्योम __iomem		*पूर्णांकmr[3];
	व्योम __iomem		*पूर्णांकsr[3];
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा irq_करोमुख्य_ops	ops;
पूर्ण *clps711x_पूर्णांकc;

अटल यंत्रlinkage व्योम __exception_irq_entry clps711x_irqh(काष्ठा pt_regs *regs)
अणु
	u32 irqstat;

	करो अणु
		irqstat = पढ़ोw_relaxed(clps711x_पूर्णांकc->पूर्णांकmr[0]) &
			  पढ़ोw_relaxed(clps711x_पूर्णांकc->पूर्णांकsr[0]);
		अगर (irqstat)
			handle_करोमुख्य_irq(clps711x_पूर्णांकc->करोमुख्य,
					  fls(irqstat) - 1, regs);

		irqstat = पढ़ोw_relaxed(clps711x_पूर्णांकc->पूर्णांकmr[1]) &
			  पढ़ोw_relaxed(clps711x_पूर्णांकc->पूर्णांकsr[1]);
		अगर (irqstat)
			handle_करोमुख्य_irq(clps711x_पूर्णांकc->करोमुख्य,
					  fls(irqstat) - 1 + 16, regs);
	पूर्ण जबतक (irqstat);
पूर्ण

अटल व्योम clps711x_पूर्णांकc_eoi(काष्ठा irq_data *d)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	ग_लिखोl_relaxed(0, clps711x_पूर्णांकc->base + clps711x_irqs[hwirq].eoi);
पूर्ण

अटल व्योम clps711x_पूर्णांकc_mask(काष्ठा irq_data *d)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	व्योम __iomem *पूर्णांकmr = clps711x_पूर्णांकc->पूर्णांकmr[hwirq / 16];
	u32 पंचांगp;

	पंचांगp = पढ़ोl_relaxed(पूर्णांकmr);
	पंचांगp &= ~(1 << (hwirq % 16));
	ग_लिखोl_relaxed(पंचांगp, पूर्णांकmr);
पूर्ण

अटल व्योम clps711x_पूर्णांकc_unmask(काष्ठा irq_data *d)
अणु
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	व्योम __iomem *पूर्णांकmr = clps711x_पूर्णांकc->पूर्णांकmr[hwirq / 16];
	u32 पंचांगp;

	पंचांगp = पढ़ोl_relaxed(पूर्णांकmr);
	पंचांगp |= 1 << (hwirq % 16);
	ग_लिखोl_relaxed(पंचांगp, पूर्णांकmr);
पूर्ण

अटल काष्ठा irq_chip clps711x_पूर्णांकc_chip = अणु
	.name		= "clps711x-intc",
	.irq_eoi	= clps711x_पूर्णांकc_eoi,
	.irq_mask	= clps711x_पूर्णांकc_mask,
	.irq_unmask	= clps711x_पूर्णांकc_unmask,
पूर्ण;

अटल पूर्णांक __init clps711x_पूर्णांकc_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
					irq_hw_number_t hw)
अणु
	irq_flow_handler_t handler = handle_level_irq;
	अचिन्हित पूर्णांक flags = 0;

	अगर (!clps711x_irqs[hw].flags)
		वापस 0;

	अगर (clps711x_irqs[hw].flags & CLPS711X_FLAG_FIQ) अणु
		handler = handle_bad_irq;
		flags |= IRQ_NOAUTOEN;
	पूर्ण अन्यथा अगर (clps711x_irqs[hw].eoi) अणु
		handler = handle_fasteoi_irq;
	पूर्ण

	/* Clear करोwn pending पूर्णांकerrupt */
	अगर (clps711x_irqs[hw].eoi)
		ग_लिखोl_relaxed(0, clps711x_पूर्णांकc->base + clps711x_irqs[hw].eoi);

	irq_set_chip_and_handler(virq, &clps711x_पूर्णांकc_chip, handler);
	irq_modअगरy_status(virq, IRQ_NOPROBE, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __init _clps711x_पूर्णांकc_init(काष्ठा device_node *np,
				      phys_addr_t base, resource_माप_प्रकार size)
अणु
	पूर्णांक err;

	clps711x_पूर्णांकc = kzalloc(माप(*clps711x_पूर्णांकc), GFP_KERNEL);
	अगर (!clps711x_पूर्णांकc)
		वापस -ENOMEM;

	clps711x_पूर्णांकc->base = ioremap(base, size);
	अगर (!clps711x_पूर्णांकc->base) अणु
		err = -ENOMEM;
		जाओ out_kमुक्त;
	पूर्ण

	clps711x_पूर्णांकc->पूर्णांकsr[0] = clps711x_पूर्णांकc->base + CLPS711X_INTSR1;
	clps711x_पूर्णांकc->पूर्णांकmr[0] = clps711x_पूर्णांकc->base + CLPS711X_INTMR1;
	clps711x_पूर्णांकc->पूर्णांकsr[1] = clps711x_पूर्णांकc->base + CLPS711X_INTSR2;
	clps711x_पूर्णांकc->पूर्णांकmr[1] = clps711x_पूर्णांकc->base + CLPS711X_INTMR2;
	clps711x_पूर्णांकc->पूर्णांकsr[2] = clps711x_पूर्णांकc->base + CLPS711X_INTSR3;
	clps711x_पूर्णांकc->पूर्णांकmr[2] = clps711x_पूर्णांकc->base + CLPS711X_INTMR3;

	/* Mask all पूर्णांकerrupts */
	ग_लिखोl_relaxed(0, clps711x_पूर्णांकc->पूर्णांकmr[0]);
	ग_लिखोl_relaxed(0, clps711x_पूर्णांकc->पूर्णांकmr[1]);
	ग_लिखोl_relaxed(0, clps711x_पूर्णांकc->पूर्णांकmr[2]);

	err = irq_alloc_descs(-1, 0, ARRAY_SIZE(clps711x_irqs), numa_node_id());
	अगर (err < 0)
		जाओ out_iounmap;

	clps711x_पूर्णांकc->ops.map = clps711x_पूर्णांकc_irq_map;
	clps711x_पूर्णांकc->ops.xlate = irq_करोमुख्य_xlate_onecell;
	clps711x_पूर्णांकc->करोमुख्य =
		irq_करोमुख्य_add_legacy(np, ARRAY_SIZE(clps711x_irqs),
				      0, 0, &clps711x_पूर्णांकc->ops, शून्य);
	अगर (!clps711x_पूर्णांकc->करोमुख्य) अणु
		err = -ENOMEM;
		जाओ out_irqमुक्त;
	पूर्ण

	irq_set_शेष_host(clps711x_पूर्णांकc->करोमुख्य);
	set_handle_irq(clps711x_irqh);

#अगर_घोषित CONFIG_FIQ
	init_FIQ(0);
#पूर्ण_अगर

	वापस 0;

out_irqमुक्त:
	irq_मुक्त_descs(0, ARRAY_SIZE(clps711x_irqs));

out_iounmap:
	iounmap(clps711x_पूर्णांकc->base);

out_kमुक्त:
	kमुक्त(clps711x_पूर्णांकc);

	वापस err;
पूर्ण

व्योम __init clps711x_पूर्णांकc_init(phys_addr_t base, resource_माप_प्रकार size)
अणु
	BUG_ON(_clps711x_पूर्णांकc_init(शून्य, base, size));
पूर्ण

#अगर_घोषित CONFIG_IRQCHIP
अटल पूर्णांक __init clps711x_पूर्णांकc_init_dt(काष्ठा device_node *np,
					काष्ठा device_node *parent)
अणु
	काष्ठा resource res;
	पूर्णांक err;

	err = of_address_to_resource(np, 0, &res);
	अगर (err)
		वापस err;

	वापस _clps711x_पूर्णांकc_init(np, res.start, resource_size(&res));
पूर्ण
IRQCHIP_DECLARE(clps711x, "cirrus,ep7209-intc", clps711x_पूर्णांकc_init_dt);
#पूर्ण_अगर
