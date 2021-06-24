<शैली गुरु>
/*
 * Broadcom STB CPU SMP and hotplug support क्रम ARM
 *
 * Copyright (C) 2013-2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/smp.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/smp_plat.h>

क्रमागत अणु
	ZONE_MAN_CLKEN_MASK		= BIT(0),
	ZONE_MAN_RESET_CNTL_MASK	= BIT(1),
	ZONE_MAN_MEM_PWR_MASK		= BIT(4),
	ZONE_RESERVED_1_MASK		= BIT(5),
	ZONE_MAN_ISO_CNTL_MASK		= BIT(6),
	ZONE_MANUAL_CONTROL_MASK	= BIT(7),
	ZONE_PWR_DN_REQ_MASK		= BIT(9),
	ZONE_PWR_UP_REQ_MASK		= BIT(10),
	ZONE_BLK_RST_ASSERT_MASK	= BIT(12),
	ZONE_PWR_OFF_STATE_MASK		= BIT(25),
	ZONE_PWR_ON_STATE_MASK		= BIT(26),
	ZONE_DPG_PWR_STATE_MASK		= BIT(28),
	ZONE_MEM_PWR_STATE_MASK		= BIT(29),
	ZONE_RESET_STATE_MASK		= BIT(31),
	CPU0_PWR_ZONE_CTRL_REG		= 1,
	CPU_RESET_CONFIG_REG		= 2,
पूर्ण;

अटल व्योम __iomem *cpubiuctrl_block;
अटल व्योम __iomem *hअगर_cont_block;
अटल u32 cpu0_pwr_zone_ctrl_reg;
अटल u32 cpu_rst_cfg_reg;
अटल u32 hअगर_cont_reg;

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * We must quiesce a dying CPU beक्रमe it can be समाप्तed by the boot CPU. Because
 * one or more cache may be disabled, we must flush to ensure coherency. We
 * cannot use traditionl completion काष्ठाures or spinlocks as they rely on
 * coherency.
 */
अटल DEFINE_PER_CPU_ALIGNED(पूर्णांक, per_cpu_sw_state);

अटल पूर्णांक per_cpu_sw_state_rd(u32 cpu)
अणु
	sync_cache_r(SHIFT_PERCPU_PTR(&per_cpu_sw_state, per_cpu_offset(cpu)));
	वापस per_cpu(per_cpu_sw_state, cpu);
पूर्ण

अटल व्योम per_cpu_sw_state_wr(u32 cpu, पूर्णांक val)
अणु
	dmb();
	per_cpu(per_cpu_sw_state, cpu) = val;
	sync_cache_w(SHIFT_PERCPU_PTR(&per_cpu_sw_state, per_cpu_offset(cpu)));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम per_cpu_sw_state_wr(u32 cpu, पूर्णांक val) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम __iomem *pwr_ctrl_get_base(u32 cpu)
अणु
	व्योम __iomem *base = cpubiuctrl_block + cpu0_pwr_zone_ctrl_reg;
	base += (cpu_logical_map(cpu) * 4);
	वापस base;
पूर्ण

अटल u32 pwr_ctrl_rd(u32 cpu)
अणु
	व्योम __iomem *base = pwr_ctrl_get_base(cpu);
	वापस पढ़ोl_relaxed(base);
पूर्ण

अटल व्योम pwr_ctrl_set(अचिन्हित पूर्णांक cpu, u32 val, u32 mask)
अणु
	व्योम __iomem *base = pwr_ctrl_get_base(cpu);
	ग_लिखोl((पढ़ोl(base) & mask) | val, base);
पूर्ण

अटल व्योम pwr_ctrl_clr(अचिन्हित पूर्णांक cpu, u32 val, u32 mask)
अणु
	व्योम __iomem *base = pwr_ctrl_get_base(cpu);
	ग_लिखोl((पढ़ोl(base) & mask) & ~val, base);
पूर्ण

#घोषणा POLL_TMOUT_MS 500
अटल पूर्णांक pwr_ctrl_रुको_पंचांगout(अचिन्हित पूर्णांक cpu, u32 set, u32 mask)
अणु
	स्थिर अचिन्हित दीर्घ समयo = jअगरfies + msecs_to_jअगरfies(POLL_TMOUT_MS);
	u32 पंचांगp;

	करो अणु
		पंचांगp = pwr_ctrl_rd(cpu) & mask;
		अगर (!set == !पंचांगp)
			वापस 0;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयo));

	पंचांगp = pwr_ctrl_rd(cpu) & mask;
	अगर (!set == !पंचांगp)
		वापस 0;

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम cpu_rst_cfg_set(u32 cpu, पूर्णांक set)
अणु
	u32 val;
	val = पढ़ोl_relaxed(cpubiuctrl_block + cpu_rst_cfg_reg);
	अगर (set)
		val |= BIT(cpu_logical_map(cpu));
	अन्यथा
		val &= ~BIT(cpu_logical_map(cpu));
	ग_लिखोl_relaxed(val, cpubiuctrl_block + cpu_rst_cfg_reg);
पूर्ण

अटल व्योम cpu_set_boot_addr(u32 cpu, अचिन्हित दीर्घ boot_addr)
अणु
	स्थिर पूर्णांक reg_ofs = cpu_logical_map(cpu) * 8;
	ग_लिखोl_relaxed(0, hअगर_cont_block + hअगर_cont_reg + reg_ofs);
	ग_लिखोl_relaxed(boot_addr, hअगर_cont_block + hअगर_cont_reg + 4 + reg_ofs);
पूर्ण

अटल व्योम brcmstb_cpu_boot(u32 cpu)
अणु
	/* Mark this CPU as "up" */
	per_cpu_sw_state_wr(cpu, 1);

	/*
	 * Set the reset vector to poपूर्णांक to the secondary_startup
	 * routine
	 */
	cpu_set_boot_addr(cpu, __pa_symbol(secondary_startup));

	/* Unhalt the cpu */
	cpu_rst_cfg_set(cpu, 0);
पूर्ण

अटल व्योम brcmstb_cpu_घातer_on(u32 cpu)
अणु
	/*
	 * The secondary cores घातer was cut, so we must go through
	 * घातer-on initialization.
	 */
	pwr_ctrl_set(cpu, ZONE_MAN_ISO_CNTL_MASK, 0xffffff00);
	pwr_ctrl_set(cpu, ZONE_MANUAL_CONTROL_MASK, -1);
	pwr_ctrl_set(cpu, ZONE_RESERVED_1_MASK, -1);

	pwr_ctrl_set(cpu, ZONE_MAN_MEM_PWR_MASK, -1);

	अगर (pwr_ctrl_रुको_पंचांगout(cpu, 1, ZONE_MEM_PWR_STATE_MASK))
		panic("ZONE_MEM_PWR_STATE_MASK set timeout");

	pwr_ctrl_set(cpu, ZONE_MAN_CLKEN_MASK, -1);

	अगर (pwr_ctrl_रुको_पंचांगout(cpu, 1, ZONE_DPG_PWR_STATE_MASK))
		panic("ZONE_DPG_PWR_STATE_MASK set timeout");

	pwr_ctrl_clr(cpu, ZONE_MAN_ISO_CNTL_MASK, -1);
	pwr_ctrl_set(cpu, ZONE_MAN_RESET_CNTL_MASK, -1);
पूर्ण

अटल पूर्णांक brcmstb_cpu_get_घातer_state(u32 cpu)
अणु
	पूर्णांक पंचांगp = pwr_ctrl_rd(cpu);
	वापस (पंचांगp & ZONE_RESET_STATE_MASK) ? 0 : 1;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

अटल व्योम brcmstb_cpu_die(u32 cpu)
अणु
	v7_निकास_coherency_flush(all);

	per_cpu_sw_state_wr(cpu, 0);

	/* Sit and रुको to die */
	wfi();

	/* We should never get here... */
	जबतक (1)
		;
पूर्ण

अटल पूर्णांक brcmstb_cpu_समाप्त(u32 cpu)
अणु
	/*
	 * Ordinarily, the hardware क्रमbids घातer-करोwn of CPU0 (which is good
	 * because it is the boot CPU), but this is not true when using BPCM
	 * manual mode.  Consequently, we must aव्योम turning off CPU0 here to
	 * ensure that TI2C master reset will work.
	 */
	अगर (cpu == 0) अणु
		pr_warn("SMP: refusing to power off CPU0\n");
		वापस 1;
	पूर्ण

	जबतक (per_cpu_sw_state_rd(cpu))
		;

	pwr_ctrl_set(cpu, ZONE_MANUAL_CONTROL_MASK, -1);
	pwr_ctrl_clr(cpu, ZONE_MAN_RESET_CNTL_MASK, -1);
	pwr_ctrl_clr(cpu, ZONE_MAN_CLKEN_MASK, -1);
	pwr_ctrl_set(cpu, ZONE_MAN_ISO_CNTL_MASK, -1);
	pwr_ctrl_clr(cpu, ZONE_MAN_MEM_PWR_MASK, -1);

	अगर (pwr_ctrl_रुको_पंचांगout(cpu, 0, ZONE_MEM_PWR_STATE_MASK))
		panic("ZONE_MEM_PWR_STATE_MASK clear timeout");

	pwr_ctrl_clr(cpu, ZONE_RESERVED_1_MASK, -1);

	अगर (pwr_ctrl_रुको_पंचांगout(cpu, 0, ZONE_DPG_PWR_STATE_MASK))
		panic("ZONE_DPG_PWR_STATE_MASK clear timeout");

	/* Flush pipeline beक्रमe resetting CPU */
	mb();

	/* Assert reset on the CPU */
	cpu_rst_cfg_set(cpu, 1);

	वापस 1;
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

अटल पूर्णांक __init setup_hअगरcpubiuctrl_regs(काष्ठा device_node *np)
अणु
	पूर्णांक rc = 0;
	अक्षर *name;
	काष्ठा device_node *syscon_np = शून्य;

	name = "syscon-cpu";

	syscon_np = of_parse_phandle(np, name, 0);
	अगर (!syscon_np) अणु
		pr_err("can't find phandle %s\n", name);
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	cpubiuctrl_block = of_iomap(syscon_np, 0);
	अगर (!cpubiuctrl_block) अणु
		pr_err("iomap failed for cpubiuctrl_block\n");
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	rc = of_property_पढ़ो_u32_index(np, name, CPU0_PWR_ZONE_CTRL_REG,
					&cpu0_pwr_zone_ctrl_reg);
	अगर (rc) अणु
		pr_err("failed to read 1st entry from %s property (%d)\n", name,
			rc);
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	rc = of_property_पढ़ो_u32_index(np, name, CPU_RESET_CONFIG_REG,
					&cpu_rst_cfg_reg);
	अगर (rc) अणु
		pr_err("failed to read 2nd entry from %s property (%d)\n", name,
			rc);
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

cleanup:
	of_node_put(syscon_np);
	वापस rc;
पूर्ण

अटल पूर्णांक __init setup_hअगरcont_regs(काष्ठा device_node *np)
अणु
	पूर्णांक rc = 0;
	अक्षर *name;
	काष्ठा device_node *syscon_np = शून्य;

	name = "syscon-cont";

	syscon_np = of_parse_phandle(np, name, 0);
	अगर (!syscon_np) अणु
		pr_err("can't find phandle %s\n", name);
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	hअगर_cont_block = of_iomap(syscon_np, 0);
	अगर (!hअगर_cont_block) अणु
		pr_err("iomap failed for hif_cont_block\n");
		rc = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/* Offset is at top of hअगर_cont_block */
	hअगर_cont_reg = 0;

cleanup:
	of_node_put(syscon_np);
	वापस rc;
पूर्ण

अटल व्योम __init brcmstb_cpu_ctrl_setup(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक rc;
	काष्ठा device_node *np;
	अक्षर *name;

	name = "brcm,brcmstb-smpboot";
	np = of_find_compatible_node(शून्य, शून्य, name);
	अगर (!np) अणु
		pr_err("can't find compatible node %s\n", name);
		वापस;
	पूर्ण

	rc = setup_hअगरcpubiuctrl_regs(np);
	अगर (rc)
		जाओ out_put_node;

	rc = setup_hअगरcont_regs(np);
	अगर (rc)
		जाओ out_put_node;

out_put_node:
	of_node_put(np);
पूर्ण

अटल पूर्णांक brcmstb_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	/* Missing the brcm,brcmstb-smpboot DT node? */
	अगर (!cpubiuctrl_block || !hअगर_cont_block)
		वापस -ENODEV;

	/* Bring up घातer to the core अगर necessary */
	अगर (brcmstb_cpu_get_घातer_state(cpu) == 0)
		brcmstb_cpu_घातer_on(cpu);

	brcmstb_cpu_boot(cpu);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा smp_operations brcmstb_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= brcmstb_cpu_ctrl_setup,
	.smp_boot_secondary	= brcmstb_boot_secondary,
#अगर_घोषित CONFIG_HOTPLUG_CPU
	.cpu_समाप्त		= brcmstb_cpu_समाप्त,
	.cpu_die		= brcmstb_cpu_die,
#पूर्ण_अगर
पूर्ण;

CPU_METHOD_OF_DECLARE(brcmstb_smp, "brcm,brahma-b15", &brcmstb_smp_ops);
