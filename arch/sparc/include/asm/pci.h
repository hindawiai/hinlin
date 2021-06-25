<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ___ASM_SPARC_PCI_H
#घोषणा ___ASM_SPARC_PCI_H


/* Can be used to override the logic in pci_scan_bus क्रम skipping
 * alपढ़ोy-configured bus numbers - to be used क्रम buggy BIOSes
 * or architectures with incomplete PCI setup by the loader.
 */
#घोषणा pcibios_assign_all_busses()	0

#घोषणा PCIBIOS_MIN_IO		0UL
#घोषणा PCIBIOS_MIN_MEM		0UL

#घोषणा PCI_IRQ_NONE		0xffffffff


#अगर_घोषित CONFIG_SPARC64

/* PCI IOMMU mapping bypass support. */

/* PCI 64-bit addressing works क्रम all slots on all controller
 * types on sparc64.  However, it requires that the device
 * can drive enough of the 64 bits.
 */
#घोषणा PCI64_REQUIRED_MASK	(~(u64)0)
#घोषणा PCI64_ADDR_BASE		0xfffc000000000000UL

/* Return the index of the PCI controller क्रम device PDEV. */
पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *bus);
अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	वापस 1;
पूर्ण

/* Platक्रमm support क्रम /proc/bus/pci/X/Y mmap()s. */
#घोषणा HAVE_PCI_MMAP
#घोषणा arch_can_pci_mmap_io()	1
#घोषणा HAVE_ARCH_PCI_GET_UNMAPPED_AREA
#घोषणा get_pci_unmapped_area get_fb_unmapped_area
#पूर्ण_अगर /* CONFIG_SPARC64 */

#अगर defined(CONFIG_SPARC64) || defined(CONFIG_LEON_PCI)
अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	वापस PCI_IRQ_NONE;
पूर्ण
#अन्यथा
#समावेश <यंत्र-generic/pci.h>
#पूर्ण_अगर

#पूर्ण_अगर /* ___ASM_SPARC_PCI_H */
