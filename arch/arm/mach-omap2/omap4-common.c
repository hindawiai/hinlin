<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 specअगरic common source file.
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Author:
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/export.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reboot.h>
#समावेश <linux/genभाग.स>

#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/memblock.h>
#समावेश <यंत्र/smp_twd.h>

#समावेश "omap-wakeupgen.h"
#समावेश "soc.h"
#समावेश "iomap.h"
#समावेश "common.h"
#समावेश "prminst44xx.h"
#समावेश "prcm_mpu44xx.h"
#समावेश "omap4-sar-layout.h"
#समावेश "omap-secure.h"
#समावेश "sram.h"

#अगर_घोषित CONFIG_CACHE_L2X0
अटल व्योम __iomem *l2cache_base;
#पूर्ण_अगर

अटल व्योम __iomem *sar_ram_base;
अटल व्योम __iomem *gic_dist_base_addr;
अटल व्योम __iomem *twd_base;

#घोषणा IRQ_LOCALTIMER		29

#अगर_घोषित CONFIG_OMAP_INTERCONNECT_BARRIER

/* Used to implement memory barrier on DRAM path */
#घोषणा OMAP4_DRAM_BARRIER_VA			0xfe600000

अटल व्योम __iomem *dram_sync, *sram_sync;
अटल phys_addr_t dram_sync_paddr;
अटल u32 dram_sync_size;

/*
 * The OMAP4 bus काष्ठाure contains asynchronous bridges which can buffer
 * data ग_लिखोs from the MPU. These asynchronous bridges can be found on
 * paths between the MPU to EMIF, and the MPU to L3 पूर्णांकerconnects.
 *
 * We need to be careful about re-ordering which can happen as a result
 * of dअगरferent accesses being perक्रमmed via dअगरferent paths, and
 * thereक्रमe dअगरferent asynchronous bridges.
 */

/*
 * OMAP4 पूर्णांकerconnect barrier which is called क्रम each mb() and wmb().
 * This is to ensure that normal paths to DRAM (normal memory, cacheable
 * accesses) are properly synchronised with ग_लिखोs to DMA coherent memory
 * (normal memory, uncacheable) and device ग_लिखोs.
 *
 * The mb() and wmb() barriers only operate only on the MPU->MA->EMIF
 * path, as we need to ensure that data is visible to other प्रणाली
 * masters prior to ग_लिखोs to those प्रणाली masters being seen.
 *
 * Note: the SRAM path is not synchronised via mb() and wmb().
 */
अटल व्योम omap4_mb(व्योम)
अणु
	अगर (dram_sync)
		ग_लिखोl_relaxed(0, dram_sync);
पूर्ण

/*
 * OMAP4 Errata i688 - asynchronous bridge corruption when entering WFI.
 *
 * If a data is stalled inside asynchronous bridge because of back
 * pressure, it may be accepted multiple बार, creating poपूर्णांकer
 * misalignment that will corrupt next transfers on that data path until
 * next reset of the प्रणाली. No recovery procedure once the issue is hit,
 * the path reमुख्यs consistently broken.
 *
 * Async bridges can be found on paths between MPU to EMIF and MPU to L3
 * पूर्णांकerconnects.
 *
 * This situation can happen only when the idle is initiated by a Master
 * Request Disconnection (which is trigged by software when executing WFI
 * on the CPU).
 *
 * The work-around क्रम this errata needs all the initiators connected
 * through an async bridge to ensure that data path is properly drained
 * beक्रमe issuing WFI. This condition will be met अगर one Strongly ordered
 * access is perक्रमmed to the target right beक्रमe executing the WFI.
 *
 * In MPU हाल, L3 T2ASYNC FIFO and DDR T2ASYNC FIFO needs to be drained.
 * IO barrier ensure that there is no synchronisation loss on initiators
 * operating on both पूर्णांकerconnect port simultaneously.
 *
 * This is a stronger version of the OMAP4 memory barrier below, and
 * operates on both the MPU->MA->EMIF path but also the MPU->OCP path
 * as well, and is necessary prior to executing a WFI.
 */
व्योम omap_पूर्णांकerconnect_sync(व्योम)
अणु
	अगर (dram_sync && sram_sync) अणु
		ग_लिखोl_relaxed(पढ़ोl_relaxed(dram_sync), dram_sync);
		ग_लिखोl_relaxed(पढ़ोl_relaxed(sram_sync), sram_sync);
		isb();
	पूर्ण
पूर्ण

अटल पूर्णांक __init omap4_sram_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा gen_pool *sram_pool;

	अगर (!soc_is_omap44xx() && !soc_is_omap54xx())
		वापस 0;

	np = of_find_compatible_node(शून्य, शून्य, "ti,omap4-mpu");
	अगर (!np)
		pr_warn("%s:Unable to allocate sram needed to handle errata I688\n",
			__func__);
	sram_pool = of_gen_pool_get(np, "sram", 0);
	अगर (!sram_pool)
		pr_warn("%s:Unable to get sram pool needed to handle errata I688\n",
			__func__);
	अन्यथा
		sram_sync = (व्योम *)gen_pool_alloc(sram_pool, PAGE_SIZE);

	वापस 0;
पूर्ण
omap_arch_initcall(omap4_sram_init);

/* Steal one page physical memory क्रम barrier implementation */
व्योम __init omap_barrier_reserve_memblock(व्योम)
अणु
	dram_sync_size = ALIGN(PAGE_SIZE, SZ_1M);
	dram_sync_paddr = arm_memblock_steal(dram_sync_size, SZ_1M);
पूर्ण

व्योम __init omap_barriers_init(व्योम)
अणु
	काष्ठा map_desc dram_io_desc[1];

	dram_io_desc[0].भव = OMAP4_DRAM_BARRIER_VA;
	dram_io_desc[0].pfn = __phys_to_pfn(dram_sync_paddr);
	dram_io_desc[0].length = dram_sync_size;
	dram_io_desc[0].type = MT_MEMORY_RW_SO;
	iotable_init(dram_io_desc, ARRAY_SIZE(dram_io_desc));
	dram_sync = (व्योम __iomem *) dram_io_desc[0].भव;

	pr_info("OMAP4: Map %pa to %p for dram barrier\n",
		&dram_sync_paddr, dram_sync);

	soc_mb = omap4_mb;
पूर्ण

#पूर्ण_अगर

व्योम gic_dist_disable(व्योम)
अणु
	अगर (gic_dist_base_addr)
		ग_लिखोl_relaxed(0x0, gic_dist_base_addr + GIC_DIST_CTRL);
पूर्ण

व्योम gic_dist_enable(व्योम)
अणु
	अगर (gic_dist_base_addr)
		ग_लिखोl_relaxed(0x1, gic_dist_base_addr + GIC_DIST_CTRL);
पूर्ण

bool gic_dist_disabled(व्योम)
अणु
	वापस !(पढ़ोl_relaxed(gic_dist_base_addr + GIC_DIST_CTRL) & 0x1);
पूर्ण

व्योम gic_समयr_retrigger(व्योम)
अणु
	u32 twd_पूर्णांक = पढ़ोl_relaxed(twd_base + TWD_TIMER_INTSTAT);
	u32 gic_पूर्णांक = पढ़ोl_relaxed(gic_dist_base_addr + GIC_DIST_PENDING_SET);
	u32 twd_ctrl = पढ़ोl_relaxed(twd_base + TWD_TIMER_CONTROL);

	अगर (twd_पूर्णांक && !(gic_पूर्णांक & BIT(IRQ_LOCALTIMER))) अणु
		/*
		 * The local समयr पूर्णांकerrupt got lost जबतक the distributor was
		 * disabled.  Ack the pending पूर्णांकerrupt, and retrigger it.
		 */
		pr_warn("%s: lost localtimer interrupt\n", __func__);
		ग_लिखोl_relaxed(1, twd_base + TWD_TIMER_INTSTAT);
		अगर (!(twd_ctrl & TWD_TIMER_CONTROL_PERIODIC)) अणु
			ग_लिखोl_relaxed(1, twd_base + TWD_TIMER_COUNTER);
			twd_ctrl |= TWD_TIMER_CONTROL_ENABLE;
			ग_लिखोl_relaxed(twd_ctrl, twd_base + TWD_TIMER_CONTROL);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CACHE_L2X0

व्योम __iomem *omap4_get_l2cache_base(व्योम)
अणु
	वापस l2cache_base;
पूर्ण

व्योम omap4_l2c310_ग_लिखो_sec(अचिन्हित दीर्घ val, अचिन्हित reg)
अणु
	अचिन्हित smc_op;

	चयन (reg) अणु
	हाल L2X0_CTRL:
		smc_op = OMAP4_MON_L2X0_CTRL_INDEX;
		अवरोध;

	हाल L2X0_AUX_CTRL:
		smc_op = OMAP4_MON_L2X0_AUXCTRL_INDEX;
		अवरोध;

	हाल L2X0_DEBUG_CTRL:
		smc_op = OMAP4_MON_L2X0_DBG_CTRL_INDEX;
		अवरोध;

	हाल L310_PREFETCH_CTRL:
		smc_op = OMAP4_MON_L2X0_PREFETCH_INDEX;
		अवरोध;

	हाल L310_POWER_CTRL:
		pr_info_once("OMAP L2C310: ROM does not support power control setting\n");
		वापस;

	शेष:
		WARN_ONCE(1, "OMAP L2C310: ignoring write to reg 0x%x\n", reg);
		वापस;
	पूर्ण

	omap_smc1(smc_op, val);
पूर्ण

पूर्णांक __init omap_l2_cache_init(व्योम)
अणु
	/* Static mapping, never released */
	l2cache_base = ioremap(OMAP44XX_L2CACHE_BASE, SZ_4K);
	अगर (WARN_ON(!l2cache_base))
		वापस -ENOMEM;
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम __iomem *omap4_get_sar_ram_base(व्योम)
अणु
	वापस sar_ram_base;
पूर्ण

/*
 * SAR RAM used to save and restore the HW context in low घातer modes.
 * Note that we need to initialize this very early क्रम kexec. See
 * omap4_mpuss_early_init().
 */
व्योम __init omap4_sar_ram_init(व्योम)
अणु
	अचिन्हित दीर्घ sar_base;

	/*
	 * To aव्योम code running on other OMAPs in
	 * multi-omap builds
	 */
	अगर (cpu_is_omap44xx())
		sar_base = OMAP44XX_SAR_RAM_BASE;
	अन्यथा अगर (soc_is_omap54xx())
		sar_base = OMAP54XX_SAR_RAM_BASE;
	अन्यथा
		वापस;

	/* Static mapping, never released */
	sar_ram_base = ioremap(sar_base, SZ_16K);
	अगर (WARN_ON(!sar_ram_base))
		वापस;
पूर्ण

अटल स्थिर काष्ठा of_device_id पूर्णांकc_match[] = अणु
	अणु .compatible = "ti,omap4-wugen-mpu", पूर्ण,
	अणु .compatible = "ti,omap5-wugen-mpu", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा device_node *पूर्णांकc_node;

व्योम __init omap_gic_of_init(व्योम)
अणु
	काष्ठा device_node *np;

	पूर्णांकc_node = of_find_matching_node(शून्य, पूर्णांकc_match);
	अगर (WARN_ON(!पूर्णांकc_node)) अणु
		pr_err("No WUGEN found in DT, system will misbehave.\n");
		pr_err("UPDATE YOUR DEVICE TREE!\n");
	पूर्ण

	/* Extract GIC distributor and TWD bases क्रम OMAP4460 ROM Errata WA */
	अगर (!cpu_is_omap446x())
		जाओ skip_errata_init;

	np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-gic");
	gic_dist_base_addr = of_iomap(np, 0);
	WARN_ON(!gic_dist_base_addr);

	np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-twd-timer");
	twd_base = of_iomap(np, 0);
	WARN_ON(!twd_base);

skip_errata_init:
	irqchip_init();
पूर्ण
