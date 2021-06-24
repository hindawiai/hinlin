<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */
/*
 * driver क्रम VIA VT1621(M) TV Encoder
 */

#समावेश <linux/slab.h>
#समावेश "via_aux.h"


अटल स्थिर अक्षर *name = "VT1621(M) TV Encoder";


व्योम via_aux_vt1621_probe(काष्ठा via_aux_bus *bus)
अणु
	काष्ठा via_aux_drv drv = अणु
		.bus	=	bus,
		.addr	=	0x20,
		.name	=	nameपूर्ण;
	u8 पंचांगp;

	अगर (!via_aux_पढ़ो(&drv, 0x1B, &पंचांगp, 1) || पंचांगp != 0x02)
		वापस;

	prपूर्णांकk(KERN_INFO "viafb: Found %s\n", name);
	via_aux_add(&drv);
पूर्ण
