<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Registration of Cobalt LED platक्रमm device.
 *
 *  Copyright (C) 2007	Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <cobalt.h>

अटल काष्ठा resource cobalt_led_resource __initdata = अणु
	.start	= 0x1c000000,
	.end	= 0x1c000000,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल __init पूर्णांक cobalt_led_add(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक retval;

	अगर (cobalt_board_id == COBALT_BRD_ID_QUBE1 ||
	    cobalt_board_id == COBALT_BRD_ID_QUBE2)
		pdev = platक्रमm_device_alloc("cobalt-qube-leds", -1);
	अन्यथा
		pdev = platक्रमm_device_alloc("cobalt-raq-leds", -1);

	अगर (!pdev)
		वापस -ENOMEM;

	retval = platक्रमm_device_add_resources(pdev, &cobalt_led_resource, 1);
	अगर (retval)
		जाओ err_मुक्त_device;

	retval = platक्रमm_device_add(pdev);
	अगर (retval)
		जाओ err_मुक्त_device;

	वापस 0;

err_मुक्त_device:
	platक्रमm_device_put(pdev);

	वापस retval;
पूर्ण
device_initcall(cobalt_led_add);
