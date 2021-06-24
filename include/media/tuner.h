<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * tuner.h - definition क्रम dअगरferent tuners
 *
 * Copyright (C) 1997 Markus Schroeder (schroedm@uni-duesselकरोrf.de)
 * minor modअगरications by Ralph Metzler (rjkm@thp.uni-koeln.de)
 */

#अगर_अघोषित _TUNER_H
#घोषणा _TUNER_H
#अगर_घोषित __KERNEL__

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-mc.h>

#घोषणा ADDR_UNSET (255)

#घोषणा TUNER_TEMIC_PAL			0        /* 4002 FH5 (3X 7756, 9483) */
#घोषणा TUNER_PHILIPS_PAL_I		1
#घोषणा TUNER_PHILIPS_NTSC		2
#घोषणा TUNER_PHILIPS_SECAM		3	/* you must actively select B/G, L, L` */

#घोषणा TUNER_ABSENT			4
#घोषणा TUNER_PHILIPS_PAL		5
#घोषणा TUNER_TEMIC_NTSC		6	/* 4032 FY5 (3X 7004, 9498, 9789)  */
#घोषणा TUNER_TEMIC_PAL_I		7	/* 4062 FY5 (3X 8501, 9957) */

#घोषणा TUNER_TEMIC_4036FY5_NTSC	8	/* 4036 FY5 (3X 1223, 1981, 7686) */
#घोषणा TUNER_ALPS_TSBH1_NTSC		9
#घोषणा TUNER_ALPS_TSBE1_PAL		10
#घोषणा TUNER_ALPS_TSBB5_PAL_I		11

#घोषणा TUNER_ALPS_TSBE5_PAL		12
#घोषणा TUNER_ALPS_TSBC5_PAL		13
#घोषणा TUNER_TEMIC_4006FH5_PAL		14	/* 4006 FH5 (3X 9500, 9501, 7291) */
#घोषणा TUNER_ALPS_TSHC6_NTSC		15

#घोषणा TUNER_TEMIC_PAL_DK		16	/* 4016 FY5 (3X 1392, 1393) */
#घोषणा TUNER_PHILIPS_NTSC_M		17
#घोषणा TUNER_TEMIC_4066FY5_PAL_I	18	/* 4066 FY5 (3X 7032, 7035) */
#घोषणा TUNER_TEMIC_4006FN5_MULTI_PAL	19	/* B/G, I and D/K स्वतःdetected (3X 7595, 7606, 7657) */

#घोषणा TUNER_TEMIC_4009FR5_PAL		20	/* incl. FM radio (3X 7607, 7488, 7711) */
#घोषणा TUNER_TEMIC_4039FR5_NTSC	21	/* incl. FM radio (3X 7246, 7578, 7732) */
#घोषणा TUNER_TEMIC_4046FM5		22	/* you must actively select B/G, D/K, I, L, L` !  (3X 7804, 7806, 8103, 8104) */
#घोषणा TUNER_PHILIPS_PAL_DK		23

#घोषणा TUNER_PHILIPS_FQ1216ME		24	/* you must actively select B/G/D/K, I, L, L` */
#घोषणा TUNER_LG_PAL_I_FM		25
#घोषणा TUNER_LG_PAL_I			26
#घोषणा TUNER_LG_NTSC_FM		27

#घोषणा TUNER_LG_PAL_FM			28
#घोषणा TUNER_LG_PAL			29
#घोषणा TUNER_TEMIC_4009FN5_MULTI_PAL_FM 30	/* B/G, I and D/K स्वतःdetected (3X 8155, 8160, 8163) */
#घोषणा TUNER_SHARP_2U5JF5540_NTSC	31

#घोषणा TUNER_Samsung_PAL_TCPM9091PD27	32
#घोषणा TUNER_MT2032			33
#घोषणा TUNER_TEMIC_4106FH5		34	/* 4106 FH5 (3X 7808, 7865) */
#घोषणा TUNER_TEMIC_4012FY5		35	/* 4012 FY5 (3X 0971, 1099) */

#घोषणा TUNER_TEMIC_4136FY5		36	/* 4136 FY5 (3X 7708, 7746) */
#घोषणा TUNER_LG_PAL_NEW_TAPC		37
#घोषणा TUNER_PHILIPS_FM1216ME_MK3	38
#घोषणा TUNER_LG_NTSC_NEW_TAPC		39

#घोषणा TUNER_HITACHI_NTSC		40
#घोषणा TUNER_PHILIPS_PAL_MK		41
#घोषणा TUNER_PHILIPS_FCV1236D		42
#घोषणा TUNER_PHILIPS_FM1236_MK3	43

#घोषणा TUNER_PHILIPS_4IN1		44	/* ATI TV Wonder Pro - Conexant */
	/*
	 * Microtune merged with Temic 12/31/1999 partially financed by Alps.
	 * these may be similar to Temic
	 */
#घोषणा TUNER_MICROTUNE_4049FM5		45
#घोषणा TUNER_PANASONIC_VP27		46
#घोषणा TUNER_LG_NTSC_TAPE		47

#घोषणा TUNER_TNF_8831BGFF		48
#घोषणा TUNER_MICROTUNE_4042FI5		49	/* DViCO FusionHDTV 3 Gold-Q - 4042 FI5 (3X 8147) */
#घोषणा TUNER_TCL_2002N			50
#घोषणा TUNER_PHILIPS_FM1256_IH3	51

#घोषणा TUNER_THOMSON_DTT7610		52
#घोषणा TUNER_PHILIPS_FQ1286		53
#घोषणा TUNER_PHILIPS_TDA8290		54
#घोषणा TUNER_TCL_2002MB		55	/* Hauppauge PVR-150 PAL */

#घोषणा TUNER_PHILIPS_FQ1216AME_MK4	56	/* Hauppauge PVR-150 PAL */
#घोषणा TUNER_PHILIPS_FQ1236A_MK4	57	/* Hauppauge PVR-500MCE NTSC */
#घोषणा TUNER_YMEC_TVF_8531MF		58
#घोषणा TUNER_YMEC_TVF_5533MF		59	/* Pixelview Pro Ultra NTSC */

#घोषणा TUNER_THOMSON_DTT761X		60	/* DTT 7611 7611A 7612 7613 7613A 7614 7615 7615A */
#घोषणा TUNER_TENA_9533_DI		61
#घोषणा TUNER_TEA5767			62	/* Only FM Radio Tuner */
#घोषणा TUNER_PHILIPS_FMD1216ME_MK3	63

#घोषणा TUNER_LG_TDVS_H06XF		64	/* TDVS H061F, H062F, H064F */
#घोषणा TUNER_YMEC_TVF66T5_B_DFF	65	/* Acorp Y878F */
#घोषणा TUNER_LG_TALN			66
#घोषणा TUNER_PHILIPS_TD1316		67

#घोषणा TUNER_PHILIPS_TUV1236D		68	/* ATI HDTV Wonder */
#घोषणा TUNER_TNF_5335MF                69	/* Sabrent Bt848   */
#घोषणा TUNER_SAMSUNG_TCPN_2121P30A     70	/* Hauppauge PVR-500MCE NTSC */
#घोषणा TUNER_XC2028			71

#घोषणा TUNER_THOMSON_FE6600		72	/* DViCO FusionHDTV DVB-T Hybrid */
#घोषणा TUNER_SAMSUNG_TCPG_6121P30A     73	/* Hauppauge PVR-500 PAL */
#घोषणा TUNER_TDA9887                   74      /* This tuner should be used only पूर्णांकernally */
#घोषणा TUNER_TEA5761			75	/* Only FM Radio Tuner */
#घोषणा TUNER_XC5000			76	/* Xceive Silicon Tuner */
#घोषणा TUNER_TCL_MF02GIP_5N		77	/* TCL MF02GIP_5N */
#घोषणा TUNER_PHILIPS_FMD1216MEX_MK3	78
#घोषणा TUNER_PHILIPS_FM1216MK5		79
#घोषणा TUNER_PHILIPS_FQ1216LME_MK3	80	/* Active loopthrough, no FM */

#घोषणा TUNER_PARTSNIC_PTI_5NF05	81
#घोषणा TUNER_PHILIPS_CU1216L           82
#घोषणा TUNER_NXP_TDA18271		83
#घोषणा TUNER_SONY_BTF_PXN01Z		84
#घोषणा TUNER_PHILIPS_FQ1236_MK5	85	/* NTSC, TDA9885, no FM radio */
#घोषणा TUNER_TENA_TNF_5337		86

#घोषणा TUNER_XC4000			87	/* Xceive Silicon Tuner */
#घोषणा TUNER_XC5000C			88	/* Xceive Silicon Tuner */

#घोषणा TUNER_SONY_BTF_PG472Z		89	/* PAL+SECAM */
#घोषणा TUNER_SONY_BTF_PK467Z		90	/* NTSC_JP */
#घोषणा TUNER_SONY_BTF_PB463Z		91	/* NTSC */

/* tv card specअगरic */
#घोषणा TDA9887_PRESENT			(1<<0)
#घोषणा TDA9887_PORT1_INACTIVE		(1<<1)
#घोषणा TDA9887_PORT2_INACTIVE		(1<<2)
#घोषणा TDA9887_QSS			(1<<3)
#घोषणा TDA9887_INTERCARRIER		(1<<4)
#घोषणा TDA9887_PORT1_ACTIVE		(1<<5)
#घोषणा TDA9887_PORT2_ACTIVE		(1<<6)
#घोषणा TDA9887_INTERCARRIER_NTSC	(1<<7)
/* Tuner takeover poपूर्णांक adjusपंचांगent, in dB, -16 <= top <= 15 */
#घोषणा TDA9887_TOP_MASK		(0x3f << 8)
#घोषणा TDA9887_TOP_SET			(1 << 13)
#घोषणा TDA9887_TOP(top)		(TDA9887_TOP_SET | \
					 (((16 + (top)) & 0x1f) << 8))

/* config options */
#घोषणा TDA9887_DEEMPHASIS_MASK		(3<<16)
#घोषणा TDA9887_DEEMPHASIS_NONE		(1<<16)
#घोषणा TDA9887_DEEMPHASIS_50		(2<<16)
#घोषणा TDA9887_DEEMPHASIS_75		(3<<16)
#घोषणा TDA9887_AUTOMUTE		(1<<18)
#घोषणा TDA9887_GATING_18		(1<<19)
#घोषणा TDA9887_GAIN_NORMAL		(1<<20)
#घोषणा TDA9887_RIF_41_3		(1<<21)  /* radio IF1 41.3 vs 33.3 */

/**
 * क्रमागत tuner_mode      - Mode of the tuner
 *
 * @T_RADIO:        Tuner core will work in radio mode
 * @T_ANALOG_TV:    Tuner core will work in analog TV mode
 *
 * Older boards only had a single tuner device, but some devices have a
 * separate tuner क्रम radio. In any हाल, the tuner-core needs to know अगर
 * the tuner chip(s) will be used in radio mode or analog TV mode, as, on
 * radio mode, frequencies are specअगरied on a dअगरferent range than on TV
 * mode. This क्रमागत is used by the tuner core in order to work with the
 * proper tuner range and eventually use a dअगरferent tuner chip जबतक in
 * radio mode.
 */
क्रमागत tuner_mode अणु
	T_RADIO		= 1 << V4L2_TUNER_RADIO,
	T_ANALOG_TV     = 1 << V4L2_TUNER_ANALOG_TV,
	/* Don't map V4L2_TUNER_DIGITAL_TV, as tuner-core won't use it */
पूर्ण;

/**
 * काष्ठा tuner_setup   - setup the tuner chipsets
 *
 * @addr:		I2C address used to control the tuner device/chipset
 * @type:		Type of the tuner, as defined at the TUNER_* macros.
 *			Each dअगरferent tuner model should have an unique
 *			identअगरier.
 * @mode_mask:		Mask with the allowed tuner modes: V4L2_TUNER_RADIO,
 *			V4L2_TUNER_ANALOG_TV and/or V4L2_TUNER_DIGITAL_TV,
 *			describing अगर the tuner should be used to support
 *			Radio, analog TV and/or digital TV.
 * @config:		Used to send tuner-specअगरic configuration क्रम complex
 *			tuners that require extra parameters to be set.
 *			Only a very few tuners require it and its usage on
 *			newer tuners should be aव्योमed.
 * @tuner_callback:	Some tuners require to call back the bridge driver,
 *			in order to करो some tasks like rising a GPIO at the
 *			bridge chipset, in order to करो things like resetting
 *			the device.
 *
 * Older boards only had a single tuner device. Nowadays multiple tuner
 * devices may be present on a single board. Using TUNER_SET_TYPE_ADDR
 * to pass the tuner_setup काष्ठाure it is possible to setup each tuner
 * device in turn.
 *
 * Since multiple devices may be present it is no दीर्घer sufficient to
 * send a command to a single i2c device. Instead you should broadcast
 * the command to all i2c devices.
 *
 * By setting the mode_mask correctly you can select which commands are
 * accepted by a specअगरic tuner device. For example, set mode_mask to
 * T_RADIO अगर the device is a radio-only tuner. That specअगरic tuner will
 * only accept commands when the tuner is in radio mode and ignore them
 * when the tuner is set to TV mode.
 */

काष्ठा tuner_setup अणु
	अचिन्हित लघु	addr;
	अचिन्हित पूर्णांक	type;
	अचिन्हित पूर्णांक	mode_mask;
	व्योम		*config;
	पूर्णांक (*tuner_callback)(व्योम *dev, पूर्णांक component, पूर्णांक cmd, पूर्णांक arg);
पूर्ण;

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _TUNER_H */
