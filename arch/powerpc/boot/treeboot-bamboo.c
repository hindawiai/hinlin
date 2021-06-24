<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright IBM Corporation, 2007
 * Josh Boyer <jwboyer@linux.vnet.ibm.com>
 *
 * Based on ebony wrapper:
 * Copyright 2007 David Gibson, IBM Corporation.
 */
#समावेश "ops.h"
#समावेश "stdio.h"
#समावेश "44x.h"
#समावेश "stdlib.h"

BSS_STACK(4096);

#घोषणा PIBS_MAC0 0xfffc0400
#घोषणा PIBS_MAC1 0xfffc0500
अक्षर pibs_mac0[6];
अक्षर pibs_mac1[6];

अटल व्योम पढ़ो_pibs_mac(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ mac64;

	mac64 = म_से_अदीर्घl((अक्षर *)PIBS_MAC0, 0, 16);
	स_नकल(&pibs_mac0, (अक्षर *)&mac64+2, 6);

	mac64 = म_से_अदीर्घl((अक्षर *)PIBS_MAC1, 0, 16);
	स_नकल(&pibs_mac1, (अक्षर *)&mac64+2, 6);
पूर्ण

व्योम platक्रमm_init(व्योम)
अणु
	अचिन्हित दीर्घ end_of_ram = 0x8000000;
	अचिन्हित दीर्घ avail_ram = end_of_ram - (अचिन्हित दीर्घ)_end;

	simple_alloc_init(_end, avail_ram, 32, 64);
	पढ़ो_pibs_mac();
	bamboo_init((u8 *)&pibs_mac0, (u8 *)&pibs_mac1);
पूर्ण
