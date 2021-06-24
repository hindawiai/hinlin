<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * saa7127 - Philips SAA7127/SAA7129 video encoder driver
 *
 * Copyright (C) 2003 Roy Bulter <rbulter@hetnet.nl>
 *
 * Based on SAA7126 video encoder driver by Gillem & Andreas Oberritter
 *
 * Copyright (C) 2000-2001 Gillem <htoa@gmx.net>
 * Copyright (C) 2002 Andreas Oberritter <obi@saftware.de>
 *
 * Based on Stadis 4:2:2 MPEG-2 Decoder Driver by Nathan Lareकरो
 *
 * Copyright (C) 1999 Nathan Lareकरो <lareकरो@gnu.org>
 *
 * This driver is deचिन्हित क्रम the Hauppauge 250/350 Linux driver
 * from the ivtv Project
 *
 * Copyright (C) 2003 Kevin Thayer <nufan_wfk@yahoo.com>
 *
 * Dual output support:
 * Copyright (C) 2004 Eric Varsanyi
 *
 * NTSC Tuning and 7.5 IRE Setup
 * Copyright (C) 2004  Chris Kennedy <c@groovy.org>
 *
 * VBI additions & cleanup:
 * Copyright (C) 2004, 2005 Hans Verkuil <hverkuil@xs4all.nl>
 *
 * Note: the saa7126 is identical to the saa7127, and the saa7128 is
 * identical to the saa7129, except that the saa7126 and saa7128 have
 * macrovision anti-taping support. This driver will almost certainly
 * work fine क्रम those chips, except of course क्रम the missing anti-taping
 * support.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/i2c/saa7127.h>

अटल पूर्णांक debug;
अटल पूर्णांक test_image;

MODULE_DESCRIPTION("Philips SAA7127/9 video encoder driver");
MODULE_AUTHOR("Kevin Thayer, Chris Kennedy, Hans Verkuil");
MODULE_LICENSE("GPL");
module_param(debug, पूर्णांक, 0644);
module_param(test_image, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");
MODULE_PARM_DESC(test_image, "test_image (0-1)");


/*
 * SAA7127 रेजिस्टरs
 */

#घोषणा SAA7127_REG_STATUS                           0x00
#घोषणा SAA7127_REG_WIDESCREEN_CONFIG                0x26
#घोषणा SAA7127_REG_WIDESCREEN_ENABLE                0x27
#घोषणा SAA7127_REG_BURST_START                      0x28
#घोषणा SAA7127_REG_BURST_END                        0x29
#घोषणा SAA7127_REG_COPYGEN_0                        0x2a
#घोषणा SAA7127_REG_COPYGEN_1                        0x2b
#घोषणा SAA7127_REG_COPYGEN_2                        0x2c
#घोषणा SAA7127_REG_OUTPUT_PORT_CONTROL              0x2d
#घोषणा SAA7127_REG_GAIN_LUMIन_अंकCE_RGB               0x38
#घोषणा SAA7127_REG_GAIN_COLORDIFF_RGB               0x39
#घोषणा SAA7127_REG_INPUT_PORT_CONTROL_1             0x3a
#घोषणा SAA7129_REG_FADE_KEY_COL2		     0x4f
#घोषणा SAA7127_REG_CHROMA_PHASE                     0x5a
#घोषणा SAA7127_REG_GAINU                            0x5b
#घोषणा SAA7127_REG_GAINV                            0x5c
#घोषणा SAA7127_REG_BLACK_LEVEL                      0x5d
#घोषणा SAA7127_REG_BLANKING_LEVEL                   0x5e
#घोषणा SAA7127_REG_VBI_BLANKING                     0x5f
#घोषणा SAA7127_REG_DAC_CONTROL                      0x61
#घोषणा SAA7127_REG_BURST_AMP                        0x62
#घोषणा SAA7127_REG_SUBC3                            0x63
#घोषणा SAA7127_REG_SUBC2                            0x64
#घोषणा SAA7127_REG_SUBC1                            0x65
#घोषणा SAA7127_REG_SUBC0                            0x66
#घोषणा SAA7127_REG_LINE_21_ODD_0                    0x67
#घोषणा SAA7127_REG_LINE_21_ODD_1                    0x68
#घोषणा SAA7127_REG_LINE_21_EVEN_0                   0x69
#घोषणा SAA7127_REG_LINE_21_EVEN_1                   0x6a
#घोषणा SAA7127_REG_RCV_PORT_CONTROL                 0x6b
#घोषणा SAA7127_REG_VTRIG                            0x6c
#घोषणा SAA7127_REG_HTRIG_HI                         0x6d
#घोषणा SAA7127_REG_MULTI                            0x6e
#घोषणा SAA7127_REG_CLOSED_CAPTION                   0x6f
#घोषणा SAA7127_REG_RCV2_OUTPUT_START                0x70
#घोषणा SAA7127_REG_RCV2_OUTPUT_END                  0x71
#घोषणा SAA7127_REG_RCV2_OUTPUT_MSBS                 0x72
#घोषणा SAA7127_REG_TTX_REQUEST_H_START              0x73
#घोषणा SAA7127_REG_TTX_REQUEST_H_DELAY_LENGTH       0x74
#घोषणा SAA7127_REG_CSYNC_ADVANCE_VSYNC_SHIFT        0x75
#घोषणा SAA7127_REG_TTX_ODD_REQ_VERT_START           0x76
#घोषणा SAA7127_REG_TTX_ODD_REQ_VERT_END             0x77
#घोषणा SAA7127_REG_TTX_EVEN_REQ_VERT_START          0x78
#घोषणा SAA7127_REG_TTX_EVEN_REQ_VERT_END            0x79
#घोषणा SAA7127_REG_FIRST_ACTIVE                     0x7a
#घोषणा SAA7127_REG_LAST_ACTIVE                      0x7b
#घोषणा SAA7127_REG_MSB_VERTICAL                     0x7c
#घोषणा SAA7127_REG_DISABLE_TTX_LINE_LO_0            0x7e
#घोषणा SAA7127_REG_DISABLE_TTX_LINE_LO_1            0x7f

/*
 **********************************************************************
 *
 *  Arrays with configuration parameters क्रम the SAA7127
 *
 **********************************************************************
 */

काष्ठा i2c_reg_value अणु
	अचिन्हित अक्षर reg;
	अचिन्हित अक्षर value;
पूर्ण;

अटल स्थिर काष्ठा i2c_reg_value saa7129_init_config_extra[] = अणु
	अणु SAA7127_REG_OUTPUT_PORT_CONTROL,		0x38 पूर्ण,
	अणु SAA7127_REG_VTRIG,				0xfa पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा i2c_reg_value saa7127_init_config_common[] = अणु
	अणु SAA7127_REG_WIDESCREEN_CONFIG,		0x0d पूर्ण,
	अणु SAA7127_REG_WIDESCREEN_ENABLE,		0x00 पूर्ण,
	अणु SAA7127_REG_COPYGEN_0,			0x77 पूर्ण,
	अणु SAA7127_REG_COPYGEN_1,			0x41 पूर्ण,
	अणु SAA7127_REG_COPYGEN_2,			0x00 पूर्ण,	/* Macrovision enable/disable */
	अणु SAA7127_REG_OUTPUT_PORT_CONTROL,		0xbf पूर्ण,
	अणु SAA7127_REG_GAIN_LUMIन_अंकCE_RGB,		0x00 पूर्ण,
	अणु SAA7127_REG_GAIN_COLORDIFF_RGB,		0x00 पूर्ण,
	अणु SAA7127_REG_INPUT_PORT_CONTROL_1,		0x80 पूर्ण,	/* क्रम color bars */
	अणु SAA7127_REG_LINE_21_ODD_0,			0x77 पूर्ण,
	अणु SAA7127_REG_LINE_21_ODD_1,			0x41 पूर्ण,
	अणु SAA7127_REG_LINE_21_EVEN_0,			0x88 पूर्ण,
	अणु SAA7127_REG_LINE_21_EVEN_1,			0x41 पूर्ण,
	अणु SAA7127_REG_RCV_PORT_CONTROL,			0x12 पूर्ण,
	अणु SAA7127_REG_VTRIG,				0xf9 पूर्ण,
	अणु SAA7127_REG_HTRIG_HI,				0x00 पूर्ण,
	अणु SAA7127_REG_RCV2_OUTPUT_START,		0x41 पूर्ण,
	अणु SAA7127_REG_RCV2_OUTPUT_END,			0xc3 पूर्ण,
	अणु SAA7127_REG_RCV2_OUTPUT_MSBS,			0x00 पूर्ण,
	अणु SAA7127_REG_TTX_REQUEST_H_START,		0x3e पूर्ण,
	अणु SAA7127_REG_TTX_REQUEST_H_DELAY_LENGTH,	0xb8 पूर्ण,
	अणु SAA7127_REG_CSYNC_ADVANCE_VSYNC_SHIFT,	0x03 पूर्ण,
	अणु SAA7127_REG_TTX_ODD_REQ_VERT_START,		0x15 पूर्ण,
	अणु SAA7127_REG_TTX_ODD_REQ_VERT_END,		0x16 पूर्ण,
	अणु SAA7127_REG_TTX_EVEN_REQ_VERT_START,		0x15 पूर्ण,
	अणु SAA7127_REG_TTX_EVEN_REQ_VERT_END,		0x16 पूर्ण,
	अणु SAA7127_REG_FIRST_ACTIVE,			0x1a पूर्ण,
	अणु SAA7127_REG_LAST_ACTIVE,			0x01 पूर्ण,
	अणु SAA7127_REG_MSB_VERTICAL,			0xc0 पूर्ण,
	अणु SAA7127_REG_DISABLE_TTX_LINE_LO_0,		0x00 पूर्ण,
	अणु SAA7127_REG_DISABLE_TTX_LINE_LO_1,		0x00 पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

#घोषणा SAA7127_60HZ_DAC_CONTROL 0x15
अटल स्थिर काष्ठा i2c_reg_value saa7127_init_config_60hz[] = अणु
	अणु SAA7127_REG_BURST_START,			0x19 पूर्ण,
	/* BURST_END is also used as a chip ID in saa7127_probe */
	अणु SAA7127_REG_BURST_END,			0x1d पूर्ण,
	अणु SAA7127_REG_CHROMA_PHASE,			0xa3 पूर्ण,
	अणु SAA7127_REG_GAINU,				0x98 पूर्ण,
	अणु SAA7127_REG_GAINV,				0xd3 पूर्ण,
	अणु SAA7127_REG_BLACK_LEVEL,			0x39 पूर्ण,
	अणु SAA7127_REG_BLANKING_LEVEL,			0x2e पूर्ण,
	अणु SAA7127_REG_VBI_BLANKING,			0x2e पूर्ण,
	अणु SAA7127_REG_DAC_CONTROL,			0x15 पूर्ण,
	अणु SAA7127_REG_BURST_AMP,			0x4d पूर्ण,
	अणु SAA7127_REG_SUBC3,				0x1f पूर्ण,
	अणु SAA7127_REG_SUBC2,				0x7c पूर्ण,
	अणु SAA7127_REG_SUBC1,				0xf0 पूर्ण,
	अणु SAA7127_REG_SUBC0,				0x21 पूर्ण,
	अणु SAA7127_REG_MULTI,				0x90 पूर्ण,
	अणु SAA7127_REG_CLOSED_CAPTION,			0x11 पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

#घोषणा SAA7127_50HZ_PAL_DAC_CONTROL 0x02
अटल काष्ठा i2c_reg_value saa7127_init_config_50hz_pal[] = अणु
	अणु SAA7127_REG_BURST_START,			0x21 पूर्ण,
	/* BURST_END is also used as a chip ID in saa7127_probe */
	अणु SAA7127_REG_BURST_END,			0x1d पूर्ण,
	अणु SAA7127_REG_CHROMA_PHASE,			0x3f पूर्ण,
	अणु SAA7127_REG_GAINU,				0x7d पूर्ण,
	अणु SAA7127_REG_GAINV,				0xaf पूर्ण,
	अणु SAA7127_REG_BLACK_LEVEL,			0x33 पूर्ण,
	अणु SAA7127_REG_BLANKING_LEVEL,			0x35 पूर्ण,
	अणु SAA7127_REG_VBI_BLANKING,			0x35 पूर्ण,
	अणु SAA7127_REG_DAC_CONTROL,			0x02 पूर्ण,
	अणु SAA7127_REG_BURST_AMP,			0x2f पूर्ण,
	अणु SAA7127_REG_SUBC3,				0xcb पूर्ण,
	अणु SAA7127_REG_SUBC2,				0x8a पूर्ण,
	अणु SAA7127_REG_SUBC1,				0x09 पूर्ण,
	अणु SAA7127_REG_SUBC0,				0x2a पूर्ण,
	अणु SAA7127_REG_MULTI,				0xa0 पूर्ण,
	अणु SAA7127_REG_CLOSED_CAPTION,			0x00 पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

#घोषणा SAA7127_50HZ_SECAM_DAC_CONTROL 0x08
अटल काष्ठा i2c_reg_value saa7127_init_config_50hz_secam[] = अणु
	अणु SAA7127_REG_BURST_START,			0x21 पूर्ण,
	/* BURST_END is also used as a chip ID in saa7127_probe */
	अणु SAA7127_REG_BURST_END,			0x1d पूर्ण,
	अणु SAA7127_REG_CHROMA_PHASE,			0x3f पूर्ण,
	अणु SAA7127_REG_GAINU,				0x6a पूर्ण,
	अणु SAA7127_REG_GAINV,				0x81 पूर्ण,
	अणु SAA7127_REG_BLACK_LEVEL,			0x33 पूर्ण,
	अणु SAA7127_REG_BLANKING_LEVEL,			0x35 पूर्ण,
	अणु SAA7127_REG_VBI_BLANKING,			0x35 पूर्ण,
	अणु SAA7127_REG_DAC_CONTROL,			0x08 पूर्ण,
	अणु SAA7127_REG_BURST_AMP,			0x2f पूर्ण,
	अणु SAA7127_REG_SUBC3,				0xb2 पूर्ण,
	अणु SAA7127_REG_SUBC2,				0x3b पूर्ण,
	अणु SAA7127_REG_SUBC1,				0xa3 पूर्ण,
	अणु SAA7127_REG_SUBC0,				0x28 पूर्ण,
	अणु SAA7127_REG_MULTI,				0x90 पूर्ण,
	अणु SAA7127_REG_CLOSED_CAPTION,			0x00 पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/*
 **********************************************************************
 *
 *  Encoder Struct, holds the configuration state of the encoder
 *
 **********************************************************************
 */

क्रमागत saa712x_model अणु
	SAA7127,
	SAA7129,
पूर्ण;

काष्ठा saa7127_state अणु
	काष्ठा v4l2_subdev sd;
	v4l2_std_id std;
	क्रमागत saa712x_model ident;
	क्रमागत saa7127_input_type input_type;
	क्रमागत saa7127_output_type output_type;
	पूर्णांक video_enable;
	पूर्णांक wss_enable;
	u16 wss_mode;
	पूर्णांक cc_enable;
	u16 cc_data;
	पूर्णांक xds_enable;
	u16 xds_data;
	पूर्णांक vps_enable;
	u8 vps_data[5];
	u8 reg_2d;
	u8 reg_3a;
	u8 reg_3a_cb;   /* colorbar bit */
	u8 reg_61;
पूर्ण;

अटल अंतरभूत काष्ठा saa7127_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा saa7127_state, sd);
पूर्ण

अटल स्थिर अक्षर * स्थिर output_strs[] =
अणु
	"S-Video + Composite",
	"Composite",
	"S-Video",
	"RGB",
	"YUV C",
	"YUV V"
पूर्ण;

अटल स्थिर अक्षर * स्थिर wss_strs[] = अणु
	"invalid",
	"letterbox 14:9 center",
	"letterbox 14:9 top",
	"invalid",
	"letterbox 16:9 top",
	"invalid",
	"invalid",
	"16:9 full format anamorphic",
	"4:3 full format",
	"invalid",
	"invalid",
	"letterbox 16:9 center",
	"invalid",
	"letterbox >16:9 center",
	"14:9 full format center",
	"invalid",
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक i;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (i2c_smbus_ग_लिखो_byte_data(client, reg, val) == 0)
			वापस 0;
	पूर्ण
	v4l2_err(sd, "I2C Write Problem\n");
	वापस -1;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_ग_लिखो_inittab(काष्ठा v4l2_subdev *sd,
				 स्थिर काष्ठा i2c_reg_value *regs)
अणु
	जबतक (regs->reg != 0) अणु
		saa7127_ग_लिखो(sd, regs->reg, regs->value);
		regs++;
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_set_vps(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_sliced_vbi_data *data)
अणु
	काष्ठा saa7127_state *state = to_state(sd);
	पूर्णांक enable = (data->line != 0);

	अगर (enable && (data->field != 0 || data->line != 16))
		वापस -EINVAL;
	अगर (state->vps_enable != enable) अणु
		v4l2_dbg(1, debug, sd, "Turn VPS Signal %s\n", enable ? "on" : "off");
		saa7127_ग_लिखो(sd, 0x54, enable << 7);
		state->vps_enable = enable;
	पूर्ण
	अगर (!enable)
		वापस 0;

	state->vps_data[0] = data->data[2];
	state->vps_data[1] = data->data[8];
	state->vps_data[2] = data->data[9];
	state->vps_data[3] = data->data[10];
	state->vps_data[4] = data->data[11];
	v4l2_dbg(1, debug, sd, "Set VPS data %*ph\n", 5, state->vps_data);
	saa7127_ग_लिखो(sd, 0x55, state->vps_data[0]);
	saa7127_ग_लिखो(sd, 0x56, state->vps_data[1]);
	saa7127_ग_लिखो(sd, 0x57, state->vps_data[2]);
	saa7127_ग_लिखो(sd, 0x58, state->vps_data[3]);
	saa7127_ग_लिखो(sd, 0x59, state->vps_data[4]);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_set_cc(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_sliced_vbi_data *data)
अणु
	काष्ठा saa7127_state *state = to_state(sd);
	u16 cc = data->data[1] << 8 | data->data[0];
	पूर्णांक enable = (data->line != 0);

	अगर (enable && (data->field != 0 || data->line != 21))
		वापस -EINVAL;
	अगर (state->cc_enable != enable) अणु
		v4l2_dbg(1, debug, sd,
			"Turn CC %s\n", enable ? "on" : "off");
		saa7127_ग_लिखो(sd, SAA7127_REG_CLOSED_CAPTION,
			(state->xds_enable << 7) | (enable << 6) | 0x11);
		state->cc_enable = enable;
	पूर्ण
	अगर (!enable)
		वापस 0;

	v4l2_dbg(2, debug, sd, "CC data: %04x\n", cc);
	saa7127_ग_लिखो(sd, SAA7127_REG_LINE_21_ODD_0, cc & 0xff);
	saa7127_ग_लिखो(sd, SAA7127_REG_LINE_21_ODD_1, cc >> 8);
	state->cc_data = cc;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_set_xds(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_sliced_vbi_data *data)
अणु
	काष्ठा saa7127_state *state = to_state(sd);
	u16 xds = data->data[1] << 8 | data->data[0];
	पूर्णांक enable = (data->line != 0);

	अगर (enable && (data->field != 1 || data->line != 21))
		वापस -EINVAL;
	अगर (state->xds_enable != enable) अणु
		v4l2_dbg(1, debug, sd, "Turn XDS %s\n", enable ? "on" : "off");
		saa7127_ग_लिखो(sd, SAA7127_REG_CLOSED_CAPTION,
				(enable << 7) | (state->cc_enable << 6) | 0x11);
		state->xds_enable = enable;
	पूर्ण
	अगर (!enable)
		वापस 0;

	v4l2_dbg(2, debug, sd, "XDS data: %04x\n", xds);
	saa7127_ग_लिखो(sd, SAA7127_REG_LINE_21_EVEN_0, xds & 0xff);
	saa7127_ग_लिखो(sd, SAA7127_REG_LINE_21_EVEN_1, xds >> 8);
	state->xds_data = xds;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_set_wss(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_sliced_vbi_data *data)
अणु
	काष्ठा saa7127_state *state = to_state(sd);
	पूर्णांक enable = (data->line != 0);

	अगर (enable && (data->field != 0 || data->line != 23))
		वापस -EINVAL;
	अगर (state->wss_enable != enable) अणु
		v4l2_dbg(1, debug, sd, "Turn WSS %s\n", enable ? "on" : "off");
		saa7127_ग_लिखो(sd, 0x27, enable << 7);
		state->wss_enable = enable;
	पूर्ण
	अगर (!enable)
		वापस 0;

	saa7127_ग_लिखो(sd, 0x26, data->data[0]);
	saa7127_ग_लिखो(sd, 0x27, 0x80 | (data->data[1] & 0x3f));
	v4l2_dbg(1, debug, sd,
		"WSS mode: %s\n", wss_strs[data->data[0] & 0xf]);
	state->wss_mode = (data->data[1] & 0x3f) << 8 | data->data[0];
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_set_video_enable(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा saa7127_state *state = to_state(sd);

	अगर (enable) अणु
		v4l2_dbg(1, debug, sd, "Enable Video Output\n");
		saa7127_ग_लिखो(sd, 0x2d, state->reg_2d);
		saa7127_ग_लिखो(sd, 0x61, state->reg_61);
	पूर्ण अन्यथा अणु
		v4l2_dbg(1, debug, sd, "Disable Video Output\n");
		saa7127_ग_लिखो(sd, 0x2d, (state->reg_2d & 0xf0));
		saa7127_ग_लिखो(sd, 0x61, (state->reg_61 | 0xc0));
	पूर्ण
	state->video_enable = enable;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_set_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा saa7127_state *state = to_state(sd);
	स्थिर काष्ठा i2c_reg_value *inittab;

	अगर (std & V4L2_STD_525_60) अणु
		v4l2_dbg(1, debug, sd, "Selecting 60 Hz video Standard\n");
		inittab = saa7127_init_config_60hz;
		state->reg_61 = SAA7127_60HZ_DAC_CONTROL;

	पूर्ण अन्यथा अगर (state->ident == SAA7129 &&
		   (std & V4L2_STD_SECAM) &&
		   !(std & (V4L2_STD_625_50 & ~V4L2_STD_SECAM))) अणु

		/* If and only अगर SECAM, with a SAA712[89] */
		v4l2_dbg(1, debug, sd,
			 "Selecting 50 Hz SECAM video Standard\n");
		inittab = saa7127_init_config_50hz_secam;
		state->reg_61 = SAA7127_50HZ_SECAM_DAC_CONTROL;

	पूर्ण अन्यथा अणु
		v4l2_dbg(1, debug, sd, "Selecting 50 Hz PAL video Standard\n");
		inittab = saa7127_init_config_50hz_pal;
		state->reg_61 = SAA7127_50HZ_PAL_DAC_CONTROL;
	पूर्ण

	/* Write Table */
	saa7127_ग_लिखो_inittab(sd, inittab);
	state->std = std;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_set_output_type(काष्ठा v4l2_subdev *sd, पूर्णांक output)
अणु
	काष्ठा saa7127_state *state = to_state(sd);

	चयन (output) अणु
	हाल SAA7127_OUTPUT_TYPE_RGB:
		state->reg_2d = 0x0f;	/* RGB + CVBS (क्रम sync) */
		state->reg_3a = 0x13;	/* by शेष चयन YUV to RGB-matrix on */
		अवरोध;

	हाल SAA7127_OUTPUT_TYPE_COMPOSITE:
		अगर (state->ident == SAA7129)
			state->reg_2d = 0x20;	/* CVBS only */
		अन्यथा
			state->reg_2d = 0x08;	/* 00001000 CVBS only, RGB DAC's off (high impedance mode) */
		state->reg_3a = 0x13;	/* by शेष चयन YUV to RGB-matrix on */
		अवरोध;

	हाल SAA7127_OUTPUT_TYPE_SVIDEO:
		अगर (state->ident == SAA7129)
			state->reg_2d = 0x18;	/* Y + C */
		अन्यथा
			state->reg_2d = 0xff;   /*11111111  croma -> R, luma -> CVBS + G + B */
		state->reg_3a = 0x13;	/* by शेष चयन YUV to RGB-matrix on */
		अवरोध;

	हाल SAA7127_OUTPUT_TYPE_YUV_V:
		state->reg_2d = 0x4f;	/* reg 2D = 01001111, all DAC's on, RGB + VBS */
		state->reg_3a = 0x0b;	/* reg 3A = 00001011, bypass RGB-matrix */
		अवरोध;

	हाल SAA7127_OUTPUT_TYPE_YUV_C:
		state->reg_2d = 0x0f;	/* reg 2D = 00001111, all DAC's on, RGB + CVBS */
		state->reg_3a = 0x0b;	/* reg 3A = 00001011, bypass RGB-matrix */
		अवरोध;

	हाल SAA7127_OUTPUT_TYPE_BOTH:
		अगर (state->ident == SAA7129)
			state->reg_2d = 0x38;
		अन्यथा
			state->reg_2d = 0xbf;
		state->reg_3a = 0x13;	/* by शेष चयन YUV to RGB-matrix on */
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	v4l2_dbg(1, debug, sd,
		"Selecting %s output type\n", output_strs[output]);

	/* Configure Encoder */
	saa7127_ग_लिखो(sd, 0x2d, state->reg_2d);
	saa7127_ग_लिखो(sd, 0x3a, state->reg_3a | state->reg_3a_cb);
	state->output_type = output;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_set_input_type(काष्ठा v4l2_subdev *sd, पूर्णांक input)
अणु
	काष्ठा saa7127_state *state = to_state(sd);

	चयन (input) अणु
	हाल SAA7127_INPUT_TYPE_NORMAL:	/* avia */
		v4l2_dbg(1, debug, sd, "Selecting Normal Encoder Input\n");
		state->reg_3a_cb = 0;
		अवरोध;

	हाल SAA7127_INPUT_TYPE_TEST_IMAGE:	/* color bar */
		v4l2_dbg(1, debug, sd, "Selecting Color Bar generator\n");
		state->reg_3a_cb = 0x80;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	saa7127_ग_लिखो(sd, 0x3a, state->reg_3a | state->reg_3a_cb);
	state->input_type = input;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_s_std_output(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा saa7127_state *state = to_state(sd);

	अगर (state->std == std)
		वापस 0;
	वापस saa7127_set_std(sd, std);
पूर्ण

अटल पूर्णांक saa7127_s_routing(काष्ठा v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
अणु
	काष्ठा saa7127_state *state = to_state(sd);
	पूर्णांक rc = 0;

	अगर (state->input_type != input)
		rc = saa7127_set_input_type(sd, input);
	अगर (rc == 0 && state->output_type != output)
		rc = saa7127_set_output_type(sd, output);
	वापस rc;
पूर्ण

अटल पूर्णांक saa7127_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा saa7127_state *state = to_state(sd);

	अगर (state->video_enable == enable)
		वापस 0;
	वापस saa7127_set_video_enable(sd, enable);
पूर्ण

अटल पूर्णांक saa7127_g_sliced_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *fmt)
अणु
	काष्ठा saa7127_state *state = to_state(sd);

	स_रखो(fmt->service_lines, 0, माप(fmt->service_lines));
	अगर (state->vps_enable)
		fmt->service_lines[0][16] = V4L2_SLICED_VPS;
	अगर (state->wss_enable)
		fmt->service_lines[0][23] = V4L2_SLICED_WSS_625;
	अगर (state->cc_enable) अणु
		fmt->service_lines[0][21] = V4L2_SLICED_CAPTION_525;
		fmt->service_lines[1][21] = V4L2_SLICED_CAPTION_525;
	पूर्ण
	fmt->service_set =
		(state->vps_enable ? V4L2_SLICED_VPS : 0) |
		(state->wss_enable ? V4L2_SLICED_WSS_625 : 0) |
		(state->cc_enable ? V4L2_SLICED_CAPTION_525 : 0);
	वापस 0;
पूर्ण

अटल पूर्णांक saa7127_s_vbi_data(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_sliced_vbi_data *data)
अणु
	चयन (data->id) अणु
	हाल V4L2_SLICED_WSS_625:
		वापस saa7127_set_wss(sd, data);
	हाल V4L2_SLICED_VPS:
		वापस saa7127_set_vps(sd, data);
	हाल V4L2_SLICED_CAPTION_525:
		अगर (data->field == 0)
			वापस saa7127_set_cc(sd, data);
		वापस saa7127_set_xds(sd, data);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक saa7127_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = saa7127_पढ़ो(sd, reg->reg & 0xff);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक saa7127_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	saa7127_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक saa7127_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा saa7127_state *state = to_state(sd);

	v4l2_info(sd, "Standard: %s\n", (state->std & V4L2_STD_525_60) ? "60 Hz" : "50 Hz");
	v4l2_info(sd, "Input:    %s\n", state->input_type ?  "color bars" : "normal");
	v4l2_info(sd, "Output:   %s\n", state->video_enable ?
			output_strs[state->output_type] : "disabled");
	v4l2_info(sd, "WSS:      %s\n", state->wss_enable ?
			wss_strs[state->wss_mode] : "disabled");
	v4l2_info(sd, "VPS:      %s\n", state->vps_enable ? "enabled" : "disabled");
	v4l2_info(sd, "CC:       %s\n", state->cc_enable ? "enabled" : "disabled");
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops saa7127_core_ops = अणु
	.log_status = saa7127_log_status,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = saa7127_g_रेजिस्टर,
	.s_रेजिस्टर = saa7127_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops saa7127_video_ops = अणु
	.s_std_output = saa7127_s_std_output,
	.s_routing = saa7127_s_routing,
	.s_stream = saa7127_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_vbi_ops saa7127_vbi_ops = अणु
	.s_vbi_data = saa7127_s_vbi_data,
	.g_sliced_fmt = saa7127_g_sliced_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops saa7127_ops = अणु
	.core = &saa7127_core_ops,
	.video = &saa7127_video_ops,
	.vbi = &saa7127_vbi_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा saa7127_state *state;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_sliced_vbi_data vbi = अणु 0, 0, 0, 0 पूर्ण;  /* set to disabled */

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	v4l_dbg(1, debug, client, "detecting saa7127 client on address 0x%x\n",
			client->addr << 1);

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &saa7127_ops);

	/* First test रेजिस्टर 0: Bits 5-7 are a version ID (should be 0),
	   and bit 2 should also be 0.
	   This is rather general, so the second test is more specअगरic and
	   looks at the 'ending point of burst in clock cycles' which is
	   0x1d after a reset and not expected to ever change. */
	अगर ((saa7127_पढ़ो(sd, 0) & 0xe4) != 0 ||
			(saa7127_पढ़ो(sd, 0x29) & 0x3f) != 0x1d) अणु
		v4l2_dbg(1, debug, sd, "saa7127 not found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (id->driver_data) अणु	/* Chip type is alपढ़ोy known */
		state->ident = id->driver_data;
	पूर्ण अन्यथा अणु		/* Needs detection */
		पूर्णांक पढ़ो_result;

		/* Detect अगर it's an saa7129 */
		पढ़ो_result = saa7127_पढ़ो(sd, SAA7129_REG_FADE_KEY_COL2);
		saa7127_ग_लिखो(sd, SAA7129_REG_FADE_KEY_COL2, 0xaa);
		अगर (saa7127_पढ़ो(sd, SAA7129_REG_FADE_KEY_COL2) == 0xaa) अणु
			saa7127_ग_लिखो(sd, SAA7129_REG_FADE_KEY_COL2,
					पढ़ो_result);
			state->ident = SAA7129;
			strscpy(client->name, "saa7129", I2C_NAME_SIZE);
		पूर्ण अन्यथा अणु
			state->ident = SAA7127;
			strscpy(client->name, "saa7127", I2C_NAME_SIZE);
		पूर्ण
	पूर्ण

	v4l2_info(sd, "%s found @ 0x%x (%s)\n", client->name,
			client->addr << 1, client->adapter->name);

	v4l2_dbg(1, debug, sd, "Configuring encoder\n");
	saa7127_ग_लिखो_inittab(sd, saa7127_init_config_common);
	saa7127_set_std(sd, V4L2_STD_NTSC);
	saa7127_set_output_type(sd, SAA7127_OUTPUT_TYPE_BOTH);
	saa7127_set_vps(sd, &vbi);
	saa7127_set_wss(sd, &vbi);
	saa7127_set_cc(sd, &vbi);
	saa7127_set_xds(sd, &vbi);
	अगर (test_image == 1)
		/* The Encoder has an पूर्णांकernal Colorbar generator */
		/* This can be used क्रम debugging */
		saa7127_set_input_type(sd, SAA7127_INPUT_TYPE_TEST_IMAGE);
	अन्यथा
		saa7127_set_input_type(sd, SAA7127_INPUT_TYPE_NORMAL);
	saa7127_set_video_enable(sd, 1);

	अगर (state->ident == SAA7129)
		saa7127_ग_लिखो_inittab(sd, saa7129_init_config_extra);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa7127_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	/* Turn off TV output */
	saa7127_set_video_enable(sd, 0);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id saa7127_id[] = अणु
	अणु "saa7127_auto", 0 पूर्ण,	/* स्वतः-detection */
	अणु "saa7126", SAA7127 पूर्ण,
	अणु "saa7127", SAA7127 पूर्ण,
	अणु "saa7128", SAA7129 पूर्ण,
	अणु "saa7129", SAA7129 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, saa7127_id);

अटल काष्ठा i2c_driver saa7127_driver = अणु
	.driver = अणु
		.name	= "saa7127",
	पूर्ण,
	.probe		= saa7127_probe,
	.हटाओ		= saa7127_हटाओ,
	.id_table	= saa7127_id,
पूर्ण;

module_i2c_driver(saa7127_driver);
