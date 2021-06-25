<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित DC_HW_TYPES_H
#घोषणा DC_HW_TYPES_H

#समावेश "os_types.h"
#समावेश "fixed31_32.h"
#समावेश "signal_types.h"

/******************************************************************************
 * Data types क्रम Virtual HW Layer of DAL3.
 * (see DAL3 design करोcuments क्रम HW Layer definition)
 *
 * The पूर्णांकended uses are:
 * 1. Generation pseuकरोcode sequences क्रम HW programming.
 * 2. Implementation of real HW programming by HW Sequencer of DAL3.
 *
 * Note: करो *not* add any types which are *not* used क्रम HW programming - this
 * will ensure separation of Logic layer from HW layer.
 ******************************************************************************/

जोड़ large_पूर्णांकeger अणु
	काष्ठा अणु
		uपूर्णांक32_t low_part;
		पूर्णांक32_t high_part;
	पूर्ण;

	काष्ठा अणु
		uपूर्णांक32_t low_part;
		पूर्णांक32_t high_part;
	पूर्ण u;

	पूर्णांक64_t quad_part;
पूर्ण;

#घोषणा PHYSICAL_ADDRESS_LOC जोड़ large_पूर्णांकeger

क्रमागत dc_plane_addr_type अणु
	PLN_ADDR_TYPE_GRAPHICS = 0,
	PLN_ADDR_TYPE_GRPH_STEREO,
	PLN_ADDR_TYPE_VIDEO_PROGRESSIVE,
	PLN_ADDR_TYPE_RGBEA
पूर्ण;

काष्ठा dc_plane_address अणु
	क्रमागत dc_plane_addr_type type;
	bool पंचांगz_surface;
	जोड़ अणु
		काष्ठाअणु
			PHYSICAL_ADDRESS_LOC addr;
			PHYSICAL_ADDRESS_LOC cursor_cache_addr;
			PHYSICAL_ADDRESS_LOC meta_addr;
			जोड़ large_पूर्णांकeger dcc_स्थिर_color;
		पूर्ण grph;

		/*stereo*/
		काष्ठा अणु
			PHYSICAL_ADDRESS_LOC left_addr;
			PHYSICAL_ADDRESS_LOC left_meta_addr;
			जोड़ large_पूर्णांकeger left_dcc_स्थिर_color;

			PHYSICAL_ADDRESS_LOC right_addr;
			PHYSICAL_ADDRESS_LOC right_meta_addr;
			जोड़ large_पूर्णांकeger right_dcc_स्थिर_color;

			PHYSICAL_ADDRESS_LOC left_alpha_addr;
			PHYSICAL_ADDRESS_LOC left_alpha_meta_addr;
			जोड़ large_पूर्णांकeger left_alpha_dcc_स्थिर_color;

			PHYSICAL_ADDRESS_LOC right_alpha_addr;
			PHYSICAL_ADDRESS_LOC right_alpha_meta_addr;
			जोड़ large_पूर्णांकeger right_alpha_dcc_स्थिर_color;

		पूर्ण grph_stereo;

		/*video  progressive*/
		काष्ठा अणु
			PHYSICAL_ADDRESS_LOC luma_addr;
			PHYSICAL_ADDRESS_LOC luma_meta_addr;
			जोड़ large_पूर्णांकeger luma_dcc_स्थिर_color;

			PHYSICAL_ADDRESS_LOC chroma_addr;
			PHYSICAL_ADDRESS_LOC chroma_meta_addr;
			जोड़ large_पूर्णांकeger chroma_dcc_स्थिर_color;
		पूर्ण video_progressive;

		काष्ठा अणु
			PHYSICAL_ADDRESS_LOC addr;
			PHYSICAL_ADDRESS_LOC meta_addr;
			जोड़ large_पूर्णांकeger dcc_स्थिर_color;

			PHYSICAL_ADDRESS_LOC alpha_addr;
			PHYSICAL_ADDRESS_LOC alpha_meta_addr;
			जोड़ large_पूर्णांकeger alpha_dcc_स्थिर_color;
		पूर्ण rgbea;
	पूर्ण;

	जोड़ large_पूर्णांकeger page_table_base;

	uपूर्णांक8_t vmid;
पूर्ण;

काष्ठा dc_size अणु
	पूर्णांक width;
	पूर्णांक height;
पूर्ण;

काष्ठा rect अणु
	पूर्णांक x;
	पूर्णांक y;
	पूर्णांक width;
	पूर्णांक height;
पूर्ण;

काष्ठा plane_size अणु
	/* Graphic surface pitch in pixels.
	 * In LINEAR_GENERAL mode, pitch
	 * is 32 pixel aligned.
	 */
	पूर्णांक surface_pitch;
	पूर्णांक chroma_pitch;
	काष्ठा rect surface_size;
	काष्ठा rect chroma_size;
पूर्ण;

काष्ठा dc_plane_dcc_param अणु
	bool enable;

	पूर्णांक meta_pitch;
	bool independent_64b_blks;
	uपूर्णांक8_t dcc_ind_blk;

	पूर्णांक meta_pitch_c;
	bool independent_64b_blks_c;
	uपूर्णांक8_t dcc_ind_blk_c;
पूर्ण;

/*Displayable pixel क्रमmat in fb*/
क्रमागत surface_pixel_क्रमmat अणु
	SURFACE_PIXEL_FORMAT_GRPH_BEGIN = 0,
	/*TOBE REMOVED paletta 256 colors*/
	SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS =
		SURFACE_PIXEL_FORMAT_GRPH_BEGIN,
	/*16 bpp*/
	SURFACE_PIXEL_FORMAT_GRPH_ARGB1555,
	/*16 bpp*/
	SURFACE_PIXEL_FORMAT_GRPH_RGB565,
	/*32 bpp*/
	SURFACE_PIXEL_FORMAT_GRPH_ARGB8888,
	/*32 bpp swaped*/
	SURFACE_PIXEL_FORMAT_GRPH_ABGR8888,

	SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010,
	/*swaped*/
	SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010,
	/*TOBE REMOVED swaped, XR_BIAS has no dअगरferance
	 * क्रम pixel layout than previous and we can
	 * delete this after discusion*/
	SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS,
	/*64 bpp */
	SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616,
	/*भग्न*/
	SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F,
	/*swaped & भग्न*/
	SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F,
	/*grow graphics here अगर necessary */
	SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FIX,
	SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FIX,
	SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FLOAT,
	SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FLOAT,
	SURFACE_PIXEL_FORMAT_GRPH_RGBE,
	SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA,
	SURFACE_PIXEL_FORMAT_VIDEO_BEGIN,
	SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr =
		SURFACE_PIXEL_FORMAT_VIDEO_BEGIN,
	SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb,
	SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr,
	SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb,
		SURFACE_PIXEL_FORMAT_SUBSAMPLE_END,
	SURFACE_PIXEL_FORMAT_VIDEO_ACrYCb2101010,
	SURFACE_PIXEL_FORMAT_VIDEO_CrYCbA1010102,
	SURFACE_PIXEL_FORMAT_VIDEO_AYCrCb8888,
	SURFACE_PIXEL_FORMAT_INVALID

	/*grow 444 video here अगर necessary */
पूर्ण;



/* Pixel क्रमmat */
क्रमागत pixel_क्रमmat अणु
	/*graph*/
	PIXEL_FORMAT_UNINITIALIZED,
	PIXEL_FORMAT_INDEX8,
	PIXEL_FORMAT_RGB565,
	PIXEL_FORMAT_ARGB8888,
	PIXEL_FORMAT_ARGB2101010,
	PIXEL_FORMAT_ARGB2101010_XRBIAS,
	PIXEL_FORMAT_FP16,
	/*video*/
	PIXEL_FORMAT_420BPP8,
	PIXEL_FORMAT_420BPP10,
	/*end of pixel क्रमmat definition*/
	PIXEL_FORMAT_INVALID,

	PIXEL_FORMAT_GRPH_BEGIN = PIXEL_FORMAT_INDEX8,
	PIXEL_FORMAT_GRPH_END = PIXEL_FORMAT_FP16,
	PIXEL_FORMAT_VIDEO_BEGIN = PIXEL_FORMAT_420BPP8,
	PIXEL_FORMAT_VIDEO_END = PIXEL_FORMAT_420BPP10,
	PIXEL_FORMAT_UNKNOWN
पूर्ण;

क्रमागत tile_split_values अणु
	DC_DISPLAY_MICRO_TILING = 0x0,
	DC_THIN_MICRO_TILING = 0x1,
	DC_DEPTH_MICRO_TILING = 0x2,
	DC_ROTATED_MICRO_TILING = 0x3,
पूर्ण;

क्रमागत tripleBuffer_enable अणु
	DC_TRIPLEBUFFER_DISABLE = 0x0,
	DC_TRIPLEBUFFER_ENABLE = 0x1,
पूर्ण;

/* TODO: These values come from hardware spec. We need to पढ़ोdress this
 * अगर they ever change.
 */
क्रमागत array_mode_values अणु
	DC_ARRAY_LINEAR_GENERAL = 0,
	DC_ARRAY_LINEAR_ALLIGNED,
	DC_ARRAY_1D_TILED_THIN1,
	DC_ARRAY_1D_TILED_THICK,
	DC_ARRAY_2D_TILED_THIN1,
	DC_ARRAY_PRT_TILED_THIN1,
	DC_ARRAY_PRT_2D_TILED_THIN1,
	DC_ARRAY_2D_TILED_THICK,
	DC_ARRAY_2D_TILED_X_THICK,
	DC_ARRAY_PRT_TILED_THICK,
	DC_ARRAY_PRT_2D_TILED_THICK,
	DC_ARRAY_PRT_3D_TILED_THIN1,
	DC_ARRAY_3D_TILED_THIN1,
	DC_ARRAY_3D_TILED_THICK,
	DC_ARRAY_3D_TILED_X_THICK,
	DC_ARRAY_PRT_3D_TILED_THICK,
पूर्ण;

क्रमागत tile_mode_values अणु
	DC_ADDR_SURF_MICRO_TILING_DISPLAY = 0x0,
	DC_ADDR_SURF_MICRO_TILING_NON_DISPLAY = 0x1,
पूर्ण;

क्रमागत swizzle_mode_values अणु
	DC_SW_LINEAR = 0,
	DC_SW_256B_S = 1,
	DC_SW_256_D = 2,
	DC_SW_256_R = 3,
	DC_SW_4KB_S = 5,
	DC_SW_4KB_D = 6,
	DC_SW_4KB_R = 7,
	DC_SW_64KB_S = 9,
	DC_SW_64KB_D = 10,
	DC_SW_64KB_R = 11,
	DC_SW_VAR_S = 13,
	DC_SW_VAR_D = 14,
	DC_SW_VAR_R = 15,
	DC_SW_64KB_S_T = 17,
	DC_SW_64KB_D_T = 18,
	DC_SW_4KB_S_X = 21,
	DC_SW_4KB_D_X = 22,
	DC_SW_4KB_R_X = 23,
	DC_SW_64KB_S_X = 25,
	DC_SW_64KB_D_X = 26,
	DC_SW_64KB_R_X = 27,
	DC_SW_VAR_S_X = 29,
	DC_SW_VAR_D_X = 30,
	DC_SW_VAR_R_X = 31,
	DC_SW_MAX = 32,
	DC_SW_UNKNOWN = DC_SW_MAX
पूर्ण;

जोड़ dc_tiling_info अणु

	काष्ठा अणु
		/* Specअगरies the number of memory banks क्रम tiling
		 *	purposes.
		 * Only applies to 2D and 3D tiling modes.
		 *	POSSIBLE VALUES: 2,4,8,16
		 */
		अचिन्हित पूर्णांक num_banks;
		/* Specअगरies the number of tiles in the x direction
		 *	to be incorporated पूर्णांकo the same bank.
		 * Only applies to 2D and 3D tiling modes.
		 *	POSSIBLE VALUES: 1,2,4,8
		 */
		अचिन्हित पूर्णांक bank_width;
		अचिन्हित पूर्णांक bank_width_c;
		/* Specअगरies the number of tiles in the y direction to
		 *	be incorporated पूर्णांकo the same bank.
		 * Only applies to 2D and 3D tiling modes.
		 *	POSSIBLE VALUES: 1,2,4,8
		 */
		अचिन्हित पूर्णांक bank_height;
		अचिन्हित पूर्णांक bank_height_c;
		/* Specअगरies the macro tile aspect ratio. Only applies
		 * to 2D and 3D tiling modes.
		 */
		अचिन्हित पूर्णांक tile_aspect;
		अचिन्हित पूर्णांक tile_aspect_c;
		/* Specअगरies the number of bytes that will be stored
		 *	contiguously क्रम each tile.
		 * If the tile data requires more storage than this
		 *	amount, it is split पूर्णांकo multiple slices.
		 * This field must not be larger than
		 *	GB_ADDR_CONFIG.DRAM_ROW_SIZE.
		 * Only applies to 2D and 3D tiling modes.
		 * For color render tarमाला_लो, TILE_SPLIT >= 256B.
		 */
		क्रमागत tile_split_values tile_split;
		क्रमागत tile_split_values tile_split_c;
		/* Specअगरies the addressing within a tile.
		 *	0x0 - DISPLAY_MICRO_TILING
		 *	0x1 - THIN_MICRO_TILING
		 *	0x2 - DEPTH_MICRO_TILING
		 *	0x3 - ROTATED_MICRO_TILING
		 */
		क्रमागत tile_mode_values tile_mode;
		क्रमागत tile_mode_values tile_mode_c;
		/* Specअगरies the number of pipes and how they are
		 *	पूर्णांकerleaved in the surface.
		 * Refer to memory addressing करोcument क्रम complete
		 *	details and स्थिरraपूर्णांकs.
		 */
		अचिन्हित पूर्णांक pipe_config;
		/* Specअगरies the tiling mode of the surface.
		 * THIN tiles use an 8x8x1 tile size.
		 * THICK tiles use an 8x8x4 tile size.
		 * 2D tiling modes rotate banks क्रम successive Z slices
		 * 3D tiling modes rotate pipes and banks क्रम Z slices
		 * Refer to memory addressing करोcument क्रम complete
		 *	details and स्थिरraपूर्णांकs.
		 */
		क्रमागत array_mode_values array_mode;
	पूर्ण gfx8;

	काष्ठा अणु
		क्रमागत swizzle_mode_values swizzle;
		अचिन्हित पूर्णांक num_pipes;
		अचिन्हित पूर्णांक max_compressed_frags;
		अचिन्हित पूर्णांक pipe_पूर्णांकerleave;

		अचिन्हित पूर्णांक num_banks;
		अचिन्हित पूर्णांक num_shader_engines;
		अचिन्हित पूर्णांक num_rb_per_se;
		bool shaderEnable;

		bool meta_linear;
		bool rb_aligned;
		bool pipe_aligned;
		अचिन्हित पूर्णांक num_pkrs;
	पूर्ण gfx9;
पूर्ण;

/* Rotation angle */
क्रमागत dc_rotation_angle अणु
	ROTATION_ANGLE_0 = 0,
	ROTATION_ANGLE_90,
	ROTATION_ANGLE_180,
	ROTATION_ANGLE_270,
	ROTATION_ANGLE_COUNT
पूर्ण;

क्रमागत dc_scan_direction अणु
	SCAN_सूचीECTION_UNKNOWN = 0,
	SCAN_सूचीECTION_HORIZONTAL = 1,  /* 0, 180 rotation */
	SCAN_सूचीECTION_VERTICAL = 2,    /* 90, 270 rotation */
पूर्ण;

काष्ठा dc_cursor_position अणु
	uपूर्णांक32_t x;
	uपूर्णांक32_t y;

	uपूर्णांक32_t x_hotspot;
	uपूर्णांक32_t y_hotspot;

	/*
	 * This parameter indicates whether HW cursor should be enabled
	 */
	bool enable;

	/* Translate cursor x/y by the source rectangle क्रम each plane. */
	bool translate_by_source;
पूर्ण;

काष्ठा dc_cursor_mi_param अणु
	अचिन्हित पूर्णांक pixel_clk_khz;
	अचिन्हित पूर्णांक ref_clk_khz;
	काष्ठा rect viewport;
	काष्ठा fixed31_32 h_scale_ratio;
	काष्ठा fixed31_32 v_scale_ratio;
	क्रमागत dc_rotation_angle rotation;
	bool mirror;
पूर्ण;

/* IPP related types */

क्रमागत अणु
	GAMMA_RGB_256_ENTRIES = 256,
	GAMMA_RGB_FLOAT_1024_ENTRIES = 1024,
	GAMMA_CS_TFM_1D_ENTRIES = 4096,
	GAMMA_CUSTOM_ENTRIES = 4096,
	GAMMA_MAX_ENTRIES = 4096
पूर्ण;

क्रमागत dc_gamma_type अणु
	GAMMA_RGB_256 = 1,
	GAMMA_RGB_FLOAT_1024 = 2,
	GAMMA_CS_TFM_1D = 3,
	GAMMA_CUSTOM = 4,
पूर्ण;

काष्ठा dc_csc_transक्रमm अणु
	uपूर्णांक16_t matrix[12];
	bool enable_adjusपंचांगent;
पूर्ण;

काष्ठा dc_rgb_fixed अणु
	काष्ठा fixed31_32 red;
	काष्ठा fixed31_32 green;
	काष्ठा fixed31_32 blue;
पूर्ण;

काष्ठा dc_gamma अणु
	काष्ठा kref refcount;
	क्रमागत dc_gamma_type type;
	अचिन्हित पूर्णांक num_entries;

	काष्ठा dc_gamma_entries अणु
		काष्ठा fixed31_32 red[GAMMA_MAX_ENTRIES];
		काष्ठा fixed31_32 green[GAMMA_MAX_ENTRIES];
		काष्ठा fixed31_32 blue[GAMMA_MAX_ENTRIES];
	पूर्ण entries;

	/* निजी to DC core */
	काष्ठा dc_context *ctx;

	/* is_identity is used क्रम RGB256 gamma identity which can also be programmed in INPUT_LUT.
	 * is_logical_identity indicates the given gamma ramp regardless of type is identity.
	 */
	bool is_identity;
पूर्ण;

/* Used by both ipp amd opp functions*/
/* TODO: to be consolidated with क्रमागत color_space */

/*
 * This क्रमागत is क्रम programming CURSOR_MODE रेजिस्टर field. What this रेजिस्टर
 * should be programmed to depends on OS requested cursor shape flags and what
 * we stored in the cursor surface.
 */
क्रमागत dc_cursor_color_क्रमmat अणु
	CURSOR_MODE_MONO,
	CURSOR_MODE_COLOR_1BIT_AND,
	CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA,
	CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA,
	CURSOR_MODE_COLOR_64BIT_FP_PRE_MULTIPLIED,
	CURSOR_MODE_COLOR_64BIT_FP_UN_PRE_MULTIPLIED
पूर्ण;

/*
 * This is all the parameters required by DAL in order to update the cursor
 * attributes, including the new cursor image surface address, size, hotspot
 * location, color क्रमmat, etc.
 */

जोड़ dc_cursor_attribute_flags अणु
	काष्ठा अणु
		uपूर्णांक32_t ENABLE_MAGNIFICATION:1;
		uपूर्णांक32_t INVERSE_TRANSPARENT_CLAMPING:1;
		uपूर्णांक32_t HORIZONTAL_MIRROR:1;
		uपूर्णांक32_t VERTICAL_MIRROR:1;
		uपूर्णांक32_t INVERT_PIXEL_DATA:1;
		uपूर्णांक32_t ZERO_EXPANSION:1;
		uपूर्णांक32_t MIN_MAX_INVERT:1;
		uपूर्णांक32_t ENABLE_CURSOR_DEGAMMA:1;
		uपूर्णांक32_t RESERVED:24;
	पूर्ण bits;
	uपूर्णांक32_t value;
पूर्ण;

काष्ठा dc_cursor_attributes अणु
	PHYSICAL_ADDRESS_LOC address;
	uपूर्णांक32_t pitch;

	/* Width and height should correspond to cursor surface width x heigh */
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;

	क्रमागत dc_cursor_color_क्रमmat color_क्रमmat;
	uपूर्णांक32_t sdr_white_level; // क्रम boosting (SDR) cursor in HDR mode

	/* In हाल we support HW Cursor rotation in the future */
	क्रमागत dc_rotation_angle rotation_angle;

	जोड़ dc_cursor_attribute_flags attribute_flags;
पूर्ण;

काष्ठा dpp_cursor_attributes अणु
	पूर्णांक bias;
	पूर्णांक scale;
पूर्ण;

/* OPP */

क्रमागत dc_color_space अणु
	COLOR_SPACE_UNKNOWN,
	COLOR_SPACE_SRGB,
	COLOR_SPACE_XR_RGB,
	COLOR_SPACE_SRGB_LIMITED,
	COLOR_SPACE_MSREF_SCRGB,
	COLOR_SPACE_YCBCR601,
	COLOR_SPACE_YCBCR709,
	COLOR_SPACE_XV_YCC_709,
	COLOR_SPACE_XV_YCC_601,
	COLOR_SPACE_YCBCR601_LIMITED,
	COLOR_SPACE_YCBCR709_LIMITED,
	COLOR_SPACE_2020_RGB_FULLRANGE,
	COLOR_SPACE_2020_RGB_LIMITEDRANGE,
	COLOR_SPACE_2020_YCBCR,
	COLOR_SPACE_ADOBERGB,
	COLOR_SPACE_DCIP3,
	COLOR_SPACE_DISPLAYNATIVE,
	COLOR_SPACE_DOLBYVISION,
	COLOR_SPACE_APPCTRL,
	COLOR_SPACE_CUSTOMPOINTS,
	COLOR_SPACE_YCBCR709_BLACK,
पूर्ण;

क्रमागत dc_dither_option अणु
	DITHER_OPTION_DEFAULT,
	DITHER_OPTION_DISABLE,
	DITHER_OPTION_FM6,
	DITHER_OPTION_FM8,
	DITHER_OPTION_FM10,
	DITHER_OPTION_SPATIAL6_FRAME_RANDOM,
	DITHER_OPTION_SPATIAL8_FRAME_RANDOM,
	DITHER_OPTION_SPATIAL10_FRAME_RANDOM,
	DITHER_OPTION_SPATIAL6,
	DITHER_OPTION_SPATIAL8,
	DITHER_OPTION_SPATIAL10,
	DITHER_OPTION_TRUN6,
	DITHER_OPTION_TRUN8,
	DITHER_OPTION_TRUN10,
	DITHER_OPTION_TRUN10_SPATIAL8,
	DITHER_OPTION_TRUN10_SPATIAL6,
	DITHER_OPTION_TRUN10_FM8,
	DITHER_OPTION_TRUN10_FM6,
	DITHER_OPTION_TRUN10_SPATIAL8_FM6,
	DITHER_OPTION_SPATIAL10_FM8,
	DITHER_OPTION_SPATIAL10_FM6,
	DITHER_OPTION_TRUN8_SPATIAL6,
	DITHER_OPTION_TRUN8_FM6,
	DITHER_OPTION_SPATIAL8_FM6,
	DITHER_OPTION_MAX = DITHER_OPTION_SPATIAL8_FM6,
	DITHER_OPTION_INVALID
पूर्ण;

क्रमागत dc_quantization_range अणु
	QUANTIZATION_RANGE_UNKNOWN,
	QUANTIZATION_RANGE_FULL,
	QUANTIZATION_RANGE_LIMITED
पूर्ण;

क्रमागत dc_dynamic_expansion अणु
	DYN_EXPANSION_AUTO,
	DYN_EXPANSION_DISABLE
पूर्ण;

/* XFM */

/* used in  काष्ठा dc_plane_state */
काष्ठा scaling_taps अणु
	uपूर्णांक32_t v_taps;
	uपूर्णांक32_t h_taps;
	uपूर्णांक32_t v_taps_c;
	uपूर्णांक32_t h_taps_c;
	bool पूर्णांकeger_scaling;
पूर्ण;

क्रमागत dc_timing_standard अणु
	DC_TIMING_STANDARD_UNDEFINED,
	DC_TIMING_STANDARD_DMT,
	DC_TIMING_STANDARD_GTF,
	DC_TIMING_STANDARD_CVT,
	DC_TIMING_STANDARD_CVT_RB,
	DC_TIMING_STANDARD_CEA770,
	DC_TIMING_STANDARD_CEA861,
	DC_TIMING_STANDARD_HDMI,
	DC_TIMING_STANDARD_TV_NTSC,
	DC_TIMING_STANDARD_TV_NTSC_J,
	DC_TIMING_STANDARD_TV_PAL,
	DC_TIMING_STANDARD_TV_PAL_M,
	DC_TIMING_STANDARD_TV_PAL_CN,
	DC_TIMING_STANDARD_TV_SECAM,
	DC_TIMING_STANDARD_EXPLICIT,
	/*!< For explicit timings from EDID, VBIOS, etc.*/
	DC_TIMING_STANDARD_USER_OVERRIDE,
	/*!< For mode timing override by user*/
	DC_TIMING_STANDARD_MAX
पूर्ण;

क्रमागत dc_color_depth अणु
	COLOR_DEPTH_UNDEFINED,
	COLOR_DEPTH_666,
	COLOR_DEPTH_888,
	COLOR_DEPTH_101010,
	COLOR_DEPTH_121212,
	COLOR_DEPTH_141414,
	COLOR_DEPTH_161616,
	COLOR_DEPTH_999,
	COLOR_DEPTH_111111,
	COLOR_DEPTH_COUNT
पूर्ण;

क्रमागत dc_pixel_encoding अणु
	PIXEL_ENCODING_UNDEFINED,
	PIXEL_ENCODING_RGB,
	PIXEL_ENCODING_YCBCR422,
	PIXEL_ENCODING_YCBCR444,
	PIXEL_ENCODING_YCBCR420,
	PIXEL_ENCODING_COUNT
पूर्ण;

क्रमागत dc_aspect_ratio अणु
	ASPECT_RATIO_NO_DATA,
	ASPECT_RATIO_4_3,
	ASPECT_RATIO_16_9,
	ASPECT_RATIO_64_27,
	ASPECT_RATIO_256_135,
	ASPECT_RATIO_FUTURE
पूर्ण;

क्रमागत scanning_type अणु
	SCANNING_TYPE_NODATA = 0,
	SCANNING_TYPE_OVERSCAN,
	SCANNING_TYPE_UNDERSCAN,
	SCANNING_TYPE_FUTURE,
	SCANNING_TYPE_UNDEFINED
पूर्ण;

काष्ठा dc_crtc_timing_flags अणु
	uपूर्णांक32_t INTERLACE :1;
	uपूर्णांक32_t HSYNC_POSITIVE_POLARITY :1; /* when set to 1,
	 it is positive polarity --reversed with dal1 or video bios define*/
	uपूर्णांक32_t VSYNC_POSITIVE_POLARITY :1; /* when set to 1,
	 it is positive polarity --reversed with dal1 or video bios define*/

	uपूर्णांक32_t HORZ_COUNT_BY_TWO:1;

	uपूर्णांक32_t EXCLUSIVE_3D :1; /* अगर this bit set,
	 timing can be driven in 3D क्रमmat only
	 and there is no corresponding 2D timing*/
	uपूर्णांक32_t RIGHT_EYE_3D_POLARITY :1; /* 1 - means right eye polarity
	 (right eye = '1', left eye = '0') */
	uपूर्णांक32_t SUB_SAMPLE_3D :1; /* 1 - means left/right  images subsampled
	 when mixed पूर्णांकo 3D image. 0 - means summation (3D timing is द्विगुनd)*/
	uपूर्णांक32_t USE_IN_3D_VIEW_ONLY :1; /* Do not use this timing in 2D View,
	 because corresponding 2D timing also present in the list*/
	uपूर्णांक32_t STEREO_3D_PREFERENCE :1; /* Means this is 2D timing
	 and we want to match priority of corresponding 3D timing*/
	uपूर्णांक32_t Y_ONLY :1;

	uपूर्णांक32_t YCBCR420 :1; /* TODO: shouldn't need this flag, should be a separate pixel क्रमmat */
	uपूर्णांक32_t DTD_COUNTER :5; /* values 1 to 16 */

	uपूर्णांक32_t FORCE_HDR :1;

	/* HDMI 2.0 - Support scrambling क्रम TMDS अक्षरacter
	 * rates less than or equal to 340Mcsc */
	uपूर्णांक32_t LTE_340MCSC_SCRAMBLE:1;

	uपूर्णांक32_t DSC : 1; /* Use DSC with this timing */
#अगर_अघोषित TRIM_FSFT
	uपूर्णांक32_t FAST_TRANSPORT: 1;
#पूर्ण_अगर
	uपूर्णांक32_t VBLANK_SYNCHRONIZABLE: 1;
पूर्ण;

क्रमागत dc_timing_3d_क्रमmat अणु
	TIMING_3D_FORMAT_NONE,
	TIMING_3D_FORMAT_FRAME_ALTERNATE, /* No stereosync at all*/
	TIMING_3D_FORMAT_INBAND_FA, /* Inband Frame Alternate (DVI/DP)*/
	TIMING_3D_FORMAT_DP_HDMI_INBAND_FA, /* Inband FA to HDMI Frame Pack*/
	/* क्रम active DP-HDMI करोngle*/
	TIMING_3D_FORMAT_SIDEBAND_FA, /* Sideband Frame Alternate (eDP)*/
	TIMING_3D_FORMAT_HW_FRAME_PACKING,
	TIMING_3D_FORMAT_SW_FRAME_PACKING,
	TIMING_3D_FORMAT_ROW_INTERLEAVE,
	TIMING_3D_FORMAT_COLUMN_INTERLEAVE,
	TIMING_3D_FORMAT_PIXEL_INTERLEAVE,
	TIMING_3D_FORMAT_SIDE_BY_SIDE,
	TIMING_3D_FORMAT_TOP_AND_BOTTOM,
	TIMING_3D_FORMAT_SBS_SW_PACKED,
	/* Side-by-side, packed by application/driver पूर्णांकo 2D frame*/
	TIMING_3D_FORMAT_TB_SW_PACKED,
	/* Top-and-bottom, packed by application/driver पूर्णांकo 2D frame*/

	TIMING_3D_FORMAT_MAX,
पूर्ण;

काष्ठा dc_dsc_config अणु
	uपूर्णांक32_t num_slices_h; /* Number of DSC slices - horizontal */
	uपूर्णांक32_t num_slices_v; /* Number of DSC slices - vertical */
	uपूर्णांक32_t bits_per_pixel; /* DSC target bitrate in 1/16 of bpp (e.g. 128 -> 8bpp) */
	bool block_pred_enable; /* DSC block prediction enable */
	uपूर्णांक32_t linebuf_depth; /* DSC line buffer depth */
	uपूर्णांक32_t version_minor; /* DSC minor version. Full version is क्रमmed as 1.version_minor. */
	bool ycbcr422_simple; /* Tell DSC engine to convert YCbCr 4:2:2 to 'YCbCr 4:2:2 simple'. */
	पूर्णांक32_t rc_buffer_size; /* DSC RC buffer block size in bytes */
पूर्ण;
काष्ठा dc_crtc_timing अणु
	uपूर्णांक32_t h_total;
	uपूर्णांक32_t h_border_left;
	uपूर्णांक32_t h_addressable;
	uपूर्णांक32_t h_border_right;
	uपूर्णांक32_t h_front_porch;
	uपूर्णांक32_t h_sync_width;

	uपूर्णांक32_t v_total;
	uपूर्णांक32_t v_border_top;
	uपूर्णांक32_t v_addressable;
	uपूर्णांक32_t v_border_bottom;
	uपूर्णांक32_t v_front_porch;
	uपूर्णांक32_t v_sync_width;

	uपूर्णांक32_t pix_clk_100hz;

	uपूर्णांक32_t vic;
	uपूर्णांक32_t hdmi_vic;
	क्रमागत dc_timing_3d_क्रमmat timing_3d_क्रमmat;
	क्रमागत dc_color_depth display_color_depth;
	क्रमागत dc_pixel_encoding pixel_encoding;
	क्रमागत dc_aspect_ratio aspect_ratio;
	क्रमागत scanning_type scan_type;

#अगर_अघोषित TRIM_FSFT
	uपूर्णांक32_t fast_transport_output_rate_100hz;
#पूर्ण_अगर

	काष्ठा dc_crtc_timing_flags flags;
	uपूर्णांक32_t dsc_fixed_bits_per_pixel_x16; /* DSC target bitrate in 1/16 of bpp (e.g. 128 -> 8bpp) */
	काष्ठा dc_dsc_config dsc_cfg;
पूर्ण;

क्रमागत trigger_delay अणु
	TRIGGER_DELAY_NEXT_PIXEL = 0,
	TRIGGER_DELAY_NEXT_LINE,
पूर्ण;

क्रमागत crtc_event अणु
	CRTC_EVENT_VSYNC_RISING = 0,
	CRTC_EVENT_VSYNC_FALLING
पूर्ण;

काष्ठा crtc_trigger_info अणु
	bool enabled;
	काष्ठा dc_stream_state *event_source;
	क्रमागत crtc_event event;
	क्रमागत trigger_delay delay;
पूर्ण;

काष्ठा dc_crtc_timing_adjust अणु
	uपूर्णांक32_t v_total_min;
	uपूर्णांक32_t v_total_max;
	uपूर्णांक32_t v_total_mid;
	uपूर्णांक32_t v_total_mid_frame_num;
पूर्ण;


/* Passed on init */
क्रमागत vram_type अणु
	VIDEO_MEMORY_TYPE_GDDR5  = 2,
	VIDEO_MEMORY_TYPE_DDR3   = 3,
	VIDEO_MEMORY_TYPE_DDR4   = 4,
	VIDEO_MEMORY_TYPE_HBM    = 5,
	VIDEO_MEMORY_TYPE_GDDR6  = 6,
पूर्ण;

क्रमागत dwb_cnv_out_bpc अणु
	DWB_CNV_OUT_BPC_8BPC  = 0,
	DWB_CNV_OUT_BPC_10BPC = 1,
पूर्ण;

क्रमागत dwb_output_depth अणु
	DWB_OUTPUT_PIXEL_DEPTH_8BPC = 0,
	DWB_OUTPUT_PIXEL_DEPTH_10BPC = 1,
पूर्ण;

क्रमागत dwb_capture_rate अणु
	dwb_capture_rate_0 = 0,	/* Every frame is captured. */
	dwb_capture_rate_1 = 1,	/* Every other frame is captured. */
	dwb_capture_rate_2 = 2,	/* Every 3rd frame is captured. */
	dwb_capture_rate_3 = 3,	/* Every 4th frame is captured. */
पूर्ण;

क्रमागत dwb_scaler_mode अणु
	dwb_scaler_mode_bypass444 = 0,
	dwb_scaler_mode_rgb444 = 1,
	dwb_scaler_mode_yuv444 = 2,
	dwb_scaler_mode_yuv420 = 3
पूर्ण;

क्रमागत dwb_subsample_position अणु
	DWB_INTERSTITIAL_SUBSAMPLING = 0,
	DWB_COSITED_SUBSAMPLING      = 1
पूर्ण;

क्रमागत dwb_stereo_eye_select अणु
	DWB_STEREO_EYE_LEFT  = 1,		/* Capture left eye only */
	DWB_STEREO_EYE_RIGHT = 2,		/* Capture right eye only */
पूर्ण;

क्रमागत dwb_stereo_type अणु
	DWB_STEREO_TYPE_FRAME_PACKING = 0,		/* Frame packing */
	DWB_STEREO_TYPE_FRAME_SEQUENTIAL = 3,	/* Frame sequential */
पूर्ण;

क्रमागत dwb_out_क्रमmat अणु
	DWB_OUT_FORMAT_32BPP_ARGB = 0,
	DWB_OUT_FORMAT_32BPP_RGBA = 1,
	DWB_OUT_FORMAT_64BPP_ARGB = 2,
	DWB_OUT_FORMAT_64BPP_RGBA = 3
पूर्ण;

क्रमागत dwb_out_denorm अणु
	DWB_OUT_DENORM_10BPC = 0,
	DWB_OUT_DENORM_8BPC = 1,
	DWB_OUT_DENORM_BYPASS = 2
पूर्ण;

क्रमागत cm_gamut_remap_select अणु
	CM_GAMUT_REMAP_MODE_BYPASS = 0,
	CM_GAMUT_REMAP_MODE_RAMA_COEFF,
	CM_GAMUT_REMAP_MODE_RAMB_COEFF,
	CM_GAMUT_REMAP_MODE_RESERVED
पूर्ण;

क्रमागत cm_gamut_coef_क्रमmat अणु
	CM_GAMUT_REMAP_COEF_FORMAT_S2_13 = 0,
	CM_GAMUT_REMAP_COEF_FORMAT_S3_12 = 1
पूर्ण;

काष्ठा mcअगर_warmup_params अणु
	जोड़ large_पूर्णांकeger	start_address;
	अचिन्हित पूर्णांक		address_increment;
	अचिन्हित पूर्णांक		region_size;
	अचिन्हित पूर्णांक		p_vmid;
पूर्ण;

#घोषणा MCIF_BUF_COUNT	4

काष्ठा mcअगर_buf_params अणु
	अचिन्हित दीर्घ दीर्घ	luma_address[MCIF_BUF_COUNT];
	अचिन्हित दीर्घ दीर्घ	chroma_address[MCIF_BUF_COUNT];
	अचिन्हित पूर्णांक		luma_pitch;
	अचिन्हित पूर्णांक		chroma_pitch;
	अचिन्हित पूर्णांक		warmup_pitch;
	अचिन्हित पूर्णांक		swlock;
	अचिन्हित पूर्णांक		p_vmid;
पूर्ण;


#घोषणा MAX_TG_COLOR_VALUE 0x3FF
काष्ठा tg_color अणु
	/* Maximum 10 bits color value */
	uपूर्णांक16_t color_r_cr;
	uपूर्णांक16_t color_g_y;
	uपूर्णांक16_t color_b_cb;
पूर्ण;

#पूर्ण_अगर /* DC_HW_TYPES_H */

