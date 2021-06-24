<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * rtc.h  --  RTC driver क्रम Wolfson WM8350 PMIC
 *
 * Copyright 2007 Wolfson Microelectronics PLC
 */

#अगर_अघोषित __LINUX_MFD_WM8350_RTC_H
#घोषणा __LINUX_MFD_WM8350_RTC_H

#समावेश <linux/platक्रमm_device.h>

/*
 * Register values.
 */
#घोषणा WM8350_RTC_SECONDS_MINUTES              0x10
#घोषणा WM8350_RTC_HOURS_DAY                    0x11
#घोषणा WM8350_RTC_DATE_MONTH                   0x12
#घोषणा WM8350_RTC_YEAR                         0x13
#घोषणा WM8350_ALARM_SECONDS_MINUTES            0x14
#घोषणा WM8350_ALARM_HOURS_DAY                  0x15
#घोषणा WM8350_ALARM_DATE_MONTH                 0x16
#घोषणा WM8350_RTC_TIME_CONTROL                 0x17

/*
 * R16 (0x10) - RTC Seconds/Minutes
 */
#घोषणा WM8350_RTC_MINS_MASK                    0x7F00
#घोषणा WM8350_RTC_MINS_SHIFT                        8
#घोषणा WM8350_RTC_SECS_MASK                    0x007F
#घोषणा WM8350_RTC_SECS_SHIFT                        0

/*
 * R17 (0x11) - RTC Hours/Day
 */
#घोषणा WM8350_RTC_DAY_MASK                     0x0700
#घोषणा WM8350_RTC_DAY_SHIFT                         8
#घोषणा WM8350_RTC_HPM_MASK                     0x0020
#घोषणा WM8350_RTC_HPM_SHIFT                         5
#घोषणा WM8350_RTC_HRS_MASK                     0x001F
#घोषणा WM8350_RTC_HRS_SHIFT                         0

/* Bit values क्रम R21 (0x15) */
#घोषणा WM8350_RTC_DAY_SUN                           1
#घोषणा WM8350_RTC_DAY_MON                           2
#घोषणा WM8350_RTC_DAY_TUE                           3
#घोषणा WM8350_RTC_DAY_WED                           4
#घोषणा WM8350_RTC_DAY_THU                           5
#घोषणा WM8350_RTC_DAY_FRI                           6
#घोषणा WM8350_RTC_DAY_SAT                           7

#घोषणा WM8350_RTC_HPM_AM                            0
#घोषणा WM8350_RTC_HPM_PM                            1

/*
 * R18 (0x12) - RTC Date/Month
 */
#घोषणा WM8350_RTC_MTH_MASK                     0x1F00
#घोषणा WM8350_RTC_MTH_SHIFT                         8
#घोषणा WM8350_RTC_DATE_MASK                    0x003F
#घोषणा WM8350_RTC_DATE_SHIFT                        0

/* Bit values क्रम R22 (0x16) */
#घोषणा WM8350_RTC_MTH_JAN                           1
#घोषणा WM8350_RTC_MTH_FEB                           2
#घोषणा WM8350_RTC_MTH_MAR                           3
#घोषणा WM8350_RTC_MTH_APR                           4
#घोषणा WM8350_RTC_MTH_MAY                           5
#घोषणा WM8350_RTC_MTH_JUN                           6
#घोषणा WM8350_RTC_MTH_JUL                           7
#घोषणा WM8350_RTC_MTH_AUG                           8
#घोषणा WM8350_RTC_MTH_SEP                           9
#घोषणा WM8350_RTC_MTH_OCT                          10
#घोषणा WM8350_RTC_MTH_NOV                          11
#घोषणा WM8350_RTC_MTH_DEC                          12
#घोषणा WM8350_RTC_MTH_JAN_BCD                    0x01
#घोषणा WM8350_RTC_MTH_FEB_BCD                    0x02
#घोषणा WM8350_RTC_MTH_MAR_BCD                    0x03
#घोषणा WM8350_RTC_MTH_APR_BCD                    0x04
#घोषणा WM8350_RTC_MTH_MAY_BCD                    0x05
#घोषणा WM8350_RTC_MTH_JUN_BCD                    0x06
#घोषणा WM8350_RTC_MTH_JUL_BCD                    0x07
#घोषणा WM8350_RTC_MTH_AUG_BCD                    0x08
#घोषणा WM8350_RTC_MTH_SEP_BCD                    0x09
#घोषणा WM8350_RTC_MTH_OCT_BCD                    0x10
#घोषणा WM8350_RTC_MTH_NOV_BCD                    0x11
#घोषणा WM8350_RTC_MTH_DEC_BCD                    0x12

/*
 * R19 (0x13) - RTC Year
 */
#घोषणा WM8350_RTC_YHUNDREDS_MASK               0x3F00
#घोषणा WM8350_RTC_YHUNDREDS_SHIFT                   8
#घोषणा WM8350_RTC_YUNITS_MASK                  0x00FF
#घोषणा WM8350_RTC_YUNITS_SHIFT                      0

/*
 * R20 (0x14) - Alarm Seconds/Minutes
 */
#घोषणा WM8350_RTC_ALMMINS_MASK                 0x7F00
#घोषणा WM8350_RTC_ALMMINS_SHIFT                     8
#घोषणा WM8350_RTC_ALMSECS_MASK                 0x007F
#घोषणा WM8350_RTC_ALMSECS_SHIFT                     0

/* Bit values क्रम R20 (0x14) */
#घोषणा WM8350_RTC_ALMMINS_DONT_CARE                -1
#घोषणा WM8350_RTC_ALMSECS_DONT_CARE                -1

/*
 * R21 (0x15) - Alarm Hours/Day
 */
#घोषणा WM8350_RTC_ALMDAY_MASK                  0x0F00
#घोषणा WM8350_RTC_ALMDAY_SHIFT                      8
#घोषणा WM8350_RTC_ALMHPM_MASK                  0x0020
#घोषणा WM8350_RTC_ALMHPM_SHIFT                      5
#घोषणा WM8350_RTC_ALMHRS_MASK                  0x001F
#घोषणा WM8350_RTC_ALMHRS_SHIFT                      0

/* Bit values क्रम R21 (0x15) */
#घोषणा WM8350_RTC_ALMDAY_DONT_CARE                 -1
#घोषणा WM8350_RTC_ALMDAY_SUN                        1
#घोषणा WM8350_RTC_ALMDAY_MON                        2
#घोषणा WM8350_RTC_ALMDAY_TUE                        3
#घोषणा WM8350_RTC_ALMDAY_WED                        4
#घोषणा WM8350_RTC_ALMDAY_THU                        5
#घोषणा WM8350_RTC_ALMDAY_FRI                        6
#घोषणा WM8350_RTC_ALMDAY_SAT                        7

#घोषणा WM8350_RTC_ALMHPM_AM                         0
#घोषणा WM8350_RTC_ALMHPM_PM                         1

#घोषणा WM8350_RTC_ALMHRS_DONT_CARE                 -1

/*
 * R22 (0x16) - Alarm Date/Month
 */
#घोषणा WM8350_RTC_ALMMTH_MASK                  0x1F00
#घोषणा WM8350_RTC_ALMMTH_SHIFT                      8
#घोषणा WM8350_RTC_ALMDATE_MASK                 0x003F
#घोषणा WM8350_RTC_ALMDATE_SHIFT                     0

/* Bit values क्रम R22 (0x16) */
#घोषणा WM8350_RTC_ALMDATE_DONT_CARE                -1

#घोषणा WM8350_RTC_ALMMTH_DONT_CARE                 -1
#घोषणा WM8350_RTC_ALMMTH_JAN                        1
#घोषणा WM8350_RTC_ALMMTH_FEB                        2
#घोषणा WM8350_RTC_ALMMTH_MAR                        3
#घोषणा WM8350_RTC_ALMMTH_APR                        4
#घोषणा WM8350_RTC_ALMMTH_MAY                        5
#घोषणा WM8350_RTC_ALMMTH_JUN                        6
#घोषणा WM8350_RTC_ALMMTH_JUL                        7
#घोषणा WM8350_RTC_ALMMTH_AUG                        8
#घोषणा WM8350_RTC_ALMMTH_SEP                        9
#घोषणा WM8350_RTC_ALMMTH_OCT                       10
#घोषणा WM8350_RTC_ALMMTH_NOV                       11
#घोषणा WM8350_RTC_ALMMTH_DEC                       12
#घोषणा WM8350_RTC_ALMMTH_JAN_BCD                 0x01
#घोषणा WM8350_RTC_ALMMTH_FEB_BCD                 0x02
#घोषणा WM8350_RTC_ALMMTH_MAR_BCD                 0x03
#घोषणा WM8350_RTC_ALMMTH_APR_BCD                 0x04
#घोषणा WM8350_RTC_ALMMTH_MAY_BCD                 0x05
#घोषणा WM8350_RTC_ALMMTH_JUN_BCD                 0x06
#घोषणा WM8350_RTC_ALMMTH_JUL_BCD                 0x07
#घोषणा WM8350_RTC_ALMMTH_AUG_BCD                 0x08
#घोषणा WM8350_RTC_ALMMTH_SEP_BCD                 0x09
#घोषणा WM8350_RTC_ALMMTH_OCT_BCD                 0x10
#घोषणा WM8350_RTC_ALMMTH_NOV_BCD                 0x11
#घोषणा WM8350_RTC_ALMMTH_DEC_BCD                 0x12

/*
 * R23 (0x17) - RTC Time Control
 */
#घोषणा WM8350_RTC_BCD                          0x8000
#घोषणा WM8350_RTC_BCD_MASK                     0x8000
#घोषणा WM8350_RTC_BCD_SHIFT                        15
#घोषणा WM8350_RTC_12HR                         0x4000
#घोषणा WM8350_RTC_12HR_MASK                    0x4000
#घोषणा WM8350_RTC_12HR_SHIFT                       14
#घोषणा WM8350_RTC_DST                          0x2000
#घोषणा WM8350_RTC_DST_MASK                     0x2000
#घोषणा WM8350_RTC_DST_SHIFT                        13
#घोषणा WM8350_RTC_SET                          0x0800
#घोषणा WM8350_RTC_SET_MASK                     0x0800
#घोषणा WM8350_RTC_SET_SHIFT                        11
#घोषणा WM8350_RTC_STS                          0x0400
#घोषणा WM8350_RTC_STS_MASK                     0x0400
#घोषणा WM8350_RTC_STS_SHIFT                        10
#घोषणा WM8350_RTC_ALMSET                       0x0200
#घोषणा WM8350_RTC_ALMSET_MASK                  0x0200
#घोषणा WM8350_RTC_ALMSET_SHIFT                      9
#घोषणा WM8350_RTC_ALMSTS                       0x0100
#घोषणा WM8350_RTC_ALMSTS_MASK                  0x0100
#घोषणा WM8350_RTC_ALMSTS_SHIFT                      8
#घोषणा WM8350_RTC_PINT                         0x0070
#घोषणा WM8350_RTC_PINT_MASK                    0x0070
#घोषणा WM8350_RTC_PINT_SHIFT                        4
#घोषणा WM8350_RTC_DSW                          0x000F
#घोषणा WM8350_RTC_DSW_MASK                     0x000F
#घोषणा WM8350_RTC_DSW_SHIFT                         0

/* Bit values क्रम R23 (0x17) */
#घोषणा WM8350_RTC_BCD_BINARY                        0
#घोषणा WM8350_RTC_BCD_BCD                           1

#घोषणा WM8350_RTC_12HR_24HR                         0
#घोषणा WM8350_RTC_12HR_12HR                         1

#घोषणा WM8350_RTC_DST_DISABLED                      0
#घोषणा WM8350_RTC_DST_ENABLED                       1

#घोषणा WM8350_RTC_SET_RUN                           0
#घोषणा WM8350_RTC_SET_SET                           1

#घोषणा WM8350_RTC_STS_RUNNING                       0
#घोषणा WM8350_RTC_STS_STOPPED                       1

#घोषणा WM8350_RTC_ALMSET_RUN                        0
#घोषणा WM8350_RTC_ALMSET_SET                        1

#घोषणा WM8350_RTC_ALMSTS_RUNNING                    0
#घोषणा WM8350_RTC_ALMSTS_STOPPED                    1

#घोषणा WM8350_RTC_PINT_DISABLED                     0
#घोषणा WM8350_RTC_PINT_SECS                         1
#घोषणा WM8350_RTC_Pपूर्णांक_न्यूनS                         2
#घोषणा WM8350_RTC_PINT_HRS                          3
#घोषणा WM8350_RTC_PINT_DAYS                         4
#घोषणा WM8350_RTC_PINT_MTHS                         5

#घोषणा WM8350_RTC_DSW_DISABLED                      0
#घोषणा WM8350_RTC_DSW_1HZ                           1
#घोषणा WM8350_RTC_DSW_2HZ                           2
#घोषणा WM8350_RTC_DSW_4HZ                           3
#घोषणा WM8350_RTC_DSW_8HZ                           4
#घोषणा WM8350_RTC_DSW_16HZ                          5
#घोषणा WM8350_RTC_DSW_32HZ                          6
#घोषणा WM8350_RTC_DSW_64HZ                          7
#घोषणा WM8350_RTC_DSW_128HZ                         8
#घोषणा WM8350_RTC_DSW_256HZ                         9
#घोषणा WM8350_RTC_DSW_512HZ                        10
#घोषणा WM8350_RTC_DSW_1024HZ                       11

/*
 * R218 (0xDA) - RTC Tick Control
 */
#घोषणा WM8350_RTC_TICKSTS                      0x4000
#घोषणा WM8350_RTC_CLKSRC                       0x2000
#घोषणा WM8350_RTC_TRIM_MASK                    0x03FF

/*
 * RTC Interrupts.
 */
#घोषणा WM8350_IRQ_RTC_PER			7
#घोषणा WM8350_IRQ_RTC_SEC			8
#घोषणा WM8350_IRQ_RTC_ALM			9

काष्ठा wm8350_rtc अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा rtc_device *rtc;
	पूर्णांक alarm_enabled;      /* used over suspend/resume */
	पूर्णांक update_enabled;
पूर्ण;

#पूर्ण_अगर
