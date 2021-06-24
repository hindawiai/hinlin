<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/i2c/tvp514x.c
 *
 * TI TVP5146/47 decoder driver
 *
 * Copyright (C) 2008 Texas Instruments Inc
 * Author: Vaibhav Hiremath <hvaibhav@ti.com>
 *
 * Contributors:
 *     Sivaraj R <sivaraj@ti.com>
 *     Brijesh R Jadav <brijesh.j@ti.com>
 *     Hardik Shah <hardik.shah@ti.com>
 *     Manjunath Hadli <mrh@ti.com>
 *     Karicheri Muralidharan <m-karicheri2@ti.com>
 *     Prabhakar Lad <prabhakar.lad@ti.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/module.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/i2c/tvp514x.h>
#समावेश <media/media-entity.h>

#समावेश "tvp514x_regs.h"

/* Private macros क्रम TVP */
#घोषणा I2C_RETRY_COUNT                 (5)
#घोषणा LOCK_RETRY_COUNT                (5)
#घोषणा LOCK_RETRY_DELAY                (200)

/* Debug functions */
अटल bool debug;
module_param(debug, bool, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-1)");

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("TVP514X linux decoder driver");
MODULE_LICENSE("GPL");

/* क्रमागत tvp514x_std - क्रमागत क्रम supported standards */
क्रमागत tvp514x_std अणु
	STD_NTSC_MJ = 0,
	STD_PAL_BDGHIN,
	STD_INVALID
पूर्ण;

/**
 * काष्ठा tvp514x_std_info - Structure to store standard inक्रमmation
 * @width: Line width in pixels
 * @height:Number of active lines
 * @video_std: Value to ग_लिखो in REG_VIDEO_STD रेजिस्टर
 * @standard: v4l2 standard काष्ठाure inक्रमmation
 */
काष्ठा tvp514x_std_info अणु
	अचिन्हित दीर्घ width;
	अचिन्हित दीर्घ height;
	u8 video_std;
	काष्ठा v4l2_standard standard;
पूर्ण;

अटल काष्ठा tvp514x_reg tvp514x_reg_list_शेष[0x40];

अटल पूर्णांक tvp514x_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable);
/**
 * काष्ठा tvp514x_decoder - TVP5146/47 decoder object
 * @sd: Subdevice Slave handle
 * @hdl: embedded &काष्ठा v4l2_ctrl_handler
 * @tvp514x_regs: copy of hw's regs with preset values.
 * @pdata: Board specअगरic
 * @ver: Chip version
 * @streaming: TVP5146/47 decoder streaming - enabled or disabled.
 * @pix: Current pixel क्रमmat
 * @num_fmts: Number of क्रमmats
 * @fmt_list: Format list
 * @current_std: Current standard
 * @num_stds: Number of standards
 * @std_list: Standards list
 * @input: Input routing at chip level
 * @output: Output routing at chip level
 * @pad: subdev media pad associated with the decoder
 * @क्रमmat: media bus frame क्रमmat
 * @पूर्णांक_seq: driver's रेजिस्टर init sequence
 */
काष्ठा tvp514x_decoder अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा tvp514x_reg tvp514x_regs[ARRAY_SIZE(tvp514x_reg_list_शेष)];
	स्थिर काष्ठा tvp514x_platक्रमm_data *pdata;

	पूर्णांक ver;
	पूर्णांक streaming;

	काष्ठा v4l2_pix_क्रमmat pix;
	पूर्णांक num_fmts;
	स्थिर काष्ठा v4l2_fmtdesc *fmt_list;

	क्रमागत tvp514x_std current_std;
	पूर्णांक num_stds;
	स्थिर काष्ठा tvp514x_std_info *std_list;
	/* Input and Output Routing parameters */
	u32 input;
	u32 output;

	/* mc related members */
	काष्ठा media_pad pad;
	काष्ठा v4l2_mbus_framefmt क्रमmat;

	काष्ठा tvp514x_reg *पूर्णांक_seq;
पूर्ण;

/* TVP514x शेष रेजिस्टर values */
अटल काष्ठा tvp514x_reg tvp514x_reg_list_शेष[] = अणु
	/* Composite selected */
	अणुTOK_WRITE, REG_INPUT_SEL, 0x05पूर्ण,
	अणुTOK_WRITE, REG_AFE_GAIN_CTRL, 0x0Fपूर्ण,
	/* Auto mode */
	अणुTOK_WRITE, REG_VIDEO_STD, 0x00पूर्ण,
	अणुTOK_WRITE, REG_OPERATION_MODE, 0x00पूर्ण,
	अणुTOK_SKIP, REG_AUTOSWITCH_MASK, 0x3Fपूर्ण,
	अणुTOK_WRITE, REG_COLOR_KILLER, 0x10पूर्ण,
	अणुTOK_WRITE, REG_LUMA_CONTROL1, 0x00पूर्ण,
	अणुTOK_WRITE, REG_LUMA_CONTROL2, 0x00पूर्ण,
	अणुTOK_WRITE, REG_LUMA_CONTROL3, 0x02पूर्ण,
	अणुTOK_WRITE, REG_BRIGHTNESS, 0x80पूर्ण,
	अणुTOK_WRITE, REG_CONTRAST, 0x80पूर्ण,
	अणुTOK_WRITE, REG_SATURATION, 0x80पूर्ण,
	अणुTOK_WRITE, REG_HUE, 0x00पूर्ण,
	अणुTOK_WRITE, REG_CHROMA_CONTROL1, 0x00पूर्ण,
	अणुTOK_WRITE, REG_CHROMA_CONTROL2, 0x0Eपूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x0F, 0x00पूर्ण,
	अणुTOK_WRITE, REG_COMP_PR_SATURATION, 0x80पूर्ण,
	अणुTOK_WRITE, REG_COMP_Y_CONTRAST, 0x80पूर्ण,
	अणुTOK_WRITE, REG_COMP_PB_SATURATION, 0x80पूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x13, 0x00पूर्ण,
	अणुTOK_WRITE, REG_COMP_Y_BRIGHTNESS, 0x80पूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x15, 0x00पूर्ण,
	/* NTSC timing */
	अणुTOK_SKIP, REG_AVID_START_PIXEL_LSB, 0x55पूर्ण,
	अणुTOK_SKIP, REG_AVID_START_PIXEL_MSB, 0x00पूर्ण,
	अणुTOK_SKIP, REG_AVID_STOP_PIXEL_LSB, 0x25पूर्ण,
	अणुTOK_SKIP, REG_AVID_STOP_PIXEL_MSB, 0x03पूर्ण,
	/* NTSC timing */
	अणुTOK_SKIP, REG_HSYNC_START_PIXEL_LSB, 0x00पूर्ण,
	अणुTOK_SKIP, REG_HSYNC_START_PIXEL_MSB, 0x00पूर्ण,
	अणुTOK_SKIP, REG_HSYNC_STOP_PIXEL_LSB, 0x40पूर्ण,
	अणुTOK_SKIP, REG_HSYNC_STOP_PIXEL_MSB, 0x00पूर्ण,
	/* NTSC timing */
	अणुTOK_SKIP, REG_VSYNC_START_LINE_LSB, 0x04पूर्ण,
	अणुTOK_SKIP, REG_VSYNC_START_LINE_MSB, 0x00पूर्ण,
	अणुTOK_SKIP, REG_VSYNC_STOP_LINE_LSB, 0x07पूर्ण,
	अणुTOK_SKIP, REG_VSYNC_STOP_LINE_MSB, 0x00पूर्ण,
	/* NTSC timing */
	अणुTOK_SKIP, REG_VBLK_START_LINE_LSB, 0x01पूर्ण,
	अणुTOK_SKIP, REG_VBLK_START_LINE_MSB, 0x00पूर्ण,
	अणुTOK_SKIP, REG_VBLK_STOP_LINE_LSB, 0x15पूर्ण,
	अणुTOK_SKIP, REG_VBLK_STOP_LINE_MSB, 0x00पूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x26, 0x00पूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x27, 0x00पूर्ण,
	अणुTOK_SKIP, REG_FAST_SWTICH_CONTROL, 0xCCपूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x29, 0x00पूर्ण,
	अणुTOK_SKIP, REG_FAST_SWTICH_SCART_DELAY, 0x00पूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x2B, 0x00पूर्ण,
	अणुTOK_SKIP, REG_SCART_DELAY, 0x00पूर्ण,
	अणुTOK_SKIP, REG_CTI_DELAY, 0x00पूर्ण,
	अणुTOK_SKIP, REG_CTI_CONTROL, 0x00पूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x2F, 0x00पूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x30, 0x00पूर्ण,
	/* Reserved */
	अणुTOK_SKIP, 0x31, 0x00पूर्ण,
	/* HS, VS active high */
	अणुTOK_WRITE, REG_SYNC_CONTROL, 0x00पूर्ण,
	/* 10-bit BT.656 */
	अणुTOK_WRITE, REG_OUTPUT_FORMATTER1, 0x00पूर्ण,
	/* Enable clk & data */
	अणुTOK_WRITE, REG_OUTPUT_FORMATTER2, 0x11पूर्ण,
	/* Enable AVID & FLD */
	अणुTOK_WRITE, REG_OUTPUT_FORMATTER3, 0xEEपूर्ण,
	/* Enable VS & HS */
	अणुTOK_WRITE, REG_OUTPUT_FORMATTER4, 0xAFपूर्ण,
	अणुTOK_WRITE, REG_OUTPUT_FORMATTER5, 0xFFपूर्ण,
	अणुTOK_WRITE, REG_OUTPUT_FORMATTER6, 0xFFपूर्ण,
	/* Clear status */
	अणुTOK_WRITE, REG_CLEAR_LOST_LOCK, 0x01पूर्ण,
	अणुTOK_TERM, 0, 0पूर्ण,
पूर्ण;

/*
 * List of image क्रमmats supported by TVP5146/47 decoder
 * Currently we are using 8 bit mode only, but can be
 * extended to 10/20 bit mode.
 */
अटल स्थिर काष्ठा v4l2_fmtdesc tvp514x_fmt_list[] = अणु
	अणु
	 .index		= 0,
	 .type		= V4L2_BUF_TYPE_VIDEO_CAPTURE,
	 .flags		= 0,
	 .description	= "8-bit UYVY 4:2:2 Format",
	 .pixelक्रमmat	= V4L2_PIX_FMT_UYVY,
	पूर्ण,
पूर्ण;

/*
 * Supported standards -
 *
 * Currently supports two standards only, need to add support क्रम rest of the
 * modes, like SECAM, etc...
 */
अटल स्थिर काष्ठा tvp514x_std_info tvp514x_std_list[] = अणु
	/* Standard: STD_NTSC_MJ */
	[STD_NTSC_MJ] = अणु
	 .width = NTSC_NUM_ACTIVE_PIXELS,
	 .height = NTSC_NUM_ACTIVE_LINES,
	 .video_std = VIDEO_STD_NTSC_MJ_BIT,
	 .standard = अणु
		      .index = 0,
		      .id = V4L2_STD_NTSC,
		      .name = "NTSC",
		      .frameperiod = अणु1001, 30000पूर्ण,
		      .framelines = 525
		     पूर्ण,
	/* Standard: STD_PAL_BDGHIN */
	पूर्ण,
	[STD_PAL_BDGHIN] = अणु
	 .width = PAL_NUM_ACTIVE_PIXELS,
	 .height = PAL_NUM_ACTIVE_LINES,
	 .video_std = VIDEO_STD_PAL_BDGHIN_BIT,
	 .standard = अणु
		      .index = 1,
		      .id = V4L2_STD_PAL,
		      .name = "PAL",
		      .frameperiod = अणु1, 25पूर्ण,
		      .framelines = 625
		     पूर्ण,
	पूर्ण,
	/* Standard: need to add क्रम additional standard */
पूर्ण;


अटल अंतरभूत काष्ठा tvp514x_decoder *to_decoder(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tvp514x_decoder, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा tvp514x_decoder, hdl)->sd;
पूर्ण


/**
 * tvp514x_पढ़ो_reg() - Read a value from a रेजिस्टर in an TVP5146/47.
 * @sd: ptr to v4l2_subdev काष्ठा
 * @reg: TVP5146/47 रेजिस्टर address
 *
 * Returns value पढ़ो अगर successful, or non-zero (-1) otherwise.
 */
अटल पूर्णांक tvp514x_पढ़ो_reg(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	पूर्णांक err, retry = 0;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

पढ़ो_again:

	err = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (err < 0) अणु
		अगर (retry <= I2C_RETRY_COUNT) अणु
			v4l2_warn(sd, "Read: retry ... %d\n", retry);
			retry++;
			msleep_पूर्णांकerruptible(10);
			जाओ पढ़ो_again;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * dump_reg() - dump the रेजिस्टर content of TVP5146/47.
 * @sd: ptr to v4l2_subdev काष्ठा
 * @reg: TVP5146/47 रेजिस्टर address
 */
अटल व्योम dump_reg(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	u32 val;

	val = tvp514x_पढ़ो_reg(sd, reg);
	v4l2_info(sd, "Reg(0x%.2X): 0x%.2X\n", reg, val);
पूर्ण

/**
 * tvp514x_ग_लिखो_reg() - Write a value to a रेजिस्टर in TVP5146/47
 * @sd: ptr to v4l2_subdev काष्ठा
 * @reg: TVP5146/47 रेजिस्टर address
 * @val: value to be written to the रेजिस्टर
 *
 * Write a value to a रेजिस्टर in an TVP5146/47 decoder device.
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक tvp514x_ग_लिखो_reg(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	पूर्णांक err, retry = 0;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

ग_लिखो_again:

	err = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
	अगर (err) अणु
		अगर (retry <= I2C_RETRY_COUNT) अणु
			v4l2_warn(sd, "Write: retry ... %d\n", retry);
			retry++;
			msleep_पूर्णांकerruptible(10);
			जाओ ग_लिखो_again;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * tvp514x_ग_लिखो_regs() : Initializes a list of TVP5146/47 रेजिस्टरs
 * @sd: ptr to v4l2_subdev काष्ठा
 * @reglist: list of TVP5146/47 रेजिस्टरs and values
 *
 * Initializes a list of TVP5146/47 रेजिस्टरs:-
 *		अगर token is TOK_TERM, then entire ग_लिखो operation terminates
 *		अगर token is TOK_DELAY, then a delay of 'val' msec is पूर्णांकroduced
 *		अगर token is TOK_SKIP, then the रेजिस्टर ग_लिखो is skipped
 *		अगर token is TOK_WRITE, then the रेजिस्टर ग_लिखो is perक्रमmed
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक tvp514x_ग_लिखो_regs(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा tvp514x_reg reglist[])
अणु
	पूर्णांक err;
	स्थिर काष्ठा tvp514x_reg *next = reglist;

	क्रम (; next->token != TOK_TERM; next++) अणु
		अगर (next->token == TOK_DELAY) अणु
			msleep(next->val);
			जारी;
		पूर्ण

		अगर (next->token == TOK_SKIP)
			जारी;

		err = tvp514x_ग_लिखो_reg(sd, next->reg, (u8) next->val);
		अगर (err) अणु
			v4l2_err(sd, "Write failed. Err[%d]\n", err);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * tvp514x_query_current_std() : Query the current standard detected by TVP5146/47
 * @sd: ptr to v4l2_subdev काष्ठा
 *
 * Returns the current standard detected by TVP5146/47, STD_INVALID अगर there is no
 * standard detected.
 */
अटल क्रमागत tvp514x_std tvp514x_query_current_std(काष्ठा v4l2_subdev *sd)
अणु
	u8 std, std_status;

	std = tvp514x_पढ़ो_reg(sd, REG_VIDEO_STD);
	अगर ((std & VIDEO_STD_MASK) == VIDEO_STD_AUTO_SWITCH_BIT)
		/* use the standard status रेजिस्टर */
		std_status = tvp514x_पढ़ो_reg(sd, REG_VIDEO_STD_STATUS);
	अन्यथा
		/* use the standard रेजिस्टर itself */
		std_status = std;

	चयन (std_status & VIDEO_STD_MASK) अणु
	हाल VIDEO_STD_NTSC_MJ_BIT:
		वापस STD_NTSC_MJ;

	हाल VIDEO_STD_PAL_BDGHIN_BIT:
		वापस STD_PAL_BDGHIN;

	शेष:
		वापस STD_INVALID;
	पूर्ण

	वापस STD_INVALID;
पूर्ण

/* TVP5146/47 रेजिस्टर dump function */
अटल व्योम tvp514x_reg_dump(काष्ठा v4l2_subdev *sd)
अणु
	dump_reg(sd, REG_INPUT_SEL);
	dump_reg(sd, REG_AFE_GAIN_CTRL);
	dump_reg(sd, REG_VIDEO_STD);
	dump_reg(sd, REG_OPERATION_MODE);
	dump_reg(sd, REG_COLOR_KILLER);
	dump_reg(sd, REG_LUMA_CONTROL1);
	dump_reg(sd, REG_LUMA_CONTROL2);
	dump_reg(sd, REG_LUMA_CONTROL3);
	dump_reg(sd, REG_BRIGHTNESS);
	dump_reg(sd, REG_CONTRAST);
	dump_reg(sd, REG_SATURATION);
	dump_reg(sd, REG_HUE);
	dump_reg(sd, REG_CHROMA_CONTROL1);
	dump_reg(sd, REG_CHROMA_CONTROL2);
	dump_reg(sd, REG_COMP_PR_SATURATION);
	dump_reg(sd, REG_COMP_Y_CONTRAST);
	dump_reg(sd, REG_COMP_PB_SATURATION);
	dump_reg(sd, REG_COMP_Y_BRIGHTNESS);
	dump_reg(sd, REG_AVID_START_PIXEL_LSB);
	dump_reg(sd, REG_AVID_START_PIXEL_MSB);
	dump_reg(sd, REG_AVID_STOP_PIXEL_LSB);
	dump_reg(sd, REG_AVID_STOP_PIXEL_MSB);
	dump_reg(sd, REG_HSYNC_START_PIXEL_LSB);
	dump_reg(sd, REG_HSYNC_START_PIXEL_MSB);
	dump_reg(sd, REG_HSYNC_STOP_PIXEL_LSB);
	dump_reg(sd, REG_HSYNC_STOP_PIXEL_MSB);
	dump_reg(sd, REG_VSYNC_START_LINE_LSB);
	dump_reg(sd, REG_VSYNC_START_LINE_MSB);
	dump_reg(sd, REG_VSYNC_STOP_LINE_LSB);
	dump_reg(sd, REG_VSYNC_STOP_LINE_MSB);
	dump_reg(sd, REG_VBLK_START_LINE_LSB);
	dump_reg(sd, REG_VBLK_START_LINE_MSB);
	dump_reg(sd, REG_VBLK_STOP_LINE_LSB);
	dump_reg(sd, REG_VBLK_STOP_LINE_MSB);
	dump_reg(sd, REG_SYNC_CONTROL);
	dump_reg(sd, REG_OUTPUT_FORMATTER1);
	dump_reg(sd, REG_OUTPUT_FORMATTER2);
	dump_reg(sd, REG_OUTPUT_FORMATTER3);
	dump_reg(sd, REG_OUTPUT_FORMATTER4);
	dump_reg(sd, REG_OUTPUT_FORMATTER5);
	dump_reg(sd, REG_OUTPUT_FORMATTER6);
	dump_reg(sd, REG_CLEAR_LOST_LOCK);
पूर्ण

/**
 * tvp514x_configure() - Configure the TVP5146/47 रेजिस्टरs
 * @sd: ptr to v4l2_subdev काष्ठा
 * @decoder: ptr to tvp514x_decoder काष्ठाure
 *
 * Returns zero अगर successful, or non-zero otherwise.
 */
अटल पूर्णांक tvp514x_configure(काष्ठा v4l2_subdev *sd,
		काष्ठा tvp514x_decoder *decoder)
अणु
	पूर्णांक err;

	/* common रेजिस्टर initialization */
	err =
	    tvp514x_ग_लिखो_regs(sd, decoder->tvp514x_regs);
	अगर (err)
		वापस err;

	अगर (debug)
		tvp514x_reg_dump(sd);

	वापस 0;
पूर्ण

/**
 * tvp514x_detect() - Detect अगर an tvp514x is present, and अगर so which revision.
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @decoder: poपूर्णांकer to tvp514x_decoder काष्ठाure
 *
 * A device is considered to be detected अगर the chip ID (LSB and MSB)
 * रेजिस्टरs match the expected values.
 * Any value of the rom version रेजिस्टर is accepted.
 * Returns ENODEV error number अगर no device is detected, or zero
 * अगर a device is detected.
 */
अटल पूर्णांक tvp514x_detect(काष्ठा v4l2_subdev *sd,
		काष्ठा tvp514x_decoder *decoder)
अणु
	u8 chip_id_msb, chip_id_lsb, rom_ver;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	chip_id_msb = tvp514x_पढ़ो_reg(sd, REG_CHIP_ID_MSB);
	chip_id_lsb = tvp514x_पढ़ो_reg(sd, REG_CHIP_ID_LSB);
	rom_ver = tvp514x_पढ़ो_reg(sd, REG_ROM_VERSION);

	v4l2_dbg(1, debug, sd,
		 "chip id detected msb:0x%x lsb:0x%x rom version:0x%x\n",
		 chip_id_msb, chip_id_lsb, rom_ver);
	अगर ((chip_id_msb != TVP514X_CHIP_ID_MSB)
		|| ((chip_id_lsb != TVP5146_CHIP_ID_LSB)
		&& (chip_id_lsb != TVP5147_CHIP_ID_LSB))) अणु
		/* We didn't पढ़ो the values we expected, so this must not be
		 * an TVP5146/47.
		 */
		v4l2_err(sd, "chip id mismatch msb:0x%x lsb:0x%x\n",
				chip_id_msb, chip_id_lsb);
		वापस -ENODEV;
	पूर्ण

	decoder->ver = rom_ver;

	v4l2_info(sd, "%s (Version - 0x%.2x) found at 0x%x (%s)\n",
			client->name, decoder->ver,
			client->addr << 1, client->adapter->name);
	वापस 0;
पूर्ण

/**
 * tvp514x_querystd() - V4L2 decoder पूर्णांकerface handler क्रम querystd
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @std_id: standard V4L2 std_id ioctl क्रमागत
 *
 * Returns the current standard detected by TVP5146/47. If no active input is
 * detected then *std_id is set to 0 and the function वापसs 0.
 */
अटल पूर्णांक tvp514x_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std_id)
अणु
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);
	क्रमागत tvp514x_std current_std;
	क्रमागत tvp514x_input input_sel;
	u8 sync_lock_status, lock_mask;

	अगर (std_id == शून्य)
		वापस -EINVAL;

	/* To query the standard the TVP514x must घातer on the ADCs. */
	अगर (!decoder->streaming) अणु
		tvp514x_s_stream(sd, 1);
		msleep(LOCK_RETRY_DELAY);
	पूर्ण

	/* query the current standard */
	current_std = tvp514x_query_current_std(sd);
	अगर (current_std == STD_INVALID) अणु
		*std_id = V4L2_STD_UNKNOWN;
		वापस 0;
	पूर्ण

	input_sel = decoder->input;

	चयन (input_sel) अणु
	हाल INPUT_CVBS_VI1A:
	हाल INPUT_CVBS_VI1B:
	हाल INPUT_CVBS_VI1C:
	हाल INPUT_CVBS_VI2A:
	हाल INPUT_CVBS_VI2B:
	हाल INPUT_CVBS_VI2C:
	हाल INPUT_CVBS_VI3A:
	हाल INPUT_CVBS_VI3B:
	हाल INPUT_CVBS_VI3C:
	हाल INPUT_CVBS_VI4A:
		lock_mask = STATUS_CLR_SUBCAR_LOCK_BIT |
			STATUS_HORZ_SYNC_LOCK_BIT |
			STATUS_VIRT_SYNC_LOCK_BIT;
		अवरोध;

	हाल INPUT_SVIDEO_VI2A_VI1A:
	हाल INPUT_SVIDEO_VI2B_VI1B:
	हाल INPUT_SVIDEO_VI2C_VI1C:
	हाल INPUT_SVIDEO_VI2A_VI3A:
	हाल INPUT_SVIDEO_VI2B_VI3B:
	हाल INPUT_SVIDEO_VI2C_VI3C:
	हाल INPUT_SVIDEO_VI4A_VI1A:
	हाल INPUT_SVIDEO_VI4A_VI1B:
	हाल INPUT_SVIDEO_VI4A_VI1C:
	हाल INPUT_SVIDEO_VI4A_VI3A:
	हाल INPUT_SVIDEO_VI4A_VI3B:
	हाल INPUT_SVIDEO_VI4A_VI3C:
		lock_mask = STATUS_HORZ_SYNC_LOCK_BIT |
			STATUS_VIRT_SYNC_LOCK_BIT;
		अवरोध;
		/*Need to add other पूर्णांकerfaces*/
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* check whether संकेत is locked */
	sync_lock_status = tvp514x_पढ़ो_reg(sd, REG_STATUS1);
	अगर (lock_mask != (sync_lock_status & lock_mask)) अणु
		*std_id = V4L2_STD_UNKNOWN;
		वापस 0;	/* No input detected */
	पूर्ण

	*std_id &= decoder->std_list[current_std].standard.id;

	v4l2_dbg(1, debug, sd, "Current STD: %s\n",
			decoder->std_list[current_std].standard.name);
	वापस 0;
पूर्ण

/**
 * tvp514x_s_std() - V4L2 decoder पूर्णांकerface handler क्रम s_std
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @std_id: standard V4L2 v4l2_std_id ioctl क्रमागत
 *
 * If std_id is supported, sets the requested standard. Otherwise, वापसs
 * -EINVAL
 */
अटल पूर्णांक tvp514x_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std_id)
अणु
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);
	पूर्णांक err, i;

	क्रम (i = 0; i < decoder->num_stds; i++)
		अगर (std_id & decoder->std_list[i].standard.id)
			अवरोध;

	अगर ((i == decoder->num_stds) || (i == STD_INVALID))
		वापस -EINVAL;

	err = tvp514x_ग_लिखो_reg(sd, REG_VIDEO_STD,
				decoder->std_list[i].video_std);
	अगर (err)
		वापस err;

	decoder->current_std = i;
	decoder->tvp514x_regs[REG_VIDEO_STD].val =
		decoder->std_list[i].video_std;

	v4l2_dbg(1, debug, sd, "Standard set to: %s\n",
			decoder->std_list[i].standard.name);
	वापस 0;
पूर्ण

/**
 * tvp514x_s_routing() - V4L2 decoder पूर्णांकerface handler क्रम s_routing
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @input: input selector क्रम routing the संकेत
 * @output: output selector क्रम routing the संकेत
 * @config: config value. Not used
 *
 * If index is valid, selects the requested input. Otherwise, वापसs -EINVAL अगर
 * the input is not supported or there is no active संकेत present in the
 * selected input.
 */
अटल पूर्णांक tvp514x_s_routing(काष्ठा v4l2_subdev *sd,
				u32 input, u32 output, u32 config)
अणु
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);
	पूर्णांक err;
	क्रमागत tvp514x_input input_sel;
	क्रमागत tvp514x_output output_sel;

	अगर ((input >= INPUT_INVALID) ||
			(output >= OUTPUT_INVALID))
		/* Index out of bound */
		वापस -EINVAL;

	input_sel = input;
	output_sel = output;

	err = tvp514x_ग_लिखो_reg(sd, REG_INPUT_SEL, input_sel);
	अगर (err)
		वापस err;

	output_sel |= tvp514x_पढ़ो_reg(sd,
			REG_OUTPUT_FORMATTER1) & 0x7;
	err = tvp514x_ग_लिखो_reg(sd, REG_OUTPUT_FORMATTER1,
			output_sel);
	अगर (err)
		वापस err;

	decoder->tvp514x_regs[REG_INPUT_SEL].val = input_sel;
	decoder->tvp514x_regs[REG_OUTPUT_FORMATTER1].val = output_sel;
	decoder->input = input;
	decoder->output = output;

	v4l2_dbg(1, debug, sd, "Input set to: %d\n", input_sel);

	वापस 0;
पूर्ण

/**
 * tvp514x_s_ctrl() - V4L2 decoder पूर्णांकerface handler क्रम s_ctrl
 * @ctrl: poपूर्णांकer to v4l2_ctrl काष्ठाure
 *
 * If the requested control is supported, sets the control's current
 * value in HW. Otherwise, वापसs -EINVAL अगर the control is not supported.
 */
अटल पूर्णांक tvp514x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);
	पूर्णांक err = -EINVAL, value;

	value = ctrl->val;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		err = tvp514x_ग_लिखो_reg(sd, REG_BRIGHTNESS, value);
		अगर (!err)
			decoder->tvp514x_regs[REG_BRIGHTNESS].val = value;
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		err = tvp514x_ग_लिखो_reg(sd, REG_CONTRAST, value);
		अगर (!err)
			decoder->tvp514x_regs[REG_CONTRAST].val = value;
		अवरोध;
	हाल V4L2_CID_SATURATION:
		err = tvp514x_ग_लिखो_reg(sd, REG_SATURATION, value);
		अगर (!err)
			decoder->tvp514x_regs[REG_SATURATION].val = value;
		अवरोध;
	हाल V4L2_CID_HUE:
		अगर (value == 180)
			value = 0x7F;
		अन्यथा अगर (value == -180)
			value = 0x80;
		err = tvp514x_ग_लिखो_reg(sd, REG_HUE, value);
		अगर (!err)
			decoder->tvp514x_regs[REG_HUE].val = value;
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		err = tvp514x_ग_लिखो_reg(sd, REG_AFE_GAIN_CTRL, value ? 0x0f : 0x0c);
		अगर (!err)
			decoder->tvp514x_regs[REG_AFE_GAIN_CTRL].val = value;
		अवरोध;
	पूर्ण

	v4l2_dbg(1, debug, sd, "Set Control: ID - %d - %d\n",
			ctrl->id, ctrl->val);
	वापस err;
पूर्ण

/**
 * tvp514x_g_frame_पूर्णांकerval() - V4L2 decoder पूर्णांकerface handler
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @ival: poपूर्णांकer to a v4l2_subdev_frame_पूर्णांकerval काष्ठाure
 *
 * Returns the decoder's video CAPTURE parameters.
 */
अटल पूर्णांक
tvp514x_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);
	क्रमागत tvp514x_std current_std;


	/* get the current standard */
	current_std = decoder->current_std;

	ival->पूर्णांकerval =
		decoder->std_list[current_std].standard.frameperiod;

	वापस 0;
पूर्ण

/**
 * tvp514x_s_frame_पूर्णांकerval() - V4L2 decoder पूर्णांकerface handler
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @ival: poपूर्णांकer to a v4l2_subdev_frame_पूर्णांकerval काष्ठाure
 *
 * Configures the decoder to use the input parameters, अगर possible. If
 * not possible, वापसs the appropriate error code.
 */
अटल पूर्णांक
tvp514x_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);
	काष्ठा v4l2_fract *समयperframe;
	क्रमागत tvp514x_std current_std;


	समयperframe = &ival->पूर्णांकerval;

	/* get the current standard */
	current_std = decoder->current_std;

	*समयperframe =
	    decoder->std_list[current_std].standard.frameperiod;

	वापस 0;
पूर्ण

/**
 * tvp514x_s_stream() - V4L2 decoder i/f handler क्रम s_stream
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @enable: streaming enable or disable
 *
 * Sets streaming to enable or disable, अगर possible.
 */
अटल पूर्णांक tvp514x_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	पूर्णांक err = 0;
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);

	अगर (decoder->streaming == enable)
		वापस 0;

	चयन (enable) अणु
	हाल 0:
	अणु
		/* Power Down Sequence */
		err = tvp514x_ग_लिखो_reg(sd, REG_OPERATION_MODE, 0x01);
		अगर (err) अणु
			v4l2_err(sd, "Unable to turn off decoder\n");
			वापस err;
		पूर्ण
		decoder->streaming = enable;
		अवरोध;
	पूर्ण
	हाल 1:
	अणु
		/* Power Up Sequence */
		err = tvp514x_ग_लिखो_regs(sd, decoder->पूर्णांक_seq);
		अगर (err) अणु
			v4l2_err(sd, "Unable to turn on decoder\n");
			वापस err;
		पूर्ण
		/* Detect अगर not alपढ़ोy detected */
		err = tvp514x_detect(sd, decoder);
		अगर (err) अणु
			v4l2_err(sd, "Unable to detect decoder\n");
			वापस err;
		पूर्ण
		err = tvp514x_configure(sd, decoder);
		अगर (err) अणु
			v4l2_err(sd, "Unable to configure decoder\n");
			वापस err;
		पूर्ण
		decoder->streaming = enable;
		अवरोध;
	पूर्ण
	शेष:
		err = -ENODEV;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops tvp514x_ctrl_ops = अणु
	.s_ctrl = tvp514x_s_ctrl,
पूर्ण;

/**
 * tvp514x_क्रमागत_mbus_code() - V4L2 decoder पूर्णांकerface handler क्रम क्रमागत_mbus_code
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @cfg: pad configuration
 * @code: poपूर्णांकer to v4l2_subdev_mbus_code_क्रमागत काष्ठाure
 *
 * Enumertaes mbus codes supported
 */
अटल पूर्णांक tvp514x_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	u32 pad = code->pad;
	u32 index = code->index;

	स_रखो(code, 0, माप(*code));
	code->index = index;
	code->pad = pad;

	अगर (index != 0)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_UYVY8_2X8;

	वापस 0;
पूर्ण

/**
 * tvp514x_get_pad_क्रमmat() - V4L2 decoder पूर्णांकerface handler क्रम get pad क्रमmat
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @cfg: pad configuration
 * @क्रमmat: poपूर्णांकer to v4l2_subdev_क्रमmat काष्ठाure
 *
 * Retrieves pad क्रमmat which is active or tried based on requirement
 */
अटल पूर्णांक tvp514x_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);
	__u32 which = क्रमmat->which;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		क्रमmat->क्रमmat = decoder->क्रमmat;
		वापस 0;
	पूर्ण

	क्रमmat->क्रमmat.code = MEDIA_BUS_FMT_UYVY8_2X8;
	क्रमmat->क्रमmat.width = tvp514x_std_list[decoder->current_std].width;
	क्रमmat->क्रमmat.height = tvp514x_std_list[decoder->current_std].height;
	क्रमmat->क्रमmat.colorspace = V4L2_COLORSPACE_SMPTE170M;
	क्रमmat->क्रमmat.field = V4L2_FIELD_INTERLACED;

	वापस 0;
पूर्ण

/**
 * tvp514x_set_pad_क्रमmat() - V4L2 decoder पूर्णांकerface handler क्रम set pad क्रमmat
 * @sd: poपूर्णांकer to standard V4L2 sub-device काष्ठाure
 * @cfg: pad configuration
 * @fmt: poपूर्णांकer to v4l2_subdev_क्रमmat काष्ठाure
 *
 * Set pad क्रमmat क्रम the output pad
 */
अटल पूर्णांक tvp514x_set_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);

	अगर (fmt->क्रमmat.field != V4L2_FIELD_INTERLACED ||
	    fmt->क्रमmat.code != MEDIA_BUS_FMT_UYVY8_2X8 ||
	    fmt->क्रमmat.colorspace != V4L2_COLORSPACE_SMPTE170M ||
	    fmt->क्रमmat.width != tvp514x_std_list[decoder->current_std].width ||
	    fmt->क्रमmat.height != tvp514x_std_list[decoder->current_std].height)
		वापस -EINVAL;

	decoder->क्रमmat = fmt->क्रमmat;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops tvp514x_video_ops = अणु
	.s_std = tvp514x_s_std,
	.s_routing = tvp514x_s_routing,
	.querystd = tvp514x_querystd,
	.g_frame_पूर्णांकerval = tvp514x_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = tvp514x_s_frame_पूर्णांकerval,
	.s_stream = tvp514x_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops tvp514x_pad_ops = अणु
	.क्रमागत_mbus_code = tvp514x_क्रमागत_mbus_code,
	.get_fmt = tvp514x_get_pad_क्रमmat,
	.set_fmt = tvp514x_set_pad_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tvp514x_ops = अणु
	.video = &tvp514x_video_ops,
	.pad = &tvp514x_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा tvp514x_decoder tvp514x_dev = अणु
	.streaming = 0,
	.fmt_list = tvp514x_fmt_list,
	.num_fmts = ARRAY_SIZE(tvp514x_fmt_list),
	.pix = अणु
		/* Default to NTSC 8-bit YUV 422 */
		.width		= NTSC_NUM_ACTIVE_PIXELS,
		.height		= NTSC_NUM_ACTIVE_LINES,
		.pixelक्रमmat	= V4L2_PIX_FMT_UYVY,
		.field		= V4L2_FIELD_INTERLACED,
		.bytesperline	= NTSC_NUM_ACTIVE_PIXELS * 2,
		.sizeimage	= NTSC_NUM_ACTIVE_PIXELS * 2 *
					NTSC_NUM_ACTIVE_LINES,
		.colorspace	= V4L2_COLORSPACE_SMPTE170M,
		पूर्ण,
	.current_std = STD_NTSC_MJ,
	.std_list = tvp514x_std_list,
	.num_stds = ARRAY_SIZE(tvp514x_std_list),

पूर्ण;

अटल काष्ठा tvp514x_platक्रमm_data *
tvp514x_get_pdata(काष्ठा i2c_client *client)
अणु
	काष्ठा tvp514x_platक्रमm_data *pdata = शून्य;
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु .bus_type = 0 पूर्ण;
	काष्ठा device_node *endpoपूर्णांक;
	अचिन्हित पूर्णांक flags;

	अगर (!IS_ENABLED(CONFIG_OF) || !client->dev.of_node)
		वापस client->dev.platक्रमm_data;

	endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(client->dev.of_node, शून्य);
	अगर (!endpoपूर्णांक)
		वापस शून्य;

	अगर (v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(endpoपूर्णांक), &bus_cfg))
		जाओ करोne;

	pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		जाओ करोne;

	flags = bus_cfg.bus.parallel.flags;

	अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		pdata->hs_polarity = 1;

	अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		pdata->vs_polarity = 1;

	अगर (flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		pdata->clk_polarity = 1;

करोne:
	of_node_put(endpoपूर्णांक);
	वापस pdata;
पूर्ण

/**
 * tvp514x_probe() - decoder driver i2c probe handler
 * @client: i2c driver client device काष्ठाure
 * @id: i2c driver id table
 *
 * Register decoder as an i2c client device and V4L2
 * device.
 */
अटल पूर्णांक
tvp514x_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tvp514x_platक्रमm_data *pdata = tvp514x_get_pdata(client);
	काष्ठा tvp514x_decoder *decoder;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	decoder = devm_kzalloc(&client->dev, माप(*decoder), GFP_KERNEL);
	अगर (!decoder)
		वापस -ENOMEM;

	/* Initialize the tvp514x_decoder with शेष configuration */
	*decoder = tvp514x_dev;
	/* Copy शेष रेजिस्टर configuration */
	स_नकल(decoder->tvp514x_regs, tvp514x_reg_list_शेष,
			माप(tvp514x_reg_list_शेष));

	decoder->पूर्णांक_seq = (काष्ठा tvp514x_reg *)id->driver_data;

	/* Copy board specअगरic inक्रमmation here */
	decoder->pdata = pdata;

	/**
	 * Fetch platक्रमm specअगरic data, and configure the
	 * tvp514x_reg_list[] accordingly. Since this is one
	 * समय configuration, no need to preserve.
	 */
	decoder->tvp514x_regs[REG_OUTPUT_FORMATTER2].val |=
		(decoder->pdata->clk_polarity << 1);
	decoder->tvp514x_regs[REG_SYNC_CONTROL].val |=
		((decoder->pdata->hs_polarity << 2) |
		 (decoder->pdata->vs_polarity << 3));
	/* Set शेष standard to स्वतः */
	decoder->tvp514x_regs[REG_VIDEO_STD].val =
		VIDEO_STD_AUTO_SWITCH_BIT;

	/* Register with V4L2 layer as slave device */
	sd = &decoder->sd;
	v4l2_i2c_subdev_init(sd, client, &tvp514x_ops);

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	decoder->pad.flags = MEDIA_PAD_FL_SOURCE;
	decoder->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	decoder->sd.entity.function = MEDIA_ENT_F_ATV_DECODER;

	ret = media_entity_pads_init(&decoder->sd.entity, 1, &decoder->pad);
	अगर (ret < 0) अणु
		v4l2_err(sd, "%s decoder driver failed to register !!\n",
			 sd->name);
		वापस ret;
	पूर्ण
#पूर्ण_अगर
	v4l2_ctrl_handler_init(&decoder->hdl, 5);
	v4l2_ctrl_new_std(&decoder->hdl, &tvp514x_ctrl_ops,
		V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&decoder->hdl, &tvp514x_ctrl_ops,
		V4L2_CID_CONTRAST, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&decoder->hdl, &tvp514x_ctrl_ops,
		V4L2_CID_SATURATION, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&decoder->hdl, &tvp514x_ctrl_ops,
		V4L2_CID_HUE, -180, 180, 180, 0);
	v4l2_ctrl_new_std(&decoder->hdl, &tvp514x_ctrl_ops,
		V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	sd->ctrl_handler = &decoder->hdl;
	अगर (decoder->hdl.error) अणु
		ret = decoder->hdl.error;
		जाओ करोne;
	पूर्ण
	v4l2_ctrl_handler_setup(&decoder->hdl);

	ret = v4l2_async_रेजिस्टर_subdev(&decoder->sd);
	अगर (!ret)
		v4l2_info(sd, "%s decoder driver registered !!\n", sd->name);

करोne:
	अगर (ret < 0) अणु
		v4l2_ctrl_handler_मुक्त(&decoder->hdl);
		media_entity_cleanup(&decoder->sd.entity);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * tvp514x_हटाओ() - decoder driver i2c हटाओ handler
 * @client: i2c driver client device काष्ठाure
 *
 * Unरेजिस्टर decoder as an i2c client device and V4L2
 * device. Complement of tvp514x_probe().
 */
अटल पूर्णांक tvp514x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा tvp514x_decoder *decoder = to_decoder(sd);

	v4l2_async_unरेजिस्टर_subdev(&decoder->sd);
	media_entity_cleanup(&decoder->sd.entity);
	v4l2_ctrl_handler_मुक्त(&decoder->hdl);
	वापस 0;
पूर्ण
/* TVP5146 Init/Power on Sequence */
अटल स्थिर काष्ठा tvp514x_reg tvp5146_init_reg_seq[] = अणु
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS1, 0x02पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS2, 0x00पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS3, 0x80पूर्ण,
	अणुTOK_WRITE, REG_VBUS_DATA_ACCESS_NO_VBUS_ADDR_INCR, 0x01पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS1, 0x60पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS2, 0x00पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS3, 0xB0पूर्ण,
	अणुTOK_WRITE, REG_VBUS_DATA_ACCESS_NO_VBUS_ADDR_INCR, 0x01पूर्ण,
	अणुTOK_WRITE, REG_VBUS_DATA_ACCESS_NO_VBUS_ADDR_INCR, 0x00पूर्ण,
	अणुTOK_WRITE, REG_OPERATION_MODE, 0x01पूर्ण,
	अणुTOK_WRITE, REG_OPERATION_MODE, 0x00पूर्ण,
	अणुTOK_TERM, 0, 0पूर्ण,
पूर्ण;

/* TVP5147 Init/Power on Sequence */
अटल स्थिर काष्ठा tvp514x_reg tvp5147_init_reg_seq[] =	अणु
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS1, 0x02पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS2, 0x00पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS3, 0x80पूर्ण,
	अणुTOK_WRITE, REG_VBUS_DATA_ACCESS_NO_VBUS_ADDR_INCR, 0x01पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS1, 0x60पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS2, 0x00पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS3, 0xB0पूर्ण,
	अणुTOK_WRITE, REG_VBUS_DATA_ACCESS_NO_VBUS_ADDR_INCR, 0x01पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS1, 0x16पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS2, 0x00पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS3, 0xA0पूर्ण,
	अणुTOK_WRITE, REG_VBUS_DATA_ACCESS_NO_VBUS_ADDR_INCR, 0x16पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS1, 0x60पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS2, 0x00पूर्ण,
	अणुTOK_WRITE, REG_VBUS_ADDRESS_ACCESS3, 0xB0पूर्ण,
	अणुTOK_WRITE, REG_VBUS_DATA_ACCESS_NO_VBUS_ADDR_INCR, 0x00पूर्ण,
	अणुTOK_WRITE, REG_OPERATION_MODE, 0x01पूर्ण,
	अणुTOK_WRITE, REG_OPERATION_MODE, 0x00पूर्ण,
	अणुTOK_TERM, 0, 0पूर्ण,
पूर्ण;

/* TVP5146M2/TVP5147M1 Init/Power on Sequence */
अटल स्थिर काष्ठा tvp514x_reg tvp514xm_init_reg_seq[] = अणु
	अणुTOK_WRITE, REG_OPERATION_MODE, 0x01पूर्ण,
	अणुTOK_WRITE, REG_OPERATION_MODE, 0x00पूर्ण,
	अणुTOK_TERM, 0, 0पूर्ण,
पूर्ण;

/*
 * I2C Device Table -
 *
 * name - Name of the actual device/chip.
 * driver_data - Driver data
 */
अटल स्थिर काष्ठा i2c_device_id tvp514x_id[] = अणु
	अणु"tvp5146", (अचिन्हित दीर्घ)tvp5146_init_reg_seqपूर्ण,
	अणु"tvp5146m2", (अचिन्हित दीर्घ)tvp514xm_init_reg_seqपूर्ण,
	अणु"tvp5147", (अचिन्हित दीर्घ)tvp5147_init_reg_seqपूर्ण,
	अणु"tvp5147m1", (अचिन्हित दीर्घ)tvp514xm_init_reg_seqपूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tvp514x_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id tvp514x_of_match[] = अणु
	अणु .compatible = "ti,tvp5146", पूर्ण,
	अणु .compatible = "ti,tvp5146m2", पूर्ण,
	अणु .compatible = "ti,tvp5147", पूर्ण,
	अणु .compatible = "ti,tvp5147m1", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tvp514x_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tvp514x_driver = अणु
	.driver = अणु
		.of_match_table = of_match_ptr(tvp514x_of_match),
		.name = TVP514X_MODULE_NAME,
	पूर्ण,
	.probe = tvp514x_probe,
	.हटाओ = tvp514x_हटाओ,
	.id_table = tvp514x_id,
पूर्ण;

module_i2c_driver(tvp514x_driver);
