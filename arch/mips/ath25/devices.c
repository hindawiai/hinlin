<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/bootinfo.h>

#समावेश <ath25_platक्रमm.h>
#समावेश "devices.h"
#समावेश "ar5312.h"
#समावेश "ar2315.h"

काष्ठा ar231x_board_config ath25_board;
क्रमागत ath25_soc_type ath25_soc = ATH25_SOC_UNKNOWN;

अटल काष्ठा resource ath25_wmac0_res[] = अणु
	अणु
		.name = "wmac0_membase",
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name = "wmac0_irq",
		.flags = IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा resource ath25_wmac1_res[] = अणु
	अणु
		.name = "wmac1_membase",
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name = "wmac1_irq",
		.flags = IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device ath25_wmac[] = अणु
	अणु
		.id = 0,
		.name = "ar231x-wmac",
		.resource = ath25_wmac0_res,
		.num_resources = ARRAY_SIZE(ath25_wmac0_res),
		.dev.platक्रमm_data = &ath25_board,
	पूर्ण,
	अणु
		.id = 1,
		.name = "ar231x-wmac",
		.resource = ath25_wmac1_res,
		.num_resources = ARRAY_SIZE(ath25_wmac1_res),
		.dev.platक्रमm_data = &ath25_board,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर soc_type_strings[] = अणु
	[ATH25_SOC_AR5312] = "Atheros AR5312",
	[ATH25_SOC_AR2312] = "Atheros AR2312",
	[ATH25_SOC_AR2313] = "Atheros AR2313",
	[ATH25_SOC_AR2315] = "Atheros AR2315",
	[ATH25_SOC_AR2316] = "Atheros AR2316",
	[ATH25_SOC_AR2317] = "Atheros AR2317",
	[ATH25_SOC_AR2318] = "Atheros AR2318",
	[ATH25_SOC_UNKNOWN] = "Atheros (unknown)",
पूर्ण;

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	अगर ((ath25_soc >= ARRAY_SIZE(soc_type_strings)) ||
	    !soc_type_strings[ath25_soc])
		वापस soc_type_strings[ATH25_SOC_UNKNOWN];
	वापस soc_type_strings[ath25_soc];
पूर्ण

व्योम __init ath25_serial_setup(u32 mapbase, पूर्णांक irq, अचिन्हित पूर्णांक uartclk)
अणु
#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
	काष्ठा uart_port s;

	स_रखो(&s, 0, माप(s));

	s.flags = UPF_BOOT_AUTOCONF | UPF_SKIP_TEST | UPF_IOREMAP;
	s.iotype = UPIO_MEM32;
	s.irq = irq;
	s.regshअगरt = 2;
	s.mapbase = mapbase;
	s.uartclk = uartclk;

	early_serial_setup(&s);
#पूर्ण_अगर /* CONFIG_SERIAL_8250_CONSOLE */
पूर्ण

पूर्णांक __init ath25_add_wmac(पूर्णांक nr, u32 base, पूर्णांक irq)
अणु
	काष्ठा resource *res;

	ath25_wmac[nr].dev.platक्रमm_data = &ath25_board;
	res = &ath25_wmac[nr].resource[0];
	res->start = base;
	res->end = base + 0x10000 - 1;
	res++;
	res->start = irq;
	res->end = irq;
	वापस platक्रमm_device_रेजिस्टर(&ath25_wmac[nr]);
पूर्ण

अटल पूर्णांक __init ath25_रेजिस्टर_devices(व्योम)
अणु
	अगर (is_ar5312())
		ar5312_init_devices();
	अन्यथा
		ar2315_init_devices();

	वापस 0;
पूर्ण

device_initcall(ath25_रेजिस्टर_devices);

अटल पूर्णांक __init ath25_arch_init(व्योम)
अणु
	अगर (is_ar5312())
		ar5312_arch_init();
	अन्यथा
		ar2315_arch_init();

	वापस 0;
पूर्ण

arch_initcall(ath25_arch_init);
