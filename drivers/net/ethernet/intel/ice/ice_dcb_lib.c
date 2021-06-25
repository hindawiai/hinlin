<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Intel Corporation. */

#समावेश "ice_dcb_lib.h"
#समावेश "ice_dcb_nl.h"

/**
 * ice_vsi_cfg_netdev_tc - Setup the netdev TC configuration
 * @vsi: the VSI being configured
 * @ena_tc: TC map to be enabled
 */
व्योम ice_vsi_cfg_netdev_tc(काष्ठा ice_vsi *vsi, u8 ena_tc)
अणु
	काष्ठा net_device *netdev = vsi->netdev;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_dcbx_cfg *dcbcfg;
	u8 netdev_tc;
	पूर्णांक i;

	अगर (!netdev)
		वापस;

	अगर (!ena_tc) अणु
		netdev_reset_tc(netdev);
		वापस;
	पूर्ण

	अगर (netdev_set_num_tc(netdev, vsi->tc_cfg.numtc))
		वापस;

	dcbcfg = &pf->hw.port_info->qos_cfg.local_dcbx_cfg;

	ice_क्रम_each_traffic_class(i)
		अगर (vsi->tc_cfg.ena_tc & BIT(i))
			netdev_set_tc_queue(netdev,
					    vsi->tc_cfg.tc_info[i].netdev_tc,
					    vsi->tc_cfg.tc_info[i].qcount_tx,
					    vsi->tc_cfg.tc_info[i].qoffset);

	क्रम (i = 0; i < ICE_MAX_USER_PRIORITY; i++) अणु
		u8 ets_tc = dcbcfg->etscfg.prio_table[i];

		/* Get the mapped netdev TC# क्रम the UP */
		netdev_tc = vsi->tc_cfg.tc_info[ets_tc].netdev_tc;
		netdev_set_prio_tc_map(netdev, i, netdev_tc);
	पूर्ण
पूर्ण

/**
 * ice_dcb_get_ena_tc - वापस biपंचांगap of enabled TCs
 * @dcbcfg: DCB config to evaluate क्रम enabled TCs
 */
u8 ice_dcb_get_ena_tc(काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	u8 i, num_tc, ena_tc = 1;

	num_tc = ice_dcb_get_num_tc(dcbcfg);

	क्रम (i = 0; i < num_tc; i++)
		ena_tc |= BIT(i);

	वापस ena_tc;
पूर्ण

/**
 * ice_is_pfc_causing_hung_q
 * @pf: poपूर्णांकer to PF काष्ठाure
 * @txqueue: Tx queue which is supposedly hung queue
 *
 * find अगर PFC is causing the hung queue, अगर yes वापस true अन्यथा false
 */
bool ice_is_pfc_causing_hung_q(काष्ठा ice_pf *pf, अचिन्हित पूर्णांक txqueue)
अणु
	u8 num_tcs = 0, i, tc, up_mapped_tc, up_in_tc = 0;
	u64 ref_prio_xoff[ICE_MAX_UP];
	काष्ठा ice_vsi *vsi;
	u32 up2tc;

	vsi = ice_get_मुख्य_vsi(pf);
	अगर (!vsi)
		वापस false;

	ice_क्रम_each_traffic_class(i)
		अगर (vsi->tc_cfg.ena_tc & BIT(i))
			num_tcs++;

	/* first find out the TC to which the hung queue beदीर्घs to */
	क्रम (tc = 0; tc < num_tcs - 1; tc++)
		अगर (ice_find_q_in_range(vsi->tc_cfg.tc_info[tc].qoffset,
					vsi->tc_cfg.tc_info[tc + 1].qoffset,
					txqueue))
			अवरोध;

	/* Build a bit map of all UPs associated to the suspect hung queue TC,
	 * so that we check क्रम its counter increment.
	 */
	up2tc = rd32(&pf->hw, PRTDCB_TUP2TC);
	क्रम (i = 0; i < ICE_MAX_UP; i++) अणु
		up_mapped_tc = (up2tc >> (i * 3)) & 0x7;
		अगर (up_mapped_tc == tc)
			up_in_tc |= BIT(i);
	पूर्ण

	/* Now that we figured out that hung queue is PFC enabled, still the
	 * Tx समयout can be legitimate. So to make sure Tx समयout is
	 * असलolutely caused by PFC storm, check अगर the counters are
	 * incrementing.
	 */
	क्रम (i = 0; i < ICE_MAX_UP; i++)
		अगर (up_in_tc & BIT(i))
			ref_prio_xoff[i] = pf->stats.priority_xoff_rx[i];

	ice_update_dcb_stats(pf);

	क्रम (i = 0; i < ICE_MAX_UP; i++)
		अगर (up_in_tc & BIT(i))
			अगर (pf->stats.priority_xoff_rx[i] > ref_prio_xoff[i])
				वापस true;

	वापस false;
पूर्ण

/**
 * ice_dcb_get_mode - माला_लो the DCB mode
 * @port_info: poपूर्णांकer to port info काष्ठाure
 * @host: अगर set it's HOST if not it's MANAGED
 */
अटल u8 ice_dcb_get_mode(काष्ठा ice_port_info *port_info, bool host)
अणु
	u8 mode;

	अगर (host)
		mode = DCB_CAP_DCBX_HOST;
	अन्यथा
		mode = DCB_CAP_DCBX_LLD_MANAGED;

	अगर (port_info->qos_cfg.local_dcbx_cfg.dcbx_mode & ICE_DCBX_MODE_CEE)
		वापस mode | DCB_CAP_DCBX_VER_CEE;
	अन्यथा
		वापस mode | DCB_CAP_DCBX_VER_IEEE;
पूर्ण

/**
 * ice_dcb_get_num_tc - Get the number of TCs from DCBX config
 * @dcbcfg: config to retrieve number of TCs from
 */
u8 ice_dcb_get_num_tc(काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	bool tc_unused = false;
	u8 num_tc = 0;
	u8 ret = 0;
	पूर्णांक i;

	/* Scan the ETS Config Priority Table to find traffic classes
	 * enabled and create a biपंचांगask of enabled TCs
	 */
	क्रम (i = 0; i < CEE_DCBX_MAX_PRIO; i++)
		num_tc |= BIT(dcbcfg->etscfg.prio_table[i]);

	/* Scan biपंचांगask क्रम contiguous TCs starting with TC0 */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		अगर (num_tc & BIT(i)) अणु
			अगर (!tc_unused) अणु
				ret++;
			पूर्ण अन्यथा अणु
				pr_err("Non-contiguous TCs - Disabling DCB\n");
				वापस 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			tc_unused = true;
		पूर्ण
	पूर्ण

	/* There is always at least 1 TC */
	अगर (!ret)
		ret = 1;

	वापस ret;
पूर्ण

/**
 * ice_dcb_get_tc - Get the TC associated with the queue
 * @vsi: ptr to the VSI
 * @queue_index: queue number associated with VSI
 */
u8 ice_dcb_get_tc(काष्ठा ice_vsi *vsi, पूर्णांक queue_index)
अणु
	वापस vsi->tx_rings[queue_index]->dcb_tc;
पूर्ण

/**
 * ice_vsi_cfg_dcb_rings - Update rings to reflect DCB TC
 * @vsi: VSI owner of rings being updated
 */
व्योम ice_vsi_cfg_dcb_rings(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा ice_ring *tx_ring, *rx_ring;
	u16 qoffset, qcount;
	पूर्णांक i, n;

	अगर (!test_bit(ICE_FLAG_DCB_ENA, vsi->back->flags)) अणु
		/* Reset the TC inक्रमmation */
		क्रम (i = 0; i < vsi->num_txq; i++) अणु
			tx_ring = vsi->tx_rings[i];
			tx_ring->dcb_tc = 0;
		पूर्ण
		क्रम (i = 0; i < vsi->num_rxq; i++) अणु
			rx_ring = vsi->rx_rings[i];
			rx_ring->dcb_tc = 0;
		पूर्ण
		वापस;
	पूर्ण

	ice_क्रम_each_traffic_class(n) अणु
		अगर (!(vsi->tc_cfg.ena_tc & BIT(n)))
			अवरोध;

		qoffset = vsi->tc_cfg.tc_info[n].qoffset;
		qcount = vsi->tc_cfg.tc_info[n].qcount_tx;
		क्रम (i = qoffset; i < (qoffset + qcount); i++) अणु
			tx_ring = vsi->tx_rings[i];
			rx_ring = vsi->rx_rings[i];
			tx_ring->dcb_tc = n;
			rx_ring->dcb_tc = n;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_dcb_bwchk - check अगर ETS bandwidth input parameters are correct
 * @pf: poपूर्णांकer to the PF काष्ठा
 * @dcbcfg: poपूर्णांकer to DCB config काष्ठाure
 */
पूर्णांक ice_dcb_bwchk(काष्ठा ice_pf *pf, काष्ठा ice_dcbx_cfg *dcbcfg)
अणु
	काष्ठा ice_dcb_ets_cfg *etscfg = &dcbcfg->etscfg;
	u8 num_tc, total_bw = 0;
	पूर्णांक i;

	/* वापसs number of contigous TCs and 1 TC क्रम non-contigous TCs,
	 * since at least 1 TC has to be configured
	 */
	num_tc = ice_dcb_get_num_tc(dcbcfg);

	/* no bandwidth checks required अगर there's only one TC, so assign
	 * all bandwidth to TC0 and वापस
	 */
	अगर (num_tc == 1) अणु
		etscfg->tcbwtable[0] = ICE_TC_MAX_BW;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < num_tc; i++)
		total_bw += etscfg->tcbwtable[i];

	अगर (!total_bw) अणु
		etscfg->tcbwtable[0] = ICE_TC_MAX_BW;
	पूर्ण अन्यथा अगर (total_bw != ICE_TC_MAX_BW) अणु
		dev_err(ice_pf_to_dev(pf), "Invalid config, total bandwidth must equal 100\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_pf_dcb_cfg - Apply new DCB configuration
 * @pf: poपूर्णांकer to the PF काष्ठा
 * @new_cfg: DCBX config to apply
 * @locked: is the RTNL held
 */
पूर्णांक ice_pf_dcb_cfg(काष्ठा ice_pf *pf, काष्ठा ice_dcbx_cfg *new_cfg, bool locked)
अणु
	काष्ठा ice_aqc_port_ets_elem buf = अणु 0 पूर्ण;
	काष्ठा ice_dcbx_cfg *old_cfg, *curr_cfg;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	पूर्णांक ret = ICE_DCB_NO_HW_CHG;
	काष्ठा ice_vsi *pf_vsi;

	curr_cfg = &pf->hw.port_info->qos_cfg.local_dcbx_cfg;

	/* FW करोes not care अगर change happened */
	अगर (!pf->hw.port_info->qos_cfg.is_sw_lldp)
		ret = ICE_DCB_HW_CHG_RST;

	/* Enable DCB tagging only when more than one TC */
	अगर (ice_dcb_get_num_tc(new_cfg) > 1) अणु
		dev_dbg(dev, "DCB tagging enabled (num TC > 1)\n");
		set_bit(ICE_FLAG_DCB_ENA, pf->flags);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "DCB tagging disabled (num TC = 1)\n");
		clear_bit(ICE_FLAG_DCB_ENA, pf->flags);
	पूर्ण

	अगर (!स_भेद(new_cfg, curr_cfg, माप(*new_cfg))) अणु
		dev_dbg(dev, "No change in DCB config required\n");
		वापस ret;
	पूर्ण

	अगर (ice_dcb_bwchk(pf, new_cfg))
		वापस -EINVAL;

	/* Store old config in हाल FW config fails */
	old_cfg = kmemdup(curr_cfg, माप(*old_cfg), GFP_KERNEL);
	अगर (!old_cfg)
		वापस -ENOMEM;

	dev_info(dev, "Commit DCB Configuration to the hardware\n");
	pf_vsi = ice_get_मुख्य_vsi(pf);
	अगर (!pf_vsi) अणु
		dev_dbg(dev, "PF VSI doesn't exist\n");
		ret = -EINVAL;
		जाओ मुक्त_cfg;
	पूर्ण

	/* aव्योम race conditions by holding the lock जबतक disabling and
	 * re-enabling the VSI
	 */
	अगर (!locked)
		rtnl_lock();
	ice_dis_vsi(pf_vsi, true);

	स_नकल(curr_cfg, new_cfg, माप(*curr_cfg));
	स_नकल(&curr_cfg->etsrec, &curr_cfg->etscfg, माप(curr_cfg->etsrec));
	स_नकल(&new_cfg->etsrec, &curr_cfg->etscfg, माप(curr_cfg->etsrec));

	/* Only send new config to HW अगर we are in SW LLDP mode. Otherwise,
	 * the new config came from the HW in the first place.
	 */
	अगर (pf->hw.port_info->qos_cfg.is_sw_lldp) अणु
		ret = ice_set_dcb_cfg(pf->hw.port_info);
		अगर (ret) अणु
			dev_err(dev, "Set DCB Config failed\n");
			/* Restore previous settings to local config */
			स_नकल(curr_cfg, old_cfg, माप(*curr_cfg));
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ice_query_port_ets(pf->hw.port_info, &buf, माप(buf), शून्य);
	अगर (ret) अणु
		dev_err(dev, "Query Port ETS failed\n");
		जाओ out;
	पूर्ण

	ice_pf_dcb_recfg(pf);

out:
	ice_ena_vsi(pf_vsi, true);
	अगर (!locked)
		rtnl_unlock();
मुक्त_cfg:
	kमुक्त(old_cfg);
	वापस ret;
पूर्ण

/**
 * ice_cfg_etsrec_शेषs - Set शेष ETS recommended DCB config
 * @pi: port inक्रमmation काष्ठाure
 */
अटल व्योम ice_cfg_etsrec_शेषs(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_dcbx_cfg *dcbcfg = &pi->qos_cfg.local_dcbx_cfg;
	u8 i;

	/* Ensure ETS recommended DCB configuration is not alपढ़ोy set */
	अगर (dcbcfg->etsrec.maxtcs)
		वापस;

	/* In CEE mode, set the शेष to 1 TC */
	dcbcfg->etsrec.maxtcs = 1;
	क्रम (i = 0; i < ICE_MAX_TRAFFIC_CLASS; i++) अणु
		dcbcfg->etsrec.tcbwtable[i] = i ? 0 : 100;
		dcbcfg->etsrec.tsatable[i] = i ? ICE_IEEE_TSA_STRICT :
						 ICE_IEEE_TSA_ETS;
	पूर्ण
पूर्ण

/**
 * ice_dcb_need_recfg - Check अगर DCB needs reconfig
 * @pf: board निजी काष्ठाure
 * @old_cfg: current DCB config
 * @new_cfg: new DCB config
 */
अटल bool
ice_dcb_need_recfg(काष्ठा ice_pf *pf, काष्ठा ice_dcbx_cfg *old_cfg,
		   काष्ठा ice_dcbx_cfg *new_cfg)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	bool need_reconfig = false;

	/* Check अगर ETS configuration has changed */
	अगर (स_भेद(&new_cfg->etscfg, &old_cfg->etscfg,
		   माप(new_cfg->etscfg))) अणु
		/* If Priority Table has changed reconfig is needed */
		अगर (स_भेद(&new_cfg->etscfg.prio_table,
			   &old_cfg->etscfg.prio_table,
			   माप(new_cfg->etscfg.prio_table))) अणु
			need_reconfig = true;
			dev_dbg(dev, "ETS UP2TC changed.\n");
		पूर्ण

		अगर (स_भेद(&new_cfg->etscfg.tcbwtable,
			   &old_cfg->etscfg.tcbwtable,
			   माप(new_cfg->etscfg.tcbwtable)))
			dev_dbg(dev, "ETS TC BW Table changed.\n");

		अगर (स_भेद(&new_cfg->etscfg.tsatable,
			   &old_cfg->etscfg.tsatable,
			   माप(new_cfg->etscfg.tsatable)))
			dev_dbg(dev, "ETS TSA Table changed.\n");
	पूर्ण

	/* Check अगर PFC configuration has changed */
	अगर (स_भेद(&new_cfg->pfc, &old_cfg->pfc, माप(new_cfg->pfc))) अणु
		need_reconfig = true;
		dev_dbg(dev, "PFC config change detected.\n");
	पूर्ण

	/* Check अगर APP Table has changed */
	अगर (स_भेद(&new_cfg->app, &old_cfg->app, माप(new_cfg->app))) अणु
		need_reconfig = true;
		dev_dbg(dev, "APP Table change detected.\n");
	पूर्ण

	dev_dbg(dev, "dcb need_reconfig=%d\n", need_reconfig);
	वापस need_reconfig;
पूर्ण

/**
 * ice_dcb_rebuild - rebuild DCB post reset
 * @pf: physical function instance
 */
व्योम ice_dcb_rebuild(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_aqc_port_ets_elem buf = अणु 0 पूर्ण;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_dcbx_cfg *err_cfg;
	क्रमागत ice_status ret;

	ret = ice_query_port_ets(pf->hw.port_info, &buf, माप(buf), शून्य);
	अगर (ret) अणु
		dev_err(dev, "Query Port ETS failed\n");
		जाओ dcb_error;
	पूर्ण

	mutex_lock(&pf->tc_mutex);

	अगर (!pf->hw.port_info->qos_cfg.is_sw_lldp)
		ice_cfg_etsrec_शेषs(pf->hw.port_info);

	ret = ice_set_dcb_cfg(pf->hw.port_info);
	अगर (ret) अणु
		dev_err(dev, "Failed to set DCB config in rebuild\n");
		जाओ dcb_error;
	पूर्ण

	अगर (!pf->hw.port_info->qos_cfg.is_sw_lldp) अणु
		ret = ice_cfg_lldp_mib_change(&pf->hw, true);
		अगर (ret && !pf->hw.port_info->qos_cfg.is_sw_lldp) अणु
			dev_err(dev, "Failed to register for MIB changes\n");
			जाओ dcb_error;
		पूर्ण
	पूर्ण

	dev_info(dev, "DCB info restored\n");
	ret = ice_query_port_ets(pf->hw.port_info, &buf, माप(buf), शून्य);
	अगर (ret) अणु
		dev_err(dev, "Query Port ETS failed\n");
		जाओ dcb_error;
	पूर्ण

	mutex_unlock(&pf->tc_mutex);

	वापस;

dcb_error:
	dev_err(dev, "Disabling DCB until new settings occur\n");
	err_cfg = kzalloc(माप(*err_cfg), GFP_KERNEL);
	अगर (!err_cfg) अणु
		mutex_unlock(&pf->tc_mutex);
		वापस;
	पूर्ण

	err_cfg->etscfg.willing = true;
	err_cfg->etscfg.tcbwtable[0] = ICE_TC_MAX_BW;
	err_cfg->etscfg.tsatable[0] = ICE_IEEE_TSA_ETS;
	स_नकल(&err_cfg->etsrec, &err_cfg->etscfg, माप(err_cfg->etsrec));
	/* Coverity warns the वापस code of ice_pf_dcb_cfg() is not checked
	 * here as is करोne क्रम other calls to that function. That check is
	 * not necessary since this is in this function's error cleanup path.
	 * Suppress the Coverity warning with the following comment...
	 */
	/* coverity[check_वापस] */
	ice_pf_dcb_cfg(pf, err_cfg, false);
	kमुक्त(err_cfg);

	mutex_unlock(&pf->tc_mutex);
पूर्ण

/**
 * ice_dcb_init_cfg - set the initial DCB config in SW
 * @pf: PF to apply config to
 * @locked: Is the RTNL held
 */
अटल पूर्णांक ice_dcb_init_cfg(काष्ठा ice_pf *pf, bool locked)
अणु
	काष्ठा ice_dcbx_cfg *newcfg;
	काष्ठा ice_port_info *pi;
	पूर्णांक ret = 0;

	pi = pf->hw.port_info;
	newcfg = kmemdup(&pi->qos_cfg.local_dcbx_cfg, माप(*newcfg),
			 GFP_KERNEL);
	अगर (!newcfg)
		वापस -ENOMEM;

	स_रखो(&pi->qos_cfg.local_dcbx_cfg, 0, माप(*newcfg));

	dev_info(ice_pf_to_dev(pf), "Configuring initial DCB values\n");
	अगर (ice_pf_dcb_cfg(pf, newcfg, locked))
		ret = -EINVAL;

	kमुक्त(newcfg);

	वापस ret;
पूर्ण

/**
 * ice_dcb_sw_dflt_cfg - Apply a शेष DCB config
 * @pf: PF to apply config to
 * @ets_willing: configure ETS willing
 * @locked: was this function called with RTNL held
 */
अटल पूर्णांक ice_dcb_sw_dflt_cfg(काष्ठा ice_pf *pf, bool ets_willing, bool locked)
अणु
	काष्ठा ice_aqc_port_ets_elem buf = अणु 0 पूर्ण;
	काष्ठा ice_dcbx_cfg *dcbcfg;
	काष्ठा ice_port_info *pi;
	काष्ठा ice_hw *hw;
	पूर्णांक ret;

	hw = &pf->hw;
	pi = hw->port_info;
	dcbcfg = kzalloc(माप(*dcbcfg), GFP_KERNEL);
	अगर (!dcbcfg)
		वापस -ENOMEM;

	स_रखो(&pi->qos_cfg.local_dcbx_cfg, 0, माप(*dcbcfg));

	dcbcfg->etscfg.willing = ets_willing ? 1 : 0;
	dcbcfg->etscfg.maxtcs = hw->func_caps.common_cap.maxtc;
	dcbcfg->etscfg.tcbwtable[0] = 100;
	dcbcfg->etscfg.tsatable[0] = ICE_IEEE_TSA_ETS;

	स_नकल(&dcbcfg->etsrec, &dcbcfg->etscfg,
	       माप(dcbcfg->etsrec));
	dcbcfg->etsrec.willing = 0;

	dcbcfg->pfc.willing = 1;
	dcbcfg->pfc.pfccap = hw->func_caps.common_cap.maxtc;

	dcbcfg->numapps = 1;
	dcbcfg->app[0].selector = ICE_APP_SEL_ETHTYPE;
	dcbcfg->app[0].priority = 3;
	dcbcfg->app[0].prot_id = ETH_P_FCOE;

	ret = ice_pf_dcb_cfg(pf, dcbcfg, locked);
	kमुक्त(dcbcfg);
	अगर (ret)
		वापस ret;

	वापस ice_query_port_ets(pi, &buf, माप(buf), शून्य);
पूर्ण

/**
 * ice_dcb_tc_contig - Check that TCs are contiguous
 * @prio_table: poपूर्णांकer to priority table
 *
 * Check अगर TCs begin with TC0 and are contiguous
 */
अटल bool ice_dcb_tc_contig(u8 *prio_table)
अणु
	bool found_empty = false;
	u8 used_tc = 0;
	पूर्णांक i;

	/* Create a biपंचांगap of used TCs */
	क्रम (i = 0; i < CEE_DCBX_MAX_PRIO; i++)
		used_tc |= BIT(prio_table[i]);

	क्रम (i = 0; i < CEE_DCBX_MAX_PRIO; i++) अणु
		अगर (used_tc & BIT(i)) अणु
			अगर (found_empty)
				वापस false;
		पूर्ण अन्यथा अणु
			found_empty = true;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 * ice_dcb_noncontig_cfg - Configure DCB क्रम non-contiguous TCs
 * @pf: poपूर्णांकer to the PF काष्ठा
 *
 * If non-contiguous TCs, then configure SW DCB with TC0 and ETS non-willing
 */
अटल पूर्णांक ice_dcb_noncontig_cfg(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_dcbx_cfg *dcbcfg = &pf->hw.port_info->qos_cfg.local_dcbx_cfg;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	पूर्णांक ret;

	/* Configure SW DCB शेष with ETS non-willing */
	ret = ice_dcb_sw_dflt_cfg(pf, false, true);
	अगर (ret) अणु
		dev_err(dev, "Failed to set local DCB config %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reconfigure with ETS willing so that FW will send LLDP MIB event */
	dcbcfg->etscfg.willing = 1;
	ret = ice_set_dcb_cfg(pf->hw.port_info);
	अगर (ret)
		dev_err(dev, "Failed to set DCB to unwilling\n");

	वापस ret;
पूर्ण

/**
 * ice_pf_dcb_recfg - Reconfigure all VEBs and VSIs
 * @pf: poपूर्णांकer to the PF काष्ठा
 *
 * Assumed caller has alपढ़ोy disabled all VSIs beक्रमe
 * calling this function. Reconfiguring DCB based on
 * local_dcbx_cfg.
 */
व्योम ice_pf_dcb_recfg(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_dcbx_cfg *dcbcfg = &pf->hw.port_info->qos_cfg.local_dcbx_cfg;
	u8 tc_map = 0;
	पूर्णांक v, ret;

	/* Update each VSI */
	ice_क्रम_each_vsi(pf, v) अणु
		काष्ठा ice_vsi *vsi = pf->vsi[v];

		अगर (!vsi)
			जारी;

		अगर (vsi->type == ICE_VSI_PF) अणु
			tc_map = ice_dcb_get_ena_tc(dcbcfg);

			/* If DCBX request non-contiguous TC, then configure
			 * शेष TC
			 */
			अगर (!ice_dcb_tc_contig(dcbcfg->etscfg.prio_table)) अणु
				tc_map = ICE_DFLT_TRAFFIC_CLASS;
				ice_dcb_noncontig_cfg(pf);
			पूर्ण
		पूर्ण अन्यथा अणु
			tc_map = ICE_DFLT_TRAFFIC_CLASS;
		पूर्ण

		ret = ice_vsi_cfg_tc(vsi, tc_map);
		अगर (ret) अणु
			dev_err(ice_pf_to_dev(pf), "Failed to config TC for VSI index: %d\n",
				vsi->idx);
			जारी;
		पूर्ण

		ice_vsi_map_rings_to_vectors(vsi);
		अगर (vsi->type == ICE_VSI_PF)
			ice_dcbnl_set_all(vsi);
	पूर्ण
पूर्ण

/**
 * ice_init_pf_dcb - initialize DCB क्रम a PF
 * @pf: PF to initialize DCB क्रम
 * @locked: Was function called with RTNL held
 */
पूर्णांक ice_init_pf_dcb(काष्ठा ice_pf *pf, bool locked)
अणु
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_port_info *port_info;
	काष्ठा ice_hw *hw = &pf->hw;
	पूर्णांक err;

	port_info = hw->port_info;

	err = ice_init_dcb(hw, false);
	अगर (err && !port_info->qos_cfg.is_sw_lldp) अणु
		dev_err(dev, "Error initializing DCB %d\n", err);
		जाओ dcb_init_err;
	पूर्ण

	dev_info(dev, "DCB is enabled in the hardware, max number of TCs supported on this port are %d\n",
		 pf->hw.func_caps.common_cap.maxtc);
	अगर (err) अणु
		काष्ठा ice_vsi *pf_vsi;

		/* FW LLDP is disabled, activate SW DCBX/LLDP mode */
		dev_info(dev, "FW LLDP is disabled, DCBx/LLDP in SW mode.\n");
		clear_bit(ICE_FLAG_FW_LLDP_AGENT, pf->flags);
		err = ice_dcb_sw_dflt_cfg(pf, true, locked);
		अगर (err) अणु
			dev_err(dev, "Failed to set local DCB config %d\n",
				err);
			err = -EIO;
			जाओ dcb_init_err;
		पूर्ण

		/* If the FW DCBX engine is not running then Rx LLDP packets
		 * need to be redirected up the stack.
		 */
		pf_vsi = ice_get_मुख्य_vsi(pf);
		अगर (!pf_vsi) अणु
			dev_err(dev, "Failed to set local DCB config\n");
			err = -EIO;
			जाओ dcb_init_err;
		पूर्ण

		ice_cfg_sw_lldp(pf_vsi, false, true);

		pf->dcbx_cap = ice_dcb_get_mode(port_info, true);
		वापस 0;
	पूर्ण

	set_bit(ICE_FLAG_FW_LLDP_AGENT, pf->flags);

	/* DCBX/LLDP enabled in FW, set DCBNL mode advertisement */
	pf->dcbx_cap = ice_dcb_get_mode(port_info, false);

	err = ice_dcb_init_cfg(pf, locked);
	अगर (err)
		जाओ dcb_init_err;

	वापस err;

dcb_init_err:
	dev_err(dev, "DCB init failed\n");
	वापस err;
पूर्ण

/**
 * ice_update_dcb_stats - Update DCB stats counters
 * @pf: PF whose stats needs to be updated
 */
व्योम ice_update_dcb_stats(काष्ठा ice_pf *pf)
अणु
	काष्ठा ice_hw_port_stats *prev_ps, *cur_ps;
	काष्ठा ice_hw *hw = &pf->hw;
	u8 port;
	पूर्णांक i;

	port = hw->port_info->lport;
	prev_ps = &pf->stats_prev;
	cur_ps = &pf->stats;

	क्रम (i = 0; i < 8; i++) अणु
		ice_stat_update32(hw, GLPRT_PXOFFRXC(port, i),
				  pf->stat_prev_loaded,
				  &prev_ps->priority_xoff_rx[i],
				  &cur_ps->priority_xoff_rx[i]);
		ice_stat_update32(hw, GLPRT_PXONRXC(port, i),
				  pf->stat_prev_loaded,
				  &prev_ps->priority_xon_rx[i],
				  &cur_ps->priority_xon_rx[i]);
		ice_stat_update32(hw, GLPRT_PXONTXC(port, i),
				  pf->stat_prev_loaded,
				  &prev_ps->priority_xon_tx[i],
				  &cur_ps->priority_xon_tx[i]);
		ice_stat_update32(hw, GLPRT_PXOFFTXC(port, i),
				  pf->stat_prev_loaded,
				  &prev_ps->priority_xoff_tx[i],
				  &cur_ps->priority_xoff_tx[i]);
		ice_stat_update32(hw, GLPRT_RXON2OFFCNT(port, i),
				  pf->stat_prev_loaded,
				  &prev_ps->priority_xon_2_xoff[i],
				  &cur_ps->priority_xon_2_xoff[i]);
	पूर्ण
पूर्ण

/**
 * ice_tx_prepare_vlan_flags_dcb - prepare VLAN tagging क्रम DCB
 * @tx_ring: ring to send buffer on
 * @first: poपूर्णांकer to काष्ठा ice_tx_buf
 *
 * This should not be called अगर the outer VLAN is software offloaded as the VLAN
 * tag will alपढ़ोy be configured with the correct ID and priority bits
 */
व्योम
ice_tx_prepare_vlan_flags_dcb(काष्ठा ice_ring *tx_ring,
			      काष्ठा ice_tx_buf *first)
अणु
	काष्ठा sk_buff *skb = first->skb;

	अगर (!test_bit(ICE_FLAG_DCB_ENA, tx_ring->vsi->back->flags))
		वापस;

	/* Insert 802.1p priority पूर्णांकo VLAN header */
	अगर ((first->tx_flags & ICE_TX_FLAGS_HW_VLAN) ||
	    skb->priority != TC_PRIO_CONTROL) अणु
		first->tx_flags &= ~ICE_TX_FLAGS_VLAN_PR_M;
		/* Mask the lower 3 bits to set the 802.1p priority */
		first->tx_flags |= (skb->priority & 0x7) <<
				   ICE_TX_FLAGS_VLAN_PR_S;
		/* अगर this is not alपढ़ोy set it means a VLAN 0 + priority needs
		 * to be offloaded
		 */
		first->tx_flags |= ICE_TX_FLAGS_HW_VLAN;
	पूर्ण
पूर्ण

/**
 * ice_dcb_process_lldp_set_mib_change - Process MIB change
 * @pf: ptr to ice_pf
 * @event: poपूर्णांकer to the admin queue receive event
 */
व्योम
ice_dcb_process_lldp_set_mib_change(काष्ठा ice_pf *pf,
				    काष्ठा ice_rq_event_info *event)
अणु
	काष्ठा ice_aqc_port_ets_elem buf = अणु 0 पूर्ण;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	काष्ठा ice_aqc_lldp_get_mib *mib;
	काष्ठा ice_dcbx_cfg पंचांगp_dcbx_cfg;
	bool need_reconfig = false;
	काष्ठा ice_port_info *pi;
	काष्ठा ice_vsi *pf_vsi;
	u8 mib_type;
	पूर्णांक ret;

	/* Not DCB capable or capability disabled */
	अगर (!(test_bit(ICE_FLAG_DCB_CAPABLE, pf->flags)))
		वापस;

	अगर (pf->dcbx_cap & DCB_CAP_DCBX_HOST) अणु
		dev_dbg(dev, "MIB Change Event in HOST mode\n");
		वापस;
	पूर्ण

	pi = pf->hw.port_info;
	mib = (काष्ठा ice_aqc_lldp_get_mib *)&event->desc.params.raw;
	/* Ignore अगर event is not क्रम Nearest Bridge */
	mib_type = ((mib->type >> ICE_AQ_LLDP_BRID_TYPE_S) &
		    ICE_AQ_LLDP_BRID_TYPE_M);
	dev_dbg(dev, "LLDP event MIB bridge type 0x%x\n", mib_type);
	अगर (mib_type != ICE_AQ_LLDP_BRID_TYPE_NEAREST_BRID)
		वापस;

	/* Check MIB Type and वापस अगर event क्रम Remote MIB update */
	mib_type = mib->type & ICE_AQ_LLDP_MIB_TYPE_M;
	dev_dbg(dev, "LLDP event mib type %s\n", mib_type ? "remote" : "local");
	अगर (mib_type == ICE_AQ_LLDP_MIB_REMOTE) अणु
		/* Update the remote cached instance and वापस */
		ret = ice_aq_get_dcb_cfg(pi->hw, ICE_AQ_LLDP_MIB_REMOTE,
					 ICE_AQ_LLDP_BRID_TYPE_NEAREST_BRID,
					 &pi->qos_cfg.remote_dcbx_cfg);
		अगर (ret) अणु
			dev_err(dev, "Failed to get remote DCB config\n");
			वापस;
		पूर्ण
	पूर्ण

	mutex_lock(&pf->tc_mutex);

	/* store the old configuration */
	पंचांगp_dcbx_cfg = pf->hw.port_info->qos_cfg.local_dcbx_cfg;

	/* Reset the old DCBX configuration data */
	स_रखो(&pi->qos_cfg.local_dcbx_cfg, 0,
	       माप(pi->qos_cfg.local_dcbx_cfg));

	/* Get updated DCBX data from firmware */
	ret = ice_get_dcb_cfg(pf->hw.port_info);
	अगर (ret) अणु
		dev_err(dev, "Failed to get DCB config\n");
		जाओ out;
	पूर्ण

	/* No change detected in DCBX configs */
	अगर (!स_भेद(&पंचांगp_dcbx_cfg, &pi->qos_cfg.local_dcbx_cfg,
		    माप(पंचांगp_dcbx_cfg))) अणु
		dev_dbg(dev, "No change detected in DCBX configuration.\n");
		जाओ out;
	पूर्ण

	pf->dcbx_cap = ice_dcb_get_mode(pi, false);

	need_reconfig = ice_dcb_need_recfg(pf, &पंचांगp_dcbx_cfg,
					   &pi->qos_cfg.local_dcbx_cfg);
	ice_dcbnl_flush_apps(pf, &पंचांगp_dcbx_cfg, &pi->qos_cfg.local_dcbx_cfg);
	अगर (!need_reconfig)
		जाओ out;

	/* Enable DCB tagging only when more than one TC */
	अगर (ice_dcb_get_num_tc(&pi->qos_cfg.local_dcbx_cfg) > 1) अणु
		dev_dbg(dev, "DCB tagging enabled (num TC > 1)\n");
		set_bit(ICE_FLAG_DCB_ENA, pf->flags);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "DCB tagging disabled (num TC = 1)\n");
		clear_bit(ICE_FLAG_DCB_ENA, pf->flags);
	पूर्ण

	pf_vsi = ice_get_मुख्य_vsi(pf);
	अगर (!pf_vsi) अणु
		dev_dbg(dev, "PF VSI doesn't exist\n");
		जाओ out;
	पूर्ण

	rtnl_lock();
	ice_dis_vsi(pf_vsi, true);

	ret = ice_query_port_ets(pf->hw.port_info, &buf, माप(buf), शून्य);
	अगर (ret) अणु
		dev_err(dev, "Query Port ETS failed\n");
		जाओ unlock_rtnl;
	पूर्ण

	/* changes in configuration update VSI */
	ice_pf_dcb_recfg(pf);

	ice_ena_vsi(pf_vsi, true);
unlock_rtnl:
	rtnl_unlock();
out:
	mutex_unlock(&pf->tc_mutex);
पूर्ण
