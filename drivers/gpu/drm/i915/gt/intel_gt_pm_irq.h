<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_GT_PM_IRQ_H
#घोषणा INTEL_GT_PM_IRQ_H

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_gt;

व्योम gen6_gt_pm_unmask_irq(काष्ठा पूर्णांकel_gt *gt, u32 mask);
व्योम gen6_gt_pm_mask_irq(काष्ठा पूर्णांकel_gt *gt, u32 mask);

व्योम gen6_gt_pm_enable_irq(काष्ठा पूर्णांकel_gt *gt, u32 enable_mask);
व्योम gen6_gt_pm_disable_irq(काष्ठा पूर्णांकel_gt *gt, u32 disable_mask);

व्योम gen6_gt_pm_reset_iir(काष्ठा पूर्णांकel_gt *gt, u32 reset_mask);

#पूर्ण_अगर /* INTEL_GT_PM_IRQ_H */
