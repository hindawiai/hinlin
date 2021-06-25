<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/linkage.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/समयx.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/bitops.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/i8259.h>

/*
 * This is the 'legacy' 8259A Programmable Interrupt Controller,
 * present in the majority of PC/AT boxes.
 * plus some generic x86 specअगरic things अगर generic specअगरics makes
 * any sense at all.
 */
अटल व्योम init_8259A(पूर्णांक स्वतः_eoi);

अटल पूर्णांक i8259A_स्वतः_eoi;
DEFINE_RAW_SPINLOCK(i8259A_lock);

/*
 * 8259A PIC functions to handle ISA devices:
 */

/*
 * This contains the irq mask क्रम both 8259A irq controllers,
 */
अचिन्हित पूर्णांक cached_irq_mask = 0xffff;

/*
 * Not all IRQs can be routed through the IO-APIC, eg. on certain (older)
 * boards the समयr पूर्णांकerrupt is not really connected to any IO-APIC pin,
 * it's fed to the master 8259A's IR0 line only.
 *
 * Any '1' bit in this mask means the IRQ is routed through the IO-APIC.
 * this 'mixed mode' IRQ handling costs nothing because it's only used
 * at IRQ setup समय.
 */
अचिन्हित दीर्घ io_apic_irqs;

अटल व्योम mask_8259A_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक mask = 1 << irq;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&i8259A_lock, flags);
	cached_irq_mask |= mask;
	अगर (irq & 8)
		outb(cached_slave_mask, PIC_SLAVE_IMR);
	अन्यथा
		outb(cached_master_mask, PIC_MASTER_IMR);
	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
पूर्ण

अटल व्योम disable_8259A_irq(काष्ठा irq_data *data)
अणु
	mask_8259A_irq(data->irq);
पूर्ण

अटल व्योम unmask_8259A_irq(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक mask = ~(1 << irq);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&i8259A_lock, flags);
	cached_irq_mask &= mask;
	अगर (irq & 8)
		outb(cached_slave_mask, PIC_SLAVE_IMR);
	अन्यथा
		outb(cached_master_mask, PIC_MASTER_IMR);
	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
पूर्ण

अटल व्योम enable_8259A_irq(काष्ठा irq_data *data)
अणु
	unmask_8259A_irq(data->irq);
पूर्ण

अटल पूर्णांक i8259A_irq_pending(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक mask = 1<<irq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	raw_spin_lock_irqsave(&i8259A_lock, flags);
	अगर (irq < 8)
		ret = inb(PIC_MASTER_CMD) & mask;
	अन्यथा
		ret = inb(PIC_SLAVE_CMD) & (mask >> 8);
	raw_spin_unlock_irqrestore(&i8259A_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम make_8259A_irq(अचिन्हित पूर्णांक irq)
अणु
	disable_irq_nosync(irq);
	io_apic_irqs &= ~(1<<irq);
	irq_set_chip_and_handler(irq, &i8259A_chip, handle_level_irq);
	enable_irq(irq);
	lapic_assign_legacy_vector(irq, true);
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
	पूर्णांक irqmask = 1<<irq;

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
अटल व्योम mask_and_ack_8259A(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;
	अचिन्हित पूर्णांक irqmask = 1 << irq;
	अचिन्हित दीर्घ flags;

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
		/* 'Specific EOI' to slave */
		outb(0x60+(irq&7), PIC_SLAVE_CMD);
		 /* 'Specific EOI' to master-IRQ2 */
		outb(0x60+PIC_CASCADE_IR, PIC_MASTER_CMD);
	पूर्ण अन्यथा अणु
		inb(PIC_MASTER_IMR);	/* DUMMY - (करो we need this?) */
		outb(cached_master_mask, PIC_MASTER_IMR);
		outb(0x60+irq, PIC_MASTER_CMD);	/* 'Specअगरic EOI to master */
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
			prपूर्णांकk_deferred(KERN_DEBUG
			       "spurious 8259A interrupt: IRQ%d.\n", irq);
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

काष्ठा irq_chip i8259A_chip = अणु
	.name		= "XT-PIC",
	.irq_mask	= disable_8259A_irq,
	.irq_disable	= disable_8259A_irq,
	.irq_unmask	= enable_8259A_irq,
	.irq_mask_ack	= mask_and_ack_8259A,
पूर्ण;

अटल अक्षर irq_trigger[2];
/**
 * ELCR रेजिस्टरs (0x4d0, 0x4d1) control edge/level of IRQ
 */
अटल व्योम restore_ELCR(अक्षर *trigger)
अणु
	outb(trigger[0], 0x4d0);
	outb(trigger[1], 0x4d1);
पूर्ण

अटल व्योम save_ELCR(अक्षर *trigger)
अणु
	/* IRQ 0,1,2,8,13 are marked as reserved */
	trigger[0] = inb(0x4d0) & 0xF8;
	trigger[1] = inb(0x4d1) & 0xDE;
पूर्ण

अटल व्योम i8259A_resume(व्योम)
अणु
	init_8259A(i8259A_स्वतः_eoi);
	restore_ELCR(irq_trigger);
पूर्ण

अटल पूर्णांक i8259A_suspend(व्योम)
अणु
	save_ELCR(irq_trigger);
	वापस 0;
पूर्ण

अटल व्योम i8259A_shutकरोwn(व्योम)
अणु
	/* Put the i8259A पूर्णांकo a quiescent state that
	 * the kernel initialization code can get it
	 * out of.
	 */
	outb(0xff, PIC_MASTER_IMR);	/* mask all of 8259A-1 */
	outb(0xff, PIC_SLAVE_IMR);	/* mask all of 8259A-2 */
पूर्ण

अटल काष्ठा syscore_ops i8259_syscore_ops = अणु
	.suspend = i8259A_suspend,
	.resume = i8259A_resume,
	.shutकरोwn = i8259A_shutकरोwn,
पूर्ण;

अटल व्योम mask_8259A(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&i8259A_lock, flags);

	outb(0xff, PIC_MASTER_IMR);	/* mask all of 8259A-1 */
	outb(0xff, PIC_SLAVE_IMR);	/* mask all of 8259A-2 */

	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
पूर्ण

अटल व्योम unmask_8259A(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&i8259A_lock, flags);

	outb(cached_master_mask, PIC_MASTER_IMR); /* restore master IRQ mask */
	outb(cached_slave_mask, PIC_SLAVE_IMR);	  /* restore slave IRQ mask */

	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
पूर्ण

अटल पूर्णांक probe_8259A(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर probe_val = ~(1 << PIC_CASCADE_IR);
	अचिन्हित अक्षर new_val;
	/*
	 * Check to see अगर we have a PIC.
	 * Mask all except the cascade and पढ़ो
	 * back the value we just wrote. If we करोn't
	 * have a PIC, we will पढ़ो 0xff as opposed to the
	 * value we wrote.
	 */
	raw_spin_lock_irqsave(&i8259A_lock, flags);

	outb(0xff, PIC_SLAVE_IMR);	/* mask all of 8259A-2 */
	outb(probe_val, PIC_MASTER_IMR);
	new_val = inb(PIC_MASTER_IMR);
	अगर (new_val != probe_val) अणु
		prपूर्णांकk(KERN_INFO "Using NULL legacy PIC\n");
		legacy_pic = &null_legacy_pic;
	पूर्ण

	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
	वापस nr_legacy_irqs();
पूर्ण

अटल व्योम init_8259A(पूर्णांक स्वतः_eoi)
अणु
	अचिन्हित दीर्घ flags;

	i8259A_स्वतः_eoi = स्वतः_eoi;

	raw_spin_lock_irqsave(&i8259A_lock, flags);

	outb(0xff, PIC_MASTER_IMR);	/* mask all of 8259A-1 */

	/*
	 * outb_pic - this has to work on a wide range of PC hardware.
	 */
	outb_pic(0x11, PIC_MASTER_CMD);	/* ICW1: select 8259A-1 init */

	/* ICW2: 8259A-1 IR0-7 mapped to ISA_IRQ_VECTOR(0) */
	outb_pic(ISA_IRQ_VECTOR(0), PIC_MASTER_IMR);

	/* 8259A-1 (the master) has a slave on IR2 */
	outb_pic(1U << PIC_CASCADE_IR, PIC_MASTER_IMR);

	अगर (स्वतः_eoi)	/* master करोes Auto EOI */
		outb_pic(MASTER_ICW4_DEFAULT | PIC_ICW4_AEOI, PIC_MASTER_IMR);
	अन्यथा		/* master expects normal EOI */
		outb_pic(MASTER_ICW4_DEFAULT, PIC_MASTER_IMR);

	outb_pic(0x11, PIC_SLAVE_CMD);	/* ICW1: select 8259A-2 init */

	/* ICW2: 8259A-2 IR0-7 mapped to ISA_IRQ_VECTOR(8) */
	outb_pic(ISA_IRQ_VECTOR(8), PIC_SLAVE_IMR);
	/* 8259A-2 is a slave on master's IR2 */
	outb_pic(PIC_CASCADE_IR, PIC_SLAVE_IMR);
	/* (slave's support क्रम AEOI in flat mode is to be investigated) */
	outb_pic(SLAVE_ICW4_DEFAULT, PIC_SLAVE_IMR);

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

/*
 * make i8259 a driver so that we can select pic functions at run समय. the goal
 * is to make x86 binary compatible among pc compatible and non-pc compatible
 * platक्रमms, such as x86 MID.
 */

अटल व्योम legacy_pic_noop(व्योम) अणु पूर्ण;
अटल व्योम legacy_pic_uपूर्णांक_noop(अचिन्हित पूर्णांक unused) अणु पूर्ण;
अटल व्योम legacy_pic_पूर्णांक_noop(पूर्णांक unused) अणु पूर्ण;
अटल पूर्णांक legacy_pic_irq_pending_noop(अचिन्हित पूर्णांक irq)
अणु
	वापस 0;
पूर्ण
अटल पूर्णांक legacy_pic_probe(व्योम)
अणु
	वापस 0;
पूर्ण

काष्ठा legacy_pic null_legacy_pic = अणु
	.nr_legacy_irqs = 0,
	.chip = &dummy_irq_chip,
	.mask = legacy_pic_uपूर्णांक_noop,
	.unmask = legacy_pic_uपूर्णांक_noop,
	.mask_all = legacy_pic_noop,
	.restore_mask = legacy_pic_noop,
	.init = legacy_pic_पूर्णांक_noop,
	.probe = legacy_pic_probe,
	.irq_pending = legacy_pic_irq_pending_noop,
	.make_irq = legacy_pic_uपूर्णांक_noop,
पूर्ण;

काष्ठा legacy_pic शेष_legacy_pic = अणु
	.nr_legacy_irqs = NR_IRQS_LEGACY,
	.chip  = &i8259A_chip,
	.mask = mask_8259A_irq,
	.unmask = unmask_8259A_irq,
	.mask_all = mask_8259A,
	.restore_mask = unmask_8259A,
	.init = init_8259A,
	.probe = probe_8259A,
	.irq_pending = i8259A_irq_pending,
	.make_irq = make_8259A_irq,
पूर्ण;

काष्ठा legacy_pic *legacy_pic = &शेष_legacy_pic;
EXPORT_SYMBOL(legacy_pic);

अटल पूर्णांक __init i8259A_init_ops(व्योम)
अणु
	अगर (legacy_pic == &शेष_legacy_pic)
		रेजिस्टर_syscore_ops(&i8259_syscore_ops);

	वापस 0;
पूर्ण

device_initcall(i8259A_init_ops);
