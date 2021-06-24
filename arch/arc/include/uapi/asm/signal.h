<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Amit Bhor, Sameer Dhavale: Codito Technologies 2004
 */

#अगर_अघोषित _ASM_ARC_SIGNAL_H
#घोषणा _ASM_ARC_SIGNAL_H

/*
 * This is much needed क्रम ARC sigवापस optimization.
 * This allows uClibc to piggback the addr of a sigवापस stub in sigaction,
 * which allows sigवापस based re-entry पूर्णांकo kernel after handling संकेत.
 * W/o this kernel needs to "synthesize" the sigवापस trampoline on user
 * mode stack which in turn क्रमces the following:
 * -TLB Flush (after making the stack page executable)
 * -Cache line Flush (to make I/D Cache lines coherent)
 */
#घोषणा SA_RESTORER	0x04000000

#समावेश <यंत्र-generic/संकेत.स>

#पूर्ण_अगर /* _ASM_ARC_SIGNAL_H */
