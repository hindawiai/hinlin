<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/compiler.h>

अचिन्हित पूर्णांक notrace __bswapsi2(अचिन्हित पूर्णांक u)
अणु
	वापस (((u) & 0xff000000) >> 24) |
	       (((u) & 0x00ff0000) >>  8) |
	       (((u) & 0x0000ff00) <<  8) |
	       (((u) & 0x000000ff) << 24);
पूर्ण

EXPORT_SYMBOL(__bswapsi2);
