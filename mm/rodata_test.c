<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rodata_test.c: functional test क्रम mark_rodata_ro function
 *
 * (C) Copyright 2008 Intel Corporation
 * Author: Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */
#घोषणा pr_fmt(fmt) "rodata_test: " fmt

#समावेश <linux/rodata_test.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sections.h>

अटल स्थिर पूर्णांक rodata_test_data = 0xC3;

व्योम rodata_test(व्योम)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक zero = 0;

	/* test 1: पढ़ो the value */
	/* If this test fails, some previous testrun has clobbered the state */
	अगर (!rodata_test_data) अणु
		pr_err("test 1 fails (start data)\n");
		वापस;
	पूर्ण

	/* test 2: ग_लिखो to the variable; this should fault */
	अगर (!copy_to_kernel_nofault((व्योम *)&rodata_test_data,
				(व्योम *)&zero, माप(zero))) अणु
		pr_err("test data was not read only\n");
		वापस;
	पूर्ण

	/* test 3: check the value hasn't changed */
	अगर (rodata_test_data == zero) अणु
		pr_err("test data was changed\n");
		वापस;
	पूर्ण

	/* test 4: check अगर the rodata section is PAGE_SIZE aligned */
	start = (अचिन्हित दीर्घ)__start_rodata;
	end = (अचिन्हित दीर्घ)__end_rodata;
	अगर (start & (PAGE_SIZE - 1)) अणु
		pr_err("start of .rodata is not page size aligned\n");
		वापस;
	पूर्ण
	अगर (end & (PAGE_SIZE - 1)) अणु
		pr_err("end of .rodata is not page size aligned\n");
		वापस;
	पूर्ण

	pr_info("all tests were successful\n");
पूर्ण
