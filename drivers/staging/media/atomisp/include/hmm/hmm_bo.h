<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित	__HMM_BO_H__
#घोषणा	__HMM_BO_H__

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश "mmu/isp_mmu.h"
#समावेश "hmm/hmm_common.h"
#समावेश "ia_css_types.h"

#घोषणा	check_bodev_null_वापस(bdev, exp)	\
		check_null_वापस(bdev, exp, \
			"NULL hmm_bo_device.\n")

#घोषणा	check_bodev_null_वापस_व्योम(bdev)	\
		check_null_वापस_व्योम(bdev, \
			"NULL hmm_bo_device.\n")

#घोषणा	check_bo_status_yes_जाओ(bo, _status, label) \
	var_not_equal_जाओ((bo->status & (_status)), (_status), \
			label, \
			"HMM buffer status not contain %s.\n", \
			#_status)

#घोषणा	check_bo_status_no_जाओ(bo, _status, label) \
	var_equal_जाओ((bo->status & (_status)), (_status), \
			label, \
			"HMM buffer status contains %s.\n", \
			#_status)

#घोषणा rbtree_node_to_hmm_bo(root_node)	\
	container_of((root_node), काष्ठा hmm_buffer_object, node)

#घोषणा	list_to_hmm_bo(list_ptr)	\
	list_entry((list_ptr), काष्ठा hmm_buffer_object, list)

#घोषणा	kref_to_hmm_bo(kref_ptr)	\
	list_entry((kref_ptr), काष्ठा hmm_buffer_object, kref)

#घोषणा	check_bo_null_वापस(bo, exp)	\
	check_null_वापस(bo, exp, "NULL hmm buffer object.\n")

#घोषणा	check_bo_null_वापस_व्योम(bo)	\
	check_null_वापस_व्योम(bo, "NULL hmm buffer object.\n")

#घोषणा	HMM_MAX_ORDER		3
#घोषणा	HMM_MIN_ORDER		0

#घोषणा	ISP_VM_START	0x0
#घोषणा	ISP_VM_SIZE	(0x7FFFFFFF)	/* 2G address space */
#घोषणा	ISP_PTR_शून्य	शून्य

#घोषणा	HMM_BO_DEVICE_INITED	0x1

क्रमागत hmm_bo_type अणु
	HMM_BO_PRIVATE,
	HMM_BO_SHARE,
	HMM_BO_USER,
	HMM_BO_LAST,
पूर्ण;

क्रमागत hmm_page_type अणु
	HMM_PAGE_TYPE_RESERVED,
	HMM_PAGE_TYPE_DYNAMIC,
	HMM_PAGE_TYPE_GENERAL,
पूर्ण;

#घोषणा	HMM_BO_MASK		0x1
#घोषणा	HMM_BO_FREE		0x0
#घोषणा	HMM_BO_ALLOCED	0x1
#घोषणा	HMM_BO_PAGE_ALLOCED	0x2
#घोषणा	HMM_BO_BINDED		0x4
#घोषणा	HMM_BO_MMAPED		0x8
#घोषणा	HMM_BO_VMAPED		0x10
#घोषणा	HMM_BO_VMAPED_CACHED	0x20
#घोषणा	HMM_BO_ACTIVE		0x1000
#घोषणा	HMM_BO_MEM_TYPE_USER     0x1
#घोषणा	HMM_BO_MEM_TYPE_PFN      0x2

काष्ठा hmm_bo_device अणु
	काष्ठा isp_mmu		mmu;

	/* start/pgnr/size is used to record the भव memory of this bo */
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक pgnr;
	अचिन्हित पूर्णांक size;

	/* list lock is used to protect the entire_bo_list */
	spinlock_t	list_lock;
	पूर्णांक flag;

	/* linked list क्रम entire buffer object */
	काष्ठा list_head entire_bo_list;
	/* rbtree क्रम मुख्यtain entire allocated vm */
	काष्ठा rb_root allocated_rbtree;
	/* rbtree क्रम मुख्यtain entire मुक्त vm */
	काष्ठा rb_root मुक्त_rbtree;
	काष्ठा mutex rbtree_mutex;
	काष्ठा kmem_cache *bo_cache;
पूर्ण;

काष्ठा hmm_page_object अणु
	काष्ठा page		*page;
	क्रमागत hmm_page_type	type;
पूर्ण;

काष्ठा hmm_buffer_object अणु
	काष्ठा hmm_bo_device	*bdev;
	काष्ठा list_head	list;
	काष्ठा kref	kref;

	काष्ठा page **pages;

	/* mutex protecting this BO */
	काष्ठा mutex		mutex;
	क्रमागत hmm_bo_type	type;
	काष्ठा hmm_page_object	*page_obj;	/* physical pages */
	पूर्णांक		from_highmem;
	पूर्णांक		mmap_count;
	पूर्णांक		status;
	पूर्णांक		mem_type;
	व्योम		*vmap_addr; /* kernel भव address by vmap */

	काष्ठा rb_node	node;
	अचिन्हित पूर्णांक	start;
	अचिन्हित पूर्णांक	end;
	अचिन्हित पूर्णांक	pgnr;
	/*
	 * When insert a bo which has the same pgnr with an existed
	 * bo node in the मुक्त_rbtree, using "prev & next" poपूर्णांकer
	 * to मुख्यtain a bo linked list instead of insert this bo
	 * पूर्णांकo मुक्त_rbtree directly, it will make sure each node
	 * in मुक्त_rbtree has dअगरferent pgnr.
	 * "prev & next" शेष is शून्य.
	 */
	काष्ठा hmm_buffer_object	*prev;
	काष्ठा hmm_buffer_object	*next;
पूर्ण;

काष्ठा hmm_buffer_object *hmm_bo_alloc(काष्ठा hmm_bo_device *bdev,
				       अचिन्हित पूर्णांक pgnr);

व्योम hmm_bo_release(काष्ठा hmm_buffer_object *bo);

पूर्णांक hmm_bo_device_init(काष्ठा hmm_bo_device *bdev,
		       काष्ठा isp_mmu_client *mmu_driver,
		       अचिन्हित पूर्णांक vaddr_start, अचिन्हित पूर्णांक size);

/*
 * clean up all hmm_bo_device related things.
 */
व्योम hmm_bo_device_निकास(काष्ठा hmm_bo_device *bdev);

/*
 * whether the bo device is inited or not.
 */
पूर्णांक hmm_bo_device_inited(काष्ठा hmm_bo_device *bdev);

/*
 * increse buffer object reference.
 */
व्योम hmm_bo_ref(काष्ठा hmm_buffer_object *bo);

/*
 * decrese buffer object reference. अगर reference reaches 0,
 * release function of the buffer object will be called.
 *
 * this call is also used to release hmm_buffer_object or its
 * upper level object with it embedded in. you need to call
 * this function when it is no दीर्घer used.
 *
 * Note:
 *
 * user करोnt need to care about पूर्णांकernal resource release of
 * the buffer object in the release callback, it will be
 * handled पूर्णांकernally.
 *
 * this call will only release पूर्णांकernal resource of the buffer
 * object but will not मुक्त the buffer object itself, as the
 * buffer object can be both pre-allocated अटलally or
 * dynamically allocated. so user need to deal with the release
 * of the buffer object itself manually. below example shows
 * the normal हाल of using the buffer object.
 *
 *	काष्ठा hmm_buffer_object *bo = hmm_bo_create(bdev, pgnr);
 *	......
 *	hmm_bo_unref(bo);
 *
 * or:
 *
 *	काष्ठा hmm_buffer_object bo;
 *
 *	hmm_bo_init(bdev, &bo, pgnr, शून्य);
 *	...
 *	hmm_bo_unref(&bo);
 */
व्योम hmm_bo_unref(काष्ठा hmm_buffer_object *bo);

/*
 * allocate/मुक्त physical pages क्रम the bo. will try to alloc mem
 * from highmem अगर from_highmem is set, and type indicate that the
 * pages will be allocated by using video driver (क्रम share buffer)
 * or by ISP driver itself.
 */

पूर्णांक hmm_bo_allocated(काष्ठा hmm_buffer_object *bo);

/*
 * allocate/मुक्त physical pages क्रम the bo. will try to alloc mem
 * from highmem अगर from_highmem is set, and type indicate that the
 * pages will be allocated by using video driver (क्रम share buffer)
 * or by ISP driver itself.
 */
पूर्णांक hmm_bo_alloc_pages(काष्ठा hmm_buffer_object *bo,
		       क्रमागत hmm_bo_type type, पूर्णांक from_highmem,
		       स्थिर व्योम __user *userptr, bool cached);
व्योम hmm_bo_मुक्त_pages(काष्ठा hmm_buffer_object *bo);
पूर्णांक hmm_bo_page_allocated(काष्ठा hmm_buffer_object *bo);

/*
 * get physical page info of the bo.
 */
पूर्णांक hmm_bo_get_page_info(काष्ठा hmm_buffer_object *bo,
			 काष्ठा hmm_page_object **page_obj, पूर्णांक *pgnr);

/*
 * bind/unbind the physical pages to a भव address space.
 */
पूर्णांक hmm_bo_bind(काष्ठा hmm_buffer_object *bo);
व्योम hmm_bo_unbind(काष्ठा hmm_buffer_object *bo);
पूर्णांक hmm_bo_binded(काष्ठा hmm_buffer_object *bo);

/*
 * vmap buffer object's pages to contiguous kernel भव address.
 * अगर the buffer has been vmaped, वापस the भव address directly.
 */
व्योम *hmm_bo_vmap(काष्ठा hmm_buffer_object *bo, bool cached);

/*
 * flush the cache क्रम the vmapped buffer object's pages,
 * अगर the buffer has not been vmapped, वापस directly.
 */
व्योम hmm_bo_flush_vmap(काष्ठा hmm_buffer_object *bo);

/*
 * vunmap buffer object's kernel भव address.
 */
व्योम hmm_bo_vunmap(काष्ठा hmm_buffer_object *bo);

/*
 * mmap the bo's physical pages to specअगरic vma.
 *
 * vma's address space size must be the same as bo's size,
 * otherwise it will वापस -EINVAL.
 *
 * vma->vm_flags will be set to (VM_RESERVED | VM_IO).
 */
पूर्णांक hmm_bo_mmap(काष्ठा vm_area_काष्ठा *vma,
		काष्ठा hmm_buffer_object *bo);

बाह्य काष्ठा hmm_pool	dynamic_pool;
बाह्य काष्ठा hmm_pool	reserved_pool;

/*
 * find the buffer object by its भव address vaddr.
 * वापस शून्य अगर no such buffer object found.
 */
काष्ठा hmm_buffer_object *hmm_bo_device_search_start(
    काष्ठा hmm_bo_device *bdev, ia_css_ptr vaddr);

/*
 * find the buffer object by its भव address.
 * it करोes not need to be the start address of one bo,
 * it can be an address within the range of one bo.
 * वापस शून्य अगर no such buffer object found.
 */
काष्ठा hmm_buffer_object *hmm_bo_device_search_in_range(
    काष्ठा hmm_bo_device *bdev, ia_css_ptr vaddr);

/*
 * find the buffer object with kernel भव address vaddr.
 * वापस शून्य अगर no such buffer object found.
 */
काष्ठा hmm_buffer_object *hmm_bo_device_search_vmap_start(
    काष्ठा hmm_bo_device *bdev, स्थिर व्योम *vaddr);

#पूर्ण_अगर
