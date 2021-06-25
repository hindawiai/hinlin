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
 * This file contains functions क्रम buffer object काष्ठाure management
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/gfp.h>		/* क्रम GFP_ATOMIC */
#समावेश <linux/mm.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>		/* क्रम kदो_स्मृति */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <यंत्र/current.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/file.h>

#समावेश <यंत्र/set_memory.h>

#समावेश "atomisp_internal.h"
#समावेश "hmm/hmm_common.h"
#समावेश "hmm/hmm_pool.h"
#समावेश "hmm/hmm_bo.h"

अटल अचिन्हित पूर्णांक order_to_nr(अचिन्हित पूर्णांक order)
अणु
	वापस 1U << order;
पूर्ण

अटल अचिन्हित पूर्णांक nr_to_order_bottom(अचिन्हित पूर्णांक nr)
अणु
	वापस fls(nr) - 1;
पूर्ण

अटल पूर्णांक __bo_init(काष्ठा hmm_bo_device *bdev, काष्ठा hmm_buffer_object *bo,
		     अचिन्हित पूर्णांक pgnr)
अणु
	check_bodev_null_वापस(bdev, -EINVAL);
	var_equal_वापस(hmm_bo_device_inited(bdev), 0, -EINVAL,
			 "hmm_bo_device not inited yet.\n");
	/* prevent zero size buffer object */
	अगर (pgnr == 0) अणु
		dev_err(atomisp_dev, "0 size buffer is not allowed.\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(bo, 0, माप(*bo));
	mutex_init(&bo->mutex);

	/* init the bo->list HEAD as an element of entire_bo_list */
	INIT_LIST_HEAD(&bo->list);

	bo->bdev = bdev;
	bo->vmap_addr = शून्य;
	bo->status = HMM_BO_FREE;
	bo->start = bdev->start;
	bo->pgnr = pgnr;
	bo->end = bo->start + pgnr_to_size(pgnr);
	bo->prev = शून्य;
	bo->next = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा hmm_buffer_object *__bo_search_and_हटाओ_from_मुक्त_rbtree(
    काष्ठा rb_node *node, अचिन्हित पूर्णांक pgnr)
अणु
	काष्ठा hmm_buffer_object *this, *ret_bo, *temp_bo;

	this = rb_entry(node, काष्ठा hmm_buffer_object, node);
	अगर (this->pgnr == pgnr ||
	    (this->pgnr > pgnr && !this->node.rb_left)) अणु
		जाओ हटाओ_bo_and_वापस;
	पूर्ण अन्यथा अणु
		अगर (this->pgnr < pgnr) अणु
			अगर (!this->node.rb_right)
				वापस शून्य;
			ret_bo = __bo_search_and_हटाओ_from_मुक्त_rbtree(
				     this->node.rb_right, pgnr);
		पूर्ण अन्यथा अणु
			ret_bo = __bo_search_and_हटाओ_from_मुक्त_rbtree(
				     this->node.rb_left, pgnr);
		पूर्ण
		अगर (!ret_bo) अणु
			अगर (this->pgnr > pgnr)
				जाओ हटाओ_bo_and_वापस;
			अन्यथा
				वापस शून्य;
		पूर्ण
		वापस ret_bo;
	पूर्ण

हटाओ_bo_and_वापस:
	/* NOTE: All nodes on मुक्त rbtree have a 'prev' that poपूर्णांकs to शून्य.
	 * 1. check अगर 'this->next' is शून्य:
	 *	yes: erase 'this' node and rebalance rbtree, return 'this'.
	 */
	अगर (!this->next) अणु
		rb_erase(&this->node, &this->bdev->मुक्त_rbtree);
		वापस this;
	पूर्ण
	/* NOTE: अगर 'this->next' is not NULL, always return 'this->next' bo.
	 * 2. check अगर 'this->next->next' is शून्य:
	 *	yes: change the related 'next/prev' poपूर्णांकer,
	 *		वापस 'this->next' but the rbtree stays unchanged.
	 */
	temp_bo = this->next;
	this->next = temp_bo->next;
	अगर (temp_bo->next)
		temp_bo->next->prev = this;
	temp_bo->next = शून्य;
	temp_bo->prev = शून्य;
	वापस temp_bo;
पूर्ण

अटल काष्ठा hmm_buffer_object *__bo_search_by_addr(काष्ठा rb_root *root,
	ia_css_ptr start)
अणु
	काष्ठा rb_node *n = root->rb_node;
	काष्ठा hmm_buffer_object *bo;

	करो अणु
		bo = rb_entry(n, काष्ठा hmm_buffer_object, node);

		अगर (bo->start > start) अणु
			अगर (!n->rb_left)
				वापस शून्य;
			n = n->rb_left;
		पूर्ण अन्यथा अगर (bo->start < start) अणु
			अगर (!n->rb_right)
				वापस शून्य;
			n = n->rb_right;
		पूर्ण अन्यथा अणु
			वापस bo;
		पूर्ण
	पूर्ण जबतक (n);

	वापस शून्य;
पूर्ण

अटल काष्ठा hmm_buffer_object *__bo_search_by_addr_in_range(
    काष्ठा rb_root *root, अचिन्हित पूर्णांक start)
अणु
	काष्ठा rb_node *n = root->rb_node;
	काष्ठा hmm_buffer_object *bo;

	करो अणु
		bo = rb_entry(n, काष्ठा hmm_buffer_object, node);

		अगर (bo->start > start) अणु
			अगर (!n->rb_left)
				वापस शून्य;
			n = n->rb_left;
		पूर्ण अन्यथा अणु
			अगर (bo->end > start)
				वापस bo;
			अगर (!n->rb_right)
				वापस शून्य;
			n = n->rb_right;
		पूर्ण
	पूर्ण जबतक (n);

	वापस शून्य;
पूर्ण

अटल व्योम __bo_insert_to_मुक्त_rbtree(काष्ठा rb_root *root,
				       काष्ठा hmm_buffer_object *bo)
अणु
	काष्ठा rb_node **new = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hmm_buffer_object *this;
	अचिन्हित पूर्णांक pgnr = bo->pgnr;

	जबतक (*new) अणु
		parent = *new;
		this = container_of(*new, काष्ठा hmm_buffer_object, node);

		अगर (pgnr < this->pgnr) अणु
			new = &((*new)->rb_left);
		पूर्ण अन्यथा अगर (pgnr > this->pgnr) अणु
			new = &((*new)->rb_right);
		पूर्ण अन्यथा अणु
			bo->prev = this;
			bo->next = this->next;
			अगर (this->next)
				this->next->prev = bo;
			this->next = bo;
			bo->status = (bo->status & ~HMM_BO_MASK) | HMM_BO_FREE;
			वापस;
		पूर्ण
	पूर्ण

	bo->status = (bo->status & ~HMM_BO_MASK) | HMM_BO_FREE;

	rb_link_node(&bo->node, parent, new);
	rb_insert_color(&bo->node, root);
पूर्ण

अटल व्योम __bo_insert_to_alloc_rbtree(काष्ठा rb_root *root,
					काष्ठा hmm_buffer_object *bo)
अणु
	काष्ठा rb_node **new = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा hmm_buffer_object *this;
	अचिन्हित पूर्णांक start = bo->start;

	जबतक (*new) अणु
		parent = *new;
		this = container_of(*new, काष्ठा hmm_buffer_object, node);

		अगर (start < this->start)
			new = &((*new)->rb_left);
		अन्यथा
			new = &((*new)->rb_right);
	पूर्ण

	kref_init(&bo->kref);
	bo->status = (bo->status & ~HMM_BO_MASK) | HMM_BO_ALLOCED;

	rb_link_node(&bo->node, parent, new);
	rb_insert_color(&bo->node, root);
पूर्ण

अटल काष्ठा hmm_buffer_object *__bo_अवरोध_up(काष्ठा hmm_bo_device *bdev,
	काष्ठा hmm_buffer_object *bo,
	अचिन्हित पूर्णांक pgnr)
अणु
	काष्ठा hmm_buffer_object *new_bo;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	new_bo = kmem_cache_alloc(bdev->bo_cache, GFP_KERNEL);
	अगर (!new_bo) अणु
		dev_err(atomisp_dev, "%s: __bo_alloc failed!\n", __func__);
		वापस शून्य;
	पूर्ण
	ret = __bo_init(bdev, new_bo, pgnr);
	अगर (ret) अणु
		dev_err(atomisp_dev, "%s: __bo_init failed!\n", __func__);
		kmem_cache_मुक्त(bdev->bo_cache, new_bo);
		वापस शून्य;
	पूर्ण

	new_bo->start = bo->start;
	new_bo->end = new_bo->start + pgnr_to_size(pgnr);
	bo->start = new_bo->end;
	bo->pgnr = bo->pgnr - pgnr;

	spin_lock_irqsave(&bdev->list_lock, flags);
	list_add_tail(&new_bo->list, &bo->list);
	spin_unlock_irqrestore(&bdev->list_lock, flags);

	वापस new_bo;
पूर्ण

अटल व्योम __bo_take_off_handling(काष्ठा hmm_buffer_object *bo)
अणु
	काष्ठा hmm_bo_device *bdev = bo->bdev;
	/* There are 4 situations when we take off a known bo from मुक्त rbtree:
	 * 1. अगर bo->next && bo->prev == शून्य, bo is a rbtree node
	 *	and करोes not have a linked list after bo, to take off this bo,
	 *	we just need erase bo directly and rebalance the मुक्त rbtree
	 */
	अगर (!bo->prev && !bo->next) अणु
		rb_erase(&bo->node, &bdev->मुक्त_rbtree);
		/* 2. when bo->next != शून्य && bo->prev == शून्य, bo is a rbtree node,
		 *	and has a linked list,to take off this bo we need erase bo
		 *	first, then, insert bo->next पूर्णांकo मुक्त rbtree and rebalance
		 *	the मुक्त rbtree
		 */
	पूर्ण अन्यथा अगर (!bo->prev && bo->next) अणु
		bo->next->prev = शून्य;
		rb_erase(&bo->node, &bdev->मुक्त_rbtree);
		__bo_insert_to_मुक्त_rbtree(&bdev->मुक्त_rbtree, bo->next);
		bo->next = शून्य;
		/* 3. when bo->prev != शून्य && bo->next == शून्य, bo is not a rbtree
		 *	node, bo is the last element of the linked list after rbtree
		 *	node, to take off this bo, we just need set the "prev/next"
		 *	poपूर्णांकers to शून्य, the मुक्त rbtree stays unchaged
		 */
	पूर्ण अन्यथा अगर (bo->prev && !bo->next) अणु
		bo->prev->next = शून्य;
		bo->prev = शून्य;
		/* 4. when bo->prev != शून्य && bo->next != शून्य ,bo is not a rbtree
		 *	node, bo is in the middle of the linked list after rbtree node,
		 *	to take off this bo, we just set take the "prev/next" poपूर्णांकers
		 *	to शून्य, the मुक्त rbtree stays unchaged
		 */
	पूर्ण अन्यथा अगर (bo->prev && bo->next) अणु
		bo->next->prev = bo->prev;
		bo->prev->next = bo->next;
		bo->next = शून्य;
		bo->prev = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा hmm_buffer_object *__bo_merge(काष्ठा hmm_buffer_object *bo,
	काष्ठा hmm_buffer_object *next_bo)
अणु
	काष्ठा hmm_bo_device *bdev;
	अचिन्हित दीर्घ flags;

	bdev = bo->bdev;
	next_bo->start = bo->start;
	next_bo->pgnr = next_bo->pgnr + bo->pgnr;

	spin_lock_irqsave(&bdev->list_lock, flags);
	list_del(&bo->list);
	spin_unlock_irqrestore(&bdev->list_lock, flags);

	kmem_cache_मुक्त(bo->bdev->bo_cache, bo);

	वापस next_bo;
पूर्ण

/*
 * hmm_bo_device functions.
 */
पूर्णांक hmm_bo_device_init(काष्ठा hmm_bo_device *bdev,
		       काष्ठा isp_mmu_client *mmu_driver,
		       अचिन्हित पूर्णांक vaddr_start,
		       अचिन्हित पूर्णांक size)
अणु
	काष्ठा hmm_buffer_object *bo;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	check_bodev_null_वापस(bdev, -EINVAL);

	ret = isp_mmu_init(&bdev->mmu, mmu_driver);
	अगर (ret) अणु
		dev_err(atomisp_dev, "isp_mmu_init failed.\n");
		वापस ret;
	पूर्ण

	bdev->start = vaddr_start;
	bdev->pgnr = माप_प्रकारo_pgnr_उच्चमान(size);
	bdev->size = pgnr_to_size(bdev->pgnr);

	spin_lock_init(&bdev->list_lock);
	mutex_init(&bdev->rbtree_mutex);

	bdev->flag = HMM_BO_DEVICE_INITED;

	INIT_LIST_HEAD(&bdev->entire_bo_list);
	bdev->allocated_rbtree = RB_ROOT;
	bdev->मुक्त_rbtree = RB_ROOT;

	bdev->bo_cache = kmem_cache_create("bo_cache",
					   माप(काष्ठा hmm_buffer_object), 0, 0, शून्य);
	अगर (!bdev->bo_cache) अणु
		dev_err(atomisp_dev, "%s: create cache failed!\n", __func__);
		isp_mmu_निकास(&bdev->mmu);
		वापस -ENOMEM;
	पूर्ण

	bo = kmem_cache_alloc(bdev->bo_cache, GFP_KERNEL);
	अगर (!bo) अणु
		dev_err(atomisp_dev, "%s: __bo_alloc failed!\n", __func__);
		isp_mmu_निकास(&bdev->mmu);
		वापस -ENOMEM;
	पूर्ण

	ret = __bo_init(bdev, bo, bdev->pgnr);
	अगर (ret) अणु
		dev_err(atomisp_dev, "%s: __bo_init failed!\n", __func__);
		kmem_cache_मुक्त(bdev->bo_cache, bo);
		isp_mmu_निकास(&bdev->mmu);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&bdev->list_lock, flags);
	list_add_tail(&bo->list, &bdev->entire_bo_list);
	spin_unlock_irqrestore(&bdev->list_lock, flags);

	__bo_insert_to_मुक्त_rbtree(&bdev->मुक्त_rbtree, bo);

	वापस 0;
पूर्ण

काष्ठा hmm_buffer_object *hmm_bo_alloc(काष्ठा hmm_bo_device *bdev,
				       अचिन्हित पूर्णांक pgnr)
अणु
	काष्ठा hmm_buffer_object *bo, *new_bo;
	काष्ठा rb_root *root = &bdev->मुक्त_rbtree;

	check_bodev_null_वापस(bdev, शून्य);
	var_equal_वापस(hmm_bo_device_inited(bdev), 0, शून्य,
			 "hmm_bo_device not inited yet.\n");

	अगर (pgnr == 0) अणु
		dev_err(atomisp_dev, "0 size buffer is not allowed.\n");
		वापस शून्य;
	पूर्ण

	mutex_lock(&bdev->rbtree_mutex);
	bo = __bo_search_and_हटाओ_from_मुक्त_rbtree(root->rb_node, pgnr);
	अगर (!bo) अणु
		mutex_unlock(&bdev->rbtree_mutex);
		dev_err(atomisp_dev, "%s: Out of Memory! hmm_bo_alloc failed",
			__func__);
		वापस शून्य;
	पूर्ण

	अगर (bo->pgnr > pgnr) अणु
		new_bo = __bo_अवरोध_up(bdev, bo, pgnr);
		अगर (!new_bo) अणु
			mutex_unlock(&bdev->rbtree_mutex);
			dev_err(atomisp_dev, "%s: __bo_break_up failed!\n",
				__func__);
			वापस शून्य;
		पूर्ण

		__bo_insert_to_alloc_rbtree(&bdev->allocated_rbtree, new_bo);
		__bo_insert_to_मुक्त_rbtree(&bdev->मुक्त_rbtree, bo);

		mutex_unlock(&bdev->rbtree_mutex);
		वापस new_bo;
	पूर्ण

	__bo_insert_to_alloc_rbtree(&bdev->allocated_rbtree, bo);

	mutex_unlock(&bdev->rbtree_mutex);
	वापस bo;
पूर्ण

व्योम hmm_bo_release(काष्ठा hmm_buffer_object *bo)
अणु
	काष्ठा hmm_bo_device *bdev = bo->bdev;
	काष्ठा hmm_buffer_object *next_bo, *prev_bo;

	mutex_lock(&bdev->rbtree_mutex);

	/*
	 * FIX ME:
	 *
	 * how to destroy the bo when it is stilled MMAPED?
	 *
	 * ideally, this will not happened as hmm_bo_release
	 * will only be called when kref reaches 0, and in mmap
	 * operation the hmm_bo_ref will eventually be called.
	 * so, अगर this happened, something goes wrong.
	 */
	अगर (bo->status & HMM_BO_MMAPED) अणु
		mutex_unlock(&bdev->rbtree_mutex);
		dev_dbg(atomisp_dev, "destroy bo which is MMAPED, do nothing\n");
		वापस;
	पूर्ण

	अगर (bo->status & HMM_BO_BINDED) अणु
		dev_warn(atomisp_dev, "the bo is still binded, unbind it first...\n");
		hmm_bo_unbind(bo);
	पूर्ण

	अगर (bo->status & HMM_BO_PAGE_ALLOCED) अणु
		dev_warn(atomisp_dev, "the pages is not freed, free pages first\n");
		hmm_bo_मुक्त_pages(bo);
	पूर्ण
	अगर (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) अणु
		dev_warn(atomisp_dev, "the vunmap is not done, do it...\n");
		hmm_bo_vunmap(bo);
	पूर्ण

	rb_erase(&bo->node, &bdev->allocated_rbtree);

	prev_bo = list_entry(bo->list.prev, काष्ठा hmm_buffer_object, list);
	next_bo = list_entry(bo->list.next, काष्ठा hmm_buffer_object, list);

	अगर (bo->list.prev != &bdev->entire_bo_list &&
	    prev_bo->end == bo->start &&
	    (prev_bo->status & HMM_BO_MASK) == HMM_BO_FREE) अणु
		__bo_take_off_handling(prev_bo);
		bo = __bo_merge(prev_bo, bo);
	पूर्ण

	अगर (bo->list.next != &bdev->entire_bo_list &&
	    next_bo->start == bo->end &&
	    (next_bo->status & HMM_BO_MASK) == HMM_BO_FREE) अणु
		__bo_take_off_handling(next_bo);
		bo = __bo_merge(bo, next_bo);
	पूर्ण

	__bo_insert_to_मुक्त_rbtree(&bdev->मुक्त_rbtree, bo);

	mutex_unlock(&bdev->rbtree_mutex);
	वापस;
पूर्ण

व्योम hmm_bo_device_निकास(काष्ठा hmm_bo_device *bdev)
अणु
	काष्ठा hmm_buffer_object *bo;
	अचिन्हित दीर्घ flags;

	dev_dbg(atomisp_dev, "%s: entering!\n", __func__);

	check_bodev_null_वापस_व्योम(bdev);

	/*
	 * release all allocated bos even they a in use
	 * and all bos will be merged पूर्णांकo a big bo
	 */
	जबतक (!RB_EMPTY_ROOT(&bdev->allocated_rbtree))
		hmm_bo_release(
		    rbtree_node_to_hmm_bo(bdev->allocated_rbtree.rb_node));

	dev_dbg(atomisp_dev, "%s: finished releasing all allocated bos!\n",
		__func__);

	/* मुक्त all bos to release all ISP भव memory */
	जबतक (!list_empty(&bdev->entire_bo_list)) अणु
		bo = list_to_hmm_bo(bdev->entire_bo_list.next);

		spin_lock_irqsave(&bdev->list_lock, flags);
		list_del(&bo->list);
		spin_unlock_irqrestore(&bdev->list_lock, flags);

		kmem_cache_मुक्त(bdev->bo_cache, bo);
	पूर्ण

	dev_dbg(atomisp_dev, "%s: finished to free all bos!\n", __func__);

	kmem_cache_destroy(bdev->bo_cache);

	isp_mmu_निकास(&bdev->mmu);
पूर्ण

पूर्णांक hmm_bo_device_inited(काष्ठा hmm_bo_device *bdev)
अणु
	check_bodev_null_वापस(bdev, -EINVAL);

	वापस bdev->flag == HMM_BO_DEVICE_INITED;
पूर्ण

पूर्णांक hmm_bo_allocated(काष्ठा hmm_buffer_object *bo)
अणु
	check_bo_null_वापस(bo, 0);

	वापस bo->status & HMM_BO_ALLOCED;
पूर्ण

काष्ठा hmm_buffer_object *hmm_bo_device_search_start(
    काष्ठा hmm_bo_device *bdev, ia_css_ptr vaddr)
अणु
	काष्ठा hmm_buffer_object *bo;

	check_bodev_null_वापस(bdev, शून्य);

	mutex_lock(&bdev->rbtree_mutex);
	bo = __bo_search_by_addr(&bdev->allocated_rbtree, vaddr);
	अगर (!bo) अणु
		mutex_unlock(&bdev->rbtree_mutex);
		dev_err(atomisp_dev, "%s can not find bo with addr: 0x%x\n",
			__func__, vaddr);
		वापस शून्य;
	पूर्ण
	mutex_unlock(&bdev->rbtree_mutex);

	वापस bo;
पूर्ण

काष्ठा hmm_buffer_object *hmm_bo_device_search_in_range(
    काष्ठा hmm_bo_device *bdev, अचिन्हित पूर्णांक vaddr)
अणु
	काष्ठा hmm_buffer_object *bo;

	check_bodev_null_वापस(bdev, शून्य);

	mutex_lock(&bdev->rbtree_mutex);
	bo = __bo_search_by_addr_in_range(&bdev->allocated_rbtree, vaddr);
	अगर (!bo) अणु
		mutex_unlock(&bdev->rbtree_mutex);
		dev_err(atomisp_dev, "%s can not find bo contain addr: 0x%x\n",
			__func__, vaddr);
		वापस शून्य;
	पूर्ण
	mutex_unlock(&bdev->rbtree_mutex);

	वापस bo;
पूर्ण

काष्ठा hmm_buffer_object *hmm_bo_device_search_vmap_start(
    काष्ठा hmm_bo_device *bdev, स्थिर व्योम *vaddr)
अणु
	काष्ठा list_head *pos;
	काष्ठा hmm_buffer_object *bo;
	अचिन्हित दीर्घ flags;

	check_bodev_null_वापस(bdev, शून्य);

	spin_lock_irqsave(&bdev->list_lock, flags);
	list_क्रम_each(pos, &bdev->entire_bo_list) अणु
		bo = list_to_hmm_bo(pos);
		/* pass bo which has no vm_node allocated */
		अगर ((bo->status & HMM_BO_MASK) == HMM_BO_FREE)
			जारी;
		अगर (bo->vmap_addr == vaddr)
			जाओ found;
	पूर्ण
	spin_unlock_irqrestore(&bdev->list_lock, flags);
	वापस शून्य;
found:
	spin_unlock_irqrestore(&bdev->list_lock, flags);
	वापस bo;
पूर्ण

अटल व्योम मुक्त_निजी_bo_pages(काष्ठा hmm_buffer_object *bo,
				  काष्ठा hmm_pool *dypool,
				  काष्ठा hmm_pool *repool,
				  पूर्णांक मुक्त_pgnr)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < मुक्त_pgnr; i++) अणु
		चयन (bo->page_obj[i].type) अणु
		हाल HMM_PAGE_TYPE_RESERVED:
			अगर (repool->pops
			    && repool->pops->pool_मुक्त_pages) अणु
				repool->pops->pool_मुक्त_pages(repool->pool_info,
							      &bo->page_obj[i]);
				hmm_mem_stat.res_cnt--;
			पूर्ण
			अवरोध;
		/*
		 * HMM_PAGE_TYPE_GENERAL indicates that pages are from प्रणाली
		 * memory, so when मुक्त them, they should be put पूर्णांकo dynamic
		 * pool.
		 */
		हाल HMM_PAGE_TYPE_DYNAMIC:
		हाल HMM_PAGE_TYPE_GENERAL:
			अगर (dypool->pops
			    && dypool->pops->pool_inited
			    && dypool->pops->pool_inited(dypool->pool_info)) अणु
				अगर (dypool->pops->pool_मुक्त_pages)
					dypool->pops->pool_मुक्त_pages(
					    dypool->pool_info,
					    &bo->page_obj[i]);
				अवरोध;
			पूर्ण

			fallthrough;

		/*
		 * अगर dynamic memory pool करोesn't exist, need to मुक्त
		 * pages to प्रणाली directly.
		 */
		शेष:
			ret = set_pages_wb(bo->page_obj[i].page, 1);
			अगर (ret)
				dev_err(atomisp_dev,
					"set page to WB err ...ret = %d\n",
					ret);
			/*
			W/A: set_pages_wb selकरोm वापस value = -EFAULT
			indicate that address of page is not in valid
			range(0xffff880000000000~0xffffc7ffffffffff)
			then, _मुक्त_pages would panic; Do not know why page
			address be valid,it maybe memory corruption by lowmemory
			*/
			अगर (!ret) अणु
				__मुक्त_pages(bo->page_obj[i].page, 0);
				hmm_mem_stat.sys_size--;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

/*Allocate pages which will be used only by ISP*/
अटल पूर्णांक alloc_निजी_pages(काष्ठा hmm_buffer_object *bo,
			       पूर्णांक from_highmem,
			       bool cached,
			       काष्ठा hmm_pool *dypool,
			       काष्ठा hmm_pool *repool)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pgnr, order, blk_pgnr, alloc_pgnr;
	काष्ठा page *pages;
	gfp_t gfp = GFP_NOWAIT | __GFP_NOWARN; /* REVISIT: need __GFP_FS too? */
	पूर्णांक i, j;
	पूर्णांक failure_number = 0;
	bool reduce_order = false;
	bool lack_mem = true;

	अगर (from_highmem)
		gfp |= __GFP_HIGHMEM;

	pgnr = bo->pgnr;

	bo->page_obj = kदो_स्मृति_array(pgnr, माप(काष्ठा hmm_page_object),
				     GFP_KERNEL);
	अगर (unlikely(!bo->page_obj))
		वापस -ENOMEM;

	i = 0;
	alloc_pgnr = 0;

	/*
	 * get physical pages from dynamic pages pool.
	 */
	अगर (dypool->pops && dypool->pops->pool_alloc_pages) अणु
		alloc_pgnr = dypool->pops->pool_alloc_pages(dypool->pool_info,
			     bo->page_obj, pgnr,
			     cached);
		hmm_mem_stat.dyc_size -= alloc_pgnr;

		अगर (alloc_pgnr == pgnr)
			वापस 0;
	पूर्ण

	pgnr -= alloc_pgnr;
	i += alloc_pgnr;

	/*
	 * get physical pages from reserved pages pool क्रम atomisp.
	 */
	अगर (repool->pops && repool->pops->pool_alloc_pages) अणु
		alloc_pgnr = repool->pops->pool_alloc_pages(repool->pool_info,
			     &bo->page_obj[i], pgnr,
			     cached);
		hmm_mem_stat.res_cnt += alloc_pgnr;
		अगर (alloc_pgnr == pgnr)
			वापस 0;
	पूर्ण

	pgnr -= alloc_pgnr;
	i += alloc_pgnr;

	जबतक (pgnr) अणु
		order = nr_to_order_bottom(pgnr);
		/*
		 * अगर be लघु of memory, we will set order to 0
		 * everyसमय.
		 */
		अगर (lack_mem)
			order = HMM_MIN_ORDER;
		अन्यथा अगर (order > HMM_MAX_ORDER)
			order = HMM_MAX_ORDER;
retry:
		/*
		 * When order > HMM_MIN_ORDER, क्रम perक्रमmance reasons we करोn't
		 * want alloc_pages() to sleep. In हाल it fails and fallbacks
		 * to HMM_MIN_ORDER or in हाल the requested order is originally
		 * the minimum value, we can allow alloc_pages() to sleep क्रम
		 * robustness purpose.
		 *
		 * REVISIT: why __GFP_FS is necessary?
		 */
		अगर (order == HMM_MIN_ORDER) अणु
			gfp &= ~GFP_NOWAIT;
			gfp |= __GFP_RECLAIM | __GFP_FS;
		पूर्ण

		pages = alloc_pages(gfp, order);
		अगर (unlikely(!pages)) अणु
			/*
			 * in low memory हाल, अगर allocation page fails,
			 * we turn to try अगर order=0 allocation could
			 * succeed. अगर order=0 fails too, that means there is
			 * no memory left.
			 */
			अगर (order == HMM_MIN_ORDER) अणु
				dev_err(atomisp_dev,
					"%s: cannot allocate pages\n",
					__func__);
				जाओ cleanup;
			पूर्ण
			order = HMM_MIN_ORDER;
			failure_number++;
			reduce_order = true;
			/*
			 * अगर fail two बार continuously, we think be लघु
			 * of memory now.
			 */
			अगर (failure_number == 2) अणु
				lack_mem = true;
				failure_number = 0;
			पूर्ण
			जाओ retry;
		पूर्ण अन्यथा अणु
			blk_pgnr = order_to_nr(order);

			अगर (!cached) अणु
				/*
				 * set memory to uncacheable -- UC_MINUS
				 */
				ret = set_pages_uc(pages, blk_pgnr);
				अगर (ret) अणु
					dev_err(atomisp_dev,
						"set page uncacheablefailed.\n");

					__मुक्त_pages(pages, order);

					जाओ cleanup;
				पूर्ण
			पूर्ण

			क्रम (j = 0; j < blk_pgnr; j++) अणु
				bo->page_obj[i].page = pages + j;
				bo->page_obj[i++].type = HMM_PAGE_TYPE_GENERAL;
			पूर्ण

			pgnr -= blk_pgnr;
			hmm_mem_stat.sys_size += blk_pgnr;

			/*
			 * अगर order is not reduced this समय, clear
			 * failure_number.
			 */
			अगर (reduce_order)
				reduce_order = false;
			अन्यथा
				failure_number = 0;
		पूर्ण
	पूर्ण

	वापस 0;
cleanup:
	alloc_pgnr = i;
	मुक्त_निजी_bo_pages(bo, dypool, repool, alloc_pgnr);

	kमुक्त(bo->page_obj);

	वापस -ENOMEM;
पूर्ण

अटल व्योम मुक्त_निजी_pages(काष्ठा hmm_buffer_object *bo,
			       काष्ठा hmm_pool *dypool,
			       काष्ठा hmm_pool *repool)
अणु
	मुक्त_निजी_bo_pages(bo, dypool, repool, bo->pgnr);

	kमुक्त(bo->page_obj);
पूर्ण

अटल व्योम मुक्त_user_pages(काष्ठा hmm_buffer_object *bo,
			    अचिन्हित पूर्णांक page_nr)
अणु
	पूर्णांक i;

	hmm_mem_stat.usr_size -= bo->pgnr;

	अगर (bo->mem_type == HMM_BO_MEM_TYPE_PFN) अणु
		unpin_user_pages(bo->pages, page_nr);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < page_nr; i++)
			put_page(bo->pages[i]);
	पूर्ण
	kमुक्त(bo->pages);
	kमुक्त(bo->page_obj);
पूर्ण

/*
 * Convert user space भव address पूर्णांकo pages list
 */
अटल पूर्णांक alloc_user_pages(काष्ठा hmm_buffer_object *bo,
			    स्थिर व्योम __user *userptr, bool cached)
अणु
	पूर्णांक page_nr;
	पूर्णांक i;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा page **pages;

	pages = kदो_स्मृति_array(bo->pgnr, माप(काष्ठा page *), GFP_KERNEL);
	अगर (unlikely(!pages))
		वापस -ENOMEM;

	bo->page_obj = kदो_स्मृति_array(bo->pgnr, माप(काष्ठा hmm_page_object),
				     GFP_KERNEL);
	अगर (unlikely(!bo->page_obj)) अणु
		kमुक्त(pages);
		वापस -ENOMEM;
	पूर्ण

	mutex_unlock(&bo->mutex);
	mmap_पढ़ो_lock(current->mm);
	vma = find_vma(current->mm, (अचिन्हित दीर्घ)userptr);
	mmap_पढ़ो_unlock(current->mm);
	अगर (!vma) अणु
		dev_err(atomisp_dev, "find_vma failed\n");
		kमुक्त(bo->page_obj);
		kमुक्त(pages);
		mutex_lock(&bo->mutex);
		वापस -EFAULT;
	पूर्ण
	mutex_lock(&bo->mutex);
	/*
	 * Handle frame buffer allocated in other kerenl space driver
	 * and map to user space
	 */

	userptr = untagged_addr(userptr);

	bo->pages = pages;

	अगर (vma->vm_flags & (VM_IO | VM_PFNMAP)) अणु
		page_nr = pin_user_pages((अचिन्हित दीर्घ)userptr, bo->pgnr,
					 FOLL_LONGTERM | FOLL_WRITE,
					 pages, शून्य);
		bo->mem_type = HMM_BO_MEM_TYPE_PFN;
	पूर्ण अन्यथा अणु
		/*Handle frame buffer allocated in user space*/
		mutex_unlock(&bo->mutex);
		page_nr = get_user_pages_fast((अचिन्हित दीर्घ)userptr,
					      (पूर्णांक)(bo->pgnr), 1, pages);
		mutex_lock(&bo->mutex);
		bo->mem_type = HMM_BO_MEM_TYPE_USER;
	पूर्ण

	dev_dbg(atomisp_dev, "%s: %d %s pages were allocated as 0x%08x\n",
		__func__,
		bo->pgnr,
		bo->mem_type == HMM_BO_MEM_TYPE_USER ? "user" : "pfn", page_nr);

	hmm_mem_stat.usr_size += bo->pgnr;

	/* can be written by caller, not क्रमced */
	अगर (page_nr != bo->pgnr) अणु
		dev_err(atomisp_dev,
			"get_user_pages err: bo->pgnr = %d, pgnr actually pinned = %d.\n",
			bo->pgnr, page_nr);
		अगर (page_nr < 0)
			page_nr = 0;
		जाओ out_of_mem;
	पूर्ण

	क्रम (i = 0; i < bo->pgnr; i++) अणु
		bo->page_obj[i].page = pages[i];
		bo->page_obj[i].type = HMM_PAGE_TYPE_GENERAL;
	पूर्ण

	वापस 0;

out_of_mem:

	मुक्त_user_pages(bo, page_nr);

	वापस -ENOMEM;
पूर्ण

/*
 * allocate/मुक्त physical pages क्रम the bo.
 *
 * type indicate where are the pages from. currently we have 3 types
 * of memory: HMM_BO_PRIVATE, HMM_BO_USER, HMM_BO_SHARE.
 *
 * from_highmem is only valid when type is HMM_BO_PRIVATE, it will
 * try to alloc memory from highmem अगर from_highmem is set.
 *
 * userptr is only valid when type is HMM_BO_USER, it indicates
 * the start address from user space task.
 *
 * from_highmem and userptr will both be ignored when type is
 * HMM_BO_SHARE.
 */
पूर्णांक hmm_bo_alloc_pages(काष्ठा hmm_buffer_object *bo,
		       क्रमागत hmm_bo_type type, पूर्णांक from_highmem,
		       स्थिर व्योम __user *userptr, bool cached)
अणु
	पूर्णांक ret = -EINVAL;

	check_bo_null_वापस(bo, -EINVAL);

	mutex_lock(&bo->mutex);
	check_bo_status_no_जाओ(bo, HMM_BO_PAGE_ALLOCED, status_err);

	/*
	 * TO DO:
	 * add HMM_BO_USER type
	 */
	अगर (type == HMM_BO_PRIVATE) अणु
		ret = alloc_निजी_pages(bo, from_highmem,
					  cached, &dynamic_pool, &reserved_pool);
	पूर्ण अन्यथा अगर (type == HMM_BO_USER) अणु
		ret = alloc_user_pages(bo, userptr, cached);
	पूर्ण अन्यथा अणु
		dev_err(atomisp_dev, "invalid buffer type.\n");
		ret = -EINVAL;
	पूर्ण
	अगर (ret)
		जाओ alloc_err;

	bo->type = type;

	bo->status |= HMM_BO_PAGE_ALLOCED;

	mutex_unlock(&bo->mutex);

	वापस 0;

alloc_err:
	mutex_unlock(&bo->mutex);
	dev_err(atomisp_dev, "alloc pages err...\n");
	वापस ret;
status_err:
	mutex_unlock(&bo->mutex);
	dev_err(atomisp_dev,
		"buffer object has already page allocated.\n");
	वापस -EINVAL;
पूर्ण

/*
 * मुक्त physical pages of the bo.
 */
व्योम hmm_bo_मुक्त_pages(काष्ठा hmm_buffer_object *bo)
अणु
	check_bo_null_वापस_व्योम(bo);

	mutex_lock(&bo->mutex);

	check_bo_status_yes_जाओ(bo, HMM_BO_PAGE_ALLOCED, status_err2);

	/* clear the flag anyway. */
	bo->status &= (~HMM_BO_PAGE_ALLOCED);

	अगर (bo->type == HMM_BO_PRIVATE)
		मुक्त_निजी_pages(bo, &dynamic_pool, &reserved_pool);
	अन्यथा अगर (bo->type == HMM_BO_USER)
		मुक्त_user_pages(bo, bo->pgnr);
	अन्यथा
		dev_err(atomisp_dev, "invalid buffer type.\n");
	mutex_unlock(&bo->mutex);

	वापस;

status_err2:
	mutex_unlock(&bo->mutex);
	dev_err(atomisp_dev,
		"buffer object not page allocated yet.\n");
पूर्ण

पूर्णांक hmm_bo_page_allocated(काष्ठा hmm_buffer_object *bo)
अणु
	check_bo_null_वापस(bo, 0);

	वापस bo->status & HMM_BO_PAGE_ALLOCED;
पूर्ण

/*
 * get physical page info of the bo.
 */
पूर्णांक hmm_bo_get_page_info(काष्ठा hmm_buffer_object *bo,
			 काष्ठा hmm_page_object **page_obj, पूर्णांक *pgnr)
अणु
	check_bo_null_वापस(bo, -EINVAL);

	mutex_lock(&bo->mutex);

	check_bo_status_yes_जाओ(bo, HMM_BO_PAGE_ALLOCED, status_err);

	*page_obj = bo->page_obj;
	*pgnr = bo->pgnr;

	mutex_unlock(&bo->mutex);

	वापस 0;

status_err:
	dev_err(atomisp_dev,
		"buffer object not page allocated yet.\n");
	mutex_unlock(&bo->mutex);
	वापस -EINVAL;
पूर्ण

/*
 * bind the physical pages to a भव address space.
 */
पूर्णांक hmm_bo_bind(काष्ठा hmm_buffer_object *bo)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक virt;
	काष्ठा hmm_bo_device *bdev;
	अचिन्हित पूर्णांक i;

	check_bo_null_वापस(bo, -EINVAL);

	mutex_lock(&bo->mutex);

	check_bo_status_yes_जाओ(bo,
				 HMM_BO_PAGE_ALLOCED | HMM_BO_ALLOCED,
				 status_err1);

	check_bo_status_no_जाओ(bo, HMM_BO_BINDED, status_err2);

	bdev = bo->bdev;

	virt = bo->start;

	क्रम (i = 0; i < bo->pgnr; i++) अणु
		ret =
		    isp_mmu_map(&bdev->mmu, virt,
				page_to_phys(bo->page_obj[i].page), 1);
		अगर (ret)
			जाओ map_err;
		virt += (1 << PAGE_SHIFT);
	पूर्ण

	/*
	 * flush TBL here.
	 *
	 * theoretically, we करोnot need to flush TLB as we didnot change
	 * any existed address mappings, but क्रम Silicon Hive's MMU, its
	 * really a bug here. I guess when fetching PTEs (page table entity)
	 * to TLB, its MMU will fetch additional INVALID PTEs स्वतःmatically
	 * क्रम perक्रमmance issue. EX, we only set up 1 page address mapping,
	 * meaning updating 1 PTE, but the MMU fetches 4 PTE at one समय,
	 * so the additional 3 PTEs are invalid.
	 */
	अगर (bo->start != 0x0)
		isp_mmu_flush_tlb_range(&bdev->mmu, bo->start,
					(bo->pgnr << PAGE_SHIFT));

	bo->status |= HMM_BO_BINDED;

	mutex_unlock(&bo->mutex);

	वापस 0;

map_err:
	/* unbind the physical pages with related भव address space */
	virt = bo->start;
	क्रम ( ; i > 0; i--) अणु
		isp_mmu_unmap(&bdev->mmu, virt, 1);
		virt += pgnr_to_size(1);
	पूर्ण

	mutex_unlock(&bo->mutex);
	dev_err(atomisp_dev,
		"setup MMU address mapping failed.\n");
	वापस ret;

status_err2:
	mutex_unlock(&bo->mutex);
	dev_err(atomisp_dev, "buffer object already binded.\n");
	वापस -EINVAL;
status_err1:
	mutex_unlock(&bo->mutex);
	dev_err(atomisp_dev,
		"buffer object vm_node or page not allocated.\n");
	वापस -EINVAL;
पूर्ण

/*
 * unbind the physical pages with related भव address space.
 */
व्योम hmm_bo_unbind(काष्ठा hmm_buffer_object *bo)
अणु
	अचिन्हित पूर्णांक virt;
	काष्ठा hmm_bo_device *bdev;
	अचिन्हित पूर्णांक i;

	check_bo_null_वापस_व्योम(bo);

	mutex_lock(&bo->mutex);

	check_bo_status_yes_जाओ(bo,
				 HMM_BO_PAGE_ALLOCED |
				 HMM_BO_ALLOCED |
				 HMM_BO_BINDED, status_err);

	bdev = bo->bdev;

	virt = bo->start;

	क्रम (i = 0; i < bo->pgnr; i++) अणु
		isp_mmu_unmap(&bdev->mmu, virt, 1);
		virt += pgnr_to_size(1);
	पूर्ण

	/*
	 * flush TLB as the address mapping has been हटाओd and
	 * related TLBs should be invalidated.
	 */
	isp_mmu_flush_tlb_range(&bdev->mmu, bo->start,
				(bo->pgnr << PAGE_SHIFT));

	bo->status &= (~HMM_BO_BINDED);

	mutex_unlock(&bo->mutex);

	वापस;

status_err:
	mutex_unlock(&bo->mutex);
	dev_err(atomisp_dev,
		"buffer vm or page not allocated or not binded yet.\n");
पूर्ण

पूर्णांक hmm_bo_binded(काष्ठा hmm_buffer_object *bo)
अणु
	पूर्णांक ret;

	check_bo_null_वापस(bo, 0);

	mutex_lock(&bo->mutex);

	ret = bo->status & HMM_BO_BINDED;

	mutex_unlock(&bo->mutex);

	वापस ret;
पूर्ण

व्योम *hmm_bo_vmap(काष्ठा hmm_buffer_object *bo, bool cached)
अणु
	काष्ठा page **pages;
	पूर्णांक i;

	check_bo_null_वापस(bo, शून्य);

	mutex_lock(&bo->mutex);
	अगर (((bo->status & HMM_BO_VMAPED) && !cached) ||
	    ((bo->status & HMM_BO_VMAPED_CACHED) && cached)) अणु
		mutex_unlock(&bo->mutex);
		वापस bo->vmap_addr;
	पूर्ण

	/* cached status need to be changed, so vunmap first */
	अगर (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) अणु
		vunmap(bo->vmap_addr);
		bo->vmap_addr = शून्य;
		bo->status &= ~(HMM_BO_VMAPED | HMM_BO_VMAPED_CACHED);
	पूर्ण

	pages = kदो_स्मृति_array(bo->pgnr, माप(*pages), GFP_KERNEL);
	अगर (unlikely(!pages)) अणु
		mutex_unlock(&bo->mutex);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < bo->pgnr; i++)
		pages[i] = bo->page_obj[i].page;

	bo->vmap_addr = vmap(pages, bo->pgnr, VM_MAP,
			     cached ? PAGE_KERNEL : PAGE_KERNEL_NOCACHE);
	अगर (unlikely(!bo->vmap_addr)) अणु
		kमुक्त(pages);
		mutex_unlock(&bo->mutex);
		dev_err(atomisp_dev, "vmap failed...\n");
		वापस शून्य;
	पूर्ण
	bo->status |= (cached ? HMM_BO_VMAPED_CACHED : HMM_BO_VMAPED);

	kमुक्त(pages);

	mutex_unlock(&bo->mutex);
	वापस bo->vmap_addr;
पूर्ण

व्योम hmm_bo_flush_vmap(काष्ठा hmm_buffer_object *bo)
अणु
	check_bo_null_वापस_व्योम(bo);

	mutex_lock(&bo->mutex);
	अगर (!(bo->status & HMM_BO_VMAPED_CACHED) || !bo->vmap_addr) अणु
		mutex_unlock(&bo->mutex);
		वापस;
	पूर्ण

	clflush_cache_range(bo->vmap_addr, bo->pgnr * PAGE_SIZE);
	mutex_unlock(&bo->mutex);
पूर्ण

व्योम hmm_bo_vunmap(काष्ठा hmm_buffer_object *bo)
अणु
	check_bo_null_वापस_व्योम(bo);

	mutex_lock(&bo->mutex);
	अगर (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) अणु
		vunmap(bo->vmap_addr);
		bo->vmap_addr = शून्य;
		bo->status &= ~(HMM_BO_VMAPED | HMM_BO_VMAPED_CACHED);
	पूर्ण

	mutex_unlock(&bo->mutex);
	वापस;
पूर्ण

व्योम hmm_bo_ref(काष्ठा hmm_buffer_object *bo)
अणु
	check_bo_null_वापस_व्योम(bo);

	kref_get(&bo->kref);
पूर्ण

अटल व्योम kref_hmm_bo_release(काष्ठा kref *kref)
अणु
	अगर (!kref)
		वापस;

	hmm_bo_release(kref_to_hmm_bo(kref));
पूर्ण

व्योम hmm_bo_unref(काष्ठा hmm_buffer_object *bo)
अणु
	check_bo_null_वापस_व्योम(bo);

	kref_put(&bo->kref, kref_hmm_bo_release);
पूर्ण

अटल व्योम hmm_bo_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hmm_buffer_object *bo =
	    (काष्ठा hmm_buffer_object *)vma->vm_निजी_data;

	check_bo_null_वापस_व्योम(bo);

	hmm_bo_ref(bo);

	mutex_lock(&bo->mutex);

	bo->status |= HMM_BO_MMAPED;

	bo->mmap_count++;

	mutex_unlock(&bo->mutex);
पूर्ण

अटल व्योम hmm_bo_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hmm_buffer_object *bo =
	    (काष्ठा hmm_buffer_object *)vma->vm_निजी_data;

	check_bo_null_वापस_व्योम(bo);

	hmm_bo_unref(bo);

	mutex_lock(&bo->mutex);

	bo->mmap_count--;

	अगर (!bo->mmap_count) अणु
		bo->status &= (~HMM_BO_MMAPED);
		vma->vm_निजी_data = शून्य;
	पूर्ण

	mutex_unlock(&bo->mutex);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा hmm_bo_vm_ops = अणु
	.खोलो = hmm_bo_vm_खोलो,
	.बंद = hmm_bo_vm_बंद,
पूर्ण;

/*
 * mmap the bo to user space.
 */
पूर्णांक hmm_bo_mmap(काष्ठा vm_area_काष्ठा *vma, काष्ठा hmm_buffer_object *bo)
अणु
	अचिन्हित पूर्णांक start, end;
	अचिन्हित पूर्णांक virt;
	अचिन्हित पूर्णांक pgnr, i;
	अचिन्हित पूर्णांक pfn;

	check_bo_null_वापस(bo, -EINVAL);

	check_bo_status_yes_जाओ(bo, HMM_BO_PAGE_ALLOCED, status_err);

	pgnr = bo->pgnr;
	start = vma->vm_start;
	end = vma->vm_end;

	/*
	 * check vma's virtual address space size and buffer object's size.
	 * must be the same.
	 */
	अगर ((start + pgnr_to_size(pgnr)) != end) अणु
		dev_warn(atomisp_dev,
			 "vma's address space size not equal to buffer object's size");
		वापस -EINVAL;
	पूर्ण

	virt = vma->vm_start;
	क्रम (i = 0; i < pgnr; i++) अणु
		pfn = page_to_pfn(bo->page_obj[i].page);
		अगर (remap_pfn_range(vma, virt, pfn, PAGE_SIZE, PAGE_SHARED)) अणु
			dev_warn(atomisp_dev,
				 "remap_pfn_range failed: virt = 0x%x, pfn = 0x%x, mapped_pgnr = %d\n",
				 virt, pfn, 1);
			वापस -EINVAL;
		पूर्ण
		virt += PAGE_SIZE;
	पूर्ण

	vma->vm_निजी_data = bo;

	vma->vm_ops = &hmm_bo_vm_ops;
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;

	/*
	 * call hmm_bo_vm_खोलो explicitly.
	 */
	hmm_bo_vm_खोलो(vma);

	वापस 0;

status_err:
	dev_err(atomisp_dev, "buffer page not allocated yet.\n");
	वापस -EINVAL;
पूर्ण
