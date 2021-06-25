<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_VDSC_H__
#घोषणा __INTEL_VDSC_H__

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_crtc_state;

bool पूर्णांकel_dsc_source_support(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_dsc_enable(काष्ठा पूर्णांकel_encoder *encoder,
		      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_dsc_disable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
पूर्णांक पूर्णांकel_dsc_compute_params(काष्ठा पूर्णांकel_encoder *encoder,
			     काष्ठा पूर्णांकel_crtc_state *pipe_config);
व्योम पूर्णांकel_dsc_get_config(काष्ठा पूर्णांकel_crtc_state *crtc_state);
क्रमागत पूर्णांकel_display_घातer_करोमुख्य
पूर्णांकel_dsc_घातer_करोमुख्य(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

#पूर्ण_अगर /* __INTEL_VDSC_H__ */
