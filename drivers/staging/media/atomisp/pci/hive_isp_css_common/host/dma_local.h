<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __DMA_LOCAL_H_INCLUDED__
#घोषणा __DMA_LOCAL_H_INCLUDED__

#समावेश <type_support.h>
#समावेश "dma_global.h"

#समावेश <defs.h>				/* HRTCAT() */
#समावेश <bits.h>				/* _hrt_get_bits() */
#समावेश <hive_isp_css_defs.h>		/* HIVE_DMA_NUM_CHANNELS */
#समावेश <dma_v2_defs.h>

#घोषणा _DMA_FSM_GROUP_CMD_IDX						_DMA_V2_FSM_GROUP_CMD_IDX
#घोषणा _DMA_FSM_GROUP_ADDR_A_IDX					_DMA_V2_FSM_GROUP_ADDR_SRC_IDX
#घोषणा _DMA_FSM_GROUP_ADDR_B_IDX					_DMA_V2_FSM_GROUP_ADDR_DEST_IDX

#घोषणा _DMA_FSM_GROUP_CMD_CTRL_IDX					_DMA_V2_FSM_GROUP_CMD_CTRL_IDX

#घोषणा _DMA_FSM_GROUP_FSM_CTRL_IDX					_DMA_V2_FSM_GROUP_FSM_CTRL_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_STATE_IDX			_DMA_V2_FSM_GROUP_FSM_CTRL_STATE_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_REQ_DEV_IDX			_DMA_V2_FSM_GROUP_FSM_CTRL_REQ_DEV_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_REQ_ADDR_IDX		_DMA_V2_FSM_GROUP_FSM_CTRL_REQ_ADDR_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_REQ_STRIDE_IDX		_DMA_V2_FSM_GROUP_FSM_CTRL_REQ_STRIDE_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_REQ_XB_IDX			_DMA_V2_FSM_GROUP_FSM_CTRL_REQ_XB_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_REQ_YB_IDX			_DMA_V2_FSM_GROUP_FSM_CTRL_REQ_YB_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_PACK_REQ_DEV_IDX	_DMA_V2_FSM_GROUP_FSM_CTRL_PACK_REQ_DEV_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_PACK_WR_DEV_IDX		_DMA_V2_FSM_GROUP_FSM_CTRL_PACK_WR_DEV_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_WR_ADDR_IDX			_DMA_V2_FSM_GROUP_FSM_CTRL_WR_ADDR_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_WR_STRIDE_IDX		_DMA_V2_FSM_GROUP_FSM_CTRL_WR_STRIDE_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_PACK_REQ_XB_IDX		_DMA_V2_FSM_GROUP_FSM_CTRL_PACK_REQ_XB_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_PACK_WR_YB_IDX		_DMA_V2_FSM_GROUP_FSM_CTRL_PACK_WR_YB_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_PACK_WR_XB_IDX		_DMA_V2_FSM_GROUP_FSM_CTRL_PACK_WR_XB_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_PACK_ELEM_REQ_IDX	_DMA_V2_FSM_GROUP_FSM_CTRL_PACK_ELEM_REQ_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_PACK_ELEM_WR_IDX	_DMA_V2_FSM_GROUP_FSM_CTRL_PACK_ELEM_WR_IDX
#घोषणा _DMA_FSM_GROUP_FSM_CTRL_PACK_S_Z_IDX		_DMA_V2_FSM_GROUP_FSM_CTRL_PACK_S_Z_IDX

#घोषणा _DMA_FSM_GROUP_FSM_PACK_IDX					_DMA_V2_FSM_GROUP_FSM_PACK_IDX
#घोषणा _DMA_FSM_GROUP_FSM_PACK_STATE_IDX			_DMA_V2_FSM_GROUP_FSM_PACK_STATE_IDX
#घोषणा _DMA_FSM_GROUP_FSM_PACK_CNT_YB_IDX			_DMA_V2_FSM_GROUP_FSM_PACK_CNT_YB_IDX
#घोषणा _DMA_FSM_GROUP_FSM_PACK_CNT_XB_REQ_IDX		_DMA_V2_FSM_GROUP_FSM_PACK_CNT_XB_REQ_IDX
#घोषणा _DMA_FSM_GROUP_FSM_PACK_CNT_XB_WR_IDX		_DMA_V2_FSM_GROUP_FSM_PACK_CNT_XB_WR_IDX

#घोषणा _DMA_FSM_GROUP_FSM_REQ_IDX					_DMA_V2_FSM_GROUP_FSM_REQ_IDX
#घोषणा _DMA_FSM_GROUP_FSM_REQ_STATE_IDX			_DMA_V2_FSM_GROUP_FSM_REQ_STATE_IDX
#घोषणा _DMA_FSM_GROUP_FSM_REQ_CNT_YB_IDX			_DMA_V2_FSM_GROUP_FSM_REQ_CNT_YB_IDX
#घोषणा _DMA_FSM_GROUP_FSM_REQ_CNT_XB_IDX			_DMA_V2_FSM_GROUP_FSM_REQ_CNT_XB_IDX

#घोषणा _DMA_FSM_GROUP_FSM_WR_IDX					_DMA_V2_FSM_GROUP_FSM_WR_IDX
#घोषणा _DMA_FSM_GROUP_FSM_WR_STATE_IDX				_DMA_V2_FSM_GROUP_FSM_WR_STATE_IDX
#घोषणा _DMA_FSM_GROUP_FSM_WR_CNT_YB_IDX			_DMA_V2_FSM_GROUP_FSM_WR_CNT_YB_IDX
#घोषणा _DMA_FSM_GROUP_FSM_WR_CNT_XB_IDX			_DMA_V2_FSM_GROUP_FSM_WR_CNT_XB_IDX

#घोषणा _DMA_DEV_INTERF_MAX_BURST_IDX			_DMA_V2_DEV_INTERF_MAX_BURST_IDX

/*
 * Macro's to compute the DMA parameter रेजिस्टर indices
 */
#घोषणा DMA_SEL_COMP(comp)     (((comp)  & _hrt_ones(_DMA_V2_ADDR_SEL_COMP_BITS))            << _DMA_V2_ADDR_SEL_COMP_IDX)
#घोषणा DMA_SEL_CH(ch)         (((ch)    & _hrt_ones(_DMA_V2_ADDR_SEL_CH_REG_BITS))          << _DMA_V2_ADDR_SEL_CH_REG_IDX)
#घोषणा DMA_SEL_PARAM(param)   (((param) & _hrt_ones(_DMA_V2_ADDR_SEL_PARAM_BITS))           << _DMA_V2_ADDR_SEL_PARAM_IDX)
/* CG = Connection Group */
#घोषणा DMA_SEL_CG_INFO(info)  (((info)  & _hrt_ones(_DMA_V2_ADDR_SEL_GROUP_COMP_INFO_BITS)) << _DMA_V2_ADDR_SEL_GROUP_COMP_INFO_IDX)
#घोषणा DMA_SEL_CG_COMP(comp)  (((comp)  & _hrt_ones(_DMA_V2_ADDR_SEL_GROUP_COMP_BITS))      << _DMA_V2_ADDR_SEL_GROUP_COMP_IDX)
#घोषणा DMA_SEL_DEV_INFO(info) (((info)  & _hrt_ones(_DMA_V2_ADDR_SEL_DEV_INTERF_INFO_BITS)) << _DMA_V2_ADDR_SEL_DEV_INTERF_INFO_IDX)
#घोषणा DMA_SEL_DEV_ID(dev)    (((dev)   & _hrt_ones(_DMA_V2_ADDR_SEL_DEV_INTERF_IDX_BITS))  << _DMA_V2_ADDR_SEL_DEV_INTERF_IDX_IDX)

#घोषणा DMA_COMMAND_FSM_REG_IDX					(DMA_SEL_COMP(_DMA_V2_SEL_FSM_CMD) >> 2)
#घोषणा DMA_CHANNEL_PARAM_REG_IDX(ch, param)	((DMA_SEL_COMP(_DMA_V2_SEL_CH_REG) | DMA_SEL_CH(ch) | DMA_SEL_PARAM(param)) >> 2)
#घोषणा DMA_CG_INFO_REG_IDX(info_id, comp_id)	((DMA_SEL_COMP(_DMA_V2_SEL_CONN_GROUP) | DMA_SEL_CG_INFO(info_id) | DMA_SEL_CG_COMP(comp_id)) >> 2)
#घोषणा DMA_DEV_INFO_REG_IDX(info_id, dev_id)	((DMA_SEL_COMP(_DMA_V2_SEL_DEV_INTERF) | DMA_SEL_DEV_INFO(info_id) | DMA_SEL_DEV_ID(dev_id)) >> 2)
#घोषणा DMA_RST_REG_IDX							(DMA_SEL_COMP(_DMA_V2_SEL_RESET) >> 2)

#घोषणा DMA_GET_CONNECTION(val)    _hrt_get_bits(val, _DMA_V2_CONNECTION_IDX,    _DMA_V2_CONNECTION_BITS)
#घोषणा DMA_GET_EXTENSION(val)     _hrt_get_bits(val, _DMA_V2_EXTENSION_IDX,     _DMA_V2_EXTENSION_BITS)
#घोषणा DMA_GET_ELEMENTS(val)      _hrt_get_bits(val, _DMA_V2_ELEMENTS_IDX,      _DMA_V2_ELEMENTS_BITS)
#घोषणा DMA_GET_CROPPING(val)      _hrt_get_bits(val, _DMA_V2_LEFT_CROPPING_IDX, _DMA_V2_LEFT_CROPPING_BITS)

प्रकार क्रमागत अणु
	DMA_CTRL_STATE_IDLE,
	DMA_CTRL_STATE_REQ_RCV,
	DMA_CTRL_STATE_RCV,
	DMA_CTRL_STATE_RCV_REQ,
	DMA_CTRL_STATE_INIT,
	N_DMA_CTRL_STATES
पूर्ण dma_ctrl_states_t;

प्रकार क्रमागत अणु
	DMA_COMMAND_READ,
	DMA_COMMAND_WRITE,
	DMA_COMMAND_SET_CHANNEL,
	DMA_COMMAND_SET_PARAM,
	DMA_COMMAND_READ_SPECIFIC,
	DMA_COMMAND_WRITE_SPECIFIC,
	DMA_COMMAND_INIT,
	DMA_COMMAND_INIT_SPECIFIC,
	DMA_COMMAND_RST,
	N_DMA_COMMANDS
पूर्ण dma_commands_t;

प्रकार क्रमागत अणु
	DMA_RW_STATE_IDLE,
	DMA_RW_STATE_REQ,
	DMA_RW_STATE_NEXT_LINE,
	DMA_RW_STATE_UNLOCK_CHANNEL,
	N_DMA_RW_STATES
पूर्ण dma_rw_states_t;

प्रकार क्रमागत अणु
	DMA_FIFO_STATE_WILL_BE_FULL,
	DMA_FIFO_STATE_FULL,
	DMA_FIFO_STATE_EMPTY,
	N_DMA_FIFO_STATES
पूर्ण dma_fअगरo_states_t;

/* प्रकार काष्ठा dma_state_s			dma_state_t; */
प्रकार काष्ठा dma_channel_state_s	dma_channel_state_t;
प्रकार काष्ठा dma_port_state_s		dma_port_state_t;

काष्ठा dma_port_state_s अणु
	bool                       req_cs;
	bool                       req_we_n;
	bool                       req_run;
	bool                       req_ack;
	bool                       send_cs;
	bool                       send_we_n;
	bool                       send_run;
	bool                       send_ack;
	dma_fअगरo_states_t          fअगरo_state;
	पूर्णांक                        fअगरo_counter;
पूर्ण;

काष्ठा dma_channel_state_s अणु
	पूर्णांक                        connection;
	bool                       sign_extend;
	पूर्णांक                        height;
	पूर्णांक                        stride_a;
	पूर्णांक                        elems_a;
	पूर्णांक                        cropping_a;
	पूर्णांक                        width_a;
	पूर्णांक                        stride_b;
	पूर्णांक                        elems_b;
	पूर्णांक                        cropping_b;
	पूर्णांक                        width_b;
पूर्ण;

काष्ठा dma_state_s अणु
	bool                       fsm_command_idle;
	bool                       fsm_command_run;
	bool                       fsm_command_stalling;
	bool                       fsm_command_error;
	dma_commands_t             last_command;
	पूर्णांक                        last_command_channel;
	पूर्णांक                        last_command_param;
	dma_commands_t             current_command;
	पूर्णांक                        current_addr_a;
	पूर्णांक                        current_addr_b;
	bool                       fsm_ctrl_idle;
	bool                       fsm_ctrl_run;
	bool                       fsm_ctrl_stalling;
	bool                       fsm_ctrl_error;
	dma_ctrl_states_t          fsm_ctrl_state;
	पूर्णांक                        fsm_ctrl_source_dev;
	पूर्णांक                        fsm_ctrl_source_addr;
	पूर्णांक                        fsm_ctrl_source_stride;
	पूर्णांक                        fsm_ctrl_source_width;
	पूर्णांक                        fsm_ctrl_source_height;
	पूर्णांक                        fsm_ctrl_pack_source_dev;
	पूर्णांक                        fsm_ctrl_pack_dest_dev;
	पूर्णांक                        fsm_ctrl_dest_addr;
	पूर्णांक                        fsm_ctrl_dest_stride;
	पूर्णांक                        fsm_ctrl_pack_source_width;
	पूर्णांक                        fsm_ctrl_pack_dest_height;
	पूर्णांक                        fsm_ctrl_pack_dest_width;
	पूर्णांक                        fsm_ctrl_pack_source_elems;
	पूर्णांक                        fsm_ctrl_pack_dest_elems;
	पूर्णांक                        fsm_ctrl_pack_extension;
	पूर्णांक						   pack_idle;
	पूर्णांक			       pack_run;
	पूर्णांक				   pack_stalling;
	पूर्णांक				   pack_error;
	पूर्णांक                        pack_cnt_height;
	पूर्णांक                        pack_src_cnt_width;
	पूर्णांक                        pack_dest_cnt_width;
	dma_rw_states_t            पढ़ो_state;
	पूर्णांक                        पढ़ो_cnt_height;
	पूर्णांक                        पढ़ो_cnt_width;
	dma_rw_states_t            ग_लिखो_state;
	पूर्णांक                        ग_लिखो_height;
	पूर्णांक                        ग_लिखो_width;
	dma_port_state_t           port_states[HIVE_ISP_NUM_DMA_CONNS];
	dma_channel_state_t        channel_states[HIVE_DMA_NUM_CHANNELS];
पूर्ण;

#पूर्ण_अगर /* __DMA_LOCAL_H_INCLUDED__ */
