<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ioport.h	Definitions of routines क्रम detecting, reserving and
 *		allocating प्रणाली resources.
 *
 * Authors:	Linus Torvalds
 */

#अगर_अघोषित _LINUX_IOPORT_H
#घोषणा _LINUX_IOPORT_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/bits.h>
#समावेश <linux/compiler.h>
#समावेश <linux/minmax.h>
#समावेश <linux/types.h>
/*
 * Resources are tree-like, allowing
 * nesting etc..
 */
काष्ठा resource अणु
	resource_माप_प्रकार start;
	resource_माप_प्रकार end;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ desc;
	काष्ठा resource *parent, *sibling, *child;
पूर्ण;

/*
 * IO resources have these defined flags.
 *
 * PCI devices expose these flags to userspace in the "resource" sysfs file,
 * so करोn't move them.
 */
#घोषणा IORESOURCE_BITS		0x000000ff	/* Bus-specअगरic bits */

#घोषणा IORESOURCE_TYPE_BITS	0x00001f00	/* Resource type */
#घोषणा IORESOURCE_IO		0x00000100	/* PCI/ISA I/O ports */
#घोषणा IORESOURCE_MEM		0x00000200
#घोषणा IORESOURCE_REG		0x00000300	/* Register offsets */
#घोषणा IORESOURCE_IRQ		0x00000400
#घोषणा IORESOURCE_DMA		0x00000800
#घोषणा IORESOURCE_BUS		0x00001000

#घोषणा IORESOURCE_PREFETCH	0x00002000	/* No side effects */
#घोषणा IORESOURCE_READONLY	0x00004000
#घोषणा IORESOURCE_CACHEABLE	0x00008000
#घोषणा IORESOURCE_RANGELENGTH	0x00010000
#घोषणा IORESOURCE_SHADOWABLE	0x00020000

#घोषणा IORESOURCE_SIZEALIGN	0x00040000	/* size indicates alignment */
#घोषणा IORESOURCE_STARTALIGN	0x00080000	/* start field is alignment */

#घोषणा IORESOURCE_MEM_64	0x00100000
#घोषणा IORESOURCE_WINDOW	0x00200000	/* क्रमwarded by bridge */
#घोषणा IORESOURCE_MUXED	0x00400000	/* Resource is software muxed */

#घोषणा IORESOURCE_EXT_TYPE_BITS 0x01000000	/* Resource extended types */
#घोषणा IORESOURCE_SYSRAM	0x01000000	/* System RAM (modअगरier) */

/* IORESOURCE_SYSRAM specअगरic bits. */
#घोषणा IORESOURCE_SYSRAM_DRIVER_MANAGED	0x02000000 /* Always detected via a driver. */
#घोषणा IORESOURCE_SYSRAM_MERGEABLE		0x04000000 /* Resource can be merged. */

#घोषणा IORESOURCE_EXCLUSIVE	0x08000000	/* Userland may not map this resource */

#घोषणा IORESOURCE_DISABLED	0x10000000
#घोषणा IORESOURCE_UNSET	0x20000000	/* No address asचिन्हित yet */
#घोषणा IORESOURCE_AUTO		0x40000000
#घोषणा IORESOURCE_BUSY		0x80000000	/* Driver has marked this resource busy */

/* I/O resource extended types */
#घोषणा IORESOURCE_SYSTEM_RAM		(IORESOURCE_MEM|IORESOURCE_SYSRAM)

/* PnP IRQ specअगरic bits (IORESOURCE_BITS) */
#घोषणा IORESOURCE_IRQ_HIGHEDGE		(1<<0)
#घोषणा IORESOURCE_IRQ_LOWEDGE		(1<<1)
#घोषणा IORESOURCE_IRQ_HIGHLEVEL	(1<<2)
#घोषणा IORESOURCE_IRQ_LOWLEVEL		(1<<3)
#घोषणा IORESOURCE_IRQ_SHAREABLE	(1<<4)
#घोषणा IORESOURCE_IRQ_OPTIONAL 	(1<<5)

/* PnP DMA specअगरic bits (IORESOURCE_BITS) */
#घोषणा IORESOURCE_DMA_TYPE_MASK	(3<<0)
#घोषणा IORESOURCE_DMA_8BIT		(0<<0)
#घोषणा IORESOURCE_DMA_8AND16BIT	(1<<0)
#घोषणा IORESOURCE_DMA_16BIT		(2<<0)

#घोषणा IORESOURCE_DMA_MASTER		(1<<2)
#घोषणा IORESOURCE_DMA_BYTE		(1<<3)
#घोषणा IORESOURCE_DMA_WORD		(1<<4)

#घोषणा IORESOURCE_DMA_SPEED_MASK	(3<<6)
#घोषणा IORESOURCE_DMA_COMPATIBLE	(0<<6)
#घोषणा IORESOURCE_DMA_TYPEA		(1<<6)
#घोषणा IORESOURCE_DMA_TYPEB		(2<<6)
#घोषणा IORESOURCE_DMA_TYPEF		(3<<6)

/* PnP memory I/O specअगरic bits (IORESOURCE_BITS) */
#घोषणा IORESOURCE_MEM_WRITEABLE	(1<<0)	/* dup: IORESOURCE_READONLY */
#घोषणा IORESOURCE_MEM_CACHEABLE	(1<<1)	/* dup: IORESOURCE_CACHEABLE */
#घोषणा IORESOURCE_MEM_RANGELENGTH	(1<<2)	/* dup: IORESOURCE_RANGELENGTH */
#घोषणा IORESOURCE_MEM_TYPE_MASK	(3<<3)
#घोषणा IORESOURCE_MEM_8BIT		(0<<3)
#घोषणा IORESOURCE_MEM_16BIT		(1<<3)
#घोषणा IORESOURCE_MEM_8AND16BIT	(2<<3)
#घोषणा IORESOURCE_MEM_32BIT		(3<<3)
#घोषणा IORESOURCE_MEM_SHADOWABLE	(1<<5)	/* dup: IORESOURCE_SHADOWABLE */
#घोषणा IORESOURCE_MEM_EXPANSIONROM	(1<<6)
#घोषणा IORESOURCE_MEM_NONPOSTED	(1<<7)

/* PnP I/O specअगरic bits (IORESOURCE_BITS) */
#घोषणा IORESOURCE_IO_16BIT_ADDR	(1<<0)
#घोषणा IORESOURCE_IO_FIXED		(1<<1)
#घोषणा IORESOURCE_IO_SPARSE		(1<<2)

/* PCI ROM control bits (IORESOURCE_BITS) */
#घोषणा IORESOURCE_ROM_ENABLE		(1<<0)	/* ROM is enabled, same as PCI_ROM_ADDRESS_ENABLE */
#घोषणा IORESOURCE_ROM_SHADOW		(1<<1)	/* Use RAM image, not ROM BAR */

/* PCI control bits.  Shares IORESOURCE_BITS with above PCI ROM.  */
#घोषणा IORESOURCE_PCI_FIXED		(1<<4)	/* Do not move resource */
#घोषणा IORESOURCE_PCI_EA_BEI		(1<<5)	/* BAR Equivalent Indicator */

/*
 * I/O Resource Descriptors
 *
 * Descriptors are used by walk_iomem_res_desc() and region_पूर्णांकersects()
 * क्रम searching a specअगरic resource range in the iomem table.  Assign
 * a new descriptor when a resource range supports the search पूर्णांकerfaces.
 * Otherwise, resource.desc must be set to IORES_DESC_NONE (0).
 */
क्रमागत अणु
	IORES_DESC_NONE				= 0,
	IORES_DESC_CRASH_KERNEL			= 1,
	IORES_DESC_ACPI_TABLES			= 2,
	IORES_DESC_ACPI_NV_STORAGE		= 3,
	IORES_DESC_PERSISTENT_MEMORY		= 4,
	IORES_DESC_PERSISTENT_MEMORY_LEGACY	= 5,
	IORES_DESC_DEVICE_PRIVATE_MEMORY	= 6,
	IORES_DESC_RESERVED			= 7,
	IORES_DESC_SOFT_RESERVED		= 8,
पूर्ण;

/*
 * Flags controlling ioremap() behavior.
 */
क्रमागत अणु
	IORES_MAP_SYSTEM_RAM		= BIT(0),
	IORES_MAP_ENCRYPTED		= BIT(1),
पूर्ण;

/* helpers to define resources */
#घोषणा DEFINE_RES_NAMED(_start, _size, _name, _flags)			\
	अणु								\
		.start = (_start),					\
		.end = (_start) + (_size) - 1,				\
		.name = (_name),					\
		.flags = (_flags),					\
		.desc = IORES_DESC_NONE,				\
	पूर्ण

#घोषणा DEFINE_RES_IO_NAMED(_start, _size, _name)			\
	DEFINE_RES_NAMED((_start), (_size), (_name), IORESOURCE_IO)
#घोषणा DEFINE_RES_IO(_start, _size)					\
	DEFINE_RES_IO_NAMED((_start), (_size), शून्य)

#घोषणा DEFINE_RES_MEM_NAMED(_start, _size, _name)			\
	DEFINE_RES_NAMED((_start), (_size), (_name), IORESOURCE_MEM)
#घोषणा DEFINE_RES_MEM(_start, _size)					\
	DEFINE_RES_MEM_NAMED((_start), (_size), शून्य)

#घोषणा DEFINE_RES_IRQ_NAMED(_irq, _name)				\
	DEFINE_RES_NAMED((_irq), 1, (_name), IORESOURCE_IRQ)
#घोषणा DEFINE_RES_IRQ(_irq)						\
	DEFINE_RES_IRQ_NAMED((_irq), शून्य)

#घोषणा DEFINE_RES_DMA_NAMED(_dma, _name)				\
	DEFINE_RES_NAMED((_dma), 1, (_name), IORESOURCE_DMA)
#घोषणा DEFINE_RES_DMA(_dma)						\
	DEFINE_RES_DMA_NAMED((_dma), शून्य)

/* PC/ISA/whatever - the normal PC address spaces: IO and memory */
बाह्य काष्ठा resource ioport_resource;
बाह्य काष्ठा resource iomem_resource;

बाह्य काष्ठा resource *request_resource_conflict(काष्ठा resource *root, काष्ठा resource *new);
बाह्य पूर्णांक request_resource(काष्ठा resource *root, काष्ठा resource *new);
बाह्य पूर्णांक release_resource(काष्ठा resource *new);
व्योम release_child_resources(काष्ठा resource *new);
बाह्य व्योम reserve_region_with_split(काष्ठा resource *root,
			     resource_माप_प्रकार start, resource_माप_प्रकार end,
			     स्थिर अक्षर *name);
बाह्य काष्ठा resource *insert_resource_conflict(काष्ठा resource *parent, काष्ठा resource *new);
बाह्य पूर्णांक insert_resource(काष्ठा resource *parent, काष्ठा resource *new);
बाह्य व्योम insert_resource_expand_to_fit(काष्ठा resource *root, काष्ठा resource *new);
बाह्य पूर्णांक हटाओ_resource(काष्ठा resource *old);
बाह्य व्योम arch_हटाओ_reservations(काष्ठा resource *avail);
बाह्य पूर्णांक allocate_resource(काष्ठा resource *root, काष्ठा resource *new,
			     resource_माप_प्रकार size, resource_माप_प्रकार min,
			     resource_माप_प्रकार max, resource_माप_प्रकार align,
			     resource_माप_प्रकार (*alignf)(व्योम *,
						       स्थिर काष्ठा resource *,
						       resource_माप_प्रकार,
						       resource_माप_प्रकार),
			     व्योम *alignf_data);
काष्ठा resource *lookup_resource(काष्ठा resource *root, resource_माप_प्रकार start);
पूर्णांक adjust_resource(काष्ठा resource *res, resource_माप_प्रकार start,
		    resource_माप_प्रकार size);
resource_माप_प्रकार resource_alignment(काष्ठा resource *res);
अटल अंतरभूत resource_माप_प्रकार resource_size(स्थिर काष्ठा resource *res)
अणु
	वापस res->end - res->start + 1;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ resource_type(स्थिर काष्ठा resource *res)
अणु
	वापस res->flags & IORESOURCE_TYPE_BITS;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ resource_ext_type(स्थिर काष्ठा resource *res)
अणु
	वापस res->flags & IORESOURCE_EXT_TYPE_BITS;
पूर्ण
/* True अगरf r1 completely contains r2 */
अटल अंतरभूत bool resource_contains(काष्ठा resource *r1, काष्ठा resource *r2)
अणु
	अगर (resource_type(r1) != resource_type(r2))
		वापस false;
	अगर (r1->flags & IORESOURCE_UNSET || r2->flags & IORESOURCE_UNSET)
		वापस false;
	वापस r1->start <= r2->start && r1->end >= r2->end;
पूर्ण

/* True अगर any part of r1 overlaps r2 */
अटल अंतरभूत bool resource_overlaps(काष्ठा resource *r1, काष्ठा resource *r2)
अणु
       वापस r1->start <= r2->end && r1->end >= r2->start;
पूर्ण

अटल अंतरभूत bool
resource_पूर्णांकersection(काष्ठा resource *r1, काष्ठा resource *r2, काष्ठा resource *r)
अणु
	अगर (!resource_overlaps(r1, r2))
		वापस false;
	r->start = max(r1->start, r2->start);
	r->end = min(r1->end, r2->end);
	वापस true;
पूर्ण

अटल अंतरभूत bool
resource_जोड़(काष्ठा resource *r1, काष्ठा resource *r2, काष्ठा resource *r)
अणु
	अगर (!resource_overlaps(r1, r2))
		वापस false;
	r->start = min(r1->start, r2->start);
	r->end = max(r1->end, r2->end);
	वापस true;
पूर्ण

/* Convenience लघुhand with allocation */
#घोषणा request_region(start,n,name)		__request_region(&ioport_resource, (start), (n), (name), 0)
#घोषणा request_muxed_region(start,n,name)	__request_region(&ioport_resource, (start), (n), (name), IORESOURCE_MUXED)
#घोषणा __request_mem_region(start,n,name, excl) __request_region(&iomem_resource, (start), (n), (name), excl)
#घोषणा request_mem_region(start,n,name) __request_region(&iomem_resource, (start), (n), (name), 0)
#घोषणा request_mem_region_exclusive(start,n,name) \
	__request_region(&iomem_resource, (start), (n), (name), IORESOURCE_EXCLUSIVE)
#घोषणा नाम_region(region, newname) करो अणु (region)->name = (newname); पूर्ण जबतक (0)

बाह्य काष्ठा resource * __request_region(काष्ठा resource *,
					resource_माप_प्रकार start,
					resource_माप_प्रकार n,
					स्थिर अक्षर *name, पूर्णांक flags);

/* Compatibility cruft */
#घोषणा release_region(start,n)	__release_region(&ioport_resource, (start), (n))
#घोषणा release_mem_region(start,n)	__release_region(&iomem_resource, (start), (n))

बाह्य व्योम __release_region(काष्ठा resource *, resource_माप_प्रकार,
				resource_माप_प्रकार);
#अगर_घोषित CONFIG_MEMORY_HOTREMOVE
बाह्य व्योम release_mem_region_adjustable(resource_माप_प्रकार, resource_माप_प्रकार);
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
बाह्य व्योम merge_प्रणाली_ram_resource(काष्ठा resource *res);
#पूर्ण_अगर

/* Wrappers क्रम managed devices */
काष्ठा device;

बाह्य पूर्णांक devm_request_resource(काष्ठा device *dev, काष्ठा resource *root,
				 काष्ठा resource *new);
बाह्य व्योम devm_release_resource(काष्ठा device *dev, काष्ठा resource *new);

#घोषणा devm_request_region(dev,start,n,name) \
	__devm_request_region(dev, &ioport_resource, (start), (n), (name))
#घोषणा devm_request_mem_region(dev,start,n,name) \
	__devm_request_region(dev, &iomem_resource, (start), (n), (name))

बाह्य काष्ठा resource * __devm_request_region(काष्ठा device *dev,
				काष्ठा resource *parent, resource_माप_प्रकार start,
				resource_माप_प्रकार n, स्थिर अक्षर *name);

#घोषणा devm_release_region(dev, start, n) \
	__devm_release_region(dev, &ioport_resource, (start), (n))
#घोषणा devm_release_mem_region(dev, start, n) \
	__devm_release_region(dev, &iomem_resource, (start), (n))

बाह्य व्योम __devm_release_region(काष्ठा device *dev, काष्ठा resource *parent,
				  resource_माप_प्रकार start, resource_माप_प्रकार n);
बाह्य पूर्णांक iomem_map_sanity_check(resource_माप_प्रकार addr, अचिन्हित दीर्घ size);
बाह्य bool iomem_is_exclusive(u64 addr);

बाह्य पूर्णांक
walk_प्रणाली_ram_range(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages,
		व्योम *arg, पूर्णांक (*func)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, व्योम *));
बाह्य पूर्णांक
walk_mem_res(u64 start, u64 end, व्योम *arg,
	     पूर्णांक (*func)(काष्ठा resource *, व्योम *));
बाह्य पूर्णांक
walk_प्रणाली_ram_res(u64 start, u64 end, व्योम *arg,
		    पूर्णांक (*func)(काष्ठा resource *, व्योम *));
बाह्य पूर्णांक
walk_iomem_res_desc(अचिन्हित दीर्घ desc, अचिन्हित दीर्घ flags, u64 start, u64 end,
		    व्योम *arg, पूर्णांक (*func)(काष्ठा resource *, व्योम *));

काष्ठा resource *devm_request_मुक्त_mem_region(काष्ठा device *dev,
		काष्ठा resource *base, अचिन्हित दीर्घ size);
काष्ठा resource *request_मुक्त_mem_region(काष्ठा resource *base,
		अचिन्हित दीर्घ size, स्थिर अक्षर *name);

अटल अंतरभूत व्योम irqresource_disabled(काष्ठा resource *res, u32 irq)
अणु
	res->start = irq;
	res->end = irq;
	res->flags |= IORESOURCE_IRQ | IORESOURCE_DISABLED | IORESOURCE_UNSET;
पूर्ण

बाह्य काष्ठा address_space *iomem_get_mapping(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर	/* _LINUX_IOPORT_H */
