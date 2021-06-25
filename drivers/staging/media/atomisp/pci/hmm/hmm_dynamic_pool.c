<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
/*
 * This file contains functions क्रम dynamic memory pool management
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/set_memory.h>

#समावेश "atomisp_internal.h"

#समावेश "hmm/hmm_pool.h"

/*
 * dynamic memory pool ops.
 */
अटल अचिन्हित पूर्णांक get_pages_from_dynamic_pool(व्योम *pool,
	काष्ठा hmm_page_object *page_obj,
	अचिन्हित पूर्णांक size, bool cached)
अणु
	काष्ठा hmm_page *hmm_page;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा hmm_dynamic_pool_info *dypool_info = pool;

	अगर (!dypool_info)
		वापस 0;

	spin_lock_irqsave(&dypool_info->list_lock, flags);
	अगर (dypool_info->initialized) अणु
		जबतक (!list_empty(&dypool_info->pages_list)) अणु
			hmm_page = list_entry(dypool_info->pages_list.next,
					      काष्ठा hmm_page, list);

			list_del(&hmm_page->list);
			dypool_info->pgnr--;
			spin_unlock_irqrestore(&dypool_info->list_lock, flags);

			page_obj[i].page = hmm_page->page;
			page_obj[i++].type = HMM_PAGE_TYPE_DYNAMIC;
			kmem_cache_मुक्त(dypool_info->pgptr_cache, hmm_page);

			अगर (i == size)
				वापस i;

			spin_lock_irqsave(&dypool_info->list_lock, flags);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dypool_info->list_lock, flags);

	वापस i;
पूर्ण

अटल व्योम मुक्त_pages_to_dynamic_pool(व्योम *pool,
				       काष्ठा hmm_page_object *page_obj)
अणु
	काष्ठा hmm_page *hmm_page;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	काष्ठा hmm_dynamic_pool_info *dypool_info = pool;

	अगर (!dypool_info)
		वापस;

	spin_lock_irqsave(&dypool_info->list_lock, flags);
	अगर (!dypool_info->initialized) अणु
		spin_unlock_irqrestore(&dypool_info->list_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&dypool_info->list_lock, flags);

	अगर (page_obj->type == HMM_PAGE_TYPE_RESERVED)
		वापस;

	अगर (dypool_info->pgnr >= dypool_info->pool_size) अणु
		/* मुक्त page directly back to प्रणाली */
		ret = set_pages_wb(page_obj->page, 1);
		अगर (ret)
			dev_err(atomisp_dev,
				"set page to WB err ...ret=%d\n", ret);
		/*
		W/A: set_pages_wb selकरोm वापस value = -EFAULT
		indicate that address of page is not in valid
		range(0xffff880000000000~0xffffc7ffffffffff)
		then, _मुक्त_pages would panic; Do not know why page
		address be valid, it maybe memory corruption by lowmemory
		*/
		अगर (!ret) अणु
			__मुक्त_pages(page_obj->page, 0);
			hmm_mem_stat.sys_size--;
		पूर्ण
		वापस;
	पूर्ण
	hmm_page = kmem_cache_zalloc(dypool_info->pgptr_cache,
				     GFP_KERNEL);
	अगर (!hmm_page) अणु
		/* मुक्त page directly */
		ret = set_pages_wb(page_obj->page, 1);
		अगर (ret)
			dev_err(atomisp_dev,
				"set page to WB err ...ret=%d\n", ret);
		अगर (!ret) अणु
			__मुक्त_pages(page_obj->page, 0);
			hmm_mem_stat.sys_size--;
		पूर्ण
		वापस;
	पूर्ण

	hmm_page->page = page_obj->page;

	/*
	 * add to pages_list of pages_pool
	 */
	spin_lock_irqsave(&dypool_info->list_lock, flags);
	list_add_tail(&hmm_page->list, &dypool_info->pages_list);
	dypool_info->pgnr++;
	spin_unlock_irqrestore(&dypool_info->list_lock, flags);
	hmm_mem_stat.dyc_size++;
पूर्ण

अटल पूर्णांक hmm_dynamic_pool_init(व्योम **pool, अचिन्हित पूर्णांक pool_size)
अणु
	काष्ठा hmm_dynamic_pool_info *dypool_info;

	अगर (pool_size == 0)
		वापस 0;

	dypool_info = kदो_स्मृति(माप(काष्ठा hmm_dynamic_pool_info),
			      GFP_KERNEL);
	अगर (unlikely(!dypool_info))
		वापस -ENOMEM;

	dypool_info->pgptr_cache = kmem_cache_create("pgptr_cache",
				   माप(काष्ठा hmm_page), 0,
				   SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!dypool_info->pgptr_cache) अणु
		kमुक्त(dypool_info);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&dypool_info->pages_list);
	spin_lock_init(&dypool_info->list_lock);
	dypool_info->initialized = true;
	dypool_info->pool_size = pool_size;
	dypool_info->pgnr = 0;

	*pool = dypool_info;

	वापस 0;
पूर्ण

अटल व्योम hmm_dynamic_pool_निकास(व्योम **pool)
अणु
	काष्ठा hmm_dynamic_pool_info *dypool_info = *pool;
	काष्ठा hmm_page *hmm_page;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!dypool_info)
		वापस;

	spin_lock_irqsave(&dypool_info->list_lock, flags);
	अगर (!dypool_info->initialized) अणु
		spin_unlock_irqrestore(&dypool_info->list_lock, flags);
		वापस;
	पूर्ण
	dypool_info->initialized = false;

	जबतक (!list_empty(&dypool_info->pages_list)) अणु
		hmm_page = list_entry(dypool_info->pages_list.next,
				      काष्ठा hmm_page, list);

		list_del(&hmm_page->list);
		spin_unlock_irqrestore(&dypool_info->list_lock, flags);

		/* can cause thपढ़ो sleep, so cannot be put पूर्णांकo spin_lock */
		ret = set_pages_wb(hmm_page->page, 1);
		अगर (ret)
			dev_err(atomisp_dev,
				"set page to WB err...ret=%d\n", ret);
		अगर (!ret) अणु
			__मुक्त_pages(hmm_page->page, 0);
			hmm_mem_stat.dyc_size--;
			hmm_mem_stat.sys_size--;
		पूर्ण
		kmem_cache_मुक्त(dypool_info->pgptr_cache, hmm_page);
		spin_lock_irqsave(&dypool_info->list_lock, flags);
	पूर्ण

	spin_unlock_irqrestore(&dypool_info->list_lock, flags);

	kmem_cache_destroy(dypool_info->pgptr_cache);

	kमुक्त(dypool_info);

	*pool = शून्य;
पूर्ण

अटल पूर्णांक hmm_dynamic_pool_inited(व्योम *pool)
अणु
	काष्ठा hmm_dynamic_pool_info *dypool_info = pool;

	अगर (!dypool_info)
		वापस 0;

	वापस dypool_info->initialized;
पूर्ण

काष्ठा hmm_pool_ops dynamic_pops = अणु
	.pool_init		= hmm_dynamic_pool_init,
	.pool_निकास		= hmm_dynamic_pool_निकास,
	.pool_alloc_pages	= get_pages_from_dynamic_pool,
	.pool_मुक्त_pages	= मुक्त_pages_to_dynamic_pool,
	.pool_inited		= hmm_dynamic_pool_inited,
पूर्ण;
