<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>

#समावेश "drbd_int.h"

#अगर_घोषित CONFIG_DEBUG_FS
व्योम __init drbd_debugfs_init(व्योम);
व्योम drbd_debugfs_cleanup(व्योम);

व्योम drbd_debugfs_resource_add(काष्ठा drbd_resource *resource);
व्योम drbd_debugfs_resource_cleanup(काष्ठा drbd_resource *resource);

व्योम drbd_debugfs_connection_add(काष्ठा drbd_connection *connection);
व्योम drbd_debugfs_connection_cleanup(काष्ठा drbd_connection *connection);

व्योम drbd_debugfs_device_add(काष्ठा drbd_device *device);
व्योम drbd_debugfs_device_cleanup(काष्ठा drbd_device *device);

व्योम drbd_debugfs_peer_device_add(काष्ठा drbd_peer_device *peer_device);
व्योम drbd_debugfs_peer_device_cleanup(काष्ठा drbd_peer_device *peer_device);
#अन्यथा

अटल अंतरभूत व्योम __init drbd_debugfs_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम drbd_debugfs_cleanup(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम drbd_debugfs_resource_add(काष्ठा drbd_resource *resource) अणु पूर्ण
अटल अंतरभूत व्योम drbd_debugfs_resource_cleanup(काष्ठा drbd_resource *resource) अणु पूर्ण

अटल अंतरभूत व्योम drbd_debugfs_connection_add(काष्ठा drbd_connection *connection) अणु पूर्ण
अटल अंतरभूत व्योम drbd_debugfs_connection_cleanup(काष्ठा drbd_connection *connection) अणु पूर्ण

अटल अंतरभूत व्योम drbd_debugfs_device_add(काष्ठा drbd_device *device) अणु पूर्ण
अटल अंतरभूत व्योम drbd_debugfs_device_cleanup(काष्ठा drbd_device *device) अणु पूर्ण

अटल अंतरभूत व्योम drbd_debugfs_peer_device_add(काष्ठा drbd_peer_device *peer_device) अणु पूर्ण
अटल अंतरभूत व्योम drbd_debugfs_peer_device_cleanup(काष्ठा drbd_peer_device *peer_device) अणु पूर्ण

#पूर्ण_अगर
