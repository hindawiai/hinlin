<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/sys_sio.c
 *
 *	Copyright (C) 1995 David A Rusling
 *	Copyright (C) 1996 Jay A Estabrook
 *	Copyright (C) 1998, 1999 Riअक्षरd Henderson
 *
 * Code क्रम all boards that route the PCI पूर्णांकerrupts through the SIO
 * PCI/ISA bridge.  This includes Noname (AXPpci33), Multia (UDB),
 * Kenetics's Platक्रमm 2000, Avanti (AlphaStation), XL, and AlphaBook1.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/screen_info.h>

#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_apecs.h>
#समावेश <यंत्र/core_lca.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "proto.h"
#समावेश "irq_impl.h"
#समावेश "pci_impl.h"
#समावेश "machvec_impl.h"
#समावेश "pc873xx.h"

#अगर defined(ALPHA_RESTORE_SRM_SETUP)
/* Save LCA configuration data as the console had it set up.  */
काष्ठा 
अणु
	अचिन्हित पूर्णांक orig_route_tab; /* क्रम SAVE/RESTORE */
पूर्ण saved_config __attribute((common));
#पूर्ण_अगर


अटल व्योम __init
sio_init_irq(व्योम)
अणु
	अगर (alpha_using_srm)
		alpha_mv.device_पूर्णांकerrupt = srm_device_पूर्णांकerrupt;

	init_i8259a_irqs();
	common_init_isa_dma();
पूर्ण

अटल अंतरभूत व्योम __init
alphabook1_init_arch(व्योम)
अणु
	/* The AlphaBook1 has LCD video fixed at 800x600,
	   37 rows and 100 cols. */
	screen_info.orig_y = 37;
	screen_info.orig_video_cols = 100;
	screen_info.orig_video_lines = 37;

	lca_init_arch();
पूर्ण


/*
 * sio_route_tab selects irq routing in PCI/ISA bridge so that:
 *		PIRQ0 -> irq 15
 *		PIRQ1 -> irq  9
 *		PIRQ2 -> irq 10
 *		PIRQ3 -> irq 11
 *
 * This probably ought to be configurable via MILO.  For
 * example, sound boards seem to like using IRQ 9.
 *
 * This is NOT how we should करो it. PIRQ0-X should have
 * their own IRQs, the way पूर्णांकel uses the IO-APIC IRQs.
 */

अटल व्योम __init
sio_pci_route(व्योम)
अणु
	अचिन्हित पूर्णांक orig_route_tab;

	/* First, ALWAYS पढ़ो and prपूर्णांक the original setting. */
	pci_bus_पढ़ो_config_dword(pci_isa_hose->bus, PCI_DEVFN(7, 0), 0x60,
				  &orig_route_tab);
	prपूर्णांकk("%s: PIRQ original 0x%x new 0x%x\n", __func__,
	       orig_route_tab, alpha_mv.sys.sio.route_tab);

#अगर defined(ALPHA_RESTORE_SRM_SETUP)
	saved_config.orig_route_tab = orig_route_tab;
#पूर्ण_अगर

	/* Now override with desired setting. */
	pci_bus_ग_लिखो_config_dword(pci_isa_hose->bus, PCI_DEVFN(7, 0), 0x60,
				   alpha_mv.sys.sio.route_tab);
पूर्ण

अटल bool sio_pci_dev_irq_needs_level(स्थिर काष्ठा pci_dev *dev)
अणु
	अगर ((dev->class >> 16 == PCI_BASE_CLASS_BRIDGE) &&
	    (dev->class >> 8 != PCI_CLASS_BRIDGE_PCMCIA))
		वापस false;

	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक __init
sio_collect_irq_levels(व्योम)
अणु
	अचिन्हित पूर्णांक level_bits = 0;
	काष्ठा pci_dev *dev = शून्य;

	/* Iterate through the devices, collecting IRQ levels.  */
	क्रम_each_pci_dev(dev) अणु
		अगर (!sio_pci_dev_irq_needs_level(dev))
			जारी;

		अगर (dev->irq)
			level_bits |= (1 << dev->irq);
	पूर्ण
	वापस level_bits;
पूर्ण

अटल व्योम __sio_fixup_irq_levels(अचिन्हित पूर्णांक level_bits, bool reset)
अणु
	अचिन्हित पूर्णांक old_level_bits;

	/*
	 * Now, make all PCI पूर्णांकerrupts level sensitive.  Notice:
	 * these रेजिस्टरs must be accessed byte-wise.  inw()/outw()
	 * करोn't work.
	 *
	 * Make sure to turn off any level bits set क्रम IRQs 9,10,11,15,
	 *  so that the only bits getting set are क्रम devices actually found.
	 * Note that we करो preserve the reमुख्यder of the bits, which we hope
	 *  will be set correctly by ARC/SRM.
	 *
	 * Note: we at least preserve any level-set bits on AlphaBook1
	 */
	old_level_bits = inb(0x4d0) | (inb(0x4d1) << 8);

	अगर (reset)
		old_level_bits &= 0x71ff;

	level_bits |= old_level_bits;

	outb((level_bits >> 0) & 0xff, 0x4d0);
	outb((level_bits >> 8) & 0xff, 0x4d1);
पूर्ण

अटल अंतरभूत व्योम
sio_fixup_irq_levels(अचिन्हित पूर्णांक level_bits)
अणु
	__sio_fixup_irq_levels(level_bits, true);
पूर्ण

अटल अंतरभूत पूर्णांक
noname_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	/*
	 * The Noname board has 5 PCI slots with each of the 4
	 * पूर्णांकerrupt pins routed to dअगरferent pins on the PCI/ISA
	 * bridge (PIRQ0-PIRQ3).  The table below is based on
	 * inक्रमmation available at:
	 *
	 *   http://ftp.digital.com/pub/DEC/axppci/ref_पूर्णांकerrupts.txt
	 *
	 * I have no inक्रमmation on the Avanti पूर्णांकerrupt routing, but
	 * the routing seems to be identical to the Noname except
	 * that the Avanti has an additional slot whose routing I'm
	 * unsure of.
	 *
	 * pirq_tab[0] is a fake entry to deal with old PCI boards
	 * that have the पूर्णांकerrupt pin number hardwired to 0 (meaning
	 * that they use the शेष INTA line, अगर they are पूर्णांकerrupt
	 * driven at all).
	 */
	अटल अक्षर irq_tab[][5] = अणु
		/*INT A   B   C   D */
		अणु 3,  3,  3,  3,  3पूर्ण, /* idsel  6 (53c810) */ 
		अणु-1, -1, -1, -1, -1पूर्ण, /* idsel  7 (SIO: PCI/ISA bridge) */
		अणु 2,  2, -1, -1, -1पूर्ण, /* idsel  8 (Hack: slot बंदst ISA) */
		अणु-1, -1, -1, -1, -1पूर्ण, /* idsel  9 (unused) */
		अणु-1, -1, -1, -1, -1पूर्ण, /* idsel 10 (unused) */
		अणु 0,  0,  2,  1,  0पूर्ण, /* idsel 11 KN25_PCI_SLOT0 */
		अणु 1,  1,  0,  2,  1पूर्ण, /* idsel 12 KN25_PCI_SLOT1 */
		अणु 2,  2,  1,  0,  2पूर्ण, /* idsel 13 KN25_PCI_SLOT2 */
		अणु 0,  0,  0,  0,  0पूर्ण, /* idsel 14 AS255 TULIP */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 6, max_idsel = 14, irqs_per_slot = 5;
	पूर्णांक irq = COMMON_TABLE_LOOKUP, पंचांगp;
	पंचांगp = __kernel_extbl(alpha_mv.sys.sio.route_tab, irq);

	irq = irq >= 0 ? पंचांगp : -1;

	/* Fixup IRQ level अगर an actual IRQ mapping is detected */
	अगर (sio_pci_dev_irq_needs_level(dev) && irq >= 0)
		__sio_fixup_irq_levels(1 << irq, false);

	वापस irq;
पूर्ण

अटल अंतरभूत पूर्णांक
p2k_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल अक्षर irq_tab[][5] = अणु
		/*INT A   B   C   D */
		अणु 0,  0, -1, -1, -1पूर्ण, /* idsel  6 (53c810) */
		अणु-1, -1, -1, -1, -1पूर्ण, /* idsel  7 (SIO: PCI/ISA bridge) */
		अणु 1,  1,  2,  3,  0पूर्ण, /* idsel  8 (slot A) */
		अणु 2,  2,  3,  0,  1पूर्ण, /* idsel  9 (slot B) */
		अणु-1, -1, -1, -1, -1पूर्ण, /* idsel 10 (unused) */
		अणु-1, -1, -1, -1, -1पूर्ण, /* idsel 11 (unused) */
		अणु 3,  3, -1, -1, -1पूर्ण, /* idsel 12 (CMD0646) */
	पूर्ण;
	स्थिर दीर्घ min_idsel = 6, max_idsel = 12, irqs_per_slot = 5;
	पूर्णांक irq = COMMON_TABLE_LOOKUP, पंचांगp;
	पंचांगp = __kernel_extbl(alpha_mv.sys.sio.route_tab, irq);
	वापस irq >= 0 ? पंचांगp : -1;
पूर्ण

अटल अंतरभूत व्योम __init
noname_init_pci(व्योम)
अणु
	common_init_pci();
	sio_pci_route();
	sio_fixup_irq_levels(sio_collect_irq_levels());

	अगर (pc873xx_probe() == -1) अणु
		prपूर्णांकk(KERN_ERR "Probing for PC873xx Super IO chip failed.\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "Found %s Super IO chip at 0x%x\n",
			pc873xx_get_model(), pc873xx_get_base());

		/* Enabling things in the Super IO chip करोesn't actually
		 * configure and enable things, the legacy drivers still
		 * need to करो the actual configuration and enabling.
		 * This only unblocks them.
		 */

#अगर !defined(CONFIG_ALPHA_AVANTI)
		/* Don't bother on the Avanti family.
		 * None of them had on-board IDE.
		 */
		pc873xx_enable_ide();
#पूर्ण_अगर
		pc873xx_enable_epp19();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __init
alphabook1_init_pci(व्योम)
अणु
	काष्ठा pci_dev *dev;
	अचिन्हित अक्षर orig, config;

	common_init_pci();
	sio_pci_route();

	/*
	 * On the AlphaBook1, the PCMCIA chip (Cirrus 6729)
	 * is sensitive to PCI bus bursts, so we must DISABLE
	 * burst mode क्रम the NCR 8xx SCSI... :-(
	 *
	 * Note that the NCR810 SCSI driver must preserve the
	 * setting of the bit in order क्रम this to work.  At the
	 * moment (2.0.29), ncr53c8xx.c करोes NOT करो this, but
	 * 53c7,8xx.c DOES.
	 */

	dev = शून्य;
	जबतक ((dev = pci_get_device(PCI_VENDOR_ID_NCR, PCI_ANY_ID, dev))) अणु
		अगर (dev->device == PCI_DEVICE_ID_NCR_53C810
		    || dev->device == PCI_DEVICE_ID_NCR_53C815
		    || dev->device == PCI_DEVICE_ID_NCR_53C820
		    || dev->device == PCI_DEVICE_ID_NCR_53C825) अणु
			अचिन्हित दीर्घ io_port;
			अचिन्हित अक्षर ctest4;

			io_port = dev->resource[0].start;
			ctest4 = inb(io_port+0x21);
			अगर (!(ctest4 & 0x80)) अणु
				prपूर्णांकk("AlphaBook1 NCR init: setting"
				       " burst disable\n");
				outb(ctest4 | 0x80, io_port+0x21);
			पूर्ण
                पूर्ण
	पूर्ण

	/* Do not set *ANY* level triggers क्रम AlphaBook1. */
	sio_fixup_irq_levels(0);

	/* Make sure that रेजिस्टर PR1 indicates 1Mb mem */
	outb(0x0f, 0x3ce); orig = inb(0x3cf);   /* पढ़ो PR5  */
	outb(0x0f, 0x3ce); outb(0x05, 0x3cf);   /* unlock PR0-4 */
	outb(0x0b, 0x3ce); config = inb(0x3cf); /* पढ़ो PR1 */
	अगर ((config & 0xc0) != 0xc0) अणु
		prपूर्णांकk("AlphaBook1 VGA init: setting 1Mb memory\n");
		config |= 0xc0;
		outb(0x0b, 0x3ce); outb(config, 0x3cf); /* ग_लिखो PR1 */
	पूर्ण
	outb(0x0f, 0x3ce); outb(orig, 0x3cf); /* (re)lock PR0-4 */
पूर्ण

व्योम
sio_समाप्त_arch(पूर्णांक mode)
अणु
#अगर defined(ALPHA_RESTORE_SRM_SETUP)
	/* Since we cannot पढ़ो the PCI DMA Winकरोw CSRs, we
	 * cannot restore them here.
	 *
	 * However, we CAN पढ़ो the PIRQ route रेजिस्टर, so restore it
	 * now...
	 */
 	pci_bus_ग_लिखो_config_dword(pci_isa_hose->bus, PCI_DEVFN(7, 0), 0x60,
				   saved_config.orig_route_tab);
#पूर्ण_अगर
पूर्ण


/*
 * The System Vectors
 */

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_BOOK1)
काष्ठा alpha_machine_vector alphabook1_mv __iniपंचांगv = अणु
	.vector_name		= "AlphaBook1",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_LCA_IO,
	.machine_check		= lca_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 16,
	.device_पूर्णांकerrupt	= isa_device_पूर्णांकerrupt,

	.init_arch		= alphabook1_init_arch,
	.init_irq		= sio_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= alphabook1_init_pci,
	.समाप्त_arch		= sio_समाप्त_arch,
	.pci_map_irq		= noname_map_irq,
	.pci_swizzle		= common_swizzle,

	.sys = अणु .sio = अणु
		/* NCR810 SCSI is 14, PCMCIA controller is 15.  */
		.route_tab	= 0x0e0f0a0a,
	पूर्णपूर्ण
पूर्ण;
ALIAS_MV(alphabook1)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_AVANTI)
काष्ठा alpha_machine_vector avanti_mv __iniपंचांगv = अणु
	.vector_name		= "Avanti",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_APECS_IO,
	.machine_check		= apecs_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 16,
	.device_पूर्णांकerrupt	= isa_device_पूर्णांकerrupt,

	.init_arch		= apecs_init_arch,
	.init_irq		= sio_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= noname_init_pci,
	.समाप्त_arch		= sio_समाप्त_arch,
	.pci_map_irq		= noname_map_irq,
	.pci_swizzle		= common_swizzle,

	.sys = अणु .sio = अणु
		.route_tab	= 0x0b0a050f, /* leave 14 क्रम IDE, 9 क्रम SND */
	पूर्णपूर्ण
पूर्ण;
ALIAS_MV(avanti)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_NONAME)
काष्ठा alpha_machine_vector noname_mv __iniपंचांगv = अणु
	.vector_name		= "Noname",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_LCA_IO,
	.machine_check		= lca_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 16,
	.device_पूर्णांकerrupt	= srm_device_पूर्णांकerrupt,

	.init_arch		= lca_init_arch,
	.init_irq		= sio_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= noname_init_pci,
	.समाप्त_arch		= sio_समाप्त_arch,
	.pci_map_irq		= noname_map_irq,
	.pci_swizzle		= common_swizzle,

	.sys = अणु .sio = अणु
		/* For UDB, the only available PCI slot must not map to IRQ 9,
		   since that's the builtin MSS sound chip. That PCI slot
		   will map to PIRQ1 (क्रम INTA at least), so we give it IRQ 15
		   instead.

		   Unक्रमtunately we have to करो this क्रम NONAME as well, since
		   they are co-indicated when the platक्रमm type "Noname" is
		   selected... :-(  */

		.route_tab	= 0x0b0a0f0d,
	पूर्णपूर्ण
पूर्ण;
ALIAS_MV(noname)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_P2K)
काष्ठा alpha_machine_vector p2k_mv __iniपंचांगv = अणु
	.vector_name		= "Platform2000",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_LCA_IO,
	.machine_check		= lca_machine_check,
	.max_isa_dma_address	= ALPHA_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= APECS_AND_LCA_DEFAULT_MEM_BASE,

	.nr_irqs		= 16,
	.device_पूर्णांकerrupt	= srm_device_पूर्णांकerrupt,

	.init_arch		= lca_init_arch,
	.init_irq		= sio_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= noname_init_pci,
	.समाप्त_arch		= sio_समाप्त_arch,
	.pci_map_irq		= p2k_map_irq,
	.pci_swizzle		= common_swizzle,

	.sys = अणु .sio = अणु
		.route_tab	= 0x0b0a090f,
	पूर्णपूर्ण
पूर्ण;
ALIAS_MV(p2k)
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_XL)
काष्ठा alpha_machine_vector xl_mv __iniपंचांगv = अणु
	.vector_name		= "XL",
	DO_EV4_MMU,
	DO_DEFAULT_RTC,
	DO_APECS_IO,
	.machine_check		= apecs_machine_check,
	.max_isa_dma_address	= ALPHA_XL_MAX_ISA_DMA_ADDRESS,
	.min_io_address		= DEFAULT_IO_BASE,
	.min_mem_address	= XL_DEFAULT_MEM_BASE,

	.nr_irqs		= 16,
	.device_पूर्णांकerrupt	= isa_device_पूर्णांकerrupt,

	.init_arch		= apecs_init_arch,
	.init_irq		= sio_init_irq,
	.init_rtc		= common_init_rtc,
	.init_pci		= noname_init_pci,
	.समाप्त_arch		= sio_समाप्त_arch,
	.pci_map_irq		= noname_map_irq,
	.pci_swizzle		= common_swizzle,

	.sys = अणु .sio = अणु
		.route_tab	= 0x0b0a090f,
	पूर्णपूर्ण
पूर्ण;
ALIAS_MV(xl)
#पूर्ण_अगर
