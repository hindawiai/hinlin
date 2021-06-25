<शैली गुरु>
/*
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
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

#समावेश "ath9k.h"

अटल व्योम ath9k_tx99_stop(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ath_drain_all_txq(sc);
	ath_startrecv(sc);

	ath9k_hw_set_पूर्णांकerrupts(ah);
	ath9k_hw_enable_पूर्णांकerrupts(ah);

	ieee80211_wake_queues(sc->hw);

	kमुक्त_skb(sc->tx99_skb);
	sc->tx99_skb = शून्य;
	sc->tx99_state = false;

	ath9k_hw_tx99_stop(sc->sc_ah);
	ath_dbg(common, XMIT, "TX99 stopped\n");
पूर्ण

अटल काष्ठा sk_buff *ath9k_build_tx99_skb(काष्ठा ath_softc *sc)
अणु
	अटल u8 PN9Data[] = अणु0xff, 0x87, 0xb8, 0x59, 0xb7, 0xa1, 0xcc, 0x24,
			       0x57, 0x5e, 0x4b, 0x9c, 0x0e, 0xe9, 0xea, 0x50,
			       0x2a, 0xbe, 0xb4, 0x1b, 0xb6, 0xb0, 0x5d, 0xf1,
			       0xe6, 0x9a, 0xe3, 0x45, 0xfd, 0x2c, 0x53, 0x18,
			       0x0c, 0xca, 0xc9, 0xfb, 0x49, 0x37, 0xe5, 0xa8,
			       0x51, 0x3b, 0x2f, 0x61, 0xaa, 0x72, 0x18, 0x84,
			       0x02, 0x23, 0x23, 0xab, 0x63, 0x89, 0x51, 0xb3,
			       0xe7, 0x8b, 0x72, 0x90, 0x4c, 0xe8, 0xfb, 0xc0पूर्ण;
	u32 len = 1200;
	काष्ठा ieee80211_tx_rate *rate;
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_tx_info *tx_info;
	काष्ठा sk_buff *skb;
	काष्ठा ath_vअगर *avp;

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	skb_put(skb, len);

	स_रखो(skb->data, 0, len);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	hdr->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA);
	hdr->duration_id = 0;

	स_नकल(hdr->addr1, hw->wiphy->perm_addr, ETH_ALEN);
	स_नकल(hdr->addr2, hw->wiphy->perm_addr, ETH_ALEN);
	स_नकल(hdr->addr3, hw->wiphy->perm_addr, ETH_ALEN);

	अगर (sc->tx99_vअगर) अणु
		avp = (काष्ठा ath_vअगर *) sc->tx99_vअगर->drv_priv;
		hdr->seq_ctrl |= cpu_to_le16(avp->seq_no);
	पूर्ण

	tx_info = IEEE80211_SKB_CB(skb);
	स_रखो(tx_info, 0, माप(*tx_info));
	rate = &tx_info->control.rates[0];
	tx_info->band = sc->cur_chan->chandef.chan->band;
	tx_info->flags = IEEE80211_TX_CTL_NO_ACK;
	tx_info->control.vअगर = sc->tx99_vअगर;
	rate->count = 1;
	अगर (ah->curchan && IS_CHAN_HT(ah->curchan)) अणु
		rate->flags |= IEEE80211_TX_RC_MCS;
		अगर (IS_CHAN_HT40(ah->curchan))
			rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
	पूर्ण

	स_नकल(skb->data + माप(*hdr), PN9Data, माप(PN9Data));

	वापस skb;
पूर्ण

अटल व्योम ath9k_tx99_deinit(काष्ठा ath_softc *sc)
अणु
	ath_reset(sc, शून्य);

	ath9k_ps_wakeup(sc);
	ath9k_tx99_stop(sc);
	ath9k_ps_restore(sc);
पूर्ण

अटल पूर्णांक ath9k_tx99_init(काष्ठा ath_softc *sc)
अणु
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_tx_control txctl;
	पूर्णांक r;

	अगर (test_bit(ATH_OP_INVALID, &common->op_flags)) अणु
		ath_err(common,
			"driver is in invalid state unable to use TX99");
		वापस -EINVAL;
	पूर्ण

	sc->tx99_skb = ath9k_build_tx99_skb(sc);
	अगर (!sc->tx99_skb)
		वापस -ENOMEM;

	स_रखो(&txctl, 0, माप(txctl));
	txctl.txq = sc->tx.txq_map[IEEE80211_AC_VO];

	ath_reset(sc, शून्य);

	ath9k_ps_wakeup(sc);

	ath9k_hw_disable_पूर्णांकerrupts(ah);
	ath_drain_all_txq(sc);
	ath_stoprecv(sc);

	sc->tx99_state = true;

	ieee80211_stop_queues(hw);

	अगर (sc->tx99_घातer == MAX_RATE_POWER + 1)
		sc->tx99_घातer = MAX_RATE_POWER;

	ath9k_hw_tx99_set_txघातer(ah, sc->tx99_घातer);
	r = ath9k_tx99_send(sc, sc->tx99_skb, &txctl);
	अगर (r) अणु
		ath_dbg(common, XMIT, "Failed to xmit TX99 skb\n");
		वापस r;
	पूर्ण

	ath_dbg(common, XMIT, "TX99 xmit started using %d ( %ddBm)\n",
		sc->tx99_घातer,
		sc->tx99_घातer / 2);

	/* We leave the hardware awake as it will be chugging on */

	वापस 0;
पूर्ण

अटल sमाप_प्रकार पढ़ो_file_tx99(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	अक्षर buf[3];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "%d\n", sc->tx99_state);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_tx99(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	अक्षर buf[32];
	bool start;
	sमाप_प्रकार len;
	पूर्णांक r;

	अगर (count < 1)
		वापस -EINVAL;

	अगर (sc->cur_chan->nvअगरs > 1)
		वापस -EOPNOTSUPP;

	len = min(count, माप(buf) - 1);
	अगर (copy_from_user(buf, user_buf, len))
		वापस -EFAULT;

	buf[len] = '\0';

	अगर (strtobool(buf, &start))
		वापस -EINVAL;

	mutex_lock(&sc->mutex);

	अगर (start == sc->tx99_state) अणु
		अगर (!start)
			जाओ out;
		ath_dbg(common, XMIT, "Resetting TX99\n");
		ath9k_tx99_deinit(sc);
	पूर्ण

	अगर (!start) अणु
		ath9k_tx99_deinit(sc);
		जाओ out;
	पूर्ण

	r = ath9k_tx99_init(sc);
	अगर (r) अणु
		mutex_unlock(&sc->mutex);
		वापस r;
	पूर्ण
out:
	mutex_unlock(&sc->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tx99 = अणु
	.पढ़ो = पढ़ो_file_tx99,
	.ग_लिखो = ग_लिखो_file_tx99,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार पढ़ो_file_tx99_घातer(काष्ठा file *file,
				    अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	अक्षर buf[32];
	अचिन्हित पूर्णांक len;

	len = प्र_लिखो(buf, "%d (%d dBm)\n",
		      sc->tx99_घातer,
		      sc->tx99_घातer / 2);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार ग_लिखो_file_tx99_घातer(काष्ठा file *file,
				     स्थिर अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ath_softc *sc = file->निजी_data;
	पूर्णांक r;
	u8 tx_घातer;

	r = kstrtou8_from_user(user_buf, count, 0, &tx_घातer);
	अगर (r)
		वापस r;

	अगर (tx_घातer > MAX_RATE_POWER)
		वापस -EINVAL;

	sc->tx99_घातer = tx_घातer;

	ath9k_ps_wakeup(sc);
	ath9k_hw_tx99_set_txघातer(sc->sc_ah, sc->tx99_घातer);
	ath9k_ps_restore(sc);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tx99_घातer = अणु
	.पढ़ो = पढ़ो_file_tx99_घातer,
	.ग_लिखो = ग_लिखो_file_tx99_घातer,
	.खोलो = simple_खोलो,
	.owner = THIS_MODULE,
	.llseek = शेष_llseek,
पूर्ण;

व्योम ath9k_tx99_init_debug(काष्ठा ath_softc *sc)
अणु
	अगर (!AR_SREV_9280_20_OR_LATER(sc->sc_ah))
		वापस;

	debugfs_create_file("tx99", 0600,
			    sc->debug.debugfs_phy, sc,
			    &fops_tx99);
	debugfs_create_file("tx99_power", 0600,
			    sc->debug.debugfs_phy, sc,
			    &fops_tx99_घातer);
पूर्ण
