<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "tests.h"
#समावेश "dso.h"
#समावेश "debug.h"
#समावेश "event.h"

अटल पूर्णांक test(स्थिर अक्षर *path, bool alloc_name, bool kmod,
		पूर्णांक comp, स्थिर अक्षर *name)
अणु
	काष्ठा kmod_path m;

	स_रखो(&m, 0x0, माप(m));

	TEST_ASSERT_VAL("kmod_path__parse",
			!__kmod_path__parse(&m, path, alloc_name));

	pr_debug("%s - alloc name %d, kmod %d, comp %d, name '%s'\n",
		 path, alloc_name, m.kmod, m.comp, m.name);

	TEST_ASSERT_VAL("wrong kmod", m.kmod == kmod);
	TEST_ASSERT_VAL("wrong comp", m.comp == comp);

	अगर (name)
		TEST_ASSERT_VAL("wrong name", m.name && !म_भेद(name, m.name));
	अन्यथा
		TEST_ASSERT_VAL("wrong name", !m.name);

	मुक्त(m.name);
	वापस 0;
पूर्ण

अटल पूर्णांक test_is_kernel_module(स्थिर अक्षर *path, पूर्णांक cpumode, bool expect)
अणु
	TEST_ASSERT_VAL("is_kernel_module",
			(!!is_kernel_module(path, cpumode)) == (!!expect));
	pr_debug("%s (cpumode: %d) - is_kernel_module: %s\n",
			path, cpumode, expect ? "true" : "false");
	वापस 0;
पूर्ण

#घोषणा T(path, an, k, c, n) \
	TEST_ASSERT_VAL("failed", !test(path, an, k, c, n))

#घोषणा M(path, c, e) \
	TEST_ASSERT_VAL("failed", !test_is_kernel_module(path, c, e))

पूर्णांक test__kmod_path__parse(काष्ठा test *t __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	/* path                alloc_name  kmod  comp   name   */
	T("/xxxx/xxxx/x-x.ko", true      , true, 0    , "[x_x]");
	T("/xxxx/xxxx/x-x.ko", false     , true, 0    , शून्य   );
	T("/xxxx/xxxx/x-x.ko", true      , true, 0    , "[x_x]");
	T("/xxxx/xxxx/x-x.ko", false     , true, 0    , शून्य   );
	M("/xxxx/xxxx/x-x.ko", PERF_RECORD_MISC_CPUMODE_UNKNOWN, true);
	M("/xxxx/xxxx/x-x.ko", PERF_RECORD_MISC_KERNEL, true);
	M("/xxxx/xxxx/x-x.ko", PERF_RECORD_MISC_USER, false);

#अगर_घोषित HAVE_ZLIB_SUPPORT
	/* path                alloc_name   kmod  comp  name  */
	T("/xxxx/xxxx/x.ko.gz", true     , true, 1   , "[x]");
	T("/xxxx/xxxx/x.ko.gz", false    , true, 1   , शून्य );
	T("/xxxx/xxxx/x.ko.gz", true     , true, 1   , "[x]");
	T("/xxxx/xxxx/x.ko.gz", false    , true, 1   , शून्य );
	M("/xxxx/xxxx/x.ko.gz", PERF_RECORD_MISC_CPUMODE_UNKNOWN, true);
	M("/xxxx/xxxx/x.ko.gz", PERF_RECORD_MISC_KERNEL, true);
	M("/xxxx/xxxx/x.ko.gz", PERF_RECORD_MISC_USER, false);

	/* path              alloc_name  kmod   comp  name  */
	T("/xxxx/xxxx/x.gz", true      , false, 1   , "x.gz");
	T("/xxxx/xxxx/x.gz", false     , false, 1   , शून्य  );
	T("/xxxx/xxxx/x.gz", true      , false, 1   , "x.gz");
	T("/xxxx/xxxx/x.gz", false     , false, 1   , शून्य  );
	M("/xxxx/xxxx/x.gz", PERF_RECORD_MISC_CPUMODE_UNKNOWN, false);
	M("/xxxx/xxxx/x.gz", PERF_RECORD_MISC_KERNEL, false);
	M("/xxxx/xxxx/x.gz", PERF_RECORD_MISC_USER, false);

	/* path   alloc_name  kmod   comp  name   */
	T("x.gz", true      , false, 1   , "x.gz");
	T("x.gz", false     , false, 1   , शून्य  );
	T("x.gz", true      , false, 1   , "x.gz");
	T("x.gz", false     , false, 1   , शून्य  );
	M("x.gz", PERF_RECORD_MISC_CPUMODE_UNKNOWN, false);
	M("x.gz", PERF_RECORD_MISC_KERNEL, false);
	M("x.gz", PERF_RECORD_MISC_USER, false);

	/* path      alloc_name  kmod  comp  name  */
	T("x.ko.gz", true      , true, 1   , "[x]");
	T("x.ko.gz", false     , true, 1   , शून्य );
	T("x.ko.gz", true      , true, 1   , "[x]");
	T("x.ko.gz", false     , true, 1   , शून्य );
	M("x.ko.gz", PERF_RECORD_MISC_CPUMODE_UNKNOWN, true);
	M("x.ko.gz", PERF_RECORD_MISC_KERNEL, true);
	M("x.ko.gz", PERF_RECORD_MISC_USER, false);
#पूर्ण_अगर

	/* path            alloc_name  kmod  comp   name           */
	T("[test_module]", true      , true, false, "[test_module]");
	T("[test_module]", false     , true, false, शून्य           );
	T("[test_module]", true      , true, false, "[test_module]");
	T("[test_module]", false     , true, false, शून्य           );
	M("[test_module]", PERF_RECORD_MISC_CPUMODE_UNKNOWN, true);
	M("[test_module]", PERF_RECORD_MISC_KERNEL, true);
	M("[test_module]", PERF_RECORD_MISC_USER, false);

	/* path            alloc_name  kmod  comp   name           */
	T("[test.module]", true      , true, false, "[test.module]");
	T("[test.module]", false     , true, false, शून्य           );
	T("[test.module]", true      , true, false, "[test.module]");
	T("[test.module]", false     , true, false, शून्य           );
	M("[test.module]", PERF_RECORD_MISC_CPUMODE_UNKNOWN, true);
	M("[test.module]", PERF_RECORD_MISC_KERNEL, true);
	M("[test.module]", PERF_RECORD_MISC_USER, false);

	/* path     alloc_name  kmod   comp   name    */
	T("[vdso]", true      , false, false, "[vdso]");
	T("[vdso]", false     , false, false, शून्य    );
	T("[vdso]", true      , false, false, "[vdso]");
	T("[vdso]", false     , false, false, शून्य    );
	M("[vdso]", PERF_RECORD_MISC_CPUMODE_UNKNOWN, false);
	M("[vdso]", PERF_RECORD_MISC_KERNEL, false);
	M("[vdso]", PERF_RECORD_MISC_USER, false);

	T("[vdso32]", true      , false, false, "[vdso32]");
	T("[vdso32]", false     , false, false, शून्य      );
	T("[vdso32]", true      , false, false, "[vdso32]");
	T("[vdso32]", false     , false, false, शून्य      );
	M("[vdso32]", PERF_RECORD_MISC_CPUMODE_UNKNOWN, false);
	M("[vdso32]", PERF_RECORD_MISC_KERNEL, false);
	M("[vdso32]", PERF_RECORD_MISC_USER, false);

	T("[vdsox32]", true      , false, false, "[vdsox32]");
	T("[vdsox32]", false     , false, false, शून्य       );
	T("[vdsox32]", true      , false, false, "[vdsox32]");
	T("[vdsox32]", false     , false, false, शून्य       );
	M("[vdsox32]", PERF_RECORD_MISC_CPUMODE_UNKNOWN, false);
	M("[vdsox32]", PERF_RECORD_MISC_KERNEL, false);
	M("[vdsox32]", PERF_RECORD_MISC_USER, false);

	/* path         alloc_name  kmod   comp   name        */
	T("[vsyscall]", true      , false, false, "[vsyscall]");
	T("[vsyscall]", false     , false, false, शून्य        );
	T("[vsyscall]", true      , false, false, "[vsyscall]");
	T("[vsyscall]", false     , false, false, शून्य        );
	M("[vsyscall]", PERF_RECORD_MISC_CPUMODE_UNKNOWN, false);
	M("[vsyscall]", PERF_RECORD_MISC_KERNEL, false);
	M("[vsyscall]", PERF_RECORD_MISC_USER, false);

	/* path                alloc_name  kmod   comp   name      */
	T("[kernel.kallsyms]", true      , false, false, "[kernel.kallsyms]");
	T("[kernel.kallsyms]", false     , false, false, शून्य               );
	T("[kernel.kallsyms]", true      , false, false, "[kernel.kallsyms]");
	T("[kernel.kallsyms]", false     , false, false, शून्य               );
	M("[kernel.kallsyms]", PERF_RECORD_MISC_CPUMODE_UNKNOWN, false);
	M("[kernel.kallsyms]", PERF_RECORD_MISC_KERNEL, false);
	M("[kernel.kallsyms]", PERF_RECORD_MISC_USER, false);

	वापस 0;
पूर्ण
