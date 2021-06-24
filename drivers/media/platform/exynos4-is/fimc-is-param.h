<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2011 - 2013 Samsung Electronics Co., Ltd.
 *
 * Authors: Younghwan Joo <yhwan.joo@samsung.com>
 *	    Sylwester Nawrocki <s.nawrocki@samsung.com>
 */
#अगर_अघोषित FIMC_IS_PARAM_H_
#घोषणा FIMC_IS_PARAM_H_

#समावेश <linux/compiler.h>

#घोषणा FIMC_IS_CONFIG_TIMEOUT		3000 /* ms */
#घोषणा IS_DEFAULT_WIDTH		1280
#घोषणा IS_DEFAULT_HEIGHT		720

#घोषणा DEFAULT_PREVIEW_STILL_WIDTH	IS_DEFAULT_WIDTH
#घोषणा DEFAULT_PREVIEW_STILL_HEIGHT	IS_DEFAULT_HEIGHT
#घोषणा DEFAULT_CAPTURE_STILL_WIDTH	IS_DEFAULT_WIDTH
#घोषणा DEFAULT_CAPTURE_STILL_HEIGHT	IS_DEFAULT_HEIGHT
#घोषणा DEFAULT_PREVIEW_VIDEO_WIDTH	IS_DEFAULT_WIDTH
#घोषणा DEFAULT_PREVIEW_VIDEO_HEIGHT	IS_DEFAULT_HEIGHT
#घोषणा DEFAULT_CAPTURE_VIDEO_WIDTH	IS_DEFAULT_WIDTH
#घोषणा DEFAULT_CAPTURE_VIDEO_HEIGHT	IS_DEFAULT_HEIGHT

#घोषणा DEFAULT_PREVIEW_STILL_FRAMERATE	30
#घोषणा DEFAULT_CAPTURE_STILL_FRAMERATE	15
#घोषणा DEFAULT_PREVIEW_VIDEO_FRAMERATE	30
#घोषणा DEFAULT_CAPTURE_VIDEO_FRAMERATE	30

#घोषणा FIMC_IS_REGION_VER		124 /* IS REGION VERSION 1.24 */
#घोषणा FIMC_IS_PARAM_SIZE		(FIMC_IS_REGION_SIZE + 1)
#घोषणा FIMC_IS_MAGIC_NUMBER		0x01020304
#घोषणा FIMC_IS_PARAM_MAX_SIZE		64 /* in bytes */
#घोषणा FIMC_IS_PARAM_MAX_ENTRIES	(FIMC_IS_PARAM_MAX_SIZE / 4)

/* The parameter biपंचांगask bit definitions. */
क्रमागत is_param_bit अणु
	PARAM_GLOBAL_SHOTMODE,
	PARAM_SENSOR_CONTROL,
	PARAM_SENSOR_OTF_OUTPUT,
	PARAM_SENSOR_FRAME_RATE,
	PARAM_BUFFER_CONTROL,
	PARAM_BUFFER_OTF_INPUT,
	PARAM_BUFFER_OTF_OUTPUT,
	PARAM_ISP_CONTROL,
	PARAM_ISP_OTF_INPUT,
	PARAM_ISP_DMA1_INPUT,
	/* 10 */
	PARAM_ISP_DMA2_INPUT,
	PARAM_ISP_AA,
	PARAM_ISP_FLASH,
	PARAM_ISP_AWB,
	PARAM_ISP_IMAGE_EFFECT,
	PARAM_ISP_ISO,
	PARAM_ISP_ADJUST,
	PARAM_ISP_METERING,
	PARAM_ISP_AFC,
	PARAM_ISP_OTF_OUTPUT,
	/* 20 */
	PARAM_ISP_DMA1_OUTPUT,
	PARAM_ISP_DMA2_OUTPUT,
	PARAM_DRC_CONTROL,
	PARAM_DRC_OTF_INPUT,
	PARAM_DRC_DMA_INPUT,
	PARAM_DRC_OTF_OUTPUT,
	PARAM_SCALERC_CONTROL,
	PARAM_SCALERC_OTF_INPUT,
	PARAM_SCALERC_IMAGE_EFFECT,
	PARAM_SCALERC_INPUT_CROP,
	/* 30 */
	PARAM_SCALERC_OUTPUT_CROP,
	PARAM_SCALERC_OTF_OUTPUT,
	PARAM_SCALERC_DMA_OUTPUT,
	PARAM_ODC_CONTROL,
	PARAM_ODC_OTF_INPUT,
	PARAM_ODC_OTF_OUTPUT,
	PARAM_DIS_CONTROL,
	PARAM_DIS_OTF_INPUT,
	PARAM_DIS_OTF_OUTPUT,
	PARAM_TDNR_CONTROL,
	/* 40 */
	PARAM_TDNR_OTF_INPUT,
	PARAM_TDNR_1ST_FRAME,
	PARAM_TDNR_OTF_OUTPUT,
	PARAM_TDNR_DMA_OUTPUT,
	PARAM_SCALERP_CONTROL,
	PARAM_SCALERP_OTF_INPUT,
	PARAM_SCALERP_IMAGE_EFFECT,
	PARAM_SCALERP_INPUT_CROP,
	PARAM_SCALERP_OUTPUT_CROP,
	PARAM_SCALERP_ROTATION,
	/* 50 */
	PARAM_SCALERP_FLIP,
	PARAM_SCALERP_OTF_OUTPUT,
	PARAM_SCALERP_DMA_OUTPUT,
	PARAM_FD_CONTROL,
	PARAM_FD_OTF_INPUT,
	PARAM_FD_DMA_INPUT,
	PARAM_FD_CONFIG,
पूर्ण;

/* Interrupt map */
#घोषणा	FIMC_IS_INT_GENERAL			0
#घोषणा	FIMC_IS_INT_FRAME_DONE_ISP		1

/* Input */

#घोषणा CONTROL_COMMAND_STOP			0
#घोषणा CONTROL_COMMAND_START			1

#घोषणा CONTROL_BYPASS_DISABLE			0
#घोषणा CONTROL_BYPASS_ENABLE			1

#घोषणा CONTROL_ERROR_NONE			0

/* OTF (On-The-Fly) input पूर्णांकerface commands */
#घोषणा OTF_INPUT_COMMAND_DISABLE		0
#घोषणा OTF_INPUT_COMMAND_ENABLE		1

/* OTF input पूर्णांकerface color क्रमmats */
क्रमागत oft_input_fmt अणु
	OTF_INPUT_FORMAT_BAYER			= 0, /* 1 channel */
	OTF_INPUT_FORMAT_YUV444			= 1, /* 3 channels */
	OTF_INPUT_FORMAT_YUV422			= 2, /* 3 channels */
	OTF_INPUT_FORMAT_YUV420			= 3, /* 3 channels */
	OTF_INPUT_FORMAT_STRGEN_COLORBAR_BAYER	= 10,
	OTF_INPUT_FORMAT_BAYER_DMA		= 11,
पूर्ण;

#घोषणा OTF_INPUT_ORDER_BAYER_GR_BG		0

/* OTF input error codes */
#घोषणा OTF_INPUT_ERROR_NONE			0 /* Input setting is करोne */

/* DMA input commands */
#घोषणा DMA_INPUT_COMMAND_DISABLE		0
#घोषणा DMA_INPUT_COMMAND_ENABLE		1

/* DMA input color क्रमmats */
क्रमागत dma_input_fmt अणु
	DMA_INPUT_FORMAT_BAYER			= 0,
	DMA_INPUT_FORMAT_YUV444			= 1,
	DMA_INPUT_FORMAT_YUV422			= 2,
	DMA_INPUT_FORMAT_YUV420			= 3,
पूर्ण;

क्रमागत dma_input_order अणु
	/* (क्रम DMA_INPUT_PLANE_3) */
	DMA_INPUT_ORDER_NO	= 0,
	/* (only valid at DMA_INPUT_PLANE_2) */
	DMA_INPUT_ORDER_CBCR	= 1,
	/* (only valid at DMA_INPUT_PLANE_2) */
	DMA_INPUT_ORDER_CRCB	= 2,
	/* (only valid at DMA_INPUT_PLANE_1 & DMA_INPUT_FORMAT_YUV444) */
	DMA_INPUT_ORDER_YCBCR	= 3,
	/* (only valid at DMA_INPUT_FORMAT_YUV422 & DMA_INPUT_PLANE_1) */
	DMA_INPUT_ORDER_YYCBCR	= 4,
	/* (only valid at DMA_INPUT_FORMAT_YUV422 & DMA_INPUT_PLANE_1) */
	DMA_INPUT_ORDER_YCBYCR	= 5,
	/* (only valid at DMA_INPUT_FORMAT_YUV422 & DMA_INPUT_PLANE_1) */
	DMA_INPUT_ORDER_YCRYCB	= 6,
	/* (only valid at DMA_INPUT_FORMAT_YUV422 & DMA_INPUT_PLANE_1) */
	DMA_INPUT_ORDER_CBYCRY	= 7,
	/* (only valid at DMA_INPUT_FORMAT_YUV422 & DMA_INPUT_PLANE_1) */
	DMA_INPUT_ORDER_CRYCBY	= 8,
	/* (only valid at DMA_INPUT_FORMAT_BAYER) */
	DMA_INPUT_ORDER_GR_BG	= 9
पूर्ण;

#घोषणा DMA_INPUT_ERROR_NONE			0 /* DMA input setting
						     is करोne */
/*
 * Data output parameter definitions
 */
#घोषणा OTF_OUTPUT_CROP_DISABLE			0
#घोषणा OTF_OUTPUT_CROP_ENABLE			1

#घोषणा OTF_OUTPUT_COMMAND_DISABLE		0
#घोषणा OTF_OUTPUT_COMMAND_ENABLE		1

क्रमागत otf_output_fmt अणु
	OTF_OUTPUT_FORMAT_YUV444		= 1,
	OTF_OUTPUT_FORMAT_YUV422		= 2,
	OTF_OUTPUT_FORMAT_YUV420		= 3,
	OTF_OUTPUT_FORMAT_RGB			= 4,
पूर्ण;

#घोषणा OTF_OUTPUT_ORDER_BAYER_GR_BG		0

#घोषणा OTF_OUTPUT_ERROR_NONE			0 /* Output Setting is करोne */

#घोषणा DMA_OUTPUT_COMMAND_DISABLE		0
#घोषणा DMA_OUTPUT_COMMAND_ENABLE		1

क्रमागत dma_output_fmt अणु
	DMA_OUTPUT_FORMAT_BAYER			= 0,
	DMA_OUTPUT_FORMAT_YUV444		= 1,
	DMA_OUTPUT_FORMAT_YUV422		= 2,
	DMA_OUTPUT_FORMAT_YUV420		= 3,
	DMA_OUTPUT_FORMAT_RGB			= 4,
पूर्ण;

क्रमागत dma_output_order अणु
	DMA_OUTPUT_ORDER_NO		= 0,
	/* क्रम DMA_OUTPUT_PLANE_3 */
	DMA_OUTPUT_ORDER_CBCR		= 1,
	/* only valid at DMA_INPUT_PLANE_2) */
	DMA_OUTPUT_ORDER_CRCB		= 2,
	/* only valid at DMA_OUTPUT_PLANE_2) */
	DMA_OUTPUT_ORDER_YYCBCR		= 3,
	/* only valid at DMA_OUTPUT_FORMAT_YUV422 & DMA_OUTPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_YCBYCR		= 4,
	/* only valid at DMA_OUTPUT_FORMAT_YUV422 & DMA_OUTPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_YCRYCB		= 5,
	/* only valid at DMA_OUTPUT_FORMAT_YUV422 & DMA_OUTPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_CBYCRY		= 6,
	/* only valid at DMA_OUTPUT_FORMAT_YUV422 & DMA_OUTPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_CRYCBY		= 7,
	/* only valid at DMA_OUTPUT_FORMAT_YUV422 & DMA_OUTPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_YCBCR		= 8,
	/* only valid at DMA_OUTPUT_FORMAT_YUV444 & DMA_OUPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_CRYCB		= 9,
	/* only valid at DMA_OUTPUT_FORMAT_YUV444 & DMA_OUPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_CRCBY		= 10,
	/* only valid at DMA_OUTPUT_FORMAT_YUV444 & DMA_OUPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_CBYCR		= 11,
	/* only valid at DMA_OUTPUT_FORMAT_YUV444 & DMA_OUPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_YCRCB		= 12,
	/* only valid at DMA_OUTPUT_FORMAT_YUV444 & DMA_OUPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_CBCRY		= 13,
	/* only valid at DMA_OUTPUT_FORMAT_YUV444 & DMA_OUPUT_PLANE_1 */
	DMA_OUTPUT_ORDER_BGR		= 14,
	/* only valid at DMA_OUTPUT_FORMAT_RGB */
	DMA_OUTPUT_ORDER_GB_BG		= 15
	/* only valid at DMA_OUTPUT_FORMAT_BAYER */
पूर्ण;

/* क्रमागत dma_output_notअगरy_dma_करोne */
#घोषणा DMA_OUTPUT_NOTIFY_DMA_DONE_DISABLE	0
#घोषणा DMA_OUTPUT_NOTIFY_DMA_DONE_ENABLE	1

/* DMA output error codes */
#घोषणा DMA_OUTPUT_ERROR_NONE			0 /* DMA output setting
						     is करोne */

/* ----------------------  Global  ----------------------------------- */
#घोषणा GLOBAL_SHOTMODE_ERROR_NONE		0 /* shot-mode setting
						     is करोne */
/* 3A lock commands */
#घोषणा ISP_AA_COMMAND_START			0
#घोषणा ISP_AA_COMMAND_STOP			1

/* 3A lock target */
#घोषणा ISP_AA_TARGET_AF			1
#घोषणा ISP_AA_TARGET_AE			2
#घोषणा ISP_AA_TARGET_AWB			4

क्रमागत isp_af_mode अणु
	ISP_AF_MODE_MANUAL			= 0,
	ISP_AF_MODE_SINGLE			= 1,
	ISP_AF_MODE_CONTINUOUS			= 2,
	ISP_AF_MODE_TOUCH			= 3,
	ISP_AF_MODE_SLEEP			= 4,
	ISP_AF_MODE_INIT			= 5,
	ISP_AF_MODE_SET_CENTER_WINDOW		= 6,
	ISP_AF_MODE_SET_TOUCH_WINDOW		= 7
पूर्ण;

/* Face AF commands */
#घोषणा ISP_AF_FACE_DISABLE			0
#घोषणा ISP_AF_FACE_ENABLE			1

/* AF range */
#घोषणा ISP_AF_RANGE_NORMAL			0
#घोषणा ISP_AF_RANGE_MACRO			1

/* AF sleep */
#घोषणा ISP_AF_SLEEP_OFF			0
#घोषणा ISP_AF_SLEEP_ON				1

/* Continuous AF commands */
#घोषणा ISP_AF_CONTINUOUS_DISABLE		0
#घोषणा ISP_AF_CONTINUOUS_ENABLE		1

/* ISP AF error codes */
#घोषणा ISP_AF_ERROR_NONE			0 /* AF mode change is करोne */
#घोषणा ISP_AF_ERROR_NONE_LOCK_DONE		1 /* AF lock is करोne */

/* Flash commands */
#घोषणा ISP_FLASH_COMMAND_DISABLE		0
#घोषणा ISP_FLASH_COMMAND_MANUAL_ON		1 /* (क्रमced flash) */
#घोषणा ISP_FLASH_COMMAND_AUTO			2
#घोषणा ISP_FLASH_COMMAND_TORCH			3 /* 3 sec */

/* Flash red-eye commands */
#घोषणा ISP_FLASH_REDEYE_DISABLE		0
#घोषणा ISP_FLASH_REDEYE_ENABLE			1

/* Flash error codes */
#घोषणा ISP_FLASH_ERROR_NONE			0 /* Flash setting is करोne */

/* --------------------------  AWB  ------------------------------------ */
क्रमागत isp_awb_command अणु
	ISP_AWB_COMMAND_AUTO			= 0,
	ISP_AWB_COMMAND_ILLUMINATION		= 1,
	ISP_AWB_COMMAND_MANUAL			= 2
पूर्ण;

क्रमागत isp_awb_illumination अणु
	ISP_AWB_ILLUMINATION_DAYLIGHT		= 0,
	ISP_AWB_ILLUMINATION_CLOUDY		= 1,
	ISP_AWB_ILLUMINATION_TUNGSTEN		= 2,
	ISP_AWB_ILLUMINATION_FLUORESCENT	= 3
पूर्ण;

/* ISP AWN error codes */
#घोषणा ISP_AWB_ERROR_NONE			0 /* AWB setting is करोne */

/* --------------------------  Effect  ----------------------------------- */
क्रमागत isp_imageeffect_command अणु
	ISP_IMAGE_EFFECT_DISABLE		= 0,
	ISP_IMAGE_EFFECT_MONOCHROME		= 1,
	ISP_IMAGE_EFFECT_NEGATIVE_MONO		= 2,
	ISP_IMAGE_EFFECT_NEGATIVE_COLOR		= 3,
	ISP_IMAGE_EFFECT_SEPIA			= 4
पूर्ण;

/* Image effect error codes */
#घोषणा ISP_IMAGE_EFFECT_ERROR_NONE		0 /* Image effect setting
						     is करोne */
/* ISO commands */
#घोषणा ISP_ISO_COMMAND_AUTO			0
#घोषणा ISP_ISO_COMMAND_MANUAL			1

/* ISO error codes */
#घोषणा ISP_ISO_ERROR_NONE			0 /* ISO setting is करोne */

/* ISP adjust commands */
#घोषणा ISP_ADJUST_COMMAND_AUTO			(0 << 0)
#घोषणा ISP_ADJUST_COMMAND_MANUAL_CONTRAST	(1 << 0)
#घोषणा ISP_ADJUST_COMMAND_MANUAL_SATURATION	(1 << 1)
#घोषणा ISP_ADJUST_COMMAND_MANUAL_SHARPNESS	(1 << 2)
#घोषणा ISP_ADJUST_COMMAND_MANUAL_EXPOSURE	(1 << 3)
#घोषणा ISP_ADJUST_COMMAND_MANUAL_BRIGHTNESS	(1 << 4)
#घोषणा ISP_ADJUST_COMMAND_MANUAL_HUE		(1 << 5)
#घोषणा ISP_ADJUST_COMMAND_MANUAL_ALL		0x7f

/* ISP adjusपंचांगent error codes */
#घोषणा ISP_ADJUST_ERROR_NONE			0 /* Adjust setting is करोne */

/*
 *  Exposure metering
 */
क्रमागत isp_metering_command अणु
	ISP_METERING_COMMAND_AVERAGE	= 0,
	ISP_METERING_COMMAND_SPOT	= 1,
	ISP_METERING_COMMAND_MATRIX	= 2,
	ISP_METERING_COMMAND_CENTER	= 3
पूर्ण;

/* ISP metering error codes */
#घोषणा ISP_METERING_ERROR_NONE		0 /* Metering setting is करोne */

/*
 * AFC
 */
क्रमागत isp_afc_command अणु
	ISP_AFC_COMMAND_DISABLE		= 0,
	ISP_AFC_COMMAND_AUTO		= 1,
	ISP_AFC_COMMAND_MANUAL		= 2,
पूर्ण;

#घोषणा ISP_AFC_MANUAL_50HZ		50
#घोषणा ISP_AFC_MANUAL_60HZ		60

/* ------------------------  SCENE MODE--------------------------------- */
क्रमागत isp_scene_mode अणु
	ISP_SCENE_NONE			= 0,
	ISP_SCENE_PORTRAIT		= 1,
	ISP_SCENE_LANDSCAPE		= 2,
	ISP_SCENE_SPORTS		= 3,
	ISP_SCENE_PARTYINDOOR		= 4,
	ISP_SCENE_BEACHSNOW		= 5,
	ISP_SCENE_SUNSET		= 6,
	ISP_SCENE_DAWN			= 7,
	ISP_SCENE_FALL			= 8,
	ISP_SCENE_NIGHT			= 9,
	ISP_SCENE_AGAINSTLIGHTWLIGHT	= 10,
	ISP_SCENE_AGAINSTLIGHTWOLIGHT	= 11,
	ISP_SCENE_FIRE			= 12,
	ISP_SCENE_TEXT			= 13,
	ISP_SCENE_CANDLE		= 14
पूर्ण;

/* AFC error codes */
#घोषणा ISP_AFC_ERROR_NONE		0 /* AFC setting is करोne */

/* ----------------------------  FD  ------------------------------------- */
क्रमागत fd_config_command अणु
	FD_CONFIG_COMMAND_MAXIMUM_NUMBER	= 0x1,
	FD_CONFIG_COMMAND_ROLL_ANGLE		= 0x2,
	FD_CONFIG_COMMAND_YAW_ANGLE		= 0x4,
	FD_CONFIG_COMMAND_SMILE_MODE		= 0x8,
	FD_CONFIG_COMMAND_BLINK_MODE		= 0x10,
	FD_CONFIG_COMMAND_EYES_DETECT		= 0x20,
	FD_CONFIG_COMMAND_MOUTH_DETECT		= 0x40,
	FD_CONFIG_COMMAND_ORIENTATION		= 0x80,
	FD_CONFIG_COMMAND_ORIENTATION_VALUE	= 0x100
पूर्ण;

क्रमागत fd_config_roll_angle अणु
	FD_CONFIG_ROLL_ANGLE_BASIC		= 0,
	FD_CONFIG_ROLL_ANGLE_PRECISE_BASIC	= 1,
	FD_CONFIG_ROLL_ANGLE_SIDES		= 2,
	FD_CONFIG_ROLL_ANGLE_PRECISE_SIDES	= 3,
	FD_CONFIG_ROLL_ANGLE_FULL		= 4,
	FD_CONFIG_ROLL_ANGLE_PRECISE_FULL	= 5,
पूर्ण;

क्रमागत fd_config_yaw_angle अणु
	FD_CONFIG_YAW_ANGLE_0			= 0,
	FD_CONFIG_YAW_ANGLE_45			= 1,
	FD_CONFIG_YAW_ANGLE_90			= 2,
	FD_CONFIG_YAW_ANGLE_45_90		= 3,
पूर्ण;

/* Smile mode configuration */
#घोषणा FD_CONFIG_SMILE_MODE_DISABLE		0
#घोषणा FD_CONFIG_SMILE_MODE_ENABLE		1

/* Blink mode configuration */
#घोषणा FD_CONFIG_BLINK_MODE_DISABLE		0
#घोषणा FD_CONFIG_BLINK_MODE_ENABLE		1

/* Eyes detection configuration */
#घोषणा FD_CONFIG_EYES_DETECT_DISABLE		0
#घोषणा FD_CONFIG_EYES_DETECT_ENABLE		1

/* Mouth detection configuration */
#घोषणा FD_CONFIG_MOUTH_DETECT_DISABLE		0
#घोषणा FD_CONFIG_MOUTH_DETECT_ENABLE		1

#घोषणा FD_CONFIG_ORIENTATION_DISABLE		0
#घोषणा FD_CONFIG_ORIENTATION_ENABLE		1

काष्ठा param_control अणु
	u32 cmd;
	u32 bypass;
	u32 buffer_address;
	u32 buffer_size;
	u32 skip_frames; /* only valid at ISP */
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 6];
	u32 err;
पूर्ण;

काष्ठा param_otf_input अणु
	u32 cmd;
	u32 width;
	u32 height;
	u32 क्रमmat;
	u32 bitwidth;
	u32 order;
	u32 crop_offset_x;
	u32 crop_offset_y;
	u32 crop_width;
	u32 crop_height;
	u32 frameसमय_min;
	u32 frameसमय_max;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 13];
	u32 err;
पूर्ण;

काष्ठा param_dma_input अणु
	u32 cmd;
	u32 width;
	u32 height;
	u32 क्रमmat;
	u32 bitwidth;
	u32 plane;
	u32 order;
	u32 buffer_number;
	u32 buffer_address;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 10];
	u32 err;
पूर्ण;

काष्ठा param_otf_output अणु
	u32 cmd;
	u32 width;
	u32 height;
	u32 क्रमmat;
	u32 bitwidth;
	u32 order;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 7];
	u32 err;
पूर्ण;

काष्ठा param_dma_output अणु
	u32 cmd;
	u32 width;
	u32 height;
	u32 क्रमmat;
	u32 bitwidth;
	u32 plane;
	u32 order;
	u32 buffer_number;
	u32 buffer_address;
	u32 notअगरy_dma_करोne;
	u32 dma_out_mask;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 12];
	u32 err;
पूर्ण;

काष्ठा param_global_shoपंचांगode अणु
	u32 cmd;
	u32 skip_frames;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 3];
	u32 err;
पूर्ण;

काष्ठा param_sensor_framerate अणु
	u32 frame_rate;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 2];
	u32 err;
पूर्ण;

काष्ठा param_isp_aa अणु
	u32 cmd;
	u32 target;
	u32 mode;
	u32 scene;
	u32 sleep;
	u32 face;
	u32 touch_x;
	u32 touch_y;
	u32 manual_af_setting;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 10];
	u32 err;
पूर्ण;

काष्ठा param_isp_flash अणु
	u32 cmd;
	u32 redeye;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 3];
	u32 err;
पूर्ण;

काष्ठा param_isp_awb अणु
	u32 cmd;
	u32 illumination;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 3];
	u32 err;
पूर्ण;

काष्ठा param_isp_imageeffect अणु
	u32 cmd;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 2];
	u32 err;
पूर्ण;

काष्ठा param_isp_iso अणु
	u32 cmd;
	u32 value;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 3];
	u32 err;
पूर्ण;

काष्ठा param_isp_adjust अणु
	u32 cmd;
	s32 contrast;
	s32 saturation;
	s32 sharpness;
	s32 exposure;
	s32 brightness;
	s32 hue;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 8];
	u32 err;
पूर्ण;

काष्ठा param_isp_metering अणु
	u32 cmd;
	u32 win_pos_x;
	u32 win_pos_y;
	u32 win_width;
	u32 win_height;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 6];
	u32 err;
पूर्ण;

काष्ठा param_isp_afc अणु
	u32 cmd;
	u32 manual;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 3];
	u32 err;
पूर्ण;

काष्ठा param_scaler_imageeffect अणु
	u32 cmd;
	u32 arbitrary_cb;
	u32 arbitrary_cr;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 4];
	u32 err;
पूर्ण;

काष्ठा param_scaler_input_crop अणु
	u32 cmd;
	u32 crop_offset_x;
	u32 crop_offset_y;
	u32 crop_width;
	u32 crop_height;
	u32 in_width;
	u32 in_height;
	u32 out_width;
	u32 out_height;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 10];
	u32 err;
पूर्ण;

काष्ठा param_scaler_output_crop अणु
	u32 cmd;
	u32 crop_offset_x;
	u32 crop_offset_y;
	u32 crop_width;
	u32 crop_height;
	u32 out_क्रमmat;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 7];
	u32 err;
पूर्ण;

काष्ठा param_scaler_rotation अणु
	u32 cmd;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 2];
	u32 err;
पूर्ण;

काष्ठा param_scaler_flip अणु
	u32 cmd;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 2];
	u32 err;
पूर्ण;

काष्ठा param_3dnr_1stframe अणु
	u32 cmd;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 2];
	u32 err;
पूर्ण;

काष्ठा param_fd_config अणु
	u32 cmd;
	u32 max_number;
	u32 roll_angle;
	u32 yaw_angle;
	u32 smile_mode;
	u32 blink_mode;
	u32 eye_detect;
	u32 mouth_detect;
	u32 orientation;
	u32 orientation_value;
	u32 reserved[FIMC_IS_PARAM_MAX_ENTRIES - 11];
	u32 err;
पूर्ण;

काष्ठा global_param अणु
	काष्ठा param_global_shoपंचांगode	shoपंचांगode;
पूर्ण;

काष्ठा sensor_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_output		otf_output;
	काष्ठा param_sensor_framerate	frame_rate;
पूर्ण __packed;

काष्ठा buffer_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_input		otf_input;
	काष्ठा param_otf_output		otf_output;
पूर्ण __packed;

काष्ठा isp_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_input		otf_input;
	काष्ठा param_dma_input		dma1_input;
	काष्ठा param_dma_input		dma2_input;
	काष्ठा param_isp_aa		aa;
	काष्ठा param_isp_flash		flash;
	काष्ठा param_isp_awb		awb;
	काष्ठा param_isp_imageeffect	effect;
	काष्ठा param_isp_iso		iso;
	काष्ठा param_isp_adjust		adjust;
	काष्ठा param_isp_metering	metering;
	काष्ठा param_isp_afc		afc;
	काष्ठा param_otf_output		otf_output;
	काष्ठा param_dma_output		dma1_output;
	काष्ठा param_dma_output		dma2_output;
पूर्ण __packed;

काष्ठा drc_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_input		otf_input;
	काष्ठा param_dma_input		dma_input;
	काष्ठा param_otf_output		otf_output;
पूर्ण __packed;

काष्ठा scalerc_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_input		otf_input;
	काष्ठा param_scaler_imageeffect	effect;
	काष्ठा param_scaler_input_crop	input_crop;
	काष्ठा param_scaler_output_crop	output_crop;
	काष्ठा param_otf_output		otf_output;
	काष्ठा param_dma_output		dma_output;
पूर्ण __packed;

काष्ठा odc_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_input		otf_input;
	काष्ठा param_otf_output		otf_output;
पूर्ण __packed;

काष्ठा dis_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_output		otf_input;
	काष्ठा param_otf_output		otf_output;
पूर्ण __packed;

काष्ठा tdnr_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_input		otf_input;
	काष्ठा param_3dnr_1stframe	frame;
	काष्ठा param_otf_output		otf_output;
	काष्ठा param_dma_output		dma_output;
पूर्ण __packed;

काष्ठा scalerp_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_input		otf_input;
	काष्ठा param_scaler_imageeffect	effect;
	काष्ठा param_scaler_input_crop	input_crop;
	काष्ठा param_scaler_output_crop	output_crop;
	काष्ठा param_scaler_rotation	rotation;
	काष्ठा param_scaler_flip	flip;
	काष्ठा param_otf_output		otf_output;
	काष्ठा param_dma_output		dma_output;
पूर्ण __packed;

काष्ठा fd_param अणु
	काष्ठा param_control		control;
	काष्ठा param_otf_input		otf_input;
	काष्ठा param_dma_input		dma_input;
	काष्ठा param_fd_config		config;
पूर्ण __packed;

काष्ठा is_param_region अणु
	काष्ठा global_param		global;
	काष्ठा sensor_param		sensor;
	काष्ठा buffer_param		buf;
	काष्ठा isp_param		isp;
	काष्ठा drc_param		drc;
	काष्ठा scalerc_param		scalerc;
	काष्ठा odc_param		odc;
	काष्ठा dis_param		dis;
	काष्ठा tdnr_param		tdnr;
	काष्ठा scalerp_param		scalerp;
	काष्ठा fd_param			fd;
पूर्ण __packed;

#घोषणा NUMBER_OF_GAMMA_CURVE_POINTS	32

काष्ठा is_tune_sensor अणु
	u32 exposure;
	u32 analog_gain;
	u32 frame_rate;
	u32 actuator_position;
पूर्ण;

काष्ठा is_tune_gammacurve अणु
	u32 num_pts_x[NUMBER_OF_GAMMA_CURVE_POINTS];
	u32 num_pts_y_r[NUMBER_OF_GAMMA_CURVE_POINTS];
	u32 num_pts_y_g[NUMBER_OF_GAMMA_CURVE_POINTS];
	u32 num_pts_y_b[NUMBER_OF_GAMMA_CURVE_POINTS];
पूर्ण;

काष्ठा is_tune_isp अणु
	/* Brightness level: range 0...100, शेष 7. */
	u32 brightness_level;
	/* Contrast level: range -127...127, शेष 0. */
	s32 contrast_level;
	/* Saturation level: range -127...127, शेष 0. */
	s32 saturation_level;
	s32 gamma_level;
	काष्ठा is_tune_gammacurve gamma_curve[4];
	/* Hue: range -127...127, शेष 0. */
	s32 hue;
	/* Sharpness blur: range -127...127, शेष 0. */
	s32 sharpness_blur;
	/* Despeckle : range -127~127, शेष : 0 */
	s32 despeckle;
	/* Edge color supression: range -127...127, शेष 0. */
	s32 edge_color_supression;
	/* Noise reduction: range -127...127, शेष 0. */
	s32 noise_reduction;
	/* (32 * 4 + 9) * 4 = 548 bytes */
पूर्ण __packed;

काष्ठा is_tune_region अणु
	काष्ठा is_tune_sensor sensor;
	काष्ठा is_tune_isp isp;
पूर्ण __packed;

काष्ठा rational अणु
	u32 num;
	u32 den;
पूर्ण;

काष्ठा srational अणु
	s32 num;
	s32 den;
पूर्ण;

#घोषणा FLASH_FIRED_SHIFT			0
#घोषणा FLASH_NOT_FIRED				0
#घोषणा FLASH_FIRED				1

#घोषणा FLASH_STROBE_SHIFT			1
#घोषणा FLASH_STROBE_NO_DETECTION		0
#घोषणा FLASH_STROBE_RESERVED			1
#घोषणा FLASH_STROBE_RETURN_LIGHT_NOT_DETECTED	2
#घोषणा FLASH_STROBE_RETURN_LIGHT_DETECTED	3

#घोषणा FLASH_MODE_SHIFT			3
#घोषणा FLASH_MODE_UNKNOWN			0
#घोषणा FLASH_MODE_COMPULSORY_FLASH_FIRING	1
#घोषणा FLASH_MODE_COMPULSORY_FLASH_SUPPRESSION	2
#घोषणा FLASH_MODE_AUTO_MODE			3

#घोषणा FLASH_FUNCTION_SHIFT			5
#घोषणा FLASH_FUNCTION_PRESENT			0
#घोषणा FLASH_FUNCTION_NONE			1

#घोषणा FLASH_RED_EYE_SHIFT			6
#घोषणा FLASH_RED_EYE_DISABLED			0
#घोषणा FLASH_RED_EYE_SUPPORTED			1

क्रमागत apex_aperture_value अणु
	F1_0	= 0,
	F1_4	= 1,
	F2_0	= 2,
	F2_8	= 3,
	F4_0	= 4,
	F5_6	= 5,
	F8_9	= 6,
	F11_0	= 7,
	F16_0	= 8,
	F22_0	= 9,
	F32_0	= 10,
पूर्ण;

काष्ठा exअगर_attribute अणु
	काष्ठा rational exposure_समय;
	काष्ठा srational shutter_speed;
	u32 iso_speed_rating;
	u32 flash;
	काष्ठा srational brightness;
पूर्ण __packed;

काष्ठा is_frame_header अणु
	u32 valid;
	u32 bad_mark;
	u32 captured;
	u32 frame_number;
	काष्ठा exअगर_attribute exअगर;
पूर्ण __packed;

काष्ठा is_fd_rect अणु
	u32 offset_x;
	u32 offset_y;
	u32 width;
	u32 height;
पूर्ण;

काष्ठा is_face_marker अणु
	u32 frame_number;
	काष्ठा is_fd_rect face;
	काष्ठा is_fd_rect left_eye;
	काष्ठा is_fd_rect right_eye;
	काष्ठा is_fd_rect mouth;
	u32 roll_angle;
	u32 yaw_angle;
	u32 confidence;
	s32 smile_level;
	s32 blink_level;
पूर्ण __packed;

#घोषणा MAX_FRAME_COUNT				8
#घोषणा MAX_FRAME_COUNT_PREVIEW			4
#घोषणा MAX_FRAME_COUNT_CAPTURE			1
#घोषणा MAX_FACE_COUNT				16
#घोषणा MAX_SHARED_COUNT			500

काष्ठा is_region अणु
	काष्ठा is_param_region parameter;
	काष्ठा is_tune_region tune;
	काष्ठा is_frame_header header[MAX_FRAME_COUNT];
	काष्ठा is_face_marker face[MAX_FACE_COUNT];
	u32 shared[MAX_SHARED_COUNT];
पूर्ण __packed;

/* Offset to the ISP DMA2 output buffer address array. */
#घोषणा DMA2_OUTPUT_ADDR_ARRAY_OFFS \
	(दुरत्व(काष्ठा is_region, shared) + 32 * माप(u32))

काष्ठा is_debug_frame_descriptor अणु
	u32 sensor_frame_समय;
	u32 sensor_exposure_समय;
	s32 sensor_analog_gain;
	/* monitor क्रम AA */
	u32 req_lei;

	u32 next_next_lei_exp;
	u32 next_next_lei_a_gain;
	u32 next_next_lei_d_gain;
	u32 next_next_lei_statlei;
	u32 next_next_lei_lei;

	u32 dummy0;
पूर्ण;

#घोषणा MAX_FRAMEDESCRIPTOR_CONTEXT_NUM	(30*20)	/* 600 frames */
#घोषणा MAX_VERSION_DISPLAY_BUF	32

काष्ठा is_share_region अणु
	u32 frame_समय;
	u32 exposure_समय;
	s32 analog_gain;

	u32 r_gain;
	u32 g_gain;
	u32 b_gain;

	u32 af_position;
	u32 af_status;
	/* 0 : SIRC_ISP_CAMERA_AUTOFOCUSMESSAGE_NOMESSAGE */
	/* 1 : SIRC_ISP_CAMERA_AUTOFOCUSMESSAGE_REACHED */
	/* 2 : SIRC_ISP_CAMERA_AUTOFOCUSMESSAGE_UNABLETOREACH */
	/* 3 : SIRC_ISP_CAMERA_AUTOFOCUSMESSAGE_LOST */
	/* शेष : unknown */
	u32 af_scene_type;

	u32 frame_descp_onoff_control;
	u32 frame_descp_update_करोne;
	u32 frame_descp_idx;
	u32 frame_descp_max_idx;
	काष्ठा is_debug_frame_descriptor
		dbg_frame_descp_ctx[MAX_FRAMEDESCRIPTOR_CONTEXT_NUM];

	u32 chip_id;
	u32 chip_rev_no;
	u8 isp_fw_ver_no[MAX_VERSION_DISPLAY_BUF];
	u8 isp_fw_ver_date[MAX_VERSION_DISPLAY_BUF];
	u8 sirc_sdk_ver_no[MAX_VERSION_DISPLAY_BUF];
	u8 sirc_sdk_rev_no[MAX_VERSION_DISPLAY_BUF];
	u8 sirc_sdk_rev_date[MAX_VERSION_DISPLAY_BUF];
पूर्ण __packed;

काष्ठा is_debug_control अणु
	u32 ग_लिखो_poपूर्णांक;	/* 0~ 500KB boundary */
	u32 निश्चित_flag;	/* 0: Not invoked, 1: Invoked */
	u32 pपात_flag;	/* 0: Not invoked, 1: Invoked */
	u32 dपात_flag;	/* 0: Not invoked, 1: Invoked */
पूर्ण;

काष्ठा sensor_खोलो_extended अणु
	u32 actuator_type;
	u32 mclk;
	u32 mipi_lane_num;
	u32 mipi_speed;
	/* Skip setfile loading when fast_खोलो_sensor is not 0 */
	u32 fast_खोलो_sensor;
	/* Activating sensor self calibration mode (6A3) */
	u32 self_calibration_mode;
	/* This field is to adjust I2c घड़ी based on ACLK200 */
	/* This value is varied in हाल of rev 0.2 */
	u32 i2c_sclk;
पूर्ण;

काष्ठा fimc_is;

पूर्णांक fimc_is_hw_get_sensor_max_framerate(काष्ठा fimc_is *is);
पूर्णांक __fimc_is_hw_update_param(काष्ठा fimc_is *is, u32 offset);
व्योम fimc_is_set_initial_params(काष्ठा fimc_is *is);
अचिन्हित पूर्णांक __get_pending_param_count(काष्ठा fimc_is *is);

पूर्णांक  __is_hw_update_params(काष्ठा fimc_is *is);
व्योम __is_get_frame_size(काष्ठा fimc_is *is, काष्ठा v4l2_mbus_framefmt *mf);
व्योम __is_set_frame_size(काष्ठा fimc_is *is, काष्ठा v4l2_mbus_framefmt *mf);
व्योम __is_set_sensor(काष्ठा fimc_is *is, पूर्णांक fps);
व्योम __is_set_isp_aa_ae(काष्ठा fimc_is *is);
व्योम __is_set_isp_flash(काष्ठा fimc_is *is, u32 cmd, u32 redeye);
व्योम __is_set_isp_awb(काष्ठा fimc_is *is, u32 cmd, u32 val);
व्योम __is_set_isp_effect(काष्ठा fimc_is *is, u32 cmd);
व्योम __is_set_isp_iso(काष्ठा fimc_is *is, u32 cmd, u32 val);
व्योम __is_set_isp_adjust(काष्ठा fimc_is *is, u32 cmd, u32 val);
व्योम __is_set_isp_metering(काष्ठा fimc_is *is, u32 id, u32 val);
व्योम __is_set_isp_afc(काष्ठा fimc_is *is, u32 cmd, u32 val);
व्योम __is_set_drc_control(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_control(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_config_maxface(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_config_rollangle(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_config_yawangle(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_config_smilemode(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_config_blinkmode(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_config_eyedetect(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_config_mouthdetect(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_config_orientation(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_fd_config_orientation_val(काष्ठा fimc_is *is, u32 val);
व्योम __is_set_isp_aa_af_mode(काष्ठा fimc_is *is, पूर्णांक cmd);
व्योम __is_set_isp_aa_af_start_stop(काष्ठा fimc_is *is, पूर्णांक cmd);

#पूर्ण_अगर
