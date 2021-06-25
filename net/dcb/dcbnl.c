<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2011, Intel Corporation.
 *
 * Description: Data Center Bridging netlink पूर्णांकerface
 * Author: Lucy Liu <lucy.liu@पूर्णांकel.com>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/slab.h>
#समावेश <net/netlink.h>
#समावेश <net/rtnetlink.h>
#समावेश <linux/dcbnl.h>
#समावेश <net/dcbevent.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/init.h>
#समावेश <net/sock.h>

/* Data Center Bridging (DCB) is a collection of Ethernet enhancements
 * पूर्णांकended to allow network traffic with dअगरfering requirements
 * (highly reliable, no drops vs. best efक्रमt vs. low latency) to operate
 * and co-exist on Ethernet.  Current DCB features are:
 *
 * Enhanced Transmission Selection (aka Priority Grouping [PG]) - provides a
 *   framework क्रम assigning bandwidth guarantees to traffic classes.
 *
 * Priority-based Flow Control (PFC) - provides a flow control mechanism which
 *   can work independently क्रम each 802.1p priority.
 *
 * Congestion Notअगरication - provides a mechanism क्रम end-to-end congestion
 *   control क्रम protocols which करो not have built-in congestion management.
 *
 * More inक्रमmation about the emerging standards क्रम these Ethernet features
 * can be found at: http://www.ieee802.org/1/pages/dcbridges.hपंचांगl
 *
 * This file implements an rtnetlink पूर्णांकerface to allow configuration of DCB
 * features क्रम capable devices.
 */

/**************** DCB attribute policies *************************************/

/* DCB netlink attributes policy */
अटल स्थिर काष्ठा nla_policy dcbnl_rtnl_policy[DCB_ATTR_MAX + 1] = अणु
	[DCB_ATTR_IFNAME]      = अणु.type = NLA_NUL_STRING, .len = IFNAMSIZ - 1पूर्ण,
	[DCB_ATTR_STATE]       = अणु.type = NLA_U8पूर्ण,
	[DCB_ATTR_PFC_CFG]     = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_ATTR_PG_CFG]      = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_ATTR_SET_ALL]     = अणु.type = NLA_U8पूर्ण,
	[DCB_ATTR_PERM_HWADDR] = अणु.type = NLA_FLAGपूर्ण,
	[DCB_ATTR_CAP]         = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_ATTR_PFC_STATE]   = अणु.type = NLA_U8पूर्ण,
	[DCB_ATTR_BCN]         = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_ATTR_APP]         = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_ATTR_IEEE]	       = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_ATTR_DCBX]        = अणु.type = NLA_U8पूर्ण,
	[DCB_ATTR_FEATCFG]     = अणु.type = NLA_NESTEDपूर्ण,
पूर्ण;

/* DCB priority flow control to User Priority nested attributes */
अटल स्थिर काष्ठा nla_policy dcbnl_pfc_up_nest[DCB_PFC_UP_ATTR_MAX + 1] = अणु
	[DCB_PFC_UP_ATTR_0]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PFC_UP_ATTR_1]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PFC_UP_ATTR_2]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PFC_UP_ATTR_3]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PFC_UP_ATTR_4]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PFC_UP_ATTR_5]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PFC_UP_ATTR_6]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PFC_UP_ATTR_7]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PFC_UP_ATTR_ALL] = अणु.type = NLA_FLAGपूर्ण,
पूर्ण;

/* DCB priority grouping nested attributes */
अटल स्थिर काष्ठा nla_policy dcbnl_pg_nest[DCB_PG_ATTR_MAX + 1] = अणु
	[DCB_PG_ATTR_TC_0]      = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_PG_ATTR_TC_1]      = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_PG_ATTR_TC_2]      = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_PG_ATTR_TC_3]      = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_PG_ATTR_TC_4]      = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_PG_ATTR_TC_5]      = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_PG_ATTR_TC_6]      = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_PG_ATTR_TC_7]      = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_PG_ATTR_TC_ALL]    = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_PG_ATTR_BW_ID_0]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PG_ATTR_BW_ID_1]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PG_ATTR_BW_ID_2]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PG_ATTR_BW_ID_3]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PG_ATTR_BW_ID_4]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PG_ATTR_BW_ID_5]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PG_ATTR_BW_ID_6]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PG_ATTR_BW_ID_7]   = अणु.type = NLA_U8पूर्ण,
	[DCB_PG_ATTR_BW_ID_ALL] = अणु.type = NLA_FLAGपूर्ण,
पूर्ण;

/* DCB traffic class nested attributes. */
अटल स्थिर काष्ठा nla_policy dcbnl_tc_param_nest[DCB_TC_ATTR_PARAM_MAX + 1] = अणु
	[DCB_TC_ATTR_PARAM_PGID]            = अणु.type = NLA_U8पूर्ण,
	[DCB_TC_ATTR_PARAM_UP_MAPPING]      = अणु.type = NLA_U8पूर्ण,
	[DCB_TC_ATTR_PARAM_STRICT_PRIO]     = अणु.type = NLA_U8पूर्ण,
	[DCB_TC_ATTR_PARAM_BW_PCT]          = अणु.type = NLA_U8पूर्ण,
	[DCB_TC_ATTR_PARAM_ALL]             = अणु.type = NLA_FLAGपूर्ण,
पूर्ण;

/* DCB capabilities nested attributes. */
अटल स्थिर काष्ठा nla_policy dcbnl_cap_nest[DCB_CAP_ATTR_MAX + 1] = अणु
	[DCB_CAP_ATTR_ALL]     = अणु.type = NLA_FLAGपूर्ण,
	[DCB_CAP_ATTR_PG]      = अणु.type = NLA_U8पूर्ण,
	[DCB_CAP_ATTR_PFC]     = अणु.type = NLA_U8पूर्ण,
	[DCB_CAP_ATTR_UP2TC]   = अणु.type = NLA_U8पूर्ण,
	[DCB_CAP_ATTR_PG_TCS]  = अणु.type = NLA_U8पूर्ण,
	[DCB_CAP_ATTR_PFC_TCS] = अणु.type = NLA_U8पूर्ण,
	[DCB_CAP_ATTR_GSP]     = अणु.type = NLA_U8पूर्ण,
	[DCB_CAP_ATTR_BCN]     = अणु.type = NLA_U8पूर्ण,
	[DCB_CAP_ATTR_DCBX]    = अणु.type = NLA_U8पूर्ण,
पूर्ण;

/* DCB capabilities nested attributes. */
अटल स्थिर काष्ठा nla_policy dcbnl_numtcs_nest[DCB_NUMTCS_ATTR_MAX + 1] = अणु
	[DCB_NUMTCS_ATTR_ALL]     = अणु.type = NLA_FLAGपूर्ण,
	[DCB_NUMTCS_ATTR_PG]      = अणु.type = NLA_U8पूर्ण,
	[DCB_NUMTCS_ATTR_PFC]     = अणु.type = NLA_U8पूर्ण,
पूर्ण;

/* DCB BCN nested attributes. */
अटल स्थिर काष्ठा nla_policy dcbnl_bcn_nest[DCB_BCN_ATTR_MAX + 1] = अणु
	[DCB_BCN_ATTR_RP_0]         = अणु.type = NLA_U8पूर्ण,
	[DCB_BCN_ATTR_RP_1]         = अणु.type = NLA_U8पूर्ण,
	[DCB_BCN_ATTR_RP_2]         = अणु.type = NLA_U8पूर्ण,
	[DCB_BCN_ATTR_RP_3]         = अणु.type = NLA_U8पूर्ण,
	[DCB_BCN_ATTR_RP_4]         = अणु.type = NLA_U8पूर्ण,
	[DCB_BCN_ATTR_RP_5]         = अणु.type = NLA_U8पूर्ण,
	[DCB_BCN_ATTR_RP_6]         = अणु.type = NLA_U8पूर्ण,
	[DCB_BCN_ATTR_RP_7]         = अणु.type = NLA_U8पूर्ण,
	[DCB_BCN_ATTR_RP_ALL]       = अणु.type = NLA_FLAGपूर्ण,
	[DCB_BCN_ATTR_BCNA_0]       = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_BCNA_1]       = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_ALPHA]        = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_BETA]         = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_GD]           = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_GI]           = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_TMAX]         = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_TD]           = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_RMIN]         = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_W]            = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_RD]           = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_RU]           = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_WRTT]         = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_RI]           = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_C]            = अणु.type = NLA_U32पूर्ण,
	[DCB_BCN_ATTR_ALL]          = अणु.type = NLA_FLAGपूर्ण,
पूर्ण;

/* DCB APP nested attributes. */
अटल स्थिर काष्ठा nla_policy dcbnl_app_nest[DCB_APP_ATTR_MAX + 1] = अणु
	[DCB_APP_ATTR_IDTYPE]       = अणु.type = NLA_U8पूर्ण,
	[DCB_APP_ATTR_ID]           = अणु.type = NLA_U16पूर्ण,
	[DCB_APP_ATTR_PRIORITY]     = अणु.type = NLA_U8पूर्ण,
पूर्ण;

/* IEEE 802.1Qaz nested attributes. */
अटल स्थिर काष्ठा nla_policy dcbnl_ieee_policy[DCB_ATTR_IEEE_MAX + 1] = अणु
	[DCB_ATTR_IEEE_ETS]	    = अणु.len = माप(काष्ठा ieee_ets)पूर्ण,
	[DCB_ATTR_IEEE_PFC]	    = अणु.len = माप(काष्ठा ieee_pfc)पूर्ण,
	[DCB_ATTR_IEEE_APP_TABLE]   = अणु.type = NLA_NESTEDपूर्ण,
	[DCB_ATTR_IEEE_MAXRATE]   = अणु.len = माप(काष्ठा ieee_maxrate)पूर्ण,
	[DCB_ATTR_IEEE_QCN]         = अणु.len = माप(काष्ठा ieee_qcn)पूर्ण,
	[DCB_ATTR_IEEE_QCN_STATS]   = अणु.len = माप(काष्ठा ieee_qcn_stats)पूर्ण,
	[DCB_ATTR_DCB_BUFFER]       = अणु.len = माप(काष्ठा dcbnl_buffer)पूर्ण,
पूर्ण;

/* DCB number of traffic classes nested attributes. */
अटल स्थिर काष्ठा nla_policy dcbnl_featcfg_nest[DCB_FEATCFG_ATTR_MAX + 1] = अणु
	[DCB_FEATCFG_ATTR_ALL]      = अणु.type = NLA_FLAGपूर्ण,
	[DCB_FEATCFG_ATTR_PG]       = अणु.type = NLA_U8पूर्ण,
	[DCB_FEATCFG_ATTR_PFC]      = अणु.type = NLA_U8पूर्ण,
	[DCB_FEATCFG_ATTR_APP]      = अणु.type = NLA_U8पूर्ण,
पूर्ण;

अटल LIST_HEAD(dcb_app_list);
अटल DEFINE_SPINLOCK(dcb_lock);

अटल काष्ठा sk_buff *dcbnl_newmsg(पूर्णांक type, u8 cmd, u32 port, u32 seq,
				    u32 flags, काष्ठा nlmsghdr **nlhp)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा dcbmsg *dcb;
	काष्ठा nlmsghdr *nlh;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	nlh = nlmsg_put(skb, port, seq, type, माप(*dcb), flags);
	BUG_ON(!nlh);

	dcb = nlmsg_data(nlh);
	dcb->dcb_family = AF_UNSPEC;
	dcb->cmd = cmd;
	dcb->dcb_pad = 0;

	अगर (nlhp)
		*nlhp = nlh;

	वापस skb;
पूर्ण

अटल पूर्णांक dcbnl_माला_लोtate(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			  u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	/* अगर (!tb[DCB_ATTR_STATE] || !netdev->dcbnl_ops->माला_लोtate) */
	अगर (!netdev->dcbnl_ops->माला_लोtate)
		वापस -EOPNOTSUPP;

	वापस nla_put_u8(skb, DCB_ATTR_STATE,
			  netdev->dcbnl_ops->माला_लोtate(netdev));
पूर्ण

अटल पूर्णांक dcbnl_getpfccfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			   u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *data[DCB_PFC_UP_ATTR_MAX + 1], *nest;
	u8 value;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक getall = 0;

	अगर (!tb[DCB_ATTR_PFC_CFG])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->getpfccfg)
		वापस -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(data, DCB_PFC_UP_ATTR_MAX,
					  tb[DCB_ATTR_PFC_CFG],
					  dcbnl_pfc_up_nest, शून्य);
	अगर (ret)
		वापस ret;

	nest = nla_nest_start_noflag(skb, DCB_ATTR_PFC_CFG);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (data[DCB_PFC_UP_ATTR_ALL])
		getall = 1;

	क्रम (i = DCB_PFC_UP_ATTR_0; i <= DCB_PFC_UP_ATTR_7; i++) अणु
		अगर (!getall && !data[i])
			जारी;

		netdev->dcbnl_ops->getpfccfg(netdev, i - DCB_PFC_UP_ATTR_0,
		                             &value);
		ret = nla_put_u8(skb, i, value);
		अगर (ret) अणु
			nla_nest_cancel(skb, nest);
			वापस ret;
		पूर्ण
	पूर्ण
	nla_nest_end(skb, nest);

	वापस 0;
पूर्ण

अटल पूर्णांक dcbnl_getperm_hwaddr(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
				u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	u8 perm_addr[MAX_ADDR_LEN];

	अगर (!netdev->dcbnl_ops->getpermhwaddr)
		वापस -EOPNOTSUPP;

	स_रखो(perm_addr, 0, माप(perm_addr));
	netdev->dcbnl_ops->getpermhwaddr(netdev, perm_addr);

	वापस nla_put(skb, DCB_ATTR_PERM_HWADDR, माप(perm_addr), perm_addr);
पूर्ण

अटल पूर्णांक dcbnl_अ_लोap(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *data[DCB_CAP_ATTR_MAX + 1], *nest;
	u8 value;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक getall = 0;

	अगर (!tb[DCB_ATTR_CAP])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->अ_लोap)
		वापस -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(data, DCB_CAP_ATTR_MAX,
					  tb[DCB_ATTR_CAP], dcbnl_cap_nest,
					  शून्य);
	अगर (ret)
		वापस ret;

	nest = nla_nest_start_noflag(skb, DCB_ATTR_CAP);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (data[DCB_CAP_ATTR_ALL])
		getall = 1;

	क्रम (i = DCB_CAP_ATTR_ALL+1; i <= DCB_CAP_ATTR_MAX; i++) अणु
		अगर (!getall && !data[i])
			जारी;

		अगर (!netdev->dcbnl_ops->अ_लोap(netdev, i, &value)) अणु
			ret = nla_put_u8(skb, i, value);
			अगर (ret) अणु
				nla_nest_cancel(skb, nest);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	nla_nest_end(skb, nest);

	वापस 0;
पूर्ण

अटल पूर्णांक dcbnl_getnumtcs(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			   u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *data[DCB_NUMTCS_ATTR_MAX + 1], *nest;
	u8 value;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक getall = 0;

	अगर (!tb[DCB_ATTR_NUMTCS])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->getnumtcs)
		वापस -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(data, DCB_NUMTCS_ATTR_MAX,
					  tb[DCB_ATTR_NUMTCS],
					  dcbnl_numtcs_nest, शून्य);
	अगर (ret)
		वापस ret;

	nest = nla_nest_start_noflag(skb, DCB_ATTR_NUMTCS);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (data[DCB_NUMTCS_ATTR_ALL])
		getall = 1;

	क्रम (i = DCB_NUMTCS_ATTR_ALL+1; i <= DCB_NUMTCS_ATTR_MAX; i++) अणु
		अगर (!getall && !data[i])
			जारी;

		ret = netdev->dcbnl_ops->getnumtcs(netdev, i, &value);
		अगर (!ret) अणु
			ret = nla_put_u8(skb, i, value);
			अगर (ret) अणु
				nla_nest_cancel(skb, nest);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण
	nla_nest_end(skb, nest);

	वापस 0;
पूर्ण

अटल पूर्णांक dcbnl_setnumtcs(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			   u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *data[DCB_NUMTCS_ATTR_MAX + 1];
	पूर्णांक ret;
	u8 value;
	पूर्णांक i;

	अगर (!tb[DCB_ATTR_NUMTCS])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->setnumtcs)
		वापस -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(data, DCB_NUMTCS_ATTR_MAX,
					  tb[DCB_ATTR_NUMTCS],
					  dcbnl_numtcs_nest, शून्य);
	अगर (ret)
		वापस ret;

	क्रम (i = DCB_NUMTCS_ATTR_ALL+1; i <= DCB_NUMTCS_ATTR_MAX; i++) अणु
		अगर (data[i] == शून्य)
			जारी;

		value = nla_get_u8(data[i]);

		ret = netdev->dcbnl_ops->setnumtcs(netdev, i, value);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस nla_put_u8(skb, DCB_ATTR_NUMTCS, !!ret);
पूर्ण

अटल पूर्णांक dcbnl_getpfcstate(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			     u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	अगर (!netdev->dcbnl_ops->getpfcstate)
		वापस -EOPNOTSUPP;

	वापस nla_put_u8(skb, DCB_ATTR_PFC_STATE,
			  netdev->dcbnl_ops->getpfcstate(netdev));
पूर्ण

अटल पूर्णांक dcbnl_setpfcstate(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			     u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	u8 value;

	अगर (!tb[DCB_ATTR_PFC_STATE])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->setpfcstate)
		वापस -EOPNOTSUPP;

	value = nla_get_u8(tb[DCB_ATTR_PFC_STATE]);

	netdev->dcbnl_ops->setpfcstate(netdev, value);

	वापस nla_put_u8(skb, DCB_ATTR_PFC_STATE, 0);
पूर्ण

अटल पूर्णांक dcbnl_getapp(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *app_nest;
	काष्ठा nlattr *app_tb[DCB_APP_ATTR_MAX + 1];
	u16 id;
	u8 up, idtype;
	पूर्णांक ret;

	अगर (!tb[DCB_ATTR_APP])
		वापस -EINVAL;

	ret = nla_parse_nested_deprecated(app_tb, DCB_APP_ATTR_MAX,
					  tb[DCB_ATTR_APP], dcbnl_app_nest,
					  शून्य);
	अगर (ret)
		वापस ret;

	/* all must be non-null */
	अगर ((!app_tb[DCB_APP_ATTR_IDTYPE]) ||
	    (!app_tb[DCB_APP_ATTR_ID]))
		वापस -EINVAL;

	/* either by eth type or by socket number */
	idtype = nla_get_u8(app_tb[DCB_APP_ATTR_IDTYPE]);
	अगर ((idtype != DCB_APP_IDTYPE_ETHTYPE) &&
	    (idtype != DCB_APP_IDTYPE_PORTNUM))
		वापस -EINVAL;

	id = nla_get_u16(app_tb[DCB_APP_ATTR_ID]);

	अगर (netdev->dcbnl_ops->getapp) अणु
		ret = netdev->dcbnl_ops->getapp(netdev, idtype, id);
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			up = ret;
	पूर्ण अन्यथा अणु
		काष्ठा dcb_app app = अणु
					.selector = idtype,
					.protocol = id,
				     पूर्ण;
		up = dcb_getapp(netdev, &app);
	पूर्ण

	app_nest = nla_nest_start_noflag(skb, DCB_ATTR_APP);
	अगर (!app_nest)
		वापस -EMSGSIZE;

	ret = nla_put_u8(skb, DCB_APP_ATTR_IDTYPE, idtype);
	अगर (ret)
		जाओ out_cancel;

	ret = nla_put_u16(skb, DCB_APP_ATTR_ID, id);
	अगर (ret)
		जाओ out_cancel;

	ret = nla_put_u8(skb, DCB_APP_ATTR_PRIORITY, up);
	अगर (ret)
		जाओ out_cancel;

	nla_nest_end(skb, app_nest);

	वापस 0;

out_cancel:
	nla_nest_cancel(skb, app_nest);
	वापस ret;
पूर्ण

अटल पूर्णांक dcbnl_setapp(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	u16 id;
	u8 up, idtype;
	काष्ठा nlattr *app_tb[DCB_APP_ATTR_MAX + 1];

	अगर (!tb[DCB_ATTR_APP])
		वापस -EINVAL;

	ret = nla_parse_nested_deprecated(app_tb, DCB_APP_ATTR_MAX,
					  tb[DCB_ATTR_APP], dcbnl_app_nest,
					  शून्य);
	अगर (ret)
		वापस ret;

	/* all must be non-null */
	अगर ((!app_tb[DCB_APP_ATTR_IDTYPE]) ||
	    (!app_tb[DCB_APP_ATTR_ID]) ||
	    (!app_tb[DCB_APP_ATTR_PRIORITY]))
		वापस -EINVAL;

	/* either by eth type or by socket number */
	idtype = nla_get_u8(app_tb[DCB_APP_ATTR_IDTYPE]);
	अगर ((idtype != DCB_APP_IDTYPE_ETHTYPE) &&
	    (idtype != DCB_APP_IDTYPE_PORTNUM))
		वापस -EINVAL;

	id = nla_get_u16(app_tb[DCB_APP_ATTR_ID]);
	up = nla_get_u8(app_tb[DCB_APP_ATTR_PRIORITY]);

	अगर (netdev->dcbnl_ops->setapp) अणु
		ret = netdev->dcbnl_ops->setapp(netdev, idtype, id, up);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		काष्ठा dcb_app app;
		app.selector = idtype;
		app.protocol = id;
		app.priority = up;
		ret = dcb_setapp(netdev, &app);
	पूर्ण

	ret = nla_put_u8(skb, DCB_ATTR_APP, ret);
	dcbnl_cee_notअगरy(netdev, RTM_SETDCB, DCB_CMD_SAPP, seq, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक __dcbnl_pg_अ_लोfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			     काष्ठा nlattr **tb, काष्ठा sk_buff *skb, पूर्णांक dir)
अणु
	काष्ठा nlattr *pg_nest, *param_nest, *data;
	काष्ठा nlattr *pg_tb[DCB_PG_ATTR_MAX + 1];
	काष्ठा nlattr *param_tb[DCB_TC_ATTR_PARAM_MAX + 1];
	u8 prio, pgid, tc_pct, up_map;
	पूर्णांक ret;
	पूर्णांक getall = 0;
	पूर्णांक i;

	अगर (!tb[DCB_ATTR_PG_CFG])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->getpgtccfgtx ||
	    !netdev->dcbnl_ops->getpgtccfgrx ||
	    !netdev->dcbnl_ops->getpgbwgcfgtx ||
	    !netdev->dcbnl_ops->getpgbwgcfgrx)
		वापस -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(pg_tb, DCB_PG_ATTR_MAX,
					  tb[DCB_ATTR_PG_CFG], dcbnl_pg_nest,
					  शून्य);
	अगर (ret)
		वापस ret;

	pg_nest = nla_nest_start_noflag(skb, DCB_ATTR_PG_CFG);
	अगर (!pg_nest)
		वापस -EMSGSIZE;

	अगर (pg_tb[DCB_PG_ATTR_TC_ALL])
		getall = 1;

	क्रम (i = DCB_PG_ATTR_TC_0; i <= DCB_PG_ATTR_TC_7; i++) अणु
		अगर (!getall && !pg_tb[i])
			जारी;

		अगर (pg_tb[DCB_PG_ATTR_TC_ALL])
			data = pg_tb[DCB_PG_ATTR_TC_ALL];
		अन्यथा
			data = pg_tb[i];
		ret = nla_parse_nested_deprecated(param_tb,
						  DCB_TC_ATTR_PARAM_MAX, data,
						  dcbnl_tc_param_nest, शून्य);
		अगर (ret)
			जाओ err_pg;

		param_nest = nla_nest_start_noflag(skb, i);
		अगर (!param_nest)
			जाओ err_pg;

		pgid = DCB_ATTR_VALUE_UNDEFINED;
		prio = DCB_ATTR_VALUE_UNDEFINED;
		tc_pct = DCB_ATTR_VALUE_UNDEFINED;
		up_map = DCB_ATTR_VALUE_UNDEFINED;

		अगर (dir) अणु
			/* Rx */
			netdev->dcbnl_ops->getpgtccfgrx(netdev,
						i - DCB_PG_ATTR_TC_0, &prio,
						&pgid, &tc_pct, &up_map);
		पूर्ण अन्यथा अणु
			/* Tx */
			netdev->dcbnl_ops->getpgtccfgtx(netdev,
						i - DCB_PG_ATTR_TC_0, &prio,
						&pgid, &tc_pct, &up_map);
		पूर्ण

		अगर (param_tb[DCB_TC_ATTR_PARAM_PGID] ||
		    param_tb[DCB_TC_ATTR_PARAM_ALL]) अणु
			ret = nla_put_u8(skb,
			                 DCB_TC_ATTR_PARAM_PGID, pgid);
			अगर (ret)
				जाओ err_param;
		पूर्ण
		अगर (param_tb[DCB_TC_ATTR_PARAM_UP_MAPPING] ||
		    param_tb[DCB_TC_ATTR_PARAM_ALL]) अणु
			ret = nla_put_u8(skb,
			                 DCB_TC_ATTR_PARAM_UP_MAPPING, up_map);
			अगर (ret)
				जाओ err_param;
		पूर्ण
		अगर (param_tb[DCB_TC_ATTR_PARAM_STRICT_PRIO] ||
		    param_tb[DCB_TC_ATTR_PARAM_ALL]) अणु
			ret = nla_put_u8(skb,
			                 DCB_TC_ATTR_PARAM_STRICT_PRIO, prio);
			अगर (ret)
				जाओ err_param;
		पूर्ण
		अगर (param_tb[DCB_TC_ATTR_PARAM_BW_PCT] ||
		    param_tb[DCB_TC_ATTR_PARAM_ALL]) अणु
			ret = nla_put_u8(skb, DCB_TC_ATTR_PARAM_BW_PCT,
			                 tc_pct);
			अगर (ret)
				जाओ err_param;
		पूर्ण
		nla_nest_end(skb, param_nest);
	पूर्ण

	अगर (pg_tb[DCB_PG_ATTR_BW_ID_ALL])
		getall = 1;
	अन्यथा
		getall = 0;

	क्रम (i = DCB_PG_ATTR_BW_ID_0; i <= DCB_PG_ATTR_BW_ID_7; i++) अणु
		अगर (!getall && !pg_tb[i])
			जारी;

		tc_pct = DCB_ATTR_VALUE_UNDEFINED;

		अगर (dir) अणु
			/* Rx */
			netdev->dcbnl_ops->getpgbwgcfgrx(netdev,
					i - DCB_PG_ATTR_BW_ID_0, &tc_pct);
		पूर्ण अन्यथा अणु
			/* Tx */
			netdev->dcbnl_ops->getpgbwgcfgtx(netdev,
					i - DCB_PG_ATTR_BW_ID_0, &tc_pct);
		पूर्ण
		ret = nla_put_u8(skb, i, tc_pct);
		अगर (ret)
			जाओ err_pg;
	पूर्ण

	nla_nest_end(skb, pg_nest);

	वापस 0;

err_param:
	nla_nest_cancel(skb, param_nest);
err_pg:
	nla_nest_cancel(skb, pg_nest);

	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक dcbnl_pgtx_अ_लोfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			     u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	वापस __dcbnl_pg_अ_लोfg(netdev, nlh, tb, skb, 0);
पूर्ण

अटल पूर्णांक dcbnl_pgrx_अ_लोfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			     u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	वापस __dcbnl_pg_अ_लोfg(netdev, nlh, tb, skb, 1);
पूर्ण

अटल पूर्णांक dcbnl_setstate(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			  u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	u8 value;

	अगर (!tb[DCB_ATTR_STATE])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->setstate)
		वापस -EOPNOTSUPP;

	value = nla_get_u8(tb[DCB_ATTR_STATE]);

	वापस nla_put_u8(skb, DCB_ATTR_STATE,
			  netdev->dcbnl_ops->setstate(netdev, value));
पूर्ण

अटल पूर्णांक dcbnl_setpfccfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			   u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *data[DCB_PFC_UP_ATTR_MAX + 1];
	पूर्णांक i;
	पूर्णांक ret;
	u8 value;

	अगर (!tb[DCB_ATTR_PFC_CFG])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->setpfccfg)
		वापस -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(data, DCB_PFC_UP_ATTR_MAX,
					  tb[DCB_ATTR_PFC_CFG],
					  dcbnl_pfc_up_nest, शून्य);
	अगर (ret)
		वापस ret;

	क्रम (i = DCB_PFC_UP_ATTR_0; i <= DCB_PFC_UP_ATTR_7; i++) अणु
		अगर (data[i] == शून्य)
			जारी;
		value = nla_get_u8(data[i]);
		netdev->dcbnl_ops->setpfccfg(netdev,
			data[i]->nla_type - DCB_PFC_UP_ATTR_0, value);
	पूर्ण

	वापस nla_put_u8(skb, DCB_ATTR_PFC_CFG, 0);
पूर्ण

अटल पूर्णांक dcbnl_setall(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	अगर (!tb[DCB_ATTR_SET_ALL])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->setall)
		वापस -EOPNOTSUPP;

	ret = nla_put_u8(skb, DCB_ATTR_SET_ALL,
			 netdev->dcbnl_ops->setall(netdev));
	dcbnl_cee_notअगरy(netdev, RTM_SETDCB, DCB_CMD_SET_ALL, seq, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक __dcbnl_pg_setcfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			     u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb,
			     पूर्णांक dir)
अणु
	काष्ठा nlattr *pg_tb[DCB_PG_ATTR_MAX + 1];
	काष्ठा nlattr *param_tb[DCB_TC_ATTR_PARAM_MAX + 1];
	पूर्णांक ret;
	पूर्णांक i;
	u8 pgid;
	u8 up_map;
	u8 prio;
	u8 tc_pct;

	अगर (!tb[DCB_ATTR_PG_CFG])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->setpgtccfgtx ||
	    !netdev->dcbnl_ops->setpgtccfgrx ||
	    !netdev->dcbnl_ops->setpgbwgcfgtx ||
	    !netdev->dcbnl_ops->setpgbwgcfgrx)
		वापस -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(pg_tb, DCB_PG_ATTR_MAX,
					  tb[DCB_ATTR_PG_CFG], dcbnl_pg_nest,
					  शून्य);
	अगर (ret)
		वापस ret;

	क्रम (i = DCB_PG_ATTR_TC_0; i <= DCB_PG_ATTR_TC_7; i++) अणु
		अगर (!pg_tb[i])
			जारी;

		ret = nla_parse_nested_deprecated(param_tb,
						  DCB_TC_ATTR_PARAM_MAX,
						  pg_tb[i],
						  dcbnl_tc_param_nest, शून्य);
		अगर (ret)
			वापस ret;

		pgid = DCB_ATTR_VALUE_UNDEFINED;
		prio = DCB_ATTR_VALUE_UNDEFINED;
		tc_pct = DCB_ATTR_VALUE_UNDEFINED;
		up_map = DCB_ATTR_VALUE_UNDEFINED;

		अगर (param_tb[DCB_TC_ATTR_PARAM_STRICT_PRIO])
			prio =
			    nla_get_u8(param_tb[DCB_TC_ATTR_PARAM_STRICT_PRIO]);

		अगर (param_tb[DCB_TC_ATTR_PARAM_PGID])
			pgid = nla_get_u8(param_tb[DCB_TC_ATTR_PARAM_PGID]);

		अगर (param_tb[DCB_TC_ATTR_PARAM_BW_PCT])
			tc_pct = nla_get_u8(param_tb[DCB_TC_ATTR_PARAM_BW_PCT]);

		अगर (param_tb[DCB_TC_ATTR_PARAM_UP_MAPPING])
			up_map =
			     nla_get_u8(param_tb[DCB_TC_ATTR_PARAM_UP_MAPPING]);

		/* dir: Tx = 0, Rx = 1 */
		अगर (dir) अणु
			/* Rx */
			netdev->dcbnl_ops->setpgtccfgrx(netdev,
				i - DCB_PG_ATTR_TC_0,
				prio, pgid, tc_pct, up_map);
		पूर्ण अन्यथा अणु
			/* Tx */
			netdev->dcbnl_ops->setpgtccfgtx(netdev,
				i - DCB_PG_ATTR_TC_0,
				prio, pgid, tc_pct, up_map);
		पूर्ण
	पूर्ण

	क्रम (i = DCB_PG_ATTR_BW_ID_0; i <= DCB_PG_ATTR_BW_ID_7; i++) अणु
		अगर (!pg_tb[i])
			जारी;

		tc_pct = nla_get_u8(pg_tb[i]);

		/* dir: Tx = 0, Rx = 1 */
		अगर (dir) अणु
			/* Rx */
			netdev->dcbnl_ops->setpgbwgcfgrx(netdev,
					 i - DCB_PG_ATTR_BW_ID_0, tc_pct);
		पूर्ण अन्यथा अणु
			/* Tx */
			netdev->dcbnl_ops->setpgbwgcfgtx(netdev,
					 i - DCB_PG_ATTR_BW_ID_0, tc_pct);
		पूर्ण
	पूर्ण

	वापस nla_put_u8(skb, DCB_ATTR_PG_CFG, 0);
पूर्ण

अटल पूर्णांक dcbnl_pgtx_setcfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			     u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	वापस __dcbnl_pg_setcfg(netdev, nlh, seq, tb, skb, 0);
पूर्ण

अटल पूर्णांक dcbnl_pgrx_setcfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			     u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	वापस __dcbnl_pg_setcfg(netdev, nlh, seq, tb, skb, 1);
पूर्ण

अटल पूर्णांक dcbnl_bcn_अ_लोfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			    u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *bcn_nest;
	काष्ठा nlattr *bcn_tb[DCB_BCN_ATTR_MAX + 1];
	u8 value_byte;
	u32 value_पूर्णांकeger;
	पूर्णांक ret;
	bool getall = false;
	पूर्णांक i;

	अगर (!tb[DCB_ATTR_BCN])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->getbcnrp ||
	    !netdev->dcbnl_ops->getbcncfg)
		वापस -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(bcn_tb, DCB_BCN_ATTR_MAX,
					  tb[DCB_ATTR_BCN], dcbnl_bcn_nest,
					  शून्य);
	अगर (ret)
		वापस ret;

	bcn_nest = nla_nest_start_noflag(skb, DCB_ATTR_BCN);
	अगर (!bcn_nest)
		वापस -EMSGSIZE;

	अगर (bcn_tb[DCB_BCN_ATTR_ALL])
		getall = true;

	क्रम (i = DCB_BCN_ATTR_RP_0; i <= DCB_BCN_ATTR_RP_7; i++) अणु
		अगर (!getall && !bcn_tb[i])
			जारी;

		netdev->dcbnl_ops->getbcnrp(netdev, i - DCB_BCN_ATTR_RP_0,
		                            &value_byte);
		ret = nla_put_u8(skb, i, value_byte);
		अगर (ret)
			जाओ err_bcn;
	पूर्ण

	क्रम (i = DCB_BCN_ATTR_BCNA_0; i <= DCB_BCN_ATTR_RI; i++) अणु
		अगर (!getall && !bcn_tb[i])
			जारी;

		netdev->dcbnl_ops->getbcncfg(netdev, i,
		                             &value_पूर्णांकeger);
		ret = nla_put_u32(skb, i, value_पूर्णांकeger);
		अगर (ret)
			जाओ err_bcn;
	पूर्ण

	nla_nest_end(skb, bcn_nest);

	वापस 0;

err_bcn:
	nla_nest_cancel(skb, bcn_nest);
	वापस ret;
पूर्ण

अटल पूर्णांक dcbnl_bcn_setcfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			    u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *data[DCB_BCN_ATTR_MAX + 1];
	पूर्णांक i;
	पूर्णांक ret;
	u8 value_byte;
	u32 value_पूर्णांक;

	अगर (!tb[DCB_ATTR_BCN])
		वापस -EINVAL;

	अगर (!netdev->dcbnl_ops->setbcncfg ||
	    !netdev->dcbnl_ops->setbcnrp)
		वापस -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(data, DCB_BCN_ATTR_MAX,
					  tb[DCB_ATTR_BCN], dcbnl_pfc_up_nest,
					  शून्य);
	अगर (ret)
		वापस ret;

	क्रम (i = DCB_BCN_ATTR_RP_0; i <= DCB_BCN_ATTR_RP_7; i++) अणु
		अगर (data[i] == शून्य)
			जारी;
		value_byte = nla_get_u8(data[i]);
		netdev->dcbnl_ops->setbcnrp(netdev,
			data[i]->nla_type - DCB_BCN_ATTR_RP_0, value_byte);
	पूर्ण

	क्रम (i = DCB_BCN_ATTR_BCNA_0; i <= DCB_BCN_ATTR_RI; i++) अणु
		अगर (data[i] == शून्य)
			जारी;
		value_पूर्णांक = nla_get_u32(data[i]);
		netdev->dcbnl_ops->setbcncfg(netdev,
	                                     i, value_पूर्णांक);
	पूर्ण

	वापस nla_put_u8(skb, DCB_ATTR_BCN, 0);
पूर्ण

अटल पूर्णांक dcbnl_build_peer_app(काष्ठा net_device *netdev, काष्ठा sk_buff* skb,
				पूर्णांक app_nested_type, पूर्णांक app_info_type,
				पूर्णांक app_entry_type)
अणु
	काष्ठा dcb_peer_app_info info;
	काष्ठा dcb_app *table = शून्य;
	स्थिर काष्ठा dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;
	u16 app_count;
	पूर्णांक err;


	/**
	 * retrieve the peer app configuration क्रमm the driver. If the driver
	 * handlers fail निकास without करोing anything
	 */
	err = ops->peer_getappinfo(netdev, &info, &app_count);
	अगर (!err && app_count) अणु
		table = kदो_स्मृति_array(app_count, माप(काष्ठा dcb_app),
				      GFP_KERNEL);
		अगर (!table)
			वापस -ENOMEM;

		err = ops->peer_getapptable(netdev, table);
	पूर्ण

	अगर (!err) अणु
		u16 i;
		काष्ठा nlattr *app;

		/**
		 * build the message, from here on the only possible failure
		 * is due to the skb size
		 */
		err = -EMSGSIZE;

		app = nla_nest_start_noflag(skb, app_nested_type);
		अगर (!app)
			जाओ nla_put_failure;

		अगर (app_info_type &&
		    nla_put(skb, app_info_type, माप(info), &info))
			जाओ nla_put_failure;

		क्रम (i = 0; i < app_count; i++) अणु
			अगर (nla_put(skb, app_entry_type, माप(काष्ठा dcb_app),
				    &table[i]))
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, app);
	पूर्ण
	err = 0;

nla_put_failure:
	kमुक्त(table);
	वापस err;
पूर्ण

/* Handle IEEE 802.1Qaz/802.1Qau/802.1Qbb GET commands. */
अटल पूर्णांक dcbnl_ieee_fill(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा nlattr *ieee, *app;
	काष्ठा dcb_app_type *itr;
	स्थिर काष्ठा dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;
	पूर्णांक dcbx;
	पूर्णांक err;

	अगर (nla_put_string(skb, DCB_ATTR_IFNAME, netdev->name))
		वापस -EMSGSIZE;

	ieee = nla_nest_start_noflag(skb, DCB_ATTR_IEEE);
	अगर (!ieee)
		वापस -EMSGSIZE;

	अगर (ops->ieee_getets) अणु
		काष्ठा ieee_ets ets;
		स_रखो(&ets, 0, माप(ets));
		err = ops->ieee_getets(netdev, &ets);
		अगर (!err &&
		    nla_put(skb, DCB_ATTR_IEEE_ETS, माप(ets), &ets))
			वापस -EMSGSIZE;
	पूर्ण

	अगर (ops->ieee_geपंचांगaxrate) अणु
		काष्ठा ieee_maxrate maxrate;
		स_रखो(&maxrate, 0, माप(maxrate));
		err = ops->ieee_geपंचांगaxrate(netdev, &maxrate);
		अगर (!err) अणु
			err = nla_put(skb, DCB_ATTR_IEEE_MAXRATE,
				      माप(maxrate), &maxrate);
			अगर (err)
				वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

	अगर (ops->ieee_getqcn) अणु
		काष्ठा ieee_qcn qcn;

		स_रखो(&qcn, 0, माप(qcn));
		err = ops->ieee_getqcn(netdev, &qcn);
		अगर (!err) अणु
			err = nla_put(skb, DCB_ATTR_IEEE_QCN,
				      माप(qcn), &qcn);
			अगर (err)
				वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

	अगर (ops->ieee_getqcnstats) अणु
		काष्ठा ieee_qcn_stats qcn_stats;

		स_रखो(&qcn_stats, 0, माप(qcn_stats));
		err = ops->ieee_getqcnstats(netdev, &qcn_stats);
		अगर (!err) अणु
			err = nla_put(skb, DCB_ATTR_IEEE_QCN_STATS,
				      माप(qcn_stats), &qcn_stats);
			अगर (err)
				वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

	अगर (ops->ieee_getpfc) अणु
		काष्ठा ieee_pfc pfc;
		स_रखो(&pfc, 0, माप(pfc));
		err = ops->ieee_getpfc(netdev, &pfc);
		अगर (!err &&
		    nla_put(skb, DCB_ATTR_IEEE_PFC, माप(pfc), &pfc))
			वापस -EMSGSIZE;
	पूर्ण

	अगर (ops->dcbnl_getbuffer) अणु
		काष्ठा dcbnl_buffer buffer;

		स_रखो(&buffer, 0, माप(buffer));
		err = ops->dcbnl_getbuffer(netdev, &buffer);
		अगर (!err &&
		    nla_put(skb, DCB_ATTR_DCB_BUFFER, माप(buffer), &buffer))
			वापस -EMSGSIZE;
	पूर्ण

	app = nla_nest_start_noflag(skb, DCB_ATTR_IEEE_APP_TABLE);
	अगर (!app)
		वापस -EMSGSIZE;

	spin_lock_bh(&dcb_lock);
	list_क्रम_each_entry(itr, &dcb_app_list, list) अणु
		अगर (itr->अगरindex == netdev->अगरindex) अणु
			err = nla_put(skb, DCB_ATTR_IEEE_APP, माप(itr->app),
					 &itr->app);
			अगर (err) अणु
				spin_unlock_bh(&dcb_lock);
				वापस -EMSGSIZE;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (netdev->dcbnl_ops->getdcbx)
		dcbx = netdev->dcbnl_ops->getdcbx(netdev);
	अन्यथा
		dcbx = -EOPNOTSUPP;

	spin_unlock_bh(&dcb_lock);
	nla_nest_end(skb, app);

	/* get peer info अगर available */
	अगर (ops->ieee_peer_getets) अणु
		काष्ठा ieee_ets ets;
		स_रखो(&ets, 0, माप(ets));
		err = ops->ieee_peer_getets(netdev, &ets);
		अगर (!err &&
		    nla_put(skb, DCB_ATTR_IEEE_PEER_ETS, माप(ets), &ets))
			वापस -EMSGSIZE;
	पूर्ण

	अगर (ops->ieee_peer_getpfc) अणु
		काष्ठा ieee_pfc pfc;
		स_रखो(&pfc, 0, माप(pfc));
		err = ops->ieee_peer_getpfc(netdev, &pfc);
		अगर (!err &&
		    nla_put(skb, DCB_ATTR_IEEE_PEER_PFC, माप(pfc), &pfc))
			वापस -EMSGSIZE;
	पूर्ण

	अगर (ops->peer_getappinfo && ops->peer_getapptable) अणु
		err = dcbnl_build_peer_app(netdev, skb,
					   DCB_ATTR_IEEE_PEER_APP,
					   DCB_ATTR_IEEE_APP_UNSPEC,
					   DCB_ATTR_IEEE_APP);
		अगर (err)
			वापस -EMSGSIZE;
	पूर्ण

	nla_nest_end(skb, ieee);
	अगर (dcbx >= 0) अणु
		err = nla_put_u8(skb, DCB_ATTR_DCBX, dcbx);
		अगर (err)
			वापस -EMSGSIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dcbnl_cee_pg_fill(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			     पूर्णांक dir)
अणु
	u8 pgid, up_map, prio, tc_pct;
	स्थिर काष्ठा dcbnl_rtnl_ops *ops = dev->dcbnl_ops;
	पूर्णांक i = dir ? DCB_ATTR_CEE_TX_PG : DCB_ATTR_CEE_RX_PG;
	काष्ठा nlattr *pg = nla_nest_start_noflag(skb, i);

	अगर (!pg)
		वापस -EMSGSIZE;

	क्रम (i = DCB_PG_ATTR_TC_0; i <= DCB_PG_ATTR_TC_7; i++) अणु
		काष्ठा nlattr *tc_nest = nla_nest_start_noflag(skb, i);

		अगर (!tc_nest)
			वापस -EMSGSIZE;

		pgid = DCB_ATTR_VALUE_UNDEFINED;
		prio = DCB_ATTR_VALUE_UNDEFINED;
		tc_pct = DCB_ATTR_VALUE_UNDEFINED;
		up_map = DCB_ATTR_VALUE_UNDEFINED;

		अगर (!dir)
			ops->getpgtccfgrx(dev, i - DCB_PG_ATTR_TC_0,
					  &prio, &pgid, &tc_pct, &up_map);
		अन्यथा
			ops->getpgtccfgtx(dev, i - DCB_PG_ATTR_TC_0,
					  &prio, &pgid, &tc_pct, &up_map);

		अगर (nla_put_u8(skb, DCB_TC_ATTR_PARAM_PGID, pgid) ||
		    nla_put_u8(skb, DCB_TC_ATTR_PARAM_UP_MAPPING, up_map) ||
		    nla_put_u8(skb, DCB_TC_ATTR_PARAM_STRICT_PRIO, prio) ||
		    nla_put_u8(skb, DCB_TC_ATTR_PARAM_BW_PCT, tc_pct))
			वापस -EMSGSIZE;
		nla_nest_end(skb, tc_nest);
	पूर्ण

	क्रम (i = DCB_PG_ATTR_BW_ID_0; i <= DCB_PG_ATTR_BW_ID_7; i++) अणु
		tc_pct = DCB_ATTR_VALUE_UNDEFINED;

		अगर (!dir)
			ops->getpgbwgcfgrx(dev, i - DCB_PG_ATTR_BW_ID_0,
					   &tc_pct);
		अन्यथा
			ops->getpgbwgcfgtx(dev, i - DCB_PG_ATTR_BW_ID_0,
					   &tc_pct);
		अगर (nla_put_u8(skb, i, tc_pct))
			वापस -EMSGSIZE;
	पूर्ण
	nla_nest_end(skb, pg);
	वापस 0;
पूर्ण

अटल पूर्णांक dcbnl_cee_fill(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा nlattr *cee, *app;
	काष्ठा dcb_app_type *itr;
	स्थिर काष्ठा dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;
	पूर्णांक dcbx, i, err = -EMSGSIZE;
	u8 value;

	अगर (nla_put_string(skb, DCB_ATTR_IFNAME, netdev->name))
		जाओ nla_put_failure;
	cee = nla_nest_start_noflag(skb, DCB_ATTR_CEE);
	अगर (!cee)
		जाओ nla_put_failure;

	/* local pg */
	अगर (ops->getpgtccfgtx && ops->getpgbwgcfgtx) अणु
		err = dcbnl_cee_pg_fill(skb, netdev, 1);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	अगर (ops->getpgtccfgrx && ops->getpgbwgcfgrx) अणु
		err = dcbnl_cee_pg_fill(skb, netdev, 0);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण

	/* local pfc */
	अगर (ops->getpfccfg) अणु
		काष्ठा nlattr *pfc_nest = nla_nest_start_noflag(skb,
								DCB_ATTR_CEE_PFC);

		अगर (!pfc_nest)
			जाओ nla_put_failure;

		क्रम (i = DCB_PFC_UP_ATTR_0; i <= DCB_PFC_UP_ATTR_7; i++) अणु
			ops->getpfccfg(netdev, i - DCB_PFC_UP_ATTR_0, &value);
			अगर (nla_put_u8(skb, i, value))
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, pfc_nest);
	पूर्ण

	/* local app */
	spin_lock_bh(&dcb_lock);
	app = nla_nest_start_noflag(skb, DCB_ATTR_CEE_APP_TABLE);
	अगर (!app)
		जाओ dcb_unlock;

	list_क्रम_each_entry(itr, &dcb_app_list, list) अणु
		अगर (itr->अगरindex == netdev->अगरindex) अणु
			काष्ठा nlattr *app_nest = nla_nest_start_noflag(skb,
									DCB_ATTR_APP);
			अगर (!app_nest)
				जाओ dcb_unlock;

			err = nla_put_u8(skb, DCB_APP_ATTR_IDTYPE,
					 itr->app.selector);
			अगर (err)
				जाओ dcb_unlock;

			err = nla_put_u16(skb, DCB_APP_ATTR_ID,
					  itr->app.protocol);
			अगर (err)
				जाओ dcb_unlock;

			err = nla_put_u8(skb, DCB_APP_ATTR_PRIORITY,
					 itr->app.priority);
			अगर (err)
				जाओ dcb_unlock;

			nla_nest_end(skb, app_nest);
		पूर्ण
	पूर्ण
	nla_nest_end(skb, app);

	अगर (netdev->dcbnl_ops->getdcbx)
		dcbx = netdev->dcbnl_ops->getdcbx(netdev);
	अन्यथा
		dcbx = -EOPNOTSUPP;

	spin_unlock_bh(&dcb_lock);

	/* features flags */
	अगर (ops->getfeatcfg) अणु
		काष्ठा nlattr *feat = nla_nest_start_noflag(skb,
							    DCB_ATTR_CEE_FEAT);
		अगर (!feat)
			जाओ nla_put_failure;

		क्रम (i = DCB_FEATCFG_ATTR_ALL + 1; i <= DCB_FEATCFG_ATTR_MAX;
		     i++)
			अगर (!ops->getfeatcfg(netdev, i, &value) &&
			    nla_put_u8(skb, i, value))
				जाओ nla_put_failure;

		nla_nest_end(skb, feat);
	पूर्ण

	/* peer info अगर available */
	अगर (ops->cee_peer_getpg) अणु
		काष्ठा cee_pg pg;
		स_रखो(&pg, 0, माप(pg));
		err = ops->cee_peer_getpg(netdev, &pg);
		अगर (!err &&
		    nla_put(skb, DCB_ATTR_CEE_PEER_PG, माप(pg), &pg))
			जाओ nla_put_failure;
	पूर्ण

	अगर (ops->cee_peer_getpfc) अणु
		काष्ठा cee_pfc pfc;
		स_रखो(&pfc, 0, माप(pfc));
		err = ops->cee_peer_getpfc(netdev, &pfc);
		अगर (!err &&
		    nla_put(skb, DCB_ATTR_CEE_PEER_PFC, माप(pfc), &pfc))
			जाओ nla_put_failure;
	पूर्ण

	अगर (ops->peer_getappinfo && ops->peer_getapptable) अणु
		err = dcbnl_build_peer_app(netdev, skb,
					   DCB_ATTR_CEE_PEER_APP_TABLE,
					   DCB_ATTR_CEE_PEER_APP_INFO,
					   DCB_ATTR_CEE_PEER_APP);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, cee);

	/* DCBX state */
	अगर (dcbx >= 0) अणु
		err = nla_put_u8(skb, DCB_ATTR_DCBX, dcbx);
		अगर (err)
			जाओ nla_put_failure;
	पूर्ण
	वापस 0;

dcb_unlock:
	spin_unlock_bh(&dcb_lock);
nla_put_failure:
	err = -EMSGSIZE;
	वापस err;
पूर्ण

अटल पूर्णांक dcbnl_notअगरy(काष्ठा net_device *dev, पूर्णांक event, पूर्णांक cmd,
			u32 seq, u32 portid, पूर्णांक dcbx_ver)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा sk_buff *skb;
	काष्ठा nlmsghdr *nlh;
	स्थिर काष्ठा dcbnl_rtnl_ops *ops = dev->dcbnl_ops;
	पूर्णांक err;

	अगर (!ops)
		वापस -EOPNOTSUPP;

	skb = dcbnl_newmsg(event, cmd, portid, seq, 0, &nlh);
	अगर (!skb)
		वापस -ENOBUFS;

	अगर (dcbx_ver == DCB_CAP_DCBX_VER_IEEE)
		err = dcbnl_ieee_fill(skb, dev);
	अन्यथा
		err = dcbnl_cee_fill(skb, dev);

	अगर (err < 0) अणु
		/* Report error to broadcast listeners */
		nlmsg_मुक्त(skb);
		rtnl_set_sk_err(net, RTNLGRP_DCB, err);
	पूर्ण अन्यथा अणु
		/* End nlmsg and notअगरy broadcast listeners */
		nlmsg_end(skb, nlh);
		rtnl_notअगरy(skb, net, 0, RTNLGRP_DCB, शून्य, GFP_KERNEL);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक dcbnl_ieee_notअगरy(काष्ठा net_device *dev, पूर्णांक event, पूर्णांक cmd,
		      u32 seq, u32 portid)
अणु
	वापस dcbnl_notअगरy(dev, event, cmd, seq, portid, DCB_CAP_DCBX_VER_IEEE);
पूर्ण
EXPORT_SYMBOL(dcbnl_ieee_notअगरy);

पूर्णांक dcbnl_cee_notअगरy(काष्ठा net_device *dev, पूर्णांक event, पूर्णांक cmd,
		     u32 seq, u32 portid)
अणु
	वापस dcbnl_notअगरy(dev, event, cmd, seq, portid, DCB_CAP_DCBX_VER_CEE);
पूर्ण
EXPORT_SYMBOL(dcbnl_cee_notअगरy);

/* Handle IEEE 802.1Qaz/802.1Qau/802.1Qbb SET commands.
 * If any requested operation can not be completed
 * the entire msg is पातed and error value is वापसed.
 * No attempt is made to reconcile the हाल where only part of the
 * cmd can be completed.
 */
अटल पूर्णांक dcbnl_ieee_set(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			  u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;
	काष्ठा nlattr *ieee[DCB_ATTR_IEEE_MAX + 1];
	पूर्णांक prio;
	पूर्णांक err;

	अगर (!ops)
		वापस -EOPNOTSUPP;

	अगर (!tb[DCB_ATTR_IEEE])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(ieee, DCB_ATTR_IEEE_MAX,
					  tb[DCB_ATTR_IEEE],
					  dcbnl_ieee_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (ieee[DCB_ATTR_IEEE_ETS] && ops->ieee_setets) अणु
		काष्ठा ieee_ets *ets = nla_data(ieee[DCB_ATTR_IEEE_ETS]);
		err = ops->ieee_setets(netdev, ets);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (ieee[DCB_ATTR_IEEE_MAXRATE] && ops->ieee_seपंचांगaxrate) अणु
		काष्ठा ieee_maxrate *maxrate =
			nla_data(ieee[DCB_ATTR_IEEE_MAXRATE]);
		err = ops->ieee_seपंचांगaxrate(netdev, maxrate);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (ieee[DCB_ATTR_IEEE_QCN] && ops->ieee_setqcn) अणु
		काष्ठा ieee_qcn *qcn =
			nla_data(ieee[DCB_ATTR_IEEE_QCN]);

		err = ops->ieee_setqcn(netdev, qcn);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (ieee[DCB_ATTR_IEEE_PFC] && ops->ieee_setpfc) अणु
		काष्ठा ieee_pfc *pfc = nla_data(ieee[DCB_ATTR_IEEE_PFC]);
		err = ops->ieee_setpfc(netdev, pfc);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (ieee[DCB_ATTR_DCB_BUFFER] && ops->dcbnl_रखो_बफfer) अणु
		काष्ठा dcbnl_buffer *buffer =
			nla_data(ieee[DCB_ATTR_DCB_BUFFER]);

		क्रम (prio = 0; prio < ARRAY_SIZE(buffer->prio2buffer); prio++) अणु
			अगर (buffer->prio2buffer[prio] >= DCBX_MAX_BUFFERS) अणु
				err = -EINVAL;
				जाओ err;
			पूर्ण
		पूर्ण

		err = ops->dcbnl_रखो_बफfer(netdev, buffer);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (ieee[DCB_ATTR_IEEE_APP_TABLE]) अणु
		काष्ठा nlattr *attr;
		पूर्णांक rem;

		nla_क्रम_each_nested(attr, ieee[DCB_ATTR_IEEE_APP_TABLE], rem) अणु
			काष्ठा dcb_app *app_data;

			अगर (nla_type(attr) != DCB_ATTR_IEEE_APP)
				जारी;

			अगर (nla_len(attr) < माप(काष्ठा dcb_app)) अणु
				err = -दुस्फल;
				जाओ err;
			पूर्ण

			app_data = nla_data(attr);
			अगर (ops->ieee_setapp)
				err = ops->ieee_setapp(netdev, app_data);
			अन्यथा
				err = dcb_ieee_setapp(netdev, app_data);
			अगर (err)
				जाओ err;
		पूर्ण
	पूर्ण

err:
	err = nla_put_u8(skb, DCB_ATTR_IEEE, err);
	dcbnl_ieee_notअगरy(netdev, RTM_SETDCB, DCB_CMD_IEEE_SET, seq, 0);
	वापस err;
पूर्ण

अटल पूर्णांक dcbnl_ieee_get(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			  u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;

	अगर (!ops)
		वापस -EOPNOTSUPP;

	वापस dcbnl_ieee_fill(skb, netdev);
पूर्ण

अटल पूर्णांक dcbnl_ieee_del(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			  u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;
	काष्ठा nlattr *ieee[DCB_ATTR_IEEE_MAX + 1];
	पूर्णांक err;

	अगर (!ops)
		वापस -EOPNOTSUPP;

	अगर (!tb[DCB_ATTR_IEEE])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(ieee, DCB_ATTR_IEEE_MAX,
					  tb[DCB_ATTR_IEEE],
					  dcbnl_ieee_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (ieee[DCB_ATTR_IEEE_APP_TABLE]) अणु
		काष्ठा nlattr *attr;
		पूर्णांक rem;

		nla_क्रम_each_nested(attr, ieee[DCB_ATTR_IEEE_APP_TABLE], rem) अणु
			काष्ठा dcb_app *app_data;

			अगर (nla_type(attr) != DCB_ATTR_IEEE_APP)
				जारी;
			app_data = nla_data(attr);
			अगर (ops->ieee_delapp)
				err = ops->ieee_delapp(netdev, app_data);
			अन्यथा
				err = dcb_ieee_delapp(netdev, app_data);
			अगर (err)
				जाओ err;
		पूर्ण
	पूर्ण

err:
	err = nla_put_u8(skb, DCB_ATTR_IEEE, err);
	dcbnl_ieee_notअगरy(netdev, RTM_SETDCB, DCB_CMD_IEEE_DEL, seq, 0);
	वापस err;
पूर्ण


/* DCBX configuration */
अटल पूर्णांक dcbnl_getdcbx(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			 u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	अगर (!netdev->dcbnl_ops->getdcbx)
		वापस -EOPNOTSUPP;

	वापस nla_put_u8(skb, DCB_ATTR_DCBX,
			  netdev->dcbnl_ops->getdcbx(netdev));
पूर्ण

अटल पूर्णांक dcbnl_setdcbx(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			 u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	u8 value;

	अगर (!netdev->dcbnl_ops->setdcbx)
		वापस -EOPNOTSUPP;

	अगर (!tb[DCB_ATTR_DCBX])
		वापस -EINVAL;

	value = nla_get_u8(tb[DCB_ATTR_DCBX]);

	वापस nla_put_u8(skb, DCB_ATTR_DCBX,
			  netdev->dcbnl_ops->setdcbx(netdev, value));
पूर्ण

अटल पूर्णांक dcbnl_getfeatcfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			    u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *data[DCB_FEATCFG_ATTR_MAX + 1], *nest;
	u8 value;
	पूर्णांक ret, i;
	पूर्णांक getall = 0;

	अगर (!netdev->dcbnl_ops->getfeatcfg)
		वापस -EOPNOTSUPP;

	अगर (!tb[DCB_ATTR_FEATCFG])
		वापस -EINVAL;

	ret = nla_parse_nested_deprecated(data, DCB_FEATCFG_ATTR_MAX,
					  tb[DCB_ATTR_FEATCFG],
					  dcbnl_featcfg_nest, शून्य);
	अगर (ret)
		वापस ret;

	nest = nla_nest_start_noflag(skb, DCB_ATTR_FEATCFG);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (data[DCB_FEATCFG_ATTR_ALL])
		getall = 1;

	क्रम (i = DCB_FEATCFG_ATTR_ALL+1; i <= DCB_FEATCFG_ATTR_MAX; i++) अणु
		अगर (!getall && !data[i])
			जारी;

		ret = netdev->dcbnl_ops->getfeatcfg(netdev, i, &value);
		अगर (!ret)
			ret = nla_put_u8(skb, i, value);

		अगर (ret) अणु
			nla_nest_cancel(skb, nest);
			जाओ nla_put_failure;
		पूर्ण
	पूर्ण
	nla_nest_end(skb, nest);

nla_put_failure:
	वापस ret;
पूर्ण

अटल पूर्णांक dcbnl_setfeatcfg(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			    u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *data[DCB_FEATCFG_ATTR_MAX + 1];
	पूर्णांक ret, i;
	u8 value;

	अगर (!netdev->dcbnl_ops->setfeatcfg)
		वापस -ENOTSUPP;

	अगर (!tb[DCB_ATTR_FEATCFG])
		वापस -EINVAL;

	ret = nla_parse_nested_deprecated(data, DCB_FEATCFG_ATTR_MAX,
					  tb[DCB_ATTR_FEATCFG],
					  dcbnl_featcfg_nest, शून्य);

	अगर (ret)
		जाओ err;

	क्रम (i = DCB_FEATCFG_ATTR_ALL+1; i <= DCB_FEATCFG_ATTR_MAX; i++) अणु
		अगर (data[i] == शून्य)
			जारी;

		value = nla_get_u8(data[i]);

		ret = netdev->dcbnl_ops->setfeatcfg(netdev, i, value);

		अगर (ret)
			जाओ err;
	पूर्ण
err:
	ret = nla_put_u8(skb, DCB_ATTR_FEATCFG, ret);

	वापस ret;
पूर्ण

/* Handle CEE DCBX GET commands. */
अटल पूर्णांक dcbnl_cee_get(काष्ठा net_device *netdev, काष्ठा nlmsghdr *nlh,
			 u32 seq, काष्ठा nlattr **tb, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;

	अगर (!ops)
		वापस -EOPNOTSUPP;

	वापस dcbnl_cee_fill(skb, netdev);
पूर्ण

काष्ठा reply_func अणु
	/* reply netlink message type */
	पूर्णांक	type;

	/* function to fill message contents */
	पूर्णांक   (*cb)(काष्ठा net_device *, काष्ठा nlmsghdr *, u32,
		    काष्ठा nlattr **, काष्ठा sk_buff *);
पूर्ण;

अटल स्थिर काष्ठा reply_func reply_funcs[DCB_CMD_MAX+1] = अणु
	[DCB_CMD_GSTATE]	= अणु RTM_GETDCB, dcbnl_माला_लोtate पूर्ण,
	[DCB_CMD_SSTATE]	= अणु RTM_SETDCB, dcbnl_setstate पूर्ण,
	[DCB_CMD_PFC_GCFG]	= अणु RTM_GETDCB, dcbnl_getpfccfg पूर्ण,
	[DCB_CMD_PFC_SCFG]	= अणु RTM_SETDCB, dcbnl_setpfccfg पूर्ण,
	[DCB_CMD_GPERM_HWADDR]	= अणु RTM_GETDCB, dcbnl_getperm_hwaddr पूर्ण,
	[DCB_CMD_GCAP]		= अणु RTM_GETDCB, dcbnl_अ_लोap पूर्ण,
	[DCB_CMD_GNUMTCS]	= अणु RTM_GETDCB, dcbnl_getnumtcs पूर्ण,
	[DCB_CMD_SNUMTCS]	= अणु RTM_SETDCB, dcbnl_setnumtcs पूर्ण,
	[DCB_CMD_PFC_GSTATE]	= अणु RTM_GETDCB, dcbnl_getpfcstate पूर्ण,
	[DCB_CMD_PFC_SSTATE]	= अणु RTM_SETDCB, dcbnl_setpfcstate पूर्ण,
	[DCB_CMD_GAPP]		= अणु RTM_GETDCB, dcbnl_getapp पूर्ण,
	[DCB_CMD_SAPP]		= अणु RTM_SETDCB, dcbnl_setapp पूर्ण,
	[DCB_CMD_PGTX_GCFG]	= अणु RTM_GETDCB, dcbnl_pgtx_अ_लोfg पूर्ण,
	[DCB_CMD_PGTX_SCFG]	= अणु RTM_SETDCB, dcbnl_pgtx_setcfg पूर्ण,
	[DCB_CMD_PGRX_GCFG]	= अणु RTM_GETDCB, dcbnl_pgrx_अ_लोfg पूर्ण,
	[DCB_CMD_PGRX_SCFG]	= अणु RTM_SETDCB, dcbnl_pgrx_setcfg पूर्ण,
	[DCB_CMD_SET_ALL]	= अणु RTM_SETDCB, dcbnl_setall पूर्ण,
	[DCB_CMD_BCN_GCFG]	= अणु RTM_GETDCB, dcbnl_bcn_अ_लोfg पूर्ण,
	[DCB_CMD_BCN_SCFG]	= अणु RTM_SETDCB, dcbnl_bcn_setcfg पूर्ण,
	[DCB_CMD_IEEE_GET]	= अणु RTM_GETDCB, dcbnl_ieee_get पूर्ण,
	[DCB_CMD_IEEE_SET]	= अणु RTM_SETDCB, dcbnl_ieee_set पूर्ण,
	[DCB_CMD_IEEE_DEL]	= अणु RTM_SETDCB, dcbnl_ieee_del पूर्ण,
	[DCB_CMD_GDCBX]		= अणु RTM_GETDCB, dcbnl_getdcbx पूर्ण,
	[DCB_CMD_SDCBX]		= अणु RTM_SETDCB, dcbnl_setdcbx पूर्ण,
	[DCB_CMD_GFEATCFG]	= अणु RTM_GETDCB, dcbnl_getfeatcfg पूर्ण,
	[DCB_CMD_SFEATCFG]	= अणु RTM_SETDCB, dcbnl_setfeatcfg पूर्ण,
	[DCB_CMD_CEE_GET]	= अणु RTM_GETDCB, dcbnl_cee_get पूर्ण,
पूर्ण;

अटल पूर्णांक dcb_करोit(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net_device *netdev;
	काष्ठा dcbmsg *dcb = nlmsg_data(nlh);
	काष्ठा nlattr *tb[DCB_ATTR_MAX + 1];
	u32 portid = NETLINK_CB(skb).portid;
	पूर्णांक ret = -EINVAL;
	काष्ठा sk_buff *reply_skb;
	काष्ठा nlmsghdr *reply_nlh = शून्य;
	स्थिर काष्ठा reply_func *fn;

	अगर ((nlh->nlmsg_type == RTM_SETDCB) && !netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	ret = nlmsg_parse_deprecated(nlh, माप(*dcb), tb, DCB_ATTR_MAX,
				     dcbnl_rtnl_policy, extack);
	अगर (ret < 0)
		वापस ret;

	अगर (dcb->cmd > DCB_CMD_MAX)
		वापस -EINVAL;

	/* check अगर a reply function has been defined क्रम the command */
	fn = &reply_funcs[dcb->cmd];
	अगर (!fn->cb)
		वापस -EOPNOTSUPP;
	अगर (fn->type == RTM_SETDCB && !netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!tb[DCB_ATTR_IFNAME])
		वापस -EINVAL;

	netdev = __dev_get_by_name(net, nla_data(tb[DCB_ATTR_IFNAME]));
	अगर (!netdev)
		वापस -ENODEV;

	अगर (!netdev->dcbnl_ops)
		वापस -EOPNOTSUPP;

	reply_skb = dcbnl_newmsg(fn->type, dcb->cmd, portid, nlh->nlmsg_seq,
				 nlh->nlmsg_flags, &reply_nlh);
	अगर (!reply_skb)
		वापस -ENOBUFS;

	ret = fn->cb(netdev, nlh, nlh->nlmsg_seq, tb, reply_skb);
	अगर (ret < 0) अणु
		nlmsg_मुक्त(reply_skb);
		जाओ out;
	पूर्ण

	nlmsg_end(reply_skb, reply_nlh);

	ret = rtnl_unicast(reply_skb, net, portid);
out:
	वापस ret;
पूर्ण

अटल काष्ठा dcb_app_type *dcb_app_lookup(स्थिर काष्ठा dcb_app *app,
					   पूर्णांक अगरindex, पूर्णांक prio)
अणु
	काष्ठा dcb_app_type *itr;

	list_क्रम_each_entry(itr, &dcb_app_list, list) अणु
		अगर (itr->app.selector == app->selector &&
		    itr->app.protocol == app->protocol &&
		    itr->अगरindex == अगरindex &&
		    ((prio == -1) || itr->app.priority == prio))
			वापस itr;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक dcb_app_add(स्थिर काष्ठा dcb_app *app, पूर्णांक अगरindex)
अणु
	काष्ठा dcb_app_type *entry;

	entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;

	स_नकल(&entry->app, app, माप(*app));
	entry->अगरindex = अगरindex;
	list_add(&entry->list, &dcb_app_list);

	वापस 0;
पूर्ण

/**
 * dcb_getapp - retrieve the DCBX application user priority
 * @dev: network पूर्णांकerface
 * @app: application to get user priority of
 *
 * On success वापसs a non-zero 802.1p user priority biपंचांगap
 * otherwise वापसs 0 as the invalid user priority biपंचांगap to
 * indicate an error.
 */
u8 dcb_getapp(काष्ठा net_device *dev, काष्ठा dcb_app *app)
अणु
	काष्ठा dcb_app_type *itr;
	u8 prio = 0;

	spin_lock_bh(&dcb_lock);
	itr = dcb_app_lookup(app, dev->अगरindex, -1);
	अगर (itr)
		prio = itr->app.priority;
	spin_unlock_bh(&dcb_lock);

	वापस prio;
पूर्ण
EXPORT_SYMBOL(dcb_getapp);

/**
 * dcb_setapp - add CEE dcb application data to app list
 * @dev: network पूर्णांकerface
 * @new: application data to add
 *
 * Priority 0 is an invalid priority in CEE spec. This routine
 * हटाओs applications from the app list अगर the priority is
 * set to zero. Priority is expected to be 8-bit 802.1p user priority biपंचांगap
 */
पूर्णांक dcb_setapp(काष्ठा net_device *dev, काष्ठा dcb_app *new)
अणु
	काष्ठा dcb_app_type *itr;
	काष्ठा dcb_app_type event;
	पूर्णांक err = 0;

	event.अगरindex = dev->अगरindex;
	स_नकल(&event.app, new, माप(event.app));
	अगर (dev->dcbnl_ops->getdcbx)
		event.dcbx = dev->dcbnl_ops->getdcbx(dev);

	spin_lock_bh(&dcb_lock);
	/* Search क्रम existing match and replace */
	itr = dcb_app_lookup(new, dev->अगरindex, -1);
	अगर (itr) अणु
		अगर (new->priority)
			itr->app.priority = new->priority;
		अन्यथा अणु
			list_del(&itr->list);
			kमुक्त(itr);
		पूर्ण
		जाओ out;
	पूर्ण
	/* App type करोes not exist add new application type */
	अगर (new->priority)
		err = dcb_app_add(new, dev->अगरindex);
out:
	spin_unlock_bh(&dcb_lock);
	अगर (!err)
		call_dcbevent_notअगरiers(DCB_APP_EVENT, &event);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dcb_setapp);

/**
 * dcb_ieee_getapp_mask - retrieve the IEEE DCB application priority
 * @dev: network पूर्णांकerface
 * @app: where to store the retrieve application data
 *
 * Helper routine which on success वापसs a non-zero 802.1Qaz user
 * priority biपंचांगap otherwise वापसs 0 to indicate the dcb_app was
 * not found in APP list.
 */
u8 dcb_ieee_getapp_mask(काष्ठा net_device *dev, काष्ठा dcb_app *app)
अणु
	काष्ठा dcb_app_type *itr;
	u8 prio = 0;

	spin_lock_bh(&dcb_lock);
	itr = dcb_app_lookup(app, dev->अगरindex, -1);
	अगर (itr)
		prio |= 1 << itr->app.priority;
	spin_unlock_bh(&dcb_lock);

	वापस prio;
पूर्ण
EXPORT_SYMBOL(dcb_ieee_getapp_mask);

/**
 * dcb_ieee_setapp - add IEEE dcb application data to app list
 * @dev: network पूर्णांकerface
 * @new: application data to add
 *
 * This adds Application data to the list. Multiple application
 * entries may exists क्रम the same selector and protocol as दीर्घ
 * as the priorities are dअगरferent. Priority is expected to be a
 * 3-bit अचिन्हित पूर्णांकeger
 */
पूर्णांक dcb_ieee_setapp(काष्ठा net_device *dev, काष्ठा dcb_app *new)
अणु
	काष्ठा dcb_app_type event;
	पूर्णांक err = 0;

	event.अगरindex = dev->अगरindex;
	स_नकल(&event.app, new, माप(event.app));
	अगर (dev->dcbnl_ops->getdcbx)
		event.dcbx = dev->dcbnl_ops->getdcbx(dev);

	spin_lock_bh(&dcb_lock);
	/* Search क्रम existing match and पात अगर found */
	अगर (dcb_app_lookup(new, dev->अगरindex, new->priority)) अणु
		err = -EEXIST;
		जाओ out;
	पूर्ण

	err = dcb_app_add(new, dev->अगरindex);
out:
	spin_unlock_bh(&dcb_lock);
	अगर (!err)
		call_dcbevent_notअगरiers(DCB_APP_EVENT, &event);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dcb_ieee_setapp);

/**
 * dcb_ieee_delapp - delete IEEE dcb application data from list
 * @dev: network पूर्णांकerface
 * @del: application data to delete
 *
 * This हटाओs a matching APP data from the APP list
 */
पूर्णांक dcb_ieee_delapp(काष्ठा net_device *dev, काष्ठा dcb_app *del)
अणु
	काष्ठा dcb_app_type *itr;
	काष्ठा dcb_app_type event;
	पूर्णांक err = -ENOENT;

	event.अगरindex = dev->अगरindex;
	स_नकल(&event.app, del, माप(event.app));
	अगर (dev->dcbnl_ops->getdcbx)
		event.dcbx = dev->dcbnl_ops->getdcbx(dev);

	spin_lock_bh(&dcb_lock);
	/* Search क्रम existing match and हटाओ it. */
	अगर ((itr = dcb_app_lookup(del, dev->अगरindex, del->priority))) अणु
		list_del(&itr->list);
		kमुक्त(itr);
		err = 0;
	पूर्ण

	spin_unlock_bh(&dcb_lock);
	अगर (!err)
		call_dcbevent_notअगरiers(DCB_APP_EVENT, &event);
	वापस err;
पूर्ण
EXPORT_SYMBOL(dcb_ieee_delapp);

/*
 * dcb_ieee_getapp_prio_dscp_mask_map - For a given device, find mapping from
 * priorities to the DSCP values asचिन्हित to that priority. Initialize p_map
 * such that each map element holds a bit mask of DSCP values configured क्रम
 * that priority by APP entries.
 */
व्योम dcb_ieee_getapp_prio_dscp_mask_map(स्थिर काष्ठा net_device *dev,
					काष्ठा dcb_ieee_app_prio_map *p_map)
अणु
	पूर्णांक अगरindex = dev->अगरindex;
	काष्ठा dcb_app_type *itr;
	u8 prio;

	स_रखो(p_map->map, 0, माप(p_map->map));

	spin_lock_bh(&dcb_lock);
	list_क्रम_each_entry(itr, &dcb_app_list, list) अणु
		अगर (itr->अगरindex == अगरindex &&
		    itr->app.selector == IEEE_8021QAZ_APP_SEL_DSCP &&
		    itr->app.protocol < 64 &&
		    itr->app.priority < IEEE_8021QAZ_MAX_TCS) अणु
			prio = itr->app.priority;
			p_map->map[prio] |= 1ULL << itr->app.protocol;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&dcb_lock);
पूर्ण
EXPORT_SYMBOL(dcb_ieee_getapp_prio_dscp_mask_map);

/*
 * dcb_ieee_getapp_dscp_prio_mask_map - For a given device, find mapping from
 * DSCP values to the priorities asचिन्हित to that DSCP value. Initialize p_map
 * such that each map element holds a bit mask of priorities configured क्रम a
 * given DSCP value by APP entries.
 */
व्योम
dcb_ieee_getapp_dscp_prio_mask_map(स्थिर काष्ठा net_device *dev,
				   काष्ठा dcb_ieee_app_dscp_map *p_map)
अणु
	पूर्णांक अगरindex = dev->अगरindex;
	काष्ठा dcb_app_type *itr;

	स_रखो(p_map->map, 0, माप(p_map->map));

	spin_lock_bh(&dcb_lock);
	list_क्रम_each_entry(itr, &dcb_app_list, list) अणु
		अगर (itr->अगरindex == अगरindex &&
		    itr->app.selector == IEEE_8021QAZ_APP_SEL_DSCP &&
		    itr->app.protocol < 64 &&
		    itr->app.priority < IEEE_8021QAZ_MAX_TCS)
			p_map->map[itr->app.protocol] |= 1 << itr->app.priority;
	पूर्ण
	spin_unlock_bh(&dcb_lock);
पूर्ण
EXPORT_SYMBOL(dcb_ieee_getapp_dscp_prio_mask_map);

/*
 * Per 802.1Q-2014, the selector value of 1 is used क्रम matching on Ethernet
 * type, with valid PID values >= 1536. A special meaning is then asचिन्हित to
 * protocol value of 0: "शेष priority. For use when priority is not
 * otherwise specअगरied".
 *
 * dcb_ieee_getapp_शेष_prio_mask - For a given device, find all APP entries
 * of the क्रमm अणु$PRIO, ETHERTYPE, 0पूर्ण and स्थिरruct a bit mask of all शेष
 * priorities set by these entries.
 */
u8 dcb_ieee_getapp_शेष_prio_mask(स्थिर काष्ठा net_device *dev)
अणु
	पूर्णांक अगरindex = dev->अगरindex;
	काष्ठा dcb_app_type *itr;
	u8 mask = 0;

	spin_lock_bh(&dcb_lock);
	list_क्रम_each_entry(itr, &dcb_app_list, list) अणु
		अगर (itr->अगरindex == अगरindex &&
		    itr->app.selector == IEEE_8021QAZ_APP_SEL_ETHERTYPE &&
		    itr->app.protocol == 0 &&
		    itr->app.priority < IEEE_8021QAZ_MAX_TCS)
			mask |= 1 << itr->app.priority;
	पूर्ण
	spin_unlock_bh(&dcb_lock);

	वापस mask;
पूर्ण
EXPORT_SYMBOL(dcb_ieee_getapp_शेष_prio_mask);

अटल पूर्णांक __init dcbnl_init(व्योम)
अणु
	INIT_LIST_HEAD(&dcb_app_list);

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETDCB, dcb_करोit, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_SETDCB, dcb_करोit, शून्य, 0);

	वापस 0;
पूर्ण
device_initcall(dcbnl_init);
