<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम AmigaOne
 *
 * Author: Gerhard Pircher (gerhard_pircher@gmx.net)
 *
 *   Based on cuboot-83xx.c
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "cuboot.h"

#समावेश "ppcboot.h"

अटल bd_t bd;

अटल व्योम platक्रमm_fixups(व्योम)
अणु
	dt_fixup_memory(bd.bi_memstart, bd.bi_memsize);
	dt_fixup_cpu_घड़ीs(bd.bi_पूर्णांकfreq, bd.bi_busfreq / 4, bd.bi_busfreq);
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
                   अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7)
अणु
	CUBOOT_INIT();
	fdt_init(_dtb_start);
	serial_console_init();
	platक्रमm_ops.fixups = platक्रमm_fixups;
पूर्ण
