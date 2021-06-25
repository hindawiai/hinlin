<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/compiler.h>

अचिन्हित दीर्घ दीर्घ notrace __bswapdi2(अचिन्हित दीर्घ दीर्घ u)
अणु
	वापस (((u) & 0xff00000000000000ull) >> 56) |
	       (((u) & 0x00ff000000000000ull) >> 40) |
	       (((u) & 0x0000ff0000000000ull) >> 24) |
	       (((u) & 0x000000ff00000000ull) >>  8) |
	       (((u) & 0x00000000ff000000ull) <<  8) |
	       (((u) & 0x0000000000ff0000ull) << 24) |
	       (((u) & 0x000000000000ff00ull) << 40) |
	       (((u) & 0x00000000000000ffull) << 56);
पूर्ण

EXPORT_SYMBOL(__bswapdi2);
