<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/syscalls.h>
#समावेश <यंत्र/syscalls.h>

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, call)[nr] = (call),

#घोषणा sys_fadvise64_64 sys_csky_fadvise64_64
व्योम * स्थिर sys_call_table[__NR_syscalls] __page_aligned_data = अणु
	[0 ... __NR_syscalls - 1] = sys_ni_syscall,
#समावेश <यंत्र/unistd.h>
पूर्ण;
