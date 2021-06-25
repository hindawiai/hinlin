<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>
#समावेश "tuner-i2c.h"
#समावेश "tda9887.h"


/* Chips:
   TDA9885 (PAL, NTSC)
   TDA9886 (PAL, SECAM, NTSC)
   TDA9887 (PAL, SECAM, NTSC, FM Radio)

   Used as part of several tuners
*/

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable verbose debug messages");

अटल DEFINE_MUTEX(tda9887_list_mutex);
अटल LIST_HEAD(hybrid_tuner_instance_list);

काष्ठा tda9887_priv अणु
	काष्ठा tuner_i2c_props i2c_props;
	काष्ठा list_head hybrid_tuner_instance_list;

	अचिन्हित अक्षर	   data[4];
	अचिन्हित पूर्णांक       config;
	अचिन्हित पूर्णांक       mode;
	अचिन्हित पूर्णांक       audmode;
	v4l2_std_id        std;

	bool               standby;
पूर्ण;

/* ---------------------------------------------------------------------- */

#घोषणा UNSET       (-1U)

काष्ठा tvnorm अणु
	v4l2_std_id       std;
	अक्षर              *name;
	अचिन्हित अक्षर     b;
	अचिन्हित अक्षर     c;
	अचिन्हित अक्षर     e;
पूर्ण;

/* ---------------------------------------------------------------------- */

//
// TDA defines
//

//// first reg (b)
#घोषणा cVideoTrapBypassOFF     0x00    // bit b0
#घोषणा cVideoTrapBypassON      0x01    // bit b0

#घोषणा cAutoMuteFmInactive     0x00    // bit b1
#घोषणा cAutoMuteFmActive       0x02    // bit b1

#घोषणा cIntercarrier           0x00    // bit b2
#घोषणा cQSS                    0x04    // bit b2

#घोषणा cPositiveAmTV           0x00    // bit b3:4
#घोषणा cFmRadio                0x08    // bit b3:4
#घोषणा cNegativeFmTV           0x10    // bit b3:4


#घोषणा cForcedMuteAudioON      0x20    // bit b5
#घोषणा cForcedMuteAudioOFF     0x00    // bit b5

#घोषणा cOutputPort1Active      0x00    // bit b6
#घोषणा cOutputPort1Inactive    0x40    // bit b6

#घोषणा cOutputPort2Active      0x00    // bit b7
#घोषणा cOutputPort2Inactive    0x80    // bit b7


//// second reg (c)
#घोषणा cDeemphasisOFF          0x00    // bit c5
#घोषणा cDeemphasisON           0x20    // bit c5

#घोषणा cDeemphasis75           0x00    // bit c6
#घोषणा cDeemphasis50           0x40    // bit c6

#घोषणा cAudioGain0             0x00    // bit c7
#घोषणा cAudioGain6             0x80    // bit c7

#घोषणा cTopMask                0x1f    // bit c0:4
#घोषणा cTopDefault		0x10	// bit c0:4

//// third reg (e)
#घोषणा cAudioIF_4_5             0x00    // bit e0:1
#घोषणा cAudioIF_5_5             0x01    // bit e0:1
#घोषणा cAudioIF_6_0             0x02    // bit e0:1
#घोषणा cAudioIF_6_5             0x03    // bit e0:1


#घोषणा cVideoIFMask		0x1c	// bit e2:4
/* Video IF selection in TV Mode (bit B3=0) */
#घोषणा cVideoIF_58_75           0x00    // bit e2:4
#घोषणा cVideoIF_45_75           0x04    // bit e2:4
#घोषणा cVideoIF_38_90           0x08    // bit e2:4
#घोषणा cVideoIF_38_00           0x0C    // bit e2:4
#घोषणा cVideoIF_33_90           0x10    // bit e2:4
#घोषणा cVideoIF_33_40           0x14    // bit e2:4
#घोषणा cRadioIF_45_75           0x18    // bit e2:4
#घोषणा cRadioIF_38_90           0x1C    // bit e2:4

/* IF1 selection in Radio Mode (bit B3=1) */
#घोषणा cRadioIF_33_30		0x00	// bit e2,4 (also 0x10,0x14)
#घोषणा cRadioIF_41_30		0x04	// bit e2,4

/* Output of AFC pin in radio mode when bit E7=1 */
#घोषणा cRadioAGC_SIF		0x00	// bit e3
#घोषणा cRadioAGC_FM		0x08	// bit e3

#घोषणा cTunerGainNormal         0x00    // bit e5
#घोषणा cTunerGainLow            0x20    // bit e5

#घोषणा cGating_18               0x00    // bit e6
#घोषणा cGating_36               0x40    // bit e6

#घोषणा cAgcOutON                0x80    // bit e7
#घोषणा cAgcOutOFF               0x00    // bit e7

/* ---------------------------------------------------------------------- */

अटल काष्ठा tvnorm tvnorms[] = अणु
	अणु
		.std   = V4L2_STD_PAL_BG | V4L2_STD_PAL_H | V4L2_STD_PAL_N,
		.name  = "PAL-BGHN",
		.b     = ( cNegativeFmTV  |
			   cQSS           ),
		.c     = ( cDeemphasisON  |
			   cDeemphasis50  |
			   cTopDefault),
		.e     = ( cGating_36     |
			   cAudioIF_5_5   |
			   cVideoIF_38_90 ),
	पूर्ण,अणु
		.std   = V4L2_STD_PAL_I,
		.name  = "PAL-I",
		.b     = ( cNegativeFmTV  |
			   cQSS           ),
		.c     = ( cDeemphasisON  |
			   cDeemphasis50  |
			   cTopDefault),
		.e     = ( cGating_36     |
			   cAudioIF_6_0   |
			   cVideoIF_38_90 ),
	पूर्ण,अणु
		.std   = V4L2_STD_PAL_DK,
		.name  = "PAL-DK",
		.b     = ( cNegativeFmTV  |
			   cQSS           ),
		.c     = ( cDeemphasisON  |
			   cDeemphasis50  |
			   cTopDefault),
		.e     = ( cGating_36     |
			   cAudioIF_6_5   |
			   cVideoIF_38_90 ),
	पूर्ण,अणु
		.std   = V4L2_STD_PAL_M | V4L2_STD_PAL_Nc,
		.name  = "PAL-M/Nc",
		.b     = ( cNegativeFmTV  |
			   cQSS           ),
		.c     = ( cDeemphasisON  |
			   cDeemphasis75  |
			   cTopDefault),
		.e     = ( cGating_36     |
			   cAudioIF_4_5   |
			   cVideoIF_45_75 ),
	पूर्ण,अणु
		.std   = V4L2_STD_SECAM_B | V4L2_STD_SECAM_G | V4L2_STD_SECAM_H,
		.name  = "SECAM-BGH",
		.b     = ( cNegativeFmTV  |
			   cQSS           ),
		.c     = ( cTopDefault),
		.e     = ( cAudioIF_5_5   |
			   cVideoIF_38_90 ),
	पूर्ण,अणु
		.std   = V4L2_STD_SECAM_L,
		.name  = "SECAM-L",
		.b     = ( cPositiveAmTV  |
			   cQSS           ),
		.c     = ( cTopDefault),
		.e     = ( cGating_36	  |
			   cAudioIF_6_5   |
			   cVideoIF_38_90 ),
	पूर्ण,अणु
		.std   = V4L2_STD_SECAM_LC,
		.name  = "SECAM-L'",
		.b     = ( cOutputPort2Inactive |
			   cPositiveAmTV  |
			   cQSS           ),
		.c     = ( cTopDefault),
		.e     = ( cGating_36	  |
			   cAudioIF_6_5   |
			   cVideoIF_33_90 ),
	पूर्ण,अणु
		.std   = V4L2_STD_SECAM_DK,
		.name  = "SECAM-DK",
		.b     = ( cNegativeFmTV  |
			   cQSS           ),
		.c     = ( cDeemphasisON  |
			   cDeemphasis50  |
			   cTopDefault),
		.e     = ( cGating_36     |
			   cAudioIF_6_5   |
			   cVideoIF_38_90 ),
	पूर्ण,अणु
		.std   = V4L2_STD_NTSC_M | V4L2_STD_NTSC_M_KR,
		.name  = "NTSC-M",
		.b     = ( cNegativeFmTV  |
			   cQSS           ),
		.c     = ( cDeemphasisON  |
			   cDeemphasis75  |
			   cTopDefault),
		.e     = ( cGating_36     |
			   cAudioIF_4_5   |
			   cVideoIF_45_75 ),
	पूर्ण,अणु
		.std   = V4L2_STD_NTSC_M_JP,
		.name  = "NTSC-M-JP",
		.b     = ( cNegativeFmTV  |
			   cQSS           ),
		.c     = ( cDeemphasisON  |
			   cDeemphasis50  |
			   cTopDefault),
		.e     = ( cGating_36     |
			   cAudioIF_4_5   |
			   cVideoIF_58_75 ),
	पूर्ण
पूर्ण;

अटल काष्ठा tvnorm radio_stereo = अणु
	.name = "Radio Stereo",
	.b    = ( cFmRadio       |
		  cQSS           ),
	.c    = ( cDeemphasisOFF |
		  cAudioGain6    |
		  cTopDefault),
	.e    = ( cTunerGainLow  |
		  cAudioIF_5_5   |
		  cRadioIF_38_90 ),
पूर्ण;

अटल काष्ठा tvnorm radio_mono = अणु
	.name = "Radio Mono",
	.b    = ( cFmRadio       |
		  cQSS           ),
	.c    = ( cDeemphasisON  |
		  cDeemphasis75  |
		  cTopDefault),
	.e    = ( cTunerGainLow  |
		  cAudioIF_5_5   |
		  cRadioIF_38_90 ),
पूर्ण;

/* ---------------------------------------------------------------------- */

अटल व्योम dump_पढ़ो_message(काष्ठा dvb_frontend *fe, अचिन्हित अक्षर *buf)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;

	अटल अक्षर *afc[16] = अणु
		"- 12.5 kHz",
		"- 37.5 kHz",
		"- 62.5 kHz",
		"- 87.5 kHz",
		"-112.5 kHz",
		"-137.5 kHz",
		"-162.5 kHz",
		"-187.5 kHz [min]",
		"+187.5 kHz [max]",
		"+162.5 kHz",
		"+137.5 kHz",
		"+112.5 kHz",
		"+ 87.5 kHz",
		"+ 62.5 kHz",
		"+ 37.5 kHz",
		"+ 12.5 kHz",
	पूर्ण;
	tuner_info("read: 0x%2x\n", buf[0]);
	tuner_info("  after power on : %s\n", (buf[0] & 0x01) ? "yes" : "no");
	tuner_info("  afc            : %s\n", afc[(buf[0] >> 1) & 0x0f]);
	tuner_info("  fmif level     : %s\n", (buf[0] & 0x20) ? "high" : "low");
	tuner_info("  afc window     : %s\n", (buf[0] & 0x40) ? "in" : "out");
	tuner_info("  vfi level      : %s\n", (buf[0] & 0x80) ? "high" : "low");
पूर्ण

अटल व्योम dump_ग_लिखो_message(काष्ठा dvb_frontend *fe, अचिन्हित अक्षर *buf)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;

	अटल अक्षर *sound[4] = अणु
		"AM/TV",
		"FM/radio",
		"FM/TV",
		"FM/radio"
	पूर्ण;
	अटल अक्षर *adjust[32] = अणु
		"-16", "-15", "-14", "-13", "-12", "-11", "-10", "-9",
		"-8",  "-7",  "-6",  "-5",  "-4",  "-3",  "-2",  "-1",
		"0",   "+1",  "+2",  "+3",  "+4",  "+5",  "+6",  "+7",
		"+8",  "+9",  "+10", "+11", "+12", "+13", "+14", "+15"
	पूर्ण;
	अटल अक्षर *deemph[4] = अणु
		"no", "no", "75", "50"
	पूर्ण;
	अटल अक्षर *carrier[4] = अणु
		"4.5 MHz",
		"5.5 MHz",
		"6.0 MHz",
		"6.5 MHz / AM"
	पूर्ण;
	अटल अक्षर *vअगर[8] = अणु
		"58.75 MHz",
		"45.75 MHz",
		"38.9 MHz",
		"38.0 MHz",
		"33.9 MHz",
		"33.4 MHz",
		"45.75 MHz + pin13",
		"38.9 MHz + pin13",
	पूर्ण;
	अटल अक्षर *rअगर[4] = अणु
		"44 MHz",
		"52 MHz",
		"52 MHz",
		"44 MHz",
	पूर्ण;

	tuner_info("write: byte B 0x%02x\n", buf[1]);
	tuner_info("  B0   video mode      : %s\n",
		   (buf[1] & 0x01) ? "video trap" : "sound trap");
	tuner_info("  B1   auto mute fm    : %s\n",
		   (buf[1] & 0x02) ? "yes" : "no");
	tuner_info("  B2   carrier mode    : %s\n",
		   (buf[1] & 0x04) ? "QSS" : "Intercarrier");
	tuner_info("  B3-4 tv sound/radio  : %s\n",
		   sound[(buf[1] & 0x18) >> 3]);
	tuner_info("  B5   force mute audio: %s\n",
		   (buf[1] & 0x20) ? "yes" : "no");
	tuner_info("  B6   output port 1   : %s\n",
		   (buf[1] & 0x40) ? "high (inactive)" : "low (active)");
	tuner_info("  B7   output port 2   : %s\n",
		   (buf[1] & 0x80) ? "high (inactive)" : "low (active)");

	tuner_info("write: byte C 0x%02x\n", buf[2]);
	tuner_info("  C0-4 top adjustment  : %s dB\n",
		   adjust[buf[2] & 0x1f]);
	tuner_info("  C5-6 de-emphasis     : %s\n",
		   deemph[(buf[2] & 0x60) >> 5]);
	tuner_info("  C7   audio gain      : %s\n",
		   (buf[2] & 0x80) ? "-6" : "0");

	tuner_info("write: byte E 0x%02x\n", buf[3]);
	tuner_info("  E0-1 sound carrier   : %s\n",
		   carrier[(buf[3] & 0x03)]);
	tuner_info("  E6   l pll gating   : %s\n",
		   (buf[3] & 0x40) ? "36" : "13");

	अगर (buf[1] & 0x08) अणु
		/* radio */
		tuner_info("  E2-4 video if        : %s\n",
			   rअगर[(buf[3] & 0x0c) >> 2]);
		tuner_info("  E7   vif agc output  : %s\n",
			   (buf[3] & 0x80)
			   ? ((buf[3] & 0x10) ? "fm-agc radio" :
						"sif-agc radio")
			   : "fm radio carrier afc");
	पूर्ण अन्यथा अणु
		/* video */
		tuner_info("  E2-4 video if        : %s\n",
			   vअगर[(buf[3] & 0x1c) >> 2]);
		tuner_info("  E5   tuner gain      : %s\n",
			   (buf[3] & 0x80)
			   ? ((buf[3] & 0x20) ? "external" : "normal")
			   : ((buf[3] & 0x20) ? "minimum"  : "normal"));
		tuner_info("  E7   vif agc output  : %s\n",
			   (buf[3] & 0x80) ? ((buf[3] & 0x20)
				? "pin3 port, pin22 vif agc out"
				: "pin22 port, pin3 vif acg ext in")
				: "pin3+pin22 port");
	पूर्ण
	tuner_info("--\n");
पूर्ण

/* ---------------------------------------------------------------------- */

अटल पूर्णांक tda9887_set_tvnorm(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;
	काष्ठा tvnorm *norm = शून्य;
	अक्षर *buf = priv->data;
	पूर्णांक i;

	अगर (priv->mode == V4L2_TUNER_RADIO) अणु
		अगर (priv->audmode == V4L2_TUNER_MODE_MONO)
			norm = &radio_mono;
		अन्यथा
			norm = &radio_stereo;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(tvnorms); i++) अणु
			अगर (tvnorms[i].std & priv->std) अणु
				norm = tvnorms+i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (शून्य == norm) अणु
		tuner_dbg("Unsupported tvnorm entry - audio muted\n");
		वापस -1;
	पूर्ण

	tuner_dbg("configure for: %s\n", norm->name);
	buf[1] = norm->b;
	buf[2] = norm->c;
	buf[3] = norm->e;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक port1  = UNSET;
अटल अचिन्हित पूर्णांक port2  = UNSET;
अटल अचिन्हित पूर्णांक qss    = UNSET;
अटल अचिन्हित पूर्णांक adjust = UNSET;

module_param(port1, पूर्णांक, 0644);
module_param(port2, पूर्णांक, 0644);
module_param(qss, पूर्णांक, 0644);
module_param(adjust, पूर्णांक, 0644);

अटल पूर्णांक tda9887_set_insmod(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;
	अक्षर *buf = priv->data;

	अगर (UNSET != port1) अणु
		अगर (port1)
			buf[1] |= cOutputPort1Inactive;
		अन्यथा
			buf[1] &= ~cOutputPort1Inactive;
	पूर्ण
	अगर (UNSET != port2) अणु
		अगर (port2)
			buf[1] |= cOutputPort2Inactive;
		अन्यथा
			buf[1] &= ~cOutputPort2Inactive;
	पूर्ण

	अगर (UNSET != qss) अणु
		अगर (qss)
			buf[1] |= cQSS;
		अन्यथा
			buf[1] &= ~cQSS;
	पूर्ण

	अगर (adjust < 0x20) अणु
		buf[2] &= ~cTopMask;
		buf[2] |= adjust;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tda9887_करो_config(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;
	अक्षर *buf = priv->data;

	अगर (priv->config & TDA9887_PORT1_ACTIVE)
		buf[1] &= ~cOutputPort1Inactive;
	अगर (priv->config & TDA9887_PORT1_INACTIVE)
		buf[1] |= cOutputPort1Inactive;
	अगर (priv->config & TDA9887_PORT2_ACTIVE)
		buf[1] &= ~cOutputPort2Inactive;
	अगर (priv->config & TDA9887_PORT2_INACTIVE)
		buf[1] |= cOutputPort2Inactive;

	अगर (priv->config & TDA9887_QSS)
		buf[1] |= cQSS;
	अगर (priv->config & TDA9887_INTERCARRIER)
		buf[1] &= ~cQSS;

	अगर (priv->config & TDA9887_AUTOMUTE)
		buf[1] |= cAutoMuteFmActive;
	अगर (priv->config & TDA9887_DEEMPHASIS_MASK) अणु
		buf[2] &= ~0x60;
		चयन (priv->config & TDA9887_DEEMPHASIS_MASK) अणु
		हाल TDA9887_DEEMPHASIS_NONE:
			buf[2] |= cDeemphasisOFF;
			अवरोध;
		हाल TDA9887_DEEMPHASIS_50:
			buf[2] |= cDeemphasisON | cDeemphasis50;
			अवरोध;
		हाल TDA9887_DEEMPHASIS_75:
			buf[2] |= cDeemphasisON | cDeemphasis75;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (priv->config & TDA9887_TOP_SET) अणु
		buf[2] &= ~cTopMask;
		buf[2] |= (priv->config >> 8) & cTopMask;
	पूर्ण
	अगर ((priv->config & TDA9887_INTERCARRIER_NTSC) &&
	    (priv->std & V4L2_STD_NTSC))
		buf[1] &= ~cQSS;
	अगर (priv->config & TDA9887_GATING_18)
		buf[3] &= ~cGating_36;

	अगर (priv->mode == V4L2_TUNER_RADIO) अणु
		अगर (priv->config & TDA9887_RIF_41_3) अणु
			buf[3] &= ~cVideoIFMask;
			buf[3] |= cRadioIF_41_30;
		पूर्ण
		अगर (priv->config & TDA9887_GAIN_NORMAL)
			buf[3] &= ~cTunerGainLow;
	पूर्ण

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल पूर्णांक tda9887_status(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;
	अचिन्हित अक्षर buf[1];
	पूर्णांक rc;

	rc = tuner_i2c_xfer_recv(&priv->i2c_props, buf, 1);
	अगर (rc != 1)
		tuner_info("i2c i/o error: rc == %d (should be 1)\n", rc);
	dump_पढ़ो_message(fe, buf);
	वापस 0;
पूर्ण

अटल व्योम tda9887_configure(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;
	पूर्णांक rc;

	स_रखो(priv->data,0,माप(priv->data));
	tda9887_set_tvnorm(fe);

	/* A note on the port settings:
	   These settings tend to depend on the specअगरics of the board.
	   By शेष they are set to inactive (bit value 1) by this driver,
	   overwriting any changes made by the tvnorm. This means that it
	   is the responsibility of the module using the tda9887 to set
	   these values in हाल of changes in the tvnorm.
	   In many हालs port 2 should be made active (0) when selecting
	   SECAM-L, and port 2 should reमुख्य inactive (1) क्रम SECAM-L'.

	   For the other standards the tda9887 application note says that
	   the ports should be set to active (0), but, again, that may
	   dअगरfer depending on the precise hardware configuration.
	 */
	priv->data[1] |= cOutputPort1Inactive;
	priv->data[1] |= cOutputPort2Inactive;

	tda9887_करो_config(fe);
	tda9887_set_insmod(fe);

	अगर (priv->standby)
		priv->data[1] |= cForcedMuteAudioON;

	tuner_dbg("writing: b=0x%02x c=0x%02x e=0x%02x\n",
		  priv->data[1], priv->data[2], priv->data[3]);
	अगर (debug > 1)
		dump_ग_लिखो_message(fe, priv->data);

	अगर (4 != (rc = tuner_i2c_xfer_send(&priv->i2c_props,priv->data,4)))
		tuner_info("i2c i/o error: rc == %d (should be 4)\n", rc);

	अगर (debug > 2) अणु
		msleep_पूर्णांकerruptible(1000);
		tda9887_status(fe);
	पूर्ण
पूर्ण

/* ---------------------------------------------------------------------- */

अटल व्योम tda9887_tuner_status(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;
	tuner_info("Data bytes: b=0x%02x c=0x%02x e=0x%02x\n",
		   priv->data[1], priv->data[2], priv->data[3]);
पूर्ण

अटल पूर्णांक tda9887_get_afc(काष्ठा dvb_frontend *fe, s32 *afc)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;
	अटल स्थिर पूर्णांक AFC_BITS_2_kHz[] = अणु
		-12500,  -37500,  -62500,  -97500,
		-112500, -137500, -162500, -187500,
		187500,  162500,  137500,  112500,
		97500 ,  62500,   37500 ,  12500
	पूर्ण;
	__u8 reg = 0;

	अगर (priv->mode != V4L2_TUNER_RADIO)
		वापस 0;
	अगर (1 == tuner_i2c_xfer_recv(&priv->i2c_props, &reg, 1))
		*afc = AFC_BITS_2_kHz[(reg >> 1) & 0x0f];
	वापस 0;
पूर्ण

अटल व्योम tda9887_standby(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;

	priv->standby = true;

	tda9887_configure(fe);
पूर्ण

अटल व्योम tda9887_set_params(काष्ठा dvb_frontend *fe,
			       काष्ठा analog_parameters *params)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;

	priv->standby = false;
	priv->mode    = params->mode;
	priv->audmode = params->audmode;
	priv->std     = params->std;
	tda9887_configure(fe);
पूर्ण

अटल पूर्णांक tda9887_set_config(काष्ठा dvb_frontend *fe, व्योम *priv_cfg)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;

	priv->config = *(अचिन्हित पूर्णांक *)priv_cfg;
	tda9887_configure(fe);

	वापस 0;
पूर्ण

अटल व्योम tda9887_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda9887_priv *priv = fe->analog_demod_priv;

	mutex_lock(&tda9887_list_mutex);

	अगर (priv)
		hybrid_tuner_release_state(priv);

	mutex_unlock(&tda9887_list_mutex);

	fe->analog_demod_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा analog_demod_ops tda9887_ops = अणु
	.info		= अणु
		.name	= "tda9887",
	पूर्ण,
	.set_params     = tda9887_set_params,
	.standby        = tda9887_standby,
	.tuner_status   = tda9887_tuner_status,
	.get_afc        = tda9887_get_afc,
	.release        = tda9887_release,
	.set_config     = tda9887_set_config,
पूर्ण;

काष्ठा dvb_frontend *tda9887_attach(काष्ठा dvb_frontend *fe,
				    काष्ठा i2c_adapter *i2c_adap,
				    u8 i2c_addr)
अणु
	काष्ठा tda9887_priv *priv = शून्य;
	पूर्णांक instance;

	mutex_lock(&tda9887_list_mutex);

	instance = hybrid_tuner_request_state(काष्ठा tda9887_priv, priv,
					      hybrid_tuner_instance_list,
					      i2c_adap, i2c_addr, "tda9887");
	चयन (instance) अणु
	हाल 0:
		mutex_unlock(&tda9887_list_mutex);
		वापस शून्य;
	हाल 1:
		fe->analog_demod_priv = priv;
		priv->standby = true;
		tuner_info("tda988[5/6/7] found\n");
		अवरोध;
	शेष:
		fe->analog_demod_priv = priv;
		अवरोध;
	पूर्ण

	mutex_unlock(&tda9887_list_mutex);

	स_नकल(&fe->ops.analog_ops, &tda9887_ops,
	       माप(काष्ठा analog_demod_ops));

	वापस fe;
पूर्ण
EXPORT_SYMBOL_GPL(tda9887_attach);

MODULE_LICENSE("GPL");
