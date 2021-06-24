<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Video Capture Driver (Video क्रम Linux 1/2)
 * क्रम the Matrox Marvel G200,G400 and Rainbow Runner-G series
 *
 * This module is an पूर्णांकerface to the KS0127 video decoder chip.
 *
 * Copyright (C) 1999  Ryan Drake <stiletto@mediaone.net>
 *
 *****************************************************************************
 *
 * Modअगरied and extended by
 *	Mike Bernson <mike@mlb.org>
 *	Gerard v.d. Horst
 *	Leon van Stuivenberg <l.vanstuivenberg@chello.nl>
 *	Gernot Ziegler <gz@lysator.liu.se>
 *
 * Version History:
 * V1.0 Ryan Drake	   Initial version by Ryan Drake
 * V1.1 Gerard v.d. Horst  Added some debugoutput, reset the video-standard
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/slab.h>
#समावेश <media/v4l2-device.h>
#समावेश "ks0127.h"

MODULE_DESCRIPTION("KS0127 video decoder driver");
MODULE_AUTHOR("Ryan Drake");
MODULE_LICENSE("GPL");

/* Addresses */
#घोषणा I2C_KS0127_ADDON   0xD8
#घोषणा I2C_KS0127_ONBOARD 0xDA


/* ks0127 control रेजिस्टरs */
#घोषणा KS_STAT     0x00
#घोषणा KS_CMDA     0x01
#घोषणा KS_CMDB     0x02
#घोषणा KS_CMDC     0x03
#घोषणा KS_CMDD     0x04
#घोषणा KS_HAVB     0x05
#घोषणा KS_HAVE     0x06
#घोषणा KS_HS1B     0x07
#घोषणा KS_HS1E     0x08
#घोषणा KS_HS2B     0x09
#घोषणा KS_HS2E     0x0a
#घोषणा KS_AGC      0x0b
#घोषणा KS_HXTRA    0x0c
#घोषणा KS_CDEM     0x0d
#घोषणा KS_PORTAB   0x0e
#घोषणा KS_LUMA     0x0f
#घोषणा KS_CON      0x10
#घोषणा KS_BRT      0x11
#घोषणा KS_CHROMA   0x12
#घोषणा KS_CHROMB   0x13
#घोषणा KS_DEMOD    0x14
#घोषणा KS_SAT      0x15
#घोषणा KS_HUE      0x16
#घोषणा KS_VERTIA   0x17
#घोषणा KS_VERTIB   0x18
#घोषणा KS_VERTIC   0x19
#घोषणा KS_HSCLL    0x1a
#घोषणा KS_HSCLH    0x1b
#घोषणा KS_VSCLL    0x1c
#घोषणा KS_VSCLH    0x1d
#घोषणा KS_OFMTA    0x1e
#घोषणा KS_OFMTB    0x1f
#घोषणा KS_VBICTL   0x20
#घोषणा KS_CCDAT2   0x21
#घोषणा KS_CCDAT1   0x22
#घोषणा KS_VBIL30   0x23
#घोषणा KS_VBIL74   0x24
#घोषणा KS_VBIL118  0x25
#घोषणा KS_VBIL1512 0x26
#घोषणा KS_TTFRAM   0x27
#घोषणा KS_TESTA    0x28
#घोषणा KS_UVOFFH   0x29
#घोषणा KS_UVOFFL   0x2a
#घोषणा KS_UGAIN    0x2b
#घोषणा KS_VGAIN    0x2c
#घोषणा KS_VAVB     0x2d
#घोषणा KS_VAVE     0x2e
#घोषणा KS_CTRACK   0x2f
#घोषणा KS_POLCTL   0x30
#घोषणा KS_REFCOD   0x31
#घोषणा KS_INVALY   0x32
#घोषणा KS_INVALU   0x33
#घोषणा KS_INVALV   0x34
#घोषणा KS_UNUSEY   0x35
#घोषणा KS_UNUSEU   0x36
#घोषणा KS_UNUSEV   0x37
#घोषणा KS_USRSAV   0x38
#घोषणा KS_USREAV   0x39
#घोषणा KS_SHS1A    0x3a
#घोषणा KS_SHS1B    0x3b
#घोषणा KS_SHS1C    0x3c
#घोषणा KS_CMDE     0x3d
#घोषणा KS_VSDEL    0x3e
#घोषणा KS_CMDF     0x3f
#घोषणा KS_GAMMA0   0x40
#घोषणा KS_GAMMA1   0x41
#घोषणा KS_GAMMA2   0x42
#घोषणा KS_GAMMA3   0x43
#घोषणा KS_GAMMA4   0x44
#घोषणा KS_GAMMA5   0x45
#घोषणा KS_GAMMA6   0x46
#घोषणा KS_GAMMA7   0x47
#घोषणा KS_GAMMA8   0x48
#घोषणा KS_GAMMA9   0x49
#घोषणा KS_GAMMA10  0x4a
#घोषणा KS_GAMMA11  0x4b
#घोषणा KS_GAMMA12  0x4c
#घोषणा KS_GAMMA13  0x4d
#घोषणा KS_GAMMA14  0x4e
#घोषणा KS_GAMMA15  0x4f
#घोषणा KS_GAMMA16  0x50
#घोषणा KS_GAMMA17  0x51
#घोषणा KS_GAMMA18  0x52
#घोषणा KS_GAMMA19  0x53
#घोषणा KS_GAMMA20  0x54
#घोषणा KS_GAMMA21  0x55
#घोषणा KS_GAMMA22  0x56
#घोषणा KS_GAMMA23  0x57
#घोषणा KS_GAMMA24  0x58
#घोषणा KS_GAMMA25  0x59
#घोषणा KS_GAMMA26  0x5a
#घोषणा KS_GAMMA27  0x5b
#घोषणा KS_GAMMA28  0x5c
#घोषणा KS_GAMMA29  0x5d
#घोषणा KS_GAMMA30  0x5e
#घोषणा KS_GAMMA31  0x5f
#घोषणा KS_GAMMAD0  0x60
#घोषणा KS_GAMMAD1  0x61
#घोषणा KS_GAMMAD2  0x62
#घोषणा KS_GAMMAD3  0x63
#घोषणा KS_GAMMAD4  0x64
#घोषणा KS_GAMMAD5  0x65
#घोषणा KS_GAMMAD6  0x66
#घोषणा KS_GAMMAD7  0x67
#घोषणा KS_GAMMAD8  0x68
#घोषणा KS_GAMMAD9  0x69
#घोषणा KS_GAMMAD10 0x6a
#घोषणा KS_GAMMAD11 0x6b
#घोषणा KS_GAMMAD12 0x6c
#घोषणा KS_GAMMAD13 0x6d
#घोषणा KS_GAMMAD14 0x6e
#घोषणा KS_GAMMAD15 0x6f
#घोषणा KS_GAMMAD16 0x70
#घोषणा KS_GAMMAD17 0x71
#घोषणा KS_GAMMAD18 0x72
#घोषणा KS_GAMMAD19 0x73
#घोषणा KS_GAMMAD20 0x74
#घोषणा KS_GAMMAD21 0x75
#घोषणा KS_GAMMAD22 0x76
#घोषणा KS_GAMMAD23 0x77
#घोषणा KS_GAMMAD24 0x78
#घोषणा KS_GAMMAD25 0x79
#घोषणा KS_GAMMAD26 0x7a
#घोषणा KS_GAMMAD27 0x7b
#घोषणा KS_GAMMAD28 0x7c
#घोषणा KS_GAMMAD29 0x7d
#घोषणा KS_GAMMAD30 0x7e
#घोषणा KS_GAMMAD31 0x7f


/****************************************************************************
* mga_dev : represents one ks0127 chip.
****************************************************************************/

काष्ठा adjust अणु
	पूर्णांक	contrast;
	पूर्णांक	bright;
	पूर्णांक	hue;
	पूर्णांक	ugain;
	पूर्णांक	vgain;
पूर्ण;

काष्ठा ks0127 अणु
	काष्ठा v4l2_subdev sd;
	v4l2_std_id	norm;
	u8		regs[256];
पूर्ण;

अटल अंतरभूत काष्ठा ks0127 *to_ks0127(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ks0127, sd);
पूर्ण


अटल पूर्णांक debug; /* insmod parameter */

module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug output");

अटल u8 reg_शेषs[64];

अटल व्योम init_reg_शेषs(व्योम)
अणु
	अटल पूर्णांक initialized;
	u8 *table = reg_शेषs;

	अगर (initialized)
		वापस;
	initialized = 1;

	table[KS_CMDA]     = 0x2c;  /* VSE=0, CCIR 601, स्वतःdetect standard */
	table[KS_CMDB]     = 0x12;  /* VALIGN=0, AGC control and input */
	table[KS_CMDC]     = 0x00;  /* Test options */
	/* घड़ी & input select, ग_लिखो 1 to PORTA */
	table[KS_CMDD]     = 0x01;
	table[KS_HAVB]     = 0x00;  /* HAV Start Control */
	table[KS_HAVE]     = 0x00;  /* HAV End Control */
	table[KS_HS1B]     = 0x10;  /* HS1 Start Control */
	table[KS_HS1E]     = 0x00;  /* HS1 End Control */
	table[KS_HS2B]     = 0x00;  /* HS2 Start Control */
	table[KS_HS2E]     = 0x00;  /* HS2 End Control */
	table[KS_AGC]      = 0x53;  /* Manual setting क्रम AGC */
	table[KS_HXTRA]    = 0x00;  /* Extra Bits क्रम HAV and HS1/2 */
	table[KS_CDEM]     = 0x00;  /* Chroma Demodulation Control */
	table[KS_PORTAB]   = 0x0f;  /* port B is input, port A output GPPORT */
	table[KS_LUMA]     = 0x01;  /* Luma control */
	table[KS_CON]      = 0x00;  /* Contrast Control */
	table[KS_BRT]      = 0x00;  /* Brightness Control */
	table[KS_CHROMA]   = 0x2a;  /* Chroma control A */
	table[KS_CHROMB]   = 0x90;  /* Chroma control B */
	table[KS_DEMOD]    = 0x00;  /* Chroma Demodulation Control & Status */
	table[KS_SAT]      = 0x00;  /* Color Saturation Control*/
	table[KS_HUE]      = 0x00;  /* Hue Control */
	table[KS_VERTIA]   = 0x00;  /* Vertical Processing Control A */
	/* Vertical Processing Control B, luma 1 line delayed */
	table[KS_VERTIB]   = 0x12;
	table[KS_VERTIC]   = 0x0b;  /* Vertical Processing Control C */
	table[KS_HSCLL]    = 0x00;  /* Horizontal Scaling Ratio Low */
	table[KS_HSCLH]    = 0x00;  /* Horizontal Scaling Ratio High */
	table[KS_VSCLL]    = 0x00;  /* Vertical Scaling Ratio Low */
	table[KS_VSCLH]    = 0x00;  /* Vertical Scaling Ratio High */
	/* 16 bit YCbCr 4:2:2 output; I can't make the bt866 like 8 bit /Sam */
	table[KS_OFMTA]    = 0x30;
	table[KS_OFMTB]    = 0x00;  /* Output Control B */
	/* VBI Decoder Control; 4bit fmt: aव्योम Y overflow */
	table[KS_VBICTL]   = 0x5d;
	table[KS_CCDAT2]   = 0x00;  /* Read Only रेजिस्टर */
	table[KS_CCDAT1]   = 0x00;  /* Read Only रेजिस्टर */
	table[KS_VBIL30]   = 0xa8;  /* VBI data decoding options */
	table[KS_VBIL74]   = 0xaa;  /* VBI data decoding options */
	table[KS_VBIL118]  = 0x2a;  /* VBI data decoding options */
	table[KS_VBIL1512] = 0x00;  /* VBI data decoding options */
	table[KS_TTFRAM]   = 0x00;  /* Teletext frame alignment pattern */
	table[KS_TESTA]    = 0x00;  /* test रेजिस्टर, shouldn't be written */
	table[KS_UVOFFH]   = 0x00;  /* UV Offset Adjusपंचांगent High */
	table[KS_UVOFFL]   = 0x00;  /* UV Offset Adjusपंचांगent Low */
	table[KS_UGAIN]    = 0x00;  /* U Component Gain Adjusपंचांगent */
	table[KS_VGAIN]    = 0x00;  /* V Component Gain Adjusपंचांगent */
	table[KS_VAVB]     = 0x07;  /* VAV Begin */
	table[KS_VAVE]     = 0x00;  /* VAV End */
	table[KS_CTRACK]   = 0x00;  /* Chroma Tracking Control */
	table[KS_POLCTL]   = 0x41;  /* Timing Signal Polarity Control */
	table[KS_REFCOD]   = 0x80;  /* Reference Code Insertion Control */
	table[KS_INVALY]   = 0x10;  /* Invalid Y Code */
	table[KS_INVALU]   = 0x80;  /* Invalid U Code */
	table[KS_INVALV]   = 0x80;  /* Invalid V Code */
	table[KS_UNUSEY]   = 0x10;  /* Unused Y Code */
	table[KS_UNUSEU]   = 0x80;  /* Unused U Code */
	table[KS_UNUSEV]   = 0x80;  /* Unused V Code */
	table[KS_USRSAV]   = 0x00;  /* reserved */
	table[KS_USREAV]   = 0x00;  /* reserved */
	table[KS_SHS1A]    = 0x00;  /* User Defined SHS1 A */
	/* User Defined SHS1 B, ALT656=1 on 0127B */
	table[KS_SHS1B]    = 0x80;
	table[KS_SHS1C]    = 0x00;  /* User Defined SHS1 C */
	table[KS_CMDE]     = 0x00;  /* Command Register E */
	table[KS_VSDEL]    = 0x00;  /* VS Delay Control */
	/* Command Register F, update -immediately- */
	/* (there might come no vsync)*/
	table[KS_CMDF]     = 0x02;
पूर्ण


/* We need to manually पढ़ो because of a bug in the KS0127 chip.
 *
 * An explanation from kayork@mail.utexas.edu:
 *
 * During I2C पढ़ोs, the KS0127 only samples क्रम a stop condition
 * during the place where the acknowledge bit should be. Any standard
 * I2C implementation (correctly) throws in another घड़ी transition
 * at the 9th bit, and the KS0127 will not recognize the stop condition
 * and will जारी to घड़ी out data.
 *
 * So we have to करो the पढ़ो ourself.  Big deal.
 *	   workaround in i2c-algo-bit
 */


अटल u8 ks0127_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	अक्षर val = 0;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = client->addr,
			.len = माप(reg),
			.buf = &reg
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD | I2C_M_NO_RD_ACK,
			.len = माप(val),
			.buf = &val
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs))
		v4l2_dbg(1, debug, sd, "read error\n");

	वापस val;
पूर्ण


अटल व्योम ks0127_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ks0127 *ks = to_ks0127(sd);
	अक्षर msg[] = अणु reg, val पूर्ण;

	अगर (i2c_master_send(client, msg, माप(msg)) != माप(msg))
		v4l2_dbg(1, debug, sd, "write error\n");

	ks->regs[reg] = val;
पूर्ण


/* generic bit-twiddling */
अटल व्योम ks0127_and_or(काष्ठा v4l2_subdev *sd, u8 reg, u8 and_v, u8 or_v)
अणु
	काष्ठा ks0127 *ks = to_ks0127(sd);

	u8 val = ks->regs[reg];
	val = (val & and_v) | or_v;
	ks0127_ग_लिखो(sd, reg, val);
पूर्ण



/****************************************************************************
* ks0127 निजी api
****************************************************************************/
अटल व्योम ks0127_init(काष्ठा v4l2_subdev *sd)
अणु
	u8 *table = reg_शेषs;
	पूर्णांक i;

	v4l2_dbg(1, debug, sd, "reset\n");
	msleep(1);

	/* initialize all रेजिस्टरs to known values */
	/* (except STAT, 0x21, 0x22, TEST and 0x38,0x39) */

	क्रम (i = 1; i < 33; i++)
		ks0127_ग_लिखो(sd, i, table[i]);

	क्रम (i = 35; i < 40; i++)
		ks0127_ग_लिखो(sd, i, table[i]);

	क्रम (i = 41; i < 56; i++)
		ks0127_ग_लिखो(sd, i, table[i]);

	क्रम (i = 58; i < 64; i++)
		ks0127_ग_लिखो(sd, i, table[i]);


	अगर ((ks0127_पढ़ो(sd, KS_STAT) & 0x80) == 0) अणु
		v4l2_dbg(1, debug, sd, "ks0122s found\n");
		वापस;
	पूर्ण

	चयन (ks0127_पढ़ो(sd, KS_CMDE) & 0x0f) अणु
	हाल 0:
		v4l2_dbg(1, debug, sd, "ks0127 found\n");
		अवरोध;

	हाल 9:
		v4l2_dbg(1, debug, sd, "ks0127B Revision A found\n");
		अवरोध;

	शेष:
		v4l2_dbg(1, debug, sd, "unknown revision\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ks0127_s_routing(काष्ठा v4l2_subdev *sd,
			    u32 input, u32 output, u32 config)
अणु
	काष्ठा ks0127 *ks = to_ks0127(sd);

	चयन (input) अणु
	हाल KS_INPUT_COMPOSITE_1:
	हाल KS_INPUT_COMPOSITE_2:
	हाल KS_INPUT_COMPOSITE_3:
	हाल KS_INPUT_COMPOSITE_4:
	हाल KS_INPUT_COMPOSITE_5:
	हाल KS_INPUT_COMPOSITE_6:
		v4l2_dbg(1, debug, sd,
			"s_routing %d: Composite\n", input);
		/* स्वतःdetect 50/60 Hz */
		ks0127_and_or(sd, KS_CMDA,   0xfc, 0x00);
		/* VSE=0 */
		ks0127_and_or(sd, KS_CMDA,   ~0x40, 0x00);
		/* set input line */
		ks0127_and_or(sd, KS_CMDB,   0xb0, input);
		/* non-मुक्तrunning mode */
		ks0127_and_or(sd, KS_CMDC,   0x70, 0x0a);
		/* analog input */
		ks0127_and_or(sd, KS_CMDD,   0x03, 0x00);
		/* enable chroma demodulation */
		ks0127_and_or(sd, KS_CTRACK, 0xcf, 0x00);
		/* chroma trap, HYBWR=1 */
		ks0127_and_or(sd, KS_LUMA,   0x00,
			       (reg_शेषs[KS_LUMA])|0x0c);
		/* scaler fullbw, luma comb off */
		ks0127_and_or(sd, KS_VERTIA, 0x08, 0x81);
		/* manual chroma comb .25 .5 .25 */
		ks0127_and_or(sd, KS_VERTIC, 0x0f, 0x90);

		/* chroma path delay */
		ks0127_and_or(sd, KS_CHROMB, 0x0f, 0x90);

		ks0127_ग_लिखो(sd, KS_UGAIN, reg_शेषs[KS_UGAIN]);
		ks0127_ग_लिखो(sd, KS_VGAIN, reg_शेषs[KS_VGAIN]);
		ks0127_ग_लिखो(sd, KS_UVOFFH, reg_शेषs[KS_UVOFFH]);
		ks0127_ग_लिखो(sd, KS_UVOFFL, reg_शेषs[KS_UVOFFL]);
		अवरोध;

	हाल KS_INPUT_SVIDEO_1:
	हाल KS_INPUT_SVIDEO_2:
	हाल KS_INPUT_SVIDEO_3:
		v4l2_dbg(1, debug, sd,
			"s_routing %d: S-Video\n", input);
		/* स्वतःdetect 50/60 Hz */
		ks0127_and_or(sd, KS_CMDA,   0xfc, 0x00);
		/* VSE=0 */
		ks0127_and_or(sd, KS_CMDA,   ~0x40, 0x00);
		/* set input line */
		ks0127_and_or(sd, KS_CMDB,   0xb0, input);
		/* non-मुक्तrunning mode */
		ks0127_and_or(sd, KS_CMDC,   0x70, 0x0a);
		/* analog input */
		ks0127_and_or(sd, KS_CMDD,   0x03, 0x00);
		/* enable chroma demodulation */
		ks0127_and_or(sd, KS_CTRACK, 0xcf, 0x00);
		ks0127_and_or(sd, KS_LUMA, 0x00,
			       reg_शेषs[KS_LUMA]);
		/* disable luma comb */
		ks0127_and_or(sd, KS_VERTIA, 0x08,
			       (reg_शेषs[KS_VERTIA]&0xf0)|0x01);
		ks0127_and_or(sd, KS_VERTIC, 0x0f,
			       reg_शेषs[KS_VERTIC]&0xf0);

		ks0127_and_or(sd, KS_CHROMB, 0x0f,
			       reg_शेषs[KS_CHROMB]&0xf0);

		ks0127_ग_लिखो(sd, KS_UGAIN, reg_शेषs[KS_UGAIN]);
		ks0127_ग_लिखो(sd, KS_VGAIN, reg_शेषs[KS_VGAIN]);
		ks0127_ग_लिखो(sd, KS_UVOFFH, reg_शेषs[KS_UVOFFH]);
		ks0127_ग_लिखो(sd, KS_UVOFFL, reg_शेषs[KS_UVOFFL]);
		अवरोध;

	हाल KS_INPUT_YUV656:
		v4l2_dbg(1, debug, sd, "s_routing 15: YUV656\n");
		अगर (ks->norm & V4L2_STD_525_60)
			/* क्रमce 60 Hz */
			ks0127_and_or(sd, KS_CMDA,   0xfc, 0x03);
		अन्यथा
			/* क्रमce 50 Hz */
			ks0127_and_or(sd, KS_CMDA,   0xfc, 0x02);

		ks0127_and_or(sd, KS_CMDA,   0xff, 0x40); /* VSE=1 */
		/* set input line and VALIGN */
		ks0127_and_or(sd, KS_CMDB,   0xb0, (input | 0x40));
		/* मुक्तrunning mode, */
		/* TSTGEN = 1 TSTGFR=11 TSTGPH=0 TSTGPK=0  VMEM=1*/
		ks0127_and_or(sd, KS_CMDC,   0x70, 0x87);
		/* digital input, SYNसूची = 0 INPSL=01 CLKसूची=0 EAV=0 */
		ks0127_and_or(sd, KS_CMDD,   0x03, 0x08);
		/* disable chroma demodulation */
		ks0127_and_or(sd, KS_CTRACK, 0xcf, 0x30);
		/* HYPK =01 CTRAP = 0 HYBWR=0 PED=1 RGBH=1 UNIT=1 */
		ks0127_and_or(sd, KS_LUMA,   0x00, 0x71);
		ks0127_and_or(sd, KS_VERTIC, 0x0f,
			       reg_शेषs[KS_VERTIC]&0xf0);

		/* scaler fullbw, luma comb off */
		ks0127_and_or(sd, KS_VERTIA, 0x08, 0x81);

		ks0127_and_or(sd, KS_CHROMB, 0x0f,
			       reg_शेषs[KS_CHROMB]&0xf0);

		ks0127_and_or(sd, KS_CON, 0x00, 0x00);
		ks0127_and_or(sd, KS_BRT, 0x00, 32);	/* spec: 34 */
			/* spec: 229 (e5) */
		ks0127_and_or(sd, KS_SAT, 0x00, 0xe8);
		ks0127_and_or(sd, KS_HUE, 0x00, 0);

		ks0127_and_or(sd, KS_UGAIN, 0x00, 238);
		ks0127_and_or(sd, KS_VGAIN, 0x00, 0x00);

		/*UOFF:0x30, VOFF:0x30, TSTCGN=1 */
		ks0127_and_or(sd, KS_UVOFFH, 0x00, 0x4f);
		ks0127_and_or(sd, KS_UVOFFL, 0x00, 0x00);
		अवरोध;

	शेष:
		v4l2_dbg(1, debug, sd,
			"s_routing: Unknown input %d\n", input);
		अवरोध;
	पूर्ण

	/* hack: CDMLPF someबार spontaneously चयनes on; */
	/* क्रमce back off */
	ks0127_ग_लिखो(sd, KS_DEMOD, reg_शेषs[KS_DEMOD]);
	वापस 0;
पूर्ण

अटल पूर्णांक ks0127_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा ks0127 *ks = to_ks0127(sd);

	/* Set to स्वतःmatic SECAM/Fsc mode */
	ks0127_and_or(sd, KS_DEMOD, 0xf0, 0x00);

	ks->norm = std;
	अगर (std & V4L2_STD_NTSC) अणु
		v4l2_dbg(1, debug, sd,
			"s_std: NTSC_M\n");
		ks0127_and_or(sd, KS_CHROMA, 0x9f, 0x20);
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL_N) अणु
		v4l2_dbg(1, debug, sd,
			"s_std: NTSC_N (fixme)\n");
		ks0127_and_or(sd, KS_CHROMA, 0x9f, 0x40);
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL) अणु
		v4l2_dbg(1, debug, sd,
			"s_std: PAL_N\n");
		ks0127_and_or(sd, KS_CHROMA, 0x9f, 0x20);
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL_M) अणु
		v4l2_dbg(1, debug, sd,
			"s_std: PAL_M (fixme)\n");
		ks0127_and_or(sd, KS_CHROMA, 0x9f, 0x40);
	पूर्ण अन्यथा अगर (std & V4L2_STD_SECAM) अणु
		v4l2_dbg(1, debug, sd,
			"s_std: SECAM\n");

		/* set to secam स्वतःdetection */
		ks0127_and_or(sd, KS_CHROMA, 0xdf, 0x20);
		ks0127_and_or(sd, KS_DEMOD, 0xf0, 0x00);
		schedule_समयout_पूर्णांकerruptible(HZ/10+1);

		/* did it स्वतःdetect? */
		अगर (!(ks0127_पढ़ो(sd, KS_DEMOD) & 0x40))
			/* क्रमce to secam mode */
			ks0127_and_or(sd, KS_DEMOD, 0xf0, 0x0f);
	पूर्ण अन्यथा अणु
		v4l2_dbg(1, debug, sd, "s_std: Unknown norm %llx\n",
			       (अचिन्हित दीर्घ दीर्घ)std);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ks0127_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	v4l2_dbg(1, debug, sd, "s_stream(%d)\n", enable);
	अगर (enable) अणु
		/* All output pins on */
		ks0127_and_or(sd, KS_OFMTA, 0xcf, 0x30);
		/* Obey the OEN pin */
		ks0127_and_or(sd, KS_CDEM, 0x7f, 0x00);
	पूर्ण अन्यथा अणु
		/* Video output pins off */
		ks0127_and_or(sd, KS_OFMTA, 0xcf, 0x00);
		/* Ignore the OEN pin */
		ks0127_and_or(sd, KS_CDEM, 0x7f, 0x80);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ks0127_status(काष्ठा v4l2_subdev *sd, u32 *pstatus, v4l2_std_id *pstd)
अणु
	पूर्णांक stat = V4L2_IN_ST_NO_SIGNAL;
	u8 status;
	v4l2_std_id std = pstd ? *pstd : V4L2_STD_ALL;

	status = ks0127_पढ़ो(sd, KS_STAT);
	अगर (!(status & 0x20))		 /* NOVID not set */
		stat = 0;
	अगर (!(status & 0x01)) अणु		      /* CLOCK set */
		stat |= V4L2_IN_ST_NO_COLOR;
		std = V4L2_STD_UNKNOWN;
	पूर्ण अन्यथा अणु
		अगर ((status & 0x08))		   /* PALDET set */
			std &= V4L2_STD_PAL;
		अन्यथा
			std &= V4L2_STD_NTSC;
	पूर्ण
	अगर ((status & 0x10))		   /* PALDET set */
		std &= V4L2_STD_525_60;
	अन्यथा
		std &= V4L2_STD_625_50;
	अगर (pstd)
		*pstd = std;
	अगर (pstatus)
		*pstatus = stat;
	वापस 0;
पूर्ण

अटल पूर्णांक ks0127_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *std)
अणु
	v4l2_dbg(1, debug, sd, "querystd\n");
	वापस ks0127_status(sd, शून्य, std);
पूर्ण

अटल पूर्णांक ks0127_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	v4l2_dbg(1, debug, sd, "g_input_status\n");
	वापस ks0127_status(sd, status, शून्य);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_video_ops ks0127_video_ops = अणु
	.s_std = ks0127_s_std,
	.s_routing = ks0127_s_routing,
	.s_stream = ks0127_s_stream,
	.querystd = ks0127_querystd,
	.g_input_status = ks0127_g_input_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ks0127_ops = अणु
	.video = &ks0127_video_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */


अटल पूर्णांक ks0127_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ks0127 *ks;
	काष्ठा v4l2_subdev *sd;

	v4l_info(client, "%s chip found @ 0x%x (%s)\n",
		client->addr == (I2C_KS0127_ADDON >> 1) ? "addon" : "on-board",
		client->addr << 1, client->adapter->name);

	ks = devm_kzalloc(&client->dev, माप(*ks), GFP_KERNEL);
	अगर (ks == शून्य)
		वापस -ENOMEM;
	sd = &ks->sd;
	v4l2_i2c_subdev_init(sd, client, &ks0127_ops);

	/* घातer up */
	init_reg_शेषs();
	ks0127_ग_लिखो(sd, KS_CMDA, 0x2c);
	mdelay(10);

	/* reset the device */
	ks0127_init(sd);
	वापस 0;
पूर्ण

अटल पूर्णांक ks0127_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	ks0127_ग_लिखो(sd, KS_OFMTA, 0x20); /* tristate */
	ks0127_ग_लिखो(sd, KS_CMDA, 0x2c | 0x80); /* घातer करोwn */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ks0127_id[] = अणु
	अणु "ks0127", 0 पूर्ण,
	अणु "ks0127b", 0 पूर्ण,
	अणु "ks0122s", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ks0127_id);

अटल काष्ठा i2c_driver ks0127_driver = अणु
	.driver = अणु
		.name	= "ks0127",
	पूर्ण,
	.probe		= ks0127_probe,
	.हटाओ		= ks0127_हटाओ,
	.id_table	= ks0127_id,
पूर्ण;

module_i2c_driver(ks0127_driver);
