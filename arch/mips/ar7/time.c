<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 *
 * Setting up the घड़ी on the MIPS boards.
 */

#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mach-ar7/ar7.h>

व्योम __init plat_समय_init(व्योम)
अणु
	काष्ठा clk *cpu_clk;

	/* Initialize ar7 घड़ीs so the CPU घड़ी frequency is correct */
	ar7_init_घड़ीs();

	cpu_clk = clk_get(शून्य, "cpu");
	अगर (IS_ERR(cpu_clk)) अणु
		prपूर्णांकk(KERN_ERR "unable to get cpu clock\n");
		वापस;
	पूर्ण

	mips_hpt_frequency = clk_get_rate(cpu_clk) / 2;
पूर्ण
