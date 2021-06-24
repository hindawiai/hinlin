<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*---------------------------------------------------------------------------+
 |  control_w.h                                                              |
 |                                                                           |
 | Copyright (C) 1992,1993                                                   |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail   billm@vaxc.cc.monash.edu.au    |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#अगर_अघोषित _CONTROLW_H_
#घोषणा _CONTROLW_H_

#अगर_घोषित __ASSEMBLY__
#घोषणा	_Const_(x)	$##x
#अन्यथा
#घोषणा	_Const_(x)	x
#पूर्ण_अगर

#घोषणा CW_RC		_Const_(0x0C00)	/* rounding control */
#घोषणा CW_PC		_Const_(0x0300)	/* precision control */

#घोषणा CW_Precision	Const_(0x0020)	/* loss of precision mask */
#घोषणा CW_Underflow	Const_(0x0010)	/* underflow mask */
#घोषणा CW_Overflow	Const_(0x0008)	/* overflow mask */
#घोषणा CW_ZeroDiv	Const_(0x0004)	/* भागide by zero mask */
#घोषणा CW_Denormal	Const_(0x0002)	/* denormalized opeअक्रम mask */
#घोषणा CW_Invalid	Const_(0x0001)	/* invalid operation mask */

#घोषणा CW_Exceptions  	_Const_(0x003f)	/* all masks */

#घोषणा RC_RND		_Const_(0x0000)
#घोषणा RC_DOWN		_Const_(0x0400)
#घोषणा RC_UP		_Const_(0x0800)
#घोषणा RC_CHOP		_Const_(0x0C00)

/* p 15-5: Precision control bits affect only the following:
   ADD, SUB(R), MUL, DIV(R), and SQRT */
#घोषणा PR_24_BITS        _Const_(0x000)
#घोषणा PR_53_BITS        _Const_(0x200)
#घोषणा PR_64_BITS        _Const_(0x300)
#घोषणा PR_RESERVED_BITS  _Const_(0x100)
/* FULL_PRECISION simulates all exceptions masked */
#घोषणा FULL_PRECISION  (PR_64_BITS | RC_RND | 0x3f)

#पूर्ण_अगर /* _CONTROLW_H_ */
