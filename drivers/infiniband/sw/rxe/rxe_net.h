<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#अगर_अघोषित RXE_NET_H
#घोषणा RXE_NET_H

#समावेश <net/sock.h>
#समावेश <net/अगर_inet6.h>
#समावेश <linux/module.h>

काष्ठा rxe_recv_sockets अणु
	काष्ठा socket *sk4;
	काष्ठा socket *sk6;
पूर्ण;

पूर्णांक rxe_net_add(स्थिर अक्षर *ibdev_name, काष्ठा net_device *ndev);

पूर्णांक rxe_net_init(व्योम);
व्योम rxe_net_निकास(व्योम);

#पूर्ण_अगर /* RXE_NET_H */
