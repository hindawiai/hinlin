<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/types.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _UAPI_XTENSA_TYPES_H
#घोषणा _UAPI_XTENSA_TYPES_H

#समावेश <यंत्र-generic/पूर्णांक-ll64.h>

#अगर_घोषित __ASSEMBLY__
# define __XTENSA_UL(x)		(x)
# define __XTENSA_UL_CONST(x)	x
#अन्यथा
# define __XTENSA_UL(x)		((अचिन्हित दीर्घ)(x))
# define ___XTENSA_UL_CONST(x)	x##UL
# define __XTENSA_UL_CONST(x)	___XTENSA_UL_CONST(x)
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_XTENSA_TYPES_H */
