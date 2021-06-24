<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2006-2007 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//	Vincent Sanders <vince@arm.linux.org.uk>
//
// S3C2410 CPU PLL tables

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>

#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>
#समावेश <linux/soc/samsung/s3c-pm.h>

/* This array should be sorted in ascending order of the frequencies */
अटल काष्ठा cpufreq_frequency_table pll_vals_12MHz[] = अणु
    अणु .frequency = 34000000,  .driver_data = PLLVAL(82, 2, 3),   पूर्ण,
    अणु .frequency = 45000000,  .driver_data = PLLVAL(82, 1, 3),   पूर्ण,
    अणु .frequency = 48000000,  .driver_data = PLLVAL(120, 2, 3),  पूर्ण,
    अणु .frequency = 51000000,  .driver_data = PLLVAL(161, 3, 3),  पूर्ण,
    अणु .frequency = 56000000,  .driver_data = PLLVAL(142, 2, 3),  पूर्ण,
    अणु .frequency = 68000000,  .driver_data = PLLVAL(82, 2, 2),   पूर्ण,
    अणु .frequency = 79000000,  .driver_data = PLLVAL(71, 1, 2),   पूर्ण,
    अणु .frequency = 85000000,  .driver_data = PLLVAL(105, 2, 2),  पूर्ण,
    अणु .frequency = 90000000,  .driver_data = PLLVAL(112, 2, 2),  पूर्ण,
    अणु .frequency = 101000000, .driver_data = PLLVAL(127, 2, 2),  पूर्ण,
    अणु .frequency = 113000000, .driver_data = PLLVAL(105, 1, 2),  पूर्ण,
    अणु .frequency = 118000000, .driver_data = PLLVAL(150, 2, 2),  पूर्ण,
    अणु .frequency = 124000000, .driver_data = PLLVAL(116, 1, 2),  पूर्ण,
    अणु .frequency = 135000000, .driver_data = PLLVAL(82, 2, 1),   पूर्ण,
    अणु .frequency = 147000000, .driver_data = PLLVAL(90, 2, 1),   पूर्ण,
    अणु .frequency = 152000000, .driver_data = PLLVAL(68, 1, 1),   पूर्ण,
    अणु .frequency = 158000000, .driver_data = PLLVAL(71, 1, 1),   पूर्ण,
    अणु .frequency = 170000000, .driver_data = PLLVAL(77, 1, 1),   पूर्ण,
    अणु .frequency = 180000000, .driver_data = PLLVAL(82, 1, 1),   पूर्ण,
    अणु .frequency = 186000000, .driver_data = PLLVAL(85, 1, 1),   पूर्ण,
    अणु .frequency = 192000000, .driver_data = PLLVAL(88, 1, 1),   पूर्ण,
    अणु .frequency = 203000000, .driver_data = PLLVAL(161, 3, 1),  पूर्ण,

    /* 2410A extras */

    अणु .frequency = 210000000, .driver_data = PLLVAL(132, 2, 1),  पूर्ण,
    अणु .frequency = 226000000, .driver_data = PLLVAL(105, 1, 1),  पूर्ण,
    अणु .frequency = 266000000, .driver_data = PLLVAL(125, 1, 1),  पूर्ण,
    अणु .frequency = 268000000, .driver_data = PLLVAL(126, 1, 1),  पूर्ण,
    अणु .frequency = 270000000, .driver_data = PLLVAL(127, 1, 1),  पूर्ण,
पूर्ण;

अटल पूर्णांक s3c2410_plls_add(काष्ठा device *dev, काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	वापस s3c_plltab_रेजिस्टर(pll_vals_12MHz, ARRAY_SIZE(pll_vals_12MHz));
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface s3c2410_plls_पूर्णांकerface = अणु
	.name		= "s3c2410_plls",
	.subsys		= &s3c2410_subsys,
	.add_dev	= s3c2410_plls_add,
पूर्ण;

अटल पूर्णांक __init s3c2410_pll_init(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2410_plls_पूर्णांकerface);

पूर्ण
arch_initcall(s3c2410_pll_init);

अटल काष्ठा subsys_पूर्णांकerface s3c2410a_plls_पूर्णांकerface = अणु
	.name		= "s3c2410a_plls",
	.subsys		= &s3c2410a_subsys,
	.add_dev	= s3c2410_plls_add,
पूर्ण;

अटल पूर्णांक __init s3c2410a_pll_init(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2410a_plls_पूर्णांकerface);
पूर्ण
arch_initcall(s3c2410a_pll_init);
