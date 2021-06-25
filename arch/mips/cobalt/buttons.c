<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Cobalt buttons platक्रमm device.
 *
 *  Copyright (C) 2007  Yoichi Yuasa <yuasa@linux-mips.org>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>

अटल काष्ठा resource cobalt_buttons_resource __initdata = अणु
	.start	= 0x1d000000,
	.end	= 0x1d000003,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल __init पूर्णांक cobalt_add_buttons(व्योम)
अणु
	काष्ठा platक्रमm_device *pd;
	पूर्णांक error;

	pd = platक्रमm_device_alloc("Cobalt buttons", -1);
	अगर (!pd)
		वापस -ENOMEM;

	error = platक्रमm_device_add_resources(pd, &cobalt_buttons_resource, 1);
	अगर (error)
		जाओ err_मुक्त_device;

	error = platक्रमm_device_add(pd);
	अगर (error)
		जाओ err_मुक्त_device;

	वापस 0;

 err_मुक्त_device:
	platक्रमm_device_put(pd);
	वापस error;
पूर्ण
device_initcall(cobalt_add_buttons);
