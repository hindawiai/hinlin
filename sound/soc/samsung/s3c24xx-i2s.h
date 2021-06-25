<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * s3c24xx-i2s.c  --  ALSA Soc Audio Layer
 *
 * Copyright 2005 Wolfson Microelectronics PLC.
 * Author: Graeme Gregory
 *         graeme.gregory@wolfsonmicro.com or linux@wolfsonmicro.com
 *
 *  Revision history
 *    10th Nov 2006   Initial version.
 */

#अगर_अघोषित S3C24XXI2S_H_
#घोषणा S3C24XXI2S_H_

/* घड़ी sources */
#घोषणा S3C24XX_CLKSRC_PCLK 0
#घोषणा S3C24XX_CLKSRC_MPLL 1

/* Clock भागiders */
#घोषणा S3C24XX_DIV_MCLK	0
#घोषणा S3C24XX_DIV_BCLK	1
#घोषणा S3C24XX_DIV_PRESCALER	2

/* prescaler */
#घोषणा S3C24XX_PRESCALE(a,b) \
	(((a - 1) << S3C2410_IISPSR_INTSHIFT) | ((b - 1) << S3C2410_IISPSR_EXTSHFIT))

u32 s3c24xx_i2s_get_घड़ीrate(व्योम);

#पूर्ण_अगर /*S3C24XXI2S_H_*/
