<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  IOMMU helpers in MMU context.
 *
 *  Copyright (C) 2015 IBM Corp. <aik@ozद_असल.ru>
 */

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mutex.h>
#समावेश <linux/migrate.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/swap.h>
#समावेश <linux/sizes.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pte-walk.h>
#समावेश <linux/mm_अंतरभूत.h>

अटल DEFINE_MUTEX(mem_list_mutex);

#घोषणा MM_IOMMU_TABLE_GROUP_PAGE_सूचीTY	0x1
#घोषणा MM_IOMMU_TABLE_GROUP_PAGE_MASK	~(SZ_4K - 1)

काष्ठा mm_iommu_table_group_mem_t अणु
	काष्ठा list_head next;
	काष्ठा rcu_head rcu;
	अचिन्हित दीर्घ used;
	atomic64_t mapped;
	अचिन्हित पूर्णांक pageshअगरt;
	u64 ua;			/* userspace address */
	u64 entries;		/* number of entries in hpas/hpages[] */
	/*
	 * in mm_iommu_get we temporarily use this to store
	 * काष्ठा page address.
	 *
	 * We need to convert ua to hpa in real mode. Make it
	 * simpler by storing physical address.
	 */
	जोड़ अणु
		काष्ठा page **hpages;	/* vदो_स्मृति'ed */
		phys_addr_t *hpas;
	पूर्ण;
#घोषणा MM_IOMMU_TABLE_INVALID_HPA	((uपूर्णांक64_t)-1)
	u64 dev_hpa;		/* Device memory base address */
पूर्ण;

bool mm_iommu_preरेजिस्टरed(काष्ठा mm_काष्ठा *mm)
अणु
	वापस !list_empty(&mm->context.iommu_group_mem_list);
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_preरेजिस्टरed);

अटल दीर्घ mm_iommu_करो_alloc(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ua,
			      अचिन्हित दीर्घ entries, अचिन्हित दीर्घ dev_hpa,
			      काष्ठा mm_iommu_table_group_mem_t **pmem)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem, *mem2;
	दीर्घ i, ret, locked_entries = 0, pinned = 0;
	अचिन्हित पूर्णांक pageshअगरt;
	अचिन्हित दीर्घ entry, chunk;

	अगर (dev_hpa == MM_IOMMU_TABLE_INVALID_HPA) अणु
		ret = account_locked_vm(mm, entries, true);
		अगर (ret)
			वापस ret;

		locked_entries = entries;
	पूर्ण

	mem = kzalloc(माप(*mem), GFP_KERNEL);
	अगर (!mem) अणु
		ret = -ENOMEM;
		जाओ unlock_निकास;
	पूर्ण

	अगर (dev_hpa != MM_IOMMU_TABLE_INVALID_HPA) अणु
		mem->pageshअगरt = __ffs(dev_hpa | (entries << PAGE_SHIFT));
		mem->dev_hpa = dev_hpa;
		जाओ good_निकास;
	पूर्ण
	mem->dev_hpa = MM_IOMMU_TABLE_INVALID_HPA;

	/*
	 * For a starting poपूर्णांक क्रम a maximum page size calculation
	 * we use @ua and @entries natural alignment to allow IOMMU pages
	 * smaller than huge pages but still bigger than PAGE_SIZE.
	 */
	mem->pageshअगरt = __ffs(ua | (entries << PAGE_SHIFT));
	mem->hpas = vzalloc(array_size(entries, माप(mem->hpas[0])));
	अगर (!mem->hpas) अणु
		kमुक्त(mem);
		ret = -ENOMEM;
		जाओ unlock_निकास;
	पूर्ण

	mmap_पढ़ो_lock(mm);
	chunk = (1UL << (PAGE_SHIFT + MAX_ORDER - 1)) /
			माप(काष्ठा vm_area_काष्ठा *);
	chunk = min(chunk, entries);
	क्रम (entry = 0; entry < entries; entry += chunk) अणु
		अचिन्हित दीर्घ n = min(entries - entry, chunk);

		ret = pin_user_pages(ua + (entry << PAGE_SHIFT), n,
				FOLL_WRITE | FOLL_LONGTERM,
				mem->hpages + entry, शून्य);
		अगर (ret == n) अणु
			pinned += n;
			जारी;
		पूर्ण
		अगर (ret > 0)
			pinned += ret;
		अवरोध;
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	अगर (pinned != entries) अणु
		अगर (!ret)
			ret = -EFAULT;
		जाओ मुक्त_निकास;
	पूर्ण

good_निकास:
	atomic64_set(&mem->mapped, 1);
	mem->used = 1;
	mem->ua = ua;
	mem->entries = entries;

	mutex_lock(&mem_list_mutex);

	list_क्रम_each_entry_rcu(mem2, &mm->context.iommu_group_mem_list, next,
				lockdep_is_held(&mem_list_mutex)) अणु
		/* Overlap? */
		अगर ((mem2->ua < (ua + (entries << PAGE_SHIFT))) &&
				(ua < (mem2->ua +
				       (mem2->entries << PAGE_SHIFT)))) अणु
			ret = -EINVAL;
			mutex_unlock(&mem_list_mutex);
			जाओ मुक्त_निकास;
		पूर्ण
	पूर्ण

	अगर (mem->dev_hpa == MM_IOMMU_TABLE_INVALID_HPA) अणु
		/*
		 * Allow to use larger than 64k IOMMU pages. Only करो that
		 * अगर we are backed by hugetlb. Skip device memory as it is not
		 * backed with page काष्ठाs.
		 */
		pageshअगरt = PAGE_SHIFT;
		क्रम (i = 0; i < entries; ++i) अणु
			काष्ठा page *page = mem->hpages[i];

			अगर ((mem->pageshअगरt > PAGE_SHIFT) && PageHuge(page))
				pageshअगरt = page_shअगरt(compound_head(page));
			mem->pageshअगरt = min(mem->pageshअगरt, pageshअगरt);
			/*
			 * We करोn't need काष्ठा page reference any more, चयन
			 * to physical address.
			 */
			mem->hpas[i] = page_to_pfn(page) << PAGE_SHIFT;
		पूर्ण
	पूर्ण

	list_add_rcu(&mem->next, &mm->context.iommu_group_mem_list);

	mutex_unlock(&mem_list_mutex);

	*pmem = mem;

	वापस 0;

मुक्त_निकास:
	/* मुक्त the references taken */
	unpin_user_pages(mem->hpages, pinned);

	vमुक्त(mem->hpas);
	kमुक्त(mem);

unlock_निकास:
	account_locked_vm(mm, locked_entries, false);

	वापस ret;
पूर्ण

दीर्घ mm_iommu_new(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ua, अचिन्हित दीर्घ entries,
		काष्ठा mm_iommu_table_group_mem_t **pmem)
अणु
	वापस mm_iommu_करो_alloc(mm, ua, entries, MM_IOMMU_TABLE_INVALID_HPA,
			pmem);
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_new);

दीर्घ mm_iommu_newdev(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ua,
		अचिन्हित दीर्घ entries, अचिन्हित दीर्घ dev_hpa,
		काष्ठा mm_iommu_table_group_mem_t **pmem)
अणु
	वापस mm_iommu_करो_alloc(mm, ua, entries, dev_hpa, pmem);
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_newdev);

अटल व्योम mm_iommu_unpin(काष्ठा mm_iommu_table_group_mem_t *mem)
अणु
	दीर्घ i;
	काष्ठा page *page = शून्य;

	अगर (!mem->hpas)
		वापस;

	क्रम (i = 0; i < mem->entries; ++i) अणु
		अगर (!mem->hpas[i])
			जारी;

		page = pfn_to_page(mem->hpas[i] >> PAGE_SHIFT);
		अगर (!page)
			जारी;

		अगर (mem->hpas[i] & MM_IOMMU_TABLE_GROUP_PAGE_सूचीTY)
			SetPageDirty(page);

		unpin_user_page(page);

		mem->hpas[i] = 0;
	पूर्ण
पूर्ण

अटल व्योम mm_iommu_करो_मुक्त(काष्ठा mm_iommu_table_group_mem_t *mem)
अणु

	mm_iommu_unpin(mem);
	vमुक्त(mem->hpas);
	kमुक्त(mem);
पूर्ण

अटल व्योम mm_iommu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem = container_of(head,
			काष्ठा mm_iommu_table_group_mem_t, rcu);

	mm_iommu_करो_मुक्त(mem);
पूर्ण

अटल व्योम mm_iommu_release(काष्ठा mm_iommu_table_group_mem_t *mem)
अणु
	list_del_rcu(&mem->next);
	call_rcu(&mem->rcu, mm_iommu_मुक्त);
पूर्ण

दीर्घ mm_iommu_put(काष्ठा mm_काष्ठा *mm, काष्ठा mm_iommu_table_group_mem_t *mem)
अणु
	दीर्घ ret = 0;
	अचिन्हित दीर्घ unlock_entries = 0;

	mutex_lock(&mem_list_mutex);

	अगर (mem->used == 0) अणु
		ret = -ENOENT;
		जाओ unlock_निकास;
	पूर्ण

	--mem->used;
	/* There are still users, निकास */
	अगर (mem->used)
		जाओ unlock_निकास;

	/* Are there still mappings? */
	अगर (atomic64_cmpxchg(&mem->mapped, 1, 0) != 1) अणु
		++mem->used;
		ret = -EBUSY;
		जाओ unlock_निकास;
	पूर्ण

	अगर (mem->dev_hpa == MM_IOMMU_TABLE_INVALID_HPA)
		unlock_entries = mem->entries;

	/* @mapped became 0 so now mappings are disabled, release the region */
	mm_iommu_release(mem);

unlock_निकास:
	mutex_unlock(&mem_list_mutex);

	account_locked_vm(mm, unlock_entries, false);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_put);

काष्ठा mm_iommu_table_group_mem_t *mm_iommu_lookup(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ ua, अचिन्हित दीर्घ size)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem, *ret = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(mem, &mm->context.iommu_group_mem_list, next) अणु
		अगर ((mem->ua <= ua) &&
				(ua + size <= mem->ua +
				 (mem->entries << PAGE_SHIFT))) अणु
			ret = mem;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_lookup);

काष्ठा mm_iommu_table_group_mem_t *mm_iommu_lookup_rm(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ ua, अचिन्हित दीर्घ size)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem, *ret = शून्य;

	list_क्रम_each_entry_lockless(mem, &mm->context.iommu_group_mem_list,
			next) अणु
		अगर ((mem->ua <= ua) &&
				(ua + size <= mem->ua +
				 (mem->entries << PAGE_SHIFT))) अणु
			ret = mem;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा mm_iommu_table_group_mem_t *mm_iommu_get(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ ua, अचिन्हित दीर्घ entries)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem, *ret = शून्य;

	mutex_lock(&mem_list_mutex);

	list_क्रम_each_entry_rcu(mem, &mm->context.iommu_group_mem_list, next,
				lockdep_is_held(&mem_list_mutex)) अणु
		अगर ((mem->ua == ua) && (mem->entries == entries)) अणु
			ret = mem;
			++mem->used;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&mem_list_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_get);

दीर्घ mm_iommu_ua_to_hpa(काष्ठा mm_iommu_table_group_mem_t *mem,
		अचिन्हित दीर्घ ua, अचिन्हित पूर्णांक pageshअगरt, अचिन्हित दीर्घ *hpa)
अणु
	स्थिर दीर्घ entry = (ua - mem->ua) >> PAGE_SHIFT;
	u64 *va;

	अगर (entry >= mem->entries)
		वापस -EFAULT;

	अगर (pageshअगरt > mem->pageshअगरt)
		वापस -EFAULT;

	अगर (!mem->hpas) अणु
		*hpa = mem->dev_hpa + (ua - mem->ua);
		वापस 0;
	पूर्ण

	va = &mem->hpas[entry];
	*hpa = (*va & MM_IOMMU_TABLE_GROUP_PAGE_MASK) | (ua & ~PAGE_MASK);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_ua_to_hpa);

दीर्घ mm_iommu_ua_to_hpa_rm(काष्ठा mm_iommu_table_group_mem_t *mem,
		अचिन्हित दीर्घ ua, अचिन्हित पूर्णांक pageshअगरt, अचिन्हित दीर्घ *hpa)
अणु
	स्थिर दीर्घ entry = (ua - mem->ua) >> PAGE_SHIFT;
	अचिन्हित दीर्घ *pa;

	अगर (entry >= mem->entries)
		वापस -EFAULT;

	अगर (pageshअगरt > mem->pageshअगरt)
		वापस -EFAULT;

	अगर (!mem->hpas) अणु
		*hpa = mem->dev_hpa + (ua - mem->ua);
		वापस 0;
	पूर्ण

	pa = (व्योम *) vदो_स्मृति_to_phys(&mem->hpas[entry]);
	अगर (!pa)
		वापस -EFAULT;

	*hpa = (*pa & MM_IOMMU_TABLE_GROUP_PAGE_MASK) | (ua & ~PAGE_MASK);

	वापस 0;
पूर्ण

बाह्य व्योम mm_iommu_ua_mark_dirty_rm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ua)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem;
	दीर्घ entry;
	व्योम *va;
	अचिन्हित दीर्घ *pa;

	mem = mm_iommu_lookup_rm(mm, ua, PAGE_SIZE);
	अगर (!mem)
		वापस;

	अगर (mem->dev_hpa != MM_IOMMU_TABLE_INVALID_HPA)
		वापस;

	entry = (ua - mem->ua) >> PAGE_SHIFT;
	va = &mem->hpas[entry];

	pa = (व्योम *) vदो_स्मृति_to_phys(va);
	अगर (!pa)
		वापस;

	*pa |= MM_IOMMU_TABLE_GROUP_PAGE_सूचीTY;
पूर्ण

bool mm_iommu_is_devmem(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ hpa,
		अचिन्हित पूर्णांक pageshअगरt, अचिन्हित दीर्घ *size)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem;
	अचिन्हित दीर्घ end;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(mem, &mm->context.iommu_group_mem_list, next) अणु
		अगर (mem->dev_hpa == MM_IOMMU_TABLE_INVALID_HPA)
			जारी;

		end = mem->dev_hpa + (mem->entries << PAGE_SHIFT);
		अगर ((mem->dev_hpa <= hpa) && (hpa < end)) अणु
			/*
			 * Since the IOMMU page size might be bigger than
			 * PAGE_SIZE, the amount of preरेजिस्टरed memory
			 * starting from @hpa might be smaller than 1<<pageshअगरt
			 * and the caller needs to distinguish this situation.
			 */
			*size = min(1UL << pageshअगरt, end - hpa);
			वापस true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_is_devmem);

दीर्घ mm_iommu_mapped_inc(काष्ठा mm_iommu_table_group_mem_t *mem)
अणु
	अगर (atomic64_inc_not_zero(&mem->mapped))
		वापस 0;

	/* Last mm_iommu_put() has been called, no more mappings allowed() */
	वापस -ENXIO;
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_mapped_inc);

व्योम mm_iommu_mapped_dec(काष्ठा mm_iommu_table_group_mem_t *mem)
अणु
	atomic64_add_unless(&mem->mapped, -1, 1);
पूर्ण
EXPORT_SYMBOL_GPL(mm_iommu_mapped_dec);

व्योम mm_iommu_init(काष्ठा mm_काष्ठा *mm)
अणु
	INIT_LIST_HEAD_RCU(&mm->context.iommu_group_mem_list);
पूर्ण
