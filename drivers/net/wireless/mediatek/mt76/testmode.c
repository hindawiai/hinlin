<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 Felix Fietkau <nbd@nbd.name> */
#समावेश "mt76.h"

अटल स्थिर काष्ठा nla_policy mt76_पंचांग_policy[NUM_MT76_TM_ATTRS] = अणु
	[MT76_TM_ATTR_RESET] = अणु .type = NLA_FLAG पूर्ण,
	[MT76_TM_ATTR_STATE] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_COUNT] = अणु .type = NLA_U32 पूर्ण,
	[MT76_TM_ATTR_TX_RATE_MODE] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_RATE_NSS] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_RATE_IDX] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_RATE_SGI] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_RATE_LDPC] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_RATE_STBC] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_LTF] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_ANTENNA] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_SPE_IDX] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_POWER_CONTROL] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_POWER] = अणु .type = NLA_NESTED पूर्ण,
	[MT76_TM_ATTR_TX_DUTY_CYCLE] = अणु .type = NLA_U8 पूर्ण,
	[MT76_TM_ATTR_TX_IPG] = अणु .type = NLA_U32 पूर्ण,
	[MT76_TM_ATTR_TX_TIME] = अणु .type = NLA_U32 पूर्ण,
	[MT76_TM_ATTR_FREQ_OFFSET] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

व्योम mt76_tesपंचांगode_tx_pending(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा mt76_wcid *wcid = &dev->global_wcid;
	काष्ठा sk_buff *skb = td->tx_skb;
	काष्ठा mt76_queue *q;
	u16 tx_queued_limit;
	पूर्णांक qid;

	अगर (!skb || !td->tx_pending)
		वापस;

	qid = skb_get_queue_mapping(skb);
	q = phy->q_tx[qid];

	tx_queued_limit = td->tx_queued_limit ? td->tx_queued_limit : 1000;

	spin_lock_bh(&q->lock);

	जबतक (td->tx_pending > 0 &&
	       td->tx_queued - td->tx_करोne < tx_queued_limit &&
	       q->queued < q->ndesc / 2) अणु
		पूर्णांक ret;

		ret = dev->queue_ops->tx_queue_skb(dev, q, skb_get(skb), wcid,
						   शून्य);
		अगर (ret < 0)
			अवरोध;

		td->tx_pending--;
		td->tx_queued++;
	पूर्ण

	dev->queue_ops->kick(dev, q);

	spin_unlock_bh(&q->lock);
पूर्ण

अटल u32
mt76_tesपंचांगode_max_mpdu_len(काष्ठा mt76_phy *phy, u8 tx_rate_mode)
अणु
	चयन (tx_rate_mode) अणु
	हाल MT76_TM_TX_MODE_HT:
		वापस IEEE80211_MAX_MPDU_LEN_HT_7935;
	हाल MT76_TM_TX_MODE_VHT:
	हाल MT76_TM_TX_MODE_HE_SU:
	हाल MT76_TM_TX_MODE_HE_EXT_SU:
	हाल MT76_TM_TX_MODE_HE_TB:
	हाल MT76_TM_TX_MODE_HE_MU:
		अगर (phy->sband_5g.sband.vht_cap.cap &
		    IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991)
			वापस IEEE80211_MAX_MPDU_LEN_VHT_7991;
		वापस IEEE80211_MAX_MPDU_LEN_VHT_11454;
	हाल MT76_TM_TX_MODE_CCK:
	हाल MT76_TM_TX_MODE_OFDM:
	शेष:
		वापस IEEE80211_MAX_FRAME_LEN;
	पूर्ण
पूर्ण

अटल व्योम
mt76_tesपंचांगode_मुक्त_skb(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	काष्ठा sk_buff *skb = td->tx_skb;

	अगर (!skb)
		वापस;

	अगर (skb_has_frag_list(skb)) अणु
		kमुक्त_skb_list(skb_shinfo(skb)->frag_list);
		skb_shinfo(skb)->frag_list = शून्य;
	पूर्ण

	dev_kमुक्त_skb(skb);
	td->tx_skb = शून्य;
पूर्ण

पूर्णांक mt76_tesपंचांगode_alloc_skb(काष्ठा mt76_phy *phy, u32 len)
अणु
#घोषणा MT_TXP_MAX_LEN	4095
	u16 fc = IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA |
		 IEEE80211_FCTL_FROMDS;
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	bool ext_phy = phy != &phy->dev->phy;
	काष्ठा sk_buff **frag_tail, *head;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_hdr *hdr;
	u32 max_len, head_len;
	पूर्णांक nfrags, i;

	max_len = mt76_tesपंचांगode_max_mpdu_len(phy, td->tx_rate_mode);
	अगर (len > max_len)
		len = max_len;
	अन्यथा अगर (len < माप(काष्ठा ieee80211_hdr))
		len = माप(काष्ठा ieee80211_hdr);

	nfrags = len / MT_TXP_MAX_LEN;
	head_len = nfrags ? MT_TXP_MAX_LEN : len;

	अगर (len > IEEE80211_MAX_FRAME_LEN)
		fc |= IEEE80211_STYPE_QOS_DATA;

	head = alloc_skb(head_len, GFP_KERNEL);
	अगर (!head)
		वापस -ENOMEM;

	hdr = __skb_put_zero(head, head_len);
	hdr->frame_control = cpu_to_le16(fc);
	स_नकल(hdr->addr1, phy->macaddr, माप(phy->macaddr));
	स_नकल(hdr->addr2, phy->macaddr, माप(phy->macaddr));
	स_नकल(hdr->addr3, phy->macaddr, माप(phy->macaddr));
	skb_set_queue_mapping(head, IEEE80211_AC_BE);

	info = IEEE80211_SKB_CB(head);
	info->flags = IEEE80211_TX_CTL_INJECTED |
		      IEEE80211_TX_CTL_NO_ACK |
		      IEEE80211_TX_CTL_NO_PS_BUFFER;

	अगर (ext_phy)
		info->hw_queue |= MT_TX_HW_QUEUE_EXT_PHY;

	frag_tail = &skb_shinfo(head)->frag_list;

	क्रम (i = 0; i < nfrags; i++) अणु
		काष्ठा sk_buff *frag;
		u16 frag_len;

		अगर (i == nfrags - 1)
			frag_len = len % MT_TXP_MAX_LEN;
		अन्यथा
			frag_len = MT_TXP_MAX_LEN;

		frag = alloc_skb(frag_len, GFP_KERNEL);
		अगर (!frag)
			वापस -ENOMEM;

		__skb_put_zero(frag, frag_len);
		head->len += frag->len;
		head->data_len += frag->len;

		अगर (*frag_tail) अणु
			(*frag_tail)->next = frag;
			frag_tail = &frag;
		पूर्ण अन्यथा अणु
			*frag_tail = frag;
		पूर्ण
	पूर्ण

	mt76_tesपंचांगode_मुक्त_skb(phy);
	td->tx_skb = head;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mt76_tesपंचांगode_alloc_skb);

अटल पूर्णांक
mt76_tesपंचांगode_tx_init(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_tx_rate *rate;
	u8 max_nss = hweight8(phy->antenna_mask);
	पूर्णांक ret;

	ret = mt76_tesपंचांगode_alloc_skb(phy, td->tx_mpdu_len);
	अगर (ret)
		वापस ret;

	अगर (td->tx_rate_mode > MT76_TM_TX_MODE_VHT)
		जाओ out;

	अगर (td->tx_antenna_mask)
		max_nss = min_t(u8, max_nss, hweight8(td->tx_antenna_mask));

	info = IEEE80211_SKB_CB(td->tx_skb);
	rate = &info->control.rates[0];
	rate->count = 1;
	rate->idx = td->tx_rate_idx;

	चयन (td->tx_rate_mode) अणु
	हाल MT76_TM_TX_MODE_CCK:
		अगर (phy->chandef.chan->band != NL80211_BAND_2GHZ)
			वापस -EINVAL;

		अगर (rate->idx > 4)
			वापस -EINVAL;
		अवरोध;
	हाल MT76_TM_TX_MODE_OFDM:
		अगर (phy->chandef.chan->band != NL80211_BAND_2GHZ)
			अवरोध;

		अगर (rate->idx > 8)
			वापस -EINVAL;

		rate->idx += 4;
		अवरोध;
	हाल MT76_TM_TX_MODE_HT:
		अगर (rate->idx > 8 * max_nss &&
			!(rate->idx == 32 &&
			  phy->chandef.width >= NL80211_CHAN_WIDTH_40))
			वापस -EINVAL;

		rate->flags |= IEEE80211_TX_RC_MCS;
		अवरोध;
	हाल MT76_TM_TX_MODE_VHT:
		अगर (rate->idx > 9)
			वापस -EINVAL;

		अगर (td->tx_rate_nss > max_nss)
			वापस -EINVAL;

		ieee80211_rate_set_vht(rate, td->tx_rate_idx, td->tx_rate_nss);
		rate->flags |= IEEE80211_TX_RC_VHT_MCS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (td->tx_rate_sgi)
		rate->flags |= IEEE80211_TX_RC_SHORT_GI;

	अगर (td->tx_rate_ldpc)
		info->flags |= IEEE80211_TX_CTL_LDPC;

	अगर (td->tx_rate_stbc)
		info->flags |= IEEE80211_TX_CTL_STBC;

	अगर (td->tx_rate_mode >= MT76_TM_TX_MODE_HT) अणु
		चयन (phy->chandef.width) अणु
		हाल NL80211_CHAN_WIDTH_40:
			rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_80:
			rate->flags |= IEEE80211_TX_RC_80_MHZ_WIDTH;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_80P80:
		हाल NL80211_CHAN_WIDTH_160:
			rate->flags |= IEEE80211_TX_RC_160_MHZ_WIDTH;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस 0;
पूर्ण

अटल व्योम
mt76_tesपंचांगode_tx_start(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	काष्ठा mt76_dev *dev = phy->dev;

	td->tx_queued = 0;
	td->tx_करोne = 0;
	td->tx_pending = td->tx_count;
	mt76_worker_schedule(&dev->tx_worker);
पूर्ण

अटल व्योम
mt76_tesपंचांगode_tx_stop(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	काष्ठा mt76_dev *dev = phy->dev;

	mt76_worker_disable(&dev->tx_worker);

	td->tx_pending = 0;

	mt76_worker_enable(&dev->tx_worker);

	रुको_event_समयout(dev->tx_रुको, td->tx_करोne == td->tx_queued,
			   MT76_TM_TIMEOUT * HZ);

	mt76_tesपंचांगode_मुक्त_skb(phy);
पूर्ण

अटल अंतरभूत व्योम
mt76_tesपंचांगode_param_set(काष्ठा mt76_tesपंचांगode_data *td, u16 idx)
अणु
	td->param_set[idx / 32] |= BIT(idx % 32);
पूर्ण

अटल अंतरभूत bool
mt76_tesपंचांगode_param_present(काष्ठा mt76_tesपंचांगode_data *td, u16 idx)
अणु
	वापस td->param_set[idx / 32] & BIT(idx % 32);
पूर्ण

अटल व्योम
mt76_tesपंचांगode_init_शेषs(काष्ठा mt76_phy *phy)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;

	अगर (td->tx_mpdu_len > 0)
		वापस;

	td->tx_mpdu_len = 1024;
	td->tx_count = 1;
	td->tx_rate_mode = MT76_TM_TX_MODE_OFDM;
	td->tx_rate_nss = 1;
पूर्ण

अटल पूर्णांक
__mt76_tesपंचांगode_set_state(काष्ठा mt76_phy *phy, क्रमागत mt76_tesपंचांगode_state state)
अणु
	क्रमागत mt76_tesपंचांगode_state prev_state = phy->test.state;
	काष्ठा mt76_dev *dev = phy->dev;
	पूर्णांक err;

	अगर (prev_state == MT76_TM_STATE_TX_FRAMES)
		mt76_tesपंचांगode_tx_stop(phy);

	अगर (state == MT76_TM_STATE_TX_FRAMES) अणु
		err = mt76_tesपंचांगode_tx_init(phy);
		अगर (err)
			वापस err;
	पूर्ण

	err = dev->test_ops->set_state(phy, state);
	अगर (err) अणु
		अगर (state == MT76_TM_STATE_TX_FRAMES)
			mt76_tesपंचांगode_tx_stop(phy);

		वापस err;
	पूर्ण

	अगर (state == MT76_TM_STATE_TX_FRAMES)
		mt76_tesपंचांगode_tx_start(phy);
	अन्यथा अगर (state == MT76_TM_STATE_RX_FRAMES) अणु
		स_रखो(&phy->test.rx_stats, 0, माप(phy->test.rx_stats));
	पूर्ण

	phy->test.state = state;

	वापस 0;
पूर्ण

पूर्णांक mt76_tesपंचांगode_set_state(काष्ठा mt76_phy *phy, क्रमागत mt76_tesपंचांगode_state state)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	काष्ठा ieee80211_hw *hw = phy->hw;

	अगर (state == td->state && state == MT76_TM_STATE_OFF)
		वापस 0;

	अगर (state > MT76_TM_STATE_OFF &&
	    (!test_bit(MT76_STATE_RUNNING, &phy->state) ||
	     !(hw->conf.flags & IEEE80211_CONF_MONITOR)))
		वापस -ENOTCONN;

	अगर (state != MT76_TM_STATE_IDLE &&
	    td->state != MT76_TM_STATE_IDLE) अणु
		पूर्णांक ret;

		ret = __mt76_tesपंचांगode_set_state(phy, MT76_TM_STATE_IDLE);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस __mt76_tesपंचांगode_set_state(phy, state);

पूर्ण
EXPORT_SYMBOL(mt76_tesपंचांगode_set_state);

अटल पूर्णांक
mt76_पंचांग_get_u8(काष्ठा nlattr *attr, u8 *dest, u8 min, u8 max)
अणु
	u8 val;

	अगर (!attr)
		वापस 0;

	val = nla_get_u8(attr);
	अगर (val < min || val > max)
		वापस -EINVAL;

	*dest = val;
	वापस 0;
पूर्ण

पूर्णांक mt76_tesपंचांगode_cmd(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		      व्योम *data, पूर्णांक len)
अणु
	काष्ठा mt76_phy *phy = hw->priv;
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	काष्ठा nlattr *tb[NUM_MT76_TM_ATTRS];
	bool ext_phy = phy != &dev->phy;
	u32 state;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!dev->test_ops)
		वापस -EOPNOTSUPP;

	err = nla_parse_deprecated(tb, MT76_TM_ATTR_MAX, data, len,
				   mt76_पंचांग_policy, शून्य);
	अगर (err)
		वापस err;

	err = -EINVAL;

	mutex_lock(&dev->mutex);

	अगर (tb[MT76_TM_ATTR_RESET]) अणु
		mt76_tesपंचांगode_set_state(phy, MT76_TM_STATE_OFF);
		स_रखो(td, 0, माप(*td));
	पूर्ण

	mt76_tesपंचांगode_init_शेषs(phy);

	अगर (tb[MT76_TM_ATTR_TX_COUNT])
		td->tx_count = nla_get_u32(tb[MT76_TM_ATTR_TX_COUNT]);

	अगर (tb[MT76_TM_ATTR_TX_RATE_IDX])
		td->tx_rate_idx = nla_get_u8(tb[MT76_TM_ATTR_TX_RATE_IDX]);

	अगर (mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_RATE_MODE], &td->tx_rate_mode,
			   0, MT76_TM_TX_MODE_MAX) ||
	    mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_RATE_NSS], &td->tx_rate_nss,
			   1, hweight8(phy->antenna_mask)) ||
	    mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_RATE_SGI], &td->tx_rate_sgi, 0, 2) ||
	    mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_RATE_LDPC], &td->tx_rate_ldpc, 0, 1) ||
	    mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_RATE_STBC], &td->tx_rate_stbc, 0, 1) ||
	    mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_LTF], &td->tx_ltf, 0, 2) ||
	    mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_ANTENNA], &td->tx_antenna_mask,
			   1 << (ext_phy * 2), phy->antenna_mask << (ext_phy * 2)) ||
	    mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_SPE_IDX], &td->tx_spe_idx, 0, 27) ||
	    mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_DUTY_CYCLE],
			   &td->tx_duty_cycle, 0, 99) ||
	    mt76_पंचांग_get_u8(tb[MT76_TM_ATTR_TX_POWER_CONTROL],
			   &td->tx_घातer_control, 0, 1))
		जाओ out;

	अगर (tb[MT76_TM_ATTR_TX_LENGTH]) अणु
		u32 val = nla_get_u32(tb[MT76_TM_ATTR_TX_LENGTH]);

		अगर (val > mt76_tesपंचांगode_max_mpdu_len(phy, td->tx_rate_mode) ||
		    val < माप(काष्ठा ieee80211_hdr))
			जाओ out;

		td->tx_mpdu_len = val;
	पूर्ण

	अगर (tb[MT76_TM_ATTR_TX_IPG])
		td->tx_ipg = nla_get_u32(tb[MT76_TM_ATTR_TX_IPG]);

	अगर (tb[MT76_TM_ATTR_TX_TIME])
		td->tx_समय = nla_get_u32(tb[MT76_TM_ATTR_TX_TIME]);

	अगर (tb[MT76_TM_ATTR_FREQ_OFFSET])
		td->freq_offset = nla_get_u32(tb[MT76_TM_ATTR_FREQ_OFFSET]);

	अगर (tb[MT76_TM_ATTR_STATE]) अणु
		state = nla_get_u32(tb[MT76_TM_ATTR_STATE]);
		अगर (state > MT76_TM_STATE_MAX)
			जाओ out;
	पूर्ण अन्यथा अणु
		state = td->state;
	पूर्ण

	अगर (tb[MT76_TM_ATTR_TX_POWER]) अणु
		काष्ठा nlattr *cur;
		पूर्णांक idx = 0;
		पूर्णांक rem;

		nla_क्रम_each_nested(cur, tb[MT76_TM_ATTR_TX_POWER], rem) अणु
			अगर (nla_len(cur) != 1 ||
			    idx >= ARRAY_SIZE(td->tx_घातer))
				जाओ out;

			td->tx_घातer[idx++] = nla_get_u8(cur);
		पूर्ण
	पूर्ण

	अगर (dev->test_ops->set_params) अणु
		err = dev->test_ops->set_params(phy, tb, state);
		अगर (err)
			जाओ out;
	पूर्ण

	क्रम (i = MT76_TM_ATTR_STATE; i < ARRAY_SIZE(tb); i++)
		अगर (tb[i])
			mt76_tesपंचांगode_param_set(td, i);

	err = 0;
	अगर (tb[MT76_TM_ATTR_STATE])
		err = mt76_tesपंचांगode_set_state(phy, state);

out:
	mutex_unlock(&dev->mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mt76_tesपंचांगode_cmd);

अटल पूर्णांक
mt76_tesपंचांगode_dump_stats(काष्ठा mt76_phy *phy, काष्ठा sk_buff *msg)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	काष्ठा mt76_dev *dev = phy->dev;
	u64 rx_packets = 0;
	u64 rx_fcs_error = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(td->rx_stats.packets); i++) अणु
		rx_packets += td->rx_stats.packets[i];
		rx_fcs_error += td->rx_stats.fcs_error[i];
	पूर्ण

	अगर (nla_put_u32(msg, MT76_TM_STATS_ATTR_TX_PENDING, td->tx_pending) ||
	    nla_put_u32(msg, MT76_TM_STATS_ATTR_TX_QUEUED, td->tx_queued) ||
	    nla_put_u32(msg, MT76_TM_STATS_ATTR_TX_DONE, td->tx_करोne) ||
	    nla_put_u64_64bit(msg, MT76_TM_STATS_ATTR_RX_PACKETS, rx_packets,
			      MT76_TM_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(msg, MT76_TM_STATS_ATTR_RX_FCS_ERROR, rx_fcs_error,
			      MT76_TM_STATS_ATTR_PAD))
		वापस -EMSGSIZE;

	अगर (dev->test_ops->dump_stats)
		वापस dev->test_ops->dump_stats(phy, msg);

	वापस 0;
पूर्ण

पूर्णांक mt76_tesपंचांगode_dump(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *msg,
		       काष्ठा netlink_callback *cb, व्योम *data, पूर्णांक len)
अणु
	काष्ठा mt76_phy *phy = hw->priv;
	काष्ठा mt76_dev *dev = phy->dev;
	काष्ठा mt76_tesपंचांगode_data *td = &phy->test;
	काष्ठा nlattr *tb[NUM_MT76_TM_ATTRS] = अणुपूर्ण;
	पूर्णांक err = 0;
	व्योम *a;
	पूर्णांक i;

	अगर (!dev->test_ops)
		वापस -EOPNOTSUPP;

	अगर (cb->args[2]++ > 0)
		वापस -ENOENT;

	अगर (data) अणु
		err = nla_parse_deprecated(tb, MT76_TM_ATTR_MAX, data, len,
					   mt76_पंचांग_policy, शून्य);
		अगर (err)
			वापस err;
	पूर्ण

	mutex_lock(&dev->mutex);

	अगर (tb[MT76_TM_ATTR_STATS]) अणु
		err = -EINVAL;

		a = nla_nest_start(msg, MT76_TM_ATTR_STATS);
		अगर (a) अणु
			err = mt76_tesपंचांगode_dump_stats(phy, msg);
			nla_nest_end(msg, a);
		पूर्ण

		जाओ out;
	पूर्ण

	mt76_tesपंचांगode_init_शेषs(phy);

	err = -EMSGSIZE;
	अगर (nla_put_u32(msg, MT76_TM_ATTR_STATE, td->state))
		जाओ out;

	अगर (dev->test_mtd.name &&
	    (nla_put_string(msg, MT76_TM_ATTR_MTD_PART, dev->test_mtd.name) ||
	     nla_put_u32(msg, MT76_TM_ATTR_MTD_OFFSET, dev->test_mtd.offset)))
		जाओ out;

	अगर (nla_put_u32(msg, MT76_TM_ATTR_TX_COUNT, td->tx_count) ||
	    nla_put_u32(msg, MT76_TM_ATTR_TX_LENGTH, td->tx_mpdu_len) ||
	    nla_put_u8(msg, MT76_TM_ATTR_TX_RATE_MODE, td->tx_rate_mode) ||
	    nla_put_u8(msg, MT76_TM_ATTR_TX_RATE_NSS, td->tx_rate_nss) ||
	    nla_put_u8(msg, MT76_TM_ATTR_TX_RATE_IDX, td->tx_rate_idx) ||
	    nla_put_u8(msg, MT76_TM_ATTR_TX_RATE_SGI, td->tx_rate_sgi) ||
	    nla_put_u8(msg, MT76_TM_ATTR_TX_RATE_LDPC, td->tx_rate_ldpc) ||
	    nla_put_u8(msg, MT76_TM_ATTR_TX_RATE_STBC, td->tx_rate_stbc) ||
	    (mt76_tesपंचांगode_param_present(td, MT76_TM_ATTR_TX_LTF) &&
	     nla_put_u8(msg, MT76_TM_ATTR_TX_LTF, td->tx_ltf)) ||
	    (mt76_tesपंचांगode_param_present(td, MT76_TM_ATTR_TX_ANTENNA) &&
	     nla_put_u8(msg, MT76_TM_ATTR_TX_ANTENNA, td->tx_antenna_mask)) ||
	    (mt76_tesपंचांगode_param_present(td, MT76_TM_ATTR_TX_SPE_IDX) &&
	     nla_put_u8(msg, MT76_TM_ATTR_TX_SPE_IDX, td->tx_spe_idx)) ||
	    (mt76_tesपंचांगode_param_present(td, MT76_TM_ATTR_TX_DUTY_CYCLE) &&
	     nla_put_u8(msg, MT76_TM_ATTR_TX_DUTY_CYCLE, td->tx_duty_cycle)) ||
	    (mt76_tesपंचांगode_param_present(td, MT76_TM_ATTR_TX_IPG) &&
	     nla_put_u32(msg, MT76_TM_ATTR_TX_IPG, td->tx_ipg)) ||
	    (mt76_tesपंचांगode_param_present(td, MT76_TM_ATTR_TX_TIME) &&
	     nla_put_u32(msg, MT76_TM_ATTR_TX_TIME, td->tx_समय)) ||
	    (mt76_tesपंचांगode_param_present(td, MT76_TM_ATTR_TX_POWER_CONTROL) &&
	     nla_put_u8(msg, MT76_TM_ATTR_TX_POWER_CONTROL, td->tx_घातer_control)) ||
	    (mt76_tesपंचांगode_param_present(td, MT76_TM_ATTR_FREQ_OFFSET) &&
	     nla_put_u8(msg, MT76_TM_ATTR_FREQ_OFFSET, td->freq_offset)))
		जाओ out;

	अगर (mt76_tesपंचांगode_param_present(td, MT76_TM_ATTR_TX_POWER)) अणु
		a = nla_nest_start(msg, MT76_TM_ATTR_TX_POWER);
		अगर (!a)
			जाओ out;

		क्रम (i = 0; i < ARRAY_SIZE(td->tx_घातer); i++)
			अगर (nla_put_u8(msg, i, td->tx_घातer[i]))
				जाओ out;

		nla_nest_end(msg, a);
	पूर्ण

	err = 0;

out:
	mutex_unlock(&dev->mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mt76_tesपंचांगode_dump);
