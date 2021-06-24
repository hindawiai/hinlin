<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_dp264.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996, 1999 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 *	Modअगरied by Christopher C. Chimelis, 2001 to
 *	add support क्रम the addition of Shark to the
 *	Tsunami family.
 *
 * Code supporting the DP264 (EV6+TSUNAMI).
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
#समावेश <यंत्र/core_tsunami.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"


/* Note mask bit is true क्रम ENABLED irqs.  */
अटल अचिन्हित दीर्घ cached_irq_mask;
/* dp264 boards handle at max four CPUs */
अटल अचिन्हित दीर्घ cpu_irq_affinity[4] = अणु 0UL, 0UL, 0UL, 0UL पूर्ण;

DEFINE_SPINLOCK(dp264_irq_lock);

अटल व्योम
tsunami_update_irq_hw(अचिन्हित दीर्घ mask)
अणु
	रेजिस्टर tsunami_cchip *cchip = TSUNAMI_cchip;
	अचिन्हित दीर्घ isa_enable = 1UL << 55;
	रेजिस्टर पूर्णांक bcpu = boot_cpuid;

#अगर_घोषित CONFIG_SMP
	अस्थिर अचिन्हित दीर्घ *dim0, *dim1, *dim2, *dim3;
	अचिन्हित दीर्घ mask0, mask1, mask2, mask3, dummy;

	mask &= ~isa_enable;
	mask0 = mask & cpu_irq_affinity[0];
	mask1 = mask & cpu_irq_affinity[1];
	mask2 = mask & cpu_irq_affinity[2];
	mask3 = mask & cpu_irq_affinity[3];

	अगर (bcpu == 0) mask0 |= isa_enable;
	अन्यथा अगर (bcpu == 1) mask1 |= isa_enable;
	अन्यथा अगर (bcpu == 2) mask2 |= isa_enable;
	अन्यथा mask3 |= isa_enable;

	dim0 = &cchip->dim0.csr;
	dim1 = &cchip->dim1.csr;
	dim2 = &cchip->dim2.csr;
	dim3 = &cchip->dim3.csr;
	अगर (!cpu_possible(0)) dim0 = &dummy;
	अगर (!cpu_possible(1)) dim1 = &dummy;
	अगर (!cpu_possible(2)) dim2 = &dummy;
	अगर (!cpu_possible(3)) dim3 = &dummy;

	*dim0 = mask0;
	*dim1 = mask1;
	*dim2 = mask2;
	*dim3 = mask3;
	mb();
	*dim0;
	*dim1;
	*dim2;
	*dim3;
#अन्यथा
	अस्थिर अचिन्हित दीर्घ *dimB;
	अगर (bcpu == 0) dimB = &cchip->dim0.csr;
	अन्यथा अगर (bcpu == 1) dimB = &cchip->dim1.csr;
	अन्यथा अगर (bcpu == 2) dimB = &cchip->dim2.csr;
	अन्यथा dimB = &cchip->dim3.csr;

	*dimB = mask | isa_enable;
	mb();
	*dimB;
#पूर्ण_अगर
पूर्ण

अटल व्योम
dp264_enable_irq(काष्ठा irq_data *d)
अणु
	spin_lock(&dp264_irq_lock);
	cached_irq_mask |= 1UL << d->irq;
	tsunami_update_irq_hw(cached_irq_mask);
	spin_unlock(&dp264_irq_lock);
पूर्ण

अटल व्योम
dp264_disable_irq(काष्ठा irq_data *d)
अणु
	spin_lock(&dp264_irq_lock);
	cached_irq_mask &= ~(1UL << d->irq);
	tsunami_update_irq_hw(cached_irq_mask);
	spin_unlock(&dp264_irq_lock);
पूर्ण

अटल व्योम
clipper_enable_irq(काष्ठा irq_data *d)
अणु
	spin_lock(&dp264_irq_lock);
	cached_irq_mask |= 1UL << (d->irq - 16);
	tsunami_update_irq_hw(cached_irq_mask);
	spin_unlock(&dp264_irq_lock);
पूर्ण

अटल व्योम
clipper_disable_irq(काष्ठा irq_data *d)
अणु
	spin_lock(&dp264_irq_lock);
	cached_irq_mask &= ~(1UL << (d->irq - 16));
	tsunami_update_irq_hw(cached_irq_mask);
	spin_unlock(&dp264_irq_lock);
पूर्ण

अटल व्योम
cpu_set_irq_affinity(अचिन्हित पूर्णांक irq, cpumask_t affinity)
अणु
	पूर्णांक cpu;

	क्रम (cpu = 0; cpu < 4; cpu++) अणु
		अचिन्हित दीर्घ aff = cpu_irq_affinity[cpu];
		अगर (cpumask_test_cpu(cpu, &affinity))
			aff |= 1UL << irq;
		अन्यथा
			aff &= ~(1UL << irq);
		cpu_irq_affinity[cpu] = aff;
	पूर्ण
पूर्ण

अटल पूर्णांक
dp264_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *affinity,
		   bool क्रमce)
अणु
	spin_lock(&dp264_irq_lock);
	cpu_set_irq_affinity(d->irq, *affinity);
	tsunami_update_irq_hw(cached_irq_mask);
	spin_unlock(&dp264_irq_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
clipper_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *affinity,
		     bool क्रमce)
अणु
	spin_lock(&dp264_irq_lock);
	cpu_set_irq_affinity(d->irq - 16, *affinity);
	tsunami_update_irq_hw(cached_irq_mask);
	spin_unlock(&dp264_irq_lock);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip dp264_irq_type = अणु
	.name			= "DP264",
	.irq_unmask		= dp264_enable_irq,
	.irq_mask		= dp264_disable_irq,
	.irq_mask_ack		= dp264_disable_irq,
	.irq_set_affinity	= dp264_set_affinity,
पूर्ण;

अटल काष्ठा irq_chip clipper_irq_type = अणु
	.name			= "CLIPPER",
	.irq_unmask		= clipper_enable_irq,
	.irq_mask		= clipper_disable_irq,
	.irq_mask_ack		= clipper_disable_irq,
	.irq_set_affinity	= clipper_set_affinity,
पूर्ण;

अटल व्योम
dp264_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित दीर्घ pld;
	अचिन्हित पूर्णांक i;

	/* Read the पूर्णांकerrupt summary रेजिस्टर of TSUNAMI */
	pld = TSUNAMI_cchip->dir0.csr;

	/*
	 * Now क्रम every possible bit set, work through them and call
	 * the appropriate पूर्णांकerrupt handler.
	 */
	जबतक (pld) अणु
		i = ffz(~pld);
		pld &= pld - 1; /* clear least bit set */
		अगर (i == 55)
			isa_device_पूर्णांकerrupt(vector);
		अन्यथा
			handle_irq(16 + i);
	पूर्ण
पूर्ण

अटल व्योम 
dp264_srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq;

	irq = (vector - 0x800) >> 4;

	/*
	 * The SRM console reports PCI पूर्णांकerrupts with a vector calculated by:
	 *
	 *	0x900 + (0x10 * DRIR-bit)
	 *
	 * So bit 16 shows up as IRQ 32, etc.
	 * 
	 * On DP264/BRICK/MONET, we adjust it करोwn by 16 because at least
	 * that many of the low order bits of the DRIR are not used, and
	 * so we करोn't count them.
	 */
	अगर (irq >= 32)
		irq -= 16;

	handle_irq(irq);
पूर्ण

अटल व्योम 
clipper_srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq;

	irq = (vector - 0x800) >> 4;

/*
	 * The SRM console reports PCI पूर्णांकerrupts with a vector calculated by:
	 *
	 *	0x900 + (0x10 * DRIR-bit)
	 *
	 * So bit 16 shows up as IRQ 32, etc.
	 * 
	 * CLIPPER uses bits 8-47 क्रम PCI पूर्णांकerrupts, so we करो not need
	 * to scale करोwn the vector reported, we just use it.
	 *
	 * Eg IRQ 24 is DRIR bit 8, etc, etc
	 */
	handle_irq(irq);
पूर्ण

अटल व्योम __init
init_tsunami_irqs(काष्ठा irq_chip * ops, पूर्णांक imin, पूर्णांक imax)
अणु
	दीर्घ i;
	क्रम (i = imin; i <= imax; ++i) अणु
		irq_set_chip_and_handler(i, ops, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण
पूर्ण

अटल व्योम __init
dp264_init_irq(व्योम)
अणु
	outb(0, DMA1_RESET_REG);
	outb(0, DMA2_RESET_REG);
	outb(DMA_MODE_CASCADE, DMA2_MODE_REG);
	outb(0, DMA2_MASK_REG);

	अगर (alpha_using_srm)
		alpha_mv.device_पूर्णांकerrupt = dp264_srm_device_पूर्णांकerrupt;

	tsunami_update_irq_hw(0);

	init_i8259a_irqs();
	init_tsunami_irqs(&dp264_irq_type, 16, 47);
पूर्ण

अटल व्योम __init
clipper_init_irq(व्योम)
अणु
	outb(0, DMA1_RESET_REG);
	outb(0, DMA2_RESET_REG);
	outb(DMA_MODE_CASCADE, DMA2_MODE_REG);
	outb(0, DMA2_MASK_REG);

	अगर (alpha_using_srm)
		alpha_mv.device_पूर्णांकerrupt = clipper_srm_device_पूर्णांकerrupt;

	tsunami_update_irq_hw(0);

	init_i8259a_irqs();
	init_tsunami_irqs(&clipper_irq_type, 24, 63);
पूर्ण


/*
 * PCI Fixup configuration.
 *
 * Summary @ TSUNAMI_CSR_DIM0:
 * Bit      Meaning
 * 0-17     Unused
 *18        Interrupt SCSI B (Adaptec 7895 builtin)
 *19        Interrupt SCSI A (Adaptec 7895 builtin)
 *20        Interrupt Line D from slot 2 PCI0
 *21        Interrupt Line C from slot 2 PCI0
 *22        Interrupt Line B from slot 2 PCI0
 *23        Interrupt Line A from slot 2 PCI0
 *24        Interrupt Line D from slot 1 PCI0
 *25        Interrupt Line C from slot 1 PCI0
 *26        Interrupt Line B from slot 1 PCI0
 *27        Interrupt Line A from slot 1 PCI0
 *28        Interrupt Line D from slot 0 PCI0
 *29        Interrupt Line C from slot 0 PCI0
 *30        Interrupt Line B from slot 0 PCI0
 *31        Interrupt Line A from slot 0 PCI0
 *
 *32        Interrupt Line D from slot 3 PCI1
 *33        Interrupt Line C from slot 3 PCI1
 *34        Interrupt Line B from slot 3 PCI1
 *35        Interrupt Line A from slot 3 PCI1
 *36        Interrupt Line D from slot 2 PCI1
 *37        Interrupt Line C from slot 2 PCI1
 *38        Interrupt Line B from slot 2 PCI1
 *39        Interrupt Line A from slot 2 PCI1
 *40        Interrupt Line D from slot 1 PCI1
 *41        Interrupt Line C from slot 1 PCI1
 *42        Interrupt Line B from slot 1 PCI1
 *43        Interrupt Line A from slot 1 PCI1
 *44        Interrupt Line D from slot 0 PCI1
 *45        Interrupt Line C from slot 0 PCI1
 *46        Interrupt Line B from slot 0 PCI1
 *47        Interrupt Line A from slot 0 PCI1
 *48-52     Unused
 *53        PCI0 NMI (from Cypress)
 *54        PCI0 SMI INT (from Cypress)
 *55        PCI0 ISA Interrupt (from Cypress)
 *56-60     Unused
 *61        PCI1 Bus Error
 *62        PCI0 Bus Error
 *63        Reserved
 *
 * IdSel	
 *   5	 Cypress Bridge I/O
 *   6	 SCSI Adaptec builtin
 *   7	 64 bit PCI option slot 0 (all busses)
 *   8	 64 bit PCI option slot 1 (all busses)
 *   9	 64 bit PCI option slot 2 (all busses)
 *  10	 64 bit PCI option slot 3 (not bus 0)
 */

अटल पूर्णांक
isa_irq_fixup(स्थिर काष्ठा pci_dev *dev, पूर्णांक irq)
अणु
	u8 irq8;

	अगर (irq > 0)
		वापस irq;

	/* This पूर्णांकerrupt is routed via ISA bridge, so we'll
	   just have to trust whatever value the console might
	   have asचिन्हित.  */
	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &irq8);

	वापस irq8 & 0xf;
पूर्ण

अटल पूर्णांक
dp264_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[6][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 5 ISA Bridge */
		अणु 16+ 3, 16+ 3, 16+ 2, 16+ 2, 16+ 2पूर्ण, /* IdSel 6 SCSI builtin*/
		अणु 16+15, 16+15, 16+14, 16+13, 16+12पूर्ण, /* IdSel 7 slot 0 */
		अणु 16+11, 16+11, 16+10, 16+ 9, 16+ 8पूर्ण, /* IdSel 8 slot 1 */
		अणु 16+ 7, 16+ 7, 16+ 6, 16+ 5, 16+ 4पूर्ण, /* IdSel 9 slot 2 */
		अणु 16+ 3, 16+ 3, 16+ 2, 16+ 1, 16+ 0पूर्ण  /* IdSel 10 slot 3 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 5, max_idsel = 10, irqs_per_slot = 5;
	काष्ठा pci_controller *hose = dev->sysdata;
	पूर्णांक irq = COMMON_TABLE_LOOKUP;

	अगर (irq > 0)
		irq += 16 * hose->index;

	वापस isa_irq_fixup(dev, irq);
पूर्ण

अटल पूर्णांक
monet_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[13][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु    45,    45,    45,    45,    45पूर्ण, /* IdSel 3 21143 PCI1 */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 4 unused */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 5 unused */
		अणु    47,    47,    47,    47,    47पूर्ण, /* IdSel 6 SCSI PCI1 */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 7 ISA Bridge */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 8 P2P PCI1 */
#अगर 1
		अणु    28,    28,    29,    30,    31पूर्ण, /* IdSel 14 slot 4 PCI2*/
		अणु    24,    24,    25,    26,    27पूर्ण, /* IdSel 15 slot 5 PCI2*/
#अन्यथा
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 9 unused */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 10 unused */
#पूर्ण_अगर
		अणु    40,    40,    41,    42,    43पूर्ण, /* IdSel 11 slot 1 PCI0*/
		अणु    36,    36,    37,    38,    39पूर्ण, /* IdSel 12 slot 2 PCI0*/
		अणु    32,    32,    33,    34,    35पूर्ण, /* IdSel 13 slot 3 PCI0*/
		अणु    28,    28,    29,    30,    31पूर्ण, /* IdSel 14 slot 4 PCI2*/
		अणु    24,    24,    25,    26,    27पूर्ण  /* IdSel 15 slot 5 PCI2*/
	पूर्ण;
	स्थिर दीर्घ min_idsel = 3, max_idsel = 15, irqs_per_slot = 5;

	वापस isa_irq_fixup(dev, COMMON_TABLE_LOOKUP);
पूर्ण

अटल u8
monet_swizzle(काष्ठा pci_dev *dev, u8 *pinp)
अणु
	काष्ठा pci_controller *hose = dev->sysdata;
	पूर्णांक slot, pin = *pinp;

	अगर (!dev->bus->parent) अणु
		slot = PCI_SLOT(dev->devfn);
	पूर्ण
	/* Check क्रम the built-in bridge on hose 1. */
	अन्यथा अगर (hose->index == 1 && PCI_SLOT(dev->bus->self->devfn) == 8) अणु
		slot = PCI_SLOT(dev->devfn);
	पूर्ण अन्यथा अणु
		/* Must be a card-based bridge.  */
		करो अणु
			/* Check क्रम built-in bridge on hose 1. */
			अगर (hose->index == 1 &&
			    PCI_SLOT(dev->bus->self->devfn) == 8) अणु
				slot = PCI_SLOT(dev->devfn);
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

अटल पूर्णांक
webbrick_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[13][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 7 ISA Bridge */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 8 unused */
		अणु    29,    29,    29,    29,    29पूर्ण, /* IdSel 9 21143 #1 */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 10 unused */
		अणु    30,    30,    30,    30,    30पूर्ण, /* IdSel 11 21143 #2 */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 12 unused */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण, /* IdSel 13 unused */
		अणु    35,    35,    34,    33,    32पूर्ण, /* IdSel 14 slot 0 */
		अणु    39,    39,    38,    37,    36पूर्ण, /* IdSel 15 slot 1 */
		अणु    43,    43,    42,    41,    40पूर्ण, /* IdSel 16 slot 2 */
		अणु    47,    47,    46,    45,    44पूर्ण, /* IdSel 17 slot 3 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 7, max_idsel = 17, irqs_per_slot = 5;

	वापस isa_irq_fixup(dev, COMMON_TABLE_LOOKUP);
पूर्ण

अटल पूर्णांक
clipper_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[7][5] = अणु
		/*INT    INTA   INTB   INTC   INTD */
		अणु 16+ 8, 16+ 8, 16+ 9, 16+10, 16+11पूर्ण, /* IdSel 1 slot 1 */
		अणु 16+12, 16+12, 16+13, 16+14, 16+15पूर्ण, /* IdSel 2 slot 2 */
		अणु 16+16, 16+16, 16+17, 16+18, 16+19पूर्ण, /* IdSel 3 slot 3 */
		अणु 16+20, 16+20, 16+21, 16+22, 16+23पूर्ण, /* IdSel 4 slot 4 */
		अणु 16+24, 16+24, 16+25, 16+26, 16+27पूर्ण, /* IdSel 5 slot 5 */
		अणु 16+28, 16+28, 16+29, 16+30, 16+31पूर्ण, /* IdSel 6 slot 6 */
		अणु    -1,    -1,    -1,    -1,    -1पूर्ण  /* IdSel 7 ISA Bridge */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 1, max_idsel = 7, irqs_per_slot = 5;
	काष्ठा pci_controller *hose = dev->sysdata;
	पूर्णांक irq = COMMON_TABLE_LOOKUP;

	अगर (irq > 0)
		irq += 16 * hose->index;

	वापस isa_irq_fixup(dev, irq);
पूर्ण

अटल व्योम __init
dp264_init_pci(व्योम)
अणु
	common_init_pci();
	SMC669_Init(0);
	locate_and_init_vga(शून्य);
पूर्ण

अटल व्योम __init
monet_init_pci(व्योम)
अणु
	common_init_pci();
	SMC669_Init(1);
	es1888_init();
	locate_and_init_vga(शून्य);
पूर्ण

अटल व्योम __init
clipper_init_pci(व्योम)
अणु
	common_init_pci();
	locate_and_init_vga(शून्य);
पूर्ण

अटल व्योम __init
webbrick_init_arch(व्योम)
अणु
	tsunami_init_arch();

	/* Tsunami caches 4 PTEs at a समय; DS10 has only 1 hose. */
	hose_head->sg_isa->align_entry = 4;
	hose_head->sg_pci->align_entry = 4;
पूर्ण


/*
 * The System Vectors
 */

काष्ठा alpha_machine_vector dp264_mv __iniपंचांगv = अणु
	.vector_name		= "DP264",
	DO_EV6_MMU,
	DO_DEFAULT_RTC,
	DO_TSUNAMI_IO,
	.machine_check		= tsunami_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= TSUNAMI_DAC_OFFSET,

	.nr_irqs		= 64,
	.device_पूर्णांकerrupt	= dp264_device_पूर्णांकerrupt,

	.init_arch		= tsunami_init_arch,
	.init_irq		= dp264_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= dp264_init_pci,
	.समाप्त_arch		= tsunami_समाप्त_arch,
	.pci_map_irq		= dp264_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;
ALIAS_MV(dp264)

काष्ठा alpha_machine_vector monet_mv __iniपंचांगv = अणु
	.vector_name		= "Monet",
	DO_EV6_MMU,
	DO_DEFAULT_RTC,
	DO_TSUNAMI_IO,
	.machine_check		= tsunami_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= TSUNAMI_DAC_OFFSET,

	.nr_irqs		= 64,
	.device_पूर्णांकerrupt	= dp264_device_पूर्णांकerrupt,

	.init_arch		= tsunami_init_arch,
	.init_irq		= dp264_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= monet_init_pci,
	.समाप्त_arch		= tsunami_समाप्त_arch,
	.pci_map_irq		= monet_map_irq,
	.pci_swizzle		= monet_swizzle,
पूर्ण;

काष्ठा alpha_machine_vector webbrick_mv __iniपंचांगv = अणु
	.vector_name		= "Webbrick",
	DO_EV6_MMU,
	DO_DEFAULT_RTC,
	DO_TSUNAMI_IO,
	.machine_check		= tsunami_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= TSUNAMI_DAC_OFFSET,

	.nr_irqs		= 64,
	.device_पूर्णांकerrupt	= dp264_device_पूर्णांकerrupt,

	.init_arch		= webbrick_init_arch,
	.init_irq		= dp264_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= common_init_pci,
	.समाप्त_arch		= tsunami_समाप्त_arch,
	.pci_map_irq		= webbrick_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;

काष्ठा alpha_machine_vector clipper_mv __iniपंचांगv = अणु
	.vector_name		= "Clipper",
	DO_EV6_MMU,
	DO_DEFAULT_RTC,
	DO_TSUNAMI_IO,
	.machine_check		= tsunami_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= TSUNAMI_DAC_OFFSET,

	.nr_irqs		= 64,
	.device_पूर्णांकerrupt	= dp264_device_पूर्णांकerrupt,

	.init_arch		= tsunami_init_arch,
	.init_irq		= clipper_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= clipper_init_pci,
	.समाप्त_arch		= tsunami_समाप्त_arch,
	.pci_map_irq		= clipper_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;

/* Sharks strongly resemble Clipper, at least as far
 * as पूर्णांकerrupt routing, etc, so we're using the
 * same functions as Clipper करोes
 */

काष्ठा alpha_machine_vector shark_mv __iniपंचांगv = अणु
	.vector_name		= "Shark",
	DO_EV6_MMU,
	DO_DEFAULT_RTC,
	DO_TSUNAMI_IO,
	.machine_check		= tsunami_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= DEFAULT_MEM_BASE,
	.pci_dac_offset		= TSUNAMI_DAC_OFFSET,

	.nr_irqs		= 64,
	.device_पूर्णांकerrupt	= dp264_device_पूर्णांकerrupt,

	.init_arch		= tsunami_init_arch,
	.init_irq		= clipper_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= common_init_pci,
	.समाप्त_arch		= tsunami_समाप्त_arch,
	.pci_map_irq		= clipper_map_irq,
	.pci_swizzle		= common_swizzle,
पूर्ण;

/* No alpha_mv alias क्रम webbrick/monet/clipper, since we compile them
   in unconditionally with DP264; setup_arch knows how to cope.  */
