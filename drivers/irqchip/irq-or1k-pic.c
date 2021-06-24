<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * Copyright (C) 2014 Stefan Kristansson <stefan.kristiansson@saunalahti.fi>
 */

#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>

/* OR1K PIC implementation */

काष्ठा or1k_pic_dev अणु
	काष्ठा irq_chip chip;
	irq_flow_handler_t handle;
	अचिन्हित दीर्घ flags;
पूर्ण;

/*
 * We're a couple of cycles faster than the generic implementations with
 * these 'fast' versions.
 */

अटल व्योम or1k_pic_mask(काष्ठा irq_data *data)
अणु
	mtspr(SPR_PICMR, mfspr(SPR_PICMR) & ~(1UL << data->hwirq));
पूर्ण

अटल व्योम or1k_pic_unmask(काष्ठा irq_data *data)
अणु
	mtspr(SPR_PICMR, mfspr(SPR_PICMR) | (1UL << data->hwirq));
पूर्ण

अटल व्योम or1k_pic_ack(काष्ठा irq_data *data)
अणु
	mtspr(SPR_PICSR, (1UL << data->hwirq));
पूर्ण

अटल व्योम or1k_pic_mask_ack(काष्ठा irq_data *data)
अणु
	mtspr(SPR_PICMR, mfspr(SPR_PICMR) & ~(1UL << data->hwirq));
	mtspr(SPR_PICSR, (1UL << data->hwirq));
पूर्ण

/*
 * There are two oddities with the OR1200 PIC implementation:
 * i)  LEVEL-triggered पूर्णांकerrupts are latched and need to be cleared
 * ii) the पूर्णांकerrupt latch is cleared by writing a 0 to the bit,
 *     as opposed to a 1 as mandated by the spec
 */
अटल व्योम or1k_pic_or1200_ack(काष्ठा irq_data *data)
अणु
	mtspr(SPR_PICSR, mfspr(SPR_PICSR) & ~(1UL << data->hwirq));
पूर्ण

अटल व्योम or1k_pic_or1200_mask_ack(काष्ठा irq_data *data)
अणु
	mtspr(SPR_PICMR, mfspr(SPR_PICMR) & ~(1UL << data->hwirq));
	mtspr(SPR_PICSR, mfspr(SPR_PICSR) & ~(1UL << data->hwirq));
पूर्ण

अटल काष्ठा or1k_pic_dev or1k_pic_level = अणु
	.chip = अणु
		.name = "or1k-PIC-level",
		.irq_unmask = or1k_pic_unmask,
		.irq_mask = or1k_pic_mask,
		.irq_mask_ack = or1k_pic_mask_ack,
	पूर्ण,
	.handle = handle_level_irq,
	.flags = IRQ_LEVEL | IRQ_NOPROBE,
पूर्ण;

अटल काष्ठा or1k_pic_dev or1k_pic_edge = अणु
	.chip = अणु
		.name = "or1k-PIC-edge",
		.irq_unmask = or1k_pic_unmask,
		.irq_mask = or1k_pic_mask,
		.irq_ack = or1k_pic_ack,
		.irq_mask_ack = or1k_pic_mask_ack,
	पूर्ण,
	.handle = handle_edge_irq,
	.flags = IRQ_LEVEL | IRQ_NOPROBE,
पूर्ण;

अटल काष्ठा or1k_pic_dev or1k_pic_or1200 = अणु
	.chip = अणु
		.name = "or1200-PIC",
		.irq_unmask = or1k_pic_unmask,
		.irq_mask = or1k_pic_mask,
		.irq_ack = or1k_pic_or1200_ack,
		.irq_mask_ack = or1k_pic_or1200_mask_ack,
	पूर्ण,
	.handle = handle_level_irq,
	.flags = IRQ_LEVEL | IRQ_NOPROBE,
पूर्ण;

अटल काष्ठा irq_करोमुख्य *root_करोमुख्य;

अटल अंतरभूत पूर्णांक pic_get_irq(पूर्णांक first)
अणु
	पूर्णांक hwirq;

	hwirq = ffs(mfspr(SPR_PICSR) >> first);
	अगर (!hwirq)
		वापस NO_IRQ;
	अन्यथा
		hwirq = hwirq + first - 1;

	वापस hwirq;
पूर्ण

अटल व्योम or1k_pic_handle_irq(काष्ठा pt_regs *regs)
अणु
	पूर्णांक irq = -1;

	जबतक ((irq = pic_get_irq(irq + 1)) != NO_IRQ)
		handle_करोमुख्य_irq(root_करोमुख्य, irq, regs);
पूर्ण

अटल पूर्णांक or1k_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq, irq_hw_number_t hw)
अणु
	काष्ठा or1k_pic_dev *pic = d->host_data;

	irq_set_chip_and_handler(irq, &pic->chip, pic->handle);
	irq_set_status_flags(irq, pic->flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops or1k_irq_करोमुख्य_ops = अणु
	.xlate = irq_करोमुख्य_xlate_onecell,
	.map = or1k_map,
पूर्ण;

/*
 * This sets up the IRQ करोमुख्य क्रम the PIC built in to the OpenRISC
 * 1000 CPU.  This is the "root" करोमुख्य as these are the पूर्णांकerrupts
 * that directly trigger an exception in the CPU.
 */
अटल पूर्णांक __init or1k_pic_init(काष्ठा device_node *node,
				 काष्ठा or1k_pic_dev *pic)
अणु
	/* Disable all पूर्णांकerrupts until explicitly requested */
	mtspr(SPR_PICMR, (0UL));

	root_करोमुख्य = irq_करोमुख्य_add_linear(node, 32, &or1k_irq_करोमुख्य_ops,
					    pic);

	set_handle_irq(or1k_pic_handle_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __init or1k_pic_or1200_init(काष्ठा device_node *node,
				       काष्ठा device_node *parent)
अणु
	वापस or1k_pic_init(node, &or1k_pic_or1200);
पूर्ण
IRQCHIP_DECLARE(or1k_pic_or1200, "opencores,or1200-pic", or1k_pic_or1200_init);
IRQCHIP_DECLARE(or1k_pic, "opencores,or1k-pic", or1k_pic_or1200_init);

अटल पूर्णांक __init or1k_pic_level_init(काष्ठा device_node *node,
				      काष्ठा device_node *parent)
अणु
	वापस or1k_pic_init(node, &or1k_pic_level);
पूर्ण
IRQCHIP_DECLARE(or1k_pic_level, "opencores,or1k-pic-level",
		or1k_pic_level_init);

अटल पूर्णांक __init or1k_pic_edge_init(काष्ठा device_node *node,
				     काष्ठा device_node *parent)
अणु
	वापस or1k_pic_init(node, &or1k_pic_edge);
पूर्ण
IRQCHIP_DECLARE(or1k_pic_edge, "opencores,or1k-pic-edge", or1k_pic_edge_init);
