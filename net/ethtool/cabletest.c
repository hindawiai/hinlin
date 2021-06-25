<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/phy.h>
#समावेश <linux/ethtool_netlink.h>
#समावेश "netlink.h"
#समावेश "common.h"

/* 802.3 standard allows 100 meters क्रम BaseT cables. However दीर्घer
 * cables might work, depending on the quality of the cables and the
 * PHY. So allow testing क्रम up to 150 meters.
 */
#घोषणा MAX_CABLE_LENGTH_CM (150 * 100)

स्थिर काष्ठा nla_policy ethnl_cable_test_act_policy[] = अणु
	[ETHTOOL_A_CABLE_TEST_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक ethnl_cable_test_started(काष्ठा phy_device *phydev, u8 cmd)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOMEM;
	व्योम *ehdr;

	skb = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!skb)
		जाओ out;

	ehdr = ethnl_bcasपंचांगsg_put(skb, cmd);
	अगर (!ehdr) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	err = ethnl_fill_reply_header(skb, phydev->attached_dev,
				      ETHTOOL_A_CABLE_TEST_NTF_HEADER);
	अगर (err)
		जाओ out;

	err = nla_put_u8(skb, ETHTOOL_A_CABLE_TEST_NTF_STATUS,
			 ETHTOOL_A_CABLE_TEST_NTF_STATUS_STARTED);
	अगर (err)
		जाओ out;

	genlmsg_end(skb, ehdr);

	वापस ethnl_multicast(skb, phydev->attached_dev);

out:
	nlmsg_मुक्त(skb);
	phydev_err(phydev, "%s: Error %pe\n", __func__, ERR_PTR(err));

	वापस err;
पूर्ण

पूर्णांक ethnl_act_cable_test(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	स्थिर काष्ठा ethtool_phy_ops *ops;
	काष्ठा nlattr **tb = info->attrs;
	काष्ठा net_device *dev;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_CABLE_TEST_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;

	dev = req_info.dev;
	अगर (!dev->phydev) अणु
		ret = -EOPNOTSUPP;
		जाओ out_dev_put;
	पूर्ण

	rtnl_lock();
	ops = ethtool_phy_ops;
	अगर (!ops || !ops->start_cable_test) अणु
		ret = -EOPNOTSUPP;
		जाओ out_rtnl;
	पूर्ण

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;

	ret = ops->start_cable_test(dev->phydev, info->extack);

	ethnl_ops_complete(dev);

	अगर (!ret)
		ethnl_cable_test_started(dev->phydev,
					 ETHTOOL_MSG_CABLE_TEST_NTF);

out_rtnl:
	rtnl_unlock();
out_dev_put:
	dev_put(dev);
	वापस ret;
पूर्ण

पूर्णांक ethnl_cable_test_alloc(काष्ठा phy_device *phydev, u8 cmd)
अणु
	पूर्णांक err = -ENOMEM;

	/* One TDR sample occupies 20 bytes. For a 150 meter cable,
	 * with four pairs, around 12K is needed.
	 */
	phydev->skb = genlmsg_new(SZ_16K, GFP_KERNEL);
	अगर (!phydev->skb)
		जाओ out;

	phydev->ehdr = ethnl_bcasपंचांगsg_put(phydev->skb, cmd);
	अगर (!phydev->ehdr) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	err = ethnl_fill_reply_header(phydev->skb, phydev->attached_dev,
				      ETHTOOL_A_CABLE_TEST_NTF_HEADER);
	अगर (err)
		जाओ out;

	err = nla_put_u8(phydev->skb, ETHTOOL_A_CABLE_TEST_NTF_STATUS,
			 ETHTOOL_A_CABLE_TEST_NTF_STATUS_COMPLETED);
	अगर (err)
		जाओ out;

	phydev->nest = nla_nest_start(phydev->skb,
				      ETHTOOL_A_CABLE_TEST_NTF_NEST);
	अगर (!phydev->nest) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	वापस 0;

out:
	nlmsg_मुक्त(phydev->skb);
	phydev->skb = शून्य;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ethnl_cable_test_alloc);

व्योम ethnl_cable_test_मुक्त(काष्ठा phy_device *phydev)
अणु
	nlmsg_मुक्त(phydev->skb);
	phydev->skb = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ethnl_cable_test_मुक्त);

व्योम ethnl_cable_test_finished(काष्ठा phy_device *phydev)
अणु
	nla_nest_end(phydev->skb, phydev->nest);

	genlmsg_end(phydev->skb, phydev->ehdr);

	ethnl_multicast(phydev->skb, phydev->attached_dev);
पूर्ण
EXPORT_SYMBOL_GPL(ethnl_cable_test_finished);

पूर्णांक ethnl_cable_test_result(काष्ठा phy_device *phydev, u8 pair, u8 result)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक ret = -EMSGSIZE;

	nest = nla_nest_start(phydev->skb, ETHTOOL_A_CABLE_NEST_RESULT);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u8(phydev->skb, ETHTOOL_A_CABLE_RESULT_PAIR, pair))
		जाओ err;
	अगर (nla_put_u8(phydev->skb, ETHTOOL_A_CABLE_RESULT_CODE, result))
		जाओ err;

	nla_nest_end(phydev->skb, nest);
	वापस 0;

err:
	nla_nest_cancel(phydev->skb, nest);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ethnl_cable_test_result);

पूर्णांक ethnl_cable_test_fault_length(काष्ठा phy_device *phydev, u8 pair, u32 cm)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक ret = -EMSGSIZE;

	nest = nla_nest_start(phydev->skb,
			      ETHTOOL_A_CABLE_NEST_FAULT_LENGTH);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u8(phydev->skb, ETHTOOL_A_CABLE_FAULT_LENGTH_PAIR, pair))
		जाओ err;
	अगर (nla_put_u32(phydev->skb, ETHTOOL_A_CABLE_FAULT_LENGTH_CM, cm))
		जाओ err;

	nla_nest_end(phydev->skb, nest);
	वापस 0;

err:
	nla_nest_cancel(phydev->skb, nest);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ethnl_cable_test_fault_length);

काष्ठा cable_test_tdr_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

अटल स्थिर काष्ठा nla_policy cable_test_tdr_act_cfg_policy[] = अणु
	[ETHTOOL_A_CABLE_TEST_TDR_CFG_FIRST]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_CABLE_TEST_TDR_CFG_LAST]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_CABLE_TEST_TDR_CFG_STEP]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_CABLE_TEST_TDR_CFG_PAIR]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

स्थिर काष्ठा nla_policy ethnl_cable_test_tdr_act_policy[] = अणु
	[ETHTOOL_A_CABLE_TEST_TDR_HEADER]	=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_CABLE_TEST_TDR_CFG]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

/* CABLE_TEST_TDR_ACT */
अटल पूर्णांक ethnl_act_cable_test_tdr_cfg(स्थिर काष्ठा nlattr *nest,
					काष्ठा genl_info *info,
					काष्ठा phy_tdr_config *cfg)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(cable_test_tdr_act_cfg_policy)];
	पूर्णांक ret;

	cfg->first = 100;
	cfg->step = 100;
	cfg->last = MAX_CABLE_LENGTH_CM;
	cfg->pair = PHY_PAIR_ALL;

	अगर (!nest)
		वापस 0;

	ret = nla_parse_nested(tb,
			       ARRAY_SIZE(cable_test_tdr_act_cfg_policy) - 1,
			       nest, cable_test_tdr_act_cfg_policy,
			       info->extack);
	अगर (ret < 0)
		वापस ret;

	अगर (tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_FIRST])
		cfg->first = nla_get_u32(
			tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_FIRST]);

	अगर (tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_LAST])
		cfg->last = nla_get_u32(tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_LAST]);

	अगर (tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_STEP])
		cfg->step = nla_get_u32(tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_STEP]);

	अगर (tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_PAIR]) अणु
		cfg->pair = nla_get_u8(tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_PAIR]);
		अगर (cfg->pair > ETHTOOL_A_CABLE_PAIR_D) अणु
			NL_SET_ERR_MSG_ATTR(
				info->extack,
				tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_PAIR],
				"invalid pair parameter");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (cfg->first > MAX_CABLE_LENGTH_CM) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_FIRST],
				    "invalid first parameter");
		वापस -EINVAL;
	पूर्ण

	अगर (cfg->last > MAX_CABLE_LENGTH_CM) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_LAST],
				    "invalid last parameter");
		वापस -EINVAL;
	पूर्ण

	अगर (cfg->first > cfg->last) अणु
		NL_SET_ERR_MSG(info->extack, "invalid first/last parameter");
		वापस -EINVAL;
	पूर्ण

	अगर (!cfg->step) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_STEP],
				    "invalid step parameter");
		वापस -EINVAL;
	पूर्ण

	अगर (cfg->step > (cfg->last - cfg->first)) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[ETHTOOL_A_CABLE_TEST_TDR_CFG_STEP],
				    "step parameter too big");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ethnl_act_cable_test_tdr(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	स्थिर काष्ठा ethtool_phy_ops *ops;
	काष्ठा nlattr **tb = info->attrs;
	काष्ठा phy_tdr_config cfg;
	काष्ठा net_device *dev;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_CABLE_TEST_TDR_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;

	dev = req_info.dev;
	अगर (!dev->phydev) अणु
		ret = -EOPNOTSUPP;
		जाओ out_dev_put;
	पूर्ण

	ret = ethnl_act_cable_test_tdr_cfg(tb[ETHTOOL_A_CABLE_TEST_TDR_CFG],
					   info, &cfg);
	अगर (ret)
		जाओ out_dev_put;

	rtnl_lock();
	ops = ethtool_phy_ops;
	अगर (!ops || !ops->start_cable_test_tdr) अणु
		ret = -EOPNOTSUPP;
		जाओ out_rtnl;
	पूर्ण

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;

	ret = ops->start_cable_test_tdr(dev->phydev, info->extack, &cfg);

	ethnl_ops_complete(dev);

	अगर (!ret)
		ethnl_cable_test_started(dev->phydev,
					 ETHTOOL_MSG_CABLE_TEST_TDR_NTF);

out_rtnl:
	rtnl_unlock();
out_dev_put:
	dev_put(dev);
	वापस ret;
पूर्ण
 
पूर्णांक ethnl_cable_test_amplitude(काष्ठा phy_device *phydev,
			       u8 pair, s16 mV)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक ret = -EMSGSIZE;

	nest = nla_nest_start(phydev->skb,
			      ETHTOOL_A_CABLE_TDR_NEST_AMPLITUDE);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u8(phydev->skb, ETHTOOL_A_CABLE_AMPLITUDE_PAIR, pair))
		जाओ err;
	अगर (nla_put_u16(phydev->skb, ETHTOOL_A_CABLE_AMPLITUDE_mV, mV))
		जाओ err;

	nla_nest_end(phydev->skb, nest);
	वापस 0;

err:
	nla_nest_cancel(phydev->skb, nest);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ethnl_cable_test_amplitude);

पूर्णांक ethnl_cable_test_pulse(काष्ठा phy_device *phydev, u16 mV)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक ret = -EMSGSIZE;

	nest = nla_nest_start(phydev->skb, ETHTOOL_A_CABLE_TDR_NEST_PULSE);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u16(phydev->skb, ETHTOOL_A_CABLE_PULSE_mV, mV))
		जाओ err;

	nla_nest_end(phydev->skb, nest);
	वापस 0;

err:
	nla_nest_cancel(phydev->skb, nest);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ethnl_cable_test_pulse);

पूर्णांक ethnl_cable_test_step(काष्ठा phy_device *phydev, u32 first, u32 last,
			  u32 step)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक ret = -EMSGSIZE;

	nest = nla_nest_start(phydev->skb, ETHTOOL_A_CABLE_TDR_NEST_STEP);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(phydev->skb, ETHTOOL_A_CABLE_STEP_FIRST_DISTANCE,
			first))
		जाओ err;

	अगर (nla_put_u32(phydev->skb, ETHTOOL_A_CABLE_STEP_LAST_DISTANCE, last))
		जाओ err;

	अगर (nla_put_u32(phydev->skb, ETHTOOL_A_CABLE_STEP_STEP_DISTANCE, step))
		जाओ err;

	nla_nest_end(phydev->skb, nest);
	वापस 0;

err:
	nla_nest_cancel(phydev->skb, nest);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ethnl_cable_test_step);
