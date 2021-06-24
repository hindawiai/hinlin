<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alon Levy
 */

#समावेश <linux/crc32.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-buf-map.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

अटल bool qxl_head_enabled(काष्ठा qxl_head *head)
अणु
	वापस head->width && head->height;
पूर्ण

अटल पूर्णांक qxl_alloc_client_monitors_config(काष्ठा qxl_device *qdev,
		अचिन्हित पूर्णांक count)
अणु
	अगर (qdev->client_monitors_config &&
	    count > qdev->client_monitors_config->count) अणु
		kमुक्त(qdev->client_monitors_config);
		qdev->client_monitors_config = शून्य;
	पूर्ण
	अगर (!qdev->client_monitors_config) अणु
		qdev->client_monitors_config = kzalloc(
				काष्ठा_size(qdev->client_monitors_config,
				heads, count), GFP_KERNEL);
		अगर (!qdev->client_monitors_config)
			वापस -ENOMEM;
	पूर्ण
	qdev->client_monitors_config->count = count;
	वापस 0;
पूर्ण

क्रमागत अणु
	MONITORS_CONFIG_MODIFIED,
	MONITORS_CONFIG_UNCHANGED,
	MONITORS_CONFIG_BAD_CRC,
	MONITORS_CONFIG_ERROR,
पूर्ण;

अटल पूर्णांक qxl_display_copy_rom_client_monitors_config(काष्ठा qxl_device *qdev)
अणु
	पूर्णांक i;
	पूर्णांक num_monitors;
	uपूर्णांक32_t crc;
	पूर्णांक status = MONITORS_CONFIG_UNCHANGED;

	num_monitors = qdev->rom->client_monitors_config.count;
	crc = crc32(0, (स्थिर uपूर्णांक8_t *)&qdev->rom->client_monitors_config,
		  माप(qdev->rom->client_monitors_config));
	अगर (crc != qdev->rom->client_monitors_config_crc)
		वापस MONITORS_CONFIG_BAD_CRC;
	अगर (!num_monitors) अणु
		DRM_DEBUG_KMS("no client monitors configured\n");
		वापस status;
	पूर्ण
	अगर (num_monitors > qxl_num_crtc) अणु
		DRM_DEBUG_KMS("client monitors list will be truncated: %d < %d\n",
			      qxl_num_crtc, num_monitors);
		num_monitors = qxl_num_crtc;
	पूर्ण अन्यथा अणु
		num_monitors = qdev->rom->client_monitors_config.count;
	पूर्ण
	अगर (qdev->client_monitors_config
	      && (num_monitors != qdev->client_monitors_config->count)) अणु
		status = MONITORS_CONFIG_MODIFIED;
	पूर्ण
	अगर (qxl_alloc_client_monitors_config(qdev, num_monitors)) अणु
		status = MONITORS_CONFIG_ERROR;
		वापस status;
	पूर्ण
	/* we copy max from the client but it isn't used */
	qdev->client_monitors_config->max_allowed = qxl_num_crtc;
	क्रम (i = 0 ; i < qdev->client_monitors_config->count ; ++i) अणु
		काष्ठा qxl_urect *c_rect =
			&qdev->rom->client_monitors_config.heads[i];
		काष्ठा qxl_head *client_head =
			&qdev->client_monitors_config->heads[i];
		अगर (client_head->x != c_rect->left) अणु
			client_head->x = c_rect->left;
			status = MONITORS_CONFIG_MODIFIED;
		पूर्ण
		अगर (client_head->y != c_rect->top) अणु
			client_head->y = c_rect->top;
			status = MONITORS_CONFIG_MODIFIED;
		पूर्ण
		अगर (client_head->width != c_rect->right - c_rect->left) अणु
			client_head->width = c_rect->right - c_rect->left;
			status = MONITORS_CONFIG_MODIFIED;
		पूर्ण
		अगर (client_head->height != c_rect->bottom - c_rect->top) अणु
			client_head->height = c_rect->bottom - c_rect->top;
			status = MONITORS_CONFIG_MODIFIED;
		पूर्ण
		अगर (client_head->surface_id != 0) अणु
			client_head->surface_id = 0;
			status = MONITORS_CONFIG_MODIFIED;
		पूर्ण
		अगर (client_head->id != i) अणु
			client_head->id = i;
			status = MONITORS_CONFIG_MODIFIED;
		पूर्ण
		अगर (client_head->flags != 0) अणु
			client_head->flags = 0;
			status = MONITORS_CONFIG_MODIFIED;
		पूर्ण
		DRM_DEBUG_KMS("read %dx%d+%d+%d\n", client_head->width, client_head->height,
			  client_head->x, client_head->y);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम qxl_update_offset_props(काष्ठा qxl_device *qdev)
अणु
	काष्ठा drm_device *dev = &qdev->ddev;
	काष्ठा drm_connector *connector;
	काष्ठा qxl_output *output;
	काष्ठा qxl_head *head;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		output = drm_connector_to_qxl_output(connector);

		head = &qdev->client_monitors_config->heads[output->index];

		drm_object_property_set_value(&connector->base,
			dev->mode_config.suggested_x_property, head->x);
		drm_object_property_set_value(&connector->base,
			dev->mode_config.suggested_y_property, head->y);
	पूर्ण
पूर्ण

व्योम qxl_display_पढ़ो_client_monitors_config(काष्ठा qxl_device *qdev)
अणु
	काष्ठा drm_device *dev = &qdev->ddev;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक status, retries, ret;

	क्रम (retries = 0; retries < 10; retries++) अणु
		status = qxl_display_copy_rom_client_monitors_config(qdev);
		अगर (status != MONITORS_CONFIG_BAD_CRC)
			अवरोध;
		udelay(5);
	पूर्ण
	अगर (status == MONITORS_CONFIG_ERROR) अणु
		DRM_DEBUG_KMS("ignoring client monitors config: error");
		वापस;
	पूर्ण
	अगर (status == MONITORS_CONFIG_BAD_CRC) अणु
		DRM_DEBUG_KMS("ignoring client monitors config: bad crc");
		वापस;
	पूर्ण
	अगर (status == MONITORS_CONFIG_UNCHANGED) अणु
		DRM_DEBUG_KMS("ignoring client monitors config: unchanged");
		वापस;
	पूर्ण

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE, ret);
	qxl_update_offset_props(qdev);
	DRM_MODESET_LOCK_ALL_END(dev, ctx, ret);
	अगर (!drm_helper_hpd_irq_event(dev)) अणु
		/* notअगरy that the monitor configuration changed, to
		   adjust at the arbitrary resolution */
		drm_kms_helper_hotplug_event(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक qxl_check_mode(काष्ठा qxl_device *qdev,
			  अचिन्हित पूर्णांक width,
			  अचिन्हित पूर्णांक height)
अणु
	अचिन्हित पूर्णांक stride;
	अचिन्हित पूर्णांक size;

	अगर (check_mul_overflow(width, 4u, &stride))
		वापस -EINVAL;
	अगर (check_mul_overflow(stride, height, &size))
		वापस -EINVAL;
	अगर (size > qdev->vram_size)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक qxl_check_framebuffer(काष्ठा qxl_device *qdev,
				 काष्ठा qxl_bo *bo)
अणु
	वापस qxl_check_mode(qdev, bo->surf.width, bo->surf.height);
पूर्ण

अटल पूर्णांक qxl_add_mode(काष्ठा drm_connector *connector,
			अचिन्हित पूर्णांक width,
			अचिन्हित पूर्णांक height,
			bool preferred)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा drm_display_mode *mode = शून्य;
	पूर्णांक rc;

	rc = qxl_check_mode(qdev, width, height);
	अगर (rc != 0)
		वापस 0;

	mode = drm_cvt_mode(dev, width, height, 60, false, false, false);
	अगर (preferred)
		mode->type |= DRM_MODE_TYPE_PREFERRED;
	mode->hdisplay = width;
	mode->vdisplay = height;
	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);
	वापस 1;
पूर्ण

अटल पूर्णांक qxl_add_monitors_config_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा qxl_output *output = drm_connector_to_qxl_output(connector);
	पूर्णांक h = output->index;
	काष्ठा qxl_head *head;

	अगर (!qdev->monitors_config)
		वापस 0;
	अगर (h >= qxl_num_crtc)
		वापस 0;
	अगर (!qdev->client_monitors_config)
		वापस 0;
	अगर (h >= qdev->client_monitors_config->count)
		वापस 0;

	head = &qdev->client_monitors_config->heads[h];
	DRM_DEBUG_KMS("head %d is %dx%d\n", h, head->width, head->height);

	वापस qxl_add_mode(connector, head->width, head->height, true);
पूर्ण

अटल काष्ठा mode_size अणु
	पूर्णांक w;
	पूर्णांक h;
पूर्ण extra_modes[] = अणु
	अणु 720,  480पूर्ण,
	अणु1152,  768पूर्ण,
	अणु1280,  854पूर्ण,
पूर्ण;

अटल पूर्णांक qxl_add_extra_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(extra_modes); i++)
		ret += qxl_add_mode(connector,
				    extra_modes[i].w,
				    extra_modes[i].h,
				    false);
	वापस ret;
पूर्ण

अटल व्योम qxl_send_monitors_config(काष्ठा qxl_device *qdev)
अणु
	पूर्णांक i;

	BUG_ON(!qdev->ram_header->monitors_config);

	अगर (qdev->monitors_config->count == 0)
		वापस;

	क्रम (i = 0 ; i < qdev->monitors_config->count ; ++i) अणु
		काष्ठा qxl_head *head = &qdev->monitors_config->heads[i];

		अगर (head->y > 8192 || head->x > 8192 ||
		    head->width > 8192 || head->height > 8192) अणु
			DRM_ERROR("head %d wrong: %dx%d+%d+%d\n",
				  i, head->width, head->height,
				  head->x, head->y);
			वापस;
		पूर्ण
	पूर्ण
	qxl_io_monitors_config(qdev);
पूर्ण

अटल व्योम qxl_crtc_update_monitors_config(काष्ठा drm_crtc *crtc,
					    स्थिर अक्षर *reason)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा qxl_crtc *qcrtc = to_qxl_crtc(crtc);
	काष्ठा qxl_head head;
	पूर्णांक oldcount, i = qcrtc->index;

	अगर (!qdev->primary_bo) अणु
		DRM_DEBUG_KMS("no primary surface, skip (%s)\n", reason);
		वापस;
	पूर्ण

	अगर (!qdev->monitors_config || qxl_num_crtc <= i)
		वापस;

	head.id = i;
	head.flags = 0;
	head.surface_id = 0;
	oldcount = qdev->monitors_config->count;
	अगर (crtc->state->active) अणु
		काष्ठा drm_display_mode *mode = &crtc->mode;

		head.width = mode->hdisplay;
		head.height = mode->vdisplay;
		head.x = crtc->x;
		head.y = crtc->y;
		अगर (qdev->monitors_config->count < i + 1)
			qdev->monitors_config->count = i + 1;
		अगर (qdev->primary_bo == qdev->dumb_shaकरोw_bo)
			head.x += qdev->dumb_heads[i].x;
	पूर्ण अन्यथा अगर (i > 0) अणु
		head.width = 0;
		head.height = 0;
		head.x = 0;
		head.y = 0;
		अगर (qdev->monitors_config->count == i + 1)
			qdev->monitors_config->count = i;
	पूर्ण अन्यथा अणु
		DRM_DEBUG_KMS("inactive head 0, skip (%s)\n", reason);
		वापस;
	पूर्ण

	अगर (head.width  == qdev->monitors_config->heads[i].width  &&
	    head.height == qdev->monitors_config->heads[i].height &&
	    head.x      == qdev->monitors_config->heads[i].x      &&
	    head.y      == qdev->monitors_config->heads[i].y      &&
	    oldcount    == qdev->monitors_config->count)
		वापस;

	DRM_DEBUG_KMS("head %d, %dx%d, at +%d+%d, %s (%s)\n",
		      i, head.width, head.height, head.x, head.y,
		      crtc->state->active ? "on" : "off", reason);
	अगर (oldcount != qdev->monitors_config->count)
		DRM_DEBUG_KMS("active heads %d -> %d (%d total)\n",
			      oldcount, qdev->monitors_config->count,
			      qxl_num_crtc);

	qdev->monitors_config->heads[i] = head;
	qdev->monitors_config->max_allowed = qxl_num_crtc;
	qxl_send_monitors_config(qdev);
पूर्ण

अटल व्योम qxl_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	qxl_crtc_update_monitors_config(crtc, "flush");
पूर्ण

अटल व्योम qxl_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा qxl_crtc *qxl_crtc = to_qxl_crtc(crtc);

	qxl_bo_unref(&qxl_crtc->cursor_bo);
	drm_crtc_cleanup(crtc);
	kमुक्त(qxl_crtc);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs qxl_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.destroy = qxl_crtc_destroy,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
पूर्ण;

अटल पूर्णांक qxl_framebuffer_surface_dirty(काष्ठा drm_framebuffer *fb,
					 काष्ठा drm_file *file_priv,
					 अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक color,
					 काष्ठा drm_clip_rect *clips,
					 अचिन्हित पूर्णांक num_clips)
अणु
	/* TODO: vmwgfx where this was cribbed from had locking. Why? */
	काष्ठा qxl_device *qdev = to_qxl(fb->dev);
	काष्ठा drm_clip_rect norect;
	काष्ठा qxl_bo *qobj;
	काष्ठा drm_modeset_acquire_ctx ctx;
	bool is_primary;
	पूर्णांक inc = 1, ret;

	DRM_MODESET_LOCK_ALL_BEGIN(fb->dev, ctx, DRM_MODESET_ACQUIRE_INTERRUPTIBLE, ret);

	qobj = gem_to_qxl_bo(fb->obj[0]);
	/* अगर we aren't primary surface ignore this */
	is_primary = qobj->shaकरोw ? qobj->shaकरोw->is_primary : qobj->is_primary;
	अगर (!is_primary)
		जाओ out_lock_end;

	अगर (!num_clips) अणु
		num_clips = 1;
		clips = &norect;
		norect.x1 = norect.y1 = 0;
		norect.x2 = fb->width;
		norect.y2 = fb->height;
	पूर्ण अन्यथा अगर (flags & DRM_MODE_FB_सूचीTY_ANNOTATE_COPY) अणु
		num_clips /= 2;
		inc = 2; /* skip source rects */
	पूर्ण

	qxl_draw_dirty_fb(qdev, fb, qobj, flags, color,
			  clips, num_clips, inc, 0);

out_lock_end:
	DRM_MODESET_LOCK_ALL_END(fb->dev, ctx, ret);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs qxl_fb_funcs = अणु
	.destroy = drm_gem_fb_destroy,
	.dirty = qxl_framebuffer_surface_dirty,
	.create_handle = drm_gem_fb_create_handle,
पूर्ण;

अटल व्योम qxl_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	qxl_crtc_update_monitors_config(crtc, "enable");
पूर्ण

अटल व्योम qxl_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	qxl_crtc_update_monitors_config(crtc, "disable");
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs qxl_crtc_helper_funcs = अणु
	.atomic_flush = qxl_crtc_atomic_flush,
	.atomic_enable = qxl_crtc_atomic_enable,
	.atomic_disable = qxl_crtc_atomic_disable,
पूर्ण;

अटल पूर्णांक qxl_primary_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा qxl_device *qdev = to_qxl(plane->dev);
	काष्ठा qxl_bo *bo;

	अगर (!new_plane_state->crtc || !new_plane_state->fb)
		वापस 0;

	bo = gem_to_qxl_bo(new_plane_state->fb->obj[0]);

	वापस qxl_check_framebuffer(qdev, bo);
पूर्ण

अटल पूर्णांक qxl_primary_apply_cursor(काष्ठा qxl_device *qdev,
				    काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा qxl_crtc *qcrtc = to_qxl_crtc(plane_state->crtc);
	काष्ठा qxl_cursor_cmd *cmd;
	काष्ठा qxl_release *release;
	पूर्णांक ret = 0;

	अगर (!qcrtc->cursor_bo)
		वापस 0;

	ret = qxl_alloc_release_reserved(qdev, माप(*cmd),
					 QXL_RELEASE_CURSOR_CMD,
					 &release, शून्य);
	अगर (ret)
		वापस ret;

	ret = qxl_release_list_add(release, qcrtc->cursor_bo);
	अगर (ret)
		जाओ out_मुक्त_release;

	ret = qxl_release_reserve_list(release, false);
	अगर (ret)
		जाओ out_मुक्त_release;

	cmd = (काष्ठा qxl_cursor_cmd *)qxl_release_map(qdev, release);
	cmd->type = QXL_CURSOR_SET;
	cmd->u.set.position.x = plane_state->crtc_x + fb->hot_x;
	cmd->u.set.position.y = plane_state->crtc_y + fb->hot_y;

	cmd->u.set.shape = qxl_bo_physical_address(qdev, qcrtc->cursor_bo, 0);

	cmd->u.set.visible = 1;
	qxl_release_unmap(qdev, release, &cmd->release_info);

	qxl_release_fence_buffer_objects(release);
	qxl_push_cursor_ring_release(qdev, release, QXL_CMD_CURSOR, false);

	वापस ret;

out_मुक्त_release:
	qxl_release_मुक्त(qdev, release);
	वापस ret;
पूर्ण

अटल पूर्णांक qxl_primary_move_cursor(काष्ठा qxl_device *qdev,
				   काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा qxl_crtc *qcrtc = to_qxl_crtc(plane_state->crtc);
	काष्ठा qxl_cursor_cmd *cmd;
	काष्ठा qxl_release *release;
	पूर्णांक ret = 0;

	अगर (!qcrtc->cursor_bo)
		वापस 0;

	ret = qxl_alloc_release_reserved(qdev, माप(*cmd),
					 QXL_RELEASE_CURSOR_CMD,
					 &release, शून्य);
	अगर (ret)
		वापस ret;

	ret = qxl_release_reserve_list(release, true);
	अगर (ret) अणु
		qxl_release_मुक्त(qdev, release);
		वापस ret;
	पूर्ण

	cmd = (काष्ठा qxl_cursor_cmd *)qxl_release_map(qdev, release);
	cmd->type = QXL_CURSOR_MOVE;
	cmd->u.position.x = plane_state->crtc_x + fb->hot_x;
	cmd->u.position.y = plane_state->crtc_y + fb->hot_y;
	qxl_release_unmap(qdev, release, &cmd->release_info);

	qxl_release_fence_buffer_objects(release);
	qxl_push_cursor_ring_release(qdev, release, QXL_CMD_CURSOR, false);
	वापस ret;
पूर्ण

अटल काष्ठा qxl_bo *qxl_create_cursor(काष्ठा qxl_device *qdev,
					काष्ठा qxl_bo *user_bo,
					पूर्णांक hot_x, पूर्णांक hot_y)
अणु
	अटल स्थिर u32 size = 64 * 64 * 4;
	काष्ठा qxl_bo *cursor_bo;
	काष्ठा dma_buf_map cursor_map;
	काष्ठा dma_buf_map user_map;
	काष्ठा qxl_cursor cursor;
	पूर्णांक ret;

	अगर (!user_bo)
		वापस शून्य;

	ret = qxl_bo_create(qdev, माप(काष्ठा qxl_cursor) + size,
			    false, true, QXL_GEM_DOMAIN_VRAM, 1,
			    शून्य, &cursor_bo);
	अगर (ret)
		जाओ err;

	ret = qxl_bo_vmap(cursor_bo, &cursor_map);
	अगर (ret)
		जाओ err_unref;

	ret = qxl_bo_vmap(user_bo, &user_map);
	अगर (ret)
		जाओ err_unmap;

	cursor.header.unique = 0;
	cursor.header.type = SPICE_CURSOR_TYPE_ALPHA;
	cursor.header.width = 64;
	cursor.header.height = 64;
	cursor.header.hot_spot_x = hot_x;
	cursor.header.hot_spot_y = hot_y;
	cursor.data_size = size;
	cursor.chunk.next_chunk = 0;
	cursor.chunk.prev_chunk = 0;
	cursor.chunk.data_size = size;
	अगर (cursor_map.is_iomem) अणु
		स_नकल_toio(cursor_map.vaddr_iomem,
			    &cursor, माप(cursor));
		स_नकल_toio(cursor_map.vaddr_iomem + माप(cursor),
			    user_map.vaddr, size);
	पूर्ण अन्यथा अणु
		स_नकल(cursor_map.vaddr,
		       &cursor, माप(cursor));
		स_नकल(cursor_map.vaddr + माप(cursor),
		       user_map.vaddr, size);
	पूर्ण

	qxl_bo_vunmap(user_bo);
	qxl_bo_vunmap(cursor_bo);
	वापस cursor_bo;

err_unmap:
	qxl_bo_vunmap(cursor_bo);
err_unref:
	qxl_bo_unpin(cursor_bo);
	qxl_bo_unref(&cursor_bo);
err:
	वापस शून्य;
पूर्ण

अटल व्योम qxl_मुक्त_cursor(काष्ठा qxl_bo *cursor_bo)
अणु
	अगर (!cursor_bo)
		वापस;

	qxl_bo_unpin(cursor_bo);
	qxl_bo_unref(&cursor_bo);
पूर्ण

अटल व्योम qxl_primary_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा qxl_device *qdev = to_qxl(plane->dev);
	काष्ठा qxl_bo *bo = gem_to_qxl_bo(new_state->fb->obj[0]);
	काष्ठा qxl_bo *primary;
	काष्ठा drm_clip_rect norect = अणु
	    .x1 = 0,
	    .y1 = 0,
	    .x2 = new_state->fb->width,
	    .y2 = new_state->fb->height
	पूर्ण;
	uपूर्णांक32_t dumb_shaकरोw_offset = 0;

	primary = bo->shaकरोw ? bo->shaकरोw : bo;

	अगर (!primary->is_primary) अणु
		अगर (qdev->primary_bo)
			qxl_io_destroy_primary(qdev);
		qxl_io_create_primary(qdev, primary);
		qxl_primary_apply_cursor(qdev, plane->state);
	पूर्ण

	अगर (bo->is_dumb)
		dumb_shaकरोw_offset =
			qdev->dumb_heads[new_state->crtc->index].x;

	qxl_draw_dirty_fb(qdev, new_state->fb, bo, 0, 0, &norect, 1, 1,
			  dumb_shaकरोw_offset);
पूर्ण

अटल व्योम qxl_primary_atomic_disable(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा qxl_device *qdev = to_qxl(plane->dev);

	अगर (old_state->fb) अणु
		काष्ठा qxl_bo *bo = gem_to_qxl_bo(old_state->fb->obj[0]);

		अगर (bo->shaकरोw)
			bo = bo->shaकरोw;
		अगर (bo->is_primary) अणु
			qxl_io_destroy_primary(qdev);
			bo->is_primary = false;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qxl_cursor_atomic_update(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा qxl_device *qdev = to_qxl(plane->dev);
	काष्ठा drm_framebuffer *fb = new_state->fb;

	अगर (fb != old_state->fb) अणु
		qxl_primary_apply_cursor(qdev, new_state);
	पूर्ण अन्यथा अणु
		qxl_primary_move_cursor(qdev, new_state);
	पूर्ण
पूर्ण

अटल व्योम qxl_cursor_atomic_disable(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा qxl_device *qdev = to_qxl(plane->dev);
	काष्ठा qxl_crtc *qcrtc;
	काष्ठा qxl_release *release;
	काष्ठा qxl_cursor_cmd *cmd;
	पूर्णांक ret;

	ret = qxl_alloc_release_reserved(qdev, माप(*cmd),
					 QXL_RELEASE_CURSOR_CMD,
					 &release, शून्य);
	अगर (ret)
		वापस;

	ret = qxl_release_reserve_list(release, true);
	अगर (ret) अणु
		qxl_release_मुक्त(qdev, release);
		वापस;
	पूर्ण

	cmd = (काष्ठा qxl_cursor_cmd *)qxl_release_map(qdev, release);
	cmd->type = QXL_CURSOR_HIDE;
	qxl_release_unmap(qdev, release, &cmd->release_info);

	qxl_release_fence_buffer_objects(release);
	qxl_push_cursor_ring_release(qdev, release, QXL_CMD_CURSOR, false);

	qcrtc = to_qxl_crtc(old_state->crtc);
	qxl_मुक्त_cursor(qcrtc->cursor_bo);
	qcrtc->cursor_bo = शून्य;
पूर्ण

अटल व्योम qxl_update_dumb_head(काष्ठा qxl_device *qdev,
				 पूर्णांक index, काष्ठा qxl_bo *bo)
अणु
	uपूर्णांक32_t width, height;

	अगर (index >= qdev->monitors_config->max_allowed)
		वापस;

	अगर (bo && bo->is_dumb) अणु
		width = bo->surf.width;
		height = bo->surf.height;
	पूर्ण अन्यथा अणु
		width = 0;
		height = 0;
	पूर्ण

	अगर (qdev->dumb_heads[index].width == width &&
	    qdev->dumb_heads[index].height == height)
		वापस;

	DRM_DEBUG("#%d: %dx%d -> %dx%d\n", index,
		  qdev->dumb_heads[index].width,
		  qdev->dumb_heads[index].height,
		  width, height);
	qdev->dumb_heads[index].width = width;
	qdev->dumb_heads[index].height = height;
पूर्ण

अटल व्योम qxl_calc_dumb_shaकरोw(काष्ठा qxl_device *qdev,
				 काष्ठा qxl_surface *surf)
अणु
	काष्ठा qxl_head *head;
	पूर्णांक i;

	स_रखो(surf, 0, माप(*surf));
	क्रम (i = 0; i < qdev->monitors_config->max_allowed; i++) अणु
		head = qdev->dumb_heads + i;
		head->x = surf->width;
		surf->width += head->width;
		अगर (surf->height < head->height)
			surf->height = head->height;
	पूर्ण
	अगर (surf->width < 64)
		surf->width = 64;
	अगर (surf->height < 64)
		surf->height = 64;
	surf->क्रमmat = SPICE_SURFACE_FMT_32_xRGB;
	surf->stride = surf->width * 4;

	अगर (!qdev->dumb_shaकरोw_bo ||
	    qdev->dumb_shaकरोw_bo->surf.width != surf->width ||
	    qdev->dumb_shaकरोw_bo->surf.height != surf->height)
		DRM_DEBUG("%dx%d\n", surf->width, surf->height);
पूर्ण

अटल व्योम qxl_prepare_shaकरोw(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *user_bo,
			       पूर्णांक crtc_index)
अणु
	काष्ठा qxl_surface surf;

	qxl_update_dumb_head(qdev, crtc_index,
			     user_bo);
	qxl_calc_dumb_shaकरोw(qdev, &surf);
	अगर (!qdev->dumb_shaकरोw_bo ||
	    qdev->dumb_shaकरोw_bo->surf.width  != surf.width ||
	    qdev->dumb_shaकरोw_bo->surf.height != surf.height) अणु
		अगर (qdev->dumb_shaकरोw_bo) अणु
			drm_gem_object_put
				(&qdev->dumb_shaकरोw_bo->tbo.base);
			qdev->dumb_shaकरोw_bo = शून्य;
		पूर्ण
		qxl_bo_create(qdev, surf.height * surf.stride,
			      true, true, QXL_GEM_DOMAIN_SURFACE, 0,
			      &surf, &qdev->dumb_shaकरोw_bo);
	पूर्ण
	अगर (user_bo->shaकरोw != qdev->dumb_shaकरोw_bo) अणु
		अगर (user_bo->shaकरोw) अणु
			qxl_bo_unpin(user_bo->shaकरोw);
			drm_gem_object_put
				(&user_bo->shaकरोw->tbo.base);
			user_bo->shaकरोw = शून्य;
		पूर्ण
		drm_gem_object_get(&qdev->dumb_shaकरोw_bo->tbo.base);
		user_bo->shaकरोw = qdev->dumb_shaकरोw_bo;
		qxl_bo_pin(user_bo->shaकरोw);
	पूर्ण
पूर्ण

अटल पूर्णांक qxl_plane_prepare_fb(काष्ठा drm_plane *plane,
				काष्ठा drm_plane_state *new_state)
अणु
	काष्ठा qxl_device *qdev = to_qxl(plane->dev);
	काष्ठा drm_gem_object *obj;
	काष्ठा qxl_bo *user_bo;

	अगर (!new_state->fb)
		वापस 0;

	obj = new_state->fb->obj[0];
	user_bo = gem_to_qxl_bo(obj);

	अगर (plane->type == DRM_PLANE_TYPE_PRIMARY &&
	    user_bo->is_dumb) अणु
		qxl_prepare_shaकरोw(qdev, user_bo, new_state->crtc->index);
	पूर्ण

	अगर (plane->type == DRM_PLANE_TYPE_CURSOR &&
	    plane->state->fb != new_state->fb) अणु
		काष्ठा qxl_crtc *qcrtc = to_qxl_crtc(new_state->crtc);
		काष्ठा qxl_bo *old_cursor_bo = qcrtc->cursor_bo;

		qcrtc->cursor_bo = qxl_create_cursor(qdev, user_bo,
						     new_state->fb->hot_x,
						     new_state->fb->hot_y);
		qxl_मुक्त_cursor(old_cursor_bo);
	पूर्ण

	वापस qxl_bo_pin(user_bo);
पूर्ण

अटल व्योम qxl_plane_cleanup_fb(काष्ठा drm_plane *plane,
				 काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_gem_object *obj;
	काष्ठा qxl_bo *user_bo;

	अगर (!old_state->fb) अणु
		/*
		 * we never executed prepare_fb, so there's nothing to
		 * unpin.
		 */
		वापस;
	पूर्ण

	obj = old_state->fb->obj[0];
	user_bo = gem_to_qxl_bo(obj);
	qxl_bo_unpin(user_bo);

	अगर (old_state->fb != plane->state->fb && user_bo->shaकरोw) अणु
		qxl_bo_unpin(user_bo->shaकरोw);
		drm_gem_object_put(&user_bo->shaकरोw->tbo.base);
		user_bo->shaकरोw = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर uपूर्णांक32_t qxl_cursor_plane_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs qxl_cursor_helper_funcs = अणु
	.atomic_update = qxl_cursor_atomic_update,
	.atomic_disable = qxl_cursor_atomic_disable,
	.prepare_fb = qxl_plane_prepare_fb,
	.cleanup_fb = qxl_plane_cleanup_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs qxl_cursor_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy	= drm_primary_helper_destroy,
	.reset		= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल स्थिर uपूर्णांक32_t qxl_primary_plane_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs primary_helper_funcs = अणु
	.atomic_check = qxl_primary_atomic_check,
	.atomic_update = qxl_primary_atomic_update,
	.atomic_disable = qxl_primary_atomic_disable,
	.prepare_fb = qxl_plane_prepare_fb,
	.cleanup_fb = qxl_plane_cleanup_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs qxl_primary_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy	= drm_primary_helper_destroy,
	.reset		= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल काष्ठा drm_plane *qxl_create_plane(काष्ठा qxl_device *qdev,
					  अचिन्हित पूर्णांक possible_crtcs,
					  क्रमागत drm_plane_type type)
अणु
	स्थिर काष्ठा drm_plane_helper_funcs *helper_funcs = शून्य;
	काष्ठा drm_plane *plane;
	स्थिर काष्ठा drm_plane_funcs *funcs;
	स्थिर uपूर्णांक32_t *क्रमmats;
	पूर्णांक num_क्रमmats;
	पूर्णांक err;

	अगर (type == DRM_PLANE_TYPE_PRIMARY) अणु
		funcs = &qxl_primary_plane_funcs;
		क्रमmats = qxl_primary_plane_क्रमmats;
		num_क्रमmats = ARRAY_SIZE(qxl_primary_plane_क्रमmats);
		helper_funcs = &primary_helper_funcs;
	पूर्ण अन्यथा अगर (type == DRM_PLANE_TYPE_CURSOR) अणु
		funcs = &qxl_cursor_plane_funcs;
		क्रमmats = qxl_cursor_plane_क्रमmats;
		helper_funcs = &qxl_cursor_helper_funcs;
		num_क्रमmats = ARRAY_SIZE(qxl_cursor_plane_क्रमmats);
	पूर्ण अन्यथा अणु
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	plane = kzalloc(माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	err = drm_universal_plane_init(&qdev->ddev, plane, possible_crtcs,
				       funcs, क्रमmats, num_क्रमmats,
				       शून्य, type, शून्य);
	अगर (err)
		जाओ मुक्त_plane;

	drm_plane_helper_add(plane, helper_funcs);

	वापस plane;

मुक्त_plane:
	kमुक्त(plane);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक qdev_crtc_init(काष्ठा drm_device *dev, पूर्णांक crtc_id)
अणु
	काष्ठा qxl_crtc *qxl_crtc;
	काष्ठा drm_plane *primary, *cursor;
	काष्ठा qxl_device *qdev = to_qxl(dev);
	पूर्णांक r;

	qxl_crtc = kzalloc(माप(काष्ठा qxl_crtc), GFP_KERNEL);
	अगर (!qxl_crtc)
		वापस -ENOMEM;

	primary = qxl_create_plane(qdev, 1 << crtc_id, DRM_PLANE_TYPE_PRIMARY);
	अगर (IS_ERR(primary)) अणु
		r = -ENOMEM;
		जाओ मुक्त_mem;
	पूर्ण

	cursor = qxl_create_plane(qdev, 1 << crtc_id, DRM_PLANE_TYPE_CURSOR);
	अगर (IS_ERR(cursor)) अणु
		r = -ENOMEM;
		जाओ clean_primary;
	पूर्ण

	r = drm_crtc_init_with_planes(dev, &qxl_crtc->base, primary, cursor,
				      &qxl_crtc_funcs, शून्य);
	अगर (r)
		जाओ clean_cursor;

	qxl_crtc->index = crtc_id;
	drm_crtc_helper_add(&qxl_crtc->base, &qxl_crtc_helper_funcs);
	वापस 0;

clean_cursor:
	drm_plane_cleanup(cursor);
	kमुक्त(cursor);
clean_primary:
	drm_plane_cleanup(primary);
	kमुक्त(primary);
मुक्त_mem:
	kमुक्त(qxl_crtc);
	वापस r;
पूर्ण

अटल पूर्णांक qxl_conn_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा qxl_output *output = drm_connector_to_qxl_output(connector);
	अचिन्हित पूर्णांक pwidth = 1024;
	अचिन्हित पूर्णांक pheight = 768;
	पूर्णांक ret = 0;

	अगर (qdev->client_monitors_config) अणु
		काष्ठा qxl_head *head;
		head = &qdev->client_monitors_config->heads[output->index];
		अगर (head->width)
			pwidth = head->width;
		अगर (head->height)
			pheight = head->height;
	पूर्ण

	ret += drm_add_modes_noedid(connector, 8192, 8192);
	ret += qxl_add_extra_modes(connector);
	ret += qxl_add_monitors_config_modes(connector);
	drm_set_preferred_mode(connector, pwidth, pheight);
	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status qxl_conn_mode_valid(काष्ठा drm_connector *connector,
			       काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *ddev = connector->dev;
	काष्ठा qxl_device *qdev = to_qxl(ddev);

	अगर (qxl_check_mode(qdev, mode->hdisplay, mode->vdisplay) != 0)
		वापस MODE_BAD;

	वापस MODE_OK;
पूर्ण

अटल काष्ठा drm_encoder *qxl_best_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा qxl_output *qxl_output =
		drm_connector_to_qxl_output(connector);

	DRM_DEBUG("\n");
	वापस &qxl_output->enc;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs qxl_connector_helper_funcs = अणु
	.get_modes = qxl_conn_get_modes,
	.mode_valid = qxl_conn_mode_valid,
	.best_encoder = qxl_best_encoder,
पूर्ण;

अटल क्रमागत drm_connector_status qxl_conn_detect(
			काष्ठा drm_connector *connector,
			bool क्रमce)
अणु
	काष्ठा qxl_output *output =
		drm_connector_to_qxl_output(connector);
	काष्ठा drm_device *ddev = connector->dev;
	काष्ठा qxl_device *qdev = to_qxl(ddev);
	bool connected = false;

	/* The first monitor is always connected */
	अगर (!qdev->client_monitors_config) अणु
		अगर (output->index == 0)
			connected = true;
	पूर्ण अन्यथा
		connected = qdev->client_monitors_config->count > output->index &&
		     qxl_head_enabled(&qdev->client_monitors_config->heads[output->index]);

	DRM_DEBUG("#%d connected: %d\n", output->index, connected);

	वापस connected ? connector_status_connected
			 : connector_status_disconnected;
पूर्ण

अटल व्योम qxl_conn_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा qxl_output *qxl_output =
		drm_connector_to_qxl_output(connector);

	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(qxl_output);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs qxl_connector_funcs = अणु
	.detect = qxl_conn_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = qxl_conn_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक qxl_mode_create_hotplug_mode_update_property(काष्ठा qxl_device *qdev)
अणु
	अगर (qdev->hotplug_mode_update_property)
		वापस 0;

	qdev->hotplug_mode_update_property =
		drm_property_create_range(&qdev->ddev, DRM_MODE_PROP_IMMUTABLE,
					  "hotplug_mode_update", 0, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक qdev_output_init(काष्ठा drm_device *dev, पूर्णांक num_output)
अणु
	काष्ठा qxl_device *qdev = to_qxl(dev);
	काष्ठा qxl_output *qxl_output;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	qxl_output = kzalloc(माप(काष्ठा qxl_output), GFP_KERNEL);
	अगर (!qxl_output)
		वापस -ENOMEM;

	qxl_output->index = num_output;

	connector = &qxl_output->base;
	encoder = &qxl_output->enc;
	drm_connector_init(dev, &qxl_output->base,
			   &qxl_connector_funcs, DRM_MODE_CONNECTOR_VIRTUAL);

	ret = drm_simple_encoder_init(dev, &qxl_output->enc,
				      DRM_MODE_ENCODER_VIRTUAL);
	अगर (ret) अणु
		drm_err(dev, "drm_simple_encoder_init() failed, error %d\n",
			ret);
		जाओ err_drm_connector_cleanup;
	पूर्ण

	/* we get HPD via client monitors config */
	connector->polled = DRM_CONNECTOR_POLL_HPD;
	encoder->possible_crtcs = 1 << num_output;
	drm_connector_attach_encoder(&qxl_output->base,
					  &qxl_output->enc);
	drm_connector_helper_add(connector, &qxl_connector_helper_funcs);

	drm_object_attach_property(&connector->base,
				   qdev->hotplug_mode_update_property, 0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_x_property, 0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_y_property, 0);
	वापस 0;

err_drm_connector_cleanup:
	drm_connector_cleanup(&qxl_output->base);
	kमुक्त(qxl_output);
	वापस ret;
पूर्ण

अटल काष्ठा drm_framebuffer *
qxl_user_framebuffer_create(काष्ठा drm_device *dev,
			    काष्ठा drm_file *file_priv,
			    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	वापस drm_gem_fb_create_with_funcs(dev, file_priv, mode_cmd,
					    &qxl_fb_funcs);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs qxl_mode_funcs = अणु
	.fb_create = qxl_user_framebuffer_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

पूर्णांक qxl_create_monitors_object(काष्ठा qxl_device *qdev)
अणु
	पूर्णांक ret;
	काष्ठा drm_gem_object *gobj;
	काष्ठा dma_buf_map map;
	पूर्णांक monitors_config_size = माप(काष्ठा qxl_monitors_config) +
		qxl_num_crtc * माप(काष्ठा qxl_head);

	ret = qxl_gem_object_create(qdev, monitors_config_size, 0,
				    QXL_GEM_DOMAIN_VRAM,
				    false, false, शून्य, &gobj);
	अगर (ret) अणु
		DRM_ERROR("%s: failed to create gem ret=%d\n", __func__, ret);
		वापस -ENOMEM;
	पूर्ण
	qdev->monitors_config_bo = gem_to_qxl_bo(gobj);

	ret = qxl_bo_vmap(qdev->monitors_config_bo, &map);
	अगर (ret)
		वापस ret;

	qdev->monitors_config = qdev->monitors_config_bo->kptr;
	qdev->ram_header->monitors_config =
		qxl_bo_physical_address(qdev, qdev->monitors_config_bo, 0);

	स_रखो(qdev->monitors_config, 0, monitors_config_size);
	qdev->dumb_heads = kसुस्मृति(qxl_num_crtc, माप(qdev->dumb_heads[0]),
				   GFP_KERNEL);
	अगर (!qdev->dumb_heads) अणु
		qxl_destroy_monitors_object(qdev);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qxl_destroy_monitors_object(काष्ठा qxl_device *qdev)
अणु
	पूर्णांक ret;

	अगर (!qdev->monitors_config_bo)
		वापस 0;

	qdev->monitors_config = शून्य;
	qdev->ram_header->monitors_config = 0;

	ret = qxl_bo_vunmap(qdev->monitors_config_bo);
	अगर (ret)
		वापस ret;

	qxl_bo_unref(&qdev->monitors_config_bo);
	वापस 0;
पूर्ण

पूर्णांक qxl_modeset_init(काष्ठा qxl_device *qdev)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	ret = drmm_mode_config_init(&qdev->ddev);
	अगर (ret)
		वापस ret;

	ret = qxl_create_monitors_object(qdev);
	अगर (ret)
		वापस ret;

	qdev->ddev.mode_config.funcs = (व्योम *)&qxl_mode_funcs;

	/* modes will be validated against the framebuffer size */
	qdev->ddev.mode_config.min_width = 0;
	qdev->ddev.mode_config.min_height = 0;
	qdev->ddev.mode_config.max_width = 8192;
	qdev->ddev.mode_config.max_height = 8192;

	qdev->ddev.mode_config.fb_base = qdev->vram_base;

	drm_mode_create_suggested_offset_properties(&qdev->ddev);
	qxl_mode_create_hotplug_mode_update_property(qdev);

	क्रम (i = 0 ; i < qxl_num_crtc; ++i) अणु
		qdev_crtc_init(&qdev->ddev, i);
		qdev_output_init(&qdev->ddev, i);
	पूर्ण

	qxl_display_पढ़ो_client_monitors_config(qdev);

	drm_mode_config_reset(&qdev->ddev);
	वापस 0;
पूर्ण

व्योम qxl_modeset_fini(काष्ठा qxl_device *qdev)
अणु
	अगर (qdev->dumb_shaकरोw_bo) अणु
		qxl_bo_unpin(qdev->dumb_shaकरोw_bo);
		drm_gem_object_put(&qdev->dumb_shaकरोw_bo->tbo.base);
		qdev->dumb_shaकरोw_bo = शून्य;
	पूर्ण
	qxl_destroy_monitors_object(qdev);
पूर्ण
