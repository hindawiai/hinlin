<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

प्रकार व्योम(*test_ubsan_fp)(व्योम);

#घोषणा UBSAN_TEST(config, ...)	करो अणु					\
		pr_info("%s " __VA_ARGS__ "%s(%s=%s)\n", __func__,	\
			माप(" " __VA_ARGS__) > 2 ? " " : "",		\
			#config, IS_ENABLED(config) ? "y" : "n");	\
	पूर्ण जबतक (0)

अटल व्योम test_ubsan_भागrem_overflow(व्योम)
अणु
	अस्थिर पूर्णांक val = 16;
	अस्थिर पूर्णांक val2 = 0;

	UBSAN_TEST(CONFIG_UBSAN_DIV_ZERO);
	val /= val2;
पूर्ण

अटल व्योम test_ubsan_shअगरt_out_of_bounds(व्योम)
अणु
	अस्थिर पूर्णांक neg = -1, wrap = 4;
	पूर्णांक val1 = 10;
	पूर्णांक val2 = पूर्णांक_उच्च;

	UBSAN_TEST(CONFIG_UBSAN_SHIFT, "negative exponent");
	val1 <<= neg;

	UBSAN_TEST(CONFIG_UBSAN_SHIFT, "left overflow");
	val2 <<= wrap;
पूर्ण

अटल व्योम test_ubsan_out_of_bounds(व्योम)
अणु
	अस्थिर पूर्णांक i = 4, j = 5, k = -1;
	अस्थिर अक्षर above[4] = अणु पूर्ण; /* Protect surrounding memory. */
	अस्थिर पूर्णांक arr[4];
	अस्थिर अक्षर below[4] = अणु पूर्ण; /* Protect surrounding memory. */

	above[0] = below[0];

	UBSAN_TEST(CONFIG_UBSAN_BOUNDS, "above");
	arr[j] = i;

	UBSAN_TEST(CONFIG_UBSAN_BOUNDS, "below");
	arr[k] = i;
पूर्ण

क्रमागत ubsan_test_क्रमागत अणु
	UBSAN_TEST_ZERO = 0,
	UBSAN_TEST_ONE,
	UBSAN_TEST_MAX,
पूर्ण;

अटल व्योम test_ubsan_load_invalid_value(व्योम)
अणु
	अस्थिर अक्षर *dst, *src;
	bool val, val2, *ptr;
	क्रमागत ubsan_test_क्रमागत eval, eval2, *eptr;
	अचिन्हित अक्षर c = 0xff;

	UBSAN_TEST(CONFIG_UBSAN_BOOL, "bool");
	dst = (अक्षर *)&val;
	src = &c;
	*dst = *src;

	ptr = &val2;
	val2 = val;

	UBSAN_TEST(CONFIG_UBSAN_ENUM, "enum");
	dst = (अक्षर *)&eval;
	src = &c;
	*dst = *src;

	eptr = &eval2;
	eval2 = eval;
पूर्ण

अटल व्योम test_ubsan_null_ptr_deref(व्योम)
अणु
	अस्थिर पूर्णांक *ptr = शून्य;
	पूर्णांक val;

	UBSAN_TEST(CONFIG_UBSAN_OBJECT_SIZE);
	val = *ptr;
पूर्ण

अटल व्योम test_ubsan_misaligned_access(व्योम)
अणु
	अस्थिर अक्षर arr[5] __aligned(4) = अणु1, 2, 3, 4, 5पूर्ण;
	अस्थिर पूर्णांक *ptr, val = 6;

	UBSAN_TEST(CONFIG_UBSAN_ALIGNMENT);
	ptr = (पूर्णांक *)(arr + 1);
	*ptr = val;
पूर्ण

अटल व्योम test_ubsan_object_size_mismatch(व्योम)
अणु
	/* "((aligned(8)))" helps this not पूर्णांकo be misaligned क्रम ptr-access. */
	अस्थिर पूर्णांक val __aligned(8) = 4;
	अस्थिर दीर्घ दीर्घ *ptr, val2;

	UBSAN_TEST(CONFIG_UBSAN_OBJECT_SIZE);
	ptr = (दीर्घ दीर्घ *)&val;
	val2 = *ptr;
पूर्ण

अटल स्थिर test_ubsan_fp test_ubsan_array[] = अणु
	test_ubsan_shअगरt_out_of_bounds,
	test_ubsan_out_of_bounds,
	test_ubsan_load_invalid_value,
	test_ubsan_misaligned_access,
	test_ubsan_object_size_mismatch,
पूर्ण;

/* Excluded because they Oops the module. */
अटल स्थिर test_ubsan_fp skip_ubsan_array[] = अणु
	test_ubsan_भागrem_overflow,
	test_ubsan_null_ptr_deref,
पूर्ण;

अटल पूर्णांक __init test_ubsan_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(test_ubsan_array); i++)
		test_ubsan_array[i]();

	वापस 0;
पूर्ण
module_init(test_ubsan_init);

अटल व्योम __निकास test_ubsan_निकास(व्योम)
अणु
	/* करो nothing */
पूर्ण
module_निकास(test_ubsan_निकास);

MODULE_AUTHOR("Jinbum Park <jinb.park7@gmail.com>");
MODULE_LICENSE("GPL v2");
