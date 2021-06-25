<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

अटल __init पूर्णांक स_रखो16_selftest(व्योम)
अणु
	अचिन्हित i, j, k;
	u16 v, *p;

	p = kदो_स्मृति(256 * 2 * 2, GFP_KERNEL);
	अगर (!p)
		वापस -1;

	क्रम (i = 0; i < 256; i++) अणु
		क्रम (j = 0; j < 256; j++) अणु
			स_रखो(p, 0xa1, 256 * 2 * माप(v));
			स_रखो16(p + i, 0xb1b2, j);
			क्रम (k = 0; k < 512; k++) अणु
				v = p[k];
				अगर (k < i) अणु
					अगर (v != 0xa1a1)
						जाओ fail;
				पूर्ण अन्यथा अगर (k < i + j) अणु
					अगर (v != 0xb1b2)
						जाओ fail;
				पूर्ण अन्यथा अणु
					अगर (v != 0xa1a1)
						जाओ fail;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

fail:
	kमुक्त(p);
	अगर (i < 256)
		वापस (i << 24) | (j << 16) | k | 0x8000;
	वापस 0;
पूर्ण

अटल __init पूर्णांक स_रखो32_selftest(व्योम)
अणु
	अचिन्हित i, j, k;
	u32 v, *p;

	p = kदो_स्मृति(256 * 2 * 4, GFP_KERNEL);
	अगर (!p)
		वापस -1;

	क्रम (i = 0; i < 256; i++) अणु
		क्रम (j = 0; j < 256; j++) अणु
			स_रखो(p, 0xa1, 256 * 2 * माप(v));
			स_रखो32(p + i, 0xb1b2b3b4, j);
			क्रम (k = 0; k < 512; k++) अणु
				v = p[k];
				अगर (k < i) अणु
					अगर (v != 0xa1a1a1a1)
						जाओ fail;
				पूर्ण अन्यथा अगर (k < i + j) अणु
					अगर (v != 0xb1b2b3b4)
						जाओ fail;
				पूर्ण अन्यथा अणु
					अगर (v != 0xa1a1a1a1)
						जाओ fail;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

fail:
	kमुक्त(p);
	अगर (i < 256)
		वापस (i << 24) | (j << 16) | k | 0x8000;
	वापस 0;
पूर्ण

अटल __init पूर्णांक स_रखो64_selftest(व्योम)
अणु
	अचिन्हित i, j, k;
	u64 v, *p;

	p = kदो_स्मृति(256 * 2 * 8, GFP_KERNEL);
	अगर (!p)
		वापस -1;

	क्रम (i = 0; i < 256; i++) अणु
		क्रम (j = 0; j < 256; j++) अणु
			स_रखो(p, 0xa1, 256 * 2 * माप(v));
			स_रखो64(p + i, 0xb1b2b3b4b5b6b7b8ULL, j);
			क्रम (k = 0; k < 512; k++) अणु
				v = p[k];
				अगर (k < i) अणु
					अगर (v != 0xa1a1a1a1a1a1a1a1ULL)
						जाओ fail;
				पूर्ण अन्यथा अगर (k < i + j) अणु
					अगर (v != 0xb1b2b3b4b5b6b7b8ULL)
						जाओ fail;
				पूर्ण अन्यथा अणु
					अगर (v != 0xa1a1a1a1a1a1a1a1ULL)
						जाओ fail;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

fail:
	kमुक्त(p);
	अगर (i < 256)
		वापस (i << 24) | (j << 16) | k | 0x8000;
	वापस 0;
पूर्ण

अटल __init पूर्णांक म_अक्षर_selftest(व्योम)
अणु
	स्थिर अक्षर *test_string = "abcdefghijkl";
	स्थिर अक्षर *empty_string = "";
	अक्षर *result;
	पूर्णांक i;

	क्रम (i = 0; i < म_माप(test_string) + 1; i++) अणु
		result = म_अक्षर(test_string, test_string[i]);
		अगर (result - test_string != i)
			वापस i + 'a';
	पूर्ण

	result = म_अक्षर(empty_string, '\0');
	अगर (result != empty_string)
		वापस 0x101;

	result = म_अक्षर(empty_string, 'a');
	अगर (result)
		वापस 0x102;

	result = म_अक्षर(test_string, 'z');
	अगर (result)
		वापस 0x103;

	वापस 0;
पूर्ण

अटल __init पूर्णांक strnchr_selftest(व्योम)
अणु
	स्थिर अक्षर *test_string = "abcdefghijkl";
	स्थिर अक्षर *empty_string = "";
	अक्षर *result;
	पूर्णांक i, j;

	क्रम (i = 0; i < म_माप(test_string) + 1; i++) अणु
		क्रम (j = 0; j < म_माप(test_string) + 2; j++) अणु
			result = strnchr(test_string, j, test_string[i]);
			अगर (j <= i) अणु
				अगर (!result)
					जारी;
				वापस ((i + 'a') << 8) | j;
			पूर्ण
			अगर (result - test_string != i)
				वापस ((i + 'a') << 8) | j;
		पूर्ण
	पूर्ण

	result = strnchr(empty_string, 0, '\0');
	अगर (result)
		वापस 0x10001;

	result = strnchr(empty_string, 1, '\0');
	अगर (result != empty_string)
		वापस 0x10002;

	result = strnchr(empty_string, 1, 'a');
	अगर (result)
		वापस 0x10003;

	result = strnchr(शून्य, 0, '\0');
	अगर (result)
		वापस 0x10004;

	वापस 0;
पूर्ण

अटल __init पूर्णांक string_selftest_init(व्योम)
अणु
	पूर्णांक test, subtest;

	test = 1;
	subtest = स_रखो16_selftest();
	अगर (subtest)
		जाओ fail;

	test = 2;
	subtest = स_रखो32_selftest();
	अगर (subtest)
		जाओ fail;

	test = 3;
	subtest = स_रखो64_selftest();
	अगर (subtest)
		जाओ fail;

	test = 4;
	subtest = म_अक्षर_selftest();
	अगर (subtest)
		जाओ fail;

	test = 5;
	subtest = strnchr_selftest();
	अगर (subtest)
		जाओ fail;

	pr_info("String selftests succeeded\n");
	वापस 0;
fail:
	pr_crit("String selftest failure %d.%08x\n", test, subtest);
	वापस 0;
पूर्ण

module_init(string_selftest_init);
MODULE_LICENSE("GPL v2");
