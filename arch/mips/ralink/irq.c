<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2009 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/mipsregs.h>

#समावेश "common.h"

#घोषणा INTC_INT_GLOBAL		BIT(31)

#घोषणा RALINK_CPU_IRQ_INTC	(MIPS_CPU_IRQ_BASE + 2)
#घोषणा RALINK_CPU_IRQ_PCI	(MIPS_CPU_IRQ_BASE + 4)
#घोषणा RALINK_CPU_IRQ_FE	(MIPS_CPU_IRQ_BASE + 5)
#घोषणा RALINK_CPU_IRQ_WIFI	(MIPS_CPU_IRQ_BASE + 6)
#घोषणा RALINK_CPU_IRQ_COUNTER	(MIPS_CPU_IRQ_BASE + 7)

/* we have a cascade of 8 irqs */
#घोषणा RALINK_INTC_IRQ_BASE	8

/* we have 32 SoC irqs */
#घोषणा RALINK_INTC_IRQ_COUNT	32

#घोषणा RALINK_INTC_IRQ_PERFC   (RALINK_INTC_IRQ_BASE + 9)

क्रमागत rt_पूर्णांकc_regs_क्रमागत अणु
	INTC_REG_STATUS0 = 0,
	INTC_REG_STATUS1,
	INTC_REG_TYPE,
	INTC_REG_RAW_STATUS,
	INTC_REG_ENABLE,
	INTC_REG_DISABLE,
पूर्ण;

अटल u32 rt_पूर्णांकc_regs[] = अणु
	[INTC_REG_STATUS0] = 0x00,
	[INTC_REG_STATUS1] = 0x04,
	[INTC_REG_TYPE] = 0x20,
	[INTC_REG_RAW_STATUS] = 0x30,
	[INTC_REG_ENABLE] = 0x34,
	[INTC_REG_DISABLE] = 0x38,
पूर्ण;

अटल व्योम __iomem *rt_पूर्णांकc_membase;

अटल पूर्णांक rt_perfcount_irq;

अटल अंतरभूत व्योम rt_पूर्णांकc_w32(u32 val, अचिन्हित reg)
अणु
	__raw_ग_लिखोl(val, rt_पूर्णांकc_membase + rt_पूर्णांकc_regs[reg]);
पूर्ण

अटल अंतरभूत u32 rt_पूर्णांकc_r32(अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(rt_पूर्णांकc_membase + rt_पूर्णांकc_regs[reg]);
पूर्ण

अटल व्योम ralink_पूर्णांकc_irq_unmask(काष्ठा irq_data *d)
अणु
	rt_पूर्णांकc_w32(BIT(d->hwirq), INTC_REG_ENABLE);
पूर्ण

अटल व्योम ralink_पूर्णांकc_irq_mask(काष्ठा irq_data *d)
अणु
	rt_पूर्णांकc_w32(BIT(d->hwirq), INTC_REG_DISABLE);
पूर्ण

अटल काष्ठा irq_chip ralink_पूर्णांकc_irq_chip = अणु
	.name		= "INTC",
	.irq_unmask	= ralink_पूर्णांकc_irq_unmask,
	.irq_mask	= ralink_पूर्णांकc_irq_mask,
	.irq_mask_ack	= ralink_पूर्णांकc_irq_mask,
पूर्ण;

पूर्णांक get_c0_perfcount_पूर्णांक(व्योम)
अणु
	वापस rt_perfcount_irq;
पूर्ण
EXPORT_SYMBOL_GPL(get_c0_perfcount_पूर्णांक);

अचिन्हित पूर्णांक get_c0_compare_पूर्णांक(व्योम)
अणु
	वापस CP0_LEGACY_COMPARE_IRQ;
पूर्ण

अटल व्योम ralink_पूर्णांकc_irq_handler(काष्ठा irq_desc *desc)
अणु
	u32 pending = rt_पूर्णांकc_r32(INTC_REG_STATUS0);

	अगर (pending) अणु
		काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);
		generic_handle_irq(irq_find_mapping(करोमुख्य, __ffs(pending)));
	पूर्ण अन्यथा अणु
		spurious_पूर्णांकerrupt();
	पूर्ण
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित दीर्घ pending;

	pending = पढ़ो_c0_status() & पढ़ो_c0_cause() & ST0_IM;

	अगर (pending & STATUSF_IP7)
		करो_IRQ(RALINK_CPU_IRQ_COUNTER);

	अन्यथा अगर (pending & STATUSF_IP5)
		करो_IRQ(RALINK_CPU_IRQ_FE);

	अन्यथा अगर (pending & STATUSF_IP6)
		करो_IRQ(RALINK_CPU_IRQ_WIFI);

	अन्यथा अगर (pending & STATUSF_IP4)
		करो_IRQ(RALINK_CPU_IRQ_PCI);

	अन्यथा अगर (pending & STATUSF_IP2)
		करो_IRQ(RALINK_CPU_IRQ_INTC);

	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

अटल पूर्णांक पूर्णांकc_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq, irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(irq, &ralink_पूर्णांकc_irq_chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops irq_करोमुख्य_ops = अणु
	.xlate = irq_करोमुख्य_xlate_onecell,
	.map = पूर्णांकc_map,
पूर्ण;

अटल पूर्णांक __init पूर्णांकc_of_init(काष्ठा device_node *node,
			       काष्ठा device_node *parent)
अणु
	काष्ठा resource res;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक irq;

	अगर (!of_property_पढ़ो_u32_array(node, "ralink,intc-registers",
					rt_पूर्णांकc_regs, 6))
		pr_info("intc: using register map from devicetree\n");

	irq = irq_of_parse_and_map(node, 0);
	अगर (!irq)
		panic("Failed to get INTC IRQ");

	अगर (of_address_to_resource(node, 0, &res))
		panic("Failed to get intc memory range");

	अगर (!request_mem_region(res.start, resource_size(&res),
				res.name))
		pr_err("Failed to request intc memory");

	rt_पूर्णांकc_membase = ioremap(res.start,
					resource_size(&res));
	अगर (!rt_पूर्णांकc_membase)
		panic("Failed to remap intc memory");

	/* disable all पूर्णांकerrupts */
	rt_पूर्णांकc_w32(~0, INTC_REG_DISABLE);

	/* route all INTC पूर्णांकerrupts to MIPS HW0 पूर्णांकerrupt */
	rt_पूर्णांकc_w32(0, INTC_REG_TYPE);

	करोमुख्य = irq_करोमुख्य_add_legacy(node, RALINK_INTC_IRQ_COUNT,
			RALINK_INTC_IRQ_BASE, 0, &irq_करोमुख्य_ops, शून्य);
	अगर (!करोमुख्य)
		panic("Failed to add irqdomain");

	rt_पूर्णांकc_w32(INTC_INT_GLOBAL, INTC_REG_ENABLE);

	irq_set_chained_handler_and_data(irq, ralink_पूर्णांकc_irq_handler, करोमुख्य);

	/* tell the kernel which irq is used क्रम perक्रमmance monitoring */
	rt_perfcount_irq = irq_create_mapping(करोमुख्य, 9);

	वापस 0;
पूर्ण

अटल काष्ठा of_device_id __initdata of_irq_ids[] = अणु
	अणु .compatible = "mti,cpu-interrupt-controller", .data = mips_cpu_irq_of_init पूर्ण,
	अणु .compatible = "ralink,rt2880-intc", .data = पूर्णांकc_of_init पूर्ण,
	अणुपूर्ण,
पूर्ण;

व्योम __init arch_init_irq(व्योम)
अणु
	of_irq_init(of_irq_ids);
पूर्ण

