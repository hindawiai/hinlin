<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_PCI_H
#घोषणा __ALPHA_PCI_H

#अगर_घोषित __KERNEL__

#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <यंत्र/machvec.h>

/*
 * The following काष्ठाure is used to manage multiple PCI busses.
 */

काष्ठा pci_iommu_arena;
काष्ठा page;

/* A controller.  Used to manage multiple PCI busses.  */

काष्ठा pci_controller अणु
	काष्ठा pci_controller *next;
        काष्ठा pci_bus *bus;
	काष्ठा resource *io_space;
	काष्ठा resource *mem_space;

	/* The following are क्रम reporting to userland.  The invariant is
	   that अगर we report a BWX-capable dense memory, we करो not report
	   a sparse memory at all, even अगर it exists.  */
	अचिन्हित दीर्घ sparse_mem_base;
	अचिन्हित दीर्घ dense_mem_base;
	अचिन्हित दीर्घ sparse_io_base;
	अचिन्हित दीर्घ dense_io_base;

	/* This one's for the kernel only.  It's in KSEG somewhere.  */
	अचिन्हित दीर्घ config_space_base;

	अचिन्हित पूर्णांक index;
	/* For compatibility with current (as of July 2003) pciutils
	   and XFree86. Eventually will be हटाओd. */
	अचिन्हित पूर्णांक need_करोमुख्य_info;

	काष्ठा pci_iommu_arena *sg_pci;
	काष्ठा pci_iommu_arena *sg_isa;

	व्योम *sysdata;
पूर्ण;

/* Override the logic in pci_scan_bus क्रम skipping alपढ़ोy-configured
   bus numbers.  */

#घोषणा pcibios_assign_all_busses()	1

#घोषणा PCIBIOS_MIN_IO		alpha_mv.min_io_address
#घोषणा PCIBIOS_MIN_MEM		alpha_mv.min_mem_address

/* IOMMU controls.  */

/* TODO: पूर्णांकegrate with include/यंत्र-generic/pci.h ? */
अटल अंतरभूत पूर्णांक pci_get_legacy_ide_irq(काष्ठा pci_dev *dev, पूर्णांक channel)
अणु
	वापस channel ? 15 : 14;
पूर्ण

#घोषणा pci_करोमुख्य_nr(bus) ((काष्ठा pci_controller *)(bus)->sysdata)->index

अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_controller *hose = bus->sysdata;
	वापस hose->need_करोमुख्य_info;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

/* Values क्रम the `which' argument to sys_pciconfig_iobase.  */
#घोषणा IOBASE_HOSE		0
#घोषणा IOBASE_SPARSE_MEM	1
#घोषणा IOBASE_DENSE_MEM	2
#घोषणा IOBASE_SPARSE_IO	3
#घोषणा IOBASE_DENSE_IO		4
#घोषणा IOBASE_ROOT_BUS		5
#घोषणा IOBASE_FROM_HOSE	0x10000

बाह्य काष्ठा pci_dev *isa_bridge;

बाह्य पूर्णांक pci_legacy_पढ़ो(काष्ठा pci_bus *bus, loff_t port, u32 *val,
			   माप_प्रकार count);
बाह्य पूर्णांक pci_legacy_ग_लिखो(काष्ठा pci_bus *bus, loff_t port, u32 val,
			    माप_प्रकार count);
बाह्य पूर्णांक pci_mmap_legacy_page_range(काष्ठा pci_bus *bus,
				      काष्ठा vm_area_काष्ठा *vma,
				      क्रमागत pci_mmap_state mmap_state);
बाह्य व्योम pci_adjust_legacy_attr(काष्ठा pci_bus *bus,
				   क्रमागत pci_mmap_state mmap_type);
#घोषणा HAVE_PCI_LEGACY	1

बाह्य पूर्णांक pci_create_resource_files(काष्ठा pci_dev *dev);
बाह्य व्योम pci_हटाओ_resource_files(काष्ठा pci_dev *dev);

#पूर्ण_अगर /* __ALPHA_PCI_H */
