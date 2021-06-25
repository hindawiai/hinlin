<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Riअक्षरd Weinberger <richrd@nod.at>
 *
 * This vDSO turns all calls पूर्णांकo a syscall so that UML can trap them.
 */


/* Disable profiling क्रम userspace code */
#घोषणा DISABLE_BRANCH_PROFILING

#समावेश <linux/समय.स>
#समावेश <linux/अ_लोpu.h>
#समावेश <यंत्र/unistd.h>

पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा __kernel_old_बारpec *ts)
अणु
	दीर्घ ret;

	यंत्र("syscall" : "=a" (ret) :
		"0" (__NR_घड़ी_समय_लो), "D" (घड़ी), "S" (ts) : "memory");

	वापस ret;
पूर्ण
पूर्णांक घड़ी_समय_लो(घड़ीid_t, काष्ठा __kernel_old_बारpec *)
	__attribute__((weak, alias("__vdso_clock_gettime")));

पूर्णांक __vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz)
अणु
	दीर्घ ret;

	यंत्र("syscall" : "=a" (ret) :
		"0" (__NR_समय_लोofday), "D" (tv), "S" (tz) : "memory");

	वापस ret;
पूर्ण
पूर्णांक समय_लोofday(काष्ठा __kernel_old_समयval *, काष्ठा समयzone *)
	__attribute__((weak, alias("__vdso_gettimeofday")));

__kernel_old_समय_प्रकार __vdso_समय(__kernel_old_समय_प्रकार *t)
अणु
	दीर्घ secs;

	यंत्र अस्थिर("syscall"
		: "=a" (secs)
		: "0" (__NR_समय), "D" (t) : "cc", "r11", "cx", "memory");

	वापस secs;
पूर्ण
__kernel_old_समय_प्रकार समय(__kernel_old_समय_प्रकार *t) __attribute__((weak, alias("__vdso_time")));

दीर्घ
__vdso_अ_लोpu(अचिन्हित *cpu, अचिन्हित *node, काष्ठा अ_लोpu_cache *unused)
अणु
	/*
	 * UML करोes not support SMP, we can cheat here. :)
	 */

	अगर (cpu)
		*cpu = 0;
	अगर (node)
		*node = 0;

	वापस 0;
पूर्ण

दीर्घ अ_लोpu(अचिन्हित *cpu, अचिन्हित *node, काष्ठा अ_लोpu_cache *tcache)
	__attribute__((weak, alias("__vdso_getcpu")));
