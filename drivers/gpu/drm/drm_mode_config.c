<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#समावेश <linux/uaccess.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_mode_config.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <linux/dma-resv.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"

पूर्णांक drm_modeset_रेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	पूर्णांक ret;

	ret = drm_plane_रेजिस्टर_all(dev);
	अगर (ret)
		जाओ err_plane;

	ret = drm_crtc_रेजिस्टर_all(dev);
	अगर  (ret)
		जाओ err_crtc;

	ret = drm_encoder_रेजिस्टर_all(dev);
	अगर (ret)
		जाओ err_encoder;

	ret = drm_connector_रेजिस्टर_all(dev);
	अगर (ret)
		जाओ err_connector;

	वापस 0;

err_connector:
	drm_encoder_unरेजिस्टर_all(dev);
err_encoder:
	drm_crtc_unरेजिस्टर_all(dev);
err_crtc:
	drm_plane_unरेजिस्टर_all(dev);
err_plane:
	वापस ret;
पूर्ण

व्योम drm_modeset_unरेजिस्टर_all(काष्ठा drm_device *dev)
अणु
	drm_connector_unरेजिस्टर_all(dev);
	drm_encoder_unरेजिस्टर_all(dev);
	drm_crtc_unरेजिस्टर_all(dev);
	drm_plane_unरेजिस्टर_all(dev);
पूर्ण

/**
 * drm_mode_getresources - get graphics configuration
 * @dev: drm device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: drm file क्रम the ioctl call
 *
 * Conकाष्ठा a set of configuration description काष्ठाures and वापस
 * them to the user, including CRTC, connector and framebuffer configuration.
 *
 * Called by the user via ioctl.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_mode_getresources(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_mode_card_res *card_res = data;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_connector *connector;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_encoder *encoder;
	पूर्णांक count, ret = 0;
	uपूर्णांक32_t __user *fb_id;
	uपूर्णांक32_t __user *crtc_id;
	uपूर्णांक32_t __user *connector_id;
	uपूर्णांक32_t __user *encoder_id;
	काष्ठा drm_connector_list_iter conn_iter;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	mutex_lock(&file_priv->fbs_lock);
	count = 0;
	fb_id = u64_to_user_ptr(card_res->fb_id_ptr);
	list_क्रम_each_entry(fb, &file_priv->fbs, filp_head) अणु
		अगर (count < card_res->count_fbs &&
		    put_user(fb->base.id, fb_id + count)) अणु
			mutex_unlock(&file_priv->fbs_lock);
			वापस -EFAULT;
		पूर्ण
		count++;
	पूर्ण
	card_res->count_fbs = count;
	mutex_unlock(&file_priv->fbs_lock);

	card_res->max_height = dev->mode_config.max_height;
	card_res->min_height = dev->mode_config.min_height;
	card_res->max_width = dev->mode_config.max_width;
	card_res->min_width = dev->mode_config.min_width;

	count = 0;
	crtc_id = u64_to_user_ptr(card_res->crtc_id_ptr);
	drm_क्रम_each_crtc(crtc, dev) अणु
		अगर (drm_lease_held(file_priv, crtc->base.id)) अणु
			अगर (count < card_res->count_crtcs &&
			    put_user(crtc->base.id, crtc_id + count))
				वापस -EFAULT;
			count++;
		पूर्ण
	पूर्ण
	card_res->count_crtcs = count;

	count = 0;
	encoder_id = u64_to_user_ptr(card_res->encoder_id_ptr);
	drm_क्रम_each_encoder(encoder, dev) अणु
		अगर (count < card_res->count_encoders &&
		    put_user(encoder->base.id, encoder_id + count))
			वापस -EFAULT;
		count++;
	पूर्ण
	card_res->count_encoders = count;

	drm_connector_list_iter_begin(dev, &conn_iter);
	count = 0;
	connector_id = u64_to_user_ptr(card_res->connector_id_ptr);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		/* only expose ग_लिखोback connectors अगर userspace understands them */
		अगर (!file_priv->ग_लिखोback_connectors &&
		    (connector->connector_type == DRM_MODE_CONNECTOR_WRITEBACK))
			जारी;

		अगर (drm_lease_held(file_priv, connector->base.id)) अणु
			अगर (count < card_res->count_connectors &&
			    put_user(connector->base.id, connector_id + count)) अणु
				drm_connector_list_iter_end(&conn_iter);
				वापस -EFAULT;
			पूर्ण
			count++;
		पूर्ण
	पूर्ण
	card_res->count_connectors = count;
	drm_connector_list_iter_end(&conn_iter);

	वापस ret;
पूर्ण

/**
 * drm_mode_config_reset - call ->reset callbacks
 * @dev: drm device
 *
 * This functions calls all the crtc's, encoder's and connector's ->reset
 * callback. Drivers can use this in e.g. their driver load or resume code to
 * reset hardware and software state.
 */
व्योम drm_mode_config_reset(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *plane;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	drm_क्रम_each_plane(plane, dev)
		अगर (plane->funcs->reset)
			plane->funcs->reset(plane);

	drm_क्रम_each_crtc(crtc, dev)
		अगर (crtc->funcs->reset)
			crtc->funcs->reset(crtc);

	drm_क्रम_each_encoder(encoder, dev)
		अगर (encoder->funcs && encoder->funcs->reset)
			encoder->funcs->reset(encoder);

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter)
		अगर (connector->funcs->reset)
			connector->funcs->reset(connector);
	drm_connector_list_iter_end(&conn_iter);
पूर्ण
EXPORT_SYMBOL(drm_mode_config_reset);

/*
 * Global properties
 */
अटल स्थिर काष्ठा drm_prop_क्रमागत_list drm_plane_type_क्रमागत_list[] = अणु
	अणु DRM_PLANE_TYPE_OVERLAY, "Overlay" पूर्ण,
	अणु DRM_PLANE_TYPE_PRIMARY, "Primary" पूर्ण,
	अणु DRM_PLANE_TYPE_CURSOR, "Cursor" पूर्ण,
पूर्ण;

अटल पूर्णांक drm_mode_create_standard_properties(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_property *prop;
	पूर्णांक ret;

	ret = drm_connector_create_standard_properties(dev);
	अगर (ret)
		वापस ret;

	prop = drm_property_create_क्रमागत(dev, DRM_MODE_PROP_IMMUTABLE,
					"type", drm_plane_type_क्रमागत_list,
					ARRAY_SIZE(drm_plane_type_क्रमागत_list));
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.plane_type_property = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"SRC_X", 0, अच_पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_src_x = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"SRC_Y", 0, अच_पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_src_y = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"SRC_W", 0, अच_पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_src_w = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"SRC_H", 0, अच_पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_src_h = prop;

	prop = drm_property_create_चिन्हित_range(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_X", पूर्णांक_न्यून, पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_crtc_x = prop;

	prop = drm_property_create_चिन्हित_range(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_Y", पूर्णांक_न्यून, पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_crtc_y = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_W", 0, पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_crtc_w = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_H", 0, पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_crtc_h = prop;

	prop = drm_property_create_object(dev, DRM_MODE_PROP_ATOMIC,
			"FB_ID", DRM_MODE_OBJECT_FB);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_fb_id = prop;

	prop = drm_property_create_चिन्हित_range(dev, DRM_MODE_PROP_ATOMIC,
			"IN_FENCE_FD", -1, पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_in_fence_fd = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"OUT_FENCE_PTR", 0, U64_MAX);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_out_fence_ptr = prop;

	prop = drm_property_create_object(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_ID", DRM_MODE_OBJECT_CRTC);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_crtc_id = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_ATOMIC | DRM_MODE_PROP_BLOB,
			"FB_DAMAGE_CLIPS", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_fb_damage_clips = prop;

	prop = drm_property_create_bool(dev, DRM_MODE_PROP_ATOMIC,
			"ACTIVE");
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_active = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_ATOMIC | DRM_MODE_PROP_BLOB,
			"MODE_ID", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_mode_id = prop;

	prop = drm_property_create_bool(dev, 0,
			"VRR_ENABLED");
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.prop_vrr_enabled = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_BLOB,
			"DEGAMMA_LUT", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.degamma_lut_property = prop;

	prop = drm_property_create_range(dev,
			DRM_MODE_PROP_IMMUTABLE,
			"DEGAMMA_LUT_SIZE", 0, अच_पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.degamma_lut_size_property = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_BLOB,
			"CTM", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.cपंचांग_property = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_BLOB,
			"GAMMA_LUT", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.gamma_lut_property = prop;

	prop = drm_property_create_range(dev,
			DRM_MODE_PROP_IMMUTABLE,
			"GAMMA_LUT_SIZE", 0, अच_पूर्णांक_उच्च);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.gamma_lut_size_property = prop;

	prop = drm_property_create(dev,
				   DRM_MODE_PROP_IMMUTABLE | DRM_MODE_PROP_BLOB,
				   "IN_FORMATS", 0);
	अगर (!prop)
		वापस -ENOMEM;
	dev->mode_config.modअगरiers_property = prop;

	वापस 0;
पूर्ण

अटल व्योम drm_mode_config_init_release(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	drm_mode_config_cleanup(dev);
पूर्ण

/**
 * drmm_mode_config_init - managed DRM mode_configuration काष्ठाure
 * 	initialization
 * @dev: DRM device
 *
 * Initialize @dev's mode_config काष्ठाure, used क्रम tracking the graphics
 * configuration of @dev.
 *
 * Since this initializes the modeset locks, no locking is possible. Which is no
 * problem, since this should happen single thपढ़ोed at init समय. It is the
 * driver's problem to ensure this guarantee.
 *
 * Cleanup is स्वतःmatically handled through रेजिस्टरing drm_mode_config_cleanup
 * with drmm_add_action().
 *
 * Returns: 0 on success, negative error value on failure.
 */
पूर्णांक drmm_mode_config_init(काष्ठा drm_device *dev)
अणु
	mutex_init(&dev->mode_config.mutex);
	drm_modeset_lock_init(&dev->mode_config.connection_mutex);
	mutex_init(&dev->mode_config.idr_mutex);
	mutex_init(&dev->mode_config.fb_lock);
	mutex_init(&dev->mode_config.blob_lock);
	INIT_LIST_HEAD(&dev->mode_config.fb_list);
	INIT_LIST_HEAD(&dev->mode_config.crtc_list);
	INIT_LIST_HEAD(&dev->mode_config.connector_list);
	INIT_LIST_HEAD(&dev->mode_config.encoder_list);
	INIT_LIST_HEAD(&dev->mode_config.property_list);
	INIT_LIST_HEAD(&dev->mode_config.property_blob_list);
	INIT_LIST_HEAD(&dev->mode_config.plane_list);
	INIT_LIST_HEAD(&dev->mode_config.privobj_list);
	idr_init(&dev->mode_config.object_idr);
	idr_init(&dev->mode_config.tile_idr);
	ida_init(&dev->mode_config.connector_ida);
	spin_lock_init(&dev->mode_config.connector_list_lock);

	init_llist_head(&dev->mode_config.connector_मुक्त_list);
	INIT_WORK(&dev->mode_config.connector_मुक्त_work, drm_connector_मुक्त_work_fn);

	drm_mode_create_standard_properties(dev);

	/* Just to be sure */
	dev->mode_config.num_fb = 0;
	dev->mode_config.num_connector = 0;
	dev->mode_config.num_crtc = 0;
	dev->mode_config.num_encoder = 0;
	dev->mode_config.num_total_plane = 0;

	अगर (IS_ENABLED(CONFIG_LOCKDEP)) अणु
		काष्ठा drm_modeset_acquire_ctx modeset_ctx;
		काष्ठा ww_acquire_ctx resv_ctx;
		काष्ठा dma_resv resv;
		पूर्णांक ret;

		dma_resv_init(&resv);

		drm_modeset_acquire_init(&modeset_ctx, 0);
		ret = drm_modeset_lock(&dev->mode_config.connection_mutex,
				       &modeset_ctx);
		अगर (ret == -EDEADLK)
			ret = drm_modeset_backoff(&modeset_ctx);

		ww_acquire_init(&resv_ctx, &reservation_ww_class);
		ret = dma_resv_lock(&resv, &resv_ctx);
		अगर (ret == -EDEADLK)
			dma_resv_lock_slow(&resv, &resv_ctx);

		dma_resv_unlock(&resv);
		ww_acquire_fini(&resv_ctx);

		drm_modeset_drop_locks(&modeset_ctx);
		drm_modeset_acquire_fini(&modeset_ctx);
		dma_resv_fini(&resv);
	पूर्ण

	वापस drmm_add_action_or_reset(dev, drm_mode_config_init_release,
					शून्य);
पूर्ण
EXPORT_SYMBOL(drmm_mode_config_init);

/**
 * drm_mode_config_cleanup - मुक्त up DRM mode_config info
 * @dev: DRM device
 *
 * Free up all the connectors and CRTCs associated with this DRM device, then
 * मुक्त up the framebuffers and associated buffer objects.
 *
 * Note that since this /should/ happen single-thपढ़ोed at driver/device
 * tearकरोwn समय, no locking is required. It's the driver's job to ensure that
 * this guarantee actually holds true.
 *
 * FIXME: With the managed drmm_mode_config_init() it is no दीर्घer necessary क्रम
 * drivers to explicitly call this function.
 */
व्योम drm_mode_config_cleanup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_crtc *crtc, *ct;
	काष्ठा drm_encoder *encoder, *enct;
	काष्ठा drm_framebuffer *fb, *fbt;
	काष्ठा drm_property *property, *pt;
	काष्ठा drm_property_blob *blob, *bt;
	काष्ठा drm_plane *plane, *plt;

	list_क्रम_each_entry_safe(encoder, enct, &dev->mode_config.encoder_list,
				 head) अणु
		encoder->funcs->destroy(encoder);
	पूर्ण

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		/* drm_connector_list_iter holds an full reference to the
		 * current connector itself, which means it is inherently safe
		 * against unreferencing the current connector - but not against
		 * deleting it right away. */
		drm_connector_put(connector);
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
	/* connector_iter drops references in a work item. */
	flush_work(&dev->mode_config.connector_मुक्त_work);
	अगर (WARN_ON(!list_empty(&dev->mode_config.connector_list))) अणु
		drm_connector_list_iter_begin(dev, &conn_iter);
		drm_क्रम_each_connector_iter(connector, &conn_iter)
			DRM_ERROR("connector %s leaked!\n", connector->name);
		drm_connector_list_iter_end(&conn_iter);
	पूर्ण

	list_क्रम_each_entry_safe(property, pt, &dev->mode_config.property_list,
				 head) अणु
		drm_property_destroy(dev, property);
	पूर्ण

	list_क्रम_each_entry_safe(plane, plt, &dev->mode_config.plane_list,
				 head) अणु
		plane->funcs->destroy(plane);
	पूर्ण

	list_क्रम_each_entry_safe(crtc, ct, &dev->mode_config.crtc_list, head) अणु
		crtc->funcs->destroy(crtc);
	पूर्ण

	list_क्रम_each_entry_safe(blob, bt, &dev->mode_config.property_blob_list,
				 head_global) अणु
		drm_property_blob_put(blob);
	पूर्ण

	/*
	 * Single-thपढ़ोed tearकरोwn context, so it's not required to grab the
	 * fb_lock to protect against concurrent fb_list access. Contrary, it
	 * would actually deadlock with the drm_framebuffer_cleanup function.
	 *
	 * Also, अगर there are any framebuffers left, that's a driver leak now,
	 * so politely WARN about this.
	 */
	WARN_ON(!list_empty(&dev->mode_config.fb_list));
	list_क्रम_each_entry_safe(fb, fbt, &dev->mode_config.fb_list, head) अणु
		काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer("[leaked fb]");

		drm_म_लिखो(&p, "framebuffer[%u]:\n", fb->base.id);
		drm_framebuffer_prपूर्णांक_info(&p, 1, fb);
		drm_framebuffer_मुक्त(&fb->base.refcount);
	पूर्ण

	ida_destroy(&dev->mode_config.connector_ida);
	idr_destroy(&dev->mode_config.tile_idr);
	idr_destroy(&dev->mode_config.object_idr);
	drm_modeset_lock_fini(&dev->mode_config.connection_mutex);
पूर्ण
EXPORT_SYMBOL(drm_mode_config_cleanup);

अटल u32 full_encoder_mask(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder;
	u32 encoder_mask = 0;

	drm_क्रम_each_encoder(encoder, dev)
		encoder_mask |= drm_encoder_mask(encoder);

	वापस encoder_mask;
पूर्ण

/*
 * For some reason we want the encoder itself included in
 * possible_clones. Make lअगरe easy क्रम drivers by allowing them
 * to leave possible_clones unset अगर no cloning is possible.
 */
अटल व्योम fixup_encoder_possible_clones(काष्ठा drm_encoder *encoder)
अणु
	अगर (encoder->possible_clones == 0)
		encoder->possible_clones = drm_encoder_mask(encoder);
पूर्ण

अटल व्योम validate_encoder_possible_clones(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	u32 encoder_mask = full_encoder_mask(dev);
	काष्ठा drm_encoder *other;

	drm_क्रम_each_encoder(other, dev) अणु
		WARN(!!(encoder->possible_clones & drm_encoder_mask(other)) !=
		     !!(other->possible_clones & drm_encoder_mask(encoder)),
		     "possible_clones mismatch: "
		     "[ENCODER:%d:%s] mask=0x%x possible_clones=0x%x vs. "
		     "[ENCODER:%d:%s] mask=0x%x possible_clones=0x%x\n",
		     encoder->base.id, encoder->name,
		     drm_encoder_mask(encoder), encoder->possible_clones,
		     other->base.id, other->name,
		     drm_encoder_mask(other), other->possible_clones);
	पूर्ण

	WARN((encoder->possible_clones & drm_encoder_mask(encoder)) == 0 ||
	     (encoder->possible_clones & ~encoder_mask) != 0,
	     "Bogus possible_clones: "
	     "[ENCODER:%d:%s] possible_clones=0x%x (full encoder mask=0x%x)\n",
	     encoder->base.id, encoder->name,
	     encoder->possible_clones, encoder_mask);
पूर्ण

अटल u32 full_crtc_mask(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_crtc *crtc;
	u32 crtc_mask = 0;

	drm_क्रम_each_crtc(crtc, dev)
		crtc_mask |= drm_crtc_mask(crtc);

	वापस crtc_mask;
पूर्ण

अटल व्योम validate_encoder_possible_crtcs(काष्ठा drm_encoder *encoder)
अणु
	u32 crtc_mask = full_crtc_mask(encoder->dev);

	WARN((encoder->possible_crtcs & crtc_mask) == 0 ||
	     (encoder->possible_crtcs & ~crtc_mask) != 0,
	     "Bogus possible_crtcs: "
	     "[ENCODER:%d:%s] possible_crtcs=0x%x (full crtc mask=0x%x)\n",
	     encoder->base.id, encoder->name,
	     encoder->possible_crtcs, crtc_mask);
पूर्ण

व्योम drm_mode_config_validate(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane *plane;
	u32 primary_with_crtc = 0, cursor_with_crtc = 0;
	अचिन्हित पूर्णांक num_primary = 0;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस;

	drm_क्रम_each_encoder(encoder, dev)
		fixup_encoder_possible_clones(encoder);

	drm_क्रम_each_encoder(encoder, dev) अणु
		validate_encoder_possible_clones(encoder);
		validate_encoder_possible_crtcs(encoder);
	पूर्ण

	drm_क्रम_each_crtc(crtc, dev) अणु
		WARN(!crtc->primary, "Missing primary plane on [CRTC:%d:%s]\n",
		     crtc->base.id, crtc->name);

		WARN(crtc->cursor && crtc->funcs->cursor_set,
		     "[CRTC:%d:%s] must not have both a cursor plane and a cursor_set func",
		     crtc->base.id, crtc->name);
		WARN(crtc->cursor && crtc->funcs->cursor_set2,
		     "[CRTC:%d:%s] must not have both a cursor plane and a cursor_set2 func",
		     crtc->base.id, crtc->name);
		WARN(crtc->cursor && crtc->funcs->cursor_move,
		     "[CRTC:%d:%s] must not have both a cursor plane and a cursor_move func",
		     crtc->base.id, crtc->name);

		अगर (crtc->primary) अणु
			WARN(!(crtc->primary->possible_crtcs & drm_crtc_mask(crtc)),
			     "Bogus primary plane possible_crtcs: [PLANE:%d:%s] must be compatible with [CRTC:%d:%s]\n",
			     crtc->primary->base.id, crtc->primary->name,
			     crtc->base.id, crtc->name);
			WARN(primary_with_crtc & drm_plane_mask(crtc->primary),
			     "Primary plane [PLANE:%d:%s] used for multiple CRTCs",
			     crtc->primary->base.id, crtc->primary->name);
			primary_with_crtc |= drm_plane_mask(crtc->primary);
		पूर्ण
		अगर (crtc->cursor) अणु
			WARN(!(crtc->cursor->possible_crtcs & drm_crtc_mask(crtc)),
			     "Bogus cursor plane possible_crtcs: [PLANE:%d:%s] must be compatible with [CRTC:%d:%s]\n",
			     crtc->cursor->base.id, crtc->cursor->name,
			     crtc->base.id, crtc->name);
			WARN(cursor_with_crtc & drm_plane_mask(crtc->cursor),
			     "Cursor plane [PLANE:%d:%s] used for multiple CRTCs",
			     crtc->cursor->base.id, crtc->cursor->name);
			cursor_with_crtc |= drm_plane_mask(crtc->cursor);
		पूर्ण
	पूर्ण

	drm_क्रम_each_plane(plane, dev) अणु
		अगर (plane->type == DRM_PLANE_TYPE_PRIMARY)
			num_primary++;
	पूर्ण

	WARN(num_primary != dev->mode_config.num_crtc,
	     "Must have as many primary planes as there are CRTCs, but have %u primary planes and %u CRTCs",
	     num_primary, dev->mode_config.num_crtc);
पूर्ण
