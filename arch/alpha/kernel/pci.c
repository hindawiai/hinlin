<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/pci.c
 *
 * Extruded from code written by
 *	Dave Rusling (david.rusling@reo.mts.dec.com)
 *	David Mosberger (davidm@cs.arizona.edu)
 */

/* 2.3.x PCI/resources, 1999 Andrea Arcangeli <andrea@suse.de> */

/*
 * Nov 2000, Ivan Kokshaysky <ink@jurassic.park.msu.ru>
 *	     PCI-PCI bridges cleanup
 */
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/module.h>
#समावेश <linux/cache.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र/machvec.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"


/*
 * Some string स्थिरants used by the various core logics. 
 */

स्थिर अक्षर *स्थिर pci_io_names[] = अणु
  "PCI IO bus 0", "PCI IO bus 1", "PCI IO bus 2", "PCI IO bus 3",
  "PCI IO bus 4", "PCI IO bus 5", "PCI IO bus 6", "PCI IO bus 7"
पूर्ण;

स्थिर अक्षर *स्थिर pci_mem_names[] = अणु
  "PCI mem bus 0", "PCI mem bus 1", "PCI mem bus 2", "PCI mem bus 3",
  "PCI mem bus 4", "PCI mem bus 5", "PCI mem bus 6", "PCI mem bus 7"
पूर्ण;

स्थिर अक्षर pci_hae0_name[] = "HAE0";

/*
 * If PCI_PROBE_ONLY in pci_flags is set, we करोn't change any PCI resource
 * assignments.
 */

/*
 * The PCI controller list.
 */

काष्ठा pci_controller *hose_head, **hose_tail = &hose_head;
काष्ठा pci_controller *pci_isa_hose;

/*
 * Quirks.
 */

अटल व्योम quirk_isa_bridge(काष्ठा pci_dev *dev)
अणु
	dev->class = PCI_CLASS_BRIDGE_ISA << 8;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82378, quirk_isa_bridge);

अटल व्योम quirk_cypress(काष्ठा pci_dev *dev)
अणु
	/* The Notorious Cy82C693 chip.  */

	/* The generic legacy mode IDE fixup in drivers/pci/probe.c
	   करोesn't work correctly with the Cypress IDE controller as
	   it has non-standard रेजिस्टर layout.  Fix that.  */
	अगर (dev->class >> 8 == PCI_CLASS_STORAGE_IDE) अणु
		dev->resource[2].start = dev->resource[3].start = 0;
		dev->resource[2].end = dev->resource[3].end = 0;
		dev->resource[2].flags = dev->resource[3].flags = 0;
		अगर (PCI_FUNC(dev->devfn) == 2) अणु
			dev->resource[0].start = 0x170;
			dev->resource[0].end = 0x177;
			dev->resource[1].start = 0x376;
			dev->resource[1].end = 0x376;
		पूर्ण
	पूर्ण

	/* The Cypress bridge responds on the PCI bus in the address range
	   0xffff0000-0xffffffff (conventional x86 BIOS ROM).  There is no
	   way to turn this off.  The bridge also supports several extended
	   BIOS ranges (disabled after घातer-up), and some consoles करो turn
	   them on.  So अगर we use a large direct-map winकरोw, or a large SG
	   winकरोw, we must aव्योम the entire 0xfff00000-0xffffffff region.  */
	अगर (dev->class >> 8 == PCI_CLASS_BRIDGE_ISA) अणु
		अगर (__direct_map_base + __direct_map_size >= 0xfff00000UL)
			__direct_map_size = 0xfff00000UL - __direct_map_base;
		अन्यथा अणु
			काष्ठा pci_controller *hose = dev->sysdata;
			काष्ठा pci_iommu_arena *pci = hose->sg_pci;
			अगर (pci && pci->dma_base + pci->size >= 0xfff00000UL)
				pci->size = 0xfff00000UL - pci->dma_base;
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_CONTAQ, PCI_DEVICE_ID_CONTAQ_82C693, quirk_cypress);

/* Called क्रम each device after PCI setup is करोne. */
अटल व्योम pcibios_fixup_final(काष्ठा pci_dev *dev)
अणु
	अचिन्हित पूर्णांक class = dev->class >> 8;

	अगर (class == PCI_CLASS_BRIDGE_ISA || class == PCI_CLASS_BRIDGE_EISA) अणु
		dev->dma_mask = MAX_ISA_DMA_ADDRESS - 1;
		isa_bridge = dev;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_ANY_ID, PCI_ANY_ID, pcibios_fixup_final);

/* Just declaring that the घातer-of-ten prefixes are actually the
   घातer-of-two ones करोesn't make it true :) */
#घोषणा KB			1024
#घोषणा MB			(1024*KB)
#घोषणा GB			(1024*MB)

resource_माप_प्रकार
pcibios_align_resource(व्योम *data, स्थिर काष्ठा resource *res,
		       resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा pci_dev *dev = data;
	काष्ठा pci_controller *hose = dev->sysdata;
	अचिन्हित दीर्घ alignto;
	resource_माप_प्रकार start = res->start;

	अगर (res->flags & IORESOURCE_IO) अणु
		/* Make sure we start at our min on all hoses */
		अगर (start - hose->io_space->start < PCIBIOS_MIN_IO)
			start = PCIBIOS_MIN_IO + hose->io_space->start;

		/*
		 * Put everything पूर्णांकo 0x00-0xff region modulo 0x400
		 */
		अगर (start & 0x300)
			start = (start + 0x3ff) & ~0x3ff;
	पूर्ण
	अन्यथा अगर	(res->flags & IORESOURCE_MEM) अणु
		/* Make sure we start at our min on all hoses */
		अगर (start - hose->mem_space->start < PCIBIOS_MIN_MEM)
			start = PCIBIOS_MIN_MEM + hose->mem_space->start;

		/*
		 * The following holds at least क्रम the Low Cost
		 * Alpha implementation of the PCI पूर्णांकerface:
		 *
		 * In sparse memory address space, the first
		 * octant (16MB) of every 128MB segment is
		 * aliased to the very first 16 MB of the
		 * address space (i.e., it aliases the ISA
		 * memory address space).  Thus, we try to
		 * aव्योम allocating PCI devices in that range.
		 * Can be allocated in 2nd-7th octant only.
		 * Devices that need more than 112MB of
		 * address space must be accessed through
		 * dense memory space only!
		 */

		/* Align to multiple of size of minimum base.  */
		alignto = max_t(resource_माप_प्रकार, 0x1000, align);
		start = ALIGN(start, alignto);
		अगर (hose->sparse_mem_base && size <= 7 * 16*MB) अणु
			अगर (((start / (16*MB)) & 0x7) == 0) अणु
				start &= ~(128*MB - 1);
				start += 16*MB;
				start  = ALIGN(start, alignto);
			पूर्ण
			अगर (start/(128*MB) != (start + size - 1)/(128*MB)) अणु
				start &= ~(128*MB - 1);
				start += (128 + 16)*MB;
				start  = ALIGN(start, alignto);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस start;
पूर्ण
#अघोषित KB
#अघोषित MB
#अघोषित GB

अटल पूर्णांक __init
pcibios_init(व्योम)
अणु
	अगर (alpha_mv.init_pci)
		alpha_mv.init_pci();
	वापस 0;
पूर्ण

subsys_initcall(pcibios_init);

#अगर_घोषित ALPHA_RESTORE_SRM_SETUP
/* Store PCI device configuration left by SRM here. */
काष्ठा pdev_srm_saved_conf
अणु
	काष्ठा pdev_srm_saved_conf *next;
	काष्ठा pci_dev *dev;
पूर्ण;

अटल काष्ठा pdev_srm_saved_conf *srm_saved_configs;

अटल व्योम pdev_save_srm_config(काष्ठा pci_dev *dev)
अणु
	काष्ठा pdev_srm_saved_conf *पंचांगp;
	अटल पूर्णांक prपूर्णांकed = 0;

	अगर (!alpha_using_srm || pci_has_flag(PCI_PROBE_ONLY))
		वापस;

	अगर (!prपूर्णांकed) अणु
		prपूर्णांकk(KERN_INFO "pci: enabling save/restore of SRM state\n");
		prपूर्णांकed = 1;
	पूर्ण

	पंचांगp = kदो_स्मृति(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp) अणु
		prपूर्णांकk(KERN_ERR "%s: kmalloc() failed!\n", __func__);
		वापस;
	पूर्ण
	पंचांगp->next = srm_saved_configs;
	पंचांगp->dev = dev;

	pci_save_state(dev);

	srm_saved_configs = पंचांगp;
पूर्ण

व्योम
pci_restore_srm_config(व्योम)
अणु
	काष्ठा pdev_srm_saved_conf *पंचांगp;

	/* No need to restore अगर probed only. */
	अगर (pci_has_flag(PCI_PROBE_ONLY))
		वापस;

	/* Restore SRM config. */
	क्रम (पंचांगp = srm_saved_configs; पंचांगp; पंचांगp = पंचांगp->next) अणु
		pci_restore_state(पंचांगp->dev);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा pdev_save_srm_config(dev)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

व्योम pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev = bus->self;

	अगर (pci_has_flag(PCI_PROBE_ONLY) && dev &&
	    (dev->class >> 8) == PCI_CLASS_BRIDGE_PCI) अणु
		pci_पढ़ो_bridge_bases(bus);
	पूर्ण

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		pdev_save_srm_config(dev);
	पूर्ण
पूर्ण

/*
 *  If we set up a device क्रम bus mastering, we need to check the latency
 *  समयr as certain firmware क्रममाला_लो to set it properly, as seen
 *  on SX164 and LX164 with SRM.
 */
व्योम
pcibios_set_master(काष्ठा pci_dev *dev)
अणु
	u8 lat;
	pci_पढ़ो_config_byte(dev, PCI_LATENCY_TIMER, &lat);
	अगर (lat >= 16) वापस;
	prपूर्णांकk("PCI: Setting latency timer of device %s to 64\n",
							pci_name(dev));
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 64);
पूर्ण

व्योम __init
pcibios_claim_one_bus(काष्ठा pci_bus *b)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *child_bus;

	list_क्रम_each_entry(dev, &b->devices, bus_list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < PCI_NUM_RESOURCES; i++) अणु
			काष्ठा resource *r = &dev->resource[i];

			अगर (r->parent || !r->start || !r->flags)
				जारी;
			अगर (pci_has_flag(PCI_PROBE_ONLY) ||
			    (r->flags & IORESOURCE_PCI_FIXED)) अणु
				अगर (pci_claim_resource(dev, i) == 0)
					जारी;

				pci_claim_bridge_resource(dev, i);
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(child_bus, &b->children, node)
		pcibios_claim_one_bus(child_bus);
पूर्ण

अटल व्योम __init
pcibios_claim_console_setup(व्योम)
अणु
	काष्ठा pci_bus *b;

	list_क्रम_each_entry(b, &pci_root_buses, node)
		pcibios_claim_one_bus(b);
पूर्ण

व्योम __init
common_init_pci(व्योम)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा list_head resources;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा pci_bus *bus;
	पूर्णांक ret, next_busno;
	पूर्णांक need_करोमुख्य_info = 0;
	u32 pci_mem_end;
	u32 sg_base;
	अचिन्हित दीर्घ end;

	/* Scan all of the recorded PCI controllers.  */
	क्रम (next_busno = 0, hose = hose_head; hose; hose = hose->next) अणु
		sg_base = hose->sg_pci ? hose->sg_pci->dma_base : ~0;

		/* Adjust hose mem_space limit to prevent PCI allocations
		   in the iommu winकरोws. */
		pci_mem_end = min((u32)__direct_map_base, sg_base) - 1;
		end = hose->mem_space->start + pci_mem_end;
		अगर (hose->mem_space->end > end)
			hose->mem_space->end = end;

		INIT_LIST_HEAD(&resources);
		pci_add_resource_offset(&resources, hose->io_space,
					hose->io_space->start);
		pci_add_resource_offset(&resources, hose->mem_space,
					hose->mem_space->start);

		bridge = pci_alloc_host_bridge(0);
		अगर (!bridge)
			जारी;

		list_splice_init(&resources, &bridge->winकरोws);
		bridge->dev.parent = शून्य;
		bridge->sysdata = hose;
		bridge->busnr = next_busno;
		bridge->ops = alpha_mv.pci_ops;
		bridge->swizzle_irq = alpha_mv.pci_swizzle;
		bridge->map_irq = alpha_mv.pci_map_irq;

		ret = pci_scan_root_bus_bridge(bridge);
		अगर (ret) अणु
			pci_मुक्त_host_bridge(bridge);
			जारी;
		पूर्ण

		bus = hose->bus = bridge->bus;
		hose->need_करोमुख्य_info = need_करोमुख्य_info;
		next_busno = bus->busn_res.end + 1;
		/* Don't allow 8-bit bus number overflow inside the hose -
		   reserve some space क्रम bridges. */ 
		अगर (next_busno > 224) अणु
			next_busno = 0;
			need_करोमुख्य_info = 1;
		पूर्ण
	पूर्ण

	pcibios_claim_console_setup();

	pci_assign_unasचिन्हित_resources();
	क्रम (hose = hose_head; hose; hose = hose->next) अणु
		bus = hose->bus;
		अगर (bus)
			pci_bus_add_devices(bus);
	पूर्ण
पूर्ण

काष्ठा pci_controller * __init
alloc_pci_controller(व्योम)
अणु
	काष्ठा pci_controller *hose;

	hose = memblock_alloc(माप(*hose), SMP_CACHE_BYTES);
	अगर (!hose)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*hose));

	*hose_tail = hose;
	hose_tail = &hose->next;

	वापस hose;
पूर्ण

काष्ठा resource * __init
alloc_resource(व्योम)
अणु
	व्योम *ptr = memblock_alloc(माप(काष्ठा resource), SMP_CACHE_BYTES);

	अगर (!ptr)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(काष्ठा resource));

	वापस ptr;
पूर्ण


/* Provide inक्रमmation on locations of various I/O regions in physical
   memory.  Do this on a per-card basis so that we choose the right hose.  */

SYSCALL_DEFINE3(pciconfig_iobase, दीर्घ, which, अचिन्हित दीर्घ, bus,
		अचिन्हित दीर्घ, dfn)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा pci_dev *dev;

	/* from hose or from bus.devfn */
	अगर (which & IOBASE_FROM_HOSE) अणु
		क्रम(hose = hose_head; hose; hose = hose->next) 
			अगर (hose->index == bus) अवरोध;
		अगर (!hose) वापस -ENODEV;
	पूर्ण अन्यथा अणु
		/* Special hook क्रम ISA access.  */
		अगर (bus == 0 && dfn == 0) अणु
			hose = pci_isa_hose;
		पूर्ण अन्यथा अणु
			dev = pci_get_करोमुख्य_bus_and_slot(0, bus, dfn);
			अगर (!dev)
				वापस -ENODEV;
			hose = dev->sysdata;
			pci_dev_put(dev);
		पूर्ण
	पूर्ण

	चयन (which & ~IOBASE_FROM_HOSE) अणु
	हाल IOBASE_HOSE:
		वापस hose->index;
	हाल IOBASE_SPARSE_MEM:
		वापस hose->sparse_mem_base;
	हाल IOBASE_DENSE_MEM:
		वापस hose->dense_mem_base;
	हाल IOBASE_SPARSE_IO:
		वापस hose->sparse_io_base;
	हाल IOBASE_DENSE_IO:
		वापस hose->dense_io_base;
	हाल IOBASE_ROOT_BUS:
		वापस hose->bus->number;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

/* Destroy an __iomem token.  Not copied from lib/iomap.c.  */

व्योम pci_iounmap(काष्ठा pci_dev *dev, व्योम __iomem * addr)
अणु
	अगर (__is_mmio(addr))
		iounmap(addr);
पूर्ण

EXPORT_SYMBOL(pci_iounmap);

/* FIXME: Some boxes have multiple ISA bridges! */
काष्ठा pci_dev *isa_bridge;
EXPORT_SYMBOL(isa_bridge);
