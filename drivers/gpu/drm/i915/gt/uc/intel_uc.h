<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_UC_H_
#घोषणा _INTEL_UC_H_

#समावेश "intel_guc.h"
#समावेश "intel_guc_submission.h"
#समावेश "intel_huc.h"
#समावेश "i915_params.h"

काष्ठा पूर्णांकel_uc;

काष्ठा पूर्णांकel_uc_ops अणु
	पूर्णांक (*sanitize)(काष्ठा पूर्णांकel_uc *uc);
	व्योम (*init_fw)(काष्ठा पूर्णांकel_uc *uc);
	व्योम (*fini_fw)(काष्ठा पूर्णांकel_uc *uc);
	पूर्णांक (*init)(काष्ठा पूर्णांकel_uc *uc);
	व्योम (*fini)(काष्ठा पूर्णांकel_uc *uc);
	पूर्णांक (*init_hw)(काष्ठा पूर्णांकel_uc *uc);
	व्योम (*fini_hw)(काष्ठा पूर्णांकel_uc *uc);
पूर्ण;

काष्ठा पूर्णांकel_uc अणु
	काष्ठा पूर्णांकel_uc_ops स्थिर *ops;
	काष्ठा पूर्णांकel_guc guc;
	काष्ठा पूर्णांकel_huc huc;

	/* Snapshot of GuC log from last failed load */
	काष्ठा drm_i915_gem_object *load_err_log;
पूर्ण;

व्योम पूर्णांकel_uc_init_early(काष्ठा पूर्णांकel_uc *uc);
व्योम पूर्णांकel_uc_driver_late_release(काष्ठा पूर्णांकel_uc *uc);
व्योम पूर्णांकel_uc_driver_हटाओ(काष्ठा पूर्णांकel_uc *uc);
व्योम पूर्णांकel_uc_init_mmio(काष्ठा पूर्णांकel_uc *uc);
व्योम पूर्णांकel_uc_reset_prepare(काष्ठा पूर्णांकel_uc *uc);
व्योम पूर्णांकel_uc_suspend(काष्ठा पूर्णांकel_uc *uc);
व्योम पूर्णांकel_uc_runसमय_suspend(काष्ठा पूर्णांकel_uc *uc);
पूर्णांक पूर्णांकel_uc_resume(काष्ठा पूर्णांकel_uc *uc);
पूर्णांक पूर्णांकel_uc_runसमय_resume(काष्ठा पूर्णांकel_uc *uc);

/*
 * We need to know as early as possible अगर we're going to use GuC or not to
 * take the correct setup paths. Additionally, once we've started loading the
 * GuC, it is unsafe to keep executing without it because some parts of the HW,
 * a subset of which is not cleaned on GT reset, will start expecting the GuC FW
 * to be running.
 * To solve both these requirements, we commit to using the microcontrollers अगर
 * the relevant modparam is set and the blobs are found on the प्रणाली. At this
 * stage, the only thing that can stop us from attempting to load the blobs on
 * the HW and use them is a fundamental issue (e.g. no memory क्रम our
 * काष्ठाures); अगर we hit such a problem during driver load we're broken even
 * without GuC, so there is no poपूर्णांक in trying to fall back.
 *
 * Given the above, we can be in one of 4 states, with the last one implying
 * we're committed to using the microcontroller:
 * - Not supported: not available in HW and/or firmware not defined.
 * - Supported: available in HW and firmware defined.
 * - Wanted: supported + enabled in modparam.
 * - In use: wanted + firmware found on the प्रणाली and successfully fetched.
 */

#घोषणा __uc_state_checker(x, func, state, required) \
अटल अंतरभूत bool पूर्णांकel_uc_##state##_##func(काष्ठा पूर्णांकel_uc *uc) \
अणु \
	वापस पूर्णांकel_##func##_is_##required(&uc->x); \
पूर्ण

#घोषणा uc_state_checkers(x, func) \
__uc_state_checker(x, func, supports, supported) \
__uc_state_checker(x, func, wants, wanted) \
__uc_state_checker(x, func, uses, used)

uc_state_checkers(guc, guc);
uc_state_checkers(huc, huc);
uc_state_checkers(guc, guc_submission);

#अघोषित uc_state_checkers
#अघोषित __uc_state_checker

#घोषणा पूर्णांकel_uc_ops_function(_NAME, _OPS, _TYPE, _RET) \
अटल अंतरभूत _TYPE पूर्णांकel_uc_##_NAME(काष्ठा पूर्णांकel_uc *uc) \
अणु \
	अगर (uc->ops->_OPS) \
		वापस uc->ops->_OPS(uc); \
	वापस _RET; \
पूर्ण
पूर्णांकel_uc_ops_function(sanitize, sanitize, पूर्णांक, 0);
पूर्णांकel_uc_ops_function(fetch_firmwares, init_fw, व्योम, );
पूर्णांकel_uc_ops_function(cleanup_firmwares, fini_fw, व्योम, );
पूर्णांकel_uc_ops_function(init, init, पूर्णांक, 0);
पूर्णांकel_uc_ops_function(fini, fini, व्योम, );
पूर्णांकel_uc_ops_function(init_hw, init_hw, पूर्णांक, 0);
पूर्णांकel_uc_ops_function(fini_hw, fini_hw, व्योम, );
#अघोषित पूर्णांकel_uc_ops_function

#पूर्ण_अगर
