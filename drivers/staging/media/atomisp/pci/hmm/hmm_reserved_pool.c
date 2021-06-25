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
 * This file contains functions क्रम reserved memory pool management
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/set_memory.h>

#समावेश "atomisp_internal.h"
#समावेश "hmm/hmm_pool.h"

/*
 * reserved memory pool ops.
 */
अटल अचिन्हित पूर्णांक get_pages_from_reserved_pool(व्योम *pool,
	काष्ठा hmm_page_object *page_obj,
	अचिन्हित पूर्णांक size, bool cached)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक repool_pgnr;
	पूर्णांक j;
	काष्ठा hmm_reserved_pool_info *repool_info = pool;

	अगर (!repool_info)
		वापस 0;

	spin_lock_irqsave(&repool_info->list_lock, flags);
	अगर (repool_info->initialized) अणु
		repool_pgnr = repool_info->index;

		क्रम (j = repool_pgnr - 1; j >= 0; j--) अणु
			page_obj[i].page = repool_info->pages[j];
			page_obj[i].type = HMM_PAGE_TYPE_RESERVED;
			i++;
			repool_info->index--;
			अगर (i == size)
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&repool_info->list_lock, flags);
	वापस i;
पूर्ण

अटल व्योम मुक्त_pages_to_reserved_pool(व्योम *pool,
					काष्ठा hmm_page_object *page_obj)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hmm_reserved_pool_info *repool_info = pool;

	अगर (!repool_info)
		वापस;

	spin_lock_irqsave(&repool_info->list_lock, flags);

	अगर (repool_info->initialized &&
	    repool_info->index < repool_info->pgnr &&
	    page_obj->type == HMM_PAGE_TYPE_RESERVED) अणु
		repool_info->pages[repool_info->index++] = page_obj->page;
	पूर्ण

	spin_unlock_irqrestore(&repool_info->list_lock, flags);
पूर्ण

अटल पूर्णांक hmm_reserved_pool_setup(काष्ठा hmm_reserved_pool_info **repool_info,
				   अचिन्हित पूर्णांक pool_size)
अणु
	काष्ठा hmm_reserved_pool_info *pool_info;

	pool_info = kदो_स्मृति(माप(काष्ठा hmm_reserved_pool_info),
			    GFP_KERNEL);
	अगर (unlikely(!pool_info))
		वापस -ENOMEM;

	pool_info->pages = kदो_स्मृति(माप(काष्ठा page *) * pool_size,
				   GFP_KERNEL);
	अगर (unlikely(!pool_info->pages)) अणु
		kमुक्त(pool_info);
		वापस -ENOMEM;
	पूर्ण

	pool_info->index = 0;
	pool_info->pgnr = 0;
	spin_lock_init(&pool_info->list_lock);
	pool_info->initialized = true;

	*repool_info = pool_info;

	वापस 0;
पूर्ण

अटल पूर्णांक hmm_reserved_pool_init(व्योम **pool, अचिन्हित पूर्णांक pool_size)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक blk_pgnr;
	अचिन्हित पूर्णांक pgnr = pool_size;
	अचिन्हित पूर्णांक order = 0;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक fail_number = 0;
	काष्ठा page *pages;
	पूर्णांक j;
	काष्ठा hmm_reserved_pool_info *repool_info;

	अगर (pool_size == 0)
		वापस 0;

	ret = hmm_reserved_pool_setup(&repool_info, pool_size);
	अगर (ret) अणु
		dev_err(atomisp_dev, "hmm_reserved_pool_setup failed.\n");
		वापस ret;
	पूर्ण

	pgnr = pool_size;

	i = 0;
	order = MAX_ORDER;

	जबतक (pgnr) अणु
		blk_pgnr = 1U << order;
		जबतक (blk_pgnr > pgnr) अणु
			order--;
			blk_pgnr >>= 1U;
		पूर्ण
		BUG_ON(order > MAX_ORDER);

		pages = alloc_pages(GFP_KERNEL | __GFP_NOWARN, order);
		अगर (unlikely(!pages)) अणु
			अगर (order == 0) अणु
				fail_number++;
				dev_err(atomisp_dev, "%s: alloc_pages failed: %d\n",
					__func__, fail_number);
				/* अगर fail five बार, will जाओ end */

				/* FIXME: whether is the mechanism is ok? */
				अगर (fail_number == ALLOC_PAGE_FAIL_NUM)
					जाओ end;
			पूर्ण अन्यथा अणु
				order--;
			पूर्ण
		पूर्ण अन्यथा अणु
			blk_pgnr = 1U << order;

			ret = set_pages_uc(pages, blk_pgnr);
			अगर (ret) अणु
				dev_err(atomisp_dev,
					"set pages uncached failed\n");
				__मुक्त_pages(pages, order);
				जाओ end;
			पूर्ण

			क्रम (j = 0; j < blk_pgnr; j++)
				repool_info->pages[i++] = pages + j;

			repool_info->index += blk_pgnr;
			repool_info->pgnr += blk_pgnr;

			pgnr -= blk_pgnr;

			fail_number = 0;
		पूर्ण
	पूर्ण

end:
	repool_info->initialized = true;

	*pool = repool_info;

	dev_info(atomisp_dev,
		 "hmm_reserved_pool init successfully,hmm_reserved_pool is with %d pages.\n",
		 repool_info->pgnr);
	वापस 0;
पूर्ण

अटल व्योम hmm_reserved_pool_निकास(व्योम **pool)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक pgnr;
	काष्ठा hmm_reserved_pool_info *repool_info = *pool;

	अगर (!repool_info)
		वापस;

	spin_lock_irqsave(&repool_info->list_lock, flags);
	अगर (!repool_info->initialized) अणु
		spin_unlock_irqrestore(&repool_info->list_lock, flags);
		वापस;
	पूर्ण
	pgnr = repool_info->pgnr;
	repool_info->index = 0;
	repool_info->pgnr = 0;
	repool_info->initialized = false;
	spin_unlock_irqrestore(&repool_info->list_lock, flags);

	क्रम (i = 0; i < pgnr; i++) अणु
		ret = set_pages_wb(repool_info->pages[i], 1);
		अगर (ret)
			dev_err(atomisp_dev,
				"set page to WB err...ret=%d\n", ret);
		/*
		W/A: set_pages_wb selकरोm वापस value = -EFAULT
		indicate that address of page is not in valid
		range(0xffff880000000000~0xffffc7ffffffffff)
		then, _मुक्त_pages would panic; Do not know why
		page address be valid, it maybe memory corruption by lowmemory
		*/
		अगर (!ret)
			__मुक्त_pages(repool_info->pages[i], 0);
	पूर्ण

	kमुक्त(repool_info->pages);
	kमुक्त(repool_info);

	*pool = शून्य;
पूर्ण

अटल पूर्णांक hmm_reserved_pool_inited(व्योम *pool)
अणु
	काष्ठा hmm_reserved_pool_info *repool_info = pool;

	अगर (!repool_info)
		वापस 0;

	वापस repool_info->initialized;
पूर्ण

काष्ठा hmm_pool_ops reserved_pops = अणु
	.pool_init		= hmm_reserved_pool_init,
	.pool_निकास		= hmm_reserved_pool_निकास,
	.pool_alloc_pages	= get_pages_from_reserved_pool,
	.pool_मुक्त_pages	= मुक्त_pages_to_reserved_pool,
	.pool_inited		= hmm_reserved_pool_inited,
पूर्ण;
