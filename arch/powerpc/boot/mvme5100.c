<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Motorola/Emerson MVME5100 with PPCBug firmware.
 *
 * Author: Stephen Chivers <schivers@csc.com>
 *
 * Copyright 2013 CSC Australia Pty. Ltd.
 */
#समावेश "types.h"
#समावेश "ops.h"
#समावेश "io.h"

BSS_STACK(4096);

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5)
अणु
	u32			heapsize;

	heapsize = 0x8000000 - (u32)_end; /* 128M */
	simple_alloc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_start);
	serial_console_init();
पूर्ण
