<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mac80211 debugfs क्रम wireless PHYs
 *
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright (C) 2018 - 2019, 2021 Intel Corporation
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"
#समावेश "debugfs.h"

#घोषणा DEBUGFS_FORMAT_BUFFER_SIZE 100

पूर्णांक mac80211_क्रमmat_buffer(अक्षर __user *userbuf, माप_प्रकार count,
				  loff_t *ppos, अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[DEBUGFS_FORMAT_BUFFER_SIZE];
	पूर्णांक res;

	बहु_शुरू(args, fmt);
	res = vscnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, res);
पूर्ण

#घोषणा DEBUGFS_READONLY_खाता_FN(name, fmt, value...)			\
अटल sमाप_प्रकार name## _पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,	\
			    माप_प्रकार count, loff_t *ppos)			\
अणु									\
	काष्ठा ieee80211_local *local = file->निजी_data;		\
									\
	वापस mac80211_क्रमmat_buffer(userbuf, count, ppos, 		\
				      fmt "\n", ##value);		\
पूर्ण

#घोषणा DEBUGFS_READONLY_खाता_OPS(name)			\
अटल स्थिर काष्ठा file_operations name## _ops = अणु			\
	.पढ़ो = name## _पढ़ो,						\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_READONLY_खाता(name, fmt, value...)		\
	DEBUGFS_READONLY_खाता_FN(name, fmt, value)		\
	DEBUGFS_READONLY_खाता_OPS(name)

#घोषणा DEBUGFS_ADD(name)						\
	debugfs_create_file(#name, 0400, phyd, local, &name## _ops)

#घोषणा DEBUGFS_ADD_MODE(name, mode)					\
	debugfs_create_file(#name, mode, phyd, local, &name## _ops);


DEBUGFS_READONLY_खाता(hw_conf, "%x",
		      local->hw.conf.flags);
DEBUGFS_READONLY_खाता(user_घातer, "%d",
		      local->user_घातer_level);
DEBUGFS_READONLY_खाता(घातer, "%d",
		      local->hw.conf.घातer_level);
DEBUGFS_READONLY_खाता(total_ps_buffered, "%d",
		      local->total_ps_buffered);
DEBUGFS_READONLY_खाता(wep_iv, "%#08x",
		      local->wep_iv & 0xffffff);
DEBUGFS_READONLY_खाता(rate_ctrl_alg, "%s",
	local->rate_ctrl ? local->rate_ctrl->ops->name : "hw/driver");

अटल sमाप_प्रकार aqm_पढ़ो(काष्ठा file *file,
			अक्षर __user *user_buf,
			माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	काष्ठा fq *fq = &local->fq;
	अक्षर buf[200];
	पूर्णांक len = 0;

	spin_lock_bh(&local->fq.lock);
	rcu_पढ़ो_lock();

	len = scnम_लिखो(buf, माप(buf),
			"access name value\n"
			"R fq_flows_cnt %u\n"
			"R fq_backlog %u\n"
			"R fq_overlimit %u\n"
			"R fq_overmemory %u\n"
			"R fq_collisions %u\n"
			"R fq_memory_usage %u\n"
			"RW fq_memory_limit %u\n"
			"RW fq_limit %u\n"
			"RW fq_quantum %u\n",
			fq->flows_cnt,
			fq->backlog,
			fq->overmemory,
			fq->overlimit,
			fq->collisions,
			fq->memory_usage,
			fq->memory_limit,
			fq->limit,
			fq->quantum);

	rcu_पढ़ो_unlock();
	spin_unlock_bh(&local->fq.lock);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,
				       buf, len);
पूर्ण

अटल sमाप_प्रकार aqm_ग_लिखो(काष्ठा file *file,
			 स्थिर अक्षर __user *user_buf,
			 माप_प्रकार count,
			 loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	अक्षर buf[100];

	अगर (count >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, user_buf, count))
		वापस -EFAULT;

	अगर (count && buf[count - 1] == '\n')
		buf[count - 1] = '\0';
	अन्यथा
		buf[count] = '\0';

	अगर (माला_पूछो(buf, "fq_limit %u", &local->fq.limit) == 1)
		वापस count;
	अन्यथा अगर (माला_पूछो(buf, "fq_memory_limit %u", &local->fq.memory_limit) == 1)
		वापस count;
	अन्यथा अगर (माला_पूछो(buf, "fq_quantum %u", &local->fq.quantum) == 1)
		वापस count;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा file_operations aqm_ops = अणु
	.ग_लिखो = aqm_ग_लिखो,
	.पढ़ो = aqm_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार airसमय_flags_पढ़ो(काष्ठा file *file,
				  अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	अक्षर buf[128] = अणुपूर्ण, *pos, *end;

	pos = buf;
	end = pos + माप(buf) - 1;

	अगर (local->airसमय_flags & AIRTIME_USE_TX)
		pos += scnम_लिखो(pos, end - pos, "AIRTIME_TX\t(%lx)\n",
				 AIRTIME_USE_TX);
	अगर (local->airसमय_flags & AIRTIME_USE_RX)
		pos += scnम_लिखो(pos, end - pos, "AIRTIME_RX\t(%lx)\n",
				 AIRTIME_USE_RX);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf,
				       म_माप(buf));
पूर्ण

अटल sमाप_प्रकार airसमय_flags_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	अक्षर buf[16];

	अगर (count >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, user_buf, count))
		वापस -EFAULT;

	अगर (count && buf[count - 1] == '\n')
		buf[count - 1] = '\0';
	अन्यथा
		buf[count] = '\0';

	अगर (kstrtou16(buf, 0, &local->airसमय_flags))
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations airसमय_flags_ops = अणु
	.ग_लिखो = airसमय_flags_ग_लिखो,
	.पढ़ो = airसमय_flags_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार aql_txq_limit_पढ़ो(काष्ठा file *file,
				  अक्षर __user *user_buf,
				  माप_प्रकार count,
				  loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	अक्षर buf[400];
	पूर्णांक len = 0;

	len = scnम_लिखो(buf, माप(buf),
			"AC	AQL limit low	AQL limit high\n"
			"VO	%u		%u\n"
			"VI	%u		%u\n"
			"BE	%u		%u\n"
			"BK	%u		%u\n",
			local->aql_txq_limit_low[IEEE80211_AC_VO],
			local->aql_txq_limit_high[IEEE80211_AC_VO],
			local->aql_txq_limit_low[IEEE80211_AC_VI],
			local->aql_txq_limit_high[IEEE80211_AC_VI],
			local->aql_txq_limit_low[IEEE80211_AC_BE],
			local->aql_txq_limit_high[IEEE80211_AC_BE],
			local->aql_txq_limit_low[IEEE80211_AC_BK],
			local->aql_txq_limit_high[IEEE80211_AC_BK]);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,
				       buf, len);
पूर्ण

अटल sमाप_प्रकार aql_txq_limit_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user *user_buf,
				   माप_प्रकार count,
				   loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	अक्षर buf[100];
	u32 ac, q_limit_low, q_limit_high, q_limit_low_old, q_limit_high_old;
	काष्ठा sta_info *sta;

	अगर (count >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, user_buf, count))
		वापस -EFAULT;

	अगर (count && buf[count - 1] == '\n')
		buf[count - 1] = '\0';
	अन्यथा
		buf[count] = '\0';

	अगर (माला_पूछो(buf, "%u %u %u", &ac, &q_limit_low, &q_limit_high) != 3)
		वापस -EINVAL;

	अगर (ac >= IEEE80211_NUM_ACS)
		वापस -EINVAL;

	q_limit_low_old = local->aql_txq_limit_low[ac];
	q_limit_high_old = local->aql_txq_limit_high[ac];

	local->aql_txq_limit_low[ac] = q_limit_low;
	local->aql_txq_limit_high[ac] = q_limit_high;

	mutex_lock(&local->sta_mtx);
	list_क्रम_each_entry(sta, &local->sta_list, list) अणु
		/* If a sta has customized queue limits, keep it */
		अगर (sta->airसमय[ac].aql_limit_low == q_limit_low_old &&
		    sta->airसमय[ac].aql_limit_high == q_limit_high_old) अणु
			sta->airसमय[ac].aql_limit_low = q_limit_low;
			sta->airसमय[ac].aql_limit_high = q_limit_high;
		पूर्ण
	पूर्ण
	mutex_unlock(&local->sta_mtx);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations aql_txq_limit_ops = अणु
	.ग_लिखो = aql_txq_limit_ग_लिखो,
	.पढ़ो = aql_txq_limit_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार aql_enable_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[3];
	पूर्णांक len;

	len = scnम_लिखो(buf, माप(buf), "%d\n",
			!अटल_key_false(&aql_disable.key));

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार aql_enable_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	bool aql_disabled = अटल_key_false(&aql_disable.key);
	अक्षर buf[3];
	माप_प्रकार len;

	अगर (count > माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, user_buf, count))
		वापस -EFAULT;

	buf[माप(buf) - 1] = '\0';
	len = म_माप(buf);
	अगर (len > 0 && buf[len - 1] == '\n')
		buf[len - 1] = 0;

	अगर (buf[0] == '0' && buf[1] == '\0') अणु
		अगर (!aql_disabled)
			अटल_branch_inc(&aql_disable);
	पूर्ण अन्यथा अगर (buf[0] == '1' && buf[1] == '\0') अणु
		अगर (aql_disabled)
			अटल_branch_dec(&aql_disable);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations aql_enable_ops = अणु
	.ग_लिखो = aql_enable_ग_लिखो,
	.पढ़ो = aql_enable_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार क्रमce_tx_status_पढ़ो(काष्ठा file *file,
				    अक्षर __user *user_buf,
				    माप_प्रकार count,
				    loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	अक्षर buf[3];
	पूर्णांक len = 0;

	len = scnम_लिखो(buf, माप(buf), "%d\n", (पूर्णांक)local->क्रमce_tx_status);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,
				       buf, len);
पूर्ण

अटल sमाप_प्रकार क्रमce_tx_status_ग_लिखो(काष्ठा file *file,
				     स्थिर अक्षर __user *user_buf,
				     माप_प्रकार count,
				     loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	अक्षर buf[3];

	अगर (count >= माप(buf))
		वापस -EINVAL;

	अगर (copy_from_user(buf, user_buf, count))
		वापस -EFAULT;

	अगर (count && buf[count - 1] == '\n')
		buf[count - 1] = '\0';
	अन्यथा
		buf[count] = '\0';

	अगर (buf[0] == '0' && buf[1] == '\0')
		local->क्रमce_tx_status = 0;
	अन्यथा अगर (buf[0] == '1' && buf[1] == '\0')
		local->क्रमce_tx_status = 1;
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations क्रमce_tx_status_ops = अणु
	.ग_लिखो = क्रमce_tx_status_ग_लिखो,
	.पढ़ो = क्रमce_tx_status_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल sमाप_प्रकार reset_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	पूर्णांक ret;

	rtnl_lock();
	wiphy_lock(local->hw.wiphy);
	__ieee80211_suspend(&local->hw, शून्य);
	ret = __ieee80211_resume(&local->hw);
	wiphy_unlock(local->hw.wiphy);

	अगर (ret)
		cfg80211_shutकरोwn_all_पूर्णांकerfaces(local->hw.wiphy);

	rtnl_unlock();

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations reset_ops = अणु
	.ग_लिखो = reset_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = noop_llseek,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर अक्षर *hw_flag_names[] = अणु
#घोषणा FLAG(F)	[IEEE80211_HW_##F] = #F
	FLAG(HAS_RATE_CONTROL),
	FLAG(RX_INCLUDES_FCS),
	FLAG(HOST_BROADCAST_PS_BUFFERING),
	FLAG(SIGNAL_UNSPEC),
	FLAG(SIGNAL_DBM),
	FLAG(NEED_DTIM_BEFORE_ASSOC),
	FLAG(SPECTRUM_MGMT),
	FLAG(AMPDU_AGGREGATION),
	FLAG(SUPPORTS_PS),
	FLAG(PS_शून्यFUNC_STACK),
	FLAG(SUPPORTS_DYNAMIC_PS),
	FLAG(MFP_CAPABLE),
	FLAG(WANT_MONITOR_VIF),
	FLAG(NO_AUTO_VIF),
	FLAG(SW_CRYPTO_CONTROL),
	FLAG(SUPPORT_FAST_XMIT),
	FLAG(REPORTS_TX_ACK_STATUS),
	FLAG(CONNECTION_MONITOR),
	FLAG(QUEUE_CONTROL),
	FLAG(SUPPORTS_PER_STA_GTK),
	FLAG(AP_LINK_PS),
	FLAG(TX_AMPDU_SETUP_IN_HW),
	FLAG(SUPPORTS_RC_TABLE),
	FLAG(P2P_DEV_ADDR_FOR_INTF),
	FLAG(TIMING_BEACON_ONLY),
	FLAG(SUPPORTS_HT_CCK_RATES),
	FLAG(CHANCTX_STA_CSA),
	FLAG(SUPPORTS_CLONED_SKBS),
	FLAG(SINGLE_SCAN_ON_ALL_BANDS),
	FLAG(TDLS_WIDER_BW),
	FLAG(SUPPORTS_AMSDU_IN_AMPDU),
	FLAG(BEACON_TX_STATUS),
	FLAG(NEEDS_UNIQUE_STA_ADDR),
	FLAG(SUPPORTS_REORDERING_BUFFER),
	FLAG(USES_RSS),
	FLAG(TX_AMSDU),
	FLAG(TX_FRAG_LIST),
	FLAG(REPORTS_LOW_ACK),
	FLAG(SUPPORTS_TX_FRAG),
	FLAG(SUPPORTS_TDLS_BUFFER_STA),
	FLAG(DEAUTH_NEED_MGD_TX_PREP),
	FLAG(DOESNT_SUPPORT_QOS_NDP),
	FLAG(BUFF_MMPDU_TXQ),
	FLAG(SUPPORTS_VHT_EXT_NSS_BW),
	FLAG(STA_MMPDU_TXQ),
	FLAG(TX_STATUS_NO_AMPDU_LEN),
	FLAG(SUPPORTS_MULTI_BSSID),
	FLAG(SUPPORTS_ONLY_HE_MULTI_BSSID),
	FLAG(AMPDU_KEYBORDER_SUPPORT),
	FLAG(SUPPORTS_TX_ENCAP_OFFLOAD),
	FLAG(SUPPORTS_RX_DECAP_OFFLOAD),
	FLAG(SUPPORTS_CONC_MON_RX_DECAP),
#अघोषित FLAG
पूर्ण;

अटल sमाप_प्रकार hwflags_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	माप_प्रकार bufsz = 30 * NUM_IEEE80211_HW_FLAGS;
	अक्षर *buf = kzalloc(bufsz, GFP_KERNEL);
	अक्षर *pos = buf, *end = buf + bufsz - 1;
	sमाप_प्रकार rv;
	पूर्णांक i;

	अगर (!buf)
		वापस -ENOMEM;

	/* fail compilation अगर somebody adds or हटाओs
	 * a flag without updating the name array above
	 */
	BUILD_BUG_ON(ARRAY_SIZE(hw_flag_names) != NUM_IEEE80211_HW_FLAGS);

	क्रम (i = 0; i < NUM_IEEE80211_HW_FLAGS; i++) अणु
		अगर (test_bit(i, local->hw.flags))
			pos += scnम_लिखो(pos, end - pos, "%s\n",
					 hw_flag_names[i]);
	पूर्ण

	rv = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, म_माप(buf));
	kमुक्त(buf);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार misc_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	/* Max len of each line is 16 अक्षरacters, plus 9 क्रम 'pending:\n' */
	माप_प्रकार bufsz = IEEE80211_MAX_QUEUES * 16 + 9;
	अक्षर *buf;
	अक्षर *pos, *end;
	sमाप_प्रकार rv;
	पूर्णांक i;
	पूर्णांक ln;

	buf = kzalloc(bufsz, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pos = buf;
	end = buf + bufsz - 1;

	pos += scnम_लिखो(pos, end - pos, "pending:\n");

	क्रम (i = 0; i < IEEE80211_MAX_QUEUES; i++) अणु
		ln = skb_queue_len(&local->pending[i]);
		pos += scnम_लिखो(pos, end - pos, "[%i] %d\n",
				 i, ln);
	पूर्ण

	rv = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, म_माप(buf));
	kमुक्त(buf);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार queues_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_local *local = file->निजी_data;
	अचिन्हित दीर्घ flags;
	अक्षर buf[IEEE80211_MAX_QUEUES * 20];
	पूर्णांक q, res = 0;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	क्रम (q = 0; q < local->hw.queues; q++)
		res += प्र_लिखो(buf + res, "%02d: %#.8lx/%d\n", q,
				local->queue_stop_reasons[q],
				skb_queue_len(&local->pending[q]));
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, res);
पूर्ण

DEBUGFS_READONLY_खाता_OPS(hwflags);
DEBUGFS_READONLY_खाता_OPS(queues);
DEBUGFS_READONLY_खाता_OPS(misc);

/* statistics stuff */

अटल sमाप_प्रकार क्रमmat_devstat_counter(काष्ठा ieee80211_local *local,
	अक्षर __user *userbuf,
	माप_प्रकार count, loff_t *ppos,
	पूर्णांक (*prपूर्णांकvalue)(काष्ठा ieee80211_low_level_stats *stats, अक्षर *buf,
			  पूर्णांक buflen))
अणु
	काष्ठा ieee80211_low_level_stats stats;
	अक्षर buf[20];
	पूर्णांक res;

	rtnl_lock();
	res = drv_get_stats(local, &stats);
	rtnl_unlock();
	अगर (res)
		वापस res;
	res = prपूर्णांकvalue(&stats, buf, माप(buf));
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, res);
पूर्ण

#घोषणा DEBUGFS_DEVSTATS_खाता(name)					\
अटल पूर्णांक prपूर्णांक_devstats_##name(काष्ठा ieee80211_low_level_stats *stats,\
				 अक्षर *buf, पूर्णांक buflen)			\
अणु									\
	वापस scnम_लिखो(buf, buflen, "%u\n", stats->name);		\
पूर्ण									\
अटल sमाप_प्रकार stats_ ##name## _पढ़ो(काष्ठा file *file,			\
				     अक्षर __user *userbuf,		\
				     माप_प्रकार count, loff_t *ppos)	\
अणु									\
	वापस क्रमmat_devstat_counter(file->निजी_data,		\
				      userbuf,				\
				      count,				\
				      ppos,				\
				      prपूर्णांक_devstats_##name);		\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations stats_ ##name## _ops = अणु		\
	.पढ़ो = stats_ ##name## _पढ़ो,					\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;

#घोषणा DEBUGFS_STATS_ADD(name)					\
	debugfs_create_u32(#name, 0400, statsd, &local->name);
#घोषणा DEBUGFS_DEVSTATS_ADD(name)					\
	debugfs_create_file(#name, 0400, statsd, local, &stats_ ##name## _ops);

DEBUGFS_DEVSTATS_खाता(करोt11ACKFailureCount);
DEBUGFS_DEVSTATS_खाता(करोt11RTSFailureCount);
DEBUGFS_DEVSTATS_खाता(करोt11FCSErrorCount);
DEBUGFS_DEVSTATS_खाता(करोt11RTSSuccessCount);

व्योम debugfs_hw_add(काष्ठा ieee80211_local *local)
अणु
	काष्ठा dentry *phyd = local->hw.wiphy->debugfsdir;
	काष्ठा dentry *statsd;

	अगर (!phyd)
		वापस;

	local->debugfs.keys = debugfs_create_dir("keys", phyd);

	DEBUGFS_ADD(total_ps_buffered);
	DEBUGFS_ADD(wep_iv);
	DEBUGFS_ADD(rate_ctrl_alg);
	DEBUGFS_ADD(queues);
	DEBUGFS_ADD(misc);
#अगर_घोषित CONFIG_PM
	DEBUGFS_ADD_MODE(reset, 0200);
#पूर्ण_अगर
	DEBUGFS_ADD(hwflags);
	DEBUGFS_ADD(user_घातer);
	DEBUGFS_ADD(घातer);
	DEBUGFS_ADD(hw_conf);
	DEBUGFS_ADD_MODE(क्रमce_tx_status, 0600);
	DEBUGFS_ADD_MODE(aql_enable, 0600);

	अगर (local->ops->wake_tx_queue)
		DEBUGFS_ADD_MODE(aqm, 0600);

	DEBUGFS_ADD_MODE(airसमय_flags, 0600);

	DEBUGFS_ADD(aql_txq_limit);
	debugfs_create_u32("aql_threshold", 0600,
			   phyd, &local->aql_threshold);

	statsd = debugfs_create_dir("statistics", phyd);

	/* अगर the dir failed, करोn't put all the other things पूर्णांकo the root! */
	अगर (!statsd)
		वापस;

#अगर_घोषित CONFIG_MAC80211_DEBUG_COUNTERS
	DEBUGFS_STATS_ADD(करोt11TransmittedFragmentCount);
	DEBUGFS_STATS_ADD(करोt11MulticastTransmittedFrameCount);
	DEBUGFS_STATS_ADD(करोt11FailedCount);
	DEBUGFS_STATS_ADD(करोt11RetryCount);
	DEBUGFS_STATS_ADD(करोt11MultipleRetryCount);
	DEBUGFS_STATS_ADD(करोt11FrameDuplicateCount);
	DEBUGFS_STATS_ADD(करोt11ReceivedFragmentCount);
	DEBUGFS_STATS_ADD(करोt11MulticastReceivedFrameCount);
	DEBUGFS_STATS_ADD(करोt11TransmittedFrameCount);
	DEBUGFS_STATS_ADD(tx_handlers_drop);
	DEBUGFS_STATS_ADD(tx_handlers_queued);
	DEBUGFS_STATS_ADD(tx_handlers_drop_wep);
	DEBUGFS_STATS_ADD(tx_handlers_drop_not_assoc);
	DEBUGFS_STATS_ADD(tx_handlers_drop_unauth_port);
	DEBUGFS_STATS_ADD(rx_handlers_drop);
	DEBUGFS_STATS_ADD(rx_handlers_queued);
	DEBUGFS_STATS_ADD(rx_handlers_drop_nullfunc);
	DEBUGFS_STATS_ADD(rx_handlers_drop_defrag);
	DEBUGFS_STATS_ADD(tx_expand_skb_head);
	DEBUGFS_STATS_ADD(tx_expand_skb_head_cloned);
	DEBUGFS_STATS_ADD(rx_expand_skb_head_defrag);
	DEBUGFS_STATS_ADD(rx_handlers_fragments);
	DEBUGFS_STATS_ADD(tx_status_drop);
#पूर्ण_अगर
	DEBUGFS_DEVSTATS_ADD(करोt11ACKFailureCount);
	DEBUGFS_DEVSTATS_ADD(करोt11RTSFailureCount);
	DEBUGFS_DEVSTATS_ADD(करोt11FCSErrorCount);
	DEBUGFS_DEVSTATS_ADD(करोt11RTSSuccessCount);
पूर्ण
