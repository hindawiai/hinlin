<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

/*
 * Copyright (c) 2008 MtekVision Co., Ltd.
 *	Kwangwoo Lee <kwlee@mtekvision.com>
 *
 * Using code from:
 *  - ads7846.c
 *	Copyright (c) 2005 David Brownell
 *	Copyright (c) 2006 Nokia Corporation
 *  - corgi_ts.c
 *	Copyright (C) 2004-2005 Riअक्षरd Purdie
 *  - omap_ts.[hc], ads7846.h, ts_osk.c
 *	Copyright (C) 2002 MontaVista Software
 *	Copyright (C) 2004 Texas Instruments
 *	Copyright (C) 2005 Dirk Behme
 */

#अगर_अघोषित _TSC2007_H
#घोषणा _TSC2007_H

काष्ठा gpio_desc;

#घोषणा TSC2007_MEASURE_TEMP0		(0x0 << 4)
#घोषणा TSC2007_MEASURE_AUX		(0x2 << 4)
#घोषणा TSC2007_MEASURE_TEMP1		(0x4 << 4)
#घोषणा TSC2007_ACTIVATE_XN		(0x8 << 4)
#घोषणा TSC2007_ACTIVATE_YN		(0x9 << 4)
#घोषणा TSC2007_ACTIVATE_YP_XN		(0xa << 4)
#घोषणा TSC2007_SETUP			(0xb << 4)
#घोषणा TSC2007_MEASURE_X		(0xc << 4)
#घोषणा TSC2007_MEASURE_Y		(0xd << 4)
#घोषणा TSC2007_MEASURE_Z1		(0xe << 4)
#घोषणा TSC2007_MEASURE_Z2		(0xf << 4)

#घोषणा TSC2007_POWER_OFF_IRQ_EN	(0x0 << 2)
#घोषणा TSC2007_ADC_ON_IRQ_DIS0		(0x1 << 2)
#घोषणा TSC2007_ADC_OFF_IRQ_EN		(0x2 << 2)
#घोषणा TSC2007_ADC_ON_IRQ_DIS1		(0x3 << 2)

#घोषणा TSC2007_12BIT			(0x0 << 1)
#घोषणा TSC2007_8BIT			(0x1 << 1)

#घोषणा MAX_12BIT			((1 << 12) - 1)

#घोषणा ADC_ON_12BIT	(TSC2007_12BIT | TSC2007_ADC_ON_IRQ_DIS0)

#घोषणा READ_Y		(ADC_ON_12BIT | TSC2007_MEASURE_Y)
#घोषणा READ_Z1		(ADC_ON_12BIT | TSC2007_MEASURE_Z1)
#घोषणा READ_Z2		(ADC_ON_12BIT | TSC2007_MEASURE_Z2)
#घोषणा READ_X		(ADC_ON_12BIT | TSC2007_MEASURE_X)
#घोषणा PWRDOWN		(TSC2007_12BIT | TSC2007_POWER_OFF_IRQ_EN)

काष्ठा ts_event अणु
	u16	x;
	u16	y;
	u16	z1, z2;
पूर्ण;

काष्ठा tsc2007 अणु
	काष्ठा input_dev	*input;
	अक्षर			phys[32];

	काष्ठा i2c_client	*client;

	u16			model;
	u16			x_plate_ohms;
	u16			max_rt;
	अचिन्हित दीर्घ		poll_period; /* in jअगरfies */
	पूर्णांक			fuzzx;
	पूर्णांक			fuzzy;
	पूर्णांक			fuzzz;

	काष्ठा gpio_desc	*gpiod;
	पूर्णांक			irq;

	रुको_queue_head_t	रुको;
	bool			stopped;

	पूर्णांक			(*get_penकरोwn_state)(काष्ठा device *);
	व्योम			(*clear_penirq)(व्योम);

	काष्ठा mutex		mlock;
पूर्ण;

पूर्णांक tsc2007_xfer(काष्ठा tsc2007 *tsc, u8 cmd);
u32 tsc2007_calculate_resistance(काष्ठा tsc2007 *tsc, काष्ठा ts_event *tc);
bool tsc2007_is_pen_करोwn(काष्ठा tsc2007 *ts);

#अगर IS_ENABLED(CONFIG_TOUCHSCREEN_TSC2007_IIO)
/* defined in tsc2007_iio.c */
पूर्णांक tsc2007_iio_configure(काष्ठा tsc2007 *ts);
#अन्यथा
अटल अंतरभूत पूर्णांक tsc2007_iio_configure(काष्ठा tsc2007 *ts)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TOUCHSCREEN_TSC2007_IIO */

#पूर्ण_अगर /* _TSC2007_H */
