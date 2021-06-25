<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम Sequoia
 *
 * Valentine Barshak <vbarshak@ru.mvista.com>
 * Copyright 2007 MontaVista Software, Inc
 *
 * Based on Ebony code by David Gibson <david@gibson.dropbear.id.au>
 * Copyright IBM Corporation, 2007
 *
 * Based on Bamboo code by Josh Boyer <jwboyer@linux.vnet.ibm.com>
 * Copyright IBM Corporation, 2007
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
#समावेश "cuboot.h"

#घोषणा TARGET_4xx
#घोषणा TARGET_44x
#समावेश "ppcboot.h"

अटल bd_t bd;


अटल व्योम sequoia_fixups(व्योम)
अणु
	अचिन्हित दीर्घ sysclk = 33333333;

	ibm440ep_fixup_घड़ीs(sysclk, 11059200, 50000000);
	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
	ibm4xx_denali_fixup_memsize();
	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
	dt_fixup_mac_address_by_alias("ethernet1", bd.bi_enet1addr);
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
                   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	platक्रमm_ops.fixups = sequoia_fixups;
	platक्रमm_ops.निकास = ibm44x_dbcr_reset;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
