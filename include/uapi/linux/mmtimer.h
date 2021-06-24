<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Intel Mulसमयdia Timer device पूर्णांकerface
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2001-2004 Silicon Graphics, Inc.  All rights reserved.
 *
 * This file should define an पूर्णांकerface compatible with the IA-PC Mulसमयdia
 * Timers Draft Specअगरication (rev. 0.97) from Intel.  Note that some
 * hardware may not be able to safely export its रेजिस्टरs to userspace,
 * so the ioctl पूर्णांकerface should support all necessary functionality.
 *
 * 11/01/01 - jbarnes - initial revision
 * 9/10/04 - Christoph Lameter - हटाओ पूर्णांकerrupt support
 * 9/17/04 - jbarnes - हटाओ test program, move some #घोषणाs to the driver
 */

#अगर_अघोषित _LINUX_MMTIMER_H
#घोषणा _LINUX_MMTIMER_H

/*
 * Breakकरोwn of the ioctl's available.  An 'optional' next to the command
 * indicates that supporting this command is optional, जबतक 'required'
 * commands must be implemented अगर conक्रमmance is desired.
 *
 * MMTIMER_GETOFFSET - optional
 *   Should वापस the offset (relative to the start of the page where the
 *   रेजिस्टरs are mapped) क्रम the counter in question.
 *
 * MMTIMER_GETRES - required
 *   The resolution of the घड़ी in femto (10^-15) seconds
 *
 * MMTIMER_GETFREQ - required
 *   Frequency of the घड़ी in Hz
 *
 * MMTIMER_GETBITS - required
 *   Number of bits in the घड़ी's counter
 *
 * MMTIMER_MMAPAVAIL - required
 *   Returns nonzero अगर the रेजिस्टरs can be mmap'd पूर्णांकo userspace, 0 otherwise
 *
 * MMTIMER_GETCOUNTER - required
 *   Gets the current value in the counter
 */
#घोषणा MMTIMER_IOCTL_BASE 'm'

#घोषणा MMTIMER_GETOFFSET _IO(MMTIMER_IOCTL_BASE, 0)
#घोषणा MMTIMER_GETRES _IOR(MMTIMER_IOCTL_BASE, 1, अचिन्हित दीर्घ)
#घोषणा MMTIMER_GETFREQ _IOR(MMTIMER_IOCTL_BASE, 2, अचिन्हित दीर्घ)
#घोषणा MMTIMER_GETBITS _IO(MMTIMER_IOCTL_BASE, 4)
#घोषणा MMTIMER_MMAPAVAIL _IO(MMTIMER_IOCTL_BASE, 6)
#घोषणा MMTIMER_GETCOUNTER _IOR(MMTIMER_IOCTL_BASE, 9, अचिन्हित दीर्घ)

#पूर्ण_अगर /* _LINUX_MMTIMER_H */
