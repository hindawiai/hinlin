<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __INPUT_FORMATTER_GLOBAL_H_INCLUDED__
#घोषणा __INPUT_FORMATTER_GLOBAL_H_INCLUDED__

#घोषणा IS_INPUT_FORMATTER_VERSION2
#घोषणा IS_INPUT_SWITCH_VERSION2

#समावेश <type_support.h>
#समावेश <प्रणाली_local.h>
#समावेश "if_defs.h"
#समावेश "str2mem_defs.h"
#समावेश "input_switch_2400_defs.h"

#घोषणा _HIVE_INPUT_SWITCH_GET_FSYNC_REG_LSB(ch_id)        ((ch_id) * 3)

#घोषणा HIVE_SWITCH_N_CHANNELS				4
#घोषणा HIVE_SWITCH_N_FORMATTYPES			32
#घोषणा HIVE_SWITCH_N_SWITCH_CODE			4
#घोषणा HIVE_SWITCH_M_CHANNELS				0x00000003
#घोषणा HIVE_SWITCH_M_FORMATTYPES			0x0000001f
#घोषणा HIVE_SWITCH_M_SWITCH_CODE			0x00000003
#घोषणा HIVE_SWITCH_M_FSYNC					0x00000007

#घोषणा HIVE_SWITCH_ENCODE_FSYNC(x) \
	(1U << (((x) - 1) & HIVE_SWITCH_M_CHANNELS))

#घोषणा _HIVE_INPUT_SWITCH_GET_LUT_FIELD(reg, bit_index) \
	(((reg) >> (bit_index)) & HIVE_SWITCH_M_SWITCH_CODE)
#घोषणा _HIVE_INPUT_SWITCH_SET_LUT_FIELD(reg, bit_index, val) \
	(((reg) & ~(HIVE_SWITCH_M_SWITCH_CODE << (bit_index))) | (((hrt_data)(val) & HIVE_SWITCH_M_SWITCH_CODE) << (bit_index)))
#घोषणा _HIVE_INPUT_SWITCH_GET_FSYNC_FIELD(reg, bit_index) \
	(((reg) >> (bit_index)) & HIVE_SWITCH_M_FSYNC)
#घोषणा _HIVE_INPUT_SWITCH_SET_FSYNC_FIELD(reg, bit_index, val) \
	(((reg) & ~(HIVE_SWITCH_M_FSYNC << (bit_index))) | (((hrt_data)(val) & HIVE_SWITCH_M_FSYNC) << (bit_index)))

प्रकार काष्ठा input_क्रमmatter_cfg_s	input_क्रमmatter_cfg_t;

/* Hardware रेजिस्टरs */
/*#घोषणा HIVE_IF_RESET_ADDRESS                   0x000*/ /* deprecated */
#घोषणा HIVE_IF_START_LINE_ADDRESS              0x004
#घोषणा HIVE_IF_START_COLUMN_ADDRESS            0x008
#घोषणा HIVE_IF_CROPPED_HEIGHT_ADDRESS          0x00C
#घोषणा HIVE_IF_CROPPED_WIDTH_ADDRESS           0x010
#घोषणा HIVE_IF_VERTICAL_DECIMATION_ADDRESS     0x014
#घोषणा HIVE_IF_HORIZONTAL_DECIMATION_ADDRESS   0x018
#घोषणा HIVE_IF_H_DEINTERLEAVING_ADDRESS        0x01C
#घोषणा HIVE_IF_LEFTPADDING_WIDTH_ADDRESS       0x020
#घोषणा HIVE_IF_END_OF_LINE_OFFSET_ADDRESS      0x024
#घोषणा HIVE_IF_VMEM_START_ADDRESS_ADDRESS      0x028
#घोषणा HIVE_IF_VMEM_END_ADDRESS_ADDRESS        0x02C
#घोषणा HIVE_IF_VMEM_INCREMENT_ADDRESS          0x030
#घोषणा HIVE_IF_YUV_420_FORMAT_ADDRESS          0x034
#घोषणा HIVE_IF_VSYNCK_ACTIVE_LOW_ADDRESS       0x038
#घोषणा HIVE_IF_HSYNCK_ACTIVE_LOW_ADDRESS       0x03C
#घोषणा HIVE_IF_ALLOW_FIFO_OVERFLOW_ADDRESS     0x040
#घोषणा HIVE_IF_BLOCK_FIFO_NO_REQ_ADDRESS       0x044
#घोषणा HIVE_IF_V_DEINTERLEAVING_ADDRESS        0x048
#घोषणा HIVE_IF_FSM_CROP_PIXEL_COUNTER          0x110
#घोषणा HIVE_IF_FSM_CROP_LINE_COUNTER           0x10C
#घोषणा HIVE_IF_FSM_CROP_STATUS                 0x108

/* Registers only क्रम simulation */
#घोषणा HIVE_IF_CRUN_MODE_ADDRESS               0x04C
#घोषणा HIVE_IF_DUMP_OUTPUT_ADDRESS             0x050

/* Follow the DMA syntax, "cmd" last */
#घोषणा IF_PACK(val, cmd)             ((val & 0x0fff) | (cmd /*& 0xf000*/))

#घोषणा HIVE_STR2MEM_SOFT_RESET_REG_ADDRESS                   (_STR2MEM_SOFT_RESET_REG_ID * _STR2MEM_REG_ALIGN)
#घोषणा HIVE_STR2MEM_INPUT_ENDIANNESS_REG_ADDRESS             (_STR2MEM_INPUT_ENDIANNESS_REG_ID * _STR2MEM_REG_ALIGN)
#घोषणा HIVE_STR2MEM_OUTPUT_ENDIANNESS_REG_ADDRESS            (_STR2MEM_OUTPUT_ENDIANNESS_REG_ID * _STR2MEM_REG_ALIGN)
#घोषणा HIVE_STR2MEM_BIT_SWAPPING_REG_ADDRESS                 (_STR2MEM_BIT_SWAPPING_REG_ID * _STR2MEM_REG_ALIGN)
#घोषणा HIVE_STR2MEM_BLOCK_SYNC_LEVEL_REG_ADDRESS             (_STR2MEM_BLOCK_SYNC_LEVEL_REG_ID * _STR2MEM_REG_ALIGN)
#घोषणा HIVE_STR2MEM_PACKET_SYNC_LEVEL_REG_ADDRESS            (_STR2MEM_PACKET_SYNC_LEVEL_REG_ID * _STR2MEM_REG_ALIGN)
#घोषणा HIVE_STR2MEM_READ_POST_WRITE_SYNC_ENABLE_REG_ADDRESS  (_STR2MEM_READ_POST_WRITE_SYNC_ENABLE_REG_ID * _STR2MEM_REG_ALIGN)
#घोषणा HIVE_STR2MEM_DUAL_BYTE_INPUTS_ENABLED_REG_ADDRESS     (_STR2MEM_DUAL_BYTE_INPUTS_ENABLED_REG_ID * _STR2MEM_REG_ALIGN)
#घोषणा HIVE_STR2MEM_EN_STAT_UPDATE_ADDRESS                   (_STR2MEM_EN_STAT_UPDATE_ID * _STR2MEM_REG_ALIGN)

/*
 * This data काष्ठाure is shared between host and SP
 */
काष्ठा input_क्रमmatter_cfg_s अणु
	u32	start_line;
	u32	start_column;
	u32	left_padding;
	u32	cropped_height;
	u32	cropped_width;
	u32	deपूर्णांकerleaving;
	u32	buf_vecs;
	u32	buf_start_index;
	u32	buf_increment;
	u32	buf_eol_offset;
	u32	is_yuv420_क्रमmat;
	u32	block_no_reqs;
पूर्ण;

बाह्य स्थिर hrt_address HIVE_IF_SRST_ADDRESS[N_INPUT_FORMATTER_ID];
बाह्य स्थिर hrt_data HIVE_IF_SRST_MASK[N_INPUT_FORMATTER_ID];
बाह्य स्थिर u8 HIVE_IF_SWITCH_CODE[N_INPUT_FORMATTER_ID];

#पूर्ण_अगर /* __INPUT_FORMATTER_GLOBAL_H_INCLUDED__ */
