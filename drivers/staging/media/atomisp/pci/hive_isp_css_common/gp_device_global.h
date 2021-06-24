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

#अगर_अघोषित __GP_DEVICE_GLOBAL_H_INCLUDED__
#घोषणा __GP_DEVICE_GLOBAL_H_INCLUDED__

#घोषणा IS_GP_DEVICE_VERSION_2

#घोषणा _REG_GP_IRQ_REQ0_ADDR				0x08
#घोषणा _REG_GP_IRQ_REQ1_ADDR				0x0C
/* The SP sends SW पूर्णांकerrupt info to this रेजिस्टर */
#घोषणा _REG_GP_IRQ_REQUEST0_ADDR			_REG_GP_IRQ_REQ0_ADDR
#घोषणा _REG_GP_IRQ_REQUEST1_ADDR			_REG_GP_IRQ_REQ1_ADDR

/* The SP configures FIFO चयनes in these रेजिस्टरs */
#घोषणा _REG_GP_SWITCH_IF_ADDR						0x40
#घोषणा _REG_GP_SWITCH_GDC1_ADDR					0x44
#घोषणा _REG_GP_SWITCH_GDC2_ADDR					0x48
/* @ INPUT_FORMATTER_BASE -> GP_DEVICE_BASE */
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

/* @ GP_DEVICE_BASE */
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

#पूर्ण_अगर /* __GP_DEVICE_GLOBAL_H_INCLUDED__ */
