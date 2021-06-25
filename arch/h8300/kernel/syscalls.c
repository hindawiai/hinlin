<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/syscalls.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/unistd.h>

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, call) [nr] = (call),

#घोषणा sys_mmap2 sys_mmap_pgoff

यंत्रlinkage पूर्णांक sys_rt_sigवापस(व्योम);

व्योम *_sys_call_table[__NR_syscalls] = अणु
#समावेश <यंत्र/unistd.h>
पूर्ण;
