<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip22-पूर्णांक.c: Routines क्रम generic manipulation of the INT[23] ASIC
 *	       found on INDY and Indigo2 workstations.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997, 1998 Ralf Baechle (ralf@gnu.org)
 * Copyright (C) 1999 Andrew R. Baker (andrewb@uab.edu)
 *		      - Indigo2 changes
 *		      - Interrupt handling fixes
 * Copyright (C) 2001, 2003 Ladislav Michl (ladis@linux-mips.org)
 */
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ip22.h>

/* So far nothing hangs here */
#अघोषित USE_LIO3_IRQ

काष्ठा sgपूर्णांक_regs *sgपूर्णांक;

अटल अक्षर lc0msk_to_irqnr[256];
अटल अक्षर lc1msk_to_irqnr[256];
अटल अक्षर lc2msk_to_irqnr[256];
अटल अक्षर lc3msk_to_irqnr[256];

बाह्य पूर्णांक ip22_eisa_init(व्योम);

अटल व्योम enable_local0_irq(काष्ठा irq_data *d)
अणु
	/* करोn't allow mappable पूर्णांकerrupt to be enabled from setup_irq,
	 * we have our own way to करो so */
	अगर (d->irq != SGI_MAP_0_IRQ)
		sgपूर्णांक->imask0 |= (1 << (d->irq - SGINT_LOCAL0));
पूर्ण

अटल व्योम disable_local0_irq(काष्ठा irq_data *d)
अणु
	sgपूर्णांक->imask0 &= ~(1 << (d->irq - SGINT_LOCAL0));
पूर्ण

अटल काष्ठा irq_chip ip22_local0_irq_type = अणु
	.name		= "IP22 local 0",
	.irq_mask	= disable_local0_irq,
	.irq_unmask	= enable_local0_irq,
पूर्ण;

अटल व्योम enable_local1_irq(काष्ठा irq_data *d)
अणु
	/* करोn't allow mappable पूर्णांकerrupt to be enabled from setup_irq,
	 * we have our own way to करो so */
	अगर (d->irq != SGI_MAP_1_IRQ)
		sgपूर्णांक->imask1 |= (1 << (d->irq - SGINT_LOCAL1));
पूर्ण

अटल व्योम disable_local1_irq(काष्ठा irq_data *d)
अणु
	sgपूर्णांक->imask1 &= ~(1 << (d->irq - SGINT_LOCAL1));
पूर्ण

अटल काष्ठा irq_chip ip22_local1_irq_type = अणु
	.name		= "IP22 local 1",
	.irq_mask	= disable_local1_irq,
	.irq_unmask	= enable_local1_irq,
पूर्ण;

अटल व्योम enable_local2_irq(काष्ठा irq_data *d)
अणु
	sgपूर्णांक->imask0 |= (1 << (SGI_MAP_0_IRQ - SGINT_LOCAL0));
	sgपूर्णांक->cmeimask0 |= (1 << (d->irq - SGINT_LOCAL2));
पूर्ण

अटल व्योम disable_local2_irq(काष्ठा irq_data *d)
अणु
	sgपूर्णांक->cmeimask0 &= ~(1 << (d->irq - SGINT_LOCAL2));
	अगर (!sgपूर्णांक->cmeimask0)
		sgपूर्णांक->imask0 &= ~(1 << (SGI_MAP_0_IRQ - SGINT_LOCAL0));
पूर्ण

अटल काष्ठा irq_chip ip22_local2_irq_type = अणु
	.name		= "IP22 local 2",
	.irq_mask	= disable_local2_irq,
	.irq_unmask	= enable_local2_irq,
पूर्ण;

अटल व्योम enable_local3_irq(काष्ठा irq_data *d)
अणु
	sgपूर्णांक->imask1 |= (1 << (SGI_MAP_1_IRQ - SGINT_LOCAL1));
	sgपूर्णांक->cmeimask1 |= (1 << (d->irq - SGINT_LOCAL3));
पूर्ण

अटल व्योम disable_local3_irq(काष्ठा irq_data *d)
अणु
	sgपूर्णांक->cmeimask1 &= ~(1 << (d->irq - SGINT_LOCAL3));
	अगर (!sgपूर्णांक->cmeimask1)
		sgपूर्णांक->imask1 &= ~(1 << (SGI_MAP_1_IRQ - SGINT_LOCAL1));
पूर्ण

अटल काष्ठा irq_chip ip22_local3_irq_type = अणु
	.name		= "IP22 local 3",
	.irq_mask	= disable_local3_irq,
	.irq_unmask	= enable_local3_irq,
पूर्ण;

अटल व्योम indy_local0_irqdispatch(व्योम)
अणु
	u8 mask = sgपूर्णांक->istat0 & sgपूर्णांक->imask0;
	u8 mask2;
	पूर्णांक irq;

	अगर (mask & SGINT_ISTAT0_LIO2) अणु
		mask2 = sgपूर्णांक->vmeistat & sgपूर्णांक->cmeimask0;
		irq = lc2msk_to_irqnr[mask2];
	पूर्ण अन्यथा
		irq = lc0msk_to_irqnr[mask];

	/*
	 * workaround क्रम INT2 bug; अगर irq == 0, INT2 has seen a fअगरo full
	 * irq, but failed to latch it पूर्णांकo status रेजिस्टर
	 */
	अगर (irq)
		करो_IRQ(irq);
	अन्यथा
		करो_IRQ(SGINT_LOCAL0 + 0);
पूर्ण

अटल व्योम indy_local1_irqdispatch(व्योम)
अणु
	u8 mask = sgपूर्णांक->istat1 & sgपूर्णांक->imask1;
	u8 mask2;
	पूर्णांक irq;

	अगर (mask & SGINT_ISTAT1_LIO3) अणु
		mask2 = sgपूर्णांक->vmeistat & sgपूर्णांक->cmeimask1;
		irq = lc3msk_to_irqnr[mask2];
	पूर्ण अन्यथा
		irq = lc1msk_to_irqnr[mask];

	/* अगर irq == 0, then the पूर्णांकerrupt has alपढ़ोy been cleared */
	अगर (irq)
		करो_IRQ(irq);
पूर्ण

बाह्य व्योम ip22_be_पूर्णांकerrupt(पूर्णांक irq);

अटल व्योम __irq_entry indy_buserror_irq(व्योम)
अणु
	पूर्णांक irq = SGI_BUSERR_IRQ;

	irq_enter();
	kstat_incr_irq_this_cpu(irq);
	ip22_be_पूर्णांकerrupt(irq);
	irq_निकास();
पूर्ण

#अगर_घोषित USE_LIO3_IRQ
#घोषणा SGI_INTERRUPTS	SGINT_END
#अन्यथा
#घोषणा SGI_INTERRUPTS	SGINT_LOCAL3
#पूर्ण_अगर

बाह्य व्योम indy_8254समयr_irq(व्योम);

/*
 * IRQs on the INDY look basically (barring software IRQs which we करोn't use
 * at all) like:
 *
 *	MIPS IRQ	Source
 *	--------	------
 *	       0	Software (ignored)
 *	       1	Software (ignored)
 *	       2	Local IRQ level zero
 *	       3	Local IRQ level one
 *	       4	8254 Timer zero
 *	       5	8254 Timer one
 *	       6	Bus Error
 *	       7	R4k समयr (what we use)
 *
 * We handle the IRQ according to _our_ priority which is:
 *
 * Highest ----	    R4k Timer
 *		    Local IRQ zero
 *		    Local IRQ one
 *		    Bus Error
 *		    8254 Timer zero
 * Lowest  ----	    8254 Timer one
 *
 * then we just वापस, अगर multiple IRQs are pending then we will just take
 * another exception, big deal.
 */

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक pending = पढ़ो_c0_status() & पढ़ो_c0_cause();

	/*
	 * First we check क्रम r4k counter/समयr IRQ.
	 */
	अगर (pending & CAUSEF_IP7)
		करो_IRQ(SGI_TIMER_IRQ);
	अन्यथा अगर (pending & CAUSEF_IP2)
		indy_local0_irqdispatch();
	अन्यथा अगर (pending & CAUSEF_IP3)
		indy_local1_irqdispatch();
	अन्यथा अगर (pending & CAUSEF_IP6)
		indy_buserror_irq();
	अन्यथा अगर (pending & (CAUSEF_IP4 | CAUSEF_IP5))
		indy_8254समयr_irq();
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	पूर्णांक i;

	/* Init local mask --> irq tables. */
	क्रम (i = 0; i < 256; i++) अणु
		अगर (i & 0x80) अणु
			lc0msk_to_irqnr[i] = SGINT_LOCAL0 + 7;
			lc1msk_to_irqnr[i] = SGINT_LOCAL1 + 7;
			lc2msk_to_irqnr[i] = SGINT_LOCAL2 + 7;
			lc3msk_to_irqnr[i] = SGINT_LOCAL3 + 7;
		पूर्ण अन्यथा अगर (i & 0x40) अणु
			lc0msk_to_irqnr[i] = SGINT_LOCAL0 + 6;
			lc1msk_to_irqnr[i] = SGINT_LOCAL1 + 6;
			lc2msk_to_irqnr[i] = SGINT_LOCAL2 + 6;
			lc3msk_to_irqnr[i] = SGINT_LOCAL3 + 6;
		पूर्ण अन्यथा अगर (i & 0x20) अणु
			lc0msk_to_irqnr[i] = SGINT_LOCAL0 + 5;
			lc1msk_to_irqnr[i] = SGINT_LOCAL1 + 5;
			lc2msk_to_irqnr[i] = SGINT_LOCAL2 + 5;
			lc3msk_to_irqnr[i] = SGINT_LOCAL3 + 5;
		पूर्ण अन्यथा अगर (i & 0x10) अणु
			lc0msk_to_irqnr[i] = SGINT_LOCAL0 + 4;
			lc1msk_to_irqnr[i] = SGINT_LOCAL1 + 4;
			lc2msk_to_irqnr[i] = SGINT_LOCAL2 + 4;
			lc3msk_to_irqnr[i] = SGINT_LOCAL3 + 4;
		पूर्ण अन्यथा अगर (i & 0x08) अणु
			lc0msk_to_irqnr[i] = SGINT_LOCAL0 + 3;
			lc1msk_to_irqnr[i] = SGINT_LOCAL1 + 3;
			lc2msk_to_irqnr[i] = SGINT_LOCAL2 + 3;
			lc3msk_to_irqnr[i] = SGINT_LOCAL3 + 3;
		पूर्ण अन्यथा अगर (i & 0x04) अणु
			lc0msk_to_irqnr[i] = SGINT_LOCAL0 + 2;
			lc1msk_to_irqnr[i] = SGINT_LOCAL1 + 2;
			lc2msk_to_irqnr[i] = SGINT_LOCAL2 + 2;
			lc3msk_to_irqnr[i] = SGINT_LOCAL3 + 2;
		पूर्ण अन्यथा अगर (i & 0x02) अणु
			lc0msk_to_irqnr[i] = SGINT_LOCAL0 + 1;
			lc1msk_to_irqnr[i] = SGINT_LOCAL1 + 1;
			lc2msk_to_irqnr[i] = SGINT_LOCAL2 + 1;
			lc3msk_to_irqnr[i] = SGINT_LOCAL3 + 1;
		पूर्ण अन्यथा अगर (i & 0x01) अणु
			lc0msk_to_irqnr[i] = SGINT_LOCAL0 + 0;
			lc1msk_to_irqnr[i] = SGINT_LOCAL1 + 0;
			lc2msk_to_irqnr[i] = SGINT_LOCAL2 + 0;
			lc3msk_to_irqnr[i] = SGINT_LOCAL3 + 0;
		पूर्ण अन्यथा अणु
			lc0msk_to_irqnr[i] = 0;
			lc1msk_to_irqnr[i] = 0;
			lc2msk_to_irqnr[i] = 0;
			lc3msk_to_irqnr[i] = 0;
		पूर्ण
	पूर्ण

	/* Mask out all पूर्णांकerrupts. */
	sgपूर्णांक->imask0 = 0;
	sgपूर्णांक->imask1 = 0;
	sgपूर्णांक->cmeimask0 = 0;
	sgपूर्णांक->cmeimask1 = 0;

	/* init CPU irqs */
	mips_cpu_irq_init();

	क्रम (i = SGINT_LOCAL0; i < SGI_INTERRUPTS; i++) अणु
		काष्ठा irq_chip *handler;

		अगर (i < SGINT_LOCAL1)
			handler		= &ip22_local0_irq_type;
		अन्यथा अगर (i < SGINT_LOCAL2)
			handler		= &ip22_local1_irq_type;
		अन्यथा अगर (i < SGINT_LOCAL3)
			handler		= &ip22_local2_irq_type;
		अन्यथा
			handler		= &ip22_local3_irq_type;

		irq_set_chip_and_handler(i, handler, handle_level_irq);
	पूर्ण

	/* vector handler. this रेजिस्टर the IRQ as non-sharable */
	अगर (request_irq(SGI_LOCAL_0_IRQ, no_action, IRQF_NO_THREAD,
			"local0 cascade", शून्य))
		pr_err("Failed to register local0 cascade interrupt\n");
	अगर (request_irq(SGI_LOCAL_1_IRQ, no_action, IRQF_NO_THREAD,
			"local1 cascade", शून्य))
		pr_err("Failed to register local1 cascade interrupt\n");
	अगर (request_irq(SGI_BUSERR_IRQ, no_action, IRQF_NO_THREAD,
			"Bus Error", शून्य))
		pr_err("Failed to register Bus Error interrupt\n");

	/* cascade in cascade. i love Indy ;-) */
	अगर (request_irq(SGI_MAP_0_IRQ, no_action, IRQF_NO_THREAD,
			"mapable0 cascade", शून्य))
		pr_err("Failed to register mapable0 cascade interrupt\n");
#अगर_घोषित USE_LIO3_IRQ
	अगर (request_irq(SGI_MAP_1_IRQ, no_action, IRQF_NO_THREAD,
			"mapable1 cascade", शून्य))
		pr_err("Failed to register mapable1 cascade interrupt\n");
#पूर्ण_अगर

#अगर_घोषित CONFIG_EISA
	अगर (ip22_is_fullhouse())	/* Only Indigo-2 has EISA stuff */
		ip22_eisa_init();
#पूर्ण_अगर
पूर्ण
