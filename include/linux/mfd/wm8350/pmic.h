<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * pmic.h  --  Power Management Driver क्रम Wolfson WM8350 PMIC
 *
 * Copyright 2007 Wolfson Microelectronics PLC
 */

#अगर_अघोषित __LINUX_MFD_WM8350_PMIC_H
#घोषणा __LINUX_MFD_WM8350_PMIC_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/regulator/machine.h>

/*
 * Register values.
 */

#घोषणा WM8350_CURRENT_SINK_DRIVER_A            0xAC
#घोषणा WM8350_CSA_FLASH_CONTROL                0xAD
#घोषणा WM8350_CURRENT_SINK_DRIVER_B            0xAE
#घोषणा WM8350_CSB_FLASH_CONTROL                0xAF
#घोषणा WM8350_DCDC_LDO_REQUESTED               0xB0
#घोषणा WM8350_DCDC_ACTIVE_OPTIONS              0xB1
#घोषणा WM8350_DCDC_SLEEP_OPTIONS               0xB2
#घोषणा WM8350_POWER_CHECK_COMPARATOR           0xB3
#घोषणा WM8350_DCDC1_CONTROL                    0xB4
#घोषणा WM8350_DCDC1_TIMEOUTS                   0xB5
#घोषणा WM8350_DCDC1_LOW_POWER                  0xB6
#घोषणा WM8350_DCDC2_CONTROL                    0xB7
#घोषणा WM8350_DCDC2_TIMEOUTS                   0xB8
#घोषणा WM8350_DCDC3_CONTROL                    0xBA
#घोषणा WM8350_DCDC3_TIMEOUTS                   0xBB
#घोषणा WM8350_DCDC3_LOW_POWER                  0xBC
#घोषणा WM8350_DCDC4_CONTROL                    0xBD
#घोषणा WM8350_DCDC4_TIMEOUTS                   0xBE
#घोषणा WM8350_DCDC4_LOW_POWER                  0xBF
#घोषणा WM8350_DCDC5_CONTROL                    0xC0
#घोषणा WM8350_DCDC5_TIMEOUTS                   0xC1
#घोषणा WM8350_DCDC6_CONTROL                    0xC3
#घोषणा WM8350_DCDC6_TIMEOUTS                   0xC4
#घोषणा WM8350_DCDC6_LOW_POWER                  0xC5
#घोषणा WM8350_LIMIT_SWITCH_CONTROL             0xC7
#घोषणा WM8350_LDO1_CONTROL                     0xC8
#घोषणा WM8350_LDO1_TIMEOUTS                    0xC9
#घोषणा WM8350_LDO1_LOW_POWER                   0xCA
#घोषणा WM8350_LDO2_CONTROL                     0xCB
#घोषणा WM8350_LDO2_TIMEOUTS                    0xCC
#घोषणा WM8350_LDO2_LOW_POWER                   0xCD
#घोषणा WM8350_LDO3_CONTROL                     0xCE
#घोषणा WM8350_LDO3_TIMEOUTS                    0xCF
#घोषणा WM8350_LDO3_LOW_POWER                   0xD0
#घोषणा WM8350_LDO4_CONTROL                     0xD1
#घोषणा WM8350_LDO4_TIMEOUTS                    0xD2
#घोषणा WM8350_LDO4_LOW_POWER                   0xD3
#घोषणा WM8350_VCC_FAULT_MASKS                  0xD7
#घोषणा WM8350_MAIN_BANDGAP_CONTROL             0xD8
#घोषणा WM8350_OSC_CONTROL                      0xD9
#घोषणा WM8350_RTC_TICK_CONTROL                 0xDA
#घोषणा WM8350_SECURITY                         0xDB
#घोषणा WM8350_RAM_BIST_1                       0xDC
#घोषणा WM8350_DCDC_LDO_STATUS                  0xE1
#घोषणा WM8350_GPIO_PIN_STATUS                  0xE6

#घोषणा WM8350_DCDC1_FORCE_PWM                  0xF8
#घोषणा WM8350_DCDC3_FORCE_PWM                  0xFA
#घोषणा WM8350_DCDC4_FORCE_PWM                  0xFB
#घोषणा WM8350_DCDC6_FORCE_PWM                  0xFD

/*
 * R172 (0xAC) - Current Sink Driver A
 */
#घोषणा WM8350_CS1_HIB_MODE                     0x1000
#घोषणा WM8350_CS1_HIB_MODE_MASK                0x1000
#घोषणा WM8350_CS1_HIB_MODE_SHIFT                   12
#घोषणा WM8350_CS1_ISEL_MASK                    0x003F
#घोषणा WM8350_CS1_ISEL_SHIFT                        0

/* Bit values क्रम R172 (0xAC) */
#घोषणा WM8350_CS1_HIB_MODE_DISABLE                  0
#घोषणा WM8350_CS1_HIB_MODE_LEAVE                    1

#घोषणा WM8350_CS1_ISEL_220M                      0x3F

/*
 * R173 (0xAD) - CSA Flash control
 */
#घोषणा WM8350_CS1_FLASH_MODE                   0x8000
#घोषणा WM8350_CS1_TRIGSRC                      0x4000
#घोषणा WM8350_CS1_DRIVE                        0x2000
#घोषणा WM8350_CS1_FLASH_DUR_MASK               0x0300
#घोषणा WM8350_CS1_OFF_RAMP_MASK                0x0030
#घोषणा WM8350_CS1_ON_RAMP_MASK                 0x0003

/*
 * R174 (0xAE) - Current Sink Driver B
 */
#घोषणा WM8350_CS2_HIB_MODE                     0x1000
#घोषणा WM8350_CS2_ISEL_MASK                    0x003F

/*
 * R175 (0xAF) - CSB Flash control
 */
#घोषणा WM8350_CS2_FLASH_MODE                   0x8000
#घोषणा WM8350_CS2_TRIGSRC                      0x4000
#घोषणा WM8350_CS2_DRIVE                        0x2000
#घोषणा WM8350_CS2_FLASH_DUR_MASK               0x0300
#घोषणा WM8350_CS2_OFF_RAMP_MASK                0x0030
#घोषणा WM8350_CS2_ON_RAMP_MASK                 0x0003

/*
 * R176 (0xB0) - DCDC/LDO requested
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
 * R177 (0xB1) - DCDC Active options
 */
#घोषणा WM8350_PUTO_MASK                        0x3000
#घोषणा WM8350_PWRUP_DELAY_MASK                 0x0300
#घोषणा WM8350_DC6_ACTIVE                       0x0020
#घोषणा WM8350_DC4_ACTIVE                       0x0008
#घोषणा WM8350_DC3_ACTIVE                       0x0004
#घोषणा WM8350_DC1_ACTIVE                       0x0001

/*
 * R178 (0xB2) - DCDC Sleep options
 */
#घोषणा WM8350_DC6_SLEEP                        0x0020
#घोषणा WM8350_DC4_SLEEP                        0x0008
#घोषणा WM8350_DC3_SLEEP                        0x0004
#घोषणा WM8350_DC1_SLEEP                        0x0001

/*
 * R179 (0xB3) - Power-check comparator
 */
#घोषणा WM8350_PCCMP_ERRACT                     0x4000
#घोषणा WM8350_PCCMP_RAIL                       0x0100
#घोषणा WM8350_PCCMP_OFF_THR_MASK               0x0070
#घोषणा WM8350_PCCMP_ON_THR_MASK                0x0007

/*
 * R180 (0xB4) - DCDC1 Control
 */
#घोषणा WM8350_DC1_OPFLT                        0x0400
#घोषणा WM8350_DC1_VSEL_MASK                    0x007F
#घोषणा WM8350_DC1_VSEL_SHIFT                        0

/*
 * R181 (0xB5) - DCDC1 Timeouts
 */
#घोषणा WM8350_DC1_ERRACT_MASK                  0xC000
#घोषणा WM8350_DC1_ERRACT_SHIFT                     14
#घोषणा WM8350_DC1_ENSLOT_MASK                  0x3C00
#घोषणा WM8350_DC1_ENSLOT_SHIFT                     10
#घोषणा WM8350_DC1_SDSLOT_MASK                  0x03C0
#घोषणा WM8350_DC1_UVTO_MASK                    0x0030
#घोषणा WM8350_DC1_SDSLOT_SHIFT                      6

/* Bit values क्रम R181 (0xB5) */
#घोषणा WM8350_DC1_ERRACT_NONE                       0
#घोषणा WM8350_DC1_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_DC1_ERRACT_SHUTDOWN_SYS               2

/*
 * R182 (0xB6) - DCDC1 Low Power
 */
#घोषणा WM8350_DC1_HIB_MODE_MASK                0x7000
#घोषणा WM8350_DC1_HIB_TRIG_MASK                0x0300
#घोषणा WM8350_DC1_VIMG_MASK                    0x007F

/*
 * R183 (0xB7) - DCDC2 Control
 */
#घोषणा WM8350_DC2_MODE                         0x4000
#घोषणा WM8350_DC2_MODE_MASK                    0x4000
#घोषणा WM8350_DC2_MODE_SHIFT                       14
#घोषणा WM8350_DC2_HIB_MODE                     0x1000
#घोषणा WM8350_DC2_HIB_MODE_MASK                0x1000
#घोषणा WM8350_DC2_HIB_MODE_SHIFT                   12
#घोषणा WM8350_DC2_HIB_TRIG_MASK                0x0300
#घोषणा WM8350_DC2_HIB_TRIG_SHIFT                    8
#घोषणा WM8350_DC2_ILIM                         0x0040
#घोषणा WM8350_DC2_ILIM_MASK                    0x0040
#घोषणा WM8350_DC2_ILIM_SHIFT                        6
#घोषणा WM8350_DC2_RMP_MASK                     0x0018
#घोषणा WM8350_DC2_RMP_SHIFT                         3
#घोषणा WM8350_DC2_FBSRC_MASK                   0x0003
#घोषणा WM8350_DC2_FBSRC_SHIFT                       0

/* Bit values क्रम R183 (0xB7) */
#घोषणा WM8350_DC2_MODE_BOOST                        0
#घोषणा WM8350_DC2_MODE_SWITCH                       1

#घोषणा WM8350_DC2_HIB_MODE_ACTIVE                   1
#घोषणा WM8350_DC2_HIB_MODE_DISABLE                  0

#घोषणा WM8350_DC2_HIB_TRIG_NONE                     0
#घोषणा WM8350_DC2_HIB_TRIG_LPWR1                    1
#घोषणा WM8350_DC2_HIB_TRIG_LPWR2                    2
#घोषणा WM8350_DC2_HIB_TRIG_LPWR3                    3

#घोषणा WM8350_DC2_ILIM_HIGH                         0
#घोषणा WM8350_DC2_ILIM_LOW                          1

#घोषणा WM8350_DC2_RMP_30V                           0
#घोषणा WM8350_DC2_RMP_20V                           1
#घोषणा WM8350_DC2_RMP_10V                           2
#घोषणा WM8350_DC2_RMP_5V                            3

#घोषणा WM8350_DC2_FBSRC_FB2                         0
#घोषणा WM8350_DC2_FBSRC_ISINKA                      1
#घोषणा WM8350_DC2_FBSRC_ISINKB                      2
#घोषणा WM8350_DC2_FBSRC_USB                         3

/*
 * R184 (0xB8) - DCDC2 Timeouts
 */
#घोषणा WM8350_DC2_ERRACT_MASK                  0xC000
#घोषणा WM8350_DC2_ERRACT_SHIFT                     14
#घोषणा WM8350_DC2_ENSLOT_MASK                  0x3C00
#घोषणा WM8350_DC2_ENSLOT_SHIFT                     10
#घोषणा WM8350_DC2_SDSLOT_MASK                  0x03C0
#घोषणा WM8350_DC2_UVTO_MASK                    0x0030

/* Bit values क्रम R184 (0xB8) */
#घोषणा WM8350_DC2_ERRACT_NONE                       0
#घोषणा WM8350_DC2_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_DC2_ERRACT_SHUTDOWN_SYS               2

/*
 * R186 (0xBA) - DCDC3 Control
 */
#घोषणा WM8350_DC3_OPFLT                        0x0400
#घोषणा WM8350_DC3_VSEL_MASK                    0x007F
#घोषणा WM8350_DC3_VSEL_SHIFT                        0

/*
 * R187 (0xBB) - DCDC3 Timeouts
 */
#घोषणा WM8350_DC3_ERRACT_MASK                  0xC000
#घोषणा WM8350_DC3_ERRACT_SHIFT                     14
#घोषणा WM8350_DC3_ENSLOT_MASK                  0x3C00
#घोषणा WM8350_DC3_ENSLOT_SHIFT                     10
#घोषणा WM8350_DC3_SDSLOT_MASK                  0x03C0
#घोषणा WM8350_DC3_UVTO_MASK                    0x0030
#घोषणा WM8350_DC3_SDSLOT_SHIFT                      6

/* Bit values क्रम R187 (0xBB) */
#घोषणा WM8350_DC3_ERRACT_NONE                       0
#घोषणा WM8350_DC3_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_DC3_ERRACT_SHUTDOWN_SYS               2
/*
 * R188 (0xBC) - DCDC3 Low Power
 */
#घोषणा WM8350_DC3_HIB_MODE_MASK                0x7000
#घोषणा WM8350_DC3_HIB_TRIG_MASK                0x0300
#घोषणा WM8350_DC3_VIMG_MASK                    0x007F

/*
 * R189 (0xBD) - DCDC4 Control
 */
#घोषणा WM8350_DC4_OPFLT                        0x0400
#घोषणा WM8350_DC4_VSEL_MASK                    0x007F
#घोषणा WM8350_DC4_VSEL_SHIFT                        0

/*
 * R190 (0xBE) - DCDC4 Timeouts
 */
#घोषणा WM8350_DC4_ERRACT_MASK                  0xC000
#घोषणा WM8350_DC4_ERRACT_SHIFT                     14
#घोषणा WM8350_DC4_ENSLOT_MASK                  0x3C00
#घोषणा WM8350_DC4_ENSLOT_SHIFT                     10
#घोषणा WM8350_DC4_SDSLOT_MASK                  0x03C0
#घोषणा WM8350_DC4_UVTO_MASK                    0x0030
#घोषणा WM8350_DC4_SDSLOT_SHIFT                      6

/* Bit values क्रम R190 (0xBE) */
#घोषणा WM8350_DC4_ERRACT_NONE                       0
#घोषणा WM8350_DC4_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_DC4_ERRACT_SHUTDOWN_SYS               2

/*
 * R191 (0xBF) - DCDC4 Low Power
 */
#घोषणा WM8350_DC4_HIB_MODE_MASK                0x7000
#घोषणा WM8350_DC4_HIB_TRIG_MASK                0x0300
#घोषणा WM8350_DC4_VIMG_MASK                    0x007F

/*
 * R192 (0xC0) - DCDC5 Control
 */
#घोषणा WM8350_DC5_MODE                         0x4000
#घोषणा WM8350_DC5_MODE_MASK                    0x4000
#घोषणा WM8350_DC5_MODE_SHIFT                       14
#घोषणा WM8350_DC5_HIB_MODE                     0x1000
#घोषणा WM8350_DC5_HIB_MODE_MASK                0x1000
#घोषणा WM8350_DC5_HIB_MODE_SHIFT                   12
#घोषणा WM8350_DC5_HIB_TRIG_MASK                0x0300
#घोषणा WM8350_DC5_HIB_TRIG_SHIFT                    8
#घोषणा WM8350_DC5_ILIM                         0x0040
#घोषणा WM8350_DC5_ILIM_MASK                    0x0040
#घोषणा WM8350_DC5_ILIM_SHIFT                        6
#घोषणा WM8350_DC5_RMP_MASK                     0x0018
#घोषणा WM8350_DC5_RMP_SHIFT                         3
#घोषणा WM8350_DC5_FBSRC_MASK                   0x0003
#घोषणा WM8350_DC5_FBSRC_SHIFT                       0

/* Bit values क्रम R192 (0xC0) */
#घोषणा WM8350_DC5_MODE_BOOST                        0
#घोषणा WM8350_DC5_MODE_SWITCH                       1

#घोषणा WM8350_DC5_HIB_MODE_ACTIVE                   1
#घोषणा WM8350_DC5_HIB_MODE_DISABLE                  0

#घोषणा WM8350_DC5_HIB_TRIG_NONE                     0
#घोषणा WM8350_DC5_HIB_TRIG_LPWR1                    1
#घोषणा WM8350_DC5_HIB_TRIG_LPWR2                    2
#घोषणा WM8350_DC5_HIB_TRIG_LPWR3                    3

#घोषणा WM8350_DC5_ILIM_HIGH                         0
#घोषणा WM8350_DC5_ILIM_LOW                          1

#घोषणा WM8350_DC5_RMP_30V                           0
#घोषणा WM8350_DC5_RMP_20V                           1
#घोषणा WM8350_DC5_RMP_10V                           2
#घोषणा WM8350_DC5_RMP_5V                            3

#घोषणा WM8350_DC5_FBSRC_FB2                         0
#घोषणा WM8350_DC5_FBSRC_ISINKA                      1
#घोषणा WM8350_DC5_FBSRC_ISINKB                      2
#घोषणा WM8350_DC5_FBSRC_USB                         3

/*
 * R193 (0xC1) - DCDC5 Timeouts
 */
#घोषणा WM8350_DC5_ERRACT_MASK                  0xC000
#घोषणा WM8350_DC5_ERRACT_SHIFT                     14
#घोषणा WM8350_DC5_ENSLOT_MASK                  0x3C00
#घोषणा WM8350_DC5_ENSLOT_SHIFT                     10
#घोषणा WM8350_DC5_SDSLOT_MASK                  0x03C0
#घोषणा WM8350_DC5_UVTO_MASK                    0x0030
#घोषणा WM8350_DC5_SDSLOT_SHIFT                      6

/* Bit values क्रम R193 (0xC1) */
#घोषणा WM8350_DC5_ERRACT_NONE                       0
#घोषणा WM8350_DC5_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_DC5_ERRACT_SHUTDOWN_SYS               2

/*
 * R195 (0xC3) - DCDC6 Control
 */
#घोषणा WM8350_DC6_OPFLT                        0x0400
#घोषणा WM8350_DC6_VSEL_MASK                    0x007F
#घोषणा WM8350_DC6_VSEL_SHIFT                        0

/*
 * R196 (0xC4) - DCDC6 Timeouts
 */
#घोषणा WM8350_DC6_ERRACT_MASK                  0xC000
#घोषणा WM8350_DC6_ERRACT_SHIFT                     14
#घोषणा WM8350_DC6_ENSLOT_MASK                  0x3C00
#घोषणा WM8350_DC6_ENSLOT_SHIFT                     10
#घोषणा WM8350_DC6_SDSLOT_MASK                  0x03C0
#घोषणा WM8350_DC6_UVTO_MASK                    0x0030
#घोषणा WM8350_DC6_SDSLOT_SHIFT                      6

/* Bit values क्रम R196 (0xC4) */
#घोषणा WM8350_DC6_ERRACT_NONE                       0
#घोषणा WM8350_DC6_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_DC6_ERRACT_SHUTDOWN_SYS               2

/*
 * R197 (0xC5) - DCDC6 Low Power
 */
#घोषणा WM8350_DC6_HIB_MODE_MASK                0x7000
#घोषणा WM8350_DC6_HIB_TRIG_MASK                0x0300
#घोषणा WM8350_DC6_VIMG_MASK                    0x007F

/*
 * R199 (0xC7) - Limit Switch Control
 */
#घोषणा WM8350_LS_ERRACT_MASK                   0xC000
#घोषणा WM8350_LS_ERRACT_SHIFT                      14
#घोषणा WM8350_LS_ENSLOT_MASK                   0x3C00
#घोषणा WM8350_LS_ENSLOT_SHIFT                      10
#घोषणा WM8350_LS_SDSLOT_MASK                   0x03C0
#घोषणा WM8350_LS_SDSLOT_SHIFT                       6
#घोषणा WM8350_LS_HIB_MODE                      0x0010
#घोषणा WM8350_LS_HIB_MODE_MASK                 0x0010
#घोषणा WM8350_LS_HIB_MODE_SHIFT                     4
#घोषणा WM8350_LS_HIB_PROT                      0x0002
#घोषणा WM8350_LS_HIB_PROT_MASK                 0x0002
#घोषणा WM8350_LS_HIB_PROT_SHIFT                     1
#घोषणा WM8350_LS_PROT                          0x0001
#घोषणा WM8350_LS_PROT_MASK                     0x0001
#घोषणा WM8350_LS_PROT_SHIFT                         0

/* Bit values क्रम R199 (0xC7) */
#घोषणा WM8350_LS_ERRACT_NONE                       0
#घोषणा WM8350_LS_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_LS_ERRACT_SHUTDOWN_SYS               2

/*
 * R200 (0xC8) - LDO1 Control
 */
#घोषणा WM8350_LDO1_SWI                         0x4000
#घोषणा WM8350_LDO1_OPFLT                       0x0400
#घोषणा WM8350_LDO1_VSEL_MASK                   0x001F
#घोषणा WM8350_LDO1_VSEL_SHIFT                       0

/*
 * R201 (0xC9) - LDO1 Timeouts
 */
#घोषणा WM8350_LDO1_ERRACT_MASK                 0xC000
#घोषणा WM8350_LDO1_ERRACT_SHIFT                    14
#घोषणा WM8350_LDO1_ENSLOT_MASK                 0x3C00
#घोषणा WM8350_LDO1_ENSLOT_SHIFT                    10
#घोषणा WM8350_LDO1_SDSLOT_MASK                 0x03C0
#घोषणा WM8350_LDO1_UVTO_MASK                   0x0030
#घोषणा WM8350_LDO1_SDSLOT_SHIFT                     6

/* Bit values क्रम R201 (0xC9) */
#घोषणा WM8350_LDO1_ERRACT_NONE                       0
#घोषणा WM8350_LDO1_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_LDO1_ERRACT_SHUTDOWN_SYS               2

/*
 * R202 (0xCA) - LDO1 Low Power
 */
#घोषणा WM8350_LDO1_HIB_MODE_MASK               0x3000
#घोषणा WM8350_LDO1_HIB_TRIG_MASK               0x0300
#घोषणा WM8350_LDO1_VIMG_MASK                   0x001F
#घोषणा WM8350_LDO1_HIB_MODE_DIS		(0x1 << 12)


/*
 * R203 (0xCB) - LDO2 Control
 */
#घोषणा WM8350_LDO2_SWI                         0x4000
#घोषणा WM8350_LDO2_OPFLT                       0x0400
#घोषणा WM8350_LDO2_VSEL_MASK                   0x001F
#घोषणा WM8350_LDO2_VSEL_SHIFT                       0

/*
 * R204 (0xCC) - LDO2 Timeouts
 */
#घोषणा WM8350_LDO2_ERRACT_MASK                 0xC000
#घोषणा WM8350_LDO2_ERRACT_SHIFT                    14
#घोषणा WM8350_LDO2_ENSLOT_MASK                 0x3C00
#घोषणा WM8350_LDO2_ENSLOT_SHIFT                    10
#घोषणा WM8350_LDO2_SDSLOT_MASK                 0x03C0
#घोषणा WM8350_LDO2_SDSLOT_SHIFT                     6

/* Bit values क्रम R204 (0xCC) */
#घोषणा WM8350_LDO2_ERRACT_NONE                       0
#घोषणा WM8350_LDO2_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_LDO2_ERRACT_SHUTDOWN_SYS               2

/*
 * R205 (0xCD) - LDO2 Low Power
 */
#घोषणा WM8350_LDO2_HIB_MODE_MASK               0x3000
#घोषणा WM8350_LDO2_HIB_TRIG_MASK               0x0300
#घोषणा WM8350_LDO2_VIMG_MASK                   0x001F

/*
 * R206 (0xCE) - LDO3 Control
 */
#घोषणा WM8350_LDO3_SWI                         0x4000
#घोषणा WM8350_LDO3_OPFLT                       0x0400
#घोषणा WM8350_LDO3_VSEL_MASK                   0x001F
#घोषणा WM8350_LDO3_VSEL_SHIFT                       0

/*
 * R207 (0xCF) - LDO3 Timeouts
 */
#घोषणा WM8350_LDO3_ERRACT_MASK                 0xC000
#घोषणा WM8350_LDO3_ERRACT_SHIFT                    14
#घोषणा WM8350_LDO3_ENSLOT_MASK                 0x3C00
#घोषणा WM8350_LDO3_ENSLOT_SHIFT                    10
#घोषणा WM8350_LDO3_SDSLOT_MASK                 0x03C0
#घोषणा WM8350_LDO3_UVTO_MASK                   0x0030
#घोषणा WM8350_LDO3_SDSLOT_SHIFT                     6

/* Bit values क्रम R207 (0xCF) */
#घोषणा WM8350_LDO3_ERRACT_NONE                       0
#घोषणा WM8350_LDO3_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_LDO3_ERRACT_SHUTDOWN_SYS               2

/*
 * R208 (0xD0) - LDO3 Low Power
 */
#घोषणा WM8350_LDO3_HIB_MODE_MASK               0x3000
#घोषणा WM8350_LDO3_HIB_TRIG_MASK               0x0300
#घोषणा WM8350_LDO3_VIMG_MASK                   0x001F

/*
 * R209 (0xD1) - LDO4 Control
 */
#घोषणा WM8350_LDO4_SWI                         0x4000
#घोषणा WM8350_LDO4_OPFLT                       0x0400
#घोषणा WM8350_LDO4_VSEL_MASK                   0x001F
#घोषणा WM8350_LDO4_VSEL_SHIFT                       0

/*
 * R210 (0xD2) - LDO4 Timeouts
 */
#घोषणा WM8350_LDO4_ERRACT_MASK                 0xC000
#घोषणा WM8350_LDO4_ERRACT_SHIFT                    14
#घोषणा WM8350_LDO4_ENSLOT_MASK                 0x3C00
#घोषणा WM8350_LDO4_ENSLOT_SHIFT                    10
#घोषणा WM8350_LDO4_SDSLOT_MASK                 0x03C0
#घोषणा WM8350_LDO4_UVTO_MASK                   0x0030
#घोषणा WM8350_LDO4_SDSLOT_SHIFT                     6

/* Bit values क्रम R210 (0xD2) */
#घोषणा WM8350_LDO4_ERRACT_NONE                       0
#घोषणा WM8350_LDO4_ERRACT_SHUTDOWN_CONV              1
#घोषणा WM8350_LDO4_ERRACT_SHUTDOWN_SYS               2

/*
 * R211 (0xD3) - LDO4 Low Power
 */
#घोषणा WM8350_LDO4_HIB_MODE_MASK               0x3000
#घोषणा WM8350_LDO4_HIB_TRIG_MASK               0x0300
#घोषणा WM8350_LDO4_VIMG_MASK                   0x001F

/*
 * R215 (0xD7) - VCC_FAULT Masks
 */
#घोषणा WM8350_LS_FAULT                         0x8000
#घोषणा WM8350_LDO4_FAULT                       0x0800
#घोषणा WM8350_LDO3_FAULT                       0x0400
#घोषणा WM8350_LDO2_FAULT                       0x0200
#घोषणा WM8350_LDO1_FAULT                       0x0100
#घोषणा WM8350_DC6_FAULT                        0x0020
#घोषणा WM8350_DC5_FAULT                        0x0010
#घोषणा WM8350_DC4_FAULT                        0x0008
#घोषणा WM8350_DC3_FAULT                        0x0004
#घोषणा WM8350_DC2_FAULT                        0x0002
#घोषणा WM8350_DC1_FAULT                        0x0001

/*
 * R216 (0xD8) - Main Bandgap Control
 */
#घोषणा WM8350_MBG_LOAD_FUSES                   0x8000
#घोषणा WM8350_MBG_FUSE_WPREP                   0x4000
#घोषणा WM8350_MBG_FUSE_WRITE                   0x2000
#घोषणा WM8350_MBG_FUSE_TRIM_MASK               0x1F00
#घोषणा WM8350_MBG_TRIM_SRC                     0x0020
#घोषणा WM8350_MBG_USER_TRIM_MASK               0x001F

/*
 * R217 (0xD9) - OSC Control
 */
#घोषणा WM8350_OSC_LOAD_FUSES                   0x8000
#घोषणा WM8350_OSC_FUSE_WPREP                   0x4000
#घोषणा WM8350_OSC_FUSE_WRITE                   0x2000
#घोषणा WM8350_OSC_FUSE_TRIM_MASK               0x0F00
#घोषणा WM8350_OSC_TRIM_SRC                     0x0020
#घोषणा WM8350_OSC_USER_TRIM_MASK               0x000F

/*
 * R248 (0xF8) - DCDC1 Force PWM
 */
#घोषणा WM8350_DCDC1_FORCE_PWM_ENA              0x0010

/*
 * R250 (0xFA) - DCDC3 Force PWM
 */
#घोषणा WM8350_DCDC3_FORCE_PWM_ENA              0x0010

/*
 * R251 (0xFB) - DCDC4 Force PWM
 */
#घोषणा WM8350_DCDC4_FORCE_PWM_ENA              0x0010

/*
 * R253 (0xFD) - DCDC1 Force PWM
 */
#घोषणा WM8350_DCDC6_FORCE_PWM_ENA              0x0010

/*
 * DCDC's
 */
#घोषणा WM8350_DCDC_1				0
#घोषणा WM8350_DCDC_2				1
#घोषणा WM8350_DCDC_3				2
#घोषणा WM8350_DCDC_4				3
#घोषणा WM8350_DCDC_5				4
#घोषणा WM8350_DCDC_6				5

/* DCDC modes */
#घोषणा WM8350_DCDC_ACTIVE_STANDBY		0
#घोषणा WM8350_DCDC_ACTIVE_PULSE		1
#घोषणा WM8350_DCDC_SLEEP_NORMAL		0
#घोषणा WM8350_DCDC_SLEEP_LOW			1

/* DCDC Low घातer (Hibernate) mode */
#घोषणा WM8350_DCDC_HIB_MODE_CUR		(0 << 12)
#घोषणा WM8350_DCDC_HIB_MODE_IMAGE		(1 << 12)
#घोषणा WM8350_DCDC_HIB_MODE_STANDBY		(2 << 12)
#घोषणा WM8350_DCDC_HIB_MODE_LDO		(4 << 12)
#घोषणा WM8350_DCDC_HIB_MODE_LDO_IM		(5 << 12)
#घोषणा WM8350_DCDC_HIB_MODE_DIS		(7 << 12)
#घोषणा WM8350_DCDC_HIB_MODE_MASK		(7 << 12)

/* DCDC Low Power (Hibernate) संकेत */
#घोषणा WM8350_DCDC_HIB_SIG_REG			(0 << 8)
#घोषणा WM8350_DCDC_HIB_SIG_LPWR1		(1 << 8)
#घोषणा WM8350_DCDC_HIB_SIG_LPWR2		(2 << 8)
#घोषणा WM8350_DCDC_HIB_SIG_LPWR3		(3 << 8)

/* LDO Low घातer (Hibernate) mode */
#घोषणा WM8350_LDO_HIB_MODE_IMAGE		(0 << 0)
#घोषणा WM8350_LDO_HIB_MODE_DIS			(1 << 0)

/* LDO Low Power (Hibernate) संकेत */
#घोषणा WM8350_LDO_HIB_SIG_REG			(0 << 8)
#घोषणा WM8350_LDO_HIB_SIG_LPWR1		(1 << 8)
#घोषणा WM8350_LDO_HIB_SIG_LPWR2		(2 << 8)
#घोषणा WM8350_LDO_HIB_SIG_LPWR3		(3 << 8)

/*
 * LDOs
 */
#घोषणा WM8350_LDO_1				6
#घोषणा WM8350_LDO_2				7
#घोषणा WM8350_LDO_3				8
#घोषणा WM8350_LDO_4				9

/*
 * ISINKs
 */
#घोषणा WM8350_ISINK_A				10
#घोषणा WM8350_ISINK_B				11

#घोषणा WM8350_ISINK_MODE_BOOST			0
#घोषणा WM8350_ISINK_MODE_SWITCH		1
#घोषणा WM8350_ISINK_ILIM_NORMAL		0
#घोषणा WM8350_ISINK_ILIM_LOW			1

#घोषणा WM8350_ISINK_FLASH_DISABLE		0
#घोषणा WM8350_ISINK_FLASH_ENABLE		1
#घोषणा WM8350_ISINK_FLASH_TRIG_BIT		0
#घोषणा WM8350_ISINK_FLASH_TRIG_GPIO		1
#घोषणा WM8350_ISINK_FLASH_MODE_EN		(1 << 13)
#घोषणा WM8350_ISINK_FLASH_MODE_DIS		(0 << 13)
#घोषणा WM8350_ISINK_FLASH_DUR_32MS		(0 << 8)
#घोषणा WM8350_ISINK_FLASH_DUR_64MS		(1 << 8)
#घोषणा WM8350_ISINK_FLASH_DUR_96MS		(2 << 8)
#घोषणा WM8350_ISINK_FLASH_DUR_1024MS		(3 << 8)
#घोषणा WM8350_ISINK_FLASH_ON_INSTANT		(0 << 0)
#घोषणा WM8350_ISINK_FLASH_ON_0_25S		(1 << 0)
#घोषणा WM8350_ISINK_FLASH_ON_0_50S		(2 << 0)
#घोषणा WM8350_ISINK_FLASH_ON_1_00S		(3 << 0)
#घोषणा WM8350_ISINK_FLASH_ON_1_95S		(1 << 0)
#घोषणा WM8350_ISINK_FLASH_ON_3_91S		(2 << 0)
#घोषणा WM8350_ISINK_FLASH_ON_7_80S		(3 << 0)
#घोषणा WM8350_ISINK_FLASH_OFF_INSTANT		(0 << 4)
#घोषणा WM8350_ISINK_FLASH_OFF_0_25S		(1 << 4)
#घोषणा WM8350_ISINK_FLASH_OFF_0_50S		(2 << 4)
#घोषणा WM8350_ISINK_FLASH_OFF_1_00S		(3 << 4)
#घोषणा WM8350_ISINK_FLASH_OFF_1_95S		(1 << 4)
#घोषणा WM8350_ISINK_FLASH_OFF_3_91S		(2 << 4)
#घोषणा WM8350_ISINK_FLASH_OFF_7_80S		(3 << 4)

/*
 * Regulator Interrupts.
 */
#घोषणा WM8350_IRQ_CS1				13
#घोषणा WM8350_IRQ_CS2				14
#घोषणा WM8350_IRQ_UV_LDO4			25
#घोषणा WM8350_IRQ_UV_LDO3			26
#घोषणा WM8350_IRQ_UV_LDO2			27
#घोषणा WM8350_IRQ_UV_LDO1			28
#घोषणा WM8350_IRQ_UV_DC6			29
#घोषणा WM8350_IRQ_UV_DC5			30
#घोषणा WM8350_IRQ_UV_DC4			31
#घोषणा WM8350_IRQ_UV_DC3			32
#घोषणा WM8350_IRQ_UV_DC2			33
#घोषणा WM8350_IRQ_UV_DC1			34
#घोषणा WM8350_IRQ_OC_LS			35

#घोषणा NUM_WM8350_REGULATORS			12

काष्ठा wm8350;
काष्ठा platक्रमm_device;
काष्ठा regulator_init_data;

/*
 * WM8350 LED platक्रमm data
 */
काष्ठा wm8350_led_platक्रमm_data अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *शेष_trigger;
	पूर्णांक max_uA;
पूर्ण;

काष्ठा wm8350_led अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा work_काष्ठा work;
	spinlock_t value_lock;
	क्रमागत led_brightness value;
	काष्ठा led_classdev cdev;
	पूर्णांक max_uA_index;
	पूर्णांक enabled;

	काष्ठा regulator *isink;
	काष्ठा regulator_consumer_supply isink_consumer;
	काष्ठा regulator_init_data isink_init;
	काष्ठा regulator *dcdc;
	काष्ठा regulator_consumer_supply dcdc_consumer;
	काष्ठा regulator_init_data dcdc_init;
पूर्ण;

काष्ठा wm8350_pmic अणु
	/* Number of regulators of each type on this device */
	पूर्णांक max_dcdc;
	पूर्णांक max_isink;

	/* ISINK to DCDC mapping */
	पूर्णांक isink_A_dcdc;
	पूर्णांक isink_B_dcdc;

	/* hibernate configs */
	u16 dcdc1_hib_mode;
	u16 dcdc3_hib_mode;
	u16 dcdc4_hib_mode;
	u16 dcdc6_hib_mode;

	/* regulator devices */
	काष्ठा platक्रमm_device *pdev[NUM_WM8350_REGULATORS];

	/* LED devices */
	काष्ठा wm8350_led led[2];
पूर्ण;

पूर्णांक wm8350_रेजिस्टर_regulator(काष्ठा wm8350 *wm8350, पूर्णांक reg,
			      काष्ठा regulator_init_data *initdata);
पूर्णांक wm8350_रेजिस्टर_led(काष्ठा wm8350 *wm8350, पूर्णांक lednum, पूर्णांक dcdc, पूर्णांक isink,
			काष्ठा wm8350_led_platक्रमm_data *pdata);

/*
 * Additional DCDC control not supported via regulator API
 */
पूर्णांक wm8350_dcdc_set_slot(काष्ठा wm8350 *wm8350, पूर्णांक dcdc, u16 start,
			 u16 stop, u16 fault);
पूर्णांक wm8350_dcdc25_set_mode(काष्ठा wm8350 *wm8350, पूर्णांक dcdc, u16 mode,
			   u16 ilim, u16 ramp, u16 feedback);

/*
 * Additional LDO control not supported via regulator API
 */
पूर्णांक wm8350_lकरो_set_slot(काष्ठा wm8350 *wm8350, पूर्णांक lकरो, u16 start, u16 stop);

/*
 * Additional ISINK control not supported via regulator API
 */
पूर्णांक wm8350_isink_set_flash(काष्ठा wm8350 *wm8350, पूर्णांक isink, u16 mode,
			   u16 trigger, u16 duration, u16 on_ramp,
			   u16 off_ramp, u16 drive);

#पूर्ण_अगर
