<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung LSI S5C73M3 8M pixel camera driver
 *
 * Copyright (C) 2012, Samsung Electronics, Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 * Andrzej Hajda <a.hajda@samsung.com>
 */
#अगर_अघोषित S5C73M3_H_
#घोषणा S5C73M3_H_

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/i2c/s5c73m3.h>

#घोषणा DRIVER_NAME			"S5C73M3"

#घोषणा S5C73M3_ISP_FMT			MEDIA_BUS_FMT_VYUY8_2X8
#घोषणा S5C73M3_JPEG_FMT		MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8

/* Subdevs pad index definitions */
क्रमागत s5c73m3_pads अणु
	S5C73M3_ISP_PAD,
	S5C73M3_JPEG_PAD,
	S5C73M3_NUM_PADS
पूर्ण;

क्रमागत s5c73m3_oअगर_pads अणु
	OIF_ISP_PAD,
	OIF_JPEG_PAD,
	OIF_SOURCE_PAD,
	OIF_NUM_PADS
पूर्ण;

#घोषणा S5C73M3_SENSOR_FW_LEN		6
#घोषणा S5C73M3_SENSOR_TYPE_LEN		12

#घोषणा S5C73M3_REG(_addrh, _addrl) (((_addrh) << 16) | _addrl)

#घोषणा AHB_MSB_ADDR_PTR			0xfcfc
#घोषणा REG_CMDWR_ADDRH				0x0050
#घोषणा REG_CMDWR_ADDRL				0x0054
#घोषणा REG_CMDRD_ADDRH				0x0058
#घोषणा REG_CMDRD_ADDRL				0x005c
#घोषणा REG_CMDBUF_ADDR				0x0f14

#घोषणा REG_I2C_SEQ_STATUS			S5C73M3_REG(0x0009, 0x59A6)
#घोषणा  SEQ_END_PLL				(1<<0x0)
#घोषणा  SEQ_END_SENSOR				(1<<0x1)
#घोषणा  SEQ_END_GPIO				(1<<0x2)
#घोषणा  SEQ_END_FROM				(1<<0x3)
#घोषणा  SEQ_END_STABLE_AE_AWB			(1<<0x4)
#घोषणा  SEQ_END_READY_I2C_CMD			(1<<0x5)

#घोषणा REG_I2C_STATUS				S5C73M3_REG(0x0009, 0x599E)
#घोषणा  I2C_STATUS_CIS_I2C			(1<<0x0)
#घोषणा  I2C_STATUS_AF_INIT			(1<<0x1)
#घोषणा  I2C_STATUS_CAL_DATA			(1<<0x2)
#घोषणा  I2C_STATUS_FRAME_COUNT			(1<<0x3)
#घोषणा  I2C_STATUS_FROM_INIT			(1<<0x4)
#घोषणा  I2C_STATUS_I2C_CIS_STREAM_OFF		(1<<0x5)
#घोषणा  I2C_STATUS_I2C_N_CMD_OVER		(1<<0x6)
#घोषणा  I2C_STATUS_I2C_N_CMD_MISMATCH		(1<<0x7)
#घोषणा  I2C_STATUS_CHECK_BIN_CRC		(1<<0x8)
#घोषणा  I2C_STATUS_EXCEPTION			(1<<0x9)
#घोषणा  I2C_STATUS_INIF_INIT_STATE		(0x8)

#घोषणा REG_STATUS				S5C73M3_REG(0x0009, 0x5080)
#घोषणा  REG_STATUS_BOOT_SUB_MAIN_ENTER		0xff01
#घोषणा  REG_STATUS_BOOT_SRAM_TIMING_OK		0xff02
#घोषणा  REG_STATUS_BOOT_INTERRUPTS_EN		0xff03
#घोषणा  REG_STATUS_BOOT_R_PLL_DONE		0xff04
#घोषणा  REG_STATUS_BOOT_R_PLL_LOCKTIME_DONE	0xff05
#घोषणा  REG_STATUS_BOOT_DELAY_COUNT_DONE	0xff06
#घोषणा  REG_STATUS_BOOT_I_PLL_DONE		0xff07
#घोषणा  REG_STATUS_BOOT_I_PLL_LOCKTIME_DONE	0xff08
#घोषणा  REG_STATUS_BOOT_PLL_INIT_OK		0xff09
#घोषणा  REG_STATUS_BOOT_SENSOR_INIT_OK		0xff0a
#घोषणा  REG_STATUS_BOOT_GPIO_SETTING_OK	0xff0b
#घोषणा  REG_STATUS_BOOT_READ_CAL_DATA_OK	0xff0c
#घोषणा  REG_STATUS_BOOT_STABLE_AE_AWB_OK	0xff0d
#घोषणा  REG_STATUS_ISP_COMMAND_COMPLETED	0xffff
#घोषणा  REG_STATUS_EXCEPTION_OCCURED		0xdead

#घोषणा COMM_RESULT_OFFSET			S5C73M3_REG(0x0009, 0x5000)

#घोषणा COMM_IMG_OUTPUT				0x0902
#घोषणा  COMM_IMG_OUTPUT_HDR			0x0008
#घोषणा  COMM_IMG_OUTPUT_YUV			0x0009
#घोषणा  COMM_IMG_OUTPUT_INTERLEAVED		0x000d

#घोषणा COMM_STILL_PRE_FLASH			0x0a00
#घोषणा  COMM_STILL_PRE_FLASH_FIRE		0x0000
#घोषणा  COMM_STILL_PRE_FLASH_NON_FIRED		0x0000
#घोषणा  COMM_STILL_PRE_FLASH_FIRED		0x0001

#घोषणा COMM_STILL_MAIN_FLASH			0x0a02
#घोषणा  COMM_STILL_MAIN_FLASH_CANCEL		0x0001
#घोषणा  COMM_STILL_MAIN_FLASH_FIRE		0x0002

#घोषणा COMM_ZOOM_STEP				0x0b00

#घोषणा COMM_IMAGE_EFFECT			0x0b0a
#घोषणा  COMM_IMAGE_EFFECT_NONE			0x0001
#घोषणा  COMM_IMAGE_EFFECT_NEGATIVE		0x0002
#घोषणा  COMM_IMAGE_EFFECT_AQUA			0x0003
#घोषणा  COMM_IMAGE_EFFECT_SEPIA		0x0004
#घोषणा  COMM_IMAGE_EFFECT_MONO			0x0005

#घोषणा COMM_IMAGE_QUALITY			0x0b0c
#घोषणा  COMM_IMAGE_QUALITY_SUPERFINE		0x0000
#घोषणा  COMM_IMAGE_QUALITY_FINE		0x0001
#घोषणा  COMM_IMAGE_QUALITY_NORMAL		0x0002

#घोषणा COMM_FLASH_MODE				0x0b0e
#घोषणा  COMM_FLASH_MODE_OFF			0x0000
#घोषणा  COMM_FLASH_MODE_ON			0x0001
#घोषणा  COMM_FLASH_MODE_AUTO			0x0002

#घोषणा COMM_FLASH_STATUS			0x0b80
#घोषणा  COMM_FLASH_STATUS_OFF			0x0001
#घोषणा  COMM_FLASH_STATUS_ON			0x0002
#घोषणा  COMM_FLASH_STATUS_AUTO			0x0003

#घोषणा COMM_FLASH_TORCH			0x0b12
#घोषणा  COMM_FLASH_TORCH_OFF			0x0000
#घोषणा  COMM_FLASH_TORCH_ON			0x0001

#घोषणा COMM_AE_NEEDS_FLASH			0x0cba
#घोषणा  COMM_AE_NEEDS_FLASH_OFF		0x0000
#घोषणा  COMM_AE_NEEDS_FLASH_ON			0x0001

#घोषणा COMM_CHG_MODE				0x0b10
#घोषणा  COMM_CHG_MODE_NEW			0x8000
#घोषणा  COMM_CHG_MODE_SUBSAMPLING_HALF		0x2000
#घोषणा  COMM_CHG_MODE_SUBSAMPLING_QUARTER	0x4000

#घोषणा  COMM_CHG_MODE_YUV_320_240		0x0001
#घोषणा  COMM_CHG_MODE_YUV_640_480		0x0002
#घोषणा  COMM_CHG_MODE_YUV_880_720		0x0003
#घोषणा  COMM_CHG_MODE_YUV_960_720		0x0004
#घोषणा  COMM_CHG_MODE_YUV_1184_666		0x0005
#घोषणा  COMM_CHG_MODE_YUV_1280_720		0x0006
#घोषणा  COMM_CHG_MODE_YUV_1536_864		0x0007
#घोषणा  COMM_CHG_MODE_YUV_1600_1200		0x0008
#घोषणा  COMM_CHG_MODE_YUV_1632_1224		0x0009
#घोषणा  COMM_CHG_MODE_YUV_1920_1080		0x000a
#घोषणा  COMM_CHG_MODE_YUV_1920_1440		0x000b
#घोषणा  COMM_CHG_MODE_YUV_2304_1296		0x000c
#घोषणा  COMM_CHG_MODE_YUV_3264_2448		0x000d
#घोषणा  COMM_CHG_MODE_YUV_352_288		0x000e
#घोषणा  COMM_CHG_MODE_YUV_1008_672		0x000f

#घोषणा  COMM_CHG_MODE_JPEG_640_480		0x0010
#घोषणा  COMM_CHG_MODE_JPEG_800_450		0x0020
#घोषणा  COMM_CHG_MODE_JPEG_800_600		0x0030
#घोषणा  COMM_CHG_MODE_JPEG_1280_720		0x0040
#घोषणा  COMM_CHG_MODE_JPEG_1280_960		0x0050
#घोषणा  COMM_CHG_MODE_JPEG_1600_900		0x0060
#घोषणा  COMM_CHG_MODE_JPEG_1600_1200		0x0070
#घोषणा  COMM_CHG_MODE_JPEG_2048_1152		0x0080
#घोषणा  COMM_CHG_MODE_JPEG_2048_1536		0x0090
#घोषणा  COMM_CHG_MODE_JPEG_2560_1440		0x00a0
#घोषणा  COMM_CHG_MODE_JPEG_2560_1920		0x00b0
#घोषणा  COMM_CHG_MODE_JPEG_3264_2176		0x00c0
#घोषणा  COMM_CHG_MODE_JPEG_1024_768		0x00d0
#घोषणा  COMM_CHG_MODE_JPEG_3264_1836		0x00e0
#घोषणा  COMM_CHG_MODE_JPEG_3264_2448		0x00f0

#घोषणा COMM_AF_CON				0x0e00
#घोषणा  COMM_AF_CON_STOP			0x0000
#घोषणा  COMM_AF_CON_SCAN			0x0001 /* Full Search */
#घोषणा  COMM_AF_CON_START			0x0002 /* Fast Search */

#घोषणा COMM_AF_CAL				0x0e06
#घोषणा COMM_AF_TOUCH_AF			0x0e0a

#घोषणा REG_AF_STATUS				S5C73M3_REG(0x0009, 0x5e80)
#घोषणा  REG_CAF_STATUS_FIND_SEARCH_सूची		0x0001
#घोषणा  REG_CAF_STATUS_FOCUSING		0x0002
#घोषणा  REG_CAF_STATUS_FOCUSED			0x0003
#घोषणा  REG_CAF_STATUS_UNFOCUSED		0x0004
#घोषणा  REG_AF_STATUS_INVALID			0x0010
#घोषणा  REG_AF_STATUS_FOCUSING			0x0020
#घोषणा  REG_AF_STATUS_FOCUSED			0x0030
#घोषणा  REG_AF_STATUS_UNFOCUSED		0x0040

#घोषणा REG_AF_TOUCH_POSITION			S5C73M3_REG(0x0009, 0x5e8e)
#घोषणा COMM_AF_FACE_ZOOM			0x0e10

#घोषणा COMM_AF_MODE				0x0e02
#घोषणा  COMM_AF_MODE_NORMAL			0x0000
#घोषणा  COMM_AF_MODE_MACRO			0x0001
#घोषणा  COMM_AF_MODE_MOVIE_CAF_START		0x0002
#घोषणा  COMM_AF_MODE_MOVIE_CAF_STOP		0x0003
#घोषणा  COMM_AF_MODE_PREVIEW_CAF_START		0x0004
#घोषणा  COMM_AF_MODE_PREVIEW_CAF_STOP		0x0005

#घोषणा COMM_AF_SOFTLANDING			0x0e16
#घोषणा  COMM_AF_SOFTLANDING_ON			0x0000
#घोषणा  COMM_AF_SOFTLANDING_RES_COMPLETE	0x0001

#घोषणा COMM_FACE_DET				0x0e0c
#घोषणा  COMM_FACE_DET_OFF			0x0000
#घोषणा  COMM_FACE_DET_ON			0x0001

#घोषणा COMM_FACE_DET_OSD			0x0e0e
#घोषणा  COMM_FACE_DET_OSD_OFF			0x0000
#घोषणा  COMM_FACE_DET_OSD_ON			0x0001

#घोषणा COMM_AE_CON				0x0c00
#घोषणा  COMM_AE_STOP				0x0000 /* lock */
#घोषणा  COMM_AE_START				0x0001 /* unlock */

#घोषणा COMM_ISO				0x0c02
#घोषणा  COMM_ISO_AUTO				0x0000
#घोषणा  COMM_ISO_100				0x0001
#घोषणा  COMM_ISO_200				0x0002
#घोषणा  COMM_ISO_400				0x0003
#घोषणा  COMM_ISO_800				0x0004
#घोषणा  COMM_ISO_SPORTS			0x0005
#घोषणा  COMM_ISO_NIGHT				0x0006
#घोषणा  COMM_ISO_INDOOR			0x0007

/* 0x00000 (-2.0 EV)...0x0008 (2.0 EV), 0.5EV step */
#घोषणा COMM_EV					0x0c04

#घोषणा COMM_METERING				0x0c06
#घोषणा  COMM_METERING_CENTER			0x0000
#घोषणा  COMM_METERING_SPOT			0x0001
#घोषणा  COMM_METERING_AVERAGE			0x0002
#घोषणा  COMM_METERING_SMART			0x0003

#घोषणा COMM_WDR				0x0c08
#घोषणा  COMM_WDR_OFF				0x0000
#घोषणा  COMM_WDR_ON				0x0001

#घोषणा COMM_FLICKER_MODE			0x0c12
#घोषणा  COMM_FLICKER_NONE			0x0000
#घोषणा  COMM_FLICKER_MANUAL_50HZ		0x0001
#घोषणा  COMM_FLICKER_MANUAL_60HZ		0x0002
#घोषणा  COMM_FLICKER_AUTO			0x0003
#घोषणा  COMM_FLICKER_AUTO_50HZ			0x0004
#घोषणा  COMM_FLICKER_AUTO_60HZ			0x0005

#घोषणा COMM_FRAME_RATE				0x0c1e
#घोषणा  COMM_FRAME_RATE_AUTO_SET		0x0000
#घोषणा  COMM_FRAME_RATE_FIXED_30FPS		0x0002
#घोषणा  COMM_FRAME_RATE_FIXED_20FPS		0x0003
#घोषणा  COMM_FRAME_RATE_FIXED_15FPS		0x0004
#घोषणा  COMM_FRAME_RATE_FIXED_60FPS		0x0007
#घोषणा  COMM_FRAME_RATE_FIXED_120FPS		0x0008
#घोषणा  COMM_FRAME_RATE_FIXED_7FPS		0x0009
#घोषणा  COMM_FRAME_RATE_FIXED_10FPS		0x000a
#घोषणा  COMM_FRAME_RATE_FIXED_90FPS		0x000b
#घोषणा  COMM_FRAME_RATE_ANTI_SHAKE		0x0013

/* 0x0000...0x0004 -> sharpness: 0, 1, 2, -1, -2 */
#घोषणा COMM_SHARPNESS				0x0c14

/* 0x0000...0x0004 -> saturation: 0, 1, 2, -1, -2 */
#घोषणा COMM_SATURATION				0x0c16

/* 0x0000...0x0004 -> contrast: 0, 1, 2, -1, -2 */
#घोषणा COMM_CONTRAST				0x0c18

#घोषणा COMM_SCENE_MODE				0x0c1a
#घोषणा  COMM_SCENE_MODE_NONE			0x0000
#घोषणा  COMM_SCENE_MODE_PORTRAIT		0x0001
#घोषणा  COMM_SCENE_MODE_LANDSCAPE		0x0002
#घोषणा  COMM_SCENE_MODE_SPORTS			0x0003
#घोषणा  COMM_SCENE_MODE_INDOOR			0x0004
#घोषणा  COMM_SCENE_MODE_BEACH			0x0005
#घोषणा  COMM_SCENE_MODE_SUNSET			0x0006
#घोषणा  COMM_SCENE_MODE_DAWN			0x0007
#घोषणा  COMM_SCENE_MODE_FALL			0x0008
#घोषणा  COMM_SCENE_MODE_NIGHT			0x0009
#घोषणा  COMM_SCENE_MODE_AGAINST_LIGHT		0x000a
#घोषणा  COMM_SCENE_MODE_FIRE			0x000b
#घोषणा  COMM_SCENE_MODE_TEXT			0x000c
#घोषणा  COMM_SCENE_MODE_CANDLE			0x000d

#घोषणा COMM_AE_AUTO_BRACKET			0x0b14
#घोषणा  COMM_AE_AUTO_BRAKET_EV05		0x0080
#घोषणा  COMM_AE_AUTO_BRAKET_EV10		0x0100
#घोषणा  COMM_AE_AUTO_BRAKET_EV15		0x0180
#घोषणा  COMM_AE_AUTO_BRAKET_EV20		0x0200

#घोषणा COMM_SENSOR_STREAMING			0x090a
#घोषणा  COMM_SENSOR_STREAMING_OFF		0x0000
#घोषणा  COMM_SENSOR_STREAMING_ON		0x0001

#घोषणा COMM_AWB_MODE				0x0d02
#घोषणा  COMM_AWB_MODE_INCANDESCENT		0x0000
#घोषणा  COMM_AWB_MODE_FLUORESCENT1		0x0001
#घोषणा  COMM_AWB_MODE_FLUORESCENT2		0x0002
#घोषणा  COMM_AWB_MODE_DAYLIGHT			0x0003
#घोषणा  COMM_AWB_MODE_CLOUDY			0x0004
#घोषणा  COMM_AWB_MODE_AUTO			0x0005

#घोषणा COMM_AWB_CON				0x0d00
#घोषणा  COMM_AWB_STOP				0x0000 /* lock */
#घोषणा  COMM_AWB_START				0x0001 /* unlock */

#घोषणा COMM_FW_UPDATE				0x0906
#घोषणा  COMM_FW_UPDATE_NOT_READY		0x0000
#घोषणा  COMM_FW_UPDATE_SUCCESS			0x0005
#घोषणा  COMM_FW_UPDATE_FAIL			0x0007
#घोषणा  COMM_FW_UPDATE_BUSY			0xffff


#घोषणा S5C73M3_MAX_SUPPLIES			6
#घोषणा S5C73M3_DEFAULT_MCLK_FREQ		24000000U

काष्ठा s5c73m3_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;
	काष्ठा अणु
		/* exposure/exposure bias cluster */
		काष्ठा v4l2_ctrl *स्वतः_exposure;
		काष्ठा v4l2_ctrl *exposure_bias;
		काष्ठा v4l2_ctrl *exposure_metering;
	पूर्ण;
	काष्ठा अणु
		/* iso/स्वतः iso cluster */
		काष्ठा v4l2_ctrl *स्वतः_iso;
		काष्ठा v4l2_ctrl *iso;
	पूर्ण;
	काष्ठा v4l2_ctrl *स्वतः_wb;
	काष्ठा अणु
		/* continuous स्वतः focus/स्वतः focus cluster */
		काष्ठा v4l2_ctrl *focus_स्वतः;
		काष्ठा v4l2_ctrl *af_start;
		काष्ठा v4l2_ctrl *af_stop;
		काष्ठा v4l2_ctrl *af_status;
		काष्ठा v4l2_ctrl *af_distance;
	पूर्ण;

	काष्ठा v4l2_ctrl *aaa_lock;
	काष्ठा v4l2_ctrl *colorfx;
	काष्ठा v4l2_ctrl *contrast;
	काष्ठा v4l2_ctrl *saturation;
	काष्ठा v4l2_ctrl *sharpness;
	काष्ठा v4l2_ctrl *zoom;
	काष्ठा v4l2_ctrl *wdr;
	काष्ठा v4l2_ctrl *stabilization;
	काष्ठा v4l2_ctrl *jpeg_quality;
	काष्ठा v4l2_ctrl *scene_mode;
पूर्ण;

क्रमागत s5c73m3_gpio_id अणु
	STBY,
	RST,
	GPIO_NUM,
पूर्ण;

क्रमागत s5c73m3_resolution_types अणु
	RES_ISP,
	RES_JPEG,
पूर्ण;

काष्ठा s5c73m3_पूर्णांकerval अणु
	u16 fps_reg;
	काष्ठा v4l2_fract पूर्णांकerval;
	/* Maximum rectangle क्रम the पूर्णांकerval */
	काष्ठा v4l2_frmsize_discrete size;
पूर्ण;

काष्ठा s5c73m3 अणु
	काष्ठा v4l2_subdev sensor_sd;
	काष्ठा media_pad sensor_pads[S5C73M3_NUM_PADS];

	काष्ठा v4l2_subdev oअगर_sd;
	काष्ठा media_pad oअगर_pads[OIF_NUM_PADS];

	काष्ठा spi_driver spidrv;
	काष्ठा spi_device *spi_dev;
	काष्ठा i2c_client *i2c_client;
	u32 i2c_ग_लिखो_address;
	u32 i2c_पढ़ो_address;

	काष्ठा regulator_bulk_data supplies[S5C73M3_MAX_SUPPLIES];
	काष्ठा s5c73m3_gpio gpio[GPIO_NUM];

	काष्ठा clk *घड़ी;

	/* External master घड़ी frequency */
	u32 mclk_frequency;
	/* Video bus type - MIPI-CSI2/parallel */
	क्रमागत v4l2_mbus_type bus_type;

	स्थिर काष्ठा s5c73m3_frame_size *sensor_pix_size[2];
	स्थिर काष्ठा s5c73m3_frame_size *oअगर_pix_size[2];
	u32 mbus_code;

	स्थिर काष्ठा s5c73m3_पूर्णांकerval *fiv;

	काष्ठा v4l2_mbus_frame_desc frame_desc;
	/* protects the काष्ठा members below */
	काष्ठा mutex lock;

	काष्ठा s5c73m3_ctrls ctrls;

	u8 streaming:1;
	u8 apply_fmt:1;
	u8 apply_fiv:1;
	u8 isp_पढ़ोy:1;

	लघु घातer;

	अक्षर sensor_fw[S5C73M3_SENSOR_FW_LEN + 2];
	अक्षर sensor_type[S5C73M3_SENSOR_TYPE_LEN + 2];
	अक्षर fw_file_version[2];
	अचिन्हित पूर्णांक fw_size;
पूर्ण;

काष्ठा s5c73m3_frame_size अणु
	u32 width;
	u32 height;
	u8 reg_val;
पूर्ण;

बाह्य पूर्णांक s5c73m3_dbg;

पूर्णांक s5c73m3_रेजिस्टर_spi_driver(काष्ठा s5c73m3 *state);
व्योम s5c73m3_unरेजिस्टर_spi_driver(काष्ठा s5c73m3 *state);
पूर्णांक s5c73m3_spi_ग_लिखो(काष्ठा s5c73m3 *state, स्थिर व्योम *addr,
		      स्थिर अचिन्हित पूर्णांक len, स्थिर अचिन्हित पूर्णांक tx_size);
पूर्णांक s5c73m3_spi_पढ़ो(काष्ठा s5c73m3 *state, व्योम *addr,
		      स्थिर अचिन्हित पूर्णांक len, स्थिर अचिन्हित पूर्णांक tx_size);

पूर्णांक s5c73m3_पढ़ो(काष्ठा s5c73m3 *state, u32 addr, u16 *data);
पूर्णांक s5c73m3_ग_लिखो(काष्ठा s5c73m3 *state, u32 addr, u16 data);
पूर्णांक s5c73m3_isp_command(काष्ठा s5c73m3 *state, u16 command, u16 data);
पूर्णांक s5c73m3_init_controls(काष्ठा s5c73m3 *state);

अटल अंतरभूत काष्ठा v4l2_subdev *ctrl_to_sensor_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा s5c73m3,
			     ctrls.handler)->sensor_sd;
पूर्ण

अटल अंतरभूत काष्ठा s5c73m3 *sensor_sd_to_s5c73m3(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा s5c73m3, sensor_sd);
पूर्ण

अटल अंतरभूत काष्ठा s5c73m3 *oअगर_sd_to_s5c73m3(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा s5c73m3, oअगर_sd);
पूर्ण
#पूर्ण_अगर	/* S5C73M3_H_ */
