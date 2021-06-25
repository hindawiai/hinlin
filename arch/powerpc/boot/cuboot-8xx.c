<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम 8xx
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "cuboot.h"

#घोषणा TARGET_8xx
#घोषणा TARGET_HAS_ETH1
#समावेश "ppcboot.h"

अटल bd_t bd;

अटल व्योम platक्रमm_fixups(व्योम)
अणु
	व्योम *node;

	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	dt_fixup_mac_addresses(bd.bi_enetaddr, bd.bi_enet1addr);
	dt_fixup_cpu_घड़ीs(bd.bi_पूर्णांकfreq, bd.bi_busfreq / 16, bd.bi_busfreq);

	node = finddevice("/soc/cpm");
	अगर (node)
		setprop(node, "clock-frequency", &bd.bi_busfreq, 4);

	node = finddevice("/soc/cpm/brg");
	अगर (node)
		setprop(node, "clock-frequency",  &bd.bi_busfreq, 4);
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
                   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	fdt_init(_dtb_start);
	serial_console_init();
	platक्रमm_ops.fixups = platक्रमm_fixups;
पूर्ण
