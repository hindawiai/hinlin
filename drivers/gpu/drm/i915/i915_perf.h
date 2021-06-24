<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_PERF_H__
#घोषणा __I915_PERF_H__

#समावेश <linux/kref.h>
#समावेश <linux/types.h>

#समावेश "i915_perf_types.h"

काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_i915_निजी;
काष्ठा i915_oa_config;
काष्ठा पूर्णांकel_context;
काष्ठा पूर्णांकel_engine_cs;

व्योम i915_perf_init(काष्ठा drm_i915_निजी *i915);
व्योम i915_perf_fini(काष्ठा drm_i915_निजी *i915);
व्योम i915_perf_रेजिस्टर(काष्ठा drm_i915_निजी *i915);
व्योम i915_perf_unरेजिस्टर(काष्ठा drm_i915_निजी *i915);
पूर्णांक i915_perf_ioctl_version(व्योम);
व्योम i915_perf_sysctl_रेजिस्टर(व्योम);
व्योम i915_perf_sysctl_unरेजिस्टर(व्योम);

पूर्णांक i915_perf_खोलो_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file);
पूर्णांक i915_perf_add_config_ioctl(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file);
पूर्णांक i915_perf_हटाओ_config_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file);

व्योम i915_oa_init_reg_state(स्थिर काष्ठा पूर्णांकel_context *ce,
			    स्थिर काष्ठा पूर्णांकel_engine_cs *engine);

काष्ठा i915_oa_config *
i915_perf_get_oa_config(काष्ठा i915_perf *perf, पूर्णांक metrics_set);

अटल अंतरभूत काष्ठा i915_oa_config *
i915_oa_config_get(काष्ठा i915_oa_config *oa_config)
अणु
	अगर (kref_get_unless_zero(&oa_config->ref))
		वापस oa_config;
	अन्यथा
		वापस शून्य;
पूर्ण

व्योम i915_oa_config_release(काष्ठा kref *ref);
अटल अंतरभूत व्योम i915_oa_config_put(काष्ठा i915_oa_config *oa_config)
अणु
	अगर (!oa_config)
		वापस;

	kref_put(&oa_config->ref, i915_oa_config_release);
पूर्ण

#पूर्ण_अगर /* __I915_PERF_H__ */
