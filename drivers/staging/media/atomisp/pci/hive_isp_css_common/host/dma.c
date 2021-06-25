<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2016, Intel Corporation.
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

#समावेश <linux/kernel.h>

#समावेश "dma.h"

#समावेश "assert_support.h"

#अगर_अघोषित __INLINE_DMA__
#समावेश "dma_private.h"
#पूर्ण_अगर /* __INLINE_DMA__ */

व्योम dma_get_state(स्थिर dma_ID_t ID, dma_state_t *state)
अणु
	पूर्णांक			i;
	hrt_data	पंचांगp;

	निश्चित(ID < N_DMA_ID);
	निश्चित(state);

	पंचांगp = dma_reg_load(ID, DMA_COMMAND_FSM_REG_IDX);
	//reg  [3:0] : flags error [3], stall, run, idle [0]
	//reg  [9:4] : command
	//reg[14:10] : channel
	//reg [23:15] : param
	state->fsm_command_idle = पंचांगp & 0x1;
	state->fsm_command_run = पंचांगp & 0x2;
	state->fsm_command_stalling = पंचांगp & 0x4;
	state->fsm_command_error    = पंचांगp & 0x8;
	state->last_command_channel = (पंचांगp >> 10 & 0x1F);
	state->last_command_param =  (पंचांगp >> 15 & 0x0F);
	पंचांगp = (पंचांगp >> 4) & 0x3F;
	/* state->last_command = (dma_commands_t)पंचांगp; */
	/* अगर the क्रमागतerator is made non-linear */
	/* AM: the list below करोes not cover all the हालs*/
	/*  and these are not correct */
	/* thereक्रमe क्रम just dumpinmg this command*/
	state->last_command = पंचांगp;

	/*
		अगर (पंचांगp == 0)
			state->last_command = DMA_COMMAND_READ;
		अगर (पंचांगp == 1)
			state->last_command = DMA_COMMAND_WRITE;
		अगर (पंचांगp == 2)
			state->last_command = DMA_COMMAND_SET_CHANNEL;
		अगर (पंचांगp == 3)
			state->last_command = DMA_COMMAND_SET_PARAM;
		अगर (पंचांगp == 4)
			state->last_command = DMA_COMMAND_READ_SPECIFIC;
		अगर (पंचांगp == 5)
			state->last_command = DMA_COMMAND_WRITE_SPECIFIC;
		अगर (पंचांगp == 8)
			state->last_command = DMA_COMMAND_INIT;
		अगर (पंचांगp == 12)
			state->last_command = DMA_COMMAND_INIT_SPECIFIC;
		अगर (पंचांगp == 15)
			state->last_command = DMA_COMMAND_RST;
	*/

	/* No sub-fields, idx = 0 */
	state->current_command = dma_reg_load(ID,
					      DMA_CG_INFO_REG_IDX(0, _DMA_FSM_GROUP_CMD_IDX));
	state->current_addr_a = dma_reg_load(ID,
					     DMA_CG_INFO_REG_IDX(0, _DMA_FSM_GROUP_ADDR_A_IDX));
	state->current_addr_b = dma_reg_load(ID,
					     DMA_CG_INFO_REG_IDX(0, _DMA_FSM_GROUP_ADDR_B_IDX));

	पंचांगp =  dma_reg_load(ID,
			    DMA_CG_INFO_REG_IDX(
				_DMA_FSM_GROUP_FSM_CTRL_STATE_IDX,
				_DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_idle = पंचांगp & 0x1;
	state->fsm_ctrl_run = पंचांगp & 0x2;
	state->fsm_ctrl_stalling = पंचांगp & 0x4;
	state->fsm_ctrl_error = पंचांगp & 0x8;
	पंचांगp = पंचांगp >> 4;
	/* state->fsm_ctrl_state = (dma_ctrl_states_t)पंचांगp; */
	अगर (पंचांगp == 0)
		state->fsm_ctrl_state = DMA_CTRL_STATE_IDLE;
	अगर (पंचांगp == 1)
		state->fsm_ctrl_state = DMA_CTRL_STATE_REQ_RCV;
	अगर (पंचांगp == 2)
		state->fsm_ctrl_state = DMA_CTRL_STATE_RCV;
	अगर (पंचांगp == 3)
		state->fsm_ctrl_state = DMA_CTRL_STATE_RCV_REQ;
	अगर (पंचांगp == 4)
		state->fsm_ctrl_state = DMA_CTRL_STATE_INIT;
	state->fsm_ctrl_source_dev = dma_reg_load(ID,
				     DMA_CG_INFO_REG_IDX(
					 _DMA_FSM_GROUP_FSM_CTRL_REQ_DEV_IDX,
					 _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_source_addr = dma_reg_load(ID,
				      DMA_CG_INFO_REG_IDX(
					  _DMA_FSM_GROUP_FSM_CTRL_REQ_ADDR_IDX,
					  _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_source_stride = dma_reg_load(ID,
					DMA_CG_INFO_REG_IDX(
					    _DMA_FSM_GROUP_FSM_CTRL_REQ_STRIDE_IDX,
					    _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_source_width = dma_reg_load(ID,
				       DMA_CG_INFO_REG_IDX(
					   _DMA_FSM_GROUP_FSM_CTRL_REQ_XB_IDX,
					   _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_source_height = dma_reg_load(ID,
					DMA_CG_INFO_REG_IDX(
					    _DMA_FSM_GROUP_FSM_CTRL_REQ_YB_IDX,
					    _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_pack_source_dev = dma_reg_load(ID,
					  DMA_CG_INFO_REG_IDX(
					      _DMA_FSM_GROUP_FSM_CTRL_PACK_REQ_DEV_IDX,
					      _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_pack_dest_dev = dma_reg_load(ID,
					DMA_CG_INFO_REG_IDX(
					    _DMA_FSM_GROUP_FSM_CTRL_PACK_WR_DEV_IDX,
					    _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_dest_addr = dma_reg_load(ID,
				    DMA_CG_INFO_REG_IDX(
					_DMA_FSM_GROUP_FSM_CTRL_WR_ADDR_IDX,
					_DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_dest_stride = dma_reg_load(ID,
				      DMA_CG_INFO_REG_IDX(
					  _DMA_FSM_GROUP_FSM_CTRL_WR_STRIDE_IDX,
					  _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_pack_source_width = dma_reg_load(ID,
					    DMA_CG_INFO_REG_IDX(
						_DMA_FSM_GROUP_FSM_CTRL_PACK_REQ_XB_IDX,
						_DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_pack_dest_height = dma_reg_load(ID,
					   DMA_CG_INFO_REG_IDX(
					       _DMA_FSM_GROUP_FSM_CTRL_PACK_WR_YB_IDX,
					       _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_pack_dest_width = dma_reg_load(ID,
					  DMA_CG_INFO_REG_IDX(
					      _DMA_FSM_GROUP_FSM_CTRL_PACK_WR_XB_IDX,
					      _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_pack_source_elems = dma_reg_load(ID,
					    DMA_CG_INFO_REG_IDX(
						_DMA_FSM_GROUP_FSM_CTRL_PACK_ELEM_REQ_IDX,
						_DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_pack_dest_elems = dma_reg_load(ID,
					  DMA_CG_INFO_REG_IDX(
					      _DMA_FSM_GROUP_FSM_CTRL_PACK_ELEM_WR_IDX,
					      _DMA_FSM_GROUP_FSM_CTRL_IDX));
	state->fsm_ctrl_pack_extension = dma_reg_load(ID,
					 DMA_CG_INFO_REG_IDX(
					     _DMA_FSM_GROUP_FSM_CTRL_PACK_S_Z_IDX,
					     _DMA_FSM_GROUP_FSM_CTRL_IDX));

	पंचांगp = dma_reg_load(ID,
			   DMA_CG_INFO_REG_IDX(
			       _DMA_FSM_GROUP_FSM_PACK_STATE_IDX,
			       _DMA_FSM_GROUP_FSM_PACK_IDX));
	state->pack_idle     = पंचांगp & 0x1;
	state->pack_run      = पंचांगp & 0x2;
	state->pack_stalling = पंचांगp & 0x4;
	state->pack_error    = पंचांगp & 0x8;
	state->pack_cnt_height = dma_reg_load(ID,
					      DMA_CG_INFO_REG_IDX(
						      _DMA_FSM_GROUP_FSM_PACK_CNT_YB_IDX,
						      _DMA_FSM_GROUP_FSM_PACK_IDX));
	state->pack_src_cnt_width = dma_reg_load(ID,
				    DMA_CG_INFO_REG_IDX(
					_DMA_FSM_GROUP_FSM_PACK_CNT_XB_REQ_IDX,
					_DMA_FSM_GROUP_FSM_PACK_IDX));
	state->pack_dest_cnt_width = dma_reg_load(ID,
				     DMA_CG_INFO_REG_IDX(
					 _DMA_FSM_GROUP_FSM_PACK_CNT_XB_WR_IDX,
					 _DMA_FSM_GROUP_FSM_PACK_IDX));

	पंचांगp = dma_reg_load(ID,
			   DMA_CG_INFO_REG_IDX(
			       _DMA_FSM_GROUP_FSM_REQ_STATE_IDX,
			       _DMA_FSM_GROUP_FSM_REQ_IDX));
	/* state->पढ़ो_state = (dma_rw_states_t)पंचांगp; */
	अगर (पंचांगp == 0)
		state->पढ़ो_state = DMA_RW_STATE_IDLE;
	अगर (पंचांगp == 1)
		state->पढ़ो_state = DMA_RW_STATE_REQ;
	अगर (पंचांगp == 2)
		state->पढ़ो_state = DMA_RW_STATE_NEXT_LINE;
	अगर (पंचांगp == 3)
		state->पढ़ो_state = DMA_RW_STATE_UNLOCK_CHANNEL;
	state->पढ़ो_cnt_height = dma_reg_load(ID,
					      DMA_CG_INFO_REG_IDX(
						      _DMA_FSM_GROUP_FSM_REQ_CNT_YB_IDX,
						      _DMA_FSM_GROUP_FSM_REQ_IDX));
	state->पढ़ो_cnt_width = dma_reg_load(ID,
					     DMA_CG_INFO_REG_IDX(
						     _DMA_FSM_GROUP_FSM_REQ_CNT_XB_IDX,
						     _DMA_FSM_GROUP_FSM_REQ_IDX));

	पंचांगp = dma_reg_load(ID,
			   DMA_CG_INFO_REG_IDX(
			       _DMA_FSM_GROUP_FSM_WR_STATE_IDX,
			       _DMA_FSM_GROUP_FSM_WR_IDX));
	/* state->ग_लिखो_state = (dma_rw_states_t)पंचांगp; */
	अगर (पंचांगp == 0)
		state->ग_लिखो_state = DMA_RW_STATE_IDLE;
	अगर (पंचांगp == 1)
		state->ग_लिखो_state = DMA_RW_STATE_REQ;
	अगर (पंचांगp == 2)
		state->ग_लिखो_state = DMA_RW_STATE_NEXT_LINE;
	अगर (पंचांगp == 3)
		state->ग_लिखो_state = DMA_RW_STATE_UNLOCK_CHANNEL;
	state->ग_लिखो_height = dma_reg_load(ID,
					   DMA_CG_INFO_REG_IDX(
					       _DMA_FSM_GROUP_FSM_WR_CNT_YB_IDX,
					       _DMA_FSM_GROUP_FSM_WR_IDX));
	state->ग_लिखो_width = dma_reg_load(ID,
					  DMA_CG_INFO_REG_IDX(
					      _DMA_FSM_GROUP_FSM_WR_CNT_XB_IDX,
					      _DMA_FSM_GROUP_FSM_WR_IDX));

	क्रम (i = 0; i < HIVE_ISP_NUM_DMA_CONNS; i++) अणु
		dma_port_state_t *port = &state->port_states[i];

		पंचांगp = dma_reg_load(ID, DMA_DEV_INFO_REG_IDX(0, i));
		port->req_cs   = ((पंचांगp & 0x1) != 0);
		port->req_we_n = ((पंचांगp & 0x2) != 0);
		port->req_run  = ((पंचांगp & 0x4) != 0);
		port->req_ack  = ((पंचांगp & 0x8) != 0);

		पंचांगp = dma_reg_load(ID, DMA_DEV_INFO_REG_IDX(1, i));
		port->send_cs   = ((पंचांगp & 0x1) != 0);
		port->send_we_n = ((पंचांगp & 0x2) != 0);
		port->send_run  = ((पंचांगp & 0x4) != 0);
		port->send_ack  = ((पंचांगp & 0x8) != 0);

		पंचांगp = dma_reg_load(ID, DMA_DEV_INFO_REG_IDX(2, i));
		अगर (पंचांगp & 0x1)
			port->fअगरo_state = DMA_FIFO_STATE_WILL_BE_FULL;
		अगर (पंचांगp & 0x2)
			port->fअगरo_state = DMA_FIFO_STATE_FULL;
		अगर (पंचांगp & 0x4)
			port->fअगरo_state = DMA_FIFO_STATE_EMPTY;
		port->fअगरo_counter = पंचांगp >> 3;
	पूर्ण

	क्रम (i = 0; i < HIVE_DMA_NUM_CHANNELS; i++) अणु
		dma_channel_state_t *ch = &state->channel_states[i];

		ch->connection = DMA_GET_CONNECTION(dma_reg_load(ID,
						    DMA_CHANNEL_PARAM_REG_IDX(i,
							    _DMA_PACKING_SETUP_PARAM)));
		ch->sign_extend = DMA_GET_EXTENSION(dma_reg_load(ID,
						    DMA_CHANNEL_PARAM_REG_IDX(i,
							    _DMA_PACKING_SETUP_PARAM)));
		ch->height = dma_reg_load(ID,
					  DMA_CHANNEL_PARAM_REG_IDX(i,
						  _DMA_HEIGHT_PARAM));
		ch->stride_a = dma_reg_load(ID,
					    DMA_CHANNEL_PARAM_REG_IDX(i,
						    _DMA_STRIDE_A_PARAM));
		ch->elems_a = DMA_GET_ELEMENTS(dma_reg_load(ID,
					       DMA_CHANNEL_PARAM_REG_IDX(i,
						       _DMA_ELEM_CROPPING_A_PARAM)));
		ch->cropping_a = DMA_GET_CROPPING(dma_reg_load(ID,
						  DMA_CHANNEL_PARAM_REG_IDX(i,
							  _DMA_ELEM_CROPPING_A_PARAM)));
		ch->width_a = dma_reg_load(ID,
					   DMA_CHANNEL_PARAM_REG_IDX(i,
						   _DMA_WIDTH_A_PARAM));
		ch->stride_b = dma_reg_load(ID,
					    DMA_CHANNEL_PARAM_REG_IDX(i,
						    _DMA_STRIDE_B_PARAM));
		ch->elems_b = DMA_GET_ELEMENTS(dma_reg_load(ID,
					       DMA_CHANNEL_PARAM_REG_IDX(i,
						       _DMA_ELEM_CROPPING_B_PARAM)));
		ch->cropping_b = DMA_GET_CROPPING(dma_reg_load(ID,
						  DMA_CHANNEL_PARAM_REG_IDX(i,
							  _DMA_ELEM_CROPPING_B_PARAM)));
		ch->width_b = dma_reg_load(ID,
					   DMA_CHANNEL_PARAM_REG_IDX(i,
						   _DMA_WIDTH_B_PARAM));
	पूर्ण
पूर्ण

व्योम
dma_set_max_burst_size(स्थिर dma_ID_t ID, dma_connection conn,
		       uपूर्णांक32_t max_burst_size)
अणु
	निश्चित(ID < N_DMA_ID);
	निश्चित(max_burst_size > 0);
	dma_reg_store(ID, DMA_DEV_INFO_REG_IDX(_DMA_DEV_INTERF_MAX_BURST_IDX, conn),
		      max_burst_size - 1);
पूर्ण
