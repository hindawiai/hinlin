<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PQ2 ADS-style PCI पूर्णांकerrupt controller
 *
 * Copyright 2007 Freescale Semiconductor, Inc.
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Loosely based on mpc82xx ADS support by Vitaly Bordug <vbordug@ru.mvista.com>
 * Copyright (c) 2006 MontaVista Software, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irq.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/cpm2.h>

#समावेश "pq2.h"

अटल DEFINE_RAW_SPINLOCK(pci_pic_lock);

काष्ठा pq2ads_pci_pic अणु
	काष्ठा device_node *node;
	काष्ठा irq_करोमुख्य *host;

	काष्ठा अणु
		u32 stat;
		u32 mask;
	पूर्ण __iomem *regs;
पूर्ण;

#घोषणा NUM_IRQS 32

अटल व्योम pq2ads_pci_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा pq2ads_pci_pic *priv = irq_data_get_irq_chip_data(d);
	पूर्णांक irq = NUM_IRQS - irqd_to_hwirq(d) - 1;

	अगर (irq != -1) अणु
		अचिन्हित दीर्घ flags;
		raw_spin_lock_irqsave(&pci_pic_lock, flags);

		setbits32(&priv->regs->mask, 1 << irq);
		mb();

		raw_spin_unlock_irqrestore(&pci_pic_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम pq2ads_pci_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा pq2ads_pci_pic *priv = irq_data_get_irq_chip_data(d);
	पूर्णांक irq = NUM_IRQS - irqd_to_hwirq(d) - 1;

	अगर (irq != -1) अणु
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&pci_pic_lock, flags);
		clrbits32(&priv->regs->mask, 1 << irq);
		raw_spin_unlock_irqrestore(&pci_pic_lock, flags);
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip pq2ads_pci_ic = अणु
	.name = "PQ2 ADS PCI",
	.irq_mask = pq2ads_pci_mask_irq,
	.irq_mask_ack = pq2ads_pci_mask_irq,
	.irq_ack = pq2ads_pci_mask_irq,
	.irq_unmask = pq2ads_pci_unmask_irq,
	.irq_enable = pq2ads_pci_unmask_irq,
	.irq_disable = pq2ads_pci_mask_irq
पूर्ण;

अटल व्योम pq2ads_pci_irq_demux(काष्ठा irq_desc *desc)
अणु
	काष्ठा pq2ads_pci_pic *priv = irq_desc_get_handler_data(desc);
	u32 stat, mask, pend;
	पूर्णांक bit;

	क्रम (;;) अणु
		stat = in_be32(&priv->regs->stat);
		mask = in_be32(&priv->regs->mask);

		pend = stat & ~mask;

		अगर (!pend)
			अवरोध;

		क्रम (bit = 0; pend != 0; ++bit, pend <<= 1) अणु
			अगर (pend & 0x80000000) अणु
				पूर्णांक virq = irq_linear_revmap(priv->host, bit);
				generic_handle_irq(virq);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pci_pic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			    irq_hw_number_t hw)
अणु
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_data(virq, h->host_data);
	irq_set_chip_and_handler(virq, &pq2ads_pci_ic, handle_level_irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pci_pic_host_ops = अणु
	.map = pci_pic_host_map,
पूर्ण;

पूर्णांक __init pq2ads_pci_init_irq(व्योम)
अणु
	काष्ठा pq2ads_pci_pic *priv;
	काष्ठा irq_करोमुख्य *host;
	काष्ठा device_node *np;
	पूर्णांक ret = -ENODEV;
	पूर्णांक irq;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,pq2ads-pci-pic");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "No pci pic node in device tree.\n");
		जाओ out;
	पूर्ण

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		prपूर्णांकk(KERN_ERR "No interrupt in pci pic node.\n");
		जाओ out_put_node;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ out_unmap_irq;
	पूर्ण

	/* PCI पूर्णांकerrupt controller रेजिस्टरs: status and mask */
	priv->regs = of_iomap(np, 0);
	अगर (!priv->regs) अणु
		prपूर्णांकk(KERN_ERR "Cannot map PCI PIC registers.\n");
		जाओ out_मुक्त_kदो_स्मृति;
	पूर्ण

	/* mask all PCI पूर्णांकerrupts */
	out_be32(&priv->regs->mask, ~0);
	mb();

	host = irq_करोमुख्य_add_linear(np, NUM_IRQS, &pci_pic_host_ops, priv);
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ out_unmap_regs;
	पूर्ण

	priv->host = host;
	irq_set_handler_data(irq, priv);
	irq_set_chained_handler(irq, pq2ads_pci_irq_demux);
	ret = 0;
	जाओ out_put_node;

out_unmap_regs:
	iounmap(priv->regs);
out_मुक्त_kदो_स्मृति:
	kमुक्त(priv);
out_unmap_irq:
	irq_dispose_mapping(irq);
out_put_node:
	of_node_put(np);
out:
	वापस ret;
पूर्ण
