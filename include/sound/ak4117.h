<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_AK4117_H
#घोषणा __SOUND_AK4117_H

/*
 *  Routines क्रम Asahi Kasei AK4117
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 */

#घोषणा AK4117_REG_PWRDN	0x00	/* घातer करोwn */
#घोषणा AK4117_REG_CLOCK	0x01	/* घड़ी control */
#घोषणा AK4117_REG_IO		0x02	/* input/output control */
#घोषणा AK4117_REG_INT0_MASK	0x03	/* पूर्णांकerrupt0 mask */
#घोषणा AK4117_REG_INT1_MASK	0x04	/* पूर्णांकerrupt1 mask */
#घोषणा AK4117_REG_RCS0		0x05	/* receiver status 0 */
#घोषणा AK4117_REG_RCS1		0x06	/* receiver status 1 */
#घोषणा AK4117_REG_RCS2		0x07	/* receiver status 2 */
#घोषणा AK4117_REG_RXCSB0	0x08	/* RX channel status byte 0 */
#घोषणा AK4117_REG_RXCSB1	0x09	/* RX channel status byte 1 */
#घोषणा AK4117_REG_RXCSB2	0x0a	/* RX channel status byte 2 */
#घोषणा AK4117_REG_RXCSB3	0x0b	/* RX channel status byte 3 */
#घोषणा AK4117_REG_RXCSB4	0x0c	/* RX channel status byte 4 */
#घोषणा AK4117_REG_Pc0		0x0d	/* burst preamble Pc byte 0 */
#घोषणा AK4117_REG_Pc1		0x0e	/* burst preamble Pc byte 1 */
#घोषणा AK4117_REG_Pd0		0x0f	/* burst preamble Pd byte 0 */
#घोषणा AK4117_REG_Pd1		0x10	/* burst preamble Pd byte 1 */
#घोषणा AK4117_REG_QSUB_ADDR	0x11	/* Q-subcode address + control */
#घोषणा AK4117_REG_QSUB_TRACK	0x12	/* Q-subcode track */
#घोषणा AK4117_REG_QSUB_INDEX	0x13	/* Q-subcode index */
#घोषणा AK4117_REG_QSUB_MINUTE	0x14	/* Q-subcode minute */
#घोषणा AK4117_REG_QSUB_SECOND	0x15	/* Q-subcode second */
#घोषणा AK4117_REG_QSUB_FRAME	0x16	/* Q-subcode frame */
#घोषणा AK4117_REG_QSUB_ZERO	0x17	/* Q-subcode zero */
#घोषणा AK4117_REG_QSUB_ABSMIN	0x18	/* Q-subcode असलolute minute */
#घोषणा AK4117_REG_QSUB_ABSSEC	0x19	/* Q-subcode असलolute second */
#घोषणा AK4117_REG_QSUB_ABSFRM	0x1a	/* Q-subcode असलolute frame */

/* sizes */
#घोषणा AK4117_REG_RXCSB_SIZE	((AK4117_REG_RXCSB4-AK4117_REG_RXCSB0)+1)
#घोषणा AK4117_REG_QSUB_SIZE	((AK4117_REG_QSUB_ABSFRM-AK4117_REG_QSUB_ADDR)+1)

/* AK4117_REG_PWRDN bits */
#घोषणा AK4117_EXCT		(1<<4)	/* 0 = X'tal mode, 1 = बाह्यal घड़ी mode */
#घोषणा AK4117_XTL1		(1<<3)	/* XTL1=0,XTL0=0 -> 11.2896Mhz; XTL1=0,XTL0=1 -> 12.288Mhz */
#घोषणा AK4117_XTL0		(1<<2)	/* XTL1=1,XTL0=0 -> 24.576Mhz; XTL1=1,XTL0=1 -> use channel status */
#घोषणा AK4117_XTL_11_2896M	(0)
#घोषणा AK4117_XTL_12_288M	AK4117_XTL0
#घोषणा AK4117_XTL_24_576M	AK4117_XTL1
#घोषणा AK4117_XTL_EXT		(AK4117_XTL1|AK4117_XTL0)
#घोषणा AK4117_PWN		(1<<1)	/* 0 = घातer करोwn, 1 = normal operation */
#घोषणा AK4117_RST		(1<<0)	/* 0 = reset & initialize (except this रेजिस्टर), 1 = normal operation */

/* AK4117_REQ_CLOCK bits */
#घोषणा AK4117_LP		(1<<7)	/* 0 = normal mode, 1 = low घातer mode (Fs up to 48kHz only) */
#घोषणा AK4117_PKCS1		(1<<6)	/* master घड़ी frequency at PLL mode (when LP == 0) */
#घोषणा AK4117_PKCS0		(1<<5)
#घोषणा AK4117_PKCS_512fs	(0)
#घोषणा AK4117_PKCS_256fs	AK4117_PKCS0
#घोषणा AK4117_PKCS_128fs	AK4117_PKCS1
#घोषणा AK4117_DIV		(1<<4)	/* 0 = MCKO == Fs, 1 = MCKO == Fs / 2; X'tal mode only */
#घोषणा AK4117_XCKS1		(1<<3)	/* master घड़ी frequency at X'tal mode */
#घोषणा AK4117_XCKS0		(1<<2)
#घोषणा AK4117_XCKS_128fs	(0)
#घोषणा AK4117_XCKS_256fs	AK4117_XCKS0
#घोषणा AK4117_XCKS_512fs	AK4117_XCKS1
#घोषणा AK4117_XCKS_1024fs	(AK4117_XCKS1|AK4117_XCKS0)
#घोषणा AK4117_CM1		(1<<1)	/* MCKO operation mode select */
#घोषणा AK4117_CM0		(1<<0)
#घोषणा AK4117_CM_PLL		(0)		/* use RX input as master घड़ी */
#घोषणा AK4117_CM_XTAL		(AK4117_CM0)	/* use X'tal as master घड़ी */
#घोषणा AK4117_CM_PLL_XTAL	(AK4117_CM1)	/* use Rx input but X'tal when PLL loses lock */
#घोषणा AK4117_CM_MONITOR	(AK4117_CM0|AK4117_CM1) /* use X'tal as master घड़ी, but use PLL क्रम monitoring */

/* AK4117_REG_IO */
#घोषणा AK4117_IPS		(1<<7)	/* Input Recovery Data Select, 0 = RX0, 1 = RX1 */
#घोषणा AK4117_UOUTE		(1<<6)	/* U-bit output enable to UOUT, 0 = disable, 1 = enable */
#घोषणा AK4117_CS12		(1<<5)	/* channel status select, 0 = channel1, 1 = channel2 */
#घोषणा AK4117_EFH2		(1<<4)	/* INT0 pin hold count select */
#घोषणा AK4117_EFH1		(1<<3)
#घोषणा AK4117_EFH_512LRCLK	(0)
#घोषणा AK4117_EFH_1024LRCLK	(AK4117_EFH1)
#घोषणा AK4117_EFH_2048LRCLK	(AK4117_EFH2)
#घोषणा AK4117_EFH_4096LRCLK	(AK4117_EFH1|AK4117_EFH2)
#घोषणा AK4117_DIF2		(1<<2)	/* audio data क्रमmat control */
#घोषणा AK4117_DIF1		(1<<1)
#घोषणा AK4117_DIF0		(1<<0)
#घोषणा AK4117_DIF_16R		(0)				/* STDO: 16-bit, right justअगरied */
#घोषणा AK4117_DIF_18R		(AK4117_DIF0)			/* STDO: 18-bit, right justअगरied */
#घोषणा AK4117_DIF_20R		(AK4117_DIF1)			/* STDO: 20-bit, right justअगरied */
#घोषणा AK4117_DIF_24R		(AK4117_DIF1|AK4117_DIF0)	/* STDO: 24-bit, right justअगरied */
#घोषणा AK4117_DIF_24L		(AK4117_DIF2)			/* STDO: 24-bit, left justअगरied */
#घोषणा AK4117_DIF_24I2S	(AK4117_DIF2|AK4117_DIF0)	/* STDO: I2S */

/* AK4117_REG_INT0_MASK & AK4117_REG_INT1_MASK */
#घोषणा AK4117_MULK		(1<<7)	/* mask enable क्रम UNLOCK bit */
#घोषणा AK4117_MPAR		(1<<6)	/* mask enable क्रम PAR bit */
#घोषणा AK4117_MAUTO		(1<<5)	/* mask enable क्रम AUTO bit */
#घोषणा AK4117_MV		(1<<4)	/* mask enable क्रम V bit */
#घोषणा AK4117_MAUD		(1<<3)	/* mask enable क्रम AUDION bit */
#घोषणा AK4117_MSTC		(1<<2)	/* mask enable क्रम STC bit */
#घोषणा AK4117_MCIT		(1<<1)	/* mask enable क्रम CINT bit */
#घोषणा AK4117_MQIT		(1<<0)	/* mask enable क्रम QINT bit */

/* AK4117_REG_RCS0 */
#घोषणा AK4117_UNLCK		(1<<7)	/* PLL lock status, 0 = lock, 1 = unlock */
#घोषणा AK4117_PAR		(1<<6)	/* parity error or biphase error status, 0 = no error, 1 = error */
#घोषणा AK4117_AUTO		(1<<5)	/* Non-PCM or DTS stream स्वतः detection, 0 = no detect, 1 = detect */
#घोषणा AK4117_V		(1<<4)	/* Validity bit, 0 = valid, 1 = invalid */
#घोषणा AK4117_AUDION		(1<<3)	/* audio bit output, 0 = audio, 1 = non-audio */
#घोषणा AK4117_STC		(1<<2)	/* sampling frequency or Pre-emphasis change, 0 = no detect, 1 = detect */
#घोषणा AK4117_CINT		(1<<1)	/* channel status buffer पूर्णांकerrupt, 0 = no change, 1 = change */
#घोषणा AK4117_QINT		(1<<0)	/* Q-subcode buffer पूर्णांकerrupt, 0 = no change, 1 = changed */

/* AK4117_REG_RCS1 */
#घोषणा AK4117_DTSCD		(1<<6)	/* DTS-CD bit audio stream detect, 0 = no detect, 1 = detect */
#घोषणा AK4117_NPCM		(1<<5)	/* Non-PCM bit stream detection, 0 = no detect, 1 = detect */
#घोषणा AK4117_PEM		(1<<4)	/* Pre-emphasis detect, 0 = OFF, 1 = ON */
#घोषणा AK4117_FS3		(1<<3)	/* sampling frequency detection */
#घोषणा AK4117_FS2		(1<<2)
#घोषणा AK4117_FS1		(1<<1)
#घोषणा AK4117_FS0		(1<<0)
#घोषणा AK4117_FS_44100HZ	(0)
#घोषणा AK4117_FS_48000HZ	(AK4117_FS1)
#घोषणा AK4117_FS_32000HZ	(AK4117_FS1|AK4117_FS0)
#घोषणा AK4117_FS_88200HZ	(AK4117_FS3)
#घोषणा AK4117_FS_96000HZ	(AK4117_FS3|AK4117_FS1)
#घोषणा AK4117_FS_176400HZ	(AK4117_FS3|AK4117_FS2)
#घोषणा AK4117_FS_192000HZ	(AK4117_FS3|AK4117_FS2|AK4117_FS1)

/* AK4117_REG_RCS2 */
#घोषणा AK4117_CCRC		(1<<1)	/* CRC क्रम channel status, 0 = no error, 1 = error */
#घोषणा AK4117_QCRC		(1<<0)	/* CRC क्रम Q-subcode, 0 = no error, 1 = error */

/* flags क्रम snd_ak4117_check_rate_and_errors() */
#घोषणा AK4117_CHECK_NO_STAT	(1<<0)	/* no statistics */
#घोषणा AK4117_CHECK_NO_RATE	(1<<1)	/* no rate check */

#घोषणा AK4117_CONTROLS		13

प्रकार व्योम (ak4117_ग_लिखो_t)(व्योम *निजी_data, अचिन्हित अक्षर addr, अचिन्हित अक्षर data);
प्रकार अचिन्हित अक्षर (ak4117_पढ़ो_t)(व्योम *निजी_data, अचिन्हित अक्षर addr);

क्रमागत अणु
	AK4117_PARITY_ERRORS,
	AK4117_V_BIT_ERRORS,
	AK4117_QCRC_ERRORS,
	AK4117_CCRC_ERRORS,
	AK4117_NUM_ERRORS
पूर्ण;

काष्ठा ak4117 अणु
	काष्ठा snd_card *card;
	ak4117_ग_लिखो_t * ग_लिखो;
	ak4117_पढ़ो_t * पढ़ो;
	व्योम * निजी_data;
	अचिन्हित पूर्णांक init: 1;
	spinlock_t lock;
	अचिन्हित अक्षर regmap[5];
	काष्ठा snd_kcontrol *kctls[AK4117_CONTROLS];
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित दीर्घ errors[AK4117_NUM_ERRORS];
	अचिन्हित अक्षर rcs0;
	अचिन्हित अक्षर rcs1;
	अचिन्हित अक्षर rcs2;
	काष्ठा समयr_list समयr;	/* statistic समयr */
	व्योम *change_callback_निजी;
	व्योम (*change_callback)(काष्ठा ak4117 *ak4117, अचिन्हित अक्षर c0, अचिन्हित अक्षर c1);
पूर्ण;

पूर्णांक snd_ak4117_create(काष्ठा snd_card *card, ak4117_पढ़ो_t *पढ़ो, ak4117_ग_लिखो_t *ग_लिखो,
		      स्थिर अचिन्हित अक्षर pgm[5], व्योम *निजी_data, काष्ठा ak4117 **r_ak4117);
व्योम snd_ak4117_reg_ग_लिखो(काष्ठा ak4117 *ak4117, अचिन्हित अक्षर reg, अचिन्हित अक्षर mask, अचिन्हित अक्षर val);
व्योम snd_ak4117_reinit(काष्ठा ak4117 *ak4117);
पूर्णांक snd_ak4117_build(काष्ठा ak4117 *ak4117, काष्ठा snd_pcm_substream *capture_substream);
पूर्णांक snd_ak4117_बाह्यal_rate(काष्ठा ak4117 *ak4117);
पूर्णांक snd_ak4117_check_rate_and_errors(काष्ठा ak4117 *ak4117, अचिन्हित पूर्णांक flags);

#पूर्ण_अगर /* __SOUND_AK4117_H */

