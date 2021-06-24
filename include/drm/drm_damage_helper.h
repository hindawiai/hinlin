<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
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
 *
 **************************************************************************/

#अगर_अघोषित DRM_DAMAGE_HELPER_H_
#घोषणा DRM_DAMAGE_HELPER_H_

#समावेश <drm/drm_atomic_helper.h>

/**
 * drm_atomic_क्रम_each_plane_damage - Iterator macro क्रम plane damage.
 * @iter: The iterator to advance.
 * @rect: Return a rectangle in fb coordinate clipped to plane src.
 *
 * Note that अगर the first call to iterator macro वापस false then no need to करो
 * plane update. Iterator will वापस full plane src when damage is not passed
 * by user-space.
 */
#घोषणा drm_atomic_क्रम_each_plane_damage(iter, rect) \
	जबतक (drm_atomic_helper_damage_iter_next(iter, rect))

/**
 * काष्ठा drm_atomic_helper_damage_iter - Closure काष्ठाure क्रम damage iterator.
 *
 * This काष्ठाure tracks state needed to walk the list of plane damage clips.
 */
काष्ठा drm_atomic_helper_damage_iter अणु
	/* निजी: Plane src in whole number. */
	काष्ठा drm_rect plane_src;
	/* निजी: Rectangles in plane damage blob. */
	स्थिर काष्ठा drm_rect *clips;
	/* निजी: Number of rectangles in plane damage blob. */
	uपूर्णांक32_t num_clips;
	/* निजी: Current clip iterator is advancing on. */
	uपूर्णांक32_t curr_clip;
	/* निजी: Whether need full plane update. */
	bool full_update;
पूर्ण;

व्योम drm_plane_enable_fb_damage_clips(काष्ठा drm_plane *plane);
व्योम drm_atomic_helper_check_plane_damage(काष्ठा drm_atomic_state *state,
					  काष्ठा drm_plane_state *plane_state);
पूर्णांक drm_atomic_helper_dirtyfb(काष्ठा drm_framebuffer *fb,
			      काष्ठा drm_file *file_priv, अचिन्हित पूर्णांक flags,
			      अचिन्हित पूर्णांक color, काष्ठा drm_clip_rect *clips,
			      अचिन्हित पूर्णांक num_clips);
व्योम
drm_atomic_helper_damage_iter_init(काष्ठा drm_atomic_helper_damage_iter *iter,
				   स्थिर काष्ठा drm_plane_state *old_state,
				   स्थिर काष्ठा drm_plane_state *new_state);
bool
drm_atomic_helper_damage_iter_next(काष्ठा drm_atomic_helper_damage_iter *iter,
				   काष्ठा drm_rect *rect);
bool drm_atomic_helper_damage_merged(स्थिर काष्ठा drm_plane_state *old_state,
				     काष्ठा drm_plane_state *state,
				     काष्ठा drm_rect *rect);

/**
 * drm_helper_get_plane_damage_clips - Returns damage clips in &drm_rect.
 * @state: Plane state.
 *
 * Returns plane damage rectangles in पूर्णांकernal &drm_rect. Currently &drm_rect
 * can be obtained by simply typecasting &drm_mode_rect. This is because both
 * are चिन्हित 32 and during drm_atomic_check_only() it is verअगरied that damage
 * clips are inside fb.
 *
 * Return: Clips in plane fb_damage_clips blob property.
 */
अटल अंतरभूत काष्ठा drm_rect *
drm_helper_get_plane_damage_clips(स्थिर काष्ठा drm_plane_state *state)
अणु
	वापस (काष्ठा drm_rect *)drm_plane_get_damage_clips(state);
पूर्ण

#पूर्ण_अगर
