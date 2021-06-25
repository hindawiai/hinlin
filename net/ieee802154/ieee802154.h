<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007, 2008, 2009 Siemens AG
 */
#अगर_अघोषित IEEE_802154_LOCAL_H
#घोषणा IEEE_802154_LOCAL_H

पूर्णांक __init ieee802154_nl_init(व्योम);
व्योम ieee802154_nl_निकास(व्योम);

#घोषणा IEEE802154_OP(_cmd, _func)			\
	अणु						\
		.cmd	= _cmd,				\
		.करोit	= _func,			\
		.dumpit	= शून्य,				\
		.flags	= GENL_ADMIN_PERM,		\
	पूर्ण

#घोषणा IEEE802154_DUMP(_cmd, _func, _dump)		\
	अणु						\
		.cmd	= _cmd,				\
		.करोit	= _func,			\
		.dumpit	= _dump,			\
	पूर्ण

काष्ठा genl_info;

काष्ठा sk_buff *ieee802154_nl_create(पूर्णांक flags, u8 req);
पूर्णांक ieee802154_nl_mcast(काष्ठा sk_buff *msg, अचिन्हित पूर्णांक group);
काष्ठा sk_buff *ieee802154_nl_new_reply(काष्ठा genl_info *info,
					पूर्णांक flags, u8 req);
पूर्णांक ieee802154_nl_reply(काष्ठा sk_buff *msg, काष्ठा genl_info *info);

बाह्य काष्ठा genl_family nl802154_family;

/* genetlink ops/groups */
पूर्णांक ieee802154_list_phy(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_dump_phy(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक ieee802154_add_अगरace(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_del_अगरace(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

क्रमागत ieee802154_mcgrp_ids अणु
	IEEE802154_COORD_MCGRP,
	IEEE802154_BEACON_MCGRP,
पूर्ण;

पूर्णांक ieee802154_associate_req(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_associate_resp(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_disassociate_req(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_scan_req(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_start_req(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_list_अगरace(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_dump_अगरace(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);
पूर्णांक ieee802154_set_macparams(काष्ठा sk_buff *skb, काष्ठा genl_info *info);

पूर्णांक ieee802154_llsec_getparams(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_setparams(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_add_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_del_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_dump_keys(काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb);
पूर्णांक ieee802154_llsec_add_dev(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_del_dev(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_dump_devs(काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb);
पूर्णांक ieee802154_llsec_add_devkey(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_del_devkey(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_dump_devkeys(काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb);
पूर्णांक ieee802154_llsec_add_seclevel(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_del_seclevel(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
पूर्णांक ieee802154_llsec_dump_seclevels(काष्ठा sk_buff *skb,
				    काष्ठा netlink_callback *cb);

#पूर्ण_अगर
