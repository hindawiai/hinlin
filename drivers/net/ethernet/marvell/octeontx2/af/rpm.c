<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Marvell OcteonTx2 RPM driver
 *
 * Copyright (C) 2020 Marvell.
 *
 */

#समावेश "cgx.h"
#समावेश "lmac_common.h"

अटल काष्ठा mac_ops	rpm_mac_ops   = अणु
	.name		=       "rpm",
	.csr_offset     =       0x4e00,
	.lmac_offset    =       20,
	.पूर्णांक_रेजिस्टर	=       RPMX_CMRX_SW_INT,
	.पूर्णांक_set_reg    =       RPMX_CMRX_SW_INT_ENA_W1S,
	.irq_offset     =       1,
	.पूर्णांक_ena_bit    =       BIT_ULL(0),
	.lmac_fwi	=	RPM_LMAC_FWI,
	.non_contiguous_serdes_lane = true,
	.rx_stats_cnt   =       43,
	.tx_stats_cnt   =       34,
	.get_nr_lmacs	=	rpm_get_nr_lmacs,
	.get_lmac_type  =       rpm_get_lmac_type,
	.mac_lmac_पूर्णांकl_lbk =    rpm_lmac_पूर्णांकernal_loopback,
	.mac_get_rx_stats  =	rpm_get_rx_stats,
	.mac_get_tx_stats  =	rpm_get_tx_stats,
	.mac_enadis_rx_छोड़ो_fwding =	rpm_lmac_enadis_rx_छोड़ो_fwding,
	.mac_get_छोड़ो_frm_status =	rpm_lmac_get_छोड़ो_frm_status,
	.mac_enadis_छोड़ो_frm =		rpm_lmac_enadis_छोड़ो_frm,
	.mac_छोड़ो_frm_config =		rpm_lmac_छोड़ो_frm_config,
पूर्ण;

काष्ठा mac_ops *rpm_get_mac_ops(व्योम)
अणु
	वापस &rpm_mac_ops;
पूर्ण

अटल व्योम rpm_ग_लिखो(rpm_t *rpm, u64 lmac, u64 offset, u64 val)
अणु
	cgx_ग_लिखो(rpm, lmac, offset, val);
पूर्ण

अटल u64 rpm_पढ़ो(rpm_t *rpm, u64 lmac, u64 offset)
अणु
	वापस	cgx_पढ़ो(rpm, lmac, offset);
पूर्ण

पूर्णांक rpm_get_nr_lmacs(व्योम *rpmd)
अणु
	rpm_t *rpm = rpmd;

	वापस hweight8(rpm_पढ़ो(rpm, 0, CGXX_CMRX_RX_LMACS) & 0xFULL);
पूर्ण

व्योम rpm_lmac_enadis_rx_छोड़ो_fwding(व्योम *rpmd, पूर्णांक lmac_id, bool enable)
अणु
	rpm_t *rpm = rpmd;
	u64 cfg;

	अगर (!rpm)
		वापस;

	अगर (enable) अणु
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg &= ~RPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNORE;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);
	पूर्ण अन्यथा अणु
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg |= RPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNORE;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);
	पूर्ण
पूर्ण

पूर्णांक rpm_lmac_get_छोड़ो_frm_status(व्योम *rpmd, पूर्णांक lmac_id,
				  u8 *tx_छोड़ो, u8 *rx_छोड़ो)
अणु
	rpm_t *rpm = rpmd;
	u64 cfg;

	अगर (!is_lmac_valid(rpm, lmac_id))
		वापस -ENODEV;

	cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
	*rx_छोड़ो = !(cfg & RPMX_MTI_MAC100X_COMMAND_CONFIG_RX_P_DISABLE);

	cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
	*tx_छोड़ो = !(cfg & RPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABLE);
	वापस 0;
पूर्ण

पूर्णांक rpm_lmac_enadis_छोड़ो_frm(व्योम *rpmd, पूर्णांक lmac_id, u8 tx_छोड़ो,
			      u8 rx_छोड़ो)
अणु
	rpm_t *rpm = rpmd;
	u64 cfg;

	अगर (!is_lmac_valid(rpm, lmac_id))
		वापस -ENODEV;

	cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
	cfg &= ~RPMX_MTI_MAC100X_COMMAND_CONFIG_RX_P_DISABLE;
	cfg |= rx_छोड़ो ? 0x0 : RPMX_MTI_MAC100X_COMMAND_CONFIG_RX_P_DISABLE;
	cfg &= ~RPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNORE;
	cfg |= rx_छोड़ो ? 0x0 : RPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNORE;
	rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

	cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
	cfg &= ~RPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABLE;
	cfg |= tx_छोड़ो ? 0x0 : RPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABLE;
	rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

	cfg = rpm_पढ़ो(rpm, 0, RPMX_CMR_RX_OVR_BP);
	अगर (tx_छोड़ो) अणु
		cfg &= ~RPMX_CMR_RX_OVR_BP_EN(lmac_id);
	पूर्ण अन्यथा अणु
		cfg |= RPMX_CMR_RX_OVR_BP_EN(lmac_id);
		cfg &= ~RPMX_CMR_RX_OVR_BP_BP(lmac_id);
	पूर्ण
	rpm_ग_लिखो(rpm, 0, RPMX_CMR_RX_OVR_BP, cfg);
	वापस 0;
पूर्ण

व्योम rpm_lmac_छोड़ो_frm_config(व्योम *rpmd, पूर्णांक lmac_id, bool enable)
अणु
	rpm_t *rpm = rpmd;
	u64 cfg;

	अगर (enable) अणु
		/* Enable 802.3 छोड़ो frame mode */
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg &= ~RPMX_MTI_MAC100X_COMMAND_CONFIG_PFC_MODE;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

		/* Enable receive छोड़ो frames */
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg &= ~RPMX_MTI_MAC100X_COMMAND_CONFIG_RX_P_DISABLE;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

		/* Enable क्रमward छोड़ो to TX block */
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg &= ~RPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNORE;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

		/* Enable छोड़ो frames transmission */
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg &= ~RPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABLE;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

		/* Set छोड़ो समय and पूर्णांकerval */
		cfg = rpm_पढ़ो(rpm, lmac_id,
			       RPMX_MTI_MAC100X_CL01_PAUSE_QUANTA);
		cfg &= ~0xFFFFULL;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_CL01_PAUSE_QUANTA,
			  cfg | RPM_DEFAULT_PAUSE_TIME);
		/* Set छोड़ो पूर्णांकerval as the hardware शेष is too लघु */
		cfg = rpm_पढ़ो(rpm, lmac_id,
			       RPMX_MTI_MAC100X_CL01_QUANTA_THRESH);
		cfg &= ~0xFFFFULL;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_CL01_QUANTA_THRESH,
			  cfg | (RPM_DEFAULT_PAUSE_TIME / 2));

	पूर्ण अन्यथा अणु
		/* ALL छोड़ो frames received are completely ignored */
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg |= RPMX_MTI_MAC100X_COMMAND_CONFIG_RX_P_DISABLE;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

		/* Disable क्रमward छोड़ो to TX block */
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg |= RPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNORE;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

		/* Disable छोड़ो frames transmission */
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg |= RPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABLE;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);
	पूर्ण
पूर्ण

पूर्णांक rpm_get_rx_stats(व्योम *rpmd, पूर्णांक lmac_id, पूर्णांक idx, u64 *rx_stat)
अणु
	rpm_t *rpm = rpmd;
	u64 val_lo, val_hi;

	अगर (!rpm || lmac_id >= rpm->lmac_count)
		वापस -ENODEV;

	mutex_lock(&rpm->lock);

	/* Update idx to poपूर्णांक per lmac Rx statistics page */
	idx += lmac_id * rpm->mac_ops->rx_stats_cnt;

	/* Read lower 32 bits of counter */
	val_lo = rpm_पढ़ो(rpm, 0, RPMX_MTI_STAT_RX_STAT_PAGES_COUNTERX +
			  (idx * 8));

	/* upon पढ़ो of lower 32 bits, higher 32 bits are written
	 * to RPMX_MTI_STAT_DATA_HI_CDC
	 */
	val_hi = rpm_पढ़ो(rpm, 0, RPMX_MTI_STAT_DATA_HI_CDC);

	*rx_stat = (val_hi << 32 | val_lo);

	mutex_unlock(&rpm->lock);
	वापस 0;
पूर्ण

पूर्णांक rpm_get_tx_stats(व्योम *rpmd, पूर्णांक lmac_id, पूर्णांक idx, u64 *tx_stat)
अणु
	rpm_t *rpm = rpmd;
	u64 val_lo, val_hi;

	अगर (!rpm || lmac_id >= rpm->lmac_count)
		वापस -ENODEV;

	mutex_lock(&rpm->lock);

	/* Update idx to poपूर्णांक per lmac Tx statistics page */
	idx += lmac_id * rpm->mac_ops->tx_stats_cnt;

	val_lo = rpm_पढ़ो(rpm, 0, RPMX_MTI_STAT_TX_STAT_PAGES_COUNTERX +
			    (idx * 8));
	val_hi = rpm_पढ़ो(rpm, 0, RPMX_MTI_STAT_DATA_HI_CDC);

	*tx_stat = (val_hi << 32 | val_lo);

	mutex_unlock(&rpm->lock);
	वापस 0;
पूर्ण

u8 rpm_get_lmac_type(व्योम *rpmd, पूर्णांक lmac_id)
अणु
	rpm_t *rpm = rpmd;
	u64 req = 0, resp;
	पूर्णांक err;

	req = FIELD_SET(CMDREG_ID, CGX_CMD_GET_LINK_STS, req);
	err = cgx_fwi_cmd_generic(req, &resp, rpm, 0);
	अगर (!err)
		वापस FIELD_GET(RESP_LINKSTAT_LMAC_TYPE, resp);
	वापस err;
पूर्ण

पूर्णांक rpm_lmac_पूर्णांकernal_loopback(व्योम *rpmd, पूर्णांक lmac_id, bool enable)
अणु
	rpm_t *rpm = rpmd;
	u8 lmac_type;
	u64 cfg;

	अगर (!rpm || lmac_id >= rpm->lmac_count)
		वापस -ENODEV;
	lmac_type = rpm->mac_ops->get_lmac_type(rpm, lmac_id);
	अगर (lmac_type == LMAC_MODE_100G_R) अणु
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_PCS100X_CONTROL1);

		अगर (enable)
			cfg |= RPMX_MTI_PCS_LBK;
		अन्यथा
			cfg &= ~RPMX_MTI_PCS_LBK;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_PCS100X_CONTROL1, cfg);
	पूर्ण अन्यथा अणु
		cfg = rpm_पढ़ो(rpm, lmac_id, RPMX_MTI_LPCSX_CONTROL1);
		अगर (enable)
			cfg |= RPMX_MTI_PCS_LBK;
		अन्यथा
			cfg &= ~RPMX_MTI_PCS_LBK;
		rpm_ग_लिखो(rpm, lmac_id, RPMX_MTI_LPCSX_CONTROL1, cfg);
	पूर्ण

	वापस 0;
पूर्ण
