<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_eb64p.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code supporting the EB64+ and EB66.
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
#समावेश <यंत्र/core_lca.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


/* Note mask bit is true क्रम DISABLED irqs.  */
अटल अचिन्हित पूर्णांक cached_irq_mask = -1;

अटल अंतरभूत व्योम
eb64p_update_irq_hw(अचिन्हित पूर्णांक irq, अचिन्हित दीर्घ mask)
अणु
	outb(mask >> (irq >= 24 ? 24 : 16), (irq >= 24 ? 0x27 : 0x26));
पूर्ण

अटल अंतरभूत व्योम
eb64p_enable_irq(काष्ठा irq_data *d)
अणु
	eb64p_update_irq_hw(d->irq, cached_irq_mask &= ~(1 << d->irq));
पूर्ण

अटल व्योम
eb64p_disable_irq(काष्ठा irq_data *d)
अणु
	eb64p_update_irq_hw(d->irq, cached_irq_mask |= 1 << d->irq);
पूर्ण

अटल काष्ठा irq_chip eb64p_irq_type = अणु
	.name		= "EB64P",
	.irq_unmask	= eb64p_enable_irq,
	.irq_mask	= eb64p_disable_irq,
	.irq_mask_ack	= eb64p_disable_irq,
पूर्ण;

अटल व्योम 
eb64p_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित दीर्घ pld;
	अचिन्हित पूर्णांक i;

	/* Read the पूर्णांकerrupt summary रेजिस्टरs */
	pld = inb(0x26) | (inb(0x27) << 8);

	/*
	 * Now, क्रम every possible bit set, work through
	 * them and call the appropriate पूर्णांकerrupt handler.
	 */
	जबतक (pld) अणु
		i = ffz(~pld);
		pld &= pld - 1;	/* clear least bit set */

		अगर (i == 5) अणु
			isa_device_पूर्णांकerrupt(vector);
		पूर्ण अन्यथा अणु
			handle_irq(16 + i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init
eb64p_init_irq(व्योम)
अणु
	दीर्घ i;

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_CABRIOLET)
	/*
	 * CABRIO SRM may not set variation correctly, so here we test
	 * the high word of the पूर्णांकerrupt summary रेजिस्टर क्रम the RAZ
	 * bits, and hope that a true EB64+ would पढ़ो all ones...
	 */
	अगर (inw(0x806) != 0xffff) अणु
		बाह्य काष्ठा alpha_machine_vector cabriolet_mv;

		prपूर्णांकk("Detected Cabriolet: correcting HWRPB.\n");

		hwrpb->sys_variation |= 2L << 10;
		hwrpb_update_checksum(hwrpb);

		alpha_mv = cabriolet_mv;
		alpha_mv.init_irq();
		वापस;
	पूर्ण
#पूर्ण_अगर /* GENERIC */

	outb(0xff, 0x26);
	outb(0xff, 0x27);

	init_i8259a_irqs();

	क्रम (i = 16; i < 32; ++i) अणु
		irq_set_chip_and_handler(i, &eb64p_irq_type, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	common_init_isa_dma();
	अगर (request_irq(16 + 5, no_action, 0, "isa-cascade", शून्य))
		pr_err("Failed to register isa-cascade interrupt\n");
पूर्ण

/*
 * PCI Fixup configuration.
 *
 * There are two 8 bit बाह्यal summary रेजिस्टरs as follows:
 *
 * Summary @ 0x26:
 * Bit      Meaning
 * 0        Interrupt Line A from slot 0
 * 1        Interrupt Line A from slot 1
 * 2        Interrupt Line B from slot 0
 * 3        Interrupt Line B from slot 1
 * 4        Interrupt Line C from slot 0
 * 5        Interrupt line from the two ISA PICs
 * 6        Tulip
 * 7        NCR SCSI
 *
 * Summary @ 0x27
 * Bit      Meaning
 * 0        Interrupt Line C from slot 1
 * 1        Interrupt Line D from slot 0
 * 2        Interrupt Line D from slot 1
 * 3        RAZ
 * 4        RAZ
 * 5        RAZ
 * 6        RAZ
 * 7        RAZ
 *
 * The device to slot mapping looks like:
 *
 * Slot     Device
 *  5       NCR SCSI controller
 *  6       PCI on board slot 0
 *  7       PCI on board slot 1
 *  8       Intel SIO PCI-ISA bridge chip
 *  9       Tulip - DECchip 21040 Ethernet controller
 *   
 *
 * This two layered पूर्णांकerrupt approach means that we allocate IRQ 16 and 
 * above क्रम PCI पूर्णांकerrupts.  The IRQ relates to which bit the पूर्णांकerrupt
 * comes in on.  This makes पूर्णांकerrupt processing much easier.
 */

अटल पूर्णांक
eb64p_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[5][5] = अणु
		/*INT  INTA  INTB  INTC   INTD */
		अणु16+7, 16+7, 16+7, 16+7,  16+7पूर्ण,  /* IdSel 5,  slot ?, ?? */
		अणु16+0, 16+0, 16+2, 16+4,  16+9पूर्ण,  /* IdSel 6,  slot ?, ?? */
		अणु16+1, 16+1, 16+3, 16+8, 16+10पूर्ण,  /* IdSel 7,  slot ?, ?? */
		अणु  -1,   -1,   -1,   -1,    -1पूर्ण,  /* IdSel 8,  SIO */
		अणु16+6, 16+6, 16+6, 16+6,  16+6पूर्ण,  /* IdSel 9,  TULIP */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 5, max_idsel = 9, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण


/*
 * The System Vector
 */

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EB64P)
काष्ठा alpha_machine_vector eb64p_mv __iniपंचांगv = अणु
	.vector_name		= "EB64+",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_APECS_IO,
	.machine_check		= apecs_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 32,
	.device_पूर्णांकerrupt	= eb64p_device_पूर्णांकerrupt,

	.init_arch		= apecs_init_arch,
	.init_irq		= eb64p_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= common_init_pci,
	.समाप्त_arch		= शून्य,
	.pci_map_irq		= eb64p_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(eb64p)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EB66)
काष्ठा alpha_machine_vector eb66_mv __iniपंचांगv = अणु
	.vector_name		= "EB66",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_LCA_IO,
	.machine_check		= lca_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 32,
	.device_पूर्णांकerrupt	= eb64p_device_पूर्णांकerrupt,

	.init_arch		= lca_init_arch,
	.init_irq		= eb64p_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= common_init_pci,
	.pci_map_irq		= eb64p_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(eb66)
#पूर्ण_अगर
