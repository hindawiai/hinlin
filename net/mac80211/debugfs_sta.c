<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2003-2005	Devicescape Software, Inc.
 * Copyright (c) 2006	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright(c) 2016 Intel Deutschland GmbH
 * Copyright (C) 2018 - 2020 Intel Corporation
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/ieee80211.h>
#समावेश "ieee80211_i.h"
#समावेश "debugfs.h"
#समावेश "debugfs_sta.h"
#समावेश "sta_info.h"
#समावेश "driver-ops.h"

/* sta attributtes */

#घोषणा STA_READ(name, field, क्रमmat_string)				\
अटल sमाप_प्रकार sta_ ##name## _पढ़ो(काष्ठा file *file,			\
				   अक्षर __user *userbuf,		\
				   माप_प्रकार count, loff_t *ppos)		\
अणु									\
	काष्ठा sta_info *sta = file->निजी_data;			\
	वापस mac80211_क्रमmat_buffer(userbuf, count, ppos, 		\
				      क्रमmat_string, sta->field);	\
पूर्ण
#घोषणा STA_READ_D(name, field) STA_READ(name, field, "%d\n")

#घोषणा STA_OPS(name)							\
अटल स्थिर काष्ठा file_operations sta_ ##name## _ops = अणु		\
	.पढ़ो = sta_##name##_पढ़ो,					\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण

#घोषणा STA_OPS_RW(name)						\
अटल स्थिर काष्ठा file_operations sta_ ##name## _ops = अणु		\
	.पढ़ो = sta_##name##_पढ़ो,					\
	.ग_लिखो = sta_##name##_ग_लिखो,					\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण

#घोषणा STA_खाता(name, field, क्रमmat)					\
		STA_READ_##क्रमmat(name, field)				\
		STA_OPS(name)

STA_खाता(aid, sta.aid, D);

अटल स्थिर अक्षर * स्थिर sta_flag_names[] = अणु
#घोषणा FLAG(F) [WLAN_STA_##F] = #F
	FLAG(AUTH),
	FLAG(ASSOC),
	FLAG(PS_STA),
	FLAG(AUTHORIZED),
	FLAG(SHORT_PREAMBLE),
	FLAG(WDS),
	FLAG(CLEAR_PS_FILT),
	FLAG(MFP),
	FLAG(BLOCK_BA),
	FLAG(PS_DRIVER),
	FLAG(PSPOLL),
	FLAG(TDLS_PEER),
	FLAG(TDLS_PEER_AUTH),
	FLAG(TDLS_INITIATOR),
	FLAG(TDLS_CHAN_SWITCH),
	FLAG(TDLS_OFF_CHANNEL),
	FLAG(TDLS_WIDER_BW),
	FLAG(UAPSD),
	FLAG(SP),
	FLAG(4ADDR_EVENT),
	FLAG(INSERTED),
	FLAG(RATE_CONTROL),
	FLAG(TOFFSET_KNOWN),
	FLAG(MPSP_OWNER),
	FLAG(MPSP_RECIPIENT),
	FLAG(PS_DELIVER),
	FLAG(USES_ENCRYPTION),
	FLAG(DECAP_OFFLOAD),
#अघोषित FLAG
पूर्ण;

अटल sमाप_प्रकार sta_flags_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[16 * NUM_WLAN_STA_FLAGS], *pos = buf;
	अक्षर *end = buf + माप(buf) - 1;
	काष्ठा sta_info *sta = file->निजी_data;
	अचिन्हित पूर्णांक flg;

	BUILD_BUG_ON(ARRAY_SIZE(sta_flag_names) != NUM_WLAN_STA_FLAGS);

	क्रम (flg = 0; flg < NUM_WLAN_STA_FLAGS; flg++) अणु
		अगर (test_sta_flag(sta, flg))
			pos += scnम_लिखो(pos, end - pos, "%s\n",
					 sta_flag_names[flg]);
	पूर्ण

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, म_माप(buf));
पूर्ण
STA_OPS(flags);

अटल sमाप_प्रकार sta_num_ps_buf_frames_पढ़ो(काष्ठा file *file,
					  अक्षर __user *userbuf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sta_info *sta = file->निजी_data;
	अक्षर buf[17*IEEE80211_NUM_ACS], *p = buf;
	पूर्णांक ac;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		p += scnम_लिखो(p, माप(buf)+buf-p, "AC%d: %d\n", ac,
			       skb_queue_len(&sta->ps_tx_buf[ac]) +
			       skb_queue_len(&sta->tx_filtered[ac]));
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
पूर्ण
STA_OPS(num_ps_buf_frames);

अटल sमाप_प्रकार sta_last_seq_ctrl_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[15*IEEE80211_NUM_TIDS], *p = buf;
	पूर्णांक i;
	काष्ठा sta_info *sta = file->निजी_data;
	क्रम (i = 0; i < IEEE80211_NUM_TIDS; i++)
		p += scnम_लिखो(p, माप(buf)+buf-p, "%x ",
			       le16_to_cpu(sta->last_seq_ctrl[i]));
	p += scnम_लिखो(p, माप(buf)+buf-p, "\n");
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
पूर्ण
STA_OPS(last_seq_ctrl);

#घोषणा AQM_TXQ_ENTRY_LEN 130

अटल sमाप_प्रकार sta_aqm_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sta_info *sta = file->निजी_data;
	काष्ठा ieee80211_local *local = sta->local;
	माप_प्रकार bufsz = AQM_TXQ_ENTRY_LEN * (IEEE80211_NUM_TIDS + 2);
	अक्षर *buf = kzalloc(bufsz, GFP_KERNEL), *p = buf;
	काष्ठा txq_info *txqi;
	sमाप_प्रकार rv;
	पूर्णांक i;

	अगर (!buf)
		वापस -ENOMEM;

	spin_lock_bh(&local->fq.lock);
	rcu_पढ़ो_lock();

	p += scnम_लिखो(p,
		       bufsz+buf-p,
		       "target %uus interval %uus ecn %s\n",
		       codel_समय_प्रकारo_us(sta->cparams.target),
		       codel_समय_प्रकारo_us(sta->cparams.पूर्णांकerval),
		       sta->cparams.ecn ? "yes" : "no");
	p += scnम_लिखो(p,
		       bufsz+buf-p,
		       "tid ac backlog-bytes backlog-packets new-flows drops marks overlimit collisions tx-bytes tx-packets flags\n");

	क्रम (i = 0; i < ARRAY_SIZE(sta->sta.txq); i++) अणु
		अगर (!sta->sta.txq[i])
			जारी;
		txqi = to_txq_info(sta->sta.txq[i]);
		p += scnम_लिखो(p, bufsz+buf-p,
			       "%d %d %u %u %u %u %u %u %u %u %u 0x%lx(%s%s%s)\n",
			       txqi->txq.tid,
			       txqi->txq.ac,
			       txqi->tin.backlog_bytes,
			       txqi->tin.backlog_packets,
			       txqi->tin.flows,
			       txqi->cstats.drop_count,
			       txqi->cstats.ecn_mark,
			       txqi->tin.overlimit,
			       txqi->tin.collisions,
			       txqi->tin.tx_bytes,
			       txqi->tin.tx_packets,
			       txqi->flags,
			       test_bit(IEEE80211_TXQ_STOP, &txqi->flags) ? "STOP" : "RUN",
			       test_bit(IEEE80211_TXQ_AMPDU, &txqi->flags) ? " AMPDU" : "",
			       test_bit(IEEE80211_TXQ_NO_AMSDU, &txqi->flags) ? " NO-AMSDU" : "");
	पूर्ण

	rcu_पढ़ो_unlock();
	spin_unlock_bh(&local->fq.lock);

	rv = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
	kमुक्त(buf);
	वापस rv;
पूर्ण
STA_OPS(aqm);

अटल sमाप_प्रकार sta_airसमय_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sta_info *sta = file->निजी_data;
	काष्ठा ieee80211_local *local = sta->sdata->local;
	माप_प्रकार bufsz = 400;
	अक्षर *buf = kzalloc(bufsz, GFP_KERNEL), *p = buf;
	u64 rx_airसमय = 0, tx_airसमय = 0;
	s64 deficit[IEEE80211_NUM_ACS];
	sमाप_प्रकार rv;
	पूर्णांक ac;

	अगर (!buf)
		वापस -ENOMEM;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		spin_lock_bh(&local->active_txq_lock[ac]);
		rx_airसमय += sta->airसमय[ac].rx_airसमय;
		tx_airसमय += sta->airसमय[ac].tx_airसमय;
		deficit[ac] = sta->airसमय[ac].deficit;
		spin_unlock_bh(&local->active_txq_lock[ac]);
	पूर्ण

	p += scnम_लिखो(p, bufsz + buf - p,
		"RX: %llu us\nTX: %llu us\nWeight: %u\n"
		"Deficit: VO: %lld us VI: %lld us BE: %lld us BK: %lld us\n",
		rx_airसमय, tx_airसमय, sta->airसमय_weight,
		deficit[0], deficit[1], deficit[2], deficit[3]);

	rv = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
	kमुक्त(buf);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार sta_airसमय_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sta_info *sta = file->निजी_data;
	काष्ठा ieee80211_local *local = sta->sdata->local;
	पूर्णांक ac;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		spin_lock_bh(&local->active_txq_lock[ac]);
		sta->airसमय[ac].rx_airसमय = 0;
		sta->airसमय[ac].tx_airसमय = 0;
		sta->airसमय[ac].deficit = sta->airसमय_weight;
		spin_unlock_bh(&local->active_txq_lock[ac]);
	पूर्ण

	वापस count;
पूर्ण
STA_OPS_RW(airसमय);

अटल sमाप_प्रकार sta_aql_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sta_info *sta = file->निजी_data;
	काष्ठा ieee80211_local *local = sta->sdata->local;
	माप_प्रकार bufsz = 400;
	अक्षर *buf = kzalloc(bufsz, GFP_KERNEL), *p = buf;
	u32 q_depth[IEEE80211_NUM_ACS];
	u32 q_limit_l[IEEE80211_NUM_ACS], q_limit_h[IEEE80211_NUM_ACS];
	sमाप_प्रकार rv;
	पूर्णांक ac;

	अगर (!buf)
		वापस -ENOMEM;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		spin_lock_bh(&local->active_txq_lock[ac]);
		q_limit_l[ac] = sta->airसमय[ac].aql_limit_low;
		q_limit_h[ac] = sta->airसमय[ac].aql_limit_high;
		spin_unlock_bh(&local->active_txq_lock[ac]);
		q_depth[ac] = atomic_पढ़ो(&sta->airसमय[ac].aql_tx_pending);
	पूर्ण

	p += scnम_लिखो(p, bufsz + buf - p,
		"Q depth: VO: %u us VI: %u us BE: %u us BK: %u us\n"
		"Q limit[low/high]: VO: %u/%u VI: %u/%u BE: %u/%u BK: %u/%u\n",
		q_depth[0], q_depth[1], q_depth[2], q_depth[3],
		q_limit_l[0], q_limit_h[0], q_limit_l[1], q_limit_h[1],
		q_limit_l[2], q_limit_h[2], q_limit_l[3], q_limit_h[3]);

	rv = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
	kमुक्त(buf);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार sta_aql_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा sta_info *sta = file->निजी_data;
	u32 ac, q_limit_l, q_limit_h;
	अक्षर _buf[100] = अणुपूर्ण, *buf = _buf;

	अगर (count > माप(_buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[माप(_buf) - 1] = '\0';
	अगर (माला_पूछो(buf, "limit %u %u %u", &ac, &q_limit_l, &q_limit_h)
	    != 3)
		वापस -EINVAL;

	अगर (ac >= IEEE80211_NUM_ACS)
		वापस -EINVAL;

	sta->airसमय[ac].aql_limit_low = q_limit_l;
	sta->airसमय[ac].aql_limit_high = q_limit_h;

	वापस count;
पूर्ण
STA_OPS_RW(aql);


अटल sमाप_प्रकार sta_agg_status_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
					माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[71 + IEEE80211_NUM_TIDS * 40], *p = buf;
	पूर्णांक i;
	काष्ठा sta_info *sta = file->निजी_data;
	काष्ठा tid_ampdu_rx *tid_rx;
	काष्ठा tid_ampdu_tx *tid_tx;

	rcu_पढ़ो_lock();

	p += scnम_लिखो(p, माप(buf) + buf - p, "next dialog_token: %#02x\n",
			sta->ampdu_mlme.dialog_token_allocator + 1);
	p += scnम_लिखो(p, माप(buf) + buf - p,
		       "TID\t\tRX\tDTKN\tSSN\t\tTX\tDTKN\tpending\n");

	क्रम (i = 0; i < IEEE80211_NUM_TIDS; i++) अणु
		bool tid_rx_valid;

		tid_rx = rcu_dereference(sta->ampdu_mlme.tid_rx[i]);
		tid_tx = rcu_dereference(sta->ampdu_mlme.tid_tx[i]);
		tid_rx_valid = test_bit(i, sta->ampdu_mlme.agg_session_valid);

		p += scnम_लिखो(p, माप(buf) + buf - p, "%02d", i);
		p += scnम_लिखो(p, माप(buf) + buf - p, "\t\t%x",
			       tid_rx_valid);
		p += scnम_लिखो(p, माप(buf) + buf - p, "\t%#.2x",
			       tid_rx_valid ?
					sta->ampdu_mlme.tid_rx_token[i] : 0);
		p += scnम_लिखो(p, माप(buf) + buf - p, "\t%#.3x",
				tid_rx ? tid_rx->ssn : 0);

		p += scnम_लिखो(p, माप(buf) + buf - p, "\t\t%x", !!tid_tx);
		p += scnम_लिखो(p, माप(buf) + buf - p, "\t%#.2x",
				tid_tx ? tid_tx->dialog_token : 0);
		p += scnम_लिखो(p, माप(buf) + buf - p, "\t%03d",
				tid_tx ? skb_queue_len(&tid_tx->pending) : 0);
		p += scnम_लिखो(p, माप(buf) + buf - p, "\n");
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
पूर्ण

अटल sमाप_प्रकार sta_agg_status_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर _buf[25] = अणुपूर्ण, *buf = _buf;
	काष्ठा sta_info *sta = file->निजी_data;
	bool start, tx;
	अचिन्हित दीर्घ tid;
	अक्षर *pos;
	पूर्णांक ret, समयout = 5000;

	अगर (count > माप(_buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;

	buf[माप(_buf) - 1] = '\0';
	pos = buf;
	buf = strsep(&pos, " ");
	अगर (!buf)
		वापस -EINVAL;

	अगर (!म_भेद(buf, "tx"))
		tx = true;
	अन्यथा अगर (!म_भेद(buf, "rx"))
		tx = false;
	अन्यथा
		वापस -EINVAL;

	buf = strsep(&pos, " ");
	अगर (!buf)
		वापस -EINVAL;
	अगर (!म_भेद(buf, "start")) अणु
		start = true;
		अगर (!tx)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (!म_भेद(buf, "stop")) अणु
		start = false;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	buf = strsep(&pos, " ");
	अगर (!buf)
		वापस -EINVAL;
	अगर (माला_पूछो(buf, "timeout=%d", &समयout) == 1) अणु
		buf = strsep(&pos, " ");
		अगर (!buf || !tx || !start)
			वापस -EINVAL;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 0, &tid);
	अगर (ret || tid >= IEEE80211_NUM_TIDS)
		वापस -EINVAL;

	अगर (tx) अणु
		अगर (start)
			ret = ieee80211_start_tx_ba_session(&sta->sta, tid,
							    समयout);
		अन्यथा
			ret = ieee80211_stop_tx_ba_session(&sta->sta, tid);
	पूर्ण अन्यथा अणु
		__ieee80211_stop_rx_ba_session(sta, tid, WLAN_BACK_RECIPIENT,
					       3, true);
		ret = 0;
	पूर्ण

	वापस ret ?: count;
पूर्ण
STA_OPS_RW(agg_status);

अटल sमाप_प्रकार sta_ht_capa_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
#घोषणा PRINT_HT_CAP(_cond, _str) \
	करो अणु \
	अगर (_cond) \
			p += scnम_लिखो(p, माप(buf)+buf-p, "\t" _str "\n"); \
	पूर्ण जबतक (0)
	अक्षर buf[512], *p = buf;
	पूर्णांक i;
	काष्ठा sta_info *sta = file->निजी_data;
	काष्ठा ieee80211_sta_ht_cap *htc = &sta->sta.ht_cap;

	p += scnम_लिखो(p, माप(buf) + buf - p, "ht %ssupported\n",
			htc->ht_supported ? "" : "not ");
	अगर (htc->ht_supported) अणु
		p += scnम_लिखो(p, माप(buf)+buf-p, "cap: %#.4x\n", htc->cap);

		PRINT_HT_CAP((htc->cap & BIT(0)), "RX LDPC");
		PRINT_HT_CAP((htc->cap & BIT(1)), "HT20/HT40");
		PRINT_HT_CAP(!(htc->cap & BIT(1)), "HT20");

		PRINT_HT_CAP(((htc->cap >> 2) & 0x3) == 0, "Static SM Power Save");
		PRINT_HT_CAP(((htc->cap >> 2) & 0x3) == 1, "Dynamic SM Power Save");
		PRINT_HT_CAP(((htc->cap >> 2) & 0x3) == 3, "SM Power Save disabled");

		PRINT_HT_CAP((htc->cap & BIT(4)), "RX Greenfield");
		PRINT_HT_CAP((htc->cap & BIT(5)), "RX HT20 SGI");
		PRINT_HT_CAP((htc->cap & BIT(6)), "RX HT40 SGI");
		PRINT_HT_CAP((htc->cap & BIT(7)), "TX STBC");

		PRINT_HT_CAP(((htc->cap >> 8) & 0x3) == 0, "No RX STBC");
		PRINT_HT_CAP(((htc->cap >> 8) & 0x3) == 1, "RX STBC 1-stream");
		PRINT_HT_CAP(((htc->cap >> 8) & 0x3) == 2, "RX STBC 2-streams");
		PRINT_HT_CAP(((htc->cap >> 8) & 0x3) == 3, "RX STBC 3-streams");

		PRINT_HT_CAP((htc->cap & BIT(10)), "HT Delayed Block Ack");

		PRINT_HT_CAP(!(htc->cap & BIT(11)), "Max AMSDU length: "
			     "3839 bytes");
		PRINT_HT_CAP((htc->cap & BIT(11)), "Max AMSDU length: "
			     "7935 bytes");

		/*
		 * For beacons and probe response this would mean the BSS
		 * करोes or करोes not allow the usage of DSSS/CCK HT40.
		 * Otherwise it means the STA करोes or करोes not use
		 * DSSS/CCK HT40.
		 */
		PRINT_HT_CAP((htc->cap & BIT(12)), "DSSS/CCK HT40");
		PRINT_HT_CAP(!(htc->cap & BIT(12)), "No DSSS/CCK HT40");

		/* BIT(13) is reserved */

		PRINT_HT_CAP((htc->cap & BIT(14)), "40 MHz Intolerant");

		PRINT_HT_CAP((htc->cap & BIT(15)), "L-SIG TXOP protection");

		p += scnम_लिखो(p, माप(buf)+buf-p, "ampdu factor/density: %d/%d\n",
				htc->ampdu_factor, htc->ampdu_density);
		p += scnम_लिखो(p, माप(buf)+buf-p, "MCS mask:");

		क्रम (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++)
			p += scnम_लिखो(p, माप(buf)+buf-p, " %.2x",
					htc->mcs.rx_mask[i]);
		p += scnम_लिखो(p, माप(buf)+buf-p, "\n");

		/* If not set this is meaningless */
		अगर (le16_to_cpu(htc->mcs.rx_highest)) अणु
			p += scnम_लिखो(p, माप(buf)+buf-p,
				       "MCS rx highest: %d Mbps\n",
				       le16_to_cpu(htc->mcs.rx_highest));
		पूर्ण

		p += scnम_लिखो(p, माप(buf)+buf-p, "MCS tx params: %x\n",
				htc->mcs.tx_params);
	पूर्ण

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
पूर्ण
STA_OPS(ht_capa);

अटल sमाप_प्रकार sta_vht_capa_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[512], *p = buf;
	काष्ठा sta_info *sta = file->निजी_data;
	काष्ठा ieee80211_sta_vht_cap *vhtc = &sta->sta.vht_cap;

	p += scnम_लिखो(p, माप(buf) + buf - p, "VHT %ssupported\n",
			vhtc->vht_supported ? "" : "not ");
	अगर (vhtc->vht_supported) अणु
		p += scnम_लिखो(p, माप(buf) + buf - p, "cap: %#.8x\n",
			       vhtc->cap);
#घोषणा PFLAG(a, b)							\
		करो अणु							\
			अगर (vhtc->cap & IEEE80211_VHT_CAP_ ## a)	\
				p += scnम_लिखो(p, माप(buf) + buf - p, \
					       "\t\t%s\n", b);		\
		पूर्ण जबतक (0)

		चयन (vhtc->cap & 0x3) अणु
		हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895:
			p += scnम_लिखो(p, माप(buf) + buf - p,
				       "\t\tMAX-MPDU-3895\n");
			अवरोध;
		हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991:
			p += scnम_लिखो(p, माप(buf) + buf - p,
				       "\t\tMAX-MPDU-7991\n");
			अवरोध;
		हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454:
			p += scnम_लिखो(p, माप(buf) + buf - p,
				       "\t\tMAX-MPDU-11454\n");
			अवरोध;
		शेष:
			p += scnम_लिखो(p, माप(buf) + buf - p,
				       "\t\tMAX-MPDU-UNKNOWN\n");
		पूर्ण
		चयन (vhtc->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK) अणु
		हाल 0:
			p += scnम_लिखो(p, माप(buf) + buf - p,
				       "\t\t80Mhz\n");
			अवरोध;
		हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ:
			p += scnम_लिखो(p, माप(buf) + buf - p,
				       "\t\t160Mhz\n");
			अवरोध;
		हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ:
			p += scnम_लिखो(p, माप(buf) + buf - p,
				       "\t\t80+80Mhz\n");
			अवरोध;
		शेष:
			p += scnम_लिखो(p, माप(buf) + buf - p,
				       "\t\tUNKNOWN-MHZ: 0x%x\n",
				       (vhtc->cap >> 2) & 0x3);
		पूर्ण
		PFLAG(RXLDPC, "RXLDPC");
		PFLAG(SHORT_GI_80, "SHORT-GI-80");
		PFLAG(SHORT_GI_160, "SHORT-GI-160");
		PFLAG(TXSTBC, "TXSTBC");
		p += scnम_लिखो(p, माप(buf) + buf - p,
			       "\t\tRXSTBC_%d\n", (vhtc->cap >> 8) & 0x7);
		PFLAG(SU_BEAMFORMER_CAPABLE, "SU-BEAMFORMER-CAPABLE");
		PFLAG(SU_BEAMFORMEE_CAPABLE, "SU-BEAMFORMEE-CAPABLE");
		p += scnम_लिखो(p, माप(buf) + buf - p,
			"\t\tBEAMFORMEE-STS: 0x%x\n",
			(vhtc->cap & IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK) >>
			IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT);
		p += scnम_लिखो(p, माप(buf) + buf - p,
			"\t\tSOUNDING-DIMENSIONS: 0x%x\n",
			(vhtc->cap & IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK)
			>> IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT);
		PFLAG(MU_BEAMFORMER_CAPABLE, "MU-BEAMFORMER-CAPABLE");
		PFLAG(MU_BEAMFORMEE_CAPABLE, "MU-BEAMFORMEE-CAPABLE");
		PFLAG(VHT_TXOP_PS, "TXOP-PS");
		PFLAG(HTC_VHT, "HTC-VHT");
		p += scnम_लिखो(p, माप(buf) + buf - p,
			"\t\tMPDU-LENGTH-EXPONENT: 0x%x\n",
			(vhtc->cap & IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK) >>
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT);
		PFLAG(VHT_LINK_ADAPTATION_VHT_UNSOL_MFB,
		      "LINK-ADAPTATION-VHT-UNSOL-MFB");
		p += scnम_लिखो(p, माप(buf) + buf - p,
			"\t\tLINK-ADAPTATION-VHT-MRQ-MFB: 0x%x\n",
			(vhtc->cap & IEEE80211_VHT_CAP_VHT_LINK_ADAPTATION_VHT_MRQ_MFB) >> 26);
		PFLAG(RX_ANTENNA_PATTERN, "RX-ANTENNA-PATTERN");
		PFLAG(TX_ANTENNA_PATTERN, "TX-ANTENNA-PATTERN");

		p += scnम_लिखो(p, माप(buf)+buf-p, "RX MCS: %.4x\n",
			       le16_to_cpu(vhtc->vht_mcs.rx_mcs_map));
		अगर (vhtc->vht_mcs.rx_highest)
			p += scnम_लिखो(p, माप(buf)+buf-p,
				       "MCS RX highest: %d Mbps\n",
				       le16_to_cpu(vhtc->vht_mcs.rx_highest));
		p += scnम_लिखो(p, माप(buf)+buf-p, "TX MCS: %.4x\n",
			       le16_to_cpu(vhtc->vht_mcs.tx_mcs_map));
		अगर (vhtc->vht_mcs.tx_highest)
			p += scnम_लिखो(p, माप(buf)+buf-p,
				       "MCS TX highest: %d Mbps\n",
				       le16_to_cpu(vhtc->vht_mcs.tx_highest));
#अघोषित PFLAG
	पूर्ण

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
पूर्ण
STA_OPS(vht_capa);

अटल sमाप_प्रकार sta_he_capa_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *buf, *p;
	माप_प्रकार buf_sz = PAGE_SIZE;
	काष्ठा sta_info *sta = file->निजी_data;
	काष्ठा ieee80211_sta_he_cap *hec = &sta->sta.he_cap;
	काष्ठा ieee80211_he_mcs_nss_supp *nss = &hec->he_mcs_nss_supp;
	u8 ppe_size;
	u8 *cap;
	पूर्णांक i;
	sमाप_प्रकार ret;

	buf = kदो_स्मृति(buf_sz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	p = buf;

	p += scnम_लिखो(p, buf_sz + buf - p, "HE %ssupported\n",
		       hec->has_he ? "" : "not ");
	अगर (!hec->has_he)
		जाओ out;

	cap = hec->he_cap_elem.mac_cap_info;
	p += scnम_लिखो(p, buf_sz + buf - p,
		       "MAC-CAP: %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x\n",
		       cap[0], cap[1], cap[2], cap[3], cap[4], cap[5]);

#घोषणा PRINT(fmt, ...)							\
	p += scnम_लिखो(p, buf_sz + buf - p, "\t\t" fmt "\n",		\
		       ##__VA_ARGS__)

#घोषणा PFLAG(t, n, a, b)						\
	करो अणु								\
		अगर (cap[n] & IEEE80211_HE_##t##_CAP##n##_##a)		\
			PRINT("%s", b);					\
	पूर्ण जबतक (0)

#घोषणा PFLAG_RANGE(t, i, n, s, m, off, fmt)				\
	करो अणु								\
		u8 msk = IEEE80211_HE_##t##_CAP##i##_##n##_MASK;	\
		u8 idx = ((cap[i] & msk) >> (ffs(msk) - 1)) + off;	\
		PRINT(fmt, (s << idx) + (m * idx));			\
	पूर्ण जबतक (0)

#घोषणा PFLAG_RANGE_DEFAULT(t, i, n, s, m, off, fmt, a, b)		\
	करो अणु								\
		अगर (cap[i] == IEEE80211_HE_##t ##_CAP##i##_##n##_##a) अणु	\
			PRINT("%s", b);					\
			अवरोध;						\
		पूर्ण							\
		PFLAG_RANGE(t, i, n, s, m, off, fmt);			\
	पूर्ण जबतक (0)

	PFLAG(MAC, 0, HTC_HE, "HTC-HE");
	PFLAG(MAC, 0, TWT_REQ, "TWT-REQ");
	PFLAG(MAC, 0, TWT_RES, "TWT-RES");
	PFLAG_RANGE_DEFAULT(MAC, 0, DYNAMIC_FRAG, 0, 1, 0,
			    "DYNAMIC-FRAG-LEVEL-%d", NOT_SUPP, "NOT-SUPP");
	PFLAG_RANGE_DEFAULT(MAC, 0, MAX_NUM_FRAG_MSDU, 1, 0, 0,
			    "MAX-NUM-FRAG-MSDU-%d", UNLIMITED, "UNLIMITED");

	PFLAG_RANGE_DEFAULT(MAC, 1, MIN_FRAG_SIZE, 128, 0, -1,
			    "MIN-FRAG-SIZE-%d", UNLIMITED, "UNLIMITED");
	PFLAG_RANGE_DEFAULT(MAC, 1, TF_MAC_PAD_DUR, 0, 8, 0,
			    "TF-MAC-PAD-DUR-%dUS", MASK, "UNKNOWN");
	PFLAG_RANGE(MAC, 1, MULTI_TID_AGG_RX_QOS, 0, 1, 1,
		    "MULTI-TID-AGG-RX-QOS-%d");

	अगर (cap[0] & IEEE80211_HE_MAC_CAP0_HTC_HE) अणु
		चयन (((cap[2] << 1) | (cap[1] >> 7)) & 0x3) अणु
		हाल 0:
			PRINT("LINK-ADAPTATION-NO-FEEDBACK");
			अवरोध;
		हाल 1:
			PRINT("LINK-ADAPTATION-RESERVED");
			अवरोध;
		हाल 2:
			PRINT("LINK-ADAPTATION-UNSOLICITED-FEEDBACK");
			अवरोध;
		हाल 3:
			PRINT("LINK-ADAPTATION-BOTH");
			अवरोध;
		पूर्ण
	पूर्ण

	PFLAG(MAC, 2, ALL_ACK, "ALL-ACK");
	PFLAG(MAC, 2, TRS, "TRS");
	PFLAG(MAC, 2, BSR, "BSR");
	PFLAG(MAC, 2, BCAST_TWT, "BCAST-TWT");
	PFLAG(MAC, 2, 32BIT_BA_BITMAP, "32BIT-BA-BITMAP");
	PFLAG(MAC, 2, MU_CASCADING, "MU-CASCADING");
	PFLAG(MAC, 2, ACK_EN, "ACK-EN");

	PFLAG(MAC, 3, OMI_CONTROL, "OMI-CONTROL");
	PFLAG(MAC, 3, OFDMA_RA, "OFDMA-RA");

	चयन (cap[3] & IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_MASK) अणु
	हाल IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_0:
		PRINT("MAX-AMPDU-LEN-EXP-USE-EXT-0");
		अवरोध;
	हाल IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_1:
		PRINT("MAX-AMPDU-LEN-EXP-VHT-EXT-1");
		अवरोध;
	हाल IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_2:
		PRINT("MAX-AMPDU-LEN-EXP-VHT-EXT-2");
		अवरोध;
	हाल IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_3:
		PRINT("MAX-AMPDU-LEN-EXP-VHT-EXT-3");
		अवरोध;
	पूर्ण

	PFLAG(MAC, 3, AMSDU_FRAG, "AMSDU-FRAG");
	PFLAG(MAC, 3, FLEX_TWT_SCHED, "FLEX-TWT-SCHED");
	PFLAG(MAC, 3, RX_CTRL_FRAME_TO_MULTIBSS, "RX-CTRL-FRAME-TO-MULTIBSS");

	PFLAG(MAC, 4, BSRP_BQRP_A_MPDU_AGG, "BSRP-BQRP-A-MPDU-AGG");
	PFLAG(MAC, 4, QTP, "QTP");
	PFLAG(MAC, 4, BQR, "BQR");
	PFLAG(MAC, 4, PSR_RESP, "PSR-RESP");
	PFLAG(MAC, 4, NDP_FB_REP, "NDP-FB-REP");
	PFLAG(MAC, 4, OPS, "OPS");
	PFLAG(MAC, 4, AMSDU_IN_AMPDU, "AMSDU-IN-AMPDU");

	PRINT("MULTI-TID-AGG-TX-QOS-%d", ((cap[5] << 1) | (cap[4] >> 7)) & 0x7);

	PFLAG(MAC, 5, SUBCHAN_SELECTIVE_TRANSMISSION,
	      "SUBCHAN-SELECTIVE-TRANSMISSION");
	PFLAG(MAC, 5, UL_2x996_TONE_RU, "UL-2x996-TONE-RU");
	PFLAG(MAC, 5, OM_CTRL_UL_MU_DATA_DIS_RX, "OM-CTRL-UL-MU-DATA-DIS-RX");
	PFLAG(MAC, 5, HE_DYNAMIC_SM_PS, "HE-DYNAMIC-SM-PS");
	PFLAG(MAC, 5, PUNCTURED_SOUNDING, "PUNCTURED-SOUNDING");
	PFLAG(MAC, 5, HT_VHT_TRIG_FRAME_RX, "HT-VHT-TRIG-FRAME-RX");

	cap = hec->he_cap_elem.phy_cap_info;
	p += scnम_लिखो(p, buf_sz + buf - p,
		       "PHY CAP: %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x %#.2x\n",
		       cap[0], cap[1], cap[2], cap[3], cap[4], cap[5], cap[6],
		       cap[7], cap[8], cap[9], cap[10]);

	PFLAG(PHY, 0, CHANNEL_WIDTH_SET_40MHZ_IN_2G,
	      "CHANNEL-WIDTH-SET-40MHZ-IN-2G");
	PFLAG(PHY, 0, CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G,
	      "CHANNEL-WIDTH-SET-40MHZ-80MHZ-IN-5G");
	PFLAG(PHY, 0, CHANNEL_WIDTH_SET_160MHZ_IN_5G,
	      "CHANNEL-WIDTH-SET-160MHZ-IN-5G");
	PFLAG(PHY, 0, CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G,
	      "CHANNEL-WIDTH-SET-80PLUS80-MHZ-IN-5G");
	PFLAG(PHY, 0, CHANNEL_WIDTH_SET_RU_MAPPING_IN_2G,
	      "CHANNEL-WIDTH-SET-RU-MAPPING-IN-2G");
	PFLAG(PHY, 0, CHANNEL_WIDTH_SET_RU_MAPPING_IN_5G,
	      "CHANNEL-WIDTH-SET-RU-MAPPING-IN-5G");

	चयन (cap[1] & IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_MASK) अणु
	हाल IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_80MHZ_ONLY_SECOND_20MHZ:
		PRINT("PREAMBLE-PUNC-RX-80MHZ-ONLY-SECOND-20MHZ");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_80MHZ_ONLY_SECOND_40MHZ:
		PRINT("PREAMBLE-PUNC-RX-80MHZ-ONLY-SECOND-40MHZ");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_160MHZ_ONLY_SECOND_20MHZ:
		PRINT("PREAMBLE-PUNC-RX-160MHZ-ONLY-SECOND-20MHZ");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_160MHZ_ONLY_SECOND_40MHZ:
		PRINT("PREAMBLE-PUNC-RX-160MHZ-ONLY-SECOND-40MHZ");
		अवरोध;
	पूर्ण

	PFLAG(PHY, 1, DEVICE_CLASS_A,
	      "IEEE80211-HE-PHY-CAP1-DEVICE-CLASS-A");
	PFLAG(PHY, 1, LDPC_CODING_IN_PAYLOAD,
	      "LDPC-CODING-IN-PAYLOAD");
	PFLAG(PHY, 1, HE_LTF_AND_GI_FOR_HE_PPDUS_0_8US,
	      "HY-CAP1-HE-LTF-AND-GI-FOR-HE-PPDUS-0-8US");
	PRINT("MIDAMBLE-RX-MAX-NSTS-%d", ((cap[2] << 1) | (cap[1] >> 7)) & 0x3);

	PFLAG(PHY, 2, NDP_4x_LTF_AND_3_2US, "NDP-4X-LTF-AND-3-2US");
	PFLAG(PHY, 2, STBC_TX_UNDER_80MHZ, "STBC-TX-UNDER-80MHZ");
	PFLAG(PHY, 2, STBC_RX_UNDER_80MHZ, "STBC-RX-UNDER-80MHZ");
	PFLAG(PHY, 2, DOPPLER_TX, "DOPPLER-TX");
	PFLAG(PHY, 2, DOPPLER_RX, "DOPPLER-RX");
	PFLAG(PHY, 2, UL_MU_FULL_MU_MIMO, "UL-MU-FULL-MU-MIMO");
	PFLAG(PHY, 2, UL_MU_PARTIAL_MU_MIMO, "UL-MU-PARTIAL-MU-MIMO");

	चयन (cap[3] & IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_MASK) अणु
	हाल IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_NO_DCM:
		PRINT("DCM-MAX-CONST-TX-NO-DCM");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_BPSK:
		PRINT("DCM-MAX-CONST-TX-BPSK");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_QPSK:
		PRINT("DCM-MAX-CONST-TX-QPSK");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_16_QAM:
		PRINT("DCM-MAX-CONST-TX-16-QAM");
		अवरोध;
	पूर्ण

	PFLAG(PHY, 3, DCM_MAX_TX_NSS_1, "DCM-MAX-TX-NSS-1");
	PFLAG(PHY, 3, DCM_MAX_TX_NSS_2, "DCM-MAX-TX-NSS-2");

	चयन (cap[3] & IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_MASK) अणु
	हाल IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_NO_DCM:
		PRINT("DCM-MAX-CONST-RX-NO-DCM");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_BPSK:
		PRINT("DCM-MAX-CONST-RX-BPSK");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_QPSK:
		PRINT("DCM-MAX-CONST-RX-QPSK");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_16_QAM:
		PRINT("DCM-MAX-CONST-RX-16-QAM");
		अवरोध;
	पूर्ण

	PFLAG(PHY, 3, DCM_MAX_RX_NSS_1, "DCM-MAX-RX-NSS-1");
	PFLAG(PHY, 3, DCM_MAX_RX_NSS_2, "DCM-MAX-RX-NSS-2");
	PFLAG(PHY, 3, RX_PARTIAL_BW_SU_IN_20MHZ_MU,
	      "RX-PARTIAL-BW-SU-IN-20MHZ-MU");
	PFLAG(PHY, 3, SU_BEAMFORMER, "SU-BEAMFORMER");

	PFLAG(PHY, 4, SU_BEAMFORMEE, "SU-BEAMFORMEE");
	PFLAG(PHY, 4, MU_BEAMFORMER, "MU-BEAMFORMER");

	PFLAG_RANGE(PHY, 4, BEAMFORMEE_MAX_STS_UNDER_80MHZ, 0, 1, 4,
		    "BEAMFORMEE-MAX-STS-UNDER-%d");
	PFLAG_RANGE(PHY, 4, BEAMFORMEE_MAX_STS_ABOVE_80MHZ, 0, 1, 4,
		    "BEAMFORMEE-MAX-STS-ABOVE-%d");

	PFLAG_RANGE(PHY, 5, BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ, 0, 1, 1,
		    "NUM-SND-DIM-UNDER-80MHZ-%d");
	PFLAG_RANGE(PHY, 5, BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ, 0, 1, 1,
		    "NUM-SND-DIM-ABOVE-80MHZ-%d");
	PFLAG(PHY, 5, NG16_SU_FEEDBACK, "NG16-SU-FEEDBACK");
	PFLAG(PHY, 5, NG16_MU_FEEDBACK, "NG16-MU-FEEDBACK");

	PFLAG(PHY, 6, CODEBOOK_SIZE_42_SU, "CODEBOOK-SIZE-42-SU");
	PFLAG(PHY, 6, CODEBOOK_SIZE_75_MU, "CODEBOOK-SIZE-75-MU");
	PFLAG(PHY, 6, TRIG_SU_BEAMFORMING_FB, "TRIG-SU-BEAMFORMING-FB");
	PFLAG(PHY, 6, TRIG_MU_BEAMFORMING_PARTIAL_BW_FB,
	      "MU-BEAMFORMING-PARTIAL-BW-FB");
	PFLAG(PHY, 6, TRIG_CQI_FB, "TRIG-CQI-FB");
	PFLAG(PHY, 6, PARTIAL_BW_EXT_RANGE, "PARTIAL-BW-EXT-RANGE");
	PFLAG(PHY, 6, PARTIAL_BANDWIDTH_DL_MUMIMO,
	      "PARTIAL-BANDWIDTH-DL-MUMIMO");
	PFLAG(PHY, 6, PPE_THRESHOLD_PRESENT, "PPE-THRESHOLD-PRESENT");

	PFLAG(PHY, 7, PSR_BASED_SR, "PSR-BASED-SR");
	PFLAG(PHY, 7, POWER_BOOST_FACTOR_SUPP, "POWER-BOOST-FACTOR-SUPP");
	PFLAG(PHY, 7, HE_SU_MU_PPDU_4XLTF_AND_08_US_GI,
	      "HE-SU-MU-PPDU-4XLTF-AND-08-US-GI");
	PFLAG_RANGE(PHY, 7, MAX_NC, 0, 1, 1, "MAX-NC-%d");
	PFLAG(PHY, 7, STBC_TX_ABOVE_80MHZ, "STBC-TX-ABOVE-80MHZ");
	PFLAG(PHY, 7, STBC_RX_ABOVE_80MHZ, "STBC-RX-ABOVE-80MHZ");

	PFLAG(PHY, 8, HE_ER_SU_PPDU_4XLTF_AND_08_US_GI,
	      "HE-ER-SU-PPDU-4XLTF-AND-08-US-GI");
	PFLAG(PHY, 8, 20MHZ_IN_40MHZ_HE_PPDU_IN_2G,
	      "20MHZ-IN-40MHZ-HE-PPDU-IN-2G");
	PFLAG(PHY, 8, 20MHZ_IN_160MHZ_HE_PPDU, "20MHZ-IN-160MHZ-HE-PPDU");
	PFLAG(PHY, 8, 80MHZ_IN_160MHZ_HE_PPDU, "80MHZ-IN-160MHZ-HE-PPDU");
	PFLAG(PHY, 8, HE_ER_SU_1XLTF_AND_08_US_GI,
	      "HE-ER-SU-1XLTF-AND-08-US-GI");
	PFLAG(PHY, 8, MIDAMBLE_RX_TX_2X_AND_1XLTF,
	      "MIDAMBLE-RX-TX-2X-AND-1XLTF");

	चयन (cap[8] & IEEE80211_HE_PHY_CAP8_DCM_MAX_RU_MASK) अणु
	हाल IEEE80211_HE_PHY_CAP8_DCM_MAX_RU_242:
		PRINT("DCM-MAX-RU-242");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP8_DCM_MAX_RU_484:
		PRINT("DCM-MAX-RU-484");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP8_DCM_MAX_RU_996:
		PRINT("DCM-MAX-RU-996");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP8_DCM_MAX_RU_2x996:
		PRINT("DCM-MAX-RU-2x996");
		अवरोध;
	पूर्ण

	PFLAG(PHY, 9, LONGER_THAN_16_SIGB_OFDM_SYM,
	      "LONGER-THAN-16-SIGB-OFDM-SYM");
	PFLAG(PHY, 9, NON_TRIGGERED_CQI_FEEDBACK,
	      "NON-TRIGGERED-CQI-FEEDBACK");
	PFLAG(PHY, 9, TX_1024_QAM_LESS_THAN_242_TONE_RU,
	      "TX-1024-QAM-LESS-THAN-242-TONE-RU");
	PFLAG(PHY, 9, RX_1024_QAM_LESS_THAN_242_TONE_RU,
	      "RX-1024-QAM-LESS-THAN-242-TONE-RU");
	PFLAG(PHY, 9, RX_FULL_BW_SU_USING_MU_WITH_COMP_SIGB,
	      "RX-FULL-BW-SU-USING-MU-WITH-COMP-SIGB");
	PFLAG(PHY, 9, RX_FULL_BW_SU_USING_MU_WITH_NON_COMP_SIGB,
	      "RX-FULL-BW-SU-USING-MU-WITH-NON-COMP-SIGB");

	चयन (cap[9] & IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_MASK) अणु
	हाल IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_0US:
		PRINT("NOMINAL-PACKET-PADDING-0US");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_8US:
		PRINT("NOMINAL-PACKET-PADDING-8US");
		अवरोध;
	हाल IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_16US:
		PRINT("NOMINAL-PACKET-PADDING-16US");
		अवरोध;
	पूर्ण

#अघोषित PFLAG_RANGE_DEFAULT
#अघोषित PFLAG_RANGE
#अघोषित PFLAG

#घोषणा PRINT_NSS_SUPP(f, n)						\
	करो अणु								\
		पूर्णांक _i;							\
		u16 v = le16_to_cpu(nss->f);				\
		p += scnम_लिखो(p, buf_sz + buf - p, n ": %#.4x\n", v);	\
		क्रम (_i = 0; _i < 8; _i += 2) अणु				\
			चयन ((v >> _i) & 0x3) अणु			\
			हाल 0:						\
				PRINT(n "-%d-SUPPORT-0-7", _i / 2);	\
				अवरोध;					\
			हाल 1:						\
				PRINT(n "-%d-SUPPORT-0-9", _i / 2);	\
				अवरोध;					\
			हाल 2:						\
				PRINT(n "-%d-SUPPORT-0-11", _i / 2);	\
				अवरोध;					\
			हाल 3:						\
				PRINT(n "-%d-NOT-SUPPORTED", _i / 2);	\
				अवरोध;					\
			पूर्ण						\
		पूर्ण							\
	पूर्ण जबतक (0)

	PRINT_NSS_SUPP(rx_mcs_80, "RX-MCS-80");
	PRINT_NSS_SUPP(tx_mcs_80, "TX-MCS-80");

	अगर (cap[0] & IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G) अणु
		PRINT_NSS_SUPP(rx_mcs_160, "RX-MCS-160");
		PRINT_NSS_SUPP(tx_mcs_160, "TX-MCS-160");
	पूर्ण

	अगर (cap[0] &
	    IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G) अणु
		PRINT_NSS_SUPP(rx_mcs_80p80, "RX-MCS-80P80");
		PRINT_NSS_SUPP(tx_mcs_80p80, "TX-MCS-80P80");
	पूर्ण

#अघोषित PRINT_NSS_SUPP
#अघोषित PRINT

	अगर (!(cap[6] & IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT))
		जाओ out;

	p += scnम_लिखो(p, buf_sz + buf - p, "PPE-THRESHOLDS: %#.2x",
		       hec->ppe_thres[0]);

	ppe_size = ieee80211_he_ppe_size(hec->ppe_thres[0], cap);
	क्रम (i = 1; i < ppe_size; i++) अणु
		p += scnम_लिखो(p, buf_sz + buf - p, " %#.2x",
			       hec->ppe_thres[i]);
	पूर्ण
	p += scnम_लिखो(p, buf_sz + buf - p, "\n");

out:
	ret = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, p - buf);
	kमुक्त(buf);
	वापस ret;
पूर्ण
STA_OPS(he_capa);

#घोषणा DEBUGFS_ADD(name) \
	debugfs_create_file(#name, 0400, \
		sta->debugfs_dir, sta, &sta_ ##name## _ops)

#घोषणा DEBUGFS_ADD_COUNTER(name, field)				\
	debugfs_create_uदीर्घ(#name, 0400, sta->debugfs_dir, &sta->field);

व्योम ieee80211_sta_debugfs_add(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_local *local = sta->local;
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा dentry *stations_dir = sta->sdata->debugfs.subdir_stations;
	u8 mac[3*ETH_ALEN];

	अगर (!stations_dir)
		वापस;

	snम_लिखो(mac, माप(mac), "%pM", sta->sta.addr);

	/*
	 * This might fail due to a race condition:
	 * When mac80211 unlinks a station, the debugfs entries
	 * reमुख्य, but it is alपढ़ोy possible to link a new
	 * station with the same address which triggers adding
	 * it to debugfs; thereक्रमe, अगर the old station isn't
	 * destroyed quickly enough the old station's debugfs
	 * dir might still be around.
	 */
	sta->debugfs_dir = debugfs_create_dir(mac, stations_dir);

	DEBUGFS_ADD(flags);
	DEBUGFS_ADD(aid);
	DEBUGFS_ADD(num_ps_buf_frames);
	DEBUGFS_ADD(last_seq_ctrl);
	DEBUGFS_ADD(agg_status);
	DEBUGFS_ADD(ht_capa);
	DEBUGFS_ADD(vht_capa);
	DEBUGFS_ADD(he_capa);

	DEBUGFS_ADD_COUNTER(rx_duplicates, rx_stats.num_duplicates);
	DEBUGFS_ADD_COUNTER(rx_fragments, rx_stats.fragments);
	DEBUGFS_ADD_COUNTER(tx_filtered, status_stats.filtered);

	अगर (local->ops->wake_tx_queue) अणु
		DEBUGFS_ADD(aqm);
		DEBUGFS_ADD(airसमय);
	पूर्ण

	अगर (wiphy_ext_feature_isset(local->hw.wiphy,
				    NL80211_EXT_FEATURE_AQL))
		DEBUGFS_ADD(aql);

	debugfs_create_xul("driver_buffered_tids", 0400, sta->debugfs_dir,
			   &sta->driver_buffered_tids);

	drv_sta_add_debugfs(local, sdata, &sta->sta, sta->debugfs_dir);
पूर्ण

व्योम ieee80211_sta_debugfs_हटाओ(काष्ठा sta_info *sta)
अणु
	debugfs_हटाओ_recursive(sta->debugfs_dir);
	sta->debugfs_dir = शून्य;
पूर्ण
