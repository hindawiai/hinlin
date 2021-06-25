<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Intel Corporation. */

#समावेश "ice.h"
#समावेश "ice_dcb.h"
#समावेश "ice_dcb_lib.h"
#समावेश "ice_dcb_nl.h"
#समावेश <net/dcbnl.h>

/**
 * ice_dcbnl_devreset - perक्रमm enough of a अगरकरोwn/अगरup to sync DCBNL info
 * @netdev: device associated with पूर्णांकerface that needs reset
 */
अटल व्योम ice_dcbnl_devreset(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);

	जबतक (ice_is_reset_in_progress(pf->state))
		usleep_range(1000, 2000);

	dev_बंद(netdev);
	netdev_state_change(netdev);
	dev_खोलो(netdev, शून्य);
	netdev_state_change(netdev);
पूर्ण

/**
 * ice_dcbnl_getets - retrieve local ETS configuration
 * @netdev: the relevant netdev
 * @ets: काष्ठा to hold ETS configuration
 */
अटल पूर्णांक ice_dcbnl_getets(काष्ठा net_device *netdev, काष्ठा ieee_ets *ets)
अणु
	काष्ठा ice_dcbx_cfg *dcbxcfg;
	काष्ठा ice_pf *pf;

	pf = ice_netdev_to_pf(netdev);
	dcbxcfg = &pf->hw.port_info->qos_cfg.local_dcbx_cfg;

	ets->willing = dcbxcfg->etscfg.willing;
	ets->ets_cap = dcbxcfg->etscfg.maxtcs;
	ets->cbs = dcbxcfg->etscfg.cbs;
	स_नकल(ets->tc_tx_bw, dcbxcfg->etscfg.tcbwtable, माप(ets->tc_tx_bw));
	स_नकल(ets->tc_rx_bw, dcbxcfg->etscfg.tcbwtable, माप(ets->tc_rx_bw));
	स_नकल(ets->tc_tsa, dcbxcfg->etscfg.tsatable, माप(ets->tc_tsa));
	स_नकल(ets->prio_tc, dcbxcfg->etscfg.prio_table, माप(ets->prio_tc));
	स_नकल(ets->tc_reco_bw, dcbxcfg->etsrec.tcbwtable,
	       माप(ets->tc_reco_bw));
	स_नकल(ets->tc_reco_tsa, dcbxcfg->etsrec.tsatable,
	       माप(ets->tc_reco_tsa));
	स_नकल(ets->reco_prio_tc, dcbxcfg->etscfg.prio_table,
	       माप(ets->reco_prio_tc));

	वापस 0;
पूर्ण

/**
 * ice_dcbnl_setets - set IEEE ETS configuration
 * @netdev: poपूर्णांकer to relevant netdev
 * @ets: काष्ठा to hold ETS configuration
 */
अटल पूर्णांक ice_dcbnl_setets(काष्ठा net_device *netdev, काष्ठा ieee_ets *ets)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_dcbx_cfg *new_cfg;
	पूर्णांक bwcfg = 0, bwrec = 0;
	पूर्णांक err, i, max_tc = 0;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		वापस -EINVAL;

	new_cfg = &pf->hw.port_info->qos_cfg.desired_dcbx_cfg;

	mutex_lock(&pf->tc_mutex);

	new_cfg->etscfg.willing = ets->willing;
	new_cfg->etscfg.cbs = ets->cbs;
	ice_क्रम_each_traffic_class(i) अणु
		new_cfg->etscfg.tcbwtable[i] = ets->tc_tx_bw[i];
		bwcfg += ets->tc_tx_bw[i];
		new_cfg->etscfg.tsatable[i] = ets->tc_tsa[i];
		new_cfg->etscfg.prio_table[i] = ets->prio_tc[i];
		अगर (ets->prio_tc[i] > max_tc)
			max_tc = ets->prio_tc[i];
		new_cfg->etsrec.tcbwtable[i] = ets->tc_reco_bw[i];
		bwrec += ets->tc_reco_bw[i];
		new_cfg->etsrec.tsatable[i] = ets->tc_reco_tsa[i];
		new_cfg->etsrec.prio_table[i] = ets->reco_prio_tc[i];
	पूर्ण

	अगर (ice_dcb_bwchk(pf, new_cfg)) अणु
		err = -EINVAL;
		जाओ ets_out;
	पूर्ण

	max_tc = pf->hw.func_caps.common_cap.maxtc;

	new_cfg->etscfg.maxtcs = max_tc;

	अगर (!bwcfg)
		new_cfg->etscfg.tcbwtable[0] = 100;

	अगर (!bwrec)
		new_cfg->etsrec.tcbwtable[0] = 100;

	err = ice_pf_dcb_cfg(pf, new_cfg, true);
	/* वापस of zero indicates new cfg applied */
	अगर (err == ICE_DCB_HW_CHG_RST)
		ice_dcbnl_devreset(netdev);
	अगर (err == ICE_DCB_NO_HW_CHG)
		err = ICE_DCB_HW_CHG_RST;

ets_out:
	mutex_unlock(&pf->tc_mutex);
	वापस err;
पूर्ण

/**
 * ice_dcbnl_getnumtcs - Get max number of traffic classes supported
 * @dev: poपूर्णांकer to netdev काष्ठा
 * @tcid: TC ID
 * @num: total number of TCs supported by the adapter
 *
 * Return the total number of TCs supported
 */
अटल पूर्णांक
ice_dcbnl_getnumtcs(काष्ठा net_device *dev, पूर्णांक __always_unused tcid, u8 *num)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(dev);

	अगर (!test_bit(ICE_FLAG_DCB_CAPABLE, pf->flags))
		वापस -EINVAL;

	*num = pf->hw.func_caps.common_cap.maxtc;
	वापस 0;
पूर्ण

/**
 * ice_dcbnl_getdcbx - retrieve current DCBX capability
 * @netdev: poपूर्णांकer to the netdev काष्ठा
 */
अटल u8 ice_dcbnl_getdcbx(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);

	वापस pf->dcbx_cap;
पूर्ण

/**
 * ice_dcbnl_setdcbx - set required DCBX capability
 * @netdev: the corresponding netdev
 * @mode: required mode
 */
अटल u8 ice_dcbnl_setdcbx(काष्ठा net_device *netdev, u8 mode)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_qos_cfg *qos_cfg;

	/* अगर FW LLDP agent is running, DCBNL not allowed to change mode */
	अगर (test_bit(ICE_FLAG_FW_LLDP_AGENT, pf->flags))
		वापस ICE_DCB_NO_HW_CHG;

	/* No support क्रम LLD_MANAGED modes or CEE+IEEE */
	अगर ((mode & DCB_CAP_DCBX_LLD_MANAGED) ||
	    ((mode & DCB_CAP_DCBX_VER_IEEE) && (mode & DCB_CAP_DCBX_VER_CEE)) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		वापस ICE_DCB_NO_HW_CHG;

	/* Alपढ़ोy set to the given mode no change */
	अगर (mode == pf->dcbx_cap)
		वापस ICE_DCB_NO_HW_CHG;

	pf->dcbx_cap = mode;
	qos_cfg = &pf->hw.port_info->qos_cfg;
	अगर (mode & DCB_CAP_DCBX_VER_CEE)
		qos_cfg->local_dcbx_cfg.dcbx_mode = ICE_DCBX_MODE_CEE;
	अन्यथा
		qos_cfg->local_dcbx_cfg.dcbx_mode = ICE_DCBX_MODE_IEEE;

	dev_info(ice_pf_to_dev(pf), "DCBx mode = 0x%x\n", mode);
	वापस ICE_DCB_HW_CHG_RST;
पूर्ण

/**
 * ice_dcbnl_get_perm_hw_addr - MAC address used by DCBX
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @perm_addr: buffer to वापस permanent MAC address
 */
अटल व्योम ice_dcbnl_get_perm_hw_addr(काष्ठा net_device *netdev, u8 *perm_addr)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_port_info *pi = pf->hw.port_info;
	पूर्णांक i, j;

	स_रखो(perm_addr, 0xff, MAX_ADDR_LEN);

	क्रम (i = 0; i < netdev->addr_len; i++)
		perm_addr[i] = pi->mac.perm_addr[i];

	क्रम (j = 0; j < netdev->addr_len; j++, i++)
		perm_addr[i] = pi->mac.perm_addr[j];
पूर्ण

/**
 * ice_get_pfc_delay - Retrieve PFC Link Delay
 * @hw: poपूर्णांकer to HW काष्ठा
 * @delay: holds the PFC Link Delay value
 */
अटल व्योम ice_get_pfc_delay(काष्ठा ice_hw *hw, u16 *delay)
अणु
	u32 val;

	val = rd32(hw, PRTDCB_GENC);
	*delay = (u16)((val & PRTDCB_GENC_PFCLDA_M) >> PRTDCB_GENC_PFCLDA_S);
पूर्ण

/**
 * ice_dcbnl_getpfc - retrieve local IEEE PFC config
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @pfc: काष्ठा to hold PFC info
 */
अटल पूर्णांक ice_dcbnl_getpfc(काष्ठा net_device *netdev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_port_info *pi = pf->hw.port_info;
	काष्ठा ice_dcbx_cfg *dcbxcfg;
	पूर्णांक i;

	dcbxcfg = &pi->qos_cfg.local_dcbx_cfg;
	pfc->pfc_cap = dcbxcfg->pfc.pfccap;
	pfc->pfc_en = dcbxcfg->pfc.pfcena;
	pfc->mbc = dcbxcfg->pfc.mbc;
	ice_get_pfc_delay(&pf->hw, &pfc->delay);

	ice_क्रम_each_traffic_class(i) अणु
		pfc->requests[i] = pf->stats.priority_xoff_tx[i];
		pfc->indications[i] = pf->stats.priority_xoff_rx[i];
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_dcbnl_setpfc - set local IEEE PFC config
 * @netdev: poपूर्णांकer to relevant netdev
 * @pfc: poपूर्णांकer to काष्ठा holding PFC config
 */
अटल पूर्णांक ice_dcbnl_setpfc(काष्ठा net_device *netdev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_dcbx_cfg *new_cfg;
	पूर्णांक err;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		वापस -EINVAL;

	mutex_lock(&pf->tc_mutex);

	new_cfg = &pf->hw.port_info->qos_cfg.desired_dcbx_cfg;

	अगर (pfc->pfc_cap)
		new_cfg->pfc.pfccap = pfc->pfc_cap;
	अन्यथा
		new_cfg->pfc.pfccap = pf->hw.func_caps.common_cap.maxtc;

	new_cfg->pfc.pfcena = pfc->pfc_en;

	err = ice_pf_dcb_cfg(pf, new_cfg, true);
	अगर (err == ICE_DCB_HW_CHG_RST)
		ice_dcbnl_devreset(netdev);
	अगर (err == ICE_DCB_NO_HW_CHG)
		err = ICE_DCB_HW_CHG_RST;
	mutex_unlock(&pf->tc_mutex);
	वापस err;
पूर्ण

/**
 * ice_dcbnl_get_pfc_cfg - Get CEE PFC config
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @prio: corresponding user priority
 * @setting: the PFC setting क्रम given priority
 */
अटल व्योम
ice_dcbnl_get_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक prio, u8 *setting)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_port_info *pi = pf->hw.port_info;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस;

	अगर (prio >= ICE_MAX_USER_PRIORITY)
		वापस;

	*setting = (pi->qos_cfg.local_dcbx_cfg.pfc.pfcena >> prio) & 0x1;
	dev_dbg(ice_pf_to_dev(pf), "Get PFC Config up=%d, setting=%d, pfcenable=0x%x\n",
		prio, *setting, pi->qos_cfg.local_dcbx_cfg.pfc.pfcena);
पूर्ण

/**
 * ice_dcbnl_set_pfc_cfg - Set CEE PFC config
 * @netdev: the corresponding netdev
 * @prio: User Priority
 * @set: PFC setting to apply
 */
अटल व्योम ice_dcbnl_set_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक prio, u8 set)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_dcbx_cfg *new_cfg;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस;

	अगर (prio >= ICE_MAX_USER_PRIORITY)
		वापस;

	new_cfg = &pf->hw.port_info->qos_cfg.desired_dcbx_cfg;

	new_cfg->pfc.pfccap = pf->hw.func_caps.common_cap.maxtc;
	अगर (set)
		new_cfg->pfc.pfcena |= BIT(prio);
	अन्यथा
		new_cfg->pfc.pfcena &= ~BIT(prio);

	dev_dbg(ice_pf_to_dev(pf), "Set PFC config UP:%d set:%d pfcena:0x%x\n",
		prio, set, new_cfg->pfc.pfcena);
पूर्ण

/**
 * ice_dcbnl_getpfcstate - get CEE PFC mode
 * @netdev: poपूर्णांकer to netdev काष्ठा
 */
अटल u8 ice_dcbnl_getpfcstate(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_port_info *pi = pf->hw.port_info;

	/* Return enabled अगर any UP enabled क्रम PFC */
	अगर (pi->qos_cfg.local_dcbx_cfg.pfc.pfcena)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * ice_dcbnl_माला_लोtate - get DCB enabled state
 * @netdev: poपूर्णांकer to netdev काष्ठा
 */
अटल u8 ice_dcbnl_माला_लोtate(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	u8 state = 0;

	state = test_bit(ICE_FLAG_DCB_CAPABLE, pf->flags);

	dev_dbg(ice_pf_to_dev(pf), "DCB enabled state = %d\n", state);
	वापस state;
पूर्ण

/**
 * ice_dcbnl_setstate - Set CEE DCB state
 * @netdev: poपूर्णांकer to relevant netdev
 * @state: state value to set
 */
अटल u8 ice_dcbnl_setstate(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस ICE_DCB_NO_HW_CHG;

	/* Nothing to करो */
	अगर (!!state == test_bit(ICE_FLAG_DCB_ENA, pf->flags))
		वापस ICE_DCB_NO_HW_CHG;

	अगर (state) अणु
		set_bit(ICE_FLAG_DCB_ENA, pf->flags);
		स_नकल(&pf->hw.port_info->qos_cfg.desired_dcbx_cfg,
		       &pf->hw.port_info->qos_cfg.local_dcbx_cfg,
		       माप(काष्ठा ice_dcbx_cfg));
	पूर्ण अन्यथा अणु
		clear_bit(ICE_FLAG_DCB_ENA, pf->flags);
	पूर्ण

	वापस ICE_DCB_HW_CHG;
पूर्ण

/**
 * ice_dcbnl_get_pg_tc_cfg_tx - get CEE PG Tx config
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @prio: the corresponding user priority
 * @prio_type: traffic priority type
 * @pgid: the BW group ID the traffic class beदीर्घs to
 * @bw_pct: BW percentage क्रम the corresponding BWG
 * @up_map: prio mapped to corresponding TC
 */
अटल व्योम
ice_dcbnl_get_pg_tc_cfg_tx(काष्ठा net_device *netdev, पूर्णांक prio,
			   u8 __always_unused *prio_type, u8 *pgid,
			   u8 __always_unused *bw_pct,
			   u8 __always_unused *up_map)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_port_info *pi = pf->hw.port_info;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस;

	अगर (prio >= ICE_MAX_USER_PRIORITY)
		वापस;

	*pgid = pi->qos_cfg.local_dcbx_cfg.etscfg.prio_table[prio];
	dev_dbg(ice_pf_to_dev(pf), "Get PG config prio=%d tc=%d\n", prio,
		*pgid);
पूर्ण

/**
 * ice_dcbnl_set_pg_tc_cfg_tx - set CEE PG Tx config
 * @netdev: poपूर्णांकer to relevant netdev
 * @tc: the corresponding traffic class
 * @prio_type: the traffic priority type
 * @bwg_id: the BW group ID the TC beदीर्घs to
 * @bw_pct: the BW perventage क्रम the BWG
 * @up_map: prio mapped to corresponding TC
 */
अटल व्योम
ice_dcbnl_set_pg_tc_cfg_tx(काष्ठा net_device *netdev, पूर्णांक tc,
			   u8 __always_unused prio_type,
			   u8 __always_unused bwg_id,
			   u8 __always_unused bw_pct, u8 up_map)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_dcbx_cfg *new_cfg;
	पूर्णांक i;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस;

	अगर (tc >= ICE_MAX_TRAFFIC_CLASS)
		वापस;

	new_cfg = &pf->hw.port_info->qos_cfg.desired_dcbx_cfg;

	/* prio_type, bwg_id and bw_pct per UP are not supported */

	ice_क्रम_each_traffic_class(i) अणु
		अगर (up_map & BIT(i))
			new_cfg->etscfg.prio_table[i] = tc;
	पूर्ण
	new_cfg->etscfg.tsatable[tc] = ICE_IEEE_TSA_ETS;
पूर्ण

/**
 * ice_dcbnl_get_pg_bwg_cfg_tx - Get CEE PGBW config
 * @netdev: poपूर्णांकer to the netdev काष्ठा
 * @pgid: corresponding traffic class
 * @bw_pct: the BW percentage क्रम the corresponding TC
 */
अटल व्योम
ice_dcbnl_get_pg_bwg_cfg_tx(काष्ठा net_device *netdev, पूर्णांक pgid, u8 *bw_pct)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_port_info *pi = pf->hw.port_info;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस;

	अगर (pgid >= ICE_MAX_TRAFFIC_CLASS)
		वापस;

	*bw_pct = pi->qos_cfg.local_dcbx_cfg.etscfg.tcbwtable[pgid];
	dev_dbg(ice_pf_to_dev(pf), "Get PG BW config tc=%d bw_pct=%d\n",
		pgid, *bw_pct);
पूर्ण

/**
 * ice_dcbnl_set_pg_bwg_cfg_tx - set CEE PG Tx BW config
 * @netdev: the corresponding netdev
 * @pgid: Correspongind traffic class
 * @bw_pct: the BW percentage क्रम the specअगरied TC
 */
अटल व्योम
ice_dcbnl_set_pg_bwg_cfg_tx(काष्ठा net_device *netdev, पूर्णांक pgid, u8 bw_pct)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_dcbx_cfg *new_cfg;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस;

	अगर (pgid >= ICE_MAX_TRAFFIC_CLASS)
		वापस;

	new_cfg = &pf->hw.port_info->qos_cfg.desired_dcbx_cfg;

	new_cfg->etscfg.tcbwtable[pgid] = bw_pct;
पूर्ण

/**
 * ice_dcbnl_get_pg_tc_cfg_rx - Get CEE PG Rx config
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @prio: the corresponding user priority
 * @prio_type: the traffic priority type
 * @pgid: the PG ID
 * @bw_pct: the BW percentage क्रम the corresponding BWG
 * @up_map: prio mapped to corresponding TC
 */
अटल व्योम
ice_dcbnl_get_pg_tc_cfg_rx(काष्ठा net_device *netdev, पूर्णांक prio,
			   u8 __always_unused *prio_type, u8 *pgid,
			   u8 __always_unused *bw_pct,
			   u8 __always_unused *up_map)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_port_info *pi = pf->hw.port_info;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस;

	अगर (prio >= ICE_MAX_USER_PRIORITY)
		वापस;

	*pgid = pi->qos_cfg.local_dcbx_cfg.etscfg.prio_table[prio];
पूर्ण

/**
 * ice_dcbnl_set_pg_tc_cfg_rx
 * @netdev: relevant netdev काष्ठा
 * @prio: corresponding user priority
 * @prio_type: the traffic priority type
 * @pgid: the PG ID
 * @bw_pct: BW percentage क्रम corresponding BWG
 * @up_map: prio mapped to corresponding TC
 *
 * lldpad requires this function poपूर्णांकer to be non-शून्य to complete CEE config.
 */
अटल व्योम
ice_dcbnl_set_pg_tc_cfg_rx(काष्ठा net_device *netdev,
			   पूर्णांक __always_unused prio,
			   u8 __always_unused prio_type,
			   u8 __always_unused pgid,
			   u8 __always_unused bw_pct,
			   u8 __always_unused up_map)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);

	dev_dbg(ice_pf_to_dev(pf), "Rx TC PG Config Not Supported.\n");
पूर्ण

/**
 * ice_dcbnl_get_pg_bwg_cfg_rx - Get CEE PG BW Rx config
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @pgid: the corresponding traffic class
 * @bw_pct: the BW percentage क्रम the corresponding TC
 */
अटल व्योम
ice_dcbnl_get_pg_bwg_cfg_rx(काष्ठा net_device *netdev, पूर्णांक __always_unused pgid,
			    u8 *bw_pct)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस;

	*bw_pct = 0;
पूर्ण

/**
 * ice_dcbnl_set_pg_bwg_cfg_rx
 * @netdev: the corresponding netdev
 * @pgid: corresponding TC
 * @bw_pct: BW percentage क्रम given TC
 *
 * lldpad requires this function poपूर्णांकer to be non-शून्य to complete CEE config.
 */
अटल व्योम
ice_dcbnl_set_pg_bwg_cfg_rx(काष्ठा net_device *netdev, पूर्णांक __always_unused pgid,
			    u8 __always_unused bw_pct)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);

	dev_dbg(ice_pf_to_dev(pf), "Rx BWG PG Config Not Supported.\n");
पूर्ण

/**
 * ice_dcbnl_get_cap - Get DCBX capabilities of adapter
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @capid: the capability type
 * @cap: the capability value
 */
अटल u8 ice_dcbnl_get_cap(काष्ठा net_device *netdev, पूर्णांक capid, u8 *cap)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);

	अगर (!(test_bit(ICE_FLAG_DCB_CAPABLE, pf->flags)))
		वापस ICE_DCB_NO_HW_CHG;

	चयन (capid) अणु
	हाल DCB_CAP_ATTR_PG:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_PFC:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_UP2TC:
		*cap = false;
		अवरोध;
	हाल DCB_CAP_ATTR_PG_TCS:
		*cap = 0x80;
		अवरोध;
	हाल DCB_CAP_ATTR_PFC_TCS:
		*cap = 0x80;
		अवरोध;
	हाल DCB_CAP_ATTR_GSP:
		*cap = false;
		अवरोध;
	हाल DCB_CAP_ATTR_BCN:
		*cap = false;
		अवरोध;
	हाल DCB_CAP_ATTR_DCBX:
		*cap = pf->dcbx_cap;
		अवरोध;
	शेष:
		*cap = false;
		अवरोध;
	पूर्ण

	dev_dbg(ice_pf_to_dev(pf), "DCBX Get Capability cap=%d capval=0x%x\n",
		capid, *cap);
	वापस 0;
पूर्ण

/**
 * ice_dcbnl_getapp - get CEE APP
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @idtype: the App selector
 * @id: the App ethtype or port number
 */
अटल पूर्णांक ice_dcbnl_getapp(काष्ठा net_device *netdev, u8 idtype, u16 id)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा dcb_app app = अणु
				.selector = idtype,
				.protocol = id,
			     पूर्ण;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस -EINVAL;

	वापस dcb_getapp(netdev, &app);
पूर्ण

/**
 * ice_dcbnl_find_app - Search क्रम APP in given DCB config
 * @cfg: काष्ठा to hold DCBX config
 * @app: काष्ठा to hold app data to look क्रम
 */
अटल bool
ice_dcbnl_find_app(काष्ठा ice_dcbx_cfg *cfg,
		   काष्ठा ice_dcb_app_priority_table *app)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cfg->numapps; i++) अणु
		अगर (app->selector == cfg->app[i].selector &&
		    app->prot_id == cfg->app[i].prot_id &&
		    app->priority == cfg->app[i].priority)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ice_dcbnl_setapp - set local IEEE App config
 * @netdev: relevant netdev काष्ठा
 * @app: काष्ठा to hold app config info
 */
अटल पूर्णांक ice_dcbnl_setapp(काष्ठा net_device *netdev, काष्ठा dcb_app *app)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_dcb_app_priority_table new_app;
	काष्ठा ice_dcbx_cfg *old_cfg, *new_cfg;
	पूर्णांक ret;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_IEEE))
		वापस -EINVAL;

	mutex_lock(&pf->tc_mutex);

	new_cfg = &pf->hw.port_info->qos_cfg.desired_dcbx_cfg;

	old_cfg = &pf->hw.port_info->qos_cfg.local_dcbx_cfg;

	अगर (old_cfg->numapps == ICE_DCBX_MAX_APPS) अणु
		ret = -EINVAL;
		जाओ setapp_out;
	पूर्ण

	ret = dcb_ieee_setapp(netdev, app);
	अगर (ret)
		जाओ setapp_out;

	new_app.selector = app->selector;
	new_app.prot_id = app->protocol;
	new_app.priority = app->priority;
	अगर (ice_dcbnl_find_app(old_cfg, &new_app)) अणु
		ret = 0;
		जाओ setapp_out;
	पूर्ण

	new_cfg->app[new_cfg->numapps++] = new_app;
	ret = ice_pf_dcb_cfg(pf, new_cfg, true);
	/* वापस of zero indicates new cfg applied */
	अगर (ret == ICE_DCB_HW_CHG_RST)
		ice_dcbnl_devreset(netdev);
	अगर (ret == ICE_DCB_NO_HW_CHG)
		ret = ICE_DCB_HW_CHG_RST;

setapp_out:
	mutex_unlock(&pf->tc_mutex);
	वापस ret;
पूर्ण

/**
 * ice_dcbnl_delapp - Delete local IEEE App config
 * @netdev: relevant netdev
 * @app: काष्ठा to hold app too delete
 *
 * Will not delete first application required by the FW
 */
अटल पूर्णांक ice_dcbnl_delapp(काष्ठा net_device *netdev, काष्ठा dcb_app *app)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_dcbx_cfg *old_cfg, *new_cfg;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret = 0;

	अगर (pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED)
		वापस -EINVAL;

	mutex_lock(&pf->tc_mutex);
	old_cfg = &pf->hw.port_info->qos_cfg.local_dcbx_cfg;

	अगर (old_cfg->numapps <= 1)
		जाओ delapp_out;

	ret = dcb_ieee_delapp(netdev, app);
	अगर (ret)
		जाओ delapp_out;

	new_cfg = &pf->hw.port_info->qos_cfg.desired_dcbx_cfg;

	क्रम (i = 1; i < new_cfg->numapps; i++) अणु
		अगर (app->selector == new_cfg->app[i].selector &&
		    app->protocol == new_cfg->app[i].prot_id &&
		    app->priority == new_cfg->app[i].priority) अणु
			new_cfg->app[i].selector = 0;
			new_cfg->app[i].prot_id = 0;
			new_cfg->app[i].priority = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Did not find DCB App */
	अगर (i == new_cfg->numapps) अणु
		ret = -EINVAL;
		जाओ delapp_out;
	पूर्ण

	new_cfg->numapps--;

	क्रम (j = i; j < new_cfg->numapps; j++) अणु
		new_cfg->app[i].selector = old_cfg->app[j + 1].selector;
		new_cfg->app[i].prot_id = old_cfg->app[j + 1].prot_id;
		new_cfg->app[i].priority = old_cfg->app[j + 1].priority;
	पूर्ण

	ret = ice_pf_dcb_cfg(pf, new_cfg, true);
	/* वापस of zero indicates new cfg applied */
	अगर (ret == ICE_DCB_HW_CHG_RST)
		ice_dcbnl_devreset(netdev);
	अगर (ret == ICE_DCB_NO_HW_CHG)
		ret = ICE_DCB_HW_CHG_RST;

delapp_out:
	mutex_unlock(&pf->tc_mutex);
	वापस ret;
पूर्ण

/**
 * ice_dcbnl_cee_set_all - Commit CEE DCB settings to HW
 * @netdev: the corresponding netdev
 */
अटल u8 ice_dcbnl_cee_set_all(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_pf *pf = ice_netdev_to_pf(netdev);
	काष्ठा ice_dcbx_cfg *new_cfg;
	पूर्णांक err;

	अगर ((pf->dcbx_cap & DCB_CAP_DCBX_LLD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		वापस ICE_DCB_NO_HW_CHG;

	new_cfg = &pf->hw.port_info->qos_cfg.desired_dcbx_cfg;

	mutex_lock(&pf->tc_mutex);

	err = ice_pf_dcb_cfg(pf, new_cfg, true);

	mutex_unlock(&pf->tc_mutex);
	वापस (err != ICE_DCB_HW_CHG_RST) ? ICE_DCB_NO_HW_CHG : err;
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops dcbnl_ops = अणु
	/* IEEE 802.1Qaz std */
	.ieee_getets = ice_dcbnl_getets,
	.ieee_setets = ice_dcbnl_setets,
	.ieee_getpfc = ice_dcbnl_getpfc,
	.ieee_setpfc = ice_dcbnl_setpfc,
	.ieee_setapp = ice_dcbnl_setapp,
	.ieee_delapp = ice_dcbnl_delapp,

	/* CEE std */
	.माला_लोtate = ice_dcbnl_माला_लोtate,
	.setstate = ice_dcbnl_setstate,
	.getpermhwaddr = ice_dcbnl_get_perm_hw_addr,
	.setpgtccfgtx = ice_dcbnl_set_pg_tc_cfg_tx,
	.setpgbwgcfgtx = ice_dcbnl_set_pg_bwg_cfg_tx,
	.setpgtccfgrx = ice_dcbnl_set_pg_tc_cfg_rx,
	.setpgbwgcfgrx = ice_dcbnl_set_pg_bwg_cfg_rx,
	.getpgtccfgtx = ice_dcbnl_get_pg_tc_cfg_tx,
	.getpgbwgcfgtx = ice_dcbnl_get_pg_bwg_cfg_tx,
	.getpgtccfgrx = ice_dcbnl_get_pg_tc_cfg_rx,
	.getpgbwgcfgrx = ice_dcbnl_get_pg_bwg_cfg_rx,
	.setpfccfg = ice_dcbnl_set_pfc_cfg,
	.getpfccfg = ice_dcbnl_get_pfc_cfg,
	.setall = ice_dcbnl_cee_set_all,
	.अ_लोap = ice_dcbnl_get_cap,
	.getnumtcs = ice_dcbnl_getnumtcs,
	.getpfcstate = ice_dcbnl_getpfcstate,
	.getapp = ice_dcbnl_getapp,

	/* DCBX configuration */
	.getdcbx = ice_dcbnl_getdcbx,
	.setdcbx = ice_dcbnl_setdcbx,
पूर्ण;

/**
 * ice_dcbnl_set_all - set all the apps and ieee data from DCBX config
 * @vsi: poपूर्णांकer to VSI काष्ठा
 */
व्योम ice_dcbnl_set_all(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा net_device *netdev = vsi->netdev;
	काष्ठा ice_dcbx_cfg *dcbxcfg;
	काष्ठा ice_port_info *pi;
	काष्ठा dcb_app sapp;
	काष्ठा ice_pf *pf;
	अचिन्हित पूर्णांक i;

	अगर (!netdev)
		वापस;

	pf = ice_netdev_to_pf(netdev);
	pi = pf->hw.port_info;

	/* SW DCB taken care of by SW Default Config */
	अगर (pf->dcbx_cap & DCB_CAP_DCBX_HOST)
		वापस;

	/* DCB not enabled */
	अगर (!test_bit(ICE_FLAG_DCB_ENA, pf->flags))
		वापस;

	dcbxcfg = &pi->qos_cfg.local_dcbx_cfg;

	क्रम (i = 0; i < dcbxcfg->numapps; i++) अणु
		u8 prio, tc_map;

		prio = dcbxcfg->app[i].priority;
		tc_map = BIT(dcbxcfg->etscfg.prio_table[prio]);

		/* Add APP only अगर the TC is enabled क्रम this VSI */
		अगर (tc_map & vsi->tc_cfg.ena_tc) अणु
			sapp.selector = dcbxcfg->app[i].selector;
			sapp.protocol = dcbxcfg->app[i].prot_id;
			sapp.priority = prio;
			dcb_ieee_setapp(netdev, &sapp);
		पूर्ण
	पूर्ण
	/* Notअगरy user-space of the changes */
	dcbnl_ieee_notअगरy(netdev, RTM_SETDCB, DCB_CMD_IEEE_SET, 0, 0);
पूर्ण

/**
 * ice_dcbnl_vsi_del_app - Delete APP on all VSIs
 * @vsi: poपूर्णांकer to the मुख्य VSI
 * @app: APP to delete
 *
 * Delete given APP from all the VSIs क्रम given PF
 */
अटल व्योम
ice_dcbnl_vsi_del_app(काष्ठा ice_vsi *vsi,
		      काष्ठा ice_dcb_app_priority_table *app)
अणु
	काष्ठा dcb_app sapp;
	पूर्णांक err;

	sapp.selector = app->selector;
	sapp.protocol = app->prot_id;
	sapp.priority = app->priority;
	err = ice_dcbnl_delapp(vsi->netdev, &sapp);
	dev_dbg(ice_pf_to_dev(vsi->back), "Deleting app for VSI idx=%d err=%d sel=%d proto=0x%x, prio=%d\n",
		vsi->idx, err, app->selector, app->prot_id, app->priority);
पूर्ण

/**
 * ice_dcbnl_flush_apps - Delete all हटाओd APPs
 * @pf: the corresponding PF
 * @old_cfg: old DCBX configuration data
 * @new_cfg: new DCBX configuration data
 *
 * Find and delete all APPS that are not present in the passed
 * DCB configuration
 */
व्योम
ice_dcbnl_flush_apps(काष्ठा ice_pf *pf, काष्ठा ice_dcbx_cfg *old_cfg,
		     काष्ठा ice_dcbx_cfg *new_cfg)
अणु
	काष्ठा ice_vsi *मुख्य_vsi = ice_get_मुख्य_vsi(pf);
	अचिन्हित पूर्णांक i;

	अगर (!मुख्य_vsi)
		वापस;

	क्रम (i = 0; i < old_cfg->numapps; i++) अणु
		काष्ठा ice_dcb_app_priority_table app = old_cfg->app[i];

		/* The APP is not available anymore delete it */
		अगर (!ice_dcbnl_find_app(new_cfg, &app))
			ice_dcbnl_vsi_del_app(मुख्य_vsi, &app);
	पूर्ण
पूर्ण

/**
 * ice_dcbnl_setup - setup DCBNL
 * @vsi: VSI to get associated netdev from
 */
व्योम ice_dcbnl_setup(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा net_device *netdev = vsi->netdev;
	काष्ठा ice_pf *pf;

	pf = ice_netdev_to_pf(netdev);
	अगर (!test_bit(ICE_FLAG_DCB_CAPABLE, pf->flags))
		वापस;

	netdev->dcbnl_ops = &dcbnl_ops;
	ice_dcbnl_set_all(vsi);
पूर्ण
