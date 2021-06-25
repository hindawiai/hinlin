<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "ixgbe.h"
#समावेश "ixgbe_type.h"
#समावेश "ixgbe_dcb.h"
#समावेश "ixgbe_dcb_82598.h"
#समावेश "ixgbe_dcb_82599.h"

/**
 * ixgbe_ieee_credits - This calculates the ieee traffic class
 * credits from the configured bandwidth percentages. Credits
 * are the smallest unit programmable पूर्णांकo the underlying
 * hardware. The IEEE 802.1Qaz specअगरication करो not use bandwidth
 * groups so this is much simplअगरied from the CEE हाल.
 * @bw: bandwidth index by traffic class
 * @refill: refill credits index by traffic class
 * @max: max credits by traffic class
 * @max_frame: maximum frame size
 */
अटल s32 ixgbe_ieee_credits(__u8 *bw, __u16 *refill,
			      __u16 *max, पूर्णांक max_frame)
अणु
	पूर्णांक min_percent = 100;
	पूर्णांक min_credit, multiplier;
	पूर्णांक i;

	min_credit = ((max_frame / 2) + DCB_CREDIT_QUANTUM - 1) /
			DCB_CREDIT_QUANTUM;

	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		अगर (bw[i] < min_percent && bw[i])
			min_percent = bw[i];
	पूर्ण

	multiplier = (min_credit / min_percent) + 1;

	/* Find out the hw credits क्रम each TC */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		पूर्णांक val = min(bw[i] * multiplier, MAX_CREDIT_REFILL);

		अगर (val < min_credit)
			val = min_credit;
		refill[i] = val;

		max[i] = bw[i] ? (bw[i] * MAX_CREDIT)/100 : min_credit;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_calculate_tc_credits - Calculates traffic class credits
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @dcb_config: Struct containing DCB settings
 * @max_frame: Maximum frame size
 * @direction: Configuring either Tx or Rx
 *
 * This function calculates the credits allocated to each traffic class.
 * It should be called only after the rules are checked by
 * ixgbe_dcb_check_config().
 */
s32 ixgbe_dcb_calculate_tc_credits(काष्ठा ixgbe_hw *hw,
				   काष्ठा ixgbe_dcb_config *dcb_config,
				   पूर्णांक max_frame, u8 direction)
अणु
	काष्ठा tc_bw_alloc *p;
	पूर्णांक min_credit;
	पूर्णांक min_multiplier;
	पूर्णांक min_percent = 100;
	/* Initialization values शेष क्रम Tx settings */
	u32 credit_refill       = 0;
	u32 credit_max          = 0;
	u16 link_percentage     = 0;
	u8  bw_percent          = 0;
	u8  i;

	अगर (!dcb_config)
		वापस DCB_ERR_CONFIG;

	min_credit = ((max_frame / 2) + DCB_CREDIT_QUANTUM - 1) /
			DCB_CREDIT_QUANTUM;

	/* Find smallest link percentage */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		p = &dcb_config->tc_config[i].path[direction];
		bw_percent = dcb_config->bw_percentage[direction][p->bwg_id];
		link_percentage = p->bwg_percent;

		link_percentage = (link_percentage * bw_percent) / 100;

		अगर (link_percentage && link_percentage < min_percent)
			min_percent = link_percentage;
	पूर्ण

	/*
	 * The ratio between traffic classes will control the bandwidth
	 * percentages seen on the wire. To calculate this ratio we use
	 * a multiplier. It is required that the refill credits must be
	 * larger than the max frame size so here we find the smallest
	 * multiplier that will allow all bandwidth percentages to be
	 * greater than the max frame size.
	 */
	min_multiplier = (min_credit / min_percent) + 1;

	/* Find out the link percentage क्रम each TC first */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		p = &dcb_config->tc_config[i].path[direction];
		bw_percent = dcb_config->bw_percentage[direction][p->bwg_id];

		link_percentage = p->bwg_percent;
		/* Must be careful of पूर्णांकeger भागision क्रम very small nums */
		link_percentage = (link_percentage * bw_percent) / 100;
		अगर (p->bwg_percent > 0 && link_percentage == 0)
			link_percentage = 1;

		/* Save link_percentage क्रम reference */
		p->link_percent = (u8)link_percentage;

		/* Calculate credit refill ratio using multiplier */
		credit_refill = min(link_percentage * min_multiplier,
				    MAX_CREDIT_REFILL);

		/* Refill at least minimum credit */
		अगर (credit_refill < min_credit)
			credit_refill = min_credit;

		p->data_credits_refill = (u16)credit_refill;

		/* Calculate maximum credit क्रम the TC */
		credit_max = (link_percentage * MAX_CREDIT) / 100;

		/*
		 * Adjusपंचांगent based on rule checking, अगर the percentage
		 * of a TC is too small, the maximum credit may not be
		 * enough to send out a jumbo frame in data plane arbitration.
		 */
		अगर (credit_max < min_credit)
			credit_max = min_credit;

		अगर (direction == DCB_TX_CONFIG) अणु
			/*
			 * Adjusपंचांगent based on rule checking, अगर the
			 * percentage of a TC is too small, the maximum
			 * credit may not be enough to send out a TSO
			 * packet in descriptor plane arbitration.
			 */
			अगर ((hw->mac.type == ixgbe_mac_82598EB) &&
			    credit_max &&
			    (credit_max < MINIMUM_CREDIT_FOR_TSO))
				credit_max = MINIMUM_CREDIT_FOR_TSO;

			dcb_config->tc_config[i].desc_credits_max =
				(u16)credit_max;
		पूर्ण

		p->data_credits_max = (u16)credit_max;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ixgbe_dcb_unpack_pfc(काष्ठा ixgbe_dcb_config *cfg, u8 *pfc_en)
अणु
	काष्ठा tc_configuration *tc_config = &cfg->tc_config[0];
	पूर्णांक tc;

	क्रम (*pfc_en = 0, tc = 0; tc < MAX_TRAFFIC_CLASS; tc++) अणु
		अगर (tc_config[tc].dcb_pfc != pfc_disabled)
			*pfc_en |= BIT(tc);
	पूर्ण
पूर्ण

व्योम ixgbe_dcb_unpack_refill(काष्ठा ixgbe_dcb_config *cfg, पूर्णांक direction,
			     u16 *refill)
अणु
	काष्ठा tc_configuration *tc_config = &cfg->tc_config[0];
	पूर्णांक tc;

	क्रम (tc = 0; tc < MAX_TRAFFIC_CLASS; tc++)
		refill[tc] = tc_config[tc].path[direction].data_credits_refill;
पूर्ण

व्योम ixgbe_dcb_unpack_max(काष्ठा ixgbe_dcb_config *cfg, u16 *max)
अणु
	काष्ठा tc_configuration *tc_config = &cfg->tc_config[0];
	पूर्णांक tc;

	क्रम (tc = 0; tc < MAX_TRAFFIC_CLASS; tc++)
		max[tc] = tc_config[tc].desc_credits_max;
पूर्ण

व्योम ixgbe_dcb_unpack_bwgid(काष्ठा ixgbe_dcb_config *cfg, पूर्णांक direction,
			    u8 *bwgid)
अणु
	काष्ठा tc_configuration *tc_config = &cfg->tc_config[0];
	पूर्णांक tc;

	क्रम (tc = 0; tc < MAX_TRAFFIC_CLASS; tc++)
		bwgid[tc] = tc_config[tc].path[direction].bwg_id;
पूर्ण

व्योम ixgbe_dcb_unpack_prio(काष्ठा ixgbe_dcb_config *cfg, पूर्णांक direction,
			    u8 *ptype)
अणु
	काष्ठा tc_configuration *tc_config = &cfg->tc_config[0];
	पूर्णांक tc;

	क्रम (tc = 0; tc < MAX_TRAFFIC_CLASS; tc++)
		ptype[tc] = tc_config[tc].path[direction].prio_type;
पूर्ण

u8 ixgbe_dcb_get_tc_from_up(काष्ठा ixgbe_dcb_config *cfg, पूर्णांक direction, u8 up)
अणु
	काष्ठा tc_configuration *tc_config = &cfg->tc_config[0];
	u8 prio_mask = BIT(up);
	u8 tc = cfg->num_tcs.pg_tcs;

	/* If tc is 0 then DCB is likely not enabled or supported */
	अगर (!tc)
		वापस 0;

	/*
	 * Test from maximum TC to 1 and report the first match we find.  If
	 * we find no match we can assume that the TC is 0 since the TC must
	 * be set क्रम all user priorities
	 */
	क्रम (tc--; tc; tc--) अणु
		अगर (prio_mask & tc_config[tc].path[direction].up_to_tc_biपंचांगap)
			अवरोध;
	पूर्ण

	वापस tc;
पूर्ण

व्योम ixgbe_dcb_unpack_map(काष्ठा ixgbe_dcb_config *cfg, पूर्णांक direction, u8 *map)
अणु
	u8 up;

	क्रम (up = 0; up < MAX_USER_PRIORITY; up++)
		map[up] = ixgbe_dcb_get_tc_from_up(cfg, direction, up);
पूर्ण

/**
 * ixgbe_dcb_hw_config - Config and enable DCB
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @dcb_config: poपूर्णांकer to ixgbe_dcb_config काष्ठाure
 *
 * Configure dcb settings and enable dcb mode.
 */
s32 ixgbe_dcb_hw_config(काष्ठा ixgbe_hw *hw,
			काष्ठा ixgbe_dcb_config *dcb_config)
अणु
	u8 pfc_en;
	u8 ptype[MAX_TRAFFIC_CLASS];
	u8 bwgid[MAX_TRAFFIC_CLASS];
	u8 prio_tc[MAX_TRAFFIC_CLASS];
	u16 refill[MAX_TRAFFIC_CLASS];
	u16 max[MAX_TRAFFIC_CLASS];

	/* Unpack CEE standard containers */
	ixgbe_dcb_unpack_pfc(dcb_config, &pfc_en);
	ixgbe_dcb_unpack_refill(dcb_config, DCB_TX_CONFIG, refill);
	ixgbe_dcb_unpack_max(dcb_config, max);
	ixgbe_dcb_unpack_bwgid(dcb_config, DCB_TX_CONFIG, bwgid);
	ixgbe_dcb_unpack_prio(dcb_config, DCB_TX_CONFIG, ptype);
	ixgbe_dcb_unpack_map(dcb_config, DCB_TX_CONFIG, prio_tc);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		वापस ixgbe_dcb_hw_config_82598(hw, pfc_en, refill, max,
						 bwgid, ptype);
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		वापस ixgbe_dcb_hw_config_82599(hw, pfc_en, refill, max,
						 bwgid, ptype, prio_tc);
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Helper routines to असलtract HW specअगरics from DCB netlink ops */
s32 ixgbe_dcb_hw_pfc_config(काष्ठा ixgbe_hw *hw, u8 pfc_en, u8 *prio_tc)
अणु
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		वापस ixgbe_dcb_config_pfc_82598(hw, pfc_en);
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		वापस ixgbe_dcb_config_pfc_82599(hw, pfc_en, prio_tc);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

s32 ixgbe_dcb_hw_ets(काष्ठा ixgbe_hw *hw, काष्ठा ieee_ets *ets, पूर्णांक max_frame)
अणु
	__u16 refill[IEEE_8021QAZ_MAX_TCS], max[IEEE_8021QAZ_MAX_TCS];
	__u8 prio_type[IEEE_8021QAZ_MAX_TCS];
	पूर्णांक i;

	/* naively give each TC a bwg to map onto CEE hardware */
	__u8 bwg_id[IEEE_8021QAZ_MAX_TCS] = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण;

	/* Map TSA onto CEE prio type */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_STRICT:
			prio_type[i] = 2;
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			prio_type[i] = 0;
			अवरोध;
		शेष:
			/* Hardware only supports priority strict or
			 * ETS transmission selection algorithms अगर
			 * we receive some other value from dcbnl
			 * throw an error
			 */
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ixgbe_ieee_credits(ets->tc_tx_bw, refill, max, max_frame);
	वापस ixgbe_dcb_hw_ets_config(hw, refill, max,
				       bwg_id, prio_type, ets->prio_tc);
पूर्ण

s32 ixgbe_dcb_hw_ets_config(काष्ठा ixgbe_hw *hw,
			    u16 *refill, u16 *max, u8 *bwg_id,
			    u8 *prio_type, u8 *prio_tc)
अणु
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		ixgbe_dcb_config_rx_arbiter_82598(hw, refill, max,
							prio_type);
		ixgbe_dcb_config_tx_desc_arbiter_82598(hw, refill, max,
							     bwg_id, prio_type);
		ixgbe_dcb_config_tx_data_arbiter_82598(hw, refill, max,
							     bwg_id, prio_type);
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		ixgbe_dcb_config_rx_arbiter_82599(hw, refill, max,
						  bwg_id, prio_type, prio_tc);
		ixgbe_dcb_config_tx_desc_arbiter_82599(hw, refill, max,
						       bwg_id, prio_type);
		ixgbe_dcb_config_tx_data_arbiter_82599(hw, refill, max, bwg_id,
						       prio_type, prio_tc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ixgbe_dcb_पढ़ो_rtrup2tc_82599(काष्ठा ixgbe_hw *hw, u8 *map)
अणु
	u32 reg, i;

	reg = IXGBE_READ_REG(hw, IXGBE_RTRUP2TC);
	क्रम (i = 0; i < MAX_USER_PRIORITY; i++)
		map[i] = IXGBE_RTRUP2TC_UP_MASK &
			(reg >> (i * IXGBE_RTRUP2TC_UP_SHIFT));
पूर्ण

व्योम ixgbe_dcb_पढ़ो_rtrup2tc(काष्ठा ixgbe_hw *hw, u8 *map)
अणु
	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		ixgbe_dcb_पढ़ो_rtrup2tc_82599(hw, map);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
