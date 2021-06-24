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

#घोषणा SERIAL8250_FOURPORT(_base, _irq) \
	SERIAL8250_PORT_FLAGS(_base, _irq, UPF_FOURPORT)

अटल काष्ठा plat_serial8250_port fourport_data[] = अणु
	SERIAL8250_FOURPORT(0x1a0, 9),
	SERIAL8250_FOURPORT(0x1a8, 9),
	SERIAL8250_FOURPORT(0x1b0, 9),
	SERIAL8250_FOURPORT(0x1b8, 9),
	SERIAL8250_FOURPORT(0x2a0, 5),
	SERIAL8250_FOURPORT(0x2a8, 5),
	SERIAL8250_FOURPORT(0x2b0, 5),
	SERIAL8250_FOURPORT(0x2b8, 5),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device fourport_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_FOURPORT,
	.dev			= अणु
		.platक्रमm_data	= fourport_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init fourport_init(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&fourport_device);
पूर्ण

module_init(fourport_init);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("8250 serial probe module for AST Fourport cards");
MODULE_LICENSE("GPL");
