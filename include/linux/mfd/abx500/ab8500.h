<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Srinidhi Kasagar <srinidhi.kasagar@stericsson.com>
 */
#अगर_अघोषित MFD_AB8500_H
#घोषणा MFD_AB8500_H

#समावेश <linux/atomic.h>
#समावेश <linux/mutex.h>
#समावेश <linux/irqकरोमुख्य.h>

काष्ठा device;

/*
 * AB IC versions
 *
 * AB8500_VERSION_AB8500 should be 0xFF but will never be पढ़ो as need a
 * non-supported multi-byte I2C access via PRCMU. Set to 0x00 to ease the
 * prपूर्णांक of version string.
 */
क्रमागत ab8500_version अणु
	AB8500_VERSION_AB8500 = 0x0,
	AB8500_VERSION_AB8505 = 0x1,
	AB8500_VERSION_AB9540 = 0x2,
	AB8500_VERSION_AB8540 = 0x4,
	AB8500_VERSION_UNDEFINED,
पूर्ण;

/* AB8500 CIDs*/
#घोषणा AB8500_CUTEARLY	0x00
#घोषणा AB8500_CUT1P0	0x10
#घोषणा AB8500_CUT1P1	0x11
#घोषणा AB8500_CUT1P2	0x12 /* Only valid क्रम AB8540 */
#घोषणा AB8500_CUT2P0	0x20
#घोषणा AB8500_CUT3P0	0x30
#घोषणा AB8500_CUT3P3	0x33

/*
 * AB8500 bank addresses
 */
#घोषणा AB8500_M_FSM_RANK	0x0
#घोषणा AB8500_SYS_CTRL1_BLOCK	0x1
#घोषणा AB8500_SYS_CTRL2_BLOCK	0x2
#घोषणा AB8500_REGU_CTRL1	0x3
#घोषणा AB8500_REGU_CTRL2	0x4
#घोषणा AB8500_USB		0x5
#घोषणा AB8500_TVOUT		0x6
#घोषणा AB8500_DBI		0x7
#घोषणा AB8500_ECI_AV_ACC	0x8
#घोषणा AB8500_RESERVED		0x9
#घोषणा AB8500_GPADC		0xA
#घोषणा AB8500_CHARGER		0xB
#घोषणा AB8500_GAS_GAUGE	0xC
#घोषणा AB8500_AUDIO		0xD
#घोषणा AB8500_INTERRUPT	0xE
#घोषणा AB8500_RTC		0xF
#घोषणा AB8500_MISC		0x10
#घोषणा AB8500_DEVELOPMENT	0x11
#घोषणा AB8500_DEBUG		0x12
#घोषणा AB8500_PROD_TEST	0x13
#घोषणा AB8500_STE_TEST		0x14
#घोषणा AB8500_OTP_EMUL		0x15

#घोषणा AB8500_DEBUG_FIELD_LAST	0x16

/*
 * Interrupts
 * Values used to index पूर्णांकo array ab8500_irq_regoffset[] defined in
 * drivers/mdf/ab8500-core.c
 */
/* Definitions क्रम AB8500, AB9540 and AB8540 */
/* ab8500_irq_regoffset[0] -> IT[Source|Latch|Mask]1 */
#घोषणा AB8500_INT_MAIN_EXT_CH_NOT_OK	0 /* not 8505/9540 */
#घोषणा AB8500_INT_UN_PLUG_TV_DET	1 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_PLUG_TV_DET		2 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_TEMP_WARM		3
#घोषणा AB8500_INT_PON_KEY2DB_F		4
#घोषणा AB8500_INT_PON_KEY2DB_R		5
#घोषणा AB8500_INT_PON_KEY1DB_F		6
#घोषणा AB8500_INT_PON_KEY1DB_R		7
/* ab8500_irq_regoffset[1] -> IT[Source|Latch|Mask]2 */
#घोषणा AB8500_INT_BATT_OVV		8
#घोषणा AB8500_INT_MAIN_CH_UNPLUG_DET	10 /* not 8505/8540 */
#घोषणा AB8500_INT_MAIN_CH_PLUG_DET	11 /* not 8505/8540 */
#घोषणा AB8500_INT_VBUS_DET_F		14
#घोषणा AB8500_INT_VBUS_DET_R		15
/* ab8500_irq_regoffset[2] -> IT[Source|Latch|Mask]3 */
#घोषणा AB8500_INT_VBUS_CH_DROP_END	16
#घोषणा AB8500_INT_RTC_60S		17
#घोषणा AB8500_INT_RTC_ALARM		18
#घोषणा AB8540_INT_BIF_INT		19
#घोषणा AB8500_INT_BAT_CTRL_INDB	20
#घोषणा AB8500_INT_CH_WD_EXP		21
#घोषणा AB8500_INT_VBUS_OVV		22
#घोषणा AB8500_INT_MAIN_CH_DROP_END	23 /* not 8505/9540/8540 */
/* ab8500_irq_regoffset[3] -> IT[Source|Latch|Mask]4 */
#घोषणा AB8500_INT_CCN_CONV_ACC		24
#घोषणा AB8500_INT_INT_AUD		25
#घोषणा AB8500_INT_CCEOC		26
#घोषणा AB8500_INT_CC_INT_CALIB		27
#घोषणा AB8500_INT_LOW_BAT_F		28
#घोषणा AB8500_INT_LOW_BAT_R		29
#घोषणा AB8500_INT_BUP_CHG_NOT_OK	30
#घोषणा AB8500_INT_BUP_CHG_OK		31
/* ab8500_irq_regoffset[4] -> IT[Source|Latch|Mask]5 */
#घोषणा AB8500_INT_GP_HW_ADC_CONV_END	32 /* not 8505/8540 */
#घोषणा AB8500_INT_ACC_DETECT_1DB_F	33
#घोषणा AB8500_INT_ACC_DETECT_1DB_R	34
#घोषणा AB8500_INT_ACC_DETECT_22DB_F	35
#घोषणा AB8500_INT_ACC_DETECT_22DB_R	36
#घोषणा AB8500_INT_ACC_DETECT_21DB_F	37
#घोषणा AB8500_INT_ACC_DETECT_21DB_R	38
#घोषणा AB8500_INT_GP_SW_ADC_CONV_END	39
/* ab8500_irq_regoffset[5] -> IT[Source|Latch|Mask]7 */
#घोषणा AB8500_INT_GPIO6R		40 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO7R		41 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO8R		42 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO9R		43 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO10R		44 /* not 8540 */
#घोषणा AB8500_INT_GPIO11R		45 /* not 8540 */
#घोषणा AB8500_INT_GPIO12R		46 /* not 8505/8540 */
#घोषणा AB8500_INT_GPIO13R		47 /* not 8540 */
/* ab8500_irq_regoffset[6] -> IT[Source|Latch|Mask]8 */
#घोषणा AB8500_INT_GPIO24R		48 /* not 8505/8540 */
#घोषणा AB8500_INT_GPIO25R		49 /* not 8505/8540 */
#घोषणा AB8500_INT_GPIO36R		50 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO37R		51 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO38R		52 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO39R		53 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO40R		54 /* not 8540 */
#घोषणा AB8500_INT_GPIO41R		55 /* not 8540 */
/* ab8500_irq_regoffset[7] -> IT[Source|Latch|Mask]9 */
#घोषणा AB8500_INT_GPIO6F		56 /* not 8505/9540 */
#घोषणा AB8500_INT_GPIO7F		57 /* not 8505/9540 */
#घोषणा AB8500_INT_GPIO8F		58 /* not 8505/9540 */
#घोषणा AB8500_INT_GPIO9F		59 /* not 8505/9540 */
#घोषणा AB8500_INT_GPIO10F		60
#घोषणा AB8500_INT_GPIO11F		61
#घोषणा AB8500_INT_GPIO12F		62 /* not 8505 */
#घोषणा AB8500_INT_GPIO13F		63
/* ab8500_irq_regoffset[8] -> IT[Source|Latch|Mask]10 */
#घोषणा AB8500_INT_GPIO24F		64 /* not 8505/8540 */
#घोषणा AB8500_INT_GPIO25F		65 /* not 8505/8540 */
#घोषणा AB8500_INT_GPIO36F		66 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO37F		67 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO38F		68 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO39F		69 /* not 8505/9540/8540 */
#घोषणा AB8500_INT_GPIO40F		70 /* not 8540 */
#घोषणा AB8500_INT_GPIO41F		71 /* not 8540 */
/* ab8500_irq_regoffset[9] -> IT[Source|Latch|Mask]12 */
#घोषणा AB8500_INT_ADP_SOURCE_ERROR	72
#घोषणा AB8500_INT_ADP_SINK_ERROR	73
#घोषणा AB8500_INT_ADP_PROBE_PLUG	74
#घोषणा AB8500_INT_ADP_PROBE_UNPLUG	75
#घोषणा AB8500_INT_ADP_SENSE_OFF	76
#घोषणा AB8500_INT_USB_PHY_POWER_ERR	78
#घोषणा AB8500_INT_USB_LINK_STATUS	79
/* ab8500_irq_regoffset[10] -> IT[Source|Latch|Mask]19 */
#घोषणा AB8500_INT_BTEMP_LOW		80
#घोषणा AB8500_INT_BTEMP_LOW_MEDIUM	81
#घोषणा AB8500_INT_BTEMP_MEDIUM_HIGH	82
#घोषणा AB8500_INT_BTEMP_HIGH		83
/* ab8500_irq_regoffset[11] -> IT[Source|Latch|Mask]20 */
#घोषणा AB8500_INT_SRP_DETECT		88
#घोषणा AB8500_INT_USB_CHARGER_NOT_OKR	89
#घोषणा AB8500_INT_ID_WAKEUP_R		90
#घोषणा AB8500_INT_ID_DET_PLUGR         91 /* 8505/9540 cut2.0 */
#घोषणा AB8500_INT_ID_DET_R1R		92
#घोषणा AB8500_INT_ID_DET_R2R		93
#घोषणा AB8500_INT_ID_DET_R3R		94
#घोषणा AB8500_INT_ID_DET_R4R		95
/* ab8500_irq_regoffset[12] -> IT[Source|Latch|Mask]21 */
#घोषणा AB8500_INT_ID_WAKEUP_F		96 /* not 8505/9540 */
#घोषणा AB8500_INT_ID_DET_PLUGF		97 /* 8505/9540 cut2.0 */
#घोषणा AB8500_INT_ID_DET_R1F		98 /* not 8505/9540 */
#घोषणा AB8500_INT_ID_DET_R2F		99 /* not 8505/9540 */
#घोषणा AB8500_INT_ID_DET_R3F		100 /* not 8505/9540 */
#घोषणा AB8500_INT_ID_DET_R4F		101 /* not 8505/9540 */
#घोषणा AB8500_INT_CHAUTORESTARTAFTSEC	102 /* not 8505/9540 */
#घोषणा AB8500_INT_CHSTOPBYSEC		103
/* ab8500_irq_regoffset[13] -> IT[Source|Latch|Mask]22 */
#घोषणा AB8500_INT_USB_CH_TH_PROT_F	104
#घोषणा AB8500_INT_USB_CH_TH_PROT_R	105
#घोषणा AB8500_INT_MAIN_CH_TH_PROT_F	106 /* not 8505/9540 */
#घोषणा AB8500_INT_MAIN_CH_TH_PROT_R	107 /* not 8505/9540 */
#घोषणा AB8500_INT_CHCURLIMNOHSCHIRP	109
#घोषणा AB8500_INT_CHCURLIMHSCHIRP	110
#घोषणा AB8500_INT_XTAL32K_KO		111

/* Definitions क्रम AB9540 / AB8505 */
/* ab8500_irq_regoffset[14] -> IT[Source|Latch|Mask]13 */
#घोषणा AB9540_INT_GPIO50R		113 /* not 8540 */
#घोषणा AB9540_INT_GPIO51R		114 /* not 8505/8540 */
#घोषणा AB9540_INT_GPIO52R		115 /* not 8540 */
#घोषणा AB9540_INT_GPIO53R		116 /* not 8540 */
#घोषणा AB9540_INT_GPIO54R		117 /* not 8505/8540 */
#घोषणा AB9540_INT_IEXT_CH_RF_BFN_R	118
/* ab8500_irq_regoffset[15] -> IT[Source|Latch|Mask]14 */
#घोषणा AB9540_INT_GPIO50F		121 /* not 8540 */
#घोषणा AB9540_INT_GPIO51F		122 /* not 8505/8540 */
#घोषणा AB9540_INT_GPIO52F		123 /* not 8540 */
#घोषणा AB9540_INT_GPIO53F		124 /* not 8540 */
#घोषणा AB9540_INT_GPIO54F		125 /* not 8505/8540 */
#घोषणा AB9540_INT_IEXT_CH_RF_BFN_F	126
/* ab8500_irq_regoffset[16] -> IT[Source|Latch|Mask]25 */
#घोषणा AB8505_INT_KEYSTUCK		128
#घोषणा AB8505_INT_IKR			129
#घोषणा AB8505_INT_IKP			130
#घोषणा AB8505_INT_KP			131
#घोषणा AB8505_INT_KEYDEGLITCH		132
#घोषणा AB8505_INT_MODPWRSTATUSF	134
#घोषणा AB8505_INT_MODPWRSTATUSR	135
/* ab8500_irq_regoffset[17] -> IT[Source|Latch|Mask]6 */
#घोषणा AB8500_INT_HOOK_DET_NEG_F	138
#घोषणा AB8500_INT_HOOK_DET_NEG_R	139
#घोषणा AB8500_INT_HOOK_DET_POS_F	140
#घोषणा AB8500_INT_HOOK_DET_POS_R	141
#घोषणा AB8500_INT_PLUG_DET_COMP_F	142
#घोषणा AB8500_INT_PLUG_DET_COMP_R	143
/* ab8500_irq_regoffset[18] -> IT[Source|Latch|Mask]23 */
#घोषणा AB8505_INT_COLL			144
#घोषणा AB8505_INT_RESERR		145
#घोषणा AB8505_INT_FRAERR		146
#घोषणा AB8505_INT_COMERR		147
#घोषणा AB8505_INT_SPDSET		148
#घोषणा AB8505_INT_DSENT		149
#घोषणा AB8505_INT_DREC			150
#घोषणा AB8505_INT_ACC_INT		151
/* ab8500_irq_regoffset[19] -> IT[Source|Latch|Mask]24 */
#घोषणा AB8505_INT_NOPINT		152
/* ab8540_irq_regoffset[20] -> IT[Source|Latch|Mask]26 */
#घोषणा AB8540_INT_IDPLUGDETCOMPF	160
#घोषणा AB8540_INT_IDPLUGDETCOMPR	161
#घोषणा AB8540_INT_FMDETCOMPLOF		162
#घोषणा AB8540_INT_FMDETCOMPLOR		163
#घोषणा AB8540_INT_FMDETCOMPHIF		164
#घोषणा AB8540_INT_FMDETCOMPHIR		165
#घोषणा AB8540_INT_ID5VDETCOMPF		166
#घोषणा AB8540_INT_ID5VDETCOMPR		167
/* ab8540_irq_regoffset[21] -> IT[Source|Latch|Mask]27 */
#घोषणा AB8540_INT_GPIO43F		168
#घोषणा AB8540_INT_GPIO43R		169
#घोषणा AB8540_INT_GPIO44F		170
#घोषणा AB8540_INT_GPIO44R		171
#घोषणा AB8540_INT_KEYPOSDETCOMPF	172
#घोषणा AB8540_INT_KEYPOSDETCOMPR	173
#घोषणा AB8540_INT_KEYNEGDETCOMPF	174
#घोषणा AB8540_INT_KEYNEGDETCOMPR	175
/* ab8540_irq_regoffset[22] -> IT[Source|Latch|Mask]28 */
#घोषणा AB8540_INT_GPIO1VBATF		176
#घोषणा AB8540_INT_GPIO1VBATR		177
#घोषणा AB8540_INT_GPIO2VBATF		178
#घोषणा AB8540_INT_GPIO2VBATR		179
#घोषणा AB8540_INT_GPIO3VBATF		180
#घोषणा AB8540_INT_GPIO3VBATR		181
#घोषणा AB8540_INT_GPIO4VBATF		182
#घोषणा AB8540_INT_GPIO4VBATR		183
/* ab8540_irq_regoffset[23] -> IT[Source|Latch|Mask]29 */
#घोषणा AB8540_INT_SYSCLKREQ2F		184
#घोषणा AB8540_INT_SYSCLKREQ2R		185
#घोषणा AB8540_INT_SYSCLKREQ3F		186
#घोषणा AB8540_INT_SYSCLKREQ3R		187
#घोषणा AB8540_INT_SYSCLKREQ4F		188
#घोषणा AB8540_INT_SYSCLKREQ4R		189
#घोषणा AB8540_INT_SYSCLKREQ5F		190
#घोषणा AB8540_INT_SYSCLKREQ5R		191
/* ab8540_irq_regoffset[24] -> IT[Source|Latch|Mask]30 */
#घोषणा AB8540_INT_PWMOUT1F		192
#घोषणा AB8540_INT_PWMOUT1R		193
#घोषणा AB8540_INT_PWMCTRL0F		194
#घोषणा AB8540_INT_PWMCTRL0R		195
#घोषणा AB8540_INT_PWMCTRL1F		196
#घोषणा AB8540_INT_PWMCTRL1R		197
#घोषणा AB8540_INT_SYSCLKREQ6F		198
#घोषणा AB8540_INT_SYSCLKREQ6R		199
/* ab8540_irq_regoffset[25] -> IT[Source|Latch|Mask]31 */
#घोषणा AB8540_INT_PWMEXTVIBRA1F	200
#घोषणा AB8540_INT_PWMEXTVIBRA1R	201
#घोषणा AB8540_INT_PWMEXTVIBRA2F	202
#घोषणा AB8540_INT_PWMEXTVIBRA2R	203
#घोषणा AB8540_INT_PWMOUT2F		204
#घोषणा AB8540_INT_PWMOUT2R		205
#घोषणा AB8540_INT_PWMOUT3F		206
#घोषणा AB8540_INT_PWMOUT3R		207
/* ab8540_irq_regoffset[26] -> IT[Source|Latch|Mask]32 */
#घोषणा AB8540_INT_ADDATA2F		208
#घोषणा AB8540_INT_ADDATA2R		209
#घोषणा AB8540_INT_DADATA2F		210
#घोषणा AB8540_INT_DADATA2R		211
#घोषणा AB8540_INT_FSYNC2F		212
#घोषणा AB8540_INT_FSYNC2R		213
#घोषणा AB8540_INT_BITCLK2F		214
#घोषणा AB8540_INT_BITCLK2R		215
/* ab8540_irq_regoffset[27] -> IT[Source|Latch|Mask]33 */
#घोषणा AB8540_INT_RTC_1S		216

/*
 * AB8500_AB9540_NR_IRQS is used when configuring the IRQ numbers क्रम the
 * entire platक्रमm. This is a "compile time" स्थिरant so this must be set to
 * the largest possible value that may be encountered with dअगरferent AB SOCs.
 * Of the currently supported AB devices, AB8500 and AB9540, it is the AB9540
 * which is larger.
 */
#घोषणा AB8500_NR_IRQS			112
#घोषणा AB8505_NR_IRQS			153
#घोषणा AB9540_NR_IRQS			153
#घोषणा AB8540_NR_IRQS			216
/* This is set to the roof of any AB8500 chip variant IRQ counts */
#घोषणा AB8500_MAX_NR_IRQS		AB8540_NR_IRQS

#घोषणा AB8500_NUM_IRQ_REGS		14
#घोषणा AB9540_NUM_IRQ_REGS		20
#घोषणा AB8540_NUM_IRQ_REGS		27

/* Turn On Status Event */
#घोषणा AB8500_POR_ON_VBAT		0x01
#घोषणा AB8500_POW_KEY_1_ON		0x02
#घोषणा AB8500_POW_KEY_2_ON		0x04
#घोषणा AB8500_RTC_ALARM		0x08
#घोषणा AB8500_MAIN_CH_DET		0x10
#घोषणा AB8500_VBUS_DET			0x20
#घोषणा AB8500_USB_ID_DET		0x40

/**
 * काष्ठा ab8500 - ab8500 पूर्णांकernal काष्ठाure
 * @dev: parent device
 * @lock: पढ़ो/ग_लिखो operations lock
 * @irq_lock: genirq bus lock
 * @transfer_ongoing: 0 अगर no transfer ongoing
 * @irq: irq line
 * @irq_करोमुख्य: irq करोमुख्य
 * @version: chip version id (e.g. ab8500 or ab9540)
 * @chip_id: chip revision id
 * @ग_लिखो: रेजिस्टर ग_लिखो
 * @ग_लिखो_masked: masked रेजिस्टर ग_लिखो
 * @पढ़ो: रेजिस्टर पढ़ो
 * @rx_buf: rx buf क्रम SPI
 * @tx_buf: tx buf क्रम SPI
 * @mask: cache of IRQ regs क्रम bus lock
 * @oldmask: cache of previous IRQ regs क्रम bus lock
 * @mask_size: Actual number of valid entries in mask[], oldmask[] and
 * irq_reg_offset
 * @irq_reg_offset: Array of offsets पूर्णांकo IRQ रेजिस्टरs
 */
काष्ठा ab8500 अणु
	काष्ठा device	*dev;
	काष्ठा mutex	lock;
	काष्ठा mutex	irq_lock;
	atomic_t	transfer_ongoing;
	पूर्णांक		irq;
	काष्ठा irq_करोमुख्य  *करोमुख्य;
	क्रमागत ab8500_version version;
	u8		chip_id;

	पूर्णांक (*ग_लिखो)(काष्ठा ab8500 *ab8500, u16 addr, u8 data);
	पूर्णांक (*ग_लिखो_masked)(काष्ठा ab8500 *ab8500, u16 addr, u8 mask, u8 data);
	पूर्णांक (*पढ़ो)(काष्ठा ab8500 *ab8500, u16 addr);

	अचिन्हित दीर्घ	tx_buf[4];
	अचिन्हित दीर्घ	rx_buf[4];

	u8 *mask;
	u8 *oldmask;
	पूर्णांक mask_size;
	स्थिर पूर्णांक *irq_reg_offset;
	पूर्णांक it_latchhier_num;
पूर्ण;

काष्ठा ab8500_codec_platक्रमm_data;
काष्ठा ab8500_sysctrl_platक्रमm_data;

/**
 * काष्ठा ab8500_platक्रमm_data - AB8500 platक्रमm data
 * @irq_base: start of AB8500 IRQs, AB8500_NR_IRQS will be used
 * @init: board-specअगरic initialization after detection of ab8500
 */
काष्ठा ab8500_platक्रमm_data अणु
	व्योम (*init) (काष्ठा ab8500 *);
	काष्ठा ab8500_codec_platक्रमm_data *codec;
	काष्ठा ab8500_sysctrl_platक्रमm_data *sysctrl;
पूर्ण;

बाह्य पूर्णांक ab8500_init(काष्ठा ab8500 *ab8500,
				 क्रमागत ab8500_version version);
बाह्य पूर्णांक ab8500_निकास(काष्ठा ab8500 *ab8500);

बाह्य पूर्णांक ab8500_suspend(काष्ठा ab8500 *ab8500);

अटल अंतरभूत पूर्णांक is_ab8500(काष्ठा ab8500 *ab)
अणु
	वापस ab->version == AB8500_VERSION_AB8500;
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8505(काष्ठा ab8500 *ab)
अणु
	वापस ab->version == AB8500_VERSION_AB8505;
पूर्ण

अटल अंतरभूत पूर्णांक is_ab9540(काष्ठा ab8500 *ab)
अणु
	वापस ab->version == AB8500_VERSION_AB9540;
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8540(काष्ठा ab8500 *ab)
अणु
	वापस ab->version == AB8500_VERSION_AB8540;
पूर्ण

/* exclude also ab8505, ab9540... */
अटल अंतरभूत पूर्णांक is_ab8500_1p0_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab8500(ab) && (ab->chip_id <= AB8500_CUT1P0));
पूर्ण

/* exclude also ab8505, ab9540... */
अटल अंतरभूत पूर्णांक is_ab8500_1p1_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab8500(ab) && (ab->chip_id <= AB8500_CUT1P1));
पूर्ण

/* exclude also ab8505, ab9540... */
अटल अंतरभूत पूर्णांक is_ab8500_2p0_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab8500(ab) && (ab->chip_id <= AB8500_CUT2P0));
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8500_3p3_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab8500(ab) && (ab->chip_id <= AB8500_CUT3P3));
पूर्ण

/* exclude also ab8505, ab9540... */
अटल अंतरभूत पूर्णांक is_ab8500_2p0(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab8500(ab) && (ab->chip_id == AB8500_CUT2P0));
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8505_1p0_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab8505(ab) && (ab->chip_id <= AB8500_CUT1P0));
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8505_2p0(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab8505(ab) && (ab->chip_id == AB8500_CUT2P0));
पूर्ण

अटल अंतरभूत पूर्णांक is_ab9540_1p0_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab9540(ab) && (ab->chip_id <= AB8500_CUT1P0));
पूर्ण

अटल अंतरभूत पूर्णांक is_ab9540_2p0(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab9540(ab) && (ab->chip_id == AB8500_CUT2P0));
पूर्ण

/*
 * Be careful, the marketing name क्रम this chip is 2.1
 * but the value पढ़ो from the chip is 3.0 (0x30)
 */
अटल अंतरभूत पूर्णांक is_ab9540_3p0(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab9540(ab) && (ab->chip_id == AB8500_CUT3P0));
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8540_1p0_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस is_ab8540(ab) && (ab->chip_id <= AB8500_CUT1P0);
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8540_1p1_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस is_ab8540(ab) && (ab->chip_id <= AB8500_CUT1P1);
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8540_1p2_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस is_ab8540(ab) && (ab->chip_id <= AB8500_CUT1P2);
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8540_2p0_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस is_ab8540(ab) && (ab->chip_id <= AB8500_CUT2P0);
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8540_2p0(काष्ठा ab8500 *ab)
अणु
	वापस is_ab8540(ab) && (ab->chip_id == AB8500_CUT2P0);
पूर्ण

अटल अंतरभूत पूर्णांक is_ab8505_2p0_earlier(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab8505(ab) && (ab->chip_id < AB8500_CUT2P0));
पूर्ण

अटल अंतरभूत पूर्णांक is_ab9540_2p0_or_earlier(काष्ठा ab8500 *ab)
अणु
	वापस (is_ab9540(ab) && (ab->chip_id < AB8500_CUT2P0));
पूर्ण

व्योम ab8500_override_turn_on_stat(u8 mask, u8 set);

#अगर_घोषित CONFIG_AB8500_DEBUG
बाह्य पूर्णांक prcmu_abb_पढ़ो(u8 slave, u8 reg, u8 *value, u8 size);
व्योम ab8500_dump_all_banks(काष्ठा device *dev);
व्योम ab8500_debug_रेजिस्टर_पूर्णांकerrupt(पूर्णांक line);
#अन्यथा
अटल अंतरभूत व्योम ab8500_dump_all_banks(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम ab8500_debug_रेजिस्टर_पूर्णांकerrupt(पूर्णांक line) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* MFD_AB8500_H */
