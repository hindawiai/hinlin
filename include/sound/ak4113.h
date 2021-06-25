<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_AK4113_H
#घोषणा __SOUND_AK4113_H

/*
 *  Routines क्रम Asahi Kasei AK4113
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *  Copyright (c) by Pavel Hofman <pavel.hofman@ivitera.com>,
 */

/* AK4113 रेजिस्टरs */
/* घातer करोwn */
#घोषणा AK4113_REG_PWRDN	0x00
/* क्रमmat control */
#घोषणा AK4113_REG_FORMAT	0x01
/* input/output control */
#घोषणा AK4113_REG_IO0		0x02
/* input/output control */
#घोषणा AK4113_REG_IO1		0x03
/* पूर्णांकerrupt0 mask */
#घोषणा AK4113_REG_INT0_MASK	0x04
/* पूर्णांकerrupt1 mask */
#घोषणा AK4113_REG_INT1_MASK	0x05
/* DAT mask & DTS select */
#घोषणा AK4113_REG_DATDTS	0x06
/* receiver status 0 */
#घोषणा AK4113_REG_RCS0		0x07
/* receiver status 1 */
#घोषणा AK4113_REG_RCS1		0x08
/* receiver status 2 */
#घोषणा AK4113_REG_RCS2		0x09
/* RX channel status byte 0 */
#घोषणा AK4113_REG_RXCSB0	0x0a
/* RX channel status byte 1 */
#घोषणा AK4113_REG_RXCSB1	0x0b
/* RX channel status byte 2 */
#घोषणा AK4113_REG_RXCSB2	0x0c
/* RX channel status byte 3 */
#घोषणा AK4113_REG_RXCSB3	0x0d
/* RX channel status byte 4 */
#घोषणा AK4113_REG_RXCSB4	0x0e
/* burst preamble Pc byte 0 */
#घोषणा AK4113_REG_Pc0		0x0f
/* burst preamble Pc byte 1 */
#घोषणा AK4113_REG_Pc1		0x10
/* burst preamble Pd byte 0 */
#घोषणा AK4113_REG_Pd0		0x11
/* burst preamble Pd byte 1 */
#घोषणा AK4113_REG_Pd1		0x12
/* Q-subcode address + control */
#घोषणा AK4113_REG_QSUB_ADDR	0x13
/* Q-subcode track */
#घोषणा AK4113_REG_QSUB_TRACK	0x14
/* Q-subcode index */
#घोषणा AK4113_REG_QSUB_INDEX	0x15
/* Q-subcode minute */
#घोषणा AK4113_REG_QSUB_MINUTE	0x16
/* Q-subcode second */
#घोषणा AK4113_REG_QSUB_SECOND	0x17
/* Q-subcode frame */
#घोषणा AK4113_REG_QSUB_FRAME	0x18
/* Q-subcode zero */
#घोषणा AK4113_REG_QSUB_ZERO	0x19
/* Q-subcode असलolute minute */
#घोषणा AK4113_REG_QSUB_ABSMIN	0x1a
/* Q-subcode असलolute second */
#घोषणा AK4113_REG_QSUB_ABSSEC	0x1b
/* Q-subcode असलolute frame */
#घोषणा AK4113_REG_QSUB_ABSFRM	0x1c

/* sizes */
#घोषणा AK4113_REG_RXCSB_SIZE	((AK4113_REG_RXCSB4-AK4113_REG_RXCSB0)+1)
#घोषणा AK4113_REG_QSUB_SIZE	((AK4113_REG_QSUB_ABSFRM-AK4113_REG_QSUB_ADDR)\
		+1)

#घोषणा AK4113_WRITABLE_REGS	(AK4113_REG_DATDTS + 1)

/* AK4113_REG_PWRDN bits */
/* Channel Status Select */
#घोषणा AK4113_CS12		(1<<7)
/* Block Start & C/U Output Mode */
#घोषणा AK4113_BCU		(1<<6)
/* Master Clock Operation Select */
#घोषणा AK4113_CM1		(1<<5)
/* Master Clock Operation Select */
#घोषणा AK4113_CM0		(1<<4)
/* Master Clock Frequency Select */
#घोषणा AK4113_OCKS1		(1<<3)
/* Master Clock Frequency Select */
#घोषणा AK4113_OCKS0		(1<<2)
/* 0 = घातer करोwn, 1 = normal operation */
#घोषणा AK4113_PWN		(1<<1)
/* 0 = reset & initialize (except thisरेजिस्टर), 1 = normal operation */
#घोषणा AK4113_RST		(1<<0)

/* AK4113_REQ_FORMAT bits */
/* V/TX Output select: 0 = Validity Flag Output, 1 = TX */
#घोषणा AK4113_VTX		(1<<7)
/* Audio Data Control */
#घोषणा AK4113_DIF2		(1<<6)
/* Audio Data Control */
#घोषणा AK4113_DIF1		(1<<5)
/* Audio Data Control */
#घोषणा AK4113_DIF0		(1<<4)
/* Deemphasis Autodetect Enable (1 = enable) */
#घोषणा AK4113_DEAU		(1<<3)
/* 32kHz-48kHz Deemphasis Control */
#घोषणा AK4113_DEM1		(1<<2)
/* 32kHz-48kHz Deemphasis Control */
#घोषणा AK4113_DEM0		(1<<1)
#घोषणा AK4113_DEM_OFF		(AK4113_DEM0)
#घोषणा AK4113_DEM_44KHZ	(0)
#घोषणा AK4113_DEM_48KHZ	(AK4113_DEM1)
#घोषणा AK4113_DEM_32KHZ	(AK4113_DEM0|AK4113_DEM1)
/* STDO: 16-bit, right justअगरied */
#घोषणा AK4113_DIF_16R		(0)
/* STDO: 18-bit, right justअगरied */
#घोषणा AK4113_DIF_18R		(AK4113_DIF0)
/* STDO: 20-bit, right justअगरied */
#घोषणा AK4113_DIF_20R		(AK4113_DIF1)
/* STDO: 24-bit, right justअगरied */
#घोषणा AK4113_DIF_24R		(AK4113_DIF1|AK4113_DIF0)
/* STDO: 24-bit, left justअगरied */
#घोषणा AK4113_DIF_24L		(AK4113_DIF2)
/* STDO: I2S */
#घोषणा AK4113_DIF_24I2S	(AK4113_DIF2|AK4113_DIF0)
/* STDO: 24-bit, left justअगरied; LRCLK, BICK = Input */
#घोषणा AK4113_DIF_I24L		(AK4113_DIF2|AK4113_DIF1)
/* STDO: I2S;  LRCLK, BICK = Input */
#घोषणा AK4113_DIF_I24I2S	(AK4113_DIF2|AK4113_DIF1|AK4113_DIF0)

/* AK4113_REG_IO0 */
/* XTL1=0,XTL0=0 -> 11.2896Mhz; XTL1=0,XTL0=1 -> 12.288Mhz */
#घोषणा AK4113_XTL1		(1<<6)
/* XTL1=1,XTL0=0 -> 24.576Mhz; XTL1=1,XTL0=1 -> use channel status */
#घोषणा AK4113_XTL0		(1<<5)
/* Block Start Signal Output: 0 = U-bit, 1 = C-bit (req. BCU = 1) */
#घोषणा AK4113_UCE		(1<<4)
/* TX Output Enable (1 = enable) */
#घोषणा AK4113_TXE		(1<<3)
/* Output Through Data Selector क्रम TX pin */
#घोषणा AK4113_OPS2		(1<<2)
/* Output Through Data Selector क्रम TX pin */
#घोषणा AK4113_OPS1		(1<<1)
/* Output Through Data Selector क्रम TX pin */
#घोषणा AK4113_OPS0		(1<<0)
/* 11.2896 MHz ref. Xtal freq. */
#घोषणा AK4113_XTL_11_2896M	(0)
/* 12.288 MHz ref. Xtal freq. */
#घोषणा AK4113_XTL_12_288M	(AK4113_XTL0)
/* 24.576 MHz ref. Xtal freq. */
#घोषणा AK4113_XTL_24_576M	(AK4113_XTL1)

/* AK4113_REG_IO1 */
/* Interrupt 0 pin Hold */
#घोषणा AK4113_EFH1		(1<<7)
/* Interrupt 0 pin Hold */
#घोषणा AK4113_EFH0		(1<<6)
#घोषणा AK4113_EFH_512LRCLK	(0)
#घोषणा AK4113_EFH_1024LRCLK	(AK4113_EFH0)
#घोषणा AK4113_EFH_2048LRCLK	(AK4113_EFH1)
#घोषणा AK4113_EFH_4096LRCLK	(AK4113_EFH1|AK4113_EFH0)
/* PLL Lock Time: 0 = 384/fs, 1 = 1/fs */
#घोषणा AK4113_FAST		(1<<5)
/* MCKO2 Output Select: 0 = CMx/OCKSx, 1 = Xtal */
#घोषणा AK4113_XMCK		(1<<4)
/* MCKO2 Output Freq. Select: 0 = x1, 1 = x0.5  (req. XMCK = 1) */
#घोषणा AK4113_DIV		(1<<3)
/* Input Recovery Data Select */
#घोषणा AK4113_IPS2		(1<<2)
/* Input Recovery Data Select */
#घोषणा AK4113_IPS1		(1<<1)
/* Input Recovery Data Select */
#घोषणा AK4113_IPS0		(1<<0)
#घोषणा AK4113_IPS(x)		((x)&7)

/* AK4113_REG_INT0_MASK && AK4113_REG_INT1_MASK*/
/* mask enable क्रम QINT bit */
#घोषणा AK4113_MQI		(1<<7)
/* mask enable क्रम AUTO bit */
#घोषणा AK4113_MAUT		(1<<6)
/* mask enable क्रम CINT bit */
#घोषणा AK4113_MCIT		(1<<5)
/* mask enable क्रम UNLOCK bit */
#घोषणा AK4113_MULK		(1<<4)
/* mask enable क्रम V bit */
#घोषणा AK4113_V		(1<<3)
/* mask enable क्रम STC bit */
#घोषणा AK4113_STC		(1<<2)
/* mask enable क्रम AUDN bit */
#घोषणा AK4113_MAN		(1<<1)
/* mask enable क्रम PAR bit */
#घोषणा AK4113_MPR		(1<<0)

/* AK4113_REG_DATDTS */
/* DAT Start ID Counter */
#घोषणा AK4113_DCNT		(1<<4)
/* DTS-CD 16-bit Sync Word Detect */
#घोषणा AK4113_DTS16		(1<<3)
/* DTS-CD 14-bit Sync Word Detect */
#घोषणा AK4113_DTS14		(1<<2)
/* mask enable क्रम DAT bit (अगर 1, no INT1 effect */
#घोषणा AK4113_MDAT1		(1<<1)
/* mask enable क्रम DAT bit (अगर 1, no INT0 effect */
#घोषणा AK4113_MDAT0		(1<<0)

/* AK4113_REG_RCS0 */
/* Q-subcode buffer पूर्णांकerrupt, 0 = no change, 1 = changed */
#घोषणा AK4113_QINT		(1<<7)
/* Non-PCM or DTS stream स्वतः detection, 0 = no detect, 1 = detect */
#घोषणा AK4113_AUTO		(1<<6)
/* channel status buffer पूर्णांकerrupt, 0 = no change, 1 = change */
#घोषणा AK4113_CINT		(1<<5)
/* PLL lock status, 0 = lock, 1 = unlock */
#घोषणा AK4113_UNLCK		(1<<4)
/* Validity bit, 0 = valid, 1 = invalid */
#घोषणा AK4113_V		(1<<3)
/* sampling frequency or Pre-emphasis change, 0 = no detect, 1 = detect */
#घोषणा AK4113_STC		(1<<2)
/* audio bit output, 0 = audio, 1 = non-audio */
#घोषणा AK4113_AUDION		(1<<1)
/* parity error or biphase error status, 0 = no error, 1 = error */
#घोषणा AK4113_PAR		(1<<0)

/* AK4113_REG_RCS1 */
/* sampling frequency detection */
#घोषणा AK4113_FS3		(1<<7)
#घोषणा AK4113_FS2		(1<<6)
#घोषणा AK4113_FS1		(1<<5)
#घोषणा AK4113_FS0		(1<<4)
/* Pre-emphasis detect, 0 = OFF, 1 = ON */
#घोषणा AK4113_PEM		(1<<3)
/* DAT Start ID Detect, 0 = no detect, 1 = detect */
#घोषणा AK4113_DAT		(1<<2)
/* DTS-CD bit audio stream detect, 0 = no detect, 1 = detect */
#घोषणा AK4113_DTSCD		(1<<1)
/* Non-PCM bit stream detection, 0 = no detect, 1 = detect */
#घोषणा AK4113_NPCM		(1<<0)
#घोषणा AK4113_FS_8000HZ	(AK4113_FS3|AK4113_FS0)
#घोषणा AK4113_FS_11025HZ	(AK4113_FS2|AK4113_FS0)
#घोषणा AK4113_FS_16000HZ	(AK4113_FS2|AK4113_FS1|AK4113_FS0)
#घोषणा AK4113_FS_22050HZ	(AK4113_FS2)
#घोषणा AK4113_FS_24000HZ	(AK4113_FS2|AK4113_FS1)
#घोषणा AK4113_FS_32000HZ	(AK4113_FS1|AK4113_FS0)
#घोषणा AK4113_FS_44100HZ	(0)
#घोषणा AK4113_FS_48000HZ	(AK4113_FS1)
#घोषणा AK4113_FS_64000HZ	(AK4113_FS3|AK4113_FS1|AK4113_FS0)
#घोषणा AK4113_FS_88200HZ	(AK4113_FS3)
#घोषणा AK4113_FS_96000HZ	(AK4113_FS3|AK4113_FS1)
#घोषणा AK4113_FS_176400HZ	(AK4113_FS3|AK4113_FS2)
#घोषणा AK4113_FS_192000HZ	(AK4113_FS3|AK4113_FS2|AK4113_FS1)

/* AK4113_REG_RCS2 */
/* CRC क्रम Q-subcode, 0 = no error, 1 = error */
#घोषणा AK4113_QCRC		(1<<1)
/* CRC क्रम channel status, 0 = no error, 1 = error */
#घोषणा AK4113_CCRC		(1<<0)

/* flags क्रम snd_ak4113_check_rate_and_errors() */
#घोषणा AK4113_CHECK_NO_STAT	(1<<0)	/* no statistics */
#घोषणा AK4113_CHECK_NO_RATE	(1<<1)	/* no rate check */

#घोषणा AK4113_CONTROLS		13

प्रकार व्योम (ak4113_ग_लिखो_t)(व्योम *निजी_data, अचिन्हित अक्षर addr,
		अचिन्हित अक्षर data);
प्रकार अचिन्हित अक्षर (ak4113_पढ़ो_t)(व्योम *निजी_data, अचिन्हित अक्षर addr);

क्रमागत अणु
	AK4113_PARITY_ERRORS,
	AK4113_V_BIT_ERRORS,
	AK4113_QCRC_ERRORS,
	AK4113_CCRC_ERRORS,
	AK4113_NUM_ERRORS
पूर्ण;

काष्ठा ak4113 अणु
	काष्ठा snd_card *card;
	ak4113_ग_लिखो_t *ग_लिखो;
	ak4113_पढ़ो_t *पढ़ो;
	व्योम *निजी_data;
	atomic_t wq_processing;
	काष्ठा mutex reinit_mutex;
	spinlock_t lock;
	अचिन्हित अक्षर regmap[AK4113_WRITABLE_REGS];
	काष्ठा snd_kcontrol *kctls[AK4113_CONTROLS];
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित दीर्घ errors[AK4113_NUM_ERRORS];
	अचिन्हित अक्षर rcs0;
	अचिन्हित अक्षर rcs1;
	अचिन्हित अक्षर rcs2;
	काष्ठा delayed_work work;
	अचिन्हित पूर्णांक check_flags;
	व्योम *change_callback_निजी;
	व्योम (*change_callback)(काष्ठा ak4113 *ak4113, अचिन्हित अक्षर c0,
			अचिन्हित अक्षर c1);
पूर्ण;

पूर्णांक snd_ak4113_create(काष्ठा snd_card *card, ak4113_पढ़ो_t *पढ़ो,
		ak4113_ग_लिखो_t *ग_लिखो,
		स्थिर अचिन्हित अक्षर *pgm,
		व्योम *निजी_data, काष्ठा ak4113 **r_ak4113);
व्योम snd_ak4113_reg_ग_लिखो(काष्ठा ak4113 *ak4113, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर mask, अचिन्हित अक्षर val);
व्योम snd_ak4113_reinit(काष्ठा ak4113 *ak4113);
पूर्णांक snd_ak4113_build(काष्ठा ak4113 *ak4113,
		काष्ठा snd_pcm_substream *capture_substream);
पूर्णांक snd_ak4113_बाह्यal_rate(काष्ठा ak4113 *ak4113);
पूर्णांक snd_ak4113_check_rate_and_errors(काष्ठा ak4113 *ak4113, अचिन्हित पूर्णांक flags);

#अगर_घोषित CONFIG_PM
व्योम snd_ak4113_suspend(काष्ठा ak4113 *chip);
व्योम snd_ak4113_resume(काष्ठा ak4113 *chip);
#अन्यथा
अटल अंतरभूत व्योम snd_ak4113_suspend(काष्ठा ak4113 *chip) अणुपूर्ण
अटल अंतरभूत व्योम snd_ak4113_resume(काष्ठा ak4113 *chip) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_AK4113_H */

