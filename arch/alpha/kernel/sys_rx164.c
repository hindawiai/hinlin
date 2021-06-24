<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_rx164.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code supporting the RX164 (PCA56+POLARIS).
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
#समावेश <यंत्र/core_polaris.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


/* Note mask bit is true क्रम ENABLED irqs.  */
अटल अचिन्हित दीर्घ cached_irq_mask;

अटल अंतरभूत व्योम
rx164_update_irq_hw(अचिन्हित दीर्घ mask)
अणु
	अस्थिर अचिन्हित पूर्णांक *irq_mask;

	irq_mask = (व्योम *)(POLARIS_DENSE_CONFIG_BASE + 0x74);
	*irq_mask = mask;
	mb();
	*irq_mask;
पूर्ण

अटल अंतरभूत व्योम
rx164_enable_irq(काष्ठा irq_data *d)
अणु
	rx164_update_irq_hw(cached_irq_mask |= 1UL << (d->irq - 16));
पूर्ण

अटल व्योम
rx164_disable_irq(काष्ठा irq_data *d)
अणु
	rx164_update_irq_hw(cached_irq_mask &= ~(1UL << (d->irq - 16)));
पूर्ण

अटल काष्ठा irq_chip rx164_irq_type = अणु
	.name		= "RX164",
	.irq_unmask	= rx164_enable_irq,
	.irq_mask	= rx164_disable_irq,
	.irq_mask_ack	= rx164_disable_irq,
पूर्ण;

अटल व्योम 
rx164_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित दीर्घ pld;
	अस्थिर अचिन्हित पूर्णांक *dirr;
	दीर्घ i;

	/* Read the पूर्णांकerrupt summary रेजिस्टर.  On Polaris, this is
	   the सूचीR रेजिस्टर in PCI config space (offset 0x84).  */
	dirr = (व्योम *)(POLARIS_DENSE_CONFIG_BASE + 0x84);
	pld = *dirr;

	/*
	 * Now क्रम every possible bit set, work through them and call
	 * the appropriate पूर्णांकerrupt handler.
	 */
	जबतक (pld) अणु
		i = ffz(~pld);
		pld &= pld - 1; /* clear least bit set */
		अगर (i == 20) अणु
			isa_no_iack_sc_device_पूर्णांकerrupt(vector);
		पूर्ण अन्यथा अणु
			handle_irq(16+i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init
rx164_init_irq(व्योम)
अणु
	दीर्घ i;

	rx164_update_irq_hw(0);
	क्रम (i = 16; i < 40; ++i) अणु
		irq_set_chip_and_handler(i, &rx164_irq_type, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	init_i8259a_irqs();
	common_init_isa_dma();

	अगर (request_irq(16 + 20, no_action, 0, "isa-cascade", शून्य))
		pr_err("Failed to register isa-cascade interrupt\n");
पूर्ण


/*
 * The RX164 changed its पूर्णांकerrupt routing between pass1 and pass2...
 *
 * PASS1:
 *
 *      Slot    IDSEL   INTA    INTB    INTC    INTD    
 *      0       6       5       10      15      20
 *      1       7       4       9       14      19
 *      2       5       3       8       13      18
 *      3       9       2       7       12      17
 *      4       10      1       6       11      16
 *
 * PASS2:
 *      Slot    IDSEL   INTA    INTB    INTC    INTD    
 *      0       5       1       7       12      17
 *      1       6       2       8       13      18
 *      2       8       3       9       14      19
 *      3       9       4       10      15      20
 *      4       10      5       11      16      6
 *      
 */

/*
 * IdSel       
 *   5  32 bit PCI option slot 0
 *   6  64 bit PCI option slot 1
 *   7  PCI-ISA bridge
 *   7  64 bit PCI option slot 2
 *   9  32 bit PCI option slot 3
 *  10  PCI-PCI bridge
 * 
 */

अटल पूर्णांक
rx164_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
#अगर 0
	अटल अक्षर irq_tab_pass1[6][5] __initdata = अणु
	  /*INT   INTA  INTB  INTC   INTD */
	  अणु 16+3, 16+3, 16+8, 16+13, 16+18पूर्ण,      /* IdSel 5,  slot 2 */
	  अणु 16+5, 16+5, 16+10, 16+15, 16+20पूर्ण,     /* IdSel 6,  slot 0 */
	  अणु 16+4, 16+4, 16+9, 16+14, 16+19पूर्ण,      /* IdSel 7,  slot 1 */
	  अणु -1,     -1,    -1,    -1,   -1पूर्ण,      /* IdSel 8, PCI/ISA bridge */
	  अणु 16+2, 16+2, 16+7, 16+12, 16+17पूर्ण,      /* IdSel 9,  slot 3 */
	  अणु 16+1, 16+1, 16+6, 16+11, 16+16पूर्ण,      /* IdSel 10, slot 4 */
	पूर्ण;
#अन्यथा
	अटल अक्षर irq_tab[6][5] = अणु
	  /*INT   INTA  INTB  INTC   INTD */
	  अणु 16+0, 16+0, 16+6, 16+11, 16+16पूर्ण,      /* IdSel 5,  slot 0 */
	  अणु 16+1, 16+1, 16+7, 16+12, 16+17पूर्ण,      /* IdSel 6,  slot 1 */
	  अणु -1,     -1,    -1,    -1,   -1पूर्ण,      /* IdSel 7, PCI/ISA bridge */
	  अणु 16+2, 16+2, 16+8, 16+13, 16+18पूर्ण,      /* IdSel 8,  slot 2 */
	  अणु 16+3, 16+3, 16+9, 16+14, 16+19पूर्ण,      /* IdSel 9,  slot 3 */
	  अणु 16+4, 16+4, 16+10, 16+15, 16+5पूर्ण,      /* IdSel 10, PCI-PCI */
	पूर्ण;
#पूर्ण_अगर
	स्थिर दीर्घ min_idsel = 5, max_idsel = 10, irqs_per_slot = 5;

	/* JRP - Need to figure out how to distinguish pass1 from pass2,
	   and use the correct table.  */
	वापस COMMON_TABLE_LOOKUP;
पूर्ण


/*
 * The System Vector
 */

काष्ठा alpha_machine_vector rx164_mv __iniपंचांगv = अणु
	.vector_name		= "RX164",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_POLARIS_IO,
	.machine_check		= polaris_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,

	.nr_irqs		= 40,
	.device_पूर्णांकerrupt	= rx164_device_पूर्णांकerrupt,

	.init_arch		= polaris_init_arch,
	.init_irq		= rx164_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= common_init_pci,
	.समाप्त_arch		= शून्य,
	.pci_map_irq		= rx164_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(rx164)
