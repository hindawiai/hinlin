<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Authors:
 * Alexander Aring <aar@pengutronix.de>
 *
 * Based on: net/wireless/nl80211.c
 */

#समावेश <linux/rtnetlink.h>

#समावेश <net/cfg802154.h>
#समावेश <net/genetlink.h>
#समावेश <net/mac802154.h>
#समावेश <net/netlink.h>
#समावेश <net/nl802154.h>
#समावेश <net/sock.h>

#समावेश "nl802154.h"
#समावेश "rdev-ops.h"
#समावेश "core.h"

/* the netlink family */
अटल काष्ठा genl_family nl802154_fam;

/* multicast groups */
क्रमागत nl802154_multicast_groups अणु
	NL802154_MCGRP_CONFIG,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group nl802154_mcgrps[] = अणु
	[NL802154_MCGRP_CONFIG] = अणु .name = "config", पूर्ण,
पूर्ण;

/* वापसs ERR_PTR values */
अटल काष्ठा wpan_dev *
__cfg802154_wpan_dev_from_attrs(काष्ठा net *netns, काष्ठा nlattr **attrs)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev;
	काष्ठा wpan_dev *result = शून्य;
	bool have_अगरidx = attrs[NL802154_ATTR_IFINDEX];
	bool have_wpan_dev_id = attrs[NL802154_ATTR_WPAN_DEV];
	u64 wpan_dev_id;
	पूर्णांक wpan_phy_idx = -1;
	पूर्णांक अगरidx = -1;

	ASSERT_RTNL();

	अगर (!have_अगरidx && !have_wpan_dev_id)
		वापस ERR_PTR(-EINVAL);

	अगर (have_अगरidx)
		अगरidx = nla_get_u32(attrs[NL802154_ATTR_IFINDEX]);
	अगर (have_wpan_dev_id) अणु
		wpan_dev_id = nla_get_u64(attrs[NL802154_ATTR_WPAN_DEV]);
		wpan_phy_idx = wpan_dev_id >> 32;
	पूर्ण

	list_क्रम_each_entry(rdev, &cfg802154_rdev_list, list) अणु
		काष्ठा wpan_dev *wpan_dev;

		अगर (wpan_phy_net(&rdev->wpan_phy) != netns)
			जारी;

		अगर (have_wpan_dev_id && rdev->wpan_phy_idx != wpan_phy_idx)
			जारी;

		list_क्रम_each_entry(wpan_dev, &rdev->wpan_dev_list, list) अणु
			अगर (have_अगरidx && wpan_dev->netdev &&
			    wpan_dev->netdev->अगरindex == अगरidx) अणु
				result = wpan_dev;
				अवरोध;
			पूर्ण
			अगर (have_wpan_dev_id &&
			    wpan_dev->identअगरier == (u32)wpan_dev_id) अणु
				result = wpan_dev;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (result)
			अवरोध;
	पूर्ण

	अगर (result)
		वापस result;

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल काष्ठा cfg802154_रेजिस्टरed_device *
__cfg802154_rdev_from_attrs(काष्ठा net *netns, काष्ठा nlattr **attrs)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = शून्य, *पंचांगp;
	काष्ठा net_device *netdev;

	ASSERT_RTNL();

	अगर (!attrs[NL802154_ATTR_WPAN_PHY] &&
	    !attrs[NL802154_ATTR_IFINDEX] &&
	    !attrs[NL802154_ATTR_WPAN_DEV])
		वापस ERR_PTR(-EINVAL);

	अगर (attrs[NL802154_ATTR_WPAN_PHY])
		rdev = cfg802154_rdev_by_wpan_phy_idx(
				nla_get_u32(attrs[NL802154_ATTR_WPAN_PHY]));

	अगर (attrs[NL802154_ATTR_WPAN_DEV]) अणु
		u64 wpan_dev_id = nla_get_u64(attrs[NL802154_ATTR_WPAN_DEV]);
		काष्ठा wpan_dev *wpan_dev;
		bool found = false;

		पंचांगp = cfg802154_rdev_by_wpan_phy_idx(wpan_dev_id >> 32);
		अगर (पंचांगp) अणु
			/* make sure wpan_dev exists */
			list_क्रम_each_entry(wpan_dev, &पंचांगp->wpan_dev_list, list) अणु
				अगर (wpan_dev->identअगरier != (u32)wpan_dev_id)
					जारी;
				found = true;
				अवरोध;
			पूर्ण

			अगर (!found)
				पंचांगp = शून्य;

			अगर (rdev && पंचांगp != rdev)
				वापस ERR_PTR(-EINVAL);
			rdev = पंचांगp;
		पूर्ण
	पूर्ण

	अगर (attrs[NL802154_ATTR_IFINDEX]) अणु
		पूर्णांक अगरindex = nla_get_u32(attrs[NL802154_ATTR_IFINDEX]);

		netdev = __dev_get_by_index(netns, अगरindex);
		अगर (netdev) अणु
			अगर (netdev->ieee802154_ptr)
				पंचांगp = wpan_phy_to_rdev(
						netdev->ieee802154_ptr->wpan_phy);
			अन्यथा
				पंचांगp = शून्य;

			/* not wireless device -- वापस error */
			अगर (!पंचांगp)
				वापस ERR_PTR(-EINVAL);

			/* mismatch -- वापस error */
			अगर (rdev && पंचांगp != rdev)
				वापस ERR_PTR(-EINVAL);

			rdev = पंचांगp;
		पूर्ण
	पूर्ण

	अगर (!rdev)
		वापस ERR_PTR(-ENODEV);

	अगर (netns != wpan_phy_net(&rdev->wpan_phy))
		वापस ERR_PTR(-ENODEV);

	वापस rdev;
पूर्ण

/* This function वापसs a poपूर्णांकer to the driver
 * that the genl_info item that is passed refers to.
 *
 * The result of this can be a PTR_ERR and hence must
 * be checked with IS_ERR() क्रम errors.
 */
अटल काष्ठा cfg802154_रेजिस्टरed_device *
cfg802154_get_dev_from_info(काष्ठा net *netns, काष्ठा genl_info *info)
अणु
	वापस __cfg802154_rdev_from_attrs(netns, info->attrs);
पूर्ण

/* policy क्रम the attributes */
अटल स्थिर काष्ठा nla_policy nl802154_policy[NL802154_ATTR_MAX+1] = अणु
	[NL802154_ATTR_WPAN_PHY] = अणु .type = NLA_U32 पूर्ण,
	[NL802154_ATTR_WPAN_PHY_NAME] = अणु .type = NLA_NUL_STRING,
					  .len = 20-1 पूर्ण,

	[NL802154_ATTR_IFINDEX] = अणु .type = NLA_U32 पूर्ण,
	[NL802154_ATTR_IFTYPE] = अणु .type = NLA_U32 पूर्ण,
	[NL802154_ATTR_IFNAME] = अणु .type = NLA_NUL_STRING, .len = IFNAMSIZ-1 पूर्ण,

	[NL802154_ATTR_WPAN_DEV] = अणु .type = NLA_U64 पूर्ण,

	[NL802154_ATTR_PAGE] = अणु .type = NLA_U8, पूर्ण,
	[NL802154_ATTR_CHANNEL] = अणु .type = NLA_U8, पूर्ण,

	[NL802154_ATTR_TX_POWER] = अणु .type = NLA_S32, पूर्ण,

	[NL802154_ATTR_CCA_MODE] = अणु .type = NLA_U32, पूर्ण,
	[NL802154_ATTR_CCA_OPT] = अणु .type = NLA_U32, पूर्ण,
	[NL802154_ATTR_CCA_ED_LEVEL] = अणु .type = NLA_S32, पूर्ण,

	[NL802154_ATTR_SUPPORTED_CHANNEL] = अणु .type = NLA_U32, पूर्ण,

	[NL802154_ATTR_PAN_ID] = अणु .type = NLA_U16, पूर्ण,
	[NL802154_ATTR_EXTENDED_ADDR] = अणु .type = NLA_U64 पूर्ण,
	[NL802154_ATTR_SHORT_ADDR] = अणु .type = NLA_U16, पूर्ण,

	[NL802154_ATTR_MIN_BE] = अणु .type = NLA_U8, पूर्ण,
	[NL802154_ATTR_MAX_BE] = अणु .type = NLA_U8, पूर्ण,
	[NL802154_ATTR_MAX_CSMA_BACKOFFS] = अणु .type = NLA_U8, पूर्ण,

	[NL802154_ATTR_MAX_FRAME_RETRIES] = अणु .type = NLA_S8, पूर्ण,

	[NL802154_ATTR_LBT_MODE] = अणु .type = NLA_U8, पूर्ण,

	[NL802154_ATTR_WPAN_PHY_CAPS] = अणु .type = NLA_NESTED पूर्ण,

	[NL802154_ATTR_SUPPORTED_COMMANDS] = अणु .type = NLA_NESTED पूर्ण,

	[NL802154_ATTR_ACKREQ_DEFAULT] = अणु .type = NLA_U8 पूर्ण,

	[NL802154_ATTR_PID] = अणु .type = NLA_U32 पूर्ण,
	[NL802154_ATTR_NETNS_FD] = अणु .type = NLA_U32 पूर्ण,
#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
	[NL802154_ATTR_SEC_ENABLED] = अणु .type = NLA_U8, पूर्ण,
	[NL802154_ATTR_SEC_OUT_LEVEL] = अणु .type = NLA_U32, पूर्ण,
	[NL802154_ATTR_SEC_OUT_KEY_ID] = अणु .type = NLA_NESTED, पूर्ण,
	[NL802154_ATTR_SEC_FRAME_COUNTER] = अणु .type = NLA_U32 पूर्ण,

	[NL802154_ATTR_SEC_LEVEL] = अणु .type = NLA_NESTED पूर्ण,
	[NL802154_ATTR_SEC_DEVICE] = अणु .type = NLA_NESTED पूर्ण,
	[NL802154_ATTR_SEC_DEVKEY] = अणु .type = NLA_NESTED पूर्ण,
	[NL802154_ATTR_SEC_KEY] = अणु .type = NLA_NESTED पूर्ण,
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */
पूर्ण;

#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
अटल पूर्णांक
nl802154_prepare_wpan_dev_dump(काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb,
			       काष्ठा cfg802154_रेजिस्टरed_device **rdev,
			       काष्ठा wpan_dev **wpan_dev)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	पूर्णांक err;

	rtnl_lock();

	अगर (!cb->args[0]) अणु
		*wpan_dev = __cfg802154_wpan_dev_from_attrs(sock_net(skb->sk),
							    info->attrs);
		अगर (IS_ERR(*wpan_dev)) अणु
			err = PTR_ERR(*wpan_dev);
			जाओ out_unlock;
		पूर्ण
		*rdev = wpan_phy_to_rdev((*wpan_dev)->wpan_phy);
		/* 0 is the first index - add 1 to parse only once */
		cb->args[0] = (*rdev)->wpan_phy_idx + 1;
		cb->args[1] = (*wpan_dev)->identअगरier;
	पूर्ण अन्यथा अणु
		/* subtract the 1 again here */
		काष्ठा wpan_phy *wpan_phy = wpan_phy_idx_to_wpan_phy(cb->args[0] - 1);
		काष्ठा wpan_dev *पंचांगp;

		अगर (!wpan_phy) अणु
			err = -ENODEV;
			जाओ out_unlock;
		पूर्ण
		*rdev = wpan_phy_to_rdev(wpan_phy);
		*wpan_dev = शून्य;

		list_क्रम_each_entry(पंचांगp, &(*rdev)->wpan_dev_list, list) अणु
			अगर (पंचांगp->identअगरier == cb->args[1]) अणु
				*wpan_dev = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!*wpan_dev) अणु
			err = -ENODEV;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	वापस 0;
 out_unlock:
	rtnl_unlock();
	वापस err;
पूर्ण

अटल व्योम
nl802154_finish_wpan_dev_dump(काष्ठा cfg802154_रेजिस्टरed_device *rdev)
अणु
	rtnl_unlock();
पूर्ण
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */

/* message building helper */
अटल अंतरभूत व्योम *nl802154hdr_put(काष्ठा sk_buff *skb, u32 portid, u32 seq,
				    पूर्णांक flags, u8 cmd)
अणु
	/* since there is no निजी header just add the generic one */
	वापस genlmsg_put(skb, portid, seq, &nl802154_fam, flags, cmd);
पूर्ण

अटल पूर्णांक
nl802154_put_flags(काष्ठा sk_buff *msg, पूर्णांक attr, u32 mask)
अणु
	काष्ठा nlattr *nl_flags = nla_nest_start_noflag(msg, attr);
	पूर्णांक i;

	अगर (!nl_flags)
		वापस -ENOBUFS;

	i = 0;
	जबतक (mask) अणु
		अगर ((mask & 1) && nla_put_flag(msg, i))
			वापस -ENOBUFS;

		mask >>= 1;
		i++;
	पूर्ण

	nla_nest_end(msg, nl_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
nl802154_send_wpan_phy_channels(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
				काष्ठा sk_buff *msg)
अणु
	काष्ठा nlattr *nl_page;
	अचिन्हित दीर्घ page;

	nl_page = nla_nest_start_noflag(msg, NL802154_ATTR_CHANNELS_SUPPORTED);
	अगर (!nl_page)
		वापस -ENOBUFS;

	क्रम (page = 0; page <= IEEE802154_MAX_PAGE; page++) अणु
		अगर (nla_put_u32(msg, NL802154_ATTR_SUPPORTED_CHANNEL,
				rdev->wpan_phy.supported.channels[page]))
			वापस -ENOBUFS;
	पूर्ण
	nla_nest_end(msg, nl_page);

	वापस 0;
पूर्ण

अटल पूर्णांक
nl802154_put_capabilities(काष्ठा sk_buff *msg,
			  काष्ठा cfg802154_रेजिस्टरed_device *rdev)
अणु
	स्थिर काष्ठा wpan_phy_supported *caps = &rdev->wpan_phy.supported;
	काष्ठा nlattr *nl_caps, *nl_channels;
	पूर्णांक i;

	nl_caps = nla_nest_start_noflag(msg, NL802154_ATTR_WPAN_PHY_CAPS);
	अगर (!nl_caps)
		वापस -ENOBUFS;

	nl_channels = nla_nest_start_noflag(msg, NL802154_CAP_ATTR_CHANNELS);
	अगर (!nl_channels)
		वापस -ENOBUFS;

	क्रम (i = 0; i <= IEEE802154_MAX_PAGE; i++) अणु
		अगर (caps->channels[i]) अणु
			अगर (nl802154_put_flags(msg, i, caps->channels[i]))
				वापस -ENOBUFS;
		पूर्ण
	पूर्ण

	nla_nest_end(msg, nl_channels);

	अगर (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_ED_LEVEL) अणु
		काष्ठा nlattr *nl_ed_lvls;

		nl_ed_lvls = nla_nest_start_noflag(msg,
						   NL802154_CAP_ATTR_CCA_ED_LEVELS);
		अगर (!nl_ed_lvls)
			वापस -ENOBUFS;

		क्रम (i = 0; i < caps->cca_ed_levels_size; i++) अणु
			अगर (nla_put_s32(msg, i, caps->cca_ed_levels[i]))
				वापस -ENOBUFS;
		पूर्ण

		nla_nest_end(msg, nl_ed_lvls);
	पूर्ण

	अगर (rdev->wpan_phy.flags & WPAN_PHY_FLAG_TXPOWER) अणु
		काष्ठा nlattr *nl_tx_pwrs;

		nl_tx_pwrs = nla_nest_start_noflag(msg,
						   NL802154_CAP_ATTR_TX_POWERS);
		अगर (!nl_tx_pwrs)
			वापस -ENOBUFS;

		क्रम (i = 0; i < caps->tx_घातers_size; i++) अणु
			अगर (nla_put_s32(msg, i, caps->tx_घातers[i]))
				वापस -ENOBUFS;
		पूर्ण

		nla_nest_end(msg, nl_tx_pwrs);
	पूर्ण

	अगर (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_MODE) अणु
		अगर (nl802154_put_flags(msg, NL802154_CAP_ATTR_CCA_MODES,
				       caps->cca_modes) ||
		    nl802154_put_flags(msg, NL802154_CAP_ATTR_CCA_OPTS,
				       caps->cca_opts))
			वापस -ENOBUFS;
	पूर्ण

	अगर (nla_put_u8(msg, NL802154_CAP_ATTR_MIN_MINBE, caps->min_minbe) ||
	    nla_put_u8(msg, NL802154_CAP_ATTR_MAX_MINBE, caps->max_minbe) ||
	    nla_put_u8(msg, NL802154_CAP_ATTR_MIN_MAXBE, caps->min_maxbe) ||
	    nla_put_u8(msg, NL802154_CAP_ATTR_MAX_MAXBE, caps->max_maxbe) ||
	    nla_put_u8(msg, NL802154_CAP_ATTR_MIN_CSMA_BACKOFFS,
		       caps->min_csma_backoffs) ||
	    nla_put_u8(msg, NL802154_CAP_ATTR_MAX_CSMA_BACKOFFS,
		       caps->max_csma_backoffs) ||
	    nla_put_s8(msg, NL802154_CAP_ATTR_MIN_FRAME_RETRIES,
		       caps->min_frame_retries) ||
	    nla_put_s8(msg, NL802154_CAP_ATTR_MAX_FRAME_RETRIES,
		       caps->max_frame_retries) ||
	    nl802154_put_flags(msg, NL802154_CAP_ATTR_IFTYPES,
			       caps->अगरtypes) ||
	    nla_put_u32(msg, NL802154_CAP_ATTR_LBT, caps->lbt))
		वापस -ENOBUFS;

	nla_nest_end(msg, nl_caps);

	वापस 0;
पूर्ण

अटल पूर्णांक nl802154_send_wpan_phy(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
				  क्रमागत nl802154_commands cmd,
				  काष्ठा sk_buff *msg, u32 portid, u32 seq,
				  पूर्णांक flags)
अणु
	काष्ठा nlattr *nl_cmds;
	व्योम *hdr;
	पूर्णांक i;

	hdr = nl802154hdr_put(msg, portid, seq, flags, cmd);
	अगर (!hdr)
		वापस -ENOBUFS;

	अगर (nla_put_u32(msg, NL802154_ATTR_WPAN_PHY, rdev->wpan_phy_idx) ||
	    nla_put_string(msg, NL802154_ATTR_WPAN_PHY_NAME,
			   wpan_phy_name(&rdev->wpan_phy)) ||
	    nla_put_u32(msg, NL802154_ATTR_GENERATION,
			cfg802154_rdev_list_generation))
		जाओ nla_put_failure;

	अगर (cmd != NL802154_CMD_NEW_WPAN_PHY)
		जाओ finish;

	/* DUMP PHY PIB */

	/* current channel settings */
	अगर (nla_put_u8(msg, NL802154_ATTR_PAGE,
		       rdev->wpan_phy.current_page) ||
	    nla_put_u8(msg, NL802154_ATTR_CHANNEL,
		       rdev->wpan_phy.current_channel))
		जाओ nla_put_failure;

	/* TODO हटाओ this behaviour, we still keep support it क्रम a जबतक
	 * so users can change the behaviour to the new one.
	 */
	अगर (nl802154_send_wpan_phy_channels(rdev, msg))
		जाओ nla_put_failure;

	/* cca mode */
	अगर (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_MODE) अणु
		अगर (nla_put_u32(msg, NL802154_ATTR_CCA_MODE,
				rdev->wpan_phy.cca.mode))
			जाओ nla_put_failure;

		अगर (rdev->wpan_phy.cca.mode == NL802154_CCA_ENERGY_CARRIER) अणु
			अगर (nla_put_u32(msg, NL802154_ATTR_CCA_OPT,
					rdev->wpan_phy.cca.opt))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	अगर (rdev->wpan_phy.flags & WPAN_PHY_FLAG_TXPOWER) अणु
		अगर (nla_put_s32(msg, NL802154_ATTR_TX_POWER,
				rdev->wpan_phy.transmit_घातer))
			जाओ nla_put_failure;
	पूर्ण

	अगर (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_ED_LEVEL) अणु
		अगर (nla_put_s32(msg, NL802154_ATTR_CCA_ED_LEVEL,
				rdev->wpan_phy.cca_ed_level))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nl802154_put_capabilities(msg, rdev))
		जाओ nla_put_failure;

	nl_cmds = nla_nest_start_noflag(msg, NL802154_ATTR_SUPPORTED_COMMANDS);
	अगर (!nl_cmds)
		जाओ nla_put_failure;

	i = 0;
#घोषणा CMD(op, n)							\
	करो अणु								\
		अगर (rdev->ops->op) अणु					\
			i++;						\
			अगर (nla_put_u32(msg, i, NL802154_CMD_ ## n))	\
				जाओ nla_put_failure;			\
		पूर्ण							\
	पूर्ण जबतक (0)

	CMD(add_भव_पूर्णांकf, NEW_INTERFACE);
	CMD(del_भव_पूर्णांकf, DEL_INTERFACE);
	CMD(set_channel, SET_CHANNEL);
	CMD(set_pan_id, SET_PAN_ID);
	CMD(set_लघु_addr, SET_SHORT_ADDR);
	CMD(set_backoff_exponent, SET_BACKOFF_EXPONENT);
	CMD(set_max_csma_backoffs, SET_MAX_CSMA_BACKOFFS);
	CMD(set_max_frame_retries, SET_MAX_FRAME_RETRIES);
	CMD(set_lbt_mode, SET_LBT_MODE);
	CMD(set_ackreq_शेष, SET_ACKREQ_DEFAULT);

	अगर (rdev->wpan_phy.flags & WPAN_PHY_FLAG_TXPOWER)
		CMD(set_tx_घातer, SET_TX_POWER);

	अगर (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_ED_LEVEL)
		CMD(set_cca_ed_level, SET_CCA_ED_LEVEL);

	अगर (rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_MODE)
		CMD(set_cca_mode, SET_CCA_MODE);

#अघोषित CMD
	nla_nest_end(msg, nl_cmds);

finish:
	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

काष्ठा nl802154_dump_wpan_phy_state अणु
	s64 filter_wpan_phy;
	दीर्घ start;

पूर्ण;

अटल पूर्णांक nl802154_dump_wpan_phy_parse(काष्ठा sk_buff *skb,
					काष्ठा netlink_callback *cb,
					काष्ठा nl802154_dump_wpan_phy_state *state)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	काष्ठा nlattr **tb = info->attrs;

	अगर (tb[NL802154_ATTR_WPAN_PHY])
		state->filter_wpan_phy = nla_get_u32(tb[NL802154_ATTR_WPAN_PHY]);
	अगर (tb[NL802154_ATTR_WPAN_DEV])
		state->filter_wpan_phy = nla_get_u64(tb[NL802154_ATTR_WPAN_DEV]) >> 32;
	अगर (tb[NL802154_ATTR_IFINDEX]) अणु
		काष्ठा net_device *netdev;
		काष्ठा cfg802154_रेजिस्टरed_device *rdev;
		पूर्णांक अगरidx = nla_get_u32(tb[NL802154_ATTR_IFINDEX]);

		netdev = __dev_get_by_index(&init_net, अगरidx);
		अगर (!netdev)
			वापस -ENODEV;
		अगर (netdev->ieee802154_ptr) अणु
			rdev = wpan_phy_to_rdev(
					netdev->ieee802154_ptr->wpan_phy);
			state->filter_wpan_phy = rdev->wpan_phy_idx;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nl802154_dump_wpan_phy(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक idx = 0, ret;
	काष्ठा nl802154_dump_wpan_phy_state *state = (व्योम *)cb->args[0];
	काष्ठा cfg802154_रेजिस्टरed_device *rdev;

	rtnl_lock();
	अगर (!state) अणु
		state = kzalloc(माप(*state), GFP_KERNEL);
		अगर (!state) अणु
			rtnl_unlock();
			वापस -ENOMEM;
		पूर्ण
		state->filter_wpan_phy = -1;
		ret = nl802154_dump_wpan_phy_parse(skb, cb, state);
		अगर (ret) अणु
			kमुक्त(state);
			rtnl_unlock();
			वापस ret;
		पूर्ण
		cb->args[0] = (दीर्घ)state;
	पूर्ण

	list_क्रम_each_entry(rdev, &cfg802154_rdev_list, list) अणु
		अगर (!net_eq(wpan_phy_net(&rdev->wpan_phy), sock_net(skb->sk)))
			जारी;
		अगर (++idx <= state->start)
			जारी;
		अगर (state->filter_wpan_phy != -1 &&
		    state->filter_wpan_phy != rdev->wpan_phy_idx)
			जारी;
		/* attempt to fit multiple wpan_phy data chunks पूर्णांकo the skb */
		ret = nl802154_send_wpan_phy(rdev,
					     NL802154_CMD_NEW_WPAN_PHY,
					     skb,
					     NETLINK_CB(cb->skb).portid,
					     cb->nlh->nlmsg_seq, NLM_F_MULTI);
		अगर (ret < 0) अणु
			अगर ((ret == -ENOBUFS || ret == -EMSGSIZE) &&
			    !skb->len && cb->min_dump_alloc < 4096) अणु
				cb->min_dump_alloc = 4096;
				rtnl_unlock();
				वापस 1;
			पूर्ण
			idx--;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	rtnl_unlock();

	state->start = idx;

	वापस skb->len;
पूर्ण

अटल पूर्णांक nl802154_dump_wpan_phy_करोne(काष्ठा netlink_callback *cb)
अणु
	kमुक्त((व्योम *)cb->args[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक nl802154_get_wpan_phy(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (nl802154_send_wpan_phy(rdev, NL802154_CMD_NEW_WPAN_PHY, msg,
				   info->snd_portid, info->snd_seq, 0) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOBUFS;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल अंतरभूत u64 wpan_dev_id(काष्ठा wpan_dev *wpan_dev)
अणु
	वापस (u64)wpan_dev->identअगरier |
	       ((u64)wpan_phy_to_rdev(wpan_dev->wpan_phy)->wpan_phy_idx << 32);
पूर्ण

#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
#समावेश <net/ieee802154_netdev.h>

अटल पूर्णांक
ieee802154_llsec_send_key_id(काष्ठा sk_buff *msg,
			     स्थिर काष्ठा ieee802154_llsec_key_id *desc)
अणु
	काष्ठा nlattr *nl_dev_addr;

	अगर (nla_put_u32(msg, NL802154_KEY_ID_ATTR_MODE, desc->mode))
		वापस -ENOBUFS;

	चयन (desc->mode) अणु
	हाल NL802154_KEY_ID_MODE_IMPLICIT:
		nl_dev_addr = nla_nest_start_noflag(msg,
						    NL802154_KEY_ID_ATTR_IMPLICIT);
		अगर (!nl_dev_addr)
			वापस -ENOBUFS;

		अगर (nla_put_le16(msg, NL802154_DEV_ADDR_ATTR_PAN_ID,
				 desc->device_addr.pan_id) ||
		    nla_put_u32(msg,  NL802154_DEV_ADDR_ATTR_MODE,
				desc->device_addr.mode))
			वापस -ENOBUFS;

		चयन (desc->device_addr.mode) अणु
		हाल NL802154_DEV_ADDR_SHORT:
			अगर (nla_put_le16(msg, NL802154_DEV_ADDR_ATTR_SHORT,
					 desc->device_addr.लघु_addr))
				वापस -ENOBUFS;
			अवरोध;
		हाल NL802154_DEV_ADDR_EXTENDED:
			अगर (nla_put_le64(msg, NL802154_DEV_ADDR_ATTR_EXTENDED,
					 desc->device_addr.extended_addr,
					 NL802154_DEV_ADDR_ATTR_PAD))
				वापस -ENOBUFS;
			अवरोध;
		शेष:
			/* userspace should handle unknown */
			अवरोध;
		पूर्ण

		nla_nest_end(msg, nl_dev_addr);
		अवरोध;
	हाल NL802154_KEY_ID_MODE_INDEX:
		अवरोध;
	हाल NL802154_KEY_ID_MODE_INDEX_SHORT:
		/* TODO renmae लघु_source? */
		अगर (nla_put_le32(msg, NL802154_KEY_ID_ATTR_SOURCE_SHORT,
				 desc->लघु_source))
			वापस -ENOBUFS;
		अवरोध;
	हाल NL802154_KEY_ID_MODE_INDEX_EXTENDED:
		अगर (nla_put_le64(msg, NL802154_KEY_ID_ATTR_SOURCE_EXTENDED,
				 desc->extended_source,
				 NL802154_KEY_ID_ATTR_PAD))
			वापस -ENOBUFS;
		अवरोध;
	शेष:
		/* userspace should handle unknown */
		अवरोध;
	पूर्ण

	/* TODO key_id to key_idx ? Check naming */
	अगर (desc->mode != NL802154_KEY_ID_MODE_IMPLICIT) अणु
		अगर (nla_put_u8(msg, NL802154_KEY_ID_ATTR_INDEX, desc->id))
			वापस -ENOBUFS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl802154_get_llsec_params(काष्ठा sk_buff *msg,
				     काष्ठा cfg802154_रेजिस्टरed_device *rdev,
				     काष्ठा wpan_dev *wpan_dev)
अणु
	काष्ठा nlattr *nl_key_id;
	काष्ठा ieee802154_llsec_params params;
	पूर्णांक ret;

	ret = rdev_get_llsec_params(rdev, wpan_dev, &params);
	अगर (ret < 0)
		वापस ret;

	अगर (nla_put_u8(msg, NL802154_ATTR_SEC_ENABLED, params.enabled) ||
	    nla_put_u32(msg, NL802154_ATTR_SEC_OUT_LEVEL, params.out_level) ||
	    nla_put_be32(msg, NL802154_ATTR_SEC_FRAME_COUNTER,
			 params.frame_counter))
		वापस -ENOBUFS;

	nl_key_id = nla_nest_start_noflag(msg, NL802154_ATTR_SEC_OUT_KEY_ID);
	अगर (!nl_key_id)
		वापस -ENOBUFS;

	ret = ieee802154_llsec_send_key_id(msg, &params.out_key);
	अगर (ret < 0)
		वापस ret;

	nla_nest_end(msg, nl_key_id);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */

अटल पूर्णांक
nl802154_send_अगरace(काष्ठा sk_buff *msg, u32 portid, u32 seq, पूर्णांक flags,
		    काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		    काष्ठा wpan_dev *wpan_dev)
अणु
	काष्ठा net_device *dev = wpan_dev->netdev;
	व्योम *hdr;

	hdr = nl802154hdr_put(msg, portid, seq, flags,
			      NL802154_CMD_NEW_INTERFACE);
	अगर (!hdr)
		वापस -1;

	अगर (dev &&
	    (nla_put_u32(msg, NL802154_ATTR_IFINDEX, dev->अगरindex) ||
	     nla_put_string(msg, NL802154_ATTR_IFNAME, dev->name)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL802154_ATTR_WPAN_PHY, rdev->wpan_phy_idx) ||
	    nla_put_u32(msg, NL802154_ATTR_IFTYPE, wpan_dev->अगरtype) ||
	    nla_put_u64_64bit(msg, NL802154_ATTR_WPAN_DEV,
			      wpan_dev_id(wpan_dev), NL802154_ATTR_PAD) ||
	    nla_put_u32(msg, NL802154_ATTR_GENERATION,
			rdev->devlist_generation ^
			(cfg802154_rdev_list_generation << 2)))
		जाओ nla_put_failure;

	/* address settings */
	अगर (nla_put_le64(msg, NL802154_ATTR_EXTENDED_ADDR,
			 wpan_dev->extended_addr,
			 NL802154_ATTR_PAD) ||
	    nla_put_le16(msg, NL802154_ATTR_SHORT_ADDR,
			 wpan_dev->लघु_addr) ||
	    nla_put_le16(msg, NL802154_ATTR_PAN_ID, wpan_dev->pan_id))
		जाओ nla_put_failure;

	/* ARET handling */
	अगर (nla_put_s8(msg, NL802154_ATTR_MAX_FRAME_RETRIES,
		       wpan_dev->frame_retries) ||
	    nla_put_u8(msg, NL802154_ATTR_MAX_BE, wpan_dev->max_be) ||
	    nla_put_u8(msg, NL802154_ATTR_MAX_CSMA_BACKOFFS,
		       wpan_dev->csma_retries) ||
	    nla_put_u8(msg, NL802154_ATTR_MIN_BE, wpan_dev->min_be))
		जाओ nla_put_failure;

	/* listen beक्रमe transmit */
	अगर (nla_put_u8(msg, NL802154_ATTR_LBT_MODE, wpan_dev->lbt))
		जाओ nla_put_failure;

	/* ackreq शेष behaviour */
	अगर (nla_put_u8(msg, NL802154_ATTR_ACKREQ_DEFAULT, wpan_dev->ackreq))
		जाओ nla_put_failure;

#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		जाओ out;

	अगर (nl802154_get_llsec_params(msg, rdev, wpan_dev) < 0)
		जाओ nla_put_failure;

out:
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
nl802154_dump_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक wp_idx = 0;
	पूर्णांक अगर_idx = 0;
	पूर्णांक wp_start = cb->args[0];
	पूर्णांक अगर_start = cb->args[1];
	काष्ठा cfg802154_रेजिस्टरed_device *rdev;
	काष्ठा wpan_dev *wpan_dev;

	rtnl_lock();
	list_क्रम_each_entry(rdev, &cfg802154_rdev_list, list) अणु
		अगर (!net_eq(wpan_phy_net(&rdev->wpan_phy), sock_net(skb->sk)))
			जारी;
		अगर (wp_idx < wp_start) अणु
			wp_idx++;
			जारी;
		पूर्ण
		अगर_idx = 0;

		list_क्रम_each_entry(wpan_dev, &rdev->wpan_dev_list, list) अणु
			अगर (अगर_idx < अगर_start) अणु
				अगर_idx++;
				जारी;
			पूर्ण
			अगर (nl802154_send_अगरace(skb, NETLINK_CB(cb->skb).portid,
						cb->nlh->nlmsg_seq, NLM_F_MULTI,
						rdev, wpan_dev) < 0) अणु
				जाओ out;
			पूर्ण
			अगर_idx++;
		पूर्ण

		wp_idx++;
	पूर्ण
out:
	rtnl_unlock();

	cb->args[0] = wp_idx;
	cb->args[1] = अगर_idx;

	वापस skb->len;
पूर्ण

अटल पूर्णांक nl802154_get_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wpan_dev *wdev = info->user_ptr[1];

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (nl802154_send_अगरace(msg, info->snd_portid, info->snd_seq, 0,
				rdev, wdev) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOBUFS;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक nl802154_new_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	क्रमागत nl802154_अगरtype type = NL802154_IFTYPE_UNSPEC;
	__le64 extended_addr = cpu_to_le64(0x0000000000000000ULL);

	/* TODO aव्योम failing a new पूर्णांकerface
	 * creation due to pending removal?
	 */

	अगर (!info->attrs[NL802154_ATTR_IFNAME])
		वापस -EINVAL;

	अगर (info->attrs[NL802154_ATTR_IFTYPE]) अणु
		type = nla_get_u32(info->attrs[NL802154_ATTR_IFTYPE]);
		अगर (type > NL802154_IFTYPE_MAX ||
		    !(rdev->wpan_phy.supported.अगरtypes & BIT(type)))
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL802154_ATTR_EXTENDED_ADDR])
		extended_addr = nla_get_le64(info->attrs[NL802154_ATTR_EXTENDED_ADDR]);

	अगर (!rdev->ops->add_भव_पूर्णांकf)
		वापस -EOPNOTSUPP;

	वापस rdev_add_भव_पूर्णांकf(rdev,
				     nla_data(info->attrs[NL802154_ATTR_IFNAME]),
				     NET_NAME_USER, type, extended_addr);
पूर्ण

अटल पूर्णांक nl802154_del_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wpan_dev *wpan_dev = info->user_ptr[1];

	अगर (!rdev->ops->del_भव_पूर्णांकf)
		वापस -EOPNOTSUPP;

	/* If we हटाओ a wpan device without a netdev then clear
	 * user_ptr[1] so that nl802154_post_करोit won't dereference it
	 * to check अगर it needs to करो dev_put(). Otherwise it crashes
	 * since the wpan_dev has been मुक्तd, unlike with a netdev where
	 * we need the dev_put() क्रम the netdev to really be मुक्तd.
	 */
	अगर (!wpan_dev->netdev)
		info->user_ptr[1] = शून्य;

	वापस rdev_del_भव_पूर्णांकf(rdev, wpan_dev);
पूर्ण

अटल पूर्णांक nl802154_set_channel(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	u8 channel, page;

	अगर (!info->attrs[NL802154_ATTR_PAGE] ||
	    !info->attrs[NL802154_ATTR_CHANNEL])
		वापस -EINVAL;

	page = nla_get_u8(info->attrs[NL802154_ATTR_PAGE]);
	channel = nla_get_u8(info->attrs[NL802154_ATTR_CHANNEL]);

	/* check 802.15.4 स्थिरraपूर्णांकs */
	अगर (page > IEEE802154_MAX_PAGE || channel > IEEE802154_MAX_CHANNEL ||
	    !(rdev->wpan_phy.supported.channels[page] & BIT(channel)))
		वापस -EINVAL;

	वापस rdev_set_channel(rdev, page, channel);
पूर्ण

अटल पूर्णांक nl802154_set_cca_mode(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wpan_phy_cca cca;

	अगर (!(rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_MODE))
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL802154_ATTR_CCA_MODE])
		वापस -EINVAL;

	cca.mode = nla_get_u32(info->attrs[NL802154_ATTR_CCA_MODE]);
	/* checking 802.15.4 स्थिरraपूर्णांकs */
	अगर (cca.mode < NL802154_CCA_ENERGY ||
	    cca.mode > NL802154_CCA_ATTR_MAX ||
	    !(rdev->wpan_phy.supported.cca_modes & BIT(cca.mode)))
		वापस -EINVAL;

	अगर (cca.mode == NL802154_CCA_ENERGY_CARRIER) अणु
		अगर (!info->attrs[NL802154_ATTR_CCA_OPT])
			वापस -EINVAL;

		cca.opt = nla_get_u32(info->attrs[NL802154_ATTR_CCA_OPT]);
		अगर (cca.opt > NL802154_CCA_OPT_ATTR_MAX ||
		    !(rdev->wpan_phy.supported.cca_opts & BIT(cca.opt)))
			वापस -EINVAL;
	पूर्ण

	वापस rdev_set_cca_mode(rdev, &cca);
पूर्ण

अटल पूर्णांक nl802154_set_cca_ed_level(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	s32 ed_level;
	पूर्णांक i;

	अगर (!(rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_ED_LEVEL))
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL802154_ATTR_CCA_ED_LEVEL])
		वापस -EINVAL;

	ed_level = nla_get_s32(info->attrs[NL802154_ATTR_CCA_ED_LEVEL]);

	क्रम (i = 0; i < rdev->wpan_phy.supported.cca_ed_levels_size; i++) अणु
		अगर (ed_level == rdev->wpan_phy.supported.cca_ed_levels[i])
			वापस rdev_set_cca_ed_level(rdev, ed_level);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nl802154_set_tx_घातer(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	s32 घातer;
	पूर्णांक i;

	अगर (!(rdev->wpan_phy.flags & WPAN_PHY_FLAG_TXPOWER))
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL802154_ATTR_TX_POWER])
		वापस -EINVAL;

	घातer = nla_get_s32(info->attrs[NL802154_ATTR_TX_POWER]);

	क्रम (i = 0; i < rdev->wpan_phy.supported.tx_घातers_size; i++) अणु
		अगर (घातer == rdev->wpan_phy.supported.tx_घातers[i])
			वापस rdev_set_tx_घातer(rdev, घातer);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nl802154_set_pan_id(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	__le16 pan_id;

	/* conflict here जबतक tx/rx calls */
	अगर (netअगर_running(dev))
		वापस -EBUSY;

	अगर (wpan_dev->lowpan_dev) अणु
		अगर (netअगर_running(wpan_dev->lowpan_dev))
			वापस -EBUSY;
	पूर्ण

	/* करोn't change address fields on monitor */
	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR ||
	    !info->attrs[NL802154_ATTR_PAN_ID])
		वापस -EINVAL;

	pan_id = nla_get_le16(info->attrs[NL802154_ATTR_PAN_ID]);

	/* TODO
	 * I am not sure about to check here on broadcast pan_id.
	 * Broadcast is a valid setting, comment from 802.15.4:
	 * If this value is 0xffff, the device is not associated.
	 *
	 * This could useful to simple deassociate an device.
	 */
	अगर (pan_id == cpu_to_le16(IEEE802154_PAN_ID_BROADCAST))
		वापस -EINVAL;

	वापस rdev_set_pan_id(rdev, wpan_dev, pan_id);
पूर्ण

अटल पूर्णांक nl802154_set_लघु_addr(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	__le16 लघु_addr;

	/* conflict here जबतक tx/rx calls */
	अगर (netअगर_running(dev))
		वापस -EBUSY;

	अगर (wpan_dev->lowpan_dev) अणु
		अगर (netअगर_running(wpan_dev->lowpan_dev))
			वापस -EBUSY;
	पूर्ण

	/* करोn't change address fields on monitor */
	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR ||
	    !info->attrs[NL802154_ATTR_SHORT_ADDR])
		वापस -EINVAL;

	लघु_addr = nla_get_le16(info->attrs[NL802154_ATTR_SHORT_ADDR]);

	/* TODO
	 * I am not sure about to check here on broadcast लघु_addr.
	 * Broadcast is a valid setting, comment from 802.15.4:
	 * A value of 0xfffe indicates that the device has
	 * associated but has not been allocated an address. A
	 * value of 0xffff indicates that the device करोes not
	 * have a लघु address.
	 *
	 * I think we should allow to set these settings but
	 * करोn't allow to allow socket communication with it.
	 */
	अगर (लघु_addr == cpu_to_le16(IEEE802154_ADDR_SHORT_UNSPEC) ||
	    लघु_addr == cpu_to_le16(IEEE802154_ADDR_SHORT_BROADCAST))
		वापस -EINVAL;

	वापस rdev_set_लघु_addr(rdev, wpan_dev, लघु_addr);
पूर्ण

अटल पूर्णांक
nl802154_set_backoff_exponent(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	u8 min_be, max_be;

	/* should be set on netअगर खोलो inside phy settings */
	अगर (netअगर_running(dev))
		वापस -EBUSY;

	अगर (!info->attrs[NL802154_ATTR_MIN_BE] ||
	    !info->attrs[NL802154_ATTR_MAX_BE])
		वापस -EINVAL;

	min_be = nla_get_u8(info->attrs[NL802154_ATTR_MIN_BE]);
	max_be = nla_get_u8(info->attrs[NL802154_ATTR_MAX_BE]);

	/* check 802.15.4 स्थिरraपूर्णांकs */
	अगर (min_be < rdev->wpan_phy.supported.min_minbe ||
	    min_be > rdev->wpan_phy.supported.max_minbe ||
	    max_be < rdev->wpan_phy.supported.min_maxbe ||
	    max_be > rdev->wpan_phy.supported.max_maxbe ||
	    min_be > max_be)
		वापस -EINVAL;

	वापस rdev_set_backoff_exponent(rdev, wpan_dev, min_be, max_be);
पूर्ण

अटल पूर्णांक
nl802154_set_max_csma_backoffs(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	u8 max_csma_backoffs;

	/* conflict here जबतक other running अगरace settings */
	अगर (netअगर_running(dev))
		वापस -EBUSY;

	अगर (!info->attrs[NL802154_ATTR_MAX_CSMA_BACKOFFS])
		वापस -EINVAL;

	max_csma_backoffs = nla_get_u8(
			info->attrs[NL802154_ATTR_MAX_CSMA_BACKOFFS]);

	/* check 802.15.4 स्थिरraपूर्णांकs */
	अगर (max_csma_backoffs < rdev->wpan_phy.supported.min_csma_backoffs ||
	    max_csma_backoffs > rdev->wpan_phy.supported.max_csma_backoffs)
		वापस -EINVAL;

	वापस rdev_set_max_csma_backoffs(rdev, wpan_dev, max_csma_backoffs);
पूर्ण

अटल पूर्णांक
nl802154_set_max_frame_retries(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	s8 max_frame_retries;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	अगर (!info->attrs[NL802154_ATTR_MAX_FRAME_RETRIES])
		वापस -EINVAL;

	max_frame_retries = nla_get_s8(
			info->attrs[NL802154_ATTR_MAX_FRAME_RETRIES]);

	/* check 802.15.4 स्थिरraपूर्णांकs */
	अगर (max_frame_retries < rdev->wpan_phy.supported.min_frame_retries ||
	    max_frame_retries > rdev->wpan_phy.supported.max_frame_retries)
		वापस -EINVAL;

	वापस rdev_set_max_frame_retries(rdev, wpan_dev, max_frame_retries);
पूर्ण

अटल पूर्णांक nl802154_set_lbt_mode(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	पूर्णांक mode;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	अगर (!info->attrs[NL802154_ATTR_LBT_MODE])
		वापस -EINVAL;

	mode = nla_get_u8(info->attrs[NL802154_ATTR_LBT_MODE]);

	अगर (mode != 0 && mode != 1)
		वापस -EINVAL;

	अगर (!wpan_phy_supported_bool(mode, rdev->wpan_phy.supported.lbt))
		वापस -EINVAL;

	वापस rdev_set_lbt_mode(rdev, wpan_dev, mode);
पूर्ण

अटल पूर्णांक
nl802154_set_ackreq_शेष(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	पूर्णांक ackreq;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	अगर (!info->attrs[NL802154_ATTR_ACKREQ_DEFAULT])
		वापस -EINVAL;

	ackreq = nla_get_u8(info->attrs[NL802154_ATTR_ACKREQ_DEFAULT]);

	अगर (ackreq != 0 && ackreq != 1)
		वापस -EINVAL;

	वापस rdev_set_ackreq_शेष(rdev, wpan_dev, ackreq);
पूर्ण

अटल पूर्णांक nl802154_wpan_phy_netns(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net *net;
	पूर्णांक err;

	अगर (info->attrs[NL802154_ATTR_PID]) अणु
		u32 pid = nla_get_u32(info->attrs[NL802154_ATTR_PID]);

		net = get_net_ns_by_pid(pid);
	पूर्ण अन्यथा अगर (info->attrs[NL802154_ATTR_NETNS_FD]) अणु
		u32 fd = nla_get_u32(info->attrs[NL802154_ATTR_NETNS_FD]);

		net = get_net_ns_by_fd(fd);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(net))
		वापस PTR_ERR(net);

	err = 0;

	/* check अगर anything to करो */
	अगर (!net_eq(wpan_phy_net(&rdev->wpan_phy), net))
		err = cfg802154_चयन_netns(rdev, net);

	put_net(net);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
अटल स्थिर काष्ठा nla_policy nl802154_dev_addr_policy[NL802154_DEV_ADDR_ATTR_MAX + 1] = अणु
	[NL802154_DEV_ADDR_ATTR_PAN_ID] = अणु .type = NLA_U16 पूर्ण,
	[NL802154_DEV_ADDR_ATTR_MODE] = अणु .type = NLA_U32 पूर्ण,
	[NL802154_DEV_ADDR_ATTR_SHORT] = अणु .type = NLA_U16 पूर्ण,
	[NL802154_DEV_ADDR_ATTR_EXTENDED] = अणु .type = NLA_U64 पूर्ण,
पूर्ण;

अटल पूर्णांक
ieee802154_llsec_parse_dev_addr(काष्ठा nlattr *nla,
				काष्ठा ieee802154_addr *addr)
अणु
	काष्ठा nlattr *attrs[NL802154_DEV_ADDR_ATTR_MAX + 1];

	अगर (!nla || nla_parse_nested_deprecated(attrs, NL802154_DEV_ADDR_ATTR_MAX, nla, nl802154_dev_addr_policy, शून्य))
		वापस -EINVAL;

	अगर (!attrs[NL802154_DEV_ADDR_ATTR_PAN_ID] || !attrs[NL802154_DEV_ADDR_ATTR_MODE])
		वापस -EINVAL;

	addr->pan_id = nla_get_le16(attrs[NL802154_DEV_ADDR_ATTR_PAN_ID]);
	addr->mode = nla_get_u32(attrs[NL802154_DEV_ADDR_ATTR_MODE]);
	चयन (addr->mode) अणु
	हाल NL802154_DEV_ADDR_SHORT:
		अगर (!attrs[NL802154_DEV_ADDR_ATTR_SHORT])
			वापस -EINVAL;
		addr->लघु_addr = nla_get_le16(attrs[NL802154_DEV_ADDR_ATTR_SHORT]);
		अवरोध;
	हाल NL802154_DEV_ADDR_EXTENDED:
		अगर (!attrs[NL802154_DEV_ADDR_ATTR_EXTENDED])
			वापस -EINVAL;
		addr->extended_addr = nla_get_le64(attrs[NL802154_DEV_ADDR_ATTR_EXTENDED]);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy nl802154_key_id_policy[NL802154_KEY_ID_ATTR_MAX + 1] = अणु
	[NL802154_KEY_ID_ATTR_MODE] = अणु .type = NLA_U32 पूर्ण,
	[NL802154_KEY_ID_ATTR_INDEX] = अणु .type = NLA_U8 पूर्ण,
	[NL802154_KEY_ID_ATTR_IMPLICIT] = अणु .type = NLA_NESTED पूर्ण,
	[NL802154_KEY_ID_ATTR_SOURCE_SHORT] = अणु .type = NLA_U32 पूर्ण,
	[NL802154_KEY_ID_ATTR_SOURCE_EXTENDED] = अणु .type = NLA_U64 पूर्ण,
पूर्ण;

अटल पूर्णांक
ieee802154_llsec_parse_key_id(काष्ठा nlattr *nla,
			      काष्ठा ieee802154_llsec_key_id *desc)
अणु
	काष्ठा nlattr *attrs[NL802154_KEY_ID_ATTR_MAX + 1];

	अगर (!nla || nla_parse_nested_deprecated(attrs, NL802154_KEY_ID_ATTR_MAX, nla, nl802154_key_id_policy, शून्य))
		वापस -EINVAL;

	अगर (!attrs[NL802154_KEY_ID_ATTR_MODE])
		वापस -EINVAL;

	desc->mode = nla_get_u32(attrs[NL802154_KEY_ID_ATTR_MODE]);
	चयन (desc->mode) अणु
	हाल NL802154_KEY_ID_MODE_IMPLICIT:
		अगर (!attrs[NL802154_KEY_ID_ATTR_IMPLICIT])
			वापस -EINVAL;

		अगर (ieee802154_llsec_parse_dev_addr(attrs[NL802154_KEY_ID_ATTR_IMPLICIT],
						    &desc->device_addr) < 0)
			वापस -EINVAL;
		अवरोध;
	हाल NL802154_KEY_ID_MODE_INDEX:
		अवरोध;
	हाल NL802154_KEY_ID_MODE_INDEX_SHORT:
		अगर (!attrs[NL802154_KEY_ID_ATTR_SOURCE_SHORT])
			वापस -EINVAL;

		desc->लघु_source = nla_get_le32(attrs[NL802154_KEY_ID_ATTR_SOURCE_SHORT]);
		अवरोध;
	हाल NL802154_KEY_ID_MODE_INDEX_EXTENDED:
		अगर (!attrs[NL802154_KEY_ID_ATTR_SOURCE_EXTENDED])
			वापस -EINVAL;

		desc->extended_source = nla_get_le64(attrs[NL802154_KEY_ID_ATTR_SOURCE_EXTENDED]);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (desc->mode != NL802154_KEY_ID_MODE_IMPLICIT) अणु
		अगर (!attrs[NL802154_KEY_ID_ATTR_INDEX])
			वापस -EINVAL;

		/* TODO change id to idx */
		desc->id = nla_get_u8(attrs[NL802154_KEY_ID_ATTR_INDEX]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl802154_set_llsec_params(काष्ठा sk_buff *skb,
				     काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा ieee802154_llsec_params params;
	u32 changed = 0;
	पूर्णांक ret;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	अगर (info->attrs[NL802154_ATTR_SEC_ENABLED]) अणु
		u8 enabled;

		enabled = nla_get_u8(info->attrs[NL802154_ATTR_SEC_ENABLED]);
		अगर (enabled != 0 && enabled != 1)
			वापस -EINVAL;

		params.enabled = nla_get_u8(info->attrs[NL802154_ATTR_SEC_ENABLED]);
		changed |= IEEE802154_LLSEC_PARAM_ENABLED;
	पूर्ण

	अगर (info->attrs[NL802154_ATTR_SEC_OUT_KEY_ID]) अणु
		ret = ieee802154_llsec_parse_key_id(info->attrs[NL802154_ATTR_SEC_OUT_KEY_ID],
						    &params.out_key);
		अगर (ret < 0)
			वापस ret;

		changed |= IEEE802154_LLSEC_PARAM_OUT_KEY;
	पूर्ण

	अगर (info->attrs[NL802154_ATTR_SEC_OUT_LEVEL]) अणु
		params.out_level = nla_get_u32(info->attrs[NL802154_ATTR_SEC_OUT_LEVEL]);
		अगर (params.out_level > NL802154_SECLEVEL_MAX)
			वापस -EINVAL;

		changed |= IEEE802154_LLSEC_PARAM_OUT_LEVEL;
	पूर्ण

	अगर (info->attrs[NL802154_ATTR_SEC_FRAME_COUNTER]) अणु
		params.frame_counter = nla_get_be32(info->attrs[NL802154_ATTR_SEC_FRAME_COUNTER]);
		changed |= IEEE802154_LLSEC_PARAM_FRAME_COUNTER;
	पूर्ण

	वापस rdev_set_llsec_params(rdev, wpan_dev, &params, changed);
पूर्ण

अटल पूर्णांक nl802154_send_key(काष्ठा sk_buff *msg, u32 cmd, u32 portid,
			     u32 seq, पूर्णांक flags,
			     काष्ठा cfg802154_रेजिस्टरed_device *rdev,
			     काष्ठा net_device *dev,
			     स्थिर काष्ठा ieee802154_llsec_key_entry *key)
अणु
	व्योम *hdr;
	u32 commands[NL802154_CMD_FRAME_NR_IDS / 32];
	काष्ठा nlattr *nl_key, *nl_key_id;

	hdr = nl802154hdr_put(msg, portid, seq, flags, cmd);
	अगर (!hdr)
		वापस -1;

	अगर (nla_put_u32(msg, NL802154_ATTR_IFINDEX, dev->अगरindex))
		जाओ nla_put_failure;

	nl_key = nla_nest_start_noflag(msg, NL802154_ATTR_SEC_KEY);
	अगर (!nl_key)
		जाओ nla_put_failure;

	nl_key_id = nla_nest_start_noflag(msg, NL802154_KEY_ATTR_ID);
	अगर (!nl_key_id)
		जाओ nla_put_failure;

	अगर (ieee802154_llsec_send_key_id(msg, &key->id) < 0)
		जाओ nla_put_failure;

	nla_nest_end(msg, nl_key_id);

	अगर (nla_put_u8(msg, NL802154_KEY_ATTR_USAGE_FRAMES,
		       key->key->frame_types))
		जाओ nla_put_failure;

	अगर (key->key->frame_types & BIT(NL802154_FRAME_CMD)) अणु
		/* TODO क्रम each nested */
		स_रखो(commands, 0, माप(commands));
		commands[7] = key->key->cmd_frame_ids;
		अगर (nla_put(msg, NL802154_KEY_ATTR_USAGE_CMDS,
			    माप(commands), commands))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put(msg, NL802154_KEY_ATTR_BYTES, NL802154_KEY_SIZE,
		    key->key->key))
		जाओ nla_put_failure;

	nla_nest_end(msg, nl_key);
	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
nl802154_dump_llsec_key(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = शून्य;
	काष्ठा ieee802154_llsec_key_entry *key;
	काष्ठा ieee802154_llsec_table *table;
	काष्ठा wpan_dev *wpan_dev;
	पूर्णांक err;

	err = nl802154_prepare_wpan_dev_dump(skb, cb, &rdev, &wpan_dev);
	अगर (err)
		वापस err;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR) अणु
		err = skb->len;
		जाओ out_err;
	पूर्ण

	अगर (!wpan_dev->netdev) अणु
		err = -EINVAL;
		जाओ out_err;
	पूर्ण

	rdev_lock_llsec_table(rdev, wpan_dev);
	rdev_get_llsec_table(rdev, wpan_dev, &table);

	/* TODO make it like station dump */
	अगर (cb->args[2])
		जाओ out;

	list_क्रम_each_entry(key, &table->keys, list) अणु
		अगर (nl802154_send_key(skb, NL802154_CMD_NEW_SEC_KEY,
				      NETLINK_CB(cb->skb).portid,
				      cb->nlh->nlmsg_seq, NLM_F_MULTI,
				      rdev, wpan_dev->netdev, key) < 0) अणु
			/* TODO */
			err = -EIO;
			rdev_unlock_llsec_table(rdev, wpan_dev);
			जाओ out_err;
		पूर्ण
	पूर्ण

	cb->args[2] = 1;

out:
	rdev_unlock_llsec_table(rdev, wpan_dev);
	err = skb->len;
out_err:
	nl802154_finish_wpan_dev_dump(rdev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy nl802154_key_policy[NL802154_KEY_ATTR_MAX + 1] = अणु
	[NL802154_KEY_ATTR_ID] = अणु NLA_NESTED पूर्ण,
	/* TODO handle it as क्रम_each_nested and NLA_FLAG? */
	[NL802154_KEY_ATTR_USAGE_FRAMES] = अणु NLA_U8 पूर्ण,
	/* TODO handle it as क्रम_each_nested, not अटल array? */
	[NL802154_KEY_ATTR_USAGE_CMDS] = अणु .len = NL802154_CMD_FRAME_NR_IDS / 8 पूर्ण,
	[NL802154_KEY_ATTR_BYTES] = अणु .len = NL802154_KEY_SIZE पूर्ण,
पूर्ण;

अटल पूर्णांक nl802154_add_llsec_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा nlattr *attrs[NL802154_KEY_ATTR_MAX + 1];
	काष्ठा ieee802154_llsec_key key = अणु पूर्ण;
	काष्ठा ieee802154_llsec_key_id id = अणु पूर्ण;
	u32 commands[NL802154_CMD_FRAME_NR_IDS / 32] = अणु पूर्ण;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL802154_ATTR_SEC_KEY] ||
	    nla_parse_nested_deprecated(attrs, NL802154_KEY_ATTR_MAX, info->attrs[NL802154_ATTR_SEC_KEY], nl802154_key_policy, info->extack))
		वापस -EINVAL;

	अगर (!attrs[NL802154_KEY_ATTR_USAGE_FRAMES] ||
	    !attrs[NL802154_KEY_ATTR_BYTES])
		वापस -EINVAL;

	अगर (ieee802154_llsec_parse_key_id(attrs[NL802154_KEY_ATTR_ID], &id) < 0)
		वापस -ENOBUFS;

	key.frame_types = nla_get_u8(attrs[NL802154_KEY_ATTR_USAGE_FRAMES]);
	अगर (key.frame_types > BIT(NL802154_FRAME_MAX) ||
	    ((key.frame_types & BIT(NL802154_FRAME_CMD)) &&
	     !attrs[NL802154_KEY_ATTR_USAGE_CMDS]))
		वापस -EINVAL;

	अगर (attrs[NL802154_KEY_ATTR_USAGE_CMDS]) अणु
		/* TODO क्रम each nested */
		nla_स_नकल(commands, attrs[NL802154_KEY_ATTR_USAGE_CMDS],
			   NL802154_CMD_FRAME_NR_IDS / 8);

		/* TODO understand the -EINVAL logic here? last condition */
		अगर (commands[0] || commands[1] || commands[2] || commands[3] ||
		    commands[4] || commands[5] || commands[6] ||
		    commands[7] > BIT(NL802154_CMD_FRAME_MAX))
			वापस -EINVAL;

		key.cmd_frame_ids = commands[7];
	पूर्ण अन्यथा अणु
		key.cmd_frame_ids = 0;
	पूर्ण

	nla_स_नकल(key.key, attrs[NL802154_KEY_ATTR_BYTES], NL802154_KEY_SIZE);

	अगर (ieee802154_llsec_parse_key_id(attrs[NL802154_KEY_ATTR_ID], &id) < 0)
		वापस -ENOBUFS;

	वापस rdev_add_llsec_key(rdev, wpan_dev, &id, &key);
पूर्ण

अटल पूर्णांक nl802154_del_llsec_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा nlattr *attrs[NL802154_KEY_ATTR_MAX + 1];
	काष्ठा ieee802154_llsec_key_id id;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL802154_ATTR_SEC_KEY] ||
	    nla_parse_nested_deprecated(attrs, NL802154_KEY_ATTR_MAX, info->attrs[NL802154_ATTR_SEC_KEY], nl802154_key_policy, info->extack))
		वापस -EINVAL;

	अगर (ieee802154_llsec_parse_key_id(attrs[NL802154_KEY_ATTR_ID], &id) < 0)
		वापस -ENOBUFS;

	वापस rdev_del_llsec_key(rdev, wpan_dev, &id);
पूर्ण

अटल पूर्णांक nl802154_send_device(काष्ठा sk_buff *msg, u32 cmd, u32 portid,
				u32 seq, पूर्णांक flags,
				काष्ठा cfg802154_रेजिस्टरed_device *rdev,
				काष्ठा net_device *dev,
				स्थिर काष्ठा ieee802154_llsec_device *dev_desc)
अणु
	व्योम *hdr;
	काष्ठा nlattr *nl_device;

	hdr = nl802154hdr_put(msg, portid, seq, flags, cmd);
	अगर (!hdr)
		वापस -1;

	अगर (nla_put_u32(msg, NL802154_ATTR_IFINDEX, dev->अगरindex))
		जाओ nla_put_failure;

	nl_device = nla_nest_start_noflag(msg, NL802154_ATTR_SEC_DEVICE);
	अगर (!nl_device)
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL802154_DEV_ATTR_FRAME_COUNTER,
			dev_desc->frame_counter) ||
	    nla_put_le16(msg, NL802154_DEV_ATTR_PAN_ID, dev_desc->pan_id) ||
	    nla_put_le16(msg, NL802154_DEV_ATTR_SHORT_ADDR,
			 dev_desc->लघु_addr) ||
	    nla_put_le64(msg, NL802154_DEV_ATTR_EXTENDED_ADDR,
			 dev_desc->hwaddr, NL802154_DEV_ATTR_PAD) ||
	    nla_put_u8(msg, NL802154_DEV_ATTR_SECLEVEL_EXEMPT,
		       dev_desc->seclevel_exempt) ||
	    nla_put_u32(msg, NL802154_DEV_ATTR_KEY_MODE, dev_desc->key_mode))
		जाओ nla_put_failure;

	nla_nest_end(msg, nl_device);
	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
nl802154_dump_llsec_dev(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = शून्य;
	काष्ठा ieee802154_llsec_device *dev;
	काष्ठा ieee802154_llsec_table *table;
	काष्ठा wpan_dev *wpan_dev;
	पूर्णांक err;

	err = nl802154_prepare_wpan_dev_dump(skb, cb, &rdev, &wpan_dev);
	अगर (err)
		वापस err;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR) अणु
		err = skb->len;
		जाओ out_err;
	पूर्ण

	अगर (!wpan_dev->netdev) अणु
		err = -EINVAL;
		जाओ out_err;
	पूर्ण

	rdev_lock_llsec_table(rdev, wpan_dev);
	rdev_get_llsec_table(rdev, wpan_dev, &table);

	/* TODO make it like station dump */
	अगर (cb->args[2])
		जाओ out;

	list_क्रम_each_entry(dev, &table->devices, list) अणु
		अगर (nl802154_send_device(skb, NL802154_CMD_NEW_SEC_LEVEL,
					 NETLINK_CB(cb->skb).portid,
					 cb->nlh->nlmsg_seq, NLM_F_MULTI,
					 rdev, wpan_dev->netdev, dev) < 0) अणु
			/* TODO */
			err = -EIO;
			rdev_unlock_llsec_table(rdev, wpan_dev);
			जाओ out_err;
		पूर्ण
	पूर्ण

	cb->args[2] = 1;

out:
	rdev_unlock_llsec_table(rdev, wpan_dev);
	err = skb->len;
out_err:
	nl802154_finish_wpan_dev_dump(rdev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy nl802154_dev_policy[NL802154_DEV_ATTR_MAX + 1] = अणु
	[NL802154_DEV_ATTR_FRAME_COUNTER] = अणु NLA_U32 पूर्ण,
	[NL802154_DEV_ATTR_PAN_ID] = अणु .type = NLA_U16 पूर्ण,
	[NL802154_DEV_ATTR_SHORT_ADDR] = अणु .type = NLA_U16 पूर्ण,
	[NL802154_DEV_ATTR_EXTENDED_ADDR] = अणु .type = NLA_U64 पूर्ण,
	[NL802154_DEV_ATTR_SECLEVEL_EXEMPT] = अणु NLA_U8 पूर्ण,
	[NL802154_DEV_ATTR_KEY_MODE] = अणु NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक
ieee802154_llsec_parse_device(काष्ठा nlattr *nla,
			      काष्ठा ieee802154_llsec_device *dev)
अणु
	काष्ठा nlattr *attrs[NL802154_DEV_ATTR_MAX + 1];

	अगर (!nla || nla_parse_nested_deprecated(attrs, NL802154_DEV_ATTR_MAX, nla, nl802154_dev_policy, शून्य))
		वापस -EINVAL;

	स_रखो(dev, 0, माप(*dev));

	अगर (!attrs[NL802154_DEV_ATTR_FRAME_COUNTER] ||
	    !attrs[NL802154_DEV_ATTR_PAN_ID] ||
	    !attrs[NL802154_DEV_ATTR_SHORT_ADDR] ||
	    !attrs[NL802154_DEV_ATTR_EXTENDED_ADDR] ||
	    !attrs[NL802154_DEV_ATTR_SECLEVEL_EXEMPT] ||
	    !attrs[NL802154_DEV_ATTR_KEY_MODE])
		वापस -EINVAL;

	/* TODO be32 */
	dev->frame_counter = nla_get_u32(attrs[NL802154_DEV_ATTR_FRAME_COUNTER]);
	dev->pan_id = nla_get_le16(attrs[NL802154_DEV_ATTR_PAN_ID]);
	dev->लघु_addr = nla_get_le16(attrs[NL802154_DEV_ATTR_SHORT_ADDR]);
	/* TODO नाम hwaddr to extended_addr */
	dev->hwaddr = nla_get_le64(attrs[NL802154_DEV_ATTR_EXTENDED_ADDR]);
	dev->seclevel_exempt = nla_get_u8(attrs[NL802154_DEV_ATTR_SECLEVEL_EXEMPT]);
	dev->key_mode = nla_get_u32(attrs[NL802154_DEV_ATTR_KEY_MODE]);

	अगर (dev->key_mode > NL802154_DEVKEY_MAX ||
	    (dev->seclevel_exempt != 0 && dev->seclevel_exempt != 1))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nl802154_add_llsec_dev(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा ieee802154_llsec_device dev_desc;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	अगर (ieee802154_llsec_parse_device(info->attrs[NL802154_ATTR_SEC_DEVICE],
					  &dev_desc) < 0)
		वापस -EINVAL;

	वापस rdev_add_device(rdev, wpan_dev, &dev_desc);
पूर्ण

अटल पूर्णांक nl802154_del_llsec_dev(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा nlattr *attrs[NL802154_DEV_ATTR_MAX + 1];
	__le64 extended_addr;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL802154_ATTR_SEC_DEVICE] ||
	    nla_parse_nested_deprecated(attrs, NL802154_DEV_ATTR_MAX, info->attrs[NL802154_ATTR_SEC_DEVICE], nl802154_dev_policy, info->extack))
		वापस -EINVAL;

	अगर (!attrs[NL802154_DEV_ATTR_EXTENDED_ADDR])
		वापस -EINVAL;

	extended_addr = nla_get_le64(attrs[NL802154_DEV_ATTR_EXTENDED_ADDR]);
	वापस rdev_del_device(rdev, wpan_dev, extended_addr);
पूर्ण

अटल पूर्णांक nl802154_send_devkey(काष्ठा sk_buff *msg, u32 cmd, u32 portid,
				u32 seq, पूर्णांक flags,
				काष्ठा cfg802154_रेजिस्टरed_device *rdev,
				काष्ठा net_device *dev, __le64 extended_addr,
				स्थिर काष्ठा ieee802154_llsec_device_key *devkey)
अणु
	व्योम *hdr;
	काष्ठा nlattr *nl_devkey, *nl_key_id;

	hdr = nl802154hdr_put(msg, portid, seq, flags, cmd);
	अगर (!hdr)
		वापस -1;

	अगर (nla_put_u32(msg, NL802154_ATTR_IFINDEX, dev->अगरindex))
		जाओ nla_put_failure;

	nl_devkey = nla_nest_start_noflag(msg, NL802154_ATTR_SEC_DEVKEY);
	अगर (!nl_devkey)
		जाओ nla_put_failure;

	अगर (nla_put_le64(msg, NL802154_DEVKEY_ATTR_EXTENDED_ADDR,
			 extended_addr, NL802154_DEVKEY_ATTR_PAD) ||
	    nla_put_u32(msg, NL802154_DEVKEY_ATTR_FRAME_COUNTER,
			devkey->frame_counter))
		जाओ nla_put_failure;

	nl_key_id = nla_nest_start_noflag(msg, NL802154_DEVKEY_ATTR_ID);
	अगर (!nl_key_id)
		जाओ nla_put_failure;

	अगर (ieee802154_llsec_send_key_id(msg, &devkey->key_id) < 0)
		जाओ nla_put_failure;

	nla_nest_end(msg, nl_key_id);
	nla_nest_end(msg, nl_devkey);
	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
nl802154_dump_llsec_devkey(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = शून्य;
	काष्ठा ieee802154_llsec_device_key *kpos;
	काष्ठा ieee802154_llsec_device *dpos;
	काष्ठा ieee802154_llsec_table *table;
	काष्ठा wpan_dev *wpan_dev;
	पूर्णांक err;

	err = nl802154_prepare_wpan_dev_dump(skb, cb, &rdev, &wpan_dev);
	अगर (err)
		वापस err;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR) अणु
		err = skb->len;
		जाओ out_err;
	पूर्ण

	अगर (!wpan_dev->netdev) अणु
		err = -EINVAL;
		जाओ out_err;
	पूर्ण

	rdev_lock_llsec_table(rdev, wpan_dev);
	rdev_get_llsec_table(rdev, wpan_dev, &table);

	/* TODO make it like station dump */
	अगर (cb->args[2])
		जाओ out;

	/* TODO look अगर हटाओ devkey and करो some nested attribute */
	list_क्रम_each_entry(dpos, &table->devices, list) अणु
		list_क्रम_each_entry(kpos, &dpos->keys, list) अणु
			अगर (nl802154_send_devkey(skb,
						 NL802154_CMD_NEW_SEC_LEVEL,
						 NETLINK_CB(cb->skb).portid,
						 cb->nlh->nlmsg_seq,
						 NLM_F_MULTI, rdev,
						 wpan_dev->netdev,
						 dpos->hwaddr,
						 kpos) < 0) अणु
				/* TODO */
				err = -EIO;
				rdev_unlock_llsec_table(rdev, wpan_dev);
				जाओ out_err;
			पूर्ण
		पूर्ण
	पूर्ण

	cb->args[2] = 1;

out:
	rdev_unlock_llsec_table(rdev, wpan_dev);
	err = skb->len;
out_err:
	nl802154_finish_wpan_dev_dump(rdev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy nl802154_devkey_policy[NL802154_DEVKEY_ATTR_MAX + 1] = अणु
	[NL802154_DEVKEY_ATTR_FRAME_COUNTER] = अणु NLA_U32 पूर्ण,
	[NL802154_DEVKEY_ATTR_EXTENDED_ADDR] = अणु NLA_U64 पूर्ण,
	[NL802154_DEVKEY_ATTR_ID] = अणु NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक nl802154_add_llsec_devkey(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा nlattr *attrs[NL802154_DEVKEY_ATTR_MAX + 1];
	काष्ठा ieee802154_llsec_device_key key;
	__le64 extended_addr;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL802154_ATTR_SEC_DEVKEY] ||
	    nla_parse_nested_deprecated(attrs, NL802154_DEVKEY_ATTR_MAX, info->attrs[NL802154_ATTR_SEC_DEVKEY], nl802154_devkey_policy, info->extack) < 0)
		वापस -EINVAL;

	अगर (!attrs[NL802154_DEVKEY_ATTR_FRAME_COUNTER] ||
	    !attrs[NL802154_DEVKEY_ATTR_EXTENDED_ADDR])
		वापस -EINVAL;

	/* TODO change key.id ? */
	अगर (ieee802154_llsec_parse_key_id(attrs[NL802154_DEVKEY_ATTR_ID],
					  &key.key_id) < 0)
		वापस -ENOBUFS;

	/* TODO be32 */
	key.frame_counter = nla_get_u32(attrs[NL802154_DEVKEY_ATTR_FRAME_COUNTER]);
	/* TODO change naming hwaddr -> extended_addr
	 * check unique identअगरier लघु+pan OR extended_addr
	 */
	extended_addr = nla_get_le64(attrs[NL802154_DEVKEY_ATTR_EXTENDED_ADDR]);
	वापस rdev_add_devkey(rdev, wpan_dev, extended_addr, &key);
पूर्ण

अटल पूर्णांक nl802154_del_llsec_devkey(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा nlattr *attrs[NL802154_DEVKEY_ATTR_MAX + 1];
	काष्ठा ieee802154_llsec_device_key key;
	__le64 extended_addr;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL802154_ATTR_SEC_DEVKEY] ||
	    nla_parse_nested_deprecated(attrs, NL802154_DEVKEY_ATTR_MAX, info->attrs[NL802154_ATTR_SEC_DEVKEY], nl802154_devkey_policy, info->extack))
		वापस -EINVAL;

	अगर (!attrs[NL802154_DEVKEY_ATTR_EXTENDED_ADDR])
		वापस -EINVAL;

	/* TODO change key.id ? */
	अगर (ieee802154_llsec_parse_key_id(attrs[NL802154_DEVKEY_ATTR_ID],
					  &key.key_id) < 0)
		वापस -ENOBUFS;

	/* TODO change naming hwaddr -> extended_addr
	 * check unique identअगरier लघु+pan OR extended_addr
	 */
	extended_addr = nla_get_le64(attrs[NL802154_DEVKEY_ATTR_EXTENDED_ADDR]);
	वापस rdev_del_devkey(rdev, wpan_dev, extended_addr, &key);
पूर्ण

अटल पूर्णांक nl802154_send_seclevel(काष्ठा sk_buff *msg, u32 cmd, u32 portid,
				  u32 seq, पूर्णांक flags,
				  काष्ठा cfg802154_रेजिस्टरed_device *rdev,
				  काष्ठा net_device *dev,
				  स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	व्योम *hdr;
	काष्ठा nlattr *nl_seclevel;

	hdr = nl802154hdr_put(msg, portid, seq, flags, cmd);
	अगर (!hdr)
		वापस -1;

	अगर (nla_put_u32(msg, NL802154_ATTR_IFINDEX, dev->अगरindex))
		जाओ nla_put_failure;

	nl_seclevel = nla_nest_start_noflag(msg, NL802154_ATTR_SEC_LEVEL);
	अगर (!nl_seclevel)
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL802154_SECLEVEL_ATTR_FRAME, sl->frame_type) ||
	    nla_put_u32(msg, NL802154_SECLEVEL_ATTR_LEVELS, sl->sec_levels) ||
	    nla_put_u8(msg, NL802154_SECLEVEL_ATTR_DEV_OVERRIDE,
		       sl->device_override))
		जाओ nla_put_failure;

	अगर (sl->frame_type == NL802154_FRAME_CMD) अणु
		अगर (nla_put_u32(msg, NL802154_SECLEVEL_ATTR_CMD_FRAME,
				sl->cmd_frame_id))
			जाओ nla_put_failure;
	पूर्ण

	nla_nest_end(msg, nl_seclevel);
	genlmsg_end(msg, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
nl802154_dump_llsec_seclevel(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = शून्य;
	काष्ठा ieee802154_llsec_seclevel *sl;
	काष्ठा ieee802154_llsec_table *table;
	काष्ठा wpan_dev *wpan_dev;
	पूर्णांक err;

	err = nl802154_prepare_wpan_dev_dump(skb, cb, &rdev, &wpan_dev);
	अगर (err)
		वापस err;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR) अणु
		err = skb->len;
		जाओ out_err;
	पूर्ण

	अगर (!wpan_dev->netdev) अणु
		err = -EINVAL;
		जाओ out_err;
	पूर्ण

	rdev_lock_llsec_table(rdev, wpan_dev);
	rdev_get_llsec_table(rdev, wpan_dev, &table);

	/* TODO make it like station dump */
	अगर (cb->args[2])
		जाओ out;

	list_क्रम_each_entry(sl, &table->security_levels, list) अणु
		अगर (nl802154_send_seclevel(skb, NL802154_CMD_NEW_SEC_LEVEL,
					   NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq, NLM_F_MULTI,
					   rdev, wpan_dev->netdev, sl) < 0) अणु
			/* TODO */
			err = -EIO;
			rdev_unlock_llsec_table(rdev, wpan_dev);
			जाओ out_err;
		पूर्ण
	पूर्ण

	cb->args[2] = 1;

out:
	rdev_unlock_llsec_table(rdev, wpan_dev);
	err = skb->len;
out_err:
	nl802154_finish_wpan_dev_dump(rdev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy nl802154_seclevel_policy[NL802154_SECLEVEL_ATTR_MAX + 1] = अणु
	[NL802154_SECLEVEL_ATTR_LEVELS] = अणु .type = NLA_U8 पूर्ण,
	[NL802154_SECLEVEL_ATTR_FRAME] = अणु .type = NLA_U32 पूर्ण,
	[NL802154_SECLEVEL_ATTR_CMD_FRAME] = अणु .type = NLA_U32 पूर्ण,
	[NL802154_SECLEVEL_ATTR_DEV_OVERRIDE] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक
llsec_parse_seclevel(काष्ठा nlattr *nla, काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	काष्ठा nlattr *attrs[NL802154_SECLEVEL_ATTR_MAX + 1];

	अगर (!nla || nla_parse_nested_deprecated(attrs, NL802154_SECLEVEL_ATTR_MAX, nla, nl802154_seclevel_policy, शून्य))
		वापस -EINVAL;

	स_रखो(sl, 0, माप(*sl));

	अगर (!attrs[NL802154_SECLEVEL_ATTR_LEVELS] ||
	    !attrs[NL802154_SECLEVEL_ATTR_FRAME] ||
	    !attrs[NL802154_SECLEVEL_ATTR_DEV_OVERRIDE])
		वापस -EINVAL;

	sl->sec_levels = nla_get_u8(attrs[NL802154_SECLEVEL_ATTR_LEVELS]);
	sl->frame_type = nla_get_u32(attrs[NL802154_SECLEVEL_ATTR_FRAME]);
	sl->device_override = nla_get_u8(attrs[NL802154_SECLEVEL_ATTR_DEV_OVERRIDE]);
	अगर (sl->frame_type > NL802154_FRAME_MAX ||
	    (sl->device_override != 0 && sl->device_override != 1))
		वापस -EINVAL;

	अगर (sl->frame_type == NL802154_FRAME_CMD) अणु
		अगर (!attrs[NL802154_SECLEVEL_ATTR_CMD_FRAME])
			वापस -EINVAL;

		sl->cmd_frame_id = nla_get_u32(attrs[NL802154_SECLEVEL_ATTR_CMD_FRAME]);
		अगर (sl->cmd_frame_id > NL802154_CMD_FRAME_MAX)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl802154_add_llsec_seclevel(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा ieee802154_llsec_seclevel sl;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	अगर (llsec_parse_seclevel(info->attrs[NL802154_ATTR_SEC_LEVEL],
				 &sl) < 0)
		वापस -EINVAL;

	वापस rdev_add_seclevel(rdev, wpan_dev, &sl);
पूर्ण

अटल पूर्णांक nl802154_del_llsec_seclevel(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;
	काष्ठा ieee802154_llsec_seclevel sl;

	अगर (wpan_dev->अगरtype == NL802154_IFTYPE_MONITOR)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL802154_ATTR_SEC_LEVEL] ||
	    llsec_parse_seclevel(info->attrs[NL802154_ATTR_SEC_LEVEL],
				 &sl) < 0)
		वापस -EINVAL;

	वापस rdev_del_seclevel(rdev, wpan_dev, &sl);
पूर्ण
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */

#घोषणा NL802154_FLAG_NEED_WPAN_PHY	0x01
#घोषणा NL802154_FLAG_NEED_NETDEV	0x02
#घोषणा NL802154_FLAG_NEED_RTNL		0x04
#घोषणा NL802154_FLAG_CHECK_NETDEV_UP	0x08
#घोषणा NL802154_FLAG_NEED_WPAN_DEV	0x10

अटल पूर्णांक nl802154_pre_करोit(स्थिर काष्ठा genl_ops *ops, काष्ठा sk_buff *skb,
			     काष्ठा genl_info *info)
अणु
	काष्ठा cfg802154_रेजिस्टरed_device *rdev;
	काष्ठा wpan_dev *wpan_dev;
	काष्ठा net_device *dev;
	bool rtnl = ops->पूर्णांकernal_flags & NL802154_FLAG_NEED_RTNL;

	अगर (rtnl)
		rtnl_lock();

	अगर (ops->पूर्णांकernal_flags & NL802154_FLAG_NEED_WPAN_PHY) अणु
		rdev = cfg802154_get_dev_from_info(genl_info_net(info), info);
		अगर (IS_ERR(rdev)) अणु
			अगर (rtnl)
				rtnl_unlock();
			वापस PTR_ERR(rdev);
		पूर्ण
		info->user_ptr[0] = rdev;
	पूर्ण अन्यथा अगर (ops->पूर्णांकernal_flags & NL802154_FLAG_NEED_NETDEV ||
		   ops->पूर्णांकernal_flags & NL802154_FLAG_NEED_WPAN_DEV) अणु
		ASSERT_RTNL();
		wpan_dev = __cfg802154_wpan_dev_from_attrs(genl_info_net(info),
							   info->attrs);
		अगर (IS_ERR(wpan_dev)) अणु
			अगर (rtnl)
				rtnl_unlock();
			वापस PTR_ERR(wpan_dev);
		पूर्ण

		dev = wpan_dev->netdev;
		rdev = wpan_phy_to_rdev(wpan_dev->wpan_phy);

		अगर (ops->पूर्णांकernal_flags & NL802154_FLAG_NEED_NETDEV) अणु
			अगर (!dev) अणु
				अगर (rtnl)
					rtnl_unlock();
				वापस -EINVAL;
			पूर्ण

			info->user_ptr[1] = dev;
		पूर्ण अन्यथा अणु
			info->user_ptr[1] = wpan_dev;
		पूर्ण

		अगर (dev) अणु
			अगर (ops->पूर्णांकernal_flags & NL802154_FLAG_CHECK_NETDEV_UP &&
			    !netअगर_running(dev)) अणु
				अगर (rtnl)
					rtnl_unlock();
				वापस -ENETDOWN;
			पूर्ण

			dev_hold(dev);
		पूर्ण

		info->user_ptr[0] = rdev;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nl802154_post_करोit(स्थिर काष्ठा genl_ops *ops, काष्ठा sk_buff *skb,
			       काष्ठा genl_info *info)
अणु
	अगर (info->user_ptr[1]) अणु
		अगर (ops->पूर्णांकernal_flags & NL802154_FLAG_NEED_WPAN_DEV) अणु
			काष्ठा wpan_dev *wpan_dev = info->user_ptr[1];

			अगर (wpan_dev->netdev)
				dev_put(wpan_dev->netdev);
		पूर्ण अन्यथा अणु
			dev_put(info->user_ptr[1]);
		पूर्ण
	पूर्ण

	अगर (ops->पूर्णांकernal_flags & NL802154_FLAG_NEED_RTNL)
		rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा genl_ops nl802154_ops[] = अणु
	अणु
		.cmd = NL802154_CMD_GET_WPAN_PHY,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		.करोit = nl802154_get_wpan_phy,
		.dumpit = nl802154_dump_wpan_phy,
		.करोne = nl802154_dump_wpan_phy_करोne,
		/* can be retrieved by unprivileged users */
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_GET_INTERFACE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_get_पूर्णांकerface,
		.dumpit = nl802154_dump_पूर्णांकerface,
		/* can be retrieved by unprivileged users */
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_WPAN_DEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_NEW_INTERFACE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_new_पूर्णांकerface,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_DEL_INTERFACE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_del_पूर्णांकerface,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_WPAN_DEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_CHANNEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_channel,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_CCA_MODE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_cca_mode,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_CCA_ED_LEVEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_cca_ed_level,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_TX_POWER,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_tx_घातer,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_WPAN_PHY_NETNS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_wpan_phy_netns,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_WPAN_PHY |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_PAN_ID,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_pan_id,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_SHORT_ADDR,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_लघु_addr,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_BACKOFF_EXPONENT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_backoff_exponent,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_MAX_CSMA_BACKOFFS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_max_csma_backoffs,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_MAX_FRAME_RETRIES,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_max_frame_retries,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_LBT_MODE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_lbt_mode,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_SET_ACKREQ_DEFAULT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_ackreq_शेष,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
	अणु
		.cmd = NL802154_CMD_SET_SEC_PARAMS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_set_llsec_params,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_GET_SEC_KEY,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		/* TODO .करोit by matching key id? */
		.dumpit = nl802154_dump_llsec_key,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_NEW_SEC_KEY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_add_llsec_key,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_DEL_SEC_KEY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_del_llsec_key,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	/* TODO unique identअगरier must लघु+pan OR extended_addr */
	अणु
		.cmd = NL802154_CMD_GET_SEC_DEV,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		/* TODO .करोit by matching extended_addr? */
		.dumpit = nl802154_dump_llsec_dev,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_NEW_SEC_DEV,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_add_llsec_dev,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_DEL_SEC_DEV,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_del_llsec_dev,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	/* TODO हटाओ complete devkey, put it as nested? */
	अणु
		.cmd = NL802154_CMD_GET_SEC_DEVKEY,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		/* TODO करोit by matching ??? */
		.dumpit = nl802154_dump_llsec_devkey,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_NEW_SEC_DEVKEY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_add_llsec_devkey,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_DEL_SEC_DEVKEY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_del_llsec_devkey,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_GET_SEC_LEVEL,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		/* TODO .करोit by matching frame_type? */
		.dumpit = nl802154_dump_llsec_seclevel,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_NEW_SEC_LEVEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl802154_add_llsec_seclevel,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL802154_CMD_DEL_SEC_LEVEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		/* TODO match frame_type only? */
		.करोit = nl802154_del_llsec_seclevel,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL802154_FLAG_NEED_NETDEV |
				  NL802154_FLAG_NEED_RTNL,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */
पूर्ण;

अटल काष्ठा genl_family nl802154_fam __ro_after_init = अणु
	.name = NL802154_GENL_NAME,	/* have users key off the name instead */
	.hdrsize = 0,			/* no निजी header */
	.version = 1,			/* no particular meaning now */
	.maxattr = NL802154_ATTR_MAX,
	.policy = nl802154_policy,
	.netnsok = true,
	.pre_करोit = nl802154_pre_करोit,
	.post_करोit = nl802154_post_करोit,
	.module = THIS_MODULE,
	.ops = nl802154_ops,
	.n_ops = ARRAY_SIZE(nl802154_ops),
	.mcgrps = nl802154_mcgrps,
	.n_mcgrps = ARRAY_SIZE(nl802154_mcgrps),
पूर्ण;

/* initialisation/निकास functions */
पूर्णांक __init nl802154_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&nl802154_fam);
पूर्ण

व्योम nl802154_निकास(व्योम)
अणु
	genl_unरेजिस्टर_family(&nl802154_fam);
पूर्ण
