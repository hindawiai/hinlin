<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2021 Intel Corporation. */

#अगर_घोषित CONFIG_I40E_DCB
#समावेश "i40e.h"
#समावेश <net/dcbnl.h>

#घोषणा I40E_DCBNL_STATUS_SUCCESS	0
#घोषणा I40E_DCBNL_STATUS_ERROR		1
अटल bool i40e_dcbnl_find_app(काष्ठा i40e_dcbx_config *cfg,
				काष्ठा i40e_dcb_app_priority_table *app);
/**
 * i40e_get_pfc_delay - retrieve PFC Link Delay
 * @hw: poपूर्णांकer to hardware काष्ठा
 * @delay: holds the PFC Link delay value
 *
 * Returns PFC Link Delay from the PRTDCB_GENC.PFCLDA
 **/
अटल व्योम i40e_get_pfc_delay(काष्ठा i40e_hw *hw, u16 *delay)
अणु
	u32 val;

	val = rd32(hw, I40E_PRTDCB_GENC);
	*delay = (u16)((val & I40E_PRTDCB_GENC_PFCLDA_MASK) >>
		       I40E_PRTDCB_GENC_PFCLDA_SHIFT);
पूर्ण

/**
 * i40e_dcbnl_ieee_getets - retrieve local IEEE ETS configuration
 * @dev: the corresponding netdev
 * @ets: काष्ठाure to hold the ETS inक्रमmation
 *
 * Returns local IEEE ETS configuration
 **/
अटल पूर्णांक i40e_dcbnl_ieee_getets(काष्ठा net_device *dev,
				  काष्ठा ieee_ets *ets)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(dev);
	काष्ठा i40e_dcbx_config *dcbxcfg;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		वापस -EINVAL;

	dcbxcfg = &pf->hw.local_dcbx_config;
	ets->willing = dcbxcfg->etscfg.willing;
	ets->ets_cap = I40E_MAX_TRAFFIC_CLASS;
	ets->cbs = dcbxcfg->etscfg.cbs;
	स_नकल(ets->tc_tx_bw, dcbxcfg->etscfg.tcbwtable,
		माप(ets->tc_tx_bw));
	स_नकल(ets->tc_rx_bw, dcbxcfg->etscfg.tcbwtable,
		माप(ets->tc_rx_bw));
	स_नकल(ets->tc_tsa, dcbxcfg->etscfg.tsatable,
		माप(ets->tc_tsa));
	स_नकल(ets->prio_tc, dcbxcfg->etscfg.prioritytable,
		माप(ets->prio_tc));
	स_नकल(ets->tc_reco_bw, dcbxcfg->etsrec.tcbwtable,
		माप(ets->tc_reco_bw));
	स_नकल(ets->tc_reco_tsa, dcbxcfg->etsrec.tsatable,
		माप(ets->tc_reco_tsa));
	स_नकल(ets->reco_prio_tc, dcbxcfg->etscfg.prioritytable,
		माप(ets->reco_prio_tc));

	वापस 0;
पूर्ण

/**
 * i40e_dcbnl_ieee_getpfc - retrieve local IEEE PFC configuration
 * @dev: the corresponding netdev
 * @pfc: काष्ठाure to hold the PFC inक्रमmation
 *
 * Returns local IEEE PFC configuration
 **/
अटल पूर्णांक i40e_dcbnl_ieee_getpfc(काष्ठा net_device *dev,
				  काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(dev);
	काष्ठा i40e_dcbx_config *dcbxcfg;
	काष्ठा i40e_hw *hw = &pf->hw;
	पूर्णांक i;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		वापस -EINVAL;

	dcbxcfg = &hw->local_dcbx_config;
	pfc->pfc_cap = dcbxcfg->pfc.pfccap;
	pfc->pfc_en = dcbxcfg->pfc.pfcenable;
	pfc->mbc = dcbxcfg->pfc.mbc;
	i40e_get_pfc_delay(hw, &pfc->delay);

	/* Get Requests/Indications */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		pfc->requests[i] = pf->stats.priority_xoff_tx[i];
		pfc->indications[i] = pf->stats.priority_xoff_rx[i];
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_dcbnl_ieee_setets - set IEEE ETS configuration
 * @netdev: the corresponding netdev
 * @ets: काष्ठाure to hold the ETS inक्रमmation
 *
 * Set IEEE ETS configuration
 **/
अटल पूर्णांक i40e_dcbnl_ieee_setets(काष्ठा net_device *netdev,
				  काष्ठा ieee_ets *ets)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);
	काष्ठा i40e_dcbx_config *old_cfg;
	पूर्णांक i, ret;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस -EINVAL;

	old_cfg = &pf->hw.local_dcbx_config;
	/* Copy current config पूर्णांकo temp */
	pf->पंचांगp_cfg = *old_cfg;

	/* Update the ETS configuration क्रम temp */
	pf->पंचांगp_cfg.etscfg.willing = ets->willing;
	pf->पंचांगp_cfg.etscfg.maxtcs = I40E_MAX_TRAFFIC_CLASS;
	pf->पंचांगp_cfg.etscfg.cbs = ets->cbs;
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		pf->पंचांगp_cfg.etscfg.tcbwtable[i] = ets->tc_tx_bw[i];
		pf->पंचांगp_cfg.etscfg.tsatable[i] = ets->tc_tsa[i];
		pf->पंचांगp_cfg.etscfg.prioritytable[i] = ets->prio_tc[i];
		pf->पंचांगp_cfg.etsrec.tcbwtable[i] = ets->tc_reco_bw[i];
		pf->पंचांगp_cfg.etsrec.tsatable[i] = ets->tc_reco_tsa[i];
		pf->पंचांगp_cfg.etsrec.prioritytable[i] = ets->reco_prio_tc[i];
	पूर्ण

	/* Commit changes to HW */
	ret = i40e_hw_dcb_config(pf, &pf->पंचांगp_cfg);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Failed setting DCB ETS configuration err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_dcbnl_ieee_setpfc - set local IEEE PFC configuration
 * @netdev: the corresponding netdev
 * @pfc: काष्ठाure to hold the PFC inक्रमmation
 *
 * Sets local IEEE PFC configuration
 **/
अटल पूर्णांक i40e_dcbnl_ieee_setpfc(काष्ठा net_device *netdev,
				  काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);
	काष्ठा i40e_dcbx_config *old_cfg;
	पूर्णांक ret;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस -EINVAL;

	old_cfg = &pf->hw.local_dcbx_config;
	/* Copy current config पूर्णांकo temp */
	pf->पंचांगp_cfg = *old_cfg;
	अगर (pfc->pfc_cap)
		pf->पंचांगp_cfg.pfc.pfccap = pfc->pfc_cap;
	अन्यथा
		pf->पंचांगp_cfg.pfc.pfccap = I40E_MAX_TRAFFIC_CLASS;
	pf->पंचांगp_cfg.pfc.pfcenable = pfc->pfc_en;

	ret = i40e_hw_dcb_config(pf, &pf->पंचांगp_cfg);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Failed setting DCB PFC configuration err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_dcbnl_ieee_setapp - set local IEEE App configuration
 * @netdev: the corresponding netdev
 * @app: काष्ठाure to hold the Application inक्रमmation
 *
 * Sets local IEEE App configuration
 **/
अटल पूर्णांक i40e_dcbnl_ieee_setapp(काष्ठा net_device *netdev,
				  काष्ठा dcb_app *app)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);
	काष्ठा i40e_dcb_app_priority_table new_app;
	काष्ठा i40e_dcbx_config *old_cfg;
	पूर्णांक ret;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस -EINVAL;

	old_cfg = &pf->hw.local_dcbx_config;
	अगर (old_cfg->numapps == I40E_DCBX_MAX_APPS)
		वापस -EINVAL;

	ret = dcb_ieee_setapp(netdev, app);
	अगर (ret)
		वापस ret;

	new_app.selector = app->selector;
	new_app.protocolid = app->protocol;
	new_app.priority = app->priority;
	/* Alपढ़ोy पूर्णांकernally available */
	अगर (i40e_dcbnl_find_app(old_cfg, &new_app))
		वापस 0;

	/* Copy current config पूर्णांकo temp */
	pf->पंचांगp_cfg = *old_cfg;
	/* Add the app */
	pf->पंचांगp_cfg.app[pf->पंचांगp_cfg.numapps++] = new_app;

	ret = i40e_hw_dcb_config(pf, &pf->पंचांगp_cfg);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Failed setting DCB configuration err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_dcbnl_ieee_delapp - delete local IEEE App configuration
 * @netdev: the corresponding netdev
 * @app: काष्ठाure to hold the Application inक्रमmation
 *
 * Deletes local IEEE App configuration other than the first application
 * required by firmware
 **/
अटल पूर्णांक i40e_dcbnl_ieee_delapp(काष्ठा net_device *netdev,
				  काष्ठा dcb_app *app)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);
	काष्ठा i40e_dcbx_config *old_cfg;
	पूर्णांक i, j, ret;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_IEEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस -EINVAL;

	ret = dcb_ieee_delapp(netdev, app);
	अगर (ret)
		वापस ret;

	old_cfg = &pf->hw.local_dcbx_config;
	/* Need one app क्रम FW so keep it */
	अगर (old_cfg->numapps == 1)
		वापस 0;

	/* Copy current config पूर्णांकo temp */
	pf->पंचांगp_cfg = *old_cfg;

	/* Find and reset the app */
	क्रम (i = 1; i < pf->पंचांगp_cfg.numapps; i++) अणु
		अगर (app->selector == pf->पंचांगp_cfg.app[i].selector &&
		    app->protocol == pf->पंचांगp_cfg.app[i].protocolid &&
		    app->priority == pf->पंचांगp_cfg.app[i].priority) अणु
			/* Reset the app data */
			pf->पंचांगp_cfg.app[i].selector = 0;
			pf->पंचांगp_cfg.app[i].protocolid = 0;
			pf->पंचांगp_cfg.app[i].priority = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If the specअगरic DCB app not found */
	अगर (i == pf->पंचांगp_cfg.numapps)
		वापस -EINVAL;

	pf->पंचांगp_cfg.numapps--;
	/* Overग_लिखो the पंचांगp_cfg app */
	क्रम (j = i; j < pf->पंचांगp_cfg.numapps; j++)
		pf->पंचांगp_cfg.app[j] = old_cfg->app[j + 1];

	ret = i40e_hw_dcb_config(pf, &pf->पंचांगp_cfg);
	अगर (ret) अणु
		dev_info(&pf->pdev->dev,
			 "Failed setting DCB configuration err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_dcbnl_माला_लोtate - Get DCB enabled state
 * @netdev: the corresponding netdev
 *
 * Get the current DCB enabled state
 **/
अटल u8 i40e_dcbnl_माला_लोtate(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	dev_dbg(&pf->pdev->dev, "DCB state=%d\n",
		!!(pf->flags & I40E_FLAG_DCB_ENABLED));
	वापस !!(pf->flags & I40E_FLAG_DCB_ENABLED);
पूर्ण

/**
 * i40e_dcbnl_setstate - Set DCB state
 * @netdev: the corresponding netdev
 * @state: enable or disable
 *
 * Set the DCB state
 **/
अटल u8 i40e_dcbnl_setstate(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);
	पूर्णांक ret = I40E_DCBNL_STATUS_SUCCESS;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस ret;

	dev_dbg(&pf->pdev->dev, "new state=%d current state=%d\n",
		state, (pf->flags & I40E_FLAG_DCB_ENABLED) ? 1 : 0);
	/* Nothing to करो */
	अगर (!state == !(pf->flags & I40E_FLAG_DCB_ENABLED))
		वापस ret;

	अगर (i40e_is_sw_dcb(pf)) अणु
		अगर (state) अणु
			pf->flags |= I40E_FLAG_DCB_ENABLED;
			स_नकल(&pf->hw.desired_dcbx_config,
			       &pf->hw.local_dcbx_config,
			       माप(काष्ठा i40e_dcbx_config));
		पूर्ण अन्यथा अणु
			pf->flags &= ~I40E_FLAG_DCB_ENABLED;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Cannot directly manipulate FW LLDP Agent */
		ret = I40E_DCBNL_STATUS_ERROR;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * i40e_dcbnl_set_pg_tc_cfg_tx - Set CEE PG Tx config
 * @netdev: the corresponding netdev
 * @tc: the corresponding traffic class
 * @prio_type: the traffic priority type
 * @bwg_id: the BW group id the traffic class beदीर्घs to
 * @bw_pct: the BW percentage क्रम the corresponding BWG
 * @up_map: prio mapped to corresponding tc
 *
 * Set Tx PG settings क्रम CEE mode
 **/
अटल व्योम i40e_dcbnl_set_pg_tc_cfg_tx(काष्ठा net_device *netdev, पूर्णांक tc,
					u8 prio_type, u8 bwg_id, u8 bw_pct,
					u8 up_map)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);
	पूर्णांक i;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस;

	/* LLTC not supported yet */
	अगर (tc >= I40E_MAX_TRAFFIC_CLASS)
		वापस;

	/* prio_type, bwg_id and bw_pct per UP are not supported */

	/* Use only up_map to map tc */
	क्रम (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) अणु
		अगर (up_map & BIT(i))
			pf->पंचांगp_cfg.etscfg.prioritytable[i] = tc;
	पूर्ण
	pf->पंचांगp_cfg.etscfg.tsatable[tc] = I40E_IEEE_TSA_ETS;
	dev_dbg(&pf->pdev->dev,
		"Set PG config tc=%d bwg_id=%d prio_type=%d bw_pct=%d up_map=%d\n",
		tc, bwg_id, prio_type, bw_pct, up_map);
पूर्ण

/**
 * i40e_dcbnl_set_pg_bwg_cfg_tx - Set CEE PG Tx BW config
 * @netdev: the corresponding netdev
 * @pgid: the corresponding traffic class
 * @bw_pct: the BW percentage क्रम the specअगरied traffic class
 *
 * Set Tx BW settings क्रम CEE mode
 **/
अटल व्योम i40e_dcbnl_set_pg_bwg_cfg_tx(काष्ठा net_device *netdev, पूर्णांक pgid,
					 u8 bw_pct)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस;

	/* LLTC not supported yet */
	अगर (pgid >= I40E_MAX_TRAFFIC_CLASS)
		वापस;

	pf->पंचांगp_cfg.etscfg.tcbwtable[pgid] = bw_pct;
	dev_dbg(&pf->pdev->dev, "Set PG BW config tc=%d bw_pct=%d\n",
		pgid, bw_pct);
पूर्ण

/**
 * i40e_dcbnl_set_pg_tc_cfg_rx - Set CEE PG Rx config
 * @netdev: the corresponding netdev
 * @prio: the corresponding traffic class
 * @prio_type: the traffic priority type
 * @pgid: the BW group id the traffic class beदीर्घs to
 * @bw_pct: the BW percentage क्रम the corresponding BWG
 * @up_map: prio mapped to corresponding tc
 *
 * Set Rx BW settings क्रम CEE mode. The hardware करोes not support this
 * so we won't allow setting of this parameter.
 **/
अटल व्योम i40e_dcbnl_set_pg_tc_cfg_rx(काष्ठा net_device *netdev,
					पूर्णांक __always_unused prio,
					u8 __always_unused prio_type,
					u8 __always_unused pgid,
					u8 __always_unused bw_pct,
					u8 __always_unused up_map)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	dev_dbg(&pf->pdev->dev, "Rx TC PG Config Not Supported.\n");
पूर्ण

/**
 * i40e_dcbnl_set_pg_bwg_cfg_rx - Set CEE PG Rx config
 * @netdev: the corresponding netdev
 * @pgid: the corresponding traffic class
 * @bw_pct: the BW percentage क्रम the specअगरied traffic class
 *
 * Set Rx BW settings क्रम CEE mode. The hardware करोes not support this
 * so we won't allow setting of this parameter.
 **/
अटल व्योम i40e_dcbnl_set_pg_bwg_cfg_rx(काष्ठा net_device *netdev, पूर्णांक pgid,
					 u8 bw_pct)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	dev_dbg(&pf->pdev->dev, "Rx BWG PG Config Not Supported.\n");
पूर्ण

/**
 * i40e_dcbnl_get_pg_tc_cfg_tx - Get CEE PG Tx config
 * @netdev: the corresponding netdev
 * @prio: the corresponding user priority
 * @prio_type: traffic priority type
 * @pgid: the BW group ID the traffic class beदीर्घs to
 * @bw_pct: BW percentage क्रम the corresponding BWG
 * @up_map: prio mapped to corresponding TC
 *
 * Get Tx PG settings क्रम CEE mode
 **/
अटल व्योम i40e_dcbnl_get_pg_tc_cfg_tx(काष्ठा net_device *netdev, पूर्णांक prio,
					u8 __always_unused *prio_type,
					u8 *pgid,
					u8 __always_unused *bw_pct,
					u8 __always_unused *up_map)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस;

	अगर (prio >= I40E_MAX_USER_PRIORITY)
		वापस;

	*pgid = pf->hw.local_dcbx_config.etscfg.prioritytable[prio];
	dev_dbg(&pf->pdev->dev, "Get PG config prio=%d tc=%d\n",
		prio, *pgid);
पूर्ण

/**
 * i40e_dcbnl_get_pg_bwg_cfg_tx - Get CEE PG BW config
 * @netdev: the corresponding netdev
 * @pgid: the corresponding traffic class
 * @bw_pct: the BW percentage क्रम the corresponding TC
 *
 * Get Tx BW settings क्रम given TC in CEE mode
 **/
अटल व्योम i40e_dcbnl_get_pg_bwg_cfg_tx(काष्ठा net_device *netdev, पूर्णांक pgid,
					 u8 *bw_pct)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस;

	अगर (pgid >= I40E_MAX_TRAFFIC_CLASS)
		वापस;

	*bw_pct = pf->hw.local_dcbx_config.etscfg.tcbwtable[pgid];
	dev_dbg(&pf->pdev->dev, "Get PG BW config tc=%d bw_pct=%d\n",
		pgid, *bw_pct);
पूर्ण

/**
 * i40e_dcbnl_get_pg_tc_cfg_rx - Get CEE PG Rx config
 * @netdev: the corresponding netdev
 * @prio: the corresponding user priority
 * @prio_type: the traffic priority type
 * @pgid: the PG ID
 * @bw_pct: the BW percentage क्रम the corresponding BWG
 * @up_map: prio mapped to corresponding TC
 *
 * Get Rx PG settings क्रम CEE mode. The UP2TC map is applied in same
 * manner क्रम Tx and Rx (symmetrical) so वापस the TC inक्रमmation क्रम
 * given priority accordingly.
 **/
अटल व्योम i40e_dcbnl_get_pg_tc_cfg_rx(काष्ठा net_device *netdev, पूर्णांक prio,
					u8 *prio_type, u8 *pgid, u8 *bw_pct,
					u8 *up_map)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस;

	अगर (prio >= I40E_MAX_USER_PRIORITY)
		वापस;

	*pgid = pf->hw.local_dcbx_config.etscfg.prioritytable[prio];
पूर्ण

/**
 * i40e_dcbnl_get_pg_bwg_cfg_rx - Get CEE PG BW Rx config
 * @netdev: the corresponding netdev
 * @pgid: the corresponding traffic class
 * @bw_pct: the BW percentage क्रम the corresponding TC
 *
 * Get Rx BW settings क्रम given TC in CEE mode
 * The adapter करोesn't support Rx ETS and runs in strict priority
 * mode in Rx path and hence just वापस 0.
 **/
अटल व्योम i40e_dcbnl_get_pg_bwg_cfg_rx(काष्ठा net_device *netdev, पूर्णांक pgid,
					 u8 *bw_pct)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस;
	*bw_pct = 0;
पूर्ण

/**
 * i40e_dcbnl_set_pfc_cfg - Set CEE PFC configuration
 * @netdev: the corresponding netdev
 * @prio: the corresponding user priority
 * @setting: the PFC setting क्रम given priority
 *
 * Set the PFC enabled/disabled setting क्रम given user priority
 **/
अटल व्योम i40e_dcbnl_set_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक prio,
				   u8 setting)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस;

	अगर (prio >= I40E_MAX_USER_PRIORITY)
		वापस;

	pf->पंचांगp_cfg.pfc.pfccap = I40E_MAX_TRAFFIC_CLASS;
	अगर (setting)
		pf->पंचांगp_cfg.pfc.pfcenable |= BIT(prio);
	अन्यथा
		pf->पंचांगp_cfg.pfc.pfcenable &= ~BIT(prio);
	dev_dbg(&pf->pdev->dev,
		"Set PFC Config up=%d setting=%d pfcenable=0x%x\n",
		prio, setting, pf->पंचांगp_cfg.pfc.pfcenable);
पूर्ण

/**
 * i40e_dcbnl_get_pfc_cfg - Get CEE PFC configuration
 * @netdev: the corresponding netdev
 * @prio: the corresponding user priority
 * @setting: the PFC setting क्रम given priority
 *
 * Get the PFC enabled/disabled setting क्रम given user priority
 **/
अटल व्योम i40e_dcbnl_get_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक prio,
				   u8 *setting)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस;

	अगर (prio >= I40E_MAX_USER_PRIORITY)
		वापस;

	*setting = (pf->hw.local_dcbx_config.pfc.pfcenable >> prio) & 0x1;
	dev_dbg(&pf->pdev->dev,
		"Get PFC Config up=%d setting=%d pfcenable=0x%x\n",
		prio, *setting, pf->hw.local_dcbx_config.pfc.pfcenable);
पूर्ण

/**
 * i40e_dcbnl_cee_set_all - Commit CEE DCB settings to hardware
 * @netdev: the corresponding netdev
 *
 * Commit the current DCB configuration to hardware
 **/
अटल u8 i40e_dcbnl_cee_set_all(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);
	पूर्णांक err;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस I40E_DCBNL_STATUS_ERROR;

	dev_dbg(&pf->pdev->dev, "Commit DCB Configuration to the hardware\n");
	err = i40e_hw_dcb_config(pf, &pf->पंचांगp_cfg);

	वापस err ? I40E_DCBNL_STATUS_ERROR : I40E_DCBNL_STATUS_SUCCESS;
पूर्ण

/**
 * i40e_dcbnl_get_cap - Get DCBX capabilities of adapter
 * @netdev: the corresponding netdev
 * @capid: the capability type
 * @cap: the capability value
 *
 * Return the capability value क्रम a given capability type
 **/
अटल u8 i40e_dcbnl_get_cap(काष्ठा net_device *netdev, पूर्णांक capid, u8 *cap)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	अगर (!(pf->flags & I40E_FLAG_DCB_CAPABLE))
		वापस I40E_DCBNL_STATUS_ERROR;

	चयन (capid) अणु
	हाल DCB_CAP_ATTR_PG:
	हाल DCB_CAP_ATTR_PFC:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_PG_TCS:
	हाल DCB_CAP_ATTR_PFC_TCS:
		*cap = 0x80;
		अवरोध;
	हाल DCB_CAP_ATTR_DCBX:
		*cap = pf->dcbx_cap;
		अवरोध;
	हाल DCB_CAP_ATTR_UP2TC:
	हाल DCB_CAP_ATTR_GSP:
	हाल DCB_CAP_ATTR_BCN:
	शेष:
		*cap = false;
		अवरोध;
	पूर्ण

	dev_dbg(&pf->pdev->dev, "Get Capability cap=%d capval=0x%x\n",
		capid, *cap);
	वापस I40E_DCBNL_STATUS_SUCCESS;
पूर्ण

/**
 * i40e_dcbnl_getnumtcs - Get max number of traffic classes supported
 * @netdev: the corresponding netdev
 * @tcid: the TC id
 * @num: total number of TCs supported by the device
 *
 * Return the total number of TCs supported by the adapter
 **/
अटल पूर्णांक i40e_dcbnl_getnumtcs(काष्ठा net_device *netdev, पूर्णांक tcid, u8 *num)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	अगर (!(pf->flags & I40E_FLAG_DCB_CAPABLE))
		वापस -EINVAL;

	*num = I40E_MAX_TRAFFIC_CLASS;
	वापस 0;
पूर्ण

/**
 * i40e_dcbnl_setnumtcs - Set CEE number of traffic classes
 * @netdev: the corresponding netdev
 * @tcid: the TC id
 * @num: total number of TCs
 *
 * Set the total number of TCs (Unsupported)
 **/
अटल पूर्णांक i40e_dcbnl_setnumtcs(काष्ठा net_device *netdev, पूर्णांक tcid, u8 num)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * i40e_dcbnl_getpfcstate - Get CEE PFC mode
 * @netdev: the corresponding netdev
 *
 * Get the current PFC enabled state
 **/
अटल u8 i40e_dcbnl_getpfcstate(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	/* Return enabled अगर any PFC enabled UP */
	अगर (pf->hw.local_dcbx_config.pfc.pfcenable)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * i40e_dcbnl_setpfcstate - Set CEE PFC mode
 * @netdev: the corresponding netdev
 * @state: required state
 *
 * The PFC state to be set; this is enabled/disabled based on the PFC
 * priority settings and not via this call क्रम i40e driver
 **/
अटल व्योम i40e_dcbnl_setpfcstate(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	dev_dbg(&pf->pdev->dev, "PFC State is modified via PFC config.\n");
पूर्ण

/**
 * i40e_dcbnl_getapp - Get CEE APP
 * @netdev: the corresponding netdev
 * @idtype: the App selector
 * @id: the App ethtype or port number
 *
 * Return the CEE mode app क्रम the given idtype and id
 **/
अटल पूर्णांक i40e_dcbnl_getapp(काष्ठा net_device *netdev, u8 idtype, u16 id)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);
	काष्ठा dcb_app app = अणु
				.selector = idtype,
				.protocol = id,
			     पूर्ण;

	अगर (!(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED))
		वापस -EINVAL;

	वापस dcb_getapp(netdev, &app);
पूर्ण

/**
 * i40e_dcbnl_setdcbx - set required DCBx capability
 * @netdev: the corresponding netdev
 * @mode: new DCB mode managed or CEE+IEEE
 *
 * Set DCBx capability features
 **/
अटल u8 i40e_dcbnl_setdcbx(काष्ठा net_device *netdev, u8 mode)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(netdev);

	/* Do not allow to set mode अगर managed by Firmware */
	अगर (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED)
		वापस I40E_DCBNL_STATUS_ERROR;

	/* No support क्रम LLD_MANAGED modes or CEE+IEEE */
	अगर ((mode & DCB_CAP_DCBX_LLD_MANAGED) ||
	    ((mode & DCB_CAP_DCBX_VER_IEEE) && (mode & DCB_CAP_DCBX_VER_CEE)) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		वापस I40E_DCBNL_STATUS_ERROR;

	/* Alपढ़ोy set to the given mode no change */
	अगर (mode == pf->dcbx_cap)
		वापस I40E_DCBNL_STATUS_SUCCESS;

	pf->dcbx_cap = mode;
	अगर (mode & DCB_CAP_DCBX_VER_CEE)
		pf->hw.local_dcbx_config.dcbx_mode = I40E_DCBX_MODE_CEE;
	अन्यथा
		pf->hw.local_dcbx_config.dcbx_mode = I40E_DCBX_MODE_IEEE;

	dev_dbg(&pf->pdev->dev, "mode=%d\n", mode);
	वापस I40E_DCBNL_STATUS_SUCCESS;
पूर्ण

/**
 * i40e_dcbnl_getdcbx - retrieve current DCBx capability
 * @dev: the corresponding netdev
 *
 * Returns DCBx capability features
 **/
अटल u8 i40e_dcbnl_getdcbx(काष्ठा net_device *dev)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(dev);

	वापस pf->dcbx_cap;
पूर्ण

/**
 * i40e_dcbnl_get_perm_hw_addr - MAC address used by DCBx
 * @dev: the corresponding netdev
 * @perm_addr: buffer to store the MAC address
 *
 * Returns the SAN MAC address used क्रम LLDP exchange
 **/
अटल व्योम i40e_dcbnl_get_perm_hw_addr(काष्ठा net_device *dev,
					u8 *perm_addr)
अणु
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(dev);
	पूर्णांक i, j;

	स_रखो(perm_addr, 0xff, MAX_ADDR_LEN);

	क्रम (i = 0; i < dev->addr_len; i++)
		perm_addr[i] = pf->hw.mac.perm_addr[i];

	क्रम (j = 0; j < dev->addr_len; j++, i++)
		perm_addr[i] = pf->hw.mac.san_addr[j];
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops dcbnl_ops = अणु
	.ieee_getets	= i40e_dcbnl_ieee_getets,
	.ieee_getpfc	= i40e_dcbnl_ieee_getpfc,
	.getdcbx	= i40e_dcbnl_getdcbx,
	.getpermhwaddr	= i40e_dcbnl_get_perm_hw_addr,
	.ieee_setets	= i40e_dcbnl_ieee_setets,
	.ieee_setpfc	= i40e_dcbnl_ieee_setpfc,
	.ieee_setapp	= i40e_dcbnl_ieee_setapp,
	.ieee_delapp	= i40e_dcbnl_ieee_delapp,
	.माला_लोtate	= i40e_dcbnl_माला_लोtate,
	.setstate	= i40e_dcbnl_setstate,
	.setpgtccfgtx	= i40e_dcbnl_set_pg_tc_cfg_tx,
	.setpgbwgcfgtx	= i40e_dcbnl_set_pg_bwg_cfg_tx,
	.setpgtccfgrx	= i40e_dcbnl_set_pg_tc_cfg_rx,
	.setpgbwgcfgrx	= i40e_dcbnl_set_pg_bwg_cfg_rx,
	.getpgtccfgtx	= i40e_dcbnl_get_pg_tc_cfg_tx,
	.getpgbwgcfgtx	= i40e_dcbnl_get_pg_bwg_cfg_tx,
	.getpgtccfgrx	= i40e_dcbnl_get_pg_tc_cfg_rx,
	.getpgbwgcfgrx	= i40e_dcbnl_get_pg_bwg_cfg_rx,
	.setpfccfg	= i40e_dcbnl_set_pfc_cfg,
	.getpfccfg	= i40e_dcbnl_get_pfc_cfg,
	.setall		= i40e_dcbnl_cee_set_all,
	.अ_लोap		= i40e_dcbnl_get_cap,
	.getnumtcs	= i40e_dcbnl_getnumtcs,
	.setnumtcs	= i40e_dcbnl_setnumtcs,
	.getpfcstate	= i40e_dcbnl_getpfcstate,
	.setpfcstate	= i40e_dcbnl_setpfcstate,
	.getapp		= i40e_dcbnl_getapp,
	.setdcbx	= i40e_dcbnl_setdcbx,
पूर्ण;

/**
 * i40e_dcbnl_set_all - set all the apps and ieee data from DCBx config
 * @vsi: the corresponding vsi
 *
 * Set up all the IEEE APPs in the DCBNL App Table and generate event क्रम
 * other settings
 **/
व्योम i40e_dcbnl_set_all(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा net_device *dev = vsi->netdev;
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(dev);
	काष्ठा i40e_dcbx_config *dcbxcfg;
	काष्ठा i40e_hw *hw = &pf->hw;
	काष्ठा dcb_app sapp;
	u8 prio, tc_map;
	पूर्णांक i;

	/* SW DCB taken care by DCBNL set calls */
	अगर (pf->dcbx_cap & DCB_CAP_DCBX_HOST)
		वापस;

	/* DCB not enabled */
	अगर (!(pf->flags & I40E_FLAG_DCB_ENABLED))
		वापस;

	/* MFP mode but not an iSCSI PF so वापस */
	अगर ((pf->flags & I40E_FLAG_MFP_ENABLED) && !(hw->func_caps.iscsi))
		वापस;

	dcbxcfg = &hw->local_dcbx_config;

	/* Set up all the App TLVs अगर DCBx is negotiated */
	क्रम (i = 0; i < dcbxcfg->numapps; i++) अणु
		prio = dcbxcfg->app[i].priority;
		tc_map = BIT(dcbxcfg->etscfg.prioritytable[prio]);

		/* Add APP only अगर the TC is enabled क्रम this VSI */
		अगर (tc_map & vsi->tc_config.enabled_tc) अणु
			sapp.selector = dcbxcfg->app[i].selector;
			sapp.protocol = dcbxcfg->app[i].protocolid;
			sapp.priority = prio;
			dcb_ieee_setapp(dev, &sapp);
		पूर्ण
	पूर्ण

	/* Notअगरy user-space of the changes */
	dcbnl_ieee_notअगरy(dev, RTM_SETDCB, DCB_CMD_IEEE_SET, 0, 0);
पूर्ण

/**
 * i40e_dcbnl_vsi_del_app - Delete APP क्रम given VSI
 * @vsi: the corresponding vsi
 * @app: APP to delete
 *
 * Delete given APP from the DCBNL APP table क्रम given
 * VSI
 **/
अटल पूर्णांक i40e_dcbnl_vsi_del_app(काष्ठा i40e_vsi *vsi,
				  काष्ठा i40e_dcb_app_priority_table *app)
अणु
	काष्ठा net_device *dev = vsi->netdev;
	काष्ठा dcb_app sapp;

	अगर (!dev)
		वापस -EINVAL;

	sapp.selector = app->selector;
	sapp.protocol = app->protocolid;
	sapp.priority = app->priority;
	वापस dcb_ieee_delapp(dev, &sapp);
पूर्ण

/**
 * i40e_dcbnl_del_app - Delete APP on all VSIs
 * @pf: the corresponding PF
 * @app: APP to delete
 *
 * Delete given APP from all the VSIs क्रम given PF
 **/
अटल व्योम i40e_dcbnl_del_app(काष्ठा i40e_pf *pf,
			       काष्ठा i40e_dcb_app_priority_table *app)
अणु
	पूर्णांक v, err;

	क्रम (v = 0; v < pf->num_alloc_vsi; v++) अणु
		अगर (pf->vsi[v] && pf->vsi[v]->netdev) अणु
			err = i40e_dcbnl_vsi_del_app(pf->vsi[v], app);
			dev_dbg(&pf->pdev->dev, "Deleting app for VSI seid=%d err=%d sel=%d proto=0x%x prio=%d\n",
				pf->vsi[v]->seid, err, app->selector,
				app->protocolid, app->priority);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * i40e_dcbnl_find_app - Search APP in given DCB config
 * @cfg: DCBX configuration data
 * @app: APP to search क्रम
 *
 * Find given APP in the DCB configuration
 **/
अटल bool i40e_dcbnl_find_app(काष्ठा i40e_dcbx_config *cfg,
				काष्ठा i40e_dcb_app_priority_table *app)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cfg->numapps; i++) अणु
		अगर (app->selector == cfg->app[i].selector &&
		    app->protocolid == cfg->app[i].protocolid &&
		    app->priority == cfg->app[i].priority)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * i40e_dcbnl_flush_apps - Delete all हटाओd APPs
 * @pf: the corresponding PF
 * @old_cfg: old DCBX configuration data
 * @new_cfg: new DCBX configuration data
 *
 * Find and delete all APPs that are not present in the passed
 * DCB configuration
 **/
व्योम i40e_dcbnl_flush_apps(काष्ठा i40e_pf *pf,
			   काष्ठा i40e_dcbx_config *old_cfg,
			   काष्ठा i40e_dcbx_config *new_cfg)
अणु
	काष्ठा i40e_dcb_app_priority_table app;
	पूर्णांक i;

	/* MFP mode but not an iSCSI PF so वापस */
	अगर ((pf->flags & I40E_FLAG_MFP_ENABLED) && !(pf->hw.func_caps.iscsi))
		वापस;

	क्रम (i = 0; i < old_cfg->numapps; i++) अणु
		app = old_cfg->app[i];
		/* The APP is not available anymore delete it */
		अगर (!i40e_dcbnl_find_app(new_cfg, &app))
			i40e_dcbnl_del_app(pf, &app);
	पूर्ण
पूर्ण

/**
 * i40e_dcbnl_setup - DCBNL setup
 * @vsi: the corresponding vsi
 *
 * Set up DCBNL ops and initial APP TLVs
 **/
व्योम i40e_dcbnl_setup(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा net_device *dev = vsi->netdev;
	काष्ठा i40e_pf *pf = i40e_netdev_to_pf(dev);

	/* Not DCB capable */
	अगर (!(pf->flags & I40E_FLAG_DCB_CAPABLE))
		वापस;

	dev->dcbnl_ops = &dcbnl_ops;

	/* Set initial IEEE DCB settings */
	i40e_dcbnl_set_all(vsi);
पूर्ण
#पूर्ण_अगर /* CONFIG_I40E_DCB */
