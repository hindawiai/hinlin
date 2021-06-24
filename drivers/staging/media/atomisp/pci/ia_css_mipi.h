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

#अगर_अघोषित __IA_CSS_MIPI_H
#घोषणा __IA_CSS_MIPI_H

/* @file
 * This file contains MIPI support functionality
 */

#समावेश <type_support.h>
#समावेश "ia_css_err.h"
#समावेश "ia_css_stream_format.h"
#समावेश "ia_css_input_port.h"

/* @brief Register size of a CSS MIPI frame क्रम check during capturing.
 *
 * @param[in]	port	CSI-2 port this check is रेजिस्टरed.
 * @param[in]	size_mem_words	The frame size in memory words (32B).
 * @वापस		Return the error in हाल of failure. E.g. MAX_NOF_ENTRIES REACHED
 *
 * Register size of a CSS MIPI frame to check during capturing. Up to
 *		IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTRIES entries per port allowed. Entries are reset
 *		when stream is stopped.
 *
 *
 */
पूर्णांक
ia_css_mipi_frame_enable_check_on_size(स्थिर क्रमागत mipi_port_id port,
				       स्थिर अचिन्हित पूर्णांक	size_mem_words);

/* @brief Calculate the size of a mipi frame.
 *
 * @param[in]	width		The width (in pixels) of the frame.
 * @param[in]	height		The height (in lines) of the frame.
 * @param[in]	क्रमmat		The frame (MIPI) क्रमmat.
 * @param[in]	hasSOLandEOL	Whether frame (MIPI) contains (optional) SOL and खातापूर्ण packets.
 * @param[in]	embedded_data_size_words		Embedded data size in memory words.
 * @param		size_mem_words					The mipi frame size in memory words (32B).
 * @वापस		The error code.
 *
 * Calculate the size of a mipi frame, based on the resolution and क्रमmat.
 */
पूर्णांक
ia_css_mipi_frame_calculate_size(स्थिर अचिन्हित पूर्णांक width,
				 स्थिर अचिन्हित पूर्णांक height,
				 स्थिर क्रमागत atomisp_input_क्रमmat क्रमmat,
				 स्थिर bool hasSOLandEOL,
				 स्थिर अचिन्हित पूर्णांक embedded_data_size_words,
				 अचिन्हित पूर्णांक *size_mem_words);

#पूर्ण_अगर /* __IA_CSS_MIPI_H */
