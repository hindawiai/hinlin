<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/arch/arm/common/vic.c
 *
 *  Copyright (C) 1999 - 2003 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/device.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/irqchip/arm-vic.h>

#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/irq.h>

#घोषणा VIC_IRQ_STATUS			0x00
#घोषणा VIC_FIQ_STATUS			0x04
#घोषणा VIC_RAW_STATUS			0x08
#घोषणा VIC_INT_SELECT			0x0c	/* 1 = FIQ, 0 = IRQ */
#घोषणा VIC_INT_ENABLE			0x10	/* 1 = enable, 0 = disable */
#घोषणा VIC_INT_ENABLE_CLEAR		0x14
#घोषणा VIC_INT_SOFT			0x18
#घोषणा VIC_INT_SOFT_CLEAR		0x1c
#घोषणा VIC_PROTECT			0x20
#घोषणा VIC_PL190_VECT_ADDR		0x30	/* PL190 only */
#घोषणा VIC_PL190_DEF_VECT_ADDR		0x34	/* PL190 only */

#घोषणा VIC_VECT_ADDR0			0x100	/* 0 to 15 (0..31 PL192) */
#घोषणा VIC_VECT_CNTL0			0x200	/* 0 to 15 (0..31 PL192) */
#घोषणा VIC_ITCR			0x300	/* VIC test control रेजिस्टर */

#घोषणा VIC_VECT_CNTL_ENABLE		(1 << 5)

#घोषणा VIC_PL192_VECT_ADDR		0xF00

/**
 * काष्ठा vic_device - VIC PM device
 * @parent_irq: The parent IRQ number of the VIC अगर cascaded, or 0.
 * @irq: The IRQ number क्रम the base of the VIC.
 * @base: The रेजिस्टर base क्रम the VIC.
 * @valid_sources: A biपंचांगask of valid पूर्णांकerrupts
 * @resume_sources: A biपंचांगask of पूर्णांकerrupts क्रम resume.
 * @resume_irqs: The IRQs enabled क्रम resume.
 * @पूर्णांक_select: Save क्रम VIC_INT_SELECT.
 * @पूर्णांक_enable: Save क्रम VIC_INT_ENABLE.
 * @soft_पूर्णांक: Save क्रम VIC_INT_SOFT.
 * @protect: Save क्रम VIC_PROTECT.
 * @करोमुख्य: The IRQ करोमुख्य क्रम the VIC.
 */
काष्ठा vic_device अणु
	व्योम __iomem	*base;
	पूर्णांक		irq;
	u32		valid_sources;
	u32		resume_sources;
	u32		resume_irqs;
	u32		पूर्णांक_select;
	u32		पूर्णांक_enable;
	u32		soft_पूर्णांक;
	u32		protect;
	काष्ठा irq_करोमुख्य *करोमुख्य;
पूर्ण;

/* we cannot allocate memory when VICs are initially रेजिस्टरed */
अटल काष्ठा vic_device vic_devices[CONFIG_ARM_VIC_NR];

अटल पूर्णांक vic_id;

अटल व्योम vic_handle_irq(काष्ठा pt_regs *regs);

/**
 * vic_init2 - common initialisation code
 * @base: Base of the VIC.
 *
 * Common initialisation code क्रम registration
 * and resume.
*/
अटल व्योम vic_init2(व्योम __iomem *base)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		व्योम __iomem *reg = base + VIC_VECT_CNTL0 + (i * 4);
		ग_लिखोl(VIC_VECT_CNTL_ENABLE | i, reg);
	पूर्ण

	ग_लिखोl(32, base + VIC_PL190_DEF_VECT_ADDR);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम resume_one_vic(काष्ठा vic_device *vic)
अणु
	व्योम __iomem *base = vic->base;

	prपूर्णांकk(KERN_DEBUG "%s: resuming vic at %p\n", __func__, base);

	/* re-initialise अटल settings */
	vic_init2(base);

	ग_लिखोl(vic->पूर्णांक_select, base + VIC_INT_SELECT);
	ग_लिखोl(vic->protect, base + VIC_PROTECT);

	/* set the enabled पूर्णांकs and then clear the non-enabled */
	ग_लिखोl(vic->पूर्णांक_enable, base + VIC_INT_ENABLE);
	ग_लिखोl(~vic->पूर्णांक_enable, base + VIC_INT_ENABLE_CLEAR);

	/* and the same क्रम the soft-पूर्णांक रेजिस्टर */

	ग_लिखोl(vic->soft_पूर्णांक, base + VIC_INT_SOFT);
	ग_लिखोl(~vic->soft_पूर्णांक, base + VIC_INT_SOFT_CLEAR);
पूर्ण

अटल व्योम vic_resume(व्योम)
अणु
	पूर्णांक id;

	क्रम (id = vic_id - 1; id >= 0; id--)
		resume_one_vic(vic_devices + id);
पूर्ण

अटल व्योम suspend_one_vic(काष्ठा vic_device *vic)
अणु
	व्योम __iomem *base = vic->base;

	prपूर्णांकk(KERN_DEBUG "%s: suspending vic at %p\n", __func__, base);

	vic->पूर्णांक_select = पढ़ोl(base + VIC_INT_SELECT);
	vic->पूर्णांक_enable = पढ़ोl(base + VIC_INT_ENABLE);
	vic->soft_पूर्णांक = पढ़ोl(base + VIC_INT_SOFT);
	vic->protect = पढ़ोl(base + VIC_PROTECT);

	/* set the पूर्णांकerrupts (अगर any) that are used क्रम
	 * resuming the प्रणाली */

	ग_लिखोl(vic->resume_irqs, base + VIC_INT_ENABLE);
	ग_लिखोl(~vic->resume_irqs, base + VIC_INT_ENABLE_CLEAR);
पूर्ण

अटल पूर्णांक vic_suspend(व्योम)
अणु
	पूर्णांक id;

	क्रम (id = 0; id < vic_id; id++)
		suspend_one_vic(vic_devices + id);

	वापस 0;
पूर्ण

अटल काष्ठा syscore_ops vic_syscore_ops = अणु
	.suspend	= vic_suspend,
	.resume		= vic_resume,
पूर्ण;

/**
 * vic_pm_init - initcall to रेजिस्टर VIC pm
 *
 * This is called via late_initcall() to रेजिस्टर
 * the resources क्रम the VICs due to the early
 * nature of the VIC's registration.
*/
अटल पूर्णांक __init vic_pm_init(व्योम)
अणु
	अगर (vic_id > 0)
		रेजिस्टर_syscore_ops(&vic_syscore_ops);

	वापस 0;
पूर्ण
late_initcall(vic_pm_init);
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा irq_chip vic_chip;

अटल पूर्णांक vic_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
			     irq_hw_number_t hwirq)
अणु
	काष्ठा vic_device *v = d->host_data;

	/* Skip invalid IRQs, only रेजिस्टर handlers क्रम the real ones */
	अगर (!(v->valid_sources & (1 << hwirq)))
		वापस -EPERM;
	irq_set_chip_and_handler(irq, &vic_chip, handle_level_irq);
	irq_set_chip_data(irq, v->base);
	irq_set_probe(irq);
	वापस 0;
पूर्ण

/*
 * Handle each पूर्णांकerrupt in a single VIC.  Returns non-zero अगर we've
 * handled at least one पूर्णांकerrupt.  This पढ़ोs the status रेजिस्टर
 * beक्रमe handling each पूर्णांकerrupt, which is necessary given that
 * handle_IRQ may briefly re-enable पूर्णांकerrupts क्रम soft IRQ handling.
 */
अटल पूर्णांक handle_one_vic(काष्ठा vic_device *vic, काष्ठा pt_regs *regs)
अणु
	u32 stat, irq;
	पूर्णांक handled = 0;

	जबतक ((stat = पढ़ोl_relaxed(vic->base + VIC_IRQ_STATUS))) अणु
		irq = ffs(stat) - 1;
		handle_करोमुख्य_irq(vic->करोमुख्य, irq, regs);
		handled = 1;
	पूर्ण

	वापस handled;
पूर्ण

अटल व्योम vic_handle_irq_cascaded(काष्ठा irq_desc *desc)
अणु
	u32 stat, hwirq;
	काष्ठा irq_chip *host_chip = irq_desc_get_chip(desc);
	काष्ठा vic_device *vic = irq_desc_get_handler_data(desc);

	chained_irq_enter(host_chip, desc);

	जबतक ((stat = पढ़ोl_relaxed(vic->base + VIC_IRQ_STATUS))) अणु
		hwirq = ffs(stat) - 1;
		generic_handle_irq(irq_find_mapping(vic->करोमुख्य, hwirq));
	पूर्ण

	chained_irq_निकास(host_chip, desc);
पूर्ण

/*
 * Keep iterating over all रेजिस्टरed VIC's until there are no pending
 * पूर्णांकerrupts.
 */
अटल व्योम __exception_irq_entry vic_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, handled;

	करो अणु
		क्रम (i = 0, handled = 0; i < vic_id; ++i)
			handled |= handle_one_vic(&vic_devices[i], regs);
	पूर्ण जबतक (handled);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops vic_irqकरोमुख्य_ops = अणु
	.map = vic_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

/**
 * vic_रेजिस्टर() - Register a VIC.
 * @base: The base address of the VIC.
 * @parent_irq: The parent IRQ अगर cascaded, अन्यथा 0.
 * @irq: The base IRQ क्रम the VIC.
 * @valid_sources: biपंचांगask of valid पूर्णांकerrupts
 * @resume_sources: biपंचांगask of पूर्णांकerrupts allowed क्रम resume sources.
 * @node: The device tree node associated with the VIC.
 *
 * Register the VIC with the प्रणाली device tree so that it can be notअगरied
 * of suspend and resume requests and ensure that the correct actions are
 * taken to re-instate the settings on resume.
 *
 * This also configures the IRQ करोमुख्य क्रम the VIC.
 */
अटल व्योम __init vic_रेजिस्टर(व्योम __iomem *base, अचिन्हित पूर्णांक parent_irq,
				अचिन्हित पूर्णांक irq,
				u32 valid_sources, u32 resume_sources,
				काष्ठा device_node *node)
अणु
	काष्ठा vic_device *v;
	पूर्णांक i;

	अगर (vic_id >= ARRAY_SIZE(vic_devices)) अणु
		prपूर्णांकk(KERN_ERR "%s: too few VICs, increase CONFIG_ARM_VIC_NR\n", __func__);
		वापस;
	पूर्ण

	v = &vic_devices[vic_id];
	v->base = base;
	v->valid_sources = valid_sources;
	v->resume_sources = resume_sources;
	set_handle_irq(vic_handle_irq);
	vic_id++;

	अगर (parent_irq) अणु
		irq_set_chained_handler_and_data(parent_irq,
						 vic_handle_irq_cascaded, v);
	पूर्ण

	v->करोमुख्य = irq_करोमुख्य_add_simple(node, fls(valid_sources), irq,
					  &vic_irqकरोमुख्य_ops, v);
	/* create an IRQ mapping क्रम each valid IRQ */
	क्रम (i = 0; i < fls(valid_sources); i++)
		अगर (valid_sources & (1 << i))
			irq_create_mapping(v->करोमुख्य, i);
	/* If no base IRQ was passed, figure out our allocated base */
	अगर (irq)
		v->irq = irq;
	अन्यथा
		v->irq = irq_find_mapping(v->करोमुख्य, 0);
पूर्ण

अटल व्योम vic_ack_irq(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक irq = d->hwirq;
	ग_लिखोl(1 << irq, base + VIC_INT_ENABLE_CLEAR);
	/* moreover, clear the soft-triggered, in हाल it was the reason */
	ग_लिखोl(1 << irq, base + VIC_INT_SOFT_CLEAR);
पूर्ण

अटल व्योम vic_mask_irq(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक irq = d->hwirq;
	ग_लिखोl(1 << irq, base + VIC_INT_ENABLE_CLEAR);
पूर्ण

अटल व्योम vic_unmask_irq(काष्ठा irq_data *d)
अणु
	व्योम __iomem *base = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक irq = d->hwirq;
	ग_लिखोl(1 << irq, base + VIC_INT_ENABLE);
पूर्ण

#अगर defined(CONFIG_PM)
अटल काष्ठा vic_device *vic_from_irq(अचिन्हित पूर्णांक irq)
अणु
        काष्ठा vic_device *v = vic_devices;
	अचिन्हित पूर्णांक base_irq = irq & ~31;
	पूर्णांक id;

	क्रम (id = 0; id < vic_id; id++, v++) अणु
		अगर (v->irq == base_irq)
			वापस v;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक vic_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा vic_device *v = vic_from_irq(d->irq);
	अचिन्हित पूर्णांक off = d->hwirq;
	u32 bit = 1 << off;

	अगर (!v)
		वापस -EINVAL;

	अगर (!(bit & v->resume_sources))
		वापस -EINVAL;

	अगर (on)
		v->resume_irqs |= bit;
	अन्यथा
		v->resume_irqs &= ~bit;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा vic_set_wake शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा irq_chip vic_chip = अणु
	.name		= "VIC",
	.irq_ack	= vic_ack_irq,
	.irq_mask	= vic_mask_irq,
	.irq_unmask	= vic_unmask_irq,
	.irq_set_wake	= vic_set_wake,
पूर्ण;

अटल व्योम __init vic_disable(व्योम __iomem *base)
अणु
	ग_लिखोl(0, base + VIC_INT_SELECT);
	ग_लिखोl(0, base + VIC_INT_ENABLE);
	ग_लिखोl(~0, base + VIC_INT_ENABLE_CLEAR);
	ग_लिखोl(0, base + VIC_ITCR);
	ग_लिखोl(~0, base + VIC_INT_SOFT_CLEAR);
पूर्ण

अटल व्योम __init vic_clear_पूर्णांकerrupts(व्योम __iomem *base)
अणु
	अचिन्हित पूर्णांक i;

	ग_लिखोl(0, base + VIC_PL190_VECT_ADDR);
	क्रम (i = 0; i < 19; i++) अणु
		अचिन्हित पूर्णांक value;

		value = पढ़ोl(base + VIC_PL190_VECT_ADDR);
		ग_लिखोl(value, base + VIC_PL190_VECT_ADDR);
	पूर्ण
पूर्ण

/*
 * The PL190 cell from ARM has been modअगरied by ST to handle 64 पूर्णांकerrupts.
 * The original cell has 32 पूर्णांकerrupts, जबतक the modअगरied one has 64,
 * replicating two blocks 0x00..0x1f in 0x20..0x3f. In that हाल
 * the probe function is called twice, with base set to offset 000
 *  and 020 within the page. We call this "second block".
 */
अटल व्योम __init vic_init_st(व्योम __iomem *base, अचिन्हित पूर्णांक irq_start,
			       u32 vic_sources, काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक vic_2nd_block = ((अचिन्हित दीर्घ)base & ~PAGE_MASK) != 0;

	/* Disable all पूर्णांकerrupts initially. */
	vic_disable(base);

	/*
	 * Make sure we clear all existing पूर्णांकerrupts. The vector रेजिस्टरs
	 * in this cell are after the second block of general रेजिस्टरs,
	 * so we can address them using standard offsets, but only from
	 * the second base address, which is 0x20 in the page
	 */
	अगर (vic_2nd_block) अणु
		vic_clear_पूर्णांकerrupts(base);

		/* ST has 16 vectors as well, but we करोn't enable them by now */
		क्रम (i = 0; i < 16; i++) अणु
			व्योम __iomem *reg = base + VIC_VECT_CNTL0 + (i * 4);
			ग_लिखोl(0, reg);
		पूर्ण

		ग_लिखोl(32, base + VIC_PL190_DEF_VECT_ADDR);
	पूर्ण

	vic_रेजिस्टर(base, 0, irq_start, vic_sources, 0, node);
पूर्ण

अटल व्योम __init __vic_init(व्योम __iomem *base, पूर्णांक parent_irq, पूर्णांक irq_start,
			      u32 vic_sources, u32 resume_sources,
			      काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक i;
	u32 cellid = 0;
	क्रमागत amba_venकरोr venकरोr;

	/* Identअगरy which VIC cell this one is, by पढ़ोing the ID */
	क्रम (i = 0; i < 4; i++) अणु
		व्योम __iomem *addr;
		addr = (व्योम __iomem *)((u32)base & PAGE_MASK) + 0xfe0 + (i * 4);
		cellid |= (पढ़ोl(addr) & 0xff) << (8 * i);
	पूर्ण
	venकरोr = (cellid >> 12) & 0xff;
	prपूर्णांकk(KERN_INFO "VIC @%p: id 0x%08x, vendor 0x%02x\n",
	       base, cellid, venकरोr);

	चयन(venकरोr) अणु
	हाल AMBA_VENDOR_ST:
		vic_init_st(base, irq_start, vic_sources, node);
		वापस;
	शेष:
		prपूर्णांकk(KERN_WARNING "VIC: unknown vendor, continuing anyways\n");
		fallthrough;
	हाल AMBA_VENDOR_ARM:
		अवरोध;
	पूर्ण

	/* Disable all पूर्णांकerrupts initially. */
	vic_disable(base);

	/* Make sure we clear all existing पूर्णांकerrupts */
	vic_clear_पूर्णांकerrupts(base);

	vic_init2(base);

	vic_रेजिस्टर(base, parent_irq, irq_start, vic_sources, resume_sources, node);
पूर्ण

/**
 * vic_init() - initialise a vectored पूर्णांकerrupt controller
 * @base: iomem base address
 * @irq_start: starting पूर्णांकerrupt number, must be muliple of 32
 * @vic_sources: biपंचांगask of पूर्णांकerrupt sources to allow
 * @resume_sources: biपंचांगask of पूर्णांकerrupt sources to allow क्रम resume
 */
व्योम __init vic_init(व्योम __iomem *base, अचिन्हित पूर्णांक irq_start,
		     u32 vic_sources, u32 resume_sources)
अणु
	__vic_init(base, 0, irq_start, vic_sources, resume_sources, शून्य);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक __init vic_of_init(काष्ठा device_node *node,
			      काष्ठा device_node *parent)
अणु
	व्योम __iomem *regs;
	u32 पूर्णांकerrupt_mask = ~0;
	u32 wakeup_mask = ~0;
	पूर्णांक parent_irq;

	regs = of_iomap(node, 0);
	अगर (WARN_ON(!regs))
		वापस -EIO;

	of_property_पढ़ो_u32(node, "valid-mask", &पूर्णांकerrupt_mask);
	of_property_पढ़ो_u32(node, "valid-wakeup-mask", &wakeup_mask);
	parent_irq = of_irq_get(node, 0);
	अगर (parent_irq < 0)
		parent_irq = 0;

	/*
	 * Passing 0 as first IRQ makes the simple करोमुख्य allocate descriptors
	 */
	__vic_init(regs, parent_irq, 0, पूर्णांकerrupt_mask, wakeup_mask, node);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(arm_pl190_vic, "arm,pl190-vic", vic_of_init);
IRQCHIP_DECLARE(arm_pl192_vic, "arm,pl192-vic", vic_of_init);
IRQCHIP_DECLARE(arm_versatile_vic, "arm,versatile-vic", vic_of_init);
#पूर्ण_अगर /* CONFIG OF */
