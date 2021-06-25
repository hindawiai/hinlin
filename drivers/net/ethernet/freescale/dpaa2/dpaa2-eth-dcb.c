<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2020 NXP */

#समावेश "dpaa2-eth.h"

अटल पूर्णांक dpaa2_eth_dcbnl_ieee_getpfc(काष्ठा net_device *net_dev,
				       काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);

	अगर (!(priv->link_state.options & DPNI_LINK_OPT_PFC_PAUSE))
		वापस 0;

	स_नकल(pfc, &priv->pfc, माप(priv->pfc));
	pfc->pfc_cap = dpaa2_eth_tc_count(priv);

	वापस 0;
पूर्ण

अटल अंतरभूत bool dpaa2_eth_is_prio_enabled(u8 pfc_en, u8 tc)
अणु
	वापस !!(pfc_en & (1 << tc));
पूर्ण

अटल पूर्णांक dpaa2_eth_set_pfc_cn(काष्ठा dpaa2_eth_priv *priv, u8 pfc_en)
अणु
	काष्ठा dpni_congestion_notअगरication_cfg cfg = अणु0पूर्ण;
	पूर्णांक i, err;

	cfg.notअगरication_mode = DPNI_CONG_OPT_FLOW_CONTROL;
	cfg.units = DPNI_CONGESTION_UNIT_FRAMES;
	cfg.message_iova = 0ULL;
	cfg.message_ctx = 0ULL;

	क्रम (i = 0; i < dpaa2_eth_tc_count(priv); i++) अणु
		अगर (dpaa2_eth_is_prio_enabled(pfc_en, i)) अणु
			cfg.threshold_entry = DPAA2_ETH_CN_THRESH_ENTRY(priv);
			cfg.threshold_निकास = DPAA2_ETH_CN_THRESH_EXIT(priv);
		पूर्ण अन्यथा अणु
			/* For priorities not set in the pfc_en mask, we leave
			 * the congestion thresholds at zero, which effectively
			 * disables generation of PFC frames क्रम them
			 */
			cfg.threshold_entry = 0;
			cfg.threshold_निकास = 0;
		पूर्ण

		err = dpni_set_congestion_notअगरication(priv->mc_io, 0,
						       priv->mc_token,
						       DPNI_QUEUE_RX, i, &cfg);
		अगर (err) अणु
			netdev_err(priv->net_dev,
				   "dpni_set_congestion_notification failed\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_eth_dcbnl_ieee_setpfc(काष्ठा net_device *net_dev,
				       काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);
	काष्ठा dpni_link_cfg link_cfg = अणु0पूर्ण;
	bool tx_छोड़ो;
	पूर्णांक err;

	अगर (pfc->mbc || pfc->delay)
		वापस -EOPNOTSUPP;

	/* If same PFC enabled mask, nothing to करो */
	अगर (priv->pfc.pfc_en == pfc->pfc_en)
		वापस 0;

	/* We allow PFC configuration even अगर it won't have any effect until
	 * general छोड़ो frames are enabled
	 */
	tx_छोड़ो = dpaa2_eth_tx_छोड़ो_enabled(priv->link_state.options);
	अगर (!dpaa2_eth_rx_छोड़ो_enabled(priv->link_state.options) || !tx_छोड़ो)
		netdev_warn(net_dev, "Pause support must be enabled in order for PFC to work!\n");

	link_cfg.rate = priv->link_state.rate;
	link_cfg.options = priv->link_state.options;
	अगर (pfc->pfc_en)
		link_cfg.options |= DPNI_LINK_OPT_PFC_PAUSE;
	अन्यथा
		link_cfg.options &= ~DPNI_LINK_OPT_PFC_PAUSE;
	err = dpni_set_link_cfg(priv->mc_io, 0, priv->mc_token, &link_cfg);
	अगर (err) अणु
		netdev_err(net_dev, "dpni_set_link_cfg failed\n");
		वापस err;
	पूर्ण

	/* Configure congestion notअगरications क्रम the enabled priorities */
	err = dpaa2_eth_set_pfc_cn(priv, pfc->pfc_en);
	अगर (err)
		वापस err;

	स_नकल(&priv->pfc, pfc, माप(priv->pfc));
	priv->pfc_enabled = !!pfc->pfc_en;

	dpaa2_eth_set_rx_taildrop(priv, tx_छोड़ो, priv->pfc_enabled);

	वापस 0;
पूर्ण

अटल u8 dpaa2_eth_dcbnl_getdcbx(काष्ठा net_device *net_dev)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);

	वापस priv->dcbx_mode;
पूर्ण

अटल u8 dpaa2_eth_dcbnl_setdcbx(काष्ठा net_device *net_dev, u8 mode)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);

	वापस (mode != (priv->dcbx_mode)) ? 1 : 0;
पूर्ण

अटल u8 dpaa2_eth_dcbnl_अ_लोap(काष्ठा net_device *net_dev, पूर्णांक capid, u8 *cap)
अणु
	काष्ठा dpaa2_eth_priv *priv = netdev_priv(net_dev);

	चयन (capid) अणु
	हाल DCB_CAP_ATTR_PFC:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_PFC_TCS:
		*cap = 1 << (dpaa2_eth_tc_count(priv) - 1);
		अवरोध;
	हाल DCB_CAP_ATTR_DCBX:
		*cap = priv->dcbx_mode;
		अवरोध;
	शेष:
		*cap = false;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा dcbnl_rtnl_ops dpaa2_eth_dcbnl_ops = अणु
	.ieee_getpfc	= dpaa2_eth_dcbnl_ieee_getpfc,
	.ieee_setpfc	= dpaa2_eth_dcbnl_ieee_setpfc,
	.getdcbx	= dpaa2_eth_dcbnl_getdcbx,
	.setdcbx	= dpaa2_eth_dcbnl_setdcbx,
	.अ_लोap		= dpaa2_eth_dcbnl_अ_लोap,
पूर्ण;
