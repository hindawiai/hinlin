<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम MPC5200
 *
 * Author: Grant Likely <grant.likely@secretlab.ca>
 *
 * Copyright (c) 2007 Secret Lab Technologies Ltd.
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "io.h"
#समावेश "cuboot.h"

#घोषणा TARGET_PPC_MPC52xx
#समावेश "ppcboot.h"

अटल bd_t bd;

अटल व्योम platक्रमm_fixups(व्योम)
अणु
	व्योम *soc, *reg;
	पूर्णांक भाग;
	u32 sysfreq;


	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	dt_fixup_mac_addresses(bd.bi_enetaddr);
	dt_fixup_cpu_घड़ीs(bd.bi_पूर्णांकfreq, bd.bi_busfreq / 4, bd.bi_busfreq);

	/* Unक्रमtunately, the specअगरic model number is encoded in the
	 * soc node name in existing dts files -- once that is fixed,
	 * this can करो a simple path lookup.
	 */
	soc = find_node_by_devtype(शून्य, "soc");
	अगर (!soc)
		soc = find_node_by_compatible(शून्य, "fsl,mpc5200-immr");
	अगर (!soc)
		soc = find_node_by_compatible(शून्य, "fsl,mpc5200b-immr");
	अगर (soc) अणु
		setprop(soc, "bus-frequency", &bd.bi_ipbfreq,
			माप(bd.bi_ipbfreq));

		अगर (!dt_xlate_reg(soc, 0, (व्योम*)&reg, शून्य))
			वापस;
		भाग = in_8(reg + 0x204) & 0x0020 ? 8 : 4;
		sysfreq = bd.bi_busfreq * भाग;
		setprop(soc, "system-frequency", &sysfreq, माप(sysfreq));
	पूर्ण
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
                   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	fdt_init(_dtb_start);
	serial_console_init();
	platक्रमm_ops.fixups = platक्रमm_fixups;
पूर्ण
