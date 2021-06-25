<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO: IOMMU DMA mapping support क्रम TCE on POWER
 *
 * Copyright (C) 2013 IBM Corp.  All rights reserved.
 *     Author: Alexey Kardashevskiy <aik@ozद_असल.ru>
 *
 * Derived from original vfio_iommu_type1.c:
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/err.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/tce.h>
#समावेश <यंत्र/mmu_context.h>

#घोषणा DRIVER_VERSION  "0.1"
#घोषणा DRIVER_AUTHOR   "aik@ozlabs.ru"
#घोषणा DRIVER_DESC     "VFIO IOMMU SPAPR TCE"

अटल व्योम tce_iommu_detach_group(व्योम *iommu_data,
		काष्ठा iommu_group *iommu_group);

/*
 * VFIO IOMMU fd क्रम SPAPR_TCE IOMMU implementation
 *
 * This code handles mapping and unmapping of user data buffers
 * पूर्णांकo DMA'ble space using the IOMMU
 */

काष्ठा tce_iommu_group अणु
	काष्ठा list_head next;
	काष्ठा iommu_group *grp;
पूर्ण;

/*
 * A container needs to remember which preरेजिस्टरed region  it has
 * referenced to करो proper cleanup at the userspace process निकास.
 */
काष्ठा tce_iommu_prereg अणु
	काष्ठा list_head next;
	काष्ठा mm_iommu_table_group_mem_t *mem;
पूर्ण;

/*
 * The container descriptor supports only a single group per container.
 * Required by the API as the container is not supplied with the IOMMU group
 * at the moment of initialization.
 */
काष्ठा tce_container अणु
	काष्ठा mutex lock;
	bool enabled;
	bool v2;
	bool def_winकरोw_pending;
	अचिन्हित दीर्घ locked_pages;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा iommu_table *tables[IOMMU_TABLE_GROUP_MAX_TABLES];
	काष्ठा list_head group_list;
	काष्ठा list_head prereg_list;
पूर्ण;

अटल दीर्घ tce_iommu_mm_set(काष्ठा tce_container *container)
अणु
	अगर (container->mm) अणु
		अगर (container->mm == current->mm)
			वापस 0;
		वापस -EPERM;
	पूर्ण
	BUG_ON(!current->mm);
	container->mm = current->mm;
	mmgrab(container->mm);

	वापस 0;
पूर्ण

अटल दीर्घ tce_iommu_prereg_मुक्त(काष्ठा tce_container *container,
		काष्ठा tce_iommu_prereg *tcemem)
अणु
	दीर्घ ret;

	ret = mm_iommu_put(container->mm, tcemem->mem);
	अगर (ret)
		वापस ret;

	list_del(&tcemem->next);
	kमुक्त(tcemem);

	वापस 0;
पूर्ण

अटल दीर्घ tce_iommu_unरेजिस्टर_pages(काष्ठा tce_container *container,
		__u64 vaddr, __u64 size)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem;
	काष्ठा tce_iommu_prereg *tcemem;
	bool found = false;
	दीर्घ ret;

	अगर ((vaddr & ~PAGE_MASK) || (size & ~PAGE_MASK))
		वापस -EINVAL;

	mem = mm_iommu_get(container->mm, vaddr, size >> PAGE_SHIFT);
	अगर (!mem)
		वापस -ENOENT;

	list_क्रम_each_entry(tcemem, &container->prereg_list, next) अणु
		अगर (tcemem->mem == mem) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		ret = -ENOENT;
	अन्यथा
		ret = tce_iommu_prereg_मुक्त(container, tcemem);

	mm_iommu_put(container->mm, mem);

	वापस ret;
पूर्ण

अटल दीर्घ tce_iommu_रेजिस्टर_pages(काष्ठा tce_container *container,
		__u64 vaddr, __u64 size)
अणु
	दीर्घ ret = 0;
	काष्ठा mm_iommu_table_group_mem_t *mem = शून्य;
	काष्ठा tce_iommu_prereg *tcemem;
	अचिन्हित दीर्घ entries = size >> PAGE_SHIFT;

	अगर ((vaddr & ~PAGE_MASK) || (size & ~PAGE_MASK) ||
			((vaddr + size) < vaddr))
		वापस -EINVAL;

	mem = mm_iommu_get(container->mm, vaddr, entries);
	अगर (mem) अणु
		list_क्रम_each_entry(tcemem, &container->prereg_list, next) अणु
			अगर (tcemem->mem == mem) अणु
				ret = -EBUSY;
				जाओ put_निकास;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = mm_iommu_new(container->mm, vaddr, entries, &mem);
		अगर (ret)
			वापस ret;
	पूर्ण

	tcemem = kzalloc(माप(*tcemem), GFP_KERNEL);
	अगर (!tcemem) अणु
		ret = -ENOMEM;
		जाओ put_निकास;
	पूर्ण

	tcemem->mem = mem;
	list_add(&tcemem->next, &container->prereg_list);

	container->enabled = true;

	वापस 0;

put_निकास:
	mm_iommu_put(container->mm, mem);
	वापस ret;
पूर्ण

अटल bool tce_page_is_contained(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ hpa,
		अचिन्हित पूर्णांक it_page_shअगरt)
अणु
	काष्ठा page *page;
	अचिन्हित दीर्घ size = 0;

	अगर (mm_iommu_is_devmem(mm, hpa, it_page_shअगरt, &size))
		वापस size == (1UL << it_page_shअगरt);

	page = pfn_to_page(hpa >> PAGE_SHIFT);
	/*
	 * Check that the TCE table granularity is not bigger than the size of
	 * a page we just found. Otherwise the hardware can get access to
	 * a bigger memory chunk that it should.
	 */
	वापस page_shअगरt(compound_head(page)) >= it_page_shअगरt;
पूर्ण

अटल अंतरभूत bool tce_groups_attached(काष्ठा tce_container *container)
अणु
	वापस !list_empty(&container->group_list);
पूर्ण

अटल दीर्घ tce_iommu_find_table(काष्ठा tce_container *container,
		phys_addr_t ioba, काष्ठा iommu_table **ptbl)
अणु
	दीर्घ i;

	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) अणु
		काष्ठा iommu_table *tbl = container->tables[i];

		अगर (tbl) अणु
			अचिन्हित दीर्घ entry = ioba >> tbl->it_page_shअगरt;
			अचिन्हित दीर्घ start = tbl->it_offset;
			अचिन्हित दीर्घ end = start + tbl->it_size;

			अगर ((start <= entry) && (entry < end)) अणु
				*ptbl = tbl;
				वापस i;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक tce_iommu_find_मुक्त_table(काष्ठा tce_container *container)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) अणु
		अगर (!container->tables[i])
			वापस i;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक tce_iommu_enable(काष्ठा tce_container *container)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ locked;
	काष्ठा iommu_table_group *table_group;
	काष्ठा tce_iommu_group *tcegrp;

	अगर (container->enabled)
		वापस -EBUSY;

	/*
	 * When userspace pages are mapped पूर्णांकo the IOMMU, they are effectively
	 * locked memory, so, theoretically, we need to update the accounting
	 * of locked pages on each map and unmap.  For घातerpc, the map unmap
	 * paths can be very hot, though, and the accounting would समाप्त
	 * perक्रमmance, especially since it would be dअगरficult to impossible
	 * to handle the accounting in real mode only.
	 *
	 * To address that, rather than precisely accounting every page, we
	 * instead account क्रम a worst हाल on locked memory when the iommu is
	 * enabled and disabled.  The worst हाल upper bound on locked memory
	 * is the size of the whole iommu winकरोw, which is usually relatively
	 * small (compared to total memory sizes) on POWER hardware.
	 *
	 * Also we करोn't have a nice way to fail on H_PUT_TCE due to ulimits,
	 * that would effectively समाप्त the guest at अक्रमom poपूर्णांकs, much better
	 * enक्रमcing the limit based on the max that the guest can map.
	 *
	 * Unक्रमtunately at the moment it counts whole tables, no matter how
	 * much memory the guest has. I.e. क्रम 4GB guest and 4 IOMMU groups
	 * each with 2GB DMA winकरोw, 8GB will be counted here. The reason क्रम
	 * this is that we cannot tell here the amount of RAM used by the guest
	 * as this inक्रमmation is only available from KVM and VFIO is
	 * KVM agnostic.
	 *
	 * So we करो not allow enabling a container without a group attached
	 * as there is no way to know how much we should increment
	 * the locked_vm counter.
	 */
	अगर (!tce_groups_attached(container))
		वापस -ENODEV;

	tcegrp = list_first_entry(&container->group_list,
			काष्ठा tce_iommu_group, next);
	table_group = iommu_group_get_iommudata(tcegrp->grp);
	अगर (!table_group)
		वापस -ENODEV;

	अगर (!table_group->tce32_size)
		वापस -EPERM;

	ret = tce_iommu_mm_set(container);
	अगर (ret)
		वापस ret;

	locked = table_group->tce32_size >> PAGE_SHIFT;
	ret = account_locked_vm(container->mm, locked, true);
	अगर (ret)
		वापस ret;

	container->locked_pages = locked;

	container->enabled = true;

	वापस ret;
पूर्ण

अटल व्योम tce_iommu_disable(काष्ठा tce_container *container)
अणु
	अगर (!container->enabled)
		वापस;

	container->enabled = false;

	BUG_ON(!container->mm);
	account_locked_vm(container->mm, container->locked_pages, false);
पूर्ण

अटल व्योम *tce_iommu_खोलो(अचिन्हित दीर्घ arg)
अणु
	काष्ठा tce_container *container;

	अगर ((arg != VFIO_SPAPR_TCE_IOMMU) && (arg != VFIO_SPAPR_TCE_v2_IOMMU)) अणु
		pr_err("tce_vfio: Wrong IOMMU type\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	container = kzalloc(माप(*container), GFP_KERNEL);
	अगर (!container)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&container->lock);
	INIT_LIST_HEAD_RCU(&container->group_list);
	INIT_LIST_HEAD_RCU(&container->prereg_list);

	container->v2 = arg == VFIO_SPAPR_TCE_v2_IOMMU;

	वापस container;
पूर्ण

अटल पूर्णांक tce_iommu_clear(काष्ठा tce_container *container,
		काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ pages);
अटल व्योम tce_iommu_मुक्त_table(काष्ठा tce_container *container,
		काष्ठा iommu_table *tbl);

अटल व्योम tce_iommu_release(व्योम *iommu_data)
अणु
	काष्ठा tce_container *container = iommu_data;
	काष्ठा tce_iommu_group *tcegrp;
	काष्ठा tce_iommu_prereg *tcemem, *पंचांगपंचांगp;
	दीर्घ i;

	जबतक (tce_groups_attached(container)) अणु
		tcegrp = list_first_entry(&container->group_list,
				काष्ठा tce_iommu_group, next);
		tce_iommu_detach_group(iommu_data, tcegrp->grp);
	पूर्ण

	/*
	 * If VFIO created a table, it was not disposed
	 * by tce_iommu_detach_group() so करो it now.
	 */
	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) अणु
		काष्ठा iommu_table *tbl = container->tables[i];

		अगर (!tbl)
			जारी;

		tce_iommu_clear(container, tbl, tbl->it_offset, tbl->it_size);
		tce_iommu_मुक्त_table(container, tbl);
	पूर्ण

	list_क्रम_each_entry_safe(tcemem, पंचांगपंचांगp, &container->prereg_list, next)
		WARN_ON(tce_iommu_prereg_मुक्त(container, tcemem));

	tce_iommu_disable(container);
	अगर (container->mm)
		mmdrop(container->mm);
	mutex_destroy(&container->lock);

	kमुक्त(container);
पूर्ण

अटल व्योम tce_iommu_unuse_page(काष्ठा tce_container *container,
		अचिन्हित दीर्घ hpa)
अणु
	काष्ठा page *page;

	page = pfn_to_page(hpa >> PAGE_SHIFT);
	unpin_user_page(page);
पूर्ण

अटल पूर्णांक tce_iommu_prereg_ua_to_hpa(काष्ठा tce_container *container,
		अचिन्हित दीर्घ tce, अचिन्हित दीर्घ shअगरt,
		अचिन्हित दीर्घ *phpa, काष्ठा mm_iommu_table_group_mem_t **pmem)
अणु
	दीर्घ ret = 0;
	काष्ठा mm_iommu_table_group_mem_t *mem;

	mem = mm_iommu_lookup(container->mm, tce, 1ULL << shअगरt);
	अगर (!mem)
		वापस -EINVAL;

	ret = mm_iommu_ua_to_hpa(mem, tce, shअगरt, phpa);
	अगर (ret)
		वापस -EINVAL;

	*pmem = mem;

	वापस 0;
पूर्ण

अटल व्योम tce_iommu_unuse_page_v2(काष्ठा tce_container *container,
		काष्ठा iommu_table *tbl, अचिन्हित दीर्घ entry)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem = शून्य;
	पूर्णांक ret;
	अचिन्हित दीर्घ hpa = 0;
	__be64 *pua = IOMMU_TABLE_USERSPACE_ENTRY_RO(tbl, entry);

	अगर (!pua)
		वापस;

	ret = tce_iommu_prereg_ua_to_hpa(container, be64_to_cpu(*pua),
			tbl->it_page_shअगरt, &hpa, &mem);
	अगर (ret)
		pr_debug("%s: tce %llx at #%lx was not cached, ret=%d\n",
				__func__, be64_to_cpu(*pua), entry, ret);
	अगर (mem)
		mm_iommu_mapped_dec(mem);

	*pua = cpu_to_be64(0);
पूर्ण

अटल पूर्णांक tce_iommu_clear(काष्ठा tce_container *container,
		काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ pages)
अणु
	अचिन्हित दीर्घ oldhpa;
	दीर्घ ret;
	क्रमागत dma_data_direction direction;
	अचिन्हित दीर्घ lastentry = entry + pages, firstentry = entry;

	क्रम ( ; entry < lastentry; ++entry) अणु
		अगर (tbl->it_indirect_levels && tbl->it_userspace) अणु
			/*
			 * For multilevel tables, we can take a लघुcut here
			 * and skip some TCEs as we know that the userspace
			 * addresses cache is a mirror of the real TCE table
			 * and अगर it is missing some indirect levels, then
			 * the hardware table करोes not have them allocated
			 * either and thereक्रमe करोes not require updating.
			 */
			__be64 *pua = IOMMU_TABLE_USERSPACE_ENTRY_RO(tbl,
					entry);
			अगर (!pua) अणु
				/* align to level_size which is घातer of two */
				entry |= tbl->it_level_size - 1;
				जारी;
			पूर्ण
		पूर्ण

		cond_resched();

		direction = DMA_NONE;
		oldhpa = 0;
		ret = iommu_tce_xchg_no_समाप्त(container->mm, tbl, entry, &oldhpa,
				&direction);
		अगर (ret)
			जारी;

		अगर (direction == DMA_NONE)
			जारी;

		अगर (container->v2) अणु
			tce_iommu_unuse_page_v2(container, tbl, entry);
			जारी;
		पूर्ण

		tce_iommu_unuse_page(container, oldhpa);
	पूर्ण

	iommu_tce_समाप्त(tbl, firstentry, pages);

	वापस 0;
पूर्ण

अटल पूर्णांक tce_iommu_use_page(अचिन्हित दीर्घ tce, अचिन्हित दीर्घ *hpa)
अणु
	काष्ठा page *page = शून्य;
	क्रमागत dma_data_direction direction = iommu_tce_direction(tce);

	अगर (pin_user_pages_fast(tce & PAGE_MASK, 1,
			direction != DMA_TO_DEVICE ? FOLL_WRITE : 0,
			&page) != 1)
		वापस -EFAULT;

	*hpa = __pa((अचिन्हित दीर्घ) page_address(page));

	वापस 0;
पूर्ण

अटल दीर्घ tce_iommu_build(काष्ठा tce_container *container,
		काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ tce, अचिन्हित दीर्घ pages,
		क्रमागत dma_data_direction direction)
अणु
	दीर्घ i, ret = 0;
	अचिन्हित दीर्घ hpa;
	क्रमागत dma_data_direction dirपंचांगp;

	क्रम (i = 0; i < pages; ++i) अणु
		अचिन्हित दीर्घ offset = tce & IOMMU_PAGE_MASK(tbl) & ~PAGE_MASK;

		ret = tce_iommu_use_page(tce, &hpa);
		अगर (ret)
			अवरोध;

		अगर (!tce_page_is_contained(container->mm, hpa,
				tbl->it_page_shअगरt)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण

		hpa |= offset;
		dirपंचांगp = direction;
		ret = iommu_tce_xchg_no_समाप्त(container->mm, tbl, entry + i,
				&hpa, &dirपंचांगp);
		अगर (ret) अणु
			tce_iommu_unuse_page(container, hpa);
			pr_err("iommu_tce: %s failed ioba=%lx, tce=%lx, ret=%ld\n",
					__func__, entry << tbl->it_page_shअगरt,
					tce, ret);
			अवरोध;
		पूर्ण

		अगर (dirपंचांगp != DMA_NONE)
			tce_iommu_unuse_page(container, hpa);

		tce += IOMMU_PAGE_SIZE(tbl);
	पूर्ण

	अगर (ret)
		tce_iommu_clear(container, tbl, entry, i);
	अन्यथा
		iommu_tce_समाप्त(tbl, entry, pages);

	वापस ret;
पूर्ण

अटल दीर्घ tce_iommu_build_v2(काष्ठा tce_container *container,
		काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ tce, अचिन्हित दीर्घ pages,
		क्रमागत dma_data_direction direction)
अणु
	दीर्घ i, ret = 0;
	अचिन्हित दीर्घ hpa;
	क्रमागत dma_data_direction dirपंचांगp;

	क्रम (i = 0; i < pages; ++i) अणु
		काष्ठा mm_iommu_table_group_mem_t *mem = शून्य;
		__be64 *pua = IOMMU_TABLE_USERSPACE_ENTRY(tbl, entry + i);

		ret = tce_iommu_prereg_ua_to_hpa(container,
				tce, tbl->it_page_shअगरt, &hpa, &mem);
		अगर (ret)
			अवरोध;

		अगर (!tce_page_is_contained(container->mm, hpa,
				tbl->it_page_shअगरt)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण

		/* Preserve offset within IOMMU page */
		hpa |= tce & IOMMU_PAGE_MASK(tbl) & ~PAGE_MASK;
		dirपंचांगp = direction;

		/* The रेजिस्टरed region is being unरेजिस्टरed */
		अगर (mm_iommu_mapped_inc(mem))
			अवरोध;

		ret = iommu_tce_xchg_no_समाप्त(container->mm, tbl, entry + i,
				&hpa, &dirपंचांगp);
		अगर (ret) अणु
			/* dirपंचांगp cannot be DMA_NONE here */
			tce_iommu_unuse_page_v2(container, tbl, entry + i);
			pr_err("iommu_tce: %s failed ioba=%lx, tce=%lx, ret=%ld\n",
					__func__, entry << tbl->it_page_shअगरt,
					tce, ret);
			अवरोध;
		पूर्ण

		अगर (dirपंचांगp != DMA_NONE)
			tce_iommu_unuse_page_v2(container, tbl, entry + i);

		*pua = cpu_to_be64(tce);

		tce += IOMMU_PAGE_SIZE(tbl);
	पूर्ण

	अगर (ret)
		tce_iommu_clear(container, tbl, entry, i);
	अन्यथा
		iommu_tce_समाप्त(tbl, entry, pages);

	वापस ret;
पूर्ण

अटल दीर्घ tce_iommu_create_table(काष्ठा tce_container *container,
			काष्ठा iommu_table_group *table_group,
			पूर्णांक num,
			__u32 page_shअगरt,
			__u64 winकरोw_size,
			__u32 levels,
			काष्ठा iommu_table **ptbl)
अणु
	दीर्घ ret, table_size;

	table_size = table_group->ops->get_table_size(page_shअगरt, winकरोw_size,
			levels);
	अगर (!table_size)
		वापस -EINVAL;

	ret = account_locked_vm(container->mm, table_size >> PAGE_SHIFT, true);
	अगर (ret)
		वापस ret;

	ret = table_group->ops->create_table(table_group, num,
			page_shअगरt, winकरोw_size, levels, ptbl);

	WARN_ON(!ret && !(*ptbl)->it_ops->मुक्त);
	WARN_ON(!ret && ((*ptbl)->it_allocated_size > table_size));

	वापस ret;
पूर्ण

अटल व्योम tce_iommu_मुक्त_table(काष्ठा tce_container *container,
		काष्ठा iommu_table *tbl)
अणु
	अचिन्हित दीर्घ pages = tbl->it_allocated_size >> PAGE_SHIFT;

	iommu_tce_table_put(tbl);
	account_locked_vm(container->mm, pages, false);
पूर्ण

अटल दीर्घ tce_iommu_create_winकरोw(काष्ठा tce_container *container,
		__u32 page_shअगरt, __u64 winकरोw_size, __u32 levels,
		__u64 *start_addr)
अणु
	काष्ठा tce_iommu_group *tcegrp;
	काष्ठा iommu_table_group *table_group;
	काष्ठा iommu_table *tbl = शून्य;
	दीर्घ ret, num;

	num = tce_iommu_find_मुक्त_table(container);
	अगर (num < 0)
		वापस num;

	/* Get the first group क्रम ops::create_table */
	tcegrp = list_first_entry(&container->group_list,
			काष्ठा tce_iommu_group, next);
	table_group = iommu_group_get_iommudata(tcegrp->grp);
	अगर (!table_group)
		वापस -EFAULT;

	अगर (!(table_group->pgsizes & (1ULL << page_shअगरt)))
		वापस -EINVAL;

	अगर (!table_group->ops->set_winकरोw || !table_group->ops->unset_winकरोw ||
			!table_group->ops->get_table_size ||
			!table_group->ops->create_table)
		वापस -EPERM;

	/* Create TCE table */
	ret = tce_iommu_create_table(container, table_group, num,
			page_shअगरt, winकरोw_size, levels, &tbl);
	अगर (ret)
		वापस ret;

	BUG_ON(!tbl->it_ops->मुक्त);

	/*
	 * Program the table to every group.
	 * Groups have been tested क्रम compatibility at the attach समय.
	 */
	list_क्रम_each_entry(tcegrp, &container->group_list, next) अणु
		table_group = iommu_group_get_iommudata(tcegrp->grp);

		ret = table_group->ops->set_winकरोw(table_group, num, tbl);
		अगर (ret)
			जाओ unset_निकास;
	पूर्ण

	container->tables[num] = tbl;

	/* Return start address asचिन्हित by platक्रमm in create_table() */
	*start_addr = tbl->it_offset << tbl->it_page_shअगरt;

	वापस 0;

unset_निकास:
	list_क्रम_each_entry(tcegrp, &container->group_list, next) अणु
		table_group = iommu_group_get_iommudata(tcegrp->grp);
		table_group->ops->unset_winकरोw(table_group, num);
	पूर्ण
	tce_iommu_मुक्त_table(container, tbl);

	वापस ret;
पूर्ण

अटल दीर्घ tce_iommu_हटाओ_winकरोw(काष्ठा tce_container *container,
		__u64 start_addr)
अणु
	काष्ठा iommu_table_group *table_group = शून्य;
	काष्ठा iommu_table *tbl;
	काष्ठा tce_iommu_group *tcegrp;
	पूर्णांक num;

	num = tce_iommu_find_table(container, start_addr, &tbl);
	अगर (num < 0)
		वापस -EINVAL;

	BUG_ON(!tbl->it_size);

	/* Detach groups from IOMMUs */
	list_क्रम_each_entry(tcegrp, &container->group_list, next) अणु
		table_group = iommu_group_get_iommudata(tcegrp->grp);

		/*
		 * SPAPR TCE IOMMU exposes the शेष DMA winकरोw to
		 * the guest via dma32_winकरोw_start/size of
		 * VFIO_IOMMU_SPAPR_TCE_GET_INFO. Some platक्रमms allow
		 * the userspace to हटाओ this winकरोw, some करो not so
		 * here we check क्रम the platक्रमm capability.
		 */
		अगर (!table_group->ops || !table_group->ops->unset_winकरोw)
			वापस -EPERM;

		table_group->ops->unset_winकरोw(table_group, num);
	पूर्ण

	/* Free table */
	tce_iommu_clear(container, tbl, tbl->it_offset, tbl->it_size);
	tce_iommu_मुक्त_table(container, tbl);
	container->tables[num] = शून्य;

	वापस 0;
पूर्ण

अटल दीर्घ tce_iommu_create_शेष_winकरोw(काष्ठा tce_container *container)
अणु
	दीर्घ ret;
	__u64 start_addr = 0;
	काष्ठा tce_iommu_group *tcegrp;
	काष्ठा iommu_table_group *table_group;

	अगर (!container->def_winकरोw_pending)
		वापस 0;

	अगर (!tce_groups_attached(container))
		वापस -ENODEV;

	tcegrp = list_first_entry(&container->group_list,
			काष्ठा tce_iommu_group, next);
	table_group = iommu_group_get_iommudata(tcegrp->grp);
	अगर (!table_group)
		वापस -ENODEV;

	ret = tce_iommu_create_winकरोw(container, IOMMU_PAGE_SHIFT_4K,
			table_group->tce32_size, 1, &start_addr);
	WARN_ON_ONCE(!ret && start_addr);

	अगर (!ret)
		container->def_winकरोw_pending = false;

	वापस ret;
पूर्ण

अटल दीर्घ tce_iommu_ioctl(व्योम *iommu_data,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा tce_container *container = iommu_data;
	अचिन्हित दीर्घ minsz, ddwsz;
	दीर्घ ret;

	चयन (cmd) अणु
	हाल VFIO_CHECK_EXTENSION:
		चयन (arg) अणु
		हाल VFIO_SPAPR_TCE_IOMMU:
		हाल VFIO_SPAPR_TCE_v2_IOMMU:
			ret = 1;
			अवरोध;
		शेष:
			ret = vfio_spapr_iommu_eeh_ioctl(शून्य, cmd, arg);
			अवरोध;
		पूर्ण

		वापस (ret < 0) ? 0 : ret;
	पूर्ण

	/*
	 * Sanity check to prevent one userspace from manipulating
	 * another userspace mm.
	 */
	BUG_ON(!container);
	अगर (container->mm && container->mm != current->mm)
		वापस -EPERM;

	चयन (cmd) अणु
	हाल VFIO_IOMMU_SPAPR_TCE_GET_INFO: अणु
		काष्ठा vfio_iommu_spapr_tce_info info;
		काष्ठा tce_iommu_group *tcegrp;
		काष्ठा iommu_table_group *table_group;

		अगर (!tce_groups_attached(container))
			वापस -ENXIO;

		tcegrp = list_first_entry(&container->group_list,
				काष्ठा tce_iommu_group, next);
		table_group = iommu_group_get_iommudata(tcegrp->grp);

		अगर (!table_group)
			वापस -ENXIO;

		minsz = दुरत्वend(काष्ठा vfio_iommu_spapr_tce_info,
				dma32_winकरोw_size);

		अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (info.argsz < minsz)
			वापस -EINVAL;

		info.dma32_winकरोw_start = table_group->tce32_start;
		info.dma32_winकरोw_size = table_group->tce32_size;
		info.flags = 0;
		स_रखो(&info.ddw, 0, माप(info.ddw));

		अगर (table_group->max_dynamic_winकरोws_supported &&
				container->v2) अणु
			info.flags |= VFIO_IOMMU_SPAPR_INFO_DDW;
			info.ddw.pgsizes = table_group->pgsizes;
			info.ddw.max_dynamic_winकरोws_supported =
				table_group->max_dynamic_winकरोws_supported;
			info.ddw.levels = table_group->max_levels;
		पूर्ण

		ddwsz = दुरत्वend(काष्ठा vfio_iommu_spapr_tce_info, ddw);

		अगर (info.argsz >= ddwsz)
			minsz = ddwsz;

		अगर (copy_to_user((व्योम __user *)arg, &info, minsz))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल VFIO_IOMMU_MAP_DMA: अणु
		काष्ठा vfio_iommu_type1_dma_map param;
		काष्ठा iommu_table *tbl = शून्य;
		दीर्घ num;
		क्रमागत dma_data_direction direction;

		अगर (!container->enabled)
			वापस -EPERM;

		minsz = दुरत्वend(काष्ठा vfio_iommu_type1_dma_map, size);

		अगर (copy_from_user(&param, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (param.argsz < minsz)
			वापस -EINVAL;

		अगर (param.flags & ~(VFIO_DMA_MAP_FLAG_READ |
				VFIO_DMA_MAP_FLAG_WRITE))
			वापस -EINVAL;

		ret = tce_iommu_create_शेष_winकरोw(container);
		अगर (ret)
			वापस ret;

		num = tce_iommu_find_table(container, param.iova, &tbl);
		अगर (num < 0)
			वापस -ENXIO;

		अगर ((param.size & ~IOMMU_PAGE_MASK(tbl)) ||
				(param.vaddr & ~IOMMU_PAGE_MASK(tbl)))
			वापस -EINVAL;

		/* iova is checked by the IOMMU API */
		अगर (param.flags & VFIO_DMA_MAP_FLAG_READ) अणु
			अगर (param.flags & VFIO_DMA_MAP_FLAG_WRITE)
				direction = DMA_BIसूचीECTIONAL;
			अन्यथा
				direction = DMA_TO_DEVICE;
		पूर्ण अन्यथा अणु
			अगर (param.flags & VFIO_DMA_MAP_FLAG_WRITE)
				direction = DMA_FROM_DEVICE;
			अन्यथा
				वापस -EINVAL;
		पूर्ण

		ret = iommu_tce_put_param_check(tbl, param.iova, param.vaddr);
		अगर (ret)
			वापस ret;

		अगर (container->v2)
			ret = tce_iommu_build_v2(container, tbl,
					param.iova >> tbl->it_page_shअगरt,
					param.vaddr,
					param.size >> tbl->it_page_shअगरt,
					direction);
		अन्यथा
			ret = tce_iommu_build(container, tbl,
					param.iova >> tbl->it_page_shअगरt,
					param.vaddr,
					param.size >> tbl->it_page_shअगरt,
					direction);

		iommu_flush_tce(tbl);

		वापस ret;
	पूर्ण
	हाल VFIO_IOMMU_UNMAP_DMA: अणु
		काष्ठा vfio_iommu_type1_dma_unmap param;
		काष्ठा iommu_table *tbl = शून्य;
		दीर्घ num;

		अगर (!container->enabled)
			वापस -EPERM;

		minsz = दुरत्वend(काष्ठा vfio_iommu_type1_dma_unmap,
				size);

		अगर (copy_from_user(&param, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (param.argsz < minsz)
			वापस -EINVAL;

		/* No flag is supported now */
		अगर (param.flags)
			वापस -EINVAL;

		ret = tce_iommu_create_शेष_winकरोw(container);
		अगर (ret)
			वापस ret;

		num = tce_iommu_find_table(container, param.iova, &tbl);
		अगर (num < 0)
			वापस -ENXIO;

		अगर (param.size & ~IOMMU_PAGE_MASK(tbl))
			वापस -EINVAL;

		ret = iommu_tce_clear_param_check(tbl, param.iova, 0,
				param.size >> tbl->it_page_shअगरt);
		अगर (ret)
			वापस ret;

		ret = tce_iommu_clear(container, tbl,
				param.iova >> tbl->it_page_shअगरt,
				param.size >> tbl->it_page_shअगरt);
		iommu_flush_tce(tbl);

		वापस ret;
	पूर्ण
	हाल VFIO_IOMMU_SPAPR_REGISTER_MEMORY: अणु
		काष्ठा vfio_iommu_spapr_रेजिस्टर_memory param;

		अगर (!container->v2)
			अवरोध;

		minsz = दुरत्वend(काष्ठा vfio_iommu_spapr_रेजिस्टर_memory,
				size);

		ret = tce_iommu_mm_set(container);
		अगर (ret)
			वापस ret;

		अगर (copy_from_user(&param, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (param.argsz < minsz)
			वापस -EINVAL;

		/* No flag is supported now */
		अगर (param.flags)
			वापस -EINVAL;

		mutex_lock(&container->lock);
		ret = tce_iommu_रेजिस्टर_pages(container, param.vaddr,
				param.size);
		mutex_unlock(&container->lock);

		वापस ret;
	पूर्ण
	हाल VFIO_IOMMU_SPAPR_UNREGISTER_MEMORY: अणु
		काष्ठा vfio_iommu_spapr_रेजिस्टर_memory param;

		अगर (!container->v2)
			अवरोध;

		अगर (!container->mm)
			वापस -EPERM;

		minsz = दुरत्वend(काष्ठा vfio_iommu_spapr_रेजिस्टर_memory,
				size);

		अगर (copy_from_user(&param, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (param.argsz < minsz)
			वापस -EINVAL;

		/* No flag is supported now */
		अगर (param.flags)
			वापस -EINVAL;

		mutex_lock(&container->lock);
		ret = tce_iommu_unरेजिस्टर_pages(container, param.vaddr,
				param.size);
		mutex_unlock(&container->lock);

		वापस ret;
	पूर्ण
	हाल VFIO_IOMMU_ENABLE:
		अगर (container->v2)
			अवरोध;

		mutex_lock(&container->lock);
		ret = tce_iommu_enable(container);
		mutex_unlock(&container->lock);
		वापस ret;


	हाल VFIO_IOMMU_DISABLE:
		अगर (container->v2)
			अवरोध;

		mutex_lock(&container->lock);
		tce_iommu_disable(container);
		mutex_unlock(&container->lock);
		वापस 0;

	हाल VFIO_EEH_PE_OP: अणु
		काष्ठा tce_iommu_group *tcegrp;

		ret = 0;
		list_क्रम_each_entry(tcegrp, &container->group_list, next) अणु
			ret = vfio_spapr_iommu_eeh_ioctl(tcegrp->grp,
					cmd, arg);
			अगर (ret)
				वापस ret;
		पूर्ण
		वापस ret;
	पूर्ण

	हाल VFIO_IOMMU_SPAPR_TCE_CREATE: अणु
		काष्ठा vfio_iommu_spapr_tce_create create;

		अगर (!container->v2)
			अवरोध;

		ret = tce_iommu_mm_set(container);
		अगर (ret)
			वापस ret;

		अगर (!tce_groups_attached(container))
			वापस -ENXIO;

		minsz = दुरत्वend(काष्ठा vfio_iommu_spapr_tce_create,
				start_addr);

		अगर (copy_from_user(&create, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (create.argsz < minsz)
			वापस -EINVAL;

		अगर (create.flags)
			वापस -EINVAL;

		mutex_lock(&container->lock);

		ret = tce_iommu_create_शेष_winकरोw(container);
		अगर (!ret)
			ret = tce_iommu_create_winकरोw(container,
					create.page_shअगरt,
					create.winकरोw_size, create.levels,
					&create.start_addr);

		mutex_unlock(&container->lock);

		अगर (!ret && copy_to_user((व्योम __user *)arg, &create, minsz))
			ret = -EFAULT;

		वापस ret;
	पूर्ण
	हाल VFIO_IOMMU_SPAPR_TCE_REMOVE: अणु
		काष्ठा vfio_iommu_spapr_tce_हटाओ हटाओ;

		अगर (!container->v2)
			अवरोध;

		ret = tce_iommu_mm_set(container);
		अगर (ret)
			वापस ret;

		अगर (!tce_groups_attached(container))
			वापस -ENXIO;

		minsz = दुरत्वend(काष्ठा vfio_iommu_spapr_tce_हटाओ,
				start_addr);

		अगर (copy_from_user(&हटाओ, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (हटाओ.argsz < minsz)
			वापस -EINVAL;

		अगर (हटाओ.flags)
			वापस -EINVAL;

		अगर (container->def_winकरोw_pending && !हटाओ.start_addr) अणु
			container->def_winकरोw_pending = false;
			वापस 0;
		पूर्ण

		mutex_lock(&container->lock);

		ret = tce_iommu_हटाओ_winकरोw(container, हटाओ.start_addr);

		mutex_unlock(&container->lock);

		वापस ret;
	पूर्ण
	पूर्ण

	वापस -ENOTTY;
पूर्ण

अटल व्योम tce_iommu_release_ownership(काष्ठा tce_container *container,
		काष्ठा iommu_table_group *table_group)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) अणु
		काष्ठा iommu_table *tbl = container->tables[i];

		अगर (!tbl)
			जारी;

		tce_iommu_clear(container, tbl, tbl->it_offset, tbl->it_size);
		अगर (tbl->it_map)
			iommu_release_ownership(tbl);

		container->tables[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tce_iommu_take_ownership(काष्ठा tce_container *container,
		काष्ठा iommu_table_group *table_group)
अणु
	पूर्णांक i, j, rc = 0;

	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) अणु
		काष्ठा iommu_table *tbl = table_group->tables[i];

		अगर (!tbl || !tbl->it_map)
			जारी;

		rc = iommu_take_ownership(tbl);
		अगर (rc) अणु
			क्रम (j = 0; j < i; ++j)
				iommu_release_ownership(
						table_group->tables[j]);

			वापस rc;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i)
		container->tables[i] = table_group->tables[i];

	वापस 0;
पूर्ण

अटल व्योम tce_iommu_release_ownership_ddw(काष्ठा tce_container *container,
		काष्ठा iommu_table_group *table_group)
अणु
	दीर्घ i;

	अगर (!table_group->ops->unset_winकरोw) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i)
		अगर (container->tables[i])
			table_group->ops->unset_winकरोw(table_group, i);

	table_group->ops->release_ownership(table_group);
पूर्ण

अटल दीर्घ tce_iommu_take_ownership_ddw(काष्ठा tce_container *container,
		काष्ठा iommu_table_group *table_group)
अणु
	दीर्घ i, ret = 0;

	अगर (!table_group->ops->create_table || !table_group->ops->set_winकरोw ||
			!table_group->ops->release_ownership) अणु
		WARN_ON_ONCE(1);
		वापस -EFAULT;
	पूर्ण

	table_group->ops->take_ownership(table_group);

	/* Set all winकरोws to the new group */
	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) अणु
		काष्ठा iommu_table *tbl = container->tables[i];

		अगर (!tbl)
			जारी;

		ret = table_group->ops->set_winकरोw(table_group, i, tbl);
		अगर (ret)
			जाओ release_निकास;
	पूर्ण

	वापस 0;

release_निकास:
	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i)
		table_group->ops->unset_winकरोw(table_group, i);

	table_group->ops->release_ownership(table_group);

	वापस ret;
पूर्ण

अटल पूर्णांक tce_iommu_attach_group(व्योम *iommu_data,
		काष्ठा iommu_group *iommu_group)
अणु
	पूर्णांक ret = 0;
	काष्ठा tce_container *container = iommu_data;
	काष्ठा iommu_table_group *table_group;
	काष्ठा tce_iommu_group *tcegrp = शून्य;

	mutex_lock(&container->lock);

	/* pr_debug("tce_vfio: Attaching group #%u to iommu %p\n",
			iommu_group_id(iommu_group), iommu_group); */
	table_group = iommu_group_get_iommudata(iommu_group);
	अगर (!table_group) अणु
		ret = -ENODEV;
		जाओ unlock_निकास;
	पूर्ण

	अगर (tce_groups_attached(container) && (!table_group->ops ||
			!table_group->ops->take_ownership ||
			!table_group->ops->release_ownership)) अणु
		ret = -EBUSY;
		जाओ unlock_निकास;
	पूर्ण

	/* Check अगर new group has the same iommu_ops (i.e. compatible) */
	list_क्रम_each_entry(tcegrp, &container->group_list, next) अणु
		काष्ठा iommu_table_group *table_group_पंचांगp;

		अगर (tcegrp->grp == iommu_group) अणु
			pr_warn("tce_vfio: Group %d is already attached\n",
					iommu_group_id(iommu_group));
			ret = -EBUSY;
			जाओ unlock_निकास;
		पूर्ण
		table_group_पंचांगp = iommu_group_get_iommudata(tcegrp->grp);
		अगर (table_group_पंचांगp->ops->create_table !=
				table_group->ops->create_table) अणु
			pr_warn("tce_vfio: Group %d is incompatible with group %d\n",
					iommu_group_id(iommu_group),
					iommu_group_id(tcegrp->grp));
			ret = -EPERM;
			जाओ unlock_निकास;
		पूर्ण
	पूर्ण

	tcegrp = kzalloc(माप(*tcegrp), GFP_KERNEL);
	अगर (!tcegrp) अणु
		ret = -ENOMEM;
		जाओ unlock_निकास;
	पूर्ण

	अगर (!table_group->ops || !table_group->ops->take_ownership ||
			!table_group->ops->release_ownership) अणु
		अगर (container->v2) अणु
			ret = -EPERM;
			जाओ मुक्त_निकास;
		पूर्ण
		ret = tce_iommu_take_ownership(container, table_group);
	पूर्ण अन्यथा अणु
		अगर (!container->v2) अणु
			ret = -EPERM;
			जाओ मुक्त_निकास;
		पूर्ण
		ret = tce_iommu_take_ownership_ddw(container, table_group);
		अगर (!tce_groups_attached(container) && !container->tables[0])
			container->def_winकरोw_pending = true;
	पूर्ण

	अगर (!ret) अणु
		tcegrp->grp = iommu_group;
		list_add(&tcegrp->next, &container->group_list);
	पूर्ण

मुक्त_निकास:
	अगर (ret && tcegrp)
		kमुक्त(tcegrp);

unlock_निकास:
	mutex_unlock(&container->lock);

	वापस ret;
पूर्ण

अटल व्योम tce_iommu_detach_group(व्योम *iommu_data,
		काष्ठा iommu_group *iommu_group)
अणु
	काष्ठा tce_container *container = iommu_data;
	काष्ठा iommu_table_group *table_group;
	bool found = false;
	काष्ठा tce_iommu_group *tcegrp;

	mutex_lock(&container->lock);

	list_क्रम_each_entry(tcegrp, &container->group_list, next) अणु
		अगर (tcegrp->grp == iommu_group) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		pr_warn("tce_vfio: detaching unattached group #%u\n",
				iommu_group_id(iommu_group));
		जाओ unlock_निकास;
	पूर्ण

	list_del(&tcegrp->next);
	kमुक्त(tcegrp);

	table_group = iommu_group_get_iommudata(iommu_group);
	BUG_ON(!table_group);

	अगर (!table_group->ops || !table_group->ops->release_ownership)
		tce_iommu_release_ownership(container, table_group);
	अन्यथा
		tce_iommu_release_ownership_ddw(container, table_group);

unlock_निकास:
	mutex_unlock(&container->lock);
पूर्ण

अटल स्थिर काष्ठा vfio_iommu_driver_ops tce_iommu_driver_ops = अणु
	.name		= "iommu-vfio-powerpc",
	.owner		= THIS_MODULE,
	.खोलो		= tce_iommu_खोलो,
	.release	= tce_iommu_release,
	.ioctl		= tce_iommu_ioctl,
	.attach_group	= tce_iommu_attach_group,
	.detach_group	= tce_iommu_detach_group,
पूर्ण;

अटल पूर्णांक __init tce_iommu_init(व्योम)
अणु
	वापस vfio_रेजिस्टर_iommu_driver(&tce_iommu_driver_ops);
पूर्ण

अटल व्योम __निकास tce_iommu_cleanup(व्योम)
अणु
	vfio_unरेजिस्टर_iommu_driver(&tce_iommu_driver_ops);
पूर्ण

module_init(tce_iommu_init);
module_निकास(tce_iommu_cleanup);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

