<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2008 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: John Rigby, <jrigby@मुक्तscale.com>
 *
 * Description:
 * MPC5121ADS CPLD irq handling
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/prom.h>

अटल काष्ठा device_node *cpld_pic_node;
अटल काष्ठा irq_करोमुख्य *cpld_pic_host;

/*
 * Bits to ignore in the misc_status रेजिस्टर
 * 0x10 touch screen penकरोwn is hard routed to irq1
 * 0x02 pci status is पढ़ो from pci status रेजिस्टर
 */
#घोषणा MISC_IGNORE 0x12

/*
 * Nothing to ignore in pci status रेजिस्टर
 */
#घोषणा PCI_IGNORE 0x00

काष्ठा cpld_pic अणु
	u8 pci_mask;
	u8 pci_status;
	u8 route;
	u8 misc_mask;
	u8 misc_status;
	u8 misc_control;
पूर्ण;

अटल काष्ठा cpld_pic __iomem *cpld_regs;

अटल व्योम __iomem *
irq_to_pic_mask(अचिन्हित पूर्णांक irq)
अणु
	वापस irq <= 7 ? &cpld_regs->pci_mask : &cpld_regs->misc_mask;
पूर्ण

अटल अचिन्हित पूर्णांक
irq_to_pic_bit(अचिन्हित पूर्णांक irq)
अणु
	वापस 1 << (irq & 0x7);
पूर्ण

अटल व्योम
cpld_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक cpld_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	व्योम __iomem *pic_mask = irq_to_pic_mask(cpld_irq);

	out_8(pic_mask,
	      in_8(pic_mask) | irq_to_pic_bit(cpld_irq));
पूर्ण

अटल व्योम
cpld_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक cpld_irq = (अचिन्हित पूर्णांक)irqd_to_hwirq(d);
	व्योम __iomem *pic_mask = irq_to_pic_mask(cpld_irq);

	out_8(pic_mask,
	      in_8(pic_mask) & ~irq_to_pic_bit(cpld_irq));
पूर्ण

अटल काष्ठा irq_chip cpld_pic = अणु
	.name = "CPLD PIC",
	.irq_mask = cpld_mask_irq,
	.irq_ack = cpld_mask_irq,
	.irq_unmask = cpld_unmask_irq,
पूर्ण;

अटल पूर्णांक
cpld_pic_get_irq(पूर्णांक offset, u8 ignore, u8 __iomem *statusp,
			    u8 __iomem *maskp)
अणु
	पूर्णांक cpld_irq;
	u8 status = in_8(statusp);
	u8 mask = in_8(maskp);

	/* ignore करोn't cares and masked irqs */
	status |= (ignore | mask);

	अगर (status == 0xff)
		वापस 0;

	cpld_irq = ffz(status) + offset;

	वापस irq_linear_revmap(cpld_pic_host, cpld_irq);
पूर्ण

अटल व्योम cpld_pic_cascade(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq;

	irq = cpld_pic_get_irq(0, PCI_IGNORE, &cpld_regs->pci_status,
		&cpld_regs->pci_mask);
	अगर (irq) अणु
		generic_handle_irq(irq);
		वापस;
	पूर्ण

	irq = cpld_pic_get_irq(8, MISC_IGNORE, &cpld_regs->misc_status,
		&cpld_regs->misc_mask);
	अगर (irq) अणु
		generic_handle_irq(irq);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक
cpld_pic_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
		    क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	वापस cpld_pic_node == node;
पूर्ण

अटल पूर्णांक
cpld_pic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			     irq_hw_number_t hw)
अणु
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &cpld_pic, handle_level_irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops cpld_pic_host_ops = अणु
	.match = cpld_pic_host_match,
	.map = cpld_pic_host_map,
पूर्ण;

व्योम __init
mpc5121_ads_cpld_map(व्योम)
अणु
	काष्ठा device_node *np = शून्य;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121ads-cpld-pic");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "CPLD PIC init: can not find cpld-pic node\n");
		वापस;
	पूर्ण

	cpld_regs = of_iomap(np, 0);
	of_node_put(np);
पूर्ण

व्योम __init
mpc5121_ads_cpld_pic_init(व्योम)
अणु
	अचिन्हित पूर्णांक cascade_irq;
	काष्ठा device_node *np = शून्य;

	pr_debug("cpld_ic_init\n");

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121ads-cpld-pic");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "CPLD PIC init: can not find cpld-pic node\n");
		वापस;
	पूर्ण

	अगर (!cpld_regs)
		जाओ end;

	cascade_irq = irq_of_parse_and_map(np, 0);
	अगर (!cascade_irq)
		जाओ end;

	/*
	 * अटलally route touch screen penकरोwn through 1
	 * and ignore it here
	 * route all others through our cascade irq
	 */
	out_8(&cpld_regs->route, 0xfd);
	out_8(&cpld_regs->pci_mask, 0xff);
	/* unmask pci पूर्णांकs in misc mask */
	out_8(&cpld_regs->misc_mask, ~(MISC_IGNORE));

	cpld_pic_node = of_node_get(np);

	cpld_pic_host = irq_करोमुख्य_add_linear(np, 16, &cpld_pic_host_ops, शून्य);
	अगर (!cpld_pic_host) अणु
		prपूर्णांकk(KERN_ERR "CPLD PIC: failed to allocate irq host!\n");
		जाओ end;
	पूर्ण

	irq_set_chained_handler(cascade_irq, cpld_pic_cascade);
end:
	of_node_put(np);
पूर्ण
