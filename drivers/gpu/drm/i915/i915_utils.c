<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <drm/drm_drv.h>

#समावेश "i915_drv.h"
#समावेश "i915_utils.h"

#घोषणा FDO_BUG_MSG "Please file a bug on drm/i915; see " FDO_BUG_URL " for details."

व्योम
__i915_prपूर्णांकk(काष्ठा drm_i915_निजी *dev_priv, स्थिर अक्षर *level,
	      स्थिर अक्षर *fmt, ...)
अणु
	अटल bool shown_bug_once;
	काष्ठा device *kdev = dev_priv->drm.dev;
	bool is_error = level[1] <= KERN_ERR[1];
	bool is_debug = level[1] == KERN_DEBUG[1];
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (is_debug && !drm_debug_enabled(DRM_UT_DRIVER))
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (is_error)
		dev_prपूर्णांकk(level, kdev, "%pV", &vaf);
	अन्यथा
		dev_prपूर्णांकk(level, kdev, "[" DRM_NAME ":%ps] %pV",
			   __builtin_वापस_address(0), &vaf);

	बहु_पूर्ण(args);

	अगर (is_error && !shown_bug_once) अणु
		/*
		 * Ask the user to file a bug report क्रम the error, except
		 * अगर they may have caused the bug by fiddling with unsafe
		 * module parameters.
		 */
		अगर (!test_taपूर्णांक(TAINT_USER))
			dev_notice(kdev, "%s", FDO_BUG_MSG);
		shown_bug_once = true;
	पूर्ण
पूर्ण

व्योम add_taपूर्णांक_क्रम_CI(काष्ठा drm_i915_निजी *i915, अचिन्हित पूर्णांक taपूर्णांक)
अणु
	__i915_prपूर्णांकk(i915, KERN_NOTICE, "CI tainted:%#x by %pS\n",
		      taपूर्णांक, (व्योम *)_RET_IP_);

	/* Failures that occur during fault injection testing are expected */
	अगर (!i915_error_injected())
		__add_taपूर्णांक_क्रम_CI(taपूर्णांक);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG)
अटल अचिन्हित पूर्णांक i915_probe_fail_count;

पूर्णांक __i915_inject_probe_error(काष्ठा drm_i915_निजी *i915, पूर्णांक err,
			      स्थिर अक्षर *func, पूर्णांक line)
अणु
	अगर (i915_probe_fail_count >= i915_modparams.inject_probe_failure)
		वापस 0;

	अगर (++i915_probe_fail_count < i915_modparams.inject_probe_failure)
		वापस 0;

	__i915_prपूर्णांकk(i915, KERN_INFO,
		      "Injecting failure %d at checkpoint %u [%s:%d]\n",
		      err, i915_modparams.inject_probe_failure, func, line);
	i915_modparams.inject_probe_failure = 0;
	वापस err;
पूर्ण

bool i915_error_injected(व्योम)
अणु
	वापस i915_probe_fail_count && !i915_modparams.inject_probe_failure;
पूर्ण

#पूर्ण_अगर

व्योम cancel_समयr(काष्ठा समयr_list *t)
अणु
	अगर (!समयr_active(t))
		वापस;

	del_समयr(t);
	WRITE_ONCE(t->expires, 0);
पूर्ण

व्योम set_समयr_ms(काष्ठा समयr_list *t, अचिन्हित दीर्घ समयout)
अणु
	अगर (!समयout) अणु
		cancel_समयr(t);
		वापस;
	पूर्ण

	समयout = msecs_to_jअगरfies(समयout);

	/*
	 * Paranoia to make sure the compiler computes the समयout beक्रमe
	 * loading 'jiffies' as jअगरfies is अस्थिर and may be updated in
	 * the background by a समयr tick. All to reduce the complनिकासy
	 * of the addition and reduce the risk of losing a jअगरfie.
	 */
	barrier();

	/* Keep t->expires = 0 reserved to indicate a canceled समयr. */
	mod_समयr(t, jअगरfies + समयout ?: 1);
पूर्ण
