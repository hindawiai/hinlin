<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम Sam440ep based off bamboo.c code
 * original copyrights below
 *
 * Author: Josh Boyer <jwboyer@linux.vnet.ibm.com>
 *
 * Copyright 2007 IBM Corporation
 *
 * Based on cuboot-ebony.c
 *
 * Modअगरied from cuboot-bamboo.c क्रम sam440ep:
 * Copyright 2008 Giuseppe Coviello <gicoviello@gmail.com>
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "44x.h"
#समावेश "4xx.h"
#समावेश "cuboot.h"

#घोषणा TARGET_4xx
#घोषणा TARGET_44x
#समावेश "ppcboot.h"

अटल bd_t bd;

अटल व्योम sam440ep_fixups(व्योम)
अणु
       अचिन्हित दीर्घ sysclk = 66666666;

       ibm440ep_fixup_घड़ीs(sysclk, 11059200, 25000000);
       ibm4xx_sdram_fixup_memsize();
       ibm4xx_quiesce_eth((u32 *)0xef600e00, (u32 *)0xef600f00);
       dt_fixup_mac_addresses(&bd.bi_enetaddr, &bd.bi_enet1addr);
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	platक्रमm_ops.fixups = sam440ep_fixups;
	platक्रमm_ops.निकास = ibm44x_dbcr_reset;
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
