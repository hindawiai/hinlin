<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2006-2008 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//	Vincent Sanders <vince@arm.linux.org.uk>
//
// S3C2440/S3C2442 CPU PLL tables (16.93444MHz Crystal)

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>

#समावेश <linux/soc/samsung/s3c-cpufreq-core.h>
#समावेश <linux/soc/samsung/s3c-pm.h>

/* This array should be sorted in ascending order of the frequencies */
अटल काष्ठा cpufreq_frequency_table s3c2440_plls_169344[] = अणु
	अणु .frequency = 78019200,	.driver_data = PLLVAL(121, 5, 3), 	पूर्ण, 	/* FVco 624.153600 */
	अणु .frequency = 84067200,	.driver_data = PLLVAL(131, 5, 3), 	पूर्ण, 	/* FVco 672.537600 */
	अणु .frequency = 90115200,	.driver_data = PLLVAL(141, 5, 3), 	पूर्ण, 	/* FVco 720.921600 */
	अणु .frequency = 96163200,	.driver_data = PLLVAL(151, 5, 3), 	पूर्ण, 	/* FVco 769.305600 */
	अणु .frequency = 102135600,	.driver_data = PLLVAL(185, 6, 3), 	पूर्ण, 	/* FVco 817.084800 */
	अणु .frequency = 108259200,	.driver_data = PLLVAL(171, 5, 3), 	पूर्ण, 	/* FVco 866.073600 */
	अणु .frequency = 114307200,	.driver_data = PLLVAL(127, 3, 3), 	पूर्ण, 	/* FVco 914.457600 */
	अणु .frequency = 120234240,	.driver_data = PLLVAL(134, 3, 3), 	पूर्ण, 	/* FVco 961.873920 */
	अणु .frequency = 126161280,	.driver_data = PLLVAL(141, 3, 3), 	पूर्ण, 	/* FVco 1009.290240 */
	अणु .frequency = 132088320,	.driver_data = PLLVAL(148, 3, 3), 	पूर्ण, 	/* FVco 1056.706560 */
	अणु .frequency = 138015360,	.driver_data = PLLVAL(155, 3, 3), 	पूर्ण, 	/* FVco 1104.122880 */
	अणु .frequency = 144789120,	.driver_data = PLLVAL(163, 3, 3), 	पूर्ण, 	/* FVco 1158.312960 */
	अणु .frequency = 150100363,	.driver_data = PLLVAL(187, 9, 2), 	पूर्ण, 	/* FVco 600.401454 */
	अणु .frequency = 156038400,	.driver_data = PLLVAL(121, 5, 2), 	पूर्ण, 	/* FVco 624.153600 */
	अणु .frequency = 162086400,	.driver_data = PLLVAL(126, 5, 2), 	पूर्ण, 	/* FVco 648.345600 */
	अणु .frequency = 168134400,	.driver_data = PLLVAL(131, 5, 2), 	पूर्ण, 	/* FVco 672.537600 */
	अणु .frequency = 174048000,	.driver_data = PLLVAL(177, 7, 2), 	पूर्ण, 	/* FVco 696.192000 */
	अणु .frequency = 180230400,	.driver_data = PLLVAL(141, 5, 2), 	पूर्ण, 	/* FVco 720.921600 */
	अणु .frequency = 186278400,	.driver_data = PLLVAL(124, 4, 2), 	पूर्ण, 	/* FVco 745.113600 */
	अणु .frequency = 192326400,	.driver_data = PLLVAL(151, 5, 2), 	पूर्ण, 	/* FVco 769.305600 */
	अणु .frequency = 198132480,	.driver_data = PLLVAL(109, 3, 2), 	पूर्ण, 	/* FVco 792.529920 */
	अणु .frequency = 204271200,	.driver_data = PLLVAL(185, 6, 2), 	पूर्ण, 	/* FVco 817.084800 */
	अणु .frequency = 210268800,	.driver_data = PLLVAL(141, 4, 2), 	पूर्ण, 	/* FVco 841.075200 */
	अणु .frequency = 216518400,	.driver_data = PLLVAL(171, 5, 2), 	पूर्ण, 	/* FVco 866.073600 */
	अणु .frequency = 222264000,	.driver_data = PLLVAL(97, 2, 2), 	पूर्ण, 	/* FVco 889.056000 */
	अणु .frequency = 228614400,	.driver_data = PLLVAL(127, 3, 2), 	पूर्ण, 	/* FVco 914.457600 */
	अणु .frequency = 234259200,	.driver_data = PLLVAL(158, 4, 2), 	पूर्ण, 	/* FVco 937.036800 */
	अणु .frequency = 240468480,	.driver_data = PLLVAL(134, 3, 2), 	पूर्ण, 	/* FVco 961.873920 */
	अणु .frequency = 246960000,	.driver_data = PLLVAL(167, 4, 2), 	पूर्ण, 	/* FVco 987.840000 */
	अणु .frequency = 252322560,	.driver_data = PLLVAL(141, 3, 2), 	पूर्ण, 	/* FVco 1009.290240 */
	अणु .frequency = 258249600,	.driver_data = PLLVAL(114, 2, 2), 	पूर्ण, 	/* FVco 1032.998400 */
	अणु .frequency = 264176640,	.driver_data = PLLVAL(148, 3, 2), 	पूर्ण, 	/* FVco 1056.706560 */
	अणु .frequency = 270950400,	.driver_data = PLLVAL(120, 2, 2), 	पूर्ण, 	/* FVco 1083.801600 */
	अणु .frequency = 276030720,	.driver_data = PLLVAL(155, 3, 2), 	पूर्ण, 	/* FVco 1104.122880 */
	अणु .frequency = 282240000,	.driver_data = PLLVAL(92, 1, 2), 	पूर्ण, 	/* FVco 1128.960000 */
	अणु .frequency = 289578240,	.driver_data = PLLVAL(163, 3, 2), 	पूर्ण, 	/* FVco 1158.312960 */
	अणु .frequency = 294235200,	.driver_data = PLLVAL(131, 2, 2), 	पूर्ण, 	/* FVco 1176.940800 */
	अणु .frequency = 300200727,	.driver_data = PLLVAL(187, 9, 1), 	पूर्ण, 	/* FVco 600.401454 */
	अणु .frequency = 306358690,	.driver_data = PLLVAL(191, 9, 1), 	पूर्ण, 	/* FVco 612.717380 */
	अणु .frequency = 312076800,	.driver_data = PLLVAL(121, 5, 1), 	पूर्ण, 	/* FVco 624.153600 */
	अणु .frequency = 318366720,	.driver_data = PLLVAL(86, 3, 1), 	पूर्ण, 	/* FVco 636.733440 */
	अणु .frequency = 324172800,	.driver_data = PLLVAL(126, 5, 1), 	पूर्ण, 	/* FVco 648.345600 */
	अणु .frequency = 330220800,	.driver_data = PLLVAL(109, 4, 1), 	पूर्ण, 	/* FVco 660.441600 */
	अणु .frequency = 336268800,	.driver_data = PLLVAL(131, 5, 1), 	पूर्ण, 	/* FVco 672.537600 */
	अणु .frequency = 342074880,	.driver_data = PLLVAL(93, 3, 1), 	पूर्ण, 	/* FVco 684.149760 */
	अणु .frequency = 348096000,	.driver_data = PLLVAL(177, 7, 1), 	पूर्ण, 	/* FVco 696.192000 */
	अणु .frequency = 355622400,	.driver_data = PLLVAL(118, 4, 1), 	पूर्ण, 	/* FVco 711.244800 */
	अणु .frequency = 360460800,	.driver_data = PLLVAL(141, 5, 1), 	पूर्ण, 	/* FVco 720.921600 */
	अणु .frequency = 366206400,	.driver_data = PLLVAL(165, 6, 1), 	पूर्ण, 	/* FVco 732.412800 */
	अणु .frequency = 372556800,	.driver_data = PLLVAL(124, 4, 1), 	पूर्ण, 	/* FVco 745.113600 */
	अणु .frequency = 378201600,	.driver_data = PLLVAL(126, 4, 1), 	पूर्ण, 	/* FVco 756.403200 */
	अणु .frequency = 384652800,	.driver_data = PLLVAL(151, 5, 1), 	पूर्ण, 	/* FVco 769.305600 */
	अणु .frequency = 391608000,	.driver_data = PLLVAL(177, 6, 1), 	पूर्ण, 	/* FVco 783.216000 */
	अणु .frequency = 396264960,	.driver_data = PLLVAL(109, 3, 1), 	पूर्ण, 	/* FVco 792.529920 */
	अणु .frequency = 402192000,	.driver_data = PLLVAL(87, 2, 1), 	पूर्ण, 	/* FVco 804.384000 */
पूर्ण;

अटल पूर्णांक s3c2440_plls169344_add(काष्ठा device *dev,
				  काष्ठा subsys_पूर्णांकerface *sअगर)
अणु
	काष्ठा clk *xtal_clk;
	अचिन्हित दीर्घ xtal;

	xtal_clk = clk_get(शून्य, "xtal");
	अगर (IS_ERR(xtal_clk))
		वापस PTR_ERR(xtal_clk);

	xtal = clk_get_rate(xtal_clk);
	clk_put(xtal_clk);

	अगर (xtal == 169344000) अणु
		prपूर्णांकk(KERN_INFO "Using PLL table for 16.9344MHz crystal\n");
		वापस s3c_plltab_रेजिस्टर(s3c2440_plls_169344,
					   ARRAY_SIZE(s3c2440_plls_169344));
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा subsys_पूर्णांकerface s3c2440_plls169344_पूर्णांकerface = अणु
	.name		= "s3c2440_plls169344",
	.subsys		= &s3c2440_subsys,
	.add_dev	= s3c2440_plls169344_add,
पूर्ण;

अटल पूर्णांक __init s3c2440_pll_16934400(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2440_plls169344_पूर्णांकerface);
पूर्ण
arch_initcall(s3c2440_pll_16934400);

अटल काष्ठा subsys_पूर्णांकerface s3c2442_plls169344_पूर्णांकerface = अणु
	.name		= "s3c2442_plls169344",
	.subsys		= &s3c2442_subsys,
	.add_dev	= s3c2440_plls169344_add,
पूर्ण;

अटल पूर्णांक __init s3c2442_pll_16934400(व्योम)
अणु
	वापस subsys_पूर्णांकerface_रेजिस्टर(&s3c2442_plls169344_पूर्णांकerface);
पूर्ण
arch_initcall(s3c2442_pll_16934400);
