<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <linux/compiler.h>

#समावेश "debug.h"
#समावेश "tests/tests.h"
#समावेश "util/find-map.c"

#घोषणा VECTORS__MAP_NAME "[vectors]"

पूर्णांक test__vectors_page(काष्ठा test *test __maybe_unused,
		       पूर्णांक subtest __maybe_unused)
अणु
	व्योम *start, *end;

	अगर (find_map(&start, &end, VECTORS__MAP_NAME)) अणु
		pr_err("%s not found, is CONFIG_KUSER_HELPERS enabled?\n",
		       VECTORS__MAP_NAME);
		वापस TEST_FAIL;
	पूर्ण

	वापस TEST_OK;
पूर्ण
