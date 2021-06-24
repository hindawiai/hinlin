<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_OVERLAY_H__
#घोषणा __INTEL_OVERLAY_H__

काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_i915_error_state_buf;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_overlay;
काष्ठा पूर्णांकel_overlay_error_state;

व्योम पूर्णांकel_overlay_setup(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_overlay_cleanup(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक पूर्णांकel_overlay_चयन_off(काष्ठा पूर्णांकel_overlay *overlay);
पूर्णांक पूर्णांकel_overlay_put_image_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv);
पूर्णांक पूर्णांकel_overlay_attrs_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv);
व्योम पूर्णांकel_overlay_reset(काष्ठा drm_i915_निजी *dev_priv);
काष्ठा पूर्णांकel_overlay_error_state *
पूर्णांकel_overlay_capture_error_state(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_overlay_prपूर्णांक_error_state(काष्ठा drm_i915_error_state_buf *e,
				     काष्ठा पूर्णांकel_overlay_error_state *error);

#पूर्ण_अगर /* __INTEL_OVERLAY_H__ */
