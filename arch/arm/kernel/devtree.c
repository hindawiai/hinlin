<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/devtree.c
 *
 *  Copyright (C) 2009 Canonical Ltd. <jeremy.kerr@canonical.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach-types.h>


#अगर_घोषित CONFIG_SMP
बाह्य काष्ठा of_cpu_method __cpu_method_of_table[];

अटल स्थिर काष्ठा of_cpu_method __cpu_method_of_table_sentinel
	__used __section("__cpu_method_of_table_end");


अटल पूर्णांक __init set_smp_ops_by_method(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *method;
	काष्ठा of_cpu_method *m = __cpu_method_of_table;

	अगर (of_property_पढ़ो_string(node, "enable-method", &method))
		वापस 0;

	क्रम (; m->method; m++)
		अगर (!म_भेद(m->method, method)) अणु
			smp_set_ops(m->ops);
			वापस 1;
		पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक set_smp_ops_by_method(काष्ठा device_node *node)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर


/*
 * arm_dt_init_cpu_maps - Function retrieves cpu nodes from the device tree
 * and builds the cpu logical map array containing MPIDR values related to
 * logical cpus
 *
 * Updates the cpu possible mask with the number of parsed cpu nodes
 */
व्योम __init arm_dt_init_cpu_maps(व्योम)
अणु
	/*
	 * Temp logical map is initialized with अच_पूर्णांक_उच्च values that are
	 * considered invalid logical map entries since the logical map must
	 * contain a list of MPIDR[23:0] values where MPIDR[31:24] must
	 * पढ़ो as 0.
	 */
	काष्ठा device_node *cpu, *cpus;
	पूर्णांक found_method = 0;
	u32 i, j, cpuidx = 1;
	u32 mpidr = is_smp() ? पढ़ो_cpuid_mpidr() & MPIDR_HWID_BITMASK : 0;

	u32 पंचांगp_map[NR_CPUS] = अणु [0 ... NR_CPUS-1] = MPIDR_INVALID पूर्ण;
	bool bootcpu_valid = false;
	cpus = of_find_node_by_path("/cpus");

	अगर (!cpus)
		वापस;

	क्रम_each_of_cpu_node(cpu) अणु
		स्थिर __be32 *cell;
		पूर्णांक prop_bytes;
		u32 hwid;

		pr_debug(" * %pOF...\n", cpu);
		/*
		 * A device tree containing CPU nodes with missing "reg"
		 * properties is considered invalid to build the
		 * cpu_logical_map.
		 */
		cell = of_get_property(cpu, "reg", &prop_bytes);
		अगर (!cell || prop_bytes < माप(*cell)) अणु
			pr_debug(" * %pOF missing reg property\n", cpu);
			of_node_put(cpu);
			वापस;
		पूर्ण

		/*
		 * Bits n:24 must be set to 0 in the DT since the reg property
		 * defines the MPIDR[23:0].
		 */
		करो अणु
			hwid = be32_to_cpu(*cell++);
			prop_bytes -= माप(*cell);
		पूर्ण जबतक (!hwid && prop_bytes > 0);

		अगर (prop_bytes || (hwid & ~MPIDR_HWID_BITMASK)) अणु
			of_node_put(cpu);
			वापस;
		पूर्ण

		/*
		 * Duplicate MPIDRs are a recipe क्रम disaster.
		 * Scan all initialized entries and check क्रम
		 * duplicates. If any is found just bail out.
		 * temp values were initialized to अच_पूर्णांक_उच्च
		 * to aव्योम matching valid MPIDR[23:0] values.
		 */
		क्रम (j = 0; j < cpuidx; j++)
			अगर (WARN(पंचांगp_map[j] == hwid,
				 "Duplicate /cpu reg properties in the DT\n")) अणु
				of_node_put(cpu);
				वापस;
			पूर्ण

		/*
		 * Build a stashed array of MPIDR values. Numbering scheme
		 * requires that अगर detected the boot CPU must be asचिन्हित
		 * logical id 0. Other CPUs get sequential indexes starting
		 * from 1. If a CPU node with a reg property matching the
		 * boot CPU MPIDR is detected, this is recorded so that the
		 * logical map built from DT is validated and can be used
		 * to override the map created in smp_setup_processor_id().
		 */
		अगर (hwid == mpidr) अणु
			i = 0;
			bootcpu_valid = true;
		पूर्ण अन्यथा अणु
			i = cpuidx++;
		पूर्ण

		अगर (WARN(cpuidx > nr_cpu_ids, "DT /cpu %u nodes greater than "
					       "max cores %u, capping them\n",
					       cpuidx, nr_cpu_ids)) अणु
			cpuidx = nr_cpu_ids;
			of_node_put(cpu);
			अवरोध;
		पूर्ण

		पंचांगp_map[i] = hwid;

		अगर (!found_method)
			found_method = set_smp_ops_by_method(cpu);
	पूर्ण

	/*
	 * Fallback to an enable-method in the cpus node अगर nothing found in
	 * a cpu node.
	 */
	अगर (!found_method)
		set_smp_ops_by_method(cpus);

	अगर (!bootcpu_valid) अणु
		pr_warn("DT missing boot CPU MPIDR[23:0], fall back to default cpu_logical_map\n");
		वापस;
	पूर्ण

	/*
	 * Since the boot CPU node contains proper data, and all nodes have
	 * a reg property, the DT CPU list can be considered valid and the
	 * logical map created in smp_setup_processor_id() can be overridden
	 */
	क्रम (i = 0; i < cpuidx; i++) अणु
		set_cpu_possible(i, true);
		cpu_logical_map(i) = पंचांगp_map[i];
		pr_debug("cpu logical map 0x%x\n", cpu_logical_map(i));
	पूर्ण
पूर्ण

bool arch_match_cpu_phys_id(पूर्णांक cpu, u64 phys_id)
अणु
	वापस phys_id == cpu_logical_map(cpu);
पूर्ण

अटल स्थिर व्योम * __init arch_get_next_mach(स्थिर अक्षर *स्थिर **match)
अणु
	अटल स्थिर काष्ठा machine_desc *mdesc = __arch_info_begin;
	स्थिर काष्ठा machine_desc *m = mdesc;

	अगर (m >= __arch_info_end)
		वापस शून्य;

	mdesc++;
	*match = m->dt_compat;
	वापस m;
पूर्ण

/**
 * setup_machine_fdt - Machine setup when an dtb was passed to the kernel
 * @dt_virt: भव address of dt blob
 *
 * If a dtb was passed to the kernel in r2, then use it to choose the
 * correct machine_desc and to setup the प्रणाली.
 */
स्थिर काष्ठा machine_desc * __init setup_machine_fdt(व्योम *dt_virt)
अणु
	स्थिर काष्ठा machine_desc *mdesc, *mdesc_best = शून्य;

#अगर defined(CONFIG_ARCH_MULTIPLATFORM) || defined(CONFIG_ARM_SINGLE_ARMV7M)
	DT_MACHINE_START(GENERIC_DT, "Generic DT based system")
		.l2c_aux_val = 0x0,
		.l2c_aux_mask = ~0x0,
	MACHINE_END

	mdesc_best = &__mach_desc_GENERIC_DT;
#पूर्ण_अगर

	अगर (!dt_virt || !early_init_dt_verअगरy(dt_virt))
		वापस शून्य;

	mdesc = of_flat_dt_match_machine(mdesc_best, arch_get_next_mach);

	अगर (!mdesc) अणु
		स्थिर अक्षर *prop;
		पूर्णांक size;
		अचिन्हित दीर्घ dt_root;

		early_prपूर्णांक("\nError: unrecognized/unsupported "
			    "device tree compatible list:\n[ ");

		dt_root = of_get_flat_dt_root();
		prop = of_get_flat_dt_prop(dt_root, "compatible", &size);
		जबतक (size > 0) अणु
			early_prपूर्णांक("'%s' ", prop);
			size -= म_माप(prop) + 1;
			prop += म_माप(prop) + 1;
		पूर्ण
		early_prपूर्णांक("]\n\n");

		dump_machine_table(); /* करोes not वापस */
	पूर्ण

	/* We really करोn't want to करो this, but someबार firmware provides buggy data */
	अगर (mdesc->dt_fixup)
		mdesc->dt_fixup();

	early_init_dt_scan_nodes();

	/* Change machine number to match the mdesc we're using */
	__machine_arch_type = mdesc->nr;

	वापस mdesc;
पूर्ण
