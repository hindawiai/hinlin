<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 - 2021 Intel Corporation
 */
#अगर_अघोषित __PMSR_H
#घोषणा __PMSR_H
#समावेश <net/cfg80211.h>
#समावेश "core.h"
#समावेश "nl80211.h"
#समावेश "rdev-ops.h"

अटल पूर्णांक pmsr_parse_fपंचांग(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा nlattr *fपंचांगreq,
			  काष्ठा cfg80211_pmsr_request_peer *out,
			  काष्ठा genl_info *info)
अणु
	स्थिर काष्ठा cfg80211_pmsr_capabilities *capa = rdev->wiphy.pmsr_capa;
	काष्ठा nlattr *tb[NL80211_PMSR_FTM_REQ_ATTR_MAX + 1];
	u32 preamble = NL80211_PREAMBLE_DMG; /* only optional in DMG */

	/* validate existing data */
	अगर (!(rdev->wiphy.pmsr_capa->fपंचांग.bandwidths & BIT(out->chandef.width))) अणु
		NL_SET_ERR_MSG(info->extack, "FTM: unsupported bandwidth");
		वापस -EINVAL;
	पूर्ण

	/* no validation needed - was alपढ़ोy करोne via nested policy */
	nla_parse_nested_deprecated(tb, NL80211_PMSR_FTM_REQ_ATTR_MAX, fपंचांगreq,
				    शून्य, शून्य);

	अगर (tb[NL80211_PMSR_FTM_REQ_ATTR_PREAMBLE])
		preamble = nla_get_u32(tb[NL80211_PMSR_FTM_REQ_ATTR_PREAMBLE]);

	/* set up values - काष्ठा is 0-initialized */
	out->fपंचांग.requested = true;

	चयन (out->chandef.chan->band) अणु
	हाल NL80211_BAND_60GHZ:
		/* optional */
		अवरोध;
	शेष:
		अगर (!tb[NL80211_PMSR_FTM_REQ_ATTR_PREAMBLE]) अणु
			NL_SET_ERR_MSG(info->extack,
				       "FTM: must specify preamble");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!(capa->fपंचांग.preambles & BIT(preamble))) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_PREAMBLE],
				    "FTM: invalid preamble");
		वापस -EINVAL;
	पूर्ण

	out->fपंचांग.preamble = preamble;

	out->fपंचांग.burst_period = 0;
	अगर (tb[NL80211_PMSR_FTM_REQ_ATTR_BURST_PERIOD])
		out->fपंचांग.burst_period =
			nla_get_u32(tb[NL80211_PMSR_FTM_REQ_ATTR_BURST_PERIOD]);

	out->fपंचांग.asap = !!tb[NL80211_PMSR_FTM_REQ_ATTR_ASAP];
	अगर (out->fपंचांग.asap && !capa->fपंचांग.asap) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_ASAP],
				    "FTM: ASAP mode not supported");
		वापस -EINVAL;
	पूर्ण

	अगर (!out->fपंचांग.asap && !capa->fपंचांग.non_asap) अणु
		NL_SET_ERR_MSG(info->extack,
			       "FTM: non-ASAP mode not supported");
		वापस -EINVAL;
	पूर्ण

	out->fपंचांग.num_bursts_exp = 0;
	अगर (tb[NL80211_PMSR_FTM_REQ_ATTR_NUM_BURSTS_EXP])
		out->fपंचांग.num_bursts_exp =
			nla_get_u32(tb[NL80211_PMSR_FTM_REQ_ATTR_NUM_BURSTS_EXP]);

	अगर (capa->fपंचांग.max_bursts_exponent >= 0 &&
	    out->fपंचांग.num_bursts_exp > capa->fपंचांग.max_bursts_exponent) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_NUM_BURSTS_EXP],
				    "FTM: max NUM_BURSTS_EXP must be set lower than the device limit");
		वापस -EINVAL;
	पूर्ण

	out->fपंचांग.burst_duration = 15;
	अगर (tb[NL80211_PMSR_FTM_REQ_ATTR_BURST_DURATION])
		out->fपंचांग.burst_duration =
			nla_get_u32(tb[NL80211_PMSR_FTM_REQ_ATTR_BURST_DURATION]);

	out->fपंचांग.fपंचांगs_per_burst = 0;
	अगर (tb[NL80211_PMSR_FTM_REQ_ATTR_FTMS_PER_BURST])
		out->fपंचांग.fपंचांगs_per_burst =
			nla_get_u32(tb[NL80211_PMSR_FTM_REQ_ATTR_FTMS_PER_BURST]);

	अगर (capa->fपंचांग.max_fपंचांगs_per_burst &&
	    (out->fपंचांग.fपंचांगs_per_burst > capa->fपंचांग.max_fपंचांगs_per_burst ||
	     out->fपंचांग.fपंचांगs_per_burst == 0)) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_FTMS_PER_BURST],
				    "FTM: FTMs per burst must be set lower than the device limit but non-zero");
		वापस -EINVAL;
	पूर्ण

	out->fपंचांग.fपंचांगr_retries = 3;
	अगर (tb[NL80211_PMSR_FTM_REQ_ATTR_NUM_FTMR_RETRIES])
		out->fपंचांग.fपंचांगr_retries =
			nla_get_u32(tb[NL80211_PMSR_FTM_REQ_ATTR_NUM_FTMR_RETRIES]);

	out->fपंचांग.request_lci = !!tb[NL80211_PMSR_FTM_REQ_ATTR_REQUEST_LCI];
	अगर (out->fपंचांग.request_lci && !capa->fपंचांग.request_lci) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_REQUEST_LCI],
				    "FTM: LCI request not supported");
	पूर्ण

	out->fपंचांग.request_civicloc =
		!!tb[NL80211_PMSR_FTM_REQ_ATTR_REQUEST_CIVICLOC];
	अगर (out->fपंचांग.request_civicloc && !capa->fपंचांग.request_civicloc) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_REQUEST_CIVICLOC],
			    "FTM: civic location request not supported");
	पूर्ण

	out->fपंचांग.trigger_based =
		!!tb[NL80211_PMSR_FTM_REQ_ATTR_TRIGGER_BASED];
	अगर (out->fपंचांग.trigger_based && !capa->fपंचांग.trigger_based) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_TRIGGER_BASED],
				    "FTM: trigger based ranging is not supported");
		वापस -EINVAL;
	पूर्ण

	out->fपंचांग.non_trigger_based =
		!!tb[NL80211_PMSR_FTM_REQ_ATTR_NON_TRIGGER_BASED];
	अगर (out->fपंचांग.non_trigger_based && !capa->fपंचांग.non_trigger_based) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_NON_TRIGGER_BASED],
				    "FTM: trigger based ranging is not supported");
		वापस -EINVAL;
	पूर्ण

	अगर (out->fपंचांग.trigger_based && out->fपंचांग.non_trigger_based) अणु
		NL_SET_ERR_MSG(info->extack,
			       "FTM: can't set both trigger based and non trigger based");
		वापस -EINVAL;
	पूर्ण

	अगर ((out->fपंचांग.trigger_based || out->fपंचांग.non_trigger_based) &&
	    out->fपंचांग.preamble != NL80211_PREAMBLE_HE) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_PREAMBLE],
				    "FTM: non EDCA based ranging must use HE preamble");
		वापस -EINVAL;
	पूर्ण

	out->fपंचांग.lmr_feedback =
		!!tb[NL80211_PMSR_FTM_REQ_ATTR_LMR_FEEDBACK];
	अगर (!out->fपंचांग.trigger_based && !out->fपंचांग.non_trigger_based &&
	    out->fपंचांग.lmr_feedback) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_FTM_REQ_ATTR_LMR_FEEDBACK],
				    "FTM: LMR feedback set for EDCA based ranging");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pmsr_parse_peer(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा nlattr *peer,
			   काष्ठा cfg80211_pmsr_request_peer *out,
			   काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *tb[NL80211_PMSR_PEER_ATTR_MAX + 1];
	काष्ठा nlattr *req[NL80211_PMSR_REQ_ATTR_MAX + 1];
	काष्ठा nlattr *treq;
	पूर्णांक err, rem;

	/* no validation needed - was alपढ़ोy करोne via nested policy */
	nla_parse_nested_deprecated(tb, NL80211_PMSR_PEER_ATTR_MAX, peer,
				    शून्य, शून्य);

	अगर (!tb[NL80211_PMSR_PEER_ATTR_ADDR] ||
	    !tb[NL80211_PMSR_PEER_ATTR_CHAN] ||
	    !tb[NL80211_PMSR_PEER_ATTR_REQ]) अणु
		NL_SET_ERR_MSG_ATTR(info->extack, peer,
				    "insufficient peer data");
		वापस -EINVAL;
	पूर्ण

	स_नकल(out->addr, nla_data(tb[NL80211_PMSR_PEER_ATTR_ADDR]), ETH_ALEN);

	/* reuse info->attrs */
	स_रखो(info->attrs, 0, माप(*info->attrs) * (NL80211_ATTR_MAX + 1));
	err = nla_parse_nested_deprecated(info->attrs, NL80211_ATTR_MAX,
					  tb[NL80211_PMSR_PEER_ATTR_CHAN],
					  शून्य, info->extack);
	अगर (err)
		वापस err;

	err = nl80211_parse_chandef(rdev, info, &out->chandef);
	अगर (err)
		वापस err;

	/* no validation needed - was alपढ़ोy करोne via nested policy */
	nla_parse_nested_deprecated(req, NL80211_PMSR_REQ_ATTR_MAX,
				    tb[NL80211_PMSR_PEER_ATTR_REQ], शून्य,
				    शून्य);

	अगर (!req[NL80211_PMSR_REQ_ATTR_DATA]) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    tb[NL80211_PMSR_PEER_ATTR_REQ],
				    "missing request type/data");
		वापस -EINVAL;
	पूर्ण

	अगर (req[NL80211_PMSR_REQ_ATTR_GET_AP_TSF])
		out->report_ap_tsf = true;

	अगर (out->report_ap_tsf && !rdev->wiphy.pmsr_capa->report_ap_tsf) अणु
		NL_SET_ERR_MSG_ATTR(info->extack,
				    req[NL80211_PMSR_REQ_ATTR_GET_AP_TSF],
				    "reporting AP TSF is not supported");
		वापस -EINVAL;
	पूर्ण

	nla_क्रम_each_nested(treq, req[NL80211_PMSR_REQ_ATTR_DATA], rem) अणु
		चयन (nla_type(treq)) अणु
		हाल NL80211_PMSR_TYPE_FTM:
			err = pmsr_parse_fपंचांग(rdev, treq, out, info);
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_ATTR(info->extack, treq,
					    "unsupported measurement type");
			err = -EINVAL;
		पूर्ण
	पूर्ण

	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक nl80211_pmsr_start(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *reqattr = info->attrs[NL80211_ATTR_PEER_MEASUREMENTS];
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	काष्ठा cfg80211_pmsr_request *req;
	काष्ठा nlattr *peers, *peer;
	पूर्णांक count, rem, err, idx;

	अगर (!rdev->wiphy.pmsr_capa)
		वापस -EOPNOTSUPP;

	अगर (!reqattr)
		वापस -EINVAL;

	peers = nla_find(nla_data(reqattr), nla_len(reqattr),
			 NL80211_PMSR_ATTR_PEERS);
	अगर (!peers)
		वापस -EINVAL;

	count = 0;
	nla_क्रम_each_nested(peer, peers, rem) अणु
		count++;

		अगर (count > rdev->wiphy.pmsr_capa->max_peers) अणु
			NL_SET_ERR_MSG_ATTR(info->extack, peer,
					    "Too many peers used");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	req = kzalloc(काष्ठा_size(req, peers, count), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	अगर (info->attrs[NL80211_ATTR_TIMEOUT])
		req->समयout = nla_get_u32(info->attrs[NL80211_ATTR_TIMEOUT]);

	अगर (info->attrs[NL80211_ATTR_MAC]) अणु
		अगर (!rdev->wiphy.pmsr_capa->अक्रमomize_mac_addr) अणु
			NL_SET_ERR_MSG_ATTR(info->extack,
					    info->attrs[NL80211_ATTR_MAC],
					    "device cannot randomize MAC address");
			err = -EINVAL;
			जाओ out_err;
		पूर्ण

		err = nl80211_parse_अक्रमom_mac(info->attrs, req->mac_addr,
					       req->mac_addr_mask);
		अगर (err)
			जाओ out_err;
	पूर्ण अन्यथा अणु
		स_नकल(req->mac_addr, wdev_address(wdev), ETH_ALEN);
		eth_broadcast_addr(req->mac_addr_mask);
	पूर्ण

	idx = 0;
	nla_क्रम_each_nested(peer, peers, rem) अणु
		/* NB: this reuses info->attrs, but we no दीर्घer need it */
		err = pmsr_parse_peer(rdev, peer, &req->peers[idx], info);
		अगर (err)
			जाओ out_err;
		idx++;
	पूर्ण

	req->n_peers = count;
	req->cookie = cfg80211_assign_cookie(rdev);
	req->nl_portid = info->snd_portid;

	err = rdev_start_pmsr(rdev, wdev, req);
	अगर (err)
		जाओ out_err;

	list_add_tail(&req->list, &wdev->pmsr_list);

	nl_set_extack_cookie_u64(info->extack, req->cookie);
	वापस 0;
out_err:
	kमुक्त(req);
	वापस err;
पूर्ण

व्योम cfg80211_pmsr_complete(काष्ठा wireless_dev *wdev,
			    काष्ठा cfg80211_pmsr_request *req,
			    gfp_t gfp)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_pmsr_request *पंचांगp, *prev, *to_मुक्त = शून्य;
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	trace_cfg80211_pmsr_complete(wdev->wiphy, wdev, req->cookie);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		जाओ मुक्त_request;

	hdr = nl80211hdr_put(msg, 0, 0, 0,
			     NL80211_CMD_PEER_MEASUREMENT_COMPLETE);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		जाओ मुक्त_msg;

	अगर (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, req->cookie,
			      NL80211_ATTR_PAD))
		जाओ मुक्त_msg;

	genlmsg_end(msg, hdr);
	genlmsg_unicast(wiphy_net(wdev->wiphy), msg, req->nl_portid);
	जाओ मुक्त_request;
मुक्त_msg:
	nlmsg_मुक्त(msg);
मुक्त_request:
	spin_lock_bh(&wdev->pmsr_lock);
	/*
	 * cfg80211_pmsr_process_पात() may have alपढ़ोy moved this request
	 * to the मुक्त list, and will मुक्त it later. In this हाल, करोn't मुक्त
	 * it here.
	 */
	list_क्रम_each_entry_safe(पंचांगp, prev, &wdev->pmsr_list, list) अणु
		अगर (पंचांगp == req) अणु
			list_del(&req->list);
			to_मुक्त = req;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&wdev->pmsr_lock);
	kमुक्त(to_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(cfg80211_pmsr_complete);

अटल पूर्णांक nl80211_pmsr_send_fपंचांग_res(काष्ठा sk_buff *msg,
				     काष्ठा cfg80211_pmsr_result *res)
अणु
	अगर (res->status == NL80211_PMSR_STATUS_FAILURE) अणु
		अगर (nla_put_u32(msg, NL80211_PMSR_FTM_RESP_ATTR_FAIL_REASON,
				res->fपंचांग.failure_reason))
			जाओ error;

		अगर (res->fपंचांग.failure_reason ==
			NL80211_PMSR_FTM_FAILURE_PEER_BUSY &&
		    res->fपंचांग.busy_retry_समय &&
		    nla_put_u32(msg, NL80211_PMSR_FTM_RESP_ATTR_BUSY_RETRY_TIME,
				res->fपंचांग.busy_retry_समय))
			जाओ error;

		वापस 0;
	पूर्ण

#घोषणा PUT(tp, attr, val)						\
	करो अणु								\
		अगर (nla_put_##tp(msg,					\
				 NL80211_PMSR_FTM_RESP_ATTR_##attr,	\
				 res->fपंचांग.val))				\
			जाओ error;					\
	पूर्ण जबतक (0)

#घोषणा PUTOPT(tp, attr, val)						\
	करो अणु								\
		अगर (res->fपंचांग.val##_valid)				\
			PUT(tp, attr, val);				\
	पूर्ण जबतक (0)

#घोषणा PUT_U64(attr, val)						\
	करो अणु								\
		अगर (nla_put_u64_64bit(msg,				\
				      NL80211_PMSR_FTM_RESP_ATTR_##attr,\
				      res->fपंचांग.val,			\
				      NL80211_PMSR_FTM_RESP_ATTR_PAD))	\
			जाओ error;					\
	पूर्ण जबतक (0)

#घोषणा PUTOPT_U64(attr, val)						\
	करो अणु								\
		अगर (res->fपंचांग.val##_valid)				\
			PUT_U64(attr, val);				\
	पूर्ण जबतक (0)

	अगर (res->fपंचांग.burst_index >= 0)
		PUT(u32, BURST_INDEX, burst_index);
	PUTOPT(u32, NUM_FTMR_ATTEMPTS, num_fपंचांगr_attempts);
	PUTOPT(u32, NUM_FTMR_SUCCESSES, num_fपंचांगr_successes);
	PUT(u8, NUM_BURSTS_EXP, num_bursts_exp);
	PUT(u8, BURST_DURATION, burst_duration);
	PUT(u8, FTMS_PER_BURST, fपंचांगs_per_burst);
	PUTOPT(s32, RSSI_AVG, rssi_avg);
	PUTOPT(s32, RSSI_SPREAD, rssi_spपढ़ो);
	अगर (res->fपंचांग.tx_rate_valid &&
	    !nl80211_put_sta_rate(msg, &res->fपंचांग.tx_rate,
				  NL80211_PMSR_FTM_RESP_ATTR_TX_RATE))
		जाओ error;
	अगर (res->fपंचांग.rx_rate_valid &&
	    !nl80211_put_sta_rate(msg, &res->fपंचांग.rx_rate,
				  NL80211_PMSR_FTM_RESP_ATTR_RX_RATE))
		जाओ error;
	PUTOPT_U64(RTT_AVG, rtt_avg);
	PUTOPT_U64(RTT_VARIANCE, rtt_variance);
	PUTOPT_U64(RTT_SPREAD, rtt_spपढ़ो);
	PUTOPT_U64(DIST_AVG, dist_avg);
	PUTOPT_U64(DIST_VARIANCE, dist_variance);
	PUTOPT_U64(DIST_SPREAD, dist_spपढ़ो);
	अगर (res->fपंचांग.lci && res->fपंचांग.lci_len &&
	    nla_put(msg, NL80211_PMSR_FTM_RESP_ATTR_LCI,
		    res->fपंचांग.lci_len, res->fपंचांग.lci))
		जाओ error;
	अगर (res->fपंचांग.civicloc && res->fपंचांग.civicloc_len &&
	    nla_put(msg, NL80211_PMSR_FTM_RESP_ATTR_CIVICLOC,
		    res->fपंचांग.civicloc_len, res->fपंचांग.civicloc))
		जाओ error;
#अघोषित PUT
#अघोषित PUTOPT
#अघोषित PUT_U64
#अघोषित PUTOPT_U64

	वापस 0;
error:
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक nl80211_pmsr_send_result(काष्ठा sk_buff *msg,
				    काष्ठा cfg80211_pmsr_result *res)
अणु
	काष्ठा nlattr *pmsr, *peers, *peer, *resp, *data, *typedata;

	pmsr = nla_nest_start_noflag(msg, NL80211_ATTR_PEER_MEASUREMENTS);
	अगर (!pmsr)
		जाओ error;

	peers = nla_nest_start_noflag(msg, NL80211_PMSR_ATTR_PEERS);
	अगर (!peers)
		जाओ error;

	peer = nla_nest_start_noflag(msg, 1);
	अगर (!peer)
		जाओ error;

	अगर (nla_put(msg, NL80211_PMSR_PEER_ATTR_ADDR, ETH_ALEN, res->addr))
		जाओ error;

	resp = nla_nest_start_noflag(msg, NL80211_PMSR_PEER_ATTR_RESP);
	अगर (!resp)
		जाओ error;

	अगर (nla_put_u32(msg, NL80211_PMSR_RESP_ATTR_STATUS, res->status) ||
	    nla_put_u64_64bit(msg, NL80211_PMSR_RESP_ATTR_HOST_TIME,
			      res->host_समय, NL80211_PMSR_RESP_ATTR_PAD))
		जाओ error;

	अगर (res->ap_tsf_valid &&
	    nla_put_u64_64bit(msg, NL80211_PMSR_RESP_ATTR_AP_TSF,
			      res->ap_tsf, NL80211_PMSR_RESP_ATTR_PAD))
		जाओ error;

	अगर (res->final && nla_put_flag(msg, NL80211_PMSR_RESP_ATTR_FINAL))
		जाओ error;

	data = nla_nest_start_noflag(msg, NL80211_PMSR_RESP_ATTR_DATA);
	अगर (!data)
		जाओ error;

	typedata = nla_nest_start_noflag(msg, res->type);
	अगर (!typedata)
		जाओ error;

	चयन (res->type) अणु
	हाल NL80211_PMSR_TYPE_FTM:
		अगर (nl80211_pmsr_send_fपंचांग_res(msg, res))
			जाओ error;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	nla_nest_end(msg, typedata);
	nla_nest_end(msg, data);
	nla_nest_end(msg, resp);
	nla_nest_end(msg, peer);
	nla_nest_end(msg, peers);
	nla_nest_end(msg, pmsr);

	वापस 0;
error:
	वापस -ENOSPC;
पूर्ण

व्योम cfg80211_pmsr_report(काष्ठा wireless_dev *wdev,
			  काष्ठा cfg80211_pmsr_request *req,
			  काष्ठा cfg80211_pmsr_result *result,
			  gfp_t gfp)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	पूर्णांक err;

	trace_cfg80211_pmsr_report(wdev->wiphy, wdev, req->cookie,
				   result->addr);

	/*
	 * Currently, only variable items are LCI and civic location,
	 * both of which are reasonably लघु so we करोn't need to
	 * worry about them here क्रम the allocation.
	 */
	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_PEER_MEASUREMENT_RESULT);
	अगर (!hdr)
		जाओ मुक्त;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		जाओ मुक्त;

	अगर (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, req->cookie,
			      NL80211_ATTR_PAD))
		जाओ मुक्त;

	err = nl80211_pmsr_send_result(msg, result);
	अगर (err) अणु
		pr_err_ratelimited("peer measurement result: message didn't fit!");
		जाओ मुक्त;
	पूर्ण

	genlmsg_end(msg, hdr);
	genlmsg_unicast(wiphy_net(wdev->wiphy), msg, req->nl_portid);
	वापस;
मुक्त:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL_GPL(cfg80211_pmsr_report);

अटल व्योम cfg80211_pmsr_process_पात(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_pmsr_request *req, *पंचांगp;
	LIST_HEAD(मुक्त_list);

	lockdep_निश्चित_held(&wdev->mtx);

	spin_lock_bh(&wdev->pmsr_lock);
	list_क्रम_each_entry_safe(req, पंचांगp, &wdev->pmsr_list, list) अणु
		अगर (req->nl_portid)
			जारी;
		list_move_tail(&req->list, &मुक्त_list);
	पूर्ण
	spin_unlock_bh(&wdev->pmsr_lock);

	list_क्रम_each_entry_safe(req, पंचांगp, &मुक्त_list, list) अणु
		rdev_पात_pmsr(rdev, wdev, req);

		kमुक्त(req);
	पूर्ण
पूर्ण

व्योम cfg80211_pmsr_मुक्त_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wireless_dev *wdev = container_of(work, काष्ठा wireless_dev,
						 pmsr_मुक्त_wk);

	wdev_lock(wdev);
	cfg80211_pmsr_process_पात(wdev);
	wdev_unlock(wdev);
पूर्ण

व्योम cfg80211_pmsr_wdev_करोwn(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_pmsr_request *req;
	bool found = false;

	spin_lock_bh(&wdev->pmsr_lock);
	list_क्रम_each_entry(req, &wdev->pmsr_list, list) अणु
		found = true;
		req->nl_portid = 0;
	पूर्ण
	spin_unlock_bh(&wdev->pmsr_lock);

	अगर (found)
		cfg80211_pmsr_process_पात(wdev);

	WARN_ON(!list_empty(&wdev->pmsr_list));
पूर्ण

व्योम cfg80211_release_pmsr(काष्ठा wireless_dev *wdev, u32 portid)
अणु
	काष्ठा cfg80211_pmsr_request *req;

	spin_lock_bh(&wdev->pmsr_lock);
	list_क्रम_each_entry(req, &wdev->pmsr_list, list) अणु
		अगर (req->nl_portid == portid) अणु
			req->nl_portid = 0;
			schedule_work(&wdev->pmsr_मुक्त_wk);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&wdev->pmsr_lock);
पूर्ण

#पूर्ण_अगर /* __PMSR_H */
