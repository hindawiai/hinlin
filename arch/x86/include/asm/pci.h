<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PCI_H
#घोषणा _ASM_X86_PCI_H

#समावेश <linux/mm.h> /* क्रम काष्ठा page */
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/numa.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/x86_init.h>

काष्ठा pci_sysdata अणु
	पूर्णांक		करोमुख्य;		/* PCI करोमुख्य */
	पूर्णांक		node;		/* NUMA node */
#अगर_घोषित CONFIG_ACPI
	काष्ठा acpi_device *companion;	/* ACPI companion device */
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_64
	व्योम		*iommu;		/* IOMMU निजी data */
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_MSI_IRQ_DOMAIN
	व्योम		*fwnode;	/* IRQ करोमुख्य क्रम MSI assignment */
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_VMD)
	काष्ठा pci_dev	*vmd_dev;	/* VMD Device अगर in Intel VMD करोमुख्य */
#पूर्ण_अगर
पूर्ण;

बाह्य पूर्णांक pci_routeirq;
बाह्य पूर्णांक noioapicquirk;
बाह्य पूर्णांक noioapicreroute;

अटल अंतरभूत काष्ठा pci_sysdata *to_pci_sysdata(स्थिर काष्ठा pci_bus *bus)
अणु
	वापस bus->sysdata;
पूर्ण

#अगर_घोषित CONFIG_PCI

#अगर_घोषित CONFIG_PCI_DOMAINS
अटल अंतरभूत पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *bus)
अणु
	वापस to_pci_sysdata(bus)->करोमुख्य;
पूर्ण

अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	वापस pci_करोमुख्य_nr(bus);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_MSI_IRQ_DOMAIN
अटल अंतरभूत व्योम *_pci_root_bus_fwnode(काष्ठा pci_bus *bus)
अणु
	वापस to_pci_sysdata(bus)->fwnode;
पूर्ण

#घोषणा pci_root_bus_fwnode	_pci_root_bus_fwnode
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_VMD)
अटल अंतरभूत bool is_vmd(काष्ठा pci_bus *bus)
अणु
	वापस to_pci_sysdata(bus)->vmd_dev != शून्य;
पूर्ण
#अन्यथा
#घोषणा is_vmd(bus)		false
#पूर्ण_अगर /* CONFIG_VMD */

/* Can be used to override the logic in pci_scan_bus क्रम skipping
   alपढ़ोy-configured bus numbers - to be used क्रम buggy BIOSes
   or architectures with incomplete PCI setup by the loader */

बाह्य अचिन्हित पूर्णांक pcibios_assign_all_busses(व्योम);
बाह्य पूर्णांक pci_legacy_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक pcibios_assign_all_busses(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ pci_mem_start;
#घोषणा PCIBIOS_MIN_IO		0x1000
#घोषणा PCIBIOS_MIN_MEM		(pci_mem_start)

#घोषणा PCIBIOS_MIN_CARDBUS_IO	0x4000

बाह्य पूर्णांक pcibios_enabled;
व्योम pcibios_scan_root(पूर्णांक bus);

काष्ठा irq_routing_table *pcibios_get_irq_routing_table(व्योम);
पूर्णांक pcibios_set_irq_routing(काष्ठा pci_dev *dev, पूर्णांक pin, पूर्णांक irq);


#घोषणा HAVE_PCI_MMAP
#घोषणा arch_can_pci_mmap_wc()	pat_enabled()
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE

#अगर_घोषित CONFIG_PCI
बाह्य व्योम early_quirks(व्योम);
#अन्यथा
अटल अंतरभूत व्योम early_quirks(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम pci_iommu_alloc(व्योम);

/* generic pci stuff */
#समावेश <यंत्र-generic/pci.h>

#अगर_घोषित CONFIG_NUMA
/* Returns the node based on pci bus */
अटल अंतरभूत पूर्णांक __pcibus_to_node(स्थिर काष्ठा pci_bus *bus)
अणु
	वापस to_pci_sysdata(bus)->node;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cpumask *
cpumask_of_pcibus(स्थिर काष्ठा pci_bus *bus)
अणु
	पूर्णांक node;

	node = __pcibus_to_node(bus);
	वापस (node == NUMA_NO_NODE) ? cpu_online_mask :
			      cpumask_of_node(node);
पूर्ण
#पूर्ण_अगर

काष्ठा pci_setup_rom अणु
	काष्ठा setup_data data;
	uपूर्णांक16_t venकरोr;
	uपूर्णांक16_t devid;
	uपूर्णांक64_t pcilen;
	अचिन्हित दीर्घ segment;
	अचिन्हित दीर्घ bus;
	अचिन्हित दीर्घ device;
	अचिन्हित दीर्घ function;
	uपूर्णांक8_t romdata[0];
पूर्ण;

#पूर्ण_अगर /* _ASM_X86_PCI_H */
