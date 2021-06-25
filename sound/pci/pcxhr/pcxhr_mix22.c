<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram pcxhr compatible soundcards
 *
 * mixer पूर्णांकerface क्रम stereo cards
 *
 * Copyright (c) 2004 by Digigram <alsa@digigram.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/asoundef.h>
#समावेश "pcxhr.h"
#समावेश "pcxhr_core.h"
#समावेश "pcxhr_mix22.h"


/* रेजिस्टरs used on the DSP and Xilinx (port 2) : HR stereo cards only */
#घोषणा PCXHR_DSP_RESET		0x20
#घोषणा PCXHR_XLX_CFG		0x24
#घोषणा PCXHR_XLX_RUER		0x28
#घोषणा PCXHR_XLX_DATA		0x2C
#घोषणा PCXHR_XLX_STATUS	0x30
#घोषणा PCXHR_XLX_LOFREQ	0x34
#घोषणा PCXHR_XLX_HIFREQ	0x38
#घोषणा PCXHR_XLX_CSUER		0x3C
#घोषणा PCXHR_XLX_SELMIC	0x40

#घोषणा PCXHR_DSP 2

/* byte access only ! */
#घोषणा PCXHR_INPB(mgr, x)	inb((mgr)->port[PCXHR_DSP] + (x))
#घोषणा PCXHR_OUTPB(mgr, x, data) outb((data), (mgr)->port[PCXHR_DSP] + (x))


/* values क्रम PCHR_DSP_RESET रेजिस्टर */
#घोषणा PCXHR_DSP_RESET_DSP	0x01
#घोषणा PCXHR_DSP_RESET_MUTE	0x02
#घोषणा PCXHR_DSP_RESET_CODEC	0x08
#घोषणा PCXHR_DSP_RESET_SMPTE	0x10
#घोषणा PCXHR_DSP_RESET_GPO_OFFSET	5
#घोषणा PCXHR_DSP_RESET_GPO_MASK	0x60

/* values क्रम PCHR_XLX_CFG रेजिस्टर */
#घोषणा PCXHR_CFG_SYNCDSP_MASK		0x80
#घोषणा PCXHR_CFG_DEPENDENCY_MASK	0x60
#घोषणा PCXHR_CFG_INDEPENDANT_SEL	0x00
#घोषणा PCXHR_CFG_MASTER_SEL		0x40
#घोषणा PCXHR_CFG_SLAVE_SEL		0x20
#घोषणा PCXHR_CFG_DATA_UER1_SEL_MASK	0x10	/* 0 (UER0), 1(UER1) */
#घोषणा PCXHR_CFG_DATAIN_SEL_MASK	0x08	/* 0 (ana), 1 (UER) */
#घोषणा PCXHR_CFG_SRC_MASK		0x04	/* 0 (Bypass), 1 (SRC Actअगर) */
#घोषणा PCXHR_CFG_CLOCK_UER1_SEL_MASK	0x02	/* 0 (UER0), 1(UER1) */
#घोषणा PCXHR_CFG_CLOCKIN_SEL_MASK	0x01	/* 0 (पूर्णांकernal), 1 (AES/EBU) */

/* values क्रम PCHR_XLX_DATA रेजिस्टर */
#घोषणा PCXHR_DATA_CODEC	0x80
#घोषणा AKM_POWER_CONTROL_CMD	0xA007
#घोषणा AKM_RESET_ON_CMD	0xA100
#घोषणा AKM_RESET_OFF_CMD	0xA103
#घोषणा AKM_CLOCK_INF_55K_CMD	0xA240
#घोषणा AKM_CLOCK_SUP_55K_CMD	0xA24D
#घोषणा AKM_MUTE_CMD		0xA38D
#घोषणा AKM_UNMUTE_CMD		0xA30D
#घोषणा AKM_LEFT_LEVEL_CMD	0xA600
#घोषणा AKM_RIGHT_LEVEL_CMD	0xA700

/* values क्रम PCHR_XLX_STATUS रेजिस्टर - READ */
#घोषणा PCXHR_STAT_SRC_LOCK		0x01
#घोषणा PCXHR_STAT_LEVEL_IN		0x02
#घोषणा PCXHR_STAT_GPI_OFFSET		2
#घोषणा PCXHR_STAT_GPI_MASK		0x0C
#घोषणा PCXHR_STAT_MIC_CAPS		0x10
/* values क्रम PCHR_XLX_STATUS रेजिस्टर - WRITE */
#घोषणा PCXHR_STAT_FREQ_SYNC_MASK	0x01
#घोषणा PCXHR_STAT_FREQ_UER1_MASK	0x02
#घोषणा PCXHR_STAT_FREQ_SAVE_MASK	0x80

/* values क्रम PCHR_XLX_CSUER रेजिस्टर */
#घोषणा PCXHR_SUER1_BIT_U_READ_MASK	0x80
#घोषणा PCXHR_SUER1_BIT_C_READ_MASK	0x40
#घोषणा PCXHR_SUER1_DATA_PRESENT_MASK	0x20
#घोषणा PCXHR_SUER1_CLOCK_PRESENT_MASK	0x10
#घोषणा PCXHR_SUER_BIT_U_READ_MASK	0x08
#घोषणा PCXHR_SUER_BIT_C_READ_MASK	0x04
#घोषणा PCXHR_SUER_DATA_PRESENT_MASK	0x02
#घोषणा PCXHR_SUER_CLOCK_PRESENT_MASK	0x01

#घोषणा PCXHR_SUER_BIT_U_WRITE_MASK	0x02
#घोषणा PCXHR_SUER_BIT_C_WRITE_MASK	0x01

/* values क्रम PCXHR_XLX_SELMIC रेजिस्टर - WRITE */
#घोषणा PCXHR_SELMIC_PREAMPLI_OFFSET	2
#घोषणा PCXHR_SELMIC_PREAMPLI_MASK	0x0C
#घोषणा PCXHR_SELMIC_PHANTOM_ALIM	0x80


अटल स्थिर अचिन्हित अक्षर g_hr222_p_level[] = अणु
    0x00,   /* [000] -49.5 dB:	AKM[000] = -1.#INF dB	(mute) */
    0x01,   /* [001] -49.0 dB:	AKM[001] = -48.131 dB	(dअगरf=0.86920 dB) */
    0x01,   /* [002] -48.5 dB:	AKM[001] = -48.131 dB	(dअगरf=0.36920 dB) */
    0x01,   /* [003] -48.0 dB:	AKM[001] = -48.131 dB	(dअगरf=0.13080 dB) */
    0x01,   /* [004] -47.5 dB:	AKM[001] = -48.131 dB	(dअगरf=0.63080 dB) */
    0x01,   /* [005] -46.5 dB:	AKM[001] = -48.131 dB	(dअगरf=1.63080 dB) */
    0x01,   /* [006] -47.0 dB:	AKM[001] = -48.131 dB	(dअगरf=1.13080 dB) */
    0x01,   /* [007] -46.0 dB:	AKM[001] = -48.131 dB	(dअगरf=2.13080 dB) */
    0x01,   /* [008] -45.5 dB:	AKM[001] = -48.131 dB	(dअगरf=2.63080 dB) */
    0x02,   /* [009] -45.0 dB:	AKM[002] = -42.110 dB	(dअगरf=2.88980 dB) */
    0x02,   /* [010] -44.5 dB:	AKM[002] = -42.110 dB	(dअगरf=2.38980 dB) */
    0x02,   /* [011] -44.0 dB:	AKM[002] = -42.110 dB	(dअगरf=1.88980 dB) */
    0x02,   /* [012] -43.5 dB:	AKM[002] = -42.110 dB	(dअगरf=1.38980 dB) */
    0x02,   /* [013] -43.0 dB:	AKM[002] = -42.110 dB	(dअगरf=0.88980 dB) */
    0x02,   /* [014] -42.5 dB:	AKM[002] = -42.110 dB	(dअगरf=0.38980 dB) */
    0x02,   /* [015] -42.0 dB:	AKM[002] = -42.110 dB	(dअगरf=0.11020 dB) */
    0x02,   /* [016] -41.5 dB:	AKM[002] = -42.110 dB	(dअगरf=0.61020 dB) */
    0x02,   /* [017] -41.0 dB:	AKM[002] = -42.110 dB	(dअगरf=1.11020 dB) */
    0x02,   /* [018] -40.5 dB:	AKM[002] = -42.110 dB	(dअगरf=1.61020 dB) */
    0x03,   /* [019] -40.0 dB:	AKM[003] = -38.588 dB	(dअगरf=1.41162 dB) */
    0x03,   /* [020] -39.5 dB:	AKM[003] = -38.588 dB	(dअगरf=0.91162 dB) */
    0x03,   /* [021] -39.0 dB:	AKM[003] = -38.588 dB	(dअगरf=0.41162 dB) */
    0x03,   /* [022] -38.5 dB:	AKM[003] = -38.588 dB	(dअगरf=0.08838 dB) */
    0x03,   /* [023] -38.0 dB:	AKM[003] = -38.588 dB	(dअगरf=0.58838 dB) */
    0x03,   /* [024] -37.5 dB:	AKM[003] = -38.588 dB	(dअगरf=1.08838 dB) */
    0x04,   /* [025] -37.0 dB:	AKM[004] = -36.090 dB	(dअगरf=0.91040 dB) */
    0x04,   /* [026] -36.5 dB:	AKM[004] = -36.090 dB	(dअगरf=0.41040 dB) */
    0x04,   /* [027] -36.0 dB:	AKM[004] = -36.090 dB	(dअगरf=0.08960 dB) */
    0x04,   /* [028] -35.5 dB:	AKM[004] = -36.090 dB	(dअगरf=0.58960 dB) */
    0x05,   /* [029] -35.0 dB:	AKM[005] = -34.151 dB	(dअगरf=0.84860 dB) */
    0x05,   /* [030] -34.5 dB:	AKM[005] = -34.151 dB	(dअगरf=0.34860 dB) */
    0x05,   /* [031] -34.0 dB:	AKM[005] = -34.151 dB	(dअगरf=0.15140 dB) */
    0x05,   /* [032] -33.5 dB:	AKM[005] = -34.151 dB	(dअगरf=0.65140 dB) */
    0x06,   /* [033] -33.0 dB:	AKM[006] = -32.568 dB	(dअगरf=0.43222 dB) */
    0x06,   /* [034] -32.5 dB:	AKM[006] = -32.568 dB	(dअगरf=0.06778 dB) */
    0x06,   /* [035] -32.0 dB:	AKM[006] = -32.568 dB	(dअगरf=0.56778 dB) */
    0x07,   /* [036] -31.5 dB:	AKM[007] = -31.229 dB	(dअगरf=0.27116 dB) */
    0x07,   /* [037] -31.0 dB:	AKM[007] = -31.229 dB	(dअगरf=0.22884 dB) */
    0x08,   /* [038] -30.5 dB:	AKM[008] = -30.069 dB	(dअगरf=0.43100 dB) */
    0x08,   /* [039] -30.0 dB:	AKM[008] = -30.069 dB	(dअगरf=0.06900 dB) */
    0x09,   /* [040] -29.5 dB:	AKM[009] = -29.046 dB	(dअगरf=0.45405 dB) */
    0x09,   /* [041] -29.0 dB:	AKM[009] = -29.046 dB	(dअगरf=0.04595 dB) */
    0x0a,   /* [042] -28.5 dB:	AKM[010] = -28.131 dB	(dअगरf=0.36920 dB) */
    0x0a,   /* [043] -28.0 dB:	AKM[010] = -28.131 dB	(dअगरf=0.13080 dB) */
    0x0b,   /* [044] -27.5 dB:	AKM[011] = -27.303 dB	(dअगरf=0.19705 dB) */
    0x0b,   /* [045] -27.0 dB:	AKM[011] = -27.303 dB	(dअगरf=0.30295 dB) */
    0x0c,   /* [046] -26.5 dB:	AKM[012] = -26.547 dB	(dअगरf=0.04718 dB) */
    0x0d,   /* [047] -26.0 dB:	AKM[013] = -25.852 dB	(dअगरf=0.14806 dB) */
    0x0e,   /* [048] -25.5 dB:	AKM[014] = -25.208 dB	(dअगरf=0.29176 dB) */
    0x0e,   /* [049] -25.0 dB:	AKM[014] = -25.208 dB	(dअगरf=0.20824 dB) */
    0x0f,   /* [050] -24.5 dB:	AKM[015] = -24.609 dB	(dअगरf=0.10898 dB) */
    0x10,   /* [051] -24.0 dB:	AKM[016] = -24.048 dB	(dअगरf=0.04840 dB) */
    0x11,   /* [052] -23.5 dB:	AKM[017] = -23.522 dB	(dअगरf=0.02183 dB) */
    0x12,   /* [053] -23.0 dB:	AKM[018] = -23.025 dB	(dअगरf=0.02535 dB) */
    0x13,   /* [054] -22.5 dB:	AKM[019] = -22.556 dB	(dअगरf=0.05573 dB) */
    0x14,   /* [055] -22.0 dB:	AKM[020] = -22.110 dB	(dअगरf=0.11020 dB) */
    0x15,   /* [056] -21.5 dB:	AKM[021] = -21.686 dB	(dअगरf=0.18642 dB) */
    0x17,   /* [057] -21.0 dB:	AKM[023] = -20.896 dB	(dअगरf=0.10375 dB) */
    0x18,   /* [058] -20.5 dB:	AKM[024] = -20.527 dB	(dअगरf=0.02658 dB) */
    0x1a,   /* [059] -20.0 dB:	AKM[026] = -19.831 dB	(dअगरf=0.16866 dB) */
    0x1b,   /* [060] -19.5 dB:	AKM[027] = -19.504 dB	(dअगरf=0.00353 dB) */
    0x1d,   /* [061] -19.0 dB:	AKM[029] = -18.883 dB	(dअगरf=0.11716 dB) */
    0x1e,   /* [062] -18.5 dB:	AKM[030] = -18.588 dB	(dअगरf=0.08838 dB) */
    0x20,   /* [063] -18.0 dB:	AKM[032] = -18.028 dB	(dअगरf=0.02780 dB) */
    0x22,   /* [064] -17.5 dB:	AKM[034] = -17.501 dB	(dअगरf=0.00123 dB) */
    0x24,   /* [065] -17.0 dB:	AKM[036] = -17.005 dB	(dअगरf=0.00475 dB) */
    0x26,   /* [066] -16.5 dB:	AKM[038] = -16.535 dB	(dअगरf=0.03513 dB) */
    0x28,   /* [067] -16.0 dB:	AKM[040] = -16.090 dB	(dअगरf=0.08960 dB) */
    0x2b,   /* [068] -15.5 dB:	AKM[043] = -15.461 dB	(dअगरf=0.03857 dB) */
    0x2d,   /* [069] -15.0 dB:	AKM[045] = -15.067 dB	(dअगरf=0.06655 dB) */
    0x30,   /* [070] -14.5 dB:	AKM[048] = -14.506 dB	(dअगरf=0.00598 dB) */
    0x33,   /* [071] -14.0 dB:	AKM[051] = -13.979 dB	(dअगरf=0.02060 dB) */
    0x36,   /* [072] -13.5 dB:	AKM[054] = -13.483 dB	(dअगरf=0.01707 dB) */
    0x39,   /* [073] -13.0 dB:	AKM[057] = -13.013 dB	(dअगरf=0.01331 dB) */
    0x3c,   /* [074] -12.5 dB:	AKM[060] = -12.568 dB	(dअगरf=0.06778 dB) */
    0x40,   /* [075] -12.0 dB:	AKM[064] = -12.007 dB	(dअगरf=0.00720 dB) */
    0x44,   /* [076] -11.5 dB:	AKM[068] = -11.481 dB	(dअगरf=0.01937 dB) */
    0x48,   /* [077] -11.0 dB:	AKM[072] = -10.984 dB	(dअगरf=0.01585 dB) */
    0x4c,   /* [078] -10.5 dB:	AKM[076] = -10.515 dB	(dअगरf=0.01453 dB) */
    0x51,   /* [079] -10.0 dB:	AKM[081] = -9.961 dB	(dअगरf=0.03890 dB) */
    0x55,   /* [080] -9.5 dB:	AKM[085] = -9.542 dB	(dअगरf=0.04243 dB) */
    0x5a,   /* [081] -9.0 dB:	AKM[090] = -9.046 dB	(dअगरf=0.04595 dB) */
    0x60,   /* [082] -8.5 dB:	AKM[096] = -8.485 dB	(dअगरf=0.01462 dB) */
    0x66,   /* [083] -8.0 dB:	AKM[102] = -7.959 dB	(dअगरf=0.04120 dB) */
    0x6c,   /* [084] -7.5 dB:	AKM[108] = -7.462 dB	(dअगरf=0.03767 dB) */
    0x72,   /* [085] -7.0 dB:	AKM[114] = -6.993 dB	(dअगरf=0.00729 dB) */
    0x79,   /* [086] -6.5 dB:	AKM[121] = -6.475 dB	(dअगरf=0.02490 dB) */
    0x80,   /* [087] -6.0 dB:	AKM[128] = -5.987 dB	(dअगरf=0.01340 dB) */
    0x87,   /* [088] -5.5 dB:	AKM[135] = -5.524 dB	(dअगरf=0.02413 dB) */
    0x8f,   /* [089] -5.0 dB:	AKM[143] = -5.024 dB	(dअगरf=0.02408 dB) */
    0x98,   /* [090] -4.5 dB:	AKM[152] = -4.494 dB	(dअगरf=0.00607 dB) */
    0xa1,   /* [091] -4.0 dB:	AKM[161] = -3.994 dB	(dअगरf=0.00571 dB) */
    0xaa,   /* [092] -3.5 dB:	AKM[170] = -3.522 dB	(dअगरf=0.02183 dB) */
    0xb5,   /* [093] -3.0 dB:	AKM[181] = -2.977 dB	(dअगरf=0.02277 dB) */
    0xbf,   /* [094] -2.5 dB:	AKM[191] = -2.510 dB	(dअगरf=0.01014 dB) */
    0xcb,   /* [095] -2.0 dB:	AKM[203] = -1.981 dB	(dअगरf=0.01912 dB) */
    0xd7,   /* [096] -1.5 dB:	AKM[215] = -1.482 dB	(dअगरf=0.01797 dB) */
    0xe3,   /* [097] -1.0 dB:	AKM[227] = -1.010 dB	(dअगरf=0.01029 dB) */
    0xf1,   /* [098] -0.5 dB:	AKM[241] = -0.490 dB	(dअगरf=0.00954 dB) */
    0xff,   /* [099] +0.0 dB:	AKM[255] = +0.000 dB	(dअगरf=0.00000 dB) */
पूर्ण;


अटल व्योम hr222_config_akm(काष्ठा pcxhr_mgr *mgr, अचिन्हित लघु data)
अणु
	अचिन्हित लघु mask = 0x8000;
	/* activate access to codec रेजिस्टरs */
	PCXHR_INPB(mgr, PCXHR_XLX_HIFREQ);

	जबतक (mask) अणु
		PCXHR_OUTPB(mgr, PCXHR_XLX_DATA,
			    data & mask ? PCXHR_DATA_CODEC : 0);
		mask >>= 1;
	पूर्ण
	/* termiate access to codec रेजिस्टरs */
	PCXHR_INPB(mgr, PCXHR_XLX_RUER);
पूर्ण


अटल पूर्णांक hr222_set_hw_playback_level(काष्ठा pcxhr_mgr *mgr,
				       पूर्णांक idx, पूर्णांक level)
अणु
	अचिन्हित लघु cmd;
	अगर (idx > 1 ||
	    level < 0 ||
	    level >= ARRAY_SIZE(g_hr222_p_level))
		वापस -EINVAL;

	अगर (idx == 0)
		cmd = AKM_LEFT_LEVEL_CMD;
	अन्यथा
		cmd = AKM_RIGHT_LEVEL_CMD;

	/* conversion from PmBoardCodedLevel to AKM nonlinear programming */
	cmd += g_hr222_p_level[level];

	hr222_config_akm(mgr, cmd);
	वापस 0;
पूर्ण


अटल पूर्णांक hr222_set_hw_capture_level(काष्ठा pcxhr_mgr *mgr,
				      पूर्णांक level_l, पूर्णांक level_r, पूर्णांक level_mic)
अणु
	/* program all input levels at the same समय */
	अचिन्हित पूर्णांक data;
	पूर्णांक i;

	अगर (!mgr->capture_chips)
		वापस -EINVAL;	/* no PCX22 */

	data  = ((level_mic & 0xff) << 24);	/* micro is mono, but apply */
	data |= ((level_mic & 0xff) << 16);	/* level on both channels */
	data |= ((level_r & 0xff) << 8);	/* line input right channel */
	data |= (level_l & 0xff);		/* line input left channel */

	PCXHR_INPB(mgr, PCXHR_XLX_DATA);	/* activate input codec */
	/* send 32 bits (4 x 8 bits) */
	क्रम (i = 0; i < 32; i++, data <<= 1) अणु
		PCXHR_OUTPB(mgr, PCXHR_XLX_DATA,
			    (data & 0x80000000) ? PCXHR_DATA_CODEC : 0);
	पूर्ण
	PCXHR_INPB(mgr, PCXHR_XLX_RUER);	/* बंद input level codec */
	वापस 0;
पूर्ण

अटल व्योम hr222_micro_boost(काष्ठा pcxhr_mgr *mgr, पूर्णांक level);

पूर्णांक hr222_sub_init(काष्ठा pcxhr_mgr *mgr)
अणु
	अचिन्हित अक्षर reg;

	mgr->board_has_analog = 1;	/* analog always available */
	mgr->xlx_cfg = PCXHR_CFG_SYNCDSP_MASK;

	reg = PCXHR_INPB(mgr, PCXHR_XLX_STATUS);
	अगर (reg & PCXHR_STAT_MIC_CAPS)
		mgr->board_has_mic = 1;	/* microphone available */
	dev_dbg(&mgr->pci->dev,
		"MIC input available = %d\n", mgr->board_has_mic);

	/* reset codec */
	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET,
		    PCXHR_DSP_RESET_DSP);
	msleep(5);
	mgr->dsp_reset = PCXHR_DSP_RESET_DSP  |
			 PCXHR_DSP_RESET_MUTE |
			 PCXHR_DSP_RESET_CODEC;
	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET, mgr->dsp_reset);
	/* hr222_ग_लिखो_gpo(mgr, 0); करोes the same */
	msleep(5);

	/* config AKM */
	hr222_config_akm(mgr, AKM_POWER_CONTROL_CMD);
	hr222_config_akm(mgr, AKM_CLOCK_INF_55K_CMD);
	hr222_config_akm(mgr, AKM_UNMUTE_CMD);
	hr222_config_akm(mgr, AKM_RESET_OFF_CMD);

	/* init micro boost */
	hr222_micro_boost(mgr, 0);

	वापस 0;
पूर्ण


/* calc PLL रेजिस्टर */
/* TODO : there is a very similar fct in pcxhr.c */
अटल पूर्णांक hr222_pll_freq_रेजिस्टर(अचिन्हित पूर्णांक freq,
				   अचिन्हित पूर्णांक *pllreg,
				   अचिन्हित पूर्णांक *realfreq)
अणु
	अचिन्हित पूर्णांक reg;

	अगर (freq < 6900 || freq > 219000)
		वापस -EINVAL;
	reg = (28224000 * 2) / freq;
	reg = (reg - 1) / 2;
	अगर (reg < 0x100)
		*pllreg = reg + 0xC00;
	अन्यथा अगर (reg < 0x200)
		*pllreg = reg + 0x800;
	अन्यथा अगर (reg < 0x400)
		*pllreg = reg & 0x1ff;
	अन्यथा अगर (reg < 0x800) अणु
		*pllreg = ((reg >> 1) & 0x1ff) + 0x200;
		reg &= ~1;
	पूर्ण अन्यथा अणु
		*pllreg = ((reg >> 2) & 0x1ff) + 0x400;
		reg &= ~3;
	पूर्ण
	अगर (realfreq)
		*realfreq = (28224000 / (reg + 1));
	वापस 0;
पूर्ण

पूर्णांक hr222_sub_set_घड़ी(काष्ठा pcxhr_mgr *mgr,
			अचिन्हित पूर्णांक rate,
			पूर्णांक *changed)
अणु
	अचिन्हित पूर्णांक speed, pllreg = 0;
	पूर्णांक err;
	अचिन्हित realfreq = rate;

	चयन (mgr->use_घड़ी_प्रकारype) अणु
	हाल HR22_CLOCK_TYPE_INTERNAL:
		err = hr222_pll_freq_रेजिस्टर(rate, &pllreg, &realfreq);
		अगर (err)
			वापस err;

		mgr->xlx_cfg &= ~(PCXHR_CFG_CLOCKIN_SEL_MASK |
				  PCXHR_CFG_CLOCK_UER1_SEL_MASK);
		अवरोध;
	हाल HR22_CLOCK_TYPE_AES_SYNC:
		mgr->xlx_cfg |= PCXHR_CFG_CLOCKIN_SEL_MASK;
		mgr->xlx_cfg &= ~PCXHR_CFG_CLOCK_UER1_SEL_MASK;
		अवरोध;
	हाल HR22_CLOCK_TYPE_AES_1:
		अगर (!mgr->board_has_aes1)
			वापस -EINVAL;

		mgr->xlx_cfg |= (PCXHR_CFG_CLOCKIN_SEL_MASK |
				 PCXHR_CFG_CLOCK_UER1_SEL_MASK);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	hr222_config_akm(mgr, AKM_MUTE_CMD);

	अगर (mgr->use_घड़ी_प्रकारype == HR22_CLOCK_TYPE_INTERNAL) अणु
		PCXHR_OUTPB(mgr, PCXHR_XLX_HIFREQ, pllreg >> 8);
		PCXHR_OUTPB(mgr, PCXHR_XLX_LOFREQ, pllreg & 0xff);
	पूर्ण

	/* set घड़ी source */
	PCXHR_OUTPB(mgr, PCXHR_XLX_CFG, mgr->xlx_cfg);

	/* codec speed modes */
	speed = rate < 55000 ? 0 : 1;
	अगर (mgr->codec_speed != speed) अणु
		mgr->codec_speed = speed;
		अगर (speed == 0)
			hr222_config_akm(mgr, AKM_CLOCK_INF_55K_CMD);
		अन्यथा
			hr222_config_akm(mgr, AKM_CLOCK_SUP_55K_CMD);
	पूर्ण

	mgr->sample_rate_real = realfreq;
	mgr->cur_घड़ी_प्रकारype = mgr->use_घड़ी_प्रकारype;

	अगर (changed)
		*changed = 1;

	hr222_config_akm(mgr, AKM_UNMUTE_CMD);

	dev_dbg(&mgr->pci->dev, "set_clock to %dHz (realfreq=%d pllreg=%x)\n",
		    rate, realfreq, pllreg);
	वापस 0;
पूर्ण

पूर्णांक hr222_get_बाह्यal_घड़ी(काष्ठा pcxhr_mgr *mgr,
			     क्रमागत pcxhr_घड़ी_प्रकारype घड़ी_प्रकारype,
			     पूर्णांक *sample_rate)
अणु
	पूर्णांक rate, calc_rate = 0;
	अचिन्हित पूर्णांक ticks;
	अचिन्हित अक्षर mask, reg;

	अगर (घड़ी_प्रकारype == HR22_CLOCK_TYPE_AES_SYNC) अणु

		mask = (PCXHR_SUER_CLOCK_PRESENT_MASK |
			PCXHR_SUER_DATA_PRESENT_MASK);
		reg = PCXHR_STAT_FREQ_SYNC_MASK;

	पूर्ण अन्यथा अगर (घड़ी_प्रकारype == HR22_CLOCK_TYPE_AES_1 && mgr->board_has_aes1) अणु

		mask = (PCXHR_SUER1_CLOCK_PRESENT_MASK |
			PCXHR_SUER1_DATA_PRESENT_MASK);
		reg = PCXHR_STAT_FREQ_UER1_MASK;

	पूर्ण अन्यथा अणु
		dev_dbg(&mgr->pci->dev,
			"get_external_clock : type %d not supported\n",
			    घड़ी_प्रकारype);
		वापस -EINVAL; /* other घड़ीs not supported */
	पूर्ण

	अगर ((PCXHR_INPB(mgr, PCXHR_XLX_CSUER) & mask) != mask) अणु
		dev_dbg(&mgr->pci->dev,
			"get_external_clock(%d) = 0 Hz\n", घड़ी_प्रकारype);
		*sample_rate = 0;
		वापस 0; /* no बाह्यal घड़ी locked */
	पूर्ण

	PCXHR_OUTPB(mgr, PCXHR_XLX_STATUS, reg); /* calculate freq */

	/* save the measured घड़ी frequency */
	reg |= PCXHR_STAT_FREQ_SAVE_MASK;

	अगर (mgr->last_reg_stat != reg) अणु
		udelay(500);	/* रुको min 2 cycles of lowest freq (8000) */
		mgr->last_reg_stat = reg;
	पूर्ण

	PCXHR_OUTPB(mgr, PCXHR_XLX_STATUS, reg); /* save */

	/* get the frequency */
	ticks = (अचिन्हित पूर्णांक)PCXHR_INPB(mgr, PCXHR_XLX_CFG);
	ticks = (ticks & 0x03) << 8;
	ticks |= (अचिन्हित पूर्णांक)PCXHR_INPB(mgr, PCXHR_DSP_RESET);

	अगर (ticks != 0)
		calc_rate = 28224000 / ticks;
	/* rounding */
	अगर (calc_rate > 184200)
		rate = 192000;
	अन्यथा अगर (calc_rate > 152200)
		rate = 176400;
	अन्यथा अगर (calc_rate > 112000)
		rate = 128000;
	अन्यथा अगर (calc_rate > 92100)
		rate = 96000;
	अन्यथा अगर (calc_rate > 76100)
		rate = 88200;
	अन्यथा अगर (calc_rate > 56000)
		rate = 64000;
	अन्यथा अगर (calc_rate > 46050)
		rate = 48000;
	अन्यथा अगर (calc_rate > 38050)
		rate = 44100;
	अन्यथा अगर (calc_rate > 28000)
		rate = 32000;
	अन्यथा अगर (calc_rate > 23025)
		rate = 24000;
	अन्यथा अगर (calc_rate > 19025)
		rate = 22050;
	अन्यथा अगर (calc_rate > 14000)
		rate = 16000;
	अन्यथा अगर (calc_rate > 11512)
		rate = 12000;
	अन्यथा अगर (calc_rate > 9512)
		rate = 11025;
	अन्यथा अगर (calc_rate > 7000)
		rate = 8000;
	अन्यथा
		rate = 0;

	dev_dbg(&mgr->pci->dev, "External clock is at %d Hz (measured %d Hz)\n",
		    rate, calc_rate);
	*sample_rate = rate;
	वापस 0;
पूर्ण


पूर्णांक hr222_पढ़ो_gpio(काष्ठा pcxhr_mgr *mgr, पूर्णांक is_gpi, पूर्णांक *value)
अणु
	अगर (is_gpi) अणु
		अचिन्हित अक्षर reg = PCXHR_INPB(mgr, PCXHR_XLX_STATUS);
		*value = (पूर्णांक)(reg & PCXHR_STAT_GPI_MASK) >>
			      PCXHR_STAT_GPI_OFFSET;
	पूर्ण अन्यथा अणु
		*value = (पूर्णांक)(mgr->dsp_reset & PCXHR_DSP_RESET_GPO_MASK) >>
			 PCXHR_DSP_RESET_GPO_OFFSET;
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक hr222_ग_लिखो_gpo(काष्ठा pcxhr_mgr *mgr, पूर्णांक value)
अणु
	अचिन्हित अक्षर reg = mgr->dsp_reset & ~PCXHR_DSP_RESET_GPO_MASK;

	reg |= (अचिन्हित अक्षर)(value << PCXHR_DSP_RESET_GPO_OFFSET) &
	       PCXHR_DSP_RESET_GPO_MASK;

	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET, reg);
	mgr->dsp_reset = reg;
	वापस 0;
पूर्ण

पूर्णांक hr222_manage_समयcode(काष्ठा pcxhr_mgr *mgr, पूर्णांक enable)
अणु
	अगर (enable)
		mgr->dsp_reset |= PCXHR_DSP_RESET_SMPTE;
	अन्यथा
		mgr->dsp_reset &= ~PCXHR_DSP_RESET_SMPTE;

	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET, mgr->dsp_reset);
	वापस 0;
पूर्ण

पूर्णांक hr222_update_analog_audio_level(काष्ठा snd_pcxhr *chip,
				    पूर्णांक is_capture, पूर्णांक channel)
अणु
	dev_dbg(chip->card->dev,
		"hr222_update_analog_audio_level(%s chan=%d)\n",
		    is_capture ? "capture" : "playback", channel);
	अगर (is_capture) अणु
		पूर्णांक level_l, level_r, level_mic;
		/* we have to update all levels */
		अगर (chip->analog_capture_active) अणु
			level_l = chip->analog_capture_volume[0];
			level_r = chip->analog_capture_volume[1];
		पूर्ण अन्यथा अणु
			level_l = HR222_LINE_CAPTURE_LEVEL_MIN;
			level_r = HR222_LINE_CAPTURE_LEVEL_MIN;
		पूर्ण
		अगर (chip->mic_active)
			level_mic = chip->mic_volume;
		अन्यथा
			level_mic = HR222_MICRO_CAPTURE_LEVEL_MIN;
		वापस hr222_set_hw_capture_level(chip->mgr,
						 level_l, level_r, level_mic);
	पूर्ण अन्यथा अणु
		पूर्णांक vol;
		अगर (chip->analog_playback_active[channel])
			vol = chip->analog_playback_volume[channel];
		अन्यथा
			vol = HR222_LINE_PLAYBACK_LEVEL_MIN;
		वापस hr222_set_hw_playback_level(chip->mgr, channel, vol);
	पूर्ण
पूर्ण


/*texts[5] = अणु"Line", "Digital", "Digi+SRC", "Mic", "Line+Mic"पूर्ण*/
#घोषणा SOURCE_LINE	0
#घोषणा SOURCE_DIGITAL	1
#घोषणा SOURCE_DIGISRC	2
#घोषणा SOURCE_MIC	3
#घोषणा SOURCE_LINEMIC	4

पूर्णांक hr222_set_audio_source(काष्ठा snd_pcxhr *chip)
अणु
	पूर्णांक digital = 0;
	/* शेष analog source */
	chip->mgr->xlx_cfg &= ~(PCXHR_CFG_SRC_MASK |
				PCXHR_CFG_DATAIN_SEL_MASK |
				PCXHR_CFG_DATA_UER1_SEL_MASK);

	अगर (chip->audio_capture_source == SOURCE_DIGISRC) अणु
		chip->mgr->xlx_cfg |= PCXHR_CFG_SRC_MASK;
		digital = 1;
	पूर्ण अन्यथा अणु
		अगर (chip->audio_capture_source == SOURCE_DIGITAL)
			digital = 1;
	पूर्ण
	अगर (digital) अणु
		chip->mgr->xlx_cfg |=  PCXHR_CFG_DATAIN_SEL_MASK;
		अगर (chip->mgr->board_has_aes1) अणु
			/* get data from the AES1 plug */
			chip->mgr->xlx_cfg |= PCXHR_CFG_DATA_UER1_SEL_MASK;
		पूर्ण
		/* chip->mic_active = 0; */
		/* chip->analog_capture_active = 0; */
	पूर्ण अन्यथा अणु
		पूर्णांक update_lvl = 0;
		chip->analog_capture_active = 0;
		chip->mic_active = 0;
		अगर (chip->audio_capture_source == SOURCE_LINE ||
		    chip->audio_capture_source == SOURCE_LINEMIC) अणु
			अगर (chip->analog_capture_active == 0)
				update_lvl = 1;
			chip->analog_capture_active = 1;
		पूर्ण
		अगर (chip->audio_capture_source == SOURCE_MIC ||
		    chip->audio_capture_source == SOURCE_LINEMIC) अणु
			अगर (chip->mic_active == 0)
				update_lvl = 1;
			chip->mic_active = 1;
		पूर्ण
		अगर (update_lvl) अणु
			/* capture: update all 3 mutes/unmutes with one call */
			hr222_update_analog_audio_level(chip, 1, 0);
		पूर्ण
	पूर्ण
	/* set the source infos (max 3 bits modअगरied) */
	PCXHR_OUTPB(chip->mgr, PCXHR_XLX_CFG, chip->mgr->xlx_cfg);
	वापस 0;
पूर्ण


पूर्णांक hr222_iec958_capture_byte(काष्ठा snd_pcxhr *chip,
			     पूर्णांक aes_idx, अचिन्हित अक्षर *aes_bits)
अणु
	अचिन्हित अक्षर idx = (अचिन्हित अक्षर)(aes_idx * 8);
	अचिन्हित अक्षर temp = 0;
	अचिन्हित अक्षर mask = chip->mgr->board_has_aes1 ?
		PCXHR_SUER1_BIT_C_READ_MASK : PCXHR_SUER_BIT_C_READ_MASK;
	पूर्णांक i;
	क्रम (i = 0; i < 8; i++) अणु
		PCXHR_OUTPB(chip->mgr, PCXHR_XLX_RUER, idx++); /* idx < 192 */
		temp <<= 1;
		अगर (PCXHR_INPB(chip->mgr, PCXHR_XLX_CSUER) & mask)
			temp |= 1;
	पूर्ण
	dev_dbg(chip->card->dev, "read iec958 AES %d byte %d = 0x%x\n",
		    chip->chip_idx, aes_idx, temp);
	*aes_bits = temp;
	वापस 0;
पूर्ण


पूर्णांक hr222_iec958_update_byte(काष्ठा snd_pcxhr *chip,
			     पूर्णांक aes_idx, अचिन्हित अक्षर aes_bits)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर new_bits = aes_bits;
	अचिन्हित अक्षर old_bits = chip->aes_bits[aes_idx];
	अचिन्हित अक्षर idx = (अचिन्हित अक्षर)(aes_idx * 8);
	क्रम (i = 0; i < 8; i++) अणु
		अगर ((old_bits & 0x01) != (new_bits & 0x01)) अणु
			/* idx < 192 */
			PCXHR_OUTPB(chip->mgr, PCXHR_XLX_RUER, idx);
			/* ग_लिखो C and U bit */
			PCXHR_OUTPB(chip->mgr, PCXHR_XLX_CSUER, new_bits&0x01 ?
				    PCXHR_SUER_BIT_C_WRITE_MASK : 0);
		पूर्ण
		idx++;
		old_bits >>= 1;
		new_bits >>= 1;
	पूर्ण
	chip->aes_bits[aes_idx] = aes_bits;
	वापस 0;
पूर्ण

अटल व्योम hr222_micro_boost(काष्ठा pcxhr_mgr *mgr, पूर्णांक level)
अणु
	अचिन्हित अक्षर boost_mask;
	boost_mask = (अचिन्हित अक्षर) (level << PCXHR_SELMIC_PREAMPLI_OFFSET);
	अगर (boost_mask & (~PCXHR_SELMIC_PREAMPLI_MASK))
		वापस; /* only values क्रमm 0 to 3 accepted */

	mgr->xlx_selmic &= ~PCXHR_SELMIC_PREAMPLI_MASK;
	mgr->xlx_selmic |= boost_mask;

	PCXHR_OUTPB(mgr, PCXHR_XLX_SELMIC, mgr->xlx_selmic);

	dev_dbg(&mgr->pci->dev, "hr222_micro_boost : set %x\n", boost_mask);
पूर्ण

अटल व्योम hr222_phantom_घातer(काष्ठा pcxhr_mgr *mgr, पूर्णांक घातer)
अणु
	अगर (घातer)
		mgr->xlx_selmic |= PCXHR_SELMIC_PHANTOM_ALIM;
	अन्यथा
		mgr->xlx_selmic &= ~PCXHR_SELMIC_PHANTOM_ALIM;

	PCXHR_OUTPB(mgr, PCXHR_XLX_SELMIC, mgr->xlx_selmic);

	dev_dbg(&mgr->pci->dev, "hr222_phantom_power : set %d\n", घातer);
पूर्ण


/* mic level */
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_mic_hr222, -9850, 50, 650);

अटल पूर्णांक hr222_mic_vol_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = HR222_MICRO_CAPTURE_LEVEL_MIN; /* -98 dB */
	/* gains from 9 dB to 31.5 dB not recommended; use micboost instead */
	uinfo->value.पूर्णांकeger.max = HR222_MICRO_CAPTURE_LEVEL_MAX; /*  +7 dB */
	वापस 0;
पूर्ण

अटल पूर्णांक hr222_mic_vol_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->mic_volume;
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक hr222_mic_vol_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	mutex_lock(&chip->mgr->mixer_mutex);
	अगर (chip->mic_volume != ucontrol->value.पूर्णांकeger.value[0]) अणु
		changed = 1;
		chip->mic_volume = ucontrol->value.पूर्णांकeger.value[0];
		hr222_update_analog_audio_level(chip, 1, 0);
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new hr222_control_mic_level = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name =		"Mic Capture Volume",
	.info =		hr222_mic_vol_info,
	.get =		hr222_mic_vol_get,
	.put =		hr222_mic_vol_put,
	.tlv = अणु .p = db_scale_mic_hr222 पूर्ण,
पूर्ण;


/* mic boost level */
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_micboost_hr222, 0, 1800, 5400);

अटल पूर्णांक hr222_mic_boost_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;	/*  0 dB */
	uinfo->value.पूर्णांकeger.max = 3;	/* 54 dB */
	वापस 0;
पूर्ण

अटल पूर्णांक hr222_mic_boost_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->mic_boost;
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक hr222_mic_boost_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	mutex_lock(&chip->mgr->mixer_mutex);
	अगर (chip->mic_boost != ucontrol->value.पूर्णांकeger.value[0]) अणु
		changed = 1;
		chip->mic_boost = ucontrol->value.पूर्णांकeger.value[0];
		hr222_micro_boost(chip->mgr, chip->mic_boost);
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new hr222_control_mic_boost = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name =		"MicBoost Capture Volume",
	.info =		hr222_mic_boost_info,
	.get =		hr222_mic_boost_get,
	.put =		hr222_mic_boost_put,
	.tlv = अणु .p = db_scale_micboost_hr222 पूर्ण,
पूर्ण;


/******************* Phantom घातer चयन *******************/
#घोषणा hr222_phantom_घातer_info	snd_ctl_boolean_mono_info

अटल पूर्णांक hr222_phantom_घातer_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->phantom_घातer;
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक hr222_phantom_घातer_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक घातer, changed = 0;

	mutex_lock(&chip->mgr->mixer_mutex);
	घातer = !!ucontrol->value.पूर्णांकeger.value[0];
	अगर (chip->phantom_घातer != घातer) अणु
		hr222_phantom_घातer(chip->mgr, घातer);
		chip->phantom_घातer = घातer;
		changed = 1;
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new hr222_phantom_घातer_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Phantom Power Switch",
	.info = hr222_phantom_घातer_info,
	.get = hr222_phantom_घातer_get,
	.put = hr222_phantom_घातer_put,
पूर्ण;


पूर्णांक hr222_add_mic_controls(काष्ठा snd_pcxhr *chip)
अणु
	पूर्णांक err;
	अगर (!chip->mgr->board_has_mic)
		वापस 0;

	/* controls */
	err = snd_ctl_add(chip->card, snd_ctl_new1(&hr222_control_mic_level,
						   chip));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(chip->card, snd_ctl_new1(&hr222_control_mic_boost,
						   chip));
	अगर (err < 0)
		वापस err;

	err = snd_ctl_add(chip->card, snd_ctl_new1(&hr222_phantom_घातer_चयन,
						   chip));
	वापस err;
पूर्ण
