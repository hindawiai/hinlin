<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_sable.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code supporting the Sable, Sable-Gamma, and Lynx प्रणालीs.
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
#समावेश <यंत्र/core_t2.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"

DEFINE_SPINLOCK(sable_lynx_irq_lock);

प्रकार काष्ठा irq_swizzle_काष्ठा
अणु
	अक्षर irq_to_mask[64];
	अक्षर mask_to_irq[64];

	/* Note mask bit is true क्रम DISABLED irqs.  */
	अचिन्हित दीर्घ shaकरोw_mask;

	व्योम (*update_irq_hw)(अचिन्हित दीर्घ bit, अचिन्हित दीर्घ mask);
	व्योम (*ack_irq_hw)(अचिन्हित दीर्घ bit);

पूर्ण irq_swizzle_t;

अटल irq_swizzle_t *sable_lynx_irq_swizzle;

अटल व्योम sable_lynx_init_irq(पूर्णांक nr_of_irqs);

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SABLE)

/***********************************************************************/
/*
 *   For SABLE, which is really baroque, we manage 40 IRQ's, but the
 *   hardware really only supports 24, not via normal ISA PIC,
 *   but cascaded custom 8259's, etc.
 *	 0-7  (अक्षर at 536)
 *	 8-15 (अक्षर at 53a)
 *	16-23 (अक्षर at 53c)
 *
 * Summary Registers (536/53a/53c):
 *
 * Bit      Meaning               Kernel IRQ
 *------------------------------------------
 * 0        PCI slot 0			34
 * 1        NCR810 (builtin)		33
 * 2        TULIP (builtin)		32
 * 3        mouse			12
 * 4        PCI slot 1			35
 * 5        PCI slot 2			36
 * 6        keyboard			1
 * 7        floppy			6
 * 8        COM2			3
 * 9        parallel port		7
 *10        EISA irq 3			-
 *11        EISA irq 4			-
 *12        EISA irq 5			5
 *13        EISA irq 6			-
 *14        EISA irq 7			-
 *15        COM1			4
 *16        EISA irq 9			9
 *17        EISA irq 10			10
 *18        EISA irq 11			11
 *19        EISA irq 12			-
 *20        EISA irq 13			-
 *21        EISA irq 14			14
 *22        NC				15
 *23        IIC				-
 */

अटल व्योम
sable_update_irq_hw(अचिन्हित दीर्घ bit, अचिन्हित दीर्घ mask)
अणु
	पूर्णांक port = 0x537;

	अगर (bit >= 16) अणु
		port = 0x53d;
		mask >>= 16;
	पूर्ण अन्यथा अगर (bit >= 8) अणु
		port = 0x53b;
		mask >>= 8;
	पूर्ण

	outb(mask, port);
पूर्ण

अटल व्योम
sable_ack_irq_hw(अचिन्हित दीर्घ bit)
अणु
	पूर्णांक port, val1, val2;

	अगर (bit >= 16) अणु
		port = 0x53c;
		val1 = 0xE0 | (bit - 16);
		val2 = 0xE0 | 4;
	पूर्ण अन्यथा अगर (bit >= 8) अणु
		port = 0x53a;
		val1 = 0xE0 | (bit - 8);
		val2 = 0xE0 | 3;
	पूर्ण अन्यथा अणु
		port = 0x536;
		val1 = 0xE0 | (bit - 0);
		val2 = 0xE0 | 1;
	पूर्ण

	outb(val1, port);	/* ack the slave */
	outb(val2, 0x534);	/* ack the master */
पूर्ण

अटल irq_swizzle_t sable_irq_swizzle = अणु
	अणु
		-1,  6, -1,  8, 15, 12,  7,  9,	/* pseuकरो PIC  0-7  */
		-1, 16, 17, 18,  3, -1, 21, 22,	/* pseuकरो PIC  8-15 */
		-1, -1, -1, -1, -1, -1, -1, -1,	/* pseuकरो EISA 0-7  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/* pseuकरो EISA 8-15  */
		 2,  1,  0,  4,  5, -1, -1, -1,	/* pseuकरो PCI */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1 	/*  */
	पूर्ण,
	अणु
		34, 33, 32, 12, 35, 36,  1,  6,	/* mask 0-7  */
		 3,  7, -1, -1,  5, -1, -1,  4,	/* mask 8-15  */
		 9, 10, 11, -1, -1, 14, 15, -1,	/* mask 16-23  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1,	/*  */
		-1, -1, -1, -1, -1, -1, -1, -1	/*  */
	पूर्ण,
	-1,
	sable_update_irq_hw,
	sable_ack_irq_hw
पूर्ण;

अटल व्योम __init
sable_init_irq(व्योम)
अणु
	outb(-1, 0x537);	/* slave 0 */
	outb(-1, 0x53b);	/* slave 1 */
	outb(-1, 0x53d);	/* slave 2 */
	outb(0x44, 0x535);	/* enable cascades in master */

	sable_lynx_irq_swizzle = &sable_irq_swizzle;
	sable_lynx_init_irq(40);
पूर्ण

/*
 * PCI Fixup configuration क्रम ALPHA SABLE (2100).
 *
 * The device to slot mapping looks like:
 *
 * Slot     Device
 *  0       TULIP
 *  1       SCSI
 *  2       PCI-EISA bridge
 *  3       none
 *  4       none
 *  5       none
 *  6       PCI on board slot 0
 *  7       PCI on board slot 1
 *  8       PCI on board slot 2
 *   
 *
 * This two layered पूर्णांकerrupt approach means that we allocate IRQ 16 and 
 * above क्रम PCI पूर्णांकerrupts.  The IRQ relates to which bit the पूर्णांकerrupt
 * comes in on.  This makes पूर्णांकerrupt processing much easier.
 */
/*
 * NOTE: the IRQ assignments below are arbitrary, but need to be consistent
 * with the values in the irq swizzling tables above.
 */

अटल पूर्णांक
sable_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[9][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु 32+0,  32+0,  32+0,  32+0,  32+0पूर्ण,  /* IdSel 0,  TULIP  */
		अणु 32+1,  32+1,  32+1,  32+1,  32+1पूर्ण,  /* IdSel 1,  SCSI   */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 2,  SIO   */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 3,  none   */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 4,  none   */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 5,  none   */
		अणु 32+2,  32+2,  32+2,  32+2,  32+2पूर्ण,  /* IdSel 6,  slot 0 */
		अणु 32+3,  32+3,  32+3,  32+3,  32+3पूर्ण,  /* IdSel 7,  slot 1 */
		अणु 32+4,  32+4,  32+4,  32+4,  32+4पूर्ण   /* IdSel 8,  slot 2 */
	पूर्ण;
	दीर्घ min_idsel = 0, max_idsel = 8, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SABLE) */

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_LYNX)

/***********************************************************************/
/* LYNX hardware specअगरics
 */
/*
 *   For LYNX, which is also baroque, we manage 64 IRQs, via a custom IC.
 *
 * Bit      Meaning               Kernel IRQ
 *------------------------------------------
 * 0        
 * 1        
 * 2        
 * 3        mouse			12
 * 4        
 * 5        
 * 6        keyboard			1
 * 7        floppy			6
 * 8        COM2			3
 * 9        parallel port		7
 *10        EISA irq 3			-
 *11        EISA irq 4			-
 *12        EISA irq 5			5
 *13        EISA irq 6			-
 *14        EISA irq 7			-
 *15        COM1			4
 *16        EISA irq 9			9
 *17        EISA irq 10			10
 *18        EISA irq 11			11
 *19        EISA irq 12			-
 *20        
 *21        EISA irq 14			14
 *22        EISA irq 15			15
 *23        IIC				-
 *24        VGA (builtin)               -
 *25
 *26
 *27
 *28        NCR810 (builtin)		28
 *29
 *30
 *31
 *32        PCI 0 slot 4 A primary bus  32
 *33        PCI 0 slot 4 B primary bus  33
 *34        PCI 0 slot 4 C primary bus  34
 *35        PCI 0 slot 4 D primary bus
 *36        PCI 0 slot 5 A primary bus
 *37        PCI 0 slot 5 B primary bus
 *38        PCI 0 slot 5 C primary bus
 *39        PCI 0 slot 5 D primary bus
 *40        PCI 0 slot 6 A primary bus
 *41        PCI 0 slot 6 B primary bus
 *42        PCI 0 slot 6 C primary bus
 *43        PCI 0 slot 6 D primary bus
 *44        PCI 0 slot 7 A primary bus
 *45        PCI 0 slot 7 B primary bus
 *46        PCI 0 slot 7 C primary bus
 *47        PCI 0 slot 7 D primary bus
 *48        PCI 0 slot 0 A secondary bus
 *49        PCI 0 slot 0 B secondary bus
 *50        PCI 0 slot 0 C secondary bus
 *51        PCI 0 slot 0 D secondary bus
 *52        PCI 0 slot 1 A secondary bus
 *53        PCI 0 slot 1 B secondary bus
 *54        PCI 0 slot 1 C secondary bus
 *55        PCI 0 slot 1 D secondary bus
 *56        PCI 0 slot 2 A secondary bus
 *57        PCI 0 slot 2 B secondary bus
 *58        PCI 0 slot 2 C secondary bus
 *59        PCI 0 slot 2 D secondary bus
 *60        PCI 0 slot 3 A secondary bus
 *61        PCI 0 slot 3 B secondary bus
 *62        PCI 0 slot 3 C secondary bus
 *63        PCI 0 slot 3 D secondary bus
 */

अटल व्योम
lynx_update_irq_hw(अचिन्हित दीर्घ bit, अचिन्हित दीर्घ mask)
अणु
	/*
	 * Write the AIR रेजिस्टर on the T3/T4 with the
	 * address of the IC mask रेजिस्टर (offset 0x40)
	 */
	*(vulp)T2_AIR = 0x40;
	mb();
	*(vulp)T2_AIR; /* re-पढ़ो to क्रमce ग_लिखो */
	mb();
	*(vulp)T2_सूची = mask;    
	mb();
	mb();
पूर्ण

अटल व्योम
lynx_ack_irq_hw(अचिन्हित दीर्घ bit)
अणु
	*(vulp)T2_VAR = (u_दीर्घ) bit;
	mb();
	mb();
पूर्ण

अटल irq_swizzle_t lynx_irq_swizzle = अणु
	अणु /* irq_to_mask */
		-1,  6, -1,  8, 15, 12,  7,  9,	/* pseuकरो PIC  0-7  */
		-1, 16, 17, 18,  3, -1, 21, 22,	/* pseuकरो PIC  8-15 */
		-1, -1, -1, -1, -1, -1, -1, -1,	/* pseuकरो */
		-1, -1, -1, -1, 28, -1, -1, -1,	/* pseuकरो */
		32, 33, 34, 35, 36, 37, 38, 39,	/* mask 32-39 */
		40, 41, 42, 43, 44, 45, 46, 47,	/* mask 40-47 */
		48, 49, 50, 51, 52, 53, 54, 55,	/* mask 48-55 */
		56, 57, 58, 59, 60, 61, 62, 63	/* mask 56-63 */
	पूर्ण,
	अणु /* mask_to_irq */
		-1, -1, -1, 12, -1, -1,  1,  6,	/* mask 0-7   */
		 3,  7, -1, -1,  5, -1, -1,  4,	/* mask 8-15  */
		 9, 10, 11, -1, -1, 14, 15, -1,	/* mask 16-23 */
		-1, -1, -1, -1, 28, -1, -1, -1,	/* mask 24-31 */
		32, 33, 34, 35, 36, 37, 38, 39,	/* mask 32-39 */
		40, 41, 42, 43, 44, 45, 46, 47,	/* mask 40-47 */
		48, 49, 50, 51, 52, 53, 54, 55,	/* mask 48-55 */
		56, 57, 58, 59, 60, 61, 62, 63	/* mask 56-63 */
	पूर्ण,
	-1,
	lynx_update_irq_hw,
	lynx_ack_irq_hw
पूर्ण;

अटल व्योम __init
lynx_init_irq(व्योम)
अणु
	sable_lynx_irq_swizzle = &lynx_irq_swizzle;
	sable_lynx_init_irq(64);
पूर्ण

/*
 * PCI Fixup configuration क्रम ALPHA LYNX (2100A)
 *
 * The device to slot mapping looks like:
 *
 * Slot     Device
 *  0       none
 *  1       none
 *  2       PCI-EISA bridge
 *  3       PCI-PCI bridge
 *  4       NCR 810 (Demi-Lynx only)
 *  5       none
 *  6       PCI on board slot 4
 *  7       PCI on board slot 5
 *  8       PCI on board slot 6
 *  9       PCI on board slot 7
 *
 * And behind the PPB we have:
 *
 * 11       PCI on board slot 0
 * 12       PCI on board slot 1
 * 13       PCI on board slot 2
 * 14       PCI on board slot 3
 */
/*
 * NOTE: the IRQ assignments below are arbitrary, but need to be consistent
 * with the values in the irq swizzling tables above.
 */

अटल पूर्णांक
lynx_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[19][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 13,  PCEB   */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 14,  PPB    */
		अणु   28,    28,    28,    28,    28पूर्ण,  /* IdSel 15,  NCR demi */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 16,  none   */
		अणु   32,    32,    33,    34,    35पूर्ण,  /* IdSel 17,  slot 4 */
		अणु   36,    36,    37,    38,    39पूर्ण,  /* IdSel 18,  slot 5 */
		अणु   40,    40,    41,    42,    43पूर्ण,  /* IdSel 19,  slot 6 */
		अणु   44,    44,    45,    46,    47पूर्ण,  /* IdSel 20,  slot 7 */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 22,  none   */
		/* The following are actually behind the PPB. */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 16   none */
		अणु   28,    28,    28,    28,    28पूर्ण,  /* IdSel 17   NCR lynx */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 18   none */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 19   none */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 20   none */
		अणु   -1,    -1,    -1,    -1,    -1पूर्ण,  /* IdSel 21   none */
		अणु   48,    48,    49,    50,    51पूर्ण,  /* IdSel 22   slot 0 */
		अणु   52,    52,    53,    54,    55पूर्ण,  /* IdSel 23   slot 1 */
		अणु   56,    56,    57,    58,    59पूर्ण,  /* IdSel 24   slot 2 */
		अणु   60,    60,    61,    62,    63पूर्ण   /* IdSel 25   slot 3 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 2, max_idsel = 20, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण

अटल u8
lynx_swizzle(काष्ठा pci_dev *dev, u8 *pinp)
अणु
	पूर्णांक slot, pin = *pinp;

	अगर (dev->bus->number == 0) अणु
		slot = PCI_SLOT(dev->devfn);
	पूर्ण
	/* Check क्रम the built-in bridge */
	अन्यथा अगर (PCI_SLOT(dev->bus->self->devfn) == 3) अणु
		slot = PCI_SLOT(dev->devfn) + 11;
	पूर्ण
	अन्यथा
	अणु
		/* Must be a card-based bridge.  */
		करो अणु
			अगर (PCI_SLOT(dev->bus->self->devfn) == 3) अणु
				slot = PCI_SLOT(dev->devfn) + 11;
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

#पूर्ण_अगर /* defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_LYNX) */

/***********************************************************************/
/* GENERIC irq routines */

अटल अंतरभूत व्योम
sable_lynx_enable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ bit, mask;

	bit = sable_lynx_irq_swizzle->irq_to_mask[d->irq];
	spin_lock(&sable_lynx_irq_lock);
	mask = sable_lynx_irq_swizzle->shaकरोw_mask &= ~(1UL << bit);
	sable_lynx_irq_swizzle->update_irq_hw(bit, mask);
	spin_unlock(&sable_lynx_irq_lock);
#अगर 0
	prपूर्णांकk("%s: mask 0x%lx bit 0x%lx irq 0x%x\n",
	       __func__, mask, bit, irq);
#पूर्ण_अगर
पूर्ण

अटल व्योम
sable_lynx_disable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ bit, mask;

	bit = sable_lynx_irq_swizzle->irq_to_mask[d->irq];
	spin_lock(&sable_lynx_irq_lock);
	mask = sable_lynx_irq_swizzle->shaकरोw_mask |= 1UL << bit;
	sable_lynx_irq_swizzle->update_irq_hw(bit, mask);
	spin_unlock(&sable_lynx_irq_lock);
#अगर 0
	prपूर्णांकk("%s: mask 0x%lx bit 0x%lx irq 0x%x\n",
	       __func__, mask, bit, irq);
#पूर्ण_अगर
पूर्ण

अटल व्योम
sable_lynx_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ bit, mask;

	bit = sable_lynx_irq_swizzle->irq_to_mask[d->irq];
	spin_lock(&sable_lynx_irq_lock);
	mask = sable_lynx_irq_swizzle->shaकरोw_mask |= 1UL << bit;
	sable_lynx_irq_swizzle->update_irq_hw(bit, mask);
	sable_lynx_irq_swizzle->ack_irq_hw(bit);
	spin_unlock(&sable_lynx_irq_lock);
पूर्ण

अटल काष्ठा irq_chip sable_lynx_irq_type = अणु
	.name		= "SABLE/LYNX",
	.irq_unmask	= sable_lynx_enable_irq,
	.irq_mask	= sable_lynx_disable_irq,
	.irq_mask_ack	= sable_lynx_mask_and_ack_irq,
पूर्ण;

अटल व्योम 
sable_lynx_srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	/* Note that the vector reported by the SRM PALcode corresponds
	   to the पूर्णांकerrupt mask bits, but we have to manage via the
	   so-called legacy IRQs क्रम many common devices.  */

	पूर्णांक bit, irq;

	bit = (vector - 0x800) >> 4;
	irq = sable_lynx_irq_swizzle->mask_to_irq[bit];
#अगर 0
	prपूर्णांकk("%s: vector 0x%lx bit 0x%x irq 0x%x\n",
	       __func__, vector, bit, irq);
#पूर्ण_अगर
	handle_irq(irq);
पूर्ण

अटल व्योम __init
sable_lynx_init_irq(पूर्णांक nr_of_irqs)
अणु
	दीर्घ i;

	क्रम (i = 0; i < nr_of_irqs; ++i) अणु
		irq_set_chip_and_handler(i, &sable_lynx_irq_type,
					 handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	common_init_isa_dma();
पूर्ण

अटल व्योम __init
sable_lynx_init_pci(व्योम)
अणु
	common_init_pci();
पूर्ण

/*****************************************************************/
/*
 * The System Vectors
 *
 * In order that T2_HAE_ADDRESS should be a स्थिरant, we play
 * these games with GAMMA_BIAS.
 */

#अगर defined(CONFIG_ALPHA_GENERIC) || \
    (defined(CONFIG_ALPHA_SABLE) && !defined(CONFIG_ALPHA_GAMMA))
#अघोषित GAMMA_BIAS
#घोषणा GAMMA_BIAS 0
काष्ठा alpha_machine_vector sable_mv __iniपंचांगv = अणु
	.vector_name		= "Sable",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_T2_IO,
	.machine_check		= t2_machine_check,
	.max_isa_dma_address	= ALPHA_SABLE_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= EISA_DEFAULT_IO_BASE,
	.min_mem_address	= T2_DEFAULT_MEM_BASE,

	.nr_irqs		= 40,
	.device_पूर्णांकerrupt	= sable_lynx_srm_device_पूर्णांकerrupt,

	.init_arch		= t2_init_arch,
	.init_irq		= sable_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= sable_lynx_init_pci,
	.समाप्त_arch		= t2_समाप्त_arch,
	.pci_map_irq		= sable_map_irq,
	.pci_swizzle		= common_swizzle,

	.sys = अणु .t2 = अणु
	    .gamma_bias		= 0
	पूर्ण पूर्ण
पूर्ण;
ALIAS_MV(sable)
#पूर्ण_अगर /* GENERIC || (SABLE && !GAMMA) */

#अगर defined(CONFIG_ALPHA_GENERIC) || \
    (defined(CONFIG_ALPHA_SABLE) && defined(CONFIG_ALPHA_GAMMA))
#अघोषित GAMMA_BIAS
#घोषणा GAMMA_BIAS _GAMMA_BIAS
काष्ठा alpha_machine_vector sable_gamma_mv __iniपंचांगv = अणु
	.vector_name		= "Sable-Gamma",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_T2_IO,
	.machine_check		= t2_machine_check,
	.max_isa_dma_address	= ALPHA_SABLE_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= EISA_DEFAULT_IO_BASE,
	.min_mem_address	= T2_DEFAULT_MEM_BASE,

	.nr_irqs		= 40,
	.device_पूर्णांकerrupt	= sable_lynx_srm_device_पूर्णांकerrupt,

	.init_arch		= t2_init_arch,
	.init_irq		= sable_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= sable_lynx_init_pci,
	.समाप्त_arch		= t2_समाप्त_arch,
	.pci_map_irq		= sable_map_irq,
	.pci_swizzle		= common_swizzle,

	.sys = अणु .t2 = अणु
	    .gamma_bias		= _GAMMA_BIAS
	पूर्ण पूर्ण
पूर्ण;
ALIAS_MV(sable_gamma)
#पूर्ण_अगर /* GENERIC || (SABLE && GAMMA) */

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_LYNX)
#अघोषित GAMMA_BIAS
#घोषणा GAMMA_BIAS _GAMMA_BIAS
काष्ठा alpha_machine_vector lynx_mv __iniपंचांगv = अणु
	.vector_name		= "Lynx",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_T2_IO,
	.machine_check		= t2_machine_check,
	.max_isa_dma_address	= ALPHA_SABLE_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= EISA_DEFAULT_IO_BASE,
	.min_mem_address	= T2_DEFAULT_MEM_BASE,

	.nr_irqs		= 64,
	.device_पूर्णांकerrupt	= sable_lynx_srm_device_पूर्णांकerrupt,

	.init_arch		= t2_init_arch,
	.init_irq		= lynx_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= sable_lynx_init_pci,
	.समाप्त_arch		= t2_समाप्त_arch,
	.pci_map_irq		= lynx_map_irq,
	.pci_swizzle		= lynx_swizzle,

	.sys = अणु .t2 = अणु
	    .gamma_bias		= _GAMMA_BIAS
	पूर्ण पूर्ण
पूर्ण;
ALIAS_MV(lynx)
#पूर्ण_अगर /* GENERIC || LYNX */
