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

#अगर_अघोषित __INPUT_SYSTEM_LOCAL_H_INCLUDED__
#घोषणा __INPUT_SYSTEM_LOCAL_H_INCLUDED__

#समावेश <type_support.h>

#समावेश "input_system_global.h"

#समावेश "input_system_defs.h"		/* HIVE_ISYS_GPREG_MULTICAST_A_IDX,... */

/*
 * _HRT_CSS_RECEIVER_2400_TWO_PIXEL_EN_REG_IDX,
 * _HRT_CSS_RECEIVER_2400_CSI2_FUNC_PROG_REG_IDX,...
 */
#समावेश "css_receiver_2400_defs.h"

#समावेश "isp_capture_defs.h"

#समावेश "isp_acquisition_defs.h"
#समावेश "input_system_ctrl_defs.h"

प्रकार क्रमागत अणु
	INPUT_SYSTEM_PORT_A = 0,
	INPUT_SYSTEM_PORT_B,
	INPUT_SYSTEM_PORT_C,
	N_INPUT_SYSTEM_PORTS
पूर्ण input_प्रणाली_csi_port_t;

प्रकार काष्ठा ctrl_unit_cfg_s			ctrl_unit_cfg_t;
प्रकार काष्ठा input_प्रणाली_network_cfg_s	input_प्रणाली_network_cfg_t;
प्रकार काष्ठा target_cfg2400_s		target_cfg2400_t;
प्रकार काष्ठा channel_cfg_s			channel_cfg_t;
प्रकार काष्ठा backend_channel_cfg_s		backend_channel_cfg_t;
प्रकार काष्ठा input_प्रणाली_cfg2400_s		input_प्रणाली_cfg2400_t;
प्रकार काष्ठा mipi_port_state_s		mipi_port_state_t;
प्रकार काष्ठा rx_channel_state_s		rx_channel_state_t;
प्रकार काष्ठा input_चयन_cfg_channel_s	input_चयन_cfg_channel_t;
प्रकार काष्ठा input_चयन_cfg_s		input_चयन_cfg_t;

काष्ठा ctrl_unit_cfg_s अणु
	isp2400_ib_buffer_t		buffer_mipi[N_CAPTURE_UNIT_ID];
	isp2400_ib_buffer_t		buffer_acquire[N_ACQUISITION_UNIT_ID];
पूर्ण;

काष्ठा input_प्रणाली_network_cfg_s अणु
	input_प्रणाली_connection_t	multicast_cfg[N_CAPTURE_UNIT_ID];
	input_प्रणाली_multiplex_t	mux_cfg;
	ctrl_unit_cfg_t				ctrl_unit_cfg[N_CTRL_UNIT_ID];
पूर्ण;

प्रकार काष्ठा अणु
// TBD.
	u32	dummy_parameter;
पूर्ण target_isp_cfg_t;

प्रकार काष्ठा अणु
// TBD.
	u32	dummy_parameter;
पूर्ण target_sp_cfg_t;

प्रकार काष्ठा अणु
// TBD.
	u32	dummy_parameter;
पूर्ण target_strm2mem_cfg_t;

काष्ठा input_चयन_cfg_channel_s अणु
	u32 hsync_data_reg[2];
	u32 vsync_data_reg;
पूर्ण;

काष्ठा target_cfg2400_s अणु
	input_चयन_cfg_channel_t		input_चयन_channel_cfg;
	target_isp_cfg_t	target_isp_cfg;
	target_sp_cfg_t		target_sp_cfg;
	target_strm2mem_cfg_t	target_strm2mem_cfg;
पूर्ण;

काष्ठा backend_channel_cfg_s अणु
	u32	fmt_control_word_1; // Format config.
	u32	fmt_control_word_2;
	u32	no_side_band;
पूर्ण;

प्रकार जोड़  अणु
	csi_cfg_t	csi_cfg;
	tpg_cfg_t	tpg_cfg;
	prbs_cfg_t	prbs_cfg;
	gpfअगरo_cfg_t	gpfअगरo_cfg;
पूर्ण source_cfg_t;

काष्ठा input_चयन_cfg_s अणु
	u32 hsync_data_reg[N_RX_CHANNEL_ID * 2];
	u32 vsync_data_reg;
पूर्ण;

// Configuration of a channel.
काष्ठा channel_cfg_s अणु
	u32		ch_id;
	backend_channel_cfg_t	backend_ch;
	input_प्रणाली_source_t	source_type;
	source_cfg_t		source_cfg;
	target_cfg2400_t	target_cfg;
पूर्ण;

// Complete configuration क्रम input प्रणाली.
काष्ठा input_प्रणाली_cfg2400_s अणु
	input_प्रणाली_source_t source_type;
	input_प्रणाली_config_flags_t	source_type_flags;
	//channel_cfg_t		channel[N_CHANNELS];
	input_प्रणाली_config_flags_t	ch_flags[N_CHANNELS];
	//  This is the place where the buffers' settings are collected, as given.
	csi_cfg_t			csi_value[N_CSI_PORTS];
	input_प्रणाली_config_flags_t	csi_flags[N_CSI_PORTS];

	// Possible another काष्ठा क्रम ib.
	// This buffers set at the end, based on the all configurations.
	isp2400_ib_buffer_t			csi_buffer[N_CSI_PORTS];
	input_प्रणाली_config_flags_t	csi_buffer_flags[N_CSI_PORTS];
	isp2400_ib_buffer_t			acquisition_buffer_unique;
	input_प्रणाली_config_flags_t	acquisition_buffer_unique_flags;
	u32			unallocated_ib_mem_words; // Used क्रम check.DEFAULT = IB_CAPACITY_IN_WORDS.
	//uपूर्णांक32_t			acq_allocated_ib_mem_words;

	input_प्रणाली_connection_t		multicast[N_CSI_PORTS];
	input_प्रणाली_multiplex_t		multiplexer;
	input_प्रणाली_config_flags_t		multiplexer_flags;

	tpg_cfg_t			tpg_value;
	input_प्रणाली_config_flags_t	tpg_flags;
	prbs_cfg_t			prbs_value;
	input_प्रणाली_config_flags_t	prbs_flags;
	gpfअगरo_cfg_t		gpfअगरo_value;
	input_प्रणाली_config_flags_t	gpfअगरo_flags;

	input_चयन_cfg_t		input_चयन_cfg;

	target_isp_cfg_t		target_isp[N_CHANNELS];
	input_प्रणाली_config_flags_t	target_isp_flags[N_CHANNELS];
	target_sp_cfg_t			target_sp[N_CHANNELS];
	input_प्रणाली_config_flags_t	target_sp_flags[N_CHANNELS];
	target_strm2mem_cfg_t	target_strm2mem[N_CHANNELS];
	input_प्रणाली_config_flags_t	target_strm2mem_flags[N_CHANNELS];

	input_प्रणाली_config_flags_t		session_flags;

पूर्ण;

/*
 * For each MIPI port
 */
#घोषणा _HRT_CSS_RECEIVER_DEVICE_READY_REG_IDX			_HRT_CSS_RECEIVER_2400_DEVICE_READY_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_IRQ_STATUS_REG_IDX			_HRT_CSS_RECEIVER_2400_IRQ_STATUS_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_IRQ_ENABLE_REG_IDX			_HRT_CSS_RECEIVER_2400_IRQ_ENABLE_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_TIMEOUT_COUNT_REG_IDX		    _HRT_CSS_RECEIVER_2400_CSI2_FUNC_PROG_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_INIT_COUNT_REG_IDX			_HRT_CSS_RECEIVER_2400_INIT_COUNT_REG_IDX
/* new regs क्रम each MIPI port w.r.t. 2300 */
#घोषणा _HRT_CSS_RECEIVER_RAW16_18_DATAID_REG_IDX       _HRT_CSS_RECEIVER_2400_RAW16_18_DATAID_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_SYNC_COUNT_REG_IDX            _HRT_CSS_RECEIVER_2400_SYNC_COUNT_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_RX_COUNT_REG_IDX              _HRT_CSS_RECEIVER_2400_RX_COUNT_REG_IDX

/* _HRT_CSS_RECEIVER_2400_COMP_FORMAT_REG_IDX is not defined per MIPI port but per channel */
/* _HRT_CSS_RECEIVER_2400_COMP_PREDICT_REG_IDX is not defined per MIPI port but per channel */
#घोषणा _HRT_CSS_RECEIVER_FS_TO_LS_DELAY_REG_IDX        _HRT_CSS_RECEIVER_2400_FS_TO_LS_DELAY_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_LS_TO_DATA_DELAY_REG_IDX      _HRT_CSS_RECEIVER_2400_LS_TO_DATA_DELAY_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_DATA_TO_LE_DELAY_REG_IDX      _HRT_CSS_RECEIVER_2400_DATA_TO_LE_DELAY_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_LE_TO_FE_DELAY_REG_IDX        _HRT_CSS_RECEIVER_2400_LE_TO_FE_DELAY_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_FE_TO_FS_DELAY_REG_IDX        _HRT_CSS_RECEIVER_2400_FE_TO_FS_DELAY_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_LE_TO_LS_DELAY_REG_IDX        _HRT_CSS_RECEIVER_2400_LE_TO_LS_DELAY_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_TWO_PIXEL_EN_REG_IDX			_HRT_CSS_RECEIVER_2400_TWO_PIXEL_EN_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_BACKEND_RST_REG_IDX           _HRT_CSS_RECEIVER_2400_BACKEND_RST_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_RAW18_REG_IDX                 _HRT_CSS_RECEIVER_2400_RAW18_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_FORCE_RAW8_REG_IDX            _HRT_CSS_RECEIVER_2400_FORCE_RAW8_REG_IDX
#घोषणा _HRT_CSS_RECEIVER_RAW16_REG_IDX                 _HRT_CSS_RECEIVER_2400_RAW16_REG_IDX

/* Previously MIPI port regs, now 2x2 logical channel regs */
#घोषणा _HRT_CSS_RECEIVER_COMP_SCHEME_VC0_REG0_IDX		_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC0_REG0_IDX
#घोषणा _HRT_CSS_RECEIVER_COMP_SCHEME_VC0_REG1_IDX		_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC0_REG1_IDX
#घोषणा _HRT_CSS_RECEIVER_COMP_SCHEME_VC1_REG0_IDX		_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC1_REG0_IDX
#घोषणा _HRT_CSS_RECEIVER_COMP_SCHEME_VC1_REG1_IDX		_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC1_REG1_IDX
#घोषणा _HRT_CSS_RECEIVER_COMP_SCHEME_VC2_REG0_IDX		_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC2_REG0_IDX
#घोषणा _HRT_CSS_RECEIVER_COMP_SCHEME_VC2_REG1_IDX		_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC2_REG1_IDX
#घोषणा _HRT_CSS_RECEIVER_COMP_SCHEME_VC3_REG0_IDX		_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC3_REG0_IDX
#घोषणा _HRT_CSS_RECEIVER_COMP_SCHEME_VC3_REG1_IDX		_HRT_CSS_RECEIVER_2400_COMP_SCHEME_VC3_REG1_IDX

/* Second backend is at offset 0x0700 w.r.t. the first port at offset 0x0100 */
#घोषणा _HRT_CSS_BE_OFFSET                              448
#घोषणा _HRT_CSS_RECEIVER_BE_GSP_ACC_OVL_REG_IDX        (_HRT_CSS_RECEIVER_2400_BE_GSP_ACC_OVL_REG_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_SRST_REG_IDX               (_HRT_CSS_RECEIVER_2400_BE_SRST_REG_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_TWO_PPC_REG_IDX            (_HRT_CSS_RECEIVER_2400_BE_TWO_PPC_REG_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_COMP_FORMAT_REG0_IDX       (_HRT_CSS_RECEIVER_2400_BE_COMP_FORMAT_REG0_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_COMP_FORMAT_REG1_IDX       (_HRT_CSS_RECEIVER_2400_BE_COMP_FORMAT_REG1_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_COMP_FORMAT_REG2_IDX       (_HRT_CSS_RECEIVER_2400_BE_COMP_FORMAT_REG2_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_COMP_FORMAT_REG3_IDX       (_HRT_CSS_RECEIVER_2400_BE_COMP_FORMAT_REG3_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_SEL_REG_IDX                (_HRT_CSS_RECEIVER_2400_BE_SEL_REG_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_RAW16_CONFIG_REG_IDX       (_HRT_CSS_RECEIVER_2400_BE_RAW16_CONFIG_REG_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_RAW18_CONFIG_REG_IDX       (_HRT_CSS_RECEIVER_2400_BE_RAW18_CONFIG_REG_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_FORCE_RAW8_REG_IDX         (_HRT_CSS_RECEIVER_2400_BE_FORCE_RAW8_REG_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_IRQ_STATUS_REG_IDX         (_HRT_CSS_RECEIVER_2400_BE_IRQ_STATUS_REG_IDX + _HRT_CSS_BE_OFFSET)
#घोषणा _HRT_CSS_RECEIVER_BE_IRQ_CLEAR_REG_IDX          (_HRT_CSS_RECEIVER_2400_BE_IRQ_CLEAR_REG_IDX + _HRT_CSS_BE_OFFSET)

#घोषणा _HRT_CSS_RECEIVER_IRQ_OVERRUN_BIT		_HRT_CSS_RECEIVER_2400_IRQ_OVERRUN_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_INIT_TIMEOUT_BIT		_HRT_CSS_RECEIVER_2400_IRQ_RESERVED_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_ENTRY_BIT	_HRT_CSS_RECEIVER_2400_IRQ_SLEEP_MODE_ENTRY_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_EXIT_BIT	_HRT_CSS_RECEIVER_2400_IRQ_SLEEP_MODE_EXIT_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_SOT_HS_BIT		_HRT_CSS_RECEIVER_2400_IRQ_ERR_SOT_HS_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_SOT_SYNC_HS_BIT	_HRT_CSS_RECEIVER_2400_IRQ_ERR_SOT_SYNC_HS_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_CONTROL_BIT		_HRT_CSS_RECEIVER_2400_IRQ_ERR_CONTROL_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_ECC_DOUBLE_BIT	_HRT_CSS_RECEIVER_2400_IRQ_ERR_ECC_DOUBLE_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_ECC_CORRECTED_BIT	_HRT_CSS_RECEIVER_2400_IRQ_ERR_ECC_CORRECTED_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_ECC_NO_CORRECTION_BIT	_HRT_CSS_RECEIVER_2400_IRQ_ERR_ECC_NO_CORRECTION_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_CRC_BIT		_HRT_CSS_RECEIVER_2400_IRQ_ERR_CRC_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_ID_BIT		_HRT_CSS_RECEIVER_2400_IRQ_ERR_ID_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_SYNC_BIT	_HRT_CSS_RECEIVER_2400_IRQ_ERR_FRAME_SYNC_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_DATA_BIT	_HRT_CSS_RECEIVER_2400_IRQ_ERR_FRAME_DATA_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_DATA_TIMEOUT_BIT		_HRT_CSS_RECEIVER_2400_IRQ_DATA_TIMEOUT_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_ESCAPE_BIT		_HRT_CSS_RECEIVER_2400_IRQ_ERR_ESCAPE_BIT
#घोषणा _HRT_CSS_RECEIVER_IRQ_ERR_LINE_SYNC_BIT		_HRT_CSS_RECEIVER_2400_IRQ_ERR_LINE_SYNC_BIT

#घोषणा _HRT_CSS_RECEIVER_FUNC_PROG_REG_IDX		_HRT_CSS_RECEIVER_2400_CSI2_FUNC_PROG_REG_IDX
#घोषणा	_HRT_CSS_RECEIVER_DATA_TIMEOUT_IDX		_HRT_CSS_RECEIVER_2400_CSI2_DATA_TIMEOUT_IDX
#घोषणा	_HRT_CSS_RECEIVER_DATA_TIMEOUT_BITS		_HRT_CSS_RECEIVER_2400_CSI2_DATA_TIMEOUT_BITS

प्रकार काष्ठा capture_unit_state_s	capture_unit_state_t;
प्रकार काष्ठा acquisition_unit_state_s	acquisition_unit_state_t;
प्रकार काष्ठा ctrl_unit_state_s	ctrl_unit_state_t;

/*
 * In 2300 ports can be configured independently and stream
 * क्रमmats need to be specअगरied. In 2400, there are only 8
 * supported configurations but the HW is fused to support
 * only a single one.
 *
 * In 2300 the compressed क्रमmat types are programmed by the
 * user. In 2400 all stream क्रमmats are encoded on the stream.
 *
 * Use the क्रमागत to check validity of a user configuration
 */
प्रकार क्रमागत अणु
	MONO_4L_1L_0L = 0,
	MONO_3L_1L_0L,
	MONO_2L_1L_0L,
	MONO_1L_1L_0L,
	STEREO_2L_1L_2L,
	STEREO_3L_1L_1L,
	STEREO_2L_1L_1L,
	STEREO_1L_1L_1L,
	N_RX_MODE
पूर्ण rx_mode_t;

प्रकार क्रमागत अणु
	MIPI_PREDICTOR_NONE = 0,
	MIPI_PREDICTOR_TYPE1,
	MIPI_PREDICTOR_TYPE2,
	N_MIPI_PREDICTOR_TYPES
पूर्ण mipi_predictor_t;

प्रकार क्रमागत अणु
	MIPI_COMPRESSOR_NONE = 0,
	MIPI_COMPRESSOR_10_6_10,
	MIPI_COMPRESSOR_10_7_10,
	MIPI_COMPRESSOR_10_8_10,
	MIPI_COMPRESSOR_12_6_12,
	MIPI_COMPRESSOR_12_7_12,
	MIPI_COMPRESSOR_12_8_12,
	N_MIPI_COMPRESSOR_METHODS
पूर्ण mipi_compressor_t;

प्रकार क्रमागत अणु
	MIPI_FORMAT_RGB888 = 0,
	MIPI_FORMAT_RGB555,
	MIPI_FORMAT_RGB444,
	MIPI_FORMAT_RGB565,
	MIPI_FORMAT_RGB666,
	MIPI_FORMAT_RAW8,		/* 5 */
	MIPI_FORMAT_RAW10,
	MIPI_FORMAT_RAW6,
	MIPI_FORMAT_RAW7,
	MIPI_FORMAT_RAW12,
	MIPI_FORMAT_RAW14,		/* 10 */
	MIPI_FORMAT_YUV420_8,
	MIPI_FORMAT_YUV420_10,
	MIPI_FORMAT_YUV422_8,
	MIPI_FORMAT_YUV422_10,
	MIPI_FORMAT_CUSTOM0,	/* 15 */
	MIPI_FORMAT_YUV420_8_LEGACY,
	MIPI_FORMAT_EMBEDDED,
	MIPI_FORMAT_CUSTOM1,
	MIPI_FORMAT_CUSTOM2,
	MIPI_FORMAT_CUSTOM3,	/* 20 */
	MIPI_FORMAT_CUSTOM4,
	MIPI_FORMAT_CUSTOM5,
	MIPI_FORMAT_CUSTOM6,
	MIPI_FORMAT_CUSTOM7,
	MIPI_FORMAT_YUV420_8_SHIFT,	/* 25 */
	MIPI_FORMAT_YUV420_10_SHIFT,
	MIPI_FORMAT_RAW16,
	MIPI_FORMAT_RAW18,
	N_MIPI_FORMAT,
पूर्ण mipi_क्रमmat_t;

#घोषणा MIPI_FORMAT_JPEG		MIPI_FORMAT_CUSTOM0
#घोषणा MIPI_FORMAT_BINARY_8	MIPI_FORMAT_CUSTOM0
#घोषणा N_MIPI_FORMAT_CUSTOM	8

/* The number of stores क्रम compressed क्रमmat types */
#घोषणा	N_MIPI_COMPRESSOR_CONTEXT	(N_RX_CHANNEL_ID * N_MIPI_FORMAT_CUSTOM)

प्रकार क्रमागत अणु
	RX_IRQ_INFO_BUFFER_OVERRUN   = 1UL << _HRT_CSS_RECEIVER_IRQ_OVERRUN_BIT,
	RX_IRQ_INFO_INIT_TIMEOUT     = 1UL << _HRT_CSS_RECEIVER_IRQ_INIT_TIMEOUT_BIT,
	RX_IRQ_INFO_ENTER_SLEEP_MODE = 1UL << _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_ENTRY_BIT,
	RX_IRQ_INFO_EXIT_SLEEP_MODE  = 1UL << _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_EXIT_BIT,
	RX_IRQ_INFO_ECC_CORRECTED    = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_CORRECTED_BIT,
	RX_IRQ_INFO_ERR_SOT          = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_SOT_HS_BIT,
	RX_IRQ_INFO_ERR_SOT_SYNC     = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_SOT_SYNC_HS_BIT,
	RX_IRQ_INFO_ERR_CONTROL      = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_CONTROL_BIT,
	RX_IRQ_INFO_ERR_ECC_DOUBLE   = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_DOUBLE_BIT,
	/*	RX_IRQ_INFO_NO_ERR           = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_NO_CORRECTION_BIT, */
	RX_IRQ_INFO_ERR_CRC          = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_CRC_BIT,
	RX_IRQ_INFO_ERR_UNKNOWN_ID   = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_ID_BIT,
	RX_IRQ_INFO_ERR_FRAME_SYNC   = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_SYNC_BIT,
	RX_IRQ_INFO_ERR_FRAME_DATA   = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_DATA_BIT,
	RX_IRQ_INFO_ERR_DATA_TIMEOUT = 1UL << _HRT_CSS_RECEIVER_IRQ_DATA_TIMEOUT_BIT,
	RX_IRQ_INFO_ERR_UNKNOWN_ESC  = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_ESCAPE_BIT,
	RX_IRQ_INFO_ERR_LINE_SYNC    = 1UL << _HRT_CSS_RECEIVER_IRQ_ERR_LINE_SYNC_BIT,
पूर्ण  rx_irq_info_t;

प्रकार काष्ठा rx_cfg_s		rx_cfg_t;

/*
 * Applied per port
 */
काष्ठा rx_cfg_s अणु
	rx_mode_t			mode;	/* The HW config */
	क्रमागत mipi_port_id		port;	/* The port ID to apply the control on */
	अचिन्हित पूर्णांक		समयout;
	अचिन्हित पूर्णांक		initcount;
	अचिन्हित पूर्णांक		synccount;
	अचिन्हित पूर्णांक		rxcount;
	mipi_predictor_t	comp;	/* Just क्रम backward compatibility */
	bool                is_two_ppc;
पूर्ण;

/* NOTE: The base has alपढ़ोy an offset of 0x0100 */
अटल स्थिर hrt_address MIPI_PORT_OFFSET[N_MIPI_PORT_ID] = अणु
	0x00000000UL,
	0x00000100UL,
	0x00000200UL
पूर्ण;

अटल स्थिर mipi_lane_cfg_t MIPI_PORT_MAXLANES[N_MIPI_PORT_ID] = अणु
	MIPI_4LANE_CFG,
	MIPI_1LANE_CFG,
	MIPI_2LANE_CFG
पूर्ण;

अटल स्थिर bool MIPI_PORT_ACTIVE[N_RX_MODE][N_MIPI_PORT_ID] = अणु
	अणुtrue, true, falseपूर्ण,
	अणुtrue, true, falseपूर्ण,
	अणुtrue, true, falseपूर्ण,
	अणुtrue, true, falseपूर्ण,
	अणुtrue, true, trueपूर्ण,
	अणुtrue, true, trueपूर्ण,
	अणुtrue, true, trueपूर्ण,
	अणुtrue, true, trueपूर्ण
पूर्ण;

अटल स्थिर mipi_lane_cfg_t MIPI_PORT_LANES[N_RX_MODE][N_MIPI_PORT_ID] = अणु
	अणुMIPI_4LANE_CFG, MIPI_1LANE_CFG, MIPI_0LANE_CFGपूर्ण,
	अणुMIPI_3LANE_CFG, MIPI_1LANE_CFG, MIPI_0LANE_CFGपूर्ण,
	अणुMIPI_2LANE_CFG, MIPI_1LANE_CFG, MIPI_0LANE_CFGपूर्ण,
	अणुMIPI_1LANE_CFG, MIPI_1LANE_CFG, MIPI_0LANE_CFGपूर्ण,
	अणुMIPI_2LANE_CFG, MIPI_1LANE_CFG, MIPI_2LANE_CFGपूर्ण,
	अणुMIPI_3LANE_CFG, MIPI_1LANE_CFG, MIPI_1LANE_CFGपूर्ण,
	अणुMIPI_2LANE_CFG, MIPI_1LANE_CFG, MIPI_1LANE_CFGपूर्ण,
	अणुMIPI_1LANE_CFG, MIPI_1LANE_CFG, MIPI_1LANE_CFGपूर्ण
पूर्ण;

अटल स्थिर hrt_address SUB_SYSTEM_OFFSET[N_SUB_SYSTEM_ID] = अणु
	0x00001000UL,
	0x00002000UL,
	0x00003000UL,
	0x00004000UL,
	0x00005000UL,
	0x00009000UL,
	0x0000A000UL,
	0x0000B000UL,
	0x0000C000UL
पूर्ण;

काष्ठा capture_unit_state_s अणु
	पूर्णांक	Packet_Length;
	पूर्णांक	Received_Length;
	पूर्णांक	Received_Short_Packets;
	पूर्णांक	Received_Long_Packets;
	पूर्णांक	Last_Command;
	पूर्णांक	Next_Command;
	पूर्णांक	Last_Acknowledge;
	पूर्णांक	Next_Acknowledge;
	पूर्णांक	FSM_State_Info;
	पूर्णांक	StartMode;
	पूर्णांक	Start_Addr;
	पूर्णांक	Mem_Region_Size;
	पूर्णांक	Num_Mem_Regions;
	/*	पूर्णांक	Init;   ग_लिखो-only रेजिस्टरs
		पूर्णांक	Start;
		पूर्णांक	Stop;      */
पूर्ण;

काष्ठा acquisition_unit_state_s अणु
	/*	पूर्णांक	Init;   ग_लिखो-only रेजिस्टर */
	पूर्णांक	Received_Short_Packets;
	पूर्णांक	Received_Long_Packets;
	पूर्णांक	Last_Command;
	पूर्णांक	Next_Command;
	पूर्णांक	Last_Acknowledge;
	पूर्णांक	Next_Acknowledge;
	पूर्णांक	FSM_State_Info;
	पूर्णांक	Int_Cntr_Info;
	पूर्णांक	Start_Addr;
	पूर्णांक	Mem_Region_Size;
	पूर्णांक	Num_Mem_Regions;
पूर्ण;

काष्ठा ctrl_unit_state_s अणु
	पूर्णांक	last_cmd;
	पूर्णांक	next_cmd;
	पूर्णांक	last_ack;
	पूर्णांक	next_ack;
	पूर्णांक	top_fsm_state;
	पूर्णांक	captA_fsm_state;
	पूर्णांक	captB_fsm_state;
	पूर्णांक	captC_fsm_state;
	पूर्णांक	acq_fsm_state;
	पूर्णांक	captA_start_addr;
	पूर्णांक	captB_start_addr;
	पूर्णांक	captC_start_addr;
	पूर्णांक	captA_mem_region_size;
	पूर्णांक	captB_mem_region_size;
	पूर्णांक	captC_mem_region_size;
	पूर्णांक	captA_num_mem_regions;
	पूर्णांक	captB_num_mem_regions;
	पूर्णांक	captC_num_mem_regions;
	पूर्णांक	acq_start_addr;
	पूर्णांक	acq_mem_region_size;
	पूर्णांक	acq_num_mem_regions;
	/*	पूर्णांक	ctrl_init;  ग_लिखो only रेजिस्टर */
	पूर्णांक	capt_reserve_one_mem_region;
पूर्ण;

काष्ठा input_प्रणाली_state_s अणु
	पूर्णांक	str_multicastA_sel;
	पूर्णांक	str_multicastB_sel;
	पूर्णांक	str_multicastC_sel;
	पूर्णांक	str_mux_sel;
	पूर्णांक	str_mon_status;
	पूर्णांक	str_mon_irq_cond;
	पूर्णांक	str_mon_irq_en;
	पूर्णांक	isys_srst;
	पूर्णांक	isys_slv_reg_srst;
	पूर्णांक	str_deपूर्णांक_portA_cnt;
	पूर्णांक	str_deपूर्णांक_portB_cnt;
	काष्ठा capture_unit_state_s		capture_unit[N_CAPTURE_UNIT_ID];
	काष्ठा acquisition_unit_state_s	acquisition_unit[N_ACQUISITION_UNIT_ID];
	काष्ठा ctrl_unit_state_s		ctrl_unit_state[N_CTRL_UNIT_ID];
पूर्ण;

काष्ठा mipi_port_state_s अणु
	पूर्णांक	device_पढ़ोy;
	पूर्णांक	irq_status;
	पूर्णांक	irq_enable;
	u32	समयout_count;
	u16	init_count;
	u16	raw16_18;
	u32	sync_count;		/*4 x uपूर्णांक8_t */
	u32	rx_count;		/*4 x uपूर्णांक8_t */
	u8		lane_sync_count[MIPI_4LANE_CFG];
	u8		lane_rx_count[MIPI_4LANE_CFG];
पूर्ण;

काष्ठा rx_channel_state_s अणु
	u32	comp_scheme0;
	u32	comp_scheme1;
	mipi_predictor_t		pred[N_MIPI_FORMAT_CUSTOM];
	mipi_compressor_t		comp[N_MIPI_FORMAT_CUSTOM];
पूर्ण;

काष्ठा receiver_state_s अणु
	u8	fs_to_ls_delay;
	u8	ls_to_data_delay;
	u8	data_to_le_delay;
	u8	le_to_fe_delay;
	u8	fe_to_fs_delay;
	u8	le_to_fs_delay;
	bool	is_two_ppc;
	पूर्णांक	backend_rst;
	u16	raw18;
	bool		क्रमce_raw8;
	u16	raw16;
	काष्ठा mipi_port_state_s	mipi_port_state[N_MIPI_PORT_ID];
	काष्ठा rx_channel_state_s	rx_channel_state[N_RX_CHANNEL_ID];
	पूर्णांक	be_gsp_acc_ovl;
	पूर्णांक	be_srst;
	पूर्णांक	be_is_two_ppc;
	पूर्णांक	be_comp_क्रमmat0;
	पूर्णांक	be_comp_क्रमmat1;
	पूर्णांक	be_comp_क्रमmat2;
	पूर्णांक	be_comp_क्रमmat3;
	पूर्णांक	be_sel;
	पूर्णांक	be_raw16_config;
	पूर्णांक	be_raw18_config;
	पूर्णांक	be_क्रमce_raw8;
	पूर्णांक	be_irq_status;
	पूर्णांक	be_irq_clear;
पूर्ण;

#पूर्ण_अगर /* __INPUT_SYSTEM_LOCAL_H_INCLUDED__ */
