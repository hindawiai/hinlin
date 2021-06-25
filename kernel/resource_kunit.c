<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Test हालs क्रम API provided by resource.c and ioport.h
 */

#समावेश <kunit/test.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

#घोषणा R0_START	0x0000
#घोषणा R0_END		0xffff
#घोषणा R1_START	0x1234
#घोषणा R1_END		0x2345
#घोषणा R2_START	0x4567
#घोषणा R2_END		0x5678
#घोषणा R3_START	0x6789
#घोषणा R3_END		0x789a
#घोषणा R4_START	0x2000
#घोषणा R4_END		0x7000

अटल काष्ठा resource r0 = अणु .start = R0_START, .end = R0_END पूर्ण;
अटल काष्ठा resource r1 = अणु .start = R1_START, .end = R1_END पूर्ण;
अटल काष्ठा resource r2 = अणु .start = R2_START, .end = R2_END पूर्ण;
अटल काष्ठा resource r3 = अणु .start = R3_START, .end = R3_END पूर्ण;
अटल काष्ठा resource r4 = अणु .start = R4_START, .end = R4_END पूर्ण;

काष्ठा result अणु
	काष्ठा resource *r1;
	काष्ठा resource *r2;
	काष्ठा resource r;
	bool ret;
पूर्ण;

अटल काष्ठा result results_क्रम_जोड़[] = अणु
	अणु
		.r1 = &r1, .r2 = &r0, .r.start = R0_START, .r.end = R0_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r2, .r2 = &r0, .r.start = R0_START, .r.end = R0_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r3, .r2 = &r0, .r.start = R0_START, .r.end = R0_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r4, .r2 = &r0, .r.start = R0_START, .r.end = R0_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r2, .r2 = &r1, .ret = false,
	पूर्ण, अणु
		.r1 = &r3, .r2 = &r1, .ret = false,
	पूर्ण, अणु
		.r1 = &r4, .r2 = &r1, .r.start = R1_START, .r.end = R4_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r2, .r2 = &r3, .ret = false,
	पूर्ण, अणु
		.r1 = &r2, .r2 = &r4, .r.start = R4_START, .r.end = R4_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r3, .r2 = &r4, .r.start = R4_START, .r.end = R3_END, .ret = true,
	पूर्ण,
पूर्ण;

अटल काष्ठा result results_क्रम_पूर्णांकersection[] = अणु
	अणु
		.r1 = &r1, .r2 = &r0, .r.start = R1_START, .r.end = R1_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r2, .r2 = &r0, .r.start = R2_START, .r.end = R2_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r3, .r2 = &r0, .r.start = R3_START, .r.end = R3_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r4, .r2 = &r0, .r.start = R4_START, .r.end = R4_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r2, .r2 = &r1, .ret = false,
	पूर्ण, अणु
		.r1 = &r3, .r2 = &r1, .ret = false,
	पूर्ण, अणु
		.r1 = &r4, .r2 = &r1, .r.start = R4_START, .r.end = R1_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r2, .r2 = &r3, .ret = false,
	पूर्ण, अणु
		.r1 = &r2, .r2 = &r4, .r.start = R2_START, .r.end = R2_END, .ret = true,
	पूर्ण, अणु
		.r1 = &r3, .r2 = &r4, .r.start = R3_START, .r.end = R4_END, .ret = true,
	पूर्ण,
पूर्ण;

अटल व्योम resource_करो_test(काष्ठा kunit *test, bool ret, काष्ठा resource *r,
			     bool exp_ret, काष्ठा resource *exp_r,
			     काष्ठा resource *r1, काष्ठा resource *r2)
अणु
	KUNIT_EXPECT_EQ_MSG(test, ret, exp_ret, "Resources %pR %pR", r1, r2);
	KUNIT_EXPECT_EQ_MSG(test, r->start, exp_r->start, "Start elements are not equal");
	KUNIT_EXPECT_EQ_MSG(test, r->end, exp_r->end, "End elements are not equal");
पूर्ण

अटल व्योम resource_करो_जोड़_test(काष्ठा kunit *test, काष्ठा result *r)
अणु
	काष्ठा resource result;
	bool ret;

	स_रखो(&result, 0, माप(result));
	ret = resource_जोड़(r->r1, r->r2, &result);
	resource_करो_test(test, ret, &result, r->ret, &r->r, r->r1, r->r2);

	स_रखो(&result, 0, माप(result));
	ret = resource_जोड़(r->r2, r->r1, &result);
	resource_करो_test(test, ret, &result, r->ret, &r->r, r->r2, r->r1);
पूर्ण

अटल व्योम resource_test_जोड़(काष्ठा kunit *test)
अणु
	काष्ठा result *r = results_क्रम_जोड़;
	अचिन्हित पूर्णांक i = 0;

	करो अणु
		resource_करो_जोड़_test(test, &r[i]);
	पूर्ण जबतक (++i < ARRAY_SIZE(results_क्रम_जोड़));
पूर्ण

अटल व्योम resource_करो_पूर्णांकersection_test(काष्ठा kunit *test, काष्ठा result *r)
अणु
	काष्ठा resource result;
	bool ret;

	स_रखो(&result, 0, माप(result));
	ret = resource_पूर्णांकersection(r->r1, r->r2, &result);
	resource_करो_test(test, ret, &result, r->ret, &r->r, r->r1, r->r2);

	स_रखो(&result, 0, माप(result));
	ret = resource_पूर्णांकersection(r->r2, r->r1, &result);
	resource_करो_test(test, ret, &result, r->ret, &r->r, r->r2, r->r1);
पूर्ण

अटल व्योम resource_test_पूर्णांकersection(काष्ठा kunit *test)
अणु
	काष्ठा result *r = results_क्रम_पूर्णांकersection;
	अचिन्हित पूर्णांक i = 0;

	करो अणु
		resource_करो_पूर्णांकersection_test(test, &r[i]);
	पूर्ण जबतक (++i < ARRAY_SIZE(results_क्रम_पूर्णांकersection));
पूर्ण

अटल काष्ठा kunit_हाल resource_test_हालs[] = अणु
	KUNIT_CASE(resource_test_जोड़),
	KUNIT_CASE(resource_test_पूर्णांकersection),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite resource_test_suite = अणु
	.name = "resource",
	.test_हालs = resource_test_हालs,
पूर्ण;
kunit_test_suite(resource_test_suite);

MODULE_LICENSE("GPL");
