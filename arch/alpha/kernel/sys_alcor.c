<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_alcor.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code supporting the ALCOR and XLT (XL-300/366/433).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/reboot.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/core_cia.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


/* Note mask bit is true क्रम ENABLED irqs.  */
अटल अचिन्हित दीर्घ cached_irq_mask;

अटल अंतरभूत व्योम
alcor_update_irq_hw(अचिन्हित दीर्घ mask)
अणु
	*(vuip)GRU_INT_MASK = mask;
	mb();
पूर्ण

अटल अंतरभूत व्योम
alcor_enable_irq(काष्ठा irq_data *d)
अणु
	alcor_update_irq_hw(cached_irq_mask |= 1UL << (d->irq - 16));
पूर्ण

अटल व्योम
alcor_disable_irq(काष्ठा irq_data *d)
अणु
	alcor_update_irq_hw(cached_irq_mask &= ~(1UL << (d->irq - 16)));
पूर्ण

अटल व्योम
alcor_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	alcor_disable_irq(d);

	/* On ALCOR/XLT, need to dismiss पूर्णांकerrupt via GRU. */
	*(vuip)GRU_INT_CLEAR = 1 << (d->irq - 16); mb();
	*(vuip)GRU_INT_CLEAR = 0; mb();
पूर्ण

अटल व्योम
alcor_isa_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	i8259a_mask_and_ack_irq(d);

	/* On ALCOR/XLT, need to dismiss पूर्णांकerrupt via GRU. */
	*(vuip)GRU_INT_CLEAR = 0x80000000; mb();
	*(vuip)GRU_INT_CLEAR = 0; mb();
पूर्ण

अटल काष्ठा irq_chip alcor_irq_type = अणु
	.name		= "ALCOR",
	.irq_unmask	= alcor_enable_irq,
	.irq_mask	= alcor_disable_irq,
	.irq_mask_ack	= alcor_mask_and_ack_irq,
पूर्ण;

अटल व्योम
alcor_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित दीर्घ pld;
	अचिन्हित पूर्णांक i;

	/* Read the पूर्णांकerrupt summary रेजिस्टर of the GRU */
	pld = (*(vuip)GRU_INT_REQ) & GRU_INT_REQ_BITS;

	/*
	 * Now क्रम every possible bit set, work through them and call
	 * the appropriate पूर्णांकerrupt handler.
	 */
	जबतक (pld) अणु
		i = ffz(~pld);
		pld &= pld - 1; /* clear least bit set */
		अगर (i == 31) अणु
			isa_device_पूर्णांकerrupt(vector);
		पूर्ण अन्यथा अणु
			handle_irq(16 + i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init
alcor_init_irq(व्योम)
अणु
	दीर्घ i;

	अगर (alpha_using_srm)
		alpha_mv.device_पूर्णांकerrupt = srm_device_पूर्णांकerrupt;

	*(vuip)GRU_INT_MASK  = 0; mb();			/* all disabled */
	*(vuip)GRU_INT_EDGE  = 0; mb();			/* all are level */
	*(vuip)GRU_INT_HILO  = 0x80000000U; mb();	/* ISA only HI */
	*(vuip)GRU_INT_CLEAR = 0; mb();			/* all clear */

	क्रम (i = 16; i < 48; ++i) अणु
		/* On Alcor, at least, lines 20..30 are not connected
		   and can generate spurious पूर्णांकerrupts अगर we turn them
		   on जबतक IRQ probing.  */
		अगर (i >= 16+20 && i <= 16+30)
			जारी;
		irq_set_chip_and_handler(i, &alcor_irq_type, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण
	i8259a_irq_type.irq_ack = alcor_isa_mask_and_ack_irq;

	init_i8259a_irqs();
	common_init_isa_dma();

	अगर (request_irq(16 + 31, no_action, 0, "isa-cascade", शून्य))
		pr_err("Failed to register isa-cascade interrupt\n");
पूर्ण


/*
 * PCI Fixup configuration.
 *
 * Summary @ GRU_INT_REQ:
 * Bit      Meaning
 * 0        Interrupt Line A from slot 2
 * 1        Interrupt Line B from slot 2
 * 2        Interrupt Line C from slot 2
 * 3        Interrupt Line D from slot 2
 * 4        Interrupt Line A from slot 1
 * 5        Interrupt line B from slot 1
 * 6        Interrupt Line C from slot 1
 * 7        Interrupt Line D from slot 1
 * 8        Interrupt Line A from slot 0
 * 9        Interrupt Line B from slot 0
 *10        Interrupt Line C from slot 0
 *11        Interrupt Line D from slot 0
 *12        Interrupt Line A from slot 4
 *13        Interrupt Line B from slot 4
 *14        Interrupt Line C from slot 4
 *15        Interrupt Line D from slot 4
 *16        Interrupt Line D from slot 3
 *17        Interrupt Line D from slot 3
 *18        Interrupt Line D from slot 3
 *19        Interrupt Line D from slot 3
 *20-30     Reserved
 *31        EISA पूर्णांकerrupt
 *
 * The device to slot mapping looks like:
 *
 * Slot     Device
 *  6       built-in TULIP (XLT only)
 *  7       PCI on board slot 0
 *  8       PCI on board slot 3
 *  9       PCI on board slot 4
 * 10       PCEB (PCI-EISA bridge)
 * 11       PCI on board slot 2
 * 12       PCI on board slot 1
 *   
 *
 * This two layered पूर्णांकerrupt approach means that we allocate IRQ 16 and 
 * above क्रम PCI पूर्णांकerrupts.  The IRQ relates to which bit the पूर्णांकerrupt
 * comes in on.  This makes पूर्णांकerrupt processing much easier.
 */

अटल पूर्णांक
alcor_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[7][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		/* note: IDSEL 17 is XLT only */
		अणु16+13, 16+13, 16+13, 16+13, 16+13पूर्ण,	/* IdSel 17,  TULIP  */
		अणु 16+8,  16+8,  16+9, 16+10, 16+11पूर्ण,	/* IdSel 18,  slot 0 */
		अणु16+16, 16+16, 16+17, 16+18, 16+19पूर्ण,	/* IdSel 19,  slot 3 */
		अणु16+12, 16+12, 16+13, 16+14, 16+15पूर्ण,	/* IdSel 20,  slot 4 */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,	/* IdSel 21,  PCEB   */
		अणु 16+0,  16+0,  16+1,  16+2,  16+3पूर्ण,	/* IdSel 22,  slot 2 */
		अणु 16+4,  16+4,  16+5,  16+6,  16+7पूर्ण,	/* IdSel 23,  slot 1 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 6, max_idsel = 12, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण

अटल व्योम
alcor_समाप्त_arch(पूर्णांक mode)
अणु
	cia_समाप्त_arch(mode);

#अगर_अघोषित ALPHA_RESTORE_SRM_SETUP
	चयन(mode) अणु
	हाल LINUX_REBOOT_CMD_RESTART:
		/* Who said DEC engineer's have no sense of humor? ;-)  */
		अगर (alpha_using_srm) अणु
			*(vuip) GRU_RESET = 0x0000dead;
			mb();
		पूर्ण
		अवरोध;
	हाल LINUX_REBOOT_CMD_HALT:
		अवरोध;
	हाल LINUX_REBOOT_CMD_POWER_OFF:
		अवरोध;
	पूर्ण

	halt();
#पूर्ण_अगर
पूर्ण

अटल व्योम __init
alcor_init_pci(व्योम)
अणु
	काष्ठा pci_dev *dev;

	cia_init_pci();

	/*
	 * Now we can look to see अगर we are really running on an XLT-type
	 * motherboard, by looking क्रम a 21040 TULIP in slot 6, which is
	 * built पूर्णांकo XLT and BRET/MAVERICK, but not available on ALCOR.
	 */
	dev = pci_get_device(PCI_VENDOR_ID_DEC,
			      PCI_DEVICE_ID_DEC_TULIP,
			      शून्य);
	अगर (dev && dev->devfn == PCI_DEVFN(6,0)) अणु
		alpha_mv.sys.cia.gru_पूर्णांक_req_bits = XLT_GRU_INT_REQ_BITS; 
		prपूर्णांकk(KERN_INFO "%s: Detected AS500 or XLT motherboard.\n",
		       __func__);
	पूर्ण
	pci_dev_put(dev);
पूर्ण


/*
 * The System Vectors
 */

काष्ठा alpha_machine_vector alcor_mv __iniपंचांगv = अणु
	.vector_name		= "Alcor",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_ALCOR_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= EISA_DEFAULT_IO_BASE,
	.min_mem_address	= CIA_DEFAULT_MEM_BASE,

	.nr_irqs		= 48,
	.device_पूर्णांकerrupt	= alcor_device_पूर्णांकerrupt,

	.init_arch		= cia_init_arch,
	.init_irq		= alcor_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= alcor_init_pci,
	.समाप्त_arch		= alcor_समाप्त_arch,
	.pci_map_irq		= alcor_map_irq,
	.pci_swizzle		= common_swizzle,

	.sys = अणु .cia = अणु
		.gru_पूर्णांक_req_bits = ALCOR_GRU_INT_REQ_BITS
	पूर्णपूर्ण
पूर्ण;
ALIAS_MV(alcor)

काष्ठा alpha_machine_vector xlt_mv __iniपंचांगv = अणु
	.vector_name		= "XLT",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= EISA_DEFAULT_IO_BASE,
	.min_mem_address	= CIA_DEFAULT_MEM_BASE,

	.nr_irqs		= 48,
	.device_पूर्णांकerrupt	= alcor_device_पूर्णांकerrupt,

	.init_arch		= cia_init_arch,
	.init_irq		= alcor_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= alcor_init_pci,
	.समाप्त_arch		= alcor_समाप्त_arch,
	.pci_map_irq		= alcor_map_irq,
	.pci_swizzle		= common_swizzle,

	.sys = अणु .cia = अणु
		.gru_पूर्णांक_req_bits = XLT_GRU_INT_REQ_BITS
	पूर्णपूर्ण
पूर्ण;

/* No alpha_mv alias क्रम XLT, since we compile it in unconditionally
   with ALCOR; setup_arch knows how to cope.  */
