<शैली गुरु>
/*
 * Suspend/resume support. Currently supporting Armada XP only.
 *
 * Copyright (C) 2014 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mbus.h>
#समावेश <linux/of_address.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/outercache.h>
#समावेश <यंत्र/suspend.h>

#समावेश "coherency.h"
#समावेश "common.h"
#समावेश "pmsu.h"

#घोषणा SDRAM_CONFIG_OFFS                  0x0
#घोषणा  SDRAM_CONFIG_SR_MODE_BIT          BIT(24)
#घोषणा SDRAM_OPERATION_OFFS               0x18
#घोषणा  SDRAM_OPERATION_SELF_REFRESH      0x7
#घोषणा SDRAM_DLB_EVICTION_OFFS            0x30c
#घोषणा  SDRAM_DLB_EVICTION_THRESHOLD_MASK 0xff

अटल व्योम (*mvebu_board_pm_enter)(व्योम __iomem *sdram_reg, u32 srcmd);
अटल व्योम __iomem *sdram_ctrl;

अटल पूर्णांक mvebu_pm_घातerकरोwn(अचिन्हित दीर्घ data)
अणु
	u32 reg, srcmd;

	flush_cache_all();
	outer_flush_all();

	/*
	 * Issue a Data Synchronization Barrier inकाष्ठाion to ensure
	 * that all state saving has been completed.
	 */
	dsb();

	/* Flush the DLB and रुको ~7 usec */
	reg = पढ़ोl(sdram_ctrl + SDRAM_DLB_EVICTION_OFFS);
	reg &= ~SDRAM_DLB_EVICTION_THRESHOLD_MASK;
	ग_लिखोl(reg, sdram_ctrl + SDRAM_DLB_EVICTION_OFFS);

	udelay(7);

	/* Set DRAM in battery backup mode */
	reg = पढ़ोl(sdram_ctrl + SDRAM_CONFIG_OFFS);
	reg &= ~SDRAM_CONFIG_SR_MODE_BIT;
	ग_लिखोl(reg, sdram_ctrl + SDRAM_CONFIG_OFFS);

	/* Prepare to go to self-refresh */

	srcmd = पढ़ोl(sdram_ctrl + SDRAM_OPERATION_OFFS);
	srcmd &= ~0x1F;
	srcmd |= SDRAM_OPERATION_SELF_REFRESH;

	mvebu_board_pm_enter(sdram_ctrl + SDRAM_OPERATION_OFFS, srcmd);

	वापस 0;
पूर्ण

#घोषणा BOOT_INFO_ADDR      0x3000
#घोषणा BOOT_MAGIC_WORD	    0xdeadb002
#घोषणा BOOT_MAGIC_LIST_END 0xffffffff

/*
 * Those रेजिस्टरs are accessed beक्रमe चयनing the पूर्णांकernal रेजिस्टर
 * base, which is why we hardcode the 0xd0000000 base address, the one
 * used by the SoC out of reset.
 */
#घोषणा MBUS_WINDOW_12_CTRL       0xd00200b0
#घोषणा MBUS_INTERNAL_REG_ADDRESS 0xd0020080

#घोषणा SDRAM_WIN_BASE_REG(x)	(0x20180 + (0x8*x))
#घोषणा SDRAM_WIN_CTRL_REG(x)	(0x20184 + (0x8*x))

अटल phys_addr_t mvebu_पूर्णांकernal_reg_base(व्योम)
अणु
	काष्ठा device_node *np;
	__be32 in_addr[2];

	np = of_find_node_by_name(शून्य, "internal-regs");
	BUG_ON(!np);

	/*
	 * Ask the DT what is the पूर्णांकernal रेजिस्टर address on this
	 * platक्रमm. In the mvebu-mbus DT binding, 0xf0010000
	 * corresponds to the पूर्णांकernal रेजिस्टर winकरोw.
	 */
	in_addr[0] = cpu_to_be32(0xf0010000);
	in_addr[1] = 0x0;

	वापस of_translate_address(np, in_addr);
पूर्ण

अटल व्योम mvebu_pm_store_armadaxp_bootinfo(u32 *store_addr)
अणु
	phys_addr_t resume_pc;

	resume_pc = __pa_symbol(armada_370_xp_cpu_resume);

	/*
	 * The bootloader expects the first two words to be a magic
	 * value (BOOT_MAGIC_WORD), followed by the address of the
	 * resume code to jump to. Then, it expects a sequence of
	 * (address, value) pairs, which can be used to restore the
	 * value of certain रेजिस्टरs. This sequence must end with the
	 * BOOT_MAGIC_LIST_END magic value.
	 */

	ग_लिखोl(BOOT_MAGIC_WORD, store_addr++);
	ग_लिखोl(resume_pc, store_addr++);

	/*
	 * Some platक्रमms remap their पूर्णांकernal रेजिस्टर base address
	 * to 0xf1000000. However, out of reset, winकरोw 12 starts at
	 * 0xf0000000 and ends at 0xf7ffffff, which would overlap with
	 * the पूर्णांकernal रेजिस्टरs. Thereक्रमe, disable winकरोw 12.
	 */
	ग_लिखोl(MBUS_WINDOW_12_CTRL, store_addr++);
	ग_लिखोl(0x0, store_addr++);

	/*
	 * Set the पूर्णांकernal रेजिस्टर base address to the value
	 * expected by Linux, as पढ़ो from the Device Tree.
	 */
	ग_लिखोl(MBUS_INTERNAL_REG_ADDRESS, store_addr++);
	ग_लिखोl(mvebu_पूर्णांकernal_reg_base(), store_addr++);

	/*
	 * Ask the mvebu-mbus driver to store the SDRAM winकरोw
	 * configuration, which has to be restored by the bootloader
	 * beक्रमe re-entering the kernel on resume.
	 */
	store_addr += mvebu_mbus_save_cpu_target(store_addr);

	ग_लिखोl(BOOT_MAGIC_LIST_END, store_addr);
पूर्ण

अटल पूर्णांक mvebu_pm_store_bootinfo(व्योम)
अणु
	u32 *store_addr;

	store_addr = phys_to_virt(BOOT_INFO_ADDR);

	अगर (of_machine_is_compatible("marvell,armadaxp"))
		mvebu_pm_store_armadaxp_bootinfo(store_addr);
	अन्यथा
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_enter_suspend(व्योम)
अणु
	पूर्णांक ret;

	ret = mvebu_pm_store_bootinfo();
	अगर (ret)
		वापस ret;

	cpu_pm_enter();

	cpu_suspend(0, mvebu_pm_घातerकरोwn);

	outer_resume();

	mvebu_v7_pmsu_idle_निकास();

	set_cpu_coherent();

	cpu_pm_निकास();
	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_pm_enter(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		cpu_करो_idle();
		अवरोध;
	हाल PM_SUSPEND_MEM:
		pr_warn("Entering suspend to RAM. Only special wake-up sources will resume the system\n");
		वापस mvebu_enter_suspend();
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_pm_valid(suspend_state_t state)
अणु
	अगर (state == PM_SUSPEND_STANDBY)
		वापस 1;

	अगर (state == PM_SUSPEND_MEM && mvebu_board_pm_enter != शून्य)
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops mvebu_pm_ops = अणु
	.enter = mvebu_pm_enter,
	.valid = mvebu_pm_valid,
पूर्ण;

अटल पूर्णांक __init mvebu_pm_init(व्योम)
अणु
	अगर (!of_machine_is_compatible("marvell,armadaxp") &&
	    !of_machine_is_compatible("marvell,armada370") &&
	    !of_machine_is_compatible("marvell,armada380") &&
	    !of_machine_is_compatible("marvell,armada390"))
		वापस -ENODEV;

	suspend_set_ops(&mvebu_pm_ops);

	वापस 0;
पूर्ण


late_initcall(mvebu_pm_init);

पूर्णांक __init mvebu_pm_suspend_init(व्योम (*board_pm_enter)(व्योम __iomem *sdram_reg,
							u32 srcmd))
अणु
	काष्ठा device_node *np;
	काष्ठा resource res;

	np = of_find_compatible_node(शून्य, शून्य,
				     "marvell,armada-xp-sdram-controller");
	अगर (!np)
		वापस -ENODEV;

	अगर (of_address_to_resource(np, 0, &res)) अणु
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण

	अगर (!request_mem_region(res.start, resource_size(&res),
				np->full_name)) अणु
		of_node_put(np);
		वापस -EBUSY;
	पूर्ण

	sdram_ctrl = ioremap(res.start, resource_size(&res));
	अगर (!sdram_ctrl) अणु
		release_mem_region(res.start, resource_size(&res));
		of_node_put(np);
		वापस -ENOMEM;
	पूर्ण

	of_node_put(np);

	mvebu_board_pm_enter = board_pm_enter;

	वापस 0;
पूर्ण
