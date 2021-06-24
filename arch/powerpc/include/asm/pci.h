<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __ASM_POWERPC_PCI_H
#घोषणा __ASM_POWERPC_PCI_H
#अगर_घोषित __KERNEL__

/*
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>

/* Return values क्रम pci_controller_ops.probe_mode function */
#घोषणा PCI_PROBE_NONE		-1	/* Don't look at this bus at all */
#घोषणा PCI_PROBE_NORMAL	0	/* Do normal PCI probing */
#घोषणा PCI_PROBE_DEVTREE	1	/* Instantiate from device tree */

#घोषणा PCIBIOS_MIN_IO		0x1000
#घोषणा PCIBIOS_MIN_MEM		0x10000000

/* Values क्रम the `which' argument to sys_pciconfig_iobase syscall.  */
#घोषणा IOBASE_BRIDGE_NUMBER	0
#घोषणा IOBASE_MEMORY		1
#घोषणा IOBASE_IO		2
#घोषणा IOBASE_ISA_IO		3
#घोषणा IOBASE_ISA_MEM		4

/*
 * Set this to 1 अगर you want the kernel to re-assign all PCI
 * bus numbers (करोn't करो that on ppc64 yet !)
 */
#घोषणा pcibios_assign_all_busses() \
	(pci_has_flag(PCI_REASSIGN_ALL_BUS))

#घोषणा HAVE_ARCH_PCI_GET_LEGACY_IDE_IRQ
अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	अगर (ppc_md.pci_get_legacy_ide_irq)
		वापस ppc_md.pci_get_legacy_ide_irq(dev, channel);
	वापस channel ? 15 : 14;
पूर्ण

#अगर_घोषित CONFIG_PCI
बाह्य व्योम set_pci_dma_ops(स्थिर काष्ठा dma_map_ops *dma_ops);
#अन्यथा	/* CONFIG_PCI */
#घोषणा set_pci_dma_ops(d)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64

/*
 * We want to aव्योम touching the cacheline size or MWI bit.
 * pSeries firmware sets the cacheline size (which is not the cpu cacheline
 * size in all हालs) and hardware treats MWI the same as memory ग_लिखो.
 */
#घोषणा PCI_DISABLE_MWI

#पूर्ण_अगर /* CONFIG_PPC64 */

बाह्य पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *bus);

/* Decide whether to display the करोमुख्य number in /proc */
बाह्य पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus);

काष्ठा vm_area_काष्ठा;

/* Tell PCI code what kind of PCI resource mappings we support */
#घोषणा HAVE_PCI_MMAP			1
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE	1
#घोषणा arch_can_pci_mmap_io()		1
#घोषणा arch_can_pci_mmap_wc()		1

बाह्य पूर्णांक pci_legacy_पढ़ो(काष्ठा pci_bus *bus, loff_t port, u32 *val,
			   माप_प्रकार count);
बाह्य पूर्णांक pci_legacy_ग_लिखो(काष्ठा pci_bus *bus, loff_t port, u32 val,
			   माप_प्रकार count);
बाह्य पूर्णांक pci_mmap_legacy_page_range(काष्ठा pci_bus *bus,
				      काष्ठा vm_area_काष्ठा *vma,
				      क्रमागत pci_mmap_state mmap_state);

#घोषणा HAVE_PCI_LEGACY	1

बाह्य व्योम pcibios_claim_one_bus(काष्ठा pci_bus *b);

बाह्य व्योम pcibios_finish_adding_to_bus(काष्ठा pci_bus *bus);

बाह्य व्योम pcibios_resource_survey(व्योम);

बाह्य काष्ठा pci_controller *init_phb_dynamic(काष्ठा device_node *dn);
बाह्य पूर्णांक हटाओ_phb_dynamic(काष्ठा pci_controller *phb);

बाह्य काष्ठा pci_dev *of_create_pci_dev(काष्ठा device_node *node,
					काष्ठा pci_bus *bus, पूर्णांक devfn);

बाह्य अचिन्हित पूर्णांक pci_parse_of_flags(u32 addr0, पूर्णांक bridge);

बाह्य व्योम of_scan_pci_bridge(काष्ठा pci_dev *dev);

बाह्य व्योम of_scan_bus(काष्ठा device_node *node, काष्ठा pci_bus *bus);
बाह्य व्योम of_rescan_bus(काष्ठा device_node *node, काष्ठा pci_bus *bus);

काष्ठा file;
बाह्य pgprot_t	pci_phys_mem_access_prot(काष्ठा file *file,
					 अचिन्हित दीर्घ pfn,
					 अचिन्हित दीर्घ size,
					 pgprot_t prot);

बाह्य resource_माप_प्रकार pcibios_io_space_offset(काष्ठा pci_controller *hose);
बाह्य व्योम pcibios_setup_bus_self(काष्ठा pci_bus *bus);
बाह्य व्योम pcibios_setup_phb_io_space(काष्ठा pci_controller *hose);
बाह्य व्योम pcibios_scan_phb(काष्ठा pci_controller *hose);

#पूर्ण_अगर	/* __KERNEL__ */

#पूर्ण_अगर /* __ASM_POWERPC_PCI_H */
