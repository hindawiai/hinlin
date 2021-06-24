<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Old U-boot compatibility क्रम Ebony
 *
 * Author: David Gibson <david@gibson.dropbear.id.au>
 *
 * Copyright 2007 David Gibson, IBM Corporatio.
 *   Based on cuboot-83xx.c, which is:
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 */

#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "44x.h"

BSS_STACK(4096);

#घोषणा OPENBIOS_MAC_BASE	0xfffffe0c
#घोषणा OPENBIOS_MAC_OFFSET	0xc

व्योम platक्रमm_init(व्योम)
अणु
	अचिन्हित दीर्घ end_of_ram = 0x8000000;
	अचिन्हित दीर्घ avail_ram = end_of_ram - (अचिन्हित दीर्घ)_end;

	simple_alloc_init(_end, avail_ram, 32, 64);
	ebony_init((u8 *)OPENBIOS_MAC_BASE,
		   (u8 *)(OPENBIOS_MAC_BASE + OPENBIOS_MAC_OFFSET));
पूर्ण
