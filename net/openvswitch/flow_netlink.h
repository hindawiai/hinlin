<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2007-2013 Nicira, Inc.
 */


#अगर_अघोषित FLOW_NETLINK_H
#घोषणा FLOW_NETLINK_H 1

#समावेश <linux/kernel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/खोलोvचयन.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in6.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समय.स>

#समावेश <net/inet_ecn.h>
#समावेश <net/ip_tunnels.h>

#समावेश "flow.h"

माप_प्रकार ovs_tun_key_attr_size(व्योम);
माप_प्रकार ovs_key_attr_size(व्योम);

व्योम ovs_match_init(काष्ठा sw_flow_match *match,
		    काष्ठा sw_flow_key *key, bool reset_key,
		    काष्ठा sw_flow_mask *mask);

पूर्णांक ovs_nla_put_key(स्थिर काष्ठा sw_flow_key *, स्थिर काष्ठा sw_flow_key *,
		    पूर्णांक attr, bool is_mask, काष्ठा sk_buff *);
पूर्णांक parse_flow_nlattrs(स्थिर काष्ठा nlattr *attr, स्थिर काष्ठा nlattr *a[],
		       u64 *attrsp, bool log);
पूर्णांक ovs_nla_get_flow_metadata(काष्ठा net *net,
			      स्थिर काष्ठा nlattr *a[OVS_KEY_ATTR_MAX + 1],
			      u64 attrs, काष्ठा sw_flow_key *key, bool log);

पूर्णांक ovs_nla_put_identअगरier(स्थिर काष्ठा sw_flow *flow, काष्ठा sk_buff *skb);
पूर्णांक ovs_nla_put_masked_key(स्थिर काष्ठा sw_flow *flow, काष्ठा sk_buff *skb);
पूर्णांक ovs_nla_put_mask(स्थिर काष्ठा sw_flow *flow, काष्ठा sk_buff *skb);

पूर्णांक ovs_nla_get_match(काष्ठा net *, काष्ठा sw_flow_match *,
		      स्थिर काष्ठा nlattr *key, स्थिर काष्ठा nlattr *mask,
		      bool log);

पूर्णांक ovs_nla_put_tunnel_info(काष्ठा sk_buff *skb,
			    काष्ठा ip_tunnel_info *tun_info);

bool ovs_nla_get_ufid(काष्ठा sw_flow_id *, स्थिर काष्ठा nlattr *, bool log);
पूर्णांक ovs_nla_get_identअगरier(काष्ठा sw_flow_id *sfid, स्थिर काष्ठा nlattr *ufid,
			   स्थिर काष्ठा sw_flow_key *key, bool log);
u32 ovs_nla_get_ufid_flags(स्थिर काष्ठा nlattr *attr);

पूर्णांक ovs_nla_copy_actions(काष्ठा net *net, स्थिर काष्ठा nlattr *attr,
			 स्थिर काष्ठा sw_flow_key *key,
			 काष्ठा sw_flow_actions **sfa, bool log);
पूर्णांक ovs_nla_add_action(काष्ठा sw_flow_actions **sfa, पूर्णांक attrtype,
		       व्योम *data, पूर्णांक len, bool log);
पूर्णांक ovs_nla_put_actions(स्थिर काष्ठा nlattr *attr,
			पूर्णांक len, काष्ठा sk_buff *skb);

व्योम ovs_nla_मुक्त_flow_actions(काष्ठा sw_flow_actions *);
व्योम ovs_nla_मुक्त_flow_actions_rcu(काष्ठा sw_flow_actions *);

पूर्णांक nsh_key_from_nlattr(स्थिर काष्ठा nlattr *attr, काष्ठा ovs_key_nsh *nsh,
			काष्ठा ovs_key_nsh *nsh_mask);
पूर्णांक nsh_hdr_from_nlattr(स्थिर काष्ठा nlattr *attr, काष्ठा nshhdr *nh,
			माप_प्रकार size);

#पूर्ण_अगर /* flow_netlink.h */
