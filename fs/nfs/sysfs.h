<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 Hammerspace Inc
 */

#अगर_अघोषित __NFS_SYSFS_H
#घोषणा __NFS_SYSFS_H

#घोषणा CONTAINER_ID_MAXLEN (64)

काष्ठा nfs_netns_client अणु
	काष्ठा kobject kobject;
	काष्ठा net *net;
	स्थिर अक्षर __rcu *identअगरier;
पूर्ण;

बाह्य काष्ठा kobject *nfs_client_kobj;

बाह्य पूर्णांक nfs_sysfs_init(व्योम);
बाह्य व्योम nfs_sysfs_निकास(व्योम);

व्योम nfs_netns_sysfs_setup(काष्ठा nfs_net *netns, काष्ठा net *net);
व्योम nfs_netns_sysfs_destroy(काष्ठा nfs_net *netns);

#पूर्ण_अगर
