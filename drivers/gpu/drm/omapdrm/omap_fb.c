<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob@ti.com>
 */

#समावेश <linux/dma-mapping.h>

#समावेश <drm/drm_modeset_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>

#समावेश "omap_dmm_tiler.h"
#समावेश "omap_drv.h"

/*
 * framebuffer funcs
 */

अटल स्थिर u32 क्रमmats[] = अणु
	/* 16bpp [A]RGB: */
	DRM_FORMAT_RGB565, /* RGB16-565 */
	DRM_FORMAT_RGBX4444, /* RGB12x-4444 */
	DRM_FORMAT_XRGB4444, /* xRGB12-4444 */
	DRM_FORMAT_RGBA4444, /* RGBA12-4444 */
	DRM_FORMAT_ARGB4444, /* ARGB16-4444 */
	DRM_FORMAT_XRGB1555, /* xRGB15-1555 */
	DRM_FORMAT_ARGB1555, /* ARGB16-1555 */
	/* 24bpp RGB: */
	DRM_FORMAT_RGB888,   /* RGB24-888 */
	/* 32bpp [A]RGB: */
	DRM_FORMAT_RGBX8888, /* RGBx24-8888 */
	DRM_FORMAT_XRGB8888, /* xRGB24-8888 */
	DRM_FORMAT_RGBA8888, /* RGBA32-8888 */
	DRM_FORMAT_ARGB8888, /* ARGB32-8888 */
	/* YUV: */
	DRM_FORMAT_NV12,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_UYVY,
पूर्ण;

/* per-plane info क्रम the fb: */
काष्ठा plane अणु
	dma_addr_t dma_addr;
पूर्ण;

#घोषणा to_omap_framebuffer(x) container_of(x, काष्ठा omap_framebuffer, base)

काष्ठा omap_framebuffer अणु
	काष्ठा drm_framebuffer base;
	पूर्णांक pin_count;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat;
	काष्ठा plane planes[2];
	/* lock क्रम pinning (pin_count and planes.dma_addr) */
	काष्ठा mutex lock;
पूर्ण;

अटल पूर्णांक omap_framebuffer_dirty(काष्ठा drm_framebuffer *fb,
				  काष्ठा drm_file *file_priv,
				  अचिन्हित flags, अचिन्हित color,
				  काष्ठा drm_clip_rect *clips,
				  अचिन्हित num_clips)
अणु
	काष्ठा drm_crtc *crtc;

	drm_modeset_lock_all(fb->dev);

	drm_क्रम_each_crtc(crtc, fb->dev)
		omap_crtc_flush(crtc);

	drm_modeset_unlock_all(fb->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs omap_framebuffer_funcs = अणु
	.create_handle = drm_gem_fb_create_handle,
	.dirty = omap_framebuffer_dirty,
	.destroy = drm_gem_fb_destroy,
पूर्ण;

अटल u32 get_linear_addr(काष्ठा drm_framebuffer *fb,
		स्थिर काष्ठा drm_क्रमmat_info *क्रमmat, पूर्णांक n, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा omap_framebuffer *omap_fb = to_omap_framebuffer(fb);
	काष्ठा plane *plane = &omap_fb->planes[n];
	u32 offset;

	offset = fb->offsets[n]
	       + (x * क्रमmat->cpp[n] / (n == 0 ? 1 : क्रमmat->hsub))
	       + (y * fb->pitches[n] / (n == 0 ? 1 : क्रमmat->vsub));

	वापस plane->dma_addr + offset;
पूर्ण

bool omap_framebuffer_supports_rotation(काष्ठा drm_framebuffer *fb)
अणु
	वापस omap_gem_flags(fb->obj[0]) & OMAP_BO_TILED_MASK;
पूर्ण

/* Note: DRM rotates counter-घड़ीwise, TILER & DSS rotates घड़ीwise */
अटल u32 drm_rotation_to_tiler(अचिन्हित पूर्णांक drm_rot)
अणु
	u32 orient;

	चयन (drm_rot & DRM_MODE_ROTATE_MASK) अणु
	शेष:
	हाल DRM_MODE_ROTATE_0:
		orient = 0;
		अवरोध;
	हाल DRM_MODE_ROTATE_90:
		orient = MASK_XY_FLIP | MASK_X_INVERT;
		अवरोध;
	हाल DRM_MODE_ROTATE_180:
		orient = MASK_X_INVERT | MASK_Y_INVERT;
		अवरोध;
	हाल DRM_MODE_ROTATE_270:
		orient = MASK_XY_FLIP | MASK_Y_INVERT;
		अवरोध;
	पूर्ण

	अगर (drm_rot & DRM_MODE_REFLECT_X)
		orient ^= MASK_X_INVERT;

	अगर (drm_rot & DRM_MODE_REFLECT_Y)
		orient ^= MASK_Y_INVERT;

	वापस orient;
पूर्ण

/* update ovl info क्रम scanout, handles हालs of multi-planar fb's, etc.
 */
व्योम omap_framebuffer_update_scanout(काष्ठा drm_framebuffer *fb,
		काष्ठा drm_plane_state *state, काष्ठा omap_overlay_info *info)
अणु
	काष्ठा omap_framebuffer *omap_fb = to_omap_framebuffer(fb);
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = omap_fb->क्रमmat;
	u32 x, y, orient = 0;

	info->fourcc = fb->क्रमmat->क्रमmat;

	info->pos_x      = state->crtc_x;
	info->pos_y      = state->crtc_y;
	info->out_width  = state->crtc_w;
	info->out_height = state->crtc_h;
	info->width      = state->src_w >> 16;
	info->height     = state->src_h >> 16;

	/* DSS driver wants the w & h in rotated orientation */
	अगर (drm_rotation_90_or_270(state->rotation))
		swap(info->width, info->height);

	x = state->src_x >> 16;
	y = state->src_y >> 16;

	अगर (omap_gem_flags(fb->obj[0]) & OMAP_BO_TILED_MASK) अणु
		u32 w = state->src_w >> 16;
		u32 h = state->src_h >> 16;

		orient = drm_rotation_to_tiler(state->rotation);

		/*
		 * omap_gem_rotated_paddr() wants the x & y in tiler units.
		 * Usually tiler unit size is the same as the pixel size, except
		 * क्रम YUV422 क्रमmats, क्रम which the tiler unit size is 32 bits
		 * and pixel size is 16 bits.
		 */
		अगर (fb->क्रमmat->क्रमmat == DRM_FORMAT_UYVY ||
				fb->क्रमmat->क्रमmat == DRM_FORMAT_YUYV) अणु
			x /= 2;
			w /= 2;
		पूर्ण

		/* adjust x,y offset क्रम invert: */
		अगर (orient & MASK_Y_INVERT)
			y += h - 1;
		अगर (orient & MASK_X_INVERT)
			x += w - 1;

		/* Note: x and y are in TILER units, not pixels */
		omap_gem_rotated_dma_addr(fb->obj[0], orient, x, y,
					  &info->paddr);
		info->rotation_type = OMAP_DSS_ROT_TILER;
		info->rotation = state->rotation ?: DRM_MODE_ROTATE_0;
		/* Note: stride in TILER units, not pixels */
		info->screen_width  = omap_gem_tiled_stride(fb->obj[0], orient);
	पूर्ण अन्यथा अणु
		चयन (state->rotation & DRM_MODE_ROTATE_MASK) अणु
		हाल 0:
		हाल DRM_MODE_ROTATE_0:
			/* OK */
			अवरोध;

		शेष:
			dev_warn(fb->dev->dev,
				"rotation '%d' ignored for non-tiled fb\n",
				state->rotation);
			अवरोध;
		पूर्ण

		info->paddr         = get_linear_addr(fb, क्रमmat, 0, x, y);
		info->rotation_type = OMAP_DSS_ROT_NONE;
		info->rotation      = DRM_MODE_ROTATE_0;
		info->screen_width  = fb->pitches[0];
	पूर्ण

	/* convert to pixels: */
	info->screen_width /= क्रमmat->cpp[0];

	अगर (fb->क्रमmat->क्रमmat == DRM_FORMAT_NV12) अणु
		अगर (info->rotation_type == OMAP_DSS_ROT_TILER) अणु
			WARN_ON(!(omap_gem_flags(fb->obj[1]) & OMAP_BO_TILED_MASK));
			omap_gem_rotated_dma_addr(fb->obj[1], orient, x/2, y/2,
						  &info->p_uv_addr);
		पूर्ण अन्यथा अणु
			info->p_uv_addr = get_linear_addr(fb, क्रमmat, 1, x, y);
		पूर्ण
	पूर्ण अन्यथा अणु
		info->p_uv_addr = 0;
	पूर्ण
पूर्ण

/* pin, prepare क्रम scanout: */
पूर्णांक omap_framebuffer_pin(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा omap_framebuffer *omap_fb = to_omap_framebuffer(fb);
	पूर्णांक ret, i, n = fb->क्रमmat->num_planes;

	mutex_lock(&omap_fb->lock);

	अगर (omap_fb->pin_count > 0) अणु
		omap_fb->pin_count++;
		mutex_unlock(&omap_fb->lock);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा plane *plane = &omap_fb->planes[i];
		ret = omap_gem_pin(fb->obj[i], &plane->dma_addr);
		अगर (ret)
			जाओ fail;
		omap_gem_dma_sync_buffer(fb->obj[i], DMA_TO_DEVICE);
	पूर्ण

	omap_fb->pin_count++;

	mutex_unlock(&omap_fb->lock);

	वापस 0;

fail:
	क्रम (i--; i >= 0; i--) अणु
		काष्ठा plane *plane = &omap_fb->planes[i];
		omap_gem_unpin(fb->obj[i]);
		plane->dma_addr = 0;
	पूर्ण

	mutex_unlock(&omap_fb->lock);

	वापस ret;
पूर्ण

/* unpin, no दीर्घer being scanned out: */
व्योम omap_framebuffer_unpin(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा omap_framebuffer *omap_fb = to_omap_framebuffer(fb);
	पूर्णांक i, n = fb->क्रमmat->num_planes;

	mutex_lock(&omap_fb->lock);

	omap_fb->pin_count--;

	अगर (omap_fb->pin_count > 0) अणु
		mutex_unlock(&omap_fb->lock);
		वापस;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा plane *plane = &omap_fb->planes[i];
		omap_gem_unpin(fb->obj[i]);
		plane->dma_addr = 0;
	पूर्ण

	mutex_unlock(&omap_fb->lock);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
व्योम omap_framebuffer_describe(काष्ठा drm_framebuffer *fb, काष्ठा seq_file *m)
अणु
	पूर्णांक i, n = fb->क्रमmat->num_planes;

	seq_म_लिखो(m, "fb: %dx%d@%4.4s\n", fb->width, fb->height,
			(अक्षर *)&fb->क्रमmat->क्रमmat);

	क्रम (i = 0; i < n; i++) अणु
		seq_म_लिखो(m, "   %d: offset=%d pitch=%d, obj: ",
				i, fb->offsets[n], fb->pitches[i]);
		omap_gem_describe(fb->obj[i], m);
	पूर्ण
पूर्ण
#पूर्ण_अगर

काष्ठा drm_framebuffer *omap_framebuffer_create(काष्ठा drm_device *dev,
		काष्ठा drm_file *file, स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_get_क्रमmat_info(dev,
								 mode_cmd);
	अचिन्हित पूर्णांक num_planes = info->num_planes;
	काष्ठा drm_gem_object *bos[4];
	काष्ठा drm_framebuffer *fb;
	पूर्णांक i;

	क्रम (i = 0; i < num_planes; i++) अणु
		bos[i] = drm_gem_object_lookup(file, mode_cmd->handles[i]);
		अगर (!bos[i]) अणु
			fb = ERR_PTR(-ENOENT);
			जाओ error;
		पूर्ण
	पूर्ण

	fb = omap_framebuffer_init(dev, mode_cmd, bos);
	अगर (IS_ERR(fb))
		जाओ error;

	वापस fb;

error:
	जबतक (--i >= 0)
		drm_gem_object_put(bos[i]);

	वापस fb;
पूर्ण

काष्ठा drm_framebuffer *omap_framebuffer_init(काष्ठा drm_device *dev,
		स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd, काष्ठा drm_gem_object **bos)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = शून्य;
	काष्ठा omap_framebuffer *omap_fb = शून्य;
	काष्ठा drm_framebuffer *fb = शून्य;
	अचिन्हित पूर्णांक pitch = mode_cmd->pitches[0];
	पूर्णांक ret, i;

	DBG("create framebuffer: dev=%p, mode_cmd=%p (%dx%d@%4.4s)",
			dev, mode_cmd, mode_cmd->width, mode_cmd->height,
			(अक्षर *)&mode_cmd->pixel_क्रमmat);

	क्रमmat = drm_get_क्रमmat_info(dev, mode_cmd);

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (क्रमmats[i] == mode_cmd->pixel_क्रमmat)
			अवरोध;
	पूर्ण

	अगर (!क्रमmat || i == ARRAY_SIZE(क्रमmats)) अणु
		dev_dbg(dev->dev, "unsupported pixel format: %4.4s\n",
			(अक्षर *)&mode_cmd->pixel_क्रमmat);
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	omap_fb = kzalloc(माप(*omap_fb), GFP_KERNEL);
	अगर (!omap_fb) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	fb = &omap_fb->base;
	omap_fb->क्रमmat = क्रमmat;
	mutex_init(&omap_fb->lock);

	/*
	 * The code below assumes that no क्रमmat use more than two planes, and
	 * that the two planes of multiplane क्रमmats need the same number of
	 * bytes per pixel.
	 */
	अगर (क्रमmat->num_planes == 2 && pitch != mode_cmd->pitches[1]) अणु
		dev_dbg(dev->dev, "pitches differ between planes 0 and 1\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (pitch % क्रमmat->cpp[0]) अणु
		dev_dbg(dev->dev,
			"buffer pitch (%u bytes) is not a multiple of pixel size (%u bytes)\n",
			pitch, क्रमmat->cpp[0]);
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	क्रम (i = 0; i < क्रमmat->num_planes; i++) अणु
		काष्ठा plane *plane = &omap_fb->planes[i];
		अचिन्हित पूर्णांक vsub = i == 0 ? 1 : क्रमmat->vsub;
		अचिन्हित पूर्णांक size;

		size = pitch * mode_cmd->height / vsub;

		अगर (size > omap_gem_mmap_size(bos[i]) - mode_cmd->offsets[i]) अणु
			dev_dbg(dev->dev,
				"provided buffer object is too small! %zu < %d\n",
				bos[i]->size - mode_cmd->offsets[i], size);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण

		fb->obj[i]    = bos[i];
		plane->dma_addr  = 0;
	पूर्ण

	drm_helper_mode_fill_fb_काष्ठा(dev, fb, mode_cmd);

	ret = drm_framebuffer_init(dev, fb, &omap_framebuffer_funcs);
	अगर (ret) अणु
		dev_err(dev->dev, "framebuffer init failed: %d\n", ret);
		जाओ fail;
	पूर्ण

	DBG("create: FB ID: %d (%p)", fb->base.id, fb);

	वापस fb;

fail:
	kमुक्त(omap_fb);

	वापस ERR_PTR(ret);
पूर्ण
