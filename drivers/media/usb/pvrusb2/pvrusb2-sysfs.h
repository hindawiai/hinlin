<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_SYSFS_H
#घोषणा __PVRUSB2_SYSFS_H

#समावेश <linux/list.h>
#समावेश <linux/sysfs.h>
#समावेश "pvrusb2-context.h"

काष्ठा pvr2_sysfs;
काष्ठा pvr2_sysfs_class;

काष्ठा pvr2_sysfs_class *pvr2_sysfs_class_create(व्योम);
व्योम pvr2_sysfs_class_destroy(काष्ठा pvr2_sysfs_class *);

काष्ठा pvr2_sysfs *pvr2_sysfs_create(काष्ठा pvr2_context *,
				     काष्ठा pvr2_sysfs_class *);

#पूर्ण_अगर /* __PVRUSB2_SYSFS_H */
