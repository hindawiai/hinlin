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
#समावेश <linux/gfp.h>
#समावेश <net/genetlink.h>
#समावेश <linux/nl802154.h>

#समावेश "ieee802154.h"

अटल अचिन्हित पूर्णांक ieee802154_seq_num;
अटल DEFINE_SPINLOCK(ieee802154_seq_lock);

/* Requests to userspace */
काष्ठा sk_buff *ieee802154_nl_create(पूर्णांक flags, u8 req)
अणु
	व्योम *hdr;
	काष्ठा sk_buff *msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अचिन्हित दीर्घ f;

	अगर (!msg)
		वापस शून्य;

	spin_lock_irqsave(&ieee802154_seq_lock, f);
	hdr = genlmsg_put(msg, 0, ieee802154_seq_num++,
			  &nl802154_family, flags, req);
	spin_unlock_irqrestore(&ieee802154_seq_lock, f);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस शून्य;
	पूर्ण

	वापस msg;
पूर्ण

पूर्णांक ieee802154_nl_mcast(काष्ठा sk_buff *msg, अचिन्हित पूर्णांक group)
अणु
	काष्ठा nlmsghdr *nlh = nlmsg_hdr(msg);
	व्योम *hdr = genlmsg_data(nlmsg_data(nlh));

	genlmsg_end(msg, hdr);

	वापस genlmsg_multicast(&nl802154_family, msg, 0, group, GFP_ATOMIC);
पूर्ण

काष्ठा sk_buff *ieee802154_nl_new_reply(काष्ठा genl_info *info,
					पूर्णांक flags, u8 req)
अणु
	व्योम *hdr;
	काष्ठा sk_buff *msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);

	अगर (!msg)
		वापस शून्य;

	hdr = genlmsg_put_reply(msg, info,
				&nl802154_family, flags, req);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस शून्य;
	पूर्ण

	वापस msg;
पूर्ण

पूर्णांक ieee802154_nl_reply(काष्ठा sk_buff *msg, काष्ठा genl_info *info)
अणु
	काष्ठा nlmsghdr *nlh = nlmsg_hdr(msg);
	व्योम *hdr = genlmsg_data(nlmsg_data(nlh));

	genlmsg_end(msg, hdr);

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल स्थिर काष्ठा genl_small_ops ieee802154_ops[] = अणु
	/* see nl-phy.c */
	IEEE802154_DUMP(IEEE802154_LIST_PHY, ieee802154_list_phy,
			ieee802154_dump_phy),
	IEEE802154_OP(IEEE802154_ADD_IFACE, ieee802154_add_अगरace),
	IEEE802154_OP(IEEE802154_DEL_IFACE, ieee802154_del_अगरace),
	/* see nl-mac.c */
	IEEE802154_OP(IEEE802154_ASSOCIATE_REQ, ieee802154_associate_req),
	IEEE802154_OP(IEEE802154_ASSOCIATE_RESP, ieee802154_associate_resp),
	IEEE802154_OP(IEEE802154_DISASSOCIATE_REQ, ieee802154_disassociate_req),
	IEEE802154_OP(IEEE802154_SCAN_REQ, ieee802154_scan_req),
	IEEE802154_OP(IEEE802154_START_REQ, ieee802154_start_req),
	IEEE802154_DUMP(IEEE802154_LIST_IFACE, ieee802154_list_अगरace,
			ieee802154_dump_अगरace),
	IEEE802154_OP(IEEE802154_SET_MACPARAMS, ieee802154_set_macparams),
	IEEE802154_OP(IEEE802154_LLSEC_GETPARAMS, ieee802154_llsec_getparams),
	IEEE802154_OP(IEEE802154_LLSEC_SETPARAMS, ieee802154_llsec_setparams),
	IEEE802154_DUMP(IEEE802154_LLSEC_LIST_KEY, शून्य,
			ieee802154_llsec_dump_keys),
	IEEE802154_OP(IEEE802154_LLSEC_ADD_KEY, ieee802154_llsec_add_key),
	IEEE802154_OP(IEEE802154_LLSEC_DEL_KEY, ieee802154_llsec_del_key),
	IEEE802154_DUMP(IEEE802154_LLSEC_LIST_DEV, शून्य,
			ieee802154_llsec_dump_devs),
	IEEE802154_OP(IEEE802154_LLSEC_ADD_DEV, ieee802154_llsec_add_dev),
	IEEE802154_OP(IEEE802154_LLSEC_DEL_DEV, ieee802154_llsec_del_dev),
	IEEE802154_DUMP(IEEE802154_LLSEC_LIST_DEVKEY, शून्य,
			ieee802154_llsec_dump_devkeys),
	IEEE802154_OP(IEEE802154_LLSEC_ADD_DEVKEY, ieee802154_llsec_add_devkey),
	IEEE802154_OP(IEEE802154_LLSEC_DEL_DEVKEY, ieee802154_llsec_del_devkey),
	IEEE802154_DUMP(IEEE802154_LLSEC_LIST_SECLEVEL, शून्य,
			ieee802154_llsec_dump_seclevels),
	IEEE802154_OP(IEEE802154_LLSEC_ADD_SECLEVEL,
		      ieee802154_llsec_add_seclevel),
	IEEE802154_OP(IEEE802154_LLSEC_DEL_SECLEVEL,
		      ieee802154_llsec_del_seclevel),
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group ieee802154_mcgrps[] = अणु
	[IEEE802154_COORD_MCGRP] = अणु .name = IEEE802154_MCAST_COORD_NAME, पूर्ण,
	[IEEE802154_BEACON_MCGRP] = अणु .name = IEEE802154_MCAST_BEACON_NAME, पूर्ण,
पूर्ण;

काष्ठा genl_family nl802154_family __ro_after_init = अणु
	.hdrsize	= 0,
	.name		= IEEE802154_NL_NAME,
	.version	= 1,
	.maxattr	= IEEE802154_ATTR_MAX,
	.policy		= ieee802154_policy,
	.module		= THIS_MODULE,
	.small_ops	= ieee802154_ops,
	.n_small_ops	= ARRAY_SIZE(ieee802154_ops),
	.mcgrps		= ieee802154_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(ieee802154_mcgrps),
पूर्ण;

पूर्णांक __init ieee802154_nl_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&nl802154_family);
पूर्ण

व्योम ieee802154_nl_निकास(व्योम)
अणु
	genl_unरेजिस्टर_family(&nl802154_family);
पूर्ण
