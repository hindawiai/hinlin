<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Release Version: irci_stable_candrpv_0415_20150521_0458 */
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

#अगर_अघोषित _IA_CSS_TYPES_H
#घोषणा _IA_CSS_TYPES_H

/* @file
 * This file contains types used क्रम the ia_css parameters.
 * These types are in a separate file because they are expected
 * to be used in software layers that करो not access the CSS API
 * directly but still need to क्रमward parameters क्रम it.
 */

#समावेश <type_support.h>

#समावेश "ia_css_frac.h"

#समावेश "isp/kernels/aa/aa_2/ia_css_aa2_types.h"
#समावेश "isp/kernels/anr/anr_1.0/ia_css_anr_types.h"
#समावेश "isp/kernels/anr/anr_2/ia_css_anr2_types.h"
#समावेश "isp/kernels/cnr/cnr_2/ia_css_cnr2_types.h"
#समावेश "isp/kernels/csc/csc_1.0/ia_css_csc_types.h"
#समावेश "isp/kernels/ctc/ctc_1.0/ia_css_ctc_types.h"
#समावेश "isp/kernels/dp/dp_1.0/ia_css_dp_types.h"
#समावेश "isp/kernels/de/de_1.0/ia_css_de_types.h"
#समावेश "isp/kernels/de/de_2/ia_css_de2_types.h"
#समावेश "isp/kernels/fc/fc_1.0/ia_css_formats_types.h"
#समावेश "isp/kernels/fpn/fpn_1.0/ia_css_fpn_types.h"
#समावेश "isp/kernels/gc/gc_1.0/ia_css_gc_types.h"
#समावेश "isp/kernels/gc/gc_2/ia_css_gc2_types.h"
#समावेश "isp/kernels/macc/macc_1.0/ia_css_macc_types.h"
#समावेश "isp/kernels/ob/ob_1.0/ia_css_ob_types.h"
#समावेश "isp/kernels/s3a/s3a_1.0/ia_css_s3a_types.h"
#समावेश "isp/kernels/sc/sc_1.0/ia_css_sc_types.h"
#समावेश "isp/kernels/sdis/sdis_1.0/ia_css_sdis_types.h"
#समावेश "isp/kernels/sdis/sdis_2/ia_css_sdis2_types.h"
#समावेश "isp/kernels/tnr/tnr_1.0/ia_css_tnr_types.h"
#समावेश "isp/kernels/wb/wb_1.0/ia_css_wb_types.h"
#समावेश "isp/kernels/xnr/xnr_1.0/ia_css_xnr_types.h"
#समावेश "isp/kernels/xnr/xnr_3.0/ia_css_xnr3_types.h"

/* ISP2401 */
#समावेश "isp/kernels/tnr/tnr3/ia_css_tnr3_types.h"

#समावेश "isp/kernels/ynr/ynr_1.0/ia_css_ynr_types.h"
#समावेश "isp/kernels/ynr/ynr_2/ia_css_ynr2_types.h"
#समावेश "isp/kernels/output/output_1.0/ia_css_output_types.h"

#घोषणा IA_CSS_DVS_STAT_GRID_INFO_SUPPORTED
/** Should be हटाओd after Driver adaptation will be करोne */

#घोषणा IA_CSS_VERSION_MAJOR    2
#घोषणा IA_CSS_VERSION_MINOR    0
#घोषणा IA_CSS_VERSION_REVISION 2

#घोषणा IA_CSS_MORPH_TABLE_NUM_PLANES  6

/* Min and max exposure IDs. These macros are here to allow
 * the drivers to get this inक्रमmation. Changing these macros
 * स्थिरitutes a CSS API change. */
#घोषणा IA_CSS_ISYS_MIN_EXPOSURE_ID 1   /** Minimum exposure ID */
#घोषणा IA_CSS_ISYS_MAX_EXPOSURE_ID 250 /** Maximum exposure ID */

/* opaque types */
काष्ठा ia_css_isp_parameters;
काष्ठा ia_css_pipe;
काष्ठा ia_css_memory_offsets;
काष्ठा ia_css_config_memory_offsets;
काष्ठा ia_css_state_memory_offsets;

/* Virtual address within the CSS address space. */
प्रकार u32 ia_css_ptr;

/* Generic resolution काष्ठाure.
 */
काष्ठा ia_css_resolution अणु
	u32 width;  /** Width */
	u32 height; /** Height */
पूर्ण;

/* Generic coordinate काष्ठाure.
 */
काष्ठा ia_css_coordinate अणु
	s32 x;	/** Value of a coordinate on the horizontal axis */
	s32 y;	/** Value of a coordinate on the vertical axis */
पूर्ण;

/* Vector with चिन्हित values. This is used to indicate motion क्रम
 * Digital Image Stabilization.
 */
काष्ठा ia_css_vector अणु
	s32 x; /** horizontal motion (in pixels) */
	s32 y; /** vertical motion (in pixels) */
पूर्ण;

/* Short hands */
#घोषणा IA_CSS_ISP_DMEM IA_CSS_ISP_DMEM0
#घोषणा IA_CSS_ISP_VMEM IA_CSS_ISP_VMEM0

/* CSS data descriptor */
काष्ठा ia_css_data अणु
	ia_css_ptr address; /** CSS भव address */
	u32   size;    /** Disabled अगर 0 */
पूर्ण;

/* Host data descriptor */
काष्ठा ia_css_host_data अणु
	अक्षर      *address; /** Host address */
	u32   size;    /** Disabled अगर 0 */
पूर्ण;

/* ISP data descriptor */
काष्ठा ia_css_isp_data अणु
	u32   address; /** ISP address */
	u32   size;    /** Disabled अगर 0 */
पूर्ण;

/* Shading Correction types. */
क्रमागत ia_css_shading_correction_type अणु
	IA_CSS_SHADING_CORRECTION_NONE,	 /** Shading Correction is not processed in the pipe. */
	IA_CSS_SHADING_CORRECTION_TYPE_1 /** Shading Correction 1.0 (pipe 1.0 on ISP2300, pipe 2.2 on ISP2400/2401) */

	/** More shading correction types can be added in the future. */
पूर्ण;

/* Shading Correction inक्रमmation. */
काष्ठा ia_css_shading_info अणु
	क्रमागत ia_css_shading_correction_type type; /** Shading Correction type. */

	जोड़ अणु	/* Shading Correction inक्रमmation of each Shading Correction types. */

		/* Shading Correction inक्रमmation of IA_CSS_SHADING_CORRECTION_TYPE_1.
		 *
		 *  This काष्ठाure contains the inक्रमmation necessary to generate
		 *  the shading table required in the isp.
		 *  This काष्ठाure is filled in the css,
		 *  and the driver needs to get it to generate the shading table.
		 *
		 *  Beक्रमe the shading correction is applied, NxN-filter and/or scaling
		 *  are applied in the isp, depending on the isp binaries.
		 *  Then, these should be considered in generating the shading table.
		 *    - Bad pixels on left/top sides generated by NxN-filter
		 *      (Bad pixels are NOT considered currently,
		 *      because they are subtle.)
		 *    - Down-scaling/Up-scaling factor
		 *
		 *  Shading correction is applied to the area
		 *  which has real sensor data and margin.
		 *  Then, the shading table should cover the area including margin.
		 *  This काष्ठाure has this inक्रमmation.
		 *    - Origin coordinate of bayer (real sensor data)
		 *      on the shading table
		 *
		 * ------------------------ISP 2401-----------------------
		 *
		 *  the shading table directly required from ISP.
		 *  This काष्ठाure is filled in CSS, and the driver needs to get it to generate the shading table.
		 *
		 *  The shading correction is applied to the bayer area which contains sensor data and padding data.
		 *  The shading table should cover this bayer area.
		 *
		 *  The shading table size directly required from ISP is expressed by these parameters.
		 *    1. uपूर्णांक32_t num_hor_grids;
		 *    2. uपूर्णांक32_t num_ver_grids;
		 *    3. uपूर्णांक32_t bqs_per_grid_cell;
		 *
		 *  In some isp binaries, the bayer scaling is applied beक्रमe the shading correction is applied.
		 *  Then, this scaling factor should be considered in generating the shading table.
		 *  The scaling factor is expressed by these parameters.
		 *    4. uपूर्णांक32_t bayer_scale_hor_ratio_in;
		 *    5. uपूर्णांक32_t bayer_scale_hor_ratio_out;
		 *    6. uपूर्णांक32_t bayer_scale_ver_ratio_in;
		 *    7. uपूर्णांक32_t bayer_scale_ver_ratio_out;
		 *
		 *  The sensor data size inputted to ISP is expressed by this parameter.
		 *  This is the size BEFORE the bayer scaling is applied.
		 *    8. काष्ठा ia_css_resolution isp_input_sensor_data_res_bqs;
		 *
		 *  The origin of the sensor data area positioned on the shading table at the shading correction
		 *  is expressed by this parameter.
		 *  The size of this area assumes the size AFTER the bayer scaling is applied
		 *  to the isp_input_sensor_data_resolution_bqs.
		 *    9. काष्ठा ia_css_coordinate sensor_data_origin_bqs_on_sctbl;
		 *
		 *  ****** Definitions of the shading table and the sensor data at the shading correction ******
		 *
		 * (0,0)--------------------- TW -------------------------------
		 *   |                                            shading table |
		 *   |      (ox,oy)---------- W --------------------------      |
		 *   |        |                               sensor data |     |
		 *   |        |                                           |     |
		 *  TH        H             sensor data center            |     |
		 *   |        |                  (cx,cy)                  |     |
		 *   |        |                                           |     |
		 *   |        |                                           |     |
		 *   |        |                                           |     |
		 *   |         -------------------------------------------      |
		 *   |                                                          |
		 *    ----------------------------------------------------------
		 *
		 *    Example of still mode क्रम output 1080p:
		 *
		 *    num_hor_grids = 66
		 *    num_ver_grids = 37
		 *    bqs_per_grid_cell = 16
		 *    bayer_scale_hor_ratio_in = 1
		 *    bayer_scale_hor_ratio_out = 1
		 *    bayer_scale_ver_ratio_in = 1
		 *    bayer_scale_ver_ratio_out = 1
		 *    isp_input_sensor_data_resolution_bqs = अणु966, 546पूर्ण
		 *    sensor_data_origin_bqs_on_sctbl = अणु61, 15पूर्ण
		 *
		 *    TW, TH [bqs]: width and height of shading table
		 *        TW = (num_hor_grids - 1) * bqs_per_grid_cell = (66 - 1) * 16 = 1040
		 *        TH = (num_ver_grids - 1) * bqs_per_grid_cell = (37 - 1) * 16 = 576
		 *
		 *    W, H [bqs]: width and height of sensor data at shading correction
		 *        W = sensor_data_res_bqs.width
		 *          = isp_input_sensor_data_res_bqs.width
		 *              * bayer_scale_hor_ratio_out / bayer_scale_hor_ratio_in + 0.5 = 966
		 *        H = sensor_data_res_bqs.height
		 *          = isp_input_sensor_data_res_bqs.height
		 *               * bayer_scale_ver_ratio_out / bayer_scale_ver_ratio_in + 0.5 = 546
		 *
		 *    (ox, oy) [bqs]: origin of sensor data positioned on shading table at shading correction
		 *        ox = sensor_data_origin_bqs_on_sctbl.x = 61
		 *        oy = sensor_data_origin_bqs_on_sctbl.y = 15
		 *
		 *    (cx, cy) [bqs]: center of sensor data positioned on shading table at shading correction
		 *        cx = ox + W/2 = 61 + 966/2 = 544
		 *        cy = oy + H/2 = 15 + 546/2 = 288
		 *
		 *  ****** Relation between the shading table and the sensor data ******
		 *
		 *    The origin of the sensor data should be on the shading table.
		 *        0 <= ox < TW,  0 <= oy < TH
		 *
		 *  ****** How to center the shading table on the sensor data ******
		 *
		 *    To center the shading table on the sensor data,
		 *    CSS decides the shading table size so that a certain grid poपूर्णांक is positioned
		 *    on the center of the sensor data at the shading correction.
		 *    CSS expects the shading center is set on this grid poपूर्णांक
		 *    when the shading table data is calculated in AIC.
		 *
		 *    W, H [bqs]: width and height of sensor data at shading correction
		 *	W = sensor_data_res_bqs.width
		 *	H = sensor_data_res_bqs.height
		 *
		 *    (cx, cy) [bqs]: center of sensor data positioned on shading table at shading correction
		 *	cx = sensor_data_origin_bqs_on_sctbl.x + W/2
		 *	cy = sensor_data_origin_bqs_on_sctbl.y + H/2
		 *
		 *    CSS decides the shading table size and the sensor data position
		 *    so that the (cx, cy) satisfies this condition.
		 *	mod(cx, bqs_per_grid_cell) = 0
		 *	mod(cy, bqs_per_grid_cell) = 0
		 *
		 *  ****** How to change the sensor data size by processes in the driver and ISP ******
		 *
		 *    1. sensor data size: Physical sensor size
		 *			   (The काष्ठा ia_css_shading_info करोes not have this inक्रमmation.)
		 *    2. process:          Driver applies the sensor cropping/binning/scaling to physical sensor size.
		 *    3. sensor data size: ISP input size (== shading_info.isp_input_sensor_data_res_bqs)
		 *			   (ISP assumes the ISP input sensor data is centered on the physical sensor.)
		 *    4. process:          ISP applies the bayer scaling by the factor of shading_info.bayer_scale_*.
		 *    5. sensor data size: Scaling factor * ISP input size (== shading_info.sensor_data_res_bqs)
		 *    6. process:          ISP applies the shading correction.
		 *
		 *  ISP block: SC1
		 *  ISP1: SC1 is used.
		 *  ISP2: SC1 is used.
		 */
		काष्ठा अणु
			/* ISP2400 */
			u32 enable;	/** Shading correction enabled.
						     0:disabled, 1:enabled */

			/* ISP2401 */
			u32 num_hor_grids;	/** Number of data poपूर्णांकs per line per color on shading table. */
			u32 num_ver_grids;	/** Number of lines of data poपूर्णांकs per color on shading table. */
			u32 bqs_per_grid_cell; /** Grid cell size in BQ unit.
							 NOTE: bqs = size in BQ(Bayer Quad) unit.
							       1BQ means अणुGr,R,B,Gbपूर्ण (2x2 pixels).
							       Horizontal 1 bqs corresponds to horizontal 2 pixels.
							       Vertical 1 bqs corresponds to vertical 2 pixels. */
			u32 bayer_scale_hor_ratio_in;
			u32 bayer_scale_hor_ratio_out;

			/** Horizontal ratio of bayer scaling between input width and output width,
			     क्रम the scaling which should be करोne beक्रमe shading correction.
				output_width = input_width * bayer_scale_hor_ratio_out
								/ bayer_scale_hor_ratio_in + 0.5 */
			u32 bayer_scale_ver_ratio_in;
			u32 bayer_scale_ver_ratio_out;

			/** Vertical ratio of bayer scaling
			between input height and output height, क्रम the scaling
			which should be करोne beक्रमe shading correction.
			  output_height = input_height * bayer_scale_ver_ratio_out
						/ bayer_scale_ver_ratio_in */
			/* ISP2400 */
			u32 sc_bayer_origin_x_bqs_on_shading_table;
			/** X coordinate (in bqs) of bayer origin on shading table.
			This indicates the left-most pixel of bayer
			(not include margin) inputted to the shading correction.
			This corresponds to the left-most pixel of bayer
			inputted to isp from sensor. */
			/* ISP2400 */
			u32 sc_bayer_origin_y_bqs_on_shading_table;
			/** Y coordinate (in bqs) of bayer origin on shading table.
			This indicates the top pixel of bayer
			(not include margin) inputted to the shading correction.
			This corresponds to the top pixel of bayer
			inputted to isp from sensor. */

			/** Vertical ratio of bayer scaling between input height and output height,
			     क्रम the scaling which should be करोne beक्रमe shading correction.
				output_height = input_height * bayer_scale_ver_ratio_out
								/ bayer_scale_ver_ratio_in + 0.5 */
			/* ISP2401 */
			काष्ठा ia_css_resolution isp_input_sensor_data_res_bqs;
			/** Sensor data size (in bqs) inputted to ISP. This is the size BEFORE bayer scaling.
			     NOTE: This is NOT the size of the physical sensor size.
				   CSS requests the driver that ISP inमाला_दो sensor data
				   by the size of isp_input_sensor_data_res_bqs.
				   The driver sends the sensor data to ISP,
				   after the adequate cropping/binning/scaling
				   are applied to the physical sensor data area.
				   ISP assumes the area of isp_input_sensor_data_res_bqs
				   is centered on the physical sensor. */
			/* ISP2401 */
			काष्ठा ia_css_resolution sensor_data_res_bqs;
			/** Sensor data size (in bqs) at shading correction.
			     This is the size AFTER bayer scaling. */
			/* ISP2401 */
			काष्ठा ia_css_coordinate sensor_data_origin_bqs_on_sctbl;
			/** Origin of sensor data area positioned on shading table at shading correction.
			     The coordinate x,y should be positive values. */
		पूर्ण type_1;

		/** More काष्ठाures can be added here when more shading correction types will be added
		     in the future. */
	पूर्ण info;
पूर्ण;

/* Default Shading Correction inक्रमmation of Shading Correction Type 1. */
#घोषणा DEFAULT_SHADING_INFO_TYPE_1 \
(काष्ठा ia_css_shading_info) अणु \
	.type = IA_CSS_SHADING_CORRECTION_TYPE_1, \
	.info = अणु \
		.type_1 = अणु \
			.bayer_scale_hor_ratio_in	= 1, \
			.bayer_scale_hor_ratio_out	= 1, \
			.bayer_scale_ver_ratio_in	= 1, \
			.bayer_scale_ver_ratio_out	= 1, \
		पूर्ण \
	पूर्ण \
पूर्ण

/* Default Shading Correction inक्रमmation. */
#घोषणा DEFAULT_SHADING_INFO	DEFAULT_SHADING_INFO_TYPE_1

/* काष्ठाure that describes the 3A and DIS grids */
काष्ठा ia_css_grid_info अणु
	/* \नame ISP input size
	  * that is visible क्रम user
	  * @अणु
	  */
	u32 isp_in_width;
	u32 isp_in_height;
	/* @पूर्ण*/

	काष्ठा ia_css_3a_grid_info  s3a_grid; /** 3A grid info */
	जोड़ ia_css_dvs_grid_u dvs_grid;
	/** All types of DVS statistics grid info जोड़ */

	क्रमागत ia_css_vamem_type vamem_type;
पूर्ण;

/* शेषs क्रम ia_css_grid_info काष्ठाs */
#घोषणा DEFAULT_GRID_INFO अणु \
	.dvs_grid	= DEFAULT_DVS_GRID_INFO, \
	.vamem_type	= IA_CSS_VAMEM_TYPE_1 \
पूर्ण

/* Morphing table, used क्रम geometric distortion and chromatic abberration
 *  correction (GDCAC, also called GDC).
 *  This table describes the imperfections पूर्णांकroduced by the lens, the
 *  advanced ISP can correct क्रम these imperfections using this table.
 */
काष्ठा ia_css_morph_table अणु
	u32 enable; /** To disable GDC, set this field to false. The
			  coordinates fields can be set to शून्य in this हाल. */
	u32 height; /** Table height */
	u32 width;  /** Table width */
	u16 *coordinates_x[IA_CSS_MORPH_TABLE_NUM_PLANES];
	/** X coordinates that describe the sensor imperfection */
	u16 *coordinates_y[IA_CSS_MORPH_TABLE_NUM_PLANES];
	/** Y coordinates that describe the sensor imperfection */
पूर्ण;

काष्ठा ia_css_dvs_6axis_config अणु
	अचिन्हित पूर्णांक exp_id;
	/** Exposure ID, see ia_css_event_खुला.h क्रम more detail */
	u32 width_y;
	u32 height_y;
	u32 width_uv;
	u32 height_uv;
	u32 *xcoords_y;
	u32 *ycoords_y;
	u32 *xcoords_uv;
	u32 *ycoords_uv;
पूर्ण;

/**
 * This specअगरies the coordinates (x,y)
 */
काष्ठा ia_css_poपूर्णांक अणु
	s32 x; /** x coordinate */
	s32 y; /** y coordinate */
पूर्ण;

/**
 * This specअगरies the region
 */
काष्ठा ia_css_region अणु
	काष्ठा ia_css_poपूर्णांक origin; /** Starting poपूर्णांक coordinates क्रम the region */
	काष्ठा ia_css_resolution resolution; /** Region resolution */
पूर्ण;

/**
 * Digital zoom:
 * This feature is currently available only क्रम video, but will become
 * available क्रम preview and capture as well.
 * Set the digital zoom factor, this is a logarithmic scale. The actual zoom
 * factor will be 64/x.
 * Setting dx or dy to 0 disables digital zoom क्रम that direction.
 * New API change क्रम Digital zoom:(added काष्ठा ia_css_region zoom_region)
 * zoom_region specअगरies the origin of the zoom region and width and
 * height of that region.
 * origin : This is the coordinate (x,y) within the effective input resolution
 * of the stream. where, x >= 0 and y >= 0. (0,0) maps to the upper left of the
 * effective input resolution.
 * resolution : This is resolution of zoom region.
 * where, x + width <= effective input width
 * y + height <= effective input height
 */
काष्ठा ia_css_dz_config अणु
	u32 dx; /** Horizontal zoom factor */
	u32 dy; /** Vertical zoom factor */
	काष्ठा ia_css_region zoom_region; /** region क्रम zoom */
पूर्ण;

/* The still capture mode, this can be RAW (simply copy sensor input to DDR),
 *  Primary ISP, the Advanced ISP (GDC) or the low-light ISP (ANR).
 */
क्रमागत ia_css_capture_mode अणु
	IA_CSS_CAPTURE_MODE_RAW,      /** no processing, copy data only */
	IA_CSS_CAPTURE_MODE_BAYER,    /** bayer processing, up to demosaic */
	IA_CSS_CAPTURE_MODE_PRIMARY,  /** primary ISP */
	IA_CSS_CAPTURE_MODE_ADVANCED, /** advanced ISP (GDC) */
	IA_CSS_CAPTURE_MODE_LOW_LIGHT /** low light ISP (ANR) */
पूर्ण;

काष्ठा ia_css_capture_config अणु
	क्रमागत ia_css_capture_mode mode; /** Still capture mode */
	u32 enable_xnr;	       /** Enable/disable XNR */
	u32 enable_raw_output;
	bool enable_capture_pp_bli;    /** Enable capture_pp_bli mode */
पूर्ण;

/* शेष settings क्रम ia_css_capture_config काष्ठाs */
#घोषणा DEFAULT_CAPTURE_CONFIG अणु \
	.mode	= IA_CSS_CAPTURE_MODE_PRIMARY, \
पूर्ण

/* ISP filter configuration. This is a collection of configurations
 *  क्रम each of the ISP filters (modules).
 *
 *  NOTE! The contents of all poपूर्णांकers is copied when get or set with the
 *  exception of the shading and morph tables. For these we only copy the
 *  poपूर्णांकer, so the caller must make sure the memory contents of these poपूर्णांकers
 *  reमुख्य valid as दीर्घ as they are used by the CSS. This will be fixed in the
 *  future by copying the contents instead of just the poपूर्णांकer.
 *
 *  Comment:
 *    ["ISP block", 1&2]   : ISP block is used both क्रम ISP1 and ISP2.
 *    ["ISP block", 1only] : ISP block is used only क्रम ISP1.
 *    ["ISP block", 2only] : ISP block is used only क्रम ISP2.
 */
काष्ठा ia_css_isp_config अणु
	काष्ठा ia_css_wb_config   *wb_config;	/** White Balance
							[WB1, 1&2] */
	काष्ठा ia_css_cc_config   *cc_config;	/** Color Correction
							[CSC1, 1only] */
	काष्ठा ia_css_tnr_config  *tnr_config;	/** Temporal Noise Reduction
							[TNR1, 1&2] */
	काष्ठा ia_css_ecd_config  *ecd_config;	/** Eigen Color Demosaicing
							[DE2, 2only] */
	काष्ठा ia_css_ynr_config  *ynr_config;	/** Y(Luma) Noise Reduction
							[YNR2&YEE2, 2only] */
	काष्ठा ia_css_fc_config   *fc_config;	/** Fringe Control
							[FC2, 2only] */
	काष्ठा ia_css_क्रमmats_config
		*क्रमmats_config;	/** Formats Control क्रम मुख्य output
							[FORMATS, 1&2] */
	काष्ठा ia_css_cnr_config  *cnr_config;	/** Chroma Noise Reduction
							[CNR2, 2only] */
	काष्ठा ia_css_macc_config *macc_config;	/** MACC
							[MACC2, 2only] */
	काष्ठा ia_css_ctc_config  *ctc_config;	/** Chroma Tone Control
							[CTC2, 2only] */
	काष्ठा ia_css_aa_config   *aa_config;	/** YUV Anti-Aliasing
							[AA2, 2only]
							(not used currently) */
	काष्ठा ia_css_aa_config   *baa_config;	/** Bayer Anti-Aliasing
							[BAA2, 1&2] */
	काष्ठा ia_css_ce_config   *ce_config;	/** Chroma Enhancement
							[CE1, 1only] */
	काष्ठा ia_css_dvs_6axis_config *dvs_6axis_config;
	काष्ठा ia_css_ob_config   *ob_config;  /** Objective Black
							[OB1, 1&2] */
	काष्ठा ia_css_dp_config   *dp_config;  /** Defect Pixel Correction
							[DPC1/DPC2, 1&2] */
	काष्ठा ia_css_nr_config   *nr_config;  /** Noise Reduction
							[BNR1&YNR1&CNR1, 1&2]*/
	काष्ठा ia_css_ee_config   *ee_config;  /** Edge Enhancement
							[YEE1, 1&2] */
	काष्ठा ia_css_de_config   *de_config;  /** Demosaic
							[DE1, 1only] */
	काष्ठा ia_css_gc_config   *gc_config;  /** Gamma Correction (क्रम YUV)
							[GC1, 1only] */
	काष्ठा ia_css_anr_config  *anr_config; /** Advanced Noise Reduction */
	काष्ठा ia_css_3a_config   *s3a_config; /** 3A Statistics config */
	काष्ठा ia_css_xnr_config  *xnr_config; /** eXtra Noise Reduction */
	काष्ठा ia_css_dz_config   *dz_config;  /** Digital Zoom */
	काष्ठा ia_css_cc_config *yuv2rgb_cc_config; /** Color Correction
							[CCM2, 2only] */
	काष्ठा ia_css_cc_config *rgb2yuv_cc_config; /** Color Correction
							[CSC2, 2only] */
	काष्ठा ia_css_macc_table  *macc_table;	/** MACC
							[MACC1/MACC2, 1&2]*/
	काष्ठा ia_css_gamma_table *gamma_table;	/** Gamma Correction (क्रम YUV)
							[GC1, 1only] */
	काष्ठा ia_css_ctc_table   *ctc_table;	/** Chroma Tone Control
							[CTC1, 1only] */

	/* \deprecated */
	काष्ठा ia_css_xnr_table   *xnr_table;	/** eXtra Noise Reduction
							[XNR1, 1&2] */
	काष्ठा ia_css_rgb_gamma_table *r_gamma_table;/** sRGB Gamma Correction
							[GC2, 2only] */
	काष्ठा ia_css_rgb_gamma_table *g_gamma_table;/** sRGB Gamma Correction
							[GC2, 2only] */
	काष्ठा ia_css_rgb_gamma_table *b_gamma_table;/** sRGB Gamma Correction
							[GC2, 2only] */
	काष्ठा ia_css_vector      *motion_vector; /** For 2-axis DVS */
	काष्ठा ia_css_shading_table *shading_table;
	काष्ठा ia_css_morph_table   *morph_table;
	काष्ठा ia_css_dvs_coefficients *dvs_coefs; /** DVS 1.0 coefficients */
	काष्ठा ia_css_dvs2_coefficients *dvs2_coefs; /** DVS 2.0 coefficients */
	काष्ठा ia_css_capture_config   *capture_config;
	काष्ठा ia_css_anr_thres   *anr_thres;
	/* @deprecatedअणुOld shading settings, see bugzilla bz675 क्रम detailsपूर्ण */
	काष्ठा ia_css_shading_settings *shading_settings;
	काष्ठा ia_css_xnr3_config *xnr3_config; /** eXtreme Noise Reduction v3 */
	/* comment from Lasse: Be aware how this feature will affect coordinate
	 *  normalization in dअगरferent parts of the प्रणाली. (e.g. face detection,
	 *  touch focus, 3A statistics and winकरोws of पूर्णांकerest, shading correction,
	 *  DVS, GDC) from IQ tool level and application level करोwn-to ISP FW level.
	 *  the risk क्रम regression is not in the inभागidual blocks, but how they
	 *  पूर्णांकegrate together. */
	काष्ठा ia_css_output_config
		*output_config;	/** Main Output Mirroring, flipping */

	काष्ठा ia_css_scaler_config
		*scaler_config;         /** Skylake: scaler config (optional) */
	काष्ठा ia_css_क्रमmats_config
		*क्रमmats_config_display;/** Formats control क्रम viewfinder/display output (optional)
										[OSYS, n/a] */
	काष्ठा ia_css_output_config
		*output_config_display; /** Viewfinder/display output mirroring, flipping (optional) */

	काष्ठा ia_css_frame
		*output_frame;          /** Output frame the config is to be applied to (optional) */
	u32			isp_config_id;	/** Unique ID to track which config was actually applied to a particular frame */
पूर्ण;

#पूर्ण_अगर /* _IA_CSS_TYPES_H */
