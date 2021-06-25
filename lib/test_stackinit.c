<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test हालs क्रम compiler-based stack variable zeroing via future
 * compiler flags or CONFIG_GCC_PLUGIN_STRUCTLEAK*.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>

/* Exfiltration buffer. */
#घोषणा MAX_VAR_SIZE	128
अटल u8 check_buf[MAX_VAR_SIZE];

/* Character array to trigger stack protector in all functions. */
#घोषणा VAR_BUFFER	 32

/* Volatile mask to convince compiler to copy memory with 0xff. */
अटल अस्थिर u8 क्रमced_mask = 0xff;

/* Location and size tracking to validate fill and test are colocated. */
अटल व्योम *fill_start, *target_start;
अटल माप_प्रकार fill_size, target_size;

अटल bool range_contains(अक्षर *haystack_start, माप_प्रकार haystack_size,
			   अक्षर *needle_start, माप_प्रकार needle_size)
अणु
	अगर (needle_start >= haystack_start &&
	    needle_start + needle_size <= haystack_start + haystack_size)
		वापस true;
	वापस false;
पूर्ण

#घोषणा DO_NOTHING_TYPE_SCALAR(var_type)	var_type
#घोषणा DO_NOTHING_TYPE_STRING(var_type)	व्योम
#घोषणा DO_NOTHING_TYPE_STRUCT(var_type)	व्योम

#घोषणा DO_NOTHING_RETURN_SCALAR(ptr)		*(ptr)
#घोषणा DO_NOTHING_RETURN_STRING(ptr)		/**/
#घोषणा DO_NOTHING_RETURN_STRUCT(ptr)		/**/

#घोषणा DO_NOTHING_CALL_SCALAR(var, name)			\
		(var) = करो_nothing_ ## name(&(var))
#घोषणा DO_NOTHING_CALL_STRING(var, name)			\
		करो_nothing_ ## name(var)
#घोषणा DO_NOTHING_CALL_STRUCT(var, name)			\
		करो_nothing_ ## name(&(var))

#घोषणा FETCH_ARG_SCALAR(var)		&var
#घोषणा FETCH_ARG_STRING(var)		var
#घोषणा FETCH_ARG_STRUCT(var)		&var

#घोषणा FILL_SIZE_STRING		16

#घोषणा INIT_CLONE_SCALAR		/**/
#घोषणा INIT_CLONE_STRING		[FILL_SIZE_STRING]
#घोषणा INIT_CLONE_STRUCT		/**/

#घोषणा INIT_SCALAR_none		/**/
#घोषणा INIT_SCALAR_zero		= 0

#घोषणा INIT_STRING_none		[FILL_SIZE_STRING] /**/
#घोषणा INIT_STRING_zero		[FILL_SIZE_STRING] = अणु पूर्ण

#घोषणा INIT_STRUCT_none		/**/
#घोषणा INIT_STRUCT_zero		= अणु पूर्ण
#घोषणा INIT_STRUCT_अटल_partial	= अणु .two = 0, पूर्ण
#घोषणा INIT_STRUCT_अटल_all		= अणु .one = arg->one,		\
					    .two = arg->two,		\
					    .three = arg->three,	\
					    .four = arg->four,		\
					पूर्ण
#घोषणा INIT_STRUCT_dynamic_partial	= अणु .two = arg->two, पूर्ण
#घोषणा INIT_STRUCT_dynamic_all		= अणु .one = arg->one,		\
					    .two = arg->two,		\
					    .three = arg->three,	\
					    .four = arg->four,		\
					पूर्ण
#घोषणा INIT_STRUCT_runसमय_partial	;				\
					var.two = 0
#घोषणा INIT_STRUCT_runसमय_all		;				\
					var.one = 0;			\
					var.two = 0;			\
					var.three = 0;			\
					स_रखो(&var.four, 0,		\
					       माप(var.four))

/*
 * @name: unique string name क्रम the test
 * @var_type: type to be tested क्रम zeroing initialization
 * @which: is this a SCALAR, STRING, or STRUCT type?
 * @init_level: what kind of initialization is perक्रमmed
 * @xfail: is this test expected to fail?
 */
#घोषणा DEFINE_TEST_DRIVER(name, var_type, which, xfail)	\
/* Returns 0 on success, 1 on failure. */			\
अटल noअंतरभूत __init पूर्णांक test_ ## name (व्योम)			\
अणु								\
	var_type zero INIT_CLONE_ ## which;			\
	पूर्णांक ignored;						\
	u8 sum = 0, i;						\
								\
	/* Notice when a new test is larger than expected. */	\
	BUILD_BUG_ON(माप(zero) > MAX_VAR_SIZE);		\
								\
	/* Fill clone type with zero क्रम per-field init. */	\
	स_रखो(&zero, 0x00, माप(zero));			\
	/* Clear entire check buffer क्रम 0xFF overlap test. */	\
	स_रखो(check_buf, 0x00, माप(check_buf));		\
	/* Fill stack with 0xFF. */				\
	ignored = leaf_ ##name((अचिन्हित दीर्घ)&ignored, 1,	\
				FETCH_ARG_ ## which(zero));	\
	/* Verअगरy all bytes overwritten with 0xFF. */		\
	क्रम (sum = 0, i = 0; i < target_size; i++)		\
		sum += (check_buf[i] != 0xFF);			\
	अगर (sum) अणु						\
		pr_err(#name ": leaf fill was not 0xFF!?\n");	\
		वापस 1;					\
	पूर्ण							\
	/* Clear entire check buffer क्रम later bit tests. */	\
	स_रखो(check_buf, 0x00, माप(check_buf));		\
	/* Extract stack-defined variable contents. */		\
	ignored = leaf_ ##name((अचिन्हित दीर्घ)&ignored, 0,	\
				FETCH_ARG_ ## which(zero));	\
								\
	/* Validate that compiler lined up fill and target. */	\
	अगर (!range_contains(fill_start, fill_size,		\
			    target_start, target_size)) अणु	\
		pr_err(#name ": stack fill missed target!?\n");	\
		pr_err(#name ": fill %zu wide\n", fill_size);	\
		pr_err(#name ": target offset by %d\n",	\
			(पूर्णांक)((sमाप_प्रकार)(uपूर्णांकptr_t)fill_start -	\
			(sमाप_प्रकार)(uपूर्णांकptr_t)target_start));	\
		वापस 1;					\
	पूर्ण							\
								\
	/* Look क्रम any bytes still 0xFF in check region. */	\
	क्रम (sum = 0, i = 0; i < target_size; i++)		\
		sum += (check_buf[i] == 0xFF);			\
								\
	अगर (sum == 0) अणु						\
		pr_info(#name " ok\n");				\
		वापस 0;					\
	पूर्ण अन्यथा अणु						\
		pr_warn(#name " %sFAIL (uninit bytes: %d)\n",	\
			(xfail) ? "X" : "", sum);		\
		वापस (xfail) ? 0 : 1;				\
	पूर्ण							\
पूर्ण
#घोषणा DEFINE_TEST(name, var_type, which, init_level)		\
/* no-op to क्रमce compiler पूर्णांकo ignoring "uninitialized" vars */\
अटल noअंतरभूत __init DO_NOTHING_TYPE_ ## which(var_type)	\
करो_nothing_ ## name(var_type *ptr)				\
अणु								\
	/* Will always be true, but compiler करोesn't know. */	\
	अगर ((अचिन्हित दीर्घ)ptr > 0x2)				\
		वापस DO_NOTHING_RETURN_ ## which(ptr);	\
	अन्यथा							\
		वापस DO_NOTHING_RETURN_ ## which(ptr + 1);	\
पूर्ण								\
अटल noअंतरभूत __init पूर्णांक leaf_ ## name(अचिन्हित दीर्घ sp,	\
					 bool fill,		\
					 var_type *arg)		\
अणु								\
	अक्षर buf[VAR_BUFFER];					\
	var_type var INIT_ ## which ## _ ## init_level;		\
								\
	target_start = &var;					\
	target_size = माप(var);				\
	/*							\
	 * Keep this buffer around to make sure we've got a	\
	 * stack frame of SOME kind...				\
	 */							\
	स_रखो(buf, (अक्षर)(sp & 0xff), माप(buf));		\
	/* Fill variable with 0xFF. */				\
	अगर (fill) अणु						\
		fill_start = &var;				\
		fill_size = माप(var);			\
		स_रखो(fill_start,				\
		       (अक्षर)((sp & 0xff) | क्रमced_mask),	\
		       fill_size);				\
	पूर्ण							\
								\
	/* Silence "never initialized" warnings. */		\
	DO_NOTHING_CALL_ ## which(var, name);			\
								\
	/* Exfiltrate "var". */					\
	स_नकल(check_buf, target_start, target_size);		\
								\
	वापस (पूर्णांक)buf[0] | (पूर्णांक)buf[माप(buf) - 1];		\
पूर्ण								\
DEFINE_TEST_DRIVER(name, var_type, which, 0)

/* Structure with no padding. */
काष्ठा test_packed अणु
	अचिन्हित दीर्घ one;
	अचिन्हित दीर्घ two;
	अचिन्हित दीर्घ three;
	अचिन्हित दीर्घ four;
पूर्ण;

/* Simple काष्ठाure with padding likely to be covered by compiler. */
काष्ठा test_small_hole अणु
	माप_प्रकार one;
	अक्षर two;
	/* 3 byte padding hole here. */
	पूर्णांक three;
	अचिन्हित दीर्घ four;
पूर्ण;

/* Try to trigger unhandled padding in a काष्ठाure. */
काष्ठा test_aligned अणु
	u32 पूर्णांकernal1;
	u64 पूर्णांकernal2;
पूर्ण __aligned(64);

काष्ठा test_big_hole अणु
	u8 one;
	u8 two;
	u8 three;
	/* 61 byte padding hole here. */
	काष्ठा test_aligned four;
पूर्ण __aligned(64);

काष्ठा test_trailing_hole अणु
	अक्षर *one;
	अक्षर *two;
	अक्षर *three;
	अक्षर four;
	/* "sizeof(unsigned long) - 1" byte padding hole here. */
पूर्ण;

/* Test अगर STRUCTLEAK is clearing काष्ठाs with __user fields. */
काष्ठा test_user अणु
	u8 one;
	अचिन्हित दीर्घ two;
	अक्षर __user *three;
	अचिन्हित दीर्घ four;
पूर्ण;

#घोषणा DEFINE_SCALAR_TEST(name, init)				\
		DEFINE_TEST(name ## _ ## init, name, SCALAR, init)

#घोषणा DEFINE_SCALAR_TESTS(init)				\
		DEFINE_SCALAR_TEST(u8, init);			\
		DEFINE_SCALAR_TEST(u16, init);			\
		DEFINE_SCALAR_TEST(u32, init);			\
		DEFINE_SCALAR_TEST(u64, init);			\
		DEFINE_TEST(अक्षर_array_ ## init, अचिन्हित अक्षर, STRING, init)

#घोषणा DEFINE_STRUCT_TEST(name, init)				\
		DEFINE_TEST(name ## _ ## init,			\
			    काष्ठा test_ ## name, STRUCT, init)

#घोषणा DEFINE_STRUCT_TESTS(init)				\
		DEFINE_STRUCT_TEST(small_hole, init);		\
		DEFINE_STRUCT_TEST(big_hole, init);		\
		DEFINE_STRUCT_TEST(trailing_hole, init);	\
		DEFINE_STRUCT_TEST(packed, init)

/* These should be fully initialized all the समय! */
DEFINE_SCALAR_TESTS(zero);
DEFINE_STRUCT_TESTS(zero);
/* Static initialization: padding may be left uninitialized. */
DEFINE_STRUCT_TESTS(अटल_partial);
DEFINE_STRUCT_TESTS(अटल_all);
/* Dynamic initialization: padding may be left uninitialized. */
DEFINE_STRUCT_TESTS(dynamic_partial);
DEFINE_STRUCT_TESTS(dynamic_all);
/* Runसमय initialization: padding may be left uninitialized. */
DEFINE_STRUCT_TESTS(runसमय_partial);
DEFINE_STRUCT_TESTS(runसमय_all);
/* No initialization without compiler instrumentation. */
DEFINE_SCALAR_TESTS(none);
DEFINE_STRUCT_TESTS(none);
DEFINE_TEST(user, काष्ठा test_user, STRUCT, none);

/*
 * Check two uses through a variable declaration outside either path,
 * which was noticed as a special हाल in porting earlier stack init
 * compiler logic.
 */
अटल पूर्णांक noअंतरभूत __leaf_चयन_none(पूर्णांक path, bool fill)
अणु
	चयन (path) अणु
		uपूर्णांक64_t var;

	हाल 1:
		target_start = &var;
		target_size = माप(var);
		अगर (fill) अणु
			fill_start = &var;
			fill_size = माप(var);

			स_रखो(fill_start, क्रमced_mask | 0x55, fill_size);
		पूर्ण
		स_नकल(check_buf, target_start, target_size);
		अवरोध;
	हाल 2:
		target_start = &var;
		target_size = माप(var);
		अगर (fill) अणु
			fill_start = &var;
			fill_size = माप(var);

			स_रखो(fill_start, क्रमced_mask | 0xaa, fill_size);
		पूर्ण
		स_नकल(check_buf, target_start, target_size);
		अवरोध;
	शेष:
		var = 5;
		वापस var & क्रमced_mask;
	पूर्ण
	वापस 0;
पूर्ण

अटल noअंतरभूत __init पूर्णांक leaf_चयन_1_none(अचिन्हित दीर्घ sp, bool fill,
					      uपूर्णांक64_t *arg)
अणु
	वापस __leaf_चयन_none(1, fill);
पूर्ण

अटल noअंतरभूत __init पूर्णांक leaf_चयन_2_none(अचिन्हित दीर्घ sp, bool fill,
					      uपूर्णांक64_t *arg)
अणु
	वापस __leaf_चयन_none(2, fill);
पूर्ण

/*
 * These are expected to fail क्रम most configurations because neither
 * GCC nor Clang have a way to perक्रमm initialization of variables in
 * non-code areas (i.e. in a चयन statement beक्रमe the first "case").
 * https://bugs.llvm.org/show_bug.cgi?id=44916
 */
DEFINE_TEST_DRIVER(चयन_1_none, uपूर्णांक64_t, SCALAR, 1);
DEFINE_TEST_DRIVER(चयन_2_none, uपूर्णांक64_t, SCALAR, 1);

अटल पूर्णांक __init test_stackinit_init(व्योम)
अणु
	अचिन्हित पूर्णांक failures = 0;

#घोषणा test_scalars(init)	करो अणु				\
		failures += test_u8_ ## init ();		\
		failures += test_u16_ ## init ();		\
		failures += test_u32_ ## init ();		\
		failures += test_u64_ ## init ();		\
		failures += test_अक्षर_array_ ## init ();	\
	पूर्ण जबतक (0)

#घोषणा test_काष्ठाs(init)	करो अणु				\
		failures += test_small_hole_ ## init ();	\
		failures += test_big_hole_ ## init ();		\
		failures += test_trailing_hole_ ## init ();	\
		failures += test_packed_ ## init ();		\
	पूर्ण जबतक (0)

	/* These are explicitly initialized and should always pass. */
	test_scalars(zero);
	test_काष्ठाs(zero);
	/* Padding here appears to be accidentally always initialized? */
	test_काष्ठाs(dynamic_partial);
	/* Padding initialization depends on compiler behaviors. */
	test_काष्ठाs(अटल_partial);
	test_काष्ठाs(अटल_all);
	test_काष्ठाs(dynamic_all);
	test_काष्ठाs(runसमय_partial);
	test_काष्ठाs(runसमय_all);

	/* STRUCTLEAK_BYREF_ALL should cover everything from here करोwn. */
	test_scalars(none);
	failures += test_चयन_1_none();
	failures += test_चयन_2_none();

	/* STRUCTLEAK_BYREF should cover from here करोwn. */
	test_काष्ठाs(none);

	/* STRUCTLEAK will only cover this. */
	failures += test_user();

	अगर (failures == 0)
		pr_info("all tests passed!\n");
	अन्यथा
		pr_err("failures: %u\n", failures);

	वापस failures ? -EINVAL : 0;
पूर्ण
module_init(test_stackinit_init);

अटल व्योम __निकास test_stackinit_निकास(व्योम)
अणु पूर्ण
module_निकास(test_stackinit_निकास);

MODULE_LICENSE("GPL");
