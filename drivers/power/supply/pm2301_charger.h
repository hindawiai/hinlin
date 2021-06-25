<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * PM2301 घातer supply पूर्णांकerface
 */

#अगर_अघोषित PM2301_CHARGER_H
#घोषणा PM2301_CHARGER_H

/* Watchकरोg समयout स्थिरant */
#घोषणा WD_TIMER			0x30 /* 4min */
#घोषणा WD_KICK_INTERVAL		(30 * HZ)

#घोषणा PM2XXX_NUM_INT_REG		0x6

/* Constant voltage/current */
#घोषणा PM2XXX_CONST_CURR		0x0
#घोषणा PM2XXX_CONST_VOLT		0x1

/* Lowest अक्षरger voltage is 3.39V -> 0x4E */
#घोषणा LOW_VOLT_REG			0x4E

#घोषणा PM2XXX_BATT_CTRL_REG1		0x00
#घोषणा PM2XXX_BATT_CTRL_REG2		0x01
#घोषणा PM2XXX_BATT_CTRL_REG3		0x02
#घोषणा PM2XXX_BATT_CTRL_REG4		0x03
#घोषणा PM2XXX_BATT_CTRL_REG5		0x04
#घोषणा PM2XXX_BATT_CTRL_REG6		0x05
#घोषणा PM2XXX_BATT_CTRL_REG7		0x06
#घोषणा PM2XXX_BATT_CTRL_REG8		0x07
#घोषणा PM2XXX_NTC_CTRL_REG1		0x08
#घोषणा PM2XXX_NTC_CTRL_REG2		0x09
#घोषणा PM2XXX_BATT_CTRL_REG9		0x0A
#घोषणा PM2XXX_BATT_STAT_REG1		0x0B
#घोषणा PM2XXX_INP_VOLT_VPWR2		0x11
#घोषणा PM2XXX_INP_DROP_VPWR2		0x13
#घोषणा PM2XXX_INP_VOLT_VPWR1		0x15
#घोषणा PM2XXX_INP_DROP_VPWR1		0x17
#घोषणा PM2XXX_INP_MODE_VPWR		0x18
#घोषणा PM2XXX_BATT_WD_KICK		0x70
#घोषणा PM2XXX_DEV_VER_STAT		0x0C
#घोषणा PM2XXX_THERM_WARN_CTRL_REG	0x20
#घोषणा PM2XXX_BATT_DISC_REG		0x21
#घोषणा PM2XXX_BATT_LOW_LEV_COMP_REG	0x22
#घोषणा PM2XXX_BATT_LOW_LEV_VAL_REG	0x23
#घोषणा PM2XXX_I2C_PAD_CTRL_REG		0x24
#घोषणा PM2XXX_SW_CTRL_REG		0x26
#घोषणा PM2XXX_LED_CTRL_REG		0x28

#घोषणा PM2XXX_REG_INT1			0x40
#घोषणा PM2XXX_MASK_REG_INT1		0x50
#घोषणा PM2XXX_SRCE_REG_INT1		0x60
#घोषणा PM2XXX_REG_INT2			0x41
#घोषणा PM2XXX_MASK_REG_INT2		0x51
#घोषणा PM2XXX_SRCE_REG_INT2		0x61
#घोषणा PM2XXX_REG_INT3			0x42
#घोषणा PM2XXX_MASK_REG_INT3		0x52
#घोषणा PM2XXX_SRCE_REG_INT3		0x62
#घोषणा PM2XXX_REG_INT4			0x43
#घोषणा PM2XXX_MASK_REG_INT4		0x53
#घोषणा PM2XXX_SRCE_REG_INT4		0x63
#घोषणा PM2XXX_REG_INT5			0x44
#घोषणा PM2XXX_MASK_REG_INT5		0x54
#घोषणा PM2XXX_SRCE_REG_INT5		0x64
#घोषणा PM2XXX_REG_INT6			0x45
#घोषणा PM2XXX_MASK_REG_INT6		0x55
#घोषणा PM2XXX_SRCE_REG_INT6		0x65

#घोषणा VPWR_OVV			0x0
#घोषणा VSYSTEM_OVV			0x1

/* control Reg 1 */
#घोषणा PM2XXX_CH_RESUME_EN		0x1
#घोषणा PM2XXX_CH_RESUME_DIS		0x0

/* control Reg 2 */
#घोषणा PM2XXX_CH_AUTO_RESUME_EN	0X2
#घोषणा PM2XXX_CH_AUTO_RESUME_DIS	0X0
#घोषणा PM2XXX_CHARGER_ENA		0x4
#घोषणा PM2XXX_CHARGER_DIS		0x0

/* control Reg 3 */
#घोषणा PM2XXX_CH_WD_CC_PHASE_OFF	0x0
#घोषणा PM2XXX_CH_WD_CC_PHASE_5MIN	0x1
#घोषणा PM2XXX_CH_WD_CC_PHASE_10MIN	0x2
#घोषणा PM2XXX_CH_WD_CC_PHASE_30MIN	0x3
#घोषणा PM2XXX_CH_WD_CC_PHASE_60MIN	0x4
#घोषणा PM2XXX_CH_WD_CC_PHASE_120MIN	0x5
#घोषणा PM2XXX_CH_WD_CC_PHASE_240MIN	0x6
#घोषणा PM2XXX_CH_WD_CC_PHASE_360MIN	0x7

#घोषणा PM2XXX_CH_WD_CV_PHASE_OFF	(0x0<<3)
#घोषणा PM2XXX_CH_WD_CV_PHASE_5MIN	(0x1<<3)
#घोषणा PM2XXX_CH_WD_CV_PHASE_10MIN	(0x2<<3)
#घोषणा PM2XXX_CH_WD_CV_PHASE_30MIN	(0x3<<3)
#घोषणा PM2XXX_CH_WD_CV_PHASE_60MIN	(0x4<<3)
#घोषणा PM2XXX_CH_WD_CV_PHASE_120MIN	(0x5<<3)
#घोषणा PM2XXX_CH_WD_CV_PHASE_240MIN	(0x6<<3)
#घोषणा PM2XXX_CH_WD_CV_PHASE_360MIN	(0x7<<3)

/* control Reg 4 */
#घोषणा PM2XXX_CH_WD_PRECH_PHASE_OFF	0x0
#घोषणा PM2XXX_CH_WD_PRECH_PHASE_1MIN	0x1
#घोषणा PM2XXX_CH_WD_PRECH_PHASE_5MIN	0x2
#घोषणा PM2XXX_CH_WD_PRECH_PHASE_10MIN	0x3
#घोषणा PM2XXX_CH_WD_PRECH_PHASE_30MIN	0x4
#घोषणा PM2XXX_CH_WD_PRECH_PHASE_60MIN	0x5
#घोषणा PM2XXX_CH_WD_PRECH_PHASE_120MIN	0x6
#घोषणा PM2XXX_CH_WD_PRECH_PHASE_240MIN	0x7

/* control Reg 5 */
#घोषणा PM2XXX_CH_WD_AUTO_TIMEOUT_NONE	0x0
#घोषणा PM2XXX_CH_WD_AUTO_TIMEOUT_20MIN	0x1

/* control Reg 6 */
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_MASK	0x0F
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_200MA	0x0
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_400MA	0x2
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_600MA	0x3
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_800MA	0x4
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_1000MA	0x5
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_1200MA	0x6
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_1400MA	0x7
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_1600MA	0x8
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_1800MA	0x9
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_2000MA	0xA
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_2200MA	0xB
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_2400MA	0xC
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_2600MA	0xD
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_2800MA	0xE
#घोषणा PM2XXX_सूची_CH_CC_CURRENT_3000MA	0xF

#घोषणा PM2XXX_CH_PRECH_CURRENT_MASK	0x30
#घोषणा PM2XXX_CH_PRECH_CURRENT_25MA	(0x0<<4)
#घोषणा PM2XXX_CH_PRECH_CURRENT_50MA	(0x1<<4)
#घोषणा PM2XXX_CH_PRECH_CURRENT_75MA	(0x2<<4)
#घोषणा PM2XXX_CH_PRECH_CURRENT_100MA	(0x3<<4)

#घोषणा PM2XXX_CH_EOC_CURRENT_MASK	0xC0
#घोषणा PM2XXX_CH_EOC_CURRENT_100MA	(0x0<<6)
#घोषणा PM2XXX_CH_EOC_CURRENT_150MA	(0x1<<6)
#घोषणा PM2XXX_CH_EOC_CURRENT_300MA	(0x2<<6)
#घोषणा PM2XXX_CH_EOC_CURRENT_400MA	(0x3<<6)

/* control Reg 7 */
#घोषणा PM2XXX_CH_PRECH_VOL_2_5		0x0
#घोषणा PM2XXX_CH_PRECH_VOL_2_7		0x1
#घोषणा PM2XXX_CH_PRECH_VOL_2_9		0x2
#घोषणा PM2XXX_CH_PRECH_VOL_3_1		0x3

#घोषणा PM2XXX_CH_VRESUME_VOL_3_2	(0x0<<2)
#घोषणा PM2XXX_CH_VRESUME_VOL_3_4	(0x1<<2)
#घोषणा PM2XXX_CH_VRESUME_VOL_3_6	(0x2<<2)
#घोषणा PM2XXX_CH_VRESUME_VOL_3_8	(0x3<<2)

/* control Reg 8 */
#घोषणा PM2XXX_CH_VOLT_MASK		0x3F
#घोषणा PM2XXX_CH_VOLT_3_5		0x0
#घोषणा PM2XXX_CH_VOLT_3_5225		0x1
#घोषणा PM2XXX_CH_VOLT_3_6		0x4
#घोषणा PM2XXX_CH_VOLT_3_7		0x8
#घोषणा PM2XXX_CH_VOLT_4_0		0x14
#घोषणा PM2XXX_CH_VOLT_4_175		0x1B
#घोषणा PM2XXX_CH_VOLT_4_2		0x1C
#घोषणा PM2XXX_CH_VOLT_4_275		0x1F
#घोषणा PM2XXX_CH_VOLT_4_3		0x20

/*NTC control रेजिस्टर 1*/
#घोषणा PM2XXX_BTEMP_HIGH_TH_45		0x0
#घोषणा PM2XXX_BTEMP_HIGH_TH_50		0x1
#घोषणा PM2XXX_BTEMP_HIGH_TH_55		0x2
#घोषणा PM2XXX_BTEMP_HIGH_TH_60		0x3
#घोषणा PM2XXX_BTEMP_HIGH_TH_65		0x4

#घोषणा PM2XXX_BTEMP_LOW_TH_N5		(0x0<<3)
#घोषणा PM2XXX_BTEMP_LOW_TH_0		(0x1<<3)
#घोषणा PM2XXX_BTEMP_LOW_TH_5		(0x2<<3)
#घोषणा PM2XXX_BTEMP_LOW_TH_10		(0x3<<3)

/*NTC control रेजिस्टर 2*/
#घोषणा PM2XXX_NTC_BETA_COEFF_3477	0x0
#घोषणा PM2XXX_NTC_BETA_COEFF_3964	0x1

#घोषणा PM2XXX_NTC_RES_10K		(0x0<<2)
#घोषणा PM2XXX_NTC_RES_47K		(0x1<<2)
#घोषणा PM2XXX_NTC_RES_100K		(0x2<<2)
#घोषणा PM2XXX_NTC_RES_NO_NTC		(0x3<<2)

/* control Reg 9 */
#घोषणा PM2XXX_CH_CC_MODEDROP_EN	1
#घोषणा PM2XXX_CH_CC_MODEDROP_DIS	0

#घोषणा PM2XXX_CH_CC_REDUCED_CURRENT_100MA	(0x0<<1)
#घोषणा PM2XXX_CH_CC_REDUCED_CURRENT_200MA	(0x1<<1)
#घोषणा PM2XXX_CH_CC_REDUCED_CURRENT_400MA	(0x2<<1)
#घोषणा PM2XXX_CH_CC_REDUCED_CURRENT_IDENT	(0x3<<1)

#घोषणा PM2XXX_CHARCHING_INFO_DIS	(0<<3)
#घोषणा PM2XXX_CHARCHING_INFO_EN	(1<<3)

#घोषणा PM2XXX_CH_150MV_DROP_300MV	(0<<4)
#घोषणा PM2XXX_CH_150MV_DROP_150MV	(1<<4)


/* अक्षरger status रेजिस्टर */
#घोषणा PM2XXX_CHG_STATUS_OFF		0x0
#घोषणा PM2XXX_CHG_STATUS_ON		0x1
#घोषणा PM2XXX_CHG_STATUS_FULL		0x2
#घोषणा PM2XXX_CHG_STATUS_ERR		0x3
#घोषणा PM2XXX_CHG_STATUS_WAIT		0x4
#घोषणा PM2XXX_CHG_STATUS_NOBAT		0x5

/* Input अक्षरger voltage VPWR2 */
#घोषणा PM2XXX_VPWR2_OVV_6_0		0x0
#घोषणा PM2XXX_VPWR2_OVV_6_3		0x1
#घोषणा PM2XXX_VPWR2_OVV_10		0x2
#घोषणा PM2XXX_VPWR2_OVV_NONE		0x3

/* Input अक्षरger drop VPWR2 */
#घोषणा PM2XXX_VPWR2_HW_OPT_EN		(0x1<<4)
#घोषणा PM2XXX_VPWR2_HW_OPT_DIS		(0x0<<4)

#घोषणा PM2XXX_VPWR2_VALID_EN		(0x1<<3)
#घोषणा PM2XXX_VPWR2_VALID_DIS		(0x0<<3)

#घोषणा PM2XXX_VPWR2_DROP_EN		(0x1<<2)
#घोषणा PM2XXX_VPWR2_DROP_DIS		(0x0<<2)

/* Input अक्षरger voltage VPWR1 */
#घोषणा PM2XXX_VPWR1_OVV_6_0		0x0
#घोषणा PM2XXX_VPWR1_OVV_6_3		0x1
#घोषणा PM2XXX_VPWR1_OVV_10		0x2
#घोषणा PM2XXX_VPWR1_OVV_NONE		0x3

/* Input अक्षरger drop VPWR1 */
#घोषणा PM2XXX_VPWR1_HW_OPT_EN		(0x1<<4)
#घोषणा PM2XXX_VPWR1_HW_OPT_DIS		(0x0<<4)

#घोषणा PM2XXX_VPWR1_VALID_EN		(0x1<<3)
#घोषणा PM2XXX_VPWR1_VALID_DIS		(0x0<<3)

#घोषणा PM2XXX_VPWR1_DROP_EN		(0x1<<2)
#घोषणा PM2XXX_VPWR1_DROP_DIS		(0x0<<2)

/* Battery low level comparator control रेजिस्टर */
#घोषणा PM2XXX_VBAT_LOW_MONITORING_DIS	0x0
#घोषणा PM2XXX_VBAT_LOW_MONITORING_ENA	0x1

/* Battery low level value control रेजिस्टर */
#घोषणा PM2XXX_VBAT_LOW_LEVEL_2_3	0x0
#घोषणा PM2XXX_VBAT_LOW_LEVEL_2_4	0x1
#घोषणा PM2XXX_VBAT_LOW_LEVEL_2_5	0x2
#घोषणा PM2XXX_VBAT_LOW_LEVEL_2_6	0x3
#घोषणा PM2XXX_VBAT_LOW_LEVEL_2_7	0x4
#घोषणा PM2XXX_VBAT_LOW_LEVEL_2_8	0x5
#घोषणा PM2XXX_VBAT_LOW_LEVEL_2_9	0x6
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_0	0x7
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_1	0x8
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_2	0x9
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_3	0xA
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_4	0xB
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_5	0xC
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_6	0xD
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_7	0xE
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_8	0xF
#घोषणा PM2XXX_VBAT_LOW_LEVEL_3_9	0x10
#घोषणा PM2XXX_VBAT_LOW_LEVEL_4_0	0x11
#घोषणा PM2XXX_VBAT_LOW_LEVEL_4_1	0x12
#घोषणा PM2XXX_VBAT_LOW_LEVEL_4_2	0x13

/* SW CTRL */
#घोषणा PM2XXX_SWCTRL_HW		0x0
#घोषणा PM2XXX_SWCTRL_SW		0x1


/* LED Driver Control */
#घोषणा PM2XXX_LED_CURRENT_MASK		0x0C
#घोषणा PM2XXX_LED_CURRENT_2_5MA	(0X0<<2)
#घोषणा PM2XXX_LED_CURRENT_1MA		(0X1<<2)
#घोषणा PM2XXX_LED_CURRENT_5MA		(0X2<<2)
#घोषणा PM2XXX_LED_CURRENT_10MA		(0X3<<2)

#घोषणा PM2XXX_LED_SELECT_MASK		0x02
#घोषणा PM2XXX_LED_SELECT_EN		(0X0<<1)
#घोषणा PM2XXX_LED_SELECT_DIS		(0X1<<1)

#घोषणा PM2XXX_ANTI_OVERSHOOT_MASK	0x01
#घोषणा PM2XXX_ANTI_OVERSHOOT_DIS	0X0
#घोषणा PM2XXX_ANTI_OVERSHOOT_EN	0X1

क्रमागत pm2xxx_reg_पूर्णांक1 अणु
	PM2XXX_INT1_ITVBATDISCONNECT	= 0x02,
	PM2XXX_INT1_ITVBATLOWR		= 0x04,
	PM2XXX_INT1_ITVBATLOWF		= 0x08,
पूर्ण;

क्रमागत pm2xxx_mask_reg_पूर्णांक1 अणु
	PM2XXX_INT1_M_ITVBATDISCONNECT	= 0x02,
	PM2XXX_INT1_M_ITVBATLOWR	= 0x04,
	PM2XXX_INT1_M_ITVBATLOWF	= 0x08,
पूर्ण;

क्रमागत pm2xxx_source_reg_पूर्णांक1 अणु
	PM2XXX_INT1_S_ITVBATDISCONNECT	= 0x02,
	PM2XXX_INT1_S_ITVBATLOWR	= 0x04,
	PM2XXX_INT1_S_ITVBATLOWF	= 0x08,
पूर्ण;

क्रमागत pm2xxx_reg_पूर्णांक2 अणु
	PM2XXX_INT2_ITVPWR2PLUG		= 0x01,
	PM2XXX_INT2_ITVPWR2UNPLUG	= 0x02,
	PM2XXX_INT2_ITVPWR1PLUG		= 0x04,
	PM2XXX_INT2_ITVPWR1UNPLUG	= 0x08,
पूर्ण;

क्रमागत pm2xxx_mask_reg_पूर्णांक2 अणु
	PM2XXX_INT2_M_ITVPWR2PLUG	= 0x01,
	PM2XXX_INT2_M_ITVPWR2UNPLUG	= 0x02,
	PM2XXX_INT2_M_ITVPWR1PLUG	= 0x04,
	PM2XXX_INT2_M_ITVPWR1UNPLUG	= 0x08,
पूर्ण;

क्रमागत pm2xxx_source_reg_पूर्णांक2 अणु
	PM2XXX_INT2_S_ITVPWR2PLUG	= 0x03,
	PM2XXX_INT2_S_ITVPWR1PLUG	= 0x0c,
पूर्ण;

क्रमागत pm2xxx_reg_पूर्णांक3 अणु
	PM2XXX_INT3_ITCHPRECHARGEWD	= 0x01,
	PM2XXX_INT3_ITCHCCWD		= 0x02,
	PM2XXX_INT3_ITCHCVWD		= 0x04,
	PM2XXX_INT3_ITAUTOTIMEOUTWD	= 0x08,
पूर्ण;

क्रमागत pm2xxx_mask_reg_पूर्णांक3 अणु
	PM2XXX_INT3_M_ITCHPRECHARGEWD	= 0x01,
	PM2XXX_INT3_M_ITCHCCWD		= 0x02,
	PM2XXX_INT3_M_ITCHCVWD		= 0x04,
	PM2XXX_INT3_M_ITAUTOTIMEOUTWD	= 0x08,
पूर्ण;

क्रमागत pm2xxx_source_reg_पूर्णांक3 अणु
	PM2XXX_INT3_S_ITCHPRECHARGEWD	= 0x01,
	PM2XXX_INT3_S_ITCHCCWD		= 0x02,
	PM2XXX_INT3_S_ITCHCVWD		= 0x04,
	PM2XXX_INT3_S_ITAUTOTIMEOUTWD	= 0x08,
पूर्ण;

क्रमागत pm2xxx_reg_पूर्णांक4 अणु
	PM2XXX_INT4_ITBATTEMPCOLD	= 0x01,
	PM2XXX_INT4_ITBATTEMPHOT	= 0x02,
	PM2XXX_INT4_ITVPWR2OVV		= 0x04,
	PM2XXX_INT4_ITVPWR1OVV		= 0x08,
	PM2XXX_INT4_ITCHARGINGON	= 0x10,
	PM2XXX_INT4_ITVRESUME		= 0x20,
	PM2XXX_INT4_ITBATTFULL		= 0x40,
	PM2XXX_INT4_ITCVPHASE		= 0x80,
पूर्ण;

क्रमागत pm2xxx_mask_reg_पूर्णांक4 अणु
	PM2XXX_INT4_M_ITBATTEMPCOLD	= 0x01,
	PM2XXX_INT4_M_ITBATTEMPHOT	= 0x02,
	PM2XXX_INT4_M_ITVPWR2OVV	= 0x04,
	PM2XXX_INT4_M_ITVPWR1OVV	= 0x08,
	PM2XXX_INT4_M_ITCHARGINGON	= 0x10,
	PM2XXX_INT4_M_ITVRESUME		= 0x20,
	PM2XXX_INT4_M_ITBATTFULL	= 0x40,
	PM2XXX_INT4_M_ITCVPHASE		= 0x80,
पूर्ण;

क्रमागत pm2xxx_source_reg_पूर्णांक4 अणु
	PM2XXX_INT4_S_ITBATTEMPCOLD	= 0x01,
	PM2XXX_INT4_S_ITBATTEMPHOT	= 0x02,
	PM2XXX_INT4_S_ITVPWR2OVV	= 0x04,
	PM2XXX_INT4_S_ITVPWR1OVV	= 0x08,
	PM2XXX_INT4_S_ITCHARGINGON	= 0x10,
	PM2XXX_INT4_S_ITVRESUME		= 0x20,
	PM2XXX_INT4_S_ITBATTFULL	= 0x40,
	PM2XXX_INT4_S_ITCVPHASE		= 0x80,
पूर्ण;

क्रमागत pm2xxx_reg_पूर्णांक5 अणु
	PM2XXX_INT5_ITTHERMALSHUTDOWNRISE	= 0x01,
	PM2XXX_INT5_ITTHERMALSHUTDOWNFALL	= 0x02,
	PM2XXX_INT5_ITTHERMALWARNINGRISE	= 0x04,
	PM2XXX_INT5_ITTHERMALWARNINGFALL	= 0x08,
	PM2XXX_INT5_ITVSYSTEMOVV		= 0x10,
पूर्ण;

क्रमागत pm2xxx_mask_reg_पूर्णांक5 अणु
	PM2XXX_INT5_M_ITTHERMALSHUTDOWNRISE	= 0x01,
	PM2XXX_INT5_M_ITTHERMALSHUTDOWNFALL	= 0x02,
	PM2XXX_INT5_M_ITTHERMALWARNINGRISE	= 0x04,
	PM2XXX_INT5_M_ITTHERMALWARNINGFALL	= 0x08,
	PM2XXX_INT5_M_ITVSYSTEMOVV		= 0x10,
पूर्ण;

क्रमागत pm2xxx_source_reg_पूर्णांक5 अणु
	PM2XXX_INT5_S_ITTHERMALSHUTDOWNRISE	= 0x01,
	PM2XXX_INT5_S_ITTHERMALSHUTDOWNFALL	= 0x02,
	PM2XXX_INT5_S_ITTHERMALWARNINGRISE	= 0x04,
	PM2XXX_INT5_S_ITTHERMALWARNINGFALL	= 0x08,
	PM2XXX_INT5_S_ITVSYSTEMOVV		= 0x10,
पूर्ण;

क्रमागत pm2xxx_reg_पूर्णांक6 अणु
	PM2XXX_INT6_ITVPWR2DROP		= 0x01,
	PM2XXX_INT6_ITVPWR1DROP		= 0x02,
	PM2XXX_INT6_ITVPWR2VALIDRISE	= 0x04,
	PM2XXX_INT6_ITVPWR2VALIDFALL	= 0x08,
	PM2XXX_INT6_ITVPWR1VALIDRISE	= 0x10,
	PM2XXX_INT6_ITVPWR1VALIDFALL	= 0x20,
पूर्ण;

क्रमागत pm2xxx_mask_reg_पूर्णांक6 अणु
	PM2XXX_INT6_M_ITVPWR2DROP	= 0x01,
	PM2XXX_INT6_M_ITVPWR1DROP	= 0x02,
	PM2XXX_INT6_M_ITVPWR2VALIDRISE	= 0x04,
	PM2XXX_INT6_M_ITVPWR2VALIDFALL	= 0x08,
	PM2XXX_INT6_M_ITVPWR1VALIDRISE	= 0x10,
	PM2XXX_INT6_M_ITVPWR1VALIDFALL	= 0x20,
पूर्ण;

क्रमागत pm2xxx_source_reg_पूर्णांक6 अणु
	PM2XXX_INT6_S_ITVPWR2DROP	= 0x01,
	PM2XXX_INT6_S_ITVPWR1DROP	= 0x02,
	PM2XXX_INT6_S_ITVPWR2VALIDRISE	= 0x04,
	PM2XXX_INT6_S_ITVPWR2VALIDFALL	= 0x08,
	PM2XXX_INT6_S_ITVPWR1VALIDRISE	= 0x10,
	PM2XXX_INT6_S_ITVPWR1VALIDFALL	= 0x20,
पूर्ण;

काष्ठा pm2xxx_अक्षरger_info अणु
	पूर्णांक अक्षरger_connected;
	पूर्णांक अक्षरger_online;
	पूर्णांक cv_active;
	bool wd_expired;
पूर्ण;

काष्ठा pm2xxx_अक्षरger_event_flags अणु
	bool मुख्यextchnotok;
	bool मुख्य_thermal_prot;
	bool ovv;
	bool chgwdexp;
पूर्ण;

काष्ठा pm2xxx_पूर्णांकerrupts अणु
	u8 reg[PM2XXX_NUM_INT_REG];
	पूर्णांक (*handler[PM2XXX_NUM_INT_REG])(व्योम *, पूर्णांक);
पूर्ण;

काष्ठा pm2xxx_config अणु
	काष्ठा i2c_client *pm2xxx_i2c;
	काष्ठा i2c_device_id *pm2xxx_id;
पूर्ण;

काष्ठा pm2xxx_irq अणु
	अक्षर *name;
	irqवापस_t (*isr)(पूर्णांक irq, व्योम *data);
पूर्ण;

काष्ठा pm2xxx_अक्षरger अणु
	काष्ठा device *dev;
	u8 chip_id;
	bool vddadc_en_ac;
	काष्ठा pm2xxx_config config;
	bool ac_conn;
	अचिन्हित पूर्णांक gpio_irq;
	पूर्णांक vbat;
	पूर्णांक old_vbat;
	पूर्णांक failure_हाल;
	पूर्णांक failure_input_ovv;
	अचिन्हित पूर्णांक lpn_pin;
	काष्ठा pm2xxx_पूर्णांकerrupts *pm2_पूर्णांक;
	काष्ठा regulator *regu;
	काष्ठा pm2xxx_bm_data *bat;
	काष्ठा mutex lock;
	काष्ठा ab8500 *parent;
	काष्ठा pm2xxx_अक्षरger_info ac;
	काष्ठा pm2xxx_अक्षरger_platक्रमm_data *pdata;
	काष्ठा workqueue_काष्ठा *अक्षरger_wq;
	काष्ठा delayed_work check_vbat_work;
	काष्ठा work_काष्ठा ac_work;
	काष्ठा work_काष्ठा check_मुख्य_thermal_prot_work;
	काष्ठा delayed_work check_hw_failure_work;
	काष्ठा ux500_अक्षरger ac_chg;
	काष्ठा घातer_supply_desc ac_chg_desc;
	काष्ठा pm2xxx_अक्षरger_event_flags flags;
पूर्ण;

#पूर्ण_अगर /* PM2301_CHARGER_H */
