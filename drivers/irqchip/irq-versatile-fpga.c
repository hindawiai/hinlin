<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Support क्रम Versatile FPGA-based IRQ controllers
 */
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqchip/versatile-fpga.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/irq.h>

#घोषणा IRQ_STATUS		0x00
#घोषणा IRQ_RAW_STATUS		0x04
#घोषणा IRQ_ENABLE_SET		0x08
#घोषणा IRQ_ENABLE_CLEAR	0x0c
#घोषणा INT_SOFT_SET		0x10
#घोषणा INT_SOFT_CLEAR		0x14
#घोषणा FIQ_STATUS		0x20
#घोषणा FIQ_RAW_STATUS		0x24
#घोषणा FIQ_ENABLE		0x28
#घोषणा FIQ_ENABLE_SET		0x28
#घोषणा FIQ_ENABLE_CLEAR	0x2C

#घोषणा PIC_ENABLES             0x20	/* set पूर्णांकerrupt pass through bits */

/**
 * काष्ठा fpga_irq_data - irq data container क्रम the FPGA IRQ controller
 * @base: memory offset in भव memory
 * @chip: chip container क्रम this instance
 * @करोमुख्य: IRQ करोमुख्य क्रम this instance
 * @valid: mask क्रम valid IRQs on this controller
 * @used_irqs: number of active IRQs on this controller
 */
काष्ठा fpga_irq_data अणु
	व्योम __iomem *base;
	काष्ठा irq_chip chip;
	u32 valid;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	u8 used_irqs;
पूर्ण;

/* we cannot allocate memory when the controllers are initially रेजिस्टरed */
अटल काष्ठा fpga_irq_data fpga_irq_devices[CONFIG_VERSATILE_FPGA_IRQ_NR];
अटल पूर्णांक fpga_irq_id;

अटल व्योम fpga_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा fpga_irq_data *f = irq_data_get_irq_chip_data(d);
	u32 mask = 1 << d->hwirq;

	ग_लिखोl(mask, f->base + IRQ_ENABLE_CLEAR);
पूर्ण

अटल व्योम fpga_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा fpga_irq_data *f = irq_data_get_irq_chip_data(d);
	u32 mask = 1 << d->hwirq;

	ग_लिखोl(mask, f->base + IRQ_ENABLE_SET);
पूर्ण

अटल व्योम fpga_irq_handle(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा fpga_irq_data *f = irq_desc_get_handler_data(desc);
	u32 status;

	chained_irq_enter(chip, desc);

	status = पढ़ोl(f->base + IRQ_STATUS);
	अगर (status == 0) अणु
		करो_bad_IRQ(desc);
		जाओ out;
	पूर्ण

	करो अणु
		अचिन्हित पूर्णांक irq = ffs(status) - 1;

		status &= ~(1 << irq);
		generic_handle_irq(irq_find_mapping(f->करोमुख्य, irq));
	पूर्ण जबतक (status);

out:
	chained_irq_निकास(chip, desc);
पूर्ण

/*
 * Handle each पूर्णांकerrupt in a single FPGA IRQ controller.  Returns non-zero
 * अगर we've handled at least one पूर्णांकerrupt.  This करोes a single पढ़ो of the
 * status रेजिस्टर and handles all पूर्णांकerrupts in order from LSB first.
 */
अटल पूर्णांक handle_one_fpga(काष्ठा fpga_irq_data *f, काष्ठा pt_regs *regs)
अणु
	पूर्णांक handled = 0;
	पूर्णांक irq;
	u32 status;

	जबतक ((status  = पढ़ोl(f->base + IRQ_STATUS))) अणु
		irq = ffs(status) - 1;
		handle_करोमुख्य_irq(f->करोमुख्य, irq, regs);
		handled = 1;
	पूर्ण

	वापस handled;
पूर्ण

/*
 * Keep iterating over all रेजिस्टरed FPGA IRQ controllers until there are
 * no pending पूर्णांकerrupts.
 */
यंत्रlinkage व्योम __exception_irq_entry fpga_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, handled;

	करो अणु
		क्रम (i = 0, handled = 0; i < fpga_irq_id; ++i)
			handled |= handle_one_fpga(&fpga_irq_devices[i], regs);
	पूर्ण जबतक (handled);
पूर्ण

अटल पूर्णांक fpga_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		irq_hw_number_t hwirq)
अणु
	काष्ठा fpga_irq_data *f = d->host_data;

	/* Skip invalid IRQs, only रेजिस्टर handlers क्रम the real ones */
	अगर (!(f->valid & BIT(hwirq)))
		वापस -EPERM;
	irq_set_chip_data(irq, f);
	irq_set_chip_and_handler(irq, &f->chip,
				handle_level_irq);
	irq_set_probe(irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops fpga_irqकरोमुख्य_ops = अणु
	.map = fpga_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

व्योम __init fpga_irq_init(व्योम __iomem *base, स्थिर अक्षर *name, पूर्णांक irq_start,
			  पूर्णांक parent_irq, u32 valid, काष्ठा device_node *node)
अणु
	काष्ठा fpga_irq_data *f;
	पूर्णांक i;

	अगर (fpga_irq_id >= ARRAY_SIZE(fpga_irq_devices)) अणु
		pr_err("%s: too few FPGA IRQ controllers, increase CONFIG_VERSATILE_FPGA_IRQ_NR\n", __func__);
		वापस;
	पूर्ण
	f = &fpga_irq_devices[fpga_irq_id];
	f->base = base;
	f->chip.name = name;
	f->chip.irq_ack = fpga_irq_mask;
	f->chip.irq_mask = fpga_irq_mask;
	f->chip.irq_unmask = fpga_irq_unmask;
	f->valid = valid;

	अगर (parent_irq != -1) अणु
		irq_set_chained_handler_and_data(parent_irq, fpga_irq_handle,
						 f);
	पूर्ण

	/* This will also allocate irq descriptors */
	f->करोमुख्य = irq_करोमुख्य_add_simple(node, fls(valid), irq_start,
					  &fpga_irqकरोमुख्य_ops, f);

	/* This will allocate all valid descriptors in the linear हाल */
	क्रम (i = 0; i < fls(valid); i++)
		अगर (valid & BIT(i)) अणु
			अगर (!irq_start)
				irq_create_mapping(f->करोमुख्य, i);
			f->used_irqs++;
		पूर्ण

	pr_info("FPGA IRQ chip %d \"%s\" @ %p, %u irqs",
		fpga_irq_id, name, base, f->used_irqs);
	अगर (parent_irq != -1)
		pr_cont(", parent IRQ: %d\n", parent_irq);
	अन्यथा
		pr_cont("\n");

	fpga_irq_id++;
पूर्ण

#अगर_घोषित CONFIG_OF
पूर्णांक __init fpga_irq_of_init(काष्ठा device_node *node,
			    काष्ठा device_node *parent)
अणु
	व्योम __iomem *base;
	u32 clear_mask;
	u32 valid_mask;
	पूर्णांक parent_irq;

	अगर (WARN_ON(!node))
		वापस -ENODEV;

	base = of_iomap(node, 0);
	WARN(!base, "unable to map fpga irq registers\n");

	अगर (of_property_पढ़ो_u32(node, "clear-mask", &clear_mask))
		clear_mask = 0;

	अगर (of_property_पढ़ो_u32(node, "valid-mask", &valid_mask))
		valid_mask = 0;

	ग_लिखोl(clear_mask, base + IRQ_ENABLE_CLEAR);
	ग_लिखोl(clear_mask, base + FIQ_ENABLE_CLEAR);

	/* Some chips are cascaded from a parent IRQ */
	parent_irq = irq_of_parse_and_map(node, 0);
	अगर (!parent_irq) अणु
		set_handle_irq(fpga_handle_irq);
		parent_irq = -1;
	पूर्ण

	fpga_irq_init(base, node->name, 0, parent_irq, valid_mask, node);

	/*
	 * On Versatile AB/PB, some secondary पूर्णांकerrupts have a direct
	 * pass-thru to the primary controller क्रम IRQs 20 and 22-31 which need
	 * to be enabled. See section 3.10 of the Versatile AB user guide.
	 */
	अगर (of_device_is_compatible(node, "arm,versatile-sic"))
		ग_लिखोl(0xffd00000, base + PIC_ENABLES);

	वापस 0;
पूर्ण
IRQCHIP_DECLARE(arm_fpga, "arm,versatile-fpga-irq", fpga_irq_of_init);
IRQCHIP_DECLARE(arm_fpga_sic, "arm,versatile-sic", fpga_irq_of_init);
IRQCHIP_DECLARE(ox810se_rps, "oxsemi,ox810se-rps-irq", fpga_irq_of_init);
#पूर्ण_अगर
