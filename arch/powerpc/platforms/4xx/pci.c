<शैली गुरु>
/*
 * PCI / PCI-X / PCI-Express support क्रम 4xx parts
 *
 * Copyright 2007 Ben. Herrenschmidt <benh@kernel.crashing.org>, IBM Corp.
 *
 * Most PCI Express code is coming from Stefan Roese implementation क्रम
 * arch/ppc in the Denx tree, slightly reworked by me.
 *
 * Copyright 2007 DENX Software Engineering, Stefan Roese <sr@denx.de>
 *
 * Some of that comes itself from a previous implementation क्रम 440SPE only
 * by Roland Dreier:
 *
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 * Roland Dreier <rolandd@cisco.com>
 *
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/dcr-regs.h>
#समावेश <mm/mmu_decl.h>

#समावेश "pci.h"

अटल पूर्णांक dma_offset_set;

#घोषणा U64_TO_U32_LOW(val)	((u32)((val) & 0x00000000ffffffffULL))
#घोषणा U64_TO_U32_HIGH(val)	((u32)((val) >> 32))

#घोषणा RES_TO_U32_LOW(val)	\
	((माप(resource_माप_प्रकार) > माप(u32)) ? U64_TO_U32_LOW(val) : (val))
#घोषणा RES_TO_U32_HIGH(val)	\
	((माप(resource_माप_प्रकार) > माप(u32)) ? U64_TO_U32_HIGH(val) : (0))

अटल अंतरभूत पूर्णांक ppc440spe_revA(व्योम)
अणु
	/* Catch both 440SPe variants, with and without RAID6 support */
        अगर ((mfspr(SPRN_PVR) & 0xffefffff) == 0x53421890)
                वापस 1;
        अन्यथा
                वापस 0;
पूर्ण

अटल व्योम fixup_ppc4xx_pci_bridge(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose;
	पूर्णांक i;

	अगर (dev->devfn != 0 || dev->bus->self != शून्य)
		वापस;

	hose = pci_bus_to_host(dev->bus);
	अगर (hose == शून्य)
		वापस;

	अगर (!of_device_is_compatible(hose->dn, "ibm,plb-pciex") &&
	    !of_device_is_compatible(hose->dn, "ibm,plb-pcix") &&
	    !of_device_is_compatible(hose->dn, "ibm,plb-pci"))
		वापस;

	अगर (of_device_is_compatible(hose->dn, "ibm,plb440epx-pci") ||
		of_device_is_compatible(hose->dn, "ibm,plb440grx-pci")) अणु
		hose->indirect_type |= PPC_INसूचीECT_TYPE_BROKEN_MRM;
	पूर्ण

	/* Hide the PCI host BARs from the kernel as their content करोesn't
	 * fit well in the resource management
	 */
	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		dev->resource[i].start = dev->resource[i].end = 0;
		dev->resource[i].flags = 0;
	पूर्ण

	prपूर्णांकk(KERN_INFO "PCI: Hiding 4xx host bridge resources %s\n",
	       pci_name(dev));
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, fixup_ppc4xx_pci_bridge);

अटल पूर्णांक __init ppc4xx_parse_dma_ranges(काष्ठा pci_controller *hose,
					  व्योम __iomem *reg,
					  काष्ठा resource *res)
अणु
	u64 size;
	स्थिर u32 *ranges;
	पूर्णांक rlen;
	पूर्णांक pna = of_n_addr_cells(hose->dn);
	पूर्णांक np = pna + 5;

	/* Default */
	res->start = 0;
	size = 0x80000000;
	res->end = size - 1;
	res->flags = IORESOURCE_MEM | IORESOURCE_PREFETCH;

	/* Get dma-ranges property */
	ranges = of_get_property(hose->dn, "dma-ranges", &rlen);
	अगर (ranges == शून्य)
		जाओ out;

	/* Walk it */
	जबतक ((rlen -= np * 4) >= 0) अणु
		u32 pci_space = ranges[0];
		u64 pci_addr = of_पढ़ो_number(ranges + 1, 2);
		u64 cpu_addr = of_translate_dma_address(hose->dn, ranges + 3);
		size = of_पढ़ो_number(ranges + pna + 3, 2);
		ranges += np;
		अगर (cpu_addr == OF_BAD_ADDR || size == 0)
			जारी;

		/* We only care about memory */
		अगर ((pci_space & 0x03000000) != 0x02000000)
			जारी;

		/* We currently only support memory at 0, and pci_addr
		 * within 32 bits space
		 */
		अगर (cpu_addr != 0 || pci_addr > 0xffffffff) अणु
			prपूर्णांकk(KERN_WARNING "%pOF: Ignored unsupported dma range"
			       " 0x%016llx...0x%016llx -> 0x%016llx\n",
			       hose->dn,
			       pci_addr, pci_addr + size - 1, cpu_addr);
			जारी;
		पूर्ण

		/* Check अगर not prefetchable */
		अगर (!(pci_space & 0x40000000))
			res->flags &= ~IORESOURCE_PREFETCH;


		/* Use that */
		res->start = pci_addr;
		/* Beware of 32 bits resources */
		अगर (माप(resource_माप_प्रकार) == माप(u32) &&
		    (pci_addr + size) > 0x100000000ull)
			res->end = 0xffffffff;
		अन्यथा
			res->end = res->start + size - 1;
		अवरोध;
	पूर्ण

	/* We only support one global DMA offset */
	अगर (dma_offset_set && pci_dram_offset != res->start) अणु
		prपूर्णांकk(KERN_ERR "%pOF: dma-ranges(s) mismatch\n", hose->dn);
		वापस -ENXIO;
	पूर्ण

	/* Check that we can fit all of memory as we करोn't support
	 * DMA bounce buffers
	 */
	अगर (size < total_memory) अणु
		prपूर्णांकk(KERN_ERR "%pOF: dma-ranges too small "
		       "(size=%llx total_memory=%llx)\n",
		       hose->dn, size, (u64)total_memory);
		वापस -ENXIO;
	पूर्ण

	/* Check we are a घातer of 2 size and that base is a multiple of size*/
	अगर ((size & (size - 1)) != 0  ||
	    (res->start & (size - 1)) != 0) अणु
		prपूर्णांकk(KERN_ERR "%pOF: dma-ranges unaligned\n", hose->dn);
		वापस -ENXIO;
	पूर्ण

	/* Check that we are fully contained within 32 bits space अगर we are not
	 * running on a 460sx or 476fpe which have 64 bit bus addresses.
	 */
	अगर (res->end > 0xffffffff &&
	    !(of_device_is_compatible(hose->dn, "ibm,plb-pciex-460sx")
	      || of_device_is_compatible(hose->dn, "ibm,plb-pciex-476fpe"))) अणु
		prपूर्णांकk(KERN_ERR "%pOF: dma-ranges outside of 32 bits space\n",
		       hose->dn);
		वापस -ENXIO;
	पूर्ण
 out:
	dma_offset_set = 1;
	pci_dram_offset = res->start;
	hose->dma_winकरोw_base_cur = res->start;
	hose->dma_winकरोw_size = resource_size(res);

	prपूर्णांकk(KERN_INFO "4xx PCI DMA offset set to 0x%08lx\n",
	       pci_dram_offset);
	prपूर्णांकk(KERN_INFO "4xx PCI DMA window base to 0x%016llx\n",
	       (अचिन्हित दीर्घ दीर्घ)hose->dma_winकरोw_base_cur);
	prपूर्णांकk(KERN_INFO "DMA window size 0x%016llx\n",
	       (अचिन्हित दीर्घ दीर्घ)hose->dma_winकरोw_size);
	वापस 0;
पूर्ण

/*
 * 4xx PCI 2.x part
 */

अटल पूर्णांक __init ppc4xx_setup_one_pci_PMM(काष्ठा pci_controller	*hose,
					   व्योम __iomem			*reg,
					   u64				plb_addr,
					   u64				pci_addr,
					   u64				size,
					   अचिन्हित पूर्णांक			flags,
					   पूर्णांक				index)
अणु
	u32 ma, pcila, pciha;

	/* Hack warning ! The "old" PCI 2.x cell only let us configure the low
	 * 32-bit of incoming PLB addresses. The top 4 bits of the 36-bit
	 * address are actually hard wired to a value that appears to depend
	 * on the specअगरic SoC. For example, it's 0 on 440EP and 1 on 440EPx.
	 *
	 * The trick here is we just crop those top bits and ignore them when
	 * programming the chip. That means the device-tree has to be right
	 * क्रम the specअगरic part used (we करोn't print a warning if it's wrong
	 * but on the other hand, you'll crash quickly enough), but at least
	 * this code should work whatever the hard coded value is
	 */
	plb_addr &= 0xffffffffull;

	/* Note: Due to the above hack, the test below करोesn't actually test
	 * अगर you address is above 4G, but it tests that address and
	 * (address + size) are both contained in the same 4G
	 */
	अगर ((plb_addr + size) > 0xffffffffull || !is_घातer_of_2(size) ||
	    size < 0x1000 || (plb_addr & (size - 1)) != 0) अणु
		prपूर्णांकk(KERN_WARNING "%pOF: Resource out of range\n", hose->dn);
		वापस -1;
	पूर्ण
	ma = (0xffffffffu << ilog2(size)) | 1;
	अगर (flags & IORESOURCE_PREFETCH)
		ma |= 2;

	pciha = RES_TO_U32_HIGH(pci_addr);
	pcila = RES_TO_U32_LOW(pci_addr);

	ग_लिखोl(plb_addr, reg + PCIL0_PMM0LA + (0x10 * index));
	ग_लिखोl(pcila, reg + PCIL0_PMM0PCILA + (0x10 * index));
	ग_लिखोl(pciha, reg + PCIL0_PMM0PCIHA + (0x10 * index));
	ग_लिखोl(ma, reg + PCIL0_PMM0MA + (0x10 * index));

	वापस 0;
पूर्ण

अटल व्योम __init ppc4xx_configure_pci_PMMs(काष्ठा pci_controller *hose,
					     व्योम __iomem *reg)
अणु
	पूर्णांक i, j, found_isa_hole = 0;

	/* Setup outbound memory winकरोws */
	क्रम (i = j = 0; i < 3; i++) अणु
		काष्ठा resource *res = &hose->mem_resources[i];
		resource_माप_प्रकार offset = hose->mem_offset[i];

		/* we only care about memory winकरोws */
		अगर (!(res->flags & IORESOURCE_MEM))
			जारी;
		अगर (j > 2) अणु
			prपूर्णांकk(KERN_WARNING "%pOF: Too many ranges\n", hose->dn);
			अवरोध;
		पूर्ण

		/* Configure the resource */
		अगर (ppc4xx_setup_one_pci_PMM(hose, reg,
					     res->start,
					     res->start - offset,
					     resource_size(res),
					     res->flags,
					     j) == 0) अणु
			j++;

			/* If the resource PCI address is 0 then we have our
			 * ISA memory hole
			 */
			अगर (res->start == offset)
				found_isa_hole = 1;
		पूर्ण
	पूर्ण

	/* Handle ISA memory hole अगर not alपढ़ोy covered */
	अगर (j <= 2 && !found_isa_hole && hose->isa_mem_size)
		अगर (ppc4xx_setup_one_pci_PMM(hose, reg, hose->isa_mem_phys, 0,
					     hose->isa_mem_size, 0, j) == 0)
			prपूर्णांकk(KERN_INFO "%pOF: Legacy ISA memory support enabled\n",
			       hose->dn);
पूर्ण

अटल व्योम __init ppc4xx_configure_pci_PTMs(काष्ठा pci_controller *hose,
					     व्योम __iomem *reg,
					     स्थिर काष्ठा resource *res)
अणु
	resource_माप_प्रकार size = resource_size(res);
	u32 sa;

	/* Calculate winकरोw size */
	sa = (0xffffffffu << ilog2(size)) | 1;
	sa |= 0x1;

	/* RAM is always at 0 local क्रम now */
	ग_लिखोl(0, reg + PCIL0_PTM1LA);
	ग_लिखोl(sa, reg + PCIL0_PTM1MS);

	/* Map on PCI side */
	early_ग_लिखो_config_dword(hose, hose->first_busno, 0,
				 PCI_BASE_ADDRESS_1, res->start);
	early_ग_लिखो_config_dword(hose, hose->first_busno, 0,
				 PCI_BASE_ADDRESS_2, 0x00000000);
	early_ग_लिखो_config_word(hose, hose->first_busno, 0,
				PCI_COMMAND, 0x0006);
पूर्ण

अटल व्योम __init ppc4xx_probe_pci_bridge(काष्ठा device_node *np)
अणु
	/* NYI */
	काष्ठा resource rsrc_cfg;
	काष्ठा resource rsrc_reg;
	काष्ठा resource dma_winकरोw;
	काष्ठा pci_controller *hose = शून्य;
	व्योम __iomem *reg = शून्य;
	स्थिर पूर्णांक *bus_range;
	पूर्णांक primary = 0;

	/* Check अगर device is enabled */
	अगर (!of_device_is_available(np)) अणु
		prपूर्णांकk(KERN_INFO "%pOF: Port disabled via device-tree\n", np);
		वापस;
	पूर्ण

	/* Fetch config space रेजिस्टरs address */
	अगर (of_address_to_resource(np, 0, &rsrc_cfg)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get PCI config register base !",
		       np);
		वापस;
	पूर्ण
	/* Fetch host bridge पूर्णांकernal रेजिस्टरs address */
	अगर (of_address_to_resource(np, 3, &rsrc_reg)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get PCI internal register base !",
		       np);
		वापस;
	पूर्ण

	/* Check अगर primary bridge */
	अगर (of_get_property(np, "primary", शून्य))
		primary = 1;

	/* Get bus range अगर any */
	bus_range = of_get_property(np, "bus-range", शून्य);

	/* Map रेजिस्टरs */
	reg = ioremap(rsrc_reg.start, resource_size(&rsrc_reg));
	अगर (reg == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't map registers !", np);
		जाओ fail;
	पूर्ण

	/* Allocate the host controller data काष्ठाure */
	hose = pcibios_alloc_controller(np);
	अगर (!hose)
		जाओ fail;

	hose->first_busno = bus_range ? bus_range[0] : 0x0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	/* Setup config space */
	setup_indirect_pci(hose, rsrc_cfg.start, rsrc_cfg.start + 0x4, 0);

	/* Disable all winकरोws */
	ग_लिखोl(0, reg + PCIL0_PMM0MA);
	ग_लिखोl(0, reg + PCIL0_PMM1MA);
	ग_लिखोl(0, reg + PCIL0_PMM2MA);
	ग_लिखोl(0, reg + PCIL0_PTM1MS);
	ग_लिखोl(0, reg + PCIL0_PTM2MS);

	/* Parse outbound mapping resources */
	pci_process_bridge_OF_ranges(hose, np, primary);

	/* Parse inbound mapping resources */
	अगर (ppc4xx_parse_dma_ranges(hose, reg, &dma_winकरोw) != 0)
		जाओ fail;

	/* Configure outbound ranges POMs */
	ppc4xx_configure_pci_PMMs(hose, reg);

	/* Configure inbound ranges PIMs */
	ppc4xx_configure_pci_PTMs(hose, reg, &dma_winकरोw);

	/* We करोn't need the रेजिस्टरs anymore */
	iounmap(reg);
	वापस;

 fail:
	अगर (hose)
		pcibios_मुक्त_controller(hose);
	अगर (reg)
		iounmap(reg);
पूर्ण

/*
 * 4xx PCI-X part
 */

अटल पूर्णांक __init ppc4xx_setup_one_pcix_POM(काष्ठा pci_controller	*hose,
					    व्योम __iomem		*reg,
					    u64				plb_addr,
					    u64				pci_addr,
					    u64				size,
					    अचिन्हित पूर्णांक		flags,
					    पूर्णांक				index)
अणु
	u32 lah, lal, pciah, pcial, sa;

	अगर (!is_घातer_of_2(size) || size < 0x1000 ||
	    (plb_addr & (size - 1)) != 0) अणु
		prपूर्णांकk(KERN_WARNING "%pOF: Resource out of range\n",
		       hose->dn);
		वापस -1;
	पूर्ण

	/* Calculate रेजिस्टर values */
	lah = RES_TO_U32_HIGH(plb_addr);
	lal = RES_TO_U32_LOW(plb_addr);
	pciah = RES_TO_U32_HIGH(pci_addr);
	pcial = RES_TO_U32_LOW(pci_addr);
	sa = (0xffffffffu << ilog2(size)) | 0x1;

	/* Program रेजिस्टर values */
	अगर (index == 0) अणु
		ग_लिखोl(lah, reg + PCIX0_POM0LAH);
		ग_लिखोl(lal, reg + PCIX0_POM0LAL);
		ग_लिखोl(pciah, reg + PCIX0_POM0PCIAH);
		ग_लिखोl(pcial, reg + PCIX0_POM0PCIAL);
		ग_लिखोl(sa, reg + PCIX0_POM0SA);
	पूर्ण अन्यथा अणु
		ग_लिखोl(lah, reg + PCIX0_POM1LAH);
		ग_लिखोl(lal, reg + PCIX0_POM1LAL);
		ग_लिखोl(pciah, reg + PCIX0_POM1PCIAH);
		ग_लिखोl(pcial, reg + PCIX0_POM1PCIAL);
		ग_लिखोl(sa, reg + PCIX0_POM1SA);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init ppc4xx_configure_pcix_POMs(काष्ठा pci_controller *hose,
					      व्योम __iomem *reg)
अणु
	पूर्णांक i, j, found_isa_hole = 0;

	/* Setup outbound memory winकरोws */
	क्रम (i = j = 0; i < 3; i++) अणु
		काष्ठा resource *res = &hose->mem_resources[i];
		resource_माप_प्रकार offset = hose->mem_offset[i];

		/* we only care about memory winकरोws */
		अगर (!(res->flags & IORESOURCE_MEM))
			जारी;
		अगर (j > 1) अणु
			prपूर्णांकk(KERN_WARNING "%pOF: Too many ranges\n", hose->dn);
			अवरोध;
		पूर्ण

		/* Configure the resource */
		अगर (ppc4xx_setup_one_pcix_POM(hose, reg,
					      res->start,
					      res->start - offset,
					      resource_size(res),
					      res->flags,
					      j) == 0) अणु
			j++;

			/* If the resource PCI address is 0 then we have our
			 * ISA memory hole
			 */
			अगर (res->start == offset)
				found_isa_hole = 1;
		पूर्ण
	पूर्ण

	/* Handle ISA memory hole अगर not alपढ़ोy covered */
	अगर (j <= 1 && !found_isa_hole && hose->isa_mem_size)
		अगर (ppc4xx_setup_one_pcix_POM(hose, reg, hose->isa_mem_phys, 0,
					      hose->isa_mem_size, 0, j) == 0)
			prपूर्णांकk(KERN_INFO "%pOF: Legacy ISA memory support enabled\n",
			       hose->dn);
पूर्ण

अटल व्योम __init ppc4xx_configure_pcix_PIMs(काष्ठा pci_controller *hose,
					      व्योम __iomem *reg,
					      स्थिर काष्ठा resource *res,
					      पूर्णांक big_pim,
					      पूर्णांक enable_msi_hole)
अणु
	resource_माप_प्रकार size = resource_size(res);
	u32 sa;

	/* RAM is always at 0 */
	ग_लिखोl(0x00000000, reg + PCIX0_PIM0LAH);
	ग_लिखोl(0x00000000, reg + PCIX0_PIM0LAL);

	/* Calculate winकरोw size */
	sa = (0xffffffffu << ilog2(size)) | 1;
	sa |= 0x1;
	अगर (res->flags & IORESOURCE_PREFETCH)
		sa |= 0x2;
	अगर (enable_msi_hole)
		sa |= 0x4;
	ग_लिखोl(sa, reg + PCIX0_PIM0SA);
	अगर (big_pim)
		ग_लिखोl(0xffffffff, reg + PCIX0_PIM0SAH);

	/* Map on PCI side */
	ग_लिखोl(0x00000000, reg + PCIX0_BAR0H);
	ग_लिखोl(res->start, reg + PCIX0_BAR0L);
	ग_लिखोw(0x0006, reg + PCIX0_COMMAND);
पूर्ण

अटल व्योम __init ppc4xx_probe_pcix_bridge(काष्ठा device_node *np)
अणु
	काष्ठा resource rsrc_cfg;
	काष्ठा resource rsrc_reg;
	काष्ठा resource dma_winकरोw;
	काष्ठा pci_controller *hose = शून्य;
	व्योम __iomem *reg = शून्य;
	स्थिर पूर्णांक *bus_range;
	पूर्णांक big_pim = 0, msi = 0, primary = 0;

	/* Fetch config space रेजिस्टरs address */
	अगर (of_address_to_resource(np, 0, &rsrc_cfg)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get PCI-X config register base !",
		       np);
		वापस;
	पूर्ण
	/* Fetch host bridge पूर्णांकernal रेजिस्टरs address */
	अगर (of_address_to_resource(np, 3, &rsrc_reg)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get PCI-X internal register base !",
		       np);
		वापस;
	पूर्ण

	/* Check अगर it supports large PIMs (440GX) */
	अगर (of_get_property(np, "large-inbound-windows", शून्य))
		big_pim = 1;

	/* Check अगर we should enable MSIs inbound hole */
	अगर (of_get_property(np, "enable-msi-hole", शून्य))
		msi = 1;

	/* Check अगर primary bridge */
	अगर (of_get_property(np, "primary", शून्य))
		primary = 1;

	/* Get bus range अगर any */
	bus_range = of_get_property(np, "bus-range", शून्य);

	/* Map रेजिस्टरs */
	reg = ioremap(rsrc_reg.start, resource_size(&rsrc_reg));
	अगर (reg == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't map registers !", np);
		जाओ fail;
	पूर्ण

	/* Allocate the host controller data काष्ठाure */
	hose = pcibios_alloc_controller(np);
	अगर (!hose)
		जाओ fail;

	hose->first_busno = bus_range ? bus_range[0] : 0x0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	/* Setup config space */
	setup_indirect_pci(hose, rsrc_cfg.start, rsrc_cfg.start + 0x4,
					PPC_INसूचीECT_TYPE_SET_CFG_TYPE);

	/* Disable all winकरोws */
	ग_लिखोl(0, reg + PCIX0_POM0SA);
	ग_लिखोl(0, reg + PCIX0_POM1SA);
	ग_लिखोl(0, reg + PCIX0_POM2SA);
	ग_लिखोl(0, reg + PCIX0_PIM0SA);
	ग_लिखोl(0, reg + PCIX0_PIM1SA);
	ग_लिखोl(0, reg + PCIX0_PIM2SA);
	अगर (big_pim) अणु
		ग_लिखोl(0, reg + PCIX0_PIM0SAH);
		ग_लिखोl(0, reg + PCIX0_PIM2SAH);
	पूर्ण

	/* Parse outbound mapping resources */
	pci_process_bridge_OF_ranges(hose, np, primary);

	/* Parse inbound mapping resources */
	अगर (ppc4xx_parse_dma_ranges(hose, reg, &dma_winकरोw) != 0)
		जाओ fail;

	/* Configure outbound ranges POMs */
	ppc4xx_configure_pcix_POMs(hose, reg);

	/* Configure inbound ranges PIMs */
	ppc4xx_configure_pcix_PIMs(hose, reg, &dma_winकरोw, big_pim, msi);

	/* We करोn't need the रेजिस्टरs anymore */
	iounmap(reg);
	वापस;

 fail:
	अगर (hose)
		pcibios_मुक्त_controller(hose);
	अगर (reg)
		iounmap(reg);
पूर्ण

#अगर_घोषित CONFIG_PPC4xx_PCI_EXPRESS

/*
 * 4xx PCI-Express part
 *
 * We support 3 parts currently based on the compatible property:
 *
 * ibm,plb-pciex-440spe
 * ibm,plb-pciex-405ex
 * ibm,plb-pciex-460ex
 *
 * Anything अन्यथा will be rejected क्रम now as they are all subtly
 * dअगरferent unक्रमtunately.
 *
 */

#घोषणा MAX_PCIE_BUS_MAPPED	0x40

काष्ठा ppc4xx_pciex_port
अणु
	काष्ठा pci_controller	*hose;
	काष्ठा device_node	*node;
	अचिन्हित पूर्णांक		index;
	पूर्णांक			endpoपूर्णांक;
	पूर्णांक			link;
	पूर्णांक			has_ibpre;
	अचिन्हित पूर्णांक		sdr_base;
	dcr_host_t		dcrs;
	काष्ठा resource		cfg_space;
	काष्ठा resource		utl_regs;
	व्योम __iomem		*utl_base;
पूर्ण;

अटल काष्ठा ppc4xx_pciex_port *ppc4xx_pciex_ports;
अटल अचिन्हित पूर्णांक ppc4xx_pciex_port_count;

काष्ठा ppc4xx_pciex_hwops
अणु
	bool want_sdr;
	पूर्णांक (*core_init)(काष्ठा device_node *np);
	पूर्णांक (*port_init_hw)(काष्ठा ppc4xx_pciex_port *port);
	पूर्णांक (*setup_utl)(काष्ठा ppc4xx_pciex_port *port);
	व्योम (*check_link)(काष्ठा ppc4xx_pciex_port *port);
पूर्ण;

अटल काष्ठा ppc4xx_pciex_hwops *ppc4xx_pciex_hwops;

अटल पूर्णांक __init ppc4xx_pciex_रुको_on_sdr(काष्ठा ppc4xx_pciex_port *port,
					   अचिन्हित पूर्णांक sdr_offset,
					   अचिन्हित पूर्णांक mask,
					   अचिन्हित पूर्णांक value,
					   पूर्णांक समयout_ms)
अणु
	u32 val;

	जबतक(समयout_ms--) अणु
		val = mfdcri(SDR0, port->sdr_base + sdr_offset);
		अगर ((val & mask) == value) अणु
			pr_debug("PCIE%d: Wait on SDR %x success with tm %d (%08x)\n",
				 port->index, sdr_offset, समयout_ms, val);
			वापस 0;
		पूर्ण
		msleep(1);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक __init ppc4xx_pciex_port_reset_sdr(काष्ठा ppc4xx_pciex_port *port)
अणु
	/* Wait क्रम reset to complete */
	अगर (ppc4xx_pciex_रुको_on_sdr(port, PESDRn_RCSSTS, 1 << 20, 0, 10)) अणु
		prपूर्णांकk(KERN_WARNING "PCIE%d: PGRST failed\n",
		       port->index);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम __init ppc4xx_pciex_check_link_sdr(काष्ठा ppc4xx_pciex_port *port)
अणु
	prपूर्णांकk(KERN_INFO "PCIE%d: Checking link...\n", port->index);

	/* Check क्रम card presence detect अगर supported, अगर not, just रुको क्रम
	 * link unconditionally.
	 *
	 * note that we करोn't fail अगर there is no link, we just filter out
	 * config space accesses. That way, it will be easier to implement
	 * hotplug later on.
	 */
	अगर (!port->has_ibpre ||
	    !ppc4xx_pciex_रुको_on_sdr(port, PESDRn_LOOP,
				      1 << 28, 1 << 28, 100)) अणु
		prपूर्णांकk(KERN_INFO
		       "PCIE%d: Device detected, waiting for link...\n",
		       port->index);
		अगर (ppc4xx_pciex_रुको_on_sdr(port, PESDRn_LOOP,
					     0x1000, 0x1000, 2000))
			prपूर्णांकk(KERN_WARNING
			       "PCIE%d: Link up failed\n", port->index);
		अन्यथा अणु
			prपूर्णांकk(KERN_INFO
			       "PCIE%d: link is up !\n", port->index);
			port->link = 1;
		पूर्ण
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO "PCIE%d: No device detected.\n", port->index);
पूर्ण

#अगर_घोषित CONFIG_44x

/* Check various reset bits of the 440SPe PCIe core */
अटल पूर्णांक __init ppc440spe_pciex_check_reset(काष्ठा device_node *np)
अणु
	u32 valPE0, valPE1, valPE2;
	पूर्णांक err = 0;

	/* SDR0_PEGPLLLCT1 reset */
	अगर (!(mfdcri(SDR0, PESDR0_PLLLCT1) & 0x01000000)) अणु
		/*
		 * the PCIe core was probably alपढ़ोy initialised
		 * by firmware - let's re-reset RCSSET regs
		 *
		 * -- Shouldn't we also re-reset the whole thing ? -- BenH
		 */
		pr_debug("PCIE: SDR0_PLLLCT1 already reset.\n");
		mtdcri(SDR0, PESDR0_440SPE_RCSSET, 0x01010000);
		mtdcri(SDR0, PESDR1_440SPE_RCSSET, 0x01010000);
		mtdcri(SDR0, PESDR2_440SPE_RCSSET, 0x01010000);
	पूर्ण

	valPE0 = mfdcri(SDR0, PESDR0_440SPE_RCSSET);
	valPE1 = mfdcri(SDR0, PESDR1_440SPE_RCSSET);
	valPE2 = mfdcri(SDR0, PESDR2_440SPE_RCSSET);

	/* SDR0_PExRCSSET rstgu */
	अगर (!(valPE0 & 0x01000000) ||
	    !(valPE1 & 0x01000000) ||
	    !(valPE2 & 0x01000000)) अणु
		prपूर्णांकk(KERN_INFO "PCIE: SDR0_PExRCSSET rstgu error\n");
		err = -1;
	पूर्ण

	/* SDR0_PExRCSSET rstdl */
	अगर (!(valPE0 & 0x00010000) ||
	    !(valPE1 & 0x00010000) ||
	    !(valPE2 & 0x00010000)) अणु
		prपूर्णांकk(KERN_INFO "PCIE: SDR0_PExRCSSET rstdl error\n");
		err = -1;
	पूर्ण

	/* SDR0_PExRCSSET rstpyn */
	अगर ((valPE0 & 0x00001000) ||
	    (valPE1 & 0x00001000) ||
	    (valPE2 & 0x00001000)) अणु
		prपूर्णांकk(KERN_INFO "PCIE: SDR0_PExRCSSET rstpyn error\n");
		err = -1;
	पूर्ण

	/* SDR0_PExRCSSET hldplb */
	अगर ((valPE0 & 0x10000000) ||
	    (valPE1 & 0x10000000) ||
	    (valPE2 & 0x10000000)) अणु
		prपूर्णांकk(KERN_INFO "PCIE: SDR0_PExRCSSET hldplb error\n");
		err = -1;
	पूर्ण

	/* SDR0_PExRCSSET rdy */
	अगर ((valPE0 & 0x00100000) ||
	    (valPE1 & 0x00100000) ||
	    (valPE2 & 0x00100000)) अणु
		prपूर्णांकk(KERN_INFO "PCIE: SDR0_PExRCSSET rdy error\n");
		err = -1;
	पूर्ण

	/* SDR0_PExRCSSET shutकरोwn */
	अगर ((valPE0 & 0x00000100) ||
	    (valPE1 & 0x00000100) ||
	    (valPE2 & 0x00000100)) अणु
		prपूर्णांकk(KERN_INFO "PCIE: SDR0_PExRCSSET shutdown error\n");
		err = -1;
	पूर्ण

	वापस err;
पूर्ण

/* Global PCIe core initializations क्रम 440SPe core */
अटल पूर्णांक __init ppc440spe_pciex_core_init(काष्ठा device_node *np)
अणु
	पूर्णांक समय_out = 20;

	/* Set PLL घड़ी receiver to LVPECL */
	dcri_clrset(SDR0, PESDR0_PLLLCT1, 0, 1 << 28);

	/* Shouldn't we करो all the calibration stuff etc... here ? */
	अगर (ppc440spe_pciex_check_reset(np))
		वापस -ENXIO;

	अगर (!(mfdcri(SDR0, PESDR0_PLLLCT2) & 0x10000)) अणु
		prपूर्णांकk(KERN_INFO "PCIE: PESDR_PLLCT2 resistance calibration "
		       "failed (0x%08x)\n",
		       mfdcri(SDR0, PESDR0_PLLLCT2));
		वापस -1;
	पूर्ण

	/* De-निश्चित reset of PCIe PLL, रुको क्रम lock */
	dcri_clrset(SDR0, PESDR0_PLLLCT1, 1 << 24, 0);
	udelay(3);

	जबतक (समय_out) अणु
		अगर (!(mfdcri(SDR0, PESDR0_PLLLCT3) & 0x10000000)) अणु
			समय_out--;
			udelay(1);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	अगर (!समय_out) अणु
		prपूर्णांकk(KERN_INFO "PCIE: VCO output not locked\n");
		वापस -1;
	पूर्ण

	pr_debug("PCIE initialization OK\n");

	वापस 3;
पूर्ण

अटल पूर्णांक __init ppc440spe_pciex_init_port_hw(काष्ठा ppc4xx_pciex_port *port)
अणु
	u32 val = 1 << 24;

	अगर (port->endpoपूर्णांक)
		val = PTYPE_LEGACY_ENDPOINT << 20;
	अन्यथा
		val = PTYPE_ROOT_PORT << 20;

	अगर (port->index == 0)
		val |= LNKW_X8 << 12;
	अन्यथा
		val |= LNKW_X4 << 12;

	mtdcri(SDR0, port->sdr_base + PESDRn_DLPSET, val);
	mtdcri(SDR0, port->sdr_base + PESDRn_UTLSET1, 0x20222222);
	अगर (ppc440spe_revA())
		mtdcri(SDR0, port->sdr_base + PESDRn_UTLSET2, 0x11000000);
	mtdcri(SDR0, port->sdr_base + PESDRn_440SPE_HSSL0SET1, 0x35000000);
	mtdcri(SDR0, port->sdr_base + PESDRn_440SPE_HSSL1SET1, 0x35000000);
	mtdcri(SDR0, port->sdr_base + PESDRn_440SPE_HSSL2SET1, 0x35000000);
	mtdcri(SDR0, port->sdr_base + PESDRn_440SPE_HSSL3SET1, 0x35000000);
	अगर (port->index == 0) अणु
		mtdcri(SDR0, port->sdr_base + PESDRn_440SPE_HSSL4SET1,
		       0x35000000);
		mtdcri(SDR0, port->sdr_base + PESDRn_440SPE_HSSL5SET1,
		       0x35000000);
		mtdcri(SDR0, port->sdr_base + PESDRn_440SPE_HSSL6SET1,
		       0x35000000);
		mtdcri(SDR0, port->sdr_base + PESDRn_440SPE_HSSL7SET1,
		       0x35000000);
	पूर्ण
	dcri_clrset(SDR0, port->sdr_base + PESDRn_RCSSET,
			(1 << 24) | (1 << 16), 1 << 12);

	वापस ppc4xx_pciex_port_reset_sdr(port);
पूर्ण

अटल पूर्णांक __init ppc440speA_pciex_init_port_hw(काष्ठा ppc4xx_pciex_port *port)
अणु
	वापस ppc440spe_pciex_init_port_hw(port);
पूर्ण

अटल पूर्णांक __init ppc440speB_pciex_init_port_hw(काष्ठा ppc4xx_pciex_port *port)
अणु
	पूर्णांक rc = ppc440spe_pciex_init_port_hw(port);

	port->has_ibpre = 1;

	वापस rc;
पूर्ण

अटल पूर्णांक ppc440speA_pciex_init_utl(काष्ठा ppc4xx_pciex_port *port)
अणु
	/* XXX Check what that value means... I hate magic */
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_SPECIAL, 0x68782800);

	/*
	 * Set buffer allocations and then निश्चित VRB and TXE.
	 */
	out_be32(port->utl_base + PEUTL_OUTTR,   0x08000000);
	out_be32(port->utl_base + PEUTL_INTR,    0x02000000);
	out_be32(port->utl_base + PEUTL_OPDBSZ,  0x10000000);
	out_be32(port->utl_base + PEUTL_PBBSZ,   0x53000000);
	out_be32(port->utl_base + PEUTL_IPHBSZ,  0x08000000);
	out_be32(port->utl_base + PEUTL_IPDBSZ,  0x10000000);
	out_be32(port->utl_base + PEUTL_RCIRQEN, 0x00f00000);
	out_be32(port->utl_base + PEUTL_PCTL,    0x80800066);

	वापस 0;
पूर्ण

अटल पूर्णांक ppc440speB_pciex_init_utl(काष्ठा ppc4xx_pciex_port *port)
अणु
	/* Report CRS to the operating प्रणाली */
	out_be32(port->utl_base + PEUTL_PBCTL,    0x08000000);

	वापस 0;
पूर्ण

अटल काष्ठा ppc4xx_pciex_hwops ppc440speA_pcie_hwops __initdata =
अणु
	.want_sdr	= true,
	.core_init	= ppc440spe_pciex_core_init,
	.port_init_hw	= ppc440speA_pciex_init_port_hw,
	.setup_utl	= ppc440speA_pciex_init_utl,
	.check_link	= ppc4xx_pciex_check_link_sdr,
पूर्ण;

अटल काष्ठा ppc4xx_pciex_hwops ppc440speB_pcie_hwops __initdata =
अणु
	.want_sdr	= true,
	.core_init	= ppc440spe_pciex_core_init,
	.port_init_hw	= ppc440speB_pciex_init_port_hw,
	.setup_utl	= ppc440speB_pciex_init_utl,
	.check_link	= ppc4xx_pciex_check_link_sdr,
पूर्ण;

अटल पूर्णांक __init ppc460ex_pciex_core_init(काष्ठा device_node *np)
अणु
	/* Nothing to करो, वापस 2 ports */
	वापस 2;
पूर्ण

अटल पूर्णांक __init ppc460ex_pciex_init_port_hw(काष्ठा ppc4xx_pciex_port *port)
अणु
	u32 val;
	u32 utlset1;

	अगर (port->endpoपूर्णांक)
		val = PTYPE_LEGACY_ENDPOINT << 20;
	अन्यथा
		val = PTYPE_ROOT_PORT << 20;

	अगर (port->index == 0) अणु
		val |= LNKW_X1 << 12;
		utlset1 = 0x20000000;
	पूर्ण अन्यथा अणु
		val |= LNKW_X4 << 12;
		utlset1 = 0x20101101;
	पूर्ण

	mtdcri(SDR0, port->sdr_base + PESDRn_DLPSET, val);
	mtdcri(SDR0, port->sdr_base + PESDRn_UTLSET1, utlset1);
	mtdcri(SDR0, port->sdr_base + PESDRn_UTLSET2, 0x01210000);

	चयन (port->index) अणु
	हाल 0:
		mtdcri(SDR0, PESDR0_460EX_L0CDRCTL, 0x00003230);
		mtdcri(SDR0, PESDR0_460EX_L0DRV, 0x00000130);
		mtdcri(SDR0, PESDR0_460EX_L0CLK, 0x00000006);

		mtdcri(SDR0, PESDR0_460EX_PHY_CTL_RST,0x10000000);
		अवरोध;

	हाल 1:
		mtdcri(SDR0, PESDR1_460EX_L0CDRCTL, 0x00003230);
		mtdcri(SDR0, PESDR1_460EX_L1CDRCTL, 0x00003230);
		mtdcri(SDR0, PESDR1_460EX_L2CDRCTL, 0x00003230);
		mtdcri(SDR0, PESDR1_460EX_L3CDRCTL, 0x00003230);
		mtdcri(SDR0, PESDR1_460EX_L0DRV, 0x00000130);
		mtdcri(SDR0, PESDR1_460EX_L1DRV, 0x00000130);
		mtdcri(SDR0, PESDR1_460EX_L2DRV, 0x00000130);
		mtdcri(SDR0, PESDR1_460EX_L3DRV, 0x00000130);
		mtdcri(SDR0, PESDR1_460EX_L0CLK, 0x00000006);
		mtdcri(SDR0, PESDR1_460EX_L1CLK, 0x00000006);
		mtdcri(SDR0, PESDR1_460EX_L2CLK, 0x00000006);
		mtdcri(SDR0, PESDR1_460EX_L3CLK, 0x00000006);

		mtdcri(SDR0, PESDR1_460EX_PHY_CTL_RST,0x10000000);
		अवरोध;
	पूर्ण

	mtdcri(SDR0, port->sdr_base + PESDRn_RCSSET,
	       mfdcri(SDR0, port->sdr_base + PESDRn_RCSSET) |
	       (PESDRx_RCSSET_RSTGU | PESDRx_RCSSET_RSTPYN));

	/* Poll क्रम PHY reset */
	/* XXX FIXME add समयout */
	चयन (port->index) अणु
	हाल 0:
		जबतक (!(mfdcri(SDR0, PESDR0_460EX_RSTSTA) & 0x1))
			udelay(10);
		अवरोध;
	हाल 1:
		जबतक (!(mfdcri(SDR0, PESDR1_460EX_RSTSTA) & 0x1))
			udelay(10);
		अवरोध;
	पूर्ण

	mtdcri(SDR0, port->sdr_base + PESDRn_RCSSET,
	       (mfdcri(SDR0, port->sdr_base + PESDRn_RCSSET) &
		~(PESDRx_RCSSET_RSTGU | PESDRx_RCSSET_RSTDL)) |
	       PESDRx_RCSSET_RSTPYN);

	port->has_ibpre = 1;

	वापस ppc4xx_pciex_port_reset_sdr(port);
पूर्ण

अटल पूर्णांक ppc460ex_pciex_init_utl(काष्ठा ppc4xx_pciex_port *port)
अणु
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_SPECIAL, 0x0);

	/*
	 * Set buffer allocations and then निश्चित VRB and TXE.
	 */
	out_be32(port->utl_base + PEUTL_PBCTL,	0x0800000c);
	out_be32(port->utl_base + PEUTL_OUTTR,	0x08000000);
	out_be32(port->utl_base + PEUTL_INTR,	0x02000000);
	out_be32(port->utl_base + PEUTL_OPDBSZ,	0x04000000);
	out_be32(port->utl_base + PEUTL_PBBSZ,	0x00000000);
	out_be32(port->utl_base + PEUTL_IPHBSZ,	0x02000000);
	out_be32(port->utl_base + PEUTL_IPDBSZ,	0x04000000);
	out_be32(port->utl_base + PEUTL_RCIRQEN,0x00f00000);
	out_be32(port->utl_base + PEUTL_PCTL,	0x80800066);

	वापस 0;
पूर्ण

अटल काष्ठा ppc4xx_pciex_hwops ppc460ex_pcie_hwops __initdata =
अणु
	.want_sdr	= true,
	.core_init	= ppc460ex_pciex_core_init,
	.port_init_hw	= ppc460ex_pciex_init_port_hw,
	.setup_utl	= ppc460ex_pciex_init_utl,
	.check_link	= ppc4xx_pciex_check_link_sdr,
पूर्ण;

अटल पूर्णांक __init apm821xx_pciex_core_init(काष्ठा device_node *np)
अणु
	/* Return the number of pcie port */
	वापस 1;
पूर्ण

अटल पूर्णांक __init apm821xx_pciex_init_port_hw(काष्ठा ppc4xx_pciex_port *port)
अणु
	u32 val;

	/*
	 * Do a software reset on PCIe ports.
	 * This code is to fix the issue that pci drivers करोesn't re-assign
	 * bus number क्रम PCIE devices after Uboot
	 * scanned and configured all the buses (eg. PCIE NIC IntelPro/1000
	 * PT quad port, SAS LSI 1064E)
	 */

	mtdcri(SDR0, PESDR0_460EX_PHY_CTL_RST, 0x0);
	mdelay(10);

	अगर (port->endpoपूर्णांक)
		val = PTYPE_LEGACY_ENDPOINT << 20;
	अन्यथा
		val = PTYPE_ROOT_PORT << 20;

	val |= LNKW_X1 << 12;

	mtdcri(SDR0, port->sdr_base + PESDRn_DLPSET, val);
	mtdcri(SDR0, port->sdr_base + PESDRn_UTLSET1, 0x00000000);
	mtdcri(SDR0, port->sdr_base + PESDRn_UTLSET2, 0x01010000);

	mtdcri(SDR0, PESDR0_460EX_L0CDRCTL, 0x00003230);
	mtdcri(SDR0, PESDR0_460EX_L0DRV, 0x00000130);
	mtdcri(SDR0, PESDR0_460EX_L0CLK, 0x00000006);

	mtdcri(SDR0, PESDR0_460EX_PHY_CTL_RST, 0x10000000);
	mdelay(50);
	mtdcri(SDR0, PESDR0_460EX_PHY_CTL_RST, 0x30000000);

	mtdcri(SDR0, port->sdr_base + PESDRn_RCSSET,
		mfdcri(SDR0, port->sdr_base + PESDRn_RCSSET) |
		(PESDRx_RCSSET_RSTGU | PESDRx_RCSSET_RSTPYN));

	/* Poll क्रम PHY reset */
	val = PESDR0_460EX_RSTSTA - port->sdr_base;
	अगर (ppc4xx_pciex_रुको_on_sdr(port, val, 0x1, 1,	100)) अणु
		prपूर्णांकk(KERN_WARNING "%s: PCIE: Can't reset PHY\n", __func__);
		वापस -EBUSY;
	पूर्ण अन्यथा अणु
		mtdcri(SDR0, port->sdr_base + PESDRn_RCSSET,
			(mfdcri(SDR0, port->sdr_base + PESDRn_RCSSET) &
			~(PESDRx_RCSSET_RSTGU | PESDRx_RCSSET_RSTDL)) |
			PESDRx_RCSSET_RSTPYN);

		port->has_ibpre = 1;
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा ppc4xx_pciex_hwops apm821xx_pcie_hwops __initdata = अणु
	.want_sdr   = true,
	.core_init	= apm821xx_pciex_core_init,
	.port_init_hw	= apm821xx_pciex_init_port_hw,
	.setup_utl	= ppc460ex_pciex_init_utl,
	.check_link = ppc4xx_pciex_check_link_sdr,
पूर्ण;

अटल पूर्णांक __init ppc460sx_pciex_core_init(काष्ठा device_node *np)
अणु
	/* HSS drive amplitude */
	mtdcri(SDR0, PESDR0_460SX_HSSL0DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR0_460SX_HSSL1DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR0_460SX_HSSL2DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR0_460SX_HSSL3DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR0_460SX_HSSL4DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR0_460SX_HSSL5DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR0_460SX_HSSL6DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR0_460SX_HSSL7DAMP, 0xB9843211);

	mtdcri(SDR0, PESDR1_460SX_HSSL0DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR1_460SX_HSSL1DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR1_460SX_HSSL2DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR1_460SX_HSSL3DAMP, 0xB9843211);

	mtdcri(SDR0, PESDR2_460SX_HSSL0DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR2_460SX_HSSL1DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR2_460SX_HSSL2DAMP, 0xB9843211);
	mtdcri(SDR0, PESDR2_460SX_HSSL3DAMP, 0xB9843211);

	/* HSS TX pre-emphasis */
	mtdcri(SDR0, PESDR0_460SX_HSSL0COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR0_460SX_HSSL1COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR0_460SX_HSSL2COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR0_460SX_HSSL3COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR0_460SX_HSSL4COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR0_460SX_HSSL5COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR0_460SX_HSSL6COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR0_460SX_HSSL7COEFA, 0xDCB98987);

	mtdcri(SDR0, PESDR1_460SX_HSSL0COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR1_460SX_HSSL1COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR1_460SX_HSSL2COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR1_460SX_HSSL3COEFA, 0xDCB98987);

	mtdcri(SDR0, PESDR2_460SX_HSSL0COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR2_460SX_HSSL1COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR2_460SX_HSSL2COEFA, 0xDCB98987);
	mtdcri(SDR0, PESDR2_460SX_HSSL3COEFA, 0xDCB98987);

	/* HSS TX calibration control */
	mtdcri(SDR0, PESDR0_460SX_HSSL1CALDRV, 0x22222222);
	mtdcri(SDR0, PESDR1_460SX_HSSL1CALDRV, 0x22220000);
	mtdcri(SDR0, PESDR2_460SX_HSSL1CALDRV, 0x22220000);

	/* HSS TX slew control */
	mtdcri(SDR0, PESDR0_460SX_HSSSLEW, 0xFFFFFFFF);
	mtdcri(SDR0, PESDR1_460SX_HSSSLEW, 0xFFFF0000);
	mtdcri(SDR0, PESDR2_460SX_HSSSLEW, 0xFFFF0000);

	/* Set HSS PRBS enabled */
	mtdcri(SDR0, PESDR0_460SX_HSSCTLSET, 0x00001130);
	mtdcri(SDR0, PESDR2_460SX_HSSCTLSET, 0x00001130);

	udelay(100);

	/* De-निश्चित PLLRESET */
	dcri_clrset(SDR0, PESDR0_PLLLCT2, 0x00000100, 0);

	/* Reset DL, UTL, GPL beक्रमe configuration */
	mtdcri(SDR0, PESDR0_460SX_RCSSET,
			PESDRx_RCSSET_RSTDL | PESDRx_RCSSET_RSTGU);
	mtdcri(SDR0, PESDR1_460SX_RCSSET,
			PESDRx_RCSSET_RSTDL | PESDRx_RCSSET_RSTGU);
	mtdcri(SDR0, PESDR2_460SX_RCSSET,
			PESDRx_RCSSET_RSTDL | PESDRx_RCSSET_RSTGU);

	udelay(100);

	/*
	 * If bअगरurcation is not enabled, u-boot would have disabled the
	 * third PCIe port
	 */
	अगर (((mfdcri(SDR0, PESDR1_460SX_HSSCTLSET) & 0x00000001) ==
				0x00000001)) अणु
		prपूर्णांकk(KERN_INFO "PCI: PCIE bifurcation setup successfully.\n");
		prपूर्णांकk(KERN_INFO "PCI: Total 3 PCIE ports are present\n");
		वापस 3;
	पूर्ण

	prपूर्णांकk(KERN_INFO "PCI: Total 2 PCIE ports are present\n");
	वापस 2;
पूर्ण

अटल पूर्णांक __init ppc460sx_pciex_init_port_hw(काष्ठा ppc4xx_pciex_port *port)
अणु

	अगर (port->endpoपूर्णांक)
		dcri_clrset(SDR0, port->sdr_base + PESDRn_UTLSET2,
				0x01000000, 0);
	अन्यथा
		dcri_clrset(SDR0, port->sdr_base + PESDRn_UTLSET2,
				0, 0x01000000);

	dcri_clrset(SDR0, port->sdr_base + PESDRn_RCSSET,
			(PESDRx_RCSSET_RSTGU | PESDRx_RCSSET_RSTDL),
			PESDRx_RCSSET_RSTPYN);

	port->has_ibpre = 1;

	वापस ppc4xx_pciex_port_reset_sdr(port);
पूर्ण

अटल पूर्णांक ppc460sx_pciex_init_utl(काष्ठा ppc4xx_pciex_port *port)
अणु
	/* Max 128 Bytes */
	out_be32 (port->utl_base + PEUTL_PBBSZ,   0x00000000);
	/* Assert VRB and TXE - per datasheet turn off addr validation */
	out_be32(port->utl_base + PEUTL_PCTL,  0x80800000);
	वापस 0;
पूर्ण

अटल व्योम __init ppc460sx_pciex_check_link(काष्ठा ppc4xx_pciex_port *port)
अणु
	व्योम __iomem *mbase;
	पूर्णांक attempt = 50;

	port->link = 0;

	mbase = ioremap(port->cfg_space.start + 0x10000000, 0x1000);
	अगर (mbase == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't map internal config space !",
			port->node);
		वापस;
	पूर्ण

	जबतक (attempt && (0 == (in_le32(mbase + PECFG_460SX_DLLSTA)
			& PECFG_460SX_DLLSTA_LINKUP))) अणु
		attempt--;
		mdelay(10);
	पूर्ण
	अगर (attempt)
		port->link = 1;
	iounmap(mbase);
पूर्ण

अटल काष्ठा ppc4xx_pciex_hwops ppc460sx_pcie_hwops __initdata = अणु
	.want_sdr	= true,
	.core_init	= ppc460sx_pciex_core_init,
	.port_init_hw	= ppc460sx_pciex_init_port_hw,
	.setup_utl	= ppc460sx_pciex_init_utl,
	.check_link	= ppc460sx_pciex_check_link,
पूर्ण;

#पूर्ण_अगर /* CONFIG_44x */

#अगर_घोषित CONFIG_40x

अटल पूर्णांक __init ppc405ex_pciex_core_init(काष्ठा device_node *np)
अणु
	/* Nothing to करो, वापस 2 ports */
	वापस 2;
पूर्ण

अटल व्योम ppc405ex_pcie_phy_reset(काष्ठा ppc4xx_pciex_port *port)
अणु
	/* Assert the PE0_PHY reset */
	mtdcri(SDR0, port->sdr_base + PESDRn_RCSSET, 0x01010000);
	msleep(1);

	/* deनिश्चित the PE0_hotreset */
	अगर (port->endpoपूर्णांक)
		mtdcri(SDR0, port->sdr_base + PESDRn_RCSSET, 0x01111000);
	अन्यथा
		mtdcri(SDR0, port->sdr_base + PESDRn_RCSSET, 0x01101000);

	/* poll क्रम phy !reset */
	/* XXX FIXME add समयout */
	जबतक (!(mfdcri(SDR0, port->sdr_base + PESDRn_405EX_PHYSTA) & 0x00001000))
		;

	/* deनिश्चित the PE0_gpl_utl_reset */
	mtdcri(SDR0, port->sdr_base + PESDRn_RCSSET, 0x00101000);
पूर्ण

अटल पूर्णांक __init ppc405ex_pciex_init_port_hw(काष्ठा ppc4xx_pciex_port *port)
अणु
	u32 val;

	अगर (port->endpoपूर्णांक)
		val = PTYPE_LEGACY_ENDPOINT;
	अन्यथा
		val = PTYPE_ROOT_PORT;

	mtdcri(SDR0, port->sdr_base + PESDRn_DLPSET,
	       1 << 24 | val << 20 | LNKW_X1 << 12);

	mtdcri(SDR0, port->sdr_base + PESDRn_UTLSET1, 0x00000000);
	mtdcri(SDR0, port->sdr_base + PESDRn_UTLSET2, 0x01010000);
	mtdcri(SDR0, port->sdr_base + PESDRn_405EX_PHYSET1, 0x720F0000);
	mtdcri(SDR0, port->sdr_base + PESDRn_405EX_PHYSET2, 0x70600003);

	/*
	 * Only reset the PHY when no link is currently established.
	 * This is क्रम the Atheros PCIe board which has problems to establish
	 * the link (again) after this PHY reset. All other currently tested
	 * PCIe boards करोn't show this problem.
	 * This has to be re-tested and fixed in a later release!
	 */
	val = mfdcri(SDR0, port->sdr_base + PESDRn_LOOP);
	अगर (!(val & 0x00001000))
		ppc405ex_pcie_phy_reset(port);

	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_CFG, 0x10000000);  /* guarded on */

	port->has_ibpre = 1;

	वापस ppc4xx_pciex_port_reset_sdr(port);
पूर्ण

अटल पूर्णांक ppc405ex_pciex_init_utl(काष्ठा ppc4xx_pciex_port *port)
अणु
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_SPECIAL, 0x0);

	/*
	 * Set buffer allocations and then निश्चित VRB and TXE.
	 */
	out_be32(port->utl_base + PEUTL_OUTTR,   0x02000000);
	out_be32(port->utl_base + PEUTL_INTR,    0x02000000);
	out_be32(port->utl_base + PEUTL_OPDBSZ,  0x04000000);
	out_be32(port->utl_base + PEUTL_PBBSZ,   0x21000000);
	out_be32(port->utl_base + PEUTL_IPHBSZ,  0x02000000);
	out_be32(port->utl_base + PEUTL_IPDBSZ,  0x04000000);
	out_be32(port->utl_base + PEUTL_RCIRQEN, 0x00f00000);
	out_be32(port->utl_base + PEUTL_PCTL,    0x80800066);

	out_be32(port->utl_base + PEUTL_PBCTL,   0x08000000);

	वापस 0;
पूर्ण

अटल काष्ठा ppc4xx_pciex_hwops ppc405ex_pcie_hwops __initdata =
अणु
	.want_sdr	= true,
	.core_init	= ppc405ex_pciex_core_init,
	.port_init_hw	= ppc405ex_pciex_init_port_hw,
	.setup_utl	= ppc405ex_pciex_init_utl,
	.check_link	= ppc4xx_pciex_check_link_sdr,
पूर्ण;

#पूर्ण_अगर /* CONFIG_40x */

#अगर_घोषित CONFIG_476FPE
अटल पूर्णांक __init ppc_476fpe_pciex_core_init(काष्ठा device_node *np)
अणु
	वापस 4;
पूर्ण

अटल व्योम __init ppc_476fpe_pciex_check_link(काष्ठा ppc4xx_pciex_port *port)
अणु
	u32 समयout_ms = 20;
	u32 val = 0, mask = (PECFG_TLDLP_LNKUP|PECFG_TLDLP_PRESENT);
	व्योम __iomem *mbase = ioremap(port->cfg_space.start + 0x10000000,
	                              0x1000);

	prपूर्णांकk(KERN_INFO "PCIE%d: Checking link...\n", port->index);

	अगर (mbase == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "PCIE%d: failed to get cfg space\n",
		                    port->index);
		वापस;
	पूर्ण

	जबतक (समयout_ms--) अणु
		val = in_le32(mbase + PECFG_TLDLP);

		अगर ((val & mask) == mask)
			अवरोध;
		msleep(10);
	पूर्ण

	अगर (val & PECFG_TLDLP_PRESENT) अणु
		prपूर्णांकk(KERN_INFO "PCIE%d: link is up !\n", port->index);
		port->link = 1;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_WARNING "PCIE%d: Link up failed\n", port->index);

	iounmap(mbase);
पूर्ण

अटल काष्ठा ppc4xx_pciex_hwops ppc_476fpe_pcie_hwops __initdata =
अणु
	.core_init	= ppc_476fpe_pciex_core_init,
	.check_link	= ppc_476fpe_pciex_check_link,
पूर्ण;
#पूर्ण_अगर /* CONFIG_476FPE */

/* Check that the core has been initied and अगर not, करो it */
अटल पूर्णांक __init ppc4xx_pciex_check_core_init(काष्ठा device_node *np)
अणु
	अटल पूर्णांक core_init;
	पूर्णांक count = -ENODEV;

	अगर (core_init++)
		वापस 0;

#अगर_घोषित CONFIG_44x
	अगर (of_device_is_compatible(np, "ibm,plb-pciex-440spe")) अणु
		अगर (ppc440spe_revA())
			ppc4xx_pciex_hwops = &ppc440speA_pcie_hwops;
		अन्यथा
			ppc4xx_pciex_hwops = &ppc440speB_pcie_hwops;
	पूर्ण
	अगर (of_device_is_compatible(np, "ibm,plb-pciex-460ex"))
		ppc4xx_pciex_hwops = &ppc460ex_pcie_hwops;
	अगर (of_device_is_compatible(np, "ibm,plb-pciex-460sx"))
		ppc4xx_pciex_hwops = &ppc460sx_pcie_hwops;
	अगर (of_device_is_compatible(np, "ibm,plb-pciex-apm821xx"))
		ppc4xx_pciex_hwops = &apm821xx_pcie_hwops;
#पूर्ण_अगर /* CONFIG_44x    */
#अगर_घोषित CONFIG_40x
	अगर (of_device_is_compatible(np, "ibm,plb-pciex-405ex"))
		ppc4xx_pciex_hwops = &ppc405ex_pcie_hwops;
#पूर्ण_अगर
#अगर_घोषित CONFIG_476FPE
	अगर (of_device_is_compatible(np, "ibm,plb-pciex-476fpe")
		|| of_device_is_compatible(np, "ibm,plb-pciex-476gtr"))
		ppc4xx_pciex_hwops = &ppc_476fpe_pcie_hwops;
#पूर्ण_अगर
	अगर (ppc4xx_pciex_hwops == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "PCIE: unknown host type %pOF\n", np);
		वापस -ENODEV;
	पूर्ण

	count = ppc4xx_pciex_hwops->core_init(np);
	अगर (count > 0) अणु
		ppc4xx_pciex_ports =
		       kसुस्मृति(count, माप(काष्ठा ppc4xx_pciex_port),
			       GFP_KERNEL);
		अगर (ppc4xx_pciex_ports) अणु
			ppc4xx_pciex_port_count = count;
			वापस 0;
		पूर्ण
		prपूर्णांकk(KERN_WARNING "PCIE: failed to allocate ports array\n");
		वापस -ENOMEM;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम __init ppc4xx_pciex_port_init_mapping(काष्ठा ppc4xx_pciex_port *port)
अणु
	/* We map PCI Express configuration based on the reg property */
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_CFGBAH,
		  RES_TO_U32_HIGH(port->cfg_space.start));
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_CFGBAL,
		  RES_TO_U32_LOW(port->cfg_space.start));

	/* XXX FIXME: Use size from reg property. For now, map 512M */
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_CFGMSK, 0xe0000001);

	/* We map UTL रेजिस्टरs based on the reg property */
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_REGBAH,
		  RES_TO_U32_HIGH(port->utl_regs.start));
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_REGBAL,
		  RES_TO_U32_LOW(port->utl_regs.start));

	/* XXX FIXME: Use size from reg property */
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_REGMSK, 0x00007001);

	/* Disable all other outbound winकरोws */
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR1MSKL, 0);
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR2MSKL, 0);
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR3MSKL, 0);
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_MSGMSK, 0);
पूर्ण

अटल पूर्णांक __init ppc4xx_pciex_port_init(काष्ठा ppc4xx_pciex_port *port)
अणु
	पूर्णांक rc = 0;

	/* Init HW */
	अगर (ppc4xx_pciex_hwops->port_init_hw)
		rc = ppc4xx_pciex_hwops->port_init_hw(port);
	अगर (rc != 0)
		वापस rc;

	/*
	 * Initialize mapping: disable all regions and configure
	 * CFG and REG regions based on resources in the device tree
	 */
	ppc4xx_pciex_port_init_mapping(port);

	अगर (ppc4xx_pciex_hwops->check_link)
		ppc4xx_pciex_hwops->check_link(port);

	/*
	 * Map UTL
	 */
	port->utl_base = ioremap(port->utl_regs.start, 0x100);
	BUG_ON(port->utl_base == शून्य);

	/*
	 * Setup UTL रेजिस्टरs --BenH.
	 */
	अगर (ppc4xx_pciex_hwops->setup_utl)
		ppc4xx_pciex_hwops->setup_utl(port);

	/*
	 * Check क्रम VC0 active or PLL Locked and निश्चित RDY.
	 */
	अगर (port->sdr_base) अणु
		अगर (of_device_is_compatible(port->node,
				"ibm,plb-pciex-460sx"))अणु
			अगर (port->link && ppc4xx_pciex_रुको_on_sdr(port,
					PESDRn_RCSSTS,
					1 << 12, 1 << 12, 5000)) अणु
				prपूर्णांकk(KERN_INFO "PCIE%d: PLL not locked\n",
						port->index);
				port->link = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (port->link &&
			ppc4xx_pciex_रुको_on_sdr(port, PESDRn_RCSSTS,
				1 << 16, 1 << 16, 5000)) अणु
			prपूर्णांकk(KERN_INFO "PCIE%d: VC0 not active\n",
					port->index);
			port->link = 0;
		पूर्ण

		dcri_clrset(SDR0, port->sdr_base + PESDRn_RCSSET, 0, 1 << 20);
	पूर्ण

	msleep(100);

	वापस 0;
पूर्ण

अटल पूर्णांक ppc4xx_pciex_validate_bdf(काष्ठा ppc4xx_pciex_port *port,
				     काष्ठा pci_bus *bus,
				     अचिन्हित पूर्णांक devfn)
अणु
	अटल पूर्णांक message;

	/* Endpoपूर्णांक can not generate upstream(remote) config cycles */
	अगर (port->endpoपूर्णांक && bus->number != port->hose->first_busno)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/* Check we are within the mapped range */
	अगर (bus->number > port->hose->last_busno) अणु
		अगर (!message) अणु
			prपूर्णांकk(KERN_WARNING "Warning! Probing bus %u"
			       " out of range !\n", bus->number);
			message++;
		पूर्ण
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	/* The root complex has only one device / function */
	अगर (bus->number == port->hose->first_busno && devfn != 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/* The other side of the RC has only one device as well */
	अगर (bus->number == (port->hose->first_busno + 1) &&
	    PCI_SLOT(devfn) != 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/* Check अगर we have a link */
	अगर ((bus->number != port->hose->first_busno) && !port->link)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस 0;
पूर्ण

अटल व्योम __iomem *ppc4xx_pciex_get_config_base(काष्ठा ppc4xx_pciex_port *port,
						  काष्ठा pci_bus *bus,
						  अचिन्हित पूर्णांक devfn)
अणु
	पूर्णांक relbus;

	/* Remove the casts when we finally हटाओ the stupid अस्थिर
	 * in काष्ठा pci_controller
	 */
	अगर (bus->number == port->hose->first_busno)
		वापस (व्योम __iomem *)port->hose->cfg_addr;

	relbus = bus->number - (port->hose->first_busno + 1);
	वापस (व्योम __iomem *)port->hose->cfg_data +
		((relbus  << 20) | (devfn << 12));
पूर्ण

अटल पूर्णांक ppc4xx_pciex_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	काष्ठा ppc4xx_pciex_port *port =
		&ppc4xx_pciex_ports[hose->indirect_type];
	व्योम __iomem *addr;
	u32 gpl_cfg;

	BUG_ON(hose != port->hose);

	अगर (ppc4xx_pciex_validate_bdf(port, bus, devfn) != 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	addr = ppc4xx_pciex_get_config_base(port, bus, devfn);

	/*
	 * Reading from configuration space of non-existing device can
	 * generate transaction errors. For the पढ़ो duration we suppress
	 * निश्चितion of machine check exceptions to aव्योम those.
	 */
	gpl_cfg = dcr_पढ़ो(port->dcrs, DCRO_PEGPL_CFG);
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_CFG, gpl_cfg | GPL_DMER_MASK_DISA);

	/* Make sure no CRS is recorded */
	out_be32(port->utl_base + PEUTL_RCSTA, 0x00040000);

	चयन (len) अणु
	हाल 1:
		*val = in_8((u8 *)(addr + offset));
		अवरोध;
	हाल 2:
		*val = in_le16((u16 *)(addr + offset));
		अवरोध;
	शेष:
		*val = in_le32((u32 *)(addr + offset));
		अवरोध;
	पूर्ण

	pr_debug("pcie-config-read: bus=%3d [%3d..%3d] devfn=0x%04x"
		 " offset=0x%04x len=%d, addr=0x%p val=0x%08x\n",
		 bus->number, hose->first_busno, hose->last_busno,
		 devfn, offset, len, addr + offset, *val);

	/* Check क्रम CRS (440SPe rev B करोes that क्रम us but heh ..) */
	अगर (in_be32(port->utl_base + PEUTL_RCSTA) & 0x00040000) अणु
		pr_debug("Got CRS !\n");
		अगर (len != 4 || offset != 0)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
		*val = 0xffff0001;
	पूर्ण

	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_CFG, gpl_cfg);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक ppc4xx_pciex_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	काष्ठा ppc4xx_pciex_port *port =
		&ppc4xx_pciex_ports[hose->indirect_type];
	व्योम __iomem *addr;
	u32 gpl_cfg;

	अगर (ppc4xx_pciex_validate_bdf(port, bus, devfn) != 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	addr = ppc4xx_pciex_get_config_base(port, bus, devfn);

	/*
	 * Reading from configuration space of non-existing device can
	 * generate transaction errors. For the पढ़ो duration we suppress
	 * निश्चितion of machine check exceptions to aव्योम those.
	 */
	gpl_cfg = dcr_पढ़ो(port->dcrs, DCRO_PEGPL_CFG);
	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_CFG, gpl_cfg | GPL_DMER_MASK_DISA);

	pr_debug("pcie-config-write: bus=%3d [%3d..%3d] devfn=0x%04x"
		 " offset=0x%04x len=%d, addr=0x%p val=0x%08x\n",
		 bus->number, hose->first_busno, hose->last_busno,
		 devfn, offset, len, addr + offset, val);

	चयन (len) अणु
	हाल 1:
		out_8((u8 *)(addr + offset), val);
		अवरोध;
	हाल 2:
		out_le16((u16 *)(addr + offset), val);
		अवरोध;
	शेष:
		out_le32((u32 *)(addr + offset), val);
		अवरोध;
	पूर्ण

	dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_CFG, gpl_cfg);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops ppc4xx_pciex_pci_ops =
अणु
	.पढ़ो  = ppc4xx_pciex_पढ़ो_config,
	.ग_लिखो = ppc4xx_pciex_ग_लिखो_config,
पूर्ण;

अटल पूर्णांक __init ppc4xx_setup_one_pciex_POM(काष्ठा ppc4xx_pciex_port	*port,
					     काष्ठा pci_controller	*hose,
					     व्योम __iomem		*mbase,
					     u64			plb_addr,
					     u64			pci_addr,
					     u64			size,
					     अचिन्हित पूर्णांक		flags,
					     पूर्णांक			index)
अणु
	u32 lah, lal, pciah, pcial, sa;

	अगर (!is_घातer_of_2(size) ||
	    (index < 2 && size < 0x100000) ||
	    (index == 2 && size < 0x100) ||
	    (plb_addr & (size - 1)) != 0) अणु
		prपूर्णांकk(KERN_WARNING "%pOF: Resource out of range\n", hose->dn);
		वापस -1;
	पूर्ण

	/* Calculate रेजिस्टर values */
	lah = RES_TO_U32_HIGH(plb_addr);
	lal = RES_TO_U32_LOW(plb_addr);
	pciah = RES_TO_U32_HIGH(pci_addr);
	pcial = RES_TO_U32_LOW(pci_addr);
	sa = (0xffffffffu << ilog2(size)) | 0x1;

	/* Program रेजिस्टर values */
	चयन (index) अणु
	हाल 0:
		out_le32(mbase + PECFG_POM0LAH, pciah);
		out_le32(mbase + PECFG_POM0LAL, pcial);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR1BAH, lah);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR1BAL, lal);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR1MSKH, 0x7fffffff);
		/*Enabled and single region */
		अगर (of_device_is_compatible(port->node, "ibm,plb-pciex-460sx"))
			dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR1MSKL,
				sa | DCRO_PEGPL_460SX_OMR1MSKL_UOT
					| DCRO_PEGPL_OMRxMSKL_VAL);
		अन्यथा अगर (of_device_is_compatible(
				port->node, "ibm,plb-pciex-476fpe") ||
			of_device_is_compatible(
				port->node, "ibm,plb-pciex-476gtr"))
			dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR1MSKL,
				sa | DCRO_PEGPL_476FPE_OMR1MSKL_UOT
					| DCRO_PEGPL_OMRxMSKL_VAL);
		अन्यथा
			dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR1MSKL,
				sa | DCRO_PEGPL_OMR1MSKL_UOT
					| DCRO_PEGPL_OMRxMSKL_VAL);
		अवरोध;
	हाल 1:
		out_le32(mbase + PECFG_POM1LAH, pciah);
		out_le32(mbase + PECFG_POM1LAL, pcial);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR2BAH, lah);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR2BAL, lal);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR2MSKH, 0x7fffffff);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR2MSKL,
				sa | DCRO_PEGPL_OMRxMSKL_VAL);
		अवरोध;
	हाल 2:
		out_le32(mbase + PECFG_POM2LAH, pciah);
		out_le32(mbase + PECFG_POM2LAL, pcial);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR3BAH, lah);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR3BAL, lal);
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR3MSKH, 0x7fffffff);
		/* Note that 3 here means enabled | IO space !!! */
		dcr_ग_लिखो(port->dcrs, DCRO_PEGPL_OMR3MSKL,
				sa | DCRO_PEGPL_OMR3MSKL_IO
					| DCRO_PEGPL_OMRxMSKL_VAL);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init ppc4xx_configure_pciex_POMs(काष्ठा ppc4xx_pciex_port *port,
					       काष्ठा pci_controller *hose,
					       व्योम __iomem *mbase)
अणु
	पूर्णांक i, j, found_isa_hole = 0;

	/* Setup outbound memory winकरोws */
	क्रम (i = j = 0; i < 3; i++) अणु
		काष्ठा resource *res = &hose->mem_resources[i];
		resource_माप_प्रकार offset = hose->mem_offset[i];

		/* we only care about memory winकरोws */
		अगर (!(res->flags & IORESOURCE_MEM))
			जारी;
		अगर (j > 1) अणु
			prपूर्णांकk(KERN_WARNING "%pOF: Too many ranges\n",
			       port->node);
			अवरोध;
		पूर्ण

		/* Configure the resource */
		अगर (ppc4xx_setup_one_pciex_POM(port, hose, mbase,
					       res->start,
					       res->start - offset,
					       resource_size(res),
					       res->flags,
					       j) == 0) अणु
			j++;

			/* If the resource PCI address is 0 then we have our
			 * ISA memory hole
			 */
			अगर (res->start == offset)
				found_isa_hole = 1;
		पूर्ण
	पूर्ण

	/* Handle ISA memory hole अगर not alपढ़ोy covered */
	अगर (j <= 1 && !found_isa_hole && hose->isa_mem_size)
		अगर (ppc4xx_setup_one_pciex_POM(port, hose, mbase,
					       hose->isa_mem_phys, 0,
					       hose->isa_mem_size, 0, j) == 0)
			prपूर्णांकk(KERN_INFO "%pOF: Legacy ISA memory support enabled\n",
			       hose->dn);

	/* Configure IO, always 64K starting at 0. We hard wire it to 64K !
	 * Note also that it -has- to be region index 2 on this HW
	 */
	अगर (hose->io_resource.flags & IORESOURCE_IO)
		ppc4xx_setup_one_pciex_POM(port, hose, mbase,
					   hose->io_base_phys, 0,
					   0x10000, IORESOURCE_IO, 2);
पूर्ण

अटल व्योम __init ppc4xx_configure_pciex_PIMs(काष्ठा ppc4xx_pciex_port *port,
					       काष्ठा pci_controller *hose,
					       व्योम __iomem *mbase,
					       काष्ठा resource *res)
अणु
	resource_माप_प्रकार size = resource_size(res);
	u64 sa;

	अगर (port->endpoपूर्णांक) अणु
		resource_माप_प्रकार ep_addr = 0;
		resource_माप_प्रकार ep_size = 32 << 20;

		/* Currently we map a fixed 64MByte winकरोw to PLB address
		 * 0 (SDRAM). This should probably be configurable via a dts
		 * property.
		 */

		/* Calculate winकरोw size */
		sa = (0xffffffffffffffffull << ilog2(ep_size));

		/* Setup BAR0 */
		out_le32(mbase + PECFG_BAR0HMPA, RES_TO_U32_HIGH(sa));
		out_le32(mbase + PECFG_BAR0LMPA, RES_TO_U32_LOW(sa) |
			 PCI_BASE_ADDRESS_MEM_TYPE_64);

		/* Disable BAR1 & BAR2 */
		out_le32(mbase + PECFG_BAR1MPA, 0);
		out_le32(mbase + PECFG_BAR2HMPA, 0);
		out_le32(mbase + PECFG_BAR2LMPA, 0);

		out_le32(mbase + PECFG_PIM01SAH, RES_TO_U32_HIGH(sa));
		out_le32(mbase + PECFG_PIM01SAL, RES_TO_U32_LOW(sa));

		out_le32(mbase + PCI_BASE_ADDRESS_0, RES_TO_U32_LOW(ep_addr));
		out_le32(mbase + PCI_BASE_ADDRESS_1, RES_TO_U32_HIGH(ep_addr));
	पूर्ण अन्यथा अणु
		/* Calculate winकरोw size */
		sa = (0xffffffffffffffffull << ilog2(size));
		अगर (res->flags & IORESOURCE_PREFETCH)
			sa |= PCI_BASE_ADDRESS_MEM_PREFETCH;

		अगर (of_device_is_compatible(port->node, "ibm,plb-pciex-460sx") ||
		    of_device_is_compatible(
			    port->node, "ibm,plb-pciex-476fpe") ||
		    of_device_is_compatible(
			    port->node, "ibm,plb-pciex-476gtr"))
			sa |= PCI_BASE_ADDRESS_MEM_TYPE_64;

		out_le32(mbase + PECFG_BAR0HMPA, RES_TO_U32_HIGH(sa));
		out_le32(mbase + PECFG_BAR0LMPA, RES_TO_U32_LOW(sa));

		/* The setup of the split looks weird to me ... let's see
		 * अगर it works
		 */
		out_le32(mbase + PECFG_PIM0LAL, 0x00000000);
		out_le32(mbase + PECFG_PIM0LAH, 0x00000000);
		out_le32(mbase + PECFG_PIM1LAL, 0x00000000);
		out_le32(mbase + PECFG_PIM1LAH, 0x00000000);
		out_le32(mbase + PECFG_PIM01SAH, 0xffff0000);
		out_le32(mbase + PECFG_PIM01SAL, 0x00000000);

		out_le32(mbase + PCI_BASE_ADDRESS_0, RES_TO_U32_LOW(res->start));
		out_le32(mbase + PCI_BASE_ADDRESS_1, RES_TO_U32_HIGH(res->start));
	पूर्ण

	/* Enable inbound mapping */
	out_le32(mbase + PECFG_PIMEN, 0x1);

	/* Enable I/O, Mem, and Busmaster cycles */
	out_le16(mbase + PCI_COMMAND,
		 in_le16(mbase + PCI_COMMAND) |
		 PCI_COMMAND_IO | PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
पूर्ण

अटल व्योम __init ppc4xx_pciex_port_setup_hose(काष्ठा ppc4xx_pciex_port *port)
अणु
	काष्ठा resource dma_winकरोw;
	काष्ठा pci_controller *hose = शून्य;
	स्थिर पूर्णांक *bus_range;
	पूर्णांक primary = 0, busses;
	व्योम __iomem *mbase = शून्य, *cfg_data = शून्य;
	स्थिर u32 *pval;
	u32 val;

	/* Check अगर primary bridge */
	अगर (of_get_property(port->node, "primary", शून्य))
		primary = 1;

	/* Get bus range अगर any */
	bus_range = of_get_property(port->node, "bus-range", शून्य);

	/* Allocate the host controller data काष्ठाure */
	hose = pcibios_alloc_controller(port->node);
	अगर (!hose)
		जाओ fail;

	/* We stick the port number in "indirect_type" so the config space
	 * ops can retrieve the port data काष्ठाure easily
	 */
	hose->indirect_type = port->index;

	/* Get bus range */
	hose->first_busno = bus_range ? bus_range[0] : 0x0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	/* Because of how big mapping the config space is (1M per bus), we
	 * limit how many busses we support. In the दीर्घ run, we could replace
	 * that with something akin to kmap_atomic instead. We set aside 1 bus
	 * क्रम the host itself too.
	 */
	busses = hose->last_busno - hose->first_busno; /* This is off by 1 */
	अगर (busses > MAX_PCIE_BUS_MAPPED) अणु
		busses = MAX_PCIE_BUS_MAPPED;
		hose->last_busno = hose->first_busno + busses;
	पूर्ण

	अगर (!port->endpoपूर्णांक) अणु
		/* Only map the बाह्यal config space in cfg_data क्रम
		 * PCIe root-complexes. External space is 1M per bus
		 */
		cfg_data = ioremap(port->cfg_space.start +
				   (hose->first_busno + 1) * 0x100000,
				   busses * 0x100000);
		अगर (cfg_data == शून्य) अणु
			prपूर्णांकk(KERN_ERR "%pOF: Can't map external config space !",
			       port->node);
			जाओ fail;
		पूर्ण
		hose->cfg_data = cfg_data;
	पूर्ण

	/* Always map the host config space in cfg_addr.
	 * Internal space is 4K
	 */
	mbase = ioremap(port->cfg_space.start + 0x10000000, 0x1000);
	अगर (mbase == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't map internal config space !",
		       port->node);
		जाओ fail;
	पूर्ण
	hose->cfg_addr = mbase;

	pr_debug("PCIE %pOF, bus %d..%d\n", port->node,
		 hose->first_busno, hose->last_busno);
	pr_debug("     config space mapped at: root @0x%p, other @0x%p\n",
		 hose->cfg_addr, hose->cfg_data);

	/* Setup config space */
	hose->ops = &ppc4xx_pciex_pci_ops;
	port->hose = hose;
	mbase = (व्योम __iomem *)hose->cfg_addr;

	अगर (!port->endpoपूर्णांक) अणु
		/*
		 * Set bus numbers on our root port
		 */
		out_8(mbase + PCI_PRIMARY_BUS, hose->first_busno);
		out_8(mbase + PCI_SECONDARY_BUS, hose->first_busno + 1);
		out_8(mbase + PCI_SUBORDINATE_BUS, hose->last_busno);
	पूर्ण

	/*
	 * OMRs are alपढ़ोy reset, also disable PIMs
	 */
	out_le32(mbase + PECFG_PIMEN, 0);

	/* Parse outbound mapping resources */
	pci_process_bridge_OF_ranges(hose, port->node, primary);

	/* Parse inbound mapping resources */
	अगर (ppc4xx_parse_dma_ranges(hose, mbase, &dma_winकरोw) != 0)
		जाओ fail;

	/* Configure outbound ranges POMs */
	ppc4xx_configure_pciex_POMs(port, hose, mbase);

	/* Configure inbound ranges PIMs */
	ppc4xx_configure_pciex_PIMs(port, hose, mbase, &dma_winकरोw);

	/* The root complex करोesn't show up if we don't set some venकरोr
	 * and device IDs पूर्णांकo it. The शेषs below are the same bogus
	 * one that the initial code in arch/ppc had. This can be
	 * overwritten by setting the "vendor-id/device-id" properties
	 * in the pciex node.
	 */

	/* Get the (optional) venकरोr-/device-id from the device-tree */
	pval = of_get_property(port->node, "vendor-id", शून्य);
	अगर (pval) अणु
		val = *pval;
	पूर्ण अन्यथा अणु
		अगर (!port->endpoपूर्णांक)
			val = 0xaaa0 + port->index;
		अन्यथा
			val = 0xeee0 + port->index;
	पूर्ण
	out_le16(mbase + 0x200, val);

	pval = of_get_property(port->node, "device-id", शून्य);
	अगर (pval) अणु
		val = *pval;
	पूर्ण अन्यथा अणु
		अगर (!port->endpoपूर्णांक)
			val = 0xbed0 + port->index;
		अन्यथा
			val = 0xfed0 + port->index;
	पूर्ण
	out_le16(mbase + 0x202, val);

	/* Enable Bus master, memory, and io space */
	अगर (of_device_is_compatible(port->node, "ibm,plb-pciex-460sx"))
		out_le16(mbase + 0x204, 0x7);

	अगर (!port->endpoपूर्णांक) अणु
		/* Set Class Code to PCI-PCI bridge and Revision Id to 1 */
		out_le32(mbase + 0x208, 0x06040001);

		prपूर्णांकk(KERN_INFO "PCIE%d: successfully set as root-complex\n",
		       port->index);
	पूर्ण अन्यथा अणु
		/* Set Class Code to Processor/PPC */
		out_le32(mbase + 0x208, 0x0b200001);

		prपूर्णांकk(KERN_INFO "PCIE%d: successfully set as endpoint\n",
		       port->index);
	पूर्ण

	वापस;
 fail:
	अगर (hose)
		pcibios_मुक्त_controller(hose);
	अगर (cfg_data)
		iounmap(cfg_data);
	अगर (mbase)
		iounmap(mbase);
पूर्ण

अटल व्योम __init ppc4xx_probe_pciex_bridge(काष्ठा device_node *np)
अणु
	काष्ठा ppc4xx_pciex_port *port;
	स्थिर u32 *pval;
	पूर्णांक portno;
	अचिन्हित पूर्णांक dcrs;

	/* First, proceed to core initialization as we assume there's
	 * only one PCIe core in the प्रणाली
	 */
	अगर (ppc4xx_pciex_check_core_init(np))
		वापस;

	/* Get the port number from the device-tree */
	pval = of_get_property(np, "port", शून्य);
	अगर (pval == शून्य) अणु
		prपूर्णांकk(KERN_ERR "PCIE: Can't find port number for %pOF\n", np);
		वापस;
	पूर्ण
	portno = *pval;
	अगर (portno >= ppc4xx_pciex_port_count) अणु
		prपूर्णांकk(KERN_ERR "PCIE: port number out of range for %pOF\n",
		       np);
		वापस;
	पूर्ण
	port = &ppc4xx_pciex_ports[portno];
	port->index = portno;

	/*
	 * Check अगर device is enabled
	 */
	अगर (!of_device_is_available(np)) अणु
		prपूर्णांकk(KERN_INFO "PCIE%d: Port disabled via device-tree\n", port->index);
		वापस;
	पूर्ण

	port->node = of_node_get(np);
	अगर (ppc4xx_pciex_hwops->want_sdr) अणु
		pval = of_get_property(np, "sdr-base", शून्य);
		अगर (pval == शून्य) अणु
			prपूर्णांकk(KERN_ERR "PCIE: missing sdr-base for %pOF\n",
			       np);
			वापस;
		पूर्ण
		port->sdr_base = *pval;
	पूर्ण

	/* Check अगर device_type property is set to "pci" or "pci-endpoint".
	 * Resulting from this setup this PCIe port will be configured
	 * as root-complex or as endpoपूर्णांक.
	 */
	अगर (of_node_is_type(port->node, "pci-endpoint")) अणु
		port->endpoपूर्णांक = 1;
	पूर्ण अन्यथा अगर (of_node_is_type(port->node, "pci")) अणु
		port->endpoपूर्णांक = 0;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "PCIE: missing or incorrect device_type for %pOF\n",
		       np);
		वापस;
	पूर्ण

	/* Fetch config space रेजिस्टरs address */
	अगर (of_address_to_resource(np, 0, &port->cfg_space)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get PCI-E config space !", np);
		वापस;
	पूर्ण
	/* Fetch host bridge पूर्णांकernal रेजिस्टरs address */
	अगर (of_address_to_resource(np, 1, &port->utl_regs)) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get UTL register base !", np);
		वापस;
	पूर्ण

	/* Map DCRs */
	dcrs = dcr_resource_start(np, 0);
	अगर (dcrs == 0) अणु
		prपूर्णांकk(KERN_ERR "%pOF: Can't get DCR register base !", np);
		वापस;
	पूर्ण
	port->dcrs = dcr_map(np, dcrs, dcr_resource_len(np, 0));

	/* Initialize the port specअगरic रेजिस्टरs */
	अगर (ppc4xx_pciex_port_init(port)) अणु
		prपूर्णांकk(KERN_WARNING "PCIE%d: Port init failed\n", port->index);
		वापस;
	पूर्ण

	/* Setup the linux hose data काष्ठाure */
	ppc4xx_pciex_port_setup_hose(port);
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC4xx_PCI_EXPRESS */

अटल पूर्णांक __init ppc4xx_pci_find_bridges(व्योम)
अणु
	काष्ठा device_node *np;

	pci_add_flags(PCI_ENABLE_PROC_DOMAINS | PCI_COMPAT_DOMAIN_0);

#अगर_घोषित CONFIG_PPC4xx_PCI_EXPRESS
	क्रम_each_compatible_node(np, शून्य, "ibm,plb-pciex")
		ppc4xx_probe_pciex_bridge(np);
#पूर्ण_अगर
	क्रम_each_compatible_node(np, शून्य, "ibm,plb-pcix")
		ppc4xx_probe_pcix_bridge(np);
	क्रम_each_compatible_node(np, शून्य, "ibm,plb-pci")
		ppc4xx_probe_pci_bridge(np);

	वापस 0;
पूर्ण
arch_initcall(ppc4xx_pci_find_bridges);

