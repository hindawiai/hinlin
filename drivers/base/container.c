<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System bus type क्रम containers.
 *
 * Copyright (C) 2013, Intel Corporation
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश <linux/container.h>

#समावेश "base.h"

#घोषणा CONTAINER_BUS_NAME	"container"

अटल पूर्णांक trivial_online(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक container_offline(काष्ठा device *dev)
अणु
	काष्ठा container_dev *cdev = to_container_dev(dev);

	वापस cdev->offline ? cdev->offline(cdev) : 0;
पूर्ण

काष्ठा bus_type container_subsys = अणु
	.name = CONTAINER_BUS_NAME,
	.dev_name = CONTAINER_BUS_NAME,
	.online = trivial_online,
	.offline = container_offline,
पूर्ण;

व्योम __init container_dev_init(व्योम)
अणु
	पूर्णांक ret;

	ret = subsys_प्रणाली_रेजिस्टर(&container_subsys, शून्य);
	अगर (ret)
		pr_err("%s() failed: %d\n", __func__, ret);
पूर्ण
