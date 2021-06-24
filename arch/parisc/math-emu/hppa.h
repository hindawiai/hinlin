<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *
 * Floating-poपूर्णांक emulation code
 *  Copyright (C) 2001 Hewlett-Packard (Paul Bame) <bame@debian.org>
 */

#अगर_घोषित __NO_PA_HDRS
    PA header file -- करो not include this header file क्रम non-PA builds.
#पूर्ण_अगर


/* amount is assumed to be a स्थिरant between 0 and 32 (non-inclusive) */
#घोषणा Shअगरtद्विगुन(left,right,amount,dest)			\
    /* पूर्णांक left, right, amount, dest; */			\
    dest = ((left) << (32-(amount))) | ((अचिन्हित पूर्णांक)(right) >> (amount))

/* amount must be less than 32 */
#घोषणा Variableshअगरtद्विगुन(left,right,amount,dest)		\
    /* अचिन्हित पूर्णांक left, right;  पूर्णांक amount, dest; */		\
    अगर (amount == 0) dest = right;				\
    अन्यथा dest = ((((अचिन्हित) left)&0x7fffffff) << (32-(amount))) |	\
          ((अचिन्हित) right >> (amount))

/* amount must be between 0 and 32 (non-inclusive) */
#घोषणा Variable_shअगरt_द्विगुन(left,right,amount,dest)		\
    /* अचिन्हित पूर्णांक left, right;  पूर्णांक amount, dest; */		\
    dest = (left << (32-(amount))) | ((अचिन्हित) right >> (amount))
