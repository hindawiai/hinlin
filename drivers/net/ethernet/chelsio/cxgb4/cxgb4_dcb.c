<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2013-2014 Chelsio Communications.  All rights reserved.
 *
 *  Written by Anish Bhatt (anish@chelsio.com)
 *	       Casey Leeकरोm (leeकरोm@chelsio.com)
 */

#समावेश "cxgb4.h"

/* DCBx version control
 */
स्थिर अक्षर * स्थिर dcb_ver_array[] = अणु
	"Unknown",
	"DCBx-CIN",
	"DCBx-CEE 1.01",
	"DCBx-IEEE",
	"", "", "",
	"Auto Negotiated"
पूर्ण;

अटल अंतरभूत bool cxgb4_dcb_state_synced(क्रमागत cxgb4_dcb_state state)
अणु
	अगर (state == CXGB4_DCB_STATE_FW_ALLSYNCED ||
	    state == CXGB4_DCB_STATE_HOST)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/* Initialize a port's Data Center Bridging state.
 */
व्योम cxgb4_dcb_state_init(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा port_dcb_info *dcb = &pi->dcb;
	पूर्णांक version_temp = dcb->dcb_version;

	स_रखो(dcb, 0, माप(काष्ठा port_dcb_info));
	dcb->state = CXGB4_DCB_STATE_START;
	अगर (version_temp)
		dcb->dcb_version = version_temp;

	netdev_dbg(dev, "%s: Initializing DCB state for port[%d]\n",
		    __func__, pi->port_id);
पूर्ण

व्योम cxgb4_dcb_version_init(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा port_dcb_info *dcb = &pi->dcb;

	/* Any ग_लिखोs here are only करोne on kernels that exlicitly need
	 * a specअगरic version, say < 2.6.38 which only support CEE
	 */
	dcb->dcb_version = FW_PORT_DCB_VER_AUTO;
पूर्ण

अटल व्योम cxgb4_dcb_cleanup_apps(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा port_dcb_info *dcb = &pi->dcb;
	काष्ठा dcb_app app;
	पूर्णांक i, err;

	/* zero priority implies हटाओ */
	app.priority = 0;

	क्रम (i = 0; i < CXGB4_MAX_DCBX_APP_SUPPORTED; i++) अणु
		/* Check अगर app list is exhausted */
		अगर (!dcb->app_priority[i].protocolid)
			अवरोध;

		app.protocol = dcb->app_priority[i].protocolid;

		अगर (dcb->dcb_version == FW_PORT_DCB_VER_IEEE) अणु
			app.priority = dcb->app_priority[i].user_prio_map;
			app.selector = dcb->app_priority[i].sel_field + 1;
			err = dcb_ieee_delapp(dev, &app);
		पूर्ण अन्यथा अणु
			app.selector = !!(dcb->app_priority[i].sel_field);
			err = dcb_setapp(dev, &app);
		पूर्ण

		अगर (err) अणु
			dev_err(adap->pdev_dev,
				"Failed DCB Clear %s Application Priority: sel=%d, prot=%d, , err=%d\n",
				dcb_ver_array[dcb->dcb_version], app.selector,
				app.protocol, -err);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Reset a port's Data Center Bridging state.  Typically used after a
 * Link Down event.
 */
व्योम cxgb4_dcb_reset(काष्ठा net_device *dev)
अणु
	cxgb4_dcb_cleanup_apps(dev);
	cxgb4_dcb_state_init(dev);
पूर्ण

/* update the dcb port support, अगर version is IEEE then set it to
 * FW_PORT_DCB_VER_IEEE and अगर DCB_CAP_DCBX_VER_CEE is alपढ़ोy set then
 * clear that. and अगर it is set to CEE then set dcb supported to
 * DCB_CAP_DCBX_VER_CEE & अगर DCB_CAP_DCBX_VER_IEEE is set, clear it
 */
अटल अंतरभूत व्योम cxgb4_dcb_update_support(काष्ठा port_dcb_info *dcb)
अणु
	अगर (dcb->dcb_version == FW_PORT_DCB_VER_IEEE) अणु
		अगर (dcb->supported & DCB_CAP_DCBX_VER_CEE)
			dcb->supported &= ~DCB_CAP_DCBX_VER_CEE;
		dcb->supported |= DCB_CAP_DCBX_VER_IEEE;
	पूर्ण अन्यथा अगर (dcb->dcb_version == FW_PORT_DCB_VER_CEE1D01) अणु
		अगर (dcb->supported & DCB_CAP_DCBX_VER_IEEE)
			dcb->supported &= ~DCB_CAP_DCBX_VER_IEEE;
		dcb->supported |= DCB_CAP_DCBX_VER_CEE;
	पूर्ण
पूर्ण

/* Finite State machine क्रम Data Center Bridging.
 */
व्योम cxgb4_dcb_state_fsm(काष्ठा net_device *dev,
			 क्रमागत cxgb4_dcb_state_input transition_to)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा port_dcb_info *dcb = &pi->dcb;
	काष्ठा adapter *adap = pi->adapter;
	क्रमागत cxgb4_dcb_state current_state = dcb->state;

	netdev_dbg(dev, "%s: State change from %d to %d for %s\n",
		    __func__, dcb->state, transition_to, dev->name);

	चयन (current_state) अणु
	हाल CXGB4_DCB_STATE_START: अणु
		चयन (transition_to) अणु
		हाल CXGB4_DCB_INPUT_FW_DISABLED: अणु
			/* we're going to use Host DCB */
			dcb->state = CXGB4_DCB_STATE_HOST;
			dcb->supported = CXGB4_DCBX_HOST_SUPPORT;
			अवरोध;
		पूर्ण

		हाल CXGB4_DCB_INPUT_FW_ENABLED: अणु
			/* we're going to use Firmware DCB */
			dcb->state = CXGB4_DCB_STATE_FW_INCOMPLETE;
			dcb->supported = DCB_CAP_DCBX_LLD_MANAGED;
			अगर (dcb->dcb_version == FW_PORT_DCB_VER_IEEE)
				dcb->supported |= DCB_CAP_DCBX_VER_IEEE;
			अन्यथा
				dcb->supported |= DCB_CAP_DCBX_VER_CEE;
			अवरोध;
		पूर्ण

		हाल CXGB4_DCB_INPUT_FW_INCOMPLETE: अणु
			/* expected transition */
			अवरोध;
		पूर्ण

		हाल CXGB4_DCB_INPUT_FW_ALLSYNCED: अणु
			dcb->state = CXGB4_DCB_STATE_FW_ALLSYNCED;
			अवरोध;
		पूर्ण

		शेष:
			जाओ bad_state_input;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल CXGB4_DCB_STATE_FW_INCOMPLETE: अणु
		अगर (transition_to != CXGB4_DCB_INPUT_FW_DISABLED) अणु
			/* during this CXGB4_DCB_STATE_FW_INCOMPLETE state,
			 * check अगर the dcb version is changed (there can be
			 * mismatch in शेष config & the negotiated चयन
			 * configuration at FW, so update the dcb support
			 * accordingly.
			 */
			cxgb4_dcb_update_support(dcb);
		पूर्ण
		चयन (transition_to) अणु
		हाल CXGB4_DCB_INPUT_FW_ENABLED: अणु
			/* we're alreaady in firmware DCB mode */
			अवरोध;
		पूर्ण

		हाल CXGB4_DCB_INPUT_FW_INCOMPLETE: अणु
			/* we're alपढ़ोy incomplete */
			अवरोध;
		पूर्ण

		हाल CXGB4_DCB_INPUT_FW_ALLSYNCED: अणु
			dcb->state = CXGB4_DCB_STATE_FW_ALLSYNCED;
			dcb->enabled = 1;
			linkwatch_fire_event(dev);
			अवरोध;
		पूर्ण

		शेष:
			जाओ bad_state_input;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल CXGB4_DCB_STATE_FW_ALLSYNCED: अणु
		चयन (transition_to) अणु
		हाल CXGB4_DCB_INPUT_FW_ENABLED: अणु
			/* we're alreaady in firmware DCB mode */
			अवरोध;
		पूर्ण

		हाल CXGB4_DCB_INPUT_FW_INCOMPLETE: अणु
			/* We were successfully running with firmware DCB but
			 * now it's telling us that it's in an "incomplete
			 * state.  We need to reset back to a ground state
			 * of incomplete.
			 */
			cxgb4_dcb_reset(dev);
			dcb->state = CXGB4_DCB_STATE_FW_INCOMPLETE;
			dcb->supported = CXGB4_DCBX_FW_SUPPORT;
			linkwatch_fire_event(dev);
			अवरोध;
		पूर्ण

		हाल CXGB4_DCB_INPUT_FW_ALLSYNCED: अणु
			/* we're already all sync'ed
			 * this is only applicable क्रम IEEE or
			 * when another VI alपढ़ोy completed negotiaton
			 */
			dcb->enabled = 1;
			linkwatch_fire_event(dev);
			अवरोध;
		पूर्ण

		शेष:
			जाओ bad_state_input;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल CXGB4_DCB_STATE_HOST: अणु
		चयन (transition_to) अणु
		हाल CXGB4_DCB_INPUT_FW_DISABLED: अणु
			/* we're alreaady in Host DCB mode */
			अवरोध;
		पूर्ण

		शेष:
			जाओ bad_state_input;
		पूर्ण
		अवरोध;
	पूर्ण

	शेष:
		जाओ bad_state_transition;
	पूर्ण
	वापस;

bad_state_input:
	dev_err(adap->pdev_dev, "cxgb4_dcb_state_fsm: illegal input symbol %d\n",
		transition_to);
	वापस;

bad_state_transition:
	dev_err(adap->pdev_dev, "cxgb4_dcb_state_fsm: bad state transition, state = %d, input = %d\n",
		current_state, transition_to);
पूर्ण

/* Handle a DCB/DCBX update message from the firmware.
 */
व्योम cxgb4_dcb_handle_fw_update(काष्ठा adapter *adap,
				स्थिर काष्ठा fw_port_cmd *pcmd)
अणु
	स्थिर जोड़ fw_port_dcb *fwdcb = &pcmd->u.dcb;
	पूर्णांक port = FW_PORT_CMD_PORTID_G(be32_to_cpu(pcmd->op_to_portid));
	काष्ठा net_device *dev = adap->port[adap->chan_map[port]];
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा port_dcb_info *dcb = &pi->dcb;
	पूर्णांक dcb_type = pcmd->u.dcb.pgid.type;
	पूर्णांक dcb_running_version;

	/* Handle Firmware DCB Control messages separately since they drive
	 * our state machine.
	 */
	अगर (dcb_type == FW_PORT_DCB_TYPE_CONTROL) अणु
		क्रमागत cxgb4_dcb_state_input input =
			((pcmd->u.dcb.control.all_syncd_pkd &
			  FW_PORT_CMD_ALL_SYNCD_F)
			 ? CXGB4_DCB_INPUT_FW_ALLSYNCED
			 : CXGB4_DCB_INPUT_FW_INCOMPLETE);

		अगर (dcb->dcb_version != FW_PORT_DCB_VER_UNKNOWN) अणु
			dcb_running_version = FW_PORT_CMD_DCB_VERSION_G(
				be16_to_cpu(
				pcmd->u.dcb.control.dcb_version_to_app_state));
			अगर (dcb_running_version == FW_PORT_DCB_VER_CEE1D01 ||
			    dcb_running_version == FW_PORT_DCB_VER_IEEE) अणु
				dcb->dcb_version = dcb_running_version;
				dev_warn(adap->pdev_dev, "Interface %s is running %s\n",
					 dev->name,
					 dcb_ver_array[dcb->dcb_version]);
			पूर्ण अन्यथा अणु
				dev_warn(adap->pdev_dev,
					 "Something screwed up, requested firmware for %s, but firmware returned %s instead\n",
					 dcb_ver_array[dcb->dcb_version],
					 dcb_ver_array[dcb_running_version]);
				dcb->dcb_version = FW_PORT_DCB_VER_UNKNOWN;
			पूर्ण
		पूर्ण

		cxgb4_dcb_state_fsm(dev, input);
		वापस;
	पूर्ण

	/* It's weird, and almost certainly an error, to get Firmware DCB
	 * messages when we either haven't been told whether we're going to be
	 * करोing Host or Firmware DCB; and even worse when we've been told
	 * that we're करोing Host DCB!
	 */
	अगर (dcb->state == CXGB4_DCB_STATE_START ||
	    dcb->state == CXGB4_DCB_STATE_HOST) अणु
		dev_err(adap->pdev_dev, "Receiving Firmware DCB messages in State %d\n",
			dcb->state);
		वापस;
	पूर्ण

	/* Now handle the general Firmware DCB update messages ...
	 */
	चयन (dcb_type) अणु
	हाल FW_PORT_DCB_TYPE_PGID:
		dcb->pgid = be32_to_cpu(fwdcb->pgid.pgid);
		dcb->msgs |= CXGB4_DCB_FW_PGID;
		अवरोध;

	हाल FW_PORT_DCB_TYPE_PGRATE:
		dcb->pg_num_tcs_supported = fwdcb->pgrate.num_tcs_supported;
		स_नकल(dcb->pgrate, &fwdcb->pgrate.pgrate,
		       माप(dcb->pgrate));
		स_नकल(dcb->tsa, &fwdcb->pgrate.tsa,
		       माप(dcb->tsa));
		dcb->msgs |= CXGB4_DCB_FW_PGRATE;
		अगर (dcb->msgs & CXGB4_DCB_FW_PGID)
			IEEE_FAUX_SYNC(dev, dcb);
		अवरोध;

	हाल FW_PORT_DCB_TYPE_PRIORATE:
		स_नकल(dcb->priorate, &fwdcb->priorate.strict_priorate,
		       माप(dcb->priorate));
		dcb->msgs |= CXGB4_DCB_FW_PRIORATE;
		अवरोध;

	हाल FW_PORT_DCB_TYPE_PFC:
		dcb->pfcen = fwdcb->pfc.pfcen;
		dcb->pfc_num_tcs_supported = fwdcb->pfc.max_pfc_tcs;
		dcb->msgs |= CXGB4_DCB_FW_PFC;
		IEEE_FAUX_SYNC(dev, dcb);
		अवरोध;

	हाल FW_PORT_DCB_TYPE_APP_ID: अणु
		स्थिर काष्ठा fw_port_app_priority *fwap = &fwdcb->app_priority;
		पूर्णांक idx = fwap->idx;
		काष्ठा app_priority *ap = &dcb->app_priority[idx];

		काष्ठा dcb_app app = अणु
			.protocol = be16_to_cpu(fwap->protocolid),
		पूर्ण;
		पूर्णांक err;

		/* Convert from firmware क्रमmat to relevant क्रमmat
		 * when using app selector
		 */
		अगर (dcb->dcb_version == FW_PORT_DCB_VER_IEEE) अणु
			app.selector = (fwap->sel_field + 1);
			app.priority = ffs(fwap->user_prio_map) - 1;
			err = dcb_ieee_setapp(dev, &app);
			IEEE_FAUX_SYNC(dev, dcb);
		पूर्ण अन्यथा अणु
			/* Default is CEE */
			app.selector = !!(fwap->sel_field);
			app.priority = fwap->user_prio_map;
			err = dcb_setapp(dev, &app);
		पूर्ण

		अगर (err)
			dev_err(adap->pdev_dev,
				"Failed DCB Set Application Priority: sel=%d, prot=%d, prio=%d, err=%d\n",
				app.selector, app.protocol, app.priority, -err);

		ap->user_prio_map = fwap->user_prio_map;
		ap->sel_field = fwap->sel_field;
		ap->protocolid = be16_to_cpu(fwap->protocolid);
		dcb->msgs |= CXGB4_DCB_FW_APP_ID;
		अवरोध;
	पूर्ण

	शेष:
		dev_err(adap->pdev_dev, "Unknown DCB update type received %x\n",
			dcb_type);
		अवरोध;
	पूर्ण
पूर्ण

/* Data Center Bridging netlink operations.
 */


/* Get current DCB enabled/disabled state.
 */
अटल u8 cxgb4_माला_लोtate(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	वापस pi->dcb.enabled;
पूर्ण

/* Set DCB enabled/disabled.
 */
अटल u8 cxgb4_setstate(काष्ठा net_device *dev, u8 enabled)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	/* If DCBx is host-managed, dcb is enabled by outside lldp agents */
	अगर (pi->dcb.state == CXGB4_DCB_STATE_HOST) अणु
		pi->dcb.enabled = enabled;
		वापस 0;
	पूर्ण

	/* Firmware करोesn't provide any mechanism to control the DCB state.
	 */
	अगर (enabled != (pi->dcb.state == CXGB4_DCB_STATE_FW_ALLSYNCED))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम cxgb4_getpgtccfg(काष्ठा net_device *dev, पूर्णांक tc,
			     u8 *prio_type, u8 *pgid, u8 *bw_per,
			     u8 *up_tc_map, पूर्णांक local)
अणु
	काष्ठा fw_port_cmd pcmd;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक err;

	*prio_type = *pgid = *bw_per = *up_tc_map = 0;

	अगर (local)
		INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	अन्यथा
		INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);

	pcmd.u.dcb.pgid.type = FW_PORT_DCB_TYPE_PGID;
	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGID failed with %d\n", -err);
		वापस;
	पूर्ण
	*pgid = (be32_to_cpu(pcmd.u.dcb.pgid.pgid) >> (tc * 4)) & 0xf;

	अगर (local)
		INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	अन्यथा
		INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);
	pcmd.u.dcb.pgrate.type = FW_PORT_DCB_TYPE_PGRATE;
	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGRATE failed with %d\n",
			-err);
		वापस;
	पूर्ण

	*bw_per = pcmd.u.dcb.pgrate.pgrate[*pgid];
	*up_tc_map = (1 << tc);

	/* prio_type is link strict */
	अगर (*pgid != 0xF)
		*prio_type = 0x2;
पूर्ण

अटल व्योम cxgb4_getpgtccfg_tx(काष्ठा net_device *dev, पूर्णांक tc,
				u8 *prio_type, u8 *pgid, u8 *bw_per,
				u8 *up_tc_map)
अणु
	/* tc 0 is written at MSB position */
	वापस cxgb4_getpgtccfg(dev, (7 - tc), prio_type, pgid, bw_per,
				up_tc_map, 1);
पूर्ण


अटल व्योम cxgb4_getpgtccfg_rx(काष्ठा net_device *dev, पूर्णांक tc,
				u8 *prio_type, u8 *pgid, u8 *bw_per,
				u8 *up_tc_map)
अणु
	/* tc 0 is written at MSB position */
	वापस cxgb4_getpgtccfg(dev, (7 - tc), prio_type, pgid, bw_per,
				up_tc_map, 0);
पूर्ण

अटल व्योम cxgb4_setpgtccfg_tx(काष्ठा net_device *dev, पूर्णांक tc,
				u8 prio_type, u8 pgid, u8 bw_per,
				u8 up_tc_map)
अणु
	काष्ठा fw_port_cmd pcmd;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक fw_tc = 7 - tc;
	u32 _pgid;
	पूर्णांक err;

	अगर (pgid == DCB_ATTR_VALUE_UNDEFINED)
		वापस;
	अगर (bw_per == DCB_ATTR_VALUE_UNDEFINED)
		वापस;

	INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	pcmd.u.dcb.pgid.type = FW_PORT_DCB_TYPE_PGID;

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGID failed with %d\n", -err);
		वापस;
	पूर्ण

	_pgid = be32_to_cpu(pcmd.u.dcb.pgid.pgid);
	_pgid &= ~(0xF << (fw_tc * 4));
	_pgid |= pgid << (fw_tc * 4);
	pcmd.u.dcb.pgid.pgid = cpu_to_be32(_pgid);

	INIT_PORT_DCB_WRITE_CMD(pcmd, pi->port_id);

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB write PGID failed with %d\n",
			-err);
		वापस;
	पूर्ण

	स_रखो(&pcmd, 0, माप(काष्ठा fw_port_cmd));

	INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	pcmd.u.dcb.pgrate.type = FW_PORT_DCB_TYPE_PGRATE;

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGRATE failed with %d\n",
			-err);
		वापस;
	पूर्ण

	pcmd.u.dcb.pgrate.pgrate[pgid] = bw_per;

	INIT_PORT_DCB_WRITE_CMD(pcmd, pi->port_id);
	अगर (pi->dcb.state == CXGB4_DCB_STATE_HOST)
		pcmd.op_to_portid |= cpu_to_be32(FW_PORT_CMD_APPLY_F);

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS)
		dev_err(adap->pdev_dev, "DCB write PGRATE failed with %d\n",
			-err);
पूर्ण

अटल व्योम cxgb4_getpgbwgcfg(काष्ठा net_device *dev, पूर्णांक pgid, u8 *bw_per,
			      पूर्णांक local)
अणु
	काष्ठा fw_port_cmd pcmd;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक err;

	अगर (local)
		INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	अन्यथा
		INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);

	pcmd.u.dcb.pgrate.type = FW_PORT_DCB_TYPE_PGRATE;
	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGRATE failed with %d\n",
			-err);
		वापस;
	पूर्ण

	*bw_per = pcmd.u.dcb.pgrate.pgrate[pgid];
पूर्ण

अटल व्योम cxgb4_getpgbwgcfg_tx(काष्ठा net_device *dev, पूर्णांक pgid, u8 *bw_per)
अणु
	वापस cxgb4_getpgbwgcfg(dev, pgid, bw_per, 1);
पूर्ण

अटल व्योम cxgb4_getpgbwgcfg_rx(काष्ठा net_device *dev, पूर्णांक pgid, u8 *bw_per)
अणु
	वापस cxgb4_getpgbwgcfg(dev, pgid, bw_per, 0);
पूर्ण

अटल व्योम cxgb4_setpgbwgcfg_tx(काष्ठा net_device *dev, पूर्णांक pgid,
				 u8 bw_per)
अणु
	काष्ठा fw_port_cmd pcmd;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक err;

	INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	pcmd.u.dcb.pgrate.type = FW_PORT_DCB_TYPE_PGRATE;

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGRATE failed with %d\n",
			-err);
		वापस;
	पूर्ण

	pcmd.u.dcb.pgrate.pgrate[pgid] = bw_per;

	INIT_PORT_DCB_WRITE_CMD(pcmd, pi->port_id);
	अगर (pi->dcb.state == CXGB4_DCB_STATE_HOST)
		pcmd.op_to_portid |= cpu_to_be32(FW_PORT_CMD_APPLY_F);

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);

	अगर (err != FW_PORT_DCB_CFG_SUCCESS)
		dev_err(adap->pdev_dev, "DCB write PGRATE failed with %d\n",
			-err);
पूर्ण

/* Return whether the specअगरied Traffic Class Priority has Priority Pause
 * Frames enabled.
 */
अटल व्योम cxgb4_getpfccfg(काष्ठा net_device *dev, पूर्णांक priority, u8 *pfccfg)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा port_dcb_info *dcb = &pi->dcb;

	अगर (!cxgb4_dcb_state_synced(dcb->state) ||
	    priority >= CXGB4_MAX_PRIORITY)
		*pfccfg = 0;
	अन्यथा
		*pfccfg = (pi->dcb.pfcen >> (7 - priority)) & 1;
पूर्ण

/* Enable/disable Priority Pause Frames क्रम the specअगरied Traffic Class
 * Priority.
 */
अटल व्योम cxgb4_setpfccfg(काष्ठा net_device *dev, पूर्णांक priority, u8 pfccfg)
अणु
	काष्ठा fw_port_cmd pcmd;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक err;

	अगर (!cxgb4_dcb_state_synced(pi->dcb.state) ||
	    priority >= CXGB4_MAX_PRIORITY)
		वापस;

	INIT_PORT_DCB_WRITE_CMD(pcmd, pi->port_id);
	अगर (pi->dcb.state == CXGB4_DCB_STATE_HOST)
		pcmd.op_to_portid |= cpu_to_be32(FW_PORT_CMD_APPLY_F);

	pcmd.u.dcb.pfc.type = FW_PORT_DCB_TYPE_PFC;
	pcmd.u.dcb.pfc.pfcen = pi->dcb.pfcen;

	अगर (pfccfg)
		pcmd.u.dcb.pfc.pfcen |= (1 << (7 - priority));
	अन्यथा
		pcmd.u.dcb.pfc.pfcen &= (~(1 << (7 - priority)));

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB PFC write failed with %d\n", -err);
		वापस;
	पूर्ण

	pi->dcb.pfcen = pcmd.u.dcb.pfc.pfcen;
पूर्ण

अटल u8 cxgb4_setall(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

/* Return DCB capabilities.
 */
अटल u8 cxgb4_अ_लोap(काष्ठा net_device *dev, पूर्णांक cap_id, u8 *caps)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	चयन (cap_id) अणु
	हाल DCB_CAP_ATTR_PG:
	हाल DCB_CAP_ATTR_PFC:
		*caps = true;
		अवरोध;

	हाल DCB_CAP_ATTR_PG_TCS:
		/* 8 priorities क्रम PG represented by biपंचांगap */
		*caps = 0x80;
		अवरोध;

	हाल DCB_CAP_ATTR_PFC_TCS:
		/* 8 priorities क्रम PFC represented by biपंचांगap */
		*caps = 0x80;
		अवरोध;

	हाल DCB_CAP_ATTR_GSP:
		*caps = true;
		अवरोध;

	हाल DCB_CAP_ATTR_UP2TC:
	हाल DCB_CAP_ATTR_BCN:
		*caps = false;
		अवरोध;

	हाल DCB_CAP_ATTR_DCBX:
		*caps = pi->dcb.supported;
		अवरोध;

	शेष:
		*caps = false;
	पूर्ण

	वापस 0;
पूर्ण

/* Return the number of Traffic Classes क्रम the indicated Traffic Class ID.
 */
अटल पूर्णांक cxgb4_getnumtcs(काष्ठा net_device *dev, पूर्णांक tcs_id, u8 *num)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	चयन (tcs_id) अणु
	हाल DCB_NUMTCS_ATTR_PG:
		अगर (pi->dcb.msgs & CXGB4_DCB_FW_PGRATE)
			*num = pi->dcb.pg_num_tcs_supported;
		अन्यथा
			*num = 0x8;
		अवरोध;

	हाल DCB_NUMTCS_ATTR_PFC:
		*num = 0x8;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Set the number of Traffic Classes supported क्रम the indicated Traffic Class
 * ID.
 */
अटल पूर्णांक cxgb4_setnumtcs(काष्ठा net_device *dev, पूर्णांक tcs_id, u8 num)
अणु
	/* Setting the number of Traffic Classes isn't supported.
	 */
	वापस -ENOSYS;
पूर्ण

/* Return whether Priority Flow Control is enabled.  */
अटल u8 cxgb4_getpfcstate(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	अगर (!cxgb4_dcb_state_synced(pi->dcb.state))
		वापस false;

	वापस pi->dcb.pfcen != 0;
पूर्ण

/* Enable/disable Priority Flow Control. */
अटल व्योम cxgb4_setpfcstate(काष्ठा net_device *dev, u8 state)
अणु
	/* We can't enable/disable Priority Flow Control but we also can't
	 * वापस an error ...
	 */
पूर्ण

/* Return the Application User Priority Map associated with the specअगरied
 * Application ID.
 */
अटल पूर्णांक __cxgb4_getapp(काष्ठा net_device *dev, u8 app_idtype, u16 app_id,
			  पूर्णांक peer)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक i;

	अगर (!cxgb4_dcb_state_synced(pi->dcb.state))
		वापस 0;

	क्रम (i = 0; i < CXGB4_MAX_DCBX_APP_SUPPORTED; i++) अणु
		काष्ठा fw_port_cmd pcmd;
		पूर्णांक err;

		अगर (peer)
			INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);
		अन्यथा
			INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);

		pcmd.u.dcb.app_priority.type = FW_PORT_DCB_TYPE_APP_ID;
		pcmd.u.dcb.app_priority.idx = i;

		err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
		अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
			dev_err(adap->pdev_dev, "DCB APP read failed with %d\n",
				-err);
			वापस err;
		पूर्ण
		अगर (be16_to_cpu(pcmd.u.dcb.app_priority.protocolid) == app_id)
			अगर (pcmd.u.dcb.app_priority.sel_field == app_idtype)
				वापस pcmd.u.dcb.app_priority.user_prio_map;

		/* exhausted app list */
		अगर (!pcmd.u.dcb.app_priority.protocolid)
			अवरोध;
	पूर्ण

	वापस -EEXIST;
पूर्ण

/* Return the Application User Priority Map associated with the specअगरied
 * Application ID.
 */
अटल पूर्णांक cxgb4_getapp(काष्ठा net_device *dev, u8 app_idtype, u16 app_id)
अणु
	/* Convert app_idtype to firmware क्रमmat beक्रमe querying */
	वापस __cxgb4_getapp(dev, app_idtype == DCB_APP_IDTYPE_ETHTYPE ?
			      app_idtype : 3, app_id, 0);
पूर्ण

/* Write a new Application User Priority Map क्रम the specअगरied Application ID
 */
अटल पूर्णांक __cxgb4_setapp(काष्ठा net_device *dev, u8 app_idtype, u16 app_id,
			  u8 app_prio)
अणु
	काष्ठा fw_port_cmd pcmd;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक i, err;


	अगर (!cxgb4_dcb_state_synced(pi->dcb.state))
		वापस -EINVAL;

	/* DCB info माला_लो thrown away on link up */
	अगर (!netअगर_carrier_ok(dev))
		वापस -ENOLINK;

	क्रम (i = 0; i < CXGB4_MAX_DCBX_APP_SUPPORTED; i++) अणु
		INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
		pcmd.u.dcb.app_priority.type = FW_PORT_DCB_TYPE_APP_ID;
		pcmd.u.dcb.app_priority.idx = i;
		err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);

		अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
			dev_err(adap->pdev_dev, "DCB app table read failed with %d\n",
				-err);
			वापस err;
		पूर्ण
		अगर (be16_to_cpu(pcmd.u.dcb.app_priority.protocolid) == app_id) अणु
			/* overग_लिखो existing app table */
			pcmd.u.dcb.app_priority.protocolid = 0;
			अवरोध;
		पूर्ण
		/* find first empty slot */
		अगर (!pcmd.u.dcb.app_priority.protocolid)
			अवरोध;
	पूर्ण

	अगर (i == CXGB4_MAX_DCBX_APP_SUPPORTED) अणु
		/* no empty slots available */
		dev_err(adap->pdev_dev, "DCB app table full\n");
		वापस -EBUSY;
	पूर्ण

	/* ग_लिखो out new app table entry */
	INIT_PORT_DCB_WRITE_CMD(pcmd, pi->port_id);
	अगर (pi->dcb.state == CXGB4_DCB_STATE_HOST)
		pcmd.op_to_portid |= cpu_to_be32(FW_PORT_CMD_APPLY_F);

	pcmd.u.dcb.app_priority.type = FW_PORT_DCB_TYPE_APP_ID;
	pcmd.u.dcb.app_priority.protocolid = cpu_to_be16(app_id);
	pcmd.u.dcb.app_priority.sel_field = app_idtype;
	pcmd.u.dcb.app_priority.user_prio_map = app_prio;
	pcmd.u.dcb.app_priority.idx = i;

	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB app table write failed with %d\n",
			-err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Priority क्रम CEE inside dcb_app is biपंचांगask, with 0 being an invalid value */
अटल पूर्णांक cxgb4_setapp(काष्ठा net_device *dev, u8 app_idtype, u16 app_id,
			u8 app_prio)
अणु
	पूर्णांक ret;
	काष्ठा dcb_app app = अणु
		.selector = app_idtype,
		.protocol = app_id,
		.priority = app_prio,
	पूर्ण;

	अगर (app_idtype != DCB_APP_IDTYPE_ETHTYPE &&
	    app_idtype != DCB_APP_IDTYPE_PORTNUM)
		वापस -EINVAL;

	/* Convert app_idtype to a क्रमmat that firmware understands */
	ret = __cxgb4_setapp(dev, app_idtype == DCB_APP_IDTYPE_ETHTYPE ?
			      app_idtype : 3, app_id, app_prio);
	अगर (ret)
		वापस ret;

	वापस dcb_setapp(dev, &app);
पूर्ण

/* Return whether IEEE Data Center Bridging has been negotiated.
 */
अटल अंतरभूत पूर्णांक
cxgb4_ieee_negotiation_complete(काष्ठा net_device *dev,
				क्रमागत cxgb4_dcb_fw_msgs dcb_subtype)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा port_dcb_info *dcb = &pi->dcb;

	अगर (dcb->state == CXGB4_DCB_STATE_FW_ALLSYNCED)
		अगर (dcb_subtype && !(dcb->msgs & dcb_subtype))
			वापस 0;

	वापस (cxgb4_dcb_state_synced(dcb->state) &&
		(dcb->supported & DCB_CAP_DCBX_VER_IEEE));
पूर्ण

अटल पूर्णांक cxgb4_ieee_पढ़ो_ets(काष्ठा net_device *dev, काष्ठा ieee_ets *ets,
			       पूर्णांक local)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा port_dcb_info *dcb = &pi->dcb;
	काष्ठा adapter *adap = pi->adapter;
	uपूर्णांक32_t tc_info;
	काष्ठा fw_port_cmd pcmd;
	पूर्णांक i, bwg, err;

	अगर (!(dcb->msgs & (CXGB4_DCB_FW_PGID | CXGB4_DCB_FW_PGRATE)))
		वापस 0;

	ets->ets_cap =  dcb->pg_num_tcs_supported;

	अगर (local) अणु
		ets->willing = 1;
		INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	पूर्ण अन्यथा अणु
		INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);
	पूर्ण

	pcmd.u.dcb.pgid.type = FW_PORT_DCB_TYPE_PGID;
	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGID failed with %d\n", -err);
		वापस err;
	पूर्ण

	tc_info = be32_to_cpu(pcmd.u.dcb.pgid.pgid);

	अगर (local)
		INIT_PORT_DCB_READ_LOCAL_CMD(pcmd, pi->port_id);
	अन्यथा
		INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);

	pcmd.u.dcb.pgrate.type = FW_PORT_DCB_TYPE_PGRATE;
	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGRATE failed with %d\n",
			-err);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		bwg = (tc_info >> ((7 - i) * 4)) & 0xF;
		ets->prio_tc[i] = bwg;
		ets->tc_tx_bw[i] = pcmd.u.dcb.pgrate.pgrate[i];
		ets->tc_rx_bw[i] = ets->tc_tx_bw[i];
		ets->tc_tsa[i] = pcmd.u.dcb.pgrate.tsa[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_ieee_get_ets(काष्ठा net_device *dev, काष्ठा ieee_ets *ets)
अणु
	वापस cxgb4_ieee_पढ़ो_ets(dev, ets, 1);
पूर्ण

/* We reuse this क्रम peer PFC as well, as we can't have it enabled one way */
अटल पूर्णांक cxgb4_ieee_get_pfc(काष्ठा net_device *dev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा port_dcb_info *dcb = &pi->dcb;

	स_रखो(pfc, 0, माप(काष्ठा ieee_pfc));

	अगर (!(dcb->msgs & CXGB4_DCB_FW_PFC))
		वापस 0;

	pfc->pfc_cap = dcb->pfc_num_tcs_supported;
	pfc->pfc_en = bitswap_1(dcb->pfcen);

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_ieee_peer_ets(काष्ठा net_device *dev, काष्ठा ieee_ets *ets)
अणु
	वापस cxgb4_ieee_पढ़ो_ets(dev, ets, 0);
पूर्ण

/* Fill in the Application User Priority Map associated with the
 * specअगरied Application.
 * Priority क्रम IEEE dcb_app is an पूर्णांकeger, with 0 being a valid value
 */
अटल पूर्णांक cxgb4_ieee_getapp(काष्ठा net_device *dev, काष्ठा dcb_app *app)
अणु
	पूर्णांक prio;

	अगर (!cxgb4_ieee_negotiation_complete(dev, CXGB4_DCB_FW_APP_ID))
		वापस -EINVAL;
	अगर (!(app->selector && app->protocol))
		वापस -EINVAL;

	/* Try querying firmware first, use firmware क्रमmat */
	prio = __cxgb4_getapp(dev, app->selector - 1, app->protocol, 0);

	अगर (prio < 0)
		prio = dcb_ieee_getapp_mask(dev, app);

	app->priority = ffs(prio) - 1;
	वापस 0;
पूर्ण

/* Write a new Application User Priority Map क्रम the specअगरied Application ID.
 * Priority क्रम IEEE dcb_app is an पूर्णांकeger, with 0 being a valid value
 */
अटल पूर्णांक cxgb4_ieee_setapp(काष्ठा net_device *dev, काष्ठा dcb_app *app)
अणु
	पूर्णांक ret;

	अगर (!cxgb4_ieee_negotiation_complete(dev, CXGB4_DCB_FW_APP_ID))
		वापस -EINVAL;
	अगर (!(app->selector && app->protocol))
		वापस -EINVAL;

	अगर (!(app->selector > IEEE_8021QAZ_APP_SEL_ETHERTYPE  &&
	      app->selector < IEEE_8021QAZ_APP_SEL_ANY))
		वापस -EINVAL;

	/* change selector to a क्रमmat that firmware understands */
	ret = __cxgb4_setapp(dev, app->selector - 1, app->protocol,
			     (1 << app->priority));
	अगर (ret)
		वापस ret;

	वापस dcb_ieee_setapp(dev, app);
पूर्ण

/* Return our DCBX parameters.
 */
अटल u8 cxgb4_getdcbx(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	/* This is alपढ़ोy set by cxgb4_set_dcb_caps, so just वापस it */
	वापस pi->dcb.supported;
पूर्ण

/* Set our DCBX parameters.
 */
अटल u8 cxgb4_setdcbx(काष्ठा net_device *dev, u8 dcb_request)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	/* Filter out requests which exceed our capabilities.
	 */
	अगर ((dcb_request & (CXGB4_DCBX_FW_SUPPORT | CXGB4_DCBX_HOST_SUPPORT))
	    != dcb_request)
		वापस 1;

	/* Can't enable DCB if we haven't successfully negotiated it.
	 */
	अगर (!cxgb4_dcb_state_synced(pi->dcb.state))
		वापस 1;

	/* There's currently no mechanism to allow क्रम the firmware DCBX
	 * negotiation to be changed from the Host Driver.  If the caller
	 * requests exactly the same parameters that we alपढ़ोy have then
	 * we'll allow them to be successfully "set" ...
	 */
	अगर (dcb_request != pi->dcb.supported)
		वापस 1;

	pi->dcb.supported = dcb_request;
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_getpeer_app(काष्ठा net_device *dev,
			     काष्ठा dcb_peer_app_info *info, u16 *app_count)
अणु
	काष्ठा fw_port_cmd pcmd;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक i, err = 0;

	अगर (!cxgb4_dcb_state_synced(pi->dcb.state))
		वापस 1;

	info->willing = 0;
	info->error = 0;

	*app_count = 0;
	क्रम (i = 0; i < CXGB4_MAX_DCBX_APP_SUPPORTED; i++) अणु
		INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);
		pcmd.u.dcb.app_priority.type = FW_PORT_DCB_TYPE_APP_ID;
		pcmd.u.dcb.app_priority.idx = *app_count;
		err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);

		अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
			dev_err(adap->pdev_dev, "DCB app table read failed with %d\n",
				-err);
			वापस err;
		पूर्ण

		/* find first empty slot */
		अगर (!pcmd.u.dcb.app_priority.protocolid)
			अवरोध;
	पूर्ण
	*app_count = i;
	वापस err;
पूर्ण

अटल पूर्णांक cxgb4_getpeerapp_tbl(काष्ठा net_device *dev, काष्ठा dcb_app *table)
अणु
	काष्ठा fw_port_cmd pcmd;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक i, err = 0;

	अगर (!cxgb4_dcb_state_synced(pi->dcb.state))
		वापस 1;

	क्रम (i = 0; i < CXGB4_MAX_DCBX_APP_SUPPORTED; i++) अणु
		INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);
		pcmd.u.dcb.app_priority.type = FW_PORT_DCB_TYPE_APP_ID;
		pcmd.u.dcb.app_priority.idx = i;
		err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);

		अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
			dev_err(adap->pdev_dev, "DCB app table read failed with %d\n",
				-err);
			वापस err;
		पूर्ण

		/* find first empty slot */
		अगर (!pcmd.u.dcb.app_priority.protocolid)
			अवरोध;

		table[i].selector = (pcmd.u.dcb.app_priority.sel_field + 1);
		table[i].protocol =
			be16_to_cpu(pcmd.u.dcb.app_priority.protocolid);
		table[i].priority =
			ffs(pcmd.u.dcb.app_priority.user_prio_map) - 1;
	पूर्ण
	वापस err;
पूर्ण

/* Return Priority Group inक्रमmation.
 */
अटल पूर्णांक cxgb4_cee_peer_getpg(काष्ठा net_device *dev, काष्ठा cee_pg *pg)
अणु
	काष्ठा fw_port_cmd pcmd;
	काष्ठा port_info *pi = netdev2pinfo(dev);
	काष्ठा adapter *adap = pi->adapter;
	u32 pgid;
	पूर्णांक i, err;

	/* We're always "willing" -- the Switch Fabric always dictates the
	 * DCBX parameters to us.
	 */
	pg->willing = true;

	INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);
	pcmd.u.dcb.pgid.type = FW_PORT_DCB_TYPE_PGID;
	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGID failed with %d\n", -err);
		वापस err;
	पूर्ण
	pgid = be32_to_cpu(pcmd.u.dcb.pgid.pgid);

	क्रम (i = 0; i < CXGB4_MAX_PRIORITY; i++)
		pg->prio_pg[7 - i] = (pgid >> (i * 4)) & 0xF;

	INIT_PORT_DCB_READ_PEER_CMD(pcmd, pi->port_id);
	pcmd.u.dcb.pgrate.type = FW_PORT_DCB_TYPE_PGRATE;
	err = t4_wr_mbox(adap, adap->mbox, &pcmd, माप(pcmd), &pcmd);
	अगर (err != FW_PORT_DCB_CFG_SUCCESS) अणु
		dev_err(adap->pdev_dev, "DCB read PGRATE failed with %d\n",
			-err);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < CXGB4_MAX_PRIORITY; i++)
		pg->pg_bw[i] = pcmd.u.dcb.pgrate.pgrate[i];

	pg->tcs_supported = pcmd.u.dcb.pgrate.num_tcs_supported;

	वापस 0;
पूर्ण

/* Return Priority Flow Control inक्रमmation.
 */
अटल पूर्णांक cxgb4_cee_peer_getpfc(काष्ठा net_device *dev, काष्ठा cee_pfc *pfc)
अणु
	काष्ठा port_info *pi = netdev2pinfo(dev);

	cxgb4_getnumtcs(dev, DCB_NUMTCS_ATTR_PFC, &(pfc->tcs_supported));

	/* Firmware sends this to us in a क्रमmwat that is a bit flipped version
	 * of spec, correct it beक्रमe we send it to host. This is taken care of
	 * by bit shअगरting in other uses of pfcen
	 */
	pfc->pfc_en = bitswap_1(pi->dcb.pfcen);

	pfc->tcs_supported = pi->dcb.pfc_num_tcs_supported;

	वापस 0;
पूर्ण

स्थिर काष्ठा dcbnl_rtnl_ops cxgb4_dcb_ops = अणु
	.ieee_getets		= cxgb4_ieee_get_ets,
	.ieee_getpfc		= cxgb4_ieee_get_pfc,
	.ieee_getapp		= cxgb4_ieee_getapp,
	.ieee_setapp		= cxgb4_ieee_setapp,
	.ieee_peer_getets	= cxgb4_ieee_peer_ets,
	.ieee_peer_getpfc	= cxgb4_ieee_get_pfc,

	/* CEE std */
	.माला_लोtate		= cxgb4_माला_लोtate,
	.setstate		= cxgb4_setstate,
	.getpgtccfgtx		= cxgb4_getpgtccfg_tx,
	.getpgbwgcfgtx		= cxgb4_getpgbwgcfg_tx,
	.getpgtccfgrx		= cxgb4_getpgtccfg_rx,
	.getpgbwgcfgrx		= cxgb4_getpgbwgcfg_rx,
	.setpgtccfgtx		= cxgb4_setpgtccfg_tx,
	.setpgbwgcfgtx		= cxgb4_setpgbwgcfg_tx,
	.setpfccfg		= cxgb4_setpfccfg,
	.getpfccfg		= cxgb4_getpfccfg,
	.setall			= cxgb4_setall,
	.अ_लोap			= cxgb4_अ_लोap,
	.getnumtcs		= cxgb4_getnumtcs,
	.setnumtcs		= cxgb4_setnumtcs,
	.getpfcstate		= cxgb4_getpfcstate,
	.setpfcstate		= cxgb4_setpfcstate,
	.getapp			= cxgb4_getapp,
	.setapp			= cxgb4_setapp,

	/* DCBX configuration */
	.getdcbx		= cxgb4_getdcbx,
	.setdcbx		= cxgb4_setdcbx,

	/* peer apps */
	.peer_getappinfo	= cxgb4_getpeer_app,
	.peer_getapptable	= cxgb4_getpeerapp_tbl,

	/* CEE peer */
	.cee_peer_getpg		= cxgb4_cee_peer_getpg,
	.cee_peer_getpfc	= cxgb4_cee_peer_getpfc,
पूर्ण;
