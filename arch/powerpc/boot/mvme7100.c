<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Motload compatibility क्रम the Emerson/Artesyn MVME7100
 *
 * Copyright 2016 Elettra-Sincrotrone Trieste S.C.p.A.
 *
 * Author: Alessio Igor Bogani <alessio.bogani@elettra.eu>
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "cuboot.h"

#घोषणा TARGET_86xx
#घोषणा TARGET_HAS_ETH1
#घोषणा TARGET_HAS_ETH2
#घोषणा TARGET_HAS_ETH3
#समावेश "ppcboot.h"

अटल bd_t bd;

BSS_STACK(16384);

अटल व्योम mvme7100_fixups(व्योम)
अणु
	व्योम *devp;
	अचिन्हित दीर्घ busfreq = bd.bi_busfreq * 1000000;

	dt_fixup_cpu_घड़ीs(bd.bi_पूर्णांकfreq * 1000000, busfreq / 4, busfreq);

	devp = finddevice("/soc@f1000000");
	अगर (devp)
		setprop(devp, "bus-frequency", &busfreq, माप(busfreq));

	devp = finddevice("/soc/serial@4500");
	अगर (devp)
		setprop(devp, "clock-frequency", &busfreq, माप(busfreq));

	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);

	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
	dt_fixup_mac_address_by_alias("ethernet1", bd.bi_enet1addr);
	dt_fixup_mac_address_by_alias("ethernet2", bd.bi_enet2addr);
	dt_fixup_mac_address_by_alias("ethernet3", bd.bi_enet3addr);
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	fdt_init(_dtb_start);
	serial_console_init();
	platक्रमm_ops.fixups = mvme7100_fixups;
पूर्ण
