<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+
 *
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal पूर्णांकerface क्रम Audio Codec '97
 *
 *  For more details look to AC '97 component specअगरication revision 2.1
 *  by Intel Corporation (http://developer.पूर्णांकel.com).
 */
/*
 *  AC'97 codec रेजिस्टरs
 */

#घोषणा AC97_RESET		0x00	/* Reset */
#घोषणा AC97_MASTER		0x02	/* Master Volume */
#घोषणा AC97_HEADPHONE		0x04	/* Headphone Volume (optional) */
#घोषणा AC97_MASTER_MONO	0x06	/* Master Volume Mono (optional) */
#घोषणा AC97_MASTER_TONE	0x08	/* Master Tone (Bass & Treble) (optional) */
#घोषणा AC97_PC_BEEP		0x0a	/* PC Beep Volume (optional) */
#घोषणा AC97_PHONE		0x0c	/* Phone Volume (optional) */
#घोषणा AC97_MIC		0x0e	/* MIC Volume */
#घोषणा AC97_LINE		0x10	/* Line In Volume */
#घोषणा AC97_CD			0x12	/* CD Volume */
#घोषणा AC97_VIDEO		0x14	/* Video Volume (optional) */
#घोषणा AC97_AUX		0x16	/* AUX Volume (optional) */
#घोषणा AC97_PCM		0x18	/* PCM Volume */
#घोषणा AC97_REC_SEL		0x1a	/* Record Select */
#घोषणा AC97_REC_GAIN		0x1c	/* Record Gain */
#घोषणा AC97_REC_GAIN_MIC	0x1e	/* Record Gain MIC (optional) */
#घोषणा AC97_GENERAL_PURPOSE	0x20	/* General Purpose (optional) */
#घोषणा AC97_3D_CONTROL		0x22	/* 3D Control (optional) */
#घोषणा AC97_INT_PAGING		0x24	/* Audio Interrupt & Paging (AC'97 2.3) */
#घोषणा AC97_POWERDOWN		0x26	/* Powerकरोwn control / status */
/* range 0x28-0x3a - AUDIO AC'97 2.0 extensions */
#घोषणा AC97_EXTENDED_ID	0x28	/* Extended Audio ID */
#घोषणा AC97_EXTENDED_STATUS	0x2a	/* Extended Audio Status and Control */
#घोषणा AC97_PCM_FRONT_DAC_RATE 0x2c	/* PCM Front DAC Rate */
#घोषणा AC97_PCM_SURR_DAC_RATE	0x2e	/* PCM Surround DAC Rate */
#घोषणा AC97_PCM_LFE_DAC_RATE	0x30	/* PCM LFE DAC Rate */
#घोषणा AC97_PCM_LR_ADC_RATE	0x32	/* PCM LR ADC Rate */
#घोषणा AC97_PCM_MIC_ADC_RATE	0x34	/* PCM MIC ADC Rate */
#घोषणा AC97_CENTER_LFE_MASTER	0x36	/* Center + LFE Master Volume */
#घोषणा AC97_SURROUND_MASTER	0x38	/* Surround (Rear) Master Volume */
#घोषणा AC97_SPDIF		0x3a	/* S/PDIF control */
/* range 0x3c-0x58 - MODEM */
#घोषणा AC97_EXTENDED_MID	0x3c	/* Extended Modem ID */
#घोषणा AC97_EXTENDED_MSTATUS	0x3e	/* Extended Modem Status and Control */
#घोषणा AC97_LINE1_RATE		0x40	/* Line1 DAC/ADC Rate */
#घोषणा AC97_LINE2_RATE		0x42	/* Line2 DAC/ADC Rate */
#घोषणा AC97_HANDSET_RATE	0x44	/* Handset DAC/ADC Rate */
#घोषणा AC97_LINE1_LEVEL	0x46	/* Line1 DAC/ADC Level */
#घोषणा AC97_LINE2_LEVEL	0x48	/* Line2 DAC/ADC Level */
#घोषणा AC97_HANDSET_LEVEL	0x4a	/* Handset DAC/ADC Level */
#घोषणा AC97_GPIO_CFG		0x4c	/* GPIO Configuration */
#घोषणा AC97_GPIO_POLARITY	0x4e	/* GPIO Pin Polarity/Type, 0=low, 1=high active */
#घोषणा AC97_GPIO_STICKY	0x50	/* GPIO Pin Sticky, 0=not, 1=sticky */
#घोषणा AC97_GPIO_WAKEUP	0x52	/* GPIO Pin Wakeup, 0=no पूर्णांक, 1=yes पूर्णांक */
#घोषणा AC97_GPIO_STATUS	0x54	/* GPIO Pin Status, slot 12 */
#घोषणा AC97_MISC_AFE		0x56	/* Miscellaneous Modem AFE Status and Control */
/* range 0x5a-0x7b - Venकरोr Specअगरic */
#घोषणा AC97_VENDOR_ID1		0x7c	/* Venकरोr ID1 */
#घोषणा AC97_VENDOR_ID2		0x7e	/* Venकरोr ID2 / revision */
/* range 0x60-0x6f (page 1) - extended codec रेजिस्टरs */
#घोषणा AC97_CODEC_CLASS_REV	0x60	/* Codec Class/Revision */
#घोषणा AC97_PCI_SVID		0x62	/* PCI Subप्रणाली Venकरोr ID */
#घोषणा AC97_PCI_SID		0x64	/* PCI Subप्रणाली ID */
#घोषणा AC97_FUNC_SELECT	0x66	/* Function Select */
#घोषणा AC97_FUNC_INFO		0x68	/* Function Inक्रमmation */
#घोषणा AC97_SENSE_INFO		0x6a	/* Sense Details */

/* volume controls */
#घोषणा AC97_MUTE_MASK_MONO	0x8000
#घोषणा AC97_MUTE_MASK_STEREO	0x8080

/* slot allocation */
#घोषणा AC97_SLOT_TAG		0
#घोषणा AC97_SLOT_CMD_ADDR	1
#घोषणा AC97_SLOT_CMD_DATA	2
#घोषणा AC97_SLOT_PCM_LEFT	3
#घोषणा AC97_SLOT_PCM_RIGHT	4
#घोषणा AC97_SLOT_MODEM_LINE1	5
#घोषणा AC97_SLOT_PCM_CENTER	6
#घोषणा AC97_SLOT_MIC		6	/* input */
#घोषणा AC97_SLOT_SPDIF_LEFT1	6
#घोषणा AC97_SLOT_PCM_SLEFT	7	/* surround left */
#घोषणा AC97_SLOT_PCM_LEFT_0	7	/* द्विगुन rate operation */
#घोषणा AC97_SLOT_SPDIF_LEFT	7
#घोषणा AC97_SLOT_PCM_SRIGHT	8	/* surround right */
#घोषणा AC97_SLOT_PCM_RIGHT_0	8	/* द्विगुन rate operation */
#घोषणा AC97_SLOT_SPDIF_RIGHT	8
#घोषणा AC97_SLOT_LFE		9
#घोषणा AC97_SLOT_SPDIF_RIGHT1	9
#घोषणा AC97_SLOT_MODEM_LINE2	10
#घोषणा AC97_SLOT_PCM_LEFT_1	10	/* द्विगुन rate operation */
#घोषणा AC97_SLOT_SPDIF_LEFT2	10
#घोषणा AC97_SLOT_HANDSET	11	/* output */
#घोषणा AC97_SLOT_PCM_RIGHT_1	11	/* द्विगुन rate operation */
#घोषणा AC97_SLOT_SPDIF_RIGHT2	11
#घोषणा AC97_SLOT_MODEM_GPIO	12	/* modem GPIO */
#घोषणा AC97_SLOT_PCM_CENTER_1	12	/* द्विगुन rate operation */

/* basic capabilities (reset रेजिस्टर) */
#घोषणा AC97_BC_DEDICATED_MIC	0x0001	/* Dedicated Mic PCM In Channel */
#घोषणा AC97_BC_RESERVED1	0x0002	/* Reserved (was Modem Line Codec support) */
#घोषणा AC97_BC_BASS_TREBLE	0x0004	/* Bass & Treble Control */
#घोषणा AC97_BC_SIM_STEREO	0x0008	/* Simulated stereo */
#घोषणा AC97_BC_HEADPHONE	0x0010	/* Headphone Out Support */
#घोषणा AC97_BC_LOUDNESS	0x0020	/* Loudness (bass boost) Support */
#घोषणा AC97_BC_16BIT_DAC	0x0000	/* 16-bit DAC resolution */
#घोषणा AC97_BC_18BIT_DAC	0x0040	/* 18-bit DAC resolution */
#घोषणा AC97_BC_20BIT_DAC	0x0080	/* 20-bit DAC resolution */
#घोषणा AC97_BC_DAC_MASK	0x00c0
#घोषणा AC97_BC_16BIT_ADC	0x0000	/* 16-bit ADC resolution */
#घोषणा AC97_BC_18BIT_ADC	0x0100	/* 18-bit ADC resolution */
#घोषणा AC97_BC_20BIT_ADC	0x0200	/* 20-bit ADC resolution */
#घोषणा AC97_BC_ADC_MASK	0x0300
#घोषणा AC97_BC_3D_TECH_ID_MASK	0x7c00	/* Per-venकरोr ID of 3D enhancement */

/* general purpose */
#घोषणा AC97_GP_DRSS_MASK	0x0c00	/* द्विगुन rate slot select */
#घोषणा AC97_GP_DRSS_1011	0x0000	/* LR(C) 10+11(+12) */
#घोषणा AC97_GP_DRSS_78		0x0400	/* LR 7+8 */

/* घातerकरोwn bits */
#घोषणा AC97_PD_ADC_STATUS	0x0001	/* ADC status (RO) */
#घोषणा AC97_PD_DAC_STATUS	0x0002	/* DAC status (RO) */
#घोषणा AC97_PD_MIXER_STATUS	0x0004	/* Analog mixer status (RO) */
#घोषणा AC97_PD_VREF_STATUS	0x0008	/* Vref status (RO) */
#घोषणा AC97_PD_PR0		0x0100	/* Power करोwn PCM ADCs and input MUX */
#घोषणा AC97_PD_PR1		0x0200	/* Power करोwn PCM front DAC */
#घोषणा AC97_PD_PR2		0x0400	/* Power करोwn Mixer (Vref still on) */
#घोषणा AC97_PD_PR3		0x0800	/* Power करोwn Mixer (Vref off) */
#घोषणा AC97_PD_PR4		0x1000	/* Power करोwn AC-Link */
#घोषणा AC97_PD_PR5		0x2000	/* Disable पूर्णांकernal घड़ी usage */
#घोषणा AC97_PD_PR6		0x4000	/* Headphone amplअगरier */
#घोषणा AC97_PD_EAPD		0x8000	/* External Amplअगरer Power Down (EAPD) */

/* extended audio ID bit defines */
#घोषणा AC97_EI_VRA		0x0001	/* Variable bit rate supported */
#घोषणा AC97_EI_DRA		0x0002	/* Double rate supported */
#घोषणा AC97_EI_SPDIF		0x0004	/* S/PDIF out supported */
#घोषणा AC97_EI_VRM		0x0008	/* Variable bit rate supported क्रम MIC */
#घोषणा AC97_EI_DACS_SLOT_MASK	0x0030	/* DACs slot assignment */
#घोषणा AC97_EI_DACS_SLOT_SHIFT	4
#घोषणा AC97_EI_CDAC		0x0040	/* PCM Center DAC available */
#घोषणा AC97_EI_SDAC		0x0080	/* PCM Surround DACs available */
#घोषणा AC97_EI_LDAC		0x0100	/* PCM LFE DAC available */
#घोषणा AC97_EI_AMAP		0x0200	/* indicates optional slot/DAC mapping based on codec ID */
#घोषणा AC97_EI_REV_MASK	0x0c00	/* AC'97 revision mask */
#घोषणा AC97_EI_REV_22		0x0400	/* AC'97 revision 2.2 */
#घोषणा AC97_EI_REV_23		0x0800	/* AC'97 revision 2.3 */
#घोषणा AC97_EI_REV_SHIFT	10
#घोषणा AC97_EI_ADDR_MASK	0xc000	/* physical codec ID (address) */
#घोषणा AC97_EI_ADDR_SHIFT	14

/* extended audio status and control bit defines */
#घोषणा AC97_EA_VRA		0x0001	/* Variable bit rate enable bit */
#घोषणा AC97_EA_DRA		0x0002	/* Double-rate audio enable bit */
#घोषणा AC97_EA_SPDIF		0x0004	/* S/PDIF out enable bit */
#घोषणा AC97_EA_VRM		0x0008	/* Variable bit rate क्रम MIC enable bit */
#घोषणा AC97_EA_SPSA_SLOT_MASK	0x0030	/* Mask क्रम slot assignment bits */
#घोषणा AC97_EA_SPSA_SLOT_SHIFT 4
#घोषणा AC97_EA_SPSA_3_4	0x0000	/* Slot asचिन्हित to 3 & 4 */
#घोषणा AC97_EA_SPSA_7_8	0x0010	/* Slot asचिन्हित to 7 & 8 */
#घोषणा AC97_EA_SPSA_6_9	0x0020	/* Slot asचिन्हित to 6 & 9 */
#घोषणा AC97_EA_SPSA_10_11	0x0030	/* Slot asचिन्हित to 10 & 11 */
#घोषणा AC97_EA_CDAC		0x0040	/* PCM Center DAC is पढ़ोy (Read only) */
#घोषणा AC97_EA_SDAC		0x0080	/* PCM Surround DACs are पढ़ोy (Read only) */
#घोषणा AC97_EA_LDAC		0x0100	/* PCM LFE DAC is पढ़ोy (Read only) */
#घोषणा AC97_EA_MDAC		0x0200	/* MIC ADC is पढ़ोy (Read only) */
#घोषणा AC97_EA_SPCV		0x0400	/* S/PDIF configuration valid (Read only) */
#घोषणा AC97_EA_PRI		0x0800	/* Turns the PCM Center DAC off */
#घोषणा AC97_EA_PRJ		0x1000	/* Turns the PCM Surround DACs off */
#घोषणा AC97_EA_PRK		0x2000	/* Turns the PCM LFE DAC off */
#घोषणा AC97_EA_PRL		0x4000	/* Turns the MIC ADC off */

/* S/PDIF control bit defines */
#घोषणा AC97_SC_PRO		0x0001	/* Professional status */
#घोषणा AC97_SC_NAUDIO		0x0002	/* Non audio stream */
#घोषणा AC97_SC_COPY		0x0004	/* Copyright status */
#घोषणा AC97_SC_PRE		0x0008	/* Preemphasis status */
#घोषणा AC97_SC_CC_MASK		0x07f0	/* Category Code mask */
#घोषणा AC97_SC_CC_SHIFT	4
#घोषणा AC97_SC_L		0x0800	/* Generation Level status */
#घोषणा AC97_SC_SPSR_MASK	0x3000	/* S/PDIF Sample Rate bits */
#घोषणा AC97_SC_SPSR_SHIFT	12
#घोषणा AC97_SC_SPSR_44K	0x0000	/* Use 44.1kHz Sample rate */
#घोषणा AC97_SC_SPSR_48K	0x2000	/* Use 48kHz Sample rate */
#घोषणा AC97_SC_SPSR_32K	0x3000	/* Use 32kHz Sample rate */
#घोषणा AC97_SC_DRS		0x4000	/* Double Rate S/PDIF */
#घोषणा AC97_SC_V		0x8000	/* Validity status */

/* Interrupt and Paging bit defines (AC'97 2.3) */
#घोषणा AC97_PAGE_MASK		0x000f	/* Page Selector */
#घोषणा AC97_PAGE_VENDOR	0	/* Venकरोr-specअगरic रेजिस्टरs */
#घोषणा AC97_PAGE_1		1	/* Extended Codec Registers page 1 */
#घोषणा AC97_INT_ENABLE		0x0800	/* Interrupt Enable */
#घोषणा AC97_INT_SENSE		0x1000	/* Sense Cycle */
#घोषणा AC97_INT_CAUSE_SENSE	0x2000	/* Sense Cycle Completed (RO) */
#घोषणा AC97_INT_CAUSE_GPIO	0x4000	/* GPIO bits changed (RO) */
#घोषणा AC97_INT_STATUS		0x8000	/* Interrupt Status */

/* extended modem ID bit defines */
#घोषणा AC97_MEI_LINE1		0x0001	/* Line1 present */
#घोषणा AC97_MEI_LINE2		0x0002	/* Line2 present */
#घोषणा AC97_MEI_HANDSET	0x0004	/* Handset present */
#घोषणा AC97_MEI_CID1		0x0008	/* caller ID decode क्रम Line1 is supported */
#घोषणा AC97_MEI_CID2		0x0010	/* caller ID decode क्रम Line2 is supported */
#घोषणा AC97_MEI_ADDR_MASK	0xc000	/* physical codec ID (address) */
#घोषणा AC97_MEI_ADDR_SHIFT	14

/* extended modem status and control bit defines */
#घोषणा AC97_MEA_GPIO		0x0001	/* GPIO is पढ़ोy (ro) */
#घोषणा AC97_MEA_MREF		0x0002	/* Vref is up to nominal level (ro) */
#घोषणा AC97_MEA_ADC1		0x0004	/* ADC1 operational (ro) */
#घोषणा AC97_MEA_DAC1		0x0008	/* DAC1 operational (ro) */
#घोषणा AC97_MEA_ADC2		0x0010	/* ADC2 operational (ro) */
#घोषणा AC97_MEA_DAC2		0x0020	/* DAC2 operational (ro) */
#घोषणा AC97_MEA_HADC		0x0040	/* HADC operational (ro) */
#घोषणा AC97_MEA_HDAC		0x0080	/* HDAC operational (ro) */
#घोषणा AC97_MEA_PRA		0x0100	/* GPIO घातer करोwn (high) */
#घोषणा AC97_MEA_PRB		0x0200	/* reserved */
#घोषणा AC97_MEA_PRC		0x0400	/* ADC1 घातer करोwn (high) */
#घोषणा AC97_MEA_PRD		0x0800	/* DAC1 घातer करोwn (high) */
#घोषणा AC97_MEA_PRE		0x1000	/* ADC2 घातer करोwn (high) */
#घोषणा AC97_MEA_PRF		0x2000	/* DAC2 घातer करोwn (high) */
#घोषणा AC97_MEA_PRG		0x4000	/* HADC घातer करोwn (high) */
#घोषणा AC97_MEA_PRH		0x8000	/* HDAC घातer करोwn (high) */

/* modem gpio status defines */
#घोषणा AC97_GPIO_LINE1_OH      0x0001  /* Off Hook Line1 */
#घोषणा AC97_GPIO_LINE1_RI      0x0002  /* Ring Detect Line1 */
#घोषणा AC97_GPIO_LINE1_CID     0x0004  /* Caller ID path enable Line1 */
#घोषणा AC97_GPIO_LINE1_LCS     0x0008  /* Loop Current Sense Line1 */
#घोषणा AC97_GPIO_LINE1_PULSE   0x0010  /* Opt./ Pulse Dial Line1 (out) */
#घोषणा AC97_GPIO_LINE1_HL1R    0x0020  /* Opt./ Handset to Line1 relay control (out) */
#घोषणा AC97_GPIO_LINE1_HOHD    0x0040  /* Opt./ Handset off hook detect Line1 (in) */
#घोषणा AC97_GPIO_LINE12_AC     0x0080  /* Opt./ Int.bit 1 / Line1/2 AC (out) */
#घोषणा AC97_GPIO_LINE12_DC     0x0100  /* Opt./ Int.bit 2 / Line1/2 DC (out) */
#घोषणा AC97_GPIO_LINE12_RS     0x0200  /* Opt./ Int.bit 3 / Line1/2 RS (out) */
#घोषणा AC97_GPIO_LINE2_OH      0x0400  /* Off Hook Line2 */
#घोषणा AC97_GPIO_LINE2_RI      0x0800  /* Ring Detect Line2 */
#घोषणा AC97_GPIO_LINE2_CID     0x1000  /* Caller ID path enable Line2 */
#घोषणा AC97_GPIO_LINE2_LCS     0x2000  /* Loop Current Sense Line2 */
#घोषणा AC97_GPIO_LINE2_PULSE   0x4000  /* Opt./ Pulse Dial Line2 (out) */
#घोषणा AC97_GPIO_LINE2_HL1R    0x8000  /* Opt./ Handset to Line2 relay control (out) */

