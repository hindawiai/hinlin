<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
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

#समावेश "platform_support.h"

#समावेश "sh_css_hrt.h"
#समावेश "ia_css_debug.h"

#समावेश "device_access.h"

#घोषणा __INLINE_EVENT__
#समावेश "event_fifo.h"
#घोषणा __INLINE_SP__
#समावेश "sp.h"
#घोषणा __INLINE_ISP__
#समावेश "isp.h"
#घोषणा __INLINE_IRQ__
#समावेश "irq.h"
#घोषणा __INLINE_FIFO_MONITOR__
#समावेश "fifo_monitor.h"

/* System independent */
#समावेश "sh_css_internal.h"

bool sh_css_hrt_प्रणाली_is_idle(व्योम)
अणु
	bool not_idle = false, idle;
	fअगरo_channel_t ch;

	idle = sp_ctrl_getbit(SP0_ID, SP_SC_REG, SP_IDLE_BIT);
	not_idle |= !idle;
	अगर (!idle)
		IA_CSS_WARNING("SP not idle");

	idle = isp_ctrl_getbit(ISP0_ID, ISP_SC_REG, ISP_IDLE_BIT);
	not_idle |= !idle;
	अगर (!idle)
		IA_CSS_WARNING("ISP not idle");

	क्रम (ch = 0; ch < N_FIFO_CHANNEL; ch++) अणु
		fअगरo_channel_state_t state;

		fअगरo_channel_get_state(FIFO_MONITOR0_ID, ch, &state);
		अगर (state.fअगरo_valid) अणु
			IA_CSS_WARNING("FIFO channel %d is not empty", ch);
			not_idle = true;
		पूर्ण
	पूर्ण

	वापस !not_idle;
पूर्ण

पूर्णांक sh_css_hrt_sp_रुको(व्योम)
अणु
	irq_sw_channel_id_t	irq_id = IRQ_SW_CHANNEL0_ID;
	/*
	 * Wait till SP is idle or till there is a SW2 पूर्णांकerrupt
	 * The SW2 पूर्णांकerrupt will be used when frameloop runs on SP
	 * and संकेतs an event with similar meaning as SP idle
	 * (e.g. frame_करोne)
	 */
	जबतक (!sp_ctrl_getbit(SP0_ID, SP_SC_REG, SP_IDLE_BIT) &&
	       ((irq_reg_load(IRQ0_ID,
			      _HRT_IRQ_CONTROLLER_STATUS_REG_IDX) &
		 (1U << (irq_id + IRQ_SW_CHANNEL_OFFSET))) == 0)) अणु
		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण
