<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sysfs.h - MediaLB sysfs inक्रमmation
 *
 * Copyright (C) 2015, Microchip Technology Germany II GmbH & Co. KG
 */

/* Author: Andrey Shvetsov <andrey.shvetsov@k2l.de> */

#अगर_अघोषित DIM2_SYSFS_H
#घोषणा	DIM2_SYSFS_H

#समावेश <linux/kobject.h>

काष्ठा medialb_bus अणु
	काष्ठा kobject kobj_group;
पूर्ण;

काष्ठा device;

पूर्णांक dim2_sysfs_probe(काष्ठा device *dev);
व्योम dim2_sysfs_destroy(काष्ठा device *dev);

/*
 * callback,
 * must deliver MediaLB state as true अगर locked or false अगर unlocked
 */
bool dim2_sysfs_get_state_cb(व्योम);

#पूर्ण_अगर	/* DIM2_SYSFS_H */
