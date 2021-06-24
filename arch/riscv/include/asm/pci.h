<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 SiFive
 */

#अगर_अघोषित _ASM_RISCV_PCI_H
#घोषणा _ASM_RISCV_PCI_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>

#घोषणा PCIBIOS_MIN_IO		0
#घोषणा PCIBIOS_MIN_MEM		0

/* RISC-V shim करोes not initialize PCI bus */
#घोषणा pcibios_assign_all_busses() 1

बाह्य पूर्णांक isa_dma_bridge_buggy;

#अगर_घोषित CONFIG_PCI
अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	/* no legacy IRQ on risc-v */
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	/* always show the करोमुख्य in /proc */
	वापस 1;
पूर्ण

#अगर_घोषित	CONFIG_NUMA

अटल अंतरभूत पूर्णांक pcibus_to_node(काष्ठा pci_bus *bus)
अणु
	वापस dev_to_node(&bus->dev);
पूर्ण
#अगर_अघोषित cpumask_of_pcibus
#घोषणा cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ?		\
				 cpu_all_mask :				\
				 cpumask_of_node(pcibus_to_node(bus)))
#पूर्ण_अगर
#पूर्ण_अगर	/* CONFIG_NUMA */

#पूर्ण_अगर  /* CONFIG_PCI */

#पूर्ण_अगर  /* _ASM_RISCV_PCI_H */
