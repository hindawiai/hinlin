<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश "tests.h"
#समावेश "session.h"
#समावेश "debug.h"
#समावेश "demangle-ocaml.h"

पूर्णांक test__demangle_ocaml(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक ret = TEST_OK;
	अक्षर *buf = शून्य;
	माप_प्रकार i;

	काष्ठा अणु
		स्थिर अक्षर *mangled, *demangled;
	पूर्ण test_हालs[] = अणु
		अणु "main",
		  शून्य पूर्ण,
		अणु "camlStdlib__array__map_154",
		  "Stdlib.array.map_154" पूर्ण,
		अणु "camlStdlib__anon_fn$5bstdlib$2eml$3a334$2c0$2d$2d54$5d_1453",
		  "Stdlib.anon_fn[stdlib.ml:334,0--54]_1453" पूर्ण,
		अणु "camlStdlib__bytes__$2b$2b_2205",
		  "Stdlib.bytes.++_2205" पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(test_हालs); i++) अणु
		buf = ocaml_demangle_sym(test_हालs[i].mangled);
		अगर ((buf == शून्य && test_हालs[i].demangled != शून्य)
				|| (buf != शून्य && test_हालs[i].demangled == शून्य)
				|| (buf != शून्य && म_भेद(buf, test_हालs[i].demangled))) अणु
			pr_debug("FAILED: %s: %s != %s\n", test_हालs[i].mangled,
				 buf == शून्य ? "(null)" : buf,
				 test_हालs[i].demangled == शून्य ? "(null)" : test_हालs[i].demangled);
			ret = TEST_FAIL;
		पूर्ण
		मुक्त(buf);
	पूर्ण

	वापस ret;
पूर्ण
