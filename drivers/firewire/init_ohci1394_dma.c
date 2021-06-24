<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * init_ohci1394_dma.c - Initializes physical DMA on all OHCI 1394 controllers
 *
 * Copyright (C) 2006-2007      Bernhard Kaindl <bk@suse.de>
 *
 * Derived from drivers/ieee1394/ohci1394.c and arch/x86/kernel/early-quirks.c
 * this file has functions to:
 * - scan the PCI very early on boot क्रम all OHCI 1394-compliant controllers
 * - reset and initialize them and make them join the IEEE1394 bus and
 * - enable physical DMA on them to allow remote debugging
 *
 * All code and data is marked as __init and __initdata, respective as
 * during boot, all OHCI1394 controllers may be claimed by the firewire
 * stack and at this poपूर्णांक, this code should not touch them anymore.
 *
 * To use physical DMA after the initialization of the firewire stack,
 * be sure that the stack enables it and (re-)attach after the bus reset
 * which may be caused by the firewire stack initialization.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>		/* क्रम PCI defines */
#समावेश <linux/माला.स>

#समावेश <यंत्र/pci-direct.h>	/* क्रम direct PCI config space access */
#समावेश <यंत्र/fixmap.h>

#समावेश <linux/init_ohci1394_dma.h>
#समावेश "ohci.h"

पूर्णांक __initdata init_ohci1394_dma_early;

काष्ठा ohci अणु
	व्योम __iomem *रेजिस्टरs;
पूर्ण;

अटल अंतरभूत व्योम reg_ग_लिखो(स्थिर काष्ठा ohci *ohci, पूर्णांक offset, u32 data)
अणु
	ग_लिखोl(data, ohci->रेजिस्टरs + offset);
पूर्ण

अटल अंतरभूत u32 reg_पढ़ो(स्थिर काष्ठा ohci *ohci, पूर्णांक offset)
अणु
	वापस पढ़ोl(ohci->रेजिस्टरs + offset);
पूर्ण

#घोषणा OHCI_LOOP_COUNT		100	/* Number of loops क्रम reg पढ़ो रुकोs */

/* Reads a PHY रेजिस्टर of an OHCI-1394 controller */
अटल अंतरभूत u8 __init get_phy_reg(काष्ठा ohci *ohci, u8 addr)
अणु
	पूर्णांक i;
	u32 r;

	reg_ग_लिखो(ohci, OHCI1394_PhyControl, (addr << 8) | 0x00008000);

	क्रम (i = 0; i < OHCI_LOOP_COUNT; i++) अणु
		अगर (reg_पढ़ो(ohci, OHCI1394_PhyControl) & 0x80000000)
			अवरोध;
		mdelay(1);
	पूर्ण
	r = reg_पढ़ो(ohci, OHCI1394_PhyControl);

	वापस (r & 0x00ff0000) >> 16;
पूर्ण

/* Writes to a PHY रेजिस्टर of an OHCI-1394 controller */
अटल अंतरभूत व्योम __init set_phy_reg(काष्ठा ohci *ohci, u8 addr, u8 data)
अणु
	पूर्णांक i;

	reg_ग_लिखो(ohci, OHCI1394_PhyControl, (addr << 8) | data | 0x00004000);

	क्रम (i = 0; i < OHCI_LOOP_COUNT; i++) अणु
		अगर (!(reg_पढ़ो(ohci, OHCI1394_PhyControl) & 0x00004000))
			अवरोध;
		mdelay(1);
	पूर्ण
पूर्ण

/* Resets an OHCI-1394 controller (क्रम sane state beक्रमe initialization) */
अटल अंतरभूत व्योम __init init_ohci1394_soft_reset(काष्ठा ohci *ohci)
अणु
	पूर्णांक i;

	reg_ग_लिखो(ohci, OHCI1394_HCControlSet, OHCI1394_HCControl_softReset);

	क्रम (i = 0; i < OHCI_LOOP_COUNT; i++) अणु
		अगर (!(reg_पढ़ो(ohci, OHCI1394_HCControlSet)
				   & OHCI1394_HCControl_softReset))
			अवरोध;
		mdelay(1);
	पूर्ण
पूर्ण

#घोषणा OHCI1394_MAX_AT_REQ_RETRIES	0xf
#घोषणा OHCI1394_MAX_AT_RESP_RETRIES	0x2
#घोषणा OHCI1394_MAX_PHYS_RESP_RETRIES	0x8

/* Basic OHCI-1394 रेजिस्टर and port inititalization */
अटल अंतरभूत व्योम __init init_ohci1394_initialize(काष्ठा ohci *ohci)
अणु
	u32 bus_options;
	पूर्णांक num_ports, i;

	/* Put some शेषs to these undefined bus options */
	bus_options = reg_पढ़ो(ohci, OHCI1394_BusOptions);
	bus_options |=  0x60000000; /* Enable CMC and ISC */
	bus_options &= ~0x00ff0000; /* XXX: Set cyc_clk_acc to zero क्रम now */
	bus_options &= ~0x18000000; /* Disable PMC and BMC */
	reg_ग_लिखो(ohci, OHCI1394_BusOptions, bus_options);

	/* Set the bus number */
	reg_ग_लिखो(ohci, OHCI1394_NodeID, 0x0000ffc0);

	/* Enable posted ग_लिखोs */
	reg_ग_लिखो(ohci, OHCI1394_HCControlSet,
			OHCI1394_HCControl_postedWriteEnable);

	/* Clear link control रेजिस्टर */
	reg_ग_लिखो(ohci, OHCI1394_LinkControlClear, 0xffffffff);

	/* enable phys */
	reg_ग_लिखो(ohci, OHCI1394_LinkControlSet,
			OHCI1394_LinkControl_rcvPhyPkt);

	/* Don't accept phy packets पूर्णांकo AR request context */
	reg_ग_लिखो(ohci, OHCI1394_LinkControlClear, 0x00000400);

	/* Clear the Isochonouys पूर्णांकerrupt masks */
	reg_ग_लिखो(ohci, OHCI1394_IsoRecvIntMaskClear, 0xffffffff);
	reg_ग_लिखो(ohci, OHCI1394_IsoRecvIntEventClear, 0xffffffff);
	reg_ग_लिखो(ohci, OHCI1394_IsoXmitIntMaskClear, 0xffffffff);
	reg_ग_लिखो(ohci, OHCI1394_IsoXmitIntEventClear, 0xffffffff);

	/* Accept asynchronous transfer requests from all nodes क्रम now */
	reg_ग_लिखो(ohci, OHCI1394_AsReqFilterHiSet, 0x80000000);

	/* Specअगरy asynchronous transfer retries */
	reg_ग_लिखो(ohci, OHCI1394_ATRetries,
		  OHCI1394_MAX_AT_REQ_RETRIES |
		  (OHCI1394_MAX_AT_RESP_RETRIES<<4) |
		  (OHCI1394_MAX_PHYS_RESP_RETRIES<<8));

	/* We करोn't want hardware swapping */
	reg_ग_लिखो(ohci, OHCI1394_HCControlClear,
		  OHCI1394_HCControl_noByteSwapData);

	/* Enable link */
	reg_ग_लिखो(ohci, OHCI1394_HCControlSet, OHCI1394_HCControl_linkEnable);

	/* If anything is connected to a port, make sure it is enabled */
	num_ports = get_phy_reg(ohci, 2) & 0xf;
	क्रम (i = 0; i < num_ports; i++) अणु
		अचिन्हित पूर्णांक status;

		set_phy_reg(ohci, 7, i);
		status = get_phy_reg(ohci, 8);

		अगर (status & 0x20)
			set_phy_reg(ohci, 8, status & ~1);
	पूर्ण
पूर्ण

/**
 * init_ohci1394_रुको_क्रम_busresets - रुको until bus resets are completed
 *
 * OHCI1394 initialization itself and any device going on- or offline
 * and any cable issue cause a IEEE1394 bus reset. The OHCI1394 spec
 * specअगरies that physical DMA is disabled on each bus reset and it
 * has to be enabled after each bus reset when needed. We resort
 * to polling here because on early boot, we have no पूर्णांकerrupts.
 */
अटल अंतरभूत व्योम __init init_ohci1394_रुको_क्रम_busresets(काष्ठा ohci *ohci)
अणु
	पूर्णांक i, events;

	क्रम (i = 0; i < 9; i++) अणु
		mdelay(200);
		events = reg_पढ़ो(ohci, OHCI1394_IntEventSet);
		अगर (events & OHCI1394_busReset)
			reg_ग_लिखो(ohci, OHCI1394_IntEventClear,
					OHCI1394_busReset);
	पूर्ण
पूर्ण

/**
 * init_ohci1394_enable_physical_dma - Enable physical DMA क्रम remote debugging
 * This enables remote DMA access over IEEE1394 from every host क्रम the low
 * 4GB of address space. DMA accesses above 4GB are not available currently.
 */
अटल अंतरभूत व्योम __init init_ohci1394_enable_physical_dma(काष्ठा ohci *ohci)
अणु
	reg_ग_लिखो(ohci, OHCI1394_PhyReqFilterHiSet, 0xffffffff);
	reg_ग_लिखो(ohci, OHCI1394_PhyReqFilterLoSet, 0xffffffff);
	reg_ग_लिखो(ohci, OHCI1394_PhyUpperBound, 0xffff0000);
पूर्ण

/**
 * init_ohci1394_reset_and_init_dma - init controller and enable DMA
 * This initializes the given controller and enables physical DMA engine in it.
 */
अटल अंतरभूत व्योम __init init_ohci1394_reset_and_init_dma(काष्ठा ohci *ohci)
अणु
	/* Start off with a soft reset, clears everything to a sane state. */
	init_ohci1394_soft_reset(ohci);

	/* Accessing some रेजिस्टरs without LPS enabled may cause lock up */
	reg_ग_लिखो(ohci, OHCI1394_HCControlSet, OHCI1394_HCControl_LPS);

	/* Disable and clear पूर्णांकerrupts */
	reg_ग_लिखो(ohci, OHCI1394_IntEventClear, 0xffffffff);
	reg_ग_लिखो(ohci, OHCI1394_IntMaskClear, 0xffffffff);

	mdelay(50); /* Wait 50msec to make sure we have full link enabled */

	init_ohci1394_initialize(ohci);
	/*
	 * The initialization causes at least one IEEE1394 bus reset. Enabling
	 * physical DMA only works *after* *all* bus resets have calmed करोwn:
	 */
	init_ohci1394_रुको_क्रम_busresets(ohci);

	/* We had to रुको and करो this now अगर we want to debug early problems */
	init_ohci1394_enable_physical_dma(ohci);
पूर्ण

/**
 * init_ohci1394_controller - Map the रेजिस्टरs of the controller and init DMA
 * This maps the रेजिस्टरs of the specअगरied controller and initializes it
 */
अटल अंतरभूत व्योम __init init_ohci1394_controller(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	अचिन्हित दीर्घ ohci_base;
	काष्ठा ohci ohci;

	prपूर्णांकk(KERN_INFO "init_ohci1394_dma: initializing OHCI-1394"
			 " at %02x:%02x.%x\n", num, slot, func);

	ohci_base = पढ़ो_pci_config(num, slot, func, PCI_BASE_ADDRESS_0+(0<<2))
						   & PCI_BASE_ADDRESS_MEM_MASK;

	set_fixmap_nocache(FIX_OHCI1394_BASE, ohci_base);

	ohci.रेजिस्टरs = (व्योम __iomem *)fix_to_virt(FIX_OHCI1394_BASE);

	init_ohci1394_reset_and_init_dma(&ohci);
पूर्ण

/**
 * debug_init_ohci1394_dma - scan क्रम OHCI1394 controllers and init DMA on them
 * Scans the whole PCI space क्रम OHCI1394 controllers and inits DMA on them
 */
व्योम __init init_ohci1394_dma_on_all_controllers(व्योम)
अणु
	पूर्णांक num, slot, func;
	u32 class;

	अगर (!early_pci_allowed())
		वापस;

	/* Poor man's PCI discovery, the only thing we can करो at early boot */
	क्रम (num = 0; num < 32; num++) अणु
		क्रम (slot = 0; slot < 32; slot++) अणु
			क्रम (func = 0; func < 8; func++) अणु
				class = पढ़ो_pci_config(num, slot, func,
							PCI_CLASS_REVISION);
				अगर (class == 0xffffffff)
					जारी; /* No device at this func */

				अगर (class>>8 != PCI_CLASS_SERIAL_FIREWIRE_OHCI)
					जारी; /* Not an OHCI-1394 device */

				init_ohci1394_controller(num, slot, func);
				अवरोध; /* Assume one controller per device */
			पूर्ण
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_INFO "init_ohci1394_dma: finished initializing OHCI DMA\n");
पूर्ण

/**
 * setup_init_ohci1394_early - enables early OHCI1394 DMA initialization
 */
अटल पूर्णांक __init setup_ohci1394_dma(अक्षर *opt)
अणु
	अगर (!म_भेद(opt, "early"))
		init_ohci1394_dma_early = 1;
	वापस 0;
पूर्ण

/* passing ohci1394_dma=early on boot causes early OHCI1394 DMA initialization */
early_param("ohci1394_dma", setup_ohci1394_dma);
