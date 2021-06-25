<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/memblock.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pm.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <bcm63xx_board.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_gpपन.स>

व्योम bcm63xx_machine_halt(व्योम)
अणु
	pr_info("System halted\n");
	जबतक (1)
		;
पूर्ण

अटल व्योम bcm6348_a1_reboot(व्योम)
अणु
	u32 reg;

	/* soft reset all blocks */
	pr_info("soft-resetting all blocks ...\n");
	reg = bcm_perf_पढ़ोl(PERF_SOFTRESET_REG);
	reg &= ~SOFTRESET_6348_ALL;
	bcm_perf_ग_लिखोl(reg, PERF_SOFTRESET_REG);
	mdelay(10);

	reg = bcm_perf_पढ़ोl(PERF_SOFTRESET_REG);
	reg |= SOFTRESET_6348_ALL;
	bcm_perf_ग_लिखोl(reg, PERF_SOFTRESET_REG);
	mdelay(10);

	/* Jump to the घातer on address. */
	pr_info("jumping to reset vector.\n");
	/* set high vectors (base at 0xbfc00000 */
	set_c0_status(ST0_BEV | ST0_ERL);
	/* run uncached in kseg0 */
	change_c0_config(CONF_CM_CMASK, CONF_CM_UNCACHED);
	__flush_cache_all();
	/* हटाओ all wired TLB entries */
	ग_लिखो_c0_wired(0);
	__यंत्र__ __अस्थिर__(
		"jr\t%0"
		:
		: "r" (0xbfc00000));
	जबतक (1)
		;
पूर्ण

व्योम bcm63xx_machine_reboot(व्योम)
अणु
	u32 reg, perf_regs[2] = अणु 0, 0 पूर्ण;
	अचिन्हित पूर्णांक i;

	/* mask and clear all बाह्यal irq */
	चयन (bcm63xx_get_cpu_id()) अणु
	हाल BCM3368_CPU_ID:
		perf_regs[0] = PERF_EXTIRQ_CFG_REG_3368;
		अवरोध;
	हाल BCM6328_CPU_ID:
		perf_regs[0] = PERF_EXTIRQ_CFG_REG_6328;
		अवरोध;
	हाल BCM6338_CPU_ID:
		perf_regs[0] = PERF_EXTIRQ_CFG_REG_6338;
		अवरोध;
	हाल BCM6345_CPU_ID:
		perf_regs[0] = PERF_EXTIRQ_CFG_REG_6345;
		अवरोध;
	हाल BCM6348_CPU_ID:
		perf_regs[0] = PERF_EXTIRQ_CFG_REG_6348;
		अवरोध;
	हाल BCM6358_CPU_ID:
		perf_regs[0] = PERF_EXTIRQ_CFG_REG_6358;
		अवरोध;
	हाल BCM6362_CPU_ID:
		perf_regs[0] = PERF_EXTIRQ_CFG_REG_6362;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		अगर (!perf_regs[i])
			अवरोध;

		reg = bcm_perf_पढ़ोl(perf_regs[i]);
		अगर (BCMCPU_IS_6348()) अणु
			reg &= ~EXTIRQ_CFG_MASK_ALL_6348;
			reg |= EXTIRQ_CFG_CLEAR_ALL_6348;
		पूर्ण अन्यथा अणु
			reg &= ~EXTIRQ_CFG_MASK_ALL;
			reg |= EXTIRQ_CFG_CLEAR_ALL;
		पूर्ण
		bcm_perf_ग_लिखोl(reg, perf_regs[i]);
	पूर्ण

	अगर (BCMCPU_IS_6348() && (bcm63xx_get_cpu_rev() == 0xa1))
		bcm6348_a1_reboot();

	pr_info("triggering watchdog soft-reset...\n");
	अगर (BCMCPU_IS_6328()) अणु
		bcm_wdt_ग_लिखोl(1, WDT_SOFTRESET_REG);
	पूर्ण अन्यथा अणु
		reg = bcm_perf_पढ़ोl(PERF_SYS_PLL_CTL_REG);
		reg |= SYS_PLL_SOFT_RESET;
		bcm_perf_ग_लिखोl(reg, PERF_SYS_PLL_CTL_REG);
	पूर्ण
	जबतक (1)
		;
पूर्ण

अटल व्योम __bcm63xx_machine_reboot(अक्षर *p)
अणु
	bcm63xx_machine_reboot();
पूर्ण

/*
 * वापस प्रणाली type in /proc/cpuinfo
 */
स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	अटल अक्षर buf[128];
	snम_लिखो(buf, माप(buf), "bcm63xx/%s (0x%04x/0x%02X)",
		 board_get_name(),
		 bcm63xx_get_cpu_id(), bcm63xx_get_cpu_rev());
	वापस buf;
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	mips_hpt_frequency = bcm63xx_get_cpu_freq() / 2;
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	memblock_add(0, bcm63xx_get_memory_size());

	_machine_halt = bcm63xx_machine_halt;
	_machine_restart = __bcm63xx_machine_reboot;
	pm_घातer_off = bcm63xx_machine_halt;

	set_io_port_base(0);
	ioport_resource.start = 0;
	ioport_resource.end = ~0;

	board_setup();
पूर्ण

पूर्णांक __init bcm63xx_रेजिस्टर_devices(व्योम)
अणु
	/* रेजिस्टर gpiochip */
	bcm63xx_gpio_init();

	वापस board_रेजिस्टर_devices();
पूर्ण

arch_initcall(bcm63xx_रेजिस्टर_devices);
