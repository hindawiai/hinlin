<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright (C) 2020 IBM Corp. */

#समावेश <kunit/test.h>

अटल व्योम aspeed_sdhci_phase_ddr52(काष्ठा kunit *test)
अणु
	पूर्णांक rate = 52000000;

	KUNIT_EXPECT_EQ(test, 0,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 0));
	KUNIT_EXPECT_EQ(test, 0,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 1));
	KUNIT_EXPECT_EQ(test, 1,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 2));
	KUNIT_EXPECT_EQ(test, 1,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 3));
	KUNIT_EXPECT_EQ(test, 2,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 4));
	KUNIT_EXPECT_EQ(test, 3,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 5));
	KUNIT_EXPECT_EQ(test, 14,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 23));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 24));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 25));

	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 0,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 180));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 0,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 181));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 1,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 182));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 1,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 183));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 2,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 184));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 3,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 185));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 14,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 203));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 204));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 205));
पूर्ण

अटल व्योम aspeed_sdhci_phase_hs200(काष्ठा kunit *test)
अणु
	पूर्णांक rate = 200000000;

	KUNIT_EXPECT_EQ(test, 0,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 0));
	KUNIT_EXPECT_EQ(test, 0,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 5));
	KUNIT_EXPECT_EQ(test, 1,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 6));
	KUNIT_EXPECT_EQ(test, 1,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 7));
	KUNIT_EXPECT_EQ(test, 14,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 89));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 90));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 91));
	KUNIT_EXPECT_EQ(test, 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 96));

	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 180));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 185));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 1,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 186));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 1,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 187));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 14,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 269));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 270));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 271));
	KUNIT_EXPECT_EQ(test, (पूर्णांक)ASPEED_SDHCI_TAP_PARAM_INVERT_CLK | 15,
			aspeed_sdhci_phase_to_tap(शून्य, rate, 276));
पूर्ण

अटल काष्ठा kunit_हाल aspeed_sdhci_test_हालs[] = अणु
	KUNIT_CASE(aspeed_sdhci_phase_ddr52),
	KUNIT_CASE(aspeed_sdhci_phase_hs200),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite aspeed_sdhci_test_suite = अणु
	.name = "sdhci-of-aspeed",
	.test_हालs = aspeed_sdhci_test_हालs,
पूर्ण;

अटल काष्ठा kunit_suite *aspeed_sdc_test_suite_array[] = अणु
	&aspeed_sdhci_test_suite,
	शून्य,
पूर्ण;

अटल काष्ठा kunit_suite **aspeed_sdc_test_suites
	__used __section(".kunit_test_suites") = aspeed_sdc_test_suite_array;
