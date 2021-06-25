<शैली गुरु>
/*
 * Code to handle IP32 IRQs
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000 Harald Koerfgen
 * Copyright (C) 2001 Keith M Wesolowski
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/ip32/crime.h>
#समावेश <यंत्र/ip32/mace.h>
#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>

/* issue a PIO पढ़ो to make sure no PIO ग_लिखोs are pending */
अटल अंतरभूत व्योम flush_crime_bus(व्योम)
अणु
	crime->control;
पूर्ण

अटल अंतरभूत व्योम flush_mace_bus(व्योम)
अणु
	mace->perअगर.ctrl.misc;
पूर्ण

/*
 * O2 irq map
 *
 * IP0 -> software (ignored)
 * IP1 -> software (ignored)
 * IP2 -> (irq0) C crime 1.1 all पूर्णांकerrupts; crime 1.5 ???
 * IP3 -> (irq1) X unknown
 * IP4 -> (irq2) X unknown
 * IP5 -> (irq3) X unknown
 * IP6 -> (irq4) X unknown
 * IP7 -> (irq5) 7 CPU count/compare समयr (प्रणाली समयr)
 *
 * crime: (C)
 *
 * CRIME_INT_STAT 31:0:
 *
 * 0  ->  8  Video in 1
 * 1  ->  9 Video in 2
 * 2  -> 10  Video out
 * 3  -> 11  Mace ethernet
 * 4  -> S  SuperIO sub-पूर्णांकerrupt
 * 5  -> M  Miscellaneous sub-पूर्णांकerrupt
 * 6  -> A  Audio sub-पूर्णांकerrupt
 * 7  -> 15  PCI bridge errors
 * 8  -> 16  PCI SCSI aic7xxx 0
 * 9  -> 17 PCI SCSI aic7xxx 1
 * 10 -> 18 PCI slot 0
 * 11 -> 19 unused (PCI slot 1)
 * 12 -> 20 unused (PCI slot 2)
 * 13 -> 21 unused (PCI shared 0)
 * 14 -> 22 unused (PCI shared 1)
 * 15 -> 23 unused (PCI shared 2)
 * 16 -> 24 GBE0 (E)
 * 17 -> 25 GBE1 (E)
 * 18 -> 26 GBE2 (E)
 * 19 -> 27 GBE3 (E)
 * 20 -> 28 CPU errors
 * 21 -> 29 Memory errors
 * 22 -> 30 RE empty edge (E)
 * 23 -> 31 RE full edge (E)
 * 24 -> 32 RE idle edge (E)
 * 25 -> 33 RE empty level
 * 26 -> 34 RE full level
 * 27 -> 35 RE idle level
 * 28 -> 36 unused (software 0) (E)
 * 29 -> 37 unused (software 1) (E)
 * 30 -> 38 unused (software 2) - crime 1.5 CPU SysCorError (E)
 * 31 -> 39 VICE
 *
 * S, M, A: Use the MACE ISA पूर्णांकerrupt रेजिस्टर
 * MACE_ISA_INT_STAT 31:0
 *
 * 0-7 -> 40-47 Audio
 * 8 -> 48 RTC
 * 9 -> 49 Keyboard
 * 10 -> X Keyboard polled
 * 11 -> 51 Mouse
 * 12 -> X Mouse polled
 * 13-15 -> 53-55 Count/compare समयrs
 * 16-19 -> 56-59 Parallel (16 E)
 * 20-25 -> 60-62 Serial 1 (22 E)
 * 26-31 -> 66-71 Serial 2 (28 E)
 *
 * Note that this means IRQs 12-14, 50, and 52 करो not exist.  This is a
 * dअगरferent IRQ map than IRIX uses, but that's OK as Linux irq handling
 * is quite dअगरferent anyway.
 */

/* Some initial पूर्णांकerrupts to set up */
बाह्य irqवापस_t crime_memerr_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);
बाह्य irqवापस_t crime_cpuerr_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);

/*
 * This is क्रम pure CRIME पूर्णांकerrupts - ie not MACE.  The advantage?
 * We get to split the रेजिस्टर in half and करो faster lookups.
 */

अटल uपूर्णांक64_t crime_mask;

अटल अंतरभूत व्योम crime_enable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - CRIME_IRQ_BASE;

	crime_mask |= 1 << bit;
	crime->imask = crime_mask;
पूर्ण

अटल अंतरभूत व्योम crime_disable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - CRIME_IRQ_BASE;

	crime_mask &= ~(1 << bit);
	crime->imask = crime_mask;
	flush_crime_bus();
पूर्ण

अटल काष्ठा irq_chip crime_level_पूर्णांकerrupt = अणु
	.name		= "IP32 CRIME",
	.irq_mask	= crime_disable_irq,
	.irq_unmask	= crime_enable_irq,
पूर्ण;

अटल व्योम crime_edge_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - CRIME_IRQ_BASE;
	uपूर्णांक64_t crime_पूर्णांक;

	/* Edge triggered पूर्णांकerrupts must be cleared. */
	crime_पूर्णांक = crime->hard_पूर्णांक;
	crime_पूर्णांक &= ~(1 << bit);
	crime->hard_पूर्णांक = crime_पूर्णांक;

	crime_disable_irq(d);
पूर्ण

अटल काष्ठा irq_chip crime_edge_पूर्णांकerrupt = अणु
	.name		= "IP32 CRIME",
	.irq_ack	= crime_edge_mask_and_ack_irq,
	.irq_mask	= crime_disable_irq,
	.irq_mask_ack	= crime_edge_mask_and_ack_irq,
	.irq_unmask	= crime_enable_irq,
पूर्ण;

/*
 * This is क्रम MACE PCI पूर्णांकerrupts.  We can decrease bus traffic by masking
 * as बंद to the source as possible.	This also means we can take the
 * next chunk of the CRIME रेजिस्टर in one piece.
 */

अटल अचिन्हित दीर्घ macepci_mask;

अटल व्योम enable_macepci_irq(काष्ठा irq_data *d)
अणु
	macepci_mask |= MACEPCI_CONTROL_INT(d->irq - MACEPCI_SCSI0_IRQ);
	mace->pci.control = macepci_mask;
	crime_mask |= 1 << (d->irq - CRIME_IRQ_BASE);
	crime->imask = crime_mask;
पूर्ण

अटल व्योम disable_macepci_irq(काष्ठा irq_data *d)
अणु
	crime_mask &= ~(1 << (d->irq - CRIME_IRQ_BASE));
	crime->imask = crime_mask;
	flush_crime_bus();
	macepci_mask &= ~MACEPCI_CONTROL_INT(d->irq - MACEPCI_SCSI0_IRQ);
	mace->pci.control = macepci_mask;
	flush_mace_bus();
पूर्ण

अटल काष्ठा irq_chip ip32_macepci_पूर्णांकerrupt = अणु
	.name = "IP32 MACE PCI",
	.irq_mask = disable_macepci_irq,
	.irq_unmask = enable_macepci_irq,
पूर्ण;

/* This is used क्रम MACE ISA पूर्णांकerrupts.  That means bits 4-6 in the
 * CRIME रेजिस्टर.
 */

#घोषणा MACEISA_AUDIO_INT	(MACEISA_AUDIO_SW_INT |		\
				 MACEISA_AUDIO_SC_INT |		\
				 MACEISA_AUDIO1_DMAT_INT |	\
				 MACEISA_AUDIO1_OF_INT |	\
				 MACEISA_AUDIO2_DMAT_INT |	\
				 MACEISA_AUDIO2_MERR_INT |	\
				 MACEISA_AUDIO3_DMAT_INT |	\
				 MACEISA_AUDIO3_MERR_INT)
#घोषणा MACEISA_MISC_INT	(MACEISA_RTC_INT |		\
				 MACEISA_KEYB_INT |		\
				 MACEISA_KEYB_POLL_INT |	\
				 MACEISA_MOUSE_INT |		\
				 MACEISA_MOUSE_POLL_INT |	\
				 MACEISA_TIMER0_INT |		\
				 MACEISA_TIMER1_INT |		\
				 MACEISA_TIMER2_INT)
#घोषणा MACEISA_SUPERIO_INT	(MACEISA_PARALLEL_INT |		\
				 MACEISA_PAR_CTXA_INT |		\
				 MACEISA_PAR_CTXB_INT |		\
				 MACEISA_PAR_MERR_INT |		\
				 MACEISA_SERIAL1_INT |		\
				 MACEISA_SERIAL1_TDMAT_INT |	\
				 MACEISA_SERIAL1_TDMAPR_INT |	\
				 MACEISA_SERIAL1_TDMAME_INT |	\
				 MACEISA_SERIAL1_RDMAT_INT |	\
				 MACEISA_SERIAL1_RDMAOR_INT |	\
				 MACEISA_SERIAL2_INT |		\
				 MACEISA_SERIAL2_TDMAT_INT |	\
				 MACEISA_SERIAL2_TDMAPR_INT |	\
				 MACEISA_SERIAL2_TDMAME_INT |	\
				 MACEISA_SERIAL2_RDMAT_INT |	\
				 MACEISA_SERIAL2_RDMAOR_INT)

अटल अचिन्हित दीर्घ maceisa_mask;

अटल व्योम enable_maceisa_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक crime_पूर्णांक = 0;

	pr_debug("maceisa enable: %u\n", d->irq);

	चयन (d->irq) अणु
	हाल MACEISA_AUDIO_SW_IRQ ... MACEISA_AUDIO3_MERR_IRQ:
		crime_पूर्णांक = MACE_AUDIO_INT;
		अवरोध;
	हाल MACEISA_RTC_IRQ ... MACEISA_TIMER2_IRQ:
		crime_पूर्णांक = MACE_MISC_INT;
		अवरोध;
	हाल MACEISA_PARALLEL_IRQ ... MACEISA_SERIAL2_RDMAOR_IRQ:
		crime_पूर्णांक = MACE_SUPERIO_INT;
		अवरोध;
	पूर्ण
	pr_debug("crime_int %08x enabled\n", crime_पूर्णांक);
	crime_mask |= crime_पूर्णांक;
	crime->imask = crime_mask;
	maceisa_mask |= 1 << (d->irq - MACEISA_AUDIO_SW_IRQ);
	mace->perअगर.ctrl.imask = maceisa_mask;
पूर्ण

अटल व्योम disable_maceisa_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक crime_पूर्णांक = 0;

	maceisa_mask &= ~(1 << (d->irq - MACEISA_AUDIO_SW_IRQ));
	अगर (!(maceisa_mask & MACEISA_AUDIO_INT))
		crime_पूर्णांक |= MACE_AUDIO_INT;
	अगर (!(maceisa_mask & MACEISA_MISC_INT))
		crime_पूर्णांक |= MACE_MISC_INT;
	अगर (!(maceisa_mask & MACEISA_SUPERIO_INT))
		crime_पूर्णांक |= MACE_SUPERIO_INT;
	crime_mask &= ~crime_पूर्णांक;
	crime->imask = crime_mask;
	flush_crime_bus();
	mace->perअगर.ctrl.imask = maceisa_mask;
	flush_mace_bus();
पूर्ण

अटल व्योम mask_and_ack_maceisa_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ mace_पूर्णांक;

	/* edge triggered */
	mace_पूर्णांक = mace->perअगर.ctrl.istat;
	mace_पूर्णांक &= ~(1 << (d->irq - MACEISA_AUDIO_SW_IRQ));
	mace->perअगर.ctrl.istat = mace_पूर्णांक;

	disable_maceisa_irq(d);
पूर्ण

अटल काष्ठा irq_chip ip32_maceisa_level_पूर्णांकerrupt = अणु
	.name		= "IP32 MACE ISA",
	.irq_mask	= disable_maceisa_irq,
	.irq_unmask	= enable_maceisa_irq,
पूर्ण;

अटल काष्ठा irq_chip ip32_maceisa_edge_पूर्णांकerrupt = अणु
	.name		= "IP32 MACE ISA",
	.irq_ack	= mask_and_ack_maceisa_irq,
	.irq_mask	= disable_maceisa_irq,
	.irq_mask_ack	= mask_and_ack_maceisa_irq,
	.irq_unmask	= enable_maceisa_irq,
पूर्ण;

/* This is used क्रम regular non-ISA, non-PCI MACE पूर्णांकerrupts.  That means
 * bits 0-3 and 7 in the CRIME रेजिस्टर.
 */

अटल व्योम enable_mace_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - CRIME_IRQ_BASE;

	crime_mask |= (1 << bit);
	crime->imask = crime_mask;
पूर्ण

अटल व्योम disable_mace_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक bit = d->irq - CRIME_IRQ_BASE;

	crime_mask &= ~(1 << bit);
	crime->imask = crime_mask;
	flush_crime_bus();
पूर्ण

अटल काष्ठा irq_chip ip32_mace_पूर्णांकerrupt = अणु
	.name = "IP32 MACE",
	.irq_mask = disable_mace_irq,
	.irq_unmask = enable_mace_irq,
पूर्ण;

अटल व्योम ip32_unknown_पूर्णांकerrupt(व्योम)
अणु
	prपूर्णांकk("Unknown interrupt occurred!\n");
	prपूर्णांकk("cp0_status: %08x\n", पढ़ो_c0_status());
	prपूर्णांकk("cp0_cause: %08x\n", पढ़ो_c0_cause());
	prपूर्णांकk("CRIME intr mask: %016lx\n", crime->imask);
	prपूर्णांकk("CRIME intr status: %016lx\n", crime->istat);
	prपूर्णांकk("CRIME hardware intr register: %016lx\n", crime->hard_पूर्णांक);
	prपूर्णांकk("MACE ISA intr mask: %08lx\n", mace->perअगर.ctrl.imask);
	prपूर्णांकk("MACE ISA intr status: %08lx\n", mace->perअगर.ctrl.istat);
	prपूर्णांकk("MACE PCI control register: %08x\n", mace->pci.control);

	prपूर्णांकk("Register dump:\n");
	show_regs(get_irq_regs());

	prपूर्णांकk("Please mail this report to linux-mips@vger.kernel.org\n");
	prपूर्णांकk("Spinning...");
	जबतक(1) ;
पूर्ण

/* CRIME 1.1 appears to deliver all पूर्णांकerrupts to this one pin. */
/* change this to loop over all edge-triggered irqs, exception masked out ones */
अटल व्योम ip32_irq0(व्योम)
अणु
	uपूर्णांक64_t crime_पूर्णांक;
	पूर्णांक irq = 0;

	/*
	 * Sanity check पूर्णांकerrupt numbering क्रमागत.
	 * MACE got 32 पूर्णांकerrupts and there are 32 MACE ISA पूर्णांकerrupts daisy
	 * chained.
	 */
	BUILD_BUG_ON(CRIME_VICE_IRQ - MACE_VID_IN1_IRQ != 31);
	BUILD_BUG_ON(MACEISA_SERIAL2_RDMAOR_IRQ - MACEISA_AUDIO_SW_IRQ != 31);

	crime_पूर्णांक = crime->istat & crime_mask;

	/* crime someसमय delivers spurious पूर्णांकerrupts, ignore them */
	अगर (unlikely(crime_पूर्णांक == 0))
		वापस;

	irq = MACE_VID_IN1_IRQ + __ffs(crime_पूर्णांक);

	अगर (crime_पूर्णांक & CRIME_MACEISA_INT_MASK) अणु
		अचिन्हित दीर्घ mace_पूर्णांक = mace->perअगर.ctrl.istat;
		irq = __ffs(mace_पूर्णांक & maceisa_mask) + MACEISA_AUDIO_SW_IRQ;
	पूर्ण

	pr_debug("*irq %u*\n", irq);
	करो_IRQ(irq);
पूर्ण

अटल व्योम ip32_irq1(व्योम)
अणु
	ip32_unknown_पूर्णांकerrupt();
पूर्ण

अटल व्योम ip32_irq2(व्योम)
अणु
	ip32_unknown_पूर्णांकerrupt();
पूर्ण

अटल व्योम ip32_irq3(व्योम)
अणु
	ip32_unknown_पूर्णांकerrupt();
पूर्ण

अटल व्योम ip32_irq4(व्योम)
अणु
	ip32_unknown_पूर्णांकerrupt();
पूर्ण

अटल व्योम ip32_irq5(व्योम)
अणु
	करो_IRQ(MIPS_CPU_IRQ_BASE + 7);
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक pending = पढ़ो_c0_status() & पढ़ो_c0_cause();

	अगर (likely(pending & IE_IRQ0))
		ip32_irq0();
	अन्यथा अगर (unlikely(pending & IE_IRQ1))
		ip32_irq1();
	अन्यथा अगर (unlikely(pending & IE_IRQ2))
		ip32_irq2();
	अन्यथा अगर (unlikely(pending & IE_IRQ3))
		ip32_irq3();
	अन्यथा अगर (unlikely(pending & IE_IRQ4))
		ip32_irq4();
	अन्यथा अगर (likely(pending & IE_IRQ5))
		ip32_irq5();
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	अचिन्हित पूर्णांक irq;

	/* Install our पूर्णांकerrupt handler, then clear and disable all
	 * CRIME and MACE पूर्णांकerrupts. */
	crime->imask = 0;
	crime->hard_पूर्णांक = 0;
	crime->soft_पूर्णांक = 0;
	mace->perअगर.ctrl.istat = 0;
	mace->perअगर.ctrl.imask = 0;

	mips_cpu_irq_init();
	क्रम (irq = CRIME_IRQ_BASE; irq <= IP32_IRQ_MAX; irq++) अणु
		चयन (irq) अणु
		हाल MACE_VID_IN1_IRQ ... MACE_PCI_BRIDGE_IRQ:
			irq_set_chip_and_handler_name(irq,
						      &ip32_mace_पूर्णांकerrupt,
						      handle_level_irq,
						      "level");
			अवरोध;

		हाल MACEPCI_SCSI0_IRQ ...  MACEPCI_SHARED2_IRQ:
			irq_set_chip_and_handler_name(irq,
						      &ip32_macepci_पूर्णांकerrupt,
						      handle_level_irq,
						      "level");
			अवरोध;

		हाल CRIME_CPUERR_IRQ:
		हाल CRIME_MEMERR_IRQ:
			irq_set_chip_and_handler_name(irq,
						      &crime_level_पूर्णांकerrupt,
						      handle_level_irq,
						      "level");
			अवरोध;

		हाल CRIME_GBE0_IRQ ... CRIME_GBE3_IRQ:
		हाल CRIME_RE_EMPTY_E_IRQ ... CRIME_RE_IDLE_E_IRQ:
		हाल CRIME_SOFT0_IRQ ... CRIME_SOFT2_IRQ:
		हाल CRIME_VICE_IRQ:
			irq_set_chip_and_handler_name(irq,
						      &crime_edge_पूर्णांकerrupt,
						      handle_edge_irq,
						      "edge");
			अवरोध;

		हाल MACEISA_PARALLEL_IRQ:
		हाल MACEISA_SERIAL1_TDMAPR_IRQ:
		हाल MACEISA_SERIAL2_TDMAPR_IRQ:
			irq_set_chip_and_handler_name(irq,
						      &ip32_maceisa_edge_पूर्णांकerrupt,
						      handle_edge_irq,
						      "edge");
			अवरोध;

		शेष:
			irq_set_chip_and_handler_name(irq,
						      &ip32_maceisa_level_पूर्णांकerrupt,
						      handle_level_irq,
						      "level");
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (request_irq(CRIME_MEMERR_IRQ, crime_memerr_पूर्णांकr, 0,
			"CRIME memory error", शून्य))
		pr_err("Failed to register CRIME memory error interrupt\n");
	अगर (request_irq(CRIME_CPUERR_IRQ, crime_cpuerr_पूर्णांकr, 0,
			"CRIME CPU error", शून्य))
		pr_err("Failed to register CRIME CPU error interrupt\n");

#घोषणा ALLINTS (IE_IRQ0 | IE_IRQ1 | IE_IRQ2 | IE_IRQ3 | IE_IRQ4 | IE_IRQ5)
	change_c0_status(ST0_IM, ALLINTS);
पूर्ण
