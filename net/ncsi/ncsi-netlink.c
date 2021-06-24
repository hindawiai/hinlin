<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright Samuel Menकरोza-Jonas, IBM Corporation 2018.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/genetlink.h>
#समावेश <net/ncsi.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/ncsi.h>

#समावेश "internal.h"
#समावेश "ncsi-pkt.h"
#समावेश "ncsi-netlink.h"

अटल काष्ठा genl_family ncsi_genl_family;

अटल स्थिर काष्ठा nla_policy ncsi_genl_policy[NCSI_ATTR_MAX + 1] = अणु
	[NCSI_ATTR_IFINDEX] =		अणु .type = NLA_U32 पूर्ण,
	[NCSI_ATTR_PACKAGE_LIST] =	अणु .type = NLA_NESTED पूर्ण,
	[NCSI_ATTR_PACKAGE_ID] =	अणु .type = NLA_U32 पूर्ण,
	[NCSI_ATTR_CHANNEL_ID] =	अणु .type = NLA_U32 पूर्ण,
	[NCSI_ATTR_DATA] =		अणु .type = NLA_BINARY, .len = 2048 पूर्ण,
	[NCSI_ATTR_MULTI_FLAG] =	अणु .type = NLA_FLAG पूर्ण,
	[NCSI_ATTR_PACKAGE_MASK] =	अणु .type = NLA_U32 पूर्ण,
	[NCSI_ATTR_CHANNEL_MASK] =	अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा ncsi_dev_priv *ndp_from_अगरindex(काष्ठा net *net, u32 अगरindex)
अणु
	काष्ठा ncsi_dev_priv *ndp;
	काष्ठा net_device *dev;
	काष्ठा ncsi_dev *nd;
	काष्ठा ncsi_dev;

	अगर (!net)
		वापस शून्य;

	dev = dev_get_by_index(net, अगरindex);
	अगर (!dev) अणु
		pr_err("NCSI netlink: No device for ifindex %u\n", अगरindex);
		वापस शून्य;
	पूर्ण

	nd = ncsi_find_dev(dev);
	ndp = nd ? TO_NCSI_DEV_PRIV(nd) : शून्य;

	dev_put(dev);
	वापस ndp;
पूर्ण

अटल पूर्णांक ncsi_ग_लिखो_channel_info(काष्ठा sk_buff *skb,
				   काष्ठा ncsi_dev_priv *ndp,
				   काष्ठा ncsi_channel *nc)
अणु
	काष्ठा ncsi_channel_vlan_filter *ncf;
	काष्ठा ncsi_channel_mode *m;
	काष्ठा nlattr *vid_nest;
	पूर्णांक i;

	nla_put_u32(skb, NCSI_CHANNEL_ATTR_ID, nc->id);
	m = &nc->modes[NCSI_MODE_LINK];
	nla_put_u32(skb, NCSI_CHANNEL_ATTR_LINK_STATE, m->data[2]);
	अगर (nc->state == NCSI_CHANNEL_ACTIVE)
		nla_put_flag(skb, NCSI_CHANNEL_ATTR_ACTIVE);
	अगर (nc == nc->package->preferred_channel)
		nla_put_flag(skb, NCSI_CHANNEL_ATTR_FORCED);

	nla_put_u32(skb, NCSI_CHANNEL_ATTR_VERSION_MAJOR, nc->version.version);
	nla_put_u32(skb, NCSI_CHANNEL_ATTR_VERSION_MINOR, nc->version.alpha2);
	nla_put_string(skb, NCSI_CHANNEL_ATTR_VERSION_STR, nc->version.fw_name);

	vid_nest = nla_nest_start_noflag(skb, NCSI_CHANNEL_ATTR_VLAN_LIST);
	अगर (!vid_nest)
		वापस -ENOMEM;
	ncf = &nc->vlan_filter;
	i = -1;
	जबतक ((i = find_next_bit((व्योम *)&ncf->biपंचांगap, ncf->n_vids,
				  i + 1)) < ncf->n_vids) अणु
		अगर (ncf->vids[i])
			nla_put_u16(skb, NCSI_CHANNEL_ATTR_VLAN_ID,
				    ncf->vids[i]);
	पूर्ण
	nla_nest_end(skb, vid_nest);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_ग_लिखो_package_info(काष्ठा sk_buff *skb,
				   काष्ठा ncsi_dev_priv *ndp, अचिन्हित पूर्णांक id)
अणु
	काष्ठा nlattr *pnest, *cnest, *nest;
	काष्ठा ncsi_package *np;
	काष्ठा ncsi_channel *nc;
	bool found;
	पूर्णांक rc;

	अगर (id > ndp->package_num - 1) अणु
		netdev_info(ndp->ndev.dev, "NCSI: No package with id %u\n", id);
		वापस -ENODEV;
	पूर्ण

	found = false;
	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		अगर (np->id != id)
			जारी;
		pnest = nla_nest_start_noflag(skb, NCSI_PKG_ATTR);
		अगर (!pnest)
			वापस -ENOMEM;
		nla_put_u32(skb, NCSI_PKG_ATTR_ID, np->id);
		अगर ((0x1 << np->id) == ndp->package_whitelist)
			nla_put_flag(skb, NCSI_PKG_ATTR_FORCED);
		cnest = nla_nest_start_noflag(skb, NCSI_PKG_ATTR_CHANNEL_LIST);
		अगर (!cnest) अणु
			nla_nest_cancel(skb, pnest);
			वापस -ENOMEM;
		पूर्ण
		NCSI_FOR_EACH_CHANNEL(np, nc) अणु
			nest = nla_nest_start_noflag(skb, NCSI_CHANNEL_ATTR);
			अगर (!nest) अणु
				nla_nest_cancel(skb, cnest);
				nla_nest_cancel(skb, pnest);
				वापस -ENOMEM;
			पूर्ण
			rc = ncsi_ग_लिखो_channel_info(skb, ndp, nc);
			अगर (rc) अणु
				nla_nest_cancel(skb, nest);
				nla_nest_cancel(skb, cnest);
				nla_nest_cancel(skb, pnest);
				वापस rc;
			पूर्ण
			nla_nest_end(skb, nest);
		पूर्ण
		nla_nest_end(skb, cnest);
		nla_nest_end(skb, pnest);
		found = true;
	पूर्ण

	अगर (!found)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_pkg_info_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा ncsi_dev_priv *ndp;
	अचिन्हित पूर्णांक package_id;
	काष्ठा sk_buff *skb;
	काष्ठा nlattr *attr;
	व्योम *hdr;
	पूर्णांक rc;

	अगर (!info || !info->attrs)
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_PACKAGE_ID])
		वापस -EINVAL;

	ndp = ndp_from_अगरindex(genl_info_net(info),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	अगर (!ndp)
		वापस -ENODEV;

	skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = genlmsg_put(skb, info->snd_portid, info->snd_seq,
			  &ncsi_genl_family, 0, NCSI_CMD_PKG_INFO);
	अगर (!hdr) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	package_id = nla_get_u32(info->attrs[NCSI_ATTR_PACKAGE_ID]);

	attr = nla_nest_start_noflag(skb, NCSI_ATTR_PACKAGE_LIST);
	अगर (!attr) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण
	rc = ncsi_ग_लिखो_package_info(skb, ndp, package_id);

	अगर (rc) अणु
		nla_nest_cancel(skb, attr);
		जाओ err;
	पूर्ण

	nla_nest_end(skb, attr);

	genlmsg_end(skb, hdr);
	वापस genlmsg_reply(skb, info);

err:
	kमुक्त_skb(skb);
	वापस rc;
पूर्ण

अटल पूर्णांक ncsi_pkg_info_all_nl(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr *attrs[NCSI_ATTR_MAX + 1];
	काष्ठा ncsi_package *np, *package;
	काष्ठा ncsi_dev_priv *ndp;
	अचिन्हित पूर्णांक package_id;
	काष्ठा nlattr *attr;
	व्योम *hdr;
	पूर्णांक rc;

	rc = genlmsg_parse_deprecated(cb->nlh, &ncsi_genl_family, attrs, NCSI_ATTR_MAX,
				      ncsi_genl_policy, शून्य);
	अगर (rc)
		वापस rc;

	अगर (!attrs[NCSI_ATTR_IFINDEX])
		वापस -EINVAL;

	ndp = ndp_from_अगरindex(get_net(sock_net(skb->sk)),
			       nla_get_u32(attrs[NCSI_ATTR_IFINDEX]));

	अगर (!ndp)
		वापस -ENODEV;

	package_id = cb->args[0];
	package = शून्य;
	NCSI_FOR_EACH_PACKAGE(ndp, np)
		अगर (np->id == package_id)
			package = np;

	अगर (!package)
		वापस 0; /* करोne */

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &ncsi_genl_family, NLM_F_MULTI,  NCSI_CMD_PKG_INFO);
	अगर (!hdr) अणु
		rc = -EMSGSIZE;
		जाओ err;
	पूर्ण

	attr = nla_nest_start_noflag(skb, NCSI_ATTR_PACKAGE_LIST);
	अगर (!attr) अणु
		rc = -EMSGSIZE;
		जाओ err;
	पूर्ण
	rc = ncsi_ग_लिखो_package_info(skb, ndp, package->id);
	अगर (rc) अणु
		nla_nest_cancel(skb, attr);
		जाओ err;
	पूर्ण

	nla_nest_end(skb, attr);
	genlmsg_end(skb, hdr);

	cb->args[0] = package_id + 1;

	वापस skb->len;
err:
	genlmsg_cancel(skb, hdr);
	वापस rc;
पूर्ण

अटल पूर्णांक ncsi_set_पूर्णांकerface_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा ncsi_package *np, *package;
	काष्ठा ncsi_channel *nc, *channel;
	u32 package_id, channel_id;
	काष्ठा ncsi_dev_priv *ndp;
	अचिन्हित दीर्घ flags;

	अगर (!info || !info->attrs)
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_PACKAGE_ID])
		वापस -EINVAL;

	ndp = ndp_from_अगरindex(get_net(sock_net(msg->sk)),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	अगर (!ndp)
		वापस -ENODEV;

	package_id = nla_get_u32(info->attrs[NCSI_ATTR_PACKAGE_ID]);
	package = शून्य;

	NCSI_FOR_EACH_PACKAGE(ndp, np)
		अगर (np->id == package_id)
			package = np;
	अगर (!package) अणु
		/* The user has set a package that करोes not exist */
		वापस -दुस्फल;
	पूर्ण

	channel = शून्य;
	अगर (info->attrs[NCSI_ATTR_CHANNEL_ID]) अणु
		channel_id = nla_get_u32(info->attrs[NCSI_ATTR_CHANNEL_ID]);
		NCSI_FOR_EACH_CHANNEL(package, nc)
			अगर (nc->id == channel_id) अणु
				channel = nc;
				अवरोध;
			पूर्ण
		अगर (!channel) अणु
			netdev_info(ndp->ndev.dev,
				    "NCSI: Channel %u does not exist!\n",
				    channel_id);
			वापस -दुस्फल;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&ndp->lock, flags);
	ndp->package_whitelist = 0x1 << package->id;
	ndp->multi_package = false;
	spin_unlock_irqrestore(&ndp->lock, flags);

	spin_lock_irqsave(&package->lock, flags);
	package->multi_channel = false;
	अगर (channel) अणु
		package->channel_whitelist = 0x1 << channel->id;
		package->preferred_channel = channel;
	पूर्ण अन्यथा अणु
		/* Allow any channel */
		package->channel_whitelist = अच_पूर्णांक_उच्च;
		package->preferred_channel = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&package->lock, flags);

	अगर (channel)
		netdev_info(ndp->ndev.dev,
			    "Set package 0x%x, channel 0x%x as preferred\n",
			    package_id, channel_id);
	अन्यथा
		netdev_info(ndp->ndev.dev, "Set package 0x%x as preferred\n",
			    package_id);

	/* Update channel configuration */
	अगर (!(ndp->flags & NCSI_DEV_RESET))
		ncsi_reset_dev(&ndp->ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_clear_पूर्णांकerface_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा ncsi_dev_priv *ndp;
	काष्ठा ncsi_package *np;
	अचिन्हित दीर्घ flags;

	अगर (!info || !info->attrs)
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_IFINDEX])
		वापस -EINVAL;

	ndp = ndp_from_अगरindex(get_net(sock_net(msg->sk)),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	अगर (!ndp)
		वापस -ENODEV;

	/* Reset any whitelists and disable multi mode */
	spin_lock_irqsave(&ndp->lock, flags);
	ndp->package_whitelist = अच_पूर्णांक_उच्च;
	ndp->multi_package = false;
	spin_unlock_irqrestore(&ndp->lock, flags);

	NCSI_FOR_EACH_PACKAGE(ndp, np) अणु
		spin_lock_irqsave(&np->lock, flags);
		np->multi_channel = false;
		np->channel_whitelist = अच_पूर्णांक_उच्च;
		np->preferred_channel = शून्य;
		spin_unlock_irqrestore(&np->lock, flags);
	पूर्ण
	netdev_info(ndp->ndev.dev, "NCSI: Cleared preferred package/channel\n");

	/* Update channel configuration */
	अगर (!(ndp->flags & NCSI_DEV_RESET))
		ncsi_reset_dev(&ndp->ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक ncsi_send_cmd_nl(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा ncsi_dev_priv *ndp;
	काष्ठा ncsi_pkt_hdr *hdr;
	काष्ठा ncsi_cmd_arg nca;
	अचिन्हित अक्षर *data;
	u32 package_id;
	u32 channel_id;
	पूर्णांक len, ret;

	अगर (!info || !info->attrs) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!info->attrs[NCSI_ATTR_IFINDEX]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!info->attrs[NCSI_ATTR_PACKAGE_ID]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!info->attrs[NCSI_ATTR_CHANNEL_ID]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!info->attrs[NCSI_ATTR_DATA]) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ndp = ndp_from_अगरindex(get_net(sock_net(msg->sk)),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	अगर (!ndp) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	package_id = nla_get_u32(info->attrs[NCSI_ATTR_PACKAGE_ID]);
	channel_id = nla_get_u32(info->attrs[NCSI_ATTR_CHANNEL_ID]);

	अगर (package_id >= NCSI_MAX_PACKAGE || channel_id >= NCSI_MAX_CHANNEL) अणु
		ret = -दुस्फल;
		जाओ out_netlink;
	पूर्ण

	len = nla_len(info->attrs[NCSI_ATTR_DATA]);
	अगर (len < माप(काष्ठा ncsi_pkt_hdr)) अणु
		netdev_info(ndp->ndev.dev, "NCSI: no command to send %u\n",
			    package_id);
		ret = -EINVAL;
		जाओ out_netlink;
	पूर्ण अन्यथा अणु
		data = (अचिन्हित अक्षर *)nla_data(info->attrs[NCSI_ATTR_DATA]);
	पूर्ण

	hdr = (काष्ठा ncsi_pkt_hdr *)data;

	nca.ndp = ndp;
	nca.package = (अचिन्हित अक्षर)package_id;
	nca.channel = (अचिन्हित अक्षर)channel_id;
	nca.type = hdr->type;
	nca.req_flags = NCSI_REQ_FLAG_NETLINK_DRIVEN;
	nca.info = info;
	nca.payload = ntohs(hdr->length);
	nca.data = data + माप(*hdr);

	ret = ncsi_xmit_cmd(&nca);
out_netlink:
	अगर (ret != 0) अणु
		netdev_err(ndp->ndev.dev,
			   "NCSI: Error %d sending command\n",
			   ret);
		ncsi_send_netlink_err(ndp->ndev.dev,
				      info->snd_seq,
				      info->snd_portid,
				      info->nlhdr,
				      ret);
	पूर्ण
out:
	वापस ret;
पूर्ण

पूर्णांक ncsi_send_netlink_rsp(काष्ठा ncsi_request *nr,
			  काष्ठा ncsi_package *np,
			  काष्ठा ncsi_channel *nc)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net *net;
	व्योम *hdr;
	पूर्णांक rc;

	net = dev_net(nr->rsp->dev);

	skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = genlmsg_put(skb, nr->snd_portid, nr->snd_seq,
			  &ncsi_genl_family, 0, NCSI_CMD_SEND_CMD);
	अगर (!hdr) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	nla_put_u32(skb, NCSI_ATTR_IFINDEX, nr->rsp->dev->अगरindex);
	अगर (np)
		nla_put_u32(skb, NCSI_ATTR_PACKAGE_ID, np->id);
	अगर (nc)
		nla_put_u32(skb, NCSI_ATTR_CHANNEL_ID, nc->id);
	अन्यथा
		nla_put_u32(skb, NCSI_ATTR_CHANNEL_ID, NCSI_RESERVED_CHANNEL);

	rc = nla_put(skb, NCSI_ATTR_DATA, nr->rsp->len, (व्योम *)nr->rsp->data);
	अगर (rc)
		जाओ err;

	genlmsg_end(skb, hdr);
	वापस genlmsg_unicast(net, skb, nr->snd_portid);

err:
	kमुक्त_skb(skb);
	वापस rc;
पूर्ण

पूर्णांक ncsi_send_netlink_समयout(काष्ठा ncsi_request *nr,
			      काष्ठा ncsi_package *np,
			      काष्ठा ncsi_channel *nc)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net *net;
	व्योम *hdr;

	skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	hdr = genlmsg_put(skb, nr->snd_portid, nr->snd_seq,
			  &ncsi_genl_family, 0, NCSI_CMD_SEND_CMD);
	अगर (!hdr) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	net = dev_net(nr->cmd->dev);

	nla_put_u32(skb, NCSI_ATTR_IFINDEX, nr->cmd->dev->अगरindex);

	अगर (np)
		nla_put_u32(skb, NCSI_ATTR_PACKAGE_ID, np->id);
	अन्यथा
		nla_put_u32(skb, NCSI_ATTR_PACKAGE_ID,
			    NCSI_PACKAGE_INDEX((((काष्ठा ncsi_pkt_hdr *)
						 nr->cmd->data)->channel)));

	अगर (nc)
		nla_put_u32(skb, NCSI_ATTR_CHANNEL_ID, nc->id);
	अन्यथा
		nla_put_u32(skb, NCSI_ATTR_CHANNEL_ID, NCSI_RESERVED_CHANNEL);

	genlmsg_end(skb, hdr);
	वापस genlmsg_unicast(net, skb, nr->snd_portid);
पूर्ण

पूर्णांक ncsi_send_netlink_err(काष्ठा net_device *dev,
			  u32 snd_seq,
			  u32 snd_portid,
			  काष्ठा nlmsghdr *nlhdr,
			  पूर्णांक err)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा nlmsgerr *nle;
	काष्ठा sk_buff *skb;
	काष्ठा net *net;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	net = dev_net(dev);

	nlh = nlmsg_put(skb, snd_portid, snd_seq,
			NLMSG_ERROR, माप(*nle), 0);
	nle = (काष्ठा nlmsgerr *)nlmsg_data(nlh);
	nle->error = err;
	स_नकल(&nle->msg, nlhdr, माप(*nlh));

	nlmsg_end(skb, nlh);

	वापस nlmsg_unicast(net->genl_sock, skb, snd_portid);
पूर्ण

अटल पूर्णांक ncsi_set_package_mask_nl(काष्ठा sk_buff *msg,
				    काष्ठा genl_info *info)
अणु
	काष्ठा ncsi_dev_priv *ndp;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (!info || !info->attrs)
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_PACKAGE_MASK])
		वापस -EINVAL;

	ndp = ndp_from_अगरindex(get_net(sock_net(msg->sk)),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	अगर (!ndp)
		वापस -ENODEV;

	spin_lock_irqsave(&ndp->lock, flags);
	अगर (nla_get_flag(info->attrs[NCSI_ATTR_MULTI_FLAG])) अणु
		अगर (ndp->flags & NCSI_DEV_HWA) अणु
			ndp->multi_package = true;
			rc = 0;
		पूर्ण अन्यथा अणु
			netdev_err(ndp->ndev.dev,
				   "NCSI: Can't use multiple packages without HWA\n");
			rc = -EPERM;
		पूर्ण
	पूर्ण अन्यथा अणु
		ndp->multi_package = false;
		rc = 0;
	पूर्ण

	अगर (!rc)
		ndp->package_whitelist =
			nla_get_u32(info->attrs[NCSI_ATTR_PACKAGE_MASK]);
	spin_unlock_irqrestore(&ndp->lock, flags);

	अगर (!rc) अणु
		/* Update channel configuration */
		अगर (!(ndp->flags & NCSI_DEV_RESET))
			ncsi_reset_dev(&ndp->ndev);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक ncsi_set_channel_mask_nl(काष्ठा sk_buff *msg,
				    काष्ठा genl_info *info)
अणु
	काष्ठा ncsi_package *np, *package;
	काष्ठा ncsi_channel *nc, *channel;
	u32 package_id, channel_id;
	काष्ठा ncsi_dev_priv *ndp;
	अचिन्हित दीर्घ flags;

	अगर (!info || !info->attrs)
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_PACKAGE_ID])
		वापस -EINVAL;

	अगर (!info->attrs[NCSI_ATTR_CHANNEL_MASK])
		वापस -EINVAL;

	ndp = ndp_from_अगरindex(get_net(sock_net(msg->sk)),
			       nla_get_u32(info->attrs[NCSI_ATTR_IFINDEX]));
	अगर (!ndp)
		वापस -ENODEV;

	package_id = nla_get_u32(info->attrs[NCSI_ATTR_PACKAGE_ID]);
	package = शून्य;
	NCSI_FOR_EACH_PACKAGE(ndp, np)
		अगर (np->id == package_id) अणु
			package = np;
			अवरोध;
		पूर्ण
	अगर (!package)
		वापस -दुस्फल;

	spin_lock_irqsave(&package->lock, flags);

	channel = शून्य;
	अगर (info->attrs[NCSI_ATTR_CHANNEL_ID]) अणु
		channel_id = nla_get_u32(info->attrs[NCSI_ATTR_CHANNEL_ID]);
		NCSI_FOR_EACH_CHANNEL(np, nc)
			अगर (nc->id == channel_id) अणु
				channel = nc;
				अवरोध;
			पूर्ण
		अगर (!channel) अणु
			spin_unlock_irqrestore(&package->lock, flags);
			वापस -दुस्फल;
		पूर्ण
		netdev_dbg(ndp->ndev.dev,
			   "NCSI: Channel %u set as preferred channel\n",
			   channel->id);
	पूर्ण

	package->channel_whitelist =
		nla_get_u32(info->attrs[NCSI_ATTR_CHANNEL_MASK]);
	अगर (package->channel_whitelist == 0)
		netdev_dbg(ndp->ndev.dev,
			   "NCSI: Package %u set to all channels disabled\n",
			   package->id);

	package->preferred_channel = channel;

	अगर (nla_get_flag(info->attrs[NCSI_ATTR_MULTI_FLAG])) अणु
		package->multi_channel = true;
		netdev_info(ndp->ndev.dev,
			    "NCSI: Multi-channel enabled on package %u\n",
			    package_id);
	पूर्ण अन्यथा अणु
		package->multi_channel = false;
	पूर्ण

	spin_unlock_irqrestore(&package->lock, flags);

	/* Update channel configuration */
	अगर (!(ndp->flags & NCSI_DEV_RESET))
		ncsi_reset_dev(&ndp->ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops ncsi_ops[] = अणु
	अणु
		.cmd = NCSI_CMD_PKG_INFO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ncsi_pkg_info_nl,
		.dumpit = ncsi_pkg_info_all_nl,
		.flags = 0,
	पूर्ण,
	अणु
		.cmd = NCSI_CMD_SET_INTERFACE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ncsi_set_पूर्णांकerface_nl,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = NCSI_CMD_CLEAR_INTERFACE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ncsi_clear_पूर्णांकerface_nl,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = NCSI_CMD_SEND_CMD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ncsi_send_cmd_nl,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = NCSI_CMD_SET_PACKAGE_MASK,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ncsi_set_package_mask_nl,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = NCSI_CMD_SET_CHANNEL_MASK,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = ncsi_set_channel_mask_nl,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family ncsi_genl_family __ro_after_init = अणु
	.name = "NCSI",
	.version = 0,
	.maxattr = NCSI_ATTR_MAX,
	.policy = ncsi_genl_policy,
	.module = THIS_MODULE,
	.small_ops = ncsi_ops,
	.n_small_ops = ARRAY_SIZE(ncsi_ops),
पूर्ण;

अटल पूर्णांक __init ncsi_init_netlink(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&ncsi_genl_family);
पूर्ण
subsys_initcall(ncsi_init_netlink);
