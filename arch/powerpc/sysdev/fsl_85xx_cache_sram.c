<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2009-2010 Freescale Semiconductor, Inc.
 *
 * Simple memory allocator असलtraction क्रम QorIQ (P1/P2) based Cache-SRAM
 *
 * Author: Vivek Mahajan <vivek.mahajan@मुक्तscale.com>
 *
 * This file is derived from the original work करोne
 * by Sylvain Munaut क्रम the Bestcomm SRAM allocator.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/fsl_85xx_cache_sram.h>

#समावेश "fsl_85xx_cache_ctlr.h"

काष्ठा mpc85xx_cache_sram *cache_sram;

व्योम *mpc85xx_cache_sram_alloc(अचिन्हित पूर्णांक size,
				phys_addr_t *phys, अचिन्हित पूर्णांक align)
अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(cache_sram == शून्य))
		वापस शून्य;

	अगर (!size || (size > cache_sram->size) || (align > cache_sram->size)) अणु
		pr_err("%s(): size(=%x) or align(=%x) zero or too big\n",
			__func__, size, align);
		वापस शून्य;
	पूर्ण

	अगर ((align & (align - 1)) || align <= 1) अणु
		pr_err("%s(): align(=%x) must be power of two and >1\n",
			__func__, align);
		वापस शून्य;
	पूर्ण

	spin_lock_irqsave(&cache_sram->lock, flags);
	offset = rh_alloc_align(cache_sram->rh, size, align, शून्य);
	spin_unlock_irqrestore(&cache_sram->lock, flags);

	अगर (IS_ERR_VALUE(offset))
		वापस शून्य;

	*phys = cache_sram->base_phys + offset;

	वापस (अचिन्हित अक्षर *)cache_sram->base_virt + offset;
पूर्ण
EXPORT_SYMBOL(mpc85xx_cache_sram_alloc);

व्योम mpc85xx_cache_sram_मुक्त(व्योम *ptr)
अणु
	अचिन्हित दीर्घ flags;
	BUG_ON(!ptr);

	spin_lock_irqsave(&cache_sram->lock, flags);
	rh_मुक्त(cache_sram->rh, ptr - cache_sram->base_virt);
	spin_unlock_irqrestore(&cache_sram->lock, flags);
पूर्ण
EXPORT_SYMBOL(mpc85xx_cache_sram_मुक्त);

पूर्णांक __init instantiate_cache_sram(काष्ठा platक्रमm_device *dev,
		काष्ठा sram_parameters sram_params)
अणु
	पूर्णांक ret = 0;

	अगर (cache_sram) अणु
		dev_err(&dev->dev, "Already initialized cache-sram\n");
		वापस -EBUSY;
	पूर्ण

	cache_sram = kzalloc(माप(काष्ठा mpc85xx_cache_sram), GFP_KERNEL);
	अगर (!cache_sram) अणु
		dev_err(&dev->dev, "Out of memory for cache_sram structure\n");
		वापस -ENOMEM;
	पूर्ण

	cache_sram->base_phys = sram_params.sram_offset;
	cache_sram->size = sram_params.sram_size;

	अगर (!request_mem_region(cache_sram->base_phys, cache_sram->size,
						"fsl_85xx_cache_sram")) अणु
		dev_err(&dev->dev, "%pOF: request memory failed\n",
				dev->dev.of_node);
		ret = -ENXIO;
		जाओ out_मुक्त;
	पूर्ण

	cache_sram->base_virt = ioremap_coherent(cache_sram->base_phys,
						 cache_sram->size);
	अगर (!cache_sram->base_virt) अणु
		dev_err(&dev->dev, "%pOF: ioremap_coherent failed\n",
			dev->dev.of_node);
		ret = -ENOMEM;
		जाओ out_release;
	पूर्ण

	cache_sram->rh = rh_create(माप(अचिन्हित पूर्णांक));
	अगर (IS_ERR(cache_sram->rh)) अणु
		dev_err(&dev->dev, "%pOF: Unable to create remote heap\n",
				dev->dev.of_node);
		ret = PTR_ERR(cache_sram->rh);
		जाओ out_unmap;
	पूर्ण

	rh_attach_region(cache_sram->rh, 0, cache_sram->size);
	spin_lock_init(&cache_sram->lock);

	dev_info(&dev->dev, "[base:0x%llx, size:0x%x] configured and loaded\n",
		(अचिन्हित दीर्घ दीर्घ)cache_sram->base_phys, cache_sram->size);

	वापस 0;

out_unmap:
	iounmap(cache_sram->base_virt);

out_release:
	release_mem_region(cache_sram->base_phys, cache_sram->size);

out_मुक्त:
	kमुक्त(cache_sram);
	वापस ret;
पूर्ण

व्योम हटाओ_cache_sram(काष्ठा platक्रमm_device *dev)
अणु
	BUG_ON(!cache_sram);

	rh_detach_region(cache_sram->rh, 0, cache_sram->size);
	rh_destroy(cache_sram->rh);

	iounmap(cache_sram->base_virt);
	release_mem_region(cache_sram->base_phys, cache_sram->size);

	kमुक्त(cache_sram);
	cache_sram = शून्य;

	dev_info(&dev->dev, "MPC85xx Cache-SRAM driver unloaded\n");
पूर्ण
