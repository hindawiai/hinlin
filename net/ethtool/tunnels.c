<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/ethtool_netlink.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/vxlan.h>

#समावेश "bitset.h"
#समावेश "common.h"
#समावेश "netlink.h"

स्थिर काष्ठा nla_policy ethnl_tunnel_info_get_policy[] = अणु
	[ETHTOOL_A_TUNNEL_INFO_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल_निश्चित(ETHTOOL_UDP_TUNNEL_TYPE_VXLAN == ilog2(UDP_TUNNEL_TYPE_VXLAN));
अटल_निश्चित(ETHTOOL_UDP_TUNNEL_TYPE_GENEVE == ilog2(UDP_TUNNEL_TYPE_GENEVE));
अटल_निश्चित(ETHTOOL_UDP_TUNNEL_TYPE_VXLAN_GPE ==
	      ilog2(UDP_TUNNEL_TYPE_VXLAN_GPE));

अटल sमाप_प्रकार ethnl_udp_table_reply_size(अचिन्हित पूर्णांक types, bool compact)
अणु
	sमाप_प्रकार size;

	size = ethnl_bitset32_size(&types, शून्य, __ETHTOOL_UDP_TUNNEL_TYPE_CNT,
				   udp_tunnel_type_names, compact);
	अगर (size < 0)
		वापस size;

	वापस size +
		nla_total_size(0) + /* _UDP_TABLE */
		nla_total_size(माप(u32)); /* _UDP_TABLE_SIZE */
पूर्ण

अटल sमाप_प्रकार
ethnl_tunnel_info_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			     काष्ठा netlink_ext_ack *extack)
अणु
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा udp_tunnel_nic_info *info;
	अचिन्हित पूर्णांक i;
	sमाप_प्रकार ret;
	माप_प्रकार size;

	info = req_base->dev->udp_tunnel_nic_info;
	अगर (!info) अणु
		NL_SET_ERR_MSG(extack,
			       "device does not report tunnel offload info");
		वापस -EOPNOTSUPP;
	पूर्ण

	size =	nla_total_size(0); /* _INFO_UDP_PORTS */

	क्रम (i = 0; i < UDP_TUNNEL_NIC_MAX_TABLES; i++) अणु
		अगर (!info->tables[i].n_entries)
			अवरोध;

		ret = ethnl_udp_table_reply_size(info->tables[i].tunnel_types,
						 compact);
		अगर (ret < 0)
			वापस ret;
		size += ret;

		size += udp_tunnel_nic_dump_size(req_base->dev, i);
	पूर्ण

	अगर (info->flags & UDP_TUNNEL_NIC_INFO_STATIC_IANA_VXLAN) अणु
		ret = ethnl_udp_table_reply_size(0, compact);
		अगर (ret < 0)
			वापस ret;
		size += ret;

		size += nla_total_size(0) +		 /* _TABLE_ENTRY */
			nla_total_size(माप(__be16)) + /* _ENTRY_PORT */
			nla_total_size(माप(u32));	 /* _ENTRY_TYPE */
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक
ethnl_tunnel_info_fill_reply(स्थिर काष्ठा ethnl_req_info *req_base,
			     काष्ठा sk_buff *skb)
अणु
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा udp_tunnel_nic_info *info;
	काष्ठा nlattr *ports, *table, *entry;
	अचिन्हित पूर्णांक i;

	info = req_base->dev->udp_tunnel_nic_info;
	अगर (!info)
		वापस -EOPNOTSUPP;

	ports = nla_nest_start(skb, ETHTOOL_A_TUNNEL_INFO_UDP_PORTS);
	अगर (!ports)
		वापस -EMSGSIZE;

	क्रम (i = 0; i < UDP_TUNNEL_NIC_MAX_TABLES; i++) अणु
		अगर (!info->tables[i].n_entries)
			अवरोध;

		table = nla_nest_start(skb, ETHTOOL_A_TUNNEL_UDP_TABLE);
		अगर (!table)
			जाओ err_cancel_ports;

		अगर (nla_put_u32(skb, ETHTOOL_A_TUNNEL_UDP_TABLE_SIZE,
				info->tables[i].n_entries))
			जाओ err_cancel_table;

		अगर (ethnl_put_bitset32(skb, ETHTOOL_A_TUNNEL_UDP_TABLE_TYPES,
				       &info->tables[i].tunnel_types, शून्य,
				       __ETHTOOL_UDP_TUNNEL_TYPE_CNT,
				       udp_tunnel_type_names, compact))
			जाओ err_cancel_table;

		अगर (udp_tunnel_nic_dump_ग_लिखो(req_base->dev, i, skb))
			जाओ err_cancel_table;

		nla_nest_end(skb, table);
	पूर्ण

	अगर (info->flags & UDP_TUNNEL_NIC_INFO_STATIC_IANA_VXLAN) अणु
		u32 zero = 0;

		table = nla_nest_start(skb, ETHTOOL_A_TUNNEL_UDP_TABLE);
		अगर (!table)
			जाओ err_cancel_ports;

		अगर (nla_put_u32(skb, ETHTOOL_A_TUNNEL_UDP_TABLE_SIZE, 1))
			जाओ err_cancel_table;

		अगर (ethnl_put_bitset32(skb, ETHTOOL_A_TUNNEL_UDP_TABLE_TYPES,
				       &zero, शून्य,
				       __ETHTOOL_UDP_TUNNEL_TYPE_CNT,
				       udp_tunnel_type_names, compact))
			जाओ err_cancel_table;

		entry = nla_nest_start(skb, ETHTOOL_A_TUNNEL_UDP_TABLE_ENTRY);

		अगर (nla_put_be16(skb, ETHTOOL_A_TUNNEL_UDP_ENTRY_PORT,
				 htons(IANA_VXLAN_UDP_PORT)) ||
		    nla_put_u32(skb, ETHTOOL_A_TUNNEL_UDP_ENTRY_TYPE,
				ilog2(UDP_TUNNEL_TYPE_VXLAN)))
			जाओ err_cancel_entry;

		nla_nest_end(skb, entry);
		nla_nest_end(skb, table);
	पूर्ण

	nla_nest_end(skb, ports);

	वापस 0;

err_cancel_entry:
	nla_nest_cancel(skb, entry);
err_cancel_table:
	nla_nest_cancel(skb, table);
err_cancel_ports:
	nla_nest_cancel(skb, ports);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक ethnl_tunnel_info_करोit(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	काष्ठा sk_buff *rskb;
	व्योम *reply_payload;
	पूर्णांक reply_len;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_TUNNEL_INFO_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;

	rtnl_lock();
	ret = ethnl_tunnel_info_reply_size(&req_info, info->extack);
	अगर (ret < 0)
		जाओ err_unlock_rtnl;
	reply_len = ret + ethnl_reply_header_size();

	rskb = ethnl_reply_init(reply_len, req_info.dev,
				ETHTOOL_MSG_TUNNEL_INFO_GET_REPLY,
				ETHTOOL_A_TUNNEL_INFO_HEADER,
				info, &reply_payload);
	अगर (!rskb) अणु
		ret = -ENOMEM;
		जाओ err_unlock_rtnl;
	पूर्ण

	ret = ethnl_tunnel_info_fill_reply(&req_info, rskb);
	अगर (ret)
		जाओ err_मुक्त_msg;
	rtnl_unlock();
	dev_put(req_info.dev);
	genlmsg_end(rskb, reply_payload);

	वापस genlmsg_reply(rskb, info);

err_मुक्त_msg:
	nlmsg_मुक्त(rskb);
err_unlock_rtnl:
	rtnl_unlock();
	dev_put(req_info.dev);
	वापस ret;
पूर्ण

काष्ठा ethnl_tunnel_info_dump_ctx अणु
	काष्ठा ethnl_req_info	req_info;
	पूर्णांक			pos_hash;
	पूर्णांक			pos_idx;
पूर्ण;

पूर्णांक ethnl_tunnel_info_start(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	काष्ठा ethnl_tunnel_info_dump_ctx *ctx = (व्योम *)cb->ctx;
	काष्ठा nlattr **tb = info->attrs;
	पूर्णांक ret;

	BUILD_BUG_ON(माप(*ctx) > माप(cb->ctx));

	स_रखो(ctx, 0, माप(*ctx));

	ret = ethnl_parse_header_dev_get(&ctx->req_info,
					 tb[ETHTOOL_A_TUNNEL_INFO_HEADER],
					 sock_net(cb->skb->sk), cb->extack,
					 false);
	अगर (ctx->req_info.dev) अणु
		dev_put(ctx->req_info.dev);
		ctx->req_info.dev = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ethnl_tunnel_info_dumpit(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा ethnl_tunnel_info_dump_ctx *ctx = (व्योम *)cb->ctx;
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक s_idx = ctx->pos_idx;
	पूर्णांक h, idx = 0;
	पूर्णांक ret = 0;
	व्योम *ehdr;

	rtnl_lock();
	cb->seq = net->dev_base_seq;
	क्रम (h = ctx->pos_hash; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		काष्ठा hlist_head *head;
		काष्ठा net_device *dev;

		head = &net->dev_index_head[h];
		idx = 0;
		hlist_क्रम_each_entry(dev, head, index_hlist) अणु
			अगर (idx < s_idx)
				जाओ cont;

			ehdr = ethnl_dump_put(skb, cb,
					      ETHTOOL_MSG_TUNNEL_INFO_GET_REPLY);
			अगर (!ehdr) अणु
				ret = -EMSGSIZE;
				जाओ out;
			पूर्ण

			ret = ethnl_fill_reply_header(skb, dev, ETHTOOL_A_TUNNEL_INFO_HEADER);
			अगर (ret < 0) अणु
				genlmsg_cancel(skb, ehdr);
				जाओ out;
			पूर्ण

			ctx->req_info.dev = dev;
			ret = ethnl_tunnel_info_fill_reply(&ctx->req_info, skb);
			ctx->req_info.dev = शून्य;
			अगर (ret < 0) अणु
				genlmsg_cancel(skb, ehdr);
				अगर (ret == -EOPNOTSUPP)
					जाओ cont;
				जाओ out;
			पूर्ण
			genlmsg_end(skb, ehdr);
cont:
			idx++;
		पूर्ण
	पूर्ण
out:
	rtnl_unlock();

	ctx->pos_hash = h;
	ctx->pos_idx = idx;
	nl_dump_check_consistent(cb, nlmsg_hdr(skb));

	अगर (ret == -EMSGSIZE && skb->len)
		वापस skb->len;
	वापस ret;
पूर्ण
