<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2016 Broadcom
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/gcd.h>
#समावेश <net/cfg80211.h>

#समावेश "core.h"
#समावेश "debug.h"
#समावेश "fwil.h"
#समावेश "fwil_types.h"
#समावेश "cfg80211.h"
#समावेश "pno.h"

#घोषणा BRCMF_PNO_VERSION		2
#घोषणा BRCMF_PNO_REPEAT		4
#घोषणा BRCMF_PNO_FREQ_EXPO_MAX		3
#घोषणा BRCMF_PNO_IMMEDIATE_SCAN_BIT	3
#घोषणा BRCMF_PNO_ENABLE_BD_SCAN_BIT	5
#घोषणा BRCMF_PNO_ENABLE_ADAPTSCAN_BIT	6
#घोषणा BRCMF_PNO_REPORT_SEPARATELY_BIT	11
#घोषणा BRCMF_PNO_SCAN_INCOMPLETE	0
#घोषणा BRCMF_PNO_WPA_AUTH_ANY		0xFFFFFFFF
#घोषणा BRCMF_PNO_HIDDEN_BIT		2
#घोषणा BRCMF_PNO_SCHED_SCAN_PERIOD	30

#घोषणा BRCMF_PNO_MAX_BUCKETS		16
#घोषणा GSCAN_BATCH_NO_THR_SET			101
#घोषणा GSCAN_RETRY_THRESHOLD			3

काष्ठा brcmf_pno_info अणु
	पूर्णांक n_reqs;
	काष्ठा cfg80211_sched_scan_request *reqs[BRCMF_PNO_MAX_BUCKETS];
	काष्ठा mutex req_lock;
पूर्ण;

#घोषणा अगरp_to_pno(_अगरp)	((_अगरp)->drvr->config->pno)

अटल पूर्णांक brcmf_pno_store_request(काष्ठा brcmf_pno_info *pi,
				   काष्ठा cfg80211_sched_scan_request *req)
अणु
	अगर (WARN(pi->n_reqs == BRCMF_PNO_MAX_BUCKETS,
		 "pno request storage full\n"))
		वापस -ENOSPC;

	brcmf_dbg(SCAN, "reqid=%llu\n", req->reqid);
	mutex_lock(&pi->req_lock);
	pi->reqs[pi->n_reqs++] = req;
	mutex_unlock(&pi->req_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_pno_हटाओ_request(काष्ठा brcmf_pno_info *pi, u64 reqid)
अणु
	पूर्णांक i, err = 0;

	mutex_lock(&pi->req_lock);

	/* Nothing to करो अगर we have no requests */
	अगर (pi->n_reqs == 0)
		जाओ करोne;

	/* find request */
	क्रम (i = 0; i < pi->n_reqs; i++) अणु
		अगर (pi->reqs[i]->reqid == reqid)
			अवरोध;
	पूर्ण
	/* request not found */
	अगर (WARN(i == pi->n_reqs, "reqid not found\n")) अणु
		err = -ENOENT;
		जाओ करोne;
	पूर्ण

	brcmf_dbg(SCAN, "reqid=%llu\n", reqid);
	pi->n_reqs--;

	/* अगर last we are करोne */
	अगर (!pi->n_reqs || i == pi->n_reqs)
		जाओ करोne;

	/* fill the gap with reमुख्यing requests */
	जबतक (i <= pi->n_reqs - 1) अणु
		pi->reqs[i] = pi->reqs[i + 1];
		i++;
	पूर्ण

करोne:
	mutex_unlock(&pi->req_lock);
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_pno_channel_config(काष्ठा brcmf_अगर *अगरp,
				    काष्ठा brcmf_pno_config_le *cfg)
अणु
	cfg->reporttype = 0;
	cfg->flags = 0;

	वापस brcmf_fil_iovar_data_set(अगरp, "pfn_cfg", cfg, माप(*cfg));
पूर्ण

अटल पूर्णांक brcmf_pno_config(काष्ठा brcmf_अगर *अगरp, u32 scan_freq,
			    u32 mscan, u32 bestn)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_pno_param_le pfn_param;
	u16 flags;
	u32 pfnmem;
	s32 err;

	स_रखो(&pfn_param, 0, माप(pfn_param));
	pfn_param.version = cpu_to_le32(BRCMF_PNO_VERSION);

	/* set extra pno params */
	flags = BIT(BRCMF_PNO_IMMEDIATE_SCAN_BIT) |
		BIT(BRCMF_PNO_ENABLE_ADAPTSCAN_BIT);
	pfn_param.repeat = BRCMF_PNO_REPEAT;
	pfn_param.exp = BRCMF_PNO_FREQ_EXPO_MAX;

	/* set up pno scan fr */
	pfn_param.scan_freq = cpu_to_le32(scan_freq);

	अगर (mscan) अणु
		pfnmem = bestn;

		/* set bestn in firmware */
		err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "pfnmem", pfnmem);
		अगर (err < 0) अणु
			bphy_err(drvr, "failed to set pfnmem\n");
			जाओ निकास;
		पूर्ण
		/* get max mscan which the firmware supports */
		err = brcmf_fil_iovar_पूर्णांक_get(अगरp, "pfnmem", &pfnmem);
		अगर (err < 0) अणु
			bphy_err(drvr, "failed to get pfnmem\n");
			जाओ निकास;
		पूर्ण
		mscan = min_t(u32, mscan, pfnmem);
		pfn_param.mscan = mscan;
		pfn_param.bestn = bestn;
		flags |= BIT(BRCMF_PNO_ENABLE_BD_SCAN_BIT);
		brcmf_dbg(INFO, "mscan=%d, bestn=%d\n", mscan, bestn);
	पूर्ण

	pfn_param.flags = cpu_to_le16(flags);
	err = brcmf_fil_iovar_data_set(अगरp, "pfn_set", &pfn_param,
				       माप(pfn_param));
	अगर (err)
		bphy_err(drvr, "pfn_set failed, err=%d\n", err);

निकास:
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_pno_set_अक्रमom(काष्ठा brcmf_अगर *अगरp, काष्ठा brcmf_pno_info *pi)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_pno_macaddr_le pfn_mac;
	u8 *mac_addr = शून्य;
	u8 *mac_mask = शून्य;
	पूर्णांक err, i;

	क्रम (i = 0; i < pi->n_reqs; i++)
		अगर (pi->reqs[i]->flags & NL80211_SCAN_FLAG_RANDOM_ADDR) अणु
			mac_addr = pi->reqs[i]->mac_addr;
			mac_mask = pi->reqs[i]->mac_addr_mask;
			अवरोध;
		पूर्ण

	/* no अक्रमom mac requested */
	अगर (!mac_addr)
		वापस 0;

	pfn_mac.version = BRCMF_PFN_MACADDR_CFG_VER;
	pfn_mac.flags = BRCMF_PFN_MAC_OUI_ONLY | BRCMF_PFN_SET_MAC_UNASSOC;

	स_नकल(pfn_mac.mac, mac_addr, ETH_ALEN);
	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		pfn_mac.mac[i] &= mac_mask[i];
		pfn_mac.mac[i] |= get_अक्रमom_पूर्णांक() & ~(mac_mask[i]);
	पूर्ण
	/* Clear multi bit */
	pfn_mac.mac[0] &= 0xFE;
	/* Set locally administered */
	pfn_mac.mac[0] |= 0x02;

	brcmf_dbg(SCAN, "enabling random mac: reqid=%llu mac=%pM\n",
		  pi->reqs[i]->reqid, pfn_mac.mac);
	err = brcmf_fil_iovar_data_set(अगरp, "pfn_macaddr", &pfn_mac,
				       माप(pfn_mac));
	अगर (err)
		bphy_err(drvr, "pfn_macaddr failed, err=%d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक brcmf_pno_add_ssid(काष्ठा brcmf_अगर *अगरp, काष्ठा cfg80211_ssid *ssid,
			      bool active)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_pno_net_param_le pfn;
	पूर्णांक err;

	pfn.auth = cpu_to_le32(WLAN_AUTH_OPEN);
	pfn.wpa_auth = cpu_to_le32(BRCMF_PNO_WPA_AUTH_ANY);
	pfn.wsec = cpu_to_le32(0);
	pfn.infra = cpu_to_le32(1);
	pfn.flags = 0;
	अगर (active)
		pfn.flags = cpu_to_le32(1 << BRCMF_PNO_HIDDEN_BIT);
	pfn.ssid.SSID_len = cpu_to_le32(ssid->ssid_len);
	स_नकल(pfn.ssid.SSID, ssid->ssid, ssid->ssid_len);

	brcmf_dbg(SCAN, "adding ssid=%.32s (active=%d)\n", ssid->ssid, active);
	err = brcmf_fil_iovar_data_set(अगरp, "pfn_add", &pfn, माप(pfn));
	अगर (err < 0)
		bphy_err(drvr, "adding failed: err=%d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_pno_add_bssid(काष्ठा brcmf_अगर *अगरp, स्थिर u8 *bssid)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_pno_bssid_le bssid_cfg;
	पूर्णांक err;

	स_नकल(bssid_cfg.bssid, bssid, ETH_ALEN);
	bssid_cfg.flags = 0;

	brcmf_dbg(SCAN, "adding bssid=%pM\n", bssid);
	err = brcmf_fil_iovar_data_set(अगरp, "pfn_add_bssid", &bssid_cfg,
				       माप(bssid_cfg));
	अगर (err < 0)
		bphy_err(drvr, "adding failed: err=%d\n", err);
	वापस err;
पूर्ण

अटल bool brcmf_is_ssid_active(काष्ठा cfg80211_ssid *ssid,
				 काष्ठा cfg80211_sched_scan_request *req)
अणु
	पूर्णांक i;

	अगर (!ssid || !req->ssids || !req->n_ssids)
		वापस false;

	क्रम (i = 0; i < req->n_ssids; i++) अणु
		अगर (ssid->ssid_len == req->ssids[i].ssid_len) अणु
			अगर (!म_भेदन(ssid->ssid, req->ssids[i].ssid,
				     ssid->ssid_len))
				वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक brcmf_pno_clean(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	पूर्णांक ret;

	/* Disable pfn */
	ret = brcmf_fil_iovar_पूर्णांक_set(अगरp, "pfn", 0);
	अगर (ret == 0) अणु
		/* clear pfn */
		ret = brcmf_fil_iovar_data_set(अगरp, "pfnclear", शून्य, 0);
	पूर्ण
	अगर (ret < 0)
		bphy_err(drvr, "failed code %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक brcmf_pno_get_bucket_channels(काष्ठा cfg80211_sched_scan_request *r,
					 काष्ठा brcmf_pno_config_le *pno_cfg)
अणु
	u32 n_chan = le32_to_cpu(pno_cfg->channel_num);
	u16 chan;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < r->n_channels; i++) अणु
		अगर (n_chan >= BRCMF_NUMCHANNELS) अणु
			err = -ENOSPC;
			जाओ करोne;
		पूर्ण
		chan = r->channels[i]->hw_value;
		brcmf_dbg(SCAN, "[%d] Chan : %u\n", n_chan, chan);
		pno_cfg->channel_list[n_chan++] = cpu_to_le16(chan);
	पूर्ण
	/* वापस number of channels */
	err = n_chan;
करोne:
	pno_cfg->channel_num = cpu_to_le32(n_chan);
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_pno_prep_fwconfig(काष्ठा brcmf_pno_info *pi,
				   काष्ठा brcmf_pno_config_le *pno_cfg,
				   काष्ठा brcmf_gscan_bucket_config **buckets,
				   u32 *scan_freq)
अणु
	काष्ठा cfg80211_sched_scan_request *sr;
	काष्ठा brcmf_gscan_bucket_config *fw_buckets;
	पूर्णांक i, err, chidx;

	brcmf_dbg(SCAN, "n_reqs=%d\n", pi->n_reqs);
	अगर (WARN_ON(!pi->n_reqs))
		वापस -ENODATA;

	/*
	 * actual scan period is determined using gcd() क्रम each
	 * scheduled scan period.
	 */
	*scan_freq = pi->reqs[0]->scan_plans[0].पूर्णांकerval;
	क्रम (i = 1; i < pi->n_reqs; i++) अणु
		sr = pi->reqs[i];
		*scan_freq = gcd(sr->scan_plans[0].पूर्णांकerval, *scan_freq);
	पूर्ण
	अगर (*scan_freq < BRCMF_PNO_SCHED_SCAN_MIN_PERIOD) अणु
		brcmf_dbg(SCAN, "scan period too small, using minimum\n");
		*scan_freq = BRCMF_PNO_SCHED_SCAN_MIN_PERIOD;
	पूर्ण

	*buckets = शून्य;
	fw_buckets = kसुस्मृति(pi->n_reqs, माप(*fw_buckets), GFP_KERNEL);
	अगर (!fw_buckets)
		वापस -ENOMEM;

	स_रखो(pno_cfg, 0, माप(*pno_cfg));
	क्रम (i = 0; i < pi->n_reqs; i++) अणु
		sr = pi->reqs[i];
		chidx = brcmf_pno_get_bucket_channels(sr, pno_cfg);
		अगर (chidx < 0) अणु
			err = chidx;
			जाओ fail;
		पूर्ण
		fw_buckets[i].bucket_end_index = chidx - 1;
		fw_buckets[i].bucket_freq_multiple =
			sr->scan_plans[0].पूर्णांकerval / *scan_freq;
		/* assure period is non-zero */
		अगर (!fw_buckets[i].bucket_freq_multiple)
			fw_buckets[i].bucket_freq_multiple = 1;
		fw_buckets[i].flag = BRCMF_PNO_REPORT_NO_BATCH;
	पूर्ण

	अगर (BRCMF_SCAN_ON()) अणु
		brcmf_err("base period=%u\n", *scan_freq);
		क्रम (i = 0; i < pi->n_reqs; i++) अणु
			brcmf_err("[%d] period %u max %u repeat %u flag %x idx %u\n",
				  i, fw_buckets[i].bucket_freq_multiple,
				  le16_to_cpu(fw_buckets[i].max_freq_multiple),
				  fw_buckets[i].repeat, fw_buckets[i].flag,
				  fw_buckets[i].bucket_end_index);
		पूर्ण
	पूर्ण
	*buckets = fw_buckets;
	वापस pi->n_reqs;

fail:
	kमुक्त(fw_buckets);
	वापस err;
पूर्ण

अटल पूर्णांक brcmf_pno_config_networks(काष्ठा brcmf_अगर *अगरp,
				     काष्ठा brcmf_pno_info *pi)
अणु
	काष्ठा cfg80211_sched_scan_request *r;
	काष्ठा cfg80211_match_set *ms;
	bool active;
	पूर्णांक i, j, err = 0;

	क्रम (i = 0; i < pi->n_reqs; i++) अणु
		r = pi->reqs[i];

		क्रम (j = 0; j < r->n_match_sets; j++) अणु
			ms = &r->match_sets[j];
			अगर (ms->ssid.ssid_len) अणु
				active = brcmf_is_ssid_active(&ms->ssid, r);
				err = brcmf_pno_add_ssid(अगरp, &ms->ssid,
							 active);
			पूर्ण
			अगर (!err && is_valid_ether_addr(ms->bssid))
				err = brcmf_pno_add_bssid(अगरp, ms->bssid);

			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक brcmf_pno_config_sched_scans(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	काष्ठा brcmf_pno_info *pi;
	काष्ठा brcmf_gscan_config *gscan_cfg;
	काष्ठा brcmf_gscan_bucket_config *buckets;
	काष्ठा brcmf_pno_config_le pno_cfg;
	माप_प्रकार gsz;
	u32 scan_freq;
	पूर्णांक err, n_buckets;

	pi = अगरp_to_pno(अगरp);
	n_buckets = brcmf_pno_prep_fwconfig(pi, &pno_cfg, &buckets,
					    &scan_freq);
	अगर (n_buckets < 0)
		वापस n_buckets;

	gsz = माप(*gscan_cfg) + (n_buckets - 1) * माप(*buckets);
	gscan_cfg = kzalloc(gsz, GFP_KERNEL);
	अगर (!gscan_cfg) अणु
		err = -ENOMEM;
		जाओ मुक्त_buckets;
	पूर्ण

	/* clean up everything */
	err = brcmf_pno_clean(अगरp);
	अगर  (err < 0) अणु
		bphy_err(drvr, "failed error=%d\n", err);
		जाओ मुक्त_gscan;
	पूर्ण

	/* configure pno */
	err = brcmf_pno_config(अगरp, scan_freq, 0, 0);
	अगर (err < 0)
		जाओ मुक्त_gscan;

	err = brcmf_pno_channel_config(अगरp, &pno_cfg);
	अगर (err < 0)
		जाओ clean;

	gscan_cfg->version = cpu_to_le16(BRCMF_GSCAN_CFG_VERSION);
	gscan_cfg->retry_threshold = GSCAN_RETRY_THRESHOLD;
	gscan_cfg->buffer_threshold = GSCAN_BATCH_NO_THR_SET;
	gscan_cfg->flags = BRCMF_GSCAN_CFG_ALL_BUCKETS_IN_1ST_SCAN;

	gscan_cfg->count_of_channel_buckets = n_buckets;
	स_नकल(&gscan_cfg->bucket[0], buckets,
	       n_buckets * माप(*buckets));

	err = brcmf_fil_iovar_data_set(अगरp, "pfn_gscan_cfg", gscan_cfg, gsz);

	अगर (err < 0)
		जाओ clean;

	/* configure अक्रमom mac */
	err = brcmf_pno_set_अक्रमom(अगरp, pi);
	अगर (err < 0)
		जाओ clean;

	err = brcmf_pno_config_networks(अगरp, pi);
	अगर (err < 0)
		जाओ clean;

	/* Enable the PNO */
	err = brcmf_fil_iovar_पूर्णांक_set(अगरp, "pfn", 1);

clean:
	अगर (err < 0)
		brcmf_pno_clean(अगरp);
मुक्त_gscan:
	kमुक्त(gscan_cfg);
मुक्त_buckets:
	kमुक्त(buckets);
	वापस err;
पूर्ण

पूर्णांक brcmf_pno_start_sched_scan(काष्ठा brcmf_अगर *अगरp,
			       काष्ठा cfg80211_sched_scan_request *req)
अणु
	काष्ठा brcmf_pno_info *pi;
	पूर्णांक ret;

	brcmf_dbg(TRACE, "reqid=%llu\n", req->reqid);

	pi = अगरp_to_pno(अगरp);
	ret = brcmf_pno_store_request(pi, req);
	अगर (ret < 0)
		वापस ret;

	ret = brcmf_pno_config_sched_scans(अगरp);
	अगर (ret < 0) अणु
		brcmf_pno_हटाओ_request(pi, req->reqid);
		अगर (pi->n_reqs)
			(व्योम)brcmf_pno_config_sched_scans(अगरp);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक brcmf_pno_stop_sched_scan(काष्ठा brcmf_अगर *अगरp, u64 reqid)
अणु
	काष्ठा brcmf_pno_info *pi;
	पूर्णांक err;

	brcmf_dbg(TRACE, "reqid=%llu\n", reqid);

	pi = अगरp_to_pno(अगरp);

	/* No PNO request */
	अगर (!pi->n_reqs)
		वापस 0;

	err = brcmf_pno_हटाओ_request(pi, reqid);
	अगर (err)
		वापस err;

	brcmf_pno_clean(अगरp);

	अगर (pi->n_reqs)
		(व्योम)brcmf_pno_config_sched_scans(अगरp);

	वापस 0;
पूर्ण

पूर्णांक brcmf_pno_attach(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_pno_info *pi;

	brcmf_dbg(TRACE, "enter\n");
	pi = kzalloc(माप(*pi), GFP_KERNEL);
	अगर (!pi)
		वापस -ENOMEM;

	cfg->pno = pi;
	mutex_init(&pi->req_lock);
	वापस 0;
पूर्ण

व्योम brcmf_pno_detach(काष्ठा brcmf_cfg80211_info *cfg)
अणु
	काष्ठा brcmf_pno_info *pi;

	brcmf_dbg(TRACE, "enter\n");
	pi = cfg->pno;
	cfg->pno = शून्य;

	WARN_ON(pi->n_reqs);
	mutex_destroy(&pi->req_lock);
	kमुक्त(pi);
पूर्ण

व्योम brcmf_pno_wiphy_params(काष्ठा wiphy *wiphy, bool gscan)
अणु
	/* scheduled scan settings */
	wiphy->max_sched_scan_reqs = gscan ? BRCMF_PNO_MAX_BUCKETS : 1;
	wiphy->max_sched_scan_ssids = BRCMF_PNO_MAX_PFN_COUNT;
	wiphy->max_match_sets = BRCMF_PNO_MAX_PFN_COUNT;
	wiphy->max_sched_scan_ie_len = BRCMF_SCAN_IE_LEN_MAX;
	wiphy->max_sched_scan_plan_पूर्णांकerval = BRCMF_PNO_SCHED_SCAN_MAX_PERIOD;
पूर्ण

u64 brcmf_pno_find_reqid_by_bucket(काष्ठा brcmf_pno_info *pi, u32 bucket)
अणु
	u64 reqid = 0;

	mutex_lock(&pi->req_lock);

	अगर (bucket < pi->n_reqs)
		reqid = pi->reqs[bucket]->reqid;

	mutex_unlock(&pi->req_lock);
	वापस reqid;
पूर्ण

u32 brcmf_pno_get_bucket_map(काष्ठा brcmf_pno_info *pi,
			     काष्ठा brcmf_pno_net_info_le *ni)
अणु
	काष्ठा cfg80211_sched_scan_request *req;
	काष्ठा cfg80211_match_set *ms;
	u32 bucket_map = 0;
	पूर्णांक i, j;

	mutex_lock(&pi->req_lock);
	क्रम (i = 0; i < pi->n_reqs; i++) अणु
		req = pi->reqs[i];

		अगर (!req->n_match_sets)
			जारी;
		क्रम (j = 0; j < req->n_match_sets; j++) अणु
			ms = &req->match_sets[j];
			अगर (ms->ssid.ssid_len == ni->SSID_len &&
			    !स_भेद(ms->ssid.ssid, ni->SSID, ni->SSID_len)) अणु
				bucket_map |= BIT(i);
				अवरोध;
			पूर्ण
			अगर (is_valid_ether_addr(ms->bssid) &&
			    !स_भेद(ms->bssid, ni->bssid, ETH_ALEN)) अणु
				bucket_map |= BIT(i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&pi->req_lock);
	वापस bucket_map;
पूर्ण
