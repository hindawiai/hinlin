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
#अगर_अघोषित __HMM_POOL_H__
#घोषणा __HMM_POOL_H__

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kref.h>
#समावेश "hmm_common.h"
#समावेश "hmm/hmm_bo.h"

#घोषणा ALLOC_PAGE_FAIL_NUM		5

क्रमागत hmm_pool_type अणु
	HMM_POOL_TYPE_RESERVED,
	HMM_POOL_TYPE_DYNAMIC,
पूर्ण;

/**
 * काष्ठा hmm_pool_ops  -  memory pool callbacks.
 *
 * @pool_init:		   initialize the memory pool.
 * @pool_निकास:		   uninitialize the memory pool.
 * @pool_alloc_pages:	   allocate pages from memory pool.
 * @pool_मुक्त_pages:	   मुक्त pages to memory pool.
 * @pool_inited:	   check whether memory pool is initialized.
 */
काष्ठा hmm_pool_ops अणु
	पूर्णांक (*pool_init)(व्योम **pool, अचिन्हित पूर्णांक pool_size);
	व्योम (*pool_निकास)(व्योम **pool);
	अचिन्हित पूर्णांक (*pool_alloc_pages)(व्योम *pool,
					 काष्ठा hmm_page_object *page_obj,
					 अचिन्हित पूर्णांक size, bool cached);
	व्योम (*pool_मुक्त_pages)(व्योम *pool,
				काष्ठा hmm_page_object *page_obj);
	पूर्णांक (*pool_inited)(व्योम *pool);
पूर्ण;

काष्ठा hmm_pool अणु
	काष्ठा hmm_pool_ops	*pops;

	व्योम			*pool_info;
पूर्ण;

/**
 * काष्ठा hmm_reserved_pool_info  - represents reserved pool निजी data.
 * @pages:			    a array that store physical pages.
 *				    The array is as reserved memory pool.
 * @index:			    to indicate the first blank page number
 *				    in reserved memory pool(pages array).
 * @pgnr:			    the valid page amount in reserved memory
 *				    pool.
 * @list_lock:			    list lock is used to protect the operation
 *				    to reserved memory pool.
 * @flag:			    reserved memory pool state flag.
 */
काष्ठा hmm_reserved_pool_info अणु
	काष्ठा page		**pages;

	अचिन्हित पूर्णांक		index;
	अचिन्हित पूर्णांक		pgnr;
	spinlock_t		list_lock;
	bool			initialized;
पूर्ण;

/**
 * काष्ठा hmm_dynamic_pool_info  -  represents dynamic pool निजी data.
 * @pages_list:			    a list that store physical pages.
 *				    The pages list is as dynamic memory pool.
 * @list_lock:			    list lock is used to protect the operation
 *				    to dynamic memory pool.
 * @flag:			    dynamic memory pool state flag.
 * @pgptr_cache:		    काष्ठा kmem_cache, manages a cache.
 */
काष्ठा hmm_dynamic_pool_info अणु
	काष्ठा list_head	pages_list;

	/* list lock is used to protect the मुक्त pages block lists */
	spinlock_t		list_lock;

	काष्ठा kmem_cache	*pgptr_cache;
	bool			initialized;

	अचिन्हित पूर्णांक		pool_size;
	अचिन्हित पूर्णांक		pgnr;
पूर्ण;

काष्ठा hmm_page अणु
	काष्ठा page		*page;
	काष्ठा list_head	list;
पूर्ण;

बाह्य काष्ठा hmm_pool_ops	reserved_pops;
बाह्य काष्ठा hmm_pool_ops	dynamic_pops;

#पूर्ण_अगर
