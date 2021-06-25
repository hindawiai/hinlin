<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// tvp5150 - Texas Instruments TVP5150A/AM1 and TVP5151 video decoder driver
//
// Copyright (c) 2005,2006 Mauro Carvalho Chehab <mchehab@kernel.org>

#समावेश <dt-bindings/media/tvp5150.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-rect.h>

#समावेश "tvp5150_reg.h"

#घोषणा TVP5150_H_MAX		720U
#घोषणा TVP5150_V_MAX_525_60	480U
#घोषणा TVP5150_V_MAX_OTHERS	576U
#घोषणा TVP5150_MAX_CROP_LEFT	511
#घोषणा TVP5150_MAX_CROP_TOP	127
#घोषणा TVP5150_CROP_SHIFT	2
#घोषणा TVP5150_MBUS_FMT	MEDIA_BUS_FMT_UYVY8_2X8
#घोषणा TVP5150_FIELD		V4L2_FIELD_ALTERNATE
#घोषणा TVP5150_COLORSPACE	V4L2_COLORSPACE_SMPTE170M
#घोषणा TVP5150_STD_MASK	(V4L2_STD_NTSC     | \
				 V4L2_STD_NTSC_443 | \
				 V4L2_STD_PAL      | \
				 V4L2_STD_PAL_M    | \
				 V4L2_STD_PAL_N    | \
				 V4L2_STD_PAL_Nc   | \
				 V4L2_STD_SECAM)

#घोषणा TVP5150_MAX_CONNECTORS	3 /* Check dt-bindings क्रम more inक्रमmation */

MODULE_DESCRIPTION("Texas Instruments TVP5150A/TVP5150AM1/TVP5151 video decoder driver");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_LICENSE("GPL v2");


अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-2)");

#घोषणा dprपूर्णांकk0(__dev, __arg...) dev_dbg_lvl(__dev, 0, 0, __arg)

क्रमागत tvp5150_pads अणु
	TVP5150_PAD_AIP1A,
	TVP5150_PAD_AIP1B,
	TVP5150_PAD_VID_OUT,
	TVP5150_NUM_PADS
पूर्ण;

काष्ठा tvp5150_connector अणु
	काष्ठा v4l2_fwnode_connector base;
	काष्ठा media_entity ent;
	काष्ठा media_pad pad;
पूर्ण;

काष्ठा tvp5150 अणु
	काष्ठा v4l2_subdev sd;

	काष्ठा media_pad pads[TVP5150_NUM_PADS];
	काष्ठा tvp5150_connector connectors[TVP5150_MAX_CONNECTORS];
	काष्ठा tvp5150_connector *cur_connector;
	अचिन्हित पूर्णांक connectors_num;

	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_rect rect;
	काष्ठा regmap *regmap;
	पूर्णांक irq;

	v4l2_std_id norm;	/* Current set standard */
	v4l2_std_id detected_norm;
	u32 input;
	u32 output;
	u32 oe;
	पूर्णांक enable;
	bool lock;

	u16 dev_id;
	u16 rom_ver;

	क्रमागत v4l2_mbus_type mbus_type;
पूर्ण;

अटल अंतरभूत काष्ठा tvp5150 *to_tvp5150(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tvp5150, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा tvp5150, hdl)->sd;
पूर्ण

अटल पूर्णांक tvp5150_पढ़ो(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर addr)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	पूर्णांक ret, val;

	ret = regmap_पढ़ो(decoder->regmap, addr, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण

अटल व्योम dump_reg_range(काष्ठा v4l2_subdev *sd, अक्षर *s, u8 init,
				स्थिर u8 end, पूर्णांक max_line)
अणु
	u8 buf[16];
	पूर्णांक i = 0, j, len;

	अगर (max_line > 16) अणु
		dprपूर्णांकk0(sd->dev, "too much data to dump\n");
		वापस;
	पूर्ण

	क्रम (i = init; i < end; i += max_line) अणु
		len = (end - i > max_line) ? max_line : end - i;

		क्रम (j = 0; j < len; j++)
			buf[j] = tvp5150_पढ़ो(sd, i + j);

		dprपूर्णांकk0(sd->dev, "%s reg %02x = %*ph\n", s, i, len, buf);
	पूर्ण
पूर्ण

अटल पूर्णांक tvp5150_log_status(काष्ठा v4l2_subdev *sd)
अणु
	dprपूर्णांकk0(sd->dev, "tvp5150: Video input source selection #1 = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_VD_IN_SRC_SEL_1));
	dprपूर्णांकk0(sd->dev, "tvp5150: Analog channel controls = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_ANAL_CHL_CTL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Operation mode controls = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_OP_MODE_CTL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Miscellaneous controls = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_MISC_CTL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Autoswitch mask= 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_AUTOSW_MSK));
	dprपूर्णांकk0(sd->dev, "tvp5150: Color killer threshold control = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_COLOR_KIL_THSH_CTL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Luminance processing controls #1 #2 and #3 = %02x %02x %02x\n",
		tvp5150_पढ़ो(sd, TVP5150_LUMA_PROC_CTL_1),
		tvp5150_पढ़ो(sd, TVP5150_LUMA_PROC_CTL_2),
		tvp5150_पढ़ो(sd, TVP5150_LUMA_PROC_CTL_3));
	dprपूर्णांकk0(sd->dev, "tvp5150: Brightness control = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_BRIGHT_CTL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Color saturation control = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_SATURATION_CTL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Hue control = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_HUE_CTL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Contrast control = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_CONTRAST_CTL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Outputs and data rates select = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_DATA_RATE_SEL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Configuration shared pins = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_CONF_SHARED_PIN));
	dprपूर्णांकk0(sd->dev, "tvp5150: Active video cropping start = 0x%02x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_ACT_VD_CROP_ST_MSB),
		tvp5150_पढ़ो(sd, TVP5150_ACT_VD_CROP_ST_LSB));
	dprपूर्णांकk0(sd->dev, "tvp5150: Active video cropping stop  = 0x%02x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_ACT_VD_CROP_STP_MSB),
		tvp5150_पढ़ो(sd, TVP5150_ACT_VD_CROP_STP_LSB));
	dprपूर्णांकk0(sd->dev, "tvp5150: Genlock/RTC = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_GENLOCK));
	dprपूर्णांकk0(sd->dev, "tvp5150: Horizontal sync start = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_HORIZ_SYNC_START));
	dprपूर्णांकk0(sd->dev, "tvp5150: Vertical blanking start = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_VERT_BLANKING_START));
	dprपूर्णांकk0(sd->dev, "tvp5150: Vertical blanking stop = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_VERT_BLANKING_STOP));
	dprपूर्णांकk0(sd->dev, "tvp5150: Chrominance processing control #1 and #2 = %02x %02x\n",
		tvp5150_पढ़ो(sd, TVP5150_CHROMA_PROC_CTL_1),
		tvp5150_पढ़ो(sd, TVP5150_CHROMA_PROC_CTL_2));
	dprपूर्णांकk0(sd->dev, "tvp5150: Interrupt reset register B = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_INT_RESET_REG_B));
	dprपूर्णांकk0(sd->dev, "tvp5150: Interrupt enable register B = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_INT_ENABLE_REG_B));
	dprपूर्णांकk0(sd->dev, "tvp5150: Interrupt configuration register B = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_INTT_CONFIG_REG_B));
	dprपूर्णांकk0(sd->dev, "tvp5150: Video standard = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_VIDEO_STD));
	dprपूर्णांकk0(sd->dev, "tvp5150: Chroma gain factor: Cb=0x%02x Cr=0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_CB_GAIN_FACT),
		tvp5150_पढ़ो(sd, TVP5150_CR_GAIN_FACTOR));
	dprपूर्णांकk0(sd->dev, "tvp5150: Macrovision on counter = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_MACROVISION_ON_CTR));
	dprपूर्णांकk0(sd->dev, "tvp5150: Macrovision off counter = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_MACROVISION_OFF_CTR));
	dprपूर्णांकk0(sd->dev, "tvp5150: ITU-R BT.656.%d timing(TVP5150AM1 only)\n",
		(tvp5150_पढ़ो(sd, TVP5150_REV_SELECT) & 1) ? 3 : 4);
	dprपूर्णांकk0(sd->dev, "tvp5150: Device ID = %02x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_MSB_DEV_ID),
		tvp5150_पढ़ो(sd, TVP5150_LSB_DEV_ID));
	dprपूर्णांकk0(sd->dev, "tvp5150: ROM version = (hex) %02x.%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_ROM_MAJOR_VER),
		tvp5150_पढ़ो(sd, TVP5150_ROM_MINOR_VER));
	dprपूर्णांकk0(sd->dev, "tvp5150: Vertical line count = 0x%02x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_VERT_LN_COUNT_MSB),
		tvp5150_पढ़ो(sd, TVP5150_VERT_LN_COUNT_LSB));
	dprपूर्णांकk0(sd->dev, "tvp5150: Interrupt status register B = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_INT_STATUS_REG_B));
	dprपूर्णांकk0(sd->dev, "tvp5150: Interrupt active register B = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_INT_ACTIVE_REG_B));
	dprपूर्णांकk0(sd->dev, "tvp5150: Status regs #1 to #5 = %02x %02x %02x %02x %02x\n",
		tvp5150_पढ़ो(sd, TVP5150_STATUS_REG_1),
		tvp5150_पढ़ो(sd, TVP5150_STATUS_REG_2),
		tvp5150_पढ़ो(sd, TVP5150_STATUS_REG_3),
		tvp5150_पढ़ो(sd, TVP5150_STATUS_REG_4),
		tvp5150_पढ़ो(sd, TVP5150_STATUS_REG_5));

	dump_reg_range(sd, "Teletext filter 1",   TVP5150_TELETEXT_FIL1_INI,
			TVP5150_TELETEXT_FIL1_END, 8);
	dump_reg_range(sd, "Teletext filter 2",   TVP5150_TELETEXT_FIL2_INI,
			TVP5150_TELETEXT_FIL2_END, 8);

	dprपूर्णांकk0(sd->dev, "tvp5150: Teletext filter enable = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_TELETEXT_FIL_ENA));
	dprपूर्णांकk0(sd->dev, "tvp5150: Interrupt status register A = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_INT_STATUS_REG_A));
	dprपूर्णांकk0(sd->dev, "tvp5150: Interrupt enable register A = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_INT_ENABLE_REG_A));
	dprपूर्णांकk0(sd->dev, "tvp5150: Interrupt configuration = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_INT_CONF));
	dprपूर्णांकk0(sd->dev, "tvp5150: VDP status register = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_VDP_STATUS_REG));
	dprपूर्णांकk0(sd->dev, "tvp5150: FIFO word count = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_FIFO_WORD_COUNT));
	dprपूर्णांकk0(sd->dev, "tvp5150: FIFO interrupt threshold = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_FIFO_INT_THRESHOLD));
	dprपूर्णांकk0(sd->dev, "tvp5150: FIFO reset = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_FIFO_RESET));
	dprपूर्णांकk0(sd->dev, "tvp5150: Line number interrupt = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_LINE_NUMBER_INT));
	dprपूर्णांकk0(sd->dev, "tvp5150: Pixel alignment register = 0x%02x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_PIX_ALIGN_REG_HIGH),
		tvp5150_पढ़ो(sd, TVP5150_PIX_ALIGN_REG_LOW));
	dprपूर्णांकk0(sd->dev, "tvp5150: FIFO output control = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_FIFO_OUT_CTRL));
	dprपूर्णांकk0(sd->dev, "tvp5150: Full field enable = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_FULL_FIELD_ENA));
	dprपूर्णांकk0(sd->dev, "tvp5150: Full field mode register = 0x%02x\n",
		tvp5150_पढ़ो(sd, TVP5150_FULL_FIELD_MODE_REG));

	dump_reg_range(sd, "CC   data",   TVP5150_CC_DATA_INI,
			TVP5150_CC_DATA_END, 8);

	dump_reg_range(sd, "WSS  data",   TVP5150_WSS_DATA_INI,
			TVP5150_WSS_DATA_END, 8);

	dump_reg_range(sd, "VPS  data",   TVP5150_VPS_DATA_INI,
			TVP5150_VPS_DATA_END, 8);

	dump_reg_range(sd, "VITC data",   TVP5150_VITC_DATA_INI,
			TVP5150_VITC_DATA_END, 10);

	dump_reg_range(sd, "Line mode",   TVP5150_LINE_MODE_INI,
			TVP5150_LINE_MODE_END, 8);
	वापस 0;
पूर्ण

/****************************************************************************
			Basic functions
 ****************************************************************************/

अटल व्योम tvp5150_selmux(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक opmode = 0;
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक input = 0;

	/* Only tvp5150am1 and tvp5151 have संकेत generator support */
	अगर ((decoder->dev_id == 0x5150 && decoder->rom_ver == 0x0400) ||
	    (decoder->dev_id == 0x5151 && decoder->rom_ver == 0x0100)) अणु
		अगर (!decoder->enable)
			input = 8;
	पूर्ण

	चयन (decoder->input) अणु
	हाल TVP5150_COMPOSITE1:
		input |= 2;
		fallthrough;
	हाल TVP5150_COMPOSITE0:
		अवरोध;
	हाल TVP5150_SVIDEO:
	शेष:
		input |= 1;
		अवरोध;
	पूर्ण

	dev_dbg_lvl(sd->dev, 1, debug,
		    "Selecting video route: route input=%s, output=%s => tvp5150 input=0x%02x, opmode=0x%02x\n",
		    decoder->input == 0 ? "aip1a" :
		    decoder->input == 2 ? "aip1b" : "svideo",
		    decoder->output == 0 ? "normal" : "black-frame-gen",
		    input, opmode);

	regmap_ग_लिखो(decoder->regmap, TVP5150_OP_MODE_CTL, opmode);
	regmap_ग_लिखो(decoder->regmap, TVP5150_VD_IN_SRC_SEL_1, input);

	/*
	 * Setup the FID/GLCO/VLK/HVLK and INTREQ/GPCL/VBLK output संकेतs. For
	 * S-Video we output the vertical lock (VLK) संकेत on FID/GLCO/VLK/HVLK
	 * and set INTREQ/GPCL/VBLK to logic 0. For composite we output the
	 * field indicator (FID) संकेत on FID/GLCO/VLK/HVLK and set
	 * INTREQ/GPCL/VBLK to logic 1.
	 */
	mask = TVP5150_MISC_CTL_GPCL | TVP5150_MISC_CTL_HVLK;
	अगर (decoder->input == TVP5150_SVIDEO)
		val = TVP5150_MISC_CTL_HVLK;
	अन्यथा
		val = TVP5150_MISC_CTL_GPCL;
	regmap_update_bits(decoder->regmap, TVP5150_MISC_CTL, mask, val);
पूर्ण;

काष्ठा i2c_reg_value अणु
	अचिन्हित अक्षर reg;
	अचिन्हित अक्षर value;
पूर्ण;

/* Default values as sugested at TVP5150AM1 datasheet */
अटल स्थिर काष्ठा i2c_reg_value tvp5150_init_शेष[] = अणु
	अणु /* 0x00 */
		TVP5150_VD_IN_SRC_SEL_1, 0x00
	पूर्ण,
	अणु /* 0x01 */
		TVP5150_ANAL_CHL_CTL, 0x15
	पूर्ण,
	अणु /* 0x02 */
		TVP5150_OP_MODE_CTL, 0x00
	पूर्ण,
	अणु /* 0x03 */
		TVP5150_MISC_CTL, 0x01
	पूर्ण,
	अणु /* 0x06 */
		TVP5150_COLOR_KIL_THSH_CTL, 0x10
	पूर्ण,
	अणु /* 0x07 */
		TVP5150_LUMA_PROC_CTL_1, 0x60
	पूर्ण,
	अणु /* 0x08 */
		TVP5150_LUMA_PROC_CTL_2, 0x00
	पूर्ण,
	अणु /* 0x09 */
		TVP5150_BRIGHT_CTL, 0x80
	पूर्ण,
	अणु /* 0x0a */
		TVP5150_SATURATION_CTL, 0x80
	पूर्ण,
	अणु /* 0x0b */
		TVP5150_HUE_CTL, 0x00
	पूर्ण,
	अणु /* 0x0c */
		TVP5150_CONTRAST_CTL, 0x80
	पूर्ण,
	अणु /* 0x0d */
		TVP5150_DATA_RATE_SEL, 0x47
	पूर्ण,
	अणु /* 0x0e */
		TVP5150_LUMA_PROC_CTL_3, 0x00
	पूर्ण,
	अणु /* 0x0f */
		TVP5150_CONF_SHARED_PIN, 0x08
	पूर्ण,
	अणु /* 0x11 */
		TVP5150_ACT_VD_CROP_ST_MSB, 0x00
	पूर्ण,
	अणु /* 0x12 */
		TVP5150_ACT_VD_CROP_ST_LSB, 0x00
	पूर्ण,
	अणु /* 0x13 */
		TVP5150_ACT_VD_CROP_STP_MSB, 0x00
	पूर्ण,
	अणु /* 0x14 */
		TVP5150_ACT_VD_CROP_STP_LSB, 0x00
	पूर्ण,
	अणु /* 0x15 */
		TVP5150_GENLOCK, 0x01
	पूर्ण,
	अणु /* 0x16 */
		TVP5150_HORIZ_SYNC_START, 0x80
	पूर्ण,
	अणु /* 0x18 */
		TVP5150_VERT_BLANKING_START, 0x00
	पूर्ण,
	अणु /* 0x19 */
		TVP5150_VERT_BLANKING_STOP, 0x00
	पूर्ण,
	अणु /* 0x1a */
		TVP5150_CHROMA_PROC_CTL_1, 0x0c
	पूर्ण,
	अणु /* 0x1b */
		TVP5150_CHROMA_PROC_CTL_2, 0x14
	पूर्ण,
	अणु /* 0x1c */
		TVP5150_INT_RESET_REG_B, 0x00
	पूर्ण,
	अणु /* 0x1d */
		TVP5150_INT_ENABLE_REG_B, 0x00
	पूर्ण,
	अणु /* 0x1e */
		TVP5150_INTT_CONFIG_REG_B, 0x00
	पूर्ण,
	अणु /* 0x28 */
		TVP5150_VIDEO_STD, 0x00
	पूर्ण,
	अणु /* 0x2e */
		TVP5150_MACROVISION_ON_CTR, 0x0f
	पूर्ण,
	अणु /* 0x2f */
		TVP5150_MACROVISION_OFF_CTR, 0x01
	पूर्ण,
	अणु /* 0xbb */
		TVP5150_TELETEXT_FIL_ENA, 0x00
	पूर्ण,
	अणु /* 0xc0 */
		TVP5150_INT_STATUS_REG_A, 0x00
	पूर्ण,
	अणु /* 0xc1 */
		TVP5150_INT_ENABLE_REG_A, 0x00
	पूर्ण,
	अणु /* 0xc2 */
		TVP5150_INT_CONF, 0x04
	पूर्ण,
	अणु /* 0xc8 */
		TVP5150_FIFO_INT_THRESHOLD, 0x80
	पूर्ण,
	अणु /* 0xc9 */
		TVP5150_FIFO_RESET, 0x00
	पूर्ण,
	अणु /* 0xca */
		TVP5150_LINE_NUMBER_INT, 0x00
	पूर्ण,
	अणु /* 0xcb */
		TVP5150_PIX_ALIGN_REG_LOW, 0x4e
	पूर्ण,
	अणु /* 0xcc */
		TVP5150_PIX_ALIGN_REG_HIGH, 0x00
	पूर्ण,
	अणु /* 0xcd */
		TVP5150_FIFO_OUT_CTRL, 0x01
	पूर्ण,
	अणु /* 0xcf */
		TVP5150_FULL_FIELD_ENA, 0x00
	पूर्ण,
	अणु /* 0xd0 */
		TVP5150_LINE_MODE_INI, 0x00
	पूर्ण,
	अणु /* 0xfc */
		TVP5150_FULL_FIELD_MODE_REG, 0x7f
	पूर्ण,
	अणु /* end of data */
		0xff, 0xff
	पूर्ण
पूर्ण;

/* Default values as sugested at TVP5150AM1 datasheet */
अटल स्थिर काष्ठा i2c_reg_value tvp5150_init_enable[] = अणु
	अणु	/* Automatic offset and AGC enabled */
		TVP5150_ANAL_CHL_CTL, 0x15
	पूर्ण, अणु	/* Activate YCrCb output 0x9 or 0xd ? */
		TVP5150_MISC_CTL, TVP5150_MISC_CTL_GPCL |
				  TVP5150_MISC_CTL_INTREQ_OE |
				  TVP5150_MISC_CTL_YCBCR_OE |
				  TVP5150_MISC_CTL_SYNC_OE |
				  TVP5150_MISC_CTL_VBLANK |
				  TVP5150_MISC_CTL_CLOCK_OE,
	पूर्ण, अणु	/* Activates video std स्वतःdetection क्रम all standards */
		TVP5150_AUTOSW_MSK, 0x0
	पूर्ण, अणु	/* Default क्रमmat: 0x47. For 4:2:2: 0x40 */
		TVP5150_DATA_RATE_SEL, 0x47
	पूर्ण, अणु
		TVP5150_CHROMA_PROC_CTL_1, 0x0c
	पूर्ण, अणु
		TVP5150_CHROMA_PROC_CTL_2, 0x54
	पूर्ण, अणु	/* Non करोcumented, but initialized on WinTV USB2 */
		0x27, 0x20
	पूर्ण, अणु
		0xff, 0xff
	पूर्ण
पूर्ण;

काष्ठा tvp5150_vbi_type अणु
	अचिन्हित पूर्णांक vbi_type;
	अचिन्हित पूर्णांक ini_line;
	अचिन्हित पूर्णांक end_line;
	अचिन्हित पूर्णांक by_field :1;
पूर्ण;

काष्ठा i2c_vbi_ram_value अणु
	u16 reg;
	काष्ठा tvp5150_vbi_type type;
	अचिन्हित अक्षर values[16];
पूर्ण;

/* This काष्ठा have the values क्रम each supported VBI Standard
 * by
 tvp5150_vbi_types should follow the same order as vbi_ram_शेष
 * value 0 means rom position 0x10, value 1 means rom position 0x30
 * and so on. There are 16 possible locations from 0 to 15.
 */

अटल काष्ठा i2c_vbi_ram_value vbi_ram_शेष[] = अणु

	/*
	 * FIXME: Current api करोesn't handle all VBI types, those not
	 * yet supported are placed under #अगर 0
	 */
#अगर 0
	[0] = अणु0x010, /* Teletext, SECAM, WST System A */
		अणुV4L2_SLICED_TELETEXT_SECAM, 6, 23, 1पूर्ण,
		अणु 0xaa, 0xaa, 0xff, 0xff, 0xe7, 0x2e, 0x20, 0x26,
		  0xe6, 0xb4, 0x0e, 0x00, 0x00, 0x00, 0x10, 0x00 पूर्ण
	पूर्ण,
#पूर्ण_अगर
	[1] = अणु0x030, /* Teletext, PAL, WST System B */
		अणुV4L2_SLICED_TELETEXT_B, 6, 22, 1पूर्ण,
		अणु 0xaa, 0xaa, 0xff, 0xff, 0x27, 0x2e, 0x20, 0x2b,
		  0xa6, 0x72, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00 पूर्ण
	पूर्ण,
#अगर 0
	[2] = अणु0x050, /* Teletext, PAL, WST System C */
		अणुV4L2_SLICED_TELETEXT_PAL_C, 6, 22, 1पूर्ण,
		अणु 0xaa, 0xaa, 0xff, 0xff, 0xe7, 0x2e, 0x20, 0x22,
		  0xa6, 0x98, 0x0d, 0x00, 0x00, 0x00, 0x10, 0x00 पूर्ण
	पूर्ण,
	[3] = अणु0x070, /* Teletext, NTSC, WST System B */
		अणुV4L2_SLICED_TELETEXT_NTSC_B, 10, 21, 1पूर्ण,
		अणु 0xaa, 0xaa, 0xff, 0xff, 0x27, 0x2e, 0x20, 0x23,
		  0x69, 0x93, 0x0d, 0x00, 0x00, 0x00, 0x10, 0x00 पूर्ण
	पूर्ण,
	[4] = अणु0x090, /* Tetetext, NTSC NABTS System C */
		अणुV4L2_SLICED_TELETEXT_NTSC_C, 10, 21, 1पूर्ण,
		अणु 0xaa, 0xaa, 0xff, 0xff, 0xe7, 0x2e, 0x20, 0x22,
		  0x69, 0x93, 0x0d, 0x00, 0x00, 0x00, 0x15, 0x00 पूर्ण
	पूर्ण,
	[5] = अणु0x0b0, /* Teletext, NTSC-J, NABTS System D */
		अणुV4L2_SLICED_TELETEXT_NTSC_D, 10, 21, 1पूर्ण,
		अणु 0xaa, 0xaa, 0xff, 0xff, 0xa7, 0x2e, 0x20, 0x23,
		  0x69, 0x93, 0x0d, 0x00, 0x00, 0x00, 0x10, 0x00 पूर्ण
	पूर्ण,
	[6] = अणु0x0d0, /* Closed Caption, PAL/SECAM */
		अणुV4L2_SLICED_CAPTION_625, 22, 22, 1पूर्ण,
		अणु 0xaa, 0x2a, 0xff, 0x3f, 0x04, 0x51, 0x6e, 0x02,
		  0xa6, 0x7b, 0x09, 0x00, 0x00, 0x00, 0x27, 0x00 पूर्ण
	पूर्ण,
#पूर्ण_अगर
	[7] = अणु0x0f0, /* Closed Caption, NTSC */
		अणुV4L2_SLICED_CAPTION_525, 21, 21, 1पूर्ण,
		अणु 0xaa, 0x2a, 0xff, 0x3f, 0x04, 0x51, 0x6e, 0x02,
		  0x69, 0x8c, 0x09, 0x00, 0x00, 0x00, 0x27, 0x00 पूर्ण
	पूर्ण,
	[8] = अणु0x110, /* Wide Screen Signal, PAL/SECAM */
		अणुV4L2_SLICED_WSS_625, 23, 23, 1पूर्ण,
		अणु 0x5b, 0x55, 0xc5, 0xff, 0x00, 0x71, 0x6e, 0x42,
		  0xa6, 0xcd, 0x0f, 0x00, 0x00, 0x00, 0x3a, 0x00 पूर्ण
	पूर्ण,
#अगर 0
	[9] = अणु0x130, /* Wide Screen Signal, NTSC C */
		अणुV4L2_SLICED_WSS_525, 20, 20, 1पूर्ण,
		अणु 0x38, 0x00, 0x3f, 0x00, 0x00, 0x71, 0x6e, 0x43,
		  0x69, 0x7c, 0x08, 0x00, 0x00, 0x00, 0x39, 0x00 पूर्ण
	पूर्ण,
	[10] = अणु0x150, /* Vertical Interval Timecode (VITC), PAL/SECAM */
		अणुV4l2_SLICED_VITC_625, 6, 22, 0पूर्ण,
		अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x8f, 0x6d, 0x49,
		  0xa6, 0x85, 0x08, 0x00, 0x00, 0x00, 0x4c, 0x00 पूर्ण
	पूर्ण,
	[11] = अणु0x170, /* Vertical Interval Timecode (VITC), NTSC */
		अणुV4l2_SLICED_VITC_525, 10, 20, 0पूर्ण,
		अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x8f, 0x6d, 0x49,
		  0x69, 0x94, 0x08, 0x00, 0x00, 0x00, 0x4c, 0x00 पूर्ण
	पूर्ण,
#पूर्ण_अगर
	[12] = अणु0x190, /* Video Program System (VPS), PAL */
		अणुV4L2_SLICED_VPS, 16, 16, 0पूर्ण,
		अणु 0xaa, 0xaa, 0xff, 0xff, 0xba, 0xce, 0x2b, 0x0d,
		  0xa6, 0xda, 0x0b, 0x00, 0x00, 0x00, 0x60, 0x00 पूर्ण
	पूर्ण,
	/* 0x1d0 User programmable */
पूर्ण;

अटल पूर्णांक tvp5150_ग_लिखो_inittab(काष्ठा v4l2_subdev *sd,
				स्थिर काष्ठा i2c_reg_value *regs)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	जबतक (regs->reg != 0xff) अणु
		regmap_ग_लिखो(decoder->regmap, regs->reg, regs->value);
		regs++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_vdp_init(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	काष्ठा regmap *map = decoder->regmap;
	अचिन्हित पूर्णांक i;
	पूर्णांक j;

	/* Disable Full Field */
	regmap_ग_लिखो(map, TVP5150_FULL_FIELD_ENA, 0);

	/* Beक्रमe programming, Line mode should be at 0xff */
	क्रम (i = TVP5150_LINE_MODE_INI; i <= TVP5150_LINE_MODE_END; i++)
		regmap_ग_लिखो(map, i, 0xff);

	/* Load Ram Table */
	क्रम (j = 0; j < ARRAY_SIZE(vbi_ram_शेष); j++) अणु
		स्थिर काष्ठा i2c_vbi_ram_value *regs = &vbi_ram_शेष[j];

		अगर (!regs->type.vbi_type)
			जारी;

		regmap_ग_लिखो(map, TVP5150_CONF_RAM_ADDR_HIGH, regs->reg >> 8);
		regmap_ग_लिखो(map, TVP5150_CONF_RAM_ADDR_LOW, regs->reg);

		क्रम (i = 0; i < 16; i++)
			regmap_ग_लिखो(map, TVP5150_VDP_CONF_RAM_DATA,
				     regs->values[i]);
	पूर्ण
	वापस 0;
पूर्ण

/* Fills VBI capabilities based on i2c_vbi_ram_value काष्ठा */
अटल पूर्णांक tvp5150_g_sliced_vbi_cap(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_sliced_vbi_cap *cap)
अणु
	पूर्णांक line, i;

	dev_dbg_lvl(sd->dev, 1, debug, "g_sliced_vbi_cap\n");
	स_रखो(cap, 0, माप(*cap));

	क्रम (i = 0; i < ARRAY_SIZE(vbi_ram_शेष); i++) अणु
		स्थिर काष्ठा i2c_vbi_ram_value *regs = &vbi_ram_शेष[i];

		अगर (!regs->type.vbi_type)
			जारी;

		क्रम (line = regs->type.ini_line;
		     line <= regs->type.end_line;
		     line++) अणु
			cap->service_lines[0][line] |= regs->type.vbi_type;
		पूर्ण
		cap->service_set |= regs->type.vbi_type;
	पूर्ण
	वापस 0;
पूर्ण

/* Set vbi processing
 * type - one of tvp5150_vbi_types
 * line - line to gather data
 * fields: bit 0 field1, bit 1, field2
 * flags (शेष=0xf0) is a biपंचांगask, were set means:
 *	bit 7: enable filtering null bytes on CC
 *	bit 6: send data also to FIFO
 *	bit 5: करोn't allow data with errors on FIFO
 *	bit 4: enable ECC when possible
 * pix_align = pix alignment:
 *	LSB = field1
 *	MSB = field2
 */
अटल पूर्णांक tvp5150_set_vbi(काष्ठा v4l2_subdev *sd,
			अचिन्हित पूर्णांक type, u8 flags, पूर्णांक line,
			स्थिर पूर्णांक fields)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std = decoder->norm;
	u8 reg;
	पूर्णांक i, pos = 0;

	अगर (std == V4L2_STD_ALL) अणु
		dev_err(sd->dev, "VBI can't be configured without knowing number of lines\n");
		वापस 0;
	पूर्ण अन्यथा अगर (std & V4L2_STD_625_50) अणु
		/* Don't follow NTSC Line number convension */
		line += 3;
	पूर्ण

	अगर (line < 6 || line > 27)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(vbi_ram_शेष); i++) अणु
		स्थिर काष्ठा i2c_vbi_ram_value *regs =  &vbi_ram_शेष[i];

		अगर (!regs->type.vbi_type)
			जारी;

		अगर ((type & regs->type.vbi_type) &&
		    (line >= regs->type.ini_line) &&
		    (line <= regs->type.end_line))
			अवरोध;
		pos++;
	पूर्ण

	type = pos | (flags & 0xf0);
	reg = ((line - 6) << 1) + TVP5150_LINE_MODE_INI;

	अगर (fields & 1)
		regmap_ग_लिखो(decoder->regmap, reg, type);

	अगर (fields & 2)
		regmap_ग_लिखो(decoder->regmap, reg + 1, type);

	वापस type;
पूर्ण

अटल पूर्णांक tvp5150_get_vbi(काष्ठा v4l2_subdev *sd, पूर्णांक line)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std = decoder->norm;
	u8 reg;
	पूर्णांक pos, type = 0;
	पूर्णांक i, ret = 0;

	अगर (std == V4L2_STD_ALL) अणु
		dev_err(sd->dev, "VBI can't be configured without knowing number of lines\n");
		वापस 0;
	पूर्ण अन्यथा अगर (std & V4L2_STD_625_50) अणु
		/* Don't follow NTSC Line number convension */
		line += 3;
	पूर्ण

	अगर (line < 6 || line > 27)
		वापस 0;

	reg = ((line - 6) << 1) + TVP5150_LINE_MODE_INI;

	क्रम (i = 0; i <= 1; i++) अणु
		ret = tvp5150_पढ़ो(sd, reg + i);
		अगर (ret < 0) अणु
			dev_err(sd->dev, "%s: failed with error = %d\n",
				 __func__, ret);
			वापस 0;
		पूर्ण
		pos = ret & 0x0f;
		अगर (pos < ARRAY_SIZE(vbi_ram_शेष))
			type |= vbi_ram_शेष[pos].type.vbi_type;
	पूर्ण

	वापस type;
पूर्ण

अटल पूर्णांक tvp5150_set_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	पूर्णांक fmt = 0;

	/* First tests should be against specअगरic std */

	अगर (std == V4L2_STD_NTSC_443) अणु
		fmt = VIDEO_STD_NTSC_4_43_BIT;
	पूर्ण अन्यथा अगर (std == V4L2_STD_PAL_M) अणु
		fmt = VIDEO_STD_PAL_M_BIT;
	पूर्ण अन्यथा अगर (std == V4L2_STD_PAL_N || std == V4L2_STD_PAL_Nc) अणु
		fmt = VIDEO_STD_PAL_COMBINATION_N_BIT;
	पूर्ण अन्यथा अणु
		/* Then, test against generic ones */
		अगर (std & V4L2_STD_NTSC)
			fmt = VIDEO_STD_NTSC_MJ_BIT;
		अन्यथा अगर (std & V4L2_STD_PAL)
			fmt = VIDEO_STD_PAL_BDGHIN_BIT;
		अन्यथा अगर (std & V4L2_STD_SECAM)
			fmt = VIDEO_STD_SECAM_BIT;
	पूर्ण

	dev_dbg_lvl(sd->dev, 1, debug, "Set video std register to %d.\n", fmt);
	regmap_ग_लिखो(decoder->regmap, TVP5150_VIDEO_STD, fmt);
	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_g_std(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	*std = decoder->norm;

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	काष्ठा tvp5150_connector *cur_con = decoder->cur_connector;
	v4l2_std_id supported_stds;

	अगर (decoder->norm == std)
		वापस 0;

	/* In हाल of no of-connectors are available no limitations are made */
	अगर (!decoder->connectors_num)
		supported_stds = V4L2_STD_ALL;
	अन्यथा
		supported_stds = cur_con->base.connector.analog.sdtv_stds;

	/*
	 * Check अगर requested std or group of std's is/are supported by the
	 * connector.
	 */
	अगर ((supported_stds & std) == 0)
		वापस -EINVAL;

	/* Change cropping height limits */
	अगर (std & V4L2_STD_525_60)
		decoder->rect.height = TVP5150_V_MAX_525_60;
	अन्यथा
		decoder->rect.height = TVP5150_V_MAX_OTHERS;

	/* Set only the specअगरic supported std in हाल of group of std's. */
	decoder->norm = supported_stds & std;

	वापस tvp5150_set_std(sd, std);
पूर्ण

अटल v4l2_std_id tvp5150_पढ़ो_std(काष्ठा v4l2_subdev *sd)
अणु
	पूर्णांक val = tvp5150_पढ़ो(sd, TVP5150_STATUS_REG_5);

	चयन (val & 0x0F) अणु
	हाल 0x01:
		वापस V4L2_STD_NTSC;
	हाल 0x03:
		वापस V4L2_STD_PAL;
	हाल 0x05:
		वापस V4L2_STD_PAL_M;
	हाल 0x07:
		वापस V4L2_STD_PAL_N | V4L2_STD_PAL_Nc;
	हाल 0x09:
		वापस V4L2_STD_NTSC_443;
	हाल 0xb:
		वापस V4L2_STD_SECAM;
	शेष:
		वापस V4L2_STD_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक query_lock(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	पूर्णांक status;

	अगर (decoder->irq)
		वापस decoder->lock;

	regmap_पढ़ो(decoder->regmap, TVP5150_STATUS_REG_1, &status);

	/* For standard detection, we need the 3 locks */
	वापस (status & 0x0e) == 0x0e;
पूर्ण

अटल पूर्णांक tvp5150_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std_id)
अणु
	*std_id = query_lock(sd) ? tvp5150_पढ़ो_std(sd) : V4L2_STD_UNKNOWN;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_event tvp5150_ev_fmt = अणु
	.type = V4L2_EVENT_SOURCE_CHANGE,
	.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
पूर्ण;

अटल irqवापस_t tvp5150_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tvp5150 *decoder = dev_id;
	काष्ठा regmap *map = decoder->regmap;
	अचिन्हित पूर्णांक mask, active = 0, status = 0;

	mask = TVP5150_MISC_CTL_YCBCR_OE | TVP5150_MISC_CTL_SYNC_OE |
	       TVP5150_MISC_CTL_CLOCK_OE;

	regmap_पढ़ो(map, TVP5150_INT_STATUS_REG_A, &status);
	अगर (status) अणु
		regmap_ग_लिखो(map, TVP5150_INT_STATUS_REG_A, status);

		अगर (status & TVP5150_INT_A_LOCK) अणु
			decoder->lock = !!(status & TVP5150_INT_A_LOCK_STATUS);
			dev_dbg_lvl(decoder->sd.dev, 1, debug,
				    "sync lo%s signal\n",
				    decoder->lock ? "ck" : "ss");
			v4l2_subdev_notअगरy_event(&decoder->sd, &tvp5150_ev_fmt);
			regmap_update_bits(map, TVP5150_MISC_CTL, mask,
					   decoder->lock ? decoder->oe : 0);
		पूर्ण

		वापस IRQ_HANDLED;
	पूर्ण

	regmap_पढ़ो(map, TVP5150_INT_ACTIVE_REG_B, &active);
	अगर (active) अणु
		status = 0;
		regmap_पढ़ो(map, TVP5150_INT_STATUS_REG_B, &status);
		अगर (status)
			regmap_ग_लिखो(map, TVP5150_INT_RESET_REG_B, status);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tvp5150_reset(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	काष्ठा regmap *map = decoder->regmap;

	/* Initializes TVP5150 to its शेष values */
	tvp5150_ग_लिखो_inittab(sd, tvp5150_init_शेष);

	अगर (decoder->irq) अणु
		/* Configure pins: FID, VSYNC, INTREQ, SCLK */
		regmap_ग_लिखो(map, TVP5150_CONF_SHARED_PIN, 0x0);
		/* Set पूर्णांकerrupt polarity to active high */
		regmap_ग_लिखो(map, TVP5150_INT_CONF, TVP5150_VDPOE | 0x1);
		regmap_ग_लिखो(map, TVP5150_INTT_CONFIG_REG_B, 0x1);
	पूर्ण अन्यथा अणु
		/* Configure pins: FID, VSYNC, GPCL/VBLK, SCLK */
		regmap_ग_लिखो(map, TVP5150_CONF_SHARED_PIN, 0x2);
		/* Keep पूर्णांकerrupt polarity active low */
		regmap_ग_लिखो(map, TVP5150_INT_CONF, TVP5150_VDPOE);
		regmap_ग_लिखो(map, TVP5150_INTT_CONFIG_REG_B, 0x0);
	पूर्ण

	/* Initializes VDP रेजिस्टरs */
	tvp5150_vdp_init(sd);

	/* Selects decoder input */
	tvp5150_selmux(sd);

	/* Initialize image preferences */
	v4l2_ctrl_handler_setup(&decoder->hdl);

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_enable(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std;

	/* Initializes TVP5150 to stream enabled values */
	tvp5150_ग_लिखो_inittab(sd, tvp5150_init_enable);

	अगर (decoder->norm == V4L2_STD_ALL)
		std = tvp5150_पढ़ो_std(sd);
	अन्यथा
		std = decoder->norm;

	/* Disable स्वतःचयन mode */
	tvp5150_set_std(sd, std);

	/*
	 * Enable the YCbCr and घड़ी outमाला_दो. In discrete sync mode
	 * (non-BT.656) additionally enable the the sync outमाला_दो.
	 */
	चयन (decoder->mbus_type) अणु
	हाल V4L2_MBUS_PARALLEL:
		/* 8-bit 4:2:2 YUV with discrete sync output */
		regmap_update_bits(decoder->regmap, TVP5150_DATA_RATE_SEL,
				   0x7, 0x0);
		decoder->oe = TVP5150_MISC_CTL_YCBCR_OE |
			      TVP5150_MISC_CTL_CLOCK_OE |
			      TVP5150_MISC_CTL_SYNC_OE;
		अवरोध;
	हाल V4L2_MBUS_BT656:
		decoder->oe = TVP5150_MISC_CTL_YCBCR_OE |
			      TVP5150_MISC_CTL_CLOCK_OE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक tvp5150_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		regmap_ग_लिखो(decoder->regmap, TVP5150_BRIGHT_CTL, ctrl->val);
		वापस 0;
	हाल V4L2_CID_CONTRAST:
		regmap_ग_लिखो(decoder->regmap, TVP5150_CONTRAST_CTL, ctrl->val);
		वापस 0;
	हाल V4L2_CID_SATURATION:
		regmap_ग_लिखो(decoder->regmap, TVP5150_SATURATION_CTL,
			     ctrl->val);
		वापस 0;
	हाल V4L2_CID_HUE:
		regmap_ग_लिखो(decoder->regmap, TVP5150_HUE_CTL, ctrl->val);
		वापस 0;
	हाल V4L2_CID_TEST_PATTERN:
		decoder->enable = ctrl->val ? false : true;
		tvp5150_selmux(sd);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम tvp5150_set_शेष(v4l2_std_id std, काष्ठा v4l2_rect *crop)
अणु
	/* Default is no cropping */
	crop->top = 0;
	crop->left = 0;
	crop->width = TVP5150_H_MAX;
	अगर (std & V4L2_STD_525_60)
		crop->height = TVP5150_V_MAX_525_60;
	अन्यथा
		crop->height = TVP5150_V_MAX_OTHERS;
पूर्ण

अटल काष्ठा v4l2_rect *
tvp5150_get_pad_crop(काष्ठा tvp5150 *decoder,
		     काष्ठा v4l2_subdev_pad_config *cfg, अचिन्हित पूर्णांक pad,
		     क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &decoder->rect;
	हाल V4L2_SUBDEV_FORMAT_TRY:
#अगर defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
		वापस v4l2_subdev_get_try_crop(&decoder->sd, cfg, pad);
#अन्यथा
		वापस ERR_PTR(-EINVAL);
#पूर्ण_अगर
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक tvp5150_fill_fmt(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *f;
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	अगर (!क्रमmat || (क्रमmat->pad != TVP5150_PAD_VID_OUT))
		वापस -EINVAL;

	f = &क्रमmat->क्रमmat;

	f->width = decoder->rect.width;
	f->height = decoder->rect.height / 2;

	f->code = TVP5150_MBUS_FMT;
	f->field = TVP5150_FIELD;
	f->colorspace = TVP5150_COLORSPACE;

	dev_dbg_lvl(sd->dev, 1, debug, "width = %d, height = %d\n", f->width,
		    f->height);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक tvp5150_get_hmax(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std;

	/* Calculate height based on current standard */
	अगर (decoder->norm == V4L2_STD_ALL)
		std = tvp5150_पढ़ो_std(sd);
	अन्यथा
		std = decoder->norm;

	वापस (std & V4L2_STD_525_60) ?
		TVP5150_V_MAX_525_60 : TVP5150_V_MAX_OTHERS;
पूर्ण

अटल व्योम tvp5150_set_hw_selection(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_rect *rect)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	अचिन्हित पूर्णांक hmax = tvp5150_get_hmax(sd);

	regmap_ग_लिखो(decoder->regmap, TVP5150_VERT_BLANKING_START, rect->top);
	regmap_ग_लिखो(decoder->regmap, TVP5150_VERT_BLANKING_STOP,
		     rect->top + rect->height - hmax);
	regmap_ग_लिखो(decoder->regmap, TVP5150_ACT_VD_CROP_ST_MSB,
		     rect->left >> TVP5150_CROP_SHIFT);
	regmap_ग_लिखो(decoder->regmap, TVP5150_ACT_VD_CROP_ST_LSB,
		     rect->left | (1 << TVP5150_CROP_SHIFT));
	regmap_ग_लिखो(decoder->regmap, TVP5150_ACT_VD_CROP_STP_MSB,
		     (rect->left + rect->width - TVP5150_MAX_CROP_LEFT) >>
		     TVP5150_CROP_SHIFT);
	regmap_ग_लिखो(decoder->regmap, TVP5150_ACT_VD_CROP_STP_LSB,
		     rect->left + rect->width - TVP5150_MAX_CROP_LEFT);
पूर्ण

अटल पूर्णांक tvp5150_set_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	काष्ठा v4l2_rect *rect = &sel->r;
	काष्ठा v4l2_rect *crop;
	अचिन्हित पूर्णांक hmax;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	dev_dbg_lvl(sd->dev, 1, debug, "%s left=%d, top=%d, width=%d, height=%d\n",
		__func__, rect->left, rect->top, rect->width, rect->height);

	/* tvp5150 has some special limits */
	rect->left = clamp(rect->left, 0, TVP5150_MAX_CROP_LEFT);
	rect->top = clamp(rect->top, 0, TVP5150_MAX_CROP_TOP);
	hmax = tvp5150_get_hmax(sd);

	/*
	 * alignments:
	 *  - width = 2 due to UYVY colorspace
	 *  - height, image = no special alignment
	 */
	v4l_bound_align_image(&rect->width,
			      TVP5150_H_MAX - TVP5150_MAX_CROP_LEFT - rect->left,
			      TVP5150_H_MAX - rect->left, 1, &rect->height,
			      hmax - TVP5150_MAX_CROP_TOP - rect->top,
			      hmax - rect->top, 0, 0);

	अगर (!IS_ENABLED(CONFIG_VIDEO_V4L2_SUBDEV_API) &&
	    sel->which == V4L2_SUBDEV_FORMAT_TRY)
		वापस 0;

	crop = tvp5150_get_pad_crop(decoder, cfg, sel->pad, sel->which);
	अगर (IS_ERR(crop))
		वापस PTR_ERR(crop);

	/*
	 * Update output image size अगर the selection (crop) rectangle size or
	 * position has been modअगरied.
	 */
	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE &&
	    !v4l2_rect_equal(rect, crop))
		tvp5150_set_hw_selection(sd, rect);

	*crop = *rect;

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_get_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा tvp5150 *decoder = container_of(sd, काष्ठा tvp5150, sd);
	काष्ठा v4l2_rect *crop;
	v4l2_std_id std;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = TVP5150_H_MAX;

		/* Calculate height based on current standard */
		अगर (decoder->norm == V4L2_STD_ALL)
			std = tvp5150_पढ़ो_std(sd);
		अन्यथा
			std = decoder->norm;
		अगर (std & V4L2_STD_525_60)
			sel->r.height = TVP5150_V_MAX_525_60;
		अन्यथा
			sel->r.height = TVP5150_V_MAX_OTHERS;
		वापस 0;
	हाल V4L2_SEL_TGT_CROP:
		crop = tvp5150_get_pad_crop(decoder, cfg, sel->pad,
					    sel->which);
		अगर (IS_ERR(crop))
			वापस PTR_ERR(crop);
		sel->r = *crop;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tvp5150_get_mbus_config(काष्ठा v4l2_subdev *sd,
				   अचिन्हित पूर्णांक pad,
				   काष्ठा v4l2_mbus_config *cfg)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	cfg->type = decoder->mbus_type;
	cfg->flags = V4L2_MBUS_MASTER | V4L2_MBUS_PCLK_SAMPLE_RISING
		   | V4L2_MBUS_FIELD_EVEN_LOW | V4L2_MBUS_DATA_ACTIVE_HIGH;

	वापस 0;
पूर्ण

/****************************************************************************
			V4L2 subdev pad ops
 ****************************************************************************/
अटल पूर्णांक tvp5150_init_cfg(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std;

	/*
	 * Reset selection to maximum on subdev_खोलो() अगर स्वतःdetection is on
	 * and a standard change is detected.
	 */
	अगर (decoder->norm == V4L2_STD_ALL) अणु
		std = tvp5150_पढ़ो_std(sd);
		अगर (std != decoder->detected_norm) अणु
			decoder->detected_norm = std;
			tvp5150_set_शेष(std, &decoder->rect);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index)
		वापस -EINVAL;

	code->code = TVP5150_MBUS_FMT;
	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	अगर (fse->index >= 8 || fse->code != TVP5150_MBUS_FMT)
		वापस -EINVAL;

	fse->code = TVP5150_MBUS_FMT;
	fse->min_width = decoder->rect.width;
	fse->max_width = decoder->rect.width;
	fse->min_height = decoder->rect.height / 2;
	fse->max_height = decoder->rect.height / 2;

	वापस 0;
पूर्ण

/****************************************************************************
 *			Media entity ops
 ****************************************************************************/
#अगर defined(CONFIG_MEDIA_CONTROLLER)
अटल पूर्णांक tvp5150_set_link(काष्ठा media_pad *connector_pad,
			    काष्ठा media_pad *tvp5150_pad, u32 flags)
अणु
	काष्ठा media_link *link;

	link = media_entity_find_link(connector_pad, tvp5150_pad);
	अगर (!link)
		वापस -EINVAL;

	link->flags = flags;
	link->reverse->flags = link->flags;

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_disable_all_input_links(काष्ठा tvp5150 *decoder)
अणु
	काष्ठा media_pad *connector_pad;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < TVP5150_NUM_PADS - 1; i++) अणु
		connector_pad = media_entity_remote_pad(&decoder->pads[i]);
		अगर (!connector_pad)
			जारी;

		err = tvp5150_set_link(connector_pad, &decoder->pads[i], 0);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_s_routing(काष्ठा v4l2_subdev *sd, u32 input, u32 output,
			     u32 config);

अटल पूर्णांक tvp5150_link_setup(काष्ठा media_entity *entity,
			      स्थिर काष्ठा media_pad *tvp5150_pad,
			      स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	काष्ठा media_pad *other_tvp5150_pad =
		&decoder->pads[tvp5150_pad->index ^ 1];
	काष्ठा v4l2_fwnode_connector *v4l2c;
	bool is_svideo = false;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/*
	 * The TVP5150 state is determined by the enabled sink pad link(s).
	 * Enabling or disabling the source pad link has no effect.
	 */
	अगर (tvp5150_pad->flags & MEDIA_PAD_FL_SOURCE)
		वापस 0;

	/* Check अगर the svideo connector should be enabled */
	क्रम (i = 0; i < decoder->connectors_num; i++) अणु
		अगर (remote->entity == &decoder->connectors[i].ent) अणु
			v4l2c = &decoder->connectors[i].base;
			is_svideo = v4l2c->type == V4L2_CONN_SVIDEO;
			अवरोध;
		पूर्ण
	पूर्ण

	dev_dbg_lvl(sd->dev, 1, debug, "link setup '%s':%d->'%s':%d[%d]",
		    remote->entity->name, remote->index,
		    tvp5150_pad->entity->name, tvp5150_pad->index,
		    flags & MEDIA_LNK_FL_ENABLED);
	अगर (is_svideo)
		dev_dbg_lvl(sd->dev, 1, debug,
			    "link setup '%s':%d->'%s':%d[%d]",
			    remote->entity->name, remote->index,
			    other_tvp5150_pad->entity->name,
			    other_tvp5150_pad->index,
			    flags & MEDIA_LNK_FL_ENABLED);

	/*
	 * The TVP5150 has an पूर्णांकernal mux which allows the following setup:
	 *
	 * comp-connector1  --\
	 *		       |---> AIP1A
	 *		      /
	 * svideo-connector -|
	 *		      \
	 *		       |---> AIP1B
	 * comp-connector2  --/
	 *
	 * We can't rely on user space that the current connector माला_लो disabled
	 * first beक्रमe enabling the new connector. Disable all active
	 * connector links to be on the safe side.
	 */
	err = tvp5150_disable_all_input_links(decoder);
	अगर (err)
		वापस err;

	tvp5150_s_routing(sd, is_svideo ? TVP5150_SVIDEO : tvp5150_pad->index,
			  flags & MEDIA_LNK_FL_ENABLED ? TVP5150_NORMAL :
			  TVP5150_BLACK_SCREEN, 0);

	अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
		काष्ठा v4l2_fwnode_connector_analog *v4l2ca;
		u32 new_norm;

		/*
		 * S-Video connector is conneted to both ports AIP1A and AIP1B.
		 * Both links must be enabled in one-shot regardless which link
		 * the user requests.
		 */
		अगर (is_svideo) अणु
			err = tvp5150_set_link((काष्ठा media_pad *)remote,
					       other_tvp5150_pad, flags);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (!decoder->connectors_num)
			वापस 0;

		/* Update the current connector */
		decoder->cur_connector =
			container_of(remote, काष्ठा tvp5150_connector, pad);

		/*
		 * Do nothing अगर the new connector supports the same tv-norms as
		 * the old one.
		 */
		v4l2ca = &decoder->cur_connector->base.connector.analog;
		new_norm = decoder->norm & v4l2ca->sdtv_stds;
		अगर (decoder->norm == new_norm)
			वापस 0;

		/*
		 * Fallback to the new connector tv-norms अगर we can't find any
		 * common between the current tv-norm and the new one.
		 */
		tvp5150_s_std(sd, new_norm ? new_norm : v4l2ca->sdtv_stds);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा media_entity_operations tvp5150_sd_media_ops = अणु
	.link_setup = tvp5150_link_setup,
पूर्ण;
#पूर्ण_अगर
/****************************************************************************
			I2C Command
 ****************************************************************************/
अटल पूर्णांक __maybe_unused tvp5150_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	अगर (decoder->irq)
		/* Disable lock पूर्णांकerrupt */
		वापस regmap_update_bits(decoder->regmap,
					  TVP5150_INT_ENABLE_REG_A,
					  TVP5150_INT_A_LOCK, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tvp5150_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_subdev *sd = dev_get_drvdata(dev);
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	अगर (decoder->irq)
		/* Enable lock पूर्णांकerrupt */
		वापस regmap_update_bits(decoder->regmap,
					  TVP5150_INT_ENABLE_REG_A,
					  TVP5150_INT_A_LOCK,
					  TVP5150_INT_A_LOCK);
	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	अचिन्हित पूर्णांक mask, val = 0;
	पूर्णांक ret;

	mask = TVP5150_MISC_CTL_YCBCR_OE | TVP5150_MISC_CTL_SYNC_OE |
	       TVP5150_MISC_CTL_CLOCK_OE;

	अगर (enable) अणु
		ret = pm_runसमय_get_sync(sd->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(sd->dev);
			वापस ret;
		पूर्ण

		tvp5150_enable(sd);

		/* Enable outमाला_दो अगर decoder is locked */
		अगर (decoder->irq)
			val = decoder->lock ? decoder->oe : 0;
		अन्यथा
			val = decoder->oe;

		v4l2_subdev_notअगरy_event(&decoder->sd, &tvp5150_ev_fmt);
	पूर्ण अन्यथा अणु
		pm_runसमय_put(sd->dev);
	पूर्ण

	regmap_update_bits(decoder->regmap, TVP5150_MISC_CTL, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_s_routing(काष्ठा v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	decoder->input = input;
	decoder->output = output;

	अगर (output == TVP5150_BLACK_SCREEN)
		decoder->enable = false;
	अन्यथा
		decoder->enable = true;

	tvp5150_selmux(sd);
	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_s_raw_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_vbi_क्रमmat *fmt)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	/*
	 * this is क्रम capturing 36 raw vbi lines
	 * अगर there's a way to cut off the beginning 2 vbi lines
	 * with the tvp5150 then the vbi line count could be lowered
	 * to 17 lines/field again, although I couldn't find a रेजिस्टर
	 * which could करो that cropping
	 */

	अगर (fmt->sample_क्रमmat == V4L2_PIX_FMT_GREY)
		regmap_ग_लिखो(decoder->regmap, TVP5150_LUMA_PROC_CTL_1, 0x70);
	अगर (fmt->count[0] == 18 && fmt->count[1] == 18) अणु
		regmap_ग_लिखो(decoder->regmap, TVP5150_VERT_BLANKING_START,
			     0x00);
		regmap_ग_लिखो(decoder->regmap, TVP5150_VERT_BLANKING_STOP, 0x01);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_s_sliced_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *svbi)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	पूर्णांक i;

	अगर (svbi->service_set != 0) अणु
		क्रम (i = 0; i <= 23; i++) अणु
			svbi->service_lines[1][i] = 0;
			svbi->service_lines[0][i] =
				tvp5150_set_vbi(sd, svbi->service_lines[0][i],
						0xf0, i, 3);
		पूर्ण
		/* Enables FIFO */
		regmap_ग_लिखो(decoder->regmap, TVP5150_FIFO_OUT_CTRL, 1);
	पूर्ण अन्यथा अणु
		/* Disables FIFO*/
		regmap_ग_लिखो(decoder->regmap, TVP5150_FIFO_OUT_CTRL, 0);

		/* Disable Full Field */
		regmap_ग_लिखो(decoder->regmap, TVP5150_FULL_FIELD_ENA, 0);

		/* Disable Line modes */
		क्रम (i = TVP5150_LINE_MODE_INI; i <= TVP5150_LINE_MODE_END; i++)
			regmap_ग_लिखो(decoder->regmap, i, 0xff);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_g_sliced_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *svbi)
अणु
	पूर्णांक i, mask = 0;

	स_रखो(svbi->service_lines, 0, माप(svbi->service_lines));

	क्रम (i = 0; i <= 23; i++) अणु
		svbi->service_lines[0][i] =
			tvp5150_get_vbi(sd, i);
		mask |= svbi->service_lines[0][i];
	पूर्ण
	svbi->service_set = mask;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक tvp5150_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	पूर्णांक res;

	res = tvp5150_पढ़ो(sd, reg->reg & 0xff);
	अगर (res < 0) अणु
		dev_err(sd->dev, "%s: failed with error = %d\n", __func__, res);
		वापस res;
	पूर्ण

	reg->val = res;
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);

	वापस regmap_ग_लिखो(decoder->regmap, reg->reg & 0xff, reg->val & 0xff);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tvp5150_subscribe_event(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
				   काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_src_change_event_subdev_subscribe(sd, fh, sub);
	हाल V4L2_EVENT_CTRL:
		वापस v4l2_ctrl_subdev_subscribe_event(sd, fh, sub);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tvp5150_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	पूर्णांक status = tvp5150_पढ़ो(sd, 0x88);

	vt->संकेत = ((status & 0x04) && (status & 0x02)) ? 0xffff : 0x0;
	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/*
	 * Setup connector pads and links. Enable the link to the first
	 * available connector per शेष.
	 */
	क्रम (i = 0; i < decoder->connectors_num; i++) अणु
		काष्ठा media_entity *con = &decoder->connectors[i].ent;
		काष्ठा media_pad *pad = &decoder->connectors[i].pad;
		काष्ठा v4l2_fwnode_connector *v4l2c =
			&decoder->connectors[i].base;
		काष्ठा v4l2_connector_link *link =
			v4l2_connector_first_link(v4l2c);
		अचिन्हित पूर्णांक port = link->fwnode_link.remote_port;
		अचिन्हित पूर्णांक flags = i ? 0 : MEDIA_LNK_FL_ENABLED;
		bool is_svideo = v4l2c->type == V4L2_CONN_SVIDEO;

		pad->flags = MEDIA_PAD_FL_SOURCE;
		ret = media_entity_pads_init(con, 1, pad);
		अगर (ret < 0)
			जाओ err;

		ret = media_device_रेजिस्टर_entity(sd->v4l2_dev->mdev, con);
		अगर (ret < 0)
			जाओ err;

		ret = media_create_pad_link(con, 0, &sd->entity, port, flags);
		अगर (ret < 0)
			जाओ err;

		अगर (is_svideo) अणु
			/*
			 * Check tvp5150_link_setup() comments क्रम more
			 * inक्रमmation.
			 */
			link = v4l2_connector_last_link(v4l2c);
			port = link->fwnode_link.remote_port;
			ret = media_create_pad_link(con, 0, &sd->entity, port,
						    flags);
			अगर (ret < 0)
				जाओ err;
		पूर्ण

		/* Enable शेष input. */
		अगर (flags == MEDIA_LNK_FL_ENABLED) अणु
			decoder->input =
				is_svideo ? TVP5150_SVIDEO :
				port == 0 ? TVP5150_COMPOSITE0 :
				TVP5150_COMPOSITE1;

			tvp5150_selmux(sd);
			decoder->cur_connector = &decoder->connectors[i];
			tvp5150_s_std(sd, v4l2c->connector.analog.sdtv_stds);
		पूर्ण
	पूर्ण

	वापस 0;

err:
	क्रम (i = 0; i < decoder->connectors_num; i++) अणु
		media_device_unरेजिस्टर_entity(&decoder->connectors[i].ent);
		media_entity_cleanup(&decoder->connectors[i].ent);
	पूर्ण
	वापस ret;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(sd->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(sd->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_बंद(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	pm_runसमय_put(sd->dev);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops tvp5150_ctrl_ops = अणु
	.s_ctrl = tvp5150_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops tvp5150_core_ops = अणु
	.log_status = tvp5150_log_status,
	.reset = tvp5150_reset,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = tvp5150_g_रेजिस्टर,
	.s_रेजिस्टर = tvp5150_s_रेजिस्टर,
#पूर्ण_अगर
	.subscribe_event = tvp5150_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops tvp5150_tuner_ops = अणु
	.g_tuner = tvp5150_g_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops tvp5150_video_ops = अणु
	.s_std = tvp5150_s_std,
	.g_std = tvp5150_g_std,
	.querystd = tvp5150_querystd,
	.s_stream = tvp5150_s_stream,
	.s_routing = tvp5150_s_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_vbi_ops tvp5150_vbi_ops = अणु
	.g_sliced_vbi_cap = tvp5150_g_sliced_vbi_cap,
	.g_sliced_fmt = tvp5150_g_sliced_fmt,
	.s_sliced_fmt = tvp5150_s_sliced_fmt,
	.s_raw_fmt = tvp5150_s_raw_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops tvp5150_pad_ops = अणु
	.init_cfg = tvp5150_init_cfg,
	.क्रमागत_mbus_code = tvp5150_क्रमागत_mbus_code,
	.क्रमागत_frame_size = tvp5150_क्रमागत_frame_size,
	.set_fmt = tvp5150_fill_fmt,
	.get_fmt = tvp5150_fill_fmt,
	.get_selection = tvp5150_get_selection,
	.set_selection = tvp5150_set_selection,
	.get_mbus_config = tvp5150_get_mbus_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tvp5150_ops = अणु
	.core = &tvp5150_core_ops,
	.tuner = &tvp5150_tuner_ops,
	.video = &tvp5150_video_ops,
	.vbi = &tvp5150_vbi_ops,
	.pad = &tvp5150_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops tvp5150_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = tvp5150_रेजिस्टरed,
	.खोलो = tvp5150_खोलो,
	.बंद = tvp5150_बंद,
पूर्ण;

/****************************************************************************
			I2C Client & Driver
 ****************************************************************************/

अटल स्थिर काष्ठा regmap_range tvp5150_पढ़ोable_ranges[] = अणु
	अणु
		.range_min = TVP5150_VD_IN_SRC_SEL_1,
		.range_max = TVP5150_AUTOSW_MSK,
	पूर्ण, अणु
		.range_min = TVP5150_COLOR_KIL_THSH_CTL,
		.range_max = TVP5150_CONF_SHARED_PIN,
	पूर्ण, अणु
		.range_min = TVP5150_ACT_VD_CROP_ST_MSB,
		.range_max = TVP5150_HORIZ_SYNC_START,
	पूर्ण, अणु
		.range_min = TVP5150_VERT_BLANKING_START,
		.range_max = TVP5150_INTT_CONFIG_REG_B,
	पूर्ण, अणु
		.range_min = TVP5150_VIDEO_STD,
		.range_max = TVP5150_VIDEO_STD,
	पूर्ण, अणु
		.range_min = TVP5150_CB_GAIN_FACT,
		.range_max = TVP5150_REV_SELECT,
	पूर्ण, अणु
		.range_min = TVP5150_MSB_DEV_ID,
		.range_max = TVP5150_STATUS_REG_5,
	पूर्ण, अणु
		.range_min = TVP5150_CC_DATA_INI,
		.range_max = TVP5150_TELETEXT_FIL_ENA,
	पूर्ण, अणु
		.range_min = TVP5150_INT_STATUS_REG_A,
		.range_max = TVP5150_FIFO_OUT_CTRL,
	पूर्ण, अणु
		.range_min = TVP5150_FULL_FIELD_ENA,
		.range_max = TVP5150_FULL_FIELD_MODE_REG,
	पूर्ण,
पूर्ण;

अटल bool tvp5150_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TVP5150_VERT_LN_COUNT_MSB:
	हाल TVP5150_VERT_LN_COUNT_LSB:
	हाल TVP5150_INT_STATUS_REG_A:
	हाल TVP5150_INT_STATUS_REG_B:
	हाल TVP5150_INT_ACTIVE_REG_B:
	हाल TVP5150_STATUS_REG_1:
	हाल TVP5150_STATUS_REG_2:
	हाल TVP5150_STATUS_REG_3:
	हाल TVP5150_STATUS_REG_4:
	हाल TVP5150_STATUS_REG_5:
	/* CC, WSS, VPS, VITC data? */
	हाल TVP5150_VBI_FIFO_READ_DATA:
	हाल TVP5150_VDP_STATUS_REG:
	हाल TVP5150_FIFO_WORD_COUNT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_access_table tvp5150_पढ़ोable_table = अणु
	.yes_ranges = tvp5150_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(tvp5150_पढ़ोable_ranges),
पूर्ण;

अटल काष्ठा regmap_config tvp5150_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xff,

	.cache_type = REGCACHE_RBTREE,

	.rd_table = &tvp5150_पढ़ोable_table,
	.अस्थिर_reg = tvp5150_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक tvp5150_detect_version(काष्ठा tvp5150 *core)
अणु
	काष्ठा v4l2_subdev *sd = &core->sd;
	काष्ठा i2c_client *c = v4l2_get_subdevdata(sd);
	u8 regs[4];
	पूर्णांक res;

	/*
	 * Read consequent रेजिस्टरs - TVP5150_MSB_DEV_ID, TVP5150_LSB_DEV_ID,
	 * TVP5150_ROM_MAJOR_VER, TVP5150_ROM_MINOR_VER
	 */
	res = regmap_bulk_पढ़ो(core->regmap, TVP5150_MSB_DEV_ID, regs, 4);
	अगर (res < 0) अणु
		dev_err(&c->dev, "reading ID registers failed: %d\n", res);
		वापस res;
	पूर्ण

	core->dev_id = (regs[0] << 8) | regs[1];
	core->rom_ver = (regs[2] << 8) | regs[3];

	dev_info(sd->dev, "tvp%04x (%u.%u) chip found @ 0x%02x (%s)\n",
		  core->dev_id, regs[2], regs[3], c->addr << 1,
		  c->adapter->name);

	अगर (core->dev_id == 0x5150 && core->rom_ver == 0x0321) अणु
		dev_info(sd->dev, "tvp5150a detected.\n");
	पूर्ण अन्यथा अगर (core->dev_id == 0x5150 && core->rom_ver == 0x0400) अणु
		dev_info(sd->dev, "tvp5150am1 detected.\n");

		/* ITU-T BT.656.4 timing */
		regmap_ग_लिखो(core->regmap, TVP5150_REV_SELECT, 0);
	पूर्ण अन्यथा अगर (core->dev_id == 0x5151 && core->rom_ver == 0x0100) अणु
		dev_info(sd->dev, "tvp5151 detected.\n");
	पूर्ण अन्यथा अणु
		dev_info(sd->dev, "*** unknown tvp%04x chip detected.\n",
			  core->dev_id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_init(काष्ठा i2c_client *c)
अणु
	काष्ठा gpio_desc *pdn_gpio;
	काष्ठा gpio_desc *reset_gpio;

	pdn_gpio = devm_gpiod_get_optional(&c->dev, "pdn", GPIOD_OUT_HIGH);
	अगर (IS_ERR(pdn_gpio))
		वापस PTR_ERR(pdn_gpio);

	अगर (pdn_gpio) अणु
		gpiod_set_value_cansleep(pdn_gpio, 0);
		/* Delay समय between घातer supplies active and reset */
		msleep(20);
	पूर्ण

	reset_gpio = devm_gpiod_get_optional(&c->dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(reset_gpio))
		वापस PTR_ERR(reset_gpio);

	अगर (reset_gpio) अणु
		/* RESETB pulse duration */
		ndelay(500);
		gpiod_set_value_cansleep(reset_gpio, 0);
		/* Delay समय between end of reset to I2C active */
		usleep_range(200, 250);
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_MEDIA_CONTROLLER)
अटल पूर्णांक tvp5150_mc_init(काष्ठा tvp5150 *decoder)
अणु
	काष्ठा v4l2_subdev *sd = &decoder->sd;
	अचिन्हित पूर्णांक i;

	sd->entity.ops = &tvp5150_sd_media_ops;
	sd->entity.function = MEDIA_ENT_F_ATV_DECODER;

	क्रम (i = 0; i < TVP5150_NUM_PADS - 1; i++) अणु
		decoder->pads[i].flags = MEDIA_PAD_FL_SINK;
		decoder->pads[i].sig_type = PAD_SIGNAL_ANALOG;
	पूर्ण

	decoder->pads[i].flags = MEDIA_PAD_FL_SOURCE;
	decoder->pads[i].sig_type = PAD_SIGNAL_DV;

	वापस media_entity_pads_init(&sd->entity, TVP5150_NUM_PADS,
				      decoder->pads);
पूर्ण

#अन्यथा /* !defined(CONFIG_MEDIA_CONTROLLER) */

अटल अंतरभूत पूर्णांक tvp5150_mc_init(काष्ठा tvp5150 *decoder)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_MEDIA_CONTROLLER) */

अटल पूर्णांक tvp5150_validate_connectors(काष्ठा tvp5150 *decoder)
अणु
	काष्ठा device *dev = decoder->sd.dev;
	काष्ठा tvp5150_connector *tvpc;
	काष्ठा v4l2_fwnode_connector *v4l2c;
	अचिन्हित पूर्णांक i;

	अगर (!decoder->connectors_num) अणु
		dev_err(dev, "No valid connector found\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < decoder->connectors_num; i++) अणु
		काष्ठा v4l2_connector_link *link0 = शून्य;
		काष्ठा v4l2_connector_link *link1;

		tvpc = &decoder->connectors[i];
		v4l2c = &tvpc->base;

		अगर (v4l2c->type == V4L2_CONN_COMPOSITE) अणु
			अगर (v4l2c->nr_of_links != 1) अणु
				dev_err(dev, "Composite: connector needs 1 link\n");
				वापस -EINVAL;
			पूर्ण
			link0 = v4l2_connector_first_link(v4l2c);
			अगर (!link0) अणु
				dev_err(dev, "Composite: invalid first link\n");
				वापस -EINVAL;
			पूर्ण
			अगर (link0->fwnode_link.remote_id == 1) अणु
				dev_err(dev, "Composite: invalid endpoint id\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (v4l2c->type == V4L2_CONN_SVIDEO) अणु
			अगर (v4l2c->nr_of_links != 2) अणु
				dev_err(dev, "SVideo: connector needs 2 links\n");
				वापस -EINVAL;
			पूर्ण
			link0 = v4l2_connector_first_link(v4l2c);
			अगर (!link0) अणु
				dev_err(dev, "SVideo: invalid first link\n");
				वापस -EINVAL;
			पूर्ण
			link1 = v4l2_connector_last_link(v4l2c);
			अगर (link0->fwnode_link.remote_port ==
			    link1->fwnode_link.remote_port) अणु
				dev_err(dev, "SVideo: invalid link setup\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (!(v4l2c->connector.analog.sdtv_stds & TVP5150_STD_MASK)) अणु
			dev_err(dev, "Unsupported tv-norm on connector %s\n",
				v4l2c->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tvp5150_parse_dt(काष्ठा tvp5150 *decoder, काष्ठा device_node *np)
अणु
	काष्ठा device *dev = decoder->sd.dev;
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु
		.bus_type = V4L2_MBUS_UNKNOWN
	पूर्ण;
	काष्ठा device_node *ep_np;
	काष्ठा tvp5150_connector *tvpc;
	काष्ठा v4l2_fwnode_connector *v4l2c;
	अचिन्हित पूर्णांक flags, ep_num;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* At least 1 output and 1 input */
	ep_num = of_graph_get_endpoपूर्णांक_count(np);
	अगर (ep_num < 2 || ep_num > 5) अणु
		dev_err(dev, "At least 1 input and 1 output must be connected to the device.\n");
		वापस -EINVAL;
	पूर्ण

	/* Layout अगर all connectors are used:
	 *
	 * tvp-5150 port@0 (AIP1A)
	 *	endpoपूर्णांक@0 -----------> Comp0-Con  port
	 *	endpoपूर्णांक@1 --------+--> Svideo-Con port
	 * tvp-5150 port@1 (AIP1B) |
	 *	endpoपूर्णांक@1 --------+
	 *	endpoपूर्णांक@0 -----------> Comp1-Con  port
	 * tvp-5150 port@2
	 *	endpoपूर्णांक (video bitstream output at YOUT[0-7] parallel bus)
	 */
	क्रम_each_endpoपूर्णांक_of_node(np, ep_np) अणु
		काष्ठा fwnode_handle *ep_fwnode = of_fwnode_handle(ep_np);
		अचिन्हित पूर्णांक next_connector = decoder->connectors_num;
		काष्ठा of_endpoपूर्णांक ep;

		of_graph_parse_endpoपूर्णांक(ep_np, &ep);
		अगर (ep.port > 1 || ep.id > 1) अणु
			dev_dbg(dev, "Ignore connector on port@%u/ep@%u\n",
				ep.port, ep.id);
			जारी;
		पूर्ण

		tvpc = &decoder->connectors[next_connector];
		v4l2c = &tvpc->base;

		अगर (ep.port == 0 || (ep.port == 1 && ep.id == 0)) अणु
			ret = v4l2_fwnode_connector_parse(ep_fwnode, v4l2c);
			अगर (ret)
				जाओ err_put;
			ret = v4l2_fwnode_connector_add_link(ep_fwnode, v4l2c);
			अगर (ret)
				जाओ err_put;
			decoder->connectors_num++;
		पूर्ण अन्यथा अणु
			/* Adding the 2nd svideo link */
			क्रम (i = 0; i < TVP5150_MAX_CONNECTORS; i++) अणु
				tvpc = &decoder->connectors[i];
				v4l2c = &tvpc->base;
				अगर (v4l2c->type == V4L2_CONN_SVIDEO)
					अवरोध;
			पूर्ण

			ret = v4l2_fwnode_connector_add_link(ep_fwnode, v4l2c);
			अगर (ret)
				जाओ err_put;
		पूर्ण
	पूर्ण

	ret = tvp5150_validate_connectors(decoder);
	अगर (ret)
		जाओ err_मुक्त;

	क्रम (i = 0; i < decoder->connectors_num; i++) अणु
		tvpc = &decoder->connectors[i];
		v4l2c = &tvpc->base;
		tvpc->ent.flags = MEDIA_ENT_FL_CONNECTOR;
		tvpc->ent.function = v4l2c->type == V4L2_CONN_SVIDEO ?
			MEDIA_ENT_F_CONN_SVIDEO : MEDIA_ENT_F_CONN_COMPOSITE;
		tvpc->ent.name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s %s",
						v4l2c->name, v4l2c->label ?
						v4l2c->label : "");
	पूर्ण

	ep_np = of_graph_get_endpoपूर्णांक_by_regs(np, TVP5150_PAD_VID_OUT, 0);
	अगर (!ep_np) अणु
		ret = -EINVAL;
		dev_err(dev, "Error no output endpoint available\n");
		जाओ err_मुक्त;
	पूर्ण
	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep_np), &bus_cfg);
	of_node_put(ep_np);
	अगर (ret)
		जाओ err_मुक्त;

	flags = bus_cfg.bus.parallel.flags;
	अगर (bus_cfg.bus_type == V4L2_MBUS_PARALLEL &&
	    !(flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH &&
	      flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH &&
	      flags & V4L2_MBUS_FIELD_EVEN_LOW)) अणु
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	decoder->mbus_type = bus_cfg.bus_type;

	वापस 0;

err_put:
	of_node_put(ep_np);
err_मुक्त:
	क्रम (i = 0; i < TVP5150_MAX_CONNECTORS; i++)
		v4l2_fwnode_connector_मुक्त(&decoder->connectors[i].base);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर tvp5150_test_patterns[2] = अणु
	"Disabled",
	"Black screen"
पूर्ण;

अटल पूर्णांक tvp5150_probe(काष्ठा i2c_client *c)
अणु
	काष्ठा tvp5150 *core;
	काष्ठा v4l2_subdev *sd;
	काष्ठा device_node *np = c->dev.of_node;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक i;
	पूर्णांक res;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(c->adapter,
	     I2C_FUNC_SMBUS_READ_BYTE | I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		वापस -EIO;

	res = tvp5150_init(c);
	अगर (res)
		वापस res;

	core = devm_kzalloc(&c->dev, माप(*core), GFP_KERNEL);
	अगर (!core)
		वापस -ENOMEM;

	map = devm_regmap_init_i2c(c, &tvp5150_config);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	core->regmap = map;
	sd = &core->sd;
	v4l2_i2c_subdev_init(sd, c, &tvp5150_ops);
	sd->पूर्णांकernal_ops = &tvp5150_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;

	अगर (IS_ENABLED(CONFIG_OF) && np) अणु
		res = tvp5150_parse_dt(core, np);
		अगर (res) अणु
			dev_err(sd->dev, "DT parsing error: %d\n", res);
			वापस res;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Default to BT.656 embedded sync */
		core->mbus_type = V4L2_MBUS_BT656;
	पूर्ण

	res = tvp5150_mc_init(core);
	अगर (res)
		वापस res;

	res = tvp5150_detect_version(core);
	अगर (res < 0)
		वापस res;

	/*
	 * Iterate over all available connectors in हाल they are supported and
	 * successfully parsed. Fallback to शेष स्वतःdetect in हाल they
	 * aren't supported.
	 */
	क्रम (i = 0; i < core->connectors_num; i++) अणु
		काष्ठा v4l2_fwnode_connector *v4l2c;

		v4l2c = &core->connectors[i].base;
		core->norm |= v4l2c->connector.analog.sdtv_stds;
	पूर्ण

	अगर (!core->connectors_num)
		core->norm = V4L2_STD_ALL;

	core->detected_norm = V4L2_STD_UNKNOWN;
	core->input = TVP5150_COMPOSITE1;
	core->enable = true;

	v4l2_ctrl_handler_init(&core->hdl, 5);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_PIXEL_RATE, 27000000,
			27000000, 1, 27000000);
	v4l2_ctrl_new_std_menu_items(&core->hdl, &tvp5150_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(tvp5150_test_patterns) - 1,
				     0, 0, tvp5150_test_patterns);
	sd->ctrl_handler = &core->hdl;
	अगर (core->hdl.error) अणु
		res = core->hdl.error;
		जाओ err;
	पूर्ण

	tvp5150_set_शेष(tvp5150_पढ़ो_std(sd), &core->rect);

	core->irq = c->irq;
	tvp5150_reset(sd, 0);	/* Calls v4l2_ctrl_handler_setup() */
	अगर (c->irq) अणु
		res = devm_request_thपढ़ोed_irq(&c->dev, c->irq, शून्य,
						tvp5150_isr, IRQF_TRIGGER_HIGH |
						IRQF_ONESHOT, "tvp5150", core);
		अगर (res)
			जाओ err;
	पूर्ण

	res = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (res < 0)
		जाओ err;

	अगर (debug > 1)
		tvp5150_log_status(sd);

	pm_runसमय_set_active(&c->dev);
	pm_runसमय_enable(&c->dev);
	pm_runसमय_idle(&c->dev);

	वापस 0;

err:
	v4l2_ctrl_handler_मुक्त(&core->hdl);
	वापस res;
पूर्ण

अटल पूर्णांक tvp5150_हटाओ(काष्ठा i2c_client *c)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(c);
	काष्ठा tvp5150 *decoder = to_tvp5150(sd);
	अचिन्हित पूर्णांक i;

	dev_dbg_lvl(sd->dev, 1, debug,
		"tvp5150.c: removing tvp5150 adapter on address 0x%x\n",
		c->addr << 1);

	क्रम (i = 0; i < decoder->connectors_num; i++)
		v4l2_fwnode_connector_मुक्त(&decoder->connectors[i].base);
	क्रम (i = 0; i < decoder->connectors_num; i++) अणु
		media_device_unरेजिस्टर_entity(&decoder->connectors[i].ent);
		media_entity_cleanup(&decoder->connectors[i].ent);
	पूर्ण
	v4l2_async_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&decoder->hdl);
	pm_runसमय_disable(&c->dev);
	pm_runसमय_set_suspended(&c->dev);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा dev_pm_ops tvp5150_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tvp5150_runसमय_suspend,
			   tvp5150_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id tvp5150_id[] = अणु
	अणु "tvp5150", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tvp5150_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tvp5150_of_match[] = अणु
	अणु .compatible = "ti,tvp5150", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tvp5150_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tvp5150_driver = अणु
	.driver = अणु
		.of_match_table = of_match_ptr(tvp5150_of_match),
		.name	= "tvp5150",
		.pm	= &tvp5150_pm_ops,
	पूर्ण,
	.probe_new	= tvp5150_probe,
	.हटाओ		= tvp5150_हटाओ,
	.id_table	= tvp5150_id,
पूर्ण;

module_i2c_driver(tvp5150_driver);
