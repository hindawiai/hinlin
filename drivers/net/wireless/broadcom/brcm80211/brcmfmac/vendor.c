<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/cfg80211.h>
#समावेश <net/netlink.h>

#समावेश <brcmu_wअगरi.h>
#समावेश "fwil_types.h"
#समावेश "core.h"
#समावेश "p2p.h"
#समावेश "debug.h"
#समावेश "cfg80211.h"
#समावेश "vendor.h"
#समावेश "fwil.h"

अटल पूर्णांक brcmf_cfg80211_vndr_cmds_dcmd_handler(काष्ठा wiphy *wiphy,
						 काष्ठा wireless_dev *wdev,
						 स्थिर व्योम *data, पूर्णांक len)
अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	काष्ठा brcmf_अगर *अगरp;
	स्थिर काष्ठा brcmf_vndr_dcmd_hdr *cmdhdr = data;
	काष्ठा sk_buff *reply;
	अचिन्हित पूर्णांक payload, ret_len;
	व्योम *dcmd_buf = शून्य, *wr_poपूर्णांकer;
	u16 msglen, maxmsglen = PAGE_SIZE - 0x100;
	पूर्णांक ret;

	अगर (len < माप(*cmdhdr)) अणु
		brcmf_err("vendor command too short: %d\n", len);
		वापस -EINVAL;
	पूर्ण

	vअगर = container_of(wdev, काष्ठा brcmf_cfg80211_vअगर, wdev);
	अगरp = vअगर->अगरp;

	brcmf_dbg(TRACE, "ifidx=%d, cmd=%d\n", अगरp->अगरidx, cmdhdr->cmd);

	अगर (cmdhdr->offset > len) अणु
		brcmf_err("bad buffer offset %d > %d\n", cmdhdr->offset, len);
		वापस -EINVAL;
	पूर्ण

	len -= cmdhdr->offset;
	ret_len = cmdhdr->len;
	अगर (ret_len > 0 || len > 0) अणु
		अगर (len > BRCMF_DCMD_MAXLEN) अणु
			brcmf_err("oversize input buffer %d\n", len);
			len = BRCMF_DCMD_MAXLEN;
		पूर्ण
		अगर (ret_len > BRCMF_DCMD_MAXLEN) अणु
			brcmf_err("oversize return buffer %d\n", ret_len);
			ret_len = BRCMF_DCMD_MAXLEN;
		पूर्ण
		payload = max_t(अचिन्हित पूर्णांक, ret_len, len) + 1;
		dcmd_buf = vzalloc(payload);
		अगर (शून्य == dcmd_buf)
			वापस -ENOMEM;

		स_नकल(dcmd_buf, (व्योम *)cmdhdr + cmdhdr->offset, len);
		*(अक्षर *)(dcmd_buf + len)  = '\0';
	पूर्ण

	अगर (cmdhdr->set)
		ret = brcmf_fil_cmd_data_set(अगरp, cmdhdr->cmd, dcmd_buf,
					     ret_len);
	अन्यथा
		ret = brcmf_fil_cmd_data_get(अगरp, cmdhdr->cmd, dcmd_buf,
					     ret_len);
	अगर (ret != 0)
		जाओ निकास;

	wr_poपूर्णांकer = dcmd_buf;
	जबतक (ret_len > 0) अणु
		msglen = ret_len > maxmsglen ? maxmsglen : ret_len;
		ret_len -= msglen;
		payload = msglen + माप(msglen);
		reply = cfg80211_venकरोr_cmd_alloc_reply_skb(wiphy, payload);
		अगर (शून्य == reply) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		अगर (nla_put(reply, BRCMF_NLATTR_DATA, msglen, wr_poपूर्णांकer) ||
		    nla_put_u16(reply, BRCMF_NLATTR_LEN, msglen)) अणु
			kमुक्त_skb(reply);
			ret = -ENOBUFS;
			अवरोध;
		पूर्ण

		ret = cfg80211_venकरोr_cmd_reply(reply);
		अगर (ret)
			अवरोध;

		wr_poपूर्णांकer += msglen;
	पूर्ण

निकास:
	vमुक्त(dcmd_buf);

	वापस ret;
पूर्ण

स्थिर काष्ठा wiphy_venकरोr_command brcmf_venकरोr_cmds[] = अणु
	अणु
		अणु
			.venकरोr_id = BROADCOM_OUI,
			.subcmd = BRCMF_VNDR_CMDS_DCMD
		पूर्ण,
		.flags = WIPHY_VENDOR_CMD_NEED_WDEV |
			 WIPHY_VENDOR_CMD_NEED_NETDEV,
		.policy = VENDOR_CMD_RAW_DATA,
		.करोit = brcmf_cfg80211_vndr_cmds_dcmd_handler
	पूर्ण,
पूर्ण;
