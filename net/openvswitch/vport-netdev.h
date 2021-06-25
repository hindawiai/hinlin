<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2007-2011 Nicira, Inc.
 */

#अगर_अघोषित VPORT_NETDEV_H
#घोषणा VPORT_NETDEV_H 1

#समावेश <linux/netdevice.h>
#समावेश <linux/rcupdate.h>

#समावेश "vport.h"

काष्ठा vport *ovs_netdev_get_vport(काष्ठा net_device *dev);

काष्ठा vport *ovs_netdev_link(काष्ठा vport *vport, स्थिर अक्षर *name);
व्योम ovs_netdev_detach_dev(काष्ठा vport *);

पूर्णांक __init ovs_netdev_init(व्योम);
व्योम ovs_netdev_निकास(व्योम);

व्योम ovs_netdev_tunnel_destroy(काष्ठा vport *vport);
#पूर्ण_अगर /* vport_netdev.h */
