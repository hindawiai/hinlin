<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_GT_PM_H
#घोषणा INTEL_GT_PM_H

#समावेश <linux/types.h>

#समावेश "intel_gt_types.h"
#समावेश "intel_wakeref.h"

अटल अंतरभूत bool पूर्णांकel_gt_pm_is_awake(स्थिर काष्ठा पूर्णांकel_gt *gt)
अणु
	वापस पूर्णांकel_wakeref_is_active(&gt->wakeref);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_gt_pm_get(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_wakeref_get(&gt->wakeref);
पूर्ण

अटल अंतरभूत व्योम __पूर्णांकel_gt_pm_get(काष्ठा पूर्णांकel_gt *gt)
अणु
	__पूर्णांकel_wakeref_get(&gt->wakeref);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_gt_pm_get_अगर_awake(काष्ठा पूर्णांकel_gt *gt)
अणु
	वापस पूर्णांकel_wakeref_get_अगर_active(&gt->wakeref);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_gt_pm_put(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_wakeref_put(&gt->wakeref);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_gt_pm_put_async(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_wakeref_put_async(&gt->wakeref);
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_gt_pm_रुको_क्रम_idle(काष्ठा पूर्णांकel_gt *gt)
अणु
	वापस पूर्णांकel_wakeref_रुको_क्रम_idle(&gt->wakeref);
पूर्ण

व्योम पूर्णांकel_gt_pm_init_early(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_pm_init(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_pm_fini(काष्ठा पूर्णांकel_gt *gt);

व्योम पूर्णांकel_gt_suspend_prepare(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_suspend_late(काष्ठा पूर्णांकel_gt *gt);
पूर्णांक पूर्णांकel_gt_resume(काष्ठा पूर्णांकel_gt *gt);

व्योम पूर्णांकel_gt_runसमय_suspend(काष्ठा पूर्णांकel_gt *gt);
पूर्णांक पूर्णांकel_gt_runसमय_resume(काष्ठा पूर्णांकel_gt *gt);

kसमय_प्रकार पूर्णांकel_gt_get_awake_समय(स्थिर काष्ठा पूर्णांकel_gt *gt);

अटल अंतरभूत bool is_mock_gt(स्थिर काष्ठा पूर्णांकel_gt *gt)
अणु
	वापस I915_SELFTEST_ONLY(gt->awake == -ENODEV);
पूर्ण

#पूर्ण_अगर /* INTEL_GT_PM_H */
