<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "tests.h"
#समावेश "c++/clang-c.h"
#समावेश <linux/kernel.h>

अटल काष्ठा अणु
	पूर्णांक (*func)(व्योम);
	स्थिर अक्षर *desc;
पूर्ण clang_testहाल_table[] = अणु
#अगर_घोषित HAVE_LIBCLANGLLVM_SUPPORT
	अणु
		.func = test__clang_to_IR,
		.desc = "builtin clang compile C source to IR",
	पूर्ण,
	अणु
		.func = test__clang_to_obj,
		.desc = "builtin clang compile C source to ELF object",
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

पूर्णांक test__clang_subtest_get_nr(व्योम)
अणु
	वापस (पूर्णांक)ARRAY_SIZE(clang_testहाल_table);
पूर्ण

स्थिर अक्षर *test__clang_subtest_get_desc(पूर्णांक i)
अणु
	अगर (i < 0 || i >= (पूर्णांक)ARRAY_SIZE(clang_testहाल_table))
		वापस शून्य;
	वापस clang_testहाल_table[i].desc;
पूर्ण

#अगर_अघोषित HAVE_LIBCLANGLLVM_SUPPORT
पूर्णांक test__clang(काष्ठा test *test __maybe_unused, पूर्णांक i __maybe_unused)
अणु
	वापस TEST_SKIP;
पूर्ण
#अन्यथा
पूर्णांक test__clang(काष्ठा test *test __maybe_unused, पूर्णांक i)
अणु
	अगर (i < 0 || i >= (पूर्णांक)ARRAY_SIZE(clang_testहाल_table))
		वापस TEST_FAIL;
	वापस clang_testहाल_table[i].func();
पूर्ण
#पूर्ण_अगर
