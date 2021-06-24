<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम C-Media CMI8338 and 8738 PCI soundcards.
 * Copyright (c) 2000 by Takashi Iwai <tiwai@suse.de>
 */
 
/* Does not work. Warning may block प्रणाली in capture mode */
/* #घोषणा USE_VAR48KRATE */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/sb.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("C-Media CMI8x38 PCI");
MODULE_LICENSE("GPL");

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK 1
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable चयनes */
अटल दीर्घ mpu_port[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)] = 1पूर्ण;
अटल दीर्घ fm_port[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)]=1पूर्ण;
अटल bool soft_ac3[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS-1)]=1पूर्ण;
#अगर_घोषित SUPPORT_JOYSTICK
अटल पूर्णांक joystick_port[SNDRV_CARDS];
#पूर्ण_अगर

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for C-Media PCI soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for C-Media PCI soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable C-Media PCI soundcard.");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port.");
module_param_hw_array(fm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fm_port, "FM port.");
module_param_array(soft_ac3, bool, शून्य, 0444);
MODULE_PARM_DESC(soft_ac3, "Software-conversion of raw SPDIF packets (model 033 only).");
#अगर_घोषित SUPPORT_JOYSTICK
module_param_hw_array(joystick_port, पूर्णांक, ioport, शून्य, 0444);
MODULE_PARM_DESC(joystick_port, "Joystick port address.");
#पूर्ण_अगर

/*
 * CM8x38 रेजिस्टरs definition
 */

#घोषणा CM_REG_FUNCTRL0		0x00
#घोषणा CM_RST_CH1		0x00080000
#घोषणा CM_RST_CH0		0x00040000
#घोषणा CM_CHEN1		0x00020000	/* ch1: enable */
#घोषणा CM_CHEN0		0x00010000	/* ch0: enable */
#घोषणा CM_PAUSE1		0x00000008	/* ch1: छोड़ो */
#घोषणा CM_PAUSE0		0x00000004	/* ch0: छोड़ो */
#घोषणा CM_CHADC1		0x00000002	/* ch1, 0:playback, 1:record */
#घोषणा CM_CHADC0		0x00000001	/* ch0, 0:playback, 1:record */

#घोषणा CM_REG_FUNCTRL1		0x04
#घोषणा CM_DSFC_MASK		0x0000E000	/* channel 1 (DAC?) sampling frequency */
#घोषणा CM_DSFC_SHIFT		13
#घोषणा CM_ASFC_MASK		0x00001C00	/* channel 0 (ADC?) sampling frequency */
#घोषणा CM_ASFC_SHIFT		10
#घोषणा CM_SPDF_1		0x00000200	/* SPDIF IN/OUT at channel B */
#घोषणा CM_SPDF_0		0x00000100	/* SPDIF OUT only channel A */
#घोषणा CM_SPDFLOOP		0x00000080	/* ext. SPDIIF/IN -> OUT loopback */
#घोषणा CM_SPDO2DAC		0x00000040	/* SPDIF/OUT can be heard from पूर्णांकernal DAC */
#घोषणा CM_INTRM		0x00000020	/* master control block (MCB) पूर्णांकerrupt enabled */
#घोषणा CM_BREQ			0x00000010	/* bus master enabled */
#घोषणा CM_VOICE_EN		0x00000008	/* legacy voice (SB16,FM) */
#घोषणा CM_UART_EN		0x00000004	/* legacy UART */
#घोषणा CM_JYSTK_EN		0x00000002	/* legacy joystick */
#घोषणा CM_ZVPORT		0x00000001	/* ZVPORT */

#घोषणा CM_REG_CHFORMAT		0x08

#घोषणा CM_CHB3D5C		0x80000000	/* 5,6 channels */
#घोषणा CM_FMOFFSET2		0x40000000	/* initial FM PCM offset 2 when Fmute=1 */
#घोषणा CM_CHB3D		0x20000000	/* 4 channels */

#घोषणा CM_CHIP_MASK1		0x1f000000
#घोषणा CM_CHIP_037		0x01000000
#घोषणा CM_SETLAT48		0x00800000	/* set latency समयr 48h */
#घोषणा CM_EDGEIRQ		0x00400000	/* emulated edge trigger legacy IRQ */
#घोषणा CM_SPD24SEL39		0x00200000	/* 24-bit spdअगर: model 039 */
#घोषणा CM_AC3EN1		0x00100000	/* enable AC3: model 037 */
#घोषणा CM_SPDIF_SELECT1	0x00080000	/* क्रम model <= 037 ? */
#घोषणा CM_SPD24SEL		0x00020000	/* 24bit spdअगर: model 037 */
/* #घोषणा CM_SPDIF_INVERSE	0x00010000 */ /* ??? */

#घोषणा CM_ADCBITLEN_MASK	0x0000C000	
#घोषणा CM_ADCBITLEN_16		0x00000000
#घोषणा CM_ADCBITLEN_15		0x00004000
#घोषणा CM_ADCBITLEN_14		0x00008000
#घोषणा CM_ADCBITLEN_13		0x0000C000

#घोषणा CM_ADCDACLEN_MASK	0x00003000	/* model 037 */
#घोषणा CM_ADCDACLEN_060	0x00000000
#घोषणा CM_ADCDACLEN_066	0x00001000
#घोषणा CM_ADCDACLEN_130	0x00002000
#घोषणा CM_ADCDACLEN_280	0x00003000

#घोषणा CM_ADCDLEN_MASK		0x00003000	/* model 039 */
#घोषणा CM_ADCDLEN_ORIGINAL	0x00000000
#घोषणा CM_ADCDLEN_EXTRA	0x00001000
#घोषणा CM_ADCDLEN_24K		0x00002000
#घोषणा CM_ADCDLEN_WEIGHT	0x00003000

#घोषणा CM_CH1_SRATE_176K	0x00000800
#घोषणा CM_CH1_SRATE_96K	0x00000800	/* model 055? */
#घोषणा CM_CH1_SRATE_88K	0x00000400
#घोषणा CM_CH0_SRATE_176K	0x00000200
#घोषणा CM_CH0_SRATE_96K	0x00000200	/* model 055? */
#घोषणा CM_CH0_SRATE_88K	0x00000100
#घोषणा CM_CH0_SRATE_128K	0x00000300
#घोषणा CM_CH0_SRATE_MASK	0x00000300

#घोषणा CM_SPDIF_INVERSE2	0x00000080	/* model 055? */
#घोषणा CM_DBLSPDS		0x00000040	/* द्विगुन SPDIF sample rate 88.2/96 */
#घोषणा CM_POLVALID		0x00000020	/* inverse SPDIF/IN valid bit */
#घोषणा CM_SPDLOCKED		0x00000010

#घोषणा CM_CH1FMT_MASK		0x0000000C	/* bit 3: 16 bits, bit 2: stereo */
#घोषणा CM_CH1FMT_SHIFT		2
#घोषणा CM_CH0FMT_MASK		0x00000003	/* bit 1: 16 bits, bit 0: stereo */
#घोषणा CM_CH0FMT_SHIFT		0

#घोषणा CM_REG_INT_HLDCLR	0x0C
#घोषणा CM_CHIP_MASK2		0xff000000
#घोषणा CM_CHIP_8768		0x20000000
#घोषणा CM_CHIP_055		0x08000000
#घोषणा CM_CHIP_039		0x04000000
#घोषणा CM_CHIP_039_6CH		0x01000000
#घोषणा CM_UNKNOWN_INT_EN	0x00080000	/* ? */
#घोषणा CM_TDMA_INT_EN		0x00040000
#घोषणा CM_CH1_INT_EN		0x00020000
#घोषणा CM_CH0_INT_EN		0x00010000

#घोषणा CM_REG_INT_STATUS	0x10
#घोषणा CM_INTR			0x80000000
#घोषणा CM_VCO			0x08000000	/* Voice Control? CMI8738 */
#घोषणा CM_MCBINT		0x04000000	/* Master Control Block पात cond.? */
#घोषणा CM_UARTINT		0x00010000
#घोषणा CM_LTDMAINT		0x00008000
#घोषणा CM_HTDMAINT		0x00004000
#घोषणा CM_XDO46		0x00000080	/* Modell 033? Direct programming EEPROM (पढ़ो data रेजिस्टर) */
#घोषणा CM_LHBTOG		0x00000040	/* High/Low status from DMA ctrl रेजिस्टर */
#घोषणा CM_LEG_HDMA		0x00000020	/* Legacy is in High DMA channel */
#घोषणा CM_LEG_STEREO		0x00000010	/* Legacy is in Stereo mode */
#घोषणा CM_CH1BUSY		0x00000008
#घोषणा CM_CH0BUSY		0x00000004
#घोषणा CM_CHINT1		0x00000002
#घोषणा CM_CHINT0		0x00000001

#घोषणा CM_REG_LEGACY_CTRL	0x14
#घोषणा CM_NXCHG		0x80000000	/* करोn't map base reg dword->sample */
#घोषणा CM_VMPU_MASK		0x60000000	/* MPU401 i/o port address */
#घोषणा CM_VMPU_330		0x00000000
#घोषणा CM_VMPU_320		0x20000000
#घोषणा CM_VMPU_310		0x40000000
#घोषणा CM_VMPU_300		0x60000000
#घोषणा CM_ENWR8237		0x10000000	/* enable bus master to ग_लिखो 8237 base reg */
#घोषणा CM_VSBSEL_MASK		0x0C000000	/* SB16 base address */
#घोषणा CM_VSBSEL_220		0x00000000
#घोषणा CM_VSBSEL_240		0x04000000
#घोषणा CM_VSBSEL_260		0x08000000
#घोषणा CM_VSBSEL_280		0x0C000000
#घोषणा CM_FMSEL_MASK		0x03000000	/* FM OPL3 base address */
#घोषणा CM_FMSEL_388		0x00000000
#घोषणा CM_FMSEL_3C8		0x01000000
#घोषणा CM_FMSEL_3E0		0x02000000
#घोषणा CM_FMSEL_3E8		0x03000000
#घोषणा CM_ENSPDOUT		0x00800000	/* enable XSPDIF/OUT to I/O पूर्णांकerface */
#घोषणा CM_SPDCOPYRHT		0x00400000	/* spdअगर in/out copyright bit */
#घोषणा CM_DAC2SPDO		0x00200000	/* enable wave+fm_midi -> SPDIF/OUT */
#घोषणा CM_INVIDWEN		0x00100000	/* पूर्णांकernal venकरोr ID ग_लिखो enable, model 039? */
#घोषणा CM_SETRETRY		0x00100000	/* 0: legacy i/o रुको (शेष), 1: legacy i/o bus retry */
#घोषणा CM_C_EEACCESS		0x00080000	/* direct programming eeprom regs */
#घोषणा CM_C_EECS		0x00040000
#घोषणा CM_C_EEDI46		0x00020000
#घोषणा CM_C_EECK46		0x00010000
#घोषणा CM_CHB3D6C		0x00008000	/* 5.1 channels support */
#घोषणा CM_CENTR2LIN		0x00004000	/* line-in as center out */
#घोषणा CM_BASE2LIN		0x00002000	/* line-in as bass out */
#घोषणा CM_EXBASEN		0x00001000	/* बाह्यal bass input enable */

#घोषणा CM_REG_MISC_CTRL	0x18
#घोषणा CM_PWD			0x80000000	/* घातer करोwn */
#घोषणा CM_RESET		0x40000000
#घोषणा CM_SFIL_MASK		0x30000000	/* filter control at front end DAC, model 037? */
#घोषणा CM_VMGAIN		0x10000000	/* analog master amp +6dB, model 039? */
#घोषणा CM_TXVX			0x08000000	/* model 037? */
#घोषणा CM_N4SPK3D		0x04000000	/* copy front to rear */
#घोषणा CM_SPDO5V		0x02000000	/* 5V spdअगर output (1 = 0.5v (coax)) */
#घोषणा CM_SPDIF48K		0x01000000	/* ग_लिखो */
#घोषणा CM_SPATUS48K		0x01000000	/* पढ़ो */
#घोषणा CM_ENDBDAC		0x00800000	/* enable द्विगुन dac */
#घोषणा CM_XCHGDAC		0x00400000	/* 0: front=ch0, 1: front=ch1 */
#घोषणा CM_SPD32SEL		0x00200000	/* 0: 16bit SPDIF, 1: 32bit */
#घोषणा CM_SPDFLOOPI		0x00100000	/* पूर्णांक. SPDIF-OUT -> पूर्णांक. IN */
#घोषणा CM_FM_EN		0x00080000	/* enable legacy FM */
#घोषणा CM_AC3EN2		0x00040000	/* enable AC3: model 039 */
#घोषणा CM_ENWRASID		0x00010000	/* choose writable पूर्णांकernal SUBID (audio) */
#घोषणा CM_VIDWPDSB		0x00010000	/* model 037? */
#घोषणा CM_SPDF_AC97		0x00008000	/* 0: SPDIF/OUT 44.1K, 1: 48K */
#घोषणा CM_MASK_EN		0x00004000	/* activate channel mask on legacy DMA */
#घोषणा CM_ENWRMSID		0x00002000	/* choose writable पूर्णांकernal SUBID (modem) */
#घोषणा CM_VIDWPPRT		0x00002000	/* model 037? */
#घोषणा CM_SखाताNB		0x00001000	/* filter stepping at front end DAC, model 037? */
#घोषणा CM_MMODE_MASK		0x00000E00	/* model DAA पूर्णांकerface mode */
#घोषणा CM_SPDIF_SELECT2	0x00000100	/* क्रम model > 039 ? */
#घोषणा CM_ENCENTER		0x00000080
#घोषणा CM_FLINKON		0x00000040	/* क्रमce modem link detection on, model 037 */
#घोषणा CM_MUTECH1		0x00000040	/* mute PCI ch1 to DAC */
#घोषणा CM_FLINKOFF		0x00000020	/* क्रमce modem link detection off, model 037 */
#घोषणा CM_MIDSMP		0x00000010	/* 1/2 पूर्णांकerpolation at front end DAC */
#घोषणा CM_UPDDMA_MASK		0x0000000C	/* TDMA position update notअगरication */
#घोषणा CM_UPDDMA_2048		0x00000000
#घोषणा CM_UPDDMA_1024		0x00000004
#घोषणा CM_UPDDMA_512		0x00000008
#घोषणा CM_UPDDMA_256		0x0000000C		
#घोषणा CM_TWAIT_MASK		0x00000003	/* model 037 */
#घोषणा CM_TWAIT1		0x00000002	/* FM i/o cycle, 0: 48, 1: 64 PCICLKs */
#घोषणा CM_TWAIT0		0x00000001	/* i/o cycle, 0: 4, 1: 6 PCICLKs */

#घोषणा CM_REG_TDMA_POSITION	0x1C
#घोषणा CM_TDMA_CNT_MASK	0xFFFF0000	/* current byte/word count */
#घोषणा CM_TDMA_ADR_MASK	0x0000FFFF	/* current address */

	/* byte */
#घोषणा CM_REG_MIXER0		0x20
#घोषणा CM_REG_SBVR		0x20		/* ग_लिखो: sb16 version */
#घोषणा CM_REG_DEV		0x20		/* पढ़ो: hardware device version */

#घोषणा CM_REG_MIXER21		0x21
#घोषणा CM_UNKNOWN_21_MASK	0x78		/* ? */
#घोषणा CM_X_ADPCM		0x04		/* SB16 ADPCM enable */
#घोषणा CM_PROINV		0x02		/* SBPro left/right channel चयनing */
#घोषणा CM_X_SB16		0x01		/* SB16 compatible */

#घोषणा CM_REG_SB16_DATA	0x22
#घोषणा CM_REG_SB16_ADDR	0x23

#घोषणा CM_REFFREQ_XIN		(315*1000*1000)/22	/* 14.31818 Mhz reference घड़ी frequency pin XIN */
#घोषणा CM_ADCMULT_XIN		512			/* Guessed (487 best क्रम 44.1kHz, not क्रम 88/176kHz) */
#घोषणा CM_TOLERANCE_RATE	0.001			/* Tolerance sample rate pitch (1000ppm) */
#घोषणा CM_MAXIMUM_RATE		80000000		/* Note more than 80MHz */

#घोषणा CM_REG_MIXER1		0x24
#घोषणा CM_FMMUTE		0x80	/* mute FM */
#घोषणा CM_FMMUTE_SHIFT		7
#घोषणा CM_WSMUTE		0x40	/* mute PCM */
#घोषणा CM_WSMUTE_SHIFT		6
#घोषणा CM_REAR2LIN		0x20	/* lin-in -> rear line out */
#घोषणा CM_REAR2LIN_SHIFT	5
#घोषणा CM_REAR2FRONT		0x10	/* exchange rear/front */
#घोषणा CM_REAR2FRONT_SHIFT	4
#घोषणा CM_WAVEINL		0x08	/* digital wave rec. left chan */
#घोषणा CM_WAVEINL_SHIFT	3
#घोषणा CM_WAVEINR		0x04	/* digical wave rec. right */
#घोषणा CM_WAVEINR_SHIFT	2
#घोषणा CM_X3DEN		0x02	/* 3D surround enable */
#घोषणा CM_X3DEN_SHIFT		1
#घोषणा CM_CDPLAY		0x01	/* enable SPDIF/IN PCM -> DAC */
#घोषणा CM_CDPLAY_SHIFT		0

#घोषणा CM_REG_MIXER2		0x25
#घोषणा CM_RAUXREN		0x80	/* AUX right capture */
#घोषणा CM_RAUXREN_SHIFT	7
#घोषणा CM_RAUXLEN		0x40	/* AUX left capture */
#घोषणा CM_RAUXLEN_SHIFT	6
#घोषणा CM_VAUXRM		0x20	/* AUX right mute */
#घोषणा CM_VAUXRM_SHIFT		5
#घोषणा CM_VAUXLM		0x10	/* AUX left mute */
#घोषणा CM_VAUXLM_SHIFT		4
#घोषणा CM_VADMIC_MASK		0x0e	/* mic gain level (0-3) << 1 */
#घोषणा CM_VADMIC_SHIFT		1
#घोषणा CM_MICGAINZ		0x01	/* mic boost */
#घोषणा CM_MICGAINZ_SHIFT	0

#घोषणा CM_REG_MIXER3		0x24
#घोषणा CM_REG_AUX_VOL		0x26
#घोषणा CM_VAUXL_MASK		0xf0
#घोषणा CM_VAUXR_MASK		0x0f

#घोषणा CM_REG_MISC		0x27
#घोषणा CM_UNKNOWN_27_MASK	0xd8	/* ? */
#घोषणा CM_XGPO1		0x20
// #घोषणा CM_XGPBIO		0x04
#घोषणा CM_MIC_CENTER_LFE	0x04	/* mic as center/lfe out? (model 039 or later?) */
#घोषणा CM_SPDIF_INVERSE	0x04	/* spdअगर input phase inverse (model 037) */
#घोषणा CM_SPDVALID		0x02	/* spdअगर input valid check */
#घोषणा CM_DMAUTO		0x01	/* SB16 DMA स्वतः detect */

#घोषणा CM_REG_AC97		0x28	/* hmmm.. करो we have ac97 link? */
/*
 * For CMI-8338 (0x28 - 0x2b) .. is this valid क्रम CMI-8738
 * or identical with AC97 codec?
 */
#घोषणा CM_REG_EXTERN_CODEC	CM_REG_AC97

/*
 * MPU401 pci port index address 0x40 - 0x4f (CMI-8738 spec ver. 0.6)
 */
#घोषणा CM_REG_MPU_PCI		0x40

/*
 * FM pci port index address 0x50 - 0x5f (CMI-8738 spec ver. 0.6)
 */
#घोषणा CM_REG_FM_PCI		0x50

/*
 * access from SB-mixer port
 */
#घोषणा CM_REG_EXTENT_IND	0xf0
#घोषणा CM_VPHONE_MASK		0xe0	/* Phone volume control (0-3) << 5 */
#घोषणा CM_VPHONE_SHIFT		5
#घोषणा CM_VPHOM		0x10	/* Phone mute control */
#घोषणा CM_VSPKM		0x08	/* Speaker mute control, शेष high */
#घोषणा CM_RLOOPREN		0x04    /* Rec. R-channel enable */
#घोषणा CM_RLOOPLEN		0x02	/* Rec. L-channel enable */
#घोषणा CM_VADMIC3		0x01	/* Mic record boost */

/*
 * CMI-8338 spec ver 0.5 (this is not valid क्रम CMI-8738):
 * the 8 रेजिस्टरs 0xf8 - 0xff are used क्रम programming m/n counter by the PLL
 * unit (पढ़ोonly?).
 */
#घोषणा CM_REG_PLL		0xf8

/*
 * extended रेजिस्टरs
 */
#घोषणा CM_REG_CH0_FRAME1	0x80	/* ग_लिखो: base address */
#घोषणा CM_REG_CH0_FRAME2	0x84	/* पढ़ो: current address */
#घोषणा CM_REG_CH1_FRAME1	0x88	/* 0-15: count of samples at bus master; buffer size */
#घोषणा CM_REG_CH1_FRAME2	0x8C	/* 16-31: count of samples at codec; fragment size */

#घोषणा CM_REG_EXT_MISC		0x90
#घोषणा CM_ADC48K44K		0x10000000	/* ADC parameters group, 0: 44k, 1: 48k */
#घोषणा CM_CHB3D8C		0x00200000	/* 7.1 channels support */
#घोषणा CM_SPD32FMT		0x00100000	/* SPDIF/IN 32k sample rate */
#घोषणा CM_ADC2SPDIF		0x00080000	/* ADC output to SPDIF/OUT */
#घोषणा CM_SHAREADC		0x00040000	/* DAC in ADC as Center/LFE */
#घोषणा CM_REALTCMP		0x00020000	/* monitor the CMPL/CMPR of ADC */
#घोषणा CM_INVLRCK		0x00010000	/* invert ZVPORT's LRCK */
#घोषणा CM_UNKNOWN_90_MASK	0x0000FFFF	/* ? */

/*
 * size of i/o region
 */
#घोषणा CM_EXTENT_CODEC	  0x100
#घोषणा CM_EXTENT_MIDI	  0x2
#घोषणा CM_EXTENT_SYNTH	  0x4


/*
 * channels क्रम playback / capture
 */
#घोषणा CM_CH_PLAY	0
#घोषणा CM_CH_CAPT	1

/*
 * flags to check device खोलो/बंद
 */
#घोषणा CM_OPEN_NONE	0
#घोषणा CM_OPEN_CH_MASK	0x01
#घोषणा CM_OPEN_DAC	0x10
#घोषणा CM_OPEN_ADC	0x20
#घोषणा CM_OPEN_SPDIF	0x40
#घोषणा CM_OPEN_MCHAN	0x80
#घोषणा CM_OPEN_PLAYBACK	(CM_CH_PLAY | CM_OPEN_DAC)
#घोषणा CM_OPEN_PLAYBACK2	(CM_CH_CAPT | CM_OPEN_DAC)
#घोषणा CM_OPEN_PLAYBACK_MULTI	(CM_CH_PLAY | CM_OPEN_DAC | CM_OPEN_MCHAN)
#घोषणा CM_OPEN_CAPTURE		(CM_CH_CAPT | CM_OPEN_ADC)
#घोषणा CM_OPEN_SPDIF_PLAYBACK	(CM_CH_PLAY | CM_OPEN_DAC | CM_OPEN_SPDIF)
#घोषणा CM_OPEN_SPDIF_CAPTURE	(CM_CH_CAPT | CM_OPEN_ADC | CM_OPEN_SPDIF)


#अगर CM_CH_PLAY == 1
#घोषणा CM_PLAYBACK_SRATE_176K	CM_CH1_SRATE_176K
#घोषणा CM_PLAYBACK_SPDF	CM_SPDF_1
#घोषणा CM_CAPTURE_SPDF		CM_SPDF_0
#अन्यथा
#घोषणा CM_PLAYBACK_SRATE_176K CM_CH0_SRATE_176K
#घोषणा CM_PLAYBACK_SPDF	CM_SPDF_0
#घोषणा CM_CAPTURE_SPDF		CM_SPDF_1
#पूर्ण_अगर


/*
 * driver data
 */

काष्ठा cmipci_pcm अणु
	काष्ठा snd_pcm_substream *substream;
	u8 running;		/* dac/adc running? */
	u8 fmt;			/* क्रमmat bits */
	u8 is_dac;
	u8 needs_silencing;
	अचिन्हित पूर्णांक dma_size;	/* in frames */
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक ch;	/* channel (0/1) */
	अचिन्हित पूर्णांक offset;	/* physical address of the buffer */
पूर्ण;

/* mixer elements toggled/resumed during ac3 playback */
काष्ठा cmipci_mixer_स्वतः_चयनes अणु
	स्थिर अक्षर *name;	/* चयन to toggle */
	पूर्णांक toggle_on;		/* value to change when ac3 mode */
पूर्ण;
अटल स्थिर काष्ठा cmipci_mixer_स्वतः_चयनes cm_saved_mixer[] = अणु
	अणु"PCM Playback Switch", 0पूर्ण,
	अणु"IEC958 Output Switch", 1पूर्ण,
	अणु"IEC958 Mix Analog", 0पूर्ण,
	// अणु"IEC958 Out To DAC", 1पूर्ण, // no दीर्घer used
	अणु"IEC958 Loop", 0पूर्ण,
पूर्ण;
#घोषणा CM_SAVED_MIXERS		ARRAY_SIZE(cm_saved_mixer)

काष्ठा cmipci अणु
	काष्ठा snd_card *card;

	काष्ठा pci_dev *pci;
	अचिन्हित पूर्णांक device;	/* device ID */
	पूर्णांक irq;

	अचिन्हित दीर्घ iobase;
	अचिन्हित पूर्णांक ctrl;	/* FUNCTRL0 current value */

	काष्ठा snd_pcm *pcm;		/* DAC/ADC PCM */
	काष्ठा snd_pcm *pcm2;	/* 2nd DAC */
	काष्ठा snd_pcm *pcm_spdअगर;	/* SPDIF */

	पूर्णांक chip_version;
	पूर्णांक max_channels;
	अचिन्हित पूर्णांक can_ac3_sw: 1;
	अचिन्हित पूर्णांक can_ac3_hw: 1;
	अचिन्हित पूर्णांक can_multi_ch: 1;
	अचिन्हित पूर्णांक can_96k: 1;	/* samplerate above 48k */
	अचिन्हित पूर्णांक करो_soft_ac3: 1;

	अचिन्हित पूर्णांक spdअगर_playback_avail: 1;	/* spdअगर पढ़ोy? */
	अचिन्हित पूर्णांक spdअगर_playback_enabled: 1;	/* spdअगर चयन enabled? */
	पूर्णांक spdअगर_counter;	/* क्रम software AC3 */

	अचिन्हित पूर्णांक dig_status;
	अचिन्हित पूर्णांक dig_pcm_status;

	काष्ठा snd_pcm_hardware *hw_info[3]; /* क्रम playbacks */

	पूर्णांक खोलोed[2];	/* खोलो mode */
	काष्ठा mutex खोलो_mutex;

	अचिन्हित पूर्णांक mixer_insensitive: 1;
	काष्ठा snd_kcontrol *mixer_res_ctl[CM_SAVED_MIXERS];
	पूर्णांक mixer_res_status[CM_SAVED_MIXERS];

	काष्ठा cmipci_pcm channel[2];	/* ch0 - DAC, ch1 - ADC or 2nd DAC */

	/* बाह्यal MIDI */
	काष्ठा snd_rawmidi *rmidi;

#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा gameport *gameport;
#पूर्ण_अगर

	spinlock_t reg_lock;

#अगर_घोषित CONFIG_PM_SLEEP
	अचिन्हित पूर्णांक saved_regs[0x20];
	अचिन्हित अक्षर saved_mixers[0x20];
#पूर्ण_अगर
पूर्ण;


/* पढ़ो/ग_लिखो operations क्रम dword रेजिस्टर */
अटल अंतरभूत व्योम snd_cmipci_ग_लिखो(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक data)
अणु
	outl(data, cm->iobase + cmd);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_cmipci_पढ़ो(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd)
अणु
	वापस inl(cm->iobase + cmd);
पूर्ण

/* पढ़ो/ग_लिखो operations क्रम word रेजिस्टर */
अटल अंतरभूत व्योम snd_cmipci_ग_लिखो_w(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd, अचिन्हित लघु data)
अणु
	outw(data, cm->iobase + cmd);
पूर्ण

अटल अंतरभूत अचिन्हित लघु snd_cmipci_पढ़ो_w(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd)
अणु
	वापस inw(cm->iobase + cmd);
पूर्ण

/* पढ़ो/ग_लिखो operations क्रम byte रेजिस्टर */
अटल अंतरभूत व्योम snd_cmipci_ग_लिखो_b(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd, अचिन्हित अक्षर data)
अणु
	outb(data, cm->iobase + cmd);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर snd_cmipci_पढ़ो_b(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd)
अणु
	वापस inb(cm->iobase + cmd);
पूर्ण

/* bit operations क्रम dword रेजिस्टर */
अटल पूर्णांक snd_cmipci_set_bit(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक flag)
अणु
	अचिन्हित पूर्णांक val, oval;
	val = oval = inl(cm->iobase + cmd);
	val |= flag;
	अगर (val == oval)
		वापस 0;
	outl(val, cm->iobase + cmd);
	वापस 1;
पूर्ण

अटल पूर्णांक snd_cmipci_clear_bit(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक flag)
अणु
	अचिन्हित पूर्णांक val, oval;
	val = oval = inl(cm->iobase + cmd);
	val &= ~flag;
	अगर (val == oval)
		वापस 0;
	outl(val, cm->iobase + cmd);
	वापस 1;
पूर्ण

/* bit operations क्रम byte रेजिस्टर */
अटल पूर्णांक snd_cmipci_set_bit_b(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd, अचिन्हित अक्षर flag)
अणु
	अचिन्हित अक्षर val, oval;
	val = oval = inb(cm->iobase + cmd);
	val |= flag;
	अगर (val == oval)
		वापस 0;
	outb(val, cm->iobase + cmd);
	वापस 1;
पूर्ण

अटल पूर्णांक snd_cmipci_clear_bit_b(काष्ठा cmipci *cm, अचिन्हित पूर्णांक cmd, अचिन्हित अक्षर flag)
अणु
	अचिन्हित अक्षर val, oval;
	val = oval = inb(cm->iobase + cmd);
	val &= ~flag;
	अगर (val == oval)
		वापस 0;
	outb(val, cm->iobase + cmd);
	वापस 1;
पूर्ण


/*
 * PCM पूर्णांकerface
 */

/*
 * calculate frequency
 */

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु 5512, 11025, 22050, 44100, 8000, 16000, 32000, 48000 पूर्ण;

अटल अचिन्हित पूर्णांक snd_cmipci_rate_freq(अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rates); i++) अणु
		अगर (rates[i] == rate)
			वापस i;
	पूर्ण
	snd_BUG();
	वापस 0;
पूर्ण

#अगर_घोषित USE_VAR48KRATE
/*
 * Determine PLL values क्रम frequency setup, maybe the CMI8338 (CMI8738???)
 * करोes it this way .. maybe not.  Never get any inक्रमmation from C-Media about
 * that <werner@suse.de>.
 */
अटल पूर्णांक snd_cmipci_pll_rmn(अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक adcmult, पूर्णांक *r, पूर्णांक *m, पूर्णांक *n)
अणु
	अचिन्हित पूर्णांक delta, tolerance;
	पूर्णांक xm, xn, xr;

	क्रम (*r = 0; rate < CM_MAXIMUM_RATE/adcmult; *r += (1<<5))
		rate <<= 1;
	*n = -1;
	अगर (*r > 0xff)
		जाओ out;
	tolerance = rate*CM_TOLERANCE_RATE;

	क्रम (xn = (1+2); xn < (0x1f+2); xn++) अणु
		क्रम (xm = (1+2); xm < (0xff+2); xm++) अणु
			xr = ((CM_REFFREQ_XIN/adcmult) * xm) / xn;

			अगर (xr < rate)
				delta = rate - xr;
			अन्यथा
				delta = xr - rate;

			/*
			 * If we found one, remember this,
			 * and try to find a बंदr one
			 */
			अगर (delta < tolerance) अणु
				tolerance = delta;
				*m = xm - 2;
				*n = xn - 2;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस (*n > -1);
पूर्ण

/*
 * Program pll रेजिस्टर bits, I assume that the 8 रेजिस्टरs 0xf8 up to 0xff
 * are mapped onto the 8 ADC/DAC sampling frequency which can be chosen
 * at the रेजिस्टर CM_REG_FUNCTRL1 (0x04).
 * Problem: other ways are also possible (any inक्रमmation about that?)
 */
अटल व्योम snd_cmipci_set_pll(काष्ठा cmipci *cm, अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक slot)
अणु
	अचिन्हित पूर्णांक reg = CM_REG_PLL + slot;
	/*
	 * Guess that this programs at reg. 0x04 the pos 15:13/12:10
	 * क्रम DSFC/ASFC (000 up to 111).
	 */

	/* FIXME: Init (Do we've to set an other रेजिस्टर first beक्रमe programming?) */

	/* FIXME: Is this correct? Or shouldn't the m/n/r values be used क्रम that? */
	snd_cmipci_ग_लिखो_b(cm, reg, rate>>8);
	snd_cmipci_ग_लिखो_b(cm, reg, rate&0xff);

	/* FIXME: Setup (Do we've to set an other रेजिस्टर first to enable this?) */
पूर्ण
#पूर्ण_अगर /* USE_VAR48KRATE */

अटल पूर्णांक snd_cmipci_playback2_hw_params(काष्ठा snd_pcm_substream *substream,
					  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	अगर (params_channels(hw_params) > 2) अणु
		mutex_lock(&cm->खोलो_mutex);
		अगर (cm->खोलोed[CM_CH_PLAY]) अणु
			mutex_unlock(&cm->खोलो_mutex);
			वापस -EBUSY;
		पूर्ण
		/* reserve the channel A */
		cm->खोलोed[CM_CH_PLAY] = CM_OPEN_PLAYBACK_MULTI;
		mutex_unlock(&cm->खोलो_mutex);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_cmipci_ch_reset(काष्ठा cmipci *cm, पूर्णांक ch)
अणु
	पूर्णांक reset = CM_RST_CH0 << (cm->channel[ch].ch);
	snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl | reset);
	snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl & ~reset);
	udelay(10);
पूर्ण


/*
 */

अटल स्थिर अचिन्हित पूर्णांक hw_channels[] = अणु1, 2, 4, 6, 8पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_channels_4 = अणु
	.count = 3,
	.list = hw_channels,
	.mask = 0,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_channels_6 = अणु
	.count = 4,
	.list = hw_channels,
	.mask = 0,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_channels_8 = अणु
	.count = 5,
	.list = hw_channels,
	.mask = 0,
पूर्ण;

अटल पूर्णांक set_dac_channels(काष्ठा cmipci *cm, काष्ठा cmipci_pcm *rec, पूर्णांक channels)
अणु
	अगर (channels > 2) अणु
		अगर (!cm->can_multi_ch || !rec->ch)
			वापस -EINVAL;
		अगर (rec->fmt != 0x03) /* stereo 16bit only */
			वापस -EINVAL;
	पूर्ण

	अगर (cm->can_multi_ch) अणु
		spin_lock_irq(&cm->reg_lock);
		अगर (channels > 2) अणु
			snd_cmipci_set_bit(cm, CM_REG_LEGACY_CTRL, CM_NXCHG);
			snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_XCHGDAC);
		पूर्ण अन्यथा अणु
			snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_NXCHG);
			snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_XCHGDAC);
		पूर्ण
		अगर (channels == 8)
			snd_cmipci_set_bit(cm, CM_REG_EXT_MISC, CM_CHB3D8C);
		अन्यथा
			snd_cmipci_clear_bit(cm, CM_REG_EXT_MISC, CM_CHB3D8C);
		अगर (channels == 6) अणु
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_CHB3D5C);
			snd_cmipci_set_bit(cm, CM_REG_LEGACY_CTRL, CM_CHB3D6C);
		पूर्ण अन्यथा अणु
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_CHB3D5C);
			snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_CHB3D6C);
		पूर्ण
		अगर (channels == 4)
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_CHB3D);
		अन्यथा
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_CHB3D);
		spin_unlock_irq(&cm->reg_lock);
	पूर्ण
	वापस 0;
पूर्ण


/*
 * prepare playback/capture channel
 * channel to be used must have been set in rec->ch.
 */
अटल पूर्णांक snd_cmipci_pcm_prepare(काष्ठा cmipci *cm, काष्ठा cmipci_pcm *rec,
				 काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित पूर्णांक reg, freq, freq_ext, val;
	अचिन्हित पूर्णांक period_size;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	rec->fmt = 0;
	rec->shअगरt = 0;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) >= 16) अणु
		rec->fmt |= 0x02;
		अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) > 16)
			rec->shअगरt++; /* 24/32bit */
	पूर्ण
	अगर (runसमय->channels > 1)
		rec->fmt |= 0x01;
	अगर (rec->is_dac && set_dac_channels(cm, rec, runसमय->channels) < 0) अणु
		dev_dbg(cm->card->dev, "cannot set dac channels\n");
		वापस -EINVAL;
	पूर्ण

	rec->offset = runसमय->dma_addr;
	/* buffer and period sizes in frame */
	rec->dma_size = runसमय->buffer_size << rec->shअगरt;
	period_size = runसमय->period_size << rec->shअगरt;
	अगर (runसमय->channels > 2) अणु
		/* multi-channels */
		rec->dma_size = (rec->dma_size * runसमय->channels) / 2;
		period_size = (period_size * runसमय->channels) / 2;
	पूर्ण

	spin_lock_irq(&cm->reg_lock);

	/* set buffer address */
	reg = rec->ch ? CM_REG_CH1_FRAME1 : CM_REG_CH0_FRAME1;
	snd_cmipci_ग_लिखो(cm, reg, rec->offset);
	/* program sample counts */
	reg = rec->ch ? CM_REG_CH1_FRAME2 : CM_REG_CH0_FRAME2;
	snd_cmipci_ग_लिखो_w(cm, reg, rec->dma_size - 1);
	snd_cmipci_ग_लिखो_w(cm, reg + 2, period_size - 1);

	/* set adc/dac flag */
	val = rec->ch ? CM_CHADC1 : CM_CHADC0;
	अगर (rec->is_dac)
		cm->ctrl &= ~val;
	अन्यथा
		cm->ctrl |= val;
	snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl);
	/* dev_dbg(cm->card->dev, "functrl0 = %08x\n", cm->ctrl); */

	/* set sample rate */
	freq = 0;
	freq_ext = 0;
	अगर (runसमय->rate > 48000)
		चयन (runसमय->rate) अणु
		हाल 88200:  freq_ext = CM_CH0_SRATE_88K; अवरोध;
		हाल 96000:  freq_ext = CM_CH0_SRATE_96K; अवरोध;
		हाल 128000: freq_ext = CM_CH0_SRATE_128K; अवरोध;
		शेष:     snd_BUG(); अवरोध;
		पूर्ण
	अन्यथा
		freq = snd_cmipci_rate_freq(runसमय->rate);
	val = snd_cmipci_पढ़ो(cm, CM_REG_FUNCTRL1);
	अगर (rec->ch) अणु
		val &= ~CM_DSFC_MASK;
		val |= (freq << CM_DSFC_SHIFT) & CM_DSFC_MASK;
	पूर्ण अन्यथा अणु
		val &= ~CM_ASFC_MASK;
		val |= (freq << CM_ASFC_SHIFT) & CM_ASFC_MASK;
	पूर्ण
	snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL1, val);
	dev_dbg(cm->card->dev, "functrl1 = %08x\n", val);

	/* set क्रमmat */
	val = snd_cmipci_पढ़ो(cm, CM_REG_CHFORMAT);
	अगर (rec->ch) अणु
		val &= ~CM_CH1FMT_MASK;
		val |= rec->fmt << CM_CH1FMT_SHIFT;
	पूर्ण अन्यथा अणु
		val &= ~CM_CH0FMT_MASK;
		val |= rec->fmt << CM_CH0FMT_SHIFT;
	पूर्ण
	अगर (cm->can_96k) अणु
		val &= ~(CM_CH0_SRATE_MASK << (rec->ch * 2));
		val |= freq_ext << (rec->ch * 2);
	पूर्ण
	snd_cmipci_ग_लिखो(cm, CM_REG_CHFORMAT, val);
	dev_dbg(cm->card->dev, "chformat = %08x\n", val);

	अगर (!rec->is_dac && cm->chip_version) अणु
		अगर (runसमय->rate > 44100)
			snd_cmipci_set_bit(cm, CM_REG_EXT_MISC, CM_ADC48K44K);
		अन्यथा
			snd_cmipci_clear_bit(cm, CM_REG_EXT_MISC, CM_ADC48K44K);
	पूर्ण

	rec->running = 0;
	spin_unlock_irq(&cm->reg_lock);

	वापस 0;
पूर्ण

/*
 * PCM trigger/stop
 */
अटल पूर्णांक snd_cmipci_pcm_trigger(काष्ठा cmipci *cm, काष्ठा cmipci_pcm *rec,
				  पूर्णांक cmd)
अणु
	अचिन्हित पूर्णांक पूर्णांकhld, chen, reset, छोड़ो;
	पूर्णांक result = 0;

	पूर्णांकhld = CM_CH0_INT_EN << rec->ch;
	chen = CM_CHEN0 << rec->ch;
	reset = CM_RST_CH0 << rec->ch;
	छोड़ो = CM_PAUSE0 << rec->ch;

	spin_lock(&cm->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		rec->running = 1;
		/* set पूर्णांकerrupt */
		snd_cmipci_set_bit(cm, CM_REG_INT_HLDCLR, पूर्णांकhld);
		cm->ctrl |= chen;
		/* enable channel */
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl);
		dev_dbg(cm->card->dev, "functrl0 = %08x\n", cm->ctrl);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		rec->running = 0;
		/* disable पूर्णांकerrupt */
		snd_cmipci_clear_bit(cm, CM_REG_INT_HLDCLR, पूर्णांकhld);
		/* reset */
		cm->ctrl &= ~chen;
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl | reset);
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl & ~reset);
		rec->needs_silencing = rec->is_dac;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		cm->ctrl |= छोड़ो;
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		cm->ctrl &= ~छोड़ो;
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl);
		अवरोध;
	शेष:
		result = -EINVAL;
		अवरोध;
	पूर्ण
	spin_unlock(&cm->reg_lock);
	वापस result;
पूर्ण

/*
 * वापस the current poपूर्णांकer
 */
अटल snd_pcm_uframes_t snd_cmipci_pcm_poपूर्णांकer(काष्ठा cmipci *cm, काष्ठा cmipci_pcm *rec,
						काष्ठा snd_pcm_substream *substream)
अणु
	माप_प्रकार ptr;
	अचिन्हित पूर्णांक reg, rem, tries;

	अगर (!rec->running)
		वापस 0;
#अगर 1 // this seems better..
	reg = rec->ch ? CM_REG_CH1_FRAME2 : CM_REG_CH0_FRAME2;
	क्रम (tries = 0; tries < 3; tries++) अणु
		rem = snd_cmipci_पढ़ो_w(cm, reg);
		अगर (rem < rec->dma_size)
			जाओ ok;
	पूर्ण 
	dev_err(cm->card->dev, "invalid PCM pointer: %#x\n", rem);
	वापस SNDRV_PCM_POS_XRUN;
ok:
	ptr = (rec->dma_size - (rem + 1)) >> rec->shअगरt;
#अन्यथा
	reg = rec->ch ? CM_REG_CH1_FRAME1 : CM_REG_CH0_FRAME1;
	ptr = snd_cmipci_पढ़ो(cm, reg) - rec->offset;
	ptr = bytes_to_frames(substream->runसमय, ptr);
#पूर्ण_अगर
	अगर (substream->runसमय->channels > 2)
		ptr = (ptr * 2) / substream->runसमय->channels;
	वापस ptr;
पूर्ण

/*
 * playback
 */

अटल पूर्णांक snd_cmipci_playback_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	वापस snd_cmipci_pcm_trigger(cm, &cm->channel[CM_CH_PLAY], cmd);
पूर्ण

अटल snd_pcm_uframes_t snd_cmipci_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	वापस snd_cmipci_pcm_poपूर्णांकer(cm, &cm->channel[CM_CH_PLAY], substream);
पूर्ण



/*
 * capture
 */

अटल पूर्णांक snd_cmipci_capture_trigger(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक cmd)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	वापस snd_cmipci_pcm_trigger(cm, &cm->channel[CM_CH_CAPT], cmd);
पूर्ण

अटल snd_pcm_uframes_t snd_cmipci_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	वापस snd_cmipci_pcm_poपूर्णांकer(cm, &cm->channel[CM_CH_CAPT], substream);
पूर्ण


/*
 * hw preparation क्रम spdअगर
 */

अटल पूर्णांक snd_cmipci_spdअगर_शेष_info(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i;

	spin_lock_irq(&chip->reg_lock);
	क्रम (i = 0; i < 4; i++)
		ucontrol->value.iec958.status[i] = (chip->dig_status >> (i * 8)) & 0xff;
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, change;
	अचिन्हित पूर्णांक val;

	val = 0;
	spin_lock_irq(&chip->reg_lock);
	क्रम (i = 0; i < 4; i++)
		val |= (अचिन्हित पूर्णांक)ucontrol->value.iec958.status[i] << (i * 8);
	change = val != chip->dig_status;
	chip->dig_status = val;
	spin_unlock_irq(&chip->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_spdअगर_शेष =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =		snd_cmipci_spdअगर_शेष_info,
	.get =		snd_cmipci_spdअगर_शेष_get,
	.put =		snd_cmipci_spdअगर_शेष_put
पूर्ण;

अटल पूर्णांक snd_cmipci_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_spdअगर_mask =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,CON_MASK),
	.info =		snd_cmipci_spdअगर_mask_info,
	.get =		snd_cmipci_spdअगर_mask_get,
पूर्ण;

अटल पूर्णांक snd_cmipci_spdअगर_stream_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i;

	spin_lock_irq(&chip->reg_lock);
	क्रम (i = 0; i < 4; i++)
		ucontrol->value.iec958.status[i] = (chip->dig_pcm_status >> (i * 8)) & 0xff;
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, change;
	अचिन्हित पूर्णांक val;

	val = 0;
	spin_lock_irq(&chip->reg_lock);
	क्रम (i = 0; i < 4; i++)
		val |= (अचिन्हित पूर्णांक)ucontrol->value.iec958.status[i] << (i * 8);
	change = val != chip->dig_pcm_status;
	chip->dig_pcm_status = val;
	spin_unlock_irq(&chip->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_spdअगर_stream =
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
	.info =		snd_cmipci_spdअगर_stream_info,
	.get =		snd_cmipci_spdअगर_stream_get,
	.put =		snd_cmipci_spdअगर_stream_put
पूर्ण;

/*
 */

/* save mixer setting and mute क्रम AC3 playback */
अटल पूर्णांक save_mixer_state(काष्ठा cmipci *cm)
अणु
	अगर (! cm->mixer_insensitive) अणु
		काष्ठा snd_ctl_elem_value *val;
		अचिन्हित पूर्णांक i;

		val = kदो_स्मृति(माप(*val), GFP_KERNEL);
		अगर (!val)
			वापस -ENOMEM;
		क्रम (i = 0; i < CM_SAVED_MIXERS; i++) अणु
			काष्ठा snd_kcontrol *ctl = cm->mixer_res_ctl[i];
			अगर (ctl) अणु
				पूर्णांक event;
				स_रखो(val, 0, माप(*val));
				ctl->get(ctl, val);
				cm->mixer_res_status[i] = val->value.पूर्णांकeger.value[0];
				val->value.पूर्णांकeger.value[0] = cm_saved_mixer[i].toggle_on;
				event = SNDRV_CTL_EVENT_MASK_INFO;
				अगर (cm->mixer_res_status[i] != val->value.पूर्णांकeger.value[0]) अणु
					ctl->put(ctl, val); /* toggle */
					event |= SNDRV_CTL_EVENT_MASK_VALUE;
				पूर्ण
				ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
				snd_ctl_notअगरy(cm->card, event, &ctl->id);
			पूर्ण
		पूर्ण
		kमुक्त(val);
		cm->mixer_insensitive = 1;
	पूर्ण
	वापस 0;
पूर्ण


/* restore the previously saved mixer status */
अटल व्योम restore_mixer_state(काष्ठा cmipci *cm)
अणु
	अगर (cm->mixer_insensitive) अणु
		काष्ठा snd_ctl_elem_value *val;
		अचिन्हित पूर्णांक i;

		val = kदो_स्मृति(माप(*val), GFP_KERNEL);
		अगर (!val)
			वापस;
		cm->mixer_insensitive = 0; /* at first clear this;
					      otherwise the changes will be ignored */
		क्रम (i = 0; i < CM_SAVED_MIXERS; i++) अणु
			काष्ठा snd_kcontrol *ctl = cm->mixer_res_ctl[i];
			अगर (ctl) अणु
				पूर्णांक event;

				स_रखो(val, 0, माप(*val));
				ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
				ctl->get(ctl, val);
				event = SNDRV_CTL_EVENT_MASK_INFO;
				अगर (val->value.पूर्णांकeger.value[0] != cm->mixer_res_status[i]) अणु
					val->value.पूर्णांकeger.value[0] = cm->mixer_res_status[i];
					ctl->put(ctl, val);
					event |= SNDRV_CTL_EVENT_MASK_VALUE;
				पूर्ण
				snd_ctl_notअगरy(cm->card, event, &ctl->id);
			पूर्ण
		पूर्ण
		kमुक्त(val);
	पूर्ण
पूर्ण

/* spinlock held! */
अटल व्योम setup_ac3(काष्ठा cmipci *cm, काष्ठा snd_pcm_substream *subs, पूर्णांक करो_ac3, पूर्णांक rate)
अणु
	अगर (करो_ac3) अणु
		/* AC3EN क्रम 037 */
		snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_AC3EN1);
		/* AC3EN क्रम 039 */
		snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_AC3EN2);
	
		अगर (cm->can_ac3_hw) अणु
			/* SPD24SEL क्रम 037, 0x02 */
			/* SPD24SEL क्रम 039, 0x20, but cannot be set */
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_SPD24SEL);
			snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
		पूर्ण अन्यथा अणु /* can_ac3_sw */
			/* SPD32SEL क्रम 037 & 039, 0x20 */
			snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
			/* set 176K sample rate to fix 033 HW bug */
			अगर (cm->chip_version == 33) अणु
				अगर (rate >= 48000) अणु
					snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_PLAYBACK_SRATE_176K);
				पूर्ण अन्यथा अणु
					snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_PLAYBACK_SRATE_176K);
				पूर्ण
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_AC3EN1);
		snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_AC3EN2);

		अगर (cm->can_ac3_hw) अणु
			/* chip model >= 37 */
			अगर (snd_pcm_क्रमmat_width(subs->runसमय->क्रमmat) > 16) अणु
				snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
				snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_SPD24SEL);
			पूर्ण अन्यथा अणु
				snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
				snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_SPD24SEL);
			पूर्ण
		पूर्ण अन्यथा अणु
			snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_SPD24SEL);
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_PLAYBACK_SRATE_176K);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक setup_spdअगर_playback(काष्ठा cmipci *cm, काष्ठा snd_pcm_substream *subs, पूर्णांक up, पूर्णांक करो_ac3)
अणु
	पूर्णांक rate, err;

	rate = subs->runसमय->rate;

	अगर (up && करो_ac3)
		अगर ((err = save_mixer_state(cm)) < 0)
			वापस err;

	spin_lock_irq(&cm->reg_lock);
	cm->spdअगर_playback_avail = up;
	अगर (up) अणु
		/* they are controlled via "IEC958 Output Switch" */
		/* snd_cmipci_set_bit(cm, CM_REG_LEGACY_CTRL, CM_ENSPDOUT); */
		/* snd_cmipci_set_bit(cm, CM_REG_FUNCTRL1, CM_SPDO2DAC); */
		अगर (cm->spdअगर_playback_enabled)
			snd_cmipci_set_bit(cm, CM_REG_FUNCTRL1, CM_PLAYBACK_SPDF);
		setup_ac3(cm, subs, करो_ac3, rate);

		अगर (rate == 48000 || rate == 96000)
			snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_SPDIF48K | CM_SPDF_AC97);
		अन्यथा
			snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPDIF48K | CM_SPDF_AC97);
		अगर (rate > 48000)
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
		अन्यथा
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
	पूर्ण अन्यथा अणु
		/* they are controlled via "IEC958 Output Switch" */
		/* snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_ENSPDOUT); */
		/* snd_cmipci_clear_bit(cm, CM_REG_FUNCTRL1, CM_SPDO2DAC); */
		snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
		snd_cmipci_clear_bit(cm, CM_REG_FUNCTRL1, CM_PLAYBACK_SPDF);
		setup_ac3(cm, subs, 0, 0);
	पूर्ण
	spin_unlock_irq(&cm->reg_lock);
	वापस 0;
पूर्ण


/*
 * preparation
 */

/* playback - enable spdअगर only on the certain condition */
अटल पूर्णांक snd_cmipci_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	पूर्णांक rate = substream->runसमय->rate;
	पूर्णांक err, करो_spdअगर, करो_ac3 = 0;

	करो_spdअगर = (rate >= 44100 && rate <= 96000 &&
		    substream->runसमय->क्रमmat == SNDRV_PCM_FORMAT_S16_LE &&
		    substream->runसमय->channels == 2);
	अगर (करो_spdअगर && cm->can_ac3_hw) 
		करो_ac3 = cm->dig_pcm_status & IEC958_AES0_NONAUDIO;
	अगर ((err = setup_spdअगर_playback(cm, substream, करो_spdअगर, करो_ac3)) < 0)
		वापस err;
	वापस snd_cmipci_pcm_prepare(cm, &cm->channel[CM_CH_PLAY], substream);
पूर्ण

/* playback  (via device #2) - enable spdअगर always */
अटल पूर्णांक snd_cmipci_playback_spdअगर_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	पूर्णांक err, करो_ac3;

	अगर (cm->can_ac3_hw) 
		करो_ac3 = cm->dig_pcm_status & IEC958_AES0_NONAUDIO;
	अन्यथा
		करो_ac3 = 1; /* करोesn't matter */
	अगर ((err = setup_spdअगर_playback(cm, substream, 1, करो_ac3)) < 0)
		वापस err;
	वापस snd_cmipci_pcm_prepare(cm, &cm->channel[CM_CH_PLAY], substream);
पूर्ण

/*
 * Apparently, the samples last played on channel A stay in some buffer, even
 * after the channel is reset, and get added to the data क्रम the rear DACs when
 * playing a multichannel stream on channel B.  This is likely to generate
 * wraparounds and thus distortions.
 * To aव्योम this, we play at least one zero sample after the actual stream has
 * stopped.
 */
अटल व्योम snd_cmipci_silence_hack(काष्ठा cmipci *cm, काष्ठा cmipci_pcm *rec)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = rec->substream->runसमय;
	अचिन्हित पूर्णांक reg, val;

	अगर (rec->needs_silencing && runसमय && runसमय->dma_area) अणु
		/* set up a small silence buffer */
		स_रखो(runसमय->dma_area, 0, PAGE_SIZE);
		reg = rec->ch ? CM_REG_CH1_FRAME2 : CM_REG_CH0_FRAME2;
		val = ((PAGE_SIZE / 4) - 1) | (((PAGE_SIZE / 4) / 2 - 1) << 16);
		snd_cmipci_ग_लिखो(cm, reg, val);
	
		/* configure क्रम 16 bits, 2 channels, 8 kHz */
		अगर (runसमय->channels > 2)
			set_dac_channels(cm, rec, 2);
		spin_lock_irq(&cm->reg_lock);
		val = snd_cmipci_पढ़ो(cm, CM_REG_FUNCTRL1);
		val &= ~(CM_ASFC_MASK << (rec->ch * 3));
		val |= (4 << CM_ASFC_SHIFT) << (rec->ch * 3);
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL1, val);
		val = snd_cmipci_पढ़ो(cm, CM_REG_CHFORMAT);
		val &= ~(CM_CH0FMT_MASK << (rec->ch * 2));
		val |= (3 << CM_CH0FMT_SHIFT) << (rec->ch * 2);
		अगर (cm->can_96k)
			val &= ~(CM_CH0_SRATE_MASK << (rec->ch * 2));
		snd_cmipci_ग_लिखो(cm, CM_REG_CHFORMAT, val);
	
		/* start stream (we करोn't need पूर्णांकerrupts) */
		cm->ctrl |= CM_CHEN0 << rec->ch;
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl);
		spin_unlock_irq(&cm->reg_lock);

		msleep(1);

		/* stop and reset stream */
		spin_lock_irq(&cm->reg_lock);
		cm->ctrl &= ~(CM_CHEN0 << rec->ch);
		val = CM_RST_CH0 << rec->ch;
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl | val);
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, cm->ctrl & ~val);
		spin_unlock_irq(&cm->reg_lock);

		rec->needs_silencing = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_cmipci_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	setup_spdअगर_playback(cm, substream, 0, 0);
	restore_mixer_state(cm);
	snd_cmipci_silence_hack(cm, &cm->channel[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_playback2_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	snd_cmipci_silence_hack(cm, &cm->channel[1]);
	वापस 0;
पूर्ण

/* capture */
अटल पूर्णांक snd_cmipci_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	वापस snd_cmipci_pcm_prepare(cm, &cm->channel[CM_CH_CAPT], substream);
पूर्ण

/* capture with spdअगर (via device #2) */
अटल पूर्णांक snd_cmipci_capture_spdअगर_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);

	spin_lock_irq(&cm->reg_lock);
	snd_cmipci_set_bit(cm, CM_REG_FUNCTRL1, CM_CAPTURE_SPDF);
	अगर (cm->can_96k) अणु
		अगर (substream->runसमय->rate > 48000)
			snd_cmipci_set_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
		अन्यथा
			snd_cmipci_clear_bit(cm, CM_REG_CHFORMAT, CM_DBLSPDS);
	पूर्ण
	अगर (snd_pcm_क्रमmat_width(substream->runसमय->क्रमmat) > 16)
		snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
	अन्यथा
		snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);

	spin_unlock_irq(&cm->reg_lock);

	वापस snd_cmipci_pcm_prepare(cm, &cm->channel[CM_CH_CAPT], substream);
पूर्ण

अटल पूर्णांक snd_cmipci_capture_spdअगर_hw_मुक्त(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(subs);

	spin_lock_irq(&cm->reg_lock);
	snd_cmipci_clear_bit(cm, CM_REG_FUNCTRL1, CM_CAPTURE_SPDF);
	snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_SPD32SEL);
	spin_unlock_irq(&cm->reg_lock);

	वापस 0;
पूर्ण


/*
 * पूर्णांकerrupt handler
 */
अटल irqवापस_t snd_cmipci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cmipci *cm = dev_id;
	अचिन्हित पूर्णांक status, mask = 0;
	
	/* fastpath out, to ease पूर्णांकerrupt sharing */
	status = snd_cmipci_पढ़ो(cm, CM_REG_INT_STATUS);
	अगर (!(status & CM_INTR))
		वापस IRQ_NONE;

	/* acknowledge पूर्णांकerrupt */
	spin_lock(&cm->reg_lock);
	अगर (status & CM_CHINT0)
		mask |= CM_CH0_INT_EN;
	अगर (status & CM_CHINT1)
		mask |= CM_CH1_INT_EN;
	snd_cmipci_clear_bit(cm, CM_REG_INT_HLDCLR, mask);
	snd_cmipci_set_bit(cm, CM_REG_INT_HLDCLR, mask);
	spin_unlock(&cm->reg_lock);

	अगर (cm->rmidi && (status & CM_UARTINT))
		snd_mpu401_uart_पूर्णांकerrupt(irq, cm->rmidi->निजी_data);

	अगर (cm->pcm) अणु
		अगर ((status & CM_CHINT0) && cm->channel[0].running)
			snd_pcm_period_elapsed(cm->channel[0].substream);
		अगर ((status & CM_CHINT1) && cm->channel[1].running)
			snd_pcm_period_elapsed(cm->channel[1].substream);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 * h/w infos
 */

/* playback on channel A */
अटल स्थिर काष्ठा snd_pcm_hardware snd_cmipci_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_5512 | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5512,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/* capture on channel B */
अटल स्थिर काष्ठा snd_pcm_hardware snd_cmipci_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_5512 | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5512,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/* playback on channel B - stereo 16bit only? */
अटल स्थिर काष्ठा snd_pcm_hardware snd_cmipci_playback2 =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_5512 | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		5512,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/* spdअगर playback on channel A */
अटल स्थिर काष्ठा snd_pcm_hardware snd_cmipci_playback_spdअगर =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
	.rate_min =		44100,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/* spdअगर playback on channel A (32bit, IEC958 subframes) */
अटल स्थिर काष्ठा snd_pcm_hardware snd_cmipci_playback_iec958_subframe =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE,
	.rates =		SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
	.rate_min =		44100,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/* spdअगर capture on channel B */
अटल स्थिर काष्ठा snd_pcm_hardware snd_cmipci_capture_spdअगर =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =	        SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE,
	.rates =		SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
	.rate_min =		44100,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		2,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rate_स्थिरraपूर्णांकs[] = अणु 5512, 8000, 11025, 16000, 22050,
			32000, 44100, 48000, 88200, 96000, 128000 पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_rates = अणु
		.count = ARRAY_SIZE(rate_स्थिरraपूर्णांकs),
		.list = rate_स्थिरraपूर्णांकs,
		.mask = 0,
पूर्ण;

/*
 * check device खोलो/बंद
 */
अटल पूर्णांक खोलो_device_check(काष्ठा cmipci *cm, पूर्णांक mode, काष्ठा snd_pcm_substream *subs)
अणु
	पूर्णांक ch = mode & CM_OPEN_CH_MASK;

	/* FIXME: a file should रुको until the device becomes मुक्त
	 * when it's खोलोed on blocking mode.  however, since the current
	 * pcm framework करोesn't pass file poपूर्णांकer beक्रमe actually खोलोed,
	 * we can't know whether blocking mode or not in खोलो callback..
	 */
	mutex_lock(&cm->खोलो_mutex);
	अगर (cm->खोलोed[ch]) अणु
		mutex_unlock(&cm->खोलो_mutex);
		वापस -EBUSY;
	पूर्ण
	cm->खोलोed[ch] = mode;
	cm->channel[ch].substream = subs;
	अगर (! (mode & CM_OPEN_DAC)) अणु
		/* disable dual DAC mode */
		cm->channel[ch].is_dac = 0;
		spin_lock_irq(&cm->reg_lock);
		snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_ENDBDAC);
		spin_unlock_irq(&cm->reg_lock);
	पूर्ण
	mutex_unlock(&cm->खोलो_mutex);
	वापस 0;
पूर्ण

अटल व्योम बंद_device_check(काष्ठा cmipci *cm, पूर्णांक mode)
अणु
	पूर्णांक ch = mode & CM_OPEN_CH_MASK;

	mutex_lock(&cm->खोलो_mutex);
	अगर (cm->खोलोed[ch] == mode) अणु
		अगर (cm->channel[ch].substream) अणु
			snd_cmipci_ch_reset(cm, ch);
			cm->channel[ch].running = 0;
			cm->channel[ch].substream = शून्य;
		पूर्ण
		cm->खोलोed[ch] = 0;
		अगर (! cm->channel[ch].is_dac) अणु
			/* enable dual DAC mode again */
			cm->channel[ch].is_dac = 1;
			spin_lock_irq(&cm->reg_lock);
			snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_ENDBDAC);
			spin_unlock_irq(&cm->reg_lock);
		पूर्ण
	पूर्ण
	mutex_unlock(&cm->खोलो_mutex);
पूर्ण

/*
 */

अटल पूर्णांक snd_cmipci_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर ((err = खोलो_device_check(cm, CM_OPEN_PLAYBACK, substream)) < 0)
		वापस err;
	runसमय->hw = snd_cmipci_playback;
	अगर (cm->chip_version == 68) अणु
		runसमय->hw.rates |= SNDRV_PCM_RATE_88200 |
				     SNDRV_PCM_RATE_96000;
		runसमय->hw.rate_max = 96000;
	पूर्ण अन्यथा अगर (cm->chip_version == 55) अणु
		err = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &hw_स्थिरraपूर्णांकs_rates);
		अगर (err < 0)
			वापस err;
		runसमय->hw.rates |= SNDRV_PCM_RATE_KNOT;
		runसमय->hw.rate_max = 128000;
	पूर्ण
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 0x10000);
	cm->dig_pcm_status = cm->dig_status;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर ((err = खोलो_device_check(cm, CM_OPEN_CAPTURE, substream)) < 0)
		वापस err;
	runसमय->hw = snd_cmipci_capture;
	अगर (cm->chip_version == 68) अणु	// 8768 only supports 44k/48k recording
		runसमय->hw.rate_min = 41000;
		runसमय->hw.rates = SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000;
	पूर्ण अन्यथा अगर (cm->chip_version == 55) अणु
		err = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &hw_स्थिरraपूर्णांकs_rates);
		अगर (err < 0)
			वापस err;
		runसमय->hw.rates |= SNDRV_PCM_RATE_KNOT;
		runसमय->hw.rate_max = 128000;
	पूर्ण
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 0x10000);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_playback2_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर ((err = खोलो_device_check(cm, CM_OPEN_PLAYBACK2, substream)) < 0) /* use channel B */
		वापस err;
	runसमय->hw = snd_cmipci_playback2;
	mutex_lock(&cm->खोलो_mutex);
	अगर (! cm->खोलोed[CM_CH_PLAY]) अणु
		अगर (cm->can_multi_ch) अणु
			runसमय->hw.channels_max = cm->max_channels;
			अगर (cm->max_channels == 4)
				snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS, &hw_स्थिरraपूर्णांकs_channels_4);
			अन्यथा अगर (cm->max_channels == 6)
				snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS, &hw_स्थिरraपूर्णांकs_channels_6);
			अन्यथा अगर (cm->max_channels == 8)
				snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS, &hw_स्थिरraपूर्णांकs_channels_8);
		पूर्ण
	पूर्ण
	mutex_unlock(&cm->खोलो_mutex);
	अगर (cm->chip_version == 68) अणु
		runसमय->hw.rates |= SNDRV_PCM_RATE_88200 |
				     SNDRV_PCM_RATE_96000;
		runसमय->hw.rate_max = 96000;
	पूर्ण अन्यथा अगर (cm->chip_version == 55) अणु
		err = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &hw_स्थिरraपूर्णांकs_rates);
		अगर (err < 0)
			वापस err;
		runसमय->hw.rates |= SNDRV_PCM_RATE_KNOT;
		runसमय->hw.rate_max = 128000;
	पूर्ण
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 0x10000);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_playback_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर ((err = खोलो_device_check(cm, CM_OPEN_SPDIF_PLAYBACK, substream)) < 0) /* use channel A */
		वापस err;
	अगर (cm->can_ac3_hw) अणु
		runसमय->hw = snd_cmipci_playback_spdअगर;
		अगर (cm->chip_version >= 37) अणु
			runसमय->hw.क्रमmats |= SNDRV_PCM_FMTBIT_S32_LE;
			snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
		पूर्ण
		अगर (cm->can_96k) अणु
			runसमय->hw.rates |= SNDRV_PCM_RATE_88200 |
					     SNDRV_PCM_RATE_96000;
			runसमय->hw.rate_max = 96000;
		पूर्ण
	पूर्ण अन्यथा अणु
		runसमय->hw = snd_cmipci_playback_iec958_subframe;
	पूर्ण
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 0x40000);
	cm->dig_pcm_status = cm->dig_status;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_capture_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	अगर ((err = खोलो_device_check(cm, CM_OPEN_SPDIF_CAPTURE, substream)) < 0) /* use channel B */
		वापस err;
	runसमय->hw = snd_cmipci_capture_spdअगर;
	अगर (cm->can_96k && !(cm->chip_version == 68)) अणु
		runसमय->hw.rates |= SNDRV_PCM_RATE_88200 |
				     SNDRV_PCM_RATE_96000;
		runसमय->hw.rate_max = 96000;
	पूर्ण
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 0, 0x40000);
	वापस 0;
पूर्ण


/*
 */

अटल पूर्णांक snd_cmipci_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	बंद_device_check(cm, CM_OPEN_PLAYBACK);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	बंद_device_check(cm, CM_OPEN_CAPTURE);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_playback2_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	बंद_device_check(cm, CM_OPEN_PLAYBACK2);
	बंद_device_check(cm, CM_OPEN_PLAYBACK_MULTI);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_playback_spdअगर_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	बंद_device_check(cm, CM_OPEN_SPDIF_PLAYBACK);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_capture_spdअगर_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cmipci *cm = snd_pcm_substream_chip(substream);
	बंद_device_check(cm, CM_OPEN_SPDIF_CAPTURE);
	वापस 0;
पूर्ण


/*
 */

अटल स्थिर काष्ठा snd_pcm_ops snd_cmipci_playback_ops = अणु
	.खोलो =		snd_cmipci_playback_खोलो,
	.बंद =	snd_cmipci_playback_बंद,
	.hw_मुक्त =	snd_cmipci_playback_hw_मुक्त,
	.prepare =	snd_cmipci_playback_prepare,
	.trigger =	snd_cmipci_playback_trigger,
	.poपूर्णांकer =	snd_cmipci_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cmipci_capture_ops = अणु
	.खोलो =		snd_cmipci_capture_खोलो,
	.बंद =	snd_cmipci_capture_बंद,
	.prepare =	snd_cmipci_capture_prepare,
	.trigger =	snd_cmipci_capture_trigger,
	.poपूर्णांकer =	snd_cmipci_capture_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cmipci_playback2_ops = अणु
	.खोलो =		snd_cmipci_playback2_खोलो,
	.बंद =	snd_cmipci_playback2_बंद,
	.hw_params =	snd_cmipci_playback2_hw_params,
	.hw_मुक्त =	snd_cmipci_playback2_hw_मुक्त,
	.prepare =	snd_cmipci_capture_prepare,	/* channel B */
	.trigger =	snd_cmipci_capture_trigger,	/* channel B */
	.poपूर्णांकer =	snd_cmipci_capture_poपूर्णांकer,	/* channel B */
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cmipci_playback_spdअगर_ops = अणु
	.खोलो =		snd_cmipci_playback_spdअगर_खोलो,
	.बंद =	snd_cmipci_playback_spdअगर_बंद,
	.hw_मुक्त =	snd_cmipci_playback_hw_मुक्त,
	.prepare =	snd_cmipci_playback_spdअगर_prepare,	/* set up rate */
	.trigger =	snd_cmipci_playback_trigger,
	.poपूर्णांकer =	snd_cmipci_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cmipci_capture_spdअगर_ops = अणु
	.खोलो =		snd_cmipci_capture_spdअगर_खोलो,
	.बंद =	snd_cmipci_capture_spdअगर_बंद,
	.hw_मुक्त =	snd_cmipci_capture_spdअगर_hw_मुक्त,
	.prepare =	snd_cmipci_capture_spdअगर_prepare,
	.trigger =	snd_cmipci_capture_trigger,
	.poपूर्णांकer =	snd_cmipci_capture_poपूर्णांकer,
पूर्ण;


/*
 */

अटल पूर्णांक snd_cmipci_pcm_new(काष्ठा cmipci *cm, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(cm->card, cm->card->driver, device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_cmipci_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_cmipci_capture_ops);

	pcm->निजी_data = cm;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "C-Media PCI DAC/ADC");
	cm->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &cm->pci->dev, 64*1024, 128*1024);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_pcm2_new(काष्ठा cmipci *cm, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(cm->card, cm->card->driver, device, 1, 0, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_cmipci_playback2_ops);

	pcm->निजी_data = cm;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "C-Media PCI 2nd DAC");
	cm->pcm2 = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &cm->pci->dev, 64*1024, 128*1024);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_pcm_spdअगर_new(काष्ठा cmipci *cm, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(cm->card, cm->card->driver, device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_cmipci_playback_spdअगर_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_cmipci_capture_spdअगर_ops);

	pcm->निजी_data = cm;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "C-Media PCI IEC958");
	cm->pcm_spdअगर = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &cm->pci->dev, 64*1024, 128*1024);

	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_alt_chmaps, cm->max_channels, 0,
				     शून्य);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/*
 * mixer पूर्णांकerface:
 * - CM8338/8738 has a compatible mixer पूर्णांकerface with SB16, but
 *   lack of some elements like tone control, i/o gain and AGC.
 * - Access to native रेजिस्टरs:
 *   - A 3D चयन
 *   - Output mute चयनes
 */

अटल व्योम snd_cmipci_mixer_ग_लिखो(काष्ठा cmipci *s, अचिन्हित अक्षर idx, अचिन्हित अक्षर data)
अणु
	outb(idx, s->iobase + CM_REG_SB16_ADDR);
	outb(data, s->iobase + CM_REG_SB16_DATA);
पूर्ण

अटल अचिन्हित अक्षर snd_cmipci_mixer_पढ़ो(काष्ठा cmipci *s, अचिन्हित अक्षर idx)
अणु
	अचिन्हित अक्षर v;

	outb(idx, s->iobase + CM_REG_SB16_ADDR);
	v = inb(s->iobase + CM_REG_SB16_DATA);
	वापस v;
पूर्ण

/*
 * general mixer element
 */
काष्ठा cmipci_sb_reg अणु
	अचिन्हित पूर्णांक left_reg, right_reg;
	अचिन्हित पूर्णांक left_shअगरt, right_shअगरt;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक invert: 1;
	अचिन्हित पूर्णांक stereo: 1;
पूर्ण;

#घोषणा COMPOSE_SB_REG(lreg,rreg,lshअगरt,rshअगरt,mask,invert,stereo) \
 ((lreg) | ((rreg) << 8) | (lshअगरt << 16) | (rshअगरt << 19) | (mask << 24) | (invert << 22) | (stereo << 23))

#घोषणा CMIPCI_DOUBLE(xname, left_reg, right_reg, left_shअगरt, right_shअगरt, mask, invert, stereo) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_cmipci_info_volume, \
  .get = snd_cmipci_get_volume, .put = snd_cmipci_put_volume, \
  .निजी_value = COMPOSE_SB_REG(left_reg, right_reg, left_shअगरt, right_shअगरt, mask, invert, stereo), \
पूर्ण

#घोषणा CMIPCI_SB_VOL_STEREO(xname,reg,shअगरt,mask) CMIPCI_DOUBLE(xname, reg, reg+1, shअगरt, shअगरt, mask, 0, 1)
#घोषणा CMIPCI_SB_VOL_MONO(xname,reg,shअगरt,mask) CMIPCI_DOUBLE(xname, reg, reg, shअगरt, shअगरt, mask, 0, 0)
#घोषणा CMIPCI_SB_SW_STEREO(xname,lshअगरt,rshअगरt) CMIPCI_DOUBLE(xname, SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, lshअगरt, rshअगरt, 1, 0, 1)
#घोषणा CMIPCI_SB_SW_MONO(xname,shअगरt) CMIPCI_DOUBLE(xname, SB_DSP4_OUTPUT_SW, SB_DSP4_OUTPUT_SW, shअगरt, shअगरt, 1, 0, 0)

अटल व्योम cmipci_sb_reg_decode(काष्ठा cmipci_sb_reg *r, अचिन्हित दीर्घ val)
अणु
	r->left_reg = val & 0xff;
	r->right_reg = (val >> 8) & 0xff;
	r->left_shअगरt = (val >> 16) & 0x07;
	r->right_shअगरt = (val >> 19) & 0x07;
	r->invert = (val >> 22) & 1;
	r->stereo = (val >> 23) & 1;
	r->mask = (val >> 24) & 0xff;
पूर्ण

अटल पूर्णांक snd_cmipci_info_volume(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा cmipci_sb_reg reg;

	cmipci_sb_reg_decode(&reg, kcontrol->निजी_value);
	uinfo->type = reg.mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = reg.stereo + 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = reg.mask;
	वापस 0;
पूर्ण
 
अटल पूर्णांक snd_cmipci_get_volume(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	काष्ठा cmipci_sb_reg reg;
	पूर्णांक val;

	cmipci_sb_reg_decode(&reg, kcontrol->निजी_value);
	spin_lock_irq(&cm->reg_lock);
	val = (snd_cmipci_mixer_पढ़ो(cm, reg.left_reg) >> reg.left_shअगरt) & reg.mask;
	अगर (reg.invert)
		val = reg.mask - val;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	अगर (reg.stereo) अणु
		val = (snd_cmipci_mixer_पढ़ो(cm, reg.right_reg) >> reg.right_shअगरt) & reg.mask;
		अगर (reg.invert)
			val = reg.mask - val;
		ucontrol->value.पूर्णांकeger.value[1] = val;
	पूर्ण
	spin_unlock_irq(&cm->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_put_volume(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	काष्ठा cmipci_sb_reg reg;
	पूर्णांक change;
	पूर्णांक left, right, oleft, oright;

	cmipci_sb_reg_decode(&reg, kcontrol->निजी_value);
	left = ucontrol->value.पूर्णांकeger.value[0] & reg.mask;
	अगर (reg.invert)
		left = reg.mask - left;
	left <<= reg.left_shअगरt;
	अगर (reg.stereo) अणु
		right = ucontrol->value.पूर्णांकeger.value[1] & reg.mask;
		अगर (reg.invert)
			right = reg.mask - right;
		right <<= reg.right_shअगरt;
	पूर्ण अन्यथा
		right = 0;
	spin_lock_irq(&cm->reg_lock);
	oleft = snd_cmipci_mixer_पढ़ो(cm, reg.left_reg);
	left |= oleft & ~(reg.mask << reg.left_shअगरt);
	change = left != oleft;
	अगर (reg.stereo) अणु
		अगर (reg.left_reg != reg.right_reg) अणु
			snd_cmipci_mixer_ग_लिखो(cm, reg.left_reg, left);
			oright = snd_cmipci_mixer_पढ़ो(cm, reg.right_reg);
		पूर्ण अन्यथा
			oright = left;
		right |= oright & ~(reg.mask << reg.right_shअगरt);
		change |= right != oright;
		snd_cmipci_mixer_ग_लिखो(cm, reg.right_reg, right);
	पूर्ण अन्यथा
		snd_cmipci_mixer_ग_लिखो(cm, reg.left_reg, left);
	spin_unlock_irq(&cm->reg_lock);
	वापस change;
पूर्ण

/*
 * input route (left,right) -> (left,right)
 */
#घोषणा CMIPCI_SB_INPUT_SW(xname, left_shअगरt, right_shअगरt) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_cmipci_info_input_sw, \
  .get = snd_cmipci_get_input_sw, .put = snd_cmipci_put_input_sw, \
  .निजी_value = COMPOSE_SB_REG(SB_DSP4_INPUT_LEFT, SB_DSP4_INPUT_RIGHT, left_shअगरt, right_shअगरt, 1, 0, 1), \
पूर्ण

अटल पूर्णांक snd_cmipci_info_input_sw(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 4;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण
 
अटल पूर्णांक snd_cmipci_get_input_sw(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	काष्ठा cmipci_sb_reg reg;
	पूर्णांक val1, val2;

	cmipci_sb_reg_decode(&reg, kcontrol->निजी_value);
	spin_lock_irq(&cm->reg_lock);
	val1 = snd_cmipci_mixer_पढ़ो(cm, reg.left_reg);
	val2 = snd_cmipci_mixer_पढ़ो(cm, reg.right_reg);
	spin_unlock_irq(&cm->reg_lock);
	ucontrol->value.पूर्णांकeger.value[0] = (val1 >> reg.left_shअगरt) & 1;
	ucontrol->value.पूर्णांकeger.value[1] = (val2 >> reg.left_shअगरt) & 1;
	ucontrol->value.पूर्णांकeger.value[2] = (val1 >> reg.right_shअगरt) & 1;
	ucontrol->value.पूर्णांकeger.value[3] = (val2 >> reg.right_shअगरt) & 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_put_input_sw(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	काष्ठा cmipci_sb_reg reg;
	पूर्णांक change;
	पूर्णांक val1, val2, oval1, oval2;

	cmipci_sb_reg_decode(&reg, kcontrol->निजी_value);
	spin_lock_irq(&cm->reg_lock);
	oval1 = snd_cmipci_mixer_पढ़ो(cm, reg.left_reg);
	oval2 = snd_cmipci_mixer_पढ़ो(cm, reg.right_reg);
	val1 = oval1 & ~((1 << reg.left_shअगरt) | (1 << reg.right_shअगरt));
	val2 = oval2 & ~((1 << reg.left_shअगरt) | (1 << reg.right_shअगरt));
	val1 |= (ucontrol->value.पूर्णांकeger.value[0] & 1) << reg.left_shअगरt;
	val2 |= (ucontrol->value.पूर्णांकeger.value[1] & 1) << reg.left_shअगरt;
	val1 |= (ucontrol->value.पूर्णांकeger.value[2] & 1) << reg.right_shअगरt;
	val2 |= (ucontrol->value.पूर्णांकeger.value[3] & 1) << reg.right_shअगरt;
	change = val1 != oval1 || val2 != oval2;
	snd_cmipci_mixer_ग_लिखो(cm, reg.left_reg, val1);
	snd_cmipci_mixer_ग_लिखो(cm, reg.right_reg, val2);
	spin_unlock_irq(&cm->reg_lock);
	वापस change;
पूर्ण

/*
 * native mixer चयनes/volumes
 */

#घोषणा CMIPCI_MIXER_SW_STEREO(xname, reg, lshअगरt, rshअगरt, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_cmipci_info_native_mixer, \
  .get = snd_cmipci_get_native_mixer, .put = snd_cmipci_put_native_mixer, \
  .निजी_value = COMPOSE_SB_REG(reg, reg, lshअगरt, rshअगरt, 1, invert, 1), \
पूर्ण

#घोषणा CMIPCI_MIXER_SW_MONO(xname, reg, shअगरt, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_cmipci_info_native_mixer, \
  .get = snd_cmipci_get_native_mixer, .put = snd_cmipci_put_native_mixer, \
  .निजी_value = COMPOSE_SB_REG(reg, reg, shअगरt, shअगरt, 1, invert, 0), \
पूर्ण

#घोषणा CMIPCI_MIXER_VOL_STEREO(xname, reg, lshअगरt, rshअगरt, mask) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_cmipci_info_native_mixer, \
  .get = snd_cmipci_get_native_mixer, .put = snd_cmipci_put_native_mixer, \
  .निजी_value = COMPOSE_SB_REG(reg, reg, lshअगरt, rshअगरt, mask, 0, 1), \
पूर्ण

#घोषणा CMIPCI_MIXER_VOL_MONO(xname, reg, shअगरt, mask) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
  .info = snd_cmipci_info_native_mixer, \
  .get = snd_cmipci_get_native_mixer, .put = snd_cmipci_put_native_mixer, \
  .निजी_value = COMPOSE_SB_REG(reg, reg, shअगरt, shअगरt, mask, 0, 0), \
पूर्ण

अटल पूर्णांक snd_cmipci_info_native_mixer(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा cmipci_sb_reg reg;

	cmipci_sb_reg_decode(&reg, kcontrol->निजी_value);
	uinfo->type = reg.mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = reg.stereo + 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = reg.mask;
	वापस 0;

पूर्ण

अटल पूर्णांक snd_cmipci_get_native_mixer(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	काष्ठा cmipci_sb_reg reg;
	अचिन्हित अक्षर oreg, val;

	cmipci_sb_reg_decode(&reg, kcontrol->निजी_value);
	spin_lock_irq(&cm->reg_lock);
	oreg = inb(cm->iobase + reg.left_reg);
	val = (oreg >> reg.left_shअगरt) & reg.mask;
	अगर (reg.invert)
		val = reg.mask - val;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	अगर (reg.stereo) अणु
		val = (oreg >> reg.right_shअगरt) & reg.mask;
		अगर (reg.invert)
			val = reg.mask - val;
		ucontrol->value.पूर्णांकeger.value[1] = val;
	पूर्ण
	spin_unlock_irq(&cm->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_put_native_mixer(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	काष्ठा cmipci_sb_reg reg;
	अचिन्हित अक्षर oreg, nreg, val;

	cmipci_sb_reg_decode(&reg, kcontrol->निजी_value);
	spin_lock_irq(&cm->reg_lock);
	oreg = inb(cm->iobase + reg.left_reg);
	val = ucontrol->value.पूर्णांकeger.value[0] & reg.mask;
	अगर (reg.invert)
		val = reg.mask - val;
	nreg = oreg & ~(reg.mask << reg.left_shअगरt);
	nreg |= (val << reg.left_shअगरt);
	अगर (reg.stereo) अणु
		val = ucontrol->value.पूर्णांकeger.value[1] & reg.mask;
		अगर (reg.invert)
			val = reg.mask - val;
		nreg &= ~(reg.mask << reg.right_shअगरt);
		nreg |= (val << reg.right_shअगरt);
	पूर्ण
	outb(nreg, cm->iobase + reg.left_reg);
	spin_unlock_irq(&cm->reg_lock);
	वापस (nreg != oreg);
पूर्ण

/*
 * special हाल - check mixer sensitivity
 */
अटल पूर्णांक snd_cmipci_get_native_mixer_sensitive(काष्ठा snd_kcontrol *kcontrol,
						 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	//काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	वापस snd_cmipci_get_native_mixer(kcontrol, ucontrol);
पूर्ण

अटल पूर्णांक snd_cmipci_put_native_mixer_sensitive(काष्ठा snd_kcontrol *kcontrol,
						 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	अगर (cm->mixer_insensitive) अणु
		/* ignored */
		वापस 0;
	पूर्ण
	वापस snd_cmipci_put_native_mixer(kcontrol, ucontrol);
पूर्ण


अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_mixers[] = अणु
	CMIPCI_SB_VOL_STEREO("Master Playback Volume", SB_DSP4_MASTER_DEV, 3, 31),
	CMIPCI_MIXER_SW_MONO("3D Control - Switch", CM_REG_MIXER1, CM_X3DEN_SHIFT, 0),
	CMIPCI_SB_VOL_STEREO("PCM Playback Volume", SB_DSP4_PCM_DEV, 3, 31),
	//CMIPCI_MIXER_SW_MONO("PCM Playback Switch", CM_REG_MIXER1, CM_WSMUTE_SHIFT, 1),
	अणु /* चयन with sensitivity */
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Switch",
		.info = snd_cmipci_info_native_mixer,
		.get = snd_cmipci_get_native_mixer_sensitive,
		.put = snd_cmipci_put_native_mixer_sensitive,
		.निजी_value = COMPOSE_SB_REG(CM_REG_MIXER1, CM_REG_MIXER1, CM_WSMUTE_SHIFT, CM_WSMUTE_SHIFT, 1, 1, 0),
	पूर्ण,
	CMIPCI_MIXER_SW_STEREO("PCM Capture Switch", CM_REG_MIXER1, CM_WAVEINL_SHIFT, CM_WAVEINR_SHIFT, 0),
	CMIPCI_SB_VOL_STEREO("Synth Playback Volume", SB_DSP4_SYNTH_DEV, 3, 31),
	CMIPCI_MIXER_SW_MONO("Synth Playback Switch", CM_REG_MIXER1, CM_FMMUTE_SHIFT, 1),
	CMIPCI_SB_INPUT_SW("Synth Capture Route", 6, 5),
	CMIPCI_SB_VOL_STEREO("CD Playback Volume", SB_DSP4_CD_DEV, 3, 31),
	CMIPCI_SB_SW_STEREO("CD Playback Switch", 2, 1),
	CMIPCI_SB_INPUT_SW("CD Capture Route", 2, 1),
	CMIPCI_SB_VOL_STEREO("Line Playback Volume", SB_DSP4_LINE_DEV, 3, 31),
	CMIPCI_SB_SW_STEREO("Line Playback Switch", 4, 3),
	CMIPCI_SB_INPUT_SW("Line Capture Route", 4, 3),
	CMIPCI_SB_VOL_MONO("Mic Playback Volume", SB_DSP4_MIC_DEV, 3, 31),
	CMIPCI_SB_SW_MONO("Mic Playback Switch", 0),
	CMIPCI_DOUBLE("Mic Capture Switch", SB_DSP4_INPUT_LEFT, SB_DSP4_INPUT_RIGHT, 0, 0, 1, 0, 0),
	CMIPCI_SB_VOL_MONO("Beep Playback Volume", SB_DSP4_SPEAKER_DEV, 6, 3),
	CMIPCI_MIXER_VOL_STEREO("Aux Playback Volume", CM_REG_AUX_VOL, 4, 0, 15),
	CMIPCI_MIXER_SW_STEREO("Aux Playback Switch", CM_REG_MIXER2, CM_VAUXLM_SHIFT, CM_VAUXRM_SHIFT, 0),
	CMIPCI_MIXER_SW_STEREO("Aux Capture Switch", CM_REG_MIXER2, CM_RAUXLEN_SHIFT, CM_RAUXREN_SHIFT, 0),
	CMIPCI_MIXER_SW_MONO("Mic Boost Playback Switch", CM_REG_MIXER2, CM_MICGAINZ_SHIFT, 1),
	CMIPCI_MIXER_VOL_MONO("Mic Capture Volume", CM_REG_MIXER2, CM_VADMIC_SHIFT, 7),
	CMIPCI_SB_VOL_MONO("Phone Playback Volume", CM_REG_EXTENT_IND, 5, 7),
	CMIPCI_DOUBLE("Phone Playback Switch", CM_REG_EXTENT_IND, CM_REG_EXTENT_IND, 4, 4, 1, 0, 0),
	CMIPCI_DOUBLE("Beep Playback Switch", CM_REG_EXTENT_IND, CM_REG_EXTENT_IND, 3, 3, 1, 0, 0),
	CMIPCI_DOUBLE("Mic Boost Capture Switch", CM_REG_EXTENT_IND, CM_REG_EXTENT_IND, 0, 0, 1, 0, 0),
पूर्ण;

/*
 * other चयनes
 */

काष्ठा cmipci_चयन_args अणु
	पूर्णांक reg;		/* रेजिस्टर index */
	अचिन्हित पूर्णांक mask;	/* mask bits */
	अचिन्हित पूर्णांक mask_on;	/* mask bits to turn on */
	अचिन्हित पूर्णांक is_byte: 1;		/* byte access? */
	अचिन्हित पूर्णांक ac3_sensitive: 1;	/* access क्रमbidden during
					 * non-audio operation?
					 */
पूर्ण;

#घोषणा snd_cmipci_uचयन_info		snd_ctl_boolean_mono_info

अटल पूर्णांक _snd_cmipci_uचयन_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol,
				   काष्ठा cmipci_चयन_args *args)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&cm->reg_lock);
	अगर (args->ac3_sensitive && cm->mixer_insensitive) अणु
		ucontrol->value.पूर्णांकeger.value[0] = 0;
		spin_unlock_irq(&cm->reg_lock);
		वापस 0;
	पूर्ण
	अगर (args->is_byte)
		val = inb(cm->iobase + args->reg);
	अन्यथा
		val = snd_cmipci_पढ़ो(cm, args->reg);
	ucontrol->value.पूर्णांकeger.value[0] = ((val & args->mask) == args->mask_on) ? 1 : 0;
	spin_unlock_irq(&cm->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_uचयन_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci_चयन_args *args;
	args = (काष्ठा cmipci_चयन_args *)kcontrol->निजी_value;
	अगर (snd_BUG_ON(!args))
		वापस -EINVAL;
	वापस _snd_cmipci_uचयन_get(kcontrol, ucontrol, args);
पूर्ण

अटल पूर्णांक _snd_cmipci_uचयन_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol,
				   काष्ठा cmipci_चयन_args *args)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक change;
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&cm->reg_lock);
	अगर (args->ac3_sensitive && cm->mixer_insensitive) अणु
		/* ignored */
		spin_unlock_irq(&cm->reg_lock);
		वापस 0;
	पूर्ण
	अगर (args->is_byte)
		val = inb(cm->iobase + args->reg);
	अन्यथा
		val = snd_cmipci_पढ़ो(cm, args->reg);
	change = (val & args->mask) != (ucontrol->value.पूर्णांकeger.value[0] ? 
			args->mask_on : (args->mask & ~args->mask_on));
	अगर (change) अणु
		val &= ~args->mask;
		अगर (ucontrol->value.पूर्णांकeger.value[0])
			val |= args->mask_on;
		अन्यथा
			val |= (args->mask & ~args->mask_on);
		अगर (args->is_byte)
			outb((अचिन्हित अक्षर)val, cm->iobase + args->reg);
		अन्यथा
			snd_cmipci_ग_लिखो(cm, args->reg, val);
	पूर्ण
	spin_unlock_irq(&cm->reg_lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_cmipci_uचयन_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci_चयन_args *args;
	args = (काष्ठा cmipci_चयन_args *)kcontrol->निजी_value;
	अगर (snd_BUG_ON(!args))
		वापस -EINVAL;
	वापस _snd_cmipci_uचयन_put(kcontrol, ucontrol, args);
पूर्ण

#घोषणा DEFINE_SWITCH_ARG(sname, xreg, xmask, xmask_on, xis_byte, xac3) \
अटल काष्ठा cmipci_चयन_args cmipci_चयन_arg_##sname = अणु \
  .reg = xreg, \
  .mask = xmask, \
  .mask_on = xmask_on, \
  .is_byte = xis_byte, \
  .ac3_sensitive = xac3, \
पूर्ण
	
#घोषणा DEFINE_BIT_SWITCH_ARG(sname, xreg, xmask, xis_byte, xac3) \
	DEFINE_SWITCH_ARG(sname, xreg, xmask, xmask, xis_byte, xac3)

#अगर 0 /* these will be controlled in pcm device */
DEFINE_BIT_SWITCH_ARG(spdअगर_in, CM_REG_FUNCTRL1, CM_SPDF_1, 0, 0);
DEFINE_BIT_SWITCH_ARG(spdअगर_out, CM_REG_FUNCTRL1, CM_SPDF_0, 0, 0);
#पूर्ण_अगर
DEFINE_BIT_SWITCH_ARG(spdअगर_in_sel1, CM_REG_CHFORMAT, CM_SPDIF_SELECT1, 0, 0);
DEFINE_BIT_SWITCH_ARG(spdअगर_in_sel2, CM_REG_MISC_CTRL, CM_SPDIF_SELECT2, 0, 0);
DEFINE_BIT_SWITCH_ARG(spdअगर_enable, CM_REG_LEGACY_CTRL, CM_ENSPDOUT, 0, 0);
DEFINE_BIT_SWITCH_ARG(spकरो2dac, CM_REG_FUNCTRL1, CM_SPDO2DAC, 0, 1);
DEFINE_BIT_SWITCH_ARG(spdi_valid, CM_REG_MISC, CM_SPDVALID, 1, 0);
DEFINE_BIT_SWITCH_ARG(spdअगर_copyright, CM_REG_LEGACY_CTRL, CM_SPDCOPYRHT, 0, 0);
DEFINE_BIT_SWITCH_ARG(spdअगर_dac_out, CM_REG_LEGACY_CTRL, CM_DAC2SPDO, 0, 1);
DEFINE_SWITCH_ARG(spकरो_5v, CM_REG_MISC_CTRL, CM_SPDO5V, 0, 0, 0); /* inverse: 0 = 5V */
// DEFINE_BIT_SWITCH_ARG(spकरो_48k, CM_REG_MISC_CTRL, CM_SPDF_AC97|CM_SPDIF48K, 0, 1);
DEFINE_BIT_SWITCH_ARG(spdअगर_loop, CM_REG_FUNCTRL1, CM_SPDFLOOP, 0, 1);
DEFINE_BIT_SWITCH_ARG(spdi_monitor, CM_REG_MIXER1, CM_CDPLAY, 1, 0);
/* DEFINE_BIT_SWITCH_ARG(spdi_phase, CM_REG_CHFORMAT, CM_SPDIF_INVERSE, 0, 0); */
DEFINE_BIT_SWITCH_ARG(spdi_phase, CM_REG_MISC, CM_SPDIF_INVERSE, 1, 0);
DEFINE_BIT_SWITCH_ARG(spdi_phase2, CM_REG_CHFORMAT, CM_SPDIF_INVERSE2, 0, 0);
#अगर CM_CH_PLAY == 1
DEFINE_SWITCH_ARG(exchange_dac, CM_REG_MISC_CTRL, CM_XCHGDAC, 0, 0, 0); /* reversed */
#अन्यथा
DEFINE_SWITCH_ARG(exchange_dac, CM_REG_MISC_CTRL, CM_XCHGDAC, CM_XCHGDAC, 0, 0);
#पूर्ण_अगर
DEFINE_BIT_SWITCH_ARG(fourch, CM_REG_MISC_CTRL, CM_N4SPK3D, 0, 0);
// DEFINE_BIT_SWITCH_ARG(line_rear, CM_REG_MIXER1, CM_REAR2LIN, 1, 0);
// DEFINE_BIT_SWITCH_ARG(line_bass, CM_REG_LEGACY_CTRL, CM_CENTR2LIN|CM_BASE2LIN, 0, 0);
// DEFINE_BIT_SWITCH_ARG(joystick, CM_REG_FUNCTRL1, CM_JYSTK_EN, 0, 0); /* now module option */
DEFINE_SWITCH_ARG(modem, CM_REG_MISC_CTRL, CM_FLINKON|CM_FLINKOFF, CM_FLINKON, 0, 0);

#घोषणा DEFINE_SWITCH(sname, stype, sarg) \
अणु .name = sname, \
  .अगरace = stype, \
  .info = snd_cmipci_uचयन_info, \
  .get = snd_cmipci_uचयन_get, \
  .put = snd_cmipci_uचयन_put, \
  .निजी_value = (अचिन्हित दीर्घ)&cmipci_चयन_arg_##sarg,\
पूर्ण

#घोषणा DEFINE_CARD_SWITCH(sname, sarg) DEFINE_SWITCH(sname, SNDRV_CTL_ELEM_IFACE_CARD, sarg)
#घोषणा DEFINE_MIXER_SWITCH(sname, sarg) DEFINE_SWITCH(sname, SNDRV_CTL_ELEM_IFACE_MIXER, sarg)


/*
 * callbacks क्रम spdअगर output चयन
 * needs toggle two रेजिस्टरs..
 */
अटल पूर्णांक snd_cmipci_spकरोut_enable_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक changed;
	changed = _snd_cmipci_uचयन_get(kcontrol, ucontrol, &cmipci_चयन_arg_spdअगर_enable);
	changed |= _snd_cmipci_uचयन_get(kcontrol, ucontrol, &cmipci_चयन_arg_spकरो2dac);
	वापस changed;
पूर्ण

अटल पूर्णांक snd_cmipci_spकरोut_enable_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed;
	changed = _snd_cmipci_uचयन_put(kcontrol, ucontrol, &cmipci_चयन_arg_spdअगर_enable);
	changed |= _snd_cmipci_uचयन_put(kcontrol, ucontrol, &cmipci_चयन_arg_spकरो2dac);
	अगर (changed) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
			अगर (chip->spdअगर_playback_avail)
				snd_cmipci_set_bit(chip, CM_REG_FUNCTRL1, CM_PLAYBACK_SPDF);
		पूर्ण अन्यथा अणु
			अगर (chip->spdअगर_playback_avail)
				snd_cmipci_clear_bit(chip, CM_REG_FUNCTRL1, CM_PLAYBACK_SPDF);
		पूर्ण
	पूर्ण
	chip->spdअगर_playback_enabled = ucontrol->value.पूर्णांकeger.value[0];
	वापस changed;
पूर्ण


अटल पूर्णांक snd_cmipci_line_in_mode_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	अटल स्थिर अक्षर *स्थिर texts[3] = अणु
		"Line-In", "Rear Output", "Bass Output"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1,
				 cm->chip_version >= 39 ? 3 : 2, texts);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_line_in_mode(काष्ठा cmipci *cm)
अणु
	अचिन्हित पूर्णांक val;
	अगर (cm->chip_version >= 39) अणु
		val = snd_cmipci_पढ़ो(cm, CM_REG_LEGACY_CTRL);
		अगर (val & (CM_CENTR2LIN | CM_BASE2LIN))
			वापस 2;
	पूर्ण
	val = snd_cmipci_पढ़ो_b(cm, CM_REG_MIXER1);
	अगर (val & CM_REAR2LIN)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_line_in_mode_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&cm->reg_lock);
	ucontrol->value.क्रमागतerated.item[0] = get_line_in_mode(cm);
	spin_unlock_irq(&cm->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_line_in_mode_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;

	spin_lock_irq(&cm->reg_lock);
	अगर (ucontrol->value.क्रमागतerated.item[0] == 2)
		change = snd_cmipci_set_bit(cm, CM_REG_LEGACY_CTRL, CM_CENTR2LIN | CM_BASE2LIN);
	अन्यथा
		change = snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_CENTR2LIN | CM_BASE2LIN);
	अगर (ucontrol->value.क्रमागतerated.item[0] == 1)
		change |= snd_cmipci_set_bit_b(cm, CM_REG_MIXER1, CM_REAR2LIN);
	अन्यथा
		change |= snd_cmipci_clear_bit_b(cm, CM_REG_MIXER1, CM_REAR2LIN);
	spin_unlock_irq(&cm->reg_lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_cmipci_mic_in_mode_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *स्थिर texts[2] = अणु "Mic-In", "Center/LFE Output" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_cmipci_mic_in_mode_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	/* same bit as spdi_phase */
	spin_lock_irq(&cm->reg_lock);
	ucontrol->value.क्रमागतerated.item[0] = 
		(snd_cmipci_पढ़ो_b(cm, CM_REG_MISC) & CM_SPDIF_INVERSE) ? 1 : 0;
	spin_unlock_irq(&cm->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_mic_in_mode_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cmipci *cm = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;

	spin_lock_irq(&cm->reg_lock);
	अगर (ucontrol->value.क्रमागतerated.item[0])
		change = snd_cmipci_set_bit_b(cm, CM_REG_MISC, CM_SPDIF_INVERSE);
	अन्यथा
		change = snd_cmipci_clear_bit_b(cm, CM_REG_MISC, CM_SPDIF_INVERSE);
	spin_unlock_irq(&cm->reg_lock);
	वापस change;
पूर्ण

/* both क्रम CM8338/8738 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_mixer_चयनes[] = अणु
	DEFINE_MIXER_SWITCH("Four Channel Mode", fourch),
	अणु
		.name = "Line-In Mode",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.info = snd_cmipci_line_in_mode_info,
		.get = snd_cmipci_line_in_mode_get,
		.put = snd_cmipci_line_in_mode_put,
	पूर्ण,
पूर्ण;

/* क्रम non-multichannel chips */
अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_nomulti_चयन =
DEFINE_MIXER_SWITCH("Exchange DAC", exchange_dac);

/* only क्रम CM8738 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_8738_mixer_चयनes[] = अणु
#अगर 0 /* controlled in pcm device */
	DEFINE_MIXER_SWITCH("IEC958 In Record", spdअगर_in),
	DEFINE_MIXER_SWITCH("IEC958 Out", spdअगर_out),
	DEFINE_MIXER_SWITCH("IEC958 Out To DAC", spकरो2dac),
#पूर्ण_अगर
	// DEFINE_MIXER_SWITCH("IEC958 Output Switch", spdअगर_enable),
	अणु .name = "IEC958 Output Switch",
	  .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	  .info = snd_cmipci_uचयन_info,
	  .get = snd_cmipci_spकरोut_enable_get,
	  .put = snd_cmipci_spकरोut_enable_put,
	पूर्ण,
	DEFINE_MIXER_SWITCH("IEC958 In Valid", spdi_valid),
	DEFINE_MIXER_SWITCH("IEC958 Copyright", spdअगर_copyright),
	DEFINE_MIXER_SWITCH("IEC958 5V", spकरो_5v),
//	DEFINE_MIXER_SWITCH("IEC958 In/Out 48KHz", spकरो_48k),
	DEFINE_MIXER_SWITCH("IEC958 Loop", spdअगर_loop),
	DEFINE_MIXER_SWITCH("IEC958 In Monitor", spdi_monitor),
पूर्ण;

/* only क्रम model 033/037 */
अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_old_mixer_चयनes[] = अणु
	DEFINE_MIXER_SWITCH("IEC958 Mix Analog", spdअगर_dac_out),
	DEFINE_MIXER_SWITCH("IEC958 In Phase Inverse", spdi_phase),
	DEFINE_MIXER_SWITCH("IEC958 In Select", spdअगर_in_sel1),
पूर्ण;

/* only क्रम model 039 or later */
अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_extra_mixer_चयनes[] = अणु
	DEFINE_MIXER_SWITCH("IEC958 In Select", spdअगर_in_sel2),
	DEFINE_MIXER_SWITCH("IEC958 In Phase Inverse", spdi_phase2),
	अणु
		.name = "Mic-In Mode",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.info = snd_cmipci_mic_in_mode_info,
		.get = snd_cmipci_mic_in_mode_get,
		.put = snd_cmipci_mic_in_mode_put,
	पूर्ण
पूर्ण;

/* card control चयनes */
अटल स्थिर काष्ठा snd_kcontrol_new snd_cmipci_modem_चयन =
DEFINE_CARD_SWITCH("Modem", modem);


अटल पूर्णांक snd_cmipci_mixer_new(काष्ठा cmipci *cm, पूर्णांक pcm_spdअगर_device)
अणु
	काष्ठा snd_card *card;
	स्थिर काष्ठा snd_kcontrol_new *sw;
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!cm || !cm->card))
		वापस -EINVAL;

	card = cm->card;

	म_नकल(card->mixername, "CMedia PCI");

	spin_lock_irq(&cm->reg_lock);
	snd_cmipci_mixer_ग_लिखो(cm, 0x00, 0x00);		/* mixer reset */
	spin_unlock_irq(&cm->reg_lock);

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_cmipci_mixers); idx++) अणु
		अगर (cm->chip_version == 68) अणु	// 8768 has no PCM volume
			अगर (!म_भेद(snd_cmipci_mixers[idx].name,
				"PCM Playback Volume"))
				जारी;
		पूर्ण
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_cmipci_mixers[idx], cm))) < 0)
			वापस err;
	पूर्ण

	/* mixer चयनes */
	sw = snd_cmipci_mixer_चयनes;
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_cmipci_mixer_चयनes); idx++, sw++) अणु
		err = snd_ctl_add(cm->card, snd_ctl_new1(sw, cm));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (! cm->can_multi_ch) अणु
		err = snd_ctl_add(cm->card, snd_ctl_new1(&snd_cmipci_nomulti_चयन, cm));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (cm->device == PCI_DEVICE_ID_CMEDIA_CM8738 ||
	    cm->device == PCI_DEVICE_ID_CMEDIA_CM8738B) अणु
		sw = snd_cmipci_8738_mixer_चयनes;
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_cmipci_8738_mixer_चयनes); idx++, sw++) अणु
			err = snd_ctl_add(cm->card, snd_ctl_new1(sw, cm));
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (cm->can_ac3_hw) अणु
			अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_cmipci_spdअगर_शेष, cm))) < 0)
				वापस err;
			kctl->id.device = pcm_spdअगर_device;
			अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_cmipci_spdअगर_mask, cm))) < 0)
				वापस err;
			kctl->id.device = pcm_spdअगर_device;
			अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_cmipci_spdअगर_stream, cm))) < 0)
				वापस err;
			kctl->id.device = pcm_spdअगर_device;
		पूर्ण
		अगर (cm->chip_version <= 37) अणु
			sw = snd_cmipci_old_mixer_चयनes;
			क्रम (idx = 0; idx < ARRAY_SIZE(snd_cmipci_old_mixer_चयनes); idx++, sw++) अणु
				err = snd_ctl_add(cm->card, snd_ctl_new1(sw, cm));
				अगर (err < 0)
					वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (cm->chip_version >= 39) अणु
		sw = snd_cmipci_extra_mixer_चयनes;
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_cmipci_extra_mixer_चयनes); idx++, sw++) अणु
			err = snd_ctl_add(cm->card, snd_ctl_new1(sw, cm));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	/* card चयनes */
	/*
	 * newer chips करोn't have the रेजिस्टर bits to क्रमce modem link
	 * detection; the bit that was FLINKON now mutes CH1
	 */
	अगर (cm->chip_version < 39) अणु
		err = snd_ctl_add(cm->card,
				  snd_ctl_new1(&snd_cmipci_modem_चयन, cm));
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (idx = 0; idx < CM_SAVED_MIXERS; idx++) अणु
		काष्ठा snd_ctl_elem_id elem_id;
		काष्ठा snd_kcontrol *ctl;
		स_रखो(&elem_id, 0, माप(elem_id));
		elem_id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		म_नकल(elem_id.name, cm_saved_mixer[idx].name);
		ctl = snd_ctl_find_id(cm->card, &elem_id);
		अगर (ctl)
			cm->mixer_res_ctl[idx] = ctl;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * proc पूर्णांकerface
 */

अटल व्योम snd_cmipci_proc_पढ़ो(काष्ठा snd_info_entry *entry, 
				 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा cmipci *cm = entry->निजी_data;
	पूर्णांक i, v;
	
	snd_iम_लिखो(buffer, "%s\n", cm->card->दीर्घname);
	क्रम (i = 0; i < 0x94; i++) अणु
		अगर (i == 0x28)
			i = 0x90;
		v = inb(cm->iobase + i);
		अगर (i % 4 == 0)
			snd_iम_लिखो(buffer, "\n%02x:", i);
		snd_iम_लिखो(buffer, " %02x", v);
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम snd_cmipci_proc_init(काष्ठा cmipci *cm)
अणु
	snd_card_ro_proc_new(cm->card, "cmipci", cm, snd_cmipci_proc_पढ़ो);
पूर्ण

अटल स्थिर काष्ठा pci_device_id snd_cmipci_ids[] = अणु
	अणुPCI_VDEVICE(CMEDIA, PCI_DEVICE_ID_CMEDIA_CM8338A), 0पूर्ण,
	अणुPCI_VDEVICE(CMEDIA, PCI_DEVICE_ID_CMEDIA_CM8338B), 0पूर्ण,
	अणुPCI_VDEVICE(CMEDIA, PCI_DEVICE_ID_CMEDIA_CM8738), 0पूर्ण,
	अणुPCI_VDEVICE(CMEDIA, PCI_DEVICE_ID_CMEDIA_CM8738B), 0पूर्ण,
	अणुPCI_VDEVICE(AL, PCI_DEVICE_ID_CMEDIA_CM8738), 0पूर्ण,
	अणु0,पूर्ण,
पूर्ण;


/*
 * check chip version and capabilities
 * driver name is modअगरied according to the chip model
 */
अटल व्योम query_chip(काष्ठा cmipci *cm)
अणु
	अचिन्हित पूर्णांक detect;

	/* check reg 0Ch, bit 24-31 */
	detect = snd_cmipci_पढ़ो(cm, CM_REG_INT_HLDCLR) & CM_CHIP_MASK2;
	अगर (! detect) अणु
		/* check reg 08h, bit 24-28 */
		detect = snd_cmipci_पढ़ो(cm, CM_REG_CHFORMAT) & CM_CHIP_MASK1;
		चयन (detect) अणु
		हाल 0:
			cm->chip_version = 33;
			अगर (cm->करो_soft_ac3)
				cm->can_ac3_sw = 1;
			अन्यथा
				cm->can_ac3_hw = 1;
			अवरोध;
		हाल CM_CHIP_037:
			cm->chip_version = 37;
			cm->can_ac3_hw = 1;
			अवरोध;
		शेष:
			cm->chip_version = 39;
			cm->can_ac3_hw = 1;
			अवरोध;
		पूर्ण
		cm->max_channels = 2;
	पूर्ण अन्यथा अणु
		अगर (detect & CM_CHIP_039) अणु
			cm->chip_version = 39;
			अगर (detect & CM_CHIP_039_6CH) /* 4 or 6 channels */
				cm->max_channels = 6;
			अन्यथा
				cm->max_channels = 4;
		पूर्ण अन्यथा अगर (detect & CM_CHIP_8768) अणु
			cm->chip_version = 68;
			cm->max_channels = 8;
			cm->can_96k = 1;
		पूर्ण अन्यथा अणु
			cm->chip_version = 55;
			cm->max_channels = 6;
			cm->can_96k = 1;
		पूर्ण
		cm->can_ac3_hw = 1;
		cm->can_multi_ch = 1;
	पूर्ण
पूर्ण

#अगर_घोषित SUPPORT_JOYSTICK
अटल पूर्णांक snd_cmipci_create_gameport(काष्ठा cmipci *cm, पूर्णांक dev)
अणु
	अटल स्थिर पूर्णांक ports[] = अणु 0x201, 0x200, 0 पूर्ण; /* FIXME: majority is 0x201? */
	काष्ठा gameport *gp;
	काष्ठा resource *r = शून्य;
	पूर्णांक i, io_port = 0;

	अगर (joystick_port[dev] == 0)
		वापस -ENODEV;

	अगर (joystick_port[dev] == 1) अणु /* स्वतः-detect */
		क्रम (i = 0; ports[i]; i++) अणु
			io_port = ports[i];
			r = request_region(io_port, 1, "CMIPCI gameport");
			अगर (r)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		io_port = joystick_port[dev];
		r = request_region(io_port, 1, "CMIPCI gameport");
	पूर्ण

	अगर (!r) अणु
		dev_warn(cm->card->dev, "cannot reserve joystick ports\n");
		वापस -EBUSY;
	पूर्ण

	cm->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(cm->card->dev, "cannot allocate memory for gameport\n");
		release_and_मुक्त_resource(r);
		वापस -ENOMEM;
	पूर्ण
	gameport_set_name(gp, "C-Media Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(cm->pci));
	gameport_set_dev_parent(gp, &cm->pci->dev);
	gp->io = io_port;
	gameport_set_port_data(gp, r);

	snd_cmipci_set_bit(cm, CM_REG_FUNCTRL1, CM_JYSTK_EN);

	gameport_रेजिस्टर_port(cm->gameport);

	वापस 0;
पूर्ण

अटल व्योम snd_cmipci_मुक्त_gameport(काष्ठा cmipci *cm)
अणु
	अगर (cm->gameport) अणु
		काष्ठा resource *r = gameport_get_port_data(cm->gameport);

		gameport_unरेजिस्टर_port(cm->gameport);
		cm->gameport = शून्य;

		snd_cmipci_clear_bit(cm, CM_REG_FUNCTRL1, CM_JYSTK_EN);
		release_and_मुक्त_resource(r);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_cmipci_create_gameport(काष्ठा cmipci *cm, पूर्णांक dev) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम snd_cmipci_मुक्त_gameport(काष्ठा cmipci *cm) अणु पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_cmipci_मुक्त(काष्ठा cmipci *cm)
अणु
	अगर (cm->irq >= 0) अणु
		snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_FM_EN);
		snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_ENSPDOUT);
		snd_cmipci_ग_लिखो(cm, CM_REG_INT_HLDCLR, 0);  /* disable पूर्णांकs */
		snd_cmipci_ch_reset(cm, CM_CH_PLAY);
		snd_cmipci_ch_reset(cm, CM_CH_CAPT);
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, 0); /* disable channels */
		snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL1, 0);

		/* reset mixer */
		snd_cmipci_mixer_ग_लिखो(cm, 0, 0);

		मुक्त_irq(cm->irq, cm);
	पूर्ण

	snd_cmipci_मुक्त_gameport(cm);
	pci_release_regions(cm->pci);
	pci_disable_device(cm->pci);
	kमुक्त(cm);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा cmipci *cm = device->device_data;
	वापस snd_cmipci_मुक्त(cm);
पूर्ण

अटल पूर्णांक snd_cmipci_create_fm(काष्ठा cmipci *cm, दीर्घ fm_port)
अणु
	दीर्घ iosynth;
	अचिन्हित पूर्णांक val;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;

	अगर (!fm_port)
		जाओ disable_fm;

	अगर (cm->chip_version >= 39) अणु
		/* first try FM regs in PCI port range */
		iosynth = cm->iobase + CM_REG_FM_PCI;
		err = snd_opl3_create(cm->card, iosynth, iosynth + 2,
				      OPL3_HW_OPL3, 1, &opl3);
	पूर्ण अन्यथा अणु
		err = -EIO;
	पूर्ण
	अगर (err < 0) अणु
		/* then try legacy ports */
		val = snd_cmipci_पढ़ो(cm, CM_REG_LEGACY_CTRL) & ~CM_FMSEL_MASK;
		iosynth = fm_port;
		चयन (iosynth) अणु
		हाल 0x3E8: val |= CM_FMSEL_3E8; अवरोध;
		हाल 0x3E0: val |= CM_FMSEL_3E0; अवरोध;
		हाल 0x3C8: val |= CM_FMSEL_3C8; अवरोध;
		हाल 0x388: val |= CM_FMSEL_388; अवरोध;
		शेष:
			जाओ disable_fm;
		पूर्ण
		snd_cmipci_ग_लिखो(cm, CM_REG_LEGACY_CTRL, val);
		/* enable FM */
		snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_FM_EN);

		अगर (snd_opl3_create(cm->card, iosynth, iosynth + 2,
				    OPL3_HW_OPL3, 0, &opl3) < 0) अणु
			dev_err(cm->card->dev,
				"no OPL device at %#lx, skipping...\n",
				iosynth);
			जाओ disable_fm;
		पूर्ण
	पूर्ण
	अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0) अणु
		dev_err(cm->card->dev, "cannot create OPL3 hwdep\n");
		वापस err;
	पूर्ण
	वापस 0;

 disable_fm:
	snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_FMSEL_MASK);
	snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_FM_EN);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
			     पूर्णांक dev, काष्ठा cmipci **rcmipci)
अणु
	काष्ठा cmipci *cm;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_cmipci_dev_मुक्त,
	पूर्ण;
	अचिन्हित पूर्णांक val;
	दीर्घ iomidi = 0;
	पूर्णांक पूर्णांकegrated_midi = 0;
	अक्षर modelstr[16];
	पूर्णांक pcm_index, pcm_spdअगर_index;
	अटल स्थिर काष्ठा pci_device_id पूर्णांकel_82437vx[] = अणु
		अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82437VX) पूर्ण,
		अणु पूर्ण,
	पूर्ण;

	*rcmipci = शून्य;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	cm = kzalloc(माप(*cm), GFP_KERNEL);
	अगर (cm == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&cm->reg_lock);
	mutex_init(&cm->खोलो_mutex);
	cm->device = pci->device;
	cm->card = card;
	cm->pci = pci;
	cm->irq = -1;
	cm->channel[0].ch = 0;
	cm->channel[1].ch = 1;
	cm->channel[0].is_dac = cm->channel[1].is_dac = 1; /* dual DAC mode */

	अगर ((err = pci_request_regions(pci, card->driver)) < 0) अणु
		kमुक्त(cm);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	cm->iobase = pci_resource_start(pci, 0);

	अगर (request_irq(pci->irq, snd_cmipci_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, cm)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_cmipci_मुक्त(cm);
		वापस -EBUSY;
	पूर्ण
	cm->irq = pci->irq;
	card->sync_irq = cm->irq;

	pci_set_master(cm->pci);

	/*
	 * check chip version, max channels and capabilities
	 */

	cm->chip_version = 0;
	cm->max_channels = 2;
	cm->करो_soft_ac3 = soft_ac3[dev];

	अगर (pci->device != PCI_DEVICE_ID_CMEDIA_CM8338A &&
	    pci->device != PCI_DEVICE_ID_CMEDIA_CM8338B)
		query_chip(cm);
	/* added -MCx suffix क्रम chip supporting multi-channels */
	अगर (cm->can_multi_ch)
		प्र_लिखो(cm->card->driver + म_माप(cm->card->driver),
			"-MC%d", cm->max_channels);
	अन्यथा अगर (cm->can_ac3_sw)
		म_नकल(cm->card->driver + म_माप(cm->card->driver), "-SWIEC");

	cm->dig_status = SNDRV_PCM_DEFAULT_CON_SPDIF;
	cm->dig_pcm_status = SNDRV_PCM_DEFAULT_CON_SPDIF;

#अगर CM_CH_PLAY == 1
	cm->ctrl = CM_CHADC0;	/* शेष FUNCNTRL0 */
#अन्यथा
	cm->ctrl = CM_CHADC1;	/* शेष FUNCNTRL0 */
#पूर्ण_अगर

	/* initialize codec रेजिस्टरs */
	snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_RESET);
	snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_RESET);
	snd_cmipci_ग_लिखो(cm, CM_REG_INT_HLDCLR, 0);	/* disable पूर्णांकs */
	snd_cmipci_ch_reset(cm, CM_CH_PLAY);
	snd_cmipci_ch_reset(cm, CM_CH_CAPT);
	snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL0, 0);	/* disable channels */
	snd_cmipci_ग_लिखो(cm, CM_REG_FUNCTRL1, 0);

	snd_cmipci_ग_लिखो(cm, CM_REG_CHFORMAT, 0);
	snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_ENDBDAC|CM_N4SPK3D);
#अगर CM_CH_PLAY == 1
	snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_XCHGDAC);
#अन्यथा
	snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_XCHGDAC);
#पूर्ण_अगर
	अगर (cm->chip_version) अणु
		snd_cmipci_ग_लिखो_b(cm, CM_REG_EXT_MISC, 0x20); /* magic */
		snd_cmipci_ग_लिखो_b(cm, CM_REG_EXT_MISC + 1, 0x09); /* more magic */
	पूर्ण
	/* Set Bus Master Request */
	snd_cmipci_set_bit(cm, CM_REG_FUNCTRL1, CM_BREQ);

	/* Assume TX and compatible chip set (Autodetection required क्रम VX chip sets) */
	चयन (pci->device) अणु
	हाल PCI_DEVICE_ID_CMEDIA_CM8738:
	हाल PCI_DEVICE_ID_CMEDIA_CM8738B:
		अगर (!pci_dev_present(पूर्णांकel_82437vx)) 
			snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_TXVX);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (cm->chip_version < 68) अणु
		val = pci->device < 0x110 ? 8338 : 8738;
	पूर्ण अन्यथा अणु
		चयन (snd_cmipci_पढ़ो_b(cm, CM_REG_INT_HLDCLR + 3) & 0x03) अणु
		हाल 0:
			val = 8769;
			अवरोध;
		हाल 2:
			val = 8762;
			अवरोध;
		शेष:
			चयन ((pci->subप्रणाली_venकरोr << 16) |
				pci->subप्रणाली_device) अणु
			हाल 0x13f69761:
			हाल 0x584d3741:
			हाल 0x584d3751:
			हाल 0x584d3761:
			हाल 0x584d3771:
			हाल 0x72848384:
				val = 8770;
				अवरोध;
			शेष:
				val = 8768;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	प्र_लिखो(card->लघुname, "C-Media CMI%d", val);
	अगर (cm->chip_version < 68)
		प्र_लिखो(modelstr, " (model %d)", cm->chip_version);
	अन्यथा
		modelstr[0] = '\0';
	प्र_लिखो(card->दीर्घname, "%s%s at %#lx, irq %i",
		card->लघुname, modelstr, cm->iobase, cm->irq);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, cm, &ops)) < 0) अणु
		snd_cmipci_मुक्त(cm);
		वापस err;
	पूर्ण

	अगर (cm->chip_version >= 39) अणु
		val = snd_cmipci_पढ़ो_b(cm, CM_REG_MPU_PCI + 1);
		अगर (val != 0x00 && val != 0xff) अणु
			अगर (mpu_port[dev])
				iomidi = cm->iobase + CM_REG_MPU_PCI;
			पूर्णांकegrated_midi = 1;
		पूर्ण
	पूर्ण
	अगर (!पूर्णांकegrated_midi) अणु
		val = 0;
		iomidi = mpu_port[dev];
		चयन (iomidi) अणु
		हाल 0x320: val = CM_VMPU_320; अवरोध;
		हाल 0x310: val = CM_VMPU_310; अवरोध;
		हाल 0x300: val = CM_VMPU_300; अवरोध;
		हाल 0x330: val = CM_VMPU_330; अवरोध;
		शेष:
			    iomidi = 0; अवरोध;
		पूर्ण
		अगर (iomidi > 0) अणु
			snd_cmipci_ग_लिखो(cm, CM_REG_LEGACY_CTRL, val);
			/* enable UART */
			snd_cmipci_set_bit(cm, CM_REG_FUNCTRL1, CM_UART_EN);
			अगर (inb(iomidi + 1) == 0xff) अणु
				dev_err(cm->card->dev,
					"cannot enable MPU-401 port at %#lx\n",
					iomidi);
				snd_cmipci_clear_bit(cm, CM_REG_FUNCTRL1,
						     CM_UART_EN);
				iomidi = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (cm->chip_version < 68) अणु
		err = snd_cmipci_create_fm(cm, fm_port[dev]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* reset mixer */
	snd_cmipci_mixer_ग_लिखो(cm, 0, 0);

	snd_cmipci_proc_init(cm);

	/* create pcm devices */
	pcm_index = pcm_spdअगर_index = 0;
	अगर ((err = snd_cmipci_pcm_new(cm, pcm_index)) < 0)
		वापस err;
	pcm_index++;
	अगर ((err = snd_cmipci_pcm2_new(cm, pcm_index)) < 0)
		वापस err;
	pcm_index++;
	अगर (cm->can_ac3_hw || cm->can_ac3_sw) अणु
		pcm_spdअगर_index = pcm_index;
		अगर ((err = snd_cmipci_pcm_spdअगर_new(cm, pcm_index)) < 0)
			वापस err;
	पूर्ण

	/* create mixer पूर्णांकerface & चयनes */
	अगर ((err = snd_cmipci_mixer_new(cm, pcm_spdअगर_index)) < 0)
		वापस err;

	अगर (iomidi > 0) अणु
		अगर ((err = snd_mpu401_uart_new(card, 0, MPU401_HW_CMIPCI,
					       iomidi,
					       (पूर्णांकegrated_midi ?
						MPU401_INFO_INTEGRATED : 0) |
					       MPU401_INFO_IRQ_HOOK,
					       -1, &cm->rmidi)) < 0) अणु
			dev_err(cm->card->dev,
				"no UART401 device at 0x%lx\n", iomidi);
		पूर्ण
	पूर्ण

#अगर_घोषित USE_VAR48KRATE
	क्रम (val = 0; val < ARRAY_SIZE(rates); val++)
		snd_cmipci_set_pll(cm, rates[val], val);

	/*
	 * (Re-)Enable बाह्यal चयन spकरो_48k
	 */
	snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_SPDIF48K|CM_SPDF_AC97);
#पूर्ण_अगर /* USE_VAR48KRATE */

	अगर (snd_cmipci_create_gameport(cm, dev) < 0)
		snd_cmipci_clear_bit(cm, CM_REG_FUNCTRL1, CM_JYSTK_EN);

	*rcmipci = cm;
	वापस 0;
पूर्ण

/*
 */

MODULE_DEVICE_TABLE(pci, snd_cmipci_ids);

अटल पूर्णांक snd_cmipci_probe(काष्ठा pci_dev *pci,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा cmipci *cm;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (! enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;
	
	चयन (pci->device) अणु
	हाल PCI_DEVICE_ID_CMEDIA_CM8738:
	हाल PCI_DEVICE_ID_CMEDIA_CM8738B:
		म_नकल(card->driver, "CMI8738");
		अवरोध;
	हाल PCI_DEVICE_ID_CMEDIA_CM8338A:
	हाल PCI_DEVICE_ID_CMEDIA_CM8338B:
		म_नकल(card->driver, "CMI8338");
		अवरोध;
	शेष:
		म_नकल(card->driver, "CMIPCI");
		अवरोध;
	पूर्ण

	err = snd_cmipci_create(card, pci, dev, &cm);
	अगर (err < 0)
		जाओ मुक्त_card;

	card->निजी_data = cm;

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ मुक्त_card;

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;

मुक्त_card:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_cmipci_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण


#अगर_घोषित CONFIG_PM_SLEEP
/*
 * घातer management
 */
अटल स्थिर अचिन्हित अक्षर saved_regs[] = अणु
	CM_REG_FUNCTRL1, CM_REG_CHFORMAT, CM_REG_LEGACY_CTRL, CM_REG_MISC_CTRL,
	CM_REG_MIXER0, CM_REG_MIXER1, CM_REG_MIXER2, CM_REG_MIXER3, CM_REG_PLL,
	CM_REG_CH0_FRAME1, CM_REG_CH0_FRAME2,
	CM_REG_CH1_FRAME1, CM_REG_CH1_FRAME2, CM_REG_EXT_MISC,
	CM_REG_INT_STATUS, CM_REG_INT_HLDCLR, CM_REG_FUNCTRL0,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर saved_mixers[] = अणु
	SB_DSP4_MASTER_DEV, SB_DSP4_MASTER_DEV + 1,
	SB_DSP4_PCM_DEV, SB_DSP4_PCM_DEV + 1,
	SB_DSP4_SYNTH_DEV, SB_DSP4_SYNTH_DEV + 1,
	SB_DSP4_CD_DEV, SB_DSP4_CD_DEV + 1,
	SB_DSP4_LINE_DEV, SB_DSP4_LINE_DEV + 1,
	SB_DSP4_MIC_DEV, SB_DSP4_SPEAKER_DEV,
	CM_REG_EXTENT_IND, SB_DSP4_OUTPUT_SW,
	SB_DSP4_INPUT_LEFT, SB_DSP4_INPUT_RIGHT,
पूर्ण;

अटल पूर्णांक snd_cmipci_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा cmipci *cm = card->निजी_data;
	पूर्णांक i;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	
	/* save रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(saved_regs); i++)
		cm->saved_regs[i] = snd_cmipci_पढ़ो(cm, saved_regs[i]);
	क्रम (i = 0; i < ARRAY_SIZE(saved_mixers); i++)
		cm->saved_mixers[i] = snd_cmipci_mixer_पढ़ो(cm, saved_mixers[i]);

	/* disable पूर्णांकs */
	snd_cmipci_ग_लिखो(cm, CM_REG_INT_HLDCLR, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cmipci_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा cmipci *cm = card->निजी_data;
	पूर्णांक i;

	/* reset / initialize to a sane state */
	snd_cmipci_ग_लिखो(cm, CM_REG_INT_HLDCLR, 0);
	snd_cmipci_ch_reset(cm, CM_CH_PLAY);
	snd_cmipci_ch_reset(cm, CM_CH_CAPT);
	snd_cmipci_mixer_ग_लिखो(cm, 0, 0);

	/* restore रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(saved_regs); i++)
		snd_cmipci_ग_लिखो(cm, saved_regs[i], cm->saved_regs[i]);
	क्रम (i = 0; i < ARRAY_SIZE(saved_mixers); i++)
		snd_cmipci_mixer_ग_लिखो(cm, saved_mixers[i], cm->saved_mixers[i]);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_cmipci_pm, snd_cmipci_suspend, snd_cmipci_resume);
#घोषणा SND_CMIPCI_PM_OPS	&snd_cmipci_pm
#अन्यथा
#घोषणा SND_CMIPCI_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver cmipci_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_cmipci_ids,
	.probe = snd_cmipci_probe,
	.हटाओ = snd_cmipci_हटाओ,
	.driver = अणु
		.pm = SND_CMIPCI_PM_OPS,
	पूर्ण,
पूर्ण;
	
module_pci_driver(cmipci_driver);
