<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005 MIPS Technologies, Inc.  All rights reserved.
 */

#अगर_अघोषित _ASM_MIPS_BOARDS_SIM_H
#घोषणा _ASM_MIPS_BOARDS_SIM_H

#घोषणा STATS_ON	1
#घोषणा STATS_OFF	2
#घोषणा STATS_CLEAR	3
#घोषणा STATS_DUMP	4
#घोषणा TRACE_ON		5
#घोषणा TRACE_OFF	6


#घोषणा simcfg(code)						\
(अणु					   \
	__यंत्र__	 __अस्थिर__( \
	"sltiu $0,$0, %0" \
		::"i"(code)					\
		); \
पूर्ण)



#पूर्ण_अगर
