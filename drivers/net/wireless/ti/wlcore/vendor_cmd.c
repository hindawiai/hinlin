<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wlcore
 *
 * Copyright (C) 2014 Texas Instruments. All rights reserved.
 */

#समावेश <linux/pm_runसमय.स>

#समावेश <net/mac80211.h>
#समावेश <net/netlink.h>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "hw_ops.h"
#समावेश "vendor_cmd.h"

अटल स्थिर
काष्ठा nla_policy wlcore_venकरोr_attr_policy[NUM_WLCORE_VENDOR_ATTR] = अणु
	[WLCORE_VENDOR_ATTR_FREQ]		= अणु .type = NLA_U32 पूर्ण,
	[WLCORE_VENDOR_ATTR_GROUP_ID]		= अणु .type = NLA_U32 पूर्ण,
	[WLCORE_VENDOR_ATTR_GROUP_KEY]		= अणु .type = NLA_BINARY,
						    .len = WLAN_MAX_KEY_LEN पूर्ण,
पूर्ण;

अटल पूर्णांक
wlcore_venकरोr_cmd_smart_config_start(काष्ठा wiphy *wiphy,
				     काष्ठा wireless_dev *wdev,
				     स्थिर व्योम *data, पूर्णांक data_len)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा nlattr *tb[NUM_WLCORE_VENDOR_ATTR];
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD, "vendor cmd smart config start");

	अगर (!data)
		वापस -EINVAL;

	ret = nla_parse_deprecated(tb, MAX_WLCORE_VENDOR_ATTR, data, data_len,
				   wlcore_venकरोr_attr_policy, शून्य);
	अगर (ret)
		वापस ret;

	अगर (!tb[WLCORE_VENDOR_ATTR_GROUP_ID])
		वापस -EINVAL;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wlcore_smart_config_start(wl,
			nla_get_u32(tb[WLCORE_VENDOR_ATTR_GROUP_ID]));

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
wlcore_venकरोr_cmd_smart_config_stop(काष्ठा wiphy *wiphy,
				    काष्ठा wireless_dev *wdev,
				    स्थिर व्योम *data, पूर्णांक data_len)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा wl1271 *wl = hw->priv;
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD, "testmode cmd smart config stop");

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wlcore_smart_config_stop(wl);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
wlcore_venकरोr_cmd_smart_config_set_group_key(काष्ठा wiphy *wiphy,
					     काष्ठा wireless_dev *wdev,
					     स्थिर व्योम *data, पूर्णांक data_len)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा nlattr *tb[NUM_WLCORE_VENDOR_ATTR];
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD, "testmode cmd smart config set group key");

	अगर (!data)
		वापस -EINVAL;

	ret = nla_parse_deprecated(tb, MAX_WLCORE_VENDOR_ATTR, data, data_len,
				   wlcore_venकरोr_attr_policy, शून्य);
	अगर (ret)
		वापस ret;

	अगर (!tb[WLCORE_VENDOR_ATTR_GROUP_ID] ||
	    !tb[WLCORE_VENDOR_ATTR_GROUP_KEY])
		वापस -EINVAL;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wlcore_smart_config_set_group_key(wl,
			nla_get_u32(tb[WLCORE_VENDOR_ATTR_GROUP_ID]),
			nla_len(tb[WLCORE_VENDOR_ATTR_GROUP_KEY]),
			nla_data(tb[WLCORE_VENDOR_ATTR_GROUP_KEY]));

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा wiphy_venकरोr_command wlcore_venकरोr_commands[] = अणु
	अणु
		.info = अणु
			.venकरोr_id = TI_OUI,
			.subcmd = WLCORE_VENDOR_CMD_SMART_CONFIG_START,
		पूर्ण,
		.flags = WIPHY_VENDOR_CMD_NEED_NETDEV |
			 WIPHY_VENDOR_CMD_NEED_RUNNING,
		.करोit = wlcore_venकरोr_cmd_smart_config_start,
		.policy = wlcore_venकरोr_attr_policy,
	पूर्ण,
	अणु
		.info = अणु
			.venकरोr_id = TI_OUI,
			.subcmd = WLCORE_VENDOR_CMD_SMART_CONFIG_STOP,
		पूर्ण,
		.flags = WIPHY_VENDOR_CMD_NEED_NETDEV |
			 WIPHY_VENDOR_CMD_NEED_RUNNING,
		.करोit = wlcore_venकरोr_cmd_smart_config_stop,
		.policy = wlcore_venकरोr_attr_policy,
	पूर्ण,
	अणु
		.info = अणु
			.venकरोr_id = TI_OUI,
			.subcmd = WLCORE_VENDOR_CMD_SMART_CONFIG_SET_GROUP_KEY,
		पूर्ण,
		.flags = WIPHY_VENDOR_CMD_NEED_NETDEV |
			 WIPHY_VENDOR_CMD_NEED_RUNNING,
		.करोit = wlcore_venकरोr_cmd_smart_config_set_group_key,
		.policy = wlcore_venकरोr_attr_policy,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nl80211_venकरोr_cmd_info wlcore_venकरोr_events[] = अणु
	अणु
		.venकरोr_id = TI_OUI,
		.subcmd = WLCORE_VENDOR_EVENT_SC_SYNC,
	पूर्ण,
	अणु
		.venकरोr_id = TI_OUI,
		.subcmd = WLCORE_VENDOR_EVENT_SC_DECODE,
	पूर्ण,
पूर्ण;

व्योम wlcore_set_venकरोr_commands(काष्ठा wiphy *wiphy)
अणु
	wiphy->venकरोr_commands = wlcore_venकरोr_commands;
	wiphy->n_venकरोr_commands = ARRAY_SIZE(wlcore_venकरोr_commands);
	wiphy->venकरोr_events = wlcore_venकरोr_events;
	wiphy->n_venकरोr_events = ARRAY_SIZE(wlcore_venकरोr_events);
पूर्ण
