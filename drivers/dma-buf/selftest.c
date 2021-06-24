<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>

#समावेश "selftest.h"

क्रमागत अणु
#घोषणा selftest(n, func) __idx_##n,
#समावेश "selftests.h"
#अघोषित selftest
पूर्ण;

#घोषणा selftest(n, f) [__idx_##n] = अणु .name = #n, .func = f पूर्ण,
अटल काष्ठा selftest अणु
	bool enabled;
	स्थिर अक्षर *name;
	पूर्णांक (*func)(व्योम);
पूर्ण selftests[] = अणु
#समावेश "selftests.h"
पूर्ण;
#अघोषित selftest

/* Embed the line number पूर्णांकo the parameter name so that we can order tests */
#घोषणा param(n) __PASTE(igt__, __PASTE(__PASTE(__LINE__, __), n))
#घोषणा selftest_0(n, func, id) \
module_param_named(id, selftests[__idx_##n].enabled, bool, 0400);
#घोषणा selftest(n, func) selftest_0(n, func, param(n))
#समावेश "selftests.h"
#अघोषित selftest

पूर्णांक __sanitycheck__(व्योम)
अणु
	pr_debug("Hello World!\n");
	वापस 0;
पूर्ण

अटल अक्षर *__st_filter;

अटल bool apply_subtest_filter(स्थिर अक्षर *caller, स्थिर अक्षर *name)
अणु
	अक्षर *filter, *sep, *tok;
	bool result = true;

	filter = kstrdup(__st_filter, GFP_KERNEL);
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

पूर्णांक
__subtests(स्थिर अक्षर *caller, स्थिर काष्ठा subtest *st, पूर्णांक count, व्योम *data)
अणु
	पूर्णांक err;

	क्रम (; count--; st++) अणु
		cond_resched();
		अगर (संकेत_pending(current))
			वापस -EINTR;

		अगर (!apply_subtest_filter(caller, st->name))
			जारी;

		pr_info("dma-buf: Running %s/%s\n", caller, st->name);

		err = st->func(data);
		अगर (err && err != -EINTR) अणु
			pr_err("dma-buf/%s: %s failed with error %d\n",
			       caller, st->name, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_शेष_test_all(काष्ठा selftest *st, अचिन्हित दीर्घ count)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < count; i++)
		अगर (st[i].enabled)
			वापस;

	क्रम (i = 0; i < count; i++)
		st[i].enabled = true;
पूर्ण

अटल पूर्णांक run_selftests(काष्ठा selftest *st, अचिन्हित दीर्घ count)
अणु
	पूर्णांक err = 0;

	set_शेष_test_all(st, count);

	/* Tests are listed in natural order in selftests.h */
	क्रम (; count--; st++) अणु
		अगर (!st->enabled)
			जारी;

		pr_info("dma-buf: Running %s\n", st->name);
		err = st->func();
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (WARN(err > 0 || err == -ENOTTY,
		 "%s returned %d, conflicting with selftest's magic values!\n",
		 st->name, err))
		err = -1;

	वापस err;
पूर्ण

अटल पूर्णांक __init st_init(व्योम)
अणु
	वापस run_selftests(selftests, ARRAY_SIZE(selftests));
पूर्ण

अटल व्योम __निकास st_निकास(व्योम)
अणु
पूर्ण

module_param_named(st_filter, __st_filter, अक्षरp, 0400);
module_init(st_init);
module_निकास(st_निकास);

MODULE_DESCRIPTION("Self-test harness for dma-buf");
MODULE_LICENSE("GPL and additional rights");
