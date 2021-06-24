<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_PCI_H
#घोषणा _ASM_IA64_PCI_H

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hw_irq.h>

काष्ठा pci_vector_काष्ठा अणु
	__u16 segment;	/* PCI Segment number */
	__u16 bus;	/* PCI Bus number */
	__u32 pci_id;	/* ACPI split 16 bits device, 16 bits function (see section 6.1.1) */
	__u8 pin;	/* PCI PIN (0 = A, 1 = B, 2 = C, 3 = D) */
	__u32 irq;	/* IRQ asचिन्हित */
पूर्ण;

/*
 * Can be used to override the logic in pci_scan_bus क्रम skipping alपढ़ोy-configured bus
 * numbers - to be used क्रम buggy BIOSes or architectures with incomplete PCI setup by the
 * loader.
 */
#घोषणा pcibios_assign_all_busses()     0

#घोषणा PCIBIOS_MIN_IO		0x1000
#घोषणा PCIBIOS_MIN_MEM		0x10000000

#घोषणा HAVE_PCI_MMAP
#घोषणा ARCH_GENERIC_PCI_MMAP_RESOURCE
#घोषणा arch_can_pci_mmap_wc()	1

#घोषणा HAVE_PCI_LEGACY
बाह्य पूर्णांक pci_mmap_legacy_page_range(काष्ठा pci_bus *bus,
				      काष्ठा vm_area_काष्ठा *vma,
				      क्रमागत pci_mmap_state mmap_state);

अक्षर *pci_get_legacy_mem(काष्ठा pci_bus *bus);
पूर्णांक pci_legacy_पढ़ो(काष्ठा pci_bus *bus, u16 port, u32 *val, u8 size);
पूर्णांक pci_legacy_ग_लिखो(काष्ठा pci_bus *bus, u16 port, u32 val, u8 size);

काष्ठा pci_controller अणु
	काष्ठा acpi_device *companion;
	व्योम *iommu;
	पूर्णांक segment;
	पूर्णांक node;		/* nearest node with memory or NUMA_NO_NODE क्रम global allocation */

	व्योम *platक्रमm_data;
पूर्ण;


#घोषणा PCI_CONTROLLER(busdev) ((काष्ठा pci_controller *) busdev->sysdata)
#घोषणा pci_करोमुख्य_nr(busdev)    (PCI_CONTROLLER(busdev)->segment)

बाह्य काष्ठा pci_ops pci_root_ops;

अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	वापस (pci_करोमुख्य_nr(bus) != 0);
पूर्ण

#घोषणा HAVE_ARCH_PCI_GET_LEGACY_IDE_IRQ
अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	वापस channel ? isa_irq_to_vector(15) : isa_irq_to_vector(14);
पूर्ण

#पूर्ण_अगर /* _ASM_IA64_PCI_H */
