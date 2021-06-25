<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*---------------------------------------------------------------------------+
 |  exception.h                                                              |
 |                                                                           |
 | Copyright (C) 1992    W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#अगर_अघोषित _EXCEPTION_H_
#घोषणा _EXCEPTION_H_

#अगर_घोषित __ASSEMBLY__
#घोषणा	Const_(x)	$##x
#अन्यथा
#घोषणा	Const_(x)	x
#पूर्ण_अगर

#अगर_अघोषित SW_C1
#समावेश "fpu_emu.h"
#पूर्ण_अगर /* SW_C1 */

#घोषणा FPU_BUSY        Const_(0x8000)	/* FPU busy bit (8087 compatibility) */
#घोषणा EX_ErrorSummary Const_(0x0080)	/* Error summary status */
/* Special exceptions: */
#घोषणा	EX_INTERNAL	Const_(0x8000)	/* Internal error in wm-FPU-emu */
#घोषणा EX_StackOver	Const_(0x0041|SW_C1)	/* stack overflow */
#घोषणा EX_StackUnder	Const_(0x0041)	/* stack underflow */
/* Exception flags: */
#घोषणा EX_Precision	Const_(0x0020)	/* loss of precision */
#घोषणा EX_Underflow	Const_(0x0010)	/* underflow */
#घोषणा EX_Overflow	Const_(0x0008)	/* overflow */
#घोषणा EX_ZeroDiv	Const_(0x0004)	/* भागide by zero */
#घोषणा EX_Denormal	Const_(0x0002)	/* denormalized opeअक्रम */
#घोषणा EX_Invalid	Const_(0x0001)	/* invalid operation */

#घोषणा PRECISION_LOST_UP    Const_((EX_Precision | SW_C1))
#घोषणा PRECISION_LOST_DOWN  Const_(EX_Precision)

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित DEBUG
#घोषणा	EXCEPTION(x)	अणु prपूर्णांकk("exception in %s at line %d\n", \
	__खाता__, __LINE__); FPU_exception(x); पूर्ण
#अन्यथा
#घोषणा	EXCEPTION(x)	FPU_exception(x)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _EXCEPTION_H_ */
