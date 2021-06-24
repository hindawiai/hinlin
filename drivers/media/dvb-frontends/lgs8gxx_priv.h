<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम Legend Silicon GB20600 (a.k.a DMB-TH) demodulator
 *    LGS8913, LGS8GL5, LGS8G75
 *    experimental support LGS8G42, LGS8G52
 *
 *    Copyright (C) 2007-2009 David T.L. Wong <davidtlwong@gmail.com>
 *    Copyright (C) 2008 Sirius International (Hong Kong) Limited
 *    Timothy Lee <timothy.lee@siriushk.com> (क्रम initial work on LGS8GL5)
 */

#अगर_अघोषित LGS8913_PRIV_H
#घोषणा LGS8913_PRIV_H

काष्ठा lgs8gxx_state अणु
	काष्ठा i2c_adapter *i2c;
	/* configuration settings */
	स्थिर काष्ठा lgs8gxx_config *config;
	काष्ठा dvb_frontend frontend;
	u16 curr_gi; /* current guard पूर्णांकerval */
पूर्ण;

#घोषणा SC_MASK		0x1C	/* Sub-Carrier Modulation Mask */
#घोषणा SC_QAM64	0x10	/* 64QAM modulation */
#घोषणा SC_QAM32	0x0C	/* 32QAM modulation */
#घोषणा SC_QAM16	0x08	/* 16QAM modulation */
#घोषणा SC_QAM4NR	0x04	/* 4QAM-NR modulation */
#घोषणा SC_QAM4		0x00	/* 4QAM modulation */

#घोषणा LGS_FEC_MASK	0x03	/* FEC Rate Mask */
#घोषणा LGS_FEC_0_4	0x00	/* FEC Rate 0.4 */
#घोषणा LGS_FEC_0_6	0x01	/* FEC Rate 0.6 */
#घोषणा LGS_FEC_0_8	0x02	/* FEC Rate 0.8 */

#घोषणा TIM_MASK	  0x20	/* Time Interleave Length Mask */
#घोषणा TIM_LONG	  0x20	/* Time Interleave Length = 720 */
#घोषणा TIM_MIDDLE     0x00   /* Time Interleave Length = 240 */

#घोषणा CF_MASK	0x80	/* Control Frame Mask */
#घोषणा CF_EN	0x80	/* Control Frame On */

#घोषणा GI_MASK	0x03	/* Guard Interval Mask */
#घोषणा GI_420	0x00	/* 1/9 Guard Interval */
#घोषणा GI_595	0x01	/* */
#घोषणा GI_945	0x02	/* 1/4 Guard Interval */


#घोषणा TS_PARALLEL	0x00	/* Parallel TS Output a.k.a. SPI */
#घोषणा TS_SERIAL	0x01	/* Serial TS Output a.k.a. SSI */
#घोषणा TS_CLK_NORMAL		0x00	/* MPEG Clock Normal */
#घोषणा TS_CLK_INVERTED		0x02	/* MPEG Clock Inverted */
#घोषणा TS_CLK_GATED		0x00	/* MPEG घड़ी gated */
#घोषणा TS_CLK_FREERUN		0x04	/* MPEG घड़ी मुक्त running*/


#पूर्ण_अगर
