<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * core.h  --  Core Driver क्रम Wolfson WM8350 PMIC
 *
 * Copyright 2007 Wolfson Microelectronics PLC
 */

#अगर_अघोषित __LINUX_MFD_WM8350_CORE_H_
#घोषणा __LINUX_MFD_WM8350_CORE_H_

#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/wm8350/audपन.स>
#समावेश <linux/mfd/wm8350/gpपन.स>
#समावेश <linux/mfd/wm8350/pmic.h>
#समावेश <linux/mfd/wm8350/rtc.h>
#समावेश <linux/mfd/wm8350/supply.h>
#समावेश <linux/mfd/wm8350/wdt.h>

/*
 * Register values.
 */
#घोषणा WM8350_RESET_ID                         0x00
#घोषणा WM8350_ID                               0x01
#घोषणा WM8350_REVISION				0x02
#घोषणा WM8350_SYSTEM_CONTROL_1                 0x03
#घोषणा WM8350_SYSTEM_CONTROL_2                 0x04
#घोषणा WM8350_SYSTEM_HIBERNATE                 0x05
#घोषणा WM8350_INTERFACE_CONTROL                0x06
#घोषणा WM8350_POWER_MGMT_1                     0x08
#घोषणा WM8350_POWER_MGMT_2                     0x09
#घोषणा WM8350_POWER_MGMT_3                     0x0A
#घोषणा WM8350_POWER_MGMT_4                     0x0B
#घोषणा WM8350_POWER_MGMT_5                     0x0C
#घोषणा WM8350_POWER_MGMT_6                     0x0D
#घोषणा WM8350_POWER_MGMT_7                     0x0E

#घोषणा WM8350_SYSTEM_INTERRUPTS                0x18
#घोषणा WM8350_INT_STATUS_1                     0x19
#घोषणा WM8350_INT_STATUS_2                     0x1A
#घोषणा WM8350_POWER_UP_INT_STATUS              0x1B
#घोषणा WM8350_UNDER_VOLTAGE_INT_STATUS         0x1C
#घोषणा WM8350_OVER_CURRENT_INT_STATUS          0x1D
#घोषणा WM8350_GPIO_INT_STATUS                  0x1E
#घोषणा WM8350_COMPARATOR_INT_STATUS            0x1F
#घोषणा WM8350_SYSTEM_INTERRUPTS_MASK           0x20
#घोषणा WM8350_INT_STATUS_1_MASK                0x21
#घोषणा WM8350_INT_STATUS_2_MASK                0x22
#घोषणा WM8350_POWER_UP_INT_STATUS_MASK         0x23
#घोषणा WM8350_UNDER_VOLTAGE_INT_STATUS_MASK    0x24
#घोषणा WM8350_OVER_CURRENT_INT_STATUS_MASK     0x25
#घोषणा WM8350_GPIO_INT_STATUS_MASK             0x26
#घोषणा WM8350_COMPARATOR_INT_STATUS_MASK       0x27
#घोषणा WM8350_CHARGER_OVERRIDES		0xE2
#घोषणा WM8350_MISC_OVERRIDES			0xE3
#घोषणा WM8350_COMPARATOR_OVERRIDES		0xE7
#घोषणा WM8350_STATE_MACHINE_STATUS		0xE9

#घोषणा WM8350_MAX_REGISTER                     0xFF

#घोषणा WM8350_UNLOCK_KEY		0x0013
#घोषणा WM8350_LOCK_KEY			0x0000

/*
 * Field Definitions.
 */

/*
 * R0 (0x00) - Reset/ID
 */
#घोषणा WM8350_SW_RESET_CHIP_ID_MASK            0xFFFF

/*
 * R1 (0x01) - ID
 */
#घोषणा WM8350_CHIP_REV_MASK                    0x7000
#घोषणा WM8350_CONF_STS_MASK                    0x0C00
#घोषणा WM8350_CUST_ID_MASK                     0x00FF

/*
 * R2 (0x02) - Revision
 */
#घोषणा WM8350_MASK_REV_MASK			0x00FF

/*
 * R3 (0x03) - System Control 1
 */
#घोषणा WM8350_CHIP_ON                          0x8000
#घोषणा WM8350_POWERCYCLE                       0x2000
#घोषणा WM8350_VCC_FAULT_OV                     0x1000
#घोषणा WM8350_REG_RSTB_TIME_MASK               0x0C00
#घोषणा WM8350_BG_SLEEP                         0x0200
#घोषणा WM8350_MEM_VALID                        0x0020
#घोषणा WM8350_CHIP_SET_UP                      0x0010
#घोषणा WM8350_ON_DEB_T                         0x0008
#घोषणा WM8350_ON_POL                           0x0002
#घोषणा WM8350_IRQ_POL                          0x0001

/*
 * R4 (0x04) - System Control 2
 */
#घोषणा WM8350_USB_SUSPEND_8MA                  0x8000
#घोषणा WM8350_USB_SUSPEND                      0x4000
#घोषणा WM8350_USB_MSTR                         0x2000
#घोषणा WM8350_USB_MSTR_SRC                     0x1000
#घोषणा WM8350_USB_500MA                        0x0800
#घोषणा WM8350_USB_NOLIM                        0x0400

/*
 * R5 (0x05) - System Hibernate
 */
#घोषणा WM8350_HIBERNATE                        0x8000
#घोषणा WM8350_WDOG_HIB_MODE                    0x0080
#घोषणा WM8350_REG_HIB_STARTUP_SEQ              0x0040
#घोषणा WM8350_REG_RESET_HIB_MODE               0x0020
#घोषणा WM8350_RST_HIB_MODE                     0x0010
#घोषणा WM8350_IRQ_HIB_MODE                     0x0008
#घोषणा WM8350_MEMRST_HIB_MODE                  0x0004
#घोषणा WM8350_PCCOMP_HIB_MODE                  0x0002
#घोषणा WM8350_TEMPMON_HIB_MODE                 0x0001

/*
 * R6 (0x06) - Interface Control
 */
#घोषणा WM8350_USE_DEV_PINS                     0x8000
#घोषणा WM8350_USE_DEV_PINS_MASK                0x8000
#घोषणा WM8350_USE_DEV_PINS_SHIFT                   15
#घोषणा WM8350_DEV_ADDR_MASK                    0x6000
#घोषणा WM8350_DEV_ADDR_SHIFT                       13
#घोषणा WM8350_CONFIG_DONE                      0x1000
#घोषणा WM8350_CONFIG_DONE_MASK                 0x1000
#घोषणा WM8350_CONFIG_DONE_SHIFT                    12
#घोषणा WM8350_RECONFIG_AT_ON                   0x0800
#घोषणा WM8350_RECONFIG_AT_ON_MASK              0x0800
#घोषणा WM8350_RECONFIG_AT_ON_SHIFT                 11
#घोषणा WM8350_AUTOINC                          0x0200
#घोषणा WM8350_AUTOINC_MASK                     0x0200
#घोषणा WM8350_AUTOINC_SHIFT                         9
#घोषणा WM8350_ARA                              0x0100
#घोषणा WM8350_ARA_MASK                         0x0100
#घोषणा WM8350_ARA_SHIFT                             8
#घोषणा WM8350_SPI_CFG                          0x0008
#घोषणा WM8350_SPI_CFG_MASK                     0x0008
#घोषणा WM8350_SPI_CFG_SHIFT                         3
#घोषणा WM8350_SPI_4WIRE                        0x0004
#घोषणा WM8350_SPI_4WIRE_MASK                   0x0004
#घोषणा WM8350_SPI_4WIRE_SHIFT                       2
#घोषणा WM8350_SPI_3WIRE                        0x0002
#घोषणा WM8350_SPI_3WIRE_MASK                   0x0002
#घोषणा WM8350_SPI_3WIRE_SHIFT                       1

/* Bit values क्रम R06 (0x06) */
#घोषणा WM8350_USE_DEV_PINS_PRIMARY                  0
#घोषणा WM8350_USE_DEV_PINS_DEV                      1

#घोषणा WM8350_DEV_ADDR_34                           0
#घोषणा WM8350_DEV_ADDR_36                           1
#घोषणा WM8350_DEV_ADDR_3C                           2
#घोषणा WM8350_DEV_ADDR_3E                           3

#घोषणा WM8350_CONFIG_DONE_OFF                       0
#घोषणा WM8350_CONFIG_DONE_DONE                      1

#घोषणा WM8350_RECONFIG_AT_ON_OFF                    0
#घोषणा WM8350_RECONFIG_AT_ON_ON                     1

#घोषणा WM8350_AUTOINC_OFF                           0
#घोषणा WM8350_AUTOINC_ON                            1

#घोषणा WM8350_ARA_OFF                               0
#घोषणा WM8350_ARA_ON                                1

#घोषणा WM8350_SPI_CFG_CMOS                          0
#घोषणा WM8350_SPI_CFG_OD                            1

#घोषणा WM8350_SPI_4WIRE_3WIRE                       0
#घोषणा WM8350_SPI_4WIRE_4WIRE                       1

#घोषणा WM8350_SPI_3WIRE_I2C                         0
#घोषणा WM8350_SPI_3WIRE_SPI                         1

/*
 * R8 (0x08) - Power mgmt (1)
 */
#घोषणा WM8350_CODEC_ISEL_MASK                  0xC000
#घोषणा WM8350_VBUFEN                           0x2000
#घोषणा WM8350_OUTPUT_DRAIN_EN                  0x0400
#घोषणा WM8350_MIC_DET_ENA                      0x0100
#घोषणा WM8350_BIASEN                           0x0020
#घोषणा WM8350_MICBEN                           0x0010
#घोषणा WM8350_VMIDEN                           0x0004
#घोषणा WM8350_VMID_MASK                        0x0003
#घोषणा WM8350_VMID_SHIFT                            0

/*
 * R9 (0x09) - Power mgmt (2)
 */
#घोषणा WM8350_IN3R_ENA                         0x0800
#घोषणा WM8350_IN3L_ENA                         0x0400
#घोषणा WM8350_INR_ENA                          0x0200
#घोषणा WM8350_INL_ENA                          0x0100
#घोषणा WM8350_MIXINR_ENA                       0x0080
#घोषणा WM8350_MIXINL_ENA                       0x0040
#घोषणा WM8350_OUT4_ENA                         0x0020
#घोषणा WM8350_OUT3_ENA                         0x0010
#घोषणा WM8350_MIXOUTR_ENA                      0x0002
#घोषणा WM8350_MIXOUTL_ENA                      0x0001

/*
 * R10 (0x0A) - Power mgmt (3)
 */
#घोषणा WM8350_IN3R_TO_OUT2R                    0x0080
#घोषणा WM8350_OUT2R_ENA                        0x0008
#घोषणा WM8350_OUT2L_ENA                        0x0004
#घोषणा WM8350_OUT1R_ENA                        0x0002
#घोषणा WM8350_OUT1L_ENA                        0x0001

/*
 * R11 (0x0B) - Power mgmt (4)
 */
#घोषणा WM8350_SYSCLK_ENA                       0x4000
#घोषणा WM8350_ADC_HPF_ENA                      0x2000
#घोषणा WM8350_FLL_ENA                          0x0800
#घोषणा WM8350_FLL_OSC_ENA                      0x0400
#घोषणा WM8350_TOCLK_ENA                        0x0100
#घोषणा WM8350_DACR_ENA                         0x0020
#घोषणा WM8350_DACL_ENA                         0x0010
#घोषणा WM8350_ADCR_ENA                         0x0008
#घोषणा WM8350_ADCL_ENA                         0x0004

/*
 * R12 (0x0C) - Power mgmt (5)
 */
#घोषणा WM8350_CODEC_ENA                        0x1000
#घोषणा WM8350_RTC_TICK_ENA                     0x0800
#घोषणा WM8350_OSC32K_ENA                       0x0400
#घोषणा WM8350_CHG_ENA                          0x0200
#घोषणा WM8350_ACC_DET_ENA                      0x0100
#घोषणा WM8350_AUXADC_ENA                       0x0080
#घोषणा WM8350_DCMP4_ENA                        0x0008
#घोषणा WM8350_DCMP3_ENA                        0x0004
#घोषणा WM8350_DCMP2_ENA                        0x0002
#घोषणा WM8350_DCMP1_ENA                        0x0001

/*
 * R13 (0x0D) - Power mgmt (6)
 */
#घोषणा WM8350_LS_ENA                           0x8000
#घोषणा WM8350_LDO4_ENA                         0x0800
#घोषणा WM8350_LDO3_ENA                         0x0400
#घोषणा WM8350_LDO2_ENA                         0x0200
#घोषणा WM8350_LDO1_ENA                         0x0100
#घोषणा WM8350_DC6_ENA                          0x0020
#घोषणा WM8350_DC5_ENA                          0x0010
#घोषणा WM8350_DC4_ENA                          0x0008
#घोषणा WM8350_DC3_ENA                          0x0004
#घोषणा WM8350_DC2_ENA                          0x0002
#घोषणा WM8350_DC1_ENA                          0x0001

/*
 * R14 (0x0E) - Power mgmt (7)
 */
#घोषणा WM8350_CS2_ENA                          0x0002
#घोषणा WM8350_CS1_ENA                          0x0001

/*
 * R24 (0x18) - System Interrupts
 */
#घोषणा WM8350_OC_INT                           0x2000
#घोषणा WM8350_UV_INT                           0x1000
#घोषणा WM8350_PUTO_INT                         0x0800
#घोषणा WM8350_CS_INT                           0x0200
#घोषणा WM8350_EXT_INT                          0x0100
#घोषणा WM8350_CODEC_INT                        0x0080
#घोषणा WM8350_GP_INT                           0x0040
#घोषणा WM8350_AUXADC_INT                       0x0020
#घोषणा WM8350_RTC_INT                          0x0010
#घोषणा WM8350_SYS_INT                          0x0008
#घोषणा WM8350_CHG_INT                          0x0004
#घोषणा WM8350_USB_INT                          0x0002
#घोषणा WM8350_WKUP_INT                         0x0001

/*
 * R25 (0x19) - Interrupt Status 1
 */
#घोषणा WM8350_CHG_BAT_HOT_EINT                 0x8000
#घोषणा WM8350_CHG_BAT_COLD_EINT                0x4000
#घोषणा WM8350_CHG_BAT_FAIL_EINT                0x2000
#घोषणा WM8350_CHG_TO_EINT                      0x1000
#घोषणा WM8350_CHG_END_EINT                     0x0800
#घोषणा WM8350_CHG_START_EINT                   0x0400
#घोषणा WM8350_CHG_FAST_RDY_EINT                0x0200
#घोषणा WM8350_RTC_PER_EINT                     0x0080
#घोषणा WM8350_RTC_SEC_EINT                     0x0040
#घोषणा WM8350_RTC_ALM_EINT                     0x0020
#घोषणा WM8350_CHG_VBATT_LT_3P9_EINT            0x0004
#घोषणा WM8350_CHG_VBATT_LT_3P1_EINT            0x0002
#घोषणा WM8350_CHG_VBATT_LT_2P85_EINT           0x0001

/*
 * R26 (0x1A) - Interrupt Status 2
 */
#घोषणा WM8350_CS1_EINT                         0x2000
#घोषणा WM8350_CS2_EINT                         0x1000
#घोषणा WM8350_USB_LIMIT_EINT                   0x0400
#घोषणा WM8350_AUXADC_DATARDY_EINT              0x0100
#घोषणा WM8350_AUXADC_DCOMP4_EINT               0x0080
#घोषणा WM8350_AUXADC_DCOMP3_EINT               0x0040
#घोषणा WM8350_AUXADC_DCOMP2_EINT               0x0020
#घोषणा WM8350_AUXADC_DCOMP1_EINT               0x0010
#घोषणा WM8350_SYS_HYST_COMP_FAIL_EINT          0x0008
#घोषणा WM8350_SYS_CHIP_GT115_EINT              0x0004
#घोषणा WM8350_SYS_CHIP_GT140_EINT              0x0002
#घोषणा WM8350_SYS_WDOG_TO_EINT                 0x0001

/*
 * R27 (0x1B) - Power Up Interrupt Status
 */
#घोषणा WM8350_PUTO_LDO4_EINT                   0x0800
#घोषणा WM8350_PUTO_LDO3_EINT                   0x0400
#घोषणा WM8350_PUTO_LDO2_EINT                   0x0200
#घोषणा WM8350_PUTO_LDO1_EINT                   0x0100
#घोषणा WM8350_PUTO_DC6_EINT                    0x0020
#घोषणा WM8350_PUTO_DC5_EINT                    0x0010
#घोषणा WM8350_PUTO_DC4_EINT                    0x0008
#घोषणा WM8350_PUTO_DC3_EINT                    0x0004
#घोषणा WM8350_PUTO_DC2_EINT                    0x0002
#घोषणा WM8350_PUTO_DC1_EINT                    0x0001

/*
 * R28 (0x1C) - Under Voltage Interrupt status
 */
#घोषणा WM8350_UV_LDO4_EINT                     0x0800
#घोषणा WM8350_UV_LDO3_EINT                     0x0400
#घोषणा WM8350_UV_LDO2_EINT                     0x0200
#घोषणा WM8350_UV_LDO1_EINT                     0x0100
#घोषणा WM8350_UV_DC6_EINT                      0x0020
#घोषणा WM8350_UV_DC5_EINT                      0x0010
#घोषणा WM8350_UV_DC4_EINT                      0x0008
#घोषणा WM8350_UV_DC3_EINT                      0x0004
#घोषणा WM8350_UV_DC2_EINT                      0x0002
#घोषणा WM8350_UV_DC1_EINT                      0x0001

/*
 * R29 (0x1D) - Over Current Interrupt status
 */
#घोषणा WM8350_OC_LS_EINT                       0x8000

/*
 * R30 (0x1E) - GPIO Interrupt Status
 */
#घोषणा WM8350_GP12_EINT                        0x1000
#घोषणा WM8350_GP11_EINT                        0x0800
#घोषणा WM8350_GP10_EINT                        0x0400
#घोषणा WM8350_GP9_EINT                         0x0200
#घोषणा WM8350_GP8_EINT                         0x0100
#घोषणा WM8350_GP7_EINT                         0x0080
#घोषणा WM8350_GP6_EINT                         0x0040
#घोषणा WM8350_GP5_EINT                         0x0020
#घोषणा WM8350_GP4_EINT                         0x0010
#घोषणा WM8350_GP3_EINT                         0x0008
#घोषणा WM8350_GP2_EINT                         0x0004
#घोषणा WM8350_GP1_EINT                         0x0002
#घोषणा WM8350_GP0_EINT                         0x0001

/*
 * R31 (0x1F) - Comparator Interrupt Status
 */
#घोषणा WM8350_EXT_USB_FB_EINT                  0x8000
#घोषणा WM8350_EXT_WALL_FB_EINT                 0x4000
#घोषणा WM8350_EXT_BAT_FB_EINT                  0x2000
#घोषणा WM8350_CODEC_JCK_DET_L_EINT             0x0800
#घोषणा WM8350_CODEC_JCK_DET_R_EINT             0x0400
#घोषणा WM8350_CODEC_MICSCD_EINT                0x0200
#घोषणा WM8350_CODEC_MICD_EINT                  0x0100
#घोषणा WM8350_WKUP_OFF_STATE_EINT              0x0040
#घोषणा WM8350_WKUP_HIB_STATE_EINT              0x0020
#घोषणा WM8350_WKUP_CONV_FAULT_EINT             0x0010
#घोषणा WM8350_WKUP_WDOG_RST_EINT               0x0008
#घोषणा WM8350_WKUP_GP_PWR_ON_EINT              0x0004
#घोषणा WM8350_WKUP_ONKEY_EINT                  0x0002
#घोषणा WM8350_WKUP_GP_WAKEUP_EINT              0x0001

/*
 * R32 (0x20) - System Interrupts Mask
 */
#घोषणा WM8350_IM_OC_INT                        0x2000
#घोषणा WM8350_IM_UV_INT                        0x1000
#घोषणा WM8350_IM_PUTO_INT                      0x0800
#घोषणा WM8350_IM_SPARE_INT                     0x0400
#घोषणा WM8350_IM_CS_INT                        0x0200
#घोषणा WM8350_IM_EXT_INT                       0x0100
#घोषणा WM8350_IM_CODEC_INT                     0x0080
#घोषणा WM8350_IM_GP_INT                        0x0040
#घोषणा WM8350_IM_AUXADC_INT                    0x0020
#घोषणा WM8350_IM_RTC_INT                       0x0010
#घोषणा WM8350_IM_SYS_INT                       0x0008
#घोषणा WM8350_IM_CHG_INT                       0x0004
#घोषणा WM8350_IM_USB_INT                       0x0002
#घोषणा WM8350_IM_WKUP_INT                      0x0001

/*
 * R33 (0x21) - Interrupt Status 1 Mask
 */
#घोषणा WM8350_IM_CHG_BAT_HOT_EINT              0x8000
#घोषणा WM8350_IM_CHG_BAT_COLD_EINT             0x4000
#घोषणा WM8350_IM_CHG_BAT_FAIL_EINT             0x2000
#घोषणा WM8350_IM_CHG_TO_EINT                   0x1000
#घोषणा WM8350_IM_CHG_END_EINT                  0x0800
#घोषणा WM8350_IM_CHG_START_EINT                0x0400
#घोषणा WM8350_IM_CHG_FAST_RDY_EINT             0x0200
#घोषणा WM8350_IM_RTC_PER_EINT                  0x0080
#घोषणा WM8350_IM_RTC_SEC_EINT                  0x0040
#घोषणा WM8350_IM_RTC_ALM_EINT                  0x0020
#घोषणा WM8350_IM_CHG_VBATT_LT_3P9_EINT         0x0004
#घोषणा WM8350_IM_CHG_VBATT_LT_3P1_EINT         0x0002
#घोषणा WM8350_IM_CHG_VBATT_LT_2P85_EINT        0x0001

/*
 * R34 (0x22) - Interrupt Status 2 Mask
 */
#घोषणा WM8350_IM_SPARE2_EINT                   0x8000
#घोषणा WM8350_IM_SPARE1_EINT                   0x4000
#घोषणा WM8350_IM_CS1_EINT                      0x2000
#घोषणा WM8350_IM_CS2_EINT                      0x1000
#घोषणा WM8350_IM_USB_LIMIT_EINT                0x0400
#घोषणा WM8350_IM_AUXADC_DATARDY_EINT           0x0100
#घोषणा WM8350_IM_AUXADC_DCOMP4_EINT            0x0080
#घोषणा WM8350_IM_AUXADC_DCOMP3_EINT            0x0040
#घोषणा WM8350_IM_AUXADC_DCOMP2_EINT            0x0020
#घोषणा WM8350_IM_AUXADC_DCOMP1_EINT            0x0010
#घोषणा WM8350_IM_SYS_HYST_COMP_FAIL_EINT       0x0008
#घोषणा WM8350_IM_SYS_CHIP_GT115_EINT           0x0004
#घोषणा WM8350_IM_SYS_CHIP_GT140_EINT           0x0002
#घोषणा WM8350_IM_SYS_WDOG_TO_EINT              0x0001

/*
 * R35 (0x23) - Power Up Interrupt Status Mask
 */
#घोषणा WM8350_IM_PUTO_LDO4_EINT                0x0800
#घोषणा WM8350_IM_PUTO_LDO3_EINT                0x0400
#घोषणा WM8350_IM_PUTO_LDO2_EINT                0x0200
#घोषणा WM8350_IM_PUTO_LDO1_EINT                0x0100
#घोषणा WM8350_IM_PUTO_DC6_EINT                 0x0020
#घोषणा WM8350_IM_PUTO_DC5_EINT                 0x0010
#घोषणा WM8350_IM_PUTO_DC4_EINT                 0x0008
#घोषणा WM8350_IM_PUTO_DC3_EINT                 0x0004
#घोषणा WM8350_IM_PUTO_DC2_EINT                 0x0002
#घोषणा WM8350_IM_PUTO_DC1_EINT                 0x0001

/*
 * R36 (0x24) - Under Voltage Interrupt status Mask
 */
#घोषणा WM8350_IM_UV_LDO4_EINT                  0x0800
#घोषणा WM8350_IM_UV_LDO3_EINT                  0x0400
#घोषणा WM8350_IM_UV_LDO2_EINT                  0x0200
#घोषणा WM8350_IM_UV_LDO1_EINT                  0x0100
#घोषणा WM8350_IM_UV_DC6_EINT                   0x0020
#घोषणा WM8350_IM_UV_DC5_EINT                   0x0010
#घोषणा WM8350_IM_UV_DC4_EINT                   0x0008
#घोषणा WM8350_IM_UV_DC3_EINT                   0x0004
#घोषणा WM8350_IM_UV_DC2_EINT                   0x0002
#घोषणा WM8350_IM_UV_DC1_EINT                   0x0001

/*
 * R37 (0x25) - Over Current Interrupt status Mask
 */
#घोषणा WM8350_IM_OC_LS_EINT                    0x8000

/*
 * R38 (0x26) - GPIO Interrupt Status Mask
 */
#घोषणा WM8350_IM_GP12_EINT                     0x1000
#घोषणा WM8350_IM_GP11_EINT                     0x0800
#घोषणा WM8350_IM_GP10_EINT                     0x0400
#घोषणा WM8350_IM_GP9_EINT                      0x0200
#घोषणा WM8350_IM_GP8_EINT                      0x0100
#घोषणा WM8350_IM_GP7_EINT                      0x0080
#घोषणा WM8350_IM_GP6_EINT                      0x0040
#घोषणा WM8350_IM_GP5_EINT                      0x0020
#घोषणा WM8350_IM_GP4_EINT                      0x0010
#घोषणा WM8350_IM_GP3_EINT                      0x0008
#घोषणा WM8350_IM_GP2_EINT                      0x0004
#घोषणा WM8350_IM_GP1_EINT                      0x0002
#घोषणा WM8350_IM_GP0_EINT                      0x0001

/*
 * R39 (0x27) - Comparator Interrupt Status Mask
 */
#घोषणा WM8350_IM_EXT_USB_FB_EINT               0x8000
#घोषणा WM8350_IM_EXT_WALL_FB_EINT              0x4000
#घोषणा WM8350_IM_EXT_BAT_FB_EINT               0x2000
#घोषणा WM8350_IM_CODEC_JCK_DET_L_EINT          0x0800
#घोषणा WM8350_IM_CODEC_JCK_DET_R_EINT          0x0400
#घोषणा WM8350_IM_CODEC_MICSCD_EINT             0x0200
#घोषणा WM8350_IM_CODEC_MICD_EINT               0x0100
#घोषणा WM8350_IM_WKUP_OFF_STATE_EINT           0x0040
#घोषणा WM8350_IM_WKUP_HIB_STATE_EINT           0x0020
#घोषणा WM8350_IM_WKUP_CONV_FAULT_EINT          0x0010
#घोषणा WM8350_IM_WKUP_WDOG_RST_EINT            0x0008
#घोषणा WM8350_IM_WKUP_GP_PWR_ON_EINT           0x0004
#घोषणा WM8350_IM_WKUP_ONKEY_EINT               0x0002
#घोषणा WM8350_IM_WKUP_GP_WAKEUP_EINT           0x0001

/*
 * R220 (0xDC) - RAM BIST 1
 */
#घोषणा WM8350_READ_STATUS                      0x0800
#घोषणा WM8350_TSTRAM_CLK                       0x0100
#घोषणा WM8350_TSTRAM_CLK_ENA                   0x0080
#घोषणा WM8350_STARTSEQ                         0x0040
#घोषणा WM8350_READ_SRC                         0x0020
#घोषणा WM8350_COUNT_सूची                        0x0010
#घोषणा WM8350_TSTRAM_MODE_MASK                 0x000E
#घोषणा WM8350_TSTRAM_ENA                       0x0001

/*
 * R225 (0xE1) - DCDC/LDO status
 */
#घोषणा WM8350_LS_STS                           0x8000
#घोषणा WM8350_LDO4_STS                         0x0800
#घोषणा WM8350_LDO3_STS                         0x0400
#घोषणा WM8350_LDO2_STS                         0x0200
#घोषणा WM8350_LDO1_STS                         0x0100
#घोषणा WM8350_DC6_STS                          0x0020
#घोषणा WM8350_DC5_STS                          0x0010
#घोषणा WM8350_DC4_STS                          0x0008
#घोषणा WM8350_DC3_STS                          0x0004
#घोषणा WM8350_DC2_STS                          0x0002
#घोषणा WM8350_DC1_STS                          0x0001

/*
 * R226 (0xE2) - Charger status
 */
#घोषणा WM8350_CHG_BATT_HOT_OVRDE		0x8000
#घोषणा WM8350_CHG_BATT_COLD_OVRDE		0x4000

/*
 * R227 (0xE3) - Misc Overrides
 */
#घोषणा WM8350_USB_LIMIT_OVRDE			0x0400

/*
 * R227 (0xE7) - Comparator Overrides
 */
#घोषणा WM8350_USB_FB_OVRDE			0x8000
#घोषणा WM8350_WALL_FB_OVRDE			0x4000
#घोषणा WM8350_BATT_FB_OVRDE			0x2000


/*
 * R233 (0xE9) - State Machinine Status
 */
#घोषणा WM8350_USB_SM_MASK			0x0700
#घोषणा WM8350_USB_SM_SHIFT			8

#घोषणा WM8350_USB_SM_100_SLV   1
#घोषणा WM8350_USB_SM_500_SLV   5
#घोषणा WM8350_USB_SM_STDBY_SLV 7

/* WM8350 wake up conditions */
#घोषणा WM8350_IRQ_WKUP_OFF_STATE		43
#घोषणा WM8350_IRQ_WKUP_HIB_STATE		44
#घोषणा WM8350_IRQ_WKUP_CONV_FAULT		45
#घोषणा WM8350_IRQ_WKUP_WDOG_RST		46
#घोषणा WM8350_IRQ_WKUP_GP_PWR_ON		47
#घोषणा WM8350_IRQ_WKUP_ONKEY			48
#घोषणा WM8350_IRQ_WKUP_GP_WAKEUP		49

/* wm8350 chip revisions */
#घोषणा WM8350_REV_E				0x4
#घोषणा WM8350_REV_F				0x5
#घोषणा WM8350_REV_G				0x6
#घोषणा WM8350_REV_H				0x7

#घोषणा WM8350_NUM_IRQ				63

#घोषणा WM8350_NUM_IRQ_REGS 7

बाह्य स्थिर काष्ठा regmap_config wm8350_regmap;

काष्ठा wm8350;

काष्ठा wm8350_hwmon अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device *classdev;
पूर्ण;

काष्ठा wm8350 अणु
	काष्ठा device *dev;

	/* device IO */
	काष्ठा regmap *regmap;
	bool unlocked;

	काष्ठा mutex auxadc_mutex;
	काष्ठा completion auxadc_करोne;

	/* Interrupt handling */
	काष्ठा mutex irq_lock;
	पूर्णांक chip_irq;
	पूर्णांक irq_base;
	u16 irq_masks[WM8350_NUM_IRQ_REGS];

	/* Client devices */
	काष्ठा wm8350_codec codec;
	काष्ठा wm8350_gpio gpio;
	काष्ठा wm8350_hwmon hwmon;
	काष्ठा wm8350_pmic pmic;
	काष्ठा wm8350_घातer घातer;
	काष्ठा wm8350_rtc rtc;
	काष्ठा wm8350_wdt wdt;
पूर्ण;

/**
 * Data to be supplied by the platक्रमm to initialise the WM8350.
 *
 * @init: Function called during driver initialisation.  Should be
 *        used by the platक्रमm to configure GPIO functions and similar.
 * @irq_high: Set अगर WM8350 IRQ is active high.
 * @irq_base: Base IRQ क्रम genirq (not currently used).
 * @gpio_base: Base क्रम gpiolib.
 */
काष्ठा wm8350_platक्रमm_data अणु
	पूर्णांक (*init)(काष्ठा wm8350 *wm8350);
	पूर्णांक irq_high;
	पूर्णांक irq_base;
	पूर्णांक gpio_base;
पूर्ण;


/*
 * WM8350 device initialisation and निकास.
 */
पूर्णांक wm8350_device_init(काष्ठा wm8350 *wm8350, पूर्णांक irq,
		       काष्ठा wm8350_platक्रमm_data *pdata);

/*
 * WM8350 device IO
 */
पूर्णांक wm8350_clear_bits(काष्ठा wm8350 *wm8350, u16 reg, u16 mask);
पूर्णांक wm8350_set_bits(काष्ठा wm8350 *wm8350, u16 reg, u16 mask);
u16 wm8350_reg_पढ़ो(काष्ठा wm8350 *wm8350, पूर्णांक reg);
पूर्णांक wm8350_reg_ग_लिखो(काष्ठा wm8350 *wm8350, पूर्णांक reg, u16 val);
पूर्णांक wm8350_reg_lock(काष्ठा wm8350 *wm8350);
पूर्णांक wm8350_reg_unlock(काष्ठा wm8350 *wm8350);
पूर्णांक wm8350_block_पढ़ो(काष्ठा wm8350 *wm8350, पूर्णांक reg, पूर्णांक size, u16 *dest);
पूर्णांक wm8350_block_ग_लिखो(काष्ठा wm8350 *wm8350, पूर्णांक reg, पूर्णांक size, u16 *src);

/*
 * WM8350 पूर्णांकernal पूर्णांकerrupts
 */
अटल अंतरभूत पूर्णांक wm8350_रेजिस्टर_irq(काष्ठा wm8350 *wm8350, पूर्णांक irq,
				      irq_handler_t handler,
				      अचिन्हित दीर्घ flags,
				      स्थिर अक्षर *name, व्योम *data)
अणु
	अगर (!wm8350->irq_base)
		वापस -ENODEV;

	वापस request_thपढ़ोed_irq(irq + wm8350->irq_base, शून्य,
				    handler, flags, name, data);
पूर्ण

अटल अंतरभूत व्योम wm8350_मुक्त_irq(काष्ठा wm8350 *wm8350, पूर्णांक irq, व्योम *data)
अणु
	मुक्त_irq(irq + wm8350->irq_base, data);
पूर्ण

अटल अंतरभूत व्योम wm8350_mask_irq(काष्ठा wm8350 *wm8350, पूर्णांक irq)
अणु
	disable_irq(irq + wm8350->irq_base);
पूर्ण

अटल अंतरभूत व्योम wm8350_unmask_irq(काष्ठा wm8350 *wm8350, पूर्णांक irq)
अणु
	enable_irq(irq + wm8350->irq_base);
पूर्ण

पूर्णांक wm8350_irq_init(काष्ठा wm8350 *wm8350, पूर्णांक irq,
		    काष्ठा wm8350_platक्रमm_data *pdata);
पूर्णांक wm8350_irq_निकास(काष्ठा wm8350 *wm8350);

#पूर्ण_अगर
