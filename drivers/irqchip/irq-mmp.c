<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/irq.c
 *
 *  Generic IRQ handling, GPIO IRQ demultiplexing, etc.
 *  Copyright (C) 2008 - 2012 Marvell Technology Group Ltd.
 *
 *  Author:	Bin Yang <bin.yang@marvell.com>
 *              Haojian Zhuang <haojian.zhuang@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/hardirq.h>

#घोषणा MAX_ICU_NR		16

#घोषणा PJ1_INT_SEL		0x10c
#घोषणा PJ4_INT_SEL		0x104

/* bit fields in PJ1_INT_SEL and PJ4_INT_SEL */
#घोषणा SEL_INT_PENDING		(1 << 6)
#घोषणा SEL_INT_NUM_MASK	0x3f

#घोषणा MMP2_ICU_INT_ROUTE_PJ4_IRQ	(1 << 5)
#घोषणा MMP2_ICU_INT_ROUTE_PJ4_FIQ	(1 << 6)

काष्ठा icu_chip_data अणु
	पूर्णांक			nr_irqs;
	अचिन्हित पूर्णांक		virq_base;
	अचिन्हित पूर्णांक		cascade_irq;
	व्योम __iomem		*reg_status;
	व्योम __iomem		*reg_mask;
	अचिन्हित पूर्णांक		conf_enable;
	अचिन्हित पूर्णांक		conf_disable;
	अचिन्हित पूर्णांक		conf_mask;
	अचिन्हित पूर्णांक		conf2_mask;
	अचिन्हित पूर्णांक		clr_mfp_irq_base;
	अचिन्हित पूर्णांक		clr_mfp_hwirq;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
पूर्ण;

काष्ठा mmp_पूर्णांकc_conf अणु
	अचिन्हित पूर्णांक	conf_enable;
	अचिन्हित पूर्णांक	conf_disable;
	अचिन्हित पूर्णांक	conf_mask;
	अचिन्हित पूर्णांक	conf2_mask;
पूर्ण;

अटल व्योम __iomem *mmp_icu_base;
अटल व्योम __iomem *mmp_icu2_base;
अटल काष्ठा icu_chip_data icu_data[MAX_ICU_NR];
अटल पूर्णांक max_icu_nr;

बाह्य व्योम mmp2_clear_pmic_पूर्णांक(व्योम);

अटल व्योम icu_mask_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा icu_chip_data *data = (काष्ठा icu_chip_data *)करोमुख्य->host_data;
	पूर्णांक hwirq;
	u32 r;

	hwirq = d->irq - data->virq_base;
	अगर (data == &icu_data[0]) अणु
		r = पढ़ोl_relaxed(mmp_icu_base + (hwirq << 2));
		r &= ~data->conf_mask;
		r |= data->conf_disable;
		ग_लिखोl_relaxed(r, mmp_icu_base + (hwirq << 2));
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_CPU_MMP2
		अगर ((data->virq_base == data->clr_mfp_irq_base)
			&& (hwirq == data->clr_mfp_hwirq))
			mmp2_clear_pmic_पूर्णांक();
#पूर्ण_अगर
		r = पढ़ोl_relaxed(data->reg_mask) | (1 << hwirq);
		ग_लिखोl_relaxed(r, data->reg_mask);
	पूर्ण
पूर्ण

अटल व्योम icu_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा icu_chip_data *data = (काष्ठा icu_chip_data *)करोमुख्य->host_data;
	पूर्णांक hwirq;
	u32 r;

	hwirq = d->irq - data->virq_base;
	अगर (data == &icu_data[0]) अणु
		r = पढ़ोl_relaxed(mmp_icu_base + (hwirq << 2));
		r &= ~data->conf_mask;
		r |= data->conf_disable;
		ग_लिखोl_relaxed(r, mmp_icu_base + (hwirq << 2));

		अगर (data->conf2_mask) अणु
			/*
			 * ICU1 (above) only controls PJ4 MP1; अगर using SMP,
			 * we need to also mask the MP2 and MM cores via ICU2.
			 */
			r = पढ़ोl_relaxed(mmp_icu2_base + (hwirq << 2));
			r &= ~data->conf2_mask;
			ग_लिखोl_relaxed(r, mmp_icu2_base + (hwirq << 2));
		पूर्ण
	पूर्ण अन्यथा अणु
		r = पढ़ोl_relaxed(data->reg_mask) | (1 << hwirq);
		ग_लिखोl_relaxed(r, data->reg_mask);
	पूर्ण
पूर्ण

अटल व्योम icu_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = d->करोमुख्य;
	काष्ठा icu_chip_data *data = (काष्ठा icu_chip_data *)करोमुख्य->host_data;
	पूर्णांक hwirq;
	u32 r;

	hwirq = d->irq - data->virq_base;
	अगर (data == &icu_data[0]) अणु
		r = पढ़ोl_relaxed(mmp_icu_base + (hwirq << 2));
		r &= ~data->conf_mask;
		r |= data->conf_enable;
		ग_लिखोl_relaxed(r, mmp_icu_base + (hwirq << 2));
	पूर्ण अन्यथा अणु
		r = पढ़ोl_relaxed(data->reg_mask) & ~(1 << hwirq);
		ग_लिखोl_relaxed(r, data->reg_mask);
	पूर्ण
पूर्ण

काष्ठा irq_chip icu_irq_chip = अणु
	.name		= "icu_irq",
	.irq_mask	= icu_mask_irq,
	.irq_mask_ack	= icu_mask_ack_irq,
	.irq_unmask	= icu_unmask_irq,
पूर्ण;

अटल व्योम icu_mux_irq_demux(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा icu_chip_data *data;
	पूर्णांक i;
	अचिन्हित दीर्घ mask, status, n;

	chained_irq_enter(chip, desc);

	क्रम (i = 1; i < max_icu_nr; i++) अणु
		अगर (irq == icu_data[i].cascade_irq) अणु
			करोमुख्य = icu_data[i].करोमुख्य;
			data = (काष्ठा icu_chip_data *)करोमुख्य->host_data;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i >= max_icu_nr) अणु
		pr_err("Spurious irq %d in MMP INTC\n", irq);
		जाओ out;
	पूर्ण

	mask = पढ़ोl_relaxed(data->reg_mask);
	जबतक (1) अणु
		status = पढ़ोl_relaxed(data->reg_status) & ~mask;
		अगर (status == 0)
			अवरोध;
		क्रम_each_set_bit(n, &status, BITS_PER_LONG) अणु
			generic_handle_irq(icu_data[i].virq_base + n);
		पूर्ण
	पूर्ण

out:
	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक mmp_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			      irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(irq, &icu_irq_chip, handle_level_irq);
	वापस 0;
पूर्ण

अटल पूर्णांक mmp_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *node,
				स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				अचिन्हित दीर्घ *out_hwirq,
				अचिन्हित पूर्णांक *out_type)
अणु
	*out_hwirq = पूर्णांकspec[0];
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mmp_irq_करोमुख्य_ops = अणु
	.map		= mmp_irq_करोमुख्य_map,
	.xlate		= mmp_irq_करोमुख्य_xlate,
पूर्ण;

अटल स्थिर काष्ठा mmp_पूर्णांकc_conf mmp_conf = अणु
	.conf_enable	= 0x51,
	.conf_disable	= 0x0,
	.conf_mask	= 0x7f,
पूर्ण;

अटल स्थिर काष्ठा mmp_पूर्णांकc_conf mmp2_conf = अणु
	.conf_enable	= 0x20,
	.conf_disable	= 0x0,
	.conf_mask	= MMP2_ICU_INT_ROUTE_PJ4_IRQ |
			  MMP2_ICU_INT_ROUTE_PJ4_FIQ,
पूर्ण;

अटल काष्ठा mmp_पूर्णांकc_conf mmp3_conf = अणु
	.conf_enable	= 0x20,
	.conf_disable	= 0x0,
	.conf_mask	= MMP2_ICU_INT_ROUTE_PJ4_IRQ |
			  MMP2_ICU_INT_ROUTE_PJ4_FIQ,
	.conf2_mask	= 0xf0,
पूर्ण;

अटल व्योम __exception_irq_entry mmp_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक hwirq;

	hwirq = पढ़ोl_relaxed(mmp_icu_base + PJ1_INT_SEL);
	अगर (!(hwirq & SEL_INT_PENDING))
		वापस;
	hwirq &= SEL_INT_NUM_MASK;
	handle_करोमुख्य_irq(icu_data[0].करोमुख्य, hwirq, regs);
पूर्ण

अटल व्योम __exception_irq_entry mmp2_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक hwirq;

	hwirq = पढ़ोl_relaxed(mmp_icu_base + PJ4_INT_SEL);
	अगर (!(hwirq & SEL_INT_PENDING))
		वापस;
	hwirq &= SEL_INT_NUM_MASK;
	handle_करोमुख्य_irq(icu_data[0].करोमुख्य, hwirq, regs);
पूर्ण

/* MMP (ARMv5) */
व्योम __init icu_init_irq(व्योम)
अणु
	पूर्णांक irq;

	max_icu_nr = 1;
	mmp_icu_base = ioremap(0xd4282000, 0x1000);
	icu_data[0].conf_enable = mmp_conf.conf_enable;
	icu_data[0].conf_disable = mmp_conf.conf_disable;
	icu_data[0].conf_mask = mmp_conf.conf_mask;
	icu_data[0].nr_irqs = 64;
	icu_data[0].virq_base = 0;
	icu_data[0].करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, 64, 0, 0,
						   &irq_करोमुख्य_simple_ops,
						   &icu_data[0]);
	क्रम (irq = 0; irq < 64; irq++) अणु
		icu_mask_irq(irq_get_irq_data(irq));
		irq_set_chip_and_handler(irq, &icu_irq_chip, handle_level_irq);
	पूर्ण
	irq_set_शेष_host(icu_data[0].करोमुख्य);
	set_handle_irq(mmp_handle_irq);
पूर्ण

/* MMP2 (ARMv7) */
व्योम __init mmp2_init_icu(व्योम)
अणु
	पूर्णांक irq, end;

	max_icu_nr = 8;
	mmp_icu_base = ioremap(0xd4282000, 0x1000);
	icu_data[0].conf_enable = mmp2_conf.conf_enable;
	icu_data[0].conf_disable = mmp2_conf.conf_disable;
	icu_data[0].conf_mask = mmp2_conf.conf_mask;
	icu_data[0].nr_irqs = 64;
	icu_data[0].virq_base = 0;
	icu_data[0].करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, 64, 0, 0,
						   &irq_करोमुख्य_simple_ops,
						   &icu_data[0]);
	icu_data[1].reg_status = mmp_icu_base + 0x150;
	icu_data[1].reg_mask = mmp_icu_base + 0x168;
	icu_data[1].clr_mfp_irq_base = icu_data[0].virq_base +
				icu_data[0].nr_irqs;
	icu_data[1].clr_mfp_hwirq = 1;		/* offset to IRQ_MMP2_PMIC_BASE */
	icu_data[1].nr_irqs = 2;
	icu_data[1].cascade_irq = 4;
	icu_data[1].virq_base = icu_data[0].virq_base + icu_data[0].nr_irqs;
	icu_data[1].करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, icu_data[1].nr_irqs,
						   icu_data[1].virq_base, 0,
						   &irq_करोमुख्य_simple_ops,
						   &icu_data[1]);
	icu_data[2].reg_status = mmp_icu_base + 0x154;
	icu_data[2].reg_mask = mmp_icu_base + 0x16c;
	icu_data[2].nr_irqs = 2;
	icu_data[2].cascade_irq = 5;
	icu_data[2].virq_base = icu_data[1].virq_base + icu_data[1].nr_irqs;
	icu_data[2].करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, icu_data[2].nr_irqs,
						   icu_data[2].virq_base, 0,
						   &irq_करोमुख्य_simple_ops,
						   &icu_data[2]);
	icu_data[3].reg_status = mmp_icu_base + 0x180;
	icu_data[3].reg_mask = mmp_icu_base + 0x17c;
	icu_data[3].nr_irqs = 3;
	icu_data[3].cascade_irq = 9;
	icu_data[3].virq_base = icu_data[2].virq_base + icu_data[2].nr_irqs;
	icu_data[3].करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, icu_data[3].nr_irqs,
						   icu_data[3].virq_base, 0,
						   &irq_करोमुख्य_simple_ops,
						   &icu_data[3]);
	icu_data[4].reg_status = mmp_icu_base + 0x158;
	icu_data[4].reg_mask = mmp_icu_base + 0x170;
	icu_data[4].nr_irqs = 5;
	icu_data[4].cascade_irq = 17;
	icu_data[4].virq_base = icu_data[3].virq_base + icu_data[3].nr_irqs;
	icu_data[4].करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, icu_data[4].nr_irqs,
						   icu_data[4].virq_base, 0,
						   &irq_करोमुख्य_simple_ops,
						   &icu_data[4]);
	icu_data[5].reg_status = mmp_icu_base + 0x15c;
	icu_data[5].reg_mask = mmp_icu_base + 0x174;
	icu_data[5].nr_irqs = 15;
	icu_data[5].cascade_irq = 35;
	icu_data[5].virq_base = icu_data[4].virq_base + icu_data[4].nr_irqs;
	icu_data[5].करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, icu_data[5].nr_irqs,
						   icu_data[5].virq_base, 0,
						   &irq_करोमुख्य_simple_ops,
						   &icu_data[5]);
	icu_data[6].reg_status = mmp_icu_base + 0x160;
	icu_data[6].reg_mask = mmp_icu_base + 0x178;
	icu_data[6].nr_irqs = 2;
	icu_data[6].cascade_irq = 51;
	icu_data[6].virq_base = icu_data[5].virq_base + icu_data[5].nr_irqs;
	icu_data[6].करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, icu_data[6].nr_irqs,
						   icu_data[6].virq_base, 0,
						   &irq_करोमुख्य_simple_ops,
						   &icu_data[6]);
	icu_data[7].reg_status = mmp_icu_base + 0x188;
	icu_data[7].reg_mask = mmp_icu_base + 0x184;
	icu_data[7].nr_irqs = 2;
	icu_data[7].cascade_irq = 55;
	icu_data[7].virq_base = icu_data[6].virq_base + icu_data[6].nr_irqs;
	icu_data[7].करोमुख्य = irq_करोमुख्य_add_legacy(शून्य, icu_data[7].nr_irqs,
						   icu_data[7].virq_base, 0,
						   &irq_करोमुख्य_simple_ops,
						   &icu_data[7]);
	end = icu_data[7].virq_base + icu_data[7].nr_irqs;
	क्रम (irq = 0; irq < end; irq++) अणु
		icu_mask_irq(irq_get_irq_data(irq));
		अगर (irq == icu_data[1].cascade_irq ||
		    irq == icu_data[2].cascade_irq ||
		    irq == icu_data[3].cascade_irq ||
		    irq == icu_data[4].cascade_irq ||
		    irq == icu_data[5].cascade_irq ||
		    irq == icu_data[6].cascade_irq ||
		    irq == icu_data[7].cascade_irq) अणु
			irq_set_chip(irq, &icu_irq_chip);
			irq_set_chained_handler(irq, icu_mux_irq_demux);
		पूर्ण अन्यथा अणु
			irq_set_chip_and_handler(irq, &icu_irq_chip,
						 handle_level_irq);
		पूर्ण
	पूर्ण
	irq_set_शेष_host(icu_data[0].करोमुख्य);
	set_handle_irq(mmp2_handle_irq);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक __init mmp_init_bases(काष्ठा device_node *node)
अणु
	पूर्णांक ret, nr_irqs, irq, i = 0;

	ret = of_property_पढ़ो_u32(node, "mrvl,intc-nr-irqs", &nr_irqs);
	अगर (ret) अणु
		pr_err("Not found mrvl,intc-nr-irqs property\n");
		वापस ret;
	पूर्ण

	mmp_icu_base = of_iomap(node, 0);
	अगर (!mmp_icu_base) अणु
		pr_err("Failed to get interrupt controller register\n");
		वापस -ENOMEM;
	पूर्ण

	icu_data[0].virq_base = 0;
	icu_data[0].करोमुख्य = irq_करोमुख्य_add_linear(node, nr_irqs,
						   &mmp_irq_करोमुख्य_ops,
						   &icu_data[0]);
	क्रम (irq = 0; irq < nr_irqs; irq++) अणु
		ret = irq_create_mapping(icu_data[0].करोमुख्य, irq);
		अगर (!ret) अणु
			pr_err("Failed to mapping hwirq\n");
			जाओ err;
		पूर्ण
		अगर (!irq)
			icu_data[0].virq_base = ret;
	पूर्ण
	icu_data[0].nr_irqs = nr_irqs;
	वापस 0;
err:
	अगर (icu_data[0].virq_base) अणु
		क्रम (i = 0; i < irq; i++)
			irq_dispose_mapping(icu_data[0].virq_base + i);
	पूर्ण
	irq_करोमुख्य_हटाओ(icu_data[0].करोमुख्य);
	iounmap(mmp_icu_base);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __init mmp_of_init(काष्ठा device_node *node,
			      काष्ठा device_node *parent)
अणु
	पूर्णांक ret;

	ret = mmp_init_bases(node);
	अगर (ret < 0)
		वापस ret;

	icu_data[0].conf_enable = mmp_conf.conf_enable;
	icu_data[0].conf_disable = mmp_conf.conf_disable;
	icu_data[0].conf_mask = mmp_conf.conf_mask;
	set_handle_irq(mmp_handle_irq);
	max_icu_nr = 1;
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(mmp_पूर्णांकc, "mrvl,mmp-intc", mmp_of_init);

अटल पूर्णांक __init mmp2_of_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	पूर्णांक ret;

	ret = mmp_init_bases(node);
	अगर (ret < 0)
		वापस ret;

	icu_data[0].conf_enable = mmp2_conf.conf_enable;
	icu_data[0].conf_disable = mmp2_conf.conf_disable;
	icu_data[0].conf_mask = mmp2_conf.conf_mask;
	set_handle_irq(mmp2_handle_irq);
	max_icu_nr = 1;
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(mmp2_पूर्णांकc, "mrvl,mmp2-intc", mmp2_of_init);

अटल पूर्णांक __init mmp3_of_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	पूर्णांक ret;

	mmp_icu2_base = of_iomap(node, 1);
	अगर (!mmp_icu2_base) अणु
		pr_err("Failed to get interrupt controller register #2\n");
		वापस -ENODEV;
	पूर्ण

	ret = mmp_init_bases(node);
	अगर (ret < 0) अणु
		iounmap(mmp_icu2_base);
		वापस ret;
	पूर्ण

	icu_data[0].conf_enable = mmp3_conf.conf_enable;
	icu_data[0].conf_disable = mmp3_conf.conf_disable;
	icu_data[0].conf_mask = mmp3_conf.conf_mask;
	icu_data[0].conf2_mask = mmp3_conf.conf2_mask;

	अगर (!parent) अणु
		/* This is the मुख्य पूर्णांकerrupt controller. */
		set_handle_irq(mmp2_handle_irq);
	पूर्ण

	max_icu_nr = 1;
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(mmp3_पूर्णांकc, "marvell,mmp3-intc", mmp3_of_init);

अटल पूर्णांक __init mmp2_mux_of_init(काष्ठा device_node *node,
				   काष्ठा device_node *parent)
अणु
	पूर्णांक i, ret, irq, j = 0;
	u32 nr_irqs, mfp_irq;
	u32 reg[4];

	अगर (!parent)
		वापस -ENODEV;

	i = max_icu_nr;
	ret = of_property_पढ़ो_u32(node, "mrvl,intc-nr-irqs",
				   &nr_irqs);
	अगर (ret) अणु
		pr_err("Not found mrvl,intc-nr-irqs property\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * For historical reasons, the "regs" property of the
	 * mrvl,mmp2-mux-पूर्णांकc is not a regular "regs" property containing
	 * addresses on the parent bus, but offsets from the पूर्णांकc's base.
	 * That is why we can't use of_address_to_resource() here.
	 */
	ret = of_property_पढ़ो_variable_u32_array(node, "reg", reg,
						  ARRAY_SIZE(reg),
						  ARRAY_SIZE(reg));
	अगर (ret < 0) अणु
		pr_err("Not found reg property\n");
		वापस -EINVAL;
	पूर्ण
	icu_data[i].reg_status = mmp_icu_base + reg[0];
	icu_data[i].reg_mask = mmp_icu_base + reg[2];
	icu_data[i].cascade_irq = irq_of_parse_and_map(node, 0);
	अगर (!icu_data[i].cascade_irq)
		वापस -EINVAL;

	icu_data[i].virq_base = 0;
	icu_data[i].करोमुख्य = irq_करोमुख्य_add_linear(node, nr_irqs,
						   &mmp_irq_करोमुख्य_ops,
						   &icu_data[i]);
	क्रम (irq = 0; irq < nr_irqs; irq++) अणु
		ret = irq_create_mapping(icu_data[i].करोमुख्य, irq);
		अगर (!ret) अणु
			pr_err("Failed to mapping hwirq\n");
			जाओ err;
		पूर्ण
		अगर (!irq)
			icu_data[i].virq_base = ret;
	पूर्ण
	icu_data[i].nr_irqs = nr_irqs;
	अगर (!of_property_पढ़ो_u32(node, "mrvl,clr-mfp-irq",
				  &mfp_irq)) अणु
		icu_data[i].clr_mfp_irq_base = icu_data[i].virq_base;
		icu_data[i].clr_mfp_hwirq = mfp_irq;
	पूर्ण
	irq_set_chained_handler(icu_data[i].cascade_irq,
				icu_mux_irq_demux);
	max_icu_nr++;
	वापस 0;
err:
	अगर (icu_data[i].virq_base) अणु
		क्रम (j = 0; j < irq; j++)
			irq_dispose_mapping(icu_data[i].virq_base + j);
	पूर्ण
	irq_करोमुख्य_हटाओ(icu_data[i].करोमुख्य);
	वापस -EINVAL;
पूर्ण
IRQCHIP_DECLARE(mmp2_mux_पूर्णांकc, "mrvl,mmp2-mux-intc", mmp2_mux_of_init);
#पूर्ण_अगर
