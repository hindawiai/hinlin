<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/sort.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

/* a simple boot-समय regression test */

#घोषणा TEST_LEN 1000

अटल पूर्णांक __init cmpपूर्णांक(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस *(पूर्णांक *)a - *(पूर्णांक *)b;
पूर्ण

अटल पूर्णांक __init test_sort_init(व्योम)
अणु
	पूर्णांक *a, i, r = 1, err = -ENOMEM;

	a = kदो_स्मृति_array(TEST_LEN, माप(*a), GFP_KERNEL);
	अगर (!a)
		वापस err;

	क्रम (i = 0; i < TEST_LEN; i++) अणु
		r = (r * 725861) % 6599;
		a[i] = r;
	पूर्ण

	sort(a, TEST_LEN, माप(*a), cmpपूर्णांक, शून्य);

	err = -EINVAL;
	क्रम (i = 0; i < TEST_LEN-1; i++)
		अगर (a[i] > a[i+1]) अणु
			pr_err("test has failed\n");
			जाओ निकास;
		पूर्ण
	err = 0;
	pr_info("test passed\n");
निकास:
	kमुक्त(a);
	वापस err;
पूर्ण

अटल व्योम __निकास test_sort_निकास(व्योम)
अणु
पूर्ण

module_init(test_sort_init);
module_निकास(test_sort_निकास);

MODULE_LICENSE("GPL");
