<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Compatibility क्रम old (not device tree aware) U-Boot versions
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 * Consolidated using macros by David Gibson <david@gibson.dropbear.id.au>
 *
 * Copyright 2007 David Gibson, IBM Corporation.
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"

#समावेश "ppcboot.h"

व्योम cuboot_init(अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5,
		 अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7,
		 अचिन्हित दीर्घ end_of_ram)
अणु
	अचिन्हित दीर्घ avail_ram = end_of_ram - (अचिन्हित दीर्घ)_end;

	loader_info.initrd_addr = r4;
	loader_info.initrd_size = r4 ? r5 - r4 : 0;
	loader_info.cmdline = (अक्षर *)r6;
	loader_info.cmdline_len = r7 - r6;

	simple_alloc_init(_end, avail_ram - 1024*1024, 32, 64);
पूर्ण
