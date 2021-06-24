<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RedBoot firmware support
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 * Copyright (c) 2008 Codehermit
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "redboot.h"
#समावेश "fsl-soc.h"
#समावेश "io.h"

अटल bd_t bd;
BSS_STACK(4096);

#घोषणा MHZ(x)	((x + 500000) / 1000000)

अटल व्योम platक्रमm_fixups(व्योम)
अणु
	व्योम *node;

	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	dt_fixup_mac_addresses(bd.bi_enetaddr);
	dt_fixup_cpu_घड़ीs(bd.bi_पूर्णांकfreq, bd.bi_busfreq / 16, bd.bi_busfreq);

	node = finddevice("/soc/cpm/brg");
	अगर (node) अणु
		म_लिखो("BRG clock-frequency <- 0x%x (%dMHz)\r\n",
		       bd.bi_busfreq, MHZ(bd.bi_busfreq));
		setprop(node, "clock-frequency",  &bd.bi_busfreq, 4);
	पूर्ण

पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	स_नकल(&bd, (अक्षर *)r3, माप(bd));

	अगर (bd.bi_tag != 0x42444944)
		वापस;

	simple_alloc_init(_end,
			  bd.bi_memstart + bd.bi_memsize - (अचिन्हित दीर्घ)_end,
			  32, 64);

	fdt_init(_dtb_start);
	serial_console_init();
	platक्रमm_ops.fixups = platक्रमm_fixups;

	loader_info.cmdline = (अक्षर *)bd.bi_cmdline;
	loader_info.cmdline_len = म_माप((अक्षर *)bd.bi_cmdline);
पूर्ण
