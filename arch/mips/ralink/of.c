<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 * Copyright (C) 2008-2009 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/sizes.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/prom.h>

#समावेश "common.h"

__iomem व्योम *rt_sysc_membase;
__iomem व्योम *rt_memc_membase;
EXPORT_SYMBOL_GPL(rt_sysc_membase);

__iomem व्योम *plat_of_remap_node(स्थिर अक्षर *node)
अणु
	काष्ठा resource res;
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, node);
	अगर (!np)
		panic("Failed to find %s node", node);

	अगर (of_address_to_resource(np, 0, &res))
		panic("Failed to get resource for %s", node);

	अगर (!request_mem_region(res.start,
				resource_size(&res),
				res.name))
		panic("Failed to request resources for %s", node);

	वापस ioremap(res.start, resource_size(&res));
पूर्ण

व्योम __init device_tree_init(व्योम)
अणु
	unflatten_and_copy_device_tree();
पूर्ण

अटल पूर्णांक memory_dtb;

अटल पूर्णांक __init early_init_dt_find_memory(अचिन्हित दीर्घ node,
				स्थिर अक्षर *uname, पूर्णांक depth, व्योम *data)
अणु
	अगर (depth == 1 && !म_भेद(uname, "memory@0"))
		memory_dtb = 1;

	वापस 0;
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	व्योम *dtb;

	set_io_port_base(KSEG1);

	/*
	 * Load the builtin devicetree. This causes the chosen node to be
	 * parsed resulting in our memory appearing.
	 */
	dtb = get_fdt();
	__dt_setup_arch(dtb);

	of_scan_flat_dt(early_init_dt_find_memory, शून्य);
	अगर (memory_dtb)
		of_scan_flat_dt(early_init_dt_scan_memory, शून्य);
	अन्यथा अगर (soc_info.mem_detect)
		soc_info.mem_detect();
	अन्यथा अगर (soc_info.mem_size)
		memblock_add(soc_info.mem_base, soc_info.mem_size * SZ_1M);
	अन्यथा
		detect_memory_region(soc_info.mem_base,
				     soc_info.mem_size_min * SZ_1M,
				     soc_info.mem_size_max * SZ_1M);
पूर्ण

अटल पूर्णांक __init plat_of_setup(व्योम)
अणु
	__dt_रेजिस्टर_buses(soc_info.compatible, "palmbus");

	/* make sure that the reset controller is setup early */
	ralink_rst_init();

	वापस 0;
पूर्ण

arch_initcall(plat_of_setup);
