<शैली गुरु>
/*
 * Copyright तऊ 2012-2014 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Eugeni Doकरोnov <eugeni.करोकरोnov@पूर्णांकel.com>
 *    Daniel Vetter <daniel.vetter@ffwll.ch>
 *
 */

#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"

/**
 * DOC: runसमय pm
 *
 * The i915 driver supports dynamic enabling and disabling of entire hardware
 * blocks at runसमय. This is especially important on the display side where
 * software is supposed to control many घातer gates manually on recent hardware,
 * since on the GT side a lot of the घातer management is करोne by the hardware.
 * But even there some manual control at the device level is required.
 *
 * Since i915 supports a भागerse set of platक्रमms with a unअगरied codebase and
 * hardware engineers just love to shuffle functionality around between घातer
 * करोमुख्यs there's a sizeable amount of indirection required. This file provides
 * generic functions to the driver क्रम grabbing and releasing references क्रम
 * असलtract घातer करोमुख्यs. It then maps those to the actual घातer wells
 * present क्रम a given platक्रमm.
 */

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)

#समावेश <linux/sort.h>

#घोषणा STACKDEPTH 8

अटल noअंतरभूत depot_stack_handle_t __save_depot_stack(व्योम)
अणु
	अचिन्हित दीर्घ entries[STACKDEPTH];
	अचिन्हित पूर्णांक n;

	n = stack_trace_save(entries, ARRAY_SIZE(entries), 1);
	वापस stack_depot_save(entries, n, GFP_NOWAIT | __GFP_NOWARN);
पूर्ण

अटल व्योम __prपूर्णांक_depot_stack(depot_stack_handle_t stack,
				अक्षर *buf, पूर्णांक sz, पूर्णांक indent)
अणु
	अचिन्हित दीर्घ *entries;
	अचिन्हित पूर्णांक nr_entries;

	nr_entries = stack_depot_fetch(stack, &entries);
	stack_trace_snprपूर्णांक(buf, sz, entries, nr_entries, indent);
पूर्ण

अटल व्योम init_पूर्णांकel_runसमय_pm_wakeref(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	spin_lock_init(&rpm->debug.lock);
पूर्ण

अटल noअंतरभूत depot_stack_handle_t
track_पूर्णांकel_runसमय_pm_wakeref(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	depot_stack_handle_t stack, *stacks;
	अचिन्हित दीर्घ flags;

	अगर (!rpm->available)
		वापस -1;

	stack = __save_depot_stack();
	अगर (!stack)
		वापस -1;

	spin_lock_irqsave(&rpm->debug.lock, flags);

	अगर (!rpm->debug.count)
		rpm->debug.last_acquire = stack;

	stacks = kपुनः_स्मृति(rpm->debug.owners,
			  (rpm->debug.count + 1) * माप(*stacks),
			  GFP_NOWAIT | __GFP_NOWARN);
	अगर (stacks) अणु
		stacks[rpm->debug.count++] = stack;
		rpm->debug.owners = stacks;
	पूर्ण अन्यथा अणु
		stack = -1;
	पूर्ण

	spin_unlock_irqrestore(&rpm->debug.lock, flags);

	वापस stack;
पूर्ण

अटल व्योम untrack_पूर्णांकel_runसमय_pm_wakeref(काष्ठा पूर्णांकel_runसमय_pm *rpm,
					     depot_stack_handle_t stack)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(rpm,
						     काष्ठा drm_i915_निजी,
						     runसमय_pm);
	अचिन्हित दीर्घ flags, n;
	bool found = false;

	अगर (unlikely(stack == -1))
		वापस;

	spin_lock_irqsave(&rpm->debug.lock, flags);
	क्रम (n = rpm->debug.count; n--; ) अणु
		अगर (rpm->debug.owners[n] == stack) अणु
			स_हटाओ(rpm->debug.owners + n,
				rpm->debug.owners + n + 1,
				(--rpm->debug.count - n) * माप(stack));
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&rpm->debug.lock, flags);

	अगर (drm_WARN(&i915->drm, !found,
		     "Unmatched wakeref (tracking %lu), count %u\n",
		     rpm->debug.count, atomic_पढ़ो(&rpm->wakeref_count))) अणु
		अक्षर *buf;

		buf = kदो_स्मृति(PAGE_SIZE, GFP_NOWAIT | __GFP_NOWARN);
		अगर (!buf)
			वापस;

		__prपूर्णांक_depot_stack(stack, buf, PAGE_SIZE, 2);
		DRM_DEBUG_DRIVER("wakeref %x from\n%s", stack, buf);

		stack = READ_ONCE(rpm->debug.last_release);
		अगर (stack) अणु
			__prपूर्णांक_depot_stack(stack, buf, PAGE_SIZE, 2);
			DRM_DEBUG_DRIVER("wakeref last released at\n%s", buf);
		पूर्ण

		kमुक्त(buf);
	पूर्ण
पूर्ण

अटल पूर्णांक cmphandle(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर depot_stack_handle_t * स्थिर a = _a, * स्थिर b = _b;

	अगर (*a < *b)
		वापस -1;
	अन्यथा अगर (*a > *b)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम
__prपूर्णांक_पूर्णांकel_runसमय_pm_wakeref(काष्ठा drm_prपूर्णांकer *p,
				 स्थिर काष्ठा पूर्णांकel_runसमय_pm_debug *dbg)
अणु
	अचिन्हित दीर्घ i;
	अक्षर *buf;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_NOWAIT | __GFP_NOWARN);
	अगर (!buf)
		वापस;

	अगर (dbg->last_acquire) अणु
		__prपूर्णांक_depot_stack(dbg->last_acquire, buf, PAGE_SIZE, 2);
		drm_म_लिखो(p, "Wakeref last acquired:\n%s", buf);
	पूर्ण

	अगर (dbg->last_release) अणु
		__prपूर्णांक_depot_stack(dbg->last_release, buf, PAGE_SIZE, 2);
		drm_म_लिखो(p, "Wakeref last released:\n%s", buf);
	पूर्ण

	drm_म_लिखो(p, "Wakeref count: %lu\n", dbg->count);

	sort(dbg->owners, dbg->count, माप(*dbg->owners), cmphandle, शून्य);

	क्रम (i = 0; i < dbg->count; i++) अणु
		depot_stack_handle_t stack = dbg->owners[i];
		अचिन्हित दीर्घ rep;

		rep = 1;
		जबतक (i + 1 < dbg->count && dbg->owners[i + 1] == stack)
			rep++, i++;
		__prपूर्णांक_depot_stack(stack, buf, PAGE_SIZE, 2);
		drm_म_लिखो(p, "Wakeref x%lu taken at:\n%s", rep, buf);
	पूर्ण

	kमुक्त(buf);
पूर्ण

अटल noअंतरभूत व्योम
__untrack_all_wakerefs(काष्ठा पूर्णांकel_runसमय_pm_debug *debug,
		       काष्ठा पूर्णांकel_runसमय_pm_debug *saved)
अणु
	*saved = *debug;

	debug->owners = शून्य;
	debug->count = 0;
	debug->last_release = __save_depot_stack();
पूर्ण

अटल व्योम
dump_and_मुक्त_wakeref_tracking(काष्ठा पूर्णांकel_runसमय_pm_debug *debug)
अणु
	अगर (debug->count) अणु
		काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer("i915");

		__prपूर्णांक_पूर्णांकel_runसमय_pm_wakeref(&p, debug);
	पूर्ण

	kमुक्त(debug->owners);
पूर्ण

अटल noअंतरभूत व्योम
__पूर्णांकel_wakeref_dec_and_check_tracking(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	काष्ठा पूर्णांकel_runसमय_pm_debug dbg = अणुपूर्ण;
	अचिन्हित दीर्घ flags;

	अगर (!atomic_dec_and_lock_irqsave(&rpm->wakeref_count,
					 &rpm->debug.lock,
					 flags))
		वापस;

	__untrack_all_wakerefs(&rpm->debug, &dbg);
	spin_unlock_irqrestore(&rpm->debug.lock, flags);

	dump_and_मुक्त_wakeref_tracking(&dbg);
पूर्ण

अटल noअंतरभूत व्योम
untrack_all_पूर्णांकel_runसमय_pm_wakerefs(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	काष्ठा पूर्णांकel_runसमय_pm_debug dbg = अणुपूर्ण;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rpm->debug.lock, flags);
	__untrack_all_wakerefs(&rpm->debug, &dbg);
	spin_unlock_irqrestore(&rpm->debug.lock, flags);

	dump_and_मुक्त_wakeref_tracking(&dbg);
पूर्ण

व्योम prपूर्णांक_पूर्णांकel_runसमय_pm_wakeref(काष्ठा पूर्णांकel_runसमय_pm *rpm,
				    काष्ठा drm_prपूर्णांकer *p)
अणु
	काष्ठा पूर्णांकel_runसमय_pm_debug dbg = अणुपूर्ण;

	करो अणु
		अचिन्हित दीर्घ alloc = dbg.count;
		depot_stack_handle_t *s;

		spin_lock_irq(&rpm->debug.lock);
		dbg.count = rpm->debug.count;
		अगर (dbg.count <= alloc) अणु
			स_नकल(dbg.owners,
			       rpm->debug.owners,
			       dbg.count * माप(*s));
		पूर्ण
		dbg.last_acquire = rpm->debug.last_acquire;
		dbg.last_release = rpm->debug.last_release;
		spin_unlock_irq(&rpm->debug.lock);
		अगर (dbg.count <= alloc)
			अवरोध;

		s = kपुनः_स्मृति(dbg.owners,
			     dbg.count * माप(*s),
			     GFP_NOWAIT | __GFP_NOWARN);
		अगर (!s)
			जाओ out;

		dbg.owners = s;
	पूर्ण जबतक (1);

	__prपूर्णांक_पूर्णांकel_runसमय_pm_wakeref(p, &dbg);

out:
	kमुक्त(dbg.owners);
पूर्ण

#अन्यथा

अटल व्योम init_पूर्णांकel_runसमय_pm_wakeref(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
पूर्ण

अटल depot_stack_handle_t
track_पूर्णांकel_runसमय_pm_wakeref(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	वापस -1;
पूर्ण

अटल व्योम untrack_पूर्णांकel_runसमय_pm_wakeref(काष्ठा पूर्णांकel_runसमय_pm *rpm,
					     पूर्णांकel_wakeref_t wref)
अणु
पूर्ण

अटल व्योम
__पूर्णांकel_wakeref_dec_and_check_tracking(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	atomic_dec(&rpm->wakeref_count);
पूर्ण

अटल व्योम
untrack_all_पूर्णांकel_runसमय_pm_wakerefs(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
पूर्ण

#पूर्ण_अगर

अटल व्योम
पूर्णांकel_runसमय_pm_acquire(काष्ठा पूर्णांकel_runसमय_pm *rpm, bool wakelock)
अणु
	अगर (wakelock) अणु
		atomic_add(1 + INTEL_RPM_WAKELOCK_BIAS, &rpm->wakeref_count);
		निश्चित_rpm_wakelock_held(rpm);
	पूर्ण अन्यथा अणु
		atomic_inc(&rpm->wakeref_count);
		निश्चित_rpm_raw_wakeref_held(rpm);
	पूर्ण
पूर्ण

अटल व्योम
पूर्णांकel_runसमय_pm_release(काष्ठा पूर्णांकel_runसमय_pm *rpm, पूर्णांक wakelock)
अणु
	अगर (wakelock) अणु
		निश्चित_rpm_wakelock_held(rpm);
		atomic_sub(INTEL_RPM_WAKELOCK_BIAS, &rpm->wakeref_count);
	पूर्ण अन्यथा अणु
		निश्चित_rpm_raw_wakeref_held(rpm);
	पूर्ण

	__पूर्णांकel_wakeref_dec_and_check_tracking(rpm);
पूर्ण

अटल पूर्णांकel_wakeref_t __पूर्णांकel_runसमय_pm_get(काष्ठा पूर्णांकel_runसमय_pm *rpm,
					      bool wakelock)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(rpm,
						     काष्ठा drm_i915_निजी,
						     runसमय_pm);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(rpm->kdev);
	drm_WARN_ONCE(&i915->drm, ret < 0,
		      "pm_runtime_get_sync() failed: %d\n", ret);

	पूर्णांकel_runसमय_pm_acquire(rpm, wakelock);

	वापस track_पूर्णांकel_runसमय_pm_wakeref(rpm);
पूर्ण

/**
 * पूर्णांकel_runसमय_pm_get_raw - grab a raw runसमय pm reference
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 *
 * This is the unlocked version of पूर्णांकel_display_घातer_is_enabled() and should
 * only be used from error capture and recovery code where deadlocks are
 * possible.
 * This function grअसल a device-level runसमय pm reference (mostly used क्रम
 * asynchronous PM management from display code) and ensures that it is घातered
 * up. Raw references are not considered during wakelock निश्चित checks.
 *
 * Any runसमय pm reference obtained by this function must have a symmetric
 * call to पूर्णांकel_runसमय_pm_put_raw() to release the reference again.
 *
 * Returns: the wakeref cookie to pass to पूर्णांकel_runसमय_pm_put_raw(), evaluates
 * as True अगर the wakeref was acquired, or False otherwise.
 */
पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get_raw(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	वापस __पूर्णांकel_runसमय_pm_get(rpm, false);
पूर्ण

/**
 * पूर्णांकel_runसमय_pm_get - grab a runसमय pm reference
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 *
 * This function grअसल a device-level runसमय pm reference (mostly used क्रम GEM
 * code to ensure the GTT or GT is on) and ensures that it is घातered up.
 *
 * Any runसमय pm reference obtained by this function must have a symmetric
 * call to पूर्णांकel_runसमय_pm_put() to release the reference again.
 *
 * Returns: the wakeref cookie to pass to पूर्णांकel_runसमय_pm_put()
 */
पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	वापस __पूर्णांकel_runसमय_pm_get(rpm, true);
पूर्ण

/**
 * __पूर्णांकel_runसमय_pm_get_अगर_active - grab a runसमय pm reference अगर device is active
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 * @ignore_usecount: get a ref even अगर dev->घातer.usage_count is 0
 *
 * This function grअसल a device-level runसमय pm reference अगर the device is
 * alपढ़ोy active and ensures that it is घातered up. It is illegal to try
 * and access the HW should पूर्णांकel_runसमय_pm_get_अगर_active() report failure.
 *
 * If @ignore_usecount is true, a reference will be acquired even अगर there is no
 * user requiring the device to be घातered up (dev->घातer.usage_count == 0).
 * If the function वापसs false in this हाल then it's guaranteed that the
 * device's runसमय suspend hook has been called alपढ़ोy or that it will be
 * called (and hence it's also guaranteed that the device's runसमय resume
 * hook will be called eventually).
 *
 * Any runसमय pm reference obtained by this function must have a symmetric
 * call to पूर्णांकel_runसमय_pm_put() to release the reference again.
 *
 * Returns: the wakeref cookie to pass to पूर्णांकel_runसमय_pm_put(), evaluates
 * as True अगर the wakeref was acquired, or False otherwise.
 */
अटल पूर्णांकel_wakeref_t __पूर्णांकel_runसमय_pm_get_अगर_active(काष्ठा पूर्णांकel_runसमय_pm *rpm,
							bool ignore_usecount)
अणु
	अगर (IS_ENABLED(CONFIG_PM)) अणु
		/*
		 * In हालs runसमय PM is disabled by the RPM core and we get
		 * an -EINVAL वापस value we are not supposed to call this
		 * function, since the घातer state is undefined. This applies
		 * aपंचांग to the late/early प्रणाली suspend/resume handlers.
		 */
		अगर (pm_runसमय_get_अगर_active(rpm->kdev, ignore_usecount) <= 0)
			वापस 0;
	पूर्ण

	पूर्णांकel_runसमय_pm_acquire(rpm, true);

	वापस track_पूर्णांकel_runसमय_pm_wakeref(rpm);
पूर्ण

पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get_अगर_in_use(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	वापस __पूर्णांकel_runसमय_pm_get_अगर_active(rpm, false);
पूर्ण

पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get_अगर_active(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	वापस __पूर्णांकel_runसमय_pm_get_अगर_active(rpm, true);
पूर्ण

/**
 * पूर्णांकel_runसमय_pm_get_noresume - grab a runसमय pm reference
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 *
 * This function grअसल a device-level runसमय pm reference (mostly used क्रम GEM
 * code to ensure the GTT or GT is on).
 *
 * It will _not_ घातer up the device but instead only check that it's घातered
 * on.  Thereक्रमe it is only valid to call this functions from contexts where
 * the device is known to be घातered up and where trying to घातer it up would
 * result in hilarity and deadlocks. That pretty much means only the प्रणाली
 * suspend/resume code where this is used to grab runसमय pm references क्रम
 * delayed setup करोwn in work items.
 *
 * Any runसमय pm reference obtained by this function must have a symmetric
 * call to पूर्णांकel_runसमय_pm_put() to release the reference again.
 *
 * Returns: the wakeref cookie to pass to पूर्णांकel_runसमय_pm_put()
 */
पूर्णांकel_wakeref_t पूर्णांकel_runसमय_pm_get_noresume(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	निश्चित_rpm_wakelock_held(rpm);
	pm_runसमय_get_noresume(rpm->kdev);

	पूर्णांकel_runसमय_pm_acquire(rpm, true);

	वापस track_पूर्णांकel_runसमय_pm_wakeref(rpm);
पूर्ण

अटल व्योम __पूर्णांकel_runसमय_pm_put(काष्ठा पूर्णांकel_runसमय_pm *rpm,
				   पूर्णांकel_wakeref_t wref,
				   bool wakelock)
अणु
	काष्ठा device *kdev = rpm->kdev;

	untrack_पूर्णांकel_runसमय_pm_wakeref(rpm, wref);

	पूर्णांकel_runसमय_pm_release(rpm, wakelock);

	pm_runसमय_mark_last_busy(kdev);
	pm_runसमय_put_स्वतःsuspend(kdev);
पूर्ण

/**
 * पूर्णांकel_runसमय_pm_put_raw - release a raw runसमय pm reference
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 * @wref: wakeref acquired क्रम the reference that is being released
 *
 * This function drops the device-level runसमय pm reference obtained by
 * पूर्णांकel_runसमय_pm_get_raw() and might घातer करोwn the corresponding
 * hardware block right away अगर this is the last reference.
 */
व्योम
पूर्णांकel_runसमय_pm_put_raw(काष्ठा पूर्णांकel_runसमय_pm *rpm, पूर्णांकel_wakeref_t wref)
अणु
	__पूर्णांकel_runसमय_pm_put(rpm, wref, false);
पूर्ण

/**
 * पूर्णांकel_runसमय_pm_put_unchecked - release an unchecked runसमय pm reference
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 *
 * This function drops the device-level runसमय pm reference obtained by
 * पूर्णांकel_runसमय_pm_get() and might घातer करोwn the corresponding
 * hardware block right away अगर this is the last reference.
 *
 * This function exists only क्रम historical reasons and should be aव्योमed in
 * new code, as the correctness of its use cannot be checked. Always use
 * पूर्णांकel_runसमय_pm_put() instead.
 */
व्योम पूर्णांकel_runसमय_pm_put_unchecked(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	__पूर्णांकel_runसमय_pm_put(rpm, -1, true);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
/**
 * पूर्णांकel_runसमय_pm_put - release a runसमय pm reference
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 * @wref: wakeref acquired क्रम the reference that is being released
 *
 * This function drops the device-level runसमय pm reference obtained by
 * पूर्णांकel_runसमय_pm_get() and might घातer करोwn the corresponding
 * hardware block right away अगर this is the last reference.
 */
व्योम पूर्णांकel_runसमय_pm_put(काष्ठा पूर्णांकel_runसमय_pm *rpm, पूर्णांकel_wakeref_t wref)
अणु
	__पूर्णांकel_runसमय_pm_put(rpm, wref, true);
पूर्ण
#पूर्ण_अगर

/**
 * पूर्णांकel_runसमय_pm_enable - enable runसमय pm
 * @rpm: the पूर्णांकel_runसमय_pm काष्ठाure
 *
 * This function enables runसमय pm at the end of the driver load sequence.
 *
 * Note that this function करोes currently not enable runसमय pm क्रम the
 * subordinate display घातer करोमुख्यs. That is करोne by
 * पूर्णांकel_घातer_करोमुख्यs_enable().
 */
व्योम पूर्णांकel_runसमय_pm_enable(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(rpm,
						     काष्ठा drm_i915_निजी,
						     runसमय_pm);
	काष्ठा device *kdev = rpm->kdev;

	/*
	 * Disable the प्रणाली suspend direct complete optimization, which can
	 * leave the device suspended skipping the driver's suspend handlers
	 * अगर the device was alपढ़ोy runसमय suspended. This is needed due to
	 * the dअगरference in our runसमय and प्रणाली suspend sequence and
	 * becaue the HDA driver may require us to enable the audio घातer
	 * करोमुख्य during प्रणाली suspend.
	 */
	dev_pm_set_driver_flags(kdev, DPM_FLAG_NO_सूचीECT_COMPLETE);

	pm_runसमय_set_स्वतःsuspend_delay(kdev, 10000); /* 10s */
	pm_runसमय_mark_last_busy(kdev);

	/*
	 * Take a permanent reference to disable the RPM functionality and drop
	 * it only when unloading the driver. Use the low level get/put helpers,
	 * so the driver's own RPM reference tracking निश्चितs also work on
	 * platक्रमms without RPM support.
	 */
	अगर (!rpm->available) अणु
		पूर्णांक ret;

		pm_runसमय_करोnt_use_स्वतःsuspend(kdev);
		ret = pm_runसमय_get_sync(kdev);
		drm_WARN(&i915->drm, ret < 0,
			 "pm_runtime_get_sync() failed: %d\n", ret);
	पूर्ण अन्यथा अणु
		pm_runसमय_use_स्वतःsuspend(kdev);
	पूर्ण

	/*
	 * The core calls the driver load handler with an RPM reference held.
	 * We drop that here and will reacquire it during unloading in
	 * पूर्णांकel_घातer_करोमुख्यs_fini().
	 */
	pm_runसमय_put_स्वतःsuspend(kdev);
पूर्ण

व्योम पूर्णांकel_runसमय_pm_disable(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(rpm,
						     काष्ठा drm_i915_निजी,
						     runसमय_pm);
	काष्ठा device *kdev = rpm->kdev;

	/* Transfer rpm ownership back to core */
	drm_WARN(&i915->drm, pm_runसमय_get_sync(kdev) < 0,
		 "Failed to pass rpm ownership back to core\n");

	pm_runसमय_करोnt_use_स्वतःsuspend(kdev);

	अगर (!rpm->available)
		pm_runसमय_put(kdev);
पूर्ण

व्योम पूर्णांकel_runसमय_pm_driver_release(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	काष्ठा drm_i915_निजी *i915 = container_of(rpm,
						     काष्ठा drm_i915_निजी,
						     runसमय_pm);
	पूर्णांक count = atomic_पढ़ो(&rpm->wakeref_count);

	drm_WARN(&i915->drm, count,
		 "i915 raw-wakerefs=%d wakelocks=%d on cleanup\n",
		 पूर्णांकel_rpm_raw_wakeref_count(count),
		 पूर्णांकel_rpm_wakelock_count(count));

	untrack_all_पूर्णांकel_runसमय_pm_wakerefs(rpm);
पूर्ण

व्योम पूर्णांकel_runसमय_pm_init_early(काष्ठा पूर्णांकel_runसमय_pm *rpm)
अणु
	काष्ठा drm_i915_निजी *i915 =
			container_of(rpm, काष्ठा drm_i915_निजी, runसमय_pm);
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);
	काष्ठा device *kdev = &pdev->dev;

	rpm->kdev = kdev;
	rpm->available = HAS_RUNTIME_PM(i915);

	init_पूर्णांकel_runसमय_pm_wakeref(rpm);
पूर्ण
