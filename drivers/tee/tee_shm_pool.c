<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Linaro Limited
 */
#समावेश <linux/device.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश "tee_private.h"

अटल पूर्णांक pool_op_gen_alloc(काष्ठा tee_shm_pool_mgr *poolm,
			     काष्ठा tee_shm *shm, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ va;
	काष्ठा gen_pool *genpool = poolm->निजी_data;
	माप_प्रकार s = roundup(size, 1 << genpool->min_alloc_order);

	va = gen_pool_alloc(genpool, s);
	अगर (!va)
		वापस -ENOMEM;

	स_रखो((व्योम *)va, 0, s);
	shm->kaddr = (व्योम *)va;
	shm->paddr = gen_pool_virt_to_phys(genpool, va);
	shm->size = s;
	वापस 0;
पूर्ण

अटल व्योम pool_op_gen_मुक्त(काष्ठा tee_shm_pool_mgr *poolm,
			     काष्ठा tee_shm *shm)
अणु
	gen_pool_मुक्त(poolm->निजी_data, (अचिन्हित दीर्घ)shm->kaddr,
		      shm->size);
	shm->kaddr = शून्य;
पूर्ण

अटल व्योम pool_op_gen_destroy_poolmgr(काष्ठा tee_shm_pool_mgr *poolm)
अणु
	gen_pool_destroy(poolm->निजी_data);
	kमुक्त(poolm);
पूर्ण

अटल स्थिर काष्ठा tee_shm_pool_mgr_ops pool_ops_generic = अणु
	.alloc = pool_op_gen_alloc,
	.मुक्त = pool_op_gen_मुक्त,
	.destroy_poolmgr = pool_op_gen_destroy_poolmgr,
पूर्ण;

/**
 * tee_shm_pool_alloc_res_mem() - Create a shared memory pool from reserved
 * memory range
 * @priv_info:	Inक्रमmation क्रम driver निजी shared memory pool
 * @dmabuf_info: Inक्रमmation क्रम dma-buf shared memory pool
 *
 * Start and end of pools will must be page aligned.
 *
 * Allocation with the flag TEE_SHM_DMA_BUF set will use the range supplied
 * in @dmabuf, others will use the range provided by @priv.
 *
 * @वापसs poपूर्णांकer to a 'struct tee_shm_pool' or an ERR_PTR on failure.
 */
काष्ठा tee_shm_pool *
tee_shm_pool_alloc_res_mem(काष्ठा tee_shm_pool_mem_info *priv_info,
			   काष्ठा tee_shm_pool_mem_info *dmabuf_info)
अणु
	काष्ठा tee_shm_pool_mgr *priv_mgr;
	काष्ठा tee_shm_pool_mgr *dmabuf_mgr;
	व्योम *rc;

	/*
	 * Create the pool क्रम driver निजी shared memory
	 */
	rc = tee_shm_pool_mgr_alloc_res_mem(priv_info->vaddr, priv_info->paddr,
					    priv_info->size,
					    3 /* 8 byte aligned */);
	अगर (IS_ERR(rc))
		वापस rc;
	priv_mgr = rc;

	/*
	 * Create the pool क्रम dma_buf shared memory
	 */
	rc = tee_shm_pool_mgr_alloc_res_mem(dmabuf_info->vaddr,
					    dmabuf_info->paddr,
					    dmabuf_info->size, PAGE_SHIFT);
	अगर (IS_ERR(rc))
		जाओ err_मुक्त_priv_mgr;
	dmabuf_mgr = rc;

	rc = tee_shm_pool_alloc(priv_mgr, dmabuf_mgr);
	अगर (IS_ERR(rc))
		जाओ err_मुक्त_dmabuf_mgr;

	वापस rc;

err_मुक्त_dmabuf_mgr:
	tee_shm_pool_mgr_destroy(dmabuf_mgr);
err_मुक्त_priv_mgr:
	tee_shm_pool_mgr_destroy(priv_mgr);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_pool_alloc_res_mem);

काष्ठा tee_shm_pool_mgr *tee_shm_pool_mgr_alloc_res_mem(अचिन्हित दीर्घ vaddr,
							phys_addr_t paddr,
							माप_प्रकार size,
							पूर्णांक min_alloc_order)
अणु
	स्थिर माप_प्रकार page_mask = PAGE_SIZE - 1;
	काष्ठा tee_shm_pool_mgr *mgr;
	पूर्णांक rc;

	/* Start and end must be page aligned */
	अगर (vaddr & page_mask || paddr & page_mask || size & page_mask)
		वापस ERR_PTR(-EINVAL);

	mgr = kzalloc(माप(*mgr), GFP_KERNEL);
	अगर (!mgr)
		वापस ERR_PTR(-ENOMEM);

	mgr->निजी_data = gen_pool_create(min_alloc_order, -1);
	अगर (!mgr->निजी_data) अणु
		rc = -ENOMEM;
		जाओ err;
	पूर्ण

	gen_pool_set_algo(mgr->निजी_data, gen_pool_best_fit, शून्य);
	rc = gen_pool_add_virt(mgr->निजी_data, vaddr, paddr, size, -1);
	अगर (rc) अणु
		gen_pool_destroy(mgr->निजी_data);
		जाओ err;
	पूर्ण

	mgr->ops = &pool_ops_generic;

	वापस mgr;
err:
	kमुक्त(mgr);

	वापस ERR_PTR(rc);
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_pool_mgr_alloc_res_mem);

अटल bool check_mgr_ops(काष्ठा tee_shm_pool_mgr *mgr)
अणु
	वापस mgr && mgr->ops && mgr->ops->alloc && mgr->ops->मुक्त &&
		mgr->ops->destroy_poolmgr;
पूर्ण

काष्ठा tee_shm_pool *tee_shm_pool_alloc(काष्ठा tee_shm_pool_mgr *priv_mgr,
					काष्ठा tee_shm_pool_mgr *dmabuf_mgr)
अणु
	काष्ठा tee_shm_pool *pool;

	अगर (!check_mgr_ops(priv_mgr) || !check_mgr_ops(dmabuf_mgr))
		वापस ERR_PTR(-EINVAL);

	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस ERR_PTR(-ENOMEM);

	pool->निजी_mgr = priv_mgr;
	pool->dma_buf_mgr = dmabuf_mgr;

	वापस pool;
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_pool_alloc);

/**
 * tee_shm_pool_मुक्त() - Free a shared memory pool
 * @pool:	The shared memory pool to मुक्त
 *
 * There must be no reमुख्यing shared memory allocated from this pool when
 * this function is called.
 */
व्योम tee_shm_pool_मुक्त(काष्ठा tee_shm_pool *pool)
अणु
	अगर (pool->निजी_mgr)
		tee_shm_pool_mgr_destroy(pool->निजी_mgr);
	अगर (pool->dma_buf_mgr)
		tee_shm_pool_mgr_destroy(pool->dma_buf_mgr);
	kमुक्त(pool);
पूर्ण
EXPORT_SYMBOL_GPL(tee_shm_pool_मुक्त);
