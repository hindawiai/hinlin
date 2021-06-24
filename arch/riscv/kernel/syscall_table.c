<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Arnd Bergmann <arnd@arndb.de>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#समावेश <linux/linkage.h>
#समावेश <linux/syscalls.h>
#समावेश <यंत्र-generic/syscalls.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/syscall.h>

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, call)	[nr] = (call),

व्योम * स्थिर sys_call_table[__NR_syscalls] = अणु
	[0 ... __NR_syscalls - 1] = sys_ni_syscall,
#समावेश <यंत्र/unistd.h>
पूर्ण;
