<शैली गुरु>
/*
 * Interrupt handling क्रम GE FPGA based PIC
 *
 * Author: Martyn Welch <martyn.welch@ge.com>
 *
 * 2008 (c) GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/irq.h>

#समावेश "ge_pic.h"

#घोषणा DEBUG
#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) करो अणु prपूर्णांकk(KERN_DEBUG "gef_pic: " fmt); पूर्ण जबतक (0)
#अन्यथा
#घोषणा DBG(fmt...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा GEF_PIC_NUM_IRQS	32

/* Interrupt Controller Interface Registers */
#घोषणा GEF_PIC_INTR_STATUS	0x0000

#घोषणा GEF_PIC_INTR_MASK(cpu)	(0x0010 + (0x4 * cpu))
#घोषणा GEF_PIC_CPU0_INTR_MASK	GEF_PIC_INTR_MASK(0)
#घोषणा GEF_PIC_CPU1_INTR_MASK	GEF_PIC_INTR_MASK(1)

#घोषणा GEF_PIC_MCP_MASK(cpu)	(0x0018 + (0x4 * cpu))
#घोषणा GEF_PIC_CPU0_MCP_MASK	GEF_PIC_MCP_MASK(0)
#घोषणा GEF_PIC_CPU1_MCP_MASK	GEF_PIC_MCP_MASK(1)


अटल DEFINE_RAW_SPINLOCK(gef_pic_lock);

अटल व्योम __iomem *gef_pic_irq_reg_base;
अटल काष्ठा irq_करोमुख्य *gef_pic_irq_host;
अटल पूर्णांक gef_pic_cascade_irq;

/*
 * Interrupt Controller Handling
 *
 * The पूर्णांकerrupt controller handles पूर्णांकerrupts क्रम most on board पूर्णांकerrupts,
 * apart from PCI पूर्णांकerrupts. For example on SBC610:
 *
 * 17:31 RO Reserved
 * 16    RO PCI Express Doorbell 3 Status
 * 15    RO PCI Express Doorbell 2 Status
 * 14    RO PCI Express Doorbell 1 Status
 * 13    RO PCI Express Doorbell 0 Status
 * 12    RO Real Time Clock Interrupt Status
 * 11    RO Temperature Interrupt Status
 * 10    RO Temperature Critical Interrupt Status
 * 9     RO Ethernet PHY1 Interrupt Status
 * 8     RO Ethernet PHY3 Interrupt Status
 * 7     RO PEX8548 Interrupt Status
 * 6     RO Reserved
 * 5     RO Watchकरोg 0 Interrupt Status
 * 4     RO Watchकरोg 1 Interrupt Status
 * 3     RO AXIS Message FIFO A Interrupt Status
 * 2     RO AXIS Message FIFO B Interrupt Status
 * 1     RO AXIS Message FIFO C Interrupt Status
 * 0     RO AXIS Message FIFO D Interrupt Status
 *
 * Interrupts can be क्रमwarded to one of two output lines. Nothing
 * clever is करोne, so अगर the masks are incorrectly set, a single input
 * पूर्णांकerrupt could generate पूर्णांकerrupts on both output lines!
 *
 * The dual lines are there to allow the chained पूर्णांकerrupts to be easily
 * passed पूर्णांकo two dअगरferent cores. We currently करो not use this functionality
 * in this driver.
 *
 * Controller can also be configured to generate Machine checks (MCP), again on
 * two lines, to be attached to two dअगरferent cores. It is suggested that these
 * should be masked out.
 */

अटल व्योम gef_pic_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक cascade_irq;

	/*
	 * See अगर we actually have an पूर्णांकerrupt, call generic handling code अगर
	 * we करो.
	 */
	cascade_irq = gef_pic_get_irq();

	अगर (cascade_irq)
		generic_handle_irq(cascade_irq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण

अटल व्योम gef_pic_mask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);
	u32 mask;

	raw_spin_lock_irqsave(&gef_pic_lock, flags);
	mask = in_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_MASK(0));
	mask &= ~(1 << hwirq);
	out_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_MASK(0), mask);
	raw_spin_unlock_irqrestore(&gef_pic_lock, flags);
पूर्ण

अटल व्योम gef_pic_mask_ack(काष्ठा irq_data *d)
अणु
	/* Don't think we actually have to करो anything to ack an पूर्णांकerrupt,
	 * we just need to clear करोwn the devices पूर्णांकerrupt and it will go away
	 */
	gef_pic_mask(d);
पूर्ण

अटल व्योम gef_pic_unmask(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक hwirq = irqd_to_hwirq(d);
	u32 mask;

	raw_spin_lock_irqsave(&gef_pic_lock, flags);
	mask = in_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_MASK(0));
	mask |= (1 << hwirq);
	out_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_MASK(0), mask);
	raw_spin_unlock_irqrestore(&gef_pic_lock, flags);
पूर्ण

अटल काष्ठा irq_chip gef_pic_chip = अणु
	.name		= "gefp",
	.irq_mask	= gef_pic_mask,
	.irq_mask_ack	= gef_pic_mask_ack,
	.irq_unmask	= gef_pic_unmask,
पूर्ण;


/* When an पूर्णांकerrupt is being configured, this call allows some flexibilty
 * in deciding which irq_chip काष्ठाure is used
 */
अटल पूर्णांक gef_pic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hwirq)
अणु
	/* All पूर्णांकerrupts are LEVEL sensitive */
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &gef_pic_chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक gef_pic_host_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
			    स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			    irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)
अणु

	*out_hwirq = पूर्णांकspec[0];
	अगर (पूर्णांकsize > 1)
		*out_flags = पूर्णांकspec[1];
	अन्यथा
		*out_flags = IRQ_TYPE_LEVEL_HIGH;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops gef_pic_host_ops = अणु
	.map	= gef_pic_host_map,
	.xlate	= gef_pic_host_xlate,
पूर्ण;


/*
 * Initialisation of PIC, this should be called in BSP
 */
व्योम __init gef_pic_init(काष्ठा device_node *np)
अणु
	अचिन्हित दीर्घ flags;

	/* Map the devices रेजिस्टरs पूर्णांकo memory */
	gef_pic_irq_reg_base = of_iomap(np, 0);

	raw_spin_lock_irqsave(&gef_pic_lock, flags);

	/* Initialise everything as masked. */
	out_be32(gef_pic_irq_reg_base + GEF_PIC_CPU0_INTR_MASK, 0);
	out_be32(gef_pic_irq_reg_base + GEF_PIC_CPU1_INTR_MASK, 0);

	out_be32(gef_pic_irq_reg_base + GEF_PIC_CPU0_MCP_MASK, 0);
	out_be32(gef_pic_irq_reg_base + GEF_PIC_CPU1_MCP_MASK, 0);

	raw_spin_unlock_irqrestore(&gef_pic_lock, flags);

	/* Map controller */
	gef_pic_cascade_irq = irq_of_parse_and_map(np, 0);
	अगर (!gef_pic_cascade_irq) अणु
		prपूर्णांकk(KERN_ERR "SBC610: failed to map cascade interrupt");
		वापस;
	पूर्ण

	/* Setup an irq_करोमुख्य काष्ठाure */
	gef_pic_irq_host = irq_करोमुख्य_add_linear(np, GEF_PIC_NUM_IRQS,
					  &gef_pic_host_ops, शून्य);
	अगर (gef_pic_irq_host == शून्य)
		वापस;

	/* Chain with parent controller */
	irq_set_chained_handler(gef_pic_cascade_irq, gef_pic_cascade);
पूर्ण

/*
 * This is called when we receive an पूर्णांकerrupt with apparently comes from this
 * chip - check, वापसing the highest पूर्णांकerrupt generated or वापस 0.
 */
अचिन्हित पूर्णांक gef_pic_get_irq(व्योम)
अणु
	u32 cause, mask, active;
	अचिन्हित पूर्णांक virq = 0;
	पूर्णांक hwirq;

	cause = in_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_STATUS);

	mask = in_be32(gef_pic_irq_reg_base + GEF_PIC_INTR_MASK(0));

	active = cause & mask;

	अगर (active) अणु
		क्रम (hwirq = GEF_PIC_NUM_IRQS - 1; hwirq > -1; hwirq--) अणु
			अगर (active & (0x1 << hwirq))
				अवरोध;
		पूर्ण
		virq = irq_linear_revmap(gef_pic_irq_host,
			(irq_hw_number_t)hwirq);
	पूर्ण

	वापस virq;
पूर्ण

