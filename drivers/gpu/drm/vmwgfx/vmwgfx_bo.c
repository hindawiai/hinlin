<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright तऊ 2011-2018 VMware, Inc., Palo Alto, CA., USA
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

#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "vmwgfx_drv.h"
#समावेश "ttm_object.h"


/**
 * काष्ठा vmw_user_buffer_object - User-space-visible buffer object
 *
 * @prime: The prime object providing user visibility.
 * @vbo: The काष्ठा vmw_buffer_object
 */
काष्ठा vmw_user_buffer_object अणु
	काष्ठा tपंचांग_prime_object prime;
	काष्ठा vmw_buffer_object vbo;
पूर्ण;


/**
 * vmw_buffer_object - Convert a काष्ठा tपंचांग_buffer_object to a काष्ठा
 * vmw_buffer_object.
 *
 * @bo: Poपूर्णांकer to the TTM buffer object.
 * Return: Poपूर्णांकer to the काष्ठा vmw_buffer_object embedding the
 * TTM buffer object.
 */
अटल काष्ठा vmw_buffer_object *
vmw_buffer_object(काष्ठा tपंचांग_buffer_object *bo)
अणु
	वापस container_of(bo, काष्ठा vmw_buffer_object, base);
पूर्ण


/**
 * vmw_user_buffer_object - Convert a काष्ठा tपंचांग_buffer_object to a काष्ठा
 * vmw_user_buffer_object.
 *
 * @bo: Poपूर्णांकer to the TTM buffer object.
 * Return: Poपूर्णांकer to the काष्ठा vmw_buffer_object embedding the TTM buffer
 * object.
 */
अटल काष्ठा vmw_user_buffer_object *
vmw_user_buffer_object(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा vmw_buffer_object *vmw_bo = vmw_buffer_object(bo);

	वापस container_of(vmw_bo, काष्ठा vmw_user_buffer_object, vbo);
पूर्ण


/**
 * vmw_bo_pin_in_placement - Validate a buffer to placement.
 *
 * @dev_priv:  Driver निजी.
 * @buf:  DMA buffer to move.
 * @placement:  The placement to pin it.
 * @पूर्णांकerruptible:  Use पूर्णांकerruptible रुको.
 * Return: Zero on success, Negative error code on failure. In particular
 * -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत
 */
पूर्णांक vmw_bo_pin_in_placement(काष्ठा vmw_निजी *dev_priv,
			    काष्ठा vmw_buffer_object *buf,
			    काष्ठा tपंचांग_placement *placement,
			    bool पूर्णांकerruptible)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणुपूर्णांकerruptible, false पूर्ण;
	काष्ठा tपंचांग_buffer_object *bo = &buf->base;
	पूर्णांक ret;
	uपूर्णांक32_t new_flags;

	ret = tपंचांग_ग_लिखो_lock(&dev_priv->reservation_sem, पूर्णांकerruptible);
	अगर (unlikely(ret != 0))
		वापस ret;

	vmw_execbuf_release_pinned_bo(dev_priv);

	ret = tपंचांग_bo_reserve(bo, पूर्णांकerruptible, false, शून्य);
	अगर (unlikely(ret != 0))
		जाओ err;

	अगर (buf->base.pin_count > 0)
		ret = tपंचांग_bo_mem_compat(placement, &bo->mem,
					&new_flags) == true ? 0 : -EINVAL;
	अन्यथा
		ret = tपंचांग_bo_validate(bo, placement, &ctx);

	अगर (!ret)
		vmw_bo_pin_reserved(buf, true);

	tपंचांग_bo_unreserve(bo);

err:
	tपंचांग_ग_लिखो_unlock(&dev_priv->reservation_sem);
	वापस ret;
पूर्ण


/**
 * vmw_bo_pin_in_vram_or_gmr - Move a buffer to vram or gmr.
 *
 * This function takes the reservation_sem in ग_लिखो mode.
 * Flushes and unpins the query bo to aव्योम failures.
 *
 * @dev_priv:  Driver निजी.
 * @buf:  DMA buffer to move.
 * @पूर्णांकerruptible:  Use पूर्णांकerruptible रुको.
 * Return: Zero on success, Negative error code on failure. In particular
 * -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत
 */
पूर्णांक vmw_bo_pin_in_vram_or_gmr(काष्ठा vmw_निजी *dev_priv,
			      काष्ठा vmw_buffer_object *buf,
			      bool पूर्णांकerruptible)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणुपूर्णांकerruptible, false पूर्ण;
	काष्ठा tपंचांग_buffer_object *bo = &buf->base;
	पूर्णांक ret;
	uपूर्णांक32_t new_flags;

	ret = tपंचांग_ग_लिखो_lock(&dev_priv->reservation_sem, पूर्णांकerruptible);
	अगर (unlikely(ret != 0))
		वापस ret;

	vmw_execbuf_release_pinned_bo(dev_priv);

	ret = tपंचांग_bo_reserve(bo, पूर्णांकerruptible, false, शून्य);
	अगर (unlikely(ret != 0))
		जाओ err;

	अगर (buf->base.pin_count > 0) अणु
		ret = tपंचांग_bo_mem_compat(&vmw_vram_gmr_placement, &bo->mem,
					&new_flags) == true ? 0 : -EINVAL;
		जाओ out_unreserve;
	पूर्ण

	ret = tपंचांग_bo_validate(bo, &vmw_vram_gmr_placement, &ctx);
	अगर (likely(ret == 0) || ret == -ERESTARTSYS)
		जाओ out_unreserve;

	ret = tपंचांग_bo_validate(bo, &vmw_vram_placement, &ctx);

out_unreserve:
	अगर (!ret)
		vmw_bo_pin_reserved(buf, true);

	tपंचांग_bo_unreserve(bo);
err:
	tपंचांग_ग_लिखो_unlock(&dev_priv->reservation_sem);
	वापस ret;
पूर्ण


/**
 * vmw_bo_pin_in_vram - Move a buffer to vram.
 *
 * This function takes the reservation_sem in ग_लिखो mode.
 * Flushes and unpins the query bo to aव्योम failures.
 *
 * @dev_priv:  Driver निजी.
 * @buf:  DMA buffer to move.
 * @पूर्णांकerruptible:  Use पूर्णांकerruptible रुको.
 * Return: Zero on success, Negative error code on failure. In particular
 * -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत
 */
पूर्णांक vmw_bo_pin_in_vram(काष्ठा vmw_निजी *dev_priv,
		       काष्ठा vmw_buffer_object *buf,
		       bool पूर्णांकerruptible)
अणु
	वापस vmw_bo_pin_in_placement(dev_priv, buf, &vmw_vram_placement,
				       पूर्णांकerruptible);
पूर्ण


/**
 * vmw_bo_pin_in_start_of_vram - Move a buffer to start of vram.
 *
 * This function takes the reservation_sem in ग_लिखो mode.
 * Flushes and unpins the query bo to aव्योम failures.
 *
 * @dev_priv:  Driver निजी.
 * @buf:  DMA buffer to pin.
 * @पूर्णांकerruptible:  Use पूर्णांकerruptible रुको.
 * Return: Zero on success, Negative error code on failure. In particular
 * -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत
 */
पूर्णांक vmw_bo_pin_in_start_of_vram(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_buffer_object *buf,
				bool पूर्णांकerruptible)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणुपूर्णांकerruptible, false पूर्ण;
	काष्ठा tपंचांग_buffer_object *bo = &buf->base;
	काष्ठा tपंचांग_placement placement;
	काष्ठा tपंचांग_place place;
	पूर्णांक ret = 0;
	uपूर्णांक32_t new_flags;

	place = vmw_vram_placement.placement[0];
	place.lpfn = bo->mem.num_pages;
	placement.num_placement = 1;
	placement.placement = &place;
	placement.num_busy_placement = 1;
	placement.busy_placement = &place;

	ret = tपंचांग_ग_लिखो_lock(&dev_priv->reservation_sem, पूर्णांकerruptible);
	अगर (unlikely(ret != 0))
		वापस ret;

	vmw_execbuf_release_pinned_bo(dev_priv);
	ret = tपंचांग_bo_reserve(bo, पूर्णांकerruptible, false, शून्य);
	अगर (unlikely(ret != 0))
		जाओ err_unlock;

	/*
	 * Is this buffer alपढ़ोy in vram but not at the start of it?
	 * In that हाल, evict it first because TTM isn't good at handling
	 * that situation.
	 */
	अगर (bo->mem.mem_type == TTM_PL_VRAM &&
	    bo->mem.start < bo->mem.num_pages &&
	    bo->mem.start > 0 &&
	    buf->base.pin_count == 0) अणु
		ctx.पूर्णांकerruptible = false;
		(व्योम) tपंचांग_bo_validate(bo, &vmw_sys_placement, &ctx);
	पूर्ण

	अगर (buf->base.pin_count > 0)
		ret = tपंचांग_bo_mem_compat(&placement, &bo->mem,
					&new_flags) == true ? 0 : -EINVAL;
	अन्यथा
		ret = tपंचांग_bo_validate(bo, &placement, &ctx);

	/* For some reason we didn't end up at the start of vram */
	WARN_ON(ret == 0 && bo->mem.start != 0);
	अगर (!ret)
		vmw_bo_pin_reserved(buf, true);

	tपंचांग_bo_unreserve(bo);
err_unlock:
	tपंचांग_ग_लिखो_unlock(&dev_priv->reservation_sem);

	वापस ret;
पूर्ण


/**
 * vmw_bo_unpin - Unpin the buffer given buffer, करोes not move the buffer.
 *
 * This function takes the reservation_sem in ग_लिखो mode.
 *
 * @dev_priv:  Driver निजी.
 * @buf:  DMA buffer to unpin.
 * @पूर्णांकerruptible:  Use पूर्णांकerruptible रुको.
 * Return: Zero on success, Negative error code on failure. In particular
 * -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत
 */
पूर्णांक vmw_bo_unpin(काष्ठा vmw_निजी *dev_priv,
		 काष्ठा vmw_buffer_object *buf,
		 bool पूर्णांकerruptible)
अणु
	काष्ठा tपंचांग_buffer_object *bo = &buf->base;
	पूर्णांक ret;

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, पूर्णांकerruptible);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = tपंचांग_bo_reserve(bo, पूर्णांकerruptible, false, शून्य);
	अगर (unlikely(ret != 0))
		जाओ err;

	vmw_bo_pin_reserved(buf, false);

	tपंचांग_bo_unreserve(bo);

err:
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	वापस ret;
पूर्ण

/**
 * vmw_bo_get_guest_ptr - Get the guest ptr representing the current placement
 * of a buffer.
 *
 * @bo: Poपूर्णांकer to a काष्ठा tपंचांग_buffer_object. Must be pinned or reserved.
 * @ptr: SVGAGuestPtr वापसing the result.
 */
व्योम vmw_bo_get_guest_ptr(स्थिर काष्ठा tपंचांग_buffer_object *bo,
			  SVGAGuestPtr *ptr)
अणु
	अगर (bo->mem.mem_type == TTM_PL_VRAM) अणु
		ptr->gmrId = SVGA_GMR_FRAMEBUFFER;
		ptr->offset = bo->mem.start << PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		ptr->gmrId = bo->mem.start;
		ptr->offset = 0;
	पूर्ण
पूर्ण


/**
 * vmw_bo_pin_reserved - Pin or unpin a buffer object without moving it.
 *
 * @vbo: The buffer object. Must be reserved.
 * @pin: Whether to pin or unpin.
 *
 */
व्योम vmw_bo_pin_reserved(काष्ठा vmw_buffer_object *vbo, bool pin)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, true पूर्ण;
	काष्ठा tपंचांग_place pl;
	काष्ठा tपंचांग_placement placement;
	काष्ठा tपंचांग_buffer_object *bo = &vbo->base;
	uपूर्णांक32_t old_mem_type = bo->mem.mem_type;
	पूर्णांक ret;

	dma_resv_निश्चित_held(bo->base.resv);

	अगर (pin == !!bo->pin_count)
		वापस;

	pl.fpfn = 0;
	pl.lpfn = 0;
	pl.mem_type = bo->mem.mem_type;
	pl.flags = bo->mem.placement;

	स_रखो(&placement, 0, माप(placement));
	placement.num_placement = 1;
	placement.placement = &pl;

	ret = tपंचांग_bo_validate(bo, &placement, &ctx);

	BUG_ON(ret != 0 || bo->mem.mem_type != old_mem_type);

	अगर (pin)
		tपंचांग_bo_pin(bo);
	अन्यथा
		tपंचांग_bo_unpin(bo);
पूर्ण

/**
 * vmw_bo_map_and_cache - Map a buffer object and cache the map
 *
 * @vbo: The buffer object to map
 * Return: A kernel भव address or शून्य अगर mapping failed.
 *
 * This function maps a buffer object पूर्णांकo the kernel address space, or
 * वापसs the भव kernel address of an alपढ़ोy existing map. The भव
 * address reमुख्यs valid as दीर्घ as the buffer object is pinned or reserved.
 * The cached map is torn करोwn on either
 * 1) Buffer object move
 * 2) Buffer object swapout
 * 3) Buffer object deकाष्ठाion
 *
 */
व्योम *vmw_bo_map_and_cache(काष्ठा vmw_buffer_object *vbo)
अणु
	काष्ठा tपंचांग_buffer_object *bo = &vbo->base;
	bool not_used;
	व्योम *भव;
	पूर्णांक ret;

	भव = tपंचांग_kmap_obj_भव(&vbo->map, &not_used);
	अगर (भव)
		वापस भव;

	ret = tपंचांग_bo_kmap(bo, 0, bo->mem.num_pages, &vbo->map);
	अगर (ret)
		DRM_ERROR("Buffer object map failed: %d.\n", ret);

	वापस tपंचांग_kmap_obj_भव(&vbo->map, &not_used);
पूर्ण


/**
 * vmw_bo_unmap - Tear करोwn a cached buffer object map.
 *
 * @vbo: The buffer object whose map we are tearing करोwn.
 *
 * This function tears करोwn a cached map set up using
 * vmw_buffer_object_map_and_cache().
 */
व्योम vmw_bo_unmap(काष्ठा vmw_buffer_object *vbo)
अणु
	अगर (vbo->map.bo == शून्य)
		वापस;

	tपंचांग_bo_kunmap(&vbo->map);
पूर्ण


/**
 * vmw_bo_acc_size - Calculate the pinned memory usage of buffers
 *
 * @dev_priv: Poपूर्णांकer to a काष्ठा vmw_निजी identअगरying the device.
 * @size: The requested buffer size.
 * @user: Whether this is an ordinary dma buffer or a user dma buffer.
 */
अटल माप_प्रकार vmw_bo_acc_size(काष्ठा vmw_निजी *dev_priv, माप_प्रकार size,
			      bool user)
अणु
	अटल माप_प्रकार काष्ठा_size, user_काष्ठा_size;
	माप_प्रकार num_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	माप_प्रकार page_array_size = tपंचांग_round_pot(num_pages * माप(व्योम *));

	अगर (unlikely(काष्ठा_size == 0)) अणु
		माप_प्रकार backend_size = tपंचांग_round_pot(vmw_tt_size);

		काष्ठा_size = backend_size +
			tपंचांग_round_pot(माप(काष्ठा vmw_buffer_object));
		user_काष्ठा_size = backend_size +
		  tपंचांग_round_pot(माप(काष्ठा vmw_user_buffer_object)) +
				      TTM_OBJ_EXTRA_SIZE;
	पूर्ण

	अगर (dev_priv->map_mode == vmw_dma_alloc_coherent)
		page_array_size +=
			tपंचांग_round_pot(num_pages * माप(dma_addr_t));

	वापस ((user) ? user_काष्ठा_size : काष्ठा_size) +
		page_array_size;
पूर्ण


/**
 * vmw_bo_bo_मुक्त - vmw buffer object deकाष्ठाor
 *
 * @bo: Poपूर्णांकer to the embedded काष्ठा tपंचांग_buffer_object
 */
व्योम vmw_bo_bo_मुक्त(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा vmw_buffer_object *vmw_bo = vmw_buffer_object(bo);

	WARN_ON(vmw_bo->dirty);
	WARN_ON(!RB_EMPTY_ROOT(&vmw_bo->res_tree));
	vmw_bo_unmap(vmw_bo);
	kमुक्त(vmw_bo);
पूर्ण


/**
 * vmw_user_bo_destroy - vmw buffer object deकाष्ठाor
 *
 * @bo: Poपूर्णांकer to the embedded काष्ठा tपंचांग_buffer_object
 */
अटल व्योम vmw_user_bo_destroy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा vmw_user_buffer_object *vmw_user_bo = vmw_user_buffer_object(bo);
	काष्ठा vmw_buffer_object *vbo = &vmw_user_bo->vbo;

	WARN_ON(vbo->dirty);
	WARN_ON(!RB_EMPTY_ROOT(&vbo->res_tree));
	vmw_bo_unmap(vbo);
	tपंचांग_prime_object_kमुक्त(vmw_user_bo, prime);
पूर्ण

/**
 * vmw_bo_create_kernel - Create a pinned BO क्रम पूर्णांकernal kernel use.
 *
 * @dev_priv: Poपूर्णांकer to the device निजी काष्ठा
 * @size: size of the BO we need
 * @placement: where to put it
 * @p_bo: resulting BO
 *
 * Creates and pin a simple BO क्रम in kernel use.
 */
पूर्णांक vmw_bo_create_kernel(काष्ठा vmw_निजी *dev_priv, अचिन्हित दीर्घ size,
			 काष्ठा tपंचांग_placement *placement,
			 काष्ठा tपंचांग_buffer_object **p_bo)
अणु
	अचिन्हित npages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा tपंचांग_buffer_object *bo;
	माप_प्रकार acc_size;
	पूर्णांक ret;

	bo = kzalloc(माप(*bo), GFP_KERNEL);
	अगर (unlikely(!bo))
		वापस -ENOMEM;

	acc_size = tपंचांग_round_pot(माप(*bo));
	acc_size += tपंचांग_round_pot(npages * माप(व्योम *));
	acc_size += tपंचांग_round_pot(माप(काष्ठा tपंचांग_tt));

	ret = tपंचांग_mem_global_alloc(&tपंचांग_mem_glob, acc_size, &ctx);
	अगर (unlikely(ret))
		जाओ error_मुक्त;

	ret = tपंचांग_bo_init_reserved(&dev_priv->bdev, bo, size,
				   tपंचांग_bo_type_device, placement, 0,
				   &ctx, शून्य, शून्य, शून्य);
	अगर (unlikely(ret))
		जाओ error_account;

	tपंचांग_bo_pin(bo);
	tपंचांग_bo_unreserve(bo);
	*p_bo = bo;

	वापस 0;

error_account:
	tपंचांग_mem_global_मुक्त(&tपंचांग_mem_glob, acc_size);

error_मुक्त:
	kमुक्त(bo);
	वापस ret;
पूर्ण

/**
 * vmw_bo_init - Initialize a vmw buffer object
 *
 * @dev_priv: Poपूर्णांकer to the device निजी काष्ठा
 * @vmw_bo: Poपूर्णांकer to the काष्ठा vmw_buffer_object to initialize.
 * @size: Buffer object size in bytes.
 * @placement: Initial placement.
 * @पूर्णांकerruptible: Whether रुकोs should be perक्रमmed पूर्णांकerruptible.
 * @pin: If the BO should be created pinned at a fixed location.
 * @bo_मुक्त: The buffer object deकाष्ठाor.
 * Returns: Zero on success, negative error code on error.
 *
 * Note that on error, the code will मुक्त the buffer object.
 */
पूर्णांक vmw_bo_init(काष्ठा vmw_निजी *dev_priv,
		काष्ठा vmw_buffer_object *vmw_bo,
		माप_प्रकार size, काष्ठा tपंचांग_placement *placement,
		bool पूर्णांकerruptible, bool pin,
		व्योम (*bo_मुक्त)(काष्ठा tपंचांग_buffer_object *bo))
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु पूर्णांकerruptible, false पूर्ण;
	काष्ठा tपंचांग_device *bdev = &dev_priv->bdev;
	माप_प्रकार acc_size;
	पूर्णांक ret;
	bool user = (bo_मुक्त == &vmw_user_bo_destroy);

	WARN_ON_ONCE(!bo_मुक्त && (!user && (bo_मुक्त != vmw_bo_bo_मुक्त)));

	acc_size = vmw_bo_acc_size(dev_priv, size, user);
	स_रखो(vmw_bo, 0, माप(*vmw_bo));
	BUILD_BUG_ON(TTM_MAX_BO_PRIORITY <= 3);
	vmw_bo->base.priority = 3;
	vmw_bo->res_tree = RB_ROOT;

	ret = tपंचांग_mem_global_alloc(&tपंचांग_mem_glob, acc_size, &ctx);
	अगर (unlikely(ret))
		वापस ret;

	ret = tपंचांग_bo_init_reserved(bdev, &vmw_bo->base, size,
				   tपंचांग_bo_type_device, placement,
				   0, &ctx, शून्य, शून्य, bo_मुक्त);
	अगर (unlikely(ret)) अणु
		tपंचांग_mem_global_मुक्त(&tपंचांग_mem_glob, acc_size);
		वापस ret;
	पूर्ण

	अगर (pin)
		tपंचांग_bo_pin(&vmw_bo->base);
	tपंचांग_bo_unreserve(&vmw_bo->base);
	वापस 0;
पूर्ण


/**
 * vmw_user_bo_release - TTM reference base object release callback क्रम
 * vmw user buffer objects
 *
 * @p_base: The TTM base object poपूर्णांकer about to be unreferenced.
 *
 * Clears the TTM base object poपूर्णांकer and drops the reference the
 * base object has on the underlying काष्ठा vmw_buffer_object.
 */
अटल व्योम vmw_user_bo_release(काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा vmw_user_buffer_object *vmw_user_bo;
	काष्ठा tपंचांग_base_object *base = *p_base;

	*p_base = शून्य;

	अगर (unlikely(base == शून्य))
		वापस;

	vmw_user_bo = container_of(base, काष्ठा vmw_user_buffer_object,
				   prime.base);
	tपंचांग_bo_put(&vmw_user_bo->vbo.base);
पूर्ण


/**
 * vmw_user_bo_ref_obj-release - TTM synccpu reference object release callback
 * क्रम vmw user buffer objects
 *
 * @base: Poपूर्णांकer to the TTM base object
 * @ref_type: Reference type of the reference reaching zero.
 *
 * Called when user-space drops its last synccpu reference on the buffer
 * object, Either explicitly or as part of a cleanup file बंद.
 */
अटल व्योम vmw_user_bo_ref_obj_release(काष्ठा tपंचांग_base_object *base,
					क्रमागत tपंचांग_ref_type ref_type)
अणु
	काष्ठा vmw_user_buffer_object *user_bo;

	user_bo = container_of(base, काष्ठा vmw_user_buffer_object, prime.base);

	चयन (ref_type) अणु
	हाल TTM_REF_SYNCCPU_WRITE:
		atomic_dec(&user_bo->vbo.cpu_ग_लिखोrs);
		अवरोध;
	शेष:
		WARN_ONCE(true, "Undefined buffer object reference release.\n");
	पूर्ण
पूर्ण


/**
 * vmw_user_bo_alloc - Allocate a user buffer object
 *
 * @dev_priv: Poपूर्णांकer to a काष्ठा device निजी.
 * @tfile: Poपूर्णांकer to a काष्ठा tपंचांग_object_file on which to रेजिस्टर the user
 * object.
 * @size: Size of the buffer object.
 * @shareable: Boolean whether the buffer is shareable with other खोलो files.
 * @handle: Poपूर्णांकer to where the handle value should be asचिन्हित.
 * @p_vbo: Poपूर्णांकer to where the refcounted काष्ठा vmw_buffer_object poपूर्णांकer
 * should be asचिन्हित.
 * @p_base: The TTM base object poपूर्णांकer about to be allocated.
 * Return: Zero on success, negative error code on error.
 */
पूर्णांक vmw_user_bo_alloc(काष्ठा vmw_निजी *dev_priv,
		      काष्ठा tपंचांग_object_file *tfile,
		      uपूर्णांक32_t size,
		      bool shareable,
		      uपूर्णांक32_t *handle,
		      काष्ठा vmw_buffer_object **p_vbo,
		      काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा vmw_user_buffer_object *user_bo;
	पूर्णांक ret;

	user_bo = kzalloc(माप(*user_bo), GFP_KERNEL);
	अगर (unlikely(!user_bo)) अणु
		DRM_ERROR("Failed to allocate a buffer.\n");
		वापस -ENOMEM;
	पूर्ण

	ret = vmw_bo_init(dev_priv, &user_bo->vbo, size,
			  (dev_priv->has_mob) ?
			  &vmw_sys_placement :
			  &vmw_vram_sys_placement, true, false,
			  &vmw_user_bo_destroy);
	अगर (unlikely(ret != 0))
		वापस ret;

	tपंचांग_bo_get(&user_bo->vbo.base);
	ret = tपंचांग_prime_object_init(tfile,
				    size,
				    &user_bo->prime,
				    shareable,
				    tपंचांग_buffer_type,
				    &vmw_user_bo_release,
				    &vmw_user_bo_ref_obj_release);
	अगर (unlikely(ret != 0)) अणु
		tपंचांग_bo_put(&user_bo->vbo.base);
		जाओ out_no_base_object;
	पूर्ण

	*p_vbo = &user_bo->vbo;
	अगर (p_base) अणु
		*p_base = &user_bo->prime.base;
		kref_get(&(*p_base)->refcount);
	पूर्ण
	*handle = user_bo->prime.base.handle;

out_no_base_object:
	वापस ret;
पूर्ण


/**
 * vmw_user_bo_verअगरy_access - verअगरy access permissions on this
 * buffer object.
 *
 * @bo: Poपूर्णांकer to the buffer object being accessed
 * @tfile: Identअगरying the caller.
 */
पूर्णांक vmw_user_bo_verअगरy_access(काष्ठा tपंचांग_buffer_object *bo,
			      काष्ठा tपंचांग_object_file *tfile)
अणु
	काष्ठा vmw_user_buffer_object *vmw_user_bo;

	अगर (unlikely(bo->destroy != vmw_user_bo_destroy))
		वापस -EPERM;

	vmw_user_bo = vmw_user_buffer_object(bo);

	/* Check that the caller has खोलोed the object. */
	अगर (likely(tपंचांग_ref_object_exists(tfile, &vmw_user_bo->prime.base)))
		वापस 0;

	DRM_ERROR("Could not grant buffer access.\n");
	वापस -EPERM;
पूर्ण


/**
 * vmw_user_bo_synccpu_grab - Grab a काष्ठा vmw_user_buffer_object क्रम cpu
 * access, idling previous GPU operations on the buffer and optionally
 * blocking it क्रम further command submissions.
 *
 * @user_bo: Poपूर्णांकer to the buffer object being grabbed क्रम CPU access
 * @tfile: Identअगरying the caller.
 * @flags: Flags indicating how the grab should be perक्रमmed.
 * Return: Zero on success, Negative error code on error. In particular,
 * -EBUSY will be वापसed अगर a करोntblock operation is requested and the
 * buffer object is busy, and -ERESTARTSYS will be वापसed अगर a रुको is
 * पूर्णांकerrupted by a संकेत.
 *
 * A blocking grab will be स्वतःmatically released when @tfile is बंदd.
 */
अटल पूर्णांक vmw_user_bo_synccpu_grab(काष्ठा vmw_user_buffer_object *user_bo,
				    काष्ठा tपंचांग_object_file *tfile,
				    uपूर्णांक32_t flags)
अणु
	bool nonblock = !!(flags & drm_vmw_synccpu_करोntblock);
	काष्ठा tपंचांग_buffer_object *bo = &user_bo->vbo.base;
	bool existed;
	पूर्णांक ret;

	अगर (flags & drm_vmw_synccpu_allow_cs) अणु
		दीर्घ lret;

		lret = dma_resv_रुको_समयout_rcu
			(bo->base.resv, true, true,
			 nonblock ? 0 : MAX_SCHEDULE_TIMEOUT);
		अगर (!lret)
			वापस -EBUSY;
		अन्यथा अगर (lret < 0)
			वापस lret;
		वापस 0;
	पूर्ण

	ret = tपंचांग_bo_reserve(bo, true, nonblock, शून्य);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = tपंचांग_bo_रुको(bo, true, nonblock);
	अगर (likely(ret == 0))
		atomic_inc(&user_bo->vbo.cpu_ग_लिखोrs);

	tपंचांग_bo_unreserve(bo);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = tपंचांग_ref_object_add(tfile, &user_bo->prime.base,
				 TTM_REF_SYNCCPU_WRITE, &existed, false);
	अगर (ret != 0 || existed)
		atomic_dec(&user_bo->vbo.cpu_ग_लिखोrs);

	वापस ret;
पूर्ण

/**
 * vmw_user_bo_synccpu_release - Release a previous grab क्रम CPU access,
 * and unblock command submission on the buffer अगर blocked.
 *
 * @handle: Handle identअगरying the buffer object.
 * @tfile: Identअगरying the caller.
 * @flags: Flags indicating the type of release.
 */
अटल पूर्णांक vmw_user_bo_synccpu_release(uपूर्णांक32_t handle,
					   काष्ठा tपंचांग_object_file *tfile,
					   uपूर्णांक32_t flags)
अणु
	अगर (!(flags & drm_vmw_synccpu_allow_cs))
		वापस tपंचांग_ref_object_base_unref(tfile, handle,
						 TTM_REF_SYNCCPU_WRITE);

	वापस 0;
पूर्ण


/**
 * vmw_user_bo_synccpu_ioctl - ioctl function implementing the synccpu
 * functionality.
 *
 * @dev: Identअगरies the drm device.
 * @data: Poपूर्णांकer to the ioctl argument.
 * @file_priv: Identअगरies the caller.
 * Return: Zero on success, negative error code on error.
 *
 * This function checks the ioctl arguments क्रम validity and calls the
 * relevant synccpu functions.
 */
पूर्णांक vmw_user_bo_synccpu_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_synccpu_arg *arg =
		(काष्ठा drm_vmw_synccpu_arg *) data;
	काष्ठा vmw_buffer_object *vbo;
	काष्ठा vmw_user_buffer_object *user_bo;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा tपंचांग_base_object *buffer_base;
	पूर्णांक ret;

	अगर ((arg->flags & (drm_vmw_synccpu_पढ़ो | drm_vmw_synccpu_ग_लिखो)) == 0
	    || (arg->flags & ~(drm_vmw_synccpu_पढ़ो | drm_vmw_synccpu_ग_लिखो |
			       drm_vmw_synccpu_करोntblock |
			       drm_vmw_synccpu_allow_cs)) != 0) अणु
		DRM_ERROR("Illegal synccpu flags.\n");
		वापस -EINVAL;
	पूर्ण

	चयन (arg->op) अणु
	हाल drm_vmw_synccpu_grab:
		ret = vmw_user_bo_lookup(tfile, arg->handle, &vbo,
					     &buffer_base);
		अगर (unlikely(ret != 0))
			वापस ret;

		user_bo = container_of(vbo, काष्ठा vmw_user_buffer_object,
				       vbo);
		ret = vmw_user_bo_synccpu_grab(user_bo, tfile, arg->flags);
		vmw_bo_unreference(&vbo);
		tपंचांग_base_object_unref(&buffer_base);
		अगर (unlikely(ret != 0 && ret != -ERESTARTSYS &&
			     ret != -EBUSY)) अणु
			DRM_ERROR("Failed synccpu grab on handle 0x%08x.\n",
				  (अचिन्हित पूर्णांक) arg->handle);
			वापस ret;
		पूर्ण
		अवरोध;
	हाल drm_vmw_synccpu_release:
		ret = vmw_user_bo_synccpu_release(arg->handle, tfile,
						  arg->flags);
		अगर (unlikely(ret != 0)) अणु
			DRM_ERROR("Failed synccpu release on handle 0x%08x.\n",
				  (अचिन्हित पूर्णांक) arg->handle);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Invalid synccpu operation.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * vmw_bo_alloc_ioctl - ioctl function implementing the buffer object
 * allocation functionality.
 *
 * @dev: Identअगरies the drm device.
 * @data: Poपूर्णांकer to the ioctl argument.
 * @file_priv: Identअगरies the caller.
 * Return: Zero on success, negative error code on error.
 *
 * This function checks the ioctl arguments क्रम validity and allocates a
 * काष्ठा vmw_user_buffer_object bo.
 */
पूर्णांक vmw_bo_alloc_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	जोड़ drm_vmw_alloc_dmabuf_arg *arg =
	    (जोड़ drm_vmw_alloc_dmabuf_arg *)data;
	काष्ठा drm_vmw_alloc_dmabuf_req *req = &arg->req;
	काष्ठा drm_vmw_dmabuf_rep *rep = &arg->rep;
	काष्ठा vmw_buffer_object *vbo;
	uपूर्णांक32_t handle;
	पूर्णांक ret;

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_user_bo_alloc(dev_priv, vmw_fpriv(file_priv)->tfile,
				req->size, false, &handle, &vbo,
				शून्य);
	अगर (unlikely(ret != 0))
		जाओ out_no_bo;

	rep->handle = handle;
	rep->map_handle = drm_vma_node_offset_addr(&vbo->base.base.vma_node);
	rep->cur_gmr_id = handle;
	rep->cur_gmr_offset = 0;

	vmw_bo_unreference(&vbo);

out_no_bo:
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);

	वापस ret;
पूर्ण


/**
 * vmw_bo_unref_ioctl - Generic handle बंद ioctl.
 *
 * @dev: Identअगरies the drm device.
 * @data: Poपूर्णांकer to the ioctl argument.
 * @file_priv: Identअगरies the caller.
 * Return: Zero on success, negative error code on error.
 *
 * This function checks the ioctl arguments क्रम validity and बंदs a
 * handle to a TTM base object, optionally मुक्तing the object.
 */
पूर्णांक vmw_bo_unref_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_unref_dmabuf_arg *arg =
	    (काष्ठा drm_vmw_unref_dmabuf_arg *)data;

	वापस tपंचांग_ref_object_base_unref(vmw_fpriv(file_priv)->tfile,
					 arg->handle,
					 TTM_REF_USAGE);
पूर्ण


/**
 * vmw_user_bo_lookup - Look up a vmw user buffer object from a handle.
 *
 * @tfile: The TTM object file the handle is रेजिस्टरed with.
 * @handle: The user buffer object handle
 * @out: Poपूर्णांकer to a where a poपूर्णांकer to the embedded
 * काष्ठा vmw_buffer_object should be placed.
 * @p_base: Poपूर्णांकer to where a poपूर्णांकer to the TTM base object should be
 * placed, or शून्य अगर no such poपूर्णांकer is required.
 * Return: Zero on success, Negative error code on error.
 *
 * Both the output base object poपूर्णांकer and the vmw buffer object poपूर्णांकer
 * will be refcounted.
 */
पूर्णांक vmw_user_bo_lookup(काष्ठा tपंचांग_object_file *tfile,
		       uपूर्णांक32_t handle, काष्ठा vmw_buffer_object **out,
		       काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा vmw_user_buffer_object *vmw_user_bo;
	काष्ठा tपंचांग_base_object *base;

	base = tपंचांग_base_object_lookup(tfile, handle);
	अगर (unlikely(base == शून्य)) अणु
		DRM_ERROR("Invalid buffer object handle 0x%08lx.\n",
			  (अचिन्हित दीर्घ)handle);
		वापस -ESRCH;
	पूर्ण

	अगर (unlikely(tपंचांग_base_object_type(base) != tपंचांग_buffer_type)) अणु
		tपंचांग_base_object_unref(&base);
		DRM_ERROR("Invalid buffer object handle 0x%08lx.\n",
			  (अचिन्हित दीर्घ)handle);
		वापस -EINVAL;
	पूर्ण

	vmw_user_bo = container_of(base, काष्ठा vmw_user_buffer_object,
				   prime.base);
	tपंचांग_bo_get(&vmw_user_bo->vbo.base);
	अगर (p_base)
		*p_base = base;
	अन्यथा
		tपंचांग_base_object_unref(&base);
	*out = &vmw_user_bo->vbo;

	वापस 0;
पूर्ण

/**
 * vmw_user_bo_noref_lookup - Look up a vmw user buffer object without reference
 * @tfile: The TTM object file the handle is रेजिस्टरed with.
 * @handle: The user buffer object handle.
 *
 * This function looks up a काष्ठा vmw_user_bo and वापसs a poपूर्णांकer to the
 * काष्ठा vmw_buffer_object it derives from without refcounting the poपूर्णांकer.
 * The वापसed poपूर्णांकer is only valid until vmw_user_bo_noref_release() is
 * called, and the object poपूर्णांकed to by the वापसed poपूर्णांकer may be करोomed.
 * Any persistent usage of the object requires a refcount to be taken using
 * tपंचांग_bo_reference_unless_करोomed(). Iff this function वापसs successfully it
 * needs to be paired with vmw_user_bo_noref_release() and no sleeping-
 * or scheduling functions may be called inbetween these function calls.
 *
 * Return: A काष्ठा vmw_buffer_object poपूर्णांकer अगर successful or negative
 * error poपूर्णांकer on failure.
 */
काष्ठा vmw_buffer_object *
vmw_user_bo_noref_lookup(काष्ठा tपंचांग_object_file *tfile, u32 handle)
अणु
	काष्ठा vmw_user_buffer_object *vmw_user_bo;
	काष्ठा tपंचांग_base_object *base;

	base = tपंचांग_base_object_noref_lookup(tfile, handle);
	अगर (!base) अणु
		DRM_ERROR("Invalid buffer object handle 0x%08lx.\n",
			  (अचिन्हित दीर्घ)handle);
		वापस ERR_PTR(-ESRCH);
	पूर्ण

	अगर (unlikely(tपंचांग_base_object_type(base) != tपंचांग_buffer_type)) अणु
		tपंचांग_base_object_noref_release();
		DRM_ERROR("Invalid buffer object handle 0x%08lx.\n",
			  (अचिन्हित दीर्घ)handle);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	vmw_user_bo = container_of(base, काष्ठा vmw_user_buffer_object,
				   prime.base);
	वापस &vmw_user_bo->vbo;
पूर्ण

/**
 * vmw_user_bo_reference - Open a handle to a vmw user buffer object.
 *
 * @tfile: The TTM object file to रेजिस्टर the handle with.
 * @vbo: The embedded vmw buffer object.
 * @handle: Poपूर्णांकer to where the new handle should be placed.
 * Return: Zero on success, Negative error code on error.
 */
पूर्णांक vmw_user_bo_reference(काष्ठा tपंचांग_object_file *tfile,
			  काष्ठा vmw_buffer_object *vbo,
			  uपूर्णांक32_t *handle)
अणु
	काष्ठा vmw_user_buffer_object *user_bo;

	अगर (vbo->base.destroy != vmw_user_bo_destroy)
		वापस -EINVAL;

	user_bo = container_of(vbo, काष्ठा vmw_user_buffer_object, vbo);

	*handle = user_bo->prime.base.handle;
	वापस tपंचांग_ref_object_add(tfile, &user_bo->prime.base,
				  TTM_REF_USAGE, शून्य, false);
पूर्ण


/**
 * vmw_bo_fence_single - Utility function to fence a single TTM buffer
 *                       object without unreserving it.
 *
 * @bo:             Poपूर्णांकer to the काष्ठा tपंचांग_buffer_object to fence.
 * @fence:          Poपूर्णांकer to the fence. If शून्य, this function will
 *                  insert a fence पूर्णांकo the command stream..
 *
 * Contrary to the tपंचांग_eu version of this function, it takes only
 * a single buffer object instead of a list, and it also करोesn't
 * unreserve the buffer object, which needs to be करोne separately.
 */
व्योम vmw_bo_fence_single(काष्ठा tपंचांग_buffer_object *bo,
			 काष्ठा vmw_fence_obj *fence)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;

	काष्ठा vmw_निजी *dev_priv =
		container_of(bdev, काष्ठा vmw_निजी, bdev);

	अगर (fence == शून्य) अणु
		vmw_execbuf_fence_commands(शून्य, dev_priv, &fence, शून्य);
		dma_resv_add_excl_fence(bo->base.resv, &fence->base);
		dma_fence_put(&fence->base);
	पूर्ण अन्यथा
		dma_resv_add_excl_fence(bo->base.resv, &fence->base);
पूर्ण


/**
 * vmw_dumb_create - Create a dumb kms buffer
 *
 * @file_priv: Poपूर्णांकer to a काष्ठा drm_file identअगरying the caller.
 * @dev: Poपूर्णांकer to the drm device.
 * @args: Poपूर्णांकer to a काष्ठा drm_mode_create_dumb काष्ठाure
 * Return: Zero on success, negative error code on failure.
 *
 * This is a driver callback क्रम the core drm create_dumb functionality.
 * Note that this is very similar to the vmw_bo_alloc ioctl, except
 * that the arguments have a dअगरferent क्रमmat.
 */
पूर्णांक vmw_dumb_create(काष्ठा drm_file *file_priv,
		    काष्ठा drm_device *dev,
		    काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा vmw_buffer_object *vbo;
	पूर्णांक ret;

	args->pitch = args->width * ((args->bpp + 7) / 8);
	args->size = args->pitch * args->height;

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = vmw_user_bo_alloc(dev_priv, vmw_fpriv(file_priv)->tfile,
				    args->size, false, &args->handle,
				    &vbo, शून्य);
	अगर (unlikely(ret != 0))
		जाओ out_no_bo;

	vmw_bo_unreference(&vbo);
out_no_bo:
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
	वापस ret;
पूर्ण


/**
 * vmw_dumb_map_offset - Return the address space offset of a dumb buffer
 *
 * @file_priv: Poपूर्णांकer to a काष्ठा drm_file identअगरying the caller.
 * @dev: Poपूर्णांकer to the drm device.
 * @handle: Handle identअगरying the dumb buffer.
 * @offset: The address space offset वापसed.
 * Return: Zero on success, negative error code on failure.
 *
 * This is a driver callback क्रम the core drm dumb_map_offset functionality.
 */
पूर्णांक vmw_dumb_map_offset(काष्ठा drm_file *file_priv,
			काष्ठा drm_device *dev, uपूर्णांक32_t handle,
			uपूर्णांक64_t *offset)
अणु
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_buffer_object *out_buf;
	पूर्णांक ret;

	ret = vmw_user_bo_lookup(tfile, handle, &out_buf, शून्य);
	अगर (ret != 0)
		वापस -EINVAL;

	*offset = drm_vma_node_offset_addr(&out_buf->base.base.vma_node);
	vmw_bo_unreference(&out_buf);
	वापस 0;
पूर्ण


/**
 * vmw_dumb_destroy - Destroy a dumb boffer
 *
 * @file_priv: Poपूर्णांकer to a काष्ठा drm_file identअगरying the caller.
 * @dev: Poपूर्णांकer to the drm device.
 * @handle: Handle identअगरying the dumb buffer.
 * Return: Zero on success, negative error code on failure.
 *
 * This is a driver callback क्रम the core drm dumb_destroy functionality.
 */
पूर्णांक vmw_dumb_destroy(काष्ठा drm_file *file_priv,
		     काष्ठा drm_device *dev,
		     uपूर्णांक32_t handle)
अणु
	वापस tपंचांग_ref_object_base_unref(vmw_fpriv(file_priv)->tfile,
					 handle, TTM_REF_USAGE);
पूर्ण


/**
 * vmw_bo_swap_notअगरy - swapout notअगरy callback.
 *
 * @bo: The buffer object to be swapped out.
 */
व्योम vmw_bo_swap_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	/* Is @bo embedded in a काष्ठा vmw_buffer_object? */
	अगर (bo->destroy != vmw_bo_bo_मुक्त &&
	    bo->destroy != vmw_user_bo_destroy)
		वापस;

	/* Kill any cached kernel maps beक्रमe swapout */
	vmw_bo_unmap(vmw_buffer_object(bo));
पूर्ण


/**
 * vmw_bo_move_notअगरy - TTM move_notअगरy_callback
 *
 * @bo: The TTM buffer object about to move.
 * @mem: The काष्ठा tपंचांग_resource indicating to what memory
 *       region the move is taking place.
 *
 * Detaches cached maps and device bindings that require that the
 * buffer करोesn't move.
 */
व्योम vmw_bo_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
			काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा vmw_buffer_object *vbo;

	/* Make sure @bo is embedded in a काष्ठा vmw_buffer_object? */
	अगर (bo->destroy != vmw_bo_bo_मुक्त &&
	    bo->destroy != vmw_user_bo_destroy)
		वापस;

	vbo = container_of(bo, काष्ठा vmw_buffer_object, base);

	/*
	 * Kill any cached kernel maps beक्रमe move to or from VRAM.
	 * With other types of moves, the underlying pages stay the same,
	 * and the map can be kept.
	 */
	अगर (mem->mem_type == TTM_PL_VRAM || bo->mem.mem_type == TTM_PL_VRAM)
		vmw_bo_unmap(vbo);

	/*
	 * If we're moving a backup MOB out of MOB placement, then make sure we
	 * पढ़ो back all resource content first, and unbind the MOB from
	 * the resource.
	 */
	अगर (mem->mem_type != VMW_PL_MOB && bo->mem.mem_type == VMW_PL_MOB)
		vmw_resource_unbind_list(vbo);
पूर्ण
