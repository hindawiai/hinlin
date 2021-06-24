<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2008 Keith Packard <keithp@keithp.com>
 */

#अगर_अघोषित _LINUX_IO_MAPPING_H
#घोषणा _LINUX_IO_MAPPING_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/bug.h>
#समावेश <linux/पन.स>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/page.h>

/*
 * The io_mapping mechanism provides an असलtraction क्रम mapping
 * inभागidual pages from an io device to the CPU in an efficient fashion.
 *
 * See Documentation/driver-api/io-mapping.rst
 */

काष्ठा io_mapping अणु
	resource_माप_प्रकार base;
	अचिन्हित दीर्घ size;
	pgprot_t prot;
	व्योम __iomem *iomem;
पूर्ण;

#अगर_घोषित CONFIG_HAVE_ATOMIC_IOMAP

#समावेश <linux/pfn.h>
#समावेश <यंत्र/iomap.h>
/*
 * For small address space machines, mapping large objects
 * पूर्णांकo the kernel भव space isn't practical. Where
 * available, use fixmap support to dynamically map pages
 * of the object at run समय.
 */

अटल अंतरभूत काष्ठा io_mapping *
io_mapping_init_wc(काष्ठा io_mapping *iomap,
		   resource_माप_प्रकार base,
		   अचिन्हित दीर्घ size)
अणु
	pgprot_t prot;

	अगर (iomap_create_wc(base, size, &prot))
		वापस शून्य;

	iomap->base = base;
	iomap->size = size;
	iomap->prot = prot;
	वापस iomap;
पूर्ण

अटल अंतरभूत व्योम
io_mapping_fini(काष्ठा io_mapping *mapping)
अणु
	iomap_मुक्त(mapping->base, mapping->size);
पूर्ण

/* Atomic map/unmap */
अटल अंतरभूत व्योम __iomem *
io_mapping_map_atomic_wc(काष्ठा io_mapping *mapping,
			 अचिन्हित दीर्घ offset)
अणु
	resource_माप_प्रकार phys_addr;

	BUG_ON(offset >= mapping->size);
	phys_addr = mapping->base + offset;
	preempt_disable();
	pagefault_disable();
	वापस __iomap_local_pfn_prot(PHYS_PFN(phys_addr), mapping->prot);
पूर्ण

अटल अंतरभूत व्योम
io_mapping_unmap_atomic(व्योम __iomem *vaddr)
अणु
	kunmap_local_indexed((व्योम __क्रमce *)vaddr);
	pagefault_enable();
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __iomem *
io_mapping_map_local_wc(काष्ठा io_mapping *mapping, अचिन्हित दीर्घ offset)
अणु
	resource_माप_प्रकार phys_addr;

	BUG_ON(offset >= mapping->size);
	phys_addr = mapping->base + offset;
	वापस __iomap_local_pfn_prot(PHYS_PFN(phys_addr), mapping->prot);
पूर्ण

अटल अंतरभूत व्योम io_mapping_unmap_local(व्योम __iomem *vaddr)
अणु
	kunmap_local_indexed((व्योम __क्रमce *)vaddr);
पूर्ण

अटल अंतरभूत व्योम __iomem *
io_mapping_map_wc(काष्ठा io_mapping *mapping,
		  अचिन्हित दीर्घ offset,
		  अचिन्हित दीर्घ size)
अणु
	resource_माप_प्रकार phys_addr;

	BUG_ON(offset >= mapping->size);
	phys_addr = mapping->base + offset;

	वापस ioremap_wc(phys_addr, size);
पूर्ण

अटल अंतरभूत व्योम
io_mapping_unmap(व्योम __iomem *vaddr)
अणु
	iounmap(vaddr);
पूर्ण

#अन्यथा  /* HAVE_ATOMIC_IOMAP */

#समावेश <linux/uaccess.h>

/* Create the io_mapping object*/
अटल अंतरभूत काष्ठा io_mapping *
io_mapping_init_wc(काष्ठा io_mapping *iomap,
		   resource_माप_प्रकार base,
		   अचिन्हित दीर्घ size)
अणु
	iomap->iomem = ioremap_wc(base, size);
	अगर (!iomap->iomem)
		वापस शून्य;

	iomap->base = base;
	iomap->size = size;
#अगर defined(pgprot_noncached_wc) /* archs can't agree on a name ... */
	iomap->prot = pgprot_noncached_wc(PAGE_KERNEL);
#या_अगर defined(pgprot_ग_लिखोcombine)
	iomap->prot = pgprot_ग_लिखोcombine(PAGE_KERNEL);
#अन्यथा
	iomap->prot = pgprot_noncached(PAGE_KERNEL);
#पूर्ण_अगर

	वापस iomap;
पूर्ण

अटल अंतरभूत व्योम
io_mapping_fini(काष्ठा io_mapping *mapping)
अणु
	iounmap(mapping->iomem);
पूर्ण

/* Non-atomic map/unmap */
अटल अंतरभूत व्योम __iomem *
io_mapping_map_wc(काष्ठा io_mapping *mapping,
		  अचिन्हित दीर्घ offset,
		  अचिन्हित दीर्घ size)
अणु
	वापस mapping->iomem + offset;
पूर्ण

अटल अंतरभूत व्योम
io_mapping_unmap(व्योम __iomem *vaddr)
अणु
पूर्ण

/* Atomic map/unmap */
अटल अंतरभूत व्योम __iomem *
io_mapping_map_atomic_wc(काष्ठा io_mapping *mapping,
			 अचिन्हित दीर्घ offset)
अणु
	preempt_disable();
	pagefault_disable();
	वापस io_mapping_map_wc(mapping, offset, PAGE_SIZE);
पूर्ण

अटल अंतरभूत व्योम
io_mapping_unmap_atomic(व्योम __iomem *vaddr)
अणु
	io_mapping_unmap(vaddr);
	pagefault_enable();
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम __iomem *
io_mapping_map_local_wc(काष्ठा io_mapping *mapping, अचिन्हित दीर्घ offset)
अणु
	वापस io_mapping_map_wc(mapping, offset, PAGE_SIZE);
पूर्ण

अटल अंतरभूत व्योम io_mapping_unmap_local(व्योम __iomem *vaddr)
अणु
	io_mapping_unmap(vaddr);
पूर्ण

#पूर्ण_अगर /* !HAVE_ATOMIC_IOMAP */

अटल अंतरभूत काष्ठा io_mapping *
io_mapping_create_wc(resource_माप_प्रकार base,
		     अचिन्हित दीर्घ size)
अणु
	काष्ठा io_mapping *iomap;

	iomap = kदो_स्मृति(माप(*iomap), GFP_KERNEL);
	अगर (!iomap)
		वापस शून्य;

	अगर (!io_mapping_init_wc(iomap, base, size)) अणु
		kमुक्त(iomap);
		वापस शून्य;
	पूर्ण

	वापस iomap;
पूर्ण

अटल अंतरभूत व्योम
io_mapping_मुक्त(काष्ठा io_mapping *iomap)
अणु
	io_mapping_fini(iomap);
	kमुक्त(iomap);
पूर्ण

#पूर्ण_अगर /* _LINUX_IO_MAPPING_H */

पूर्णांक io_mapping_map_user(काष्ठा io_mapping *iomap, काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size);
