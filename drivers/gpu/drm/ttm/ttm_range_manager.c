<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright (c) 2007-2010 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 */

#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <drm/drm_mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>

/*
 * Currently we use a spinlock क्रम the lock, but a mutex *may* be
 * more appropriate to reduce scheduling latency अगर the range manager
 * ends up with very fragmented allocation patterns.
 */

काष्ठा tपंचांग_range_manager अणु
	काष्ठा tपंचांग_resource_manager manager;
	काष्ठा drm_mm mm;
	spinlock_t lock;
पूर्ण;

अटल अंतरभूत काष्ठा tपंचांग_range_manager *to_range_manager(काष्ठा tपंचांग_resource_manager *man)
अणु
	वापस container_of(man, काष्ठा tपंचांग_range_manager, manager);
पूर्ण

अटल पूर्णांक tपंचांग_range_man_alloc(काष्ठा tपंचांग_resource_manager *man,
			       काष्ठा tपंचांग_buffer_object *bo,
			       स्थिर काष्ठा tपंचांग_place *place,
			       काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा tपंचांग_range_manager *rman = to_range_manager(man);
	काष्ठा drm_mm *mm = &rman->mm;
	काष्ठा drm_mm_node *node;
	क्रमागत drm_mm_insert_mode mode;
	अचिन्हित दीर्घ lpfn;
	पूर्णांक ret;

	lpfn = place->lpfn;
	अगर (!lpfn)
		lpfn = man->size;

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	mode = DRM_MM_INSERT_BEST;
	अगर (place->flags & TTM_PL_FLAG_TOPDOWN)
		mode = DRM_MM_INSERT_HIGH;

	spin_lock(&rman->lock);
	ret = drm_mm_insert_node_in_range(mm, node,
					  mem->num_pages,
					  mem->page_alignment, 0,
					  place->fpfn, lpfn, mode);
	spin_unlock(&rman->lock);

	अगर (unlikely(ret)) अणु
		kमुक्त(node);
	पूर्ण अन्यथा अणु
		mem->mm_node = node;
		mem->start = node->start;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम tपंचांग_range_man_मुक्त(काष्ठा tपंचांग_resource_manager *man,
			       काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा tपंचांग_range_manager *rman = to_range_manager(man);

	अगर (mem->mm_node) अणु
		spin_lock(&rman->lock);
		drm_mm_हटाओ_node(mem->mm_node);
		spin_unlock(&rman->lock);

		kमुक्त(mem->mm_node);
		mem->mm_node = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tपंचांग_resource_manager_func tपंचांग_range_manager_func;

पूर्णांक tपंचांग_range_man_init(काष्ठा tपंचांग_device *bdev,
		       अचिन्हित type, bool use_tt,
		       अचिन्हित दीर्घ p_size)
अणु
	काष्ठा tपंचांग_resource_manager *man;
	काष्ठा tपंचांग_range_manager *rman;

	rman = kzalloc(माप(*rman), GFP_KERNEL);
	अगर (!rman)
		वापस -ENOMEM;

	man = &rman->manager;
	man->use_tt = use_tt;

	man->func = &tपंचांग_range_manager_func;

	tपंचांग_resource_manager_init(man, p_size);

	drm_mm_init(&rman->mm, 0, p_size);
	spin_lock_init(&rman->lock);

	tपंचांग_set_driver_manager(bdev, type, &rman->manager);
	tपंचांग_resource_manager_set_used(man, true);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_range_man_init);

पूर्णांक tपंचांग_range_man_fini(काष्ठा tपंचांग_device *bdev,
		       अचिन्हित type)
अणु
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(bdev, type);
	काष्ठा tपंचांग_range_manager *rman = to_range_manager(man);
	काष्ठा drm_mm *mm = &rman->mm;
	पूर्णांक ret;

	tपंचांग_resource_manager_set_used(man, false);

	ret = tपंचांग_resource_manager_evict_all(bdev, man);
	अगर (ret)
		वापस ret;

	spin_lock(&rman->lock);
	drm_mm_clean(mm);
	drm_mm_takeकरोwn(mm);
	spin_unlock(&rman->lock);

	tपंचांग_resource_manager_cleanup(man);
	tपंचांग_set_driver_manager(bdev, type, शून्य);
	kमुक्त(rman);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_range_man_fini);

अटल व्योम tपंचांग_range_man_debug(काष्ठा tपंचांग_resource_manager *man,
				काष्ठा drm_prपूर्णांकer *prपूर्णांकer)
अणु
	काष्ठा tपंचांग_range_manager *rman = to_range_manager(man);

	spin_lock(&rman->lock);
	drm_mm_prपूर्णांक(&rman->mm, prपूर्णांकer);
	spin_unlock(&rman->lock);
पूर्ण

अटल स्थिर काष्ठा tपंचांग_resource_manager_func tपंचांग_range_manager_func = अणु
	.alloc = tपंचांग_range_man_alloc,
	.मुक्त = tपंचांग_range_man_मुक्त,
	.debug = tपंचांग_range_man_debug
पूर्ण;
