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

#अगर_अघोषित __I915_SELFTEST_H__
#घोषणा __I915_SELFTEST_H__

#समावेश <linux/types.h>

काष्ठा pci_dev;
काष्ठा drm_i915_निजी;

काष्ठा i915_selftest अणु
	अचिन्हित दीर्घ समयout_jअगरfies;
	अचिन्हित पूर्णांक समयout_ms;
	अचिन्हित पूर्णांक अक्रमom_seed;
	अक्षर *filter;
	पूर्णांक mock;
	पूर्णांक live;
	पूर्णांक perf;
पूर्ण;

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश <linux/fault-inject.h>

बाह्य काष्ठा i915_selftest i915_selftest;

पूर्णांक i915_mock_selftests(व्योम);
पूर्णांक i915_live_selftests(काष्ठा pci_dev *pdev);
पूर्णांक i915_perf_selftests(काष्ठा pci_dev *pdev);

/* We extract the function declarations from i915_mock_selftests.h and
 * i915_live_selftests.h Add your unit test declarations there!
 *
 * Mock unit tests are run very early upon module load, beक्रमe the driver
 * is probed. All hardware पूर्णांकeractions, as well as other subप्रणालीs, must
 * be "mocked".
 *
 * Live unit tests are run after the driver is loaded - all hardware
 * पूर्णांकeractions are real.
 */
#घोषणा selftest(name, func) पूर्णांक func(व्योम);
#समावेश "selftests/i915_mock_selftests.h"
#अघोषित selftest
#घोषणा selftest(name, func) पूर्णांक func(काष्ठा drm_i915_निजी *i915);
#समावेश "selftests/i915_live_selftests.h"
#समावेश "selftests/i915_perf_selftests.h"
#अघोषित selftest

काष्ठा i915_subtest अणु
	पूर्णांक (*func)(व्योम *data);
	स्थिर अक्षर *name;
पूर्ण;

पूर्णांक __i915_nop_setup(व्योम *data);
पूर्णांक __i915_nop_tearकरोwn(पूर्णांक err, व्योम *data);

पूर्णांक __i915_live_setup(व्योम *data);
पूर्णांक __i915_live_tearकरोwn(पूर्णांक err, व्योम *data);

पूर्णांक __पूर्णांकel_gt_live_setup(व्योम *data);
पूर्णांक __पूर्णांकel_gt_live_tearकरोwn(पूर्णांक err, व्योम *data);

पूर्णांक __i915_subtests(स्थिर अक्षर *caller,
		    पूर्णांक (*setup)(व्योम *data),
		    पूर्णांक (*tearकरोwn)(पूर्णांक err, व्योम *data),
		    स्थिर काष्ठा i915_subtest *st,
		    अचिन्हित पूर्णांक count,
		    व्योम *data);
#घोषणा i915_subtests(T, data) \
	__i915_subtests(__func__, \
			__i915_nop_setup, __i915_nop_tearकरोwn, \
			T, ARRAY_SIZE(T), data)
#घोषणा i915_live_subtests(T, data) (अणु \
	typecheck(काष्ठा drm_i915_निजी *, data); \
	__i915_subtests(__func__, \
			__i915_live_setup, __i915_live_tearकरोwn, \
			T, ARRAY_SIZE(T), data); \
पूर्ण)
#घोषणा पूर्णांकel_gt_live_subtests(T, data) (अणु \
	typecheck(काष्ठा पूर्णांकel_gt *, data); \
	__i915_subtests(__func__, \
			__पूर्णांकel_gt_live_setup, __पूर्णांकel_gt_live_tearकरोwn, \
			T, ARRAY_SIZE(T), data); \
पूर्ण)

#घोषणा SUBTEST(x) अणु x, #x पूर्ण

#घोषणा I915_SELFTEST_DECLARE(x) x
#घोषणा I915_SELFTEST_ONLY(x) unlikely(x)
#घोषणा I915_SELFTEST_EXPORT

#अन्यथा /* !IS_ENABLED(CONFIG_DRM_I915_SELFTEST) */

अटल अंतरभूत पूर्णांक i915_mock_selftests(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक i915_live_selftests(काष्ठा pci_dev *pdev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक i915_perf_selftests(काष्ठा pci_dev *pdev) अणु वापस 0; पूर्ण

#घोषणा I915_SELFTEST_DECLARE(x)
#घोषणा I915_SELFTEST_ONLY(x) 0
#घोषणा I915_SELFTEST_EXPORT अटल

#पूर्ण_अगर

/* Using the i915_selftest_ prefix becomes a little unwieldy with the helpers.
 * Instead we use the igt_ लघुhand, in reference to the पूर्णांकel-gpu-tools
 * suite of uabi test हालs (which includes a test runner क्रम our selftests).
 */

#घोषणा IGT_TIMEOUT(name__) \
	अचिन्हित दीर्घ name__ = jअगरfies + i915_selftest.समयout_jअगरfies

__म_लिखो(2, 3)
bool __igt_समयout(अचिन्हित दीर्घ समयout, स्थिर अक्षर *fmt, ...);

#घोषणा igt_समयout(t, fmt, ...) \
	__igt_समयout((t), KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)

व्योम igt_hexdump(स्थिर व्योम *buf, माप_प्रकार len);

#पूर्ण_अगर /* !__I915_SELFTEST_H__ */
