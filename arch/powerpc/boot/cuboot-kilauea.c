<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम PPC405EX. This image is alपढ़ोy included
 * a dtb.
 *
 * Author: Tiejun Chen <tiejun.chen@windriver.com>
 *
 * Copyright (C) 2009 Wind River Systems, Inc.
 */

#समावेश "ops.h"
#समावेश "io.h"
#समावेश "dcr.h"
#समावेश "stdio.h"
#समावेश "4xx.h"
#समावेश "44x.h"
#समावेश "cuboot.h"

#घोषणा TARGET_4xx
#घोषणा TARGET_44x
#समावेश "ppcboot.h"

#घोषणा KILAUEA_SYS_EXT_SERIAL_CLOCK     11059200        /* ext. 11.059MHz clk */

अटल bd_t bd;

अटल व्योम kilauea_fixups(व्योम)
अणु
	अचिन्हित दीर्घ sysclk = 33333333;

	ibm405ex_fixup_घड़ीs(sysclk, KILAUEA_SYS_EXT_SERIAL_CLOCK);
	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
	dt_fixup_mac_address_by_alias("ethernet1", bd.bi_enet1addr);
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	platक्रमm_ops.fixups = kilauea_fixups;
	platक्रमm_ops.निकास = ibm40x_dbcr_reset;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
