<शैली गुरु>
/*
 * Allwinner A20/A31 SoCs NMI IRQ chip driver.
 *
 * Carlo Caione <carlo.caione@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा DRV_NAME	"sunxi-nmi"
#घोषणा pr_fmt(fmt)	DRV_NAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>

#घोषणा SUNXI_NMI_SRC_TYPE_MASK	0x00000003

#घोषणा SUNXI_NMI_IRQ_BIT	BIT(0)

/*
 * For deprecated sun6i-a31-sc-nmi compatible.
 */
#घोषणा SUN6I_NMI_CTRL		0x00
#घोषणा SUN6I_NMI_PENDING	0x04
#घोषणा SUN6I_NMI_ENABLE	0x34

#घोषणा SUN7I_NMI_CTRL		0x00
#घोषणा SUN7I_NMI_PENDING	0x04
#घोषणा SUN7I_NMI_ENABLE	0x08

#घोषणा SUN9I_NMI_CTRL		0x00
#घोषणा SUN9I_NMI_ENABLE	0x04
#घोषणा SUN9I_NMI_PENDING	0x08

क्रमागत अणु
	SUNXI_SRC_TYPE_LEVEL_LOW = 0,
	SUNXI_SRC_TYPE_EDGE_FALLING,
	SUNXI_SRC_TYPE_LEVEL_HIGH,
	SUNXI_SRC_TYPE_EDGE_RISING,
पूर्ण;

काष्ठा sunxi_sc_nmi_reg_offs अणु
	u32 ctrl;
	u32 pend;
	u32 enable;
पूर्ण;

अटल स्थिर काष्ठा sunxi_sc_nmi_reg_offs sun6i_reg_offs __initस्थिर = अणु
	.ctrl	= SUN6I_NMI_CTRL,
	.pend	= SUN6I_NMI_PENDING,
	.enable	= SUN6I_NMI_ENABLE,
पूर्ण;

अटल स्थिर काष्ठा sunxi_sc_nmi_reg_offs sun7i_reg_offs __initस्थिर = अणु
	.ctrl	= SUN7I_NMI_CTRL,
	.pend	= SUN7I_NMI_PENDING,
	.enable	= SUN7I_NMI_ENABLE,
पूर्ण;

अटल स्थिर काष्ठा sunxi_sc_nmi_reg_offs sun9i_reg_offs __initस्थिर = अणु
	.ctrl	= SUN9I_NMI_CTRL,
	.pend	= SUN9I_NMI_PENDING,
	.enable	= SUN9I_NMI_ENABLE,
पूर्ण;

अटल अंतरभूत व्योम sunxi_sc_nmi_ग_लिखो(काष्ठा irq_chip_generic *gc, u32 off,
				      u32 val)
अणु
	irq_reg_ग_लिखोl(gc, val, off);
पूर्ण

अटल अंतरभूत u32 sunxi_sc_nmi_पढ़ो(काष्ठा irq_chip_generic *gc, u32 off)
अणु
	वापस irq_reg_पढ़ोl(gc, off);
पूर्ण

अटल व्योम sunxi_sc_nmi_handle_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक virq = irq_find_mapping(करोमुख्य, 0);

	chained_irq_enter(chip, desc);
	generic_handle_irq(virq);
	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक sunxi_sc_nmi_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	काष्ठा irq_chip_type *ct = gc->chip_types;
	u32 src_type_reg;
	u32 ctrl_off = ct->regs.type;
	अचिन्हित पूर्णांक src_type;
	अचिन्हित पूर्णांक i;

	irq_gc_lock(gc);

	चयन (flow_type & IRQF_TRIGGER_MASK) अणु
	हाल IRQ_TYPE_EDGE_FALLING:
		src_type = SUNXI_SRC_TYPE_EDGE_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		src_type = SUNXI_SRC_TYPE_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		src_type = SUNXI_SRC_TYPE_LEVEL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_NONE:
	हाल IRQ_TYPE_LEVEL_LOW:
		src_type = SUNXI_SRC_TYPE_LEVEL_LOW;
		अवरोध;
	शेष:
		irq_gc_unlock(gc);
		pr_err("Cannot assign multiple trigger modes to IRQ %d.\n",
			data->irq);
		वापस -EBADR;
	पूर्ण

	irqd_set_trigger_type(data, flow_type);
	irq_setup_alt_chip(data, flow_type);

	क्रम (i = 0; i < gc->num_ct; i++, ct++)
		अगर (ct->type & flow_type)
			ctrl_off = ct->regs.type;

	src_type_reg = sunxi_sc_nmi_पढ़ो(gc, ctrl_off);
	src_type_reg &= ~SUNXI_NMI_SRC_TYPE_MASK;
	src_type_reg |= src_type;
	sunxi_sc_nmi_ग_लिखो(gc, ctrl_off, src_type_reg);

	irq_gc_unlock(gc);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल पूर्णांक __init sunxi_sc_nmi_irq_init(काष्ठा device_node *node,
					स्थिर काष्ठा sunxi_sc_nmi_reg_offs *reg_offs)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा irq_chip_generic *gc;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक clr = IRQ_NOREQUEST | IRQ_NOPROBE | IRQ_NOAUTOEN;
	पूर्णांक ret;


	करोमुख्य = irq_करोमुख्य_add_linear(node, 1, &irq_generic_chip_ops, शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("Could not register interrupt domain.\n");
		वापस -ENOMEM;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(करोमुख्य, 1, 2, DRV_NAME,
					     handle_fasteoi_irq, clr, 0,
					     IRQ_GC_INIT_MASK_CACHE);
	अगर (ret) अणु
		pr_err("Could not allocate generic interrupt chip.\n");
		जाओ fail_irqd_हटाओ;
	पूर्ण

	irq = irq_of_parse_and_map(node, 0);
	अगर (irq <= 0) अणु
		pr_err("unable to parse irq\n");
		ret = -EINVAL;
		जाओ fail_irqd_हटाओ;
	पूर्ण

	gc = irq_get_करोमुख्य_generic_chip(करोमुख्य, 0);
	gc->reg_base = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(gc->reg_base)) अणु
		pr_err("unable to map resource\n");
		ret = PTR_ERR(gc->reg_base);
		जाओ fail_irqd_हटाओ;
	पूर्ण

	gc->chip_types[0].type			= IRQ_TYPE_LEVEL_MASK;
	gc->chip_types[0].chip.irq_mask		= irq_gc_mask_clr_bit;
	gc->chip_types[0].chip.irq_unmask	= irq_gc_mask_set_bit;
	gc->chip_types[0].chip.irq_eoi		= irq_gc_ack_set_bit;
	gc->chip_types[0].chip.irq_set_type	= sunxi_sc_nmi_set_type;
	gc->chip_types[0].chip.flags		= IRQCHIP_EOI_THREADED | IRQCHIP_EOI_IF_HANDLED;
	gc->chip_types[0].regs.ack		= reg_offs->pend;
	gc->chip_types[0].regs.mask		= reg_offs->enable;
	gc->chip_types[0].regs.type		= reg_offs->ctrl;

	gc->chip_types[1].type			= IRQ_TYPE_EDGE_BOTH;
	gc->chip_types[1].chip.name		= gc->chip_types[0].chip.name;
	gc->chip_types[1].chip.irq_ack		= irq_gc_ack_set_bit;
	gc->chip_types[1].chip.irq_mask		= irq_gc_mask_clr_bit;
	gc->chip_types[1].chip.irq_unmask	= irq_gc_mask_set_bit;
	gc->chip_types[1].chip.irq_set_type	= sunxi_sc_nmi_set_type;
	gc->chip_types[1].regs.ack		= reg_offs->pend;
	gc->chip_types[1].regs.mask		= reg_offs->enable;
	gc->chip_types[1].regs.type		= reg_offs->ctrl;
	gc->chip_types[1].handler		= handle_edge_irq;

	/* Disable any active पूर्णांकerrupts */
	sunxi_sc_nmi_ग_लिखो(gc, reg_offs->enable, 0);

	/* Clear any pending NMI पूर्णांकerrupts */
	sunxi_sc_nmi_ग_लिखो(gc, reg_offs->pend, SUNXI_NMI_IRQ_BIT);

	irq_set_chained_handler_and_data(irq, sunxi_sc_nmi_handle_irq, करोमुख्य);

	वापस 0;

fail_irqd_हटाओ:
	irq_करोमुख्य_हटाओ(करोमुख्य);

	वापस ret;
पूर्ण

अटल पूर्णांक __init sun6i_sc_nmi_irq_init(काष्ठा device_node *node,
					काष्ठा device_node *parent)
अणु
	वापस sunxi_sc_nmi_irq_init(node, &sun6i_reg_offs);
पूर्ण
IRQCHIP_DECLARE(sun6i_sc_nmi, "allwinner,sun6i-a31-sc-nmi", sun6i_sc_nmi_irq_init);

अटल पूर्णांक __init sun7i_sc_nmi_irq_init(काष्ठा device_node *node,
					काष्ठा device_node *parent)
अणु
	वापस sunxi_sc_nmi_irq_init(node, &sun7i_reg_offs);
पूर्ण
IRQCHIP_DECLARE(sun7i_sc_nmi, "allwinner,sun7i-a20-sc-nmi", sun7i_sc_nmi_irq_init);

अटल पूर्णांक __init sun9i_nmi_irq_init(काष्ठा device_node *node,
				     काष्ठा device_node *parent)
अणु
	वापस sunxi_sc_nmi_irq_init(node, &sun9i_reg_offs);
पूर्ण
IRQCHIP_DECLARE(sun9i_nmi, "allwinner,sun9i-a80-nmi", sun9i_nmi_irq_init);
