<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/mfd/wm831x/core.h -- Core पूर्णांकerface क्रम WM831x
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित __MFD_WM831X_CORE_H__
#घोषणा __MFD_WM831X_CORE_H__

#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/list.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/wm831x/auxadc.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/of.h>

/*
 * Register values.
 */
#घोषणा WM831X_RESET_ID                         0x00
#घोषणा WM831X_REVISION                         0x01
#घोषणा WM831X_PARENT_ID                        0x4000
#घोषणा WM831X_SYSVDD_CONTROL                   0x4001
#घोषणा WM831X_THERMAL_MONITORING               0x4002
#घोषणा WM831X_POWER_STATE                      0x4003
#घोषणा WM831X_WATCHDOG                         0x4004
#घोषणा WM831X_ON_PIN_CONTROL                   0x4005
#घोषणा WM831X_RESET_CONTROL                    0x4006
#घोषणा WM831X_CONTROL_INTERFACE                0x4007
#घोषणा WM831X_SECURITY_KEY                     0x4008
#घोषणा WM831X_SOFTWARE_SCRATCH                 0x4009
#घोषणा WM831X_OTP_CONTROL                      0x400A
#घोषणा WM831X_GPIO_LEVEL                       0x400C
#घोषणा WM831X_SYSTEM_STATUS                    0x400D
#घोषणा WM831X_ON_SOURCE                        0x400E
#घोषणा WM831X_OFF_SOURCE                       0x400F
#घोषणा WM831X_SYSTEM_INTERRUPTS                0x4010
#घोषणा WM831X_INTERRUPT_STATUS_1               0x4011
#घोषणा WM831X_INTERRUPT_STATUS_2               0x4012
#घोषणा WM831X_INTERRUPT_STATUS_3               0x4013
#घोषणा WM831X_INTERRUPT_STATUS_4               0x4014
#घोषणा WM831X_INTERRUPT_STATUS_5               0x4015
#घोषणा WM831X_IRQ_CONFIG                       0x4017
#घोषणा WM831X_SYSTEM_INTERRUPTS_MASK           0x4018
#घोषणा WM831X_INTERRUPT_STATUS_1_MASK          0x4019
#घोषणा WM831X_INTERRUPT_STATUS_2_MASK          0x401A
#घोषणा WM831X_INTERRUPT_STATUS_3_MASK          0x401B
#घोषणा WM831X_INTERRUPT_STATUS_4_MASK          0x401C
#घोषणा WM831X_INTERRUPT_STATUS_5_MASK          0x401D
#घोषणा WM831X_RTC_WRITE_COUNTER                0x4020
#घोषणा WM831X_RTC_TIME_1                       0x4021
#घोषणा WM831X_RTC_TIME_2                       0x4022
#घोषणा WM831X_RTC_ALARM_1                      0x4023
#घोषणा WM831X_RTC_ALARM_2                      0x4024
#घोषणा WM831X_RTC_CONTROL                      0x4025
#घोषणा WM831X_RTC_TRIM                         0x4026
#घोषणा WM831X_TOUCH_CONTROL_1                  0x4028
#घोषणा WM831X_TOUCH_CONTROL_2                  0x4029
#घोषणा WM831X_TOUCH_DATA_X                     0x402A
#घोषणा WM831X_TOUCH_DATA_Y                     0x402B
#घोषणा WM831X_TOUCH_DATA_Z                     0x402C
#घोषणा WM831X_AUXADC_DATA                      0x402D
#घोषणा WM831X_AUXADC_CONTROL                   0x402E
#घोषणा WM831X_AUXADC_SOURCE                    0x402F
#घोषणा WM831X_COMPARATOR_CONTROL               0x4030
#घोषणा WM831X_COMPARATOR_1                     0x4031
#घोषणा WM831X_COMPARATOR_2                     0x4032
#घोषणा WM831X_COMPARATOR_3                     0x4033
#घोषणा WM831X_COMPARATOR_4                     0x4034
#घोषणा WM831X_GPIO1_CONTROL                    0x4038
#घोषणा WM831X_GPIO2_CONTROL                    0x4039
#घोषणा WM831X_GPIO3_CONTROL                    0x403A
#घोषणा WM831X_GPIO4_CONTROL                    0x403B
#घोषणा WM831X_GPIO5_CONTROL                    0x403C
#घोषणा WM831X_GPIO6_CONTROL                    0x403D
#घोषणा WM831X_GPIO7_CONTROL                    0x403E
#घोषणा WM831X_GPIO8_CONTROL                    0x403F
#घोषणा WM831X_GPIO9_CONTROL                    0x4040
#घोषणा WM831X_GPIO10_CONTROL                   0x4041
#घोषणा WM831X_GPIO11_CONTROL                   0x4042
#घोषणा WM831X_GPIO12_CONTROL                   0x4043
#घोषणा WM831X_GPIO13_CONTROL                   0x4044
#घोषणा WM831X_GPIO14_CONTROL                   0x4045
#घोषणा WM831X_GPIO15_CONTROL                   0x4046
#घोषणा WM831X_GPIO16_CONTROL                   0x4047
#घोषणा WM831X_CHARGER_CONTROL_1                0x4048
#घोषणा WM831X_CHARGER_CONTROL_2                0x4049
#घोषणा WM831X_CHARGER_STATUS                   0x404A
#घोषणा WM831X_BACKUP_CHARGER_CONTROL           0x404B
#घोषणा WM831X_STATUS_LED_1                     0x404C
#घोषणा WM831X_STATUS_LED_2                     0x404D
#घोषणा WM831X_CURRENT_SINK_1                   0x404E
#घोषणा WM831X_CURRENT_SINK_2                   0x404F
#घोषणा WM831X_DCDC_ENABLE                      0x4050
#घोषणा WM831X_LDO_ENABLE                       0x4051
#घोषणा WM831X_DCDC_STATUS                      0x4052
#घोषणा WM831X_LDO_STATUS                       0x4053
#घोषणा WM831X_DCDC_UV_STATUS                   0x4054
#घोषणा WM831X_LDO_UV_STATUS                    0x4055
#घोषणा WM831X_DC1_CONTROL_1                    0x4056
#घोषणा WM831X_DC1_CONTROL_2                    0x4057
#घोषणा WM831X_DC1_ON_CONFIG                    0x4058
#घोषणा WM831X_DC1_SLEEP_CONTROL                0x4059
#घोषणा WM831X_DC1_DVS_CONTROL                  0x405A
#घोषणा WM831X_DC2_CONTROL_1                    0x405B
#घोषणा WM831X_DC2_CONTROL_2                    0x405C
#घोषणा WM831X_DC2_ON_CONFIG                    0x405D
#घोषणा WM831X_DC2_SLEEP_CONTROL                0x405E
#घोषणा WM831X_DC2_DVS_CONTROL                  0x405F
#घोषणा WM831X_DC3_CONTROL_1                    0x4060
#घोषणा WM831X_DC3_CONTROL_2                    0x4061
#घोषणा WM831X_DC3_ON_CONFIG                    0x4062
#घोषणा WM831X_DC3_SLEEP_CONTROL                0x4063
#घोषणा WM831X_DC4_CONTROL                      0x4064
#घोषणा WM831X_DC4_SLEEP_CONTROL                0x4065
#घोषणा WM832X_DC4_SLEEP_CONTROL                0x4067
#घोषणा WM831X_EPE1_CONTROL                     0x4066
#घोषणा WM831X_EPE2_CONTROL                     0x4067
#घोषणा WM831X_LDO1_CONTROL                     0x4068
#घोषणा WM831X_LDO1_ON_CONTROL                  0x4069
#घोषणा WM831X_LDO1_SLEEP_CONTROL               0x406A
#घोषणा WM831X_LDO2_CONTROL                     0x406B
#घोषणा WM831X_LDO2_ON_CONTROL                  0x406C
#घोषणा WM831X_LDO2_SLEEP_CONTROL               0x406D
#घोषणा WM831X_LDO3_CONTROL                     0x406E
#घोषणा WM831X_LDO3_ON_CONTROL                  0x406F
#घोषणा WM831X_LDO3_SLEEP_CONTROL               0x4070
#घोषणा WM831X_LDO4_CONTROL                     0x4071
#घोषणा WM831X_LDO4_ON_CONTROL                  0x4072
#घोषणा WM831X_LDO4_SLEEP_CONTROL               0x4073
#घोषणा WM831X_LDO5_CONTROL                     0x4074
#घोषणा WM831X_LDO5_ON_CONTROL                  0x4075
#घोषणा WM831X_LDO5_SLEEP_CONTROL               0x4076
#घोषणा WM831X_LDO6_CONTROL                     0x4077
#घोषणा WM831X_LDO6_ON_CONTROL                  0x4078
#घोषणा WM831X_LDO6_SLEEP_CONTROL               0x4079
#घोषणा WM831X_LDO7_CONTROL                     0x407A
#घोषणा WM831X_LDO7_ON_CONTROL                  0x407B
#घोषणा WM831X_LDO7_SLEEP_CONTROL               0x407C
#घोषणा WM831X_LDO8_CONTROL                     0x407D
#घोषणा WM831X_LDO8_ON_CONTROL                  0x407E
#घोषणा WM831X_LDO8_SLEEP_CONTROL               0x407F
#घोषणा WM831X_LDO9_CONTROL                     0x4080
#घोषणा WM831X_LDO9_ON_CONTROL                  0x4081
#घोषणा WM831X_LDO9_SLEEP_CONTROL               0x4082
#घोषणा WM831X_LDO10_CONTROL                    0x4083
#घोषणा WM831X_LDO10_ON_CONTROL                 0x4084
#घोषणा WM831X_LDO10_SLEEP_CONTROL              0x4085
#घोषणा WM831X_LDO11_ON_CONTROL                 0x4087
#घोषणा WM831X_LDO11_SLEEP_CONTROL              0x4088
#घोषणा WM831X_POWER_GOOD_SOURCE_1              0x408E
#घोषणा WM831X_POWER_GOOD_SOURCE_2              0x408F
#घोषणा WM831X_CLOCK_CONTROL_1                  0x4090
#घोषणा WM831X_CLOCK_CONTROL_2                  0x4091
#घोषणा WM831X_FLL_CONTROL_1                    0x4092
#घोषणा WM831X_FLL_CONTROL_2                    0x4093
#घोषणा WM831X_FLL_CONTROL_3                    0x4094
#घोषणा WM831X_FLL_CONTROL_4                    0x4095
#घोषणा WM831X_FLL_CONTROL_5                    0x4096
#घोषणा WM831X_UNIQUE_ID_1                      0x7800
#घोषणा WM831X_UNIQUE_ID_2                      0x7801
#घोषणा WM831X_UNIQUE_ID_3                      0x7802
#घोषणा WM831X_UNIQUE_ID_4                      0x7803
#घोषणा WM831X_UNIQUE_ID_5                      0x7804
#घोषणा WM831X_UNIQUE_ID_6                      0x7805
#घोषणा WM831X_UNIQUE_ID_7                      0x7806
#घोषणा WM831X_UNIQUE_ID_8                      0x7807
#घोषणा WM831X_FACTORY_OTP_ID                   0x7808
#घोषणा WM831X_FACTORY_OTP_1                    0x7809
#घोषणा WM831X_FACTORY_OTP_2                    0x780A
#घोषणा WM831X_FACTORY_OTP_3                    0x780B
#घोषणा WM831X_FACTORY_OTP_4                    0x780C
#घोषणा WM831X_FACTORY_OTP_5                    0x780D
#घोषणा WM831X_CUSTOMER_OTP_ID                  0x7810
#घोषणा WM831X_DC1_OTP_CONTROL                  0x7811
#घोषणा WM831X_DC2_OTP_CONTROL                  0x7812
#घोषणा WM831X_DC3_OTP_CONTROL                  0x7813
#घोषणा WM831X_LDO1_2_OTP_CONTROL               0x7814
#घोषणा WM831X_LDO3_4_OTP_CONTROL               0x7815
#घोषणा WM831X_LDO5_6_OTP_CONTROL               0x7816
#घोषणा WM831X_LDO7_8_OTP_CONTROL               0x7817
#घोषणा WM831X_LDO9_10_OTP_CONTROL              0x7818
#घोषणा WM831X_LDO11_EPE_CONTROL                0x7819
#घोषणा WM831X_GPIO1_OTP_CONTROL                0x781A
#घोषणा WM831X_GPIO2_OTP_CONTROL                0x781B
#घोषणा WM831X_GPIO3_OTP_CONTROL                0x781C
#घोषणा WM831X_GPIO4_OTP_CONTROL                0x781D
#घोषणा WM831X_GPIO5_OTP_CONTROL                0x781E
#घोषणा WM831X_GPIO6_OTP_CONTROL                0x781F
#घोषणा WM831X_DBE_CHECK_DATA                   0x7827

/*
 * R0 (0x00) - Reset ID
 */
#घोषणा WM831X_CHIP_ID_MASK                     0xFFFF  /* CHIP_ID - [15:0] */
#घोषणा WM831X_CHIP_ID_SHIFT                         0  /* CHIP_ID - [15:0] */
#घोषणा WM831X_CHIP_ID_WIDTH                        16  /* CHIP_ID - [15:0] */

/*
 * R1 (0x01) - Revision
 */
#घोषणा WM831X_PARENT_REV_MASK                  0xFF00  /* PARENT_REV - [15:8] */
#घोषणा WM831X_PARENT_REV_SHIFT                      8  /* PARENT_REV - [15:8] */
#घोषणा WM831X_PARENT_REV_WIDTH                      8  /* PARENT_REV - [15:8] */
#घोषणा WM831X_CHILD_REV_MASK                   0x00FF  /* CHILD_REV - [7:0] */
#घोषणा WM831X_CHILD_REV_SHIFT                       0  /* CHILD_REV - [7:0] */
#घोषणा WM831X_CHILD_REV_WIDTH                       8  /* CHILD_REV - [7:0] */

/*
 * R16384 (0x4000) - Parent ID
 */
#घोषणा WM831X_PARENT_ID_MASK                   0xFFFF  /* PARENT_ID - [15:0] */
#घोषणा WM831X_PARENT_ID_SHIFT                       0  /* PARENT_ID - [15:0] */
#घोषणा WM831X_PARENT_ID_WIDTH                      16  /* PARENT_ID - [15:0] */

/*
 * R16389 (0x4005) - ON Pin Control
 */
#घोषणा WM831X_ON_PIN_SECACT_MASK               0x0300  /* ON_PIN_SECACT - [9:8] */
#घोषणा WM831X_ON_PIN_SECACT_SHIFT                   8  /* ON_PIN_SECACT - [9:8] */
#घोषणा WM831X_ON_PIN_SECACT_WIDTH                   2  /* ON_PIN_SECACT - [9:8] */
#घोषणा WM831X_ON_PIN_PRIMACT_MASK              0x0030  /* ON_PIN_PRIMACT - [5:4] */
#घोषणा WM831X_ON_PIN_PRIMACT_SHIFT                  4  /* ON_PIN_PRIMACT - [5:4] */
#घोषणा WM831X_ON_PIN_PRIMACT_WIDTH                  2  /* ON_PIN_PRIMACT - [5:4] */
#घोषणा WM831X_ON_PIN_STS                       0x0008  /* ON_PIN_STS */
#घोषणा WM831X_ON_PIN_STS_MASK                  0x0008  /* ON_PIN_STS */
#घोषणा WM831X_ON_PIN_STS_SHIFT                      3  /* ON_PIN_STS */
#घोषणा WM831X_ON_PIN_STS_WIDTH                      1  /* ON_PIN_STS */
#घोषणा WM831X_ON_PIN_TO_MASK                   0x0003  /* ON_PIN_TO - [1:0] */
#घोषणा WM831X_ON_PIN_TO_SHIFT                       0  /* ON_PIN_TO - [1:0] */
#घोषणा WM831X_ON_PIN_TO_WIDTH                       2  /* ON_PIN_TO - [1:0] */

/*
 * R16528 (0x4090) - Clock Control 1
 */
#घोषणा WM831X_CLKOUT_ENA                       0x8000  /* CLKOUT_ENA */
#घोषणा WM831X_CLKOUT_ENA_MASK                  0x8000  /* CLKOUT_ENA */
#घोषणा WM831X_CLKOUT_ENA_SHIFT                     15  /* CLKOUT_ENA */
#घोषणा WM831X_CLKOUT_ENA_WIDTH                      1  /* CLKOUT_ENA */
#घोषणा WM831X_CLKOUT_OD                        0x2000  /* CLKOUT_OD */
#घोषणा WM831X_CLKOUT_OD_MASK                   0x2000  /* CLKOUT_OD */
#घोषणा WM831X_CLKOUT_OD_SHIFT                      13  /* CLKOUT_OD */
#घोषणा WM831X_CLKOUT_OD_WIDTH                       1  /* CLKOUT_OD */
#घोषणा WM831X_CLKOUT_SLOT_MASK                 0x0700  /* CLKOUT_SLOT - [10:8] */
#घोषणा WM831X_CLKOUT_SLOT_SHIFT                     8  /* CLKOUT_SLOT - [10:8] */
#घोषणा WM831X_CLKOUT_SLOT_WIDTH                     3  /* CLKOUT_SLOT - [10:8] */
#घोषणा WM831X_CLKOUT_SLPSLOT_MASK              0x0070  /* CLKOUT_SLPSLOT - [6:4] */
#घोषणा WM831X_CLKOUT_SLPSLOT_SHIFT                  4  /* CLKOUT_SLPSLOT - [6:4] */
#घोषणा WM831X_CLKOUT_SLPSLOT_WIDTH                  3  /* CLKOUT_SLPSLOT - [6:4] */
#घोषणा WM831X_CLKOUT_SRC                       0x0001  /* CLKOUT_SRC */
#घोषणा WM831X_CLKOUT_SRC_MASK                  0x0001  /* CLKOUT_SRC */
#घोषणा WM831X_CLKOUT_SRC_SHIFT                      0  /* CLKOUT_SRC */
#घोषणा WM831X_CLKOUT_SRC_WIDTH                      1  /* CLKOUT_SRC */

/*
 * R16529 (0x4091) - Clock Control 2
 */
#घोषणा WM831X_XTAL_INH                         0x8000  /* XTAL_INH */
#घोषणा WM831X_XTAL_INH_MASK                    0x8000  /* XTAL_INH */
#घोषणा WM831X_XTAL_INH_SHIFT                       15  /* XTAL_INH */
#घोषणा WM831X_XTAL_INH_WIDTH                        1  /* XTAL_INH */
#घोषणा WM831X_XTAL_ENA                         0x2000  /* XTAL_ENA */
#घोषणा WM831X_XTAL_ENA_MASK                    0x2000  /* XTAL_ENA */
#घोषणा WM831X_XTAL_ENA_SHIFT                       13  /* XTAL_ENA */
#घोषणा WM831X_XTAL_ENA_WIDTH                        1  /* XTAL_ENA */
#घोषणा WM831X_XTAL_BKUPENA                     0x1000  /* XTAL_BKUPENA */
#घोषणा WM831X_XTAL_BKUPENA_MASK                0x1000  /* XTAL_BKUPENA */
#घोषणा WM831X_XTAL_BKUPENA_SHIFT                   12  /* XTAL_BKUPENA */
#घोषणा WM831X_XTAL_BKUPENA_WIDTH                    1  /* XTAL_BKUPENA */
#घोषणा WM831X_FLL_AUTO                         0x0080  /* FLL_AUTO */
#घोषणा WM831X_FLL_AUTO_MASK                    0x0080  /* FLL_AUTO */
#घोषणा WM831X_FLL_AUTO_SHIFT                        7  /* FLL_AUTO */
#घोषणा WM831X_FLL_AUTO_WIDTH                        1  /* FLL_AUTO */
#घोषणा WM831X_FLL_AUTO_FREQ_MASK               0x0007  /* FLL_AUTO_FREQ - [2:0] */
#घोषणा WM831X_FLL_AUTO_FREQ_SHIFT                   0  /* FLL_AUTO_FREQ - [2:0] */
#घोषणा WM831X_FLL_AUTO_FREQ_WIDTH                   3  /* FLL_AUTO_FREQ - [2:0] */

/*
 * R16530 (0x4092) - FLL Control 1
 */
#घोषणा WM831X_FLL_FRAC                         0x0004  /* FLL_FRAC */
#घोषणा WM831X_FLL_FRAC_MASK                    0x0004  /* FLL_FRAC */
#घोषणा WM831X_FLL_FRAC_SHIFT                        2  /* FLL_FRAC */
#घोषणा WM831X_FLL_FRAC_WIDTH                        1  /* FLL_FRAC */
#घोषणा WM831X_FLL_OSC_ENA                      0x0002  /* FLL_OSC_ENA */
#घोषणा WM831X_FLL_OSC_ENA_MASK                 0x0002  /* FLL_OSC_ENA */
#घोषणा WM831X_FLL_OSC_ENA_SHIFT                     1  /* FLL_OSC_ENA */
#घोषणा WM831X_FLL_OSC_ENA_WIDTH                     1  /* FLL_OSC_ENA */
#घोषणा WM831X_FLL_ENA                          0x0001  /* FLL_ENA */
#घोषणा WM831X_FLL_ENA_MASK                     0x0001  /* FLL_ENA */
#घोषणा WM831X_FLL_ENA_SHIFT                         0  /* FLL_ENA */
#घोषणा WM831X_FLL_ENA_WIDTH                         1  /* FLL_ENA */

/*
 * R16531 (0x4093) - FLL Control 2
 */
#घोषणा WM831X_FLL_OUTDIV_MASK                  0x3F00  /* FLL_OUTDIV - [13:8] */
#घोषणा WM831X_FLL_OUTDIV_SHIFT                      8  /* FLL_OUTDIV - [13:8] */
#घोषणा WM831X_FLL_OUTDIV_WIDTH                      6  /* FLL_OUTDIV - [13:8] */
#घोषणा WM831X_FLL_CTRL_RATE_MASK               0x0070  /* FLL_CTRL_RATE - [6:4] */
#घोषणा WM831X_FLL_CTRL_RATE_SHIFT                   4  /* FLL_CTRL_RATE - [6:4] */
#घोषणा WM831X_FLL_CTRL_RATE_WIDTH                   3  /* FLL_CTRL_RATE - [6:4] */
#घोषणा WM831X_FLL_FRATIO_MASK                  0x0007  /* FLL_FRATIO - [2:0] */
#घोषणा WM831X_FLL_FRATIO_SHIFT                      0  /* FLL_FRATIO - [2:0] */
#घोषणा WM831X_FLL_FRATIO_WIDTH                      3  /* FLL_FRATIO - [2:0] */

/*
 * R16532 (0x4094) - FLL Control 3
 */
#घोषणा WM831X_FLL_K_MASK                       0xFFFF  /* FLL_K - [15:0] */
#घोषणा WM831X_FLL_K_SHIFT                           0  /* FLL_K - [15:0] */
#घोषणा WM831X_FLL_K_WIDTH                          16  /* FLL_K - [15:0] */

/*
 * R16533 (0x4095) - FLL Control 4
 */
#घोषणा WM831X_FLL_N_MASK                       0x7FE0  /* FLL_N - [14:5] */
#घोषणा WM831X_FLL_N_SHIFT                           5  /* FLL_N - [14:5] */
#घोषणा WM831X_FLL_N_WIDTH                          10  /* FLL_N - [14:5] */
#घोषणा WM831X_FLL_GAIN_MASK                    0x000F  /* FLL_GAIN - [3:0] */
#घोषणा WM831X_FLL_GAIN_SHIFT                        0  /* FLL_GAIN - [3:0] */
#घोषणा WM831X_FLL_GAIN_WIDTH                        4  /* FLL_GAIN - [3:0] */

/*
 * R16534 (0x4096) - FLL Control 5
 */
#घोषणा WM831X_FLL_CLK_REF_DIV_MASK             0x0018  /* FLL_CLK_REF_DIV - [4:3] */
#घोषणा WM831X_FLL_CLK_REF_DIV_SHIFT                 3  /* FLL_CLK_REF_DIV - [4:3] */
#घोषणा WM831X_FLL_CLK_REF_DIV_WIDTH                 2  /* FLL_CLK_REF_DIV - [4:3] */
#घोषणा WM831X_FLL_CLK_SRC_MASK                 0x0003  /* FLL_CLK_SRC - [1:0] */
#घोषणा WM831X_FLL_CLK_SRC_SHIFT                     0  /* FLL_CLK_SRC - [1:0] */
#घोषणा WM831X_FLL_CLK_SRC_WIDTH                     2  /* FLL_CLK_SRC - [1:0] */

काष्ठा regulator_dev;
काष्ठा irq_करोमुख्य;

#घोषणा WM831X_NUM_IRQ_REGS 5
#घोषणा WM831X_NUM_GPIO_REGS 16

क्रमागत wm831x_parent अणु
	WM8310 = 0x8310,
	WM8311 = 0x8311,
	WM8312 = 0x8312,
	WM8320 = 0x8320,
	WM8321 = 0x8321,
	WM8325 = 0x8325,
	WM8326 = 0x8326,
पूर्ण;

काष्ठा wm831x;

प्रकार पूर्णांक (*wm831x_auxadc_पढ़ो_fn)(काष्ठा wm831x *wm831x,
				     क्रमागत wm831x_auxadc input);

काष्ठा wm831x अणु
	काष्ठा mutex io_lock;

	काष्ठा device *dev;

	काष्ठा regmap *regmap;

	काष्ठा wm831x_pdata pdata;
	क्रमागत wm831x_parent type;

	पूर्णांक irq;  /* Our chip IRQ */
	काष्ठा mutex irq_lock;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	पूर्णांक irq_masks_cur[WM831X_NUM_IRQ_REGS];   /* Currently active value */
	पूर्णांक irq_masks_cache[WM831X_NUM_IRQ_REGS]; /* Cached hardware value */

	bool soft_shutकरोwn;

	/* Chip revision based flags */
	अचिन्हित has_gpio_ena:1;         /* Has GPIO enable bit */
	अचिन्हित has_cs_sts:1;           /* Has current sink status bit */
	अचिन्हित अक्षरger_irq_wake:1;     /* Are अक्षरger IRQs a wake source? */

	पूर्णांक num_gpio;

	/* Used by the पूर्णांकerrupt controller code to post ग_लिखोs */
	पूर्णांक gpio_update[WM831X_NUM_GPIO_REGS];
	bool gpio_level_high[WM831X_NUM_GPIO_REGS];
	bool gpio_level_low[WM831X_NUM_GPIO_REGS];

	काष्ठा mutex auxadc_lock;
	काष्ठा list_head auxadc_pending;
	u16 auxadc_active;
	wm831x_auxadc_पढ़ो_fn auxadc_पढ़ो;

	/* The WM831x has a security key blocking access to certain
	 * रेजिस्टरs.  The mutex is taken by the accessors क्रम locking
	 * and unlocking the security key, locked is used to fail
	 * ग_लिखोs अगर the lock is held.
	 */
	काष्ठा mutex key_lock;
	अचिन्हित पूर्णांक locked:1;
पूर्ण;

/* Device I/O API */
पूर्णांक wm831x_reg_पढ़ो(काष्ठा wm831x *wm831x, अचिन्हित लघु reg);
पूर्णांक wm831x_reg_ग_लिखो(काष्ठा wm831x *wm831x, अचिन्हित लघु reg,
		 अचिन्हित लघु val);
व्योम wm831x_reg_lock(काष्ठा wm831x *wm831x);
पूर्णांक wm831x_reg_unlock(काष्ठा wm831x *wm831x);
पूर्णांक wm831x_set_bits(काष्ठा wm831x *wm831x, अचिन्हित लघु reg,
		    अचिन्हित लघु mask, अचिन्हित लघु val);
पूर्णांक wm831x_bulk_पढ़ो(काष्ठा wm831x *wm831x, अचिन्हित लघु reg,
		     पूर्णांक count, u16 *buf);

पूर्णांक wm831x_device_init(काष्ठा wm831x *wm831x, पूर्णांक irq);
पूर्णांक wm831x_device_suspend(काष्ठा wm831x *wm831x);
व्योम wm831x_device_shutकरोwn(काष्ठा wm831x *wm831x);
पूर्णांक wm831x_irq_init(काष्ठा wm831x *wm831x, पूर्णांक irq);
व्योम wm831x_irq_निकास(काष्ठा wm831x *wm831x);
व्योम wm831x_auxadc_init(काष्ठा wm831x *wm831x);

अटल अंतरभूत पूर्णांक wm831x_irq(काष्ठा wm831x *wm831x, पूर्णांक irq)
अणु
	वापस irq_create_mapping(wm831x->irq_करोमुख्य, irq);
पूर्ण

बाह्य काष्ठा regmap_config wm831x_regmap_config;

बाह्य स्थिर काष्ठा of_device_id wm831x_of_match[];

#पूर्ण_अगर
