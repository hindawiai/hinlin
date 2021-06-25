<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * memconsole.c
 *
 * Architecture-independent parts of the memory based BIOS console.
 *
 * Copyright 2017 Google Inc.
 */

#समावेश <linux/sysfs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/module.h>

#समावेश "memconsole.h"

अटल sमाप_प्रकार memconsole_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobp,
			       काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			       loff_t pos, माप_प्रकार count)
अणु
	sमाप_प्रकार (*memconsole_पढ़ो_func)(अक्षर *, loff_t, माप_प्रकार);

	memconsole_पढ़ो_func = bin_attr->निजी;
	अगर (WARN_ON_ONCE(!memconsole_पढ़ो_func))
		वापस -EIO;

	वापस memconsole_पढ़ो_func(buf, pos, count);
पूर्ण

अटल काष्ठा bin_attribute memconsole_bin_attr = अणु
	.attr = अणु.name = "log", .mode = 0444पूर्ण,
	.पढ़ो = memconsole_पढ़ो,
पूर्ण;

व्योम memconsole_setup(sमाप_प्रकार (*पढ़ो_func)(अक्षर *, loff_t, माप_प्रकार))
अणु
	memconsole_bin_attr.निजी = पढ़ो_func;
पूर्ण
EXPORT_SYMBOL(memconsole_setup);

पूर्णांक memconsole_sysfs_init(व्योम)
अणु
	वापस sysfs_create_bin_file(firmware_kobj, &memconsole_bin_attr);
पूर्ण
EXPORT_SYMBOL(memconsole_sysfs_init);

व्योम memconsole_निकास(व्योम)
अणु
	sysfs_हटाओ_bin_file(firmware_kobj, &memconsole_bin_attr);
पूर्ण
EXPORT_SYMBOL(memconsole_निकास);

MODULE_AUTHOR("Google, Inc.");
MODULE_LICENSE("GPL");
