<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*---------------------------------------------------------------------------+
 |  status_w.h                                                               |
 |                                                                           |
 | Copyright (C) 1992,1993                                                   |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#अगर_अघोषित _STATUS_H_
#घोषणा _STATUS_H_

#समावेश "fpu_emu.h"		/* क्रम definition of PECULIAR_486 */

#अगर_घोषित __ASSEMBLY__
#घोषणा	Const__(x)	$##x
#अन्यथा
#घोषणा	Const__(x)	x
#पूर्ण_अगर

#घोषणा SW_Backward    	Const__(0x8000)	/* backward compatibility */
#घोषणा SW_C3		Const__(0x4000)	/* condition bit 3 */
#घोषणा SW_Top		Const__(0x3800)	/* top of stack */
#घोषणा SW_Top_Shअगरt 	Const__(11)	/* shअगरt क्रम top of stack bits */
#घोषणा SW_C2		Const__(0x0400)	/* condition bit 2 */
#घोषणा SW_C1		Const__(0x0200)	/* condition bit 1 */
#घोषणा SW_C0		Const__(0x0100)	/* condition bit 0 */
#घोषणा SW_Summary     	Const__(0x0080)	/* exception summary */
#घोषणा SW_Stack_Fault	Const__(0x0040)	/* stack fault */
#घोषणा SW_Precision   	Const__(0x0020)	/* loss of precision */
#घोषणा SW_Underflow   	Const__(0x0010)	/* underflow */
#घोषणा SW_Overflow    	Const__(0x0008)	/* overflow */
#घोषणा SW_Zero_Div    	Const__(0x0004)	/* भागide by zero */
#घोषणा SW_Denorm_Op   	Const__(0x0002)	/* denormalized opeअक्रम */
#घोषणा SW_Invalid     	Const__(0x0001)	/* invalid operation */

#घोषणा SW_Exc_Mask     Const__(0x27f)	/* Status word exception bit mask */

#अगर_अघोषित __ASSEMBLY__

#घोषणा COMP_A_gt_B	1
#घोषणा COMP_A_eq_B	2
#घोषणा COMP_A_lt_B	3
#घोषणा COMP_No_Comp	4
#घोषणा COMP_Denormal   0x20
#घोषणा COMP_NaN	0x40
#घोषणा COMP_SNaN	0x80

#घोषणा status_word() \
  ((partial_status & ~SW_Top & 0xffff) | ((top << SW_Top_Shअगरt) & SW_Top))
अटल अंतरभूत व्योम setcc(पूर्णांक cc)
अणु
	partial_status &= ~(SW_C0 | SW_C1 | SW_C2 | SW_C3);
	partial_status |= (cc) & (SW_C0 | SW_C1 | SW_C2 | SW_C3);
पूर्ण

#अगर_घोषित PECULIAR_486
   /* Default, this conveys no inक्रमmation, but an 80486 करोes it. */
   /* Clear the SW_C1 bit, "other bits undefined". */
#  define clear_C1()  अणु partial_status &= ~SW_C1; पूर्ण
# अन्यथा
#  define clear_C1()
#पूर्ण_अगर /* PECULIAR_486 */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _STATUS_H_ */
