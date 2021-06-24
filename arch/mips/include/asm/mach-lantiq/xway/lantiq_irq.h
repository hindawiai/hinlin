<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#अगर_अघोषित _LANTIQ_XWAY_IRQ_H__
#घोषणा _LANTIQ_XWAY_IRQ_H__

#घोषणा INT_NUM_IRQ0		8
#घोषणा INT_NUM_IM0_IRL0	(INT_NUM_IRQ0 + 0)
#घोषणा INT_NUM_IM1_IRL0	(INT_NUM_IRQ0 + 32)
#घोषणा INT_NUM_IM2_IRL0	(INT_NUM_IRQ0 + 64)
#घोषणा INT_NUM_IM3_IRL0	(INT_NUM_IRQ0 + 96)
#घोषणा INT_NUM_IM4_IRL0	(INT_NUM_IRQ0 + 128)
#घोषणा INT_NUM_IM_OFFSET	(INT_NUM_IM1_IRL0 - INT_NUM_IM0_IRL0)

#घोषणा LTQ_DMA_CH0_INT		(INT_NUM_IM2_IRL0)

#घोषणा MAX_IM			5

#पूर्ण_अगर
