<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VMALLOC_H
#घोषणा _LINUX_VMALLOC_H

#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/llist.h>
#समावेश <यंत्र/page.h>		/* pgprot_t */
#समावेश <linux/rbtree.h>
#समावेश <linux/overflow.h>

#समावेश <यंत्र/vदो_स्मृति.h>

काष्ठा vm_area_काष्ठा;		/* vma defining user mapping in mm_types.h */
काष्ठा notअगरier_block;		/* in notअगरier.h */

/* bits in flags of vदो_स्मृति's vm_काष्ठा below */
#घोषणा VM_IOREMAP		0x00000001	/* ioremap() and मित्रs */
#घोषणा VM_ALLOC		0x00000002	/* vदो_स्मृति() */
#घोषणा VM_MAP			0x00000004	/* vmap()ed pages */
#घोषणा VM_USERMAP		0x00000008	/* suitable क्रम remap_vदो_स्मृति_range */
#घोषणा VM_DMA_COHERENT		0x00000010	/* dma_alloc_coherent */
#घोषणा VM_UNINITIALIZED	0x00000020	/* vm_काष्ठा is not fully initialized */
#घोषणा VM_NO_GUARD		0x00000040      /* करोn't add guard page */
#घोषणा VM_KASAN		0x00000080      /* has allocated kasan shaकरोw memory */
#घोषणा VM_FLUSH_RESET_PERMS	0x00000100	/* reset direct map and flush TLB on unmap, can't be मुक्तd in atomic context */
#घोषणा VM_MAP_PUT_PAGES	0x00000200	/* put pages and मुक्त array in vमुक्त */
#घोषणा VM_NO_HUGE_VMAP		0x00000400	/* क्रमce PAGE_SIZE pte mapping */

/*
 * VM_KASAN is used slighly dअगरferently depending on CONFIG_KASAN_VMALLOC.
 *
 * If IS_ENABLED(CONFIG_KASAN_VMALLOC), VM_KASAN is set on a vm_काष्ठा after
 * shaकरोw memory has been mapped. It's used to handle allocation errors so that
 * we करोn't try to poison shaकरोw on मुक्त अगर it was never allocated.
 *
 * Otherwise, VM_KASAN is set क्रम kasan_module_alloc() allocations and used to
 * determine which allocations need the module shaकरोw मुक्तd.
 */

/* bits [20..32] reserved क्रम arch specअगरic ioremap पूर्णांकernals */

/*
 * Maximum alignment क्रम ioremap() regions.
 * Can be overridden by arch-specअगरic value.
 */
#अगर_अघोषित IOREMAP_MAX_ORDER
#घोषणा IOREMAP_MAX_ORDER	(7 + PAGE_SHIFT)	/* 128 pages */
#पूर्ण_अगर

काष्ठा vm_काष्ठा अणु
	काष्ठा vm_काष्ठा	*next;
	व्योम			*addr;
	अचिन्हित दीर्घ		size;
	अचिन्हित दीर्घ		flags;
	काष्ठा page		**pages;
#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMALLOC
	अचिन्हित पूर्णांक		page_order;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		nr_pages;
	phys_addr_t		phys_addr;
	स्थिर व्योम		*caller;
पूर्ण;

काष्ठा vmap_area अणु
	अचिन्हित दीर्घ बहु_शुरू;
	अचिन्हित दीर्घ बहु_पूर्ण;

	काष्ठा rb_node rb_node;         /* address sorted rbtree */
	काष्ठा list_head list;          /* address sorted list */

	/*
	 * The following two variables can be packed, because
	 * a vmap_area object can be either:
	 *    1) in "free" tree (root is vmap_area_root)
	 *    2) or "busy" tree (root is मुक्त_vmap_area_root)
	 */
	जोड़ अणु
		अचिन्हित दीर्घ subtree_max_size; /* in "free" tree */
		काष्ठा vm_काष्ठा *vm;           /* in "busy" tree */
	पूर्ण;
पूर्ण;

/* archs that select HAVE_ARCH_HUGE_VMAP should override one or more of these */
#अगर_अघोषित arch_vmap_p4d_supported
अटल अंतरभूत bool arch_vmap_p4d_supported(pgprot_t prot)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_vmap_pud_supported
अटल अंतरभूत bool arch_vmap_pud_supported(pgprot_t prot)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_vmap_pmd_supported
अटल अंतरभूत bool arch_vmap_pmd_supported(pgprot_t prot)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 *	Highlevel APIs क्रम driver use
 */
बाह्य व्योम vm_unmap_ram(स्थिर व्योम *mem, अचिन्हित पूर्णांक count);
बाह्य व्योम *vm_map_ram(काष्ठा page **pages, अचिन्हित पूर्णांक count, पूर्णांक node);
बाह्य व्योम vm_unmap_aliases(व्योम);

#अगर_घोषित CONFIG_MMU
बाह्य व्योम __init vदो_स्मृति_init(व्योम);
बाह्य अचिन्हित दीर्घ vदो_स्मृति_nr_pages(व्योम);
#अन्यथा
अटल अंतरभूत व्योम vदो_स्मृति_init(व्योम)
अणु
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ vदो_स्मृति_nr_pages(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

बाह्य व्योम *vदो_स्मृति(अचिन्हित दीर्घ size);
बाह्य व्योम *vzalloc(अचिन्हित दीर्घ size);
बाह्य व्योम *vदो_स्मृति_user(अचिन्हित दीर्घ size);
बाह्य व्योम *vदो_स्मृति_node(अचिन्हित दीर्घ size, पूर्णांक node);
बाह्य व्योम *vzalloc_node(अचिन्हित दीर्घ size, पूर्णांक node);
बाह्य व्योम *vदो_स्मृति_32(अचिन्हित दीर्घ size);
बाह्य व्योम *vदो_स्मृति_32_user(अचिन्हित दीर्घ size);
बाह्य व्योम *__vदो_स्मृति(अचिन्हित दीर्घ size, gfp_t gfp_mask);
बाह्य व्योम *__vदो_स्मृति_node_range(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
			अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, gfp_t gfp_mask,
			pgprot_t prot, अचिन्हित दीर्घ vm_flags, पूर्णांक node,
			स्थिर व्योम *caller);
व्योम *__vदो_स्मृति_node(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align, gfp_t gfp_mask,
		पूर्णांक node, स्थिर व्योम *caller);

बाह्य व्योम vमुक्त(स्थिर व्योम *addr);
बाह्य व्योम vमुक्त_atomic(स्थिर व्योम *addr);

बाह्य व्योम *vmap(काष्ठा page **pages, अचिन्हित पूर्णांक count,
			अचिन्हित दीर्घ flags, pgprot_t prot);
व्योम *vmap_pfn(अचिन्हित दीर्घ *pfns, अचिन्हित पूर्णांक count, pgprot_t prot);
बाह्य व्योम vunmap(स्थिर व्योम *addr);

बाह्य पूर्णांक remap_vदो_स्मृति_range_partial(काष्ठा vm_area_काष्ठा *vma,
				       अचिन्हित दीर्घ uaddr, व्योम *kaddr,
				       अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ size);

बाह्य पूर्णांक remap_vदो_स्मृति_range(काष्ठा vm_area_काष्ठा *vma, व्योम *addr,
							अचिन्हित दीर्घ pgoff);

/*
 * Architectures can set this mask to a combination of PGTBL_P?D_MODIFIED values
 * and let generic vदो_स्मृति and ioremap code know when arch_sync_kernel_mappings()
 * needs to be called.
 */
#अगर_अघोषित ARCH_PAGE_TABLE_SYNC_MASK
#घोषणा ARCH_PAGE_TABLE_SYNC_MASK 0
#पूर्ण_अगर

/*
 * There is no शेष implementation क्रम arch_sync_kernel_mappings(). It is
 * relied upon the compiler to optimize calls out अगर ARCH_PAGE_TABLE_SYNC_MASK
 * is 0.
 */
व्योम arch_sync_kernel_mappings(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

/*
 *	Lowlevel-APIs (not क्रम driver use!)
 */

अटल अंतरभूत माप_प्रकार get_vm_area_size(स्थिर काष्ठा vm_काष्ठा *area)
अणु
	अगर (!(area->flags & VM_NO_GUARD))
		/* वापस actual size without guard page */
		वापस area->size - PAGE_SIZE;
	अन्यथा
		वापस area->size;

पूर्ण

बाह्य काष्ठा vm_काष्ठा *get_vm_area(अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags);
बाह्य काष्ठा vm_काष्ठा *get_vm_area_caller(अचिन्हित दीर्घ size,
					अचिन्हित दीर्घ flags, स्थिर व्योम *caller);
बाह्य काष्ठा vm_काष्ठा *__get_vm_area_caller(अचिन्हित दीर्घ size,
					अचिन्हित दीर्घ flags,
					अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
					स्थिर व्योम *caller);
व्योम मुक्त_vm_area(काष्ठा vm_काष्ठा *area);
बाह्य काष्ठा vm_काष्ठा *हटाओ_vm_area(स्थिर व्योम *addr);
बाह्य काष्ठा vm_काष्ठा *find_vm_area(स्थिर व्योम *addr);

अटल अंतरभूत bool is_vm_area_hugepages(स्थिर व्योम *addr)
अणु
	/*
	 * This may not 100% tell अगर the area is mapped with > PAGE_SIZE
	 * page table entries, अगर क्रम some reason the architecture indicates
	 * larger sizes are available but decides not to use them, nothing
	 * prevents that. This only indicates the size of the physical page
	 * allocated in the vदो_स्मृति layer.
	 */
#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMALLOC
	वापस find_vm_area(addr)->page_order > 0;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_MMU
पूर्णांक vmap_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			phys_addr_t phys_addr, pgprot_t prot,
			अचिन्हित पूर्णांक max_page_shअगरt);
व्योम vunmap_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end);
अटल अंतरभूत व्योम set_vm_flush_reset_perms(व्योम *addr)
अणु
	काष्ठा vm_काष्ठा *vm = find_vm_area(addr);

	अगर (vm)
		vm->flags |= VM_FLUSH_RESET_PERMS;
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम set_vm_flush_reset_perms(व्योम *addr)
अणु
पूर्ण
#पूर्ण_अगर

/* क्रम /proc/kcore */
बाह्य दीर्घ vपढ़ो(अक्षर *buf, अक्षर *addr, अचिन्हित दीर्घ count);

/*
 *	Internals.  Dont't use..
 */
बाह्य काष्ठा list_head vmap_area_list;
बाह्य __init व्योम vm_area_add_early(काष्ठा vm_काष्ठा *vm);
बाह्य __init व्योम vm_area_रेजिस्टर_early(काष्ठा vm_काष्ठा *vm, माप_प्रकार align);

#अगर_घोषित CONFIG_SMP
# अगरdef CONFIG_MMU
काष्ठा vm_काष्ठा **pcpu_get_vm_areas(स्थिर अचिन्हित दीर्घ *offsets,
				     स्थिर माप_प्रकार *sizes, पूर्णांक nr_vms,
				     माप_प्रकार align);

व्योम pcpu_मुक्त_vm_areas(काष्ठा vm_काष्ठा **vms, पूर्णांक nr_vms);
# अन्यथा
अटल अंतरभूत काष्ठा vm_काष्ठा **
pcpu_get_vm_areas(स्थिर अचिन्हित दीर्घ *offsets,
		स्थिर माप_प्रकार *sizes, पूर्णांक nr_vms,
		माप_प्रकार align)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
pcpu_मुक्त_vm_areas(काष्ठा vm_काष्ठा **vms, पूर्णांक nr_vms)
अणु
पूर्ण
# endअगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
#घोषणा VMALLOC_TOTAL (VMALLOC_END - VMALLOC_START)
#अन्यथा
#घोषणा VMALLOC_TOTAL 0UL
#पूर्ण_अगर

पूर्णांक रेजिस्टर_vmap_purge_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_vmap_purge_notअगरier(काष्ठा notअगरier_block *nb);

#अगर defined(CONFIG_MMU) && defined(CONFIG_PRINTK)
bool vदो_स्मृति_dump_obj(व्योम *object);
#अन्यथा
अटल अंतरभूत bool vदो_स्मृति_dump_obj(व्योम *object) अणु वापस false; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_VMALLOC_H */
