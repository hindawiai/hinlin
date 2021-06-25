<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Samsung's S3C64XX flattened device tree enabled machine
//
// Copyright (c) 2013 Tomasz Figa <tomasz.figa@gmail.com>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "cpu.h"
#समावेश "map.h"

#समावेश "s3c64xx.h"

/*
 * IO mapping क्रम shared प्रणाली controller IP.
 *
 * FIXME: Make reमुख्यing drivers use dynamic mapping.
 */
अटल काष्ठा map_desc s3c64xx_dt_iodesc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)S3C_VA_SYS,
		.pfn		= __phys_to_pfn(S3C64XX_PA_SYSCON),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init s3c64xx_dt_map_io(व्योम)
अणु
	debug_ll_io_init();
	iotable_init(s3c64xx_dt_iodesc, ARRAY_SIZE(s3c64xx_dt_iodesc));

	s3c64xx_init_cpu();

	अगर (!soc_is_s3c64xx())
		panic("SoC is not S3C64xx!");
पूर्ण

अटल स्थिर अक्षर *स्थिर s3c64xx_dt_compat[] __initस्थिर = अणु
	"samsung,s3c6400",
	"samsung,s3c6410",
	शून्य
पूर्ण;

DT_MACHINE_START(S3C6400_DT, "Samsung S3C64xx (Flattened Device Tree)")
	/* Maपूर्णांकainer: Tomasz Figa <tomasz.figa@gmail.com> */
	.dt_compat	= s3c64xx_dt_compat,
	.map_io		= s3c64xx_dt_map_io,
MACHINE_END
