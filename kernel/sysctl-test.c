<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KUnit test of proc sysctl.
 */

#समावेश <kunit/test.h>
#समावेश <linux/sysctl.h>

#घोषणा KUNIT_PROC_READ 0
#घोषणा KUNIT_PROC_WRITE 1

अटल पूर्णांक i_zero;
अटल पूर्णांक i_one_hundred = 100;

/*
 * Test that proc_करोपूर्णांकvec will not try to use a शून्य .data field even when the
 * length is non-zero.
 */
अटल व्योम sysctl_test_api_करोपूर्णांकvec_null_tbl_data(काष्ठा kunit *test)
अणु
	काष्ठा ctl_table null_data_table = अणु
		.procname = "foo",
		/*
		 * Here we are testing that proc_करोपूर्णांकvec behaves correctly when
		 * we give it a शून्य .data field. Normally this would poपूर्णांक to a
		 * piece of memory where the value would be stored.
		 */
		.data		= शून्य,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	/*
	 * proc_करोपूर्णांकvec expects a buffer in user space, so we allocate one. We
	 * also need to cast it to __user so sparse करोesn't get mad.
	 */
	व्योम __user *buffer = (व्योम __user *)kunit_kzalloc(test, माप(पूर्णांक),
							   GFP_USER);
	माप_प्रकार len;
	loff_t pos;

	/*
	 * We करोn't care what the starting length is since proc_करोपूर्णांकvec should
	 * not try to पढ़ो because .data is शून्य.
	 */
	len = 1234;
	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&null_data_table,
					       KUNIT_PROC_READ, buffer, &len,
					       &pos));
	KUNIT_EXPECT_EQ(test, (माप_प्रकार)0, len);

	/*
	 * See above.
	 */
	len = 1234;
	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&null_data_table,
					       KUNIT_PROC_WRITE, buffer, &len,
					       &pos));
	KUNIT_EXPECT_EQ(test, (माप_प्रकार)0, len);
पूर्ण

/*
 * Similar to the previous test, we create a काष्ठा ctrl_table that has a .data
 * field that proc_करोपूर्णांकvec cannot करो anything with; however, this समय it is
 * because we tell proc_करोपूर्णांकvec that the size is 0.
 */
अटल व्योम sysctl_test_api_करोपूर्णांकvec_table_maxlen_unset(काष्ठा kunit *test)
अणु
	पूर्णांक data = 0;
	काष्ठा ctl_table data_maxlen_unset_table = अणु
		.procname = "foo",
		.data		= &data,
		/*
		 * So .data is no दीर्घer शून्य, but we tell proc_करोपूर्णांकvec its
		 * length is 0, so it still shouldn't try to use it.
		 */
		.maxlen		= 0,
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	व्योम __user *buffer = (व्योम __user *)kunit_kzalloc(test, माप(पूर्णांक),
							   GFP_USER);
	माप_प्रकार len;
	loff_t pos;

	/*
	 * As beक्रमe, we करोn't care what buffer length is because proc_करोपूर्णांकvec
	 * cannot करो anything because its पूर्णांकernal .data buffer has zero length.
	 */
	len = 1234;
	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&data_maxlen_unset_table,
					       KUNIT_PROC_READ, buffer, &len,
					       &pos));
	KUNIT_EXPECT_EQ(test, (माप_प्रकार)0, len);

	/*
	 * See previous comment.
	 */
	len = 1234;
	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&data_maxlen_unset_table,
					       KUNIT_PROC_WRITE, buffer, &len,
					       &pos));
	KUNIT_EXPECT_EQ(test, (माप_प्रकार)0, len);
पूर्ण

/*
 * Here we provide a valid काष्ठा ctl_table, but we try to पढ़ो and ग_लिखो from
 * it using a buffer of zero length, so it should still fail in a similar way as
 * beक्रमe.
 */
अटल व्योम sysctl_test_api_करोपूर्णांकvec_table_len_is_zero(काष्ठा kunit *test)
अणु
	पूर्णांक data = 0;
	/* Good table. */
	काष्ठा ctl_table table = अणु
		.procname = "foo",
		.data		= &data,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	व्योम __user *buffer = (व्योम __user *)kunit_kzalloc(test, माप(पूर्णांक),
							   GFP_USER);
	/*
	 * However, now our पढ़ो/ग_लिखो buffer has zero length.
	 */
	माप_प्रकार len = 0;
	loff_t pos;

	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&table, KUNIT_PROC_READ, buffer,
					       &len, &pos));
	KUNIT_EXPECT_EQ(test, (माप_प्रकार)0, len);

	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&table, KUNIT_PROC_WRITE, buffer,
					       &len, &pos));
	KUNIT_EXPECT_EQ(test, (माप_प्रकार)0, len);
पूर्ण

/*
 * Test that proc_करोपूर्णांकvec refuses to पढ़ो when the file position is non-zero.
 */
अटल व्योम sysctl_test_api_करोपूर्णांकvec_table_पढ़ो_but_position_set(
		काष्ठा kunit *test)
अणु
	पूर्णांक data = 0;
	/* Good table. */
	काष्ठा ctl_table table = अणु
		.procname = "foo",
		.data		= &data,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	व्योम __user *buffer = (व्योम __user *)kunit_kzalloc(test, माप(पूर्णांक),
							   GFP_USER);
	/*
	 * We करोn't care about our buffer length because we start off with a
	 * non-zero file position.
	 */
	माप_प्रकार len = 1234;
	/*
	 * proc_करोपूर्णांकvec should refuse to पढ़ो पूर्णांकo the buffer since the file
	 * pos is non-zero.
	 */
	loff_t pos = 1;

	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&table, KUNIT_PROC_READ, buffer,
					       &len, &pos));
	KUNIT_EXPECT_EQ(test, (माप_प्रकार)0, len);
पूर्ण

/*
 * Test that we can पढ़ो a two digit number in a sufficiently size buffer.
 * Nothing fancy.
 */
अटल व्योम sysctl_test_करोपूर्णांकvec_पढ़ो_happy_single_positive(काष्ठा kunit *test)
अणु
	पूर्णांक data = 0;
	/* Good table. */
	काष्ठा ctl_table table = अणु
		.procname = "foo",
		.data		= &data,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	माप_प्रकार len = 4;
	loff_t pos = 0;
	अक्षर *buffer = kunit_kzalloc(test, len, GFP_USER);
	अक्षर __user *user_buffer = (अक्षर __user *)buffer;
	/* Store 13 in the data field. */
	*((पूर्णांक *)table.data) = 13;

	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&table, KUNIT_PROC_READ,
					       user_buffer, &len, &pos));
	KUNIT_ASSERT_EQ(test, (माप_प्रकार)3, len);
	buffer[len] = '\0';
	/* And we पढ़ो 13 back out. */
	KUNIT_EXPECT_STREQ(test, "13\n", buffer);
पूर्ण

/*
 * Same as previous test, just now with negative numbers.
 */
अटल व्योम sysctl_test_करोपूर्णांकvec_पढ़ो_happy_single_negative(काष्ठा kunit *test)
अणु
	पूर्णांक data = 0;
	/* Good table. */
	काष्ठा ctl_table table = अणु
		.procname = "foo",
		.data		= &data,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	माप_प्रकार len = 5;
	loff_t pos = 0;
	अक्षर *buffer = kunit_kzalloc(test, len, GFP_USER);
	अक्षर __user *user_buffer = (अक्षर __user *)buffer;
	*((पूर्णांक *)table.data) = -16;

	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&table, KUNIT_PROC_READ,
					       user_buffer, &len, &pos));
	KUNIT_ASSERT_EQ(test, (माप_प्रकार)4, len);
	buffer[len] = '\0';
	KUNIT_EXPECT_STREQ(test, "-16\n", (अक्षर *)buffer);
पूर्ण

/*
 * Test that a simple positive ग_लिखो works.
 */
अटल व्योम sysctl_test_करोपूर्णांकvec_ग_लिखो_happy_single_positive(काष्ठा kunit *test)
अणु
	पूर्णांक data = 0;
	/* Good table. */
	काष्ठा ctl_table table = अणु
		.procname = "foo",
		.data		= &data,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	अक्षर input[] = "9";
	माप_प्रकार len = माप(input) - 1;
	loff_t pos = 0;
	अक्षर *buffer = kunit_kzalloc(test, len, GFP_USER);
	अक्षर __user *user_buffer = (अक्षर __user *)buffer;

	स_नकल(buffer, input, len);

	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&table, KUNIT_PROC_WRITE,
					       user_buffer, &len, &pos));
	KUNIT_EXPECT_EQ(test, माप(input) - 1, len);
	KUNIT_EXPECT_EQ(test, माप(input) - 1, (माप_प्रकार)pos);
	KUNIT_EXPECT_EQ(test, 9, *((पूर्णांक *)table.data));
पूर्ण

/*
 * Same as previous test, but now with negative numbers.
 */
अटल व्योम sysctl_test_करोपूर्णांकvec_ग_लिखो_happy_single_negative(काष्ठा kunit *test)
अणु
	पूर्णांक data = 0;
	काष्ठा ctl_table table = अणु
		.procname = "foo",
		.data		= &data,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	अक्षर input[] = "-9";
	माप_प्रकार len = माप(input) - 1;
	loff_t pos = 0;
	अक्षर *buffer = kunit_kzalloc(test, len, GFP_USER);
	अक्षर __user *user_buffer = (अक्षर __user *)buffer;

	स_नकल(buffer, input, len);

	KUNIT_EXPECT_EQ(test, 0, proc_करोपूर्णांकvec(&table, KUNIT_PROC_WRITE,
					       user_buffer, &len, &pos));
	KUNIT_EXPECT_EQ(test, माप(input) - 1, len);
	KUNIT_EXPECT_EQ(test, माप(input) - 1, (माप_प्रकार)pos);
	KUNIT_EXPECT_EQ(test, -9, *((पूर्णांक *)table.data));
पूर्ण

/*
 * Test that writing a value smaller than the minimum possible value is not
 * allowed.
 */
अटल व्योम sysctl_test_api_करोपूर्णांकvec_ग_लिखो_single_less_पूर्णांक_min(
		काष्ठा kunit *test)
अणु
	पूर्णांक data = 0;
	काष्ठा ctl_table table = अणु
		.procname = "foo",
		.data		= &data,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	माप_प्रकार max_len = 32, len = max_len;
	loff_t pos = 0;
	अक्षर *buffer = kunit_kzalloc(test, max_len, GFP_USER);
	अक्षर __user *user_buffer = (अक्षर __user *)buffer;
	अचिन्हित दीर्घ असल_of_less_than_min = (अचिन्हित दीर्घ)पूर्णांक_उच्च
					     - (पूर्णांक_उच्च + पूर्णांक_न्यून) + 1;

	/*
	 * We use this rigmarole to create a string that contains a value one
	 * less than the minimum accepted value.
	 */
	KUNIT_ASSERT_LT(test,
			(माप_प्रकार)snम_लिखो(buffer, max_len, "-%lu",
					 असल_of_less_than_min),
			max_len);

	KUNIT_EXPECT_EQ(test, -EINVAL, proc_करोपूर्णांकvec(&table, KUNIT_PROC_WRITE,
						     user_buffer, &len, &pos));
	KUNIT_EXPECT_EQ(test, max_len, len);
	KUNIT_EXPECT_EQ(test, 0, *((पूर्णांक *)table.data));
पूर्ण

/*
 * Test that writing the maximum possible value works.
 */
अटल व्योम sysctl_test_api_करोपूर्णांकvec_ग_लिखो_single_greater_पूर्णांक_max(
		काष्ठा kunit *test)
अणु
	पूर्णांक data = 0;
	काष्ठा ctl_table table = अणु
		.procname = "foo",
		.data		= &data,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= &i_zero,
		.extra2         = &i_one_hundred,
	पूर्ण;
	माप_प्रकार max_len = 32, len = max_len;
	loff_t pos = 0;
	अक्षर *buffer = kunit_kzalloc(test, max_len, GFP_USER);
	अक्षर __user *user_buffer = (अक्षर __user *)buffer;
	अचिन्हित दीर्घ greater_than_max = (अचिन्हित दीर्घ)पूर्णांक_उच्च + 1;

	KUNIT_ASSERT_GT(test, greater_than_max, (अचिन्हित दीर्घ)पूर्णांक_उच्च);
	KUNIT_ASSERT_LT(test, (माप_प्रकार)snम_लिखो(buffer, max_len, "%lu",
					       greater_than_max),
			max_len);
	KUNIT_EXPECT_EQ(test, -EINVAL, proc_करोपूर्णांकvec(&table, KUNIT_PROC_WRITE,
						     user_buffer, &len, &pos));
	KUNIT_ASSERT_EQ(test, max_len, len);
	KUNIT_EXPECT_EQ(test, 0, *((पूर्णांक *)table.data));
पूर्ण

अटल काष्ठा kunit_हाल sysctl_test_हालs[] = अणु
	KUNIT_CASE(sysctl_test_api_करोपूर्णांकvec_null_tbl_data),
	KUNIT_CASE(sysctl_test_api_करोपूर्णांकvec_table_maxlen_unset),
	KUNIT_CASE(sysctl_test_api_करोपूर्णांकvec_table_len_is_zero),
	KUNIT_CASE(sysctl_test_api_करोपूर्णांकvec_table_पढ़ो_but_position_set),
	KUNIT_CASE(sysctl_test_करोपूर्णांकvec_पढ़ो_happy_single_positive),
	KUNIT_CASE(sysctl_test_करोपूर्णांकvec_पढ़ो_happy_single_negative),
	KUNIT_CASE(sysctl_test_करोपूर्णांकvec_ग_लिखो_happy_single_positive),
	KUNIT_CASE(sysctl_test_करोपूर्णांकvec_ग_लिखो_happy_single_negative),
	KUNIT_CASE(sysctl_test_api_करोपूर्णांकvec_ग_लिखो_single_less_पूर्णांक_min),
	KUNIT_CASE(sysctl_test_api_करोपूर्णांकvec_ग_लिखो_single_greater_पूर्णांक_max),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite sysctl_test_suite = अणु
	.name = "sysctl_test",
	.test_हालs = sysctl_test_हालs,
पूर्ण;

kunit_test_suites(&sysctl_test_suite);

MODULE_LICENSE("GPL v2");
