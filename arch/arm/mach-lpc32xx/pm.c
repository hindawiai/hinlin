<शैली गुरु>
/*
 * arch/arm/mach-lpc32xx/pm.c
 *
 * Original authors: Vitaly Wool, Dmitry Chigirev <source@mvista.com>
 * Modअगरied by Kevin Wells <kevin.wells@nxp.com>
 *
 * 2005 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

/*
 * LPC32XX CPU and प्रणाली घातer management
 *
 * The LPC32XX has three CPU modes क्रम controlling प्रणाली घातer: run,
 * direct-run, and halt modes. When चयनing between halt and run modes,
 * the CPU transistions through direct-run mode. For Linux, direct-run
 * mode is not used in normal operation. Halt mode is used when the
 * प्रणाली is fully suspended.
 *
 * Run mode:
 * The ARM CPU घड़ी (HCLK_PLL), HCLK bus घड़ी, and PCLK bus घड़ीs are
 * derived from the HCLK PLL. The HCLK and PCLK bus rates are भागided from
 * the HCLK_PLL rate. Linux runs in this mode.
 *
 * Direct-run mode:
 * The ARM CPU घड़ी, HCLK bus घड़ी, and PCLK bus घड़ीs are driven from
 * SYSCLK. SYSCLK is usually around 13MHz, but may vary based on SYSCLK
 * source or the frequency of the मुख्य oscillator. In this mode, the
 * HCLK_PLL can be safely enabled, changed, or disabled.
 *
 * Halt mode:
 * SYSCLK is gated off and the CPU and प्रणाली घड़ीs are halted.
 * Peripherals based on the 32KHz oscillator घड़ी (ie, RTC, touch,
 * key scanner, etc.) still operate अगर enabled. In this state, an enabled
 * प्रणाली event (ie, GPIO state change, RTC match, key press, etc.) will
 * wake the प्रणाली up back पूर्णांकo direct-run mode.
 *
 * DRAM refresh
 * DRAM घड़ीing and refresh are slightly dअगरferent क्रम प्रणालीs with DDR
 * DRAM or regular SDRAM devices. If SDRAM is used in the प्रणाली, the
 * SDRAM will still be accessible in direct-run mode. In DDR based प्रणालीs,
 * a transition to direct-run mode will stop all DDR accesses (no घड़ीs).
 * Because of this, the code to चयन घातer modes and the code to enter
 * and निकास DRAM self-refresh modes must not be executed in DRAM. A small
 * section of IRAM is used instead क्रम this.
 *
 * Suspend is handled with the following logic:
 *  Backup a small area of IRAM used क्रम the suspend code
 *  Copy suspend code to IRAM
 *  Transfer control to code in IRAM
 *  Places DRAMs in self-refresh mode
 *  Enter direct-run mode
 *  Save state of HCLK_PLL PLL
 *  Disable HCLK_PLL PLL
 *  Enter halt mode - CPU and buses will stop
 *  System enters direct-run mode when an enabled event occurs
 *  HCLK PLL state is restored
 *  Run mode is entered
 *  DRAMS are placed back पूर्णांकo normal mode
 *  Code execution वापसs from IRAM
 *  IRAM code are used क्रम suspend is restored
 *  Suspend mode is निकासed
 */

#समावेश <linux/suspend.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <यंत्र/cacheflush.h>

#समावेश "lpc32xx.h"
#समावेश "common.h"

#घोषणा TEMP_IRAM_AREA  IO_ADDRESS(LPC32XX_IRAM_BASE)

/*
 * Both STANDBY and MEM suspend states are handled the same with no
 * loss of CPU or memory state
 */
अटल पूर्णांक lpc32xx_pm_enter(suspend_state_t state)
अणु
	पूर्णांक (*lpc32xx_suspend_ptr) (व्योम);
	व्योम *iram_swap_area;

	/* Allocate some space क्रम temporary IRAM storage */
	iram_swap_area = kmemdup((व्योम *)TEMP_IRAM_AREA,
				 lpc32xx_sys_suspend_sz, GFP_KERNEL);
	अगर (!iram_swap_area)
		वापस -ENOMEM;

	/*
	 * Copy code to suspend प्रणाली पूर्णांकo IRAM. The suspend code
	 * needs to run from IRAM as DRAM may no दीर्घer be available
	 * when the PLL is stopped.
	 */
	स_नकल((व्योम *) TEMP_IRAM_AREA, &lpc32xx_sys_suspend,
		lpc32xx_sys_suspend_sz);
	flush_icache_range((अचिन्हित दीर्घ)TEMP_IRAM_AREA,
		(अचिन्हित दीर्घ)(TEMP_IRAM_AREA) + lpc32xx_sys_suspend_sz);

	/* Transfer to suspend code in IRAM */
	lpc32xx_suspend_ptr = (व्योम *) TEMP_IRAM_AREA;
	flush_cache_all();
	(व्योम) lpc32xx_suspend_ptr();

	/* Restore original IRAM contents */
	स_नकल((व्योम *) TEMP_IRAM_AREA, iram_swap_area,
		lpc32xx_sys_suspend_sz);

	kमुक्त(iram_swap_area);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops lpc32xx_pm_ops = अणु
	.valid	= suspend_valid_only_mem,
	.enter	= lpc32xx_pm_enter,
पूर्ण;

#घोषणा EMC_DYN_MEM_CTRL_OFS 0x20
#घोषणा EMC_SRMMC           (1 << 3)
#घोषणा EMC_CTRL_REG io_p2v(LPC32XX_EMC_BASE + EMC_DYN_MEM_CTRL_OFS)
अटल पूर्णांक __init lpc32xx_pm_init(व्योम)
अणु
	/*
	 * Setup SDRAM self-refresh घड़ी to स्वतःmatically disable o
	 * start of self-refresh. This only needs to be करोne once.
	 */
	__raw_ग_लिखोl(__raw_पढ़ोl(EMC_CTRL_REG) | EMC_SRMMC, EMC_CTRL_REG);

	suspend_set_ops(&lpc32xx_pm_ops);

	वापस 0;
पूर्ण
arch_initcall(lpc32xx_pm_init);
