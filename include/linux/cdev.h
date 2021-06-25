<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CDEV_H
#घोषणा _LINUX_CDEV_H

#समावेश <linux/kobject.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/list.h>
#समावेश <linux/device.h>

काष्ठा file_operations;
काष्ठा inode;
काष्ठा module;

काष्ठा cdev अणु
	काष्ठा kobject kobj;
	काष्ठा module *owner;
	स्थिर काष्ठा file_operations *ops;
	काष्ठा list_head list;
	dev_t dev;
	अचिन्हित पूर्णांक count;
पूर्ण __अक्रमomize_layout;

व्योम cdev_init(काष्ठा cdev *, स्थिर काष्ठा file_operations *);

काष्ठा cdev *cdev_alloc(व्योम);

व्योम cdev_put(काष्ठा cdev *p);

पूर्णांक cdev_add(काष्ठा cdev *, dev_t, अचिन्हित);

व्योम cdev_set_parent(काष्ठा cdev *p, काष्ठा kobject *kobj);
पूर्णांक cdev_device_add(काष्ठा cdev *cdev, काष्ठा device *dev);
व्योम cdev_device_del(काष्ठा cdev *cdev, काष्ठा device *dev);

व्योम cdev_del(काष्ठा cdev *);

व्योम cd_क्रमget(काष्ठा inode *);

#पूर्ण_अगर
