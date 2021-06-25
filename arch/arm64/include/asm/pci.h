<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_PCI_H
#घोषणा __ASM_PCI_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>

#घोषणा PCIBIOS_MIN_IO		0x1000
#घोषणा PCIBIOS_MIN_MEM		0

/*
 * Set to 1 अगर the kernel should re-assign all PCI bus numbers
 */
#घोषणा pcibios_assign_all_busses() \
	(pci_has_flag(PCI_REASSIGN_ALL_BUS))

#घोषणा arch_can_pci_mmap_wc() 1
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE	1

बाह्य पूर्णांक isa_dma_bridge_buggy;

#अगर_घोषित CONFIG_PCI
अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	/* no legacy IRQ on arm64 */
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर  /* CONFIG_PCI */

#पूर्ण_अगर  /* __ASM_PCI_H */
