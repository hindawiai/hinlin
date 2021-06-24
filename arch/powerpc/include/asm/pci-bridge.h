<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_PCI_BRIDGE_H
#घोषणा _ASM_POWERPC_PCI_BRIDGE_H
#अगर_घोषित __KERNEL__
/*
 */
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/ioport.h>
#समावेश <linux/numa.h>

काष्ठा device_node;

/*
 * PCI controller operations
 */
काष्ठा pci_controller_ops अणु
	व्योम		(*dma_dev_setup)(काष्ठा pci_dev *pdev);
	व्योम		(*dma_bus_setup)(काष्ठा pci_bus *bus);
	bool		(*iommu_bypass_supported)(काष्ठा pci_dev *pdev,
				u64 mask);

	पूर्णांक		(*probe_mode)(काष्ठा pci_bus *bus);

	/* Called when pci_enable_device() is called. Returns true to
	 * allow assignment/enabling of the device. */
	bool		(*enable_device_hook)(काष्ठा pci_dev *pdev);

	व्योम		(*disable_device)(काष्ठा pci_dev *pdev);

	व्योम		(*release_device)(काष्ठा pci_dev *pdev);

	/* Called during PCI resource reassignment */
	resource_माप_प्रकार (*winकरोw_alignment)(काष्ठा pci_bus *bus,
					    अचिन्हित दीर्घ type);
	व्योम		(*setup_bridge)(काष्ठा pci_bus *bus,
					अचिन्हित दीर्घ type);
	व्योम		(*reset_secondary_bus)(काष्ठा pci_dev *pdev);

#अगर_घोषित CONFIG_PCI_MSI
	पूर्णांक		(*setup_msi_irqs)(काष्ठा pci_dev *pdev,
					  पूर्णांक nvec, पूर्णांक type);
	व्योम		(*tearकरोwn_msi_irqs)(काष्ठा pci_dev *pdev);
#पूर्ण_अगर

	व्योम		(*shutकरोwn)(काष्ठा pci_controller *hose);
पूर्ण;

/*
 * Structure of a PCI controller (host bridge)
 */
काष्ठा pci_controller अणु
	काष्ठा pci_bus *bus;
	अक्षर is_dynamic;
#अगर_घोषित CONFIG_PPC64
	पूर्णांक node;
#पूर्ण_अगर
	काष्ठा device_node *dn;
	काष्ठा list_head list_node;
	काष्ठा device *parent;

	पूर्णांक first_busno;
	पूर्णांक last_busno;
	पूर्णांक self_busno;
	काष्ठा resource busn;

	व्योम __iomem *io_base_virt;
#अगर_घोषित CONFIG_PPC64
	व्योम __iomem *io_base_alloc;
#पूर्ण_अगर
	resource_माप_प्रकार io_base_phys;
	resource_माप_प्रकार pci_io_size;

	/* Some machines have a special region to क्रमward the ISA
	 * "memory" cycles such as VGA memory regions. Left to 0
	 * अगर unsupported
	 */
	resource_माप_प्रकार	isa_mem_phys;
	resource_माप_प्रकार	isa_mem_size;

	काष्ठा pci_controller_ops controller_ops;
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
	 *  BROKEN_MRM - the 440EPx/GRx chips have an errata that causes hangs on
	 *   the PLB4.  Effectively disable MRM commands by setting this.
	 *  FSL_CFG_REG_LINK - Freescale controller version in which the PCIe
	 *   link status is in a RC PCIe cfg रेजिस्टर (vs being a SoC रेजिस्टर)
	 */
#घोषणा PPC_INसूचीECT_TYPE_SET_CFG_TYPE		0x00000001
#घोषणा PPC_INसूचीECT_TYPE_EXT_REG		0x00000002
#घोषणा PPC_INसूचीECT_TYPE_SURPRESS_PRIMARY_BUS	0x00000004
#घोषणा PPC_INसूचीECT_TYPE_NO_PCIE_LINK		0x00000008
#घोषणा PPC_INसूचीECT_TYPE_BIG_ENDIAN		0x00000010
#घोषणा PPC_INसूचीECT_TYPE_BROKEN_MRM		0x00000020
#घोषणा PPC_INसूचीECT_TYPE_FSL_CFG_REG_LINK	0x00000040
	u32 indirect_type;
	/* Currently, we limit ourselves to 1 IO range and 3 mem
	 * ranges since the common pci_bus काष्ठाure can't handle more
	 */
	काष्ठा resource	io_resource;
	काष्ठा resource mem_resources[3];
	resource_माप_प्रकार mem_offset[3];
	पूर्णांक global_number;		/* PCI करोमुख्य number */

	resource_माप_प्रकार dma_winकरोw_base_cur;
	resource_माप_प्रकार dma_winकरोw_size;

#अगर_घोषित CONFIG_PPC64
	अचिन्हित दीर्घ buid;
	काष्ठा pci_dn *pci_data;
#पूर्ण_अगर	/* CONFIG_PPC64 */

	व्योम *निजी_data;
पूर्ण;

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

बाह्य व्योम setup_indirect_pci(काष्ठा pci_controller* hose,
			       resource_माप_प्रकार cfg_addr,
			       resource_माप_प्रकार cfg_data, u32 flags);

बाह्य पूर्णांक indirect_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक offset, पूर्णांक len, u32 *val);

बाह्य पूर्णांक __indirect_पढ़ो_config(काष्ठा pci_controller *hose,
				  अचिन्हित अक्षर bus_number, अचिन्हित पूर्णांक devfn,
				  पूर्णांक offset, पूर्णांक len, u32 *val);

बाह्य पूर्णांक indirect_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				 पूर्णांक offset, पूर्णांक len, u32 val);

अटल अंतरभूत काष्ठा pci_controller *pci_bus_to_host(स्थिर काष्ठा pci_bus *bus)
अणु
	वापस bus->sysdata;
पूर्ण

#अगर_अघोषित CONFIG_PPC64

बाह्य पूर्णांक pci_device_from_OF_node(काष्ठा device_node *node,
				   u8 *bus, u8 *devfn);
बाह्य व्योम pci_create_OF_bus_map(व्योम);

#अन्यथा	/* CONFIG_PPC64 */

/*
 * PCI stuff, क्रम nodes representing PCI devices, poपूर्णांकed to
 * by device_node->data.
 */
काष्ठा iommu_table;

काष्ठा pci_dn अणु
	पूर्णांक     flags;
#घोषणा PCI_DN_FLAG_IOV_VF	0x01
#घोषणा PCI_DN_FLAG_DEAD	0x02    /* Device has been hot-हटाओd */

	पूर्णांक	busno;			/* pci bus number */
	पूर्णांक	devfn;			/* pci device and function number */
	पूर्णांक	venकरोr_id;		/* Venकरोr ID */
	पूर्णांक	device_id;		/* Device ID */
	पूर्णांक	class_code;		/* Device class code */

	काष्ठा  pci_dn *parent;
	काष्ठा  pci_controller *phb;	/* क्रम pci devices */
	काष्ठा	iommu_table_group *table_group;	/* क्रम phb's or bridges */

	पूर्णांक	pci_ext_config_space;	/* क्रम pci devices */
#अगर_घोषित CONFIG_EEH
	काष्ठा eeh_dev *edev;		/* eeh device */
#पूर्ण_अगर
#घोषणा IODA_INVALID_PE		0xFFFFFFFF
	अचिन्हित पूर्णांक pe_number;
#अगर_घोषित CONFIG_PCI_IOV
	u16     vfs_expanded;		/* number of VFs IOV BAR expanded */
	u16     num_vfs;		/* number of VFs enabled*/
	अचिन्हित पूर्णांक *pe_num_map;	/* PE# क्रम the first VF PE or array */
	bool    m64_single_mode;	/* Use M64 BAR in Single Mode */
#घोषणा IODA_INVALID_M64        (-1)
	पूर्णांक     (*m64_map)[PCI_SRIOV_NUM_BARS];	/* Only used on घातernv */
	पूर्णांक     last_allow_rc;			/* Only used on pseries */
#पूर्ण_अगर /* CONFIG_PCI_IOV */
	पूर्णांक	mps;			/* Maximum Payload Size */
	काष्ठा list_head child_list;
	काष्ठा list_head list;
	काष्ठा resource holes[PCI_SRIOV_NUM_BARS];
पूर्ण;

/* Get the poपूर्णांकer to a device_node's pci_dn */
#घोषणा PCI_DN(dn)	((काष्ठा pci_dn *) (dn)->data)

बाह्य काष्ठा pci_dn *pci_get_pdn_by_devfn(काष्ठा pci_bus *bus,
					   पूर्णांक devfn);
बाह्य काष्ठा pci_dn *pci_get_pdn(काष्ठा pci_dev *pdev);
बाह्य काष्ठा pci_dn *pci_add_device_node_info(काष्ठा pci_controller *hose,
					       काष्ठा device_node *dn);
बाह्य व्योम pci_हटाओ_device_node_info(काष्ठा device_node *dn);

#अगर_घोषित CONFIG_PCI_IOV
काष्ठा pci_dn *add_sriov_vf_pdns(काष्ठा pci_dev *pdev);
व्योम हटाओ_sriov_vf_pdns(काष्ठा pci_dev *pdev);
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pci_device_from_OF_node(काष्ठा device_node *np,
					  u8 *bus, u8 *devfn)
अणु
	अगर (!PCI_DN(np))
		वापस -ENODEV;
	*bus = PCI_DN(np)->busno;
	*devfn = PCI_DN(np)->devfn;
	वापस 0;
पूर्ण

#अगर defined(CONFIG_EEH)
अटल अंतरभूत काष्ठा eeh_dev *pdn_to_eeh_dev(काष्ठा pci_dn *pdn)
अणु
	वापस pdn ? pdn->edev : शून्य;
पूर्ण
#अन्यथा
#घोषणा pdn_to_eeh_dev(x)	(शून्य)
#पूर्ण_अगर

/** Find the bus corresponding to the indicated device node */
बाह्य काष्ठा pci_bus *pci_find_bus_by_node(काष्ठा device_node *dn);

/** Remove all of the PCI devices under this bus */
बाह्य व्योम pci_hp_हटाओ_devices(काष्ठा pci_bus *bus);

/** Discover new pci devices under this bus, and add them */
बाह्य व्योम pci_hp_add_devices(काष्ठा pci_bus *bus);

बाह्य पूर्णांक pcibios_unmap_io_space(काष्ठा pci_bus *bus);
बाह्य पूर्णांक pcibios_map_io_space(काष्ठा pci_bus *bus);

#अगर_घोषित CONFIG_NUMA
#घोषणा PHB_SET_NODE(PHB, NODE)		((PHB)->node = (NODE))
#अन्यथा
#घोषणा PHB_SET_NODE(PHB, NODE)		((PHB)->node = NUMA_NO_NODE)
#पूर्ण_अगर

#पूर्ण_अगर	/* CONFIG_PPC64 */

/* Get the PCI host controller क्रम an OF device */
बाह्य काष्ठा pci_controller *pci_find_hose_क्रम_OF_device(
			काष्ठा device_node* node);

बाह्य काष्ठा pci_controller *pci_find_controller_क्रम_करोमुख्य(पूर्णांक करोमुख्य_nr);

/* Fill up host controller resources from the OF node */
बाह्य व्योम pci_process_bridge_OF_ranges(काष्ठा pci_controller *hose,
			काष्ठा device_node *dev, पूर्णांक primary);

/* Allocate & मुक्त a PCI host bridge काष्ठाure */
बाह्य काष्ठा pci_controller *pcibios_alloc_controller(काष्ठा device_node *dev);
बाह्य व्योम pcibios_मुक्त_controller(काष्ठा pci_controller *phb);
बाह्य व्योम pcibios_मुक्त_controller_deferred(काष्ठा pci_host_bridge *bridge);

#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक pcibios_vaddr_is_ioport(व्योम __iomem *address);
#अन्यथा
अटल अंतरभूत पूर्णांक pcibios_vaddr_is_ioport(व्योम __iomem *address)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PCI */

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_PCI_BRIDGE_H */
