<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007	Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2020 Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/mac80211.h>
#समावेश <net/cfg80211.h>
#समावेश "ieee80211_i.h"
#समावेश "rate.h"
#समावेश "debugfs.h"
#समावेश "debugfs_netdev.h"
#समावेश "driver-ops.h"

अटल sमाप_प्रकार ieee80211_अगर_पढ़ो(
	काष्ठा ieee80211_sub_अगर_data *sdata,
	अक्षर __user *userbuf,
	माप_प्रकार count, loff_t *ppos,
	sमाप_प्रकार (*क्रमmat)(स्थिर काष्ठा ieee80211_sub_अगर_data *, अक्षर *, पूर्णांक))
अणु
	अक्षर buf[200];
	sमाप_प्रकार ret = -EINVAL;

	पढ़ो_lock(&dev_base_lock);
	ret = (*क्रमmat)(sdata, buf, माप(buf));
	पढ़ो_unlock(&dev_base_lock);

	अगर (ret >= 0)
		ret = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, ret);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ieee80211_अगर_ग_लिखो(
	काष्ठा ieee80211_sub_अगर_data *sdata,
	स्थिर अक्षर __user *userbuf,
	माप_प्रकार count, loff_t *ppos,
	sमाप_प्रकार (*ग_लिखो)(काष्ठा ieee80211_sub_अगर_data *, स्थिर अक्षर *, पूर्णांक))
अणु
	अक्षर buf[64];
	sमाप_प्रकार ret;

	अगर (count >= माप(buf))
		वापस -E2BIG;

	अगर (copy_from_user(buf, userbuf, count))
		वापस -EFAULT;
	buf[count] = '\0';

	ret = -ENODEV;
	rtnl_lock();
	ret = (*ग_लिखो)(sdata, buf, count);
	rtnl_unlock();

	वापस ret;
पूर्ण

#घोषणा IEEE80211_IF_FMT(name, field, क्रमmat_string)			\
अटल sमाप_प्रकार ieee80211_अगर_fmt_##name(					\
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata, अक्षर *buf,		\
	पूर्णांक buflen)							\
अणु									\
	वापस scnम_लिखो(buf, buflen, क्रमmat_string, sdata->field);	\
पूर्ण
#घोषणा IEEE80211_IF_FMT_DEC(name, field)				\
		IEEE80211_IF_FMT(name, field, "%d\n")
#घोषणा IEEE80211_IF_FMT_HEX(name, field)				\
		IEEE80211_IF_FMT(name, field, "%#x\n")
#घोषणा IEEE80211_IF_FMT_LHEX(name, field)				\
		IEEE80211_IF_FMT(name, field, "%#lx\n")
#घोषणा IEEE80211_IF_FMT_SIZE(name, field)				\
		IEEE80211_IF_FMT(name, field, "%zd\n")

#घोषणा IEEE80211_IF_FMT_HEXARRAY(name, field)				\
अटल sमाप_प्रकार ieee80211_अगर_fmt_##name(					\
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata,			\
	अक्षर *buf, पूर्णांक buflen)						\
अणु									\
	अक्षर *p = buf;							\
	पूर्णांक i;								\
	क्रम (i = 0; i < माप(sdata->field); i++) अणु			\
		p += scnम_लिखो(p, buflen + buf - p, "%.2x ",		\
				 sdata->field[i]);			\
	पूर्ण								\
	p += scnम_लिखो(p, buflen + buf - p, "\n");			\
	वापस p - buf;							\
पूर्ण

#घोषणा IEEE80211_IF_FMT_ATOMIC(name, field)				\
अटल sमाप_प्रकार ieee80211_अगर_fmt_##name(					\
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata,			\
	अक्षर *buf, पूर्णांक buflen)						\
अणु									\
	वापस scnम_लिखो(buf, buflen, "%d\n", atomic_पढ़ो(&sdata->field));\
पूर्ण

#घोषणा IEEE80211_IF_FMT_MAC(name, field)				\
अटल sमाप_प्रकार ieee80211_अगर_fmt_##name(					\
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata, अक्षर *buf,		\
	पूर्णांक buflen)							\
अणु									\
	वापस scnम_लिखो(buf, buflen, "%pM\n", sdata->field);		\
पूर्ण

#घोषणा IEEE80211_IF_FMT_JIFFIES_TO_MS(name, field)			\
अटल sमाप_प्रकार ieee80211_अगर_fmt_##name(					\
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata,			\
	अक्षर *buf, पूर्णांक buflen)						\
अणु									\
	वापस scnम_लिखो(buf, buflen, "%d\n",				\
			 jअगरfies_to_msecs(sdata->field));		\
पूर्ण

#घोषणा _IEEE80211_IF_खाता_OPS(name, _पढ़ो, _ग_लिखो)			\
अटल स्थिर काष्ठा file_operations name##_ops = अणु			\
	.पढ़ो = (_पढ़ो),						\
	.ग_लिखो = (_ग_लिखो),						\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण

#घोषणा _IEEE80211_IF_खाता_R_FN(name)					\
अटल sमाप_प्रकार ieee80211_अगर_पढ़ो_##name(काष्ठा file *file,		\
					अक्षर __user *userbuf,		\
					माप_प्रकार count, loff_t *ppos)	\
अणु									\
	वापस ieee80211_अगर_पढ़ो(file->निजी_data,			\
				 userbuf, count, ppos,			\
				 ieee80211_अगर_fmt_##name);		\
पूर्ण

#घोषणा _IEEE80211_IF_खाता_W_FN(name)					\
अटल sमाप_प्रकार ieee80211_अगर_ग_लिखो_##name(काष्ठा file *file,		\
					 स्थिर अक्षर __user *userbuf,	\
					 माप_प्रकार count, loff_t *ppos)	\
अणु									\
	वापस ieee80211_अगर_ग_लिखो(file->निजी_data, userbuf, count,	\
				  ppos, ieee80211_अगर_parse_##name);	\
पूर्ण

#घोषणा IEEE80211_IF_खाता_R(name)					\
	_IEEE80211_IF_खाता_R_FN(name)					\
	_IEEE80211_IF_खाता_OPS(name, ieee80211_अगर_पढ़ो_##name, शून्य)

#घोषणा IEEE80211_IF_खाता_W(name)					\
	_IEEE80211_IF_खाता_W_FN(name)					\
	_IEEE80211_IF_खाता_OPS(name, शून्य, ieee80211_अगर_ग_लिखो_##name)

#घोषणा IEEE80211_IF_खाता_RW(name)					\
	_IEEE80211_IF_खाता_R_FN(name)					\
	_IEEE80211_IF_खाता_W_FN(name)					\
	_IEEE80211_IF_खाता_OPS(name, ieee80211_अगर_पढ़ो_##name,		\
			       ieee80211_अगर_ग_लिखो_##name)

#घोषणा IEEE80211_IF_खाता(name, field, क्रमmat)				\
	IEEE80211_IF_FMT_##क्रमmat(name, field)				\
	IEEE80211_IF_खाता_R(name)

/* common attributes */
IEEE80211_IF_खाता(rc_rateidx_mask_2ghz, rc_rateidx_mask[NL80211_BAND_2GHZ],
		  HEX);
IEEE80211_IF_खाता(rc_rateidx_mask_5ghz, rc_rateidx_mask[NL80211_BAND_5GHZ],
		  HEX);
IEEE80211_IF_खाता(rc_rateidx_mcs_mask_2ghz,
		  rc_rateidx_mcs_mask[NL80211_BAND_2GHZ], HEXARRAY);
IEEE80211_IF_खाता(rc_rateidx_mcs_mask_5ghz,
		  rc_rateidx_mcs_mask[NL80211_BAND_5GHZ], HEXARRAY);

अटल sमाप_प्रकार ieee80211_अगर_fmt_rc_rateidx_vht_mcs_mask_2ghz(
				स्थिर काष्ठा ieee80211_sub_अगर_data *sdata,
				अक्षर *buf, पूर्णांक buflen)
अणु
	पूर्णांक i, len = 0;
	स्थिर u16 *mask = sdata->rc_rateidx_vht_mcs_mask[NL80211_BAND_2GHZ];

	क्रम (i = 0; i < NL80211_VHT_NSS_MAX; i++)
		len += scnम_लिखो(buf + len, buflen - len, "%04x ", mask[i]);
	len += scnम_लिखो(buf + len, buflen - len, "\n");

	वापस len;
पूर्ण

IEEE80211_IF_खाता_R(rc_rateidx_vht_mcs_mask_2ghz);

अटल sमाप_प्रकार ieee80211_अगर_fmt_rc_rateidx_vht_mcs_mask_5ghz(
				स्थिर काष्ठा ieee80211_sub_अगर_data *sdata,
				अक्षर *buf, पूर्णांक buflen)
अणु
	पूर्णांक i, len = 0;
	स्थिर u16 *mask = sdata->rc_rateidx_vht_mcs_mask[NL80211_BAND_5GHZ];

	क्रम (i = 0; i < NL80211_VHT_NSS_MAX; i++)
		len += scnम_लिखो(buf + len, buflen - len, "%04x ", mask[i]);
	len += scnम_लिखो(buf + len, buflen - len, "\n");

	वापस len;
पूर्ण

IEEE80211_IF_खाता_R(rc_rateidx_vht_mcs_mask_5ghz);

IEEE80211_IF_खाता(flags, flags, HEX);
IEEE80211_IF_खाता(state, state, LHEX);
IEEE80211_IF_खाता(txघातer, vअगर.bss_conf.txघातer, DEC);
IEEE80211_IF_खाता(ap_घातer_level, ap_घातer_level, DEC);
IEEE80211_IF_खाता(user_घातer_level, user_घातer_level, DEC);

अटल sमाप_प्रकार
ieee80211_अगर_fmt_hw_queues(स्थिर काष्ठा ieee80211_sub_अगर_data *sdata,
			   अक्षर *buf, पूर्णांक buflen)
अणु
	पूर्णांक len;

	len = scnम_लिखो(buf, buflen, "AC queues: VO:%d VI:%d BE:%d BK:%d\n",
			sdata->vअगर.hw_queue[IEEE80211_AC_VO],
			sdata->vअगर.hw_queue[IEEE80211_AC_VI],
			sdata->vअगर.hw_queue[IEEE80211_AC_BE],
			sdata->vअगर.hw_queue[IEEE80211_AC_BK]);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		len += scnम_लिखो(buf + len, buflen - len, "cab queue: %d\n",
				 sdata->vअगर.cab_queue);

	वापस len;
पूर्ण
IEEE80211_IF_खाता_R(hw_queues);

/* STA attributes */
IEEE80211_IF_खाता(bssid, u.mgd.bssid, MAC);
IEEE80211_IF_खाता(aid, vअगर.bss_conf.aid, DEC);
IEEE80211_IF_खाता(beacon_समयout, u.mgd.beacon_समयout, JIFFIES_TO_MS);

अटल पूर्णांक ieee80211_set_smps(काष्ठा ieee80211_sub_अगर_data *sdata,
			      क्रमागत ieee80211_smps_mode smps_mode)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक err;

	अगर (!(local->hw.wiphy->features & NL80211_FEATURE_STATIC_SMPS) &&
	    smps_mode == IEEE80211_SMPS_STATIC)
		वापस -EINVAL;

	/* स्वतः should be dynamic अगर in PS mode */
	अगर (!(local->hw.wiphy->features & NL80211_FEATURE_DYNAMIC_SMPS) &&
	    (smps_mode == IEEE80211_SMPS_DYNAMIC ||
	     smps_mode == IEEE80211_SMPS_AUTOMATIC))
		वापस -EINVAL;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	sdata_lock(sdata);
	err = __ieee80211_request_smps_mgd(sdata, smps_mode);
	sdata_unlock(sdata);

	वापस err;
पूर्ण

अटल स्थिर अक्षर *smps_modes[IEEE80211_SMPS_NUM_MODES] = अणु
	[IEEE80211_SMPS_AUTOMATIC] = "auto",
	[IEEE80211_SMPS_OFF] = "off",
	[IEEE80211_SMPS_STATIC] = "static",
	[IEEE80211_SMPS_DYNAMIC] = "dynamic",
पूर्ण;

अटल sमाप_प्रकार ieee80211_अगर_fmt_smps(स्थिर काष्ठा ieee80211_sub_अगर_data *sdata,
				     अक्षर *buf, पूर्णांक buflen)
अणु
	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION)
		वापस snम_लिखो(buf, buflen, "request: %s\nused: %s\n",
				smps_modes[sdata->u.mgd.req_smps],
				smps_modes[sdata->smps_mode]);
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार ieee80211_अगर_parse_smps(काष्ठा ieee80211_sub_अगर_data *sdata,
				       स्थिर अक्षर *buf, पूर्णांक buflen)
अणु
	क्रमागत ieee80211_smps_mode mode;

	क्रम (mode = 0; mode < IEEE80211_SMPS_NUM_MODES; mode++) अणु
		अगर (म_भेदन(buf, smps_modes[mode], buflen) == 0) अणु
			पूर्णांक err = ieee80211_set_smps(sdata, mode);
			अगर (!err)
				वापस buflen;
			वापस err;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
IEEE80211_IF_खाता_RW(smps);

अटल sमाप_प्रकार ieee80211_अगर_parse_tkip_mic_test(
	काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	u8 addr[ETH_ALEN];
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	__le16 fc;

	अगर (!mac_pton(buf, addr))
		वापस -EINVAL;

	अगर (!ieee80211_sdata_running(sdata))
		वापस -ENOTCONN;

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + 24 + 100);
	अगर (!skb)
		वापस -ENOMEM;
	skb_reserve(skb, local->hw.extra_tx_headroom);

	hdr = skb_put_zero(skb, 24);
	fc = cpu_to_le16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA);

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP:
		fc |= cpu_to_le16(IEEE80211_FCTL_FROMDS);
		/* DA BSSID SA */
		स_नकल(hdr->addr1, addr, ETH_ALEN);
		स_नकल(hdr->addr2, sdata->vअगर.addr, ETH_ALEN);
		स_नकल(hdr->addr3, sdata->vअगर.addr, ETH_ALEN);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		fc |= cpu_to_le16(IEEE80211_FCTL_TODS);
		/* BSSID SA DA */
		sdata_lock(sdata);
		अगर (!sdata->u.mgd.associated) अणु
			sdata_unlock(sdata);
			dev_kमुक्त_skb(skb);
			वापस -ENOTCONN;
		पूर्ण
		स_नकल(hdr->addr1, sdata->u.mgd.associated->bssid, ETH_ALEN);
		स_नकल(hdr->addr2, sdata->vअगर.addr, ETH_ALEN);
		स_नकल(hdr->addr3, addr, ETH_ALEN);
		sdata_unlock(sdata);
		अवरोध;
	शेष:
		dev_kमुक्त_skb(skb);
		वापस -EOPNOTSUPP;
	पूर्ण
	hdr->frame_control = fc;

	/*
	 * Add some length to the test frame to make it look bit more valid.
	 * The exact contents करोes not matter since the recipient is required
	 * to drop this because of the Michael MIC failure.
	 */
	skb_put_zero(skb, 50);

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_TKIP_MIC_FAILURE;

	ieee80211_tx_skb(sdata, skb);

	वापस buflen;
पूर्ण
IEEE80211_IF_खाता_W(tkip_mic_test);

अटल sमाप_प्रकार ieee80211_अगर_parse_beacon_loss(
	काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर अक्षर *buf, पूर्णांक buflen)
अणु
	अगर (!ieee80211_sdata_running(sdata) || !sdata->vअगर.bss_conf.assoc)
		वापस -ENOTCONN;

	ieee80211_beacon_loss(&sdata->vअगर);

	वापस buflen;
पूर्ण
IEEE80211_IF_खाता_W(beacon_loss);

अटल sमाप_प्रकार ieee80211_अगर_fmt_uapsd_queues(
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata, अक्षर *buf, पूर्णांक buflen)
अणु
	स्थिर काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	वापस snम_लिखो(buf, buflen, "0x%x\n", अगरmgd->uapsd_queues);
पूर्ण

अटल sमाप_प्रकार ieee80211_अगर_parse_uapsd_queues(
	काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u8 val;
	पूर्णांक ret;

	ret = kstrtou8(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val & ~IEEE80211_WMM_IE_STA_QOSINFO_AC_MASK)
		वापस -दुस्फल;

	अगरmgd->uapsd_queues = val;

	वापस buflen;
पूर्ण
IEEE80211_IF_खाता_RW(uapsd_queues);

अटल sमाप_प्रकार ieee80211_अगर_fmt_uapsd_max_sp_len(
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata, अक्षर *buf, पूर्णांक buflen)
अणु
	स्थिर काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	वापस snम_लिखो(buf, buflen, "0x%x\n", अगरmgd->uapsd_max_sp_len);
पूर्ण

अटल sमाप_प्रकार ieee80211_अगर_parse_uapsd_max_sp_len(
	काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		वापस -EINVAL;

	अगर (val & ~IEEE80211_WMM_IE_STA_QOSINFO_SP_MASK)
		वापस -दुस्फल;

	अगरmgd->uapsd_max_sp_len = val;

	वापस buflen;
पूर्ण
IEEE80211_IF_खाता_RW(uapsd_max_sp_len);

अटल sमाप_प्रकार ieee80211_अगर_fmt_tdls_wider_bw(
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata, अक्षर *buf, पूर्णांक buflen)
अणु
	स्थिर काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	bool tdls_wider_bw;

	tdls_wider_bw = ieee80211_hw_check(&sdata->local->hw, TDLS_WIDER_BW) &&
			!अगरmgd->tdls_wider_bw_prohibited;

	वापस snम_लिखो(buf, buflen, "%d\n", tdls_wider_bw);
पूर्ण

अटल sमाप_प्रकार ieee80211_अगर_parse_tdls_wider_bw(
	काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u8 val;
	पूर्णांक ret;

	ret = kstrtou8(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगरmgd->tdls_wider_bw_prohibited = !val;
	वापस buflen;
पूर्ण
IEEE80211_IF_खाता_RW(tdls_wider_bw);

/* AP attributes */
IEEE80211_IF_खाता(num_mcast_sta, u.ap.num_mcast_sta, ATOMIC);
IEEE80211_IF_खाता(num_sta_ps, u.ap.ps.num_sta_ps, ATOMIC);
IEEE80211_IF_खाता(dtim_count, u.ap.ps.dtim_count, DEC);
IEEE80211_IF_खाता(num_mcast_sta_vlan, u.vlan.num_mcast_sta, ATOMIC);

अटल sमाप_प्रकार ieee80211_अगर_fmt_num_buffered_multicast(
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata, अक्षर *buf, पूर्णांक buflen)
अणु
	वापस scnम_लिखो(buf, buflen, "%u\n",
			 skb_queue_len(&sdata->u.ap.ps.bc_buf));
पूर्ण
IEEE80211_IF_खाता_R(num_buffered_multicast);

अटल sमाप_प्रकार ieee80211_अगर_fmt_aqm(
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata, अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा txq_info *txqi;
	पूर्णांक len;

	अगर (!sdata->vअगर.txq)
		वापस 0;

	txqi = to_txq_info(sdata->vअगर.txq);

	spin_lock_bh(&local->fq.lock);
	rcu_पढ़ो_lock();

	len = scnम_लिखो(buf,
			buflen,
			"ac backlog-bytes backlog-packets new-flows drops marks overlimit collisions tx-bytes tx-packets\n"
			"%u %u %u %u %u %u %u %u %u %u\n",
			txqi->txq.ac,
			txqi->tin.backlog_bytes,
			txqi->tin.backlog_packets,
			txqi->tin.flows,
			txqi->cstats.drop_count,
			txqi->cstats.ecn_mark,
			txqi->tin.overlimit,
			txqi->tin.collisions,
			txqi->tin.tx_bytes,
			txqi->tin.tx_packets);

	rcu_पढ़ो_unlock();
	spin_unlock_bh(&local->fq.lock);

	वापस len;
पूर्ण
IEEE80211_IF_खाता_R(aqm);

IEEE80211_IF_खाता(multicast_to_unicast, u.ap.multicast_to_unicast, HEX);

/* IBSS attributes */
अटल sमाप_प्रकार ieee80211_अगर_fmt_tsf(
	स्थिर काष्ठा ieee80211_sub_अगर_data *sdata, अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	u64 tsf;

	tsf = drv_get_tsf(local, (काष्ठा ieee80211_sub_अगर_data *)sdata);

	वापस scnम_लिखो(buf, buflen, "0x%016llx\n", (अचिन्हित दीर्घ दीर्घ) tsf);
पूर्ण

अटल sमाप_प्रकार ieee80211_अगर_parse_tsf(
	काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	अचिन्हित दीर्घ दीर्घ tsf;
	पूर्णांक ret;
	पूर्णांक tsf_is_delta = 0;

	अगर (म_भेदन(buf, "reset", 5) == 0) अणु
		अगर (local->ops->reset_tsf) अणु
			drv_reset_tsf(local, sdata);
			wiphy_info(local->hw.wiphy, "debugfs reset TSF\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (buflen > 10 && buf[1] == '=') अणु
			अगर (buf[0] == '+')
				tsf_is_delta = 1;
			अन्यथा अगर (buf[0] == '-')
				tsf_is_delta = -1;
			अन्यथा
				वापस -EINVAL;
			buf += 2;
		पूर्ण
		ret = kम_से_अदीर्घl(buf, 10, &tsf);
		अगर (ret < 0)
			वापस ret;
		अगर (tsf_is_delta && local->ops->offset_tsf) अणु
			drv_offset_tsf(local, sdata, tsf_is_delta * tsf);
			wiphy_info(local->hw.wiphy,
				   "debugfs offset TSF by %018lld\n",
				   tsf_is_delta * tsf);
		पूर्ण अन्यथा अगर (local->ops->set_tsf) अणु
			अगर (tsf_is_delta)
				tsf = drv_get_tsf(local, sdata) +
				      tsf_is_delta * tsf;
			drv_set_tsf(local, sdata, tsf);
			wiphy_info(local->hw.wiphy,
				   "debugfs set TSF to %#018llx\n", tsf);
		पूर्ण
	पूर्ण

	ieee80211_recalc_dtim(local, sdata);
	वापस buflen;
पूर्ण
IEEE80211_IF_खाता_RW(tsf);


#अगर_घोषित CONFIG_MAC80211_MESH
IEEE80211_IF_खाता(estab_plinks, u.mesh.estab_plinks, ATOMIC);

/* Mesh stats attributes */
IEEE80211_IF_खाता(fwded_mcast, u.mesh.mshstats.fwded_mcast, DEC);
IEEE80211_IF_खाता(fwded_unicast, u.mesh.mshstats.fwded_unicast, DEC);
IEEE80211_IF_खाता(fwded_frames, u.mesh.mshstats.fwded_frames, DEC);
IEEE80211_IF_खाता(dropped_frames_ttl, u.mesh.mshstats.dropped_frames_ttl, DEC);
IEEE80211_IF_खाता(dropped_frames_congestion,
		  u.mesh.mshstats.dropped_frames_congestion, DEC);
IEEE80211_IF_खाता(dropped_frames_no_route,
		  u.mesh.mshstats.dropped_frames_no_route, DEC);

/* Mesh parameters */
IEEE80211_IF_खाता(करोt11MeshMaxRetries,
		  u.mesh.mshcfg.करोt11MeshMaxRetries, DEC);
IEEE80211_IF_खाता(करोt11MeshRetryTimeout,
		  u.mesh.mshcfg.करोt11MeshRetryTimeout, DEC);
IEEE80211_IF_खाता(करोt11MeshConfirmTimeout,
		  u.mesh.mshcfg.करोt11MeshConfirmTimeout, DEC);
IEEE80211_IF_खाता(करोt11MeshHoldingTimeout,
		  u.mesh.mshcfg.करोt11MeshHoldingTimeout, DEC);
IEEE80211_IF_खाता(करोt11MeshTTL, u.mesh.mshcfg.करोt11MeshTTL, DEC);
IEEE80211_IF_खाता(element_ttl, u.mesh.mshcfg.element_ttl, DEC);
IEEE80211_IF_खाता(स्वतः_खोलो_plinks, u.mesh.mshcfg.स्वतः_खोलो_plinks, DEC);
IEEE80211_IF_खाता(करोt11MeshMaxPeerLinks,
		  u.mesh.mshcfg.करोt11MeshMaxPeerLinks, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMPactivePathTimeout,
		  u.mesh.mshcfg.करोt11MeshHWMPactivePathTimeout, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMPpreqMinInterval,
		  u.mesh.mshcfg.करोt11MeshHWMPpreqMinInterval, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMPperrMinInterval,
		  u.mesh.mshcfg.करोt11MeshHWMPperrMinInterval, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMPnetDiameterTraversalTime,
		  u.mesh.mshcfg.करोt11MeshHWMPnetDiameterTraversalTime, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMPmaxPREQretries,
		  u.mesh.mshcfg.करोt11MeshHWMPmaxPREQretries, DEC);
IEEE80211_IF_खाता(path_refresh_समय,
		  u.mesh.mshcfg.path_refresh_समय, DEC);
IEEE80211_IF_खाता(min_discovery_समयout,
		  u.mesh.mshcfg.min_discovery_समयout, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMPRootMode,
		  u.mesh.mshcfg.करोt11MeshHWMPRootMode, DEC);
IEEE80211_IF_खाता(करोt11MeshGateAnnouncementProtocol,
		  u.mesh.mshcfg.करोt11MeshGateAnnouncementProtocol, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMPRannInterval,
		  u.mesh.mshcfg.करोt11MeshHWMPRannInterval, DEC);
IEEE80211_IF_खाता(करोt11MeshForwarding, u.mesh.mshcfg.करोt11MeshForwarding, DEC);
IEEE80211_IF_खाता(rssi_threshold, u.mesh.mshcfg.rssi_threshold, DEC);
IEEE80211_IF_खाता(ht_opmode, u.mesh.mshcfg.ht_opmode, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMPactivePathToRootTimeout,
		  u.mesh.mshcfg.करोt11MeshHWMPactivePathToRootTimeout, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMProotInterval,
		  u.mesh.mshcfg.करोt11MeshHWMProotInterval, DEC);
IEEE80211_IF_खाता(करोt11MeshHWMPconfirmationInterval,
		  u.mesh.mshcfg.करोt11MeshHWMPconfirmationInterval, DEC);
IEEE80211_IF_खाता(घातer_mode, u.mesh.mshcfg.घातer_mode, DEC);
IEEE80211_IF_खाता(करोt11MeshAwakeWinकरोwDuration,
		  u.mesh.mshcfg.करोt11MeshAwakeWinकरोwDuration, DEC);
IEEE80211_IF_खाता(करोt11MeshConnectedToMeshGate,
		  u.mesh.mshcfg.करोt11MeshConnectedToMeshGate, DEC);
IEEE80211_IF_खाता(करोt11MeshNolearn, u.mesh.mshcfg.करोt11MeshNolearn, DEC);
IEEE80211_IF_खाता(करोt11MeshConnectedToAuthServer,
		  u.mesh.mshcfg.करोt11MeshConnectedToAuthServer, DEC);
#पूर्ण_अगर

#घोषणा DEBUGFS_ADD_MODE(name, mode) \
	debugfs_create_file(#name, mode, sdata->vअगर.debugfs_dir, \
			    sdata, &name##_ops)

#घोषणा DEBUGFS_ADD(name) DEBUGFS_ADD_MODE(name, 0400)

अटल व्योम add_common_files(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	DEBUGFS_ADD(rc_rateidx_mask_2ghz);
	DEBUGFS_ADD(rc_rateidx_mask_5ghz);
	DEBUGFS_ADD(rc_rateidx_mcs_mask_2ghz);
	DEBUGFS_ADD(rc_rateidx_mcs_mask_5ghz);
	DEBUGFS_ADD(rc_rateidx_vht_mcs_mask_2ghz);
	DEBUGFS_ADD(rc_rateidx_vht_mcs_mask_5ghz);
	DEBUGFS_ADD(hw_queues);

	अगर (sdata->local->ops->wake_tx_queue &&
	    sdata->vअगर.type != NL80211_IFTYPE_P2P_DEVICE &&
	    sdata->vअगर.type != NL80211_IFTYPE_न_अंक)
		DEBUGFS_ADD(aqm);
पूर्ण

अटल व्योम add_sta_files(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	DEBUGFS_ADD(bssid);
	DEBUGFS_ADD(aid);
	DEBUGFS_ADD(beacon_समयout);
	DEBUGFS_ADD_MODE(smps, 0600);
	DEBUGFS_ADD_MODE(tkip_mic_test, 0200);
	DEBUGFS_ADD_MODE(beacon_loss, 0200);
	DEBUGFS_ADD_MODE(uapsd_queues, 0600);
	DEBUGFS_ADD_MODE(uapsd_max_sp_len, 0600);
	DEBUGFS_ADD_MODE(tdls_wider_bw, 0600);
पूर्ण

अटल व्योम add_ap_files(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	DEBUGFS_ADD(num_mcast_sta);
	DEBUGFS_ADD_MODE(smps, 0600);
	DEBUGFS_ADD(num_sta_ps);
	DEBUGFS_ADD(dtim_count);
	DEBUGFS_ADD(num_buffered_multicast);
	DEBUGFS_ADD_MODE(tkip_mic_test, 0200);
	DEBUGFS_ADD_MODE(multicast_to_unicast, 0600);
पूर्ण

अटल व्योम add_vlan_files(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	/* add num_mcast_sta_vlan using name num_mcast_sta */
	debugfs_create_file("num_mcast_sta", 0400, sdata->vअगर.debugfs_dir,
			    sdata, &num_mcast_sta_vlan_ops);
पूर्ण

अटल व्योम add_ibss_files(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	DEBUGFS_ADD_MODE(tsf, 0600);
पूर्ण

#अगर_घोषित CONFIG_MAC80211_MESH

अटल व्योम add_mesh_files(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	DEBUGFS_ADD_MODE(tsf, 0600);
	DEBUGFS_ADD_MODE(estab_plinks, 0400);
पूर्ण

अटल व्योम add_mesh_stats(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा dentry *dir = debugfs_create_dir("mesh_stats",
						sdata->vअगर.debugfs_dir);
#घोषणा MESHSTATS_ADD(name)\
	debugfs_create_file(#name, 0400, dir, sdata, &name##_ops)

	MESHSTATS_ADD(fwded_mcast);
	MESHSTATS_ADD(fwded_unicast);
	MESHSTATS_ADD(fwded_frames);
	MESHSTATS_ADD(dropped_frames_ttl);
	MESHSTATS_ADD(dropped_frames_no_route);
	MESHSTATS_ADD(dropped_frames_congestion);
#अघोषित MESHSTATS_ADD
पूर्ण

अटल व्योम add_mesh_config(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा dentry *dir = debugfs_create_dir("mesh_config",
						sdata->vअगर.debugfs_dir);

#घोषणा MESHPARAMS_ADD(name) \
	debugfs_create_file(#name, 0600, dir, sdata, &name##_ops)

	MESHPARAMS_ADD(करोt11MeshMaxRetries);
	MESHPARAMS_ADD(करोt11MeshRetryTimeout);
	MESHPARAMS_ADD(करोt11MeshConfirmTimeout);
	MESHPARAMS_ADD(करोt11MeshHoldingTimeout);
	MESHPARAMS_ADD(करोt11MeshTTL);
	MESHPARAMS_ADD(element_ttl);
	MESHPARAMS_ADD(स्वतः_खोलो_plinks);
	MESHPARAMS_ADD(करोt11MeshMaxPeerLinks);
	MESHPARAMS_ADD(करोt11MeshHWMPactivePathTimeout);
	MESHPARAMS_ADD(करोt11MeshHWMPpreqMinInterval);
	MESHPARAMS_ADD(करोt11MeshHWMPperrMinInterval);
	MESHPARAMS_ADD(करोt11MeshHWMPnetDiameterTraversalTime);
	MESHPARAMS_ADD(करोt11MeshHWMPmaxPREQretries);
	MESHPARAMS_ADD(path_refresh_समय);
	MESHPARAMS_ADD(min_discovery_समयout);
	MESHPARAMS_ADD(करोt11MeshHWMPRootMode);
	MESHPARAMS_ADD(करोt11MeshHWMPRannInterval);
	MESHPARAMS_ADD(करोt11MeshForwarding);
	MESHPARAMS_ADD(करोt11MeshGateAnnouncementProtocol);
	MESHPARAMS_ADD(rssi_threshold);
	MESHPARAMS_ADD(ht_opmode);
	MESHPARAMS_ADD(करोt11MeshHWMPactivePathToRootTimeout);
	MESHPARAMS_ADD(करोt11MeshHWMProotInterval);
	MESHPARAMS_ADD(करोt11MeshHWMPconfirmationInterval);
	MESHPARAMS_ADD(घातer_mode);
	MESHPARAMS_ADD(करोt11MeshAwakeWinकरोwDuration);
	MESHPARAMS_ADD(करोt11MeshConnectedToMeshGate);
	MESHPARAMS_ADD(करोt11MeshNolearn);
	MESHPARAMS_ADD(करोt11MeshConnectedToAuthServer);
#अघोषित MESHPARAMS_ADD
पूर्ण
#पूर्ण_अगर

अटल व्योम add_files(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (!sdata->vअगर.debugfs_dir)
		वापस;

	DEBUGFS_ADD(flags);
	DEBUGFS_ADD(state);
	DEBUGFS_ADD(txघातer);
	DEBUGFS_ADD(user_घातer_level);
	DEBUGFS_ADD(ap_घातer_level);

	अगर (sdata->vअगर.type != NL80211_IFTYPE_MONITOR)
		add_common_files(sdata);

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
#अगर_घोषित CONFIG_MAC80211_MESH
		add_mesh_files(sdata);
		add_mesh_stats(sdata);
		add_mesh_config(sdata);
#पूर्ण_अगर
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		add_sta_files(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		add_ibss_files(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		add_ap_files(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_AP_VLAN:
		add_vlan_files(sdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम ieee80211_debugfs_add_netdev(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अक्षर buf[10+IFNAMSIZ];

	प्र_लिखो(buf, "netdev:%s", sdata->name);
	sdata->vअगर.debugfs_dir = debugfs_create_dir(buf,
		sdata->local->hw.wiphy->debugfsdir);
	sdata->debugfs.subdir_stations = debugfs_create_dir("stations",
							sdata->vअगर.debugfs_dir);
	add_files(sdata);
पूर्ण

व्योम ieee80211_debugfs_हटाओ_netdev(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (!sdata->vअगर.debugfs_dir)
		वापस;

	debugfs_हटाओ_recursive(sdata->vअगर.debugfs_dir);
	sdata->vअगर.debugfs_dir = शून्य;
	sdata->debugfs.subdir_stations = शून्य;
पूर्ण

व्योम ieee80211_debugfs_नाम_netdev(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा dentry *dir;
	अक्षर buf[10 + IFNAMSIZ];

	dir = sdata->vअगर.debugfs_dir;

	अगर (IS_ERR_OR_शून्य(dir))
		वापस;

	प्र_लिखो(buf, "netdev:%s", sdata->name);
	debugfs_नाम(dir->d_parent, dir, dir->d_parent, buf);
पूर्ण
