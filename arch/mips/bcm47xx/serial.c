<शैली गुरु>
/*
 * 8250 UART probe driver क्रम the BCM47XX platक्रमms
 * Author: Aurelien Jarno
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007 Aurelien Jarno <aurelien@aurel32.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/ssb/ssb.h>
#समावेश <bcm47xx.h>

अटल काष्ठा plat_serial8250_port uart8250_data[5];

अटल काष्ठा platक्रमm_device uart8250_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= uart8250_data,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_BCM47XX_SSB
अटल पूर्णांक __init uart8250_init_ssb(व्योम)
अणु
	पूर्णांक i;
	काष्ठा ssb_mipscore *mcore = &(bcm47xx_bus.ssb.mipscore);

	स_रखो(&uart8250_data, 0,  माप(uart8250_data));

	क्रम (i = 0; i < mcore->nr_serial_ports &&
		    i < ARRAY_SIZE(uart8250_data) - 1; i++) अणु
		काष्ठा plat_serial8250_port *p = &(uart8250_data[i]);
		काष्ठा ssb_serial_port *ssb_port = &(mcore->serial_ports[i]);

		p->mapbase = (अचिन्हित पूर्णांक)ssb_port->regs;
		p->membase = (व्योम *)ssb_port->regs;
		p->irq = ssb_port->irq + 2;
		p->uartclk = ssb_port->baud_base;
		p->regshअगरt = ssb_port->reg_shअगरt;
		p->iotype = UPIO_MEM;
		p->flags = UPF_BOOT_AUTOCONF | UPF_SHARE_IRQ;
	पूर्ण
	वापस platक्रमm_device_रेजिस्टर(&uart8250_device);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCM47XX_BCMA
अटल पूर्णांक __init uart8250_init_bcma(व्योम)
अणु
	पूर्णांक i;
	काष्ठा bcma_drv_cc *cc = &(bcm47xx_bus.bcma.bus.drv_cc);

	स_रखो(&uart8250_data, 0,  माप(uart8250_data));

	क्रम (i = 0; i < cc->nr_serial_ports &&
		    i < ARRAY_SIZE(uart8250_data) - 1; i++) अणु
		काष्ठा plat_serial8250_port *p = &(uart8250_data[i]);
		काष्ठा bcma_serial_port *bcma_port;
		bcma_port = &(cc->serial_ports[i]);

		p->mapbase = (अचिन्हित पूर्णांक)bcma_port->regs;
		p->membase = (व्योम *)bcma_port->regs;
		p->irq = bcma_port->irq;
		p->uartclk = bcma_port->baud_base;
		p->regshअगरt = bcma_port->reg_shअगरt;
		p->iotype = UPIO_MEM;
		p->flags = UPF_BOOT_AUTOCONF | UPF_SHARE_IRQ;
	पूर्ण
	वापस platक्रमm_device_रेजिस्टर(&uart8250_device);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init uart8250_init(व्योम)
अणु
	चयन (bcm47xx_bus_type) अणु
#अगर_घोषित CONFIG_BCM47XX_SSB
	हाल BCM47XX_BUS_TYPE_SSB:
		वापस uart8250_init_ssb();
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCM47XX_BCMA
	हाल BCM47XX_BUS_TYPE_BCMA:
		वापस uart8250_init_bcma();
#पूर्ण_अगर
	पूर्ण
	वापस -EINVAL;
पूर्ण
device_initcall(uart8250_init);
