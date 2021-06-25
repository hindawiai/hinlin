<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_sx164.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999, 2000 Riअक्षरd Henderson
 *
 * Code supporting the SX164 (PCA56+PYXIS).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_cia.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/special_insns.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


अटल व्योम __init
sx164_init_irq(व्योम)
अणु
	outb(0, DMA1_RESET_REG);
	outb(0, DMA2_RESET_REG);
	outb(DMA_MODE_CASCADE, DMA2_MODE_REG);
	outb(0, DMA2_MASK_REG);

	अगर (alpha_using_srm)
		alpha_mv.device_पूर्णांकerrupt = srm_device_पूर्णांकerrupt;

	init_i8259a_irqs();

	/* Not पूर्णांकerested in the bogus पूर्णांकerrupts (0,3,4,5,40-47),
	   NMI (1), or HALT (2).  */
	अगर (alpha_using_srm)
		init_srm_irqs(40, 0x3f0000);
	अन्यथा
		init_pyxis_irqs(0xff00003f0000UL);

	अगर (request_irq(16 + 6, no_action, 0, "timer-cascade", शून्य))
		pr_err("Failed to register timer-cascade interrupt\n");
पूर्ण

/*
 * PCI Fixup configuration.
 *
 * Summary @ PYXIS_INT_REQ:
 * Bit      Meaning
 * 0        RSVD
 * 1        NMI
 * 2        Halt/Reset चयन
 * 3        MBZ
 * 4        RAZ
 * 5        RAZ
 * 6        Interval समयr (RTC)
 * 7        PCI-ISA Bridge
 * 8        Interrupt Line A from slot 3
 * 9        Interrupt Line A from slot 2
 *10        Interrupt Line A from slot 1
 *11        Interrupt Line A from slot 0
 *12        Interrupt Line B from slot 3
 *13        Interrupt Line B from slot 2
 *14        Interrupt Line B from slot 1
 *15        Interrupt line B from slot 0
 *16        Interrupt Line C from slot 3
 *17        Interrupt Line C from slot 2
 *18        Interrupt Line C from slot 1
 *19        Interrupt Line C from slot 0
 *20        Interrupt Line D from slot 3
 *21        Interrupt Line D from slot 2
 *22        Interrupt Line D from slot 1
 *23        Interrupt Line D from slot 0
 *
 * IdSel       
 *   5  32 bit PCI option slot 2
 *   6  64 bit PCI option slot 0
 *   7  64 bit PCI option slot 1
 *   8  Cypress I/O
 *   9  32 bit PCI option slot 3
 */

अटल पूर्णांक
sx164_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[5][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु 16+ 9, 16+ 9, 16+13, 16+17, 16+21पूर्ण, /* IdSel 5 slot 2 J17 */
		अणु 16+11, 16+11, 16+15, 16+19, 16+23पूर्ण, /* IdSel 6 slot 0 J19 */
		अणु 16+10, 16+10, 16+14, 16+18, 16+22पूर्ण, /* IdSel 7 slot 1 J18 */
		अणु    -1,    -1,    -1,	  -1,    -1पूर्ण, /* IdSel 8 SIO        */
		अणु 16+ 8, 16+ 8, 16+12, 16+16, 16+20पूर्ण  /* IdSel 9 slot 3 J15 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 5, max_idsel = 9, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण

अटल व्योम __init
sx164_init_pci(व्योम)
अणु
	cia_init_pci();
	SMC669_Init(0);
पूर्ण

अटल व्योम __init
sx164_init_arch(व्योम)
अणु
	/*
	 * OSF palcode v1.23 क्रममाला_लो to enable PCA56 Motion Video
	 * Inकाष्ठाions. Let's enable it.
	 * We have to check palcode revision because CSERVE पूर्णांकerface
	 * is subject to change without notice. For example, it
	 * has been changed completely since v1.16 (found in MILO
	 * distribution). -ink
	 */
	काष्ठा percpu_काष्ठा *cpu = (काष्ठा percpu_काष्ठा*)
		((अक्षर*)hwrpb + hwrpb->processor_offset);

	अगर (amask(AMASK_MAX) != 0
	    && alpha_using_srm
	    && (cpu->pal_revision & 0xffff) <= 0x117) अणु
		__यंत्र__ __अस्थिर__(
		"lda	$16,8($31)\n"
		"call_pal 9\n"		/* Allow PALRES insns in kernel mode */
		".long  0x64000118\n\n"	/* hw_mfpr $0,icsr */
		"ldah	$16,(1<<(19-16))($31)\n"
		"or	$0,$16,$0\n"	/* set MVE bit */
		".long  0x74000118\n"	/* hw_mtpr $0,icsr */
		"lda	$16,9($31)\n"
		"call_pal 9"		/* Disable PALRES insns */
		: : : "$0", "$16");
		prपूर्णांकk("PCA56 MVI set enabled\n");
	पूर्ण

	pyxis_init_arch();
पूर्ण

/*
 * The System Vector
 */

काष्ठा alpha_machine_vector sx164_mv __iniपंचांगv = अणु
	.vector_name		= "SX164",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_PYXIS_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= PYXIS_DAC_OFFSET,

	.nr_irqs		= 48,
	.device_पूर्णांकerrupt	= pyxis_device_पूर्णांकerrupt,

	.init_arch		= sx164_init_arch,
	.init_irq		= sx164_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= sx164_init_pci,
	.समाप्त_arch		= cia_समाप्त_arch,
	.pci_map_irq		= sx164_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(sx164)
