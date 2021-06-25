<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_miata.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999, 2000 Riअक्षरd Henderson
 *
 * Code supporting the MIATA (EV56+PYXIS).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_cia.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


अटल व्योम 
miata_srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq;

	irq = (vector - 0x800) >> 4;

	/*
	 * I really hate to करो this, but the MIATA SRM console ignores the
	 *  low 8 bits in the पूर्णांकerrupt summary रेजिस्टर, and reports the
	 *  vector 0x80 *lower* than I expected from the bit numbering in
	 *  the करोcumentation.
	 * This was करोne because the low 8 summary bits really aren't used
	 *  क्रम reporting any पूर्णांकerrupts (the PCI-ISA bridge, bit 7, isn't
	 *  used क्रम this purpose, as PIC पूर्णांकerrupts are delivered as the
	 *  vectors 0x800-0x8f0).
	 * But I really करोn't want to change the fixup code क्रम allocation
	 *  of IRQs, nor the alpha_irq_mask मुख्यtenance stuff, both of which
	 *  look nice and clean now.
	 * So, here's this grotty hack... :-(
	 */
	अगर (irq >= 16)
		irq = irq + 8;

	handle_irq(irq);
पूर्ण

अटल व्योम __init
miata_init_irq(व्योम)
अणु
	अगर (alpha_using_srm)
		alpha_mv.device_पूर्णांकerrupt = miata_srm_device_पूर्णांकerrupt;

#अगर 0
	/* These अवरोध on MiataGL so we'll try not to करो it at all.  */
	*(vulp)PYXIS_INT_HILO = 0x000000B2UL; mb();	/* ISA/NMI HI */
	*(vulp)PYXIS_RT_COUNT = 0UL; mb();		/* clear count */
#पूर्ण_अगर

	init_i8259a_irqs();

	/* Not पूर्णांकerested in the bogus पूर्णांकerrupts (3,10), Fan Fault (0),
           NMI (1), or EIDE (9).

	   We also disable the risers (4,5), since we करोn't know how to
	   route the पूर्णांकerrupts behind the bridge.  */
	init_pyxis_irqs(0x63b0000);

	common_init_isa_dma();
	अगर (request_irq(16 + 2, no_action, 0, "halt-switch", शून्य))
		pr_err("Failed to register halt-switch interrupt\n");
	अगर (request_irq(16 + 6, no_action, 0, "timer-cascade", शून्य))
		pr_err("Failed to register timer-cascade interrupt\n");
पूर्ण


/*
 * PCI Fixup configuration.
 *
 * Summary @ PYXIS_INT_REQ:
 * Bit      Meaning
 * 0        Fan Fault
 * 1        NMI
 * 2        Halt/Reset चयन
 * 3        none
 * 4        CID0 (Riser ID)
 * 5        CID1 (Riser ID)
 * 6        Interval समयr
 * 7        PCI-ISA Bridge
 * 8        Ethernet
 * 9        EIDE (deprecated, ISA 14/15 used)
 *10        none
 *11        USB
 *12        Interrupt Line A from slot 4
 *13        Interrupt Line B from slot 4
 *14        Interrupt Line C from slot 4
 *15        Interrupt Line D from slot 4
 *16        Interrupt Line A from slot 5
 *17        Interrupt line B from slot 5
 *18        Interrupt Line C from slot 5
 *19        Interrupt Line D from slot 5
 *20        Interrupt Line A from slot 1
 *21        Interrupt Line B from slot 1
 *22        Interrupt Line C from slot 1
 *23        Interrupt Line D from slot 1
 *24        Interrupt Line A from slot 2
 *25        Interrupt Line B from slot 2
 *26        Interrupt Line C from slot 2
 *27        Interrupt Line D from slot 2
 *27        Interrupt Line A from slot 3
 *29        Interrupt Line B from slot 3
 *30        Interrupt Line C from slot 3
 *31        Interrupt Line D from slot 3
 *
 * The device to slot mapping looks like:
 *
 * Slot     Device
 *  3       DC21142 Ethernet
 *  4       EIDE CMD646
 *  5       none
 *  6       USB
 *  7       PCI-ISA bridge
 *  8       PCI-PCI Bridge      (SBU Riser)
 *  9       none
 * 10       none
 * 11       PCI on board slot 4 (SBU Riser)
 * 12       PCI on board slot 5 (SBU Riser)
 *
 *  These are behind the bridge, so I'm not sure what to करो...
 *
 * 13       PCI on board slot 1 (SBU Riser)
 * 14       PCI on board slot 2 (SBU Riser)
 * 15       PCI on board slot 3 (SBU Riser)
 *   
 *
 * This two layered पूर्णांकerrupt approach means that we allocate IRQ 16 and 
 * above क्रम PCI पूर्णांकerrupts.  The IRQ relates to which bit the पूर्णांकerrupt
 * comes in on.  This makes पूर्णांकerrupt processing much easier.
 */

अटल पूर्णांक
miata_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
        अटल अक्षर irq_tab[18][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु16+ 8, 16+ 8, 16+ 8, 16+ 8, 16+ 8पूर्ण,  /* IdSel 14,  DC21142 */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 15,  EIDE    */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 16,  none    */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 17,  none    */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 18,  PCI-ISA */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 19,  PCI-PCI */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 20,  none    */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 21,  none    */
		अणु16+12, 16+12, 16+13, 16+14, 16+15पूर्ण,  /* IdSel 22,  slot 4  */
		अणु16+16, 16+16, 16+17, 16+18, 16+19पूर्ण,  /* IdSel 23,  slot 5  */
		/* the next 7 are actually on PCI bus 1, across the bridge */
		अणु16+11, 16+11, 16+11, 16+11, 16+11पूर्ण,  /* IdSel 24,  QLISP/GL*/
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 25,  none    */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 26,  none    */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 27,  none    */
		अणु16+20, 16+20, 16+21, 16+22, 16+23पूर्ण,  /* IdSel 28,  slot 1  */
		अणु16+24, 16+24, 16+25, 16+26, 16+27पूर्ण,  /* IdSel 29,  slot 2  */
		अणु16+28, 16+28, 16+29, 16+30, 16+31पूर्ण,  /* IdSel 30,  slot 3  */
		/* This bridge is on the मुख्य bus of the later orig MIATA */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 31,  PCI-PCI */
        पूर्ण;
	स्थिर दीर्घ min_idsel = 3, max_idsel = 20, irqs_per_slot = 5;
	
	/* the USB function of the 82c693 has it's पूर्णांकerrupt connected to 
           the 2nd 8259 controller. So we have to check क्रम it first. */

	अगर((slot == 7) && (PCI_FUNC(dev->devfn) == 3)) अणु
		u8 irq=0;
		काष्ठा pci_dev *pdev = pci_get_slot(dev->bus, dev->devfn & ~7);
		अगर(pdev == शून्य || pci_पढ़ो_config_byte(pdev, 0x40,&irq) != PCIBIOS_SUCCESSFUL) अणु
			pci_dev_put(pdev);
			वापस -1;
		पूर्ण
		अन्यथा	अणु
			pci_dev_put(pdev);
			वापस irq;
		पूर्ण
	पूर्ण

	वापस COMMON_TABLE_LOOKUP;
पूर्ण

अटल u8
miata_swizzle(काष्ठा pci_dev *dev, u8 *pinp)
अणु
	पूर्णांक slot, pin = *pinp;

	अगर (dev->bus->number == 0) अणु
		slot = PCI_SLOT(dev->devfn);
	पूर्ण		
	/* Check क्रम the built-in bridge.  */
	अन्यथा अगर ((PCI_SLOT(dev->bus->self->devfn) == 8) ||
		 (PCI_SLOT(dev->bus->self->devfn) == 20)) अणु
		slot = PCI_SLOT(dev->devfn) + 9;
	पूर्ण
	अन्यथा 
	अणु
		/* Must be a card-based bridge.  */
		करो अणु
			अगर ((PCI_SLOT(dev->bus->self->devfn) == 8) ||
			    (PCI_SLOT(dev->bus->self->devfn) == 20)) अणु
				slot = PCI_SLOT(dev->devfn) + 9;
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

अटल व्योम __init
miata_init_pci(व्योम)
अणु
	cia_init_pci();
	SMC669_Init(0); /* it might be a GL (fails harmlessly अगर not) */
	es1888_init();
पूर्ण

अटल व्योम
miata_समाप्त_arch(पूर्णांक mode)
अणु
	cia_समाप्त_arch(mode);

#अगर_अघोषित ALPHA_RESTORE_SRM_SETUP
	चयन(mode) अणु
	हाल LINUX_REBOOT_CMD_RESTART:
		/* Who said DEC engineers have no sense of humor? ;-)  */ 
		अगर (alpha_using_srm) अणु
			*(vuip) PYXIS_RESET = 0x0000dead; 
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


/*
 * The System Vector
 */

काष्ठा alpha_machine_vector miata_mv __iniपंचांगv = अणु
	.vector_name		= "Miata",
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

	.init_arch		= pyxis_init_arch,
	.init_irq		= miata_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= miata_init_pci,
	.समाप्त_arch		= miata_समाप्त_arch,
	.pci_map_irq		= miata_map_irq,
	.pci_swizzle		= miata_swizzle,
पूर्ण;
ALIAS_MV(miata)
