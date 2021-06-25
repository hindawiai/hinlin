<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * firmware.c - firmware subप्रणाली hoohaw.
 *
 * Copyright (c) 2002-3 Patrick Mochel
 * Copyright (c) 2002-3 Open Source Development Lअसल
 * Copyright (c) 2007 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2007 Novell Inc.
 */
#समावेश <linux/kobject.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>

#समावेश "base.h"

काष्ठा kobject *firmware_kobj;
EXPORT_SYMBOL_GPL(firmware_kobj);

पूर्णांक __init firmware_init(व्योम)
अणु
	firmware_kobj = kobject_create_and_add("firmware", शून्य);
	अगर (!firmware_kobj)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
