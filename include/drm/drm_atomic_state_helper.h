<शैली गुरु>
/*
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

#समावेश <linux/types.h>

काष्ठा drm_bridge;
काष्ठा drm_bridge_state;
काष्ठा drm_crtc;
काष्ठा drm_crtc_state;
काष्ठा drm_plane;
काष्ठा drm_plane_state;
काष्ठा drm_connector;
काष्ठा drm_connector_state;
काष्ठा drm_निजी_obj;
काष्ठा drm_निजी_state;
काष्ठा drm_modeset_acquire_ctx;
काष्ठा drm_device;

व्योम __drm_atomic_helper_crtc_state_reset(काष्ठा drm_crtc_state *state,
					  काष्ठा drm_crtc *crtc);
व्योम __drm_atomic_helper_crtc_reset(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_crtc_state *state);
व्योम drm_atomic_helper_crtc_reset(काष्ठा drm_crtc *crtc);
व्योम __drm_atomic_helper_crtc_duplicate_state(काष्ठा drm_crtc *crtc,
					      काष्ठा drm_crtc_state *state);
काष्ठा drm_crtc_state *
drm_atomic_helper_crtc_duplicate_state(काष्ठा drm_crtc *crtc);
व्योम __drm_atomic_helper_crtc_destroy_state(काष्ठा drm_crtc_state *state);
व्योम drm_atomic_helper_crtc_destroy_state(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_crtc_state *state);

व्योम __drm_atomic_helper_plane_state_reset(काष्ठा drm_plane_state *state,
					   काष्ठा drm_plane *plane);
व्योम __drm_atomic_helper_plane_reset(काष्ठा drm_plane *plane,
				     काष्ठा drm_plane_state *state);
व्योम drm_atomic_helper_plane_reset(काष्ठा drm_plane *plane);
व्योम __drm_atomic_helper_plane_duplicate_state(काष्ठा drm_plane *plane,
					       काष्ठा drm_plane_state *state);
काष्ठा drm_plane_state *
drm_atomic_helper_plane_duplicate_state(काष्ठा drm_plane *plane);
व्योम __drm_atomic_helper_plane_destroy_state(काष्ठा drm_plane_state *state);
व्योम drm_atomic_helper_plane_destroy_state(काष्ठा drm_plane *plane,
					  काष्ठा drm_plane_state *state);

व्योम __drm_atomic_helper_connector_state_reset(काष्ठा drm_connector_state *conn_state,
					       काष्ठा drm_connector *connector);
व्योम __drm_atomic_helper_connector_reset(काष्ठा drm_connector *connector,
					 काष्ठा drm_connector_state *conn_state);
व्योम drm_atomic_helper_connector_reset(काष्ठा drm_connector *connector);
व्योम drm_atomic_helper_connector_tv_reset(काष्ठा drm_connector *connector);
व्योम
__drm_atomic_helper_connector_duplicate_state(काष्ठा drm_connector *connector,
					   काष्ठा drm_connector_state *state);
काष्ठा drm_connector_state *
drm_atomic_helper_connector_duplicate_state(काष्ठा drm_connector *connector);
व्योम
__drm_atomic_helper_connector_destroy_state(काष्ठा drm_connector_state *state);
व्योम drm_atomic_helper_connector_destroy_state(काष्ठा drm_connector *connector,
					  काष्ठा drm_connector_state *state);
व्योम __drm_atomic_helper_निजी_obj_duplicate_state(काष्ठा drm_निजी_obj *obj,
						     काष्ठा drm_निजी_state *state);

व्योम __drm_atomic_helper_bridge_duplicate_state(काष्ठा drm_bridge *bridge,
						काष्ठा drm_bridge_state *state);
काष्ठा drm_bridge_state *
drm_atomic_helper_bridge_duplicate_state(काष्ठा drm_bridge *bridge);
व्योम drm_atomic_helper_bridge_destroy_state(काष्ठा drm_bridge *bridge,
					    काष्ठा drm_bridge_state *state);
व्योम __drm_atomic_helper_bridge_reset(काष्ठा drm_bridge *bridge,
				      काष्ठा drm_bridge_state *state);
काष्ठा drm_bridge_state *
drm_atomic_helper_bridge_reset(काष्ठा drm_bridge *bridge);
