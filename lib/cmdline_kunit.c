<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Test हालs क्रम API provided by cmdline.c
 */

#समावेश <kunit/test.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/माला.स>

अटल स्थिर अक्षर *cmdline_test_strings[] = अणु
	"\"\"", ""  , "=" , "\"-", ","    , "-,"   , ",-"   , "-" ,
	"+,"  , "--", ",,", "''" , "\"\",", "\",\"", "-\"\"", "\"",
पूर्ण;

अटल स्थिर पूर्णांक cmdline_test_values[] = अणु
	1, 1, 1, 1, 2, 3, 2, 3,
	1, 3, 2, 1, 1, 1, 3, 1,
पूर्ण;

अटल_निश्चित(ARRAY_SIZE(cmdline_test_strings) == ARRAY_SIZE(cmdline_test_values));

अटल स्थिर अक्षर *cmdline_test_range_strings[] = अणु
	"-7" , "--7"  , "-1-2"    , "7--9",
	"7-" , "-7--9", "7-9,"    , "9-7" ,
	"5-a", "a-5"  , "5-8"     , ",8-5",
	"+,1", "-,4"  , "-3,0-1,6", "4,-" ,
	" +2", " -9"  , "0-1,-3,6", "- 9" ,
पूर्ण;

अटल स्थिर पूर्णांक cmdline_test_range_values[][16] = अणु
	अणु 1, -7, पूर्ण, अणु 0, -0, पूर्ण, अणु 4, -1, 0, +1, 2, पूर्ण, अणु 0, 7, पूर्ण,
	अणु 0, +7, पूर्ण, अणु 0, -7, पूर्ण, अणु 3, +7, 8, +9, 0, पूर्ण, अणु 0, 9, पूर्ण,
	अणु 0, +5, पूर्ण, अणु 0, -0, पूर्ण, अणु 4, +5, 6, +7, 8, पूर्ण, अणु 0, 0, पूर्ण,
	अणु 0, +0, पूर्ण, अणु 0, -0, पूर्ण, अणु 4, -3, 0, +1, 6, पूर्ण, अणु 1, 4, पूर्ण,
	अणु 0, +0, पूर्ण, अणु 0, -0, पूर्ण, अणु 4, +0, 1, -3, 6, पूर्ण, अणु 0, 0, पूर्ण,
पूर्ण;

अटल_निश्चित(ARRAY_SIZE(cmdline_test_range_strings) == ARRAY_SIZE(cmdline_test_range_values));

अटल व्योम cmdline_करो_one_test(काष्ठा kunit *test, स्थिर अक्षर *in, पूर्णांक rc, पूर्णांक offset)
अणु
	स्थिर अक्षर *fmt = "Pattern: %s";
	स्थिर अक्षर *out = in;
	पूर्णांक dummy;
	पूर्णांक ret;

	ret = get_option((अक्षर **)&out, &dummy);

	KUNIT_EXPECT_EQ_MSG(test, ret, rc, fmt, in);
	KUNIT_EXPECT_PTR_EQ_MSG(test, out, in + offset, fmt, in);
पूर्ण

अटल व्योम cmdline_test_noपूर्णांक(काष्ठा kunit *test)
अणु
	अचिन्हित पूर्णांक i = 0;

	करो अणु
		स्थिर अक्षर *str = cmdline_test_strings[i];
		पूर्णांक rc = 0;
		पूर्णांक offset;

		/* Only first and leading '-' will advance the poपूर्णांकer */
		offset = !!(*str == '-');
		cmdline_करो_one_test(test, str, rc, offset);
	पूर्ण जबतक (++i < ARRAY_SIZE(cmdline_test_strings));
पूर्ण

अटल व्योम cmdline_test_lead_पूर्णांक(काष्ठा kunit *test)
अणु
	अचिन्हित पूर्णांक i = 0;
	अक्षर in[32];

	करो अणु
		स्थिर अक्षर *str = cmdline_test_strings[i];
		पूर्णांक rc = cmdline_test_values[i];
		पूर्णांक offset;

		प्र_लिखो(in, "%u%s", get_अक्रमom_पूर्णांक() % 256, str);
		/* Only first '-' after the number will advance the poपूर्णांकer */
		offset = म_माप(in) - म_माप(str) + !!(rc == 2);
		cmdline_करो_one_test(test, in, rc, offset);
	पूर्ण जबतक (++i < ARRAY_SIZE(cmdline_test_strings));
पूर्ण

अटल व्योम cmdline_test_tail_पूर्णांक(काष्ठा kunit *test)
अणु
	अचिन्हित पूर्णांक i = 0;
	अक्षर in[32];

	करो अणु
		स्थिर अक्षर *str = cmdline_test_strings[i];
		/* When "" or "-" the result will be valid पूर्णांकeger */
		पूर्णांक rc = म_भेद(str, "") ? (म_भेद(str, "-") ? 0 : 1) : 1;
		पूर्णांक offset;

		प्र_लिखो(in, "%s%u", str, get_अक्रमom_पूर्णांक() % 256);
		/*
		 * Only first and leading '-' not followed by पूर्णांकeger
		 * will advance the poपूर्णांकer.
		 */
		offset = rc ? म_माप(in) : !!(*str == '-');
		cmdline_करो_one_test(test, in, rc, offset);
	पूर्ण जबतक (++i < ARRAY_SIZE(cmdline_test_strings));
पूर्ण

अटल व्योम cmdline_करो_one_range_test(काष्ठा kunit *test, स्थिर अक्षर *in,
				      अचिन्हित पूर्णांक n, स्थिर पूर्णांक *e)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक r[16];
	पूर्णांक *p;

	स_रखो(r, 0, माप(r));
	get_options(in, ARRAY_SIZE(r), r);
	KUNIT_EXPECT_EQ_MSG(test, r[0], e[0], "in test %u (parsed) expected %d numbers, got %d",
			    n, e[0], r[0]);
	क्रम (i = 1; i < ARRAY_SIZE(r); i++)
		KUNIT_EXPECT_EQ_MSG(test, r[i], e[i], "in test %u at %u", n, i);

	स_रखो(r, 0, माप(r));
	get_options(in, 0, r);
	KUNIT_EXPECT_EQ_MSG(test, r[0], e[0], "in test %u (validated) expected %d numbers, got %d",
			    n, e[0], r[0]);

	p = स_प्रथम_inv(&r[1], 0, माप(r) - माप(r[0]));
	KUNIT_EXPECT_PTR_EQ_MSG(test, p, (पूर्णांक *)0, "in test %u at %u out of bound", n, p - r);
पूर्ण

अटल व्योम cmdline_test_range(काष्ठा kunit *test)
अणु
	अचिन्हित पूर्णांक i = 0;

	करो अणु
		स्थिर अक्षर *str = cmdline_test_range_strings[i];
		स्थिर पूर्णांक *e = cmdline_test_range_values[i];

		cmdline_करो_one_range_test(test, str, i, e);
	पूर्ण जबतक (++i < ARRAY_SIZE(cmdline_test_range_strings));
पूर्ण

अटल काष्ठा kunit_हाल cmdline_test_हालs[] = अणु
	KUNIT_CASE(cmdline_test_noपूर्णांक),
	KUNIT_CASE(cmdline_test_lead_पूर्णांक),
	KUNIT_CASE(cmdline_test_tail_पूर्णांक),
	KUNIT_CASE(cmdline_test_range),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite cmdline_test_suite = अणु
	.name = "cmdline",
	.test_हालs = cmdline_test_हालs,
पूर्ण;
kunit_test_suite(cmdline_test_suite);

MODULE_LICENSE("GPL");
