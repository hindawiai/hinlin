<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*---------------------------------------------------------------------------+
 |  fpu_यंत्र.h                                                                |
 |                                                                           |
 | Copyright (C) 1992,1995,1997                                              |
 |                       W. Metzenthen, 22 Parker St, Ormond, Vic 3163,      |
 |                       Australia.  E-mail billm@suburbia.net               |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#अगर_अघोषित _FPU_ASM_H_
#घोषणा _FPU_ASM_H_

#समावेश <linux/linkage.h>

#घोषणा	EXCEPTION	FPU_exception

#घोषणा PARAM1	8(%ebp)
#घोषणा	PARAM2	12(%ebp)
#घोषणा	PARAM3	16(%ebp)
#घोषणा	PARAM4	20(%ebp)
#घोषणा	PARAM5	24(%ebp)
#घोषणा	PARAM6	28(%ebp)
#घोषणा	PARAM7	32(%ebp)

#घोषणा SIGL_OFFSET 0
#घोषणा	EXP(x)	8(x)
#घोषणा SIG(x)	SIGL_OFFSET##(x)
#घोषणा	SIGL(x)	SIGL_OFFSET##(x)
#घोषणा	SIGH(x)	4(x)

#पूर्ण_अगर /* _FPU_ASM_H_ */
