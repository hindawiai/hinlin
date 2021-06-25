<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_fdt.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/machine.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/समय.स>

अटल __initस्थिर स्थिर व्योम *fdt;
अटल __initस्थिर स्थिर काष्ठा mips_machine *mach;
अटल __initस्थिर स्थिर व्योम *mach_match_data;

व्योम __init prom_init(व्योम)
अणु
	plat_get_fdt();
	BUG_ON(!fdt);
पूर्ण

व्योम __init *plat_get_fdt(व्योम)
अणु
	स्थिर काष्ठा mips_machine *check_mach;
	स्थिर काष्ठा of_device_id *match;

	अगर (fdt)
		/* Alपढ़ोy set up */
		वापस (व्योम *)fdt;

	fdt = (व्योम *)get_fdt();
	अगर (fdt && !fdt_check_header(fdt)) अणु
		/*
		 * We have been provided with the appropriate device tree क्रम
		 * the board. Make use of it & search क्रम any machine काष्ठा
		 * based upon the root compatible string.
		 */
		क्रम_each_mips_machine(check_mach) अणु
			match = mips_machine_is_compatible(check_mach, fdt);
			अगर (match) अणु
				mach = check_mach;
				mach_match_data = match->data;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_LEGACY_BOARDS)) अणु
		/*
		 * We weren't booted using the UHI boot protocol, but करो
		 * support some number of boards with legacy boot protocols.
		 * Attempt to find the right one.
		 */
		क्रम_each_mips_machine(check_mach) अणु
			अगर (!check_mach->detect)
				जारी;

			अगर (!check_mach->detect())
				जारी;

			mach = check_mach;
		पूर्ण

		/*
		 * If we करोn't recognise the machine then we can't जारी, so
		 * die here.
		 */
		BUG_ON(!mach);

		/* Retrieve the machine's FDT */
		fdt = mach->fdt;
	पूर्ण
	वापस (व्योम *)fdt;
पूर्ण

#अगर_घोषित CONFIG_RELOCATABLE

व्योम __init plat_fdt_relocated(व्योम *new_location)
अणु
	/*
	 * reset fdt as the cached value would poपूर्णांक to the location
	 * beक्रमe relocations happened and update the location argument
	 * अगर it was passed using UHI
	 */
	fdt = शून्य;

	अगर (fw_arg0 == -2)
		fw_arg1 = (अचिन्हित दीर्घ)new_location;
पूर्ण

#पूर्ण_अगर /* CONFIG_RELOCATABLE */

व्योम __init plat_mem_setup(व्योम)
अणु
	अगर (mach && mach->fixup_fdt)
		fdt = mach->fixup_fdt(fdt, mach_match_data);

	fw_init_cmdline();
	__dt_setup_arch((व्योम *)fdt);
पूर्ण

व्योम __init device_tree_init(व्योम)
अणु
	पूर्णांक err;

	unflatten_and_copy_device_tree();
	mips_cpc_probe();

	err = रेजिस्टर_cps_smp_ops();
	अगर (err)
		err = रेजिस्टर_up_smp_ops();
पूर्ण

पूर्णांक __init apply_mips_fdt_fixups(व्योम *fdt_out, माप_प्रकार fdt_out_size,
				 स्थिर व्योम *fdt_in,
				 स्थिर काष्ठा mips_fdt_fixup *fixups)
अणु
	पूर्णांक err;

	err = fdt_खोलो_पूर्णांकo(fdt_in, fdt_out, fdt_out_size);
	अगर (err) अणु
		pr_err("Failed to open FDT\n");
		वापस err;
	पूर्ण

	क्रम (; fixups->apply; fixups++) अणु
		err = fixups->apply(fdt_out);
		अगर (err) अणु
			pr_err("Failed to apply FDT fixup \"%s\"\n",
			       fixups->description);
			वापस err;
		पूर्ण
	पूर्ण

	err = fdt_pack(fdt_out);
	अगर (err)
		pr_err("Failed to pack FDT\n");
	वापस err;
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा clk *clk;

	of_clk_init(शून्य);

	अगर (!cpu_has_counter) अणु
		mips_hpt_frequency = 0;
	पूर्ण अन्यथा अगर (mach && mach->measure_hpt_freq) अणु
		mips_hpt_frequency = mach->measure_hpt_freq();
	पूर्ण अन्यथा अणु
		np = of_get_cpu_node(0, शून्य);
		अगर (!np) अणु
			pr_err("Failed to get CPU node\n");
			वापस;
		पूर्ण

		clk = of_clk_get(np, 0);
		अगर (IS_ERR(clk)) अणु
			pr_err("Failed to get CPU clock: %ld\n", PTR_ERR(clk));
			वापस;
		पूर्ण

		mips_hpt_frequency = clk_get_rate(clk);
		clk_put(clk);

		चयन (boot_cpu_type()) अणु
		हाल CPU_20KC:
		हाल CPU_25KF:
			/* The counter runs at the CPU घड़ी rate */
			अवरोध;
		शेष:
			/* The counter runs at half the CPU घड़ी rate */
			mips_hpt_frequency /= 2;
			अवरोध;
		पूर्ण
	पूर्ण

	समयr_probe();
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	काष्ठा device_node *पूर्णांकc_node;

	पूर्णांकc_node = of_find_compatible_node(शून्य, शून्य,
					    "mti,cpu-interrupt-controller");
	अगर (!cpu_has_veic && !पूर्णांकc_node)
		mips_cpu_irq_init();
	of_node_put(पूर्णांकc_node);

	irqchip_init();
पूर्ण
