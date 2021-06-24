<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright IBM Corporation, 2007
 * Josh Boyer <jwboyer@linux.vnet.ibm.com>
 *
 * Based on ebony wrapper:
 * Copyright 2007 David Gibson, IBM Corporation.
 *
 * Clocking code based on code by:
 * Stefan Roese <sr@denx.de>
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "elf.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "page.h"
#समावेश "ops.h"
#समावेश "dcr.h"
#समावेश "4xx.h"
#समावेश "44x.h"

अटल u8 *bamboo_mac0, *bamboo_mac1;

अटल व्योम bamboo_fixups(व्योम)
अणु
	अचिन्हित दीर्घ sysclk = 33333333;

	ibm440ep_fixup_घड़ीs(sysclk, 11059200, 25000000);
	ibm4xx_sdram_fixup_memsize();
	ibm4xx_quiesce_eth((u32 *)0xef600e00, (u32 *)0xef600f00);
	dt_fixup_mac_address_by_alias("ethernet0", bamboo_mac0);
	dt_fixup_mac_address_by_alias("ethernet1", bamboo_mac1);
पूर्ण

व्योम bamboo_init(व्योम *mac0, व्योम *mac1)
अणु
	platक्रमm_ops.fixups = bamboo_fixups;
	platक्रमm_ops.निकास = ibm44x_dbcr_reset;
	bamboo_mac0 = mac0;
	bamboo_mac1 = mac1;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
