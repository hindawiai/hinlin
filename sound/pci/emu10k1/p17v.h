<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) by James Courtier-Dutton <James@superbug.demon.co.uk>
 *  Driver p17v chips
 *  Version: 0.01
 */

/******************************************************************************/
/* Audigy2Value Tina (P17V) poपूर्णांकer-offset रेजिस्टर set,
 * accessed through the PTR20 and DATA24 रेजिस्टरs  */
/******************************************************************************/

/* 00 - 07: Not used */
#घोषणा P17V_PLAYBACK_FIFO_PTR	0x08	/* Current playback fअगरo poपूर्णांकer
					 * and number of sound samples in cache.
					 */  
/* 09 - 12: Not used */
#घोषणा P17V_CAPTURE_FIFO_PTR	0x13	/* Current capture fअगरo poपूर्णांकer
					 * and number of sound samples in cache.
					 */  
/* 14 - 17: Not used */
#घोषणा P17V_PB_CHN_SEL		0x18	/* P17v playback channel select */
#घोषणा P17V_SE_SLOT_SEL_L	0x19	/* Sound Engine slot select low */
#घोषणा P17V_SE_SLOT_SEL_H	0x1a	/* Sound Engine slot select high */
/* 1b - 1f: Not used */
/* 20 - 2f: Not used */
/* 30 - 3b: Not used */
#घोषणा P17V_SPI		0x3c	/* SPI पूर्णांकerface रेजिस्टर */
#घोषणा P17V_I2C_ADDR		0x3d	/* I2C Address */
#घोषणा P17V_I2C_0		0x3e	/* I2C Data */
#घोषणा P17V_I2C_1		0x3f	/* I2C Data */
/* I2C values */
#घोषणा I2C_A_ADC_ADD_MASK	0x000000fe	/*The address is a 7 bit address */
#घोषणा I2C_A_ADC_RW_MASK	0x00000001	/*bit mask क्रम R/W */
#घोषणा I2C_A_ADC_TRANS_MASK	0x00000010  	/*Bit mask क्रम I2c address DAC value  */
#घोषणा I2C_A_ADC_ABORT_MASK	0x00000020	/*Bit mask क्रम I2C transaction पात flag */
#घोषणा I2C_A_ADC_LAST_MASK	0x00000040	/*Bit mask क्रम Last word transaction */
#घोषणा I2C_A_ADC_BYTE_MASK	0x00000080	/*Bit mask क्रम Byte Mode */

#घोषणा I2C_A_ADC_ADD		0x00000034	/*This is the Device address क्रम ADC  */
#घोषणा I2C_A_ADC_READ		0x00000001	/*To perक्रमm a पढ़ो operation */
#घोषणा I2C_A_ADC_START		0x00000100	/*Start I2C transaction */
#घोषणा I2C_A_ADC_ABORT		0x00000200	/*I2C transaction पात */
#घोषणा I2C_A_ADC_LAST		0x00000400	/*I2C last transaction */
#घोषणा I2C_A_ADC_BYTE		0x00000800	/*I2C one byte mode */

#घोषणा I2C_D_ADC_REG_MASK	0xfe000000  	/*ADC address रेजिस्टर */ 
#घोषणा I2C_D_ADC_DAT_MASK	0x01ff0000  	/*ADC data रेजिस्टर */

#घोषणा ADC_TIMEOUT		0x00000007	/*ADC Timeout Clock Disable */
#घोषणा ADC_IFC_CTRL		0x0000000b	/*ADC Interface Control */
#घोषणा ADC_MASTER		0x0000000c	/*ADC Master Mode Control */
#घोषणा ADC_POWER		0x0000000d	/*ADC PowerDown Control */
#घोषणा ADC_ATTEN_ADCL		0x0000000e	/*ADC Attenuation ADCL */
#घोषणा ADC_ATTEN_ADCR		0x0000000f	/*ADC Attenuation ADCR */
#घोषणा ADC_ALC_CTRL1		0x00000010	/*ADC ALC Control 1 */
#घोषणा ADC_ALC_CTRL2		0x00000011	/*ADC ALC Control 2 */
#घोषणा ADC_ALC_CTRL3		0x00000012	/*ADC ALC Control 3 */
#घोषणा ADC_NOISE_CTRL		0x00000013	/*ADC Noise Gate Control */
#घोषणा ADC_LIMIT_CTRL		0x00000014	/*ADC Limiter Control */
#घोषणा ADC_MUX			0x00000015  	/*ADC Mux offset */
#अगर 0
/* FIXME: Not tested yet. */
#घोषणा ADC_GAIN_MASK		0x000000ff	//Mask क्रम ADC Gain
#घोषणा ADC_ZERODB		0x000000cf	//Value to set ADC to 0dB
#घोषणा ADC_MUTE_MASK		0x000000c0	//Mask क्रम ADC mute
#घोषणा ADC_MUTE		0x000000c0	//Value to mute ADC
#घोषणा ADC_OSR			0x00000008	//Mask क्रम ADC oversample rate select
#घोषणा ADC_TIMEOUT_DISABLE	0x00000008	//Value and mask to disable Timeout घड़ी
#घोषणा ADC_HPF_DISABLE		0x00000100	//Value and mask to disable High pass filter
#घोषणा ADC_TRANWIN_MASK	0x00000070	//Mask क्रम Length of Transient Winकरोw
#पूर्ण_अगर

#घोषणा ADC_MUX_MASK		0x0000000f	//Mask क्रम ADC Mux
#घोषणा ADC_MUX_0		0x00000001	//Value to select Unknown at ADC Mux (Not used)
#घोषणा ADC_MUX_1		0x00000002	//Value to select Unknown at ADC Mux (Not used)
#घोषणा ADC_MUX_2		0x00000004	//Value to select Mic at ADC Mux
#घोषणा ADC_MUX_3		0x00000008	//Value to select Line-In at ADC Mux

#घोषणा P17V_START_AUDIO	0x40	/* Start Audio bit */
/* 41 - 47: Reserved */
#घोषणा P17V_START_CAPTURE	0x48	/* Start Capture bit */
#घोषणा P17V_CAPTURE_FIFO_BASE	0x49	/* Record FIFO base address */
#घोषणा P17V_CAPTURE_FIFO_SIZE	0x4a	/* Record FIFO buffer size */
#घोषणा P17V_CAPTURE_FIFO_INDEX	0x4b	/* Record FIFO capture index */
#घोषणा P17V_CAPTURE_VOL_H	0x4c	/* P17v capture volume control */
#घोषणा P17V_CAPTURE_VOL_L	0x4d	/* P17v capture volume control */
/* 4e - 4f: Not used */
/* 50 - 5f: Not used */
#घोषणा P17V_SRCSel		0x60	/* SRC48 and SRCMulti sample rate select
					 * and output select
					 */
#घोषणा P17V_MIXER_AC97_10K1_VOL_L	0x61	/* 10K to Mixer_AC97 input volume control */
#घोषणा P17V_MIXER_AC97_10K1_VOL_H	0x62	/* 10K to Mixer_AC97 input volume control */
#घोषणा P17V_MIXER_AC97_P17V_VOL_L	0x63	/* P17V to Mixer_AC97 input volume control */
#घोषणा P17V_MIXER_AC97_P17V_VOL_H	0x64	/* P17V to Mixer_AC97 input volume control */
#घोषणा P17V_MIXER_AC97_SRP_REC_VOL_L	0x65	/* SRP Record to Mixer_AC97 input volume control */
#घोषणा P17V_MIXER_AC97_SRP_REC_VOL_H	0x66	/* SRP Record to Mixer_AC97 input volume control */
/* 67 - 68: Reserved */
#घोषणा P17V_MIXER_Spdअगर_10K1_VOL_L	0x69	/* 10K to Mixer_Spdअगर input volume control */
#घोषणा P17V_MIXER_Spdअगर_10K1_VOL_H	0x6A	/* 10K to Mixer_Spdअगर input volume control */
#घोषणा P17V_MIXER_Spdअगर_P17V_VOL_L	0x6B	/* P17V to Mixer_Spdअगर input volume control */
#घोषणा P17V_MIXER_Spdअगर_P17V_VOL_H	0x6C	/* P17V to Mixer_Spdअगर input volume control */
#घोषणा P17V_MIXER_Spdअगर_SRP_REC_VOL_L	0x6D	/* SRP Record to Mixer_Spdअगर input volume control */
#घोषणा P17V_MIXER_Spdअगर_SRP_REC_VOL_H	0x6E	/* SRP Record to Mixer_Spdअगर input volume control */
/* 6f - 70: Reserved */
#घोषणा P17V_MIXER_I2S_10K1_VOL_L	0x71	/* 10K to Mixer_I2S input volume control */
#घोषणा P17V_MIXER_I2S_10K1_VOL_H	0x72	/* 10K to Mixer_I2S input volume control */
#घोषणा P17V_MIXER_I2S_P17V_VOL_L	0x73	/* P17V to Mixer_I2S input volume control */
#घोषणा P17V_MIXER_I2S_P17V_VOL_H	0x74	/* P17V to Mixer_I2S input volume control */
#घोषणा P17V_MIXER_I2S_SRP_REC_VOL_L	0x75	/* SRP Record to Mixer_I2S input volume control */
#घोषणा P17V_MIXER_I2S_SRP_REC_VOL_H	0x76	/* SRP Record to Mixer_I2S input volume control */
/* 77 - 78: Reserved */
#घोषणा P17V_MIXER_AC97_ENABLE		0x79	/* Mixer AC97 input audio enable */
#घोषणा P17V_MIXER_SPDIF_ENABLE		0x7A	/* Mixer SPDIF input audio enable */
#घोषणा P17V_MIXER_I2S_ENABLE		0x7B	/* Mixer I2S input audio enable */
#घोषणा P17V_AUDIO_OUT_ENABLE		0x7C	/* Audio out enable */
#घोषणा P17V_MIXER_ATT			0x7D	/* SRP Mixer Attenuation Select */
#घोषणा P17V_SRP_RECORD_SRR		0x7E	/* SRP Record channel source Select */
#घोषणा P17V_SOFT_RESET_SRP_MIXER	0x7F	/* SRP and mixer soft reset */

#घोषणा P17V_AC97_OUT_MASTER_VOL_L	0x80	/* AC97 Output master volume control */
#घोषणा P17V_AC97_OUT_MASTER_VOL_H	0x81	/* AC97 Output master volume control */
#घोषणा P17V_SPDIF_OUT_MASTER_VOL_L	0x82	/* SPDIF Output master volume control */
#घोषणा P17V_SPDIF_OUT_MASTER_VOL_H	0x83	/* SPDIF Output master volume control */
#घोषणा P17V_I2S_OUT_MASTER_VOL_L	0x84	/* I2S Output master volume control */
#घोषणा P17V_I2S_OUT_MASTER_VOL_H	0x85	/* I2S Output master volume control */
/* 86 - 87: Not used */
#घोषणा P17V_I2S_CHANNEL_SWAP_PHASE_INVERSE	0x88	/* I2S out mono channel swap
							 * and phase inverse */
#घोषणा P17V_SPDIF_CHANNEL_SWAP_PHASE_INVERSE	0x89	/* SPDIF out mono channel swap
							 * and phase inverse */
/* 8A: Not used */
#घोषणा P17V_SRP_P17V_ESR		0x8B	/* SRP_P17V estimated sample rate and rate lock */
#घोषणा P17V_SRP_REC_ESR		0x8C	/* SRP_REC estimated sample rate and rate lock */
#घोषणा P17V_SRP_BYPASS			0x8D	/* srps channel bypass and srps bypass */
/* 8E - 92: Not used */
#घोषणा P17V_I2S_SRC_SEL		0x93	/* I2SIN mode sel */






