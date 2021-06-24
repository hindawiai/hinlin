<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_mikasa.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code supporting the MIKASA (AlphaServer 1000).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_apecs.h>
#समावेश <यंत्र/core_cia.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


/* Note mask bit is true क्रम ENABLED irqs.  */
अटल पूर्णांक cached_irq_mask;

अटल अंतरभूत व्योम
mikasa_update_irq_hw(पूर्णांक mask)
अणु
	outw(mask, 0x536);
पूर्ण

अटल अंतरभूत व्योम
mikasa_enable_irq(काष्ठा irq_data *d)
अणु
	mikasa_update_irq_hw(cached_irq_mask |= 1 << (d->irq - 16));
पूर्ण

अटल व्योम
mikasa_disable_irq(काष्ठा irq_data *d)
अणु
	mikasa_update_irq_hw(cached_irq_mask &= ~(1 << (d->irq - 16)));
पूर्ण

अटल काष्ठा irq_chip mikasa_irq_type = अणु
	.name		= "MIKASA",
	.irq_unmask	= mikasa_enable_irq,
	.irq_mask	= mikasa_disable_irq,
	.irq_mask_ack	= mikasa_disable_irq,
पूर्ण;

अटल व्योम 
mikasa_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित दीर्घ pld;
	अचिन्हित पूर्णांक i;

	/* Read the पूर्णांकerrupt summary रेजिस्टरs */
	pld = (((~inw(0x534) & 0x0000ffffUL) << 16)
	       | (((अचिन्हित दीर्घ) inb(0xa0)) << 8)
	       | inb(0x20));

	/*
	 * Now क्रम every possible bit set, work through them and call
	 * the appropriate पूर्णांकerrupt handler.
	 */
	जबतक (pld) अणु
		i = ffz(~pld);
		pld &= pld - 1; /* clear least bit set */
		अगर (i < 16) अणु
			isa_device_पूर्णांकerrupt(vector);
		पूर्ण अन्यथा अणु
			handle_irq(i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init
mikasa_init_irq(व्योम)
अणु
	दीर्घ i;

	अगर (alpha_using_srm)
		alpha_mv.device_पूर्णांकerrupt = srm_device_पूर्णांकerrupt;

	mikasa_update_irq_hw(0);

	क्रम (i = 16; i < 32; ++i) अणु
		irq_set_chip_and_handler(i, &mikasa_irq_type,
					 handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	init_i8259a_irqs();
	common_init_isa_dma();
पूर्ण


/*
 * PCI Fixup configuration.
 *
 * Summary @ 0x536:
 * Bit      Meaning
 * 0        Interrupt Line A from slot 0
 * 1        Interrupt Line B from slot 0
 * 2        Interrupt Line C from slot 0
 * 3        Interrupt Line D from slot 0
 * 4        Interrupt Line A from slot 1
 * 5        Interrupt line B from slot 1
 * 6        Interrupt Line C from slot 1
 * 7        Interrupt Line D from slot 1
 * 8        Interrupt Line A from slot 2
 * 9        Interrupt Line B from slot 2
 *10        Interrupt Line C from slot 2
 *11        Interrupt Line D from slot 2
 *12        NCR 810 SCSI
 *13        Power Supply Fail
 *14        Temperature Warn
 *15        Reserved
 *
 * The device to slot mapping looks like:
 *
 * Slot     Device
 *  6       NCR SCSI controller
 *  7       Intel PCI-EISA bridge chip
 * 11       PCI on board slot 0
 * 12       PCI on board slot 1
 * 13       PCI on board slot 2
 *   
 *
 * This two layered पूर्णांकerrupt approach means that we allocate IRQ 16 and 
 * above क्रम PCI पूर्णांकerrupts.  The IRQ relates to which bit the पूर्णांकerrupt
 * comes in on.  This makes पूर्णांकerrupt processing much easier.
 */

अटल पूर्णांक
mikasa_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[8][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु16+12, 16+12, 16+12, 16+12, 16+12पूर्ण,	/* IdSel 17,  SCSI */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,	/* IdSel 18,  PCEB */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,	/* IdSel 19,  ???? */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,	/* IdSel 20,  ???? */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,	/* IdSel 21,  ???? */
		अणु 16+0,  16+0,  16+1,  16+2,  16+3पूर्ण,	/* IdSel 22,  slot 0 */
		अणु 16+4,  16+4,  16+5,  16+6,  16+7पूर्ण,	/* IdSel 23,  slot 1 */
		अणु 16+8,  16+8,  16+9, 16+10, 16+11पूर्ण,	/* IdSel 24,  slot 2 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 6, max_idsel = 13, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण


#अगर defined(CONFIG_ALPHA_GENERIC) || !defined(CONFIG_ALPHA_PRIMO)
अटल व्योम
mikasa_apecs_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
अणु
#घोषणा MCHK_NO_DEVSEL 0x205U
#घोषणा MCHK_NO_TABT 0x204U

	काष्ठा el_common *mchk_header;
	अचिन्हित पूर्णांक code;

	mchk_header = (काष्ठा el_common *)la_ptr;

	/* Clear the error beक्रमe any reporting.  */
	mb();
	mb(); /* magic */
	draina();
	apecs_pci_clr_err();
	wrmces(0x7);
	mb();

	code = mchk_header->code;
	process_mcheck_info(vector, la_ptr, "MIKASA APECS",
			    (mcheck_expected(0)
			     && (code == MCHK_NO_DEVSEL
			         || code == MCHK_NO_TABT)));
पूर्ण
#पूर्ण_अगर


/*
 * The System Vector
 */

#अगर defined(CONFIG_ALPHA_GENERIC) || !defined(CONFIG_ALPHA_PRIMO)
काष्ठा alpha_machine_vector mikasa_mv __iniपंचांगv = अणु
	.vector_name		= "Mikasa",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_APECS_IO,
	.machine_check		= mikasa_apecs_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 32,
	.device_पूर्णांकerrupt	= mikasa_device_पूर्णांकerrupt,

	.init_arch		= apecs_init_arch,
	.init_irq		= mikasa_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= common_init_pci,
	.pci_map_irq		= mikasa_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(mikasa)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_PRIMO)
काष्ठा alpha_machine_vector mikasa_primo_mv __iniपंचांगv = अणु
	.vector_name		= "Mikasa-Primo",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= CIA_DEFAULT_MEM_BASE,

	.nr_irqs		= 32,
	.device_पूर्णांकerrupt	= mikasa_device_पूर्णांकerrupt,

	.init_arch		= cia_init_arch,
	.init_irq		= mikasa_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= cia_init_pci,
	.समाप्त_arch		= cia_समाप्त_arch,
	.pci_map_irq		= mikasa_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(mikasa_primo)
#पूर्ण_अगर
