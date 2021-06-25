<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम Taishan
 *
 * Author: Hugh Blemings <hugh@au.ibm.com>
 *
 * Copyright 2007 Hugh Blemings, IBM Corporation.
 *   Based on cuboot-ebony.c which is:
 * Copyright 2007 David Gibson, IBM Corporation.
 *   Based on cuboot-83xx.c, which is:
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "cuboot.h"
#समावेश "reg.h"
#समावेश "dcr.h"
#समावेश "4xx.h"

#घोषणा TARGET_4xx
#घोषणा TARGET_44x
#घोषणा TARGET_440GX
#समावेश "ppcboot.h"

अटल bd_t bd;

BSS_STACK(4096);

अटल व्योम taishan_fixups(व्योम)
अणु
	/* FIXME: sysclk should be derived by पढ़ोing the FPGA
	   रेजिस्टरs */
	अचिन्हित दीर्घ sysclk = 33000000;

	ibm440gx_fixup_घड़ीs(sysclk, 6 * 1843200, 25000000);

	ibm4xx_sdram_fixup_memsize();

	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
	dt_fixup_mac_address_by_alias("ethernet1", bd.bi_enet1addr);

	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();

	platक्रमm_ops.fixups = taishan_fixups;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
