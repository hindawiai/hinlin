<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2007-2010 VMware, Inc., Palo Alto, CA., USA
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

#समावेश "vmwgfx_drv.h"
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <linux/idr.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>

काष्ठा vmwgfx_gmrid_man अणु
	काष्ठा tपंचांग_resource_manager manager;
	spinlock_t lock;
	काष्ठा ida gmr_ida;
	uपूर्णांक32_t max_gmr_ids;
	uपूर्णांक32_t max_gmr_pages;
	uपूर्णांक32_t used_gmr_pages;
पूर्ण;

अटल काष्ठा vmwgfx_gmrid_man *to_gmrid_manager(काष्ठा tपंचांग_resource_manager *man)
अणु
	वापस container_of(man, काष्ठा vmwgfx_gmrid_man, manager);
पूर्ण

अटल पूर्णांक vmw_gmrid_man_get_node(काष्ठा tपंचांग_resource_manager *man,
				  काष्ठा tपंचांग_buffer_object *bo,
				  स्थिर काष्ठा tपंचांग_place *place,
				  काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा vmwgfx_gmrid_man *gman = to_gmrid_manager(man);
	पूर्णांक id;

	id = ida_alloc_max(&gman->gmr_ida, gman->max_gmr_ids - 1, GFP_KERNEL);
	अगर (id < 0)
		वापस id;

	spin_lock(&gman->lock);

	अगर (gman->max_gmr_pages > 0) अणु
		gman->used_gmr_pages += mem->num_pages;
		अगर (unlikely(gman->used_gmr_pages > gman->max_gmr_pages))
			जाओ nospace;
	पूर्ण

	mem->mm_node = gman;
	mem->start = id;

	spin_unlock(&gman->lock);
	वापस 0;

nospace:
	gman->used_gmr_pages -= mem->num_pages;
	spin_unlock(&gman->lock);
	ida_मुक्त(&gman->gmr_ida, id);
	वापस -ENOSPC;
पूर्ण

अटल व्योम vmw_gmrid_man_put_node(काष्ठा tपंचांग_resource_manager *man,
				   काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा vmwgfx_gmrid_man *gman = to_gmrid_manager(man);

	अगर (mem->mm_node) अणु
		ida_मुक्त(&gman->gmr_ida, mem->start);
		spin_lock(&gman->lock);
		gman->used_gmr_pages -= mem->num_pages;
		spin_unlock(&gman->lock);
		mem->mm_node = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा tपंचांग_resource_manager_func vmw_gmrid_manager_func;

पूर्णांक vmw_gmrid_man_init(काष्ठा vmw_निजी *dev_priv, पूर्णांक type)
अणु
	काष्ठा tपंचांग_resource_manager *man;
	काष्ठा vmwgfx_gmrid_man *gman =
		kzalloc(माप(*gman), GFP_KERNEL);

	अगर (unlikely(!gman))
		वापस -ENOMEM;

	man = &gman->manager;

	man->func = &vmw_gmrid_manager_func;
	/* TODO: This is most likely not correct */
	man->use_tt = true;
	tपंचांग_resource_manager_init(man, 0);
	spin_lock_init(&gman->lock);
	gman->used_gmr_pages = 0;
	ida_init(&gman->gmr_ida);

	चयन (type) अणु
	हाल VMW_PL_GMR:
		gman->max_gmr_ids = dev_priv->max_gmr_ids;
		gman->max_gmr_pages = dev_priv->max_gmr_pages;
		अवरोध;
	हाल VMW_PL_MOB:
		gman->max_gmr_ids = VMWGFX_NUM_MOB;
		gman->max_gmr_pages = dev_priv->max_mob_pages;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	tपंचांग_set_driver_manager(&dev_priv->bdev, type, &gman->manager);
	tपंचांग_resource_manager_set_used(man, true);
	वापस 0;
पूर्ण

व्योम vmw_gmrid_man_fini(काष्ठा vmw_निजी *dev_priv, पूर्णांक type)
अणु
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&dev_priv->bdev, type);
	काष्ठा vmwgfx_gmrid_man *gman = to_gmrid_manager(man);

	tपंचांग_resource_manager_set_used(man, false);

	tपंचांग_resource_manager_evict_all(&dev_priv->bdev, man);

	tपंचांग_resource_manager_cleanup(man);

	tपंचांग_set_driver_manager(&dev_priv->bdev, type, शून्य);
	ida_destroy(&gman->gmr_ida);
	kमुक्त(gman);

पूर्ण

अटल स्थिर काष्ठा tपंचांग_resource_manager_func vmw_gmrid_manager_func = अणु
	.alloc = vmw_gmrid_man_get_node,
	.मुक्त = vmw_gmrid_man_put_node,
पूर्ण;
