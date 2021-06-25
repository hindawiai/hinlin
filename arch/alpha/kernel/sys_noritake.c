<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_noritake.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code supporting the NORITAKE (AlphaServer 1000A), 
 * CORELLE (AlphaServer 800), and ALCOR Primo (AlphaStation 600A).
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
noritake_update_irq_hw(पूर्णांक irq, पूर्णांक mask)
अणु
	पूर्णांक port = 0x54a;
	अगर (irq >= 32) अणु
	    mask >>= 16;
	    port = 0x54c;
	पूर्ण
	outw(mask, port);
पूर्ण

अटल व्योम
noritake_enable_irq(काष्ठा irq_data *d)
अणु
	noritake_update_irq_hw(d->irq, cached_irq_mask |= 1 << (d->irq - 16));
पूर्ण

अटल व्योम
noritake_disable_irq(काष्ठा irq_data *d)
अणु
	noritake_update_irq_hw(d->irq, cached_irq_mask &= ~(1 << (d->irq - 16)));
पूर्ण

अटल काष्ठा irq_chip noritake_irq_type = अणु
	.name		= "NORITAKE",
	.irq_unmask	= noritake_enable_irq,
	.irq_mask	= noritake_disable_irq,
	.irq_mask_ack	= noritake_disable_irq,
पूर्ण;

अटल व्योम 
noritake_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित दीर्घ pld;
	अचिन्हित पूर्णांक i;

	/* Read the पूर्णांकerrupt summary रेजिस्टरs of NORITAKE */
	pld = (((अचिन्हित दीर्घ) inw(0x54c) << 32)
	       | ((अचिन्हित दीर्घ) inw(0x54a) << 16)
	       | ((अचिन्हित दीर्घ) inb(0xa0) << 8)
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

अटल व्योम 
noritake_srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq;

	irq = (vector - 0x800) >> 4;

	/*
	 * I really hate to करो this, too, but the NORITAKE SRM console also
	 * reports PCI vectors *lower* than I expected from the bit numbers
	 * in the करोcumentation.
	 * But I really करोn't want to change the fixup code क्रम allocation
	 * of IRQs, nor the alpha_irq_mask मुख्यtenance stuff, both of which
	 * look nice and clean now.
	 * So, here's this additional grotty hack... :-(
	 */
	अगर (irq >= 16)
		irq = irq + 1;

	handle_irq(irq);
पूर्ण

अटल व्योम __init
noritake_init_irq(व्योम)
अणु
	दीर्घ i;

	अगर (alpha_using_srm)
		alpha_mv.device_पूर्णांकerrupt = noritake_srm_device_पूर्णांकerrupt;

	outw(0, 0x54a);
	outw(0, 0x54c);

	क्रम (i = 16; i < 48; ++i) अणु
		irq_set_chip_and_handler(i, &noritake_irq_type,
					 handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	init_i8259a_irqs();
	common_init_isa_dma();
पूर्ण


/*
 * PCI Fixup configuration.
 *
 * Summary @ 0x542, summary रेजिस्टर #1:
 * Bit      Meaning
 * 0        All valid पूर्णांकs from summary regs 2 & 3
 * 1        QLOGIC ISP1020A SCSI
 * 2        Interrupt Line A from slot 0
 * 3        Interrupt Line B from slot 0
 * 4        Interrupt Line A from slot 1
 * 5        Interrupt line B from slot 1
 * 6        Interrupt Line A from slot 2
 * 7        Interrupt Line B from slot 2
 * 8        Interrupt Line A from slot 3
 * 9        Interrupt Line B from slot 3
 *10        Interrupt Line A from slot 4
 *11        Interrupt Line B from slot 4
 *12        Interrupt Line A from slot 5
 *13        Interrupt Line B from slot 5
 *14        Interrupt Line A from slot 6
 *15        Interrupt Line B from slot 6
 *
 * Summary @ 0x544, summary रेजिस्टर #2:
 * Bit      Meaning
 * 0        OR of all unmasked पूर्णांकs in SR #2
 * 1        OR of secondary bus पूर्णांकs
 * 2        Interrupt Line C from slot 0
 * 3        Interrupt Line D from slot 0
 * 4        Interrupt Line C from slot 1
 * 5        Interrupt line D from slot 1
 * 6        Interrupt Line C from slot 2
 * 7        Interrupt Line D from slot 2
 * 8        Interrupt Line C from slot 3
 * 9        Interrupt Line D from slot 3
 *10        Interrupt Line C from slot 4
 *11        Interrupt Line D from slot 4
 *12        Interrupt Line C from slot 5
 *13        Interrupt Line D from slot 5
 *14        Interrupt Line C from slot 6
 *15        Interrupt Line D from slot 6
 *
 * The device to slot mapping looks like:
 *
 * Slot     Device
 *  7       Intel PCI-EISA bridge chip
 *  8       DEC PCI-PCI bridge chip
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
noritake_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[15][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		/* note: IDSELs 16, 17, and 25 are CORELLE only */
		अणु 16+1,  16+1,  16+1,  16+1,  16+1पूर्ण,  /* IdSel 16,  QLOGIC */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 17, S3 Trio64 */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 18,  PCEB */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 19,  PPB  */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 20,  ???? */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 21,  ???? */
		अणु 16+2,  16+2,  16+3,  32+2,  32+3पूर्ण,  /* IdSel 22,  slot 0 */
		अणु 16+4,  16+4,  16+5,  32+4,  32+5पूर्ण,  /* IdSel 23,  slot 1 */
		अणु 16+6,  16+6,  16+7,  32+6,  32+7पूर्ण,  /* IdSel 24,  slot 2 */
		अणु 16+8,  16+8,  16+9,  32+8,  32+9पूर्ण,  /* IdSel 25,  slot 3 */
		/* The following 5 are actually on PCI bus 1, which is 
		   across the built-in bridge of the NORITAKE only.  */
		अणु 16+1,  16+1,  16+1,  16+1,  16+1पूर्ण,  /* IdSel 16,  QLOGIC */
		अणु 16+8,  16+8,  16+9,  32+8,  32+9पूर्ण,  /* IdSel 17,  slot 3 */
		अणु16+10, 16+10, 16+11, 32+10, 32+11पूर्ण,  /* IdSel 18,  slot 4 */
		अणु16+12, 16+12, 16+13, 32+12, 32+13पूर्ण,  /* IdSel 19,  slot 5 */
		अणु16+14, 16+14, 16+15, 32+14, 32+15पूर्ण,  /* IdSel 20,  slot 6 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 5, max_idsel = 19, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण

अटल u8
noritake_swizzle(काष्ठा pci_dev *dev, u8 *pinp)
अणु
	पूर्णांक slot, pin = *pinp;

	अगर (dev->bus->number == 0) अणु
		slot = PCI_SLOT(dev->devfn);
	पूर्ण
	/* Check क्रम the built-in bridge */
	अन्यथा अगर (PCI_SLOT(dev->bus->self->devfn) == 8) अणु
		slot = PCI_SLOT(dev->devfn) + 15; /* WAG! */
	पूर्ण
	अन्यथा
	अणु
		/* Must be a card-based bridge.  */
		करो अणु
			अगर (PCI_SLOT(dev->bus->self->devfn) == 8) अणु
				slot = PCI_SLOT(dev->devfn) + 15;
				अवरोध;
			पूर्ण
			pin = pci_swizzle_पूर्णांकerrupt_pin(dev, pin);

			/* Move up the chain of bridges.  */
			dev = dev->bus->self;
			/* Slot of the next bridge.  */
			slot = PCI_SLOT(dev->devfn);
		पूर्ण जबतक (dev->bus->self);
	पूर्ण
	*pinp = pin;
	वापस slot;
पूर्ण

#अगर defined(CONFIG_ALPHA_GENERIC) || !defined(CONFIG_ALPHA_PRIMO)
अटल व्योम
noritake_apecs_machine_check(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la_ptr)
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
        process_mcheck_info(vector, la_ptr, "NORITAKE APECS",
                            (mcheck_expected(0)
                             && (code == MCHK_NO_DEVSEL
                                 || code == MCHK_NO_TABT)));
पूर्ण
#पूर्ण_अगर


/*
 * The System Vectors
 */

#अगर defined(CONFIG_ALPHA_GENERIC) || !defined(CONFIG_ALPHA_PRIMO)
काष्ठा alpha_machine_vector noritake_mv __iniपंचांगv = अणु
	.vector_name		= "Noritake",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_APECS_IO,
	.machine_check		= noritake_apecs_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= EISA_DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 48,
	.device_पूर्णांकerrupt	= noritake_device_पूर्णांकerrupt,

	.init_arch		= apecs_init_arch,
	.init_irq		= noritake_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= common_init_pci,
	.pci_map_irq		= noritake_map_irq,
	.pci_swizzle		= noritake_swizzle,
पूर्ण;
ALIAS_MV(noritake)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_PRIMO)
काष्ठा alpha_machine_vector noritake_primo_mv __iniपंचांगv = अणु
	.vector_name		= "Noritake-Primo",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= EISA_DEFAULT_IO_BASE,
	.min_mem_address	= CIA_DEFAULT_MEM_BASE,

	.nr_irqs		= 48,
	.device_पूर्णांकerrupt	= noritake_device_पूर्णांकerrupt,

	.init_arch		= cia_init_arch,
	.init_irq		= noritake_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= cia_init_pci,
	.समाप्त_arch		= cia_समाप्त_arch,
	.pci_map_irq		= noritake_map_irq,
	.pci_swizzle		= noritake_swizzle,
पूर्ण;
ALIAS_MV(noritake_primo)
#पूर्ण_अगर
