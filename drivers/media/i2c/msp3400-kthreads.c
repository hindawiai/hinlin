<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Programming the mspx4xx sound processor family
 *
 * (c) 1997-2001 Gerd Knorr <kraxel@bytesex.org>
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/suspend.h>
#समावेश "msp3400-driver.h"

/* this one uses the स्वतःmatic sound standard detection of newer msp34xx
   chip versions */
अटल काष्ठा अणु
	पूर्णांक retval;
	पूर्णांक मुख्य, second;
	अक्षर *name;
	v4l2_std_id std;
पूर्ण msp_stdlist[] = अणु
	अणु 0x0000, 0, 0, "could not detect sound standard", V4L2_STD_ALL पूर्ण,
	अणु 0x0001, 0, 0, "autodetect start", V4L2_STD_ALL पूर्ण,
	अणु 0x0002, MSP_CARRIER(4.5), MSP_CARRIER(4.72),
	  "4.5/4.72  M Dual FM-Stereo", V4L2_STD_MN पूर्ण,
	अणु 0x0003, MSP_CARRIER(5.5), MSP_CARRIER(5.7421875),
	  "5.5/5.74  B/G Dual FM-Stereo", V4L2_STD_BG पूर्ण,
	अणु 0x0004, MSP_CARRIER(6.5), MSP_CARRIER(6.2578125),
	  "6.5/6.25  D/K1 Dual FM-Stereo", V4L2_STD_DK पूर्ण,
	अणु 0x0005, MSP_CARRIER(6.5), MSP_CARRIER(6.7421875),
	  "6.5/6.74  D/K2 Dual FM-Stereo", V4L2_STD_DK पूर्ण,
	अणु 0x0006, MSP_CARRIER(6.5), MSP_CARRIER(6.5),
	  "6.5  D/K FM-Mono (HDEV3)", V4L2_STD_DK पूर्ण,
	अणु 0x0007, MSP_CARRIER(6.5), MSP_CARRIER(5.7421875),
	  "6.5/5.74  D/K3 Dual FM-Stereo", V4L2_STD_DK पूर्ण,
	अणु 0x0008, MSP_CARRIER(5.5), MSP_CARRIER(5.85),
	  "5.5/5.85  B/G NICAM FM", V4L2_STD_BG पूर्ण,
	अणु 0x0009, MSP_CARRIER(6.5), MSP_CARRIER(5.85),
	  "6.5/5.85  L NICAM AM", V4L2_STD_L पूर्ण,
	अणु 0x000a, MSP_CARRIER(6.0), MSP_CARRIER(6.55),
	  "6.0/6.55  I NICAM FM", V4L2_STD_PAL_I पूर्ण,
	अणु 0x000b, MSP_CARRIER(6.5), MSP_CARRIER(5.85),
	  "6.5/5.85  D/K NICAM FM", V4L2_STD_DK पूर्ण,
	अणु 0x000c, MSP_CARRIER(6.5), MSP_CARRIER(5.85),
	  "6.5/5.85  D/K NICAM FM (HDEV2)", V4L2_STD_DK पूर्ण,
	अणु 0x000d, MSP_CARRIER(6.5), MSP_CARRIER(5.85),
	  "6.5/5.85  D/K NICAM FM (HDEV3)", V4L2_STD_DK पूर्ण,
	अणु 0x0020, MSP_CARRIER(4.5), MSP_CARRIER(4.5),
	  "4.5  M BTSC-Stereo", V4L2_STD_MTS पूर्ण,
	अणु 0x0021, MSP_CARRIER(4.5), MSP_CARRIER(4.5),
	  "4.5  M BTSC-Mono + SAP", V4L2_STD_MTS पूर्ण,
	अणु 0x0030, MSP_CARRIER(4.5), MSP_CARRIER(4.5),
	  "4.5  M EIA-J Japan Stereo", V4L2_STD_NTSC_M_JP पूर्ण,
	अणु 0x0040, MSP_CARRIER(10.7), MSP_CARRIER(10.7),
	  "10.7  FM-Stereo Radio", V4L2_STD_ALL पूर्ण,
	अणु 0x0050, MSP_CARRIER(6.5), MSP_CARRIER(6.5),
	  "6.5  SAT-Mono", V4L2_STD_ALL पूर्ण,
	अणु 0x0051, MSP_CARRIER(7.02), MSP_CARRIER(7.20),
	  "7.02/7.20  SAT-Stereo", V4L2_STD_ALL पूर्ण,
	अणु 0x0060, MSP_CARRIER(7.2), MSP_CARRIER(7.2),
	  "7.2  SAT ADR", V4L2_STD_ALL पूर्ण,
	अणु     -1, 0, 0, शून्य, 0 पूर्ण, /* खातापूर्ण */
पूर्ण;

अटल काष्ठा msp3400c_init_data_dem अणु
	पूर्णांक fir1[6];
	पूर्णांक fir2[6];
	पूर्णांक cकरो1;
	पूर्णांक cकरो2;
	पूर्णांक ad_cv;
	पूर्णांक mode_reg;
	पूर्णांक dsp_src;
	पूर्णांक dsp_matrix;
पूर्ण msp3400c_init_data[] = अणु
	अणु	/* AM (क्रम carrier detect / msp3400) */
		अणु75, 19, 36, 35, 39, 40पूर्ण,
		अणु75, 19, 36, 35, 39, 40पूर्ण,
		MSP_CARRIER(5.5), MSP_CARRIER(5.5),
		0x00d0, 0x0500, 0x0020, 0x3000
	पूर्ण, अणु	/* AM (क्रम carrier detect / msp3410) */
		अणु-1, -1, -8, 2, 59, 126पूर्ण,
		अणु-1, -1, -8, 2, 59, 126पूर्ण,
		MSP_CARRIER(5.5), MSP_CARRIER(5.5),
		0x00d0, 0x0100, 0x0020, 0x3000
	पूर्ण, अणु	/* FM Radio */
		अणु-8, -8, 4, 6, 78, 107पूर्ण,
		अणु-8, -8, 4, 6, 78, 107पूर्ण,
		MSP_CARRIER(10.7), MSP_CARRIER(10.7),
		0x00d0, 0x0480, 0x0020, 0x3000
	पूर्ण, अणु	/* Terrestrial FM-mono + FM-stereo */
		अणु3, 18, 27, 48, 66, 72पूर्ण,
		अणु3, 18, 27, 48, 66, 72पूर्ण,
		MSP_CARRIER(5.5), MSP_CARRIER(5.5),
		0x00d0, 0x0480, 0x0030, 0x3000
	पूर्ण, अणु	/* Sat FM-mono */
		अणु 1, 9, 14, 24, 33, 37पूर्ण,
		अणु 3, 18, 27, 48, 66, 72पूर्ण,
		MSP_CARRIER(6.5), MSP_CARRIER(6.5),
		0x00c6, 0x0480, 0x0000, 0x3000
	पूर्ण, अणु	/* NICAM/FM --  B/G (5.5/5.85), D/K (6.5/5.85) */
		अणु-2, -8, -10, 10, 50, 86पूर्ण,
		अणु3, 18, 27, 48, 66, 72पूर्ण,
		MSP_CARRIER(5.5), MSP_CARRIER(5.5),
		0x00d0, 0x0040, 0x0120, 0x3000
	पूर्ण, अणु	/* NICAM/FM -- I (6.0/6.552) */
		अणु2, 4, -6, -4, 40, 94पूर्ण,
		अणु3, 18, 27, 48, 66, 72पूर्ण,
		MSP_CARRIER(6.0), MSP_CARRIER(6.0),
		0x00d0, 0x0040, 0x0120, 0x3000
	पूर्ण, अणु	/* NICAM/AM -- L (6.5/5.85) */
		अणु-2, -8, -10, 10, 50, 86पूर्ण,
		अणु-4, -12, -9, 23, 79, 126पूर्ण,
		MSP_CARRIER(6.5), MSP_CARRIER(6.5),
		0x00c6, 0x0140, 0x0120, 0x7c00
	पूर्ण,
पूर्ण;

काष्ठा msp3400c_carrier_detect अणु
	पूर्णांक   cकरो;
	अक्षर *name;
पूर्ण;

अटल काष्ठा msp3400c_carrier_detect msp3400c_carrier_detect_मुख्य[] = अणु
	/* मुख्य carrier */
	अणु MSP_CARRIER(4.5),        "4.5   NTSC"                   पूर्ण,
	अणु MSP_CARRIER(5.5),        "5.5   PAL B/G"                पूर्ण,
	अणु MSP_CARRIER(6.0),        "6.0   PAL I"                  पूर्ण,
	अणु MSP_CARRIER(6.5),        "6.5   PAL D/K + SAT + SECAM"  पूर्ण
पूर्ण;

अटल काष्ठा msp3400c_carrier_detect msp3400c_carrier_detect_55[] = अणु
	/* PAL B/G */
	अणु MSP_CARRIER(5.7421875),  "5.742 PAL B/G FM-stereo"     पूर्ण,
	अणु MSP_CARRIER(5.85),       "5.85  PAL B/G NICAM"         पूर्ण
पूर्ण;

अटल काष्ठा msp3400c_carrier_detect msp3400c_carrier_detect_65[] = अणु
	/* PAL SAT / SECAM */
	अणु MSP_CARRIER(5.85),       "5.85  PAL D/K + SECAM NICAM" पूर्ण,
	अणु MSP_CARRIER(6.2578125),  "6.25  PAL D/K1 FM-stereo" पूर्ण,
	अणु MSP_CARRIER(6.7421875),  "6.74  PAL D/K2 FM-stereo" पूर्ण,
	अणु MSP_CARRIER(7.02),       "7.02  PAL SAT FM-stereo s/b" पूर्ण,
	अणु MSP_CARRIER(7.20),       "7.20  PAL SAT FM-stereo s"   पूर्ण,
	अणु MSP_CARRIER(7.38),       "7.38  PAL SAT FM-stereo b"   पूर्ण,
पूर्ण;

/* ------------------------------------------------------------------------ */

स्थिर अक्षर *msp_standard_std_name(पूर्णांक std)
अणु
	पूर्णांक i;

	क्रम (i = 0; msp_stdlist[i].name != शून्य; i++)
		अगर (msp_stdlist[i].retval == std)
			वापस msp_stdlist[i].name;
	वापस "unknown";
पूर्ण

अटल v4l2_std_id msp_standard_std(पूर्णांक std)
अणु
	पूर्णांक i;

	क्रम (i = 0; msp_stdlist[i].name != शून्य; i++)
		अगर (msp_stdlist[i].retval == std)
			वापस msp_stdlist[i].std;
	वापस V4L2_STD_ALL;
पूर्ण

अटल व्योम msp_set_source(काष्ठा i2c_client *client, u16 src)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));

	अगर (msp_करोlby) अणु
		msp_ग_लिखो_dsp(client, 0x0008, 0x0520); /* I2S1 */
		msp_ग_लिखो_dsp(client, 0x0009, 0x0620); /* I2S2 */
	पूर्ण अन्यथा अणु
		msp_ग_लिखो_dsp(client, 0x0008, src);
		msp_ग_लिखो_dsp(client, 0x0009, src);
	पूर्ण
	msp_ग_लिखो_dsp(client, 0x000a, src);
	msp_ग_लिखो_dsp(client, 0x000b, src);
	msp_ग_लिखो_dsp(client, 0x000c, src);
	अगर (state->has_scart2_out)
		msp_ग_लिखो_dsp(client, 0x0041, src);
पूर्ण

व्योम msp3400c_set_carrier(काष्ठा i2c_client *client, पूर्णांक cकरो1, पूर्णांक cकरो2)
अणु
	msp_ग_लिखो_dem(client, 0x0093, cकरो1 & 0xfff);
	msp_ग_लिखो_dem(client, 0x009b, cकरो1 >> 12);
	msp_ग_लिखो_dem(client, 0x00a3, cकरो2 & 0xfff);
	msp_ग_लिखो_dem(client, 0x00ab, cकरो2 >> 12);
	msp_ग_लिखो_dem(client, 0x0056, 0); /* LOAD_REG_1/2 */
पूर्ण

व्योम msp3400c_set_mode(काष्ठा i2c_client *client, पूर्णांक mode)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	काष्ठा msp3400c_init_data_dem *data = &msp3400c_init_data[mode];
	पूर्णांक tuner = (state->route_in >> 3) & 1;
	पूर्णांक i;

	dev_dbg_lvl(&client->dev, 1, msp_debug, "set_mode: %d\n", mode);
	state->mode = mode;
	state->rxsubchans = V4L2_TUNER_SUB_MONO;

	msp_ग_लिखो_dem(client, 0x00bb, data->ad_cv | (tuner ? 0x100 : 0));

	क्रम (i = 5; i >= 0; i--)               /* fir 1 */
		msp_ग_लिखो_dem(client, 0x0001, data->fir1[i]);

	msp_ग_लिखो_dem(client, 0x0005, 0x0004); /* fir 2 */
	msp_ग_लिखो_dem(client, 0x0005, 0x0040);
	msp_ग_लिखो_dem(client, 0x0005, 0x0000);
	क्रम (i = 5; i >= 0; i--)
		msp_ग_लिखो_dem(client, 0x0005, data->fir2[i]);

	msp_ग_लिखो_dem(client, 0x0083, data->mode_reg);

	msp3400c_set_carrier(client, data->cकरो1, data->cकरो2);

	msp_set_source(client, data->dsp_src);
	/* set prescales */

	/* volume prescale क्रम SCART (AM mono input) */
	msp_ग_लिखो_dsp(client, 0x000d, 0x1900);
	msp_ग_लिखो_dsp(client, 0x000e, data->dsp_matrix);
	अगर (state->has_nicam) /* nicam prescale */
		msp_ग_लिखो_dsp(client, 0x0010, 0x5a00);
पूर्ण

/* Set audio mode. Note that the pre-'G' models करो not support BTSC+SAP,
   nor करो they support stereo BTSC. */
अटल व्योम msp3400c_set_audmode(काष्ठा i2c_client *client)
अणु
	अटल अक्षर *strmode[] = अणु
		"mono", "stereo", "lang2", "lang1", "lang1+lang2"
	पूर्ण;
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	अक्षर *modestr = (state->audmode >= 0 && state->audmode < 5) ?
		strmode[state->audmode] : "unknown";
	पूर्णांक src = 0;	/* channel source: FM/AM, nicam or SCART */
	पूर्णांक audmode = state->audmode;

	अगर (state->opmode == OPMODE_AUTOSELECT) अणु
		/* this method would अवरोध everything, let's make sure
		 * it's never called
		 */
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"set_audmode called with mode=%d instead of set_source (ignored)\n",
			state->audmode);
		वापस;
	पूर्ण

	/* Note: क्रम the C and D revs no NTSC stereo + SAP is possible as
	   the hardware करोes not support SAP. So the rxsubchans combination
	   of STEREO | LANG2 करोes not occur. */

	अगर (state->mode != MSP_MODE_EXTERN) अणु
		/* चयन to mono अगर only mono is available */
		अगर (state->rxsubchans == V4L2_TUNER_SUB_MONO)
			audmode = V4L2_TUNER_MODE_MONO;
		/* अगर bilingual */
		अन्यथा अगर (state->rxsubchans & V4L2_TUNER_SUB_LANG2) अणु
			/* and mono or stereo, then fallback to lang1 */
			अगर (audmode == V4L2_TUNER_MODE_MONO ||
			    audmode == V4L2_TUNER_MODE_STEREO)
				audmode = V4L2_TUNER_MODE_LANG1;
		पूर्ण
		/* अगर stereo, and audmode is not mono, then चयन to stereo */
		अन्यथा अगर (audmode != V4L2_TUNER_MODE_MONO)
			audmode = V4L2_TUNER_MODE_STEREO;
	पूर्ण

	/* चयन demodulator */
	चयन (state->mode) अणु
	हाल MSP_MODE_FM_TERRA:
		dev_dbg_lvl(&client->dev, 1, msp_debug, "FM set_audmode: %s\n", modestr);
		चयन (audmode) अणु
		हाल V4L2_TUNER_MODE_STEREO:
			msp_ग_लिखो_dsp(client, 0x000e, 0x3001);
			अवरोध;
		हाल V4L2_TUNER_MODE_MONO:
		हाल V4L2_TUNER_MODE_LANG1:
		हाल V4L2_TUNER_MODE_LANG2:
		हाल V4L2_TUNER_MODE_LANG1_LANG2:
			msp_ग_लिखो_dsp(client, 0x000e, 0x3000);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MSP_MODE_FM_SAT:
		dev_dbg_lvl(&client->dev, 1, msp_debug, "SAT set_audmode: %s\n", modestr);
		चयन (audmode) अणु
		हाल V4L2_TUNER_MODE_MONO:
			msp3400c_set_carrier(client, MSP_CARRIER(6.5), MSP_CARRIER(6.5));
			अवरोध;
		हाल V4L2_TUNER_MODE_STEREO:
		हाल V4L2_TUNER_MODE_LANG1_LANG2:
			msp3400c_set_carrier(client, MSP_CARRIER(7.2), MSP_CARRIER(7.02));
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1:
			msp3400c_set_carrier(client, MSP_CARRIER(7.38), MSP_CARRIER(7.02));
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG2:
			msp3400c_set_carrier(client, MSP_CARRIER(7.38), MSP_CARRIER(7.02));
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MSP_MODE_FM_NICAM1:
	हाल MSP_MODE_FM_NICAM2:
	हाल MSP_MODE_AM_NICAM:
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"NICAM set_audmode: %s\n", modestr);
		अगर (state->nicam_on)
			src = 0x0100;  /* NICAM */
		अवरोध;
	हाल MSP_MODE_BTSC:
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"BTSC set_audmode: %s\n", modestr);
		अवरोध;
	हाल MSP_MODE_EXTERN:
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"extern set_audmode: %s\n", modestr);
		src = 0x0200;  /* SCART */
		अवरोध;
	हाल MSP_MODE_FM_RADIO:
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"FM-Radio set_audmode: %s\n", modestr);
		अवरोध;
	शेष:
		dev_dbg_lvl(&client->dev, 1, msp_debug, "mono set_audmode\n");
		वापस;
	पूर्ण

	/* चयन audio */
	dev_dbg_lvl(&client->dev, 1, msp_debug, "set audmode %d\n", audmode);
	चयन (audmode) अणु
	हाल V4L2_TUNER_MODE_STEREO:
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		src |= 0x0020;
		अवरोध;
	हाल V4L2_TUNER_MODE_MONO:
		अगर (state->mode == MSP_MODE_AM_NICAM) अणु
			dev_dbg_lvl(&client->dev, 1, msp_debug, "switching to AM mono\n");
			/* AM mono decoding is handled by tuner, not MSP chip */
			/* SCART चयनing control रेजिस्टर */
			msp_set_scart(client, SCART_MONO, 0);
			src = 0x0200;
			अवरोध;
		पूर्ण
		अगर (state->rxsubchans & V4L2_TUNER_SUB_STEREO)
			src = 0x0030;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1:
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		src |= 0x0010;
		अवरोध;
	पूर्ण
	dev_dbg_lvl(&client->dev, 1, msp_debug,
		"set_audmode final source/matrix = 0x%x\n", src);

	msp_set_source(client, src);
पूर्ण

अटल व्योम msp3400c_prपूर्णांक_mode(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));

	अगर (state->मुख्य == state->second)
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"mono sound carrier: %d.%03d MHz\n",
			state->मुख्य / 910000, (state->मुख्य / 910) % 1000);
	अन्यथा
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"main sound carrier: %d.%03d MHz\n",
			state->मुख्य / 910000, (state->मुख्य / 910) % 1000);
	अगर (state->mode == MSP_MODE_FM_NICAM1 || state->mode == MSP_MODE_FM_NICAM2)
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"NICAM/FM carrier  : %d.%03d MHz\n",
			state->second / 910000, (state->second/910) % 1000);
	अगर (state->mode == MSP_MODE_AM_NICAM)
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"NICAM/AM carrier  : %d.%03d MHz\n",
			state->second / 910000, (state->second / 910) % 1000);
	अगर (state->mode == MSP_MODE_FM_TERRA && state->मुख्य != state->second) अणु
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"FM-stereo carrier : %d.%03d MHz\n",
			state->second / 910000, (state->second / 910) % 1000);
	पूर्ण
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक msp3400c_detect_stereo(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	पूर्णांक val;
	पूर्णांक rxsubchans = state->rxsubchans;
	पूर्णांक newnicam = state->nicam_on;
	पूर्णांक update = 0;

	चयन (state->mode) अणु
	हाल MSP_MODE_FM_TERRA:
		val = msp_पढ़ो_dsp(client, 0x18);
		अगर (val > 32767)
			val -= 65536;
		dev_dbg_lvl(&client->dev, 2, msp_debug,
			"stereo detect register: %d\n", val);
		अगर (val > 8192) अणु
			rxsubchans = V4L2_TUNER_SUB_STEREO;
		पूर्ण अन्यथा अगर (val < -4096) अणु
			rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
		पूर्ण अन्यथा अणु
			rxsubchans = V4L2_TUNER_SUB_MONO;
		पूर्ण
		newnicam = 0;
		अवरोध;
	हाल MSP_MODE_FM_NICAM1:
	हाल MSP_MODE_FM_NICAM2:
	हाल MSP_MODE_AM_NICAM:
		val = msp_पढ़ो_dem(client, 0x23);
		dev_dbg_lvl(&client->dev, 2, msp_debug, "nicam sync=%d, mode=%d\n",
			val & 1, (val & 0x1e) >> 1);

		अगर (val & 1) अणु
			/* nicam synced */
			चयन ((val & 0x1e) >> 1)  अणु
			हाल 0:
			हाल 8:
				rxsubchans = V4L2_TUNER_SUB_STEREO;
				अवरोध;
			हाल 1:
			हाल 9:
				rxsubchans = V4L2_TUNER_SUB_MONO;
				अवरोध;
			हाल 2:
			हाल 10:
				rxsubchans = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
				अवरोध;
			शेष:
				rxsubchans = V4L2_TUNER_SUB_MONO;
				अवरोध;
			पूर्ण
			newnicam = 1;
		पूर्ण अन्यथा अणु
			newnicam = 0;
			rxsubchans = V4L2_TUNER_SUB_MONO;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (rxsubchans != state->rxsubchans) अणु
		update = 1;
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"watch: rxsubchans %02x => %02x\n",
			state->rxsubchans, rxsubchans);
		state->rxsubchans = rxsubchans;
	पूर्ण
	अगर (newnicam != state->nicam_on) अणु
		update = 1;
		dev_dbg_lvl(&client->dev, 1, msp_debug, "watch: nicam %d => %d\n",
			state->nicam_on, newnicam);
		state->nicam_on = newnicam;
	पूर्ण
	वापस update;
पूर्ण

/*
 * A kernel thपढ़ो क्रम msp3400 control -- we करोn't want to block the
 * in the ioctl जबतक करोing the sound carrier & stereo detect
 */
/* stereo/multilang monitoring */
अटल व्योम watch_stereo(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));

	अगर (msp_detect_stereo(client))
		msp_set_audmode(client);

	अगर (msp_once)
		state->watch_stereo = 0;
पूर्ण

पूर्णांक msp3400c_thपढ़ो(व्योम *data)
अणु
	काष्ठा i2c_client *client = data;
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	काष्ठा msp3400c_carrier_detect *cd;
	पूर्णांक count, max1, max2, val1, val2, val, i;

	dev_dbg_lvl(&client->dev, 1, msp_debug, "msp3400 daemon started\n");
	state->detected_std = V4L2_STD_ALL;
	set_मुक्तzable();
	क्रम (;;) अणु
		dev_dbg_lvl(&client->dev, 2, msp_debug, "msp3400 thread: sleep\n");
		msp_sleep(state, -1);
		dev_dbg_lvl(&client->dev, 2, msp_debug, "msp3400 thread: wakeup\n");

restart:
		dev_dbg_lvl(&client->dev, 2, msp_debug, "thread: restart scan\n");
		state->restart = 0;
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (state->radio || MSP_MODE_EXTERN == state->mode) अणु
			/* no carrier scan, just unmute */
			dev_dbg_lvl(&client->dev, 1, msp_debug,
				"thread: no carrier scan\n");
			state->scan_in_progress = 0;
			msp_update_volume(state);
			जारी;
		पूर्ण

		/* mute audio */
		state->scan_in_progress = 1;
		msp_update_volume(state);

		msp3400c_set_mode(client, MSP_MODE_AM_DETECT);
		val1 = val2 = 0;
		max1 = max2 = -1;
		state->watch_stereo = 0;
		state->nicam_on = 0;

		/* रुको क्रम tuner to settle करोwn after a channel change */
		अगर (msp_sleep(state, 200))
			जाओ restart;

		/* carrier detect pass #1 -- मुख्य carrier */
		cd = msp3400c_carrier_detect_मुख्य;
		count = ARRAY_SIZE(msp3400c_carrier_detect_मुख्य);

		अगर (msp_amsound && (state->v4l2_std & V4L2_STD_SECAM)) अणु
			/* स्वतःdetect करोesn't work well with AM ... */
			max1 = 3;
			count = 0;
			dev_dbg_lvl(&client->dev, 1, msp_debug, "AM sound override\n");
		पूर्ण

		क्रम (i = 0; i < count; i++) अणु
			msp3400c_set_carrier(client, cd[i].cकरो, cd[i].cकरो);
			अगर (msp_sleep(state, 100))
				जाओ restart;
			val = msp_पढ़ो_dsp(client, 0x1b);
			अगर (val > 32767)
				val -= 65536;
			अगर (val1 < val) अणु
				val1 = val;
				max1 = i;
			पूर्ण
			dev_dbg_lvl(&client->dev, 1, msp_debug,
				"carrier1 val: %5d / %s\n", val, cd[i].name);
		पूर्ण

		/* carrier detect pass #2 -- second (stereo) carrier */
		चयन (max1) अणु
		हाल 1: /* 5.5 */
			cd = msp3400c_carrier_detect_55;
			count = ARRAY_SIZE(msp3400c_carrier_detect_55);
			अवरोध;
		हाल 3: /* 6.5 */
			cd = msp3400c_carrier_detect_65;
			count = ARRAY_SIZE(msp3400c_carrier_detect_65);
			अवरोध;
		हाल 0: /* 4.5 */
		हाल 2: /* 6.0 */
		शेष:
			cd = शून्य;
			count = 0;
			अवरोध;
		पूर्ण

		अगर (msp_amsound && (state->v4l2_std & V4L2_STD_SECAM)) अणु
			/* स्वतःdetect करोesn't work well with AM ... */
			cd = शून्य;
			count = 0;
			max2 = 0;
		पूर्ण
		क्रम (i = 0; i < count; i++) अणु
			msp3400c_set_carrier(client, cd[i].cकरो, cd[i].cकरो);
			अगर (msp_sleep(state, 100))
				जाओ restart;
			val = msp_पढ़ो_dsp(client, 0x1b);
			अगर (val > 32767)
				val -= 65536;
			अगर (val2 < val) अणु
				val2 = val;
				max2 = i;
			पूर्ण
			dev_dbg_lvl(&client->dev, 1, msp_debug,
				"carrier2 val: %5d / %s\n", val, cd[i].name);
		पूर्ण

		/* program the msp3400 according to the results */
		state->मुख्य = msp3400c_carrier_detect_मुख्य[max1].cकरो;
		चयन (max1) अणु
		हाल 1: /* 5.5 */
			state->detected_std = V4L2_STD_BG | V4L2_STD_PAL_H;
			अगर (max2 == 0) अणु
				/* B/G FM-stereo */
				state->second = msp3400c_carrier_detect_55[max2].cकरो;
				msp3400c_set_mode(client, MSP_MODE_FM_TERRA);
				state->watch_stereo = 1;
			पूर्ण अन्यथा अगर (max2 == 1 && state->has_nicam) अणु
				/* B/G NICAM */
				state->second = msp3400c_carrier_detect_55[max2].cकरो;
				msp3400c_set_mode(client, MSP_MODE_FM_NICAM1);
				state->nicam_on = 1;
				state->watch_stereo = 1;
			पूर्ण अन्यथा अणु
				जाओ no_second;
			पूर्ण
			अवरोध;
		हाल 2: /* 6.0 */
			/* PAL I NICAM */
			state->detected_std = V4L2_STD_PAL_I;
			state->second = MSP_CARRIER(6.552);
			msp3400c_set_mode(client, MSP_MODE_FM_NICAM2);
			state->nicam_on = 1;
			state->watch_stereo = 1;
			अवरोध;
		हाल 3: /* 6.5 */
			अगर (max2 == 1 || max2 == 2) अणु
				/* D/K FM-stereo */
				state->second = msp3400c_carrier_detect_65[max2].cकरो;
				msp3400c_set_mode(client, MSP_MODE_FM_TERRA);
				state->watch_stereo = 1;
				state->detected_std = V4L2_STD_DK;
			पूर्ण अन्यथा अगर (max2 == 0 && (state->v4l2_std & V4L2_STD_SECAM)) अणु
				/* L NICAM or AM-mono */
				state->second = msp3400c_carrier_detect_65[max2].cकरो;
				msp3400c_set_mode(client, MSP_MODE_AM_NICAM);
				state->watch_stereo = 1;
				state->detected_std = V4L2_STD_L;
			पूर्ण अन्यथा अगर (max2 == 0 && state->has_nicam) अणु
				/* D/K NICAM */
				state->second = msp3400c_carrier_detect_65[max2].cकरो;
				msp3400c_set_mode(client, MSP_MODE_FM_NICAM1);
				state->nicam_on = 1;
				state->watch_stereo = 1;
				state->detected_std = V4L2_STD_DK;
			पूर्ण अन्यथा अणु
				जाओ no_second;
			पूर्ण
			अवरोध;
		हाल 0: /* 4.5 */
			state->detected_std = V4L2_STD_MN;
			fallthrough;
		शेष:
no_second:
			state->second = msp3400c_carrier_detect_मुख्य[max1].cकरो;
			msp3400c_set_mode(client, MSP_MODE_FM_TERRA);
			अवरोध;
		पूर्ण
		msp3400c_set_carrier(client, state->second, state->मुख्य);

		/* unmute */
		state->scan_in_progress = 0;
		msp3400c_set_audmode(client);
		msp_update_volume(state);

		अगर (msp_debug)
			msp3400c_prपूर्णांक_mode(client);

		/* monitor tv audio mode, the first समय करोn't रुको
		   so दीर्घ to get a quick stereo/bilingual result */
		count = 3;
		जबतक (state->watch_stereo) अणु
			अगर (msp_sleep(state, count ? 1000 : 5000))
				जाओ restart;
			अगर (count)
				count--;
			watch_stereo(client);
		पूर्ण
	पूर्ण
	dev_dbg_lvl(&client->dev, 1, msp_debug, "thread: exit\n");
	वापस 0;
पूर्ण


पूर्णांक msp3410d_thपढ़ो(व्योम *data)
अणु
	काष्ठा i2c_client *client = data;
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	पूर्णांक val, i, std, count;

	dev_dbg_lvl(&client->dev, 1, msp_debug, "msp3410 daemon started\n");
	state->detected_std = V4L2_STD_ALL;
	set_मुक्तzable();
	क्रम (;;) अणु
		dev_dbg_lvl(&client->dev, 2, msp_debug, "msp3410 thread: sleep\n");
		msp_sleep(state, -1);
		dev_dbg_lvl(&client->dev, 2, msp_debug, "msp3410 thread: wakeup\n");

restart:
		dev_dbg_lvl(&client->dev, 2, msp_debug, "thread: restart scan\n");
		state->restart = 0;
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (state->mode == MSP_MODE_EXTERN) अणु
			/* no carrier scan needed, just unmute */
			dev_dbg_lvl(&client->dev, 1, msp_debug,
				"thread: no carrier scan\n");
			state->scan_in_progress = 0;
			msp_update_volume(state);
			जारी;
		पूर्ण

		/* mute audio */
		state->scan_in_progress = 1;
		msp_update_volume(state);

		/* start स्वतःdetect. Note: स्वतःdetect is not supported क्रम
		   NTSC-M and radio, hence we क्रमce the standard in those
		   हालs. */
		अगर (state->radio)
			std = 0x40;
		अन्यथा
			std = (state->v4l2_std & V4L2_STD_NTSC) ? 0x20 : 1;
		state->watch_stereo = 0;
		state->nicam_on = 0;

		/* रुको क्रम tuner to settle करोwn after a channel change */
		अगर (msp_sleep(state, 200))
			जाओ restart;

		अगर (msp_debug)
			dev_dbg_lvl(&client->dev, 2, msp_debug,
				"setting standard: %s (0x%04x)\n",
				msp_standard_std_name(std), std);

		अगर (std != 1) अणु
			/* programmed some specअगरic mode */
			val = std;
		पूर्ण अन्यथा अणु
			/* triggered स्वतःdetect */
			msp_ग_लिखो_dem(client, 0x20, std);
			क्रम (;;) अणु
				अगर (msp_sleep(state, 100))
					जाओ restart;

				/* check results */
				val = msp_पढ़ो_dem(client, 0x7e);
				अगर (val < 0x07ff)
					अवरोध;
				dev_dbg_lvl(&client->dev, 2, msp_debug,
					"detection still in progress\n");
			पूर्ण
		पूर्ण
		क्रम (i = 0; msp_stdlist[i].name != शून्य; i++)
			अगर (msp_stdlist[i].retval == val)
				अवरोध;
		dev_dbg_lvl(&client->dev, 1, msp_debug, "current standard: %s (0x%04x)\n",
			msp_standard_std_name(val), val);
		state->मुख्य   = msp_stdlist[i].मुख्य;
		state->second = msp_stdlist[i].second;
		state->std = val;
		state->rxsubchans = V4L2_TUNER_SUB_MONO;

		अगर (msp_amsound && !state->radio &&
		    (state->v4l2_std & V4L2_STD_SECAM) && (val != 0x0009)) अणु
			/* स्वतःdetection has failed, let backup */
			dev_dbg_lvl(&client->dev, 1, msp_debug, "autodetection failed, switching to backup standard: %s (0x%04x)\n",
				msp_stdlist[8].name ?
					msp_stdlist[8].name : "unknown", val);
			state->std = val = 0x0009;
			msp_ग_लिखो_dem(client, 0x20, val);
		पूर्ण अन्यथा अणु
			state->detected_std = msp_standard_std(state->std);
		पूर्ण

		/* set stereo */
		चयन (val) अणु
		हाल 0x0008: /* B/G NICAM */
		हाल 0x000a: /* I NICAM */
		हाल 0x000b: /* D/K NICAM */
			अगर (val == 0x000a)
				state->mode = MSP_MODE_FM_NICAM2;
			अन्यथा
				state->mode = MSP_MODE_FM_NICAM1;
			/* just turn on stereo */
			state->nicam_on = 1;
			state->watch_stereo = 1;
			अवरोध;
		हाल 0x0009:
			state->mode = MSP_MODE_AM_NICAM;
			state->nicam_on = 1;
			state->watch_stereo = 1;
			अवरोध;
		हाल 0x0020: /* BTSC */
			/* The pre-'G' models only have BTSC-mono */
			state->mode = MSP_MODE_BTSC;
			अवरोध;
		हाल 0x0040: /* FM radio */
			state->mode = MSP_MODE_FM_RADIO;
			state->rxsubchans = V4L2_TUNER_SUB_STEREO;
			/* not needed in theory अगर we have radio, but
			   लघु programming enables carrier mute */
			msp3400c_set_mode(client, MSP_MODE_FM_RADIO);
			msp3400c_set_carrier(client, MSP_CARRIER(10.7),
					    MSP_CARRIER(10.7));
			अवरोध;
		हाल 0x0002:
		हाल 0x0003:
		हाल 0x0004:
		हाल 0x0005:
			state->mode = MSP_MODE_FM_TERRA;
			state->watch_stereo = 1;
			अवरोध;
		पूर्ण

		/* set various prescales */
		msp_ग_लिखो_dsp(client, 0x0d, 0x1900); /* scart */
		msp_ग_लिखो_dsp(client, 0x0e, 0x3000); /* FM */
		अगर (state->has_nicam)
			msp_ग_लिखो_dsp(client, 0x10, 0x5a00); /* nicam */

		अगर (state->has_i2s_conf)
			msp_ग_लिखो_dem(client, 0x40, state->i2s_mode);

		/* unmute */
		msp3400c_set_audmode(client);
		state->scan_in_progress = 0;
		msp_update_volume(state);

		/* monitor tv audio mode, the first समय करोn't रुको
		   so दीर्घ to get a quick stereo/bilingual result */
		count = 3;
		जबतक (state->watch_stereo) अणु
			अगर (msp_sleep(state, count ? 1000 : 5000))
				जाओ restart;
			अगर (count)
				count--;
			watch_stereo(client);
		पूर्ण
	पूर्ण
	dev_dbg_lvl(&client->dev, 1, msp_debug, "thread: exit\n");
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

/* msp34xxG + (स्वतःselect no-thपढ़ो)
 * this one uses both स्वतःmatic standard detection and स्वतःmatic sound
 * select which are available in the newer G versions
 * काष्ठा msp: only norm, acb and source are really used in this mode
 */

अटल पूर्णांक msp34xxg_modus(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));

	अगर (state->radio) अणु
		dev_dbg_lvl(&client->dev, 1, msp_debug, "selected radio modus\n");
		वापस 0x0001;
	पूर्ण
	अगर (state->v4l2_std == V4L2_STD_NTSC_M_JP) अणु
		dev_dbg_lvl(&client->dev, 1, msp_debug, "selected M (EIA-J) modus\n");
		वापस 0x4001;
	पूर्ण
	अगर (state->v4l2_std == V4L2_STD_NTSC_M_KR) अणु
		dev_dbg_lvl(&client->dev, 1, msp_debug, "selected M (A2) modus\n");
		वापस 0x0001;
	पूर्ण
	अगर (state->v4l2_std == V4L2_STD_SECAM_L) अणु
		dev_dbg_lvl(&client->dev, 1, msp_debug, "selected SECAM-L modus\n");
		वापस 0x6001;
	पूर्ण
	अगर (state->v4l2_std & V4L2_STD_MN) अणु
		dev_dbg_lvl(&client->dev, 1, msp_debug, "selected M (BTSC) modus\n");
		वापस 0x2001;
	पूर्ण
	वापस 0x7001;
पूर्ण

अटल व्योम msp34xxg_set_source(काष्ठा i2c_client *client, u16 reg, पूर्णांक in)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	पूर्णांक source, matrix;

	चयन (state->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		source = 0; /* mono only */
		matrix = 0x30;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		source = 4; /* stereo or B */
		matrix = 0x10;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		source = 1; /* stereo or A|B */
		matrix = 0x20;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1:
		source = 3; /* stereo or A */
		matrix = 0x00;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
	शेष:
		source = 3; /* stereo or A */
		matrix = 0x20;
		अवरोध;
	पूर्ण

	अगर (in == MSP_DSP_IN_TUNER)
		source = (source << 8) | 0x20;
	/* the msp34x2g माला_दो the MAIN_AVC, MAIN and AUX sources in 12, 13, 14
	   instead of 11, 12, 13. So we add one क्रम that msp version. */
	अन्यथा अगर (in >= MSP_DSP_IN_MAIN_AVC && state->has_करोlby_pro_logic)
		source = ((in + 1) << 8) | matrix;
	अन्यथा
		source = (in << 8) | matrix;

	dev_dbg_lvl(&client->dev, 1, msp_debug,
		"set source to %d (0x%x) for output %02x\n", in, source, reg);
	msp_ग_लिखो_dsp(client, reg, source);
पूर्ण

अटल व्योम msp34xxg_set_sources(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	u32 in = state->route_in;

	msp34xxg_set_source(client, 0x0008, (in >> 4) & 0xf);
	/* quasi-peak detector is set to same input as the loudspeaker (MAIN) */
	msp34xxg_set_source(client, 0x000c, (in >> 4) & 0xf);
	msp34xxg_set_source(client, 0x0009, (in >> 8) & 0xf);
	msp34xxg_set_source(client, 0x000a, (in >> 12) & 0xf);
	अगर (state->has_scart2_out)
		msp34xxg_set_source(client, 0x0041, (in >> 16) & 0xf);
	msp34xxg_set_source(client, 0x000b, (in >> 20) & 0xf);
पूर्ण

/* (re-)initialize the msp34xxg */
अटल व्योम msp34xxg_reset(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	पूर्णांक tuner = (state->route_in >> 3) & 1;
	पूर्णांक modus;

	/* initialize std to 1 (स्वतःdetect) to संकेत that no standard is
	   selected yet. */
	state->std = 1;

	msp_reset(client);

	अगर (state->has_i2s_conf)
		msp_ग_लिखो_dem(client, 0x40, state->i2s_mode);

	/* step-by-step initialisation, as described in the manual */
	modus = msp34xxg_modus(client);
	modus |= tuner ? 0x100 : 0;
	msp_ग_लिखो_dem(client, 0x30, modus);

	/* ग_लिखो the dsps that may have an influence on
	   standard/audio स्वतःdetection right now */
	msp34xxg_set_sources(client);

	msp_ग_लिखो_dsp(client, 0x0d, 0x1900); /* scart */
	msp_ग_लिखो_dsp(client, 0x0e, 0x3000); /* FM */
	अगर (state->has_nicam)
		msp_ग_लिखो_dsp(client, 0x10, 0x5a00); /* nicam */

	/* set identअगरication threshold. Personally, I
	 * I set it to a higher value than the शेष
	 * of 0x190 to ignore noisy stereo संकेतs.
	 * this needs tuning. (recommended range 0x00a0-0x03c0)
	 * 0x7f0 = क्रमced mono mode
	 *
	 * a2 threshold क्रम stereo/bilingual.
	 * Note: this रेजिस्टर is part of the Manual/Compatibility mode.
	 * It is supported by all 'G'-family chips.
	 */
	msp_ग_लिखो_dem(client, 0x22, msp_stereo_thresh);
पूर्ण

पूर्णांक msp34xxg_thपढ़ो(व्योम *data)
अणु
	काष्ठा i2c_client *client = data;
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	पूर्णांक val, i;

	dev_dbg_lvl(&client->dev, 1, msp_debug, "msp34xxg daemon started\n");
	state->detected_std = V4L2_STD_ALL;
	set_मुक्तzable();
	क्रम (;;) अणु
		dev_dbg_lvl(&client->dev, 2, msp_debug, "msp34xxg thread: sleep\n");
		msp_sleep(state, -1);
		dev_dbg_lvl(&client->dev, 2, msp_debug, "msp34xxg thread: wakeup\n");

restart:
		dev_dbg_lvl(&client->dev, 1, msp_debug, "thread: restart scan\n");
		state->restart = 0;
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (state->mode == MSP_MODE_EXTERN) अणु
			/* no carrier scan needed, just unmute */
			dev_dbg_lvl(&client->dev, 1, msp_debug,
				"thread: no carrier scan\n");
			state->scan_in_progress = 0;
			msp_update_volume(state);
			जारी;
		पूर्ण

		/* setup the chip*/
		msp34xxg_reset(client);
		state->std = state->radio ? 0x40 :
			(state->क्रमce_btsc && msp_standard == 1) ? 32 : msp_standard;
		msp_ग_लिखो_dem(client, 0x20, state->std);
		/* start स्वतःdetect */
		अगर (state->std != 1)
			जाओ unmute;

		/* watch स्वतःdetect */
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"started autodetect, waiting for result\n");
		क्रम (i = 0; i < 10; i++) अणु
			अगर (msp_sleep(state, 100))
				जाओ restart;

			/* check results */
			val = msp_पढ़ो_dem(client, 0x7e);
			अगर (val < 0x07ff) अणु
				state->std = val;
				अवरोध;
			पूर्ण
			dev_dbg_lvl(&client->dev, 2, msp_debug,
				"detection still in progress\n");
		पूर्ण
		अगर (state->std == 1) अणु
			dev_dbg_lvl(&client->dev, 1, msp_debug,
				"detection still in progress after 10 tries. giving up.\n");
			जारी;
		पूर्ण

unmute:
		dev_dbg_lvl(&client->dev, 1, msp_debug,
			"detected standard: %s (0x%04x)\n",
			msp_standard_std_name(state->std), state->std);
		state->detected_std = msp_standard_std(state->std);

		अगर (state->std == 9) अणु
			/* AM NICAM mode */
			msp_ग_लिखो_dsp(client, 0x0e, 0x7c00);
		पूर्ण

		/* unmute: dispatch sound to scart output, set scart volume */
		msp_update_volume(state);

		/* restore ACB */
		अगर (msp_ग_लिखो_dsp(client, 0x13, state->acb))
			वापस -1;

		/* the periodic stereo/SAP check is only relevant क्रम
		   the 0x20 standard (BTSC) */
		अगर (state->std != 0x20)
			जारी;

		state->watch_stereo = 1;

		/* monitor tv audio mode, the first समय करोn't रुको
		   in order to get a quick stereo/SAP update */
		watch_stereo(client);
		जबतक (state->watch_stereo) अणु
			watch_stereo(client);
			अगर (msp_sleep(state, 5000))
				जाओ restart;
		पूर्ण
	पूर्ण
	dev_dbg_lvl(&client->dev, 1, msp_debug, "thread: exit\n");
	वापस 0;
पूर्ण

अटल पूर्णांक msp34xxg_detect_stereo(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));
	पूर्णांक status = msp_पढ़ो_dem(client, 0x0200);
	पूर्णांक is_bilingual = status & 0x100;
	पूर्णांक is_stereo = status & 0x40;
	पूर्णांक oldrx = state->rxsubchans;

	अगर (state->mode == MSP_MODE_EXTERN)
		वापस 0;

	state->rxsubchans = 0;
	अगर (is_stereo)
		state->rxsubchans = V4L2_TUNER_SUB_STEREO;
	अन्यथा
		state->rxsubchans = V4L2_TUNER_SUB_MONO;
	अगर (is_bilingual) अणु
		अगर (state->std == 0x20)
			state->rxsubchans |= V4L2_TUNER_SUB_SAP;
		अन्यथा
			state->rxsubchans =
				V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	पूर्ण
	dev_dbg_lvl(&client->dev, 1, msp_debug,
		"status=0x%x, stereo=%d, bilingual=%d -> rxsubchans=%d\n",
		status, is_stereo, is_bilingual, state->rxsubchans);
	वापस (oldrx != state->rxsubchans);
पूर्ण

अटल व्योम msp34xxg_set_audmode(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));

	अगर (state->std == 0x20) अणु
	       अगर ((state->rxsubchans & V4L2_TUNER_SUB_SAP) &&
		   (state->audmode == V4L2_TUNER_MODE_LANG1_LANG2 ||
		    state->audmode == V4L2_TUNER_MODE_LANG2)) अणु
			msp_ग_लिखो_dem(client, 0x20, 0x21);
	       पूर्ण अन्यथा अणु
			msp_ग_लिखो_dem(client, 0x20, 0x20);
	       पूर्ण
	पूर्ण

	msp34xxg_set_sources(client);
पूर्ण

व्योम msp_set_audmode(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));

	चयन (state->opmode) अणु
	हाल OPMODE_MANUAL:
	हाल OPMODE_AUTODETECT:
		msp3400c_set_audmode(client);
		अवरोध;
	हाल OPMODE_AUTOSELECT:
		msp34xxg_set_audmode(client);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक msp_detect_stereo(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state  = to_state(i2c_get_clientdata(client));

	चयन (state->opmode) अणु
	हाल OPMODE_MANUAL:
	हाल OPMODE_AUTODETECT:
		वापस msp3400c_detect_stereo(client);
	हाल OPMODE_AUTOSELECT:
		वापस msp34xxg_detect_stereo(client);
	पूर्ण
	वापस 0;
पूर्ण

