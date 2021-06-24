<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
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
 *
 */

/********************************************\
Queue Control Unit, DCF Control Unit Functions
\********************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"
#समावेश <linux/log2.h>

/**
 * DOC: Queue Control Unit (QCU)/DCF Control Unit (DCU) functions
 *
 * Here we setup parameters क्रम the 12 available TX queues. Note that
 * on the various रेजिस्टरs we can usually only map the first 10 of them so
 * basically we have 10 queues to play with. Each queue has a matching
 * QCU that controls when the queue will get triggered and multiple QCUs
 * can be mapped to a single DCU that controls the various DFS parameters
 * क्रम the various queues. In our setup we have a 1:1 mapping between QCUs
 * and DCUs allowing us to have dअगरferent DFS settings क्रम each queue.
 *
 * When a frame goes पूर्णांकo a TX queue, QCU decides when it'll trigger a
 * transmission based on various criteria (such as how many data we have inside
 * it's buffer or -if it's a beacon queue- if it's समय to fire up the queue
 * based on TSF etc), DCU adds backoff, IFSes etc and then a scheduler
 * (arbitrator) decides the priority of each QCU based on it's configuration
 * (e.g. beacons are always transmitted when they leave DCU bypassing all other
 * frames from other queues रुकोing to be transmitted). After a frame leaves
 * the DCU it goes to PCU क्रम further processing and then to PHY क्रम
 * the actual transmission.
 */


/******************\
* Helper functions *
\******************/

/**
 * ath5k_hw_num_tx_pending() - Get number of pending frames क्रम a  given queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue: One of क्रमागत ath5k_tx_queue_id
 */
u32
ath5k_hw_num_tx_pending(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue)
अणु
	u32 pending;
	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/* Return अगर queue is declared inactive */
	अगर (ah->ah_txq[queue].tqi_type == AR5K_TX_QUEUE_INACTIVE)
		वापस false;

	/* XXX: How about AR5K_CFG_TXCNT ? */
	अगर (ah->ah_version == AR5K_AR5210)
		वापस false;

	pending = ath5k_hw_reg_पढ़ो(ah, AR5K_QUEUE_STATUS(queue));
	pending &= AR5K_QCU_STS_FRMPENDCNT;

	/* It's possible to have no frames pending even अगर TXE
	 * is set. To indicate that q has not stopped वापस
	 * true */
	अगर (!pending && AR5K_REG_READ_Q(ah, AR5K_QCU_TXE, queue))
		वापस true;

	वापस pending;
पूर्ण

/**
 * ath5k_hw_release_tx_queue() - Set a transmit queue inactive
 * @ah: The &काष्ठा ath5k_hw
 * @queue: One of क्रमागत ath5k_tx_queue_id
 */
व्योम
ath5k_hw_release_tx_queue(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue)
अणु
	अगर (WARN_ON(queue >= ah->ah_capabilities.cap_queues.q_tx_num))
		वापस;

	/* This queue will be skipped in further operations */
	ah->ah_txq[queue].tqi_type = AR5K_TX_QUEUE_INACTIVE;
	/*For SIMR setup*/
	AR5K_Q_DISABLE_BITS(ah->ah_txq_status, queue);
पूर्ण

/**
 * ath5k_cw_validate() - Make sure the given cw is valid
 * @cw_req: The contention winकरोw value to check
 *
 * Make sure cw is a घातer of 2 minus 1 and smaller than 1024
 */
अटल u16
ath5k_cw_validate(u16 cw_req)
अणु
	cw_req = min(cw_req, (u16)1023);

	/* Check अगर cw_req + 1 a घातer of 2 */
	अगर (is_घातer_of_2(cw_req + 1))
		वापस cw_req;

	/* Check अगर cw_req is a घातer of 2 */
	अगर (is_घातer_of_2(cw_req))
		वापस cw_req - 1;

	/* If none of the above is correct
	 * find the बंदst घातer of 2 */
	cw_req = (u16) roundup_घात_of_two(cw_req) - 1;

	वापस cw_req;
पूर्ण

/**
 * ath5k_hw_get_tx_queueprops() - Get properties क्रम a transmit queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue: One of क्रमागत ath5k_tx_queue_id
 * @queue_info: The &काष्ठा ath5k_txq_info to fill
 */
पूर्णांक
ath5k_hw_get_tx_queueprops(काष्ठा ath5k_hw *ah, पूर्णांक queue,
		काष्ठा ath5k_txq_info *queue_info)
अणु
	स_नकल(queue_info, &ah->ah_txq[queue], माप(काष्ठा ath5k_txq_info));
	वापस 0;
पूर्ण

/**
 * ath5k_hw_set_tx_queueprops() - Set properties क्रम a transmit queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue: One of क्रमागत ath5k_tx_queue_id
 * @qinfo: The &काष्ठा ath5k_txq_info to use
 *
 * Returns 0 on success or -EIO अगर queue is inactive
 */
पूर्णांक
ath5k_hw_set_tx_queueprops(काष्ठा ath5k_hw *ah, पूर्णांक queue,
				स्थिर काष्ठा ath5k_txq_info *qinfo)
अणु
	काष्ठा ath5k_txq_info *qi;

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	qi = &ah->ah_txq[queue];

	अगर (qi->tqi_type == AR5K_TX_QUEUE_INACTIVE)
		वापस -EIO;

	/* copy and validate values */
	qi->tqi_type = qinfo->tqi_type;
	qi->tqi_subtype = qinfo->tqi_subtype;
	qi->tqi_flags = qinfo->tqi_flags;
	/*
	 * According to the करोcs: Although the AIFS field is 8 bit wide,
	 * the maximum supported value is 0xFC. Setting it higher than that
	 * will cause the DCU to hang.
	 */
	qi->tqi_aअगरs = min(qinfo->tqi_aअगरs, (u8)0xFC);
	qi->tqi_cw_min = ath5k_cw_validate(qinfo->tqi_cw_min);
	qi->tqi_cw_max = ath5k_cw_validate(qinfo->tqi_cw_max);
	qi->tqi_cbr_period = qinfo->tqi_cbr_period;
	qi->tqi_cbr_overflow_limit = qinfo->tqi_cbr_overflow_limit;
	qi->tqi_burst_समय = qinfo->tqi_burst_समय;
	qi->tqi_पढ़ोy_समय = qinfo->tqi_पढ़ोy_समय;

	/*XXX: Is this supported on 5210 ?*/
	/*XXX: Is this correct क्रम AR5K_WME_AC_VI,VO ???*/
	अगर ((qinfo->tqi_type == AR5K_TX_QUEUE_DATA &&
		((qinfo->tqi_subtype == AR5K_WME_AC_VI) ||
		 (qinfo->tqi_subtype == AR5K_WME_AC_VO))) ||
	     qinfo->tqi_type == AR5K_TX_QUEUE_UAPSD)
		qi->tqi_flags |= AR5K_TXQ_FLAG_POST_FR_BKOFF_DIS;

	वापस 0;
पूर्ण

/**
 * ath5k_hw_setup_tx_queue() - Initialize a transmit queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue_type: One of क्रमागत ath5k_tx_queue
 * @queue_info: The &काष्ठा ath5k_txq_info to use
 *
 * Returns 0 on success, -EINVAL on invalid arguments
 */
पूर्णांक
ath5k_hw_setup_tx_queue(काष्ठा ath5k_hw *ah, क्रमागत ath5k_tx_queue queue_type,
		काष्ठा ath5k_txq_info *queue_info)
अणु
	अचिन्हित पूर्णांक queue;
	पूर्णांक ret;

	/*
	 * Get queue by type
	 */
	/* 5210 only has 2 queues */
	अगर (ah->ah_capabilities.cap_queues.q_tx_num == 2) अणु
		चयन (queue_type) अणु
		हाल AR5K_TX_QUEUE_DATA:
			queue = AR5K_TX_QUEUE_ID_NOQCU_DATA;
			अवरोध;
		हाल AR5K_TX_QUEUE_BEACON:
		हाल AR5K_TX_QUEUE_CAB:
			queue = AR5K_TX_QUEUE_ID_NOQCU_BEACON;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (queue_type) अणु
		हाल AR5K_TX_QUEUE_DATA:
			queue = queue_info->tqi_subtype;
			अवरोध;
		हाल AR5K_TX_QUEUE_UAPSD:
			queue = AR5K_TX_QUEUE_ID_UAPSD;
			अवरोध;
		हाल AR5K_TX_QUEUE_BEACON:
			queue = AR5K_TX_QUEUE_ID_BEACON;
			अवरोध;
		हाल AR5K_TX_QUEUE_CAB:
			queue = AR5K_TX_QUEUE_ID_CAB;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Setup पूर्णांकernal queue काष्ठाure
	 */
	स_रखो(&ah->ah_txq[queue], 0, माप(काष्ठा ath5k_txq_info));
	ah->ah_txq[queue].tqi_type = queue_type;

	अगर (queue_info != शून्य) अणु
		queue_info->tqi_type = queue_type;
		ret = ath5k_hw_set_tx_queueprops(ah, queue, queue_info);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * We use ah_txq_status to hold a temp value क्रम
	 * the Secondary पूर्णांकerrupt mask रेजिस्टरs on 5211+
	 * check out ath5k_hw_reset_tx_queue
	 */
	AR5K_Q_ENABLE_BITS(ah->ah_txq_status, queue);

	वापस queue;
पूर्ण


/*******************************\
* Single QCU/DCU initialization *
\*******************************/

/**
 * ath5k_hw_set_tx_retry_limits() - Set tx retry limits on DCU
 * @ah: The &काष्ठा ath5k_hw
 * @queue: One of क्रमागत ath5k_tx_queue_id
 *
 * This function is used when initializing a queue, to set
 * retry limits based on ah->ah_retry_* and the chipset used.
 */
व्योम
ath5k_hw_set_tx_retry_limits(काष्ठा ath5k_hw *ah,
				  अचिन्हित पूर्णांक queue)
अणु
	/* Single data queue on AR5210 */
	अगर (ah->ah_version == AR5K_AR5210) अणु
		काष्ठा ath5k_txq_info *tq = &ah->ah_txq[queue];

		अगर (queue > 0)
			वापस;

		ath5k_hw_reg_ग_लिखो(ah,
			(tq->tqi_cw_min << AR5K_NODCU_RETRY_LMT_CW_MIN_S)
			| AR5K_REG_SM(ah->ah_retry_दीर्घ,
				      AR5K_NODCU_RETRY_LMT_SLG_RETRY)
			| AR5K_REG_SM(ah->ah_retry_लघु,
				      AR5K_NODCU_RETRY_LMT_SSH_RETRY)
			| AR5K_REG_SM(ah->ah_retry_दीर्घ,
				      AR5K_NODCU_RETRY_LMT_LG_RETRY)
			| AR5K_REG_SM(ah->ah_retry_लघु,
				      AR5K_NODCU_RETRY_LMT_SH_RETRY),
			AR5K_NODCU_RETRY_LMT);
	/* DCU on AR5211+ */
	पूर्ण अन्यथा अणु
		ath5k_hw_reg_ग_लिखो(ah,
			AR5K_REG_SM(ah->ah_retry_दीर्घ,
				    AR5K_DCU_RETRY_LMT_RTS)
			| AR5K_REG_SM(ah->ah_retry_दीर्घ,
				      AR5K_DCU_RETRY_LMT_STA_RTS)
			| AR5K_REG_SM(max(ah->ah_retry_दीर्घ, ah->ah_retry_लघु),
				      AR5K_DCU_RETRY_LMT_STA_DATA),
			AR5K_QUEUE_DFS_RETRY_LIMIT(queue));
	पूर्ण
पूर्ण

/**
 * ath5k_hw_reset_tx_queue() - Initialize a single hw queue
 * @ah: The &काष्ठा ath5k_hw
 * @queue: One of क्रमागत ath5k_tx_queue_id
 *
 * Set DCF properties क्रम the given transmit queue on DCU
 * and configures all queue-specअगरic parameters.
 */
पूर्णांक
ath5k_hw_reset_tx_queue(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक queue)
अणु
	काष्ठा ath5k_txq_info *tq = &ah->ah_txq[queue];

	AR5K_ASSERT_ENTRY(queue, ah->ah_capabilities.cap_queues.q_tx_num);

	/* Skip अगर queue inactive or अगर we are on AR5210
	 * that करोesn't have QCU/DCU */
	अगर ((ah->ah_version == AR5K_AR5210) ||
	(tq->tqi_type == AR5K_TX_QUEUE_INACTIVE))
		वापस 0;

	/*
	 * Set contention winकरोw (cw_min/cw_max)
	 * and arbitrated पूर्णांकerframe space (aअगरs)...
	 */
	ath5k_hw_reg_ग_लिखो(ah,
		AR5K_REG_SM(tq->tqi_cw_min, AR5K_DCU_LCL_IFS_CW_MIN) |
		AR5K_REG_SM(tq->tqi_cw_max, AR5K_DCU_LCL_IFS_CW_MAX) |
		AR5K_REG_SM(tq->tqi_aअगरs, AR5K_DCU_LCL_IFS_AIFS),
		AR5K_QUEUE_DFS_LOCAL_IFS(queue));

	/*
	 * Set tx retry limits क्रम this queue
	 */
	ath5k_hw_set_tx_retry_limits(ah, queue);


	/*
	 * Set misc रेजिस्टरs
	 */

	/* Enable DCU to रुको क्रम next fragment from QCU */
	AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_DFS_MISC(queue),
				AR5K_DCU_MISC_FRAG_WAIT);

	/* On Maui and Spirit use the global seqnum on DCU */
	अगर (ah->ah_mac_version < AR5K_SREV_AR5211)
		AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_DFS_MISC(queue),
					AR5K_DCU_MISC_SEQNUM_CTL);

	/* Constant bit rate period */
	अगर (tq->tqi_cbr_period) अणु
		ath5k_hw_reg_ग_लिखो(ah, AR5K_REG_SM(tq->tqi_cbr_period,
					AR5K_QCU_CBRCFG_INTVAL) |
					AR5K_REG_SM(tq->tqi_cbr_overflow_limit,
					AR5K_QCU_CBRCFG_ORN_THRES),
					AR5K_QUEUE_CBRCFG(queue));

		AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
					AR5K_QCU_MISC_FRSHED_CBR);

		अगर (tq->tqi_cbr_overflow_limit)
			AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
					AR5K_QCU_MISC_CBR_THRES_ENABLE);
	पूर्ण

	/* Ready समय पूर्णांकerval */
	अगर (tq->tqi_पढ़ोy_समय && (tq->tqi_type != AR5K_TX_QUEUE_CAB))
		ath5k_hw_reg_ग_लिखो(ah, AR5K_REG_SM(tq->tqi_पढ़ोy_समय,
					AR5K_QCU_RDYTIMECFG_INTVAL) |
					AR5K_QCU_RDYTIMECFG_ENABLE,
					AR5K_QUEUE_RDYTIMECFG(queue));

	अगर (tq->tqi_burst_समय) अणु
		ath5k_hw_reg_ग_लिखो(ah, AR5K_REG_SM(tq->tqi_burst_समय,
					AR5K_DCU_CHAN_TIME_DUR) |
					AR5K_DCU_CHAN_TIME_ENABLE,
					AR5K_QUEUE_DFS_CHANNEL_TIME(queue));

		अगर (tq->tqi_flags & AR5K_TXQ_FLAG_RDYTIME_EXP_POLICY_ENABLE)
			AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
					AR5K_QCU_MISC_RDY_VEOL_POLICY);
	पूर्ण

	/* Enable/disable Post frame backoff */
	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_BACKOFF_DISABLE)
		ath5k_hw_reg_ग_लिखो(ah, AR5K_DCU_MISC_POST_FR_BKOFF_DIS,
					AR5K_QUEUE_DFS_MISC(queue));

	/* Enable/disable fragmentation burst backoff */
	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_FRAG_BURST_BACKOFF_ENABLE)
		ath5k_hw_reg_ग_लिखो(ah, AR5K_DCU_MISC_BACKOFF_FRAG,
					AR5K_QUEUE_DFS_MISC(queue));

	/*
	 * Set रेजिस्टरs by queue type
	 */
	चयन (tq->tqi_type) अणु
	हाल AR5K_TX_QUEUE_BEACON:
		AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
				AR5K_QCU_MISC_FRSHED_DBA_GT |
				AR5K_QCU_MISC_CBREXP_BCN_DIS |
				AR5K_QCU_MISC_BCN_ENABLE);

		AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_DFS_MISC(queue),
				(AR5K_DCU_MISC_ARBLOCK_CTL_GLOBAL <<
				AR5K_DCU_MISC_ARBLOCK_CTL_S) |
				AR5K_DCU_MISC_ARBLOCK_IGNORE |
				AR5K_DCU_MISC_POST_FR_BKOFF_DIS |
				AR5K_DCU_MISC_BCN_ENABLE);
		अवरोध;

	हाल AR5K_TX_QUEUE_CAB:
		/* XXX: use BCN_SENT_GT, अगर we can figure out how */
		AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
					AR5K_QCU_MISC_FRSHED_DBA_GT |
					AR5K_QCU_MISC_CBREXP_DIS |
					AR5K_QCU_MISC_CBREXP_BCN_DIS);

		ath5k_hw_reg_ग_लिखो(ah, ((tq->tqi_पढ़ोy_समय -
					(AR5K_TUNE_SW_BEACON_RESP -
					AR5K_TUNE_DMA_BEACON_RESP) -
				AR5K_TUNE_ADDITIONAL_SWBA_BACKOFF) * 1024) |
					AR5K_QCU_RDYTIMECFG_ENABLE,
					AR5K_QUEUE_RDYTIMECFG(queue));

		AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_DFS_MISC(queue),
					(AR5K_DCU_MISC_ARBLOCK_CTL_GLOBAL <<
					AR5K_DCU_MISC_ARBLOCK_CTL_S));
		अवरोध;

	हाल AR5K_TX_QUEUE_UAPSD:
		AR5K_REG_ENABLE_BITS(ah, AR5K_QUEUE_MISC(queue),
					AR5K_QCU_MISC_CBREXP_DIS);
		अवरोध;

	हाल AR5K_TX_QUEUE_DATA:
	शेष:
			अवरोध;
	पूर्ण

	/* TODO: Handle frame compression */

	/*
	 * Enable पूर्णांकerrupts क्रम this tx queue
	 * in the secondary पूर्णांकerrupt mask रेजिस्टरs
	 */
	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_TXOKINT_ENABLE)
		AR5K_Q_ENABLE_BITS(ah->ah_txq_imr_txok, queue);

	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_TXERRINT_ENABLE)
		AR5K_Q_ENABLE_BITS(ah->ah_txq_imr_txerr, queue);

	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_TXURNINT_ENABLE)
		AR5K_Q_ENABLE_BITS(ah->ah_txq_imr_txurn, queue);

	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_TXDESCINT_ENABLE)
		AR5K_Q_ENABLE_BITS(ah->ah_txq_imr_txdesc, queue);

	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_TXEOLINT_ENABLE)
		AR5K_Q_ENABLE_BITS(ah->ah_txq_imr_txeol, queue);

	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_CBRORNINT_ENABLE)
		AR5K_Q_ENABLE_BITS(ah->ah_txq_imr_cbrorn, queue);

	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_CBRURNINT_ENABLE)
		AR5K_Q_ENABLE_BITS(ah->ah_txq_imr_cbrurn, queue);

	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_QTRIGINT_ENABLE)
		AR5K_Q_ENABLE_BITS(ah->ah_txq_imr_qtrig, queue);

	अगर (tq->tqi_flags & AR5K_TXQ_FLAG_TXNOFRMINT_ENABLE)
		AR5K_Q_ENABLE_BITS(ah->ah_txq_imr_nofrm, queue);

	/* Update secondary पूर्णांकerrupt mask रेजिस्टरs */

	/* Filter out inactive queues */
	ah->ah_txq_imr_txok &= ah->ah_txq_status;
	ah->ah_txq_imr_txerr &= ah->ah_txq_status;
	ah->ah_txq_imr_txurn &= ah->ah_txq_status;
	ah->ah_txq_imr_txdesc &= ah->ah_txq_status;
	ah->ah_txq_imr_txeol &= ah->ah_txq_status;
	ah->ah_txq_imr_cbrorn &= ah->ah_txq_status;
	ah->ah_txq_imr_cbrurn &= ah->ah_txq_status;
	ah->ah_txq_imr_qtrig &= ah->ah_txq_status;
	ah->ah_txq_imr_nofrm &= ah->ah_txq_status;

	ath5k_hw_reg_ग_लिखो(ah, AR5K_REG_SM(ah->ah_txq_imr_txok,
					AR5K_SIMR0_QCU_TXOK) |
					AR5K_REG_SM(ah->ah_txq_imr_txdesc,
					AR5K_SIMR0_QCU_TXDESC),
					AR5K_SIMR0);

	ath5k_hw_reg_ग_लिखो(ah, AR5K_REG_SM(ah->ah_txq_imr_txerr,
					AR5K_SIMR1_QCU_TXERR) |
					AR5K_REG_SM(ah->ah_txq_imr_txeol,
					AR5K_SIMR1_QCU_TXEOL),
					AR5K_SIMR1);

	/* Update SIMR2 but करोn't overग_लिखो rest simr2 settings */
	AR5K_REG_DISABLE_BITS(ah, AR5K_SIMR2, AR5K_SIMR2_QCU_TXURN);
	AR5K_REG_ENABLE_BITS(ah, AR5K_SIMR2,
				AR5K_REG_SM(ah->ah_txq_imr_txurn,
				AR5K_SIMR2_QCU_TXURN));

	ath5k_hw_reg_ग_लिखो(ah, AR5K_REG_SM(ah->ah_txq_imr_cbrorn,
				AR5K_SIMR3_QCBRORN) |
				AR5K_REG_SM(ah->ah_txq_imr_cbrurn,
				AR5K_SIMR3_QCBRURN),
				AR5K_SIMR3);

	ath5k_hw_reg_ग_लिखो(ah, AR5K_REG_SM(ah->ah_txq_imr_qtrig,
				AR5K_SIMR4_QTRIG), AR5K_SIMR4);

	/* Set TXNOFRM_QCU क्रम the queues with TXNOFRM enabled */
	ath5k_hw_reg_ग_लिखो(ah, AR5K_REG_SM(ah->ah_txq_imr_nofrm,
				AR5K_TXNOFRM_QCU), AR5K_TXNOFRM);

	/* No queue has TXNOFRM enabled, disable the पूर्णांकerrupt
	 * by setting AR5K_TXNOFRM to zero */
	अगर (ah->ah_txq_imr_nofrm == 0)
		ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_TXNOFRM);

	/* Set QCU mask क्रम this DCU to save घातer */
	AR5K_REG_WRITE_Q(ah, AR5K_QUEUE_QCUMASK(queue), queue);

	वापस 0;
पूर्ण


/**************************\
* Global QCU/DCU functions *
\**************************/

/**
 * ath5k_hw_set_अगरs_पूर्णांकervals()  - Set global पूर्णांकer-frame spaces on DCU
 * @ah: The &काष्ठा ath5k_hw
 * @slot_समय: Slot समय in us
 *
 * Sets the global IFS पूर्णांकervals on DCU (also works on AR5210) क्रम
 * the given slot समय and the current bwmode.
 */
पूर्णांक ath5k_hw_set_अगरs_पूर्णांकervals(काष्ठा ath5k_hw *ah, अचिन्हित पूर्णांक slot_समय)
अणु
	काष्ठा ieee80211_channel *channel = ah->ah_current_channel;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_rate *rate;
	u32 ack_tx_समय, eअगरs, eअगरs_घड़ी, sअगरs, sअगरs_घड़ी;
	u32 slot_समय_घड़ी = ath5k_hw_htoघड़ी(ah, slot_समय);
	u32 rate_flags, i;

	अगर (slot_समय < 6 || slot_समय_घड़ी > AR5K_SLOT_TIME_MAX)
		वापस -EINVAL;

	sअगरs = ath5k_hw_get_शेष_sअगरs(ah);
	sअगरs_घड़ी = ath5k_hw_htoघड़ी(ah, sअगरs - 2);

	/* EIFS
	 * Txसमय of ack at lowest rate + SIFS + DIFS
	 * (DIFS = SIFS + 2 * Slot समय)
	 *
	 * Note: HAL has some predefined values क्रम EIFS
	 * Turbo:   (37 + 2 * 6)
	 * Default: (74 + 2 * 9)
	 * Half:    (149 + 2 * 13)
	 * Quarter: (298 + 2 * 21)
	 *
	 * (74 + 2 * 6) क्रम AR5210 शेष and turbo !
	 *
	 * According to the क्रमmula we have
	 * ack_tx_समय = 25 क्रम turbo and
	 * ack_tx_समय = 42.5 * घड़ी multiplier
	 * क्रम शेष/half/quarter.
	 *
	 * This can't be right, 42 is what we would get
	 * from ath5k_hw_get_frame_dur_क्रम_bwmode or
	 * ieee80211_generic_frame_duration क्रम zero frame
	 * length and without SIFS !
	 *
	 * Also we have dअगरferent lowest rate क्रम 802.11a
	 */
	अगर (channel->band == NL80211_BAND_5GHZ)
		band = NL80211_BAND_5GHZ;
	अन्यथा
		band = NL80211_BAND_2GHZ;

	चयन (ah->ah_bwmode) अणु
	हाल AR5K_BWMODE_5MHZ:
		rate_flags = IEEE80211_RATE_SUPPORTS_5MHZ;
		अवरोध;
	हाल AR5K_BWMODE_10MHZ:
		rate_flags = IEEE80211_RATE_SUPPORTS_10MHZ;
		अवरोध;
	शेष:
		rate_flags = 0;
		अवरोध;
	पूर्ण
	sband = &ah->sbands[band];
	rate = शून्य;
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			जारी;
		rate = &sband->bitrates[i];
		अवरोध;
	पूर्ण
	अगर (WARN_ON(!rate))
		वापस -EINVAL;

	ack_tx_समय = ath5k_hw_get_frame_duration(ah, band, 10, rate, false);

	/* ack_tx_समय includes an SIFS alपढ़ोy */
	eअगरs = ack_tx_समय + sअगरs + 2 * slot_समय;
	eअगरs_घड़ी = ath5k_hw_htoघड़ी(ah, eअगरs);

	/* Set IFS settings on AR5210 */
	अगर (ah->ah_version == AR5K_AR5210) अणु
		u32 pअगरs, pअगरs_घड़ी, dअगरs, dअगरs_घड़ी;

		/* Set slot समय */
		ath5k_hw_reg_ग_लिखो(ah, slot_समय_घड़ी, AR5K_SLOT_TIME);

		/* Set EIFS */
		eअगरs_घड़ी = AR5K_REG_SM(eअगरs_घड़ी, AR5K_IFS1_EIFS);

		/* PIFS = Slot समय + SIFS */
		pअगरs = slot_समय + sअगरs;
		pअगरs_घड़ी = ath5k_hw_htoघड़ी(ah, pअगरs);
		pअगरs_घड़ी = AR5K_REG_SM(pअगरs_घड़ी, AR5K_IFS1_PIFS);

		/* DIFS = SIFS + 2 * Slot समय */
		dअगरs = sअगरs + 2 * slot_समय;
		dअगरs_घड़ी = ath5k_hw_htoघड़ी(ah, dअगरs);

		/* Set SIFS/DIFS */
		ath5k_hw_reg_ग_लिखो(ah, (dअगरs_घड़ी <<
				AR5K_IFS0_DIFS_S) | sअगरs_घड़ी,
				AR5K_IFS0);

		/* Set PIFS/EIFS and preserve AR5K_INIT_CARR_SENSE_EN */
		ath5k_hw_reg_ग_लिखो(ah, pअगरs_घड़ी | eअगरs_घड़ी |
				(AR5K_INIT_CARR_SENSE_EN << AR5K_IFS1_CS_EN_S),
				AR5K_IFS1);

		वापस 0;
	पूर्ण

	/* Set IFS slot समय */
	ath5k_hw_reg_ग_लिखो(ah, slot_समय_घड़ी, AR5K_DCU_GBL_IFS_SLOT);

	/* Set EIFS पूर्णांकerval */
	ath5k_hw_reg_ग_लिखो(ah, eअगरs_घड़ी, AR5K_DCU_GBL_IFS_EIFS);

	/* Set SIFS पूर्णांकerval in usecs */
	AR5K_REG_WRITE_BITS(ah, AR5K_DCU_GBL_IFS_MISC,
				AR5K_DCU_GBL_IFS_MISC_SIFS_DUR_USEC,
				sअगरs);

	/* Set SIFS पूर्णांकerval in घड़ी cycles */
	ath5k_hw_reg_ग_लिखो(ah, sअगरs_घड़ी, AR5K_DCU_GBL_IFS_SIFS);

	वापस 0;
पूर्ण


/**
 * ath5k_hw_init_queues() - Initialize tx queues
 * @ah: The &काष्ठा ath5k_hw
 *
 * Initializes all tx queues based on inक्रमmation on
 * ah->ah_txq* set by the driver
 */
पूर्णांक
ath5k_hw_init_queues(काष्ठा ath5k_hw *ah)
अणु
	पूर्णांक i, ret;

	/* TODO: HW Compression support क्रम data queues */
	/* TODO: Burst prefetch क्रम data queues */

	/*
	 * Reset queues and start beacon समयrs at the end of the reset routine
	 * This also sets QCU mask on each DCU क्रम 1:1 qcu to dcu mapping
	 * Note: If we want we can assign multiple qcus on one dcu.
	 */
	अगर (ah->ah_version != AR5K_AR5210)
		क्रम (i = 0; i < ah->ah_capabilities.cap_queues.q_tx_num; i++) अणु
			ret = ath5k_hw_reset_tx_queue(ah, i);
			अगर (ret) अणु
				ATH5K_ERR(ah,
					"failed to reset TX queue #%d\n", i);
				वापस ret;
			पूर्ण
		पूर्ण
	अन्यथा
		/* No QCU/DCU on AR5210, just set tx
		 * retry limits. We set IFS parameters
		 * on ath5k_hw_set_अगरs_पूर्णांकervals */
		ath5k_hw_set_tx_retry_limits(ah, 0);

	/* Set the turbo flag when operating on 40MHz */
	अगर (ah->ah_bwmode == AR5K_BWMODE_40MHZ)
		AR5K_REG_ENABLE_BITS(ah, AR5K_DCU_GBL_IFS_MISC,
				AR5K_DCU_GBL_IFS_MISC_TURBO_MODE);

	/* If we didn't set IFS timings through
	 * ath5k_hw_set_coverage_class make sure
	 * we set them here */
	अगर (!ah->ah_coverage_class) अणु
		अचिन्हित पूर्णांक slot_समय = ath5k_hw_get_शेष_slotसमय(ah);
		ath5k_hw_set_अगरs_पूर्णांकervals(ah, slot_समय);
	पूर्ण

	वापस 0;
पूर्ण
