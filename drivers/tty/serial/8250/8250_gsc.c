<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Serial Device Initialisation क्रम Lasi/Asp/Wax/Dino
 *
 *	(c) Copyright Matthew Wilcox <willy@debian.org> 2001-2002
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/पन.स>

#समावेश "8250.h"

अटल पूर्णांक __init serial_init_chip(काष्ठा parisc_device *dev)
अणु
	काष्ठा uart_8250_port uart;
	अचिन्हित दीर्घ address;
	पूर्णांक err;

#अगर_घोषित CONFIG_64BIT
	अगर (!dev->irq && (dev->id.sversion == 0xad))
		dev->irq = iosapic_serial_irq(dev);
#पूर्ण_अगर

	अगर (!dev->irq) अणु
		/* We find some unattached serial ports by walking native
		 * busses.  These should be silently ignored.  Otherwise,
		 * what we have here is a missing parent device, so tell
		 * the user what they're missing.
		 */
		अगर (parisc_parent(dev)->id.hw_type != HPHW_IOA)
			dev_info(&dev->dev,
				"Serial: device 0x%llx not configured.\n"
				"Enable support for Wax, Lasi, Asp or Dino.\n",
				(अचिन्हित दीर्घ दीर्घ)dev->hpa.start);
		वापस -ENODEV;
	पूर्ण

	address = dev->hpa.start;
	अगर (dev->id.sversion != 0x8d)
		address += 0x800;

	स_रखो(&uart, 0, माप(uart));
	uart.port.iotype	= UPIO_MEM;
	/* 7.272727MHz on Lasi.  Assumed the same क्रम Dino, Wax and Timi. */
	uart.port.uartclk	= (dev->id.sversion != 0xad) ?
					7272727 : 1843200;
	uart.port.mapbase	= address;
	uart.port.membase	= ioremap(address, 16);
	अगर (!uart.port.membase) अणु
		dev_warn(&dev->dev, "Failed to map memory\n");
		वापस -ENOMEM;
	पूर्ण
	uart.port.irq	= dev->irq;
	uart.port.flags	= UPF_BOOT_AUTOCONF;
	uart.port.dev	= &dev->dev;

	err = serial8250_रेजिस्टर_8250_port(&uart);
	अगर (err < 0) अणु
		dev_warn(&dev->dev,
			"serial8250_register_8250_port returned error %d\n",
			err);
		iounmap(uart.port.membase);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id serial_tbl[] __initस्थिर = अणु
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00075 पूर्ण,
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x0008c पूर्ण,
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x0008d पूर्ण,
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x000ad पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/* Hack.  Some machines have SERIAL_0 attached to Lasi and SERIAL_1
 * attached to Dino.  Unक्रमtunately, Dino appears beक्रमe Lasi in the device
 * tree.  To ensure that ttyS0 == SERIAL_0, we रेजिस्टर two drivers; one
 * which only knows about Lasi and then a second which will find all the
 * other serial ports.  HPUX ignores this problem.
 */
अटल स्थिर काष्ठा parisc_device_id lasi_tbl[] __initस्थिर = अणु
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, 0x03B, 0x0008C पूर्ण, /* C1xx/C1xxL */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, 0x03C, 0x0008C पूर्ण, /* B132L */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, 0x03D, 0x0008C पूर्ण, /* B160L */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, 0x03E, 0x0008C पूर्ण, /* B132L+ */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, 0x03F, 0x0008C पूर्ण, /* B180L+ */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, 0x046, 0x0008C पूर्ण, /* Rocky2 120 */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, 0x047, 0x0008C पूर्ण, /* Rocky2 150 */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, 0x04E, 0x0008C पूर्ण, /* Kiji L2 132 */
	अणु HPHW_FIO, HVERSION_REV_ANY_ID, 0x056, 0x0008C पूर्ण, /* Raven+ */
	अणु 0 पूर्ण
पूर्ण;


MODULE_DEVICE_TABLE(parisc, serial_tbl);

अटल काष्ठा parisc_driver lasi_driver __refdata = अणु
	.name		= "serial_1",
	.id_table	= lasi_tbl,
	.probe		= serial_init_chip,
पूर्ण;

अटल काष्ठा parisc_driver serial_driver __refdata = अणु
	.name		= "serial",
	.id_table	= serial_tbl,
	.probe		= serial_init_chip,
पूर्ण;

अटल पूर्णांक __init probe_serial_gsc(व्योम)
अणु
	रेजिस्टर_parisc_driver(&lasi_driver);
	रेजिस्टर_parisc_driver(&serial_driver);
	वापस 0;
पूर्ण

module_init(probe_serial_gsc);

MODULE_LICENSE("GPL");
