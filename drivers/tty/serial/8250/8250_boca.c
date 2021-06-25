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

अटल काष्ठा plat_serial8250_port boca_data[] = अणु
	SERIAL8250_PORT(0x100, 12),
	SERIAL8250_PORT(0x108, 12),
	SERIAL8250_PORT(0x110, 12),
	SERIAL8250_PORT(0x118, 12),
	SERIAL8250_PORT(0x120, 12),
	SERIAL8250_PORT(0x128, 12),
	SERIAL8250_PORT(0x130, 12),
	SERIAL8250_PORT(0x138, 12),
	SERIAL8250_PORT(0x140, 12),
	SERIAL8250_PORT(0x148, 12),
	SERIAL8250_PORT(0x150, 12),
	SERIAL8250_PORT(0x158, 12),
	SERIAL8250_PORT(0x160, 12),
	SERIAL8250_PORT(0x168, 12),
	SERIAL8250_PORT(0x170, 12),
	SERIAL8250_PORT(0x178, 12),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device boca_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_BOCA,
	.dev			= अणु
		.platक्रमm_data	= boca_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init boca_init(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&boca_device);
पूर्ण

module_init(boca_init);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("8250 serial probe module for Boca cards");
MODULE_LICENSE("GPL");
