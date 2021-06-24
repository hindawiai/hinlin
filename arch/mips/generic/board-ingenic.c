<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम Ingenic SoCs
 *
 * Copyright (C) 2009-2010, Lars-Peter Clausen <lars@metafoo.de>
 * Copyright (C) 2011, Maarten ter Huurne <maarten@treewalker.org>
 * Copyright (C) 2020 Paul Cercueil <paul@crapouillou.net>
 */

#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/pm.h>
#समावेश <linux/sizes.h>
#समावेश <linux/suspend.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/machine.h>
#समावेश <यंत्र/reboot.h>

अटल __init अक्षर *ingenic_get_प्रणाली_type(अचिन्हित दीर्घ machtype)
अणु
	चयन (machtype) अणु
	हाल MACH_INGENIC_X2000E:
		वापस "X2000E";
	हाल MACH_INGENIC_X2000:
		वापस "X2000";
	हाल MACH_INGENIC_X1830:
		वापस "X1830";
	हाल MACH_INGENIC_X1000E:
		वापस "X1000E";
	हाल MACH_INGENIC_X1000:
		वापस "X1000";
	हाल MACH_INGENIC_JZ4780:
		वापस "JZ4780";
	हाल MACH_INGENIC_JZ4775:
		वापस "JZ4775";
	हाल MACH_INGENIC_JZ4770:
		वापस "JZ4770";
	हाल MACH_INGENIC_JZ4725B:
		वापस "JZ4725B";
	शेष:
		वापस "JZ4740";
	पूर्ण
पूर्ण

अटल __init स्थिर व्योम *ingenic_fixup_fdt(स्थिर व्योम *fdt, स्थिर व्योम *match_data)
अणु
	/*
	 * Old devicetree files क्रम the qi,lb60 board did not have a /memory
	 * node. Hardcode the memory info here.
	 */
	अगर (!fdt_node_check_compatible(fdt, 0, "qi,lb60") &&
	    fdt_path_offset(fdt, "/memory") < 0)
		early_init_dt_add_memory_arch(0, SZ_32M);

	mips_machtype = (अचिन्हित दीर्घ)match_data;
	प्रणाली_type = ingenic_get_प्रणाली_type(mips_machtype);

	वापस fdt;
पूर्ण

अटल स्थिर काष्ठा of_device_id ingenic_of_match[] __initस्थिर = अणु
	अणु .compatible = "ingenic,jz4740", .data = (व्योम *)MACH_INGENIC_JZ4740 पूर्ण,
	अणु .compatible = "ingenic,jz4725b", .data = (व्योम *)MACH_INGENIC_JZ4725B पूर्ण,
	अणु .compatible = "ingenic,jz4770", .data = (व्योम *)MACH_INGENIC_JZ4770 पूर्ण,
	अणु .compatible = "ingenic,jz4775", .data = (व्योम *)MACH_INGENIC_JZ4775 पूर्ण,
	अणु .compatible = "ingenic,jz4780", .data = (व्योम *)MACH_INGENIC_JZ4780 पूर्ण,
	अणु .compatible = "ingenic,x1000", .data = (व्योम *)MACH_INGENIC_X1000 पूर्ण,
	अणु .compatible = "ingenic,x1000e", .data = (व्योम *)MACH_INGENIC_X1000E पूर्ण,
	अणु .compatible = "ingenic,x1830", .data = (व्योम *)MACH_INGENIC_X1830 पूर्ण,
	अणु .compatible = "ingenic,x2000", .data = (व्योम *)MACH_INGENIC_X2000 पूर्ण,
	अणु .compatible = "ingenic,x2000e", .data = (व्योम *)MACH_INGENIC_X2000E पूर्ण,
	अणुपूर्ण
पूर्ण;

MIPS_MACHINE(ingenic) = अणु
	.matches = ingenic_of_match,
	.fixup_fdt = ingenic_fixup_fdt,
पूर्ण;

अटल व्योम ingenic_रुको_instr(व्योम)
अणु
	__यंत्र__(".set push;\n"
		".set mips3;\n"
		"wait;\n"
		".set pop;\n"
	);
पूर्ण

अटल व्योम ingenic_halt(व्योम)
अणु
	क्रम (;;)
		ingenic_रुको_instr();
पूर्ण

अटल पूर्णांक __maybe_unused ingenic_pm_enter(suspend_state_t state)
अणु
	ingenic_रुको_instr();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops ingenic_pm_ops __maybe_unused = अणु
	.valid = suspend_valid_only_mem,
	.enter = ingenic_pm_enter,
पूर्ण;

अटल पूर्णांक __init ingenic_pm_init(व्योम)
अणु
	अगर (boot_cpu_type() == CPU_XBURST) अणु
		अगर (IS_ENABLED(CONFIG_PM_SLEEP))
			suspend_set_ops(&ingenic_pm_ops);
		_machine_halt = ingenic_halt;
	पूर्ण

	वापस 0;

पूर्ण
late_initcall(ingenic_pm_init);
