<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qede NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश "qede_ptp.h"
#घोषणा QEDE_PTP_TX_TIMEOUT (2 * HZ)

काष्ठा qede_ptp अणु
	स्थिर काष्ठा qed_eth_ptp_ops	*ops;
	काष्ठा ptp_घड़ी_info		घड़ी_info;
	काष्ठा cyclecounter		cc;
	काष्ठा समयcounter		tc;
	काष्ठा ptp_घड़ी		*घड़ी;
	काष्ठा work_काष्ठा		work;
	अचिन्हित दीर्घ			ptp_tx_start;
	काष्ठा qede_dev			*edev;
	काष्ठा sk_buff			*tx_skb;

	/* ptp spinlock is used क्रम protecting the cycle/समय counter fields
	 * and, also क्रम serializing the qed PTP API invocations.
	 */
	spinlock_t			lock;
	bool				hw_ts_ioctl_called;
	u16				tx_type;
	u16				rx_filter;
पूर्ण;

/**
 * qede_ptp_adjfreq() - Adjust the frequency of the PTP cycle counter.
 *
 * @info: The PTP घड़ी info काष्ठाure.
 * @ppb: Parts per billion adjusपंचांगent from base.
 *
 * Return: Zero on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक qede_ptp_adjfreq(काष्ठा ptp_घड़ी_info *info, s32 ppb)
अणु
	काष्ठा qede_ptp *ptp = container_of(info, काष्ठा qede_ptp, घड़ी_info);
	काष्ठा qede_dev *edev = ptp->edev;
	पूर्णांक rc;

	__qede_lock(edev);
	अगर (edev->state == QEDE_STATE_OPEN) अणु
		spin_lock_bh(&ptp->lock);
		rc = ptp->ops->adjfreq(edev->cdev, ppb);
		spin_unlock_bh(&ptp->lock);
	पूर्ण अन्यथा अणु
		DP_ERR(edev, "PTP adjfreq called while interface is down\n");
		rc = -EFAULT;
	पूर्ण
	__qede_unlock(edev);

	वापस rc;
पूर्ण

अटल पूर्णांक qede_ptp_adjसमय(काष्ठा ptp_घड़ी_info *info, s64 delta)
अणु
	काष्ठा qede_dev *edev;
	काष्ठा qede_ptp *ptp;

	ptp = container_of(info, काष्ठा qede_ptp, घड़ी_info);
	edev = ptp->edev;

	DP_VERBOSE(edev, QED_MSG_DEBUG, "PTP adjtime called, delta = %llx\n",
		   delta);

	spin_lock_bh(&ptp->lock);
	समयcounter_adjसमय(&ptp->tc, delta);
	spin_unlock_bh(&ptp->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक qede_ptp_समय_लो(काष्ठा ptp_घड़ी_info *info, काष्ठा बारpec64 *ts)
अणु
	काष्ठा qede_dev *edev;
	काष्ठा qede_ptp *ptp;
	u64 ns;

	ptp = container_of(info, काष्ठा qede_ptp, घड़ी_info);
	edev = ptp->edev;

	spin_lock_bh(&ptp->lock);
	ns = समयcounter_पढ़ो(&ptp->tc);
	spin_unlock_bh(&ptp->lock);

	DP_VERBOSE(edev, QED_MSG_DEBUG, "PTP gettime called, ns = %llu\n", ns);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

अटल पूर्णांक qede_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *info,
			    स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा qede_dev *edev;
	काष्ठा qede_ptp *ptp;
	u64 ns;

	ptp = container_of(info, काष्ठा qede_ptp, घड़ी_info);
	edev = ptp->edev;

	ns = बारpec64_to_ns(ts);

	DP_VERBOSE(edev, QED_MSG_DEBUG, "PTP settime called, ns = %llu\n", ns);

	/* Re-init the समयcounter */
	spin_lock_bh(&ptp->lock);
	समयcounter_init(&ptp->tc, &ptp->cc, ns);
	spin_unlock_bh(&ptp->lock);

	वापस 0;
पूर्ण

/* Enable (or disable) ancillary features of the phc subप्रणाली */
अटल पूर्णांक qede_ptp_ancillary_feature_enable(काष्ठा ptp_घड़ी_info *info,
					     काष्ठा ptp_घड़ी_request *rq,
					     पूर्णांक on)
अणु
	काष्ठा qede_dev *edev;
	काष्ठा qede_ptp *ptp;

	ptp = container_of(info, काष्ठा qede_ptp, घड़ी_info);
	edev = ptp->edev;

	DP_ERR(edev, "PHC ancillary features are not supported\n");

	वापस -ENOTSUPP;
पूर्ण

अटल व्योम qede_ptp_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा qede_dev *edev;
	काष्ठा qede_ptp *ptp;
	u64 बारtamp, ns;
	bool समयकरोut;
	पूर्णांक rc;

	ptp = container_of(work, काष्ठा qede_ptp, work);
	edev = ptp->edev;
	समयकरोut = समय_is_beक्रमe_jअगरfies(ptp->ptp_tx_start +
					  QEDE_PTP_TX_TIMEOUT);

	/* Read Tx बारtamp रेजिस्टरs */
	spin_lock_bh(&ptp->lock);
	rc = ptp->ops->पढ़ो_tx_ts(edev->cdev, &बारtamp);
	spin_unlock_bh(&ptp->lock);
	अगर (rc) अणु
		अगर (unlikely(समयकरोut)) अणु
			DP_INFO(edev, "Tx timestamp is not recorded\n");
			dev_kमुक्त_skb_any(ptp->tx_skb);
			ptp->tx_skb = शून्य;
			clear_bit_unlock(QEDE_FLAGS_PTP_TX_IN_PRORGESS,
					 &edev->flags);
			edev->ptp_skip_txts++;
		पूर्ण अन्यथा अणु
			/* Reschedule to keep checking क्रम a valid TS value */
			schedule_work(&ptp->work);
		पूर्ण
		वापस;
	पूर्ण

	ns = समयcounter_cyc2समय(&ptp->tc, बारtamp);
	स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_kसमय(ns);
	skb_tstamp_tx(ptp->tx_skb, &shhwtstamps);
	dev_kमुक्त_skb_any(ptp->tx_skb);
	ptp->tx_skb = शून्य;
	clear_bit_unlock(QEDE_FLAGS_PTP_TX_IN_PRORGESS, &edev->flags);

	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "Tx timestamp, timestamp cycles = %llu, ns = %llu\n",
		   बारtamp, ns);
पूर्ण

/* Read the PHC. This API is invoked with ptp_lock held. */
अटल u64 qede_ptp_पढ़ो_cc(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा qede_dev *edev;
	काष्ठा qede_ptp *ptp;
	u64 phc_cycles;
	पूर्णांक rc;

	ptp = container_of(cc, काष्ठा qede_ptp, cc);
	edev = ptp->edev;
	rc = ptp->ops->पढ़ो_cc(edev->cdev, &phc_cycles);
	अगर (rc)
		WARN_ONCE(1, "PHC read err %d\n", rc);

	DP_VERBOSE(edev, QED_MSG_DEBUG, "PHC read cycles = %llu\n", phc_cycles);

	वापस phc_cycles;
पूर्ण

अटल पूर्णांक qede_ptp_cfg_filters(काष्ठा qede_dev *edev)
अणु
	क्रमागत qed_ptp_hwtstamp_tx_type tx_type = QED_PTP_HWTSTAMP_TX_ON;
	क्रमागत qed_ptp_filter_type rx_filter = QED_PTP_FILTER_NONE;
	काष्ठा qede_ptp *ptp = edev->ptp;

	अगर (!ptp)
		वापस -EIO;

	अगर (!ptp->hw_ts_ioctl_called) अणु
		DP_INFO(edev, "TS IOCTL not called\n");
		वापस 0;
	पूर्ण

	चयन (ptp->tx_type) अणु
	हाल HWTSTAMP_TX_ON:
		set_bit(QEDE_FLAGS_TX_TIMESTAMPING_EN, &edev->flags);
		tx_type = QED_PTP_HWTSTAMP_TX_ON;
		अवरोध;

	हाल HWTSTAMP_TX_OFF:
		clear_bit(QEDE_FLAGS_TX_TIMESTAMPING_EN, &edev->flags);
		tx_type = QED_PTP_HWTSTAMP_TX_OFF;
		अवरोध;

	हाल HWTSTAMP_TX_ONESTEP_SYNC:
	हाल HWTSTAMP_TX_ONESTEP_P2P:
		DP_ERR(edev, "One-step timestamping is not supported\n");
		वापस -दुस्फल;
	पूर्ण

	spin_lock_bh(&ptp->lock);
	चयन (ptp->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		rx_filter = QED_PTP_FILTER_NONE;
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		ptp->rx_filter = HWTSTAMP_FILTER_NONE;
		rx_filter = QED_PTP_FILTER_ALL;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		rx_filter = QED_PTP_FILTER_V1_L4_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		/* Initialize PTP detection क्रम UDP/IPv4 events */
		rx_filter = QED_PTP_FILTER_V1_L4_GEN;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		rx_filter = QED_PTP_FILTER_V2_L4_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		/* Initialize PTP detection क्रम UDP/IPv4 or UDP/IPv6 events */
		rx_filter = QED_PTP_FILTER_V2_L4_GEN;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		rx_filter = QED_PTP_FILTER_V2_L2_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		/* Initialize PTP detection L2 events */
		rx_filter = QED_PTP_FILTER_V2_L2_GEN;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		rx_filter = QED_PTP_FILTER_V2_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		ptp->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		/* Initialize PTP detection L2, UDP/IPv4 or UDP/IPv6 events */
		rx_filter = QED_PTP_FILTER_V2_GEN;
		अवरोध;
	पूर्ण

	ptp->ops->cfg_filters(edev->cdev, rx_filter, tx_type);

	spin_unlock_bh(&ptp->lock);

	वापस 0;
पूर्ण

पूर्णांक qede_ptp_hw_ts(काष्ठा qede_dev *edev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hwtstamp_config config;
	काष्ठा qede_ptp *ptp;
	पूर्णांक rc;

	ptp = edev->ptp;
	अगर (!ptp)
		वापस -EIO;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "HWTSTAMP IOCTL: Requested tx_type = %d, requested rx_filters = %d\n",
		   config.tx_type, config.rx_filter);

	अगर (config.flags) अणु
		DP_ERR(edev, "config.flags is reserved for future use\n");
		वापस -EINVAL;
	पूर्ण

	ptp->hw_ts_ioctl_called = 1;
	ptp->tx_type = config.tx_type;
	ptp->rx_filter = config.rx_filter;

	rc = qede_ptp_cfg_filters(edev);
	अगर (rc)
		वापस rc;

	config.rx_filter = ptp->rx_filter;

	वापस copy_to_user(अगरr->अगरr_data, &config,
			    माप(config)) ? -EFAULT : 0;
पूर्ण

पूर्णांक qede_ptp_get_ts_info(काष्ठा qede_dev *edev, काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा qede_ptp *ptp = edev->ptp;

	अगर (!ptp) अणु
		info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
					SOF_TIMESTAMPING_RX_SOFTWARE |
					SOF_TIMESTAMPING_SOFTWARE;
		info->phc_index = -1;

		वापस 0;
	पूर्ण

	info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE |
				SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;

	अगर (ptp->घड़ी)
		info->phc_index = ptp_घड़ी_index(ptp->घड़ी);
	अन्यथा
		info->phc_index = -1;

	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) |
			   BIT(HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
			   BIT(HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
			   BIT(HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_L2_SYNC) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_EVENT) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_SYNC) |
			   BIT(HWTSTAMP_FILTER_PTP_V2_DELAY_REQ);

	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON);

	वापस 0;
पूर्ण

व्योम qede_ptp_disable(काष्ठा qede_dev *edev)
अणु
	काष्ठा qede_ptp *ptp;

	ptp = edev->ptp;
	अगर (!ptp)
		वापस;

	अगर (ptp->घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(ptp->घड़ी);
		ptp->घड़ी = शून्य;
	पूर्ण

	/* Cancel PTP work queue. Should be करोne after the Tx queues are
	 * drained to prevent additional scheduling.
	 */
	cancel_work_sync(&ptp->work);
	अगर (ptp->tx_skb) अणु
		dev_kमुक्त_skb_any(ptp->tx_skb);
		ptp->tx_skb = शून्य;
		clear_bit_unlock(QEDE_FLAGS_PTP_TX_IN_PRORGESS, &edev->flags);
	पूर्ण

	/* Disable PTP in HW */
	spin_lock_bh(&ptp->lock);
	ptp->ops->disable(edev->cdev);
	spin_unlock_bh(&ptp->lock);

	kमुक्त(ptp);
	edev->ptp = शून्य;
पूर्ण

अटल पूर्णांक qede_ptp_init(काष्ठा qede_dev *edev)
अणु
	काष्ठा qede_ptp *ptp;
	पूर्णांक rc;

	ptp = edev->ptp;
	अगर (!ptp)
		वापस -EINVAL;

	spin_lock_init(&ptp->lock);

	/* Configure PTP in HW */
	rc = ptp->ops->enable(edev->cdev);
	अगर (rc) अणु
		DP_INFO(edev, "PTP HW enable failed\n");
		वापस rc;
	पूर्ण

	/* Init work queue क्रम Tx बारtamping */
	INIT_WORK(&ptp->work, qede_ptp_task);

	/* Init cyclecounter and समयcounter */
	स_रखो(&ptp->cc, 0, माप(ptp->cc));
	ptp->cc.पढ़ो = qede_ptp_पढ़ो_cc;
	ptp->cc.mask = CYCLECOUNTER_MASK(64);
	ptp->cc.shअगरt = 0;
	ptp->cc.mult = 1;

	समयcounter_init(&ptp->tc, &ptp->cc, kसमय_प्रकारo_ns(kसमय_get_real()));

	वापस 0;
पूर्ण

पूर्णांक qede_ptp_enable(काष्ठा qede_dev *edev)
अणु
	काष्ठा qede_ptp *ptp;
	पूर्णांक rc;

	ptp = kzalloc(माप(*ptp), GFP_KERNEL);
	अगर (!ptp) अणु
		DP_INFO(edev, "Failed to allocate struct for PTP\n");
		वापस -ENOMEM;
	पूर्ण

	ptp->edev = edev;
	ptp->ops = edev->ops->ptp;
	अगर (!ptp->ops) अणु
		DP_INFO(edev, "PTP enable failed\n");
		rc = -EIO;
		जाओ err1;
	पूर्ण

	edev->ptp = ptp;

	rc = qede_ptp_init(edev);
	अगर (rc)
		जाओ err1;

	qede_ptp_cfg_filters(edev);

	/* Fill the ptp_घड़ी_info काष्ठा and रेजिस्टर PTP घड़ी */
	ptp->घड़ी_info.owner = THIS_MODULE;
	snम_लिखो(ptp->घड़ी_info.name, 16, "%s", edev->ndev->name);
	ptp->घड़ी_info.max_adj = QED_MAX_PHC_DRIFT_PPB;
	ptp->घड़ी_info.n_alarm = 0;
	ptp->घड़ी_info.n_ext_ts = 0;
	ptp->घड़ी_info.n_per_out = 0;
	ptp->घड़ी_info.pps = 0;
	ptp->घड़ी_info.adjfreq = qede_ptp_adjfreq;
	ptp->घड़ी_info.adjसमय = qede_ptp_adjसमय;
	ptp->घड़ी_info.समय_लो64 = qede_ptp_समय_लो;
	ptp->घड़ी_info.समय_रखो64 = qede_ptp_समय_रखो;
	ptp->घड़ी_info.enable = qede_ptp_ancillary_feature_enable;

	ptp->घड़ी = ptp_घड़ी_रेजिस्टर(&ptp->घड़ी_info, &edev->pdev->dev);
	अगर (IS_ERR(ptp->घड़ी)) अणु
		DP_ERR(edev, "PTP clock registration failed\n");
		qede_ptp_disable(edev);
		rc = -EINVAL;
		जाओ err2;
	पूर्ण

	वापस 0;

err1:
	kमुक्त(ptp);
err2:
	edev->ptp = शून्य;

	वापस rc;
पूर्ण

व्योम qede_ptp_tx_ts(काष्ठा qede_dev *edev, काष्ठा sk_buff *skb)
अणु
	काष्ठा qede_ptp *ptp;

	ptp = edev->ptp;
	अगर (!ptp)
		वापस;

	अगर (test_and_set_bit_lock(QEDE_FLAGS_PTP_TX_IN_PRORGESS,
				  &edev->flags)) अणु
		DP_ERR(edev, "Timestamping in progress\n");
		edev->ptp_skip_txts++;
		वापस;
	पूर्ण

	अगर (unlikely(!test_bit(QEDE_FLAGS_TX_TIMESTAMPING_EN, &edev->flags))) अणु
		DP_ERR(edev,
		       "Tx timestamping was not enabled, this packet will not be timestamped\n");
		clear_bit_unlock(QEDE_FLAGS_PTP_TX_IN_PRORGESS, &edev->flags);
		edev->ptp_skip_txts++;
	पूर्ण अन्यथा अगर (unlikely(ptp->tx_skb)) अणु
		DP_ERR(edev,
		       "The device supports only a single outstanding packet to timestamp, this packet will not be timestamped\n");
		clear_bit_unlock(QEDE_FLAGS_PTP_TX_IN_PRORGESS, &edev->flags);
		edev->ptp_skip_txts++;
	पूर्ण अन्यथा अणु
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		/* schedule check क्रम Tx बारtamp */
		ptp->tx_skb = skb_get(skb);
		ptp->ptp_tx_start = jअगरfies;
		schedule_work(&ptp->work);
	पूर्ण
पूर्ण

व्योम qede_ptp_rx_ts(काष्ठा qede_dev *edev, काष्ठा sk_buff *skb)
अणु
	काष्ठा qede_ptp *ptp;
	u64 बारtamp, ns;
	पूर्णांक rc;

	ptp = edev->ptp;
	अगर (!ptp)
		वापस;

	spin_lock_bh(&ptp->lock);
	rc = ptp->ops->पढ़ो_rx_ts(edev->cdev, &बारtamp);
	अगर (rc) अणु
		spin_unlock_bh(&ptp->lock);
		DP_INFO(edev, "Invalid Rx timestamp\n");
		वापस;
	पूर्ण

	ns = समयcounter_cyc2समय(&ptp->tc, बारtamp);
	spin_unlock_bh(&ptp->lock);
	skb_hwtstamps(skb)->hwtstamp = ns_to_kसमय(ns);
	DP_VERBOSE(edev, QED_MSG_DEBUG,
		   "Rx timestamp, timestamp cycles = %llu, ns = %llu\n",
		   बारtamp, ns);
पूर्ण
