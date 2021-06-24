<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * stv0900_init.h
 *
 * Driver क्रम ST STV0900 satellite demodulator IC.
 *
 * Copyright (C) ST Microelectronics.
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 */

#अगर_अघोषित STV0900_INIT_H
#घोषणा STV0900_INIT_H

#समावेश "stv0900_priv.h"

/* DVBS2 C/N Look-Up table */
अटल स्थिर काष्ठा stv0900_table stv0900_s2_cn = अणु
	55,
	अणु
		अणु -30,	13348 पूर्ण, /*C/N=-3dB*/
		अणु -20,	12640 पूर्ण, /*C/N=-2dB*/
		अणु -10,	11883 पूर्ण, /*C/N=-1dB*/
		अणु 0,	11101 पूर्ण, /*C/N=-0dB*/
		अणु 5,	10718 पूर्ण, /*C/N=0.5dB*/
		अणु 10,	10339 पूर्ण, /*C/N=1.0dB*/
		अणु 15,	9947 पूर्ण, /*C/N=1.5dB*/
		अणु 20,	9552 पूर्ण, /*C/N=2.0dB*/
		अणु 25,	9183 पूर्ण, /*C/N=2.5dB*/
		अणु 30,	8799 पूर्ण, /*C/N=3.0dB*/
		अणु 35,	8422 पूर्ण, /*C/N=3.5dB*/
		अणु 40,	8062 पूर्ण, /*C/N=4.0dB*/
		अणु 45,	7707 पूर्ण, /*C/N=4.5dB*/
		अणु 50,	7353 पूर्ण, /*C/N=5.0dB*/
		अणु 55,	7025 पूर्ण, /*C/N=5.5dB*/
		अणु 60,	6684 पूर्ण, /*C/N=6.0dB*/
		अणु 65,	6331 पूर्ण, /*C/N=6.5dB*/
		अणु 70,	6036 पूर्ण, /*C/N=7.0dB*/
		अणु 75,	5727 पूर्ण, /*C/N=7.5dB*/
		अणु 80,	5437 पूर्ण, /*C/N=8.0dB*/
		अणु 85,	5164 पूर्ण, /*C/N=8.5dB*/
		अणु 90,	4902 पूर्ण, /*C/N=9.0dB*/
		अणु 95,	4653 पूर्ण, /*C/N=9.5dB*/
		अणु 100,	4408 पूर्ण, /*C/N=10.0dB*/
		अणु 105,	4187 पूर्ण, /*C/N=10.5dB*/
		अणु 110,	3961 पूर्ण, /*C/N=11.0dB*/
		अणु 115,	3751 पूर्ण, /*C/N=11.5dB*/
		अणु 120,	3558 पूर्ण, /*C/N=12.0dB*/
		अणु 125,	3368 पूर्ण, /*C/N=12.5dB*/
		अणु 130,	3191 पूर्ण, /*C/N=13.0dB*/
		अणु 135,	3017 पूर्ण, /*C/N=13.5dB*/
		अणु 140,	2862 पूर्ण, /*C/N=14.0dB*/
		अणु 145,	2710 पूर्ण, /*C/N=14.5dB*/
		अणु 150,	2565 पूर्ण, /*C/N=15.0dB*/
		अणु 160,	2300 पूर्ण, /*C/N=16.0dB*/
		अणु 170,	2058 पूर्ण, /*C/N=17.0dB*/
		अणु 180,	1849 पूर्ण, /*C/N=18.0dB*/
		अणु 190,	1663 पूर्ण, /*C/N=19.0dB*/
		अणु 200,	1495 पूर्ण, /*C/N=20.0dB*/
		अणु 210,	1349 पूर्ण, /*C/N=21.0dB*/
		अणु 220,	1222 पूर्ण, /*C/N=22.0dB*/
		अणु 230,	1110 पूर्ण, /*C/N=23.0dB*/
		अणु 240,	1011 पूर्ण, /*C/N=24.0dB*/
		अणु 250,	925 पूर्ण, /*C/N=25.0dB*/
		अणु 260,	853 पूर्ण, /*C/N=26.0dB*/
		अणु 270,	789 पूर्ण, /*C/N=27.0dB*/
		अणु 280,	734 पूर्ण, /*C/N=28.0dB*/
		अणु 290,	690 पूर्ण, /*C/N=29.0dB*/
		अणु 300,	650 पूर्ण, /*C/N=30.0dB*/
		अणु 310,	619 पूर्ण, /*C/N=31.0dB*/
		अणु 320,	593 पूर्ण, /*C/N=32.0dB*/
		अणु 330,	571 पूर्ण, /*C/N=33.0dB*/
		अणु 400,	498 पूर्ण, /*C/N=40.0dB*/
		अणु 450,	484 पूर्ण, /*C/N=45.0dB*/
		अणु 500,	481 पूर्ण  /*C/N=50.0dB*/
	पूर्ण
पूर्ण;

/* RF level C/N Look-Up table */
अटल स्थिर काष्ठा stv0900_table stv0900_rf = अणु
	14,
	अणु
		अणु -5, 0xCAA1 पूर्ण, /*-5dBm*/
		अणु -10, 0xC229 पूर्ण, /*-10dBm*/
		अणु -15, 0xBB08 पूर्ण, /*-15dBm*/
		अणु -20, 0xB4BC पूर्ण, /*-20dBm*/
		अणु -25, 0xAD5A पूर्ण, /*-25dBm*/
		अणु -30, 0xA298 पूर्ण, /*-30dBm*/
		अणु -35, 0x98A8 पूर्ण, /*-35dBm*/
		अणु -40, 0x8389 पूर्ण, /*-40dBm*/
		अणु -45, 0x59BE पूर्ण, /*-45dBm*/
		अणु -50, 0x3A14 पूर्ण, /*-50dBm*/
		अणु -55, 0x2D11 पूर्ण, /*-55dBm*/
		अणु -60, 0x210D पूर्ण, /*-60dBm*/
		अणु -65, 0xA14F पूर्ण, /*-65dBm*/
		अणु -70, 0x7AA पूर्ण	/*-70dBm*/
	पूर्ण
पूर्ण;

काष्ठा stv0900_car_loop_optim अणु
	क्रमागत fe_stv0900_modcode modcode;
	u8 car_loop_pilots_on_2;
	u8 car_loop_pilots_off_2;
	u8 car_loop_pilots_on_5;
	u8 car_loop_pilots_off_5;
	u8 car_loop_pilots_on_10;
	u8 car_loop_pilots_off_10;
	u8 car_loop_pilots_on_20;
	u8 car_loop_pilots_off_20;
	u8 car_loop_pilots_on_30;
	u8 car_loop_pilots_off_30;

पूर्ण;

काष्ठा stv0900_लघु_frames_car_loop_optim अणु
	क्रमागत fe_stv0900_modulation modulation;
	u8 car_loop_cut12_2;    /* Cut 1.2,   SR<=3msps     */
	u8 car_loop_cut20_2;    /* Cut 2.0,   SR<3msps      */
	u8 car_loop_cut12_5;    /* Cut 1.2,   3<SR<=7msps   */
	u8 car_loop_cut20_5;    /* Cut 2.0,   3<SR<=7msps   */
	u8 car_loop_cut12_10;   /* Cut 1.2,   7<SR<=15msps  */
	u8 car_loop_cut20_10;   /* Cut 2.0,   7<SR<=15msps  */
	u8 car_loop_cut12_20;   /* Cut 1.2,   10<SR<=25msps */
	u8 car_loop_cut20_20;   /* Cut 2.0,   10<SR<=25msps */
	u8 car_loop_cut12_30;   /* Cut 1.2,   25<SR<=45msps */
	u8 car_loop_cut20_30;   /* Cut 2.0,   10<SR<=45msps */

पूर्ण;

काष्ठा stv0900_लघु_frames_car_loop_optim_vs_mod अणु
	क्रमागत fe_stv0900_modulation modulation;
	u8 car_loop_2;	  /* SR<3msps      */
	u8 car_loop_5;	  /* 3<SR<=7msps   */
	u8 car_loop_10;   /* 7<SR<=15msps  */
	u8 car_loop_20;   /* 10<SR<=25msps */
	u8 car_loop_30;   /* 10<SR<=45msps */
पूर्ण;

/* Cut 1.x Tracking carrier loop carrier QPSK 1/2 to 8PSK 9/10 दीर्घ Frame */
अटल स्थिर काष्ठा stv0900_car_loop_optim FE_STV0900_S2CarLoop[14] = अणु
	/*Modcod		2MPon	2MPoff	5MPon	5MPoff	10MPon
				10MPoff	20MPon	20MPoff	30MPon	30MPoff */
	अणु STV0900_QPSK_12,	0x1C,	0x0D,	0x1B,	0x2C,	0x3A,
				0x1C,	0x2A,	0x3B,	0x2A,	0x1B पूर्ण,
	अणु STV0900_QPSK_35,	0x2C,	0x0D,	0x2B,	0x2C,	0x3A,
				0x0C,	0x3A,	0x2B,	0x2A,	0x0B पूर्ण,
	अणु STV0900_QPSK_23,	0x2C,	0x0D,	0x2B,	0x2C,	0x0B,
				0x0C,	0x3A,	0x1B,	0x2A,	0x3A पूर्ण,
	अणु STV0900_QPSK_34,	0x3C,	0x0D,	0x3B,	0x1C,	0x0B,
				0x3B,	0x3A,	0x0B,	0x2A,	0x3A पूर्ण,
	अणु STV0900_QPSK_45,	0x3C,	0x0D,	0x3B,	0x1C,	0x0B,
				0x3B,	0x3A,	0x0B,	0x2A,	0x3A पूर्ण,
	अणु STV0900_QPSK_56,	0x0D,	0x0D,	0x3B,	0x1C,	0x0B,
				0x3B,	0x3A,	0x0B,	0x2A,	0x3A पूर्ण,
	अणु STV0900_QPSK_89,	0x0D,	0x0D,	0x3B,	0x1C,	0x1B,
				0x3B,	0x3A,	0x0B,	0x2A,	0x3A पूर्ण,
	अणु STV0900_QPSK_910,	0x1D,	0x0D,	0x3B,	0x1C,	0x1B,
				0x3B,	0x3A,	0x0B,	0x2A,	0x3A पूर्ण,
	अणु STV0900_8PSK_35,	0x29,	0x3B,	0x09,	0x2B,	0x38,
				0x0B,	0x18,	0x1A,	0x08,	0x0A पूर्ण,
	अणु STV0900_8PSK_23,	0x0A,	0x3B,	0x29,	0x2B,	0x19,
				0x0B,	0x38,	0x1A,	0x18,	0x0A पूर्ण,
	अणु STV0900_8PSK_34,	0x3A,	0x3B,	0x2A,	0x2B,	0x39,
				0x0B,	0x19,	0x1A,	0x38,	0x0A पूर्ण,
	अणु STV0900_8PSK_56,	0x1B,	0x3B,	0x0B,	0x2B,	0x1A,
				0x0B,	0x39,	0x1A,	0x19,	0x0A पूर्ण,
	अणु STV0900_8PSK_89,	0x3B,	0x3B,	0x0B,	0x2B,	0x2A,
				0x0B,	0x39,	0x1A,	0x29,	0x39 पूर्ण,
	अणु STV0900_8PSK_910,	0x3B,	0x3B,	0x0B,	0x2B,	0x2A,
				0x0B,	0x39,	0x1A,	0x29,	0x39 पूर्ण
पूर्ण;


/* Cut 2.0 Tracking carrier loop carrier QPSK 1/2 to 8PSK 9/10 दीर्घ Frame */
अटल स्थिर काष्ठा stv0900_car_loop_optim FE_STV0900_S2CarLoopCut20[14] = अणु
	/* Modcod		2MPon	2MPoff	5MPon	5MPoff	10MPon
				10MPoff	20MPon	20MPoff	30MPon	30MPoff */
	अणु STV0900_QPSK_12,	0x1F,	0x3F,	0x1E,	0x3F,	0x3D,
				0x1F,	0x3D,	0x3E,	0x3D,	0x1E पूर्ण,
	अणु STV0900_QPSK_35,	0x2F,	0x3F,	0x2E,	0x2F,	0x3D,
				0x0F,	0x0E,	0x2E,	0x3D,	0x0E पूर्ण,
	अणु STV0900_QPSK_23,	0x2F,	0x3F,	0x2E,	0x2F,	0x0E,
				0x0F,	0x0E,	0x1E,	0x3D,	0x3D पूर्ण,
	अणु STV0900_QPSK_34,	0x3F,	0x3F,	0x3E,	0x1F,	0x0E,
				0x3E,	0x0E,	0x1E,	0x3D,	0x3D पूर्ण,
	अणु STV0900_QPSK_45,	0x3F,	0x3F,	0x3E,	0x1F,	0x0E,
				0x3E,	0x0E,	0x1E,	0x3D,	0x3D पूर्ण,
	अणु STV0900_QPSK_56,	0x3F,	0x3F,	0x3E,	0x1F,	0x0E,
				0x3E,	0x0E,	0x1E,	0x3D,	0x3D पूर्ण,
	अणु STV0900_QPSK_89,	0x3F,	0x3F,	0x3E,	0x1F,	0x1E,
				0x3E,	0x0E,	0x1E,	0x3D,	0x3D पूर्ण,
	अणु STV0900_QPSK_910,	0x3F,	0x3F,	0x3E,	0x1F,	0x1E,
				0x3E,	0x0E,	0x1E,	0x3D,	0x3D पूर्ण,
	अणु STV0900_8PSK_35,	0x3c,	0x0c,	0x1c,	0x3b,	0x0c,
				0x3b,	0x2b,	0x2b,	0x1b,	0x2b पूर्ण,
	अणु STV0900_8PSK_23,	0x1d,	0x0c,	0x3c,	0x0c,	0x2c,
				0x3b,	0x0c,	0x2b,	0x2b,	0x2b पूर्ण,
	अणु STV0900_8PSK_34,	0x0e,	0x1c,	0x3d,	0x0c,	0x0d,
				0x3b,	0x2c,	0x3b,	0x0c,	0x2b पूर्ण,
	अणु STV0900_8PSK_56,	0x2e,	0x3e,	0x1e,	0x2e,	0x2d,
				0x1e,	0x3c,	0x2d,	0x2c,	0x1d पूर्ण,
	अणु STV0900_8PSK_89,	0x3e,	0x3e,	0x1e,	0x2e,	0x3d,
				0x1e,	0x0d,	0x2d,	0x3c,	0x1d पूर्ण,
	अणु STV0900_8PSK_910,	0x3e,	0x3e,	0x1e,	0x2e,	0x3d,
				0x1e,	0x1d,	0x2d,	0x0d,	0x1d पूर्ण,
पूर्ण;



/* Cut 2.0 Tracking carrier loop carrier 16APSK 2/3 to 32APSK 9/10 दीर्घ Frame */
अटल स्थिर काष्ठा stv0900_car_loop_optim FE_STV0900_S2APSKCarLoopCut20[11] = अणु
	/* Modcod		2MPon	2MPoff	5MPon	5MPoff	10MPon
				10MPoff	20MPon	20MPoff	30MPon	30MPoff */
	अणु STV0900_16APSK_23,	0x0C,	0x0C,	0x0C,	0x0C,	0x1D,
				0x0C,	0x3C,	0x0C,	0x2C,	0x0C पूर्ण,
	अणु STV0900_16APSK_34,	0x0C,	0x0C,	0x0C,	0x0C,	0x0E,
				0x0C,	0x2D,	0x0C,	0x1D,	0x0C पूर्ण,
	अणु STV0900_16APSK_45,	0x0C,	0x0C,	0x0C,	0x0C,	0x1E,
				0x0C,	0x3D,	0x0C,	0x2D,	0x0C पूर्ण,
	अणु STV0900_16APSK_56,	0x0C,	0x0C,	0x0C,	0x0C,	0x1E,
				0x0C,	0x3D,	0x0C,	0x2D,	0x0C पूर्ण,
	अणु STV0900_16APSK_89,	0x0C,	0x0C,	0x0C,	0x0C,	0x2E,
				0x0C,	0x0E,	0x0C,	0x3D,	0x0C पूर्ण,
	अणु STV0900_16APSK_910,	0x0C,	0x0C,	0x0C,	0x0C,	0x2E,
				0x0C,	0x0E,	0x0C,	0x3D,	0x0C पूर्ण,
	अणु STV0900_32APSK_34,	0x0C,	0x0C,	0x0C,	0x0C,	0x0C,
				0x0C,	0x0C,	0x0C,	0x0C,	0x0C पूर्ण,
	अणु STV0900_32APSK_45,	0x0C,	0x0C,	0x0C,	0x0C,	0x0C,
				0x0C,	0x0C,	0x0C,	0x0C,	0x0C पूर्ण,
	अणु STV0900_32APSK_56,	0x0C,	0x0C,	0x0C,	0x0C,	0x0C,
				0x0C,	0x0C,	0x0C,	0x0C,	0x0C पूर्ण,
	अणु STV0900_32APSK_89,	0x0C,	0x0C,	0x0C,	0x0C,	0x0C,
				0x0C,	0x0C,	0x0C,	0x0C,	0x0C पूर्ण,
	अणु STV0900_32APSK_910,	0x0C,	0x0C,	0x0C,	0x0C,	0x0C,
				0x0C,	0x0C,	0x0C,	0x0C,	0x0C पूर्ण,
पूर्ण;


/* Cut 2.0 Tracking carrier loop carrier QPSK 1/4 to QPSK 2/5 दीर्घ Frame */
अटल स्थिर काष्ठा stv0900_car_loop_optim FE_STV0900_S2LowQPCarLoopCut20[3] = अणु
	/* Modcod		2MPon	2MPoff	5MPon	5MPoff	10MPon
				10MPoff	20MPon	20MPoff	30MPon	30MPoff */
	अणु STV0900_QPSK_14,	0x0F,	0x3F,	0x0E,	0x3F,	0x2D,
				0x2F,	0x2D,	0x1F,	0x3D,	0x3E पूर्ण,
	अणु STV0900_QPSK_13,	0x0F,	0x3F,	0x0E,	0x3F,	0x2D,
				0x2F,	0x3D,	0x0F,	0x3D,	0x2E पूर्ण,
	अणु STV0900_QPSK_25,	0x1F,	0x3F,	0x1E,	0x3F,	0x3D,
				0x1F,	0x3D,	0x3E,	0x3D,	0x2E पूर्ण
पूर्ण;


/* Cut 2.0 Tracking carrier loop carrier  लघु Frame, cut 1.2 and 2.0 */
अटल स्थिर
काष्ठा stv0900_लघु_frames_car_loop_optim FE_STV0900_S2ShortCarLoop[4] = अणु
	/*Mod		2Mcut1.2 2Mcut2.0 5Mcut1.2 5Mcut2.0 10Mcut1.2
			10Mcut2.0 20Mcut1.2 20M_cut2.0 30Mcut1.2 30Mcut2.0*/
	अणु STV0900_QPSK,		0x3C,	0x2F,	0x2B,	0x2E,	0x0B,
				0x0E,	0x3A,	0x0E,	0x2A,	0x3D पूर्ण,
	अणु STV0900_8PSK,		0x0B,	0x3E,	0x2A,	0x0E,	0x0A,
				0x2D,	0x19,	0x0D,	0x09,	0x3C पूर्ण,
	अणु STV0900_16APSK,	0x1B,	0x1E,	0x1B,	0x1E,	0x1B,
				0x1E,	0x3A,	0x3D,	0x2A,	0x2D पूर्ण,
	अणु STV0900_32APSK,	0x1B,	0x1E,	0x1B,	0x1E,	0x1B,
				0x1E,	0x3A,	0x3D,	0x2A,	0x2D पूर्ण
पूर्ण;

अटल	स्थिर काष्ठा stv0900_car_loop_optim FE_STV0900_S2CarLoopCut30[14] = अणु
	/*Modcod		2MPon	2MPoff	5MPon	5MPoff	10MPon
				10MPoff	20MPon	20MPoff	30MPon	30MPoff	*/
	अणु STV0900_QPSK_12,	0x3C,	0x2C,	0x0C,	0x2C,	0x1B,
				0x2C,	0x1B,	0x1C,	0x0B,	0x3B पूर्ण,
	अणु STV0900_QPSK_35,	0x0D,	0x0D,	0x0C,	0x0D,	0x1B,
				0x3C,	0x1B,	0x1C,	0x0B,	0x3B पूर्ण,
	अणु STV0900_QPSK_23,	0x1D,	0x0D,	0x0C,	0x1D,	0x2B,
				0x3C,	0x1B,	0x1C,	0x0B,	0x3B पूर्ण,
	अणु STV0900_QPSK_34,	0x1D,	0x1D,	0x0C,	0x1D,	0x2B,
				0x3C,	0x1B,	0x1C,	0x0B,	0x3B पूर्ण,
	अणु STV0900_QPSK_45,	0x2D,	0x1D,	0x1C,	0x1D,	0x2B,
				0x3C,	0x2B,	0x0C,	0x1B,	0x3B पूर्ण,
	अणु STV0900_QPSK_56,	0x2D,	0x1D,	0x1C,	0x1D,	0x2B,
				0x3C,	0x2B,	0x0C,	0x1B,	0x3B पूर्ण,
	अणु STV0900_QPSK_89,	0x3D,	0x2D,	0x1C,	0x1D,	0x3B,
				0x3C,	0x2B,	0x0C,	0x1B,	0x3B पूर्ण,
	अणु STV0900_QPSK_910,	0x3D,	0x2D,	0x1C,	0x1D,	0x3B,
				0x3C,	0x2B,	0x0C,	0x1B,	0x3B पूर्ण,
	अणु STV0900_8PSK_35,	0x39,	0x19,	0x39,	0x19,	0x19,
				0x19,	0x19,	0x19,	0x09,	0x19 पूर्ण,
	अणु STV0900_8PSK_23,	0x2A,	0x39,	0x1A,	0x0A,	0x39,
				0x0A,	0x29,	0x39,	0x29,	0x0A पूर्ण,
	अणु STV0900_8PSK_34,	0x0B,	0x3A,	0x0B,	0x0B,	0x3A,
				0x1B,	0x1A,	0x0B,	0x1A,	0x3A पूर्ण,
	अणु STV0900_8PSK_56,	0x0C,	0x1B,	0x3B,	0x2B,	0x1B,
				0x3B,	0x3A,	0x3B,	0x3A,	0x1B पूर्ण,
	अणु STV0900_8PSK_89,	0x2C,	0x2C,	0x2C,	0x1C,	0x2B,
				0x0C,	0x0B,	0x3B,	0x0B,	0x1B पूर्ण,
	अणु STV0900_8PSK_910,	0x2C,	0x3C,	0x2C,	0x1C,	0x3B,
				0x1C,	0x0B,	0x3B,	0x0B,	0x1B पूर्ण
पूर्ण;

अटल	स्थिर
काष्ठा stv0900_car_loop_optim FE_STV0900_S2APSKCarLoopCut30[11] = अणु
	/*Modcod		2MPon	2MPoff	5MPon	5MPoff	10MPon
				10MPoff	20MPon	20MPoff	30MPon	30MPoff	*/
	अणु STV0900_16APSK_23,	0x0A,	0x0A,	0x0A,	0x0A,	0x1A,
				0x0A,	0x3A,	0x0A,	0x2A,	0x0A पूर्ण,
	अणु STV0900_16APSK_34,	0x0A,	0x0A,	0x0A,	0x0A,	0x0B,
				0x0A,	0x3B,	0x0A,	0x1B,	0x0A पूर्ण,
	अणु STV0900_16APSK_45,	0x0A,	0x0A,	0x0A,	0x0A,	0x1B,
				0x0A,	0x3B,	0x0A,	0x2B,	0x0A पूर्ण,
	अणु STV0900_16APSK_56,	0x0A,	0x0A,	0x0A,	0x0A,	0x1B,
				0x0A,	0x3B,	0x0A,	0x2B,	0x0A पूर्ण,
	अणु STV0900_16APSK_89,	0x0A,	0x0A,	0x0A,	0x0A,	0x2B,
				0x0A,	0x0C,	0x0A,	0x3B,	0x0A पूर्ण,
	अणु STV0900_16APSK_910,	0x0A,	0x0A,	0x0A,	0x0A,	0x2B,
				0x0A,	0x0C,	0x0A,	0x3B,	0x0A पूर्ण,
	अणु STV0900_32APSK_34,	0x0A,	0x0A,	0x0A,	0x0A,	0x0A,
				0x0A,	0x0A,	0x0A,	0x0A,	0x0A पूर्ण,
	अणु STV0900_32APSK_45,	0x0A,	0x0A,	0x0A,	0x0A,	0x0A,
				0x0A,	0x0A,	0x0A,	0x0A,	0x0A पूर्ण,
	अणु STV0900_32APSK_56,	0x0A,	0x0A,	0x0A,	0x0A,	0x0A,
				0x0A,	0x0A,	0x0A,	0x0A,	0x0A पूर्ण,
	अणु STV0900_32APSK_89,	0x0A,	0x0A,	0x0A,	0x0A,	0x0A,
				0x0A,	0x0A,	0x0A,	0x0A,	0x0A पूर्ण,
	अणु STV0900_32APSK_910,	0x0A,	0x0A,	0x0A,	0x0A,	0x0A,
				0x0A,	0x0A,	0x0A,	0x0A,	0x0A पूर्ण
पूर्ण;

अटल	स्थिर
काष्ठा stv0900_car_loop_optim FE_STV0900_S2LowQPCarLoopCut30[3] = अणु
	/*Modcod		2MPon	2MPoff	5MPon	5MPoff	10MPon
				10MPoff	20MPon	20MPoff	30MPon	30MPoff*/
	अणु STV0900_QPSK_14,	0x0C,	0x3C,	0x0B,	0x3C,	0x2A,
				0x2C,	0x2A,	0x1C,	0x3A,	0x3B पूर्ण,
	अणु STV0900_QPSK_13,	0x0C,	0x3C,	0x0B,	0x3C,	0x2A,
				0x2C,	0x3A,	0x0C,	0x3A,	0x2B पूर्ण,
	अणु STV0900_QPSK_25,	0x1C,	0x3C,	0x1B,	0x3C,	0x3A,
				0x1C,	0x3A,	0x3B,	0x3A,	0x2B पूर्ण
पूर्ण;

अटल	स्थिर काष्ठा stv0900_लघु_frames_car_loop_optim_vs_mod
FE_STV0900_S2ShortCarLoopCut30[4] = अणु
	/*Mod		2Mcut3.0 5Mcut3.0 10Mcut3.0 20Mcut3.0 30Mcut3.0*/
	अणु STV0900_QPSK,		0x2C,	0x2B,	0x0B,	0x0B,	0x3A पूर्ण,
	अणु STV0900_8PSK,		0x3B,	0x0B,	0x2A,	0x0A,	0x39 पूर्ण,
	अणु STV0900_16APSK,	0x1B,	0x1B,	0x1B,	0x3A,	0x2A पूर्ण,
	अणु STV0900_32APSK,	0x1B,	0x1B,	0x1B,	0x3A,	0x2A पूर्ण,

पूर्ण;

अटल स्थिर u16 STV0900_InitVal[181][2] = अणु
	अणु R0900_OUTCFG		, 0x00	पूर्ण,
	अणु R0900_AGCRF1CFG	, 0x11	पूर्ण,
	अणु R0900_AGCRF2CFG	, 0x13	पूर्ण,
	अणु R0900_TSGENERAL1X	, 0x14	पूर्ण,
	अणु R0900_TSTTNR2		, 0x21	पूर्ण,
	अणु R0900_TSTTNR4		, 0x21	पूर्ण,
	अणु R0900_P2_DISTXCTL	, 0x22	पूर्ण,
	अणु R0900_P2_F22TX	, 0xc0	पूर्ण,
	अणु R0900_P2_F22RX	, 0xc0	पूर्ण,
	अणु R0900_P2_DISRXCTL	, 0x00	पूर्ण,
	अणु R0900_P2_TNRSTEPS	, 0x87	पूर्ण,
	अणु R0900_P2_TNRGAIN	, 0x09	पूर्ण,
	अणु R0900_P2_DMDCFGMD	, 0xF9	पूर्ण,
	अणु R0900_P2_DEMOD	, 0x08	पूर्ण,
	अणु R0900_P2_DMDCFG3	, 0xc4	पूर्ण,
	अणु R0900_P2_CARFREQ	, 0xed	पूर्ण,
	अणु R0900_P2_TNRCFG2	, 0x02	पूर्ण,
	अणु R0900_P2_TNRCFG3	, 0x02	पूर्ण,
	अणु R0900_P2_LDT		, 0xd0	पूर्ण,
	अणु R0900_P2_LDT2		, 0xb8	पूर्ण,
	अणु R0900_P2_TMGCFG	, 0xd2	पूर्ण,
	अणु R0900_P2_TMGTHRISE	, 0x20	पूर्ण,
	अणु R0900_P2_TMGTHFALL	, 0x00	पूर्ण,
	अणु R0900_P2_FECSPY	, 0x88	पूर्ण,
	अणु R0900_P2_FSPYDATA	, 0x3a	पूर्ण,
	अणु R0900_P2_FBERCPT4	, 0x00	पूर्ण,
	अणु R0900_P2_FSPYBER	, 0x10	पूर्ण,
	अणु R0900_P2_ERRCTRL1	, 0x35	पूर्ण,
	अणु R0900_P2_ERRCTRL2	, 0xc1	पूर्ण,
	अणु R0900_P2_CFRICFG	, 0xf8	पूर्ण,
	अणु R0900_P2_NOSCFG	, 0x1c	पूर्ण,
	अणु R0900_P2_DMDT0M	, 0x20	पूर्ण,
	अणु R0900_P2_CORRELMANT	, 0x70	पूर्ण,
	अणु R0900_P2_CORRELABS	, 0x88	पूर्ण,
	अणु R0900_P2_AGC2O	, 0x5b	पूर्ण,
	अणु R0900_P2_AGC2REF	, 0x38	पूर्ण,
	अणु R0900_P2_CARCFG	, 0xe4	पूर्ण,
	अणु R0900_P2_ACLC		, 0x1A	पूर्ण,
	अणु R0900_P2_BCLC		, 0x09	पूर्ण,
	अणु R0900_P2_CARHDR	, 0x08	पूर्ण,
	अणु R0900_P2_KREFTMG	, 0xc1	पूर्ण,
	अणु R0900_P2_SFRUPRATIO	, 0xf0	पूर्ण,
	अणु R0900_P2_SFRLOWRATIO	, 0x70	पूर्ण,
	अणु R0900_P2_SFRSTEP	, 0x58	पूर्ण,
	अणु R0900_P2_TMGCFG2	, 0x01	पूर्ण,
	अणु R0900_P2_CAR2CFG	, 0x26	पूर्ण,
	अणु R0900_P2_BCLC2S2Q	, 0x86	पूर्ण,
	अणु R0900_P2_BCLC2S28	, 0x86	पूर्ण,
	अणु R0900_P2_SMAPCOEF7	, 0x77	पूर्ण,
	अणु R0900_P2_SMAPCOEF6	, 0x85	पूर्ण,
	अणु R0900_P2_SMAPCOEF5	, 0x77	पूर्ण,
	अणु R0900_P2_TSCFGL	, 0x20	पूर्ण,
	अणु R0900_P2_DMDCFG2	, 0x3b	पूर्ण,
	अणु R0900_P2_MODCODLST0	, 0xff	पूर्ण,
	अणु R0900_P2_MODCODLST1	, 0xff	पूर्ण,
	अणु R0900_P2_MODCODLST2	, 0xff	पूर्ण,
	अणु R0900_P2_MODCODLST3	, 0xff	पूर्ण,
	अणु R0900_P2_MODCODLST4	, 0xff	पूर्ण,
	अणु R0900_P2_MODCODLST5	, 0xff	पूर्ण,
	अणु R0900_P2_MODCODLST6	, 0xff	पूर्ण,
	अणु R0900_P2_MODCODLST7	, 0xcc	पूर्ण,
	अणु R0900_P2_MODCODLST8	, 0xcc	पूर्ण,
	अणु R0900_P2_MODCODLST9	, 0xcc	पूर्ण,
	अणु R0900_P2_MODCODLSTA	, 0xcc	पूर्ण,
	अणु R0900_P2_MODCODLSTB	, 0xcc	पूर्ण,
	अणु R0900_P2_MODCODLSTC	, 0xcc	पूर्ण,
	अणु R0900_P2_MODCODLSTD	, 0xcc	पूर्ण,
	अणु R0900_P2_MODCODLSTE	, 0xcc	पूर्ण,
	अणु R0900_P2_MODCODLSTF	, 0xcf	पूर्ण,
	अणु R0900_P1_DISTXCTL	, 0x22	पूर्ण,
	अणु R0900_P1_F22TX	, 0xc0	पूर्ण,
	अणु R0900_P1_F22RX	, 0xc0	पूर्ण,
	अणु R0900_P1_DISRXCTL	, 0x00	पूर्ण,
	अणु R0900_P1_TNRSTEPS	, 0x87	पूर्ण,
	अणु R0900_P1_TNRGAIN	, 0x09	पूर्ण,
	अणु R0900_P1_DMDCFGMD	, 0xf9	पूर्ण,
	अणु R0900_P1_DEMOD	, 0x08	पूर्ण,
	अणु R0900_P1_DMDCFG3	, 0xc4	पूर्ण,
	अणु R0900_P1_DMDT0M	, 0x20	पूर्ण,
	अणु R0900_P1_CARFREQ	, 0xed	पूर्ण,
	अणु R0900_P1_TNRCFG2	, 0x82	पूर्ण,
	अणु R0900_P1_TNRCFG3	, 0x02	पूर्ण,
	अणु R0900_P1_LDT		, 0xd0	पूर्ण,
	अणु R0900_P1_LDT2		, 0xb8	पूर्ण,
	अणु R0900_P1_TMGCFG	, 0xd2	पूर्ण,
	अणु R0900_P1_TMGTHRISE	, 0x20	पूर्ण,
	अणु R0900_P1_TMGTHFALL	, 0x00	पूर्ण,
	अणु R0900_P1_SFRUPRATIO	, 0xf0	पूर्ण,
	अणु R0900_P1_SFRLOWRATIO	, 0x70	पूर्ण,
	अणु R0900_P1_TSCFGL	, 0x20	पूर्ण,
	अणु R0900_P1_FECSPY	, 0x88	पूर्ण,
	अणु R0900_P1_FSPYDATA	, 0x3a	पूर्ण,
	अणु R0900_P1_FBERCPT4	, 0x00	पूर्ण,
	अणु R0900_P1_FSPYBER	, 0x10	पूर्ण,
	अणु R0900_P1_ERRCTRL1	, 0x35	पूर्ण,
	अणु R0900_P1_ERRCTRL2	, 0xc1	पूर्ण,
	अणु R0900_P1_CFRICFG	, 0xf8	पूर्ण,
	अणु R0900_P1_NOSCFG	, 0x1c	पूर्ण,
	अणु R0900_P1_CORRELMANT	, 0x70	पूर्ण,
	अणु R0900_P1_CORRELABS	, 0x88	पूर्ण,
	अणु R0900_P1_AGC2O	, 0x5b	पूर्ण,
	अणु R0900_P1_AGC2REF	, 0x38	पूर्ण,
	अणु R0900_P1_CARCFG	, 0xe4	पूर्ण,
	अणु R0900_P1_ACLC		, 0x1A	पूर्ण,
	अणु R0900_P1_BCLC		, 0x09	पूर्ण,
	अणु R0900_P1_CARHDR	, 0x08	पूर्ण,
	अणु R0900_P1_KREFTMG	, 0xc1	पूर्ण,
	अणु R0900_P1_SFRSTEP	, 0x58	पूर्ण,
	अणु R0900_P1_TMGCFG2	, 0x01	पूर्ण,
	अणु R0900_P1_CAR2CFG	, 0x26	पूर्ण,
	अणु R0900_P1_BCLC2S2Q	, 0x86	पूर्ण,
	अणु R0900_P1_BCLC2S28	, 0x86	पूर्ण,
	अणु R0900_P1_SMAPCOEF7	, 0x77	पूर्ण,
	अणु R0900_P1_SMAPCOEF6	, 0x85	पूर्ण,
	अणु R0900_P1_SMAPCOEF5	, 0x77	पूर्ण,
	अणु R0900_P1_DMDCFG2	, 0x3b	पूर्ण,
	अणु R0900_P1_MODCODLST0	, 0xff	पूर्ण,
	अणु R0900_P1_MODCODLST1	, 0xff	पूर्ण,
	अणु R0900_P1_MODCODLST2	, 0xff	पूर्ण,
	अणु R0900_P1_MODCODLST3	, 0xff	पूर्ण,
	अणु R0900_P1_MODCODLST4	, 0xff	पूर्ण,
	अणु R0900_P1_MODCODLST5	, 0xff	पूर्ण,
	अणु R0900_P1_MODCODLST6	, 0xff	पूर्ण,
	अणु R0900_P1_MODCODLST7	, 0xcc	पूर्ण,
	अणु R0900_P1_MODCODLST8	, 0xcc	पूर्ण,
	अणु R0900_P1_MODCODLST9	, 0xcc	पूर्ण,
	अणु R0900_P1_MODCODLSTA	, 0xcc	पूर्ण,
	अणु R0900_P1_MODCODLSTB	, 0xcc	पूर्ण,
	अणु R0900_P1_MODCODLSTC	, 0xcc	पूर्ण,
	अणु R0900_P1_MODCODLSTD	, 0xcc	पूर्ण,
	अणु R0900_P1_MODCODLSTE	, 0xcc	पूर्ण,
	अणु R0900_P1_MODCODLSTF	, 0xcf	पूर्ण,
	अणु R0900_GENCFG		, 0x1d	पूर्ण,
	अणु R0900_NBITER_NF4	, 0x37	पूर्ण,
	अणु R0900_NBITER_NF5	, 0x29	पूर्ण,
	अणु R0900_NBITER_NF6	, 0x37	पूर्ण,
	अणु R0900_NBITER_NF7	, 0x33	पूर्ण,
	अणु R0900_NBITER_NF8	, 0x31	पूर्ण,
	अणु R0900_NBITER_NF9	, 0x2f	पूर्ण,
	अणु R0900_NBITER_NF10	, 0x39	पूर्ण,
	अणु R0900_NBITER_NF11	, 0x3a	पूर्ण,
	अणु R0900_NBITER_NF12	, 0x29	पूर्ण,
	अणु R0900_NBITER_NF13	, 0x37	पूर्ण,
	अणु R0900_NBITER_NF14	, 0x33	पूर्ण,
	अणु R0900_NBITER_NF15	, 0x2f	पूर्ण,
	अणु R0900_NBITER_NF16	, 0x39	पूर्ण,
	अणु R0900_NBITER_NF17	, 0x3a	पूर्ण,
	अणु R0900_NBITERNOERR	, 0x04	पूर्ण,
	अणु R0900_GAINLLR_NF4	, 0x0C	पूर्ण,
	अणु R0900_GAINLLR_NF5	, 0x0F	पूर्ण,
	अणु R0900_GAINLLR_NF6	, 0x11	पूर्ण,
	अणु R0900_GAINLLR_NF7	, 0x14	पूर्ण,
	अणु R0900_GAINLLR_NF8	, 0x17	पूर्ण,
	अणु R0900_GAINLLR_NF9	, 0x19	पूर्ण,
	अणु R0900_GAINLLR_NF10	, 0x20	पूर्ण,
	अणु R0900_GAINLLR_NF11	, 0x21	पूर्ण,
	अणु R0900_GAINLLR_NF12	, 0x0D	पूर्ण,
	अणु R0900_GAINLLR_NF13	, 0x0F	पूर्ण,
	अणु R0900_GAINLLR_NF14	, 0x13	पूर्ण,
	अणु R0900_GAINLLR_NF15	, 0x1A	पूर्ण,
	अणु R0900_GAINLLR_NF16	, 0x1F	पूर्ण,
	अणु R0900_GAINLLR_NF17	, 0x21	पूर्ण,
	अणु R0900_RCCFG2		, 0x20	पूर्ण,
	अणु R0900_P1_FECM		, 0x01	पूर्ण, /*disable DSS modes*/
	अणु R0900_P2_FECM		, 0x01	पूर्ण, /*disable DSS modes*/
	अणु R0900_P1_PRVIT	, 0x2F	पूर्ण, /*disable puncture rate 6/7*/
	अणु R0900_P2_PRVIT	, 0x2F	पूर्ण, /*disable puncture rate 6/7*/
	अणु R0900_STROUT1CFG	, 0x4c	पूर्ण,
	अणु R0900_STROUT2CFG	, 0x4c	पूर्ण,
	अणु R0900_CLKOUT1CFG	, 0x50	पूर्ण,
	अणु R0900_CLKOUT2CFG	, 0x50	पूर्ण,
	अणु R0900_DPN1CFG		, 0x4a	पूर्ण,
	अणु R0900_DPN2CFG		, 0x4a	पूर्ण,
	अणु R0900_DATA71CFG	, 0x52	पूर्ण,
	अणु R0900_DATA72CFG	, 0x52	पूर्ण,
	अणु R0900_P1_TSCFGM	, 0xc0	पूर्ण,
	अणु R0900_P2_TSCFGM	, 0xc0	पूर्ण,
	अणु R0900_P1_TSCFGH	, 0xe0	पूर्ण, /* DVB-CI timings */
	अणु R0900_P2_TSCFGH	, 0xe0	पूर्ण, /* DVB-CI timings */
	अणु R0900_P1_TSSPEED	, 0x40	पूर्ण,
	अणु R0900_P2_TSSPEED	, 0x40	पूर्ण,
पूर्ण;

अटल स्थिर u16 STV0900_Cut20_AddOnVal[32][2] = अणु
	अणु R0900_P2_DMDCFG3	, 0xe8	पूर्ण,
	अणु R0900_P2_DMDCFG4	, 0x10	पूर्ण,
	अणु R0900_P2_CARFREQ	, 0x38	पूर्ण,
	अणु R0900_P2_CARHDR	, 0x20	पूर्ण,
	अणु R0900_P2_KREFTMG	, 0x5a	पूर्ण,
	अणु R0900_P2_SMAPCOEF7	, 0x06	पूर्ण,
	अणु R0900_P2_SMAPCOEF6	, 0x00	पूर्ण,
	अणु R0900_P2_SMAPCOEF5	, 0x04	पूर्ण,
	अणु R0900_P2_NOSCFG	, 0x0c	पूर्ण,
	अणु R0900_P1_DMDCFG3	, 0xe8	पूर्ण,
	अणु R0900_P1_DMDCFG4	, 0x10	पूर्ण,
	अणु R0900_P1_CARFREQ	, 0x38	पूर्ण,
	अणु R0900_P1_CARHDR	, 0x20	पूर्ण,
	अणु R0900_P1_KREFTMG	, 0x5a	पूर्ण,
	अणु R0900_P1_SMAPCOEF7	, 0x06	पूर्ण,
	अणु R0900_P1_SMAPCOEF6	, 0x00	पूर्ण,
	अणु R0900_P1_SMAPCOEF5	, 0x04	पूर्ण,
	अणु R0900_P1_NOSCFG	, 0x0c	पूर्ण,
	अणु R0900_GAINLLR_NF4	, 0x21	पूर्ण,
	अणु R0900_GAINLLR_NF5	, 0x21	पूर्ण,
	अणु R0900_GAINLLR_NF6	, 0x20	पूर्ण,
	अणु R0900_GAINLLR_NF7	, 0x1F	पूर्ण,
	अणु R0900_GAINLLR_NF8	, 0x1E	पूर्ण,
	अणु R0900_GAINLLR_NF9	, 0x1E	पूर्ण,
	अणु R0900_GAINLLR_NF10	, 0x1D	पूर्ण,
	अणु R0900_GAINLLR_NF11	, 0x1B	पूर्ण,
	अणु R0900_GAINLLR_NF12	, 0x20	पूर्ण,
	अणु R0900_GAINLLR_NF13	, 0x20	पूर्ण,
	अणु R0900_GAINLLR_NF14	, 0x20	पूर्ण,
	अणु R0900_GAINLLR_NF15	, 0x20	पूर्ण,
	अणु R0900_GAINLLR_NF16	, 0x20	पूर्ण,
	अणु R0900_GAINLLR_NF17	, 0x21	पूर्ण

पूर्ण;

#पूर्ण_अगर
