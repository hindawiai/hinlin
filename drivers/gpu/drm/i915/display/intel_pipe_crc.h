<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_PIPE_CRC_H__
#घोषणा __INTEL_PIPE_CRC_H__

#समावेश <linux/types.h>

काष्ठा drm_crtc;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc;

#अगर_घोषित CONFIG_DEBUG_FS
व्योम पूर्णांकel_crtc_crc_init(काष्ठा पूर्णांकel_crtc *crtc);
पूर्णांक पूर्णांकel_crtc_set_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source_name);
पूर्णांक पूर्णांकel_crtc_verअगरy_crc_source(काष्ठा drm_crtc *crtc,
				 स्थिर अक्षर *source_name, माप_प्रकार *values_cnt);
स्थिर अक्षर *स्थिर *पूर्णांकel_crtc_get_crc_sources(काष्ठा drm_crtc *crtc,
					      माप_प्रकार *count);
व्योम पूर्णांकel_crtc_disable_pipe_crc(काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_crtc_enable_pipe_crc(काष्ठा पूर्णांकel_crtc *crtc);
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकel_crtc_crc_init(काष्ठा पूर्णांकel_crtc *crtc) अणुपूर्ण
#घोषणा पूर्णांकel_crtc_set_crc_source शून्य
#घोषणा पूर्णांकel_crtc_verअगरy_crc_source शून्य
#घोषणा पूर्णांकel_crtc_get_crc_sources शून्य
अटल अंतरभूत व्योम पूर्णांकel_crtc_disable_pipe_crc(काष्ठा पूर्णांकel_crtc *crtc)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_crtc_enable_pipe_crc(काष्ठा पूर्णांकel_crtc *crtc)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __INTEL_PIPE_CRC_H__ */
