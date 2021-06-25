<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// S3C series CPU initialisation

/*
 * NOTE: Code in this file is not used on S3C64xx when booting with
 * Device Tree support.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "cpu.h"
#समावेश "devs.h"

अटल काष्ठा cpu_table *cpu;

अटल काष्ठा cpu_table * __init s3c_lookup_cpu(अचिन्हित दीर्घ idcode,
						काष्ठा cpu_table *tab,
						अचिन्हित पूर्णांक count)
अणु
	क्रम (; count != 0; count--, tab++) अणु
		अगर ((idcode & tab->idmask) == (tab->idcode & tab->idmask))
			वापस tab;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम __init s3c_init_cpu(अचिन्हित दीर्घ idcode,
			 काष्ठा cpu_table *cputab, अचिन्हित पूर्णांक cputab_size)
अणु
	cpu = s3c_lookup_cpu(idcode, cputab, cputab_size);

	अगर (cpu == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Unknown CPU type 0x%08lx\n", idcode);
		panic("Unknown S3C24XX CPU");
	पूर्ण

	prपूर्णांकk("CPU %s (id 0x%08lx)\n", cpu->name, idcode);

	अगर (cpu->init == शून्य) अणु
		prपूर्णांकk(KERN_ERR "CPU %s support not enabled\n", cpu->name);
		panic("Unsupported Samsung CPU");
	पूर्ण

	अगर (cpu->map_io)
		cpu->map_io();
पूर्ण

/* s3c24xx_init_घड़ीs
 *
 * Initialise the घड़ी subप्रणाली and associated inक्रमmation from the
 * given master crystal value.
 *
 * xtal  = 0 -> use शेष PLL crystal value (normally 12MHz)
 *      != 0 -> PLL crystal value in Hz
*/

व्योम __init s3c24xx_init_घड़ीs(पूर्णांक xtal)
अणु
	अगर (xtal == 0)
		xtal = 12*1000*1000;

	अगर (cpu == शून्य)
		panic("s3c24xx_init_clocks: no cpu setup?\n");

	अगर (cpu->init_घड़ीs == शून्य)
		panic("s3c24xx_init_clocks: cpu has no clock init\n");
	अन्यथा
		(cpu->init_घड़ीs)(xtal);
पूर्ण

/* uart management */
#अगर IS_ENABLED(CONFIG_SAMSUNG_ATAGS)
अटल पूर्णांक nr_uarts __initdata = 0;

#अगर_घोषित CONFIG_SERIAL_SAMSUNG_UARTS
अटल काष्ठा s3c2410_uartcfg uart_cfgs[CONFIG_SERIAL_SAMSUNG_UARTS];
#पूर्ण_अगर

/* s3c24xx_init_uartdevs
 *
 * copy the specअगरied platक्रमm data and configuration पूर्णांकo our central
 * set of devices, beक्रमe the data is thrown away after the init process.
 *
 * This also fills in the array passed to the serial driver क्रम the
 * early initialisation of the console.
*/

व्योम __init s3c24xx_init_uartdevs(अक्षर *name,
				  काष्ठा s3c24xx_uart_resources *res,
				  काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no)
अणु
#अगर_घोषित CONFIG_SERIAL_SAMSUNG_UARTS
	काष्ठा platक्रमm_device *platdev;
	काष्ठा s3c2410_uartcfg *cfgptr = uart_cfgs;
	काष्ठा s3c24xx_uart_resources *resp;
	पूर्णांक uart;

	स_नकल(cfgptr, cfg, माप(काष्ठा s3c2410_uartcfg) * no);

	क्रम (uart = 0; uart < no; uart++, cfg++, cfgptr++) अणु
		platdev = s3c24xx_uart_src[cfgptr->hwport];

		resp = res + cfgptr->hwport;

		s3c24xx_uart_devs[uart] = platdev;

		platdev->name = name;
		platdev->resource = resp->resources;
		platdev->num_resources = resp->nr_resources;

		platdev->dev.platक्रमm_data = cfgptr;
	पूर्ण

	nr_uarts = no;
#पूर्ण_अगर
पूर्ण

व्योम __init s3c24xx_init_uarts(काष्ठा s3c2410_uartcfg *cfg, पूर्णांक no)
अणु
	अगर (cpu == शून्य)
		वापस;

	अगर (cpu->init_uarts == शून्य && IS_ENABLED(CONFIG_SAMSUNG_ATAGS)) अणु
		prपूर्णांकk(KERN_ERR "s3c24xx_init_uarts: cpu has no uart init\n");
	पूर्ण अन्यथा
		(cpu->init_uarts)(cfg, no);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init s3c_arch_init(व्योम)
अणु
	पूर्णांक ret;

	/* init is only needed क्रम ATAGS based platक्रमms */
	अगर (!IS_ENABLED(CONFIG_ATAGS) ||
	    (!soc_is_s3c24xx() && !soc_is_s3c64xx()))
		वापस 0;

	// करो the correct init क्रम cpu

	अगर (cpu == शून्य) अणु
		/* Not needed when booting with device tree. */
		अगर (of_have_populated_dt())
			वापस 0;
		panic("s3c_arch_init: NULL cpu\n");
	पूर्ण

	ret = (cpu->init)();
	अगर (ret != 0)
		वापस ret;
#अगर IS_ENABLED(CONFIG_SAMSUNG_ATAGS)
	ret = platक्रमm_add_devices(s3c24xx_uart_devs, nr_uarts);
#पूर्ण_अगर
	वापस ret;
पूर्ण

arch_initcall(s3c_arch_init);
