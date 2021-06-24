<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/media/i2c/smiapp/ccs.h
 *
 * Generic driver क्रम MIPI CCS/SMIA/SMIA++ compliant camera sensors
 *
 * Copyright (C) 2020 Intel Corporation
 * Copyright (C) 2010--2012 Nokia Corporation
 * Contact: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __CCS_H__
#घोषणा __CCS_H__

#समावेश <linux/mutex.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "ccs-data.h"
#समावेश "ccs-limits.h"
#समावेश "ccs-quirk.h"
#समावेश "ccs-regs.h"
#समावेश "ccs-reg-access.h"
#समावेश "../ccs-pll.h"
#समावेश "smiapp-reg-defs.h"

/*
 * Standard SMIA++ स्थिरants
 */
#घोषणा SMIA_VERSION_1			10
#घोषणा SMIAPP_VERSION_0_8		8 /* Draft 0.8 */
#घोषणा SMIAPP_VERSION_0_9		9 /* Draft 0.9 */
#घोषणा SMIAPP_VERSION_1		10

#घोषणा SMIAPP_PROखाता_0		0
#घोषणा SMIAPP_PROखाता_1		1
#घोषणा SMIAPP_PROखाता_2		2

#घोषणा SMIAPP_NVM_PAGE_SIZE		64	/* bytes */

#घोषणा SMIAPP_RESET_DELAY_CLOCKS	2400
#घोषणा SMIAPP_RESET_DELAY(clk)				\
	(1000 +	(SMIAPP_RESET_DELAY_CLOCKS * 1000	\
		 + (clk) / 1000 - 1) / ((clk) / 1000))

#घोषणा CCS_COLOUR_COMPONENTS		4

#घोषणा SMIAPP_NAME			"smiapp"
#घोषणा CCS_NAME			"ccs"

#घोषणा CCS_DFL_I2C_ADDR	(0x20 >> 1) /* Default I2C Address */
#घोषणा CCS_ALT_I2C_ADDR	(0x6e >> 1) /* Alternate I2C Address */

#घोषणा CCS_LIM(sensor, limit) \
	ccs_get_limit(sensor, CCS_L_##limit, 0)

#घोषणा CCS_LIM_AT(sensor, limit, offset)	\
	ccs_get_limit(sensor, CCS_L_##limit, CCS_L_##limit##_OFFSET(offset))

/*
 * Someबार due to board layout considerations the camera module can be
 * mounted rotated. The typical rotation used is 180 degrees which can be
 * corrected by giving a शेष H-FLIP and V-FLIP in the sensor पढ़ोout.
 * FIXME: rotation also changes the bayer pattern.
 */
क्रमागत ccs_module_board_orient अणु
	CCS_MODULE_BOARD_ORIENT_0 = 0,
	CCS_MODULE_BOARD_ORIENT_180,
पूर्ण;

काष्ठा ccs_flash_strobe_parms अणु
	u8 mode;
	u32 strobe_width_high_us;
	u16 strobe_delay;
	u16 stobe_start_poपूर्णांक;
	u8 trigger;
पूर्ण;

काष्ठा ccs_hwconfig अणु
	/*
	 * Change the cci address अगर i2c_addr_alt is set.
	 * Both शेष and alternate cci addr need to be present
	 */
	अचिन्हित लघु i2c_addr_dfl;	/* Default i2c addr */
	अचिन्हित लघु i2c_addr_alt;	/* Alternate i2c addr */

	u32 ext_clk;			/* sensor बाह्यal clk */

	अचिन्हित पूर्णांक lanes;		/* Number of CSI-2 lanes */
	u32 csi_संकेतling_mode;	/* CCS_CSI_SIGNALLING_MODE_* */
	u64 *op_sys_घड़ी;

	क्रमागत ccs_module_board_orient module_board_orient;

	काष्ठा ccs_flash_strobe_parms *strobe_setup;
पूर्ण;

काष्ठा ccs_quirk;

#घोषणा CCS_MODULE_IDENT_FLAG_REV_LE		(1 << 0)

काष्ठा ccs_module_ident अणु
	u16 mipi_manufacturer_id;
	u16 model_id;
	u8 smia_manufacturer_id;
	u8 revision_number_major;

	u8 flags;

	अक्षर *name;
	स्थिर काष्ठा ccs_quirk *quirk;
पूर्ण;

काष्ठा ccs_module_info अणु
	u32 smia_manufacturer_id;
	u32 mipi_manufacturer_id;
	u32 model_id;
	u32 revision_number;

	u32 module_year;
	u32 module_month;
	u32 module_day;

	u32 sensor_smia_manufacturer_id;
	u32 sensor_mipi_manufacturer_id;
	u32 sensor_model_id;
	u32 sensor_revision_number;
	u32 sensor_firmware_version;

	u32 smia_version;
	u32 smiapp_version;
	u32 ccs_version;

	अक्षर *name;
	स्थिर काष्ठा ccs_quirk *quirk;
पूर्ण;

#घोषणा CCS_IDENT_FQ(manufacturer, model, rev, fl, _name, _quirk)	\
	अणु .smia_manufacturer_id = manufacturer,				\
	  .model_id = model,						\
	  .revision_number_major = rev,					\
	  .flags = fl,							\
	  .name = _name,						\
	  .quirk = _quirk, पूर्ण

#घोषणा CCS_IDENT_LQ(manufacturer, model, rev, _name, _quirk)	\
	अणु .smia_manufacturer_id = manufacturer,				\
	  .model_id = model,						\
	  .revision_number_major = rev,					\
	  .flags = CCS_MODULE_IDENT_FLAG_REV_LE,			\
	  .name = _name,						\
	  .quirk = _quirk, पूर्ण

#घोषणा CCS_IDENT_L(manufacturer, model, rev, _name)			\
	अणु .smia_manufacturer_id = manufacturer,				\
	  .model_id = model,						\
	  .revision_number_major = rev,					\
	  .flags = CCS_MODULE_IDENT_FLAG_REV_LE,			\
	  .name = _name, पूर्ण

#घोषणा CCS_IDENT_Q(manufacturer, model, rev, _name, _quirk)		\
	अणु .smia_manufacturer_id = manufacturer,				\
	  .model_id = model,						\
	  .revision_number_major = rev,					\
	  .flags = 0,							\
	  .name = _name,						\
	  .quirk = _quirk, पूर्ण

#घोषणा CCS_IDENT(manufacturer, model, rev, _name)			\
	अणु .smia_manufacturer_id = manufacturer,				\
	  .model_id = model,						\
	  .revision_number_major = rev,					\
	  .flags = 0,							\
	  .name = _name, पूर्ण

काष्ठा ccs_csi_data_क्रमmat अणु
	u32 code;
	u8 width;
	u8 compressed;
	u8 pixel_order;
पूर्ण;

#घोषणा CCS_SUBDEVS			3

#घोषणा CCS_PA_PAD_SRC			0
#घोषणा CCS_PAD_SINK			0
#घोषणा CCS_PAD_SRC			1
#घोषणा CCS_PADS			2

काष्ठा ccs_binning_subtype अणु
	u8 horizontal:4;
	u8 vertical:4;
पूर्ण __packed;

काष्ठा ccs_subdev अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pads[CCS_PADS];
	काष्ठा v4l2_rect sink_fmt;
	काष्ठा v4l2_rect crop[CCS_PADS];
	काष्ठा v4l2_rect compose; /* compose on sink */
	अचिन्हित लघु sink_pad;
	अचिन्हित लघु source_pad;
	पूर्णांक npads;
	काष्ठा ccs_sensor *sensor;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
पूर्ण;

/*
 * काष्ठा ccs_sensor - Main device काष्ठाure
 */
काष्ठा ccs_sensor अणु
	/*
	 * "mutex" is used to serialise access to all fields here
	 * except v4l2_ctrls at the end of the काष्ठा. "mutex" is also
	 * used to serialise access to file handle specअगरic
	 * inक्रमmation.
	 */
	काष्ठा mutex mutex;
	काष्ठा ccs_subdev ssds[CCS_SUBDEVS];
	u32 ssds_used;
	काष्ठा ccs_subdev *src;
	काष्ठा ccs_subdev *binner;
	काष्ठा ccs_subdev *scaler;
	काष्ठा ccs_subdev *pixel_array;
	काष्ठा ccs_hwconfig hwcfg;
	काष्ठा regulator_bulk_data *regulators;
	काष्ठा clk *ext_clk;
	काष्ठा gpio_desc *xshutकरोwn;
	काष्ठा gpio_desc *reset;
	व्योम *ccs_limits;
	u8 nbinning_subtypes;
	काष्ठा ccs_binning_subtype binning_subtypes[CCS_LIM_BINNING_SUB_TYPE_MAX_N + 1];
	u32 mbus_frame_fmts;
	स्थिर काष्ठा ccs_csi_data_क्रमmat *csi_क्रमmat;
	स्थिर काष्ठा ccs_csi_data_क्रमmat *पूर्णांकernal_csi_क्रमmat;
	u32 शेष_mbus_frame_fmts;
	पूर्णांक शेष_pixel_order;
	काष्ठा ccs_data_container sdata, mdata;

	u8 binning_horizontal;
	u8 binning_vertical;

	u8 scale_m;
	u8 scaling_mode;

	u8 hvflip_inv_mask; /* H/VFLIP inversion due to sensor orientation */
	u8 frame_skip;
	u16 embedded_start; /* embedded data start line */
	u16 embedded_end;
	u16 image_start; /* image data start line */
	u16 visible_pixel_start; /* start pixel of the visible image */

	bool streaming;
	bool dev_init_करोne;
	u8 compressed_min_bpp;

	काष्ठा ccs_module_info minfo;

	काष्ठा ccs_pll pll;

	/* Is a शेष क्रमmat supported क्रम a given BPP? */
	अचिन्हित दीर्घ *valid_link_freqs;

	/* Pixel array controls */
	काष्ठा v4l2_ctrl *exposure;
	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vflip;
	काष्ठा v4l2_ctrl *vblank;
	काष्ठा v4l2_ctrl *hblank;
	काष्ठा v4l2_ctrl *pixel_rate_parray;
	काष्ठा v4l2_ctrl *luminance_level;
	/* src controls */
	काष्ठा v4l2_ctrl *link_freq;
	काष्ठा v4l2_ctrl *pixel_rate_csi;
	/* test pattern colour components */
	काष्ठा v4l2_ctrl *test_data[CCS_COLOUR_COMPONENTS];
पूर्ण;

#घोषणा to_ccs_subdev(_sd)				\
	container_of(_sd, काष्ठा ccs_subdev, sd)

#घोषणा to_ccs_sensor(_sd)	\
	(to_ccs_subdev(_sd)->sensor)

व्योम ccs_replace_limit(काष्ठा ccs_sensor *sensor,
		       अचिन्हित पूर्णांक limit, अचिन्हित पूर्णांक offset, u32 val);
u32 ccs_get_limit(काष्ठा ccs_sensor *sensor, अचिन्हित पूर्णांक limit,
		  अचिन्हित पूर्णांक offset);

#पूर्ण_अगर /* __CCS_H__ */
