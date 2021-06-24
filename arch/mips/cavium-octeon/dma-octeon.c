<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000  Ani Joshi <ajoshi@unixbox.com>
 * Copyright (C) 2000, 2001  Ralf Baechle <ralf@gnu.org>
 * Copyright (C) 2005 Ilya A. Volynets-Evenbakh <ilya@total-knowledge.com>
 * swiped from i386, and cloned क्रम MIPS by Geert, polished by Ralf.
 * IP32 changes by Ilya.
 * Copyright (C) 2010 Cavium Networks, Inc.
 */
#समावेश <linux/dma-direct.h>
#समावेश <linux/memblock.h>
#समावेश <linux/swiotlb.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/bootinfo.h>

#समावेश <यंत्र/octeon/octeon.h>

#अगर_घोषित CONFIG_PCI
#समावेश <linux/pci.h>
#समावेश <यंत्र/octeon/pci-octeon.h>
#समावेश <यंत्र/octeon/cvmx-npi-defs.h>
#समावेश <यंत्र/octeon/cvmx-pci-defs.h>

काष्ठा octeon_dma_map_ops अणु
	dma_addr_t (*phys_to_dma)(काष्ठा device *dev, phys_addr_t paddr);
	phys_addr_t (*dma_to_phys)(काष्ठा device *dev, dma_addr_t daddr);
पूर्ण;

अटल dma_addr_t octeon_hole_phys_to_dma(phys_addr_t paddr)
अणु
	अगर (paddr >= CVMX_PCIE_BAR1_PHYS_BASE && paddr < (CVMX_PCIE_BAR1_PHYS_BASE + CVMX_PCIE_BAR1_PHYS_SIZE))
		वापस paddr - CVMX_PCIE_BAR1_PHYS_BASE + CVMX_PCIE_BAR1_RC_BASE;
	अन्यथा
		वापस paddr;
पूर्ण

अटल phys_addr_t octeon_hole_dma_to_phys(dma_addr_t daddr)
अणु
	अगर (daddr >= CVMX_PCIE_BAR1_RC_BASE)
		वापस daddr + CVMX_PCIE_BAR1_PHYS_BASE - CVMX_PCIE_BAR1_RC_BASE;
	अन्यथा
		वापस daddr;
पूर्ण

अटल dma_addr_t octeon_gen1_phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	अगर (paddr >= 0x410000000ull && paddr < 0x420000000ull)
		paddr -= 0x400000000ull;
	वापस octeon_hole_phys_to_dma(paddr);
पूर्ण

अटल phys_addr_t octeon_gen1_dma_to_phys(काष्ठा device *dev, dma_addr_t daddr)
अणु
	daddr = octeon_hole_dma_to_phys(daddr);

	अगर (daddr >= 0x10000000ull && daddr < 0x20000000ull)
		daddr += 0x400000000ull;

	वापस daddr;
पूर्ण

अटल स्थिर काष्ठा octeon_dma_map_ops octeon_gen1_ops = अणु
	.phys_to_dma	= octeon_gen1_phys_to_dma,
	.dma_to_phys	= octeon_gen1_dma_to_phys,
पूर्ण;

अटल dma_addr_t octeon_gen2_phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	वापस octeon_hole_phys_to_dma(paddr);
पूर्ण

अटल phys_addr_t octeon_gen2_dma_to_phys(काष्ठा device *dev, dma_addr_t daddr)
अणु
	वापस octeon_hole_dma_to_phys(daddr);
पूर्ण

अटल स्थिर काष्ठा octeon_dma_map_ops octeon_gen2_ops = अणु
	.phys_to_dma	= octeon_gen2_phys_to_dma,
	.dma_to_phys	= octeon_gen2_dma_to_phys,
पूर्ण;

अटल dma_addr_t octeon_big_phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	अगर (paddr >= 0x410000000ull && paddr < 0x420000000ull)
		paddr -= 0x400000000ull;

	/* Anything in the BAR1 hole or above goes via BAR2 */
	अगर (paddr >= 0xf0000000ull)
		paddr = OCTEON_BAR2_PCI_ADDRESS + paddr;

	वापस paddr;
पूर्ण

अटल phys_addr_t octeon_big_dma_to_phys(काष्ठा device *dev, dma_addr_t daddr)
अणु
	अगर (daddr >= OCTEON_BAR2_PCI_ADDRESS)
		daddr -= OCTEON_BAR2_PCI_ADDRESS;

	अगर (daddr >= 0x10000000ull && daddr < 0x20000000ull)
		daddr += 0x400000000ull;
	वापस daddr;
पूर्ण

अटल स्थिर काष्ठा octeon_dma_map_ops octeon_big_ops = अणु
	.phys_to_dma	= octeon_big_phys_to_dma,
	.dma_to_phys	= octeon_big_dma_to_phys,
पूर्ण;

अटल dma_addr_t octeon_small_phys_to_dma(काष्ठा device *dev,
					   phys_addr_t paddr)
अणु
	अगर (paddr >= 0x410000000ull && paddr < 0x420000000ull)
		paddr -= 0x400000000ull;

	/* Anything not in the BAR1 range goes via BAR2 */
	अगर (paddr >= octeon_bar1_pci_phys && paddr < octeon_bar1_pci_phys + 0x8000000ull)
		paddr = paddr - octeon_bar1_pci_phys;
	अन्यथा
		paddr = OCTEON_BAR2_PCI_ADDRESS + paddr;

	वापस paddr;
पूर्ण

अटल phys_addr_t octeon_small_dma_to_phys(काष्ठा device *dev,
					    dma_addr_t daddr)
अणु
	अगर (daddr >= OCTEON_BAR2_PCI_ADDRESS)
		daddr -= OCTEON_BAR2_PCI_ADDRESS;
	अन्यथा
		daddr += octeon_bar1_pci_phys;

	अगर (daddr >= 0x10000000ull && daddr < 0x20000000ull)
		daddr += 0x400000000ull;
	वापस daddr;
पूर्ण

अटल स्थिर काष्ठा octeon_dma_map_ops octeon_small_ops = अणु
	.phys_to_dma	= octeon_small_phys_to_dma,
	.dma_to_phys	= octeon_small_dma_to_phys,
पूर्ण;

अटल स्थिर काष्ठा octeon_dma_map_ops *octeon_pci_dma_ops;

व्योम __init octeon_pci_dma_init(व्योम)
अणु
	चयन (octeon_dma_bar_type) अणु
	हाल OCTEON_DMA_BAR_TYPE_PCIE:
		octeon_pci_dma_ops = &octeon_gen1_ops;
		अवरोध;
	हाल OCTEON_DMA_BAR_TYPE_PCIE2:
		octeon_pci_dma_ops = &octeon_gen2_ops;
		अवरोध;
	हाल OCTEON_DMA_BAR_TYPE_BIG:
		octeon_pci_dma_ops = &octeon_big_ops;
		अवरोध;
	हाल OCTEON_DMA_BAR_TYPE_SMALL:
		octeon_pci_dma_ops = &octeon_small_ops;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
#अगर_घोषित CONFIG_PCI
	अगर (dev && dev_is_pci(dev))
		वापस octeon_pci_dma_ops->phys_to_dma(dev, paddr);
#पूर्ण_अगर
	वापस paddr;
पूर्ण

phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t daddr)
अणु
#अगर_घोषित CONFIG_PCI
	अगर (dev && dev_is_pci(dev))
		वापस octeon_pci_dma_ops->dma_to_phys(dev, daddr);
#पूर्ण_अगर
	वापस daddr;
पूर्ण

अक्षर *octeon_swiotlb;

व्योम __init plat_swiotlb_setup(व्योम)
अणु
	phys_addr_t start, end;
	phys_addr_t max_addr;
	phys_addr_t addr_size;
	माप_प्रकार swiotlbsize;
	अचिन्हित दीर्घ swiotlb_nsद_असल;
	u64 i;

	max_addr = 0;
	addr_size = 0;

	क्रम_each_mem_range(i, &start, &end) अणु
		/* These addresses map low क्रम PCI. */
		अगर (start > 0x410000000ull && !OCTEON_IS_OCTEON2())
			जारी;

		addr_size += (end - start);

		अगर (max_addr < end)
			max_addr = end;
	पूर्ण

	swiotlbsize = PAGE_SIZE;

#अगर_घोषित CONFIG_PCI
	/*
	 * For OCTEON_DMA_BAR_TYPE_SMALL, size the iotlb at 1/4 memory
	 * size to a maximum of 64MB
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN31XX)
	    || OCTEON_IS_MODEL(OCTEON_CN38XX_PASS2)) अणु
		swiotlbsize = addr_size / 4;
		अगर (swiotlbsize > 64 * (1<<20))
			swiotlbsize = 64 * (1<<20);
	पूर्ण अन्यथा अगर (max_addr > 0xf0000000ul) अणु
		/*
		 * Otherwise only allocate a big iotlb अगर there is
		 * memory past the BAR1 hole.
		 */
		swiotlbsize = 64 * (1<<20);
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_OHCI_HCD_PLATFORM
	/* OCTEON II ohci is only 32-bit. */
	अगर (OCTEON_IS_OCTEON2() && max_addr >= 0x100000000ul)
		swiotlbsize = 64 * (1<<20);
#पूर्ण_अगर
	swiotlb_nsद_असल = swiotlbsize >> IO_TLB_SHIFT;
	swiotlb_nsद_असल = ALIGN(swiotlb_nsद_असल, IO_TLB_SEGSIZE);
	swiotlbsize = swiotlb_nsद_असल << IO_TLB_SHIFT;

	octeon_swiotlb = memblock_alloc_low(swiotlbsize, PAGE_SIZE);
	अगर (!octeon_swiotlb)
		panic("%s: Failed to allocate %zu bytes align=%lx\n",
		      __func__, swiotlbsize, PAGE_SIZE);

	अगर (swiotlb_init_with_tbl(octeon_swiotlb, swiotlb_nsद_असल, 1) == -ENOMEM)
		panic("Cannot allocate SWIOTLB buffer");
पूर्ण
