<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/xtensa/platक्रमms/xt2000/setup.c
 *
 * Platक्रमm specअगरic functions क्रम the XT2000 board.
 *
 * Authors:	Chris Zankel <chris@zankel.net>
 *		Joe Taylor <joe@tensilica.com>
 *
 * Copyright 2001 - 2004 Tensilica Inc.
 */
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/types.h>
#समावेश <linux/major.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/platक्रमm.h>
#समावेश <यंत्र/bootparam.h>
#समावेश <platक्रमm/hardware.h>
#समावेश <platक्रमm/serial.h>

/* Assumes s poपूर्णांकs to an 8-chr string.  No checking क्रम शून्य. */

अटल व्योम led_prपूर्णांक (पूर्णांक f, अक्षर *s)
अणु
	अचिन्हित दीर्घ* led_addr = (अचिन्हित दीर्घ*) (XT2000_LED_ADDR + 0xE0) + f;
	पूर्णांक i;
	क्रम (i = f; i < 8; i++)
		अगर ((*led_addr++ = *s++) == 0)
		    अवरोध;
पूर्ण

व्योम platक्रमm_halt(व्योम)
अणु
	led_prपूर्णांक (0, "  HALT  ");
	local_irq_disable();
	जबतक (1);
पूर्ण

व्योम platक्रमm_घातer_off(व्योम)
अणु
	led_prपूर्णांक (0, "POWEROFF");
	local_irq_disable();
	जबतक (1);
पूर्ण

व्योम platक्रमm_restart(व्योम)
अणु
	/* Flush and reset the mmu, simulate a processor reset, and
	 * jump to the reset vector. */
	cpu_reset();
	/* control never माला_लो here */
पूर्ण

व्योम __init platक्रमm_setup(अक्षर** cmdline)
अणु
	led_prपूर्णांक (0, "LINUX   ");
पूर्ण

/* early initialization */

व्योम __init platक्रमm_init(bp_tag_t *first)
अणु
पूर्ण

/* Heartbeat. Let the LED blink. */

व्योम platक्रमm_heartbeat(व्योम)
अणु
	अटल पूर्णांक i=0, t = 0;

	अगर (--t < 0)
	अणु
		t = 59;
		led_prपूर्णांक(7, i ? ".": " ");
		i ^= 1;
	पूर्ण
पूर्ण

//#घोषणा RS_TABLE_SIZE 2

#घोषणा _SERIAL_PORT(_base,_irq)					\
अणु									\
	.mapbase	= (_base),					\
	.membase	= (व्योम*)(_base),				\
	.irq		= (_irq),					\
	.uartclk	= DUART16552_XTAL_FREQ,				\
	.iotype		= UPIO_MEM,					\
	.flags		= UPF_BOOT_AUTOCONF,				\
	.regshअगरt	= 2,						\
पूर्ण

अटल काष्ठा plat_serial8250_port xt2000_serial_data[] = अणु
#अगर XCHAL_HAVE_BE
	_SERIAL_PORT(DUART16552_1_ADDR + 3, DUART16552_1_INTNUM),
	_SERIAL_PORT(DUART16552_2_ADDR + 3, DUART16552_2_INTNUM),
#अन्यथा
	_SERIAL_PORT(DUART16552_1_ADDR, DUART16552_1_INTNUM),
	_SERIAL_PORT(DUART16552_2_ADDR, DUART16552_2_INTNUM),
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device xt2000_serial8250_device = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev		= अणु
	    .platक्रमm_data = xt2000_serial_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource xt2000_sonic_res[] = अणु
	अणु
		.start = SONIC83934_ADDR,
		.end   = SONIC83934_ADDR + 0xff,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = SONIC83934_INTNUM,
		.end = SONIC83934_INTNUM,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device xt2000_sonic_device = अणु
	.name		= "xtsonic",
	.num_resources	= ARRAY_SIZE(xt2000_sonic_res),
	.resource		= xt2000_sonic_res,
पूर्ण;

अटल पूर्णांक __init xt2000_setup_devinit(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&xt2000_serial8250_device);
	platक्रमm_device_रेजिस्टर(&xt2000_sonic_device);

	वापस 0;
पूर्ण

device_initcall(xt2000_setup_devinit);
