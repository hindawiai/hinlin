<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/ptrace.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _UAPI_XTENSA_PTRACE_H
#घोषणा _UAPI_XTENSA_PTRACE_H

#समावेश <linux/types.h>

/* Registers used by strace */

#घोषणा REG_A_BASE	0x0000
#घोषणा REG_AR_BASE	0x0100
#घोषणा REG_PC		0x0020
#घोषणा REG_PS		0x02e6
#घोषणा REG_WB		0x0248
#घोषणा REG_WS		0x0249
#घोषणा REG_LBEG	0x0200
#घोषणा REG_LEND	0x0201
#घोषणा REG_LCOUNT	0x0202
#घोषणा REG_SAR		0x0203

#घोषणा SYSCALL_NR	0x00ff

/* Other PTRACE_ values defined in <linux/ptrace.h> using values 0-9,16,17,24 */

#घोषणा PTRACE_GETREGS		12
#घोषणा PTRACE_SETREGS		13
#घोषणा PTRACE_GETXTREGS	18
#घोषणा PTRACE_SETXTREGS	19
#घोषणा PTRACE_GETHBPREGS	20
#घोषणा PTRACE_SETHBPREGS	21

#अगर_अघोषित __ASSEMBLY__

काष्ठा user_pt_regs अणु
	__u32 pc;
	__u32 ps;
	__u32 lbeg;
	__u32 lend;
	__u32 lcount;
	__u32 sar;
	__u32 winकरोwstart;
	__u32 winकरोwbase;
	__u32 thपढ़ोptr;
	__u32 syscall;
	__u32 reserved[6 + 48];
	__u32 a[64];
पूर्ण;

#पूर्ण_अगर
#पूर्ण_अगर /* _UAPI_XTENSA_PTRACE_H */
