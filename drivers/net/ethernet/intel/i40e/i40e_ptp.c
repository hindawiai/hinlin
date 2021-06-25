<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "i40e.h"
#समावेश <linux/ptp_classअगरy.h>

/* The XL710 बारync is very much like Intel's 82599 design when it comes to
 * the fundamental घड़ी design. However, the घड़ी operations are much simpler
 * in the XL710 because the device supports a full 64 bits of nanoseconds.
 * Because the field is so wide, we can क्रमgo the cycle counter and just
 * operate with the nanosecond field directly without fear of overflow.
 *
 * Much like the 82599, the update period is dependent upon the link speed:
 * At 40Gb link or no link, the period is 1.6ns.
 * At 10Gb link, the period is multiplied by 2. (3.2ns)
 * At 1Gb link, the period is multiplied by 20. (32ns)
 * 1588 functionality is not supported at 100Mbps.
 */
#घोषणा I40E_PTP_40GB_INCVAL		0x0199999999ULL
#घोषणा I40E_PTP_10GB_INCVAL_MULT	2
#घोषणा I40E_PTP_1GB_INCVAL_MULT	20

#घोषणा I40E_PRTTSYN_CTL1_TSYNTYPE_V1  BIT(I40E_PRTTSYN_CTL1_TSYNTYPE_SHIFT)
#घोषणा I40E_PRTTSYN_CTL1_TSYNTYPE_V2  (2 << \
					I40E_PRTTSYN_CTL1_TSYNTYPE_SHIFT)

/**
 * i40e_ptp_पढ़ो - Read the PHC समय from the device
 * @pf: Board निजी काष्ठाure
 * @ts: बारpec काष्ठाure to hold the current समय value
 * @sts: काष्ठाure to hold the प्रणाली समय beक्रमe and after पढ़ोing the PHC
 *
 * This function पढ़ोs the PRTTSYN_TIME रेजिस्टरs and stores them in a
 * बारpec. However, since the रेजिस्टरs are 64 bits of nanoseconds, we must
 * convert the result to a बारpec beक्रमe we can वापस.
 **/
अटल व्योम i40e_ptp_पढ़ो(काष्ठा i40e_pf *pf, काष्ठा बारpec64 *ts,
			  काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 hi, lo;
	u64 ns;

	/* The समयr latches on the lowest रेजिस्टर पढ़ो. */
	ptp_पढ़ो_प्रणाली_prets(sts);
	lo = rd32(hw, I40E_PRTTSYN_TIME_L);
	ptp_पढ़ो_प्रणाली_postts(sts);
	hi = rd32(hw, I40E_PRTTSYN_TIME_H);

	ns = (((u64)hi) << 32) | lo;

	*ts = ns_to_बारpec64(ns);
पूर्ण

/**
 * i40e_ptp_ग_लिखो - Write the PHC समय to the device
 * @pf: Board निजी काष्ठाure
 * @ts: बारpec काष्ठाure that holds the new समय value
 *
 * This function ग_लिखोs the PRTTSYN_TIME रेजिस्टरs with the user value. Since
 * we receive a बारpec from the stack, we must convert that बारpec पूर्णांकo
 * nanoseconds beक्रमe programming the रेजिस्टरs.
 **/
अटल व्योम i40e_ptp_ग_लिखो(काष्ठा i40e_pf *pf, स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u64 ns = बारpec64_to_ns(ts);

	/* The समयr will not update until the high रेजिस्टर is written, so
	 * ग_लिखो the low रेजिस्टर first.
	 */
	wr32(hw, I40E_PRTTSYN_TIME_L, ns & 0xFFFFFFFF);
	wr32(hw, I40E_PRTTSYN_TIME_H, ns >> 32);
पूर्ण

/**
 * i40e_ptp_convert_to_hwtstamp - Convert device घड़ी to प्रणाली समय
 * @hwtstamps: Timestamp काष्ठाure to update
 * @बारtamp: Timestamp from the hardware
 *
 * We need to convert the NIC घड़ी value पूर्णांकo a hwtstamp which can be used by
 * the upper level बारtamping functions. Since the बारtamp is simply a 64-
 * bit nanosecond value, we can call ns_to_kसमय directly to handle this.
 **/
अटल व्योम i40e_ptp_convert_to_hwtstamp(काष्ठा skb_shared_hwtstamps *hwtstamps,
					 u64 बारtamp)
अणु
	स_रखो(hwtstamps, 0, माप(*hwtstamps));

	hwtstamps->hwtstamp = ns_to_kसमय(बारtamp);
पूर्ण

/**
 * i40e_ptp_adjfreq - Adjust the PHC frequency
 * @ptp: The PTP घड़ी काष्ठाure
 * @ppb: Parts per billion adjusपंचांगent from the base
 *
 * Adjust the frequency of the PHC by the indicated parts per billion from the
 * base frequency.
 **/
अटल पूर्णांक i40e_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा i40e_pf *pf = container_of(ptp, काष्ठा i40e_pf, ptp_caps);
	काष्ठा i40e_hw *hw = &pf->hw;
	u64 adj, freq, dअगरf;
	पूर्णांक neg_adj = 0;

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण

	freq = I40E_PTP_40GB_INCVAL;
	freq *= ppb;
	dअगरf = भाग_u64(freq, 1000000000ULL);

	अगर (neg_adj)
		adj = I40E_PTP_40GB_INCVAL - dअगरf;
	अन्यथा
		adj = I40E_PTP_40GB_INCVAL + dअगरf;

	/* At some link speeds, the base incval is so large that directly
	 * multiplying by ppb would result in arithmetic overflow even when
	 * using a u64. Aव्योम this by instead calculating the new incval
	 * always in terms of the 40GbE घड़ी rate and then multiplying by the
	 * link speed factor afterwards. This करोes result in slightly lower
	 * precision at lower link speeds, but it is fairly minor.
	 */
	smp_mb(); /* Force any pending update beक्रमe accessing. */
	adj *= READ_ONCE(pf->ptp_adj_mult);

	wr32(hw, I40E_PRTTSYN_INC_L, adj & 0xFFFFFFFF);
	wr32(hw, I40E_PRTTSYN_INC_H, adj >> 32);

	वापस 0;
पूर्ण

/**
 * i40e_ptp_adjसमय - Adjust the PHC समय
 * @ptp: The PTP घड़ी काष्ठाure
 * @delta: Offset in nanoseconds to adjust the PHC समय by
 *
 * Adjust the current घड़ी समय by a delta specअगरied in nanoseconds.
 **/
अटल पूर्णांक i40e_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा i40e_pf *pf = container_of(ptp, काष्ठा i40e_pf, ptp_caps);
	काष्ठा बारpec64 now, then;

	then = ns_to_बारpec64(delta);
	mutex_lock(&pf->पंचांगreg_lock);

	i40e_ptp_पढ़ो(pf, &now, शून्य);
	now = बारpec64_add(now, then);
	i40e_ptp_ग_लिखो(pf, (स्थिर काष्ठा बारpec64 *)&now);

	mutex_unlock(&pf->पंचांगreg_lock);

	वापस 0;
पूर्ण

/**
 * i40e_ptp_समय_लोx - Get the समय of the PHC
 * @ptp: The PTP घड़ी काष्ठाure
 * @ts: बारpec काष्ठाure to hold the current समय value
 * @sts: काष्ठाure to hold the प्रणाली समय beक्रमe and after पढ़ोing the PHC
 *
 * Read the device घड़ी and वापस the correct value on ns, after converting it
 * पूर्णांकo a बारpec काष्ठा.
 **/
अटल पूर्णांक i40e_ptp_समय_लोx(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts,
			     काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा i40e_pf *pf = container_of(ptp, काष्ठा i40e_pf, ptp_caps);

	mutex_lock(&pf->पंचांगreg_lock);
	i40e_ptp_पढ़ो(pf, ts, sts);
	mutex_unlock(&pf->पंचांगreg_lock);

	वापस 0;
पूर्ण

/**
 * i40e_ptp_समय_रखो - Set the समय of the PHC
 * @ptp: The PTP घड़ी काष्ठाure
 * @ts: बारpec काष्ठाure that holds the new समय value
 *
 * Set the device घड़ी to the user input value. The conversion from बारpec
 * to ns happens in the ग_लिखो function.
 **/
अटल पूर्णांक i40e_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			    स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा i40e_pf *pf = container_of(ptp, काष्ठा i40e_pf, ptp_caps);

	mutex_lock(&pf->पंचांगreg_lock);
	i40e_ptp_ग_लिखो(pf, ts);
	mutex_unlock(&pf->पंचांगreg_lock);

	वापस 0;
पूर्ण

/**
 * i40e_ptp_feature_enable - Enable/disable ancillary features of the PHC subप्रणाली
 * @ptp: The PTP घड़ी काष्ठाure
 * @rq: The requested feature to change
 * @on: Enable/disable flag
 *
 * The XL710 करोes not support any of the ancillary features of the PHC
 * subप्रणाली, so this function may just वापस.
 **/
अटल पूर्णांक i40e_ptp_feature_enable(काष्ठा ptp_घड़ी_info *ptp,
				   काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/**
 * i40e_ptp_get_rx_events - Read I40E_PRTTSYN_STAT_1 and latch events
 * @pf: the PF data काष्ठाure
 *
 * This function पढ़ोs I40E_PRTTSYN_STAT_1 and updates the corresponding समयrs
 * क्रम noticed latch events. This allows the driver to keep track of the first
 * समय a latch event was noticed which will be used to help clear out Rx
 * बारtamps क्रम packets that got dropped or lost.
 *
 * This function will वापस the current value of I40E_PRTTSYN_STAT_1 and is
 * expected to be called only जबतक under the ptp_rx_lock.
 **/
अटल u32 i40e_ptp_get_rx_events(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 prttsyn_stat, new_latch_events;
	पूर्णांक  i;

	prttsyn_stat = rd32(hw, I40E_PRTTSYN_STAT_1);
	new_latch_events = prttsyn_stat & ~pf->latch_event_flags;

	/* Update the jअगरfies समय क्रम any newly latched बारtamp. This
	 * ensures that we store the समय that we first discovered a बारtamp
	 * was latched by the hardware. The service task will later determine
	 * अगर we should मुक्त the latch and drop that बारtamp should too much
	 * समय pass. This flow ensures that we only update jअगरfies क्रम new
	 * events latched since the last समय we checked, and not all events
	 * currently latched, so that the service task accounting reमुख्यs
	 * accurate.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (new_latch_events & BIT(i))
			pf->latch_events[i] = jअगरfies;
	पूर्ण

	/* Finally, we store the current status of the Rx बारtamp latches */
	pf->latch_event_flags = prttsyn_stat;

	वापस prttsyn_stat;
पूर्ण

/**
 * i40e_ptp_rx_hang - Detect error हाल when Rx बारtamp रेजिस्टरs are hung
 * @pf: The PF निजी data काष्ठाure
 *
 * This watchकरोg task is scheduled to detect error हाल where hardware has
 * dropped an Rx packet that was बारtamped when the ring is full. The
 * particular error is rare but leaves the device in a state unable to बारtamp
 * any future packets.
 **/
व्योम i40e_ptp_rx_hang(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	अचिन्हित पूर्णांक i, cleared = 0;

	/* Since we cannot turn off the Rx बारtamp logic अगर the device is
	 * configured क्रम Tx बारtamping, we check अगर Rx बारtamping is
	 * configured. We करोn't want to spuriously warn about Rx बारtamp
	 * hangs अगर we करोn't care about the बारtamps.
	 */
	अगर (!(pf->flags & I40E_FLAG_PTP) || !pf->ptp_rx)
		वापस;

	spin_lock_bh(&pf->ptp_rx_lock);

	/* Update current latch बार क्रम Rx events */
	i40e_ptp_get_rx_events(pf);

	/* Check all the currently latched Rx events and see whether they have
	 * been latched क्रम over a second. It is assumed that any बारtamp
	 * should have been cleared within this समय, or अन्यथा it was captured
	 * क्रम a dropped frame that the driver never received. Thus, we will
	 * clear any बारtamp that has been latched क्रम over 1 second.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		अगर ((pf->latch_event_flags & BIT(i)) &&
		    समय_is_beक्रमe_jअगरfies(pf->latch_events[i] + HZ)) अणु
			rd32(hw, I40E_PRTTSYN_RXTIME_H(i));
			pf->latch_event_flags &= ~BIT(i);
			cleared++;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&pf->ptp_rx_lock);

	/* Log a warning अगर more than 2 बारtamps got dropped in the same
	 * check. We करोn't want to warn about all drops because it can occur
	 * in normal scenarios such as PTP frames on multicast addresses we
	 * aren't listening to. However, administrator should know अगर this is
	 * the reason packets aren't receiving बारtamps.
	 */
	अगर (cleared > 2)
		dev_dbg(&pf->pdev->dev,
			"Dropped %d missed RXTIME timestamp events\n",
			cleared);

	/* Finally, update the rx_hwtstamp_cleared counter */
	pf->rx_hwtstamp_cleared += cleared;
पूर्ण

/**
 * i40e_ptp_tx_hang - Detect error हाल when Tx बारtamp रेजिस्टर is hung
 * @pf: The PF निजी data काष्ठाure
 *
 * This watchकरोg task is run periodically to make sure that we clear the Tx
 * बारtamp logic अगर we करोn't obtain a बारtamp in a reasonable amount of
 * समय. It is unexpected in the normal हाल but अगर it occurs it results in
 * permanently preventing बारtamps of future packets.
 **/
व्योम i40e_ptp_tx_hang(काष्ठा i40e_pf *pf)
अणु
	काष्ठा sk_buff *skb;

	अगर (!(pf->flags & I40E_FLAG_PTP) || !pf->ptp_tx)
		वापस;

	/* Nothing to करो अगर we're not alपढ़ोy रुकोing क्रम a बारtamp */
	अगर (!test_bit(__I40E_PTP_TX_IN_PROGRESS, pf->state))
		वापस;

	/* We alपढ़ोy have a handler routine which is run when we are notअगरied
	 * of a Tx बारtamp in the hardware. If we करोn't get an पूर्णांकerrupt
	 * within a second it is reasonable to assume that we never will.
	 */
	अगर (समय_is_beक्रमe_jअगरfies(pf->ptp_tx_start + HZ)) अणु
		skb = pf->ptp_tx_skb;
		pf->ptp_tx_skb = शून्य;
		clear_bit_unlock(__I40E_PTP_TX_IN_PROGRESS, pf->state);

		/* Free the skb after we clear the bitlock */
		dev_kमुक्त_skb_any(skb);
		pf->tx_hwtstamp_समयouts++;
	पूर्ण
पूर्ण

/**
 * i40e_ptp_tx_hwtstamp - Utility function which वापसs the Tx बारtamp
 * @pf: Board निजी काष्ठाure
 *
 * Read the value of the Tx बारtamp from the रेजिस्टरs, convert it पूर्णांकo a
 * value consumable by the stack, and store that result पूर्णांकo the shhwtstamps
 * काष्ठा beक्रमe वापसing it up the stack.
 **/
व्योम i40e_ptp_tx_hwtstamp(काष्ठा i40e_pf *pf)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा sk_buff *skb = pf->ptp_tx_skb;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 hi, lo;
	u64 ns;

	अगर (!(pf->flags & I40E_FLAG_PTP) || !pf->ptp_tx)
		वापस;

	/* करोn't attempt to timestamp if we don't have an skb */
	अगर (!pf->ptp_tx_skb)
		वापस;

	lo = rd32(hw, I40E_PRTTSYN_TXTIME_L);
	hi = rd32(hw, I40E_PRTTSYN_TXTIME_H);

	ns = (((u64)hi) << 32) | lo;
	i40e_ptp_convert_to_hwtstamp(&shhwtstamps, ns);

	/* Clear the bit lock as soon as possible after पढ़ोing the रेजिस्टर,
	 * and prior to notअगरying the stack via skb_tstamp_tx(). Otherwise
	 * applications might wake up and attempt to request another transmit
	 * बारtamp prior to the bit lock being cleared.
	 */
	pf->ptp_tx_skb = शून्य;
	clear_bit_unlock(__I40E_PTP_TX_IN_PROGRESS, pf->state);

	/* Notअगरy the stack and मुक्त the skb after we've unlocked */
	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kमुक्त_skb_any(skb);
पूर्ण

/**
 * i40e_ptp_rx_hwtstamp - Utility function which checks क्रम an Rx बारtamp
 * @pf: Board निजी काष्ठाure
 * @skb: Particular skb to send बारtamp with
 * @index: Index पूर्णांकo the receive बारtamp रेजिस्टरs क्रम the बारtamp
 *
 * The XL710 receives a notअगरication in the receive descriptor with an offset
 * पूर्णांकo the set of RXTIME रेजिस्टरs where the बारtamp is क्रम that skb. This
 * function goes and fetches the receive बारtamp from that offset, अगर a valid
 * one exists. The RXTIME रेजिस्टरs are in ns, so we must convert the result
 * first.
 **/
व्योम i40e_ptp_rx_hwtstamp(काष्ठा i40e_pf *pf, काष्ठा sk_buff *skb, u8 index)
अणु
	u32 prttsyn_stat, hi, lo;
	काष्ठा i40e_hw *hw;
	u64 ns;

	/* Since we cannot turn off the Rx बारtamp logic अगर the device is
	 * करोing Tx बारtamping, check अगर Rx बारtamping is configured.
	 */
	अगर (!(pf->flags & I40E_FLAG_PTP) || !pf->ptp_rx)
		वापस;

	hw = &pf->hw;

	spin_lock_bh(&pf->ptp_rx_lock);

	/* Get current Rx events and update latch बार */
	prttsyn_stat = i40e_ptp_get_rx_events(pf);

	/* TODO: Should we warn about missing Rx बारtamp event? */
	अगर (!(prttsyn_stat & BIT(index))) अणु
		spin_unlock_bh(&pf->ptp_rx_lock);
		वापस;
	पूर्ण

	/* Clear the latched event since we're about to पढ़ो its रेजिस्टर */
	pf->latch_event_flags &= ~BIT(index);

	lo = rd32(hw, I40E_PRTTSYN_RXTIME_L(index));
	hi = rd32(hw, I40E_PRTTSYN_RXTIME_H(index));

	spin_unlock_bh(&pf->ptp_rx_lock);

	ns = (((u64)hi) << 32) | lo;

	i40e_ptp_convert_to_hwtstamp(skb_hwtstamps(skb), ns);
पूर्ण

/**
 * i40e_ptp_set_increment - Utility function to update घड़ी increment rate
 * @pf: Board निजी काष्ठाure
 *
 * During a link change, the DMA frequency that drives the 1588 logic will
 * change. In order to keep the PRTTSYN_TIME रेजिस्टरs in units of nanoseconds,
 * we must update the increment value per घड़ी tick.
 **/
व्योम i40e_ptp_set_increment(काष्ठा i40e_pf *pf)
अणु
	काष्ठा i40e_link_status *hw_link_info;
	काष्ठा i40e_hw *hw = &pf->hw;
	u64 incval;
	u32 mult;

	hw_link_info = &hw->phy.link_info;

	i40e_aq_get_link_info(&pf->hw, true, शून्य, शून्य);

	चयन (hw_link_info->link_speed) अणु
	हाल I40E_LINK_SPEED_10GB:
		mult = I40E_PTP_10GB_INCVAL_MULT;
		अवरोध;
	हाल I40E_LINK_SPEED_1GB:
		mult = I40E_PTP_1GB_INCVAL_MULT;
		अवरोध;
	हाल I40E_LINK_SPEED_100MB:
	अणु
		अटल पूर्णांक warn_once;

		अगर (!warn_once) अणु
			dev_warn(&pf->pdev->dev,
				 "1588 functionality is not supported at 100 Mbps. Stopping the PHC.\n");
			warn_once++;
		पूर्ण
		mult = 0;
		अवरोध;
	पूर्ण
	हाल I40E_LINK_SPEED_40GB:
	शेष:
		mult = 1;
		अवरोध;
	पूर्ण

	/* The increment value is calculated by taking the base 40GbE incvalue
	 * and multiplying it by a factor based on the link speed.
	 */
	incval = I40E_PTP_40GB_INCVAL * mult;

	/* Write the new increment value पूर्णांकo the increment रेजिस्टर. The
	 * hardware will not update the घड़ी until both रेजिस्टरs have been
	 * written.
	 */
	wr32(hw, I40E_PRTTSYN_INC_L, incval & 0xFFFFFFFF);
	wr32(hw, I40E_PRTTSYN_INC_H, incval >> 32);

	/* Update the base adjustement value. */
	WRITE_ONCE(pf->ptp_adj_mult, mult);
	smp_mb(); /* Force the above update. */
पूर्ण

/**
 * i40e_ptp_get_ts_config - ioctl पूर्णांकerface to पढ़ो the HW बारtamping
 * @pf: Board निजी काष्ठाure
 * @अगरr: ioctl data
 *
 * Obtain the current hardware बारtamping settigs as requested. To करो this,
 * keep a shaकरोw copy of the बारtamp settings rather than attempting to
 * deस्थिरruct it from the रेजिस्टरs.
 **/
पूर्णांक i40e_ptp_get_ts_config(काष्ठा i40e_pf *pf, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config *config = &pf->tstamp_config;

	अगर (!(pf->flags & I40E_FLAG_PTP))
		वापस -EOPNOTSUPP;

	वापस copy_to_user(अगरr->अगरr_data, config, माप(*config)) ?
		-EFAULT : 0;
पूर्ण

/**
 * i40e_ptp_set_बारtamp_mode - setup hardware क्रम requested बारtamp mode
 * @pf: Board निजी काष्ठाure
 * @config: hwtstamp settings requested or saved
 *
 * Control hardware रेजिस्टरs to enter the specअगरic mode requested by the
 * user. Also used during reset path to ensure that बारtamp settings are
 * मुख्यtained.
 *
 * Note: modअगरies config in place, and may update the requested mode to be
 * more broad अगर the specअगरic filter is not directly supported.
 **/
अटल पूर्णांक i40e_ptp_set_बारtamp_mode(काष्ठा i40e_pf *pf,
				       काष्ठा hwtstamp_config *config)
अणु
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 tsyntype, regval;

	/* Reserved क्रम future extensions. */
	अगर (config->flags)
		वापस -EINVAL;

	चयन (config->tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		pf->ptp_tx = false;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		pf->ptp_tx = true;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		pf->ptp_rx = false;
		/* We set the type to V1, but करो not enable UDP packet
		 * recognition. In this way, we should be as बंद to
		 * disabling PTP Rx बारtamps as possible since V1 packets
		 * are always UDP, since L2 packets are a V2 feature.
		 */
		tsyntype = I40E_PRTTSYN_CTL1_TSYNTYPE_V1;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
		अगर (!(pf->hw_features & I40E_HW_PTP_L4_CAPABLE))
			वापस -दुस्फल;
		pf->ptp_rx = true;
		tsyntype = I40E_PRTTSYN_CTL1_V1MESSTYPE0_MASK |
			   I40E_PRTTSYN_CTL1_TSYNTYPE_V1 |
			   I40E_PRTTSYN_CTL1_UDP_ENA_MASK;
		config->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		अगर (!(pf->hw_features & I40E_HW_PTP_L4_CAPABLE))
			वापस -दुस्फल;
		fallthrough;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		pf->ptp_rx = true;
		tsyntype = I40E_PRTTSYN_CTL1_V2MESSTYPE0_MASK |
			   I40E_PRTTSYN_CTL1_TSYNTYPE_V2;
		अगर (pf->hw_features & I40E_HW_PTP_L4_CAPABLE) अणु
			tsyntype |= I40E_PRTTSYN_CTL1_UDP_ENA_MASK;
			config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		पूर्ण अन्यथा अणु
			config->rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		पूर्ण
		अवरोध;
	हाल HWTSTAMP_FILTER_NTP_ALL:
	हाल HWTSTAMP_FILTER_ALL:
	शेष:
		वापस -दुस्फल;
	पूर्ण

	/* Clear out all 1588-related रेजिस्टरs to clear and unlatch them. */
	spin_lock_bh(&pf->ptp_rx_lock);
	rd32(hw, I40E_PRTTSYN_STAT_0);
	rd32(hw, I40E_PRTTSYN_TXTIME_H);
	rd32(hw, I40E_PRTTSYN_RXTIME_H(0));
	rd32(hw, I40E_PRTTSYN_RXTIME_H(1));
	rd32(hw, I40E_PRTTSYN_RXTIME_H(2));
	rd32(hw, I40E_PRTTSYN_RXTIME_H(3));
	pf->latch_event_flags = 0;
	spin_unlock_bh(&pf->ptp_rx_lock);

	/* Enable/disable the Tx बारtamp पूर्णांकerrupt based on user input. */
	regval = rd32(hw, I40E_PRTTSYN_CTL0);
	अगर (pf->ptp_tx)
		regval |= I40E_PRTTSYN_CTL0_TXTIME_INT_ENA_MASK;
	अन्यथा
		regval &= ~I40E_PRTTSYN_CTL0_TXTIME_INT_ENA_MASK;
	wr32(hw, I40E_PRTTSYN_CTL0, regval);

	regval = rd32(hw, I40E_PFINT_ICR0_ENA);
	अगर (pf->ptp_tx)
		regval |= I40E_PFINT_ICR0_ENA_TIMESYNC_MASK;
	अन्यथा
		regval &= ~I40E_PFINT_ICR0_ENA_TIMESYNC_MASK;
	wr32(hw, I40E_PFINT_ICR0_ENA, regval);

	/* Although there is no simple on/off चयन क्रम Rx, we "disable" Rx
	 * बारtamps by setting to V1 only mode and clear the UDP
	 * recognition. This ought to disable all PTP Rx बारtamps as V1
	 * packets are always over UDP. Note that software is configured to
	 * ignore Rx बारtamps via the pf->ptp_rx flag.
	 */
	regval = rd32(hw, I40E_PRTTSYN_CTL1);
	/* clear everything but the enable bit */
	regval &= I40E_PRTTSYN_CTL1_TSYNENA_MASK;
	/* now enable bits क्रम desired Rx बारtamps */
	regval |= tsyntype;
	wr32(hw, I40E_PRTTSYN_CTL1, regval);

	वापस 0;
पूर्ण

/**
 * i40e_ptp_set_ts_config - ioctl पूर्णांकerface to control the HW बारtamping
 * @pf: Board निजी काष्ठाure
 * @अगरr: ioctl data
 *
 * Respond to the user filter requests and make the appropriate hardware
 * changes here. The XL710 cannot support splitting of the Tx/Rx बारtamping
 * logic, so keep track in software of whether to indicate these बारtamps
 * or not.
 *
 * It is permissible to "upgrade" the user request to a broader filter, as दीर्घ
 * as the user receives the बारtamps they care about and the user is notअगरied
 * the filter has been broadened.
 **/
पूर्णांक i40e_ptp_set_ts_config(काष्ठा i40e_pf *pf, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	पूर्णांक err;

	अगर (!(pf->flags & I40E_FLAG_PTP))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	err = i40e_ptp_set_बारtamp_mode(pf, &config);
	अगर (err)
		वापस err;

	/* save these settings क्रम future reference */
	pf->tstamp_config = config;

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

/**
 * i40e_ptp_create_घड़ी - Create PTP घड़ी device क्रम userspace
 * @pf: Board निजी काष्ठाure
 *
 * This function creates a new PTP घड़ी device. It only creates one अगर we
 * करोn't alपढ़ोy have one, so it is safe to call. Will वापस error अगर it
 * can't create one, but success अगर we alपढ़ोy have a device. Should be used
 * by i40e_ptp_init to create घड़ी initially, and prevent global resets from
 * creating new घड़ी devices.
 **/
अटल दीर्घ i40e_ptp_create_घड़ी(काष्ठा i40e_pf *pf)
अणु
	/* no need to create a घड़ी device अगर we alपढ़ोy have one */
	अगर (!IS_ERR_OR_शून्य(pf->ptp_घड़ी))
		वापस 0;

	strlcpy(pf->ptp_caps.name, i40e_driver_name,
		माप(pf->ptp_caps.name) - 1);
	pf->ptp_caps.owner = THIS_MODULE;
	pf->ptp_caps.max_adj = 999999999;
	pf->ptp_caps.n_ext_ts = 0;
	pf->ptp_caps.pps = 0;
	pf->ptp_caps.adjfreq = i40e_ptp_adjfreq;
	pf->ptp_caps.adjसमय = i40e_ptp_adjसमय;
	pf->ptp_caps.समय_लोx64 = i40e_ptp_समय_लोx;
	pf->ptp_caps.समय_रखो64 = i40e_ptp_समय_रखो;
	pf->ptp_caps.enable = i40e_ptp_feature_enable;

	/* Attempt to रेजिस्टर the घड़ी beक्रमe enabling the hardware. */
	pf->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&pf->ptp_caps, &pf->pdev->dev);
	अगर (IS_ERR(pf->ptp_घड़ी))
		वापस PTR_ERR(pf->ptp_घड़ी);

	/* clear the hwtstamp settings here during घड़ी create, instead of
	 * during regular init, so that we can मुख्यtain settings across a
	 * reset or suspend.
	 */
	pf->tstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;
	pf->tstamp_config.tx_type = HWTSTAMP_TX_OFF;

	/* Set the previous "reset" समय to the current Kernel घड़ी समय */
	kसमय_get_real_ts64(&pf->ptp_prev_hw_समय);
	pf->ptp_reset_start = kसमय_get();

	वापस 0;
पूर्ण

/**
 * i40e_ptp_save_hw_समय - Save the current PTP समय as ptp_prev_hw_समय
 * @pf: Board निजी काष्ठाure
 *
 * Read the current PTP समय and save it पूर्णांकo pf->ptp_prev_hw_समय. This should
 * be called at the end of preparing to reset, just beक्रमe hardware reset
 * occurs, in order to preserve the PTP समय as बंद as possible across
 * resets.
 */
व्योम i40e_ptp_save_hw_समय(काष्ठा i40e_pf *pf)
अणु
	/* करोn't try to access the PTP clock if it's not enabled */
	अगर (!(pf->flags & I40E_FLAG_PTP))
		वापस;

	i40e_ptp_समय_लोx(&pf->ptp_caps, &pf->ptp_prev_hw_समय, शून्य);
	/* Get a monotonic starting समय क्रम this reset */
	pf->ptp_reset_start = kसमय_get();
पूर्ण

/**
 * i40e_ptp_restore_hw_समय - Restore the ptp_prev_hw_समय + delta to PTP regs
 * @pf: Board निजी काष्ठाure
 *
 * Restore the PTP hardware घड़ी रेजिस्टरs. We previously cached the PTP
 * hardware समय as pf->ptp_prev_hw_समय. To be as accurate as possible,
 * update this value based on the समय delta since the समय was saved, using
 * CLOCK_MONOTONIC (via kसमय_get()) to calculate the समय dअगरference.
 *
 * This ensures that the hardware घड़ी is restored to nearly what it should
 * have been अगर a reset had not occurred.
 */
व्योम i40e_ptp_restore_hw_समय(काष्ठा i40e_pf *pf)
अणु
	kसमय_प्रकार delta = kसमय_sub(kसमय_get(), pf->ptp_reset_start);

	/* Update the previous HW समय with the kसमय delta */
	बारpec64_add_ns(&pf->ptp_prev_hw_समय, kसमय_प्रकारo_ns(delta));

	/* Restore the hardware घड़ी रेजिस्टरs */
	i40e_ptp_समय_रखो(&pf->ptp_caps, &pf->ptp_prev_hw_समय);
पूर्ण

/**
 * i40e_ptp_init - Initialize the 1588 support after device probe or reset
 * @pf: Board निजी काष्ठाure
 *
 * This function sets device up क्रम 1588 support. The first समय it is run, it
 * will create a PHC घड़ी device. It करोes not create a घड़ी device अगर one
 * alपढ़ोy exists. It also reconfigures the device after a reset.
 *
 * The first समय a घड़ी is created, i40e_ptp_create_घड़ी will set
 * pf->ptp_prev_hw_समय to the current प्रणाली समय. During resets, it is
 * expected that this बारpec will be set to the last known PTP घड़ी समय,
 * in order to preserve the घड़ी समय as बंद as possible across a reset.
 **/
व्योम i40e_ptp_init(काष्ठा i40e_pf *pf)
अणु
	काष्ठा net_device *netdev = pf->vsi[pf->lan_vsi]->netdev;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 pf_id;
	दीर्घ err;

	/* Only one PF is asचिन्हित to control 1588 logic per port. Do not
	 * enable any support क्रम PFs not asचिन्हित via PRTTSYN_CTL0.PF_ID
	 */
	pf_id = (rd32(hw, I40E_PRTTSYN_CTL0) & I40E_PRTTSYN_CTL0_PF_ID_MASK) >>
		I40E_PRTTSYN_CTL0_PF_ID_SHIFT;
	अगर (hw->pf_id != pf_id) अणु
		pf->flags &= ~I40E_FLAG_PTP;
		dev_info(&pf->pdev->dev, "%s: PTP not supported on %s\n",
			 __func__,
			 netdev->name);
		वापस;
	पूर्ण

	mutex_init(&pf->पंचांगreg_lock);
	spin_lock_init(&pf->ptp_rx_lock);

	/* ensure we have a घड़ी device */
	err = i40e_ptp_create_घड़ी(pf);
	अगर (err) अणु
		pf->ptp_घड़ी = शून्य;
		dev_err(&pf->pdev->dev, "%s: ptp_clock_register failed\n",
			__func__);
	पूर्ण अन्यथा अगर (pf->ptp_घड़ी) अणु
		u32 regval;

		अगर (pf->hw.debug_mask & I40E_DEBUG_LAN)
			dev_info(&pf->pdev->dev, "PHC enabled\n");
		pf->flags |= I40E_FLAG_PTP;

		/* Ensure the घड़ीs are running. */
		regval = rd32(hw, I40E_PRTTSYN_CTL0);
		regval |= I40E_PRTTSYN_CTL0_TSYNENA_MASK;
		wr32(hw, I40E_PRTTSYN_CTL0, regval);
		regval = rd32(hw, I40E_PRTTSYN_CTL1);
		regval |= I40E_PRTTSYN_CTL1_TSYNENA_MASK;
		wr32(hw, I40E_PRTTSYN_CTL1, regval);

		/* Set the increment value per घड़ी tick. */
		i40e_ptp_set_increment(pf);

		/* reset बारtamping mode */
		i40e_ptp_set_बारtamp_mode(pf, &pf->tstamp_config);

		/* Restore the घड़ी समय based on last known value */
		i40e_ptp_restore_hw_समय(pf);
	पूर्ण
पूर्ण

/**
 * i40e_ptp_stop - Disable the driver/hardware support and unरेजिस्टर the PHC
 * @pf: Board निजी काष्ठाure
 *
 * This function handles the cleanup work required from the initialization by
 * clearing out the important inक्रमmation and unरेजिस्टरing the PHC.
 **/
व्योम i40e_ptp_stop(काष्ठा i40e_pf *pf)
अणु
	pf->flags &= ~I40E_FLAG_PTP;
	pf->ptp_tx = false;
	pf->ptp_rx = false;

	अगर (pf->ptp_tx_skb) अणु
		काष्ठा sk_buff *skb = pf->ptp_tx_skb;

		pf->ptp_tx_skb = शून्य;
		clear_bit_unlock(__I40E_PTP_TX_IN_PROGRESS, pf->state);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	अगर (pf->ptp_घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(pf->ptp_घड़ी);
		pf->ptp_घड़ी = शून्य;
		dev_info(&pf->pdev->dev, "%s: removed PHC on %s\n", __func__,
			 pf->vsi[pf->lan_vsi]->netdev->name);
	पूर्ण
पूर्ण
