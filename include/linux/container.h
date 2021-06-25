<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम container bus type.
 *
 * Copyright (C) 2013, Intel Corporation
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#अगर_अघोषित _LINUX_CONTAINER_H
#घोषणा _LINUX_CONTAINER_H

#समावेश <linux/device.h>

/* drivers/base/घातer/container.c */
बाह्य काष्ठा bus_type container_subsys;

काष्ठा container_dev अणु
	काष्ठा device dev;
	पूर्णांक (*offline)(काष्ठा container_dev *cdev);
पूर्ण;

अटल अंतरभूत काष्ठा container_dev *to_container_dev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा container_dev, dev);
पूर्ण

#पूर्ण_अगर /* _LINUX_CONTAINER_H */
