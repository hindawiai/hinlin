<शैली गुरु>
/* linux/i2c/tps6507x-ts.h
 *
 * Functions to access TPS65070 touch screen chip.
 *
 * Copyright (c) 2009 RidgeRun (todd.fischer@ridgerun.com)
 *
 *
 *  For licencing details see kernel-base/COPYING
 */

#अगर_अघोषित __LINUX_I2C_TPS6507X_TS_H
#घोषणा __LINUX_I2C_TPS6507X_TS_H

/* Board specअगरic touch screen initial values */
काष्ठा touchscreen_init_data अणु
	पूर्णांक	poll_period;	/* ms */
	__u16	min_pressure;	/* min पढ़ोing to be treated as a touch */
	__u16	venकरोr;
	__u16	product;
	__u16	version;
पूर्ण;

#पूर्ण_अगर /*  __LINUX_I2C_TPS6507X_TS_H */
