<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "sp.h"

#अगर_अघोषित __INLINE_SP__
#समावेश "sp_private.h"
#पूर्ण_अगर /* __INLINE_SP__ */

#समावेश "assert_support.h"

व्योम cnd_sp_irq_enable(
    स्थिर sp_ID_t		ID,
    स्थिर bool		cnd)
अणु
	अगर (cnd) अणु
		sp_ctrl_setbit(ID, SP_IRQ_READY_REG, SP_IRQ_READY_BIT);
		/* Enabling the IRQ immediately triggers an पूर्णांकerrupt, clear it */
		sp_ctrl_setbit(ID, SP_IRQ_CLEAR_REG, SP_IRQ_CLEAR_BIT);
	पूर्ण अन्यथा अणु
		sp_ctrl_clearbit(ID, SP_IRQ_READY_REG, SP_IRQ_READY_BIT);
	पूर्ण
पूर्ण

व्योम sp_get_state(
    स्थिर sp_ID_t			ID,
    sp_state_t				*state,
    sp_stall_t				*stall)
अणु
	hrt_data sc = sp_ctrl_load(ID, SP_SC_REG);

	निश्चित(state);
	निश्चित(stall);

	state->pc = sp_ctrl_load(ID, SP_PC_REG);
	state->status_रेजिस्टर = sc;
	state->is_broken   = (sc & (1U << SP_BROKEN_BIT)) != 0;
	state->is_idle     = (sc & (1U << SP_IDLE_BIT)) != 0;
	state->is_sleeping = (sc & (1U << SP_SLEEPING_BIT)) != 0;
	state->is_stalling = (sc & (1U << SP_STALLING_BIT)) != 0;
	stall->fअगरo0 =
	    !sp_ctrl_getbit(ID, SP_FIFO0_SINK_REG, SP_FIFO0_SINK_BIT);
	stall->fअगरo1 =
	    !sp_ctrl_getbit(ID, SP_FIFO1_SINK_REG, SP_FIFO1_SINK_BIT);
	stall->fअगरo2 =
	    !sp_ctrl_getbit(ID, SP_FIFO2_SINK_REG, SP_FIFO2_SINK_BIT);
	stall->fअगरo3 =
	    !sp_ctrl_getbit(ID, SP_FIFO3_SINK_REG, SP_FIFO3_SINK_BIT);
	stall->fअगरo4 =
	    !sp_ctrl_getbit(ID, SP_FIFO4_SINK_REG, SP_FIFO4_SINK_BIT);
	stall->fअगरo5 =
	    !sp_ctrl_getbit(ID, SP_FIFO5_SINK_REG, SP_FIFO5_SINK_BIT);
	stall->fअगरo6 =
	    !sp_ctrl_getbit(ID, SP_FIFO6_SINK_REG, SP_FIFO6_SINK_BIT);
	stall->fअगरo7 =
	    !sp_ctrl_getbit(ID, SP_FIFO7_SINK_REG, SP_FIFO7_SINK_BIT);
	stall->fअगरo8 =
	    !sp_ctrl_getbit(ID, SP_FIFO8_SINK_REG, SP_FIFO8_SINK_BIT);
	stall->fअगरo9 =
	    !sp_ctrl_getbit(ID, SP_FIFO9_SINK_REG, SP_FIFO9_SINK_BIT);
	stall->fअगरoa =
	    !sp_ctrl_getbit(ID, SP_FIFOA_SINK_REG, SP_FIFOA_SINK_BIT);
	stall->dmem =
	    !sp_ctrl_getbit(ID, SP_DMEM_SINK_REG, SP_DMEM_SINK_BIT);
	stall->control_master =
	    !sp_ctrl_getbit(ID, SP_CTRL_MT_SINK_REG, SP_CTRL_MT_SINK_BIT);
	stall->icache_master =
	    !sp_ctrl_getbit(ID, SP_ICACHE_MT_SINK_REG,
			    SP_ICACHE_MT_SINK_BIT);
पूर्ण
