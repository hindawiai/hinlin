<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2006-2007 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//	Vincent Sanders <vince@arm.linux.org.uk>
//
// S3C2440/S3C2442 CPU PLL tables (12MHz Crystal)

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>

#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>
#समावेश <linux/soc/samsung/s3c-pm.h>

/* This array should be sorted in ascending order of the frequencies */
अटल काष्ठा cpufreq_frequency_table s3c2440_plls_12[] = अणु
	अणु .frequency = 75000000,	.driver_data = PLLVAL(0x75, 3, 3),  पूर्ण, 	/* FVco 600.000000 */
	अणु .frequency = 80000000,	.driver_data = PLLVAL(0x98, 4, 3),  पूर्ण, 	/* FVco 640.000000 */
	अणु .frequency = 90000000,	.driver_data = PLLVAL(0x70, 2, 3),  पूर्ण, 	/* FVco 720.000000 */
	अणु .frequency = 100000000,	.driver_data = PLLVAL(0x5c, 1, 3),  पूर्ण, 	/* FVco 800.000000 */
	अणु .frequency = 110000000,	.driver_data = PLLVAL(0x66, 1, 3),  पूर्ण, 	/* FVco 880.000000 */
	अणु .frequency = 120000000,	.driver_data = PLLVAL(0x70, 1, 3),  पूर्ण, 	/* FVco 960.000000 */
	अणु .frequency = 150000000,	.driver_data = PLLVAL(0x75, 3, 2),  पूर्ण, 	/* FVco 600.000000 */
	अणु .frequency = 160000000,	.driver_data = PLLVAL(0x98, 4, 2),  पूर्ण, 	/* FVco 640.000000 */
	अणु .frequency = 170000000,	.driver_data = PLLVAL(0x4d, 1, 2),  पूर्ण, 	/* FVco 680.000000 */
	अणु .frequency = 180000000,	.driver_data = PLLVAL(0x70, 2, 2),  पूर्ण, 	/* FVco 720.000000 */
	अणु .frequency = 190000000,	.driver_data = PLLVAL(0x57, 1, 2),  पूर्ण, 	/* FVco 760.000000 */
	अणु .frequency = 200000000,	.driver_data = PLLVAL(0x5c, 1, 2),  पूर्ण, 	/* FVco 800.000000 */
	अणु .frequency = 210000000,	.driver_data = PLLVAL(0x84, 2, 2),  पूर्ण, 	/* FVco 840.000000 */
	अणु .frequency = 220000000,	.driver_data = PLLVAL(0x66, 1, 2),  पूर्ण, 	/* FVco 880.000000 */
	अणु .frequency = 230000000,	.driver_data = PLLVAL(0x6b, 1, 2),  पूर्ण, 	/* FVco 920.000000 */
	अणु .frequency = 240000000,	.driver_data = PLLVAL(0x70, 1, 2),  पूर्ण, 	/* FVco 960.000000 */
	अणु .frequency = 300000000,	.driver_data = PLLVAL(0x75, 3, 1),  पूर्ण, 	/* FVco 600.000000 */
	अणु .frequency = 310000000,	.driver_data = PLLVAL(0x93, 4, 1),  पूर्ण, 	/* FVco 620.000000 */
	अणु .frequency = 320000000,	.driver_data = PLLVAL(0x98, 4, 1),  पूर्ण, 	/* FVco 640.000000 */
	अणु .frequency = 330000000,	.driver_data = PLLVAL(0x66, 2, 1),  पूर्ण, 	/* FVco 660.000000 */
	अणु .frequency = 340000000,	.driver_data = PLLVAL(0x4d, 1, 1),  पूर्ण, 	/* FVco 680.000000 */
	अणु .frequency = 350000000,	.driver_data = PLLVAL(0xa7, 4, 1),  पूर्ण, 	/* FVco 700.000000 */
	अणु .frequency = 360000000,	.driver_data = PLLVAL(0x70, 2, 1),  पूर्ण, 	/* FVco 720.000000 */
	अणु .frequency = 370000000,	.driver_data = PLLVAL(0xb1, 4, 1),  पूर्ण, 	/* FVco 740.000000 */
	अणु .frequency = 380000000,	.driver_data = PLLVAL(0x57, 1, 1),  पूर्ण, 	/* FVco 760.000000 */
	अणु .frequency = 390000000,	.driver_data = PLLVAL(0x7a, 2, 1),  पूर्ण, 	/* FVco 780.000000 */
	अणु .frequency = 400000000,	.driver_data = PLLVAL(0x5c, 1, 1),  पूर्ण, 	/* FVco 800.000000 */
पूर्ण;

अटल पूर्णांक s3c2440_plls12_add(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	काष्ठा clk *xtal_clk;
	अचिन्हित दीर्घ xtal;

	xtal_clk = clk_get(शून्य, "xtal");
	अगर (IS_ERR(xtal_clk))
		वापस PTR_ERR(xtal_clk);

	xtal = clk_get_rate(xtal_clk);
	clk_put(xtal_clk);

	अगर (xtal == 12000000) अणु
		prपूर्णांकk(KERN_INFO "Using PLL table for 12MHz crystal\n");
		वापस s3c_plltab_रेजिस्टर(s3c2440_plls_12,
					   ARRAY_SIZE(s3c2440_plls_12));
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface s3c2440_plls12_पूर्णांकerface = अणु
	.name		= "s3c2440_plls12",
	.subsys		= &s3c2440_subsys,
	.add_dev	= s3c2440_plls12_add,
पूर्ण;

अटल पूर्णांक __init s3c2440_pll_12mhz(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2440_plls12_पूर्णांकerface);

पूर्ण
arch_initcall(s3c2440_pll_12mhz);

अटल काष्ठा subsys_पूर्णांकerface s3c2442_plls12_पूर्णांकerface = अणु
	.name		= "s3c2442_plls12",
	.subsys		= &s3c2442_subsys,
	.add_dev	= s3c2440_plls12_add,
पूर्ण;

अटल पूर्णांक __init s3c2442_pll_12mhz(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2442_plls12_पूर्णांकerface);

पूर्ण
arch_initcall(s3c2442_pll_12mhz);
