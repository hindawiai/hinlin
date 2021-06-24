<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2019 Google, Inc.
 *
 * Authors:
 * Sean Paul <seanpaul@chromium.org>
 */
#अगर_अघोषित DRM_SELF_REFRESH_HELPER_H_
#घोषणा DRM_SELF_REFRESH_HELPER_H_

काष्ठा drm_atomic_state;
काष्ठा drm_crtc;

व्योम drm_self_refresh_helper_alter_state(काष्ठा drm_atomic_state *state);
व्योम drm_self_refresh_helper_update_avg_बार(काष्ठा drm_atomic_state *state,
					अचिन्हित पूर्णांक commit_समय_ms,
					अचिन्हित पूर्णांक new_self_refresh_mask);

पूर्णांक drm_self_refresh_helper_init(काष्ठा drm_crtc *crtc);
व्योम drm_self_refresh_helper_cleanup(काष्ठा drm_crtc *crtc);
#पूर्ण_अगर
