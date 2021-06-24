<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Roy Zang <tie-fei.zang@मुक्तscale.com>
 *
 * Description:
 * Old U-boot compatibility क्रम mpc7448hpc2 board
 * Based on the code of Scott Wood <scottwood@मुक्तscale.com>
 * क्रम 83xx and 85xx.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "cuboot.h"

#घोषणा TARGET_HAS_ETH1
#समावेश "ppcboot.h"

अटल bd_t bd;
बाह्य अक्षर _dtb_start[], _dtb_end[];

अटल व्योम platक्रमm_fixups(व्योम)
अणु
	व्योम *tsi;

	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	dt_fixup_mac_addresses(bd.bi_enetaddr, bd.bi_enet1addr);
	dt_fixup_cpu_घड़ीs(bd.bi_पूर्णांकfreq, bd.bi_busfreq / 4, bd.bi_busfreq);
	tsi = find_node_by_devtype(शून्य, "tsi-bridge");
	अगर (tsi)
		setprop(tsi, "bus-frequency", &bd.bi_busfreq,
			माप(bd.bi_busfreq));
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	fdt_init(_dtb_start);
	serial_console_init();
	platक्रमm_ops.fixups = platक्रमm_fixups;
पूर्ण
