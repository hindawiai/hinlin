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

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/cfg802154.h>
#समावेश <net/af_ieee802154.h>
#समावेश <net/ieee802154_netdev.h>
#समावेश <net/rtnetlink.h> /* क्रम rtnl_अणुun,पूर्णlock */
#समावेश <linux/nl802154.h>

#समावेश "ieee802154.h"
#समावेश "rdev-ops.h"
#समावेश "core.h"

अटल पूर्णांक ieee802154_nl_fill_phy(काष्ठा sk_buff *msg, u32 portid,
				  u32 seq, पूर्णांक flags, काष्ठा wpan_phy *phy)
अणु
	व्योम *hdr;
	पूर्णांक i, pages = 0;
	uपूर्णांक32_t *buf = kसुस्मृति(32, माप(uपूर्णांक32_t), GFP_KERNEL);

	pr_debug("%s\n", __func__);

	अगर (!buf)
		वापस -EMSGSIZE;

	hdr = genlmsg_put(msg, 0, seq, &nl802154_family, flags,
			  IEEE802154_LIST_PHY);
	अगर (!hdr)
		जाओ out;

	rtnl_lock();
	अगर (nla_put_string(msg, IEEE802154_ATTR_PHY_NAME, wpan_phy_name(phy)) ||
	    nla_put_u8(msg, IEEE802154_ATTR_PAGE, phy->current_page) ||
	    nla_put_u8(msg, IEEE802154_ATTR_CHANNEL, phy->current_channel))
		जाओ nla_put_failure;
	क्रम (i = 0; i < 32; i++) अणु
		अगर (phy->supported.channels[i])
			buf[pages++] = phy->supported.channels[i] | (i << 27);
	पूर्ण
	अगर (pages &&
	    nla_put(msg, IEEE802154_ATTR_CHANNEL_PAGE_LIST,
		    pages * माप(uपूर्णांक32_t), buf))
		जाओ nla_put_failure;
	rtnl_unlock();
	kमुक्त(buf);
	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	rtnl_unlock();
	genlmsg_cancel(msg, hdr);
out:
	kमुक्त(buf);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक ieee802154_list_phy(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	/* Request क्रम पूर्णांकerface name, index, type, IEEE address,
	 * PAN Id, लघु address
	 */
	काष्ठा sk_buff *msg;
	काष्ठा wpan_phy *phy;
	स्थिर अक्षर *name;
	पूर्णांक rc = -ENOBUFS;

	pr_debug("%s\n", __func__);

	अगर (!info->attrs[IEEE802154_ATTR_PHY_NAME])
		वापस -EINVAL;

	name = nla_data(info->attrs[IEEE802154_ATTR_PHY_NAME]);
	अगर (name[nla_len(info->attrs[IEEE802154_ATTR_PHY_NAME]) - 1] != '\0')
		वापस -EINVAL; /* phy name should be null-terminated */

	phy = wpan_phy_find(name);
	अगर (!phy)
		वापस -ENODEV;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		जाओ out_dev;

	rc = ieee802154_nl_fill_phy(msg, info->snd_portid, info->snd_seq,
				    0, phy);
	अगर (rc < 0)
		जाओ out_मुक्त;

	wpan_phy_put(phy);

	वापस genlmsg_reply(msg, info);
out_मुक्त:
	nlmsg_मुक्त(msg);
out_dev:
	wpan_phy_put(phy);
	वापस rc;
पूर्ण

काष्ठा dump_phy_data अणु
	काष्ठा sk_buff *skb;
	काष्ठा netlink_callback *cb;
	पूर्णांक idx, s_idx;
पूर्ण;

अटल पूर्णांक ieee802154_dump_phy_iter(काष्ठा wpan_phy *phy, व्योम *_data)
अणु
	पूर्णांक rc;
	काष्ठा dump_phy_data *data = _data;

	pr_debug("%s\n", __func__);

	अगर (data->idx++ < data->s_idx)
		वापस 0;

	rc = ieee802154_nl_fill_phy(data->skb,
				    NETLINK_CB(data->cb->skb).portid,
				    data->cb->nlh->nlmsg_seq,
				    NLM_F_MULTI,
				    phy);

	अगर (rc < 0) अणु
		data->idx--;
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ieee802154_dump_phy(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा dump_phy_data data = अणु
		.cb = cb,
		.skb = skb,
		.s_idx = cb->args[0],
		.idx = 0,
	पूर्ण;

	pr_debug("%s\n", __func__);

	wpan_phy_क्रम_each(ieee802154_dump_phy_iter, &data);

	cb->args[0] = data.idx;

	वापस skb->len;
पूर्ण

पूर्णांक ieee802154_add_अगरace(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा wpan_phy *phy;
	स्थिर अक्षर *name;
	स्थिर अक्षर *devname;
	पूर्णांक rc = -ENOBUFS;
	काष्ठा net_device *dev;
	पूर्णांक type = __IEEE802154_DEV_INVALID;
	अचिन्हित अक्षर name_assign_type;

	pr_debug("%s\n", __func__);

	अगर (!info->attrs[IEEE802154_ATTR_PHY_NAME])
		वापस -EINVAL;

	name = nla_data(info->attrs[IEEE802154_ATTR_PHY_NAME]);
	अगर (name[nla_len(info->attrs[IEEE802154_ATTR_PHY_NAME]) - 1] != '\0')
		वापस -EINVAL; /* phy name should be null-terminated */

	अगर (info->attrs[IEEE802154_ATTR_DEV_NAME]) अणु
		devname = nla_data(info->attrs[IEEE802154_ATTR_DEV_NAME]);
		अगर (devname[nla_len(info->attrs[IEEE802154_ATTR_DEV_NAME]) - 1]
				!= '\0')
			वापस -EINVAL; /* phy name should be null-terminated */
		name_assign_type = NET_NAME_USER;
	पूर्ण अन्यथा  अणु
		devname = "wpan%d";
		name_assign_type = NET_NAME_ENUM;
	पूर्ण

	अगर (म_माप(devname) >= IFNAMSIZ)
		वापस -ENAMETOOLONG;

	phy = wpan_phy_find(name);
	अगर (!phy)
		वापस -ENODEV;

	msg = ieee802154_nl_new_reply(info, 0, IEEE802154_ADD_IFACE);
	अगर (!msg)
		जाओ out_dev;

	अगर (info->attrs[IEEE802154_ATTR_HW_ADDR] &&
	    nla_len(info->attrs[IEEE802154_ATTR_HW_ADDR]) !=
			IEEE802154_ADDR_LEN) अणु
		rc = -EINVAL;
		जाओ nla_put_failure;
	पूर्ण

	अगर (info->attrs[IEEE802154_ATTR_DEV_TYPE]) अणु
		type = nla_get_u8(info->attrs[IEEE802154_ATTR_DEV_TYPE]);
		अगर (type >= __IEEE802154_DEV_MAX) अणु
			rc = -EINVAL;
			जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	dev = rdev_add_भव_पूर्णांकf_deprecated(wpan_phy_to_rdev(phy), devname,
					       name_assign_type, type);
	अगर (IS_ERR(dev)) अणु
		rc = PTR_ERR(dev);
		जाओ nla_put_failure;
	पूर्ण
	dev_hold(dev);

	अगर (info->attrs[IEEE802154_ATTR_HW_ADDR]) अणु
		काष्ठा sockaddr addr;

		addr.sa_family = ARPHRD_IEEE802154;
		nla_स_नकल(&addr.sa_data, info->attrs[IEEE802154_ATTR_HW_ADDR],
			   IEEE802154_ADDR_LEN);

		/* strangely enough, some callbacks (inetdev_event) from
		 * dev_set_mac_address require RTNL_LOCK
		 */
		rtnl_lock();
		rc = dev_set_mac_address(dev, &addr, शून्य);
		rtnl_unlock();
		अगर (rc)
			जाओ dev_unरेजिस्टर;
	पूर्ण

	अगर (nla_put_string(msg, IEEE802154_ATTR_PHY_NAME, wpan_phy_name(phy)) ||
	    nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, dev->name)) अणु
		rc = -EMSGSIZE;
		जाओ nla_put_failure;
	पूर्ण
	dev_put(dev);

	wpan_phy_put(phy);

	वापस ieee802154_nl_reply(msg, info);

dev_unरेजिस्टर:
	rtnl_lock(); /* del_अगरace must be called with RTNL lock */
	rdev_del_भव_पूर्णांकf_deprecated(wpan_phy_to_rdev(phy), dev);
	dev_put(dev);
	rtnl_unlock();
nla_put_failure:
	nlmsg_मुक्त(msg);
out_dev:
	wpan_phy_put(phy);
	वापस rc;
पूर्ण

पूर्णांक ieee802154_del_अगरace(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा wpan_phy *phy;
	स्थिर अक्षर *name;
	पूर्णांक rc;
	काष्ठा net_device *dev;

	pr_debug("%s\n", __func__);

	अगर (!info->attrs[IEEE802154_ATTR_DEV_NAME])
		वापस -EINVAL;

	name = nla_data(info->attrs[IEEE802154_ATTR_DEV_NAME]);
	अगर (name[nla_len(info->attrs[IEEE802154_ATTR_DEV_NAME]) - 1] != '\0')
		वापस -EINVAL; /* name should be null-terminated */

	rc = -ENODEV;
	dev = dev_get_by_name(genl_info_net(info), name);
	अगर (!dev)
		वापस rc;
	अगर (dev->type != ARPHRD_IEEE802154)
		जाओ out;

	phy = dev->ieee802154_ptr->wpan_phy;
	BUG_ON(!phy);
	get_device(&phy->dev);

	rc = -EINVAL;
	/* phy name is optional, but should be checked अगर it's given */
	अगर (info->attrs[IEEE802154_ATTR_PHY_NAME]) अणु
		काष्ठा wpan_phy *phy2;

		स्थिर अक्षर *pname =
			nla_data(info->attrs[IEEE802154_ATTR_PHY_NAME]);
		अगर (pname[nla_len(info->attrs[IEEE802154_ATTR_PHY_NAME]) - 1]
				!= '\0')
			/* name should be null-terminated */
			जाओ out_dev;

		phy2 = wpan_phy_find(pname);
		अगर (!phy2)
			जाओ out_dev;

		अगर (phy != phy2) अणु
			wpan_phy_put(phy2);
			जाओ out_dev;
		पूर्ण
	पूर्ण

	rc = -ENOBUFS;

	msg = ieee802154_nl_new_reply(info, 0, IEEE802154_DEL_IFACE);
	अगर (!msg)
		जाओ out_dev;

	rtnl_lock();
	rdev_del_भव_पूर्णांकf_deprecated(wpan_phy_to_rdev(phy), dev);

	/* We करोn't have device anymore */
	dev_put(dev);
	dev = शून्य;

	rtnl_unlock();

	अगर (nla_put_string(msg, IEEE802154_ATTR_PHY_NAME, wpan_phy_name(phy)) ||
	    nla_put_string(msg, IEEE802154_ATTR_DEV_NAME, name))
		जाओ nla_put_failure;
	wpan_phy_put(phy);

	वापस ieee802154_nl_reply(msg, info);

nla_put_failure:
	nlmsg_मुक्त(msg);
out_dev:
	wpan_phy_put(phy);
out:
	अगर (dev)
		dev_put(dev);

	वापस rc;
पूर्ण
