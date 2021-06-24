<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Joshua Henderson, joshua.henderson@microchip.com
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_data/sdhci-pic32.h>

#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/mips-boards/generic.h>
#समावेश <यंत्र/prom.h>

#समावेश "pic32mzda.h"

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "PIC32MZDA";
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	व्योम *dtb;

	dtb = get_fdt();
	अगर (!dtb) अणु
		pr_err("pic32: no DTB found.\n");
		वापस;
	पूर्ण

	/*
	 * Load the builtin device tree. This causes the chosen node to be
	 * parsed resulting in our memory appearing.
	 */
	__dt_setup_arch(dtb);

	pr_info("Found following command lines\n");
	pr_info(" boot_command_line: %s\n", boot_command_line);
	pr_info(" arcs_cmdline     : %s\n", arcs_cmdline);
#अगर_घोषित CONFIG_CMDLINE_BOOL
	pr_info(" builtin_cmdline  : %s\n", CONFIG_CMDLINE);
#पूर्ण_अगर
	अगर (dtb != __dtb_start)
		strlcpy(arcs_cmdline, boot_command_line, COMMAND_LINE_SIZE);

#अगर_घोषित CONFIG_EARLY_PRINTK
	fw_init_early_console(-1);
#पूर्ण_अगर
	pic32_config_init();
पूर्ण

अटल __init व्योम pic32_init_cmdline(पूर्णांक argc, अक्षर *argv[])
अणु
	अचिन्हित पूर्णांक count = COMMAND_LINE_SIZE - 1;
	पूर्णांक i;
	अक्षर *dst = &(arcs_cmdline[0]);
	अक्षर *src;

	क्रम (i = 1; i < argc && count; ++i) अणु
		src = argv[i];
		जबतक (*src && count) अणु
			*dst++ = *src++;
			--count;
		पूर्ण
		*dst++ = ' ';
	पूर्ण
	अगर (i > 1)
		--dst;

	*dst = 0;
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	pic32_init_cmdline((पूर्णांक)fw_arg0, (अक्षर **)fw_arg1);
पूर्ण

व्योम __init device_tree_init(व्योम)
अणु
	अगर (!initial_boot_params)
		वापस;

	unflatten_and_copy_device_tree();
पूर्ण

अटल काष्ठा pic32_sdhci_platक्रमm_data sdhci_data = अणु
	.setup_dma = pic32_set_sdhci_adma_fअगरo_threshold,
पूर्ण;

अटल काष्ठा of_dev_auxdata pic32_auxdata_lookup[] __initdata = अणु
	OF_DEV_AUXDATA("microchip,pic32mzda-sdhci", 0, "sdhci", &sdhci_data),
	अणु /* sentinel */पूर्ण
पूर्ण;

अटल पूर्णांक __init pic32_of_prepare_platक्रमm_data(काष्ठा of_dev_auxdata *lookup)
अणु
	काष्ठा device_node *root, *np;
	काष्ठा resource res;

	root = of_find_node_by_path("/");

	क्रम (; lookup->compatible; lookup++) अणु
		np = of_find_compatible_node(शून्य, शून्य, lookup->compatible);
		अगर (np) अणु
			lookup->name = (अक्षर *)np->name;
			अगर (lookup->phys_addr)
				जारी;
			अगर (!of_address_to_resource(np, 0, &res))
				lookup->phys_addr = res.start;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init plat_of_setup(व्योम)
अणु
	अगर (!of_have_populated_dt())
		panic("Device tree not present");

	pic32_of_prepare_platक्रमm_data(pic32_auxdata_lookup);
	अगर (of_platक्रमm_शेष_populate(शून्य, pic32_auxdata_lookup, शून्य))
		panic("Failed to populate DT");

	वापस 0;
पूर्ण
arch_initcall(plat_of_setup);
