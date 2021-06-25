<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/syscalls.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/unistd.h>
#समावेश <यंत्र/syscalls.h>

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, call) [nr] = (call),

#घोषणा sys_rt_sigवापस sys_rt_sigवापस_wrapper
#घोषणा sys_fadvise64_64 sys_fadvise64_64_wrapper
व्योम *sys_call_table[__NR_syscalls] __aligned(8192) = अणु
	[0 ... __NR_syscalls - 1] = sys_ni_syscall,
#समावेश <यंत्र/unistd.h>
पूर्ण;
