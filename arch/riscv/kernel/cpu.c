<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/smp.h>

/*
 * Returns the hart ID of the given device tree node, or -ENODEV अगर the node
 * isn't an enabled and valid RISC-V hart node.
 */
पूर्णांक riscv_of_processor_hartid(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *isa;
	u32 hart;

	अगर (!of_device_is_compatible(node, "riscv")) अणु
		pr_warn("Found incompatible CPU\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "reg", &hart)) अणु
		pr_warn("Found CPU without hart ID\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!of_device_is_available(node)) अणु
		pr_info("CPU with hartid=%d is not available\n", hart);
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_string(node, "riscv,isa", &isa)) अणु
		pr_warn("CPU with hartid=%d has no \"riscv,isa\" property\n", hart);
		वापस -ENODEV;
	पूर्ण
	अगर (isa[0] != 'r' || isa[1] != 'v') अणु
		pr_warn("CPU with hartid=%d has an invalid ISA of \"%s\"\n", hart, isa);
		वापस -ENODEV;
	पूर्ण

	वापस hart;
पूर्ण

/*
 * Find hart ID of the CPU DT node under which given DT node falls.
 *
 * To achieve this, we walk up the DT tree until we find an active
 * RISC-V core (HART) node and extract the cpuid from it.
 */
पूर्णांक riscv_of_parent_hartid(काष्ठा device_node *node)
अणु
	क्रम (; node; node = node->parent) अणु
		अगर (of_device_is_compatible(node, "riscv"))
			वापस riscv_of_processor_hartid(node);
	पूर्ण

	वापस -1;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम prपूर्णांक_isa(काष्ठा seq_file *f, स्थिर अक्षर *isa)
अणु
	/* Prपूर्णांक the entire ISA as it is */
	seq_माला_दो(f, "isa\t\t: ");
	seq_ग_लिखो(f, isa, म_माप(isa));
	seq_माला_दो(f, "\n");
पूर्ण

अटल व्योम prपूर्णांक_mmu(काष्ठा seq_file *f, स्थिर अक्षर *mmu_type)
अणु
#अगर defined(CONFIG_32BIT)
	अगर (म_भेद(mmu_type, "riscv,sv32") != 0)
		वापस;
#या_अगर defined(CONFIG_64BIT)
	अगर (म_भेद(mmu_type, "riscv,sv39") != 0 &&
	    म_भेद(mmu_type, "riscv,sv48") != 0)
		वापस;
#पूर्ण_अगर

	seq_म_लिखो(f, "mmu\t\t: %s\n", mmu_type+6);
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	*pos = cpumask_next(*pos - 1, cpu_online_mask);
	अगर ((*pos) < nr_cpu_ids)
		वापस (व्योम *)(uपूर्णांकptr_t)(1 + *pos);
	वापस शून्य;
पूर्ण

अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस c_start(m, pos);
पूर्ण

अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक c_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित दीर्घ cpu_id = (अचिन्हित दीर्घ)v - 1;
	काष्ठा device_node *node = of_get_cpu_node(cpu_id, शून्य);
	स्थिर अक्षर *compat, *isa, *mmu;

	seq_म_लिखो(m, "processor\t: %lu\n", cpu_id);
	seq_म_लिखो(m, "hart\t\t: %lu\n", cpuid_to_hartid_map(cpu_id));
	अगर (!of_property_पढ़ो_string(node, "riscv,isa", &isa))
		prपूर्णांक_isa(m, isa);
	अगर (!of_property_पढ़ो_string(node, "mmu-type", &mmu))
		prपूर्णांक_mmu(m, mmu);
	अगर (!of_property_पढ़ो_string(node, "compatible", &compat)
	    && म_भेद(compat, "riscv"))
		seq_म_लिखो(m, "uarch\t\t: %s\n", compat);
	seq_माला_दो(m, "\n");
	of_node_put(node);

	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= c_show
पूर्ण;

#पूर्ण_अगर /* CONFIG_PROC_FS */
