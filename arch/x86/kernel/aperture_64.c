<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Firmware replacement code.
 *
 * Work around broken BIOSes that करोn't set an aperture, only set the
 * aperture in the AGP bridge, or set too small aperture.
 *
 * If all fails map the aperture over some low memory.  This is cheaper than
 * करोing bounce buffering. The memory is lost. This is करोne at early boot
 * because only the booपंचांगem allocator can allocate 32+MB.
 *
 * Copyright 2002 Andi Kleen, SuSE Lअसल.
 */
#घोषणा pr_fmt(fmt) "AGP: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kcore.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/pci.h>
#समावेश <linux/bitops.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/gart.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/amd_nb.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <linux/crash_dump.h>

/*
 * Using 512M as goal, in हाल kexec will load kernel_big
 * that will करो the on-position decompress, and could overlap with
 * with the gart aperture that is used.
 * Sequence:
 * kernel_small
 * ==> kexec (with kdump trigger path or gart still enabled)
 * ==> kernel_small (gart area become e820_reserved)
 * ==> kexec (with kdump trigger path or gart still enabled)
 * ==> kerne_big (uncompressed size will be big than 64M or 128M)
 * So करोn't use 512M below as gart iommu, leave the space क्रम kernel
 * code क्रम safe.
 */
#घोषणा GART_MIN_ADDR	(512ULL << 20)
#घोषणा GART_MAX_ADDR	(1ULL   << 32)

पूर्णांक gart_iommu_aperture;
पूर्णांक gart_iommu_aperture_disabled __initdata;
पूर्णांक gart_iommu_aperture_allowed __initdata;

पूर्णांक fallback_aper_order __initdata = 1; /* 64MB */
पूर्णांक fallback_aper_क्रमce __initdata;

पूर्णांक fix_aperture __initdata = 1;

#अगर defined(CONFIG_PROC_VMCORE) || defined(CONFIG_PROC_KCORE)
/*
 * If the first kernel maps the aperture over e820 RAM, the kdump kernel will
 * use the same range because it will reमुख्य configured in the northbridge.
 * Trying to dump this area via /proc/vmcore may crash the machine, so exclude
 * it from vmcore.
 */
अटल अचिन्हित दीर्घ aperture_pfn_start, aperture_page_count;

अटल पूर्णांक gart_mem_pfn_is_ram(अचिन्हित दीर्घ pfn)
अणु
	वापस likely((pfn < aperture_pfn_start) ||
		      (pfn >= aperture_pfn_start + aperture_page_count));
पूर्ण

अटल व्योम __init exclude_from_core(u64 aper_base, u32 aper_order)
अणु
	aperture_pfn_start = aper_base >> PAGE_SHIFT;
	aperture_page_count = (32 * 1024 * 1024) << aper_order >> PAGE_SHIFT;
#अगर_घोषित CONFIG_PROC_VMCORE
	WARN_ON(रेजिस्टर_oldmem_pfn_is_ram(&gart_mem_pfn_is_ram));
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_KCORE
	WARN_ON(रेजिस्टर_mem_pfn_is_ram(&gart_mem_pfn_is_ram));
#पूर्ण_अगर
पूर्ण
#अन्यथा
अटल व्योम exclude_from_core(u64 aper_base, u32 aper_order)
अणु
पूर्ण
#पूर्ण_अगर

/* This code runs beक्रमe the PCI subप्रणाली is initialized, so just
   access the northbridge directly. */

अटल u32 __init allocate_aperture(व्योम)
अणु
	u32 aper_size;
	अचिन्हित दीर्घ addr;

	/* aper_size should <= 1G */
	अगर (fallback_aper_order > 5)
		fallback_aper_order = 5;
	aper_size = (32 * 1024 * 1024) << fallback_aper_order;

	/*
	 * Aperture has to be naturally aligned. This means a 2GB aperture
	 * won't have much chance of finding a place in the lower 4GB of
	 * memory. Unक्रमtunately we cannot move it up because that would
	 * make the IOMMU useless.
	 */
	addr = memblock_find_in_range(GART_MIN_ADDR, GART_MAX_ADDR,
				      aper_size, aper_size);
	अगर (!addr) अणु
		pr_err("Cannot allocate aperture memory hole [mem %#010lx-%#010lx] (%uKB)\n",
		       addr, addr + aper_size - 1, aper_size >> 10);
		वापस 0;
	पूर्ण
	memblock_reserve(addr, aper_size);
	pr_info("Mapping aperture over RAM [mem %#010lx-%#010lx] (%uKB)\n",
		addr, addr + aper_size - 1, aper_size >> 10);
	रेजिस्टर_nosave_region(addr >> PAGE_SHIFT,
			       (addr+aper_size) >> PAGE_SHIFT);

	वापस (u32)addr;
पूर्ण


/* Find a PCI capability */
अटल u32 __init find_cap(पूर्णांक bus, पूर्णांक slot, पूर्णांक func, पूर्णांक cap)
अणु
	पूर्णांक bytes;
	u8 pos;

	अगर (!(पढ़ो_pci_config_16(bus, slot, func, PCI_STATUS) &
						PCI_STATUS_CAP_LIST))
		वापस 0;

	pos = पढ़ो_pci_config_byte(bus, slot, func, PCI_CAPABILITY_LIST);
	क्रम (bytes = 0; bytes < 48 && pos >= 0x40; bytes++) अणु
		u8 id;

		pos &= ~3;
		id = पढ़ो_pci_config_byte(bus, slot, func, pos+PCI_CAP_LIST_ID);
		अगर (id == 0xff)
			अवरोध;
		अगर (id == cap)
			वापस pos;
		pos = पढ़ो_pci_config_byte(bus, slot, func,
						pos+PCI_CAP_LIST_NEXT);
	पूर्ण
	वापस 0;
पूर्ण

/* Read a standard AGPv3 bridge header */
अटल u32 __init पढ़ो_agp(पूर्णांक bus, पूर्णांक slot, पूर्णांक func, पूर्णांक cap, u32 *order)
अणु
	u32 apsize;
	u32 apsizereg;
	पूर्णांक nbits;
	u32 aper_low, aper_hi;
	u64 aper;
	u32 old_order;

	pr_info("pci 0000:%02x:%02x:%02x: AGP bridge\n", bus, slot, func);
	apsizereg = पढ़ो_pci_config_16(bus, slot, func, cap + 0x14);
	अगर (apsizereg == 0xffffffff) अणु
		pr_err("pci 0000:%02x:%02x.%d: APSIZE unreadable\n",
		       bus, slot, func);
		वापस 0;
	पूर्ण

	/* old_order could be the value from NB gart setting */
	old_order = *order;

	apsize = apsizereg & 0xfff;
	/* Some BIOS use weird encodings not in the AGPv3 table. */
	अगर (apsize & 0xff)
		apsize |= 0xf00;
	nbits = hweight16(apsize);
	*order = 7 - nbits;
	अगर ((पूर्णांक)*order < 0) /* < 32MB */
		*order = 0;

	aper_low = पढ़ो_pci_config(bus, slot, func, 0x10);
	aper_hi = पढ़ो_pci_config(bus, slot, func, 0x14);
	aper = (aper_low & ~((1<<22)-1)) | ((u64)aper_hi << 32);

	/*
	 * On some sick chips, APSIZE is 0. It means it wants 4G
	 * so let द्विगुन check that order, and lets trust AMD NB settings:
	 */
	pr_info("pci 0000:%02x:%02x.%d: AGP aperture [bus addr %#010Lx-%#010Lx] (old size %uMB)\n",
		bus, slot, func, aper, aper + (32ULL << (old_order + 20)) - 1,
		32 << old_order);
	अगर (aper + (32ULL<<(20 + *order)) > 0x100000000ULL) अणु
		pr_info("pci 0000:%02x:%02x.%d: AGP aperture size %uMB (APSIZE %#x) is not right, using settings from NB\n",
			bus, slot, func, 32 << *order, apsizereg);
		*order = old_order;
	पूर्ण

	pr_info("pci 0000:%02x:%02x.%d: AGP aperture [bus addr %#010Lx-%#010Lx] (%uMB, APSIZE %#x)\n",
		bus, slot, func, aper, aper + (32ULL << (*order + 20)) - 1,
		32 << *order, apsizereg);

	अगर (!aperture_valid(aper, (32*1024*1024) << *order, 32<<20))
		वापस 0;
	वापस (u32)aper;
पूर्ण

/*
 * Look क्रम an AGP bridge. Winकरोws only expects the aperture in the
 * AGP bridge and some BIOS क्रमget to initialize the Northbridge too.
 * Work around this here.
 *
 * Do an PCI bus scan by hand because we're running beक्रमe the PCI
 * subप्रणाली.
 *
 * All AMD AGP bridges are AGPv3 compliant, so we can करो this scan
 * generically. It's probably overसमाप्त to always scan all slots because
 * the AGP bridges should be always an own bus on the HT hierarchy,
 * but करो it here क्रम future safety.
 */
अटल u32 __init search_agp_bridge(u32 *order, पूर्णांक *valid_agp)
अणु
	पूर्णांक bus, slot, func;

	/* Poor man's PCI discovery */
	क्रम (bus = 0; bus < 256; bus++) अणु
		क्रम (slot = 0; slot < 32; slot++) अणु
			क्रम (func = 0; func < 8; func++) अणु
				u32 class, cap;
				u8 type;
				class = पढ़ो_pci_config(bus, slot, func,
							PCI_CLASS_REVISION);
				अगर (class == 0xffffffff)
					अवरोध;

				चयन (class >> 16) अणु
				हाल PCI_CLASS_BRIDGE_HOST:
				हाल PCI_CLASS_BRIDGE_OTHER: /* needed? */
					/* AGP bridge? */
					cap = find_cap(bus, slot, func,
							PCI_CAP_ID_AGP);
					अगर (!cap)
						अवरोध;
					*valid_agp = 1;
					वापस पढ़ो_agp(bus, slot, func, cap,
							order);
				पूर्ण

				/* No multi-function device? */
				type = पढ़ो_pci_config_byte(bus, slot, func,
							       PCI_HEADER_TYPE);
				अगर (!(type & 0x80))
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	pr_info("No AGP bridge found\n");

	वापस 0;
पूर्ण

अटल bool gart_fix_e820 __initdata = true;

अटल पूर्णांक __init parse_gart_mem(अक्षर *p)
अणु
	वापस kstrtobool(p, &gart_fix_e820);
पूर्ण
early_param("gart_fix_e820", parse_gart_mem);

/*
 * With kexec/kdump, अगर the first kernel करोesn't shut करोwn the GART and the
 * second kernel allocates a dअगरferent GART region, there might be two
 * overlapping GART regions present:
 *
 * - the first still used by the GART initialized in the first kernel.
 * - (sub-)set of it used as normal RAM by the second kernel.
 *
 * which leads to memory corruptions and a kernel panic eventually.
 *
 * This can also happen अगर the BIOS has क्रमgotten to mark the GART region
 * as reserved.
 *
 * Try to update the e820 map to mark that new region as reserved.
 */
व्योम __init early_gart_iommu_check(व्योम)
अणु
	u32 agp_aper_order = 0;
	पूर्णांक i, fix, slot, valid_agp = 0;
	u32 ctl;
	u32 aper_size = 0, aper_order = 0, last_aper_order = 0;
	u64 aper_base = 0, last_aper_base = 0;
	पूर्णांक aper_enabled = 0, last_aper_enabled = 0, last_valid = 0;

	अगर (!amd_gart_present())
		वापस;

	अगर (!early_pci_allowed())
		वापस;

	/* This is mostly duplicate of iommu_hole_init */
	search_agp_bridge(&agp_aper_order, &valid_agp);

	fix = 0;
	क्रम (i = 0; amd_nb_bus_dev_ranges[i].dev_limit; i++) अणु
		पूर्णांक bus;
		पूर्णांक dev_base, dev_limit;

		bus = amd_nb_bus_dev_ranges[i].bus;
		dev_base = amd_nb_bus_dev_ranges[i].dev_base;
		dev_limit = amd_nb_bus_dev_ranges[i].dev_limit;

		क्रम (slot = dev_base; slot < dev_limit; slot++) अणु
			अगर (!early_is_amd_nb(पढ़ो_pci_config(bus, slot, 3, 0x00)))
				जारी;

			ctl = पढ़ो_pci_config(bus, slot, 3, AMD64_GARTAPERTURECTL);
			aper_enabled = ctl & GARTEN;
			aper_order = (ctl >> 1) & 7;
			aper_size = (32 * 1024 * 1024) << aper_order;
			aper_base = पढ़ो_pci_config(bus, slot, 3, AMD64_GARTAPERTUREBASE) & 0x7fff;
			aper_base <<= 25;

			अगर (last_valid) अणु
				अगर ((aper_order != last_aper_order) ||
				    (aper_base != last_aper_base) ||
				    (aper_enabled != last_aper_enabled)) अणु
					fix = 1;
					अवरोध;
				पूर्ण
			पूर्ण

			last_aper_order = aper_order;
			last_aper_base = aper_base;
			last_aper_enabled = aper_enabled;
			last_valid = 1;
		पूर्ण
	पूर्ण

	अगर (!fix && !aper_enabled)
		वापस;

	अगर (!aper_base || !aper_size || aper_base + aper_size > 0x100000000UL)
		fix = 1;

	अगर (gart_fix_e820 && !fix && aper_enabled) अणु
		अगर (e820__mapped_any(aper_base, aper_base + aper_size,
				    E820_TYPE_RAM)) अणु
			/* reserve it, so we can reuse it in second kernel */
			pr_info("e820: reserve [mem %#010Lx-%#010Lx] for GART\n",
				aper_base, aper_base + aper_size - 1);
			e820__range_add(aper_base, aper_size, E820_TYPE_RESERVED);
			e820__update_table_prपूर्णांक();
		पूर्ण
	पूर्ण

	अगर (valid_agp)
		वापस;

	/* disable them all at first */
	क्रम (i = 0; i < amd_nb_bus_dev_ranges[i].dev_limit; i++) अणु
		पूर्णांक bus;
		पूर्णांक dev_base, dev_limit;

		bus = amd_nb_bus_dev_ranges[i].bus;
		dev_base = amd_nb_bus_dev_ranges[i].dev_base;
		dev_limit = amd_nb_bus_dev_ranges[i].dev_limit;

		क्रम (slot = dev_base; slot < dev_limit; slot++) अणु
			अगर (!early_is_amd_nb(पढ़ो_pci_config(bus, slot, 3, 0x00)))
				जारी;

			ctl = पढ़ो_pci_config(bus, slot, 3, AMD64_GARTAPERTURECTL);
			ctl &= ~GARTEN;
			ग_लिखो_pci_config(bus, slot, 3, AMD64_GARTAPERTURECTL, ctl);
		पूर्ण
	पूर्ण

पूर्ण

अटल पूर्णांक __initdata prपूर्णांकed_gart_size_msg;

पूर्णांक __init gart_iommu_hole_init(व्योम)
अणु
	u32 agp_aper_base = 0, agp_aper_order = 0;
	u32 aper_size, aper_alloc = 0, aper_order = 0, last_aper_order = 0;
	u64 aper_base, last_aper_base = 0;
	पूर्णांक fix, slot, valid_agp = 0;
	पूर्णांक i, node;

	अगर (!amd_gart_present())
		वापस -ENODEV;

	अगर (gart_iommu_aperture_disabled || !fix_aperture ||
	    !early_pci_allowed())
		वापस -ENODEV;

	pr_info("Checking aperture...\n");

	अगर (!fallback_aper_क्रमce)
		agp_aper_base = search_agp_bridge(&agp_aper_order, &valid_agp);

	fix = 0;
	node = 0;
	क्रम (i = 0; i < amd_nb_bus_dev_ranges[i].dev_limit; i++) अणु
		पूर्णांक bus;
		पूर्णांक dev_base, dev_limit;
		u32 ctl;

		bus = amd_nb_bus_dev_ranges[i].bus;
		dev_base = amd_nb_bus_dev_ranges[i].dev_base;
		dev_limit = amd_nb_bus_dev_ranges[i].dev_limit;

		क्रम (slot = dev_base; slot < dev_limit; slot++) अणु
			अगर (!early_is_amd_nb(पढ़ो_pci_config(bus, slot, 3, 0x00)))
				जारी;

			iommu_detected = 1;
			gart_iommu_aperture = 1;
			x86_init.iommu.iommu_init = gart_iommu_init;

			ctl = पढ़ो_pci_config(bus, slot, 3,
					      AMD64_GARTAPERTURECTL);

			/*
			 * Beक्रमe we करो anything अन्यथा disable the GART. It may
			 * still be enabled अगर we boot पूर्णांकo a crash-kernel here.
			 * Reconfiguring the GART जबतक it is enabled could have
			 * unknown side-effects.
			 */
			ctl &= ~GARTEN;
			ग_लिखो_pci_config(bus, slot, 3, AMD64_GARTAPERTURECTL, ctl);

			aper_order = (ctl >> 1) & 7;
			aper_size = (32 * 1024 * 1024) << aper_order;
			aper_base = पढ़ो_pci_config(bus, slot, 3, AMD64_GARTAPERTUREBASE) & 0x7fff;
			aper_base <<= 25;

			pr_info("Node %d: aperture [bus addr %#010Lx-%#010Lx] (%uMB)\n",
				node, aper_base, aper_base + aper_size - 1,
				aper_size >> 20);
			node++;

			अगर (!aperture_valid(aper_base, aper_size, 64<<20)) अणु
				अगर (valid_agp && agp_aper_base &&
				    agp_aper_base == aper_base &&
				    agp_aper_order == aper_order) अणु
					/* the same between two setting from NB and agp */
					अगर (!no_iommu &&
					    max_pfn > MAX_DMA32_PFN &&
					    !prपूर्णांकed_gart_size_msg) अणु
						pr_err("you are using iommu with agp, but GART size is less than 64MB\n");
						pr_err("please increase GART size in your BIOS setup\n");
						pr_err("if BIOS doesn't have that option, contact your HW vendor!\n");
						prपूर्णांकed_gart_size_msg = 1;
					पूर्ण
				पूर्ण अन्यथा अणु
					fix = 1;
					जाओ out;
				पूर्ण
			पूर्ण

			अगर ((last_aper_order && aper_order != last_aper_order) ||
			    (last_aper_base && aper_base != last_aper_base)) अणु
				fix = 1;
				जाओ out;
			पूर्ण
			last_aper_order = aper_order;
			last_aper_base = aper_base;
		पूर्ण
	पूर्ण

out:
	अगर (!fix && !fallback_aper_क्रमce) अणु
		अगर (last_aper_base) अणु
			/*
			 * If this is the kdump kernel, the first kernel
			 * may have allocated the range over its e820 RAM
			 * and fixed up the northbridge
			 */
			exclude_from_core(last_aper_base, last_aper_order);

			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (!fallback_aper_क्रमce) अणु
		aper_alloc = agp_aper_base;
		aper_order = agp_aper_order;
	पूर्ण

	अगर (aper_alloc) अणु
		/* Got the aperture from the AGP bridge */
	पूर्ण अन्यथा अगर ((!no_iommu && max_pfn > MAX_DMA32_PFN) ||
		   क्रमce_iommu ||
		   valid_agp ||
		   fallback_aper_क्रमce) अणु
		pr_info("Your BIOS doesn't leave an aperture memory hole\n");
		pr_info("Please enable the IOMMU option in the BIOS setup\n");
		pr_info("This costs you %dMB of RAM\n",
			32 << fallback_aper_order);

		aper_order = fallback_aper_order;
		aper_alloc = allocate_aperture();
		अगर (!aper_alloc) अणु
			/*
			 * Could disable AGP and IOMMU here, but it's
			 * probably not worth it. But the later users
			 * cannot deal with bad apertures and turning
			 * on the aperture over memory causes very
			 * strange problems, so it's better to panic
			 * early.
			 */
			panic("Not enough memory for aperture");
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	/*
	 * If this is the kdump kernel _and_ the first kernel did not
	 * configure the aperture in the northbridge, this range may
	 * overlap with the first kernel's memory. We can't access the
	 * range through vmcore even though it should be part of the dump.
	 */
	exclude_from_core(aper_alloc, aper_order);

	/* Fix up the north bridges */
	क्रम (i = 0; i < amd_nb_bus_dev_ranges[i].dev_limit; i++) अणु
		पूर्णांक bus, dev_base, dev_limit;

		/*
		 * Don't enable translation yet but enable GART IO and CPU
		 * accesses and set DISTLBWALKPRB since GART table memory is UC.
		 */
		u32 ctl = aper_order << 1;

		bus = amd_nb_bus_dev_ranges[i].bus;
		dev_base = amd_nb_bus_dev_ranges[i].dev_base;
		dev_limit = amd_nb_bus_dev_ranges[i].dev_limit;
		क्रम (slot = dev_base; slot < dev_limit; slot++) अणु
			अगर (!early_is_amd_nb(पढ़ो_pci_config(bus, slot, 3, 0x00)))
				जारी;

			ग_लिखो_pci_config(bus, slot, 3, AMD64_GARTAPERTURECTL, ctl);
			ग_लिखो_pci_config(bus, slot, 3, AMD64_GARTAPERTUREBASE, aper_alloc >> 25);
		पूर्ण
	पूर्ण

	set_up_gart_resume(aper_order, aper_alloc);

	वापस 1;
पूर्ण
