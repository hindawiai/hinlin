<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */
/*
 * driver क्रम VIA VT1631 LVDS Transmitter
 */

#समावेश <linux/slab.h>
#समावेश "via_aux.h"


अटल स्थिर अक्षर *name = "VT1631 LVDS Transmitter";


व्योम via_aux_vt1631_probe(काष्ठा via_aux_bus *bus)
अणु
	काष्ठा via_aux_drv drv = अणु
		.bus	=	bus,
		.addr	=	0x38,
		.name	=	nameपूर्ण;
	/* check venकरोr id and device id */
	स्थिर u8 id[] = अणु0x06, 0x11, 0x91, 0x31पूर्ण, len = ARRAY_SIZE(id);
	u8 पंचांगp[ARRAY_SIZE(id)];

	अगर (!via_aux_पढ़ो(&drv, 0x00, पंचांगp, len) || स_भेद(id, पंचांगp, len))
		वापस;

	prपूर्णांकk(KERN_INFO "viafb: Found %s\n", name);
	via_aux_add(&drv);
पूर्ण
