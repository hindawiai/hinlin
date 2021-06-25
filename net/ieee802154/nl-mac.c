<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Netlink पूर्णांकerface क्रम IEEE 802.15.4 stack
 *
 * Copyright 2007, 2008 Siemens AG
 *
 * Written by:
 * Sergey Lapin <slapin@ossfans.org>
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Maxim Osipov <maxim.osipov@siemens.com>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ieee802154.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/sock.h>
#समावेश <linux/nl802154.h>
#समावेश <linux/export.h>
#समावेश <net/af_ieee802154.h>
#समावेश <net/ieee802154_netdev.h>
#समावेश <net/cfg802154.h>

#समावेश "ieee802154.h"

अटल पूर्णांक nla_put_hwaddr(काष्ठा sk_buff *msg, पूर्णांक type, __le64 hwaddr,
			  पूर्णांक padattr)
अणु
	वापस nla_put_u64_64bit(msg, type, swab64((__क्रमce u64)hwaddr),
				 padattr);
पूर्ण

अटल __le64 nla_get_hwaddr(स्थिर काष्ठा nlattr *nla)
अणु
	वापस ieee802154_devaddr_from_raw(nla_data(nla));
पूर्ण

अटल पूर्णांक nla_put_लघुaddr(काष्ठा sk_buff *msg, पूर्णांक type, __le16 addr)
अणु
	वापस nla_put_u16(msg, type, le16_to_cpu(addr));
पूर्ण

अटल __le16 nla_get_लघुaddr(स्थिर काष्ठा nlattr *nla)
अणु
	वापस cpu_to_le16(nla_get_u16(nla));
पूर्ण

अटल पूर्णांक ieee802154_nl_start_confirm(काष्ठा net_device *dev, u8 status)
अणु
	काष्ठा sk_buff *msg;

	pr_debug("%s\n", __func__);

	msg = ieee802154_nl_create(0, IEEE802154_START_CONF);
	अगर (!msg)
		वापस -ENOBUFS;

	अगर (nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name) ||
	    nla_put_u32(msg, IEEE802154_ATTR_DEV_INDEX, dev->अगरindex) ||
	    nla_put(msg, IEEE802154_ATTR_HW_ADDR, IEEE802154_ADDR_LEN,
		    dev->dev_addr) ||
	    nla_put_u8(msg, IEEE802154_ATTR_STATUS, status))
		जाओ nla_put_failure;
	वापस ieee802154_nl_mcast(msg, IEEE802154_COORD_MCGRP);

nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक ieee802154_nl_fill_अगरace(काष्ठा sk_buff *msg, u32 portid,
				    u32 seq, पूर्णांक flags, काष्ठा net_device *dev)
अणु
	व्योम *hdr;
	काष्ठा wpan_phy *phy;
	काष्ठा ieee802154_mlme_ops *ops;
	__le16 लघु_addr, pan_id;

	pr_debug("%s\n", __func__);

	hdr = genlmsg_put(msg, 0, seq, &nl802154_family, flags,
			  IEEE802154_LIST_IFACE);
	अगर (!hdr)
		जाओ out;

	ops = ieee802154_mlme_ops(dev);
	phy = dev->ieee802154_ptr->wpan_phy;
	BUG_ON(!phy);
	get_device(&phy->dev);

	rtnl_lock();
	लघु_addr = dev->ieee802154_ptr->लघु_addr;
	pan_id = dev->ieee802154_ptr->pan_id;
	rtnl_unlock();

	अगर (nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name) ||
	    nla_put_string(msg, IEEE802154_ATTR_PHY_NAME, wpan_phy_name(phy)) ||
	    nla_put_u32(msg, IEEE802154_ATTR_DEV_INDEX, dev->अगरindex) ||
	    nla_put(msg, IEEE802154_ATTR_HW_ADDR, IEEE802154_ADDR_LEN,
		    dev->dev_addr) ||
	    nla_put_लघुaddr(msg, IEEE802154_ATTR_SHORT_ADDR, लघु_addr) ||
	    nla_put_लघुaddr(msg, IEEE802154_ATTR_PAN_ID, pan_id))
		जाओ nla_put_failure;

	अगर (ops->get_mac_params) अणु
		काष्ठा ieee802154_mac_params params;

		rtnl_lock();
		ops->get_mac_params(dev, &params);
		rtnl_unlock();

		अगर (nla_put_s8(msg, IEEE802154_ATTR_TXPOWER,
			       params.transmit_घातer / 100) ||
		    nla_put_u8(msg, IEEE802154_ATTR_LBT_ENABLED, params.lbt) ||
		    nla_put_u8(msg, IEEE802154_ATTR_CCA_MODE,
			       params.cca.mode) ||
		    nla_put_s32(msg, IEEE802154_ATTR_CCA_ED_LEVEL,
				params.cca_ed_level / 100) ||
		    nla_put_u8(msg, IEEE802154_ATTR_CSMA_RETRIES,
			       params.csma_retries) ||
		    nla_put_u8(msg, IEEE802154_ATTR_CSMA_MIN_BE,
			       params.min_be) ||
		    nla_put_u8(msg, IEEE802154_ATTR_CSMA_MAX_BE,
			       params.max_be) ||
		    nla_put_s8(msg, IEEE802154_ATTR_FRAME_RETRIES,
			       params.frame_retries))
			जाओ nla_put_failure;
	पूर्ण

	wpan_phy_put(phy);
	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	wpan_phy_put(phy);
	genlmsg_cancel(msg, hdr);
out:
	वापस -EMSGSIZE;
पूर्ण

/* Requests from userspace */
अटल काष्ठा net_device *ieee802154_nl_get_dev(काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev;

	अगर (info->attrs[IEEE802154_ATTR_DEV_NAME]) अणु
		अक्षर name[IFNAMSIZ + 1];

		nla_strscpy(name, info->attrs[IEEE802154_ATTR_DEV_NAME],
			    माप(name));
		dev = dev_get_by_name(&init_net, name);
	पूर्ण अन्यथा अगर (info->attrs[IEEE802154_ATTR_DEV_INDEX]) अणु
		dev = dev_get_by_index(&init_net,
			nla_get_u32(info->attrs[IEEE802154_ATTR_DEV_INDEX]));
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	अगर (!dev)
		वापस शून्य;

	अगर (dev->type != ARPHRD_IEEE802154) अणु
		dev_put(dev);
		वापस शून्य;
	पूर्ण

	वापस dev;
पूर्ण

पूर्णांक ieee802154_associate_req(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev;
	काष्ठा ieee802154_addr addr;
	u8 page;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (!info->attrs[IEEE802154_ATTR_CHANNEL] ||
	    !info->attrs[IEEE802154_ATTR_COORD_PAN_ID] ||
	    (!info->attrs[IEEE802154_ATTR_COORD_HW_ADDR] &&
		!info->attrs[IEEE802154_ATTR_COORD_SHORT_ADDR]) ||
	    !info->attrs[IEEE802154_ATTR_CAPABILITY])
		वापस -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;
	अगर (!ieee802154_mlme_ops(dev)->assoc_req)
		जाओ out;

	अगर (info->attrs[IEEE802154_ATTR_COORD_HW_ADDR]) अणु
		addr.mode = IEEE802154_ADDR_LONG;
		addr.extended_addr = nla_get_hwaddr(
				info->attrs[IEEE802154_ATTR_COORD_HW_ADDR]);
	पूर्ण अन्यथा अणु
		addr.mode = IEEE802154_ADDR_SHORT;
		addr.लघु_addr = nla_get_लघुaddr(
				info->attrs[IEEE802154_ATTR_COORD_SHORT_ADDR]);
	पूर्ण
	addr.pan_id = nla_get_लघुaddr(
			info->attrs[IEEE802154_ATTR_COORD_PAN_ID]);

	अगर (info->attrs[IEEE802154_ATTR_PAGE])
		page = nla_get_u8(info->attrs[IEEE802154_ATTR_PAGE]);
	अन्यथा
		page = 0;

	ret = ieee802154_mlme_ops(dev)->assoc_req(dev, &addr,
			nla_get_u8(info->attrs[IEEE802154_ATTR_CHANNEL]),
			page,
			nla_get_u8(info->attrs[IEEE802154_ATTR_CAPABILITY]));

out:
	dev_put(dev);
	वापस ret;
पूर्ण

पूर्णांक ieee802154_associate_resp(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev;
	काष्ठा ieee802154_addr addr;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (!info->attrs[IEEE802154_ATTR_STATUS] ||
	    !info->attrs[IEEE802154_ATTR_DEST_HW_ADDR] ||
	    !info->attrs[IEEE802154_ATTR_DEST_SHORT_ADDR])
		वापस -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;
	अगर (!ieee802154_mlme_ops(dev)->assoc_resp)
		जाओ out;

	addr.mode = IEEE802154_ADDR_LONG;
	addr.extended_addr = nla_get_hwaddr(
			info->attrs[IEEE802154_ATTR_DEST_HW_ADDR]);
	rtnl_lock();
	addr.pan_id = dev->ieee802154_ptr->pan_id;
	rtnl_unlock();

	ret = ieee802154_mlme_ops(dev)->assoc_resp(dev, &addr,
		nla_get_लघुaddr(info->attrs[IEEE802154_ATTR_DEST_SHORT_ADDR]),
		nla_get_u8(info->attrs[IEEE802154_ATTR_STATUS]));

out:
	dev_put(dev);
	वापस ret;
पूर्ण

पूर्णांक ieee802154_disassociate_req(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev;
	काष्ठा ieee802154_addr addr;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर ((!info->attrs[IEEE802154_ATTR_DEST_HW_ADDR] &&
	    !info->attrs[IEEE802154_ATTR_DEST_SHORT_ADDR]) ||
	    !info->attrs[IEEE802154_ATTR_REASON])
		वापस -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;
	अगर (!ieee802154_mlme_ops(dev)->disassoc_req)
		जाओ out;

	अगर (info->attrs[IEEE802154_ATTR_DEST_HW_ADDR]) अणु
		addr.mode = IEEE802154_ADDR_LONG;
		addr.extended_addr = nla_get_hwaddr(
				info->attrs[IEEE802154_ATTR_DEST_HW_ADDR]);
	पूर्ण अन्यथा अणु
		addr.mode = IEEE802154_ADDR_SHORT;
		addr.लघु_addr = nla_get_लघुaddr(
				info->attrs[IEEE802154_ATTR_DEST_SHORT_ADDR]);
	पूर्ण
	rtnl_lock();
	addr.pan_id = dev->ieee802154_ptr->pan_id;
	rtnl_unlock();

	ret = ieee802154_mlme_ops(dev)->disassoc_req(dev, &addr,
			nla_get_u8(info->attrs[IEEE802154_ATTR_REASON]));

out:
	dev_put(dev);
	वापस ret;
पूर्ण

/* PANid, channel, beacon_order = 15, superframe_order = 15,
 * PAN_coordinator, battery_lअगरe_extension = 0,
 * coord_realignment = 0, security_enable = 0
*/
पूर्णांक ieee802154_start_req(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev;
	काष्ठा ieee802154_addr addr;

	u8 channel, bcn_ord, sf_ord;
	u8 page;
	पूर्णांक pan_coord, blx, coord_realign;
	पूर्णांक ret = -EBUSY;

	अगर (!info->attrs[IEEE802154_ATTR_COORD_PAN_ID] ||
	    !info->attrs[IEEE802154_ATTR_COORD_SHORT_ADDR] ||
	    !info->attrs[IEEE802154_ATTR_CHANNEL] ||
	    !info->attrs[IEEE802154_ATTR_BCN_ORD] ||
	    !info->attrs[IEEE802154_ATTR_SF_ORD] ||
	    !info->attrs[IEEE802154_ATTR_PAN_COORD] ||
	    !info->attrs[IEEE802154_ATTR_BAT_EXT] ||
	    !info->attrs[IEEE802154_ATTR_COORD_REALIGN]
	 )
		वापस -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;

	अगर (netअगर_running(dev))
		जाओ out;

	अगर (!ieee802154_mlme_ops(dev)->start_req) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	addr.mode = IEEE802154_ADDR_SHORT;
	addr.लघु_addr = nla_get_लघुaddr(
			info->attrs[IEEE802154_ATTR_COORD_SHORT_ADDR]);
	addr.pan_id = nla_get_लघुaddr(
			info->attrs[IEEE802154_ATTR_COORD_PAN_ID]);

	channel = nla_get_u8(info->attrs[IEEE802154_ATTR_CHANNEL]);
	bcn_ord = nla_get_u8(info->attrs[IEEE802154_ATTR_BCN_ORD]);
	sf_ord = nla_get_u8(info->attrs[IEEE802154_ATTR_SF_ORD]);
	pan_coord = nla_get_u8(info->attrs[IEEE802154_ATTR_PAN_COORD]);
	blx = nla_get_u8(info->attrs[IEEE802154_ATTR_BAT_EXT]);
	coord_realign = nla_get_u8(info->attrs[IEEE802154_ATTR_COORD_REALIGN]);

	अगर (info->attrs[IEEE802154_ATTR_PAGE])
		page = nla_get_u8(info->attrs[IEEE802154_ATTR_PAGE]);
	अन्यथा
		page = 0;

	अगर (addr.लघु_addr == cpu_to_le16(IEEE802154_ADDR_BROADCAST)) अणु
		ieee802154_nl_start_confirm(dev, IEEE802154_NO_SHORT_ADDRESS);
		dev_put(dev);
		वापस -EINVAL;
	पूर्ण

	rtnl_lock();
	ret = ieee802154_mlme_ops(dev)->start_req(dev, &addr, channel, page,
		bcn_ord, sf_ord, pan_coord, blx, coord_realign);
	rtnl_unlock();

	/* FIXME: add validation क्रम unused parameters to be sane
	 * क्रम SoftMAC
	 */
	ieee802154_nl_start_confirm(dev, IEEE802154_SUCCESS);

out:
	dev_put(dev);
	वापस ret;
पूर्ण

पूर्णांक ieee802154_scan_req(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev;
	पूर्णांक ret = -EOPNOTSUPP;
	u8 type;
	u32 channels;
	u8 duration;
	u8 page;

	अगर (!info->attrs[IEEE802154_ATTR_SCAN_TYPE] ||
	    !info->attrs[IEEE802154_ATTR_CHANNELS] ||
	    !info->attrs[IEEE802154_ATTR_DURATION])
		वापस -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;
	अगर (!ieee802154_mlme_ops(dev)->scan_req)
		जाओ out;

	type = nla_get_u8(info->attrs[IEEE802154_ATTR_SCAN_TYPE]);
	channels = nla_get_u32(info->attrs[IEEE802154_ATTR_CHANNELS]);
	duration = nla_get_u8(info->attrs[IEEE802154_ATTR_DURATION]);

	अगर (info->attrs[IEEE802154_ATTR_PAGE])
		page = nla_get_u8(info->attrs[IEEE802154_ATTR_PAGE]);
	अन्यथा
		page = 0;

	ret = ieee802154_mlme_ops(dev)->scan_req(dev, type, channels,
						 page, duration);

out:
	dev_put(dev);
	वापस ret;
पूर्ण

पूर्णांक ieee802154_list_अगरace(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	/* Request क्रम पूर्णांकerface name, index, type, IEEE address,
	 * PAN Id, लघु address
	 */
	काष्ठा sk_buff *msg;
	काष्ठा net_device *dev = शून्य;
	पूर्णांक rc = -ENOBUFS;

	pr_debug("%s\n", __func__);

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		जाओ out_dev;

	rc = ieee802154_nl_fill_अगरace(msg, info->snd_portid, info->snd_seq,
				      0, dev);
	अगर (rc < 0)
		जाओ out_मुक्त;

	dev_put(dev);

	वापस genlmsg_reply(msg, info);
out_मुक्त:
	nlmsg_मुक्त(msg);
out_dev:
	dev_put(dev);
	वापस rc;
पूर्ण

पूर्णांक ieee802154_dump_अगरace(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net_device *dev;
	पूर्णांक idx;
	पूर्णांक s_idx = cb->args[0];

	pr_debug("%s\n", __func__);

	idx = 0;
	क्रम_each_netdev(net, dev) अणु
		अगर (idx < s_idx || dev->type != ARPHRD_IEEE802154)
			जाओ cont;

		अगर (ieee802154_nl_fill_अगरace(skb, NETLINK_CB(cb->skb).portid,
					     cb->nlh->nlmsg_seq,
					     NLM_F_MULTI, dev) < 0)
			अवरोध;
cont:
		idx++;
	पूर्ण
	cb->args[0] = idx;

	वापस skb->len;
पूर्ण

पूर्णांक ieee802154_set_macparams(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा ieee802154_mlme_ops *ops;
	काष्ठा ieee802154_mac_params params;
	काष्ठा wpan_phy *phy;
	पूर्णांक rc = -EINVAL;

	pr_debug("%s\n", __func__);

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;

	ops = ieee802154_mlme_ops(dev);

	अगर (!ops->get_mac_params || !ops->set_mac_params) अणु
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (!info->attrs[IEEE802154_ATTR_LBT_ENABLED] &&
	    !info->attrs[IEEE802154_ATTR_CCA_MODE] &&
	    !info->attrs[IEEE802154_ATTR_CCA_ED_LEVEL] &&
	    !info->attrs[IEEE802154_ATTR_CSMA_RETRIES] &&
	    !info->attrs[IEEE802154_ATTR_CSMA_MIN_BE] &&
	    !info->attrs[IEEE802154_ATTR_CSMA_MAX_BE] &&
	    !info->attrs[IEEE802154_ATTR_FRAME_RETRIES])
		जाओ out;

	phy = dev->ieee802154_ptr->wpan_phy;
	get_device(&phy->dev);

	rtnl_lock();
	ops->get_mac_params(dev, &params);

	अगर (info->attrs[IEEE802154_ATTR_TXPOWER])
		params.transmit_घातer = nla_get_s8(info->attrs[IEEE802154_ATTR_TXPOWER]) * 100;

	अगर (info->attrs[IEEE802154_ATTR_LBT_ENABLED])
		params.lbt = nla_get_u8(info->attrs[IEEE802154_ATTR_LBT_ENABLED]);

	अगर (info->attrs[IEEE802154_ATTR_CCA_MODE])
		params.cca.mode = nla_get_u8(info->attrs[IEEE802154_ATTR_CCA_MODE]);

	अगर (info->attrs[IEEE802154_ATTR_CCA_ED_LEVEL])
		params.cca_ed_level = nla_get_s32(info->attrs[IEEE802154_ATTR_CCA_ED_LEVEL]) * 100;

	अगर (info->attrs[IEEE802154_ATTR_CSMA_RETRIES])
		params.csma_retries = nla_get_u8(info->attrs[IEEE802154_ATTR_CSMA_RETRIES]);

	अगर (info->attrs[IEEE802154_ATTR_CSMA_MIN_BE])
		params.min_be = nla_get_u8(info->attrs[IEEE802154_ATTR_CSMA_MIN_BE]);

	अगर (info->attrs[IEEE802154_ATTR_CSMA_MAX_BE])
		params.max_be = nla_get_u8(info->attrs[IEEE802154_ATTR_CSMA_MAX_BE]);

	अगर (info->attrs[IEEE802154_ATTR_FRAME_RETRIES])
		params.frame_retries = nla_get_s8(info->attrs[IEEE802154_ATTR_FRAME_RETRIES]);

	rc = ops->set_mac_params(dev, &params);
	rtnl_unlock();

	wpan_phy_put(phy);
	dev_put(dev);

	वापस 0;

out:
	dev_put(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक
ieee802154_llsec_parse_key_id(काष्ठा genl_info *info,
			      काष्ठा ieee802154_llsec_key_id *desc)
अणु
	स_रखो(desc, 0, माप(*desc));

	अगर (!info->attrs[IEEE802154_ATTR_LLSEC_KEY_MODE])
		वापस -EINVAL;

	desc->mode = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_KEY_MODE]);

	अगर (desc->mode == IEEE802154_SCF_KEY_IMPLICIT) अणु
		अगर (!info->attrs[IEEE802154_ATTR_PAN_ID])
			वापस -EINVAL;

		desc->device_addr.pan_id = nla_get_लघुaddr(info->attrs[IEEE802154_ATTR_PAN_ID]);

		अगर (info->attrs[IEEE802154_ATTR_SHORT_ADDR]) अणु
			desc->device_addr.mode = IEEE802154_ADDR_SHORT;
			desc->device_addr.लघु_addr = nla_get_लघुaddr(info->attrs[IEEE802154_ATTR_SHORT_ADDR]);
		पूर्ण अन्यथा अणु
			अगर (!info->attrs[IEEE802154_ATTR_HW_ADDR])
				वापस -EINVAL;

			desc->device_addr.mode = IEEE802154_ADDR_LONG;
			desc->device_addr.extended_addr = nla_get_hwaddr(info->attrs[IEEE802154_ATTR_HW_ADDR]);
		पूर्ण
	पूर्ण

	अगर (desc->mode != IEEE802154_SCF_KEY_IMPLICIT &&
	    !info->attrs[IEEE802154_ATTR_LLSEC_KEY_ID])
		वापस -EINVAL;

	अगर (desc->mode == IEEE802154_SCF_KEY_SHORT_INDEX &&
	    !info->attrs[IEEE802154_ATTR_LLSEC_KEY_SOURCE_SHORT])
		वापस -EINVAL;

	अगर (desc->mode == IEEE802154_SCF_KEY_HW_INDEX &&
	    !info->attrs[IEEE802154_ATTR_LLSEC_KEY_SOURCE_EXTENDED])
		वापस -EINVAL;

	अगर (desc->mode != IEEE802154_SCF_KEY_IMPLICIT)
		desc->id = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_KEY_ID]);

	चयन (desc->mode) अणु
	हाल IEEE802154_SCF_KEY_SHORT_INDEX:
	अणु
		u32 source = nla_get_u32(info->attrs[IEEE802154_ATTR_LLSEC_KEY_SOURCE_SHORT]);

		desc->लघु_source = cpu_to_le32(source);
		अवरोध;
	पूर्ण
	हाल IEEE802154_SCF_KEY_HW_INDEX:
		desc->extended_source = nla_get_hwaddr(info->attrs[IEEE802154_ATTR_LLSEC_KEY_SOURCE_EXTENDED]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ieee802154_llsec_fill_key_id(काष्ठा sk_buff *msg,
			     स्थिर काष्ठा ieee802154_llsec_key_id *desc)
अणु
	अगर (nla_put_u8(msg, IEEE802154_ATTR_LLSEC_KEY_MODE, desc->mode))
		वापस -EMSGSIZE;

	अगर (desc->mode == IEEE802154_SCF_KEY_IMPLICIT) अणु
		अगर (nla_put_लघुaddr(msg, IEEE802154_ATTR_PAN_ID,
				      desc->device_addr.pan_id))
			वापस -EMSGSIZE;

		अगर (desc->device_addr.mode == IEEE802154_ADDR_SHORT &&
		    nla_put_लघुaddr(msg, IEEE802154_ATTR_SHORT_ADDR,
				      desc->device_addr.लघु_addr))
			वापस -EMSGSIZE;

		अगर (desc->device_addr.mode == IEEE802154_ADDR_LONG &&
		    nla_put_hwaddr(msg, IEEE802154_ATTR_HW_ADDR,
				   desc->device_addr.extended_addr,
				   IEEE802154_ATTR_PAD))
			वापस -EMSGSIZE;
	पूर्ण

	अगर (desc->mode != IEEE802154_SCF_KEY_IMPLICIT &&
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_KEY_ID, desc->id))
		वापस -EMSGSIZE;

	अगर (desc->mode == IEEE802154_SCF_KEY_SHORT_INDEX &&
	    nla_put_u32(msg, IEEE802154_ATTR_LLSEC_KEY_SOURCE_SHORT,
			le32_to_cpu(desc->लघु_source)))
		वापस -EMSGSIZE;

	अगर (desc->mode == IEEE802154_SCF_KEY_HW_INDEX &&
	    nla_put_hwaddr(msg, IEEE802154_ATTR_LLSEC_KEY_SOURCE_EXTENDED,
			   desc->extended_source, IEEE802154_ATTR_PAD))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

पूर्णांक ieee802154_llsec_getparams(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा net_device *dev = शून्य;
	पूर्णांक rc = -ENOBUFS;
	काष्ठा ieee802154_mlme_ops *ops;
	व्योम *hdr;
	काष्ठा ieee802154_llsec_params params;

	pr_debug("%s\n", __func__);

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;

	ops = ieee802154_mlme_ops(dev);
	अगर (!ops->llsec) अणु
		rc = -EOPNOTSUPP;
		जाओ out_dev;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		जाओ out_dev;

	hdr = genlmsg_put(msg, 0, info->snd_seq, &nl802154_family, 0,
			  IEEE802154_LLSEC_GETPARAMS);
	अगर (!hdr)
		जाओ out_मुक्त;

	rc = ops->llsec->get_params(dev, &params);
	अगर (rc < 0)
		जाओ out_मुक्त;

	अगर (nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name) ||
	    nla_put_u32(msg, IEEE802154_ATTR_DEV_INDEX, dev->अगरindex) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_ENABLED, params.enabled) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_SECLEVEL, params.out_level) ||
	    nla_put_u32(msg, IEEE802154_ATTR_LLSEC_FRAME_COUNTER,
			be32_to_cpu(params.frame_counter)) ||
	    ieee802154_llsec_fill_key_id(msg, &params.out_key)) अणु
		rc = -ENOBUFS;
		जाओ out_मुक्त;
	पूर्ण

	dev_put(dev);

	वापस ieee802154_nl_reply(msg, info);
out_मुक्त:
	nlmsg_मुक्त(msg);
out_dev:
	dev_put(dev);
	वापस rc;
पूर्ण

पूर्णांक ieee802154_llsec_setparams(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev = शून्य;
	पूर्णांक rc = -EINVAL;
	काष्ठा ieee802154_mlme_ops *ops;
	काष्ठा ieee802154_llsec_params params;
	पूर्णांक changed = 0;

	pr_debug("%s\n", __func__);

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;

	अगर (!info->attrs[IEEE802154_ATTR_LLSEC_ENABLED] &&
	    !info->attrs[IEEE802154_ATTR_LLSEC_KEY_MODE] &&
	    !info->attrs[IEEE802154_ATTR_LLSEC_SECLEVEL])
		जाओ out;

	ops = ieee802154_mlme_ops(dev);
	अगर (!ops->llsec) अणु
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (info->attrs[IEEE802154_ATTR_LLSEC_SECLEVEL] &&
	    nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_SECLEVEL]) > 7)
		जाओ out;

	अगर (info->attrs[IEEE802154_ATTR_LLSEC_ENABLED]) अणु
		params.enabled = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_ENABLED]);
		changed |= IEEE802154_LLSEC_PARAM_ENABLED;
	पूर्ण

	अगर (info->attrs[IEEE802154_ATTR_LLSEC_KEY_MODE]) अणु
		अगर (ieee802154_llsec_parse_key_id(info, &params.out_key))
			जाओ out;

		changed |= IEEE802154_LLSEC_PARAM_OUT_KEY;
	पूर्ण

	अगर (info->attrs[IEEE802154_ATTR_LLSEC_SECLEVEL]) अणु
		params.out_level = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_SECLEVEL]);
		changed |= IEEE802154_LLSEC_PARAM_OUT_LEVEL;
	पूर्ण

	अगर (info->attrs[IEEE802154_ATTR_LLSEC_FRAME_COUNTER]) अणु
		u32 fc = nla_get_u32(info->attrs[IEEE802154_ATTR_LLSEC_FRAME_COUNTER]);

		params.frame_counter = cpu_to_be32(fc);
		changed |= IEEE802154_LLSEC_PARAM_FRAME_COUNTER;
	पूर्ण

	rc = ops->llsec->set_params(dev, &params, changed);

	dev_put(dev);

	वापस rc;
out:
	dev_put(dev);
	वापस rc;
पूर्ण

काष्ठा llsec_dump_data अणु
	काष्ठा sk_buff *skb;
	पूर्णांक s_idx, s_idx2;
	पूर्णांक portid;
	पूर्णांक nlmsg_seq;
	काष्ठा net_device *dev;
	काष्ठा ieee802154_mlme_ops *ops;
	काष्ठा ieee802154_llsec_table *table;
पूर्ण;

अटल पूर्णांक
ieee802154_llsec_dump_table(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			    पूर्णांक (*step)(काष्ठा llsec_dump_data *))
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net_device *dev;
	काष्ठा llsec_dump_data data;
	पूर्णांक idx = 0;
	पूर्णांक first_dev = cb->args[0];
	पूर्णांक rc;

	क्रम_each_netdev(net, dev) अणु
		अगर (idx < first_dev || dev->type != ARPHRD_IEEE802154)
			जाओ skip;

		data.ops = ieee802154_mlme_ops(dev);
		अगर (!data.ops->llsec)
			जाओ skip;

		data.skb = skb;
		data.s_idx = cb->args[1];
		data.s_idx2 = cb->args[2];
		data.dev = dev;
		data.portid = NETLINK_CB(cb->skb).portid;
		data.nlmsg_seq = cb->nlh->nlmsg_seq;

		data.ops->llsec->lock_table(dev);
		data.ops->llsec->get_table(data.dev, &data.table);
		rc = step(&data);
		data.ops->llsec->unlock_table(dev);

		अगर (rc < 0)
			अवरोध;

skip:
		idx++;
	पूर्ण
	cb->args[0] = idx;

	वापस skb->len;
पूर्ण

अटल पूर्णांक
ieee802154_nl_llsec_change(काष्ठा sk_buff *skb, काष्ठा genl_info *info,
			   पूर्णांक (*fn)(काष्ठा net_device*, काष्ठा genl_info*))
अणु
	काष्ठा net_device *dev = शून्य;
	पूर्णांक rc = -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	अगर (!dev)
		वापस -ENODEV;

	अगर (!ieee802154_mlme_ops(dev)->llsec)
		rc = -EOPNOTSUPP;
	अन्यथा
		rc = fn(dev, info);

	dev_put(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक
ieee802154_llsec_parse_key(काष्ठा genl_info *info,
			   काष्ठा ieee802154_llsec_key *key)
अणु
	u8 frames;
	u32 commands[256 / 32];

	स_रखो(key, 0, माप(*key));

	अगर (!info->attrs[IEEE802154_ATTR_LLSEC_KEY_USAGE_FRAME_TYPES] ||
	    !info->attrs[IEEE802154_ATTR_LLSEC_KEY_BYTES])
		वापस -EINVAL;

	frames = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_KEY_USAGE_FRAME_TYPES]);
	अगर ((frames & BIT(IEEE802154_FC_TYPE_MAC_CMD)) &&
	    !info->attrs[IEEE802154_ATTR_LLSEC_KEY_USAGE_COMMANDS])
		वापस -EINVAL;

	अगर (info->attrs[IEEE802154_ATTR_LLSEC_KEY_USAGE_COMMANDS]) अणु
		nla_स_नकल(commands,
			   info->attrs[IEEE802154_ATTR_LLSEC_KEY_USAGE_COMMANDS],
			   256 / 8);

		अगर (commands[0] || commands[1] || commands[2] || commands[3] ||
		    commands[4] || commands[5] || commands[6] ||
		    commands[7] >= BIT(IEEE802154_CMD_GTS_REQ + 1))
			वापस -EINVAL;

		key->cmd_frame_ids = commands[7];
	पूर्ण

	key->frame_types = frames;

	nla_स_नकल(key->key, info->attrs[IEEE802154_ATTR_LLSEC_KEY_BYTES],
		   IEEE802154_LLSEC_KEY_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक llsec_add_key(काष्ठा net_device *dev, काष्ठा genl_info *info)
अणु
	काष्ठा ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	काष्ठा ieee802154_llsec_key key;
	काष्ठा ieee802154_llsec_key_id id;

	अगर (ieee802154_llsec_parse_key(info, &key) ||
	    ieee802154_llsec_parse_key_id(info, &id))
		वापस -EINVAL;

	वापस ops->llsec->add_key(dev, &id, &key);
पूर्ण

पूर्णांक ieee802154_llsec_add_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अगर ((info->nlhdr->nlmsg_flags & (NLM_F_CREATE | NLM_F_EXCL)) !=
	    (NLM_F_CREATE | NLM_F_EXCL))
		वापस -EINVAL;

	वापस ieee802154_nl_llsec_change(skb, info, llsec_add_key);
पूर्ण

अटल पूर्णांक llsec_हटाओ_key(काष्ठा net_device *dev, काष्ठा genl_info *info)
अणु
	काष्ठा ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	काष्ठा ieee802154_llsec_key_id id;

	अगर (ieee802154_llsec_parse_key_id(info, &id))
		वापस -EINVAL;

	वापस ops->llsec->del_key(dev, &id);
पूर्ण

पूर्णांक ieee802154_llsec_del_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस ieee802154_nl_llsec_change(skb, info, llsec_हटाओ_key);
पूर्ण

अटल पूर्णांक
ieee802154_nl_fill_key(काष्ठा sk_buff *msg, u32 portid, u32 seq,
		       स्थिर काष्ठा ieee802154_llsec_key_entry *key,
		       स्थिर काष्ठा net_device *dev)
अणु
	व्योम *hdr;
	u32 commands[256 / 32];

	hdr = genlmsg_put(msg, 0, seq, &nl802154_family, NLM_F_MULTI,
			  IEEE802154_LLSEC_LIST_KEY);
	अगर (!hdr)
		जाओ out;

	अगर (nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name) ||
	    nla_put_u32(msg, IEEE802154_ATTR_DEV_INDEX, dev->अगरindex) ||
	    ieee802154_llsec_fill_key_id(msg, &key->id) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_KEY_USAGE_FRAME_TYPES,
		       key->key->frame_types))
		जाओ nla_put_failure;

	अगर (key->key->frame_types & BIT(IEEE802154_FC_TYPE_MAC_CMD)) अणु
		स_रखो(commands, 0, माप(commands));
		commands[7] = key->key->cmd_frame_ids;
		अगर (nla_put(msg, IEEE802154_ATTR_LLSEC_KEY_USAGE_COMMANDS,
			    माप(commands), commands))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put(msg, IEEE802154_ATTR_LLSEC_KEY_BYTES,
		    IEEE802154_LLSEC_KEY_SIZE, key->key->key))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
out:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक llsec_iter_keys(काष्ठा llsec_dump_data *data)
अणु
	काष्ठा ieee802154_llsec_key_entry *pos;
	पूर्णांक rc = 0, idx = 0;

	list_क्रम_each_entry(pos, &data->table->keys, list) अणु
		अगर (idx++ < data->s_idx)
			जारी;

		अगर (ieee802154_nl_fill_key(data->skb, data->portid,
					   data->nlmsg_seq, pos, data->dev)) अणु
			rc = -EMSGSIZE;
			अवरोध;
		पूर्ण

		data->s_idx++;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक ieee802154_llsec_dump_keys(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	वापस ieee802154_llsec_dump_table(skb, cb, llsec_iter_keys);
पूर्ण

अटल पूर्णांक
llsec_parse_dev(काष्ठा genl_info *info,
		काष्ठा ieee802154_llsec_device *dev)
अणु
	स_रखो(dev, 0, माप(*dev));

	अगर (!info->attrs[IEEE802154_ATTR_LLSEC_FRAME_COUNTER] ||
	    !info->attrs[IEEE802154_ATTR_HW_ADDR] ||
	    !info->attrs[IEEE802154_ATTR_LLSEC_DEV_OVERRIDE] ||
	    !info->attrs[IEEE802154_ATTR_LLSEC_DEV_KEY_MODE] ||
	    (!!info->attrs[IEEE802154_ATTR_PAN_ID] !=
	     !!info->attrs[IEEE802154_ATTR_SHORT_ADDR]))
		वापस -EINVAL;

	अगर (info->attrs[IEEE802154_ATTR_PAN_ID]) अणु
		dev->pan_id = nla_get_लघुaddr(info->attrs[IEEE802154_ATTR_PAN_ID]);
		dev->लघु_addr = nla_get_लघुaddr(info->attrs[IEEE802154_ATTR_SHORT_ADDR]);
	पूर्ण अन्यथा अणु
		dev->लघु_addr = cpu_to_le16(IEEE802154_ADDR_UNDEF);
	पूर्ण

	dev->hwaddr = nla_get_hwaddr(info->attrs[IEEE802154_ATTR_HW_ADDR]);
	dev->frame_counter = nla_get_u32(info->attrs[IEEE802154_ATTR_LLSEC_FRAME_COUNTER]);
	dev->seclevel_exempt = !!nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_DEV_OVERRIDE]);
	dev->key_mode = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_DEV_KEY_MODE]);

	अगर (dev->key_mode >= __IEEE802154_LLSEC_DEVKEY_MAX)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक llsec_add_dev(काष्ठा net_device *dev, काष्ठा genl_info *info)
अणु
	काष्ठा ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	काष्ठा ieee802154_llsec_device desc;

	अगर (llsec_parse_dev(info, &desc))
		वापस -EINVAL;

	वापस ops->llsec->add_dev(dev, &desc);
पूर्ण

पूर्णांक ieee802154_llsec_add_dev(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अगर ((info->nlhdr->nlmsg_flags & (NLM_F_CREATE | NLM_F_EXCL)) !=
	    (NLM_F_CREATE | NLM_F_EXCL))
		वापस -EINVAL;

	वापस ieee802154_nl_llsec_change(skb, info, llsec_add_dev);
पूर्ण

अटल पूर्णांक llsec_del_dev(काष्ठा net_device *dev, काष्ठा genl_info *info)
अणु
	काष्ठा ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	__le64 devaddr;

	अगर (!info->attrs[IEEE802154_ATTR_HW_ADDR])
		वापस -EINVAL;

	devaddr = nla_get_hwaddr(info->attrs[IEEE802154_ATTR_HW_ADDR]);

	वापस ops->llsec->del_dev(dev, devaddr);
पूर्ण

पूर्णांक ieee802154_llsec_del_dev(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस ieee802154_nl_llsec_change(skb, info, llsec_del_dev);
पूर्ण

अटल पूर्णांक
ieee802154_nl_fill_dev(काष्ठा sk_buff *msg, u32 portid, u32 seq,
		       स्थिर काष्ठा ieee802154_llsec_device *desc,
		       स्थिर काष्ठा net_device *dev)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, 0, seq, &nl802154_family, NLM_F_MULTI,
			  IEEE802154_LLSEC_LIST_DEV);
	अगर (!hdr)
		जाओ out;

	अगर (nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name) ||
	    nla_put_u32(msg, IEEE802154_ATTR_DEV_INDEX, dev->अगरindex) ||
	    nla_put_लघुaddr(msg, IEEE802154_ATTR_PAN_ID, desc->pan_id) ||
	    nla_put_लघुaddr(msg, IEEE802154_ATTR_SHORT_ADDR,
			      desc->लघु_addr) ||
	    nla_put_hwaddr(msg, IEEE802154_ATTR_HW_ADDR, desc->hwaddr,
			   IEEE802154_ATTR_PAD) ||
	    nla_put_u32(msg, IEEE802154_ATTR_LLSEC_FRAME_COUNTER,
			desc->frame_counter) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_DEV_OVERRIDE,
		       desc->seclevel_exempt) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_DEV_KEY_MODE, desc->key_mode))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
out:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक llsec_iter_devs(काष्ठा llsec_dump_data *data)
अणु
	काष्ठा ieee802154_llsec_device *pos;
	पूर्णांक rc = 0, idx = 0;

	list_क्रम_each_entry(pos, &data->table->devices, list) अणु
		अगर (idx++ < data->s_idx)
			जारी;

		अगर (ieee802154_nl_fill_dev(data->skb, data->portid,
					   data->nlmsg_seq, pos, data->dev)) अणु
			rc = -EMSGSIZE;
			अवरोध;
		पूर्ण

		data->s_idx++;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक ieee802154_llsec_dump_devs(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	वापस ieee802154_llsec_dump_table(skb, cb, llsec_iter_devs);
पूर्ण

अटल पूर्णांक llsec_add_devkey(काष्ठा net_device *dev, काष्ठा genl_info *info)
अणु
	काष्ठा ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	काष्ठा ieee802154_llsec_device_key key;
	__le64 devaddr;

	अगर (!info->attrs[IEEE802154_ATTR_LLSEC_FRAME_COUNTER] ||
	    !info->attrs[IEEE802154_ATTR_HW_ADDR] ||
	    ieee802154_llsec_parse_key_id(info, &key.key_id))
		वापस -EINVAL;

	devaddr = nla_get_hwaddr(info->attrs[IEEE802154_ATTR_HW_ADDR]);
	key.frame_counter = nla_get_u32(info->attrs[IEEE802154_ATTR_LLSEC_FRAME_COUNTER]);

	वापस ops->llsec->add_devkey(dev, devaddr, &key);
पूर्ण

पूर्णांक ieee802154_llsec_add_devkey(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अगर ((info->nlhdr->nlmsg_flags & (NLM_F_CREATE | NLM_F_EXCL)) !=
	    (NLM_F_CREATE | NLM_F_EXCL))
		वापस -EINVAL;

	वापस ieee802154_nl_llsec_change(skb, info, llsec_add_devkey);
पूर्ण

अटल पूर्णांक llsec_del_devkey(काष्ठा net_device *dev, काष्ठा genl_info *info)
अणु
	काष्ठा ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	काष्ठा ieee802154_llsec_device_key key;
	__le64 devaddr;

	अगर (!info->attrs[IEEE802154_ATTR_HW_ADDR] ||
	    ieee802154_llsec_parse_key_id(info, &key.key_id))
		वापस -EINVAL;

	devaddr = nla_get_hwaddr(info->attrs[IEEE802154_ATTR_HW_ADDR]);

	वापस ops->llsec->del_devkey(dev, devaddr, &key);
पूर्ण

पूर्णांक ieee802154_llsec_del_devkey(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस ieee802154_nl_llsec_change(skb, info, llsec_del_devkey);
पूर्ण

अटल पूर्णांक
ieee802154_nl_fill_devkey(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			  __le64 devaddr,
			  स्थिर काष्ठा ieee802154_llsec_device_key *devkey,
			  स्थिर काष्ठा net_device *dev)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, 0, seq, &nl802154_family, NLM_F_MULTI,
			  IEEE802154_LLSEC_LIST_DEVKEY);
	अगर (!hdr)
		जाओ out;

	अगर (nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name) ||
	    nla_put_u32(msg, IEEE802154_ATTR_DEV_INDEX, dev->अगरindex) ||
	    nla_put_hwaddr(msg, IEEE802154_ATTR_HW_ADDR, devaddr,
			   IEEE802154_ATTR_PAD) ||
	    nla_put_u32(msg, IEEE802154_ATTR_LLSEC_FRAME_COUNTER,
			devkey->frame_counter) ||
	    ieee802154_llsec_fill_key_id(msg, &devkey->key_id))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
out:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक llsec_iter_devkeys(काष्ठा llsec_dump_data *data)
अणु
	काष्ठा ieee802154_llsec_device *dpos;
	काष्ठा ieee802154_llsec_device_key *kpos;
	पूर्णांक idx = 0, idx2;

	list_क्रम_each_entry(dpos, &data->table->devices, list) अणु
		अगर (idx++ < data->s_idx)
			जारी;

		idx2 = 0;

		list_क्रम_each_entry(kpos, &dpos->keys, list) अणु
			अगर (idx2++ < data->s_idx2)
				जारी;

			अगर (ieee802154_nl_fill_devkey(data->skb, data->portid,
						      data->nlmsg_seq,
						      dpos->hwaddr, kpos,
						      data->dev)) अणु
				वापस -EMSGSIZE;
			पूर्ण

			data->s_idx2++;
		पूर्ण

		data->s_idx++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ieee802154_llsec_dump_devkeys(काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb)
अणु
	वापस ieee802154_llsec_dump_table(skb, cb, llsec_iter_devkeys);
पूर्ण

अटल पूर्णांक
llsec_parse_seclevel(काष्ठा genl_info *info,
		     काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	स_रखो(sl, 0, माप(*sl));

	अगर (!info->attrs[IEEE802154_ATTR_LLSEC_FRAME_TYPE] ||
	    !info->attrs[IEEE802154_ATTR_LLSEC_SECLEVELS] ||
	    !info->attrs[IEEE802154_ATTR_LLSEC_DEV_OVERRIDE])
		वापस -EINVAL;

	sl->frame_type = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_FRAME_TYPE]);
	अगर (sl->frame_type == IEEE802154_FC_TYPE_MAC_CMD) अणु
		अगर (!info->attrs[IEEE802154_ATTR_LLSEC_CMD_FRAME_ID])
			वापस -EINVAL;

		sl->cmd_frame_id = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_CMD_FRAME_ID]);
	पूर्ण

	sl->sec_levels = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_SECLEVELS]);
	sl->device_override = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_DEV_OVERRIDE]);

	वापस 0;
पूर्ण

अटल पूर्णांक llsec_add_seclevel(काष्ठा net_device *dev, काष्ठा genl_info *info)
अणु
	काष्ठा ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	काष्ठा ieee802154_llsec_seclevel sl;

	अगर (llsec_parse_seclevel(info, &sl))
		वापस -EINVAL;

	वापस ops->llsec->add_seclevel(dev, &sl);
पूर्ण

पूर्णांक ieee802154_llsec_add_seclevel(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अगर ((info->nlhdr->nlmsg_flags & (NLM_F_CREATE | NLM_F_EXCL)) !=
	    (NLM_F_CREATE | NLM_F_EXCL))
		वापस -EINVAL;

	वापस ieee802154_nl_llsec_change(skb, info, llsec_add_seclevel);
पूर्ण

अटल पूर्णांक llsec_del_seclevel(काष्ठा net_device *dev, काष्ठा genl_info *info)
अणु
	काष्ठा ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	काष्ठा ieee802154_llsec_seclevel sl;

	अगर (llsec_parse_seclevel(info, &sl))
		वापस -EINVAL;

	वापस ops->llsec->del_seclevel(dev, &sl);
पूर्ण

पूर्णांक ieee802154_llsec_del_seclevel(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस ieee802154_nl_llsec_change(skb, info, llsec_del_seclevel);
पूर्ण

अटल पूर्णांक
ieee802154_nl_fill_seclevel(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			    स्थिर काष्ठा ieee802154_llsec_seclevel *sl,
			    स्थिर काष्ठा net_device *dev)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, 0, seq, &nl802154_family, NLM_F_MULTI,
			  IEEE802154_LLSEC_LIST_SECLEVEL);
	अगर (!hdr)
		जाओ out;

	अगर (nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name) ||
	    nla_put_u32(msg, IEEE802154_ATTR_DEV_INDEX, dev->अगरindex) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_FRAME_TYPE, sl->frame_type) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_SECLEVELS, sl->sec_levels) ||
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_DEV_OVERRIDE,
		       sl->device_override))
		जाओ nla_put_failure;

	अगर (sl->frame_type == IEEE802154_FC_TYPE_MAC_CMD &&
	    nla_put_u8(msg, IEEE802154_ATTR_LLSEC_CMD_FRAME_ID,
		       sl->cmd_frame_id))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
out:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक llsec_iter_seclevels(काष्ठा llsec_dump_data *data)
अणु
	काष्ठा ieee802154_llsec_seclevel *pos;
	पूर्णांक rc = 0, idx = 0;

	list_क्रम_each_entry(pos, &data->table->security_levels, list) अणु
		अगर (idx++ < data->s_idx)
			जारी;

		अगर (ieee802154_nl_fill_seclevel(data->skb, data->portid,
						data->nlmsg_seq, pos,
						data->dev)) अणु
			rc = -EMSGSIZE;
			अवरोध;
		पूर्ण

		data->s_idx++;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक ieee802154_llsec_dump_seclevels(काष्ठा sk_buff *skb,
				    काष्ठा netlink_callback *cb)
अणु
	वापस ieee802154_llsec_dump_table(skb, cb, llsec_iter_seclevels);
पूर्ण
