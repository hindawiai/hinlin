<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2009 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2010 Joonas Lahtinen <joonas.lahtinen@gmail.com>
 *  Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#समावेश <linux/माला.स>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/addrspace.h>

#समावेश <यंत्र/mach-ralink/ralink_regs.h>

#समावेश "common.h"

काष्ठा ralink_soc_info soc_info;
काष्ठा rt2880_pmx_group *rt2880_pinmux_data = शून्य;

क्रमागत ralink_soc_type ralink_soc;
EXPORT_SYMBOL_GPL(ralink_soc);

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस soc_info.sys_type;
पूर्ण

अटल __init व्योम prom_init_cmdline(व्योम)
अणु
	पूर्णांक argc;
	अक्षर **argv;
	पूर्णांक i;

	pr_debug("prom: fw_arg0=%08x fw_arg1=%08x fw_arg2=%08x fw_arg3=%08x\n",
	       (अचिन्हित पूर्णांक)fw_arg0, (अचिन्हित पूर्णांक)fw_arg1,
	       (अचिन्हित पूर्णांक)fw_arg2, (अचिन्हित पूर्णांक)fw_arg3);

	argc = fw_arg0;
	argv = (अक्षर **) KSEG1ADDR(fw_arg1);

	अगर (!argv) अणु
		pr_debug("argv=%p is invalid, skipping\n",
		       argv);
		वापस;
	पूर्ण

	क्रम (i = 0; i < argc; i++) अणु
		अक्षर *p = (अक्षर *) KSEG1ADDR(argv[i]);

		अगर (CPHYSADDR(p) && *p) अणु
			pr_debug("argv[%d]: %s\n", i, p);
			strlcat(arcs_cmdline, " ", माप(arcs_cmdline));
			strlcat(arcs_cmdline, p, माप(arcs_cmdline));
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	prom_soc_init(&soc_info);

	pr_info("SoC Type: %s\n", get_प्रणाली_type());

	prom_init_cmdline();
पूर्ण
