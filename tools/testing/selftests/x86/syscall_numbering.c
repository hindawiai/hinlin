<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * syscall_arg_fault.c - tests faults 32-bit fast syscall stack args
 * Copyright (c) 2018 Andrew Lutomirski
 */

#घोषणा _GNU_SOURCE

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <syscall.h>

अटल पूर्णांक nerrs;

#घोषणा X32_BIT 0x40000000UL

अटल व्योम check_enosys(अचिन्हित दीर्घ nr, bool *ok)
अणु
	/* If this fails, a segfault is reasonably likely. */
	ख_साफ(मानक_निकास);

	दीर्घ ret = syscall(nr, 0, 0, 0, 0, 0, 0);
	अगर (ret == 0) अणु
		म_लिखो("[FAIL]\tsyscall %lu succeeded, but it should have failed\n", nr);
		*ok = false;
	पूर्ण अन्यथा अगर (त्रुटि_सं != ENOSYS) अणु
		म_लिखो("[FAIL]\tsyscall %lu had error code %d, but it should have reported ENOSYS\n", nr, त्रुटि_सं);
		*ok = false;
	पूर्ण
पूर्ण

अटल व्योम test_x32_without_x32_bit(व्योम)
अणु
	bool ok = true;

	/*
	 * Syscalls 512-547 are "x32" syscalls.  They are पूर्णांकended to be
	 * called with the x32 (0x40000000) bit set.  Calling them without
	 * the x32 bit set is nonsense and should not work.
	 */
	म_लिखो("[RUN]\tChecking syscalls 512-547\n");
	क्रम (पूर्णांक i = 512; i <= 547; i++)
		check_enosys(i, &ok);

	/*
	 * Check that a handful of 64-bit-only syscalls are rejected अगर the x32
	 * bit is set.
	 */
	म_लिखो("[RUN]\tChecking some 64-bit syscalls in x32 range\n");
	check_enosys(16 | X32_BIT, &ok);	/* ioctl */
	check_enosys(19 | X32_BIT, &ok);	/* पढ़ोv */
	check_enosys(20 | X32_BIT, &ok);	/* ग_लिखोv */

	/*
	 * Check some syscalls with high bits set.
	 */
	म_लिखो("[RUN]\टChecking numbers above 2^32-1\न");
	check_enosys((1UL << 32), &ok);
	check_enosys(X32_BIT | (1UL << 32), &ok);

	अगर (!ok)
		nerrs++;
	अन्यथा
		म_लिखो("[OK]\tThey all returned -ENOSYS\n");
पूर्ण

पूर्णांक मुख्य()
अणु
	/*
	 * Anyone diagnosing a failure will want to know whether the kernel
	 * supports x32.  Tell them.
	 */
	म_लिखो("\tChecking for x32...");
	ख_साफ(मानक_निकास);
	अगर (syscall(39 | X32_BIT, 0, 0, 0, 0, 0, 0) >= 0) अणु
		म_लिखो(" supported\n");
	पूर्ण अन्यथा अगर (त्रुटि_सं == ENOSYS) अणु
		म_लिखो(" not supported\n");
	पूर्ण अन्यथा अणु
		म_लिखो(" confused\n");
	पूर्ण

	test_x32_without_x32_bit();

	वापस nerrs ? 1 : 0;
पूर्ण
