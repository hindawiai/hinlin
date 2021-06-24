<शैली गुरु>
/*
 * Copyright (C) 2014 Red Hat
 * Copyright (C) 2014 Intel Corp.
 * Copyright (C) 2018 Intel Corp.
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
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 * Daniel Vetter <daniel.vetter@ffwll.ch>
 */

#अगर_अघोषित DRM_ATOMIC_UAPI_H_
#घोषणा DRM_ATOMIC_UAPI_H_

काष्ठा drm_crtc_state;
काष्ठा drm_display_mode;
काष्ठा drm_property_blob;
काष्ठा drm_plane_state;
काष्ठा drm_crtc;
काष्ठा drm_connector_state;
काष्ठा dma_fence;
काष्ठा drm_framebuffer;

पूर्णांक __must_check
drm_atomic_set_mode_क्रम_crtc(काष्ठा drm_crtc_state *state,
			     स्थिर काष्ठा drm_display_mode *mode);
पूर्णांक __must_check
drm_atomic_set_mode_prop_क्रम_crtc(काष्ठा drm_crtc_state *state,
				  काष्ठा drm_property_blob *blob);
पूर्णांक __must_check
drm_atomic_set_crtc_क्रम_plane(काष्ठा drm_plane_state *plane_state,
			      काष्ठा drm_crtc *crtc);
व्योम drm_atomic_set_fb_क्रम_plane(काष्ठा drm_plane_state *plane_state,
				 काष्ठा drm_framebuffer *fb);
व्योम drm_atomic_set_fence_क्रम_plane(काष्ठा drm_plane_state *plane_state,
				    काष्ठा dma_fence *fence);
पूर्णांक __must_check
drm_atomic_set_crtc_क्रम_connector(काष्ठा drm_connector_state *conn_state,
				  काष्ठा drm_crtc *crtc);

#पूर्ण_अगर
