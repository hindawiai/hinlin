<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* TI K3 CPPI5 descriptors pool API
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/kernel.h>

#समावेश "k3-cppi-desc-pool.h"

काष्ठा k3_cppi_desc_pool अणु
	काष्ठा device		*dev;
	dma_addr_t		dma_addr;
	व्योम			*cpumem;	/* dma_alloc map */
	माप_प्रकार			desc_size;
	माप_प्रकार			mem_size;
	माप_प्रकार			num_desc;
	काष्ठा gen_pool		*gen_pool;
पूर्ण;

व्योम k3_cppi_desc_pool_destroy(काष्ठा k3_cppi_desc_pool *pool)
अणु
	अगर (!pool)
		वापस;

	WARN(gen_pool_size(pool->gen_pool) != gen_pool_avail(pool->gen_pool),
	     "k3_knav_desc_pool size %zu != avail %zu",
	     gen_pool_size(pool->gen_pool),
	     gen_pool_avail(pool->gen_pool));
	अगर (pool->cpumem)
		dma_मुक्त_coherent(pool->dev, pool->mem_size, pool->cpumem,
				  pool->dma_addr);

	gen_pool_destroy(pool->gen_pool);	/* मुक्तs pool->name */
पूर्ण

काष्ठा k3_cppi_desc_pool *
k3_cppi_desc_pool_create_name(काष्ठा device *dev, माप_प्रकार size,
			      माप_प्रकार desc_size,
			      स्थिर अक्षर *name)
अणु
	काष्ठा k3_cppi_desc_pool *pool;
	स्थिर अक्षर *pool_name = शून्य;
	पूर्णांक ret = -ENOMEM;

	pool = devm_kzalloc(dev, माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस ERR_PTR(ret);

	pool->dev = dev;
	pool->desc_size	= roundup_घात_of_two(desc_size);
	pool->num_desc	= size;
	pool->mem_size	= pool->num_desc * pool->desc_size;

	pool_name = kstrdup_स्थिर(name ? name : dev_name(pool->dev),
				  GFP_KERNEL);
	अगर (!pool_name)
		वापस ERR_PTR(-ENOMEM);

	pool->gen_pool = gen_pool_create(ilog2(pool->desc_size), -1);
	अगर (!pool->gen_pool) अणु
		ret = -ENOMEM;
		dev_err(pool->dev, "pool create failed %d\n", ret);
		kमुक्त_स्थिर(pool_name);
		जाओ gen_pool_create_fail;
	पूर्ण

	pool->gen_pool->name = pool_name;

	pool->cpumem = dma_alloc_coherent(pool->dev, pool->mem_size,
					  &pool->dma_addr, GFP_KERNEL);

	अगर (!pool->cpumem)
		जाओ dma_alloc_fail;

	ret = gen_pool_add_virt(pool->gen_pool, (अचिन्हित दीर्घ)pool->cpumem,
				(phys_addr_t)pool->dma_addr, pool->mem_size,
				-1);
	अगर (ret < 0) अणु
		dev_err(pool->dev, "pool add failed %d\n", ret);
		जाओ gen_pool_add_virt_fail;
	पूर्ण

	वापस pool;

gen_pool_add_virt_fail:
	dma_मुक्त_coherent(pool->dev, pool->mem_size, pool->cpumem,
			  pool->dma_addr);
dma_alloc_fail:
	gen_pool_destroy(pool->gen_pool);	/* मुक्तs pool->name */
gen_pool_create_fail:
	devm_kमुक्त(pool->dev, pool);
	वापस ERR_PTR(ret);
पूर्ण

dma_addr_t k3_cppi_desc_pool_virt2dma(काष्ठा k3_cppi_desc_pool *pool,
				      व्योम *addr)
अणु
	वापस addr ? pool->dma_addr + (addr - pool->cpumem) : 0;
पूर्ण

व्योम *k3_cppi_desc_pool_dma2virt(काष्ठा k3_cppi_desc_pool *pool, dma_addr_t dma)
अणु
	वापस dma ? pool->cpumem + (dma - pool->dma_addr) : शून्य;
पूर्ण

व्योम *k3_cppi_desc_pool_alloc(काष्ठा k3_cppi_desc_pool *pool)
अणु
	वापस (व्योम *)gen_pool_alloc(pool->gen_pool, pool->desc_size);
पूर्ण

व्योम k3_cppi_desc_pool_मुक्त(काष्ठा k3_cppi_desc_pool *pool, व्योम *addr)
अणु
	gen_pool_मुक्त(pool->gen_pool, (अचिन्हित दीर्घ)addr, pool->desc_size);
पूर्ण

माप_प्रकार k3_cppi_desc_pool_avail(काष्ठा k3_cppi_desc_pool *pool)
अणु
	वापस gen_pool_avail(pool->gen_pool) / pool->desc_size;
पूर्ण
