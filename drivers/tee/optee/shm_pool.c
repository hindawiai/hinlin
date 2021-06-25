<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Linaro Limited
 * Copyright (c) 2017, EPAM Systems
 */
#समावेश <linux/device.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश "optee_private.h"
#समावेश "optee_smc.h"
#समावेश "shm_pool.h"

अटल पूर्णांक pool_op_alloc(काष्ठा tee_shm_pool_mgr *poolm,
			 काष्ठा tee_shm *shm, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक order = get_order(size);
	काष्ठा page *page;
	पूर्णांक rc = 0;

	page = alloc_pages(GFP_KERNEL | __GFP_ZERO, order);
	अगर (!page)
		वापस -ENOMEM;

	shm->kaddr = page_address(page);
	shm->paddr = page_to_phys(page);
	shm->size = PAGE_SIZE << order;

	अगर (shm->flags & TEE_SHM_DMA_BUF) अणु
		अचिन्हित पूर्णांक nr_pages = 1 << order, i;
		काष्ठा page **pages;

		pages = kसुस्मृति(nr_pages, माप(pages), GFP_KERNEL);
		अगर (!pages)
			वापस -ENOMEM;

		क्रम (i = 0; i < nr_pages; i++) अणु
			pages[i] = page;
			page++;
		पूर्ण

		shm->flags |= TEE_SHM_REGISTER;
		rc = optee_shm_रेजिस्टर(shm->ctx, shm, pages, nr_pages,
					(अचिन्हित दीर्घ)shm->kaddr);
		kमुक्त(pages);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम pool_op_मुक्त(काष्ठा tee_shm_pool_mgr *poolm,
			 काष्ठा tee_shm *shm)
अणु
	अगर (shm->flags & TEE_SHM_DMA_BUF)
		optee_shm_unरेजिस्टर(shm->ctx, shm);

	मुक्त_pages((अचिन्हित दीर्घ)shm->kaddr, get_order(shm->size));
	shm->kaddr = शून्य;
पूर्ण

अटल व्योम pool_op_destroy_poolmgr(काष्ठा tee_shm_pool_mgr *poolm)
अणु
	kमुक्त(poolm);
पूर्ण

अटल स्थिर काष्ठा tee_shm_pool_mgr_ops pool_ops = अणु
	.alloc = pool_op_alloc,
	.मुक्त = pool_op_मुक्त,
	.destroy_poolmgr = pool_op_destroy_poolmgr,
पूर्ण;

/**
 * optee_shm_pool_alloc_pages() - create page-based allocator pool
 *
 * This pool is used when OP-TEE supports dymanic SHM. In this हाल
 * command buffers and such are allocated from kernel's own memory.
 */
काष्ठा tee_shm_pool_mgr *optee_shm_pool_alloc_pages(व्योम)
अणु
	काष्ठा tee_shm_pool_mgr *mgr = kzalloc(माप(*mgr), GFP_KERNEL);

	अगर (!mgr)
		वापस ERR_PTR(-ENOMEM);

	mgr->ops = &pool_ops;

	वापस mgr;
पूर्ण
