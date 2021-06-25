<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom STB SoCs Bus Unit Interface controls
 *
 * Copyright (C) 2015, Broadcom Corporation
 */

#घोषणा pr_fmt(fmt)	"brcmstb: " KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/soc/brcmstb/brcmstb.h>

#घोषणा RACENPREF_MASK			0x3
#घोषणा RACPREFINST_SHIFT		0
#घोषणा RACENINST_SHIFT			2
#घोषणा RACPREFDATA_SHIFT		4
#घोषणा RACENDATA_SHIFT			6
#घोषणा RAC_CPU_SHIFT			8
#घोषणा RACCFG_MASK			0xff
#घोषणा DPREF_LINE_2_SHIFT		24
#घोषणा DPREF_LINE_2_MASK		0xff

/* Biपंचांगask to enable inकाष्ठाion and data prefetching with a 256-bytes stride */
#घोषणा RAC_DATA_INST_EN_MASK		(1 << RACPREFINST_SHIFT | \
					 RACENPREF_MASK << RACENINST_SHIFT | \
					 1 << RACPREFDATA_SHIFT | \
					 RACENPREF_MASK << RACENDATA_SHIFT)

#घोषणा  CPU_CREDIT_REG_MCPx_WR_PAIRING_EN_MASK	0x70000000
#घोषणा CPU_CREDIT_REG_MCPx_READ_CRED_MASK	0xf
#घोषणा CPU_CREDIT_REG_MCPx_WRITE_CRED_MASK	0xf
#घोषणा CPU_CREDIT_REG_MCPx_READ_CRED_SHIFT(x)	((x) * 8)
#घोषणा CPU_CREDIT_REG_MCPx_WRITE_CRED_SHIFT(x)	(((x) * 8) + 4)

#घोषणा CPU_MCP_FLOW_REG_MCPx_RDBUFF_CRED_SHIFT(x)	((x) * 8)
#घोषणा CPU_MCP_FLOW_REG_MCPx_RDBUFF_CRED_MASK		0xff

#घोषणा CPU_WRITEBACK_CTRL_REG_WB_THROTTLE_THRESHOLD_MASK	0xf
#घोषणा CPU_WRITEBACK_CTRL_REG_WB_THROTTLE_TIMEOUT_MASK		0xf
#घोषणा CPU_WRITEBACK_CTRL_REG_WB_THROTTLE_TIMEOUT_SHIFT	4
#घोषणा CPU_WRITEBACK_CTRL_REG_WB_THROTTLE_ENABLE		BIT(8)

अटल व्योम __iomem *cpubiuctrl_base;
अटल bool mcp_wr_pairing_en;
अटल स्थिर पूर्णांक *cpubiuctrl_regs;

क्रमागत cpubiuctrl_regs अणु
	CPU_CREDIT_REG = 0,
	CPU_MCP_FLOW_REG,
	CPU_WRITEBACK_CTRL_REG,
	RAC_CONFIG0_REG,
	RAC_CONFIG1_REG,
	NUM_CPU_BIUCTRL_REGS,
पूर्ण;

अटल अंतरभूत u32 cbc_पढ़ोl(पूर्णांक reg)
अणु
	पूर्णांक offset = cpubiuctrl_regs[reg];

	अगर (offset == -1 ||
	    (IS_ENABLED(CONFIG_CACHE_B15_RAC) && reg >= RAC_CONFIG0_REG))
		वापस (u32)-1;

	वापस पढ़ोl_relaxed(cpubiuctrl_base + offset);
पूर्ण

अटल अंतरभूत व्योम cbc_ग_लिखोl(u32 val, पूर्णांक reg)
अणु
	पूर्णांक offset = cpubiuctrl_regs[reg];

	अगर (offset == -1 ||
	    (IS_ENABLED(CONFIG_CACHE_B15_RAC) && reg >= RAC_CONFIG0_REG))
		वापस;

	ग_लिखोl(val, cpubiuctrl_base + offset);
पूर्ण

अटल स्थिर पूर्णांक b15_cpubiuctrl_regs[] = अणु
	[CPU_CREDIT_REG] = 0x184,
	[CPU_MCP_FLOW_REG] = -1,
	[CPU_WRITEBACK_CTRL_REG] = -1,
	[RAC_CONFIG0_REG] = -1,
	[RAC_CONFIG1_REG] = -1,
पूर्ण;

/* Odd हालs, e.g: 7260A0 */
अटल स्थिर पूर्णांक b53_cpubiuctrl_no_wb_regs[] = अणु
	[CPU_CREDIT_REG] = 0x0b0,
	[CPU_MCP_FLOW_REG] = 0x0b4,
	[CPU_WRITEBACK_CTRL_REG] = -1,
	[RAC_CONFIG0_REG] = 0x78,
	[RAC_CONFIG1_REG] = 0x7c,
पूर्ण;

अटल स्थिर पूर्णांक b53_cpubiuctrl_regs[] = अणु
	[CPU_CREDIT_REG] = 0x0b0,
	[CPU_MCP_FLOW_REG] = 0x0b4,
	[CPU_WRITEBACK_CTRL_REG] = 0x22c,
	[RAC_CONFIG0_REG] = 0x78,
	[RAC_CONFIG1_REG] = 0x7c,
पूर्ण;

अटल स्थिर पूर्णांक a72_cpubiuctrl_regs[] = अणु
	[CPU_CREDIT_REG] = 0x18,
	[CPU_MCP_FLOW_REG] = 0x1c,
	[CPU_WRITEBACK_CTRL_REG] = 0x20,
	[RAC_CONFIG0_REG] = 0x08,
	[RAC_CONFIG1_REG] = 0x0c,
पूर्ण;

अटल पूर्णांक __init mcp_ग_लिखो_pairing_set(व्योम)
अणु
	u32 creds = 0;

	अगर (!cpubiuctrl_base)
		वापस -1;

	creds = cbc_पढ़ोl(CPU_CREDIT_REG);
	अगर (mcp_wr_pairing_en) अणु
		pr_info("MCP: Enabling write pairing\n");
		cbc_ग_लिखोl(creds | CPU_CREDIT_REG_MCPx_WR_PAIRING_EN_MASK,
			   CPU_CREDIT_REG);
	पूर्ण अन्यथा अगर (creds & CPU_CREDIT_REG_MCPx_WR_PAIRING_EN_MASK) अणु
		pr_info("MCP: Disabling write pairing\n");
		cbc_ग_लिखोl(creds & ~CPU_CREDIT_REG_MCPx_WR_PAIRING_EN_MASK,
			   CPU_CREDIT_REG);
	पूर्ण अन्यथा अणु
		pr_info("MCP: Write pairing already disabled\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर u32 a72_b53_mach_compat[] = अणु
	0x7211,
	0x7216,
	0x72164,
	0x72165,
	0x7255,
	0x7260,
	0x7268,
	0x7271,
	0x7278,
पूर्ण;

/* The पढ़ो-ahead cache present in the Brahma-B53 CPU is a special piece of
 * hardware after the पूर्णांकegrated L2 cache of the B53 CPU complex whose purpose
 * is to prefetch inकाष्ठाion and/or data with a line size of either 64 bytes
 * or 256 bytes. The rationale is that the data-bus of the CPU पूर्णांकerface is
 * optimized क्रम 256-byte transactions, and enabling the पढ़ो-ahead cache
 * provides a signअगरicant perक्रमmance boost (typically twice the perक्रमmance
 * क्रम a स_नकल benchmark application).
 *
 * The पढ़ो-ahead cache is transparent क्रम Virtual Address cache मुख्यtenance
 * operations: IC IVAU, DC IVAC, DC CVAC, DC CVAU and DC CIVAC.  So no special
 * handling is needed क्रम the DMA API above and beyond what is included in the
 * arm64 implementation.
 *
 * In addition, since the Poपूर्णांक of Unअगरication is typically between L1 and L2
 * क्रम the Brahma-B53 processor no special पढ़ो-ahead cache handling is needed
 * क्रम the IC IALLU and IC IALLUIS cache मुख्यtenance operations.
 *
 * However, it is not possible to specअगरy the cache level (L3) क्रम the cache
 * मुख्यtenance inकाष्ठाions operating by set/way to operate on the पढ़ो-ahead
 * cache.  The पढ़ो-ahead cache will मुख्यtain coherency when inner cache lines
 * are cleaned by set/way, but अगर it is necessary to invalidate inner cache
 * lines by set/way to मुख्यtain coherency with प्रणाली masters operating on
 * shared memory that करोes not have hardware support क्रम coherency, then it
 * will also be necessary to explicitly invalidate the पढ़ो-ahead cache.
 */
अटल व्योम __init a72_b53_rac_enable_all(काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक cpu;
	u32 enable = 0, pref_dist, shअगरt;

	अगर (IS_ENABLED(CONFIG_CACHE_B15_RAC))
		वापस;

	अगर (WARN(num_possible_cpus() > 4, "RAC only supports 4 CPUs\n"))
		वापस;

	pref_dist = cbc_पढ़ोl(RAC_CONFIG1_REG);
	क्रम_each_possible_cpu(cpu) अणु
		shअगरt = cpu * RAC_CPU_SHIFT + RACPREFDATA_SHIFT;
		enable |= RAC_DATA_INST_EN_MASK << (cpu * RAC_CPU_SHIFT);
		अगर (cpubiuctrl_regs == a72_cpubiuctrl_regs) अणु
			enable &= ~(RACENPREF_MASK << shअगरt);
			enable |= 3 << shअगरt;
			pref_dist |= 1 << (cpu + DPREF_LINE_2_SHIFT);
		पूर्ण
	पूर्ण

	cbc_ग_लिखोl(enable, RAC_CONFIG0_REG);
	cbc_ग_लिखोl(pref_dist, RAC_CONFIG1_REG);

	pr_info("%pOF: Broadcom %s read-ahead cache\n",
		np, cpubiuctrl_regs == a72_cpubiuctrl_regs ?
		"Cortex-A72" : "Brahma-B53");
पूर्ण

अटल व्योम __init mcp_a72_b53_set(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	u32 reg;

	reg = brcmstb_get_family_id();

	क्रम (i = 0; i < ARRAY_SIZE(a72_b53_mach_compat); i++) अणु
		अगर (BRCM_ID(reg) == a72_b53_mach_compat[i])
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(a72_b53_mach_compat))
		वापस;

	/* Set all 3 MCP पूर्णांकerfaces to 8 credits */
	reg = cbc_पढ़ोl(CPU_CREDIT_REG);
	क्रम (i = 0; i < 3; i++) अणु
		reg &= ~(CPU_CREDIT_REG_MCPx_WRITE_CRED_MASK <<
			 CPU_CREDIT_REG_MCPx_WRITE_CRED_SHIFT(i));
		reg &= ~(CPU_CREDIT_REG_MCPx_READ_CRED_MASK <<
			 CPU_CREDIT_REG_MCPx_READ_CRED_SHIFT(i));
		reg |= 8 << CPU_CREDIT_REG_MCPx_WRITE_CRED_SHIFT(i);
		reg |= 8 << CPU_CREDIT_REG_MCPx_READ_CRED_SHIFT(i);
	पूर्ण
	cbc_ग_लिखोl(reg, CPU_CREDIT_REG);

	/* Max out the number of in-flight Jwords पढ़ोs on the MCP पूर्णांकerface */
	reg = cbc_पढ़ोl(CPU_MCP_FLOW_REG);
	क्रम (i = 0; i < 3; i++)
		reg |= CPU_MCP_FLOW_REG_MCPx_RDBUFF_CRED_MASK <<
			CPU_MCP_FLOW_REG_MCPx_RDBUFF_CRED_SHIFT(i);
	cbc_ग_लिखोl(reg, CPU_MCP_FLOW_REG);

	/* Enable ग_लिखोback throttling, set समयout to 128 cycles, 256 cycles
	 * threshold
	 */
	reg = cbc_पढ़ोl(CPU_WRITEBACK_CTRL_REG);
	reg |= CPU_WRITEBACK_CTRL_REG_WB_THROTTLE_ENABLE;
	reg &= ~CPU_WRITEBACK_CTRL_REG_WB_THROTTLE_THRESHOLD_MASK;
	reg &= ~(CPU_WRITEBACK_CTRL_REG_WB_THROTTLE_TIMEOUT_MASK <<
		 CPU_WRITEBACK_CTRL_REG_WB_THROTTLE_TIMEOUT_SHIFT);
	reg |= 8;
	reg |= 7 << CPU_WRITEBACK_CTRL_REG_WB_THROTTLE_TIMEOUT_SHIFT;
	cbc_ग_लिखोl(reg, CPU_WRITEBACK_CTRL_REG);
पूर्ण

अटल पूर्णांक __init setup_hअगरcpubiuctrl_regs(काष्ठा device_node *np)
अणु
	काष्ठा device_node *cpu_dn;
	u32 family_id;
	पूर्णांक ret = 0;

	cpubiuctrl_base = of_iomap(np, 0);
	अगर (!cpubiuctrl_base) अणु
		pr_err("failed to remap BIU control base\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mcp_wr_pairing_en = of_property_पढ़ो_bool(np, "brcm,write-pairing");

	cpu_dn = of_get_cpu_node(0, शून्य);
	अगर (!cpu_dn) अणु
		pr_err("failed to obtain CPU device node\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (of_device_is_compatible(cpu_dn, "brcm,brahma-b15"))
		cpubiuctrl_regs = b15_cpubiuctrl_regs;
	अन्यथा अगर (of_device_is_compatible(cpu_dn, "brcm,brahma-b53"))
		cpubiuctrl_regs = b53_cpubiuctrl_regs;
	अन्यथा अगर (of_device_is_compatible(cpu_dn, "arm,cortex-a72"))
		cpubiuctrl_regs = a72_cpubiuctrl_regs;
	अन्यथा अणु
		pr_err("unsupported CPU\n");
		ret = -EINVAL;
	पूर्ण
	of_node_put(cpu_dn);

	family_id = brcmstb_get_family_id();
	अगर (BRCM_ID(family_id) == 0x7260 && BRCM_REV(family_id) == 0)
		cpubiuctrl_regs = b53_cpubiuctrl_no_wb_regs;
out:
	of_node_put(np);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल u32 cpubiuctrl_reg_save[NUM_CPU_BIUCTRL_REGS];

अटल पूर्णांक brcmstb_cpu_credit_reg_suspend(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!cpubiuctrl_base)
		वापस 0;

	क्रम (i = 0; i < NUM_CPU_BIUCTRL_REGS; i++)
		cpubiuctrl_reg_save[i] = cbc_पढ़ोl(i);

	वापस 0;
पूर्ण

अटल व्योम brcmstb_cpu_credit_reg_resume(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!cpubiuctrl_base)
		वापस;

	क्रम (i = 0; i < NUM_CPU_BIUCTRL_REGS; i++)
		cbc_ग_लिखोl(cpubiuctrl_reg_save[i], i);
पूर्ण

अटल काष्ठा syscore_ops brcmstb_cpu_credit_syscore_ops = अणु
	.suspend = brcmstb_cpu_credit_reg_suspend,
	.resume = brcmstb_cpu_credit_reg_resume,
पूर्ण;
#पूर्ण_अगर


अटल पूर्णांक __init brcmstb_biuctrl_init(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret;

	/* We might be running on a multi-platक्रमm kernel, करोn't make this a
	 * fatal error, just bail out early
	 */
	np = of_find_compatible_node(शून्य, शून्य, "brcm,brcmstb-cpu-biu-ctrl");
	अगर (!np)
		वापस 0;

	ret = setup_hअगरcpubiuctrl_regs(np);
	अगर (ret)
		वापस ret;

	ret = mcp_ग_लिखो_pairing_set();
	अगर (ret) अणु
		pr_err("MCP: Unable to disable write pairing!\n");
		वापस ret;
	पूर्ण

	a72_b53_rac_enable_all(np);
	mcp_a72_b53_set();
#अगर_घोषित CONFIG_PM_SLEEP
	रेजिस्टर_syscore_ops(&brcmstb_cpu_credit_syscore_ops);
#पूर्ण_अगर
	वापस 0;
पूर्ण
early_initcall(brcmstb_biuctrl_init);
