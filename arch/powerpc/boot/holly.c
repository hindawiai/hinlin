<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2007 IBM Corporation
 *
 * Stephen Winiecki <stevewin@us.ibm.com>
 * Josh Boyer <jwboyer@linux.vnet.ibm.com>
 *
 * Based on earlier code:
 * Copyright (C) Paul Mackerras 1997.
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "elf.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "page.h"
#समावेश "ops.h"
#समावेश "io.h"

BSS_STACK(4096);

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5)
अणु
	u32 heapsize = 0x8000000 - (u32)_end; /* 128M */

	simple_alloc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
