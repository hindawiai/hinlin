<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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
 */

#समावेश <linux/अक्रमom.h>

#समावेश "gt/intel_gt_pm.h"
#समावेश "i915_drv.h"
#समावेश "i915_selftest.h"

#समावेश "igt_flush_test.h"

काष्ठा i915_selftest i915_selftest __पढ़ो_mostly = अणु
	.समयout_ms = 500,
पूर्ण;

पूर्णांक i915_mock_sanitycheck(व्योम)
अणु
	pr_info(DRIVER_NAME ": %s() - ok!\n", __func__);
	वापस 0;
पूर्ण

पूर्णांक i915_live_sanitycheck(काष्ठा drm_i915_निजी *i915)
अणु
	pr_info("%s: %s() - ok!\n", i915->drm.driver->name, __func__);
	वापस 0;
पूर्ण

क्रमागत अणु
#घोषणा selftest(name, func) mock_##name,
#समावेश "i915_mock_selftests.h"
#अघोषित selftest
पूर्ण;

क्रमागत अणु
#घोषणा selftest(name, func) live_##name,
#समावेश "i915_live_selftests.h"
#अघोषित selftest
पूर्ण;

क्रमागत अणु
#घोषणा selftest(name, func) perf_##name,
#समावेश "i915_perf_selftests.h"
#अघोषित selftest
पूर्ण;

काष्ठा selftest अणु
	bool enabled;
	स्थिर अक्षर *name;
	जोड़ अणु
		पूर्णांक (*mock)(व्योम);
		पूर्णांक (*live)(काष्ठा drm_i915_निजी *);
	पूर्ण;
पूर्ण;

#घोषणा selftest(n, f) [mock_##n] = अणु .name = #n, अणु .mock = f पूर्ण पूर्ण,
अटल काष्ठा selftest mock_selftests[] = अणु
#समावेश "i915_mock_selftests.h"
पूर्ण;
#अघोषित selftest

#घोषणा selftest(n, f) [live_##n] = अणु .name = #n, अणु .live = f पूर्ण पूर्ण,
अटल काष्ठा selftest live_selftests[] = अणु
#समावेश "i915_live_selftests.h"
पूर्ण;
#अघोषित selftest

#घोषणा selftest(n, f) [perf_##n] = अणु .name = #n, अणु .live = f पूर्ण पूर्ण,
अटल काष्ठा selftest perf_selftests[] = अणु
#समावेश "i915_perf_selftests.h"
पूर्ण;
#अघोषित selftest

/* Embed the line number पूर्णांकo the parameter name so that we can order tests */
#घोषणा selftest(n, func) selftest_0(n, func, param(n))
#घोषणा param(n) __PASTE(igt__, __PASTE(__LINE__, __mock_##n))
#घोषणा selftest_0(n, func, id) \
module_param_named(id, mock_selftests[mock_##n].enabled, bool, 0400);
#समावेश "i915_mock_selftests.h"
#अघोषित selftest_0
#अघोषित param

#घोषणा param(n) __PASTE(igt__, __PASTE(__LINE__, __live_##n))
#घोषणा selftest_0(n, func, id) \
module_param_named(id, live_selftests[live_##n].enabled, bool, 0400);
#समावेश "i915_live_selftests.h"
#अघोषित selftest_0
#अघोषित param

#घोषणा param(n) __PASTE(igt__, __PASTE(__LINE__, __perf_##n))
#घोषणा selftest_0(n, func, id) \
module_param_named(id, perf_selftests[perf_##n].enabled, bool, 0400);
#समावेश "i915_perf_selftests.h"
#अघोषित selftest_0
#अघोषित param
#अघोषित selftest

अटल व्योम set_शेष_test_all(काष्ठा selftest *st, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		अगर (st[i].enabled)
			वापस;

	क्रम (i = 0; i < count; i++)
		st[i].enabled = true;
पूर्ण

अटल पूर्णांक __run_selftests(स्थिर अक्षर *name,
			   काष्ठा selftest *st,
			   अचिन्हित पूर्णांक count,
			   व्योम *data)
अणु
	पूर्णांक err = 0;

	जबतक (!i915_selftest.अक्रमom_seed)
		i915_selftest.अक्रमom_seed = get_अक्रमom_पूर्णांक();

	i915_selftest.समयout_jअगरfies =
		i915_selftest.समयout_ms ?
		msecs_to_jअगरfies_समयout(i915_selftest.समयout_ms) :
		MAX_SCHEDULE_TIMEOUT;

	set_शेष_test_all(st, count);

	pr_info(DRIVER_NAME ": Performing %s selftests with st_random_seed=0x%x st_timeout=%u\n",
		name, i915_selftest.अक्रमom_seed, i915_selftest.समयout_ms);

	/* Tests are listed in order in i915_*_selftests.h */
	क्रम (; count--; st++) अणु
		अगर (!st->enabled)
			जारी;

		cond_resched();
		अगर (संकेत_pending(current))
			वापस -EINTR;

		pr_info(DRIVER_NAME ": Running %s\n", st->name);
		अगर (data)
			err = st->live(data);
		अन्यथा
			err = st->mock();
		अगर (err == -EINTR && !संकेत_pending(current))
			err = 0;
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (WARN(err > 0 || err == -ENOTTY,
		 "%s returned %d, conflicting with selftest's magic values!\n",
		 st->name, err))
		err = -1;

	वापस err;
पूर्ण

#घोषणा run_selftests(x, data) \
	__run_selftests(#x, x##_selftests, ARRAY_SIZE(x##_selftests), data)

पूर्णांक i915_mock_selftests(व्योम)
अणु
	पूर्णांक err;

	अगर (!i915_selftest.mock)
		वापस 0;

	err = run_selftests(mock, शून्य);
	अगर (err) अणु
		i915_selftest.mock = err;
		वापस err;
	पूर्ण

	अगर (i915_selftest.mock < 0) अणु
		i915_selftest.mock = -ENOTTY;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक i915_live_selftests(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err;

	अगर (!i915_selftest.live)
		वापस 0;

	err = run_selftests(live, pdev_to_i915(pdev));
	अगर (err) अणु
		i915_selftest.live = err;
		वापस err;
	पूर्ण

	अगर (i915_selftest.live < 0) अणु
		i915_selftest.live = -ENOTTY;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक i915_perf_selftests(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक err;

	अगर (!i915_selftest.perf)
		वापस 0;

	err = run_selftests(perf, pdev_to_i915(pdev));
	अगर (err) अणु
		i915_selftest.perf = err;
		वापस err;
	पूर्ण

	अगर (i915_selftest.perf < 0) अणु
		i915_selftest.perf = -ENOTTY;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool apply_subtest_filter(स्थिर अक्षर *caller, स्थिर अक्षर *name)
अणु
	अक्षर *filter, *sep, *tok;
	bool result = true;

	filter = kstrdup(i915_selftest.filter, GFP_KERNEL);
	क्रम (sep = filter; (tok = strsep(&sep, ","));) अणु
		bool allow = true;
		अक्षर *sl;

		अगर (*tok == '!') अणु
			allow = false;
			tok++;
		पूर्ण

		अगर (*tok == '\0')
			जारी;

		sl = म_अक्षर(tok, '/');
		अगर (sl) अणु
			*sl++ = '\0';
			अगर (म_भेद(tok, caller)) अणु
				अगर (allow)
					result = false;
				जारी;
			पूर्ण
			tok = sl;
		पूर्ण

		अगर (म_भेद(tok, name)) अणु
			अगर (allow)
				result = false;
			जारी;
		पूर्ण

		result = allow;
		अवरोध;
	पूर्ण
	kमुक्त(filter);

	वापस result;
पूर्ण

पूर्णांक __i915_nop_setup(व्योम *data)
अणु
	वापस 0;
पूर्ण

पूर्णांक __i915_nop_tearकरोwn(पूर्णांक err, व्योम *data)
अणु
	वापस err;
पूर्ण

पूर्णांक __i915_live_setup(व्योम *data)
अणु
	काष्ठा drm_i915_निजी *i915 = data;

	/* The selftests expect an idle प्रणाली */
	अगर (पूर्णांकel_gt_pm_रुको_क्रम_idle(&i915->gt))
		वापस -EIO;

	वापस पूर्णांकel_gt_terminally_wedged(&i915->gt);
पूर्ण

पूर्णांक __i915_live_tearकरोwn(पूर्णांक err, व्योम *data)
अणु
	काष्ठा drm_i915_निजी *i915 = data;

	अगर (igt_flush_test(i915))
		err = -EIO;

	i915_gem_drain_मुक्तd_objects(i915);

	वापस err;
पूर्ण

पूर्णांक __पूर्णांकel_gt_live_setup(व्योम *data)
अणु
	काष्ठा पूर्णांकel_gt *gt = data;

	/* The selftests expect an idle प्रणाली */
	अगर (पूर्णांकel_gt_pm_रुको_क्रम_idle(gt))
		वापस -EIO;

	वापस पूर्णांकel_gt_terminally_wedged(gt);
पूर्ण

पूर्णांक __पूर्णांकel_gt_live_tearकरोwn(पूर्णांक err, व्योम *data)
अणु
	काष्ठा पूर्णांकel_gt *gt = data;

	अगर (igt_flush_test(gt->i915))
		err = -EIO;

	i915_gem_drain_मुक्तd_objects(gt->i915);

	वापस err;
पूर्ण

पूर्णांक __i915_subtests(स्थिर अक्षर *caller,
		    पूर्णांक (*setup)(व्योम *data),
		    पूर्णांक (*tearकरोwn)(पूर्णांक err, व्योम *data),
		    स्थिर काष्ठा i915_subtest *st,
		    अचिन्हित पूर्णांक count,
		    व्योम *data)
अणु
	पूर्णांक err;

	क्रम (; count--; st++) अणु
		cond_resched();
		अगर (संकेत_pending(current))
			वापस -EINTR;

		अगर (!apply_subtest_filter(caller, st->name))
			जारी;

		err = setup(data);
		अगर (err) अणु
			pr_err(DRIVER_NAME "/%s: setup failed for %s\n",
			       caller, st->name);
			वापस err;
		पूर्ण

		pr_info(DRIVER_NAME ": Running %s/%s\n", caller, st->name);
		GEM_TRACE("Running %s/%s\n", caller, st->name);

		err = tearकरोwn(st->func(data), data);
		अगर (err && err != -EINTR) अणु
			pr_err(DRIVER_NAME "/%s: %s failed with error %d\n",
			       caller, st->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

bool __igt_समयout(अचिन्हित दीर्घ समयout, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;

	अगर (!संकेत_pending(current)) अणु
		cond_resched();
		अगर (समय_beक्रमe(jअगरfies, समयout))
			वापस false;
	पूर्ण

	अगर (fmt) अणु
		बहु_शुरू(va, fmt);
		vprपूर्णांकk(fmt, va);
		बहु_पूर्ण(va);
	पूर्ण

	वापस true;
पूर्ण

व्योम igt_hexdump(स्थिर व्योम *buf, माप_प्रकार len)
अणु
	स्थिर माप_प्रकार rowsize = 8 * माप(u32);
	स्थिर व्योम *prev = शून्य;
	bool skip = false;
	माप_प्रकार pos;

	क्रम (pos = 0; pos < len; pos += rowsize) अणु
		अक्षर line[128];

		अगर (prev && !स_भेद(prev, buf + pos, rowsize)) अणु
			अगर (!skip) अणु
				pr_info("*\n");
				skip = true;
			पूर्ण
			जारी;
		पूर्ण

		WARN_ON_ONCE(hex_dump_to_buffer(buf + pos, len - pos,
						rowsize, माप(u32),
						line, माप(line),
						false) >= माप(line));
		pr_info("[%04zx] %s\n", pos, line);

		prev = buf + pos;
		skip = false;
	पूर्ण
पूर्ण

module_param_named(st_अक्रमom_seed, i915_selftest.अक्रमom_seed, uपूर्णांक, 0400);
module_param_named(st_समयout, i915_selftest.समयout_ms, uपूर्णांक, 0400);
module_param_named(st_filter, i915_selftest.filter, अक्षरp, 0400);

module_param_named_unsafe(mock_selftests, i915_selftest.mock, पूर्णांक, 0400);
MODULE_PARM_DESC(mock_selftests, "Run selftests before loading, using mock hardware (0:disabled [default], 1:run tests then load driver, -1:run tests then exit module)");

module_param_named_unsafe(live_selftests, i915_selftest.live, पूर्णांक, 0400);
MODULE_PARM_DESC(live_selftests, "Run selftests after driver initialisation on the live system (0:disabled [default], 1:run tests then continue, -1:run tests then exit module)");

module_param_named_unsafe(perf_selftests, i915_selftest.perf, पूर्णांक, 0400);
MODULE_PARM_DESC(perf_selftests, "Run performance orientated selftests after driver initialisation on the live system (0:disabled [default], 1:run tests then continue, -1:run tests then exit module)");
