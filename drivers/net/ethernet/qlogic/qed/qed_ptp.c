<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश "qed.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_hw.h"
#समावेश "qed_l2.h"
#समावेश "qed_mcp.h"
#समावेश "qed_ptp.h"
#समावेश "qed_reg_addr.h"

/* 16 nano second समय quantas to रुको beक्रमe making a Drअगरt adjusपंचांगent */
#घोषणा QED_DRIFT_CNTR_TIME_QUANTA_SHIFT	0
/* Nano seconds to add/subtract when making a Drअगरt adjusपंचांगent */
#घोषणा QED_DRIFT_CNTR_ADJUSTMENT_SHIFT		28
/* Add/subtract the Adjusपंचांगent_Value when making a Drअगरt adjusपंचांगent */
#घोषणा QED_DRIFT_CNTR_सूचीECTION_SHIFT		31
#घोषणा QED_TIMESTAMP_MASK			BIT(16)
/* Param mask क्रम Hardware to detect/बारtamp the L2/L4 unicast PTP packets */
#घोषणा QED_PTP_UCAST_PARAM_MASK              0x70F

अटल क्रमागत qed_resc_lock qed_ptcdev_to_resc(काष्ठा qed_hwfn *p_hwfn)
अणु
	चयन (MFW_PORT(p_hwfn)) अणु
	हाल 0:
		वापस QED_RESC_LOCK_PTP_PORT0;
	हाल 1:
		वापस QED_RESC_LOCK_PTP_PORT1;
	हाल 2:
		वापस QED_RESC_LOCK_PTP_PORT2;
	हाल 3:
		वापस QED_RESC_LOCK_PTP_PORT3;
	शेष:
		वापस QED_RESC_LOCK_RESC_INVALID;
	पूर्ण
पूर्ण

अटल पूर्णांक qed_ptp_res_lock(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_resc_lock_params params;
	क्रमागत qed_resc_lock resource;
	पूर्णांक rc;

	resource = qed_ptcdev_to_resc(p_hwfn);
	अगर (resource == QED_RESC_LOCK_RESC_INVALID)
		वापस -EINVAL;

	qed_mcp_resc_lock_शेष_init(&params, शून्य, resource, true);

	rc = qed_mcp_resc_lock(p_hwfn, p_ptt, &params);
	अगर (rc && rc != -EINVAL) अणु
		वापस rc;
	पूर्ण अन्यथा अगर (rc == -EINVAL) अणु
		/* MFW करोesn't support resource locking, first PF on the port
		 * has lock ownership.
		 */
		अगर (p_hwfn->असल_pf_id < p_hwfn->cdev->num_ports_in_engine)
			वापस 0;

		DP_INFO(p_hwfn, "PF doesn't have lock ownership\n");
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (!rc && !params.b_granted) अणु
		DP_INFO(p_hwfn, "Failed to acquire ptp resource lock\n");
		वापस -EBUSY;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qed_ptp_res_unlock(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_resc_unlock_params params;
	क्रमागत qed_resc_lock resource;
	पूर्णांक rc;

	resource = qed_ptcdev_to_resc(p_hwfn);
	अगर (resource == QED_RESC_LOCK_RESC_INVALID)
		वापस -EINVAL;

	qed_mcp_resc_lock_शेष_init(शून्य, &params, resource, true);

	rc = qed_mcp_resc_unlock(p_hwfn, p_ptt, &params);
	अगर (rc == -EINVAL) अणु
		/* MFW करोesn't support locking, first PF has lock ownership */
		अगर (p_hwfn->असल_pf_id < p_hwfn->cdev->num_ports_in_engine) अणु
			rc = 0;
		पूर्ण अन्यथा अणु
			DP_INFO(p_hwfn, "PF doesn't have lock ownership\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (rc) अणु
		DP_INFO(p_hwfn, "Failed to release the ptp resource lock\n");
	पूर्ण

	वापस rc;
पूर्ण

/* Read Rx बारtamp */
अटल पूर्णांक qed_ptp_hw_पढ़ो_rx_ts(काष्ठा qed_dev *cdev, u64 *बारtamp)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;
	u32 val;

	*बारtamp = 0;
	val = qed_rd(p_hwfn, p_ptt, NIG_REG_LLH_PTP_HOST_BUF_SEQID);
	अगर (!(val & QED_TIMESTAMP_MASK)) अणु
		DP_INFO(p_hwfn, "Invalid Rx timestamp, buf_seqid = %d\n", val);
		वापस -EINVAL;
	पूर्ण

	val = qed_rd(p_hwfn, p_ptt, NIG_REG_LLH_PTP_HOST_BUF_TS_LSB);
	*बारtamp = qed_rd(p_hwfn, p_ptt, NIG_REG_LLH_PTP_HOST_BUF_TS_MSB);
	*बारtamp <<= 32;
	*बारtamp |= val;

	/* Reset बारtamp रेजिस्टर to allow new बारtamp */
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_HOST_BUF_SEQID,
	       QED_TIMESTAMP_MASK);

	वापस 0;
पूर्ण

/* Read Tx बारtamp */
अटल पूर्णांक qed_ptp_hw_पढ़ो_tx_ts(काष्ठा qed_dev *cdev, u64 *बारtamp)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;
	u32 val;

	*बारtamp = 0;
	val = qed_rd(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_SEQID);
	अगर (!(val & QED_TIMESTAMP_MASK)) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_DEBUG,
			   "Invalid Tx timestamp, buf_seqid = %08x\n", val);
		वापस -EINVAL;
	पूर्ण

	val = qed_rd(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_TS_LSB);
	*बारtamp = qed_rd(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_TS_MSB);
	*बारtamp <<= 32;
	*बारtamp |= val;

	/* Reset बारtamp रेजिस्टर to allow new बारtamp */
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_SEQID, QED_TIMESTAMP_MASK);

	वापस 0;
पूर्ण

/* Read Phy Hardware Clock */
अटल पूर्णांक qed_ptp_hw_पढ़ो_cc(काष्ठा qed_dev *cdev, u64 *phc_cycles)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;
	u32 temp = 0;

	temp = qed_rd(p_hwfn, p_ptt, NIG_REG_TSGEN_SYNC_TIME_LSB);
	*phc_cycles = qed_rd(p_hwfn, p_ptt, NIG_REG_TSGEN_SYNC_TIME_MSB);
	*phc_cycles <<= 32;
	*phc_cycles |= temp;

	वापस 0;
पूर्ण

/* Filter PTP protocol packets that need to be बारtamped */
अटल पूर्णांक qed_ptp_hw_cfg_filters(काष्ठा qed_dev *cdev,
				  क्रमागत qed_ptp_filter_type rx_type,
				  क्रमागत qed_ptp_hwtstamp_tx_type tx_type)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;
	u32 rule_mask, enable_cfg = 0x0;

	चयन (rx_type) अणु
	हाल QED_PTP_FILTER_NONE:
		enable_cfg = 0x0;
		rule_mask = 0x3FFF;
		अवरोध;
	हाल QED_PTP_FILTER_ALL:
		enable_cfg = 0x7;
		rule_mask = 0x3CAA;
		अवरोध;
	हाल QED_PTP_FILTER_V1_L4_EVENT:
		enable_cfg = 0x3;
		rule_mask = 0x3FFA;
		अवरोध;
	हाल QED_PTP_FILTER_V1_L4_GEN:
		enable_cfg = 0x3;
		rule_mask = 0x3FFE;
		अवरोध;
	हाल QED_PTP_FILTER_V2_L4_EVENT:
		enable_cfg = 0x5;
		rule_mask = 0x3FAA;
		अवरोध;
	हाल QED_PTP_FILTER_V2_L4_GEN:
		enable_cfg = 0x5;
		rule_mask = 0x3FEE;
		अवरोध;
	हाल QED_PTP_FILTER_V2_L2_EVENT:
		enable_cfg = 0x5;
		rule_mask = 0x3CFF;
		अवरोध;
	हाल QED_PTP_FILTER_V2_L2_GEN:
		enable_cfg = 0x5;
		rule_mask = 0x3EFF;
		अवरोध;
	हाल QED_PTP_FILTER_V2_EVENT:
		enable_cfg = 0x5;
		rule_mask = 0x3CAA;
		अवरोध;
	हाल QED_PTP_FILTER_V2_GEN:
		enable_cfg = 0x5;
		rule_mask = 0x3EEE;
		अवरोध;
	शेष:
		DP_INFO(p_hwfn, "Invalid PTP filter type %d\n", rx_type);
		वापस -EINVAL;
	पूर्ण

	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_PARAM_MASK,
	       QED_PTP_UCAST_PARAM_MASK);
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_RULE_MASK, rule_mask);
	qed_wr(p_hwfn, p_ptt, NIG_REG_RX_PTP_EN, enable_cfg);

	अगर (tx_type == QED_PTP_HWTSTAMP_TX_OFF) अणु
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_PTP_EN, 0x0);
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_PARAM_MASK, 0x7FF);
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_RULE_MASK, 0x3FFF);
	पूर्ण अन्यथा अणु
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_PTP_EN, enable_cfg);
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_PARAM_MASK,
		       QED_PTP_UCAST_PARAM_MASK);
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_RULE_MASK, rule_mask);
	पूर्ण

	/* Reset possibly old बारtamps */
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_HOST_BUF_SEQID,
	       QED_TIMESTAMP_MASK);

	वापस 0;
पूर्ण

/* Adjust the HW घड़ी by a rate given in parts-per-billion (ppb) units.
 * FW/HW accepts the adjusपंचांगent value in terms of 3 parameters:
 *   Drअगरt period - adjusपंचांगent happens once in certain number of nano seconds.
 *   Drअगरt value - समय is adjusted by a certain value, क्रम example by 5 ns.
 *   Drअगरt direction - add or subtract the adjusपंचांगent value.
 * The routine translates ppb पूर्णांकo the adjusपंचांगent triplet in an optimal manner.
 */
अटल पूर्णांक qed_ptp_hw_adjfreq(काष्ठा qed_dev *cdev, s32 ppb)
अणु
	s64 best_val = 0, val, best_period = 0, period, approx_dev, dअगर, dअगर2;
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;
	u32 drअगरt_ctr_cfg = 0, drअगरt_state;
	पूर्णांक drअगरt_dir = 1;

	अगर (ppb < 0) अणु
		ppb = -ppb;
		drअगरt_dir = 0;
	पूर्ण

	अगर (ppb > 1) अणु
		s64 best_dअगर = ppb, best_approx_dev = 1;

		/* Adjusपंचांगent value is up to +/-7ns, find an optimal value in
		 * this range.
		 */
		क्रम (val = 7; val > 0; val--) अणु
			period = भाग_s64(val * 1000000000, ppb);
			period -= 8;
			period >>= 4;
			अगर (period < 1)
				period = 1;
			अगर (period > 0xFFFFFFE)
				period = 0xFFFFFFE;

			/* Check both rounding ends क्रम approximate error */
			approx_dev = period * 16 + 8;
			dअगर = ppb * approx_dev - val * 1000000000;
			dअगर2 = dअगर + 16 * ppb;

			अगर (dअगर < 0)
				dअगर = -dअगर;
			अगर (dअगर2 < 0)
				dअगर2 = -dअगर2;

			/* Determine which end gives better approximation */
			अगर (dअगर * (approx_dev + 16) > dअगर2 * approx_dev) अणु
				period++;
				approx_dev += 16;
				dअगर = dअगर2;
			पूर्ण

			/* Track best approximation found so far */
			अगर (best_dअगर * approx_dev > dअगर * best_approx_dev) अणु
				best_dअगर = dअगर;
				best_val = val;
				best_period = period;
				best_approx_dev = approx_dev;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (ppb == 1) अणु
		/* This is a special हाल as its the only value which wouldn't
		 * fit in a s64 variable. In order to prevent castings simple
		 * handle it seperately.
		 */
		best_val = 4;
		best_period = 0xee6b27f;
	पूर्ण अन्यथा अणु
		best_val = 0;
		best_period = 0xFFFFFFF;
	पूर्ण

	drअगरt_ctr_cfg = (best_period << QED_DRIFT_CNTR_TIME_QUANTA_SHIFT) |
			(((पूर्णांक)best_val) << QED_DRIFT_CNTR_ADJUSTMENT_SHIFT) |
			(((पूर्णांक)drअगरt_dir) << QED_DRIFT_CNTR_सूचीECTION_SHIFT);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_RST_DRIFT_CNTR, 0x1);

	drअगरt_state = qed_rd(p_hwfn, p_ptt, NIG_REG_TSGEN_RST_DRIFT_CNTR);
	अगर (drअगरt_state & 1) अणु
		qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_DRIFT_CNTR_CONF,
		       drअगरt_ctr_cfg);
	पूर्ण अन्यथा अणु
		DP_INFO(p_hwfn, "Drift counter is not reset\n");
		वापस -EINVAL;
	पूर्ण

	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_RST_DRIFT_CNTR, 0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_ptp_hw_enable(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt) अणु
		DP_NOTICE(p_hwfn, "Failed to acquire PTT for PTP\n");
		वापस -EBUSY;
	पूर्ण

	p_hwfn->p_ptp_ptt = p_ptt;

	rc = qed_ptp_res_lock(p_hwfn, p_ptt);
	अगर (rc) अणु
		DP_INFO(p_hwfn,
			"Couldn't acquire the resource lock, skip ptp enable for this PF\n");
		qed_ptt_release(p_hwfn, p_ptt);
		p_hwfn->p_ptp_ptt = शून्य;
		वापस rc;
	पूर्ण

	/* Reset PTP event detection rules - will be configured in the IOCTL */
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_PARAM_MASK, 0x7FF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_RULE_MASK, 0x3FFF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_PARAM_MASK, 0x7FF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_RULE_MASK, 0x3FFF);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_PTP_EN, 7);
	qed_wr(p_hwfn, p_ptt, NIG_REG_RX_PTP_EN, 7);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TS_OUTPUT_ENABLE_PDA, 0x1);

	/* Pause मुक्त running counter */
	अगर (QED_IS_BB_B0(p_hwfn->cdev))
		qed_wr(p_hwfn, p_ptt, NIG_REG_TIMESYNC_GEN_REG_BB, 2);
	अगर (QED_IS_AH(p_hwfn->cdev))
		qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_FREECNT_UPDATE_K2, 2);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_FREE_CNT_VALUE_LSB, 0);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_FREE_CNT_VALUE_MSB, 0);
	/* Resume मुक्त running counter */
	अगर (QED_IS_BB_B0(p_hwfn->cdev))
		qed_wr(p_hwfn, p_ptt, NIG_REG_TIMESYNC_GEN_REG_BB, 4);
	अगर (QED_IS_AH(p_hwfn->cdev)) अणु
		qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_FREECNT_UPDATE_K2, 4);
		qed_wr(p_hwfn, p_ptt, NIG_REG_PTP_LATCH_OSTS_PKT_TIME, 1);
	पूर्ण

	/* Disable drअगरt रेजिस्टर */
	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_DRIFT_CNTR_CONF, 0x0);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TSGEN_RST_DRIFT_CNTR, 0x0);

	/* Reset possibly old बारtamps */
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_HOST_BUF_SEQID,
	       QED_TIMESTAMP_MASK);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_BUF_SEQID, QED_TIMESTAMP_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_ptp_hw_disable(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt = p_hwfn->p_ptp_ptt;

	qed_ptp_res_unlock(p_hwfn, p_ptt);

	/* Reset PTP event detection rules */
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_PARAM_MASK, 0x7FF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_LLH_PTP_RULE_MASK, 0x3FFF);

	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_PARAM_MASK, 0x7FF);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_LLH_PTP_RULE_MASK, 0x3FFF);

	/* Disable the PTP feature */
	qed_wr(p_hwfn, p_ptt, NIG_REG_RX_PTP_EN, 0x0);
	qed_wr(p_hwfn, p_ptt, NIG_REG_TX_PTP_EN, 0x0);

	qed_ptt_release(p_hwfn, p_ptt);
	p_hwfn->p_ptp_ptt = शून्य;

	वापस 0;
पूर्ण

स्थिर काष्ठा qed_eth_ptp_ops qed_ptp_ops_pass = अणु
	.cfg_filters = qed_ptp_hw_cfg_filters,
	.पढ़ो_rx_ts = qed_ptp_hw_पढ़ो_rx_ts,
	.पढ़ो_tx_ts = qed_ptp_hw_पढ़ो_tx_ts,
	.पढ़ो_cc = qed_ptp_hw_पढ़ो_cc,
	.adjfreq = qed_ptp_hw_adjfreq,
	.disable = qed_ptp_hw_disable,
	.enable = qed_ptp_hw_enable,
पूर्ण;
