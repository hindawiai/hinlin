<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or MIT
/*
 * Copyright 2018 Noralf Trथचnnes
 */

#समावेश <linux/dma-buf-map.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_client.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"

/**
 * DOC: overview
 *
 * This library provides support क्रम clients running in the kernel like fbdev and bootsplash.
 *
 * GEM drivers which provide a GEM based dumb buffer with a भव address are supported.
 */

अटल पूर्णांक drm_client_खोलो(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_device *dev = client->dev;
	काष्ठा drm_file *file;

	file = drm_file_alloc(dev->primary);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	mutex_lock(&dev->filelist_mutex);
	list_add(&file->lhead, &dev->filelist_पूर्णांकernal);
	mutex_unlock(&dev->filelist_mutex);

	client->file = file;

	वापस 0;
पूर्ण

अटल व्योम drm_client_बंद(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_device *dev = client->dev;

	mutex_lock(&dev->filelist_mutex);
	list_del(&client->file->lhead);
	mutex_unlock(&dev->filelist_mutex);

	drm_file_मुक्त(client->file);
पूर्ण

/**
 * drm_client_init - Initialise a DRM client
 * @dev: DRM device
 * @client: DRM client
 * @name: Client name
 * @funcs: DRM client functions (optional)
 *
 * This initialises the client and खोलोs a &drm_file.
 * Use drm_client_रेजिस्टर() to complete the process.
 * The caller needs to hold a reference on @dev beक्रमe calling this function.
 * The client is मुक्तd when the &drm_device is unरेजिस्टरed. See drm_client_release().
 *
 * Returns:
 * Zero on success or negative error code on failure.
 */
पूर्णांक drm_client_init(काष्ठा drm_device *dev, काष्ठा drm_client_dev *client,
		    स्थिर अक्षर *name, स्थिर काष्ठा drm_client_funcs *funcs)
अणु
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET) || !dev->driver->dumb_create)
		वापस -EOPNOTSUPP;

	अगर (funcs && !try_module_get(funcs->owner))
		वापस -ENODEV;

	client->dev = dev;
	client->name = name;
	client->funcs = funcs;

	ret = drm_client_modeset_create(client);
	अगर (ret)
		जाओ err_put_module;

	ret = drm_client_खोलो(client);
	अगर (ret)
		जाओ err_मुक्त;

	drm_dev_get(dev);

	वापस 0;

err_मुक्त:
	drm_client_modeset_मुक्त(client);
err_put_module:
	अगर (funcs)
		module_put(funcs->owner);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_client_init);

/**
 * drm_client_रेजिस्टर - Register client
 * @client: DRM client
 *
 * Add the client to the &drm_device client list to activate its callbacks.
 * @client must be initialized by a call to drm_client_init(). After
 * drm_client_रेजिस्टर() it is no दीर्घer permissible to call drm_client_release()
 * directly (outside the unरेजिस्टर callback), instead cleanup will happen
 * स्वतःmatically on driver unload.
 */
व्योम drm_client_रेजिस्टर(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_device *dev = client->dev;

	mutex_lock(&dev->clientlist_mutex);
	list_add(&client->list, &dev->clientlist);
	mutex_unlock(&dev->clientlist_mutex);
पूर्ण
EXPORT_SYMBOL(drm_client_रेजिस्टर);

/**
 * drm_client_release - Release DRM client resources
 * @client: DRM client
 *
 * Releases resources by closing the &drm_file that was खोलोed by drm_client_init().
 * It is called स्वतःmatically अगर the &drm_client_funcs.unरेजिस्टर callback is _not_ set.
 *
 * This function should only be called from the unरेजिस्टर callback. An exception
 * is fbdev which cannot मुक्त the buffer अगर userspace has खोलो file descriptors.
 *
 * Note:
 * Clients cannot initiate a release by themselves. This is करोne to keep the code simple.
 * The driver has to be unloaded beक्रमe the client can be unloaded.
 */
व्योम drm_client_release(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_device *dev = client->dev;

	drm_dbg_kms(dev, "%s\n", client->name);

	drm_client_modeset_मुक्त(client);
	drm_client_बंद(client);
	drm_dev_put(dev);
	अगर (client->funcs)
		module_put(client->funcs->owner);
पूर्ण
EXPORT_SYMBOL(drm_client_release);

व्योम drm_client_dev_unरेजिस्टर(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_client_dev *client, *पंचांगp;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस;

	mutex_lock(&dev->clientlist_mutex);
	list_क्रम_each_entry_safe(client, पंचांगp, &dev->clientlist, list) अणु
		list_del(&client->list);
		अगर (client->funcs && client->funcs->unरेजिस्टर) अणु
			client->funcs->unरेजिस्टर(client);
		पूर्ण अन्यथा अणु
			drm_client_release(client);
			kमुक्त(client);
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->clientlist_mutex);
पूर्ण

/**
 * drm_client_dev_hotplug - Send hotplug event to clients
 * @dev: DRM device
 *
 * This function calls the &drm_client_funcs.hotplug callback on the attached clients.
 *
 * drm_kms_helper_hotplug_event() calls this function, so drivers that use it
 * करोn't need to call this function themselves.
 */
व्योम drm_client_dev_hotplug(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_client_dev *client;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस;

	mutex_lock(&dev->clientlist_mutex);
	list_क्रम_each_entry(client, &dev->clientlist, list) अणु
		अगर (!client->funcs || !client->funcs->hotplug)
			जारी;

		ret = client->funcs->hotplug(client);
		drm_dbg_kms(dev, "%s: ret=%d\n", client->name, ret);
	पूर्ण
	mutex_unlock(&dev->clientlist_mutex);
पूर्ण
EXPORT_SYMBOL(drm_client_dev_hotplug);

व्योम drm_client_dev_restore(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_client_dev *client;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस;

	mutex_lock(&dev->clientlist_mutex);
	list_क्रम_each_entry(client, &dev->clientlist, list) अणु
		अगर (!client->funcs || !client->funcs->restore)
			जारी;

		ret = client->funcs->restore(client);
		drm_dbg_kms(dev, "%s: ret=%d\n", client->name, ret);
		अगर (!ret) /* The first one to वापस zero माला_लो the privilege to restore */
			अवरोध;
	पूर्ण
	mutex_unlock(&dev->clientlist_mutex);
पूर्ण

अटल व्योम drm_client_buffer_delete(काष्ठा drm_client_buffer *buffer)
अणु
	काष्ठा drm_device *dev = buffer->client->dev;

	drm_gem_vunmap(buffer->gem, &buffer->map);

	अगर (buffer->gem)
		drm_gem_object_put(buffer->gem);

	अगर (buffer->handle)
		drm_mode_destroy_dumb(dev, buffer->handle, buffer->client->file);

	kमुक्त(buffer);
पूर्ण

अटल काष्ठा drm_client_buffer *
drm_client_buffer_create(काष्ठा drm_client_dev *client, u32 width, u32 height, u32 क्रमmat)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(क्रमmat);
	काष्ठा drm_mode_create_dumb dumb_args = अणु पूर्ण;
	काष्ठा drm_device *dev = client->dev;
	काष्ठा drm_client_buffer *buffer;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	buffer = kzalloc(माप(*buffer), GFP_KERNEL);
	अगर (!buffer)
		वापस ERR_PTR(-ENOMEM);

	buffer->client = client;

	dumb_args.width = width;
	dumb_args.height = height;
	dumb_args.bpp = info->cpp[0] * 8;
	ret = drm_mode_create_dumb(dev, &dumb_args, client->file);
	अगर (ret)
		जाओ err_delete;

	buffer->handle = dumb_args.handle;
	buffer->pitch = dumb_args.pitch;

	obj = drm_gem_object_lookup(client->file, dumb_args.handle);
	अगर (!obj)  अणु
		ret = -ENOENT;
		जाओ err_delete;
	पूर्ण

	buffer->gem = obj;

	वापस buffer;

err_delete:
	drm_client_buffer_delete(buffer);

	वापस ERR_PTR(ret);
पूर्ण

/**
 * drm_client_buffer_vmap - Map DRM client buffer पूर्णांकo address space
 * @buffer: DRM client buffer
 * @map_copy: Returns the mapped memory's address
 *
 * This function maps a client buffer पूर्णांकo kernel address space. If the
 * buffer is alपढ़ोy mapped, it वापसs the existing mapping's address.
 *
 * Client buffer mappings are not ref'counted. Each call to
 * drm_client_buffer_vmap() should be followed by a call to
 * drm_client_buffer_vunmap(); or the client buffer should be mapped
 * throughout its lअगरeसमय.
 *
 * The वापसed address is a copy of the पूर्णांकernal value. In contrast to
 * other vmap पूर्णांकerfaces, you करोn't need it for the client's vunmap
 * function. So you can modअगरy it at will during blit and draw operations.
 *
 * Returns:
 *	0 on success, or a negative त्रुटि_सं code otherwise.
 */
पूर्णांक
drm_client_buffer_vmap(काष्ठा drm_client_buffer *buffer, काष्ठा dma_buf_map *map_copy)
अणु
	काष्ठा dma_buf_map *map = &buffer->map;
	पूर्णांक ret;

	/*
	 * FIXME: The dependency on GEM here isn't required, we could
	 * convert the driver handle to a dma-buf instead and use the
	 * backend-agnostic dma-buf vmap support instead. This would
	 * require that the handle2fd prime ioctl is reworked to pull the
	 * fd_install step out of the driver backend hooks, to make that
	 * final step optional क्रम पूर्णांकernal users.
	 */
	ret = drm_gem_vmap(buffer->gem, map);
	अगर (ret)
		वापस ret;

	*map_copy = *map;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_client_buffer_vmap);

/**
 * drm_client_buffer_vunmap - Unmap DRM client buffer
 * @buffer: DRM client buffer
 *
 * This function हटाओs a client buffer's memory mapping. Calling this
 * function is only required by clients that manage their buffer mappings
 * by themselves.
 */
व्योम drm_client_buffer_vunmap(काष्ठा drm_client_buffer *buffer)
अणु
	काष्ठा dma_buf_map *map = &buffer->map;

	drm_gem_vunmap(buffer->gem, map);
पूर्ण
EXPORT_SYMBOL(drm_client_buffer_vunmap);

अटल व्योम drm_client_buffer_rmfb(काष्ठा drm_client_buffer *buffer)
अणु
	पूर्णांक ret;

	अगर (!buffer->fb)
		वापस;

	ret = drm_mode_rmfb(buffer->client->dev, buffer->fb->base.id, buffer->client->file);
	अगर (ret)
		drm_err(buffer->client->dev,
			"Error removing FB:%u (%d)\n", buffer->fb->base.id, ret);

	buffer->fb = शून्य;
पूर्ण

अटल पूर्णांक drm_client_buffer_addfb(काष्ठा drm_client_buffer *buffer,
				   u32 width, u32 height, u32 क्रमmat)
अणु
	काष्ठा drm_client_dev *client = buffer->client;
	काष्ठा drm_mode_fb_cmd fb_req = अणु पूर्ण;
	स्थिर काष्ठा drm_क्रमmat_info *info;
	पूर्णांक ret;

	info = drm_क्रमmat_info(क्रमmat);
	fb_req.bpp = info->cpp[0] * 8;
	fb_req.depth = info->depth;
	fb_req.width = width;
	fb_req.height = height;
	fb_req.handle = buffer->handle;
	fb_req.pitch = buffer->pitch;

	ret = drm_mode_addfb(client->dev, &fb_req, client->file);
	अगर (ret)
		वापस ret;

	buffer->fb = drm_framebuffer_lookup(client->dev, buffer->client->file, fb_req.fb_id);
	अगर (WARN_ON(!buffer->fb))
		वापस -ENOENT;

	/* drop the reference we picked up in framebuffer lookup */
	drm_framebuffer_put(buffer->fb);

	strscpy(buffer->fb->comm, client->name, TASK_COMM_LEN);

	वापस 0;
पूर्ण

/**
 * drm_client_framebuffer_create - Create a client framebuffer
 * @client: DRM client
 * @width: Framebuffer width
 * @height: Framebuffer height
 * @क्रमmat: Buffer क्रमmat
 *
 * This function creates a &drm_client_buffer which consists of a
 * &drm_framebuffer backed by a dumb buffer.
 * Call drm_client_framebuffer_delete() to मुक्त the buffer.
 *
 * Returns:
 * Poपूर्णांकer to a client buffer or an error poपूर्णांकer on failure.
 */
काष्ठा drm_client_buffer *
drm_client_framebuffer_create(काष्ठा drm_client_dev *client, u32 width, u32 height, u32 क्रमmat)
अणु
	काष्ठा drm_client_buffer *buffer;
	पूर्णांक ret;

	buffer = drm_client_buffer_create(client, width, height, क्रमmat);
	अगर (IS_ERR(buffer))
		वापस buffer;

	ret = drm_client_buffer_addfb(buffer, width, height, क्रमmat);
	अगर (ret) अणु
		drm_client_buffer_delete(buffer);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस buffer;
पूर्ण
EXPORT_SYMBOL(drm_client_framebuffer_create);

/**
 * drm_client_framebuffer_delete - Delete a client framebuffer
 * @buffer: DRM client buffer (can be शून्य)
 */
व्योम drm_client_framebuffer_delete(काष्ठा drm_client_buffer *buffer)
अणु
	अगर (!buffer)
		वापस;

	drm_client_buffer_rmfb(buffer);
	drm_client_buffer_delete(buffer);
पूर्ण
EXPORT_SYMBOL(drm_client_framebuffer_delete);

/**
 * drm_client_framebuffer_flush - Manually flush client framebuffer
 * @buffer: DRM client buffer (can be शून्य)
 * @rect: Damage rectangle (अगर शून्य flushes all)
 *
 * This calls &drm_framebuffer_funcs->dirty (अगर present) to flush buffer changes
 * क्रम drivers that need it.
 *
 * Returns:
 * Zero on success or negative error code on failure.
 */
पूर्णांक drm_client_framebuffer_flush(काष्ठा drm_client_buffer *buffer, काष्ठा drm_rect *rect)
अणु
	अगर (!buffer || !buffer->fb || !buffer->fb->funcs->dirty)
		वापस 0;

	अगर (rect) अणु
		काष्ठा drm_clip_rect clip = अणु
			.x1 = rect->x1,
			.y1 = rect->y1,
			.x2 = rect->x2,
			.y2 = rect->y2,
		पूर्ण;

		वापस buffer->fb->funcs->dirty(buffer->fb, buffer->client->file,
						0, 0, &clip, 1);
	पूर्ण

	वापस buffer->fb->funcs->dirty(buffer->fb, buffer->client->file,
					0, 0, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(drm_client_framebuffer_flush);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक drm_client_debugfs_पूर्णांकernal_clients(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);
	काष्ठा drm_client_dev *client;

	mutex_lock(&dev->clientlist_mutex);
	list_क्रम_each_entry(client, &dev->clientlist, list)
		drm_म_लिखो(&p, "%s\n", client->name);
	mutex_unlock(&dev->clientlist_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_info_list drm_client_debugfs_list[] = अणु
	अणु "internal_clients", drm_client_debugfs_पूर्णांकernal_clients, 0 पूर्ण,
पूर्ण;

व्योम drm_client_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(drm_client_debugfs_list,
				 ARRAY_SIZE(drm_client_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
#पूर्ण_अगर
