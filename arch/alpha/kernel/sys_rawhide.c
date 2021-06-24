<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_rawhide.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code supporting the RAWHIDE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_mcpcia.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


/*
 * HACK ALERT! only the boot cpu is used क्रम पूर्णांकerrupts.
 */


/* Note mask bit is true क्रम ENABLED irqs.  */

अटल अचिन्हित पूर्णांक hose_irq_masks[4] = अणु
	0xff0000, 0xfe0000, 0xff0000, 0xff0000
पूर्ण;
अटल अचिन्हित पूर्णांक cached_irq_masks[4];
DEFINE_SPINLOCK(rawhide_irq_lock);

अटल अंतरभूत व्योम
rawhide_update_irq_hw(पूर्णांक hose, पूर्णांक mask)
अणु
	*(vuip)MCPCIA_INT_MASK0(MCPCIA_HOSE2MID(hose)) = mask;
	mb();
	*(vuip)MCPCIA_INT_MASK0(MCPCIA_HOSE2MID(hose));
पूर्ण

#घोषणा hose_exists(h) \
  (((h) < MCPCIA_MAX_HOSES) && (cached_irq_masks[(h)] != 0))

अटल अंतरभूत व्योम 
rawhide_enable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask, hose;
	अचिन्हित पूर्णांक irq = d->irq;

	irq -= 16;
	hose = irq / 24;
	अगर (!hose_exists(hose)) /* अगर hose non-existent, निकास */
		वापस;

	irq -= hose * 24;
	mask = 1 << irq;

	spin_lock(&rawhide_irq_lock);
	mask |= cached_irq_masks[hose];
	cached_irq_masks[hose] = mask;
	rawhide_update_irq_hw(hose, mask);
	spin_unlock(&rawhide_irq_lock);
पूर्ण

अटल व्योम 
rawhide_disable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask, hose;
	अचिन्हित पूर्णांक irq = d->irq;

	irq -= 16;
	hose = irq / 24;
	अगर (!hose_exists(hose)) /* अगर hose non-existent, निकास */
		वापस;

	irq -= hose * 24;
	mask = ~(1 << irq) | hose_irq_masks[hose];

	spin_lock(&rawhide_irq_lock);
	mask &= cached_irq_masks[hose];
	cached_irq_masks[hose] = mask;
	rawhide_update_irq_hw(hose, mask);
	spin_unlock(&rawhide_irq_lock);
पूर्ण

अटल व्योम
rawhide_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक mask, mask1, hose;
	अचिन्हित पूर्णांक irq = d->irq;

	irq -= 16;
	hose = irq / 24;
	अगर (!hose_exists(hose)) /* अगर hose non-existent, निकास */
		वापस;

	irq -= hose * 24;
	mask1 = 1 << irq;
	mask = ~mask1 | hose_irq_masks[hose];

	spin_lock(&rawhide_irq_lock);

	mask &= cached_irq_masks[hose];
	cached_irq_masks[hose] = mask;
	rawhide_update_irq_hw(hose, mask);

	/* Clear the पूर्णांकerrupt.  */
	*(vuip)MCPCIA_INT_REQ(MCPCIA_HOSE2MID(hose)) = mask1;

	spin_unlock(&rawhide_irq_lock);
पूर्ण

अटल काष्ठा irq_chip rawhide_irq_type = अणु
	.name		= "RAWHIDE",
	.irq_unmask	= rawhide_enable_irq,
	.irq_mask	= rawhide_disable_irq,
	.irq_mask_ack	= rawhide_mask_and_ack_irq,
पूर्ण;

अटल व्योम 
rawhide_srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq;

	irq = (vector - 0x800) >> 4;

        /*
         * The RAWHIDE SRM console reports PCI पूर्णांकerrupts with a vector
	 * 0x80 *higher* than one might expect, as PCI IRQ 0 (ie bit 0)
	 * shows up as IRQ 24, etc, etc. We adjust it करोwn by 8 to have
	 * it line up with the actual bit numbers from the REQ रेजिस्टरs,
	 * which is how we manage the पूर्णांकerrupts/mask. Sigh...
	 *
	 * Also, PCI #1 पूर्णांकerrupts are offset some more... :-(
         */

	अगर (irq == 52) अणु
		/* SCSI on PCI1 is special.  */
		irq = 72;
	पूर्ण

	/* Adjust by which hose it is from.  */
	irq -= ((irq + 16) >> 2) & 0x38;

	handle_irq(irq);
पूर्ण

अटल व्योम __init
rawhide_init_irq(व्योम)
अणु
	काष्ठा pci_controller *hose;
	दीर्घ i;

	mcpcia_init_hoses();

	/* Clear them all; only hoses that exist will be non-zero. */
	क्रम (i = 0; i < MCPCIA_MAX_HOSES; i++) cached_irq_masks[i] = 0;

	क्रम (hose = hose_head; hose; hose = hose->next) अणु
		अचिन्हित पूर्णांक h = hose->index;
		अचिन्हित पूर्णांक mask = hose_irq_masks[h];

		cached_irq_masks[h] = mask;
		*(vuip)MCPCIA_INT_MASK0(MCPCIA_HOSE2MID(h)) = mask;
		*(vuip)MCPCIA_INT_MASK1(MCPCIA_HOSE2MID(h)) = 0;
	पूर्ण

	क्रम (i = 16; i < 128; ++i) अणु
		irq_set_chip_and_handler(i, &rawhide_irq_type,
					 handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	init_i8259a_irqs();
	common_init_isa_dma();
पूर्ण

/*
 * PCI Fixup configuration.
 *
 * Summary @ MCPCIA_PCI0_INT_REQ:
 * Bit      Meaning
 * 0        Interrupt Line A from slot 2 PCI0
 * 1        Interrupt Line B from slot 2 PCI0
 * 2        Interrupt Line C from slot 2 PCI0
 * 3        Interrupt Line D from slot 2 PCI0
 * 4        Interrupt Line A from slot 3 PCI0
 * 5        Interrupt Line B from slot 3 PCI0
 * 6        Interrupt Line C from slot 3 PCI0
 * 7        Interrupt Line D from slot 3 PCI0
 * 8        Interrupt Line A from slot 4 PCI0
 * 9        Interrupt Line B from slot 4 PCI0
 * 10       Interrupt Line C from slot 4 PCI0
 * 11       Interrupt Line D from slot 4 PCI0
 * 12       Interrupt Line A from slot 5 PCI0
 * 13       Interrupt Line B from slot 5 PCI0
 * 14       Interrupt Line C from slot 5 PCI0
 * 15       Interrupt Line D from slot 5 PCI0
 * 16       EISA पूर्णांकerrupt (PCI 0) or SCSI पूर्णांकerrupt (PCI 1)
 * 17-23    NA
 *
 * IdSel	
 *   1	 EISA bridge (PCI bus 0 only)
 *   2 	 PCI option slot 2
 *   3	 PCI option slot 3
 *   4   PCI option slot 4
 *   5   PCI option slot 5
 * 
 */

अटल पूर्णांक
rawhide_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[5][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु 16+16, 16+16, 16+16, 16+16, 16+16पूर्ण, /* IdSel 1 SCSI PCI 1 */
		अणु 16+ 0, 16+ 0, 16+ 1, 16+ 2, 16+ 3पूर्ण, /* IdSel 2 slot 2 */
		अणु 16+ 4, 16+ 4, 16+ 5, 16+ 6, 16+ 7पूर्ण, /* IdSel 3 slot 3 */
		अणु 16+ 8, 16+ 8, 16+ 9, 16+10, 16+11पूर्ण, /* IdSel 4 slot 4 */
		अणु 16+12, 16+12, 16+13, 16+14, 16+15पूर्ण  /* IdSel 5 slot 5 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 1, max_idsel = 5, irqs_per_slot = 5;

	काष्ठा pci_controller *hose = dev->sysdata;
	पूर्णांक irq = COMMON_TABLE_LOOKUP;
	अगर (irq >= 0)
		irq += 24 * hose->index;
	वापस irq;
पूर्ण


/*
 * The System Vector
 */

काष्ठा alpha_machine_vector rawhide_mv __iniपंचांगv = अणु
	.vector_name		= "Rawhide",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_MCPCIA_IO,
	.machine_check		= mcpcia_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= MCPCIA_DEFAULT_MEM_BASE,
	.pci_dac_offset		= MCPCIA_DAC_OFFSET,

	.nr_irqs		= 128,
	.device_पूर्णांकerrupt	= rawhide_srm_device_पूर्णांकerrupt,

	.init_arch		= mcpcia_init_arch,
	.init_irq		= rawhide_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= common_init_pci,
	.समाप्त_arch		= शून्य,
	.pci_map_irq		= rawhide_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(rawhide)
