<शैली गुरु>
/*
 * Legacy: Generic DRM Contexts
 *
 * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
 *
 * Author: Rickard E. (Rik) Faith <faith@valinux.com>
 * Author: Gareth Hughes <gareth@valinux.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_legacy.h"

काष्ठा drm_ctx_list अणु
	काष्ठा list_head head;
	drm_context_t handle;
	काष्ठा drm_file *tag;
पूर्ण;

/******************************************************************/
/** \नame Context biपंचांगap support */
/*@अणु*/

/*
 * Free a handle from the context biपंचांगap.
 *
 * \param dev DRM device.
 * \param ctx_handle context handle.
 *
 * Clears the bit specअगरied by \p ctx_handle in drm_device::ctx_biपंचांगap and the entry
 * in drm_device::ctx_idr, जबतक holding the drm_device::काष्ठा_mutex
 * lock.
 */
व्योम drm_legacy_ctxbiपंचांगap_मुक्त(काष्ठा drm_device * dev, पूर्णांक ctx_handle)
अणु
	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस;

	mutex_lock(&dev->काष्ठा_mutex);
	idr_हटाओ(&dev->ctx_idr, ctx_handle);
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण

/*
 * Context biपंचांगap allocation.
 *
 * \param dev DRM device.
 * \लeturn (non-negative) context handle on success or a negative number on failure.
 *
 * Allocate a new idr from drm_device::ctx_idr जबतक holding the
 * drm_device::काष्ठा_mutex lock.
 */
अटल पूर्णांक drm_legacy_ctxbiपंचांगap_next(काष्ठा drm_device * dev)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->काष्ठा_mutex);
	ret = idr_alloc(&dev->ctx_idr, शून्य, DRM_RESERVED_CONTEXTS, 0,
			GFP_KERNEL);
	mutex_unlock(&dev->काष्ठा_mutex);
	वापस ret;
पूर्ण

/*
 * Context biपंचांगap initialization.
 *
 * \param dev DRM device.
 *
 * Initialise the drm_device::ctx_idr
 */
व्योम drm_legacy_ctxbiपंचांगap_init(काष्ठा drm_device * dev)
अणु
	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस;

	idr_init(&dev->ctx_idr);
पूर्ण

/*
 * Context biपंचांगap cleanup.
 *
 * \param dev DRM device.
 *
 * Free all idr members using drm_ctx_sarea_मुक्त helper function
 * जबतक holding the drm_device::काष्ठा_mutex lock.
 */
व्योम drm_legacy_ctxbiपंचांगap_cleanup(काष्ठा drm_device * dev)
अणु
	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस;

	mutex_lock(&dev->काष्ठा_mutex);
	idr_destroy(&dev->ctx_idr);
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण

/**
 * drm_ctxbiपंचांगap_flush() - Flush all contexts owned by a file
 * @dev: DRM device to operate on
 * @file: Open file to flush contexts क्रम
 *
 * This iterates over all contexts on @dev and drops them अगर they're owned by
 * @file. Note that after this call वापसs, new contexts might be added अगर
 * the file is still alive.
 */
व्योम drm_legacy_ctxbiपंचांगap_flush(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा drm_ctx_list *pos, *पंचांगp;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस;

	mutex_lock(&dev->ctxlist_mutex);

	list_क्रम_each_entry_safe(pos, पंचांगp, &dev->ctxlist, head) अणु
		अगर (pos->tag == file &&
		    pos->handle != DRM_KERNEL_CONTEXT) अणु
			अगर (dev->driver->context_dtor)
				dev->driver->context_dtor(dev, pos->handle);

			drm_legacy_ctxbiपंचांगap_मुक्त(dev, pos->handle);
			list_del(&pos->head);
			kमुक्त(pos);
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->ctxlist_mutex);
पूर्ण

/*@पूर्ण*/

/******************************************************************/
/** \नame Per Context SAREA Support */
/*@अणु*/

/*
 * Get per-context SAREA.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument poपूर्णांकing to a drm_ctx_priv_map काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Gets the map from drm_device::ctx_idr with the handle specअगरied and
 * वापसs its handle.
 */
पूर्णांक drm_legacy_माला_लोareactx(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_ctx_priv_map *request = data;
	काष्ठा drm_local_map *map;
	काष्ठा drm_map_list *_entry;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	mutex_lock(&dev->काष्ठा_mutex);

	map = idr_find(&dev->ctx_idr, request->ctx_id);
	अगर (!map) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		वापस -EINVAL;
	पूर्ण

	request->handle = शून्य;
	list_क्रम_each_entry(_entry, &dev->maplist, head) अणु
		अगर (_entry->map == map) अणु
			request->handle =
			    (व्योम *)(अचिन्हित दीर्घ)_entry->user_token;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->काष्ठा_mutex);

	अगर (request->handle == शून्य)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Set per-context SAREA.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument poपूर्णांकing to a drm_ctx_priv_map काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Searches the mapping specअगरied in \p arg and update the entry in
 * drm_device::ctx_idr with it.
 */
पूर्णांक drm_legacy_setsareactx(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_ctx_priv_map *request = data;
	काष्ठा drm_local_map *map = शून्य;
	काष्ठा drm_map_list *r_list = शून्य;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	mutex_lock(&dev->काष्ठा_mutex);
	list_क्रम_each_entry(r_list, &dev->maplist, head) अणु
		अगर (r_list->map
		    && r_list->user_token == (अचिन्हित दीर्घ) request->handle)
			जाओ found;
	पूर्ण
      bad:
	mutex_unlock(&dev->काष्ठा_mutex);
	वापस -EINVAL;

      found:
	map = r_list->map;
	अगर (!map)
		जाओ bad;

	अगर (IS_ERR(idr_replace(&dev->ctx_idr, map, request->ctx_id)))
		जाओ bad;

	mutex_unlock(&dev->काष्ठा_mutex);

	वापस 0;
पूर्ण

/*@पूर्ण*/

/******************************************************************/
/** \नame The actual DRM context handling routines */
/*@अणु*/

/*
 * Switch context.
 *
 * \param dev DRM device.
 * \param old old context handle.
 * \param new new context handle.
 * \लeturn zero on success or a negative number on failure.
 *
 * Attempt to set drm_device::context_flag.
 */
अटल पूर्णांक drm_context_चयन(काष्ठा drm_device * dev, पूर्णांक old, पूर्णांक new)
अणु
	अगर (test_and_set_bit(0, &dev->context_flag)) अणु
		DRM_ERROR("Reentering -- FIXME\n");
		वापस -EBUSY;
	पूर्ण

	DRM_DEBUG("Context switch from %d to %d\n", old, new);

	अगर (new == dev->last_context) अणु
		clear_bit(0, &dev->context_flag);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Complete context चयन.
 *
 * \param dev DRM device.
 * \param new new context handle.
 * \लeturn zero on success or a negative number on failure.
 *
 * Updates drm_device::last_context and drm_device::last_चयन. Verअगरies the
 * hardware lock is held, clears the drm_device::context_flag and wakes up
 * drm_device::context_रुको.
 */
अटल पूर्णांक drm_context_चयन_complete(काष्ठा drm_device *dev,
				       काष्ठा drm_file *file_priv, पूर्णांक new)
अणु
	dev->last_context = new;	/* PRE/POST: This is the _only_ ग_लिखोr. */

	अगर (!_DRM_LOCK_IS_HELD(file_priv->master->lock.hw_lock->lock)) अणु
		DRM_ERROR("Lock isn't held after context switch\n");
	पूर्ण

	/* If a context चयन is ever initiated
	   when the kernel holds the lock, release
	   that lock here. */
	clear_bit(0, &dev->context_flag);

	वापस 0;
पूर्ण

/*
 * Reserve contexts.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument poपूर्णांकing to a drm_ctx_res काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 */
पूर्णांक drm_legacy_resctx(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_ctx_res *res = data;
	काष्ठा drm_ctx ctx;
	पूर्णांक i;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	अगर (res->count >= DRM_RESERVED_CONTEXTS) अणु
		स_रखो(&ctx, 0, माप(ctx));
		क्रम (i = 0; i < DRM_RESERVED_CONTEXTS; i++) अणु
			ctx.handle = i;
			अगर (copy_to_user(&res->contexts[i], &ctx, माप(ctx)))
				वापस -EFAULT;
		पूर्ण
	पूर्ण
	res->count = DRM_RESERVED_CONTEXTS;

	वापस 0;
पूर्ण

/*
 * Add context.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument poपूर्णांकing to a drm_ctx काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Get a new handle क्रम the context and copy to userspace.
 */
पूर्णांक drm_legacy_addctx(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_ctx_list *ctx_entry;
	काष्ठा drm_ctx *ctx = data;
	पूर्णांक पंचांगp_handle;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	पंचांगp_handle = drm_legacy_ctxbiपंचांगap_next(dev);
	अगर (पंचांगp_handle == DRM_KERNEL_CONTEXT) अणु
		/* Skip kernel's context and get a new one. */
		पंचांगp_handle = drm_legacy_ctxbiपंचांगap_next(dev);
	पूर्ण
	DRM_DEBUG("%d\n", पंचांगp_handle);
	अगर (पंचांगp_handle < 0) अणु
		DRM_DEBUG("Not enough free contexts.\n");
		/* Should this वापस -EBUSY instead? */
		वापस पंचांगp_handle;
	पूर्ण

	ctx->handle = पंचांगp_handle;

	ctx_entry = kदो_स्मृति(माप(*ctx_entry), GFP_KERNEL);
	अगर (!ctx_entry) अणु
		DRM_DEBUG("out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&ctx_entry->head);
	ctx_entry->handle = ctx->handle;
	ctx_entry->tag = file_priv;

	mutex_lock(&dev->ctxlist_mutex);
	list_add(&ctx_entry->head, &dev->ctxlist);
	mutex_unlock(&dev->ctxlist_mutex);

	वापस 0;
पूर्ण

/*
 * Get context.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument poपूर्णांकing to a drm_ctx काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 */
पूर्णांक drm_legacy_अ_लोtx(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_ctx *ctx = data;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	/* This is 0, because we करोn't handle any context flags */
	ctx->flags = 0;

	वापस 0;
पूर्ण

/*
 * Switch context.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument poपूर्णांकing to a drm_ctx काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Calls context_चयन().
 */
पूर्णांक drm_legacy_चयनctx(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_ctx *ctx = data;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	DRM_DEBUG("%d\n", ctx->handle);
	वापस drm_context_चयन(dev, dev->last_context, ctx->handle);
पूर्ण

/*
 * New context.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument poपूर्णांकing to a drm_ctx काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * Calls context_चयन_complete().
 */
पूर्णांक drm_legacy_newctx(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_ctx *ctx = data;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	DRM_DEBUG("%d\n", ctx->handle);
	drm_context_चयन_complete(dev, file_priv, ctx->handle);

	वापस 0;
पूर्ण

/*
 * Remove context.
 *
 * \param inode device inode.
 * \param file_priv DRM file निजी.
 * \param cmd command.
 * \param arg user argument poपूर्णांकing to a drm_ctx काष्ठाure.
 * \लeturn zero on success or a negative number on failure.
 *
 * If not the special kernel context, calls ctxbiपंचांगap_मुक्त() to मुक्त the specअगरied context.
 */
पूर्णांक drm_legacy_rmctx(काष्ठा drm_device *dev, व्योम *data,
		     काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_ctx *ctx = data;

	अगर (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	DRM_DEBUG("%d\n", ctx->handle);
	अगर (ctx->handle != DRM_KERNEL_CONTEXT) अणु
		अगर (dev->driver->context_dtor)
			dev->driver->context_dtor(dev, ctx->handle);
		drm_legacy_ctxbiपंचांगap_मुक्त(dev, ctx->handle);
	पूर्ण

	mutex_lock(&dev->ctxlist_mutex);
	अगर (!list_empty(&dev->ctxlist)) अणु
		काष्ठा drm_ctx_list *pos, *n;

		list_क्रम_each_entry_safe(pos, n, &dev->ctxlist, head) अणु
			अगर (pos->handle == ctx->handle) अणु
				list_del(&pos->head);
				kमुक्त(pos);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->ctxlist_mutex);

	वापस 0;
पूर्ण

/*@पूर्ण*/
