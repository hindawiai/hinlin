<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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
#अगर_अघोषित DC_TYPES_H_
#घोषणा DC_TYPES_H_

/* AND EdidUtility only needs a portion
 * of this file, including the rest only
 * causes additional issues.
 */
#समावेश "os_types.h"
#समावेश "fixed31_32.h"
#समावेश "irq_types.h"
#समावेश "dc_dp_types.h"
#समावेश "dc_hw_types.h"
#समावेश "dal_types.h"
#समावेश "grph_object_defs.h"

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
#समावेश "dm_cp_psp.h"
#पूर्ण_अगर

/* क्रमward declarations */
काष्ठा dc_plane_state;
काष्ठा dc_stream_state;
काष्ठा dc_link;
काष्ठा dc_sink;
काष्ठा dal;
काष्ठा dc_dmub_srv;

/********************************
 * Environment definitions
 ********************************/
क्रमागत dce_environment अणु
	DCE_ENV_PRODUCTION_DRV = 0,
	/* Emulation on FPGA, in "Maximus" System.
	 * This environment enक्रमces that *only* DC रेजिस्टरs accessed.
	 * (access to non-DC रेजिस्टरs will hang FPGA) */
	DCE_ENV_FPGA_MAXIMUS,
	/* Emulation on real HW or on FPGA. Used by Diagnostics, enक्रमces
	 * requirements of Diagnostics team. */
	DCE_ENV_DIAG,
	/*
	 * Guest VM प्रणाली, DC HW may exist but is not भवized and
	 * should not be used.  SW support क्रम VDI only.
	 */
	DCE_ENV_VIRTUAL_HW
पूर्ण;

/* Note: use these macro definitions instead of direct comparison! */
#घोषणा IS_FPGA_MAXIMUS_DC(dce_environment) \
	(dce_environment == DCE_ENV_FPGA_MAXIMUS)

#घोषणा IS_DIAG_DC(dce_environment) \
	(IS_FPGA_MAXIMUS_DC(dce_environment) || (dce_environment == DCE_ENV_DIAG))

काष्ठा hw_asic_id अणु
	uपूर्णांक32_t chip_id;
	uपूर्णांक32_t chip_family;
	uपूर्णांक32_t pci_revision_id;
	uपूर्णांक32_t hw_पूर्णांकernal_rev;
	uपूर्णांक32_t vram_type;
	uपूर्णांक32_t vram_width;
	uपूर्णांक32_t feature_flags;
	uपूर्णांक32_t fake_paths_num;
	व्योम *atombios_base_address;
पूर्ण;

काष्ठा dc_perf_trace अणु
	अचिन्हित दीर्घ पढ़ो_count;
	अचिन्हित दीर्घ ग_लिखो_count;
	अचिन्हित दीर्घ last_entry_पढ़ो;
	अचिन्हित दीर्घ last_entry_ग_लिखो;
पूर्ण;

काष्ठा dc_context अणु
	काष्ठा dc *dc;

	व्योम *driver_context; /* e.g. amdgpu_device */
	काष्ठा dc_perf_trace *perf_trace;
	व्योम *cgs_device;

	क्रमागत dce_environment dce_environment;
	काष्ठा hw_asic_id asic_id;

	/* toकरो: below should probably move to dc.  to facilitate removal
	 * of AS we will store these here
	 */
	क्रमागत dce_version dce_version;
	काष्ठा dc_bios *dc_bios;
	bool created_bios;
	काष्ठा gpio_service *gpio_service;
	uपूर्णांक32_t dc_sink_id_count;
	uपूर्णांक32_t dc_stream_id_count;
	uपूर्णांक32_t dc_edp_id_count;
	uपूर्णांक64_t fbc_gpu_addr;
	काष्ठा dc_dmub_srv *dmub_srv;

#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	काष्ठा cp_psp cp_psp;
#पूर्ण_अगर
पूर्ण;


#घोषणा DC_MAX_EDID_BUFFER_SIZE 1280
#घोषणा DC_EDID_BLOCK_SIZE 128
#घोषणा MAX_SURFACE_NUM 4
#घोषणा NUM_PIXEL_FORMATS 10
#घोषणा MAX_REPEATER_CNT 8

#समावेश "dc_ddc_types.h"

क्रमागत tiling_mode अणु
	TILING_MODE_INVALID,
	TILING_MODE_LINEAR,
	TILING_MODE_TILED,
	TILING_MODE_COUNT
पूर्ण;

क्रमागत view_3d_क्रमmat अणु
	VIEW_3D_FORMAT_NONE = 0,
	VIEW_3D_FORMAT_FRAME_SEQUENTIAL,
	VIEW_3D_FORMAT_SIDE_BY_SIDE,
	VIEW_3D_FORMAT_TOP_AND_BOTTOM,
	VIEW_3D_FORMAT_COUNT,
	VIEW_3D_FORMAT_FIRST = VIEW_3D_FORMAT_FRAME_SEQUENTIAL
पूर्ण;

क्रमागत plane_stereo_क्रमmat अणु
	PLANE_STEREO_FORMAT_NONE = 0,
	PLANE_STEREO_FORMAT_SIDE_BY_SIDE = 1,
	PLANE_STEREO_FORMAT_TOP_AND_BOTTOM = 2,
	PLANE_STEREO_FORMAT_FRAME_ALTERNATE = 3,
	PLANE_STEREO_FORMAT_ROW_INTERLEAVED = 5,
	PLANE_STEREO_FORMAT_COLUMN_INTERLEAVED = 6,
	PLANE_STEREO_FORMAT_CHECKER_BOARD = 7
पूर्ण;

/* TODO: Find way to calculate number of bits
 *  Please increase अगर pixel_क्रमmat क्रमागत increases
 * num  from  PIXEL_FORMAT_INDEX8 to PIXEL_FORMAT_444BPP32
 */

क्रमागत dc_edid_connector_type अणु
	DC_EDID_CONNECTOR_UNKNOWN = 0,
	DC_EDID_CONNECTOR_ANALOG = 1,
	DC_EDID_CONNECTOR_DIGITAL = 10,
	DC_EDID_CONNECTOR_DVI = 11,
	DC_EDID_CONNECTOR_HDMIA = 12,
	DC_EDID_CONNECTOR_MDDI = 14,
	DC_EDID_CONNECTOR_DISPLAYPORT = 15
पूर्ण;

क्रमागत dc_edid_status अणु
	EDID_OK,
	EDID_BAD_INPUT,
	EDID_NO_RESPONSE,
	EDID_BAD_CHECKSUM,
	EDID_THE_SAME,
	EDID_FALL_BACK,
पूर्ण;

क्रमागत act_वापस_status अणु
	ACT_SUCCESS,
	ACT_LINK_LOST,
	ACT_FAILED
पूर्ण;

/* audio capability from EDID*/
काष्ठा dc_cea_audio_mode अणु
	uपूर्णांक8_t क्रमmat_code; /* ucData[0] [6:3]*/
	uपूर्णांक8_t channel_count; /* ucData[0] [2:0]*/
	uपूर्णांक8_t sample_rate; /* ucData[1]*/
	जोड़ अणु
		uपूर्णांक8_t sample_size; /* क्रम LPCM*/
		/*  क्रम Audio Formats 2-8 (Max bit rate भागided by 8 kHz)*/
		uपूर्णांक8_t max_bit_rate;
		uपूर्णांक8_t audio_codec_venकरोr_specअगरic; /* क्रम Audio Formats 9-15*/
	पूर्ण;
पूर्ण;

काष्ठा dc_edid अणु
	uपूर्णांक32_t length;
	uपूर्णांक8_t raw_edid[DC_MAX_EDID_BUFFER_SIZE];
पूर्ण;

/* When speaker location data block is not available, DEFAULT_SPEAKER_LOCATION
 * is used. In this हाल we assume speaker location are: front left, front
 * right and front center. */
#घोषणा DEFAULT_SPEAKER_LOCATION 5

#घोषणा DC_MAX_AUDIO_DESC_COUNT 16

#घोषणा AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS 20

जोड़ display_content_support अणु
	अचिन्हित पूर्णांक raw;
	काष्ठा अणु
		अचिन्हित पूर्णांक valid_content_type :1;
		अचिन्हित पूर्णांक game_content :1;
		अचिन्हित पूर्णांक cinema_content :1;
		अचिन्हित पूर्णांक photo_content :1;
		अचिन्हित पूर्णांक graphics_content :1;
		अचिन्हित पूर्णांक reserved :27;
	पूर्ण bits;
पूर्ण;

काष्ठा dc_panel_patch अणु
	अचिन्हित पूर्णांक dpघातerup_delay;
	अचिन्हित पूर्णांक extra_t12_ms;
	अचिन्हित पूर्णांक extra_delay_backlight_off;
	अचिन्हित पूर्णांक extra_t7_ms;
	अचिन्हित पूर्णांक skip_scdc_overग_लिखो;
	अचिन्हित पूर्णांक delay_ignore_msa;
	अचिन्हित पूर्णांक disable_fec;
	अचिन्हित पूर्णांक extra_t3_ms;
	अचिन्हित पूर्णांक max_dsc_target_bpp_limit;
	अचिन्हित पूर्णांक skip_avmute;
पूर्ण;

काष्ठा dc_edid_caps अणु
	/* sink identअगरication */
	uपूर्णांक16_t manufacturer_id;
	uपूर्णांक16_t product_id;
	uपूर्णांक32_t serial_number;
	uपूर्णांक8_t manufacture_week;
	uपूर्णांक8_t manufacture_year;
	uपूर्णांक8_t display_name[AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS];

	/* audio caps */
	uपूर्णांक8_t speaker_flags;
	uपूर्णांक32_t audio_mode_count;
	काष्ठा dc_cea_audio_mode audio_modes[DC_MAX_AUDIO_DESC_COUNT];
	uपूर्णांक32_t audio_latency;
	uपूर्णांक32_t video_latency;

	जोड़ display_content_support content_support;

	uपूर्णांक8_t qs_bit;
	uपूर्णांक8_t qy_bit;

	uपूर्णांक32_t max_पंचांगds_clk_mhz;

	/*HDMI 2.0 caps*/
	bool lte_340mcsc_scramble;

	bool edid_hdmi;
	bool hdr_supported;

	काष्ठा dc_panel_patch panel_patch;
पूर्ण;

काष्ठा view अणु
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
पूर्ण;

काष्ठा dc_mode_flags अणु
	/* note: part of refresh rate flag*/
	uपूर्णांक32_t INTERLACE :1;
	/* native display timing*/
	uपूर्णांक32_t NATIVE :1;
	/* preferred is the recommended mode, one per display */
	uपूर्णांक32_t PREFERRED :1;
	/* true अगर this mode should use reduced blanking timings
	 *_not_ related to the Reduced Blanking adjusपंचांगent*/
	uपूर्णांक32_t REDUCED_BLANKING :1;
	/* note: part of refreshrate flag*/
	uपूर्णांक32_t VIDEO_OPTIMIZED_RATE :1;
	/* should be reported to upper layers as mode_flags*/
	uपूर्णांक32_t PACKED_PIXEL_FORMAT :1;
	/*< preferred view*/
	uपूर्णांक32_t PREFERRED_VIEW :1;
	/* this timing should be used only in tiled mode*/
	uपूर्णांक32_t TILED_MODE :1;
	uपूर्णांक32_t DSE_MODE :1;
	/* Refresh rate भागider when Miracast sink is using a
	 dअगरferent rate than the output display device
	 Must be zero क्रम wired displays and non-zero क्रम
	 Miracast displays*/
	uपूर्णांक32_t MIRACAST_REFRESH_DIVIDER;
पूर्ण;


क्रमागत dc_timing_source अणु
	TIMING_SOURCE_UNDEFINED,

	/* explicitly specअगरed by user, most important*/
	TIMING_SOURCE_USER_FORCED,
	TIMING_SOURCE_USER_OVERRIDE,
	TIMING_SOURCE_CUSTOM,
	TIMING_SOURCE_EXPLICIT,

	/* explicitly specअगरied by the display device, more important*/
	TIMING_SOURCE_EDID_CEA_SVD_3D,
	TIMING_SOURCE_EDID_CEA_SVD_PREFERRED,
	TIMING_SOURCE_EDID_CEA_SVD_420,
	TIMING_SOURCE_EDID_DETAILED,
	TIMING_SOURCE_EDID_ESTABLISHED,
	TIMING_SOURCE_EDID_STANDARD,
	TIMING_SOURCE_EDID_CEA_SVD,
	TIMING_SOURCE_EDID_CVT_3BYTE,
	TIMING_SOURCE_EDID_4BYTE,
	TIMING_SOURCE_VBIOS,
	TIMING_SOURCE_CV,
	TIMING_SOURCE_TV,
	TIMING_SOURCE_HDMI_VIC,

	/* implicitly specअगरied by display device, still safe but less important*/
	TIMING_SOURCE_DEFAULT,

	/* only used क्रम custom base modes */
	TIMING_SOURCE_CUSTOM_BASE,

	/* these timing might not work, least important*/
	TIMING_SOURCE_RANGELIMIT,
	TIMING_SOURCE_OS_FORCED,
	TIMING_SOURCE_IMPLICIT,

	/* only used by शेष mode list*/
	TIMING_SOURCE_BASICMODE,

	TIMING_SOURCE_COUNT
पूर्ण;


काष्ठा stereo_3d_features अणु
	bool supported			;
	bool allTimings			;
	bool cloneMode			;
	bool scaling			;
	bool singleFrameSWPacked;
पूर्ण;

क्रमागत dc_timing_support_method अणु
	TIMING_SUPPORT_METHOD_UNDEFINED,
	TIMING_SUPPORT_METHOD_EXPLICIT,
	TIMING_SUPPORT_METHOD_IMPLICIT,
	TIMING_SUPPORT_METHOD_NATIVE
पूर्ण;

काष्ठा dc_mode_info अणु
	uपूर्णांक32_t pixel_width;
	uपूर्णांक32_t pixel_height;
	uपूर्णांक32_t field_rate;
	/* Vertical refresh rate क्रम progressive modes.
	* Field rate क्रम पूर्णांकerlaced modes.*/

	क्रमागत dc_timing_standard timing_standard;
	क्रमागत dc_timing_source timing_source;
	काष्ठा dc_mode_flags flags;
पूर्ण;

क्रमागत dc_घातer_state अणु
	DC_POWER_STATE_ON = 1,
	DC_POWER_STATE_STANDBY,
	DC_POWER_STATE_SUSPEND,
	DC_POWER_STATE_OFF
पूर्ण;

/* DC PowerStates */
क्रमागत dc_video_घातer_state अणु
	DC_VIDEO_POWER_UNSPECIFIED = 0,
	DC_VIDEO_POWER_ON = 1,
	DC_VIDEO_POWER_STANDBY,
	DC_VIDEO_POWER_SUSPEND,
	DC_VIDEO_POWER_OFF,
	DC_VIDEO_POWER_HIBERNATE,
	DC_VIDEO_POWER_SHUTDOWN,
	DC_VIDEO_POWER_ULPS,	/* BACO or Ultra-Light-Power-State */
	DC_VIDEO_POWER_AFTER_RESET,
	DC_VIDEO_POWER_MAXIMUM
पूर्ण;

क्रमागत dc_acpi_cm_घातer_state अणु
	DC_ACPI_CM_POWER_STATE_D0 = 1,
	DC_ACPI_CM_POWER_STATE_D1 = 2,
	DC_ACPI_CM_POWER_STATE_D2 = 4,
	DC_ACPI_CM_POWER_STATE_D3 = 8
पूर्ण;

क्रमागत dc_connection_type अणु
	dc_connection_none,
	dc_connection_single,
	dc_connection_mst_branch,
	dc_connection_active_करोngle
पूर्ण;

काष्ठा dc_csc_adjusपंचांगents अणु
	काष्ठा fixed31_32 contrast;
	काष्ठा fixed31_32 saturation;
	काष्ठा fixed31_32 brightness;
	काष्ठा fixed31_32 hue;
पूर्ण;

क्रमागत dpcd_करोwnstream_port_max_bpc अणु
	DOWN_STREAM_MAX_8BPC = 0,
	DOWN_STREAM_MAX_10BPC,
	DOWN_STREAM_MAX_12BPC,
	DOWN_STREAM_MAX_16BPC
पूर्ण;


क्रमागत link_training_offset अणु
	DPRX                = 0,
	LTTPR_PHY_REPEATER1 = 1,
	LTTPR_PHY_REPEATER2 = 2,
	LTTPR_PHY_REPEATER3 = 3,
	LTTPR_PHY_REPEATER4 = 4,
	LTTPR_PHY_REPEATER5 = 5,
	LTTPR_PHY_REPEATER6 = 6,
	LTTPR_PHY_REPEATER7 = 7,
	LTTPR_PHY_REPEATER8 = 8
पूर्ण;

काष्ठा dc_lttpr_caps अणु
	जोड़ dpcd_rev revision;
	uपूर्णांक8_t mode;
	uपूर्णांक8_t max_lane_count;
	uपूर्णांक8_t max_link_rate;
	uपूर्णांक8_t phy_repeater_cnt;
	uपूर्णांक8_t max_ext_समयout;
	uपूर्णांक8_t aux_rd_पूर्णांकerval[MAX_REPEATER_CNT - 1];
पूर्ण;

काष्ठा dc_करोngle_caps अणु
	/* करोngle type (DP converter, CV smart करोngle) */
	क्रमागत display_करोngle_type करोngle_type;
	bool extendedCapValid;
	/* If करोngle_type == DISPLAY_DONGLE_DP_HDMI_CONVERTER,
	indicates 'Frame Sequential-to-lllFrame Pack' conversion capability.*/
	bool is_dp_hdmi_s3d_converter;
	bool is_dp_hdmi_ycbcr422_pass_through;
	bool is_dp_hdmi_ycbcr420_pass_through;
	bool is_dp_hdmi_ycbcr422_converter;
	bool is_dp_hdmi_ycbcr420_converter;
	uपूर्णांक32_t dp_hdmi_max_bpc;
	uपूर्णांक32_t dp_hdmi_max_pixel_clk_in_khz;
पूर्ण;
/* Scaling क्रमmat */
क्रमागत scaling_transक्रमmation अणु
	SCALING_TRANSFORMATION_UNINITIALIZED,
	SCALING_TRANSFORMATION_IDENTITY = 0x0001,
	SCALING_TRANSFORMATION_CENTER_TIMING = 0x0002,
	SCALING_TRANSFORMATION_FULL_SCREEN_SCALE = 0x0004,
	SCALING_TRANSFORMATION_PRESERVE_ASPECT_RATIO_SCALE = 0x0008,
	SCALING_TRANSFORMATION_DAL_DECIDE = 0x0010,
	SCALING_TRANSFORMATION_INVALID = 0x80000000,

	/* Flag the first and last */
	SCALING_TRANSFORMATION_BEGING = SCALING_TRANSFORMATION_IDENTITY,
	SCALING_TRANSFORMATION_END =
		SCALING_TRANSFORMATION_PRESERVE_ASPECT_RATIO_SCALE
पूर्ण;

क्रमागत display_content_type अणु
	DISPLAY_CONTENT_TYPE_NO_DATA = 0,
	DISPLAY_CONTENT_TYPE_GRAPHICS = 1,
	DISPLAY_CONTENT_TYPE_PHOTO = 2,
	DISPLAY_CONTENT_TYPE_CINEMA = 4,
	DISPLAY_CONTENT_TYPE_GAME = 8
पूर्ण;

क्रमागत cm_gamut_adjust_type अणु
	CM_GAMUT_ADJUST_TYPE_BYPASS = 0,
	CM_GAMUT_ADJUST_TYPE_HW, /* without adjusपंचांगents */
	CM_GAMUT_ADJUST_TYPE_SW /* use adjusपंचांगents */
पूर्ण;

काष्ठा cm_grph_csc_adjusपंचांगent अणु
	काष्ठा fixed31_32 temperature_matrix[12];
	क्रमागत cm_gamut_adjust_type gamut_adjust_type;
	क्रमागत cm_gamut_coef_क्रमmat gamut_coef_क्रमmat;
पूर्ण;

/* ग_लिखोback */
काष्ठा dwb_stereo_params अणु
	bool				stereo_enabled;		/* false: normal mode, true: 3D stereo */
	क्रमागत dwb_stereo_type		stereo_type;		/* indicates stereo क्रमmat */
	bool				stereo_polarity;	/* indicates left eye or right eye comes first in stereo mode */
	क्रमागत dwb_stereo_eye_select	stereo_eye_select;	/* indicate which eye should be captured */
पूर्ण;

काष्ठा dc_dwb_cnv_params अणु
	अचिन्हित पूर्णांक		src_width;	/* input active width */
	अचिन्हित पूर्णांक		src_height;	/* input active height (half-active height in पूर्णांकerlaced mode) */
	अचिन्हित पूर्णांक		crop_width;	/* cropped winकरोw width at cnv output */
	bool			crop_en;	/* winकरोw cropping enable in cnv */
	अचिन्हित पूर्णांक		crop_height;	/* cropped winकरोw height at cnv output */
	अचिन्हित पूर्णांक		crop_x;		/* cropped winकरोw start x value at cnv output */
	अचिन्हित पूर्णांक		crop_y;		/* cropped winकरोw start y value at cnv output */
	क्रमागत dwb_cnv_out_bpc cnv_out_bpc;	/* cnv output pixel depth - 8bpc or 10bpc */
	क्रमागत dwb_out_क्रमmat	fc_out_क्रमmat;	/* dwb output pixel क्रमmat - 2101010 or 16161616 and ARGB or RGBA */
	क्रमागत dwb_out_denorm	out_denorm_mode;/* dwb output denormalization mode */
	अचिन्हित पूर्णांक		out_max_pix_val;/* pixel values greater than out_max_pix_val are clamped to out_max_pix_val */
	अचिन्हित पूर्णांक		out_min_pix_val;/* pixel values less than out_min_pix_val are clamped to out_min_pix_val */
पूर्ण;

काष्ठा dc_dwb_params अणु
	अचिन्हित पूर्णांक			dwbscl_black_color; /* must be in FP1.5.10 */
	अचिन्हित पूर्णांक			hdr_mult;	/* must be in FP1.6.12 */
	काष्ठा cm_grph_csc_adjusपंचांगent	csc_params;
	काष्ठा dwb_stereo_params	stereo_params;
	काष्ठा dc_dwb_cnv_params	cnv_params;	/* CNV source size and cropping winकरोw parameters */
	अचिन्हित पूर्णांक			dest_width;	/* Destination width */
	अचिन्हित पूर्णांक			dest_height;	/* Destination height */
	क्रमागत dwb_scaler_mode		out_क्रमmat;	/* शेष = YUV420 - TODO: limit this to 0 and 1 on dcn3 */
	क्रमागत dwb_output_depth		output_depth;	/* output pixel depth - 8bpc or 10bpc */
	क्रमागत dwb_capture_rate		capture_rate;	/* controls the frame capture rate */
	काष्ठा scaling_taps 		scaler_taps;	/* Scaling taps */
	क्रमागत dwb_subsample_position	subsample_position;
	काष्ठा dc_transfer_func *out_transfer_func;
पूर्ण;

/* audio*/

जोड़ audio_sample_rates अणु
	काष्ठा sample_rates अणु
		uपूर्णांक8_t RATE_32:1;
		uपूर्णांक8_t RATE_44_1:1;
		uपूर्णांक8_t RATE_48:1;
		uपूर्णांक8_t RATE_88_2:1;
		uपूर्णांक8_t RATE_96:1;
		uपूर्णांक8_t RATE_176_4:1;
		uपूर्णांक8_t RATE_192:1;
	पूर्ण rate;

	uपूर्णांक8_t all;
पूर्ण;

काष्ठा audio_speaker_flags अणु
	uपूर्णांक32_t FL_FR:1;
	uपूर्णांक32_t LFE:1;
	uपूर्णांक32_t FC:1;
	uपूर्णांक32_t RL_RR:1;
	uपूर्णांक32_t RC:1;
	uपूर्णांक32_t FLC_FRC:1;
	uपूर्णांक32_t RLC_RRC:1;
	uपूर्णांक32_t SUPPORT_AI:1;
पूर्ण;

काष्ठा audio_speaker_info अणु
	uपूर्णांक32_t ALLSPEAKERS:7;
	uपूर्णांक32_t SUPPORT_AI:1;
पूर्ण;


काष्ठा audio_info_flags अणु

	जोड़ अणु

		काष्ठा audio_speaker_flags speaker_flags;
		काष्ठा audio_speaker_info   info;

		uपूर्णांक8_t all;
	पूर्ण;
पूर्ण;

क्रमागत audio_क्रमmat_code अणु
	AUDIO_FORMAT_CODE_FIRST = 1,
	AUDIO_FORMAT_CODE_LINEARPCM = AUDIO_FORMAT_CODE_FIRST,

	AUDIO_FORMAT_CODE_AC3,
	/*Layers 1 & 2 */
	AUDIO_FORMAT_CODE_MPEG1,
	/*MPEG1 Layer 3 */
	AUDIO_FORMAT_CODE_MP3,
	/*multichannel */
	AUDIO_FORMAT_CODE_MPEG2,
	AUDIO_FORMAT_CODE_AAC,
	AUDIO_FORMAT_CODE_DTS,
	AUDIO_FORMAT_CODE_ATRAC,
	AUDIO_FORMAT_CODE_1BITAUDIO,
	AUDIO_FORMAT_CODE_DOLBYDIGITALPLUS,
	AUDIO_FORMAT_CODE_DTS_HD,
	AUDIO_FORMAT_CODE_MAT_MLP,
	AUDIO_FORMAT_CODE_DST,
	AUDIO_FORMAT_CODE_WMAPRO,
	AUDIO_FORMAT_CODE_LAST,
	AUDIO_FORMAT_CODE_COUNT =
		AUDIO_FORMAT_CODE_LAST - AUDIO_FORMAT_CODE_FIRST
पूर्ण;

काष्ठा audio_mode अणु
	 /* ucData[0] [6:3] */
	क्रमागत audio_क्रमmat_code क्रमmat_code;
	/* ucData[0] [2:0] */
	uपूर्णांक8_t channel_count;
	/* ucData[1] */
	जोड़ audio_sample_rates sample_rates;
	जोड़ अणु
		/* क्रम LPCM */
		uपूर्णांक8_t sample_size;
		/* क्रम Audio Formats 2-8 (Max bit rate भागided by 8 kHz) */
		uपूर्णांक8_t max_bit_rate;
		/* क्रम Audio Formats 9-15 */
		uपूर्णांक8_t venकरोr_specअगरic;
	पूर्ण;
पूर्ण;

काष्ठा audio_info अणु
	काष्ठा audio_info_flags flags;
	uपूर्णांक32_t video_latency;
	uपूर्णांक32_t audio_latency;
	uपूर्णांक32_t display_index;
	uपूर्णांक8_t display_name[AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS];
	uपूर्णांक32_t manufacture_id;
	uपूर्णांक32_t product_id;
	/* PortID used क्रम ContainerID when defined */
	uपूर्णांक32_t port_id[2];
	uपूर्णांक32_t mode_count;
	/* this field must be last in this काष्ठा */
	काष्ठा audio_mode modes[DC_MAX_AUDIO_DESC_COUNT];
पूर्ण;
काष्ठा audio_check अणु
	अचिन्हित पूर्णांक audio_packet_type;
	अचिन्हित पूर्णांक max_audiosample_rate;
	अचिन्हित पूर्णांक acat;
पूर्ण;
क्रमागत dc_infoframe_type अणु
	DC_HDMI_INFOFRAME_TYPE_VENDOR = 0x81,
	DC_HDMI_INFOFRAME_TYPE_AVI = 0x82,
	DC_HDMI_INFOFRAME_TYPE_SPD = 0x83,
	DC_HDMI_INFOFRAME_TYPE_AUDIO = 0x84,
	DC_DP_INFOFRAME_TYPE_PPS = 0x10,
पूर्ण;

काष्ठा dc_info_packet अणु
	bool valid;
	uपूर्णांक8_t hb0;
	uपूर्णांक8_t hb1;
	uपूर्णांक8_t hb2;
	uपूर्णांक8_t hb3;
	uपूर्णांक8_t sb[32];
पूर्ण;

काष्ठा dc_info_packet_128 अणु
	bool valid;
	uपूर्णांक8_t hb0;
	uपूर्णांक8_t hb1;
	uपूर्णांक8_t hb2;
	uपूर्णांक8_t hb3;
	uपूर्णांक8_t sb[128];
पूर्ण;

#घोषणा DC_PLANE_UPDATE_TIMES_MAX 10

काष्ठा dc_plane_flip_समय अणु
	अचिन्हित पूर्णांक समय_elapsed_in_us[DC_PLANE_UPDATE_TIMES_MAX];
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक prev_update_समय_in_us;
पूर्ण;

क्रमागत dc_psr_state अणु
	PSR_STATE0 = 0x0,
	PSR_STATE1,
	PSR_STATE1a,
	PSR_STATE2,
	PSR_STATE2a,
	PSR_STATE3,
	PSR_STATE3Init,
	PSR_STATE4,
	PSR_STATE4a,
	PSR_STATE4b,
	PSR_STATE4c,
	PSR_STATE4d,
	PSR_STATE5,
	PSR_STATE5a,
	PSR_STATE5b,
	PSR_STATE5c,
	PSR_STATE_INVALID = 0xFF
पूर्ण;

काष्ठा psr_config अणु
	अचिन्हित अक्षर psr_version;
	अचिन्हित पूर्णांक psr_rfb_setup_समय;
	bool psr_निकास_link_training_required;
	bool psr_frame_capture_indication_req;
	अचिन्हित पूर्णांक psr_sdp_transmit_line_num_deadline;
	bool allow_smu_optimizations;
	bool allow_multi_disp_optimizations;
पूर्ण;

जोड़ dmcu_psr_level अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक SKIP_CRC:1;
		अचिन्हित पूर्णांक SKIP_DP_VID_STREAM_DISABLE:1;
		अचिन्हित पूर्णांक SKIP_PHY_POWER_DOWN:1;
		अचिन्हित पूर्णांक SKIP_AUX_ACK_CHECK:1;
		अचिन्हित पूर्णांक SKIP_CRTC_DISABLE:1;
		अचिन्हित पूर्णांक SKIP_AUX_RFB_CAPTURE_CHECK:1;
		अचिन्हित पूर्णांक SKIP_SMU_NOTIFICATION:1;
		अचिन्हित पूर्णांक SKIP_AUTO_STATE_ADVANCE:1;
		अचिन्हित पूर्णांक DISABLE_PSR_ENTRY_ABORT:1;
		अचिन्हित पूर्णांक SKIP_SINGLE_OTG_DISABLE:1;
		अचिन्हित पूर्णांक RESERVED:22;
	पूर्ण bits;
	अचिन्हित पूर्णांक u32all;
पूर्ण;

क्रमागत physical_phy_id अणु
	PHYLD_0,
	PHYLD_1,
	PHYLD_2,
	PHYLD_3,
	PHYLD_4,
	PHYLD_5,
	PHYLD_6,
	PHYLD_7,
	PHYLD_8,
	PHYLD_9,
	PHYLD_COUNT,
	PHYLD_UNKNOWN = (-1L)
पूर्ण;

क्रमागत phy_type अणु
	PHY_TYPE_UNKNOWN  = 1,
	PHY_TYPE_PCIE_PHY = 2,
	PHY_TYPE_UNIPHY = 3,
पूर्ण;

काष्ठा psr_context अणु
	/* ddc line */
	क्रमागत channel_id channel;
	/* Transmitter id */
	क्रमागत transmitter transmitterId;
	/* Engine Id is used क्रम Dig Be source select */
	क्रमागत engine_id engineId;
	/* Controller Id used क्रम Dig Fe source select */
	क्रमागत controller_id controllerId;
	/* Pcie or Uniphy */
	क्रमागत phy_type phyType;
	/* Physical PHY Id used by SMU पूर्णांकerpretation */
	क्रमागत physical_phy_id smuPhyId;
	/* Vertical total pixels from crtc timing.
	 * This is used क्रम अटल screen detection.
	 * ie. If we want to detect half a frame,
	 * we use this to determine the hyst lines.
	 */
	अचिन्हित पूर्णांक crtcTimingVerticalTotal;
	/* PSR supported from panel capabilities and
	 * current display configuration
	 */
	bool psrSupportedDisplayConfig;
	/* Whether fast link training is supported by the panel */
	bool psrExitLinkTrainingRequired;
	/* If RFB setup समय is greater than the total VBLANK समय,
	 * it is not possible क्रम the sink to capture the video frame
	 * in the same frame the SDP is sent. In this हाल,
	 * the frame capture indication bit should be set and an extra
	 * अटल frame should be transmitted to the sink.
	 */
	bool psrFrameCaptureIndicationReq;
	/* Set the last possible line SDP may be transmitted without violating
	 * the RFB setup समय or entering the active video frame.
	 */
	अचिन्हित पूर्णांक sdpTransmitLineNumDeadline;
	/* The VSync rate in Hz used to calculate the
	 * step size क्रम smooth brightness feature
	 */
	अचिन्हित पूर्णांक vsync_rate_hz;
	अचिन्हित पूर्णांक skipPsrWaitForPllLock;
	अचिन्हित पूर्णांक numberOfControllers;
	/* Unused, क्रम future use. To indicate that first changed frame from
	 * state3 shouldn't result in psr_inactive, but rather to perक्रमm
	 * an स्वतःmatic single frame rfb_update.
	 */
	bool rfb_update_स्वतः_en;
	/* Number of frame beक्रमe entering अटल screen */
	अचिन्हित पूर्णांक समयhyst_frames;
	/* Partial frames beक्रमe entering अटल screen */
	अचिन्हित पूर्णांक hyst_lines;
	/* # of repeated AUX transaction attempts to make beक्रमe
	 * indicating failure to the driver
	 */
	अचिन्हित पूर्णांक aux_repeats;
	/* Controls hw blocks to घातer करोwn during PSR active state */
	जोड़ dmcu_psr_level psr_level;
	/* Controls additional delay after remote frame capture beक्रमe
	 * continuing घातerd own
	 */
	अचिन्हित पूर्णांक frame_delay;
	bool allow_smu_optimizations;
	bool allow_multi_disp_optimizations;
पूर्ण;

काष्ठा colorspace_transक्रमm अणु
	काष्ठा fixed31_32 matrix[12];
	bool enable_remap;
पूर्ण;

क्रमागत i2c_mot_mode अणु
	I2C_MOT_UNDEF,
	I2C_MOT_TRUE,
	I2C_MOT_FALSE
पूर्ण;

काष्ठा AsicStateEx अणु
	अचिन्हित पूर्णांक memoryClock;
	अचिन्हित पूर्णांक displayClock;
	अचिन्हित पूर्णांक engineClock;
	अचिन्हित पूर्णांक maxSupportedDppClock;
	अचिन्हित पूर्णांक dppClock;
	अचिन्हित पूर्णांक socClock;
	अचिन्हित पूर्णांक dcfClockDeepSleep;
	अचिन्हित पूर्णांक fClock;
	अचिन्हित पूर्णांक phyClock;
पूर्ण;


क्रमागत dc_घड़ी_प्रकारype अणु
	DC_CLOCK_TYPE_DISPCLK = 0,
	DC_CLOCK_TYPE_DPPCLK        = 1,
पूर्ण;

काष्ठा dc_घड़ी_config अणु
	uपूर्णांक32_t max_घड़ी_khz;
	uपूर्णांक32_t min_घड़ी_khz;
	uपूर्णांक32_t bw_requirequired_घड़ी_khz;
	uपूर्णांक32_t current_घड़ी_khz;/*current घड़ी in use*/
पूर्ण;

/* DSC DPCD capabilities */
जोड़ dsc_slice_caps1 अणु
	काष्ठा अणु
		uपूर्णांक8_t NUM_SLICES_1 : 1;
		uपूर्णांक8_t NUM_SLICES_2 : 1;
		uपूर्णांक8_t RESERVED : 1;
		uपूर्णांक8_t NUM_SLICES_4 : 1;
		uपूर्णांक8_t NUM_SLICES_6 : 1;
		uपूर्णांक8_t NUM_SLICES_8 : 1;
		uपूर्णांक8_t NUM_SLICES_10 : 1;
		uपूर्णांक8_t NUM_SLICES_12 : 1;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ dsc_slice_caps2 अणु
	काष्ठा अणु
		uपूर्णांक8_t NUM_SLICES_16 : 1;
		uपूर्णांक8_t NUM_SLICES_20 : 1;
		uपूर्णांक8_t NUM_SLICES_24 : 1;
		uपूर्णांक8_t RESERVED : 5;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ dsc_color_क्रमmats अणु
	काष्ठा अणु
		uपूर्णांक8_t RGB : 1;
		uपूर्णांक8_t YCBCR_444 : 1;
		uपूर्णांक8_t YCBCR_SIMPLE_422 : 1;
		uपूर्णांक8_t YCBCR_NATIVE_422 : 1;
		uपूर्णांक8_t YCBCR_NATIVE_420 : 1;
		uपूर्णांक8_t RESERVED : 3;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

जोड़ dsc_color_depth अणु
	काष्ठा अणु
		uपूर्णांक8_t RESERVED1 : 1;
		uपूर्णांक8_t COLOR_DEPTH_8_BPC : 1;
		uपूर्णांक8_t COLOR_DEPTH_10_BPC : 1;
		uपूर्णांक8_t COLOR_DEPTH_12_BPC : 1;
		uपूर्णांक8_t RESERVED2 : 3;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

काष्ठा dsc_dec_dpcd_caps अणु
	bool is_dsc_supported;
	uपूर्णांक8_t dsc_version;
	पूर्णांक32_t rc_buffer_size; /* DSC RC buffer block size in bytes */
	जोड़ dsc_slice_caps1 slice_caps1;
	जोड़ dsc_slice_caps2 slice_caps2;
	पूर्णांक32_t lb_bit_depth;
	bool is_block_pred_supported;
	पूर्णांक32_t edp_max_bits_per_pixel; /* Valid only in eDP */
	जोड़ dsc_color_क्रमmats color_क्रमmats;
	जोड़ dsc_color_depth color_depth;
	पूर्णांक32_t throughput_mode_0_mps; /* In MPs */
	पूर्णांक32_t throughput_mode_1_mps; /* In MPs */
	पूर्णांक32_t max_slice_width;
	uपूर्णांक32_t bpp_increment_भाग; /* bpp increment भागisor, e.g. अगर 16, it's 1/16th of a bit */

	/* Extended DSC caps */
	uपूर्णांक32_t branch_overall_throughput_0_mps; /* In MPs */
	uपूर्णांक32_t branch_overall_throughput_1_mps; /* In MPs */
	uपूर्णांक32_t branch_max_line_width;
पूर्ण;

काष्ठा dc_golden_table अणु
	uपूर्णांक16_t dc_golden_table_ver;
	uपूर्णांक32_t aux_dphy_rx_control0_val;
	uपूर्णांक32_t aux_dphy_tx_control_val;
	uपूर्णांक32_t aux_dphy_rx_control1_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_0_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_1_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_2_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_3_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_4_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_5_val;
पूर्ण;

क्रमागत dc_gpu_mem_alloc_type अणु
	DC_MEM_ALLOC_TYPE_GART,
	DC_MEM_ALLOC_TYPE_FRAME_BUFFER,
	DC_MEM_ALLOC_TYPE_INVISIBLE_FRAME_BUFFER,
	DC_MEM_ALLOC_TYPE_AGP
पूर्ण;

क्रमागत dc_psr_version अणु
	DC_PSR_VERSION_1			= 0,
	DC_PSR_VERSION_UNSUPPORTED		= 0xFFFFFFFF,
पूर्ण;

/* Possible values of display_endpoपूर्णांक_id.endpoपूर्णांक */
क्रमागत display_endpoपूर्णांक_type अणु
	DISPLAY_ENDPOINT_PHY = 0, /* Physical connector. */
	DISPLAY_ENDPOINT_UNKNOWN = -1
पूर्ण;

/* Extends graphics_object_id with an additional member 'ep_type' क्रम
 * distinguishing between physical endpoपूर्णांकs (with entries in BIOS connector table) and
 * logical endpoपूर्णांकs.
 */
काष्ठा display_endpoपूर्णांक_id अणु
	काष्ठा graphics_object_id link_id;
	क्रमागत display_endpoपूर्णांक_type ep_type;
पूर्ण;

#पूर्ण_अगर /* DC_TYPES_H_ */
