<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 1995, 1996, 1999 by Ralf Baechle
 * Copyright (C) 2008 Wind River Systems,
 *   written by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _UAPI_ASM_TYPES_H
#घोषणा _UAPI_ASM_TYPES_H

/*
 * We करोn't use पूर्णांक-l64.h क्रम the kernel anymore but still use it क्रम
 * userspace to aव्योम code changes.
 *
 * However, some user programs (e.g. perf) may not want this. They can
 * flag __SANE_USERSPACE_TYPES__ to get पूर्णांक-ll64.h here.
 */
#अगर_अघोषित __KERNEL__
# अगर _MIPS_SZLONG == 64 && !defined(__SANE_USERSPACE_TYPES__)
#  include <यंत्र-generic/पूर्णांक-l64.h>
# अन्यथा
#  include <यंत्र-generic/पूर्णांक-ll64.h>
# endअगर
#पूर्ण_अगर


#पूर्ण_अगर /* _UAPI_ASM_TYPES_H */
