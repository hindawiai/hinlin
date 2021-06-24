<शैली गुरु>
/*
 * Copyright तऊ 2012 Red Hat
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *      Dave Airlie <airlied@redhat.com>
 *      Rob Clark <rob.clark@linaro.org>
 *
 */

#समावेश <linux/export.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/rbtree.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_prime.h>

#समावेश "drm_internal.h"

/**
 * DOC: overview and lअगरeसमय rules
 *
 * Similar to GEM global names, PRIME file descriptors are also used to share
 * buffer objects across processes. They offer additional security: as file
 * descriptors must be explicitly sent over UNIX करोमुख्य sockets to be shared
 * between applications, they can't be guessed like the globally unique GEM
 * names.
 *
 * Drivers that support the PRIME API implement the
 * &drm_driver.prime_handle_to_fd and &drm_driver.prime_fd_to_handle operations.
 * GEM based drivers must use drm_gem_prime_handle_to_fd() and
 * drm_gem_prime_fd_to_handle() to implement these. For GEM based drivers the
 * actual driver पूर्णांकerfaces is provided through the &drm_gem_object_funcs.export
 * and &drm_driver.gem_prime_import hooks.
 *
 * &dma_buf_ops implementations क्रम GEM drivers are all inभागidually exported
 * क्रम drivers which need to overग_लिखो or reimplement some of them.
 *
 * Reference Counting क्रम GEM Drivers
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * On the export the &dma_buf holds a reference to the exported buffer object,
 * usually a &drm_gem_object. It takes this reference in the PRIME_HANDLE_TO_FD
 * IOCTL, when it first calls &drm_gem_object_funcs.export
 * and stores the exporting GEM object in the &dma_buf.priv field. This
 * reference needs to be released when the final reference to the &dma_buf
 * itself is dropped and its &dma_buf_ops.release function is called.  For
 * GEM-based drivers, the &dma_buf should be exported using
 * drm_gem_dmabuf_export() and then released by drm_gem_dmabuf_release().
 *
 * Thus the chain of references always flows in one direction, aव्योमing loops:
 * importing GEM object -> dma-buf -> exported GEM bo. A further complication
 * are the lookup caches क्रम import and export. These are required to guarantee
 * that any given object will always have only one uniqe userspace handle. This
 * is required to allow userspace to detect duplicated imports, since some GEM
 * drivers करो fail command submissions अगर a given buffer object is listed more
 * than once. These import and export caches in &drm_prime_file_निजी only
 * retain a weak reference, which is cleaned up when the corresponding object is
 * released.
 *
 * Self-importing: If userspace is using PRIME as a replacement क्रम flink then
 * it will get a fd->handle request क्रम a GEM object that it created.  Drivers
 * should detect this situation and वापस back the underlying object from the
 * dma-buf निजी. For GEM based drivers this is handled in
 * drm_gem_prime_import() alपढ़ोy.
 */

काष्ठा drm_prime_member अणु
	काष्ठा dma_buf *dma_buf;
	uपूर्णांक32_t handle;

	काष्ठा rb_node dmabuf_rb;
	काष्ठा rb_node handle_rb;
पूर्ण;

अटल पूर्णांक drm_prime_add_buf_handle(काष्ठा drm_prime_file_निजी *prime_fpriv,
				    काष्ठा dma_buf *dma_buf, uपूर्णांक32_t handle)
अणु
	काष्ठा drm_prime_member *member;
	काष्ठा rb_node **p, *rb;

	member = kदो_स्मृति(माप(*member), GFP_KERNEL);
	अगर (!member)
		वापस -ENOMEM;

	get_dma_buf(dma_buf);
	member->dma_buf = dma_buf;
	member->handle = handle;

	rb = शून्य;
	p = &prime_fpriv->dmabufs.rb_node;
	जबतक (*p) अणु
		काष्ठा drm_prime_member *pos;

		rb = *p;
		pos = rb_entry(rb, काष्ठा drm_prime_member, dmabuf_rb);
		अगर (dma_buf > pos->dma_buf)
			p = &rb->rb_right;
		अन्यथा
			p = &rb->rb_left;
	पूर्ण
	rb_link_node(&member->dmabuf_rb, rb, p);
	rb_insert_color(&member->dmabuf_rb, &prime_fpriv->dmabufs);

	rb = शून्य;
	p = &prime_fpriv->handles.rb_node;
	जबतक (*p) अणु
		काष्ठा drm_prime_member *pos;

		rb = *p;
		pos = rb_entry(rb, काष्ठा drm_prime_member, handle_rb);
		अगर (handle > pos->handle)
			p = &rb->rb_right;
		अन्यथा
			p = &rb->rb_left;
	पूर्ण
	rb_link_node(&member->handle_rb, rb, p);
	rb_insert_color(&member->handle_rb, &prime_fpriv->handles);

	वापस 0;
पूर्ण

अटल काष्ठा dma_buf *drm_prime_lookup_buf_by_handle(काष्ठा drm_prime_file_निजी *prime_fpriv,
						      uपूर्णांक32_t handle)
अणु
	काष्ठा rb_node *rb;

	rb = prime_fpriv->handles.rb_node;
	जबतक (rb) अणु
		काष्ठा drm_prime_member *member;

		member = rb_entry(rb, काष्ठा drm_prime_member, handle_rb);
		अगर (member->handle == handle)
			वापस member->dma_buf;
		अन्यथा अगर (member->handle < handle)
			rb = rb->rb_right;
		अन्यथा
			rb = rb->rb_left;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक drm_prime_lookup_buf_handle(काष्ठा drm_prime_file_निजी *prime_fpriv,
				       काष्ठा dma_buf *dma_buf,
				       uपूर्णांक32_t *handle)
अणु
	काष्ठा rb_node *rb;

	rb = prime_fpriv->dmabufs.rb_node;
	जबतक (rb) अणु
		काष्ठा drm_prime_member *member;

		member = rb_entry(rb, काष्ठा drm_prime_member, dmabuf_rb);
		अगर (member->dma_buf == dma_buf) अणु
			*handle = member->handle;
			वापस 0;
		पूर्ण अन्यथा अगर (member->dma_buf < dma_buf) अणु
			rb = rb->rb_right;
		पूर्ण अन्यथा अणु
			rb = rb->rb_left;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

व्योम drm_prime_हटाओ_buf_handle_locked(काष्ठा drm_prime_file_निजी *prime_fpriv,
					काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा rb_node *rb;

	rb = prime_fpriv->dmabufs.rb_node;
	जबतक (rb) अणु
		काष्ठा drm_prime_member *member;

		member = rb_entry(rb, काष्ठा drm_prime_member, dmabuf_rb);
		अगर (member->dma_buf == dma_buf) अणु
			rb_erase(&member->handle_rb, &prime_fpriv->handles);
			rb_erase(&member->dmabuf_rb, &prime_fpriv->dmabufs);

			dma_buf_put(dma_buf);
			kमुक्त(member);
			वापस;
		पूर्ण अन्यथा अगर (member->dma_buf < dma_buf) अणु
			rb = rb->rb_right;
		पूर्ण अन्यथा अणु
			rb = rb->rb_left;
		पूर्ण
	पूर्ण
पूर्ण

व्योम drm_prime_init_file_निजी(काष्ठा drm_prime_file_निजी *prime_fpriv)
अणु
	mutex_init(&prime_fpriv->lock);
	prime_fpriv->dmabufs = RB_ROOT;
	prime_fpriv->handles = RB_ROOT;
पूर्ण

व्योम drm_prime_destroy_file_निजी(काष्ठा drm_prime_file_निजी *prime_fpriv)
अणु
	/* by now drm_gem_release should've made sure the list is empty */
	WARN_ON(!RB_EMPTY_ROOT(&prime_fpriv->dmabufs));
पूर्ण

/**
 * drm_gem_dmabuf_export - &dma_buf export implementation क्रम GEM
 * @dev: parent device क्रम the exported dmabuf
 * @exp_info: the export inक्रमmation used by dma_buf_export()
 *
 * This wraps dma_buf_export() क्रम use by generic GEM drivers that are using
 * drm_gem_dmabuf_release(). In addition to calling dma_buf_export(), we take
 * a reference to the &drm_device and the exported &drm_gem_object (stored in
 * &dma_buf_export_info.priv) which is released by drm_gem_dmabuf_release().
 *
 * Returns the new dmabuf.
 */
काष्ठा dma_buf *drm_gem_dmabuf_export(काष्ठा drm_device *dev,
				      काष्ठा dma_buf_export_info *exp_info)
अणु
	काष्ठा drm_gem_object *obj = exp_info->priv;
	काष्ठा dma_buf *dma_buf;

	dma_buf = dma_buf_export(exp_info);
	अगर (IS_ERR(dma_buf))
		वापस dma_buf;

	drm_dev_get(dev);
	drm_gem_object_get(obj);
	dma_buf->file->f_mapping = obj->dev->anon_inode->i_mapping;

	वापस dma_buf;
पूर्ण
EXPORT_SYMBOL(drm_gem_dmabuf_export);

/**
 * drm_gem_dmabuf_release - &dma_buf release implementation क्रम GEM
 * @dma_buf: buffer to be released
 *
 * Generic release function क्रम dma_bufs exported as PRIME buffers. GEM drivers
 * must use this in their &dma_buf_ops काष्ठाure as the release callback.
 * drm_gem_dmabuf_release() should be used in conjunction with
 * drm_gem_dmabuf_export().
 */
व्योम drm_gem_dmabuf_release(काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा drm_gem_object *obj = dma_buf->priv;
	काष्ठा drm_device *dev = obj->dev;

	/* drop the reference on the export fd holds */
	drm_gem_object_put(obj);

	drm_dev_put(dev);
पूर्ण
EXPORT_SYMBOL(drm_gem_dmabuf_release);

/**
 * drm_gem_prime_fd_to_handle - PRIME import function क्रम GEM drivers
 * @dev: dev to export the buffer from
 * @file_priv: drm file-निजी काष्ठाure
 * @prime_fd: fd id of the dma-buf which should be imported
 * @handle: poपूर्णांकer to storage क्रम the handle of the imported buffer object
 *
 * This is the PRIME import function which must be used mandatorily by GEM
 * drivers to ensure correct lअगरeसमय management of the underlying GEM object.
 * The actual importing of GEM object from the dma-buf is करोne through the
 * &drm_driver.gem_prime_import driver callback.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_prime_fd_to_handle(काष्ठा drm_device *dev,
			       काष्ठा drm_file *file_priv, पूर्णांक prime_fd,
			       uपूर्णांक32_t *handle)
अणु
	काष्ठा dma_buf *dma_buf;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	dma_buf = dma_buf_get(prime_fd);
	अगर (IS_ERR(dma_buf))
		वापस PTR_ERR(dma_buf);

	mutex_lock(&file_priv->prime.lock);

	ret = drm_prime_lookup_buf_handle(&file_priv->prime,
			dma_buf, handle);
	अगर (ret == 0)
		जाओ out_put;

	/* never seen this one, need to import */
	mutex_lock(&dev->object_name_lock);
	अगर (dev->driver->gem_prime_import)
		obj = dev->driver->gem_prime_import(dev, dma_buf);
	अन्यथा
		obj = drm_gem_prime_import(dev, dma_buf);
	अगर (IS_ERR(obj)) अणु
		ret = PTR_ERR(obj);
		जाओ out_unlock;
	पूर्ण

	अगर (obj->dma_buf) अणु
		WARN_ON(obj->dma_buf != dma_buf);
	पूर्ण अन्यथा अणु
		obj->dma_buf = dma_buf;
		get_dma_buf(dma_buf);
	पूर्ण

	/* _handle_create_tail unconditionally unlocks dev->object_name_lock. */
	ret = drm_gem_handle_create_tail(file_priv, obj, handle);
	drm_gem_object_put(obj);
	अगर (ret)
		जाओ out_put;

	ret = drm_prime_add_buf_handle(&file_priv->prime,
			dma_buf, *handle);
	mutex_unlock(&file_priv->prime.lock);
	अगर (ret)
		जाओ fail;

	dma_buf_put(dma_buf);

	वापस 0;

fail:
	/* hmm, अगर driver attached, we are relying on the मुक्त-object path
	 * to detach.. which seems ok..
	 */
	drm_gem_handle_delete(file_priv, *handle);
	dma_buf_put(dma_buf);
	वापस ret;

out_unlock:
	mutex_unlock(&dev->object_name_lock);
out_put:
	mutex_unlock(&file_priv->prime.lock);
	dma_buf_put(dma_buf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_prime_fd_to_handle);

पूर्णांक drm_prime_fd_to_handle_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_prime_handle *args = data;

	अगर (!dev->driver->prime_fd_to_handle)
		वापस -ENOSYS;

	वापस dev->driver->prime_fd_to_handle(dev, file_priv,
			args->fd, &args->handle);
पूर्ण

अटल काष्ठा dma_buf *export_and_रेजिस्टर_object(काष्ठा drm_device *dev,
						  काष्ठा drm_gem_object *obj,
						  uपूर्णांक32_t flags)
अणु
	काष्ठा dma_buf *dmabuf;

	/* prevent races with concurrent gem_बंद. */
	अगर (obj->handle_count == 0) अणु
		dmabuf = ERR_PTR(-ENOENT);
		वापस dmabuf;
	पूर्ण

	अगर (obj->funcs && obj->funcs->export)
		dmabuf = obj->funcs->export(obj, flags);
	अन्यथा
		dmabuf = drm_gem_prime_export(obj, flags);
	अगर (IS_ERR(dmabuf)) अणु
		/* normally the created dma-buf takes ownership of the ref,
		 * but अगर that fails then drop the ref
		 */
		वापस dmabuf;
	पूर्ण

	/*
	 * Note that callers करो not need to clean up the export cache
	 * since the check क्रम obj->handle_count guarantees that someone
	 * will clean it up.
	 */
	obj->dma_buf = dmabuf;
	get_dma_buf(obj->dma_buf);

	वापस dmabuf;
पूर्ण

/**
 * drm_gem_prime_handle_to_fd - PRIME export function क्रम GEM drivers
 * @dev: dev to export the buffer from
 * @file_priv: drm file-निजी काष्ठाure
 * @handle: buffer handle to export
 * @flags: flags like DRM_CLOEXEC
 * @prime_fd: poपूर्णांकer to storage क्रम the fd id of the create dma-buf
 *
 * This is the PRIME export function which must be used mandatorily by GEM
 * drivers to ensure correct lअगरeसमय management of the underlying GEM object.
 * The actual exporting from GEM object to a dma-buf is करोne through the
 * &drm_gem_object_funcs.export callback.
 */
पूर्णांक drm_gem_prime_handle_to_fd(काष्ठा drm_device *dev,
			       काष्ठा drm_file *file_priv, uपूर्णांक32_t handle,
			       uपूर्णांक32_t flags,
			       पूर्णांक *prime_fd)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret = 0;
	काष्ठा dma_buf *dmabuf;

	mutex_lock(&file_priv->prime.lock);
	obj = drm_gem_object_lookup(file_priv, handle);
	अगर (!obj)  अणु
		ret = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	dmabuf = drm_prime_lookup_buf_by_handle(&file_priv->prime, handle);
	अगर (dmabuf) अणु
		get_dma_buf(dmabuf);
		जाओ out_have_handle;
	पूर्ण

	mutex_lock(&dev->object_name_lock);
	/* re-export the original imported object */
	अगर (obj->import_attach) अणु
		dmabuf = obj->import_attach->dmabuf;
		get_dma_buf(dmabuf);
		जाओ out_have_obj;
	पूर्ण

	अगर (obj->dma_buf) अणु
		get_dma_buf(obj->dma_buf);
		dmabuf = obj->dma_buf;
		जाओ out_have_obj;
	पूर्ण

	dmabuf = export_and_रेजिस्टर_object(dev, obj, flags);
	अगर (IS_ERR(dmabuf)) अणु
		/* normally the created dma-buf takes ownership of the ref,
		 * but अगर that fails then drop the ref
		 */
		ret = PTR_ERR(dmabuf);
		mutex_unlock(&dev->object_name_lock);
		जाओ out;
	पूर्ण

out_have_obj:
	/*
	 * If we've exported this buffer then cheat and add it to the import list
	 * so we get the correct handle back. We must करो this under the
	 * protection of dev->object_name_lock to ensure that a racing gem बंद
	 * ioctl करोesn't miss to हटाओ this buffer handle from the cache.
	 */
	ret = drm_prime_add_buf_handle(&file_priv->prime,
				       dmabuf, handle);
	mutex_unlock(&dev->object_name_lock);
	अगर (ret)
		जाओ fail_put_dmabuf;

out_have_handle:
	ret = dma_buf_fd(dmabuf, flags);
	/*
	 * We must _not_ हटाओ the buffer from the handle cache since the newly
	 * created dma buf is alपढ़ोy linked in the global obj->dma_buf poपूर्णांकer,
	 * and that is invariant as दीर्घ as a userspace gem handle exists.
	 * Closing the handle will clean out the cache anyway, so we करोn't leak.
	 */
	अगर (ret < 0) अणु
		जाओ fail_put_dmabuf;
	पूर्ण अन्यथा अणु
		*prime_fd = ret;
		ret = 0;
	पूर्ण

	जाओ out;

fail_put_dmabuf:
	dma_buf_put(dmabuf);
out:
	drm_gem_object_put(obj);
out_unlock:
	mutex_unlock(&file_priv->prime.lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_prime_handle_to_fd);

पूर्णांक drm_prime_handle_to_fd_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_prime_handle *args = data;

	अगर (!dev->driver->prime_handle_to_fd)
		वापस -ENOSYS;

	/* check flags are valid */
	अगर (args->flags & ~(DRM_CLOEXEC | DRM_RDWR))
		वापस -EINVAL;

	वापस dev->driver->prime_handle_to_fd(dev, file_priv,
			args->handle, args->flags, &args->fd);
पूर्ण

/**
 * DOC: PRIME Helpers
 *
 * Drivers can implement &drm_gem_object_funcs.export and
 * &drm_driver.gem_prime_import in terms of simpler APIs by using the helper
 * functions drm_gem_prime_export() and drm_gem_prime_import(). These functions
 * implement dma-buf support in terms of some lower-level helpers, which are
 * again exported क्रम drivers to use inभागidually:
 *
 * Exporting buffers
 * ~~~~~~~~~~~~~~~~~
 *
 * Optional pinning of buffers is handled at dma-buf attach and detach समय in
 * drm_gem_map_attach() and drm_gem_map_detach(). Backing storage itself is
 * handled by drm_gem_map_dma_buf() and drm_gem_unmap_dma_buf(), which relies on
 * &drm_gem_object_funcs.get_sg_table.
 *
 * For kernel-पूर्णांकernal access there's drm_gem_dmabuf_vmap() and
 * drm_gem_dmabuf_vunmap(). Userspace mmap support is provided by
 * drm_gem_dmabuf_mmap().
 *
 * Note that these export helpers can only be used अगर the underlying backing
 * storage is fully coherent and either permanently pinned, or it is safe to pin
 * it indefinitely.
 *
 * FIXME: The underlying helper functions are named rather inconsistently.
 *
 * Exporting buffers
 * ~~~~~~~~~~~~~~~~~
 *
 * Importing dma-bufs using drm_gem_prime_import() relies on
 * &drm_driver.gem_prime_import_sg_table.
 *
 * Note that similarly to the export helpers this permanently pins the
 * underlying backing storage. Which is ok क्रम scanout, but is not the best
 * option क्रम sharing lots of buffers क्रम rendering.
 */

/**
 * drm_gem_map_attach - dma_buf attach implementation क्रम GEM
 * @dma_buf: buffer to attach device to
 * @attach: buffer attachment data
 *
 * Calls &drm_gem_object_funcs.pin क्रम device specअगरic handling. This can be
 * used as the &dma_buf_ops.attach callback. Must be used together with
 * drm_gem_map_detach().
 *
 * Returns 0 on success, negative error code on failure.
 */
पूर्णांक drm_gem_map_attach(काष्ठा dma_buf *dma_buf,
		       काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा drm_gem_object *obj = dma_buf->priv;

	वापस drm_gem_pin(obj);
पूर्ण
EXPORT_SYMBOL(drm_gem_map_attach);

/**
 * drm_gem_map_detach - dma_buf detach implementation क्रम GEM
 * @dma_buf: buffer to detach from
 * @attach: attachment to be detached
 *
 * Calls &drm_gem_object_funcs.pin क्रम device specअगरic handling.  Cleans up
 * &dma_buf_attachment from drm_gem_map_attach(). This can be used as the
 * &dma_buf_ops.detach callback.
 */
व्योम drm_gem_map_detach(काष्ठा dma_buf *dma_buf,
			काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा drm_gem_object *obj = dma_buf->priv;

	drm_gem_unpin(obj);
पूर्ण
EXPORT_SYMBOL(drm_gem_map_detach);

/**
 * drm_gem_map_dma_buf - map_dma_buf implementation क्रम GEM
 * @attach: attachment whose scatterlist is to be वापसed
 * @dir: direction of DMA transfer
 *
 * Calls &drm_gem_object_funcs.get_sg_table and then maps the scatterlist. This
 * can be used as the &dma_buf_ops.map_dma_buf callback. Should be used together
 * with drm_gem_unmap_dma_buf().
 *
 * Returns:sg_table containing the scatterlist to be वापसed; वापसs ERR_PTR
 * on error. May वापस -EINTR अगर it is पूर्णांकerrupted by a संकेत.
 */
काष्ठा sg_table *drm_gem_map_dma_buf(काष्ठा dma_buf_attachment *attach,
				     क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_gem_object *obj = attach->dmabuf->priv;
	काष्ठा sg_table *sgt;
	पूर्णांक ret;

	अगर (WARN_ON(dir == DMA_NONE))
		वापस ERR_PTR(-EINVAL);

	अगर (WARN_ON(!obj->funcs->get_sg_table))
		वापस ERR_PTR(-ENOSYS);

	sgt = obj->funcs->get_sg_table(obj);
	अगर (IS_ERR(sgt))
		वापस sgt;

	ret = dma_map_sgtable(attach->dev, sgt, dir,
			      DMA_ATTR_SKIP_CPU_SYNC);
	अगर (ret) अणु
		sg_मुक्त_table(sgt);
		kमुक्त(sgt);
		sgt = ERR_PTR(ret);
	पूर्ण

	वापस sgt;
पूर्ण
EXPORT_SYMBOL(drm_gem_map_dma_buf);

/**
 * drm_gem_unmap_dma_buf - unmap_dma_buf implementation क्रम GEM
 * @attach: attachment to unmap buffer from
 * @sgt: scatterlist info of the buffer to unmap
 * @dir: direction of DMA transfer
 *
 * This can be used as the &dma_buf_ops.unmap_dma_buf callback.
 */
व्योम drm_gem_unmap_dma_buf(काष्ठा dma_buf_attachment *attach,
			   काष्ठा sg_table *sgt,
			   क्रमागत dma_data_direction dir)
अणु
	अगर (!sgt)
		वापस;

	dma_unmap_sgtable(attach->dev, sgt, dir, DMA_ATTR_SKIP_CPU_SYNC);
	sg_मुक्त_table(sgt);
	kमुक्त(sgt);
पूर्ण
EXPORT_SYMBOL(drm_gem_unmap_dma_buf);

/**
 * drm_gem_dmabuf_vmap - dma_buf vmap implementation क्रम GEM
 * @dma_buf: buffer to be mapped
 * @map: the भव address of the buffer
 *
 * Sets up a kernel भव mapping. This can be used as the &dma_buf_ops.vmap
 * callback. Calls पूर्णांकo &drm_gem_object_funcs.vmap क्रम device specअगरic handling.
 * The kernel भव address is वापसed in map.
 *
 * Returns 0 on success or a negative त्रुटि_सं code otherwise.
 */
पूर्णांक drm_gem_dmabuf_vmap(काष्ठा dma_buf *dma_buf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_object *obj = dma_buf->priv;

	वापस drm_gem_vmap(obj, map);
पूर्ण
EXPORT_SYMBOL(drm_gem_dmabuf_vmap);

/**
 * drm_gem_dmabuf_vunmap - dma_buf vunmap implementation क्रम GEM
 * @dma_buf: buffer to be unmapped
 * @map: the भव address of the buffer
 *
 * Releases a kernel भव mapping. This can be used as the
 * &dma_buf_ops.vunmap callback. Calls पूर्णांकo &drm_gem_object_funcs.vunmap क्रम device specअगरic handling.
 */
व्योम drm_gem_dmabuf_vunmap(काष्ठा dma_buf *dma_buf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_object *obj = dma_buf->priv;

	drm_gem_vunmap(obj, map);
पूर्ण
EXPORT_SYMBOL(drm_gem_dmabuf_vunmap);

/**
 * drm_gem_prime_mmap - PRIME mmap function क्रम GEM drivers
 * @obj: GEM object
 * @vma: Virtual address range
 *
 * This function sets up a userspace mapping क्रम PRIME exported buffers using
 * the same codepath that is used क्रम regular GEM buffer mapping on the DRM fd.
 * The fake GEM offset is added to vma->vm_pgoff and &drm_driver->fops->mmap is
 * called to set up the mapping.
 *
 * Drivers can use this as their &drm_driver.gem_prime_mmap callback.
 */
पूर्णांक drm_gem_prime_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *priv;
	काष्ठा file *fil;
	पूर्णांक ret;

	/* Add the fake offset */
	vma->vm_pgoff += drm_vma_node_start(&obj->vma_node);

	अगर (obj->funcs && obj->funcs->mmap) अणु
		vma->vm_ops = obj->funcs->vm_ops;

		ret = obj->funcs->mmap(obj, vma);
		अगर (ret)
			वापस ret;
		vma->vm_निजी_data = obj;
		drm_gem_object_get(obj);
		वापस 0;
	पूर्ण

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	fil = kzalloc(माप(*fil), GFP_KERNEL);
	अगर (!priv || !fil) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Used by drm_gem_mmap() to lookup the GEM object */
	priv->minor = obj->dev->primary;
	fil->निजी_data = priv;

	ret = drm_vma_node_allow(&obj->vma_node, priv);
	अगर (ret)
		जाओ out;

	ret = obj->dev->driver->fops->mmap(fil, vma);

	drm_vma_node_revoke(&obj->vma_node, priv);
out:
	kमुक्त(priv);
	kमुक्त(fil);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_prime_mmap);

/**
 * drm_gem_dmabuf_mmap - dma_buf mmap implementation क्रम GEM
 * @dma_buf: buffer to be mapped
 * @vma: भव address range
 *
 * Provides memory mapping क्रम the buffer. This can be used as the
 * &dma_buf_ops.mmap callback. It just क्रमwards to &drm_driver.gem_prime_mmap,
 * which should be set to drm_gem_prime_mmap().
 *
 * FIXME: There's really no poपूर्णांक to this wrapper, drivers which need anything
 * अन्यथा but drm_gem_prime_mmap can roll their own &dma_buf_ops.mmap callback.
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_dmabuf_mmap(काष्ठा dma_buf *dma_buf, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *obj = dma_buf->priv;
	काष्ठा drm_device *dev = obj->dev;

	अगर (!dev->driver->gem_prime_mmap)
		वापस -ENOSYS;

	वापस dev->driver->gem_prime_mmap(obj, vma);
पूर्ण
EXPORT_SYMBOL(drm_gem_dmabuf_mmap);

अटल स्थिर काष्ठा dma_buf_ops drm_gem_prime_dmabuf_ops =  अणु
	.cache_sgt_mapping = true,
	.attach = drm_gem_map_attach,
	.detach = drm_gem_map_detach,
	.map_dma_buf = drm_gem_map_dma_buf,
	.unmap_dma_buf = drm_gem_unmap_dma_buf,
	.release = drm_gem_dmabuf_release,
	.mmap = drm_gem_dmabuf_mmap,
	.vmap = drm_gem_dmabuf_vmap,
	.vunmap = drm_gem_dmabuf_vunmap,
पूर्ण;

/**
 * drm_prime_pages_to_sg - converts a page array पूर्णांकo an sg list
 * @dev: DRM device
 * @pages: poपूर्णांकer to the array of page poपूर्णांकers to convert
 * @nr_pages: length of the page vector
 *
 * This helper creates an sg table object from a set of pages
 * the driver is responsible क्रम mapping the pages पूर्णांकo the
 * importers address space क्रम use with dma_buf itself.
 *
 * This is useful क्रम implementing &drm_gem_object_funcs.get_sg_table.
 */
काष्ठा sg_table *drm_prime_pages_to_sg(काष्ठा drm_device *dev,
				       काष्ठा page **pages, अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा sg_table *sg;
	काष्ठा scatterlist *sge;
	माप_प्रकार max_segment = 0;

	sg = kदो_स्मृति(माप(काष्ठा sg_table), GFP_KERNEL);
	अगर (!sg)
		वापस ERR_PTR(-ENOMEM);

	अगर (dev)
		max_segment = dma_max_mapping_size(dev->dev);
	अगर (max_segment == 0)
		max_segment = अच_पूर्णांक_उच्च;
	sge = __sg_alloc_table_from_pages(sg, pages, nr_pages, 0,
					  nr_pages << PAGE_SHIFT,
					  max_segment,
					  शून्य, 0, GFP_KERNEL);
	अगर (IS_ERR(sge)) अणु
		kमुक्त(sg);
		sg = ERR_CAST(sge);
	पूर्ण
	वापस sg;
पूर्ण
EXPORT_SYMBOL(drm_prime_pages_to_sg);

/**
 * drm_prime_get_contiguous_size - वापसs the contiguous size of the buffer
 * @sgt: sg_table describing the buffer to check
 *
 * This helper calculates the contiguous size in the DMA address space
 * of the the buffer described by the provided sg_table.
 *
 * This is useful क्रम implementing
 * &drm_gem_object_funcs.gem_prime_import_sg_table.
 */
अचिन्हित दीर्घ drm_prime_get_contiguous_size(काष्ठा sg_table *sgt)
अणु
	dma_addr_t expected = sg_dma_address(sgt->sgl);
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ size = 0;
	पूर्णांक i;

	क्रम_each_sgtable_dma_sg(sgt, sg, i) अणु
		अचिन्हित पूर्णांक len = sg_dma_len(sg);

		अगर (!len)
			अवरोध;
		अगर (sg_dma_address(sg) != expected)
			अवरोध;
		expected += len;
		size += len;
	पूर्ण
	वापस size;
पूर्ण
EXPORT_SYMBOL(drm_prime_get_contiguous_size);

/**
 * drm_gem_prime_export - helper library implementation of the export callback
 * @obj: GEM object to export
 * @flags: flags like DRM_CLOEXEC and DRM_RDWR
 *
 * This is the implementation of the &drm_gem_object_funcs.export functions क्रम GEM drivers
 * using the PRIME helpers. It is used as the शेष in
 * drm_gem_prime_handle_to_fd().
 */
काष्ठा dma_buf *drm_gem_prime_export(काष्ठा drm_gem_object *obj,
				     पूर्णांक flags)
अणु
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा dma_buf_export_info exp_info = अणु
		.exp_name = KBUILD_MODNAME, /* white lie क्रम debug */
		.owner = dev->driver->fops->owner,
		.ops = &drm_gem_prime_dmabuf_ops,
		.size = obj->size,
		.flags = flags,
		.priv = obj,
		.resv = obj->resv,
	पूर्ण;

	वापस drm_gem_dmabuf_export(dev, &exp_info);
पूर्ण
EXPORT_SYMBOL(drm_gem_prime_export);

/**
 * drm_gem_prime_import_dev - core implementation of the import callback
 * @dev: drm_device to import पूर्णांकo
 * @dma_buf: dma-buf object to import
 * @attach_dev: काष्ठा device to dma_buf attach
 *
 * This is the core of drm_gem_prime_import(). It's deचिन्हित to be called by
 * drivers who want to use a dअगरferent device काष्ठाure than &drm_device.dev क्रम
 * attaching via dma_buf. This function calls
 * &drm_driver.gem_prime_import_sg_table पूर्णांकernally.
 *
 * Drivers must arrange to call drm_prime_gem_destroy() from their
 * &drm_gem_object_funcs.मुक्त hook when using this function.
 */
काष्ठा drm_gem_object *drm_gem_prime_import_dev(काष्ठा drm_device *dev,
					    काष्ठा dma_buf *dma_buf,
					    काष्ठा device *attach_dev)
अणु
	काष्ठा dma_buf_attachment *attach;
	काष्ठा sg_table *sgt;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	अगर (dma_buf->ops == &drm_gem_prime_dmabuf_ops) अणु
		obj = dma_buf->priv;
		अगर (obj->dev == dev) अणु
			/*
			 * Importing dmabuf exported from out own gem increases
			 * refcount on gem itself instead of f_count of dmabuf.
			 */
			drm_gem_object_get(obj);
			वापस obj;
		पूर्ण
	पूर्ण

	अगर (!dev->driver->gem_prime_import_sg_table)
		वापस ERR_PTR(-EINVAL);

	attach = dma_buf_attach(dma_buf, attach_dev);
	अगर (IS_ERR(attach))
		वापस ERR_CAST(attach);

	get_dma_buf(dma_buf);

	sgt = dma_buf_map_attachment(attach, DMA_BIसूचीECTIONAL);
	अगर (IS_ERR(sgt)) अणु
		ret = PTR_ERR(sgt);
		जाओ fail_detach;
	पूर्ण

	obj = dev->driver->gem_prime_import_sg_table(dev, attach, sgt);
	अगर (IS_ERR(obj)) अणु
		ret = PTR_ERR(obj);
		जाओ fail_unmap;
	पूर्ण

	obj->import_attach = attach;
	obj->resv = dma_buf->resv;

	वापस obj;

fail_unmap:
	dma_buf_unmap_attachment(attach, sgt, DMA_BIसूचीECTIONAL);
fail_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(drm_gem_prime_import_dev);

/**
 * drm_gem_prime_import - helper library implementation of the import callback
 * @dev: drm_device to import पूर्णांकo
 * @dma_buf: dma-buf object to import
 *
 * This is the implementation of the gem_prime_import functions क्रम GEM drivers
 * using the PRIME helpers. Drivers can use this as their
 * &drm_driver.gem_prime_import implementation. It is used as the शेष
 * implementation in drm_gem_prime_fd_to_handle().
 *
 * Drivers must arrange to call drm_prime_gem_destroy() from their
 * &drm_gem_object_funcs.मुक्त hook when using this function.
 */
काष्ठा drm_gem_object *drm_gem_prime_import(काष्ठा drm_device *dev,
					    काष्ठा dma_buf *dma_buf)
अणु
	वापस drm_gem_prime_import_dev(dev, dma_buf, dev->dev);
पूर्ण
EXPORT_SYMBOL(drm_gem_prime_import);

/**
 * drm_prime_sg_to_page_array - convert an sg table पूर्णांकo a page array
 * @sgt: scatter-gather table to convert
 * @pages: array of page poपूर्णांकers to store the pages in
 * @max_entries: size of the passed-in array
 *
 * Exports an sg table पूर्णांकo an array of pages.
 *
 * This function is deprecated and strongly discouraged to be used.
 * The page array is only useful क्रम page faults and those can corrupt fields
 * in the काष्ठा page अगर they are not handled by the exporting driver.
 */
पूर्णांक __deprecated drm_prime_sg_to_page_array(काष्ठा sg_table *sgt,
					    काष्ठा page **pages,
					    पूर्णांक max_entries)
अणु
	काष्ठा sg_page_iter page_iter;
	काष्ठा page **p = pages;

	क्रम_each_sgtable_page(sgt, &page_iter, 0) अणु
		अगर (WARN_ON(p - pages >= max_entries))
			वापस -1;
		*p++ = sg_page_iter_page(&page_iter);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_prime_sg_to_page_array);

/**
 * drm_prime_sg_to_dma_addr_array - convert an sg table पूर्णांकo a dma addr array
 * @sgt: scatter-gather table to convert
 * @addrs: array to store the dma bus address of each page
 * @max_entries: size of both the passed-in arrays
 *
 * Exports an sg table पूर्णांकo an array of addresses.
 *
 * Drivers should use this in their &drm_driver.gem_prime_import_sg_table
 * implementation.
 */
पूर्णांक drm_prime_sg_to_dma_addr_array(काष्ठा sg_table *sgt, dma_addr_t *addrs,
				   पूर्णांक max_entries)
अणु
	काष्ठा sg_dma_page_iter dma_iter;
	dma_addr_t *a = addrs;

	क्रम_each_sgtable_dma_page(sgt, &dma_iter, 0) अणु
		अगर (WARN_ON(a - addrs >= max_entries))
			वापस -1;
		*a++ = sg_page_iter_dma_address(&dma_iter);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_prime_sg_to_dma_addr_array);

/**
 * drm_prime_gem_destroy - helper to clean up a PRIME-imported GEM object
 * @obj: GEM object which was created from a dma-buf
 * @sg: the sg-table which was pinned at import समय
 *
 * This is the cleanup functions which GEM drivers need to call when they use
 * drm_gem_prime_import() or drm_gem_prime_import_dev() to import dma-bufs.
 */
व्योम drm_prime_gem_destroy(काष्ठा drm_gem_object *obj, काष्ठा sg_table *sg)
अणु
	काष्ठा dma_buf_attachment *attach;
	काष्ठा dma_buf *dma_buf;

	attach = obj->import_attach;
	अगर (sg)
		dma_buf_unmap_attachment(attach, sg, DMA_BIसूचीECTIONAL);
	dma_buf = attach->dmabuf;
	dma_buf_detach(attach->dmabuf, attach);
	/* हटाओ the reference */
	dma_buf_put(dma_buf);
पूर्ण
EXPORT_SYMBOL(drm_prime_gem_destroy);
