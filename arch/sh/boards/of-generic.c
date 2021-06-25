<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SH generic board support, using device tree
 *
 * Copyright (C) 2015-2016 Smart Energy Instruments, Inc.
 */

#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/irqchip.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/rtc.h>

#अगर_घोषित CONFIG_SMP

अटल व्योम dummy_smp_setup(व्योम)
अणु
पूर्ण

अटल व्योम dummy_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
पूर्ण

अटल व्योम dummy_start_cpu(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ entry_poपूर्णांक)
अणु
पूर्ण

अटल अचिन्हित पूर्णांक dummy_smp_processor_id(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम dummy_send_ipi(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक message)
अणु
पूर्ण

अटल काष्ठा plat_smp_ops dummy_smp_ops = अणु
	.smp_setup		= dummy_smp_setup,
	.prepare_cpus		= dummy_prepare_cpus,
	.start_cpu		= dummy_start_cpu,
	.smp_processor_id	= dummy_smp_processor_id,
	.send_ipi		= dummy_send_ipi,
	.cpu_die		= native_cpu_die,
	.cpu_disable		= native_cpu_disable,
	.play_dead		= native_play_dead,
पूर्ण;

बाह्य स्थिर काष्ठा of_cpu_method __cpu_method_of_table[];
स्थिर काष्ठा of_cpu_method __cpu_method_of_table_sentinel
	__section("__cpu_method_of_table_end");

अटल व्योम sh_of_smp_probe(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर अक्षर *method = शून्य;
	स्थिर काष्ठा of_cpu_method *m = __cpu_method_of_table;

	pr_info("SH generic board support: scanning for cpus\n");

	init_cpu_possible(cpumask_of(0));

	क्रम_each_of_cpu_node(np) अणु
		स्थिर __be32 *cell = of_get_property(np, "reg", शून्य);
		u64 id = -1;
		अगर (cell) id = of_पढ़ो_number(cell, of_n_addr_cells(np));
		अगर (id < NR_CPUS) अणु
			अगर (!method)
				of_property_पढ़ो_string(np, "enable-method", &method);
			set_cpu_possible(id, true);
			set_cpu_present(id, true);
			__cpu_number_map[id] = id;
			__cpu_logical_map[id] = id;
		पूर्ण
	पूर्ण
	अगर (!method) अणु
		np = of_find_node_by_name(शून्य, "cpus");
		of_property_पढ़ो_string(np, "enable-method", &method);
		of_node_put(np);
	पूर्ण

	pr_info("CPU enable method: %s\n", method);
	अगर (method)
		क्रम (; m->method; m++)
			अगर (!म_भेद(m->method, method)) अणु
				रेजिस्टर_smp_ops(m->ops);
				वापस;
			पूर्ण

	रेजिस्टर_smp_ops(&dummy_smp_ops);
पूर्ण

#अन्यथा

अटल व्योम sh_of_smp_probe(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल व्योम noop(व्योम)
अणु
पूर्ण

अटल पूर्णांक noopi(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __init sh_of_mem_reserve(व्योम)
अणु
	early_init_fdt_reserve_self();
	early_init_fdt_scan_reserved_mem();
पूर्ण

अटल व्योम __init sh_of_setup(अक्षर **cmdline_p)
अणु
	काष्ठा device_node *root;

	sh_mv.mv_name = "Unknown SH model";
	root = of_find_node_by_path("/");
	अगर (root) अणु
		of_property_पढ़ो_string(root, "model", &sh_mv.mv_name);
		of_node_put(root);
	पूर्ण

	sh_of_smp_probe();
पूर्ण

अटल पूर्णांक sh_of_irq_demux(पूर्णांक irq)
अणु
	/* FIXME: eventually this should not be used at all;
	 * the पूर्णांकerrupt controller should set_handle_irq(). */
	वापस irq;
पूर्ण

अटल व्योम __init sh_of_init_irq(व्योम)
अणु
	pr_info("SH generic board support: scanning for interrupt controllers\n");
	irqchip_init();
पूर्ण

अटल पूर्णांक __init sh_of_clk_init(व्योम)
अणु
#अगर_घोषित CONFIG_COMMON_CLK
	/* Disabled pending move to COMMON_CLK framework. */
	pr_info("SH generic board support: scanning for clk providers\n");
	of_clk_init(शून्य);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल काष्ठा sh_machine_vector __iniपंचांगv sh_of_generic_mv = अणु
	.mv_setup	= sh_of_setup,
	.mv_name	= "devicetree", /* replaced by DT root's model */
	.mv_irq_demux	= sh_of_irq_demux,
	.mv_init_irq	= sh_of_init_irq,
	.mv_clk_init	= sh_of_clk_init,
	.mv_mode_pins	= noopi,
	.mv_mem_init	= noop,
	.mv_mem_reserve	= sh_of_mem_reserve,
पूर्ण;

काष्ठा sh_clk_ops;

व्योम __init __weak arch_init_clk_ops(काष्ठा sh_clk_ops **ops, पूर्णांक idx)
अणु
पूर्ण

व्योम __init __weak plat_irq_setup(व्योम)
अणु
पूर्ण
