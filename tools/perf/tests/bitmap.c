<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <perf/cpumap.h>
#समावेश <पूर्णांकernal/cpumap.h>
#समावेश "tests.h"
#समावेश "debug.h"

#घोषणा NBITS 100

अटल अचिन्हित दीर्घ *get_biपंचांगap(स्थिर अक्षर *str, पूर्णांक nbits)
अणु
	काष्ठा perf_cpu_map *map = perf_cpu_map__new(str);
	अचिन्हित दीर्घ *bm = शून्य;
	पूर्णांक i;

	bm = biपंचांगap_alloc(nbits);

	अगर (map && bm) अणु
		क्रम (i = 0; i < map->nr; i++)
			set_bit(map->map[i], bm);
	पूर्ण

	अगर (map)
		perf_cpu_map__put(map);
	वापस bm;
पूर्ण

अटल पूर्णांक test_biपंचांगap(स्थिर अक्षर *str)
अणु
	अचिन्हित दीर्घ *bm = get_biपंचांगap(str, NBITS);
	अक्षर buf[100];
	पूर्णांक ret;

	biपंचांगap_scnम_लिखो(bm, NBITS, buf, माप(buf));
	pr_debug("bitmap: %s\n", buf);

	ret = !म_भेद(buf, str);
	मुक्त(bm);
	वापस ret;
पूर्ण

पूर्णांक test__biपंचांगap_prपूर्णांक(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	TEST_ASSERT_VAL("failed to convert map", test_biपंचांगap("1"));
	TEST_ASSERT_VAL("failed to convert map", test_biपंचांगap("1,5"));
	TEST_ASSERT_VAL("failed to convert map", test_biपंचांगap("1,3,5,7,9,11,13,15,17,19,21-40"));
	TEST_ASSERT_VAL("failed to convert map", test_biपंचांगap("2-5"));
	TEST_ASSERT_VAL("failed to convert map", test_biपंचांगap("1,3-6,8-10,24,35-37"));
	TEST_ASSERT_VAL("failed to convert map", test_biपंचांगap("1,3-6,8-10,24,35-37"));
	TEST_ASSERT_VAL("failed to convert map", test_biपंचांगap("1-10,12-20,22-30,32-40"));
	वापस 0;
पूर्ण
