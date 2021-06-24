<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MEMREMAP_H_
#घोषणा _LINUX_MEMREMAP_H_
#समावेश <linux/range.h>
#समावेश <linux/ioport.h>
#समावेश <linux/percpu-refcount.h>

काष्ठा resource;
काष्ठा device;

/**
 * काष्ठा vmem_alपंचांगap - pre-allocated storage क्रम vmemmap_populate
 * @base_pfn: base of the entire dev_pagemap mapping
 * @reserve: pages mapped, but reserved क्रम driver use (relative to @base)
 * @मुक्त: मुक्त pages set aside in the mapping क्रम memmap storage
 * @align: pages reserved to meet allocation alignments
 * @alloc: track pages consumed, निजी to vmemmap_populate()
 */
काष्ठा vmem_alपंचांगap अणु
	अचिन्हित दीर्घ base_pfn;
	स्थिर अचिन्हित दीर्घ end_pfn;
	स्थिर अचिन्हित दीर्घ reserve;
	अचिन्हित दीर्घ मुक्त;
	अचिन्हित दीर्घ align;
	अचिन्हित दीर्घ alloc;
पूर्ण;

/*
 * Specialize ZONE_DEVICE memory पूर्णांकo multiple types each having dअगरferents
 * usage.
 *
 * MEMORY_DEVICE_PRIVATE:
 * Device memory that is not directly addressable by the CPU: CPU can neither
 * पढ़ो nor ग_लिखो निजी memory. In this हाल, we करो still have काष्ठा pages
 * backing the device memory. Doing so simplअगरies the implementation, but it is
 * important to remember that there are certain poपूर्णांकs at which the काष्ठा page
 * must be treated as an opaque object, rather than a "normal" काष्ठा page.
 *
 * A more complete discussion of unaddressable memory may be found in
 * include/linux/hmm.h and Documentation/vm/hmm.rst.
 *
 * MEMORY_DEVICE_FS_DAX:
 * Host memory that has similar access semantics as System RAM i.e. DMA
 * coherent and supports page pinning. In support of coordinating page
 * pinning vs other operations MEMORY_DEVICE_FS_DAX arranges क्रम a
 * wakeup event whenever a page is unpinned and becomes idle. This
 * wakeup is used to coordinate physical address space management (ex:
 * fs truncate/hole punch) vs pinned pages (ex: device dma).
 *
 * MEMORY_DEVICE_GENERIC:
 * Host memory that has similar access semantics as System RAM i.e. DMA
 * coherent and supports page pinning. This is क्रम example used by DAX devices
 * that expose memory using a अक्षरacter device.
 *
 * MEMORY_DEVICE_PCI_P2PDMA:
 * Device memory residing in a PCI BAR पूर्णांकended क्रम use with Peer-to-Peer
 * transactions.
 */
क्रमागत memory_type अणु
	/* 0 is reserved to catch uninitialized type fields */
	MEMORY_DEVICE_PRIVATE = 1,
	MEMORY_DEVICE_FS_DAX,
	MEMORY_DEVICE_GENERIC,
	MEMORY_DEVICE_PCI_P2PDMA,
पूर्ण;

काष्ठा dev_pagemap_ops अणु
	/*
	 * Called once the page refcount reaches 1.  (ZONE_DEVICE pages never
	 * reach 0 refcount unless there is a refcount bug. This allows the
	 * device driver to implement its own memory management.)
	 */
	व्योम (*page_मुक्त)(काष्ठा page *page);

	/*
	 * Transition the refcount in काष्ठा dev_pagemap to the dead state.
	 */
	व्योम (*समाप्त)(काष्ठा dev_pagemap *pgmap);

	/*
	 * Wait क्रम refcount in काष्ठा dev_pagemap to be idle and reap it.
	 */
	व्योम (*cleanup)(काष्ठा dev_pagemap *pgmap);

	/*
	 * Used क्रम निजी (un-addressable) device memory only.  Must migrate
	 * the page back to a CPU accessible page.
	 */
	vm_fault_t (*migrate_to_ram)(काष्ठा vm_fault *vmf);
पूर्ण;

#घोषणा PGMAP_ALTMAP_VALID	(1 << 0)

/**
 * काष्ठा dev_pagemap - metadata क्रम ZONE_DEVICE mappings
 * @alपंचांगap: pre-allocated/reserved memory क्रम vmemmap allocations
 * @ref: reference count that pins the devm_memremap_pages() mapping
 * @पूर्णांकernal_ref: पूर्णांकernal reference अगर @ref is not provided by the caller
 * @करोne: completion क्रम @पूर्णांकernal_ref
 * @type: memory type: see MEMORY_* in memory_hotplug.h
 * @flags: PGMAP_* flags to specअगरy defailed behavior
 * @ops: method table
 * @owner: an opaque poपूर्णांकer identअगरying the entity that manages this
 *	instance.  Used by various helpers to make sure that no
 *	क्रमeign ZONE_DEVICE memory is accessed.
 * @nr_range: number of ranges to be mapped
 * @range: range to be mapped when nr_range == 1
 * @ranges: array of ranges to be mapped when nr_range > 1
 */
काष्ठा dev_pagemap अणु
	काष्ठा vmem_alपंचांगap alपंचांगap;
	काष्ठा percpu_ref *ref;
	काष्ठा percpu_ref पूर्णांकernal_ref;
	काष्ठा completion करोne;
	क्रमागत memory_type type;
	अचिन्हित पूर्णांक flags;
	स्थिर काष्ठा dev_pagemap_ops *ops;
	व्योम *owner;
	पूर्णांक nr_range;
	जोड़ अणु
		काष्ठा range range;
		काष्ठा range ranges[0];
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा vmem_alपंचांगap *pgmap_alपंचांगap(काष्ठा dev_pagemap *pgmap)
अणु
	अगर (pgmap->flags & PGMAP_ALTMAP_VALID)
		वापस &pgmap->alपंचांगap;
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_ZONE_DEVICE
व्योम *memremap_pages(काष्ठा dev_pagemap *pgmap, पूर्णांक nid);
व्योम memunmap_pages(काष्ठा dev_pagemap *pgmap);
व्योम *devm_memremap_pages(काष्ठा device *dev, काष्ठा dev_pagemap *pgmap);
व्योम devm_memunmap_pages(काष्ठा device *dev, काष्ठा dev_pagemap *pgmap);
काष्ठा dev_pagemap *get_dev_pagemap(अचिन्हित दीर्घ pfn,
		काष्ठा dev_pagemap *pgmap);
bool pgmap_pfn_valid(काष्ठा dev_pagemap *pgmap, अचिन्हित दीर्घ pfn);

अचिन्हित दीर्घ vmem_alपंचांगap_offset(काष्ठा vmem_alपंचांगap *alपंचांगap);
व्योम vmem_alपंचांगap_मुक्त(काष्ठा vmem_alपंचांगap *alपंचांगap, अचिन्हित दीर्घ nr_pfns);
अचिन्हित दीर्घ memremap_compat_align(व्योम);
#अन्यथा
अटल अंतरभूत व्योम *devm_memremap_pages(काष्ठा device *dev,
		काष्ठा dev_pagemap *pgmap)
अणु
	/*
	 * Fail attempts to call devm_memremap_pages() without
	 * ZONE_DEVICE support enabled, this requires callers to fall
	 * back to plain devm_memremap() based on config
	 */
	WARN_ON_ONCE(1);
	वापस ERR_PTR(-ENXIO);
पूर्ण

अटल अंतरभूत व्योम devm_memunmap_pages(काष्ठा device *dev,
		काष्ठा dev_pagemap *pgmap)
अणु
पूर्ण

अटल अंतरभूत काष्ठा dev_pagemap *get_dev_pagemap(अचिन्हित दीर्घ pfn,
		काष्ठा dev_pagemap *pgmap)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool pgmap_pfn_valid(काष्ठा dev_pagemap *pgmap, अचिन्हित दीर्घ pfn)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ vmem_alपंचांगap_offset(काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम vmem_alपंचांगap_मुक्त(काष्ठा vmem_alपंचांगap *alपंचांगap,
		अचिन्हित दीर्घ nr_pfns)
अणु
पूर्ण

/* when memremap_pages() is disabled all archs can remap a single page */
अटल अंतरभूत अचिन्हित दीर्घ memremap_compat_align(व्योम)
अणु
	वापस PAGE_SIZE;
पूर्ण
#पूर्ण_अगर /* CONFIG_ZONE_DEVICE */

अटल अंतरभूत व्योम put_dev_pagemap(काष्ठा dev_pagemap *pgmap)
अणु
	अगर (pgmap)
		percpu_ref_put(pgmap->ref);
पूर्ण

#पूर्ण_अगर /* _LINUX_MEMREMAP_H_ */
