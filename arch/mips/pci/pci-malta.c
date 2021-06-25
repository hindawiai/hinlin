<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999, 2000, 2004, 2005	 MIPS Technologies, Inc.
 *	All rights reserved.
 *	Authors: Carsten Langgaard <carstenl@mips.com>
 *		 Maciej W. Rozycki <macro@mips.com>
 *
 * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)
 *
 * MIPS boards specअगरic PCI support.
 */
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/gt64120.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/mips-boards/generic.h>
#समावेश <यंत्र/mips-boards/bonito64.h>
#समावेश <यंत्र/mips-boards/msc01_pci.h>

अटल काष्ठा resource bonito64_mem_resource = अणु
	.name	= "Bonito PCI MEM",
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource bonito64_io_resource = अणु
	.name	= "Bonito PCI I/O",
	.start	= 0x00000000UL,
	.end	= 0x000fffffUL,
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल काष्ठा resource gt64120_mem_resource = अणु
	.name	= "GT-64120 PCI MEM",
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource gt64120_io_resource = अणु
	.name	= "GT-64120 PCI I/O",
	.flags	= IORESOURCE_IO,
पूर्ण;

अटल काष्ठा resource msc_mem_resource = अणु
	.name	= "MSC PCI MEM",
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource msc_io_resource = अणु
	.name	= "MSC PCI I/O",
	.flags	= IORESOURCE_IO,
पूर्ण;

बाह्य काष्ठा pci_ops bonito64_pci_ops;
बाह्य काष्ठा pci_ops gt64xxx_pci0_ops;
बाह्य काष्ठा pci_ops msc_pci_ops;

अटल काष्ठा pci_controller bonito64_controller = अणु
	.pci_ops	= &bonito64_pci_ops,
	.io_resource	= &bonito64_io_resource,
	.mem_resource	= &bonito64_mem_resource,
	.io_offset	= 0x00000000UL,
पूर्ण;

अटल काष्ठा pci_controller gt64120_controller = अणु
	.pci_ops	= &gt64xxx_pci0_ops,
	.io_resource	= &gt64120_io_resource,
	.mem_resource	= &gt64120_mem_resource,
पूर्ण;

अटल काष्ठा pci_controller msc_controller = अणु
	.pci_ops	= &msc_pci_ops,
	.io_resource	= &msc_io_resource,
	.mem_resource	= &msc_mem_resource,
पूर्ण;

व्योम __init mips_pcibios_init(व्योम)
अणु
	काष्ठा pci_controller *controller;
	resource_माप_प्रकार start, end, map, start1, end1, map1, map2, map3, mask;

	चयन (mips_revision_sconid) अणु
	हाल MIPS_REVISION_SCON_GT64120:
		/*
		 * Due to a bug in the Galileo प्रणाली controller, we need
		 * to setup the PCI BAR क्रम the Galileo पूर्णांकernal रेजिस्टरs.
		 * This should be करोne in the bios/bootprom and will be
		 * fixed in a later revision of YAMON (the MIPS boards
		 * boot prom).
		 */
		GT_WRITE(GT_PCI0_CFGADDR_OFS,
			 (0 << GT_PCI0_CFGADDR_BUSNUM_SHF) | /* Local bus */
			 (0 << GT_PCI0_CFGADDR_DEVNUM_SHF) | /* GT64120 dev */
			 (0 << GT_PCI0_CFGADDR_FUNCTNUM_SHF) | /* Function 0*/
			 ((0x20/4) << GT_PCI0_CFGADDR_REGNUM_SHF) | /* BAR 4*/
			 GT_PCI0_CFGADDR_CONFIGEN_BIT);

		/* Perक्रमm the ग_लिखो */
		GT_WRITE(GT_PCI0_CFGDATA_OFS, CPHYSADDR(MIPS_GT_BASE));

		/* Set up resource ranges from the controller's रेजिस्टरs.  */
		start = GT_READ(GT_PCI0M0LD_OFS);
		end = GT_READ(GT_PCI0M0HD_OFS);
		map = GT_READ(GT_PCI0M0REMAP_OFS);
		end = (end & GT_PCI_HD_MSK) | (start & ~GT_PCI_HD_MSK);
		start1 = GT_READ(GT_PCI0M1LD_OFS);
		end1 = GT_READ(GT_PCI0M1HD_OFS);
		map1 = GT_READ(GT_PCI0M1REMAP_OFS);
		end1 = (end1 & GT_PCI_HD_MSK) | (start1 & ~GT_PCI_HD_MSK);
		/* Cannot support multiple winकरोws, use the wider.  */
		अगर (end1 - start1 > end - start) अणु
			start = start1;
			end = end1;
			map = map1;
		पूर्ण
		mask = ~(start ^ end);
		/* We करोn't support remapping with a discontiguous mask.  */
		BUG_ON((start & GT_PCI_HD_MSK) != (map & GT_PCI_HD_MSK) &&
		       mask != ~((mask & -mask) - 1));
		gt64120_mem_resource.start = start;
		gt64120_mem_resource.end = end;
		gt64120_controller.mem_offset = (start & mask) - (map & mask);
		/* Addresses are 36-bit, so करो shअगरts in the destinations.  */
		gt64120_mem_resource.start <<= GT_PCI_DCRM_SHF;
		gt64120_mem_resource.end <<= GT_PCI_DCRM_SHF;
		gt64120_mem_resource.end |= (1 << GT_PCI_DCRM_SHF) - 1;
		gt64120_controller.mem_offset <<= GT_PCI_DCRM_SHF;

		start = GT_READ(GT_PCI0IOLD_OFS);
		end = GT_READ(GT_PCI0IOHD_OFS);
		map = GT_READ(GT_PCI0IOREMAP_OFS);
		end = (end & GT_PCI_HD_MSK) | (start & ~GT_PCI_HD_MSK);
		mask = ~(start ^ end);
		/* We करोn't support remapping with a discontiguous mask.  */
		BUG_ON((start & GT_PCI_HD_MSK) != (map & GT_PCI_HD_MSK) &&
		       mask != ~((mask & -mask) - 1));
		gt64120_io_resource.start = map & mask;
		gt64120_io_resource.end = (map & mask) | ~mask;
		gt64120_controller.io_offset = 0;
		/* Addresses are 36-bit, so करो shअगरts in the destinations.  */
		gt64120_io_resource.start <<= GT_PCI_DCRM_SHF;
		gt64120_io_resource.end <<= GT_PCI_DCRM_SHF;
		gt64120_io_resource.end |= (1 << GT_PCI_DCRM_SHF) - 1;

		controller = &gt64120_controller;
		अवरोध;

	हाल MIPS_REVISION_SCON_BONITO:
		/* Set up resource ranges from the controller's रेजिस्टरs.  */
		map = BONITO_PCIMAP;
		map1 = (BONITO_PCIMAP & BONITO_PCIMAP_PCIMAP_LO0) >>
		       BONITO_PCIMAP_PCIMAP_LO0_SHIFT;
		map2 = (BONITO_PCIMAP & BONITO_PCIMAP_PCIMAP_LO1) >>
		       BONITO_PCIMAP_PCIMAP_LO1_SHIFT;
		map3 = (BONITO_PCIMAP & BONITO_PCIMAP_PCIMAP_LO2) >>
		       BONITO_PCIMAP_PCIMAP_LO2_SHIFT;
		/* Combine as many adjacent winकरोws as possible.  */
		map = map1;
		start = BONITO_PCILO0_BASE;
		end = 1;
		अगर (map3 == map2 + 1) अणु
			map = map2;
			start = BONITO_PCILO1_BASE;
			end++;
		पूर्ण
		अगर (map2 == map1 + 1) अणु
			map = map1;
			start = BONITO_PCILO0_BASE;
			end++;
		पूर्ण
		bonito64_mem_resource.start = start;
		bonito64_mem_resource.end = start +
					    BONITO_PCIMAP_WINBASE(end) - 1;
		bonito64_controller.mem_offset = start -
						 BONITO_PCIMAP_WINBASE(map);

		controller = &bonito64_controller;
		अवरोध;

	हाल MIPS_REVISION_SCON_SOCIT:
	हाल MIPS_REVISION_SCON_ROCIT:
	हाल MIPS_REVISION_SCON_SOCITSC:
	हाल MIPS_REVISION_SCON_SOCITSCP:
		/* Set up resource ranges from the controller's रेजिस्टरs.  */
		MSC_READ(MSC01_PCI_SC2PMBASL, start);
		MSC_READ(MSC01_PCI_SC2PMMSKL, mask);
		MSC_READ(MSC01_PCI_SC2PMMAPL, map);
		msc_mem_resource.start = start & mask;
		msc_mem_resource.end = (start & mask) | ~mask;
		msc_controller.mem_offset = (start & mask) - (map & mask);
		अगर (mips_cps_numiocu(0)) अणु
			ग_लिखो_gcr_reg0_base(start);
			ग_लिखो_gcr_reg0_mask(mask |
					    CM_GCR_REGn_MASK_CMTGT_IOCU0);
		पूर्ण
		MSC_READ(MSC01_PCI_SC2PIOBASL, start);
		MSC_READ(MSC01_PCI_SC2PIOMSKL, mask);
		MSC_READ(MSC01_PCI_SC2PIOMAPL, map);
		msc_io_resource.start = map & mask;
		msc_io_resource.end = (map & mask) | ~mask;
		msc_controller.io_offset = 0;
		ioport_resource.end = ~mask;
		अगर (mips_cps_numiocu(0)) अणु
			ग_लिखो_gcr_reg1_base(start);
			ग_लिखो_gcr_reg1_mask(mask |
					    CM_GCR_REGn_MASK_CMTGT_IOCU0);
		पूर्ण
		/* If ranges overlap I/O takes precedence.  */
		start = start & mask;
		end = start | ~mask;
		अगर ((start >= msc_mem_resource.start &&
		     start <= msc_mem_resource.end) ||
		    (end >= msc_mem_resource.start &&
		     end <= msc_mem_resource.end)) अणु
			/* Use the larger space.  */
			start = max(start, msc_mem_resource.start);
			end = min(end, msc_mem_resource.end);
			अगर (start - msc_mem_resource.start >=
			    msc_mem_resource.end - end)
				msc_mem_resource.end = start - 1;
			अन्यथा
				msc_mem_resource.start = end + 1;
		पूर्ण

		controller = &msc_controller;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* PIIX4 ACPI starts at 0x1000 */
	अगर (controller->io_resource->start < 0x00001000UL)
		controller->io_resource->start = 0x00001000UL;

	iomem_resource.end &= 0xfffffffffULL;			/* 64 GB */
	ioport_resource.end = controller->io_resource->end;

	controller->io_map_base = mips_io_port_base;

	रेजिस्टर_pci_controller(controller);
पूर्ण
