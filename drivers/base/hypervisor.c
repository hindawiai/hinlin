<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * hypervisor.c - /sys/hypervisor subप्रणाली.
 *
 * Copyright (C) IBM Corp. 2006
 * Copyright (C) 2007 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (C) 2007 Novell Inc.
 */

#समावेश <linux/kobject.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश "base.h"

काष्ठा kobject *hypervisor_kobj;
EXPORT_SYMBOL_GPL(hypervisor_kobj);

पूर्णांक __init hypervisor_init(व्योम)
अणु
	hypervisor_kobj = kobject_create_and_add("hypervisor", शून्य);
	अगर (!hypervisor_kobj)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
