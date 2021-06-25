<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_MICROBLAZE_PCI_BRIDGE_H
#घोषणा _ASM_MICROBLAZE_PCI_BRIDGE_H
#अगर_घोषित __KERNEL__
/*
 */
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/ioport.h>

काष्ठा device_node;

#अगर_घोषित CONFIG_PCI
बाह्य काष्ठा list_head hose_list;
बाह्य पूर्णांक pcibios_vaddr_is_ioport(व्योम __iomem *address);
#अन्यथा
अटल अंतरभूत पूर्णांक pcibios_vaddr_is_ioport(व्योम __iomem *address)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Structure of a PCI controller (host bridge)
 */
काष्ठा pci_controller अणु
	काष्ठा pci_bus *bus;
	अक्षर is_dynamic;
	काष्ठा device_node *dn;
	काष्ठा list_head list_node;
	काष्ठा device *parent;

	पूर्णांक first_busno;
	पूर्णांक last_busno;

	पूर्णांक self_busno;

	व्योम __iomem *io_base_virt;
	resource_माप_प्रकार io_base_phys;

	resource_माप_प्रकार pci_io_size;

	/* Some machines (PReP) have a non 1:1 mapping of
	 * the PCI memory space in the CPU bus space
	 */
	resource_माप_प्रकार pci_mem_offset;

	/* Some machines have a special region to क्रमward the ISA
	 * "memory" cycles such as VGA memory regions. Left to 0
	 * अगर unsupported
	 */
	resource_माप_प्रकार isa_mem_phys;
	resource_माप_प्रकार isa_mem_size;

	काष्ठा pci_ops *ops;
	अचिन्हित पूर्णांक __iomem *cfg_addr;
	व्योम __iomem *cfg_data;

	/*
	 * Used क्रम variants of PCI indirect handling and possible quirks:
	 *  SET_CFG_TYPE - used on 4xx or any PHB that करोes explicit type0/1
	 *  EXT_REG - provides access to PCI-e extended रेजिस्टरs
	 *  SURPRESS_PRIMARY_BUS - we suppress the setting of PCI_PRIMARY_BUS
	 *   on Freescale PCI-e controllers since they used the PCI_PRIMARY_BUS
	 *   to determine which bus number to match on when generating type0
	 *   config cycles
	 *  NO_PCIE_LINK - the Freescale PCI-e controllers have issues with
	 *   hanging अगर we करोn't have link and try to करो config cycles to
	 *   anything but the PHB.  Only allow talking to the PHB अगर this is
	 *   set.
	 *  BIG_ENDIAN - cfg_addr is a big endian रेजिस्टर
	 *  BROKEN_MRM - the 440EPx/GRx chips have an errata that causes hangs
	 *   on the PLB4.  Effectively disable MRM commands by setting this.
	 */
#घोषणा INसूचीECT_TYPE_SET_CFG_TYPE		0x00000001
#घोषणा INसूचीECT_TYPE_EXT_REG		0x00000002
#घोषणा INसूचीECT_TYPE_SURPRESS_PRIMARY_BUS	0x00000004
#घोषणा INसूचीECT_TYPE_NO_PCIE_LINK		0x00000008
#घोषणा INसूचीECT_TYPE_BIG_ENDIAN		0x00000010
#घोषणा INसूचीECT_TYPE_BROKEN_MRM		0x00000020
	u32 indirect_type;

	/* Currently, we limit ourselves to 1 IO range and 3 mem
	 * ranges since the common pci_bus काष्ठाure can't handle more
	 */
	काष्ठा resource io_resource;
	काष्ठा resource mem_resources[3];
	पूर्णांक global_number;	/* PCI करोमुख्य number */
पूर्ण;

#अगर_घोषित CONFIG_PCI
अटल अंतरभूत काष्ठा pci_controller *pci_bus_to_host(स्थिर काष्ठा pci_bus *bus)
अणु
	वापस bus->sysdata;
पूर्ण

अटल अंतरभूत पूर्णांक isa_vaddr_is_ioport(व्योम __iomem *address)
अणु
	/* No specअगरic ISA handling on ppc32 at this stage, it
	 * all goes through PCI
	 */
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

/* These are used क्रम config access beक्रमe all the PCI probing
   has been करोne. */
बाह्य पूर्णांक early_पढ़ो_config_byte(काष्ठा pci_controller *hose, पूर्णांक bus,
			पूर्णांक dev_fn, पूर्णांक where, u8 *val);
बाह्य पूर्णांक early_पढ़ो_config_word(काष्ठा pci_controller *hose, पूर्णांक bus,
			पूर्णांक dev_fn, पूर्णांक where, u16 *val);
बाह्य पूर्णांक early_पढ़ो_config_dword(काष्ठा pci_controller *hose, पूर्णांक bus,
			पूर्णांक dev_fn, पूर्णांक where, u32 *val);
बाह्य पूर्णांक early_ग_लिखो_config_byte(काष्ठा pci_controller *hose, पूर्णांक bus,
			पूर्णांक dev_fn, पूर्णांक where, u8 val);
बाह्य पूर्णांक early_ग_लिखो_config_word(काष्ठा pci_controller *hose, पूर्णांक bus,
			पूर्णांक dev_fn, पूर्णांक where, u16 val);
बाह्य पूर्णांक early_ग_लिखो_config_dword(काष्ठा pci_controller *hose, पूर्णांक bus,
			पूर्णांक dev_fn, पूर्णांक where, u32 val);

बाह्य पूर्णांक early_find_capability(काष्ठा pci_controller *hose, पूर्णांक bus,
				 पूर्णांक dev_fn, पूर्णांक cap);

बाह्य व्योम setup_indirect_pci(काष्ठा pci_controller *hose,
			       resource_माप_प्रकार cfg_addr,
			       resource_माप_प्रकार cfg_data, u32 flags);

/* Get the PCI host controller क्रम an OF device */
बाह्य काष्ठा pci_controller *pci_find_hose_क्रम_OF_device(
			काष्ठा device_node *node);

/* Fill up host controller resources from the OF node */
बाह्य व्योम pci_process_bridge_OF_ranges(काष्ठा pci_controller *hose,
			काष्ठा device_node *dev, पूर्णांक primary);

/* Allocate & मुक्त a PCI host bridge काष्ठाure */
बाह्य काष्ठा pci_controller *pcibios_alloc_controller(काष्ठा device_node *dev);
बाह्य व्योम pcibios_मुक्त_controller(काष्ठा pci_controller *phb);

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_MICROBLAZE_PCI_BRIDGE_H */
