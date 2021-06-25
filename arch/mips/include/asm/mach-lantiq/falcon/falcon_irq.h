<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2010 Thomas Langer <thomas.langer@lantiq.com>
 */

#अगर_अघोषित _FALCON_IRQ__
#घोषणा _FALCON_IRQ__

#घोषणा INT_NUM_IRQ0			8
#घोषणा INT_NUM_IM0_IRL0		(INT_NUM_IRQ0 + 0)
#घोषणा INT_NUM_IM1_IRL0		(INT_NUM_IM0_IRL0 + 32)
#घोषणा INT_NUM_IM2_IRL0		(INT_NUM_IM1_IRL0 + 32)
#घोषणा INT_NUM_IM3_IRL0		(INT_NUM_IM2_IRL0 + 32)
#घोषणा INT_NUM_IM4_IRL0		(INT_NUM_IM3_IRL0 + 32)
#घोषणा INT_NUM_EXTRA_START		(INT_NUM_IM4_IRL0 + 32)
#घोषणा INT_NUM_IM_OFFSET		(INT_NUM_IM1_IRL0 - INT_NUM_IM0_IRL0)

#घोषणा MAX_IM			5

#पूर्ण_अगर /* _FALCON_IRQ__ */
