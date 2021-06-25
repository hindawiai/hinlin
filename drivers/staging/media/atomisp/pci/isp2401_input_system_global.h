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

/* CSI reveiver has 3 ports. */
#घोषणा		N_CSI_PORTS (3)

#समावेश "system_local.h"
#समावेश "isys_dma_global.h"	/*	isys2401_dma_channel,
				 *	isys2401_dma_cfg_t
				 */

#समावेश "ibuf_ctrl_local.h"	/*	ibuf_cfg_t,
				 *	ibuf_ctrl_cfg_t
				 */

#समावेश "isys_stream2mmio.h"	/*	stream2mmio_cfg_t */

#समावेश "csi_rx.h"		/*	csi_rx_frontend_cfg_t,
				 *	csi_rx_backend_cfg_t,
				 *	csi_rx_backend_lut_entry_t
				 */
#समावेश "pixelgen.h"

#घोषणा INPUT_SYSTEM_N_STREAM_ID  6	/* maximum number of simultaneous
					भव channels supported*/

प्रकार क्रमागत अणु
	INPUT_SYSTEM_SOURCE_TYPE_UNDEFINED = 0,
	INPUT_SYSTEM_SOURCE_TYPE_SENSOR,
	INPUT_SYSTEM_SOURCE_TYPE_TPG,
	INPUT_SYSTEM_SOURCE_TYPE_PRBS,
	N_INPUT_SYSTEM_SOURCE_TYPE
पूर्ण input_प्रणाली_source_type_t;

प्रकार क्रमागत अणु
	INPUT_SYSTEM_POLL_ON_WAIT_FOR_FRAME,
	INPUT_SYSTEM_POLL_ON_CAPTURE_REQUEST,
पूर्ण input_प्रणाली_polling_mode_t;

प्रकार काष्ठा input_प्रणाली_channel_s input_प्रणाली_channel_t;
काष्ठा input_प्रणाली_channel_s अणु
	stream2mmio_ID_t	stream2mmio_id;
	stream2mmio_sid_ID_t	stream2mmio_sid_id;

	ibuf_ctrl_ID_t		ibuf_ctrl_id;
	isp2401_ib_buffer_t	ib_buffer;

	isys2401_dma_ID_t	dma_id;
	isys2401_dma_channel	dma_channel;
पूर्ण;

प्रकार काष्ठा input_प्रणाली_channel_cfg_s input_प्रणाली_channel_cfg_t;
काष्ठा input_प्रणाली_channel_cfg_s अणु
	stream2mmio_cfg_t	stream2mmio_cfg;
	ibuf_ctrl_cfg_t		ibuf_ctrl_cfg;
	isys2401_dma_cfg_t	dma_cfg;
	isys2401_dma_port_cfg_t	dma_src_port_cfg;
	isys2401_dma_port_cfg_t	dma_dest_port_cfg;
पूर्ण;

प्रकार काष्ठा input_प्रणाली_input_port_s input_प्रणाली_input_port_t;
काष्ठा input_प्रणाली_input_port_s अणु
	input_प्रणाली_source_type_t	source_type;

	काष्ठा अणु
		csi_rx_frontend_ID_t		frontend_id;
		csi_rx_backend_ID_t		backend_id;
		csi_mipi_packet_type_t		packet_type;
		csi_rx_backend_lut_entry_t	backend_lut_entry;
	पूर्ण csi_rx;

	काष्ठा अणु
		csi_mipi_packet_type_t		packet_type;
		csi_rx_backend_lut_entry_t	backend_lut_entry;
	पूर्ण metadata;

	काष्ठा अणु
		pixelgen_ID_t			pixelgen_id;
	पूर्ण pixelgen;
पूर्ण;

प्रकार काष्ठा input_प्रणाली_input_port_cfg_s input_प्रणाली_input_port_cfg_t;
काष्ठा input_प्रणाली_input_port_cfg_s अणु
	काष्ठा अणु
		csi_rx_frontend_cfg_t	frontend_cfg;
		csi_rx_backend_cfg_t	backend_cfg;
		csi_rx_backend_cfg_t	md_backend_cfg;
	पूर्ण csi_rx_cfg;

	काष्ठा अणु
		pixelgen_tpg_cfg_t	tpg_cfg;
		pixelgen_prbs_cfg_t	prbs_cfg;
	पूर्ण pixelgen_cfg;
पूर्ण;

प्रकार काष्ठा isp2401_input_प्रणाली_cfg_s isp2401_input_प्रणाली_cfg_t;
काष्ठा isp2401_input_प्रणाली_cfg_s अणु
	input_प्रणाली_input_port_ID_t	input_port_id;

	input_प्रणाली_source_type_t	mode;

	/* ISP2401 */
	input_प्रणाली_polling_mode_t	polling_mode;

	bool online;
	bool raw_packed;
	s8 linked_isys_stream_id;

	काष्ठा अणु
		bool	comp_enable;
		s32	active_lanes;
		s32	fmt_type;
		s32	ch_id;
		s32 comp_predictor;
		s32 comp_scheme;
	पूर्ण csi_port_attr;

	pixelgen_tpg_cfg_t	tpg_port_attr;

	pixelgen_prbs_cfg_t prbs_port_attr;

	काष्ठा अणु
		s32 align_req_in_bytes;
		s32 bits_per_pixel;
		s32 pixels_per_line;
		s32 lines_per_frame;
	पूर्ण input_port_resolution;

	काष्ठा अणु
		s32 left_padding;
		s32 max_isp_input_width;
	पूर्ण output_port_attr;

	काष्ठा अणु
		bool    enable;
		s32 fmt_type;
		s32 align_req_in_bytes;
		s32 bits_per_pixel;
		s32 pixels_per_line;
		s32 lines_per_frame;
	पूर्ण metadata;
पूर्ण;

प्रकार काष्ठा भव_input_प्रणाली_stream_s भव_input_प्रणाली_stream_t;
काष्ठा भव_input_प्रणाली_stream_s अणु
	u32 id;				/*Used when multiple MIPI data types and/or भव channels are used.
								Must be unique within one CSI RX
								and lower than SH_CSS_MAX_ISYS_CHANNEL_NODES */
	u8 enable_metadata;
	input_प्रणाली_input_port_t	input_port;
	input_प्रणाली_channel_t		channel;
	input_प्रणाली_channel_t		md_channel; /* metadata channel */
	u8 online;
	s8 linked_isys_stream_id;
	u8 valid;

	/* ISP2401 */
	input_प्रणाली_polling_mode_t	polling_mode;
	s32 subscr_index;
पूर्ण;

प्रकार काष्ठा भव_input_प्रणाली_stream_cfg_s
	भव_input_प्रणाली_stream_cfg_t;
काष्ठा भव_input_प्रणाली_stream_cfg_s अणु
	u8 enable_metadata;
	input_प्रणाली_input_port_cfg_t	input_port_cfg;
	input_प्रणाली_channel_cfg_t	channel_cfg;
	input_प्रणाली_channel_cfg_t	md_channel_cfg;
	u8 valid;
पूर्ण;

#घोषणा ISP_INPUT_BUF_START_ADDR	0
#घोषणा NUM_OF_INPUT_BUF		2
#घोषणा NUM_OF_LINES_PER_BUF		2
#घोषणा LINES_OF_ISP_INPUT_BUF		(NUM_OF_INPUT_BUF * NUM_OF_LINES_PER_BUF)
#घोषणा ISP_INPUT_BUF_STRIDE		SH_CSS_MAX_SENSOR_WIDTH
