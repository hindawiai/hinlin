<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Driver क्रम Microsemi VSC85xx PHYs - MACsec support
 *
 * Author: Antoine Tenart
 * License: Dual MIT/GPL
 * Copyright (c) 2020 Microsemi Corporation
 */

#समावेश <linux/phy.h>
#समावेश <dt-bindings/net/mscc-phy-vsc8531.h>

#समावेश <crypto/aes.h>

#समावेश <net/macsec.h>

#समावेश "mscc.h"
#समावेश "mscc_mac.h"
#समावेश "mscc_macsec.h"
#समावेश "mscc_fc_buffer.h"

अटल u32 vsc8584_macsec_phy_पढ़ो(काष्ठा phy_device *phydev,
				   क्रमागत macsec_bank bank, u32 reg)
अणु
	u32 val, val_l = 0, val_h = 0;
	अचिन्हित दीर्घ deadline;
	पूर्णांक rc;

	rc = phy_select_page(phydev, MSCC_PHY_PAGE_MACSEC);
	अगर (rc < 0)
		जाओ failed;

	__phy_ग_लिखो(phydev, MSCC_EXT_PAGE_MACSEC_20,
		    MSCC_PHY_MACSEC_20_TARGET(bank >> 2));

	अगर (bank >> 2 == 0x1)
		/* non-MACsec access */
		bank &= 0x3;
	अन्यथा
		bank = 0;

	__phy_ग_लिखो(phydev, MSCC_EXT_PAGE_MACSEC_19,
		    MSCC_PHY_MACSEC_19_CMD | MSCC_PHY_MACSEC_19_READ |
		    MSCC_PHY_MACSEC_19_REG_ADDR(reg) |
		    MSCC_PHY_MACSEC_19_TARGET(bank));

	deadline = jअगरfies + msecs_to_jअगरfies(PROC_CMD_NCOMPLETED_TIMEOUT_MS);
	करो अणु
		val = __phy_पढ़ो(phydev, MSCC_EXT_PAGE_MACSEC_19);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, deadline) && !(val & MSCC_PHY_MACSEC_19_CMD));

	val_l = __phy_पढ़ो(phydev, MSCC_EXT_PAGE_MACSEC_17);
	val_h = __phy_पढ़ो(phydev, MSCC_EXT_PAGE_MACSEC_18);

failed:
	phy_restore_page(phydev, rc, rc);

	वापस (val_h << 16) | val_l;
पूर्ण

अटल व्योम vsc8584_macsec_phy_ग_लिखो(काष्ठा phy_device *phydev,
				     क्रमागत macsec_bank bank, u32 reg, u32 val)
अणु
	अचिन्हित दीर्घ deadline;
	पूर्णांक rc;

	rc = phy_select_page(phydev, MSCC_PHY_PAGE_MACSEC);
	अगर (rc < 0)
		जाओ failed;

	__phy_ग_लिखो(phydev, MSCC_EXT_PAGE_MACSEC_20,
		    MSCC_PHY_MACSEC_20_TARGET(bank >> 2));

	अगर ((bank >> 2 == 0x1) || (bank >> 2 == 0x3))
		bank &= 0x3;
	अन्यथा
		/* MACsec access */
		bank = 0;

	__phy_ग_लिखो(phydev, MSCC_EXT_PAGE_MACSEC_17, (u16)val);
	__phy_ग_लिखो(phydev, MSCC_EXT_PAGE_MACSEC_18, (u16)(val >> 16));

	__phy_ग_लिखो(phydev, MSCC_EXT_PAGE_MACSEC_19,
		    MSCC_PHY_MACSEC_19_CMD | MSCC_PHY_MACSEC_19_REG_ADDR(reg) |
		    MSCC_PHY_MACSEC_19_TARGET(bank));

	deadline = jअगरfies + msecs_to_jअगरfies(PROC_CMD_NCOMPLETED_TIMEOUT_MS);
	करो अणु
		val = __phy_पढ़ो(phydev, MSCC_EXT_PAGE_MACSEC_19);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, deadline) && !(val & MSCC_PHY_MACSEC_19_CMD));

failed:
	phy_restore_page(phydev, rc, rc);
पूर्ण

अटल व्योम vsc8584_macsec_classअगरication(काष्ठा phy_device *phydev,
					  क्रमागत macsec_bank bank)
अणु
	/* enable VLAN tag parsing */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_CP_TAG,
				 MSCC_MS_SAM_CP_TAG_PARSE_STAG |
				 MSCC_MS_SAM_CP_TAG_PARSE_QTAG |
				 MSCC_MS_SAM_CP_TAG_PARSE_QINQ);
पूर्ण

अटल व्योम vsc8584_macsec_flow_शेष_action(काष्ठा phy_device *phydev,
					       क्रमागत macsec_bank bank,
					       bool block)
अणु
	u32 port = (bank == MACSEC_INGR) ?
		    MSCC_MS_PORT_UNCONTROLLED : MSCC_MS_PORT_COMMON;
	u32 action = MSCC_MS_FLOW_BYPASS;

	अगर (block)
		action = MSCC_MS_FLOW_DROP;

	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_NM_FLOW_NCP,
				 /* MACsec untagged */
				 MSCC_MS_SAM_NM_FLOW_NCP_UNTAGGED_FLOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FLOW_NCP_UNTAGGED_DROP_ACTION(MSCC_MS_ACTION_DROP) |
				 MSCC_MS_SAM_NM_FLOW_NCP_UNTAGGED_DEST_PORT(port) |
				 /* MACsec tagged */
				 MSCC_MS_SAM_NM_FLOW_NCP_TAGGED_FLOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FLOW_NCP_TAGGED_DROP_ACTION(MSCC_MS_ACTION_DROP) |
				 MSCC_MS_SAM_NM_FLOW_NCP_TAGGED_DEST_PORT(port) |
				 /* Bad tag */
				 MSCC_MS_SAM_NM_FLOW_NCP_BADTAG_FLOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FLOW_NCP_BADTAG_DROP_ACTION(MSCC_MS_ACTION_DROP) |
				 MSCC_MS_SAM_NM_FLOW_NCP_BADTAG_DEST_PORT(port) |
				 /* Kay tag */
				 MSCC_MS_SAM_NM_FLOW_NCP_KAY_FLOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FLOW_NCP_KAY_DROP_ACTION(MSCC_MS_ACTION_DROP) |
				 MSCC_MS_SAM_NM_FLOW_NCP_KAY_DEST_PORT(port));
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_NM_FLOW_CP,
				 /* MACsec untagged */
				 MSCC_MS_SAM_NM_FLOW_NCP_UNTAGGED_FLOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FLOW_CP_UNTAGGED_DROP_ACTION(MSCC_MS_ACTION_DROP) |
				 MSCC_MS_SAM_NM_FLOW_CP_UNTAGGED_DEST_PORT(port) |
				 /* MACsec tagged */
				 MSCC_MS_SAM_NM_FLOW_NCP_TAGGED_FLOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FLOW_CP_TAGGED_DROP_ACTION(MSCC_MS_ACTION_DROP) |
				 MSCC_MS_SAM_NM_FLOW_CP_TAGGED_DEST_PORT(port) |
				 /* Bad tag */
				 MSCC_MS_SAM_NM_FLOW_NCP_BADTAG_FLOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FLOW_CP_BADTAG_DROP_ACTION(MSCC_MS_ACTION_DROP) |
				 MSCC_MS_SAM_NM_FLOW_CP_BADTAG_DEST_PORT(port) |
				 /* Kay tag */
				 MSCC_MS_SAM_NM_FLOW_NCP_KAY_FLOW_TYPE(action) |
				 MSCC_MS_SAM_NM_FLOW_CP_KAY_DROP_ACTION(MSCC_MS_ACTION_DROP) |
				 MSCC_MS_SAM_NM_FLOW_CP_KAY_DEST_PORT(port));
पूर्ण

अटल व्योम vsc8584_macsec_पूर्णांकegrity_checks(काष्ठा phy_device *phydev,
					    क्रमागत macsec_bank bank)
अणु
	u32 val;

	अगर (bank != MACSEC_INGR)
		वापस;

	/* Set शेष rules to pass unmatched frames */
	val = vsc8584_macsec_phy_पढ़ो(phydev, bank,
				      MSCC_MS_PARAMS2_IG_CC_CONTROL);
	val |= MSCC_MS_PARAMS2_IG_CC_CONTROL_NON_MATCH_CTRL_ACT |
	       MSCC_MS_PARAMS2_IG_CC_CONTROL_NON_MATCH_ACT;
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_PARAMS2_IG_CC_CONTROL,
				 val);

	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_PARAMS2_IG_CP_TAG,
				 MSCC_MS_PARAMS2_IG_CP_TAG_PARSE_STAG |
				 MSCC_MS_PARAMS2_IG_CP_TAG_PARSE_QTAG |
				 MSCC_MS_PARAMS2_IG_CP_TAG_PARSE_QINQ);
पूर्ण

अटल व्योम vsc8584_macsec_block_init(काष्ठा phy_device *phydev,
				      क्रमागत macsec_bank bank)
अणु
	u32 val;
	पूर्णांक i;

	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_ENA_CFG,
				 MSCC_MS_ENA_CFG_SW_RST |
				 MSCC_MS_ENA_CFG_MACSEC_BYPASS_ENA);

	/* Set the MACsec block out of s/w reset and enable घड़ीs */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_ENA_CFG,
				 MSCC_MS_ENA_CFG_CLK_ENA);

	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_STATUS_CONTEXT_CTRL,
				 bank == MACSEC_INGR ? 0xe5880214 : 0xe5880218);
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_MISC_CONTROL,
				 MSCC_MS_MISC_CONTROL_MC_LATENCY_FIX(bank == MACSEC_INGR ? 57 : 40) |
				 MSCC_MS_MISC_CONTROL_XFORM_REC_SIZE(bank == MACSEC_INGR ? 1 : 2));

	/* Clear the counters */
	val = vsc8584_macsec_phy_पढ़ो(phydev, bank, MSCC_MS_COUNT_CONTROL);
	val |= MSCC_MS_COUNT_CONTROL_AUTO_CNTR_RESET;
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_COUNT_CONTROL, val);

	/* Enable octet increment mode */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_PP_CTRL,
				 MSCC_MS_PP_CTRL_MACSEC_OCTET_INCR_MODE);

	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_BLOCK_CTX_UPDATE, 0x3);

	val = vsc8584_macsec_phy_पढ़ो(phydev, bank, MSCC_MS_COUNT_CONTROL);
	val |= MSCC_MS_COUNT_CONTROL_RESET_ALL;
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_COUNT_CONTROL, val);

	/* Set the MTU */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_NON_VLAN_MTU_CHECK,
				 MSCC_MS_NON_VLAN_MTU_CHECK_NV_MTU_COMPARE(32761) |
				 MSCC_MS_NON_VLAN_MTU_CHECK_NV_MTU_COMP_DROP);

	क्रम (i = 0; i < 8; i++)
		vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_VLAN_MTU_CHECK(i),
					 MSCC_MS_VLAN_MTU_CHECK_MTU_COMPARE(32761) |
					 MSCC_MS_VLAN_MTU_CHECK_MTU_COMP_DROP);

	अगर (bank == MACSEC_EGR) अणु
		val = vsc8584_macsec_phy_पढ़ो(phydev, bank, MSCC_MS_INTR_CTRL_STATUS);
		val &= ~MSCC_MS_INTR_CTRL_STATUS_INTR_ENABLE_M;
		vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_INTR_CTRL_STATUS, val);

		vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_FC_CFG,
					 MSCC_MS_FC_CFG_FCBUF_ENA |
					 MSCC_MS_FC_CFG_LOW_THRESH(0x1) |
					 MSCC_MS_FC_CFG_HIGH_THRESH(0x4) |
					 MSCC_MS_FC_CFG_LOW_BYTES_VAL(0x4) |
					 MSCC_MS_FC_CFG_HIGH_BYTES_VAL(0x6));
	पूर्ण

	vsc8584_macsec_classअगरication(phydev, bank);
	vsc8584_macsec_flow_शेष_action(phydev, bank, false);
	vsc8584_macsec_पूर्णांकegrity_checks(phydev, bank);

	/* Enable the MACsec block */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_ENA_CFG,
				 MSCC_MS_ENA_CFG_CLK_ENA |
				 MSCC_MS_ENA_CFG_MACSEC_ENA |
				 MSCC_MS_ENA_CFG_MACSEC_SPEED_MODE(0x5));
पूर्ण

अटल व्योम vsc8584_macsec_mac_init(काष्ठा phy_device *phydev,
				    क्रमागत macsec_bank bank)
अणु
	u32 val;
	पूर्णांक i;

	/* Clear host & line stats */
	क्रम (i = 0; i < 36; i++)
		vsc8584_macsec_phy_ग_लिखो(phydev, bank, 0x1c + i, 0);

	val = vsc8584_macsec_phy_पढ़ो(phydev, bank,
				      MSCC_MAC_PAUSE_CFG_TX_FRAME_CTRL);
	val &= ~MSCC_MAC_PAUSE_CFG_TX_FRAME_CTRL_PAUSE_MODE_M;
	val |= MSCC_MAC_PAUSE_CFG_TX_FRAME_CTRL_PAUSE_MODE(2) |
	       MSCC_MAC_PAUSE_CFG_TX_FRAME_CTRL_PAUSE_VALUE(0xffff);
	vsc8584_macsec_phy_ग_लिखो(phydev, bank,
				 MSCC_MAC_PAUSE_CFG_TX_FRAME_CTRL, val);

	val = vsc8584_macsec_phy_पढ़ो(phydev, bank,
				      MSCC_MAC_PAUSE_CFG_TX_FRAME_CTRL_2);
	val |= 0xffff;
	vsc8584_macsec_phy_ग_लिखो(phydev, bank,
				 MSCC_MAC_PAUSE_CFG_TX_FRAME_CTRL_2, val);

	val = vsc8584_macsec_phy_पढ़ो(phydev, bank,
				      MSCC_MAC_PAUSE_CFG_RX_FRAME_CTRL);
	अगर (bank == HOST_MAC)
		val |= MSCC_MAC_PAUSE_CFG_RX_FRAME_CTRL_PAUSE_TIMER_ENA |
		       MSCC_MAC_PAUSE_CFG_RX_FRAME_CTRL_PAUSE_FRAME_DROP_ENA;
	अन्यथा
		val |= MSCC_MAC_PAUSE_CFG_RX_FRAME_CTRL_PAUSE_REACT_ENA |
		       MSCC_MAC_PAUSE_CFG_RX_FRAME_CTRL_PAUSE_FRAME_DROP_ENA |
		       MSCC_MAC_PAUSE_CFG_RX_FRAME_CTRL_PAUSE_MODE |
		       MSCC_MAC_PAUSE_CFG_RX_FRAME_CTRL_EARLY_PAUSE_DETECT_ENA;
	vsc8584_macsec_phy_ग_लिखो(phydev, bank,
				 MSCC_MAC_PAUSE_CFG_RX_FRAME_CTRL, val);

	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MAC_CFG_PKTINF_CFG,
				 MSCC_MAC_CFG_PKTINF_CFG_STRIP_FCS_ENA |
				 MSCC_MAC_CFG_PKTINF_CFG_INSERT_FCS_ENA |
				 MSCC_MAC_CFG_PKTINF_CFG_LPI_RELAY_ENA |
				 MSCC_MAC_CFG_PKTINF_CFG_STRIP_PREAMBLE_ENA |
				 MSCC_MAC_CFG_PKTINF_CFG_INSERT_PREAMBLE_ENA |
				 (bank == HOST_MAC ?
				  MSCC_MAC_CFG_PKTINF_CFG_ENABLE_TX_PADDING : 0) |
				 (IS_ENABLED(CONFIG_NETWORK_PHY_TIMESTAMPING) ?
				  MSCC_MAC_CFG_PKTINF_CFG_MACSEC_BYPASS_NUM_PTP_STALL_CLKS(0x8) : 0));

	val = vsc8584_macsec_phy_पढ़ो(phydev, bank, MSCC_MAC_CFG_MODE_CFG);
	val &= ~MSCC_MAC_CFG_MODE_CFG_DISABLE_DIC;
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MAC_CFG_MODE_CFG, val);

	val = vsc8584_macsec_phy_पढ़ो(phydev, bank, MSCC_MAC_CFG_MAXLEN_CFG);
	val &= ~MSCC_MAC_CFG_MAXLEN_CFG_MAX_LEN_M;
	val |= MSCC_MAC_CFG_MAXLEN_CFG_MAX_LEN(10240);
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MAC_CFG_MAXLEN_CFG, val);

	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MAC_CFG_ADV_CHK_CFG,
				 MSCC_MAC_CFG_ADV_CHK_CFG_SFD_CHK_ENA |
				 MSCC_MAC_CFG_ADV_CHK_CFG_PRM_CHK_ENA |
				 MSCC_MAC_CFG_ADV_CHK_CFG_OOR_ERR_ENA |
				 MSCC_MAC_CFG_ADV_CHK_CFG_INR_ERR_ENA);

	val = vsc8584_macsec_phy_पढ़ो(phydev, bank, MSCC_MAC_CFG_LFS_CFG);
	val &= ~MSCC_MAC_CFG_LFS_CFG_LFS_MODE_ENA;
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MAC_CFG_LFS_CFG, val);

	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MAC_CFG_ENA_CFG,
				 MSCC_MAC_CFG_ENA_CFG_RX_CLK_ENA |
				 MSCC_MAC_CFG_ENA_CFG_TX_CLK_ENA |
				 MSCC_MAC_CFG_ENA_CFG_RX_ENA |
				 MSCC_MAC_CFG_ENA_CFG_TX_ENA);
पूर्ण

/* Must be called with mdio_lock taken */
अटल पूर्णांक __vsc8584_macsec_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	क्रमागत macsec_bank proc_bank;
	u32 val;

	vsc8584_macsec_block_init(phydev, MACSEC_INGR);
	vsc8584_macsec_block_init(phydev, MACSEC_EGR);
	vsc8584_macsec_mac_init(phydev, HOST_MAC);
	vsc8584_macsec_mac_init(phydev, LINE_MAC);

	vsc8584_macsec_phy_ग_लिखो(phydev, FC_BUFFER,
				 MSCC_FCBUF_FC_READ_THRESH_CFG,
				 MSCC_FCBUF_FC_READ_THRESH_CFG_TX_THRESH(4) |
				 MSCC_FCBUF_FC_READ_THRESH_CFG_RX_THRESH(5));

	val = vsc8584_macsec_phy_पढ़ो(phydev, FC_BUFFER, MSCC_FCBUF_MODE_CFG);
	val |= MSCC_FCBUF_MODE_CFG_PAUSE_GEN_ENA |
	       MSCC_FCBUF_MODE_CFG_RX_PPM_RATE_ADAPT_ENA |
	       MSCC_FCBUF_MODE_CFG_TX_PPM_RATE_ADAPT_ENA;
	vsc8584_macsec_phy_ग_लिखो(phydev, FC_BUFFER, MSCC_FCBUF_MODE_CFG, val);

	vsc8584_macsec_phy_ग_लिखो(phydev, FC_BUFFER, MSCC_FCBUF_PPM_RATE_ADAPT_THRESH_CFG,
				 MSCC_FCBUF_PPM_RATE_ADAPT_THRESH_CFG_TX_THRESH(8) |
				 MSCC_FCBUF_PPM_RATE_ADAPT_THRESH_CFG_TX_OFFSET(9));

	val = vsc8584_macsec_phy_पढ़ो(phydev, FC_BUFFER,
				      MSCC_FCBUF_TX_DATA_QUEUE_CFG);
	val &= ~(MSCC_FCBUF_TX_DATA_QUEUE_CFG_START_M |
		 MSCC_FCBUF_TX_DATA_QUEUE_CFG_END_M);
	val |= MSCC_FCBUF_TX_DATA_QUEUE_CFG_START(0) |
		MSCC_FCBUF_TX_DATA_QUEUE_CFG_END(5119);
	vsc8584_macsec_phy_ग_लिखो(phydev, FC_BUFFER,
				 MSCC_FCBUF_TX_DATA_QUEUE_CFG, val);

	val = vsc8584_macsec_phy_पढ़ो(phydev, FC_BUFFER, MSCC_FCBUF_ENA_CFG);
	val |= MSCC_FCBUF_ENA_CFG_TX_ENA | MSCC_FCBUF_ENA_CFG_RX_ENA;
	vsc8584_macsec_phy_ग_लिखो(phydev, FC_BUFFER, MSCC_FCBUF_ENA_CFG, val);

	proc_bank = (priv->addr < 2) ? PROC_0 : PROC_2;

	val = vsc8584_macsec_phy_पढ़ो(phydev, proc_bank,
				      MSCC_PROC_IP_1588_TOP_CFG_STAT_MODE_CTL);
	val &= ~MSCC_PROC_IP_1588_TOP_CFG_STAT_MODE_CTL_PROTOCOL_MODE_M;
	val |= MSCC_PROC_IP_1588_TOP_CFG_STAT_MODE_CTL_PROTOCOL_MODE(4);
	vsc8584_macsec_phy_ग_लिखो(phydev, proc_bank,
				 MSCC_PROC_IP_1588_TOP_CFG_STAT_MODE_CTL, val);

	वापस 0;
पूर्ण

अटल व्योम vsc8584_macsec_flow(काष्ठा phy_device *phydev,
				काष्ठा macsec_flow *flow)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	क्रमागत macsec_bank bank = flow->bank;
	u32 val, match = 0, mask = 0, action = 0, idx = flow->index;

	अगर (flow->match.tagged)
		match |= MSCC_MS_SAM_MISC_MATCH_TAGGED;
	अगर (flow->match.untagged)
		match |= MSCC_MS_SAM_MISC_MATCH_UNTAGGED;

	अगर (bank == MACSEC_INGR && flow->assoc_num >= 0) अणु
		match |= MSCC_MS_SAM_MISC_MATCH_AN(flow->assoc_num);
		mask |= MSCC_MS_SAM_MASK_AN_MASK(0x3);
	पूर्ण

	अगर (bank == MACSEC_INGR && flow->match.sci && flow->rx_sa->sc->sci) अणु
		u64 sci = (__क्रमce u64)flow->rx_sa->sc->sci;

		match |= MSCC_MS_SAM_MISC_MATCH_TCI(BIT(3));
		mask |= MSCC_MS_SAM_MASK_TCI_MASK(BIT(3)) |
			MSCC_MS_SAM_MASK_SCI_MASK;

		vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_MATCH_SCI_LO(idx),
					 lower_32_bits(sci));
		vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_MATCH_SCI_HI(idx),
					 upper_32_bits(sci));
	पूर्ण

	अगर (flow->match.etype) अणु
		mask |= MSCC_MS_SAM_MASK_MAC_ETYPE_MASK;

		vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_MAC_SA_MATCH_HI(idx),
					 MSCC_MS_SAM_MAC_SA_MATCH_HI_ETYPE((__क्रमce u32)htons(flow->etype)));
	पूर्ण

	match |= MSCC_MS_SAM_MISC_MATCH_PRIORITY(flow->priority);

	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_MISC_MATCH(idx), match);
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_MASK(idx), mask);

	/* Action क्रम matching packets */
	अगर (flow->action.drop)
		action = MSCC_MS_FLOW_DROP;
	अन्यथा अगर (flow->action.bypass || flow->port == MSCC_MS_PORT_UNCONTROLLED)
		action = MSCC_MS_FLOW_BYPASS;
	अन्यथा
		action = (bank == MACSEC_INGR) ?
			 MSCC_MS_FLOW_INGRESS : MSCC_MS_FLOW_EGRESS;

	val = MSCC_MS_SAM_FLOW_CTRL_FLOW_TYPE(action) |
	      MSCC_MS_SAM_FLOW_CTRL_DROP_ACTION(MSCC_MS_ACTION_DROP) |
	      MSCC_MS_SAM_FLOW_CTRL_DEST_PORT(flow->port);

	अगर (action == MSCC_MS_FLOW_BYPASS)
		जाओ ग_लिखो_ctrl;

	अगर (bank == MACSEC_INGR) अणु
		अगर (priv->secy->replay_protect)
			val |= MSCC_MS_SAM_FLOW_CTRL_REPLAY_PROTECT;
		अगर (priv->secy->validate_frames == MACSEC_VALIDATE_STRICT)
			val |= MSCC_MS_SAM_FLOW_CTRL_VALIDATE_FRAMES(MSCC_MS_VALIDATE_STRICT);
		अन्यथा अगर (priv->secy->validate_frames == MACSEC_VALIDATE_CHECK)
			val |= MSCC_MS_SAM_FLOW_CTRL_VALIDATE_FRAMES(MSCC_MS_VALIDATE_CHECK);
	पूर्ण अन्यथा अगर (bank == MACSEC_EGR) अणु
		अगर (priv->secy->protect_frames)
			val |= MSCC_MS_SAM_FLOW_CTRL_PROTECT_FRAME;
		अगर (priv->secy->tx_sc.encrypt)
			val |= MSCC_MS_SAM_FLOW_CTRL_CONF_PROTECT;
		अगर (priv->secy->tx_sc.send_sci)
			val |= MSCC_MS_SAM_FLOW_CTRL_INCLUDE_SCI;
	पूर्ण

ग_लिखो_ctrl:
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_FLOW_CTRL(idx), val);
पूर्ण

अटल काष्ठा macsec_flow *vsc8584_macsec_find_flow(काष्ठा macsec_context *ctx,
						    क्रमागत macsec_bank bank)
अणु
	काष्ठा vsc8531_निजी *priv = ctx->phydev->priv;
	काष्ठा macsec_flow *pos, *पंचांगp;

	list_क्रम_each_entry_safe(pos, पंचांगp, &priv->macsec_flows, list)
		अगर (pos->assoc_num == ctx->sa.assoc_num && pos->bank == bank)
			वापस pos;

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल व्योम vsc8584_macsec_flow_enable(काष्ठा phy_device *phydev,
				       काष्ठा macsec_flow *flow)
अणु
	क्रमागत macsec_bank bank = flow->bank;
	u32 val, idx = flow->index;

	अगर ((flow->bank == MACSEC_INGR && flow->rx_sa && !flow->rx_sa->active) ||
	    (flow->bank == MACSEC_EGR && flow->tx_sa && !flow->tx_sa->active))
		वापस;

	/* Enable */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_ENTRY_SET1, BIT(idx));

	/* Set in-use */
	val = vsc8584_macsec_phy_पढ़ो(phydev, bank, MSCC_MS_SAM_FLOW_CTRL(idx));
	val |= MSCC_MS_SAM_FLOW_CTRL_SA_IN_USE;
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_FLOW_CTRL(idx), val);
पूर्ण

अटल व्योम vsc8584_macsec_flow_disable(काष्ठा phy_device *phydev,
					काष्ठा macsec_flow *flow)
अणु
	क्रमागत macsec_bank bank = flow->bank;
	u32 val, idx = flow->index;

	/* Disable */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_ENTRY_CLEAR1, BIT(idx));

	/* Clear in-use */
	val = vsc8584_macsec_phy_पढ़ो(phydev, bank, MSCC_MS_SAM_FLOW_CTRL(idx));
	val &= ~MSCC_MS_SAM_FLOW_CTRL_SA_IN_USE;
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_SAM_FLOW_CTRL(idx), val);
पूर्ण

अटल u32 vsc8584_macsec_flow_context_id(काष्ठा macsec_flow *flow)
अणु
	अगर (flow->bank == MACSEC_INGR)
		वापस flow->index + MSCC_MS_MAX_FLOWS;

	वापस flow->index;
पूर्ण

/* Derive the AES key to get a key क्रम the hash autentication */
अटल पूर्णांक vsc8584_macsec_derive_key(स्थिर u8 key[MACSEC_KEYID_LEN],
				     u16 key_len, u8 hkey[16])
अणु
	स्थिर u8 input[AES_BLOCK_SIZE] = अणु0पूर्ण;
	काष्ठा crypto_aes_ctx ctx;
	पूर्णांक ret;

	ret = aes_expandkey(&ctx, key, key_len);
	अगर (ret)
		वापस ret;

	aes_encrypt(&ctx, hkey, input);
	memzero_explicit(&ctx, माप(ctx));
	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_transक्रमmation(काष्ठा phy_device *phydev,
					 काष्ठा macsec_flow *flow)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	क्रमागत macsec_bank bank = flow->bank;
	पूर्णांक i, ret, index = flow->index;
	u32 rec = 0, control = 0;
	u8 hkey[16];
	u64 sci;

	ret = vsc8584_macsec_derive_key(flow->key, priv->secy->key_len, hkey);
	अगर (ret)
		वापस ret;

	चयन (priv->secy->key_len) अणु
	हाल 16:
		control |= CONTROL_CRYPTO_ALG(CTRYPTO_ALG_AES_CTR_128);
		अवरोध;
	हाल 32:
		control |= CONTROL_CRYPTO_ALG(CTRYPTO_ALG_AES_CTR_256);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	control |= (bank == MACSEC_EGR) ?
		   (CONTROL_TYPE_EGRESS | CONTROL_AN(priv->secy->tx_sc.encoding_sa)) :
		   (CONTROL_TYPE_INGRESS | CONTROL_SEQ_MASK);

	control |= CONTROL_UPDATE_SEQ | CONTROL_ENCRYPT_AUTH | CONTROL_KEY_IN_CTX |
		   CONTROL_IV0 | CONTROL_IV1 | CONTROL_IV_IN_SEQ |
		   CONTROL_DIGEST_TYPE(0x2) | CONTROL_SEQ_TYPE(0x1) |
		   CONTROL_AUTH_ALG(AUTH_ALG_AES_GHAS) | CONTROL_CONTEXT_ID;

	/* Set the control word */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_XFORM_REC(index, rec++),
				 control);

	/* Set the context ID. Must be unique. */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_XFORM_REC(index, rec++),
				 vsc8584_macsec_flow_context_id(flow));

	/* Set the encryption/decryption key */
	क्रम (i = 0; i < priv->secy->key_len / माप(u32); i++)
		vsc8584_macsec_phy_ग_लिखो(phydev, bank,
					 MSCC_MS_XFORM_REC(index, rec++),
					 ((u32 *)flow->key)[i]);

	/* Set the authentication key */
	क्रम (i = 0; i < 4; i++)
		vsc8584_macsec_phy_ग_लिखो(phydev, bank,
					 MSCC_MS_XFORM_REC(index, rec++),
					 ((u32 *)hkey)[i]);

	/* Initial sequence number */
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_XFORM_REC(index, rec++),
				 bank == MACSEC_INGR ?
				 flow->rx_sa->next_pn : flow->tx_sa->next_pn);

	अगर (bank == MACSEC_INGR)
		/* Set the mask (replay winकरोw size) */
		vsc8584_macsec_phy_ग_लिखो(phydev, bank,
					 MSCC_MS_XFORM_REC(index, rec++),
					 priv->secy->replay_winकरोw);

	/* Set the input vectors */
	sci = (__क्रमce u64)(bank == MACSEC_INGR ? flow->rx_sa->sc->sci : priv->secy->sci);
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_XFORM_REC(index, rec++),
				 lower_32_bits(sci));
	vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_XFORM_REC(index, rec++),
				 upper_32_bits(sci));

	जबतक (rec < 20)
		vsc8584_macsec_phy_ग_लिखो(phydev, bank, MSCC_MS_XFORM_REC(index, rec++),
					 0);

	flow->has_transक्रमmation = true;
	वापस 0;
पूर्ण

अटल काष्ठा macsec_flow *vsc8584_macsec_alloc_flow(काष्ठा vsc8531_निजी *priv,
						     क्रमागत macsec_bank bank)
अणु
	अचिन्हित दीर्घ *biपंचांगap = bank == MACSEC_INGR ?
				&priv->ingr_flows : &priv->egr_flows;
	काष्ठा macsec_flow *flow;
	पूर्णांक index;

	index = find_first_zero_bit(biपंचांगap, MSCC_MS_MAX_FLOWS);

	अगर (index == MSCC_MS_MAX_FLOWS)
		वापस ERR_PTR(-ENOMEM);

	flow = kzalloc(माप(*flow), GFP_KERNEL);
	अगर (!flow)
		वापस ERR_PTR(-ENOMEM);

	set_bit(index, biपंचांगap);
	flow->index = index;
	flow->bank = bank;
	flow->priority = 8;
	flow->assoc_num = -1;

	list_add_tail(&flow->list, &priv->macsec_flows);
	वापस flow;
पूर्ण

अटल व्योम vsc8584_macsec_मुक्त_flow(काष्ठा vsc8531_निजी *priv,
				     काष्ठा macsec_flow *flow)
अणु
	अचिन्हित दीर्घ *biपंचांगap = flow->bank == MACSEC_INGR ?
				&priv->ingr_flows : &priv->egr_flows;

	list_del(&flow->list);
	clear_bit(flow->index, biपंचांगap);
	kमुक्त(flow);
पूर्ण

अटल पूर्णांक vsc8584_macsec_add_flow(काष्ठा phy_device *phydev,
				   काष्ठा macsec_flow *flow, bool update)
अणु
	पूर्णांक ret;

	flow->port = MSCC_MS_PORT_CONTROLLED;
	vsc8584_macsec_flow(phydev, flow);

	अगर (update)
		वापस 0;

	ret = vsc8584_macsec_transक्रमmation(phydev, flow);
	अगर (ret) अणु
		vsc8584_macsec_मुक्त_flow(phydev->priv, flow);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_शेष_flows(काष्ठा phy_device *phydev)
अणु
	काष्ठा macsec_flow *flow;

	/* Add a rule to let the MKA traffic go through, ingress */
	flow = vsc8584_macsec_alloc_flow(phydev->priv, MACSEC_INGR);
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	flow->priority = 15;
	flow->port = MSCC_MS_PORT_UNCONTROLLED;
	flow->match.tagged = 1;
	flow->match.untagged = 1;
	flow->match.etype = 1;
	flow->etype = ETH_P_PAE;
	flow->action.bypass = 1;

	vsc8584_macsec_flow(phydev, flow);
	vsc8584_macsec_flow_enable(phydev, flow);

	/* Add a rule to let the MKA traffic go through, egress */
	flow = vsc8584_macsec_alloc_flow(phydev->priv, MACSEC_EGR);
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	flow->priority = 15;
	flow->port = MSCC_MS_PORT_COMMON;
	flow->match.untagged = 1;
	flow->match.etype = 1;
	flow->etype = ETH_P_PAE;
	flow->action.bypass = 1;

	vsc8584_macsec_flow(phydev, flow);
	vsc8584_macsec_flow_enable(phydev, flow);

	वापस 0;
पूर्ण

अटल व्योम vsc8584_macsec_del_flow(काष्ठा phy_device *phydev,
				    काष्ठा macsec_flow *flow)
अणु
	vsc8584_macsec_flow_disable(phydev, flow);
	vsc8584_macsec_मुक्त_flow(phydev->priv, flow);
पूर्ण

अटल पूर्णांक __vsc8584_macsec_add_rxsa(काष्ठा macsec_context *ctx,
				     काष्ठा macsec_flow *flow, bool update)
अणु
	काष्ठा phy_device *phydev = ctx->phydev;
	काष्ठा vsc8531_निजी *priv = phydev->priv;

	अगर (!flow) अणु
		flow = vsc8584_macsec_alloc_flow(priv, MACSEC_INGR);
		अगर (IS_ERR(flow))
			वापस PTR_ERR(flow);

		स_नकल(flow->key, ctx->sa.key, priv->secy->key_len);
	पूर्ण

	flow->assoc_num = ctx->sa.assoc_num;
	flow->rx_sa = ctx->sa.rx_sa;

	/* Always match tagged packets on ingress */
	flow->match.tagged = 1;
	flow->match.sci = 1;

	अगर (priv->secy->validate_frames != MACSEC_VALIDATE_DISABLED)
		flow->match.untagged = 1;

	वापस vsc8584_macsec_add_flow(phydev, flow, update);
पूर्ण

अटल पूर्णांक __vsc8584_macsec_add_txsa(काष्ठा macsec_context *ctx,
				     काष्ठा macsec_flow *flow, bool update)
अणु
	काष्ठा phy_device *phydev = ctx->phydev;
	काष्ठा vsc8531_निजी *priv = phydev->priv;

	अगर (!flow) अणु
		flow = vsc8584_macsec_alloc_flow(priv, MACSEC_EGR);
		अगर (IS_ERR(flow))
			वापस PTR_ERR(flow);

		स_नकल(flow->key, ctx->sa.key, priv->secy->key_len);
	पूर्ण

	flow->assoc_num = ctx->sa.assoc_num;
	flow->tx_sa = ctx->sa.tx_sa;

	/* Always match untagged packets on egress */
	flow->match.untagged = 1;

	वापस vsc8584_macsec_add_flow(phydev, flow, update);
पूर्ण

अटल पूर्णांक vsc8584_macsec_dev_खोलो(काष्ठा macsec_context *ctx)
अणु
	काष्ठा vsc8531_निजी *priv = ctx->phydev->priv;
	काष्ठा macsec_flow *flow, *पंचांगp;

	/* No operation to perक्रमm beक्रमe the commit step */
	अगर (ctx->prepare)
		वापस 0;

	list_क्रम_each_entry_safe(flow, पंचांगp, &priv->macsec_flows, list)
		vsc8584_macsec_flow_enable(ctx->phydev, flow);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_dev_stop(काष्ठा macsec_context *ctx)
अणु
	काष्ठा vsc8531_निजी *priv = ctx->phydev->priv;
	काष्ठा macsec_flow *flow, *पंचांगp;

	/* No operation to perक्रमm beक्रमe the commit step */
	अगर (ctx->prepare)
		वापस 0;

	list_क्रम_each_entry_safe(flow, पंचांगp, &priv->macsec_flows, list)
		vsc8584_macsec_flow_disable(ctx->phydev, flow);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_add_secy(काष्ठा macsec_context *ctx)
अणु
	काष्ठा vsc8531_निजी *priv = ctx->phydev->priv;
	काष्ठा macsec_secy *secy = ctx->secy;

	अगर (ctx->prepare) अणु
		अगर (priv->secy)
			वापस -EEXIST;

		वापस 0;
	पूर्ण

	priv->secy = secy;

	vsc8584_macsec_flow_शेष_action(ctx->phydev, MACSEC_EGR,
					   secy->validate_frames != MACSEC_VALIDATE_DISABLED);
	vsc8584_macsec_flow_शेष_action(ctx->phydev, MACSEC_INGR,
					   secy->validate_frames != MACSEC_VALIDATE_DISABLED);

	वापस vsc8584_macsec_शेष_flows(ctx->phydev);
पूर्ण

अटल पूर्णांक vsc8584_macsec_del_secy(काष्ठा macsec_context *ctx)
अणु
	काष्ठा vsc8531_निजी *priv = ctx->phydev->priv;
	काष्ठा macsec_flow *flow, *पंचांगp;

	/* No operation to perक्रमm beक्रमe the commit step */
	अगर (ctx->prepare)
		वापस 0;

	list_क्रम_each_entry_safe(flow, पंचांगp, &priv->macsec_flows, list)
		vsc8584_macsec_del_flow(ctx->phydev, flow);

	vsc8584_macsec_flow_शेष_action(ctx->phydev, MACSEC_EGR, false);
	vsc8584_macsec_flow_शेष_action(ctx->phydev, MACSEC_INGR, false);

	priv->secy = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_upd_secy(काष्ठा macsec_context *ctx)
अणु
	/* No operation to perक्रमm beक्रमe the commit step */
	अगर (ctx->prepare)
		वापस 0;

	vsc8584_macsec_del_secy(ctx);
	वापस vsc8584_macsec_add_secy(ctx);
पूर्ण

अटल पूर्णांक vsc8584_macsec_add_rxsc(काष्ठा macsec_context *ctx)
अणु
	/* Nothing to करो */
	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_upd_rxsc(काष्ठा macsec_context *ctx)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक vsc8584_macsec_del_rxsc(काष्ठा macsec_context *ctx)
अणु
	काष्ठा vsc8531_निजी *priv = ctx->phydev->priv;
	काष्ठा macsec_flow *flow, *पंचांगp;

	/* No operation to perक्रमm beक्रमe the commit step */
	अगर (ctx->prepare)
		वापस 0;

	list_क्रम_each_entry_safe(flow, पंचांगp, &priv->macsec_flows, list) अणु
		अगर (flow->bank == MACSEC_INGR && flow->rx_sa &&
		    flow->rx_sa->sc->sci == ctx->rx_sc->sci)
			vsc8584_macsec_del_flow(ctx->phydev, flow);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_add_rxsa(काष्ठा macsec_context *ctx)
अणु
	काष्ठा macsec_flow *flow = शून्य;

	अगर (ctx->prepare)
		वापस __vsc8584_macsec_add_rxsa(ctx, flow, false);

	flow = vsc8584_macsec_find_flow(ctx, MACSEC_INGR);
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	vsc8584_macsec_flow_enable(ctx->phydev, flow);
	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_upd_rxsa(काष्ठा macsec_context *ctx)
अणु
	काष्ठा macsec_flow *flow;

	flow = vsc8584_macsec_find_flow(ctx, MACSEC_INGR);
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	अगर (ctx->prepare) अणु
		/* Make sure the flow is disabled beक्रमe updating it */
		vsc8584_macsec_flow_disable(ctx->phydev, flow);

		वापस __vsc8584_macsec_add_rxsa(ctx, flow, true);
	पूर्ण

	vsc8584_macsec_flow_enable(ctx->phydev, flow);
	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_del_rxsa(काष्ठा macsec_context *ctx)
अणु
	काष्ठा macsec_flow *flow;

	flow = vsc8584_macsec_find_flow(ctx, MACSEC_INGR);

	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);
	अगर (ctx->prepare)
		वापस 0;

	vsc8584_macsec_del_flow(ctx->phydev, flow);
	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_add_txsa(काष्ठा macsec_context *ctx)
अणु
	काष्ठा macsec_flow *flow = शून्य;

	अगर (ctx->prepare)
		वापस __vsc8584_macsec_add_txsa(ctx, flow, false);

	flow = vsc8584_macsec_find_flow(ctx, MACSEC_EGR);
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	vsc8584_macsec_flow_enable(ctx->phydev, flow);
	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_upd_txsa(काष्ठा macsec_context *ctx)
अणु
	काष्ठा macsec_flow *flow;

	flow = vsc8584_macsec_find_flow(ctx, MACSEC_EGR);
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	अगर (ctx->prepare) अणु
		/* Make sure the flow is disabled beक्रमe updating it */
		vsc8584_macsec_flow_disable(ctx->phydev, flow);

		वापस __vsc8584_macsec_add_txsa(ctx, flow, true);
	पूर्ण

	vsc8584_macsec_flow_enable(ctx->phydev, flow);
	वापस 0;
पूर्ण

अटल पूर्णांक vsc8584_macsec_del_txsa(काष्ठा macsec_context *ctx)
अणु
	काष्ठा macsec_flow *flow;

	flow = vsc8584_macsec_find_flow(ctx, MACSEC_EGR);

	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);
	अगर (ctx->prepare)
		वापस 0;

	vsc8584_macsec_del_flow(ctx->phydev, flow);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा macsec_ops vsc8584_macsec_ops = अणु
	.mकरो_dev_खोलो = vsc8584_macsec_dev_खोलो,
	.mकरो_dev_stop = vsc8584_macsec_dev_stop,
	.mकरो_add_secy = vsc8584_macsec_add_secy,
	.mकरो_upd_secy = vsc8584_macsec_upd_secy,
	.mकरो_del_secy = vsc8584_macsec_del_secy,
	.mकरो_add_rxsc = vsc8584_macsec_add_rxsc,
	.mकरो_upd_rxsc = vsc8584_macsec_upd_rxsc,
	.mकरो_del_rxsc = vsc8584_macsec_del_rxsc,
	.mकरो_add_rxsa = vsc8584_macsec_add_rxsa,
	.mकरो_upd_rxsa = vsc8584_macsec_upd_rxsa,
	.mकरो_del_rxsa = vsc8584_macsec_del_rxsa,
	.mकरो_add_txsa = vsc8584_macsec_add_txsa,
	.mकरो_upd_txsa = vsc8584_macsec_upd_txsa,
	.mकरो_del_txsa = vsc8584_macsec_del_txsa,
पूर्ण;

पूर्णांक vsc8584_macsec_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;

	चयन (phydev->phy_id & phydev->drv->phy_id_mask) अणु
	हाल PHY_ID_VSC856X:
	हाल PHY_ID_VSC8582:
	हाल PHY_ID_VSC8584:
		INIT_LIST_HEAD(&vsc8531->macsec_flows);
		vsc8531->secy = शून्य;

		phydev->macsec_ops = &vsc8584_macsec_ops;

		वापस __vsc8584_macsec_init(phydev);
	पूर्ण

	वापस 0;
पूर्ण

व्योम vsc8584_handle_macsec_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	काष्ठा macsec_flow *flow, *पंचांगp;
	u32 cause, rec;

	/* Check MACsec PN rollover */
	cause = vsc8584_macsec_phy_पढ़ो(phydev, MACSEC_EGR,
					MSCC_MS_INTR_CTRL_STATUS);
	cause &= MSCC_MS_INTR_CTRL_STATUS_INTR_CLR_STATUS_M;
	अगर (!(cause & MACSEC_INTR_CTRL_STATUS_ROLLOVER))
		वापस;

	rec = 6 + priv->secy->key_len / माप(u32);
	list_क्रम_each_entry_safe(flow, पंचांगp, &priv->macsec_flows, list) अणु
		u32 val;

		अगर (flow->bank != MACSEC_EGR || !flow->has_transक्रमmation)
			जारी;

		val = vsc8584_macsec_phy_पढ़ो(phydev, MACSEC_EGR,
					      MSCC_MS_XFORM_REC(flow->index, rec));
		अगर (val == 0xffffffff) अणु
			vsc8584_macsec_flow_disable(phydev, flow);
			macsec_pn_wrapped(priv->secy, flow->tx_sa);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

व्योम vsc8584_config_macsec_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_2);
	phy_ग_लिखो(phydev, MSCC_PHY_EXTENDED_INT, MSCC_PHY_EXTENDED_INT_MS_EGR);
	phy_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	vsc8584_macsec_phy_ग_लिखो(phydev, MACSEC_EGR, MSCC_MS_AIC_CTRL, 0xf);
	vsc8584_macsec_phy_ग_लिखो(phydev, MACSEC_EGR, MSCC_MS_INTR_CTRL_STATUS,
				 MSCC_MS_INTR_CTRL_STATUS_INTR_ENABLE(MACSEC_INTR_CTRL_STATUS_ROLLOVER));
पूर्ण
