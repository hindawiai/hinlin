<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * File: pn_dev.h
 *
 * Phonet network device
 *
 * Copyright (C) 2008 Nokia Corporation.
 */

#अगर_अघोषित PN_DEV_H
#घोषणा PN_DEV_H

काष्ठा phonet_device_list अणु
	काष्ठा list_head list;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा phonet_device_list *phonet_device_list(काष्ठा net *net);

काष्ठा phonet_device अणु
	काष्ठा list_head list;
	काष्ठा net_device *netdev;
	DECLARE_BITMAP(addrs, 64);
	काष्ठा rcu_head	rcu;
पूर्ण;

पूर्णांक phonet_device_init(व्योम);
व्योम phonet_device_निकास(व्योम);
पूर्णांक phonet_netlink_रेजिस्टर(व्योम);
काष्ठा net_device *phonet_device_get(काष्ठा net *net);

पूर्णांक phonet_address_add(काष्ठा net_device *dev, u8 addr);
पूर्णांक phonet_address_del(काष्ठा net_device *dev, u8 addr);
u8 phonet_address_get(काष्ठा net_device *dev, u8 addr);
पूर्णांक phonet_address_lookup(काष्ठा net *net, u8 addr);
व्योम phonet_address_notअगरy(पूर्णांक event, काष्ठा net_device *dev, u8 addr);

पूर्णांक phonet_route_add(काष्ठा net_device *dev, u8 daddr);
पूर्णांक phonet_route_del(काष्ठा net_device *dev, u8 daddr);
व्योम rपंचांग_phonet_notअगरy(पूर्णांक event, काष्ठा net_device *dev, u8 dst);
काष्ठा net_device *phonet_route_get_rcu(काष्ठा net *net, u8 daddr);
काष्ठा net_device *phonet_route_output(काष्ठा net *net, u8 daddr);

#घोषणा PN_NO_ADDR	0xff

बाह्य स्थिर काष्ठा seq_operations pn_sock_seq_ops;
बाह्य स्थिर काष्ठा seq_operations pn_res_seq_ops;

#पूर्ण_अगर
