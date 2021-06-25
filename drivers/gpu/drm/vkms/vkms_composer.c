<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/crc32.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "vkms_drv.h"

अटल u32 get_pixel_from_buffer(पूर्णांक x, पूर्णांक y, स्थिर u8 *buffer,
				 स्थिर काष्ठा vkms_composer *composer)
अणु
	u32 pixel;
	पूर्णांक src_offset = composer->offset + (y * composer->pitch)
				      + (x * composer->cpp);

	pixel = *(u32 *)&buffer[src_offset];

	वापस pixel;
पूर्ण

/**
 * compute_crc - Compute CRC value on output frame
 *
 * @vaddr: address to final framebuffer
 * @composer: framebuffer's metadata
 *
 * वापसs CRC value computed using crc32 on the visible portion of
 * the final framebuffer at vaddr_out
 */
अटल uपूर्णांक32_t compute_crc(स्थिर u8 *vaddr,
			    स्थिर काष्ठा vkms_composer *composer)
अणु
	पूर्णांक x, y;
	u32 crc = 0, pixel = 0;
	पूर्णांक x_src = composer->src.x1 >> 16;
	पूर्णांक y_src = composer->src.y1 >> 16;
	पूर्णांक h_src = drm_rect_height(&composer->src) >> 16;
	पूर्णांक w_src = drm_rect_width(&composer->src) >> 16;

	क्रम (y = y_src; y < y_src + h_src; ++y) अणु
		क्रम (x = x_src; x < x_src + w_src; ++x) अणु
			pixel = get_pixel_from_buffer(x, y, vaddr, composer);
			crc = crc32_le(crc, (व्योम *)&pixel, माप(u32));
		पूर्ण
	पूर्ण

	वापस crc;
पूर्ण

अटल u8 blend_channel(u8 src, u8 dst, u8 alpha)
अणु
	u32 pre_blend;
	u8 new_color;

	pre_blend = (src * 255 + dst * (255 - alpha));

	/* Faster भाग by 255 */
	new_color = ((pre_blend + ((pre_blend + 257) >> 8)) >> 8);

	वापस new_color;
पूर्ण

अटल व्योम alpha_blending(स्थिर u8 *argb_src, u8 *argb_dst)
अणु
	u8 alpha;

	alpha = argb_src[3];
	argb_dst[0] = blend_channel(argb_src[0], argb_dst[0], alpha);
	argb_dst[1] = blend_channel(argb_src[1], argb_dst[1], alpha);
	argb_dst[2] = blend_channel(argb_src[2], argb_dst[2], alpha);
	/* Opaque primary */
	argb_dst[3] = 0xFF;
पूर्ण

/**
 * blend - blend value at vaddr_src with value at vaddr_dst
 * @vaddr_dst: destination address
 * @vaddr_src: source address
 * @dst_composer: destination framebuffer's metadata
 * @src_composer: source framebuffer's metadata
 *
 * Blend the vaddr_src value with the vaddr_dst value using the pre-multiplied
 * alpha blending equation, since DRM currently assumes that the pixel color
 * values have alपढ़ोy been pre-multiplied with the alpha channel values. See
 * more drm_plane_create_blend_mode_property(). This function uses buffer's
 * metadata to locate the new composite values at vaddr_dst.
 */
अटल व्योम blend(व्योम *vaddr_dst, व्योम *vaddr_src,
		  काष्ठा vkms_composer *dst_composer,
		  काष्ठा vkms_composer *src_composer)
अणु
	पूर्णांक i, j, j_dst, i_dst;
	पूर्णांक offset_src, offset_dst;
	u8 *pixel_dst, *pixel_src;

	पूर्णांक x_src = src_composer->src.x1 >> 16;
	पूर्णांक y_src = src_composer->src.y1 >> 16;

	पूर्णांक x_dst = src_composer->dst.x1;
	पूर्णांक y_dst = src_composer->dst.y1;
	पूर्णांक h_dst = drm_rect_height(&src_composer->dst);
	पूर्णांक w_dst = drm_rect_width(&src_composer->dst);

	पूर्णांक y_limit = y_src + h_dst;
	पूर्णांक x_limit = x_src + w_dst;

	क्रम (i = y_src, i_dst = y_dst; i < y_limit; ++i) अणु
		क्रम (j = x_src, j_dst = x_dst; j < x_limit; ++j) अणु
			offset_dst = dst_composer->offset
				     + (i_dst * dst_composer->pitch)
				     + (j_dst++ * dst_composer->cpp);
			offset_src = src_composer->offset
				     + (i * src_composer->pitch)
				     + (j * src_composer->cpp);

			pixel_src = (u8 *)(vaddr_src + offset_src);
			pixel_dst = (u8 *)(vaddr_dst + offset_dst);
			alpha_blending(pixel_src, pixel_dst);
		पूर्ण
		i_dst++;
	पूर्ण
पूर्ण

अटल व्योम compose_cursor(काष्ठा vkms_composer *cursor_composer,
			   काष्ठा vkms_composer *primary_composer,
			   व्योम *vaddr_out)
अणु
	काष्ठा drm_gem_object *cursor_obj;
	काष्ठा drm_gem_shmem_object *cursor_shmem_obj;

	cursor_obj = drm_gem_fb_get_obj(&cursor_composer->fb, 0);
	cursor_shmem_obj = to_drm_gem_shmem_obj(cursor_obj);

	अगर (WARN_ON(!cursor_shmem_obj->vaddr))
		वापस;

	blend(vaddr_out, cursor_shmem_obj->vaddr,
	      primary_composer, cursor_composer);
पूर्ण

अटल पूर्णांक compose_planes(व्योम **vaddr_out,
			  काष्ठा vkms_composer *primary_composer,
			  काष्ठा vkms_composer *cursor_composer)
अणु
	काष्ठा drm_framebuffer *fb = &primary_composer->fb;
	काष्ठा drm_gem_object *gem_obj = drm_gem_fb_get_obj(fb, 0);
	काष्ठा drm_gem_shmem_object *shmem_obj = to_drm_gem_shmem_obj(gem_obj);

	अगर (!*vaddr_out) अणु
		*vaddr_out = kzalloc(shmem_obj->base.size, GFP_KERNEL);
		अगर (!*vaddr_out) अणु
			DRM_ERROR("Cannot allocate memory for output frame.");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(!shmem_obj->vaddr))
		वापस -EINVAL;

	स_नकल(*vaddr_out, shmem_obj->vaddr, shmem_obj->base.size);

	अगर (cursor_composer)
		compose_cursor(cursor_composer, primary_composer, *vaddr_out);

	वापस 0;
पूर्ण

/**
 * vkms_composer_worker - ordered work_काष्ठा to compute CRC
 *
 * @work: work_काष्ठा
 *
 * Work handler क्रम composing and computing CRCs. work_काष्ठा scheduled in
 * an ordered workqueue that's periodically scheduled to run by
 * _vblank_handle() and flushed at vkms_atomic_crtc_destroy_state().
 */
व्योम vkms_composer_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vkms_crtc_state *crtc_state = container_of(work,
						काष्ठा vkms_crtc_state,
						composer_work);
	काष्ठा drm_crtc *crtc = crtc_state->base.crtc;
	काष्ठा vkms_output *out = drm_crtc_to_vkms_output(crtc);
	काष्ठा vkms_composer *primary_composer = शून्य;
	काष्ठा vkms_composer *cursor_composer = शून्य;
	bool crc_pending, wb_pending;
	व्योम *vaddr_out = शून्य;
	u32 crc32 = 0;
	u64 frame_start, frame_end;
	पूर्णांक ret;

	spin_lock_irq(&out->composer_lock);
	frame_start = crtc_state->frame_start;
	frame_end = crtc_state->frame_end;
	crc_pending = crtc_state->crc_pending;
	wb_pending = crtc_state->wb_pending;
	crtc_state->frame_start = 0;
	crtc_state->frame_end = 0;
	crtc_state->crc_pending = false;
	spin_unlock_irq(&out->composer_lock);

	/*
	 * We raced with the vblank hrसमयr and previous work alपढ़ोy computed
	 * the crc, nothing to करो.
	 */
	अगर (!crc_pending)
		वापस;

	अगर (crtc_state->num_active_planes >= 1)
		primary_composer = crtc_state->active_planes[0]->composer;

	अगर (crtc_state->num_active_planes == 2)
		cursor_composer = crtc_state->active_planes[1]->composer;

	अगर (!primary_composer)
		वापस;

	अगर (wb_pending)
		vaddr_out = crtc_state->active_ग_लिखोback;

	ret = compose_planes(&vaddr_out, primary_composer, cursor_composer);
	अगर (ret) अणु
		अगर (ret == -EINVAL && !wb_pending)
			kमुक्त(vaddr_out);
		वापस;
	पूर्ण

	crc32 = compute_crc(vaddr_out, primary_composer);

	अगर (wb_pending) अणु
		drm_ग_लिखोback_संकेत_completion(&out->wb_connector, 0);
		spin_lock_irq(&out->composer_lock);
		crtc_state->wb_pending = false;
		spin_unlock_irq(&out->composer_lock);
	पूर्ण अन्यथा अणु
		kमुक्त(vaddr_out);
	पूर्ण

	/*
	 * The worker can fall behind the vblank hrसमयr, make sure we catch up.
	 */
	जबतक (frame_start <= frame_end)
		drm_crtc_add_crc_entry(crtc, true, frame_start++, &crc32);
पूर्ण

अटल स्थिर अक्षर * स्थिर pipe_crc_sources[] = अणु"auto"पूर्ण;

स्थिर अक्षर *स्थिर *vkms_get_crc_sources(काष्ठा drm_crtc *crtc,
					माप_प्रकार *count)
अणु
	*count = ARRAY_SIZE(pipe_crc_sources);
	वापस pipe_crc_sources;
पूर्ण

अटल पूर्णांक vkms_crc_parse_source(स्थिर अक्षर *src_name, bool *enabled)
अणु
	पूर्णांक ret = 0;

	अगर (!src_name) अणु
		*enabled = false;
	पूर्ण अन्यथा अगर (म_भेद(src_name, "auto") == 0) अणु
		*enabled = true;
	पूर्ण अन्यथा अणु
		*enabled = false;
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vkms_verअगरy_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *src_name,
			   माप_प्रकार *values_cnt)
अणु
	bool enabled;

	अगर (vkms_crc_parse_source(src_name, &enabled) < 0) अणु
		DRM_DEBUG_DRIVER("unknown source %s\n", src_name);
		वापस -EINVAL;
	पूर्ण

	*values_cnt = 1;

	वापस 0;
पूर्ण

व्योम vkms_set_composer(काष्ठा vkms_output *out, bool enabled)
अणु
	bool old_enabled;

	अगर (enabled)
		drm_crtc_vblank_get(&out->crtc);

	spin_lock_irq(&out->lock);
	old_enabled = out->composer_enabled;
	out->composer_enabled = enabled;
	spin_unlock_irq(&out->lock);

	अगर (old_enabled)
		drm_crtc_vblank_put(&out->crtc);
पूर्ण

पूर्णांक vkms_set_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *src_name)
अणु
	काष्ठा vkms_output *out = drm_crtc_to_vkms_output(crtc);
	bool enabled = false;
	पूर्णांक ret = 0;

	ret = vkms_crc_parse_source(src_name, &enabled);

	vkms_set_composer(out, enabled);

	वापस ret;
पूर्ण
