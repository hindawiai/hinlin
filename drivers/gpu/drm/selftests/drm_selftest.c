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

#समावेश <linux/compiler.h>

#घोषणा selftest(name, func) __idx_##name,
क्रमागत अणु
#समावेश TESTS
पूर्ण;
#अघोषित selftest

#घोषणा selftest(n, f) [__idx_##n] = अणु .name = #n, .func = f पूर्ण,
अटल काष्ठा drm_selftest अणु
	bool enabled;
	स्थिर अक्षर *name;
	पूर्णांक (*func)(व्योम *);
पूर्ण selftests[] = अणु
#समावेश TESTS
पूर्ण;
#अघोषित selftest

/* Embed the line number पूर्णांकo the parameter name so that we can order tests */
#घोषणा param(n) __PASTE(igt__, __PASTE(__PASTE(__LINE__, __), n))
#घोषणा selftest_0(n, func, id) \
module_param_named(id, selftests[__idx_##n].enabled, bool, 0400);
#घोषणा selftest(n, func) selftest_0(n, func, param(n))
#समावेश TESTS
#अघोषित selftest

अटल व्योम set_शेष_test_all(काष्ठा drm_selftest *st, अचिन्हित दीर्घ count)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < count; i++)
		अगर (st[i].enabled)
			वापस;

	क्रम (i = 0; i < count; i++)
		st[i].enabled = true;
पूर्ण

अटल पूर्णांक run_selftests(काष्ठा drm_selftest *st,
			 अचिन्हित दीर्घ count,
			 व्योम *data)
अणु
	पूर्णांक err = 0;

	set_शेष_test_all(st, count);

	/* Tests are listed in natural order in drm_*_selftests.h */
	क्रम (; count--; st++) अणु
		अगर (!st->enabled)
			जारी;

		pr_debug("drm: Running %s\n", st->name);
		err = st->func(data);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (WARN(err > 0 || err == -ENOTTY,
		 "%s returned %d, conflicting with selftest's magic values!\n",
		 st->name, err))
		err = -1;

	rcu_barrier();
	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused
__drm_subtests(स्थिर अक्षर *caller,
	       स्थिर काष्ठा drm_subtest *st,
	       पूर्णांक count,
	       व्योम *data)
अणु
	पूर्णांक err;

	क्रम (; count--; st++) अणु
		pr_debug("Running %s/%s\n", caller, st->name);
		err = st->func(data);
		अगर (err) अणु
			pr_err("%s: %s failed with error %d\n",
			       caller, st->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
