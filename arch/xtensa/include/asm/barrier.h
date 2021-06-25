<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2012 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_SYSTEM_H
#घोषणा _XTENSA_SYSTEM_H

#समावेश <यंत्र/core.h>

#घोषणा mb()  (अणु __यंत्र__ __अस्थिर__("memw" : : : "memory"); पूर्ण)
#घोषणा rmb() barrier()
#घोषणा wmb() mb()

#अगर XCHAL_HAVE_S32C1I
#घोषणा __smp_mb__beक्रमe_atomic()		barrier()
#घोषणा __smp_mb__after_atomic()		barrier()
#पूर्ण_अगर

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* _XTENSA_SYSTEM_H */
