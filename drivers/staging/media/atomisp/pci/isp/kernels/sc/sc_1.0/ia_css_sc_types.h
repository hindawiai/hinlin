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

#अगर_अघोषित __IA_CSS_SC_TYPES_H
#घोषणा __IA_CSS_SC_TYPES_H

/* @file
* CSS-API header file क्रम Lens Shading Correction (SC) parameters.
*/

/* Number of color planes in the shading table. */
#घोषणा IA_CSS_SC_NUM_COLORS           4

/* The 4 colors that a shading table consists of.
 *  For each color we store a grid of values.
 */
क्रमागत ia_css_sc_color अणु
	IA_CSS_SC_COLOR_GR, /** Green on a green-red line */
	IA_CSS_SC_COLOR_R,  /** Red */
	IA_CSS_SC_COLOR_B,  /** Blue */
	IA_CSS_SC_COLOR_GB  /** Green on a green-blue line */
पूर्ण;

/* Lens Shading Correction table.
 *
 *  This describes the color shading artefacts
 *  पूर्णांकroduced by lens imperfections. To correct artefacts,
 *  bayer values should be multiplied by gains in this table.
 *
 *------------ deprecated(bz675) : from ---------------------------
 *  When shading_settings.enable_shading_table_conversion is set as 0,
 *  this shading table is directly sent to the isp. This table should contain
 *  the data based on the ia_css_shading_info inक्रमmation filled in the css.
 *  So, the driver needs to get the ia_css_shading_info inक्रमmation
 *  from the css, prior to generating the shading table.
 *
 *  When shading_settings.enable_shading_table_conversion is set as 1,
 *  this shading table is converted in the legacy way in the css
 *  beक्रमe it is sent to the isp.
 *  The driver करोes not need to get the ia_css_shading_info inक्रमmation.
 *
 *  NOTE:
 *  The shading table conversion will be हटाओd from the css in the near future,
 *  because it करोes not support the bayer scaling by sensor.
 *  Also, we had better generate the shading table only in one place(AIC).
 *  At the moment, to support the old driver which assumes the conversion is करोne in the css,
 *  shading_settings.enable_shading_table_conversion is set as 1 by शेष.
 *------------ deprecated(bz675) : to ---------------------------
 *
 *  ISP block: SC1
 *  ISP1: SC1 is used.
 *  ISP2: SC1 is used.
 */
काष्ठा ia_css_shading_table अणु
	u32 enable; /** Set to false क्रम no shading correction.
			  The data field can be शून्य when enable == true */
	/* ------ deprecated(bz675) : from ------ */
	u32 sensor_width;  /** Native sensor width in pixels. */
	u32 sensor_height; /** Native sensor height in lines.
		When shading_settings.enable_shading_table_conversion is set
		as 0, sensor_width and sensor_height are NOT used.
		These are used only in the legacy shading table conversion
		in the css, when shading_settings.
		enable_shading_table_conversion is set as 1. */
	/* ------ deprecated(bz675) : to ------ */
	u32 width;  /** Number of data poपूर्णांकs per line per color.
				u8.0, [0,81] */
	u32 height; /** Number of lines of data poपूर्णांकs per color.
				u8.0, [0,61] */
	u32 fraction_bits; /** Bits of fractional part in the data
				poपूर्णांकs.
				u8.0, [0,13] */
	u16 *data[IA_CSS_SC_NUM_COLORS];
	/** Table data, one array क्रम each color.
	     Use ia_css_sc_color to index this array.
	     u[13-fraction_bits].[fraction_bits], [0,8191] */
पूर्ण;

/* ------ deprecated(bz675) : from ------ */
/* Shading Correction settings.
 *
 *  NOTE:
 *  This काष्ठाure should be हटाओd when the shading table conversion is
 *  हटाओd from the css.
 */
काष्ठा ia_css_shading_settings अणु
	u32 enable_shading_table_conversion; /** Set to 0,
		अगर the conversion of the shading table should be disabled
		in the css. (शेष 1)
		  0: The shading table is directly sent to the isp.
		     The shading table should contain the data based on the
		     ia_css_shading_info inक्रमmation filled in the css.
		  1: The shading table is converted in the css, to be fitted
		     to the shading table definition required in the isp.
		NOTE:
		Previously, the shading table was always converted in the css
		beक्रमe it was sent to the isp, and this config was not defined.
		Currently, the driver is supposed to pass the shading table
		which should be directly sent to the isp.
		However, some drivers may still pass the shading table which
		needs the conversion without setting this config as 1.
		To support such an unexpected हाल क्रम the समय being,
		enable_shading_table_conversion is set as 1 by शेष
		in the css. */
पूर्ण;

/* ------ deprecated(bz675) : to ------ */

/* Shading Correction configuration.
 *
 *  NOTE: The shading table size is larger than or equal to the पूर्णांकernal frame size.
 */
/* ISP2401 */
काष्ठा ia_css_sc_configuration अणु
	u32 पूर्णांकernal_frame_origin_x_bqs_on_sctbl; /** Origin X (in bqs) of पूर्णांकernal frame on shading table. */
	u32 पूर्णांकernal_frame_origin_y_bqs_on_sctbl; /** Origin Y (in bqs) of पूर्णांकernal frame on shading table. */
	/** NOTE: bqs = size in BQ(Bayer Quad) unit.
		1BQ means अणुGr,R,B,Gbपूर्ण(2x2 pixels).
		Horizontal 1 bqs corresponds to horizontal 2 pixels.
		Vertical 1 bqs corresponds to vertical 2 pixels. */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_SC_TYPES_H */
