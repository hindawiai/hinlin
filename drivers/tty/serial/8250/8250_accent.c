<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2005 Russell King.
 *  Data taken from include/यंत्र-i386/serial.h
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_8250.h>

#समावेश "8250.h"

अटल काष्ठा plat_serial8250_port accent_data[] = अणु
	SERIAL8250_PORT(0x330, 4),
	SERIAL8250_PORT(0x338, 4),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device accent_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_ACCENT,
	.dev			= अणु
		.platक्रमm_data	= accent_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init accent_init(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&accent_device);
पूर्ण

module_init(accent_init);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("8250 serial probe module for Accent Async cards");
MODULE_LICENSE("GPL");
