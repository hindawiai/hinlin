<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * imr_selftest.c -- Intel Isolated Memory Region self-test driver
 *
 * Copyright(c) 2013 Intel Corporation.
 * Copyright(c) 2015 Bryan O'Donoghue <pure.logic@nexus-software.ie>
 *
 * IMR self test. The purpose of this module is to run a set of tests on the
 * IMR API to validate it's sanity. We check क्रम overlapping, reserved
 * addresses and setup/tearकरोwn sanity.
 *
 */

#समावेश <यंत्र-generic/sections.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/imr.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>

#घोषणा SELFTEST KBUILD_MODNAME ": "
/**
 * imr_self_test_result - Prपूर्णांक result string क्रम self test.
 *
 * @res:	result code - true अगर test passed false otherwise.
 * @fmt:	क्रमmat string.
 * ...		variadic argument list.
 */
अटल __म_लिखो(2, 3)
व्योम __init imr_self_test_result(पूर्णांक res, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची vlist;

	/* Prपूर्णांक pass/fail. */
	अगर (res)
		pr_info(SELFTEST "pass ");
	अन्यथा
		pr_info(SELFTEST "fail ");

	/* Prपूर्णांक variable string. */
	बहु_शुरू(vlist, fmt);
	vprपूर्णांकk(fmt, vlist);
	बहु_पूर्ण(vlist);

	/* Optional warning. */
	WARN(res == 0, "test failed");
पूर्ण
#अघोषित SELFTEST

/**
 * imr_self_test
 *
 * Verअगरy IMR self_test with some simple tests to verअगरy overlap,
 * zero sized allocations and 1 KiB sized areas.
 *
 */
अटल व्योम __init imr_self_test(व्योम)
अणु
	phys_addr_t base  = virt_to_phys(&_text);
	माप_प्रकार size = virt_to_phys(&__end_rodata) - base;
	स्थिर अक्षर *fmt_over = "overlapped IMR @ (0x%08lx - 0x%08lx)\n";
	पूर्णांक ret;

	/* Test zero zero. */
	ret = imr_add_range(0, 0, 0, 0);
	imr_self_test_result(ret < 0, "zero sized IMR\n");

	/* Test exact overlap. */
	ret = imr_add_range(base, size, IMR_CPU, IMR_CPU);
	imr_self_test_result(ret < 0, fmt_over, __va(base), __va(base + size));

	/* Test overlap with base inside of existing. */
	base += size - IMR_ALIGN;
	ret = imr_add_range(base, size, IMR_CPU, IMR_CPU);
	imr_self_test_result(ret < 0, fmt_over, __va(base), __va(base + size));

	/* Test overlap with end inside of existing. */
	base -= size + IMR_ALIGN * 2;
	ret = imr_add_range(base, size, IMR_CPU, IMR_CPU);
	imr_self_test_result(ret < 0, fmt_over, __va(base), __va(base + size));

	/* Test that a 1 KiB IMR @ zero with पढ़ो/ग_लिखो all will bomb out. */
	ret = imr_add_range(0, IMR_ALIGN, IMR_READ_ACCESS_ALL,
			    IMR_WRITE_ACCESS_ALL);
	imr_self_test_result(ret < 0, "1KiB IMR @ 0x00000000 - access-all\n");

	/* Test that a 1 KiB IMR @ zero with CPU only will work. */
	ret = imr_add_range(0, IMR_ALIGN, IMR_CPU, IMR_CPU);
	imr_self_test_result(ret >= 0, "1KiB IMR @ 0x00000000 - cpu-access\n");
	अगर (ret >= 0) अणु
		ret = imr_हटाओ_range(0, IMR_ALIGN);
		imr_self_test_result(ret == 0, "teardown - cpu-access\n");
	पूर्ण

	/* Test 2 KiB works. */
	size = IMR_ALIGN * 2;
	ret = imr_add_range(0, size, IMR_READ_ACCESS_ALL, IMR_WRITE_ACCESS_ALL);
	imr_self_test_result(ret >= 0, "2KiB IMR @ 0x00000000\n");
	अगर (ret >= 0) अणु
		ret = imr_हटाओ_range(0, size);
		imr_self_test_result(ret == 0, "teardown 2KiB\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id imr_ids[] __initस्थिर = अणु
	X86_MATCH_VENDOR_FAM_MODEL(INTEL, 5, INTEL_FAM5_QUARK_X1000, शून्य),
	अणुपूर्ण
पूर्ण;

/**
 * imr_self_test_init - entry poपूर्णांक क्रम IMR driver.
 *
 * वापस: -ENODEV क्रम no IMR support 0 अगर good to go.
 */
अटल पूर्णांक __init imr_self_test_init(व्योम)
अणु
	अगर (x86_match_cpu(imr_ids))
		imr_self_test();
	वापस 0;
पूर्ण

/**
 * imr_self_test_निकास - निकास poपूर्णांक क्रम IMR code.
 *
 * वापस:
 */
device_initcall(imr_self_test_init);
