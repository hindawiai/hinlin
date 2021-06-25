<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/boot/gamecube.c
 *
 * Nपूर्णांकenकरो GameCube bootwrapper support
 * Copyright (C) 2004-2009 The GameCube Linux Team
 * Copyright (C) 2008,2009 Albert Herranz
 */

#समावेश <मानकघोष.स>
#समावेश "stdio.h"
#समावेश "types.h"
#समावेश "io.h"
#समावेश "ops.h"

#समावेश "ugecon.h"

BSS_STACK(8192);

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5)
अणु
	u32 heapsize = 16*1024*1024 - (u32)_end;

	simple_alloc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_start);

	अगर (ug_probe())
		console_ops.ग_लिखो = ug_console_ग_लिखो;
पूर्ण

