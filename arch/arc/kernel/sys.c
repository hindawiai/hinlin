<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/syscalls.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/unistd.h>

#समावेश <यंत्र/syscalls.h>

#घोषणा sys_clone	sys_clone_wrapper
#घोषणा sys_clone3	sys_clone3_wrapper

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, call) [nr] = (call),

व्योम *sys_call_table[NR_syscalls] = अणु
	[0 ... NR_syscalls-1] = sys_ni_syscall,
#समावेश <यंत्र/unistd.h>
पूर्ण;
