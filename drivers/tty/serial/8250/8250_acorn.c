<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/drivers/serial/acorn.c
 *
 *  Copyright (C) 1996-2003 Russell King.
 */
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ecard.h>
#समावेश <यंत्र/माला.स>

#समावेश "8250.h"

#घोषणा MAX_PORTS	3

काष्ठा serial_card_type अणु
	अचिन्हित पूर्णांक	num_ports;
	अचिन्हित पूर्णांक	uartclk;
	अचिन्हित पूर्णांक	type;
	अचिन्हित पूर्णांक	offset[MAX_PORTS];
पूर्ण;

काष्ठा serial_card_info अणु
	अचिन्हित पूर्णांक	num_ports;
	पूर्णांक		ports[MAX_PORTS];
	व्योम __iomem *vaddr;
पूर्ण;

अटल पूर्णांक
serial_card_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा serial_card_info *info;
	काष्ठा serial_card_type *type = id->data;
	काष्ठा uart_8250_port uart;
	अचिन्हित दीर्घ bus_addr;
	अचिन्हित पूर्णांक i;

	info = kzalloc(माप(काष्ठा serial_card_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->num_ports = type->num_ports;

	bus_addr = ecard_resource_start(ec, type->type);
	info->vaddr = ecardm_iomap(ec, type->type, 0, 0);
	अगर (!info->vaddr) अणु
		kमुक्त(info);
		वापस -ENOMEM;
	पूर्ण

	ecard_set_drvdata(ec, info);

	स_रखो(&uart, 0, माप(काष्ठा uart_8250_port));
	uart.port.irq	= ec->irq;
	uart.port.flags	= UPF_BOOT_AUTOCONF | UPF_SHARE_IRQ;
	uart.port.uartclk	= type->uartclk;
	uart.port.iotype	= UPIO_MEM;
	uart.port.regshअगरt	= 2;
	uart.port.dev	= &ec->dev;

	क्रम (i = 0; i < info->num_ports; i++) अणु
		uart.port.membase = info->vaddr + type->offset[i];
		uart.port.mapbase = bus_addr + type->offset[i];

		info->ports[i] = serial8250_रेजिस्टर_8250_port(&uart);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम serial_card_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा serial_card_info *info = ecard_get_drvdata(ec);
	पूर्णांक i;

	ecard_set_drvdata(ec, शून्य);

	क्रम (i = 0; i < info->num_ports; i++)
		अगर (info->ports[i] > 0)
			serial8250_unरेजिस्टर_port(info->ports[i]);

	kमुक्त(info);
पूर्ण

अटल काष्ठा serial_card_type atomwide_type = अणु
	.num_ports	= 3,
	.uartclk	= 7372800,
	.type		= ECARD_RES_IOCSLOW,
	.offset		= अणु 0x2800, 0x2400, 0x2000 पूर्ण,
पूर्ण;

अटल काष्ठा serial_card_type serport_type = अणु
	.num_ports	= 2,
	.uartclk	= 3686400,
	.type		= ECARD_RES_IOCSLOW,
	.offset		= अणु 0x2000, 0x2020 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ecard_id serial_cids[] = अणु
	अणु MANU_ATOMWIDE,	PROD_ATOMWIDE_3PSERIAL,	&atomwide_type	पूर्ण,
	अणु MANU_SERPORT,		PROD_SERPORT_DSPORT,	&serport_type	पूर्ण,
	अणु 0xffff, 0xffff पूर्ण
पूर्ण;

अटल काष्ठा ecard_driver serial_card_driver = अणु
	.probe		= serial_card_probe,
	.हटाओ		= serial_card_हटाओ,
	.id_table	= serial_cids,
	.drv = अणु
		.name	= "8250_acorn",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init serial_card_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&serial_card_driver);
पूर्ण

अटल व्योम __निकास serial_card_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&serial_card_driver);
पूर्ण

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("Acorn 8250-compatible serial port expansion card driver");
MODULE_LICENSE("GPL");

module_init(serial_card_init);
module_निकास(serial_card_निकास);
