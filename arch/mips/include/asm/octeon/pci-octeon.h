<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005-2009 Cavium Networks
 */

#अगर_अघोषित __PCI_OCTEON_H__
#घोषणा __PCI_OCTEON_H__

#समावेश <linux/pci.h>

/*
 * The physical memory base mapped by BAR1.  256MB at the end of the
 * first 4GB.
 */
#घोषणा CVMX_PCIE_BAR1_PHYS_BASE ((1ull << 32) - (1ull << 28))
#घोषणा CVMX_PCIE_BAR1_PHYS_SIZE (1ull << 28)

/*
 * The RC base of BAR1.	 gen1 has a 39-bit BAR2, gen2 has 41-bit BAR2,
 * place BAR1 so it is the same क्रम both.
 */
#घोषणा CVMX_PCIE_BAR1_RC_BASE (1ull << 41)

/*
 * pcibios_map_irq() is defined inside pci-octeon.c. All it करोes is
 * call the Octeon specअगरic version poपूर्णांकed to by this variable. This
 * function needs to change क्रम PCI or PCIe based hosts.
 */
बाह्य पूर्णांक (*octeon_pcibios_map_irq)(स्थिर काष्ठा pci_dev *dev,
				     u8 slot, u8 pin);

/*
 * For PCI (not PCIe) the BAR2 base address.
 */
#घोषणा OCTEON_BAR2_PCI_ADDRESS 0x8000000000ull

/*
 * For PCI (not PCIe) the base of the memory mapped by BAR1
 */
बाह्य u64 octeon_bar1_pci_phys;

/*
 * The following defines are used when octeon_dma_bar_type =
 * OCTEON_DMA_BAR_TYPE_BIG
 */
#घोषणा OCTEON_PCI_BAR1_HOLE_BITS 5
#घोषणा OCTEON_PCI_BAR1_HOLE_SIZE (1ul<<(OCTEON_PCI_BAR1_HOLE_BITS+3))

क्रमागत octeon_dma_bar_type अणु
	OCTEON_DMA_BAR_TYPE_INVALID,
	OCTEON_DMA_BAR_TYPE_SMALL,
	OCTEON_DMA_BAR_TYPE_BIG,
	OCTEON_DMA_BAR_TYPE_PCIE,
	OCTEON_DMA_BAR_TYPE_PCIE2
पूर्ण;

/*
 * This tells the DMA mapping प्रणाली in dma-octeon.c how to map PCI
 * DMA addresses.
 */
बाह्य क्रमागत octeon_dma_bar_type octeon_dma_bar_type;

व्योम octeon_pci_dma_init(व्योम);
बाह्य अक्षर *octeon_swiotlb;

#पूर्ण_अगर
