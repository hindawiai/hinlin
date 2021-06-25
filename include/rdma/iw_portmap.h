<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2014 Intel Corporation. All rights reserved.
 * Copyright (c) 2014 Chelsio, Inc. All rights reserved.
 */

#अगर_अघोषित _IW_PORTMAP_H
#घोषणा _IW_PORTMAP_H

#समावेश <linux/socket.h>
#समावेश <linux/netlink.h>

#घोषणा IWPM_ULIBNAME_SIZE	32
#घोषणा IWPM_DEVNAME_SIZE	32
#घोषणा IWPM_IFNAME_SIZE	16
#घोषणा IWPM_IPADDR_SIZE	16

क्रमागत अणु
	IWPM_INVALID_NLMSG_ERR = 10,
	IWPM_CREATE_MAPPING_ERR,
	IWPM_DUPLICATE_MAPPING_ERR,
	IWPM_UNKNOWN_MAPPING_ERR,
	IWPM_CLIENT_DEV_INFO_ERR,
	IWPM_USER_LIB_INFO_ERR,
	IWPM_REMOTE_QUERY_REJECT
पूर्ण;

काष्ठा iwpm_dev_data अणु
	अक्षर dev_name[IWPM_DEVNAME_SIZE];
	अक्षर अगर_name[IWPM_IFNAME_SIZE];
पूर्ण;

काष्ठा iwpm_sa_data अणु
	काष्ठा sockaddr_storage loc_addr;
	काष्ठा sockaddr_storage mapped_loc_addr;
	काष्ठा sockaddr_storage rem_addr;
	काष्ठा sockaddr_storage mapped_rem_addr;
	u32 flags;
पूर्ण;

पूर्णांक iwpm_init(u8);
पूर्णांक iwpm_निकास(u8);
पूर्णांक iwpm_valid_pid(व्योम);
पूर्णांक iwpm_रेजिस्टर_pid(काष्ठा iwpm_dev_data *pm_msg, u8 nl_client);
पूर्णांक iwpm_add_mapping(काष्ठा iwpm_sa_data *pm_msg, u8 nl_client);
पूर्णांक iwpm_add_and_query_mapping(काष्ठा iwpm_sa_data *pm_msg, u8 nl_client);
पूर्णांक iwpm_हटाओ_mapping(काष्ठा sockaddr_storage *local_addr, u8 nl_client);
पूर्णांक iwpm_रेजिस्टर_pid_cb(काष्ठा sk_buff *, काष्ठा netlink_callback *);
पूर्णांक iwpm_add_mapping_cb(काष्ठा sk_buff *, काष्ठा netlink_callback *);
पूर्णांक iwpm_add_and_query_mapping_cb(काष्ठा sk_buff *, काष्ठा netlink_callback *);
पूर्णांक iwpm_remote_info_cb(काष्ठा sk_buff *, काष्ठा netlink_callback *);
पूर्णांक iwpm_mapping_error_cb(काष्ठा sk_buff *, काष्ठा netlink_callback *);
पूर्णांक iwpm_mapping_info_cb(काष्ठा sk_buff *, काष्ठा netlink_callback *);
पूर्णांक iwpm_ack_mapping_info_cb(काष्ठा sk_buff *, काष्ठा netlink_callback *);
पूर्णांक iwpm_get_remote_info(काष्ठा sockaddr_storage *mapped_loc_addr,
			काष्ठा sockaddr_storage *mapped_rem_addr,
			काष्ठा sockaddr_storage *remote_addr, u8 nl_client);
पूर्णांक iwpm_create_mapinfo(काष्ठा sockaddr_storage *local_addr,
			काष्ठा sockaddr_storage *mapped_addr, u8 nl_client,
			u32 map_flags);
पूर्णांक iwpm_हटाओ_mapinfo(काष्ठा sockaddr_storage *local_addr,
			काष्ठा sockaddr_storage *mapped_addr);

पूर्णांक iwpm_hello_cb(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
#पूर्ण_अगर /* _IW_PORTMAP_H */
