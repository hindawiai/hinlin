<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Written by Paul B Schroeder < pschroeder "at" uplogix "dot" com >
 *  Based on 8250_boca.
 *
 *  Copyright (C) 2005 Russell King.
 *  Data taken from include/यंत्र-i386/serial.h
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_8250.h>

#समावेश "8250.h"

अटल काष्ठा plat_serial8250_port exar_data[] = अणु
	SERIAL8250_PORT(0x100, 5),
	SERIAL8250_PORT(0x108, 5),
	SERIAL8250_PORT(0x110, 5),
	SERIAL8250_PORT(0x118, 5),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device exar_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_EXAR_ST16C554,
	.dev			= अणु
		.platक्रमm_data	= exar_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init exar_init(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&exar_device);
पूर्ण

module_init(exar_init);

MODULE_AUTHOR("Paul B Schroeder");
MODULE_DESCRIPTION("8250 serial probe module for Exar cards");
MODULE_LICENSE("GPL");
