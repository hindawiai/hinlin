<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * System call table क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/syscalls.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/unistd.h>

#समावेश <यंत्र/syscall.h>

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, call) [nr] = (call),

व्योम *sys_call_table[__NR_syscalls] = अणु
#समावेश <यंत्र/unistd.h>
पूर्ण;
