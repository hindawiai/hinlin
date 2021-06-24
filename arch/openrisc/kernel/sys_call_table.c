<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC sys_call_table.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#समावेश <linux/syscalls.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/unistd.h>

#समावेश <यंत्र/syscalls.h>

#अघोषित __SYSCALL
#घोषणा __SYSCALL(nr, call) [nr] = (call),

व्योम *sys_call_table[__NR_syscalls] = अणु
#समावेश <यंत्र/unistd.h>
पूर्ण;
