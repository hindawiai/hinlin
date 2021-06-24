<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
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

#समावेश "vmwgfx_resource_priv.h"
#समावेश "vmwgfx_binding.h"
#समावेश "vmwgfx_drv.h"

#घोषणा VMW_RES_EVICT_ERR_COUNT 10

/**
 * vmw_resource_mob_attach - Mark a resource as attached to its backing mob
 * @res: The resource
 */
व्योम vmw_resource_mob_attach(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_buffer_object *backup = res->backup;
	काष्ठा rb_node **new = &backup->res_tree.rb_node, *parent = शून्य;

	dma_resv_निश्चित_held(res->backup->base.base.resv);
	res->used_prio = (res->res_dirty) ? res->func->dirty_prio :
		res->func->prio;

	जबतक (*new) अणु
		काष्ठा vmw_resource *this =
			container_of(*new, काष्ठा vmw_resource, mob_node);

		parent = *new;
		new = (res->backup_offset < this->backup_offset) ?
			&((*new)->rb_left) : &((*new)->rb_right);
	पूर्ण

	rb_link_node(&res->mob_node, parent, new);
	rb_insert_color(&res->mob_node, &backup->res_tree);

	vmw_bo_prio_add(backup, res->used_prio);
पूर्ण

/**
 * vmw_resource_mob_detach - Mark a resource as detached from its backing mob
 * @res: The resource
 */
व्योम vmw_resource_mob_detach(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_buffer_object *backup = res->backup;

	dma_resv_निश्चित_held(backup->base.base.resv);
	अगर (vmw_resource_mob_attached(res)) अणु
		rb_erase(&res->mob_node, &backup->res_tree);
		RB_CLEAR_NODE(&res->mob_node);
		vmw_bo_prio_del(backup, res->used_prio);
	पूर्ण
पूर्ण

काष्ठा vmw_resource *vmw_resource_reference(काष्ठा vmw_resource *res)
अणु
	kref_get(&res->kref);
	वापस res;
पूर्ण

काष्ठा vmw_resource *
vmw_resource_reference_unless_करोomed(काष्ठा vmw_resource *res)
अणु
	वापस kref_get_unless_zero(&res->kref) ? res : शून्य;
पूर्ण

/**
 * vmw_resource_release_id - release a resource id to the id manager.
 *
 * @res: Poपूर्णांकer to the resource.
 *
 * Release the resource id to the resource id manager and set it to -1
 */
व्योम vmw_resource_release_id(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा idr *idr = &dev_priv->res_idr[res->func->res_type];

	spin_lock(&dev_priv->resource_lock);
	अगर (res->id != -1)
		idr_हटाओ(idr, res->id);
	res->id = -1;
	spin_unlock(&dev_priv->resource_lock);
पूर्ण

अटल व्योम vmw_resource_release(काष्ठा kref *kref)
अणु
	काष्ठा vmw_resource *res =
	    container_of(kref, काष्ठा vmw_resource, kref);
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	पूर्णांक id;
	काष्ठा idr *idr = &dev_priv->res_idr[res->func->res_type];

	spin_lock(&dev_priv->resource_lock);
	list_del_init(&res->lru_head);
	spin_unlock(&dev_priv->resource_lock);
	अगर (res->backup) अणु
		काष्ठा tपंचांग_buffer_object *bo = &res->backup->base;

		tपंचांग_bo_reserve(bo, false, false, शून्य);
		अगर (vmw_resource_mob_attached(res) &&
		    res->func->unbind != शून्य) अणु
			काष्ठा tपंचांग_validate_buffer val_buf;

			val_buf.bo = bo;
			val_buf.num_shared = 0;
			res->func->unbind(res, false, &val_buf);
		पूर्ण
		res->backup_dirty = false;
		vmw_resource_mob_detach(res);
		अगर (res->dirty)
			res->func->dirty_मुक्त(res);
		अगर (res->coherent)
			vmw_bo_dirty_release(res->backup);
		tपंचांग_bo_unreserve(bo);
		vmw_bo_unreference(&res->backup);
	पूर्ण

	अगर (likely(res->hw_destroy != शून्य)) अणु
		mutex_lock(&dev_priv->binding_mutex);
		vmw_binding_res_list_समाप्त(&res->binding_head);
		mutex_unlock(&dev_priv->binding_mutex);
		res->hw_destroy(res);
	पूर्ण

	id = res->id;
	अगर (res->res_मुक्त != शून्य)
		res->res_मुक्त(res);
	अन्यथा
		kमुक्त(res);

	spin_lock(&dev_priv->resource_lock);
	अगर (id != -1)
		idr_हटाओ(idr, id);
	spin_unlock(&dev_priv->resource_lock);
पूर्ण

व्योम vmw_resource_unreference(काष्ठा vmw_resource **p_res)
अणु
	काष्ठा vmw_resource *res = *p_res;

	*p_res = शून्य;
	kref_put(&res->kref, vmw_resource_release);
पूर्ण


/**
 * vmw_resource_alloc_id - release a resource id to the id manager.
 *
 * @res: Poपूर्णांकer to the resource.
 *
 * Allocate the lowest मुक्त resource from the resource manager, and set
 * @res->id to that id. Returns 0 on success and -ENOMEM on failure.
 */
पूर्णांक vmw_resource_alloc_id(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	पूर्णांक ret;
	काष्ठा idr *idr = &dev_priv->res_idr[res->func->res_type];

	BUG_ON(res->id != -1);

	idr_preload(GFP_KERNEL);
	spin_lock(&dev_priv->resource_lock);

	ret = idr_alloc(idr, res, 1, 0, GFP_NOWAIT);
	अगर (ret >= 0)
		res->id = ret;

	spin_unlock(&dev_priv->resource_lock);
	idr_preload_end();
	वापस ret < 0 ? ret : 0;
पूर्ण

/**
 * vmw_resource_init - initialize a काष्ठा vmw_resource
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी काष्ठा.
 * @res:            The काष्ठा vmw_resource to initialize.
 * @delay_id:       Boolean whether to defer device id allocation until
 *                  the first validation.
 * @res_मुक्त:       Resource deकाष्ठाor.
 * @func:           Resource function table.
 */
पूर्णांक vmw_resource_init(काष्ठा vmw_निजी *dev_priv, काष्ठा vmw_resource *res,
		      bool delay_id,
		      व्योम (*res_मुक्त) (काष्ठा vmw_resource *res),
		      स्थिर काष्ठा vmw_res_func *func)
अणु
	kref_init(&res->kref);
	res->hw_destroy = शून्य;
	res->res_मुक्त = res_मुक्त;
	res->dev_priv = dev_priv;
	res->func = func;
	RB_CLEAR_NODE(&res->mob_node);
	INIT_LIST_HEAD(&res->lru_head);
	INIT_LIST_HEAD(&res->binding_head);
	res->id = -1;
	res->backup = शून्य;
	res->backup_offset = 0;
	res->backup_dirty = false;
	res->res_dirty = false;
	res->coherent = false;
	res->used_prio = 3;
	res->dirty = शून्य;
	अगर (delay_id)
		वापस 0;
	अन्यथा
		वापस vmw_resource_alloc_id(res);
पूर्ण


/**
 * vmw_user_resource_lookup_handle - lookup a काष्ठा resource from a
 * TTM user-space handle and perक्रमm basic type checks
 *
 * @dev_priv:     Poपूर्णांकer to a device निजी काष्ठा
 * @tfile:        Poपूर्णांकer to a काष्ठा tपंचांग_object_file identअगरying the caller
 * @handle:       The TTM user-space handle
 * @converter:    Poपूर्णांकer to an object describing the resource type
 * @p_res:        On successful वापस the location poपूर्णांकed to will contain
 *                a poपूर्णांकer to a refcounted काष्ठा vmw_resource.
 *
 * If the handle can't be found or is associated with an incorrect resource
 * type, -EINVAL will be वापसed.
 */
पूर्णांक vmw_user_resource_lookup_handle(काष्ठा vmw_निजी *dev_priv,
				    काष्ठा tपंचांग_object_file *tfile,
				    uपूर्णांक32_t handle,
				    स्थिर काष्ठा vmw_user_resource_conv
				    *converter,
				    काष्ठा vmw_resource **p_res)
अणु
	काष्ठा tपंचांग_base_object *base;
	काष्ठा vmw_resource *res;
	पूर्णांक ret = -EINVAL;

	base = tपंचांग_base_object_lookup(tfile, handle);
	अगर (unlikely(base == शून्य))
		वापस -EINVAL;

	अगर (unlikely(tपंचांग_base_object_type(base) != converter->object_type))
		जाओ out_bad_resource;

	res = converter->base_obj_to_res(base);
	kref_get(&res->kref);

	*p_res = res;
	ret = 0;

out_bad_resource:
	tपंचांग_base_object_unref(&base);

	वापस ret;
पूर्ण

/**
 * vmw_user_resource_lookup_handle - lookup a काष्ठा resource from a
 * TTM user-space handle and perक्रमm basic type checks
 *
 * @dev_priv:     Poपूर्णांकer to a device निजी काष्ठा
 * @tfile:        Poपूर्णांकer to a काष्ठा tपंचांग_object_file identअगरying the caller
 * @handle:       The TTM user-space handle
 * @converter:    Poपूर्णांकer to an object describing the resource type
 *
 * If the handle can't be found or is associated with an incorrect resource
 * type, -EINVAL will be वापसed.
 */
काष्ठा vmw_resource *
vmw_user_resource_noref_lookup_handle(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा tपंचांग_object_file *tfile,
				      uपूर्णांक32_t handle,
				      स्थिर काष्ठा vmw_user_resource_conv
				      *converter)
अणु
	काष्ठा tपंचांग_base_object *base;

	base = tपंचांग_base_object_noref_lookup(tfile, handle);
	अगर (!base)
		वापस ERR_PTR(-ESRCH);

	अगर (unlikely(tपंचांग_base_object_type(base) != converter->object_type)) अणु
		tपंचांग_base_object_noref_release();
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस converter->base_obj_to_res(base);
पूर्ण

/*
 * Helper function that looks either a surface or bo.
 *
 * The poपूर्णांकer this poपूर्णांकed at by out_surf and out_buf needs to be null.
 */
पूर्णांक vmw_user_lookup_handle(काष्ठा vmw_निजी *dev_priv,
			   काष्ठा tपंचांग_object_file *tfile,
			   uपूर्णांक32_t handle,
			   काष्ठा vmw_surface **out_surf,
			   काष्ठा vmw_buffer_object **out_buf)
अणु
	काष्ठा vmw_resource *res;
	पूर्णांक ret;

	BUG_ON(*out_surf || *out_buf);

	ret = vmw_user_resource_lookup_handle(dev_priv, tfile, handle,
					      user_surface_converter,
					      &res);
	अगर (!ret) अणु
		*out_surf = vmw_res_to_srf(res);
		वापस 0;
	पूर्ण

	*out_surf = शून्य;
	ret = vmw_user_bo_lookup(tfile, handle, out_buf, शून्य);
	वापस ret;
पूर्ण

/**
 * vmw_resource_buf_alloc - Allocate a backup buffer क्रम a resource.
 *
 * @res:            The resource क्रम which to allocate a backup buffer.
 * @पूर्णांकerruptible:  Whether any sleeps during allocation should be
 *                  perक्रमmed जबतक पूर्णांकerruptible.
 */
अटल पूर्णांक vmw_resource_buf_alloc(काष्ठा vmw_resource *res,
				  bool पूर्णांकerruptible)
अणु
	अचिन्हित दीर्घ size =
		(res->backup_size + PAGE_SIZE - 1) & PAGE_MASK;
	काष्ठा vmw_buffer_object *backup;
	पूर्णांक ret;

	अगर (likely(res->backup)) अणु
		BUG_ON(res->backup->base.base.size < size);
		वापस 0;
	पूर्ण

	backup = kzalloc(माप(*backup), GFP_KERNEL);
	अगर (unlikely(!backup))
		वापस -ENOMEM;

	ret = vmw_bo_init(res->dev_priv, backup, res->backup_size,
			      res->func->backup_placement,
			      पूर्णांकerruptible, false,
			      &vmw_bo_bo_मुक्त);
	अगर (unlikely(ret != 0))
		जाओ out_no_bo;

	res->backup = backup;

out_no_bo:
	वापस ret;
पूर्ण

/**
 * vmw_resource_करो_validate - Make a resource up-to-date and visible
 *                            to the device.
 *
 * @res:            The resource to make visible to the device.
 * @val_buf:        Inक्रमmation about a buffer possibly
 *                  containing backup data अगर a bind operation is needed.
 * @dirtying:       Transfer dirty regions.
 *
 * On hardware resource लघुage, this function वापसs -EBUSY and
 * should be retried once resources have been मुक्तd up.
 */
अटल पूर्णांक vmw_resource_करो_validate(काष्ठा vmw_resource *res,
				    काष्ठा tपंचांग_validate_buffer *val_buf,
				    bool dirtying)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा vmw_res_func *func = res->func;

	अगर (unlikely(res->id == -1)) अणु
		ret = func->create(res);
		अगर (unlikely(ret != 0))
			वापस ret;
	पूर्ण

	अगर (func->bind &&
	    ((func->needs_backup && !vmw_resource_mob_attached(res) &&
	      val_buf->bo != शून्य) ||
	     (!func->needs_backup && val_buf->bo != शून्य))) अणु
		ret = func->bind(res, val_buf);
		अगर (unlikely(ret != 0))
			जाओ out_bind_failed;
		अगर (func->needs_backup)
			vmw_resource_mob_attach(res);
	पूर्ण

	/*
	 * Handle the हाल where the backup mob is marked coherent but
	 * the resource isn't.
	 */
	अगर (func->dirty_alloc && vmw_resource_mob_attached(res) &&
	    !res->coherent) अणु
		अगर (res->backup->dirty && !res->dirty) अणु
			ret = func->dirty_alloc(res);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर (!res->backup->dirty && res->dirty) अणु
			func->dirty_मुक्त(res);
		पूर्ण
	पूर्ण

	/*
	 * Transfer the dirty regions to the resource and update
	 * the resource.
	 */
	अगर (res->dirty) अणु
		अगर (dirtying && !res->res_dirty) अणु
			pgoff_t start = res->backup_offset >> PAGE_SHIFT;
			pgoff_t end = __KERNEL_DIV_ROUND_UP
				(res->backup_offset + res->backup_size,
				 PAGE_SIZE);

			vmw_bo_dirty_unmap(res->backup, start, end);
		पूर्ण

		vmw_bo_dirty_transfer_to_res(res);
		वापस func->dirty_sync(res);
	पूर्ण

	वापस 0;

out_bind_failed:
	func->destroy(res);

	वापस ret;
पूर्ण

/**
 * vmw_resource_unreserve - Unreserve a resource previously reserved क्रम
 * command submission.
 *
 * @res:               Poपूर्णांकer to the काष्ठा vmw_resource to unreserve.
 * @dirty_set:         Change dirty status of the resource.
 * @dirty:             When changing dirty status indicates the new status.
 * @चयन_backup:     Backup buffer has been चयनed.
 * @new_backup:        Poपूर्णांकer to new backup buffer अगर command submission
 *                     चयनed. May be शून्य.
 * @new_backup_offset: New backup offset अगर @चयन_backup is true.
 *
 * Currently unreserving a resource means putting it back on the device's
 * resource lru list, so that it can be evicted अगर necessary.
 */
व्योम vmw_resource_unreserve(काष्ठा vmw_resource *res,
			    bool dirty_set,
			    bool dirty,
			    bool चयन_backup,
			    काष्ठा vmw_buffer_object *new_backup,
			    अचिन्हित दीर्घ new_backup_offset)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;

	अगर (!list_empty(&res->lru_head))
		वापस;

	अगर (चयन_backup && new_backup != res->backup) अणु
		अगर (res->backup) अणु
			vmw_resource_mob_detach(res);
			अगर (res->coherent)
				vmw_bo_dirty_release(res->backup);
			vmw_bo_unreference(&res->backup);
		पूर्ण

		अगर (new_backup) अणु
			res->backup = vmw_bo_reference(new_backup);

			/*
			 * The validation code should alपढ़ोy have added a
			 * dirty tracker here.
			 */
			WARN_ON(res->coherent && !new_backup->dirty);

			vmw_resource_mob_attach(res);
		पूर्ण अन्यथा अणु
			res->backup = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (चयन_backup && res->coherent) अणु
		vmw_bo_dirty_release(res->backup);
	पूर्ण

	अगर (चयन_backup)
		res->backup_offset = new_backup_offset;

	अगर (dirty_set)
		res->res_dirty = dirty;

	अगर (!res->func->may_evict || res->id == -1 || res->pin_count)
		वापस;

	spin_lock(&dev_priv->resource_lock);
	list_add_tail(&res->lru_head,
		      &res->dev_priv->res_lru[res->func->res_type]);
	spin_unlock(&dev_priv->resource_lock);
पूर्ण

/**
 * vmw_resource_check_buffer - Check whether a backup buffer is needed
 *                             क्रम a resource and in that हाल, allocate
 *                             one, reserve and validate it.
 *
 * @ticket:         The ww aqcquire context to use, or शून्य अगर trylocking.
 * @res:            The resource क्रम which to allocate a backup buffer.
 * @पूर्णांकerruptible:  Whether any sleeps during allocation should be
 *                  perक्रमmed जबतक पूर्णांकerruptible.
 * @val_buf:        On successful वापस contains data about the
 *                  reserved and validated backup buffer.
 */
अटल पूर्णांक
vmw_resource_check_buffer(काष्ठा ww_acquire_ctx *ticket,
			  काष्ठा vmw_resource *res,
			  bool पूर्णांकerruptible,
			  काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	काष्ठा list_head val_list;
	bool backup_dirty = false;
	पूर्णांक ret;

	अगर (unlikely(res->backup == शून्य)) अणु
		ret = vmw_resource_buf_alloc(res, पूर्णांकerruptible);
		अगर (unlikely(ret != 0))
			वापस ret;
	पूर्ण

	INIT_LIST_HEAD(&val_list);
	tपंचांग_bo_get(&res->backup->base);
	val_buf->bo = &res->backup->base;
	val_buf->num_shared = 0;
	list_add_tail(&val_buf->head, &val_list);
	ret = tपंचांग_eu_reserve_buffers(ticket, &val_list, पूर्णांकerruptible, शून्य);
	अगर (unlikely(ret != 0))
		जाओ out_no_reserve;

	अगर (res->func->needs_backup && !vmw_resource_mob_attached(res))
		वापस 0;

	backup_dirty = res->backup_dirty;
	ret = tपंचांग_bo_validate(&res->backup->base,
			      res->func->backup_placement,
			      &ctx);

	अगर (unlikely(ret != 0))
		जाओ out_no_validate;

	वापस 0;

out_no_validate:
	tपंचांग_eu_backoff_reservation(ticket, &val_list);
out_no_reserve:
	tपंचांग_bo_put(val_buf->bo);
	val_buf->bo = शून्य;
	अगर (backup_dirty)
		vmw_bo_unreference(&res->backup);

	वापस ret;
पूर्ण

/*
 * vmw_resource_reserve - Reserve a resource क्रम command submission
 *
 * @res:            The resource to reserve.
 *
 * This function takes the resource off the LRU list and make sure
 * a backup buffer is present क्रम guest-backed resources. However,
 * the buffer may not be bound to the resource at this poपूर्णांक.
 *
 */
पूर्णांक vmw_resource_reserve(काष्ठा vmw_resource *res, bool पूर्णांकerruptible,
			 bool no_backup)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	पूर्णांक ret;

	spin_lock(&dev_priv->resource_lock);
	list_del_init(&res->lru_head);
	spin_unlock(&dev_priv->resource_lock);

	अगर (res->func->needs_backup && res->backup == शून्य &&
	    !no_backup) अणु
		ret = vmw_resource_buf_alloc(res, पूर्णांकerruptible);
		अगर (unlikely(ret != 0)) अणु
			DRM_ERROR("Failed to allocate a backup buffer "
				  "of size %lu. bytes\n",
				  (अचिन्हित दीर्घ) res->backup_size);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_resource_backoff_reservation - Unreserve and unreference a
 *                                    backup buffer
 *.
 * @ticket:         The ww acquire ctx used क्रम reservation.
 * @val_buf:        Backup buffer inक्रमmation.
 */
अटल व्योम
vmw_resource_backoff_reservation(काष्ठा ww_acquire_ctx *ticket,
				 काष्ठा tपंचांग_validate_buffer *val_buf)
अणु
	काष्ठा list_head val_list;

	अगर (likely(val_buf->bo == शून्य))
		वापस;

	INIT_LIST_HEAD(&val_list);
	list_add_tail(&val_buf->head, &val_list);
	tपंचांग_eu_backoff_reservation(ticket, &val_list);
	tपंचांग_bo_put(val_buf->bo);
	val_buf->bo = शून्य;
पूर्ण

/**
 * vmw_resource_करो_evict - Evict a resource, and transfer its data
 *                         to a backup buffer.
 *
 * @ticket:         The ww acquire ticket to use, or शून्य अगर trylocking.
 * @res:            The resource to evict.
 * @पूर्णांकerruptible:  Whether to रुको पूर्णांकerruptible.
 */
अटल पूर्णांक vmw_resource_करो_evict(काष्ठा ww_acquire_ctx *ticket,
				 काष्ठा vmw_resource *res, bool पूर्णांकerruptible)
अणु
	काष्ठा tपंचांग_validate_buffer val_buf;
	स्थिर काष्ठा vmw_res_func *func = res->func;
	पूर्णांक ret;

	BUG_ON(!func->may_evict);

	val_buf.bo = शून्य;
	val_buf.num_shared = 0;
	ret = vmw_resource_check_buffer(ticket, res, पूर्णांकerruptible, &val_buf);
	अगर (unlikely(ret != 0))
		वापस ret;

	अगर (unlikely(func->unbind != शून्य &&
		     (!func->needs_backup || vmw_resource_mob_attached(res)))) अणु
		ret = func->unbind(res, res->res_dirty, &val_buf);
		अगर (unlikely(ret != 0))
			जाओ out_no_unbind;
		vmw_resource_mob_detach(res);
	पूर्ण
	ret = func->destroy(res);
	res->backup_dirty = true;
	res->res_dirty = false;
out_no_unbind:
	vmw_resource_backoff_reservation(ticket, &val_buf);

	वापस ret;
पूर्ण


/**
 * vmw_resource_validate - Make a resource up-to-date and visible
 *                         to the device.
 * @res: The resource to make visible to the device.
 * @पूर्णांकr: Perक्रमm रुकोs पूर्णांकerruptible अगर possible.
 * @dirtying: Pending GPU operation will dirty the resource
 *
 * On succesful वापस, any backup DMA buffer poपूर्णांकed to by @res->backup will
 * be reserved and validated.
 * On hardware resource लघुage, this function will repeatedly evict
 * resources of the same type until the validation succeeds.
 *
 * Return: Zero on success, -ERESTARTSYS अगर पूर्णांकerrupted, negative error code
 * on failure.
 */
पूर्णांक vmw_resource_validate(काष्ठा vmw_resource *res, bool पूर्णांकr,
			  bool dirtying)
अणु
	पूर्णांक ret;
	काष्ठा vmw_resource *evict_res;
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा list_head *lru_list = &dev_priv->res_lru[res->func->res_type];
	काष्ठा tपंचांग_validate_buffer val_buf;
	अचिन्हित err_count = 0;

	अगर (!res->func->create)
		वापस 0;

	val_buf.bo = शून्य;
	val_buf.num_shared = 0;
	अगर (res->backup)
		val_buf.bo = &res->backup->base;
	करो अणु
		ret = vmw_resource_करो_validate(res, &val_buf, dirtying);
		अगर (likely(ret != -EBUSY))
			अवरोध;

		spin_lock(&dev_priv->resource_lock);
		अगर (list_empty(lru_list) || !res->func->may_evict) अणु
			DRM_ERROR("Out of device device resources "
				  "for %s.\n", res->func->type_name);
			ret = -EBUSY;
			spin_unlock(&dev_priv->resource_lock);
			अवरोध;
		पूर्ण

		evict_res = vmw_resource_reference
			(list_first_entry(lru_list, काष्ठा vmw_resource,
					  lru_head));
		list_del_init(&evict_res->lru_head);

		spin_unlock(&dev_priv->resource_lock);

		/* Trylock backup buffers with a शून्य ticket. */
		ret = vmw_resource_करो_evict(शून्य, evict_res, पूर्णांकr);
		अगर (unlikely(ret != 0)) अणु
			spin_lock(&dev_priv->resource_lock);
			list_add_tail(&evict_res->lru_head, lru_list);
			spin_unlock(&dev_priv->resource_lock);
			अगर (ret == -ERESTARTSYS ||
			    ++err_count > VMW_RES_EVICT_ERR_COUNT) अणु
				vmw_resource_unreference(&evict_res);
				जाओ out_no_validate;
			पूर्ण
		पूर्ण

		vmw_resource_unreference(&evict_res);
	पूर्ण जबतक (1);

	अगर (unlikely(ret != 0))
		जाओ out_no_validate;
	अन्यथा अगर (!res->func->needs_backup && res->backup) अणु
		WARN_ON_ONCE(vmw_resource_mob_attached(res));
		vmw_bo_unreference(&res->backup);
	पूर्ण

	वापस 0;

out_no_validate:
	वापस ret;
पूर्ण


/**
 * vmw_resource_unbind_list
 *
 * @vbo: Poपूर्णांकer to the current backing MOB.
 *
 * Evicts the Guest Backed hardware resource अगर the backup
 * buffer is being moved out of MOB memory.
 * Note that this function will not race with the resource
 * validation code, since resource validation and eviction
 * both require the backup buffer to be reserved.
 */
व्योम vmw_resource_unbind_list(काष्ठा vmw_buffer_object *vbo)
अणु
	काष्ठा tपंचांग_validate_buffer val_buf = अणु
		.bo = &vbo->base,
		.num_shared = 0
	पूर्ण;

	dma_resv_निश्चित_held(vbo->base.base.resv);
	जबतक (!RB_EMPTY_ROOT(&vbo->res_tree)) अणु
		काष्ठा rb_node *node = vbo->res_tree.rb_node;
		काष्ठा vmw_resource *res =
			container_of(node, काष्ठा vmw_resource, mob_node);

		अगर (!WARN_ON_ONCE(!res->func->unbind))
			(व्योम) res->func->unbind(res, res->res_dirty, &val_buf);

		res->backup_dirty = true;
		res->res_dirty = false;
		vmw_resource_mob_detach(res);
	पूर्ण

	(व्योम) tपंचांग_bo_रुको(&vbo->base, false, false);
पूर्ण


/**
 * vmw_query_पढ़ोback_all - Read back cached query states
 *
 * @dx_query_mob: Buffer containing the DX query MOB
 *
 * Read back cached states from the device अगर they exist.  This function
 * assumings binding_mutex is held.
 */
पूर्णांक vmw_query_पढ़ोback_all(काष्ठा vmw_buffer_object *dx_query_mob)
अणु
	काष्ठा vmw_resource *dx_query_ctx;
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDXReadbackAllQuery body;
	पूर्ण *cmd;


	/* No query bound, so करो nothing */
	अगर (!dx_query_mob || !dx_query_mob->dx_query_ctx)
		वापस 0;

	dx_query_ctx = dx_query_mob->dx_query_ctx;
	dev_priv     = dx_query_ctx->dev_priv;

	cmd = VMW_CMD_CTX_RESERVE(dev_priv, माप(*cmd), dx_query_ctx->id);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id   = SVGA_3D_CMD_DX_READBACK_ALL_QUERY;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid    = dx_query_ctx->id;

	vmw_cmd_commit(dev_priv, माप(*cmd));

	/* Triggers a rebind the next समय affected context is bound */
	dx_query_mob->dx_query_ctx = शून्य;

	वापस 0;
पूर्ण



/**
 * vmw_query_move_notअगरy - Read back cached query states
 *
 * @bo: The TTM buffer object about to move.
 * @old_mem: The memory region @bo is moving from.
 * @new_mem: The memory region @bo is moving to.
 *
 * Called beक्रमe the query MOB is swapped out to पढ़ो back cached query
 * states from the device.
 */
व्योम vmw_query_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
			   काष्ठा tपंचांग_resource *old_mem,
			   काष्ठा tपंचांग_resource *new_mem)
अणु
	काष्ठा vmw_buffer_object *dx_query_mob;
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	काष्ठा vmw_निजी *dev_priv;


	dev_priv = container_of(bdev, काष्ठा vmw_निजी, bdev);

	mutex_lock(&dev_priv->binding_mutex);

	dx_query_mob = container_of(bo, काष्ठा vmw_buffer_object, base);
	अगर (!dx_query_mob || !dx_query_mob->dx_query_ctx) अणु
		mutex_unlock(&dev_priv->binding_mutex);
		वापस;
	पूर्ण

	/* If BO is being moved from MOB to प्रणाली memory */
	अगर (new_mem->mem_type == TTM_PL_SYSTEM &&
	    old_mem->mem_type == VMW_PL_MOB) अणु
		काष्ठा vmw_fence_obj *fence;

		(व्योम) vmw_query_पढ़ोback_all(dx_query_mob);
		mutex_unlock(&dev_priv->binding_mutex);

		/* Create a fence and attach the BO to it */
		(व्योम) vmw_execbuf_fence_commands(शून्य, dev_priv, &fence, शून्य);
		vmw_bo_fence_single(bo, fence);

		अगर (fence != शून्य)
			vmw_fence_obj_unreference(&fence);

		(व्योम) tपंचांग_bo_रुको(bo, false, false);
	पूर्ण अन्यथा
		mutex_unlock(&dev_priv->binding_mutex);

पूर्ण

/**
 * vmw_resource_needs_backup - Return whether a resource needs a backup buffer.
 *
 * @res:            The resource being queried.
 */
bool vmw_resource_needs_backup(स्थिर काष्ठा vmw_resource *res)
अणु
	वापस res->func->needs_backup;
पूर्ण

/**
 * vmw_resource_evict_type - Evict all resources of a specअगरic type
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी काष्ठा
 * @type:           The resource type to evict
 *
 * To aव्योम thrashing starvation or as part of the hibernation sequence,
 * try to evict all evictable resources of a specअगरic type.
 */
अटल व्योम vmw_resource_evict_type(काष्ठा vmw_निजी *dev_priv,
				    क्रमागत vmw_res_type type)
अणु
	काष्ठा list_head *lru_list = &dev_priv->res_lru[type];
	काष्ठा vmw_resource *evict_res;
	अचिन्हित err_count = 0;
	पूर्णांक ret;
	काष्ठा ww_acquire_ctx ticket;

	करो अणु
		spin_lock(&dev_priv->resource_lock);

		अगर (list_empty(lru_list))
			जाओ out_unlock;

		evict_res = vmw_resource_reference(
			list_first_entry(lru_list, काष्ठा vmw_resource,
					 lru_head));
		list_del_init(&evict_res->lru_head);
		spin_unlock(&dev_priv->resource_lock);

		/* Wait lock backup buffers with a ticket. */
		ret = vmw_resource_करो_evict(&ticket, evict_res, false);
		अगर (unlikely(ret != 0)) अणु
			spin_lock(&dev_priv->resource_lock);
			list_add_tail(&evict_res->lru_head, lru_list);
			spin_unlock(&dev_priv->resource_lock);
			अगर (++err_count > VMW_RES_EVICT_ERR_COUNT) अणु
				vmw_resource_unreference(&evict_res);
				वापस;
			पूर्ण
		पूर्ण

		vmw_resource_unreference(&evict_res);
	पूर्ण जबतक (1);

out_unlock:
	spin_unlock(&dev_priv->resource_lock);
पूर्ण

/**
 * vmw_resource_evict_all - Evict all evictable resources
 *
 * @dev_priv:       Poपूर्णांकer to a device निजी काष्ठा
 *
 * To aव्योम thrashing starvation or as part of the hibernation sequence,
 * evict all evictable resources. In particular this means that all
 * guest-backed resources that are रेजिस्टरed with the device are
 * evicted and the OTable becomes clean.
 */
व्योम vmw_resource_evict_all(काष्ठा vmw_निजी *dev_priv)
अणु
	क्रमागत vmw_res_type type;

	mutex_lock(&dev_priv->cmdbuf_mutex);

	क्रम (type = 0; type < vmw_res_max; ++type)
		vmw_resource_evict_type(dev_priv, type);

	mutex_unlock(&dev_priv->cmdbuf_mutex);
पूर्ण

/*
 * vmw_resource_pin - Add a pin reference on a resource
 *
 * @res: The resource to add a pin reference on
 *
 * This function adds a pin reference, and अगर needed validates the resource.
 * Having a pin reference means that the resource can never be evicted, and
 * its id will never change as दीर्घ as there is a pin reference.
 * This function वापसs 0 on success and a negative error code on failure.
 */
पूर्णांक vmw_resource_pin(काष्ठा vmw_resource *res, bool पूर्णांकerruptible)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु पूर्णांकerruptible, false पूर्ण;
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	पूर्णांक ret;

	tपंचांग_ग_लिखो_lock(&dev_priv->reservation_sem, पूर्णांकerruptible);
	mutex_lock(&dev_priv->cmdbuf_mutex);
	ret = vmw_resource_reserve(res, पूर्णांकerruptible, false);
	अगर (ret)
		जाओ out_no_reserve;

	अगर (res->pin_count == 0) अणु
		काष्ठा vmw_buffer_object *vbo = शून्य;

		अगर (res->backup) अणु
			vbo = res->backup;

			tपंचांग_bo_reserve(&vbo->base, पूर्णांकerruptible, false, शून्य);
			अगर (!vbo->base.pin_count) अणु
				ret = tपंचांग_bo_validate
					(&vbo->base,
					 res->func->backup_placement,
					 &ctx);
				अगर (ret) अणु
					tपंचांग_bo_unreserve(&vbo->base);
					जाओ out_no_validate;
				पूर्ण
			पूर्ण

			/* Do we really need to pin the MOB as well? */
			vmw_bo_pin_reserved(vbo, true);
		पूर्ण
		ret = vmw_resource_validate(res, पूर्णांकerruptible, true);
		अगर (vbo)
			tपंचांग_bo_unreserve(&vbo->base);
		अगर (ret)
			जाओ out_no_validate;
	पूर्ण
	res->pin_count++;

out_no_validate:
	vmw_resource_unreserve(res, false, false, false, शून्य, 0UL);
out_no_reserve:
	mutex_unlock(&dev_priv->cmdbuf_mutex);
	tपंचांग_ग_लिखो_unlock(&dev_priv->reservation_sem);

	वापस ret;
पूर्ण

/**
 * vmw_resource_unpin - Remove a pin reference from a resource
 *
 * @res: The resource to हटाओ a pin reference from
 *
 * Having a pin reference means that the resource can never be evicted, and
 * its id will never change as दीर्घ as there is a pin reference.
 */
व्योम vmw_resource_unpin(काष्ठा vmw_resource *res)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	पूर्णांक ret;

	(व्योम) tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, false);
	mutex_lock(&dev_priv->cmdbuf_mutex);

	ret = vmw_resource_reserve(res, false, true);
	WARN_ON(ret);

	WARN_ON(res->pin_count == 0);
	अगर (--res->pin_count == 0 && res->backup) अणु
		काष्ठा vmw_buffer_object *vbo = res->backup;

		(व्योम) tपंचांग_bo_reserve(&vbo->base, false, false, शून्य);
		vmw_bo_pin_reserved(vbo, false);
		tपंचांग_bo_unreserve(&vbo->base);
	पूर्ण

	vmw_resource_unreserve(res, false, false, false, शून्य, 0UL);

	mutex_unlock(&dev_priv->cmdbuf_mutex);
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);
पूर्ण

/**
 * vmw_res_type - Return the resource type
 *
 * @res: Poपूर्णांकer to the resource
 */
क्रमागत vmw_res_type vmw_res_type(स्थिर काष्ठा vmw_resource *res)
अणु
	वापस res->func->res_type;
पूर्ण

/**
 * vmw_resource_update_dirty - Update a resource's dirty tracker with a
 * sequential range of touched backing store memory.
 * @res: The resource.
 * @start: The first page touched.
 * @end: The last page touched + 1.
 */
व्योम vmw_resource_dirty_update(काष्ठा vmw_resource *res, pgoff_t start,
			       pgoff_t end)
अणु
	अगर (res->dirty)
		res->func->dirty_range_add(res, start << PAGE_SHIFT,
					   end << PAGE_SHIFT);
पूर्ण

/**
 * vmw_resources_clean - Clean resources पूर्णांकersecting a mob range
 * @vbo: The mob buffer object
 * @start: The mob page offset starting the range
 * @end: The mob page offset ending the range
 * @num_prefault: Returns how many pages including the first have been
 * cleaned and are ok to prefault
 */
पूर्णांक vmw_resources_clean(काष्ठा vmw_buffer_object *vbo, pgoff_t start,
			pgoff_t end, pgoff_t *num_prefault)
अणु
	काष्ठा rb_node *cur = vbo->res_tree.rb_node;
	काष्ठा vmw_resource *found = शून्य;
	अचिन्हित दीर्घ res_start = start << PAGE_SHIFT;
	अचिन्हित दीर्घ res_end = end << PAGE_SHIFT;
	अचिन्हित दीर्घ last_cleaned = 0;

	/*
	 * Find the resource with lowest backup_offset that पूर्णांकersects the
	 * range.
	 */
	जबतक (cur) अणु
		काष्ठा vmw_resource *cur_res =
			container_of(cur, काष्ठा vmw_resource, mob_node);

		अगर (cur_res->backup_offset >= res_end) अणु
			cur = cur->rb_left;
		पूर्ण अन्यथा अगर (cur_res->backup_offset + cur_res->backup_size <=
			   res_start) अणु
			cur = cur->rb_right;
		पूर्ण अन्यथा अणु
			found = cur_res;
			cur = cur->rb_left;
			/* Continue to look क्रम resources with lower offsets */
		पूर्ण
	पूर्ण

	/*
	 * In order of increasing backup_offset, clean dirty resorces
	 * पूर्णांकersecting the range.
	 */
	जबतक (found) अणु
		अगर (found->res_dirty) अणु
			पूर्णांक ret;

			अगर (!found->func->clean)
				वापस -EINVAL;

			ret = found->func->clean(found);
			अगर (ret)
				वापस ret;

			found->res_dirty = false;
		पूर्ण
		last_cleaned = found->backup_offset + found->backup_size;
		cur = rb_next(&found->mob_node);
		अगर (!cur)
			अवरोध;

		found = container_of(cur, काष्ठा vmw_resource, mob_node);
		अगर (found->backup_offset >= res_end)
			अवरोध;
	पूर्ण

	/*
	 * Set number of pages allowed prefaulting and fence the buffer object
	 */
	*num_prefault = 1;
	अगर (last_cleaned > res_start) अणु
		काष्ठा tपंचांग_buffer_object *bo = &vbo->base;

		*num_prefault = __KERNEL_DIV_ROUND_UP(last_cleaned - res_start,
						      PAGE_SIZE);
		vmw_bo_fence_single(bo, शून्य);
		अगर (bo->moving)
			dma_fence_put(bo->moving);
		bo->moving = dma_fence_get
			(dma_resv_get_excl(bo->base.resv));
	पूर्ण

	वापस 0;
पूर्ण
