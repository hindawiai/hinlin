<शैली गुरु>
/*
 * Copyright 2011 Red Hat, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modअगरy, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/dma-buf-map.h>

#समावेश <drm/drm_fourcc.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

अटल पूर्णांक alloc_clips(काष्ठा qxl_device *qdev,
		       काष्ठा qxl_release *release,
		       अचिन्हित पूर्णांक num_clips,
		       काष्ठा qxl_bo **clips_bo)
अणु
	पूर्णांक size = माप(काष्ठा qxl_clip_rects) + माप(काष्ठा qxl_rect) * num_clips;

	वापस qxl_alloc_bo_reserved(qdev, release, size, clips_bo);
पूर्ण

/* वापसs a poपूर्णांकer to the alपढ़ोy allocated qxl_rect array inside
 * the qxl_clip_rects. This is *not* the same as the memory allocated
 * on the device, it is offset to qxl_clip_rects.chunk.data */
अटल काष्ठा qxl_rect *drawable_set_clipping(काष्ठा qxl_device *qdev,
					      अचिन्हित पूर्णांक num_clips,
					      काष्ठा qxl_bo *clips_bo)
अणु
	काष्ठा dma_buf_map map;
	काष्ठा qxl_clip_rects *dev_clips;
	पूर्णांक ret;

	ret = qxl_bo_vmap_locked(clips_bo, &map);
	अगर (ret)
		वापस शून्य;
	dev_clips = map.vaddr; /* TODO: Use mapping असलtraction properly */

	dev_clips->num_rects = num_clips;
	dev_clips->chunk.next_chunk = 0;
	dev_clips->chunk.prev_chunk = 0;
	dev_clips->chunk.data_size = माप(काष्ठा qxl_rect) * num_clips;
	वापस (काष्ठा qxl_rect *)dev_clips->chunk.data;
पूर्ण

अटल पूर्णांक
alloc_drawable(काष्ठा qxl_device *qdev, काष्ठा qxl_release **release)
अणु
	वापस qxl_alloc_release_reserved(qdev, माप(काष्ठा qxl_drawable),
					  QXL_RELEASE_DRAWABLE, release, शून्य);
पूर्ण

अटल व्योम
मुक्त_drawable(काष्ठा qxl_device *qdev, काष्ठा qxl_release *release)
अणु
	qxl_release_मुक्त(qdev, release);
पूर्ण

/* release needs to be reserved at this poपूर्णांक */
अटल पूर्णांक
make_drawable(काष्ठा qxl_device *qdev, पूर्णांक surface, uपूर्णांक8_t type,
	      स्थिर काष्ठा qxl_rect *rect,
	      काष्ठा qxl_release *release)
अणु
	काष्ठा qxl_drawable *drawable;
	पूर्णांक i;

	drawable = (काष्ठा qxl_drawable *)qxl_release_map(qdev, release);
	अगर (!drawable)
		वापस -ENOMEM;

	drawable->type = type;

	drawable->surface_id = surface;		/* Only primary क्रम now */
	drawable->effect = QXL_EFFECT_OPAQUE;
	drawable->self_biपंचांगap = 0;
	drawable->self_biपंचांगap_area.top = 0;
	drawable->self_biपंचांगap_area.left = 0;
	drawable->self_biपंचांगap_area.bottom = 0;
	drawable->self_biपंचांगap_area.right = 0;
	/* FIXME: add clipping */
	drawable->clip.type = SPICE_CLIP_TYPE_NONE;

	/*
	 * surfaces_dest[i] should apparently be filled out with the
	 * surfaces that we depend on, and surface_rects should be
	 * filled with the rectangles of those surfaces that we
	 * are going to use.
	 */
	क्रम (i = 0; i < 3; ++i)
		drawable->surfaces_dest[i] = -1;

	अगर (rect)
		drawable->bbox = *rect;

	drawable->mm_समय = qdev->rom->mm_घड़ी;
	qxl_release_unmap(qdev, release, &drawable->release_info);
	वापस 0;
पूर्ण

/* push a draw command using the given clipping rectangles as
 * the sources from the shaकरोw framebuffer.
 *
 * Right now implementing with a single draw and a clip list. Clip
 * lists are known to be a problem perक्रमmance wise, this can be solved
 * by treating them dअगरferently in the server.
 */
व्योम qxl_draw_dirty_fb(काष्ठा qxl_device *qdev,
		       काष्ठा drm_framebuffer *fb,
		       काष्ठा qxl_bo *bo,
		       अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक color,
		       काष्ठा drm_clip_rect *clips,
		       अचिन्हित पूर्णांक num_clips, पूर्णांक inc,
		       uपूर्णांक32_t dumb_shaकरोw_offset)
अणु
	/*
	 * TODO: अगर flags & DRM_MODE_FB_सूचीTY_ANNOTATE_FILL then we should
	 * send a fill command instead, much cheaper.
	 *
	 * See include/drm/drm_mode.h
	 */
	काष्ठा drm_clip_rect *clips_ptr;
	पूर्णांक i;
	पूर्णांक left, right, top, bottom;
	पूर्णांक width, height;
	काष्ठा qxl_drawable *drawable;
	काष्ठा qxl_rect drawable_rect;
	काष्ठा qxl_rect *rects;
	पूर्णांक stride = fb->pitches[0];
	/* depth is not actually पूर्णांकeresting, we करोn't mask with it */
	पूर्णांक depth = fb->क्रमmat->cpp[0] * 8;
	काष्ठा dma_buf_map surface_map;
	uपूर्णांक8_t *surface_base;
	काष्ठा qxl_release *release;
	काष्ठा qxl_bo *clips_bo;
	काष्ठा qxl_drm_image *dimage;
	पूर्णांक ret;

	ret = alloc_drawable(qdev, &release);
	अगर (ret)
		वापस;

	clips->x1 += dumb_shaकरोw_offset;
	clips->x2 += dumb_shaकरोw_offset;

	left = clips->x1;
	right = clips->x2;
	top = clips->y1;
	bottom = clips->y2;

	/* skip the first clip rect */
	क्रम (i = 1, clips_ptr = clips + inc;
	     i < num_clips; i++, clips_ptr += inc) अणु
		left = min_t(पूर्णांक, left, (पूर्णांक)clips_ptr->x1);
		right = max_t(पूर्णांक, right, (पूर्णांक)clips_ptr->x2);
		top = min_t(पूर्णांक, top, (पूर्णांक)clips_ptr->y1);
		bottom = max_t(पूर्णांक, bottom, (पूर्णांक)clips_ptr->y2);
	पूर्ण

	width = right - left;
	height = bottom - top;

	ret = alloc_clips(qdev, release, num_clips, &clips_bo);
	अगर (ret)
		जाओ out_मुक्त_drawable;

	ret = qxl_image_alloc_objects(qdev, release,
				      &dimage,
				      height, stride);
	अगर (ret)
		जाओ out_मुक्त_clips;

	/* करो a reservation run over all the objects we just allocated */
	ret = qxl_release_reserve_list(release, true);
	अगर (ret)
		जाओ out_मुक्त_image;

	drawable_rect.left = left;
	drawable_rect.right = right;
	drawable_rect.top = top;
	drawable_rect.bottom = bottom;

	ret = make_drawable(qdev, 0, QXL_DRAW_COPY, &drawable_rect,
			    release);
	अगर (ret)
		जाओ out_release_backoff;

	ret = qxl_bo_vmap_locked(bo, &surface_map);
	अगर (ret)
		जाओ out_release_backoff;
	surface_base = surface_map.vaddr; /* TODO: Use mapping असलtraction properly */

	ret = qxl_image_init(qdev, release, dimage, surface_base,
			     left - dumb_shaकरोw_offset,
			     top, width, height, depth, stride);
	qxl_bo_vunmap_locked(bo);
	अगर (ret)
		जाओ out_release_backoff;

	rects = drawable_set_clipping(qdev, num_clips, clips_bo);
	अगर (!rects) अणु
		ret = -EINVAL;
		जाओ out_release_backoff;
	पूर्ण
	drawable = (काष्ठा qxl_drawable *)qxl_release_map(qdev, release);

	drawable->clip.type = SPICE_CLIP_TYPE_RECTS;
	drawable->clip.data = qxl_bo_physical_address(qdev,
						      clips_bo, 0);

	drawable->u.copy.src_area.top = 0;
	drawable->u.copy.src_area.bottom = height;
	drawable->u.copy.src_area.left = 0;
	drawable->u.copy.src_area.right = width;

	drawable->u.copy.rop_descriptor = SPICE_ROPD_OP_PUT;
	drawable->u.copy.scale_mode = 0;
	drawable->u.copy.mask.flags = 0;
	drawable->u.copy.mask.pos.x = 0;
	drawable->u.copy.mask.pos.y = 0;
	drawable->u.copy.mask.biपंचांगap = 0;

	drawable->u.copy.src_biपंचांगap = qxl_bo_physical_address(qdev, dimage->bo, 0);
	qxl_release_unmap(qdev, release, &drawable->release_info);

	clips_ptr = clips;
	क्रम (i = 0; i < num_clips; i++, clips_ptr += inc) अणु
		rects[i].left   = clips_ptr->x1;
		rects[i].right  = clips_ptr->x2;
		rects[i].top    = clips_ptr->y1;
		rects[i].bottom = clips_ptr->y2;
	पूर्ण
	qxl_bo_vunmap_locked(clips_bo);

	qxl_release_fence_buffer_objects(release);
	qxl_push_command_ring_release(qdev, release, QXL_CMD_DRAW, false);

out_release_backoff:
	अगर (ret)
		qxl_release_backoff_reserve_list(release);
out_मुक्त_image:
	qxl_image_मुक्त_objects(qdev, dimage);
out_मुक्त_clips:
	qxl_bo_unref(&clips_bo);
out_मुक्त_drawable:
	/* only मुक्त drawable on error */
	अगर (ret)
		मुक्त_drawable(qdev, release);

पूर्ण
