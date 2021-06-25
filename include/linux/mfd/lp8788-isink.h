<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI LP8788 MFD - common definitions क्रम current sinks
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#अगर_अघोषित __ISINK_LP8788_H__
#घोषणा __ISINK_LP8788_H__

/* रेजिस्टर address */
#घोषणा LP8788_ISINK_CTRL		0x99
#घोषणा LP8788_ISINK12_IOUT		0x9A
#घोषणा LP8788_ISINK3_IOUT		0x9B
#घोषणा LP8788_ISINK1_PWM		0x9C
#घोषणा LP8788_ISINK2_PWM		0x9D
#घोषणा LP8788_ISINK3_PWM		0x9E

/* mask bits */
#घोषणा LP8788_ISINK1_IOUT_M		0x0F	/* Addr 9Ah */
#घोषणा LP8788_ISINK2_IOUT_M		0xF0
#घोषणा LP8788_ISINK3_IOUT_M		0x0F	/* Addr 9Bh */

/* 6 bits used क्रम PWM code : Addr 9C ~ 9Eh */
#घोषणा LP8788_ISINK_MAX_PWM		63
#घोषणा LP8788_ISINK_SCALE_OFFSET	3

अटल स्थिर u8 lp8788_iout_addr[] = अणु
	LP8788_ISINK12_IOUT,
	LP8788_ISINK12_IOUT,
	LP8788_ISINK3_IOUT,
पूर्ण;

अटल स्थिर u8 lp8788_iout_mask[] = अणु
	LP8788_ISINK1_IOUT_M,
	LP8788_ISINK2_IOUT_M,
	LP8788_ISINK3_IOUT_M,
पूर्ण;

अटल स्थिर u8 lp8788_pwm_addr[] = अणु
	LP8788_ISINK1_PWM,
	LP8788_ISINK2_PWM,
	LP8788_ISINK3_PWM,
पूर्ण;

#पूर्ण_अगर
