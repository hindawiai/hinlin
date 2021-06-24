<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sysfs.c - MediaLB sysfs inक्रमmation
 *
 * Copyright (C) 2015, Microchip Technology Germany II GmbH & Co. KG
 */

/* Author: Andrey Shvetsov <andrey.shvetsov@k2l.de> */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश "sysfs.h"
#समावेश <linux/device.h>

अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	bool state = dim2_sysfs_get_state_cb();

	वापस प्र_लिखो(buf, "%s\n", state ? "locked" : "");
पूर्ण

अटल DEVICE_ATTR_RO(state);

अटल काष्ठा attribute *dev_attrs[] = अणु
	&dev_attr_state.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group dev_attr_group = अणु
	.attrs = dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dev_attr_groups[] = अणु
	&dev_attr_group,
	शून्य,
पूर्ण;

पूर्णांक dim2_sysfs_probe(काष्ठा device *dev)
अणु
	dev->groups = dev_attr_groups;
	वापस device_रेजिस्टर(dev);
पूर्ण

व्योम dim2_sysfs_destroy(काष्ठा device *dev)
अणु
	device_unरेजिस्टर(dev);
पूर्ण
