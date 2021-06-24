<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Based on reduced version of METAG
 */


#समावेश <linux/init.h>
#समावेश <linux/reboot.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <यंत्र/mach_desc.h>

#अगर_घोषित CONFIG_SERIAL_EARLYCON

अटल अचिन्हित पूर्णांक __initdata arc_base_baud;

अचिन्हित पूर्णांक __init arc_early_base_baud(व्योम)
अणु
	वापस arc_base_baud/16;
पूर्ण

अटल व्योम __init arc_set_early_base_baud(अचिन्हित दीर्घ dt_root)
अणु
	अगर (of_flat_dt_is_compatible(dt_root, "abilis,arc-tb10x"))
		arc_base_baud = 166666666;	/* Fixed 166.6MHz clk (TB10x) */
	अन्यथा अगर (of_flat_dt_is_compatible(dt_root, "snps,arc-sdp") ||
		 of_flat_dt_is_compatible(dt_root, "snps,hsdk"))
		arc_base_baud = 33333333;	/* Fixed 33MHz clk (AXS10x & HSDK) */
	अन्यथा
		arc_base_baud = 50000000;	/* Fixed शेष 50MHz */
पूर्ण
#अन्यथा
#घोषणा arc_set_early_base_baud(dt_root)
#पूर्ण_अगर

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
 * @dt:		भव address poपूर्णांकer to dt blob
 *
 * If a dtb was passed to the kernel, then use it to choose the correct
 * machine_desc and to setup the प्रणाली.
 */
स्थिर काष्ठा machine_desc * __init setup_machine_fdt(व्योम *dt)
अणु
	स्थिर काष्ठा machine_desc *mdesc;
	अचिन्हित दीर्घ dt_root;

	अगर (!early_init_dt_scan(dt))
		वापस शून्य;

	mdesc = of_flat_dt_match_machine(शून्य, arch_get_next_mach);
	अगर (!mdesc)
		machine_halt();

	dt_root = of_get_flat_dt_root();
	arc_set_early_base_baud(dt_root);

	वापस mdesc;
पूर्ण
