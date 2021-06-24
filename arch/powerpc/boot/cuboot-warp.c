<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008 PIKA Technologies
 *   Sean MacLennan <smaclennan@pikatech.com>
 */

#समावेश "ops.h"
#समावेश "4xx.h"
#समावेश "cuboot.h"
#समावेश "stdio.h"

#घोषणा TARGET_4xx
#घोषणा TARGET_44x
#समावेश "ppcboot.h"

अटल bd_t bd;

अटल व्योम warp_fixups(व्योम)
अणु
	ibm440ep_fixup_घड़ीs(66000000, 11059200, 50000000);
	ibm4xx_sdram_fixup_memsize();
	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();

	platक्रमm_ops.fixups = warp_fixups;
	platक्रमm_ops.निकास = ibm44x_dbcr_reset;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
