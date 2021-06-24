<शैली गुरु>
/*
 * tps80031.h -- TI TPS80031 and TI TPS80032 PMIC driver.
 *
 * Copyright (c) 2012, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#अगर_अघोषित __LINUX_MFD_TPS80031_H
#घोषणा __LINUX_MFD_TPS80031_H

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>

/* Pull-ups/Pull-करोwns */
#घोषणा TPS80031_CFG_INPUT_PUPD1			0xF0
#घोषणा TPS80031_CFG_INPUT_PUPD2			0xF1
#घोषणा TPS80031_CFG_INPUT_PUPD3			0xF2
#घोषणा TPS80031_CFG_INPUT_PUPD4			0xF3
#घोषणा TPS80031_CFG_LDO_PD1				0xF4
#घोषणा TPS80031_CFG_LDO_PD2				0xF5
#घोषणा TPS80031_CFG_SMPS_PD				0xF6

/* Real Time Clock */
#घोषणा TPS80031_SECONDS_REG				0x00
#घोषणा TPS80031_MINUTES_REG				0x01
#घोषणा TPS80031_HOURS_REG				0x02
#घोषणा TPS80031_DAYS_REG				0x03
#घोषणा TPS80031_MONTHS_REG				0x04
#घोषणा TPS80031_YEARS_REG				0x05
#घोषणा TPS80031_WEEKS_REG				0x06
#घोषणा TPS80031_ALARM_SECONDS_REG			0x08
#घोषणा TPS80031_ALARM_MINUTES_REG			0x09
#घोषणा TPS80031_ALARM_HOURS_REG			0x0A
#घोषणा TPS80031_ALARM_DAYS_REG				0x0B
#घोषणा TPS80031_ALARM_MONTHS_REG			0x0C
#घोषणा TPS80031_ALARM_YEARS_REG			0x0D
#घोषणा TPS80031_RTC_CTRL_REG				0x10
#घोषणा TPS80031_RTC_STATUS_REG				0x11
#घोषणा TPS80031_RTC_INTERRUPTS_REG			0x12
#घोषणा TPS80031_RTC_COMP_LSB_REG			0x13
#घोषणा TPS80031_RTC_COMP_MSB_REG			0x14
#घोषणा TPS80031_RTC_RESET_STATUS_REG			0x16

/*PMC Master Module */
#घोषणा TPS80031_PHOENIX_START_CONDITION		0x1F
#घोषणा TPS80031_PHOENIX_MSK_TRANSITION			0x20
#घोषणा TPS80031_STS_HW_CONDITIONS			0x21
#घोषणा TPS80031_PHOENIX_LAST_TURNOFF_STS		0x22
#घोषणा TPS80031_VSYSMIN_LO_THRESHOLD			0x23
#घोषणा TPS80031_VSYSMIN_HI_THRESHOLD			0x24
#घोषणा TPS80031_PHOENIX_DEV_ON				0x25
#घोषणा TPS80031_STS_PWR_GRP_STATE			0x27
#घोषणा TPS80031_PH_CFG_VSYSLOW				0x28
#घोषणा TPS80031_PH_STS_BOOT				0x29
#घोषणा TPS80031_PHOENIX_SENS_TRANSITION		0x2A
#घोषणा TPS80031_PHOENIX_SEQ_CFG			0x2B
#घोषणा TPS80031_PRIMARY_WATCHDOG_CFG			0X2C
#घोषणा TPS80031_KEY_PRESS_DUR_CFG			0X2D
#घोषणा TPS80031_SMPS_LDO_SHORT_STS			0x2E

/* PMC Slave Module - Broadcast */
#घोषणा TPS80031_BROADCAST_ADDR_ALL			0x31
#घोषणा TPS80031_BROADCAST_ADDR_REF			0x32
#घोषणा TPS80031_BROADCAST_ADDR_PROV			0x33
#घोषणा TPS80031_BROADCAST_ADDR_CLK_RST			0x34

/* PMC Slave Module  SMPS Regulators */
#घोषणा TPS80031_SMPS4_CFG_TRANS			0x41
#घोषणा TPS80031_SMPS4_CFG_STATE			0x42
#घोषणा TPS80031_SMPS4_CFG_VOLTAGE			0x44
#घोषणा TPS80031_VIO_CFG_TRANS				0x47
#घोषणा TPS80031_VIO_CFG_STATE				0x48
#घोषणा TPS80031_VIO_CFG_FORCE				0x49
#घोषणा TPS80031_VIO_CFG_VOLTAGE			0x4A
#घोषणा TPS80031_VIO_CFG_STEP				0x48
#घोषणा TPS80031_SMPS1_CFG_TRANS			0x53
#घोषणा TPS80031_SMPS1_CFG_STATE			0x54
#घोषणा TPS80031_SMPS1_CFG_FORCE			0x55
#घोषणा TPS80031_SMPS1_CFG_VOLTAGE			0x56
#घोषणा TPS80031_SMPS1_CFG_STEP				0x57
#घोषणा TPS80031_SMPS2_CFG_TRANS			0x59
#घोषणा TPS80031_SMPS2_CFG_STATE			0x5A
#घोषणा TPS80031_SMPS2_CFG_FORCE			0x5B
#घोषणा TPS80031_SMPS2_CFG_VOLTAGE			0x5C
#घोषणा TPS80031_SMPS2_CFG_STEP				0x5D
#घोषणा TPS80031_SMPS3_CFG_TRANS			0x65
#घोषणा TPS80031_SMPS3_CFG_STATE			0x66
#घोषणा TPS80031_SMPS3_CFG_VOLTAGE			0x68

/* PMC Slave Module  LDO Regulators */
#घोषणा TPS80031_VANA_CFG_TRANS				0x81
#घोषणा TPS80031_VANA_CFG_STATE				0x82
#घोषणा TPS80031_VANA_CFG_VOLTAGE			0x83
#घोषणा TPS80031_LDO2_CFG_TRANS				0x85
#घोषणा TPS80031_LDO2_CFG_STATE				0x86
#घोषणा TPS80031_LDO2_CFG_VOLTAGE			0x87
#घोषणा TPS80031_LDO4_CFG_TRANS				0x89
#घोषणा TPS80031_LDO4_CFG_STATE				0x8A
#घोषणा TPS80031_LDO4_CFG_VOLTAGE			0x8B
#घोषणा TPS80031_LDO3_CFG_TRANS				0x8D
#घोषणा TPS80031_LDO3_CFG_STATE				0x8E
#घोषणा TPS80031_LDO3_CFG_VOLTAGE			0x8F
#घोषणा TPS80031_LDO6_CFG_TRANS				0x91
#घोषणा TPS80031_LDO6_CFG_STATE				0x92
#घोषणा TPS80031_LDO6_CFG_VOLTAGE			0x93
#घोषणा TPS80031_LDOLN_CFG_TRANS			0x95
#घोषणा TPS80031_LDOLN_CFG_STATE			0x96
#घोषणा TPS80031_LDOLN_CFG_VOLTAGE			0x97
#घोषणा TPS80031_LDO5_CFG_TRANS				0x99
#घोषणा TPS80031_LDO5_CFG_STATE				0x9A
#घोषणा TPS80031_LDO5_CFG_VOLTAGE			0x9B
#घोषणा TPS80031_LDO1_CFG_TRANS				0x9D
#घोषणा TPS80031_LDO1_CFG_STATE				0x9E
#घोषणा TPS80031_LDO1_CFG_VOLTAGE			0x9F
#घोषणा TPS80031_LDOUSB_CFG_TRANS			0xA1
#घोषणा TPS80031_LDOUSB_CFG_STATE			0xA2
#घोषणा TPS80031_LDOUSB_CFG_VOLTAGE			0xA3
#घोषणा TPS80031_LDO7_CFG_TRANS				0xA5
#घोषणा TPS80031_LDO7_CFG_STATE				0xA6
#घोषणा TPS80031_LDO7_CFG_VOLTAGE			0xA7

/* PMC Slave Module  External Control */
#घोषणा TPS80031_REGEN1_CFG_TRANS			0xAE
#घोषणा TPS80031_REGEN1_CFG_STATE			0xAF
#घोषणा TPS80031_REGEN2_CFG_TRANS			0xB1
#घोषणा TPS80031_REGEN2_CFG_STATE			0xB2
#घोषणा TPS80031_SYSEN_CFG_TRANS			0xB4
#घोषणा TPS80031_SYSEN_CFG_STATE			0xB5

/* PMC Slave Module  Internal Control */
#घोषणा TPS80031_NRESPWRON_CFG_TRANS			0xB7
#घोषणा TPS80031_NRESPWRON_CFG_STATE			0xB8
#घोषणा TPS80031_CLK32KAO_CFG_TRANS			0xBA
#घोषणा TPS80031_CLK32KAO_CFG_STATE			0xBB
#घोषणा TPS80031_CLK32KG_CFG_TRANS			0xBD
#घोषणा TPS80031_CLK32KG_CFG_STATE			0xBE
#घोषणा TPS80031_CLK32KAUDIO_CFG_TRANS			0xC0
#घोषणा TPS80031_CLK32KAUDIO_CFG_STATE			0xC1
#घोषणा TPS80031_VRTC_CFG_TRANS				0xC3
#घोषणा TPS80031_VRTC_CFG_STATE				0xC4
#घोषणा TPS80031_BIAS_CFG_TRANS				0xC6
#घोषणा TPS80031_BIAS_CFG_STATE				0xC7
#घोषणा TPS80031_VSYSMIN_HI_CFG_TRANS			0xC9
#घोषणा TPS80031_VSYSMIN_HI_CFG_STATE			0xCA
#घोषणा TPS80031_RC6MHZ_CFG_TRANS			0xCC
#घोषणा TPS80031_RC6MHZ_CFG_STATE			0xCD
#घोषणा TPS80031_TMP_CFG_TRANS				0xCF
#घोषणा TPS80031_TMP_CFG_STATE				0xD0

/* PMC Slave Module  resources assignment */
#घोषणा TPS80031_PREQ1_RES_ASS_A			0xD7
#घोषणा TPS80031_PREQ1_RES_ASS_B			0xD8
#घोषणा TPS80031_PREQ1_RES_ASS_C			0xD9
#घोषणा TPS80031_PREQ2_RES_ASS_A			0xDA
#घोषणा TPS80031_PREQ2_RES_ASS_B			0xDB
#घोषणा TPS80031_PREQ2_RES_ASS_C			0xDC
#घोषणा TPS80031_PREQ3_RES_ASS_A			0xDD
#घोषणा TPS80031_PREQ3_RES_ASS_B			0xDE
#घोषणा TPS80031_PREQ3_RES_ASS_C			0xDF

/* PMC Slave Module  Miscellaneous */
#घोषणा TPS80031_SMPS_OFFSET				0xE0
#घोषणा TPS80031_SMPS_MULT				0xE3
#घोषणा TPS80031_MISC1					0xE4
#घोषणा TPS80031_MISC2					0xE5
#घोषणा TPS80031_BBSPOR_CFG				0xE6
#घोषणा TPS80031_TMP_CFG				0xE7

/* Battery Charging Controller and Indicator LED */
#घोषणा TPS80031_CONTROLLER_CTRL2			0xDA
#घोषणा TPS80031_CONTROLLER_VSEL_COMP			0xDB
#घोषणा TPS80031_CHARGERUSB_VSYSREG			0xDC
#घोषणा TPS80031_CHARGERUSB_VICHRG_PC			0xDD
#घोषणा TPS80031_LINEAR_CHRG_STS			0xDE
#घोषणा TPS80031_CONTROLLER_INT_MASK			0xE0
#घोषणा TPS80031_CONTROLLER_CTRL1			0xE1
#घोषणा TPS80031_CONTROLLER_WDG				0xE2
#घोषणा TPS80031_CONTROLLER_STAT1			0xE3
#घोषणा TPS80031_CHARGERUSB_INT_STATUS			0xE4
#घोषणा TPS80031_CHARGERUSB_INT_MASK			0xE5
#घोषणा TPS80031_CHARGERUSB_STATUS_INT1			0xE6
#घोषणा TPS80031_CHARGERUSB_STATUS_INT2			0xE7
#घोषणा TPS80031_CHARGERUSB_CTRL1			0xE8
#घोषणा TPS80031_CHARGERUSB_CTRL2			0xE9
#घोषणा TPS80031_CHARGERUSB_CTRL3			0xEA
#घोषणा TPS80031_CHARGERUSB_STAT1			0xEB
#घोषणा TPS80031_CHARGERUSB_VOREG			0xEC
#घोषणा TPS80031_CHARGERUSB_VICHRG			0xED
#घोषणा TPS80031_CHARGERUSB_CINLIMIT			0xEE
#घोषणा TPS80031_CHARGERUSB_CTRLLIMIT1			0xEF
#घोषणा TPS80031_CHARGERUSB_CTRLLIMIT2			0xF0
#घोषणा TPS80031_LED_PWM_CTRL1				0xF4
#घोषणा TPS80031_LED_PWM_CTRL2				0xF5

/* USB On-The-Go  */
#घोषणा TPS80031_BACKUP_REG				0xFA
#घोषणा TPS80031_USB_VENDOR_ID_LSB			0x00
#घोषणा TPS80031_USB_VENDOR_ID_MSB			0x01
#घोषणा TPS80031_USB_PRODUCT_ID_LSB			0x02
#घोषणा TPS80031_USB_PRODUCT_ID_MSB			0x03
#घोषणा TPS80031_USB_VBUS_CTRL_SET			0x04
#घोषणा TPS80031_USB_VBUS_CTRL_CLR			0x05
#घोषणा TPS80031_USB_ID_CTRL_SET			0x06
#घोषणा TPS80031_USB_ID_CTRL_CLR			0x07
#घोषणा TPS80031_USB_VBUS_INT_SRC			0x08
#घोषणा TPS80031_USB_VBUS_INT_LATCH_SET			0x09
#घोषणा TPS80031_USB_VBUS_INT_LATCH_CLR			0x0A
#घोषणा TPS80031_USB_VBUS_INT_EN_LO_SET			0x0B
#घोषणा TPS80031_USB_VBUS_INT_EN_LO_CLR			0x0C
#घोषणा TPS80031_USB_VBUS_INT_EN_HI_SET			0x0D
#घोषणा TPS80031_USB_VBUS_INT_EN_HI_CLR			0x0E
#घोषणा TPS80031_USB_ID_INT_SRC				0x0F
#घोषणा TPS80031_USB_ID_INT_LATCH_SET			0x10
#घोषणा TPS80031_USB_ID_INT_LATCH_CLR			0x11
#घोषणा TPS80031_USB_ID_INT_EN_LO_SET			0x12
#घोषणा TPS80031_USB_ID_INT_EN_LO_CLR			0x13
#घोषणा TPS80031_USB_ID_INT_EN_HI_SET			0x14
#घोषणा TPS80031_USB_ID_INT_EN_HI_CLR			0x15
#घोषणा TPS80031_USB_OTG_ADP_CTRL			0x16
#घोषणा TPS80031_USB_OTG_ADP_HIGH			0x17
#घोषणा TPS80031_USB_OTG_ADP_LOW			0x18
#घोषणा TPS80031_USB_OTG_ADP_RISE			0x19
#घोषणा TPS80031_USB_OTG_REVISION			0x1A

/* Gas Gauge */
#घोषणा TPS80031_FG_REG_00				0xC0
#घोषणा TPS80031_FG_REG_01				0xC1
#घोषणा TPS80031_FG_REG_02				0xC2
#घोषणा TPS80031_FG_REG_03				0xC3
#घोषणा TPS80031_FG_REG_04				0xC4
#घोषणा TPS80031_FG_REG_05				0xC5
#घोषणा TPS80031_FG_REG_06				0xC6
#घोषणा TPS80031_FG_REG_07				0xC7
#घोषणा TPS80031_FG_REG_08				0xC8
#घोषणा TPS80031_FG_REG_09				0xC9
#घोषणा TPS80031_FG_REG_10				0xCA
#घोषणा TPS80031_FG_REG_11				0xCB

/* General Purpose ADC */
#घोषणा TPS80031_GPADC_CTRL				0x2E
#घोषणा TPS80031_GPADC_CTRL2				0x2F
#घोषणा TPS80031_RTSELECT_LSB				0x32
#घोषणा TPS80031_RTSELECT_ISB				0x33
#घोषणा TPS80031_RTSELECT_MSB				0x34
#घोषणा TPS80031_GPSELECT_ISB				0x35
#घोषणा TPS80031_CTRL_P1				0x36
#घोषणा TPS80031_RTCH0_LSB				0x37
#घोषणा TPS80031_RTCH0_MSB				0x38
#घोषणा TPS80031_RTCH1_LSB				0x39
#घोषणा TPS80031_RTCH1_MSB				0x3A
#घोषणा TPS80031_GPCH0_LSB				0x3B
#घोषणा TPS80031_GPCH0_MSB				0x3C

/* SIM, MMC and Battery Detection */
#घोषणा TPS80031_SIMDEBOUNCING				0xEB
#घोषणा TPS80031_SIMCTRL				0xEC
#घोषणा TPS80031_MMCDEBOUNCING				0xED
#घोषणा TPS80031_MMCCTRL				0xEE
#घोषणा TPS80031_BATDEBOUNCING				0xEF

/* Vibrator Driver and PWMs */
#घोषणा TPS80031_VIBCTRL				0x9B
#घोषणा TPS80031_VIBMODE				0x9C
#घोषणा TPS80031_PWM1ON					0xBA
#घोषणा TPS80031_PWM1OFF				0xBB
#घोषणा TPS80031_PWM2ON					0xBD
#घोषणा TPS80031_PWM2OFF				0xBE

/* Control Interface */
#घोषणा TPS80031_INT_STS_A				0xD0
#घोषणा TPS80031_INT_STS_B				0xD1
#घोषणा TPS80031_INT_STS_C				0xD2
#घोषणा TPS80031_INT_MSK_LINE_A				0xD3
#घोषणा TPS80031_INT_MSK_LINE_B				0xD4
#घोषणा TPS80031_INT_MSK_LINE_C				0xD5
#घोषणा TPS80031_INT_MSK_STS_A				0xD6
#घोषणा TPS80031_INT_MSK_STS_B				0xD7
#घोषणा TPS80031_INT_MSK_STS_C				0xD8
#घोषणा TPS80031_TOGGLE1				0x90
#घोषणा TPS80031_TOGGLE2				0x91
#घोषणा TPS80031_TOGGLE3				0x92
#घोषणा TPS80031_PWDNSTATUS1				0x93
#घोषणा TPS80031_PWDNSTATUS2				0x94
#घोषणा TPS80031_VALIDITY0				0x17
#घोषणा TPS80031_VALIDITY1				0x18
#घोषणा TPS80031_VALIDITY2				0x19
#घोषणा TPS80031_VALIDITY3				0x1A
#घोषणा TPS80031_VALIDITY4				0x1B
#घोषणा TPS80031_VALIDITY5				0x1C
#घोषणा TPS80031_VALIDITY6				0x1D
#घोषणा TPS80031_VALIDITY7				0x1E

/* Version number related रेजिस्टर */
#घोषणा TPS80031_JTAGVERNUM				0x87
#घोषणा TPS80031_EPROM_REV				0xDF

/* GPADC Trimming Bits. */
#घोषणा TPS80031_GPADC_TRIM0				0xCC
#घोषणा TPS80031_GPADC_TRIM1				0xCD
#घोषणा TPS80031_GPADC_TRIM2				0xCE
#घोषणा TPS80031_GPADC_TRIM3				0xCF
#घोषणा TPS80031_GPADC_TRIM4				0xD0
#घोषणा TPS80031_GPADC_TRIM5				0xD1
#घोषणा TPS80031_GPADC_TRIM6				0xD2
#घोषणा TPS80031_GPADC_TRIM7				0xD3
#घोषणा TPS80031_GPADC_TRIM8				0xD4
#घोषणा TPS80031_GPADC_TRIM9				0xD5
#घोषणा TPS80031_GPADC_TRIM10				0xD6
#घोषणा TPS80031_GPADC_TRIM11				0xD7
#घोषणा TPS80031_GPADC_TRIM12				0xD8
#घोषणा TPS80031_GPADC_TRIM13				0xD9
#घोषणा TPS80031_GPADC_TRIM14				0xDA
#घोषणा TPS80031_GPADC_TRIM15				0xDB
#घोषणा TPS80031_GPADC_TRIM16				0xDC
#घोषणा TPS80031_GPADC_TRIM17				0xDD
#घोषणा TPS80031_GPADC_TRIM18				0xDE

/* TPS80031_CONTROLLER_STAT1 bit fields */
#घोषणा TPS80031_CONTROLLER_STAT1_BAT_TEMP		0
#घोषणा TPS80031_CONTROLLER_STAT1_BAT_REMOVED		1
#घोषणा TPS80031_CONTROLLER_STAT1_VBUS_DET		2
#घोषणा TPS80031_CONTROLLER_STAT1_VAC_DET		3
#घोषणा TPS80031_CONTROLLER_STAT1_FAULT_WDG		4
#घोषणा TPS80031_CONTROLLER_STAT1_LINCH_GATED		6
/* TPS80031_CONTROLLER_INT_MASK bit filed */
#घोषणा TPS80031_CONTROLLER_INT_MASK_MVAC_DET		0
#घोषणा TPS80031_CONTROLLER_INT_MASK_MVBUS_DET		1
#घोषणा TPS80031_CONTROLLER_INT_MASK_MBAT_TEMP		2
#घोषणा TPS80031_CONTROLLER_INT_MASK_MFAULT_WDG		3
#घोषणा TPS80031_CONTROLLER_INT_MASK_MBAT_REMOVED	4
#घोषणा TPS80031_CONTROLLER_INT_MASK_MLINCH_GATED	5

#घोषणा TPS80031_CHARGE_CONTROL_SUB_INT_MASK		0x3F

/* TPS80031_PHOENIX_DEV_ON bit field */
#घोषणा TPS80031_DEVOFF					0x1

#घोषणा TPS80031_EXT_CONTROL_CFG_TRANS			0
#घोषणा TPS80031_EXT_CONTROL_CFG_STATE			1

/* State रेजिस्टर field */
#घोषणा TPS80031_STATE_OFF				0x00
#घोषणा TPS80031_STATE_ON				0x01
#घोषणा TPS80031_STATE_MASK				0x03

/* Trans रेजिस्टर field */
#घोषणा TPS80031_TRANS_ACTIVE_OFF			0x00
#घोषणा TPS80031_TRANS_ACTIVE_ON			0x01
#घोषणा TPS80031_TRANS_ACTIVE_MASK			0x03
#घोषणा TPS80031_TRANS_SLEEP_OFF			0x00
#घोषणा TPS80031_TRANS_SLEEP_ON				0x04
#घोषणा TPS80031_TRANS_SLEEP_MASK			0x0C
#घोषणा TPS80031_TRANS_OFF_OFF				0x00
#घोषणा TPS80031_TRANS_OFF_ACTIVE			0x10
#घोषणा TPS80031_TRANS_OFF_MASK				0x30

#घोषणा TPS80031_EXT_PWR_REQ		(TPS80031_PWR_REQ_INPUT_PREQ1 | \
					TPS80031_PWR_REQ_INPUT_PREQ2 | \
					TPS80031_PWR_REQ_INPUT_PREQ3)

/* TPS80031_BBSPOR_CFG bit field */
#घोषणा TPS80031_BBSPOR_CHG_EN				0x8
#घोषणा TPS80031_MAX_REGISTER				0xFF

काष्ठा i2c_client;

/* Supported chips */
क्रमागत chips अणु
	TPS80031 = 0x00000001,
	TPS80032 = 0x00000002,
पूर्ण;

क्रमागत अणु
	TPS80031_INT_PWRON,
	TPS80031_INT_RPWRON,
	TPS80031_INT_SYS_VLOW,
	TPS80031_INT_RTC_ALARM,
	TPS80031_INT_RTC_PERIOD,
	TPS80031_INT_HOT_DIE,
	TPS80031_INT_VXX_SHORT,
	TPS80031_INT_SPDURATION,
	TPS80031_INT_WATCHDOG,
	TPS80031_INT_BAT,
	TPS80031_INT_SIM,
	TPS80031_INT_MMC,
	TPS80031_INT_RES,
	TPS80031_INT_GPADC_RT,
	TPS80031_INT_GPADC_SW2_EOC,
	TPS80031_INT_CC_AUTOCAL,
	TPS80031_INT_ID_WKUP,
	TPS80031_INT_VBUSS_WKUP,
	TPS80031_INT_ID,
	TPS80031_INT_VBUS,
	TPS80031_INT_CHRG_CTRL,
	TPS80031_INT_EXT_CHRG,
	TPS80031_INT_INT_CHRG,
	TPS80031_INT_RES2,
	TPS80031_INT_BAT_TEMP_OVRANGE,
	TPS80031_INT_BAT_REMOVED,
	TPS80031_INT_VBUS_DET,
	TPS80031_INT_VAC_DET,
	TPS80031_INT_FAULT_WDG,
	TPS80031_INT_LINCH_GATED,

	/* Last पूर्णांकerrupt id to get the end number */
	TPS80031_INT_NR,
पूर्ण;

/* TPS80031 Slave IDs */
#घोषणा TPS80031_NUM_SLAVES				4
#घोषणा TPS80031_SLAVE_ID0				0
#घोषणा TPS80031_SLAVE_ID1				1
#घोषणा TPS80031_SLAVE_ID2				2
#घोषणा TPS80031_SLAVE_ID3				3

/* TPS80031 I2C addresses */
#घोषणा TPS80031_I2C_ID0_ADDR				0x12
#घोषणा TPS80031_I2C_ID1_ADDR				0x48
#घोषणा TPS80031_I2C_ID2_ADDR				0x49
#घोषणा TPS80031_I2C_ID3_ADDR				0x4A

क्रमागत अणु
	TPS80031_REGULATOR_VIO,
	TPS80031_REGULATOR_SMPS1,
	TPS80031_REGULATOR_SMPS2,
	TPS80031_REGULATOR_SMPS3,
	TPS80031_REGULATOR_SMPS4,
	TPS80031_REGULATOR_VANA,
	TPS80031_REGULATOR_LDO1,
	TPS80031_REGULATOR_LDO2,
	TPS80031_REGULATOR_LDO3,
	TPS80031_REGULATOR_LDO4,
	TPS80031_REGULATOR_LDO5,
	TPS80031_REGULATOR_LDO6,
	TPS80031_REGULATOR_LDO7,
	TPS80031_REGULATOR_LDOLN,
	TPS80031_REGULATOR_LDOUSB,
	TPS80031_REGULATOR_VBUS,
	TPS80031_REGULATOR_REGEN1,
	TPS80031_REGULATOR_REGEN2,
	TPS80031_REGULATOR_SYSEN,
	TPS80031_REGULATOR_MAX,
पूर्ण;

/* Dअगरferent configurations क्रम the rails */
क्रमागत अणु
	/* USBLDO input selection */
	TPS80031_USBLDO_INPUT_VSYS		= 0x00000001,
	TPS80031_USBLDO_INPUT_PMID		= 0x00000002,

	/* LDO3 output mode */
	TPS80031_LDO3_OUTPUT_VIB		= 0x00000004,

	/* VBUS configuration */
	TPS80031_VBUS_DISCHRG_EN_PDN		= 0x00000004,
	TPS80031_VBUS_SW_ONLY			= 0x00000008,
	TPS80031_VBUS_SW_N_ID			= 0x00000010,
पूर्ण;

/* External controls requests */
क्रमागत tps80031_ext_control अणु
	TPS80031_PWR_REQ_INPUT_NONE		= 0x00000000,
	TPS80031_PWR_REQ_INPUT_PREQ1		= 0x00000001,
	TPS80031_PWR_REQ_INPUT_PREQ2		= 0x00000002,
	TPS80031_PWR_REQ_INPUT_PREQ3		= 0x00000004,
	TPS80031_PWR_OFF_ON_SLEEP		= 0x00000008,
	TPS80031_PWR_ON_ON_SLEEP		= 0x00000010,
पूर्ण;

क्रमागत tps80031_pupd_pins अणु
	TPS80031_PREQ1 = 0,
	TPS80031_PREQ2A,
	TPS80031_PREQ2B,
	TPS80031_PREQ2C,
	TPS80031_PREQ3,
	TPS80031_NRES_WARM,
	TPS80031_PWM_FORCE,
	TPS80031_CHRG_EXT_CHRG_STATZ,
	TPS80031_SIM,
	TPS80031_MMC,
	TPS80031_GPADC_START,
	TPS80031_DVSI2C_SCL,
	TPS80031_DVSI2C_SDA,
	TPS80031_CTLI2C_SCL,
	TPS80031_CTLI2C_SDA,
पूर्ण;

क्रमागत tps80031_pupd_settings अणु
	TPS80031_PUPD_NORMAL,
	TPS80031_PUPD_PULLDOWN,
	TPS80031_PUPD_PULLUP,
पूर्ण;

काष्ठा tps80031 अणु
	काष्ठा device		*dev;
	अचिन्हित दीर्घ		chip_info;
	पूर्णांक			es_version;
	काष्ठा i2c_client	*clients[TPS80031_NUM_SLAVES];
	काष्ठा regmap		*regmap[TPS80031_NUM_SLAVES];
	काष्ठा regmap_irq_chip_data *irq_data;
पूर्ण;

काष्ठा tps80031_pupd_init_data अणु
	पूर्णांक input_pin;
	पूर्णांक setting;
पूर्ण;

/*
 * काष्ठा tps80031_regulator_platक्रमm_data - tps80031 regulator platक्रमm data.
 *
 * @reg_init_data: The regulator init data.
 * @ext_ctrl_flag: External control flag क्रम sleep/घातer request control.
 * @config_flags: Configuration flag to configure the rails.
 *		  It should be ORed of config क्रमागतs.
 */

काष्ठा tps80031_regulator_platक्रमm_data अणु
	काष्ठा regulator_init_data *reg_init_data;
	अचिन्हित पूर्णांक ext_ctrl_flag;
	अचिन्हित पूर्णांक config_flags;
पूर्ण;

काष्ठा tps80031_platक्रमm_data अणु
	पूर्णांक irq_base;
	bool use_घातer_off;
	काष्ठा tps80031_pupd_init_data *pupd_init_data;
	पूर्णांक pupd_init_data_size;
	काष्ठा tps80031_regulator_platक्रमm_data
			*regulator_pdata[TPS80031_REGULATOR_MAX];
पूर्ण;

अटल अंतरभूत पूर्णांक tps80031_ग_लिखो(काष्ठा device *dev, पूर्णांक sid,
		पूर्णांक reg, uपूर्णांक8_t val)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);

	वापस regmap_ग_लिखो(tps80031->regmap[sid], reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक tps80031_ग_लिखोs(काष्ठा device *dev, पूर्णांक sid, पूर्णांक reg,
		पूर्णांक len, uपूर्णांक8_t *val)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);

	वापस regmap_bulk_ग_लिखो(tps80031->regmap[sid], reg, val, len);
पूर्ण

अटल अंतरभूत पूर्णांक tps80031_पढ़ो(काष्ठा device *dev, पूर्णांक sid,
		पूर्णांक reg, uपूर्णांक8_t *val)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ival;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tps80031->regmap[sid], reg, &ival);
	अगर (ret < 0) अणु
		dev_err(dev, "failed reading from reg 0x%02x\n", reg);
		वापस ret;
	पूर्ण

	*val = ival;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक tps80031_पढ़ोs(काष्ठा device *dev, पूर्णांक sid,
		पूर्णांक reg, पूर्णांक len, uपूर्णांक8_t *val)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);

	वापस regmap_bulk_पढ़ो(tps80031->regmap[sid], reg, val, len);
पूर्ण

अटल अंतरभूत पूर्णांक tps80031_set_bits(काष्ठा device *dev, पूर्णांक sid,
		पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);

	वापस regmap_update_bits(tps80031->regmap[sid], reg,
				bit_mask, bit_mask);
पूर्ण

अटल अंतरभूत पूर्णांक tps80031_clr_bits(काष्ठा device *dev, पूर्णांक sid,
		पूर्णांक reg, uपूर्णांक8_t bit_mask)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);

	वापस regmap_update_bits(tps80031->regmap[sid], reg, bit_mask, 0);
पूर्ण

अटल अंतरभूत पूर्णांक tps80031_update(काष्ठा device *dev, पूर्णांक sid,
		पूर्णांक reg, uपूर्णांक8_t val, uपूर्णांक8_t mask)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);

	वापस regmap_update_bits(tps80031->regmap[sid], reg, mask, val);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ tps80031_get_chip_info(काष्ठा device *dev)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);

	वापस tps80031->chip_info;
पूर्ण

अटल अंतरभूत पूर्णांक tps80031_get_pmu_version(काष्ठा device *dev)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);

	वापस tps80031->es_version;
पूर्ण

अटल अंतरभूत पूर्णांक tps80031_irq_get_virq(काष्ठा device *dev, पूर्णांक irq)
अणु
	काष्ठा tps80031 *tps80031 = dev_get_drvdata(dev);

	वापस regmap_irq_get_virq(tps80031->irq_data, irq);
पूर्ण

बाह्य पूर्णांक tps80031_ext_घातer_req_config(काष्ठा device *dev,
		अचिन्हित दीर्घ ext_ctrl_flag, पूर्णांक preq_bit,
		पूर्णांक state_reg_add, पूर्णांक trans_reg_add);
#पूर्ण_अगर /*__LINUX_MFD_TPS80031_H */
