<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_cabriolet.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999, 2000 Riअक्षरd Henderson
 *
 * Code supporting the Cabriolet (AlphaPC64), EB66+, and EB164,
 * PC164 and LX164.
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
#समावेश <यंत्र/core_apecs.h>
#समावेश <यंत्र/core_cia.h>
#समावेश <यंत्र/core_lca.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"
#समावेश "pc873xx.h"

/* Note mask bit is true क्रम DISABLED irqs.  */
अटल अचिन्हित दीर्घ cached_irq_mask = ~0UL;

अटल अंतरभूत व्योम
cabriolet_update_irq_hw(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ mask)
अणु
	पूर्णांक ofs = (irq - 16) / 8;
	outb(mask >> (16 + ofs * 8), 0x804 + ofs);
पूर्ण

अटल अंतरभूत व्योम
cabriolet_enable_irq(काष्ठा irq_data *d)
अणु
	cabriolet_update_irq_hw(d->irq, cached_irq_mask &= ~(1UL << d->irq));
पूर्ण

अटल व्योम
cabriolet_disable_irq(काष्ठा irq_data *d)
अणु
	cabriolet_update_irq_hw(d->irq, cached_irq_mask |= 1UL << d->irq);
पूर्ण

अटल काष्ठा irq_chip cabriolet_irq_type = अणु
	.name		= "CABRIOLET",
	.irq_unmask	= cabriolet_enable_irq,
	.irq_mask	= cabriolet_disable_irq,
	.irq_mask_ack	= cabriolet_disable_irq,
पूर्ण;

अटल व्योम 
cabriolet_device_पूर्णांकerrupt(अचिन्हित दीर्घ v)
अणु
	अचिन्हित दीर्घ pld;
	अचिन्हित पूर्णांक i;

	/* Read the पूर्णांकerrupt summary रेजिस्टरs */
	pld = inb(0x804) | (inb(0x805) << 8) | (inb(0x806) << 16);

	/*
	 * Now क्रम every possible bit set, work through them and call
	 * the appropriate पूर्णांकerrupt handler.
	 */
	जबतक (pld) अणु
		i = ffz(~pld);
		pld &= pld - 1;	/* clear least bit set */
		अगर (i == 4) अणु
			isa_device_पूर्णांकerrupt(v);
		पूर्ण अन्यथा अणु
			handle_irq(16 + i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init
common_init_irq(व्योम (*srm_dev_पूर्णांक)(अचिन्हित दीर्घ v))
अणु
	init_i8259a_irqs();

	अगर (alpha_using_srm) अणु
		alpha_mv.device_पूर्णांकerrupt = srm_dev_पूर्णांक;
		init_srm_irqs(35, 0);
	पूर्ण
	अन्यथा अणु
		दीर्घ i;

		outb(0xff, 0x804);
		outb(0xff, 0x805);
		outb(0xff, 0x806);

		क्रम (i = 16; i < 35; ++i) अणु
			irq_set_chip_and_handler(i, &cabriolet_irq_type,
						 handle_level_irq);
			irq_set_status_flags(i, IRQ_LEVEL);
		पूर्ण
	पूर्ण

	common_init_isa_dma();
	अगर (request_irq(16 + 4, no_action, 0, "isa-cascade", शून्य))
		pr_err("Failed to register isa-cascade interrupt\n");
पूर्ण

#अगर_अघोषित CONFIG_ALPHA_PC164
अटल व्योम __init
cabriolet_init_irq(व्योम)
अणु
	common_init_irq(srm_device_पूर्णांकerrupt);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_PC164)
/* In theory, the PC164 has the same पूर्णांकerrupt hardware as the other
   Cabriolet based प्रणालीs.  However, something got screwed up late
   in the development cycle which broke the पूर्णांकerrupt masking hardware.
   Repeat, it is not possible to mask and ack पूर्णांकerrupts.  At all.

   In an attempt to work around this, जबतक processing पूर्णांकerrupts,
   we करो not allow the IPL to drop below what it is currently.  This
   prevents the possibility of recursion.  

   ??? Another option might be to क्रमce all PCI devices to use edge
   triggered rather than level triggered पूर्णांकerrupts.  That might be
   too invasive though.  */

अटल व्योम
pc164_srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ v)
अणु
	__min_ipl = getipl();
	srm_device_पूर्णांकerrupt(v);
	__min_ipl = 0;
पूर्ण

अटल व्योम
pc164_device_पूर्णांकerrupt(अचिन्हित दीर्घ v)
अणु
	__min_ipl = getipl();
	cabriolet_device_पूर्णांकerrupt(v);
	__min_ipl = 0;
पूर्ण

अटल व्योम __init
pc164_init_irq(व्योम)
अणु
	common_init_irq(pc164_srm_device_पूर्णांकerrupt);
पूर्ण
#पूर्ण_अगर

/*
 * The EB66+ is very similar to the EB66 except that it करोes not have
 * the on-board NCR and Tulip chips.  In the code below, I have used
 * slot number to refer to the id select line and *not* the slot
 * number used in the EB66+ करोcumentation.  However, in the table,
 * I've given the slot number, the id select line and the Jxx number
 * that's prपूर्णांकed on the board.  The पूर्णांकerrupt pins from the PCI slots
 * are wired पूर्णांकo 3 पूर्णांकerrupt summary रेजिस्टरs at 0x804, 0x805 and
 * 0x806 ISA.
 *
 * In the table, -1 means करोn't assign an IRQ number.  This is usually
 * because it is the Saturn IO (SIO) PCI/ISA Bridge Chip.
 */

अटल अंतरभूत पूर्णांक
eb66p_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[5][5] = अणु
		/*INT  INTA  INTB  INTC   INTD */
		अणु16+0, 16+0, 16+5,  16+9, 16+13पूर्ण,  /* IdSel 6,  slot 0, J25 */
		अणु16+1, 16+1, 16+6, 16+10, 16+14पूर्ण,  /* IdSel 7,  slot 1, J26 */
		अणु  -1,   -1,   -1,    -1,    -1पूर्ण,  /* IdSel 8,  SIO         */
		अणु16+2, 16+2, 16+7, 16+11, 16+15पूर्ण,  /* IdSel 9,  slot 2, J27 */
		अणु16+3, 16+3, 16+8, 16+12,  16+6पूर्ण   /* IdSel 10, slot 3, J28 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 6, max_idsel = 10, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण


/*
 * The AlphaPC64 is very similar to the EB66+ except that its slots
 * are numbered dअगरferently.  In the code below, I have used slot
 * number to refer to the id select line and *not* the slot number
 * used in the AlphaPC64 करोcumentation.  However, in the table, I've
 * given the slot number, the id select line and the Jxx number that's
 * prपूर्णांकed on the board.  The पूर्णांकerrupt pins from the PCI slots are
 * wired पूर्णांकo 3 पूर्णांकerrupt summary रेजिस्टरs at 0x804, 0x805 and 0x806
 * ISA.
 *
 * In the table, -1 means करोn't assign an IRQ number.  This is usually
 * because it is the Saturn IO (SIO) PCI/ISA Bridge Chip.
 */

अटल अंतरभूत पूर्णांक
cabriolet_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[5][5] = अणु
		/*INT   INTA  INTB  INTC   INTD */
		अणु 16+2, 16+2, 16+7, 16+11, 16+15पूर्ण, /* IdSel 5,  slot 2, J21 */
		अणु 16+0, 16+0, 16+5,  16+9, 16+13पूर्ण, /* IdSel 6,  slot 0, J19 */
		अणु 16+1, 16+1, 16+6, 16+10, 16+14पूर्ण, /* IdSel 7,  slot 1, J20 */
		अणु   -1,   -1,   -1,    -1,    -1पूर्ण, /* IdSel 8,  SIO         */
		अणु 16+3, 16+3, 16+8, 16+12, 16+16पूर्ण  /* IdSel 9,  slot 3, J22 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 5, max_idsel = 9, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण

अटल अंतरभूत व्योम __init
cabriolet_enable_ide(व्योम)
अणु
	अगर (pc873xx_probe() == -1) अणु
		prपूर्णांकk(KERN_ERR "Probing for PC873xx Super IO chip failed.\n");
	 पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "Found %s Super IO chip at 0x%x\n",
			pc873xx_get_model(), pc873xx_get_base());

		pc873xx_enable_ide();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __init
cabriolet_init_pci(व्योम)
अणु
	common_init_pci();
	cabriolet_enable_ide();
पूर्ण

अटल अंतरभूत व्योम __init
cia_cab_init_pci(व्योम)
अणु
	cia_init_pci();
	cabriolet_enable_ide();
पूर्ण

/*
 * The PC164 and LX164 have 19 PCI पूर्णांकerrupts, four from each of the four
 * PCI slots, the SIO, PCI/IDE, and USB.
 * 
 * Each of the पूर्णांकerrupts can be inभागidually masked. This is
 * accomplished by setting the appropriate bit in the mask रेजिस्टर.
 * A bit is set by writing a "1" to the desired position in the mask
 * रेजिस्टर and cleared by writing a "0". There are 3 mask रेजिस्टरs
 * located at ISA address 804h, 805h and 806h.
 * 
 * An I/O पढ़ो at ISA address 804h, 805h, 806h will वापस the
 * state of the 11 PCI पूर्णांकerrupts and not the state of the MASKED
 * पूर्णांकerrupts.
 * 
 * Note: A ग_लिखो to I/O 804h, 805h, and 806h the mask रेजिस्टर will be
 * updated.
 * 
 * 
 * 				ISA DATA<7:0>
 * ISA     +--------------------------------------------------------------+
 * ADDRESS |   7   |   6   |   5   |   4   |   3   |   2  |   1   |   0   |
 *         +==============================================================+
 * 0x804   | INTB0 |  USB  |  IDE  |  SIO  | INTA3 |INTA2 | INTA1 | INTA0 |
 *         +--------------------------------------------------------------+
 * 0x805   | INTD0 | INTC3 | INTC2 | INTC1 | INTC0 |INTB3 | INTB2 | INTB1 |
 *         +--------------------------------------------------------------+
 * 0x806   | Rsrv  | Rsrv  | Rsrv  | Rsrv  | Rsrv  |INTD3 | INTD2 | INTD1 |
 *         +--------------------------------------------------------------+
 *         * Rsrv = reserved bits
 *         Note: The mask रेजिस्टर is ग_लिखो-only.
 * 
 * IdSel	
 *   5	 32 bit PCI option slot 2
 *   6	 64 bit PCI option slot 0
 *   7	 64 bit PCI option slot 1
 *   8	 Saturn I/O
 *   9	 32 bit PCI option slot 3
 *  10	 USB
 *  11	 IDE
 * 
 */

अटल अंतरभूत पूर्णांक
alphapc164_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[7][5] = अणु
		/*INT   INTA  INTB   INTC   INTD */
		अणु 16+2, 16+2, 16+9,  16+13, 16+17पूर्ण, /* IdSel  5, slot 2, J20 */
		अणु 16+0, 16+0, 16+7,  16+11, 16+15पूर्ण, /* IdSel  6, slot 0, J29 */
		अणु 16+1, 16+1, 16+8,  16+12, 16+16पूर्ण, /* IdSel  7, slot 1, J26 */
		अणु   -1,   -1,   -1,    -1,    -1पूर्ण,  /* IdSel  8, SIO */
		अणु 16+3, 16+3, 16+10, 16+14, 16+18पूर्ण, /* IdSel  9, slot 3, J19 */
		अणु 16+6, 16+6, 16+6,  16+6,  16+6पूर्ण,  /* IdSel 10, USB */
		अणु 16+5, 16+5, 16+5,  16+5,  16+5पूर्ण   /* IdSel 11, IDE */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 5, max_idsel = 11, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण

अटल अंतरभूत व्योम __init
alphapc164_init_pci(व्योम)
अणु
	cia_init_pci();
	SMC93x_Init();
पूर्ण


/*
 * The System Vector
 */

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_CABRIOLET)
काष्ठा alpha_machine_vector cabriolet_mv __iniपंचांगv = अणु
	.vector_name		= "Cabriolet",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_APECS_IO,
	.machine_check		= apecs_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 35,
	.device_पूर्णांकerrupt	= cabriolet_device_पूर्णांकerrupt,

	.init_arch		= apecs_init_arch,
	.init_irq		= cabriolet_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= cabriolet_init_pci,
	.pci_map_irq		= cabriolet_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
#अगर_अघोषित CONFIG_ALPHA_EB64P
ALIAS_MV(cabriolet)
#पूर्ण_अगर
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EB164)
काष्ठा alpha_machine_vector eb164_mv __iniपंचांगv = अणु
	.vector_name		= "EB164",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= CIA_DEFAULT_MEM_BASE,

	.nr_irqs		= 35,
	.device_पूर्णांकerrupt	= cabriolet_device_पूर्णांकerrupt,

	.init_arch		= cia_init_arch,
	.init_irq		= cabriolet_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= cia_cab_init_pci,
	.समाप्त_arch		= cia_समाप्त_arch,
	.pci_map_irq		= cabriolet_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(eb164)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EB66P)
काष्ठा alpha_machine_vector eb66p_mv __iniपंचांगv = अणु
	.vector_name		= "EB66+",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_LCA_IO,
	.machine_check		= lca_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 35,
	.device_पूर्णांकerrupt	= cabriolet_device_पूर्णांकerrupt,

	.init_arch		= lca_init_arch,
	.init_irq		= cabriolet_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= cabriolet_init_pci,
	.pci_map_irq		= eb66p_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(eb66p)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_LX164)
काष्ठा alpha_machine_vector lx164_mv __iniपंचांगv = अणु
	.vector_name		= "LX164",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_PYXIS_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= PYXIS_DAC_OFFSET,

	.nr_irqs		= 35,
	.device_पूर्णांकerrupt	= cabriolet_device_पूर्णांकerrupt,

	.init_arch		= pyxis_init_arch,
	.init_irq		= cabriolet_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= alphapc164_init_pci,
	.समाप्त_arch		= cia_समाप्त_arch,
	.pci_map_irq		= alphapc164_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(lx164)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_PC164)
काष्ठा alpha_machine_vector pc164_mv __iniपंचांगv = अणु
	.vector_name		= "PC164",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= CIA_DEFAULT_MEM_BASE,

	.nr_irqs		= 35,
	.device_पूर्णांकerrupt	= pc164_device_पूर्णांकerrupt,

	.init_arch		= cia_init_arch,
	.init_irq		= pc164_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= alphapc164_init_pci,
	.समाप्त_arch		= cia_समाप्त_arch,
	.pci_map_irq		= alphapc164_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(pc164)
#पूर्ण_अगर
