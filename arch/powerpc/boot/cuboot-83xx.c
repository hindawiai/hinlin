<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम 83xx
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "cuboot.h"

#घोषणा TARGET_83xx
#समावेश "ppcboot.h"

अटल bd_t bd;

अटल व्योम platक्रमm_fixups(व्योम)
अणु
	व्योम *soc;

	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
	dt_fixup_mac_address_by_alias("ethernet1", bd.bi_enet1addr);
	dt_fixup_cpu_घड़ीs(bd.bi_पूर्णांकfreq, bd.bi_busfreq / 4, bd.bi_busfreq);

	/* Unक्रमtunately, the specअगरic model number is encoded in the
	 * soc node name in existing dts files -- once that is fixed,
	 * this can करो a simple path lookup.
	 */
	soc = find_node_by_devtype(शून्य, "soc");
	अगर (soc) अणु
		व्योम *serial = शून्य;

		setprop(soc, "bus-frequency", &bd.bi_busfreq,
		        माप(bd.bi_busfreq));

		जबतक ((serial = find_node_by_devtype(serial, "serial"))) अणु
			अगर (get_parent(serial) != soc)
				जारी;

			setprop(serial, "clock-frequency", &bd.bi_busfreq,
			        माप(bd.bi_busfreq));
		पूर्ण
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
