<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */
#समावेश "testmode.h"

#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <net/genetlink.h>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "acx.h"
#समावेश "io.h"

#घोषणा WL1271_TM_MAX_DATA_LENGTH 1024

क्रमागत wl1271_पंचांग_commands अणु
	WL1271_TM_CMD_UNSPEC,
	WL1271_TM_CMD_TEST,
	WL1271_TM_CMD_INTERROGATE,
	WL1271_TM_CMD_CONFIGURE,
	WL1271_TM_CMD_NVS_PUSH,		/* Not in use. Keep to not अवरोध ABI */
	WL1271_TM_CMD_SET_PLT_MODE,
	WL1271_TM_CMD_RECOVER,		/* Not in use. Keep to not अवरोध ABI */
	WL1271_TM_CMD_GET_MAC,

	__WL1271_TM_CMD_AFTER_LAST
पूर्ण;
#घोषणा WL1271_TM_CMD_MAX (__WL1271_TM_CMD_AFTER_LAST - 1)

क्रमागत wl1271_पंचांग_attrs अणु
	WL1271_TM_ATTR_UNSPEC,
	WL1271_TM_ATTR_CMD_ID,
	WL1271_TM_ATTR_ANSWER,
	WL1271_TM_ATTR_DATA,
	WL1271_TM_ATTR_IE_ID,
	WL1271_TM_ATTR_PLT_MODE,

	__WL1271_TM_ATTR_AFTER_LAST
पूर्ण;
#घोषणा WL1271_TM_ATTR_MAX (__WL1271_TM_ATTR_AFTER_LAST - 1)

अटल काष्ठा nla_policy wl1271_पंचांग_policy[WL1271_TM_ATTR_MAX + 1] = अणु
	[WL1271_TM_ATTR_CMD_ID] =	अणु .type = NLA_U32 पूर्ण,
	[WL1271_TM_ATTR_ANSWER] =	अणु .type = NLA_U8 पूर्ण,
	[WL1271_TM_ATTR_DATA] =		अणु .type = NLA_BINARY,
					  .len = WL1271_TM_MAX_DATA_LENGTH पूर्ण,
	[WL1271_TM_ATTR_IE_ID] =	अणु .type = NLA_U32 पूर्ण,
	[WL1271_TM_ATTR_PLT_MODE] =	अणु .type = NLA_U32 पूर्ण,
पूर्ण;


अटल पूर्णांक wl1271_पंचांग_cmd_test(काष्ठा wl1271 *wl, काष्ठा nlattr *tb[])
अणु
	पूर्णांक buf_len, ret, len;
	काष्ठा sk_buff *skb;
	व्योम *buf;
	u8 answer = 0;

	wl1271_debug(DEBUG_TESTMODE, "testmode cmd test");

	अगर (!tb[WL1271_TM_ATTR_DATA])
		वापस -EINVAL;

	buf = nla_data(tb[WL1271_TM_ATTR_DATA]);
	buf_len = nla_len(tb[WL1271_TM_ATTR_DATA]);

	अगर (tb[WL1271_TM_ATTR_ANSWER])
		answer = nla_get_u8(tb[WL1271_TM_ATTR_ANSWER]);

	अगर (buf_len > माप(काष्ठा wl1271_command))
		वापस -EMSGSIZE;

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

	ret = wl1271_cmd_test(wl, buf, buf_len, answer);
	अगर (ret < 0) अणु
		wl1271_warning("testmode cmd test failed: %d", ret);
		जाओ out_sleep;
	पूर्ण

	अगर (answer) अणु
		/* If we got bip calibration answer prपूर्णांक radio status */
		काष्ठा wl1271_cmd_cal_p2g *params =
			(काष्ठा wl1271_cmd_cal_p2g *) buf;

		s16 radio_status = (s16) le16_to_cpu(params->radio_status);

		अगर (params->test.id == TEST_CMD_P2G_CAL &&
		    radio_status < 0)
			wl1271_warning("testmode cmd: radio status=%d",
					radio_status);
		अन्यथा
			wl1271_info("testmode cmd: radio status=%d",
					radio_status);

		len = nla_total_size(buf_len);
		skb = cfg80211_tesपंचांगode_alloc_reply_skb(wl->hw->wiphy, len);
		अगर (!skb) अणु
			ret = -ENOMEM;
			जाओ out_sleep;
		पूर्ण

		अगर (nla_put(skb, WL1271_TM_ATTR_DATA, buf_len, buf)) अणु
			kमुक्त_skb(skb);
			ret = -EMSGSIZE;
			जाओ out_sleep;
		पूर्ण

		ret = cfg80211_tesपंचांगode_reply(skb);
		अगर (ret < 0)
			जाओ out_sleep;
	पूर्ण

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_पंचांग_cmd_पूर्णांकerrogate(काष्ठा wl1271 *wl, काष्ठा nlattr *tb[])
अणु
	पूर्णांक ret;
	काष्ठा wl1271_command *cmd;
	काष्ठा sk_buff *skb;
	u8 ie_id;

	wl1271_debug(DEBUG_TESTMODE, "testmode cmd interrogate");

	अगर (!tb[WL1271_TM_ATTR_IE_ID])
		वापस -EINVAL;

	ie_id = nla_get_u8(tb[WL1271_TM_ATTR_IE_ID]);

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

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out_sleep;
	पूर्ण

	ret = wl1271_cmd_पूर्णांकerrogate(wl, ie_id, cmd,
				     माप(काष्ठा acx_header), माप(*cmd));
	अगर (ret < 0) अणु
		wl1271_warning("testmode cmd interrogate failed: %d", ret);
		जाओ out_मुक्त;
	पूर्ण

	skb = cfg80211_tesपंचांगode_alloc_reply_skb(wl->hw->wiphy, माप(*cmd));
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	अगर (nla_put(skb, WL1271_TM_ATTR_DATA, माप(*cmd), cmd)) अणु
		kमुक्त_skb(skb);
		ret = -EMSGSIZE;
		जाओ out_मुक्त;
	पूर्ण

	ret = cfg80211_tesपंचांगode_reply(skb);
	अगर (ret < 0)
		जाओ out_मुक्त;

out_मुक्त:
	kमुक्त(cmd);
out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_पंचांग_cmd_configure(काष्ठा wl1271 *wl, काष्ठा nlattr *tb[])
अणु
	पूर्णांक buf_len, ret;
	व्योम *buf;
	u8 ie_id;

	wl1271_debug(DEBUG_TESTMODE, "testmode cmd configure");

	अगर (!tb[WL1271_TM_ATTR_DATA])
		वापस -EINVAL;
	अगर (!tb[WL1271_TM_ATTR_IE_ID])
		वापस -EINVAL;

	ie_id = nla_get_u8(tb[WL1271_TM_ATTR_IE_ID]);
	buf = nla_data(tb[WL1271_TM_ATTR_DATA]);
	buf_len = nla_len(tb[WL1271_TM_ATTR_DATA]);

	अगर (buf_len > माप(काष्ठा wl1271_command))
		वापस -EMSGSIZE;

	mutex_lock(&wl->mutex);
	ret = wl1271_cmd_configure(wl, ie_id, buf, buf_len);
	mutex_unlock(&wl->mutex);

	अगर (ret < 0) अणु
		wl1271_warning("testmode cmd configure failed: %d", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_पंचांग_detect_fem(काष्ठा wl1271 *wl, काष्ठा nlattr *tb[])
अणु
	/* वापस FEM type */
	पूर्णांक ret, len;
	काष्ठा sk_buff *skb;

	ret = wl1271_plt_start(wl, PLT_FEM_DETECT);
	अगर (ret < 0)
		जाओ out;

	mutex_lock(&wl->mutex);

	len = nla_total_size(माप(wl->fem_manuf));
	skb = cfg80211_tesपंचांगode_alloc_reply_skb(wl->hw->wiphy, len);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out_mutex;
	पूर्ण

	अगर (nla_put(skb, WL1271_TM_ATTR_DATA, माप(wl->fem_manuf),
					      &wl->fem_manuf)) अणु
		kमुक्त_skb(skb);
		ret = -EMSGSIZE;
		जाओ out_mutex;
	पूर्ण

	ret = cfg80211_tesपंचांगode_reply(skb);

out_mutex:
	mutex_unlock(&wl->mutex);

	/* We always stop plt after DETECT mode */
	wl1271_plt_stop(wl);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_पंचांग_cmd_set_plt_mode(काष्ठा wl1271 *wl, काष्ठा nlattr *tb[])
अणु
	u32 val;
	पूर्णांक ret;

	wl1271_debug(DEBUG_TESTMODE, "testmode cmd set plt mode");

	अगर (!tb[WL1271_TM_ATTR_PLT_MODE])
		वापस -EINVAL;

	val = nla_get_u32(tb[WL1271_TM_ATTR_PLT_MODE]);

	चयन (val) अणु
	हाल PLT_OFF:
		ret = wl1271_plt_stop(wl);
		अवरोध;
	हाल PLT_ON:
	हाल PLT_CHIP_AWAKE:
		ret = wl1271_plt_start(wl, val);
		अवरोध;
	हाल PLT_FEM_DETECT:
		ret = wl1271_पंचांग_detect_fem(wl, tb);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_पंचांग_cmd_get_mac(काष्ठा wl1271 *wl, काष्ठा nlattr *tb[])
अणु
	काष्ठा sk_buff *skb;
	u8 mac_addr[ETH_ALEN];
	पूर्णांक ret = 0;

	mutex_lock(&wl->mutex);

	अगर (!wl->plt) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (wl->fuse_oui_addr == 0 && wl->fuse_nic_addr == 0) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	mac_addr[0] = (u8)(wl->fuse_oui_addr >> 16);
	mac_addr[1] = (u8)(wl->fuse_oui_addr >> 8);
	mac_addr[2] = (u8) wl->fuse_oui_addr;
	mac_addr[3] = (u8)(wl->fuse_nic_addr >> 16);
	mac_addr[4] = (u8)(wl->fuse_nic_addr >> 8);
	mac_addr[5] = (u8) wl->fuse_nic_addr;

	skb = cfg80211_tesपंचांगode_alloc_reply_skb(wl->hw->wiphy, ETH_ALEN);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (nla_put(skb, WL1271_TM_ATTR_DATA, ETH_ALEN, mac_addr)) अणु
		kमुक्त_skb(skb);
		ret = -EMSGSIZE;
		जाओ out;
	पूर्ण

	ret = cfg80211_tesपंचांगode_reply(skb);
	अगर (ret < 0)
		जाओ out;

out:
	mutex_unlock(&wl->mutex);
	वापस ret;
पूर्ण

पूर्णांक wl1271_पंचांग_cmd(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  व्योम *data, पूर्णांक len)
अणु
	काष्ठा wl1271 *wl = hw->priv;
	काष्ठा nlattr *tb[WL1271_TM_ATTR_MAX + 1];
	u32 nla_cmd;
	पूर्णांक err;

	err = nla_parse_deprecated(tb, WL1271_TM_ATTR_MAX, data, len,
				   wl1271_पंचांग_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!tb[WL1271_TM_ATTR_CMD_ID])
		वापस -EINVAL;

	nla_cmd = nla_get_u32(tb[WL1271_TM_ATTR_CMD_ID]);

	/* Only SET_PLT_MODE is allowed in हाल of mode PLT_CHIP_AWAKE */
	अगर (wl->plt_mode == PLT_CHIP_AWAKE &&
	    nla_cmd != WL1271_TM_CMD_SET_PLT_MODE)
		वापस -EOPNOTSUPP;

	चयन (nla_cmd) अणु
	हाल WL1271_TM_CMD_TEST:
		वापस wl1271_पंचांग_cmd_test(wl, tb);
	हाल WL1271_TM_CMD_INTERROGATE:
		वापस wl1271_पंचांग_cmd_पूर्णांकerrogate(wl, tb);
	हाल WL1271_TM_CMD_CONFIGURE:
		वापस wl1271_पंचांग_cmd_configure(wl, tb);
	हाल WL1271_TM_CMD_SET_PLT_MODE:
		वापस wl1271_पंचांग_cmd_set_plt_mode(wl, tb);
	हाल WL1271_TM_CMD_GET_MAC:
		वापस wl12xx_पंचांग_cmd_get_mac(wl, tb);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
