<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The simple platक्रमm -- क्रम booting when firmware करोesn't supply a device
 *                        tree or any platक्रमm configuration inक्रमmation.
 *                        All data is extracted from an embedded device tree
 *                        blob.
 *
 * Authors: Scott Wood <scottwood@मुक्तscale.com>
 *          Grant Likely <grant.likely@secretlab.ca>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 * Copyright (c) 2008 Secret Lab Technologies Ltd.
 */

#समावेश "ops.h"
#समावेश "types.h"
#समावेश "io.h"
#समावेश "stdio.h"
#समावेश <libfdt.h>

BSS_STACK(4*1024);

बाह्य पूर्णांक platक्रमm_specअगरic_init(व्योम) __attribute__((weak));

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	स्थिर u32 *na, *ns, *reg, *समयbase;
	u64 memsize64;
	पूर्णांक node, size, i;

	/* Make sure FDT blob is sane */
	अगर (fdt_check_header(_dtb_start) != 0)
		fatal("Invalid device tree blob\n");

	/* Find the #address-cells and #size-cells properties */
	node = fdt_path_offset(_dtb_start, "/");
	अगर (node < 0)
		fatal("Cannot find root node\n");
	na = fdt_getprop(_dtb_start, node, "#address-cells", &size);
	अगर (!na || (size != 4))
		fatal("Cannot find #address-cells property");
	ns = fdt_getprop(_dtb_start, node, "#size-cells", &size);
	अगर (!ns || (size != 4))
		fatal("Cannot find #size-cells property");

	/* Find the memory range */
	node = fdt_node_offset_by_prop_value(_dtb_start, -1, "device_type",
					     "memory", माप("memory"));
	अगर (node < 0)
		fatal("Cannot find memory node\n");
	reg = fdt_getprop(_dtb_start, node, "reg", &size);
	अगर (size < (*na+*ns) * माप(u32))
		fatal("cannot get memory range\n");

	/* Only पूर्णांकerested in memory based at 0 */
	क्रम (i = 0; i < *na; i++)
		अगर (*reg++ != 0)
			fatal("Memory range is not based at address 0\n");

	/* get the memsize and truncate it to under 4G on 32 bit machines */
	memsize64 = 0;
	क्रम (i = 0; i < *ns; i++)
		memsize64 = (memsize64 << 32) | *reg++;
	अगर (माप(व्योम *) == 4 && memsize64 >= 0x100000000ULL)
		memsize64 = 0xffffffff;

	/* finally, setup the समयbase */
	node = fdt_node_offset_by_prop_value(_dtb_start, -1, "device_type",
					     "cpu", माप("cpu"));
	अगर (!node)
		fatal("Cannot find cpu node\n");
	समयbase = fdt_getprop(_dtb_start, node, "timebase-frequency", &size);
	अगर (समयbase && (size == 4))
		समयbase_period_ns = 1000000000 / *समयbase;

	/* Now we have the memory size; initialize the heap */
	simple_alloc_init(_end, memsize64 - (अचिन्हित दीर्घ)_end, 32, 64);

	/* prepare the device tree and find the console */
	fdt_init(_dtb_start);

	अगर (platक्रमm_specअगरic_init)
		platक्रमm_specअगरic_init();

	serial_console_init();
पूर्ण
