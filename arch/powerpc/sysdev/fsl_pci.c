<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC83xx/85xx/86xx PCI/PCIE support routing.
 *
 * Copyright 2007-2012 Freescale Semiconductor, Inc.
 * Copyright 2008-2009 MontaVista Software, Inc.
 *
 * Initial author: Xianghua Xiao <x.xiao@मुक्तscale.com>
 * Recode: ZHANG WEI <wei.zhang@मुक्तscale.com>
 * Reग_लिखो the routing क्रम Frescale PCI and PCI Express
 * 	Roy Zang <tie-fei.zang@मुक्तscale.com>
 * MPC83xx PCI-Express support:
 * 	Tony Li <tony.li@मुक्तscale.com>
 * 	Anton Vorontsov <avorontsov@ru.mvista.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/fsl/edac.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/log2.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mpc85xx.h>
#समावेश <यंत्र/disassemble.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/swiotlb.h>
#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

अटल पूर्णांक fsl_pcie_bus_fixup, is_mpc83xx_pci;

अटल व्योम quirk_fsl_pcie_early(काष्ठा pci_dev *dev)
अणु
	u8 hdr_type;

	/* अगर we aren't a PCIe don't bother */
	अगर (!pci_is_pcie(dev))
		वापस;

	/* अगर we aren't in host mode don't bother */
	pci_पढ़ो_config_byte(dev, PCI_HEADER_TYPE, &hdr_type);
	अगर ((hdr_type & 0x7f) != PCI_HEADER_TYPE_BRIDGE)
		वापस;

	dev->class = PCI_CLASS_BRIDGE_PCI << 8;
	fsl_pcie_bus_fixup = 1;
	वापस;
पूर्ण

अटल पूर्णांक fsl_indirect_पढ़ो_config(काष्ठा pci_bus *, अचिन्हित पूर्णांक,
				    पूर्णांक, पूर्णांक, u32 *);

अटल पूर्णांक fsl_pcie_check_link(काष्ठा pci_controller *hose)
अणु
	u32 val = 0;

	अगर (hose->indirect_type & PPC_INसूचीECT_TYPE_FSL_CFG_REG_LINK) अणु
		अगर (hose->ops->पढ़ो == fsl_indirect_पढ़ो_config)
			__indirect_पढ़ो_config(hose, hose->first_busno, 0,
					       PCIE_LTSSM, 4, &val);
		अन्यथा
			early_पढ़ो_config_dword(hose, 0, 0, PCIE_LTSSM, &val);
		अगर (val < PCIE_LTSSM_L0)
			वापस 1;
	पूर्ण अन्यथा अणु
		काष्ठा ccsr_pci __iomem *pci = hose->निजी_data;
		/* क्रम PCIe IP rev 3.0 or greater use CSR0 क्रम link state */
		val = (in_be32(&pci->pex_csr0) & PEX_CSR0_LTSSM_MASK)
				>> PEX_CSR0_LTSSM_SHIFT;
		अगर (val != PEX_CSR0_LTSSM_L0)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_indirect_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);

	अगर (fsl_pcie_check_link(hose))
		hose->indirect_type |= PPC_INसूचीECT_TYPE_NO_PCIE_LINK;
	अन्यथा
		hose->indirect_type &= ~PPC_INसूचीECT_TYPE_NO_PCIE_LINK;

	वापस indirect_पढ़ो_config(bus, devfn, offset, len, val);
पूर्ण

#अगर defined(CONFIG_FSL_SOC_BOOKE) || defined(CONFIG_PPC_86xx)

अटल काष्ठा pci_ops fsl_indirect_pcie_ops =
अणु
	.पढ़ो = fsl_indirect_पढ़ो_config,
	.ग_लिखो = indirect_ग_लिखो_config,
पूर्ण;

अटल u64 pci64_dma_offset;

#अगर_घोषित CONFIG_SWIOTLB
अटल व्योम pci_dma_dev_setup_swiotlb(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(pdev->bus);

	pdev->dev.bus_dma_limit =
		hose->dma_winकरोw_base_cur + hose->dma_winकरोw_size - 1;
पूर्ण

अटल व्योम setup_swiotlb_ops(काष्ठा pci_controller *hose)
अणु
	अगर (ppc_swiotlb_enable)
		hose->controller_ops.dma_dev_setup = pci_dma_dev_setup_swiotlb;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम setup_swiotlb_ops(काष्ठा pci_controller *hose) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम fsl_pci_dma_set_mask(काष्ठा device *dev, u64 dma_mask)
अणु
	/*
	 * Fix up PCI devices that are able to DMA to the large inbound
	 * mapping that allows addressing any RAM address from across PCI.
	 */
	अगर (dev_is_pci(dev) && dma_mask >= pci64_dma_offset * 2 - 1) अणु
		dev->bus_dma_limit = 0;
		dev->archdata.dma_offset = pci64_dma_offset;
	पूर्ण
पूर्ण

अटल पूर्णांक setup_one_aपंचांगu(काष्ठा ccsr_pci __iomem *pci,
	अचिन्हित पूर्णांक index, स्थिर काष्ठा resource *res,
	resource_माप_प्रकार offset)
अणु
	resource_माप_प्रकार pci_addr = res->start - offset;
	resource_माप_प्रकार phys_addr = res->start;
	resource_माप_प्रकार size = resource_size(res);
	u32 flags = 0x80044000; /* enable & mem R/W */
	अचिन्हित पूर्णांक i;

	pr_debug("PCI MEM resource start 0x%016llx, size 0x%016llx.\n",
		(u64)res->start, (u64)size);

	अगर (res->flags & IORESOURCE_PREFETCH)
		flags |= 0x10000000; /* enable relaxed ordering */

	क्रम (i = 0; size > 0; i++) अणु
		अचिन्हित पूर्णांक bits = min_t(u32, ilog2(size),
					__ffs(pci_addr | phys_addr));

		अगर (index + i >= 5)
			वापस -1;

		out_be32(&pci->घात[index + i].potar, pci_addr >> 12);
		out_be32(&pci->घात[index + i].potear, (u64)pci_addr >> 44);
		out_be32(&pci->घात[index + i].घातbar, phys_addr >> 12);
		out_be32(&pci->घात[index + i].घातar, flags | (bits - 1));

		pci_addr += (resource_माप_प्रकार)1U << bits;
		phys_addr += (resource_माप_प्रकार)1U << bits;
		size -= (resource_माप_प्रकार)1U << bits;
	पूर्ण

	वापस i;
पूर्ण

अटल bool is_kdump(व्योम)
अणु
	काष्ठा device_node *node;

	node = of_find_node_by_type(शून्य, "memory");
	अगर (!node) अणु
		WARN_ON_ONCE(1);
		वापस false;
	पूर्ण

	वापस of_property_पढ़ो_bool(node, "linux,usable-memory");
पूर्ण

/* aपंचांगu setup क्रम fsl pci/pcie controller */
अटल व्योम setup_pci_aपंचांगu(काष्ठा pci_controller *hose)
अणु
	काष्ठा ccsr_pci __iomem *pci = hose->निजी_data;
	पूर्णांक i, j, n, mem_log, win_idx = 3, start_idx = 1, end_idx = 4;
	u64 mem, sz, paddr_hi = 0;
	u64 offset = 0, paddr_lo = ULदीर्घ_उच्च;
	u32 pcicsrbar = 0, pcicsrbar_sz;
	u32 piwar = PIWAR_EN | PIWAR_PF | PIWAR_TGI_LOCAL |
			PIWAR_READ_SNOOP | PIWAR_WRITE_SNOOP;
	स्थिर u64 *reg;
	पूर्णांक len;
	bool setup_inbound;

	/*
	 * If this is kdump, we करोn't want to trigger a bunch of PCI
	 * errors by closing the winकरोw on in-flight DMA.
	 *
	 * We still run most of the function's logic so that things like
	 * hose->dma_winकरोw_size still get set.
	 */
	setup_inbound = !is_kdump();

	अगर (of_device_is_compatible(hose->dn, "fsl,bsc9132-pcie")) अणु
		/*
		 * BSC9132 Rev1.0 has an issue where all the PEX inbound
		 * winकरोws have implemented the शेष target value as 0xf
		 * क्रम CCSR space.In all Freescale legacy devices the target
		 * of 0xf is reserved क्रम local memory space. 9132 Rev1.0
		 * now has local mempry space mapped to target 0x0 instead of
		 * 0xf. Hence adding a workaround to हटाओ the target 0xf
		 * defined क्रम memory space from Inbound winकरोw attributes.
		 */
		piwar &= ~PIWAR_TGI_LOCAL;
	पूर्ण

	अगर (early_find_capability(hose, 0, 0, PCI_CAP_ID_EXP)) अणु
		अगर (in_be32(&pci->block_rev1) >= PCIE_IP_REV_2_2) अणु
			win_idx = 2;
			start_idx = 0;
			end_idx = 3;
		पूर्ण
	पूर्ण

	/* Disable all winकरोws (except घातar0 since it's ignored) */
	क्रम(i = 1; i < 5; i++)
		out_be32(&pci->घात[i].घातar, 0);

	अगर (setup_inbound) अणु
		क्रम (i = start_idx; i < end_idx; i++)
			out_be32(&pci->piw[i].piwar, 0);
	पूर्ण

	/* Setup outbound MEM winकरोw */
	क्रम(i = 0, j = 1; i < 3; i++) अणु
		अगर (!(hose->mem_resources[i].flags & IORESOURCE_MEM))
			जारी;

		paddr_lo = min(paddr_lo, (u64)hose->mem_resources[i].start);
		paddr_hi = max(paddr_hi, (u64)hose->mem_resources[i].end);

		/* We assume all memory resources have the same offset */
		offset = hose->mem_offset[i];
		n = setup_one_aपंचांगu(pci, j, &hose->mem_resources[i], offset);

		अगर (n < 0 || j >= 5) अणु
			pr_err("Ran out of outbound PCI ATMUs for resource %d!\n", i);
			hose->mem_resources[i].flags |= IORESOURCE_DISABLED;
		पूर्ण अन्यथा
			j += n;
	पूर्ण

	/* Setup outbound IO winकरोw */
	अगर (hose->io_resource.flags & IORESOURCE_IO) अणु
		अगर (j >= 5) अणु
			pr_err("Ran out of outbound PCI ATMUs for IO resource\n");
		पूर्ण अन्यथा अणु
			pr_debug("PCI IO resource start 0x%016llx, size 0x%016llx, "
				 "phy base 0x%016llx.\n",
				 (u64)hose->io_resource.start,
				 (u64)resource_size(&hose->io_resource),
				 (u64)hose->io_base_phys);
			out_be32(&pci->घात[j].potar, (hose->io_resource.start >> 12));
			out_be32(&pci->घात[j].potear, 0);
			out_be32(&pci->घात[j].घातbar, (hose->io_base_phys >> 12));
			/* Enable, IO R/W */
			out_be32(&pci->घात[j].घातar, 0x80088000
				| (ilog2(hose->io_resource.end
				- hose->io_resource.start + 1) - 1));
		पूर्ण
	पूर्ण

	/* convert to pci address space */
	paddr_hi -= offset;
	paddr_lo -= offset;

	अगर (paddr_hi == paddr_lo) अणु
		pr_err("%pOF: No outbound window space\n", hose->dn);
		वापस;
	पूर्ण

	अगर (paddr_lo == 0) अणु
		pr_err("%pOF: No space for inbound window\n", hose->dn);
		वापस;
	पूर्ण

	/* setup PCSRBAR/PEXCSRBAR */
	early_ग_लिखो_config_dword(hose, 0, 0, PCI_BASE_ADDRESS_0, 0xffffffff);
	early_पढ़ो_config_dword(hose, 0, 0, PCI_BASE_ADDRESS_0, &pcicsrbar_sz);
	pcicsrbar_sz = ~pcicsrbar_sz + 1;

	अगर (paddr_hi < (0x100000000ull - pcicsrbar_sz) ||
		(paddr_lo > 0x100000000ull))
		pcicsrbar = 0x100000000ull - pcicsrbar_sz;
	अन्यथा
		pcicsrbar = (paddr_lo - pcicsrbar_sz) & -pcicsrbar_sz;
	early_ग_लिखो_config_dword(hose, 0, 0, PCI_BASE_ADDRESS_0, pcicsrbar);

	paddr_lo = min(paddr_lo, (u64)pcicsrbar);

	pr_info("%pOF: PCICSRBAR @ 0x%x\n", hose->dn, pcicsrbar);

	/* Setup inbound mem winकरोw */
	mem = memblock_end_of_DRAM();
	pr_info("%s: end of DRAM %llx\n", __func__, mem);

	/*
	 * The msi-address-64 property, अगर it exists, indicates the physical
	 * address of the MSIIR रेजिस्टर.  Normally, this रेजिस्टर is located
	 * inside CCSR, so the ATMU that covers all of CCSR is used. But अगर
	 * this property exists, then we normally need to create a new ATMU
	 * क्रम it.  For now, however, we cheat.  The only entity that creates
	 * this property is the Freescale hypervisor, and the address is
	 * specअगरied in the partition configuration.  Typically, the address
	 * is located in the page immediately after the end of DDR.  If so, we
	 * can aव्योम allocating a new ATMU by extending the DDR ATMU by one
	 * page.
	 */
	reg = of_get_property(hose->dn, "msi-address-64", &len);
	अगर (reg && (len == माप(u64))) अणु
		u64 address = be64_to_cpup(reg);

		अगर ((address >= mem) && (address < (mem + PAGE_SIZE))) अणु
			pr_info("%pOF: extending DDR ATMU to cover MSIIR", hose->dn);
			mem += PAGE_SIZE;
		पूर्ण अन्यथा अणु
			/* TODO: Create a new ATMU क्रम MSIIR */
			pr_warn("%pOF: msi-address-64 address of %llx is "
				"unsupported\n", hose->dn, address);
		पूर्ण
	पूर्ण

	sz = min(mem, paddr_lo);
	mem_log = ilog2(sz);

	/* PCIe can overmap inbound & outbound since RX & TX are separated */
	अगर (early_find_capability(hose, 0, 0, PCI_CAP_ID_EXP)) अणु
		/* Size winकरोw to exact size अगर घातer-of-two or one size up */
		अगर ((1ull << mem_log) != mem) अणु
			mem_log++;
			अगर ((1ull << mem_log) > mem)
				pr_info("%pOF: Setting PCI inbound window "
					"greater than memory size\n", hose->dn);
		पूर्ण

		piwar |= ((mem_log - 1) & PIWAR_SZ_MASK);

		अगर (setup_inbound) अणु
			/* Setup inbound memory winकरोw */
			out_be32(&pci->piw[win_idx].pitar,  0x00000000);
			out_be32(&pci->piw[win_idx].piwbar, 0x00000000);
			out_be32(&pci->piw[win_idx].piwar,  piwar);
		पूर्ण

		win_idx--;
		hose->dma_winकरोw_base_cur = 0x00000000;
		hose->dma_winकरोw_size = (resource_माप_प्रकार)sz;

		/*
		 * अगर we have >4G of memory setup second PCI inbound winकरोw to
		 * let devices that are 64-bit address capable to work w/o
		 * SWIOTLB and access the full range of memory
		 */
		अगर (sz != mem) अणु
			mem_log = ilog2(mem);

			/* Size winकरोw up अगर we करोnt fit in exact घातer-of-2 */
			अगर ((1ull << mem_log) != mem)
				mem_log++;

			piwar = (piwar & ~PIWAR_SZ_MASK) | (mem_log - 1);
			pci64_dma_offset = 1ULL << mem_log;

			अगर (setup_inbound) अणु
				/* Setup inbound memory winकरोw */
				out_be32(&pci->piw[win_idx].pitar,  0x00000000);
				out_be32(&pci->piw[win_idx].piwbear,
						pci64_dma_offset >> 44);
				out_be32(&pci->piw[win_idx].piwbar,
						pci64_dma_offset >> 12);
				out_be32(&pci->piw[win_idx].piwar,  piwar);
			पूर्ण

			/*
			 * install our own dma_set_mask handler to fixup dma_ops
			 * and dma_offset
			 */
			ppc_md.dma_set_mask = fsl_pci_dma_set_mask;

			pr_info("%pOF: Setup 64-bit PCI DMA window\n", hose->dn);
		पूर्ण
	पूर्ण अन्यथा अणु
		u64 paddr = 0;

		अगर (setup_inbound) अणु
			/* Setup inbound memory winकरोw */
			out_be32(&pci->piw[win_idx].pitar,  paddr >> 12);
			out_be32(&pci->piw[win_idx].piwbar, paddr >> 12);
			out_be32(&pci->piw[win_idx].piwar,
				 (piwar | (mem_log - 1)));
		पूर्ण

		win_idx--;
		paddr += 1ull << mem_log;
		sz -= 1ull << mem_log;

		अगर (sz) अणु
			mem_log = ilog2(sz);
			piwar |= (mem_log - 1);

			अगर (setup_inbound) अणु
				out_be32(&pci->piw[win_idx].pitar,
					 paddr >> 12);
				out_be32(&pci->piw[win_idx].piwbar,
					 paddr >> 12);
				out_be32(&pci->piw[win_idx].piwar, piwar);
			पूर्ण

			win_idx--;
			paddr += 1ull << mem_log;
		पूर्ण

		hose->dma_winकरोw_base_cur = 0x00000000;
		hose->dma_winकरोw_size = (resource_माप_प्रकार)paddr;
	पूर्ण

	अगर (hose->dma_winकरोw_size < mem) अणु
#अगर_घोषित CONFIG_SWIOTLB
		ppc_swiotlb_enable = 1;
#अन्यथा
		pr_err("%pOF: ERROR: Memory size exceeds PCI ATMU ability to "
			"map - enable CONFIG_SWIOTLB to avoid dma errors.\n",
			 hose->dn);
#पूर्ण_अगर
		/* adjusting outbound winकरोws could reclaim space in mem map */
		अगर (paddr_hi < 0xffffffffull)
			pr_warn("%pOF: WARNING: Outbound window cfg leaves "
				"gaps in memory map. Adjusting the memory map "
				"could reduce unnecessary bounce buffering.\n",
				hose->dn);

		pr_info("%pOF: DMA window size is 0x%llx\n", hose->dn,
			(u64)hose->dma_winकरोw_size);
	पूर्ण
पूर्ण

अटल व्योम setup_pci_cmd(काष्ठा pci_controller *hose)
अणु
	u16 cmd;
	पूर्णांक cap_x;

	early_पढ़ो_config_word(hose, 0, 0, PCI_COMMAND, &cmd);
	cmd |= PCI_COMMAND_SERR | PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY
		| PCI_COMMAND_IO;
	early_ग_लिखो_config_word(hose, 0, 0, PCI_COMMAND, cmd);

	cap_x = early_find_capability(hose, 0, 0, PCI_CAP_ID_PCIX);
	अगर (cap_x) अणु
		पूर्णांक pci_x_cmd = cap_x + PCI_X_CMD;
		cmd = PCI_X_CMD_MAX_SPLIT | PCI_X_CMD_MAX_READ
			| PCI_X_CMD_ERO | PCI_X_CMD_DPERR_E;
		early_ग_लिखो_config_word(hose, 0, 0, pci_x_cmd, cmd);
	पूर्ण अन्यथा अणु
		early_ग_लिखो_config_byte(hose, 0, 0, PCI_LATENCY_TIMER, 0x80);
	पूर्ण
पूर्ण

व्योम fsl_pcibios_fixup_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	पूर्णांक i, is_pcie = 0, no_link;

	/* The root complex bridge comes up with bogus resources,
	 * we copy the PHB ones in.
	 *
	 * With the current generic PCI code, the PHB bus no दीर्घer
	 * has bus->resource[0..4] set, so things are a bit more
	 * tricky.
	 */

	अगर (fsl_pcie_bus_fixup)
		is_pcie = early_find_capability(hose, 0, 0, PCI_CAP_ID_EXP);
	no_link = !!(hose->indirect_type & PPC_INसूचीECT_TYPE_NO_PCIE_LINK);

	अगर (bus->parent == hose->bus && (is_pcie || no_link)) अणु
		क्रम (i = 0; i < PCI_BRIDGE_RESOURCE_NUM; ++i) अणु
			काष्ठा resource *res = bus->resource[i];
			काष्ठा resource *par;

			अगर (!res)
				जारी;
			अगर (i == 0)
				par = &hose->io_resource;
			अन्यथा अगर (i < 4)
				par = &hose->mem_resources[i-1];
			अन्यथा par = शून्य;

			res->start = par ? par->start : 0;
			res->end   = par ? par->end   : 0;
			res->flags = par ? par->flags : 0;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक fsl_add_bridge(काष्ठा platक्रमm_device *pdev, पूर्णांक is_primary)
अणु
	पूर्णांक len;
	काष्ठा pci_controller *hose;
	काष्ठा resource rsrc;
	स्थिर पूर्णांक *bus_range;
	u8 hdr_type, progअगर;
	काष्ठा device_node *dev;
	काष्ठा ccsr_pci __iomem *pci;
	u16 temp;
	u32 svr = mfspr(SPRN_SVR);

	dev = pdev->dev.of_node;

	अगर (!of_device_is_available(dev)) अणु
		pr_warn("%pOF: disabled\n", dev);
		वापस -ENODEV;
	पूर्ण

	pr_debug("Adding PCI host bridge %pOF\n", dev);

	/* Fetch host bridge रेजिस्टरs address */
	अगर (of_address_to_resource(dev, 0, &rsrc)) अणु
		prपूर्णांकk(KERN_WARNING "Can't get pci register base!");
		वापस -ENOMEM;
	पूर्ण

	/* Get bus range अगर any */
	bus_range = of_get_property(dev, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक))
		prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF, assume"
			" bus 0\n", dev);

	pci_add_flags(PCI_REASSIGN_ALL_BUS);
	hose = pcibios_alloc_controller(dev);
	अगर (!hose)
		वापस -ENOMEM;

	/* set platक्रमm device as the parent */
	hose->parent = &pdev->dev;
	hose->first_busno = bus_range ? bus_range[0] : 0x0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	pr_debug("PCI memory map start 0x%016llx, size 0x%016llx\n",
		 (u64)rsrc.start, (u64)resource_size(&rsrc));

	pci = hose->निजी_data = ioremap(rsrc.start, resource_size(&rsrc));
	अगर (!hose->निजी_data)
		जाओ no_bridge;

	setup_indirect_pci(hose, rsrc.start, rsrc.start + 0x4,
			   PPC_INसूचीECT_TYPE_BIG_ENDIAN);

	अगर (in_be32(&pci->block_rev1) < PCIE_IP_REV_3_0)
		hose->indirect_type |= PPC_INसूचीECT_TYPE_FSL_CFG_REG_LINK;

	अगर (early_find_capability(hose, 0, 0, PCI_CAP_ID_EXP)) अणु
		/* use fsl_indirect_पढ़ो_config क्रम PCIe */
		hose->ops = &fsl_indirect_pcie_ops;
		/* For PCIE पढ़ो HEADER_TYPE to identअगरy controller mode */
		early_पढ़ो_config_byte(hose, 0, 0, PCI_HEADER_TYPE, &hdr_type);
		अगर ((hdr_type & 0x7f) != PCI_HEADER_TYPE_BRIDGE)
			जाओ no_bridge;

	पूर्ण अन्यथा अणु
		/* For PCI पढ़ो PROG to identअगरy controller mode */
		early_पढ़ो_config_byte(hose, 0, 0, PCI_CLASS_PROG, &progअगर);
		अगर ((progअगर & 1) &&
		    !of_property_पढ़ो_bool(dev, "fsl,pci-agent-force-enum"))
			जाओ no_bridge;
	पूर्ण

	setup_pci_cmd(hose);

	/* check PCI express link status */
	अगर (early_find_capability(hose, 0, 0, PCI_CAP_ID_EXP)) अणु
		hose->indirect_type |= PPC_INसूचीECT_TYPE_EXT_REG |
			PPC_INसूचीECT_TYPE_SURPRESS_PRIMARY_BUS;
		अगर (fsl_pcie_check_link(hose))
			hose->indirect_type |= PPC_INसूचीECT_TYPE_NO_PCIE_LINK;
	पूर्ण अन्यथा अणु
		/*
		 * Set PBFR(PCI Bus Function Register)[10] = 1 to
		 * disable the combining of crossing cacheline
		 * boundary requests पूर्णांकo one burst transaction.
		 * PCI-X operation is not affected.
		 * Fix erratum PCI 5 on MPC8548
		 */
#घोषणा PCI_BUS_FUNCTION 0x44
#घोषणा PCI_BUS_FUNCTION_MDS 0x400	/* Master disable streaming */
		अगर (((SVR_SOC_VER(svr) == SVR_8543) ||
		     (SVR_SOC_VER(svr) == SVR_8545) ||
		     (SVR_SOC_VER(svr) == SVR_8547) ||
		     (SVR_SOC_VER(svr) == SVR_8548)) &&
		    !early_find_capability(hose, 0, 0, PCI_CAP_ID_PCIX)) अणु
			early_पढ़ो_config_word(hose, 0, 0,
					PCI_BUS_FUNCTION, &temp);
			temp |= PCI_BUS_FUNCTION_MDS;
			early_ग_लिखो_config_word(hose, 0, 0,
					PCI_BUS_FUNCTION, temp);
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_INFO "Found FSL PCI host bridge at 0x%016llx. "
		"Firmware bus number: %d->%d\n",
		(अचिन्हित दीर्घ दीर्घ)rsrc.start, hose->first_busno,
		hose->last_busno);

	pr_debug(" ->Hose at 0x%p, cfg_addr=0x%p,cfg_data=0x%p\n",
		hose, hose->cfg_addr, hose->cfg_data);

	/* Interpret the "ranges" property */
	/* This also maps the I/O region and sets isa_io/mem_base */
	pci_process_bridge_OF_ranges(hose, dev, is_primary);

	/* Setup PEX winकरोw रेजिस्टरs */
	setup_pci_aपंचांगu(hose);

	/* Set up controller operations */
	setup_swiotlb_ops(hose);

	वापस 0;

no_bridge:
	iounmap(hose->निजी_data);
	/* unmap cfg_data & cfg_addr separately अगर not on same page */
	अगर (((अचिन्हित दीर्घ)hose->cfg_data & PAGE_MASK) !=
	    ((अचिन्हित दीर्घ)hose->cfg_addr & PAGE_MASK))
		iounmap(hose->cfg_data);
	iounmap(hose->cfg_addr);
	pcibios_मुक्त_controller(hose);
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_FSL_SOC_BOOKE || CONFIG_PPC_86xx */

DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_FREESCALE, PCI_ANY_ID,
			quirk_fsl_pcie_early);

#अगर defined(CONFIG_PPC_83xx) || defined(CONFIG_PPC_MPC512x)
काष्ठा mpc83xx_pcie_priv अणु
	व्योम __iomem *cfg_type0;
	व्योम __iomem *cfg_type1;
	u32 dev_base;
पूर्ण;

काष्ठा pex_inbound_winकरोw अणु
	u32 ar;
	u32 tar;
	u32 barl;
	u32 barh;
पूर्ण;

/*
 * With the convention of u-boot, the PCIE outbound winकरोw 0 serves
 * as configuration transactions outbound.
 */
#घोषणा PEX_OUTWIN0_BAR		0xCA4
#घोषणा PEX_OUTWIN0_TAL		0xCA8
#घोषणा PEX_OUTWIN0_TAH		0xCAC
#घोषणा PEX_RC_INWIN_BASE	0xE60
#घोषणा PEX_RCIWARn_EN		0x1

अटल पूर्णांक mpc83xx_pcie_exclude_device(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);

	अगर (hose->indirect_type & PPC_INसूचीECT_TYPE_NO_PCIE_LINK)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * Workaround क्रम the HW bug: क्रम Type 0 configure transactions the
	 * PCI-E controller करोes not check the device number bits and just
	 * assumes that the device number bits are 0.
	 */
	अगर (bus->number == hose->first_busno ||
			bus->primary == hose->first_busno) अणु
		अगर (devfn & 0xf8)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	अगर (ppc_md.pci_exclude_device) अणु
		अगर (ppc_md.pci_exclude_device(hose, bus->number, devfn))
			वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल व्योम __iomem *mpc83xx_pcie_remap_cfg(काष्ठा pci_bus *bus,
					    अचिन्हित पूर्णांक devfn, पूर्णांक offset)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	काष्ठा mpc83xx_pcie_priv *pcie = hose->dn->data;
	u32 dev_base = bus->number << 24 | devfn << 16;
	पूर्णांक ret;

	ret = mpc83xx_pcie_exclude_device(bus, devfn);
	अगर (ret)
		वापस शून्य;

	offset &= 0xfff;

	/* Type 0 */
	अगर (bus->number == hose->first_busno)
		वापस pcie->cfg_type0 + offset;

	अगर (pcie->dev_base == dev_base)
		जाओ mapped;

	out_le32(pcie->cfg_type0 + PEX_OUTWIN0_TAL, dev_base);

	pcie->dev_base = dev_base;
mapped:
	वापस pcie->cfg_type1 + offset;
पूर्ण

अटल पूर्णांक mpc83xx_pcie_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);

	/* PPC_INसूचीECT_TYPE_SURPRESS_PRIMARY_BUS */
	अगर (offset == PCI_PRIMARY_BUS && bus->number == hose->first_busno)
		val &= 0xffffff00;

	वापस pci_generic_config_ग_लिखो(bus, devfn, offset, len, val);
पूर्ण

अटल काष्ठा pci_ops mpc83xx_pcie_ops = अणु
	.map_bus = mpc83xx_pcie_remap_cfg,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = mpc83xx_pcie_ग_लिखो_config,
पूर्ण;

अटल पूर्णांक __init mpc83xx_pcie_setup(काष्ठा pci_controller *hose,
				     काष्ठा resource *reg)
अणु
	काष्ठा mpc83xx_pcie_priv *pcie;
	u32 cfg_bar;
	पूर्णांक ret = -ENOMEM;

	pcie = zalloc_maybe_booपंचांगem(माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस ret;

	pcie->cfg_type0 = ioremap(reg->start, resource_size(reg));
	अगर (!pcie->cfg_type0)
		जाओ err0;

	cfg_bar = in_le32(pcie->cfg_type0 + PEX_OUTWIN0_BAR);
	अगर (!cfg_bar) अणु
		/* PCI-E isn't configured. */
		ret = -ENODEV;
		जाओ err1;
	पूर्ण

	pcie->cfg_type1 = ioremap(cfg_bar, 0x1000);
	अगर (!pcie->cfg_type1)
		जाओ err1;

	WARN_ON(hose->dn->data);
	hose->dn->data = pcie;
	hose->ops = &mpc83xx_pcie_ops;
	hose->indirect_type |= PPC_INसूचीECT_TYPE_FSL_CFG_REG_LINK;

	out_le32(pcie->cfg_type0 + PEX_OUTWIN0_TAH, 0);
	out_le32(pcie->cfg_type0 + PEX_OUTWIN0_TAL, 0);

	अगर (fsl_pcie_check_link(hose))
		hose->indirect_type |= PPC_INसूचीECT_TYPE_NO_PCIE_LINK;

	वापस 0;
err1:
	iounmap(pcie->cfg_type0);
err0:
	kमुक्त(pcie);
	वापस ret;

पूर्ण

पूर्णांक __init mpc83xx_add_bridge(काष्ठा device_node *dev)
अणु
	पूर्णांक ret;
	पूर्णांक len;
	काष्ठा pci_controller *hose;
	काष्ठा resource rsrc_reg;
	काष्ठा resource rsrc_cfg;
	स्थिर पूर्णांक *bus_range;
	पूर्णांक primary;

	is_mpc83xx_pci = 1;

	अगर (!of_device_is_available(dev)) अणु
		pr_warn("%pOF: disabled by the firmware.\n",
			dev);
		वापस -ENODEV;
	पूर्ण
	pr_debug("Adding PCI host bridge %pOF\n", dev);

	/* Fetch host bridge रेजिस्टरs address */
	अगर (of_address_to_resource(dev, 0, &rsrc_reg)) अणु
		prपूर्णांकk(KERN_WARNING "Can't get pci register base!\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(&rsrc_cfg, 0, माप(rsrc_cfg));

	अगर (of_address_to_resource(dev, 1, &rsrc_cfg)) अणु
		prपूर्णांकk(KERN_WARNING
			"No pci config register base in dev tree, "
			"using default\n");
		/*
		 * MPC83xx supports up to two host controllers
		 * 	one at 0x8500 has config space रेजिस्टरs at 0x8300
		 * 	one at 0x8600 has config space रेजिस्टरs at 0x8380
		 */
		अगर ((rsrc_reg.start & 0xfffff) == 0x8500)
			rsrc_cfg.start = (rsrc_reg.start & 0xfff00000) + 0x8300;
		अन्यथा अगर ((rsrc_reg.start & 0xfffff) == 0x8600)
			rsrc_cfg.start = (rsrc_reg.start & 0xfff00000) + 0x8380;
	पूर्ण
	/*
	 * Controller at offset 0x8500 is primary
	 */
	अगर ((rsrc_reg.start & 0xfffff) == 0x8500)
		primary = 1;
	अन्यथा
		primary = 0;

	/* Get bus range अगर any */
	bus_range = of_get_property(dev, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक)) अणु
		prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF, assume"
		       " bus 0\n", dev);
	पूर्ण

	pci_add_flags(PCI_REASSIGN_ALL_BUS);
	hose = pcibios_alloc_controller(dev);
	अगर (!hose)
		वापस -ENOMEM;

	hose->first_busno = bus_range ? bus_range[0] : 0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	अगर (of_device_is_compatible(dev, "fsl,mpc8314-pcie")) अणु
		ret = mpc83xx_pcie_setup(hose, &rsrc_reg);
		अगर (ret)
			जाओ err0;
	पूर्ण अन्यथा अणु
		setup_indirect_pci(hose, rsrc_cfg.start,
				   rsrc_cfg.start + 4, 0);
	पूर्ण

	prपूर्णांकk(KERN_INFO "Found FSL PCI host bridge at 0x%016llx. "
	       "Firmware bus number: %d->%d\n",
	       (अचिन्हित दीर्घ दीर्घ)rsrc_reg.start, hose->first_busno,
	       hose->last_busno);

	pr_debug(" ->Hose at 0x%p, cfg_addr=0x%p,cfg_data=0x%p\n",
	    hose, hose->cfg_addr, hose->cfg_data);

	/* Interpret the "ranges" property */
	/* This also maps the I/O region and sets isa_io/mem_base */
	pci_process_bridge_OF_ranges(hose, dev, primary);

	वापस 0;
err0:
	pcibios_मुक्त_controller(hose);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_83xx */

u64 fsl_pci_immrbar_base(काष्ठा pci_controller *hose)
अणु
#अगर_घोषित CONFIG_PPC_83xx
	अगर (is_mpc83xx_pci) अणु
		काष्ठा mpc83xx_pcie_priv *pcie = hose->dn->data;
		काष्ठा pex_inbound_winकरोw *in;
		पूर्णांक i;

		/* Walk the Root Complex Inbound winकरोws to match IMMR base */
		in = pcie->cfg_type0 + PEX_RC_INWIN_BASE;
		क्रम (i = 0; i < 4; i++) अणु
			/* not enabled, skip */
			अगर (!(in_le32(&in[i].ar) & PEX_RCIWARn_EN))
				जारी;

			अगर (get_immrbase() == in_le32(&in[i].tar))
				वापस (u64)in_le32(&in[i].barh) << 32 |
					    in_le32(&in[i].barl);
		पूर्ण

		prपूर्णांकk(KERN_WARNING "could not find PCI BAR matching IMMR\n");
	पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FSL_SOC_BOOKE) || defined(CONFIG_PPC_86xx)
	अगर (!is_mpc83xx_pci) अणु
		u32 base;

		pci_bus_पढ़ो_config_dword(hose->bus,
			PCI_DEVFN(0, 0), PCI_BASE_ADDRESS_0, &base);

		/*
		 * For PEXCSRBAR, bit 3-0 indicate prefetchable and
		 * address type. So when getting base address, these
		 * bits should be masked
		 */
		base &= PCI_BASE_ADDRESS_MEM_MASK;

		वापस base;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_E500
अटल पूर्णांक mcheck_handle_load(काष्ठा pt_regs *regs, u32 inst)
अणु
	अचिन्हित पूर्णांक rd, ra, rb, d;

	rd = get_rt(inst);
	ra = get_ra(inst);
	rb = get_rb(inst);
	d = get_d(inst);

	चयन (get_op(inst)) अणु
	हाल 31:
		चयन (get_xop(inst)) अणु
		हाल OP_31_XOP_LWZX:
		हाल OP_31_XOP_LWBRX:
			regs->gpr[rd] = 0xffffffff;
			अवरोध;

		हाल OP_31_XOP_LWZUX:
			regs->gpr[rd] = 0xffffffff;
			regs->gpr[ra] += regs->gpr[rb];
			अवरोध;

		हाल OP_31_XOP_LBZX:
			regs->gpr[rd] = 0xff;
			अवरोध;

		हाल OP_31_XOP_LBZUX:
			regs->gpr[rd] = 0xff;
			regs->gpr[ra] += regs->gpr[rb];
			अवरोध;

		हाल OP_31_XOP_LHZX:
		हाल OP_31_XOP_LHBRX:
			regs->gpr[rd] = 0xffff;
			अवरोध;

		हाल OP_31_XOP_LHZUX:
			regs->gpr[rd] = 0xffff;
			regs->gpr[ra] += regs->gpr[rb];
			अवरोध;

		हाल OP_31_XOP_LHAX:
			regs->gpr[rd] = ~0UL;
			अवरोध;

		हाल OP_31_XOP_LHAUX:
			regs->gpr[rd] = ~0UL;
			regs->gpr[ra] += regs->gpr[rb];
			अवरोध;

		शेष:
			वापस 0;
		पूर्ण
		अवरोध;

	हाल OP_LWZ:
		regs->gpr[rd] = 0xffffffff;
		अवरोध;

	हाल OP_LWZU:
		regs->gpr[rd] = 0xffffffff;
		regs->gpr[ra] += (s16)d;
		अवरोध;

	हाल OP_LBZ:
		regs->gpr[rd] = 0xff;
		अवरोध;

	हाल OP_LBZU:
		regs->gpr[rd] = 0xff;
		regs->gpr[ra] += (s16)d;
		अवरोध;

	हाल OP_LHZ:
		regs->gpr[rd] = 0xffff;
		अवरोध;

	हाल OP_LHZU:
		regs->gpr[rd] = 0xffff;
		regs->gpr[ra] += (s16)d;
		अवरोध;

	हाल OP_LHA:
		regs->gpr[rd] = ~0UL;
		अवरोध;

	हाल OP_LHAU:
		regs->gpr[rd] = ~0UL;
		regs->gpr[ra] += (s16)d;
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक is_in_pci_mem_space(phys_addr_t addr)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा resource *res;
	पूर्णांक i;

	list_क्रम_each_entry(hose, &hose_list, list_node) अणु
		अगर (!(hose->indirect_type & PPC_INसूचीECT_TYPE_EXT_REG))
			जारी;

		क्रम (i = 0; i < 3; i++) अणु
			res = &hose->mem_resources[i];
			अगर ((res->flags & IORESOURCE_MEM) &&
				addr >= res->start && addr <= res->end)
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक fsl_pci_mcheck_exception(काष्ठा pt_regs *regs)
अणु
	u32 inst;
	पूर्णांक ret;
	phys_addr_t addr = 0;

	/* Let KVM/QEMU deal with the exception */
	अगर (regs->msr & MSR_GS)
		वापस 0;

#अगर_घोषित CONFIG_PHYS_64BIT
	addr = mfspr(SPRN_MCARU);
	addr <<= 32;
#पूर्ण_अगर
	addr += mfspr(SPRN_MCAR);

	अगर (is_in_pci_mem_space(addr)) अणु
		अगर (user_mode(regs))
			ret = copy_from_user_nofault(&inst,
					(व्योम __user *)regs->nip, माप(inst));
		अन्यथा
			ret = get_kernel_nofault(inst, (व्योम *)regs->nip);

		अगर (!ret && mcheck_handle_load(regs, inst)) अणु
			regs->nip += 4;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FSL_SOC_BOOKE) || defined(CONFIG_PPC_86xx)
अटल स्थिर काष्ठा of_device_id pci_ids[] = अणु
	अणु .compatible = "fsl,mpc8540-pci", पूर्ण,
	अणु .compatible = "fsl,mpc8548-pcie", पूर्ण,
	अणु .compatible = "fsl,mpc8610-pci", पूर्ण,
	अणु .compatible = "fsl,mpc8641-pcie", पूर्ण,
	अणु .compatible = "fsl,qoriq-pcie", पूर्ण,
	अणु .compatible = "fsl,qoriq-pcie-v2.1", पूर्ण,
	अणु .compatible = "fsl,qoriq-pcie-v2.2", पूर्ण,
	अणु .compatible = "fsl,qoriq-pcie-v2.3", पूर्ण,
	अणु .compatible = "fsl,qoriq-pcie-v2.4", पूर्ण,
	अणु .compatible = "fsl,qoriq-pcie-v3.0", पूर्ण,

	/*
	 * The following entries are क्रम compatibility with older device
	 * trees.
	 */
	अणु .compatible = "fsl,p1022-pcie", पूर्ण,
	अणु .compatible = "fsl,p4080-pcie", पूर्ण,

	अणुपूर्ण,
पूर्ण;

काष्ठा device_node *fsl_pci_primary;

व्योम fsl_pci_assign_primary(व्योम)
अणु
	काष्ठा device_node *np;

	/* Callers can specअगरy the primary bus using other means. */
	अगर (fsl_pci_primary)
		वापस;

	/* If a PCI host bridge contains an ISA node, it's primary. */
	np = of_find_node_by_type(शून्य, "isa");
	जबतक ((fsl_pci_primary = of_get_parent(np))) अणु
		of_node_put(np);
		np = fsl_pci_primary;

		अगर (of_match_node(pci_ids, np) && of_device_is_available(np))
			वापस;
	पूर्ण

	/*
	 * If there's no PCI host bridge with ISA, arbitrarily
	 * designate one as primary.  This can go away once
	 * various bugs with primary-less प्रणालीs are fixed.
	 */
	क्रम_each_matching_node(np, pci_ids) अणु
		अगर (of_device_is_available(np)) अणु
			fsl_pci_primary = np;
			of_node_put(np);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल irqवापस_t fsl_pci_pme_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pci_controller *hose = dev_id;
	काष्ठा ccsr_pci __iomem *pci = hose->निजी_data;
	u32 dr;

	dr = in_be32(&pci->pex_pme_mes_dr);
	अगर (!dr)
		वापस IRQ_NONE;

	out_be32(&pci->pex_pme_mes_dr, dr);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fsl_pci_pme_probe(काष्ठा pci_controller *hose)
अणु
	काष्ठा ccsr_pci __iomem *pci;
	काष्ठा pci_dev *dev;
	पूर्णांक pme_irq;
	पूर्णांक res;
	u16 pms;

	/* Get hose's pci_dev */
	dev = list_first_entry(&hose->bus->devices, typeof(*dev), bus_list);

	/* PME Disable */
	pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pms);
	pms &= ~PCI_PM_CTRL_PME_ENABLE;
	pci_ग_लिखो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, pms);

	pme_irq = irq_of_parse_and_map(hose->dn, 0);
	अगर (!pme_irq) अणु
		dev_err(&dev->dev, "Failed to map PME interrupt.\n");

		वापस -ENXIO;
	पूर्ण

	res = devm_request_irq(hose->parent, pme_irq,
			fsl_pci_pme_handle,
			IRQF_SHARED,
			"[PCI] PME", hose);
	अगर (res < 0) अणु
		dev_err(&dev->dev, "Unable to request irq %d for PME\n", pme_irq);
		irq_dispose_mapping(pme_irq);

		वापस -ENODEV;
	पूर्ण

	pci = hose->निजी_data;

	/* Enable PTOD, ENL23D & EXL23D */
	clrbits32(&pci->pex_pme_mes_disr,
		  PME_DISR_EN_PTOD | PME_DISR_EN_ENL23D | PME_DISR_EN_EXL23D);

	out_be32(&pci->pex_pme_mes_ier, 0);
	setbits32(&pci->pex_pme_mes_ier,
		  PME_DISR_EN_PTOD | PME_DISR_EN_ENL23D | PME_DISR_EN_EXL23D);

	/* PME Enable */
	pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pms);
	pms |= PCI_PM_CTRL_PME_ENABLE;
	pci_ग_लिखो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, pms);

	वापस 0;
पूर्ण

अटल व्योम send_pme_turnoff_message(काष्ठा pci_controller *hose)
अणु
	काष्ठा ccsr_pci __iomem *pci = hose->निजी_data;
	u32 dr;
	पूर्णांक i;

	/* Send PME_Turn_Off Message Request */
	setbits32(&pci->pex_pmcr, PEX_PMCR_PTOMR);

	/* Wait trun off करोne */
	क्रम (i = 0; i < 150; i++) अणु
		dr = in_be32(&pci->pex_pme_mes_dr);
		अगर (dr) अणु
			out_be32(&pci->pex_pme_mes_dr, dr);
			अवरोध;
		पूर्ण

		udelay(1000);
	पूर्ण
पूर्ण

अटल व्योम fsl_pci_syscore_करो_suspend(काष्ठा pci_controller *hose)
अणु
	send_pme_turnoff_message(hose);
पूर्ण

अटल पूर्णांक fsl_pci_syscore_suspend(व्योम)
अणु
	काष्ठा pci_controller *hose, *पंचांगp;

	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node)
		fsl_pci_syscore_करो_suspend(hose);

	वापस 0;
पूर्ण

अटल व्योम fsl_pci_syscore_करो_resume(काष्ठा pci_controller *hose)
अणु
	काष्ठा ccsr_pci __iomem *pci = hose->निजी_data;
	u32 dr;
	पूर्णांक i;

	/* Send Exit L2 State Message */
	setbits32(&pci->pex_pmcr, PEX_PMCR_EXL2S);

	/* Wait निकास करोne */
	क्रम (i = 0; i < 150; i++) अणु
		dr = in_be32(&pci->pex_pme_mes_dr);
		अगर (dr) अणु
			out_be32(&pci->pex_pme_mes_dr, dr);
			अवरोध;
		पूर्ण

		udelay(1000);
	पूर्ण

	setup_pci_aपंचांगu(hose);
पूर्ण

अटल व्योम fsl_pci_syscore_resume(व्योम)
अणु
	काष्ठा pci_controller *hose, *पंचांगp;

	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node)
		fsl_pci_syscore_करो_resume(hose);
पूर्ण

अटल काष्ठा syscore_ops pci_syscore_pm_ops = अणु
	.suspend = fsl_pci_syscore_suspend,
	.resume = fsl_pci_syscore_resume,
पूर्ण;
#पूर्ण_अगर

व्योम fsl_pcibios_fixup_phb(काष्ठा pci_controller *phb)
अणु
#अगर_घोषित CONFIG_PM_SLEEP
	fsl_pci_pme_probe(phb);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक add_err_dev(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_device *errdev;
	काष्ठा mpc85xx_edac_pci_plat_data pd = अणु
		.of_node = pdev->dev.of_node
	पूर्ण;

	errdev = platक्रमm_device_रेजिस्टर_resndata(&pdev->dev,
						   "mpc85xx-pci-edac",
						   PLATFORM_DEVID_AUTO,
						   pdev->resource,
						   pdev->num_resources,
						   &pd, माप(pd));

	वापस PTR_ERR_OR_ZERO(errdev);
पूर्ण

अटल पूर्णांक fsl_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node;
	पूर्णांक ret;

	node = pdev->dev.of_node;
	ret = fsl_add_bridge(pdev, fsl_pci_primary == node);
	अगर (ret)
		वापस ret;

	ret = add_err_dev(pdev);
	अगर (ret)
		dev_err(&pdev->dev, "couldn't register error device: %d\n",
			ret);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver fsl_pci_driver = अणु
	.driver = अणु
		.name = "fsl-pci",
		.of_match_table = pci_ids,
	पूर्ण,
	.probe = fsl_pci_probe,
पूर्ण;

अटल पूर्णांक __init fsl_pci_init(व्योम)
अणु
#अगर_घोषित CONFIG_PM_SLEEP
	रेजिस्टर_syscore_ops(&pci_syscore_pm_ops);
#पूर्ण_अगर
	वापस platक्रमm_driver_रेजिस्टर(&fsl_pci_driver);
पूर्ण
arch_initcall(fsl_pci_init);
#पूर्ण_अगर
