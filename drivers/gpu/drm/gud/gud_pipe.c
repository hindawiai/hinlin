<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright 2020 Noralf Trथचnnes
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/lz4.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_क्रमmat_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_rect.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/gud.h>

#समावेश "gud_internal.h"

/*
 * FIXME: The driver is probably broken on Big Endian machines.
 * See discussion:
 * https://lore.kernel.org/dri-devel/CAKb7UvihLX0hgBOP3VBG7O+atwZcUVCPVuBdfmDMpg0NjXe-cQ@mail.gmail.com/
 */

अटल bool gud_is_big_endian(व्योम)
अणु
#अगर defined(__BIG_ENDIAN)
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल माप_प्रकार gud_xrgb8888_to_r124(u8 *dst, स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
				   व्योम *src, काष्ठा drm_framebuffer *fb,
				   काष्ठा drm_rect *rect)
अणु
	अचिन्हित पूर्णांक block_width = drm_क्रमmat_info_block_width(क्रमmat, 0);
	अचिन्हित पूर्णांक bits_per_pixel = 8 / block_width;
	अचिन्हित पूर्णांक x, y, width, height;
	u8 pix, *pix8, *block = dst; /* Assign to silence compiler warning */
	माप_प्रकार len;
	व्योम *buf;

	WARN_ON_ONCE(क्रमmat->अक्षर_per_block[0] != 1);

	/* Start on a byte boundary */
	rect->x1 = ALIGN_DOWN(rect->x1, block_width);
	width = drm_rect_width(rect);
	height = drm_rect_height(rect);
	len = drm_क्रमmat_info_min_pitch(क्रमmat, 0, width) * height;

	buf = kदो_स्मृति(width * height, GFP_KERNEL);
	अगर (!buf)
		वापस 0;

	drm_fb_xrgb8888_to_gray8(buf, src, fb, rect);
	pix8 = buf;

	क्रम (y = 0; y < height; y++) अणु
		क्रम (x = 0; x < width; x++) अणु
			अचिन्हित पूर्णांक pixpos = x % block_width; /* within byte from the left */
			अचिन्हित पूर्णांक pixshअगरt = (block_width - pixpos - 1) * bits_per_pixel;

			अगर (!pixpos) अणु
				block = dst++;
				*block = 0;
			पूर्ण

			pix = (*pix8++) >> (8 - bits_per_pixel);
			*block |= pix << pixshअगरt;
		पूर्ण
	पूर्ण

	kमुक्त(buf);

	वापस len;
पूर्ण

अटल माप_प्रकार gud_xrgb8888_to_color(u8 *dst, स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
				    व्योम *src, काष्ठा drm_framebuffer *fb,
				    काष्ठा drm_rect *rect)
अणु
	अचिन्हित पूर्णांक block_width = drm_क्रमmat_info_block_width(क्रमmat, 0);
	अचिन्हित पूर्णांक bits_per_pixel = 8 / block_width;
	u8 r, g, b, pix, *block = dst; /* Assign to silence compiler warning */
	अचिन्हित पूर्णांक x, y, width;
	u32 *pix32;
	माप_प्रकार len;

	/* Start on a byte boundary */
	rect->x1 = ALIGN_DOWN(rect->x1, block_width);
	width = drm_rect_width(rect);
	len = drm_क्रमmat_info_min_pitch(क्रमmat, 0, width) * drm_rect_height(rect);

	क्रम (y = rect->y1; y < rect->y2; y++) अणु
		pix32 = src + (y * fb->pitches[0]);
		pix32 += rect->x1;

		क्रम (x = 0; x < width; x++) अणु
			अचिन्हित पूर्णांक pixpos = x % block_width; /* within byte from the left */
			अचिन्हित पूर्णांक pixshअगरt = (block_width - pixpos - 1) * bits_per_pixel;

			अगर (!pixpos) अणु
				block = dst++;
				*block = 0;
			पूर्ण

			r = *pix32 >> 16;
			g = *pix32 >> 8;
			b = *pix32++;

			चयन (क्रमmat->क्रमmat) अणु
			हाल GUD_DRM_FORMAT_XRGB1111:
				pix = ((r >> 7) << 2) | ((g >> 7) << 1) | (b >> 7);
				अवरोध;
			शेष:
				WARN_ON_ONCE(1);
				वापस len;
			पूर्ण

			*block |= pix << pixshअगरt;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक gud_prep_flush(काष्ठा gud_device *gdrm, काष्ठा drm_framebuffer *fb,
			  स्थिर काष्ठा drm_क्रमmat_info *क्रमmat, काष्ठा drm_rect *rect,
			  काष्ठा gud_set_buffer_req *req)
अणु
	काष्ठा dma_buf_attachment *import_attach = fb->obj[0]->import_attach;
	u8 compression = gdrm->compression;
	काष्ठा dma_buf_map map;
	व्योम *vaddr, *buf;
	माप_प्रकार pitch, len;
	पूर्णांक ret = 0;

	pitch = drm_क्रमmat_info_min_pitch(क्रमmat, 0, drm_rect_width(rect));
	len = pitch * drm_rect_height(rect);
	अगर (len > gdrm->bulk_len)
		वापस -E2BIG;

	ret = drm_gem_shmem_vmap(fb->obj[0], &map);
	अगर (ret)
		वापस ret;

	vaddr = map.vaddr + fb->offsets[0];

	अगर (import_attach) अणु
		ret = dma_buf_begin_cpu_access(import_attach->dmabuf, DMA_FROM_DEVICE);
		अगर (ret)
			जाओ vunmap;
	पूर्ण
retry:
	अगर (compression)
		buf = gdrm->compress_buf;
	अन्यथा
		buf = gdrm->bulk_buf;

	/*
	 * Imported buffers are assumed to be ग_लिखो-combined and thus uncached
	 * with slow पढ़ोs (at least on ARM).
	 */
	अगर (क्रमmat != fb->क्रमmat) अणु
		अगर (क्रमmat->क्रमmat == GUD_DRM_FORMAT_R1) अणु
			len = gud_xrgb8888_to_r124(buf, क्रमmat, vaddr, fb, rect);
			अगर (!len) अणु
				ret = -ENOMEM;
				जाओ end_cpu_access;
			पूर्ण
		पूर्ण अन्यथा अगर (क्रमmat->क्रमmat == DRM_FORMAT_RGB565) अणु
			drm_fb_xrgb8888_to_rgb565(buf, vaddr, fb, rect, gud_is_big_endian());
		पूर्ण अन्यथा अणु
			len = gud_xrgb8888_to_color(buf, क्रमmat, vaddr, fb, rect);
		पूर्ण
	पूर्ण अन्यथा अगर (gud_is_big_endian() && क्रमmat->cpp[0] > 1) अणु
		drm_fb_swab(buf, vaddr, fb, rect, !import_attach);
	पूर्ण अन्यथा अगर (compression && !import_attach && pitch == fb->pitches[0]) अणु
		/* can compress directly from the framebuffer */
		buf = vaddr + rect->y1 * pitch;
	पूर्ण अन्यथा अणु
		drm_fb_स_नकल(buf, vaddr, fb, rect);
	पूर्ण

	स_रखो(req, 0, माप(*req));
	req->x = cpu_to_le32(rect->x1);
	req->y = cpu_to_le32(rect->y1);
	req->width = cpu_to_le32(drm_rect_width(rect));
	req->height = cpu_to_le32(drm_rect_height(rect));
	req->length = cpu_to_le32(len);

	अगर (compression & GUD_COMPRESSION_LZ4) अणु
		पूर्णांक complen;

		complen = LZ4_compress_शेष(buf, gdrm->bulk_buf, len, len, gdrm->lz4_comp_mem);
		अगर (complen <= 0) अणु
			compression = 0;
			जाओ retry;
		पूर्ण

		req->compression = GUD_COMPRESSION_LZ4;
		req->compressed_length = cpu_to_le32(complen);
	पूर्ण

end_cpu_access:
	अगर (import_attach)
		dma_buf_end_cpu_access(import_attach->dmabuf, DMA_FROM_DEVICE);
vunmap:
	drm_gem_shmem_vunmap(fb->obj[0], &map);

	वापस ret;
पूर्ण

अटल पूर्णांक gud_flush_rect(काष्ठा gud_device *gdrm, काष्ठा drm_framebuffer *fb,
			  स्थिर काष्ठा drm_क्रमmat_info *क्रमmat, काष्ठा drm_rect *rect)
अणु
	काष्ठा usb_device *usb = gud_to_usb_device(gdrm);
	काष्ठा gud_set_buffer_req req;
	पूर्णांक ret, actual_length;
	माप_प्रकार len, trlen;

	drm_dbg(&gdrm->drm, "Flushing [FB:%d] " DRM_RECT_FMT "\n", fb->base.id, DRM_RECT_ARG(rect));

	ret = gud_prep_flush(gdrm, fb, क्रमmat, rect, &req);
	अगर (ret)
		वापस ret;

	len = le32_to_cpu(req.length);

	अगर (req.compression)
		trlen = le32_to_cpu(req.compressed_length);
	अन्यथा
		trlen = len;

	gdrm->stats_length += len;
	/* Did it wrap around? */
	अगर (gdrm->stats_length <= len && gdrm->stats_actual_length) अणु
		gdrm->stats_length = len;
		gdrm->stats_actual_length = 0;
	पूर्ण
	gdrm->stats_actual_length += trlen;

	अगर (!(gdrm->flags & GUD_DISPLAY_FLAG_FULL_UPDATE) || gdrm->prev_flush_failed) अणु
		ret = gud_usb_set(gdrm, GUD_REQ_SET_BUFFER, 0, &req, माप(req));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = usb_bulk_msg(usb, gdrm->bulk_pipe, gdrm->bulk_buf, trlen,
			   &actual_length, msecs_to_jअगरfies(3000));
	अगर (!ret && trlen != actual_length)
		ret = -EIO;
	अगर (ret)
		gdrm->stats_num_errors++;

	वापस ret;
पूर्ण

व्योम gud_clear_damage(काष्ठा gud_device *gdrm)
अणु
	gdrm->damage.x1 = पूर्णांक_उच्च;
	gdrm->damage.y1 = पूर्णांक_उच्च;
	gdrm->damage.x2 = 0;
	gdrm->damage.y2 = 0;
पूर्ण

अटल व्योम gud_add_damage(काष्ठा gud_device *gdrm, काष्ठा drm_rect *damage)
अणु
	gdrm->damage.x1 = min(gdrm->damage.x1, damage->x1);
	gdrm->damage.y1 = min(gdrm->damage.y1, damage->y1);
	gdrm->damage.x2 = max(gdrm->damage.x2, damage->x2);
	gdrm->damage.y2 = max(gdrm->damage.y2, damage->y2);
पूर्ण

अटल व्योम gud_retry_failed_flush(काष्ठा gud_device *gdrm, काष्ठा drm_framebuffer *fb,
				   काष्ठा drm_rect *damage)
अणु
	/*
	 * pipe_update रुकोs क्रम the worker when the display mode is going to change.
	 * This ensures that the width and height is still the same making it safe to
	 * add back the damage.
	 */

	mutex_lock(&gdrm->damage_lock);
	अगर (!gdrm->fb) अणु
		drm_framebuffer_get(fb);
		gdrm->fb = fb;
	पूर्ण
	gud_add_damage(gdrm, damage);
	mutex_unlock(&gdrm->damage_lock);

	/* Retry only once to aव्योम a possible storm in हाल of जारीs errors. */
	अगर (!gdrm->prev_flush_failed)
		queue_work(प्रणाली_दीर्घ_wq, &gdrm->work);
	gdrm->prev_flush_failed = true;
पूर्ण

व्योम gud_flush_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gud_device *gdrm = container_of(work, काष्ठा gud_device, work);
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_rect damage;
	अचिन्हित पूर्णांक i, lines;
	पूर्णांक idx, ret = 0;
	माप_प्रकार pitch;

	अगर (!drm_dev_enter(&gdrm->drm, &idx))
		वापस;

	mutex_lock(&gdrm->damage_lock);
	fb = gdrm->fb;
	gdrm->fb = शून्य;
	damage = gdrm->damage;
	gud_clear_damage(gdrm);
	mutex_unlock(&gdrm->damage_lock);

	अगर (!fb)
		जाओ out;

	क्रमmat = fb->क्रमmat;
	अगर (क्रमmat->क्रमmat == DRM_FORMAT_XRGB8888 && gdrm->xrgb8888_emulation_क्रमmat)
		क्रमmat = gdrm->xrgb8888_emulation_क्रमmat;

	/* Split update अगर it's too big */
	pitch = drm_क्रमmat_info_min_pitch(क्रमmat, 0, drm_rect_width(&damage));
	lines = drm_rect_height(&damage);

	अगर (gdrm->bulk_len < lines * pitch)
		lines = gdrm->bulk_len / pitch;

	क्रम (i = 0; i < DIV_ROUND_UP(drm_rect_height(&damage), lines); i++) अणु
		काष्ठा drm_rect rect = damage;

		rect.y1 += i * lines;
		rect.y2 = min_t(u32, rect.y1 + lines, damage.y2);

		ret = gud_flush_rect(gdrm, fb, क्रमmat, &rect);
		अगर (ret) अणु
			अगर (ret != -ENODEV && ret != -ECONNRESET &&
			    ret != -ESHUTDOWN && ret != -EPROTO) अणु
				bool prev_flush_failed = gdrm->prev_flush_failed;

				gud_retry_failed_flush(gdrm, fb, &damage);
				अगर (!prev_flush_failed)
					dev_err_ratelimited(fb->dev->dev,
							    "Failed to flush framebuffer: error=%d\n", ret);
			पूर्ण
			अवरोध;
		पूर्ण

		gdrm->prev_flush_failed = false;
	पूर्ण

	drm_framebuffer_put(fb);
out:
	drm_dev_निकास(idx);
पूर्ण

अटल व्योम gud_fb_queue_damage(काष्ठा gud_device *gdrm, काष्ठा drm_framebuffer *fb,
				काष्ठा drm_rect *damage)
अणु
	काष्ठा drm_framebuffer *old_fb = शून्य;

	mutex_lock(&gdrm->damage_lock);

	अगर (fb != gdrm->fb) अणु
		old_fb = gdrm->fb;
		drm_framebuffer_get(fb);
		gdrm->fb = fb;
	पूर्ण

	gud_add_damage(gdrm, damage);

	mutex_unlock(&gdrm->damage_lock);

	queue_work(प्रणाली_दीर्घ_wq, &gdrm->work);

	अगर (old_fb)
		drm_framebuffer_put(old_fb);
पूर्ण

पूर्णांक gud_pipe_check(काष्ठा drm_simple_display_pipe *pipe,
		   काष्ठा drm_plane_state *new_plane_state,
		   काष्ठा drm_crtc_state *new_crtc_state)
अणु
	काष्ठा gud_device *gdrm = to_gud_device(pipe->crtc.dev);
	काष्ठा drm_plane_state *old_plane_state = pipe->plane.state;
	स्थिर काष्ठा drm_display_mode *mode = &new_crtc_state->mode;
	काष्ठा drm_atomic_state *state = new_plane_state->state;
	काष्ठा drm_framebuffer *old_fb = old_plane_state->fb;
	काष्ठा drm_connector_state *connector_state = शून्य;
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = fb->क्रमmat;
	काष्ठा drm_connector *connector;
	अचिन्हित पूर्णांक i, num_properties;
	काष्ठा gud_state_req *req;
	पूर्णांक idx, ret;
	माप_प्रकार len;

	अगर (WARN_ON_ONCE(!fb))
		वापस -EINVAL;

	अगर (old_plane_state->rotation != new_plane_state->rotation)
		new_crtc_state->mode_changed = true;

	अगर (old_fb && old_fb->क्रमmat != क्रमmat)
		new_crtc_state->mode_changed = true;

	अगर (!new_crtc_state->mode_changed && !new_crtc_state->connectors_changed)
		वापस 0;

	/* Only one connector is supported */
	अगर (hweight32(new_crtc_state->connector_mask) != 1)
		वापस -EINVAL;

	अगर (क्रमmat->क्रमmat == DRM_FORMAT_XRGB8888 && gdrm->xrgb8888_emulation_क्रमmat)
		क्रमmat = gdrm->xrgb8888_emulation_क्रमmat;

	क्रम_each_new_connector_in_state(state, connector, connector_state, i) अणु
		अगर (connector_state->crtc)
			अवरोध;
	पूर्ण

	/*
	 * DRM_IOCTL_MODE_OBJ_SETPROPERTY on the rotation property will not have
	 * the connector included in the state.
	 */
	अगर (!connector_state) अणु
		काष्ठा drm_connector_list_iter conn_iter;

		drm_connector_list_iter_begin(pipe->crtc.dev, &conn_iter);
		drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
			अगर (connector->state->crtc) अणु
				connector_state = connector->state;
				अवरोध;
			पूर्ण
		पूर्ण
		drm_connector_list_iter_end(&conn_iter);
	पूर्ण

	अगर (WARN_ON_ONCE(!connector_state))
		वापस -ENOENT;

	len = काष्ठा_size(req, properties,
			  GUD_PROPERTIES_MAX_NUM + GUD_CONNECTOR_PROPERTIES_MAX_NUM);
	req = kzalloc(len, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	gud_from_display_mode(&req->mode, mode);

	req->क्रमmat = gud_from_fourcc(क्रमmat->क्रमmat);
	अगर (WARN_ON_ONCE(!req->क्रमmat)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	req->connector = drm_connector_index(connector_state->connector);

	ret = gud_connector_fill_properties(connector_state, req->properties);
	अगर (ret < 0)
		जाओ out;

	num_properties = ret;
	क्रम (i = 0; i < gdrm->num_properties; i++) अणु
		u16 prop = gdrm->properties[i];
		u64 val;

		चयन (prop) अणु
		हाल GUD_PROPERTY_ROTATION:
			/* DRM UAPI matches the protocol so use value directly */
			val = new_plane_state->rotation;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		req->properties[num_properties + i].prop = cpu_to_le16(prop);
		req->properties[num_properties + i].val = cpu_to_le64(val);
		num_properties++;
	पूर्ण

	अगर (drm_dev_enter(fb->dev, &idx)) अणु
		len = काष्ठा_size(req, properties, num_properties);
		ret = gud_usb_set(gdrm, GUD_REQ_SET_STATE_CHECK, 0, req, len);
		drm_dev_निकास(idx);
	पूर्ण  अन्यथा अणु
		ret = -ENODEV;
	पूर्ण
out:
	kमुक्त(req);

	वापस ret;
पूर्ण

व्योम gud_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
		     काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_device *drm = pipe->crtc.dev;
	काष्ठा gud_device *gdrm = to_gud_device(drm);
	काष्ठा drm_plane_state *state = pipe->plane.state;
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_rect damage;
	पूर्णांक idx;

	अगर (crtc->state->mode_changed || !crtc->state->enable) अणु
		cancel_work_sync(&gdrm->work);
		mutex_lock(&gdrm->damage_lock);
		अगर (gdrm->fb) अणु
			drm_framebuffer_put(gdrm->fb);
			gdrm->fb = शून्य;
		पूर्ण
		gud_clear_damage(gdrm);
		mutex_unlock(&gdrm->damage_lock);
	पूर्ण

	अगर (!drm_dev_enter(drm, &idx))
		वापस;

	अगर (!old_state->fb)
		gud_usb_set_u8(gdrm, GUD_REQ_SET_CONTROLLER_ENABLE, 1);

	अगर (fb && (crtc->state->mode_changed || crtc->state->connectors_changed))
		gud_usb_set(gdrm, GUD_REQ_SET_STATE_COMMIT, 0, शून्य, 0);

	अगर (crtc->state->active_changed)
		gud_usb_set_u8(gdrm, GUD_REQ_SET_DISPLAY_ENABLE, crtc->state->active);

	अगर (drm_atomic_helper_damage_merged(old_state, state, &damage)) अणु
		अगर (gdrm->flags & GUD_DISPLAY_FLAG_FULL_UPDATE)
			drm_rect_init(&damage, 0, 0, fb->width, fb->height);
		gud_fb_queue_damage(gdrm, fb, &damage);
	पूर्ण

	अगर (!crtc->state->enable)
		gud_usb_set_u8(gdrm, GUD_REQ_SET_CONTROLLER_ENABLE, 0);

	drm_dev_निकास(idx);
पूर्ण
