<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "i915_reg.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_irq.h"
#समावेश "intel_gt_pm_irq.h"

अटल व्योम ग_लिखो_pm_imr(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 mask = gt->pm_imr;
	i915_reg_t reg;

	अगर (INTEL_GEN(i915) >= 11) अणु
		reg = GEN11_GPM_WGBOXPERF_INTR_MASK;
		mask <<= 16; /* pm is in upper half */
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 8) अणु
		reg = GEN8_GT_IMR(2);
	पूर्ण अन्यथा अणु
		reg = GEN6_PMIMR;
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो(uncore, reg, mask);
पूर्ण

अटल व्योम gen6_gt_pm_update_irq(काष्ठा पूर्णांकel_gt *gt,
				  u32 पूर्णांकerrupt_mask,
				  u32 enabled_irq_mask)
अणु
	u32 new_val;

	WARN_ON(enabled_irq_mask & ~पूर्णांकerrupt_mask);

	lockdep_निश्चित_held(&gt->irq_lock);

	new_val = gt->pm_imr;
	new_val &= ~पूर्णांकerrupt_mask;
	new_val |= ~enabled_irq_mask & पूर्णांकerrupt_mask;

	अगर (new_val != gt->pm_imr) अणु
		gt->pm_imr = new_val;
		ग_लिखो_pm_imr(gt);
	पूर्ण
पूर्ण

व्योम gen6_gt_pm_unmask_irq(काष्ठा पूर्णांकel_gt *gt, u32 mask)
अणु
	gen6_gt_pm_update_irq(gt, mask, mask);
पूर्ण

व्योम gen6_gt_pm_mask_irq(काष्ठा पूर्णांकel_gt *gt, u32 mask)
अणु
	gen6_gt_pm_update_irq(gt, mask, 0);
पूर्ण

व्योम gen6_gt_pm_reset_iir(काष्ठा पूर्णांकel_gt *gt, u32 reset_mask)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	i915_reg_t reg = INTEL_GEN(gt->i915) >= 8 ? GEN8_GT_IIR(2) : GEN6_PMIIR;

	lockdep_निश्चित_held(&gt->irq_lock);

	पूर्णांकel_uncore_ग_लिखो(uncore, reg, reset_mask);
	पूर्णांकel_uncore_ग_लिखो(uncore, reg, reset_mask);
	पूर्णांकel_uncore_posting_पढ़ो(uncore, reg);
पूर्ण

अटल व्योम ग_लिखो_pm_ier(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 mask = gt->pm_ier;
	i915_reg_t reg;

	अगर (INTEL_GEN(i915) >= 11) अणु
		reg = GEN11_GPM_WGBOXPERF_INTR_ENABLE;
		mask <<= 16; /* pm is in upper half */
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 8) अणु
		reg = GEN8_GT_IER(2);
	पूर्ण अन्यथा अणु
		reg = GEN6_PMIER;
	पूर्ण

	पूर्णांकel_uncore_ग_लिखो(uncore, reg, mask);
पूर्ण

व्योम gen6_gt_pm_enable_irq(काष्ठा पूर्णांकel_gt *gt, u32 enable_mask)
अणु
	lockdep_निश्चित_held(&gt->irq_lock);

	gt->pm_ier |= enable_mask;
	ग_लिखो_pm_ier(gt);
	gen6_gt_pm_unmask_irq(gt, enable_mask);
पूर्ण

व्योम gen6_gt_pm_disable_irq(काष्ठा पूर्णांकel_gt *gt, u32 disable_mask)
अणु
	lockdep_निश्चित_held(&gt->irq_lock);

	gt->pm_ier &= ~disable_mask;
	gen6_gt_pm_mask_irq(gt, disable_mask);
	ग_लिखो_pm_ier(gt);
पूर्ण
