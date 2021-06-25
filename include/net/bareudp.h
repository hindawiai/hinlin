<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __NET_BAREUDP_H
#घोषणा __NET_BAREUDP_H

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <net/rtnetlink.h>

काष्ठा bareudp_conf अणु
	__be16 ethertype;
	__be16 port;
	u16 sport_min;
	bool multi_proto_mode;
पूर्ण;

काष्ठा net_device *bareudp_dev_create(काष्ठा net *net, स्थिर अक्षर *name,
				      u8 name_assign_type,
				      काष्ठा bareudp_conf *info);

अटल अंतरभूत bool netअगर_is_bareudp(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->rtnl_link_ops &&
	       !म_भेद(dev->rtnl_link_ops->kind, "bareudp");
पूर्ण

#पूर्ण_अगर
