<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
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
 *          Alex Deucher
 */

#समावेश <drm/drm_device.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"

अटल व्योम radeon_lock_cursor(काष्ठा drm_crtc *crtc, bool lock)
अणु
	काष्ठा radeon_device *rdev = crtc->dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	uपूर्णांक32_t cur_lock;

	अगर (ASIC_IS_DCE4(rdev)) अणु
		cur_lock = RREG32(EVERGREEN_CUR_UPDATE + radeon_crtc->crtc_offset);
		अगर (lock)
			cur_lock |= EVERGREEN_CURSOR_UPDATE_LOCK;
		अन्यथा
			cur_lock &= ~EVERGREEN_CURSOR_UPDATE_LOCK;
		WREG32(EVERGREEN_CUR_UPDATE + radeon_crtc->crtc_offset, cur_lock);
	पूर्ण अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		cur_lock = RREG32(AVIVO_D1CUR_UPDATE + radeon_crtc->crtc_offset);
		अगर (lock)
			cur_lock |= AVIVO_D1CURSOR_UPDATE_LOCK;
		अन्यथा
			cur_lock &= ~AVIVO_D1CURSOR_UPDATE_LOCK;
		WREG32(AVIVO_D1CUR_UPDATE + radeon_crtc->crtc_offset, cur_lock);
	पूर्ण अन्यथा अणु
		cur_lock = RREG32(RADEON_CUR_OFFSET + radeon_crtc->crtc_offset);
		अगर (lock)
			cur_lock |= RADEON_CUR_LOCK;
		अन्यथा
			cur_lock &= ~RADEON_CUR_LOCK;
		WREG32(RADEON_CUR_OFFSET + radeon_crtc->crtc_offset, cur_lock);
	पूर्ण
पूर्ण

अटल व्योम radeon_hide_cursor(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा radeon_device *rdev = crtc->dev->dev_निजी;

	अगर (ASIC_IS_DCE4(rdev)) अणु
		WREG32_IDX(EVERGREEN_CUR_CONTROL + radeon_crtc->crtc_offset,
			   EVERGREEN_CURSOR_MODE(EVERGREEN_CURSOR_24_8_PRE_MULT) |
			   EVERGREEN_CURSOR_URGENT_CONTROL(EVERGREEN_CURSOR_URGENT_1_2));
	पूर्ण अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		WREG32_IDX(AVIVO_D1CUR_CONTROL + radeon_crtc->crtc_offset,
			   (AVIVO_D1CURSOR_MODE_24BPP << AVIVO_D1CURSOR_MODE_SHIFT));
	पूर्ण अन्यथा अणु
		u32 reg;
		चयन (radeon_crtc->crtc_id) अणु
		हाल 0:
			reg = RADEON_CRTC_GEN_CNTL;
			अवरोध;
		हाल 1:
			reg = RADEON_CRTC2_GEN_CNTL;
			अवरोध;
		शेष:
			वापस;
		पूर्ण
		WREG32_IDX(reg, RREG32_IDX(reg) & ~RADEON_CRTC_CUR_EN);
	पूर्ण
पूर्ण

अटल व्योम radeon_show_cursor(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा radeon_device *rdev = crtc->dev->dev_निजी;

	अगर (radeon_crtc->cursor_out_of_bounds)
		वापस;

	अगर (ASIC_IS_DCE4(rdev)) अणु
		WREG32(EVERGREEN_CUR_SURFACE_ADDRESS_HIGH + radeon_crtc->crtc_offset,
		       upper_32_bits(radeon_crtc->cursor_addr));
		WREG32(EVERGREEN_CUR_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
		       lower_32_bits(radeon_crtc->cursor_addr));
		WREG32(RADEON_MM_INDEX, EVERGREEN_CUR_CONTROL + radeon_crtc->crtc_offset);
		WREG32(RADEON_MM_DATA, EVERGREEN_CURSOR_EN |
		       EVERGREEN_CURSOR_MODE(EVERGREEN_CURSOR_24_8_PRE_MULT) |
		       EVERGREEN_CURSOR_URGENT_CONTROL(EVERGREEN_CURSOR_URGENT_1_2));
	पूर्ण अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		अगर (rdev->family >= CHIP_RV770) अणु
			अगर (radeon_crtc->crtc_id)
				WREG32(R700_D2CUR_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(radeon_crtc->cursor_addr));
			अन्यथा
				WREG32(R700_D1CUR_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(radeon_crtc->cursor_addr));
		पूर्ण

		WREG32(AVIVO_D1CUR_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
		       lower_32_bits(radeon_crtc->cursor_addr));
		WREG32(RADEON_MM_INDEX, AVIVO_D1CUR_CONTROL + radeon_crtc->crtc_offset);
		WREG32(RADEON_MM_DATA, AVIVO_D1CURSOR_EN |
		       (AVIVO_D1CURSOR_MODE_24BPP << AVIVO_D1CURSOR_MODE_SHIFT));
	पूर्ण अन्यथा अणु
		/* offset is from DISP(2)_BASE_ADDRESS */
		WREG32(RADEON_CUR_OFFSET + radeon_crtc->crtc_offset,
		       radeon_crtc->cursor_addr - radeon_crtc->legacy_display_base_addr);

		चयन (radeon_crtc->crtc_id) अणु
		हाल 0:
			WREG32(RADEON_MM_INDEX, RADEON_CRTC_GEN_CNTL);
			अवरोध;
		हाल 1:
			WREG32(RADEON_MM_INDEX, RADEON_CRTC2_GEN_CNTL);
			अवरोध;
		शेष:
			वापस;
		पूर्ण

		WREG32_P(RADEON_MM_DATA, (RADEON_CRTC_CUR_EN |
					  (RADEON_CRTC_CUR_MODE_24BPP << RADEON_CRTC_CUR_MODE_SHIFT)),
			 ~(RADEON_CRTC_CUR_EN | RADEON_CRTC_CUR_MODE_MASK));
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_cursor_move_locked(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा radeon_device *rdev = crtc->dev->dev_निजी;
	पूर्णांक xorigin = 0, yorigin = 0;
	पूर्णांक w = radeon_crtc->cursor_width;

	radeon_crtc->cursor_x = x;
	radeon_crtc->cursor_y = y;

	अगर (ASIC_IS_AVIVO(rdev)) अणु
		/* avivo cursor are offset पूर्णांकo the total surface */
		x += crtc->x;
		y += crtc->y;
	पूर्ण

	अगर (x < 0)
		xorigin = min(-x, radeon_crtc->max_cursor_width - 1);
	अगर (y < 0)
		yorigin = min(-y, radeon_crtc->max_cursor_height - 1);

	अगर (!ASIC_IS_AVIVO(rdev)) अणु
		x += crtc->x;
		y += crtc->y;
	पूर्ण
	DRM_DEBUG("x %d y %d c->x %d c->y %d\n", x, y, crtc->x, crtc->y);

	/* fixed on DCE6 and newer */
	अगर (ASIC_IS_AVIVO(rdev) && !ASIC_IS_DCE6(rdev)) अणु
		पूर्णांक i = 0;
		काष्ठा drm_crtc *crtc_p;

		/*
		 * avivo cursor image can't end on 128 pixel boundary or
		 * go past the end of the frame अगर both crtcs are enabled
		 *
		 * NOTE: It is safe to access crtc->enabled of other crtcs
		 * without holding either the mode_config lock or the other
		 * crtc's lock as दीर्घ as ग_लिखो access to this flag _always_
		 * grअसल all locks.
		 */
		list_क्रम_each_entry(crtc_p, &crtc->dev->mode_config.crtc_list, head) अणु
			अगर (crtc_p->enabled)
				i++;
		पूर्ण
		अगर (i > 1) अणु
			पूर्णांक cursor_end, frame_end;

			cursor_end = x + w;
			frame_end = crtc->x + crtc->mode.crtc_hdisplay;
			अगर (cursor_end >= frame_end) अणु
				w = w - (cursor_end - frame_end);
				अगर (!(frame_end & 0x7f))
					w--;
			पूर्ण अन्यथा अगर (cursor_end <= 0) अणु
				जाओ out_of_bounds;
			पूर्ण अन्यथा अगर (!(cursor_end & 0x7f)) अणु
				w--;
			पूर्ण
			अगर (w <= 0) अणु
				जाओ out_of_bounds;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (x <= (crtc->x - w) || y <= (crtc->y - radeon_crtc->cursor_height) ||
	    x >= (crtc->x + crtc->mode.hdisplay) ||
	    y >= (crtc->y + crtc->mode.vdisplay))
		जाओ out_of_bounds;

	x += xorigin;
	y += yorigin;

	अगर (ASIC_IS_DCE4(rdev)) अणु
		WREG32(EVERGREEN_CUR_POSITION + radeon_crtc->crtc_offset, (x << 16) | y);
		WREG32(EVERGREEN_CUR_HOT_SPOT + radeon_crtc->crtc_offset, (xorigin << 16) | yorigin);
		WREG32(EVERGREEN_CUR_SIZE + radeon_crtc->crtc_offset,
		       ((w - 1) << 16) | (radeon_crtc->cursor_height - 1));
	पूर्ण अन्यथा अगर (ASIC_IS_AVIVO(rdev)) अणु
		WREG32(AVIVO_D1CUR_POSITION + radeon_crtc->crtc_offset, (x << 16) | y);
		WREG32(AVIVO_D1CUR_HOT_SPOT + radeon_crtc->crtc_offset, (xorigin << 16) | yorigin);
		WREG32(AVIVO_D1CUR_SIZE + radeon_crtc->crtc_offset,
		       ((w - 1) << 16) | (radeon_crtc->cursor_height - 1));
	पूर्ण अन्यथा अणु
		x -= crtc->x;
		y -= crtc->y;

		अगर (crtc->mode.flags & DRM_MODE_FLAG_DBLSCAN)
			y *= 2;

		WREG32(RADEON_CUR_HORZ_VERT_OFF + radeon_crtc->crtc_offset,
		       (RADEON_CUR_LOCK
			| (xorigin << 16)
			| yorigin));
		WREG32(RADEON_CUR_HORZ_VERT_POSN + radeon_crtc->crtc_offset,
		       (RADEON_CUR_LOCK
			| (x << 16)
			| y));
		/* offset is from DISP(2)_BASE_ADDRESS */
		WREG32(RADEON_CUR_OFFSET + radeon_crtc->crtc_offset,
		       radeon_crtc->cursor_addr - radeon_crtc->legacy_display_base_addr +
		       yorigin * 256);
	पूर्ण

	अगर (radeon_crtc->cursor_out_of_bounds) अणु
		radeon_crtc->cursor_out_of_bounds = false;
		अगर (radeon_crtc->cursor_bo)
			radeon_show_cursor(crtc);
	पूर्ण

	वापस 0;

 out_of_bounds:
	अगर (!radeon_crtc->cursor_out_of_bounds) अणु
		radeon_hide_cursor(crtc);
		radeon_crtc->cursor_out_of_bounds = true;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक radeon_crtc_cursor_move(काष्ठा drm_crtc *crtc,
			    पूर्णांक x, पूर्णांक y)
अणु
	पूर्णांक ret;

	radeon_lock_cursor(crtc, true);
	ret = radeon_cursor_move_locked(crtc, x, y);
	radeon_lock_cursor(crtc, false);

	वापस ret;
पूर्ण

पूर्णांक radeon_crtc_cursor_set2(काष्ठा drm_crtc *crtc,
			    काष्ठा drm_file *file_priv,
			    uपूर्णांक32_t handle,
			    uपूर्णांक32_t width,
			    uपूर्णांक32_t height,
			    पूर्णांक32_t hot_x,
			    पूर्णांक32_t hot_y)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा radeon_device *rdev = crtc->dev->dev_निजी;
	काष्ठा drm_gem_object *obj;
	काष्ठा radeon_bo *robj;
	पूर्णांक ret;

	अगर (!handle) अणु
		/* turn off cursor */
		radeon_hide_cursor(crtc);
		obj = शून्य;
		जाओ unpin;
	पूर्ण

	अगर ((width > radeon_crtc->max_cursor_width) ||
	    (height > radeon_crtc->max_cursor_height)) अणु
		DRM_ERROR("bad cursor width or height %d x %d\n", width, height);
		वापस -EINVAL;
	पूर्ण

	obj = drm_gem_object_lookup(file_priv, handle);
	अगर (!obj) अणु
		DRM_ERROR("Cannot find cursor object %x for crtc %d\n", handle, radeon_crtc->crtc_id);
		वापस -ENOENT;
	पूर्ण

	robj = gem_to_radeon_bo(obj);
	ret = radeon_bo_reserve(robj, false);
	अगर (ret != 0) अणु
		drm_gem_object_put(obj);
		वापस ret;
	पूर्ण
	/* Only 27 bit offset क्रम legacy cursor */
	ret = radeon_bo_pin_restricted(robj, RADEON_GEM_DOMAIN_VRAM,
				       ASIC_IS_AVIVO(rdev) ? 0 : 1 << 27,
				       &radeon_crtc->cursor_addr);
	radeon_bo_unreserve(robj);
	अगर (ret) अणु
		DRM_ERROR("Failed to pin new cursor BO (%d)\n", ret);
		drm_gem_object_put(obj);
		वापस ret;
	पूर्ण

	radeon_lock_cursor(crtc, true);

	अगर (width != radeon_crtc->cursor_width ||
	    height != radeon_crtc->cursor_height ||
	    hot_x != radeon_crtc->cursor_hot_x ||
	    hot_y != radeon_crtc->cursor_hot_y) अणु
		पूर्णांक x, y;

		x = radeon_crtc->cursor_x + radeon_crtc->cursor_hot_x - hot_x;
		y = radeon_crtc->cursor_y + radeon_crtc->cursor_hot_y - hot_y;

		radeon_crtc->cursor_width = width;
		radeon_crtc->cursor_height = height;
		radeon_crtc->cursor_hot_x = hot_x;
		radeon_crtc->cursor_hot_y = hot_y;

		radeon_cursor_move_locked(crtc, x, y);
	पूर्ण

	radeon_show_cursor(crtc);

	radeon_lock_cursor(crtc, false);

unpin:
	अगर (radeon_crtc->cursor_bo) अणु
		काष्ठा radeon_bo *robj = gem_to_radeon_bo(radeon_crtc->cursor_bo);
		ret = radeon_bo_reserve(robj, false);
		अगर (likely(ret == 0)) अणु
			radeon_bo_unpin(robj);
			radeon_bo_unreserve(robj);
		पूर्ण
		drm_gem_object_put(radeon_crtc->cursor_bo);
	पूर्ण

	radeon_crtc->cursor_bo = obj;
	वापस 0;
पूर्ण

/**
 * radeon_cursor_reset - Re-set the current cursor, अगर any.
 *
 * @crtc: drm crtc
 *
 * If the CRTC passed in currently has a cursor asचिन्हित, this function
 * makes sure it's visible.
 */
व्योम radeon_cursor_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

	अगर (radeon_crtc->cursor_bo) अणु
		radeon_lock_cursor(crtc, true);

		radeon_cursor_move_locked(crtc, radeon_crtc->cursor_x,
					  radeon_crtc->cursor_y);

		radeon_show_cursor(crtc);

		radeon_lock_cursor(crtc, false);
	पूर्ण
पूर्ण
