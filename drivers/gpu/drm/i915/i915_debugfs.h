<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_DEBUGFS_H__
#घोषणा __I915_DEBUGFS_H__

काष्ठा drm_connector;
काष्ठा drm_i915_gem_object;
काष्ठा drm_i915_निजी;
काष्ठा seq_file;

#अगर_घोषित CONFIG_DEBUG_FS
व्योम i915_debugfs_रेजिस्टर(काष्ठा drm_i915_निजी *dev_priv);
व्योम i915_debugfs_describe_obj(काष्ठा seq_file *m, काष्ठा drm_i915_gem_object *obj);
#अन्यथा
अटल अंतरभूत व्योम i915_debugfs_रेजिस्टर(काष्ठा drm_i915_निजी *dev_priv) अणुपूर्ण
अटल अंतरभूत व्योम i915_debugfs_describe_obj(काष्ठा seq_file *m, काष्ठा drm_i915_gem_object *obj) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __I915_DEBUGFS_H__ */
