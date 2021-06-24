<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */
/*
 * infraकाष्ठाure क्रम devices connected via I2C
 */

#समावेश <linux/slab.h>
#समावेश "via_aux.h"


काष्ठा via_aux_bus *via_aux_probe(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा via_aux_bus *bus;

	अगर (!adap)
		वापस शून्य;

	bus = kदो_स्मृति(माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस शून्य;

	bus->adap = adap;
	INIT_LIST_HEAD(&bus->drivers);

	via_aux_edid_probe(bus);
	via_aux_vt1636_probe(bus);
	via_aux_vt1632_probe(bus);
	via_aux_vt1631_probe(bus);
	via_aux_vt1625_probe(bus);
	via_aux_vt1622_probe(bus);
	via_aux_vt1621_probe(bus);
	via_aux_sii164_probe(bus);
	via_aux_ch7301_probe(bus);

	वापस bus;
पूर्ण

व्योम via_aux_मुक्त(काष्ठा via_aux_bus *bus)
अणु
	काष्ठा via_aux_drv *pos, *n;

	अगर (!bus)
		वापस;

	list_क्रम_each_entry_safe(pos, n, &bus->drivers, chain) अणु
		अगर (pos->cleanup)
			pos->cleanup(pos);

		list_del(&pos->chain);
		kमुक्त(pos->data);
		kमुक्त(pos);
	पूर्ण

	kमुक्त(bus);
पूर्ण

स्थिर काष्ठा fb_videomode *via_aux_get_preferred_mode(काष्ठा via_aux_bus *bus)
अणु
	काष्ठा via_aux_drv *pos;
	स्थिर काष्ठा fb_videomode *mode = शून्य;

	अगर (!bus)
		वापस शून्य;

	list_क्रम_each_entry(pos, &bus->drivers, chain) अणु
		अगर (pos->get_preferred_mode)
			mode = pos->get_preferred_mode(pos);
	पूर्ण

	वापस mode;
पूर्ण
