<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_AK4114_H
#घोषणा __SOUND_AK4114_H

/*
 *  Routines क्रम Asahi Kasei AK4114
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 */

/* AK4114 रेजिस्टरs */
#घोषणा AK4114_REG_PWRDN	0x00	/* घातer करोwn */
#घोषणा AK4114_REG_FORMAT	0x01	/* क्रमmat control */
#घोषणा AK4114_REG_IO0		0x02	/* input/output control */
#घोषणा AK4114_REG_IO1		0x03	/* input/output control */
#घोषणा AK4114_REG_INT0_MASK	0x04	/* पूर्णांकerrupt0 mask */
#घोषणा AK4114_REG_INT1_MASK	0x05	/* पूर्णांकerrupt1 mask */
#घोषणा AK4114_REG_RCS0		0x06	/* receiver status 0 */
#घोषणा AK4114_REG_RCS1		0x07	/* receiver status 1 */
#घोषणा AK4114_REG_RXCSB0	0x08	/* RX channel status byte 0 */
#घोषणा AK4114_REG_RXCSB1	0x09	/* RX channel status byte 1 */
#घोषणा AK4114_REG_RXCSB2	0x0a	/* RX channel status byte 2 */
#घोषणा AK4114_REG_RXCSB3	0x0b	/* RX channel status byte 3 */
#घोषणा AK4114_REG_RXCSB4	0x0c	/* RX channel status byte 4 */
#घोषणा AK4114_REG_TXCSB0	0x0d	/* TX channel status byte 0 */
#घोषणा AK4114_REG_TXCSB1	0x0e	/* TX channel status byte 1 */
#घोषणा AK4114_REG_TXCSB2	0x0f	/* TX channel status byte 2 */
#घोषणा AK4114_REG_TXCSB3	0x10	/* TX channel status byte 3 */
#घोषणा AK4114_REG_TXCSB4	0x11	/* TX channel status byte 4 */
#घोषणा AK4114_REG_Pc0		0x12	/* burst preamble Pc byte 0 */
#घोषणा AK4114_REG_Pc1		0x13	/* burst preamble Pc byte 1 */
#घोषणा AK4114_REG_Pd0		0x14	/* burst preamble Pd byte 0 */
#घोषणा AK4114_REG_Pd1		0x15	/* burst preamble Pd byte 1 */
#घोषणा AK4114_REG_QSUB_ADDR	0x16	/* Q-subcode address + control */
#घोषणा AK4114_REG_QSUB_TRACK	0x17	/* Q-subcode track */
#घोषणा AK4114_REG_QSUB_INDEX	0x18	/* Q-subcode index */
#घोषणा AK4114_REG_QSUB_MINUTE	0x19	/* Q-subcode minute */
#घोषणा AK4114_REG_QSUB_SECOND	0x1a	/* Q-subcode second */
#घोषणा AK4114_REG_QSUB_FRAME	0x1b	/* Q-subcode frame */
#घोषणा AK4114_REG_QSUB_ZERO	0x1c	/* Q-subcode zero */
#घोषणा AK4114_REG_QSUB_ABSMIN	0x1d	/* Q-subcode असलolute minute */
#घोषणा AK4114_REG_QSUB_ABSSEC	0x1e	/* Q-subcode असलolute second */
#घोषणा AK4114_REG_QSUB_ABSFRM	0x1f	/* Q-subcode असलolute frame */

/* sizes */
#घोषणा AK4114_REG_RXCSB_SIZE	((AK4114_REG_RXCSB4-AK4114_REG_RXCSB0)+1)
#घोषणा AK4114_REG_TXCSB_SIZE	((AK4114_REG_TXCSB4-AK4114_REG_TXCSB0)+1)
#घोषणा AK4114_REG_QSUB_SIZE	((AK4114_REG_QSUB_ABSFRM-AK4114_REG_QSUB_ADDR)+1)

/* AK4117_REG_PWRDN bits */
#घोषणा AK4114_CS12		(1<<7)	/* Channel Status Select */
#घोषणा AK4114_BCU		(1<<6)	/* Block Start & C/U Output Mode */
#घोषणा AK4114_CM1		(1<<5)	/* Master Clock Operation Select */
#घोषणा AK4114_CM0		(1<<4)	/* Master Clock Operation Select */
#घोषणा AK4114_OCKS1		(1<<3)	/* Master Clock Frequency Select */
#घोषणा AK4114_OCKS0		(1<<2)	/* Master Clock Frequency Select */
#घोषणा AK4114_PWN		(1<<1)	/* 0 = घातer करोwn, 1 = normal operation */
#घोषणा AK4114_RST		(1<<0)	/* 0 = reset & initialize (except this रेजिस्टर), 1 = normal operation */

/* AK4114_REQ_FORMAT bits */
#घोषणा AK4114_MONO		(1<<7)	/* Double Sampling Frequency Mode: 0 = stereo, 1 = mono */
#घोषणा AK4114_DIF2		(1<<6)	/* Audio Data Control */
#घोषणा AK4114_DIF1		(1<<5)	/* Audio Data Control */
#घोषणा AK4114_DIF0		(1<<4)	/* Audio Data Control */
#घोषणा AK4114_DIF_16R		(0)				/* STDO: 16-bit, right justअगरied */
#घोषणा AK4114_DIF_18R		(AK4114_DIF0)			/* STDO: 18-bit, right justअगरied */
#घोषणा AK4114_DIF_20R		(AK4114_DIF1)			/* STDO: 20-bit, right justअगरied */
#घोषणा AK4114_DIF_24R		(AK4114_DIF1|AK4114_DIF0)	/* STDO: 24-bit, right justअगरied */
#घोषणा AK4114_DIF_24L		(AK4114_DIF2)			/* STDO: 24-bit, left justअगरied */
#घोषणा AK4114_DIF_24I2S	(AK4114_DIF2|AK4114_DIF0)	/* STDO: I2S */
#घोषणा AK4114_DIF_I24L		(AK4114_DIF2|AK4114_DIF1)	/* STDO: 24-bit, left justअगरied; LRCLK, BICK = Input */
#घोषणा AK4114_DIF_I24I2S	(AK4114_DIF2|AK4114_DIF1|AK4114_DIF0) /* STDO: I2S;  LRCLK, BICK = Input */
#घोषणा AK4114_DEAU		(1<<3)	/* Deemphasis Autodetect Enable (1 = enable) */
#घोषणा AK4114_DEM1		(1<<2)	/* 32kHz-48kHz Deemphasis Control */
#घोषणा AK4114_DEM0		(1<<1)	/* 32kHz-48kHz Deemphasis Control */
#घोषणा AK4114_DEM_44KHZ	(0)
#घोषणा AK4114_DEM_48KHZ	(AK4114_DEM1)
#घोषणा AK4114_DEM_32KHZ	(AK4114_DEM0|AK4114_DEM1)
#घोषणा AK4114_DEM_96KHZ	(AK4114_DEM1)	/* DFS must be set */
#घोषणा AK4114_DFS		(1<<0)	/* 96kHz Deemphasis Control */

/* AK4114_REG_IO0 */
#घोषणा AK4114_TX1E		(1<<7)	/* TX1 Output Enable (1 = enable) */
#घोषणा AK4114_OPS12		(1<<6)	/* Output Data Selector क्रम TX1 pin */
#घोषणा AK4114_OPS11		(1<<5)	/* Output Data Selector क्रम TX1 pin */
#घोषणा AK4114_OPS10		(1<<4)	/* Output Data Selector क्रम TX1 pin */
#घोषणा AK4114_TX0E		(1<<3)	/* TX0 Output Enable (1 = enable) */
#घोषणा AK4114_OPS02		(1<<2)	/* Output Data Selector क्रम TX0 pin */
#घोषणा AK4114_OPS01		(1<<1)	/* Output Data Selector क्रम TX0 pin */
#घोषणा AK4114_OPS00		(1<<0)	/* Output Data Selector क्रम TX0 pin */

/* AK4114_REG_IO1 */
#घोषणा AK4114_EFH1		(1<<7)	/* Interrupt 0 pin Hold */
#घोषणा AK4114_EFH0		(1<<6)	/* Interrupt 0 pin Hold */
#घोषणा AK4114_EFH_512		(0)
#घोषणा AK4114_EFH_1024		(AK4114_EFH0)
#घोषणा AK4114_EFH_2048		(AK4114_EFH1)
#घोषणा AK4114_EFH_4096		(AK4114_EFH1|AK4114_EFH0)
#घोषणा AK4114_UDIT		(1<<5)	/* U-bit Control क्रम DIT (0 = fixed '0', 1 = recovered) */
#घोषणा AK4114_TLR		(1<<4)	/* Double Sampling Frequency Select क्रम DIT (0 = L channel, 1 = R channel) */
#घोषणा AK4114_DIT		(1<<3)	/* TX1 out: 0 = Through Data (RX data), 1 = Transmit Data (DAUX data) */
#घोषणा AK4114_IPS2		(1<<2)	/* Input Recovery Data Select */
#घोषणा AK4114_IPS1		(1<<1)	/* Input Recovery Data Select */
#घोषणा AK4114_IPS0		(1<<0)	/* Input Recovery Data Select */
#घोषणा AK4114_IPS(x)		((x)&7)

/* AK4114_REG_INT0_MASK && AK4114_REG_INT1_MASK*/
#घोषणा AK4117_MQI              (1<<7)  /* mask enable क्रम QINT bit */
#घोषणा AK4117_MAT              (1<<6)  /* mask enable क्रम AUTO bit */
#घोषणा AK4117_MCI              (1<<5)  /* mask enable क्रम CINT bit */
#घोषणा AK4117_MUL              (1<<4)  /* mask enable क्रम UNLOCK bit */
#घोषणा AK4117_MDTS             (1<<3)  /* mask enable क्रम DTSCD bit */
#घोषणा AK4117_MPE              (1<<2)  /* mask enable क्रम PEM bit */
#घोषणा AK4117_MAN              (1<<1)  /* mask enable क्रम AUDN bit */
#घोषणा AK4117_MPR              (1<<0)  /* mask enable क्रम PAR bit */

/* AK4114_REG_RCS0 */
#घोषणा AK4114_QINT		(1<<7)	/* Q-subcode buffer पूर्णांकerrupt, 0 = no change, 1 = changed */
#घोषणा AK4114_AUTO		(1<<6)	/* Non-PCM or DTS stream स्वतः detection, 0 = no detect, 1 = detect */
#घोषणा AK4114_CINT		(1<<5)	/* channel status buffer पूर्णांकerrupt, 0 = no change, 1 = change */
#घोषणा AK4114_UNLCK		(1<<4)	/* PLL lock status, 0 = lock, 1 = unlock */
#घोषणा AK4114_DTSCD		(1<<3)	/* DTS-CD Detect, 0 = No detect, 1 = Detect */
#घोषणा AK4114_PEM		(1<<2)	/* Pre-emphasis Detect, 0 = OFF, 1 = ON */
#घोषणा AK4114_AUDION		(1<<1)	/* audio bit output, 0 = audio, 1 = non-audio */
#घोषणा AK4114_PAR		(1<<0)	/* parity error or biphase error status, 0 = no error, 1 = error */

/* AK4114_REG_RCS1 */
#घोषणा AK4114_FS3		(1<<7)	/* sampling frequency detection */
#घोषणा AK4114_FS2		(1<<6)
#घोषणा AK4114_FS1		(1<<5)
#घोषणा AK4114_FS0		(1<<4)
#घोषणा AK4114_FS_44100HZ	(0)
#घोषणा AK4114_FS_48000HZ	(AK4114_FS1)
#घोषणा AK4114_FS_32000HZ	(AK4114_FS1|AK4114_FS0)
#घोषणा AK4114_FS_88200HZ	(AK4114_FS3)
#घोषणा AK4114_FS_96000HZ	(AK4114_FS3|AK4114_FS1)
#घोषणा AK4114_FS_176400HZ	(AK4114_FS3|AK4114_FS2)
#घोषणा AK4114_FS_192000HZ	(AK4114_FS3|AK4114_FS2|AK4114_FS1)
#घोषणा AK4114_V		(1<<3)	/* Validity of Channel Status, 0 = Valid, 1 = Invalid */
#घोषणा AK4114_QCRC		(1<<1)	/* CRC क्रम Q-subcode, 0 = no error, 1 = error */
#घोषणा AK4114_CCRC		(1<<0)	/* CRC क्रम channel status, 0 = no error, 1 = error */

/* flags क्रम snd_ak4114_check_rate_and_errors() */
#घोषणा AK4114_CHECK_NO_STAT	(1<<0)	/* no statistics */
#घोषणा AK4114_CHECK_NO_RATE	(1<<1)	/* no rate check */

#घोषणा AK4114_CONTROLS		15

प्रकार व्योम (ak4114_ग_लिखो_t)(व्योम *निजी_data, अचिन्हित अक्षर addr, अचिन्हित अक्षर data);
प्रकार अचिन्हित अक्षर (ak4114_पढ़ो_t)(व्योम *निजी_data, अचिन्हित अक्षर addr);

क्रमागत अणु
	AK4114_PARITY_ERRORS,
	AK4114_V_BIT_ERRORS,
	AK4114_QCRC_ERRORS,
	AK4114_CCRC_ERRORS,
	AK4114_NUM_ERRORS
पूर्ण;

काष्ठा ak4114 अणु
	काष्ठा snd_card *card;
	ak4114_ग_लिखो_t * ग_लिखो;
	ak4114_पढ़ो_t * पढ़ो;
	व्योम * निजी_data;
	atomic_t wq_processing;
	काष्ठा mutex reinit_mutex;
	spinlock_t lock;
	अचिन्हित अक्षर regmap[6];
	अचिन्हित अक्षर txcsb[5];
	काष्ठा snd_kcontrol *kctls[AK4114_CONTROLS];
	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;
	अचिन्हित दीर्घ errors[AK4114_NUM_ERRORS];
	अचिन्हित अक्षर rcs0;
	अचिन्हित अक्षर rcs1;
	काष्ठा delayed_work work;
	अचिन्हित पूर्णांक check_flags;
	व्योम *change_callback_निजी;
	व्योम (*change_callback)(काष्ठा ak4114 *ak4114, अचिन्हित अक्षर c0, अचिन्हित अक्षर c1);
पूर्ण;

पूर्णांक snd_ak4114_create(काष्ठा snd_card *card,
		      ak4114_पढ़ो_t *पढ़ो, ak4114_ग_लिखो_t *ग_लिखो,
		      स्थिर अचिन्हित अक्षर pgm[6], स्थिर अचिन्हित अक्षर txcsb[5],
		      व्योम *निजी_data, काष्ठा ak4114 **r_ak4114);
व्योम snd_ak4114_reg_ग_लिखो(काष्ठा ak4114 *ak4114, अचिन्हित अक्षर reg, अचिन्हित अक्षर mask, अचिन्हित अक्षर val);
व्योम snd_ak4114_reinit(काष्ठा ak4114 *ak4114);
पूर्णांक snd_ak4114_build(काष्ठा ak4114 *ak4114,
		     काष्ठा snd_pcm_substream *playback_substream,
                     काष्ठा snd_pcm_substream *capture_substream);
पूर्णांक snd_ak4114_बाह्यal_rate(काष्ठा ak4114 *ak4114);
पूर्णांक snd_ak4114_check_rate_and_errors(काष्ठा ak4114 *ak4114, अचिन्हित पूर्णांक flags);

#अगर_घोषित CONFIG_PM
व्योम snd_ak4114_suspend(काष्ठा ak4114 *chip);
व्योम snd_ak4114_resume(काष्ठा ak4114 *chip);
#अन्यथा
अटल अंतरभूत व्योम snd_ak4114_suspend(काष्ठा ak4114 *chip) अणुपूर्ण
अटल अंतरभूत व्योम snd_ak4114_resume(काष्ठा ak4114 *chip) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_AK4114_H */

