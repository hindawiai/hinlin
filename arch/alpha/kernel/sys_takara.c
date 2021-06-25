<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_takara.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code supporting the TAKARA.
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
#समावेश <यंत्र/core_cia.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"
#समावेश "pc873xx.h"

/* Note mask bit is true क्रम DISABLED irqs.  */
अटल अचिन्हित दीर्घ cached_irq_mask[2] = अणु -1, -1 पूर्ण;

अटल अंतरभूत व्योम
takara_update_irq_hw(अचिन्हित दीर्घ irq, अचिन्हित दीर्घ mask)
अणु
	पूर्णांक regaddr;

	mask = (irq >= 64 ? mask << 16 : mask >> ((irq - 16) & 0x30));
	regaddr = 0x510 + (((irq - 16) >> 2) & 0x0c);
	outl(mask & 0xffff0000UL, regaddr);
पूर्ण

अटल अंतरभूत व्योम
takara_enable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
	अचिन्हित दीर्घ mask;
	mask = (cached_irq_mask[irq >= 64] &= ~(1UL << (irq & 63)));
	takara_update_irq_hw(irq, mask);
पूर्ण

अटल व्योम
takara_disable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक irq = d->irq;
	अचिन्हित दीर्घ mask;
	mask = (cached_irq_mask[irq >= 64] |= 1UL << (irq & 63));
	takara_update_irq_hw(irq, mask);
पूर्ण

अटल काष्ठा irq_chip takara_irq_type = अणु
	.name		= "TAKARA",
	.irq_unmask	= takara_enable_irq,
	.irq_mask	= takara_disable_irq,
	.irq_mask_ack	= takara_disable_irq,
पूर्ण;

अटल व्योम
takara_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	अचिन्हित पूर्णांकstatus;

	/*
	 * The PALcode will have passed us vectors 0x800 or 0x810,
	 * which are fairly arbitrary values and serve only to tell
	 * us whether an पूर्णांकerrupt has come in on IRQ0 or IRQ1. If
	 * it's IRQ1 it's a PCI interrupt; if it's IRQ0, it's
	 * probably ISA, but PCI पूर्णांकerrupts can come through IRQ0
	 * as well अगर the पूर्णांकerrupt controller isn't in accelerated
	 * mode.
	 *
	 * OTOH, the accelerator thing करोesn't seem to be working
	 * overly well, so what we'll करो instead is try directly
	 * examining the Master Interrupt Register to see अगर it's a
	 * PCI पूर्णांकerrupt, and अगर _not_ then we'll pass it on to the
	 * ISA handler.
	 */

	पूर्णांकstatus = inw(0x500) & 15;
	अगर (पूर्णांकstatus) अणु
		/*
		 * This is a PCI पूर्णांकerrupt. Check each bit and
		 * despatch an पूर्णांकerrupt अगर it's set.
		 */

		अगर (पूर्णांकstatus & 8) handle_irq(16+3);
		अगर (पूर्णांकstatus & 4) handle_irq(16+2);
		अगर (पूर्णांकstatus & 2) handle_irq(16+1);
		अगर (पूर्णांकstatus & 1) handle_irq(16+0);
	पूर्ण अन्यथा अणु
		isa_device_पूर्णांकerrupt (vector);
	पूर्ण
पूर्ण

अटल व्योम 
takara_srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ vector)
अणु
	पूर्णांक irq = (vector - 0x800) >> 4;
	handle_irq(irq);
पूर्ण

अटल व्योम __init
takara_init_irq(व्योम)
अणु
	दीर्घ i;

	init_i8259a_irqs();

	अगर (alpha_using_srm) अणु
		alpha_mv.device_पूर्णांकerrupt = takara_srm_device_पूर्णांकerrupt;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक ctlreg = inl(0x500);

		/* Return to non-accelerated mode.  */
		ctlreg &= ~0x8000;
		outl(ctlreg, 0x500);

		/* Enable the PCI पूर्णांकerrupt रेजिस्टर.  */
		ctlreg = 0x05107c00;
		outl(ctlreg, 0x500);
	पूर्ण

	क्रम (i = 16; i < 128; i += 16)
		takara_update_irq_hw(i, -1);

	क्रम (i = 16; i < 128; ++i) अणु
		irq_set_chip_and_handler(i, &takara_irq_type,
					 handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	पूर्ण

	common_init_isa_dma();
पूर्ण


/*
 * The Takara has PCI devices 1, 2, and 3 configured to slots 20,
 * 19, and 18 respectively, in the शेष configuration. They can
 * also be jumpered to slots 8, 7, and 6 respectively, which is fun
 * because the SIO ISA bridge can also be slot 7. However, the SIO
 * करोesn't explicitly generate PCI-type पूर्णांकerrupts, so we can
 * assign it whatever the hell IRQ we like and it करोesn't matter.
 */

अटल पूर्णांक
takara_map_irq_srm(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[15][5] = अणु
		अणु 16+3, 16+3, 16+3, 16+3, 16+3पूर्ण,   /* slot  6 == device 3 */
		अणु 16+2, 16+2, 16+2, 16+2, 16+2पूर्ण,   /* slot  7 == device 2 */
		अणु 16+1, 16+1, 16+1, 16+1, 16+1पूर्ण,   /* slot  8 == device 1 */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot  9 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 10 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 11 == nothing */
		/* These are behind the bridges.  */
		अणु   12,   12,   13,   14,   15पूर्ण,   /* slot 12 == nothing */
		अणु    8,    8,    9,   19,   11पूर्ण,   /* slot 13 == nothing */
		अणु    4,    4,    5,    6,    7पूर्ण,   /* slot 14 == nothing */
		अणु    0,    0,    1,    2,    3पूर्ण,   /* slot 15 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 16 == nothing */
		अणु64+ 0, 64+0, 64+1, 64+2, 64+3पूर्ण,   /* slot 17= device 4 */
		अणु48+ 0, 48+0, 48+1, 48+2, 48+3पूर्ण,   /* slot 18= device 3 */
		अणु32+ 0, 32+0, 32+1, 32+2, 32+3पूर्ण,   /* slot 19= device 2 */
		अणु16+ 0, 16+0, 16+1, 16+2, 16+3पूर्ण,   /* slot 20= device 1 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 6, max_idsel = 20, irqs_per_slot = 5;
        पूर्णांक irq = COMMON_TABLE_LOOKUP;
	अगर (irq >= 0 && irq < 16) अणु
		/* Guess that we are behind a bridge.  */
		अचिन्हित पूर्णांक busslot = PCI_SLOT(dev->bus->self->devfn);
		irq += irq_tab[busslot-min_idsel][0];
	पूर्ण
	वापस irq;
पूर्ण

अटल पूर्णांक __init
takara_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[15][5] __initdata = अणु
		अणु 16+3, 16+3, 16+3, 16+3, 16+3पूर्ण,   /* slot  6 == device 3 */
		अणु 16+2, 16+2, 16+2, 16+2, 16+2पूर्ण,   /* slot  7 == device 2 */
		अणु 16+1, 16+1, 16+1, 16+1, 16+1पूर्ण,   /* slot  8 == device 1 */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot  9 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 10 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 11 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 12 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 13 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 14 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 15 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 16 == nothing */
		अणु   -1,   -1,   -1,   -1,   -1पूर्ण,   /* slot 17 == nothing */
		अणु 16+3, 16+3, 16+3, 16+3, 16+3पूर्ण,   /* slot 18 == device 3 */
		अणु 16+2, 16+2, 16+2, 16+2, 16+2पूर्ण,   /* slot 19 == device 2 */
		अणु 16+1, 16+1, 16+1, 16+1, 16+1पूर्ण,   /* slot 20 == device 1 */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 6, max_idsel = 20, irqs_per_slot = 5;
	वापस COMMON_TABLE_LOOKUP;
पूर्ण

अटल u8
takara_swizzle(काष्ठा pci_dev *dev, u8 *pinp)
अणु
	पूर्णांक slot = PCI_SLOT(dev->devfn);
	पूर्णांक pin = *pinp;
	अचिन्हित पूर्णांक ctlreg = inl(0x500);
	अचिन्हित पूर्णांक busslot;

	अगर (!dev->bus->self)
		वापस slot;

	busslot = PCI_SLOT(dev->bus->self->devfn);
	/* Check क्रम built-in bridges.  */
	अगर (dev->bus->number != 0
	    && busslot > 16
	    && ((1<<(36-busslot)) & ctlreg)) अणु
		अगर (pin == 1)
			pin += (20 - busslot);
		अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "takara_swizzle: can only "
			       "handle cards with INTA IRQ pin.\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Must be a card-based bridge.  */
		prपूर्णांकk(KERN_WARNING "takara_swizzle: cannot handle "
		       "card-bridge behind builtin bridge yet.\n");
	पूर्ण

	*pinp = pin;
	वापस slot;
पूर्ण

अटल व्योम __init
takara_init_pci(व्योम)
अणु
	अगर (alpha_using_srm)
		alpha_mv.pci_map_irq = takara_map_irq_srm;

	cia_init_pci();

	अगर (pc873xx_probe() == -1) अणु
		prपूर्णांकk(KERN_ERR "Probing for PC873xx Super IO chip failed.\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "Found %s Super IO chip at 0x%x\n",
			pc873xx_get_model(), pc873xx_get_base());
		pc873xx_enable_ide();
	पूर्ण
पूर्ण


/*
 * The System Vector
 */

काष्ठा alpha_machine_vector takara_mv __iniपंचांगv = अणु
	.vector_name		= "Takara",
	DO_EV5_MMU,
	DO_DEFAULT_RTC,
	DO_CIA_IO,
	.machine_check		= cia_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= CIA_DEFAULT_MEM_BASE,

	.nr_irqs		= 128,
	.device_पूर्णांकerrupt	= takara_device_पूर्णांकerrupt,

	.init_arch		= cia_init_arch,
	.init_irq		= takara_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= takara_init_pci,
	.समाप्त_arch		= cia_समाप्त_arch,
	.pci_map_irq		= takara_map_irq,
	.pci_swizzle		= takara_swizzle,
पूर्ण;
ALIAS_MV(takara)
