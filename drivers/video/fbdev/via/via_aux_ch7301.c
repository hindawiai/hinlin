<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */
/*
 * driver क्रम Chrontel CH7301 DVI Transmitter
 */

#समावेश <linux/slab.h>
#समावेश "via_aux.h"


अटल स्थिर अक्षर *name = "CH7301 DVI Transmitter";


अटल व्योम probe(काष्ठा via_aux_bus *bus, u8 addr)
अणु
	काष्ठा via_aux_drv drv = अणु
		.bus	=	bus,
		.addr	=	addr,
		.name	=	nameपूर्ण;
	u8 पंचांगp;

	अगर (!via_aux_पढ़ो(&drv, 0x4B, &पंचांगp, 1) || पंचांगp != 0x17)
		वापस;

	prपूर्णांकk(KERN_INFO "viafb: Found %s at address 0x%x\n", name, addr);
	via_aux_add(&drv);
पूर्ण

व्योम via_aux_ch7301_probe(काष्ठा via_aux_bus *bus)
अणु
	probe(bus, 0x75);
	probe(bus, 0x76);
पूर्ण
