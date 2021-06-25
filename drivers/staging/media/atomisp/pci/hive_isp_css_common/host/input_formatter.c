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

#समावेश "system_global.h"

#अगर_अघोषित ISP2401

#समावेश "input_formatter.h"
#समावेश <type_support.h>
#समावेश "gp_device.h"

#समावेश "assert_support.h"

#अगर_अघोषित __INLINE_INPUT_FORMATTER__
#समावेश "input_formatter_private.h"
#पूर्ण_अगर /* __INLINE_INPUT_FORMATTER__ */

अटल स्थिर अचिन्हित पूर्णांक input_क्रमmatter_alignment[N_INPUT_FORMATTER_ID] = अणु
	ISP_VEC_ALIGN, ISP_VEC_ALIGN, HIVE_ISP_CTRL_DATA_BYTES
पूर्ण;

स्थिर hrt_address HIVE_IF_SRST_ADDRESS[N_INPUT_FORMATTER_ID] = अणु
	INPUT_FORMATTER0_SRST_OFFSET,
	INPUT_FORMATTER1_SRST_OFFSET,
	INPUT_FORMATTER2_SRST_OFFSET,
	INPUT_FORMATTER3_SRST_OFFSET
पूर्ण;

स्थिर hrt_data HIVE_IF_SRST_MASK[N_INPUT_FORMATTER_ID] = अणु
	INPUT_FORMATTER0_SRST_MASK,
	INPUT_FORMATTER1_SRST_MASK,
	INPUT_FORMATTER2_SRST_MASK,
	INPUT_FORMATTER3_SRST_MASK
पूर्ण;

स्थिर u8 HIVE_IF_SWITCH_CODE[N_INPUT_FORMATTER_ID] = अणु
	HIVE_INPUT_SWITCH_SELECT_IF_PRIM,
	HIVE_INPUT_SWITCH_SELECT_IF_PRIM,
	HIVE_INPUT_SWITCH_SELECT_IF_SEC,
	HIVE_INPUT_SWITCH_SELECT_STR_TO_MEM
पूर्ण;

/* MW Should be part of प्रणाली_global.h, where we have the मुख्य क्रमागतeration */
अटल स्थिर bool HIVE_IF_BIN_COPY[N_INPUT_FORMATTER_ID] = अणु
	false, false, false, true
पूर्ण;

व्योम input_क्रमmatter_rst(
    स्थिर input_क्रमmatter_ID_t		ID)
अणु
	hrt_address	addr;
	hrt_data	rst;

	निश्चित(ID < N_INPUT_FORMATTER_ID);

	addr = HIVE_IF_SRST_ADDRESS[ID];
	rst = HIVE_IF_SRST_MASK[ID];

	/* TEMPORARY HACK: THIS RESET BREAKS THE METADATA FEATURE
	 * WICH USES THE STREAM2MEMRY BLOCK.
	 * MUST BE FIXED PROPERLY
	 */
	अगर (!HIVE_IF_BIN_COPY[ID]) अणु
		input_क्रमmatter_reg_store(ID, addr, rst);
	पूर्ण

	वापस;
पूर्ण

अचिन्हित पूर्णांक input_क्रमmatter_get_alignment(
    स्थिर input_क्रमmatter_ID_t		ID)
अणु
	निश्चित(ID < N_INPUT_FORMATTER_ID);

	वापस input_क्रमmatter_alignment[ID];
पूर्ण

व्योम input_क्रमmatter_set_fअगरo_blocking_mode(
    स्थिर input_क्रमmatter_ID_t		ID,
    स्थिर bool						enable)
अणु
	निश्चित(ID < N_INPUT_FORMATTER_ID);

	/* cnd_input_क्रमmatter_reg_store() */
	अगर (!HIVE_IF_BIN_COPY[ID]) अणु
		input_क्रमmatter_reg_store(ID,
					  HIVE_IF_BLOCK_FIFO_NO_REQ_ADDRESS, enable);
	पूर्ण
	वापस;
पूर्ण

व्योम input_क्रमmatter_get_चयन_state(
    स्थिर input_क्रमmatter_ID_t		ID,
    input_क्रमmatter_चयन_state_t	*state)
अणु
	निश्चित(ID < N_INPUT_FORMATTER_ID);
	निश्चित(state);

	/* We'll change this पूर्णांकo an पूर्णांकelligent function to get चयन info per IF */
	(व्योम)ID;

	state->अगर_input_चयन_lut_reg[0] = gp_device_reg_load(GP_DEVICE0_ID,
					    _REG_GP_IFMT_input_चयन_lut_reg0);
	state->अगर_input_चयन_lut_reg[1] = gp_device_reg_load(GP_DEVICE0_ID,
					    _REG_GP_IFMT_input_चयन_lut_reg1);
	state->अगर_input_चयन_lut_reg[2] = gp_device_reg_load(GP_DEVICE0_ID,
					    _REG_GP_IFMT_input_चयन_lut_reg2);
	state->अगर_input_चयन_lut_reg[3] = gp_device_reg_load(GP_DEVICE0_ID,
					    _REG_GP_IFMT_input_चयन_lut_reg3);
	state->अगर_input_चयन_lut_reg[4] = gp_device_reg_load(GP_DEVICE0_ID,
					    _REG_GP_IFMT_input_चयन_lut_reg4);
	state->अगर_input_चयन_lut_reg[5] = gp_device_reg_load(GP_DEVICE0_ID,
					    _REG_GP_IFMT_input_चयन_lut_reg5);
	state->अगर_input_चयन_lut_reg[6] = gp_device_reg_load(GP_DEVICE0_ID,
					    _REG_GP_IFMT_input_चयन_lut_reg6);
	state->अगर_input_चयन_lut_reg[7] = gp_device_reg_load(GP_DEVICE0_ID,
					    _REG_GP_IFMT_input_चयन_lut_reg7);
	state->अगर_input_चयन_fsync_lut = gp_device_reg_load(GP_DEVICE0_ID,
					   _REG_GP_IFMT_input_चयन_fsync_lut);
	state->अगर_input_चयन_ch_id_fmt_type = gp_device_reg_load(GP_DEVICE0_ID,
						_REG_GP_IFMT_input_चयन_ch_id_fmt_type);

	वापस;
पूर्ण

व्योम input_क्रमmatter_get_state(
    स्थिर input_क्रमmatter_ID_t		ID,
    input_क्रमmatter_state_t			*state)
अणु
	निश्चित(ID < N_INPUT_FORMATTER_ID);
	निश्चित(state);
	/*
		state->reset = input_क्रमmatter_reg_load(ID,
			HIVE_IF_RESET_ADDRESS);
	 */
	state->start_line = input_क्रमmatter_reg_load(ID,
			    HIVE_IF_START_LINE_ADDRESS);
	state->start_column = input_क्रमmatter_reg_load(ID,
			      HIVE_IF_START_COLUMN_ADDRESS);
	state->cropped_height = input_क्रमmatter_reg_load(ID,
				HIVE_IF_CROPPED_HEIGHT_ADDRESS);
	state->cropped_width = input_क्रमmatter_reg_load(ID,
			       HIVE_IF_CROPPED_WIDTH_ADDRESS);
	state->ver_decimation = input_क्रमmatter_reg_load(ID,
				HIVE_IF_VERTICAL_DECIMATION_ADDRESS);
	state->hor_decimation = input_क्रमmatter_reg_load(ID,
				HIVE_IF_HORIZONTAL_DECIMATION_ADDRESS);
	state->hor_deपूर्णांकerleaving = input_क्रमmatter_reg_load(ID,
				    HIVE_IF_H_DEINTERLEAVING_ADDRESS);
	state->left_padding = input_क्रमmatter_reg_load(ID,
			      HIVE_IF_LEFTPADDING_WIDTH_ADDRESS);
	state->eol_offset = input_क्रमmatter_reg_load(ID,
			    HIVE_IF_END_OF_LINE_OFFSET_ADDRESS);
	state->vmem_start_address = input_क्रमmatter_reg_load(ID,
				    HIVE_IF_VMEM_START_ADDRESS_ADDRESS);
	state->vmem_end_address = input_क्रमmatter_reg_load(ID,
				  HIVE_IF_VMEM_END_ADDRESS_ADDRESS);
	state->vmem_increment = input_क्रमmatter_reg_load(ID,
				HIVE_IF_VMEM_INCREMENT_ADDRESS);
	state->is_yuv420 = input_क्रमmatter_reg_load(ID,
			   HIVE_IF_YUV_420_FORMAT_ADDRESS);
	state->vsync_active_low = input_क्रमmatter_reg_load(ID,
				  HIVE_IF_VSYNCK_ACTIVE_LOW_ADDRESS);
	state->hsync_active_low = input_क्रमmatter_reg_load(ID,
				  HIVE_IF_HSYNCK_ACTIVE_LOW_ADDRESS);
	state->allow_fअगरo_overflow = input_क्रमmatter_reg_load(ID,
				     HIVE_IF_ALLOW_FIFO_OVERFLOW_ADDRESS);
	state->block_fअगरo_when_no_req = input_क्रमmatter_reg_load(ID,
					HIVE_IF_BLOCK_FIFO_NO_REQ_ADDRESS);
	state->ver_deपूर्णांकerleaving = input_क्रमmatter_reg_load(ID,
				    HIVE_IF_V_DEINTERLEAVING_ADDRESS);
	/* FSM */
	state->fsm_sync_status = input_क्रमmatter_reg_load(ID,
				 HIVE_IF_FSM_SYNC_STATUS);
	state->fsm_sync_counter = input_क्रमmatter_reg_load(ID,
				  HIVE_IF_FSM_SYNC_COUNTER);
	state->fsm_crop_status = input_क्रमmatter_reg_load(ID,
				 HIVE_IF_FSM_CROP_STATUS);
	state->fsm_crop_line_counter = input_क्रमmatter_reg_load(ID,
				       HIVE_IF_FSM_CROP_LINE_COUNTER);
	state->fsm_crop_pixel_counter = input_क्रमmatter_reg_load(ID,
					HIVE_IF_FSM_CROP_PIXEL_COUNTER);
	state->fsm_deपूर्णांकerleaving_index = input_क्रमmatter_reg_load(ID,
					  HIVE_IF_FSM_DEINTERLEAVING_IDX);
	state->fsm_dec_h_counter = input_क्रमmatter_reg_load(ID,
				   HIVE_IF_FSM_DECIMATION_H_COUNTER);
	state->fsm_dec_v_counter = input_क्रमmatter_reg_load(ID,
				   HIVE_IF_FSM_DECIMATION_V_COUNTER);
	state->fsm_dec_block_v_counter = input_क्रमmatter_reg_load(ID,
					 HIVE_IF_FSM_DECIMATION_BLOCK_V_COUNTER);
	state->fsm_padding_status = input_क्रमmatter_reg_load(ID,
				    HIVE_IF_FSM_PADDING_STATUS);
	state->fsm_padding_elem_counter = input_क्रमmatter_reg_load(ID,
					  HIVE_IF_FSM_PADDING_ELEMENT_COUNTER);
	state->fsm_vector_support_error = input_क्रमmatter_reg_load(ID,
					  HIVE_IF_FSM_VECTOR_SUPPORT_ERROR);
	state->fsm_vector_buffer_full = input_क्रमmatter_reg_load(ID,
					HIVE_IF_FSM_VECTOR_SUPPORT_BUFF_FULL);
	state->vector_support = input_क्रमmatter_reg_load(ID,
				HIVE_IF_FSM_VECTOR_SUPPORT);
	state->sensor_data_lost = input_क्रमmatter_reg_load(ID,
				  HIVE_IF_FIFO_SENSOR_STATUS);

	वापस;
पूर्ण

व्योम input_क्रमmatter_bin_get_state(
    स्थिर input_क्रमmatter_ID_t		ID,
    input_क्रमmatter_bin_state_t		*state)
अणु
	निश्चित(ID < N_INPUT_FORMATTER_ID);
	निश्चित(state);

	state->reset = input_क्रमmatter_reg_load(ID,
						HIVE_STR2MEM_SOFT_RESET_REG_ADDRESS);
	state->input_endianness = input_क्रमmatter_reg_load(ID,
				  HIVE_STR2MEM_INPUT_ENDIANNESS_REG_ADDRESS);
	state->output_endianness = input_क्रमmatter_reg_load(ID,
				   HIVE_STR2MEM_OUTPUT_ENDIANNESS_REG_ADDRESS);
	state->bitswap = input_क्रमmatter_reg_load(ID,
			 HIVE_STR2MEM_BIT_SWAPPING_REG_ADDRESS);
	state->block_synch = input_क्रमmatter_reg_load(ID,
			     HIVE_STR2MEM_BLOCK_SYNC_LEVEL_REG_ADDRESS);
	state->packet_synch = input_क्रमmatter_reg_load(ID,
			      HIVE_STR2MEM_PACKET_SYNC_LEVEL_REG_ADDRESS);
	state->पढ़ोpostग_लिखो_synch = input_क्रमmatter_reg_load(ID,
				     HIVE_STR2MEM_READ_POST_WRITE_SYNC_ENABLE_REG_ADDRESS);
	state->is_2ppc = input_क्रमmatter_reg_load(ID,
			 HIVE_STR2MEM_DUAL_BYTE_INPUTS_ENABLED_REG_ADDRESS);
	state->en_status_update = input_क्रमmatter_reg_load(ID,
				  HIVE_STR2MEM_EN_STAT_UPDATE_ADDRESS);
	वापस;
पूर्ण
#पूर्ण_अगर
