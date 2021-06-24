<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019  Arm Limited
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */

#अगर_अघोषित COMPILER_H
#घोषणा COMPILER_H

#घोषणा __always_unused __attribute__((__unused__))
#घोषणा __noवापस __attribute__((__noवापस__))
#घोषणा __unreachable() __builtin_unreachable()

/* curse(e) has value e, but the compiler cannot assume so */
#घोषणा curse(e) (अणु				\
	__typeof__(e) __curse_e = (e);		\
	यंत्र ("" : "+r" (__curse_e));		\
	__curse_e;				\
पूर्ण)

#पूर्ण_अगर /* ! COMPILER_H */
