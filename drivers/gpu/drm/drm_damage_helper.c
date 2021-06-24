<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright (c) 2018 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 * Deepak Rawat <drawat@vmware.com>
 * Rob Clark <robdclark@gmail.com>
 *
 **************************************************************************/

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_device.h>

/**
 * DOC: overview
 *
 * FB_DAMAGE_CLIPS is an optional plane property which provides a means to
 * specअगरy a list of damage rectangles on a plane in framebuffer coordinates of
 * the framebuffer attached to the plane. In current context damage is the area
 * of plane framebuffer that has changed since last plane update (also called
 * page-flip), irrespective of whether currently attached framebuffer is same as
 * framebuffer attached during last plane update or not.
 *
 * FB_DAMAGE_CLIPS is a hपूर्णांक to kernel which could be helpful क्रम some drivers
 * to optimize पूर्णांकernally especially क्रम भव devices where each framebuffer
 * change needs to be transmitted over network, usb, etc.
 *
 * Since FB_DAMAGE_CLIPS is a hपूर्णांक so it is an optional property. User-space can
 * ignore damage clips property and in that हाल driver will करो a full plane
 * update. In हाल damage clips are provided then it is guaranteed that the area
 * inside damage clips will be updated to plane. For efficiency driver can करो
 * full update or can update more than specअगरied in damage clips. Since driver
 * is मुक्त to पढ़ो more, user-space must always render the entire visible
 * framebuffer. Otherwise there can be corruptions. Also, अगर a user-space
 * provides damage clips which करोesn't encompass the actual damage to
 * framebuffer (since last plane update) can result in incorrect rendering.
 *
 * FB_DAMAGE_CLIPS is a blob property with the layout of blob data is simply an
 * array of &drm_mode_rect. Unlike plane &drm_plane_state.src coordinates,
 * damage clips are not in 16.16 fixed poपूर्णांक. Similar to plane src in
 * framebuffer, damage clips cannot be negative. In damage clip, x1/y1 are
 * inclusive and x2/y2 are exclusive. While kernel करोes not error क्रम overlapped
 * damage clips, it is strongly discouraged.
 *
 * Drivers that are पूर्णांकerested in damage पूर्णांकerface क्रम plane should enable
 * FB_DAMAGE_CLIPS property by calling drm_plane_enable_fb_damage_clips().
 * Drivers implementing damage can use drm_atomic_helper_damage_iter_init() and
 * drm_atomic_helper_damage_iter_next() helper iterator function to get damage
 * rectangles clipped to &drm_plane_state.src.
 */

अटल व्योम convert_clip_rect_to_rect(स्थिर काष्ठा drm_clip_rect *src,
				      काष्ठा drm_mode_rect *dest,
				      uपूर्णांक32_t num_clips, uपूर्णांक32_t src_inc)
अणु
	जबतक (num_clips > 0) अणु
		dest->x1 = src->x1;
		dest->y1 = src->y1;
		dest->x2 = src->x2;
		dest->y2 = src->y2;
		src += src_inc;
		dest++;
		num_clips--;
	पूर्ण
पूर्ण

/**
 * drm_plane_enable_fb_damage_clips - Enables plane fb damage clips property.
 * @plane: Plane on which to enable damage clips property.
 *
 * This function lets driver to enable the damage clips property on a plane.
 */
व्योम drm_plane_enable_fb_damage_clips(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा drm_mode_config *config = &dev->mode_config;

	drm_object_attach_property(&plane->base, config->prop_fb_damage_clips,
				   0);
पूर्ण
EXPORT_SYMBOL(drm_plane_enable_fb_damage_clips);

/**
 * drm_atomic_helper_check_plane_damage - Verअगरy plane damage on atomic_check.
 * @state: The driver state object.
 * @plane_state: Plane state क्रम which to verअगरy damage.
 *
 * This helper function makes sure that damage from plane state is discarded
 * क्रम full modeset. If there are more reasons a driver would want to करो a full
 * plane update rather than processing inभागidual damage regions, then those
 * हालs should be taken care of here.
 *
 * Note that &drm_plane_state.fb_damage_clips == शून्य in plane state means that
 * full plane update should happen. It also ensure helper iterator will वापस
 * &drm_plane_state.src as damage.
 */
व्योम drm_atomic_helper_check_plane_damage(काष्ठा drm_atomic_state *state,
					  काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_crtc_state *crtc_state;

	अगर (plane_state->crtc) अणु
		crtc_state = drm_atomic_get_new_crtc_state(state,
							   plane_state->crtc);

		अगर (WARN_ON(!crtc_state))
			वापस;

		अगर (drm_atomic_crtc_needs_modeset(crtc_state)) अणु
			drm_property_blob_put(plane_state->fb_damage_clips);
			plane_state->fb_damage_clips = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_check_plane_damage);

/**
 * drm_atomic_helper_dirtyfb - Helper क्रम dirtyfb.
 * @fb: DRM framebuffer.
 * @file_priv: Drm file क्रम the ioctl call.
 * @flags: Dirty fb annotate flags.
 * @color: Color क्रम annotate fill.
 * @clips: Dirty region.
 * @num_clips: Count of clip in clips.
 *
 * A helper to implement &drm_framebuffer_funcs.dirty using damage पूर्णांकerface
 * during plane update. If num_clips is 0 then this helper will करो a full plane
 * update. This is the same behaviour expected by सूचीTFB IOCTL.
 *
 * Note that this helper is blocking implementation. This is what current
 * drivers and userspace expect in their सूचीTYFB IOCTL implementation, as a way
 * to rate-limit userspace and make sure its rendering करोesn't get ahead of
 * uploading new data too much.
 *
 * Return: Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक drm_atomic_helper_dirtyfb(काष्ठा drm_framebuffer *fb,
			      काष्ठा drm_file *file_priv, अचिन्हित पूर्णांक flags,
			      अचिन्हित पूर्णांक color, काष्ठा drm_clip_rect *clips,
			      अचिन्हित पूर्णांक num_clips)
अणु
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_property_blob *damage = शून्य;
	काष्ठा drm_mode_rect *rects = शून्य;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_plane *plane;
	पूर्णांक ret = 0;

	/*
	 * When called from ioctl, we are पूर्णांकerruptable, but not when called
	 * पूर्णांकernally (ie. defio worker)
	 */
	drm_modeset_acquire_init(&ctx,
		file_priv ? DRM_MODESET_ACQUIRE_INTERRUPTIBLE : 0);

	state = drm_atomic_state_alloc(fb->dev);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ out_drop_locks;
	पूर्ण
	state->acquire_ctx = &ctx;

	अगर (clips) अणु
		uपूर्णांक32_t inc = 1;

		अगर (flags & DRM_MODE_FB_सूचीTY_ANNOTATE_COPY) अणु
			inc = 2;
			num_clips /= 2;
		पूर्ण

		rects = kसुस्मृति(num_clips, माप(*rects), GFP_KERNEL);
		अगर (!rects) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		convert_clip_rect_to_rect(clips, rects, num_clips, inc);
		damage = drm_property_create_blob(fb->dev,
						  num_clips * माप(*rects),
						  rects);
		अगर (IS_ERR(damage)) अणु
			ret = PTR_ERR(damage);
			damage = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण

retry:
	drm_क्रम_each_plane(plane, fb->dev) अणु
		काष्ठा drm_plane_state *plane_state;

		ret = drm_modeset_lock(&plane->mutex, state->acquire_ctx);
		अगर (ret)
			जाओ out;

		अगर (plane->state->fb != fb) अणु
			drm_modeset_unlock(&plane->mutex);
			जारी;
		पूर्ण

		plane_state = drm_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state)) अणु
			ret = PTR_ERR(plane_state);
			जाओ out;
		पूर्ण

		drm_property_replace_blob(&plane_state->fb_damage_clips,
					  damage);
	पूर्ण

	ret = drm_atomic_commit(state);

out:
	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		ret = drm_modeset_backoff(&ctx);
		अगर (!ret)
			जाओ retry;
	पूर्ण

	drm_property_blob_put(damage);
	kमुक्त(rects);
	drm_atomic_state_put(state);

out_drop_locks:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;

पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_dirtyfb);

/**
 * drm_atomic_helper_damage_iter_init - Initialize the damage iterator.
 * @iter: The iterator to initialize.
 * @old_state: Old plane state क्रम validation.
 * @state: Plane state from which to iterate the damage clips.
 *
 * Initialize an iterator, which clips plane damage
 * &drm_plane_state.fb_damage_clips to plane &drm_plane_state.src. This iterator
 * वापसs full plane src in हाल damage is not present because either
 * user-space didn't sent or driver discarded it (it want to करो full plane
 * update). Currently this iterator वापसs full plane src in हाल plane src
 * changed but that can be changed in future to वापस damage.
 *
 * For the हाल when plane is not visible or plane update should not happen the
 * first call to iter_next will वापस false. Note that this helper use clipped
 * &drm_plane_state.src, so driver calling this helper should have called
 * drm_atomic_helper_check_plane_state() earlier.
 */
व्योम
drm_atomic_helper_damage_iter_init(काष्ठा drm_atomic_helper_damage_iter *iter,
				   स्थिर काष्ठा drm_plane_state *old_state,
				   स्थिर काष्ठा drm_plane_state *state)
अणु
	स_रखो(iter, 0, माप(*iter));

	अगर (!state || !state->crtc || !state->fb || !state->visible)
		वापस;

	iter->clips = drm_helper_get_plane_damage_clips(state);
	iter->num_clips = drm_plane_get_damage_clips_count(state);

	/* Round करोwn क्रम x1/y1 and round up क्रम x2/y2 to catch all pixels */
	iter->plane_src.x1 = state->src.x1 >> 16;
	iter->plane_src.y1 = state->src.y1 >> 16;
	iter->plane_src.x2 = (state->src.x2 >> 16) + !!(state->src.x2 & 0xFFFF);
	iter->plane_src.y2 = (state->src.y2 >> 16) + !!(state->src.y2 & 0xFFFF);

	अगर (!iter->clips || !drm_rect_equals(&state->src, &old_state->src)) अणु
		iter->clips = शून्य;
		iter->num_clips = 0;
		iter->full_update = true;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_damage_iter_init);

/**
 * drm_atomic_helper_damage_iter_next - Advance the damage iterator.
 * @iter: The iterator to advance.
 * @rect: Return a rectangle in fb coordinate clipped to plane src.
 *
 * Since plane src is in 16.16 fixed poपूर्णांक and damage clips are whole number,
 * this iterator round off clips that पूर्णांकersect with plane src. Round करोwn क्रम
 * x1/y1 and round up क्रम x2/y2 क्रम the पूर्णांकersected coordinate. Similar rounding
 * off क्रम full plane src, in हाल it's वापसed as damage. This iterator will
 * skip damage clips outside of plane src.
 *
 * Return: True अगर the output is valid, false अगर reached the end.
 *
 * If the first call to iterator next वापसs false then it means no need to
 * update the plane.
 */
bool
drm_atomic_helper_damage_iter_next(काष्ठा drm_atomic_helper_damage_iter *iter,
				   काष्ठा drm_rect *rect)
अणु
	bool ret = false;

	अगर (iter->full_update) अणु
		*rect = iter->plane_src;
		iter->full_update = false;
		वापस true;
	पूर्ण

	जबतक (iter->curr_clip < iter->num_clips) अणु
		*rect = iter->clips[iter->curr_clip];
		iter->curr_clip++;

		अगर (drm_rect_पूर्णांकersect(rect, &iter->plane_src)) अणु
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_damage_iter_next);

/**
 * drm_atomic_helper_damage_merged - Merged plane damage
 * @old_state: Old plane state क्रम validation.
 * @state: Plane state from which to iterate the damage clips.
 * @rect: Returns the merged damage rectangle
 *
 * This function merges any valid plane damage clips पूर्णांकo one rectangle and
 * वापसs it in @rect.
 *
 * For details see: drm_atomic_helper_damage_iter_init() and
 * drm_atomic_helper_damage_iter_next().
 *
 * Returns:
 * True अगर there is valid plane damage otherwise false.
 */
bool drm_atomic_helper_damage_merged(स्थिर काष्ठा drm_plane_state *old_state,
				     काष्ठा drm_plane_state *state,
				     काष्ठा drm_rect *rect)
अणु
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_rect clip;
	bool valid = false;

	rect->x1 = पूर्णांक_उच्च;
	rect->y1 = पूर्णांक_उच्च;
	rect->x2 = 0;
	rect->y2 = 0;

	drm_atomic_helper_damage_iter_init(&iter, old_state, state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip) अणु
		rect->x1 = min(rect->x1, clip.x1);
		rect->y1 = min(rect->y1, clip.y1);
		rect->x2 = max(rect->x2, clip.x2);
		rect->y2 = max(rect->y2, clip.y2);
		valid = true;
	पूर्ण

	वापस valid;
पूर्ण
EXPORT_SYMBOL(drm_atomic_helper_damage_merged);
