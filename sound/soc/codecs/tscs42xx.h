<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// tscs42xx.h -- TSCS42xx ALSA SoC Audio driver
// Copyright 2017 Tempo Semiconductor, Inc.
// Author: Steven Eckhoff <steven.eckhoff.खोलोsource@gmail.com>

#अगर_अघोषित __WOOKIE_H__
#घोषणा __WOOKIE_H__

क्रमागत अणु
	TSCS42XX_PLL_SRC_XTAL,
	TSCS42XX_PLL_SRC_MCLK1,
	TSCS42XX_PLL_SRC_MCLK2,
	TSCS42XX_PLL_SRC_CNT,
पूर्ण;

#घोषणा R_HPVOLL        0x0
#घोषणा R_HPVOLR        0x1
#घोषणा R_SPKVOLL       0x2
#घोषणा R_SPKVOLR       0x3
#घोषणा R_DACVOLL       0x4
#घोषणा R_DACVOLR       0x5
#घोषणा R_ADCVOLL       0x6
#घोषणा R_ADCVOLR       0x7
#घोषणा R_INVOLL        0x8
#घोषणा R_INVOLR        0x9
#घोषणा R_INMODE        0x0B
#घोषणा R_INSELL        0x0C
#घोषणा R_INSELR        0x0D
#घोषणा R_AIC1          0x13
#घोषणा R_AIC2          0x14
#घोषणा R_CNVRTR0       0x16
#घोषणा R_ADCSR         0x17
#घोषणा R_CNVRTR1       0x18
#घोषणा R_DACSR         0x19
#घोषणा R_PWRM1         0x1A
#घोषणा R_PWRM2         0x1B
#घोषणा R_CTL		0x1C
#घोषणा R_CONFIG0       0x1F
#घोषणा R_CONFIG1       0x20
#घोषणा R_DMICCTL       0x24
#घोषणा R_CLECTL        0x25
#घोषणा R_MUGAIN        0x26
#घोषणा R_COMPTH        0x27
#घोषणा R_CMPRAT        0x28
#घोषणा R_CATKTCL       0x29
#घोषणा R_CATKTCH       0x2A
#घोषणा R_CRELTCL       0x2B
#घोषणा R_CRELTCH       0x2C
#घोषणा R_LIMTH         0x2D
#घोषणा R_LIMTGT        0x2E
#घोषणा R_LATKTCL       0x2F
#घोषणा R_LATKTCH       0x30
#घोषणा R_LRELTCL       0x31
#घोषणा R_LRELTCH       0x32
#घोषणा R_EXPTH         0x33
#घोषणा R_EXPRAT        0x34
#घोषणा R_XATKTCL       0x35
#घोषणा R_XATKTCH       0x36
#घोषणा R_XRELTCL       0x37
#घोषणा R_XRELTCH       0x38
#घोषणा R_FXCTL         0x39
#घोषणा R_DACCRWRL      0x3A
#घोषणा R_DACCRWRM      0x3B
#घोषणा R_DACCRWRH      0x3C
#घोषणा R_DACCRRDL      0x3D
#घोषणा R_DACCRRDM      0x3E
#घोषणा R_DACCRRDH      0x3F
#घोषणा R_DACCRADDR     0x40
#घोषणा R_DCOFSEL       0x41
#घोषणा R_PLLCTL9       0x4E
#घोषणा R_PLLCTLA       0x4F
#घोषणा R_PLLCTLB       0x50
#घोषणा R_PLLCTLC       0x51
#घोषणा R_PLLCTLD       0x52
#घोषणा R_PLLCTLE       0x53
#घोषणा R_PLLCTLF       0x54
#घोषणा R_PLLCTL10      0x55
#घोषणा R_PLLCTL11      0x56
#घोषणा R_PLLCTL12      0x57
#घोषणा R_PLLCTL1B      0x60
#घोषणा R_PLLCTL1C      0x61
#घोषणा R_TIMEBASE      0x77
#घोषणा R_DEVIDL        0x7D
#घोषणा R_DEVIDH        0x7E
#घोषणा R_RESET         0x80
#घोषणा R_DACCRSTAT     0x8A
#घोषणा R_PLLCTL0       0x8E
#घोषणा R_PLLREFSEL     0x8F
#घोषणा R_DACMBCEN      0xC7
#घोषणा R_DACMBCCTL     0xC8
#घोषणा R_DACMBCMUG1    0xC9
#घोषणा R_DACMBCTHR1    0xCA
#घोषणा R_DACMBCRAT1    0xCB
#घोषणा R_DACMBCATK1L   0xCC
#घोषणा R_DACMBCATK1H   0xCD
#घोषणा R_DACMBCREL1L   0xCE
#घोषणा R_DACMBCREL1H   0xCF
#घोषणा R_DACMBCMUG2    0xD0
#घोषणा R_DACMBCTHR2    0xD1
#घोषणा R_DACMBCRAT2    0xD2
#घोषणा R_DACMBCATK2L   0xD3
#घोषणा R_DACMBCATK2H   0xD4
#घोषणा R_DACMBCREL2L   0xD5
#घोषणा R_DACMBCREL2H   0xD6
#घोषणा R_DACMBCMUG3    0xD7
#घोषणा R_DACMBCTHR3    0xD8
#घोषणा R_DACMBCRAT3    0xD9
#घोषणा R_DACMBCATK3L   0xDA
#घोषणा R_DACMBCATK3H   0xDB
#घोषणा R_DACMBCREL3L   0xDC
#घोषणा R_DACMBCREL3H   0xDD

/* Helpers */
#घोषणा RM(m, b) ((m)<<(b))
#घोषणा RV(v, b) ((v)<<(b))

/****************************
 *      R_HPVOLL (0x0)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_HPVOLL                            0

/* Field Masks */
#घोषणा FM_HPVOLL                            0X7F

/* Field Values */
#घोषणा FV_HPVOLL_P6DB                       0x7F
#घोषणा FV_HPVOLL_N88PT5DB                   0x1
#घोषणा FV_HPVOLL_MUTE                       0x0

/* Register Masks */
#घोषणा RM_HPVOLL                            RM(FM_HPVOLL, FB_HPVOLL)

/* Register Values */
#घोषणा RV_HPVOLL_P6DB                       RV(FV_HPVOLL_P6DB, FB_HPVOLL)
#घोषणा RV_HPVOLL_N88PT5DB                   RV(FV_HPVOLL_N88PT5DB, FB_HPVOLL)
#घोषणा RV_HPVOLL_MUTE                       RV(FV_HPVOLL_MUTE, FB_HPVOLL)

/****************************
 *      R_HPVOLR (0x1)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_HPVOLR                            0

/* Field Masks */
#घोषणा FM_HPVOLR                            0X7F

/* Field Values */
#घोषणा FV_HPVOLR_P6DB                       0x7F
#घोषणा FV_HPVOLR_N88PT5DB                   0x1
#घोषणा FV_HPVOLR_MUTE                       0x0

/* Register Masks */
#घोषणा RM_HPVOLR                            RM(FM_HPVOLR, FB_HPVOLR)

/* Register Values */
#घोषणा RV_HPVOLR_P6DB                       RV(FV_HPVOLR_P6DB, FB_HPVOLR)
#घोषणा RV_HPVOLR_N88PT5DB                   RV(FV_HPVOLR_N88PT5DB, FB_HPVOLR)
#घोषणा RV_HPVOLR_MUTE                       RV(FV_HPVOLR_MUTE, FB_HPVOLR)

/*****************************
 *      R_SPKVOLL (0x2)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_SPKVOLL                           0

/* Field Masks */
#घोषणा FM_SPKVOLL                           0X7F

/* Field Values */
#घोषणा FV_SPKVOLL_P12DB                     0x7F
#घोषणा FV_SPKVOLL_N77PT25DB                 0x8
#घोषणा FV_SPKVOLL_MUTE                      0x0

/* Register Masks */
#घोषणा RM_SPKVOLL                           RM(FM_SPKVOLL, FB_SPKVOLL)

/* Register Values */
#घोषणा RV_SPKVOLL_P12DB                     RV(FV_SPKVOLL_P12DB, FB_SPKVOLL)
#घोषणा RV_SPKVOLL_N77PT25DB \
	 RV(FV_SPKVOLL_N77PT25DB, FB_SPKVOLL)

#घोषणा RV_SPKVOLL_MUTE                      RV(FV_SPKVOLL_MUTE, FB_SPKVOLL)

/*****************************
 *      R_SPKVOLR (0x3)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_SPKVOLR                           0

/* Field Masks */
#घोषणा FM_SPKVOLR                           0X7F

/* Field Values */
#घोषणा FV_SPKVOLR_P12DB                     0x7F
#घोषणा FV_SPKVOLR_N77PT25DB                 0x8
#घोषणा FV_SPKVOLR_MUTE                      0x0

/* Register Masks */
#घोषणा RM_SPKVOLR                           RM(FM_SPKVOLR, FB_SPKVOLR)

/* Register Values */
#घोषणा RV_SPKVOLR_P12DB                     RV(FV_SPKVOLR_P12DB, FB_SPKVOLR)
#घोषणा RV_SPKVOLR_N77PT25DB \
	 RV(FV_SPKVOLR_N77PT25DB, FB_SPKVOLR)

#घोषणा RV_SPKVOLR_MUTE                      RV(FV_SPKVOLR_MUTE, FB_SPKVOLR)

/*****************************
 *      R_DACVOLL (0x4)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_DACVOLL                           0

/* Field Masks */
#घोषणा FM_DACVOLL                           0XFF

/* Field Values */
#घोषणा FV_DACVOLL_0DB                       0xFF
#घोषणा FV_DACVOLL_N95PT625DB                0x1
#घोषणा FV_DACVOLL_MUTE                      0x0

/* Register Masks */
#घोषणा RM_DACVOLL                           RM(FM_DACVOLL, FB_DACVOLL)

/* Register Values */
#घोषणा RV_DACVOLL_0DB                       RV(FV_DACVOLL_0DB, FB_DACVOLL)
#घोषणा RV_DACVOLL_N95PT625DB \
	 RV(FV_DACVOLL_N95PT625DB, FB_DACVOLL)

#घोषणा RV_DACVOLL_MUTE                      RV(FV_DACVOLL_MUTE, FB_DACVOLL)

/*****************************
 *      R_DACVOLR (0x5)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_DACVOLR                           0

/* Field Masks */
#घोषणा FM_DACVOLR                           0XFF

/* Field Values */
#घोषणा FV_DACVOLR_0DB                       0xFF
#घोषणा FV_DACVOLR_N95PT625DB                0x1
#घोषणा FV_DACVOLR_MUTE                      0x0

/* Register Masks */
#घोषणा RM_DACVOLR                           RM(FM_DACVOLR, FB_DACVOLR)

/* Register Values */
#घोषणा RV_DACVOLR_0DB                       RV(FV_DACVOLR_0DB, FB_DACVOLR)
#घोषणा RV_DACVOLR_N95PT625DB \
	 RV(FV_DACVOLR_N95PT625DB, FB_DACVOLR)

#घोषणा RV_DACVOLR_MUTE                      RV(FV_DACVOLR_MUTE, FB_DACVOLR)

/*****************************
 *      R_ADCVOLL (0x6)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_ADCVOLL                           0

/* Field Masks */
#घोषणा FM_ADCVOLL                           0XFF

/* Field Values */
#घोषणा FV_ADCVOLL_P24DB                     0xFF
#घोषणा FV_ADCVOLL_N71PT25DB                 0x1
#घोषणा FV_ADCVOLL_MUTE                      0x0

/* Register Masks */
#घोषणा RM_ADCVOLL                           RM(FM_ADCVOLL, FB_ADCVOLL)

/* Register Values */
#घोषणा RV_ADCVOLL_P24DB                     RV(FV_ADCVOLL_P24DB, FB_ADCVOLL)
#घोषणा RV_ADCVOLL_N71PT25DB \
	 RV(FV_ADCVOLL_N71PT25DB, FB_ADCVOLL)

#घोषणा RV_ADCVOLL_MUTE                      RV(FV_ADCVOLL_MUTE, FB_ADCVOLL)

/*****************************
 *      R_ADCVOLR (0x7)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_ADCVOLR                           0

/* Field Masks */
#घोषणा FM_ADCVOLR                           0XFF

/* Field Values */
#घोषणा FV_ADCVOLR_P24DB                     0xFF
#घोषणा FV_ADCVOLR_N71PT25DB                 0x1
#घोषणा FV_ADCVOLR_MUTE                      0x0

/* Register Masks */
#घोषणा RM_ADCVOLR                           RM(FM_ADCVOLR, FB_ADCVOLR)

/* Register Values */
#घोषणा RV_ADCVOLR_P24DB                     RV(FV_ADCVOLR_P24DB, FB_ADCVOLR)
#घोषणा RV_ADCVOLR_N71PT25DB \
	 RV(FV_ADCVOLR_N71PT25DB, FB_ADCVOLR)

#घोषणा RV_ADCVOLR_MUTE                      RV(FV_ADCVOLR_MUTE, FB_ADCVOLR)

/****************************
 *      R_INVOLL (0x8)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_INVOLL_INMUTEL                    7
#घोषणा FB_INVOLL_IZCL                       6
#घोषणा FB_INVOLL                            0

/* Field Masks */
#घोषणा FM_INVOLL_INMUTEL                    0X1
#घोषणा FM_INVOLL_IZCL                       0X1
#घोषणा FM_INVOLL                            0X3F

/* Field Values */
#घोषणा FV_INVOLL_INMUTEL_ENABLE             0x1
#घोषणा FV_INVOLL_INMUTEL_DISABLE            0x0
#घोषणा FV_INVOLL_IZCL_ENABLE                0x1
#घोषणा FV_INVOLL_IZCL_DISABLE               0x0
#घोषणा FV_INVOLL_P30DB                      0x3F
#घोषणा FV_INVOLL_N17PT25DB                  0x0

/* Register Masks */
#घोषणा RM_INVOLL_INMUTEL \
	 RM(FM_INVOLL_INMUTEL, FB_INVOLL_INMUTEL)

#घोषणा RM_INVOLL_IZCL                       RM(FM_INVOLL_IZCL, FB_INVOLL_IZCL)
#घोषणा RM_INVOLL                            RM(FM_INVOLL, FB_INVOLL)

/* Register Values */
#घोषणा RV_INVOLL_INMUTEL_ENABLE \
	 RV(FV_INVOLL_INMUTEL_ENABLE, FB_INVOLL_INMUTEL)

#घोषणा RV_INVOLL_INMUTEL_DISABLE \
	 RV(FV_INVOLL_INMUTEL_DISABLE, FB_INVOLL_INMUTEL)

#घोषणा RV_INVOLL_IZCL_ENABLE \
	 RV(FV_INVOLL_IZCL_ENABLE, FB_INVOLL_IZCL)

#घोषणा RV_INVOLL_IZCL_DISABLE \
	 RV(FV_INVOLL_IZCL_DISABLE, FB_INVOLL_IZCL)

#घोषणा RV_INVOLL_P30DB                      RV(FV_INVOLL_P30DB, FB_INVOLL)
#घोषणा RV_INVOLL_N17PT25DB                  RV(FV_INVOLL_N17PT25DB, FB_INVOLL)

/****************************
 *      R_INVOLR (0x9)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_INVOLR_INMUTER                    7
#घोषणा FB_INVOLR_IZCR                       6
#घोषणा FB_INVOLR                            0

/* Field Masks */
#घोषणा FM_INVOLR_INMUTER                    0X1
#घोषणा FM_INVOLR_IZCR                       0X1
#घोषणा FM_INVOLR                            0X3F

/* Field Values */
#घोषणा FV_INVOLR_INMUTER_ENABLE             0x1
#घोषणा FV_INVOLR_INMUTER_DISABLE            0x0
#घोषणा FV_INVOLR_IZCR_ENABLE                0x1
#घोषणा FV_INVOLR_IZCR_DISABLE               0x0
#घोषणा FV_INVOLR_P30DB                      0x3F
#घोषणा FV_INVOLR_N17PT25DB                  0x0

/* Register Masks */
#घोषणा RM_INVOLR_INMUTER \
	 RM(FM_INVOLR_INMUTER, FB_INVOLR_INMUTER)

#घोषणा RM_INVOLR_IZCR                       RM(FM_INVOLR_IZCR, FB_INVOLR_IZCR)
#घोषणा RM_INVOLR                            RM(FM_INVOLR, FB_INVOLR)

/* Register Values */
#घोषणा RV_INVOLR_INMUTER_ENABLE \
	 RV(FV_INVOLR_INMUTER_ENABLE, FB_INVOLR_INMUTER)

#घोषणा RV_INVOLR_INMUTER_DISABLE \
	 RV(FV_INVOLR_INMUTER_DISABLE, FB_INVOLR_INMUTER)

#घोषणा RV_INVOLR_IZCR_ENABLE \
	 RV(FV_INVOLR_IZCR_ENABLE, FB_INVOLR_IZCR)

#घोषणा RV_INVOLR_IZCR_DISABLE \
	 RV(FV_INVOLR_IZCR_DISABLE, FB_INVOLR_IZCR)

#घोषणा RV_INVOLR_P30DB                      RV(FV_INVOLR_P30DB, FB_INVOLR)
#घोषणा RV_INVOLR_N17PT25DB                  RV(FV_INVOLR_N17PT25DB, FB_INVOLR)

/*****************************
 *      R_INMODE (0x0B)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_INMODE_DS                         0

/* Field Masks */
#घोषणा FM_INMODE_DS                         0X1

/* Field Values */
#घोषणा FV_INMODE_DS_LRIN1                   0x0
#घोषणा FV_INMODE_DS_LRIN2                   0x1

/* Register Masks */
#घोषणा RM_INMODE_DS                         RM(FM_INMODE_DS, FB_INMODE_DS)

/* Register Values */
#घोषणा RV_INMODE_DS_LRIN1 \
	 RV(FV_INMODE_DS_LRIN1, FB_INMODE_DS)

#घोषणा RV_INMODE_DS_LRIN2 \
	 RV(FV_INMODE_DS_LRIN2, FB_INMODE_DS)


/*****************************
 *      R_INSELL (0x0C)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_INSELL                            6
#घोषणा FB_INSELL_MICBSTL                    4

/* Field Masks */
#घोषणा FM_INSELL                            0X3
#घोषणा FM_INSELL_MICBSTL                    0X3

/* Field Values */
#घोषणा FV_INSELL_IN1                        0x0
#घोषणा FV_INSELL_IN2                        0x1
#घोषणा FV_INSELL_IN3                        0x2
#घोषणा FV_INSELL_D2S                        0x3
#घोषणा FV_INSELL_MICBSTL_OFF                0x0
#घोषणा FV_INSELL_MICBSTL_10DB               0x1
#घोषणा FV_INSELL_MICBSTL_20DB               0x2
#घोषणा FV_INSELL_MICBSTL_30DB               0x3

/* Register Masks */
#घोषणा RM_INSELL                            RM(FM_INSELL, FB_INSELL)
#घोषणा RM_INSELL_MICBSTL \
	 RM(FM_INSELL_MICBSTL, FB_INSELL_MICBSTL)


/* Register Values */
#घोषणा RV_INSELL_IN1                        RV(FV_INSELL_IN1, FB_INSELL)
#घोषणा RV_INSELL_IN2                        RV(FV_INSELL_IN2, FB_INSELL)
#घोषणा RV_INSELL_IN3                        RV(FV_INSELL_IN3, FB_INSELL)
#घोषणा RV_INSELL_D2S                        RV(FV_INSELL_D2S, FB_INSELL)
#घोषणा RV_INSELL_MICBSTL_OFF \
	 RV(FV_INSELL_MICBSTL_OFF, FB_INSELL_MICBSTL)

#घोषणा RV_INSELL_MICBSTL_10DB \
	 RV(FV_INSELL_MICBSTL_10DB, FB_INSELL_MICBSTL)

#घोषणा RV_INSELL_MICBSTL_20DB \
	 RV(FV_INSELL_MICBSTL_20DB, FB_INSELL_MICBSTL)

#घोषणा RV_INSELL_MICBSTL_30DB \
	 RV(FV_INSELL_MICBSTL_30DB, FB_INSELL_MICBSTL)


/*****************************
 *      R_INSELR (0x0D)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_INSELR                            6
#घोषणा FB_INSELR_MICBSTR                    4

/* Field Masks */
#घोषणा FM_INSELR                            0X3
#घोषणा FM_INSELR_MICBSTR                    0X3

/* Field Values */
#घोषणा FV_INSELR_IN1                        0x0
#घोषणा FV_INSELR_IN2                        0x1
#घोषणा FV_INSELR_IN3                        0x2
#घोषणा FV_INSELR_D2S                        0x3
#घोषणा FV_INSELR_MICBSTR_OFF                0x0
#घोषणा FV_INSELR_MICBSTR_10DB               0x1
#घोषणा FV_INSELR_MICBSTR_20DB               0x2
#घोषणा FV_INSELR_MICBSTR_30DB               0x3

/* Register Masks */
#घोषणा RM_INSELR                            RM(FM_INSELR, FB_INSELR)
#घोषणा RM_INSELR_MICBSTR \
	 RM(FM_INSELR_MICBSTR, FB_INSELR_MICBSTR)


/* Register Values */
#घोषणा RV_INSELR_IN1                        RV(FV_INSELR_IN1, FB_INSELR)
#घोषणा RV_INSELR_IN2                        RV(FV_INSELR_IN2, FB_INSELR)
#घोषणा RV_INSELR_IN3                        RV(FV_INSELR_IN3, FB_INSELR)
#घोषणा RV_INSELR_D2S                        RV(FV_INSELR_D2S, FB_INSELR)
#घोषणा RV_INSELR_MICBSTR_OFF \
	 RV(FV_INSELR_MICBSTR_OFF, FB_INSELR_MICBSTR)

#घोषणा RV_INSELR_MICBSTR_10DB \
	 RV(FV_INSELR_MICBSTR_10DB, FB_INSELR_MICBSTR)

#घोषणा RV_INSELR_MICBSTR_20DB \
	 RV(FV_INSELR_MICBSTR_20DB, FB_INSELR_MICBSTR)

#घोषणा RV_INSELR_MICBSTR_30DB \
	 RV(FV_INSELR_MICBSTR_30DB, FB_INSELR_MICBSTR)


/***************************
 *      R_AIC1 (0x13)      *
 ***************************/

/* Field Offsets */
#घोषणा FB_AIC1_BCLKINV                      6
#घोषणा FB_AIC1_MS                           5
#घोषणा FB_AIC1_LRP                          4
#घोषणा FB_AIC1_WL                           2
#घोषणा FB_AIC1_FORMAT                       0

/* Field Masks */
#घोषणा FM_AIC1_BCLKINV                      0X1
#घोषणा FM_AIC1_MS                           0X1
#घोषणा FM_AIC1_LRP                          0X1
#घोषणा FM_AIC1_WL                           0X3
#घोषणा FM_AIC1_FORMAT                       0X3

/* Field Values */
#घोषणा FV_AIC1_BCLKINV_ENABLE               0x1
#घोषणा FV_AIC1_BCLKINV_DISABLE              0x0
#घोषणा FV_AIC1_MS_MASTER                    0x1
#घोषणा FV_AIC1_MS_SLAVE                     0x0
#घोषणा FV_AIC1_LRP_INVERT                   0x1
#घोषणा FV_AIC1_LRP_NORMAL                   0x0
#घोषणा FV_AIC1_WL_16                        0x0
#घोषणा FV_AIC1_WL_20                        0x1
#घोषणा FV_AIC1_WL_24                        0x2
#घोषणा FV_AIC1_WL_32                        0x3
#घोषणा FV_AIC1_FORMAT_RIGHT                 0x0
#घोषणा FV_AIC1_FORMAT_LEFT                  0x1
#घोषणा FV_AIC1_FORMAT_I2S                   0x2

/* Register Masks */
#घोषणा RM_AIC1_BCLKINV \
	 RM(FM_AIC1_BCLKINV, FB_AIC1_BCLKINV)

#घोषणा RM_AIC1_MS                           RM(FM_AIC1_MS, FB_AIC1_MS)
#घोषणा RM_AIC1_LRP                          RM(FM_AIC1_LRP, FB_AIC1_LRP)
#घोषणा RM_AIC1_WL                           RM(FM_AIC1_WL, FB_AIC1_WL)
#घोषणा RM_AIC1_FORMAT                       RM(FM_AIC1_FORMAT, FB_AIC1_FORMAT)

/* Register Values */
#घोषणा RV_AIC1_BCLKINV_ENABLE \
	 RV(FV_AIC1_BCLKINV_ENABLE, FB_AIC1_BCLKINV)

#घोषणा RV_AIC1_BCLKINV_DISABLE \
	 RV(FV_AIC1_BCLKINV_DISABLE, FB_AIC1_BCLKINV)

#घोषणा RV_AIC1_MS_MASTER                    RV(FV_AIC1_MS_MASTER, FB_AIC1_MS)
#घोषणा RV_AIC1_MS_SLAVE                     RV(FV_AIC1_MS_SLAVE, FB_AIC1_MS)
#घोषणा RV_AIC1_LRP_INVERT \
	 RV(FV_AIC1_LRP_INVERT, FB_AIC1_LRP)

#घोषणा RV_AIC1_LRP_NORMAL \
	 RV(FV_AIC1_LRP_NORMAL, FB_AIC1_LRP)

#घोषणा RV_AIC1_WL_16                        RV(FV_AIC1_WL_16, FB_AIC1_WL)
#घोषणा RV_AIC1_WL_20                        RV(FV_AIC1_WL_20, FB_AIC1_WL)
#घोषणा RV_AIC1_WL_24                        RV(FV_AIC1_WL_24, FB_AIC1_WL)
#घोषणा RV_AIC1_WL_32                        RV(FV_AIC1_WL_32, FB_AIC1_WL)
#घोषणा RV_AIC1_FORMAT_RIGHT \
	 RV(FV_AIC1_FORMAT_RIGHT, FB_AIC1_FORMAT)

#घोषणा RV_AIC1_FORMAT_LEFT \
	 RV(FV_AIC1_FORMAT_LEFT, FB_AIC1_FORMAT)

#घोषणा RV_AIC1_FORMAT_I2S \
	 RV(FV_AIC1_FORMAT_I2S, FB_AIC1_FORMAT)


/***************************
 *      R_AIC2 (0x14)      *
 ***************************/

/* Field Offsets */
#घोषणा FB_AIC2_DACDSEL                      6
#घोषणा FB_AIC2_ADCDSEL                      4
#घोषणा FB_AIC2_TRI                          3
#घोषणा FB_AIC2_BLRCM                        0

/* Field Masks */
#घोषणा FM_AIC2_DACDSEL                      0X3
#घोषणा FM_AIC2_ADCDSEL                      0X3
#घोषणा FM_AIC2_TRI                          0X1
#घोषणा FM_AIC2_BLRCM                        0X7

/* Field Values */
#घोषणा FV_AIC2_BLRCM_DAC_BCLK_LRCLK_SHARED  0x3

/* Register Masks */
#घोषणा RM_AIC2_DACDSEL \
	 RM(FM_AIC2_DACDSEL, FB_AIC2_DACDSEL)

#घोषणा RM_AIC2_ADCDSEL \
	 RM(FM_AIC2_ADCDSEL, FB_AIC2_ADCDSEL)

#घोषणा RM_AIC2_TRI                          RM(FM_AIC2_TRI, FB_AIC2_TRI)
#घोषणा RM_AIC2_BLRCM                        RM(FM_AIC2_BLRCM, FB_AIC2_BLRCM)

/* Register Values */
#घोषणा RV_AIC2_BLRCM_DAC_BCLK_LRCLK_SHARED \
	 RV(FV_AIC2_BLRCM_DAC_BCLK_LRCLK_SHARED, FB_AIC2_BLRCM)


/******************************
 *      R_CNVRTR0 (0x16)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_CNVRTR0_ADCPOLR                   7
#घोषणा FB_CNVRTR0_ADCPOLL                   6
#घोषणा FB_CNVRTR0_AMONOMIX                  4
#घोषणा FB_CNVRTR0_ADCMU                     3
#घोषणा FB_CNVRTR0_HPOR                      2
#घोषणा FB_CNVRTR0_ADCHPDR                   1
#घोषणा FB_CNVRTR0_ADCHPDL                   0

/* Field Masks */
#घोषणा FM_CNVRTR0_ADCPOLR                   0X1
#घोषणा FM_CNVRTR0_ADCPOLL                   0X1
#घोषणा FM_CNVRTR0_AMONOMIX                  0X3
#घोषणा FM_CNVRTR0_ADCMU                     0X1
#घोषणा FM_CNVRTR0_HPOR                      0X1
#घोषणा FM_CNVRTR0_ADCHPDR                   0X1
#घोषणा FM_CNVRTR0_ADCHPDL                   0X1

/* Field Values */
#घोषणा FV_CNVRTR0_ADCPOLR_INVERT            0x1
#घोषणा FV_CNVRTR0_ADCPOLR_NORMAL            0x0
#घोषणा FV_CNVRTR0_ADCPOLL_INVERT            0x1
#घोषणा FV_CNVRTR0_ADCPOLL_NORMAL            0x0
#घोषणा FV_CNVRTR0_ADCMU_ENABLE              0x1
#घोषणा FV_CNVRTR0_ADCMU_DISABLE             0x0
#घोषणा FV_CNVRTR0_ADCHPDR_ENABLE            0x1
#घोषणा FV_CNVRTR0_ADCHPDR_DISABLE           0x0
#घोषणा FV_CNVRTR0_ADCHPDL_ENABLE            0x1
#घोषणा FV_CNVRTR0_ADCHPDL_DISABLE           0x0

/* Register Masks */
#घोषणा RM_CNVRTR0_ADCPOLR \
	 RM(FM_CNVRTR0_ADCPOLR, FB_CNVRTR0_ADCPOLR)

#घोषणा RM_CNVRTR0_ADCPOLL \
	 RM(FM_CNVRTR0_ADCPOLL, FB_CNVRTR0_ADCPOLL)

#घोषणा RM_CNVRTR0_AMONOMIX \
	 RM(FM_CNVRTR0_AMONOMIX, FB_CNVRTR0_AMONOMIX)

#घोषणा RM_CNVRTR0_ADCMU \
	 RM(FM_CNVRTR0_ADCMU, FB_CNVRTR0_ADCMU)

#घोषणा RM_CNVRTR0_HPOR \
	 RM(FM_CNVRTR0_HPOR, FB_CNVRTR0_HPOR)

#घोषणा RM_CNVRTR0_ADCHPDR \
	 RM(FM_CNVRTR0_ADCHPDR, FB_CNVRTR0_ADCHPDR)

#घोषणा RM_CNVRTR0_ADCHPDL \
	 RM(FM_CNVRTR0_ADCHPDL, FB_CNVRTR0_ADCHPDL)


/* Register Values */
#घोषणा RV_CNVRTR0_ADCPOLR_INVERT \
	 RV(FV_CNVRTR0_ADCPOLR_INVERT, FB_CNVRTR0_ADCPOLR)

#घोषणा RV_CNVRTR0_ADCPOLR_NORMAL \
	 RV(FV_CNVRTR0_ADCPOLR_NORMAL, FB_CNVRTR0_ADCPOLR)

#घोषणा RV_CNVRTR0_ADCPOLL_INVERT \
	 RV(FV_CNVRTR0_ADCPOLL_INVERT, FB_CNVRTR0_ADCPOLL)

#घोषणा RV_CNVRTR0_ADCPOLL_NORMAL \
	 RV(FV_CNVRTR0_ADCPOLL_NORMAL, FB_CNVRTR0_ADCPOLL)

#घोषणा RV_CNVRTR0_ADCMU_ENABLE \
	 RV(FV_CNVRTR0_ADCMU_ENABLE, FB_CNVRTR0_ADCMU)

#घोषणा RV_CNVRTR0_ADCMU_DISABLE \
	 RV(FV_CNVRTR0_ADCMU_DISABLE, FB_CNVRTR0_ADCMU)

#घोषणा RV_CNVRTR0_ADCHPDR_ENABLE \
	 RV(FV_CNVRTR0_ADCHPDR_ENABLE, FB_CNVRTR0_ADCHPDR)

#घोषणा RV_CNVRTR0_ADCHPDR_DISABLE \
	 RV(FV_CNVRTR0_ADCHPDR_DISABLE, FB_CNVRTR0_ADCHPDR)

#घोषणा RV_CNVRTR0_ADCHPDL_ENABLE \
	 RV(FV_CNVRTR0_ADCHPDL_ENABLE, FB_CNVRTR0_ADCHPDL)

#घोषणा RV_CNVRTR0_ADCHPDL_DISABLE \
	 RV(FV_CNVRTR0_ADCHPDL_DISABLE, FB_CNVRTR0_ADCHPDL)


/****************************
 *      R_ADCSR (0x17)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_ADCSR_ABCM                        6
#घोषणा FB_ADCSR_ABR                         3
#घोषणा FB_ADCSR_ABM                         0

/* Field Masks */
#घोषणा FM_ADCSR_ABCM                        0X3
#घोषणा FM_ADCSR_ABR                         0X3
#घोषणा FM_ADCSR_ABM                         0X7

/* Field Values */
#घोषणा FV_ADCSR_ABCM_AUTO                   0x0
#घोषणा FV_ADCSR_ABCM_32                     0x1
#घोषणा FV_ADCSR_ABCM_40                     0x2
#घोषणा FV_ADCSR_ABCM_64                     0x3
#घोषणा FV_ADCSR_ABR_32                      0x0
#घोषणा FV_ADCSR_ABR_44_1                    0x1
#घोषणा FV_ADCSR_ABR_48                      0x2
#घोषणा FV_ADCSR_ABM_PT25                    0x0
#घोषणा FV_ADCSR_ABM_PT5                     0x1
#घोषणा FV_ADCSR_ABM_1                       0x2
#घोषणा FV_ADCSR_ABM_2                       0x3

/* Register Masks */
#घोषणा RM_ADCSR_ABCM                        RM(FM_ADCSR_ABCM, FB_ADCSR_ABCM)
#घोषणा RM_ADCSR_ABR                         RM(FM_ADCSR_ABR, FB_ADCSR_ABR)
#घोषणा RM_ADCSR_ABM                         RM(FM_ADCSR_ABM, FB_ADCSR_ABM)

/* Register Values */
#घोषणा RV_ADCSR_ABCM_AUTO \
	 RV(FV_ADCSR_ABCM_AUTO, FB_ADCSR_ABCM)

#घोषणा RV_ADCSR_ABCM_32 \
	 RV(FV_ADCSR_ABCM_32, FB_ADCSR_ABCM)

#घोषणा RV_ADCSR_ABCM_40 \
	 RV(FV_ADCSR_ABCM_40, FB_ADCSR_ABCM)

#घोषणा RV_ADCSR_ABCM_64 \
	 RV(FV_ADCSR_ABCM_64, FB_ADCSR_ABCM)

#घोषणा RV_ADCSR_ABR_32                      RV(FV_ADCSR_ABR_32, FB_ADCSR_ABR)
#घोषणा RV_ADCSR_ABR_44_1 \
	 RV(FV_ADCSR_ABR_44_1, FB_ADCSR_ABR)

#घोषणा RV_ADCSR_ABR_48                      RV(FV_ADCSR_ABR_48, FB_ADCSR_ABR)
#घोषणा RV_ADCSR_ABR_                        RV(FV_ADCSR_ABR_, FB_ADCSR_ABR)
#घोषणा RV_ADCSR_ABM_PT25 \
	 RV(FV_ADCSR_ABM_PT25, FB_ADCSR_ABM)

#घोषणा RV_ADCSR_ABM_PT5                     RV(FV_ADCSR_ABM_PT5, FB_ADCSR_ABM)
#घोषणा RV_ADCSR_ABM_1                       RV(FV_ADCSR_ABM_1, FB_ADCSR_ABM)
#घोषणा RV_ADCSR_ABM_2                       RV(FV_ADCSR_ABM_2, FB_ADCSR_ABM)

/******************************
 *      R_CNVRTR1 (0x18)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_CNVRTR1_DACPOLR                   7
#घोषणा FB_CNVRTR1_DACPOLL                   6
#घोषणा FB_CNVRTR1_DMONOMIX                  4
#घोषणा FB_CNVRTR1_DACMU                     3
#घोषणा FB_CNVRTR1_DEEMPH                    2
#घोषणा FB_CNVRTR1_DACDITH                   0

/* Field Masks */
#घोषणा FM_CNVRTR1_DACPOLR                   0X1
#घोषणा FM_CNVRTR1_DACPOLL                   0X1
#घोषणा FM_CNVRTR1_DMONOMIX                  0X3
#घोषणा FM_CNVRTR1_DACMU                     0X1
#घोषणा FM_CNVRTR1_DEEMPH                    0X1
#घोषणा FM_CNVRTR1_DACDITH                   0X3

/* Field Values */
#घोषणा FV_CNVRTR1_DACPOLR_INVERT            0x1
#घोषणा FV_CNVRTR1_DACPOLR_NORMAL            0x0
#घोषणा FV_CNVRTR1_DACPOLL_INVERT            0x1
#घोषणा FV_CNVRTR1_DACPOLL_NORMAL            0x0
#घोषणा FV_CNVRTR1_DMONOMIX_ENABLE           0x1
#घोषणा FV_CNVRTR1_DMONOMIX_DISABLE          0x0
#घोषणा FV_CNVRTR1_DACMU_ENABLE              0x1
#घोषणा FV_CNVRTR1_DACMU_DISABLE             0x0

/* Register Masks */
#घोषणा RM_CNVRTR1_DACPOLR \
	 RM(FM_CNVRTR1_DACPOLR, FB_CNVRTR1_DACPOLR)

#घोषणा RM_CNVRTR1_DACPOLL \
	 RM(FM_CNVRTR1_DACPOLL, FB_CNVRTR1_DACPOLL)

#घोषणा RM_CNVRTR1_DMONOMIX \
	 RM(FM_CNVRTR1_DMONOMIX, FB_CNVRTR1_DMONOMIX)

#घोषणा RM_CNVRTR1_DACMU \
	 RM(FM_CNVRTR1_DACMU, FB_CNVRTR1_DACMU)

#घोषणा RM_CNVRTR1_DEEMPH \
	 RM(FM_CNVRTR1_DEEMPH, FB_CNVRTR1_DEEMPH)

#घोषणा RM_CNVRTR1_DACDITH \
	 RM(FM_CNVRTR1_DACDITH, FB_CNVRTR1_DACDITH)


/* Register Values */
#घोषणा RV_CNVRTR1_DACPOLR_INVERT \
	 RV(FV_CNVRTR1_DACPOLR_INVERT, FB_CNVRTR1_DACPOLR)

#घोषणा RV_CNVRTR1_DACPOLR_NORMAL \
	 RV(FV_CNVRTR1_DACPOLR_NORMAL, FB_CNVRTR1_DACPOLR)

#घोषणा RV_CNVRTR1_DACPOLL_INVERT \
	 RV(FV_CNVRTR1_DACPOLL_INVERT, FB_CNVRTR1_DACPOLL)

#घोषणा RV_CNVRTR1_DACPOLL_NORMAL \
	 RV(FV_CNVRTR1_DACPOLL_NORMAL, FB_CNVRTR1_DACPOLL)

#घोषणा RV_CNVRTR1_DMONOMIX_ENABLE \
	 RV(FV_CNVRTR1_DMONOMIX_ENABLE, FB_CNVRTR1_DMONOMIX)

#घोषणा RV_CNVRTR1_DMONOMIX_DISABLE \
	 RV(FV_CNVRTR1_DMONOMIX_DISABLE, FB_CNVRTR1_DMONOMIX)

#घोषणा RV_CNVRTR1_DACMU_ENABLE \
	 RV(FV_CNVRTR1_DACMU_ENABLE, FB_CNVRTR1_DACMU)

#घोषणा RV_CNVRTR1_DACMU_DISABLE \
	 RV(FV_CNVRTR1_DACMU_DISABLE, FB_CNVRTR1_DACMU)


/****************************
 *      R_DACSR (0x19)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_DACSR_DBCM                        6
#घोषणा FB_DACSR_DBR                         3
#घोषणा FB_DACSR_DBM                         0

/* Field Masks */
#घोषणा FM_DACSR_DBCM                        0X3
#घोषणा FM_DACSR_DBR                         0X3
#घोषणा FM_DACSR_DBM                         0X7

/* Field Values */
#घोषणा FV_DACSR_DBCM_AUTO                   0x0
#घोषणा FV_DACSR_DBCM_32                     0x1
#घोषणा FV_DACSR_DBCM_40                     0x2
#घोषणा FV_DACSR_DBCM_64                     0x3
#घोषणा FV_DACSR_DBR_32                      0x0
#घोषणा FV_DACSR_DBR_44_1                    0x1
#घोषणा FV_DACSR_DBR_48                      0x2
#घोषणा FV_DACSR_DBM_PT25                    0x0
#घोषणा FV_DACSR_DBM_PT5                     0x1
#घोषणा FV_DACSR_DBM_1                       0x2
#घोषणा FV_DACSR_DBM_2                       0x3

/* Register Masks */
#घोषणा RM_DACSR_DBCM                        RM(FM_DACSR_DBCM, FB_DACSR_DBCM)
#घोषणा RM_DACSR_DBR                         RM(FM_DACSR_DBR, FB_DACSR_DBR)
#घोषणा RM_DACSR_DBM                         RM(FM_DACSR_DBM, FB_DACSR_DBM)

/* Register Values */
#घोषणा RV_DACSR_DBCM_AUTO \
	 RV(FV_DACSR_DBCM_AUTO, FB_DACSR_DBCM)

#घोषणा RV_DACSR_DBCM_32 \
	 RV(FV_DACSR_DBCM_32, FB_DACSR_DBCM)

#घोषणा RV_DACSR_DBCM_40 \
	 RV(FV_DACSR_DBCM_40, FB_DACSR_DBCM)

#घोषणा RV_DACSR_DBCM_64 \
	 RV(FV_DACSR_DBCM_64, FB_DACSR_DBCM)

#घोषणा RV_DACSR_DBR_32                      RV(FV_DACSR_DBR_32, FB_DACSR_DBR)
#घोषणा RV_DACSR_DBR_44_1 \
	 RV(FV_DACSR_DBR_44_1, FB_DACSR_DBR)

#घोषणा RV_DACSR_DBR_48                      RV(FV_DACSR_DBR_48, FB_DACSR_DBR)
#घोषणा RV_DACSR_DBM_PT25 \
	 RV(FV_DACSR_DBM_PT25, FB_DACSR_DBM)

#घोषणा RV_DACSR_DBM_PT5                     RV(FV_DACSR_DBM_PT5, FB_DACSR_DBM)
#घोषणा RV_DACSR_DBM_1                       RV(FV_DACSR_DBM_1, FB_DACSR_DBM)
#घोषणा RV_DACSR_DBM_2                       RV(FV_DACSR_DBM_2, FB_DACSR_DBM)

/****************************
 *      R_PWRM1 (0x1A)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_PWRM1_BSTL                        7
#घोषणा FB_PWRM1_BSTR                        6
#घोषणा FB_PWRM1_PGAL                        5
#घोषणा FB_PWRM1_PGAR                        4
#घोषणा FB_PWRM1_ADCL                        3
#घोषणा FB_PWRM1_ADCR                        2
#घोषणा FB_PWRM1_MICB                        1
#घोषणा FB_PWRM1_DIGENB                      0

/* Field Masks */
#घोषणा FM_PWRM1_BSTL                        0X1
#घोषणा FM_PWRM1_BSTR                        0X1
#घोषणा FM_PWRM1_PGAL                        0X1
#घोषणा FM_PWRM1_PGAR                        0X1
#घोषणा FM_PWRM1_ADCL                        0X1
#घोषणा FM_PWRM1_ADCR                        0X1
#घोषणा FM_PWRM1_MICB                        0X1
#घोषणा FM_PWRM1_DIGENB                      0X1

/* Field Values */
#घोषणा FV_PWRM1_BSTL_ENABLE                 0x1
#घोषणा FV_PWRM1_BSTL_DISABLE                0x0
#घोषणा FV_PWRM1_BSTR_ENABLE                 0x1
#घोषणा FV_PWRM1_BSTR_DISABLE                0x0
#घोषणा FV_PWRM1_PGAL_ENABLE                 0x1
#घोषणा FV_PWRM1_PGAL_DISABLE                0x0
#घोषणा FV_PWRM1_PGAR_ENABLE                 0x1
#घोषणा FV_PWRM1_PGAR_DISABLE                0x0
#घोषणा FV_PWRM1_ADCL_ENABLE                 0x1
#घोषणा FV_PWRM1_ADCL_DISABLE                0x0
#घोषणा FV_PWRM1_ADCR_ENABLE                 0x1
#घोषणा FV_PWRM1_ADCR_DISABLE                0x0
#घोषणा FV_PWRM1_MICB_ENABLE                 0x1
#घोषणा FV_PWRM1_MICB_DISABLE                0x0
#घोषणा FV_PWRM1_DIGENB_DISABLE              0x1
#घोषणा FV_PWRM1_DIGENB_ENABLE               0x0

/* Register Masks */
#घोषणा RM_PWRM1_BSTL                        RM(FM_PWRM1_BSTL, FB_PWRM1_BSTL)
#घोषणा RM_PWRM1_BSTR                        RM(FM_PWRM1_BSTR, FB_PWRM1_BSTR)
#घोषणा RM_PWRM1_PGAL                        RM(FM_PWRM1_PGAL, FB_PWRM1_PGAL)
#घोषणा RM_PWRM1_PGAR                        RM(FM_PWRM1_PGAR, FB_PWRM1_PGAR)
#घोषणा RM_PWRM1_ADCL                        RM(FM_PWRM1_ADCL, FB_PWRM1_ADCL)
#घोषणा RM_PWRM1_ADCR                        RM(FM_PWRM1_ADCR, FB_PWRM1_ADCR)
#घोषणा RM_PWRM1_MICB                        RM(FM_PWRM1_MICB, FB_PWRM1_MICB)
#घोषणा RM_PWRM1_DIGENB \
	 RM(FM_PWRM1_DIGENB, FB_PWRM1_DIGENB)


/* Register Values */
#घोषणा RV_PWRM1_BSTL_ENABLE \
	 RV(FV_PWRM1_BSTL_ENABLE, FB_PWRM1_BSTL)

#घोषणा RV_PWRM1_BSTL_DISABLE \
	 RV(FV_PWRM1_BSTL_DISABLE, FB_PWRM1_BSTL)

#घोषणा RV_PWRM1_BSTR_ENABLE \
	 RV(FV_PWRM1_BSTR_ENABLE, FB_PWRM1_BSTR)

#घोषणा RV_PWRM1_BSTR_DISABLE \
	 RV(FV_PWRM1_BSTR_DISABLE, FB_PWRM1_BSTR)

#घोषणा RV_PWRM1_PGAL_ENABLE \
	 RV(FV_PWRM1_PGAL_ENABLE, FB_PWRM1_PGAL)

#घोषणा RV_PWRM1_PGAL_DISABLE \
	 RV(FV_PWRM1_PGAL_DISABLE, FB_PWRM1_PGAL)

#घोषणा RV_PWRM1_PGAR_ENABLE \
	 RV(FV_PWRM1_PGAR_ENABLE, FB_PWRM1_PGAR)

#घोषणा RV_PWRM1_PGAR_DISABLE \
	 RV(FV_PWRM1_PGAR_DISABLE, FB_PWRM1_PGAR)

#घोषणा RV_PWRM1_ADCL_ENABLE \
	 RV(FV_PWRM1_ADCL_ENABLE, FB_PWRM1_ADCL)

#घोषणा RV_PWRM1_ADCL_DISABLE \
	 RV(FV_PWRM1_ADCL_DISABLE, FB_PWRM1_ADCL)

#घोषणा RV_PWRM1_ADCR_ENABLE \
	 RV(FV_PWRM1_ADCR_ENABLE, FB_PWRM1_ADCR)

#घोषणा RV_PWRM1_ADCR_DISABLE \
	 RV(FV_PWRM1_ADCR_DISABLE, FB_PWRM1_ADCR)

#घोषणा RV_PWRM1_MICB_ENABLE \
	 RV(FV_PWRM1_MICB_ENABLE, FB_PWRM1_MICB)

#घोषणा RV_PWRM1_MICB_DISABLE \
	 RV(FV_PWRM1_MICB_DISABLE, FB_PWRM1_MICB)

#घोषणा RV_PWRM1_DIGENB_DISABLE \
	 RV(FV_PWRM1_DIGENB_DISABLE, FB_PWRM1_DIGENB)

#घोषणा RV_PWRM1_DIGENB_ENABLE \
	 RV(FV_PWRM1_DIGENB_ENABLE, FB_PWRM1_DIGENB)


/****************************
 *      R_PWRM2 (0x1B)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_PWRM2_D2S                         7
#घोषणा FB_PWRM2_HPL                         6
#घोषणा FB_PWRM2_HPR                         5
#घोषणा FB_PWRM2_SPKL                        4
#घोषणा FB_PWRM2_SPKR                        3
#घोषणा FB_PWRM2_INSELL                      2
#घोषणा FB_PWRM2_INSELR                      1
#घोषणा FB_PWRM2_VREF                        0

/* Field Masks */
#घोषणा FM_PWRM2_D2S                         0X1
#घोषणा FM_PWRM2_HPL                         0X1
#घोषणा FM_PWRM2_HPR                         0X1
#घोषणा FM_PWRM2_SPKL                        0X1
#घोषणा FM_PWRM2_SPKR                        0X1
#घोषणा FM_PWRM2_INSELL                      0X1
#घोषणा FM_PWRM2_INSELR                      0X1
#घोषणा FM_PWRM2_VREF                        0X1

/* Field Values */
#घोषणा FV_PWRM2_D2S_ENABLE                  0x1
#घोषणा FV_PWRM2_D2S_DISABLE                 0x0
#घोषणा FV_PWRM2_HPL_ENABLE                  0x1
#घोषणा FV_PWRM2_HPL_DISABLE                 0x0
#घोषणा FV_PWRM2_HPR_ENABLE                  0x1
#घोषणा FV_PWRM2_HPR_DISABLE                 0x0
#घोषणा FV_PWRM2_SPKL_ENABLE                 0x1
#घोषणा FV_PWRM2_SPKL_DISABLE                0x0
#घोषणा FV_PWRM2_SPKR_ENABLE                 0x1
#घोषणा FV_PWRM2_SPKR_DISABLE                0x0
#घोषणा FV_PWRM2_INSELL_ENABLE               0x1
#घोषणा FV_PWRM2_INSELL_DISABLE              0x0
#घोषणा FV_PWRM2_INSELR_ENABLE               0x1
#घोषणा FV_PWRM2_INSELR_DISABLE              0x0
#घोषणा FV_PWRM2_VREF_ENABLE                 0x1
#घोषणा FV_PWRM2_VREF_DISABLE                0x0

/* Register Masks */
#घोषणा RM_PWRM2_D2S                         RM(FM_PWRM2_D2S, FB_PWRM2_D2S)
#घोषणा RM_PWRM2_HPL                         RM(FM_PWRM2_HPL, FB_PWRM2_HPL)
#घोषणा RM_PWRM2_HPR                         RM(FM_PWRM2_HPR, FB_PWRM2_HPR)
#घोषणा RM_PWRM2_SPKL                        RM(FM_PWRM2_SPKL, FB_PWRM2_SPKL)
#घोषणा RM_PWRM2_SPKR                        RM(FM_PWRM2_SPKR, FB_PWRM2_SPKR)
#घोषणा RM_PWRM2_INSELL \
	 RM(FM_PWRM2_INSELL, FB_PWRM2_INSELL)

#घोषणा RM_PWRM2_INSELR \
	 RM(FM_PWRM2_INSELR, FB_PWRM2_INSELR)

#घोषणा RM_PWRM2_VREF                        RM(FM_PWRM2_VREF, FB_PWRM2_VREF)

/* Register Values */
#घोषणा RV_PWRM2_D2S_ENABLE \
	 RV(FV_PWRM2_D2S_ENABLE, FB_PWRM2_D2S)

#घोषणा RV_PWRM2_D2S_DISABLE \
	 RV(FV_PWRM2_D2S_DISABLE, FB_PWRM2_D2S)

#घोषणा RV_PWRM2_HPL_ENABLE \
	 RV(FV_PWRM2_HPL_ENABLE, FB_PWRM2_HPL)

#घोषणा RV_PWRM2_HPL_DISABLE \
	 RV(FV_PWRM2_HPL_DISABLE, FB_PWRM2_HPL)

#घोषणा RV_PWRM2_HPR_ENABLE \
	 RV(FV_PWRM2_HPR_ENABLE, FB_PWRM2_HPR)

#घोषणा RV_PWRM2_HPR_DISABLE \
	 RV(FV_PWRM2_HPR_DISABLE, FB_PWRM2_HPR)

#घोषणा RV_PWRM2_SPKL_ENABLE \
	 RV(FV_PWRM2_SPKL_ENABLE, FB_PWRM2_SPKL)

#घोषणा RV_PWRM2_SPKL_DISABLE \
	 RV(FV_PWRM2_SPKL_DISABLE, FB_PWRM2_SPKL)

#घोषणा RV_PWRM2_SPKR_ENABLE \
	 RV(FV_PWRM2_SPKR_ENABLE, FB_PWRM2_SPKR)

#घोषणा RV_PWRM2_SPKR_DISABLE \
	 RV(FV_PWRM2_SPKR_DISABLE, FB_PWRM2_SPKR)

#घोषणा RV_PWRM2_INSELL_ENABLE \
	 RV(FV_PWRM2_INSELL_ENABLE, FB_PWRM2_INSELL)

#घोषणा RV_PWRM2_INSELL_DISABLE \
	 RV(FV_PWRM2_INSELL_DISABLE, FB_PWRM2_INSELL)

#घोषणा RV_PWRM2_INSELR_ENABLE \
	 RV(FV_PWRM2_INSELR_ENABLE, FB_PWRM2_INSELR)

#घोषणा RV_PWRM2_INSELR_DISABLE \
	 RV(FV_PWRM2_INSELR_DISABLE, FB_PWRM2_INSELR)

#घोषणा RV_PWRM2_VREF_ENABLE \
	 RV(FV_PWRM2_VREF_ENABLE, FB_PWRM2_VREF)

#घोषणा RV_PWRM2_VREF_DISABLE \
	 RV(FV_PWRM2_VREF_DISABLE, FB_PWRM2_VREF)

/******************************
 *      R_CTL (0x1C)          *
 ******************************/

/* Fiel Offsets */
#घोषणा FB_CTL_HPSWEN                        7
#घोषणा FB_CTL_HPSWPOL                       6

/******************************
 *      R_CONFIG0 (0x1F)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_CONFIG0_ASDM                      6
#घोषणा FB_CONFIG0_DSDM                      4
#घोषणा FB_CONFIG0_DC_BYPASS                 1
#घोषणा FB_CONFIG0_SD_FORCE_ON               0

/* Field Masks */
#घोषणा FM_CONFIG0_ASDM                      0X3
#घोषणा FM_CONFIG0_DSDM                      0X3
#घोषणा FM_CONFIG0_DC_BYPASS                 0X1
#घोषणा FM_CONFIG0_SD_FORCE_ON               0X1

/* Field Values */
#घोषणा FV_CONFIG0_ASDM_HALF                 0x1
#घोषणा FV_CONFIG0_ASDM_FULL                 0x2
#घोषणा FV_CONFIG0_ASDM_AUTO                 0x3
#घोषणा FV_CONFIG0_DSDM_HALF                 0x1
#घोषणा FV_CONFIG0_DSDM_FULL                 0x2
#घोषणा FV_CONFIG0_DSDM_AUTO                 0x3
#घोषणा FV_CONFIG0_DC_BYPASS_ENABLE          0x1
#घोषणा FV_CONFIG0_DC_BYPASS_DISABLE         0x0
#घोषणा FV_CONFIG0_SD_FORCE_ON_ENABLE        0x1
#घोषणा FV_CONFIG0_SD_FORCE_ON_DISABLE       0x0

/* Register Masks */
#घोषणा RM_CONFIG0_ASDM \
	 RM(FM_CONFIG0_ASDM, FB_CONFIG0_ASDM)

#घोषणा RM_CONFIG0_DSDM \
	 RM(FM_CONFIG0_DSDM, FB_CONFIG0_DSDM)

#घोषणा RM_CONFIG0_DC_BYPASS \
	 RM(FM_CONFIG0_DC_BYPASS, FB_CONFIG0_DC_BYPASS)

#घोषणा RM_CONFIG0_SD_FORCE_ON \
	 RM(FM_CONFIG0_SD_FORCE_ON, FB_CONFIG0_SD_FORCE_ON)


/* Register Values */
#घोषणा RV_CONFIG0_ASDM_HALF \
	 RV(FV_CONFIG0_ASDM_HALF, FB_CONFIG0_ASDM)

#घोषणा RV_CONFIG0_ASDM_FULL \
	 RV(FV_CONFIG0_ASDM_FULL, FB_CONFIG0_ASDM)

#घोषणा RV_CONFIG0_ASDM_AUTO \
	 RV(FV_CONFIG0_ASDM_AUTO, FB_CONFIG0_ASDM)

#घोषणा RV_CONFIG0_DSDM_HALF \
	 RV(FV_CONFIG0_DSDM_HALF, FB_CONFIG0_DSDM)

#घोषणा RV_CONFIG0_DSDM_FULL \
	 RV(FV_CONFIG0_DSDM_FULL, FB_CONFIG0_DSDM)

#घोषणा RV_CONFIG0_DSDM_AUTO \
	 RV(FV_CONFIG0_DSDM_AUTO, FB_CONFIG0_DSDM)

#घोषणा RV_CONFIG0_DC_BYPASS_ENABLE \
	 RV(FV_CONFIG0_DC_BYPASS_ENABLE, FB_CONFIG0_DC_BYPASS)

#घोषणा RV_CONFIG0_DC_BYPASS_DISABLE \
	 RV(FV_CONFIG0_DC_BYPASS_DISABLE, FB_CONFIG0_DC_BYPASS)

#घोषणा RV_CONFIG0_SD_FORCE_ON_ENABLE \
	 RV(FV_CONFIG0_SD_FORCE_ON_ENABLE, FB_CONFIG0_SD_FORCE_ON)

#घोषणा RV_CONFIG0_SD_FORCE_ON_DISABLE \
	 RV(FV_CONFIG0_SD_FORCE_ON_DISABLE, FB_CONFIG0_SD_FORCE_ON)


/******************************
 *      R_CONFIG1 (0x20)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_CONFIG1_EQ2_EN                    7
#घोषणा FB_CONFIG1_EQ2_BE                    4
#घोषणा FB_CONFIG1_EQ1_EN                    3
#घोषणा FB_CONFIG1_EQ1_BE                    0

/* Field Masks */
#घोषणा FM_CONFIG1_EQ2_EN                    0X1
#घोषणा FM_CONFIG1_EQ2_BE                    0X7
#घोषणा FM_CONFIG1_EQ1_EN                    0X1
#घोषणा FM_CONFIG1_EQ1_BE                    0X7

/* Field Values */
#घोषणा FV_CONFIG1_EQ2_EN_ENABLE             0x1
#घोषणा FV_CONFIG1_EQ2_EN_DISABLE            0x0
#घोषणा FV_CONFIG1_EQ2_BE_PRE                0x0
#घोषणा FV_CONFIG1_EQ2_BE_PRE_EQ_0           0x1
#घोषणा FV_CONFIG1_EQ2_BE_PRE_EQ0_1          0x2
#घोषणा FV_CONFIG1_EQ2_BE_PRE_EQ0_2          0x3
#घोषणा FV_CONFIG1_EQ2_BE_PRE_EQ0_3          0x4
#घोषणा FV_CONFIG1_EQ2_BE_PRE_EQ0_4          0x5
#घोषणा FV_CONFIG1_EQ2_BE_PRE_EQ0_5          0x6
#घोषणा FV_CONFIG1_EQ1_EN_ENABLE             0x1
#घोषणा FV_CONFIG1_EQ1_EN_DISABLE            0x0
#घोषणा FV_CONFIG1_EQ1_BE_PRE                0x0
#घोषणा FV_CONFIG1_EQ1_BE_PRE_EQ_0           0x1
#घोषणा FV_CONFIG1_EQ1_BE_PRE_EQ0_1          0x2
#घोषणा FV_CONFIG1_EQ1_BE_PRE_EQ0_2          0x3
#घोषणा FV_CONFIG1_EQ1_BE_PRE_EQ0_3          0x4
#घोषणा FV_CONFIG1_EQ1_BE_PRE_EQ0_4          0x5
#घोषणा FV_CONFIG1_EQ1_BE_PRE_EQ0_5          0x6

/* Register Masks */
#घोषणा RM_CONFIG1_EQ2_EN \
	 RM(FM_CONFIG1_EQ2_EN, FB_CONFIG1_EQ2_EN)

#घोषणा RM_CONFIG1_EQ2_BE \
	 RM(FM_CONFIG1_EQ2_BE, FB_CONFIG1_EQ2_BE)

#घोषणा RM_CONFIG1_EQ1_EN \
	 RM(FM_CONFIG1_EQ1_EN, FB_CONFIG1_EQ1_EN)

#घोषणा RM_CONFIG1_EQ1_BE \
	 RM(FM_CONFIG1_EQ1_BE, FB_CONFIG1_EQ1_BE)


/* Register Values */
#घोषणा RV_CONFIG1_EQ2_EN_ENABLE \
	 RV(FV_CONFIG1_EQ2_EN_ENABLE, FB_CONFIG1_EQ2_EN)

#घोषणा RV_CONFIG1_EQ2_EN_DISABLE \
	 RV(FV_CONFIG1_EQ2_EN_DISABLE, FB_CONFIG1_EQ2_EN)

#घोषणा RV_CONFIG1_EQ2_BE_PRE \
	 RV(FV_CONFIG1_EQ2_BE_PRE, FB_CONFIG1_EQ2_BE)

#घोषणा RV_CONFIG1_EQ2_BE_PRE_EQ_0 \
	 RV(FV_CONFIG1_EQ2_BE_PRE_EQ_0, FB_CONFIG1_EQ2_BE)

#घोषणा RV_CONFIG1_EQ2_BE_PRE_EQ0_1 \
	 RV(FV_CONFIG1_EQ2_BE_PRE_EQ0_1, FB_CONFIG1_EQ2_BE)

#घोषणा RV_CONFIG1_EQ2_BE_PRE_EQ0_2 \
	 RV(FV_CONFIG1_EQ2_BE_PRE_EQ0_2, FB_CONFIG1_EQ2_BE)

#घोषणा RV_CONFIG1_EQ2_BE_PRE_EQ0_3 \
	 RV(FV_CONFIG1_EQ2_BE_PRE_EQ0_3, FB_CONFIG1_EQ2_BE)

#घोषणा RV_CONFIG1_EQ2_BE_PRE_EQ0_4 \
	 RV(FV_CONFIG1_EQ2_BE_PRE_EQ0_4, FB_CONFIG1_EQ2_BE)

#घोषणा RV_CONFIG1_EQ2_BE_PRE_EQ0_5 \
	 RV(FV_CONFIG1_EQ2_BE_PRE_EQ0_5, FB_CONFIG1_EQ2_BE)

#घोषणा RV_CONFIG1_EQ1_EN_ENABLE \
	 RV(FV_CONFIG1_EQ1_EN_ENABLE, FB_CONFIG1_EQ1_EN)

#घोषणा RV_CONFIG1_EQ1_EN_DISABLE \
	 RV(FV_CONFIG1_EQ1_EN_DISABLE, FB_CONFIG1_EQ1_EN)

#घोषणा RV_CONFIG1_EQ1_BE_PRE \
	 RV(FV_CONFIG1_EQ1_BE_PRE, FB_CONFIG1_EQ1_BE)

#घोषणा RV_CONFIG1_EQ1_BE_PRE_EQ_0 \
	 RV(FV_CONFIG1_EQ1_BE_PRE_EQ_0, FB_CONFIG1_EQ1_BE)

#घोषणा RV_CONFIG1_EQ1_BE_PRE_EQ0_1 \
	 RV(FV_CONFIG1_EQ1_BE_PRE_EQ0_1, FB_CONFIG1_EQ1_BE)

#घोषणा RV_CONFIG1_EQ1_BE_PRE_EQ0_2 \
	 RV(FV_CONFIG1_EQ1_BE_PRE_EQ0_2, FB_CONFIG1_EQ1_BE)

#घोषणा RV_CONFIG1_EQ1_BE_PRE_EQ0_3 \
	 RV(FV_CONFIG1_EQ1_BE_PRE_EQ0_3, FB_CONFIG1_EQ1_BE)

#घोषणा RV_CONFIG1_EQ1_BE_PRE_EQ0_4 \
	 RV(FV_CONFIG1_EQ1_BE_PRE_EQ0_4, FB_CONFIG1_EQ1_BE)

#घोषणा RV_CONFIG1_EQ1_BE_PRE_EQ0_5 \
	 RV(FV_CONFIG1_EQ1_BE_PRE_EQ0_5, FB_CONFIG1_EQ1_BE)


/******************************
 *      R_DMICCTL (0x24)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_DMICCTL_DMICEN                    7
#घोषणा FB_DMICCTL_DMONO                     4
#घोषणा FB_DMICCTL_DMPHADJ                   2
#घोषणा FB_DMICCTL_DMRATE                    0

/* Field Masks */
#घोषणा FM_DMICCTL_DMICEN                    0X1
#घोषणा FM_DMICCTL_DMONO                     0X1
#घोषणा FM_DMICCTL_DMPHADJ                   0X3
#घोषणा FM_DMICCTL_DMRATE                    0X3

/* Field Values */
#घोषणा FV_DMICCTL_DMICEN_ENABLE             0x1
#घोषणा FV_DMICCTL_DMICEN_DISABLE            0x0
#घोषणा FV_DMICCTL_DMONO_STEREO              0x0
#घोषणा FV_DMICCTL_DMONO_MONO                0x1

/* Register Masks */
#घोषणा RM_DMICCTL_DMICEN \
	 RM(FM_DMICCTL_DMICEN, FB_DMICCTL_DMICEN)

#घोषणा RM_DMICCTL_DMONO \
	 RM(FM_DMICCTL_DMONO, FB_DMICCTL_DMONO)

#घोषणा RM_DMICCTL_DMPHADJ \
	 RM(FM_DMICCTL_DMPHADJ, FB_DMICCTL_DMPHADJ)

#घोषणा RM_DMICCTL_DMRATE \
	 RM(FM_DMICCTL_DMRATE, FB_DMICCTL_DMRATE)


/* Register Values */
#घोषणा RV_DMICCTL_DMICEN_ENABLE \
	 RV(FV_DMICCTL_DMICEN_ENABLE, FB_DMICCTL_DMICEN)

#घोषणा RV_DMICCTL_DMICEN_DISABLE \
	 RV(FV_DMICCTL_DMICEN_DISABLE, FB_DMICCTL_DMICEN)

#घोषणा RV_DMICCTL_DMONO_STEREO \
	 RV(FV_DMICCTL_DMONO_STEREO, FB_DMICCTL_DMONO)

#घोषणा RV_DMICCTL_DMONO_MONO \
	 RV(FV_DMICCTL_DMONO_MONO, FB_DMICCTL_DMONO)


/*****************************
 *      R_CLECTL (0x25)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_CLECTL_LVL_MODE                   4
#घोषणा FB_CLECTL_WINDOWSEL                  3
#घोषणा FB_CLECTL_EXP_EN                     2
#घोषणा FB_CLECTL_LIMIT_EN                   1
#घोषणा FB_CLECTL_COMP_EN                    0

/* Field Masks */
#घोषणा FM_CLECTL_LVL_MODE                   0X1
#घोषणा FM_CLECTL_WINDOWSEL                  0X1
#घोषणा FM_CLECTL_EXP_EN                     0X1
#घोषणा FM_CLECTL_LIMIT_EN                   0X1
#घोषणा FM_CLECTL_COMP_EN                    0X1

/* Field Values */
#घोषणा FV_CLECTL_LVL_MODE_AVG               0x0
#घोषणा FV_CLECTL_LVL_MODE_PEAK              0x1
#घोषणा FV_CLECTL_WINDOWSEL_512              0x0
#घोषणा FV_CLECTL_WINDOWSEL_64               0x1
#घोषणा FV_CLECTL_EXP_EN_ENABLE              0x1
#घोषणा FV_CLECTL_EXP_EN_DISABLE             0x0
#घोषणा FV_CLECTL_LIMIT_EN_ENABLE            0x1
#घोषणा FV_CLECTL_LIMIT_EN_DISABLE           0x0
#घोषणा FV_CLECTL_COMP_EN_ENABLE             0x1
#घोषणा FV_CLECTL_COMP_EN_DISABLE            0x0

/* Register Masks */
#घोषणा RM_CLECTL_LVL_MODE \
	 RM(FM_CLECTL_LVL_MODE, FB_CLECTL_LVL_MODE)

#घोषणा RM_CLECTL_WINDOWSEL \
	 RM(FM_CLECTL_WINDOWSEL, FB_CLECTL_WINDOWSEL)

#घोषणा RM_CLECTL_EXP_EN \
	 RM(FM_CLECTL_EXP_EN, FB_CLECTL_EXP_EN)

#घोषणा RM_CLECTL_LIMIT_EN \
	 RM(FM_CLECTL_LIMIT_EN, FB_CLECTL_LIMIT_EN)

#घोषणा RM_CLECTL_COMP_EN \
	 RM(FM_CLECTL_COMP_EN, FB_CLECTL_COMP_EN)


/* Register Values */
#घोषणा RV_CLECTL_LVL_MODE_AVG \
	 RV(FV_CLECTL_LVL_MODE_AVG, FB_CLECTL_LVL_MODE)

#घोषणा RV_CLECTL_LVL_MODE_PEAK \
	 RV(FV_CLECTL_LVL_MODE_PEAK, FB_CLECTL_LVL_MODE)

#घोषणा RV_CLECTL_WINDOWSEL_512 \
	 RV(FV_CLECTL_WINDOWSEL_512, FB_CLECTL_WINDOWSEL)

#घोषणा RV_CLECTL_WINDOWSEL_64 \
	 RV(FV_CLECTL_WINDOWSEL_64, FB_CLECTL_WINDOWSEL)

#घोषणा RV_CLECTL_EXP_EN_ENABLE \
	 RV(FV_CLECTL_EXP_EN_ENABLE, FB_CLECTL_EXP_EN)

#घोषणा RV_CLECTL_EXP_EN_DISABLE \
	 RV(FV_CLECTL_EXP_EN_DISABLE, FB_CLECTL_EXP_EN)

#घोषणा RV_CLECTL_LIMIT_EN_ENABLE \
	 RV(FV_CLECTL_LIMIT_EN_ENABLE, FB_CLECTL_LIMIT_EN)

#घोषणा RV_CLECTL_LIMIT_EN_DISABLE \
	 RV(FV_CLECTL_LIMIT_EN_DISABLE, FB_CLECTL_LIMIT_EN)

#घोषणा RV_CLECTL_COMP_EN_ENABLE \
	 RV(FV_CLECTL_COMP_EN_ENABLE, FB_CLECTL_COMP_EN)

#घोषणा RV_CLECTL_COMP_EN_DISABLE \
	 RV(FV_CLECTL_COMP_EN_DISABLE, FB_CLECTL_COMP_EN)


/*****************************
 *      R_MUGAIN (0x26)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_MUGAIN_CLEMUG                     0

/* Field Masks */
#घोषणा FM_MUGAIN_CLEMUG                     0X1F

/* Field Values */
#घोषणा FV_MUGAIN_CLEMUG_46PT5DB             0x1F
#घोषणा FV_MUGAIN_CLEMUG_0DB                 0x0

/* Register Masks */
#घोषणा RM_MUGAIN_CLEMUG \
	 RM(FM_MUGAIN_CLEMUG, FB_MUGAIN_CLEMUG)


/* Register Values */
#घोषणा RV_MUGAIN_CLEMUG_46PT5DB \
	 RV(FV_MUGAIN_CLEMUG_46PT5DB, FB_MUGAIN_CLEMUG)

#घोषणा RV_MUGAIN_CLEMUG_0DB \
	 RV(FV_MUGAIN_CLEMUG_0DB, FB_MUGAIN_CLEMUG)


/*****************************
 *      R_COMPTH (0x27)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_COMPTH                            0

/* Field Masks */
#घोषणा FM_COMPTH                            0XFF

/* Field Values */
#घोषणा FV_COMPTH_0DB                        0xFF
#घोषणा FV_COMPTH_N95PT625DB                 0x0

/* Register Masks */
#घोषणा RM_COMPTH                            RM(FM_COMPTH, FB_COMPTH)

/* Register Values */
#घोषणा RV_COMPTH_0DB                        RV(FV_COMPTH_0DB, FB_COMPTH)
#घोषणा RV_COMPTH_N95PT625DB \
	 RV(FV_COMPTH_N95PT625DB, FB_COMPTH)


/*****************************
 *      R_CMPRAT (0x28)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_CMPRAT                            0

/* Field Masks */
#घोषणा FM_CMPRAT                            0X1F

/* Register Masks */
#घोषणा RM_CMPRAT                            RM(FM_CMPRAT, FB_CMPRAT)

/******************************
 *      R_CATKTCL (0x29)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_CATKTCL                           0

/* Field Masks */
#घोषणा FM_CATKTCL                           0XFF

/* Register Masks */
#घोषणा RM_CATKTCL                           RM(FM_CATKTCL, FB_CATKTCL)

/******************************
 *      R_CATKTCH (0x2A)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_CATKTCH                           0

/* Field Masks */
#घोषणा FM_CATKTCH                           0XFF

/* Register Masks */
#घोषणा RM_CATKTCH                           RM(FM_CATKTCH, FB_CATKTCH)

/******************************
 *      R_CRELTCL (0x2B)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_CRELTCL                           0

/* Field Masks */
#घोषणा FM_CRELTCL                           0XFF

/* Register Masks */
#घोषणा RM_CRELTCL                           RM(FM_CRELTCL, FB_CRELTCL)

/******************************
 *      R_CRELTCH (0x2C)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_CRELTCH                           0

/* Field Masks */
#घोषणा FM_CRELTCH                           0XFF

/* Register Masks */
#घोषणा RM_CRELTCH                           RM(FM_CRELTCH, FB_CRELTCH)

/****************************
 *      R_LIMTH (0x2D)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_LIMTH                             0

/* Field Masks */
#घोषणा FM_LIMTH                             0XFF

/* Field Values */
#घोषणा FV_LIMTH_0DB                         0xFF
#घोषणा FV_LIMTH_N95PT625DB                  0x0

/* Register Masks */
#घोषणा RM_LIMTH                             RM(FM_LIMTH, FB_LIMTH)

/* Register Values */
#घोषणा RV_LIMTH_0DB                         RV(FV_LIMTH_0DB, FB_LIMTH)
#घोषणा RV_LIMTH_N95PT625DB                  RV(FV_LIMTH_N95PT625DB, FB_LIMTH)

/*****************************
 *      R_LIMTGT (0x2E)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_LIMTGT                            0

/* Field Masks */
#घोषणा FM_LIMTGT                            0XFF

/* Field Values */
#घोषणा FV_LIMTGT_0DB                        0xFF
#घोषणा FV_LIMTGT_N95PT625DB                 0x0

/* Register Masks */
#घोषणा RM_LIMTGT                            RM(FM_LIMTGT, FB_LIMTGT)

/* Register Values */
#घोषणा RV_LIMTGT_0DB                        RV(FV_LIMTGT_0DB, FB_LIMTGT)
#घोषणा RV_LIMTGT_N95PT625DB \
	 RV(FV_LIMTGT_N95PT625DB, FB_LIMTGT)


/******************************
 *      R_LATKTCL (0x2F)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_LATKTCL                           0

/* Field Masks */
#घोषणा FM_LATKTCL                           0XFF

/* Register Masks */
#घोषणा RM_LATKTCL                           RM(FM_LATKTCL, FB_LATKTCL)

/******************************
 *      R_LATKTCH (0x30)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_LATKTCH                           0

/* Field Masks */
#घोषणा FM_LATKTCH                           0XFF

/* Register Masks */
#घोषणा RM_LATKTCH                           RM(FM_LATKTCH, FB_LATKTCH)

/******************************
 *      R_LRELTCL (0x31)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_LRELTCL                           0

/* Field Masks */
#घोषणा FM_LRELTCL                           0XFF

/* Register Masks */
#घोषणा RM_LRELTCL                           RM(FM_LRELTCL, FB_LRELTCL)

/******************************
 *      R_LRELTCH (0x32)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_LRELTCH                           0

/* Field Masks */
#घोषणा FM_LRELTCH                           0XFF

/* Register Masks */
#घोषणा RM_LRELTCH                           RM(FM_LRELTCH, FB_LRELTCH)

/****************************
 *      R_EXPTH (0x33)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_EXPTH                             0

/* Field Masks */
#घोषणा FM_EXPTH                             0XFF

/* Field Values */
#घोषणा FV_EXPTH_0DB                         0xFF
#घोषणा FV_EXPTH_N95PT625DB                  0x0

/* Register Masks */
#घोषणा RM_EXPTH                             RM(FM_EXPTH, FB_EXPTH)

/* Register Values */
#घोषणा RV_EXPTH_0DB                         RV(FV_EXPTH_0DB, FB_EXPTH)
#घोषणा RV_EXPTH_N95PT625DB                  RV(FV_EXPTH_N95PT625DB, FB_EXPTH)

/*****************************
 *      R_EXPRAT (0x34)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_EXPRAT                            0

/* Field Masks */
#घोषणा FM_EXPRAT                            0X7

/* Register Masks */
#घोषणा RM_EXPRAT                            RM(FM_EXPRAT, FB_EXPRAT)

/******************************
 *      R_XATKTCL (0x35)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_XATKTCL                           0

/* Field Masks */
#घोषणा FM_XATKTCL                           0XFF

/* Register Masks */
#घोषणा RM_XATKTCL                           RM(FM_XATKTCL, FB_XATKTCL)

/******************************
 *      R_XATKTCH (0x36)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_XATKTCH                           0

/* Field Masks */
#घोषणा FM_XATKTCH                           0XFF

/* Register Masks */
#घोषणा RM_XATKTCH                           RM(FM_XATKTCH, FB_XATKTCH)

/******************************
 *      R_XRELTCL (0x37)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_XRELTCL                           0

/* Field Masks */
#घोषणा FM_XRELTCL                           0XFF

/* Register Masks */
#घोषणा RM_XRELTCL                           RM(FM_XRELTCL, FB_XRELTCL)

/******************************
 *      R_XRELTCH (0x38)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_XRELTCH                           0

/* Field Masks */
#घोषणा FM_XRELTCH                           0XFF

/* Register Masks */
#घोषणा RM_XRELTCH                           RM(FM_XRELTCH, FB_XRELTCH)

/****************************
 *      R_FXCTL (0x39)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_FXCTL_3DEN                        4
#घोषणा FB_FXCTL_TEEN                        3
#घोषणा FB_FXCTL_TNLFBYPASS                  2
#घोषणा FB_FXCTL_BEEN                        1
#घोषणा FB_FXCTL_BNLFBYPASS                  0

/* Field Masks */
#घोषणा FM_FXCTL_3DEN                        0X1
#घोषणा FM_FXCTL_TEEN                        0X1
#घोषणा FM_FXCTL_TNLFBYPASS                  0X1
#घोषणा FM_FXCTL_BEEN                        0X1
#घोषणा FM_FXCTL_BNLFBYPASS                  0X1

/* Field Values */
#घोषणा FV_FXCTL_3DEN_ENABLE                 0x1
#घोषणा FV_FXCTL_3DEN_DISABLE                0x0
#घोषणा FV_FXCTL_TEEN_ENABLE                 0x1
#घोषणा FV_FXCTL_TEEN_DISABLE                0x0
#घोषणा FV_FXCTL_TNLFBYPASS_ENABLE           0x1
#घोषणा FV_FXCTL_TNLFBYPASS_DISABLE          0x0
#घोषणा FV_FXCTL_BEEN_ENABLE                 0x1
#घोषणा FV_FXCTL_BEEN_DISABLE                0x0
#घोषणा FV_FXCTL_BNLFBYPASS_ENABLE           0x1
#घोषणा FV_FXCTL_BNLFBYPASS_DISABLE          0x0

/* Register Masks */
#घोषणा RM_FXCTL_3DEN                        RM(FM_FXCTL_3DEN, FB_FXCTL_3DEN)
#घोषणा RM_FXCTL_TEEN                        RM(FM_FXCTL_TEEN, FB_FXCTL_TEEN)
#घोषणा RM_FXCTL_TNLFBYPASS \
	 RM(FM_FXCTL_TNLFBYPASS, FB_FXCTL_TNLFBYPASS)

#घोषणा RM_FXCTL_BEEN                        RM(FM_FXCTL_BEEN, FB_FXCTL_BEEN)
#घोषणा RM_FXCTL_BNLFBYPASS \
	 RM(FM_FXCTL_BNLFBYPASS, FB_FXCTL_BNLFBYPASS)


/* Register Values */
#घोषणा RV_FXCTL_3DEN_ENABLE \
	 RV(FV_FXCTL_3DEN_ENABLE, FB_FXCTL_3DEN)

#घोषणा RV_FXCTL_3DEN_DISABLE \
	 RV(FV_FXCTL_3DEN_DISABLE, FB_FXCTL_3DEN)

#घोषणा RV_FXCTL_TEEN_ENABLE \
	 RV(FV_FXCTL_TEEN_ENABLE, FB_FXCTL_TEEN)

#घोषणा RV_FXCTL_TEEN_DISABLE \
	 RV(FV_FXCTL_TEEN_DISABLE, FB_FXCTL_TEEN)

#घोषणा RV_FXCTL_TNLFBYPASS_ENABLE \
	 RV(FV_FXCTL_TNLFBYPASS_ENABLE, FB_FXCTL_TNLFBYPASS)

#घोषणा RV_FXCTL_TNLFBYPASS_DISABLE \
	 RV(FV_FXCTL_TNLFBYPASS_DISABLE, FB_FXCTL_TNLFBYPASS)

#घोषणा RV_FXCTL_BEEN_ENABLE \
	 RV(FV_FXCTL_BEEN_ENABLE, FB_FXCTL_BEEN)

#घोषणा RV_FXCTL_BEEN_DISABLE \
	 RV(FV_FXCTL_BEEN_DISABLE, FB_FXCTL_BEEN)

#घोषणा RV_FXCTL_BNLFBYPASS_ENABLE \
	 RV(FV_FXCTL_BNLFBYPASS_ENABLE, FB_FXCTL_BNLFBYPASS)

#घोषणा RV_FXCTL_BNLFBYPASS_DISABLE \
	 RV(FV_FXCTL_BNLFBYPASS_DISABLE, FB_FXCTL_BNLFBYPASS)


/*******************************
 *      R_DACCRWRL (0x3A)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_DACCRWRL_DACCRWDL                 0

/* Field Masks */
#घोषणा FM_DACCRWRL_DACCRWDL                 0XFF

/* Register Masks */
#घोषणा RM_DACCRWRL_DACCRWDL \
	 RM(FM_DACCRWRL_DACCRWDL, FB_DACCRWRL_DACCRWDL)


/*******************************
 *      R_DACCRWRM (0x3B)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_DACCRWRM_DACCRWDM                 0

/* Field Masks */
#घोषणा FM_DACCRWRM_DACCRWDM                 0XFF

/* Register Masks */
#घोषणा RM_DACCRWRM_DACCRWDM \
	 RM(FM_DACCRWRM_DACCRWDM, FB_DACCRWRM_DACCRWDM)


/*******************************
 *      R_DACCRWRH (0x3C)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_DACCRWRH_DACCRWDH                 0

/* Field Masks */
#घोषणा FM_DACCRWRH_DACCRWDH                 0XFF

/* Register Masks */
#घोषणा RM_DACCRWRH_DACCRWDH \
	 RM(FM_DACCRWRH_DACCRWDH, FB_DACCRWRH_DACCRWDH)


/*******************************
 *      R_DACCRRDL (0x3D)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_DACCRRDL                          0

/* Field Masks */
#घोषणा FM_DACCRRDL                          0XFF

/* Register Masks */
#घोषणा RM_DACCRRDL                          RM(FM_DACCRRDL, FB_DACCRRDL)

/*******************************
 *      R_DACCRRDM (0x3E)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_DACCRRDM                          0

/* Field Masks */
#घोषणा FM_DACCRRDM                          0XFF

/* Register Masks */
#घोषणा RM_DACCRRDM                          RM(FM_DACCRRDM, FB_DACCRRDM)

/*******************************
 *      R_DACCRRDH (0x3F)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_DACCRRDH                          0

/* Field Masks */
#घोषणा FM_DACCRRDH                          0XFF

/* Register Masks */
#घोषणा RM_DACCRRDH                          RM(FM_DACCRRDH, FB_DACCRRDH)

/********************************
 *      R_DACCRADDR (0x40)      *
 ********************************/

/* Field Offsets */
#घोषणा FB_DACCRADDR_DACCRADD                0

/* Field Masks */
#घोषणा FM_DACCRADDR_DACCRADD                0XFF

/* Register Masks */
#घोषणा RM_DACCRADDR_DACCRADD \
	 RM(FM_DACCRADDR_DACCRADD, FB_DACCRADDR_DACCRADD)


/******************************
 *      R_DCOFSEL (0x41)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_DCOFSEL_DC_COEF_SEL               0

/* Field Masks */
#घोषणा FM_DCOFSEL_DC_COEF_SEL               0X7

/* Field Values */
#घोषणा FV_DCOFSEL_DC_COEF_SEL_2_N8          0x0
#घोषणा FV_DCOFSEL_DC_COEF_SEL_2_N9          0x1
#घोषणा FV_DCOFSEL_DC_COEF_SEL_2_N10         0x2
#घोषणा FV_DCOFSEL_DC_COEF_SEL_2_N11         0x3
#घोषणा FV_DCOFSEL_DC_COEF_SEL_2_N12         0x4
#घोषणा FV_DCOFSEL_DC_COEF_SEL_2_N13         0x5
#घोषणा FV_DCOFSEL_DC_COEF_SEL_2_N14         0x6
#घोषणा FV_DCOFSEL_DC_COEF_SEL_2_N15         0x7

/* Register Masks */
#घोषणा RM_DCOFSEL_DC_COEF_SEL \
	 RM(FM_DCOFSEL_DC_COEF_SEL, FB_DCOFSEL_DC_COEF_SEL)


/* Register Values */
#घोषणा RV_DCOFSEL_DC_COEF_SEL_2_N8 \
	 RV(FV_DCOFSEL_DC_COEF_SEL_2_N8, FB_DCOFSEL_DC_COEF_SEL)

#घोषणा RV_DCOFSEL_DC_COEF_SEL_2_N9 \
	 RV(FV_DCOFSEL_DC_COEF_SEL_2_N9, FB_DCOFSEL_DC_COEF_SEL)

#घोषणा RV_DCOFSEL_DC_COEF_SEL_2_N10 \
	 RV(FV_DCOFSEL_DC_COEF_SEL_2_N10, FB_DCOFSEL_DC_COEF_SEL)

#घोषणा RV_DCOFSEL_DC_COEF_SEL_2_N11 \
	 RV(FV_DCOFSEL_DC_COEF_SEL_2_N11, FB_DCOFSEL_DC_COEF_SEL)

#घोषणा RV_DCOFSEL_DC_COEF_SEL_2_N12 \
	 RV(FV_DCOFSEL_DC_COEF_SEL_2_N12, FB_DCOFSEL_DC_COEF_SEL)

#घोषणा RV_DCOFSEL_DC_COEF_SEL_2_N13 \
	 RV(FV_DCOFSEL_DC_COEF_SEL_2_N13, FB_DCOFSEL_DC_COEF_SEL)

#घोषणा RV_DCOFSEL_DC_COEF_SEL_2_N14 \
	 RV(FV_DCOFSEL_DC_COEF_SEL_2_N14, FB_DCOFSEL_DC_COEF_SEL)

#घोषणा RV_DCOFSEL_DC_COEF_SEL_2_N15 \
	 RV(FV_DCOFSEL_DC_COEF_SEL_2_N15, FB_DCOFSEL_DC_COEF_SEL)


/******************************
 *      R_PLLCTL9 (0x4E)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_PLLCTL9_REFDIV_PLL1               0

/* Field Masks */
#घोषणा FM_PLLCTL9_REFDIV_PLL1               0XFF

/* Register Masks */
#घोषणा RM_PLLCTL9_REFDIV_PLL1 \
	 RM(FM_PLLCTL9_REFDIV_PLL1, FB_PLLCTL9_REFDIV_PLL1)


/******************************
 *      R_PLLCTLA (0x4F)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_PLLCTLA_OUTDIV_PLL1               0

/* Field Masks */
#घोषणा FM_PLLCTLA_OUTDIV_PLL1               0XFF

/* Register Masks */
#घोषणा RM_PLLCTLA_OUTDIV_PLL1 \
	 RM(FM_PLLCTLA_OUTDIV_PLL1, FB_PLLCTLA_OUTDIV_PLL1)


/******************************
 *      R_PLLCTLB (0x50)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_PLLCTLB_FBDIV_PLL1L               0

/* Field Masks */
#घोषणा FM_PLLCTLB_FBDIV_PLL1L               0XFF

/* Register Masks */
#घोषणा RM_PLLCTLB_FBDIV_PLL1L \
	 RM(FM_PLLCTLB_FBDIV_PLL1L, FB_PLLCTLB_FBDIV_PLL1L)


/******************************
 *      R_PLLCTLC (0x51)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_PLLCTLC_FBDIV_PLL1H               0

/* Field Masks */
#घोषणा FM_PLLCTLC_FBDIV_PLL1H               0X7

/* Register Masks */
#घोषणा RM_PLLCTLC_FBDIV_PLL1H \
	 RM(FM_PLLCTLC_FBDIV_PLL1H, FB_PLLCTLC_FBDIV_PLL1H)


/******************************
 *      R_PLLCTLD (0x52)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_PLLCTLD_RZ_PLL1                   3
#घोषणा FB_PLLCTLD_CP_PLL1                   0

/* Field Masks */
#घोषणा FM_PLLCTLD_RZ_PLL1                   0X7
#घोषणा FM_PLLCTLD_CP_PLL1                   0X7

/* Register Masks */
#घोषणा RM_PLLCTLD_RZ_PLL1 \
	 RM(FM_PLLCTLD_RZ_PLL1, FB_PLLCTLD_RZ_PLL1)

#घोषणा RM_PLLCTLD_CP_PLL1 \
	 RM(FM_PLLCTLD_CP_PLL1, FB_PLLCTLD_CP_PLL1)


/******************************
 *      R_PLLCTLE (0x53)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_PLLCTLE_REFDIV_PLL2               0

/* Field Masks */
#घोषणा FM_PLLCTLE_REFDIV_PLL2               0XFF

/* Register Masks */
#घोषणा RM_PLLCTLE_REFDIV_PLL2 \
	 RM(FM_PLLCTLE_REFDIV_PLL2, FB_PLLCTLE_REFDIV_PLL2)


/******************************
 *      R_PLLCTLF (0x54)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_PLLCTLF_OUTDIV_PLL2               0

/* Field Masks */
#घोषणा FM_PLLCTLF_OUTDIV_PLL2               0XFF

/* Register Masks */
#घोषणा RM_PLLCTLF_OUTDIV_PLL2 \
	 RM(FM_PLLCTLF_OUTDIV_PLL2, FB_PLLCTLF_OUTDIV_PLL2)


/*******************************
 *      R_PLLCTL10 (0x55)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_PLLCTL10_FBDIV_PLL2L              0

/* Field Masks */
#घोषणा FM_PLLCTL10_FBDIV_PLL2L              0XFF

/* Register Masks */
#घोषणा RM_PLLCTL10_FBDIV_PLL2L \
	 RM(FM_PLLCTL10_FBDIV_PLL2L, FB_PLLCTL10_FBDIV_PLL2L)


/*******************************
 *      R_PLLCTL11 (0x56)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_PLLCTL11_FBDIV_PLL2H              0

/* Field Masks */
#घोषणा FM_PLLCTL11_FBDIV_PLL2H              0X7

/* Register Masks */
#घोषणा RM_PLLCTL11_FBDIV_PLL2H \
	 RM(FM_PLLCTL11_FBDIV_PLL2H, FB_PLLCTL11_FBDIV_PLL2H)


/*******************************
 *      R_PLLCTL12 (0x57)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_PLLCTL12_RZ_PLL2                  3
#घोषणा FB_PLLCTL12_CP_PLL2                  0

/* Field Masks */
#घोषणा FM_PLLCTL12_RZ_PLL2                  0X7
#घोषणा FM_PLLCTL12_CP_PLL2                  0X7

/* Register Masks */
#घोषणा RM_PLLCTL12_RZ_PLL2 \
	 RM(FM_PLLCTL12_RZ_PLL2, FB_PLLCTL12_RZ_PLL2)

#घोषणा RM_PLLCTL12_CP_PLL2 \
	 RM(FM_PLLCTL12_CP_PLL2, FB_PLLCTL12_CP_PLL2)


/*******************************
 *      R_PLLCTL1B (0x60)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_PLLCTL1B_VCOI_PLL2                4
#घोषणा FB_PLLCTL1B_VCOI_PLL1                2

/* Field Masks */
#घोषणा FM_PLLCTL1B_VCOI_PLL2                0X3
#घोषणा FM_PLLCTL1B_VCOI_PLL1                0X3

/* Register Masks */
#घोषणा RM_PLLCTL1B_VCOI_PLL2 \
	 RM(FM_PLLCTL1B_VCOI_PLL2, FB_PLLCTL1B_VCOI_PLL2)

#घोषणा RM_PLLCTL1B_VCOI_PLL1 \
	 RM(FM_PLLCTL1B_VCOI_PLL1, FB_PLLCTL1B_VCOI_PLL1)


/*******************************
 *      R_PLLCTL1C (0x61)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_PLLCTL1C_PDB_PLL2                 2
#घोषणा FB_PLLCTL1C_PDB_PLL1                 1

/* Field Masks */
#घोषणा FM_PLLCTL1C_PDB_PLL2                 0X1
#घोषणा FM_PLLCTL1C_PDB_PLL1                 0X1

/* Field Values */
#घोषणा FV_PLLCTL1C_PDB_PLL2_ENABLE          0x1
#घोषणा FV_PLLCTL1C_PDB_PLL2_DISABLE         0x0
#घोषणा FV_PLLCTL1C_PDB_PLL1_ENABLE          0x1
#घोषणा FV_PLLCTL1C_PDB_PLL1_DISABLE         0x0

/* Register Masks */
#घोषणा RM_PLLCTL1C_PDB_PLL2 \
	 RM(FM_PLLCTL1C_PDB_PLL2, FB_PLLCTL1C_PDB_PLL2)

#घोषणा RM_PLLCTL1C_PDB_PLL1 \
	 RM(FM_PLLCTL1C_PDB_PLL1, FB_PLLCTL1C_PDB_PLL1)


/* Register Values */
#घोषणा RV_PLLCTL1C_PDB_PLL2_ENABLE \
	 RV(FV_PLLCTL1C_PDB_PLL2_ENABLE, FB_PLLCTL1C_PDB_PLL2)

#घोषणा RV_PLLCTL1C_PDB_PLL2_DISABLE \
	 RV(FV_PLLCTL1C_PDB_PLL2_DISABLE, FB_PLLCTL1C_PDB_PLL2)

#घोषणा RV_PLLCTL1C_PDB_PLL1_ENABLE \
	 RV(FV_PLLCTL1C_PDB_PLL1_ENABLE, FB_PLLCTL1C_PDB_PLL1)

#घोषणा RV_PLLCTL1C_PDB_PLL1_DISABLE \
	 RV(FV_PLLCTL1C_PDB_PLL1_DISABLE, FB_PLLCTL1C_PDB_PLL1)


/*******************************
 *      R_TIMEBASE (0x77)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_TIMEBASE_DIVIDER                  0

/* Field Masks */
#घोषणा FM_TIMEBASE_DIVIDER                  0XFF

/* Register Masks */
#घोषणा RM_TIMEBASE_DIVIDER \
	 RM(FM_TIMEBASE_DIVIDER, FB_TIMEBASE_DIVIDER)


/*****************************
 *      R_DEVIDL (0x7D)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_DEVIDL_DIDL                       0

/* Field Masks */
#घोषणा FM_DEVIDL_DIDL                       0XFF

/* Register Masks */
#घोषणा RM_DEVIDL_DIDL                       RM(FM_DEVIDL_DIDL, FB_DEVIDL_DIDL)

/*****************************
 *      R_DEVIDH (0x7E)      *
 *****************************/

/* Field Offsets */
#घोषणा FB_DEVIDH_DIDH                       0

/* Field Masks */
#घोषणा FM_DEVIDH_DIDH                       0XFF

/* Register Masks */
#घोषणा RM_DEVIDH_DIDH                       RM(FM_DEVIDH_DIDH, FB_DEVIDH_DIDH)

/****************************
 *      R_RESET (0x80)      *
 ****************************/

/* Field Offsets */
#घोषणा FB_RESET                             0

/* Field Masks */
#घोषणा FM_RESET                             0XFF

/* Field Values */
#घोषणा FV_RESET_ENABLE                      0x85

/* Register Masks */
#घोषणा RM_RESET                             RM(FM_RESET, FB_RESET)

/* Register Values */
#घोषणा RV_RESET_ENABLE                      RV(FV_RESET_ENABLE, FB_RESET)

/********************************
 *      R_DACCRSTAT (0x8A)      *
 ********************************/

/* Field Offsets */
#घोषणा FB_DACCRSTAT_DACCR_BUSY              7

/* Field Masks */
#घोषणा FM_DACCRSTAT_DACCR_BUSY              0X1

/* Register Masks */
#घोषणा RM_DACCRSTAT_DACCR_BUSY \
	 RM(FM_DACCRSTAT_DACCR_BUSY, FB_DACCRSTAT_DACCR_BUSY)


/******************************
 *      R_PLLCTL0 (0x8E)      *
 ******************************/

/* Field Offsets */
#घोषणा FB_PLLCTL0_PLL2_LOCK                 1
#घोषणा FB_PLLCTL0_PLL1_LOCK                 0

/* Field Masks */
#घोषणा FM_PLLCTL0_PLL2_LOCK                 0X1
#घोषणा FM_PLLCTL0_PLL1_LOCK                 0X1

/* Register Masks */
#घोषणा RM_PLLCTL0_PLL2_LOCK \
	 RM(FM_PLLCTL0_PLL2_LOCK, FB_PLLCTL0_PLL2_LOCK)

#घोषणा RM_PLLCTL0_PLL1_LOCK \
	 RM(FM_PLLCTL0_PLL1_LOCK, FB_PLLCTL0_PLL1_LOCK)


/********************************
 *      R_PLLREFSEL (0x8F)      *
 ********************************/

/* Field Offsets */
#घोषणा FB_PLLREFSEL_PLL2_REF_SEL            4
#घोषणा FB_PLLREFSEL_PLL1_REF_SEL            0

/* Field Masks */
#घोषणा FM_PLLREFSEL_PLL2_REF_SEL            0X7
#घोषणा FM_PLLREFSEL_PLL1_REF_SEL            0X7

/* Field Values */
#घोषणा FV_PLLREFSEL_PLL2_REF_SEL_XTAL_MCLK1 0x0
#घोषणा FV_PLLREFSEL_PLL2_REF_SEL_MCLK2      0x1
#घोषणा FV_PLLREFSEL_PLL1_REF_SEL_XTAL_MCLK1 0x0
#घोषणा FV_PLLREFSEL_PLL1_REF_SEL_MCLK2      0x1

/* Register Masks */
#घोषणा RM_PLLREFSEL_PLL2_REF_SEL \
	 RM(FM_PLLREFSEL_PLL2_REF_SEL, FB_PLLREFSEL_PLL2_REF_SEL)

#घोषणा RM_PLLREFSEL_PLL1_REF_SEL \
	 RM(FM_PLLREFSEL_PLL1_REF_SEL, FB_PLLREFSEL_PLL1_REF_SEL)


/* Register Values */
#घोषणा RV_PLLREFSEL_PLL2_REF_SEL_XTAL_MCLK1 \
	 RV(FV_PLLREFSEL_PLL2_REF_SEL_XTAL_MCLK1, FB_PLLREFSEL_PLL2_REF_SEL)

#घोषणा RV_PLLREFSEL_PLL2_REF_SEL_MCLK2 \
	 RV(FV_PLLREFSEL_PLL2_REF_SEL_MCLK2, FB_PLLREFSEL_PLL2_REF_SEL)

#घोषणा RV_PLLREFSEL_PLL1_REF_SEL_XTAL_MCLK1 \
	 RV(FV_PLLREFSEL_PLL1_REF_SEL_XTAL_MCLK1, FB_PLLREFSEL_PLL1_REF_SEL)

#घोषणा RV_PLLREFSEL_PLL1_REF_SEL_MCLK2 \
	 RV(FV_PLLREFSEL_PLL1_REF_SEL_MCLK2, FB_PLLREFSEL_PLL1_REF_SEL)


/*******************************
 *      R_DACMBCEN (0xC7)      *
 *******************************/

/* Field Offsets */
#घोषणा FB_DACMBCEN_MBCEN3                   2
#घोषणा FB_DACMBCEN_MBCEN2                   1
#घोषणा FB_DACMBCEN_MBCEN1                   0

/* Field Masks */
#घोषणा FM_DACMBCEN_MBCEN3                   0X1
#घोषणा FM_DACMBCEN_MBCEN2                   0X1
#घोषणा FM_DACMBCEN_MBCEN1                   0X1

/* Register Masks */
#घोषणा RM_DACMBCEN_MBCEN3 \
	 RM(FM_DACMBCEN_MBCEN3, FB_DACMBCEN_MBCEN3)

#घोषणा RM_DACMBCEN_MBCEN2 \
	 RM(FM_DACMBCEN_MBCEN2, FB_DACMBCEN_MBCEN2)

#घोषणा RM_DACMBCEN_MBCEN1 \
	 RM(FM_DACMBCEN_MBCEN1, FB_DACMBCEN_MBCEN1)


/********************************
 *      R_DACMBCCTL (0xC8)      *
 ********************************/

/* Field Offsets */
#घोषणा FB_DACMBCCTL_LVLMODE3                5
#घोषणा FB_DACMBCCTL_WINSEL3                 4
#घोषणा FB_DACMBCCTL_LVLMODE2                3
#घोषणा FB_DACMBCCTL_WINSEL2                 2
#घोषणा FB_DACMBCCTL_LVLMODE1                1
#घोषणा FB_DACMBCCTL_WINSEL1                 0

/* Field Masks */
#घोषणा FM_DACMBCCTL_LVLMODE3                0X1
#घोषणा FM_DACMBCCTL_WINSEL3                 0X1
#घोषणा FM_DACMBCCTL_LVLMODE2                0X1
#घोषणा FM_DACMBCCTL_WINSEL2                 0X1
#घोषणा FM_DACMBCCTL_LVLMODE1                0X1
#घोषणा FM_DACMBCCTL_WINSEL1                 0X1

/* Register Masks */
#घोषणा RM_DACMBCCTL_LVLMODE3 \
	 RM(FM_DACMBCCTL_LVLMODE3, FB_DACMBCCTL_LVLMODE3)

#घोषणा RM_DACMBCCTL_WINSEL3 \
	 RM(FM_DACMBCCTL_WINSEL3, FB_DACMBCCTL_WINSEL3)

#घोषणा RM_DACMBCCTL_LVLMODE2 \
	 RM(FM_DACMBCCTL_LVLMODE2, FB_DACMBCCTL_LVLMODE2)

#घोषणा RM_DACMBCCTL_WINSEL2 \
	 RM(FM_DACMBCCTL_WINSEL2, FB_DACMBCCTL_WINSEL2)

#घोषणा RM_DACMBCCTL_LVLMODE1 \
	 RM(FM_DACMBCCTL_LVLMODE1, FB_DACMBCCTL_LVLMODE1)

#घोषणा RM_DACMBCCTL_WINSEL1 \
	 RM(FM_DACMBCCTL_WINSEL1, FB_DACMBCCTL_WINSEL1)


/*********************************
 *      R_DACMBCMUG1 (0xC9)      *
 *********************************/

/* Field Offsets */
#घोषणा FB_DACMBCMUG1_PHASE                  5
#घोषणा FB_DACMBCMUG1_MUGAIN                 0

/* Field Masks */
#घोषणा FM_DACMBCMUG1_PHASE                  0X1
#घोषणा FM_DACMBCMUG1_MUGAIN                 0X1F

/* Register Masks */
#घोषणा RM_DACMBCMUG1_PHASE \
	 RM(FM_DACMBCMUG1_PHASE, FB_DACMBCMUG1_PHASE)

#घोषणा RM_DACMBCMUG1_MUGAIN \
	 RM(FM_DACMBCMUG1_MUGAIN, FB_DACMBCMUG1_MUGAIN)


/*********************************
 *      R_DACMBCTHR1 (0xCA)      *
 *********************************/

/* Field Offsets */
#घोषणा FB_DACMBCTHR1_THRESH                 0

/* Field Masks */
#घोषणा FM_DACMBCTHR1_THRESH                 0XFF

/* Register Masks */
#घोषणा RM_DACMBCTHR1_THRESH \
	 RM(FM_DACMBCTHR1_THRESH, FB_DACMBCTHR1_THRESH)


/*********************************
 *      R_DACMBCRAT1 (0xCB)      *
 *********************************/

/* Field Offsets */
#घोषणा FB_DACMBCRAT1_RATIO                  0

/* Field Masks */
#घोषणा FM_DACMBCRAT1_RATIO                  0X1F

/* Register Masks */
#घोषणा RM_DACMBCRAT1_RATIO \
	 RM(FM_DACMBCRAT1_RATIO, FB_DACMBCRAT1_RATIO)


/**********************************
 *      R_DACMBCATK1L (0xCC)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCATK1L_TCATKL                0

/* Field Masks */
#घोषणा FM_DACMBCATK1L_TCATKL                0XFF

/* Register Masks */
#घोषणा RM_DACMBCATK1L_TCATKL \
	 RM(FM_DACMBCATK1L_TCATKL, FB_DACMBCATK1L_TCATKL)


/**********************************
 *      R_DACMBCATK1H (0xCD)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCATK1H_TCATKH                0

/* Field Masks */
#घोषणा FM_DACMBCATK1H_TCATKH                0XFF

/* Register Masks */
#घोषणा RM_DACMBCATK1H_TCATKH \
	 RM(FM_DACMBCATK1H_TCATKH, FB_DACMBCATK1H_TCATKH)


/**********************************
 *      R_DACMBCREL1L (0xCE)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCREL1L_TCRELL                0

/* Field Masks */
#घोषणा FM_DACMBCREL1L_TCRELL                0XFF

/* Register Masks */
#घोषणा RM_DACMBCREL1L_TCRELL \
	 RM(FM_DACMBCREL1L_TCRELL, FB_DACMBCREL1L_TCRELL)


/**********************************
 *      R_DACMBCREL1H (0xCF)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCREL1H_TCRELH                0

/* Field Masks */
#घोषणा FM_DACMBCREL1H_TCRELH                0XFF

/* Register Masks */
#घोषणा RM_DACMBCREL1H_TCRELH \
	 RM(FM_DACMBCREL1H_TCRELH, FB_DACMBCREL1H_TCRELH)


/*********************************
 *      R_DACMBCMUG2 (0xD0)      *
 *********************************/

/* Field Offsets */
#घोषणा FB_DACMBCMUG2_PHASE                  5
#घोषणा FB_DACMBCMUG2_MUGAIN                 0

/* Field Masks */
#घोषणा FM_DACMBCMUG2_PHASE                  0X1
#घोषणा FM_DACMBCMUG2_MUGAIN                 0X1F

/* Register Masks */
#घोषणा RM_DACMBCMUG2_PHASE \
	 RM(FM_DACMBCMUG2_PHASE, FB_DACMBCMUG2_PHASE)

#घोषणा RM_DACMBCMUG2_MUGAIN \
	 RM(FM_DACMBCMUG2_MUGAIN, FB_DACMBCMUG2_MUGAIN)


/*********************************
 *      R_DACMBCTHR2 (0xD1)      *
 *********************************/

/* Field Offsets */
#घोषणा FB_DACMBCTHR2_THRESH                 0

/* Field Masks */
#घोषणा FM_DACMBCTHR2_THRESH                 0XFF

/* Register Masks */
#घोषणा RM_DACMBCTHR2_THRESH \
	 RM(FM_DACMBCTHR2_THRESH, FB_DACMBCTHR2_THRESH)


/*********************************
 *      R_DACMBCRAT2 (0xD2)      *
 *********************************/

/* Field Offsets */
#घोषणा FB_DACMBCRAT2_RATIO                  0

/* Field Masks */
#घोषणा FM_DACMBCRAT2_RATIO                  0X1F

/* Register Masks */
#घोषणा RM_DACMBCRAT2_RATIO \
	 RM(FM_DACMBCRAT2_RATIO, FB_DACMBCRAT2_RATIO)


/**********************************
 *      R_DACMBCATK2L (0xD3)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCATK2L_TCATKL                0

/* Field Masks */
#घोषणा FM_DACMBCATK2L_TCATKL                0XFF

/* Register Masks */
#घोषणा RM_DACMBCATK2L_TCATKL \
	 RM(FM_DACMBCATK2L_TCATKL, FB_DACMBCATK2L_TCATKL)


/**********************************
 *      R_DACMBCATK2H (0xD4)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCATK2H_TCATKH                0

/* Field Masks */
#घोषणा FM_DACMBCATK2H_TCATKH                0XFF

/* Register Masks */
#घोषणा RM_DACMBCATK2H_TCATKH \
	 RM(FM_DACMBCATK2H_TCATKH, FB_DACMBCATK2H_TCATKH)


/**********************************
 *      R_DACMBCREL2L (0xD5)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCREL2L_TCRELL                0

/* Field Masks */
#घोषणा FM_DACMBCREL2L_TCRELL                0XFF

/* Register Masks */
#घोषणा RM_DACMBCREL2L_TCRELL \
	 RM(FM_DACMBCREL2L_TCRELL, FB_DACMBCREL2L_TCRELL)


/**********************************
 *      R_DACMBCREL2H (0xD6)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCREL2H_TCRELH                0

/* Field Masks */
#घोषणा FM_DACMBCREL2H_TCRELH                0XFF

/* Register Masks */
#घोषणा RM_DACMBCREL2H_TCRELH \
	 RM(FM_DACMBCREL2H_TCRELH, FB_DACMBCREL2H_TCRELH)


/*********************************
 *      R_DACMBCMUG3 (0xD7)      *
 *********************************/

/* Field Offsets */
#घोषणा FB_DACMBCMUG3_PHASE                  5
#घोषणा FB_DACMBCMUG3_MUGAIN                 0

/* Field Masks */
#घोषणा FM_DACMBCMUG3_PHASE                  0X1
#घोषणा FM_DACMBCMUG3_MUGAIN                 0X1F

/* Register Masks */
#घोषणा RM_DACMBCMUG3_PHASE \
	 RM(FM_DACMBCMUG3_PHASE, FB_DACMBCMUG3_PHASE)

#घोषणा RM_DACMBCMUG3_MUGAIN \
	 RM(FM_DACMBCMUG3_MUGAIN, FB_DACMBCMUG3_MUGAIN)


/*********************************
 *      R_DACMBCTHR3 (0xD8)      *
 *********************************/

/* Field Offsets */
#घोषणा FB_DACMBCTHR3_THRESH                 0

/* Field Masks */
#घोषणा FM_DACMBCTHR3_THRESH                 0XFF

/* Register Masks */
#घोषणा RM_DACMBCTHR3_THRESH \
	 RM(FM_DACMBCTHR3_THRESH, FB_DACMBCTHR3_THRESH)


/*********************************
 *      R_DACMBCRAT3 (0xD9)      *
 *********************************/

/* Field Offsets */
#घोषणा FB_DACMBCRAT3_RATIO                  0

/* Field Masks */
#घोषणा FM_DACMBCRAT3_RATIO                  0X1F

/* Register Masks */
#घोषणा RM_DACMBCRAT3_RATIO \
	 RM(FM_DACMBCRAT3_RATIO, FB_DACMBCRAT3_RATIO)


/**********************************
 *      R_DACMBCATK3L (0xDA)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCATK3L_TCATKL                0

/* Field Masks */
#घोषणा FM_DACMBCATK3L_TCATKL                0XFF

/* Register Masks */
#घोषणा RM_DACMBCATK3L_TCATKL \
	 RM(FM_DACMBCATK3L_TCATKL, FB_DACMBCATK3L_TCATKL)


/**********************************
 *      R_DACMBCATK3H (0xDB)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCATK3H_TCATKH                0

/* Field Masks */
#घोषणा FM_DACMBCATK3H_TCATKH                0XFF

/* Register Masks */
#घोषणा RM_DACMBCATK3H_TCATKH \
	 RM(FM_DACMBCATK3H_TCATKH, FB_DACMBCATK3H_TCATKH)


/**********************************
 *      R_DACMBCREL3L (0xDC)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCREL3L_TCRELL                0

/* Field Masks */
#घोषणा FM_DACMBCREL3L_TCRELL                0XFF

/* Register Masks */
#घोषणा RM_DACMBCREL3L_TCRELL \
	 RM(FM_DACMBCREL3L_TCRELL, FB_DACMBCREL3L_TCRELL)


/**********************************
 *      R_DACMBCREL3H (0xDD)      *
 **********************************/

/* Field Offsets */
#घोषणा FB_DACMBCREL3H_TCRELH                0

/* Field Masks */
#घोषणा FM_DACMBCREL3H_TCRELH                0XFF

/* Register Masks */
#घोषणा RM_DACMBCREL3H_TCRELH \
	 RM(FM_DACMBCREL3H_TCRELH, FB_DACMBCREL3H_TCRELH)


#पूर्ण_अगर /* __WOOKIE_H__ */
