<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016 Yang Ling <gnaygnil@gmail.com>
 */

#समावेश <platक्रमm.h>

अटल काष्ठा platक्रमm_device *ls1c_platक्रमm_devices[] __initdata = अणु
	&ls1x_uart_pdev,
	&ls1x_eth0_pdev,
	&ls1x_rtc_pdev,
	&ls1x_wdt_pdev,
पूर्ण;

अटल पूर्णांक __init ls1c_platक्रमm_init(व्योम)
अणु
	ls1x_serial_set_uartclk(&ls1x_uart_pdev);
	ls1x_rtc_set_extclk(&ls1x_rtc_pdev);

	वापस platक्रमm_add_devices(ls1c_platक्रमm_devices,
				   ARRAY_SIZE(ls1c_platक्रमm_devices));
पूर्ण

arch_initcall(ls1c_platक्रमm_init);
