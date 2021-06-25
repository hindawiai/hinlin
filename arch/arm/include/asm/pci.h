<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASMARM_PCI_H
#घोषणा ASMARM_PCI_H

#अगर_घोषित __KERNEL__
#समावेश <यंत्र/mach/pci.h> /* क्रम pci_sys_data */

बाह्य अचिन्हित दीर्घ pcibios_min_io;
#घोषणा PCIBIOS_MIN_IO pcibios_min_io
बाह्य अचिन्हित दीर्घ pcibios_min_mem;
#घोषणा PCIBIOS_MIN_MEM pcibios_min_mem

#घोषणा pcibios_assign_all_busses()	pci_has_flag(PCI_REASSIGN_ALL_BUS)

#अगर_घोषित CONFIG_PCI_DOMAINS
अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	वापस pci_करोमुख्य_nr(bus);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_DOMAINS */

#घोषणा HAVE_PCI_MMAP
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE

अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	वापस channel ? 15 : 14;
पूर्ण

बाह्य व्योम pcibios_report_status(अचिन्हित पूर्णांक status_mask, पूर्णांक warn);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
