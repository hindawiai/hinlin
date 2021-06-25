<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Marvell Armada AP and CP110 helper
 *
 * Copyright (C) 2018 Marvell
 *
 * Gregory Clement <gregory.clement@bootlin.com>
 *
 */

#समावेश "armada_ap_cp_helper.h"
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

अक्षर *ap_cp_unique_name(काष्ठा device *dev, काष्ठा device_node *np,
			स्थिर अक्षर *name)
अणु
	स्थिर __be32 *reg;
	u64 addr;

	/* Do not create a name अगर there is no घड़ी */
	अगर (!name)
		वापस शून्य;

	reg = of_get_property(np, "reg", शून्य);
	addr = of_translate_address(np, reg);
	वापस devm_kaप्र_लिखो(dev, GFP_KERNEL, "%llx-%s",
			      (अचिन्हित दीर्घ दीर्घ)addr, name);
पूर्ण
