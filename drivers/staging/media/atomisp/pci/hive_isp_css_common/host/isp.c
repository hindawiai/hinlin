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

#समावेश <linux/delay.h>

#समावेश <प्रणाली_global.h>
#समावेश "isp.h"

#अगर_अघोषित __INLINE_ISP__
#समावेश "isp_private.h"
#पूर्ण_अगर /* __INLINE_ISP__ */

#समावेश "assert_support.h"

व्योम cnd_isp_irq_enable(
    स्थिर isp_ID_t		ID,
    स्थिर bool		cnd)
अणु
	अगर (cnd) अणु
		isp_ctrl_setbit(ID, ISP_IRQ_READY_REG, ISP_IRQ_READY_BIT);
		/* Enabling the IRQ immediately triggers an पूर्णांकerrupt, clear it */
		isp_ctrl_setbit(ID, ISP_IRQ_CLEAR_REG, ISP_IRQ_CLEAR_BIT);
	पूर्ण अन्यथा अणु
		isp_ctrl_clearbit(ID, ISP_IRQ_READY_REG,
				  ISP_IRQ_READY_BIT);
	पूर्ण
	वापस;
पूर्ण

व्योम isp_get_state(
    स्थिर isp_ID_t		ID,
    isp_state_t			*state,
    isp_stall_t			*stall)
अणु
	hrt_data sc = isp_ctrl_load(ID, ISP_SC_REG);

	निश्चित(state);
	निश्चित(stall);

#अगर defined(_hrt_sysmem_ident_address)
	/* Patch to aव्योम compiler unused symbol warning in C_RUN build */
	(व्योम)__hrt_sysmem_ident_address;
	(व्योम)_hrt_sysmem_map_var;
#पूर्ण_अगर

	state->pc = isp_ctrl_load(ID, ISP_PC_REG);
	state->status_रेजिस्टर = sc;
	state->is_broken = isp_ctrl_getbit(ID, ISP_SC_REG, ISP_BROKEN_BIT);
	state->is_idle = isp_ctrl_getbit(ID, ISP_SC_REG, ISP_IDLE_BIT);
	state->is_sleeping = isp_ctrl_getbit(ID, ISP_SC_REG, ISP_SLEEPING_BIT);
	state->is_stalling = isp_ctrl_getbit(ID, ISP_SC_REG, ISP_STALLING_BIT);
	stall->stat_ctrl =
	    !isp_ctrl_getbit(ID, ISP_CTRL_SINK_REG, ISP_CTRL_SINK_BIT);
	stall->pmem =
	    !isp_ctrl_getbit(ID, ISP_PMEM_SINK_REG, ISP_PMEM_SINK_BIT);
	stall->dmem =
	    !isp_ctrl_getbit(ID, ISP_DMEM_SINK_REG, ISP_DMEM_SINK_BIT);
	stall->vmem =
	    !isp_ctrl_getbit(ID, ISP_VMEM_SINK_REG, ISP_VMEM_SINK_BIT);
	stall->fअगरo0 =
	    !isp_ctrl_getbit(ID, ISP_FIFO0_SINK_REG, ISP_FIFO0_SINK_BIT);
	stall->fअगरo1 =
	    !isp_ctrl_getbit(ID, ISP_FIFO1_SINK_REG, ISP_FIFO1_SINK_BIT);
	stall->fअगरo2 =
	    !isp_ctrl_getbit(ID, ISP_FIFO2_SINK_REG, ISP_FIFO2_SINK_BIT);
	stall->fअगरo3 =
	    !isp_ctrl_getbit(ID, ISP_FIFO3_SINK_REG, ISP_FIFO3_SINK_BIT);
	stall->fअगरo4 =
	    !isp_ctrl_getbit(ID, ISP_FIFO4_SINK_REG, ISP_FIFO4_SINK_BIT);
	stall->fअगरo5 =
	    !isp_ctrl_getbit(ID, ISP_FIFO5_SINK_REG, ISP_FIFO5_SINK_BIT);
	stall->fअगरo6 =
	    !isp_ctrl_getbit(ID, ISP_FIFO6_SINK_REG, ISP_FIFO6_SINK_BIT);
	stall->vamem1 =
	    !isp_ctrl_getbit(ID, ISP_VAMEM1_SINK_REG, ISP_VAMEM1_SINK_BIT);
	stall->vamem2 =
	    !isp_ctrl_getbit(ID, ISP_VAMEM2_SINK_REG, ISP_VAMEM2_SINK_BIT);
	stall->vamem3 =
	    !isp_ctrl_getbit(ID, ISP_VAMEM3_SINK_REG, ISP_VAMEM3_SINK_BIT);
	stall->hmem =
	    !isp_ctrl_getbit(ID, ISP_HMEM_SINK_REG, ISP_HMEM_SINK_BIT);
	/*
		stall->icache_master =
			!isp_ctrl_getbit(ID, ISP_ICACHE_MT_SINK_REG,
				ISP_ICACHE_MT_SINK_BIT);
	 */
	वापस;
पूर्ण

/* ISP functions to control the ISP state from the host, even in crun. */

/* Inspect पढ़ोiness of an ISP indexed by ID */
अचिन्हित पूर्णांक isp_is_पढ़ोy(isp_ID_t ID)
अणु
	निश्चित(ID < N_ISP_ID);
	वापस isp_ctrl_getbit(ID, ISP_SC_REG, ISP_IDLE_BIT);
पूर्ण

/* Inspect sleeping of an ISP indexed by ID */
अचिन्हित पूर्णांक isp_is_sleeping(isp_ID_t ID)
अणु
	निश्चित(ID < N_ISP_ID);
	वापस isp_ctrl_getbit(ID, ISP_SC_REG, ISP_SLEEPING_BIT);
पूर्ण

/* To be called by the host immediately beक्रमe starting ISP ID. */
व्योम isp_start(isp_ID_t ID)
अणु
	निश्चित(ID < N_ISP_ID);
पूर्ण

/* Wake up ISP ID. */
व्योम isp_wake(isp_ID_t ID)
अणु
	निश्चित(ID < N_ISP_ID);
	isp_ctrl_setbit(ID, ISP_SC_REG, ISP_START_BIT);
	udelay(1);
पूर्ण
