<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "htc.h"

अटल sमाप_प्रकार पढ़ो_file_tgt_पूर्णांक_stats(काष्ठा file *file, अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath9k_htc_priv *priv = file->निजी_data;
	काष्ठा ath9k_htc_target_पूर्णांक_stats cmd_rsp;
	अक्षर buf[512];
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक ret = 0;

	स_रखो(&cmd_rsp, 0, माप(cmd_rsp));

	ath9k_htc_ps_wakeup(priv);

	WMI_CMD(WMI_INT_STATS_CMDID);
	अगर (ret) अणु
		ath9k_htc_ps_restore(priv);
		वापस -EINVAL;
	पूर्ण

	ath9k_htc_ps_restore(priv);

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "RX",
			 be32_to_cpu(cmd_rsp.rx));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "RXORN",
			 be32_to_cpu(cmd_rsp.rxorn));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "RXEOL",
			 be32_to_cpu(cmd_rsp.rxeol));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "TXURN",
			 be32_to_cpu(cmd_rsp.txurn));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "TXTO",
			 be32_to_cpu(cmd_rsp.txto));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "CST",
			 be32_to_cpu(cmd_rsp.cst));

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tgt_पूर्णांक_stats = अणु
	.पढ़ो = पढ़ो_file_tgt_पूर्णांक_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_tgt_tx_stats(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath9k_htc_priv *priv = file->निजी_data;
	काष्ठा ath9k_htc_target_tx_stats cmd_rsp;
	अक्षर buf[512];
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक ret = 0;

	स_रखो(&cmd_rsp, 0, माप(cmd_rsp));

	ath9k_htc_ps_wakeup(priv);

	WMI_CMD(WMI_TX_STATS_CMDID);
	अगर (ret) अणु
		ath9k_htc_ps_restore(priv);
		वापस -EINVAL;
	पूर्ण

	ath9k_htc_ps_restore(priv);

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "Xretries",
			 be32_to_cpu(cmd_rsp.xretries));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "FifoErr",
			 be32_to_cpu(cmd_rsp.fअगरoerr));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "Filtered",
			 be32_to_cpu(cmd_rsp.filtered));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "TimerExp",
			 be32_to_cpu(cmd_rsp.समयr_exp));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "ShortRetries",
			 be32_to_cpu(cmd_rsp.लघुretries));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "LongRetries",
			 be32_to_cpu(cmd_rsp.दीर्घretries));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "QueueNull",
			 be32_to_cpu(cmd_rsp.qnull));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "EncapFail",
			 be32_to_cpu(cmd_rsp.encap_fail));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "NoBuf",
			 be32_to_cpu(cmd_rsp.nobuf));

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tgt_tx_stats = अणु
	.पढ़ो = पढ़ो_file_tgt_tx_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_tgt_rx_stats(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath9k_htc_priv *priv = file->निजी_data;
	काष्ठा ath9k_htc_target_rx_stats cmd_rsp;
	अक्षर buf[512];
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक ret = 0;

	स_रखो(&cmd_rsp, 0, माप(cmd_rsp));

	ath9k_htc_ps_wakeup(priv);

	WMI_CMD(WMI_RX_STATS_CMDID);
	अगर (ret) अणु
		ath9k_htc_ps_restore(priv);
		वापस -EINVAL;
	पूर्ण

	ath9k_htc_ps_restore(priv);

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "NoBuf",
			 be32_to_cpu(cmd_rsp.nobuf));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "HostSend",
			 be32_to_cpu(cmd_rsp.host_send));

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "HostDone",
			 be32_to_cpu(cmd_rsp.host_करोne));

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tgt_rx_stats = अणु
	.पढ़ो = पढ़ो_file_tgt_rx_stats,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_xmit(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath9k_htc_priv *priv = file->निजी_data;
	अक्षर buf[512];
	अचिन्हित पूर्णांक len = 0;

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "Buffers queued",
			 priv->debug.tx_stats.buf_queued);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "Buffers completed",
			 priv->debug.tx_stats.buf_completed);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "SKBs queued",
			 priv->debug.tx_stats.skb_queued);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "SKBs success",
			 priv->debug.tx_stats.skb_success);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "SKBs failed",
			 priv->debug.tx_stats.skb_failed);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "CAB queued",
			 priv->debug.tx_stats.cab_queued);

	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "BE queued",
			 priv->debug.tx_stats.queue_stats[IEEE80211_AC_BE]);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "BK queued",
			 priv->debug.tx_stats.queue_stats[IEEE80211_AC_BK]);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "VI queued",
			 priv->debug.tx_stats.queue_stats[IEEE80211_AC_VI]);
	len += scnम_लिखो(buf + len, माप(buf) - len,
			 "%20s : %10u\n", "VO queued",
			 priv->debug.tx_stats.queue_stats[IEEE80211_AC_VO]);

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_xmit = अणु
	.पढ़ो = पढ़ो_file_xmit,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath9k_htc_err_stat_rx(काष्ठा ath9k_htc_priv *priv,
			     काष्ठा ath_rx_status *rs)
अणु
	ath9k_cmn_debug_stat_rx(&priv->debug.rx_stats, rs);
पूर्ण

अटल sमाप_प्रकार पढ़ो_file_skb_rx(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath9k_htc_priv *priv = file->निजी_data;
	अक्षर *buf;
	अचिन्हित पूर्णांक len = 0, size = 1500;
	sमाप_प्रकार retval = 0;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	len += scnम_लिखो(buf + len, size - len,
			 "%20s : %10u\n", "SKBs allocated",
			 priv->debug.skbrx_stats.skb_allocated);
	len += scnम_लिखो(buf + len, size - len,
			 "%20s : %10u\n", "SKBs completed",
			 priv->debug.skbrx_stats.skb_completed);
	len += scnम_लिखो(buf + len, size - len,
			 "%20s : %10u\n", "SKBs Dropped",
			 priv->debug.skbrx_stats.skb_dropped);

	अगर (len > size)
		len = size;

	retval = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
	kमुक्त(buf);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_skb_rx = अणु
	.पढ़ो = पढ़ो_file_skb_rx,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_slot(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath9k_htc_priv *priv = file->निजी_data;
	अक्षर buf[512];
	अचिन्हित पूर्णांक len;

	spin_lock_bh(&priv->tx.tx_lock);
	len = scnम_लिखो(buf, माप(buf),
			"TX slot bitmap : %*pb\n"
			"Used slots     : %d\n",
			MAX_TX_BUF_NUM, priv->tx.tx_slot,
			biपंचांगap_weight(priv->tx.tx_slot, MAX_TX_BUF_NUM));
	spin_unlock_bh(&priv->tx.tx_lock);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_slot = अणु
	.पढ़ो = पढ़ो_file_slot,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_queue(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath9k_htc_priv *priv = file->निजी_data;
	अक्षर buf[512];
	अचिन्हित पूर्णांक len = 0;

	len += scnम_लिखो(buf + len, माप(buf) - len, "%20s : %10u\n",
			 "Mgmt endpoint", skb_queue_len(&priv->tx.mgmt_ep_queue));

	len += scnम_लिखो(buf + len, माप(buf) - len, "%20s : %10u\n",
			 "Cab endpoint", skb_queue_len(&priv->tx.cab_ep_queue));

	len += scnम_लिखो(buf + len, माप(buf) - len, "%20s : %10u\n",
			 "Data BE endpoint", skb_queue_len(&priv->tx.data_be_queue));

	len += scnम_लिखो(buf + len, माप(buf) - len, "%20s : %10u\n",
			 "Data BK endpoint", skb_queue_len(&priv->tx.data_bk_queue));

	len += scnम_लिखो(buf + len, माप(buf) - len, "%20s : %10u\n",
			 "Data VI endpoint", skb_queue_len(&priv->tx.data_vi_queue));

	len += scnम_लिखो(buf + len, माप(buf) - len, "%20s : %10u\n",
			 "Data VO endpoint", skb_queue_len(&priv->tx.data_vo_queue));

	len += scnम_लिखो(buf + len, माप(buf) - len, "%20s : %10u\n",
			 "Failed queue", skb_queue_len(&priv->tx.tx_failed));

	spin_lock_bh(&priv->tx.tx_lock);
	len += scnम_लिखो(buf + len, माप(buf) - len, "%20s : %10u\n",
			 "Queued count", priv->tx.queued_cnt);
	spin_unlock_bh(&priv->tx.tx_lock);

	अगर (len > माप(buf))
		len = माप(buf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);

पूर्ण

अटल स्थिर काष्ठा file_operations fops_queue = अणु
	.पढ़ो = पढ़ो_file_queue,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_debug(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath9k_htc_priv *priv = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "0x%08x\n", common->debug_mask);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_debug(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath9k_htc_priv *priv = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	अचिन्हित दीर्घ mask;
	अक्षर buf[32];
	sमाप_प्रकार len;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';
	अगर (kम_से_अदीर्घ(buf, 0, &mask))
		वापस -EINVAL;

	common->debug_mask = mask;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_debug = अणु
	.पढ़ो = पढ़ो_file_debug,
	.ग_लिखो = ग_लिखो_file_debug,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

/* Ethtool support क्रम get-stats */
#घोषणा AMKSTR(nm) #nm "_BE", #nm "_BK", #nm "_VI", #nm "_VO"
अटल स्थिर अक्षर ath9k_htc_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"tx_pkts_nic",
	"tx_bytes_nic",
	"rx_pkts_nic",
	"rx_bytes_nic",

	AMKSTR(d_tx_pkts),

	"d_rx_crc_err",
	"d_rx_decrypt_crc_err",
	"d_rx_phy_err",
	"d_rx_mic_err",
	"d_rx_pre_delim_crc_err",
	"d_rx_post_delim_crc_err",
	"d_rx_decrypt_busy_err",

	"d_rx_phyerr_radar",
	"d_rx_phyerr_ofdm_timing",
	"d_rx_phyerr_cck_timing",

पूर्ण;
#घोषणा ATH9K_HTC_SSTATS_LEN ARRAY_SIZE(ath9k_htc_gstrings_stats)

व्योम ath9k_htc_get_et_strings(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      u32 sset, u8 *data)
अणु
	अगर (sset == ETH_SS_STATS)
		स_नकल(data, *ath9k_htc_gstrings_stats,
		       माप(ath9k_htc_gstrings_stats));
पूर्ण

पूर्णांक ath9k_htc_get_et_sset_count(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर, पूर्णांक sset)
अणु
	अगर (sset == ETH_SS_STATS)
		वापस ATH9K_HTC_SSTATS_LEN;
	वापस 0;
पूर्ण

#घोषणा STXBASE priv->debug.tx_stats
#घोषणा SRXBASE priv->debug.rx_stats
#घोषणा SKBTXBASE priv->debug.tx_stats
#घोषणा SKBRXBASE priv->debug.skbrx_stats
#घोषणा ASTXQ(a)					\
	data[i++] = STXBASE.a[IEEE80211_AC_BE];		\
	data[i++] = STXBASE.a[IEEE80211_AC_BK];		\
	data[i++] = STXBASE.a[IEEE80211_AC_VI];		\
	data[i++] = STXBASE.a[IEEE80211_AC_VO]

व्योम ath9k_htc_get_et_stats(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	पूर्णांक i = 0;

	data[i++] = SKBTXBASE.skb_success;
	data[i++] = SKBTXBASE.skb_success_bytes;
	data[i++] = SKBRXBASE.skb_completed;
	data[i++] = SKBRXBASE.skb_completed_bytes;

	ASTXQ(queue_stats);

	data[i++] = SRXBASE.crc_err;
	data[i++] = SRXBASE.decrypt_crc_err;
	data[i++] = SRXBASE.phy_err;
	data[i++] = SRXBASE.mic_err;
	data[i++] = SRXBASE.pre_delim_crc_err;
	data[i++] = SRXBASE.post_delim_crc_err;
	data[i++] = SRXBASE.decrypt_busy_err;

	data[i++] = SRXBASE.phy_err_stats[ATH9K_PHYERR_RADAR];
	data[i++] = SRXBASE.phy_err_stats[ATH9K_PHYERR_OFDM_TIMING];
	data[i++] = SRXBASE.phy_err_stats[ATH9K_PHYERR_CCK_TIMING];

	WARN_ON(i != ATH9K_HTC_SSTATS_LEN);
पूर्ण

व्योम ath9k_htc_deinit_debug(काष्ठा ath9k_htc_priv *priv)
अणु
	ath9k_cmn_spectral_deinit_debug(&priv->spec_priv);
पूर्ण

पूर्णांक ath9k_htc_init_debug(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;

	priv->debug.debugfs_phy = debugfs_create_dir(KBUILD_MODNAME,
					     priv->hw->wiphy->debugfsdir);
	अगर (!priv->debug.debugfs_phy)
		वापस -ENOMEM;

	ath9k_cmn_spectral_init_debug(&priv->spec_priv, priv->debug.debugfs_phy);

	debugfs_create_file("tgt_int_stats", 0400, priv->debug.debugfs_phy,
			    priv, &fops_tgt_पूर्णांक_stats);
	debugfs_create_file("tgt_tx_stats", 0400, priv->debug.debugfs_phy,
			    priv, &fops_tgt_tx_stats);
	debugfs_create_file("tgt_rx_stats", 0400, priv->debug.debugfs_phy,
			    priv, &fops_tgt_rx_stats);
	debugfs_create_file("xmit", 0400, priv->debug.debugfs_phy,
			    priv, &fops_xmit);
	debugfs_create_file("skb_rx", 0400, priv->debug.debugfs_phy,
			    priv, &fops_skb_rx);

	ath9k_cmn_debug_recv(priv->debug.debugfs_phy, &priv->debug.rx_stats);
	ath9k_cmn_debug_phy_err(priv->debug.debugfs_phy, &priv->debug.rx_stats);

	debugfs_create_file("slot", 0400, priv->debug.debugfs_phy,
			    priv, &fops_slot);
	debugfs_create_file("queue", 0400, priv->debug.debugfs_phy,
			    priv, &fops_queue);
	debugfs_create_file("debug", 0600, priv->debug.debugfs_phy,
			    priv, &fops_debug);

	ath9k_cmn_debug_base_eeprom(priv->debug.debugfs_phy, priv->ah);
	ath9k_cmn_debug_modal_eeprom(priv->debug.debugfs_phy, priv->ah);

	वापस 0;
पूर्ण
