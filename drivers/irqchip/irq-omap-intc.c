<शैली गुरु>
/*
 * linux/arch/arm/mach-omap2/irq.c
 *
 * Interrupt handler क्रम OMAP2 boards.
 *
 * Copyright (C) 2005 Nokia Corporation
 * Author: Paul Mundt <paul.mundt@nokia.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/exception.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <linux/irqchip/irq-omap-पूर्णांकc.h>

/* selected INTC रेजिस्टर offsets */

#घोषणा INTC_REVISION		0x0000
#घोषणा INTC_SYSCONFIG		0x0010
#घोषणा INTC_SYSSTATUS		0x0014
#घोषणा INTC_SIR		0x0040
#घोषणा INTC_CONTROL		0x0048
#घोषणा INTC_PROTECTION		0x004C
#घोषणा INTC_IDLE		0x0050
#घोषणा INTC_THRESHOLD		0x0068
#घोषणा INTC_MIR0		0x0084
#घोषणा INTC_MIR_CLEAR0		0x0088
#घोषणा INTC_MIR_SET0		0x008c
#घोषणा INTC_PENDING_IRQ0	0x0098
#घोषणा INTC_PENDING_IRQ1	0x00b8
#घोषणा INTC_PENDING_IRQ2	0x00d8
#घोषणा INTC_PENDING_IRQ3	0x00f8
#घोषणा INTC_ILR0		0x0100

#घोषणा ACTIVEIRQ_MASK		0x7f	/* omap2/3 active पूर्णांकerrupt bits */
#घोषणा SPURIOUSIRQ_MASK	(0x1ffffff << 7)
#घोषणा INTCPS_NR_ILR_REGS	128
#घोषणा INTCPS_NR_MIR_REGS	4

#घोषणा INTC_IDLE_FUNCIDLE	(1 << 0)
#घोषणा INTC_IDLE_TURBO		(1 << 1)

#घोषणा INTC_PROTECTION_ENABLE	(1 << 0)

काष्ठा omap_पूर्णांकc_regs अणु
	u32 sysconfig;
	u32 protection;
	u32 idle;
	u32 threshold;
	u32 ilr[INTCPS_NR_ILR_REGS];
	u32 mir[INTCPS_NR_MIR_REGS];
पूर्ण;
अटल काष्ठा omap_पूर्णांकc_regs पूर्णांकc_context;

अटल काष्ठा irq_करोमुख्य *करोमुख्य;
अटल व्योम __iomem *omap_irq_base;
अटल पूर्णांक omap_nr_pending;
अटल पूर्णांक omap_nr_irqs;

अटल व्योम पूर्णांकc_ग_लिखोl(u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, omap_irq_base + reg);
पूर्ण

अटल u32 पूर्णांकc_पढ़ोl(u32 reg)
अणु
	वापस पढ़ोl_relaxed(omap_irq_base + reg);
पूर्ण

व्योम omap_पूर्णांकc_save_context(व्योम)
अणु
	पूर्णांक i;

	पूर्णांकc_context.sysconfig =
		पूर्णांकc_पढ़ोl(INTC_SYSCONFIG);
	पूर्णांकc_context.protection =
		पूर्णांकc_पढ़ोl(INTC_PROTECTION);
	पूर्णांकc_context.idle =
		पूर्णांकc_पढ़ोl(INTC_IDLE);
	पूर्णांकc_context.threshold =
		पूर्णांकc_पढ़ोl(INTC_THRESHOLD);

	क्रम (i = 0; i < omap_nr_irqs; i++)
		पूर्णांकc_context.ilr[i] =
			पूर्णांकc_पढ़ोl((INTC_ILR0 + 0x4 * i));
	क्रम (i = 0; i < INTCPS_NR_MIR_REGS; i++)
		पूर्णांकc_context.mir[i] =
			पूर्णांकc_पढ़ोl(INTC_MIR0 + (0x20 * i));
पूर्ण

व्योम omap_पूर्णांकc_restore_context(व्योम)
अणु
	पूर्णांक i;

	पूर्णांकc_ग_लिखोl(INTC_SYSCONFIG, पूर्णांकc_context.sysconfig);
	पूर्णांकc_ग_लिखोl(INTC_PROTECTION, पूर्णांकc_context.protection);
	पूर्णांकc_ग_लिखोl(INTC_IDLE, पूर्णांकc_context.idle);
	पूर्णांकc_ग_लिखोl(INTC_THRESHOLD, पूर्णांकc_context.threshold);

	क्रम (i = 0; i < omap_nr_irqs; i++)
		पूर्णांकc_ग_लिखोl(INTC_ILR0 + 0x4 * i,
				पूर्णांकc_context.ilr[i]);

	क्रम (i = 0; i < INTCPS_NR_MIR_REGS; i++)
		पूर्णांकc_ग_लिखोl(INTC_MIR0 + 0x20 * i,
			पूर्णांकc_context.mir[i]);
	/* MIRs are saved and restore with other PRCM रेजिस्टरs */
पूर्ण

व्योम omap3_पूर्णांकc_prepare_idle(व्योम)
अणु
	/*
	 * Disable स्वतःidle as it can stall पूर्णांकerrupt controller,
	 * cf. errata ID i540 क्रम 3430 (all revisions up to 3.1.x)
	 */
	पूर्णांकc_ग_लिखोl(INTC_SYSCONFIG, 0);
	पूर्णांकc_ग_लिखोl(INTC_IDLE, INTC_IDLE_TURBO);
पूर्ण

व्योम omap3_पूर्णांकc_resume_idle(व्योम)
अणु
	/* Re-enable स्वतःidle */
	पूर्णांकc_ग_लिखोl(INTC_SYSCONFIG, 1);
	पूर्णांकc_ग_लिखोl(INTC_IDLE, 0);
पूर्ण

/* XXX: FIQ and additional INTC support (only MPU at the moment) */
अटल व्योम omap_ack_irq(काष्ठा irq_data *d)
अणु
	पूर्णांकc_ग_लिखोl(INTC_CONTROL, 0x1);
पूर्ण

अटल व्योम omap_mask_ack_irq(काष्ठा irq_data *d)
अणु
	irq_gc_mask_disable_reg(d);
	omap_ack_irq(d);
पूर्ण

अटल व्योम __init omap_irq_soft_reset(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = पूर्णांकc_पढ़ोl(INTC_REVISION) & 0xff;

	pr_info("IRQ: Found an INTC at 0x%p (revision %ld.%ld) with %d interrupts\n",
		omap_irq_base, पंचांगp >> 4, पंचांगp & 0xf, omap_nr_irqs);

	पंचांगp = पूर्णांकc_पढ़ोl(INTC_SYSCONFIG);
	पंचांगp |= 1 << 1;	/* soft reset */
	पूर्णांकc_ग_लिखोl(INTC_SYSCONFIG, पंचांगp);

	जबतक (!(पूर्णांकc_पढ़ोl(INTC_SYSSTATUS) & 0x1))
		/* Wait क्रम reset to complete */;

	/* Enable स्वतःidle */
	पूर्णांकc_ग_लिखोl(INTC_SYSCONFIG, 1 << 0);
पूर्ण

पूर्णांक omap_irq_pending(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < omap_nr_pending; i++)
		अगर (पूर्णांकc_पढ़ोl(INTC_PENDING_IRQ0 + (0x20 * i)))
			वापस 1;
	वापस 0;
पूर्ण

व्योम omap3_पूर्णांकc_suspend(व्योम)
अणु
	/* A pending पूर्णांकerrupt would prevent OMAP from entering suspend */
	omap_ack_irq(शून्य);
पूर्ण

अटल पूर्णांक __init omap_alloc_gc_of(काष्ठा irq_करोमुख्य *d, व्योम __iomem *base)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	ret = irq_alloc_करोमुख्य_generic_chips(d, 32, 1, "INTC",
			handle_level_irq, IRQ_NOREQUEST | IRQ_NOPROBE,
			IRQ_LEVEL, 0);
	अगर (ret) अणु
		pr_warn("Failed to allocate irq chips\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < omap_nr_pending; i++) अणु
		काष्ठा irq_chip_generic *gc;
		काष्ठा irq_chip_type *ct;

		gc = irq_get_करोमुख्य_generic_chip(d, 32 * i);
		gc->reg_base = base;
		ct = gc->chip_types;

		ct->type = IRQ_TYPE_LEVEL_MASK;

		ct->chip.irq_ack = omap_mask_ack_irq;
		ct->chip.irq_mask = irq_gc_mask_disable_reg;
		ct->chip.irq_unmask = irq_gc_unmask_enable_reg;

		ct->chip.flags |= IRQCHIP_SKIP_SET_WAKE;

		ct->regs.enable = INTC_MIR_CLEAR0 + 32 * i;
		ct->regs.disable = INTC_MIR_SET0 + 32 * i;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init omap_alloc_gc_legacy(व्योम __iomem *base,
		अचिन्हित पूर्णांक irq_start, अचिन्हित पूर्णांक num)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;

	gc = irq_alloc_generic_chip("INTC", 1, irq_start, base,
			handle_level_irq);
	ct = gc->chip_types;
	ct->chip.irq_ack = omap_mask_ack_irq;
	ct->chip.irq_mask = irq_gc_mask_disable_reg;
	ct->chip.irq_unmask = irq_gc_unmask_enable_reg;
	ct->chip.flags |= IRQCHIP_SKIP_SET_WAKE;

	ct->regs.enable = INTC_MIR_CLEAR0;
	ct->regs.disable = INTC_MIR_SET0;
	irq_setup_generic_chip(gc, IRQ_MSK(num), IRQ_GC_INIT_MASK_CACHE,
			IRQ_NOREQUEST | IRQ_NOPROBE, 0);
पूर्ण

अटल पूर्णांक __init omap_init_irq_of(काष्ठा device_node *node)
अणु
	पूर्णांक ret;

	omap_irq_base = of_iomap(node, 0);
	अगर (WARN_ON(!omap_irq_base))
		वापस -ENOMEM;

	करोमुख्य = irq_करोमुख्य_add_linear(node, omap_nr_irqs,
			&irq_generic_chip_ops, शून्य);

	omap_irq_soft_reset();

	ret = omap_alloc_gc_of(करोमुख्य, omap_irq_base);
	अगर (ret < 0)
		irq_करोमुख्य_हटाओ(करोमुख्य);

	वापस ret;
पूर्ण

अटल पूर्णांक __init omap_init_irq_legacy(u32 base, काष्ठा device_node *node)
अणु
	पूर्णांक j, irq_base;

	omap_irq_base = ioremap(base, SZ_4K);
	अगर (WARN_ON(!omap_irq_base))
		वापस -ENOMEM;

	irq_base = irq_alloc_descs(-1, 0, omap_nr_irqs, 0);
	अगर (irq_base < 0) अणु
		pr_warn("Couldn't allocate IRQ numbers\n");
		irq_base = 0;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_legacy(node, omap_nr_irqs, irq_base, 0,
			&irq_करोमुख्य_simple_ops, शून्य);

	omap_irq_soft_reset();

	क्रम (j = 0; j < omap_nr_irqs; j += 32)
		omap_alloc_gc_legacy(omap_irq_base + j, j + irq_base, 32);

	वापस 0;
पूर्ण

अटल व्योम __init omap_irq_enable_protection(व्योम)
अणु
	u32 reg;

	reg = पूर्णांकc_पढ़ोl(INTC_PROTECTION);
	reg |= INTC_PROTECTION_ENABLE;
	पूर्णांकc_ग_लिखोl(INTC_PROTECTION, reg);
पूर्ण

अटल पूर्णांक __init omap_init_irq(u32 base, काष्ठा device_node *node)
अणु
	पूर्णांक ret;

	/*
	 * FIXME legacy OMAP DMA driver sitting under arch/arm/plat-omap/dma.c
	 * depends is still not पढ़ोy क्रम linear IRQ करोमुख्यs; because of that
	 * we need to temporarily "blacklist" OMAP2 and OMAP3 devices from using
	 * linear IRQ Doमुख्य until that driver is finally fixed.
	 */
	अगर (of_device_is_compatible(node, "ti,omap2-intc") ||
			of_device_is_compatible(node, "ti,omap3-intc")) अणु
		काष्ठा resource res;

		अगर (of_address_to_resource(node, 0, &res))
			वापस -ENOMEM;

		base = res.start;
		ret = omap_init_irq_legacy(base, node);
	पूर्ण अन्यथा अगर (node) अणु
		ret = omap_init_irq_of(node);
	पूर्ण अन्यथा अणु
		ret = omap_init_irq_legacy(base, शून्य);
	पूर्ण

	अगर (ret == 0)
		omap_irq_enable_protection();

	वापस ret;
पूर्ण

अटल यंत्रlinkage व्योम __exception_irq_entry
omap_पूर्णांकc_handle_irq(काष्ठा pt_regs *regs)
अणु
	बाह्य अचिन्हित दीर्घ irq_err_count;
	u32 irqnr;

	irqnr = पूर्णांकc_पढ़ोl(INTC_SIR);

	/*
	 * A spurious IRQ can result अगर पूर्णांकerrupt that triggered the
	 * sorting is no दीर्घer active during the sorting (10 INTC
	 * functional घड़ी cycles after पूर्णांकerrupt निश्चितion). Or a
	 * change in पूर्णांकerrupt mask affected the result during sorting
	 * समय. There is no special handling required except ignoring
	 * the SIR रेजिस्टर value just पढ़ो and retrying.
	 * See section 6.2.5 of AM335x TRM Literature Number: SPRUH73K
	 *
	 * Many a बार, a spurious पूर्णांकerrupt situation has been fixed
	 * by adding a flush क्रम the posted ग_लिखो acking the IRQ in
	 * the device driver. Typically, this is going be the device
	 * driver whose पूर्णांकerrupt was handled just beक्रमe the spurious
	 * IRQ occurred. Pay attention to those device drivers अगर you
	 * run पूर्णांकo hitting the spurious IRQ condition below.
	 */
	अगर (unlikely((irqnr & SPURIOUSIRQ_MASK) == SPURIOUSIRQ_MASK)) अणु
		pr_err_once("%s: spurious irq!\n", __func__);
		irq_err_count++;
		omap_ack_irq(शून्य);
		वापस;
	पूर्ण

	irqnr &= ACTIVEIRQ_MASK;
	handle_करोमुख्य_irq(करोमुख्य, irqnr, regs);
पूर्ण

अटल पूर्णांक __init पूर्णांकc_of_init(काष्ठा device_node *node,
			     काष्ठा device_node *parent)
अणु
	पूर्णांक ret;

	omap_nr_pending = 3;
	omap_nr_irqs = 96;

	अगर (WARN_ON(!node))
		वापस -ENODEV;

	अगर (of_device_is_compatible(node, "ti,dm814-intc") ||
	    of_device_is_compatible(node, "ti,dm816-intc") ||
	    of_device_is_compatible(node, "ti,am33xx-intc")) अणु
		omap_nr_irqs = 128;
		omap_nr_pending = 4;
	पूर्ण

	ret = omap_init_irq(-1, of_node_get(node));
	अगर (ret < 0)
		वापस ret;

	set_handle_irq(omap_पूर्णांकc_handle_irq);

	वापस 0;
पूर्ण

IRQCHIP_DECLARE(omap2_पूर्णांकc, "ti,omap2-intc", पूर्णांकc_of_init);
IRQCHIP_DECLARE(omap3_पूर्णांकc, "ti,omap3-intc", पूर्णांकc_of_init);
IRQCHIP_DECLARE(dm814x_पूर्णांकc, "ti,dm814-intc", पूर्णांकc_of_init);
IRQCHIP_DECLARE(dm816x_पूर्णांकc, "ti,dm816-intc", पूर्णांकc_of_init);
IRQCHIP_DECLARE(am33xx_पूर्णांकc, "ti,am33xx-intc", पूर्णांकc_of_init);
