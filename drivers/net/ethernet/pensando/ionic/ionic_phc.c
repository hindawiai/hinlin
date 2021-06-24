<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2021 Pensanकरो Systems, Inc */

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>

#समावेश "ionic.h"
#समावेश "ionic_bus.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_ethtool.h"

अटल पूर्णांक ionic_hwstamp_tx_mode(पूर्णांक config_tx_type)
अणु
	चयन (config_tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		वापस IONIC_TXSTAMP_OFF;
	हाल HWTSTAMP_TX_ON:
		वापस IONIC_TXSTAMP_ON;
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
		वापस IONIC_TXSTAMP_ONESTEP_SYNC;
	हाल HWTSTAMP_TX_ONESTEP_P2P:
		वापस IONIC_TXSTAMP_ONESTEP_P2P;
	शेष:
		वापस -दुस्फल;
	पूर्ण
पूर्ण

अटल u64 ionic_hwstamp_rx_filt(पूर्णांक config_rx_filter)
अणु
	चयन (config_rx_filter) अणु
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
		वापस IONIC_PKT_CLS_PTP1_ALL;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		वापस IONIC_PKT_CLS_PTP1_SYNC;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		वापस IONIC_PKT_CLS_PTP1_SYNC | IONIC_PKT_CLS_PTP1_DREQ;

	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
		वापस IONIC_PKT_CLS_PTP2_L4_ALL;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
		वापस IONIC_PKT_CLS_PTP2_L4_SYNC;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		वापस IONIC_PKT_CLS_PTP2_L4_SYNC | IONIC_PKT_CLS_PTP2_L4_DREQ;

	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		वापस IONIC_PKT_CLS_PTP2_L2_ALL;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
		वापस IONIC_PKT_CLS_PTP2_L2_SYNC;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		वापस IONIC_PKT_CLS_PTP2_L2_SYNC | IONIC_PKT_CLS_PTP2_L2_DREQ;

	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
		वापस IONIC_PKT_CLS_PTP2_ALL;
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
		वापस IONIC_PKT_CLS_PTP2_SYNC;
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		वापस IONIC_PKT_CLS_PTP2_SYNC | IONIC_PKT_CLS_PTP2_DREQ;

	हाल HWTSTAMP_FILTER_NTP_ALL:
		वापस IONIC_PKT_CLS_NTP_ALL;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ionic_lअगर_hwstamp_set_ts_config(काष्ठा ionic_lअगर *lअगर,
					   काष्ठा hwtstamp_config *new_ts)
अणु
	काष्ठा ionic *ionic = lअगर->ionic;
	काष्ठा hwtstamp_config *config;
	काष्ठा hwtstamp_config ts;
	पूर्णांक tx_mode = 0;
	u64 rx_filt = 0;
	पूर्णांक err, err2;
	bool rx_all;
	__le64 mask;

	अगर (!lअगर->phc || !lअगर->phc->ptp)
		वापस -EOPNOTSUPP;

	mutex_lock(&lअगर->phc->config_lock);

	अगर (new_ts) अणु
		config = new_ts;
	पूर्ण अन्यथा अणु
		/* If called with new_ts == शून्य, replay the previous request
		 * primarily क्रम recovery after a FW_RESET.
		 * We saved the previous configuration request info, so copy
		 * the previous request क्रम reference, clear the current state
		 * to match the device's reset state, and run with it.
		 */
		config = &ts;
		स_नकल(config, &lअगर->phc->ts_config, माप(*config));
		स_रखो(&lअगर->phc->ts_config, 0, माप(lअगर->phc->ts_config));
		lअगर->phc->ts_config_tx_mode = 0;
		lअगर->phc->ts_config_rx_filt = 0;
	पूर्ण

	tx_mode = ionic_hwstamp_tx_mode(config->tx_type);
	अगर (tx_mode < 0) अणु
		err = tx_mode;
		जाओ err_queues;
	पूर्ण

	mask = cpu_to_le64(BIT_ULL(tx_mode));
	अगर ((ionic->ident.lअगर.eth.hwstamp_tx_modes & mask) != mask) अणु
		err = -दुस्फल;
		जाओ err_queues;
	पूर्ण

	rx_filt = ionic_hwstamp_rx_filt(config->rx_filter);
	rx_all = config->rx_filter != HWTSTAMP_FILTER_NONE && !rx_filt;

	mask = cpu_to_le64(rx_filt);
	अगर ((ionic->ident.lअगर.eth.hwstamp_rx_filters & mask) != mask) अणु
		rx_filt = 0;
		rx_all = true;
		config->rx_filter = HWTSTAMP_FILTER_ALL;
	पूर्ण

	dev_dbg(ionic->dev, "config_rx_filter %d rx_filt %#llx rx_all %d\n",
		config->rx_filter, rx_filt, rx_all);

	अगर (tx_mode) अणु
		err = ionic_lअगर_create_hwstamp_txq(lअगर);
		अगर (err)
			जाओ err_queues;
	पूर्ण

	अगर (rx_filt) अणु
		err = ionic_lअगर_create_hwstamp_rxq(lअगर);
		अगर (err)
			जाओ err_queues;
	पूर्ण

	अगर (tx_mode != lअगर->phc->ts_config_tx_mode) अणु
		err = ionic_lअगर_set_hwstamp_txmode(lअगर, tx_mode);
		अगर (err)
			जाओ err_txmode;
	पूर्ण

	अगर (rx_filt != lअगर->phc->ts_config_rx_filt) अणु
		err = ionic_lअगर_set_hwstamp_rxfilt(lअगर, rx_filt);
		अगर (err)
			जाओ err_rxfilt;
	पूर्ण

	अगर (rx_all != (lअगर->phc->ts_config.rx_filter == HWTSTAMP_FILTER_ALL)) अणु
		err = ionic_lअगर_config_hwstamp_rxq_all(lअगर, rx_all);
		अगर (err)
			जाओ err_rxall;
	पूर्ण

	स_नकल(&lअगर->phc->ts_config, config, माप(*config));
	lअगर->phc->ts_config_rx_filt = rx_filt;
	lअगर->phc->ts_config_tx_mode = tx_mode;

	mutex_unlock(&lअगर->phc->config_lock);

	वापस 0;

err_rxall:
	अगर (rx_filt != lअगर->phc->ts_config_rx_filt) अणु
		rx_filt = lअगर->phc->ts_config_rx_filt;
		err2 = ionic_lअगर_set_hwstamp_rxfilt(lअगर, rx_filt);
		अगर (err2)
			dev_err(ionic->dev,
				"Failed to revert rx timestamp filter: %d\n", err2);
	पूर्ण
err_rxfilt:
	अगर (tx_mode != lअगर->phc->ts_config_tx_mode) अणु
		tx_mode = lअगर->phc->ts_config_tx_mode;
		err2 = ionic_lअगर_set_hwstamp_txmode(lअगर, tx_mode);
		अगर (err2)
			dev_err(ionic->dev,
				"Failed to revert tx timestamp mode: %d\n", err2);
	पूर्ण
err_txmode:
	/* special queues reमुख्य allocated, just unused */
err_queues:
	mutex_unlock(&lअगर->phc->config_lock);
	वापस err;
पूर्ण

पूर्णांक ionic_lअगर_hwstamp_set(काष्ठा ionic_lअगर *lअगर, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	पूर्णांक err;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	err = ionic_lअगर_hwstamp_set_ts_config(lअगर, &config);
	अगर (err) अणु
		netdev_info(lअगर->netdev, "hwstamp set failed: %d\n", err);
		वापस err;
	पूर्ण

	अगर (copy_to_user(अगरr->अगरr_data, &config, माप(config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक ionic_lअगर_hwstamp_replay(काष्ठा ionic_lअगर *lअगर)
अणु
	पूर्णांक err;

	err = ionic_lअगर_hwstamp_set_ts_config(lअगर, शून्य);
	अगर (err)
		netdev_info(lअगर->netdev, "hwstamp replay failed: %d\n", err);

	वापस err;
पूर्ण

पूर्णांक ionic_lअगर_hwstamp_get(काष्ठा ionic_lअगर *lअगर, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;

	अगर (!lअगर->phc || !lअगर->phc->ptp)
		वापस -EOPNOTSUPP;

	mutex_lock(&lअगर->phc->config_lock);
	स_नकल(&config, &lअगर->phc->ts_config, माप(config));
	mutex_unlock(&lअगर->phc->config_lock);

	अगर (copy_to_user(अगरr->अगरr_data, &config, माप(config)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल u64 ionic_hwstamp_पढ़ो(काष्ठा ionic *ionic,
			      काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	u32 tick_high_beक्रमe, tick_high, tick_low;

	/* पढ़ो and discard low part to defeat hw staging of high part */
	(व्योम)ioपढ़ो32(&ionic->idev.hwstamp_regs->tick_low);

	tick_high_beक्रमe = ioपढ़ो32(&ionic->idev.hwstamp_regs->tick_high);

	ptp_पढ़ो_प्रणाली_prets(sts);
	tick_low = ioपढ़ो32(&ionic->idev.hwstamp_regs->tick_low);
	ptp_पढ़ो_प्रणाली_postts(sts);

	tick_high = ioपढ़ो32(&ionic->idev.hwstamp_regs->tick_high);

	/* If tick_high changed, re-पढ़ो tick_low once more.  Assume tick_high
	 * cannot change again so soon as in the span of re-पढ़ोing tick_low.
	 */
	अगर (tick_high != tick_high_beक्रमe) अणु
		ptp_पढ़ो_प्रणाली_prets(sts);
		tick_low = ioपढ़ो32(&ionic->idev.hwstamp_regs->tick_low);
		ptp_पढ़ो_प्रणाली_postts(sts);
	पूर्ण

	वापस (u64)tick_low | ((u64)tick_high << 32);
पूर्ण

अटल u64 ionic_cc_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा ionic_phc *phc = container_of(cc, काष्ठा ionic_phc, cc);
	काष्ठा ionic *ionic = phc->lअगर->ionic;

	वापस ionic_hwstamp_पढ़ो(ionic, शून्य);
पूर्ण

अटल पूर्णांक ionic_setphc_cmd(काष्ठा ionic_phc *phc, काष्ठा ionic_admin_ctx *ctx)
अणु
	ctx->work = COMPLETION_INITIALIZER_ONSTACK(ctx->work);

	ctx->cmd.lअगर_setphc.opcode = IONIC_CMD_LIF_SETPHC;
	ctx->cmd.lअगर_setphc.lअगर_index = cpu_to_le16(phc->lअगर->index);

	ctx->cmd.lअगर_setphc.tick = cpu_to_le64(phc->tc.cycle_last);
	ctx->cmd.lअगर_setphc.nsec = cpu_to_le64(phc->tc.nsec);
	ctx->cmd.lअगर_setphc.frac = cpu_to_le64(phc->tc.frac);
	ctx->cmd.lअगर_setphc.mult = cpu_to_le32(phc->cc.mult);
	ctx->cmd.lअगर_setphc.shअगरt = cpu_to_le32(phc->cc.shअगरt);

	वापस ionic_adminq_post(phc->lअगर, ctx);
पूर्ण

अटल पूर्णांक ionic_phc_adjfine(काष्ठा ptp_घड़ी_info *info, दीर्घ scaled_ppm)
अणु
	काष्ठा ionic_phc *phc = container_of(info, काष्ठा ionic_phc, ptp_info);
	काष्ठा ionic_admin_ctx ctx = अणुपूर्ण;
	अचिन्हित दीर्घ irqflags;
	s64 adj;
	पूर्णांक err;

	/* Reject phc adjusपंचांगents during device upgrade */
	अगर (test_bit(IONIC_LIF_F_FW_RESET, phc->lअगर->state))
		वापस -EBUSY;

	/* Adjusपंचांगent value scaled by 2^16 million */
	adj = (s64)scaled_ppm * phc->init_cc_mult;

	/* Adjusपंचांगent value to scale */
	adj /= (s64)SCALED_PPM;

	/* Final adjusted multiplier */
	adj += phc->init_cc_mult;

	spin_lock_irqsave(&phc->lock, irqflags);

	/* update the poपूर्णांक-in-समय basis to now, beक्रमe adjusting the rate */
	समयcounter_पढ़ो(&phc->tc);
	phc->cc.mult = adj;

	/* Setphc commands are posted in-order, sequenced by phc->lock.  We
	 * need to drop the lock beक्रमe रुकोing क्रम the command to complete.
	 */
	err = ionic_setphc_cmd(phc, &ctx);

	spin_unlock_irqrestore(&phc->lock, irqflags);

	वापस ionic_adminq_रुको(phc->lअगर, &ctx, err);
पूर्ण

अटल पूर्णांक ionic_phc_adjसमय(काष्ठा ptp_घड़ी_info *info, s64 delta)
अणु
	काष्ठा ionic_phc *phc = container_of(info, काष्ठा ionic_phc, ptp_info);
	काष्ठा ionic_admin_ctx ctx = अणुपूर्ण;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक err;

	/* Reject phc adjusपंचांगents during device upgrade */
	अगर (test_bit(IONIC_LIF_F_FW_RESET, phc->lअगर->state))
		वापस -EBUSY;

	spin_lock_irqsave(&phc->lock, irqflags);

	समयcounter_adjसमय(&phc->tc, delta);

	/* Setphc commands are posted in-order, sequenced by phc->lock.  We
	 * need to drop the lock beक्रमe रुकोing क्रम the command to complete.
	 */
	err = ionic_setphc_cmd(phc, &ctx);

	spin_unlock_irqrestore(&phc->lock, irqflags);

	वापस ionic_adminq_रुको(phc->lअगर, &ctx, err);
पूर्ण

अटल पूर्णांक ionic_phc_समय_रखो64(काष्ठा ptp_घड़ी_info *info,
			       स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा ionic_phc *phc = container_of(info, काष्ठा ionic_phc, ptp_info);
	काष्ठा ionic_admin_ctx ctx = अणुपूर्ण;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक err;
	u64 ns;

	/* Reject phc adjusपंचांगents during device upgrade */
	अगर (test_bit(IONIC_LIF_F_FW_RESET, phc->lअगर->state))
		वापस -EBUSY;

	ns = बारpec64_to_ns(ts);

	spin_lock_irqsave(&phc->lock, irqflags);

	समयcounter_init(&phc->tc, &phc->cc, ns);

	/* Setphc commands are posted in-order, sequenced by phc->lock.  We
	 * need to drop the lock beक्रमe रुकोing क्रम the command to complete.
	 */
	err = ionic_setphc_cmd(phc, &ctx);

	spin_unlock_irqrestore(&phc->lock, irqflags);

	वापस ionic_adminq_रुको(phc->lअगर, &ctx, err);
पूर्ण

अटल पूर्णांक ionic_phc_समय_लोx64(काष्ठा ptp_घड़ी_info *info,
				काष्ठा बारpec64 *ts,
				काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा ionic_phc *phc = container_of(info, काष्ठा ionic_phc, ptp_info);
	काष्ठा ionic *ionic = phc->lअगर->ionic;
	अचिन्हित दीर्घ irqflags;
	u64 tick, ns;

	/* Do not attempt to पढ़ो device समय during upgrade */
	अगर (test_bit(IONIC_LIF_F_FW_RESET, phc->lअगर->state))
		वापस -EBUSY;

	spin_lock_irqsave(&phc->lock, irqflags);

	tick = ionic_hwstamp_पढ़ो(ionic, sts);

	ns = समयcounter_cyc2समय(&phc->tc, tick);

	spin_unlock_irqrestore(&phc->lock, irqflags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

अटल दीर्घ ionic_phc_aux_work(काष्ठा ptp_घड़ी_info *info)
अणु
	काष्ठा ionic_phc *phc = container_of(info, काष्ठा ionic_phc, ptp_info);
	काष्ठा ionic_admin_ctx ctx = अणुपूर्ण;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक err;

	/* Do not update phc during device upgrade, but keep polling to resume
	 * after upgrade.  Since we करोn't update the poपूर्णांक in समय basis, there
	 * is no expectation that we are मुख्यtaining the phc समय during the
	 * upgrade.  After upgrade, it will need to be पढ़ोjusted back to the
	 * correct समय by the ptp daemon.
	 */
	अगर (test_bit(IONIC_LIF_F_FW_RESET, phc->lअगर->state))
		वापस phc->aux_work_delay;

	spin_lock_irqsave(&phc->lock, irqflags);

	/* update poपूर्णांक-in-समय basis to now */
	समयcounter_पढ़ो(&phc->tc);

	/* Setphc commands are posted in-order, sequenced by phc->lock.  We
	 * need to drop the lock beक्रमe रुकोing क्रम the command to complete.
	 */
	err = ionic_setphc_cmd(phc, &ctx);

	spin_unlock_irqrestore(&phc->lock, irqflags);

	ionic_adminq_रुको(phc->lअगर, &ctx, err);

	वापस phc->aux_work_delay;
पूर्ण

kसमय_प्रकार ionic_lअगर_phc_kसमय(काष्ठा ionic_lअगर *lअगर, u64 tick)
अणु
	अचिन्हित दीर्घ irqflags;
	u64 ns;

	अगर (!lअगर->phc)
		वापस 0;

	spin_lock_irqsave(&lअगर->phc->lock, irqflags);
	ns = समयcounter_cyc2समय(&lअगर->phc->tc, tick);
	spin_unlock_irqrestore(&lअगर->phc->lock, irqflags);

	वापस ns_to_kसमय(ns);
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info ionic_ptp_info = अणु
	.owner		= THIS_MODULE,
	.name		= "ionic_ptp",
	.adjfine	= ionic_phc_adjfine,
	.adjसमय	= ionic_phc_adjसमय,
	.समय_लोx64	= ionic_phc_समय_लोx64,
	.समय_रखो64	= ionic_phc_समय_रखो64,
	.करो_aux_work	= ionic_phc_aux_work,
पूर्ण;

व्योम ionic_lअगर_रेजिस्टर_phc(काष्ठा ionic_lअगर *lअगर)
अणु
	अगर (!lअगर->phc || !(lअगर->hw_features & IONIC_ETH_HW_TIMESTAMP))
		वापस;

	lअगर->phc->ptp = ptp_घड़ी_रेजिस्टर(&lअगर->phc->ptp_info, lअगर->ionic->dev);

	अगर (IS_ERR(lअगर->phc->ptp)) अणु
		dev_warn(lअगर->ionic->dev, "Cannot register phc device: %ld\n",
			 PTR_ERR(lअगर->phc->ptp));

		lअगर->phc->ptp = शून्य;
	पूर्ण

	अगर (lअगर->phc->ptp)
		ptp_schedule_worker(lअगर->phc->ptp, lअगर->phc->aux_work_delay);
पूर्ण

व्योम ionic_lअगर_unरेजिस्टर_phc(काष्ठा ionic_lअगर *lअगर)
अणु
	अगर (!lअगर->phc || !lअगर->phc->ptp)
		वापस;

	ptp_घड़ी_unरेजिस्टर(lअगर->phc->ptp);

	lअगर->phc->ptp = शून्य;
पूर्ण

व्योम ionic_lअगर_alloc_phc(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic *ionic = lअगर->ionic;
	काष्ठा ionic_phc *phc;
	u64 delay, dअगरf, mult;
	u64 frac = 0;
	u64 features;
	u32 shअगरt;

	अगर (!ionic->idev.hwstamp_regs)
		वापस;

	features = le64_to_cpu(ionic->ident.lअगर.eth.config.features);
	अगर (!(features & IONIC_ETH_HW_TIMESTAMP))
		वापस;

	phc = devm_kzalloc(ionic->dev, माप(*phc), GFP_KERNEL);
	अगर (!phc)
		वापस;

	phc->lअगर = lअगर;

	phc->cc.पढ़ो = ionic_cc_पढ़ो;
	phc->cc.mask = le64_to_cpu(ionic->ident.dev.hwstamp_mask);
	phc->cc.mult = le32_to_cpu(ionic->ident.dev.hwstamp_mult);
	phc->cc.shअगरt = le32_to_cpu(ionic->ident.dev.hwstamp_shअगरt);

	अगर (!phc->cc.mult) अणु
		dev_err(lअगर->ionic->dev,
			"Invalid device PHC mask multiplier %u, disabling HW timestamp support\n",
			phc->cc.mult);
		devm_kमुक्त(lअगर->ionic->dev, phc);
		lअगर->phc = शून्य;
		वापस;
	पूर्ण

	dev_dbg(lअगर->ionic->dev, "Device PHC mask %#llx mult %u shift %u\n",
		phc->cc.mask, phc->cc.mult, phc->cc.shअगरt);

	spin_lock_init(&phc->lock);
	mutex_init(&phc->config_lock);

	/* max ticks is limited by the multiplier, or by the update period. */
	अगर (phc->cc.shअगरt + 2 + ilog2(IONIC_PHC_UPDATE_NS) >= 64) अणु
		/* max ticks that करो not overflow when multiplied by max
		 * adjusted multiplier (twice the initial multiplier)
		 */
		dअगरf = U64_MAX / phc->cc.mult / 2;
	पूर्ण अन्यथा अणु
		/* approx ticks at four बार the update period */
		dअगरf = (u64)IONIC_PHC_UPDATE_NS << (phc->cc.shअगरt + 2);
		dअगरf = DIV_ROUND_UP(dअगरf, phc->cc.mult);
	पूर्ण

	/* transक्रमm to biपंचांगask */
	dअगरf |= dअगरf >> 1;
	dअगरf |= dअगरf >> 2;
	dअगरf |= dअगरf >> 4;
	dअगरf |= dअगरf >> 8;
	dअगरf |= dअगरf >> 16;
	dअगरf |= dअगरf >> 32;

	/* स्थिरrain to the hardware biपंचांगask, and use this as the biपंचांगask */
	dअगरf &= phc->cc.mask;
	phc->cc.mask = dअगरf;

	/* the wrap period is now defined by dअगरf (or phc->cc.mask)
	 *
	 * we will update the समय basis at about 1/4 the wrap period, so
	 * should not see a dअगरference of more than +/- dअगरf/4.
	 *
	 * this is sufficient not see a dअगरference of more than +/- dअगरf/2, as
	 * required by समयcounter_cyc2समय, to detect an old समय stamp.
	 *
	 * adjust the initial multiplier, being careful to aव्योम overflow:
	 *  - करो not overflow 63 bits: init_cc_mult * SCALED_PPM
	 *  - करो not overflow 64 bits: max_mult * (dअगरf / 2)
	 *
	 * we want to increase the initial multiplier as much as possible, to
	 * allow क्रम more precise adjusपंचांगent in ionic_phc_adjfine.
	 *
	 * only adjust the multiplier अगर we can द्विगुन it or more.
	 */
	mult = U64_MAX / 2 / max(dअगरf / 2, SCALED_PPM);
	shअगरt = mult / phc->cc.mult;
	अगर (shअगरt >= 2) अणु
		/* initial multiplier will be 2^n of hardware cc.mult */
		shअगरt = fls(shअगरt);
		/* increase cc.mult and cc.shअगरt by the same 2^n and n. */
		phc->cc.mult <<= shअगरt;
		phc->cc.shअगरt += shअगरt;
	पूर्ण

	dev_dbg(lअगर->ionic->dev, "Initial PHC mask %#llx mult %u shift %u\n",
		phc->cc.mask, phc->cc.mult, phc->cc.shअगरt);

	/* frequency adjusपंचांगents are relative to the initial multiplier */
	phc->init_cc_mult = phc->cc.mult;

	समयcounter_init(&phc->tc, &phc->cc, kसमय_get_real_ns());

	/* Update cycle_last at 1/4 the wrap period, or IONIC_PHC_UPDATE_NS */
	delay = min_t(u64, IONIC_PHC_UPDATE_NS,
		      cyclecounter_cyc2ns(&phc->cc, dअगरf / 4, 0, &frac));
	dev_dbg(lअगर->ionic->dev, "Work delay %llu ms\n", delay / NSEC_PER_MSEC);

	phc->aux_work_delay = nsecs_to_jअगरfies(delay);

	phc->ptp_info = ionic_ptp_info;

	/* We have allowed to adjust the multiplier up to +/- 1 part per 1.
	 * Here expressed as NORMAL_PPB (1 billion parts per billion).
	 */
	phc->ptp_info.max_adj = NORMAL_PPB;

	lअगर->phc = phc;
पूर्ण

व्योम ionic_lअगर_मुक्त_phc(काष्ठा ionic_lअगर *lअगर)
अणु
	अगर (!lअगर->phc)
		वापस;

	mutex_destroy(&lअगर->phc->config_lock);

	devm_kमुक्त(lअगर->ionic->dev, lअगर->phc);
	lअगर->phc = शून्य;
पूर्ण
