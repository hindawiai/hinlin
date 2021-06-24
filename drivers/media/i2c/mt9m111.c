<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम MT9M111/MT9M112/MT9M131 CMOS Image Sensor from Micron/Aptina
 *
 * Copyright (C) 2008, Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 */
#समावेश <linux/clk.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/log2.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>

/*
 * MT9M111, MT9M112 and MT9M131:
 * i2c address is 0x48 or 0x5d (depending on SADDR pin)
 * The platक्रमm has to define काष्ठा i2c_board_info objects and link to them
 * from काष्ठा soc_camera_host_desc
 */

/*
 * Sensor core रेजिस्टर addresses (0x000..0x0ff)
 */
#घोषणा MT9M111_CHIP_VERSION		0x000
#घोषणा MT9M111_ROW_START		0x001
#घोषणा MT9M111_COLUMN_START		0x002
#घोषणा MT9M111_WINDOW_HEIGHT		0x003
#घोषणा MT9M111_WINDOW_WIDTH		0x004
#घोषणा MT9M111_HORIZONTAL_BLANKING_B	0x005
#घोषणा MT9M111_VERTICAL_BLANKING_B	0x006
#घोषणा MT9M111_HORIZONTAL_BLANKING_A	0x007
#घोषणा MT9M111_VERTICAL_BLANKING_A	0x008
#घोषणा MT9M111_SHUTTER_WIDTH		0x009
#घोषणा MT9M111_ROW_SPEED		0x00a
#घोषणा MT9M111_EXTRA_DELAY		0x00b
#घोषणा MT9M111_SHUTTER_DELAY		0x00c
#घोषणा MT9M111_RESET			0x00d
#घोषणा MT9M111_READ_MODE_B		0x020
#घोषणा MT9M111_READ_MODE_A		0x021
#घोषणा MT9M111_FLASH_CONTROL		0x023
#घोषणा MT9M111_GREEN1_GAIN		0x02b
#घोषणा MT9M111_BLUE_GAIN		0x02c
#घोषणा MT9M111_RED_GAIN		0x02d
#घोषणा MT9M111_GREEN2_GAIN		0x02e
#घोषणा MT9M111_GLOBAL_GAIN		0x02f
#घोषणा MT9M111_CONTEXT_CONTROL		0x0c8
#घोषणा MT9M111_PAGE_MAP		0x0f0
#घोषणा MT9M111_BYTE_WISE_ADDR		0x0f1

#घोषणा MT9M111_RESET_SYNC_CHANGES	(1 << 15)
#घोषणा MT9M111_RESET_RESTART_BAD_FRAME	(1 << 9)
#घोषणा MT9M111_RESET_SHOW_BAD_FRAMES	(1 << 8)
#घोषणा MT9M111_RESET_RESET_SOC		(1 << 5)
#घोषणा MT9M111_RESET_OUTPUT_DISABLE	(1 << 4)
#घोषणा MT9M111_RESET_CHIP_ENABLE	(1 << 3)
#घोषणा MT9M111_RESET_ANALOG_STANDBY	(1 << 2)
#घोषणा MT9M111_RESET_RESTART_FRAME	(1 << 1)
#घोषणा MT9M111_RESET_RESET_MODE	(1 << 0)

#घोषणा MT9M111_RM_FULL_POWER_RD	(0 << 10)
#घोषणा MT9M111_RM_LOW_POWER_RD		(1 << 10)
#घोषणा MT9M111_RM_COL_SKIP_4X		(1 << 5)
#घोषणा MT9M111_RM_ROW_SKIP_4X		(1 << 4)
#घोषणा MT9M111_RM_COL_SKIP_2X		(1 << 3)
#घोषणा MT9M111_RM_ROW_SKIP_2X		(1 << 2)
#घोषणा MT9M111_RMB_MIRROR_COLS		(1 << 1)
#घोषणा MT9M111_RMB_MIRROR_ROWS		(1 << 0)
#घोषणा MT9M111_CTXT_CTRL_RESTART	(1 << 15)
#घोषणा MT9M111_CTXT_CTRL_DEFECTCOR_B	(1 << 12)
#घोषणा MT9M111_CTXT_CTRL_RESIZE_B	(1 << 10)
#घोषणा MT9M111_CTXT_CTRL_CTRL2_B	(1 << 9)
#घोषणा MT9M111_CTXT_CTRL_GAMMA_B	(1 << 8)
#घोषणा MT9M111_CTXT_CTRL_XENON_EN	(1 << 7)
#घोषणा MT9M111_CTXT_CTRL_READ_MODE_B	(1 << 3)
#घोषणा MT9M111_CTXT_CTRL_LED_FLASH_EN	(1 << 2)
#घोषणा MT9M111_CTXT_CTRL_VBLANK_SEL_B	(1 << 1)
#घोषणा MT9M111_CTXT_CTRL_HBLANK_SEL_B	(1 << 0)

/*
 * Colorpipe रेजिस्टर addresses (0x100..0x1ff)
 */
#घोषणा MT9M111_OPER_MODE_CTRL		0x106
#घोषणा MT9M111_OUTPUT_FORMAT_CTRL	0x108
#घोषणा MT9M111_TPG_CTRL		0x148
#घोषणा MT9M111_REDUCER_XZOOM_B		0x1a0
#घोषणा MT9M111_REDUCER_XSIZE_B		0x1a1
#घोषणा MT9M111_REDUCER_YZOOM_B		0x1a3
#घोषणा MT9M111_REDUCER_YSIZE_B		0x1a4
#घोषणा MT9M111_REDUCER_XZOOM_A		0x1a6
#घोषणा MT9M111_REDUCER_XSIZE_A		0x1a7
#घोषणा MT9M111_REDUCER_YZOOM_A		0x1a9
#घोषणा MT9M111_REDUCER_YSIZE_A		0x1aa
#घोषणा MT9M111_EFFECTS_MODE		0x1e2

#घोषणा MT9M111_OUTPUT_FORMAT_CTRL2_A	0x13a
#घोषणा MT9M111_OUTPUT_FORMAT_CTRL2_B	0x19b

#घोषणा MT9M111_OPMODE_AUTOEXPO_EN	(1 << 14)
#घोषणा MT9M111_OPMODE_AUTOWHITEBAL_EN	(1 << 1)
#घोषणा MT9M111_OUTFMT_FLIP_BAYER_COL	(1 << 9)
#घोषणा MT9M111_OUTFMT_FLIP_BAYER_ROW	(1 << 8)
#घोषणा MT9M111_OUTFMT_PROCESSED_BAYER	(1 << 14)
#घोषणा MT9M111_OUTFMT_BYPASS_IFP	(1 << 10)
#घोषणा MT9M111_OUTFMT_INV_PIX_CLOCK	(1 << 9)
#घोषणा MT9M111_OUTFMT_RGB		(1 << 8)
#घोषणा MT9M111_OUTFMT_RGB565		(0 << 6)
#घोषणा MT9M111_OUTFMT_RGB555		(1 << 6)
#घोषणा MT9M111_OUTFMT_RGB444x		(2 << 6)
#घोषणा MT9M111_OUTFMT_RGBx444		(3 << 6)
#घोषणा MT9M111_OUTFMT_TST_RAMP_OFF	(0 << 4)
#घोषणा MT9M111_OUTFMT_TST_RAMP_COL	(1 << 4)
#घोषणा MT9M111_OUTFMT_TST_RAMP_ROW	(2 << 4)
#घोषणा MT9M111_OUTFMT_TST_RAMP_FRAME	(3 << 4)
#घोषणा MT9M111_OUTFMT_SHIFT_3_UP	(1 << 3)
#घोषणा MT9M111_OUTFMT_AVG_CHROMA	(1 << 2)
#घोषणा MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN	(1 << 1)
#घोषणा MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B	(1 << 0)
#घोषणा MT9M111_TPG_SEL_MASK		GENMASK(2, 0)
#घोषणा MT9M111_EFFECTS_MODE_MASK	GENMASK(2, 0)
#घोषणा MT9M111_RM_PWR_MASK		BIT(10)
#घोषणा MT9M111_RM_SKIP2_MASK		GENMASK(3, 2)

/*
 * Camera control रेजिस्टर addresses (0x200..0x2ff not implemented)
 */

#घोषणा reg_पढ़ो(reg) mt9m111_reg_पढ़ो(client, MT9M111_##reg)
#घोषणा reg_ग_लिखो(reg, val) mt9m111_reg_ग_लिखो(client, MT9M111_##reg, (val))
#घोषणा reg_set(reg, val) mt9m111_reg_set(client, MT9M111_##reg, (val))
#घोषणा reg_clear(reg, val) mt9m111_reg_clear(client, MT9M111_##reg, (val))
#घोषणा reg_mask(reg, val, mask) mt9m111_reg_mask(client, MT9M111_##reg, \
		(val), (mask))

#घोषणा MT9M111_MIN_DARK_ROWS	8
#घोषणा MT9M111_MIN_DARK_COLS	26
#घोषणा MT9M111_MAX_HEIGHT	1024
#घोषणा MT9M111_MAX_WIDTH	1280

काष्ठा mt9m111_context अणु
	u16 पढ़ो_mode;
	u16 blanking_h;
	u16 blanking_v;
	u16 reducer_xzoom;
	u16 reducer_yzoom;
	u16 reducer_xsize;
	u16 reducer_ysize;
	u16 output_fmt_ctrl2;
	u16 control;
पूर्ण;

अटल काष्ठा mt9m111_context context_a = अणु
	.पढ़ो_mode		= MT9M111_READ_MODE_A,
	.blanking_h		= MT9M111_HORIZONTAL_BLANKING_A,
	.blanking_v		= MT9M111_VERTICAL_BLANKING_A,
	.reducer_xzoom		= MT9M111_REDUCER_XZOOM_A,
	.reducer_yzoom		= MT9M111_REDUCER_YZOOM_A,
	.reducer_xsize		= MT9M111_REDUCER_XSIZE_A,
	.reducer_ysize		= MT9M111_REDUCER_YSIZE_A,
	.output_fmt_ctrl2	= MT9M111_OUTPUT_FORMAT_CTRL2_A,
	.control		= MT9M111_CTXT_CTRL_RESTART,
पूर्ण;

अटल काष्ठा mt9m111_context context_b = अणु
	.पढ़ो_mode		= MT9M111_READ_MODE_B,
	.blanking_h		= MT9M111_HORIZONTAL_BLANKING_B,
	.blanking_v		= MT9M111_VERTICAL_BLANKING_B,
	.reducer_xzoom		= MT9M111_REDUCER_XZOOM_B,
	.reducer_yzoom		= MT9M111_REDUCER_YZOOM_B,
	.reducer_xsize		= MT9M111_REDUCER_XSIZE_B,
	.reducer_ysize		= MT9M111_REDUCER_YSIZE_B,
	.output_fmt_ctrl2	= MT9M111_OUTPUT_FORMAT_CTRL2_B,
	.control		= MT9M111_CTXT_CTRL_RESTART |
		MT9M111_CTXT_CTRL_DEFECTCOR_B | MT9M111_CTXT_CTRL_RESIZE_B |
		MT9M111_CTXT_CTRL_CTRL2_B | MT9M111_CTXT_CTRL_GAMMA_B |
		MT9M111_CTXT_CTRL_READ_MODE_B | MT9M111_CTXT_CTRL_VBLANK_SEL_B |
		MT9M111_CTXT_CTRL_HBLANK_SEL_B,
पूर्ण;

/* MT9M111 has only one fixed colorspace per pixelcode */
काष्ठा mt9m111_datafmt अणु
	u32	code;
	क्रमागत v4l2_colorspace		colorspace;
पूर्ण;

अटल स्थिर काष्ठा mt9m111_datafmt mt9m111_colour_fmts[] = अणु
	अणुMEDIA_BUS_FMT_YUYV8_2X8, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_YVYU8_2X8, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_UYVY8_2X8, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_VYUY8_2X8, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_RGB555_2X8_PADHI_LE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_RGB555_2X8_PADHI_BE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_RGB565_2X8_LE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_RGB565_2X8_BE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_BGR565_2X8_LE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_BGR565_2X8_BE, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_SBGGR8_1X8, V4L2_COLORSPACE_SRGBपूर्ण,
	अणुMEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE, V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

क्रमागत mt9m111_mode_id अणु
	MT9M111_MODE_SXGA_8FPS,
	MT9M111_MODE_SXGA_15FPS,
	MT9M111_MODE_QSXGA_30FPS,
	MT9M111_NUM_MODES,
पूर्ण;

काष्ठा mt9m111_mode_info अणु
	अचिन्हित पूर्णांक sensor_w;
	अचिन्हित पूर्णांक sensor_h;
	अचिन्हित पूर्णांक max_image_w;
	अचिन्हित पूर्णांक max_image_h;
	अचिन्हित पूर्णांक max_fps;
	अचिन्हित पूर्णांक reg_val;
	अचिन्हित पूर्णांक reg_mask;
पूर्ण;

काष्ठा mt9m111 अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl *gain;
	काष्ठा mt9m111_context *ctx;
	काष्ठा v4l2_rect rect;	/* cropping rectangle */
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक width;	/* output */
	अचिन्हित पूर्णांक height;	/* sizes */
	काष्ठा v4l2_fract frame_पूर्णांकerval;
	स्थिर काष्ठा mt9m111_mode_info *current_mode;
	काष्ठा mutex घातer_lock; /* lock to protect घातer_count */
	पूर्णांक घातer_count;
	स्थिर काष्ठा mt9m111_datafmt *fmt;
	पूर्णांक lastpage;	/* PageMap cache value */
	काष्ठा regulator *regulator;
	bool is_streaming;
	/* user poपूर्णांक of view - 0: falling 1: rising edge */
	अचिन्हित पूर्णांक pclk_sample:1;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_pad pad;
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा mt9m111_mode_info mt9m111_mode_data[MT9M111_NUM_MODES] = अणु
	[MT9M111_MODE_SXGA_8FPS] = अणु
		.sensor_w = 1280,
		.sensor_h = 1024,
		.max_image_w = 1280,
		.max_image_h = 1024,
		.max_fps = 8,
		.reg_val = MT9M111_RM_LOW_POWER_RD,
		.reg_mask = MT9M111_RM_PWR_MASK | MT9M111_RM_SKIP2_MASK,
	पूर्ण,
	[MT9M111_MODE_SXGA_15FPS] = अणु
		.sensor_w = 1280,
		.sensor_h = 1024,
		.max_image_w = 1280,
		.max_image_h = 1024,
		.max_fps = 15,
		.reg_val = MT9M111_RM_FULL_POWER_RD,
		.reg_mask = MT9M111_RM_PWR_MASK | MT9M111_RM_SKIP2_MASK,
	पूर्ण,
	[MT9M111_MODE_QSXGA_30FPS] = अणु
		.sensor_w = 1280,
		.sensor_h = 1024,
		.max_image_w = 640,
		.max_image_h = 512,
		.max_fps = 30,
		.reg_val = MT9M111_RM_LOW_POWER_RD | MT9M111_RM_COL_SKIP_2X |
			   MT9M111_RM_ROW_SKIP_2X,
		.reg_mask = MT9M111_RM_PWR_MASK | MT9M111_RM_SKIP2_MASK,
	पूर्ण,
पूर्ण;

/* Find a data क्रमmat by a pixel code */
अटल स्थिर काष्ठा mt9m111_datafmt *mt9m111_find_datafmt(काष्ठा mt9m111 *mt9m111,
						u32 code)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(mt9m111_colour_fmts); i++)
		अगर (mt9m111_colour_fmts[i].code == code)
			वापस mt9m111_colour_fmts + i;

	वापस mt9m111->fmt;
पूर्ण

अटल काष्ठा mt9m111 *to_mt9m111(स्थिर काष्ठा i2c_client *client)
अणु
	वापस container_of(i2c_get_clientdata(client), काष्ठा mt9m111, subdev);
पूर्ण

अटल पूर्णांक reg_page_map_set(काष्ठा i2c_client *client, स्थिर u16 reg)
अणु
	पूर्णांक ret;
	u16 page;
	काष्ठा mt9m111 *mt9m111 = to_mt9m111(client);

	page = (reg >> 8);
	अगर (page == mt9m111->lastpage)
		वापस 0;
	अगर (page > 2)
		वापस -EINVAL;

	ret = i2c_smbus_ग_लिखो_word_swapped(client, MT9M111_PAGE_MAP, page);
	अगर (!ret)
		mt9m111->lastpage = page;
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_reg_पढ़ो(काष्ठा i2c_client *client, स्थिर u16 reg)
अणु
	पूर्णांक ret;

	ret = reg_page_map_set(client, reg);
	अगर (!ret)
		ret = i2c_smbus_पढ़ो_word_swapped(client, reg & 0xff);

	dev_dbg(&client->dev, "read  reg.%03x -> %04x\n", reg, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_reg_ग_लिखो(काष्ठा i2c_client *client, स्थिर u16 reg,
			     स्थिर u16 data)
अणु
	पूर्णांक ret;

	ret = reg_page_map_set(client, reg);
	अगर (!ret)
		ret = i2c_smbus_ग_लिखो_word_swapped(client, reg & 0xff, data);
	dev_dbg(&client->dev, "write reg.%03x = %04x -> %d\n", reg, data, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_reg_set(काष्ठा i2c_client *client, स्थिर u16 reg,
			   स्थिर u16 data)
अणु
	पूर्णांक ret;

	ret = mt9m111_reg_पढ़ो(client, reg);
	अगर (ret >= 0)
		ret = mt9m111_reg_ग_लिखो(client, reg, ret | data);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_reg_clear(काष्ठा i2c_client *client, स्थिर u16 reg,
			     स्थिर u16 data)
अणु
	पूर्णांक ret;

	ret = mt9m111_reg_पढ़ो(client, reg);
	अगर (ret >= 0)
		ret = mt9m111_reg_ग_लिखो(client, reg, ret & ~data);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_reg_mask(काष्ठा i2c_client *client, स्थिर u16 reg,
			    स्थिर u16 data, स्थिर u16 mask)
अणु
	पूर्णांक ret;

	ret = mt9m111_reg_पढ़ो(client, reg);
	अगर (ret >= 0)
		ret = mt9m111_reg_ग_लिखो(client, reg, (ret & ~mask) | data);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_set_context(काष्ठा mt9m111 *mt9m111,
			       काष्ठा mt9m111_context *ctx)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	वापस reg_ग_लिखो(CONTEXT_CONTROL, ctx->control);
पूर्ण

अटल पूर्णांक mt9m111_setup_rect_ctx(काष्ठा mt9m111 *mt9m111,
			काष्ठा mt9m111_context *ctx, काष्ठा v4l2_rect *rect,
			अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	पूर्णांक ret = mt9m111_reg_ग_लिखो(client, ctx->reducer_xzoom, rect->width);
	अगर (!ret)
		ret = mt9m111_reg_ग_लिखो(client, ctx->reducer_yzoom, rect->height);
	अगर (!ret)
		ret = mt9m111_reg_ग_लिखो(client, ctx->reducer_xsize, width);
	अगर (!ret)
		ret = mt9m111_reg_ग_लिखो(client, ctx->reducer_ysize, height);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_setup_geometry(काष्ठा mt9m111 *mt9m111, काष्ठा v4l2_rect *rect,
			पूर्णांक width, पूर्णांक height, u32 code)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	पूर्णांक ret;

	ret = reg_ग_लिखो(COLUMN_START, rect->left);
	अगर (!ret)
		ret = reg_ग_लिखो(ROW_START, rect->top);

	अगर (!ret)
		ret = reg_ग_लिखो(WINDOW_WIDTH, rect->width);
	अगर (!ret)
		ret = reg_ग_लिखो(WINDOW_HEIGHT, rect->height);

	अगर (code != MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE) अणु
		/* IFP in use, करोwn-scaling possible */
		अगर (!ret)
			ret = mt9m111_setup_rect_ctx(mt9m111, &context_b,
						     rect, width, height);
		अगर (!ret)
			ret = mt9m111_setup_rect_ctx(mt9m111, &context_a,
						     rect, width, height);
	पूर्ण

	dev_dbg(&client->dev, "%s(%x): %ux%u@%u:%u -> %ux%u = %d\n",
		__func__, code, rect->width, rect->height, rect->left, rect->top,
		width, height, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_enable(काष्ठा mt9m111 *mt9m111)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	वापस reg_ग_लिखो(RESET, MT9M111_RESET_CHIP_ENABLE);
पूर्ण

अटल पूर्णांक mt9m111_reset(काष्ठा mt9m111 *mt9m111)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	पूर्णांक ret;

	ret = reg_set(RESET, MT9M111_RESET_RESET_MODE);
	अगर (!ret)
		ret = reg_set(RESET, MT9M111_RESET_RESET_SOC);
	अगर (!ret)
		ret = reg_clear(RESET, MT9M111_RESET_RESET_MODE
				| MT9M111_RESET_RESET_SOC);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_set_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m111 *mt9m111 = to_mt9m111(client);
	काष्ठा v4l2_rect rect = sel->r;
	पूर्णांक width, height;
	पूर्णांक ret, align = 0;

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	अगर (mt9m111->fmt->code == MEDIA_BUS_FMT_SBGGR8_1X8 ||
	    mt9m111->fmt->code == MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE) अणु
		/* Bayer क्रमmat - even size lengths */
		align = 1;
		/* Let the user play with the starting pixel */
	पूर्ण

	/* FIXME: the datasheet करोesn't specअगरy minimum sizes */
	v4l_bound_align_image(&rect.width, 2, MT9M111_MAX_WIDTH, align,
			      &rect.height, 2, MT9M111_MAX_HEIGHT, align, 0);
	rect.left = clamp(rect.left, MT9M111_MIN_DARK_COLS,
			  MT9M111_MIN_DARK_COLS + MT9M111_MAX_WIDTH -
			  (__s32)rect.width);
	rect.top = clamp(rect.top, MT9M111_MIN_DARK_ROWS,
			 MT9M111_MIN_DARK_ROWS + MT9M111_MAX_HEIGHT -
			 (__s32)rect.height);

	width = min(mt9m111->width, rect.width);
	height = min(mt9m111->height, rect.height);

	ret = mt9m111_setup_geometry(mt9m111, &rect, width, height, mt9m111->fmt->code);
	अगर (!ret) अणु
		mt9m111->rect = rect;
		mt9m111->width = width;
		mt9m111->height = height;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_get_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m111 *mt9m111 = to_mt9m111(client);

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = MT9M111_MIN_DARK_COLS;
		sel->r.top = MT9M111_MIN_DARK_ROWS;
		sel->r.width = MT9M111_MAX_WIDTH;
		sel->r.height = MT9M111_MAX_HEIGHT;
		वापस 0;
	हाल V4L2_SEL_TGT_CROP:
		sel->r = mt9m111->rect;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mt9m111_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा mt9m111 *mt9m111 = container_of(sd, काष्ठा mt9m111, subdev);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		क्रमmat->क्रमmat = *mf;
		वापस 0;
#अन्यथा
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण

	mf->width	= mt9m111->width;
	mf->height	= mt9m111->height;
	mf->code	= mt9m111->fmt->code;
	mf->colorspace	= mt9m111->fmt->colorspace;
	mf->field	= V4L2_FIELD_NONE;
	mf->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	mf->quantization	= V4L2_QUANTIZATION_DEFAULT;
	mf->xfer_func	= V4L2_XFER_FUNC_DEFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m111_set_pixfmt(काष्ठा mt9m111 *mt9m111,
			      u32 code)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	u16 data_outfmt2, mask_outfmt2 = MT9M111_OUTFMT_PROCESSED_BAYER |
		MT9M111_OUTFMT_BYPASS_IFP | MT9M111_OUTFMT_RGB |
		MT9M111_OUTFMT_RGB565 | MT9M111_OUTFMT_RGB555 |
		MT9M111_OUTFMT_RGB444x | MT9M111_OUTFMT_RGBx444 |
		MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN |
		MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
	पूर्णांक ret;

	चयन (code) अणु
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		data_outfmt2 = MT9M111_OUTFMT_PROCESSED_BAYER |
			MT9M111_OUTFMT_RGB;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE:
		data_outfmt2 = MT9M111_OUTFMT_BYPASS_IFP | MT9M111_OUTFMT_RGB;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB555 |
			MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB555;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB565 |
			MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB565_2X8_BE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB565;
		अवरोध;
	हाल MEDIA_BUS_FMT_BGR565_2X8_BE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB565 |
			MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
		अवरोध;
	हाल MEDIA_BUS_FMT_BGR565_2X8_LE:
		data_outfmt2 = MT9M111_OUTFMT_RGB | MT9M111_OUTFMT_RGB565 |
			MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN |
			MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		data_outfmt2 = 0;
		अवरोध;
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
		data_outfmt2 = MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		data_outfmt2 = MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN;
		अवरोध;
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
		data_outfmt2 = MT9M111_OUTFMT_SWAP_YCbCr_C_Y_RGB_EVEN |
			MT9M111_OUTFMT_SWAP_YCbCr_Cb_Cr_RGB_R_B;
		अवरोध;
	शेष:
		dev_err(&client->dev, "Pixel format not handled: %x\n", code);
		वापस -EINVAL;
	पूर्ण

	/* receiver samples on falling edge, chip-hw शेष is rising */
	अगर (mt9m111->pclk_sample == 0)
		mask_outfmt2 |= MT9M111_OUTFMT_INV_PIX_CLOCK;

	ret = mt9m111_reg_mask(client, context_a.output_fmt_ctrl2,
			       data_outfmt2, mask_outfmt2);
	अगर (!ret)
		ret = mt9m111_reg_mask(client, context_b.output_fmt_ctrl2,
				       data_outfmt2, mask_outfmt2);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9m111 *mt9m111 = container_of(sd, काष्ठा mt9m111, subdev);
	स्थिर काष्ठा mt9m111_datafmt *fmt;
	काष्ठा v4l2_rect *rect = &mt9m111->rect;
	bool bayer;
	पूर्णांक ret;

	अगर (mt9m111->is_streaming)
		वापस -EBUSY;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	fmt = mt9m111_find_datafmt(mt9m111, mf->code);

	bayer = fmt->code == MEDIA_BUS_FMT_SBGGR8_1X8 ||
		fmt->code == MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE;

	/*
	 * With Bayer क्रमmat enक्रमce even side lengths, but let the user play
	 * with the starting pixel
	 */
	अगर (bayer) अणु
		rect->width = ALIGN(rect->width, 2);
		rect->height = ALIGN(rect->height, 2);
	पूर्ण

	अगर (fmt->code == MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE) अणु
		/* IFP bypass mode, no scaling */
		mf->width = rect->width;
		mf->height = rect->height;
	पूर्ण अन्यथा अणु
		/* No upscaling */
		अगर (mf->width > rect->width)
			mf->width = rect->width;
		अगर (mf->height > rect->height)
			mf->height = rect->height;
	पूर्ण

	dev_dbg(&client->dev, "%s(): %ux%u, code=%x\n", __func__,
		mf->width, mf->height, fmt->code);

	mf->code = fmt->code;
	mf->colorspace = fmt->colorspace;
	mf->field	= V4L2_FIELD_NONE;
	mf->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	mf->quantization	= V4L2_QUANTIZATION_DEFAULT;
	mf->xfer_func	= V4L2_XFER_FUNC_DEFAULT;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cfg->try_fmt = *mf;
		वापस 0;
	पूर्ण

	ret = mt9m111_setup_geometry(mt9m111, rect, mf->width, mf->height, mf->code);
	अगर (!ret)
		ret = mt9m111_set_pixfmt(mt9m111, mf->code);
	अगर (!ret) अणु
		mt9m111->width	= mf->width;
		mt9m111->height	= mf->height;
		mt9m111->fmt	= fmt;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mt9m111_mode_info *
mt9m111_find_mode(काष्ठा mt9m111 *mt9m111, अचिन्हित पूर्णांक req_fps,
		  अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	स्थिर काष्ठा mt9m111_mode_info *mode;
	काष्ठा v4l2_rect *sensor_rect = &mt9m111->rect;
	अचिन्हित पूर्णांक gap, gap_best = (अचिन्हित पूर्णांक) -1;
	पूर्णांक i, best_gap_idx = MT9M111_MODE_SXGA_15FPS;
	bool skip_30fps = false;

	/*
	 * The fps selection is based on the row, column skipping mechanism.
	 * So ensure that the sensor winकरोw is set to शेष अन्यथा the fps
	 * aren't calculated correctly within the sensor hw.
	 */
	अगर (sensor_rect->width != MT9M111_MAX_WIDTH ||
	    sensor_rect->height != MT9M111_MAX_HEIGHT) अणु
		dev_info(mt9m111->subdev.dev,
			 "Framerate selection is not supported for cropped "
			 "images\n");
		वापस शून्य;
	पूर्ण

	/* 30fps only supported क्रम images not exceeding 640x512 */
	अगर (width > MT9M111_MAX_WIDTH / 2 || height > MT9M111_MAX_HEIGHT / 2) अणु
		dev_dbg(mt9m111->subdev.dev,
			"Framerates > 15fps are supported only for images "
			"not exceeding 640x512\n");
		skip_30fps = true;
	पूर्ण

	/* find best matched fps */
	क्रम (i = 0; i < MT9M111_NUM_MODES; i++) अणु
		अचिन्हित पूर्णांक fps = mt9m111_mode_data[i].max_fps;

		अगर (fps == 30 && skip_30fps)
			जारी;

		gap = असल(fps - req_fps);
		अगर (gap < gap_best) अणु
			best_gap_idx = i;
			gap_best = gap;
		पूर्ण
	पूर्ण

	/*
	 * Use context a/b शेष timing values instead of calculate blanking
	 * timing values.
	 */
	mode = &mt9m111_mode_data[best_gap_idx];
	mt9m111->ctx = (best_gap_idx == MT9M111_MODE_QSXGA_30FPS) ? &context_a :
								    &context_b;
	वापस mode;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक mt9m111_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक val;

	अगर (reg->reg > 0x2ff)
		वापस -EINVAL;

	val = mt9m111_reg_पढ़ो(client, reg->reg);
	reg->size = 2;
	reg->val = (u64)val;

	अगर (reg->val > 0xffff)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m111_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg > 0x2ff)
		वापस -EINVAL;

	अगर (mt9m111_reg_ग_लिखो(client, reg->reg, reg->val) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mt9m111_set_flip(काष्ठा mt9m111 *mt9m111, पूर्णांक flip, पूर्णांक mask)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	पूर्णांक ret;

	अगर (flip)
		ret = mt9m111_reg_set(client, mt9m111->ctx->पढ़ो_mode, mask);
	अन्यथा
		ret = mt9m111_reg_clear(client, mt9m111->ctx->पढ़ो_mode, mask);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_get_global_gain(काष्ठा mt9m111 *mt9m111)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	पूर्णांक data;

	data = reg_पढ़ो(GLOBAL_GAIN);
	अगर (data >= 0)
		वापस (data & 0x2f) * (1 << ((data >> 10) & 1)) *
			(1 << ((data >> 9) & 1));
	वापस data;
पूर्ण

अटल पूर्णांक mt9m111_set_global_gain(काष्ठा mt9m111 *mt9m111, पूर्णांक gain)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	u16 val;

	अगर (gain > 63 * 2 * 2)
		वापस -EINVAL;

	अगर ((gain >= 64 * 2) && (gain < 63 * 2 * 2))
		val = (1 << 10) | (1 << 9) | (gain / 4);
	अन्यथा अगर ((gain >= 64) && (gain < 64 * 2))
		val = (1 << 9) | (gain / 2);
	अन्यथा
		val = gain;

	वापस reg_ग_लिखो(GLOBAL_GAIN, val);
पूर्ण

अटल पूर्णांक mt9m111_set_स्वतःexposure(काष्ठा mt9m111 *mt9m111, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);

	अगर (val == V4L2_EXPOSURE_AUTO)
		वापस reg_set(OPER_MODE_CTRL, MT9M111_OPMODE_AUTOEXPO_EN);
	वापस reg_clear(OPER_MODE_CTRL, MT9M111_OPMODE_AUTOEXPO_EN);
पूर्ण

अटल पूर्णांक mt9m111_set_स्वतःwhitebalance(काष्ठा mt9m111 *mt9m111, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);

	अगर (on)
		वापस reg_set(OPER_MODE_CTRL, MT9M111_OPMODE_AUTOWHITEBAL_EN);
	वापस reg_clear(OPER_MODE_CTRL, MT9M111_OPMODE_AUTOWHITEBAL_EN);
पूर्ण

अटल स्थिर अक्षर * स्थिर mt9m111_test_pattern_menu[] = अणु
	"Disabled",
	"Vertical monochrome gradient",
	"Flat color type 1",
	"Flat color type 2",
	"Flat color type 3",
	"Flat color type 4",
	"Flat color type 5",
	"Color bar",
पूर्ण;

अटल पूर्णांक mt9m111_set_test_pattern(काष्ठा mt9m111 *mt9m111, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);

	वापस mt9m111_reg_mask(client, MT9M111_TPG_CTRL, val,
				MT9M111_TPG_SEL_MASK);
पूर्ण

अटल पूर्णांक mt9m111_set_colorfx(काष्ठा mt9m111 *mt9m111, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	अटल स्थिर काष्ठा v4l2_control colorfx[] = अणु
		अणु V4L2_COLORFX_NONE,		0 पूर्ण,
		अणु V4L2_COLORFX_BW,		1 पूर्ण,
		अणु V4L2_COLORFX_SEPIA,		2 पूर्ण,
		अणु V4L2_COLORFX_NEGATIVE,	3 पूर्ण,
		अणु V4L2_COLORFX_SOLARIZATION,	4 पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(colorfx); i++) अणु
		अगर (colorfx[i].id == val) अणु
			वापस mt9m111_reg_mask(client, MT9M111_EFFECTS_MODE,
						colorfx[i].value,
						MT9M111_EFFECTS_MODE_MASK);
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mt9m111_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9m111 *mt9m111 = container_of(ctrl->handler,
					       काष्ठा mt9m111, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		वापस mt9m111_set_flip(mt9m111, ctrl->val,
					MT9M111_RMB_MIRROR_ROWS);
	हाल V4L2_CID_HFLIP:
		वापस mt9m111_set_flip(mt9m111, ctrl->val,
					MT9M111_RMB_MIRROR_COLS);
	हाल V4L2_CID_GAIN:
		वापस mt9m111_set_global_gain(mt9m111, ctrl->val);
	हाल V4L2_CID_EXPOSURE_AUTO:
		वापस mt9m111_set_स्वतःexposure(mt9m111, ctrl->val);
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		वापस mt9m111_set_स्वतःwhitebalance(mt9m111, ctrl->val);
	हाल V4L2_CID_TEST_PATTERN:
		वापस mt9m111_set_test_pattern(mt9m111, ctrl->val);
	हाल V4L2_CID_COLORFX:
		वापस mt9m111_set_colorfx(mt9m111, ctrl->val);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mt9m111_suspend(काष्ठा mt9m111 *mt9m111)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	पूर्णांक ret;

	v4l2_ctrl_s_ctrl(mt9m111->gain, mt9m111_get_global_gain(mt9m111));

	ret = reg_set(RESET, MT9M111_RESET_RESET_MODE);
	अगर (!ret)
		ret = reg_set(RESET, MT9M111_RESET_RESET_SOC |
			      MT9M111_RESET_OUTPUT_DISABLE |
			      MT9M111_RESET_ANALOG_STANDBY);
	अगर (!ret)
		ret = reg_clear(RESET, MT9M111_RESET_CHIP_ENABLE);

	वापस ret;
पूर्ण

अटल व्योम mt9m111_restore_state(काष्ठा mt9m111 *mt9m111)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);

	mt9m111_set_context(mt9m111, mt9m111->ctx);
	mt9m111_set_pixfmt(mt9m111, mt9m111->fmt->code);
	mt9m111_setup_geometry(mt9m111, &mt9m111->rect,
			mt9m111->width, mt9m111->height, mt9m111->fmt->code);
	v4l2_ctrl_handler_setup(&mt9m111->hdl);
	mt9m111_reg_mask(client, mt9m111->ctx->पढ़ो_mode,
			 mt9m111->current_mode->reg_val,
			 mt9m111->current_mode->reg_mask);
पूर्ण

अटल पूर्णांक mt9m111_resume(काष्ठा mt9m111 *mt9m111)
अणु
	पूर्णांक ret = mt9m111_enable(mt9m111);
	अगर (!ret)
		ret = mt9m111_reset(mt9m111);
	अगर (!ret)
		mt9m111_restore_state(mt9m111);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_init(काष्ठा mt9m111 *mt9m111)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	पूर्णांक ret;

	ret = mt9m111_enable(mt9m111);
	अगर (!ret)
		ret = mt9m111_reset(mt9m111);
	अगर (!ret)
		ret = mt9m111_set_context(mt9m111, mt9m111->ctx);
	अगर (ret)
		dev_err(&client->dev, "mt9m111 init failed: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_घातer_on(काष्ठा mt9m111 *mt9m111)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&mt9m111->subdev);
	पूर्णांक ret;

	ret = clk_prepare_enable(mt9m111->clk);
	अगर (ret < 0)
		वापस ret;

	ret = regulator_enable(mt9m111->regulator);
	अगर (ret < 0)
		जाओ out_clk_disable;

	ret = mt9m111_resume(mt9m111);
	अगर (ret < 0)
		जाओ out_regulator_disable;

	वापस 0;

out_regulator_disable:
	regulator_disable(mt9m111->regulator);

out_clk_disable:
	clk_disable_unprepare(mt9m111->clk);

	dev_err(&client->dev, "Failed to resume the sensor: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम mt9m111_घातer_off(काष्ठा mt9m111 *mt9m111)
अणु
	mt9m111_suspend(mt9m111);
	regulator_disable(mt9m111->regulator);
	clk_disable_unprepare(mt9m111->clk);
पूर्ण

अटल पूर्णांक mt9m111_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा mt9m111 *mt9m111 = container_of(sd, काष्ठा mt9m111, subdev);
	पूर्णांक ret = 0;

	mutex_lock(&mt9m111->घातer_lock);

	/*
	 * If the घातer count is modअगरied from 0 to != 0 or from != 0 to 0,
	 * update the घातer state.
	 */
	अगर (mt9m111->घातer_count == !on) अणु
		अगर (on)
			ret = mt9m111_घातer_on(mt9m111);
		अन्यथा
			mt9m111_घातer_off(mt9m111);
	पूर्ण

	अगर (!ret) अणु
		/* Update the घातer count. */
		mt9m111->घातer_count += on ? 1 : -1;
		WARN_ON(mt9m111->घातer_count < 0);
	पूर्ण

	mutex_unlock(&mt9m111->घातer_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mt9m111_ctrl_ops = अणु
	.s_ctrl = mt9m111_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9m111_subdev_core_ops = अणु
	.s_घातer	= mt9m111_s_घातer,
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर	= mt9m111_g_रेजिस्टर,
	.s_रेजिस्टर	= mt9m111_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mt9m111_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा mt9m111 *mt9m111 = container_of(sd, काष्ठा mt9m111, subdev);

	fi->पूर्णांकerval = mt9m111->frame_पूर्णांकerval;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m111_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा mt9m111 *mt9m111 = container_of(sd, काष्ठा mt9m111, subdev);
	स्थिर काष्ठा mt9m111_mode_info *mode;
	काष्ठा v4l2_fract *fract = &fi->पूर्णांकerval;
	पूर्णांक fps;

	अगर (mt9m111->is_streaming)
		वापस -EBUSY;

	अगर (fi->pad != 0)
		वापस -EINVAL;

	अगर (fract->numerator == 0) अणु
		fract->denominator = 30;
		fract->numerator = 1;
	पूर्ण

	fps = DIV_ROUND_CLOSEST(fract->denominator, fract->numerator);

	/* Find best fitting mode. Do not update the mode अगर no one was found. */
	mode = mt9m111_find_mode(mt9m111, fps, mt9m111->width, mt9m111->height);
	अगर (!mode)
		वापस 0;

	अगर (mode->max_fps != fps) अणु
		fract->denominator = mode->max_fps;
		fract->numerator = 1;
	पूर्ण

	mt9m111->current_mode = mode;
	mt9m111->frame_पूर्णांकerval = fi->पूर्णांकerval;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9m111_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= ARRAY_SIZE(mt9m111_colour_fmts))
		वापस -EINVAL;

	code->code = mt9m111_colour_fmts[code->index].code;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m111_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा mt9m111 *mt9m111 = container_of(sd, काष्ठा mt9m111, subdev);

	mt9m111->is_streaming = !!enable;
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m111_init_cfg(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg)
अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	काष्ठा v4l2_mbus_framefmt *क्रमmat =
		v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);

	क्रमmat->width	= MT9M111_MAX_WIDTH;
	क्रमmat->height	= MT9M111_MAX_HEIGHT;
	क्रमmat->code	= mt9m111_colour_fmts[0].code;
	क्रमmat->colorspace	= mt9m111_colour_fmts[0].colorspace;
	क्रमmat->field	= V4L2_FIELD_NONE;
	क्रमmat->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	क्रमmat->quantization	= V4L2_QUANTIZATION_DEFAULT;
	क्रमmat->xfer_func	= V4L2_XFER_FUNC_DEFAULT;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक mt9m111_get_mbus_config(काष्ठा v4l2_subdev *sd,
				   अचिन्हित पूर्णांक pad,
				   काष्ठा v4l2_mbus_config *cfg)
अणु
	काष्ठा mt9m111 *mt9m111 = container_of(sd, काष्ठा mt9m111, subdev);

	cfg->flags = V4L2_MBUS_MASTER |
		V4L2_MBUS_HSYNC_ACTIVE_HIGH | V4L2_MBUS_VSYNC_ACTIVE_HIGH |
		V4L2_MBUS_DATA_ACTIVE_HIGH;

	cfg->flags |= mt9m111->pclk_sample ? V4L2_MBUS_PCLK_SAMPLE_RISING :
		V4L2_MBUS_PCLK_SAMPLE_FALLING;

	cfg->type = V4L2_MBUS_PARALLEL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9m111_subdev_video_ops = अणु
	.s_stream	= mt9m111_s_stream,
	.g_frame_पूर्णांकerval = mt9m111_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = mt9m111_s_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9m111_subdev_pad_ops = अणु
	.init_cfg	= mt9m111_init_cfg,
	.क्रमागत_mbus_code = mt9m111_क्रमागत_mbus_code,
	.get_selection	= mt9m111_get_selection,
	.set_selection	= mt9m111_set_selection,
	.get_fmt	= mt9m111_get_fmt,
	.set_fmt	= mt9m111_set_fmt,
	.get_mbus_config = mt9m111_get_mbus_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mt9m111_subdev_ops = अणु
	.core	= &mt9m111_subdev_core_ops,
	.video	= &mt9m111_subdev_video_ops,
	.pad	= &mt9m111_subdev_pad_ops,
पूर्ण;

/*
 * Interface active, can use i2c. If it fails, it can indeed mean, that
 * this wasn't our capture पूर्णांकerface, so, we रुको क्रम the right one
 */
अटल पूर्णांक mt9m111_video_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9m111 *mt9m111 = to_mt9m111(client);
	s32 data;
	पूर्णांक ret;

	ret = mt9m111_s_घातer(&mt9m111->subdev, 1);
	अगर (ret < 0)
		वापस ret;

	data = reg_पढ़ो(CHIP_VERSION);

	चयन (data) अणु
	हाल 0x143a: /* MT9M111 or MT9M131 */
		dev_info(&client->dev,
			"Detected a MT9M111/MT9M131 chip ID %x\n", data);
		अवरोध;
	हाल 0x148c: /* MT9M112 */
		dev_info(&client->dev, "Detected a MT9M112 chip ID %x\n", data);
		अवरोध;
	शेष:
		dev_err(&client->dev,
			"No MT9M111/MT9M112/MT9M131 chip detected register read %x\n",
			data);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	ret = mt9m111_init(mt9m111);
	अगर (ret)
		जाओ करोne;

	ret = v4l2_ctrl_handler_setup(&mt9m111->hdl);

करोne:
	mt9m111_s_घातer(&mt9m111->subdev, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_probe_fw(काष्ठा i2c_client *client, काष्ठा mt9m111 *mt9m111)
अणु
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_PARALLEL
	पूर्ण;
	काष्ठा fwnode_handle *np;
	पूर्णांक ret;

	np = fwnode_graph_get_next_endpoपूर्णांक(dev_fwnode(&client->dev), शून्य);
	अगर (!np)
		वापस -EINVAL;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(np, &bus_cfg);
	अगर (ret)
		जाओ out_put_fw;

	mt9m111->pclk_sample = !!(bus_cfg.bus.parallel.flags &
				  V4L2_MBUS_PCLK_SAMPLE_RISING);

out_put_fw:
	fwnode_handle_put(np);
	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9m111 *mt9m111;
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		वापस -EIO;
	पूर्ण

	mt9m111 = devm_kzalloc(&client->dev, माप(काष्ठा mt9m111), GFP_KERNEL);
	अगर (!mt9m111)
		वापस -ENOMEM;

	अगर (dev_fwnode(&client->dev)) अणु
		ret = mt9m111_probe_fw(client, mt9m111);
		अगर (ret)
			वापस ret;
	पूर्ण

	mt9m111->clk = devm_clk_get(&client->dev, "mclk");
	अगर (IS_ERR(mt9m111->clk))
		वापस PTR_ERR(mt9m111->clk);

	mt9m111->regulator = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(mt9m111->regulator)) अणु
		dev_err(&client->dev, "regulator not found: %ld\n",
			PTR_ERR(mt9m111->regulator));
		वापस PTR_ERR(mt9m111->regulator);
	पूर्ण

	/* Default HIGHPOWER context */
	mt9m111->ctx = &context_b;

	v4l2_i2c_subdev_init(&mt9m111->subdev, client, &mt9m111_subdev_ops);
	mt9m111->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
				 V4L2_SUBDEV_FL_HAS_EVENTS;

	v4l2_ctrl_handler_init(&mt9m111->hdl, 7);
	v4l2_ctrl_new_std(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	mt9m111->gain = v4l2_ctrl_new_std(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_GAIN, 0, 63 * 2 * 2, 1, 32);
	v4l2_ctrl_new_std_menu(&mt9m111->hdl,
			&mt9m111_ctrl_ops, V4L2_CID_EXPOSURE_AUTO, 1, 0,
			V4L2_EXPOSURE_AUTO);
	v4l2_ctrl_new_std_menu_items(&mt9m111->hdl,
			&mt9m111_ctrl_ops, V4L2_CID_TEST_PATTERN,
			ARRAY_SIZE(mt9m111_test_pattern_menu) - 1, 0, 0,
			mt9m111_test_pattern_menu);
	v4l2_ctrl_new_std_menu(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_COLORFX, V4L2_COLORFX_SOLARIZATION,
			~(BIT(V4L2_COLORFX_NONE) |
				BIT(V4L2_COLORFX_BW) |
				BIT(V4L2_COLORFX_SEPIA) |
				BIT(V4L2_COLORFX_NEGATIVE) |
				BIT(V4L2_COLORFX_SOLARIZATION)),
			V4L2_COLORFX_NONE);
	mt9m111->subdev.ctrl_handler = &mt9m111->hdl;
	अगर (mt9m111->hdl.error) अणु
		ret = mt9m111->hdl.error;
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	mt9m111->pad.flags = MEDIA_PAD_FL_SOURCE;
	mt9m111->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&mt9m111->subdev.entity, 1, &mt9m111->pad);
	अगर (ret < 0)
		जाओ out_hdlमुक्त;
#पूर्ण_अगर

	mt9m111->current_mode = &mt9m111_mode_data[MT9M111_MODE_SXGA_15FPS];
	mt9m111->frame_पूर्णांकerval.numerator = 1;
	mt9m111->frame_पूर्णांकerval.denominator = mt9m111->current_mode->max_fps;

	/* Second stage probe - when a capture adapter is there */
	mt9m111->rect.left	= MT9M111_MIN_DARK_COLS;
	mt9m111->rect.top	= MT9M111_MIN_DARK_ROWS;
	mt9m111->rect.width	= MT9M111_MAX_WIDTH;
	mt9m111->rect.height	= MT9M111_MAX_HEIGHT;
	mt9m111->width		= mt9m111->rect.width;
	mt9m111->height		= mt9m111->rect.height;
	mt9m111->fmt		= &mt9m111_colour_fmts[0];
	mt9m111->lastpage	= -1;
	mutex_init(&mt9m111->घातer_lock);

	ret = mt9m111_video_probe(client);
	अगर (ret < 0)
		जाओ out_entityclean;

	mt9m111->subdev.dev = &client->dev;
	ret = v4l2_async_रेजिस्टर_subdev(&mt9m111->subdev);
	अगर (ret < 0)
		जाओ out_entityclean;

	वापस 0;

out_entityclean:
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	media_entity_cleanup(&mt9m111->subdev.entity);
out_hdlमुक्त:
#पूर्ण_अगर
	v4l2_ctrl_handler_मुक्त(&mt9m111->hdl);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9m111_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9m111 *mt9m111 = to_mt9m111(client);

	v4l2_async_unरेजिस्टर_subdev(&mt9m111->subdev);
	media_entity_cleanup(&mt9m111->subdev.entity);
	v4l2_ctrl_handler_मुक्त(&mt9m111->hdl);

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा of_device_id mt9m111_of_match[] = अणु
	अणु .compatible = "micron,mt9m111", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt9m111_of_match);

अटल स्थिर काष्ठा i2c_device_id mt9m111_id[] = अणु
	अणु "mt9m111", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt9m111_id);

अटल काष्ठा i2c_driver mt9m111_i2c_driver = अणु
	.driver = अणु
		.name = "mt9m111",
		.of_match_table = of_match_ptr(mt9m111_of_match),
	पूर्ण,
	.probe_new	= mt9m111_probe,
	.हटाओ		= mt9m111_हटाओ,
	.id_table	= mt9m111_id,
पूर्ण;

module_i2c_driver(mt9m111_i2c_driver);

MODULE_DESCRIPTION("Micron/Aptina MT9M111/MT9M112/MT9M131 Camera driver");
MODULE_AUTHOR("Robert Jarzmik");
MODULE_LICENSE("GPL");
