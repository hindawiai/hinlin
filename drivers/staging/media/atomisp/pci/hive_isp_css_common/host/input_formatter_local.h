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

#अगर_अघोषित __INPUT_FORMATTER_LOCAL_H_INCLUDED__
#घोषणा __INPUT_FORMATTER_LOCAL_H_INCLUDED__

#समावेश "input_formatter_global.h"

#समावेश "isp.h"		/* ISP_VEC_ALIGN */

प्रकार काष्ठा input_क्रमmatter_चयन_state_s	input_क्रमmatter_चयन_state_t;
प्रकार काष्ठा input_क्रमmatter_state_s			input_क्रमmatter_state_t;
प्रकार काष्ठा input_क्रमmatter_bin_state_s		input_क्रमmatter_bin_state_t;

#घोषणा HIVE_IF_FSM_SYNC_STATUS                 0x100
#घोषणा HIVE_IF_FSM_SYNC_COUNTER                0x104
#घोषणा HIVE_IF_FSM_DEINTERLEAVING_IDX          0x114
#घोषणा HIVE_IF_FSM_DECIMATION_H_COUNTER        0x118
#घोषणा HIVE_IF_FSM_DECIMATION_V_COUNTER        0x11C
#घोषणा HIVE_IF_FSM_DECIMATION_BLOCK_V_COUNTER  0x120
#घोषणा HIVE_IF_FSM_PADDING_STATUS              0x124
#घोषणा HIVE_IF_FSM_PADDING_ELEMENT_COUNTER     0x128
#घोषणा HIVE_IF_FSM_VECTOR_SUPPORT_ERROR        0x12C
#घोषणा HIVE_IF_FSM_VECTOR_SUPPORT_BUFF_FULL    0x130
#घोषणा HIVE_IF_FSM_VECTOR_SUPPORT              0x134
#घोषणा HIVE_IF_FIFO_SENSOR_STATUS              0x138

/*
 * The चयन LUT's coding defines a sink क्रम each
 * single channel ID + channel क्रमmat type. Conversely
 * the sink (i.e. an input क्रमmatter) can be reached
 * from multiple channel & क्रमmat type combinations
 *
 * LUT[0,1] channel=0, क्रमmat type अणु0,1,...31पूर्ण
 * LUT[2,3] channel=1, क्रमmat type अणु0,1,...31पूर्ण
 * LUT[4,5] channel=2, क्रमmat type अणु0,1,...31पूर्ण
 * LUT[6,7] channel=3, क्रमmat type अणु0,1,...31पूर्ण
 *
 * Each रेजिस्टर hold 16 2-bit fields encoding the sink
 * अणु0,1,2,3पूर्ण, "0" means unconnected.
 *
 * The single FSYNCH रेजिस्टर uses four 3-bit fields of 1-hot
 * encoded sink inक्रमmation, "0" means unconnected.
 *
 * The encoding is redundant. The FSYNCH setting will connect
 * a channel to a sink. At that poपूर्णांक the LUT's beदीर्घing to
 * that channel can be directed to another sink. Thus the data
 * goes to another place than the synch
 */
काष्ठा input_क्रमmatter_चयन_state_s अणु
	पूर्णांक	अगर_input_चयन_lut_reg[8];
	पूर्णांक	अगर_input_चयन_fsync_lut;
	पूर्णांक	अगर_input_चयन_ch_id_fmt_type;
	bool अगर_input_चयन_map[HIVE_SWITCH_N_CHANNELS][HIVE_SWITCH_N_FORMATTYPES];
पूर्ण;

काष्ठा input_क्रमmatter_state_s अणु
	/*	पूर्णांक	reset; */
	पूर्णांक	start_line;
	पूर्णांक	start_column;
	पूर्णांक	cropped_height;
	पूर्णांक	cropped_width;
	पूर्णांक	ver_decimation;
	पूर्णांक	hor_decimation;
	पूर्णांक	ver_deपूर्णांकerleaving;
	पूर्णांक	hor_deपूर्णांकerleaving;
	पूर्णांक	left_padding;
	पूर्णांक	eol_offset;
	पूर्णांक	vmem_start_address;
	पूर्णांक	vmem_end_address;
	पूर्णांक	vmem_increment;
	पूर्णांक	is_yuv420;
	पूर्णांक	vsync_active_low;
	पूर्णांक	hsync_active_low;
	पूर्णांक	allow_fअगरo_overflow;
	पूर्णांक block_fअगरo_when_no_req;
	पूर्णांक	fsm_sync_status;
	पूर्णांक	fsm_sync_counter;
	पूर्णांक	fsm_crop_status;
	पूर्णांक	fsm_crop_line_counter;
	पूर्णांक	fsm_crop_pixel_counter;
	पूर्णांक	fsm_deपूर्णांकerleaving_index;
	पूर्णांक	fsm_dec_h_counter;
	पूर्णांक	fsm_dec_v_counter;
	पूर्णांक	fsm_dec_block_v_counter;
	पूर्णांक	fsm_padding_status;
	पूर्णांक	fsm_padding_elem_counter;
	पूर्णांक	fsm_vector_support_error;
	पूर्णांक	fsm_vector_buffer_full;
	पूर्णांक	vector_support;
	पूर्णांक	sensor_data_lost;
पूर्ण;

काष्ठा input_क्रमmatter_bin_state_s अणु
	u32	reset;
	u32	input_endianness;
	u32	output_endianness;
	u32	bitswap;
	u32	block_synch;
	u32	packet_synch;
	u32	पढ़ोpostग_लिखो_synch;
	u32	is_2ppc;
	u32	en_status_update;
पूर्ण;

#पूर्ण_अगर /* __INPUT_FORMATTER_LOCAL_H_INCLUDED__ */
