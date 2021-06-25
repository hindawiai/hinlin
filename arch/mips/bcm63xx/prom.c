<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/bmips.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <bcm63xx_board.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>

व्योम __init prom_init(व्योम)
अणु
	u32 reg, mask;

	bcm63xx_cpu_init();

	/* stop any running watchकरोg */
	bcm_wdt_ग_लिखोl(WDT_STOP_1, WDT_CTL_REG);
	bcm_wdt_ग_लिखोl(WDT_STOP_2, WDT_CTL_REG);

	/* disable all hardware blocks घड़ी क्रम now */
	अगर (BCMCPU_IS_3368())
		mask = CKCTL_3368_ALL_SAFE_EN;
	अन्यथा अगर (BCMCPU_IS_6328())
		mask = CKCTL_6328_ALL_SAFE_EN;
	अन्यथा अगर (BCMCPU_IS_6338())
		mask = CKCTL_6338_ALL_SAFE_EN;
	अन्यथा अगर (BCMCPU_IS_6345())
		mask = CKCTL_6345_ALL_SAFE_EN;
	अन्यथा अगर (BCMCPU_IS_6348())
		mask = CKCTL_6348_ALL_SAFE_EN;
	अन्यथा अगर (BCMCPU_IS_6358())
		mask = CKCTL_6358_ALL_SAFE_EN;
	अन्यथा अगर (BCMCPU_IS_6362())
		mask = CKCTL_6362_ALL_SAFE_EN;
	अन्यथा अगर (BCMCPU_IS_6368())
		mask = CKCTL_6368_ALL_SAFE_EN;
	अन्यथा
		mask = 0;

	reg = bcm_perf_पढ़ोl(PERF_CKCTL_REG);
	reg &= ~mask;
	bcm_perf_ग_लिखोl(reg, PERF_CKCTL_REG);

	/* करो low level board init */
	board_prom_init();

	/* set up SMP */
	अगर (!रेजिस्टर_bmips_smp_ops()) अणु
		/*
		 * BCM6328 might not have its second CPU enabled, जबतक BCM3368
		 * and BCM6358 need special handling क्रम their shared TLB, so
		 * disable SMP क्रम now.
		 */
		अगर (BCMCPU_IS_6328()) अणु
			reg = bcm_पढ़ोl(BCM_6328_OTP_BASE +
					OTP_USER_BITS_6328_REG(3));

			अगर (reg & OTP_6328_REG3_TP1_DISABLED)
				bmips_smp_enabled = 0;
		पूर्ण अन्यथा अगर (BCMCPU_IS_3368() || BCMCPU_IS_6358()) अणु
			bmips_smp_enabled = 0;
		पूर्ण

		अगर (!bmips_smp_enabled)
			वापस;

		/*
		 * The bootloader has set up the CPU1 reset vector at
		 * 0xa000_0200.
		 * This conflicts with the special पूर्णांकerrupt vector (IV).
		 * The bootloader has also set up CPU1 to respond to the wrong
		 * IPI पूर्णांकerrupt.
		 * Here we will start up CPU1 in the background and ask it to
		 * reconfigure itself then go back to sleep.
		 */
		स_नकल((व्योम *)0xa0000200, bmips_smp_movevec, 0x20);
		__sync();
		set_c0_cause(C_SW0);
		cpumask_set_cpu(1, &bmips_booted_mask);

		/*
		 * FIXME: we really should have some sort of hazard barrier here
		 */
	पूर्ण
पूर्ण
