<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* linux/spi/ads7846.h */

/* Touchscreen अक्षरacteristics vary between boards and models.  The
 * platक्रमm_data क्रम the device's "struct device" holds this inक्रमmation.
 *
 * It's OK अगर the min/max values are zero.
 */
क्रमागत ads7846_filter अणु
	ADS7846_FILTER_OK,
	ADS7846_FILTER_REPEAT,
	ADS7846_FILTER_IGNORE,
पूर्ण;

काष्ठा ads7846_platक्रमm_data अणु
	u16	model;			/* 7843, 7845, 7846, 7873. */
	u16	vref_delay_usecs;	/* 0 क्रम बाह्यal vref; etc */
	u16	vref_mv;		/* बाह्यal vref value, milliVolts
					 * ads7846: अगर 0, use पूर्णांकernal vref */
	bool	keep_vref_on;		/* set to keep vref on क्रम dअगरferential
					 * measurements as well */
	bool	swap_xy;		/* swap x and y axes */

	/* Settling समय of the analog संकेतs; a function of Vcc and the
	 * capacitance on the X/Y drivers.  If set to non-zero, two samples
	 * are taken with settle_delay us apart, and the second one is used.
	 * ~150 uSec with 0.01uF caps.
	 */
	u16	settle_delay_usecs;

	/* If set to non-zero, after samples are taken this delay is applied
	 * and penirq is rechecked, to help aव्योम false events.  This value
	 * is affected by the material used to build the touch layer.
	 */
	u16	penirq_recheck_delay_usecs;

	u16	x_plate_ohms;
	u16	y_plate_ohms;

	u16	x_min, x_max;
	u16	y_min, y_max;
	u16	pressure_min, pressure_max;

	u16	debounce_max;		/* max number of additional पढ़ोings
					 * per sample */
	u16	debounce_tol;		/* tolerance used क्रम filtering */
	u16	debounce_rep;		/* additional consecutive good पढ़ोings
					 * required after the first two */
	पूर्णांक	gpio_penकरोwn;		/* the GPIO used to decide the penकरोwn
					 * state अगर get_penकरोwn_state == शून्य */
	पूर्णांक	gpio_penकरोwn_debounce;	/* platक्रमm specअगरic debounce समय क्रम
					 * the gpio_penकरोwn */
	पूर्णांक	(*get_penकरोwn_state)(व्योम);
	पूर्णांक	(*filter_init)	(स्थिर काष्ठा ads7846_platक्रमm_data *pdata,
				 व्योम **filter_data);
	पूर्णांक	(*filter)	(व्योम *filter_data, पूर्णांक data_idx, पूर्णांक *val);
	व्योम	(*filter_cleanup)(व्योम *filter_data);
	व्योम	(*रुको_क्रम_sync)(व्योम);
	bool	wakeup;
	अचिन्हित दीर्घ irq_flags;
पूर्ण;

