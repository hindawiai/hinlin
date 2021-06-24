<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cx88x-audio.c - Conexant CX23880/23881 audio करोwnstream driver driver
 *
 *  (c) 2001 Michael Eskin, Tom Zakrajsek [Winकरोws version]
 *  (c) 2002 Yurij Sysoev <yurij@naturesoft.net>
 *  (c) 2003 Gerd Knorr <kraxel@bytesex.org>
 *
 * -----------------------------------------------------------------------
 *
 * Lot of vooकरोo here.  Even the data sheet करोesn't help to
 * understand what is going on here, the करोcumentation क्रम the audio
 * part of the cx2388x chip is *very* bad.
 *
 * Some of this comes from party करोne linux driver sources I got from
 * [unकरोcumented].
 *
 * Some comes from the dscaler sources, one of the dscaler driver guy works
 * क्रम Conexant ...
 *
 * -----------------------------------------------------------------------
 */

#समावेश "cx88.h"

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/poll.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/ioport.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>

अटल अचिन्हित पूर्णांक audio_debug;
module_param(audio_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(audio_debug, "enable debug messages [audio]");

अटल अचिन्हित पूर्णांक always_analog;
module_param(always_analog, पूर्णांक, 0644);
MODULE_PARM_DESC(always_analog, "force analog audio out");

अटल अचिन्हित पूर्णांक radio_deemphasis;
module_param(radio_deemphasis, पूर्णांक, 0644);
MODULE_PARM_DESC(radio_deemphasis,
		 "Radio deemphasis time constant, 0=None, 1=50us (elsewhere), 2=75us (USA)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु				\
	अगर (audio_debug)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: tvaudio:" fmt),		\
			__func__, ##arg);				\
पूर्ण जबतक (0)
/* ----------------------------------------------------------- */

अटल स्थिर अक्षर * स्थिर aud_ctl_names[64] = अणु
	[EN_BTSC_FORCE_MONO] = "BTSC_FORCE_MONO",
	[EN_BTSC_FORCE_STEREO] = "BTSC_FORCE_STEREO",
	[EN_BTSC_FORCE_SAP] = "BTSC_FORCE_SAP",
	[EN_BTSC_AUTO_STEREO] = "BTSC_AUTO_STEREO",
	[EN_BTSC_AUTO_SAP] = "BTSC_AUTO_SAP",
	[EN_A2_FORCE_MONO1] = "A2_FORCE_MONO1",
	[EN_A2_FORCE_MONO2] = "A2_FORCE_MONO2",
	[EN_A2_FORCE_STEREO] = "A2_FORCE_STEREO",
	[EN_A2_AUTO_MONO2] = "A2_AUTO_MONO2",
	[EN_A2_AUTO_STEREO] = "A2_AUTO_STEREO",
	[EN_EIAJ_FORCE_MONO1] = "EIAJ_FORCE_MONO1",
	[EN_EIAJ_FORCE_MONO2] = "EIAJ_FORCE_MONO2",
	[EN_EIAJ_FORCE_STEREO] = "EIAJ_FORCE_STEREO",
	[EN_EIAJ_AUTO_MONO2] = "EIAJ_AUTO_MONO2",
	[EN_EIAJ_AUTO_STEREO] = "EIAJ_AUTO_STEREO",
	[EN_NICAM_FORCE_MONO1] = "NICAM_FORCE_MONO1",
	[EN_NICAM_FORCE_MONO2] = "NICAM_FORCE_MONO2",
	[EN_NICAM_FORCE_STEREO] = "NICAM_FORCE_STEREO",
	[EN_NICAM_AUTO_MONO2] = "NICAM_AUTO_MONO2",
	[EN_NICAM_AUTO_STEREO] = "NICAM_AUTO_STEREO",
	[EN_FMRADIO_FORCE_MONO] = "FMRADIO_FORCE_MONO",
	[EN_FMRADIO_FORCE_STEREO] = "FMRADIO_FORCE_STEREO",
	[EN_FMRADIO_AUTO_STEREO] = "FMRADIO_AUTO_STEREO",
पूर्ण;

काष्ठा rlist अणु
	u32 reg;
	u32 val;
पूर्ण;

अटल व्योम set_audio_रेजिस्टरs(काष्ठा cx88_core *core, स्थिर काष्ठा rlist *l)
अणु
	पूर्णांक i;

	क्रम (i = 0; l[i].reg; i++) अणु
		चयन (l[i].reg) अणु
		हाल AUD_PDF_DDS_CNST_BYTE2:
		हाल AUD_PDF_DDS_CNST_BYTE1:
		हाल AUD_PDF_DDS_CNST_BYTE0:
		हाल AUD_QAM_MODE:
		हाल AUD_PHACC_FREQ_8MSB:
		हाल AUD_PHACC_FREQ_8LSB:
			cx_ग_लिखोb(l[i].reg, l[i].val);
			अवरोध;
		शेष:
			cx_ग_लिखो(l[i].reg, l[i].val);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम set_audio_start(काष्ठा cx88_core *core, u32 mode)
अणु
	/* mute */
	cx_ग_लिखो(AUD_VOL_CTL, (1 << 6));

	/* start programming */
	cx_ग_लिखो(AUD_INIT, mode);
	cx_ग_लिखो(AUD_INIT_LD, 0x0001);
	cx_ग_लिखो(AUD_SOFT_RESET, 0x0001);
पूर्ण

अटल व्योम set_audio_finish(काष्ठा cx88_core *core, u32 ctl)
अणु
	u32 volume;

	/* restart dma; This aव्योमs buzz in NICAM and is good in others  */
	cx88_stop_audio_dma(core);
	cx_ग_लिखो(AUD_RATE_THRES_DMD, 0x000000C0);
	cx88_start_audio_dma(core);

	अगर (core->board.mpeg & CX88_MPEG_BLACKBIRD) अणु
		cx_ग_लिखो(AUD_I2SINPUTCNTL, 4);
		cx_ग_लिखो(AUD_BAUDRATE, 1);
		/*
		 * 'pass-thru mode': this enables the i2s
		 * output to the mpeg encoder
		 */
		cx_set(AUD_CTL, EN_I2SOUT_ENABLE);
		cx_ग_लिखो(AUD_I2SOUTPUTCNTL, 1);
		cx_ग_लिखो(AUD_I2SCNTL, 0);
		/* cx_ग_लिखो(AUD_APB_IN_RATE_ADJ, 0); */
	पूर्ण
	अगर ((always_analog) || (!(core->board.mpeg & CX88_MPEG_BLACKBIRD))) अणु
		ctl |= EN_DAC_ENABLE;
		cx_ग_लिखो(AUD_CTL, ctl);
	पूर्ण

	/* finish programming */
	cx_ग_लिखो(AUD_SOFT_RESET, 0x0000);

	/* unmute */
	volume = cx_sपढ़ो(SHADOW_AUD_VOL_CTL);
	cx_sग_लिखो(SHADOW_AUD_VOL_CTL, AUD_VOL_CTL, volume);

	core->last_change = jअगरfies;
पूर्ण

/* ----------------------------------------------------------- */

अटल व्योम set_audio_standard_BTSC(काष्ठा cx88_core *core, अचिन्हित पूर्णांक sap,
				    u32 mode)
अणु
	अटल स्थिर काष्ठा rlist btsc[] = अणु
		अणुAUD_AFE_12DB_EN, 0x00000001पूर्ण,
		अणुAUD_OUT1_SEL, 0x00000013पूर्ण,
		अणुAUD_OUT1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_POLY0_DDS_CONSTANT, 0x0012010cपूर्ण,
		अणुAUD_DMD_RA_DDS, 0x00c3e7aaपूर्ण,
		अणुAUD_DBX_IN_GAIN, 0x00004734पूर्ण,
		अणुAUD_DBX_WBE_GAIN, 0x00004640पूर्ण,
		अणुAUD_DBX_SE_GAIN, 0x00008d31पूर्ण,
		अणुAUD_DCOC_0_SRC, 0x0000001aपूर्ण,
		अणुAUD_IIR1_4_SEL, 0x00000021पूर्ण,
		अणुAUD_DCOC_PASS_IN, 0x00000003पूर्ण,
		अणुAUD_DCOC_0_SHIFT_IN0, 0x0000000aपूर्ण,
		अणुAUD_DCOC_0_SHIFT_IN1, 0x00000008पूर्ण,
		अणुAUD_DCOC_1_SHIFT_IN0, 0x0000000aपूर्ण,
		अणुAUD_DCOC_1_SHIFT_IN1, 0x00000008पूर्ण,
		अणुAUD_DN0_FREQ, 0x0000283bपूर्ण,
		अणुAUD_DN2_SRC_SEL, 0x00000008पूर्ण,
		अणुAUD_DN2_FREQ, 0x00003000पूर्ण,
		अणुAUD_DN2_AFC, 0x00000002पूर्ण,
		अणुAUD_DN2_SHFT, 0x00000000पूर्ण,
		अणुAUD_IIR2_2_SEL, 0x00000020पूर्ण,
		अणुAUD_IIR2_2_SHIFT, 0x00000000पूर्ण,
		अणुAUD_IIR2_3_SEL, 0x0000001fपूर्ण,
		अणुAUD_IIR2_3_SHIFT, 0x00000000पूर्ण,
		अणुAUD_CRDC1_SRC_SEL, 0x000003ceपूर्ण,
		अणुAUD_CRDC1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_CORDIC_SHIFT_1, 0x00000007पूर्ण,
		अणुAUD_DCOC_1_SRC, 0x0000001bपूर्ण,
		अणुAUD_DCOC1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_RDSI_SEL, 0x00000008पूर्ण,
		अणुAUD_RDSQ_SEL, 0x00000008पूर्ण,
		अणुAUD_RDSI_SHIFT, 0x00000000पूर्ण,
		अणुAUD_RDSQ_SHIFT, 0x00000000पूर्ण,
		अणुAUD_POLYPH80SCALEFAC, 0x00000003पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा rlist btsc_sap[] = अणु
		अणुAUD_AFE_12DB_EN, 0x00000001पूर्ण,
		अणुAUD_DBX_IN_GAIN, 0x00007200पूर्ण,
		अणुAUD_DBX_WBE_GAIN, 0x00006200पूर्ण,
		अणुAUD_DBX_SE_GAIN, 0x00006200पूर्ण,
		अणुAUD_IIR1_1_SEL, 0x00000000पूर्ण,
		अणुAUD_IIR1_3_SEL, 0x00000001पूर्ण,
		अणुAUD_DN1_SRC_SEL, 0x00000007पूर्ण,
		अणुAUD_IIR1_4_SHIFT, 0x00000006पूर्ण,
		अणुAUD_IIR2_1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_IIR2_2_SHIFT, 0x00000000पूर्ण,
		अणुAUD_IIR3_0_SHIFT, 0x00000000पूर्ण,
		अणुAUD_IIR3_1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_IIR3_0_SEL, 0x0000000dपूर्ण,
		अणुAUD_IIR3_1_SEL, 0x0000000eपूर्ण,
		अणुAUD_DEEMPH1_SRC_SEL, 0x00000014पूर्ण,
		अणुAUD_DEEMPH1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DEEMPH1_G0, 0x00004000पूर्ण,
		अणुAUD_DEEMPH1_A0, 0x00000000पूर्ण,
		अणुAUD_DEEMPH1_B0, 0x00000000पूर्ण,
		अणुAUD_DEEMPH1_A1, 0x00000000पूर्ण,
		अणुAUD_DEEMPH1_B1, 0x00000000पूर्ण,
		अणुAUD_OUT0_SEL, 0x0000003fपूर्ण,
		अणुAUD_OUT1_SEL, 0x0000003fपूर्ण,
		अणुAUD_DN1_AFC, 0x00000002पूर्ण,
		अणुAUD_DCOC_0_SHIFT_IN0, 0x0000000aपूर्ण,
		अणुAUD_DCOC_0_SHIFT_IN1, 0x00000008पूर्ण,
		अणुAUD_DCOC_1_SHIFT_IN0, 0x0000000aपूर्ण,
		अणुAUD_DCOC_1_SHIFT_IN1, 0x00000008पूर्ण,
		अणुAUD_IIR1_0_SEL, 0x0000001dपूर्ण,
		अणुAUD_IIR1_2_SEL, 0x0000001eपूर्ण,
		अणुAUD_IIR2_1_SEL, 0x00000002पूर्ण,
		अणुAUD_IIR2_2_SEL, 0x00000004पूर्ण,
		अणुAUD_IIR3_2_SEL, 0x0000000fपूर्ण,
		अणुAUD_DCOC2_SHIFT, 0x00000001पूर्ण,
		अणुAUD_IIR3_2_SHIFT, 0x00000001पूर्ण,
		अणुAUD_DEEMPH0_SRC_SEL, 0x00000014पूर्ण,
		अणुAUD_CORDIC_SHIFT_1, 0x00000006पूर्ण,
		अणुAUD_POLY0_DDS_CONSTANT, 0x000e4db2पूर्ण,
		अणुAUD_DMD_RA_DDS, 0x00f696e6पूर्ण,
		अणुAUD_IIR2_3_SEL, 0x00000025पूर्ण,
		अणुAUD_IIR1_4_SEL, 0x00000021पूर्ण,
		अणुAUD_DN1_FREQ, 0x0000c965पूर्ण,
		अणुAUD_DCOC_PASS_IN, 0x00000003पूर्ण,
		अणुAUD_DCOC_0_SRC, 0x0000001aपूर्ण,
		अणुAUD_DCOC_1_SRC, 0x0000001bपूर्ण,
		अणुAUD_DCOC1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_RDSI_SEL, 0x00000009पूर्ण,
		अणुAUD_RDSQ_SEL, 0x00000009पूर्ण,
		अणुAUD_RDSI_SHIFT, 0x00000000पूर्ण,
		अणुAUD_RDSQ_SHIFT, 0x00000000पूर्ण,
		अणुAUD_POLYPH80SCALEFAC, 0x00000003पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	mode |= EN_FMRADIO_EN_RDS;

	अगर (sap) अणु
		dprपूर्णांकk("%s SAP (status: unknown)\n", __func__);
		set_audio_start(core, SEL_SAP);
		set_audio_रेजिस्टरs(core, btsc_sap);
		set_audio_finish(core, mode);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("%s (status: known-good)\n", __func__);
		set_audio_start(core, SEL_BTSC);
		set_audio_रेजिस्टरs(core, btsc);
		set_audio_finish(core, mode);
	पूर्ण
पूर्ण

अटल व्योम set_audio_standard_NICAM(काष्ठा cx88_core *core, u32 mode)
अणु
	अटल स्थिर काष्ठा rlist nicam_l[] = अणु
		अणुAUD_AFE_12DB_EN, 0x00000001पूर्ण,
		अणुAUD_RATE_ADJ1, 0x00000060पूर्ण,
		अणुAUD_RATE_ADJ2, 0x000000F9पूर्ण,
		अणुAUD_RATE_ADJ3, 0x000001CCपूर्ण,
		अणुAUD_RATE_ADJ4, 0x000002B3पूर्ण,
		अणुAUD_RATE_ADJ5, 0x00000726पूर्ण,
		अणुAUD_DEEMPHDENOM1_R, 0x0000F3D0पूर्ण,
		अणुAUD_DEEMPHDENOM2_R, 0x00000000पूर्ण,
		अणुAUD_ERRLOGPERIOD_R, 0x00000064पूर्ण,
		अणुAUD_ERRINTRPTTHSHLD1_R, 0x00000FFFपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD2_R, 0x0000001Fपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD3_R, 0x0000000Fपूर्ण,
		अणुAUD_POLYPH80SCALEFAC, 0x00000003पूर्ण,
		अणुAUD_DMD_RA_DDS, 0x00C00000पूर्ण,
		अणुAUD_PLL_INT, 0x0000001Eपूर्ण,
		अणुAUD_PLL_DDS, 0x00000000पूर्ण,
		अणुAUD_PLL_FRAC, 0x0000E542पूर्ण,
		अणुAUD_START_TIMER, 0x00000000पूर्ण,
		अणुAUD_DEEMPHNUMER1_R, 0x000353DEपूर्ण,
		अणुAUD_DEEMPHNUMER2_R, 0x000001B1पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE2, 0x06पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE1, 0x82पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE0, 0x12पूर्ण,
		अणुAUD_QAM_MODE, 0x05पूर्ण,
		अणुAUD_PHACC_FREQ_8MSB, 0x34पूर्ण,
		अणुAUD_PHACC_FREQ_8LSB, 0x4Cपूर्ण,
		अणुAUD_DEEMPHGAIN_R, 0x00006680पूर्ण,
		अणुAUD_RATE_THRES_DMD, 0x000000C0पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा rlist nicam_bgdki_common[] = अणु
		अणुAUD_AFE_12DB_EN, 0x00000001पूर्ण,
		अणुAUD_RATE_ADJ1, 0x00000010पूर्ण,
		अणुAUD_RATE_ADJ2, 0x00000040पूर्ण,
		अणुAUD_RATE_ADJ3, 0x00000100पूर्ण,
		अणुAUD_RATE_ADJ4, 0x00000400पूर्ण,
		अणुAUD_RATE_ADJ5, 0x00001000पूर्ण,
		अणुAUD_ERRLOGPERIOD_R, 0x00000fffपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD1_R, 0x000003ffपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD2_R, 0x000000ffपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD3_R, 0x0000003fपूर्ण,
		अणुAUD_POLYPH80SCALEFAC, 0x00000003पूर्ण,
		अणुAUD_DEEMPHGAIN_R, 0x000023c2पूर्ण,
		अणुAUD_DEEMPHNUMER1_R, 0x0002a7bcपूर्ण,
		अणुAUD_DEEMPHNUMER2_R, 0x0003023eपूर्ण,
		अणुAUD_DEEMPHDENOM1_R, 0x0000f3d0पूर्ण,
		अणुAUD_DEEMPHDENOM2_R, 0x00000000पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE2, 0x06पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE1, 0x82पूर्ण,
		अणुAUD_QAM_MODE, 0x05पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा rlist nicam_i[] = अणु
		अणुAUD_PDF_DDS_CNST_BYTE0, 0x12पूर्ण,
		अणुAUD_PHACC_FREQ_8MSB, 0x3aपूर्ण,
		अणुAUD_PHACC_FREQ_8LSB, 0x93पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा rlist nicam_शेष[] = अणु
		अणुAUD_PDF_DDS_CNST_BYTE0, 0x16पूर्ण,
		अणुAUD_PHACC_FREQ_8MSB, 0x34पूर्ण,
		अणुAUD_PHACC_FREQ_8LSB, 0x4cपूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	set_audio_start(core, SEL_NICAM);
	चयन (core->tvaudio) अणु
	हाल WW_L:
		dprपूर्णांकk("%s SECAM-L NICAM (status: devel)\n", __func__);
		set_audio_रेजिस्टरs(core, nicam_l);
		अवरोध;
	हाल WW_I:
		dprपूर्णांकk("%s PAL-I NICAM (status: known-good)\n", __func__);
		set_audio_रेजिस्टरs(core, nicam_bgdki_common);
		set_audio_रेजिस्टरs(core, nicam_i);
		अवरोध;
	हाल WW_NONE:
	हाल WW_BTSC:
	हाल WW_BG:
	हाल WW_DK:
	हाल WW_EIAJ:
	हाल WW_I2SPT:
	हाल WW_FM:
	हाल WW_I2SADC:
	हाल WW_M:
		dprपूर्णांकk("%s PAL-BGDK NICAM (status: known-good)\n", __func__);
		set_audio_रेजिस्टरs(core, nicam_bgdki_common);
		set_audio_रेजिस्टरs(core, nicam_शेष);
		अवरोध;
	पूर्ण

	mode |= EN_DMTRX_LR | EN_DMTRX_BYPASS;
	set_audio_finish(core, mode);
पूर्ण

अटल व्योम set_audio_standard_A2(काष्ठा cx88_core *core, u32 mode)
अणु
	अटल स्थिर काष्ठा rlist a2_bgdk_common[] = अणु
		अणुAUD_ERRLOGPERIOD_R, 0x00000064पूर्ण,
		अणुAUD_ERRINTRPTTHSHLD1_R, 0x00000fffपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD2_R, 0x0000001fपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD3_R, 0x0000000fपूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE2, 0x06पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE1, 0x82पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE0, 0x12पूर्ण,
		अणुAUD_QAM_MODE, 0x05पूर्ण,
		अणुAUD_PHACC_FREQ_8MSB, 0x34पूर्ण,
		अणुAUD_PHACC_FREQ_8LSB, 0x4cपूर्ण,
		अणुAUD_RATE_ADJ1, 0x00000100पूर्ण,
		अणुAUD_RATE_ADJ2, 0x00000200पूर्ण,
		अणुAUD_RATE_ADJ3, 0x00000300पूर्ण,
		अणुAUD_RATE_ADJ4, 0x00000400पूर्ण,
		अणुAUD_RATE_ADJ5, 0x00000500पूर्ण,
		अणुAUD_THR_FR, 0x00000000पूर्ण,
		अणुAAGC_HYST, 0x0000001aपूर्ण,
		अणुAUD_PILOT_BQD_1_K0, 0x0000755bपूर्ण,
		अणुAUD_PILOT_BQD_1_K1, 0x00551340पूर्ण,
		अणुAUD_PILOT_BQD_1_K2, 0x006d30beपूर्ण,
		अणुAUD_PILOT_BQD_1_K3, 0xffd394afपूर्ण,
		अणुAUD_PILOT_BQD_1_K4, 0x00400000पूर्ण,
		अणुAUD_PILOT_BQD_2_K0, 0x00040000पूर्ण,
		अणुAUD_PILOT_BQD_2_K1, 0x002a4841पूर्ण,
		अणुAUD_PILOT_BQD_2_K2, 0x00400000पूर्ण,
		अणुAUD_PILOT_BQD_2_K3, 0x00000000पूर्ण,
		अणुAUD_PILOT_BQD_2_K4, 0x00000000पूर्ण,
		अणुAUD_MODE_CHG_TIMER, 0x00000040पूर्ण,
		अणुAUD_AFE_12DB_EN, 0x00000001पूर्ण,
		अणुAUD_CORDIC_SHIFT_0, 0x00000007पूर्ण,
		अणुAUD_CORDIC_SHIFT_1, 0x00000007पूर्ण,
		अणुAUD_DEEMPH0_G0, 0x00000380पूर्ण,
		अणुAUD_DEEMPH1_G0, 0x00000380पूर्ण,
		अणुAUD_DCOC_0_SRC, 0x0000001aपूर्ण,
		अणुAUD_DCOC0_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DCOC_0_SHIFT_IN0, 0x0000000aपूर्ण,
		अणुAUD_DCOC_0_SHIFT_IN1, 0x00000008पूर्ण,
		अणुAUD_DCOC_PASS_IN, 0x00000003पूर्ण,
		अणुAUD_IIR3_0_SEL, 0x00000021पूर्ण,
		अणुAUD_DN2_AFC, 0x00000002पूर्ण,
		अणुAUD_DCOC_1_SRC, 0x0000001bपूर्ण,
		अणुAUD_DCOC1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DCOC_1_SHIFT_IN0, 0x0000000aपूर्ण,
		अणुAUD_DCOC_1_SHIFT_IN1, 0x00000008पूर्ण,
		अणुAUD_IIR3_1_SEL, 0x00000023पूर्ण,
		अणुAUD_RDSI_SEL, 0x00000017पूर्ण,
		अणुAUD_RDSI_SHIFT, 0x00000000पूर्ण,
		अणुAUD_RDSQ_SEL, 0x00000017पूर्ण,
		अणुAUD_RDSQ_SHIFT, 0x00000000पूर्ण,
		अणुAUD_PLL_INT, 0x0000001eपूर्ण,
		अणुAUD_PLL_DDS, 0x00000000पूर्ण,
		अणुAUD_PLL_FRAC, 0x0000e542पूर्ण,
		अणुAUD_POLYPH80SCALEFAC, 0x00000001पूर्ण,
		अणुAUD_START_TIMER, 0x00000000पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा rlist a2_bg[] = अणु
		अणुAUD_DMD_RA_DDS, 0x002a4f2fपूर्ण,
		अणुAUD_C1_UP_THR, 0x00007000पूर्ण,
		अणुAUD_C1_LO_THR, 0x00005400पूर्ण,
		अणुAUD_C2_UP_THR, 0x00005400पूर्ण,
		अणुAUD_C2_LO_THR, 0x00003000पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा rlist a2_dk[] = अणु
		अणुAUD_DMD_RA_DDS, 0x002a4f2fपूर्ण,
		अणुAUD_C1_UP_THR, 0x00007000पूर्ण,
		अणुAUD_C1_LO_THR, 0x00005400पूर्ण,
		अणुAUD_C2_UP_THR, 0x00005400पूर्ण,
		अणुAUD_C2_LO_THR, 0x00003000पूर्ण,
		अणुAUD_DN0_FREQ, 0x00003a1cपूर्ण,
		अणुAUD_DN2_FREQ, 0x0000d2e0पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा rlist a1_i[] = अणु
		अणुAUD_ERRLOGPERIOD_R, 0x00000064पूर्ण,
		अणुAUD_ERRINTRPTTHSHLD1_R, 0x00000fffपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD2_R, 0x0000001fपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD3_R, 0x0000000fपूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE2, 0x06पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE1, 0x82पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE0, 0x12पूर्ण,
		अणुAUD_QAM_MODE, 0x05पूर्ण,
		अणुAUD_PHACC_FREQ_8MSB, 0x3aपूर्ण,
		अणुAUD_PHACC_FREQ_8LSB, 0x93पूर्ण,
		अणुAUD_DMD_RA_DDS, 0x002a4f2fपूर्ण,
		अणुAUD_PLL_INT, 0x0000001eपूर्ण,
		अणुAUD_PLL_DDS, 0x00000004पूर्ण,
		अणुAUD_PLL_FRAC, 0x0000e542पूर्ण,
		अणुAUD_RATE_ADJ1, 0x00000100पूर्ण,
		अणुAUD_RATE_ADJ2, 0x00000200पूर्ण,
		अणुAUD_RATE_ADJ3, 0x00000300पूर्ण,
		अणुAUD_RATE_ADJ4, 0x00000400पूर्ण,
		अणुAUD_RATE_ADJ5, 0x00000500पूर्ण,
		अणुAUD_THR_FR, 0x00000000पूर्ण,
		अणुAUD_PILOT_BQD_1_K0, 0x0000755bपूर्ण,
		अणुAUD_PILOT_BQD_1_K1, 0x00551340पूर्ण,
		अणुAUD_PILOT_BQD_1_K2, 0x006d30beपूर्ण,
		अणुAUD_PILOT_BQD_1_K3, 0xffd394afपूर्ण,
		अणुAUD_PILOT_BQD_1_K4, 0x00400000पूर्ण,
		अणुAUD_PILOT_BQD_2_K0, 0x00040000पूर्ण,
		अणुAUD_PILOT_BQD_2_K1, 0x002a4841पूर्ण,
		अणुAUD_PILOT_BQD_2_K2, 0x00400000पूर्ण,
		अणुAUD_PILOT_BQD_2_K3, 0x00000000पूर्ण,
		अणुAUD_PILOT_BQD_2_K4, 0x00000000पूर्ण,
		अणुAUD_MODE_CHG_TIMER, 0x00000060पूर्ण,
		अणुAUD_AFE_12DB_EN, 0x00000001पूर्ण,
		अणुAAGC_HYST, 0x0000000aपूर्ण,
		अणुAUD_CORDIC_SHIFT_0, 0x00000007पूर्ण,
		अणुAUD_CORDIC_SHIFT_1, 0x00000007पूर्ण,
		अणुAUD_C1_UP_THR, 0x00007000पूर्ण,
		अणुAUD_C1_LO_THR, 0x00005400पूर्ण,
		अणुAUD_C2_UP_THR, 0x00005400पूर्ण,
		अणुAUD_C2_LO_THR, 0x00003000पूर्ण,
		अणुAUD_DCOC_0_SRC, 0x0000001aपूर्ण,
		अणुAUD_DCOC0_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DCOC_0_SHIFT_IN0, 0x0000000aपूर्ण,
		अणुAUD_DCOC_0_SHIFT_IN1, 0x00000008पूर्ण,
		अणुAUD_DCOC_PASS_IN, 0x00000003पूर्ण,
		अणुAUD_IIR3_0_SEL, 0x00000021पूर्ण,
		अणुAUD_DN2_AFC, 0x00000002पूर्ण,
		अणुAUD_DCOC_1_SRC, 0x0000001bपूर्ण,
		अणुAUD_DCOC1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DCOC_1_SHIFT_IN0, 0x0000000aपूर्ण,
		अणुAUD_DCOC_1_SHIFT_IN1, 0x00000008पूर्ण,
		अणुAUD_IIR3_1_SEL, 0x00000023पूर्ण,
		अणुAUD_DN0_FREQ, 0x000035a3पूर्ण,
		अणुAUD_DN2_FREQ, 0x000029c7पूर्ण,
		अणुAUD_CRDC0_SRC_SEL, 0x00000511पूर्ण,
		अणुAUD_IIR1_0_SEL, 0x00000001पूर्ण,
		अणुAUD_IIR1_1_SEL, 0x00000000पूर्ण,
		अणुAUD_IIR3_2_SEL, 0x00000003पूर्ण,
		अणुAUD_IIR3_2_SHIFT, 0x00000000पूर्ण,
		अणुAUD_IIR3_0_SEL, 0x00000002पूर्ण,
		अणुAUD_IIR2_0_SEL, 0x00000021पूर्ण,
		अणुAUD_IIR2_0_SHIFT, 0x00000002पूर्ण,
		अणुAUD_DEEMPH0_SRC_SEL, 0x0000000bपूर्ण,
		अणुAUD_DEEMPH1_SRC_SEL, 0x0000000bपूर्ण,
		अणुAUD_POLYPH80SCALEFAC, 0x00000001पूर्ण,
		अणुAUD_START_TIMER, 0x00000000पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा rlist am_l[] = अणु
		अणुAUD_ERRLOGPERIOD_R, 0x00000064पूर्ण,
		अणुAUD_ERRINTRPTTHSHLD1_R, 0x00000FFFपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD2_R, 0x0000001Fपूर्ण,
		अणुAUD_ERRINTRPTTHSHLD3_R, 0x0000000Fपूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE2, 0x48पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE1, 0x3Dपूर्ण,
		अणुAUD_QAM_MODE, 0x00पूर्ण,
		अणुAUD_PDF_DDS_CNST_BYTE0, 0xf5पूर्ण,
		अणुAUD_PHACC_FREQ_8MSB, 0x3aपूर्ण,
		अणुAUD_PHACC_FREQ_8LSB, 0x4aपूर्ण,
		अणुAUD_DEEMPHGAIN_R, 0x00006680पूर्ण,
		अणुAUD_DEEMPHNUMER1_R, 0x000353DEपूर्ण,
		अणुAUD_DEEMPHNUMER2_R, 0x000001B1पूर्ण,
		अणुAUD_DEEMPHDENOM1_R, 0x0000F3D0पूर्ण,
		अणुAUD_DEEMPHDENOM2_R, 0x00000000पूर्ण,
		अणुAUD_FM_MODE_ENABLE, 0x00000007पूर्ण,
		अणुAUD_POLYPH80SCALEFAC, 0x00000003पूर्ण,
		अणुAUD_AFE_12DB_EN, 0x00000001पूर्ण,
		अणुAAGC_GAIN, 0x00000000पूर्ण,
		अणुAAGC_HYST, 0x00000018पूर्ण,
		अणुAAGC_DEF, 0x00000020पूर्ण,
		अणुAUD_DN0_FREQ, 0x00000000पूर्ण,
		अणुAUD_POLY0_DDS_CONSTANT, 0x000E4DB2पूर्ण,
		अणुAUD_DCOC_0_SRC, 0x00000021पूर्ण,
		अणुAUD_IIR1_0_SEL, 0x00000000पूर्ण,
		अणुAUD_IIR1_0_SHIFT, 0x00000007पूर्ण,
		अणुAUD_IIR1_1_SEL, 0x00000002पूर्ण,
		अणुAUD_IIR1_1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DCOC_1_SRC, 0x00000003पूर्ण,
		अणुAUD_DCOC1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DCOC_PASS_IN, 0x00000000पूर्ण,
		अणुAUD_IIR1_2_SEL, 0x00000023पूर्ण,
		अणुAUD_IIR1_2_SHIFT, 0x00000000पूर्ण,
		अणुAUD_IIR1_3_SEL, 0x00000004पूर्ण,
		अणुAUD_IIR1_3_SHIFT, 0x00000007पूर्ण,
		अणुAUD_IIR1_4_SEL, 0x00000005पूर्ण,
		अणुAUD_IIR1_4_SHIFT, 0x00000007पूर्ण,
		अणुAUD_IIR3_0_SEL, 0x00000007पूर्ण,
		अणुAUD_IIR3_0_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DEEMPH0_SRC_SEL, 0x00000011पूर्ण,
		अणुAUD_DEEMPH0_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DEEMPH0_G0, 0x00007000पूर्ण,
		अणुAUD_DEEMPH0_A0, 0x00000000पूर्ण,
		अणुAUD_DEEMPH0_B0, 0x00000000पूर्ण,
		अणुAUD_DEEMPH0_A1, 0x00000000पूर्ण,
		अणुAUD_DEEMPH0_B1, 0x00000000पूर्ण,
		अणुAUD_DEEMPH1_SRC_SEL, 0x00000011पूर्ण,
		अणुAUD_DEEMPH1_SHIFT, 0x00000000पूर्ण,
		अणुAUD_DEEMPH1_G0, 0x00007000पूर्ण,
		अणुAUD_DEEMPH1_A0, 0x00000000पूर्ण,
		अणुAUD_DEEMPH1_B0, 0x00000000पूर्ण,
		अणुAUD_DEEMPH1_A1, 0x00000000पूर्ण,
		अणुAUD_DEEMPH1_B1, 0x00000000पूर्ण,
		अणुAUD_OUT0_SEL, 0x0000003Fपूर्ण,
		अणुAUD_OUT1_SEL, 0x0000003Fपूर्ण,
		अणुAUD_DMD_RA_DDS, 0x00F5C285पूर्ण,
		अणुAUD_PLL_INT, 0x0000001Eपूर्ण,
		अणुAUD_PLL_DDS, 0x00000000पूर्ण,
		अणुAUD_PLL_FRAC, 0x0000E542पूर्ण,
		अणुAUD_RATE_ADJ1, 0x00000100पूर्ण,
		अणुAUD_RATE_ADJ2, 0x00000200पूर्ण,
		अणुAUD_RATE_ADJ3, 0x00000300पूर्ण,
		अणुAUD_RATE_ADJ4, 0x00000400पूर्ण,
		अणुAUD_RATE_ADJ5, 0x00000500पूर्ण,
		अणुAUD_RATE_THRES_DMD, 0x000000C0पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा rlist a2_deemph50[] = अणु
		अणुAUD_DEEMPH0_G0, 0x00000380पूर्ण,
		अणुAUD_DEEMPH1_G0, 0x00000380पूर्ण,
		अणुAUD_DEEMPHGAIN_R, 0x000011e1पूर्ण,
		अणुAUD_DEEMPHNUMER1_R, 0x0002a7bcपूर्ण,
		अणुAUD_DEEMPHNUMER2_R, 0x0003023cपूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	set_audio_start(core, SEL_A2);
	चयन (core->tvaudio) अणु
	हाल WW_BG:
		dprपूर्णांकk("%s PAL-BG A1/2 (status: known-good)\n", __func__);
		set_audio_रेजिस्टरs(core, a2_bgdk_common);
		set_audio_रेजिस्टरs(core, a2_bg);
		set_audio_रेजिस्टरs(core, a2_deemph50);
		अवरोध;
	हाल WW_DK:
		dprपूर्णांकk("%s PAL-DK A1/2 (status: known-good)\n", __func__);
		set_audio_रेजिस्टरs(core, a2_bgdk_common);
		set_audio_रेजिस्टरs(core, a2_dk);
		set_audio_रेजिस्टरs(core, a2_deemph50);
		अवरोध;
	हाल WW_I:
		dprपूर्णांकk("%s PAL-I A1 (status: known-good)\n", __func__);
		set_audio_रेजिस्टरs(core, a1_i);
		set_audio_रेजिस्टरs(core, a2_deemph50);
		अवरोध;
	हाल WW_L:
		dprपूर्णांकk("%s AM-L (status: devel)\n", __func__);
		set_audio_रेजिस्टरs(core, am_l);
		अवरोध;
	हाल WW_NONE:
	हाल WW_BTSC:
	हाल WW_EIAJ:
	हाल WW_I2SPT:
	हाल WW_FM:
	हाल WW_I2SADC:
	हाल WW_M:
		dprपूर्णांकk("%s Warning: wrong value\n", __func__);
		वापस;
	पूर्ण

	mode |= EN_FMRADIO_EN_RDS | EN_DMTRX_SUMDIFF;
	set_audio_finish(core, mode);
पूर्ण

अटल व्योम set_audio_standard_EIAJ(काष्ठा cx88_core *core)
अणु
	अटल स्थिर काष्ठा rlist eiaj[] = अणु
		/* TODO: eiaj रेजिस्टर settings are not there yet ... */

		अणु /* end of list */ पूर्ण,
	पूर्ण;
	dprपूर्णांकk("%s (status: unknown)\n", __func__);

	set_audio_start(core, SEL_EIAJ);
	set_audio_रेजिस्टरs(core, eiaj);
	set_audio_finish(core, EN_EIAJ_AUTO_STEREO);
पूर्ण

अटल व्योम set_audio_standard_FM(काष्ठा cx88_core *core,
				  क्रमागत cx88_deemph_type deemph)
अणु
	अटल स्थिर काष्ठा rlist fm_deemph_50[] = अणु
		अणुAUD_DEEMPH0_G0, 0x0C45पूर्ण,
		अणुAUD_DEEMPH0_A0, 0x6262पूर्ण,
		अणुAUD_DEEMPH0_B0, 0x1C29पूर्ण,
		अणुAUD_DEEMPH0_A1, 0x3FC66पूर्ण,
		अणुAUD_DEEMPH0_B1, 0x399Aपूर्ण,

		अणुAUD_DEEMPH1_G0, 0x0D80पूर्ण,
		अणुAUD_DEEMPH1_A0, 0x6262पूर्ण,
		अणुAUD_DEEMPH1_B0, 0x1C29पूर्ण,
		अणुAUD_DEEMPH1_A1, 0x3FC66पूर्ण,
		अणुAUD_DEEMPH1_B1, 0x399Aपूर्ण,

		अणुAUD_POLYPH80SCALEFAC, 0x0003पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा rlist fm_deemph_75[] = अणु
		अणुAUD_DEEMPH0_G0, 0x091Bपूर्ण,
		अणुAUD_DEEMPH0_A0, 0x6B68पूर्ण,
		अणुAUD_DEEMPH0_B0, 0x11ECपूर्ण,
		अणुAUD_DEEMPH0_A1, 0x3FC66पूर्ण,
		अणुAUD_DEEMPH0_B1, 0x399Aपूर्ण,

		अणुAUD_DEEMPH1_G0, 0x0AA0पूर्ण,
		अणुAUD_DEEMPH1_A0, 0x6B68पूर्ण,
		अणुAUD_DEEMPH1_B0, 0x11ECपूर्ण,
		अणुAUD_DEEMPH1_A1, 0x3FC66पूर्ण,
		अणुAUD_DEEMPH1_B1, 0x399Aपूर्ण,

		अणुAUD_POLYPH80SCALEFAC, 0x0003पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	/*
	 * It is enough to leave शेष values?
	 *
	 * No, it's not!  The deemphasis रेजिस्टरs are reset to the 75us
	 * values by शेष.  Analyzing the spectrum of the decoded audio
	 * reveals that "no deemphasis" is the same as 75 us, जबतक the 50 us
	 * setting results in less deemphasis.
	 */
	अटल स्थिर काष्ठा rlist fm_no_deemph[] = अणु
		अणुAUD_POLYPH80SCALEFAC, 0x0003पूर्ण,
		अणु /* end of list */ पूर्ण,
	पूर्ण;

	dprपूर्णांकk("%s (status: unknown)\n", __func__);
	set_audio_start(core, SEL_FMRADIO);

	चयन (deemph) अणु
	शेष:
	हाल FM_NO_DEEMPH:
		set_audio_रेजिस्टरs(core, fm_no_deemph);
		अवरोध;

	हाल FM_DEEMPH_50:
		set_audio_रेजिस्टरs(core, fm_deemph_50);
		अवरोध;

	हाल FM_DEEMPH_75:
		set_audio_रेजिस्टरs(core, fm_deemph_75);
		अवरोध;
	पूर्ण

	set_audio_finish(core, EN_FMRADIO_AUTO_STEREO);
पूर्ण

/* ----------------------------------------------------------- */

अटल पूर्णांक cx88_detect_nicam(काष्ठा cx88_core *core)
अणु
	पूर्णांक i, j = 0;

	dprपूर्णांकk("start nicam autodetect.\n");

	क्रम (i = 0; i < 6; i++) अणु
		/* अगर bit1=1 then nicam is detected */
		j += ((cx_पढ़ो(AUD_NICAM_STATUS2) & 0x02) >> 1);

		अगर (j == 1) अणु
			dprपूर्णांकk("nicam is detected.\n");
			वापस 1;
		पूर्ण

		/* रुको a little bit क्रम next पढ़ोing status */
		usleep_range(10000, 20000);
	पूर्ण

	dprपूर्णांकk("nicam is not detected.\n");
	वापस 0;
पूर्ण

व्योम cx88_set_tvaudio(काष्ठा cx88_core *core)
अणु
	चयन (core->tvaudio) अणु
	हाल WW_BTSC:
		set_audio_standard_BTSC(core, 0, EN_BTSC_AUTO_STEREO);
		अवरोध;
	हाल WW_BG:
	हाल WW_DK:
	हाल WW_M:
	हाल WW_I:
	हाल WW_L:
		/* prepare all dsp रेजिस्टरs */
		set_audio_standard_A2(core, EN_A2_FORCE_MONO1);

		/*
		 * set nicam mode - otherwise
		 * AUD_NICAM_STATUS2 contains wrong values
		 */
		set_audio_standard_NICAM(core, EN_NICAM_AUTO_STEREO);
		अगर (cx88_detect_nicam(core) == 0) अणु
			/* fall back to fm / am mono */
			set_audio_standard_A2(core, EN_A2_FORCE_MONO1);
			core->audiomode_current = V4L2_TUNER_MODE_MONO;
			core->use_nicam = 0;
		पूर्ण अन्यथा अणु
			core->use_nicam = 1;
		पूर्ण
		अवरोध;
	हाल WW_EIAJ:
		set_audio_standard_EIAJ(core);
		अवरोध;
	हाल WW_FM:
		set_audio_standard_FM(core, radio_deemphasis);
		अवरोध;
	हाल WW_I2SADC:
		set_audio_start(core, 0x01);
		/*
		 * Slave/Philips/Autobaud
		 * NB on Nova-S bit1 NPhilipsSony appears to be inverted:
		 *	0= Sony, 1=Philips
		 */
		cx_ग_लिखो(AUD_I2SINPUTCNTL, core->board.i2sinअ_दोntl);
		/* Switch to "I2S ADC mode" */
		cx_ग_लिखो(AUD_I2SCNTL, 0x1);
		set_audio_finish(core, EN_I2SIN_ENABLE);
		अवरोध;
	हाल WW_NONE:
	हाल WW_I2SPT:
		pr_info("unknown tv audio mode [%d]\n", core->tvaudio);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cx88_set_tvaudio);

व्योम cx88_newstation(काष्ठा cx88_core *core)
अणु
	core->audiomode_manual = UNSET;
	core->last_change = jअगरfies;
पूर्ण
EXPORT_SYMBOL(cx88_newstation);

व्योम cx88_get_stereo(काष्ठा cx88_core *core, काष्ठा v4l2_tuner *t)
अणु
	अटल स्थिर अक्षर * स्थिर m[] = अणु "stereo", "dual mono",
					  "mono",   "sap" पूर्ण;
	अटल स्थिर अक्षर * स्थिर p[] = अणु "no pilot", "pilot c1",
					  "pilot c2", "?" पूर्ण;
	u32 reg, mode, pilot;

	reg = cx_पढ़ो(AUD_STATUS);
	mode = reg & 0x03;
	pilot = (reg >> 2) & 0x03;

	अगर (core->astat != reg)
		dprपूर्णांकk("AUD_STATUS: 0x%x [%s/%s] ctl=%s\n",
			reg, m[mode], p[pilot],
			aud_ctl_names[cx_पढ़ो(AUD_CTL) & 63]);
	core->astat = reg;

	t->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_SAP |
	    V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;
	t->rxsubchans = UNSET;
	t->audmode = V4L2_TUNER_MODE_MONO;

	चयन (mode) अणु
	हाल 0:
		t->audmode = V4L2_TUNER_MODE_STEREO;
		अवरोध;
	हाल 1:
		t->audmode = V4L2_TUNER_MODE_LANG2;
		अवरोध;
	हाल 2:
		t->audmode = V4L2_TUNER_MODE_MONO;
		अवरोध;
	हाल 3:
		t->audmode = V4L2_TUNER_MODE_SAP;
		अवरोध;
	पूर्ण

	चयन (core->tvaudio) अणु
	हाल WW_BTSC:
	हाल WW_BG:
	हाल WW_DK:
	हाल WW_M:
	हाल WW_EIAJ:
		अगर (!core->use_nicam) अणु
			t->rxsubchans = cx88_dsp_detect_stereo_sap(core);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल WW_NONE:
	हाल WW_I:
	हाल WW_L:
	हाल WW_I2SPT:
	हाल WW_FM:
	हाल WW_I2SADC:
		/* nothing */
		अवरोध;
	पूर्ण

	/* If software stereo detection is not supported... */
	अगर (t->rxsubchans == UNSET) अणु
		t->rxsubchans = V4L2_TUNER_SUB_MONO;
		/*
		 * If the hardware itself detected stereo, also वापस
		 * stereo as an available subchannel
		 */
		अगर (t->audmode == V4L2_TUNER_MODE_STEREO)
			t->rxsubchans |= V4L2_TUNER_SUB_STEREO;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cx88_get_stereo);


व्योम cx88_set_stereo(काष्ठा cx88_core *core, u32 mode, पूर्णांक manual)
अणु
	u32 ctl = UNSET;
	u32 mask = UNSET;

	अगर (manual) अणु
		core->audiomode_manual = mode;
	पूर्ण अन्यथा अणु
		अगर (core->audiomode_manual != UNSET)
			वापस;
	पूर्ण
	core->audiomode_current = mode;

	चयन (core->tvaudio) अणु
	हाल WW_BTSC:
		चयन (mode) अणु
		हाल V4L2_TUNER_MODE_MONO:
			set_audio_standard_BTSC(core, 0, EN_BTSC_FORCE_MONO);
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1:
			set_audio_standard_BTSC(core, 0, EN_BTSC_AUTO_STEREO);
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG2:
			set_audio_standard_BTSC(core, 1, EN_BTSC_FORCE_SAP);
			अवरोध;
		हाल V4L2_TUNER_MODE_STEREO:
		हाल V4L2_TUNER_MODE_LANG1_LANG2:
			set_audio_standard_BTSC(core, 0, EN_BTSC_FORCE_STEREO);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल WW_BG:
	हाल WW_DK:
	हाल WW_M:
	हाल WW_I:
	हाल WW_L:
		अगर (core->use_nicam == 1) अणु
			चयन (mode) अणु
			हाल V4L2_TUNER_MODE_MONO:
			हाल V4L2_TUNER_MODE_LANG1:
				set_audio_standard_NICAM(core,
							 EN_NICAM_FORCE_MONO1);
				अवरोध;
			हाल V4L2_TUNER_MODE_LANG2:
				set_audio_standard_NICAM(core,
							 EN_NICAM_FORCE_MONO2);
				अवरोध;
			हाल V4L2_TUNER_MODE_STEREO:
			हाल V4L2_TUNER_MODE_LANG1_LANG2:
				set_audio_standard_NICAM(core,
							 EN_NICAM_FORCE_STEREO);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((core->tvaudio == WW_I) ||
			    (core->tvaudio == WW_L)) अणु
				/* fall back to fm / am mono */
				set_audio_standard_A2(core, EN_A2_FORCE_MONO1);
			पूर्ण अन्यथा अणु
				/* TODO: Add A2 स्वतःdection */
				mask = 0x3f;
				चयन (mode) अणु
				हाल V4L2_TUNER_MODE_MONO:
				हाल V4L2_TUNER_MODE_LANG1:
					ctl = EN_A2_FORCE_MONO1;
					अवरोध;
				हाल V4L2_TUNER_MODE_LANG2:
					ctl = EN_A2_FORCE_MONO2;
					अवरोध;
				हाल V4L2_TUNER_MODE_STEREO:
				हाल V4L2_TUNER_MODE_LANG1_LANG2:
					ctl = EN_A2_FORCE_STEREO;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल WW_FM:
		चयन (mode) अणु
		हाल V4L2_TUNER_MODE_MONO:
			ctl = EN_FMRADIO_FORCE_MONO;
			mask = 0x3f;
			अवरोध;
		हाल V4L2_TUNER_MODE_STEREO:
			ctl = EN_FMRADIO_AUTO_STEREO;
			mask = 0x3f;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल WW_I2SADC:
	हाल WW_NONE:
	हाल WW_EIAJ:
	हाल WW_I2SPT:
		/* DO NOTHING */
		अवरोध;
	पूर्ण

	अगर (ctl != UNSET) अणु
		dprपूर्णांकk("cx88_set_stereo: mask 0x%x, ctl 0x%x [status=0x%x,ctl=0x%x,vol=0x%x]\n",
			mask, ctl, cx_पढ़ो(AUD_STATUS),
			cx_पढ़ो(AUD_CTL), cx_sपढ़ो(SHADOW_AUD_VOL_CTL));
		cx_anकरोr(AUD_CTL, mask, ctl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cx88_set_stereo);

पूर्णांक cx88_audio_thपढ़ो(व्योम *data)
अणु
	काष्ठा cx88_core *core = data;
	काष्ठा v4l2_tuner t;
	u32 mode = 0;

	dprपूर्णांकk("cx88: tvaudio thread started\n");
	set_मुक्तzable();
	क्रम (;;) अणु
		msleep_पूर्णांकerruptible(1000);
		अगर (kthपढ़ो_should_stop())
			अवरोध;
		try_to_मुक्तze();

		चयन (core->tvaudio) अणु
		हाल WW_BG:
		हाल WW_DK:
		हाल WW_M:
		हाल WW_I:
		हाल WW_L:
			अगर (core->use_nicam)
				जाओ hw_स्वतःdetect;

			/* just monitor the audio status क्रम now ... */
			स_रखो(&t, 0, माप(t));
			cx88_get_stereo(core, &t);

			अगर (core->audiomode_manual != UNSET)
				/* manually set, करोn't करो anything. */
				जारी;

			/* monitor संकेत and set stereo अगर available */
			अगर (t.rxsubchans & V4L2_TUNER_SUB_STEREO)
				mode = V4L2_TUNER_MODE_STEREO;
			अन्यथा
				mode = V4L2_TUNER_MODE_MONO;
			अगर (mode == core->audiomode_current)
				जारी;
			/* स्वतःmatically चयन to best available mode */
			cx88_set_stereo(core, mode, 0);
			अवरोध;
		हाल WW_NONE:
		हाल WW_BTSC:
		हाल WW_EIAJ:
		हाल WW_I2SPT:
		हाल WW_FM:
		हाल WW_I2SADC:
hw_स्वतःdetect:
			/*
			 * stereo स्वतःdetection is supported by hardware so
			 * we करोn't need to करो it manually. Do nothing.
			 */
			अवरोध;
		पूर्ण
	पूर्ण

	dprपूर्णांकk("cx88: tvaudio thread exiting\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cx88_audio_thपढ़ो);
