<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP
 */
#समावेश <kunit/test.h>
#समावेश <linux/pm_qos.h>

/* Basic test क्रम aggregating two "min" requests */
अटल व्योम freq_qos_test_min(काष्ठा kunit *test)
अणु
	काष्ठा freq_स्थिरraपूर्णांकs	qos;
	काष्ठा freq_qos_request	req1, req2;
	पूर्णांक ret;

	freq_स्थिरraपूर्णांकs_init(&qos);
	स_रखो(&req1, 0, माप(req1));
	स_रखो(&req2, 0, माप(req2));

	ret = freq_qos_add_request(&qos, &req1, FREQ_QOS_MIN, 1000);
	KUNIT_EXPECT_EQ(test, ret, 1);
	ret = freq_qos_add_request(&qos, &req2, FREQ_QOS_MIN, 2000);
	KUNIT_EXPECT_EQ(test, ret, 1);

	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MIN), 2000);

	ret = freq_qos_हटाओ_request(&req2);
	KUNIT_EXPECT_EQ(test, ret, 1);
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MIN), 1000);

	ret = freq_qos_हटाओ_request(&req1);
	KUNIT_EXPECT_EQ(test, ret, 1);
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MIN),
			FREQ_QOS_MIN_DEFAULT_VALUE);
पूर्ण

/* Test that requests क्रम MAX_DEFAULT_VALUE have no effect */
अटल व्योम freq_qos_test_maxdef(काष्ठा kunit *test)
अणु
	काष्ठा freq_स्थिरraपूर्णांकs	qos;
	काष्ठा freq_qos_request	req1, req2;
	पूर्णांक ret;

	freq_स्थिरraपूर्णांकs_init(&qos);
	स_रखो(&req1, 0, माप(req1));
	स_रखो(&req2, 0, माप(req2));
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MAX),
			FREQ_QOS_MAX_DEFAULT_VALUE);

	ret = freq_qos_add_request(&qos, &req1, FREQ_QOS_MAX,
			FREQ_QOS_MAX_DEFAULT_VALUE);
	KUNIT_EXPECT_EQ(test, ret, 0);
	ret = freq_qos_add_request(&qos, &req2, FREQ_QOS_MAX,
			FREQ_QOS_MAX_DEFAULT_VALUE);
	KUNIT_EXPECT_EQ(test, ret, 0);

	/* Add max 1000 */
	ret = freq_qos_update_request(&req1, 1000);
	KUNIT_EXPECT_EQ(test, ret, 1);
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MAX), 1000);

	/* Add max 2000, no impact */
	ret = freq_qos_update_request(&req2, 2000);
	KUNIT_EXPECT_EQ(test, ret, 0);
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MAX), 1000);

	/* Remove max 1000, new max 2000 */
	ret = freq_qos_हटाओ_request(&req1);
	KUNIT_EXPECT_EQ(test, ret, 1);
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MAX), 2000);
पूर्ण

/*
 * Test that a freq_qos_request can be added again after removal
 *
 * This issue was solved by commit 05ff1ba412fd ("PM: QoS: Invalidate frequency
 * QoS requests after removal")
 */
अटल व्योम freq_qos_test_पढ़ोd(काष्ठा kunit *test)
अणु
	काष्ठा freq_स्थिरraपूर्णांकs	qos;
	काष्ठा freq_qos_request	req;
	पूर्णांक ret;

	freq_स्थिरraपूर्णांकs_init(&qos);
	स_रखो(&req, 0, माप(req));
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MIN),
			FREQ_QOS_MIN_DEFAULT_VALUE);

	/* Add */
	ret = freq_qos_add_request(&qos, &req, FREQ_QOS_MIN, 1000);
	KUNIT_EXPECT_EQ(test, ret, 1);
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MIN), 1000);

	/* Remove */
	ret = freq_qos_हटाओ_request(&req);
	KUNIT_EXPECT_EQ(test, ret, 1);
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MIN),
			FREQ_QOS_MIN_DEFAULT_VALUE);

	/* Add again */
	ret = freq_qos_add_request(&qos, &req, FREQ_QOS_MIN, 2000);
	KUNIT_EXPECT_EQ(test, ret, 1);
	KUNIT_EXPECT_EQ(test, freq_qos_पढ़ो_value(&qos, FREQ_QOS_MIN), 2000);
पूर्ण

अटल काष्ठा kunit_हाल pm_qos_test_हालs[] = अणु
	KUNIT_CASE(freq_qos_test_min),
	KUNIT_CASE(freq_qos_test_maxdef),
	KUNIT_CASE(freq_qos_test_पढ़ोd),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा kunit_suite pm_qos_test_module = अणु
	.name = "qos-kunit-test",
	.test_हालs = pm_qos_test_हालs,
पूर्ण;
kunit_test_suites(&pm_qos_test_module);
