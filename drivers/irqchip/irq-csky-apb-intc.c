<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/module.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>

#घोषणा INTC_IRQS		64

#घोषणा CK_INTC_ICR		0x00
#घोषणा CK_INTC_PEN31_00	0x14
#घोषणा CK_INTC_PEN63_32	0x2c
#घोषणा CK_INTC_NEN31_00	0x10
#घोषणा CK_INTC_NEN63_32	0x28
#घोषणा CK_INTC_SOURCE		0x40
#घोषणा CK_INTC_DUAL_BASE	0x100

#घोषणा GX_INTC_PEN31_00	0x00
#घोषणा GX_INTC_PEN63_32	0x04
#घोषणा GX_INTC_NEN31_00	0x40
#घोषणा GX_INTC_NEN63_32	0x44
#घोषणा GX_INTC_NMASK31_00	0x50
#घोषणा GX_INTC_NMASK63_32	0x54
#घोषणा GX_INTC_SOURCE		0x60

अटल व्योम __iomem *reg_base;
अटल काष्ठा irq_करोमुख्य *root_करोमुख्य;

अटल पूर्णांक nr_irq = INTC_IRQS;

/*
 * When controller support pulse संकेत, the PEN_reg will hold on संकेत
 * without software trigger.
 *
 * So, to support pulse संकेत we need to clear IFR_reg and the address of
 * IFR_offset is NEN_offset - 8.
 */
अटल व्योम irq_ck_mask_set_bit(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	काष्ठा irq_chip_type *ct = irq_data_get_chip_type(d);
	अचिन्हित दीर्घ अगरr = ct->regs.mask - 8;
	u32 mask = d->mask;

	irq_gc_lock(gc);
	*ct->mask_cache |= mask;
	irq_reg_ग_लिखोl(gc, *ct->mask_cache, ct->regs.mask);
	irq_reg_ग_लिखोl(gc, irq_reg_पढ़ोl(gc, अगरr) & ~mask, अगरr);
	irq_gc_unlock(gc);
पूर्ण

अटल व्योम __init ck_set_gc(काष्ठा device_node *node, व्योम __iomem *reg_base,
			     u32 mask_reg, u32 irq_base)
अणु
	काष्ठा irq_chip_generic *gc;

	gc = irq_get_करोमुख्य_generic_chip(root_करोमुख्य, irq_base);
	gc->reg_base = reg_base;
	gc->chip_types[0].regs.mask = mask_reg;
	gc->chip_types[0].chip.irq_mask = irq_gc_mask_clr_bit;
	gc->chip_types[0].chip.irq_unmask = irq_gc_mask_set_bit;

	अगर (of_find_property(node, "csky,support-pulse-signal", शून्य))
		gc->chip_types[0].chip.irq_unmask = irq_ck_mask_set_bit;
पूर्ण

अटल अंतरभूत u32 build_channel_val(u32 idx, u32 magic)
अणु
	u32 res;

	/*
	 * Set the same index क्रम each channel
	 */
	res = idx | (idx << 8) | (idx << 16) | (idx << 24);

	/*
	 * Set the channel magic number in descending order.
	 * The magic is 0x00010203 क्रम ck-पूर्णांकc
	 * The magic is 0x03020100 क्रम gx6605s-पूर्णांकc
	 */
	वापस res | magic;
पूर्ण

अटल अंतरभूत व्योम setup_irq_channel(u32 magic, व्योम __iomem *reg_addr)
अणु
	u32 i;

	/* Setup 64 channel slots */
	क्रम (i = 0; i < INTC_IRQS; i += 4)
		ग_लिखोl(build_channel_val(i, magic), reg_addr + i);
पूर्ण

अटल पूर्णांक __init
ck_पूर्णांकc_init_comm(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	पूर्णांक ret;

	अगर (parent) अणु
		pr_err("C-SKY Intc not a root irq controller\n");
		वापस -EINVAL;
	पूर्ण

	reg_base = of_iomap(node, 0);
	अगर (!reg_base) अणु
		pr_err("C-SKY Intc unable to map: %p.\n", node);
		वापस -EINVAL;
	पूर्ण

	root_करोमुख्य = irq_करोमुख्य_add_linear(node, nr_irq,
					    &irq_generic_chip_ops, शून्य);
	अगर (!root_करोमुख्य) अणु
		pr_err("C-SKY Intc irq_domain_add failed.\n");
		वापस -ENOMEM;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(root_करोमुख्य, 32, 1,
			"csky_intc", handle_level_irq,
			IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN, 0, 0);
	अगर (ret) अणु
		pr_err("C-SKY Intc irq_alloc_gc failed.\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool handle_irq_perbit(काष्ठा pt_regs *regs, u32 hwirq,
				     u32 irq_base)
अणु
	अगर (hwirq == 0)
		वापस 0;

	handle_करोमुख्य_irq(root_करोमुख्य, irq_base + __fls(hwirq), regs);

	वापस 1;
पूर्ण

/* gx6605s 64 irqs पूर्णांकerrupt controller */
अटल व्योम gx_irq_handler(काष्ठा pt_regs *regs)
अणु
	bool ret;

retry:
	ret = handle_irq_perbit(regs,
			पढ़ोl(reg_base + GX_INTC_PEN63_32), 32);
	अगर (ret)
		जाओ retry;

	ret = handle_irq_perbit(regs,
			पढ़ोl(reg_base + GX_INTC_PEN31_00), 0);
	अगर (ret)
		जाओ retry;
पूर्ण

अटल पूर्णांक __init
gx_पूर्णांकc_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	पूर्णांक ret;

	ret = ck_पूर्णांकc_init_comm(node, parent);
	अगर (ret)
		वापस ret;

	/*
	 * Initial enable reg to disable all पूर्णांकerrupts
	 */
	ग_लिखोl(0x0, reg_base + GX_INTC_NEN31_00);
	ग_लिखोl(0x0, reg_base + GX_INTC_NEN63_32);

	/*
	 * Initial mask reg with all unmasked, because we only use enable reg
	 */
	ग_लिखोl(0x0, reg_base + GX_INTC_NMASK31_00);
	ग_लिखोl(0x0, reg_base + GX_INTC_NMASK63_32);

	setup_irq_channel(0x03020100, reg_base + GX_INTC_SOURCE);

	ck_set_gc(node, reg_base, GX_INTC_NEN31_00, 0);
	ck_set_gc(node, reg_base, GX_INTC_NEN63_32, 32);

	set_handle_irq(gx_irq_handler);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(csky_gx6605s_पूर्णांकc, "csky,gx6605s-intc", gx_पूर्णांकc_init);

/*
 * C-SKY simple 64 irqs पूर्णांकerrupt controller, dual-together could support 128
 * irqs.
 */
अटल व्योम ck_irq_handler(काष्ठा pt_regs *regs)
अणु
	bool ret;
	व्योम __iomem *reg_pen_lo = reg_base + CK_INTC_PEN31_00;
	व्योम __iomem *reg_pen_hi = reg_base + CK_INTC_PEN63_32;

retry:
	/* handle 0 - 63 irqs */
	ret = handle_irq_perbit(regs, पढ़ोl(reg_pen_hi), 32);
	अगर (ret)
		जाओ retry;

	ret = handle_irq_perbit(regs, पढ़ोl(reg_pen_lo), 0);
	अगर (ret)
		जाओ retry;

	अगर (nr_irq == INTC_IRQS)
		वापस;

	/* handle 64 - 127 irqs */
	ret = handle_irq_perbit(regs,
			पढ़ोl(reg_pen_hi + CK_INTC_DUAL_BASE), 96);
	अगर (ret)
		जाओ retry;

	ret = handle_irq_perbit(regs,
			पढ़ोl(reg_pen_lo + CK_INTC_DUAL_BASE), 64);
	अगर (ret)
		जाओ retry;
पूर्ण

अटल पूर्णांक __init
ck_पूर्णांकc_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	पूर्णांक ret;

	ret = ck_पूर्णांकc_init_comm(node, parent);
	अगर (ret)
		वापस ret;

	/* Initial enable reg to disable all पूर्णांकerrupts */
	ग_लिखोl(0, reg_base + CK_INTC_NEN31_00);
	ग_लिखोl(0, reg_base + CK_INTC_NEN63_32);

	/* Enable irq पूर्णांकc */
	ग_लिखोl(BIT(31), reg_base + CK_INTC_ICR);

	ck_set_gc(node, reg_base, CK_INTC_NEN31_00, 0);
	ck_set_gc(node, reg_base, CK_INTC_NEN63_32, 32);

	setup_irq_channel(0x00010203, reg_base + CK_INTC_SOURCE);

	set_handle_irq(ck_irq_handler);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(ck_पूर्णांकc, "csky,apb-intc", ck_पूर्णांकc_init);

अटल पूर्णांक __init
ck_dual_पूर्णांकc_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	पूर्णांक ret;

	/* dual-apb-पूर्णांकc up to 128 irq sources*/
	nr_irq = INTC_IRQS * 2;

	ret = ck_पूर्णांकc_init(node, parent);
	अगर (ret)
		वापस ret;

	/* Initial enable reg to disable all पूर्णांकerrupts */
	ग_लिखोl(0, reg_base + CK_INTC_NEN31_00 + CK_INTC_DUAL_BASE);
	ग_लिखोl(0, reg_base + CK_INTC_NEN63_32 + CK_INTC_DUAL_BASE);

	ck_set_gc(node, reg_base + CK_INTC_DUAL_BASE, CK_INTC_NEN31_00, 64);
	ck_set_gc(node, reg_base + CK_INTC_DUAL_BASE, CK_INTC_NEN63_32, 96);

	setup_irq_channel(0x00010203,
			  reg_base + CK_INTC_SOURCE + CK_INTC_DUAL_BASE);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(ck_dual_पूर्णांकc, "csky,dual-apb-intc", ck_dual_पूर्णांकc_init);
