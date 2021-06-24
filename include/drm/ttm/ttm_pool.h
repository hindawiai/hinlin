<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Christian Kथघnig
 */

#अगर_अघोषित _TTM_PAGE_POOL_H_
#घोषणा _TTM_PAGE_POOL_H_

#समावेश <linux/mmzone.h>
#समावेश <linux/llist.h>
#समावेश <linux/spinlock.h>
#समावेश <drm/tपंचांग/tपंचांग_caching.h>

काष्ठा device;
काष्ठा tपंचांग_tt;
काष्ठा tपंचांग_pool;
काष्ठा tपंचांग_operation_ctx;

/**
 * tपंचांग_pool_type - Pool क्रम a certain memory type
 *
 * @pool: the pool we beदीर्घ to, might be शून्य क्रम the global ones
 * @order: the allocation order our pages have
 * @caching: the caching type our pages have
 * @shrinker_list: our place on the global shrinker list
 * @lock: protection of the page list
 * @pages: the list of pages in the pool
 */
काष्ठा tपंचांग_pool_type अणु
	काष्ठा tपंचांग_pool *pool;
	अचिन्हित पूर्णांक order;
	क्रमागत tपंचांग_caching caching;

	काष्ठा list_head shrinker_list;

	spinlock_t lock;
	काष्ठा list_head pages;
पूर्ण;

/**
 * tपंचांग_pool - Pool क्रम all caching and orders
 *
 * @use_dma_alloc: अगर coherent DMA allocations should be used
 * @use_dma32: अगर GFP_DMA32 should be used
 * @caching: pools क्रम each caching/order
 */
काष्ठा tपंचांग_pool अणु
	काष्ठा device *dev;

	bool use_dma_alloc;
	bool use_dma32;

	काष्ठा अणु
		काष्ठा tपंचांग_pool_type orders[MAX_ORDER];
	पूर्ण caching[TTM_NUM_CACHING_TYPES];
पूर्ण;

पूर्णांक tपंचांग_pool_alloc(काष्ठा tपंचांग_pool *pool, काष्ठा tपंचांग_tt *tt,
		   काष्ठा tपंचांग_operation_ctx *ctx);
व्योम tपंचांग_pool_मुक्त(काष्ठा tपंचांग_pool *pool, काष्ठा tपंचांग_tt *tt);

व्योम tपंचांग_pool_init(काष्ठा tपंचांग_pool *pool, काष्ठा device *dev,
		   bool use_dma_alloc, bool use_dma32);
व्योम tपंचांग_pool_fini(काष्ठा tपंचांग_pool *pool);

पूर्णांक tपंचांग_pool_debugfs(काष्ठा tपंचांग_pool *pool, काष्ठा seq_file *m);

पूर्णांक tपंचांग_pool_mgr_init(अचिन्हित दीर्घ num_pages);
व्योम tपंचांग_pool_mgr_fini(व्योम);

#पूर्ण_अगर
