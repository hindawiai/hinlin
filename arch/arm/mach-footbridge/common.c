<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-footbridge/common.c
 *
 *  Copyright (C) 1998-2000 Russell King, Dave Gilbert.
 */
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/ioport.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <video/vga.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/hardware/dec21285.h>

#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/pci.h>

#समावेश "common.h"

अचिन्हित पूर्णांक mem_fclk_21285 = 50000000;

EXPORT_SYMBOL(mem_fclk_21285);

अटल पूर्णांक __init early_fclk(अक्षर *arg)
अणु
	mem_fclk_21285 = simple_म_से_अदीर्घ(arg, शून्य, 0);
	वापस 0;
पूर्ण

early_param("mem_fclk_21285", early_fclk);

अटल पूर्णांक __init parse_tag_memclk(स्थिर काष्ठा tag *tag)
अणु
	mem_fclk_21285 = tag->u.memclk.fmemclk;
	वापस 0;
पूर्ण

__tagtable(ATAG_MEMCLK, parse_tag_memclk);

/*
 * Footbridge IRQ translation table
 *  Converts from our IRQ numbers पूर्णांकo FootBridge masks
 */
अटल स्थिर पूर्णांक fb_irq_mask[] = अणु
	IRQ_MASK_UART_RX,	/*  0 */
	IRQ_MASK_UART_TX,	/*  1 */
	IRQ_MASK_TIMER1,	/*  2 */
	IRQ_MASK_TIMER2,	/*  3 */
	IRQ_MASK_TIMER3,	/*  4 */
	IRQ_MASK_IN0,		/*  5 */
	IRQ_MASK_IN1,		/*  6 */
	IRQ_MASK_IN2,		/*  7 */
	IRQ_MASK_IN3,		/*  8 */
	IRQ_MASK_DOORBELLHOST,	/*  9 */
	IRQ_MASK_DMA1,		/* 10 */
	IRQ_MASK_DMA2,		/* 11 */
	IRQ_MASK_PCI,		/* 12 */
	IRQ_MASK_SDRAMPARITY,	/* 13 */
	IRQ_MASK_I2OINPOST,	/* 14 */
	IRQ_MASK_PCI_ABORT,	/* 15 */
	IRQ_MASK_PCI_SERR,	/* 16 */
	IRQ_MASK_DISCARD_TIMER,	/* 17 */
	IRQ_MASK_PCI_DPERR,	/* 18 */
	IRQ_MASK_PCI_PERR,	/* 19 */
पूर्ण;

अटल व्योम fb_mask_irq(काष्ठा irq_data *d)
अणु
	*CSR_IRQ_DISABLE = fb_irq_mask[_DC21285_INR(d->irq)];
पूर्ण

अटल व्योम fb_unmask_irq(काष्ठा irq_data *d)
अणु
	*CSR_IRQ_ENABLE = fb_irq_mask[_DC21285_INR(d->irq)];
पूर्ण

अटल काष्ठा irq_chip fb_chip = अणु
	.irq_ack	= fb_mask_irq,
	.irq_mask	= fb_mask_irq,
	.irq_unmask	= fb_unmask_irq,
पूर्ण;

अटल व्योम __init __fb_init_irq(व्योम)
अणु
	अचिन्हित पूर्णांक irq;

	/*
	 * setup DC21285 IRQs
	 */
	*CSR_IRQ_DISABLE = -1;
	*CSR_FIQ_DISABLE = -1;

	क्रम (irq = _DC21285_IRQ(0); irq < _DC21285_IRQ(20); irq++) अणु
		irq_set_chip_and_handler(irq, &fb_chip, handle_level_irq);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण
पूर्ण

व्योम __init footbridge_init_irq(व्योम)
अणु
	__fb_init_irq();

	अगर (!footbridge_cfn_mode())
		वापस;

	अगर (machine_is_ebsa285())
		/* The following is dependent on which slot
		 * you plug the Southbridge card पूर्णांकo.  We
		 * currently assume that you plug it पूर्णांकo
		 * the right-hand most slot.
		 */
		isa_init_irq(IRQ_PCI);

	अगर (machine_is_cats())
		isa_init_irq(IRQ_IN2);

	अगर (machine_is_netwinder())
		isa_init_irq(IRQ_IN3);
पूर्ण

/*
 * Common mapping क्रम all प्रणालीs.  Note that the outbound ग_लिखो flush is
 * commented out since there is a "No Fix" problem with it.  Not mapping
 * it means that we have extra bullet protection on our feet.
 */
अटल काष्ठा map_desc fb_common_io_desc[] __initdata = अणु
	अणु
		.भव	= ARMCSR_BASE,
		.pfn		= __phys_to_pfn(DC21285_ARMCSR_BASE),
		.length		= ARMCSR_SIZE,
		.type		= MT_DEVICE,
	पूर्ण
पूर्ण;

/*
 * The mapping when the footbridge is in host mode.  We करोn't map any of
 * this when we are in add-in mode.
 */
अटल काष्ठा map_desc ebsa285_host_io_desc[] __initdata = अणु
#अगर defined(CONFIG_ARCH_FOOTBRIDGE) && defined(CONFIG_FOOTBRIDGE_HOST)
	अणु
		.भव	= PCIMEM_BASE,
		.pfn		= __phys_to_pfn(DC21285_PCI_MEM),
		.length		= PCIMEM_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= PCICFG0_BASE,
		.pfn		= __phys_to_pfn(DC21285_PCI_TYPE_0_CONFIG),
		.length		= PCICFG0_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= PCICFG1_BASE,
		.pfn		= __phys_to_pfn(DC21285_PCI_TYPE_1_CONFIG),
		.length		= PCICFG1_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= PCIIACK_BASE,
		.pfn		= __phys_to_pfn(DC21285_PCI_IACK),
		.length		= PCIIACK_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

व्योम __init footbridge_map_io(व्योम)
अणु
	/*
	 * Set up the common mapping first; we need this to
	 * determine whether we're in host mode or not.
	 */
	iotable_init(fb_common_io_desc, ARRAY_SIZE(fb_common_io_desc));

	/*
	 * Now, work out what we've got to map in addition on this
	 * platक्रमm.
	 */
	अगर (footbridge_cfn_mode()) अणु
		iotable_init(ebsa285_host_io_desc, ARRAY_SIZE(ebsa285_host_io_desc));
		pci_map_io_early(__phys_to_pfn(DC21285_PCI_IO));
	पूर्ण

	vga_base = PCIMEM_BASE;
पूर्ण

व्योम footbridge_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (mode == REBOOT_SOFT) अणु
		/* Jump पूर्णांकo the ROM */
		soft_restart(0x41000000);
	पूर्ण अन्यथा अणु
		/*
		 * Force the watchकरोg to करो a CPU reset.
		 *
		 * After making sure that the watchकरोg is disabled
		 * (so we can change the समयr रेजिस्टरs) we first
		 * enable the समयr to स्वतःreload itself.  Next, the
		 * समयr पूर्णांकerval is set really लघु and any
		 * current पूर्णांकerrupt request is cleared (so we can
		 * see an edge transition).  Finally, TIMER4 is
		 * enabled as the watchकरोg.
		 */
		*CSR_SA110_CNTL &= ~(1 << 13);
		*CSR_TIMER4_CNTL = TIMER_CNTL_ENABLE |
				   TIMER_CNTL_AUTORELOAD |
				   TIMER_CNTL_DIV16;
		*CSR_TIMER4_LOAD = 0x2;
		*CSR_TIMER4_CLR  = 0;
		*CSR_SA110_CNTL |= (1 << 13);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_FOOTBRIDGE_ADDIN

अटल अंतरभूत अचिन्हित दीर्घ fb_bus_sdram_offset(व्योम)
अणु
	वापस *CSR_PCISDRAMBASE & 0xfffffff0;
पूर्ण

/*
 * These two functions convert भव addresses to PCI addresses and PCI
 * addresses to भव addresses.  Note that it is only legal to use these
 * on memory obtained via get_zeroed_page or kदो_स्मृति.
 */
अचिन्हित दीर्घ __virt_to_bus(अचिन्हित दीर्घ res)
अणु
	WARN_ON(res < PAGE_OFFSET || res >= (अचिन्हित दीर्घ)high_memory);

	वापस res + (fb_bus_sdram_offset() - PAGE_OFFSET);
पूर्ण
EXPORT_SYMBOL(__virt_to_bus);

अचिन्हित दीर्घ __bus_to_virt(अचिन्हित दीर्घ res)
अणु
	res = res - (fb_bus_sdram_offset() - PAGE_OFFSET);

	WARN_ON(res < PAGE_OFFSET || res >= (अचिन्हित दीर्घ)high_memory);

	वापस res;
पूर्ण
EXPORT_SYMBOL(__bus_to_virt);

अचिन्हित दीर्घ __pfn_to_bus(अचिन्हित दीर्घ pfn)
अणु
	वापस __pfn_to_phys(pfn) + (fb_bus_sdram_offset() - PHYS_OFFSET);
पूर्ण
EXPORT_SYMBOL(__pfn_to_bus);

अचिन्हित दीर्घ __bus_to_pfn(अचिन्हित दीर्घ bus)
अणु
	वापस __phys_to_pfn(bus - (fb_bus_sdram_offset() - PHYS_OFFSET));
पूर्ण
EXPORT_SYMBOL(__bus_to_pfn);

#पूर्ण_अगर
