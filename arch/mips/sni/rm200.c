<शैली गुरु>
/*
 * RM200 specअगरic code
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006,2007 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 *
 * i8259 parts ripped out of arch/mips/kernel/i8259.c
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/sni.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/irq_cpu.h>

#घोषणा RM200_I8259A_IRQ_BASE 32

#घोषणा MEMPORT(_base,_irq)				\
	अणु						\
		.mapbase	= _base,		\
		.irq		= _irq,			\
		.uartclk	= 1843200,		\
		.iotype		= UPIO_MEM,		\
		.flags		= UPF_BOOT_AUTOCONF|UPF_IOREMAP, \
	पूर्ण

अटल काष्ठा plat_serial8250_port rm200_data[] = अणु
	MEMPORT(0x160003f8, RM200_I8259A_IRQ_BASE + 4),
	MEMPORT(0x160002f8, RM200_I8259A_IRQ_BASE + 3),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rm200_serial8250_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= rm200_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource rm200_ds1216_rsrc[] = अणु
	अणु
		.start = 0x1cd41ffc,
		.end   = 0x1cd41fff,
		.flags = IORESOURCE_MEM
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device rm200_ds1216_device = अणु
	.name		= "rtc-ds1216",
	.num_resources	= ARRAY_SIZE(rm200_ds1216_rsrc),
	.resource	= rm200_ds1216_rsrc
पूर्ण;

अटल काष्ठा resource snirm_82596_rm200_rsrc[] = अणु
	अणु
		.start = 0x18000000,
		.end   = 0x180fffff,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = 0x1b000000,
		.end   = 0x1b000004,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = 0x1ff00000,
		.end   = 0x1ff00020,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = 27,
		.end   = 27,
		.flags = IORESOURCE_IRQ
	पूर्ण,
	अणु
		.flags = 0x00
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device snirm_82596_rm200_pdev = अणु
	.name		= "snirm_82596",
	.num_resources	= ARRAY_SIZE(snirm_82596_rm200_rsrc),
	.resource	= snirm_82596_rm200_rsrc
पूर्ण;

अटल काष्ठा resource snirm_53c710_rm200_rsrc[] = अणु
	अणु
		.start = 0x19000000,
		.end   = 0x190fffff,
		.flags = IORESOURCE_MEM
	पूर्ण,
	अणु
		.start = 26,
		.end   = 26,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device snirm_53c710_rm200_pdev = अणु
	.name		= "snirm_53c710",
	.num_resources	= ARRAY_SIZE(snirm_53c710_rm200_rsrc),
	.resource	= snirm_53c710_rm200_rsrc
पूर्ण;

अटल पूर्णांक __init snirm_setup_devinit(व्योम)
अणु
	अगर (sni_brd_type == SNI_BRD_RM200) अणु
		platक्रमm_device_रेजिस्टर(&rm200_serial8250_device);
		platक्रमm_device_रेजिस्टर(&rm200_ds1216_device);
		platक्रमm_device_रेजिस्टर(&snirm_82596_rm200_pdev);
		platक्रमm_device_रेजिस्टर(&snirm_53c710_rm200_pdev);
		sni_eisa_root_init();
	पूर्ण
	वापस 0;
पूर्ण

device_initcall(snirm_setup_devinit);

/*
 * RM200 has an ISA and an EISA bus. The iSA bus is only used
 * क्रम onboard devices and also has twi i8259 PICs. Since these
 * PICs are no accessible via inb/outb the following code uses
 * पढ़ोb/ग_लिखोb to access them
 */

अटल DEFINE_RAW_SPINLOCK(sni_rm200_i8259A_lock);
#घोषणा PIC_CMD	   0x00
#घोषणा PIC_IMR	   0x01
#घोषणा PIC_ISR	   PIC_CMD
#घोषणा PIC_POLL   PIC_ISR
#घोषणा PIC_OCW3   PIC_ISR

/* i8259A PIC related value */
#घोषणा PIC_CASCADE_IR		2
#घोषणा MASTER_ICW4_DEFAULT	0x01
#घोषणा SLAVE_ICW4_DEFAULT	0x01

/*
 * This contains the irq mask क्रम both 8259A irq controllers,
 */
अटल अचिन्हित पूर्णांक rm200_cached_irq_mask = 0xffff;
अटल __iomem u8 *rm200_pic_master;
अटल __iomem u8 *rm200_pic_slave;

#घोषणा cached_master_mask	(rm200_cached_irq_mask)
#घोषणा cached_slave_mask	(rm200_cached_irq_mask >> 8)

अटल व्योम sni_rm200_disable_8259A_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask, irq = d->irq - RM200_I8259A_IRQ_BASE;
	अचिन्हित दीर्घ flags;

	mask = 1 << irq;
	raw_spin_lock_irqsave(&sni_rm200_i8259A_lock, flags);
	rm200_cached_irq_mask |= mask;
	अगर (irq & 8)
		ग_लिखोb(cached_slave_mask, rm200_pic_slave + PIC_IMR);
	अन्यथा
		ग_लिखोb(cached_master_mask, rm200_pic_master + PIC_IMR);
	raw_spin_unlock_irqrestore(&sni_rm200_i8259A_lock, flags);
पूर्ण

अटल व्योम sni_rm200_enable_8259A_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask, irq = d->irq - RM200_I8259A_IRQ_BASE;
	अचिन्हित दीर्घ flags;

	mask = ~(1 << irq);
	raw_spin_lock_irqsave(&sni_rm200_i8259A_lock, flags);
	rm200_cached_irq_mask &= mask;
	अगर (irq & 8)
		ग_लिखोb(cached_slave_mask, rm200_pic_slave + PIC_IMR);
	अन्यथा
		ग_लिखोb(cached_master_mask, rm200_pic_master + PIC_IMR);
	raw_spin_unlock_irqrestore(&sni_rm200_i8259A_lock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक sni_rm200_i8259A_irq_real(अचिन्हित पूर्णांक irq)
अणु
	पूर्णांक value;
	पूर्णांक irqmask = 1 << irq;

	अगर (irq < 8) अणु
		ग_लिखोb(0x0B, rm200_pic_master + PIC_CMD);
		value = पढ़ोb(rm200_pic_master + PIC_CMD) & irqmask;
		ग_लिखोb(0x0A, rm200_pic_master + PIC_CMD);
		वापस value;
	पूर्ण
	ग_लिखोb(0x0B, rm200_pic_slave + PIC_CMD); /* ISR रेजिस्टर */
	value = पढ़ोb(rm200_pic_slave + PIC_CMD) & (irqmask >> 8);
	ग_लिखोb(0x0A, rm200_pic_slave + PIC_CMD);
	वापस value;
पूर्ण

/*
 * Careful! The 8259A is a fragile beast, it pretty
 * much _has_ to be करोne exactly like this (mask it
 * first, _then_ send the EOI, and the order of EOI
 * to the two 8259s is important!
 */
व्योम sni_rm200_mask_and_ack_8259A(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irqmask, irq = d->irq - RM200_I8259A_IRQ_BASE;
	अचिन्हित दीर्घ flags;

	irqmask = 1 << irq;
	raw_spin_lock_irqsave(&sni_rm200_i8259A_lock, flags);
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
	अगर (rm200_cached_irq_mask & irqmask)
		जाओ spurious_8259A_irq;
	rm200_cached_irq_mask |= irqmask;

handle_real_irq:
	अगर (irq & 8) अणु
		पढ़ोb(rm200_pic_slave + PIC_IMR);
		ग_लिखोb(cached_slave_mask, rm200_pic_slave + PIC_IMR);
		ग_लिखोb(0x60+(irq & 7), rm200_pic_slave + PIC_CMD);
		ग_लिखोb(0x60+PIC_CASCADE_IR, rm200_pic_master + PIC_CMD);
	पूर्ण अन्यथा अणु
		पढ़ोb(rm200_pic_master + PIC_IMR);
		ग_लिखोb(cached_master_mask, rm200_pic_master + PIC_IMR);
		ग_लिखोb(0x60+irq, rm200_pic_master + PIC_CMD);
	पूर्ण
	raw_spin_unlock_irqrestore(&sni_rm200_i8259A_lock, flags);
	वापस;

spurious_8259A_irq:
	/*
	 * this is the slow path - should happen rarely.
	 */
	अगर (sni_rm200_i8259A_irq_real(irq))
		/*
		 * oops, the IRQ _is_ in service according to the
		 * 8259A - not spurious, go handle it.
		 */
		जाओ handle_real_irq;

	अणु
		अटल पूर्णांक spurious_irq_mask;
		/*
		 * At this poपूर्णांक we can be sure the IRQ is spurious,
		 * let's ACK and report it. [once per IRQ]
		 */
		अगर (!(spurious_irq_mask & irqmask)) अणु
			prपूर्णांकk(KERN_DEBUG
			       "spurious RM200 8259A interrupt: IRQ%d.\n", irq);
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

अटल काष्ठा irq_chip sni_rm200_i8259A_chip = अणु
	.name		= "RM200-XT-PIC",
	.irq_mask	= sni_rm200_disable_8259A_irq,
	.irq_unmask	= sni_rm200_enable_8259A_irq,
	.irq_mask_ack	= sni_rm200_mask_and_ack_8259A,
पूर्ण;

/*
 * Do the traditional i8259 पूर्णांकerrupt polling thing.  This is क्रम the few
 * हालs where no better पूर्णांकerrupt acknowledge method is available and we
 * असलolutely must touch the i8259.
 */
अटल अंतरभूत पूर्णांक sni_rm200_i8259_irq(व्योम)
अणु
	पूर्णांक irq;

	raw_spin_lock(&sni_rm200_i8259A_lock);

	/* Perक्रमm an पूर्णांकerrupt acknowledge cycle on controller 1. */
	ग_लिखोb(0x0C, rm200_pic_master + PIC_CMD);	/* prepare क्रम poll */
	irq = पढ़ोb(rm200_pic_master + PIC_CMD) & 7;
	अगर (irq == PIC_CASCADE_IR) अणु
		/*
		 * Interrupt is cascaded so perक्रमm पूर्णांकerrupt
		 * acknowledge on controller 2.
		 */
		ग_लिखोb(0x0C, rm200_pic_slave + PIC_CMD); /* prepare क्रम poll */
		irq = (पढ़ोb(rm200_pic_slave + PIC_CMD) & 7) + 8;
	पूर्ण

	अगर (unlikely(irq == 7)) अणु
		/*
		 * This may be a spurious पूर्णांकerrupt.
		 *
		 * Read the पूर्णांकerrupt status रेजिस्टर (ISR). If the most
		 * signअगरicant bit is not set then there is no valid
		 * पूर्णांकerrupt.
		 */
		ग_लिखोb(0x0B, rm200_pic_master + PIC_ISR); /* ISR रेजिस्टर */
		अगर (~पढ़ोb(rm200_pic_master + PIC_ISR) & 0x80)
			irq = -1;
	पूर्ण

	raw_spin_unlock(&sni_rm200_i8259A_lock);

	वापस likely(irq >= 0) ? irq + RM200_I8259A_IRQ_BASE : irq;
पूर्ण

व्योम sni_rm200_init_8259A(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&sni_rm200_i8259A_lock, flags);

	ग_लिखोb(0xff, rm200_pic_master + PIC_IMR);
	ग_लिखोb(0xff, rm200_pic_slave + PIC_IMR);

	ग_लिखोb(0x11, rm200_pic_master + PIC_CMD);
	ग_लिखोb(0, rm200_pic_master + PIC_IMR);
	ग_लिखोb(1U << PIC_CASCADE_IR, rm200_pic_master + PIC_IMR);
	ग_लिखोb(MASTER_ICW4_DEFAULT, rm200_pic_master + PIC_IMR);
	ग_लिखोb(0x11, rm200_pic_slave + PIC_CMD);
	ग_लिखोb(8, rm200_pic_slave + PIC_IMR);
	ग_लिखोb(PIC_CASCADE_IR, rm200_pic_slave + PIC_IMR);
	ग_लिखोb(SLAVE_ICW4_DEFAULT, rm200_pic_slave + PIC_IMR);
	udelay(100);		/* रुको क्रम 8259A to initialize */

	ग_लिखोb(cached_master_mask, rm200_pic_master + PIC_IMR);
	ग_लिखोb(cached_slave_mask, rm200_pic_slave + PIC_IMR);

	raw_spin_unlock_irqrestore(&sni_rm200_i8259A_lock, flags);
पूर्ण

/*
 * IRQ2 is cascade पूर्णांकerrupt to second पूर्णांकerrupt controller
 */

अटल काष्ठा resource sni_rm200_pic1_resource = अणु
	.name = "onboard ISA pic1",
	.start = 0x16000020,
	.end = 0x16000023,
	.flags = IORESOURCE_BUSY
पूर्ण;

अटल काष्ठा resource sni_rm200_pic2_resource = अणु
	.name = "onboard ISA pic2",
	.start = 0x160000a0,
	.end = 0x160000a3,
	.flags = IORESOURCE_BUSY
पूर्ण;

/* ISA irq handler */
अटल irqवापस_t sni_rm200_i8259A_irq_handler(पूर्णांक dummy, व्योम *p)
अणु
	पूर्णांक irq;

	irq = sni_rm200_i8259_irq();
	अगर (unlikely(irq < 0))
		वापस IRQ_NONE;

	करो_IRQ(irq);
	वापस IRQ_HANDLED;
पूर्ण

व्योम __init sni_rm200_i8259_irqs(व्योम)
अणु
	पूर्णांक i;

	rm200_pic_master = ioremap(0x16000020, 4);
	अगर (!rm200_pic_master)
		वापस;
	rm200_pic_slave = ioremap(0x160000a0, 4);
	अगर (!rm200_pic_slave) अणु
		iounmap(rm200_pic_master);
		वापस;
	पूर्ण

	insert_resource(&iomem_resource, &sni_rm200_pic1_resource);
	insert_resource(&iomem_resource, &sni_rm200_pic2_resource);

	sni_rm200_init_8259A();

	क्रम (i = RM200_I8259A_IRQ_BASE; i < RM200_I8259A_IRQ_BASE + 16; i++)
		irq_set_chip_and_handler(i, &sni_rm200_i8259A_chip,
					 handle_level_irq);

	अगर (request_irq(RM200_I8259A_IRQ_BASE + PIC_CASCADE_IR, no_action,
			IRQF_NO_THREAD, "cascade", शून्य))
		pr_err("Failed to register cascade interrupt\n");
पूर्ण


#घोषणा SNI_RM200_INT_STAT_REG	CKSEG1ADDR(0xbc000000)
#घोषणा SNI_RM200_INT_ENA_REG	CKSEG1ADDR(0xbc080000)

#घोषणा SNI_RM200_INT_START  24
#घोषणा SNI_RM200_INT_END    28

अटल व्योम enable_rm200_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq - SNI_RM200_INT_START);

	*(अस्थिर u8 *)SNI_RM200_INT_ENA_REG &= ~mask;
पूर्ण

व्योम disable_rm200_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask = 1 << (d->irq - SNI_RM200_INT_START);

	*(अस्थिर u8 *)SNI_RM200_INT_ENA_REG |= mask;
पूर्ण

अटल काष्ठा irq_chip rm200_irq_type = अणु
	.name = "RM200",
	.irq_mask = disable_rm200_irq,
	.irq_unmask = enable_rm200_irq,
पूर्ण;

अटल व्योम sni_rm200_hwपूर्णांक(व्योम)
अणु
	u32 pending = पढ़ो_c0_cause() & पढ़ो_c0_status();
	u8 mask;
	u8 stat;
	पूर्णांक irq;

	अगर (pending & C_IRQ5)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 7);
	अन्यथा अगर (pending & C_IRQ0) अणु
		clear_c0_status(IE_IRQ0);
		mask = *(अस्थिर u8 *)SNI_RM200_INT_ENA_REG ^ 0x1f;
		stat = *(अस्थिर u8 *)SNI_RM200_INT_STAT_REG ^ 0x14;
		irq = ffs(stat & mask & 0x1f);

		अगर (likely(irq > 0))
			करो_IRQ(irq + SNI_RM200_INT_START - 1);
		set_c0_status(IE_IRQ0);
	पूर्ण
पूर्ण

व्योम __init sni_rm200_irq_init(व्योम)
अणु
	पूर्णांक i;

	* (अस्थिर u8 *)SNI_RM200_INT_ENA_REG = 0x1f;

	sni_rm200_i8259_irqs();
	mips_cpu_irq_init();
	/* Actually we've got more पूर्णांकerrupts to handle ...  */
	क्रम (i = SNI_RM200_INT_START; i <= SNI_RM200_INT_END; i++)
		irq_set_chip_and_handler(i, &rm200_irq_type, handle_level_irq);
	sni_hwपूर्णांक = sni_rm200_hwपूर्णांक;
	change_c0_status(ST0_IM, IE_IRQ0);
	अगर (request_irq(SNI_RM200_INT_START + 0, sni_rm200_i8259A_irq_handler,
			0, "onboard ISA", शून्य))
		pr_err("Failed to register onboard ISA interrupt\n");
	अगर (request_irq(SNI_RM200_INT_START + 1, sni_isa_irq_handler, 0, "ISA",
			शून्य))
		pr_err("Failed to register ISA interrupt\n");
पूर्ण

व्योम __init sni_rm200_init(व्योम)
अणु
पूर्ण
