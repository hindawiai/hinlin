<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_ruffian.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999, 2000 Riअक्षरd Henderson
 *
 * Code supporting the RUFFIAN.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समयx.h>
#समावेश <linux/init.h>

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


अटल व्योम __init
ruffian_init_irq(व्योम)
अणु
	/* Invert 6&7 क्रम i82371 */
	*(vulp)PYXIS_INT_HILO  = 0x000000c0UL; mb();
	*(vulp)PYXIS_INT_CNFG  = 0x00002064UL; mb();	 /* all clear */

	outb(0x11,0xA0);
	outb(0x08,0xA1);
	outb(0x02,0xA1);
	outb(0x01,0xA1);
	outb(0xFF,0xA1);
	
	outb(0x11,0x20);
	outb(0x00,0x21);
	outb(0x04,0x21);
	outb(0x01,0x21);
	outb(0xFF,0x21);
	
	/* Finish writing the 82C59A PIC Operation Control Words */
	outb(0x20,0xA0);
	outb(0x20,0x20);
	
	init_i8259a_irqs();

	/* Not पूर्णांकerested in the bogus पूर्णांकerrupts (0,3,6),
	   NMI (1), HALT (2), flash (5), or 21142 (8).  */
	init_pyxis_irqs(0x16f0000);

	common_init_isa_dma();
पूर्ण

#घोषणा RUFFIAN_LATCH	DIV_ROUND_CLOSEST(PIT_TICK_RATE, HZ)

अटल व्योम __init
ruffian_init_rtc(व्योम)
अणु
	/* Ruffian करोes not have the RTC connected to the CPU समयr
	   पूर्णांकerrupt.  Instead, it uses the PIT connected to IRQ 0.  */

	/* Setup पूर्णांकerval समयr.  */
	outb(0x34, 0x43);		/* binary, mode 2, LSB/MSB, ch 0 */
	outb(RUFFIAN_LATCH & 0xff, 0x40);	/* LSB */
	outb(RUFFIAN_LATCH >> 8, 0x40);		/* MSB */

	outb(0xb6, 0x43);		/* pit counter 2: speaker */
	outb(0x31, 0x42);
	outb(0x13, 0x42);

	अगर (request_irq(0, rtc_समयr_पूर्णांकerrupt, 0, "timer", शून्य))
		pr_err("Failed to request irq 0 (timer)\n");
पूर्ण

अटल व्योम
ruffian_समाप्त_arch (पूर्णांक mode)
अणु
	cia_समाप्त_arch(mode);
#अगर 0
	/* This only causes re-entry to ARCSBIOS */
	/* Perhaps this works क्रम other PYXIS as well?  */
	*(vuip) PYXIS_RESET = 0x0000dead;
	mb();
#पूर्ण_अगर
पूर्ण

/*
 *  Interrupt routing:
 *
 *		Primary bus
 *	  IdSel		INTA	INTB	INTC	INTD
 * 21052   13		  -	  -	  -	  -
 * SIO	   14		 23	  -	  -	  -
 * 21143   15		 44	  -	  -	  -
 * Slot 0  17		 43	 42	 41	 40
 *
 *		Secondary bus
 *	  IdSel		INTA	INTB	INTC	INTD
 * Slot 0   8 (18)	 19	 18	 17	 16
 * Slot 1   9 (19)	 31	 30	 29	 28
 * Slot 2  10 (20)	 27	 26	 25	 24
 * Slot 3  11 (21)	 39	 38	 37	 36
 * Slot 4  12 (22)	 35	 34	 33	 32
 * 53c875  13 (23)	 20	  -	  -	  -
 *
 */

अटल पूर्णांक
ruffian_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
        अटल अक्षर irq_tab[11][5] = अणु
	      /*INT  INTA INTB INTC INTD */
		अणु-1,  -1,  -1,  -1,  -1पूर्ण,  /* IdSel 13,  21052	     */
		अणु-1,  -1,  -1,  -1,  -1पूर्ण,  /* IdSel 14,  SIO	     */
		अणु44,  44,  44,  44,  44पूर्ण,  /* IdSel 15,  21143	     */
		अणु-1,  -1,  -1,  -1,  -1पूर्ण,  /* IdSel 16,  none	     */
		अणु43,  43,  42,  41,  40पूर्ण,  /* IdSel 17,  64-bit slot */
		/* the next 6 are actually on PCI bus 1, across the bridge */
		अणु19,  19,  18,  17,  16पूर्ण,  /* IdSel  8,  slot 0	     */
		अणु31,  31,  30,  29,  28पूर्ण,  /* IdSel  9,  slot 1	     */
		अणु27,  27,  26,  25,  24पूर्ण,  /* IdSel 10,  slot 2	     */
		अणु39,  39,  38,  37,  36पूर्ण,  /* IdSel 11,  slot 3	     */
		अणु35,  35,  34,  33,  32पूर्ण,  /* IdSel 12,  slot 4	     */
		अणु20,  20,  20,  20,  20पूर्ण,  /* IdSel 13,  53c875	     */
        पूर्ण;
	स्थिर दीर्घ min_idsel = 13, max_idsel = 23, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण

अटल u8
ruffian_swizzle(काष्ठा pci_dev *dev, u8 *pinp)
अणु
	पूर्णांक slot, pin = *pinp;

	अगर (dev->bus->number == 0) अणु
		slot = PCI_SLOT(dev->devfn);
	पूर्ण		
	/* Check क्रम the built-in bridge.  */
	अन्यथा अगर (PCI_SLOT(dev->bus->self->devfn) == 13) अणु
		slot = PCI_SLOT(dev->devfn) + 10;
	पूर्ण
	अन्यथा 
	अणु
		/* Must be a card-based bridge.  */
		करो अणु
			अगर (PCI_SLOT(dev->bus->self->devfn) == 13) अणु
				slot = PCI_SLOT(dev->devfn) + 10;
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

#अगर_घोषित BUILDING_FOR_MILO
/*
 * The DeskStation Ruffian motherboard firmware करोes not place
 * the memory size in the PALimpure area.  Thereक्रमe, we use
 * the Bank Configuration Registers in PYXIS to obtain the size.
 */
अटल अचिन्हित दीर्घ __init
ruffian_get_bank_size(अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ bank_addr, bank, ret = 0;

	/* Valid offsets are: 0x800, 0x840 and 0x880
	   since Ruffian only uses three banks.  */
	bank_addr = (अचिन्हित दीर्घ)PYXIS_MCR + offset;
	bank = *(vulp)bank_addr;

	/* Check BANK_ENABLE */
	अगर (bank & 0x01) अणु
		अटल अचिन्हित दीर्घ size[] __initdata = अणु
			0x40000000UL, /* 0x00,   1G */
			0x20000000UL, /* 0x02, 512M */
			0x10000000UL, /* 0x04, 256M */
			0x08000000UL, /* 0x06, 128M */
			0x04000000UL, /* 0x08,  64M */
			0x02000000UL, /* 0x0a,  32M */
			0x01000000UL, /* 0x0c,  16M */
			0x00800000UL, /* 0x0e,   8M */
			0x80000000UL, /* 0x10,   2G */
		पूर्ण;

		bank = (bank & 0x1e) >> 1;
		अगर (bank < ARRAY_SIZE(size))
			ret = size[bank];
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* BUILDING_FOR_MILO */

/*
 * The System Vector
 */

काष्ठा alpha_machine_vector ruffian_mv __iniपंचांगv = अणु
	.vector_name		= "Ruffian",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_PYXIS_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_RUFFIAN_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= PYXIS_DAC_OFFSET,

	.nr_irqs		= 48,
	.device_पूर्णांकerrupt	= pyxis_device_पूर्णांकerrupt,

	.init_arch		= pyxis_init_arch,
	.init_irq		= ruffian_init_irq,
	.init_rtc		= ruffian_init_rtc,
	.init_pci		= cia_init_pci,
	.समाप्त_arch		= ruffian_समाप्त_arch,
	.pci_map_irq		= ruffian_map_irq,
	.pci_swizzle		= ruffian_swizzle,
पूर्ण;
ALIAS_MV(ruffian)
