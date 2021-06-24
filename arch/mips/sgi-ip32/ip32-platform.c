<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007 Ralf Baechle (ralf@linux-mips.org)
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/rtc/ds1685.h>

#समावेश <यंत्र/ip32/mace.h>
#समावेश <यंत्र/ip32/ip32_पूर्णांकs.h>

बाह्य व्योम ip32_prepare_घातeroff(व्योम);

#घोषणा MACEISA_SERIAL1_OFFS   दुरत्व(काष्ठा sgi_mace, isa.serial1)
#घोषणा MACEISA_SERIAL2_OFFS   दुरत्व(काष्ठा sgi_mace, isa.serial2)

#घोषणा MACE_PORT(offset,_irq)						\
अणु									\
	.mapbase	= MACE_BASE + offset,				\
	.irq		= _irq,						\
	.uartclk	= 1843200,					\
	.iotype		= UPIO_MEM,					\
	.flags		= UPF_SKIP_TEST|UPF_IOREMAP,			\
	.regshअगरt	= 8,						\
पूर्ण

अटल काष्ठा plat_serial8250_port uart8250_data[] = अणु
	MACE_PORT(MACEISA_SERIAL1_OFFS, MACEISA_SERIAL1_IRQ),
	MACE_PORT(MACEISA_SERIAL2_OFFS, MACEISA_SERIAL2_IRQ),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device uart8250_device = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= uart8250_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init uart8250_init(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&uart8250_device);
पूर्ण

device_initcall(uart8250_init);

अटल __init पूर्णांक meth_devinit(व्योम)
अणु
	काष्ठा platक्रमm_device *pd;
	पूर्णांक ret;

	pd = platक्रमm_device_alloc("meth", -1);
	अगर (!pd)
		वापस -ENOMEM;

	ret = platक्रमm_device_add(pd);
	अगर (ret)
		platक्रमm_device_put(pd);

	वापस ret;
पूर्ण

device_initcall(meth_devinit);

अटल __init पूर्णांक sgio2audio_devinit(व्योम)
अणु
	काष्ठा platक्रमm_device *pd;
	पूर्णांक ret;

	pd = platक्रमm_device_alloc("sgio2audio", -1);
	अगर (!pd)
		वापस -ENOMEM;

	ret = platक्रमm_device_add(pd);
	अगर (ret)
		platक्रमm_device_put(pd);

	वापस ret;
पूर्ण

device_initcall(sgio2audio_devinit);

अटल __init पूर्णांक sgio2btns_devinit(व्योम)
अणु
	वापस IS_ERR(platक्रमm_device_रेजिस्टर_simple("sgibtns", -1, शून्य, 0));
पूर्ण

device_initcall(sgio2btns_devinit);

#घोषणा MACE_RTC_RES_START (MACE_BASE + दुरत्व(काष्ठा sgi_mace, isa.rtc))
#घोषणा MACE_RTC_RES_END (MACE_RTC_RES_START + 32767)

अटल काष्ठा resource ip32_rtc_resources[] = अणु
	अणु
		.start	= MACEISA_RTC_IRQ,
		.end	= MACEISA_RTC_IRQ,
		.flags	= IORESOURCE_IRQ
	पूर्ण, अणु
		.start	= MACE_RTC_RES_START,
		.end	= MACE_RTC_RES_END,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

/* RTC रेजिस्टरs on IP32 are each padded by 256 bytes (0x100). */
अटल काष्ठा ds1685_rtc_platक्रमm_data
ip32_rtc_platक्रमm_data[] = अणु
	अणु
		.regstep = 0x100,
		.bcd_mode = true,
		.no_irq = false,
		.uie_unsupported = false,
		.access_type = ds1685_reg_direct,
		.plat_prepare_घातeroff = ip32_prepare_घातeroff,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device ip32_rtc_device = अणु
	.name			= "rtc-ds1685",
	.id			= -1,
	.dev			= अणु
		.platक्रमm_data	= ip32_rtc_platक्रमm_data,
	पूर्ण,
	.num_resources		= ARRAY_SIZE(ip32_rtc_resources),
	.resource		= ip32_rtc_resources,
पूर्ण;

अटल __init पूर्णांक sgio2_rtc_devinit(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&ip32_rtc_device);
पूर्ण

device_initcall(sgio2_rtc_devinit);
