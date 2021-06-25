<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Author: Hugues Fruchet <hugues.fruchet@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित DELTA_MJPEG_FW_H
#घोषणा DELTA_MJPEG_FW_H

/*
 * काष्ठा jpeg_decoded_buffer_address_t
 *
 * defines the addresses where the decoded picture/additional
 * info related to the block काष्ठाures will be stored
 *
 * @display_luma_p:		address of the luma buffer
 * @display_chroma_p:		address of the chroma buffer
 */
काष्ठा jpeg_decoded_buffer_address_t अणु
	u32 luma_p;
	u32 chroma_p;
पूर्ण;

/*
 * काष्ठा jpeg_display_buffer_address_t
 *
 * defines the addresses (used by the Display Reस्थिरruction block)
 * where the pictures to be displayed will be stored
 *
 * @काष्ठा_size:		size of the काष्ठाure in bytes
 * @display_luma_p:		address of the luma buffer
 * @display_chroma_p:		address of the chroma buffer
 * @display_decimated_luma_p:	address of the decimated luma buffer
 * @display_decimated_chroma_p:	address of the decimated chroma buffer
 */
काष्ठा jpeg_display_buffer_address_t अणु
	u32 काष्ठा_size;
	u32 display_luma_p;
	u32 display_chroma_p;
	u32 display_decimated_luma_p;
	u32 display_decimated_chroma_p;
पूर्ण;

/*
 * used क्रम enabling मुख्य/aux outमाला_दो क्रम both display &
 * reference reस्थिरruction blocks
 */
क्रमागत jpeg_rcn_ref_disp_enable_t अणु
	/* enable decimated (क्रम display) reस्थिरruction */
	JPEG_DISP_AUX_EN = 0x00000010,
	/* enable मुख्य (क्रम display) reस्थिरruction */
	JPEG_DISP_MAIN_EN = 0x00000020,
	/* enable both मुख्य & decimated (क्रम display) reस्थिरruction */
	JPEG_DISP_AUX_MAIN_EN = 0x00000030,
	/* enable only reference output(ex. क्रम trick modes) */
	JPEG_REF_MAIN_EN = 0x00000100,
	/*
	 * enable reference output with decimated
	 * (क्रम display) reस्थिरruction
	 */
	JPEG_REF_MAIN_DISP_AUX_EN = 0x00000110,
	/*
	 * enable reference output with मुख्य
	 * (क्रम display) reस्थिरruction
	 */
	JPEG_REF_MAIN_DISP_MAIN_EN = 0x00000120,
	/*
	 * enable reference output with मुख्य & decimated
	 * (क्रम display) reस्थिरruction
	 */
	JPEG_REF_MAIN_DISP_MAIN_AUX_EN = 0x00000130
पूर्ण;

/* identअगरies the horizontal decimation factor */
क्रमागत jpeg_horizontal_deci_factor_t अणु
	/* no resize */
	JPEG_HDEC_1 = 0x00000000,
	/* Advanced H/2 resize using improved 8-tap filters */
	JPEG_HDEC_ADVANCED_2 = 0x00000101,
	/* Advanced H/4 resize using improved 8-tap filters */
	JPEG_HDEC_ADVANCED_4 = 0x00000102
पूर्ण;

/* identअगरies the vertical decimation factor */
क्रमागत jpeg_vertical_deci_factor_t अणु
	/* no resize */
	JPEG_VDEC_1 = 0x00000000,
	/* V/2 , progressive resize */
	JPEG_VDEC_ADVANCED_2_PROG = 0x00000204,
	/* V/2 , पूर्णांकerlaced resize */
	JPEG_VDEC_ADVANCED_2_INT = 0x000000208
पूर्ण;

/* status of the decoding process */
क्रमागत jpeg_decoding_error_t अणु
	JPEG_DECODER_NO_ERROR = 0,
	JPEG_DECODER_UNDEFINED_HUFF_TABLE = 1,
	JPEG_DECODER_UNSUPPORTED_MARKER = 2,
	JPEG_DECODER_UNABLE_ALLOCATE_MEMORY = 3,
	JPEG_DECODER_NON_SUPPORTED_SAMP_FACTORS = 4,
	JPEG_DECODER_BAD_PARAMETER = 5,
	JPEG_DECODER_DECODE_ERROR = 6,
	JPEG_DECODER_BAD_RESTART_MARKER = 7,
	JPEG_DECODER_UNSUPPORTED_COLORSPACE = 8,
	JPEG_DECODER_BAD_SOS_SPECTRAL = 9,
	JPEG_DECODER_BAD_SOS_SUCCESSIVE = 10,
	JPEG_DECODER_BAD_HEADER_LENGTH = 11,
	JPEG_DECODER_BAD_COUNT_VALUE = 12,
	JPEG_DECODER_BAD_DHT_MARKER = 13,
	JPEG_DECODER_BAD_INDEX_VALUE = 14,
	JPEG_DECODER_BAD_NUMBER_HUFFMAN_TABLES = 15,
	JPEG_DECODER_BAD_QUANT_TABLE_LENGTH = 16,
	JPEG_DECODER_BAD_NUMBER_QUANT_TABLES = 17,
	JPEG_DECODER_BAD_COMPONENT_COUNT = 18,
	JPEG_DECODER_DIVIDE_BY_ZERO_ERROR = 19,
	JPEG_DECODER_NOT_JPG_IMAGE = 20,
	JPEG_DECODER_UNSUPPORTED_ROTATION_ANGLE = 21,
	JPEG_DECODER_UNSUPPORTED_SCALING = 22,
	JPEG_DECODER_INSUFFICIENT_OUTPUTBUFFER_SIZE = 23,
	JPEG_DECODER_BAD_HWCFG_GP_VERSION_VALUE = 24,
	JPEG_DECODER_BAD_VALUE_FROM_RED = 25,
	JPEG_DECODER_BAD_SUBREGION_PARAMETERS = 26,
	JPEG_DECODER_PROGRESSIVE_DECODE_NOT_SUPPORTED = 27,
	JPEG_DECODER_ERROR_TASK_TIMEOUT = 28,
	JPEG_DECODER_ERROR_FEATURE_NOT_SUPPORTED = 29
पूर्ण;

/* identअगरies the decoding mode */
क्रमागत jpeg_decoding_mode_t अणु
	JPEG_NORMAL_DECODE = 0,
पूर्ण;

क्रमागत jpeg_additional_flags_t अणु
	JPEG_ADDITIONAL_FLAG_NONE = 0,
	/* request firmware to वापस values of the CEH रेजिस्टरs */
	JPEG_ADDITIONAL_FLAG_CEH = 1,
	/* output storage of auxiliary reस्थिरruction in Raster क्रमmat. */
	JPEG_ADDITIONAL_FLAG_RASTER = 64,
	/* output storage of auxiliary reस्थिरruction in 420MB क्रमmat. */
	JPEG_ADDITIONAL_FLAG_420MB = 128
पूर्ण;

/*
 * काष्ठा jpeg_video_decode_init_params_t - initialization command parameters
 *
 * @circular_buffer_begin_addr_p:	start address of fw circular buffer
 * @circular_buffer_end_addr_p:		end address of fw circular buffer
 */
काष्ठा jpeg_video_decode_init_params_t अणु
	u32 circular_buffer_begin_addr_p;
	u32 circular_buffer_end_addr_p;
	u32 reserved;
पूर्ण;

/*
 * काष्ठा jpeg_decode_params_t - decode command parameters
 *
 * @picture_start_addr_p:	start address of jpeg picture
 * @picture_end_addr_p:		end address of jpeg picture
 * @decoded_buffer_addr:	decoded picture buffer
 * @display_buffer_addr:	display picture buffer
 * @मुख्य_aux_enable:		enable मुख्य and/or aux outमाला_दो
 * @horizontal_decimation_factor:horizontal decimation factor
 * @vertical_decimation_factor:	vertical decimation factor
 * @xvalue0:			the x(0) coordinate क्रम subregion decoding
 * @xvalue1:			the x(1) coordinate क्रम subregion decoding
 * @yvalue0:			the y(0) coordinate क्रम subregion decoding
 * @yvalue1:			the y(1) coordinate क्रम subregion decoding
 * @decoding_mode:		decoding mode
 * @additional_flags:		additional flags
 * @field_flag:			determines frame/field scan
 * @is_jpeg_image:		1 = still jpeg, 0 = motion jpeg
 */
काष्ठा jpeg_decode_params_t अणु
	u32 picture_start_addr_p;
	u32 picture_end_addr_p;
	काष्ठा jpeg_decoded_buffer_address_t decoded_buffer_addr;
	काष्ठा jpeg_display_buffer_address_t display_buffer_addr;
	क्रमागत jpeg_rcn_ref_disp_enable_t मुख्य_aux_enable;
	क्रमागत jpeg_horizontal_deci_factor_t horizontal_decimation_factor;
	क्रमागत jpeg_vertical_deci_factor_t vertical_decimation_factor;
	u32 xvalue0;
	u32 xvalue1;
	u32 yvalue0;
	u32 yvalue1;
	क्रमागत jpeg_decoding_mode_t decoding_mode;
	u32 additional_flags;
	u32 field_flag;
	u32 reserved;
	u32 is_jpeg_image;
पूर्ण;

/*
 * काष्ठा jpeg_decode_वापस_params_t
 *
 * status वापसed by firmware after decoding
 *
 * @decode_समय_in_us:	decoding समय in microseconds
 * @pm_cycles:		profiling inक्रमmation
 * @pm_dmiss:		profiling inक्रमmation
 * @pm_imiss:		profiling inक्रमmation
 * @pm_bundles:		profiling inक्रमmation
 * @pm_pft:		profiling inक्रमmation
 * @error_code:		status of the decoding process
 * @ceh_रेजिस्टरs:	array where values of the Contrast Enhancement
 *			Histogram (CEH) रेजिस्टरs will be stored.
 *			ceh_रेजिस्टरs[0] correspond to रेजिस्टर MBE_CEH_0_7,
 *			ceh_रेजिस्टरs[1] correspond to रेजिस्टर MBE_CEH_8_15
 *			ceh_रेजिस्टरs[2] correspond to रेजिस्टर MBE_CEH_16_23
 *			Note that elements of this array will be updated only
 *			अगर additional_flags has JPEG_ADDITIONAL_FLAG_CEH set.
 */
काष्ठा jpeg_decode_वापस_params_t अणु
	/* profiling info */
	u32 decode_समय_in_us;
	u32 pm_cycles;
	u32 pm_dmiss;
	u32 pm_imiss;
	u32 pm_bundles;
	u32 pm_pft;
	क्रमागत jpeg_decoding_error_t error_code;
	u32 ceh_रेजिस्टरs[32];
पूर्ण;

#पूर्ण_अगर /* DELTA_MJPEG_FW_H */
