<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_PCI_H
#घोषणा __ASM_SH_PCI_H

/* Can be used to override the logic in pci_scan_bus क्रम skipping
   alपढ़ोy-configured bus numbers - to be used क्रम buggy BIOSes
   or architectures with incomplete PCI setup by the loader */

#घोषणा pcibios_assign_all_busses()	1

/*
 * A board can define one or more PCI channels that represent built-in (or
 * बाह्यal) PCI controllers.
 */
काष्ठा pci_channel अणु
	काष्ठा pci_channel	*next;
	काष्ठा pci_bus		*bus;

	काष्ठा pci_ops		*pci_ops;

	काष्ठा resource		*resources;
	अचिन्हित पूर्णांक		nr_resources;

	अचिन्हित दीर्घ		io_offset;
	अचिन्हित दीर्घ		mem_offset;

	अचिन्हित दीर्घ		reg_base;
	अचिन्हित दीर्घ		io_map_base;

	अचिन्हित पूर्णांक		index;
	अचिन्हित पूर्णांक		need_करोमुख्य_info;

	/* Optional error handling */
	काष्ठा समयr_list	err_समयr, serr_समयr;
	अचिन्हित पूर्णांक		err_irq, serr_irq;
पूर्ण;

/* arch/sh/drivers/pci/pci.c */
बाह्य raw_spinlock_t pci_config_lock;

बाह्य पूर्णांक रेजिस्टर_pci_controller(काष्ठा pci_channel *hose);
बाह्य व्योम pcibios_report_status(अचिन्हित पूर्णांक status_mask, पूर्णांक warn);

/* arch/sh/drivers/pci/common.c */
बाह्य पूर्णांक early_पढ़ो_config_byte(काष्ठा pci_channel *hose, पूर्णांक top_bus,
				  पूर्णांक bus, पूर्णांक devfn, पूर्णांक offset, u8 *value);
बाह्य पूर्णांक early_पढ़ो_config_word(काष्ठा pci_channel *hose, पूर्णांक top_bus,
				  पूर्णांक bus, पूर्णांक devfn, पूर्णांक offset, u16 *value);
बाह्य पूर्णांक early_पढ़ो_config_dword(काष्ठा pci_channel *hose, पूर्णांक top_bus,
				   पूर्णांक bus, पूर्णांक devfn, पूर्णांक offset, u32 *value);
बाह्य पूर्णांक early_ग_लिखो_config_byte(काष्ठा pci_channel *hose, पूर्णांक top_bus,
				   पूर्णांक bus, पूर्णांक devfn, पूर्णांक offset, u8 value);
बाह्य पूर्णांक early_ग_लिखो_config_word(काष्ठा pci_channel *hose, पूर्णांक top_bus,
				   पूर्णांक bus, पूर्णांक devfn, पूर्णांक offset, u16 value);
बाह्य पूर्णांक early_ग_लिखो_config_dword(काष्ठा pci_channel *hose, पूर्णांक top_bus,
				    पूर्णांक bus, पूर्णांक devfn, पूर्णांक offset, u32 value);
बाह्य व्योम pcibios_enable_समयrs(काष्ठा pci_channel *hose);
बाह्य अचिन्हित पूर्णांक pcibios_handle_status_errors(अचिन्हित दीर्घ addr,
				 अचिन्हित पूर्णांक status, काष्ठा pci_channel *hose);
बाह्य पूर्णांक pci_is_66mhz_capable(काष्ठा pci_channel *hose,
				पूर्णांक top_bus, पूर्णांक current_bus);

बाह्य अचिन्हित दीर्घ PCIBIOS_MIN_IO, PCIBIOS_MIN_MEM;

#घोषणा HAVE_PCI_MMAP
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE

/* Dynamic DMA mapping stuff.
 * SuperH has everything mapped अटलally like x86.
 */

#अगर_घोषित CONFIG_PCI
/*
 * None of the SH PCI controllers support MWI, it is always treated as a
 * direct memory ग_लिखो.
 */
#घोषणा PCI_DISABLE_MWI
#पूर्ण_अगर

/* Board-specअगरic fixup routines. */
पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);

#घोषणा pci_करोमुख्य_nr(bus) ((काष्ठा pci_channel *)(bus)->sysdata)->index

अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_channel *hose = bus->sysdata;
	वापस hose->need_करोमुख्य_info;
पूर्ण

/* Chances are this पूर्णांकerrupt is wired PC-style ...  */
अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	वापस channel ? 15 : 14;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_PCI_H */
