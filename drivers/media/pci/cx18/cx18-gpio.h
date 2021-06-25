<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 gpio functions
 *
 *  Derived from ivtv-gpपन.स
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

व्योम cx18_gpio_init(काष्ठा cx18 *cx);
पूर्णांक cx18_gpio_रेजिस्टर(काष्ठा cx18 *cx, u32 hw);

क्रमागत cx18_gpio_reset_type अणु
	CX18_GPIO_RESET_I2C     = 0,
	CX18_GPIO_RESET_Z8F0811 = 1,
	CX18_GPIO_RESET_XC2028  = 2,
पूर्ण;

व्योम cx18_reset_ir_gpio(व्योम *data);
पूर्णांक cx18_reset_tuner_gpio(व्योम *dev, पूर्णांक component, पूर्णांक cmd, पूर्णांक value);
