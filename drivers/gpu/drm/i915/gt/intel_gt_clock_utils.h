<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __INTEL_GT_CLOCK_UTILS_H__
#घोषणा __INTEL_GT_CLOCK_UTILS_H__

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_gt;

व्योम पूर्णांकel_gt_init_घड़ी_frequency(काष्ठा पूर्णांकel_gt *gt);

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)
व्योम पूर्णांकel_gt_check_घड़ी_frequency(स्थिर काष्ठा पूर्णांकel_gt *gt);
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकel_gt_check_घड़ी_frequency(स्थिर काष्ठा पूर्णांकel_gt *gt) अणुपूर्ण
#पूर्ण_अगर

u64 पूर्णांकel_gt_घड़ी_पूर्णांकerval_to_ns(स्थिर काष्ठा पूर्णांकel_gt *gt, u64 count);
u64 पूर्णांकel_gt_pm_पूर्णांकerval_to_ns(स्थिर काष्ठा पूर्णांकel_gt *gt, u64 count);

u64 पूर्णांकel_gt_ns_to_घड़ी_पूर्णांकerval(स्थिर काष्ठा पूर्णांकel_gt *gt, u64 ns);
u64 पूर्णांकel_gt_ns_to_pm_पूर्णांकerval(स्थिर काष्ठा पूर्णांकel_gt *gt, u64 ns);

#पूर्ण_अगर /* __INTEL_GT_CLOCK_UTILS_H__ */
