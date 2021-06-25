<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_GT__
#घोषणा __INTEL_GT__

#समावेश "intel_engine_types.h"
#समावेश "intel_gt_types.h"
#समावेश "intel_reset.h"

काष्ठा drm_i915_निजी;
काष्ठा drm_prपूर्णांकer;

#घोषणा GT_TRACE(gt, fmt, ...) करो अणु					\
	स्थिर काष्ठा पूर्णांकel_gt *gt__ __maybe_unused = (gt);		\
	GEM_TRACE("%s " fmt, dev_name(gt__->i915->drm.dev),		\
		  ##__VA_ARGS__);					\
पूर्ण जबतक (0)

अटल अंतरभूत काष्ठा पूर्णांकel_gt *uc_to_gt(काष्ठा पूर्णांकel_uc *uc)
अणु
	वापस container_of(uc, काष्ठा पूर्णांकel_gt, uc);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_gt *guc_to_gt(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस container_of(guc, काष्ठा पूर्णांकel_gt, uc.guc);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_gt *huc_to_gt(काष्ठा पूर्णांकel_huc *huc)
अणु
	वापस container_of(huc, काष्ठा पूर्णांकel_gt, uc.huc);
पूर्ण

व्योम पूर्णांकel_gt_init_early(काष्ठा पूर्णांकel_gt *gt, काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_gt_init_hw_early(काष्ठा पूर्णांकel_gt *gt, काष्ठा i915_ggtt *ggtt);
पूर्णांक पूर्णांकel_gt_probe_lmem(काष्ठा पूर्णांकel_gt *gt);
पूर्णांक पूर्णांकel_gt_init_mmio(काष्ठा पूर्णांकel_gt *gt);
पूर्णांक __must_check पूर्णांकel_gt_init_hw(काष्ठा पूर्णांकel_gt *gt);
पूर्णांक पूर्णांकel_gt_init(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_driver_रेजिस्टर(काष्ठा पूर्णांकel_gt *gt);

व्योम पूर्णांकel_gt_driver_unरेजिस्टर(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_driver_हटाओ(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_driver_release(काष्ठा पूर्णांकel_gt *gt);

व्योम पूर्णांकel_gt_driver_late_release(काष्ठा पूर्णांकel_gt *gt);

व्योम पूर्णांकel_gt_check_and_clear_faults(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_clear_error_रेजिस्टरs(काष्ठा पूर्णांकel_gt *gt,
				    पूर्णांकel_engine_mask_t engine_mask);

व्योम पूर्णांकel_gt_flush_ggtt_ग_लिखोs(काष्ठा पूर्णांकel_gt *gt);
व्योम पूर्णांकel_gt_chipset_flush(काष्ठा पूर्णांकel_gt *gt);

अटल अंतरभूत u32 पूर्णांकel_gt_scratch_offset(स्थिर काष्ठा पूर्णांकel_gt *gt,
					  क्रमागत पूर्णांकel_gt_scratch_field field)
अणु
	वापस i915_ggtt_offset(gt->scratch) + field;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_gt_has_unrecoverable_error(स्थिर काष्ठा पूर्णांकel_gt *gt)
अणु
	वापस test_bit(I915_WEDGED_ON_INIT, &gt->reset.flags) ||
	       test_bit(I915_WEDGED_ON_FINI, &gt->reset.flags);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_gt_is_wedged(स्थिर काष्ठा पूर्णांकel_gt *gt)
अणु
	GEM_BUG_ON(पूर्णांकel_gt_has_unrecoverable_error(gt) &&
		   !test_bit(I915_WEDGED, &gt->reset.flags));

	वापस unlikely(test_bit(I915_WEDGED, &gt->reset.flags));
पूर्ण

व्योम पूर्णांकel_gt_info_prपूर्णांक(स्थिर काष्ठा पूर्णांकel_gt_info *info,
			 काष्ठा drm_prपूर्णांकer *p);

व्योम पूर्णांकel_gt_watchकरोg_work(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर /* __INTEL_GT_H__ */
