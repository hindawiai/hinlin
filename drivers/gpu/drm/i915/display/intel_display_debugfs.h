<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __INTEL_DISPLAY_DEBUGFS_H__
#घोषणा __INTEL_DISPLAY_DEBUGFS_H__

काष्ठा drm_connector;
काष्ठा drm_crtc;
काष्ठा drm_i915_निजी;

#अगर_घोषित CONFIG_DEBUG_FS
व्योम पूर्णांकel_display_debugfs_रेजिस्टर(काष्ठा drm_i915_निजी *i915);
पूर्णांक पूर्णांकel_connector_debugfs_add(काष्ठा drm_connector *connector);
पूर्णांक पूर्णांकel_crtc_debugfs_add(काष्ठा drm_crtc *crtc);
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकel_display_debugfs_रेजिस्टर(काष्ठा drm_i915_निजी *i915) अणुपूर्ण
अटल अंतरभूत पूर्णांक पूर्णांकel_connector_debugfs_add(काष्ठा drm_connector *connector) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक पूर्णांकel_crtc_debugfs_add(काष्ठा drm_crtc *crtc) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __INTEL_DISPLAY_DEBUGFS_H__ */
