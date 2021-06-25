<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-omap2/sdrc2xxx.c
 *
 * SDRAM timing related functions क्रम OMAP2xxx
 *
 * Copyright (C) 2005, 2008 Texas Instruments Inc.
 * Copyright (C) 2005, 2008 Nokia Corporation
 *
 * Tony Lindgren <tony@atomide.com>
 * Paul Walmsley
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश "soc.h"
#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "prm2xxx.h"
#समावेश "clock.h"
#समावेश "sdrc.h"
#समावेश "sram.h"

/* Memory timing, DLL mode flags */
#घोषणा M_DDR		1
#घोषणा M_LOCK_CTRL	(1 << 2)
#घोषणा M_UNLOCK	0
#घोषणा M_LOCK		1


अटल काष्ठा memory_timings mem_timings;
अटल u32 curr_perf_level = CORE_CLK_SRC_DPLL_X2;

अटल u32 omap2xxx_sdrc_get_slow_dll_ctrl(व्योम)
अणु
	वापस mem_timings.slow_dll_ctrl;
पूर्ण

अटल u32 omap2xxx_sdrc_get_fast_dll_ctrl(व्योम)
अणु
	वापस mem_timings.fast_dll_ctrl;
पूर्ण

अटल u32 omap2xxx_sdrc_get_type(व्योम)
अणु
	वापस mem_timings.m_type;
पूर्ण

/*
 * Check the DLL lock state, and वापस tue अगर running in unlock mode.
 * This is needed to compensate क्रम the shअगरted DLL value in unlock mode.
 */
u32 omap2xxx_sdrc_dll_is_unlocked(व्योम)
अणु
	/* dlla and dllb are a set */
	u32 dll_state = sdrc_पढ़ो_reg(SDRC_DLLA_CTRL);

	अगर ((dll_state & (1 << 2)) == (1 << 2))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * 'level' is the value to store to CM_CLKSEL2_PLL.CORE_CLK_SRC.
 * Practical values are CORE_CLK_SRC_DPLL (क्रम CORE_CLK = DPLL_CLK) or
 * CORE_CLK_SRC_DPLL_X2 (क्रम CORE_CLK = * DPLL_CLK * 2)
 *
 * Used by the घड़ी framework during CORE DPLL changes
 */
u32 omap2xxx_sdrc_reprogram(u32 level, u32 क्रमce)
अणु
	u32 dll_ctrl, m_type;
	u32 prev = curr_perf_level;
	अचिन्हित दीर्घ flags;

	अगर ((curr_perf_level == level) && !क्रमce)
		वापस prev;

	अगर (level == CORE_CLK_SRC_DPLL)
		dll_ctrl = omap2xxx_sdrc_get_slow_dll_ctrl();
	अन्यथा अगर (level == CORE_CLK_SRC_DPLL_X2)
		dll_ctrl = omap2xxx_sdrc_get_fast_dll_ctrl();
	अन्यथा
		वापस prev;

	m_type = omap2xxx_sdrc_get_type();

	local_irq_save(flags);
	/*
	 * XXX These calls should be असलtracted out through a
	 * prm2xxx.c function
	 */
	अगर (cpu_is_omap2420())
		ग_लिखोl_relaxed(0xffff, OMAP2420_PRCM_VOLTSETUP);
	अन्यथा
		ग_लिखोl_relaxed(0xffff, OMAP2430_PRCM_VOLTSETUP);
	omap2_sram_reprogram_sdrc(level, dll_ctrl, m_type);
	curr_perf_level = level;
	local_irq_restore(flags);

	वापस prev;
पूर्ण

/* Used by the घड़ी framework during CORE DPLL changes */
व्योम omap2xxx_sdrc_init_params(u32 क्रमce_lock_to_unlock_mode)
अणु
	अचिन्हित दीर्घ dll_cnt;
	u32 fast_dll = 0;

	/* DDR = 1, SDR = 0 */
	mem_timings.m_type = !((sdrc_पढ़ो_reg(SDRC_MR_0) & 0x3) == 0x1);

	/* 2422 es2.05 and beyond has a single SIP DDR instead of 2 like others.
	 * In the हाल of 2422, its ok to use CS1 instead of CS0.
	 */
	अगर (cpu_is_omap2422())
		mem_timings.base_cs = 1;
	अन्यथा
		mem_timings.base_cs = 0;

	अगर (mem_timings.m_type != M_DDR)
		वापस;

	/* With DDR we need to determine the low frequency DLL value */
	अगर (((mem_timings.fast_dll_ctrl & (1 << 2)) == M_LOCK_CTRL))
		mem_timings.dll_mode = M_UNLOCK;
	अन्यथा
		mem_timings.dll_mode = M_LOCK;

	अगर (mem_timings.base_cs == 0) अणु
		fast_dll = sdrc_पढ़ो_reg(SDRC_DLLA_CTRL);
		dll_cnt = sdrc_पढ़ो_reg(SDRC_DLLA_STATUS) & 0xff00;
	पूर्ण अन्यथा अणु
		fast_dll = sdrc_पढ़ो_reg(SDRC_DLLB_CTRL);
		dll_cnt = sdrc_पढ़ो_reg(SDRC_DLLB_STATUS) & 0xff00;
	पूर्ण
	अगर (क्रमce_lock_to_unlock_mode) अणु
		fast_dll &= ~0xff00;
		fast_dll |= dll_cnt;		/* Current lock mode */
	पूर्ण
	/* set fast timings with DLL filter disabled */
	mem_timings.fast_dll_ctrl = (fast_dll | (3 << 8));

	/* No disruptions, DDR will be offline & C-ABI not followed */
	omap2_sram_ddr_init(&mem_timings.slow_dll_ctrl,
			    mem_timings.fast_dll_ctrl,
			    mem_timings.base_cs,
			    क्रमce_lock_to_unlock_mode);
	mem_timings.slow_dll_ctrl &= 0xff00;	/* Keep lock value */

	/* Turn status पूर्णांकo unlock ctrl */
	mem_timings.slow_dll_ctrl |=
		((mem_timings.fast_dll_ctrl & 0xF) | (1 << 2));

	/* 90 degree phase क्रम anything below 133MHz + disable DLL filter */
	mem_timings.slow_dll_ctrl |= ((1 << 1) | (3 << 8));
पूर्ण
