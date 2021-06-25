<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "ixgbe.h"
#समावेश "ixgbe_type.h"
#समावेश "ixgbe_dcb.h"
#समावेश "ixgbe_dcb_82598.h"

/**
 * ixgbe_dcb_config_rx_arbiter_82598 - Config Rx data arbiter
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @refill: refill credits index by traffic class
 * @max: max credits index by traffic class
 * @prio_type: priority type indexed by traffic class
 *
 * Configure Rx Data Arbiter and credits क्रम each traffic class.
 */
s32 ixgbe_dcb_config_rx_arbiter_82598(काष्ठा ixgbe_hw *hw,
					u16 *refill,
					u16 *max,
					u8 *prio_type)
अणु
	u32    reg           = 0;
	u32    credit_refill = 0;
	u32    credit_max    = 0;
	u8     i             = 0;

	reg = IXGBE_READ_REG(hw, IXGBE_RUPPBMR) | IXGBE_RUPPBMR_MQA;
	IXGBE_WRITE_REG(hw, IXGBE_RUPPBMR, reg);

	reg = IXGBE_READ_REG(hw, IXGBE_RMCS);
	/* Enable Arbiter */
	reg &= ~IXGBE_RMCS_ARBDIS;
	/* Enable Receive Recycle within the BWG */
	reg |= IXGBE_RMCS_RRM;
	/* Enable Deficit Fixed Priority arbitration*/
	reg |= IXGBE_RMCS_DFP;

	IXGBE_WRITE_REG(hw, IXGBE_RMCS, reg);

	/* Configure traffic class credits and priority */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		credit_refill = refill[i];
		credit_max    = max[i];

		reg = credit_refill | (credit_max << IXGBE_RT2CR_MCL_SHIFT);

		अगर (prio_type[i] == prio_link)
			reg |= IXGBE_RT2CR_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_RT2CR(i), reg);
	पूर्ण

	reg = IXGBE_READ_REG(hw, IXGBE_RDRXCTL);
	reg |= IXGBE_RDRXCTL_RDMTS_1_2;
	reg |= IXGBE_RDRXCTL_MPBEN;
	reg |= IXGBE_RDRXCTL_MCEN;
	IXGBE_WRITE_REG(hw, IXGBE_RDRXCTL, reg);

	reg = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	/* Make sure there is enough descriptors beक्रमe arbitration */
	reg &= ~IXGBE_RXCTRL_DMBYPS;
	IXGBE_WRITE_REG(hw, IXGBE_RXCTRL, reg);

	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_config_tx_desc_arbiter_82598 - Config Tx Desc. arbiter
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @refill: refill credits index by traffic class
 * @max: max credits index by traffic class
 * @bwg_id: bandwidth grouping indexed by traffic class
 * @prio_type: priority type indexed by traffic class
 *
 * Configure Tx Descriptor Arbiter and credits क्रम each traffic class.
 */
s32 ixgbe_dcb_config_tx_desc_arbiter_82598(काष्ठा ixgbe_hw *hw,
						u16 *refill,
						u16 *max,
						u8 *bwg_id,
						u8 *prio_type)
अणु
	u32    reg, max_credits;
	u8     i;

	reg = IXGBE_READ_REG(hw, IXGBE_DPMCS);

	/* Enable arbiter */
	reg &= ~IXGBE_DPMCS_ARBDIS;
	reg |= IXGBE_DPMCS_TSOEF;

	/* Configure Max TSO packet size 34KB including payload and headers */
	reg |= (0x4 << IXGBE_DPMCS_MTSOS_SHIFT);

	IXGBE_WRITE_REG(hw, IXGBE_DPMCS, reg);

	/* Configure traffic class credits and priority */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		max_credits = max[i];
		reg = max_credits << IXGBE_TDTQ2TCCR_MCL_SHIFT;
		reg |= refill[i];
		reg |= (u32)(bwg_id[i]) << IXGBE_TDTQ2TCCR_BWG_SHIFT;

		अगर (prio_type[i] == prio_group)
			reg |= IXGBE_TDTQ2TCCR_GSP;

		अगर (prio_type[i] == prio_link)
			reg |= IXGBE_TDTQ2TCCR_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_TDTQ2TCCR(i), reg);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_config_tx_data_arbiter_82598 - Config Tx data arbiter
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @refill: refill credits index by traffic class
 * @max: max credits index by traffic class
 * @bwg_id: bandwidth grouping indexed by traffic class
 * @prio_type: priority type indexed by traffic class
 *
 * Configure Tx Data Arbiter and credits क्रम each traffic class.
 */
s32 ixgbe_dcb_config_tx_data_arbiter_82598(काष्ठा ixgbe_hw *hw,
						u16 *refill,
						u16 *max,
						u8 *bwg_id,
						u8 *prio_type)
अणु
	u32 reg;
	u8 i;

	reg = IXGBE_READ_REG(hw, IXGBE_PDPMCS);
	/* Enable Data Plane Arbiter */
	reg &= ~IXGBE_PDPMCS_ARBDIS;
	/* Enable DFP and Transmit Recycle Mode */
	reg |= (IXGBE_PDPMCS_TPPAC | IXGBE_PDPMCS_TRM);

	IXGBE_WRITE_REG(hw, IXGBE_PDPMCS, reg);

	/* Configure traffic class credits and priority */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		reg = refill[i];
		reg |= (u32)(max[i]) << IXGBE_TDPT2TCCR_MCL_SHIFT;
		reg |= (u32)(bwg_id[i]) << IXGBE_TDPT2TCCR_BWG_SHIFT;

		अगर (prio_type[i] == prio_group)
			reg |= IXGBE_TDPT2TCCR_GSP;

		अगर (prio_type[i] == prio_link)
			reg |= IXGBE_TDPT2TCCR_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_TDPT2TCCR(i), reg);
	पूर्ण

	/* Enable Tx packet buffer भागision */
	reg = IXGBE_READ_REG(hw, IXGBE_DTXCTL);
	reg |= IXGBE_DTXCTL_ENDBUBD;
	IXGBE_WRITE_REG(hw, IXGBE_DTXCTL, reg);

	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_config_pfc_82598 - Config priority flow control
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @pfc_en: enabled pfc biपंचांगask
 *
 * Configure Priority Flow Control क्रम each traffic class.
 */
s32 ixgbe_dcb_config_pfc_82598(काष्ठा ixgbe_hw *hw, u8 pfc_en)
अणु
	u32 fcrtl, reg;
	u8  i;

	/* Enable Transmit Priority Flow Control */
	reg = IXGBE_READ_REG(hw, IXGBE_RMCS);
	reg &= ~IXGBE_RMCS_TFCE_802_3X;
	reg |= IXGBE_RMCS_TFCE_PRIORITY;
	IXGBE_WRITE_REG(hw, IXGBE_RMCS, reg);

	/* Enable Receive Priority Flow Control */
	reg = IXGBE_READ_REG(hw, IXGBE_FCTRL);
	reg &= ~(IXGBE_FCTRL_RPFCE | IXGBE_FCTRL_RFCE);

	अगर (pfc_en)
		reg |= IXGBE_FCTRL_RPFCE;

	IXGBE_WRITE_REG(hw, IXGBE_FCTRL, reg);

	/* Configure PFC Tx thresholds per TC */
	क्रम (i = 0; i < MAX_TRAFFIC_CLASS; i++) अणु
		अगर (!(pfc_en & BIT(i))) अणु
			IXGBE_WRITE_REG(hw, IXGBE_FCRTL(i), 0);
			IXGBE_WRITE_REG(hw, IXGBE_FCRTH(i), 0);
			जारी;
		पूर्ण

		fcrtl = (hw->fc.low_water[i] << 10) | IXGBE_FCRTL_XONE;
		reg = (hw->fc.high_water[i] << 10) | IXGBE_FCRTH_FCEN;
		IXGBE_WRITE_REG(hw, IXGBE_FCRTL(i), fcrtl);
		IXGBE_WRITE_REG(hw, IXGBE_FCRTH(i), reg);
	पूर्ण

	/* Configure छोड़ो समय */
	reg = hw->fc.छोड़ो_समय * 0x00010001;
	क्रम (i = 0; i < (MAX_TRAFFIC_CLASS / 2); i++)
		IXGBE_WRITE_REG(hw, IXGBE_FCTTV(i), reg);

	/* Configure flow control refresh threshold value */
	IXGBE_WRITE_REG(hw, IXGBE_FCRTV, hw->fc.छोड़ो_समय / 2);


	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_config_tc_stats_82598 - Configure traffic class statistics
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Configure queue statistics रेजिस्टरs, all queues beदीर्घing to same traffic
 * class uses a single set of queue statistics counters.
 */
अटल s32 ixgbe_dcb_config_tc_stats_82598(काष्ठा ixgbe_hw *hw)
अणु
	u32 reg = 0;
	u8  i   = 0;
	u8  j   = 0;

	/* Receive Queues stats setting -  8 queues per statistics reg */
	क्रम (i = 0, j = 0; i < 15 && j < 8; i = i + 2, j++) अणु
		reg = IXGBE_READ_REG(hw, IXGBE_RQSMR(i));
		reg |= ((0x1010101) * j);
		IXGBE_WRITE_REG(hw, IXGBE_RQSMR(i), reg);
		reg = IXGBE_READ_REG(hw, IXGBE_RQSMR(i + 1));
		reg |= ((0x1010101) * j);
		IXGBE_WRITE_REG(hw, IXGBE_RQSMR(i + 1), reg);
	पूर्ण
	/* Transmit Queues stats setting -  4 queues per statistics reg */
	क्रम (i = 0; i < 8; i++) अणु
		reg = IXGBE_READ_REG(hw, IXGBE_TQSMR(i));
		reg |= ((0x1010101) * i);
		IXGBE_WRITE_REG(hw, IXGBE_TQSMR(i), reg);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_dcb_hw_config_82598 - Config and enable DCB
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @pfc_en: enabled pfc biपंचांगask
 * @refill: refill credits index by traffic class
 * @max: max credits index by traffic class
 * @bwg_id: bandwidth grouping indexed by traffic class
 * @prio_type: priority type indexed by traffic class
 *
 * Configure dcb settings and enable dcb mode.
 */
s32 ixgbe_dcb_hw_config_82598(काष्ठा ixgbe_hw *hw, u8 pfc_en, u16 *refill,
			      u16 *max, u8 *bwg_id, u8 *prio_type)
अणु
	ixgbe_dcb_config_rx_arbiter_82598(hw, refill, max, prio_type);
	ixgbe_dcb_config_tx_desc_arbiter_82598(hw, refill, max,
					       bwg_id, prio_type);
	ixgbe_dcb_config_tx_data_arbiter_82598(hw, refill, max,
					       bwg_id, prio_type);
	ixgbe_dcb_config_pfc_82598(hw, pfc_en);
	ixgbe_dcb_config_tc_stats_82598(hw);

	वापस 0;
पूर्ण
