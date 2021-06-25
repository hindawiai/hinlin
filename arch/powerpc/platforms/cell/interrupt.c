<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Cell Internal Interrupt Controller
 *
 * Copyright (C) 2006 Benjamin Herrenschmidt (benh@kernel.crashing.org)
 *                    IBM, Corp.
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 *
 * TODO:
 * - Fix various assumptions related to HW CPU numbers vs. linux CPU numbers
 *   vs node numbers in the setup code
 * - Implement proper handling of maxcpus=1/2 (that is, routing of irqs from
 *   a non-active node to the active node)
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/export.h>
#समावेश <linux/percpu.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cell-regs.h>

#समावेश "interrupt.h"

काष्ठा iic अणु
	काष्ठा cbe_iic_thपढ़ो_regs __iomem *regs;
	u8 target_id;
	u8 eoi_stack[16];
	पूर्णांक eoi_ptr;
	काष्ठा device_node *node;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा iic, cpu_iic);
#घोषणा IIC_NODE_COUNT	2
अटल काष्ठा irq_करोमुख्य *iic_host;

/* Convert between "pending" bits and hw irq number */
अटल irq_hw_number_t iic_pending_to_hwnum(काष्ठा cbe_iic_pending_bits bits)
अणु
	अचिन्हित अक्षर unit = bits.source & 0xf;
	अचिन्हित अक्षर node = bits.source >> 4;
	अचिन्हित अक्षर class = bits.class & 3;

	/* Decode IPIs */
	अगर (bits.flags & CBE_IIC_IRQ_IPI)
		वापस IIC_IRQ_TYPE_IPI | (bits.prio >> 4);
	अन्यथा
		वापस (node << IIC_IRQ_NODE_SHIFT) | (class << 4) | unit;
पूर्ण

अटल व्योम iic_mask(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम iic_unmask(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम iic_eoi(काष्ठा irq_data *d)
अणु
	काष्ठा iic *iic = this_cpu_ptr(&cpu_iic);
	out_be64(&iic->regs->prio, iic->eoi_stack[--iic->eoi_ptr]);
	BUG_ON(iic->eoi_ptr < 0);
पूर्ण

अटल काष्ठा irq_chip iic_chip = अणु
	.name = "CELL-IIC",
	.irq_mask = iic_mask,
	.irq_unmask = iic_unmask,
	.irq_eoi = iic_eoi,
पूर्ण;


अटल व्योम iic_ioexc_eoi(काष्ठा irq_data *d)
अणु
पूर्ण

अटल व्योम iic_ioexc_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा cbe_iic_regs __iomem *node_iic =
		(व्योम __iomem *)irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);
	अचिन्हित पूर्णांक base = (irq & 0xffffff00) | IIC_IRQ_TYPE_IOEXC;
	अचिन्हित दीर्घ bits, ack;
	पूर्णांक cascade;

	क्रम (;;) अणु
		bits = in_be64(&node_iic->iic_is);
		अगर (bits == 0)
			अवरोध;
		/* pre-ack edge पूर्णांकerrupts */
		ack = bits & IIC_ISR_EDGE_MASK;
		अगर (ack)
			out_be64(&node_iic->iic_is, ack);
		/* handle them */
		क्रम (cascade = 63; cascade >= 0; cascade--)
			अगर (bits & (0x8000000000000000UL >> cascade)) अणु
				अचिन्हित पूर्णांक cirq =
					irq_linear_revmap(iic_host,
							  base | cascade);
				अगर (cirq)
					generic_handle_irq(cirq);
			पूर्ण
		/* post-ack level पूर्णांकerrupts */
		ack = bits & ~IIC_ISR_EDGE_MASK;
		अगर (ack)
			out_be64(&node_iic->iic_is, ack);
	पूर्ण
	chip->irq_eoi(&desc->irq_data);
पूर्ण


अटल काष्ठा irq_chip iic_ioexc_chip = अणु
	.name = "CELL-IOEX",
	.irq_mask = iic_mask,
	.irq_unmask = iic_unmask,
	.irq_eoi = iic_ioexc_eoi,
पूर्ण;

/* Get an IRQ number from the pending state रेजिस्टर of the IIC */
अटल अचिन्हित पूर्णांक iic_get_irq(व्योम)
अणु
	काष्ठा cbe_iic_pending_bits pending;
	काष्ठा iic *iic;
	अचिन्हित पूर्णांक virq;

	iic = this_cpu_ptr(&cpu_iic);
	*(अचिन्हित दीर्घ *) &pending =
		in_be64((u64 __iomem *) &iic->regs->pending_destr);
	अगर (!(pending.flags & CBE_IIC_IRQ_VALID))
		वापस 0;
	virq = irq_linear_revmap(iic_host, iic_pending_to_hwnum(pending));
	अगर (!virq)
		वापस 0;
	iic->eoi_stack[++iic->eoi_ptr] = pending.prio;
	BUG_ON(iic->eoi_ptr > 15);
	वापस virq;
पूर्ण

व्योम iic_setup_cpu(व्योम)
अणु
	out_be64(&this_cpu_ptr(&cpu_iic)->regs->prio, 0xff);
पूर्ण

u8 iic_get_target_id(पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_iic, cpu).target_id;
पूर्ण

EXPORT_SYMBOL_GPL(iic_get_target_id);

#अगर_घोषित CONFIG_SMP

/* Use the highest पूर्णांकerrupt priorities क्रम IPI */
अटल अंतरभूत पूर्णांक iic_msg_to_irq(पूर्णांक msg)
अणु
	वापस IIC_IRQ_TYPE_IPI + 0xf - msg;
पूर्ण

व्योम iic_message_pass(पूर्णांक cpu, पूर्णांक msg)
अणु
	out_be64(&per_cpu(cpu_iic, cpu).regs->generate, (0xf - msg) << 4);
पूर्ण

अटल व्योम iic_request_ipi(पूर्णांक msg)
अणु
	पूर्णांक virq;

	virq = irq_create_mapping(iic_host, iic_msg_to_irq(msg));
	अगर (!virq) अणु
		prपूर्णांकk(KERN_ERR
		       "iic: failed to map IPI %s\n", smp_ipi_name[msg]);
		वापस;
	पूर्ण

	/*
	 * If smp_request_message_ipi encounters an error it will notअगरy
	 * the error.  If a message is not needed it will वापस non-zero.
	 */
	अगर (smp_request_message_ipi(virq, msg))
		irq_dispose_mapping(virq);
पूर्ण

व्योम iic_request_IPIs(व्योम)
अणु
	iic_request_ipi(PPC_MSG_CALL_FUNCTION);
	iic_request_ipi(PPC_MSG_RESCHEDULE);
	iic_request_ipi(PPC_MSG_TICK_BROADCAST);
	iic_request_ipi(PPC_MSG_NMI_IPI);
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */


अटल पूर्णांक iic_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
			  क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	वापस of_device_is_compatible(node,
				    "IBM,CBEA-Internal-Interrupt-Controller");
पूर्ण

अटल पूर्णांक iic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			irq_hw_number_t hw)
अणु
	चयन (hw & IIC_IRQ_TYPE_MASK) अणु
	हाल IIC_IRQ_TYPE_IPI:
		irq_set_chip_and_handler(virq, &iic_chip, handle_percpu_irq);
		अवरोध;
	हाल IIC_IRQ_TYPE_IOEXC:
		irq_set_chip_and_handler(virq, &iic_ioexc_chip,
					 handle_edge_eoi_irq);
		अवरोध;
	शेष:
		irq_set_chip_and_handler(virq, &iic_chip, handle_edge_eoi_irq);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iic_host_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
			   स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			   irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)

अणु
	अचिन्हित पूर्णांक node, ext, unit, class;
	स्थिर u32 *val;

	अगर (!of_device_is_compatible(ct,
				     "IBM,CBEA-Internal-Interrupt-Controller"))
		वापस -ENODEV;
	अगर (पूर्णांकsize != 1)
		वापस -ENODEV;
	val = of_get_property(ct, "#interrupt-cells", शून्य);
	अगर (val == शून्य || *val != 1)
		वापस -ENODEV;

	node = पूर्णांकspec[0] >> 24;
	ext = (पूर्णांकspec[0] >> 16) & 0xff;
	class = (पूर्णांकspec[0] >> 8) & 0xff;
	unit = पूर्णांकspec[0] & 0xff;

	/* Check अगर node is in supported range */
	अगर (node > 1)
		वापस -EINVAL;

	/* Build up पूर्णांकerrupt number, special हाल क्रम IO exceptions */
	*out_hwirq = (node << IIC_IRQ_NODE_SHIFT);
	अगर (unit == IIC_UNIT_IIC && class == 1)
		*out_hwirq |= IIC_IRQ_TYPE_IOEXC | ext;
	अन्यथा
		*out_hwirq |= IIC_IRQ_TYPE_NORMAL |
			(class << IIC_IRQ_CLASS_SHIFT) | unit;

	/* Dummy flags, ignored by iic code */
	*out_flags = IRQ_TYPE_EDGE_RISING;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops iic_host_ops = अणु
	.match = iic_host_match,
	.map = iic_host_map,
	.xlate = iic_host_xlate,
पूर्ण;

अटल व्योम __init init_one_iic(अचिन्हित पूर्णांक hw_cpu, अचिन्हित दीर्घ addr,
				काष्ठा device_node *node)
अणु
	/* XXX FIXME: should locate the linux CPU number from the HW cpu
	 * number properly. We are lucky क्रम now
	 */
	काष्ठा iic *iic = &per_cpu(cpu_iic, hw_cpu);

	iic->regs = ioremap(addr, माप(काष्ठा cbe_iic_thपढ़ो_regs));
	BUG_ON(iic->regs == शून्य);

	iic->target_id = ((hw_cpu & 2) << 3) | ((hw_cpu & 1) ? 0xf : 0xe);
	iic->eoi_stack[0] = 0xff;
	iic->node = of_node_get(node);
	out_be64(&iic->regs->prio, 0);

	prपूर्णांकk(KERN_INFO "IIC for CPU %d target id 0x%x : %pOF\n",
	       hw_cpu, iic->target_id, node);
पूर्ण

अटल पूर्णांक __init setup_iic(व्योम)
अणु
	काष्ठा device_node *dn;
	काष्ठा resource r0, r1;
	अचिन्हित पूर्णांक node, cascade, found = 0;
	काष्ठा cbe_iic_regs __iomem *node_iic;
	स्थिर u32 *np;

	क्रम_each_node_by_name(dn, "interrupt-controller") अणु
		अगर (!of_device_is_compatible(dn,
				     "IBM,CBEA-Internal-Interrupt-Controller"))
			जारी;
		np = of_get_property(dn, "ibm,interrupt-server-ranges", शून्य);
		अगर (np == शून्य) अणु
			prपूर्णांकk(KERN_WARNING "IIC: CPU association not found\n");
			of_node_put(dn);
			वापस -ENODEV;
		पूर्ण
		अगर (of_address_to_resource(dn, 0, &r0) ||
		    of_address_to_resource(dn, 1, &r1)) अणु
			prपूर्णांकk(KERN_WARNING "IIC: Can't resolve addresses\n");
			of_node_put(dn);
			वापस -ENODEV;
		पूर्ण
		found++;
		init_one_iic(np[0], r0.start, dn);
		init_one_iic(np[1], r1.start, dn);

		/* Setup cascade क्रम IO exceptions. XXX cleanup tricks to get
		 * node vs CPU etc...
		 * Note that we configure the IIC_IRR here with a hard coded
		 * priority of 1. We might want to improve that later.
		 */
		node = np[0] >> 1;
		node_iic = cbe_get_cpu_iic_regs(np[0]);
		cascade = node << IIC_IRQ_NODE_SHIFT;
		cascade |= 1 << IIC_IRQ_CLASS_SHIFT;
		cascade |= IIC_UNIT_IIC;
		cascade = irq_create_mapping(iic_host, cascade);
		अगर (!cascade)
			जारी;
		/*
		 * irq_data is a generic poपूर्णांकer that माला_लो passed back
		 * to us later, so the क्रमced cast is fine.
		 */
		irq_set_handler_data(cascade, (व्योम __क्रमce *)node_iic);
		irq_set_chained_handler(cascade, iic_ioexc_cascade);
		out_be64(&node_iic->iic_ir,
			 (1 << 12)		/* priority */ |
			 (node << 4)		/* dest node */ |
			 IIC_UNIT_THREAD_0	/* route them to thपढ़ो 0 */);
		/* Flush pending (make sure it triggers अगर there is
		 * anything pending
		 */
		out_be64(&node_iic->iic_is, 0xfffffffffffffffful);
	पूर्ण

	अगर (found)
		वापस 0;
	अन्यथा
		वापस -ENODEV;
पूर्ण

व्योम __init iic_init_IRQ(व्योम)
अणु
	/* Setup an irq host data काष्ठाure */
	iic_host = irq_करोमुख्य_add_linear(शून्य, IIC_SOURCE_COUNT, &iic_host_ops,
					 शून्य);
	BUG_ON(iic_host == शून्य);
	irq_set_शेष_host(iic_host);

	/* Discover and initialize iics */
	अगर (setup_iic() < 0)
		panic("IIC: Failed to initialize !\n");

	/* Set master पूर्णांकerrupt handling function */
	ppc_md.get_irq = iic_get_irq;

	/* Enable on current CPU */
	iic_setup_cpu();
पूर्ण

व्योम iic_set_पूर्णांकerrupt_routing(पूर्णांक cpu, पूर्णांक thपढ़ो, पूर्णांक priority)
अणु
	काष्ठा cbe_iic_regs __iomem *iic_regs = cbe_get_cpu_iic_regs(cpu);
	u64 iic_ir = 0;
	पूर्णांक node = cpu >> 1;

	/* Set which node and thपढ़ो will handle the next पूर्णांकerrupt */
	iic_ir |= CBE_IIC_IR_PRIO(priority) |
		  CBE_IIC_IR_DEST_NODE(node);
	अगर (thपढ़ो == 0)
		iic_ir |= CBE_IIC_IR_DEST_UNIT(CBE_IIC_IR_PT_0);
	अन्यथा
		iic_ir |= CBE_IIC_IR_DEST_UNIT(CBE_IIC_IR_PT_1);
	out_be64(&iic_regs->iic_ir, iic_ir);
पूर्ण
