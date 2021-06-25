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

#समावेश <type_support.h>

//CSI reveiver has 3 ports.
#घोषणा		N_CSI_PORTS (3)
//AM: Use previous define क्रम this.

//MIPI allows upto 4 channels.
#घोषणा		N_CHANNELS  (4)
// 12KB = 256bit x 384 words
#घोषणा		IB_CAPACITY_IN_WORDS (384)

प्रकार क्रमागत अणु
	MIPI_0LANE_CFG = 0,
	MIPI_1LANE_CFG = 1,
	MIPI_2LANE_CFG = 2,
	MIPI_3LANE_CFG = 3,
	MIPI_4LANE_CFG = 4
पूर्ण mipi_lane_cfg_t;

प्रकार क्रमागत अणु
	INPUT_SYSTEM_SOURCE_SENSOR = 0,
	INPUT_SYSTEM_SOURCE_FIFO,
	INPUT_SYSTEM_SOURCE_TPG,
	INPUT_SYSTEM_SOURCE_PRBS,
	INPUT_SYSTEM_SOURCE_MEMORY,
	N_INPUT_SYSTEM_SOURCE
पूर्ण input_प्रणाली_source_t;

/* पूर्णांकernal routing configuration */
प्रकार क्रमागत अणु
	INPUT_SYSTEM_DISCARD_ALL = 0,
	INPUT_SYSTEM_CSI_BACKEND = 1,
	INPUT_SYSTEM_INPUT_BUFFER = 2,
	INPUT_SYSTEM_MULTICAST = 3,
	N_INPUT_SYSTEM_CONNECTION
पूर्ण input_प्रणाली_connection_t;

प्रकार क्रमागत अणु
	INPUT_SYSTEM_MIPI_PORT0,
	INPUT_SYSTEM_MIPI_PORT1,
	INPUT_SYSTEM_MIPI_PORT2,
	INPUT_SYSTEM_ACQUISITION_UNIT,
	N_INPUT_SYSTEM_MULTIPLEX
पूर्ण input_प्रणाली_multiplex_t;

प्रकार क्रमागत अणु
	INPUT_SYSTEM_SINK_MEMORY = 0,
	INPUT_SYSTEM_SINK_ISP,
	INPUT_SYSTEM_SINK_SP,
	N_INPUT_SYSTEM_SINK
पूर्ण input_प्रणाली_sink_t;

प्रकार क्रमागत अणु
	INPUT_SYSTEM_FIFO_CAPTURE = 0,
	INPUT_SYSTEM_FIFO_CAPTURE_WITH_COUNTING,
	INPUT_SYSTEM_SRAM_BUFFERING,
	INPUT_SYSTEM_XMEM_BUFFERING,
	INPUT_SYSTEM_XMEM_CAPTURE,
	INPUT_SYSTEM_XMEM_ACQUIRE,
	N_INPUT_SYSTEM_BUFFERING_MODE
पूर्ण buffering_mode_t;

प्रकार काष्ठा isp2400_input_प्रणाली_cfg_s	input_प्रणाली_cfg_t;
प्रकार काष्ठा sync_generator_cfg_s	sync_generator_cfg_t;
प्रकार काष्ठा tpg_cfg_s			tpg_cfg_t;
प्रकार काष्ठा prbs_cfg_s			prbs_cfg_t;

/* MW: uपूर्णांक16_t should be sufficient */
काष्ठा isp2400_input_प्रणाली_cfg_s अणु
	u32	no_side_band;
	u32	fmt_type;
	u32	ch_id;
	u32	input_mode;
पूर्ण;

काष्ठा sync_generator_cfg_s अणु
	u32	width;
	u32	height;
	u32	hblank_cycles;
	u32	vblank_cycles;
पूर्ण;

/* MW: tpg & prbs are exclusive */
काष्ठा tpg_cfg_s अणु
	u32	x_mask;
	u32	y_mask;
	u32	x_delta;
	u32	y_delta;
	u32	xy_mask;
	sync_generator_cfg_t sync_gen_cfg;
पूर्ण;

काष्ठा prbs_cfg_s अणु
	u32	seed;
	sync_generator_cfg_t sync_gen_cfg;
पूर्ण;

काष्ठा gpfअगरo_cfg_s अणु
// TBD.
	sync_generator_cfg_t sync_gen_cfg;
पूर्ण;

प्रकार काष्ठा gpfअगरo_cfg_s		gpfअगरo_cfg_t;

//ALX:Commented out to pass the compilation.
//प्रकार काष्ठा isp2400_input_प्रणाली_cfg_s input_प्रणाली_cfg_t;

काष्ठा ib_buffer_s अणु
	u32	mem_reg_size;
	u32	nof_mem_regs;
	u32	mem_reg_addr;
पूर्ण;

प्रकार काष्ठा ib_buffer_s	isp2400_ib_buffer_t;

काष्ठा csi_cfg_s अणु
	u32			csi_port;
	buffering_mode_t	buffering_mode;
	isp2400_ib_buffer_t	csi_buffer;
	isp2400_ib_buffer_t	acquisition_buffer;
	u32			nof_xmem_buffers;
पूर्ण;

प्रकार काष्ठा csi_cfg_s	 csi_cfg_t;

प्रकार क्रमागत अणु
	INPUT_SYSTEM_CFG_FLAG_RESET	= 0,
	INPUT_SYSTEM_CFG_FLAG_SET		= 1U << 0,
	INPUT_SYSTEM_CFG_FLAG_BLOCKED	= 1U << 1,
	INPUT_SYSTEM_CFG_FLAG_REQUIRED	= 1U << 2,
	INPUT_SYSTEM_CFG_FLAG_CONFLICT	= 1U << 3	// To mark a conflicting configuration.
पूर्ण isp2400_input_प्रणाली_cfg_flag_t;

प्रकार u32 input_प्रणाली_config_flags_t;
