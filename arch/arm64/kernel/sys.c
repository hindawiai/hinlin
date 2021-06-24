<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AArch64-specअगरic प्रणाली calls implementation
 *
 * Copyright (C) 2012 ARM Ltd.
 * Author: Catalin Marinas <catalin.marinas@arm.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/syscall.h>

SYSCALL_DEFINE6(mmap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
		अचिन्हित दीर्घ, fd, अचिन्हित दीर्घ, off)
अणु
	अगर (offset_in_page(off) != 0)
		वापस -EINVAL;

	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, off >> PAGE_SHIFT);
पूर्ण

SYSCALL_DEFINE1(arm64_personality, अचिन्हित पूर्णांक, personality)
अणु
	अगर (personality(personality) == PER_LINUX32 &&
		!प्रणाली_supports_32bit_el0())
		वापस -EINVAL;
	वापस ksys_personality(personality);
पूर्ण

यंत्रlinkage दीर्घ sys_ni_syscall(व्योम);

यंत्रlinkage दीर्घ __arm64_sys_ni_syscall(स्थिर काष्ठा pt_regs *__unused)
अणु
	वापस sys_ni_syscall();
पूर्ण

/*
 * Wrappers to pass the pt_regs argument.
 */
#घोषणा __arm64_sys_personality		__arm64_sys_arm64_personality

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, sym)	यंत्रlinkage दीर्घ __arm64_##sym(स्थिर काष्ठा pt_regs *);
#समावेश <यंत्र/unistd.h>

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, sym)	[nr] = __arm64_##sym,

स्थिर syscall_fn_t sys_call_table[__NR_syscalls] = अणु
	[0 ... __NR_syscalls - 1] = __arm64_sys_ni_syscall,
#समावेश <यंत्र/unistd.h>
पूर्ण;
