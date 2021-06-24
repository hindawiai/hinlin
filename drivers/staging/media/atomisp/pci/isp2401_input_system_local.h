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

#अगर_अघोषित __INPUT_SYSTEM_LOCAL_H_INCLUDED__
#घोषणा __INPUT_SYSTEM_LOCAL_H_INCLUDED__

#समावेश "type_support.h"
#समावेश "input_system_global.h"

#समावेश "csi_rx.h"
#समावेश "pixelgen.h"
#समावेश "isys_stream2mmio.h"
#समावेश "isys_irq.h"

प्रकार क्रमागत अणु
	MIPI_FORMAT_SHORT1 = 0x08,
	MIPI_FORMAT_SHORT2,
	MIPI_FORMAT_SHORT3,
	MIPI_FORMAT_SHORT4,
	MIPI_FORMAT_SHORT5,
	MIPI_FORMAT_SHORT6,
	MIPI_FORMAT_SHORT7,
	MIPI_FORMAT_SHORT8,
	MIPI_FORMAT_EMBEDDED = 0x12,
	MIPI_FORMAT_YUV420_8 = 0x18,
	MIPI_FORMAT_YUV420_10,
	MIPI_FORMAT_YUV420_8_LEGACY,
	MIPI_FORMAT_YUV420_8_SHIFT = 0x1C,
	MIPI_FORMAT_YUV420_10_SHIFT,
	MIPI_FORMAT_YUV422_8 = 0x1E,
	MIPI_FORMAT_YUV422_10,
	MIPI_FORMAT_RGB444 = 0x20,
	MIPI_FORMAT_RGB555,
	MIPI_FORMAT_RGB565,
	MIPI_FORMAT_RGB666,
	MIPI_FORMAT_RGB888,
	MIPI_FORMAT_RAW6 = 0x28,
	MIPI_FORMAT_RAW7,
	MIPI_FORMAT_RAW8,
	MIPI_FORMAT_RAW10,
	MIPI_FORMAT_RAW12,
	MIPI_FORMAT_RAW14,
	MIPI_FORMAT_CUSTOM0 = 0x30,
	MIPI_FORMAT_CUSTOM1,
	MIPI_FORMAT_CUSTOM2,
	MIPI_FORMAT_CUSTOM3,
	MIPI_FORMAT_CUSTOM4,
	MIPI_FORMAT_CUSTOM5,
	MIPI_FORMAT_CUSTOM6,
	MIPI_FORMAT_CUSTOM7,
	//MIPI_FORMAT_RAW16, /*not supported by 2401*/
	//MIPI_FORMAT_RAW18,
	N_MIPI_FORMAT
पूर्ण mipi_क्रमmat_t;

#घोषणा N_MIPI_FORMAT_CUSTOM	8

/* The number of stores क्रम compressed क्रमmat types */
#घोषणा	N_MIPI_COMPRESSOR_CONTEXT	(N_RX_CHANNEL_ID * N_MIPI_FORMAT_CUSTOM)
#घोषणा UNCOMPRESSED_BITS_PER_PIXEL_10	10
#घोषणा UNCOMPRESSED_BITS_PER_PIXEL_12	12
#घोषणा COMPRESSED_BITS_PER_PIXEL_6	6
#घोषणा COMPRESSED_BITS_PER_PIXEL_7	7
#घोषणा COMPRESSED_BITS_PER_PIXEL_8	8
क्रमागत mipi_compressor अणु
	MIPI_COMPRESSOR_NONE = 0,
	MIPI_COMPRESSOR_10_6_10,
	MIPI_COMPRESSOR_10_7_10,
	MIPI_COMPRESSOR_10_8_10,
	MIPI_COMPRESSOR_12_6_12,
	MIPI_COMPRESSOR_12_7_12,
	MIPI_COMPRESSOR_12_8_12,
	N_MIPI_COMPRESSOR_METHODS
पूर्ण;

प्रकार क्रमागत अणु
	MIPI_PREDICTOR_NONE = 0,
	MIPI_PREDICTOR_TYPE1,
	MIPI_PREDICTOR_TYPE2,
	N_MIPI_PREDICTOR_TYPES
पूर्ण mipi_predictor_t;

प्रकार काष्ठा input_प्रणाली_state_s	input_प्रणाली_state_t;
काष्ठा input_प्रणाली_state_s अणु
	ibuf_ctrl_state_t	ibuf_ctrl_state[N_IBUF_CTRL_ID];
	csi_rx_fe_ctrl_state_t	csi_rx_fe_ctrl_state[N_CSI_RX_FRONTEND_ID];
	csi_rx_be_ctrl_state_t	csi_rx_be_ctrl_state[N_CSI_RX_BACKEND_ID];
	pixelgen_ctrl_state_t	pixelgen_ctrl_state[N_PIXELGEN_ID];
	stream2mmio_state_t	stream2mmio_state[N_STREAM2MMIO_ID];
	isys_irqc_state_t	isys_irqc_state[N_ISYS_IRQ_ID];
पूर्ण;
#पूर्ण_अगर /* __INPUT_SYSTEM_LOCAL_H_INCLUDED__ */
