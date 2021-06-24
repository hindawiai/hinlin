<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 */

#समावेश <linux/slab.h>
#समावेश <linux/tee_drv.h>
#समावेश <linux/psp-sev.h>
#समावेश "amdtee_private.h"

अटल पूर्णांक pool_op_alloc(काष्ठा tee_shm_pool_mgr *poolm, काष्ठा tee_shm *shm,
			 माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक order = get_order(size);
	अचिन्हित दीर्घ va;
	पूर्णांक rc;

	va = __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, order);
	अगर (!va)
		वापस -ENOMEM;

	shm->kaddr = (व्योम *)va;
	shm->paddr = __psp_pa((व्योम *)va);
	shm->size = PAGE_SIZE << order;

	/* Map the allocated memory in to TEE */
	rc = amdtee_map_shmem(shm);
	अगर (rc) अणु
		मुक्त_pages(va, order);
		shm->kaddr = शून्य;
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pool_op_मुक्त(काष्ठा tee_shm_pool_mgr *poolm, काष्ठा tee_shm *shm)
अणु
	/* Unmap the shared memory from TEE */
	amdtee_unmap_shmem(shm);
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

अटल काष्ठा tee_shm_pool_mgr *pool_mem_mgr_alloc(व्योम)
अणु
	काष्ठा tee_shm_pool_mgr *mgr = kzalloc(माप(*mgr), GFP_KERNEL);

	अगर (!mgr)
		वापस ERR_PTR(-ENOMEM);

	mgr->ops = &pool_ops;

	वापस mgr;
पूर्ण

काष्ठा tee_shm_pool *amdtee_config_shm(व्योम)
अणु
	काष्ठा tee_shm_pool_mgr *priv_mgr;
	काष्ठा tee_shm_pool_mgr *dmabuf_mgr;
	व्योम *rc;

	rc = pool_mem_mgr_alloc();
	अगर (IS_ERR(rc))
		वापस rc;
	priv_mgr = rc;

	rc = pool_mem_mgr_alloc();
	अगर (IS_ERR(rc)) अणु
		tee_shm_pool_mgr_destroy(priv_mgr);
		वापस rc;
	पूर्ण
	dmabuf_mgr = rc;

	rc = tee_shm_pool_alloc(priv_mgr, dmabuf_mgr);
	अगर (IS_ERR(rc)) अणु
		tee_shm_pool_mgr_destroy(priv_mgr);
		tee_shm_pool_mgr_destroy(dmabuf_mgr);
	पूर्ण

	वापस rc;
पूर्ण
