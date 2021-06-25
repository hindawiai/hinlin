<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 * Based on घातerpc version
 */

#अगर_अघोषित __ASM_MICROBLAZE_PCI_H
#घोषणा __ASM_MICROBLAZE_PCI_H
#अगर_घोषित __KERNEL__

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pci-bridge.h>

#घोषणा PCIBIOS_MIN_IO		0x1000
#घोषणा PCIBIOS_MIN_MEM		0x10000000

/* Values क्रम the `which' argument to sys_pciconfig_iobase syscall.  */
#घोषणा IOBASE_BRIDGE_NUMBER	0
#घोषणा IOBASE_MEMORY		1
#घोषणा IOBASE_IO		2
#घोषणा IOBASE_ISA_IO		3
#घोषणा IOBASE_ISA_MEM		4

#घोषणा pcibios_scan_all_fns(a, b)	0

/*
 * Set this to 1 अगर you want the kernel to re-assign all PCI
 * bus numbers (करोn't करो that on ppc64 yet !)
 */
#घोषणा pcibios_assign_all_busses()	0

बाह्य पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *bus);

/* Decide whether to display the करोमुख्य number in /proc */
बाह्य पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus);

काष्ठा vm_area_काष्ठा;

/* Tell PCI code what kind of PCI resource mappings we support */
#घोषणा HAVE_PCI_MMAP			1
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE	1
#घोषणा arch_can_pci_mmap_io()		1

बाह्य पूर्णांक pci_legacy_पढ़ो(काष्ठा pci_bus *bus, loff_t port, u32 *val,
			   माप_प्रकार count);
बाह्य पूर्णांक pci_legacy_ग_लिखो(काष्ठा pci_bus *bus, loff_t port, u32 val,
			   माप_प्रकार count);
बाह्य पूर्णांक pci_mmap_legacy_page_range(काष्ठा pci_bus *bus,
				      काष्ठा vm_area_काष्ठा *vma,
				      क्रमागत pci_mmap_state mmap_state);

#घोषणा HAVE_PCI_LEGACY	1

बाह्य व्योम pcibios_resource_survey(व्योम);

काष्ठा file;
बाह्य pgprot_t	pci_phys_mem_access_prot(काष्ठा file *file,
					 अचिन्हित दीर्घ pfn,
					 अचिन्हित दीर्घ size,
					 pgprot_t prot);

/* This part of code was originally in xilinx-pci.h */
#अगर_घोषित CONFIG_PCI_XILINX
बाह्य व्योम __init xilinx_pci_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __init xilinx_pci_init(व्योम) अणु वापस; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर /* __ASM_MICROBLAZE_PCI_H */
