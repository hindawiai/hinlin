<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* linux/spi/ad7877.h */

/* Touchscreen अक्षरacteristics vary between boards and models.  The
 * platक्रमm_data क्रम the device's "struct device" holds this inक्रमmation.
 *
 * It's OK अगर the min/max values are zero.
 */
काष्ठा ad7877_platक्रमm_data अणु
	u16	model;			/* 7877 */
	u16	vref_delay_usecs;	/* 0 क्रम बाह्यal vref; etc */
	u16	x_plate_ohms;
	u16	y_plate_ohms;

	u16	x_min, x_max;
	u16	y_min, y_max;
	u16	pressure_min, pressure_max;

	u8	stopacq_polarity;	/* 1 = Active HIGH, 0 = Active LOW */
	u8	first_conversion_delay;	/* 0 = 0.5us, 1 = 128us, 2 = 1ms, 3 = 8ms */
	u8	acquisition_समय;	/* 0 = 2us, 1 = 4us, 2 = 8us, 3 = 16us */
	u8	averaging;		/* 0 = 1, 1 = 4, 2 = 8, 3 = 16 */
	u8	pen_करोwn_acc_पूर्णांकerval;	/* 0 = covert once, 1 = every 0.5 ms,
					   2 = ever 1 ms,   3 = every 8 ms,*/
पूर्ण;
