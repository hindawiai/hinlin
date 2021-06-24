<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * tps65910.h  --  TI TPS6591x
 *
 * Copyright 2010-2011 Texas Instruments Inc.
 *
 * Author: Graeme Gregory <gg@slimlogic.co.uk>
 * Author: Jorge Eduarकरो Candelaria <jedu@slimlogic.co.uk>
 * Author: Arnaud Deconinck <a-deconinck@ti.com>
 */

#अगर_अघोषित __LINUX_MFD_TPS65910_H
#घोषणा __LINUX_MFD_TPS65910_H

#समावेश <linux/gpपन.स>
#समावेश <linux/regmap.h>

/* TPS chip id list */
#घोषणा TPS65910			0
#घोषणा TPS65911			1

/* TPS regulator type list */
#घोषणा REGULATOR_LDO			0
#घोषणा REGULATOR_DCDC			1

/*
 * List of रेजिस्टरs क्रम component TPS65910
 *
 */

#घोषणा TPS65910_SECONDS				0x0
#घोषणा TPS65910_MINUTES				0x1
#घोषणा TPS65910_HOURS					0x2
#घोषणा TPS65910_DAYS					0x3
#घोषणा TPS65910_MONTHS					0x4
#घोषणा TPS65910_YEARS					0x5
#घोषणा TPS65910_WEEKS					0x6
#घोषणा TPS65910_ALARM_SECONDS				0x8
#घोषणा TPS65910_ALARM_MINUTES				0x9
#घोषणा TPS65910_ALARM_HOURS				0xA
#घोषणा TPS65910_ALARM_DAYS				0xB
#घोषणा TPS65910_ALARM_MONTHS				0xC
#घोषणा TPS65910_ALARM_YEARS				0xD
#घोषणा TPS65910_RTC_CTRL				0x10
#घोषणा TPS65910_RTC_STATUS				0x11
#घोषणा TPS65910_RTC_INTERRUPTS				0x12
#घोषणा TPS65910_RTC_COMP_LSB				0x13
#घोषणा TPS65910_RTC_COMP_MSB				0x14
#घोषणा TPS65910_RTC_RES_PROG				0x15
#घोषणा TPS65910_RTC_RESET_STATUS			0x16
#घोषणा TPS65910_BCK1					0x17
#घोषणा TPS65910_BCK2					0x18
#घोषणा TPS65910_BCK3					0x19
#घोषणा TPS65910_BCK4					0x1A
#घोषणा TPS65910_BCK5					0x1B
#घोषणा TPS65910_PUADEN					0x1C
#घोषणा TPS65910_REF					0x1D
#घोषणा TPS65910_VRTC					0x1E
#घोषणा TPS65910_VIO					0x20
#घोषणा TPS65910_VDD1					0x21
#घोषणा TPS65910_VDD1_OP				0x22
#घोषणा TPS65910_VDD1_SR				0x23
#घोषणा TPS65910_VDD2					0x24
#घोषणा TPS65910_VDD2_OP				0x25
#घोषणा TPS65910_VDD2_SR				0x26
#घोषणा TPS65910_VDD3					0x27
#घोषणा TPS65910_VDIG1					0x30
#घोषणा TPS65910_VDIG2					0x31
#घोषणा TPS65910_VAUX1					0x32
#घोषणा TPS65910_VAUX2					0x33
#घोषणा TPS65910_VAUX33					0x34
#घोषणा TPS65910_VMMC					0x35
#घोषणा TPS65910_VPLL					0x36
#घोषणा TPS65910_VDAC					0x37
#घोषणा TPS65910_THERM					0x38
#घोषणा TPS65910_BBCH					0x39
#घोषणा TPS65910_DCDCCTRL				0x3E
#घोषणा TPS65910_DEVCTRL				0x3F
#घोषणा TPS65910_DEVCTRL2				0x40
#घोषणा TPS65910_SLEEP_KEEP_LDO_ON			0x41
#घोषणा TPS65910_SLEEP_KEEP_RES_ON			0x42
#घोषणा TPS65910_SLEEP_SET_LDO_OFF			0x43
#घोषणा TPS65910_SLEEP_SET_RES_OFF			0x44
#घोषणा TPS65910_EN1_LDO_ASS				0x45
#घोषणा TPS65910_EN1_SMPS_ASS				0x46
#घोषणा TPS65910_EN2_LDO_ASS				0x47
#घोषणा TPS65910_EN2_SMPS_ASS				0x48
#घोषणा TPS65910_EN3_LDO_ASS				0x49
#घोषणा TPS65910_SPARE					0x4A
#घोषणा TPS65910_INT_STS				0x50
#घोषणा TPS65910_INT_MSK				0x51
#घोषणा TPS65910_INT_STS2				0x52
#घोषणा TPS65910_INT_MSK2				0x53
#घोषणा TPS65910_INT_STS3				0x54
#घोषणा TPS65910_INT_MSK3				0x55
#घोषणा TPS65910_GPIO0					0x60
#घोषणा TPS65910_GPIO1					0x61
#घोषणा TPS65910_GPIO2					0x62
#घोषणा TPS65910_GPIO3					0x63
#घोषणा TPS65910_GPIO4					0x64
#घोषणा TPS65910_GPIO5					0x65
#घोषणा TPS65910_GPIO6					0x66
#घोषणा TPS65910_GPIO7					0x67
#घोषणा TPS65910_GPIO8					0x68
#घोषणा TPS65910_JTAGVERNUM				0x80
#घोषणा TPS65910_MAX_REGISTER				0x80

/*
 * List of रेजिस्टरs specअगरic to TPS65911
 */
#घोषणा TPS65911_VDDCTRL				0x27
#घोषणा TPS65911_VDDCTRL_OP				0x28
#घोषणा TPS65911_VDDCTRL_SR				0x29
#घोषणा TPS65911_LDO1					0x30
#घोषणा TPS65911_LDO2					0x31
#घोषणा TPS65911_LDO5					0x32
#घोषणा TPS65911_LDO8					0x33
#घोषणा TPS65911_LDO7					0x34
#घोषणा TPS65911_LDO6					0x35
#घोषणा TPS65911_LDO4					0x36
#घोषणा TPS65911_LDO3					0x37
#घोषणा TPS65911_VMBCH					0x6A
#घोषणा TPS65911_VMBCH2					0x6B

/*
 * List of रेजिस्टर bitfields क्रम component TPS65910
 *
 */

/* RTC_CTRL_REG bitfields */
#घोषणा TPS65910_RTC_CTRL_STOP_RTC			0x01 /*0=stop, 1=run */
#घोषणा TPS65910_RTC_CTRL_AUTO_COMP			0x04
#घोषणा TPS65910_RTC_CTRL_GET_TIME			0x40

/* RTC_STATUS_REG bitfields */
#घोषणा TPS65910_RTC_STATUS_ALARM               0x40

/* RTC_INTERRUPTS_REG bitfields */
#घोषणा TPS65910_RTC_INTERRUPTS_EVERY           0x03
#घोषणा TPS65910_RTC_INTERRUPTS_IT_ALARM        0x08

/*Register BCK1  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा BCK1_BCKUP_MASK					0xFF
#घोषणा BCK1_BCKUP_SHIFT				0


/*Register BCK2  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा BCK2_BCKUP_MASK					0xFF
#घोषणा BCK2_BCKUP_SHIFT				0


/*Register BCK3  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा BCK3_BCKUP_MASK					0xFF
#घोषणा BCK3_BCKUP_SHIFT				0


/*Register BCK4  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा BCK4_BCKUP_MASK					0xFF
#घोषणा BCK4_BCKUP_SHIFT				0


/*Register BCK5  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा BCK5_BCKUP_MASK					0xFF
#घोषणा BCK5_BCKUP_SHIFT				0


/*Register PUADEN  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा PUADEN_EN3P_MASK				0x80
#घोषणा PUADEN_EN3P_SHIFT				7
#घोषणा PUADEN_I2CCTLP_MASK				0x40
#घोषणा PUADEN_I2CCTLP_SHIFT				6
#घोषणा PUADEN_I2CSRP_MASK				0x20
#घोषणा PUADEN_I2CSRP_SHIFT				5
#घोषणा PUADEN_PWRONP_MASK				0x10
#घोषणा PUADEN_PWRONP_SHIFT				4
#घोषणा PUADEN_SLEEPP_MASK				0x08
#घोषणा PUADEN_SLEEPP_SHIFT				3
#घोषणा PUADEN_PWRHOLDP_MASK				0x04
#घोषणा PUADEN_PWRHOLDP_SHIFT				2
#घोषणा PUADEN_BOOT1P_MASK				0x02
#घोषणा PUADEN_BOOT1P_SHIFT				1
#घोषणा PUADEN_BOOT0P_MASK				0x01
#घोषणा PUADEN_BOOT0P_SHIFT				0


/*Register REF	(0x80) रेजिस्टर.RegisterDescription */
#घोषणा REF_VMBCH_SEL_MASK				0x0C
#घोषणा REF_VMBCH_SEL_SHIFT				2
#घोषणा REF_ST_MASK					0x03
#घोषणा REF_ST_SHIFT					0


/*Register VRTC  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VRTC_VRTC_OFFMASK_MASK				0x08
#घोषणा VRTC_VRTC_OFFMASK_SHIFT				3
#घोषणा VRTC_ST_MASK					0x03
#घोषणा VRTC_ST_SHIFT					0


/*Register VIO	(0x80) रेजिस्टर.RegisterDescription */
#घोषणा VIO_ILMAX_MASK					0xC0
#घोषणा VIO_ILMAX_SHIFT					6
#घोषणा VIO_SEL_MASK					0x0C
#घोषणा VIO_SEL_SHIFT					2
#घोषणा VIO_ST_MASK					0x03
#घोषणा VIO_ST_SHIFT					0


/*Register VDD1  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDD1_VGAIN_SEL_MASK				0xC0
#घोषणा VDD1_VGAIN_SEL_SHIFT				6
#घोषणा VDD1_ILMAX_MASK					0x20
#घोषणा VDD1_ILMAX_SHIFT				5
#घोषणा VDD1_TSTEP_MASK					0x1C
#घोषणा VDD1_TSTEP_SHIFT				2
#घोषणा VDD1_ST_MASK					0x03
#घोषणा VDD1_ST_SHIFT					0


/*Register VDD1_OP  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDD1_OP_CMD_MASK				0x80
#घोषणा VDD1_OP_CMD_SHIFT				7
#घोषणा VDD1_OP_SEL_MASK				0x7F
#घोषणा VDD1_OP_SEL_SHIFT				0


/*Register VDD1_SR  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDD1_SR_SEL_MASK				0x7F
#घोषणा VDD1_SR_SEL_SHIFT				0


/*Register VDD2  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDD2_VGAIN_SEL_MASK				0xC0
#घोषणा VDD2_VGAIN_SEL_SHIFT				6
#घोषणा VDD2_ILMAX_MASK					0x20
#घोषणा VDD2_ILMAX_SHIFT				5
#घोषणा VDD2_TSTEP_MASK					0x1C
#घोषणा VDD2_TSTEP_SHIFT				2
#घोषणा VDD2_ST_MASK					0x03
#घोषणा VDD2_ST_SHIFT					0


/*Register VDD2_OP  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDD2_OP_CMD_MASK				0x80
#घोषणा VDD2_OP_CMD_SHIFT				7
#घोषणा VDD2_OP_SEL_MASK				0x7F
#घोषणा VDD2_OP_SEL_SHIFT				0

/*Register VDD2_SR  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDD2_SR_SEL_MASK				0x7F
#घोषणा VDD2_SR_SEL_SHIFT				0


/*Registers VDD1, VDD2 voltage values definitions */
#घोषणा VDD1_2_NUM_VOLT_FINE				73
#घोषणा VDD1_2_NUM_VOLT_COARSE				3
#घोषणा VDD1_2_MIN_VOLT					6000
#घोषणा VDD1_2_OFFSET					125


/*Register VDD3  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDD3_CKINEN_MASK				0x04
#घोषणा VDD3_CKINEN_SHIFT				2
#घोषणा VDD3_ST_MASK					0x03
#घोषणा VDD3_ST_SHIFT					0
#घोषणा VDDCTRL_MIN_VOLT				6000
#घोषणा VDDCTRL_OFFSET					125

/*Registers VDIG (0x80) to VDAC रेजिस्टर.RegisterDescription */
#घोषणा LDO_SEL_MASK					0x0C
#घोषणा LDO_SEL_SHIFT					2
#घोषणा LDO_ST_MASK					0x03
#घोषणा LDO_ST_SHIFT					0
#घोषणा LDO_ST_ON_BIT					0x01
#घोषणा LDO_ST_MODE_BIT					0x02	


/* Registers LDO1 to LDO8 in tps65910 */
#घोषणा LDO1_SEL_MASK					0xFC
#घोषणा LDO3_SEL_MASK					0x7C
#घोषणा LDO_MIN_VOLT					1000
#घोषणा LDO_MAX_VOLT					3300


/*Register VDIG1  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDIG1_SEL_MASK					0x0C
#घोषणा VDIG1_SEL_SHIFT					2
#घोषणा VDIG1_ST_MASK					0x03
#घोषणा VDIG1_ST_SHIFT					0


/*Register VDIG2  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDIG2_SEL_MASK					0x0C
#घोषणा VDIG2_SEL_SHIFT					2
#घोषणा VDIG2_ST_MASK					0x03
#घोषणा VDIG2_ST_SHIFT					0


/*Register VAUX1  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VAUX1_SEL_MASK					0x0C
#घोषणा VAUX1_SEL_SHIFT					2
#घोषणा VAUX1_ST_MASK					0x03
#घोषणा VAUX1_ST_SHIFT					0


/*Register VAUX2  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VAUX2_SEL_MASK					0x0C
#घोषणा VAUX2_SEL_SHIFT					2
#घोषणा VAUX2_ST_MASK					0x03
#घोषणा VAUX2_ST_SHIFT					0


/*Register VAUX33  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VAUX33_SEL_MASK					0x0C
#घोषणा VAUX33_SEL_SHIFT				2
#घोषणा VAUX33_ST_MASK					0x03
#घोषणा VAUX33_ST_SHIFT					0


/*Register VMMC  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VMMC_SEL_MASK					0x0C
#घोषणा VMMC_SEL_SHIFT					2
#घोषणा VMMC_ST_MASK					0x03
#घोषणा VMMC_ST_SHIFT					0


/*Register VPLL  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VPLL_SEL_MASK					0x0C
#घोषणा VPLL_SEL_SHIFT					2
#घोषणा VPLL_ST_MASK					0x03
#घोषणा VPLL_ST_SHIFT					0


/*Register VDAC  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा VDAC_SEL_MASK					0x0C
#घोषणा VDAC_SEL_SHIFT					2
#घोषणा VDAC_ST_MASK					0x03
#घोषणा VDAC_ST_SHIFT					0


/*Register THERM  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा THERM_THERM_HD_MASK				0x20
#घोषणा THERM_THERM_HD_SHIFT				5
#घोषणा THERM_THERM_TS_MASK				0x10
#घोषणा THERM_THERM_TS_SHIFT				4
#घोषणा THERM_THERM_HDSEL_MASK				0x0C
#घोषणा THERM_THERM_HDSEL_SHIFT				2
#घोषणा THERM_RSVD1_MASK				0x02
#घोषणा THERM_RSVD1_SHIFT				1
#घोषणा THERM_THERM_STATE_MASK				0x01
#घोषणा THERM_THERM_STATE_SHIFT				0


/*Register BBCH  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा BBCH_BBSEL_MASK					0x06
#घोषणा BBCH_BBSEL_SHIFT				1


/*Register DCDCCTRL  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा DCDCCTRL_VDD2_PSKIP_MASK			0x20
#घोषणा DCDCCTRL_VDD2_PSKIP_SHIFT			5
#घोषणा DCDCCTRL_VDD1_PSKIP_MASK			0x10
#घोषणा DCDCCTRL_VDD1_PSKIP_SHIFT			4
#घोषणा DCDCCTRL_VIO_PSKIP_MASK				0x08
#घोषणा DCDCCTRL_VIO_PSKIP_SHIFT			3
#घोषणा DCDCCTRL_DCDCCKEXT_MASK				0x04
#घोषणा DCDCCTRL_DCDCCKEXT_SHIFT			2
#घोषणा DCDCCTRL_DCDCCKSYNC_MASK			0x03
#घोषणा DCDCCTRL_DCDCCKSYNC_SHIFT			0


/*Register DEVCTRL  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा DEVCTRL_PWR_OFF_MASK				0x80
#घोषणा DEVCTRL_PWR_OFF_SHIFT				7
#घोषणा DEVCTRL_RTC_PWDN_MASK				0x40
#घोषणा DEVCTRL_RTC_PWDN_SHIFT				6
#घोषणा DEVCTRL_CK32K_CTRL_MASK				0x20
#घोषणा DEVCTRL_CK32K_CTRL_SHIFT			5
#घोषणा DEVCTRL_SR_CTL_I2C_SEL_MASK			0x10
#घोषणा DEVCTRL_SR_CTL_I2C_SEL_SHIFT			4
#घोषणा DEVCTRL_DEV_OFF_RST_MASK			0x08
#घोषणा DEVCTRL_DEV_OFF_RST_SHIFT			3
#घोषणा DEVCTRL_DEV_ON_MASK				0x04
#घोषणा DEVCTRL_DEV_ON_SHIFT				2
#घोषणा DEVCTRL_DEV_SLP_MASK				0x02
#घोषणा DEVCTRL_DEV_SLP_SHIFT				1
#घोषणा DEVCTRL_DEV_OFF_MASK				0x01
#घोषणा DEVCTRL_DEV_OFF_SHIFT				0


/*Register DEVCTRL2  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा DEVCTRL2_TSLOT_LENGTH_MASK			0x30
#घोषणा DEVCTRL2_TSLOT_LENGTH_SHIFT			4
#घोषणा DEVCTRL2_SLEEPSIG_POL_MASK			0x08
#घोषणा DEVCTRL2_SLEEPSIG_POL_SHIFT			3
#घोषणा DEVCTRL2_PWON_LP_OFF_MASK			0x04
#घोषणा DEVCTRL2_PWON_LP_OFF_SHIFT			2
#घोषणा DEVCTRL2_PWON_LP_RST_MASK			0x02
#घोषणा DEVCTRL2_PWON_LP_RST_SHIFT			1
#घोषणा DEVCTRL2_IT_POL_MASK				0x01
#घोषणा DEVCTRL2_IT_POL_SHIFT				0


/*Register SLEEP_KEEP_LDO_ON  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा SLEEP_KEEP_LDO_ON_VDAC_KEEPON_MASK		0x80
#घोषणा SLEEP_KEEP_LDO_ON_VDAC_KEEPON_SHIFT		7
#घोषणा SLEEP_KEEP_LDO_ON_VPLL_KEEPON_MASK		0x40
#घोषणा SLEEP_KEEP_LDO_ON_VPLL_KEEPON_SHIFT		6
#घोषणा SLEEP_KEEP_LDO_ON_VAUX33_KEEPON_MASK		0x20
#घोषणा SLEEP_KEEP_LDO_ON_VAUX33_KEEPON_SHIFT		5
#घोषणा SLEEP_KEEP_LDO_ON_VAUX2_KEEPON_MASK		0x10
#घोषणा SLEEP_KEEP_LDO_ON_VAUX2_KEEPON_SHIFT		4
#घोषणा SLEEP_KEEP_LDO_ON_VAUX1_KEEPON_MASK		0x08
#घोषणा SLEEP_KEEP_LDO_ON_VAUX1_KEEPON_SHIFT		3
#घोषणा SLEEP_KEEP_LDO_ON_VDIG2_KEEPON_MASK		0x04
#घोषणा SLEEP_KEEP_LDO_ON_VDIG2_KEEPON_SHIFT		2
#घोषणा SLEEP_KEEP_LDO_ON_VDIG1_KEEPON_MASK		0x02
#घोषणा SLEEP_KEEP_LDO_ON_VDIG1_KEEPON_SHIFT		1
#घोषणा SLEEP_KEEP_LDO_ON_VMMC_KEEPON_MASK		0x01
#घोषणा SLEEP_KEEP_LDO_ON_VMMC_KEEPON_SHIFT		0


/*Register SLEEP_KEEP_RES_ON  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा SLEEP_KEEP_RES_ON_THERM_KEEPON_MASK		0x80
#घोषणा SLEEP_KEEP_RES_ON_THERM_KEEPON_SHIFT		7
#घोषणा SLEEP_KEEP_RES_ON_CLKOUT32K_KEEPON_MASK		0x40
#घोषणा SLEEP_KEEP_RES_ON_CLKOUT32K_KEEPON_SHIFT	6
#घोषणा SLEEP_KEEP_RES_ON_VRTC_KEEPON_MASK		0x20
#घोषणा SLEEP_KEEP_RES_ON_VRTC_KEEPON_SHIFT		5
#घोषणा SLEEP_KEEP_RES_ON_I2CHS_KEEPON_MASK		0x10
#घोषणा SLEEP_KEEP_RES_ON_I2CHS_KEEPON_SHIFT		4
#घोषणा SLEEP_KEEP_RES_ON_VDD3_KEEPON_MASK		0x08
#घोषणा SLEEP_KEEP_RES_ON_VDD3_KEEPON_SHIFT		3
#घोषणा SLEEP_KEEP_RES_ON_VDD2_KEEPON_MASK		0x04
#घोषणा SLEEP_KEEP_RES_ON_VDD2_KEEPON_SHIFT		2
#घोषणा SLEEP_KEEP_RES_ON_VDD1_KEEPON_MASK		0x02
#घोषणा SLEEP_KEEP_RES_ON_VDD1_KEEPON_SHIFT		1
#घोषणा SLEEP_KEEP_RES_ON_VIO_KEEPON_MASK		0x01
#घोषणा SLEEP_KEEP_RES_ON_VIO_KEEPON_SHIFT		0


/*Register SLEEP_SET_LDO_OFF  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा SLEEP_SET_LDO_OFF_VDAC_SETOFF_MASK		0x80
#घोषणा SLEEP_SET_LDO_OFF_VDAC_SETOFF_SHIFT		7
#घोषणा SLEEP_SET_LDO_OFF_VPLL_SETOFF_MASK		0x40
#घोषणा SLEEP_SET_LDO_OFF_VPLL_SETOFF_SHIFT		6
#घोषणा SLEEP_SET_LDO_OFF_VAUX33_SETOFF_MASK		0x20
#घोषणा SLEEP_SET_LDO_OFF_VAUX33_SETOFF_SHIFT		5
#घोषणा SLEEP_SET_LDO_OFF_VAUX2_SETOFF_MASK		0x10
#घोषणा SLEEP_SET_LDO_OFF_VAUX2_SETOFF_SHIFT		4
#घोषणा SLEEP_SET_LDO_OFF_VAUX1_SETOFF_MASK		0x08
#घोषणा SLEEP_SET_LDO_OFF_VAUX1_SETOFF_SHIFT		3
#घोषणा SLEEP_SET_LDO_OFF_VDIG2_SETOFF_MASK		0x04
#घोषणा SLEEP_SET_LDO_OFF_VDIG2_SETOFF_SHIFT		2
#घोषणा SLEEP_SET_LDO_OFF_VDIG1_SETOFF_MASK		0x02
#घोषणा SLEEP_SET_LDO_OFF_VDIG1_SETOFF_SHIFT		1
#घोषणा SLEEP_SET_LDO_OFF_VMMC_SETOFF_MASK		0x01
#घोषणा SLEEP_SET_LDO_OFF_VMMC_SETOFF_SHIFT		0


/*Register SLEEP_SET_RES_OFF  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा SLEEP_SET_RES_OFF_DEFAULT_VOLT_MASK		0x80
#घोषणा SLEEP_SET_RES_OFF_DEFAULT_VOLT_SHIFT		7
#घोषणा SLEEP_SET_RES_OFF_RSVD_MASK			0x60
#घोषणा SLEEP_SET_RES_OFF_RSVD_SHIFT			5
#घोषणा SLEEP_SET_RES_OFF_SPARE_SETOFF_MASK		0x10
#घोषणा SLEEP_SET_RES_OFF_SPARE_SETOFF_SHIFT		4
#घोषणा SLEEP_SET_RES_OFF_VDD3_SETOFF_MASK		0x08
#घोषणा SLEEP_SET_RES_OFF_VDD3_SETOFF_SHIFT		3
#घोषणा SLEEP_SET_RES_OFF_VDD2_SETOFF_MASK		0x04
#घोषणा SLEEP_SET_RES_OFF_VDD2_SETOFF_SHIFT		2
#घोषणा SLEEP_SET_RES_OFF_VDD1_SETOFF_MASK		0x02
#घोषणा SLEEP_SET_RES_OFF_VDD1_SETOFF_SHIFT		1
#घोषणा SLEEP_SET_RES_OFF_VIO_SETOFF_MASK		0x01
#घोषणा SLEEP_SET_RES_OFF_VIO_SETOFF_SHIFT		0


/*Register EN1_LDO_ASS	(0x80) रेजिस्टर.RegisterDescription */
#घोषणा EN1_LDO_ASS_VDAC_EN1_MASK			0x80
#घोषणा EN1_LDO_ASS_VDAC_EN1_SHIFT			7
#घोषणा EN1_LDO_ASS_VPLL_EN1_MASK			0x40
#घोषणा EN1_LDO_ASS_VPLL_EN1_SHIFT			6
#घोषणा EN1_LDO_ASS_VAUX33_EN1_MASK			0x20
#घोषणा EN1_LDO_ASS_VAUX33_EN1_SHIFT			5
#घोषणा EN1_LDO_ASS_VAUX2_EN1_MASK			0x10
#घोषणा EN1_LDO_ASS_VAUX2_EN1_SHIFT			4
#घोषणा EN1_LDO_ASS_VAUX1_EN1_MASK			0x08
#घोषणा EN1_LDO_ASS_VAUX1_EN1_SHIFT			3
#घोषणा EN1_LDO_ASS_VDIG2_EN1_MASK			0x04
#घोषणा EN1_LDO_ASS_VDIG2_EN1_SHIFT			2
#घोषणा EN1_LDO_ASS_VDIG1_EN1_MASK			0x02
#घोषणा EN1_LDO_ASS_VDIG1_EN1_SHIFT			1
#घोषणा EN1_LDO_ASS_VMMC_EN1_MASK			0x01
#घोषणा EN1_LDO_ASS_VMMC_EN1_SHIFT			0


/*Register EN1_SMPS_ASS  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा EN1_SMPS_ASS_RSVD_MASK				0xE0
#घोषणा EN1_SMPS_ASS_RSVD_SHIFT				5
#घोषणा EN1_SMPS_ASS_SPARE_EN1_MASK			0x10
#घोषणा EN1_SMPS_ASS_SPARE_EN1_SHIFT			4
#घोषणा EN1_SMPS_ASS_VDD3_EN1_MASK			0x08
#घोषणा EN1_SMPS_ASS_VDD3_EN1_SHIFT			3
#घोषणा EN1_SMPS_ASS_VDD2_EN1_MASK			0x04
#घोषणा EN1_SMPS_ASS_VDD2_EN1_SHIFT			2
#घोषणा EN1_SMPS_ASS_VDD1_EN1_MASK			0x02
#घोषणा EN1_SMPS_ASS_VDD1_EN1_SHIFT			1
#घोषणा EN1_SMPS_ASS_VIO_EN1_MASK			0x01
#घोषणा EN1_SMPS_ASS_VIO_EN1_SHIFT			0


/*Register EN2_LDO_ASS	(0x80) रेजिस्टर.RegisterDescription */
#घोषणा EN2_LDO_ASS_VDAC_EN2_MASK			0x80
#घोषणा EN2_LDO_ASS_VDAC_EN2_SHIFT			7
#घोषणा EN2_LDO_ASS_VPLL_EN2_MASK			0x40
#घोषणा EN2_LDO_ASS_VPLL_EN2_SHIFT			6
#घोषणा EN2_LDO_ASS_VAUX33_EN2_MASK			0x20
#घोषणा EN2_LDO_ASS_VAUX33_EN2_SHIFT			5
#घोषणा EN2_LDO_ASS_VAUX2_EN2_MASK			0x10
#घोषणा EN2_LDO_ASS_VAUX2_EN2_SHIFT			4
#घोषणा EN2_LDO_ASS_VAUX1_EN2_MASK			0x08
#घोषणा EN2_LDO_ASS_VAUX1_EN2_SHIFT			3
#घोषणा EN2_LDO_ASS_VDIG2_EN2_MASK			0x04
#घोषणा EN2_LDO_ASS_VDIG2_EN2_SHIFT			2
#घोषणा EN2_LDO_ASS_VDIG1_EN2_MASK			0x02
#घोषणा EN2_LDO_ASS_VDIG1_EN2_SHIFT			1
#घोषणा EN2_LDO_ASS_VMMC_EN2_MASK			0x01
#घोषणा EN2_LDO_ASS_VMMC_EN2_SHIFT			0


/*Register EN2_SMPS_ASS  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा EN2_SMPS_ASS_RSVD_MASK				0xE0
#घोषणा EN2_SMPS_ASS_RSVD_SHIFT				5
#घोषणा EN2_SMPS_ASS_SPARE_EN2_MASK			0x10
#घोषणा EN2_SMPS_ASS_SPARE_EN2_SHIFT			4
#घोषणा EN2_SMPS_ASS_VDD3_EN2_MASK			0x08
#घोषणा EN2_SMPS_ASS_VDD3_EN2_SHIFT			3
#घोषणा EN2_SMPS_ASS_VDD2_EN2_MASK			0x04
#घोषणा EN2_SMPS_ASS_VDD2_EN2_SHIFT			2
#घोषणा EN2_SMPS_ASS_VDD1_EN2_MASK			0x02
#घोषणा EN2_SMPS_ASS_VDD1_EN2_SHIFT			1
#घोषणा EN2_SMPS_ASS_VIO_EN2_MASK			0x01
#घोषणा EN2_SMPS_ASS_VIO_EN2_SHIFT			0


/*Register EN3_LDO_ASS	(0x80) रेजिस्टर.RegisterDescription */
#घोषणा EN3_LDO_ASS_VDAC_EN3_MASK			0x80
#घोषणा EN3_LDO_ASS_VDAC_EN3_SHIFT			7
#घोषणा EN3_LDO_ASS_VPLL_EN3_MASK			0x40
#घोषणा EN3_LDO_ASS_VPLL_EN3_SHIFT			6
#घोषणा EN3_LDO_ASS_VAUX33_EN3_MASK			0x20
#घोषणा EN3_LDO_ASS_VAUX33_EN3_SHIFT			5
#घोषणा EN3_LDO_ASS_VAUX2_EN3_MASK			0x10
#घोषणा EN3_LDO_ASS_VAUX2_EN3_SHIFT			4
#घोषणा EN3_LDO_ASS_VAUX1_EN3_MASK			0x08
#घोषणा EN3_LDO_ASS_VAUX1_EN3_SHIFT			3
#घोषणा EN3_LDO_ASS_VDIG2_EN3_MASK			0x04
#घोषणा EN3_LDO_ASS_VDIG2_EN3_SHIFT			2
#घोषणा EN3_LDO_ASS_VDIG1_EN3_MASK			0x02
#घोषणा EN3_LDO_ASS_VDIG1_EN3_SHIFT			1
#घोषणा EN3_LDO_ASS_VMMC_EN3_MASK			0x01
#घोषणा EN3_LDO_ASS_VMMC_EN3_SHIFT			0


/*Register SPARE  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा SPARE_SPARE_MASK				0xFF
#घोषणा SPARE_SPARE_SHIFT				0

#घोषणा TPS65910_INT_STS_RTC_PERIOD_IT_MASK			0x80
#घोषणा TPS65910_INT_STS_RTC_PERIOD_IT_SHIFT			7
#घोषणा TPS65910_INT_STS_RTC_ALARM_IT_MASK			0x40
#घोषणा TPS65910_INT_STS_RTC_ALARM_IT_SHIFT			6
#घोषणा TPS65910_INT_STS_HOTDIE_IT_MASK				0x20
#घोषणा TPS65910_INT_STS_HOTDIE_IT_SHIFT			5
#घोषणा TPS65910_INT_STS_PWRHOLD_F_IT_MASK			0x10
#घोषणा TPS65910_INT_STS_PWRHOLD_F_IT_SHIFT			4
#घोषणा TPS65910_INT_STS_PWRON_LP_IT_MASK			0x08
#घोषणा TPS65910_INT_STS_PWRON_LP_IT_SHIFT			3
#घोषणा TPS65910_INT_STS_PWRON_IT_MASK				0x04
#घोषणा TPS65910_INT_STS_PWRON_IT_SHIFT				2
#घोषणा TPS65910_INT_STS_VMBHI_IT_MASK				0x02
#घोषणा TPS65910_INT_STS_VMBHI_IT_SHIFT				1
#घोषणा TPS65910_INT_STS_VMBDCH_IT_MASK				0x01
#घोषणा TPS65910_INT_STS_VMBDCH_IT_SHIFT			0

#घोषणा TPS65910_INT_MSK_RTC_PERIOD_IT_MSK_MASK			0x80
#घोषणा TPS65910_INT_MSK_RTC_PERIOD_IT_MSK_SHIFT		7
#घोषणा TPS65910_INT_MSK_RTC_ALARM_IT_MSK_MASK			0x40
#घोषणा TPS65910_INT_MSK_RTC_ALARM_IT_MSK_SHIFT			6
#घोषणा TPS65910_INT_MSK_HOTDIE_IT_MSK_MASK			0x20
#घोषणा TPS65910_INT_MSK_HOTDIE_IT_MSK_SHIFT			5
#घोषणा TPS65910_INT_MSK_PWRHOLD_IT_MSK_MASK			0x10
#घोषणा TPS65910_INT_MSK_PWRHOLD_IT_MSK_SHIFT			4
#घोषणा TPS65910_INT_MSK_PWRON_LP_IT_MSK_MASK			0x08
#घोषणा TPS65910_INT_MSK_PWRON_LP_IT_MSK_SHIFT			3
#घोषणा TPS65910_INT_MSK_PWRON_IT_MSK_MASK			0x04
#घोषणा TPS65910_INT_MSK_PWRON_IT_MSK_SHIFT			2
#घोषणा TPS65910_INT_MSK_VMBHI_IT_MSK_MASK			0x02
#घोषणा TPS65910_INT_MSK_VMBHI_IT_MSK_SHIFT			1
#घोषणा TPS65910_INT_MSK_VMBDCH_IT_MSK_MASK			0x01
#घोषणा TPS65910_INT_MSK_VMBDCH_IT_MSK_SHIFT			0

#घोषणा TPS65910_INT_STS2_GPIO0_F_IT_SHIFT			2
#घोषणा TPS65910_INT_STS2_GPIO0_F_IT_MASK			0x02
#घोषणा TPS65910_INT_STS2_GPIO0_R_IT_SHIFT			1
#घोषणा TPS65910_INT_STS2_GPIO0_R_IT_MASK			0x01

#घोषणा TPS65910_INT_MSK2_GPIO0_F_IT_MSK_SHIFT			2
#घोषणा TPS65910_INT_MSK2_GPIO0_F_IT_MSK_MASK			0x02
#घोषणा TPS65910_INT_MSK2_GPIO0_R_IT_MSK_SHIFT			1
#घोषणा TPS65910_INT_MSK2_GPIO0_R_IT_MSK_MASK			0x01

/*Register INT_STS  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा INT_STS_RTC_PERIOD_IT_MASK			0x80
#घोषणा INT_STS_RTC_PERIOD_IT_SHIFT			7
#घोषणा INT_STS_RTC_ALARM_IT_MASK			0x40
#घोषणा INT_STS_RTC_ALARM_IT_SHIFT			6
#घोषणा INT_STS_HOTDIE_IT_MASK				0x20
#घोषणा INT_STS_HOTDIE_IT_SHIFT				5
#घोषणा INT_STS_PWRHOLD_R_IT_MASK			0x10
#घोषणा INT_STS_PWRHOLD_R_IT_SHIFT			4
#घोषणा INT_STS_PWRON_LP_IT_MASK			0x08
#घोषणा INT_STS_PWRON_LP_IT_SHIFT			3
#घोषणा INT_STS_PWRON_IT_MASK				0x04
#घोषणा INT_STS_PWRON_IT_SHIFT				2
#घोषणा INT_STS_VMBHI_IT_MASK				0x02
#घोषणा INT_STS_VMBHI_IT_SHIFT				1
#घोषणा INT_STS_PWRHOLD_F_IT_MASK			0x01
#घोषणा INT_STS_PWRHOLD_F_IT_SHIFT			0


/*Register INT_MSK  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा INT_MSK_RTC_PERIOD_IT_MSK_MASK			0x80
#घोषणा INT_MSK_RTC_PERIOD_IT_MSK_SHIFT			7
#घोषणा INT_MSK_RTC_ALARM_IT_MSK_MASK			0x40
#घोषणा INT_MSK_RTC_ALARM_IT_MSK_SHIFT			6
#घोषणा INT_MSK_HOTDIE_IT_MSK_MASK			0x20
#घोषणा INT_MSK_HOTDIE_IT_MSK_SHIFT			5
#घोषणा INT_MSK_PWRHOLD_R_IT_MSK_MASK			0x10
#घोषणा INT_MSK_PWRHOLD_R_IT_MSK_SHIFT			4
#घोषणा INT_MSK_PWRON_LP_IT_MSK_MASK			0x08
#घोषणा INT_MSK_PWRON_LP_IT_MSK_SHIFT			3
#घोषणा INT_MSK_PWRON_IT_MSK_MASK			0x04
#घोषणा INT_MSK_PWRON_IT_MSK_SHIFT			2
#घोषणा INT_MSK_VMBHI_IT_MSK_MASK			0x02
#घोषणा INT_MSK_VMBHI_IT_MSK_SHIFT			1
#घोषणा INT_MSK_PWRHOLD_F_IT_MSK_MASK			0x01
#घोषणा INT_MSK_PWRHOLD_F_IT_MSK_SHIFT			0


/*Register INT_STS2  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा INT_STS2_GPIO3_F_IT_MASK			0x80
#घोषणा INT_STS2_GPIO3_F_IT_SHIFT			7
#घोषणा INT_STS2_GPIO3_R_IT_MASK			0x40
#घोषणा INT_STS2_GPIO3_R_IT_SHIFT			6
#घोषणा INT_STS2_GPIO2_F_IT_MASK			0x20
#घोषणा INT_STS2_GPIO2_F_IT_SHIFT			5
#घोषणा INT_STS2_GPIO2_R_IT_MASK			0x10
#घोषणा INT_STS2_GPIO2_R_IT_SHIFT			4
#घोषणा INT_STS2_GPIO1_F_IT_MASK			0x08
#घोषणा INT_STS2_GPIO1_F_IT_SHIFT			3
#घोषणा INT_STS2_GPIO1_R_IT_MASK			0x04
#घोषणा INT_STS2_GPIO1_R_IT_SHIFT			2
#घोषणा INT_STS2_GPIO0_F_IT_MASK			0x02
#घोषणा INT_STS2_GPIO0_F_IT_SHIFT			1
#घोषणा INT_STS2_GPIO0_R_IT_MASK			0x01
#घोषणा INT_STS2_GPIO0_R_IT_SHIFT			0


/*Register INT_MSK2  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा INT_MSK2_GPIO3_F_IT_MSK_MASK			0x80
#घोषणा INT_MSK2_GPIO3_F_IT_MSK_SHIFT			7
#घोषणा INT_MSK2_GPIO3_R_IT_MSK_MASK			0x40
#घोषणा INT_MSK2_GPIO3_R_IT_MSK_SHIFT			6
#घोषणा INT_MSK2_GPIO2_F_IT_MSK_MASK			0x20
#घोषणा INT_MSK2_GPIO2_F_IT_MSK_SHIFT			5
#घोषणा INT_MSK2_GPIO2_R_IT_MSK_MASK			0x10
#घोषणा INT_MSK2_GPIO2_R_IT_MSK_SHIFT			4
#घोषणा INT_MSK2_GPIO1_F_IT_MSK_MASK			0x08
#घोषणा INT_MSK2_GPIO1_F_IT_MSK_SHIFT			3
#घोषणा INT_MSK2_GPIO1_R_IT_MSK_MASK			0x04
#घोषणा INT_MSK2_GPIO1_R_IT_MSK_SHIFT			2
#घोषणा INT_MSK2_GPIO0_F_IT_MSK_MASK			0x02
#घोषणा INT_MSK2_GPIO0_F_IT_MSK_SHIFT			1
#घोषणा INT_MSK2_GPIO0_R_IT_MSK_MASK			0x01
#घोषणा INT_MSK2_GPIO0_R_IT_MSK_SHIFT			0


/*Register INT_STS3  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा INT_STS3_PWRDN_IT_MASK				0x80
#घोषणा INT_STS3_PWRDN_IT_SHIFT				7
#घोषणा INT_STS3_VMBCH2_L_IT_MASK			0x40
#घोषणा INT_STS3_VMBCH2_L_IT_SHIFT			6
#घोषणा INT_STS3_VMBCH2_H_IT_MASK			0x20
#घोषणा INT_STS3_VMBCH2_H_IT_SHIFT			5
#घोषणा INT_STS3_WTCHDG_IT_MASK				0x10
#घोषणा INT_STS3_WTCHDG_IT_SHIFT			4
#घोषणा INT_STS3_GPIO5_F_IT_MASK			0x08
#घोषणा INT_STS3_GPIO5_F_IT_SHIFT			3
#घोषणा INT_STS3_GPIO5_R_IT_MASK			0x04
#घोषणा INT_STS3_GPIO5_R_IT_SHIFT			2
#घोषणा INT_STS3_GPIO4_F_IT_MASK			0x02
#घोषणा INT_STS3_GPIO4_F_IT_SHIFT			1
#घोषणा INT_STS3_GPIO4_R_IT_MASK			0x01
#घोषणा INT_STS3_GPIO4_R_IT_SHIFT			0


/*Register INT_MSK3  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा INT_MSK3_PWRDN_IT_MSK_MASK			0x80
#घोषणा INT_MSK3_PWRDN_IT_MSK_SHIFT			7
#घोषणा INT_MSK3_VMBCH2_L_IT_MSK_MASK			0x40
#घोषणा INT_MSK3_VMBCH2_L_IT_MSK_SHIFT			6
#घोषणा INT_MSK3_VMBCH2_H_IT_MSK_MASK			0x20
#घोषणा INT_MSK3_VMBCH2_H_IT_MSK_SHIFT			5
#घोषणा INT_MSK3_WTCHDG_IT_MSK_MASK			0x10
#घोषणा INT_MSK3_WTCHDG_IT_MSK_SHIFT			4
#घोषणा INT_MSK3_GPIO5_F_IT_MSK_MASK			0x08
#घोषणा INT_MSK3_GPIO5_F_IT_MSK_SHIFT			3
#घोषणा INT_MSK3_GPIO5_R_IT_MSK_MASK			0x04
#घोषणा INT_MSK3_GPIO5_R_IT_MSK_SHIFT			2
#घोषणा INT_MSK3_GPIO4_F_IT_MSK_MASK			0x02
#घोषणा INT_MSK3_GPIO4_F_IT_MSK_SHIFT			1
#घोषणा INT_MSK3_GPIO4_R_IT_MSK_MASK			0x01
#घोषणा INT_MSK3_GPIO4_R_IT_MSK_SHIFT			0


/*Register GPIO  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा GPIO_SLEEP_MASK                         0x80
#घोषणा GPIO_SLEEP_SHIFT                        7
#घोषणा GPIO_DEB_MASK                           0x10
#घोषणा GPIO_DEB_SHIFT                          4
#घोषणा GPIO_PUEN_MASK                          0x08
#घोषणा GPIO_PUEN_SHIFT                         3
#घोषणा GPIO_CFG_MASK                           0x04
#घोषणा GPIO_CFG_SHIFT                          2
#घोषणा GPIO_STS_MASK                           0x02
#घोषणा GPIO_STS_SHIFT                          1
#घोषणा GPIO_SET_MASK                           0x01
#घोषणा GPIO_SET_SHIFT                          0


/*Register JTAGVERNUM  (0x80) रेजिस्टर.RegisterDescription */
#घोषणा JTAGVERNUM_VERNUM_MASK				0x0F
#घोषणा JTAGVERNUM_VERNUM_SHIFT				0


/* Register VDDCTRL (0x27) bit definitions */
#घोषणा VDDCTRL_ST_MASK                                  0x03
#घोषणा VDDCTRL_ST_SHIFT                                 0


/*Register VDDCTRL_OP  (0x28) bit definitios */
#घोषणा VDDCTRL_OP_CMD_MASK                              0x80
#घोषणा VDDCTRL_OP_CMD_SHIFT                             7
#घोषणा VDDCTRL_OP_SEL_MASK                              0x7F
#घोषणा VDDCTRL_OP_SEL_SHIFT                             0


/*Register VDDCTRL_SR  (0x29) bit definitions */
#घोषणा VDDCTRL_SR_SEL_MASK                              0x7F
#घोषणा VDDCTRL_SR_SEL_SHIFT                             0


/* IRQ Definitions */
#घोषणा TPS65910_IRQ_VBAT_VMBDCH			0
#घोषणा TPS65910_IRQ_VBAT_VMHI				1
#घोषणा TPS65910_IRQ_PWRON				2
#घोषणा TPS65910_IRQ_PWRON_LP				3
#घोषणा TPS65910_IRQ_PWRHOLD				4
#घोषणा TPS65910_IRQ_HOTDIE				5
#घोषणा TPS65910_IRQ_RTC_ALARM				6
#घोषणा TPS65910_IRQ_RTC_PERIOD				7
#घोषणा TPS65910_IRQ_GPIO_R				8
#घोषणा TPS65910_IRQ_GPIO_F				9
#घोषणा TPS65910_NUM_IRQ				10

#घोषणा TPS65911_IRQ_PWRHOLD_F				0
#घोषणा TPS65911_IRQ_VBAT_VMHI				1
#घोषणा TPS65911_IRQ_PWRON				2
#घोषणा TPS65911_IRQ_PWRON_LP				3
#घोषणा TPS65911_IRQ_PWRHOLD_R				4
#घोषणा TPS65911_IRQ_HOTDIE				5
#घोषणा TPS65911_IRQ_RTC_ALARM				6
#घोषणा TPS65911_IRQ_RTC_PERIOD				7
#घोषणा TPS65911_IRQ_GPIO0_R				8
#घोषणा TPS65911_IRQ_GPIO0_F				9
#घोषणा TPS65911_IRQ_GPIO1_R				10
#घोषणा TPS65911_IRQ_GPIO1_F				11
#घोषणा TPS65911_IRQ_GPIO2_R				12
#घोषणा TPS65911_IRQ_GPIO2_F				13
#घोषणा TPS65911_IRQ_GPIO3_R				14
#घोषणा TPS65911_IRQ_GPIO3_F				15
#घोषणा TPS65911_IRQ_GPIO4_R				16
#घोषणा TPS65911_IRQ_GPIO4_F				17
#घोषणा TPS65911_IRQ_GPIO5_R				18
#घोषणा TPS65911_IRQ_GPIO5_F				19
#घोषणा TPS65911_IRQ_WTCHDG				20
#घोषणा TPS65911_IRQ_VMBCH2_H				21
#घोषणा TPS65911_IRQ_VMBCH2_L				22
#घोषणा TPS65911_IRQ_PWRDN				23

#घोषणा TPS65911_NUM_IRQ				24

/* GPIO Register Definitions */
#घोषणा TPS65910_GPIO_DEB				BIT(2)
#घोषणा TPS65910_GPIO_PUEN				BIT(3)
#घोषणा TPS65910_GPIO_CFG				BIT(2)
#घोषणा TPS65910_GPIO_STS				BIT(1)
#घोषणा TPS65910_GPIO_SET				BIT(0)

/* Max number of TPS65910/11 GPIOs */
#घोषणा TPS65910_NUM_GPIO				6
#घोषणा TPS65911_NUM_GPIO				9
#घोषणा TPS6591X_MAX_NUM_GPIO				9

/* Regulator Index Definitions */
#घोषणा TPS65910_REG_VRTC				0
#घोषणा TPS65910_REG_VIO				1
#घोषणा TPS65910_REG_VDD1				2
#घोषणा TPS65910_REG_VDD2				3
#घोषणा TPS65910_REG_VDD3				4
#घोषणा TPS65910_REG_VDIG1				5
#घोषणा TPS65910_REG_VDIG2				6
#घोषणा TPS65910_REG_VPLL				7
#घोषणा TPS65910_REG_VDAC				8
#घोषणा TPS65910_REG_VAUX1				9
#घोषणा TPS65910_REG_VAUX2				10
#घोषणा TPS65910_REG_VAUX33				11
#घोषणा TPS65910_REG_VMMC				12
#घोषणा TPS65910_REG_VBB				13

#घोषणा TPS65911_REG_VDDCTRL				4
#घोषणा TPS65911_REG_LDO1				5
#घोषणा TPS65911_REG_LDO2				6
#घोषणा TPS65911_REG_LDO3				7
#घोषणा TPS65911_REG_LDO4				8
#घोषणा TPS65911_REG_LDO5				9
#घोषणा TPS65911_REG_LDO6				10
#घोषणा TPS65911_REG_LDO7				11
#घोषणा TPS65911_REG_LDO8				12

/* Max number of TPS65910/11 regulators */
#घोषणा TPS65910_NUM_REGS				14

/* External sleep controls through EN1/EN2/EN3/SLEEP inमाला_दो */
#घोषणा TPS65910_SLEEP_CONTROL_EXT_INPUT_EN1		0x1
#घोषणा TPS65910_SLEEP_CONTROL_EXT_INPUT_EN2		0x2
#घोषणा TPS65910_SLEEP_CONTROL_EXT_INPUT_EN3		0x4
#घोषणा TPS65911_SLEEP_CONTROL_EXT_INPUT_SLEEP		0x8

/*
 * Sleep keepon data: Maपूर्णांकains the state in sleep mode
 * @therm_keepon: Keep on the thermal monitoring in sleep state.
 * @clkout32k_keepon: Keep on the 32KHz घड़ी output in sleep state.
 * @i2chs_keepon: Keep on high speed पूर्णांकernal घड़ी in sleep state.
 */
काष्ठा tps65910_sleep_keepon_data अणु
	अचिन्हित therm_keepon:1;
	अचिन्हित clkout32k_keepon:1;
	अचिन्हित i2chs_keepon:1;
पूर्ण;

/**
 * काष्ठा tps65910_board
 * Board platक्रमm data may be used to initialize regulators.
 */

काष्ठा tps65910_board अणु
	पूर्णांक gpio_base;
	पूर्णांक irq;
	पूर्णांक irq_base;
	पूर्णांक vmbch_threshold;
	पूर्णांक vmbch2_threshold;
	bool en_ck32k_xtal;
	bool en_dev_slp;
	bool pm_off;
	काष्ठा tps65910_sleep_keepon_data slp_keepon;
	bool en_gpio_sleep[TPS6591X_MAX_NUM_GPIO];
	अचिन्हित दीर्घ regulator_ext_sleep_control[TPS65910_NUM_REGS];
	काष्ठा regulator_init_data *tps65910_pmic_init_data[TPS65910_NUM_REGS];
पूर्ण;

/**
 * काष्ठा tps65910 - tps65910 sub-driver chip access routines
 */

काष्ठा tps65910 अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c_client;
	काष्ठा regmap *regmap;
	अचिन्हित दीर्घ id;

	/* Device node parsed board data */
	काष्ठा tps65910_board *of_plat_data;

	/* IRQ Handling */
	पूर्णांक chip_irq;
	काष्ठा regmap_irq_chip_data *irq_data;
पूर्ण;

काष्ठा tps65910_platक्रमm_data अणु
	पूर्णांक irq;
	पूर्णांक irq_base;
पूर्ण;

अटल अंतरभूत पूर्णांक tps65910_chip_id(काष्ठा tps65910 *tps65910)
अणु
	वापस tps65910->id;
पूर्ण

#पूर्ण_अगर /*  __LINUX_MFD_TPS65910_H */
