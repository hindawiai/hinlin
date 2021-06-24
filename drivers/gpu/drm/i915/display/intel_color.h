<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_COLOR_H__
#घोषणा __INTEL_COLOR_H__

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_crtc;
काष्ठा drm_property_blob;

व्योम पूर्णांकel_color_init(काष्ठा पूर्णांकel_crtc *crtc);
पूर्णांक पूर्णांकel_color_check(काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_color_commit(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_color_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_color_get_config(काष्ठा पूर्णांकel_crtc_state *crtc_state);
पूर्णांक पूर्णांकel_color_get_gamma_bit_precision(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
bool पूर्णांकel_color_lut_equal(काष्ठा drm_property_blob *blob1,
			   काष्ठा drm_property_blob *blob2,
			   u32 gamma_mode, u32 bit_precision);

#पूर्ण_अगर /* __INTEL_COLOR_H__ */
