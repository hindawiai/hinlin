<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_FBDEV_H__
#घोषणा __INTEL_FBDEV_H__

#समावेश <linux/types.h>

काष्ठा drm_device;
काष्ठा drm_i915_निजी;

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
पूर्णांक पूर्णांकel_fbdev_init(काष्ठा drm_device *dev);
व्योम पूर्णांकel_fbdev_initial_config_async(काष्ठा drm_device *dev);
व्योम पूर्णांकel_fbdev_unरेजिस्टर(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_fbdev_fini(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_fbdev_set_suspend(काष्ठा drm_device *dev, पूर्णांक state, bool synchronous);
व्योम पूर्णांकel_fbdev_output_poll_changed(काष्ठा drm_device *dev);
व्योम पूर्णांकel_fbdev_restore_mode(काष्ठा drm_device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक पूर्णांकel_fbdev_init(काष्ठा drm_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_fbdev_initial_config_async(काष्ठा drm_device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_fbdev_unरेजिस्टर(काष्ठा drm_i915_निजी *dev_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_fbdev_fini(काष्ठा drm_i915_निजी *dev_priv)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_fbdev_set_suspend(काष्ठा drm_device *dev, पूर्णांक state, bool synchronous)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_fbdev_output_poll_changed(काष्ठा drm_device *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_fbdev_restore_mode(काष्ठा drm_device *dev)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __INTEL_FBDEV_H__ */
