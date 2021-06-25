<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __ASM_CSKY_PCI_H
#घोषणा __ASM_CSKY_PCI_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>

#घोषणा PCIBIOS_MIN_IO		0
#घोषणा PCIBIOS_MIN_MEM		0

/* C-SKY shim करोes not initialize PCI bus */
#घोषणा pcibios_assign_all_busses() 1

बाह्य पूर्णांक isa_dma_bridge_buggy;

#अगर_घोषित CONFIG_PCI
अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	/* no legacy IRQ on csky */
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	/* always show the करोमुख्य in /proc */
	वापस 1;
पूर्ण
#पूर्ण_अगर  /* CONFIG_PCI */

#पूर्ण_अगर  /* __ASM_CSKY_PCI_H */
