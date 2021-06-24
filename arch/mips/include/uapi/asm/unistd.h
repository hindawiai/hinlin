<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 96, 97, 98, 99, 2000 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 *
 * Changed प्रणाली calls macros _syscall5 - _syscall7 to push args 5 to 7 onto
 * the stack. Robin Farine क्रम ACN S.A, Copyright (C) 1996 by ACN S.A
 */
#अगर_अघोषित _UAPI_ASM_UNISTD_H
#घोषणा _UAPI_ASM_UNISTD_H

#समावेश <यंत्र/sgidefs.h>

#अगर _MIPS_SIM == _MIPS_SIM_ABI32

#घोषणा __NR_Linux	4000
#समावेश <यंत्र/unistd_o32.h>

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#अगर _MIPS_SIM == _MIPS_SIM_ABI64

#घोषणा __NR_Linux	5000
#समावेश <यंत्र/unistd_n64.h>

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI64 */

#अगर _MIPS_SIM == _MIPS_SIM_NABI32

#घोषणा __NR_Linux	6000
#समावेश <यंत्र/unistd_n32.h>

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_NABI32 */

#पूर्ण_अगर /* _UAPI_ASM_UNISTD_H */
