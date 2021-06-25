<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Code to handle x86 style IRQs plus some generic पूर्णांकerrupt stuff.
 *
 * Copyright (C) 1992 Linus Torvalds
 * Copyright (C) 1994 - 2000 Ralf Baechle
 */
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/पन.स>

/*
 * This is the 'legacy' 8259A Programmable Interrupt Controller,
 * present in the majority of PC/AT boxes.
 * plus some generic x86 specअगरic things अगर generic specअगरics makes
 * any sense at all.
 * this file should become arch/i386/kernel/irq.c when the old irq.c
 * moves to arch independent land
 */

अटल पूर्णांक i8259A_स्वतः_eoi = -1;
DEFINE_RAW_SPINLOCK(i8259A_lock);
अटल व्योम disable_8259A_irq(काष्ठा irq_data *d);
अटल व्योम enable_8259A_irq(काष्ठा irq_data *d);
अटल व्योम mask_and_ack_8259A(काष्ठा irq_data *d);
अटल व्योम init_8259A(पूर्णांक स्वतः_eoi);
अटल पूर्णांक (*i8259_poll)(व्योम) = i8259_irq;

अटल काष्ठा irq_chip i8259A_chip = अणु
	.name			= "XT-PIC",
	.irq_mask		= disable_8259A_irq,
	.irq_disable		= disable_8259A_irq,
	.irq_unmask		= enable_8259A_irq,
	.irq_mask_ack		= mask_and_ack_8259A,
पूर्ण;

/*
 * 8259A PIC functions to handle ISA devices:
 */

व्योम i8259_set_poll(पूर्णांक (*poll)(व्योम))
अणु
	i8259_poll = poll;
पूर्ण

/*
 * This contains the irq mask क्रम both 8259A irq controllers,
 */
अटल अचिन्हित पूर्णांक cached_irq_mask = 0xffff;

#घोषणा cached_master_mask	(cached_irq_mask)
#घोषणा cached_slave_mask	(cached_irq_mask >> 8)

अटल व्योम disable_8259A_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask, irq = d->irq - I8259A_IRQ_BASE;
	अचिन्हित दीर्घ flags;

	mask = 1 << irq;
	raw_spin_lock_irqsave(&i8259A_lock, flags);
	cached_irq_mask |= mask;
	अगर (irq & 8)
		outb(cached_slave_mask, PIC_SLAVE_IMR);
	अन्यथा
		outb(cached_master_mask, PIC_MASTER_IMR);
	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
पूर्ण

अटल व्योम enable_8259A_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask, irq = d->irq - I8259A_IRQ_BASE;
	अचिन्हित दीर्घ flags;

	mask = ~(1 << irq);
	raw_spin_lock_irqsave(&i8259A_lock, flags);
	cached_irq_mask &= mask;
	अगर (irq & 8)
		outb(cached_slave_mask, PIC_SLAVE_IMR);
	अन्यथा
		outb(cached_master_mask, PIC_MASTER_IMR);
	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
पूर्ण

व्योम make_8259A_irq(अचिन्हित पूर्णांक irq)
अणु
	disable_irq_nosync(irq);
	irq_set_chip_and_handler(irq, &i8259A_chip, handle_level_irq);
	enable_irq(irq);
पूर्ण

/*
 * This function assumes to be called rarely. Switching between
 * 8259A रेजिस्टरs is slow.
 * This has to be रक्षित by the irq controller spinlock
 * beक्रमe being called.
 */
अटल अंतरभूत पूर्णांक i8259A_irq_real(अचिन्हित पूर्णांक irq)
अणु
	पूर्णांक value;
	पूर्णांक irqmask = 1 << irq;

	अगर (irq < 8) अणु
		outb(0x0B, PIC_MASTER_CMD);	/* ISR रेजिस्टर */
		value = inb(PIC_MASTER_CMD) & irqmask;
		outb(0x0A, PIC_MASTER_CMD);	/* back to the IRR रेजिस्टर */
		वापस value;
	पूर्ण
	outb(0x0B, PIC_SLAVE_CMD);	/* ISR रेजिस्टर */
	value = inb(PIC_SLAVE_CMD) & (irqmask >> 8);
	outb(0x0A, PIC_SLAVE_CMD);	/* back to the IRR रेजिस्टर */
	वापस value;
पूर्ण

/*
 * Careful! The 8259A is a fragile beast, it pretty
 * much _has_ to be करोne exactly like this (mask it
 * first, _then_ send the EOI, and the order of EOI
 * to the two 8259s is important!
 */
अटल व्योम mask_and_ack_8259A(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irqmask, irq = d->irq - I8259A_IRQ_BASE;
	अचिन्हित दीर्घ flags;

	irqmask = 1 << irq;
	raw_spin_lock_irqsave(&i8259A_lock, flags);
	/*
	 * Lightweight spurious IRQ detection. We करो not want
	 * to overकरो spurious IRQ handling - it's usually a sign
	 * of hardware problems, so we only करो the checks we can
	 * करो without slowing करोwn good hardware unnecessarily.
	 *
	 * Note that IRQ7 and IRQ15 (the two spurious IRQs
	 * usually resulting from the 8259A-1|2 PICs) occur
	 * even अगर the IRQ is masked in the 8259A. Thus we
	 * can check spurious 8259A IRQs without करोing the
	 * quite slow i8259A_irq_real() call क्रम every IRQ.
	 * This करोes not cover 100% of spurious पूर्णांकerrupts,
	 * but should be enough to warn the user that there
	 * is something bad going on ...
	 */
	अगर (cached_irq_mask & irqmask)
		जाओ spurious_8259A_irq;
	cached_irq_mask |= irqmask;

handle_real_irq:
	अगर (irq & 8) अणु
		inb(PIC_SLAVE_IMR);	/* DUMMY - (करो we need this?) */
		outb(cached_slave_mask, PIC_SLAVE_IMR);
		outb(0x60+(irq&7), PIC_SLAVE_CMD);/* 'Specific EOI' to slave */
		outb(0x60+PIC_CASCADE_IR, PIC_MASTER_CMD); /* 'Specific EOI' to master-IRQ2 */
	पूर्ण अन्यथा अणु
		inb(PIC_MASTER_IMR);	/* DUMMY - (करो we need this?) */
		outb(cached_master_mask, PIC_MASTER_IMR);
		outb(0x60+irq, PIC_MASTER_CMD); /* 'Specअगरic EOI to master */
	पूर्ण
	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
	वापस;

spurious_8259A_irq:
	/*
	 * this is the slow path - should happen rarely.
	 */
	अगर (i8259A_irq_real(irq))
		/*
		 * oops, the IRQ _is_ in service according to the
		 * 8259A - not spurious, go handle it.
		 */
		जाओ handle_real_irq;

	अणु
		अटल पूर्णांक spurious_irq_mask;
		/*
		 * At this poपूर्णांक we can be sure the IRQ is spurious,
		 * lets ACK and report it. [once per IRQ]
		 */
		अगर (!(spurious_irq_mask & irqmask)) अणु
			prपूर्णांकk(KERN_DEBUG "spurious 8259A interrupt: IRQ%d.\n", irq);
			spurious_irq_mask |= irqmask;
		पूर्ण
		atomic_inc(&irq_err_count);
		/*
		 * Theoretically we करो not have to handle this IRQ,
		 * but in Linux this करोes not cause problems and is
		 * simpler क्रम us.
		 */
		जाओ handle_real_irq;
	पूर्ण
पूर्ण

अटल व्योम i8259A_resume(व्योम)
अणु
	अगर (i8259A_स्वतः_eoi >= 0)
		init_8259A(i8259A_स्वतः_eoi);
पूर्ण

अटल व्योम i8259A_shutकरोwn(व्योम)
अणु
	/* Put the i8259A पूर्णांकo a quiescent state that
	 * the kernel initialization code can get it
	 * out of.
	 */
	अगर (i8259A_स्वतः_eoi >= 0) अणु
		outb(0xff, PIC_MASTER_IMR);	/* mask all of 8259A-1 */
		outb(0xff, PIC_SLAVE_IMR);	/* mask all of 8259A-2 */
	पूर्ण
पूर्ण

अटल काष्ठा syscore_ops i8259_syscore_ops = अणु
	.resume = i8259A_resume,
	.shutकरोwn = i8259A_shutकरोwn,
पूर्ण;

अटल व्योम init_8259A(पूर्णांक स्वतः_eoi)
अणु
	अचिन्हित दीर्घ flags;

	i8259A_स्वतः_eoi = स्वतः_eoi;

	raw_spin_lock_irqsave(&i8259A_lock, flags);

	outb(0xff, PIC_MASTER_IMR);	/* mask all of 8259A-1 */
	outb(0xff, PIC_SLAVE_IMR);	/* mask all of 8259A-2 */

	/*
	 * outb_p - this has to work on a wide range of PC hardware.
	 */
	outb_p(0x11, PIC_MASTER_CMD);	/* ICW1: select 8259A-1 init */
	outb_p(I8259A_IRQ_BASE + 0, PIC_MASTER_IMR);	/* ICW2: 8259A-1 IR0 mapped to I8259A_IRQ_BASE + 0x00 */
	outb_p(1U << PIC_CASCADE_IR, PIC_MASTER_IMR);	/* 8259A-1 (the master) has a slave on IR2 */
	अगर (स्वतः_eoi)	/* master करोes Auto EOI */
		outb_p(MASTER_ICW4_DEFAULT | PIC_ICW4_AEOI, PIC_MASTER_IMR);
	अन्यथा		/* master expects normal EOI */
		outb_p(MASTER_ICW4_DEFAULT, PIC_MASTER_IMR);

	outb_p(0x11, PIC_SLAVE_CMD);	/* ICW1: select 8259A-2 init */
	outb_p(I8259A_IRQ_BASE + 8, PIC_SLAVE_IMR);	/* ICW2: 8259A-2 IR0 mapped to I8259A_IRQ_BASE + 0x08 */
	outb_p(PIC_CASCADE_IR, PIC_SLAVE_IMR);	/* 8259A-2 is a slave on master's IR2 */
	outb_p(SLAVE_ICW4_DEFAULT, PIC_SLAVE_IMR); /* (slave's support क्रम AEOI in flat mode is to be investigated) */
	अगर (स्वतः_eoi)
		/*
		 * In AEOI mode we just have to mask the पूर्णांकerrupt
		 * when acking.
		 */
		i8259A_chip.irq_mask_ack = disable_8259A_irq;
	अन्यथा
		i8259A_chip.irq_mask_ack = mask_and_ack_8259A;

	udelay(100);		/* रुको क्रम 8259A to initialize */

	outb(cached_master_mask, PIC_MASTER_IMR); /* restore master IRQ mask */
	outb(cached_slave_mask, PIC_SLAVE_IMR);	  /* restore slave IRQ mask */

	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
पूर्ण

अटल काष्ठा resource pic1_io_resource = अणु
	.name = "pic1",
	.start = PIC_MASTER_CMD,
	.end = PIC_MASTER_IMR,
	.flags = IORESOURCE_IO | IORESOURCE_BUSY
पूर्ण;

अटल काष्ठा resource pic2_io_resource = अणु
	.name = "pic2",
	.start = PIC_SLAVE_CMD,
	.end = PIC_SLAVE_IMR,
	.flags = IORESOURCE_IO | IORESOURCE_BUSY
पूर्ण;

अटल पूर्णांक i8259A_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
				 irq_hw_number_t hw)
अणु
	irq_set_chip_and_handler(virq, &i8259A_chip, handle_level_irq);
	irq_set_probe(virq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops i8259A_ops = अणु
	.map = i8259A_irq_करोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

/*
 * On प्रणालीs with i8259-style पूर्णांकerrupt controllers we assume क्रम
 * driver compatibility reasons पूर्णांकerrupts 0 - 15 to be the i8259
 * पूर्णांकerrupts even अगर the hardware uses a dअगरferent पूर्णांकerrupt numbering.
 */
काष्ठा irq_करोमुख्य * __init __init_i8259_irqs(काष्ठा device_node *node)
अणु
	/*
	 * PIC_CASCADE_IR is cascade पूर्णांकerrupt to second पूर्णांकerrupt controller
	 */
	पूर्णांक irq = I8259A_IRQ_BASE + PIC_CASCADE_IR;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	insert_resource(&ioport_resource, &pic1_io_resource);
	insert_resource(&ioport_resource, &pic2_io_resource);

	init_8259A(0);

	करोमुख्य = irq_करोमुख्य_add_legacy(node, 16, I8259A_IRQ_BASE, 0,
				       &i8259A_ops, शून्य);
	अगर (!करोमुख्य)
		panic("Failed to add i8259 IRQ domain");

	अगर (request_irq(irq, no_action, IRQF_NO_THREAD, "cascade", शून्य))
		pr_err("Failed to register cascade interrupt\n");
	रेजिस्टर_syscore_ops(&i8259_syscore_ops);
	वापस करोमुख्य;
पूर्ण

व्योम __init init_i8259_irqs(व्योम)
अणु
	__init_i8259_irqs(शून्य);
पूर्ण

अटल व्योम i8259_irq_dispatch(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य = irq_desc_get_handler_data(desc);
	पूर्णांक hwirq = i8259_poll();
	अचिन्हित पूर्णांक irq;

	अगर (hwirq < 0)
		वापस;

	irq = irq_linear_revmap(करोमुख्य, hwirq);
	generic_handle_irq(irq);
पूर्ण

पूर्णांक __init i8259_of_init(काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	अचिन्हित पूर्णांक parent_irq;

	करोमुख्य = __init_i8259_irqs(node);

	parent_irq = irq_of_parse_and_map(node, 0);
	अगर (!parent_irq) अणु
		pr_err("Failed to map i8259 parent IRQ\n");
		irq_करोमुख्य_हटाओ(करोमुख्य);
		वापस -ENODEV;
	पूर्ण

	irq_set_chained_handler_and_data(parent_irq, i8259_irq_dispatch,
					 करोमुख्य);
	वापस 0;
पूर्ण
IRQCHIP_DECLARE(i8259, "intel,i8259", i8259_of_init);
