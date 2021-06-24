<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 96, 98, 99, 2000 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_RESOURCE_H
#घोषणा _ASM_RESOURCE_H


/*
 * These five resource limit IDs have a MIPS/Linux-specअगरic ordering,
 * the rest comes from the generic header:
 */
#घोषणा RLIMIT_NOखाता		5	/* max number of खोलो files */
#घोषणा RLIMIT_AS		6	/* address space limit */
#घोषणा RLIMIT_RSS		7	/* max resident set size */
#घोषणा RLIMIT_NPROC		8	/* max number of processes */
#घोषणा RLIMIT_MEMLOCK		9	/* max locked-in-memory address space */

/*
 * SuS says limits have to be अचिन्हित.
 * Which makes a ton more sense anyway,
 * but we keep the old value on MIPS32,
 * क्रम compatibility:
 */
#अगर_अघोषित __mips64
# define RLIM_अनन्त		0x7fffffffUL
#पूर्ण_अगर

#समावेश <यंत्र-generic/resource.h>

#पूर्ण_अगर /* _ASM_RESOURCE_H */
