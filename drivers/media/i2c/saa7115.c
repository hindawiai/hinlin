<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// saa711x - Philips SAA711x video decoder driver
// This driver can work with saa7111, saa7111a, saa7113, saa7114,
//			     saa7115 and saa7118.
//
// Based on saa7114 driver by Maxim Yevtyushkin, which is based on
// the saa7111 driver by Dave Perks.
//
// Copyright (C) 1998 Dave Perks <dperks@ibm.net>
// Copyright (C) 2002 Maxim Yevtyushkin <max@linuxmediaद_असल.com>
//
// Slight changes क्रम video timing and attachment output by
// Wolfgang Scherr <scherr@net4you.net>
//
// Moved over to the linux >= 2.4.x i2c protocol (1/1/2003)
// by Ronald Bultje <rbultje@ronald.bitfreak.net>
//
// Added saa7115 support by Kevin Thayer <nufan_wfk at yahoo.com>
// (2/17/2003)
//
// VBI support (2004) and cleanups (2005) by Hans Verkuil <hverkuil@xs4all.nl>
//
// Copyright (c) 2005-2006 Mauro Carvalho Chehab <mchehab@kernel.org>
//	SAA7111, SAA7113 and SAA7118 support

#समावेश "saa711x_regs.h"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/i2c/saa7115.h>
#समावेश <यंत्र/भाग64.h>

#घोषणा VRES_60HZ	(480+16)

MODULE_DESCRIPTION("Philips SAA7111/SAA7113/SAA7114/SAA7115/SAA7118 video decoder driver");
MODULE_AUTHOR(  "Maxim Yevtyushkin, Kevin Thayer, Chris Kennedy, "
		"Hans Verkuil, Mauro Carvalho Chehab");
MODULE_LICENSE("GPL");

अटल bool debug;
module_param(debug, bool, 0644);

MODULE_PARM_DESC(debug, "Debug level (0-1)");


क्रमागत saa711x_model अणु
	SAA7111A,
	SAA7111,
	SAA7113,
	GM7113C,
	SAA7114,
	SAA7115,
	SAA7118,
पूर्ण;

क्रमागत saa711x_pads अणु
	SAA711X_PAD_IF_INPUT,
	SAA711X_PAD_VID_OUT,
	SAA711X_NUM_PADS
पूर्ण;

काष्ठा saa711x_state अणु
	काष्ठा v4l2_subdev sd;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_pad pads[SAA711X_NUM_PADS];
#पूर्ण_अगर
	काष्ठा v4l2_ctrl_handler hdl;

	काष्ठा अणु
		/* chroma gain control cluster */
		काष्ठा v4l2_ctrl *agc;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;

	v4l2_std_id std;
	पूर्णांक input;
	पूर्णांक output;
	पूर्णांक enable;
	पूर्णांक radio;
	पूर्णांक width;
	पूर्णांक height;
	क्रमागत saa711x_model ident;
	u32 audclk_freq;
	u32 crystal_freq;
	bool ucgc;
	u8 cgcभाग;
	bool apll;
	bool द्विगुन_asclk;
पूर्ण;

अटल अंतरभूत काष्ठा saa711x_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा saa711x_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा saa711x_state, hdl)->sd;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल अंतरभूत पूर्णांक saa711x_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

/* Sanity routine to check अगर a रेजिस्टर is present */
अटल पूर्णांक saa711x_has_reg(स्थिर पूर्णांक id, स्थिर u8 reg)
अणु
	अगर (id == SAA7111)
		वापस reg < 0x20 && reg != 0x01 && reg != 0x0f &&
		       (reg < 0x13 || reg > 0x19) && reg != 0x1d && reg != 0x1e;
	अगर (id == SAA7111A)
		वापस reg < 0x20 && reg != 0x01 && reg != 0x0f &&
		       reg != 0x14 && reg != 0x18 && reg != 0x19 &&
		       reg != 0x1d && reg != 0x1e;

	/* common क्रम saa7113/4/5/8 */
	अगर (unlikely((reg >= 0x3b && reg <= 0x3f) || reg == 0x5c || reg == 0x5f ||
	    reg == 0xa3 || reg == 0xa7 || reg == 0xab || reg == 0xaf || (reg >= 0xb5 && reg <= 0xb7) ||
	    reg == 0xd3 || reg == 0xd7 || reg == 0xdb || reg == 0xdf || (reg >= 0xe5 && reg <= 0xe7) ||
	    reg == 0x82 || (reg >= 0x89 && reg <= 0x8e)))
		वापस 0;

	चयन (id) अणु
	हाल GM7113C:
		वापस reg != 0x14 && (reg < 0x18 || reg > 0x1e) && reg < 0x20;
	हाल SAA7113:
		वापस reg != 0x14 && (reg < 0x18 || reg > 0x1e) && (reg < 0x20 || reg > 0x3f) &&
		       reg != 0x5d && reg < 0x63;
	हाल SAA7114:
		वापस (reg < 0x1a || reg > 0x1e) && (reg < 0x20 || reg > 0x2f) &&
		       (reg < 0x63 || reg > 0x7f) && reg != 0x33 && reg != 0x37 &&
		       reg != 0x81 && reg < 0xf0;
	हाल SAA7115:
		वापस (reg < 0x20 || reg > 0x2f) && reg != 0x65 && (reg < 0xfc || reg > 0xfe);
	हाल SAA7118:
		वापस (reg < 0x1a || reg > 0x1d) && (reg < 0x20 || reg > 0x22) &&
		       (reg < 0x26 || reg > 0x28) && reg != 0x33 && reg != 0x37 &&
		       (reg < 0x63 || reg > 0x7f) && reg != 0x81 && reg < 0xf0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक saa711x_ग_लिखोregs(काष्ठा v4l2_subdev *sd, स्थिर अचिन्हित अक्षर *regs)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	अचिन्हित अक्षर reg, data;

	जबतक (*regs != 0x00) अणु
		reg = *(regs++);
		data = *(regs++);

		/* According with datasheets, reserved regs should be
		   filled with 0 - seems better not to touch on they */
		अगर (saa711x_has_reg(state->ident, reg)) अणु
			अगर (saa711x_ग_लिखो(sd, reg, data) < 0)
				वापस -1;
		पूर्ण अन्यथा अणु
			v4l2_dbg(1, debug, sd, "tried to access reserved reg 0x%02x\n", reg);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक saa711x_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

/* ----------------------------------------------------------------------- */

/* SAA7111 initialization table */
अटल स्थिर अचिन्हित अक्षर saa7111_init[] = अणु
	R_01_INC_DELAY, 0x00,		/* reserved */

	/*front end */
	R_02_INPUT_CNTL_1, 0xd0,	/* FUSE=3, GUDL=2, MODE=0 */
	R_03_INPUT_CNTL_2, 0x23,	/* HLNRS=0, VBSL=1, WPOFF=0, HOLDG=0,
					 * GAFIX=0, GAI1=256, GAI2=256 */
	R_04_INPUT_CNTL_3, 0x00,	/* GAI1=256 */
	R_05_INPUT_CNTL_4, 0x00,	/* GAI2=256 */

	/* decoder */
	R_06_H_SYNC_START, 0xf3,	/* HSB at  13(50Hz) /  17(60Hz)
					 * pixels after end of last line */
	R_07_H_SYNC_STOP, 0xe8,		/* HSS seems to be needed to
					 * work with NTSC, too */
	R_08_SYNC_CNTL, 0xc8,		/* AUFD=1, FSEL=1, EXFIL=0,
					 * VTRC=1, HPLL=0, VNOI=0 */
	R_09_LUMA_CNTL, 0x01,		/* BYPS=0, PREF=0, BPSS=0,
					 * VBLB=0, UPTCV=0, APER=1 */
	R_0A_LUMA_BRIGHT_CNTL, 0x80,
	R_0B_LUMA_CONTRAST_CNTL, 0x47,	/* 0b - CONT=1.109 */
	R_0C_CHROMA_SAT_CNTL, 0x40,
	R_0D_CHROMA_HUE_CNTL, 0x00,
	R_0E_CHROMA_CNTL_1, 0x01,	/* 0e - CDTO=0, CSTD=0, DCCF=0,
					 * FCTC=0, CHBW=1 */
	R_0F_CHROMA_GAIN_CNTL, 0x00,	/* reserved */
	R_10_CHROMA_CNTL_2, 0x48,	/* 10 - OFTS=1, HDEL=0, VRLN=1, YDEL=0 */
	R_11_MODE_DELAY_CNTL, 0x1c,	/* 11 - GPSW=0, CM99=0, FECO=0, COMPO=1,
					 * OEYC=1, OEHV=1, VIPB=0, COLO=0 */
	R_12_RT_SIGNAL_CNTL, 0x00,	/* 12 - output control 2 */
	R_13_RT_X_PORT_OUT_CNTL, 0x00,	/* 13 - output control 3 */
	R_14_ANAL_ADC_COMPAT_CNTL, 0x00,
	R_15_VGATE_START_FID_CHG, 0x00,
	R_16_VGATE_STOP, 0x00,
	R_17_MISC_VGATE_CONF_AND_MSB, 0x00,

	0x00, 0x00
पूर्ण;

/*
 * This table has one illegal value, and some values that are not
 * correct according to the datasheet initialization table.
 *
 *  If you need a table with legal/शेष values tell the driver in
 *  i2c_board_info.platक्रमm_data, and you will get the gm7113c_init
 *  table instead.
 */

/* SAA7113 Init codes */
अटल स्थिर अचिन्हित अक्षर saa7113_init[] = अणु
	R_01_INC_DELAY, 0x08,
	R_02_INPUT_CNTL_1, 0xc2,
	R_03_INPUT_CNTL_2, 0x30,
	R_04_INPUT_CNTL_3, 0x00,
	R_05_INPUT_CNTL_4, 0x00,
	R_06_H_SYNC_START, 0x89,	/* Illegal value -119,
					 * min. value = -108 (0x94) */
	R_07_H_SYNC_STOP, 0x0d,
	R_08_SYNC_CNTL, 0x88,		/* Not datasheet शेष.
					 * HTC = VTR mode, should be 0x98 */
	R_09_LUMA_CNTL, 0x01,
	R_0A_LUMA_BRIGHT_CNTL, 0x80,
	R_0B_LUMA_CONTRAST_CNTL, 0x47,
	R_0C_CHROMA_SAT_CNTL, 0x40,
	R_0D_CHROMA_HUE_CNTL, 0x00,
	R_0E_CHROMA_CNTL_1, 0x01,
	R_0F_CHROMA_GAIN_CNTL, 0x2a,
	R_10_CHROMA_CNTL_2, 0x08,	/* Not datsheet शेष.
					 * VRLN enabled, should be 0x00 */
	R_11_MODE_DELAY_CNTL, 0x0c,
	R_12_RT_SIGNAL_CNTL, 0x07,	/* Not datasheet शेष,
					 * should be 0x01 */
	R_13_RT_X_PORT_OUT_CNTL, 0x00,
	R_14_ANAL_ADC_COMPAT_CNTL, 0x00,
	R_15_VGATE_START_FID_CHG, 0x00,
	R_16_VGATE_STOP, 0x00,
	R_17_MISC_VGATE_CONF_AND_MSB, 0x00,

	0x00, 0x00
पूर्ण;

/*
 * GM7113C is a clone of the SAA7113 chip
 *  This init table is copied out of the saa7113 datasheet.
 *  In R_08 we enable "Automatic Field Detection" [AUFD],
 *  this is disabled when saa711x_set_v4lstd is called.
 */
अटल स्थिर अचिन्हित अक्षर gm7113c_init[] = अणु
	R_01_INC_DELAY, 0x08,
	R_02_INPUT_CNTL_1, 0xc0,
	R_03_INPUT_CNTL_2, 0x33,
	R_04_INPUT_CNTL_3, 0x00,
	R_05_INPUT_CNTL_4, 0x00,
	R_06_H_SYNC_START, 0xe9,
	R_07_H_SYNC_STOP, 0x0d,
	R_08_SYNC_CNTL, 0x98,
	R_09_LUMA_CNTL, 0x01,
	R_0A_LUMA_BRIGHT_CNTL, 0x80,
	R_0B_LUMA_CONTRAST_CNTL, 0x47,
	R_0C_CHROMA_SAT_CNTL, 0x40,
	R_0D_CHROMA_HUE_CNTL, 0x00,
	R_0E_CHROMA_CNTL_1, 0x01,
	R_0F_CHROMA_GAIN_CNTL, 0x2a,
	R_10_CHROMA_CNTL_2, 0x00,
	R_11_MODE_DELAY_CNTL, 0x0c,
	R_12_RT_SIGNAL_CNTL, 0x01,
	R_13_RT_X_PORT_OUT_CNTL, 0x00,
	R_14_ANAL_ADC_COMPAT_CNTL, 0x00,
	R_15_VGATE_START_FID_CHG, 0x00,
	R_16_VGATE_STOP, 0x00,
	R_17_MISC_VGATE_CONF_AND_MSB, 0x00,

	0x00, 0x00
पूर्ण;

/* If a value dअगरfers from the Hauppauge driver values, then the comment starts with
   'was 0xXX' to denote the Hauppauge value. Otherwise the value is identical to what the
   Hauppauge driver sets. */

/* SAA7114 and SAA7115 initialization table */
अटल स्थिर अचिन्हित अक्षर saa7115_init_स्वतः_input[] = अणु
		/* Front-End Part */
	R_01_INC_DELAY, 0x48,			/* white peak control disabled */
	R_03_INPUT_CNTL_2, 0x20,		/* was 0x30. 0x20: दीर्घ vertical blanking */
	R_04_INPUT_CNTL_3, 0x90,		/* analog gain set to 0 */
	R_05_INPUT_CNTL_4, 0x90,		/* analog gain set to 0 */
		/* Decoder Part */
	R_06_H_SYNC_START, 0xeb,		/* horiz sync begin = -21 */
	R_07_H_SYNC_STOP, 0xe0,			/* horiz sync stop = -17 */
	R_09_LUMA_CNTL, 0x53,			/* 0x53, was 0x56 क्रम 60hz. luminance control */
	R_0A_LUMA_BRIGHT_CNTL, 0x80,		/* was 0x88. decoder brightness, 0x80 is itu standard */
	R_0B_LUMA_CONTRAST_CNTL, 0x44,		/* was 0x48. decoder contrast, 0x44 is itu standard */
	R_0C_CHROMA_SAT_CNTL, 0x40,		/* was 0x47. decoder saturation, 0x40 is itu standard */
	R_0D_CHROMA_HUE_CNTL, 0x00,
	R_0F_CHROMA_GAIN_CNTL, 0x00,		/* use स्वतःmatic gain  */
	R_10_CHROMA_CNTL_2, 0x06,		/* chroma: active adaptive combfilter */
	R_11_MODE_DELAY_CNTL, 0x00,
	R_12_RT_SIGNAL_CNTL, 0x9d,		/* RTS0 output control: VGATE */
	R_13_RT_X_PORT_OUT_CNTL, 0x80,		/* ITU656 standard mode, RTCO output enable RTCE */
	R_14_ANAL_ADC_COMPAT_CNTL, 0x00,
	R_18_RAW_DATA_GAIN_CNTL, 0x40,		/* gain 0x00 = nominal */
	R_19_RAW_DATA_OFF_CNTL, 0x80,
	R_1A_COLOR_KILL_LVL_CNTL, 0x77,		/* recommended value */
	R_1B_MISC_TVVCRDET, 0x42,		/* recommended value */
	R_1C_ENHAN_COMB_CTRL1, 0xa9,		/* recommended value */
	R_1D_ENHAN_COMB_CTRL2, 0x01,		/* recommended value */


	R_80_GLOBAL_CNTL_1, 0x0,		/* No tasks enabled at init */

		/* Power Device Control */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xd0,	/* reset device */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xf0,	/* set device programmed, all in operational mode */
	0x00, 0x00
पूर्ण;

/* Used to reset saa7113, saa7114 and saa7115 */
अटल स्थिर अचिन्हित अक्षर saa7115_cfg_reset_scaler[] = अणु
	R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED, 0x00,	/* disable I-port output */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xd0,		/* reset scaler */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xf0,		/* activate scaler */
	R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED, 0x01,	/* enable I-port output */
	0x00, 0x00
पूर्ण;

/* ============== SAA7715 VIDEO ढाँचाs =============  */

अटल स्थिर अचिन्हित अक्षर saa7115_cfg_60hz_video[] = अणु
	R_80_GLOBAL_CNTL_1, 0x00,			/* reset tasks */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xd0,		/* reset scaler */

	R_15_VGATE_START_FID_CHG, 0x03,
	R_16_VGATE_STOP, 0x11,
	R_17_MISC_VGATE_CONF_AND_MSB, 0x9c,

	R_08_SYNC_CNTL, 0x68,			/* 0xBO: स्वतः detection, 0x68 = NTSC */
	R_0E_CHROMA_CNTL_1, 0x07,		/* video स्वतःdetection is on */

	R_5A_V_OFF_FOR_SLICER, 0x06,		/* standard 60hz value क्रम ITU656 line counting */

	/* Task A */
	R_90_A_TASK_HANDLING_CNTL, 0x80,
	R_91_A_X_PORT_FORMATS_AND_CONF, 0x48,
	R_92_A_X_PORT_INPUT_REFERENCE_SIGNAL, 0x40,
	R_93_A_I_PORT_OUTPUT_FORMATS_AND_CONF, 0x84,

	/* hoffset low (input), 0x0002 is minimum */
	R_94_A_HORIZ_INPUT_WINDOW_START, 0x01,
	R_95_A_HORIZ_INPUT_WINDOW_START_MSB, 0x00,

	/* hsize low (input), 0x02d0 = 720 */
	R_96_A_HORIZ_INPUT_WINDOW_LENGTH, 0xd0,
	R_97_A_HORIZ_INPUT_WINDOW_LENGTH_MSB, 0x02,

	R_98_A_VERT_INPUT_WINDOW_START, 0x05,
	R_99_A_VERT_INPUT_WINDOW_START_MSB, 0x00,

	R_9A_A_VERT_INPUT_WINDOW_LENGTH, 0x0c,
	R_9B_A_VERT_INPUT_WINDOW_LENGTH_MSB, 0x00,

	R_9C_A_HORIZ_OUTPUT_WINDOW_LENGTH, 0xa0,
	R_9D_A_HORIZ_OUTPUT_WINDOW_LENGTH_MSB, 0x05,

	R_9E_A_VERT_OUTPUT_WINDOW_LENGTH, 0x0c,
	R_9F_A_VERT_OUTPUT_WINDOW_LENGTH_MSB, 0x00,

	/* Task B */
	R_C0_B_TASK_HANDLING_CNTL, 0x00,
	R_C1_B_X_PORT_FORMATS_AND_CONF, 0x08,
	R_C2_B_INPUT_REFERENCE_SIGNAL_DEFINITION, 0x00,
	R_C3_B_I_PORT_FORMATS_AND_CONF, 0x80,

	/* 0x0002 is minimum */
	R_C4_B_HORIZ_INPUT_WINDOW_START, 0x02,
	R_C5_B_HORIZ_INPUT_WINDOW_START_MSB, 0x00,

	/* 0x02d0 = 720 */
	R_C6_B_HORIZ_INPUT_WINDOW_LENGTH, 0xd0,
	R_C7_B_HORIZ_INPUT_WINDOW_LENGTH_MSB, 0x02,

	/* vwinकरोw start 0x12 = 18 */
	R_C8_B_VERT_INPUT_WINDOW_START, 0x12,
	R_C9_B_VERT_INPUT_WINDOW_START_MSB, 0x00,

	/* vwinकरोw length 0xf8 = 248 */
	R_CA_B_VERT_INPUT_WINDOW_LENGTH, VRES_60HZ>>1,
	R_CB_B_VERT_INPUT_WINDOW_LENGTH_MSB, VRES_60HZ>>9,

	/* hwinकरोw 0x02d0 = 720 */
	R_CC_B_HORIZ_OUTPUT_WINDOW_LENGTH, 0xd0,
	R_CD_B_HORIZ_OUTPUT_WINDOW_LENGTH_MSB, 0x02,

	R_F0_LFCO_PER_LINE, 0xad,		/* Set PLL Register. 60hz 525 lines per frame, 27 MHz */
	R_F1_P_I_PARAM_SELECT, 0x05,		/* low bit with 0xF0 */
	R_F5_PULSGEN_LINE_LENGTH, 0xad,
	R_F6_PULSE_A_POS_LSB_AND_PULSEGEN_CONFIG, 0x01,

	0x00, 0x00
पूर्ण;

अटल स्थिर अचिन्हित अक्षर saa7115_cfg_50hz_video[] = अणु
	R_80_GLOBAL_CNTL_1, 0x00,
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xd0,	/* reset scaler */

	R_15_VGATE_START_FID_CHG, 0x37,		/* VGATE start */
	R_16_VGATE_STOP, 0x16,
	R_17_MISC_VGATE_CONF_AND_MSB, 0x99,

	R_08_SYNC_CNTL, 0x28,			/* 0x28 = PAL */
	R_0E_CHROMA_CNTL_1, 0x07,

	R_5A_V_OFF_FOR_SLICER, 0x03,		/* standard 50hz value */

	/* Task A */
	R_90_A_TASK_HANDLING_CNTL, 0x81,
	R_91_A_X_PORT_FORMATS_AND_CONF, 0x48,
	R_92_A_X_PORT_INPUT_REFERENCE_SIGNAL, 0x40,
	R_93_A_I_PORT_OUTPUT_FORMATS_AND_CONF, 0x84,

	/* This is weird: the datasheet says that you should use 2 as the minimum value, */
	/* but Hauppauge uses 0, and changing that to 2 causes indeed problems (क्रम 50hz) */
	/* hoffset low (input), 0x0002 is minimum */
	R_94_A_HORIZ_INPUT_WINDOW_START, 0x00,
	R_95_A_HORIZ_INPUT_WINDOW_START_MSB, 0x00,

	/* hsize low (input), 0x02d0 = 720 */
	R_96_A_HORIZ_INPUT_WINDOW_LENGTH, 0xd0,
	R_97_A_HORIZ_INPUT_WINDOW_LENGTH_MSB, 0x02,

	R_98_A_VERT_INPUT_WINDOW_START, 0x03,
	R_99_A_VERT_INPUT_WINDOW_START_MSB, 0x00,

	/* vsize 0x12 = 18 */
	R_9A_A_VERT_INPUT_WINDOW_LENGTH, 0x12,
	R_9B_A_VERT_INPUT_WINDOW_LENGTH_MSB, 0x00,

	/* hsize 0x05a0 = 1440 */
	R_9C_A_HORIZ_OUTPUT_WINDOW_LENGTH, 0xa0,
	R_9D_A_HORIZ_OUTPUT_WINDOW_LENGTH_MSB, 0x05,	/* hsize hi (output) */
	R_9E_A_VERT_OUTPUT_WINDOW_LENGTH, 0x12,		/* vsize low (output), 0x12 = 18 */
	R_9F_A_VERT_OUTPUT_WINDOW_LENGTH_MSB, 0x00,	/* vsize hi (output) */

	/* Task B */
	R_C0_B_TASK_HANDLING_CNTL, 0x00,
	R_C1_B_X_PORT_FORMATS_AND_CONF, 0x08,
	R_C2_B_INPUT_REFERENCE_SIGNAL_DEFINITION, 0x00,
	R_C3_B_I_PORT_FORMATS_AND_CONF, 0x80,

	/* This is weird: the datasheet says that you should use 2 as the minimum value, */
	/* but Hauppauge uses 0, and changing that to 2 causes indeed problems (क्रम 50hz) */
	/* hoffset low (input), 0x0002 is minimum. See comment above. */
	R_C4_B_HORIZ_INPUT_WINDOW_START, 0x00,
	R_C5_B_HORIZ_INPUT_WINDOW_START_MSB, 0x00,

	/* hsize 0x02d0 = 720 */
	R_C6_B_HORIZ_INPUT_WINDOW_LENGTH, 0xd0,
	R_C7_B_HORIZ_INPUT_WINDOW_LENGTH_MSB, 0x02,

	/* voffset 0x16 = 22 */
	R_C8_B_VERT_INPUT_WINDOW_START, 0x16,
	R_C9_B_VERT_INPUT_WINDOW_START_MSB, 0x00,

	/* vsize 0x0120 = 288 */
	R_CA_B_VERT_INPUT_WINDOW_LENGTH, 0x20,
	R_CB_B_VERT_INPUT_WINDOW_LENGTH_MSB, 0x01,

	/* hsize 0x02d0 = 720 */
	R_CC_B_HORIZ_OUTPUT_WINDOW_LENGTH, 0xd0,
	R_CD_B_HORIZ_OUTPUT_WINDOW_LENGTH_MSB, 0x02,

	R_F0_LFCO_PER_LINE, 0xb0,		/* Set PLL Register. 50hz 625 lines per frame, 27 MHz */
	R_F1_P_I_PARAM_SELECT, 0x05,		/* low bit with 0xF0, (was 0x05) */
	R_F5_PULSGEN_LINE_LENGTH, 0xb0,
	R_F6_PULSE_A_POS_LSB_AND_PULSEGEN_CONFIG, 0x01,

	0x00, 0x00
पूर्ण;

/* ============== SAA7715 VIDEO ढाँचाs (end) =======  */

अटल स्थिर अचिन्हित अक्षर saa7115_cfg_vbi_on[] = अणु
	R_80_GLOBAL_CNTL_1, 0x00,			/* reset tasks */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xd0,		/* reset scaler */
	R_80_GLOBAL_CNTL_1, 0x30,			/* Activate both tasks */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xf0,		/* activate scaler */
	R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED, 0x01,	/* Enable I-port output */

	0x00, 0x00
पूर्ण;

अटल स्थिर अचिन्हित अक्षर saa7115_cfg_vbi_off[] = अणु
	R_80_GLOBAL_CNTL_1, 0x00,			/* reset tasks */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xd0,		/* reset scaler */
	R_80_GLOBAL_CNTL_1, 0x20,			/* Activate only task "B" */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xf0,		/* activate scaler */
	R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED, 0x01,	/* Enable I-port output */

	0x00, 0x00
पूर्ण;


अटल स्थिर अचिन्हित अक्षर saa7115_init_misc[] = अणु
	R_81_V_SYNC_FLD_ID_SRC_SEL_AND_RETIMED_V_F, 0x01,
	R_83_X_PORT_I_O_ENA_AND_OUT_CLK, 0x01,
	R_84_I_PORT_SIGNAL_DEF, 0x20,
	R_85_I_PORT_SIGNAL_POLAR, 0x21,
	R_86_I_PORT_FIFO_FLAG_CNTL_AND_ARBIT, 0xc5,
	R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED, 0x01,

	/* Task A */
	R_A0_A_HORIZ_PRESCALING, 0x01,
	R_A1_A_ACCUMULATION_LENGTH, 0x00,
	R_A2_A_PRESCALER_DC_GAIN_AND_FIR_PREFILTER, 0x00,

	/* Configure controls at nominal value*/
	R_A4_A_LUMA_BRIGHTNESS_CNTL, 0x80,
	R_A5_A_LUMA_CONTRAST_CNTL, 0x40,
	R_A6_A_CHROMA_SATURATION_CNTL, 0x40,

	/* note: 2 x zoom ensures that VBI lines have same length as video lines. */
	R_A8_A_HORIZ_LUMA_SCALING_INC, 0x00,
	R_A9_A_HORIZ_LUMA_SCALING_INC_MSB, 0x02,

	R_AA_A_HORIZ_LUMA_PHASE_OFF, 0x00,

	/* must be horiz lum scaling / 2 */
	R_AC_A_HORIZ_CHROMA_SCALING_INC, 0x00,
	R_AD_A_HORIZ_CHROMA_SCALING_INC_MSB, 0x01,

	/* must be offset luma / 2 */
	R_AE_A_HORIZ_CHROMA_PHASE_OFF, 0x00,

	R_B0_A_VERT_LUMA_SCALING_INC, 0x00,
	R_B1_A_VERT_LUMA_SCALING_INC_MSB, 0x04,

	R_B2_A_VERT_CHROMA_SCALING_INC, 0x00,
	R_B3_A_VERT_CHROMA_SCALING_INC_MSB, 0x04,

	R_B4_A_VERT_SCALING_MODE_CNTL, 0x01,

	R_B8_A_VERT_CHROMA_PHASE_OFF_00, 0x00,
	R_B9_A_VERT_CHROMA_PHASE_OFF_01, 0x00,
	R_BA_A_VERT_CHROMA_PHASE_OFF_10, 0x00,
	R_BB_A_VERT_CHROMA_PHASE_OFF_11, 0x00,

	R_BC_A_VERT_LUMA_PHASE_OFF_00, 0x00,
	R_BD_A_VERT_LUMA_PHASE_OFF_01, 0x00,
	R_BE_A_VERT_LUMA_PHASE_OFF_10, 0x00,
	R_BF_A_VERT_LUMA_PHASE_OFF_11, 0x00,

	/* Task B */
	R_D0_B_HORIZ_PRESCALING, 0x01,
	R_D1_B_ACCUMULATION_LENGTH, 0x00,
	R_D2_B_PRESCALER_DC_GAIN_AND_FIR_PREFILTER, 0x00,

	/* Configure controls at nominal value*/
	R_D4_B_LUMA_BRIGHTNESS_CNTL, 0x80,
	R_D5_B_LUMA_CONTRAST_CNTL, 0x40,
	R_D6_B_CHROMA_SATURATION_CNTL, 0x40,

	/* hor lum scaling 0x0400 = 1 */
	R_D8_B_HORIZ_LUMA_SCALING_INC, 0x00,
	R_D9_B_HORIZ_LUMA_SCALING_INC_MSB, 0x04,

	R_DA_B_HORIZ_LUMA_PHASE_OFF, 0x00,

	/* must be hor lum scaling / 2 */
	R_DC_B_HORIZ_CHROMA_SCALING, 0x00,
	R_DD_B_HORIZ_CHROMA_SCALING_MSB, 0x02,

	/* must be offset luma / 2 */
	R_DE_B_HORIZ_PHASE_OFFSET_CRHOMA, 0x00,

	R_E0_B_VERT_LUMA_SCALING_INC, 0x00,
	R_E1_B_VERT_LUMA_SCALING_INC_MSB, 0x04,

	R_E2_B_VERT_CHROMA_SCALING_INC, 0x00,
	R_E3_B_VERT_CHROMA_SCALING_INC_MSB, 0x04,

	R_E4_B_VERT_SCALING_MODE_CNTL, 0x01,

	R_E8_B_VERT_CHROMA_PHASE_OFF_00, 0x00,
	R_E9_B_VERT_CHROMA_PHASE_OFF_01, 0x00,
	R_EA_B_VERT_CHROMA_PHASE_OFF_10, 0x00,
	R_EB_B_VERT_CHROMA_PHASE_OFF_11, 0x00,

	R_EC_B_VERT_LUMA_PHASE_OFF_00, 0x00,
	R_ED_B_VERT_LUMA_PHASE_OFF_01, 0x00,
	R_EE_B_VERT_LUMA_PHASE_OFF_10, 0x00,
	R_EF_B_VERT_LUMA_PHASE_OFF_11, 0x00,

	R_F2_NOMINAL_PLL2_DTO, 0x50,		/* crystal घड़ी = 24.576 MHz, target = 27MHz */
	R_F3_PLL_INCREMENT, 0x46,
	R_F4_PLL2_STATUS, 0x00,
	R_F7_PULSE_A_POS_MSB, 0x4b,		/* not the recommended settings! */
	R_F8_PULSE_B_POS, 0x00,
	R_F9_PULSE_B_POS_MSB, 0x4b,
	R_FA_PULSE_C_POS, 0x00,
	R_FB_PULSE_C_POS_MSB, 0x4b,

	/* PLL2 lock detection settings: 71 lines 50% phase error */
	R_FF_S_PLL_MAX_PHASE_ERR_THRESH_NUM_LINES, 0x88,

	/* Turn off VBI */
	R_40_SLICER_CNTL_1, 0x20,             /* No framing code errors allowed. */
	R_41_LCR_BASE, 0xff,
	R_41_LCR_BASE+1, 0xff,
	R_41_LCR_BASE+2, 0xff,
	R_41_LCR_BASE+3, 0xff,
	R_41_LCR_BASE+4, 0xff,
	R_41_LCR_BASE+5, 0xff,
	R_41_LCR_BASE+6, 0xff,
	R_41_LCR_BASE+7, 0xff,
	R_41_LCR_BASE+8, 0xff,
	R_41_LCR_BASE+9, 0xff,
	R_41_LCR_BASE+10, 0xff,
	R_41_LCR_BASE+11, 0xff,
	R_41_LCR_BASE+12, 0xff,
	R_41_LCR_BASE+13, 0xff,
	R_41_LCR_BASE+14, 0xff,
	R_41_LCR_BASE+15, 0xff,
	R_41_LCR_BASE+16, 0xff,
	R_41_LCR_BASE+17, 0xff,
	R_41_LCR_BASE+18, 0xff,
	R_41_LCR_BASE+19, 0xff,
	R_41_LCR_BASE+20, 0xff,
	R_41_LCR_BASE+21, 0xff,
	R_41_LCR_BASE+22, 0xff,
	R_58_PROGRAM_FRAMING_CODE, 0x40,
	R_59_H_OFF_FOR_SLICER, 0x47,
	R_5B_FLD_OFF_AND_MSB_FOR_H_AND_V_OFF, 0x83,
	R_5D_DID, 0xbd,
	R_5E_SDID, 0x35,

	R_02_INPUT_CNTL_1, 0xc4, /* input tuner -> input 4, amplअगरier active */

	R_80_GLOBAL_CNTL_1, 0x20,		/* enable task B */
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xd0,
	R_88_POWER_SAVE_ADC_PORT_CNTL, 0xf0,
	0x00, 0x00
पूर्ण;

अटल पूर्णांक saa711x_odd_parity(u8 c)
अणु
	c ^= (c >> 4);
	c ^= (c >> 2);
	c ^= (c >> 1);

	वापस c & 1;
पूर्ण

अटल पूर्णांक saa711x_decode_vps(u8 *dst, u8 *p)
अणु
	अटल स्थिर u8 biphase_tbl[] = अणु
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
		0xd2, 0x5a, 0x52, 0xd2, 0x96, 0x1e, 0x16, 0x96,
		0x92, 0x1a, 0x12, 0x92, 0xd2, 0x5a, 0x52, 0xd2,
		0xd0, 0x58, 0x50, 0xd0, 0x94, 0x1c, 0x14, 0x94,
		0x90, 0x18, 0x10, 0x90, 0xd0, 0x58, 0x50, 0xd0,
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
		0xe1, 0x69, 0x61, 0xe1, 0xa5, 0x2d, 0x25, 0xa5,
		0xa1, 0x29, 0x21, 0xa1, 0xe1, 0x69, 0x61, 0xe1,
		0xc3, 0x4b, 0x43, 0xc3, 0x87, 0x0f, 0x07, 0x87,
		0x83, 0x0b, 0x03, 0x83, 0xc3, 0x4b, 0x43, 0xc3,
		0xc1, 0x49, 0x41, 0xc1, 0x85, 0x0d, 0x05, 0x85,
		0x81, 0x09, 0x01, 0x81, 0xc1, 0x49, 0x41, 0xc1,
		0xe1, 0x69, 0x61, 0xe1, 0xa5, 0x2d, 0x25, 0xa5,
		0xa1, 0x29, 0x21, 0xa1, 0xe1, 0x69, 0x61, 0xe1,
		0xe0, 0x68, 0x60, 0xe0, 0xa4, 0x2c, 0x24, 0xa4,
		0xa0, 0x28, 0x20, 0xa0, 0xe0, 0x68, 0x60, 0xe0,
		0xc2, 0x4a, 0x42, 0xc2, 0x86, 0x0e, 0x06, 0x86,
		0x82, 0x0a, 0x02, 0x82, 0xc2, 0x4a, 0x42, 0xc2,
		0xc0, 0x48, 0x40, 0xc0, 0x84, 0x0c, 0x04, 0x84,
		0x80, 0x08, 0x00, 0x80, 0xc0, 0x48, 0x40, 0xc0,
		0xe0, 0x68, 0x60, 0xe0, 0xa4, 0x2c, 0x24, 0xa4,
		0xa0, 0x28, 0x20, 0xa0, 0xe0, 0x68, 0x60, 0xe0,
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
		0xd2, 0x5a, 0x52, 0xd2, 0x96, 0x1e, 0x16, 0x96,
		0x92, 0x1a, 0x12, 0x92, 0xd2, 0x5a, 0x52, 0xd2,
		0xd0, 0x58, 0x50, 0xd0, 0x94, 0x1c, 0x14, 0x94,
		0x90, 0x18, 0x10, 0x90, 0xd0, 0x58, 0x50, 0xd0,
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
	पूर्ण;
	पूर्णांक i;
	u8 c, err = 0;

	क्रम (i = 0; i < 2 * 13; i += 2) अणु
		err |= biphase_tbl[p[i]] | biphase_tbl[p[i + 1]];
		c = (biphase_tbl[p[i + 1]] & 0xf) | ((biphase_tbl[p[i]] & 0xf) << 4);
		dst[i / 2] = c;
	पूर्ण
	वापस err & 0xf0;
पूर्ण

अटल पूर्णांक saa711x_decode_wss(u8 *p)
अणु
	अटल स्थिर पूर्णांक wss_bits[8] = अणु
		0, 0, 0, 1, 0, 1, 1, 1
	पूर्ण;
	अचिन्हित अक्षर parity;
	पूर्णांक wss = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		पूर्णांक b1 = wss_bits[p[i] & 7];
		पूर्णांक b2 = wss_bits[(p[i] >> 3) & 7];

		अगर (b1 == b2)
			वापस -1;
		wss |= b2 << i;
	पूर्ण
	parity = wss & 15;
	parity ^= parity >> 2;
	parity ^= parity >> 1;

	अगर (!(parity & 1))
		वापस -1;

	वापस wss;
पूर्ण

अटल पूर्णांक saa711x_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	u32 acpf;
	u32 acni;
	u32 hz;
	u64 f;
	u8 acc = 0;	/* reg 0x3a, audio घड़ी control */

	/* Checks क्रम chips that करोn't have audio घड़ी (saa7111, saa7113) */
	अगर (!saa711x_has_reg(state->ident, R_30_AUD_MAST_CLK_CYCLES_PER_FIELD))
		वापस 0;

	v4l2_dbg(1, debug, sd, "set audio clock freq: %d\n", freq);

	/* sanity check */
	अगर (freq < 32000 || freq > 48000)
		वापस -EINVAL;

	/* hz is the refresh rate बार 100 */
	hz = (state->std & V4L2_STD_525_60) ? 5994 : 5000;
	/* acpf = (256 * freq) / field_frequency == (256 * 100 * freq) / hz */
	acpf = (25600 * freq) / hz;
	/* acni = (256 * freq * 2^23) / crystal_frequency =
		  (freq * 2^(8+23)) / crystal_frequency =
		  (freq << 31) / crystal_frequency */
	f = freq;
	f = f << 31;
	करो_भाग(f, state->crystal_freq);
	acni = f;
	अगर (state->ucgc) अणु
		acpf = acpf * state->cgcभाग / 16;
		acni = acni * state->cgcभाग / 16;
		acc = 0x80;
		अगर (state->cgcभाग == 3)
			acc |= 0x40;
	पूर्ण
	अगर (state->apll)
		acc |= 0x08;

	अगर (state->द्विगुन_asclk) अणु
		acpf <<= 1;
		acni <<= 1;
	पूर्ण
	saa711x_ग_लिखो(sd, R_38_CLK_RATIO_AMXCLK_TO_ASCLK, 0x03);
	saa711x_ग_लिखो(sd, R_39_CLK_RATIO_ASCLK_TO_ALRCLK, 0x10 << state->द्विगुन_asclk);
	saa711x_ग_लिखो(sd, R_3A_AUD_CLK_GEN_BASIC_SETUP, acc);

	saa711x_ग_लिखो(sd, R_30_AUD_MAST_CLK_CYCLES_PER_FIELD, acpf & 0xff);
	saa711x_ग_लिखो(sd, R_30_AUD_MAST_CLK_CYCLES_PER_FIELD+1,
							(acpf >> 8) & 0xff);
	saa711x_ग_लिखो(sd, R_30_AUD_MAST_CLK_CYCLES_PER_FIELD+2,
							(acpf >> 16) & 0x03);

	saa711x_ग_लिखो(sd, R_34_AUD_MAST_CLK_NOMINAL_INC, acni & 0xff);
	saa711x_ग_लिखो(sd, R_34_AUD_MAST_CLK_NOMINAL_INC+1, (acni >> 8) & 0xff);
	saa711x_ग_लिखो(sd, R_34_AUD_MAST_CLK_NOMINAL_INC+2, (acni >> 16) & 0x3f);
	state->audclk_freq = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा saa711x_state *state = to_state(sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_CHROMA_AGC:
		/* chroma gain cluster */
		अगर (state->agc->val)
			state->gain->val =
				saa711x_पढ़ो(sd, R_0F_CHROMA_GAIN_CNTL) & 0x7f;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा saa711x_state *state = to_state(sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		saa711x_ग_लिखो(sd, R_0A_LUMA_BRIGHT_CNTL, ctrl->val);
		अवरोध;

	हाल V4L2_CID_CONTRAST:
		saa711x_ग_लिखो(sd, R_0B_LUMA_CONTRAST_CNTL, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		saa711x_ग_लिखो(sd, R_0C_CHROMA_SAT_CNTL, ctrl->val);
		अवरोध;

	हाल V4L2_CID_HUE:
		saa711x_ग_लिखो(sd, R_0D_CHROMA_HUE_CNTL, ctrl->val);
		अवरोध;

	हाल V4L2_CID_CHROMA_AGC:
		/* chroma gain cluster */
		अगर (state->agc->val)
			saa711x_ग_लिखो(sd, R_0F_CHROMA_GAIN_CNTL, state->gain->val);
		अन्यथा
			saa711x_ग_लिखो(sd, R_0F_CHROMA_GAIN_CNTL, state->gain->val | 0x80);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_set_size(काष्ठा v4l2_subdev *sd, पूर्णांक width, पूर्णांक height)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	पूर्णांक HPSC, HFSC;
	पूर्णांक VSCY;
	पूर्णांक res;
	पूर्णांक is_50hz = state->std & V4L2_STD_625_50;
	पूर्णांक Vsrc = is_50hz ? 576 : 480;

	v4l2_dbg(1, debug, sd, "decoder set size to %ix%i\n", width, height);

	/* FIXME need better bounds checking here */
	अगर ((width < 1) || (width > 1440))
		वापस -EINVAL;
	अगर ((height < 1) || (height > Vsrc))
		वापस -EINVAL;

	अगर (!saa711x_has_reg(state->ident, R_D0_B_HORIZ_PRESCALING)) अणु
		/* Decoder only supports 720 columns and 480 or 576 lines */
		अगर (width != 720)
			वापस -EINVAL;
		अगर (height != Vsrc)
			वापस -EINVAL;
	पूर्ण

	state->width = width;
	state->height = height;

	अगर (!saa711x_has_reg(state->ident, R_CC_B_HORIZ_OUTPUT_WINDOW_LENGTH))
		वापस 0;

	/* probably have a valid size, let's set it */
	/* Set output width/height */
	/* width */

	saa711x_ग_लिखो(sd, R_CC_B_HORIZ_OUTPUT_WINDOW_LENGTH,
					(u8) (width & 0xff));
	saa711x_ग_लिखो(sd, R_CD_B_HORIZ_OUTPUT_WINDOW_LENGTH_MSB,
					(u8) ((width >> 8) & 0xff));

	/* Vertical Scaling uses height/2 */
	res = height / 2;

	/* On 60Hz, it is using a higher Vertical Output Size */
	अगर (!is_50hz)
		res += (VRES_60HZ - 480) >> 1;

		/* height */
	saa711x_ग_लिखो(sd, R_CE_B_VERT_OUTPUT_WINDOW_LENGTH,
					(u8) (res & 0xff));
	saa711x_ग_लिखो(sd, R_CF_B_VERT_OUTPUT_WINDOW_LENGTH_MSB,
					(u8) ((res >> 8) & 0xff));

	/* Scaling settings */
	/* Hprescaler is न्यूनमान(inres/outres) */
	HPSC = (पूर्णांक)(720 / width);
	/* 0 is not allowed (भाग. by zero) */
	HPSC = HPSC ? HPSC : 1;
	HFSC = (पूर्णांक)((1024 * 720) / (HPSC * width));
	/* FIXME hardcodes to "Task B"
	 * ग_लिखो H prescaler पूर्णांकeger */
	saa711x_ग_लिखो(sd, R_D0_B_HORIZ_PRESCALING,
				(u8) (HPSC & 0x3f));

	v4l2_dbg(1, debug, sd, "Hpsc: 0x%05x, Hfsc: 0x%05x\n", HPSC, HFSC);
	/* ग_लिखो H fine-scaling (luminance) */
	saa711x_ग_लिखो(sd, R_D8_B_HORIZ_LUMA_SCALING_INC,
				(u8) (HFSC & 0xff));
	saa711x_ग_लिखो(sd, R_D9_B_HORIZ_LUMA_SCALING_INC_MSB,
				(u8) ((HFSC >> 8) & 0xff));
	/* ग_लिखो H fine-scaling (chrominance)
	 * must be lum/2, so i'll just bitshअगरt :) */
	saa711x_ग_लिखो(sd, R_DC_B_HORIZ_CHROMA_SCALING,
				(u8) ((HFSC >> 1) & 0xff));
	saa711x_ग_लिखो(sd, R_DD_B_HORIZ_CHROMA_SCALING_MSB,
				(u8) ((HFSC >> 9) & 0xff));

	VSCY = (पूर्णांक)((1024 * Vsrc) / height);
	v4l2_dbg(1, debug, sd, "Vsrc: %d, Vscy: 0x%05x\n", Vsrc, VSCY);

	/* Correct Contrast and Luminance */
	saa711x_ग_लिखो(sd, R_D5_B_LUMA_CONTRAST_CNTL,
					(u8) (64 * 1024 / VSCY));
	saa711x_ग_लिखो(sd, R_D6_B_CHROMA_SATURATION_CNTL,
					(u8) (64 * 1024 / VSCY));

		/* ग_लिखो V fine-scaling (luminance) */
	saa711x_ग_लिखो(sd, R_E0_B_VERT_LUMA_SCALING_INC,
					(u8) (VSCY & 0xff));
	saa711x_ग_लिखो(sd, R_E1_B_VERT_LUMA_SCALING_INC_MSB,
					(u8) ((VSCY >> 8) & 0xff));
		/* ग_लिखो V fine-scaling (chrominance) */
	saa711x_ग_लिखो(sd, R_E2_B_VERT_CHROMA_SCALING_INC,
					(u8) (VSCY & 0xff));
	saa711x_ग_लिखो(sd, R_E3_B_VERT_CHROMA_SCALING_INC_MSB,
					(u8) ((VSCY >> 8) & 0xff));

	saa711x_ग_लिखोregs(sd, saa7115_cfg_reset_scaler);

	/* Activates task "B" */
	saa711x_ग_लिखो(sd, R_80_GLOBAL_CNTL_1,
				saa711x_पढ़ो(sd, R_80_GLOBAL_CNTL_1) | 0x20);

	वापस 0;
पूर्ण

अटल व्योम saa711x_set_v4lstd(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा saa711x_state *state = to_state(sd);

	/* Prevent unnecessary standard changes. During a standard
	   change the I-Port is temporarily disabled. Any devices
	   पढ़ोing from that port can get confused.
	   Note that s_std is also used to चयन from
	   radio to TV mode, so अगर a s_std is broadcast to
	   all I2C devices then you करो not want to have an unwanted
	   side-effect here. */
	अगर (std == state->std)
		वापस;

	state->std = std;

	// This works क्रम NTSC-M, SECAM-L and the 50Hz PAL variants.
	अगर (std & V4L2_STD_525_60) अणु
		v4l2_dbg(1, debug, sd, "decoder set standard 60 Hz\n");
		अगर (state->ident == GM7113C) अणु
			u8 reg = saa711x_पढ़ो(sd, R_08_SYNC_CNTL);
			reg &= ~(SAA7113_R_08_FSEL | SAA7113_R_08_AUFD);
			reg |= SAA7113_R_08_FSEL;
			saa711x_ग_लिखो(sd, R_08_SYNC_CNTL, reg);
		पूर्ण अन्यथा अणु
			saa711x_ग_लिखोregs(sd, saa7115_cfg_60hz_video);
		पूर्ण
		saa711x_set_size(sd, 720, 480);
	पूर्ण अन्यथा अणु
		v4l2_dbg(1, debug, sd, "decoder set standard 50 Hz\n");
		अगर (state->ident == GM7113C) अणु
			u8 reg = saa711x_पढ़ो(sd, R_08_SYNC_CNTL);
			reg &= ~(SAA7113_R_08_FSEL | SAA7113_R_08_AUFD);
			saa711x_ग_लिखो(sd, R_08_SYNC_CNTL, reg);
		पूर्ण अन्यथा अणु
			saa711x_ग_लिखोregs(sd, saa7115_cfg_50hz_video);
		पूर्ण
		saa711x_set_size(sd, 720, 576);
	पूर्ण

	/* Register 0E - Bits D6-D4 on NO-AUTO mode
		(SAA7111 and SAA7113 करोesn't have स्वतः mode)
	    50 Hz / 625 lines           60 Hz / 525 lines
	000 PAL BGDHI (4.43Mhz)         NTSC M (3.58MHz)
	001 NTSC 4.43 (50 Hz)           PAL 4.43 (60 Hz)
	010 Combination-PAL N (3.58MHz) NTSC 4.43 (60 Hz)
	011 NTSC N (3.58MHz)            PAL M (3.58MHz)
	100 reserved                    NTSC-Japan (3.58MHz)
	*/
	अगर (state->ident <= SAA7113 ||
	    state->ident == GM7113C) अणु
		u8 reg = saa711x_पढ़ो(sd, R_0E_CHROMA_CNTL_1) & 0x8f;

		अगर (std == V4L2_STD_PAL_M) अणु
			reg |= 0x30;
		पूर्ण अन्यथा अगर (std == V4L2_STD_PAL_Nc) अणु
			reg |= 0x20;
		पूर्ण अन्यथा अगर (std == V4L2_STD_PAL_60) अणु
			reg |= 0x10;
		पूर्ण अन्यथा अगर (std == V4L2_STD_NTSC_M_JP) अणु
			reg |= 0x40;
		पूर्ण अन्यथा अगर (std & V4L2_STD_SECAM) अणु
			reg |= 0x50;
		पूर्ण
		saa711x_ग_लिखो(sd, R_0E_CHROMA_CNTL_1, reg);
	पूर्ण अन्यथा अणु
		/* restart task B अगर needed */
		पूर्णांक taskb = saa711x_पढ़ो(sd, R_80_GLOBAL_CNTL_1) & 0x10;

		अगर (taskb && state->ident == SAA7114)
			saa711x_ग_लिखोregs(sd, saa7115_cfg_vbi_on);

		/* चयन audio mode too! */
		saa711x_s_घड़ी_freq(sd, state->audclk_freq);
	पूर्ण
पूर्ण

/* setup the sliced VBI lcr रेजिस्टरs according to the sliced VBI क्रमmat */
अटल व्योम saa711x_set_lcr(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *fmt)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	पूर्णांक is_50hz = (state->std & V4L2_STD_625_50);
	u8 lcr[24];
	पूर्णांक i, x;

#अगर 1
	/* saa7113/7114/7118 VBI support are experimental */
	अगर (!saa711x_has_reg(state->ident, R_41_LCR_BASE))
		वापस;

#अन्यथा
	/* SAA7113 and SAA7118 also should support VBI - Need testing */
	अगर (state->ident != SAA7115)
		वापस;
#पूर्ण_अगर

	क्रम (i = 0; i <= 23; i++)
		lcr[i] = 0xff;

	अगर (fmt == शून्य) अणु
		/* raw VBI */
		अगर (is_50hz)
			क्रम (i = 6; i <= 23; i++)
				lcr[i] = 0xdd;
		अन्यथा
			क्रम (i = 10; i <= 21; i++)
				lcr[i] = 0xdd;
	पूर्ण अन्यथा अणु
		/* sliced VBI */
		/* first clear lines that cannot be captured */
		अगर (is_50hz) अणु
			क्रम (i = 0; i <= 5; i++)
				fmt->service_lines[0][i] =
					fmt->service_lines[1][i] = 0;
		पूर्ण
		अन्यथा अणु
			क्रम (i = 0; i <= 9; i++)
				fmt->service_lines[0][i] =
					fmt->service_lines[1][i] = 0;
			क्रम (i = 22; i <= 23; i++)
				fmt->service_lines[0][i] =
					fmt->service_lines[1][i] = 0;
		पूर्ण

		/* Now set the lcr values according to the specअगरied service */
		क्रम (i = 6; i <= 23; i++) अणु
			lcr[i] = 0;
			क्रम (x = 0; x <= 1; x++) अणु
				चयन (fmt->service_lines[1-x][i]) अणु
					हाल 0:
						lcr[i] |= 0xf << (4 * x);
						अवरोध;
					हाल V4L2_SLICED_TELETEXT_B:
						lcr[i] |= 1 << (4 * x);
						अवरोध;
					हाल V4L2_SLICED_CAPTION_525:
						lcr[i] |= 4 << (4 * x);
						अवरोध;
					हाल V4L2_SLICED_WSS_625:
						lcr[i] |= 5 << (4 * x);
						अवरोध;
					हाल V4L2_SLICED_VPS:
						lcr[i] |= 7 << (4 * x);
						अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* ग_लिखो the lcr रेजिस्टरs */
	क्रम (i = 2; i <= 23; i++) अणु
		saa711x_ग_लिखो(sd, i - 2 + R_41_LCR_BASE, lcr[i]);
	पूर्ण

	/* enable/disable raw VBI capturing */
	saa711x_ग_लिखोregs(sd, fmt == शून्य ?
				saa7115_cfg_vbi_on :
				saa7115_cfg_vbi_off);
पूर्ण

अटल पूर्णांक saa711x_g_sliced_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *sliced)
अणु
	अटल u16 lcr2vbi[] = अणु
		0, V4L2_SLICED_TELETEXT_B, 0,	/* 1 */
		0, V4L2_SLICED_CAPTION_525,	/* 4 */
		V4L2_SLICED_WSS_625, 0,		/* 5 */
		V4L2_SLICED_VPS, 0, 0, 0, 0,	/* 7 */
		0, 0, 0, 0
	पूर्ण;
	पूर्णांक i;

	स_रखो(sliced->service_lines, 0, माप(sliced->service_lines));
	sliced->service_set = 0;
	/* करोne अगर using raw VBI */
	अगर (saa711x_पढ़ो(sd, R_80_GLOBAL_CNTL_1) & 0x10)
		वापस 0;
	क्रम (i = 2; i <= 23; i++) अणु
		u8 v = saa711x_पढ़ो(sd, i - 2 + R_41_LCR_BASE);

		sliced->service_lines[0][i] = lcr2vbi[v >> 4];
		sliced->service_lines[1][i] = lcr2vbi[v & 0xf];
		sliced->service_set |=
			sliced->service_lines[0][i] | sliced->service_lines[1][i];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_raw_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_vbi_क्रमmat *fmt)
अणु
	saa711x_set_lcr(sd, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_sliced_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *fmt)
अणु
	saa711x_set_lcr(sd, fmt);
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;

	अगर (क्रमmat->pad || fmt->code != MEDIA_BUS_FMT_FIXED)
		वापस -EINVAL;
	fmt->field = V4L2_FIELD_INTERLACED;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		वापस 0;
	वापस saa711x_set_size(sd, fmt->width, fmt->height);
पूर्ण

/* Decode the sliced VBI data stream as created by the saa7115.
   The क्रमmat is described in the saa7115 datasheet in Tables 25 and 26
   and in Figure 33.
   The current implementation uses SAV/EAV codes and not the ancillary data
   headers. The vbi->p poपूर्णांकer poपूर्णांकs to the R_5E_SDID byte right after the SAV
   code. */
अटल पूर्णांक saa711x_decode_vbi_line(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_decode_vbi_line *vbi)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	अटल स्थिर अक्षर vbi_no_data_pattern[] = अणु
		0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0, 0xa0
	पूर्ण;
	u8 *p = vbi->p;
	u32 wss;
	पूर्णांक id1, id2;   /* the ID1 and ID2 bytes from the पूर्णांकernal header */

	vbi->type = 0;  /* mark result as a failure */
	id1 = p[2];
	id2 = p[3];
	/* Note: the field bit is inverted क्रम 60 Hz video */
	अगर (state->std & V4L2_STD_525_60)
		id1 ^= 0x40;

	/* Skip पूर्णांकernal header, p now poपूर्णांकs to the start of the payload */
	p += 4;
	vbi->p = p;

	/* calculate field and line number of the VBI packet (1-23) */
	vbi->is_second_field = ((id1 & 0x40) != 0);
	vbi->line = (id1 & 0x3f) << 3;
	vbi->line |= (id2 & 0x70) >> 4;

	/* Obtain data type */
	id2 &= 0xf;

	/* If the VBI slicer करोes not detect any संकेत it will fill up
	   the payload buffer with 0xa0 bytes. */
	अगर (!स_भेद(p, vbi_no_data_pattern, माप(vbi_no_data_pattern)))
		वापस 0;

	/* decode payloads */
	चयन (id2) अणु
	हाल 1:
		vbi->type = V4L2_SLICED_TELETEXT_B;
		अवरोध;
	हाल 4:
		अगर (!saa711x_odd_parity(p[0]) || !saa711x_odd_parity(p[1]))
			वापस 0;
		vbi->type = V4L2_SLICED_CAPTION_525;
		अवरोध;
	हाल 5:
		wss = saa711x_decode_wss(p);
		अगर (wss == -1)
			वापस 0;
		p[0] = wss & 0xff;
		p[1] = wss >> 8;
		vbi->type = V4L2_SLICED_WSS_625;
		अवरोध;
	हाल 7:
		अगर (saa711x_decode_vps(p, p) != 0)
			वापस 0;
		vbi->type = V4L2_SLICED_VPS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* ============ SAA7115 AUDIO settings (end) ============= */

अटल पूर्णांक saa711x_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	पूर्णांक status;

	अगर (state->radio)
		वापस 0;
	status = saa711x_पढ़ो(sd, R_1F_STATUS_BYTE_2_VD_DEC);

	v4l2_dbg(1, debug, sd, "status: 0x%02x\n", status);
	vt->संकेत = ((status & (1 << 6)) == 0) ? 0xffff : 0x0;
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा saa711x_state *state = to_state(sd);

	state->radio = 0;
	saa711x_set_v4lstd(sd, std);
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_radio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा saa711x_state *state = to_state(sd);

	state->radio = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_routing(काष्ठा v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	u8 mask = (state->ident <= SAA7111A) ? 0xf8 : 0xf0;

	v4l2_dbg(1, debug, sd, "decoder set input %d output %d\n",
		input, output);

	/* saa7111/3 करोes not have these inमाला_दो */
	अगर ((state->ident <= SAA7113 ||
	     state->ident == GM7113C) &&
	    (input == SAA7115_COMPOSITE4 ||
	     input == SAA7115_COMPOSITE5)) अणु
		वापस -EINVAL;
	पूर्ण
	अगर (input > SAA7115_SVIDEO3)
		वापस -EINVAL;
	अगर (state->input == input && state->output == output)
		वापस 0;
	v4l2_dbg(1, debug, sd, "now setting %s input %s output\n",
		(input >= SAA7115_SVIDEO0) ? "S-Video" : "Composite",
		(output == SAA7115_IPORT_ON) ? "iport on" : "iport off");
	state->input = input;

	/* saa7111 has slightly dअगरferent input numbering */
	अगर (state->ident <= SAA7111A) अणु
		अगर (input >= SAA7115_COMPOSITE4)
			input -= 2;
		/* saa7111 specअगरic */
		saa711x_ग_लिखो(sd, R_10_CHROMA_CNTL_2,
				(saa711x_पढ़ो(sd, R_10_CHROMA_CNTL_2) & 0x3f) |
				((output & 0xc0) ^ 0x40));
		saa711x_ग_लिखो(sd, R_13_RT_X_PORT_OUT_CNTL,
				(saa711x_पढ़ो(sd, R_13_RT_X_PORT_OUT_CNTL) & 0xf0) |
				((output & 2) ? 0x0a : 0));
	पूर्ण

	/* select mode */
	saa711x_ग_लिखो(sd, R_02_INPUT_CNTL_1,
		      (saa711x_पढ़ो(sd, R_02_INPUT_CNTL_1) & mask) |
		       input);

	/* bypass chrominance trap क्रम S-Video modes */
	saa711x_ग_लिखो(sd, R_09_LUMA_CNTL,
			(saa711x_पढ़ो(sd, R_09_LUMA_CNTL) & 0x7f) |
			(state->input >= SAA7115_SVIDEO0 ? 0x80 : 0x0));

	state->output = output;
	अगर (state->ident == SAA7114 ||
			state->ident == SAA7115) अणु
		saa711x_ग_लिखो(sd, R_83_X_PORT_I_O_ENA_AND_OUT_CLK,
				(saa711x_पढ़ो(sd, R_83_X_PORT_I_O_ENA_AND_OUT_CLK) & 0xfe) |
				(state->output & 0x01));
	पूर्ण
	अगर (state->ident > SAA7111A) अणु
		अगर (config & SAA7115_IDQ_IS_DEFAULT)
			saa711x_ग_लिखो(sd, R_85_I_PORT_SIGNAL_POLAR, 0x20);
		अन्यथा
			saa711x_ग_लिखो(sd, R_85_I_PORT_SIGNAL_POLAR, 0x21);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_gpio(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	काष्ठा saa711x_state *state = to_state(sd);

	अगर (state->ident > SAA7111A)
		वापस -EINVAL;
	saa711x_ग_लिखो(sd, 0x11, (saa711x_पढ़ो(sd, 0x11) & 0x7f) |
		(val ? 0x80 : 0));
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा saa711x_state *state = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s output\n",
			enable ? "enable" : "disable");

	अगर (state->enable == enable)
		वापस 0;
	state->enable = enable;
	अगर (!saa711x_has_reg(state->ident, R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED))
		वापस 0;
	saa711x_ग_लिखो(sd, R_87_I_PORT_I_O_ENA_OUT_CLK_AND_GATED, state->enable);
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_crystal_freq(काष्ठा v4l2_subdev *sd, u32 freq, u32 flags)
अणु
	काष्ठा saa711x_state *state = to_state(sd);

	अगर (freq != SAA7115_FREQ_32_11_MHZ && freq != SAA7115_FREQ_24_576_MHZ)
		वापस -EINVAL;
	state->crystal_freq = freq;
	state->द्विगुन_asclk = flags & SAA7115_FREQ_FL_DOUBLE_ASCLK;
	state->cgcभाग = (flags & SAA7115_FREQ_FL_CGCDIV) ? 3 : 4;
	state->ucgc = flags & SAA7115_FREQ_FL_UCGC;
	state->apll = flags & SAA7115_FREQ_FL_APLL;
	saa711x_s_घड़ी_freq(sd, state->audclk_freq);
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_reset(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	v4l2_dbg(1, debug, sd, "decoder RESET\n");
	saa711x_ग_लिखोregs(sd, saa7115_cfg_reset_scaler);
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_g_vbi_data(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_data *data)
अणु
	/* Note: the पूर्णांकernal field ID is inverted क्रम NTSC,
	   so data->field 0 maps to the saa7115 even field,
	   whereas क्रम PAL it maps to the saa7115 odd field. */
	चयन (data->id) अणु
	हाल V4L2_SLICED_WSS_625:
		अगर (saa711x_पढ़ो(sd, 0x6b) & 0xc0)
			वापस -EIO;
		data->data[0] = saa711x_पढ़ो(sd, 0x6c);
		data->data[1] = saa711x_पढ़ो(sd, 0x6d);
		वापस 0;
	हाल V4L2_SLICED_CAPTION_525:
		अगर (data->field == 0) अणु
			/* CC */
			अगर (saa711x_पढ़ो(sd, 0x66) & 0x30)
				वापस -EIO;
			data->data[0] = saa711x_पढ़ो(sd, 0x69);
			data->data[1] = saa711x_पढ़ो(sd, 0x6a);
			वापस 0;
		पूर्ण
		/* XDS */
		अगर (saa711x_पढ़ो(sd, 0x66) & 0xc0)
			वापस -EIO;
		data->data[0] = saa711x_पढ़ो(sd, 0x67);
		data->data[1] = saa711x_पढ़ो(sd, 0x68);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक saa711x_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	पूर्णांक reg1f, reg1e;

	/*
	 * The V4L2 core alपढ़ोy initializes std with all supported
	 * Standards. All driver needs to करो is to mask it, to हटाओ
	 * standards that करोn't apply from the mask
	 */

	reg1f = saa711x_पढ़ो(sd, R_1F_STATUS_BYTE_2_VD_DEC);

	अगर (state->ident == SAA7115) अणु
		reg1e = saa711x_पढ़ो(sd, R_1E_STATUS_BYTE_1_VD_DEC);

		v4l2_dbg(1, debug, sd, "Status byte 1 (0x1e)=0x%02x\n", reg1e);

		चयन (reg1e & 0x03) अणु
		हाल 1:
			*std &= V4L2_STD_NTSC;
			अवरोध;
		हाल 2:
			/*
			 * V4L2_STD_PAL just cover the european PAL standards.
			 * This is wrong, as the device could also be using an
			 * other PAL standard.
			 */
			*std &= V4L2_STD_PAL   | V4L2_STD_PAL_N  | V4L2_STD_PAL_Nc |
				V4L2_STD_PAL_M | V4L2_STD_PAL_60;
			अवरोध;
		हाल 3:
			*std &= V4L2_STD_SECAM;
			अवरोध;
		शेष:
			*std = V4L2_STD_UNKNOWN;
			/* Can't detect anything */
			अवरोध;
		पूर्ण
	पूर्ण

	v4l2_dbg(1, debug, sd, "Status byte 2 (0x1f)=0x%02x\n", reg1f);

	/* horizontal/vertical not locked */
	अगर (reg1f & 0x40) अणु
		*std = V4L2_STD_UNKNOWN;
		जाओ ret;
	पूर्ण

	अगर (reg1f & 0x20)
		*std &= V4L2_STD_525_60;
	अन्यथा
		*std &= V4L2_STD_625_50;

ret:
	v4l2_dbg(1, debug, sd, "detected std mask = %08Lx\n", *std);

	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	पूर्णांक reg1e = 0x80;
	पूर्णांक reg1f;

	*status = V4L2_IN_ST_NO_SIGNAL;
	अगर (state->ident == SAA7115)
		reg1e = saa711x_पढ़ो(sd, R_1E_STATUS_BYTE_1_VD_DEC);
	reg1f = saa711x_पढ़ो(sd, R_1F_STATUS_BYTE_2_VD_DEC);
	अगर ((reg1f & 0xc1) == 0x81 && (reg1e & 0xc0) == 0x80)
		*status = 0;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक saa711x_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	reg->val = saa711x_पढ़ो(sd, reg->reg & 0xff);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक saa711x_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	saa711x_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक saa711x_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा saa711x_state *state = to_state(sd);
	पूर्णांक reg1e, reg1f;
	पूर्णांक संकेतOk;
	पूर्णांक vcr;

	v4l2_info(sd, "Audio frequency: %d Hz\n", state->audclk_freq);
	अगर (state->ident != SAA7115) अणु
		/* status क्रम the saa7114 */
		reg1f = saa711x_पढ़ो(sd, R_1F_STATUS_BYTE_2_VD_DEC);
		संकेतOk = (reg1f & 0xc1) == 0x81;
		v4l2_info(sd, "Video signal:    %s\n", संकेतOk ? "ok" : "bad");
		v4l2_info(sd, "Frequency:       %s\n", (reg1f & 0x20) ? "60 Hz" : "50 Hz");
		वापस 0;
	पूर्ण

	/* status क्रम the saa7115 */
	reg1e = saa711x_पढ़ो(sd, R_1E_STATUS_BYTE_1_VD_DEC);
	reg1f = saa711x_पढ़ो(sd, R_1F_STATUS_BYTE_2_VD_DEC);

	संकेतOk = (reg1f & 0xc1) == 0x81 && (reg1e & 0xc0) == 0x80;
	vcr = !(reg1f & 0x10);

	अगर (state->input >= 6)
		v4l2_info(sd, "Input:           S-Video %d\n", state->input - 6);
	अन्यथा
		v4l2_info(sd, "Input:           Composite %d\n", state->input);
	v4l2_info(sd, "Video signal:    %s\n", संकेतOk ? (vcr ? "VCR" : "broadcast/DVD") : "bad");
	v4l2_info(sd, "Frequency:       %s\n", (reg1f & 0x20) ? "60 Hz" : "50 Hz");

	चयन (reg1e & 0x03) अणु
	हाल 1:
		v4l2_info(sd, "Detected format: NTSC\n");
		अवरोध;
	हाल 2:
		v4l2_info(sd, "Detected format: PAL\n");
		अवरोध;
	हाल 3:
		v4l2_info(sd, "Detected format: SECAM\n");
		अवरोध;
	शेष:
		v4l2_info(sd, "Detected format: BW/No color\n");
		अवरोध;
	पूर्ण
	v4l2_info(sd, "Width, Height:   %d, %d\n", state->width, state->height);
	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops saa711x_ctrl_ops = अणु
	.s_ctrl = saa711x_s_ctrl,
	.g_अस्थिर_ctrl = saa711x_g_अस्थिर_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops saa711x_core_ops = अणु
	.log_status = saa711x_log_status,
	.reset = saa711x_reset,
	.s_gpio = saa711x_s_gpio,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = saa711x_g_रेजिस्टर,
	.s_रेजिस्टर = saa711x_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops saa711x_tuner_ops = अणु
	.s_radio = saa711x_s_radio,
	.g_tuner = saa711x_g_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops saa711x_audio_ops = अणु
	.s_घड़ी_freq = saa711x_s_घड़ी_freq,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops saa711x_video_ops = अणु
	.s_std = saa711x_s_std,
	.s_routing = saa711x_s_routing,
	.s_crystal_freq = saa711x_s_crystal_freq,
	.s_stream = saa711x_s_stream,
	.querystd = saa711x_querystd,
	.g_input_status = saa711x_g_input_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_vbi_ops saa711x_vbi_ops = अणु
	.g_vbi_data = saa711x_g_vbi_data,
	.decode_vbi_line = saa711x_decode_vbi_line,
	.g_sliced_fmt = saa711x_g_sliced_fmt,
	.s_sliced_fmt = saa711x_s_sliced_fmt,
	.s_raw_fmt = saa711x_s_raw_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops saa711x_pad_ops = अणु
	.set_fmt = saa711x_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops saa711x_ops = अणु
	.core = &saa711x_core_ops,
	.tuner = &saa711x_tuner_ops,
	.audio = &saa711x_audio_ops,
	.video = &saa711x_video_ops,
	.vbi = &saa711x_vbi_ops,
	.pad = &saa711x_pad_ops,
पूर्ण;

#घोषणा CHIP_VER_SIZE	16

/* ----------------------------------------------------------------------- */

अटल व्योम saa711x_ग_लिखो_platक्रमm_data(काष्ठा saa711x_state *state,
					काष्ठा saa7115_platक्रमm_data *data)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 work;

	अगर (state->ident != GM7113C &&
	    state->ident != SAA7113)
		वापस;

	अगर (data->saa7113_r08_htc) अणु
		work = saa711x_पढ़ो(sd, R_08_SYNC_CNTL);
		work &= ~SAA7113_R_08_HTC_MASK;
		work |= ((*data->saa7113_r08_htc) << SAA7113_R_08_HTC_OFFSET);
		saa711x_ग_लिखो(sd, R_08_SYNC_CNTL, work);
	पूर्ण

	अगर (data->saa7113_r10_vrln) अणु
		work = saa711x_पढ़ो(sd, R_10_CHROMA_CNTL_2);
		work &= ~SAA7113_R_10_VRLN_MASK;
		अगर (*data->saa7113_r10_vrln)
			work |= (1 << SAA7113_R_10_VRLN_OFFSET);
		saa711x_ग_लिखो(sd, R_10_CHROMA_CNTL_2, work);
	पूर्ण

	अगर (data->saa7113_r10_ofts) अणु
		work = saa711x_पढ़ो(sd, R_10_CHROMA_CNTL_2);
		work &= ~SAA7113_R_10_OFTS_MASK;
		work |= (*data->saa7113_r10_ofts << SAA7113_R_10_OFTS_OFFSET);
		saa711x_ग_लिखो(sd, R_10_CHROMA_CNTL_2, work);
	पूर्ण

	अगर (data->saa7113_r12_rts0) अणु
		work = saa711x_पढ़ो(sd, R_12_RT_SIGNAL_CNTL);
		work &= ~SAA7113_R_12_RTS0_MASK;
		work |= (*data->saa7113_r12_rts0 << SAA7113_R_12_RTS0_OFFSET);

		/* According to the datasheet,
		 * SAA7113_RTS_DOT_IN should only be used on RTS1 */
		WARN_ON(*data->saa7113_r12_rts0 == SAA7113_RTS_DOT_IN);
		saa711x_ग_लिखो(sd, R_12_RT_SIGNAL_CNTL, work);
	पूर्ण

	अगर (data->saa7113_r12_rts1) अणु
		work = saa711x_पढ़ो(sd, R_12_RT_SIGNAL_CNTL);
		work &= ~SAA7113_R_12_RTS1_MASK;
		work |= (*data->saa7113_r12_rts1 << SAA7113_R_12_RTS1_OFFSET);
		saa711x_ग_लिखो(sd, R_12_RT_SIGNAL_CNTL, work);
	पूर्ण

	अगर (data->saa7113_r13_adlsb) अणु
		work = saa711x_पढ़ो(sd, R_13_RT_X_PORT_OUT_CNTL);
		work &= ~SAA7113_R_13_ADLSB_MASK;
		अगर (*data->saa7113_r13_adlsb)
			work |= (1 << SAA7113_R_13_ADLSB_OFFSET);
		saa711x_ग_लिखो(sd, R_13_RT_X_PORT_OUT_CNTL, work);
	पूर्ण
पूर्ण

/**
 * saa711x_detect_chip - Detects the saa711x (or clone) variant
 * @client:		I2C client काष्ठाure.
 * @id:			I2C device ID काष्ठाure.
 * @name:		Name of the device to be filled.
 *
 * Detects the Philips/NXP saa711x chip, or some clone of it.
 * अगर 'id' is शून्य or id->driver_data is equal to 1, it स्वतः-probes
 * the analog demod.
 * If the tuner is not found, it वापसs -ENODEV.
 * If स्वतः-detection is disabled and the tuner करोesn't match what it was
 *	required, it वापसs -EINVAL and fills 'name'.
 * If the chip is found, it वापसs the chip ID and fills 'name'.
 */
अटल पूर्णांक saa711x_detect_chip(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *id,
			       अक्षर *name)
अणु
	अक्षर chip_ver[CHIP_VER_SIZE];
	अक्षर chip_id;
	पूर्णांक i;
	पूर्णांक स्वतःdetect;

	स्वतःdetect = !id || id->driver_data == 1;

	/* Read the chip version रेजिस्टर */
	क्रम (i = 0; i < CHIP_VER_SIZE; i++) अणु
		i2c_smbus_ग_लिखो_byte_data(client, 0, i);
		chip_ver[i] = i2c_smbus_पढ़ो_byte_data(client, 0);
		name[i] = (chip_ver[i] & 0x0f) + '0';
		अगर (name[i] > '9')
			name[i] += 'a' - '9' - 1;
	पूर्ण
	name[i] = '\0';

	/* Check अगर it is a Philips/NXP chip */
	अगर (!स_भेद(name + 1, "f711", 4)) अणु
		chip_id = name[5];
		snम_लिखो(name, CHIP_VER_SIZE, "saa711%c", chip_id);

		अगर (!स्वतःdetect && म_भेद(name, id->name))
			वापस -EINVAL;

		चयन (chip_id) अणु
		हाल '1':
			अगर (chip_ver[0] & 0xf0) अणु
				snम_लिखो(name, CHIP_VER_SIZE, "saa711%ca", chip_id);
				v4l_info(client, "saa7111a variant found\n");
				वापस SAA7111A;
			पूर्ण
			वापस SAA7111;
		हाल '3':
			वापस SAA7113;
		हाल '4':
			वापस SAA7114;
		हाल '5':
			वापस SAA7115;
		हाल '8':
			वापस SAA7118;
		शेष:
			v4l2_info(client,
				  "WARNING: Philips/NXP chip unknown - Falling back to saa7111\n");
			वापस SAA7111;
		पूर्ण
	पूर्ण

	/* Check अगर it is a gm7113c */
	अगर (!स_भेद(name, "0000", 4)) अणु
		chip_id = 0;
		क्रम (i = 0; i < 4; i++) अणु
			chip_id = chip_id << 1;
			chip_id |= (chip_ver[i] & 0x80) ? 1 : 0;
		पूर्ण

		/*
		 * Note: From the datasheet, only versions 1 and 2
		 * exists. However, tests on a device labeled as:
		 * "GM7113C 1145" वापसed "10" on all 16 chip
		 * version (reg 0x00) पढ़ोs. So, we need to also
		 * accept at least version 0. For now, let's just
		 * assume that a device that वापसs "0000" क्रम
		 * the lower nibble is a gm7113c.
		 */

		strscpy(name, "gm7113c", CHIP_VER_SIZE);

		अगर (!स्वतःdetect && म_भेद(name, id->name))
			वापस -EINVAL;

		v4l_dbg(1, debug, client,
			"It seems to be a %s chip (%*ph) @ 0x%x.\n",
			name, 16, chip_ver, client->addr << 1);

		वापस GM7113C;
	पूर्ण

	/* Check अगर it is a CJC7113 */
	अगर (!स_भेद(name, "1111111111111111", CHIP_VER_SIZE)) अणु
		strscpy(name, "cjc7113", CHIP_VER_SIZE);

		अगर (!स्वतःdetect && म_भेद(name, id->name))
			वापस -EINVAL;

		v4l_dbg(1, debug, client,
			"It seems to be a %s chip (%*ph) @ 0x%x.\n",
			name, 16, chip_ver, client->addr << 1);

		/* CJC7113 seems to be SAA7113-compatible */
		वापस SAA7113;
	पूर्ण

	/* Chip was not discovered. Return its ID and करोn't bind */
	v4l_dbg(1, debug, client, "chip %*ph @ 0x%x is unknown.\n",
		16, chip_ver, client->addr << 1);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक saa711x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा saa711x_state *state;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा saa7115_platक्रमm_data *pdata;
	पूर्णांक ident;
	अक्षर name[CHIP_VER_SIZE + 1];
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	पूर्णांक ret;
#पूर्ण_अगर

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	ident = saa711x_detect_chip(client, id, name);
	अगर (ident == -EINVAL) अणु
		/* Chip exists, but करोesn't match */
		v4l_warn(client, "found %s while %s was expected\n",
			 name, id->name);
		वापस -ENODEV;
	पूर्ण
	अगर (ident < 0)
		वापस ident;

	strscpy(client->name, name, माप(client->name));

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस -ENOMEM;
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &saa711x_ops);

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	state->pads[SAA711X_PAD_IF_INPUT].flags = MEDIA_PAD_FL_SINK;
	state->pads[SAA711X_PAD_IF_INPUT].sig_type = PAD_SIGNAL_ANALOG;
	state->pads[SAA711X_PAD_VID_OUT].flags = MEDIA_PAD_FL_SOURCE;
	state->pads[SAA711X_PAD_VID_OUT].sig_type = PAD_SIGNAL_DV;

	sd->entity.function = MEDIA_ENT_F_ATV_DECODER;

	ret = media_entity_pads_init(&sd->entity, SAA711X_NUM_PADS,
				     state->pads);
	अगर (ret < 0)
		वापस ret;
#पूर्ण_अगर

	v4l_info(client, "%s found @ 0x%x (%s)\n", name,
		 client->addr << 1, client->adapter->name);
	hdl = &state->hdl;
	v4l2_ctrl_handler_init(hdl, 6);
	/* add in ascending ID order */
	v4l2_ctrl_new_std(hdl, &saa711x_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &saa711x_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 127, 1, 64);
	v4l2_ctrl_new_std(hdl, &saa711x_ctrl_ops,
			V4L2_CID_SATURATION, 0, 127, 1, 64);
	v4l2_ctrl_new_std(hdl, &saa711x_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	state->agc = v4l2_ctrl_new_std(hdl, &saa711x_ctrl_ops,
			V4L2_CID_CHROMA_AGC, 0, 1, 1, 1);
	state->gain = v4l2_ctrl_new_std(hdl, &saa711x_ctrl_ops,
			V4L2_CID_CHROMA_GAIN, 0, 127, 1, 40);
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		पूर्णांक err = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_स्वतः_cluster(2, &state->agc, 0, true);

	state->input = -1;
	state->output = SAA7115_IPORT_ON;
	state->enable = 1;
	state->radio = 0;
	state->ident = ident;

	state->audclk_freq = 48000;

	v4l2_dbg(1, debug, sd, "writing init values\n");

	/* init to 60hz/48khz */
	state->crystal_freq = SAA7115_FREQ_24_576_MHZ;
	pdata = client->dev.platक्रमm_data;
	चयन (state->ident) अणु
	हाल SAA7111:
	हाल SAA7111A:
		saa711x_ग_लिखोregs(sd, saa7111_init);
		अवरोध;
	हाल GM7113C:
		saa711x_ग_लिखोregs(sd, gm7113c_init);
		अवरोध;
	हाल SAA7113:
		अगर (pdata && pdata->saa7113_क्रमce_gm7113c_init)
			saa711x_ग_लिखोregs(sd, gm7113c_init);
		अन्यथा
			saa711x_ग_लिखोregs(sd, saa7113_init);
		अवरोध;
	शेष:
		state->crystal_freq = SAA7115_FREQ_32_11_MHZ;
		saa711x_ग_लिखोregs(sd, saa7115_init_स्वतः_input);
	पूर्ण
	अगर (state->ident > SAA7111A && state->ident != GM7113C)
		saa711x_ग_लिखोregs(sd, saa7115_init_misc);

	अगर (pdata)
		saa711x_ग_लिखो_platक्रमm_data(state, pdata);

	saa711x_set_v4lstd(sd, V4L2_STD_NTSC);
	v4l2_ctrl_handler_setup(hdl);

	v4l2_dbg(1, debug, sd, "status: (1E) 0x%02x, (1F) 0x%02x\n",
		saa711x_पढ़ो(sd, R_1E_STATUS_BYTE_1_VD_DEC),
		saa711x_पढ़ो(sd, R_1F_STATUS_BYTE_2_VD_DEC));
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक saa711x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id saa711x_id[] = अणु
	अणु "saa7115_auto", 1 पूर्ण, /* स्वतःdetect */
	अणु "saa7111", 0 पूर्ण,
	अणु "saa7113", 0 पूर्ण,
	अणु "saa7114", 0 पूर्ण,
	अणु "saa7115", 0 पूर्ण,
	अणु "saa7118", 0 पूर्ण,
	अणु "gm7113c", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, saa711x_id);

अटल काष्ठा i2c_driver saa711x_driver = अणु
	.driver = अणु
		.name	= "saa7115",
	पूर्ण,
	.probe		= saa711x_probe,
	.हटाओ		= saa711x_हटाओ,
	.id_table	= saa711x_id,
पूर्ण;

module_i2c_driver(saa711x_driver);
