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

/* For MIPI_PORT0_ID to MIPI_PORT2_ID */
#समावेश "system_global.h"

#अगर_अघोषित __IA_CSS_INPUT_PORT_H
#घोषणा __IA_CSS_INPUT_PORT_H

/* @file
 * This file contains inक्रमmation about the possible input ports क्रम CSS
 */

/* Backward compatible क्रम CSS API 2.0 only
 *  TO BE REMOVED when all drivers move to CSS	API 2.1
 */
#घोषणा	IA_CSS_CSI2_PORT_4LANE MIPI_PORT0_ID
#घोषणा	IA_CSS_CSI2_PORT_1LANE MIPI_PORT1_ID
#घोषणा	IA_CSS_CSI2_PORT_2LANE MIPI_PORT2_ID

/* The CSI2 पूर्णांकerface supports 2 types of compression or can
 *  be run without compression.
 */
क्रमागत ia_css_csi2_compression_type अणु
	IA_CSS_CSI2_COMPRESSION_TYPE_NONE, /** No compression */
	IA_CSS_CSI2_COMPRESSION_TYPE_1,    /** Compression scheme 1 */
	IA_CSS_CSI2_COMPRESSION_TYPE_2     /** Compression scheme 2 */
पूर्ण;

काष्ठा ia_css_csi2_compression अणु
	क्रमागत ia_css_csi2_compression_type type;
	/** Compression used */
	अचिन्हित पूर्णांक                      compressed_bits_per_pixel;
	/** Compressed bits per pixel (only when compression is enabled) */
	अचिन्हित पूर्णांक                      uncompressed_bits_per_pixel;
	/** Uncompressed bits per pixel (only when compression is enabled) */
पूर्ण;

/* Input port काष्ठाure.
 */
काष्ठा ia_css_input_port अणु
	क्रमागत mipi_port_id port; /** Physical CSI-2 port */
	अचिन्हित पूर्णांक num_lanes; /** Number of lanes used (4-lane port only) */
	अचिन्हित पूर्णांक समयout;   /** Timeout value */
	अचिन्हित पूर्णांक rxcount;   /** Register value, should include all lanes */
	काष्ठा ia_css_csi2_compression compression; /** Compression used */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_INPUT_PORT_H */
