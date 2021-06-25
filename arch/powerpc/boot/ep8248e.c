<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Embedded Planet EP8248E with PlanetCore firmware
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "planetcore.h"
#समावेश "pq2.h"

अटल अक्षर *table;
अटल u64 mem_size;

#समावेश <पन.स>

अटल व्योम platक्रमm_fixups(व्योम)
अणु
	u64 val;

	dt_fixup_memory(0, mem_size);
	planetcore_set_mac_addrs(table);

	अगर (!planetcore_get_decimal(table, PLANETCORE_KEY_CRYSTAL_HZ, &val)) अणु
		म_लिखो("No PlanetCore crystal frequency key.\r\n");
		वापस;
	पूर्ण

	pq2_fixup_घड़ीs(val);
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
                   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	table = (अक्षर *)r3;
	planetcore_prepare_table(table);

	अगर (!planetcore_get_decimal(table, PLANETCORE_KEY_MB_RAM, &mem_size))
		वापस;

	mem_size *= 1024 * 1024;
	simple_alloc_init(_end, mem_size - (अचिन्हित दीर्घ)_end, 32, 64);

	fdt_init(_dtb_start);

	planetcore_set_मानक_निकास_path(table);
	serial_console_init();
	platक्रमm_ops.fixups = platक्रमm_fixups;
पूर्ण
