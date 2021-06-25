<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_RUNTIME_PM_H__
#घोषणा __INTEL_RUNTIME_PM_H__

#समावेश <linux/types.h>

#समावेश "display/intel_display.h"

#समावेश "intel_wakeref.h"

#समावेश "i915_utils.h"

काष्ठा device;
काष्ठा drm_i915_निजी;
काष्ठा drm_prपूर्णांकer;

क्रमागत i915_drm_suspend_mode अणु
	I915_DRM_SUSPEND_IDLE,
	I915_DRM_SUSPEND_MEM,
	I915_DRM_SUSPEND_HIBERNATE,
पूर्ण;

/*
 * This काष्ठा helps tracking the state needed क्रम runसमय PM, which माला_दो the
 * device in PCI D3 state. Notice that when this happens, nothing on the
 * graphics device works, even रेजिस्टर access, so we करोn't get पूर्णांकerrupts nor
 * anything अन्यथा.
 *
 * Every piece of our code that needs to actually touch the hardware needs to
 * either call पूर्णांकel_runसमय_pm_get or call पूर्णांकel_display_घातer_get with the
 * appropriate घातer करोमुख्य.
 *
 * Our driver uses the स्वतःsuspend delay feature, which means we'll only really
 * suspend अगर we stay with zero refcount क्रम a certain amount of समय. The
 * शेष value is currently very conservative (see पूर्णांकel_runसमय_pm_enable), but
 * it can be changed with the standard runसमय PM files from sysfs.
 *
 * The irqs_disabled variable becomes true exactly after we disable the IRQs and
 * goes back to false exactly beक्रमe we reenable the IRQs. We use this variable
 * to check अगर someone is trying to enable/disable IRQs जबतक they're supposed
 * to be disabled. This shouldn't happen and we'll prपूर्णांक some error messages in
 * हाल it happens.
 *
 * For more, पढ़ो the Documentation/घातer/runसमय_pm.rst.
 */
काष्ठा पूर्णांकel_runसमय_pm अणु
	atomic_t wakeref_count;
	काष्ठा device *kdev; /* poपूर्णांकs to i915->drm.pdev->dev */
	bool available;
	bool suspended;
	bool irqs_enabled;

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
	/*
	 * To aide detection of wakeref leaks and general misuse, we
	 * track all wakeref holders. With manual markup (i.e. वापसing
	 * a cookie to each rpm_get caller which they then supply to their
	 * paired rpm_put) we can हटाओ corresponding pairs of and keep
	 * the array trimmed to active wakerefs.
	 */
	काष्ठा पूर्णांकel_runसमय_pm_debug अणु
		spinlock_t lock;

		depot_stack_handle_t last_acquire;
		depot_stack_handle_t last_release;

		depot_stack_handle_t *owners;
		अचिन्हित दीर्घ count;
	पूर्ण debug;
#पूर्ण_अगर
पूर्ण;

#घोषणा BITS_PER_WAKEREF	\
	BITS_PER_TYPE(काष्ठा_member(काष्ठा पूर्णांकel_runसमय_pm, wakeref_count))
#घोषणा INTEL_RPM_WAKELOCK_SHIFT	(BITS_PER_WAKEREF / 2)
#घोषणा INTEL_RPM_WAKELOCK_BIAS		(1 << INTEL_RPM_WAKELOCK_SHIFT)
#घोषणा INTEL_RPM_RAW_WAKEREF_MASK	(INTEL_RPM_WAKELOCK_BIAS - 1)

अटल अंतरभूत पूर्णांक
पूर्णांकel_rpm_raw_wakeref_count(पूर्णांक wakeref_count)
अणु
	वापस wakeref_count & INTEL_RPM_RAW_WAKEREF_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक
पूर्णांकel_rpm_wakelock_count(पूर्णांक wakeref_count)
अणु
	वापस wakeref_count >> INTEL_RPM_WAKELOCK_SHIFT;
पूर्ण

अटल अंतरभूत व्योम
निश्चित_rpm_device_not_suspended(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	WARN_ONCE(rpm->suspended,
		  "Device suspended during HW access\n");
पूर्ण

अटल अंतरभूत व्योम
__निश्चित_rpm_raw_wakeref_held(काष्ठा पूर्णांकel_runसमय_pm *rpm, पूर्णांक wakeref_count)
अणु
	निश्चित_rpm_device_not_suspended(rpm);
	WARN_ONCE(!पूर्णांकel_rpm_raw_wakeref_count(wakeref_count),
		  "RPM raw-wakeref not held\n");
पूर्ण

अटल अंतरभूत व्योम
__निश्चित_rpm_wakelock_held(काष्ठा पूर्णांकel_runसमय_pm *rpm, पूर्णांक wakeref_count)
अणु
	__निश्चित_rpm_raw_wakeref_held(rpm, wakeref_count);
	WARN_ONCE(!पूर्णांकel_rpm_wakelock_count(wakeref_count),
		  "RPM wakelock ref not held during HW access\n");
पूर्ण

अटल अंतरभूत व्योम
निश्चित_rpm_raw_wakeref_held(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	__निश्चित_rpm_raw_wakeref_held(rpm, atomic_पढ़ो(&rpm->wakeref_count));
पूर्ण

अटल अंतरभूत व्योम
निश्चित_rpm_wakelock_held(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	__निश्चित_rpm_wakelock_held(rpm, atomic_पढ़ो(&rpm->wakeref_count));
पूर्ण

/**
 * disable_rpm_wakeref_निश्चितs - disable the RPM निश्चित checks
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 *
 * This function disable निश्चितs that check अगर we hold an RPM wakelock
 * reference, जबतक keeping the device-not-suspended checks still enabled.
 * It's meant to be used only in special circumstances where our rule about
 * the wakelock refcount wrt. the device घातer state करोesn't hold. According
 * to this rule at any poपूर्णांक where we access the HW or want to keep the HW in
 * an active state we must hold an RPM wakelock reference acquired via one of
 * the पूर्णांकel_runसमय_pm_get() helpers. Currently there are a few special spots
 * where this rule करोesn't hold: the IRQ and suspend/resume handlers, the
 * क्रमcewake release समयr, and the GPU RPS and hangcheck works. All other
 * users should aव्योम using this function.
 *
 * Any calls to this function must have a symmetric call to
 * enable_rpm_wakeref_निश्चितs().
 */
अटल अंतरभूत व्योम
disable_rpm_wakeref_निश्चितs(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	atomic_add(INTEL_RPM_WAKELOCK_BIAS + 1,
		   &rpm->wakeref_count);
पूर्ण

/**
 * enable_rpm_wakeref_निश्चितs - re-enable the RPM निश्चित checks
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 *
 * This function re-enables the RPM निश्चित checks after disabling them with
 * disable_rpm_wakeref_निश्चितs. It's meant to be used only in special
 * circumstances otherwise its use should be aव्योमed.
 *
 * Any calls to this function must have a symmetric call to
 * disable_rpm_wakeref_निश्चितs().
 */
अटल अंतरभूत व्योम
enable_rpm_wakeref_निश्चितs(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	atomic_sub(INTEL_RPM_WAKELOCK_BIAS + 1,
		   &rpm->wakeref_count);
पूर्ण

व्योम पूर्णांकel_runसमय_pm_init_early(काष्ठा पूर्णांकel_runसमय_pm *rpm);
व्योम पूर्णांकel_runसमय_pm_enable(काष्ठा पूर्णांकel_runसमय_pm *rpm);
व्योम पूर्णांकel_runसमय_pm_disable(काष्ठा पूर्णांकel_runसमय_pm *rpm);
व्योम पूर्णांकel_runसमय_pm_driver_release(काष्ठा पूर्णांकel_runसमय_pm *rpm);

पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get(काष्ठा पूर्णांकel_runसमय_pm *rpm);
पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get_अगर_in_use(काष्ठा पूर्णांकel_runसमय_pm *rpm);
पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get_अगर_active(काष्ठा पूर्णांकel_runसमय_pm *rpm);
पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get_noresume(काष्ठा पूर्णांकel_runसमय_pm *rpm);
पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get_raw(काष्ठा पूर्णांकel_runसमय_pm *rpm);

#घोषणा with_पूर्णांकel_runसमय_pm(rpm, wf) \
	क्रम ((wf) = पूर्णांकel_runसमय_pm_get(rpm); (wf); \
	     पूर्णांकel_runसमय_pm_put((rpm), (wf)), (wf) = 0)

#घोषणा with_पूर्णांकel_runसमय_pm_अगर_in_use(rpm, wf) \
	क्रम ((wf) = पूर्णांकel_runसमय_pm_get_अगर_in_use(rpm); (wf); \
	     पूर्णांकel_runसमय_pm_put((rpm), (wf)), (wf) = 0)

#घोषणा with_पूर्णांकel_runसमय_pm_अगर_active(rpm, wf) \
	क्रम ((wf) = पूर्णांकel_runसमय_pm_get_अगर_active(rpm); (wf); \
	     पूर्णांकel_runसमय_pm_put((rpm), (wf)), (wf) = 0)

व्योम पूर्णांकel_runसमय_pm_put_unchecked(काष्ठा पूर्णांकel_runसमय_pm *rpm);
#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
व्योम पूर्णांकel_runसमय_pm_put(काष्ठा पूर्णांकel_runसमय_pm *rpm, पूर्णांकel_wakeref_t wref);
#अन्यथा
अटल अंतरभूत व्योम
पूर्णांकel_runसमय_pm_put(काष्ठा पूर्णांकel_runसमय_pm *rpm, पूर्णांकel_wakeref_t wref)
अणु
	पूर्णांकel_runसमय_pm_put_unchecked(rpm);
पूर्ण
#पूर्ण_अगर
व्योम पूर्णांकel_runसमय_pm_put_raw(काष्ठा पूर्णांकel_runसमय_pm *rpm, पूर्णांकel_wakeref_t wref);

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
व्योम prपूर्णांक_पूर्णांकel_runसमय_pm_wakeref(काष्ठा पूर्णांकel_runसमय_pm *rpm,
				    काष्ठा drm_prपूर्णांकer *p);
#अन्यथा
अटल अंतरभूत व्योम prपूर्णांक_पूर्णांकel_runसमय_pm_wakeref(काष्ठा पूर्णांकel_runसमय_pm *rpm,
						  काष्ठा drm_prपूर्णांकer *p)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __INTEL_RUNTIME_PM_H__ */
