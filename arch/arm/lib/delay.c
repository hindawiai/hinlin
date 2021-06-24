<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Delay loops based on the OpenRISC implementation.
 *
 * Copyright (C) 2012 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/समयx.h>

/*
 * Default to the loop-based delay implementation.
 */
काष्ठा arm_delay_ops arm_delay_ops __ro_after_init = अणु
	.delay		= __loop_delay,
	.स्थिर_udelay	= __loop_स्थिर_udelay,
	.udelay		= __loop_udelay,
पूर्ण;

अटल स्थिर काष्ठा delay_समयr *delay_समयr;
अटल bool delay_calibrated;
अटल u64 delay_res;

पूर्णांक पढ़ो_current_समयr(अचिन्हित दीर्घ *समयr_val)
अणु
	अगर (!delay_समयr)
		वापस -ENXIO;

	*समयr_val = delay_समयr->पढ़ो_current_समयr();
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पढ़ो_current_समयr);

अटल अंतरभूत u64 cyc_to_ns(u64 cyc, u32 mult, u32 shअगरt)
अणु
	वापस (cyc * mult) >> shअगरt;
पूर्ण

अटल व्योम __समयr_delay(अचिन्हित दीर्घ cycles)
अणु
	cycles_t start = get_cycles();

	जबतक ((get_cycles() - start) < cycles)
		cpu_relax();
पूर्ण

अटल व्योम __समयr_स्थिर_udelay(अचिन्हित दीर्घ xloops)
अणु
	अचिन्हित दीर्घ दीर्घ loops = xloops;
	loops *= arm_delay_ops.ticks_per_jअगरfy;
	__समयr_delay(loops >> UDELAY_SHIFT);
पूर्ण

अटल व्योम __समयr_udelay(अचिन्हित दीर्घ usecs)
अणु
	__समयr_स्थिर_udelay(usecs * UDELAY_MULT);
पूर्ण

व्योम __init रेजिस्टर_current_समयr_delay(स्थिर काष्ठा delay_समयr *समयr)
अणु
	u32 new_mult, new_shअगरt;
	u64 res;

	घड़ीs_calc_mult_shअगरt(&new_mult, &new_shअगरt, समयr->freq,
			       NSEC_PER_SEC, 3600);
	res = cyc_to_ns(1ULL, new_mult, new_shअगरt);

	अगर (res > 1000) अणु
		pr_err("Ignoring delay timer %ps, which has insufficient resolution of %lluns\n",
			समयr, res);
		वापस;
	पूर्ण

	अगर (!delay_calibrated && (!delay_res || (res < delay_res))) अणु
		pr_info("Switching to timer-based delay loop, resolution %lluns\n", res);
		delay_समयr			= समयr;
		lpj_fine			= समयr->freq / HZ;
		delay_res			= res;

		/* cpufreq may scale loops_per_jअगरfy, so keep a निजी copy */
		arm_delay_ops.ticks_per_jअगरfy	= lpj_fine;
		arm_delay_ops.delay		= __समयr_delay;
		arm_delay_ops.स्थिर_udelay	= __समयr_स्थिर_udelay;
		arm_delay_ops.udelay		= __समयr_udelay;
	पूर्ण अन्यथा अणु
		pr_info("Ignoring duplicate/late registration of read_current_timer delay\n");
	पूर्ण
पूर्ण

अचिन्हित दीर्घ calibrate_delay_is_known(व्योम)
अणु
	delay_calibrated = true;
	वापस lpj_fine;
पूर्ण

व्योम calibration_delay_करोne(व्योम)
अणु
	delay_calibrated = true;
पूर्ण
