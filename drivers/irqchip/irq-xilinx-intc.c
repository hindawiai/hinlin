<शैली गुरु>
/*
 * Copyright (C) 2007-2013 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2012-2013 Xilinx, Inc.
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/jump_label.h>
#समावेश <linux/bug.h>
#समावेश <linux/of_irq.h>

/* No one अन्यथा should require these स्थिरants, so define them locally here. */
#घोषणा ISR 0x00			/* Interrupt Status Register */
#घोषणा IPR 0x04			/* Interrupt Pending Register */
#घोषणा IER 0x08			/* Interrupt Enable Register */
#घोषणा IAR 0x0c			/* Interrupt Acknowledge Register */
#घोषणा SIE 0x10			/* Set Interrupt Enable bits */
#घोषणा CIE 0x14			/* Clear Interrupt Enable bits */
#घोषणा IVR 0x18			/* Interrupt Vector Register */
#घोषणा MER 0x1c			/* Master Enable Register */

#घोषणा MER_ME (1<<0)
#घोषणा MER_HIE (1<<1)

अटल DEFINE_STATIC_KEY_FALSE(xपूर्णांकc_is_be);

काष्ठा xपूर्णांकc_irq_chip अणु
	व्योम		__iomem *base;
	काष्ठा		irq_करोमुख्य *root_करोमुख्य;
	u32		पूर्णांकr_mask;
	u32		nr_irq;
पूर्ण;

अटल काष्ठा xपूर्णांकc_irq_chip *primary_पूर्णांकc;

अटल व्योम xपूर्णांकc_ग_लिखो(काष्ठा xपूर्णांकc_irq_chip *irqc, पूर्णांक reg, u32 data)
अणु
	अगर (अटल_branch_unlikely(&xपूर्णांकc_is_be))
		ioग_लिखो32be(data, irqc->base + reg);
	अन्यथा
		ioग_लिखो32(data, irqc->base + reg);
पूर्ण

अटल u32 xपूर्णांकc_पढ़ो(काष्ठा xपूर्णांकc_irq_chip *irqc, पूर्णांक reg)
अणु
	अगर (अटल_branch_unlikely(&xपूर्णांकc_is_be))
		वापस ioपढ़ो32be(irqc->base + reg);
	अन्यथा
		वापस ioपढ़ो32(irqc->base + reg);
पूर्ण

अटल व्योम पूर्णांकc_enable_or_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा xपूर्णांकc_irq_chip *irqc = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ mask = BIT(d->hwirq);

	pr_debug("irq-xilinx: enable_or_unmask: %ld\n", d->hwirq);

	/* ack level irqs because they can't be acked during
	 * ack function since the handle_level_irq function
	 * acks the irq beक्रमe calling the पूर्णांकerrupt handler
	 */
	अगर (irqd_is_level_type(d))
		xपूर्णांकc_ग_लिखो(irqc, IAR, mask);

	xपूर्णांकc_ग_लिखो(irqc, SIE, mask);
पूर्ण

अटल व्योम पूर्णांकc_disable_or_mask(काष्ठा irq_data *d)
अणु
	काष्ठा xपूर्णांकc_irq_chip *irqc = irq_data_get_irq_chip_data(d);

	pr_debug("irq-xilinx: disable: %ld\n", d->hwirq);
	xपूर्णांकc_ग_लिखो(irqc, CIE, BIT(d->hwirq));
पूर्ण

अटल व्योम पूर्णांकc_ack(काष्ठा irq_data *d)
अणु
	काष्ठा xपूर्णांकc_irq_chip *irqc = irq_data_get_irq_chip_data(d);

	pr_debug("irq-xilinx: ack: %ld\n", d->hwirq);
	xपूर्णांकc_ग_लिखो(irqc, IAR, BIT(d->hwirq));
पूर्ण

अटल व्योम पूर्णांकc_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा xपूर्णांकc_irq_chip *irqc = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ mask = BIT(d->hwirq);

	pr_debug("irq-xilinx: disable_and_ack: %ld\n", d->hwirq);
	xपूर्णांकc_ग_लिखो(irqc, CIE, mask);
	xपूर्णांकc_ग_लिखो(irqc, IAR, mask);
पूर्ण

अटल काष्ठा irq_chip पूर्णांकc_dev = अणु
	.name = "Xilinx INTC",
	.irq_unmask = पूर्णांकc_enable_or_unmask,
	.irq_mask = पूर्णांकc_disable_or_mask,
	.irq_ack = पूर्णांकc_ack,
	.irq_mask_ack = पूर्णांकc_mask_ack,
पूर्ण;

अटल अचिन्हित पूर्णांक xपूर्णांकc_get_irq_local(काष्ठा xपूर्णांकc_irq_chip *irqc)
अणु
	अचिन्हित पूर्णांक irq = 0;
	u32 hwirq;

	hwirq = xपूर्णांकc_पढ़ो(irqc, IVR);
	अगर (hwirq != -1U)
		irq = irq_find_mapping(irqc->root_करोमुख्य, hwirq);

	pr_debug("irq-xilinx: hwirq=%d, irq=%d\n", hwirq, irq);

	वापस irq;
पूर्ण

अचिन्हित पूर्णांक xपूर्णांकc_get_irq(व्योम)
अणु
	अचिन्हित पूर्णांक irq = -1;
	u32 hwirq;

	hwirq = xपूर्णांकc_पढ़ो(primary_पूर्णांकc, IVR);
	अगर (hwirq != -1U)
		irq = irq_find_mapping(primary_पूर्णांकc->root_करोमुख्य, hwirq);

	pr_debug("irq-xilinx: hwirq=%d, irq=%d\n", hwirq, irq);

	वापस irq;
पूर्ण

अटल पूर्णांक xपूर्णांकc_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq, irq_hw_number_t hw)
अणु
	काष्ठा xपूर्णांकc_irq_chip *irqc = d->host_data;

	अगर (irqc->पूर्णांकr_mask & BIT(hw)) अणु
		irq_set_chip_and_handler_name(irq, &पूर्णांकc_dev,
					      handle_edge_irq, "edge");
		irq_clear_status_flags(irq, IRQ_LEVEL);
	पूर्ण अन्यथा अणु
		irq_set_chip_and_handler_name(irq, &पूर्णांकc_dev,
					      handle_level_irq, "level");
		irq_set_status_flags(irq, IRQ_LEVEL);
	पूर्ण
	irq_set_chip_data(irq, irqc);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops xपूर्णांकc_irq_करोमुख्य_ops = अणु
	.xlate = irq_करोमुख्य_xlate_onetwocell,
	.map = xपूर्णांकc_map,
पूर्ण;

अटल व्योम xil_पूर्णांकc_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा xपूर्णांकc_irq_chip *irqc;
	u32 pending;

	irqc = irq_data_get_irq_handler_data(&desc->irq_data);
	chained_irq_enter(chip, desc);
	करो अणु
		pending = xपूर्णांकc_get_irq_local(irqc);
		अगर (pending == 0)
			अवरोध;
		generic_handle_irq(pending);
	पूर्ण जबतक (true);
	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक __init xilinx_पूर्णांकc_of_init(काष्ठा device_node *पूर्णांकc,
					     काष्ठा device_node *parent)
अणु
	काष्ठा xपूर्णांकc_irq_chip *irqc;
	पूर्णांक ret, irq;

	irqc = kzalloc(माप(*irqc), GFP_KERNEL);
	अगर (!irqc)
		वापस -ENOMEM;
	irqc->base = of_iomap(पूर्णांकc, 0);
	BUG_ON(!irqc->base);

	ret = of_property_पढ़ो_u32(पूर्णांकc, "xlnx,num-intr-inputs", &irqc->nr_irq);
	अगर (ret < 0) अणु
		pr_err("irq-xilinx: unable to read xlnx,num-intr-inputs\n");
		जाओ error;
	पूर्ण

	ret = of_property_पढ़ो_u32(पूर्णांकc, "xlnx,kind-of-intr", &irqc->पूर्णांकr_mask);
	अगर (ret < 0) अणु
		pr_warn("irq-xilinx: unable to read xlnx,kind-of-intr\n");
		irqc->पूर्णांकr_mask = 0;
	पूर्ण

	अगर (irqc->पूर्णांकr_mask >> irqc->nr_irq)
		pr_warn("irq-xilinx: mismatch in kind-of-intr param\n");

	pr_info("irq-xilinx: %pOF: num_irq=%d, edge=0x%x\n",
		पूर्णांकc, irqc->nr_irq, irqc->पूर्णांकr_mask);


	/*
	 * Disable all बाह्यal पूर्णांकerrupts until they are
	 * explicitly requested.
	 */
	xपूर्णांकc_ग_लिखो(irqc, IER, 0);

	/* Acknowledge any pending पूर्णांकerrupts just in हाल. */
	xपूर्णांकc_ग_लिखो(irqc, IAR, 0xffffffff);

	/* Turn on the Master Enable. */
	xपूर्णांकc_ग_लिखो(irqc, MER, MER_HIE | MER_ME);
	अगर (xपूर्णांकc_पढ़ो(irqc, MER) != (MER_HIE | MER_ME)) अणु
		अटल_branch_enable(&xपूर्णांकc_is_be);
		xपूर्णांकc_ग_लिखो(irqc, MER, MER_HIE | MER_ME);
	पूर्ण

	irqc->root_करोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc, irqc->nr_irq,
						  &xपूर्णांकc_irq_करोमुख्य_ops, irqc);
	अगर (!irqc->root_करोमुख्य) अणु
		pr_err("irq-xilinx: Unable to create IRQ domain\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (parent) अणु
		irq = irq_of_parse_and_map(पूर्णांकc, 0);
		अगर (irq) अणु
			irq_set_chained_handler_and_data(irq,
							 xil_पूर्णांकc_irq_handler,
							 irqc);
		पूर्ण अन्यथा अणु
			pr_err("irq-xilinx: interrupts property not in DT\n");
			ret = -EINVAL;
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		primary_पूर्णांकc = irqc;
		irq_set_शेष_host(primary_पूर्णांकc->root_करोमुख्य);
	पूर्ण

	वापस 0;

error:
	iounmap(irqc->base);
	kमुक्त(irqc);
	वापस ret;

पूर्ण

IRQCHIP_DECLARE(xilinx_पूर्णांकc_xps, "xlnx,xps-intc-1.00.a", xilinx_पूर्णांकc_of_init);
IRQCHIP_DECLARE(xilinx_पूर्णांकc_opb, "xlnx,opb-intc-1.00.c", xilinx_पूर्णांकc_of_init);
