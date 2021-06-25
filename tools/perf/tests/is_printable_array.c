<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "print_binary.h"

पूर्णांक test__is_prपूर्णांकable_array(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	अक्षर buf1[] = अणु 'k', 'r', 4, 'v', 'a', 0 पूर्ण;
	अक्षर buf2[] = अणु 'k', 'r', 'a', 'v', 4, 0 पूर्ण;
	काष्ठा अणु
		अक्षर		*buf;
		अचिन्हित पूर्णांक	 len;
		पूर्णांक		 ret;
	पूर्ण t[] = अणु
		अणु (अक्षर *) "krava",	माप("krava"),	1 पूर्ण,
		अणु (अक्षर *) "krava",	माप("krava") - 1,	0 पूर्ण,
		अणु (अक्षर *) "",		माप(""),		1 पूर्ण,
		अणु (अक्षर *) "",		0,			0 पूर्ण,
		अणु शून्य,			0,			0 पूर्ण,
		अणु buf1,			माप(buf1),		0 पूर्ण,
		अणु buf2,			माप(buf2),		0 पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(t); i++) अणु
		पूर्णांक ret;

		ret = is_prपूर्णांकable_array((अक्षर *) t[i].buf, t[i].len);
		अगर (ret != t[i].ret) अणु
			pr_err("failed: test %u\n", i);
			वापस TEST_FAIL;
		पूर्ण
	पूर्ण

	वापस TEST_OK;
पूर्ण
