<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2005 Russell King.
 *  Data taken from include/यंत्र-i386/serial.h
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_8250.h>

#घोषणा HUB6(card, port)						\
	अणु								\
		.iobase		= 0x302,				\
		.irq		= 3,					\
		.uartclk	= 1843200,				\
		.iotype		= UPIO_HUB6,				\
		.flags		= UPF_BOOT_AUTOCONF,			\
		.hub6		= (card) << 6 | (port) << 3 | 1,	\
	पूर्ण

अटल काष्ठा plat_serial8250_port hub6_data[] = अणु
	HUB6(0, 0),
	HUB6(0, 1),
	HUB6(0, 2),
	HUB6(0, 3),
	HUB6(0, 4),
	HUB6(0, 5),
	HUB6(1, 0),
	HUB6(1, 1),
	HUB6(1, 2),
	HUB6(1, 3),
	HUB6(1, 4),
	HUB6(1, 5),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device hub6_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_HUB6,
	.dev			= अणु
		.platक्रमm_data	= hub6_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hub6_init(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&hub6_device);
पूर्ण

module_init(hub6_init);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("8250 serial probe module for Hub6 cards");
MODULE_LICENSE("GPL");
