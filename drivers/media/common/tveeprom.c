<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tveeprom - eeprom decoder क्रम tvcard configuration eeproms
 *
 * Data and decoding routines shamelessly borrowed from bttv-cards.c
 * eeprom access routine shamelessly borrowed from bttv-अगर.c
 * which are:

    Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)
			   & Marcus Metzler (mocm@thp.uni-koeln.de)
    (c) 1999-2001 Gerd Knorr <kraxel@goldbach.in-berlin.de>

 * Adjusपंचांगents to fit a more general model and all bugs:

	Copyright (C) 2003 John Klar <linpvr at projectplयंत्रa.com>

 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/i2c.h>

#समावेश <media/tuner.h>
#समावेश <media/tveeprom.h>
#समावेश <media/v4l2-common.h>

MODULE_DESCRIPTION("i2c Hauppauge eeprom decoder driver");
MODULE_AUTHOR("John Klar");
MODULE_LICENSE("GPL");

#घोषणा STRM(array, i) \
	(i < माप(array) / माप(अक्षर *) ? array[i] : "unknown")


/*
 * The Hauppauge eeprom uses an 8bit field to determine which
 * tuner क्रमmats the tuner supports.
 */
अटल स्थिर काष्ठा अणु
	पूर्णांक	id;
	स्थिर अक्षर * स्थिर name;
पूर्ण hauppauge_tuner_fmt[] = अणु
	अणु V4L2_STD_UNKNOWN,                   " UNKNOWN" पूर्ण,
	अणु V4L2_STD_UNKNOWN,                   " FM" पूर्ण,
	अणु V4L2_STD_B|V4L2_STD_GH,             " PAL(B/G)" पूर्ण,
	अणु V4L2_STD_MN,                        " NTSC(M)" पूर्ण,
	अणु V4L2_STD_PAL_I,                     " PAL(I)" पूर्ण,
	अणु V4L2_STD_SECAM_L|V4L2_STD_SECAM_LC, " SECAM(L/L')" पूर्ण,
	अणु V4L2_STD_DK,                        " PAL(D/D1/K)" पूर्ण,
	अणु V4L2_STD_ATSC,                      " ATSC/DVB Digital" पूर्ण,
पूर्ण;

/* This is the full list of possible tuners. Many thanks to Hauppauge क्रम
   supplying this inक्रमmation. Note that many tuners where only used क्रम
   testing and never made it to the outside world. So you will only see
   a subset in actual produced cards. */
अटल स्थिर काष्ठा अणु
	पूर्णांक  id;
	स्थिर अक्षर * स्थिर name;
पूर्ण hauppauge_tuner[] = अणु
	/* 0-9 */
	अणु TUNER_ABSENT,			"None" पूर्ण,
	अणु TUNER_ABSENT,			"External" पूर्ण,
	अणु TUNER_ABSENT,			"Unspecified" पूर्ण,
	अणु TUNER_PHILIPS_PAL,		"Philips FI1216" पूर्ण,
	अणु TUNER_PHILIPS_SECAM,		"Philips FI1216MF" पूर्ण,
	अणु TUNER_PHILIPS_NTSC,		"Philips FI1236" पूर्ण,
	अणु TUNER_PHILIPS_PAL_I,		"Philips FI1246" पूर्ण,
	अणु TUNER_PHILIPS_PAL_DK,		"Philips FI1256" पूर्ण,
	अणु TUNER_PHILIPS_PAL,		"Philips FI1216 MK2" पूर्ण,
	अणु TUNER_PHILIPS_SECAM,		"Philips FI1216MF MK2" पूर्ण,
	/* 10-19 */
	अणु TUNER_PHILIPS_NTSC,		"Philips FI1236 MK2" पूर्ण,
	अणु TUNER_PHILIPS_PAL_I,		"Philips FI1246 MK2" पूर्ण,
	अणु TUNER_PHILIPS_PAL_DK,		"Philips FI1256 MK2" पूर्ण,
	अणु TUNER_TEMIC_NTSC,		"Temic 4032FY5" पूर्ण,
	अणु TUNER_TEMIC_PAL,		"Temic 4002FH5" पूर्ण,
	अणु TUNER_TEMIC_PAL_I,		"Temic 4062FY5" पूर्ण,
	अणु TUNER_PHILIPS_PAL,		"Philips FR1216 MK2" पूर्ण,
	अणु TUNER_PHILIPS_SECAM,		"Philips FR1216MF MK2" पूर्ण,
	अणु TUNER_PHILIPS_NTSC,		"Philips FR1236 MK2" पूर्ण,
	अणु TUNER_PHILIPS_PAL_I,		"Philips FR1246 MK2" पूर्ण,
	/* 20-29 */
	अणु TUNER_PHILIPS_PAL_DK,		"Philips FR1256 MK2" पूर्ण,
	अणु TUNER_PHILIPS_PAL,		"Philips FM1216" पूर्ण,
	अणु TUNER_PHILIPS_SECAM,		"Philips FM1216MF" पूर्ण,
	अणु TUNER_PHILIPS_NTSC,		"Philips FM1236" पूर्ण,
	अणु TUNER_PHILIPS_PAL_I,		"Philips FM1246" पूर्ण,
	अणु TUNER_PHILIPS_PAL_DK,		"Philips FM1256" पूर्ण,
	अणु TUNER_TEMIC_4036FY5_NTSC,	"Temic 4036FY5" पूर्ण,
	अणु TUNER_ABSENT,			"Samsung TCPN9082D" पूर्ण,
	अणु TUNER_ABSENT,			"Samsung TCPM9092P" पूर्ण,
	अणु TUNER_TEMIC_4006FH5_PAL,	"Temic 4006FH5" पूर्ण,
	/* 30-39 */
	अणु TUNER_ABSENT,			"Samsung TCPN9085D" पूर्ण,
	अणु TUNER_ABSENT,			"Samsung TCPB9085P" पूर्ण,
	अणु TUNER_ABSENT,			"Samsung TCPL9091P" पूर्ण,
	अणु TUNER_TEMIC_4039FR5_NTSC,	"Temic 4039FR5" पूर्ण,
	अणु TUNER_PHILIPS_FQ1216ME,	"Philips FQ1216 ME" पूर्ण,
	अणु TUNER_TEMIC_4066FY5_PAL_I,	"Temic 4066FY5" पूर्ण,
	अणु TUNER_PHILIPS_NTSC,		"Philips TD1536" पूर्ण,
	अणु TUNER_PHILIPS_NTSC,		"Philips TD1536D" पूर्ण,
	अणु TUNER_PHILIPS_NTSC,		"Philips FMR1236" पूर्ण, /* mono radio */
	अणु TUNER_ABSENT,			"Philips FI1256MP" पूर्ण,
	/* 40-49 */
	अणु TUNER_ABSENT,			"Samsung TCPQ9091P" पूर्ण,
	अणु TUNER_TEMIC_4006FN5_MULTI_PAL,"Temic 4006FN5" पूर्ण,
	अणु TUNER_TEMIC_4009FR5_PAL,	"Temic 4009FR5" पूर्ण,
	अणु TUNER_TEMIC_4046FM5,		"Temic 4046FM5" पूर्ण,
	अणु TUNER_TEMIC_4009FN5_MULTI_PAL_FM, "Temic 4009FN5" पूर्ण,
	अणु TUNER_ABSENT,			"Philips TD1536D FH 44"पूर्ण,
	अणु TUNER_LG_NTSC_FM,		"LG TP18NSR01F"पूर्ण,
	अणु TUNER_LG_PAL_FM,		"LG TP18PSB01D"पूर्ण,
	अणु TUNER_LG_PAL,		"LG TP18PSB11D"पूर्ण,
	अणु TUNER_LG_PAL_I_FM,		"LG TAPC-I001D"पूर्ण,
	/* 50-59 */
	अणु TUNER_LG_PAL_I,		"LG TAPC-I701D"पूर्ण,
	अणु TUNER_ABSENT,			"Temic 4042FI5"पूर्ण,
	अणु TUNER_MICROTUNE_4049FM5,	"Microtune 4049 FM5"पूर्ण,
	अणु TUNER_ABSENT,			"LG TPI8NSR11F"पूर्ण,
	अणु TUNER_ABSENT,			"Microtune 4049 FM5 Alt I2C"पूर्ण,
	अणु TUNER_PHILIPS_FM1216ME_MK3,	"Philips FQ1216ME MK3"पूर्ण,
	अणु TUNER_ABSENT,			"Philips FI1236 MK3"पूर्ण,
	अणु TUNER_PHILIPS_FM1216ME_MK3,	"Philips FM1216 ME MK3"पूर्ण,
	अणु TUNER_PHILIPS_FM1236_MK3,	"Philips FM1236 MK3"पूर्ण,
	अणु TUNER_ABSENT,			"Philips FM1216MP MK3"पूर्ण,
	/* 60-69 */
	अणु TUNER_PHILIPS_FM1216ME_MK3,	"LG S001D MK3"पूर्ण,
	अणु TUNER_ABSENT,			"LG M001D MK3"पूर्ण,
	अणु TUNER_PHILIPS_FM1216ME_MK3,	"LG S701D MK3"पूर्ण,
	अणु TUNER_ABSENT,			"LG M701D MK3"पूर्ण,
	अणु TUNER_ABSENT,			"Temic 4146FM5"पूर्ण,
	अणु TUNER_ABSENT,			"Temic 4136FY5"पूर्ण,
	अणु TUNER_ABSENT,			"Temic 4106FH5"पूर्ण,
	अणु TUNER_ABSENT,			"Philips FQ1216LMP MK3"पूर्ण,
	अणु TUNER_LG_NTSC_TAPE,		"LG TAPE H001F MK3"पूर्ण,
	अणु TUNER_LG_NTSC_TAPE,		"LG TAPE H701F MK3"पूर्ण,
	/* 70-79 */
	अणु TUNER_ABSENT,			"LG TALN H200T"पूर्ण,
	अणु TUNER_ABSENT,			"LG TALN H250T"पूर्ण,
	अणु TUNER_ABSENT,			"LG TALN M200T"पूर्ण,
	अणु TUNER_ABSENT,			"LG TALN Z200T"पूर्ण,
	अणु TUNER_ABSENT,			"LG TALN S200T"पूर्ण,
	अणु TUNER_ABSENT,			"Thompson DTT7595"पूर्ण,
	अणु TUNER_ABSENT,			"Thompson DTT7592"पूर्ण,
	अणु TUNER_ABSENT,			"Silicon TDA8275C1 8290"पूर्ण,
	अणु TUNER_ABSENT,			"Silicon TDA8275C1 8290 FM"पूर्ण,
	अणु TUNER_ABSENT,			"Thompson DTT757"पूर्ण,
	/* 80-89 */
	अणु TUNER_PHILIPS_FQ1216LME_MK3,	"Philips FQ1216LME MK3"पूर्ण,
	अणु TUNER_LG_PAL_NEW_TAPC,	"LG TAPC G701D"पूर्ण,
	अणु TUNER_LG_NTSC_NEW_TAPC,	"LG TAPC H791F"पूर्ण,
	अणु TUNER_LG_PAL_NEW_TAPC,	"TCL 2002MB 3"पूर्ण,
	अणु TUNER_LG_PAL_NEW_TAPC,	"TCL 2002MI 3"पूर्ण,
	अणु TUNER_TCL_2002N,		"TCL 2002N 6A"पूर्ण,
	अणु TUNER_PHILIPS_FM1236_MK3,	"Philips FQ1236 MK3"पूर्ण,
	अणु TUNER_SAMSUNG_TCPN_2121P30A,	"Samsung TCPN 2121P30A"पूर्ण,
	अणु TUNER_ABSENT,			"Samsung TCPE 4121P30A"पूर्ण,
	अणु TUNER_PHILIPS_FM1216ME_MK3,	"TCL MFPE05 2"पूर्ण,
	/* 90-99 */
	अणु TUNER_ABSENT,			"LG TALN H202T"पूर्ण,
	अणु TUNER_PHILIPS_FQ1216AME_MK4,	"Philips FQ1216AME MK4"पूर्ण,
	अणु TUNER_PHILIPS_FQ1236A_MK4,	"Philips FQ1236A MK4"पूर्ण,
	अणु TUNER_ABSENT,			"Philips FQ1286A MK4"पूर्ण,
	अणु TUNER_ABSENT,			"Philips FQ1216ME MK5"पूर्ण,
	अणु TUNER_ABSENT,			"Philips FQ1236 MK5"पूर्ण,
	अणु TUNER_SAMSUNG_TCPG_6121P30A,	"Samsung TCPG 6121P30A"पूर्ण,
	अणु TUNER_TCL_2002MB,		"TCL 2002MB_3H"पूर्ण,
	अणु TUNER_ABSENT,			"TCL 2002MI_3H"पूर्ण,
	अणु TUNER_TCL_2002N,		"TCL 2002N 5H"पूर्ण,
	/* 100-109 */
	अणु TUNER_PHILIPS_FMD1216ME_MK3,	"Philips FMD1216ME"पूर्ण,
	अणु TUNER_TEA5767,		"Philips TEA5768HL FM Radio"पूर्ण,
	अणु TUNER_ABSENT,			"Panasonic ENV57H12D5"पूर्ण,
	अणु TUNER_PHILIPS_FM1236_MK3,	"TCL MFNM05-4"पूर्ण,
	अणु TUNER_PHILIPS_FM1236_MK3,	"TCL MNM05-4"पूर्ण,
	अणु TUNER_PHILIPS_FM1216ME_MK3,	"TCL MPE05-2"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MQNM05-4"पूर्ण,
	अणु TUNER_ABSENT,			"LG TAPC-W701D"पूर्ण,
	अणु TUNER_ABSENT,			"TCL 9886P-WM"पूर्ण,
	अणु TUNER_ABSENT,			"TCL 1676NM-WM"पूर्ण,
	/* 110-119 */
	अणु TUNER_ABSENT,			"Thompson DTT75105"पूर्ण,
	अणु TUNER_ABSENT,			"Conexant_CX24109"पूर्ण,
	अणु TUNER_TCL_2002N,		"TCL M2523_5N_E"पूर्ण,
	अणु TUNER_TCL_2002MB,		"TCL M2523_3DB_E"पूर्ण,
	अणु TUNER_ABSENT,			"Philips 8275A"पूर्ण,
	अणु TUNER_ABSENT,			"Microtune MT2060"पूर्ण,
	अणु TUNER_PHILIPS_FM1236_MK3,	"Philips FM1236 MK5"पूर्ण,
	अणु TUNER_PHILIPS_FM1216ME_MK3,	"Philips FM1216ME MK5"पूर्ण,
	अणु TUNER_ABSENT,			"TCL M2523_3DI_E"पूर्ण,
	अणु TUNER_ABSENT,			"Samsung THPD5222FG30A"पूर्ण,
	/* 120-129 */
	अणु TUNER_XC2028,			"Xceive XC3028"पूर्ण,
	अणु TUNER_PHILIPS_FQ1216LME_MK3,	"Philips FQ1216LME MK5"पूर्ण,
	अणु TUNER_ABSENT,			"Philips FQD1216LME"पूर्ण,
	अणु TUNER_ABSENT,			"Conexant CX24118A"पूर्ण,
	अणु TUNER_ABSENT,			"TCL DMF11WIP"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MFNM05_4H_E"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MNM05_4H_E"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MPE05_2H_E"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MQNM05_4_U"पूर्ण,
	अणु TUNER_ABSENT,			"TCL M2523_5NH_E"पूर्ण,
	/* 130-139 */
	अणु TUNER_ABSENT,			"TCL M2523_3DBH_E"पूर्ण,
	अणु TUNER_ABSENT,			"TCL M2523_3DIH_E"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MFPE05_2_U"पूर्ण,
	अणु TUNER_PHILIPS_FMD1216MEX_MK3,	"Philips FMD1216MEX"पूर्ण,
	अणु TUNER_ABSENT,			"Philips FRH2036B"पूर्ण,
	अणु TUNER_ABSENT,			"Panasonic ENGF75_01GF"पूर्ण,
	अणु TUNER_ABSENT,			"MaxLinear MXL5005"पूर्ण,
	अणु TUNER_ABSENT,			"MaxLinear MXL5003"पूर्ण,
	अणु TUNER_ABSENT,			"Xceive XC2028"पूर्ण,
	अणु TUNER_ABSENT,			"Microtune MT2131"पूर्ण,
	/* 140-149 */
	अणु TUNER_ABSENT,			"Philips 8275A_8295"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MF02GIP_5N_E"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MF02GIP_3DB_E"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MF02GIP_3DI_E"पूर्ण,
	अणु TUNER_ABSENT,			"Microtune MT2266"पूर्ण,
	अणु TUNER_ABSENT,			"TCL MF10WPP_4N_E"पूर्ण,
	अणु TUNER_ABSENT,			"LG TAPQ_H702F"पूर्ण,
	अणु TUNER_ABSENT,			"TCL M09WPP_4N_E"पूर्ण,
	अणु TUNER_ABSENT,			"MaxLinear MXL5005_v2"पूर्ण,
	अणु TUNER_PHILIPS_TDA8290,	"Philips 18271_8295"पूर्ण,
	/* 150-159 */
	अणु TUNER_XC5000,                 "Xceive XC5000"पूर्ण,
	अणु TUNER_ABSENT,                 "Xceive XC3028L"पूर्ण,
	अणु TUNER_ABSENT,                 "NXP 18271C2_716x"पूर्ण,
	अणु TUNER_ABSENT,                 "Xceive XC4000"पूर्ण,
	अणु TUNER_ABSENT,                 "Dibcom 7070"पूर्ण,
	अणु TUNER_PHILIPS_TDA8290,        "NXP 18271C2"पूर्ण,
	अणु TUNER_ABSENT,                 "Siano SMS1010"पूर्ण,
	अणु TUNER_ABSENT,                 "Siano SMS1150"पूर्ण,
	अणु TUNER_ABSENT,                 "MaxLinear 5007"पूर्ण,
	अणु TUNER_ABSENT,                 "TCL M09WPP_2P_E"पूर्ण,
	/* 160-169 */
	अणु TUNER_ABSENT,                 "Siano SMS1180"पूर्ण,
	अणु TUNER_ABSENT,                 "Maxim_MAX2165"पूर्ण,
	अणु TUNER_ABSENT,                 "Siano SMS1140"पूर्ण,
	अणु TUNER_ABSENT,                 "Siano SMS1150 B1"पूर्ण,
	अणु TUNER_ABSENT,                 "MaxLinear 111"पूर्ण,
	अणु TUNER_ABSENT,                 "Dibcom 7770"पूर्ण,
	अणु TUNER_ABSENT,                 "Siano SMS1180VNS"पूर्ण,
	अणु TUNER_ABSENT,                 "Siano SMS1184"पूर्ण,
	अणु TUNER_PHILIPS_FQ1236_MK5,	"TCL M30WTP-4N-E"पूर्ण,
	अणु TUNER_ABSENT,                 "TCL_M11WPP_2PN_E"पूर्ण,
	/* 170-179 */
	अणु TUNER_ABSENT,                 "MaxLinear 301"पूर्ण,
	अणु TUNER_ABSENT,                 "Mirics MSi001"पूर्ण,
	अणु TUNER_ABSENT,                 "MaxLinear MxL241SF"पूर्ण,
	अणु TUNER_XC5000C,                "Xceive XC5000C"पूर्ण,
	अणु TUNER_ABSENT,                 "Montage M68TS2020"पूर्ण,
	अणु TUNER_ABSENT,                 "Siano SMS1530"पूर्ण,
	अणु TUNER_ABSENT,                 "Dibcom 7090"पूर्ण,
	अणु TUNER_ABSENT,                 "Xceive XC5200C"पूर्ण,
	अणु TUNER_ABSENT,                 "NXP 18273"पूर्ण,
	अणु TUNER_ABSENT,                 "Montage M88TS2022"पूर्ण,
	/* 180-188 */
	अणु TUNER_ABSENT,                 "NXP 18272M"पूर्ण,
	अणु TUNER_ABSENT,                 "NXP 18272S"पूर्ण,

	अणु TUNER_ABSENT,                 "Mirics MSi003"पूर्ण,
	अणु TUNER_ABSENT,                 "MaxLinear MxL256"पूर्ण,
	अणु TUNER_ABSENT,                 "SiLabs Si2158"पूर्ण,
	अणु TUNER_ABSENT,                 "SiLabs Si2178"पूर्ण,
	अणु TUNER_ABSENT,                 "SiLabs Si2157"पूर्ण,
	अणु TUNER_ABSENT,                 "SiLabs Si2177"पूर्ण,
	अणु TUNER_ABSENT,                 "ITE IT9137FN"पूर्ण,
पूर्ण;

/* Use TVEEPROM_AUDPROC_INTERNAL क्रम those audio 'chips' that are
 * पूर्णांकernal to a video chip, i.e. not a separate audio chip. */
अटल स्थिर काष्ठा अणु
	u32   id;
	स्थिर अक्षर * स्थिर name;
पूर्ण audio_ic[] = अणु
	/* 0-4 */
	अणु TVEEPROM_AUDPROC_NONE,  "None"      पूर्ण,
	अणु TVEEPROM_AUDPROC_OTHER, "TEA6300"   पूर्ण,
	अणु TVEEPROM_AUDPROC_OTHER, "TEA6320"   पूर्ण,
	अणु TVEEPROM_AUDPROC_OTHER, "TDA9850"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3400C"  पूर्ण,
	/* 5-9 */
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3410D"  पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3415"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3430"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3438"   पूर्ण,
	अणु TVEEPROM_AUDPROC_OTHER, "CS5331"    पूर्ण,
	/* 10-14 */
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3435"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3440"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3445"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3411"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3416"   पूर्ण,
	/* 15-19 */
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3425"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3451"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP3418"   पूर्ण,
	अणु TVEEPROM_AUDPROC_OTHER, "Type 0x12" पूर्ण,
	अणु TVEEPROM_AUDPROC_OTHER, "OKI7716"   पूर्ण,
	/* 20-24 */
	अणु TVEEPROM_AUDPROC_MSP,   "MSP4410"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP4420"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP4440"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP4450"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP4408"   पूर्ण,
	/* 25-29 */
	अणु TVEEPROM_AUDPROC_MSP,   "MSP4418"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP4428"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP4448"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "MSP4458"   पूर्ण,
	अणु TVEEPROM_AUDPROC_MSP,   "Type 0x1d" पूर्ण,
	/* 30-34 */
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX880"     पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX881"     पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX883"     पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX882"     पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX25840"   पूर्ण,
	/* 35-39 */
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX25841"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX25842"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX25843"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX23418"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX23885"   पूर्ण,
	/* 40-44 */
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX23888"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "SAA7131"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX23887"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "SAA7164"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "AU8522"    पूर्ण,
	/* 45-49 */
	अणु TVEEPROM_AUDPROC_INTERNAL, "AVF4910B"  पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "SAA7231"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "CX23102"   पूर्ण,
	अणु TVEEPROM_AUDPROC_INTERNAL, "SAA7163"   पूर्ण,
	अणु TVEEPROM_AUDPROC_OTHER,    "AK4113"    पूर्ण,
	/* 50-52 */
	अणु TVEEPROM_AUDPROC_OTHER,    "CS5340"    पूर्ण,
	अणु TVEEPROM_AUDPROC_OTHER,    "CS8416"    पूर्ण,
	अणु TVEEPROM_AUDPROC_OTHER,    "CX20810"   पूर्ण,
पूर्ण;

/* This list is supplied by Hauppauge. Thanks! */
अटल स्थिर अक्षर *decoderIC[] = अणु
	/* 0-4 */
	"None", "BT815", "BT817", "BT819", "BT815A",
	/* 5-9 */
	"BT817A", "BT819A", "BT827", "BT829", "BT848",
	/* 10-14 */
	"BT848A", "BT849A", "BT829A", "BT827A", "BT878",
	/* 15-19 */
	"BT879", "BT880", "VPX3226E", "SAA7114", "SAA7115",
	/* 20-24 */
	"CX880", "CX881", "CX883", "SAA7111", "SAA7113",
	/* 25-29 */
	"CX882", "TVP5150A", "CX25840", "CX25841", "CX25842",
	/* 30-34 */
	"CX25843", "CX23418", "NEC61153", "CX23885", "CX23888",
	/* 35-39 */
	"SAA7131", "CX25837", "CX23887", "CX23885A", "CX23887A",
	/* 40-44 */
	"SAA7164", "CX23885B", "AU8522", "ADV7401", "AVF4910B",
	/* 45-49 */
	"SAA7231", "CX23102", "SAA7163", "ADV7441A", "ADV7181C",
	/* 50-53 */
	"CX25836", "TDA9955", "TDA19977", "ADV7842"
पूर्ण;

अटल पूर्णांक hasRadioTuner(पूर्णांक tunerType)
अणु
	चयन (tunerType) अणु
	हाल 18: /* PNPEnv_TUNER_FR1236_MK2 */
	हाल 23: /* PNPEnv_TUNER_FM1236 */
	हाल 38: /* PNPEnv_TUNER_FMR1236 */
	हाल 16: /* PNPEnv_TUNER_FR1216_MK2 */
	हाल 19: /* PNPEnv_TUNER_FR1246_MK2 */
	हाल 21: /* PNPEnv_TUNER_FM1216 */
	हाल 24: /* PNPEnv_TUNER_FM1246 */
	हाल 17: /* PNPEnv_TUNER_FR1216MF_MK2 */
	हाल 22: /* PNPEnv_TUNER_FM1216MF */
	हाल 20: /* PNPEnv_TUNER_FR1256_MK2 */
	हाल 25: /* PNPEnv_TUNER_FM1256 */
	हाल 33: /* PNPEnv_TUNER_4039FR5 */
	हाल 42: /* PNPEnv_TUNER_4009FR5 */
	हाल 52: /* PNPEnv_TUNER_4049FM5 */
	हाल 54: /* PNPEnv_TUNER_4049FM5_AltI2C */
	हाल 44: /* PNPEnv_TUNER_4009FN5 */
	हाल 31: /* PNPEnv_TUNER_TCPB9085P */
	हाल 30: /* PNPEnv_TUNER_TCPN9085D */
	हाल 46: /* PNPEnv_TUNER_TP18NSR01F */
	हाल 47: /* PNPEnv_TUNER_TP18PSB01D */
	हाल 49: /* PNPEnv_TUNER_TAPC_I001D */
	हाल 60: /* PNPEnv_TUNER_TAPE_S001D_MK3 */
	हाल 57: /* PNPEnv_TUNER_FM1216ME_MK3 */
	हाल 59: /* PNPEnv_TUNER_FM1216MP_MK3 */
	हाल 58: /* PNPEnv_TUNER_FM1236_MK3 */
	हाल 68: /* PNPEnv_TUNER_TAPE_H001F_MK3 */
	हाल 61: /* PNPEnv_TUNER_TAPE_M001D_MK3 */
	हाल 78: /* PNPEnv_TUNER_TDA8275C1_8290_FM */
	हाल 89: /* PNPEnv_TUNER_TCL_MFPE05_2 */
	हाल 92: /* PNPEnv_TUNER_PHILIPS_FQ1236A_MK4 */
	हाल 105:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम tveeprom_hauppauge_analog(काष्ठा tveeprom *tvee,
			       अचिन्हित अक्षर *eeprom_data)
अणु
	/* ----------------------------------------------
	** The hauppauge eeprom क्रमmat is tagged
	**
	** अगर packet[0] == 0x84, then packet[0..1] == length
	** अन्यथा length = packet[0] & 3f;
	** अगर packet[0] & f8 == f8, then EOD and packet[1] == checksum
	**
	** In our (ivtv) हाल we're पूर्णांकerested in the following:
	** tuner type:   tag [00].05 or [0a].01 (index पूर्णांकo hauppauge_tuner)
	** tuner fmts:   tag [00].04 or [0a].00 (biपंचांगask index पूर्णांकo
	**		 hauppauge_tuner_fmt)
	** radio:        tag [00].अणुlastपूर्ण or [0e].00  (biपंचांगask.  bit2=FM)
	** audio proc:   tag [02].01 or [05].00 (mask with 0x7f)
	** decoder proc: tag [09].01)

	** Fun info:
	** model:      tag [00].07-08 or [06].00-01
	** revision:   tag [00].09-0b or [06].04-06
	** serial#:    tag [01].05-07 or [04].04-06

	** # of inमाला_दो/outमाला_दो ???
	*/

	पूर्णांक i, j, len, करोne, beenhere, tag, start;

	पूर्णांक tuner1 = 0, t_क्रमmat1 = 0, audioic = -1;
	स्थिर अक्षर *t_name1 = शून्य;
	स्थिर अक्षर *t_fmt_name1[8] = अणु " none", "", "", "", "", "", "", "" पूर्ण;

	पूर्णांक tuner2 = 0, t_क्रमmat2 = 0;
	स्थिर अक्षर *t_name2 = शून्य;
	स्थिर अक्षर *t_fmt_name2[8] = अणु " none", "", "", "", "", "", "", "" पूर्ण;

	स_रखो(tvee, 0, माप(*tvee));
	tvee->tuner_type = TUNER_ABSENT;
	tvee->tuner2_type = TUNER_ABSENT;

	करोne = len = beenhere = 0;

	/* Dअगरferent eeprom start offsets क्रम em28xx, cx2388x and cx23418 */
	अगर (eeprom_data[0] == 0x1a &&
	    eeprom_data[1] == 0xeb &&
	    eeprom_data[2] == 0x67 &&
	    eeprom_data[3] == 0x95)
		start = 0xa0; /* Generic em28xx offset */
	अन्यथा अगर ((eeprom_data[0] & 0xe1) == 0x01 &&
		 eeprom_data[1] == 0x00 &&
		 eeprom_data[2] == 0x00 &&
		 eeprom_data[8] == 0x84)
		start = 8; /* Generic cx2388x offset */
	अन्यथा अगर (eeprom_data[1] == 0x70 &&
		 eeprom_data[2] == 0x00 &&
		 eeprom_data[4] == 0x74 &&
		 eeprom_data[8] == 0x84)
		start = 8; /* Generic cx23418 offset (models 74xxx) */
	अन्यथा
		start = 0;

	क्रम (i = start; !करोne && i < 256; i += len) अणु
		अगर (eeprom_data[i] == 0x84) अणु
			len = eeprom_data[i + 1] + (eeprom_data[i + 2] << 8);
			i += 3;
		पूर्ण अन्यथा अगर ((eeprom_data[i] & 0xf0) == 0x70) अणु
			अगर (eeprom_data[i] & 0x08) अणु
				/* verअगरy checksum! */
				करोne = 1;
				अवरोध;
			पूर्ण
			len = eeprom_data[i] & 0x07;
			++i;
		पूर्ण अन्यथा अणु
			pr_warn("Encountered bad packet header [%02x]. Corrupt or not a Hauppauge eeprom.\n",
				eeprom_data[i]);
			वापस;
		पूर्ण

		pr_debug("Tag [%02x] + %d bytes: %*ph\n",
			eeprom_data[i], len - 1, len, &eeprom_data[i]);

		/* process by tag */
		tag = eeprom_data[i];
		चयन (tag) अणु
		हाल 0x00:
			/* tag: 'Comprehensive' */
			tuner1 = eeprom_data[i+6];
			t_क्रमmat1 = eeprom_data[i+5];
			tvee->has_radio = eeprom_data[i+len-1];
			/* old style tag, करोn't know how to detect
			IR presence, mark as unknown. */
			tvee->has_ir = 0;
			tvee->model =
				eeprom_data[i+8] +
				(eeprom_data[i+9] << 8);
			tvee->revision = eeprom_data[i+10] +
				(eeprom_data[i+11] << 8) +
				(eeprom_data[i+12] << 16);
			अवरोध;

		हाल 0x01:
			/* tag: 'SerialID' */
			tvee->serial_number =
				eeprom_data[i+6] +
				(eeprom_data[i+7] << 8) +
				(eeprom_data[i+8] << 16);
			अवरोध;

		हाल 0x02:
			/* tag 'AudioInfo'
			Note mask with 0x7F, high bit used on some older models
			to indicate 4052 mux was हटाओd in favor of using MSP
			inमाला_दो directly. */
			audioic = eeprom_data[i+2] & 0x7f;
			अगर (audioic < ARRAY_SIZE(audio_ic))
				tvee->audio_processor = audio_ic[audioic].id;
			अन्यथा
				tvee->audio_processor = TVEEPROM_AUDPROC_OTHER;
			अवरोध;

		/* हाल 0x03: tag 'EEInfo' */

		हाल 0x04:
			/* tag 'SerialID2' */
			tvee->serial_number =
				eeprom_data[i+5] +
				(eeprom_data[i+6] << 8) +
				(eeprom_data[i+7] << 16)+
				(eeprom_data[i+8] << 24);

			अगर (eeprom_data[i + 8] == 0xf0) अणु
				tvee->MAC_address[0] = 0x00;
				tvee->MAC_address[1] = 0x0D;
				tvee->MAC_address[2] = 0xFE;
				tvee->MAC_address[3] = eeprom_data[i + 7];
				tvee->MAC_address[4] = eeprom_data[i + 6];
				tvee->MAC_address[5] = eeprom_data[i + 5];
				tvee->has_MAC_address = 1;
			पूर्ण
			अवरोध;

		हाल 0x05:
			/* tag 'Audio2'
			Note mask with 0x7F, high bit used on some older models
			to indicate 4052 mux was हटाओd in favor of using MSP
			inमाला_दो directly. */
			audioic = eeprom_data[i+1] & 0x7f;
			अगर (audioic < ARRAY_SIZE(audio_ic))
				tvee->audio_processor = audio_ic[audioic].id;
			अन्यथा
				tvee->audio_processor = TVEEPROM_AUDPROC_OTHER;

			अवरोध;

		हाल 0x06:
			/* tag 'ModelRev' */
			tvee->model =
				eeprom_data[i + 1] +
				(eeprom_data[i + 2] << 8) +
				(eeprom_data[i + 3] << 16) +
				(eeprom_data[i + 4] << 24);
			tvee->revision =
				eeprom_data[i + 5] +
				(eeprom_data[i + 6] << 8) +
				(eeprom_data[i + 7] << 16);
			अवरोध;

		हाल 0x07:
			/* tag 'Details': according to Hauppauge not पूर्णांकeresting
			on any PCI-era or later boards. */
			अवरोध;

		/* there is no tag 0x08 defined */

		हाल 0x09:
			/* tag 'Video' */
			tvee->decoder_processor = eeprom_data[i + 1];
			अवरोध;

		हाल 0x0a:
			/* tag 'Tuner' */
			अगर (beenhere == 0) अणु
				tuner1 = eeprom_data[i + 2];
				t_क्रमmat1 = eeprom_data[i + 1];
				beenhere = 1;
			पूर्ण अन्यथा अणु
				/* a second (radio) tuner may be present */
				tuner2 = eeprom_data[i + 2];
				t_क्रमmat2 = eeprom_data[i + 1];
				/* not a TV tuner? */
				अगर (t_क्रमmat2 == 0)
					tvee->has_radio = 1; /* must be radio */
			पूर्ण
			अवरोध;

		हाल 0x0b:
			/* tag 'Inputs': according to Hauppauge this is specअगरic
			to each driver family, so no good assumptions can be
			made. */
			अवरोध;

		/* हाल 0x0c: tag 'Balun' */
		/* हाल 0x0d: tag 'Teletext' */

		हाल 0x0e:
			/* tag: 'Radio' */
			tvee->has_radio = eeprom_data[i+1];
			अवरोध;

		हाल 0x0f:
			/* tag 'IRInfo' */
			tvee->has_ir = 1 | (eeprom_data[i+1] << 1);
			अवरोध;

		/* हाल 0x10: tag 'VBIInfo' */
		/* हाल 0x11: tag 'QCInfo' */
		/* हाल 0x12: tag 'InfoBits' */

		शेष:
			pr_debug("Not sure what to do with tag [%02x]\n",
					tag);
			/* dump the rest of the packet? */
		पूर्ण
	पूर्ण

	अगर (!करोne) अणु
		pr_warn("Ran out of data!\n");
		वापस;
	पूर्ण

	अगर (tvee->revision != 0) अणु
		tvee->rev_str[0] = 32 + ((tvee->revision >> 18) & 0x3f);
		tvee->rev_str[1] = 32 + ((tvee->revision >> 12) & 0x3f);
		tvee->rev_str[2] = 32 + ((tvee->revision >>  6) & 0x3f);
		tvee->rev_str[3] = 32 + (tvee->revision & 0x3f);
		tvee->rev_str[4] = 0;
	पूर्ण

	अगर (hasRadioTuner(tuner1) && !tvee->has_radio) अणु
		pr_info("The eeprom says no radio is present, but the tuner type\n");
		pr_info("indicates otherwise. I will assume that radio is present.\n");
		tvee->has_radio = 1;
	पूर्ण

	अगर (tuner1 < ARRAY_SIZE(hauppauge_tuner)) अणु
		tvee->tuner_type = hauppauge_tuner[tuner1].id;
		t_name1 = hauppauge_tuner[tuner1].name;
	पूर्ण अन्यथा अणु
		t_name1 = "unknown";
	पूर्ण

	अगर (tuner2 < ARRAY_SIZE(hauppauge_tuner)) अणु
		tvee->tuner2_type = hauppauge_tuner[tuner2].id;
		t_name2 = hauppauge_tuner[tuner2].name;
	पूर्ण अन्यथा अणु
		t_name2 = "unknown";
	पूर्ण

	tvee->tuner_hauppauge_model = tuner1;
	tvee->tuner2_hauppauge_model = tuner2;
	tvee->tuner_क्रमmats = 0;
	tvee->tuner2_क्रमmats = 0;
	क्रम (i = j = 0; i < 8; i++) अणु
		अगर (t_क्रमmat1 & (1 << i)) अणु
			tvee->tuner_क्रमmats |= hauppauge_tuner_fmt[i].id;
			t_fmt_name1[j++] = hauppauge_tuner_fmt[i].name;
		पूर्ण
	पूर्ण
	क्रम (i = j = 0; i < 8; i++) अणु
		अगर (t_क्रमmat2 & (1 << i)) अणु
			tvee->tuner2_क्रमmats |= hauppauge_tuner_fmt[i].id;
			t_fmt_name2[j++] = hauppauge_tuner_fmt[i].name;
		पूर्ण
	पूर्ण

	pr_info("Hauppauge model %d, rev %s, serial# %u\n",
		tvee->model, tvee->rev_str, tvee->serial_number);
	अगर (tvee->has_MAC_address == 1)
		pr_info("MAC address is %pM\n", tvee->MAC_address);
	pr_info("tuner model is %s (idx %d, type %d)\n",
		t_name1, tuner1, tvee->tuner_type);
	pr_info("TV standards%s%s%s%s%s%s%s%s (eeprom 0x%02x)\n",
		t_fmt_name1[0], t_fmt_name1[1], t_fmt_name1[2],
		t_fmt_name1[3],	t_fmt_name1[4], t_fmt_name1[5],
		t_fmt_name1[6], t_fmt_name1[7],	t_क्रमmat1);
	अगर (tuner2)
		pr_info("second tuner model is %s (idx %d, type %d)\n",
					t_name2, tuner2, tvee->tuner2_type);
	अगर (t_क्रमmat2)
		pr_info("TV standards%s%s%s%s%s%s%s%s (eeprom 0x%02x)\n",
			t_fmt_name2[0], t_fmt_name2[1], t_fmt_name2[2],
			t_fmt_name2[3],	t_fmt_name2[4], t_fmt_name2[5],
			t_fmt_name2[6], t_fmt_name2[7], t_क्रमmat2);
	अगर (audioic < 0) अणु
		pr_info("audio processor is unknown (no idx)\n");
		tvee->audio_processor = TVEEPROM_AUDPROC_OTHER;
	पूर्ण अन्यथा अणु
		अगर (audioic < ARRAY_SIZE(audio_ic))
			pr_info("audio processor is %s (idx %d)\n",
					audio_ic[audioic].name, audioic);
		अन्यथा
			pr_info("audio processor is unknown (idx %d)\n",
								audioic);
	पूर्ण
	अगर (tvee->decoder_processor)
		pr_info("decoder processor is %s (idx %d)\n",
			STRM(decoderIC, tvee->decoder_processor),
			tvee->decoder_processor);
	अगर (tvee->has_ir)
		pr_info("has %sradio, has %sIR receiver, has %sIR transmitter\n",
				tvee->has_radio ? "" : "no ",
				(tvee->has_ir & 2) ? "" : "no ",
				(tvee->has_ir & 4) ? "" : "no ");
	अन्यथा
		pr_info("has %sradio\n",
				tvee->has_radio ? "" : "no ");
पूर्ण
EXPORT_SYMBOL(tveeprom_hauppauge_analog);

/* ----------------------------------------------------------------------- */
/* generic helper functions                                                */

पूर्णांक tveeprom_पढ़ो(काष्ठा i2c_client *c, अचिन्हित अक्षर *eedata, पूर्णांक len)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक err;

	buf = 0;
	err = i2c_master_send(c, &buf, 1);
	अगर (err != 1) अणु
		pr_info("Huh, no eeprom present (err=%d)?\n", err);
		वापस -1;
	पूर्ण
	err = i2c_master_recv(c, eedata, len);
	अगर (err != len) अणु
		pr_warn("i2c eeprom read error (err=%d)\n", err);
		वापस -1;
	पूर्ण

	prपूर्णांक_hex_dump_debug("full 256-byte eeprom dump:", DUMP_PREFIX_NONE,
			     16, 1, eedata, len, true);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tveeprom_पढ़ो);
