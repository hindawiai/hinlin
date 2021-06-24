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

#अगर_अघोषित __GP_DEVICE_LOCAL_H_INCLUDED__
#घोषणा __GP_DEVICE_LOCAL_H_INCLUDED__

#समावेश "gp_device_global.h"

/* @ GP_REGS_BASE -> GP_DEVICE_BASE */
#घोषणा _REG_GP_SDRAM_WAKEUP_ADDR					0x00
#घोषणा _REG_GP_IDLE_ADDR							0x04
/* #घोषणा _REG_GP_IRQ_REQ0_ADDR					0x08 */
/* #घोषणा _REG_GP_IRQ_REQ1_ADDR					0x0C */
#घोषणा _REG_GP_SP_STREAM_STAT_ADDR					0x10
#घोषणा _REG_GP_SP_STREAM_STAT_B_ADDR				0x14
#घोषणा _REG_GP_ISP_STREAM_STAT_ADDR				0x18
#घोषणा _REG_GP_MOD_STREAM_STAT_ADDR				0x1C
#घोषणा _REG_GP_SP_STREAM_STAT_IRQ_COND_ADDR		0x20
#घोषणा _REG_GP_SP_STREAM_STAT_B_IRQ_COND_ADDR		0x24
#घोषणा _REG_GP_ISP_STREAM_STAT_IRQ_COND_ADDR		0x28
#घोषणा _REG_GP_MOD_STREAM_STAT_IRQ_COND_ADDR		0x2C
#घोषणा _REG_GP_SP_STREAM_STAT_IRQ_ENABLE_ADDR		0x30
#घोषणा _REG_GP_SP_STREAM_STAT_B_IRQ_ENABLE_ADDR	0x34
#घोषणा _REG_GP_ISP_STREAM_STAT_IRQ_ENABLE_ADDR		0x38
#घोषणा _REG_GP_MOD_STREAM_STAT_IRQ_ENABLE_ADDR		0x3C
/*
#घोषणा _REG_GP_SWITCH_IF_ADDR						0x40
#घोषणा _REG_GP_SWITCH_GDC1_ADDR					0x44
#घोषणा _REG_GP_SWITCH_GDC2_ADDR					0x48
*/
#घोषणा _REG_GP_SLV_REG_RST_ADDR					0x50
#घोषणा _REG_GP_SWITCH_ISYS2401_ADDR				0x54

/* @ INPUT_FORMATTER_BASE -> GP_DEVICE_BASE */
/*
#घोषणा _REG_GP_IFMT_input_चयन_lut_reg0			0x00030800
#घोषणा _REG_GP_IFMT_input_चयन_lut_reg1			0x00030804
#घोषणा _REG_GP_IFMT_input_चयन_lut_reg2			0x00030808
#घोषणा _REG_GP_IFMT_input_चयन_lut_reg3			0x0003080C
#घोषणा _REG_GP_IFMT_input_चयन_lut_reg4			0x00030810
#घोषणा _REG_GP_IFMT_input_चयन_lut_reg5			0x00030814
#घोषणा _REG_GP_IFMT_input_चयन_lut_reg6			0x00030818
#घोषणा _REG_GP_IFMT_input_चयन_lut_reg7			0x0003081C
#घोषणा _REG_GP_IFMT_input_चयन_fsync_lut			0x00030820
#घोषणा _REG_GP_IFMT_srst							0x00030824
#घोषणा _REG_GP_IFMT_slv_reg_srst					0x00030828
#घोषणा _REG_GP_IFMT_input_चयन_ch_id_fmt_type	0x0003082C
*/
/* @ GP_DEVICE_BASE */
/*
#घोषणा _REG_GP_SYNCGEN_ENABLE_ADDR					0x00090000
#घोषणा _REG_GP_SYNCGEN_FREE_RUNNING_ADDR			0x00090004
#घोषणा _REG_GP_SYNCGEN_PAUSE_ADDR					0x00090008
#घोषणा _REG_GP_NR_FRAMES_ADDR						0x0009000C
#घोषणा _REG_GP_SYNGEN_NR_PIX_ADDR					0x00090010
#घोषणा _REG_GP_SYNGEN_NR_LINES_ADDR				0x00090014
#घोषणा _REG_GP_SYNGEN_HBLANK_CYCLES_ADDR			0x00090018
#घोषणा _REG_GP_SYNGEN_VBLANK_CYCLES_ADDR			0x0009001C
#घोषणा _REG_GP_ISEL_SOF_ADDR						0x00090020
#घोषणा _REG_GP_ISEL_खातापूर्ण_ADDR						0x00090024
#घोषणा _REG_GP_ISEL_SOL_ADDR						0x00090028
#घोषणा _REG_GP_ISEL_EOL_ADDR						0x0009002C
#घोषणा _REG_GP_ISEL_LFSR_ENABLE_ADDR				0x00090030
#घोषणा _REG_GP_ISEL_LFSR_ENABLE_B_ADDR				0x00090034
#घोषणा _REG_GP_ISEL_LFSR_RESET_VALUE_ADDR			0x00090038
#घोषणा _REG_GP_ISEL_TPG_ENABLE_ADDR				0x0009003C
#घोषणा _REG_GP_ISEL_TPG_ENABLE_B_ADDR				0x00090040
#घोषणा _REG_GP_ISEL_HOR_CNT_MASK_ADDR				0x00090044
#घोषणा _REG_GP_ISEL_VER_CNT_MASK_ADDR				0x00090048
#घोषणा _REG_GP_ISEL_XY_CNT_MASK_ADDR				0x0009004C
#घोषणा _REG_GP_ISEL_HOR_CNT_DELTA_ADDR				0x00090050
#घोषणा _REG_GP_ISEL_VER_CNT_DELTA_ADDR				0x00090054
#घोषणा _REG_GP_ISEL_TPG_MODE_ADDR					0x00090058
#घोषणा _REG_GP_ISEL_TPG_RED1_ADDR					0x0009005C
#घोषणा _REG_GP_ISEL_TPG_GREEN1_ADDR				0x00090060
#घोषणा _REG_GP_ISEL_TPG_BLUE1_ADDR					0x00090064
#घोषणा _REG_GP_ISEL_TPG_RED2_ADDR					0x00090068
#घोषणा _REG_GP_ISEL_TPG_GREEN2_ADDR				0x0009006C
#घोषणा _REG_GP_ISEL_TPG_BLUE2_ADDR					0x00090070
#घोषणा _REG_GP_ISEL_CH_ID_ADDR						0x00090074
#घोषणा _REG_GP_ISEL_FMT_TYPE_ADDR					0x00090078
#घोषणा _REG_GP_ISEL_DATA_SEL_ADDR					0x0009007C
#घोषणा _REG_GP_ISEL_SBAND_SEL_ADDR					0x00090080
#घोषणा _REG_GP_ISEL_SYNC_SEL_ADDR					0x00090084
#घोषणा _REG_GP_SYNCGEN_HOR_CNT_ADDR				0x00090088
#घोषणा _REG_GP_SYNCGEN_VER_CNT_ADDR				0x0009008C
#घोषणा _REG_GP_SYNCGEN_FRAME_CNT_ADDR				0x00090090
#घोषणा _REG_GP_SOFT_RESET_ADDR						0x00090094
*/

काष्ठा gp_device_state_s अणु
	पूर्णांक syncgen_enable;
	पूर्णांक syncgen_मुक्त_running;
	पूर्णांक syncgen_छोड़ो;
	पूर्णांक nr_frames;
	पूर्णांक syngen_nr_pix;
	पूर्णांक syngen_nr_lines;
	पूर्णांक syngen_hblank_cycles;
	पूर्णांक syngen_vblank_cycles;
	पूर्णांक isel_sof;
	पूर्णांक isel_eof;
	पूर्णांक isel_sol;
	पूर्णांक isel_eol;
	पूर्णांक isel_lfsr_enable;
	पूर्णांक isel_lfsr_enable_b;
	पूर्णांक isel_lfsr_reset_value;
	पूर्णांक isel_tpg_enable;
	पूर्णांक isel_tpg_enable_b;
	पूर्णांक isel_hor_cnt_mask;
	पूर्णांक isel_ver_cnt_mask;
	पूर्णांक isel_xy_cnt_mask;
	पूर्णांक isel_hor_cnt_delta;
	पूर्णांक isel_ver_cnt_delta;
	पूर्णांक isel_tpg_mode;
	पूर्णांक isel_tpg_red1;
	पूर्णांक isel_tpg_green1;
	पूर्णांक isel_tpg_blue1;
	पूर्णांक isel_tpg_red2;
	पूर्णांक isel_tpg_green2;
	पूर्णांक isel_tpg_blue2;
	पूर्णांक isel_ch_id;
	पूर्णांक isel_fmt_type;
	पूर्णांक isel_data_sel;
	पूर्णांक isel_sband_sel;
	पूर्णांक isel_sync_sel;
	पूर्णांक syncgen_hor_cnt;
	पूर्णांक syncgen_ver_cnt;
	पूर्णांक syncgen_frame_cnt;
	पूर्णांक soft_reset;
पूर्ण;

#पूर्ण_अगर /* __GP_DEVICE_LOCAL_H_INCLUDED__ */
