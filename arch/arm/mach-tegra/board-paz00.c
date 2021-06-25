<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-tegra/board-paz00.c
 *
 * Copyright (C) 2011 Marc Dietrich <marvin24@gmx.de>
 *
 * Based on board-harmony.c
 * Copyright (C) 2010 Google, Inc.
 */

#समावेश <linux/property.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "board.h"

अटल काष्ठा property_entry wअगरi_rfसमाप्त_prop[] __initdata = अणु
	PROPERTY_ENTRY_STRING("name", "wifi_rfkill"),
	PROPERTY_ENTRY_STRING("type", "wlan"),
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device wअगरi_rfसमाप्त_device = अणु
	.name	= "rfkill_gpio",
	.id	= -1,
पूर्ण;

अटल काष्ठा gpiod_lookup_table wअगरi_gpio_lookup = अणु
	.dev_id = "rfkill_gpio",
	.table = अणु
		GPIO_LOOKUP("tegra-gpio", 25, "reset", 0),
		GPIO_LOOKUP("tegra-gpio", 85, "shutdown", 0),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

व्योम __init tegra_paz00_wअगरiसमाप्त_init(व्योम)
अणु
	platक्रमm_device_add_properties(&wअगरi_rfसमाप्त_device, wअगरi_rfसमाप्त_prop);
	gpiod_add_lookup_table(&wअगरi_gpio_lookup);
	platक्रमm_device_रेजिस्टर(&wअगरi_rfसमाप्त_device);
पूर्ण
