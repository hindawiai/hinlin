<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित _ASM_PCI_H
#घोषणा _ASM_PCI_H

#समावेश <linux/mm.h>

#अगर_घोषित __KERNEL__

/*
 * This file essentially defines the पूर्णांकerface between board
 * specअगरic PCI code and MIPS common PCI code.	Should potentially put
 * पूर्णांकo include/यंत्र/pci.h file.
 */

#समावेश <linux/ioport.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>

#अगर_घोषित CONFIG_PCI_DRIVERS_LEGACY

/*
 * Each pci channel is a top-level PCI bus seem by CPU.	 A machine  with
 * multiple PCI channels may have multiple PCI host controllers or a
 * single controller supporting multiple channels.
 */
काष्ठा pci_controller अणु
	काष्ठा list_head list;
	काष्ठा pci_bus *bus;
	काष्ठा device_node *of_node;

	काष्ठा pci_ops *pci_ops;
	काष्ठा resource *mem_resource;
	अचिन्हित दीर्घ mem_offset;
	काष्ठा resource *io_resource;
	अचिन्हित दीर्घ io_offset;
	अचिन्हित दीर्घ io_map_base;

#अगर_अघोषित CONFIG_PCI_DOMAINS_GENERIC
	अचिन्हित पूर्णांक index;
	/* For compatibility with current (as of July 2003) pciutils
	   and XFree86. Eventually will be हटाओd. */
	अचिन्हित पूर्णांक need_करोमुख्य_info;
#पूर्ण_अगर

	/* Optional access methods क्रम पढ़ोing/writing the bus number
	   of the PCI controller */
	पूर्णांक (*get_busno)(व्योम);
	व्योम (*set_busno)(पूर्णांक busno);
पूर्ण;

/*
 * Used by boards to रेजिस्टर their PCI busses beक्रमe the actual scanning.
 */
बाह्य व्योम रेजिस्टर_pci_controller(काष्ठा pci_controller *hose);

/*
 * board supplied pci irq fixup routine
 */
बाह्य पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
बाह्य पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev);

बाह्य अक्षर * (*pcibios_plat_setup)(अक्षर *str);

#अगर_घोषित CONFIG_OF
/* this function parses memory ranges from a device node */
बाह्य व्योम pci_load_of_ranges(काष्ठा pci_controller *hose,
			       काष्ठा device_node *node);
#अन्यथा
अटल अंतरभूत व्योम pci_load_of_ranges(काष्ठा pci_controller *hose,
				      काष्ठा device_node *node) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_DOMAINS_GENERIC
अटल अंतरभूत व्योम set_pci_need_करोमुख्य_info(काष्ठा pci_controller *hose,
					    पूर्णांक need_करोमुख्य_info)
अणु
	/* nothing to करो */
पूर्ण
#या_अगर defined(CONFIG_PCI_DOMAINS)
अटल अंतरभूत व्योम set_pci_need_करोमुख्य_info(काष्ठा pci_controller *hose,
					    पूर्णांक need_करोमुख्य_info)
अणु
	hose->need_करोमुख्य_info = need_करोमुख्य_info;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_DOMAINS */

#पूर्ण_अगर

/* Can be used to override the logic in pci_scan_bus क्रम skipping
   alपढ़ोy-configured bus numbers - to be used क्रम buggy BIOSes
   or architectures with incomplete PCI setup by the loader */
अटल अंतरभूत अचिन्हित पूर्णांक pcibios_assign_all_busses(व्योम)
अणु
	वापस 1;
पूर्ण

बाह्य अचिन्हित दीर्घ PCIBIOS_MIN_IO;
बाह्य अचिन्हित दीर्घ PCIBIOS_MIN_MEM;

#घोषणा PCIBIOS_MIN_CARDBUS_IO	0x4000

#घोषणा HAVE_PCI_MMAP
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE

/*
 * Dynamic DMA mapping stuff.
 * MIPS has everything mapped अटलally.
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/पन.स>

#अगर_घोषित CONFIG_PCI_DOMAINS_GENERIC
अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	वापस pci_करोमुख्य_nr(bus);
पूर्ण
#या_अगर defined(CONFIG_PCI_DOMAINS)
#घोषणा pci_करोमुख्य_nr(bus) ((काष्ठा pci_controller *)(bus)->sysdata)->index

अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;
	वापस hose->need_करोमुख्य_info;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_DOMAINS */

#पूर्ण_अगर /* __KERNEL__ */

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
बाह्य पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev);

/* Chances are this पूर्णांकerrupt is wired PC-style ...  */
अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	वापस channel ? 15 : 14;
पूर्ण

#पूर्ण_अगर /* _ASM_PCI_H */
