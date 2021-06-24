<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * i8259 पूर्णांकerrupt controller driver.
 */
#अघोषित DEBUG

#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/prom.h>

अटल अस्थिर व्योम __iomem *pci_पूर्णांकack; /* RO, gives us the irq vector */

अटल अचिन्हित अक्षर cached_8259[2] = अणु 0xff, 0xff पूर्ण;
#घोषणा cached_A1 (cached_8259[0])
#घोषणा cached_21 (cached_8259[1])

अटल DEFINE_RAW_SPINLOCK(i8259_lock);

अटल काष्ठा irq_करोमुख्य *i8259_host;

/*
 * Acknowledge the IRQ using either the PCI host bridge's पूर्णांकerrupt
 * acknowledge feature or poll.  How i8259_init() is called determines
 * which is called.  It should be noted that polling is broken on some
 * IBM and Motorola PReP boxes so we must use the पूर्णांक-ack feature on them.
 */
अचिन्हित पूर्णांक i8259_irq(व्योम)
अणु
	पूर्णांक irq;
	पूर्णांक lock = 0;

	/* Either पूर्णांक-ack or poll क्रम the IRQ */
	अगर (pci_पूर्णांकack)
		irq = पढ़ोb(pci_पूर्णांकack);
	अन्यथा अणु
		raw_spin_lock(&i8259_lock);
		lock = 1;

		/* Perक्रमm an पूर्णांकerrupt acknowledge cycle on controller 1. */
		outb(0x0C, 0x20);		/* prepare क्रम poll */
		irq = inb(0x20) & 7;
		अगर (irq == 2 ) अणु
			/*
			 * Interrupt is cascaded so perक्रमm पूर्णांकerrupt
			 * acknowledge on controller 2.
			 */
			outb(0x0C, 0xA0);	/* prepare क्रम poll */
			irq = (inb(0xA0) & 7) + 8;
		पूर्ण
	पूर्ण

	अगर (irq == 7) अणु
		/*
		 * This may be a spurious पूर्णांकerrupt.
		 *
		 * Read the पूर्णांकerrupt status रेजिस्टर (ISR). If the most
		 * signअगरicant bit is not set then there is no valid
		 * पूर्णांकerrupt.
		 */
		अगर (!pci_पूर्णांकack)
			outb(0x0B, 0x20);	/* ISR रेजिस्टर */
		अगर(~inb(0x20) & 0x80)
			irq = 0;
	पूर्ण अन्यथा अगर (irq == 0xff)
		irq = 0;

	अगर (lock)
		raw_spin_unlock(&i8259_lock);
	वापस irq;
पूर्ण

अटल व्योम i8259_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&i8259_lock, flags);
	अगर (d->irq > 7) अणु
		cached_A1 |= 1 << (d->irq-8);
		inb(0xA1); 	/* DUMMY */
		outb(cached_A1, 0xA1);
		outb(0x20, 0xA0);	/* Non-specअगरic EOI */
		outb(0x20, 0x20);	/* Non-specअगरic EOI to cascade */
	पूर्ण अन्यथा अणु
		cached_21 |= 1 << d->irq;
		inb(0x21); 	/* DUMMY */
		outb(cached_21, 0x21);
		outb(0x20, 0x20);	/* Non-specअगरic EOI */
	पूर्ण
	raw_spin_unlock_irqrestore(&i8259_lock, flags);
पूर्ण

अटल व्योम i8259_set_irq_mask(पूर्णांक irq_nr)
अणु
	outb(cached_A1,0xA1);
	outb(cached_21,0x21);
पूर्ण

अटल व्योम i8259_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;

	pr_debug("i8259_mask_irq(%d)\n", d->irq);

	raw_spin_lock_irqsave(&i8259_lock, flags);
	अगर (d->irq < 8)
		cached_21 |= 1 << d->irq;
	अन्यथा
		cached_A1 |= 1 << (d->irq-8);
	i8259_set_irq_mask(d->irq);
	raw_spin_unlock_irqrestore(&i8259_lock, flags);
पूर्ण

अटल व्योम i8259_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;

	pr_debug("i8259_unmask_irq(%d)\n", d->irq);

	raw_spin_lock_irqsave(&i8259_lock, flags);
	अगर (d->irq < 8)
		cached_21 &= ~(1 << d->irq);
	अन्यथा
		cached_A1 &= ~(1 << (d->irq-8));
	i8259_set_irq_mask(d->irq);
	raw_spin_unlock_irqrestore(&i8259_lock, flags);
पूर्ण

अटल काष्ठा irq_chip i8259_pic = अणु
	.name		= "i8259",
	.irq_mask	= i8259_mask_irq,
	.irq_disable	= i8259_mask_irq,
	.irq_unmask	= i8259_unmask_irq,
	.irq_mask_ack	= i8259_mask_and_ack_irq,
पूर्ण;

अटल काष्ठा resource pic1_iores = अणु
	.name = "8259 (master)",
	.start = 0x20,
	.end = 0x21,
	.flags = IORESOURCE_IO | IORESOURCE_BUSY,
पूर्ण;

अटल काष्ठा resource pic2_iores = अणु
	.name = "8259 (slave)",
	.start = 0xa0,
	.end = 0xa1,
	.flags = IORESOURCE_IO | IORESOURCE_BUSY,
पूर्ण;

अटल काष्ठा resource pic_edgectrl_iores = अणु
	.name = "8259 edge control",
	.start = 0x4d0,
	.end = 0x4d1,
	.flags = IORESOURCE_IO | IORESOURCE_BUSY,
पूर्ण;

अटल पूर्णांक i8259_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
			    क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	काष्ठा device_node *of_node = irq_करोमुख्य_get_of_node(h);
	वापस of_node == शून्य || of_node == node;
पूर्ण

अटल पूर्णांक i8259_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु
	pr_debug("i8259_host_map(%d, 0x%lx)\n", virq, hw);

	/* We block the पूर्णांकernal cascade */
	अगर (hw == 2)
		irq_set_status_flags(virq, IRQ_NOREQUEST);

	/* We use the level handler only क्रम now, we might want to
	 * be more cautious here but that works क्रम now
	 */
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &i8259_pic, handle_level_irq);
	वापस 0;
पूर्ण

अटल पूर्णांक i8259_host_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
			    स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			    irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)
अणु
	अटल अचिन्हित अक्षर map_isa_senses[4] = अणु
		IRQ_TYPE_LEVEL_LOW,
		IRQ_TYPE_LEVEL_HIGH,
		IRQ_TYPE_EDGE_FALLING,
		IRQ_TYPE_EDGE_RISING,
	पूर्ण;

	*out_hwirq = पूर्णांकspec[0];
	अगर (पूर्णांकsize > 1 && पूर्णांकspec[1] < 4)
		*out_flags = map_isa_senses[पूर्णांकspec[1]];
	अन्यथा
		*out_flags = IRQ_TYPE_NONE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops i8259_host_ops = अणु
	.match = i8259_host_match,
	.map = i8259_host_map,
	.xlate = i8259_host_xlate,
पूर्ण;

काष्ठा irq_करोमुख्य *i8259_get_host(व्योम)
अणु
	वापस i8259_host;
पूर्ण

/**
 * i8259_init - Initialize the legacy controller
 * @node: device node of the legacy PIC (can be शून्य, but then, it will match
 *        all पूर्णांकerrupts, so beware)
 * @पूर्णांकack_addr: PCI पूर्णांकerrupt acknowledge (real) address which will वापस
 *             	 the active irq from the 8259
 */
व्योम i8259_init(काष्ठा device_node *node, अचिन्हित दीर्घ पूर्णांकack_addr)
अणु
	अचिन्हित दीर्घ flags;

	/* initialize the controller */
	raw_spin_lock_irqsave(&i8259_lock, flags);

	/* Mask all first */
	outb(0xff, 0xA1);
	outb(0xff, 0x21);

	/* init master पूर्णांकerrupt controller */
	outb(0x11, 0x20); /* Start init sequence */
	outb(0x00, 0x21); /* Vector base */
	outb(0x04, 0x21); /* edge triggered, Cascade (slave) on IRQ2 */
	outb(0x01, 0x21); /* Select 8086 mode */

	/* init slave पूर्णांकerrupt controller */
	outb(0x11, 0xA0); /* Start init sequence */
	outb(0x08, 0xA1); /* Vector base */
	outb(0x02, 0xA1); /* edge triggered, Cascade (slave) on IRQ2 */
	outb(0x01, 0xA1); /* Select 8086 mode */

	/* That thing is slow */
	udelay(100);

	/* always पढ़ो ISR */
	outb(0x0B, 0x20);
	outb(0x0B, 0xA0);

	/* Unmask the पूर्णांकernal cascade */
	cached_21 &= ~(1 << 2);

	/* Set पूर्णांकerrupt masks */
	outb(cached_A1, 0xA1);
	outb(cached_21, 0x21);

	raw_spin_unlock_irqrestore(&i8259_lock, flags);

	/* create a legacy host */
	i8259_host = irq_करोमुख्य_add_legacy_isa(node, &i8259_host_ops, शून्य);
	अगर (i8259_host == शून्य) अणु
		prपूर्णांकk(KERN_ERR "i8259: failed to allocate irq host !\n");
		वापस;
	पूर्ण

	/* reserve our resources */
	/* XXX should we जारी करोing that ? it seems to cause problems
	 * with further requesting of PCI IO resources क्रम that range...
	 * need to look पूर्णांकo it.
	 */
	request_resource(&ioport_resource, &pic1_iores);
	request_resource(&ioport_resource, &pic2_iores);
	request_resource(&ioport_resource, &pic_edgectrl_iores);

	अगर (पूर्णांकack_addr != 0)
		pci_पूर्णांकack = ioremap(पूर्णांकack_addr, 1);

	prपूर्णांकk(KERN_INFO "i8259 legacy interrupt controller initialized\n");
पूर्ण
