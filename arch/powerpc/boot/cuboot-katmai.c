<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम Kaपंचांगai
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
#समावेश "reg.h"
#समावेश "dcr.h"
#समावेश "4xx.h"
#समावेश "44x.h"
#समावेश "cuboot.h"

#घोषणा TARGET_4xx
#घोषणा TARGET_44x
#समावेश "ppcboot.h"

अटल bd_t bd;

BSS_STACK(4096);

अटल व्योम kaपंचांगai_fixups(व्योम)
अणु
	अचिन्हित दीर्घ sysclk = 33333000;

	/* 440SP Clock logic is all but identical to 440GX
	 * so we just use that code क्रम now at least
	 */
	ibm440spe_fixup_घड़ीs(sysclk, 6 * 1843200, 0);

	ibm440spe_fixup_memsize();

	dt_fixup_mac_address(0, bd.bi_enetaddr);

	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();

	platक्रमm_ops.fixups = kaपंचांगai_fixups;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
