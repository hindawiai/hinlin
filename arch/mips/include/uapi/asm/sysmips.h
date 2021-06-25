<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Definitions क्रम the MIPS sysmips(2) call
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SYSMIPS_H
#घोषणा _ASM_SYSMIPS_H

/*
 * Commands क्रम the sysmips(2) call
 *
 * sysmips(2) is deprecated - though some existing software uses it.
 * We only support the following commands.
 */
#घोषणा SETNAME			   1	/* set hostname			 */
#घोषणा FLUSH_CACHE		   3	/* ग_लिखोback and invalidate caches */
#घोषणा MIPS_FIXADE		   7	/* control address error fixing	 */
#घोषणा MIPS_RDNVRAM		  10	/* पढ़ो NVRAM */
#घोषणा MIPS_ATOMIC_SET		2001	/* atomically set variable	 */

#पूर्ण_अगर /* _ASM_SYSMIPS_H */
