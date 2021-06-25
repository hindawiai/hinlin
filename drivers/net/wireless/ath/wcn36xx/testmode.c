<शैली गुरु>
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <net/netlink.h>
#समावेश <linux/firmware.h>
#समावेश <net/cfg80211.h>
#समावेश "wcn36xx.h"

#समावेश "testmode.h"
#समावेश "testmode_i.h"
#समावेश "hal.h"
#समावेश "smd.h"

अटल स्थिर काष्ठा nla_policy wcn36xx_पंचांग_policy[WCN36XX_TM_ATTR_MAX + 1] = अणु
	[WCN36XX_TM_ATTR_CMD] = अणु .type = NLA_U16 पूर्ण,
	[WCN36XX_TM_ATTR_DATA] = अणु .type = NLA_BINARY,
	.len = WCN36XX_TM_DATA_MAX_LEN पूर्ण,
पूर्ण;

काष्ठा build_release_number अणु
	u16 drv_major;
	u16 drv_minor;
	u16 drv_patch;
	u16 drv_build;
	u16 ptt_max;
	u16 ptt_min;
	u16 fw_ver;
पूर्ण __packed;

अटल पूर्णांक wcn36xx_पंचांग_cmd_ptt(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा nlattr *tb[])
अणु
	पूर्णांक ret = 0, buf_len;
	व्योम *buf;
	काष्ठा fपंचांग_rsp_msg *msg, *rsp = शून्य;
	काष्ठा sk_buff *skb;

	अगर (!tb[WCN36XX_TM_ATTR_DATA])
		वापस -EINVAL;

	buf = nla_data(tb[WCN36XX_TM_ATTR_DATA]);
	buf_len = nla_len(tb[WCN36XX_TM_ATTR_DATA]);
	msg = (काष्ठा fपंचांग_rsp_msg *)buf;

	wcn36xx_dbg(WCN36XX_DBG_TESTMODE,
		    "testmode cmd wmi msg_id 0x%04X msg_len %d buf %pK buf_len %d\n",
		   msg->msg_id, msg->msg_body_length,
		   buf, buf_len);

	wcn36xx_dbg_dump(WCN36XX_DBG_TESTMODE_DUMP, "REQ ", buf, buf_len);

	अगर (msg->msg_id == MSG_GET_BUILD_RELEASE_NUMBER) अणु
		काष्ठा build_release_number *body =
				(काष्ठा build_release_number *)
				msg->msg_response;

		body->drv_major = wcn->fw_major;
		body->drv_minor = wcn->fw_minor;
		body->drv_patch = wcn->fw_version;
		body->drv_build = wcn->fw_revision;
		body->ptt_max = 10;
		body->ptt_min = 0;

		rsp = msg;
		rsp->resp_status = 0;
	पूर्ण अन्यथा अणु
		wcn36xx_dbg(WCN36XX_DBG_TESTMODE,
			    "PPT Request >> HAL size %d\n",
				msg->msg_body_length);

		msg->resp_status = wcn36xx_smd_process_ptt_msg(wcn, vअगर, msg,
							       msg->msg_body_length, (व्योम *)(&rsp));

		wcn36xx_dbg(WCN36XX_DBG_TESTMODE,
			    "Response status = %d\n",
				msg->resp_status);
		अगर (rsp)
			wcn36xx_dbg(WCN36XX_DBG_TESTMODE,
				    "PPT Response << HAL size %d\n",
					rsp->msg_body_length);
	पूर्ण

	अगर (!rsp) अणु
		rsp = msg;
		wcn36xx_warn("No response! Echoing request with response status %d\n",
			     rsp->resp_status);
	पूर्ण
	wcn36xx_dbg_dump(WCN36XX_DBG_TESTMODE_DUMP, "RSP ",
			 rsp, rsp->msg_body_length);

	skb = cfg80211_tesपंचांगode_alloc_reply_skb(wcn->hw->wiphy,
						nla_total_size(msg->msg_body_length));
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = nla_put(skb, WCN36XX_TM_ATTR_DATA, rsp->msg_body_length, rsp);
	अगर (ret) अणु
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	ret = cfg80211_tesपंचांगode_reply(skb);

out:
	अगर (rsp != msg)
		kमुक्त(rsp);

	वापस ret;
पूर्ण

पूर्णांक wcn36xx_पंचांग_cmd(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   व्योम *data, पूर्णांक len)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा nlattr *tb[WCN36XX_TM_ATTR_MAX + 1];
	पूर्णांक ret = 0;
	अचिन्हित लघु attr;

	wcn36xx_dbg_dump(WCN36XX_DBG_TESTMODE_DUMP, "Data:", data, len);
	ret = nla_parse_deprecated(tb, WCN36XX_TM_ATTR_MAX, data, len,
				   wcn36xx_पंचांग_policy, शून्य);
	अगर (ret)
		वापस ret;

	अगर (!tb[WCN36XX_TM_ATTR_CMD])
		वापस -EINVAL;

	attr = nla_get_u16(tb[WCN36XX_TM_ATTR_CMD]);

	अगर (attr != WCN36XX_TM_CMD_PTT)
		वापस -EOPNOTSUPP;

	वापस wcn36xx_पंचांग_cmd_ptt(wcn, vअगर, tb);
पूर्ण
