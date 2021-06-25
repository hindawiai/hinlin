<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "ixgbe.h"
#समावेश "ixgbe_type.h"
#समावेश "ixgbe_dcb.h"
#समावेश "ixgbe_dcb_82599.h"

/**
 * ixgbe_dcb_config_rx_arbiter_82599 - Config Rx Data arbiter
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @refill: refill credits index by traffic class
 * @max: max credits index by traffic class
 * @bwg_id: bandwidth grouping indexed by traffic class
 * @prio_type: priority type indexed by traffic class
 * @prio_tc: priority to tc assignments indexed by priority
 *
 * Configure Rx Packet Arbiter and credits क्रम each traffic class.
 */
s32 ixgbe_dcb_config_rx_arbiter_82599(काष्ठा ixgbe_hw *hw,
				      u16 *refill,
				      u16 *max,
				      u8 *bwg_id,
				      u8 *prio_type,
				      u8 *prio_tc)
अणु
	u32    reg           = 0;
	u32    credit_refill = 0;
	u32    credit_max    = 0;
	u8     i             = 0;

	/*
	 * Disable the arbiter beक्रमe changing parameters
	 * (always enable recycle mode; WSP)
	 */
	reg = IXGBE_RTRPCS_RRM | IXGBE_RTRPCS_RAC | IXGBE_RTRPCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTRPCS, reg);

	/* Map all traffic classes to their UP */
	reg = 0;
	क्रम (i = 0; i < MAX_USER_PRIORITY; i++)
		reg |= (prio_tc[i] << (i * IXGBE_RTRUP2TC_UP_SHIFT));
	IXGBE_WRITE_REG(hw, IXGBE_RTRUP2TC, reg);

	/* Configure traffic class credits and priority */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		credit_refill = refill[i];
		credit_max    = max[i];
		reg = credit_refill | (credit_max << IXGBE_RTRPT4C_MCL_SHIFT);

		reg |= (u32)(bwg_id[i]) << IXGBE_RTRPT4C_BWG_SHIFT;

		अगर (prio_type[i] == prio_link)
			reg |= IXGBE_RTRPT4C_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_RTRPT4C(i), reg);
	पूर्ण

	/*
	 * Configure Rx packet plane (recycle mode; WSP) and
	 * enable arbiter
	 */
	reg = IXGBE_RTRPCS_RRM | IXGBE_RTRPCS_RAC;
	IXGBE_WRITE_REG(hw, IXGBE_RTRPCS, reg);

	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_config_tx_desc_arbiter_82599 - Config Tx Desc. arbiter
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @refill: refill credits index by traffic class
 * @max: max credits index by traffic class
 * @bwg_id: bandwidth grouping indexed by traffic class
 * @prio_type: priority type indexed by traffic class
 *
 * Configure Tx Descriptor Arbiter and credits क्रम each traffic class.
 */
s32 ixgbe_dcb_config_tx_desc_arbiter_82599(काष्ठा ixgbe_hw *hw,
					   u16 *refill,
					   u16 *max,
					   u8 *bwg_id,
					   u8 *prio_type)
अणु
	u32    reg, max_credits;
	u8     i;

	/* Clear the per-Tx queue credits; we use per-TC instead */
	क्रम (i = 0; i < 128; i++) अणु
		IXGBE_WRITE_REG(hw, IXGBE_RTTDQSEL, i);
		IXGBE_WRITE_REG(hw, IXGBE_RTTDT1C, 0);
	पूर्ण

	/* Configure traffic class credits and priority */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		max_credits = max[i];
		reg = max_credits << IXGBE_RTTDT2C_MCL_SHIFT;
		reg |= refill[i];
		reg |= (u32)(bwg_id[i]) << IXGBE_RTTDT2C_BWG_SHIFT;

		अगर (prio_type[i] == prio_group)
			reg |= IXGBE_RTTDT2C_GSP;

		अगर (prio_type[i] == prio_link)
			reg |= IXGBE_RTTDT2C_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_RTTDT2C(i), reg);
	पूर्ण

	/*
	 * Configure Tx descriptor plane (recycle mode; WSP) and
	 * enable arbiter
	 */
	reg = IXGBE_RTTDCS_TDPAC | IXGBE_RTTDCS_TDRM;
	IXGBE_WRITE_REG(hw, IXGBE_RTTDCS, reg);

	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_config_tx_data_arbiter_82599 - Config Tx Data arbiter
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @refill: refill credits index by traffic class
 * @max: max credits index by traffic class
 * @bwg_id: bandwidth grouping indexed by traffic class
 * @prio_type: priority type indexed by traffic class
 * @prio_tc: priority to tc assignments indexed by priority
 *
 * Configure Tx Packet Arbiter and credits क्रम each traffic class.
 */
s32 ixgbe_dcb_config_tx_data_arbiter_82599(काष्ठा ixgbe_hw *hw,
					   u16 *refill,
					   u16 *max,
					   u8 *bwg_id,
					   u8 *prio_type,
					   u8 *prio_tc)
अणु
	u32 reg;
	u8 i;

	/*
	 * Disable the arbiter beक्रमe changing parameters
	 * (always enable recycle mode; SP; arb delay)
	 */
	reg = IXGBE_RTTPCS_TPPAC | IXGBE_RTTPCS_TPRM |
	      (IXGBE_RTTPCS_ARBD_DCB << IXGBE_RTTPCS_ARBD_SHIFT) |
	      IXGBE_RTTPCS_ARBDIS;
	IXGBE_WRITE_REG(hw, IXGBE_RTTPCS, reg);

	/* Map all traffic classes to their UP */
	reg = 0;
	क्रम (i = 0; i < MAX_USER_PRIORITY; i++)
		reg |= (prio_tc[i] << (i * IXGBE_RTTUP2TC_UP_SHIFT));
	IXGBE_WRITE_REG(hw, IXGBE_RTTUP2TC, reg);

	/* Configure traffic class credits and priority */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		reg = refill[i];
		reg |= (u32)(max[i]) << IXGBE_RTTPT2C_MCL_SHIFT;
		reg |= (u32)(bwg_id[i]) << IXGBE_RTTPT2C_BWG_SHIFT;

		अगर (prio_type[i] == prio_group)
			reg |= IXGBE_RTTPT2C_GSP;

		अगर (prio_type[i] == prio_link)
			reg |= IXGBE_RTTPT2C_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_RTTPT2C(i), reg);
	पूर्ण

	/*
	 * Configure Tx packet plane (recycle mode; SP; arb delay) and
	 * enable arbiter
	 */
	reg = IXGBE_RTTPCS_TPPAC | IXGBE_RTTPCS_TPRM |
	      (IXGBE_RTTPCS_ARBD_DCB << IXGBE_RTTPCS_ARBD_SHIFT);
	IXGBE_WRITE_REG(hw, IXGBE_RTTPCS, reg);

	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_config_pfc_82599 - Configure priority flow control
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @pfc_en: enabled pfc biपंचांगask
 * @prio_tc: priority to tc assignments indexed by priority
 *
 * Configure Priority Flow Control (PFC) क्रम each traffic class.
 */
s32 ixgbe_dcb_config_pfc_82599(काष्ठा ixgbe_hw *hw, u8 pfc_en, u8 *prio_tc)
अणु
	u32 i, j, fcrtl, reg;
	u8 max_tc = 0;

	/* Enable Transmit Priority Flow Control */
	IXGBE_WRITE_REG(hw, IXGBE_FCCFG, IXGBE_FCCFG_TFCE_PRIORITY);

	/* Enable Receive Priority Flow Control */
	reg = IXGBE_READ_REG(hw, IXGBE_MFLCN);
	reg |= IXGBE_MFLCN_DPF;

	/*
	 * X540 & X550 supports per TC Rx priority flow control.
	 * So clear all TCs and only enable those that should be
	 * enabled.
	 */
	reg &= ~(IXGBE_MFLCN_RPFCE_MASK | IXGBE_MFLCN_RFCE);

	अगर (hw->mac.type >= ixgbe_mac_X540)
		reg |= pfc_en << IXGBE_MFLCN_RPFCE_SHIFT;

	अगर (pfc_en)
		reg |= IXGBE_MFLCN_RPFCE;

	IXGBE_WRITE_REG(hw, IXGBE_MFLCN, reg);

	क्रम (i = 0; i < MAX_USER_PRIORITY; i++) अणु
		अगर (prio_tc[i] > max_tc)
			max_tc = prio_tc[i];
	पूर्ण


	/* Configure PFC Tx thresholds per TC */
	क्रम (i = 0; i <= max_tc; i++) अणु
		पूर्णांक enabled = 0;

		क्रम (j = 0; j < MAX_USER_PRIORITY; j++) अणु
			अगर ((prio_tc[j] == i) && (pfc_en & BIT(j))) अणु
				enabled = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (enabled) अणु
			reg = (hw->fc.high_water[i] << 10) | IXGBE_FCRTH_FCEN;
			fcrtl = (hw->fc.low_water[i] << 10) | IXGBE_FCRTL_XONE;
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL_82599(i), fcrtl);
		पूर्ण अन्यथा अणु
			/* In order to prevent Tx hangs when the पूर्णांकernal Tx
			 * चयन is enabled we must set the high water mark
			 * to the Rx packet buffer size - 24KB.  This allows
			 * the Tx चयन to function even under heavy Rx
			 * workloads.
			 */
			reg = IXGBE_READ_REG(hw, IXGBE_RXPBSIZE(i)) - 24576;
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL_82599(i), 0);
		पूर्ण

		IXGBE_WRITE_REG(hw, IXGBE_FCRTH_82599(i), reg);
	पूर्ण

	क्रम (; i < MAX_TRAFFIC_CLASS; i++) अणु
		IXGBE_WRITE_REG(hw, IXGBE_FCRTL_82599(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_FCRTH_82599(i), 0);
	पूर्ण

	/* Configure छोड़ो समय (2 TCs per रेजिस्टर) */
	reg = hw->fc.छोड़ो_समय * 0x00010001;
	क्रम (i = 0; i < (MAX_TRAFFIC_CLASS / 2); i++)
		IXGBE_WRITE_REG(hw, IXGBE_FCTTV(i), reg);

	/* Configure flow control refresh threshold value */
	IXGBE_WRITE_REG(hw, IXGBE_FCRTV, hw->fc.छोड़ो_समय / 2);

	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_config_tc_stats_82599 - Config traffic class statistics
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Configure queue statistics रेजिस्टरs, all queues beदीर्घing to same traffic
 * class uses a single set of queue statistics counters.
 */
अटल s32 ixgbe_dcb_config_tc_stats_82599(काष्ठा ixgbe_hw *hw)
अणु
	u32 reg = 0;
	u8  i   = 0;

	/*
	 * Receive Queues stats setting
	 * 32 RQSMR रेजिस्टरs, each configuring 4 queues.
	 * Set all 16 queues of each TC to the same stat
	 * with TC 'n' going to stat 'n'.
	 */
	क्रम (i = 0; i < 32; i++) अणु
		reg = 0x01010101 * (i / 4);
		IXGBE_WRITE_REG(hw, IXGBE_RQSMR(i), reg);
	पूर्ण
	/*
	 * Transmit Queues stats setting
	 * 32 TQSM रेजिस्टरs, each controlling 4 queues.
	 * Set all queues of each TC to the same stat
	 * with TC 'n' going to stat 'n'.
	 * Tx queues are allocated non-unअगरormly to TCs:
	 * 32, 32, 16, 16, 8, 8, 8, 8.
	 */
	क्रम (i = 0; i < 32; i++) अणु
		अगर (i < 8)
			reg = 0x00000000;
		अन्यथा अगर (i < 16)
			reg = 0x01010101;
		अन्यथा अगर (i < 20)
			reg = 0x02020202;
		अन्यथा अगर (i < 24)
			reg = 0x03030303;
		अन्यथा अगर (i < 26)
			reg = 0x04040404;
		अन्यथा अगर (i < 28)
			reg = 0x05050505;
		अन्यथा अगर (i < 30)
			reg = 0x06060606;
		अन्यथा
			reg = 0x07070707;
		IXGBE_WRITE_REG(hw, IXGBE_TQSM(i), reg);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_hw_config_82599 - Configure and enable DCB
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @pfc_en: enabled pfc biपंचांगask
 * @refill: refill credits index by traffic class
 * @max: max credits index by traffic class
 * @bwg_id: bandwidth grouping indexed by traffic class
 * @prio_type: priority type indexed by traffic class
 * @prio_tc: priority to tc assignments indexed by priority
 *
 * Configure dcb settings and enable dcb mode.
 */
s32 ixgbe_dcb_hw_config_82599(काष्ठा ixgbe_hw *hw, u8 pfc_en, u16 *refill,
			      u16 *max, u8 *bwg_id, u8 *prio_type, u8 *prio_tc)
अणु
	ixgbe_dcb_config_rx_arbiter_82599(hw, refill, max, bwg_id,
					  prio_type, prio_tc);
	ixgbe_dcb_config_tx_desc_arbiter_82599(hw, refill, max,
					       bwg_id, prio_type);
	ixgbe_dcb_config_tx_data_arbiter_82599(hw, refill, max,
					       bwg_id, prio_type, prio_tc);
	ixgbe_dcb_config_pfc_82599(hw, pfc_en, prio_tc);
	ixgbe_dcb_config_tc_stats_82599(hw);

	वापस 0;
पूर्ण

