<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  KVM guest address space mapping code
 *
 *    Copyright IBM Corp. 2007, 2020
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 *		 David Hildenbअक्रम <david@redhat.com>
 *		 Janosch Frank <frankja@linux.vnet.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pagewalk.h>
#समावेश <linux/swap.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/swapops.h>
#समावेश <linux/ksm.h>
#समावेश <linux/mman.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/gmap.h>
#समावेश <यंत्र/tlb.h>

#घोषणा GMAP_SHADOW_FAKE_TABLE 1ULL

/**
 * gmap_alloc - allocate and initialize a guest address space
 * @mm: poपूर्णांकer to the parent mm_काष्ठा
 * @limit: maximum address of the gmap address space
 *
 * Returns a guest address space काष्ठाure.
 */
अटल काष्ठा gmap *gmap_alloc(अचिन्हित दीर्घ limit)
अणु
	काष्ठा gmap *gmap;
	काष्ठा page *page;
	अचिन्हित दीर्घ *table;
	अचिन्हित दीर्घ etype, atype;

	अगर (limit < _REGION3_SIZE) अणु
		limit = _REGION3_SIZE - 1;
		atype = _ASCE_TYPE_SEGMENT;
		etype = _SEGMENT_ENTRY_EMPTY;
	पूर्ण अन्यथा अगर (limit < _REGION2_SIZE) अणु
		limit = _REGION2_SIZE - 1;
		atype = _ASCE_TYPE_REGION3;
		etype = _REGION3_ENTRY_EMPTY;
	पूर्ण अन्यथा अगर (limit < _REGION1_SIZE) अणु
		limit = _REGION1_SIZE - 1;
		atype = _ASCE_TYPE_REGION2;
		etype = _REGION2_ENTRY_EMPTY;
	पूर्ण अन्यथा अणु
		limit = -1UL;
		atype = _ASCE_TYPE_REGION1;
		etype = _REGION1_ENTRY_EMPTY;
	पूर्ण
	gmap = kzalloc(माप(काष्ठा gmap), GFP_KERNEL_ACCOUNT);
	अगर (!gmap)
		जाओ out;
	INIT_LIST_HEAD(&gmap->crst_list);
	INIT_LIST_HEAD(&gmap->children);
	INIT_LIST_HEAD(&gmap->pt_list);
	INIT_RADIX_TREE(&gmap->guest_to_host, GFP_KERNEL_ACCOUNT);
	INIT_RADIX_TREE(&gmap->host_to_guest, GFP_ATOMIC | __GFP_ACCOUNT);
	INIT_RADIX_TREE(&gmap->host_to_rmap, GFP_ATOMIC | __GFP_ACCOUNT);
	spin_lock_init(&gmap->guest_table_lock);
	spin_lock_init(&gmap->shaकरोw_lock);
	refcount_set(&gmap->ref_count, 1);
	page = alloc_pages(GFP_KERNEL_ACCOUNT, CRST_ALLOC_ORDER);
	अगर (!page)
		जाओ out_मुक्त;
	page->index = 0;
	list_add(&page->lru, &gmap->crst_list);
	table = (अचिन्हित दीर्घ *) page_to_phys(page);
	crst_table_init(table, etype);
	gmap->table = table;
	gmap->asce = atype | _ASCE_TABLE_LENGTH |
		_ASCE_USER_BITS | __pa(table);
	gmap->asce_end = limit;
	वापस gmap;

out_मुक्त:
	kमुक्त(gmap);
out:
	वापस शून्य;
पूर्ण

/**
 * gmap_create - create a guest address space
 * @mm: poपूर्णांकer to the parent mm_काष्ठा
 * @limit: maximum size of the gmap address space
 *
 * Returns a guest address space काष्ठाure.
 */
काष्ठा gmap *gmap_create(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ limit)
अणु
	काष्ठा gmap *gmap;
	अचिन्हित दीर्घ gmap_asce;

	gmap = gmap_alloc(limit);
	अगर (!gmap)
		वापस शून्य;
	gmap->mm = mm;
	spin_lock(&mm->context.lock);
	list_add_rcu(&gmap->list, &mm->context.gmap_list);
	अगर (list_is_singular(&mm->context.gmap_list))
		gmap_asce = gmap->asce;
	अन्यथा
		gmap_asce = -1UL;
	WRITE_ONCE(mm->context.gmap_asce, gmap_asce);
	spin_unlock(&mm->context.lock);
	वापस gmap;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_create);

अटल व्योम gmap_flush_tlb(काष्ठा gmap *gmap)
अणु
	अगर (MACHINE_HAS_IDTE)
		__tlb_flush_idte(gmap->asce);
	अन्यथा
		__tlb_flush_global();
पूर्ण

अटल व्योम gmap_radix_tree_मुक्त(काष्ठा radix_tree_root *root)
अणु
	काष्ठा radix_tree_iter iter;
	अचिन्हित दीर्घ indices[16];
	अचिन्हित दीर्घ index;
	व्योम __rcu **slot;
	पूर्णांक i, nr;

	/* A radix tree is मुक्तd by deleting all of its entries */
	index = 0;
	करो अणु
		nr = 0;
		radix_tree_क्रम_each_slot(slot, root, &iter, index) अणु
			indices[nr] = iter.index;
			अगर (++nr == 16)
				अवरोध;
		पूर्ण
		क्रम (i = 0; i < nr; i++) अणु
			index = indices[i];
			radix_tree_delete(root, index);
		पूर्ण
	पूर्ण जबतक (nr > 0);
पूर्ण

अटल व्योम gmap_rmap_radix_tree_मुक्त(काष्ठा radix_tree_root *root)
अणु
	काष्ठा gmap_rmap *rmap, *rnext, *head;
	काष्ठा radix_tree_iter iter;
	अचिन्हित दीर्घ indices[16];
	अचिन्हित दीर्घ index;
	व्योम __rcu **slot;
	पूर्णांक i, nr;

	/* A radix tree is मुक्तd by deleting all of its entries */
	index = 0;
	करो अणु
		nr = 0;
		radix_tree_क्रम_each_slot(slot, root, &iter, index) अणु
			indices[nr] = iter.index;
			अगर (++nr == 16)
				अवरोध;
		पूर्ण
		क्रम (i = 0; i < nr; i++) अणु
			index = indices[i];
			head = radix_tree_delete(root, index);
			gmap_क्रम_each_rmap_safe(rmap, rnext, head)
				kमुक्त(rmap);
		पूर्ण
	पूर्ण जबतक (nr > 0);
पूर्ण

/**
 * gmap_मुक्त - मुक्त a guest address space
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 *
 * No locks required. There are no references to this gmap anymore.
 */
अटल व्योम gmap_मुक्त(काष्ठा gmap *gmap)
अणु
	काष्ठा page *page, *next;

	/* Flush tlb of all gmaps (अगर not alपढ़ोy करोne क्रम shaकरोws) */
	अगर (!(gmap_is_shaकरोw(gmap) && gmap->हटाओd))
		gmap_flush_tlb(gmap);
	/* Free all segment & region tables. */
	list_क्रम_each_entry_safe(page, next, &gmap->crst_list, lru)
		__मुक्त_pages(page, CRST_ALLOC_ORDER);
	gmap_radix_tree_मुक्त(&gmap->guest_to_host);
	gmap_radix_tree_मुक्त(&gmap->host_to_guest);

	/* Free additional data क्रम a shaकरोw gmap */
	अगर (gmap_is_shaकरोw(gmap)) अणु
		/* Free all page tables. */
		list_क्रम_each_entry_safe(page, next, &gmap->pt_list, lru)
			page_table_मुक्त_pgste(page);
		gmap_rmap_radix_tree_मुक्त(&gmap->host_to_rmap);
		/* Release reference to the parent */
		gmap_put(gmap->parent);
	पूर्ण

	kमुक्त(gmap);
पूर्ण

/**
 * gmap_get - increase reference counter क्रम guest address space
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 *
 * Returns the gmap poपूर्णांकer
 */
काष्ठा gmap *gmap_get(काष्ठा gmap *gmap)
अणु
	refcount_inc(&gmap->ref_count);
	वापस gmap;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_get);

/**
 * gmap_put - decrease reference counter क्रम guest address space
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 *
 * If the reference counter reaches zero the guest address space is मुक्तd.
 */
व्योम gmap_put(काष्ठा gmap *gmap)
अणु
	अगर (refcount_dec_and_test(&gmap->ref_count))
		gmap_मुक्त(gmap);
पूर्ण
EXPORT_SYMBOL_GPL(gmap_put);

/**
 * gmap_हटाओ - हटाओ a guest address space but करो not मुक्त it yet
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 */
व्योम gmap_हटाओ(काष्ठा gmap *gmap)
अणु
	काष्ठा gmap *sg, *next;
	अचिन्हित दीर्घ gmap_asce;

	/* Remove all shaकरोw gmaps linked to this gmap */
	अगर (!list_empty(&gmap->children)) अणु
		spin_lock(&gmap->shaकरोw_lock);
		list_क्रम_each_entry_safe(sg, next, &gmap->children, list) अणु
			list_del(&sg->list);
			gmap_put(sg);
		पूर्ण
		spin_unlock(&gmap->shaकरोw_lock);
	पूर्ण
	/* Remove gmap from the pre-mm list */
	spin_lock(&gmap->mm->context.lock);
	list_del_rcu(&gmap->list);
	अगर (list_empty(&gmap->mm->context.gmap_list))
		gmap_asce = 0;
	अन्यथा अगर (list_is_singular(&gmap->mm->context.gmap_list))
		gmap_asce = list_first_entry(&gmap->mm->context.gmap_list,
					     काष्ठा gmap, list)->asce;
	अन्यथा
		gmap_asce = -1UL;
	WRITE_ONCE(gmap->mm->context.gmap_asce, gmap_asce);
	spin_unlock(&gmap->mm->context.lock);
	synchronize_rcu();
	/* Put reference */
	gmap_put(gmap);
पूर्ण
EXPORT_SYMBOL_GPL(gmap_हटाओ);

/**
 * gmap_enable - चयन primary space to the guest address space
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 */
व्योम gmap_enable(काष्ठा gmap *gmap)
अणु
	S390_lowcore.gmap = (अचिन्हित दीर्घ) gmap;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_enable);

/**
 * gmap_disable - चयन back to the standard primary address space
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 */
व्योम gmap_disable(काष्ठा gmap *gmap)
अणु
	S390_lowcore.gmap = 0UL;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_disable);

/**
 * gmap_get_enabled - get a poपूर्णांकer to the currently enabled gmap
 *
 * Returns a poपूर्णांकer to the currently enabled gmap. 0 अगर none is enabled.
 */
काष्ठा gmap *gmap_get_enabled(व्योम)
अणु
	वापस (काष्ठा gmap *) S390_lowcore.gmap;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_get_enabled);

/*
 * gmap_alloc_table is assumed to be called with mmap_lock held
 */
अटल पूर्णांक gmap_alloc_table(काष्ठा gmap *gmap, अचिन्हित दीर्घ *table,
			    अचिन्हित दीर्घ init, अचिन्हित दीर्घ gaddr)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ *new;

	/* since we करोnt मुक्त the gmap table until gmap_मुक्त we can unlock */
	page = alloc_pages(GFP_KERNEL_ACCOUNT, CRST_ALLOC_ORDER);
	अगर (!page)
		वापस -ENOMEM;
	new = (अचिन्हित दीर्घ *) page_to_phys(page);
	crst_table_init(new, init);
	spin_lock(&gmap->guest_table_lock);
	अगर (*table & _REGION_ENTRY_INVALID) अणु
		list_add(&page->lru, &gmap->crst_list);
		*table = (अचिन्हित दीर्घ) new | _REGION_ENTRY_LENGTH |
			(*table & _REGION_ENTRY_TYPE_MASK);
		page->index = gaddr;
		page = शून्य;
	पूर्ण
	spin_unlock(&gmap->guest_table_lock);
	अगर (page)
		__मुक्त_pages(page, CRST_ALLOC_ORDER);
	वापस 0;
पूर्ण

/**
 * __gmap_segment_gaddr - find भव address from segment poपूर्णांकer
 * @entry: poपूर्णांकer to a segment table entry in the guest address space
 *
 * Returns the भव address in the guest address space क्रम the segment
 */
अटल अचिन्हित दीर्घ __gmap_segment_gaddr(अचिन्हित दीर्घ *entry)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ offset, mask;

	offset = (अचिन्हित दीर्घ) entry / माप(अचिन्हित दीर्घ);
	offset = (offset & (PTRS_PER_PMD - 1)) * PMD_SIZE;
	mask = ~(PTRS_PER_PMD * माप(pmd_t) - 1);
	page = virt_to_page((व्योम *)((अचिन्हित दीर्घ) entry & mask));
	वापस page->index + offset;
पूर्ण

/**
 * __gmap_unlink_by_vmaddr - unlink a single segment via a host address
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 * @vmaddr: address in the host process address space
 *
 * Returns 1 अगर a TLB flush is required
 */
अटल पूर्णांक __gmap_unlink_by_vmaddr(काष्ठा gmap *gmap, अचिन्हित दीर्घ vmaddr)
अणु
	अचिन्हित दीर्घ *entry;
	पूर्णांक flush = 0;

	BUG_ON(gmap_is_shaकरोw(gmap));
	spin_lock(&gmap->guest_table_lock);
	entry = radix_tree_delete(&gmap->host_to_guest, vmaddr >> PMD_SHIFT);
	अगर (entry) अणु
		flush = (*entry != _SEGMENT_ENTRY_EMPTY);
		*entry = _SEGMENT_ENTRY_EMPTY;
	पूर्ण
	spin_unlock(&gmap->guest_table_lock);
	वापस flush;
पूर्ण

/**
 * __gmap_unmap_by_gaddr - unmap a single segment via a guest address
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 * @gaddr: address in the guest address space
 *
 * Returns 1 अगर a TLB flush is required
 */
अटल पूर्णांक __gmap_unmap_by_gaddr(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr)
अणु
	अचिन्हित दीर्घ vmaddr;

	vmaddr = (अचिन्हित दीर्घ) radix_tree_delete(&gmap->guest_to_host,
						   gaddr >> PMD_SHIFT);
	वापस vmaddr ? __gmap_unlink_by_vmaddr(gmap, vmaddr) : 0;
पूर्ण

/**
 * gmap_unmap_segment - unmap segment from the guest address space
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 * @to: address in the guest address space
 * @len: length of the memory area to unmap
 *
 * Returns 0 अगर the unmap succeeded, -EINVAL अगर not.
 */
पूर्णांक gmap_unmap_segment(काष्ठा gmap *gmap, अचिन्हित दीर्घ to, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ off;
	पूर्णांक flush;

	BUG_ON(gmap_is_shaकरोw(gmap));
	अगर ((to | len) & (PMD_SIZE - 1))
		वापस -EINVAL;
	अगर (len == 0 || to + len < to)
		वापस -EINVAL;

	flush = 0;
	mmap_ग_लिखो_lock(gmap->mm);
	क्रम (off = 0; off < len; off += PMD_SIZE)
		flush |= __gmap_unmap_by_gaddr(gmap, to + off);
	mmap_ग_लिखो_unlock(gmap->mm);
	अगर (flush)
		gmap_flush_tlb(gmap);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_unmap_segment);

/**
 * gmap_map_segment - map a segment to the guest address space
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 * @from: source address in the parent address space
 * @to: target address in the guest address space
 * @len: length of the memory area to map
 *
 * Returns 0 अगर the mmap succeeded, -EINVAL or -ENOMEM अगर not.
 */
पूर्णांक gmap_map_segment(काष्ठा gmap *gmap, अचिन्हित दीर्घ from,
		     अचिन्हित दीर्घ to, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ off;
	पूर्णांक flush;

	BUG_ON(gmap_is_shaकरोw(gmap));
	अगर ((from | to | len) & (PMD_SIZE - 1))
		वापस -EINVAL;
	अगर (len == 0 || from + len < from || to + len < to ||
	    from + len - 1 > TASK_SIZE_MAX || to + len - 1 > gmap->asce_end)
		वापस -EINVAL;

	flush = 0;
	mmap_ग_लिखो_lock(gmap->mm);
	क्रम (off = 0; off < len; off += PMD_SIZE) अणु
		/* Remove old translation */
		flush |= __gmap_unmap_by_gaddr(gmap, to + off);
		/* Store new translation */
		अगर (radix_tree_insert(&gmap->guest_to_host,
				      (to + off) >> PMD_SHIFT,
				      (व्योम *) from + off))
			अवरोध;
	पूर्ण
	mmap_ग_लिखो_unlock(gmap->mm);
	अगर (flush)
		gmap_flush_tlb(gmap);
	अगर (off >= len)
		वापस 0;
	gmap_unmap_segment(gmap, to, len);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_map_segment);

/**
 * __gmap_translate - translate a guest address to a user space address
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: guest address
 *
 * Returns user space address which corresponds to the guest address or
 * -EFAULT अगर no such mapping exists.
 * This function करोes not establish potentially missing page table entries.
 * The mmap_lock of the mm that beदीर्घs to the address space must be held
 * when this function माला_लो called.
 *
 * Note: Can also be called क्रम shaकरोw gmaps.
 */
अचिन्हित दीर्घ __gmap_translate(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr)
अणु
	अचिन्हित दीर्घ vmaddr;

	vmaddr = (अचिन्हित दीर्घ)
		radix_tree_lookup(&gmap->guest_to_host, gaddr >> PMD_SHIFT);
	/* Note: guest_to_host is empty क्रम a shaकरोw gmap */
	वापस vmaddr ? (vmaddr | (gaddr & ~PMD_MASK)) : -EFAULT;
पूर्ण
EXPORT_SYMBOL_GPL(__gmap_translate);

/**
 * gmap_translate - translate a guest address to a user space address
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: guest address
 *
 * Returns user space address which corresponds to the guest address or
 * -EFAULT अगर no such mapping exists.
 * This function करोes not establish potentially missing page table entries.
 */
अचिन्हित दीर्घ gmap_translate(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr)
अणु
	अचिन्हित दीर्घ rc;

	mmap_पढ़ो_lock(gmap->mm);
	rc = __gmap_translate(gmap, gaddr);
	mmap_पढ़ो_unlock(gmap->mm);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_translate);

/**
 * gmap_unlink - disconnect a page table from the gmap shaकरोw tables
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @table: poपूर्णांकer to the host page table
 * @vmaddr: vm address associated with the host page table
 */
व्योम gmap_unlink(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ *table,
		 अचिन्हित दीर्घ vmaddr)
अणु
	काष्ठा gmap *gmap;
	पूर्णांक flush;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(gmap, &mm->context.gmap_list, list) अणु
		flush = __gmap_unlink_by_vmaddr(gmap, vmaddr);
		अगर (flush)
			gmap_flush_tlb(gmap);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम gmap_pmdp_xchg(काष्ठा gmap *gmap, pmd_t *old, pmd_t new,
			   अचिन्हित दीर्घ gaddr);

/**
 * gmap_link - set up shaकरोw page tables to connect a host to a guest address
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: guest address
 * @vmaddr: vm address
 *
 * Returns 0 on success, -ENOMEM क्रम out of memory conditions, and -EFAULT
 * अगर the vm address is alपढ़ोy mapped to a dअगरferent guest segment.
 * The mmap_lock of the mm that beदीर्घs to the address space must be held
 * when this function माला_लो called.
 */
पूर्णांक __gmap_link(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr, अचिन्हित दीर्घ vmaddr)
अणु
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ *table;
	spinlock_t *ptl;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	u64 unprot;
	पूर्णांक rc;

	BUG_ON(gmap_is_shaकरोw(gmap));
	/* Create higher level tables in the gmap page table */
	table = gmap->table;
	अगर ((gmap->asce & _ASCE_TYPE_MASK) >= _ASCE_TYPE_REGION1) अणु
		table += (gaddr & _REGION1_INDEX) >> _REGION1_SHIFT;
		अगर ((*table & _REGION_ENTRY_INVALID) &&
		    gmap_alloc_table(gmap, table, _REGION2_ENTRY_EMPTY,
				     gaddr & _REGION1_MASK))
			वापस -ENOMEM;
		table = (अचिन्हित दीर्घ *)(*table & _REGION_ENTRY_ORIGIN);
	पूर्ण
	अगर ((gmap->asce & _ASCE_TYPE_MASK) >= _ASCE_TYPE_REGION2) अणु
		table += (gaddr & _REGION2_INDEX) >> _REGION2_SHIFT;
		अगर ((*table & _REGION_ENTRY_INVALID) &&
		    gmap_alloc_table(gmap, table, _REGION3_ENTRY_EMPTY,
				     gaddr & _REGION2_MASK))
			वापस -ENOMEM;
		table = (अचिन्हित दीर्घ *)(*table & _REGION_ENTRY_ORIGIN);
	पूर्ण
	अगर ((gmap->asce & _ASCE_TYPE_MASK) >= _ASCE_TYPE_REGION3) अणु
		table += (gaddr & _REGION3_INDEX) >> _REGION3_SHIFT;
		अगर ((*table & _REGION_ENTRY_INVALID) &&
		    gmap_alloc_table(gmap, table, _SEGMENT_ENTRY_EMPTY,
				     gaddr & _REGION3_MASK))
			वापस -ENOMEM;
		table = (अचिन्हित दीर्घ *)(*table & _REGION_ENTRY_ORIGIN);
	पूर्ण
	table += (gaddr & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
	/* Walk the parent mm page table */
	mm = gmap->mm;
	pgd = pgd_offset(mm, vmaddr);
	VM_BUG_ON(pgd_none(*pgd));
	p4d = p4d_offset(pgd, vmaddr);
	VM_BUG_ON(p4d_none(*p4d));
	pud = pud_offset(p4d, vmaddr);
	VM_BUG_ON(pud_none(*pud));
	/* large puds cannot yet be handled */
	अगर (pud_large(*pud))
		वापस -EFAULT;
	pmd = pmd_offset(pud, vmaddr);
	VM_BUG_ON(pmd_none(*pmd));
	/* Are we allowed to use huge pages? */
	अगर (pmd_large(*pmd) && !gmap->mm->context.allow_gmap_hpage_1m)
		वापस -EFAULT;
	/* Link gmap segment table entry location to page table. */
	rc = radix_tree_preload(GFP_KERNEL_ACCOUNT);
	अगर (rc)
		वापस rc;
	ptl = pmd_lock(mm, pmd);
	spin_lock(&gmap->guest_table_lock);
	अगर (*table == _SEGMENT_ENTRY_EMPTY) अणु
		rc = radix_tree_insert(&gmap->host_to_guest,
				       vmaddr >> PMD_SHIFT, table);
		अगर (!rc) अणु
			अगर (pmd_large(*pmd)) अणु
				*table = (pmd_val(*pmd) &
					  _SEGMENT_ENTRY_HARDWARE_BITS_LARGE)
					| _SEGMENT_ENTRY_GMAP_UC;
			पूर्ण अन्यथा
				*table = pmd_val(*pmd) &
					_SEGMENT_ENTRY_HARDWARE_BITS;
		पूर्ण
	पूर्ण अन्यथा अगर (*table & _SEGMENT_ENTRY_PROTECT &&
		   !(pmd_val(*pmd) & _SEGMENT_ENTRY_PROTECT)) अणु
		unprot = (u64)*table;
		unprot &= ~_SEGMENT_ENTRY_PROTECT;
		unprot |= _SEGMENT_ENTRY_GMAP_UC;
		gmap_pmdp_xchg(gmap, (pmd_t *)table, __pmd(unprot), gaddr);
	पूर्ण
	spin_unlock(&gmap->guest_table_lock);
	spin_unlock(ptl);
	radix_tree_preload_end();
	वापस rc;
पूर्ण

/**
 * gmap_fault - resolve a fault on a guest address
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: guest address
 * @fault_flags: flags to pass करोwn to handle_mm_fault()
 *
 * Returns 0 on success, -ENOMEM क्रम out of memory conditions, and -EFAULT
 * अगर the vm address is alपढ़ोy mapped to a dअगरferent guest segment.
 */
पूर्णांक gmap_fault(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr,
	       अचिन्हित पूर्णांक fault_flags)
अणु
	अचिन्हित दीर्घ vmaddr;
	पूर्णांक rc;
	bool unlocked;

	mmap_पढ़ो_lock(gmap->mm);

retry:
	unlocked = false;
	vmaddr = __gmap_translate(gmap, gaddr);
	अगर (IS_ERR_VALUE(vmaddr)) अणु
		rc = vmaddr;
		जाओ out_up;
	पूर्ण
	अगर (fixup_user_fault(gmap->mm, vmaddr, fault_flags,
			     &unlocked)) अणु
		rc = -EFAULT;
		जाओ out_up;
	पूर्ण
	/*
	 * In the हाल that fixup_user_fault unlocked the mmap_lock during
	 * faultin reकरो __gmap_translate to not race with a map/unmap_segment.
	 */
	अगर (unlocked)
		जाओ retry;

	rc = __gmap_link(gmap, gaddr, vmaddr);
out_up:
	mmap_पढ़ो_unlock(gmap->mm);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_fault);

/*
 * this function is assumed to be called with mmap_lock held
 */
व्योम __gmap_zap(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr)
अणु
	अचिन्हित दीर्घ vmaddr;
	spinlock_t *ptl;
	pte_t *ptep;

	/* Find the vm address क्रम the guest address */
	vmaddr = (अचिन्हित दीर्घ) radix_tree_lookup(&gmap->guest_to_host,
						   gaddr >> PMD_SHIFT);
	अगर (vmaddr) अणु
		vmaddr |= gaddr & ~PMD_MASK;
		/* Get poपूर्णांकer to the page table entry */
		ptep = get_locked_pte(gmap->mm, vmaddr, &ptl);
		अगर (likely(ptep))
			ptep_zap_unused(gmap->mm, vmaddr, ptep, 0);
		pte_unmap_unlock(ptep, ptl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__gmap_zap);

व्योम gmap_discard(काष्ठा gmap *gmap, अचिन्हित दीर्घ from, अचिन्हित दीर्घ to)
अणु
	अचिन्हित दीर्घ gaddr, vmaddr, size;
	काष्ठा vm_area_काष्ठा *vma;

	mmap_पढ़ो_lock(gmap->mm);
	क्रम (gaddr = from; gaddr < to;
	     gaddr = (gaddr + PMD_SIZE) & PMD_MASK) अणु
		/* Find the vm address क्रम the guest address */
		vmaddr = (अचिन्हित दीर्घ)
			radix_tree_lookup(&gmap->guest_to_host,
					  gaddr >> PMD_SHIFT);
		अगर (!vmaddr)
			जारी;
		vmaddr |= gaddr & ~PMD_MASK;
		/* Find vma in the parent mm */
		vma = find_vma(gmap->mm, vmaddr);
		अगर (!vma)
			जारी;
		/*
		 * We करो not discard pages that are backed by
		 * hugetlbfs, so we करोn't have to refault them.
		 */
		अगर (is_vm_hugetlb_page(vma))
			जारी;
		size = min(to - gaddr, PMD_SIZE - (gaddr & ~PMD_MASK));
		zap_page_range(vma, vmaddr, size);
	पूर्ण
	mmap_पढ़ो_unlock(gmap->mm);
पूर्ण
EXPORT_SYMBOL_GPL(gmap_discard);

अटल LIST_HEAD(gmap_notअगरier_list);
अटल DEFINE_SPINLOCK(gmap_notअगरier_lock);

/**
 * gmap_रेजिस्टर_pte_notअगरier - रेजिस्टर a pte invalidation callback
 * @nb: poपूर्णांकer to the gmap notअगरier block
 */
व्योम gmap_रेजिस्टर_pte_notअगरier(काष्ठा gmap_notअगरier *nb)
अणु
	spin_lock(&gmap_notअगरier_lock);
	list_add_rcu(&nb->list, &gmap_notअगरier_list);
	spin_unlock(&gmap_notअगरier_lock);
पूर्ण
EXPORT_SYMBOL_GPL(gmap_रेजिस्टर_pte_notअगरier);

/**
 * gmap_unरेजिस्टर_pte_notअगरier - हटाओ a pte invalidation callback
 * @nb: poपूर्णांकer to the gmap notअगरier block
 */
व्योम gmap_unरेजिस्टर_pte_notअगरier(काष्ठा gmap_notअगरier *nb)
अणु
	spin_lock(&gmap_notअगरier_lock);
	list_del_rcu(&nb->list);
	spin_unlock(&gmap_notअगरier_lock);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(gmap_unरेजिस्टर_pte_notअगरier);

/**
 * gmap_call_notअगरier - call all रेजिस्टरed invalidation callbacks
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @start: start भव address in the guest address space
 * @end: end भव address in the guest address space
 */
अटल व्योम gmap_call_notअगरier(काष्ठा gmap *gmap, अचिन्हित दीर्घ start,
			       अचिन्हित दीर्घ end)
अणु
	काष्ठा gmap_notअगरier *nb;

	list_क्रम_each_entry(nb, &gmap_notअगरier_list, list)
		nb->notअगरier_call(gmap, start, end);
पूर्ण

/**
 * gmap_table_walk - walk the gmap page tables
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: भव address in the guest address space
 * @level: page table level to stop at
 *
 * Returns a table entry poपूर्णांकer क्रम the given guest address and @level
 * @level=0 : वापसs a poपूर्णांकer to a page table table entry (or शून्य)
 * @level=1 : वापसs a poपूर्णांकer to a segment table entry (or शून्य)
 * @level=2 : वापसs a poपूर्णांकer to a region-3 table entry (or शून्य)
 * @level=3 : वापसs a poपूर्णांकer to a region-2 table entry (or शून्य)
 * @level=4 : वापसs a poपूर्णांकer to a region-1 table entry (or शून्य)
 *
 * Returns शून्य अगर the gmap page tables could not be walked to the
 * requested level.
 *
 * Note: Can also be called क्रम shaकरोw gmaps.
 */
अटल अंतरभूत अचिन्हित दीर्घ *gmap_table_walk(काष्ठा gmap *gmap,
					     अचिन्हित दीर्घ gaddr, पूर्णांक level)
अणु
	स्थिर पूर्णांक asce_type = gmap->asce & _ASCE_TYPE_MASK;
	अचिन्हित दीर्घ *table = gmap->table;

	अगर (gmap_is_shaकरोw(gmap) && gmap->हटाओd)
		वापस शून्य;

	अगर (WARN_ON_ONCE(level > (asce_type >> 2) + 1))
		वापस शून्य;

	अगर (asce_type != _ASCE_TYPE_REGION1 &&
	    gaddr & (-1UL << (31 + (asce_type >> 2) * 11)))
		वापस शून्य;

	चयन (asce_type) अणु
	हाल _ASCE_TYPE_REGION1:
		table += (gaddr & _REGION1_INDEX) >> _REGION1_SHIFT;
		अगर (level == 4)
			अवरोध;
		अगर (*table & _REGION_ENTRY_INVALID)
			वापस शून्य;
		table = (अचिन्हित दीर्घ *)(*table & _REGION_ENTRY_ORIGIN);
		fallthrough;
	हाल _ASCE_TYPE_REGION2:
		table += (gaddr & _REGION2_INDEX) >> _REGION2_SHIFT;
		अगर (level == 3)
			अवरोध;
		अगर (*table & _REGION_ENTRY_INVALID)
			वापस शून्य;
		table = (अचिन्हित दीर्घ *)(*table & _REGION_ENTRY_ORIGIN);
		fallthrough;
	हाल _ASCE_TYPE_REGION3:
		table += (gaddr & _REGION3_INDEX) >> _REGION3_SHIFT;
		अगर (level == 2)
			अवरोध;
		अगर (*table & _REGION_ENTRY_INVALID)
			वापस शून्य;
		table = (अचिन्हित दीर्घ *)(*table & _REGION_ENTRY_ORIGIN);
		fallthrough;
	हाल _ASCE_TYPE_SEGMENT:
		table += (gaddr & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
		अगर (level == 1)
			अवरोध;
		अगर (*table & _REGION_ENTRY_INVALID)
			वापस शून्य;
		table = (अचिन्हित दीर्घ *)(*table & _SEGMENT_ENTRY_ORIGIN);
		table += (gaddr & _PAGE_INDEX) >> _PAGE_SHIFT;
	पूर्ण
	वापस table;
पूर्ण

/**
 * gmap_pte_op_walk - walk the gmap page table, get the page table lock
 *		      and वापस the pte poपूर्णांकer
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: भव address in the guest address space
 * @ptl: poपूर्णांकer to the spinlock poपूर्णांकer
 *
 * Returns a poपूर्णांकer to the locked pte क्रम a guest address, or शून्य
 */
अटल pte_t *gmap_pte_op_walk(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr,
			       spinlock_t **ptl)
अणु
	अचिन्हित दीर्घ *table;

	BUG_ON(gmap_is_shaकरोw(gmap));
	/* Walk the gmap page table, lock and get pte poपूर्णांकer */
	table = gmap_table_walk(gmap, gaddr, 1); /* get segment poपूर्णांकer */
	अगर (!table || *table & _SEGMENT_ENTRY_INVALID)
		वापस शून्य;
	वापस pte_alloc_map_lock(gmap->mm, (pmd_t *) table, gaddr, ptl);
पूर्ण

/**
 * gmap_pte_op_fixup - क्रमce a page in and connect the gmap page table
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: भव address in the guest address space
 * @vmaddr: address in the host process address space
 * @prot: indicates access rights: PROT_NONE, PROT_READ or PROT_WRITE
 *
 * Returns 0 अगर the caller can retry __gmap_translate (might fail again),
 * -ENOMEM अगर out of memory and -EFAULT अगर anything goes wrong जबतक fixing
 * up or connecting the gmap page table.
 */
अटल पूर्णांक gmap_pte_op_fixup(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr,
			     अचिन्हित दीर्घ vmaddr, पूर्णांक prot)
अणु
	काष्ठा mm_काष्ठा *mm = gmap->mm;
	अचिन्हित पूर्णांक fault_flags;
	bool unlocked = false;

	BUG_ON(gmap_is_shaकरोw(gmap));
	fault_flags = (prot == PROT_WRITE) ? FAULT_FLAG_WRITE : 0;
	अगर (fixup_user_fault(mm, vmaddr, fault_flags, &unlocked))
		वापस -EFAULT;
	अगर (unlocked)
		/* lost mmap_lock, caller has to retry __gmap_translate */
		वापस 0;
	/* Connect the page tables */
	वापस __gmap_link(gmap, gaddr, vmaddr);
पूर्ण

/**
 * gmap_pte_op_end - release the page table lock
 * @ptl: poपूर्णांकer to the spinlock poपूर्णांकer
 */
अटल व्योम gmap_pte_op_end(spinlock_t *ptl)
अणु
	अगर (ptl)
		spin_unlock(ptl);
पूर्ण

/**
 * gmap_pmd_op_walk - walk the gmap tables, get the guest table lock
 *		      and वापस the pmd poपूर्णांकer
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: भव address in the guest address space
 *
 * Returns a poपूर्णांकer to the pmd क्रम a guest address, or शून्य
 */
अटल अंतरभूत pmd_t *gmap_pmd_op_walk(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr)
अणु
	pmd_t *pmdp;

	BUG_ON(gmap_is_shaकरोw(gmap));
	pmdp = (pmd_t *) gmap_table_walk(gmap, gaddr, 1);
	अगर (!pmdp)
		वापस शून्य;

	/* without huge pages, there is no need to take the table lock */
	अगर (!gmap->mm->context.allow_gmap_hpage_1m)
		वापस pmd_none(*pmdp) ? शून्य : pmdp;

	spin_lock(&gmap->guest_table_lock);
	अगर (pmd_none(*pmdp)) अणु
		spin_unlock(&gmap->guest_table_lock);
		वापस शून्य;
	पूर्ण

	/* 4k page table entries are locked via the pte (pte_alloc_map_lock). */
	अगर (!pmd_large(*pmdp))
		spin_unlock(&gmap->guest_table_lock);
	वापस pmdp;
पूर्ण

/**
 * gmap_pmd_op_end - release the guest_table_lock अगर needed
 * @gmap: poपूर्णांकer to the guest mapping meta data काष्ठाure
 * @pmdp: poपूर्णांकer to the pmd
 */
अटल अंतरभूत व्योम gmap_pmd_op_end(काष्ठा gmap *gmap, pmd_t *pmdp)
अणु
	अगर (pmd_large(*pmdp))
		spin_unlock(&gmap->guest_table_lock);
पूर्ण

/*
 * gmap_protect_pmd - हटाओ access rights to memory and set pmd notअगरication bits
 * @pmdp: poपूर्णांकer to the pmd to be रक्षित
 * @prot: indicates access rights: PROT_NONE, PROT_READ or PROT_WRITE
 * @bits: notअगरication bits to set
 *
 * Returns:
 * 0 अगर successfully रक्षित
 * -EAGAIN अगर a fixup is needed
 * -EINVAL अगर unsupported notअगरier bits have been specअगरied
 *
 * Expected to be called with sg->mm->mmap_lock in पढ़ो and
 * guest_table_lock held.
 */
अटल पूर्णांक gmap_protect_pmd(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr,
			    pmd_t *pmdp, पूर्णांक prot, अचिन्हित दीर्घ bits)
अणु
	पूर्णांक pmd_i = pmd_val(*pmdp) & _SEGMENT_ENTRY_INVALID;
	पूर्णांक pmd_p = pmd_val(*pmdp) & _SEGMENT_ENTRY_PROTECT;
	pmd_t new = *pmdp;

	/* Fixup needed */
	अगर ((pmd_i && (prot != PROT_NONE)) || (pmd_p && (prot == PROT_WRITE)))
		वापस -EAGAIN;

	अगर (prot == PROT_NONE && !pmd_i) अणु
		pmd_val(new) |= _SEGMENT_ENTRY_INVALID;
		gmap_pmdp_xchg(gmap, pmdp, new, gaddr);
	पूर्ण

	अगर (prot == PROT_READ && !pmd_p) अणु
		pmd_val(new) &= ~_SEGMENT_ENTRY_INVALID;
		pmd_val(new) |= _SEGMENT_ENTRY_PROTECT;
		gmap_pmdp_xchg(gmap, pmdp, new, gaddr);
	पूर्ण

	अगर (bits & GMAP_NOTIFY_MPROT)
		pmd_val(*pmdp) |= _SEGMENT_ENTRY_GMAP_IN;

	/* Shaकरोw GMAP protection needs split PMDs */
	अगर (bits & GMAP_NOTIFY_SHADOW)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * gmap_protect_pte - हटाओ access rights to memory and set pgste bits
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: भव address in the guest address space
 * @pmdp: poपूर्णांकer to the pmd associated with the pte
 * @prot: indicates access rights: PROT_NONE, PROT_READ or PROT_WRITE
 * @bits: notअगरication bits to set
 *
 * Returns 0 अगर successfully रक्षित, -ENOMEM अगर out of memory and
 * -EAGAIN अगर a fixup is needed.
 *
 * Expected to be called with sg->mm->mmap_lock in पढ़ो
 */
अटल पूर्णांक gmap_protect_pte(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr,
			    pmd_t *pmdp, पूर्णांक prot, अचिन्हित दीर्घ bits)
अणु
	पूर्णांक rc;
	pte_t *ptep;
	spinlock_t *ptl = शून्य;
	अचिन्हित दीर्घ pbits = 0;

	अगर (pmd_val(*pmdp) & _SEGMENT_ENTRY_INVALID)
		वापस -EAGAIN;

	ptep = pte_alloc_map_lock(gmap->mm, pmdp, gaddr, &ptl);
	अगर (!ptep)
		वापस -ENOMEM;

	pbits |= (bits & GMAP_NOTIFY_MPROT) ? PGSTE_IN_BIT : 0;
	pbits |= (bits & GMAP_NOTIFY_SHADOW) ? PGSTE_VSIE_BIT : 0;
	/* Protect and unlock. */
	rc = ptep_क्रमce_prot(gmap->mm, gaddr, ptep, prot, pbits);
	gmap_pte_op_end(ptl);
	वापस rc;
पूर्ण

/*
 * gmap_protect_range - हटाओ access rights to memory and set pgste bits
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: भव address in the guest address space
 * @len: size of area
 * @prot: indicates access rights: PROT_NONE, PROT_READ or PROT_WRITE
 * @bits: pgste notअगरication bits to set
 *
 * Returns 0 अगर successfully रक्षित, -ENOMEM अगर out of memory and
 * -EFAULT अगर gaddr is invalid (or mapping क्रम shaकरोws is missing).
 *
 * Called with sg->mm->mmap_lock in पढ़ो.
 */
अटल पूर्णांक gmap_protect_range(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr,
			      अचिन्हित दीर्घ len, पूर्णांक prot, अचिन्हित दीर्घ bits)
अणु
	अचिन्हित दीर्घ vmaddr, dist;
	pmd_t *pmdp;
	पूर्णांक rc;

	BUG_ON(gmap_is_shaकरोw(gmap));
	जबतक (len) अणु
		rc = -EAGAIN;
		pmdp = gmap_pmd_op_walk(gmap, gaddr);
		अगर (pmdp) अणु
			अगर (!pmd_large(*pmdp)) अणु
				rc = gmap_protect_pte(gmap, gaddr, pmdp, prot,
						      bits);
				अगर (!rc) अणु
					len -= PAGE_SIZE;
					gaddr += PAGE_SIZE;
				पूर्ण
			पूर्ण अन्यथा अणु
				rc = gmap_protect_pmd(gmap, gaddr, pmdp, prot,
						      bits);
				अगर (!rc) अणु
					dist = HPAGE_SIZE - (gaddr & ~HPAGE_MASK);
					len = len < dist ? 0 : len - dist;
					gaddr = (gaddr & HPAGE_MASK) + HPAGE_SIZE;
				पूर्ण
			पूर्ण
			gmap_pmd_op_end(gmap, pmdp);
		पूर्ण
		अगर (rc) अणु
			अगर (rc == -EINVAL)
				वापस rc;

			/* -EAGAIN, fixup of userspace mm and gmap */
			vmaddr = __gmap_translate(gmap, gaddr);
			अगर (IS_ERR_VALUE(vmaddr))
				वापस vmaddr;
			rc = gmap_pte_op_fixup(gmap, gaddr, vmaddr, prot);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * gmap_mprotect_notअगरy - change access rights क्रम a range of ptes and
 *                        call the notअगरier अगर any pte changes again
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: भव address in the guest address space
 * @len: size of area
 * @prot: indicates access rights: PROT_NONE, PROT_READ or PROT_WRITE
 *
 * Returns 0 अगर क्रम each page in the given range a gmap mapping exists,
 * the new access rights could be set and the notअगरier could be armed.
 * If the gmap mapping is missing क्रम one or more pages -EFAULT is
 * वापसed. If no memory could be allocated -ENOMEM is वापसed.
 * This function establishes missing page table entries.
 */
पूर्णांक gmap_mprotect_notअगरy(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr,
			 अचिन्हित दीर्घ len, पूर्णांक prot)
अणु
	पूर्णांक rc;

	अगर ((gaddr & ~PAGE_MASK) || (len & ~PAGE_MASK) || gmap_is_shaकरोw(gmap))
		वापस -EINVAL;
	अगर (!MACHINE_HAS_ESOP && prot == PROT_READ)
		वापस -EINVAL;
	mmap_पढ़ो_lock(gmap->mm);
	rc = gmap_protect_range(gmap, gaddr, len, prot, GMAP_NOTIFY_MPROT);
	mmap_पढ़ो_unlock(gmap->mm);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_mprotect_notअगरy);

/**
 * gmap_पढ़ो_table - get an अचिन्हित दीर्घ value from a guest page table using
 *                   असलolute addressing, without marking the page referenced.
 * @gmap: poपूर्णांकer to guest mapping meta data काष्ठाure
 * @gaddr: भव address in the guest address space
 * @val: poपूर्णांकer to the अचिन्हित दीर्घ value to वापस
 *
 * Returns 0 अगर the value was पढ़ो, -ENOMEM अगर out of memory and -EFAULT
 * अगर पढ़ोing using the भव address failed. -EINVAL अगर called on a gmap
 * shaकरोw.
 *
 * Called with gmap->mm->mmap_lock in पढ़ो.
 */
पूर्णांक gmap_पढ़ो_table(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr, अचिन्हित दीर्घ *val)
अणु
	अचिन्हित दीर्घ address, vmaddr;
	spinlock_t *ptl;
	pte_t *ptep, pte;
	पूर्णांक rc;

	अगर (gmap_is_shaकरोw(gmap))
		वापस -EINVAL;

	जबतक (1) अणु
		rc = -EAGAIN;
		ptep = gmap_pte_op_walk(gmap, gaddr, &ptl);
		अगर (ptep) अणु
			pte = *ptep;
			अगर (pte_present(pte) && (pte_val(pte) & _PAGE_READ)) अणु
				address = pte_val(pte) & PAGE_MASK;
				address += gaddr & ~PAGE_MASK;
				*val = *(अचिन्हित दीर्घ *) address;
				pte_val(*ptep) |= _PAGE_YOUNG;
				/* Do *NOT* clear the _PAGE_INVALID bit! */
				rc = 0;
			पूर्ण
			gmap_pte_op_end(ptl);
		पूर्ण
		अगर (!rc)
			अवरोध;
		vmaddr = __gmap_translate(gmap, gaddr);
		अगर (IS_ERR_VALUE(vmaddr)) अणु
			rc = vmaddr;
			अवरोध;
		पूर्ण
		rc = gmap_pte_op_fixup(gmap, gaddr, vmaddr, PROT_READ);
		अगर (rc)
			अवरोध;
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_पढ़ो_table);

/**
 * gmap_insert_rmap - add a rmap to the host_to_rmap radix tree
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @vmaddr: vm address associated with the rmap
 * @rmap: poपूर्णांकer to the rmap काष्ठाure
 *
 * Called with the sg->guest_table_lock
 */
अटल अंतरभूत व्योम gmap_insert_rmap(काष्ठा gmap *sg, अचिन्हित दीर्घ vmaddr,
				    काष्ठा gmap_rmap *rmap)
अणु
	व्योम __rcu **slot;

	BUG_ON(!gmap_is_shaकरोw(sg));
	slot = radix_tree_lookup_slot(&sg->host_to_rmap, vmaddr >> PAGE_SHIFT);
	अगर (slot) अणु
		rmap->next = radix_tree_deref_slot_रक्षित(slot,
							&sg->guest_table_lock);
		radix_tree_replace_slot(&sg->host_to_rmap, slot, rmap);
	पूर्ण अन्यथा अणु
		rmap->next = शून्य;
		radix_tree_insert(&sg->host_to_rmap, vmaddr >> PAGE_SHIFT,
				  rmap);
	पूर्ण
पूर्ण

/**
 * gmap_protect_rmap - restrict access rights to memory (RO) and create an rmap
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: rmap address in the shaकरोw gmap
 * @paddr: address in the parent guest address space
 * @len: length of the memory area to protect
 *
 * Returns 0 अगर successfully रक्षित and the rmap was created, -ENOMEM
 * अगर out of memory and -EFAULT अगर paddr is invalid.
 */
अटल पूर्णांक gmap_protect_rmap(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr,
			     अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ len)
अणु
	काष्ठा gmap *parent;
	काष्ठा gmap_rmap *rmap;
	अचिन्हित दीर्घ vmaddr;
	spinlock_t *ptl;
	pte_t *ptep;
	पूर्णांक rc;

	BUG_ON(!gmap_is_shaकरोw(sg));
	parent = sg->parent;
	जबतक (len) अणु
		vmaddr = __gmap_translate(parent, paddr);
		अगर (IS_ERR_VALUE(vmaddr))
			वापस vmaddr;
		rmap = kzalloc(माप(*rmap), GFP_KERNEL_ACCOUNT);
		अगर (!rmap)
			वापस -ENOMEM;
		rmap->raddr = raddr;
		rc = radix_tree_preload(GFP_KERNEL_ACCOUNT);
		अगर (rc) अणु
			kमुक्त(rmap);
			वापस rc;
		पूर्ण
		rc = -EAGAIN;
		ptep = gmap_pte_op_walk(parent, paddr, &ptl);
		अगर (ptep) अणु
			spin_lock(&sg->guest_table_lock);
			rc = ptep_क्रमce_prot(parent->mm, paddr, ptep, PROT_READ,
					     PGSTE_VSIE_BIT);
			अगर (!rc)
				gmap_insert_rmap(sg, vmaddr, rmap);
			spin_unlock(&sg->guest_table_lock);
			gmap_pte_op_end(ptl);
		पूर्ण
		radix_tree_preload_end();
		अगर (rc) अणु
			kमुक्त(rmap);
			rc = gmap_pte_op_fixup(parent, paddr, vmaddr, PROT_READ);
			अगर (rc)
				वापस rc;
			जारी;
		पूर्ण
		paddr += PAGE_SIZE;
		len -= PAGE_SIZE;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा _SHADOW_RMAP_MASK	0x7
#घोषणा _SHADOW_RMAP_REGION1	0x5
#घोषणा _SHADOW_RMAP_REGION2	0x4
#घोषणा _SHADOW_RMAP_REGION3	0x3
#घोषणा _SHADOW_RMAP_SEGMENT	0x2
#घोषणा _SHADOW_RMAP_PGTABLE	0x1

/**
 * gmap_idte_one - invalidate a single region or segment table entry
 * @asce: region or segment table *origin* + table-type bits
 * @vaddr: भव address to identअगरy the table entry to flush
 *
 * The invalid bit of a single region or segment table entry is set
 * and the associated TLB entries depending on the entry are flushed.
 * The table-type of the @asce identअगरies the portion of the @vaddr
 * that is used as the invalidation index.
 */
अटल अंतरभूत व्योम gmap_idte_one(अचिन्हित दीर्घ asce, अचिन्हित दीर्घ vaddr)
अणु
	यंत्र अस्थिर(
		"	.insn	rrf,0xb98e0000,%0,%1,0,0"
		: : "a" (asce), "a" (vaddr) : "cc", "memory");
पूर्ण

/**
 * gmap_unshaकरोw_page - हटाओ a page from a shaकरोw page table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: rmap address in the shaकरोw guest address space
 *
 * Called with the sg->guest_table_lock
 */
अटल व्योम gmap_unshaकरोw_page(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr)
अणु
	अचिन्हित दीर्घ *table;

	BUG_ON(!gmap_is_shaकरोw(sg));
	table = gmap_table_walk(sg, raddr, 0); /* get page table poपूर्णांकer */
	अगर (!table || *table & _PAGE_INVALID)
		वापस;
	gmap_call_notअगरier(sg, raddr, raddr + _PAGE_SIZE - 1);
	ptep_unshaकरोw_pte(sg->mm, raddr, (pte_t *) table);
पूर्ण

/**
 * __gmap_unshaकरोw_pgt - हटाओ all entries from a shaकरोw page table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: rmap address in the shaकरोw guest address space
 * @pgt: poपूर्णांकer to the start of a shaकरोw page table
 *
 * Called with the sg->guest_table_lock
 */
अटल व्योम __gmap_unshaकरोw_pgt(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr,
				अचिन्हित दीर्घ *pgt)
अणु
	पूर्णांक i;

	BUG_ON(!gmap_is_shaकरोw(sg));
	क्रम (i = 0; i < _PAGE_ENTRIES; i++, raddr += _PAGE_SIZE)
		pgt[i] = _PAGE_INVALID;
पूर्ण

/**
 * gmap_unshaकरोw_pgt - हटाओ a shaकरोw page table from a segment entry
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: address in the shaकरोw guest address space
 *
 * Called with the sg->guest_table_lock
 */
अटल व्योम gmap_unshaकरोw_pgt(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr)
अणु
	अचिन्हित दीर्घ sto, *ste, *pgt;
	काष्ठा page *page;

	BUG_ON(!gmap_is_shaकरोw(sg));
	ste = gmap_table_walk(sg, raddr, 1); /* get segment poपूर्णांकer */
	अगर (!ste || !(*ste & _SEGMENT_ENTRY_ORIGIN))
		वापस;
	gmap_call_notअगरier(sg, raddr, raddr + _SEGMENT_SIZE - 1);
	sto = (अचिन्हित दीर्घ) (ste - ((raddr & _SEGMENT_INDEX) >> _SEGMENT_SHIFT));
	gmap_idte_one(sto | _ASCE_TYPE_SEGMENT, raddr);
	pgt = (अचिन्हित दीर्घ *)(*ste & _SEGMENT_ENTRY_ORIGIN);
	*ste = _SEGMENT_ENTRY_EMPTY;
	__gmap_unshaकरोw_pgt(sg, raddr, pgt);
	/* Free page table */
	page = pfn_to_page(__pa(pgt) >> PAGE_SHIFT);
	list_del(&page->lru);
	page_table_मुक्त_pgste(page);
पूर्ण

/**
 * __gmap_unshaकरोw_sgt - हटाओ all entries from a shaकरोw segment table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: rmap address in the shaकरोw guest address space
 * @sgt: poपूर्णांकer to the start of a shaकरोw segment table
 *
 * Called with the sg->guest_table_lock
 */
अटल व्योम __gmap_unshaकरोw_sgt(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr,
				अचिन्हित दीर्घ *sgt)
अणु
	अचिन्हित दीर्घ *pgt;
	काष्ठा page *page;
	पूर्णांक i;

	BUG_ON(!gmap_is_shaकरोw(sg));
	क्रम (i = 0; i < _CRST_ENTRIES; i++, raddr += _SEGMENT_SIZE) अणु
		अगर (!(sgt[i] & _SEGMENT_ENTRY_ORIGIN))
			जारी;
		pgt = (अचिन्हित दीर्घ *)(sgt[i] & _REGION_ENTRY_ORIGIN);
		sgt[i] = _SEGMENT_ENTRY_EMPTY;
		__gmap_unshaकरोw_pgt(sg, raddr, pgt);
		/* Free page table */
		page = pfn_to_page(__pa(pgt) >> PAGE_SHIFT);
		list_del(&page->lru);
		page_table_मुक्त_pgste(page);
	पूर्ण
पूर्ण

/**
 * gmap_unshaकरोw_sgt - हटाओ a shaकरोw segment table from a region-3 entry
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: rmap address in the shaकरोw guest address space
 *
 * Called with the shaकरोw->guest_table_lock
 */
अटल व्योम gmap_unshaकरोw_sgt(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr)
अणु
	अचिन्हित दीर्घ r3o, *r3e, *sgt;
	काष्ठा page *page;

	BUG_ON(!gmap_is_shaकरोw(sg));
	r3e = gmap_table_walk(sg, raddr, 2); /* get region-3 poपूर्णांकer */
	अगर (!r3e || !(*r3e & _REGION_ENTRY_ORIGIN))
		वापस;
	gmap_call_notअगरier(sg, raddr, raddr + _REGION3_SIZE - 1);
	r3o = (अचिन्हित दीर्घ) (r3e - ((raddr & _REGION3_INDEX) >> _REGION3_SHIFT));
	gmap_idte_one(r3o | _ASCE_TYPE_REGION3, raddr);
	sgt = (अचिन्हित दीर्घ *)(*r3e & _REGION_ENTRY_ORIGIN);
	*r3e = _REGION3_ENTRY_EMPTY;
	__gmap_unshaकरोw_sgt(sg, raddr, sgt);
	/* Free segment table */
	page = pfn_to_page(__pa(sgt) >> PAGE_SHIFT);
	list_del(&page->lru);
	__मुक्त_pages(page, CRST_ALLOC_ORDER);
पूर्ण

/**
 * __gmap_unshaकरोw_r3t - हटाओ all entries from a shaकरोw region-3 table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: address in the shaकरोw guest address space
 * @r3t: poपूर्णांकer to the start of a shaकरोw region-3 table
 *
 * Called with the sg->guest_table_lock
 */
अटल व्योम __gmap_unshaकरोw_r3t(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr,
				अचिन्हित दीर्घ *r3t)
अणु
	अचिन्हित दीर्घ *sgt;
	काष्ठा page *page;
	पूर्णांक i;

	BUG_ON(!gmap_is_shaकरोw(sg));
	क्रम (i = 0; i < _CRST_ENTRIES; i++, raddr += _REGION3_SIZE) अणु
		अगर (!(r3t[i] & _REGION_ENTRY_ORIGIN))
			जारी;
		sgt = (अचिन्हित दीर्घ *)(r3t[i] & _REGION_ENTRY_ORIGIN);
		r3t[i] = _REGION3_ENTRY_EMPTY;
		__gmap_unshaकरोw_sgt(sg, raddr, sgt);
		/* Free segment table */
		page = pfn_to_page(__pa(sgt) >> PAGE_SHIFT);
		list_del(&page->lru);
		__मुक्त_pages(page, CRST_ALLOC_ORDER);
	पूर्ण
पूर्ण

/**
 * gmap_unshaकरोw_r3t - हटाओ a shaकरोw region-3 table from a region-2 entry
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: rmap address in the shaकरोw guest address space
 *
 * Called with the sg->guest_table_lock
 */
अटल व्योम gmap_unshaकरोw_r3t(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr)
अणु
	अचिन्हित दीर्घ r2o, *r2e, *r3t;
	काष्ठा page *page;

	BUG_ON(!gmap_is_shaकरोw(sg));
	r2e = gmap_table_walk(sg, raddr, 3); /* get region-2 poपूर्णांकer */
	अगर (!r2e || !(*r2e & _REGION_ENTRY_ORIGIN))
		वापस;
	gmap_call_notअगरier(sg, raddr, raddr + _REGION2_SIZE - 1);
	r2o = (अचिन्हित दीर्घ) (r2e - ((raddr & _REGION2_INDEX) >> _REGION2_SHIFT));
	gmap_idte_one(r2o | _ASCE_TYPE_REGION2, raddr);
	r3t = (अचिन्हित दीर्घ *)(*r2e & _REGION_ENTRY_ORIGIN);
	*r2e = _REGION2_ENTRY_EMPTY;
	__gmap_unshaकरोw_r3t(sg, raddr, r3t);
	/* Free region 3 table */
	page = pfn_to_page(__pa(r3t) >> PAGE_SHIFT);
	list_del(&page->lru);
	__मुक्त_pages(page, CRST_ALLOC_ORDER);
पूर्ण

/**
 * __gmap_unshaकरोw_r2t - हटाओ all entries from a shaकरोw region-2 table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: rmap address in the shaकरोw guest address space
 * @r2t: poपूर्णांकer to the start of a shaकरोw region-2 table
 *
 * Called with the sg->guest_table_lock
 */
अटल व्योम __gmap_unshaकरोw_r2t(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr,
				अचिन्हित दीर्घ *r2t)
अणु
	अचिन्हित दीर्घ *r3t;
	काष्ठा page *page;
	पूर्णांक i;

	BUG_ON(!gmap_is_shaकरोw(sg));
	क्रम (i = 0; i < _CRST_ENTRIES; i++, raddr += _REGION2_SIZE) अणु
		अगर (!(r2t[i] & _REGION_ENTRY_ORIGIN))
			जारी;
		r3t = (अचिन्हित दीर्घ *)(r2t[i] & _REGION_ENTRY_ORIGIN);
		r2t[i] = _REGION2_ENTRY_EMPTY;
		__gmap_unshaकरोw_r3t(sg, raddr, r3t);
		/* Free region 3 table */
		page = pfn_to_page(__pa(r3t) >> PAGE_SHIFT);
		list_del(&page->lru);
		__मुक्त_pages(page, CRST_ALLOC_ORDER);
	पूर्ण
पूर्ण

/**
 * gmap_unshaकरोw_r2t - हटाओ a shaकरोw region-2 table from a region-1 entry
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: rmap address in the shaकरोw guest address space
 *
 * Called with the sg->guest_table_lock
 */
अटल व्योम gmap_unshaकरोw_r2t(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr)
अणु
	अचिन्हित दीर्घ r1o, *r1e, *r2t;
	काष्ठा page *page;

	BUG_ON(!gmap_is_shaकरोw(sg));
	r1e = gmap_table_walk(sg, raddr, 4); /* get region-1 poपूर्णांकer */
	अगर (!r1e || !(*r1e & _REGION_ENTRY_ORIGIN))
		वापस;
	gmap_call_notअगरier(sg, raddr, raddr + _REGION1_SIZE - 1);
	r1o = (अचिन्हित दीर्घ) (r1e - ((raddr & _REGION1_INDEX) >> _REGION1_SHIFT));
	gmap_idte_one(r1o | _ASCE_TYPE_REGION1, raddr);
	r2t = (अचिन्हित दीर्घ *)(*r1e & _REGION_ENTRY_ORIGIN);
	*r1e = _REGION1_ENTRY_EMPTY;
	__gmap_unshaकरोw_r2t(sg, raddr, r2t);
	/* Free region 2 table */
	page = pfn_to_page(__pa(r2t) >> PAGE_SHIFT);
	list_del(&page->lru);
	__मुक्त_pages(page, CRST_ALLOC_ORDER);
पूर्ण

/**
 * __gmap_unshaकरोw_r1t - हटाओ all entries from a shaकरोw region-1 table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @raddr: rmap address in the shaकरोw guest address space
 * @r1t: poपूर्णांकer to the start of a shaकरोw region-1 table
 *
 * Called with the shaकरोw->guest_table_lock
 */
अटल व्योम __gmap_unshaकरोw_r1t(काष्ठा gmap *sg, अचिन्हित दीर्घ raddr,
				अचिन्हित दीर्घ *r1t)
अणु
	अचिन्हित दीर्घ asce, *r2t;
	काष्ठा page *page;
	पूर्णांक i;

	BUG_ON(!gmap_is_shaकरोw(sg));
	asce = (अचिन्हित दीर्घ) r1t | _ASCE_TYPE_REGION1;
	क्रम (i = 0; i < _CRST_ENTRIES; i++, raddr += _REGION1_SIZE) अणु
		अगर (!(r1t[i] & _REGION_ENTRY_ORIGIN))
			जारी;
		r2t = (अचिन्हित दीर्घ *)(r1t[i] & _REGION_ENTRY_ORIGIN);
		__gmap_unshaकरोw_r2t(sg, raddr, r2t);
		/* Clear entry and flush translation r1t -> r2t */
		gmap_idte_one(asce, raddr);
		r1t[i] = _REGION1_ENTRY_EMPTY;
		/* Free region 2 table */
		page = pfn_to_page(__pa(r2t) >> PAGE_SHIFT);
		list_del(&page->lru);
		__मुक्त_pages(page, CRST_ALLOC_ORDER);
	पूर्ण
पूर्ण

/**
 * gmap_unshaकरोw - हटाओ a shaकरोw page table completely
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 *
 * Called with sg->guest_table_lock
 */
अटल व्योम gmap_unshaकरोw(काष्ठा gmap *sg)
अणु
	अचिन्हित दीर्घ *table;

	BUG_ON(!gmap_is_shaकरोw(sg));
	अगर (sg->हटाओd)
		वापस;
	sg->हटाओd = 1;
	gmap_call_notअगरier(sg, 0, -1UL);
	gmap_flush_tlb(sg);
	table = (अचिन्हित दीर्घ *)(sg->asce & _ASCE_ORIGIN);
	चयन (sg->asce & _ASCE_TYPE_MASK) अणु
	हाल _ASCE_TYPE_REGION1:
		__gmap_unshaकरोw_r1t(sg, 0, table);
		अवरोध;
	हाल _ASCE_TYPE_REGION2:
		__gmap_unshaकरोw_r2t(sg, 0, table);
		अवरोध;
	हाल _ASCE_TYPE_REGION3:
		__gmap_unshaकरोw_r3t(sg, 0, table);
		अवरोध;
	हाल _ASCE_TYPE_SEGMENT:
		__gmap_unshaकरोw_sgt(sg, 0, table);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * gmap_find_shaकरोw - find a specअगरic asce in the list of shaकरोw tables
 * @parent: poपूर्णांकer to the parent gmap
 * @asce: ASCE क्रम which the shaकरोw table is created
 * @edat_level: edat level to be used क्रम the shaकरोw translation
 *
 * Returns the poपूर्णांकer to a gmap अगर a shaकरोw table with the given asce is
 * alपढ़ोy available, ERR_PTR(-EAGAIN) अगर another one is just being created,
 * otherwise शून्य
 */
अटल काष्ठा gmap *gmap_find_shaकरोw(काष्ठा gmap *parent, अचिन्हित दीर्घ asce,
				     पूर्णांक edat_level)
अणु
	काष्ठा gmap *sg;

	list_क्रम_each_entry(sg, &parent->children, list) अणु
		अगर (sg->orig_asce != asce || sg->edat_level != edat_level ||
		    sg->हटाओd)
			जारी;
		अगर (!sg->initialized)
			वापस ERR_PTR(-EAGAIN);
		refcount_inc(&sg->ref_count);
		वापस sg;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * gmap_shaकरोw_valid - check अगर a shaकरोw guest address space matches the
 *                     given properties and is still valid
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @asce: ASCE क्रम which the shaकरोw table is requested
 * @edat_level: edat level to be used क्रम the shaकरोw translation
 *
 * Returns 1 अगर the gmap shaकरोw is still valid and matches the given
 * properties, the caller can जारी using it. Returns 0 otherwise, the
 * caller has to request a new shaकरोw gmap in this हाल.
 *
 */
पूर्णांक gmap_shaकरोw_valid(काष्ठा gmap *sg, अचिन्हित दीर्घ asce, पूर्णांक edat_level)
अणु
	अगर (sg->हटाओd)
		वापस 0;
	वापस sg->orig_asce == asce && sg->edat_level == edat_level;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_shaकरोw_valid);

/**
 * gmap_shaकरोw - create/find a shaकरोw guest address space
 * @parent: poपूर्णांकer to the parent gmap
 * @asce: ASCE क्रम which the shaकरोw table is created
 * @edat_level: edat level to be used क्रम the shaकरोw translation
 *
 * The pages of the top level page table referred by the asce parameter
 * will be set to पढ़ो-only and marked in the PGSTEs of the kvm process.
 * The shaकरोw table will be हटाओd स्वतःmatically on any change to the
 * PTE mapping क्रम the source table.
 *
 * Returns a guest address space काष्ठाure, ERR_PTR(-ENOMEM) अगर out of memory,
 * ERR_PTR(-EAGAIN) अगर the caller has to retry and ERR_PTR(-EFAULT) अगर the
 * parent gmap table could not be रक्षित.
 */
काष्ठा gmap *gmap_shaकरोw(काष्ठा gmap *parent, अचिन्हित दीर्घ asce,
			 पूर्णांक edat_level)
अणु
	काष्ठा gmap *sg, *new;
	अचिन्हित दीर्घ limit;
	पूर्णांक rc;

	BUG_ON(parent->mm->context.allow_gmap_hpage_1m);
	BUG_ON(gmap_is_shaकरोw(parent));
	spin_lock(&parent->shaकरोw_lock);
	sg = gmap_find_shaकरोw(parent, asce, edat_level);
	spin_unlock(&parent->shaकरोw_lock);
	अगर (sg)
		वापस sg;
	/* Create a new shaकरोw gmap */
	limit = -1UL >> (33 - (((asce & _ASCE_TYPE_MASK) >> 2) * 11));
	अगर (asce & _ASCE_REAL_SPACE)
		limit = -1UL;
	new = gmap_alloc(limit);
	अगर (!new)
		वापस ERR_PTR(-ENOMEM);
	new->mm = parent->mm;
	new->parent = gmap_get(parent);
	new->orig_asce = asce;
	new->edat_level = edat_level;
	new->initialized = false;
	spin_lock(&parent->shaकरोw_lock);
	/* Recheck अगर another CPU created the same shaकरोw */
	sg = gmap_find_shaकरोw(parent, asce, edat_level);
	अगर (sg) अणु
		spin_unlock(&parent->shaकरोw_lock);
		gmap_मुक्त(new);
		वापस sg;
	पूर्ण
	अगर (asce & _ASCE_REAL_SPACE) अणु
		/* only allow one real-space gmap shaकरोw */
		list_क्रम_each_entry(sg, &parent->children, list) अणु
			अगर (sg->orig_asce & _ASCE_REAL_SPACE) अणु
				spin_lock(&sg->guest_table_lock);
				gmap_unshaकरोw(sg);
				spin_unlock(&sg->guest_table_lock);
				list_del(&sg->list);
				gmap_put(sg);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	refcount_set(&new->ref_count, 2);
	list_add(&new->list, &parent->children);
	अगर (asce & _ASCE_REAL_SPACE) अणु
		/* nothing to protect, वापस right away */
		new->initialized = true;
		spin_unlock(&parent->shaकरोw_lock);
		वापस new;
	पूर्ण
	spin_unlock(&parent->shaकरोw_lock);
	/* protect after insertion, so it will get properly invalidated */
	mmap_पढ़ो_lock(parent->mm);
	rc = gmap_protect_range(parent, asce & _ASCE_ORIGIN,
				((asce & _ASCE_TABLE_LENGTH) + 1) * PAGE_SIZE,
				PROT_READ, GMAP_NOTIFY_SHADOW);
	mmap_पढ़ो_unlock(parent->mm);
	spin_lock(&parent->shaकरोw_lock);
	new->initialized = true;
	अगर (rc) अणु
		list_del(&new->list);
		gmap_मुक्त(new);
		new = ERR_PTR(rc);
	पूर्ण
	spin_unlock(&parent->shaकरोw_lock);
	वापस new;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_shaकरोw);

/**
 * gmap_shaकरोw_r2t - create an empty shaकरोw region 2 table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @saddr: faulting address in the shaकरोw gmap
 * @r2t: parent gmap address of the region 2 table to get shaकरोwed
 * @fake: r2t references contiguous guest memory block, not a r2t
 *
 * The r2t parameter specअगरies the address of the source table. The
 * four pages of the source table are made पढ़ो-only in the parent gmap
 * address space. A ग_लिखो to the source table area @r2t will स्वतःmatically
 * हटाओ the shaकरोw r2 table and all of its decendents.
 *
 * Returns 0 अगर successfully shaकरोwed or alपढ़ोy shaकरोwed, -EAGAIN अगर the
 * shaकरोw table काष्ठाure is incomplete, -ENOMEM अगर out of memory and
 * -EFAULT अगर an address in the parent gmap could not be resolved.
 *
 * Called with sg->mm->mmap_lock in पढ़ो.
 */
पूर्णांक gmap_shaकरोw_r2t(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ r2t,
		    पूर्णांक fake)
अणु
	अचिन्हित दीर्घ raddr, origin, offset, len;
	अचिन्हित दीर्घ *s_r2t, *table;
	काष्ठा page *page;
	पूर्णांक rc;

	BUG_ON(!gmap_is_shaकरोw(sg));
	/* Allocate a shaकरोw region second table */
	page = alloc_pages(GFP_KERNEL_ACCOUNT, CRST_ALLOC_ORDER);
	अगर (!page)
		वापस -ENOMEM;
	page->index = r2t & _REGION_ENTRY_ORIGIN;
	अगर (fake)
		page->index |= GMAP_SHADOW_FAKE_TABLE;
	s_r2t = (अचिन्हित दीर्घ *) page_to_phys(page);
	/* Install shaकरोw region second table */
	spin_lock(&sg->guest_table_lock);
	table = gmap_table_walk(sg, saddr, 4); /* get region-1 poपूर्णांकer */
	अगर (!table) अणु
		rc = -EAGAIN;		/* Race with unshaकरोw */
		जाओ out_मुक्त;
	पूर्ण
	अगर (!(*table & _REGION_ENTRY_INVALID)) अणु
		rc = 0;			/* Alपढ़ोy established */
		जाओ out_मुक्त;
	पूर्ण अन्यथा अगर (*table & _REGION_ENTRY_ORIGIN) अणु
		rc = -EAGAIN;		/* Race with shaकरोw */
		जाओ out_मुक्त;
	पूर्ण
	crst_table_init(s_r2t, _REGION2_ENTRY_EMPTY);
	/* mark as invalid as दीर्घ as the parent table is not रक्षित */
	*table = (अचिन्हित दीर्घ) s_r2t | _REGION_ENTRY_LENGTH |
		 _REGION_ENTRY_TYPE_R1 | _REGION_ENTRY_INVALID;
	अगर (sg->edat_level >= 1)
		*table |= (r2t & _REGION_ENTRY_PROTECT);
	list_add(&page->lru, &sg->crst_list);
	अगर (fake) अणु
		/* nothing to protect क्रम fake tables */
		*table &= ~_REGION_ENTRY_INVALID;
		spin_unlock(&sg->guest_table_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
	/* Make r2t पढ़ो-only in parent gmap page table */
	raddr = (saddr & _REGION1_MASK) | _SHADOW_RMAP_REGION1;
	origin = r2t & _REGION_ENTRY_ORIGIN;
	offset = ((r2t & _REGION_ENTRY_OFFSET) >> 6) * PAGE_SIZE;
	len = ((r2t & _REGION_ENTRY_LENGTH) + 1) * PAGE_SIZE - offset;
	rc = gmap_protect_rmap(sg, raddr, origin + offset, len);
	spin_lock(&sg->guest_table_lock);
	अगर (!rc) अणु
		table = gmap_table_walk(sg, saddr, 4);
		अगर (!table || (*table & _REGION_ENTRY_ORIGIN) !=
			      (अचिन्हित दीर्घ) s_r2t)
			rc = -EAGAIN;		/* Race with unshaकरोw */
		अन्यथा
			*table &= ~_REGION_ENTRY_INVALID;
	पूर्ण अन्यथा अणु
		gmap_unshaकरोw_r2t(sg, raddr);
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
	वापस rc;
out_मुक्त:
	spin_unlock(&sg->guest_table_lock);
	__मुक्त_pages(page, CRST_ALLOC_ORDER);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_shaकरोw_r2t);

/**
 * gmap_shaकरोw_r3t - create a shaकरोw region 3 table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @saddr: faulting address in the shaकरोw gmap
 * @r3t: parent gmap address of the region 3 table to get shaकरोwed
 * @fake: r3t references contiguous guest memory block, not a r3t
 *
 * Returns 0 अगर successfully shaकरोwed or alपढ़ोy shaकरोwed, -EAGAIN अगर the
 * shaकरोw table काष्ठाure is incomplete, -ENOMEM अगर out of memory and
 * -EFAULT अगर an address in the parent gmap could not be resolved.
 *
 * Called with sg->mm->mmap_lock in पढ़ो.
 */
पूर्णांक gmap_shaकरोw_r3t(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ r3t,
		    पूर्णांक fake)
अणु
	अचिन्हित दीर्घ raddr, origin, offset, len;
	अचिन्हित दीर्घ *s_r3t, *table;
	काष्ठा page *page;
	पूर्णांक rc;

	BUG_ON(!gmap_is_shaकरोw(sg));
	/* Allocate a shaकरोw region second table */
	page = alloc_pages(GFP_KERNEL_ACCOUNT, CRST_ALLOC_ORDER);
	अगर (!page)
		वापस -ENOMEM;
	page->index = r3t & _REGION_ENTRY_ORIGIN;
	अगर (fake)
		page->index |= GMAP_SHADOW_FAKE_TABLE;
	s_r3t = (अचिन्हित दीर्घ *) page_to_phys(page);
	/* Install shaकरोw region second table */
	spin_lock(&sg->guest_table_lock);
	table = gmap_table_walk(sg, saddr, 3); /* get region-2 poपूर्णांकer */
	अगर (!table) अणु
		rc = -EAGAIN;		/* Race with unshaकरोw */
		जाओ out_मुक्त;
	पूर्ण
	अगर (!(*table & _REGION_ENTRY_INVALID)) अणु
		rc = 0;			/* Alपढ़ोy established */
		जाओ out_मुक्त;
	पूर्ण अन्यथा अगर (*table & _REGION_ENTRY_ORIGIN) अणु
		rc = -EAGAIN;		/* Race with shaकरोw */
		जाओ out_मुक्त;
	पूर्ण
	crst_table_init(s_r3t, _REGION3_ENTRY_EMPTY);
	/* mark as invalid as दीर्घ as the parent table is not रक्षित */
	*table = (अचिन्हित दीर्घ) s_r3t | _REGION_ENTRY_LENGTH |
		 _REGION_ENTRY_TYPE_R2 | _REGION_ENTRY_INVALID;
	अगर (sg->edat_level >= 1)
		*table |= (r3t & _REGION_ENTRY_PROTECT);
	list_add(&page->lru, &sg->crst_list);
	अगर (fake) अणु
		/* nothing to protect क्रम fake tables */
		*table &= ~_REGION_ENTRY_INVALID;
		spin_unlock(&sg->guest_table_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
	/* Make r3t पढ़ो-only in parent gmap page table */
	raddr = (saddr & _REGION2_MASK) | _SHADOW_RMAP_REGION2;
	origin = r3t & _REGION_ENTRY_ORIGIN;
	offset = ((r3t & _REGION_ENTRY_OFFSET) >> 6) * PAGE_SIZE;
	len = ((r3t & _REGION_ENTRY_LENGTH) + 1) * PAGE_SIZE - offset;
	rc = gmap_protect_rmap(sg, raddr, origin + offset, len);
	spin_lock(&sg->guest_table_lock);
	अगर (!rc) अणु
		table = gmap_table_walk(sg, saddr, 3);
		अगर (!table || (*table & _REGION_ENTRY_ORIGIN) !=
			      (अचिन्हित दीर्घ) s_r3t)
			rc = -EAGAIN;		/* Race with unshaकरोw */
		अन्यथा
			*table &= ~_REGION_ENTRY_INVALID;
	पूर्ण अन्यथा अणु
		gmap_unshaकरोw_r3t(sg, raddr);
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
	वापस rc;
out_मुक्त:
	spin_unlock(&sg->guest_table_lock);
	__मुक्त_pages(page, CRST_ALLOC_ORDER);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_shaकरोw_r3t);

/**
 * gmap_shaकरोw_sgt - create a shaकरोw segment table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @saddr: faulting address in the shaकरोw gmap
 * @sgt: parent gmap address of the segment table to get shaकरोwed
 * @fake: sgt references contiguous guest memory block, not a sgt
 *
 * Returns: 0 अगर successfully shaकरोwed or alपढ़ोy shaकरोwed, -EAGAIN अगर the
 * shaकरोw table काष्ठाure is incomplete, -ENOMEM अगर out of memory and
 * -EFAULT अगर an address in the parent gmap could not be resolved.
 *
 * Called with sg->mm->mmap_lock in पढ़ो.
 */
पूर्णांक gmap_shaकरोw_sgt(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ sgt,
		    पूर्णांक fake)
अणु
	अचिन्हित दीर्घ raddr, origin, offset, len;
	अचिन्हित दीर्घ *s_sgt, *table;
	काष्ठा page *page;
	पूर्णांक rc;

	BUG_ON(!gmap_is_shaकरोw(sg) || (sgt & _REGION3_ENTRY_LARGE));
	/* Allocate a shaकरोw segment table */
	page = alloc_pages(GFP_KERNEL_ACCOUNT, CRST_ALLOC_ORDER);
	अगर (!page)
		वापस -ENOMEM;
	page->index = sgt & _REGION_ENTRY_ORIGIN;
	अगर (fake)
		page->index |= GMAP_SHADOW_FAKE_TABLE;
	s_sgt = (अचिन्हित दीर्घ *) page_to_phys(page);
	/* Install shaकरोw region second table */
	spin_lock(&sg->guest_table_lock);
	table = gmap_table_walk(sg, saddr, 2); /* get region-3 poपूर्णांकer */
	अगर (!table) अणु
		rc = -EAGAIN;		/* Race with unshaकरोw */
		जाओ out_मुक्त;
	पूर्ण
	अगर (!(*table & _REGION_ENTRY_INVALID)) अणु
		rc = 0;			/* Alपढ़ोy established */
		जाओ out_मुक्त;
	पूर्ण अन्यथा अगर (*table & _REGION_ENTRY_ORIGIN) अणु
		rc = -EAGAIN;		/* Race with shaकरोw */
		जाओ out_मुक्त;
	पूर्ण
	crst_table_init(s_sgt, _SEGMENT_ENTRY_EMPTY);
	/* mark as invalid as दीर्घ as the parent table is not रक्षित */
	*table = (अचिन्हित दीर्घ) s_sgt | _REGION_ENTRY_LENGTH |
		 _REGION_ENTRY_TYPE_R3 | _REGION_ENTRY_INVALID;
	अगर (sg->edat_level >= 1)
		*table |= sgt & _REGION_ENTRY_PROTECT;
	list_add(&page->lru, &sg->crst_list);
	अगर (fake) अणु
		/* nothing to protect क्रम fake tables */
		*table &= ~_REGION_ENTRY_INVALID;
		spin_unlock(&sg->guest_table_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
	/* Make sgt पढ़ो-only in parent gmap page table */
	raddr = (saddr & _REGION3_MASK) | _SHADOW_RMAP_REGION3;
	origin = sgt & _REGION_ENTRY_ORIGIN;
	offset = ((sgt & _REGION_ENTRY_OFFSET) >> 6) * PAGE_SIZE;
	len = ((sgt & _REGION_ENTRY_LENGTH) + 1) * PAGE_SIZE - offset;
	rc = gmap_protect_rmap(sg, raddr, origin + offset, len);
	spin_lock(&sg->guest_table_lock);
	अगर (!rc) अणु
		table = gmap_table_walk(sg, saddr, 2);
		अगर (!table || (*table & _REGION_ENTRY_ORIGIN) !=
			      (अचिन्हित दीर्घ) s_sgt)
			rc = -EAGAIN;		/* Race with unshaकरोw */
		अन्यथा
			*table &= ~_REGION_ENTRY_INVALID;
	पूर्ण अन्यथा अणु
		gmap_unshaकरोw_sgt(sg, raddr);
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
	वापस rc;
out_मुक्त:
	spin_unlock(&sg->guest_table_lock);
	__मुक्त_pages(page, CRST_ALLOC_ORDER);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_shaकरोw_sgt);

/**
 * gmap_shaकरोw_lookup_pgtable - find a shaकरोw page table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @saddr: the address in the shaकरोw aguest address space
 * @pgt: parent gmap address of the page table to get shaकरोwed
 * @dat_protection: अगर the pgtable is marked as रक्षित by dat
 * @fake: pgt references contiguous guest memory block, not a pgtable
 *
 * Returns 0 अगर the shaकरोw page table was found and -EAGAIN अगर the page
 * table was not found.
 *
 * Called with sg->mm->mmap_lock in पढ़ो.
 */
पूर्णांक gmap_shaकरोw_pgt_lookup(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr,
			   अचिन्हित दीर्घ *pgt, पूर्णांक *dat_protection,
			   पूर्णांक *fake)
अणु
	अचिन्हित दीर्घ *table;
	काष्ठा page *page;
	पूर्णांक rc;

	BUG_ON(!gmap_is_shaकरोw(sg));
	spin_lock(&sg->guest_table_lock);
	table = gmap_table_walk(sg, saddr, 1); /* get segment poपूर्णांकer */
	अगर (table && !(*table & _SEGMENT_ENTRY_INVALID)) अणु
		/* Shaकरोw page tables are full pages (pte+pgste) */
		page = pfn_to_page(*table >> PAGE_SHIFT);
		*pgt = page->index & ~GMAP_SHADOW_FAKE_TABLE;
		*dat_protection = !!(*table & _SEGMENT_ENTRY_PROTECT);
		*fake = !!(page->index & GMAP_SHADOW_FAKE_TABLE);
		rc = 0;
	पूर्ण अन्यथा  अणु
		rc = -EAGAIN;
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
	वापस rc;

पूर्ण
EXPORT_SYMBOL_GPL(gmap_shaकरोw_pgt_lookup);

/**
 * gmap_shaकरोw_pgt - instantiate a shaकरोw page table
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @saddr: faulting address in the shaकरोw gmap
 * @pgt: parent gmap address of the page table to get shaकरोwed
 * @fake: pgt references contiguous guest memory block, not a pgtable
 *
 * Returns 0 अगर successfully shaकरोwed or alपढ़ोy shaकरोwed, -EAGAIN अगर the
 * shaकरोw table काष्ठाure is incomplete, -ENOMEM अगर out of memory,
 * -EFAULT अगर an address in the parent gmap could not be resolved and
 *
 * Called with gmap->mm->mmap_lock in पढ़ो
 */
पूर्णांक gmap_shaकरोw_pgt(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ pgt,
		    पूर्णांक fake)
अणु
	अचिन्हित दीर्घ raddr, origin;
	अचिन्हित दीर्घ *s_pgt, *table;
	काष्ठा page *page;
	पूर्णांक rc;

	BUG_ON(!gmap_is_shaकरोw(sg) || (pgt & _SEGMENT_ENTRY_LARGE));
	/* Allocate a shaकरोw page table */
	page = page_table_alloc_pgste(sg->mm);
	अगर (!page)
		वापस -ENOMEM;
	page->index = pgt & _SEGMENT_ENTRY_ORIGIN;
	अगर (fake)
		page->index |= GMAP_SHADOW_FAKE_TABLE;
	s_pgt = (अचिन्हित दीर्घ *) page_to_phys(page);
	/* Install shaकरोw page table */
	spin_lock(&sg->guest_table_lock);
	table = gmap_table_walk(sg, saddr, 1); /* get segment poपूर्णांकer */
	अगर (!table) अणु
		rc = -EAGAIN;		/* Race with unshaकरोw */
		जाओ out_मुक्त;
	पूर्ण
	अगर (!(*table & _SEGMENT_ENTRY_INVALID)) अणु
		rc = 0;			/* Alपढ़ोy established */
		जाओ out_मुक्त;
	पूर्ण अन्यथा अगर (*table & _SEGMENT_ENTRY_ORIGIN) अणु
		rc = -EAGAIN;		/* Race with shaकरोw */
		जाओ out_मुक्त;
	पूर्ण
	/* mark as invalid as दीर्घ as the parent table is not रक्षित */
	*table = (अचिन्हित दीर्घ) s_pgt | _SEGMENT_ENTRY |
		 (pgt & _SEGMENT_ENTRY_PROTECT) | _SEGMENT_ENTRY_INVALID;
	list_add(&page->lru, &sg->pt_list);
	अगर (fake) अणु
		/* nothing to protect क्रम fake tables */
		*table &= ~_SEGMENT_ENTRY_INVALID;
		spin_unlock(&sg->guest_table_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
	/* Make pgt पढ़ो-only in parent gmap page table (not the pgste) */
	raddr = (saddr & _SEGMENT_MASK) | _SHADOW_RMAP_SEGMENT;
	origin = pgt & _SEGMENT_ENTRY_ORIGIN & PAGE_MASK;
	rc = gmap_protect_rmap(sg, raddr, origin, PAGE_SIZE);
	spin_lock(&sg->guest_table_lock);
	अगर (!rc) अणु
		table = gmap_table_walk(sg, saddr, 1);
		अगर (!table || (*table & _SEGMENT_ENTRY_ORIGIN) !=
			      (अचिन्हित दीर्घ) s_pgt)
			rc = -EAGAIN;		/* Race with unshaकरोw */
		अन्यथा
			*table &= ~_SEGMENT_ENTRY_INVALID;
	पूर्ण अन्यथा अणु
		gmap_unshaकरोw_pgt(sg, raddr);
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
	वापस rc;
out_मुक्त:
	spin_unlock(&sg->guest_table_lock);
	page_table_मुक्त_pgste(page);
	वापस rc;

पूर्ण
EXPORT_SYMBOL_GPL(gmap_shaकरोw_pgt);

/**
 * gmap_shaकरोw_page - create a shaकरोw page mapping
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @saddr: faulting address in the shaकरोw gmap
 * @pte: pte in parent gmap address space to get shaकरोwed
 *
 * Returns 0 अगर successfully shaकरोwed or alपढ़ोy shaकरोwed, -EAGAIN अगर the
 * shaकरोw table काष्ठाure is incomplete, -ENOMEM अगर out of memory and
 * -EFAULT अगर an address in the parent gmap could not be resolved.
 *
 * Called with sg->mm->mmap_lock in पढ़ो.
 */
पूर्णांक gmap_shaकरोw_page(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, pte_t pte)
अणु
	काष्ठा gmap *parent;
	काष्ठा gmap_rmap *rmap;
	अचिन्हित दीर्घ vmaddr, paddr;
	spinlock_t *ptl;
	pte_t *sptep, *tptep;
	पूर्णांक prot;
	पूर्णांक rc;

	BUG_ON(!gmap_is_shaकरोw(sg));
	parent = sg->parent;
	prot = (pte_val(pte) & _PAGE_PROTECT) ? PROT_READ : PROT_WRITE;

	rmap = kzalloc(माप(*rmap), GFP_KERNEL_ACCOUNT);
	अगर (!rmap)
		वापस -ENOMEM;
	rmap->raddr = (saddr & PAGE_MASK) | _SHADOW_RMAP_PGTABLE;

	जबतक (1) अणु
		paddr = pte_val(pte) & PAGE_MASK;
		vmaddr = __gmap_translate(parent, paddr);
		अगर (IS_ERR_VALUE(vmaddr)) अणु
			rc = vmaddr;
			अवरोध;
		पूर्ण
		rc = radix_tree_preload(GFP_KERNEL_ACCOUNT);
		अगर (rc)
			अवरोध;
		rc = -EAGAIN;
		sptep = gmap_pte_op_walk(parent, paddr, &ptl);
		अगर (sptep) अणु
			spin_lock(&sg->guest_table_lock);
			/* Get page table poपूर्णांकer */
			tptep = (pte_t *) gmap_table_walk(sg, saddr, 0);
			अगर (!tptep) अणु
				spin_unlock(&sg->guest_table_lock);
				gmap_pte_op_end(ptl);
				radix_tree_preload_end();
				अवरोध;
			पूर्ण
			rc = ptep_shaकरोw_pte(sg->mm, saddr, sptep, tptep, pte);
			अगर (rc > 0) अणु
				/* Success and a new mapping */
				gmap_insert_rmap(sg, vmaddr, rmap);
				rmap = शून्य;
				rc = 0;
			पूर्ण
			gmap_pte_op_end(ptl);
			spin_unlock(&sg->guest_table_lock);
		पूर्ण
		radix_tree_preload_end();
		अगर (!rc)
			अवरोध;
		rc = gmap_pte_op_fixup(parent, paddr, vmaddr, prot);
		अगर (rc)
			अवरोध;
	पूर्ण
	kमुक्त(rmap);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_shaकरोw_page);

/**
 * gmap_shaकरोw_notअगरy - handle notअगरications क्रम shaकरोw gmap
 *
 * Called with sg->parent->shaकरोw_lock.
 */
अटल व्योम gmap_shaकरोw_notअगरy(काष्ठा gmap *sg, अचिन्हित दीर्घ vmaddr,
			       अचिन्हित दीर्घ gaddr)
अणु
	काष्ठा gmap_rmap *rmap, *rnext, *head;
	अचिन्हित दीर्घ start, end, bits, raddr;

	BUG_ON(!gmap_is_shaकरोw(sg));

	spin_lock(&sg->guest_table_lock);
	अगर (sg->हटाओd) अणु
		spin_unlock(&sg->guest_table_lock);
		वापस;
	पूर्ण
	/* Check क्रम top level table */
	start = sg->orig_asce & _ASCE_ORIGIN;
	end = start + ((sg->orig_asce & _ASCE_TABLE_LENGTH) + 1) * PAGE_SIZE;
	अगर (!(sg->orig_asce & _ASCE_REAL_SPACE) && gaddr >= start &&
	    gaddr < end) अणु
		/* The complete shaकरोw table has to go */
		gmap_unshaकरोw(sg);
		spin_unlock(&sg->guest_table_lock);
		list_del(&sg->list);
		gmap_put(sg);
		वापस;
	पूर्ण
	/* Remove the page table tree from on specअगरic entry */
	head = radix_tree_delete(&sg->host_to_rmap, vmaddr >> PAGE_SHIFT);
	gmap_क्रम_each_rmap_safe(rmap, rnext, head) अणु
		bits = rmap->raddr & _SHADOW_RMAP_MASK;
		raddr = rmap->raddr ^ bits;
		चयन (bits) अणु
		हाल _SHADOW_RMAP_REGION1:
			gmap_unshaकरोw_r2t(sg, raddr);
			अवरोध;
		हाल _SHADOW_RMAP_REGION2:
			gmap_unshaकरोw_r3t(sg, raddr);
			अवरोध;
		हाल _SHADOW_RMAP_REGION3:
			gmap_unshaकरोw_sgt(sg, raddr);
			अवरोध;
		हाल _SHADOW_RMAP_SEGMENT:
			gmap_unshaकरोw_pgt(sg, raddr);
			अवरोध;
		हाल _SHADOW_RMAP_PGTABLE:
			gmap_unshaकरोw_page(sg, raddr);
			अवरोध;
		पूर्ण
		kमुक्त(rmap);
	पूर्ण
	spin_unlock(&sg->guest_table_lock);
पूर्ण

/**
 * ptep_notअगरy - call all invalidation callbacks क्रम a specअगरic pte.
 * @mm: poपूर्णांकer to the process mm_काष्ठा
 * @addr: भव address in the process address space
 * @pte: poपूर्णांकer to the page table entry
 * @bits: bits from the pgste that caused the notअगरy call
 *
 * This function is assumed to be called with the page table lock held
 * क्रम the pte to notअगरy.
 */
व्योम ptep_notअगरy(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
		 pte_t *pte, अचिन्हित दीर्घ bits)
अणु
	अचिन्हित दीर्घ offset, gaddr = 0;
	अचिन्हित दीर्घ *table;
	काष्ठा gmap *gmap, *sg, *next;

	offset = ((अचिन्हित दीर्घ) pte) & (255 * माप(pte_t));
	offset = offset * (PAGE_SIZE / माप(pte_t));
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(gmap, &mm->context.gmap_list, list) अणु
		spin_lock(&gmap->guest_table_lock);
		table = radix_tree_lookup(&gmap->host_to_guest,
					  vmaddr >> PMD_SHIFT);
		अगर (table)
			gaddr = __gmap_segment_gaddr(table) + offset;
		spin_unlock(&gmap->guest_table_lock);
		अगर (!table)
			जारी;

		अगर (!list_empty(&gmap->children) && (bits & PGSTE_VSIE_BIT)) अणु
			spin_lock(&gmap->shaकरोw_lock);
			list_क्रम_each_entry_safe(sg, next,
						 &gmap->children, list)
				gmap_shaकरोw_notअगरy(sg, vmaddr, gaddr);
			spin_unlock(&gmap->shaकरोw_lock);
		पूर्ण
		अगर (bits & PGSTE_IN_BIT)
			gmap_call_notअगरier(gmap, gaddr, gaddr + PAGE_SIZE - 1);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(ptep_notअगरy);

अटल व्योम pmdp_notअगरy_gmap(काष्ठा gmap *gmap, pmd_t *pmdp,
			     अचिन्हित दीर्घ gaddr)
अणु
	pmd_val(*pmdp) &= ~_SEGMENT_ENTRY_GMAP_IN;
	gmap_call_notअगरier(gmap, gaddr, gaddr + HPAGE_SIZE - 1);
पूर्ण

/**
 * gmap_pmdp_xchg - exchange a gmap pmd with another
 * @gmap: poपूर्णांकer to the guest address space काष्ठाure
 * @pmdp: poपूर्णांकer to the pmd entry
 * @new: replacement entry
 * @gaddr: the affected guest address
 *
 * This function is assumed to be called with the guest_table_lock
 * held.
 */
अटल व्योम gmap_pmdp_xchg(काष्ठा gmap *gmap, pmd_t *pmdp, pmd_t new,
			   अचिन्हित दीर्घ gaddr)
अणु
	gaddr &= HPAGE_MASK;
	pmdp_notअगरy_gmap(gmap, pmdp, gaddr);
	pmd_val(new) &= ~_SEGMENT_ENTRY_GMAP_IN;
	अगर (MACHINE_HAS_TLB_GUEST)
		__pmdp_idte(gaddr, (pmd_t *)pmdp, IDTE_GUEST_ASCE, gmap->asce,
			    IDTE_GLOBAL);
	अन्यथा अगर (MACHINE_HAS_IDTE)
		__pmdp_idte(gaddr, (pmd_t *)pmdp, 0, 0, IDTE_GLOBAL);
	अन्यथा
		__pmdp_csp(pmdp);
	*pmdp = new;
पूर्ण

अटल व्योम gmap_pmdp_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
			    पूर्णांक purge)
अणु
	pmd_t *pmdp;
	काष्ठा gmap *gmap;
	अचिन्हित दीर्घ gaddr;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(gmap, &mm->context.gmap_list, list) अणु
		spin_lock(&gmap->guest_table_lock);
		pmdp = (pmd_t *)radix_tree_delete(&gmap->host_to_guest,
						  vmaddr >> PMD_SHIFT);
		अगर (pmdp) अणु
			gaddr = __gmap_segment_gaddr((अचिन्हित दीर्घ *)pmdp);
			pmdp_notअगरy_gmap(gmap, pmdp, gaddr);
			WARN_ON(pmd_val(*pmdp) & ~(_SEGMENT_ENTRY_HARDWARE_BITS_LARGE |
						   _SEGMENT_ENTRY_GMAP_UC));
			अगर (purge)
				__pmdp_csp(pmdp);
			pmd_val(*pmdp) = _SEGMENT_ENTRY_EMPTY;
		पूर्ण
		spin_unlock(&gmap->guest_table_lock);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * gmap_pmdp_invalidate - invalidate all affected guest pmd entries without
 *                        flushing
 * @mm: poपूर्णांकer to the process mm_काष्ठा
 * @vmaddr: भव address in the process address space
 */
व्योम gmap_pmdp_invalidate(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr)
अणु
	gmap_pmdp_clear(mm, vmaddr, 0);
पूर्ण
EXPORT_SYMBOL_GPL(gmap_pmdp_invalidate);

/**
 * gmap_pmdp_csp - csp all affected guest pmd entries
 * @mm: poपूर्णांकer to the process mm_काष्ठा
 * @vmaddr: भव address in the process address space
 */
व्योम gmap_pmdp_csp(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr)
अणु
	gmap_pmdp_clear(mm, vmaddr, 1);
पूर्ण
EXPORT_SYMBOL_GPL(gmap_pmdp_csp);

/**
 * gmap_pmdp_idte_local - invalidate and clear a guest pmd entry
 * @mm: poपूर्णांकer to the process mm_काष्ठा
 * @vmaddr: भव address in the process address space
 */
व्योम gmap_pmdp_idte_local(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr)
अणु
	अचिन्हित दीर्घ *entry, gaddr;
	काष्ठा gmap *gmap;
	pmd_t *pmdp;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(gmap, &mm->context.gmap_list, list) अणु
		spin_lock(&gmap->guest_table_lock);
		entry = radix_tree_delete(&gmap->host_to_guest,
					  vmaddr >> PMD_SHIFT);
		अगर (entry) अणु
			pmdp = (pmd_t *)entry;
			gaddr = __gmap_segment_gaddr(entry);
			pmdp_notअगरy_gmap(gmap, pmdp, gaddr);
			WARN_ON(*entry & ~(_SEGMENT_ENTRY_HARDWARE_BITS_LARGE |
					   _SEGMENT_ENTRY_GMAP_UC));
			अगर (MACHINE_HAS_TLB_GUEST)
				__pmdp_idte(gaddr, pmdp, IDTE_GUEST_ASCE,
					    gmap->asce, IDTE_LOCAL);
			अन्यथा अगर (MACHINE_HAS_IDTE)
				__pmdp_idte(gaddr, pmdp, 0, 0, IDTE_LOCAL);
			*entry = _SEGMENT_ENTRY_EMPTY;
		पूर्ण
		spin_unlock(&gmap->guest_table_lock);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(gmap_pmdp_idte_local);

/**
 * gmap_pmdp_idte_global - invalidate and clear a guest pmd entry
 * @mm: poपूर्णांकer to the process mm_काष्ठा
 * @vmaddr: भव address in the process address space
 */
व्योम gmap_pmdp_idte_global(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr)
अणु
	अचिन्हित दीर्घ *entry, gaddr;
	काष्ठा gmap *gmap;
	pmd_t *pmdp;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(gmap, &mm->context.gmap_list, list) अणु
		spin_lock(&gmap->guest_table_lock);
		entry = radix_tree_delete(&gmap->host_to_guest,
					  vmaddr >> PMD_SHIFT);
		अगर (entry) अणु
			pmdp = (pmd_t *)entry;
			gaddr = __gmap_segment_gaddr(entry);
			pmdp_notअगरy_gmap(gmap, pmdp, gaddr);
			WARN_ON(*entry & ~(_SEGMENT_ENTRY_HARDWARE_BITS_LARGE |
					   _SEGMENT_ENTRY_GMAP_UC));
			अगर (MACHINE_HAS_TLB_GUEST)
				__pmdp_idte(gaddr, pmdp, IDTE_GUEST_ASCE,
					    gmap->asce, IDTE_GLOBAL);
			अन्यथा अगर (MACHINE_HAS_IDTE)
				__pmdp_idte(gaddr, pmdp, 0, 0, IDTE_GLOBAL);
			अन्यथा
				__pmdp_csp(pmdp);
			*entry = _SEGMENT_ENTRY_EMPTY;
		पूर्ण
		spin_unlock(&gmap->guest_table_lock);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(gmap_pmdp_idte_global);

/**
 * gmap_test_and_clear_dirty_pmd - test and reset segment dirty status
 * @gmap: poपूर्णांकer to guest address space
 * @pmdp: poपूर्णांकer to the pmd to be tested
 * @gaddr: भव address in the guest address space
 *
 * This function is assumed to be called with the guest_table_lock
 * held.
 */
अटल bool gmap_test_and_clear_dirty_pmd(काष्ठा gmap *gmap, pmd_t *pmdp,
					  अचिन्हित दीर्घ gaddr)
अणु
	अगर (pmd_val(*pmdp) & _SEGMENT_ENTRY_INVALID)
		वापस false;

	/* Alपढ़ोy रक्षित memory, which did not change is clean */
	अगर (pmd_val(*pmdp) & _SEGMENT_ENTRY_PROTECT &&
	    !(pmd_val(*pmdp) & _SEGMENT_ENTRY_GMAP_UC))
		वापस false;

	/* Clear UC indication and reset protection */
	pmd_val(*pmdp) &= ~_SEGMENT_ENTRY_GMAP_UC;
	gmap_protect_pmd(gmap, gaddr, pmdp, PROT_READ, 0);
	वापस true;
पूर्ण

/**
 * gmap_sync_dirty_log_pmd - set biपंचांगap based on dirty status of segment
 * @gmap: poपूर्णांकer to guest address space
 * @biपंचांगap: dirty biपंचांगap क्रम this pmd
 * @gaddr: भव address in the guest address space
 * @vmaddr: भव address in the host address space
 *
 * This function is assumed to be called with the guest_table_lock
 * held.
 */
व्योम gmap_sync_dirty_log_pmd(काष्ठा gmap *gmap, अचिन्हित दीर्घ biपंचांगap[4],
			     अचिन्हित दीर्घ gaddr, अचिन्हित दीर्घ vmaddr)
अणु
	पूर्णांक i;
	pmd_t *pmdp;
	pte_t *ptep;
	spinlock_t *ptl;

	pmdp = gmap_pmd_op_walk(gmap, gaddr);
	अगर (!pmdp)
		वापस;

	अगर (pmd_large(*pmdp)) अणु
		अगर (gmap_test_and_clear_dirty_pmd(gmap, pmdp, gaddr))
			biपंचांगap_fill(biपंचांगap, _PAGE_ENTRIES);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < _PAGE_ENTRIES; i++, vmaddr += PAGE_SIZE) अणु
			ptep = pte_alloc_map_lock(gmap->mm, pmdp, vmaddr, &ptl);
			अगर (!ptep)
				जारी;
			अगर (ptep_test_and_clear_uc(gmap->mm, vmaddr, ptep))
				set_bit(i, biपंचांगap);
			spin_unlock(ptl);
		पूर्ण
	पूर्ण
	gmap_pmd_op_end(gmap, pmdp);
पूर्ण
EXPORT_SYMBOL_GPL(gmap_sync_dirty_log_pmd);

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल पूर्णांक thp_split_walk_pmd_entry(pmd_t *pmd, अचिन्हित दीर्घ addr,
				    अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	काष्ठा vm_area_काष्ठा *vma = walk->vma;

	split_huge_pmd(vma, pmd, addr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops thp_split_walk_ops = अणु
	.pmd_entry	= thp_split_walk_pmd_entry,
पूर्ण;

अटल अंतरभूत व्योम thp_split_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	क्रम (vma = mm->mmap; vma != शून्य; vma = vma->vm_next) अणु
		vma->vm_flags &= ~VM_HUGEPAGE;
		vma->vm_flags |= VM_NOHUGEPAGE;
		walk_page_vma(vma, &thp_split_walk_ops, शून्य);
	पूर्ण
	mm->def_flags |= VM_NOHUGEPAGE;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम thp_split_mm(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

/*
 * Remove all empty zero pages from the mapping क्रम lazy refaulting
 * - This must be called after mm->context.has_pgste is set, to aव्योम
 *   future creation of zero pages
 * - This must be called after THP was enabled
 */
अटल पूर्णांक __zap_zero_pages(pmd_t *pmd, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ end, काष्ठा mm_walk *walk)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = start; addr != end; addr += PAGE_SIZE) अणु
		pte_t *ptep;
		spinlock_t *ptl;

		ptep = pte_offset_map_lock(walk->mm, pmd, addr, &ptl);
		अगर (is_zero_pfn(pte_pfn(*ptep)))
			ptep_xchg_direct(walk->mm, addr, ptep, __pte(_PAGE_INVALID));
		pte_unmap_unlock(ptep, ptl);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops zap_zero_walk_ops = अणु
	.pmd_entry	= __zap_zero_pages,
पूर्ण;

/*
 * चयन on pgstes क्रम its userspace process (क्रम kvm)
 */
पूर्णांक s390_enable_sie(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;

	/* Do we have pgstes? अगर yes, we are करोne */
	अगर (mm_has_pgste(mm))
		वापस 0;
	/* Fail अगर the page tables are 2K */
	अगर (!mm_alloc_pgste(mm))
		वापस -EINVAL;
	mmap_ग_लिखो_lock(mm);
	mm->context.has_pgste = 1;
	/* split thp mappings and disable thp क्रम future mappings */
	thp_split_mm(mm);
	walk_page_range(mm, 0, TASK_SIZE, &zap_zero_walk_ops, शून्य);
	mmap_ग_लिखो_unlock(mm);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(s390_enable_sie);

पूर्णांक gmap_mark_unmergeable(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक ret;

	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		ret = ksm_madvise(vma, vma->vm_start, vma->vm_end,
				  MADV_UNMERGEABLE, &vma->vm_flags);
		अगर (ret)
			वापस ret;
	पूर्ण
	mm->def_flags &= ~VM_MERGEABLE;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gmap_mark_unmergeable);

/*
 * Enable storage key handling from now on and initialize the storage
 * keys with the शेष key.
 */
अटल पूर्णांक __s390_enable_skey_pte(pte_t *pte, अचिन्हित दीर्घ addr,
				  अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	/* Clear storage key */
	ptep_zap_key(walk->mm, addr, pte);
	वापस 0;
पूर्ण

अटल पूर्णांक __s390_enable_skey_hugetlb(pte_t *pte, अचिन्हित दीर्घ addr,
				      अचिन्हित दीर्घ hmask, अचिन्हित दीर्घ next,
				      काष्ठा mm_walk *walk)
अणु
	pmd_t *pmd = (pmd_t *)pte;
	अचिन्हित दीर्घ start, end;
	काष्ठा page *page = pmd_page(*pmd);

	/*
	 * The ग_लिखो check makes sure we करो not set a key on shared
	 * memory. This is needed as the walker करोes not dअगरferentiate
	 * between actual guest memory and the process executable or
	 * shared libraries.
	 */
	अगर (pmd_val(*pmd) & _SEGMENT_ENTRY_INVALID ||
	    !(pmd_val(*pmd) & _SEGMENT_ENTRY_WRITE))
		वापस 0;

	start = pmd_val(*pmd) & HPAGE_MASK;
	end = start + HPAGE_SIZE - 1;
	__storage_key_init_range(start, end);
	set_bit(PG_arch_1, &page->flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops enable_skey_walk_ops = अणु
	.hugetlb_entry		= __s390_enable_skey_hugetlb,
	.pte_entry		= __s390_enable_skey_pte,
पूर्ण;

पूर्णांक s390_enable_skey(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक rc = 0;

	mmap_ग_लिखो_lock(mm);
	अगर (mm_uses_skeys(mm))
		जाओ out_up;

	mm->context.uses_skeys = 1;
	rc = gmap_mark_unmergeable();
	अगर (rc) अणु
		mm->context.uses_skeys = 0;
		जाओ out_up;
	पूर्ण
	walk_page_range(mm, 0, TASK_SIZE, &enable_skey_walk_ops, शून्य);

out_up:
	mmap_ग_लिखो_unlock(mm);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(s390_enable_skey);

/*
 * Reset CMMA state, make all pages stable again.
 */
अटल पूर्णांक __s390_reset_cmma(pte_t *pte, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	ptep_zap_unused(walk->mm, addr, pte, 1);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops reset_cmma_walk_ops = अणु
	.pte_entry		= __s390_reset_cmma,
पूर्ण;

व्योम s390_reset_cmma(काष्ठा mm_काष्ठा *mm)
अणु
	mmap_ग_लिखो_lock(mm);
	walk_page_range(mm, 0, TASK_SIZE, &reset_cmma_walk_ops, शून्य);
	mmap_ग_लिखो_unlock(mm);
पूर्ण
EXPORT_SYMBOL_GPL(s390_reset_cmma);

/*
 * make inaccessible pages accessible again
 */
अटल पूर्णांक __s390_reset_acc(pte_t *ptep, अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ next, काष्ठा mm_walk *walk)
अणु
	pte_t pte = READ_ONCE(*ptep);

	अगर (pte_present(pte))
		WARN_ON_ONCE(uv_destroy_page(pte_val(pte) & PAGE_MASK));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mm_walk_ops reset_acc_walk_ops = अणु
	.pte_entry		= __s390_reset_acc,
पूर्ण;

#समावेश <linux/sched/mm.h>
व्योम s390_reset_acc(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (!mm_is_रक्षित(mm))
		वापस;
	/*
	 * we might be called during
	 * reset:                             we walk the pages and clear
	 * बंद of all kvm file descriptors: we walk the pages and clear
	 * निकास of process on fd closure:     vma alपढ़ोy gone, करो nothing
	 */
	अगर (!mmget_not_zero(mm))
		वापस;
	mmap_पढ़ो_lock(mm);
	walk_page_range(mm, 0, TASK_SIZE, &reset_acc_walk_ops, शून्य);
	mmap_पढ़ो_unlock(mm);
	mmput(mm);
पूर्ण
EXPORT_SYMBOL_GPL(s390_reset_acc);
