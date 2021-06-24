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

#समावेश "fifo_monitor.h"

#समावेश <type_support.h>
#समावेश "device_access.h"

#समावेश <bits.h>

#समावेश "gp_device.h"

#समावेश "assert_support.h"

#अगर_अघोषित __INLINE_FIFO_MONITOR__
#घोषणा STORAGE_CLASS_FIFO_MONITOR_DATA अटल स्थिर
#अन्यथा
#घोषणा STORAGE_CLASS_FIFO_MONITOR_DATA स्थिर
#पूर्ण_अगर /* __INLINE_FIFO_MONITOR__ */

STORAGE_CLASS_FIFO_MONITOR_DATA अचिन्हित पूर्णांक FIFO_SWITCH_ADDR[N_FIFO_SWITCH] = अणु
	_REG_GP_SWITCH_IF_ADDR,
	_REG_GP_SWITCH_GDC1_ADDR,
	_REG_GP_SWITCH_GDC2_ADDR
पूर्ण;

#अगर_अघोषित __INLINE_FIFO_MONITOR__
#समावेश "fifo_monitor_private.h"
#पूर्ण_अगर /* __INLINE_FIFO_MONITOR__ */

अटल अंतरभूत bool fअगरo_monitor_status_valid(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक			reg,
    स्थिर अचिन्हित पूर्णांक			port_id);

अटल अंतरभूत bool fअगरo_monitor_status_accept(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक			reg,
    स्थिर अचिन्हित पूर्णांक			port_id);

व्योम fअगरo_channel_get_state(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर fअगरo_channel_t		channel_id,
    fअगरo_channel_state_t		*state)
अणु
	निश्चित(channel_id < N_FIFO_CHANNEL);
	निश्चित(state);

	चयन (channel_id) अणु
	हाल FIFO_CHANNEL_ISP0_TO_SP0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_SP); /* ISP_STR_MON_PORT_ISP2SP */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_SP);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_ISP); /* ISP_STR_MON_PORT_SP2ISP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_ISP);
		अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_ISP0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_ISP); /* ISP_STR_MON_PORT_SP2ISP */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_ISP);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_SP); /* ISP_STR_MON_PORT_ISP2SP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_SP);
		अवरोध;
	हाल FIFO_CHANNEL_ISP0_TO_IF0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_PIF_A); /* ISP_STR_MON_PORT_ISP2PIFA */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_PIF_A);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_PIF_A); /* MOD_STR_MON_PORT_CELLS2PIFA */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_PIF_A);
		अवरोध;
	हाल FIFO_CHANNEL_IF0_TO_ISP0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_PIF_A); /* MOD_STR_MON_PORT_PIFA2CELLS */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_PIF_A);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_PIF_A); /* ISP_STR_MON_PORT_PIFA2ISP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_PIF_A);
		अवरोध;
	हाल FIFO_CHANNEL_ISP0_TO_IF1:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_PIF_B); /* ISP_STR_MON_PORT_ISP2PIFA */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_PIF_B);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_PIF_B); /* MOD_STR_MON_PORT_CELLS2PIFB */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_PIF_B);
		अवरोध;
	हाल FIFO_CHANNEL_IF1_TO_ISP0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_PIF_B); /* MOD_STR_MON_PORT_PIFB2CELLS */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_PIF_B);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_PIF_B); /* ISP_STR_MON_PORT_PIFB2ISP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_PIF_B);
		अवरोध;
	हाल FIFO_CHANNEL_ISP0_TO_DMA0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_DMA); /* ISP_STR_MON_PORT_ISP2DMA */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_DMA);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_DMA_FR_ISP); /* MOD_STR_MON_PORT_ISP2DMA */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_DMA_FR_ISP);
		अवरोध;
	हाल FIFO_CHANNEL_DMA0_TO_ISP0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_DMA2ISP); /* MOD_STR_MON_PORT_DMA2ISP */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_DMA2ISP);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_DMA); /* ISP_STR_MON_PORT_DMA2ISP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_DMA);
		अवरोध;
	हाल FIFO_CHANNEL_ISP0_TO_GDC0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_GDC); /* ISP_STR_MON_PORT_ISP2GDC1 */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_GDC);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_GDC); /* MOD_STR_MON_PORT_CELLS2GDC1 */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_GDC);
		अवरोध;
	हाल FIFO_CHANNEL_GDC0_TO_ISP0:
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_GDC); /* MOD_STR_MON_PORT_GDC12CELLS */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_GDC);
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_GDC); /* ISP_STR_MON_PORT_GDC12ISP */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_GDC);
		अवरोध;
	हाल FIFO_CHANNEL_ISP0_TO_GDC1:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_ISP2GDC2);
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_ISP2GDC2);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_CELLS2GDC2);
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_CELLS2GDC2);
		अवरोध;
	हाल FIFO_CHANNEL_GDC1_TO_ISP0:
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_GDC22CELLS);
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_GDC22CELLS);
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_GDC22ISP);
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_GDC22ISP);
		अवरोध;
	हाल FIFO_CHANNEL_ISP0_TO_HOST0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_GPD); /* ISP_STR_MON_PORT_ISP2GPD */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_SND_GPD);
		अणु
			hrt_data	value = ia_css_device_load_uपूर्णांक32(0x0000000000380014ULL);

			state->fअगरo_valid  = !_hrt_get_bit(value, 0);
			state->sink_accept = false; /* no monitor connected */
		पूर्ण
		अवरोध;
	हाल FIFO_CHANNEL_HOST0_TO_ISP0: अणु
		hrt_data	value = ia_css_device_load_uपूर्णांक32(0x000000000038001CULL);

		state->fअगरo_valid  = false; /* no monitor connected */
		state->sink_accept = !_hrt_get_bit(value, 0);
	पूर्ण
	state->src_valid   = fअगरo_monitor_status_valid(ID,
			     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_GPD); /* ISP_STR_MON_PORT_FA2ISP */
	state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
			     HIVE_GP_REGS_ISP_STREAM_STAT_IDX,
			     ISP_STR_MON_PORT_RCV_GPD);
	अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_IF0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_PIF_A); /* SP_STR_MON_PORT_SP2PIFA */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_PIF_A);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_PIF_A); /* MOD_STR_MON_PORT_CELLS2PIFA */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_PIF_A);
		अवरोध;
	हाल FIFO_CHANNEL_IF0_TO_SP0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_PIF_A); /* MOD_STR_MON_PORT_PIFA2CELLS */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_PIF_A);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_PIF_A); /* SP_STR_MON_PORT_PIFA2SP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_PIF_A);
		अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_IF1:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_PIF_B); /* SP_STR_MON_PORT_SP2PIFB */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_PIF_B);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_PIF_B); /* MOD_STR_MON_PORT_CELLS2PIFB */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_PIF_B);
		अवरोध;
	हाल FIFO_CHANNEL_IF1_TO_SP0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_PIF_B); /* MOD_STR_MON_PORT_PIFB2CELLS */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_PIF_B);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_PIF_B); /* SP_STR_MON_PORT_PIFB2SP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     ISP_STR_MON_PORT_RCV_PIF_B);
		अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_IF2:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_SIF); /* SP_STR_MON_PORT_SP2SIF */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_SIF);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_SIF); /* MOD_STR_MON_PORT_SP2SIF */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_SIF);
		अवरोध;
	हाल FIFO_CHANNEL_IF2_TO_SP0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_SIF); /* MOD_STR_MON_PORT_SIF2SP */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_SIF);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_SIF); /* SP_STR_MON_PORT_SIF2SP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_SIF);
		अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_DMA0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_DMA); /* SP_STR_MON_PORT_SP2DMA */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_DMA);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_DMA_FR_SP); /* MOD_STR_MON_PORT_SP2DMA */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_DMA_FR_SP);
		अवरोध;
	हाल FIFO_CHANNEL_DMA0_TO_SP0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_DMA2SP); /* MOD_STR_MON_PORT_DMA2SP */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_DMA2SP);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_DMA); /* SP_STR_MON_PORT_DMA2SP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_DMA);
		अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_GDC0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_B_IDX,
				     SP_STR_MON_PORT_B_SP2GDC1);
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_B_IDX,
				     SP_STR_MON_PORT_B_SP2GDC1);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_CELLS2GDC1);
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_CELLS2GDC1);
		अवरोध;
	हाल FIFO_CHANNEL_GDC0_TO_SP0:
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_GDC12CELLS);
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_GDC12CELLS);
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_B_IDX,
				     SP_STR_MON_PORT_B_GDC12SP);
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_B_IDX,
				     SP_STR_MON_PORT_B_GDC12SP);
		अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_GDC1:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_B_IDX,
				     SP_STR_MON_PORT_B_SP2GDC2);
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_B_IDX,
				     SP_STR_MON_PORT_B_SP2GDC2);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_CELLS2GDC2);
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_CELLS2GDC2);
		अवरोध;
	हाल FIFO_CHANNEL_GDC1_TO_SP0:
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_GDC22CELLS);
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_GDC22CELLS);
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_B_IDX,
				     SP_STR_MON_PORT_B_GDC22SP);
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_B_IDX,
				     SP_STR_MON_PORT_B_GDC22SP);
		अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_HOST0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_GPD); /* SP_STR_MON_PORT_SP2GPD */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_GPD);
		अणु
			hrt_data	value = ia_css_device_load_uपूर्णांक32(0x0000000000380010ULL);

			state->fअगरo_valid  = !_hrt_get_bit(value, 0);
			state->sink_accept = false; /* no monitor connected */
		पूर्ण
		अवरोध;
	हाल FIFO_CHANNEL_HOST0_TO_SP0: अणु
		hrt_data	value = ia_css_device_load_uपूर्णांक32(0x0000000000380018ULL);

		state->fअगरo_valid  = false; /* no monitor connected */
		state->sink_accept = !_hrt_get_bit(value, 0);
	पूर्ण
	state->src_valid   = fअगरo_monitor_status_valid(ID,
			     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_GPD); /* SP_STR_MON_PORT_FA2SP */
	state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
			     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
			     SP_STR_MON_PORT_RCV_GPD);
	अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_STREAM2MEM0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_MC); /* SP_STR_MON_PORT_SP2MC */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SND_MC);
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_MC); /* MOD_STR_MON_PORT_SP2MC */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_RCV_MC);
		अवरोध;
	हाल FIFO_CHANNEL_STREAM2MEM0_TO_SP0:
		state->fअगरo_valid  = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_MC); /* SP_STR_MON_PORT_MC2SP */
		state->sink_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_MOD_STREAM_STAT_IDX,
				     MOD_STR_MON_PORT_SND_MC);
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_MC); /* MOD_STR_MON_PORT_MC2SP */
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_RCV_MC);
		अवरोध;
	हाल FIFO_CHANNEL_SP0_TO_INPUT_SYSTEM0:
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SP2ISYS);
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_SP2ISYS);
		state->fअगरo_valid  = false;
		state->sink_accept = false;
		अवरोध;
	हाल FIFO_CHANNEL_INPUT_SYSTEM0_TO_SP0:
		state->fअगरo_valid  = false;
		state->sink_accept = false;
		state->src_valid   = fअगरo_monitor_status_valid(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_ISYS2SP);
		state->fअगरo_accept = fअगरo_monitor_status_accept(ID,
				     HIVE_GP_REGS_SP_STREAM_STAT_IDX,
				     SP_STR_MON_PORT_ISYS2SP);
		अवरोध;
	शेष:
		निश्चित(0);
		अवरोध;
	पूर्ण

	वापस;
पूर्ण

व्योम fअगरo_चयन_get_state(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर fअगरo_चयन_t			चयन_id,
    fअगरo_चयन_state_t			*state)
अणु
	hrt_data		data = (hrt_data)-1;

	निश्चित(ID == FIFO_MONITOR0_ID);
	निश्चित(चयन_id < N_FIFO_SWITCH);
	निश्चित(state);

	(व्योम)ID;

	data = gp_device_reg_load(GP_DEVICE0_ID, FIFO_SWITCH_ADDR[चयन_id]);

	state->is_none = (data == HIVE_ISP_CSS_STREAM_SWITCH_NONE);
	state->is_sp = (data == HIVE_ISP_CSS_STREAM_SWITCH_SP);
	state->is_isp = (data == HIVE_ISP_CSS_STREAM_SWITCH_ISP);

	वापस;
पूर्ण

व्योम fअगरo_monitor_get_state(
    स्थिर fअगरo_monitor_ID_t		ID,
    fअगरo_monitor_state_t		*state)
अणु
	fअगरo_channel_t	ch_id;
	fअगरo_चयन_t	sw_id;

	निश्चित(ID < N_FIFO_MONITOR_ID);
	निश्चित(state);

	क्रम (ch_id = 0; ch_id < N_FIFO_CHANNEL; ch_id++) अणु
		fअगरo_channel_get_state(ID, ch_id,
				       &state->fअगरo_channels[ch_id]);
	पूर्ण

	क्रम (sw_id = 0; sw_id < N_FIFO_SWITCH; sw_id++) अणु
		fअगरo_चयन_get_state(ID, sw_id,
				      &state->fअगरo_चयनes[sw_id]);
	पूर्ण
	वापस;
पूर्ण

अटल अंतरभूत bool fअगरo_monitor_status_valid(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक			reg,
    स्थिर अचिन्हित पूर्णांक			port_id)
अणु
	hrt_data	data = fअगरo_monitor_reg_load(ID, reg);

	वापस (data >> (((port_id * 2) + _hive_str_mon_valid_offset))) & 0x1;
पूर्ण

अटल अंतरभूत bool fअगरo_monitor_status_accept(
    स्थिर fअगरo_monitor_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक			reg,
    स्थिर अचिन्हित पूर्णांक			port_id)
अणु
	hrt_data	data = fअगरo_monitor_reg_load(ID, reg);

	वापस (data >> (((port_id * 2) + _hive_str_mon_accept_offset))) & 0x1;
पूर्ण
