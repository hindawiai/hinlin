<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/sysdev/uic.c
 *
 * IBM PowerPC 4xx Universal Interrupt Controller
 *
 * Copyright 2007 David Gibson <dwg@au1.ibm.com>, IBM Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/dcr.h>

#घोषणा NR_UIC_INTS	32

#घोषणा UIC_SR		0x0
#घोषणा UIC_ER		0x2
#घोषणा UIC_CR		0x3
#घोषणा UIC_PR		0x4
#घोषणा UIC_TR		0x5
#घोषणा UIC_MSR		0x6
#घोषणा UIC_VR		0x7
#घोषणा UIC_VCR		0x8

काष्ठा uic *primary_uic;

काष्ठा uic अणु
	पूर्णांक index;
	पूर्णांक dcrbase;

	raw_spinlock_t lock;

	/* The remapper क्रम this UIC */
	काष्ठा irq_करोमुख्य	*irqhost;
पूर्ण;

अटल व्योम uic_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा uic *uic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 er, sr;

	sr = 1 << (31-src);
	raw_spin_lock_irqsave(&uic->lock, flags);
	/* ack level-triggered पूर्णांकerrupts here */
	अगर (irqd_is_level_type(d))
		mtdcr(uic->dcrbase + UIC_SR, sr);
	er = mfdcr(uic->dcrbase + UIC_ER);
	er |= sr;
	mtdcr(uic->dcrbase + UIC_ER, er);
	raw_spin_unlock_irqrestore(&uic->lock, flags);
पूर्ण

अटल व्योम uic_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा uic *uic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 er;

	raw_spin_lock_irqsave(&uic->lock, flags);
	er = mfdcr(uic->dcrbase + UIC_ER);
	er &= ~(1 << (31 - src));
	mtdcr(uic->dcrbase + UIC_ER, er);
	raw_spin_unlock_irqrestore(&uic->lock, flags);
पूर्ण

अटल व्योम uic_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा uic *uic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&uic->lock, flags);
	mtdcr(uic->dcrbase + UIC_SR, 1 << (31-src));
	raw_spin_unlock_irqrestore(&uic->lock, flags);
पूर्ण

अटल व्योम uic_mask_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा uic *uic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	u32 er, sr;

	sr = 1 << (31-src);
	raw_spin_lock_irqsave(&uic->lock, flags);
	er = mfdcr(uic->dcrbase + UIC_ER);
	er &= ~sr;
	mtdcr(uic->dcrbase + UIC_ER, er);
 	/* On the UIC, acking (i.e. clearing the SR bit)
	 * a level irq will have no effect अगर the पूर्णांकerrupt
	 * is still निश्चितed by the device, even अगर
	 * the पूर्णांकerrupt is alपढ़ोy masked. Thereक्रमe
	 * we only ack the egde पूर्णांकerrupts here, जबतक
	 * level पूर्णांकerrupts are ack'ed after the actual
	 * isr call in the uic_unmask_irq()
	 */
	अगर (!irqd_is_level_type(d))
		mtdcr(uic->dcrbase + UIC_SR, sr);
	raw_spin_unlock_irqrestore(&uic->lock, flags);
पूर्ण

अटल पूर्णांक uic_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा uic *uic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
	अचिन्हित दीर्घ flags;
	पूर्णांक trigger, polarity;
	u32 tr, pr, mask;

	चयन (flow_type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_NONE:
		uic_mask_irq(d);
		वापस 0;

	हाल IRQ_TYPE_EDGE_RISING:
		trigger = 1; polarity = 1;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		trigger = 1; polarity = 0;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		trigger = 0; polarity = 1;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		trigger = 0; polarity = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask = ~(1 << (31 - src));

	raw_spin_lock_irqsave(&uic->lock, flags);
	tr = mfdcr(uic->dcrbase + UIC_TR);
	pr = mfdcr(uic->dcrbase + UIC_PR);
	tr = (tr & mask) | (trigger << (31-src));
	pr = (pr & mask) | (polarity << (31-src));

	mtdcr(uic->dcrbase + UIC_PR, pr);
	mtdcr(uic->dcrbase + UIC_TR, tr);
	mtdcr(uic->dcrbase + UIC_SR, ~mask);

	raw_spin_unlock_irqrestore(&uic->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip uic_irq_chip = अणु
	.name		= "UIC",
	.irq_unmask	= uic_unmask_irq,
	.irq_mask	= uic_mask_irq,
	.irq_mask_ack	= uic_mask_ack_irq,
	.irq_ack	= uic_ack_irq,
	.irq_set_type	= uic_set_irq_type,
पूर्ण;

अटल पूर्णांक uic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			irq_hw_number_t hw)
अणु
	काष्ठा uic *uic = h->host_data;

	irq_set_chip_data(virq, uic);
	/* Despite the name, handle_level_irq() works क्रम both level
	 * and edge irqs on UIC.  FIXME: check this is correct */
	irq_set_chip_and_handler(virq, &uic_irq_chip, handle_level_irq);

	/* Set शेष irq type */
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops uic_host_ops = अणु
	.map	= uic_host_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल व्योम uic_irq_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा irq_data *idata = irq_desc_get_irq_data(desc);
	काष्ठा uic *uic = irq_desc_get_handler_data(desc);
	u32 msr;
	पूर्णांक src;
	पूर्णांक subvirq;

	raw_spin_lock(&desc->lock);
	अगर (irqd_is_level_type(idata))
		chip->irq_mask(idata);
	अन्यथा
		chip->irq_mask_ack(idata);
	raw_spin_unlock(&desc->lock);

	msr = mfdcr(uic->dcrbase + UIC_MSR);
	अगर (!msr) /* spurious पूर्णांकerrupt */
		जाओ uic_irq_ret;

	src = 32 - ffs(msr);

	subvirq = irq_linear_revmap(uic->irqhost, src);
	generic_handle_irq(subvirq);

uic_irq_ret:
	raw_spin_lock(&desc->lock);
	अगर (irqd_is_level_type(idata))
		chip->irq_ack(idata);
	अगर (!irqd_irq_disabled(idata) && chip->irq_unmask)
		chip->irq_unmask(idata);
	raw_spin_unlock(&desc->lock);
पूर्ण

अटल काष्ठा uic * __init uic_init_one(काष्ठा device_node *node)
अणु
	काष्ठा uic *uic;
	स्थिर u32 *indexp, *dcrreg;
	पूर्णांक len;

	BUG_ON(! of_device_is_compatible(node, "ibm,uic"));

	uic = kzalloc(माप(*uic), GFP_KERNEL);
	अगर (! uic)
		वापस शून्य; /* FIXME: panic? */

	raw_spin_lock_init(&uic->lock);
	indexp = of_get_property(node, "cell-index", &len);
	अगर (!indexp || (len != माप(u32))) अणु
		prपूर्णांकk(KERN_ERR "uic: Device node %pOF has missing or invalid "
		       "cell-index property\n", node);
		वापस शून्य;
	पूर्ण
	uic->index = *indexp;

	dcrreg = of_get_property(node, "dcr-reg", &len);
	अगर (!dcrreg || (len != 2*माप(u32))) अणु
		prपूर्णांकk(KERN_ERR "uic: Device node %pOF has missing or invalid "
		       "dcr-reg property\n", node);
		वापस शून्य;
	पूर्ण
	uic->dcrbase = *dcrreg;

	uic->irqhost = irq_करोमुख्य_add_linear(node, NR_UIC_INTS, &uic_host_ops,
					     uic);
	अगर (! uic->irqhost)
		वापस शून्य; /* FIXME: panic? */

	/* Start with all पूर्णांकerrupts disabled, level and non-critical */
	mtdcr(uic->dcrbase + UIC_ER, 0);
	mtdcr(uic->dcrbase + UIC_CR, 0);
	mtdcr(uic->dcrbase + UIC_TR, 0);
	/* Clear any pending पूर्णांकerrupts, in हाल the firmware left some */
	mtdcr(uic->dcrbase + UIC_SR, 0xffffffff);

	prपूर्णांकk ("UIC%d (%d IRQ sources) at DCR 0x%x\n", uic->index,
		NR_UIC_INTS, uic->dcrbase);

	वापस uic;
पूर्ण

व्योम __init uic_init_tree(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा uic *uic;
	स्थिर u32 *पूर्णांकerrupts;

	/* First locate and initialize the top-level UIC */
	क्रम_each_compatible_node(np, शून्य, "ibm,uic") अणु
		पूर्णांकerrupts = of_get_property(np, "interrupts", शून्य);
		अगर (!पूर्णांकerrupts)
			अवरोध;
	पूर्ण

	BUG_ON(!np); /* uic_init_tree() assumes there's a UIC as the
		      * top-level पूर्णांकerrupt controller */
	primary_uic = uic_init_one(np);
	अगर (!primary_uic)
		panic("Unable to initialize primary UIC %pOF\n", np);

	irq_set_शेष_host(primary_uic->irqhost);
	of_node_put(np);

	/* The scan again क्रम cascaded UICs */
	क्रम_each_compatible_node(np, शून्य, "ibm,uic") अणु
		पूर्णांकerrupts = of_get_property(np, "interrupts", शून्य);
		अगर (पूर्णांकerrupts) अणु
			/* Secondary UIC */
			पूर्णांक cascade_virq;

			uic = uic_init_one(np);
			अगर (! uic)
				panic("Unable to initialize a secondary UIC %pOF\n",
				      np);

			cascade_virq = irq_of_parse_and_map(np, 0);

			irq_set_handler_data(cascade_virq, uic);
			irq_set_chained_handler(cascade_virq, uic_irq_cascade);

			/* FIXME: setup critical cascade?? */
		पूर्ण
	पूर्ण
पूर्ण

/* Return an पूर्णांकerrupt vector or 0 अगर no पूर्णांकerrupt is pending. */
अचिन्हित पूर्णांक uic_get_irq(व्योम)
अणु
	u32 msr;
	पूर्णांक src;

	BUG_ON(! primary_uic);

	msr = mfdcr(primary_uic->dcrbase + UIC_MSR);
	src = 32 - ffs(msr);

	वापस irq_linear_revmap(primary_uic->irqhost, src);
पूर्ण
