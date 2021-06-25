<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Interrupt management क्रम most GSC and related devices.
 *
 * (c) Copyright 1999 Alex deVries क्रम The Puffin Group
 * (c) Copyright 1999 Grant Grundler क्रम Hewlett-Packard
 * (c) Copyright 1999 Matthew Wilcox
 * (c) Copyright 2000 Helge Deller
 * (c) Copyright 2001 Matthew Wilcox क्रम Hewlett-Packard
 */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/पन.स>

#समावेश "gsc.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DEBPRINTK prपूर्णांकk
#अन्यथा
#घोषणा DEBPRINTK(x,...)
#पूर्ण_अगर

पूर्णांक gsc_alloc_irq(काष्ठा gsc_irq *i)
अणु
	पूर्णांक irq = txn_alloc_irq(GSC_EIM_WIDTH);
	अगर (irq < 0) अणु
		prपूर्णांकk("cannot get irq\n");
		वापस irq;
	पूर्ण

	i->txn_addr = txn_alloc_addr(irq);
	i->txn_data = txn_alloc_data(irq);
	i->irq = irq;

	वापस irq;
पूर्ण

पूर्णांक gsc_claim_irq(काष्ठा gsc_irq *i, पूर्णांक irq)
अणु
	पूर्णांक c = irq;

	irq += CPU_IRQ_BASE; /* भवize the IRQ first */

	irq = txn_claim_irq(irq);
	अगर (irq < 0) अणु
		prपूर्णांकk("cannot claim irq %d\n", c);
		वापस irq;
	पूर्ण

	i->txn_addr = txn_alloc_addr(irq);
	i->txn_data = txn_alloc_data(irq);
	i->irq = irq;

	वापस irq;
पूर्ण

EXPORT_SYMBOL(gsc_alloc_irq);
EXPORT_SYMBOL(gsc_claim_irq);

/* Common पूर्णांकerrupt demultiplexer used by Asp, Lasi & Wax.  */
irqवापस_t gsc_asic_पूर्णांकr(पूर्णांक gsc_asic_irq, व्योम *dev)
अणु
	अचिन्हित दीर्घ irr;
	काष्ठा gsc_asic *gsc_asic = dev;

	irr = gsc_पढ़ोl(gsc_asic->hpa + OFFSET_IRR);
	अगर (irr == 0)
		वापस IRQ_NONE;

	DEBPRINTK("%s intr, mask=0x%x\n", gsc_asic->name, irr);

	करो अणु
		पूर्णांक local_irq = __ffs(irr);
		अचिन्हित पूर्णांक irq = gsc_asic->global_irq[local_irq];
		generic_handle_irq(irq);
		irr &= ~(1 << local_irq);
	पूर्ण जबतक (irr);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक gsc_find_local_irq(अचिन्हित पूर्णांक irq, पूर्णांक *global_irqs, पूर्णांक limit)
अणु
	पूर्णांक local_irq;

	क्रम (local_irq = 0; local_irq < limit; local_irq++) अणु
		अगर (global_irqs[local_irq] == irq)
			वापस local_irq;
	पूर्ण

	वापस NO_IRQ;
पूर्ण

अटल व्योम gsc_asic_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gsc_asic *irq_dev = irq_data_get_irq_chip_data(d);
	पूर्णांक local_irq = gsc_find_local_irq(d->irq, irq_dev->global_irq, 32);
	u32 imr;

	DEBPRINTK(KERN_DEBUG "%s(%d) %s: IMR 0x%x\n", __func__, d->irq,
			irq_dev->name, imr);

	/* Disable the IRQ line by clearing the bit in the IMR */
	imr = gsc_पढ़ोl(irq_dev->hpa + OFFSET_IMR);
	imr &= ~(1 << local_irq);
	gsc_ग_लिखोl(imr, irq_dev->hpa + OFFSET_IMR);
पूर्ण

अटल व्योम gsc_asic_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा gsc_asic *irq_dev = irq_data_get_irq_chip_data(d);
	पूर्णांक local_irq = gsc_find_local_irq(d->irq, irq_dev->global_irq, 32);
	u32 imr;

	DEBPRINTK(KERN_DEBUG "%s(%d) %s: IMR 0x%x\n", __func__, d->irq,
			irq_dev->name, imr);

	/* Enable the IRQ line by setting the bit in the IMR */
	imr = gsc_पढ़ोl(irq_dev->hpa + OFFSET_IMR);
	imr |= 1 << local_irq;
	gsc_ग_लिखोl(imr, irq_dev->hpa + OFFSET_IMR);
	/*
	 * FIXME: पढ़ो IPR to make sure the IRQ isn't alपढ़ोy pending.
	 *   If so, we need to पढ़ो IRR and manually call करो_irq().
	 */
पूर्ण

अटल काष्ठा irq_chip gsc_asic_पूर्णांकerrupt_type = अणु
	.name		=	"GSC-ASIC",
	.irq_unmask	=	gsc_asic_unmask_irq,
	.irq_mask	=	gsc_asic_mask_irq,
पूर्ण;

पूर्णांक gsc_assign_irq(काष्ठा irq_chip *type, व्योम *data)
अणु
	अटल पूर्णांक irq = GSC_IRQ_BASE;

	अगर (irq > GSC_IRQ_MAX)
		वापस NO_IRQ;

	irq_set_chip_and_handler(irq, type, handle_simple_irq);
	irq_set_chip_data(irq, data);

	वापस irq++;
पूर्ण

व्योम gsc_asic_assign_irq(काष्ठा gsc_asic *asic, पूर्णांक local_irq, पूर्णांक *irqp)
अणु
	पूर्णांक irq = asic->global_irq[local_irq];
	
	अगर (irq <= 0) अणु
		irq = gsc_assign_irq(&gsc_asic_पूर्णांकerrupt_type, asic);
		अगर (irq == NO_IRQ)
			वापस;

		asic->global_irq[local_irq] = irq;
	पूर्ण
	*irqp = irq;
पूर्ण

काष्ठा gsc_fixup_काष्ठा अणु
	व्योम (*choose_irq)(काष्ठा parisc_device *, व्योम *);
	व्योम *ctrl;
पूर्ण;

अटल पूर्णांक gsc_fixup_irqs_callback(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा parisc_device *padev = to_parisc_device(dev);
	काष्ठा gsc_fixup_काष्ठा *gf = data;

	/* work-around क्रम 715/64 and others which have parent
	   at path [5] and children at path [5/0/x] */
	अगर (padev->id.hw_type == HPHW_FAULTY)
		gsc_fixup_irqs(padev, gf->ctrl, gf->choose_irq);
	gf->choose_irq(padev, gf->ctrl);

	वापस 0;
पूर्ण

व्योम gsc_fixup_irqs(काष्ठा parisc_device *parent, व्योम *ctrl,
			व्योम (*choose_irq)(काष्ठा parisc_device *, व्योम *))
अणु
	काष्ठा gsc_fixup_काष्ठा data = अणु
		.choose_irq	= choose_irq,
		.ctrl		= ctrl,
	पूर्ण;

	device_क्रम_each_child(&parent->dev, &data, gsc_fixup_irqs_callback);
पूर्ण

पूर्णांक gsc_common_setup(काष्ठा parisc_device *parent, काष्ठा gsc_asic *gsc_asic)
अणु
	काष्ठा resource *res;
	पूर्णांक i;

	gsc_asic->gsc = parent;

	/* Initialise local irq -> global irq mapping */
	क्रम (i = 0; i < 32; i++) अणु
		gsc_asic->global_irq[i] = NO_IRQ;
	पूर्ण

	/* allocate resource region */
	res = request_mem_region(gsc_asic->hpa, 0x100000, gsc_asic->name);
	अगर (res) अणु
		res->flags = IORESOURCE_MEM; 	/* करो not mark it busy ! */
	पूर्ण

#अगर 0
	prपूर्णांकk(KERN_WARNING "%s IRQ %d EIM 0x%x", gsc_asic->name,
			parent->irq, gsc_asic->eim);
	अगर (gsc_पढ़ोl(gsc_asic->hpa + OFFSET_IMR))
		prपूर्णांकk("  IMR is non-zero! (0x%x)",
				gsc_पढ़ोl(gsc_asic->hpa + OFFSET_IMR));
	prपूर्णांकk("\n");
#पूर्ण_अगर

	वापस 0;
पूर्ण

बाह्य काष्ठा parisc_driver lasi_driver;
बाह्य काष्ठा parisc_driver asp_driver;
बाह्य काष्ठा parisc_driver wax_driver;

व्योम __init gsc_init(व्योम)
अणु
#अगर_घोषित CONFIG_GSC_LASI
	रेजिस्टर_parisc_driver(&lasi_driver);
	रेजिस्टर_parisc_driver(&asp_driver);
#पूर्ण_अगर
#अगर_घोषित CONFIG_GSC_WAX
	रेजिस्टर_parisc_driver(&wax_driver);
#पूर्ण_अगर
पूर्ण
