<शैली गुरु>
/* bnx2x_sriov.c: QLogic Everest network driver.
 *
 * Copyright 2009-2013 Broadcom Corporation
 * Copyright 2014 QLogic Corporation
 * All rights reserved
 *
 * Unless you and QLogic execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2, available
 * at http://www.gnu.org/licenses/old-licenses/gpl-2.0.hपंचांगl (the "GPL").
 *
 * Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other QLogic software provided under a
 * license other than the GPL, without QLogic's express prior written
 * consent.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Shmulik Ravid
 *	       Ariel Elior <ariel.elior@qlogic.com>
 *
 */
#समावेश "bnx2x.h"
#समावेश "bnx2x_init.h"
#समावेश "bnx2x_cmn.h"
#समावेश "bnx2x_sp.h"
#समावेश <linux/crc32.h>
#समावेश <linux/अगर_vlan.h>

अटल पूर्णांक bnx2x_vf_op_prep(काष्ठा bnx2x *bp, पूर्णांक vfidx,
			    काष्ठा bnx2x_virtf **vf,
			    काष्ठा pf_vf_bulletin_content **bulletin,
			    bool test_queue);

/* General service functions */
अटल व्योम storm_स_रखो_vf_to_pf(काष्ठा bnx2x *bp, u16 असल_fid,
					 u16 pf_id)
अणु
	REG_WR8(bp, BAR_XSTRORM_INTMEM + XSTORM_VF_TO_PF_OFFSET(असल_fid),
		pf_id);
	REG_WR8(bp, BAR_CSTRORM_INTMEM + CSTORM_VF_TO_PF_OFFSET(असल_fid),
		pf_id);
	REG_WR8(bp, BAR_TSTRORM_INTMEM + TSTORM_VF_TO_PF_OFFSET(असल_fid),
		pf_id);
	REG_WR8(bp, BAR_USTRORM_INTMEM + USTORM_VF_TO_PF_OFFSET(असल_fid),
		pf_id);
पूर्ण

अटल व्योम storm_स_रखो_func_en(काष्ठा bnx2x *bp, u16 असल_fid,
					u8 enable)
अणु
	REG_WR8(bp, BAR_XSTRORM_INTMEM + XSTORM_FUNC_EN_OFFSET(असल_fid),
		enable);
	REG_WR8(bp, BAR_CSTRORM_INTMEM + CSTORM_FUNC_EN_OFFSET(असल_fid),
		enable);
	REG_WR8(bp, BAR_TSTRORM_INTMEM + TSTORM_FUNC_EN_OFFSET(असल_fid),
		enable);
	REG_WR8(bp, BAR_USTRORM_INTMEM + USTORM_FUNC_EN_OFFSET(असल_fid),
		enable);
पूर्ण

पूर्णांक bnx2x_vf_idx_by_असल_fid(काष्ठा bnx2x *bp, u16 असल_vfid)
अणु
	पूर्णांक idx;

	क्रम_each_vf(bp, idx)
		अगर (bnx2x_vf(bp, idx, असल_vfid) == असल_vfid)
			अवरोध;
	वापस idx;
पूर्ण

अटल
काष्ठा bnx2x_virtf *bnx2x_vf_by_असल_fid(काष्ठा bnx2x *bp, u16 असल_vfid)
अणु
	u16 idx =  (u16)bnx2x_vf_idx_by_असल_fid(bp, असल_vfid);
	वापस (idx < BNX2X_NR_VIRTFN(bp)) ? BP_VF(bp, idx) : शून्य;
पूर्ण

अटल व्योम bnx2x_vf_igu_ack_sb(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				u8 igu_sb_id, u8 segment, u16 index, u8 op,
				u8 update)
अणु
	/* acking a VF sb through the PF - use the GRC */
	u32 ctl;
	u32 igu_addr_data = IGU_REG_COMMAND_REG_32LSB_DATA;
	u32 igu_addr_ctl = IGU_REG_COMMAND_REG_CTRL;
	u32 func_encode = vf->असल_vfid;
	u32 addr_encode = IGU_CMD_E2_PROD_UPD_BASE + igu_sb_id;
	काष्ठा igu_regular cmd_data = अणु0पूर्ण;

	cmd_data.sb_id_and_flags =
			((index << IGU_REGULAR_SB_INDEX_SHIFT) |
			 (segment << IGU_REGULAR_SEGMENT_ACCESS_SHIFT) |
			 (update << IGU_REGULAR_BUPDATE_SHIFT) |
			 (op << IGU_REGULAR_ENABLE_INT_SHIFT));

	ctl = addr_encode << IGU_CTRL_REG_ADDRESS_SHIFT		|
	      func_encode << IGU_CTRL_REG_FID_SHIFT		|
	      IGU_CTRL_CMD_TYPE_WR << IGU_CTRL_REG_TYPE_SHIFT;

	DP(NETIF_MSG_HW, "write 0x%08x to IGU(via GRC) addr 0x%x\n",
	   cmd_data.sb_id_and_flags, igu_addr_data);
	REG_WR(bp, igu_addr_data, cmd_data.sb_id_and_flags);
	barrier();

	DP(NETIF_MSG_HW, "write 0x%08x to IGU(via GRC) addr 0x%x\n",
	   ctl, igu_addr_ctl);
	REG_WR(bp, igu_addr_ctl, ctl);
	barrier();
पूर्ण

अटल bool bnx2x_validate_vf_sp_objs(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_virtf *vf,
				       bool prपूर्णांक_err)
अणु
	अगर (!bnx2x_leading_vfq(vf, sp_initialized)) अणु
		अगर (prपूर्णांक_err)
			BNX2X_ERR("Slowpath objects not yet initialized!\n");
		अन्यथा
			DP(BNX2X_MSG_IOV, "Slowpath objects not yet initialized!\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* VFOP operations states */
व्योम bnx2x_vfop_qctor_dump_tx(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			      काष्ठा bnx2x_queue_init_params *init_params,
			      काष्ठा bnx2x_queue_setup_params *setup_params,
			      u16 q_idx, u16 sb_idx)
अणु
	DP(BNX2X_MSG_IOV,
	   "VF[%d] Q_SETUP: txq[%d]-- vfsb=%d, sb-index=%d, hc-rate=%d, flags=0x%lx, traffic-type=%d",
	   vf->असल_vfid,
	   q_idx,
	   sb_idx,
	   init_params->tx.sb_cq_index,
	   init_params->tx.hc_rate,
	   setup_params->flags,
	   setup_params->txq_params.traffic_type);
पूर्ण

व्योम bnx2x_vfop_qctor_dump_rx(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			    काष्ठा bnx2x_queue_init_params *init_params,
			    काष्ठा bnx2x_queue_setup_params *setup_params,
			    u16 q_idx, u16 sb_idx)
अणु
	काष्ठा bnx2x_rxq_setup_params *rxq_params = &setup_params->rxq_params;

	DP(BNX2X_MSG_IOV, "VF[%d] Q_SETUP: rxq[%d]-- vfsb=%d, sb-index=%d, hc-rate=%d, mtu=%d, buf-size=%d\n"
	   "sge-size=%d, max_sge_pkt=%d, tpa-agg-size=%d, flags=0x%lx, drop-flags=0x%x, cache-log=%d\n",
	   vf->असल_vfid,
	   q_idx,
	   sb_idx,
	   init_params->rx.sb_cq_index,
	   init_params->rx.hc_rate,
	   setup_params->gen_params.mtu,
	   rxq_params->buf_sz,
	   rxq_params->sge_buf_sz,
	   rxq_params->max_sges_pkt,
	   rxq_params->tpa_agg_sz,
	   setup_params->flags,
	   rxq_params->drop_flags,
	   rxq_params->cache_line_log);
पूर्ण

व्योम bnx2x_vfop_qctor_prep(काष्ठा bnx2x *bp,
			   काष्ठा bnx2x_virtf *vf,
			   काष्ठा bnx2x_vf_queue *q,
			   काष्ठा bnx2x_vf_queue_स्थिरruct_params *p,
			   अचिन्हित दीर्घ q_type)
अणु
	काष्ठा bnx2x_queue_init_params *init_p = &p->qstate.params.init;
	काष्ठा bnx2x_queue_setup_params *setup_p = &p->prep_qsetup;

	/* INIT */

	/* Enable host coalescing in the transition to INIT state */
	अगर (test_bit(BNX2X_Q_FLG_HC, &init_p->rx.flags))
		__set_bit(BNX2X_Q_FLG_HC_EN, &init_p->rx.flags);

	अगर (test_bit(BNX2X_Q_FLG_HC, &init_p->tx.flags))
		__set_bit(BNX2X_Q_FLG_HC_EN, &init_p->tx.flags);

	/* FW SB ID */
	init_p->rx.fw_sb_id = vf_igu_sb(vf, q->sb_idx);
	init_p->tx.fw_sb_id = vf_igu_sb(vf, q->sb_idx);

	/* context */
	init_p->cxts[0] = q->cxt;

	/* SETUP */

	/* Setup-op general parameters */
	setup_p->gen_params.spcl_id = vf->sp_cl_id;
	setup_p->gen_params.stat_id = vfq_stat_id(vf, q);
	setup_p->gen_params.fp_hsi = vf->fp_hsi;

	/* Setup-op flags:
	 * collect statistics, zero statistics, local-चयनing, security,
	 * OV क्रम Flex10, RSS and MCAST क्रम leading
	 */
	अगर (test_bit(BNX2X_Q_FLG_STATS, &setup_p->flags))
		__set_bit(BNX2X_Q_FLG_ZERO_STATS, &setup_p->flags);

	/* क्रम VFs, enable tx चयनing, bd coherency, and mac address
	 * anti-spoofing
	 */
	__set_bit(BNX2X_Q_FLG_TX_SWITCH, &setup_p->flags);
	__set_bit(BNX2X_Q_FLG_TX_SEC, &setup_p->flags);
	अगर (vf->spoofchk)
		__set_bit(BNX2X_Q_FLG_ANTI_SPOOF, &setup_p->flags);
	अन्यथा
		__clear_bit(BNX2X_Q_FLG_ANTI_SPOOF, &setup_p->flags);

	/* Setup-op rx parameters */
	अगर (test_bit(BNX2X_Q_TYPE_HAS_RX, &q_type)) अणु
		काष्ठा bnx2x_rxq_setup_params *rxq_p = &setup_p->rxq_params;

		rxq_p->cl_qzone_id = vfq_qzone_id(vf, q);
		rxq_p->fw_sb_id = vf_igu_sb(vf, q->sb_idx);
		rxq_p->rss_engine_id = FW_VF_HANDLE(vf->असल_vfid);

		अगर (test_bit(BNX2X_Q_FLG_TPA, &setup_p->flags))
			rxq_p->max_tpa_queues = BNX2X_VF_MAX_TPA_AGG_QUEUES;
	पूर्ण

	/* Setup-op tx parameters */
	अगर (test_bit(BNX2X_Q_TYPE_HAS_TX, &q_type)) अणु
		setup_p->txq_params.tss_leading_cl_id = vf->leading_rss;
		setup_p->txq_params.fw_sb_id = vf_igu_sb(vf, q->sb_idx);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_vf_queue_create(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_virtf *vf, पूर्णांक qid,
				 काष्ठा bnx2x_vf_queue_स्थिरruct_params *qctor)
अणु
	काष्ठा bnx2x_queue_state_params *q_params;
	पूर्णांक rc = 0;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->असल_vfid, qid);

	/* Prepare ramrod inक्रमmation */
	q_params = &qctor->qstate;
	q_params->q_obj = &bnx2x_vfq(vf, qid, sp_obj);
	set_bit(RAMROD_COMP_WAIT, &q_params->ramrod_flags);

	अगर (bnx2x_get_q_logical_state(bp, q_params->q_obj) ==
	    BNX2X_Q_LOGICAL_STATE_ACTIVE) अणु
		DP(BNX2X_MSG_IOV, "queue was already up. Aborting gracefully\n");
		जाओ out;
	पूर्ण

	/* Run Queue 'construction' ramrods */
	q_params->cmd = BNX2X_Q_CMD_INIT;
	rc = bnx2x_queue_state_change(bp, q_params);
	अगर (rc)
		जाओ out;

	स_नकल(&q_params->params.setup, &qctor->prep_qsetup,
	       माप(काष्ठा bnx2x_queue_setup_params));
	q_params->cmd = BNX2X_Q_CMD_SETUP;
	rc = bnx2x_queue_state_change(bp, q_params);
	अगर (rc)
		जाओ out;

	/* enable पूर्णांकerrupts */
	bnx2x_vf_igu_ack_sb(bp, vf, vf_igu_sb(vf, bnx2x_vfq(vf, qid, sb_idx)),
			    USTORM_ID, 0, IGU_INT_ENABLE, 0);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_vf_queue_destroy(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				  पूर्णांक qid)
अणु
	क्रमागत bnx2x_queue_cmd cmds[] = अणुBNX2X_Q_CMD_HALT,
				       BNX2X_Q_CMD_TERMINATE,
				       BNX2X_Q_CMD_CFC_DELपूर्ण;
	काष्ठा bnx2x_queue_state_params q_params;
	पूर्णांक rc, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->असल_vfid);

	/* Prepare ramrod inक्रमmation */
	स_रखो(&q_params, 0, माप(काष्ठा bnx2x_queue_state_params));
	q_params.q_obj = &bnx2x_vfq(vf, qid, sp_obj);
	set_bit(RAMROD_COMP_WAIT, &q_params.ramrod_flags);

	अगर (bnx2x_get_q_logical_state(bp, q_params.q_obj) ==
	    BNX2X_Q_LOGICAL_STATE_STOPPED) अणु
		DP(BNX2X_MSG_IOV, "queue was already stopped. Aborting gracefully\n");
		जाओ out;
	पूर्ण

	/* Run Queue 'destruction' ramrods */
	क्रम (i = 0; i < ARRAY_SIZE(cmds); i++) अणु
		q_params.cmd = cmds[i];
		rc = bnx2x_queue_state_change(bp, &q_params);
		अगर (rc) अणु
			BNX2X_ERR("Failed to run Queue command %d\n", cmds[i]);
			वापस rc;
		पूर्ण
	पूर्ण
out:
	/* Clean Context */
	अगर (bnx2x_vfq(vf, qid, cxt)) अणु
		bnx2x_vfq(vf, qid, cxt)->ustorm_ag_context.cdu_usage = 0;
		bnx2x_vfq(vf, qid, cxt)->xstorm_ag_context.cdu_reserved = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
bnx2x_vf_set_igu_info(काष्ठा bnx2x *bp, u8 igu_sb_id, u8 असल_vfid)
अणु
	काष्ठा bnx2x_virtf *vf = bnx2x_vf_by_असल_fid(bp, असल_vfid);
	अगर (vf) अणु
		/* the first igu entry beदीर्घing to VFs of this PF */
		अगर (!BP_VFDB(bp)->first_vf_igu_entry)
			BP_VFDB(bp)->first_vf_igu_entry = igu_sb_id;

		/* the first igu entry beदीर्घing to this VF */
		अगर (!vf_sb_count(vf))
			vf->igu_base_id = igu_sb_id;

		++vf_sb_count(vf);
		++vf->sb_count;
	पूर्ण
	BP_VFDB(bp)->vf_sbs_pool++;
पूर्ण

अटल पूर्णांक bnx2x_vf_vlan_mac_clear(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				   पूर्णांक qid, bool drv_only, पूर्णांक type)
अणु
	काष्ठा bnx2x_vlan_mac_ramrod_params ramrod;
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "vf[%d] - deleting all %s\n", vf->असल_vfid,
			  (type == BNX2X_VF_FILTER_VLAN_MAC) ? "VLAN-MACs" :
			  (type == BNX2X_VF_FILTER_MAC) ? "MACs" : "VLANs");

	/* Prepare ramrod params */
	स_रखो(&ramrod, 0, माप(काष्ठा bnx2x_vlan_mac_ramrod_params));
	अगर (type == BNX2X_VF_FILTER_VLAN_MAC) अणु
		set_bit(BNX2X_ETH_MAC, &ramrod.user_req.vlan_mac_flags);
		ramrod.vlan_mac_obj = &bnx2x_vfq(vf, qid, vlan_mac_obj);
	पूर्ण अन्यथा अगर (type == BNX2X_VF_FILTER_MAC) अणु
		set_bit(BNX2X_ETH_MAC, &ramrod.user_req.vlan_mac_flags);
		ramrod.vlan_mac_obj = &bnx2x_vfq(vf, qid, mac_obj);
	पूर्ण अन्यथा अणु
		ramrod.vlan_mac_obj = &bnx2x_vfq(vf, qid, vlan_obj);
	पूर्ण
	ramrod.user_req.cmd = BNX2X_VLAN_MAC_DEL;

	set_bit(RAMROD_EXEC, &ramrod.ramrod_flags);
	अगर (drv_only)
		set_bit(RAMROD_DRV_CLR_ONLY, &ramrod.ramrod_flags);
	अन्यथा
		set_bit(RAMROD_COMP_WAIT, &ramrod.ramrod_flags);

	/* Start deleting */
	rc = ramrod.vlan_mac_obj->delete_all(bp,
					     ramrod.vlan_mac_obj,
					     &ramrod.user_req.vlan_mac_flags,
					     &ramrod.ramrod_flags);
	अगर (rc) अणु
		BNX2X_ERR("Failed to delete all %s\n",
			  (type == BNX2X_VF_FILTER_VLAN_MAC) ? "VLAN-MACs" :
			  (type == BNX2X_VF_FILTER_MAC) ? "MACs" : "VLANs");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_vf_mac_vlan_config(काष्ठा bnx2x *bp,
				    काष्ठा bnx2x_virtf *vf, पूर्णांक qid,
				    काष्ठा bnx2x_vf_mac_vlan_filter *filter,
				    bool drv_only)
अणु
	काष्ठा bnx2x_vlan_mac_ramrod_params ramrod;
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "vf[%d] - %s a %s filter\n",
	   vf->असल_vfid, filter->add ? "Adding" : "Deleting",
	   (filter->type == BNX2X_VF_FILTER_VLAN_MAC) ? "VLAN-MAC" :
	   (filter->type == BNX2X_VF_FILTER_MAC) ? "MAC" : "VLAN");

	/* Prepare ramrod params */
	स_रखो(&ramrod, 0, माप(काष्ठा bnx2x_vlan_mac_ramrod_params));
	अगर (filter->type == BNX2X_VF_FILTER_VLAN_MAC) अणु
		ramrod.vlan_mac_obj = &bnx2x_vfq(vf, qid, vlan_mac_obj);
		ramrod.user_req.u.vlan.vlan = filter->vid;
		स_नकल(&ramrod.user_req.u.mac.mac, filter->mac, ETH_ALEN);
		set_bit(BNX2X_ETH_MAC, &ramrod.user_req.vlan_mac_flags);
	पूर्ण अन्यथा अगर (filter->type == BNX2X_VF_FILTER_VLAN) अणु
		ramrod.vlan_mac_obj = &bnx2x_vfq(vf, qid, vlan_obj);
		ramrod.user_req.u.vlan.vlan = filter->vid;
	पूर्ण अन्यथा अणु
		set_bit(BNX2X_ETH_MAC, &ramrod.user_req.vlan_mac_flags);
		ramrod.vlan_mac_obj = &bnx2x_vfq(vf, qid, mac_obj);
		स_नकल(&ramrod.user_req.u.mac.mac, filter->mac, ETH_ALEN);
	पूर्ण
	ramrod.user_req.cmd = filter->add ? BNX2X_VLAN_MAC_ADD :
					    BNX2X_VLAN_MAC_DEL;

	set_bit(RAMROD_EXEC, &ramrod.ramrod_flags);
	अगर (drv_only)
		set_bit(RAMROD_DRV_CLR_ONLY, &ramrod.ramrod_flags);
	अन्यथा
		set_bit(RAMROD_COMP_WAIT, &ramrod.ramrod_flags);

	/* Add/Remove the filter */
	rc = bnx2x_config_vlan_mac(bp, &ramrod);
	अगर (rc == -EEXIST)
		वापस 0;
	अगर (rc) अणु
		BNX2X_ERR("Failed to %s %s\n",
			  filter->add ? "add" : "delete",
			  (filter->type == BNX2X_VF_FILTER_VLAN_MAC) ?
				"VLAN-MAC" :
			  (filter->type == BNX2X_VF_FILTER_MAC) ?
				"MAC" : "VLAN");
		वापस rc;
	पूर्ण

	filter->applied = true;

	वापस 0;
पूर्ण

पूर्णांक bnx2x_vf_mac_vlan_config_list(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				  काष्ठा bnx2x_vf_mac_vlan_filters *filters,
				  पूर्णांक qid, bool drv_only)
अणु
	पूर्णांक rc = 0, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->असल_vfid);

	अगर (!bnx2x_validate_vf_sp_objs(bp, vf, true))
		वापस -EINVAL;

	/* Prepare ramrod params */
	क्रम (i = 0; i < filters->count; i++) अणु
		rc = bnx2x_vf_mac_vlan_config(bp, vf, qid,
					      &filters->filters[i], drv_only);
		अगर (rc)
			अवरोध;
	पूर्ण

	/* Rollback अगर needed */
	अगर (i != filters->count) अणु
		BNX2X_ERR("Managed only %d/%d filters - rolling back\n",
			  i, filters->count);
		जबतक (--i >= 0) अणु
			अगर (!filters->filters[i].applied)
				जारी;
			filters->filters[i].add = !filters->filters[i].add;
			bnx2x_vf_mac_vlan_config(bp, vf, qid,
						 &filters->filters[i],
						 drv_only);
		पूर्ण
	पूर्ण

	/* It's our responsibility to मुक्त the filters */
	kमुक्त(filters);

	वापस rc;
पूर्ण

पूर्णांक bnx2x_vf_queue_setup(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf, पूर्णांक qid,
			 काष्ठा bnx2x_vf_queue_स्थिरruct_params *qctor)
अणु
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->असल_vfid, qid);

	rc = bnx2x_vf_queue_create(bp, vf, qid, qctor);
	अगर (rc)
		जाओ op_err;

	/* Schedule the configuration of any pending vlan filters */
	bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_HYPERVISOR_VLAN,
			       BNX2X_MSG_IOV);
	वापस 0;
op_err:
	BNX2X_ERR("QSETUP[%d:%d] error: rc %d\n", vf->असल_vfid, qid, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_vf_queue_flr(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			       पूर्णांक qid)
अणु
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->असल_vfid, qid);

	/* If needed, clean the filtering data base */
	अगर ((qid == LEADING_IDX) &&
	    bnx2x_validate_vf_sp_objs(bp, vf, false)) अणु
		rc = bnx2x_vf_vlan_mac_clear(bp, vf, qid, true,
					     BNX2X_VF_FILTER_VLAN_MAC);
		अगर (rc)
			जाओ op_err;
		rc = bnx2x_vf_vlan_mac_clear(bp, vf, qid, true,
					     BNX2X_VF_FILTER_VLAN);
		अगर (rc)
			जाओ op_err;
		rc = bnx2x_vf_vlan_mac_clear(bp, vf, qid, true,
					     BNX2X_VF_FILTER_MAC);
		अगर (rc)
			जाओ op_err;
	पूर्ण

	/* Terminate queue */
	अगर (bnx2x_vfq(vf, qid, sp_obj).state != BNX2X_Q_STATE_RESET) अणु
		काष्ठा bnx2x_queue_state_params qstate;

		स_रखो(&qstate, 0, माप(काष्ठा bnx2x_queue_state_params));
		qstate.q_obj = &bnx2x_vfq(vf, qid, sp_obj);
		qstate.q_obj->state = BNX2X_Q_STATE_STOPPED;
		qstate.cmd = BNX2X_Q_CMD_TERMINATE;
		set_bit(RAMROD_COMP_WAIT, &qstate.ramrod_flags);
		rc = bnx2x_queue_state_change(bp, &qstate);
		अगर (rc)
			जाओ op_err;
	पूर्ण

	वापस 0;
op_err:
	BNX2X_ERR("vf[%d:%d] error: rc %d\n", vf->असल_vfid, qid, rc);
	वापस rc;
पूर्ण

पूर्णांक bnx2x_vf_mcast(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
		   bnx2x_mac_addr_t *mcasts, पूर्णांक mc_num, bool drv_only)
अणु
	काष्ठा bnx2x_mcast_list_elem *mc = शून्य;
	काष्ठा bnx2x_mcast_ramrod_params mcast;
	पूर्णांक rc, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->असल_vfid);

	/* Prepare Multicast command */
	स_रखो(&mcast, 0, माप(काष्ठा bnx2x_mcast_ramrod_params));
	mcast.mcast_obj = &vf->mcast_obj;
	अगर (drv_only)
		set_bit(RAMROD_DRV_CLR_ONLY, &mcast.ramrod_flags);
	अन्यथा
		set_bit(RAMROD_COMP_WAIT, &mcast.ramrod_flags);
	अगर (mc_num) अणु
		mc = kसुस्मृति(mc_num, माप(काष्ठा bnx2x_mcast_list_elem),
			     GFP_KERNEL);
		अगर (!mc) अणु
			BNX2X_ERR("Cannot Configure multicasts due to lack of memory\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (mc_num) अणु
		INIT_LIST_HEAD(&mcast.mcast_list);
		क्रम (i = 0; i < mc_num; i++) अणु
			mc[i].mac = mcasts[i];
			list_add_tail(&mc[i].link,
				      &mcast.mcast_list);
		पूर्ण

		/* add new mcasts */
		mcast.mcast_list_len = mc_num;
		rc = bnx2x_config_mcast(bp, &mcast, BNX2X_MCAST_CMD_SET);
		अगर (rc)
			BNX2X_ERR("Failed to set multicasts\n");
	पूर्ण अन्यथा अणु
		/* clear existing mcasts */
		rc = bnx2x_config_mcast(bp, &mcast, BNX2X_MCAST_CMD_DEL);
		अगर (rc)
			BNX2X_ERR("Failed to remove multicasts\n");
	पूर्ण

	kमुक्त(mc);

	वापस rc;
पूर्ण

अटल व्योम bnx2x_vf_prep_rx_mode(काष्ठा bnx2x *bp, u8 qid,
				  काष्ठा bnx2x_rx_mode_ramrod_params *ramrod,
				  काष्ठा bnx2x_virtf *vf,
				  अचिन्हित दीर्घ accept_flags)
अणु
	काष्ठा bnx2x_vf_queue *vfq = vfq_get(vf, qid);

	स_रखो(ramrod, 0, माप(*ramrod));
	ramrod->cid = vfq->cid;
	ramrod->cl_id = vfq_cl_id(vf, vfq);
	ramrod->rx_mode_obj = &bp->rx_mode_obj;
	ramrod->func_id = FW_VF_HANDLE(vf->असल_vfid);
	ramrod->rx_accept_flags = accept_flags;
	ramrod->tx_accept_flags = accept_flags;
	ramrod->pstate = &vf->filter_state;
	ramrod->state = BNX2X_FILTER_RX_MODE_PENDING;

	set_bit(BNX2X_FILTER_RX_MODE_PENDING, &vf->filter_state);
	set_bit(RAMROD_RX, &ramrod->ramrod_flags);
	set_bit(RAMROD_TX, &ramrod->ramrod_flags);

	ramrod->rdata = bnx2x_vf_sp(bp, vf, rx_mode_rdata.e2);
	ramrod->rdata_mapping = bnx2x_vf_sp_map(bp, vf, rx_mode_rdata.e2);
पूर्ण

पूर्णांक bnx2x_vf_rxmode(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
		    पूर्णांक qid, अचिन्हित दीर्घ accept_flags)
अणु
	काष्ठा bnx2x_rx_mode_ramrod_params ramrod;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->असल_vfid);

	bnx2x_vf_prep_rx_mode(bp, qid, &ramrod, vf, accept_flags);
	set_bit(RAMROD_COMP_WAIT, &ramrod.ramrod_flags);
	vfq_get(vf, qid)->accept_flags = ramrod.rx_accept_flags;
	वापस bnx2x_config_rx_mode(bp, &ramrod);
पूर्ण

पूर्णांक bnx2x_vf_queue_tearकरोwn(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf, पूर्णांक qid)
अणु
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "vf[%d:%d]\n", vf->असल_vfid, qid);

	/* Remove all classअगरication configuration क्रम leading queue */
	अगर (qid == LEADING_IDX) अणु
		rc = bnx2x_vf_rxmode(bp, vf, qid, 0);
		अगर (rc)
			जाओ op_err;

		/* Remove filtering अगर feasible */
		अगर (bnx2x_validate_vf_sp_objs(bp, vf, true)) अणु
			rc = bnx2x_vf_vlan_mac_clear(bp, vf, qid,
						     false,
						     BNX2X_VF_FILTER_VLAN_MAC);
			अगर (rc)
				जाओ op_err;
			rc = bnx2x_vf_vlan_mac_clear(bp, vf, qid,
						     false,
						     BNX2X_VF_FILTER_VLAN);
			अगर (rc)
				जाओ op_err;
			rc = bnx2x_vf_vlan_mac_clear(bp, vf, qid,
						     false,
						     BNX2X_VF_FILTER_MAC);
			अगर (rc)
				जाओ op_err;
			rc = bnx2x_vf_mcast(bp, vf, शून्य, 0, false);
			अगर (rc)
				जाओ op_err;
		पूर्ण
	पूर्ण

	/* Destroy queue */
	rc = bnx2x_vf_queue_destroy(bp, vf, qid);
	अगर (rc)
		जाओ op_err;
	वापस rc;
op_err:
	BNX2X_ERR("vf[%d:%d] error: rc %d\n",
		  vf->असल_vfid, qid, rc);
	वापस rc;
पूर्ण

/* VF enable primitives
 * when pretend is required the caller is responsible
 * क्रम calling pretend prior to calling these routines
 */

/* पूर्णांकernal vf enable - until vf is enabled पूर्णांकernally all transactions
 * are blocked. This routine should always be called last with pretend.
 */
अटल व्योम bnx2x_vf_enable_पूर्णांकernal(काष्ठा bnx2x *bp, u8 enable)
अणु
	REG_WR(bp, PGLUE_B_REG_INTERNAL_VFID_ENABLE, enable ? 1 : 0);
पूर्ण

/* clears vf error in all semi blocks */
अटल व्योम bnx2x_vf_semi_clear_err(काष्ठा bnx2x *bp, u8 असल_vfid)
अणु
	REG_WR(bp, TSEM_REG_VFPF_ERR_NUM, असल_vfid);
	REG_WR(bp, USEM_REG_VFPF_ERR_NUM, असल_vfid);
	REG_WR(bp, CSEM_REG_VFPF_ERR_NUM, असल_vfid);
	REG_WR(bp, XSEM_REG_VFPF_ERR_NUM, असल_vfid);
पूर्ण

अटल व्योम bnx2x_vf_pglue_clear_err(काष्ठा bnx2x *bp, u8 असल_vfid)
अणु
	u32 was_err_group = (2 * BP_PATH(bp) + असल_vfid) >> 5;
	u32 was_err_reg = 0;

	चयन (was_err_group) अणु
	हाल 0:
	    was_err_reg = PGLUE_B_REG_WAS_ERROR_VF_31_0_CLR;
	    अवरोध;
	हाल 1:
	    was_err_reg = PGLUE_B_REG_WAS_ERROR_VF_63_32_CLR;
	    अवरोध;
	हाल 2:
	    was_err_reg = PGLUE_B_REG_WAS_ERROR_VF_95_64_CLR;
	    अवरोध;
	हाल 3:
	    was_err_reg = PGLUE_B_REG_WAS_ERROR_VF_127_96_CLR;
	    अवरोध;
	पूर्ण
	REG_WR(bp, was_err_reg, 1 << (असल_vfid & 0x1f));
पूर्ण

अटल व्योम bnx2x_vf_igu_reset(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	पूर्णांक i;
	u32 val;

	/* Set VF masks and configuration - pretend */
	bnx2x_pretend_func(bp, HW_VF_HANDLE(bp, vf->असल_vfid));

	REG_WR(bp, IGU_REG_SB_INT_BEFORE_MASK_LSB, 0);
	REG_WR(bp, IGU_REG_SB_INT_BEFORE_MASK_MSB, 0);
	REG_WR(bp, IGU_REG_SB_MASK_LSB, 0);
	REG_WR(bp, IGU_REG_SB_MASK_MSB, 0);
	REG_WR(bp, IGU_REG_PBA_STATUS_LSB, 0);
	REG_WR(bp, IGU_REG_PBA_STATUS_MSB, 0);

	val = REG_RD(bp, IGU_REG_VF_CONFIGURATION);
	val |= (IGU_VF_CONF_FUNC_EN | IGU_VF_CONF_MSI_MSIX_EN);
	val &= ~IGU_VF_CONF_PARENT_MASK;
	val |= (BP_ABS_FUNC(bp) >> 1) << IGU_VF_CONF_PARENT_SHIFT;
	REG_WR(bp, IGU_REG_VF_CONFIGURATION, val);

	DP(BNX2X_MSG_IOV,
	   "value in IGU_REG_VF_CONFIGURATION of vf %d after write is 0x%08x\n",
	   vf->असल_vfid, val);

	bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));

	/* iterate over all queues, clear sb consumer */
	क्रम (i = 0; i < vf_sb_count(vf); i++) अणु
		u8 igu_sb_id = vf_igu_sb(vf, i);

		/* zero prod memory */
		REG_WR(bp, IGU_REG_PROD_CONS_MEMORY + igu_sb_id * 4, 0);

		/* clear sb state machine */
		bnx2x_igu_clear_sb_gen(bp, vf->असल_vfid, igu_sb_id,
				       false /* VF */);

		/* disable + update */
		bnx2x_vf_igu_ack_sb(bp, vf, igu_sb_id, USTORM_ID, 0,
				    IGU_INT_DISABLE, 1);
	पूर्ण
पूर्ण

व्योम bnx2x_vf_enable_access(काष्ठा bnx2x *bp, u8 असल_vfid)
अणु
	/* set the VF-PF association in the FW */
	storm_स_रखो_vf_to_pf(bp, FW_VF_HANDLE(असल_vfid), BP_FUNC(bp));
	storm_स_रखो_func_en(bp, FW_VF_HANDLE(असल_vfid), 1);

	/* clear vf errors*/
	bnx2x_vf_semi_clear_err(bp, असल_vfid);
	bnx2x_vf_pglue_clear_err(bp, असल_vfid);

	/* पूर्णांकernal vf-enable - pretend */
	bnx2x_pretend_func(bp, HW_VF_HANDLE(bp, असल_vfid));
	DP(BNX2X_MSG_IOV, "enabling internal access for vf %x\n", असल_vfid);
	bnx2x_vf_enable_पूर्णांकernal(bp, true);
	bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));
पूर्ण

अटल व्योम bnx2x_vf_enable_traffic(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	/* Reset vf in IGU  पूर्णांकerrupts are still disabled */
	bnx2x_vf_igu_reset(bp, vf);

	/* pretend to enable the vf with the PBF */
	bnx2x_pretend_func(bp, HW_VF_HANDLE(bp, vf->असल_vfid));
	REG_WR(bp, PBF_REG_DISABLE_VF, 0);
	bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));
पूर्ण

अटल u8 bnx2x_vf_is_pcie_pending(काष्ठा bnx2x *bp, u8 असल_vfid)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा bnx2x_virtf *vf = bnx2x_vf_by_असल_fid(bp, असल_vfid);

	अगर (!vf)
		वापस false;

	dev = pci_get_करोमुख्य_bus_and_slot(vf->करोमुख्य, vf->bus, vf->devfn);
	अगर (dev)
		वापस bnx2x_is_pcie_pending(dev);
	वापस false;
पूर्ण

पूर्णांक bnx2x_vf_flr_clnup_epilog(काष्ठा bnx2x *bp, u8 असल_vfid)
अणु
	/* Verअगरy no pending pci transactions */
	अगर (bnx2x_vf_is_pcie_pending(bp, असल_vfid))
		BNX2X_ERR("PCIE Transactions still pending\n");

	वापस 0;
पूर्ण

/* must be called after the number of PF queues and the number of VFs are
 * both known
 */
अटल व्योम
bnx2x_iov_अटल_resc(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	काष्ठा vf_pf_resc_request *resc = &vf->alloc_resc;

	/* will be set only during VF-ACQUIRE */
	resc->num_rxqs = 0;
	resc->num_txqs = 0;

	resc->num_mac_filters = VF_MAC_CREDIT_CNT;
	resc->num_vlan_filters = VF_VLAN_CREDIT_CNT;

	/* no real limitation */
	resc->num_mc_filters = 0;

	/* num_sbs alपढ़ोy set */
	resc->num_sbs = vf->sb_count;
पूर्ण

/* FLR routines: */
अटल व्योम bnx2x_vf_मुक्त_resc(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	/* reset the state variables */
	bnx2x_iov_अटल_resc(bp, vf);
	vf->state = VF_FREE;
पूर्ण

अटल व्योम bnx2x_vf_flr_clnup_hw(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	u32 poll_cnt = bnx2x_flr_clnup_poll_count(bp);

	/* DQ usage counter */
	bnx2x_pretend_func(bp, HW_VF_HANDLE(bp, vf->असल_vfid));
	bnx2x_flr_clnup_poll_hw_counter(bp, DORQ_REG_VF_USAGE_CNT,
					"DQ VF usage counter timed out",
					poll_cnt);
	bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));

	/* FW cleanup command - poll क्रम the results */
	अगर (bnx2x_send_final_clnup(bp, (u8)FW_VF_HANDLE(vf->असल_vfid),
				   poll_cnt))
		BNX2X_ERR("VF[%d] Final cleanup timed-out\n", vf->असल_vfid);

	/* verअगरy TX hw is flushed */
	bnx2x_tx_hw_flushed(bp, poll_cnt);
पूर्ण

अटल व्योम bnx2x_vf_flr(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	पूर्णांक rc, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->असल_vfid);

	/* the cleanup operations are valid अगर and only अगर the VF
	 * was first acquired.
	 */
	क्रम (i = 0; i < vf_rxq_count(vf); i++) अणु
		rc = bnx2x_vf_queue_flr(bp, vf, i);
		अगर (rc)
			जाओ out;
	पूर्ण

	/* हटाओ multicasts */
	bnx2x_vf_mcast(bp, vf, शून्य, 0, true);

	/* dispatch final cleanup and रुको क्रम HW queues to flush */
	bnx2x_vf_flr_clnup_hw(bp, vf);

	/* release VF resources */
	bnx2x_vf_मुक्त_resc(bp, vf);

	vf->malicious = false;

	/* re-खोलो the mailbox */
	bnx2x_vf_enable_mbx(bp, vf->असल_vfid);
	वापस;
out:
	BNX2X_ERR("vf[%d:%d] failed flr: rc %d\n",
		  vf->असल_vfid, i, rc);
पूर्ण

अटल व्योम bnx2x_vf_flr_clnup(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_virtf *vf;
	पूर्णांक i;

	क्रम (i = 0; i < BNX2X_NR_VIRTFN(bp); i++) अणु
		/* VF should be RESET & in FLR cleanup states */
		अगर (bnx2x_vf(bp, i, state) != VF_RESET ||
		    !bnx2x_vf(bp, i, flr_clnup_stage))
			जारी;

		DP(BNX2X_MSG_IOV, "next vf to cleanup: %d. Num of vfs: %d\n",
		   i, BNX2X_NR_VIRTFN(bp));

		vf = BP_VF(bp, i);

		/* lock the vf pf channel */
		bnx2x_lock_vf_pf_channel(bp, vf, CHANNEL_TLV_FLR);

		/* invoke the VF FLR SM */
		bnx2x_vf_flr(bp, vf);

		/* mark the VF to be ACKED and जारी */
		vf->flr_clnup_stage = false;
		bnx2x_unlock_vf_pf_channel(bp, vf, CHANNEL_TLV_FLR);
	पूर्ण

	/* Acknowledge the handled VFs.
	 * we are acknowledge all the vfs which an flr was requested क्रम, even
	 * अगर amongst them there are such that we never खोलोed, since the mcp
	 * will पूर्णांकerrupt us immediately again अगर we only ack some of the bits,
	 * resulting in an endless loop. This can happen क्रम example in KVM
	 * where an 'all ones' flr request is someबार given by hyper visor
	 */
	DP(BNX2X_MSG_MCP, "DRV_STATUS_VF_DISABLED ACK for vfs 0x%x 0x%x\n",
	   bp->vfdb->flrd_vfs[0], bp->vfdb->flrd_vfs[1]);
	क्रम (i = 0; i < FLRD_VFS_DWORDS; i++)
		SHMEM2_WR(bp, drv_ack_vf_disabled[BP_FW_MB_IDX(bp)][i],
			  bp->vfdb->flrd_vfs[i]);

	bnx2x_fw_command(bp, DRV_MSG_CODE_VF_DISABLED_DONE, 0);

	/* clear the acked bits - better yet अगर the MCP implemented
	 * ग_लिखो to clear semantics
	 */
	क्रम (i = 0; i < FLRD_VFS_DWORDS; i++)
		SHMEM2_WR(bp, drv_ack_vf_disabled[BP_FW_MB_IDX(bp)][i], 0);
पूर्ण

व्योम bnx2x_vf_handle_flr_event(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	/* Read FLR'd VFs */
	क्रम (i = 0; i < FLRD_VFS_DWORDS; i++)
		bp->vfdb->flrd_vfs[i] = SHMEM2_RD(bp, mcp_vf_disabled[i]);

	DP(BNX2X_MSG_MCP,
	   "DRV_STATUS_VF_DISABLED received for vfs 0x%x 0x%x\n",
	   bp->vfdb->flrd_vfs[0], bp->vfdb->flrd_vfs[1]);

	क्रम_each_vf(bp, i) अणु
		काष्ठा bnx2x_virtf *vf = BP_VF(bp, i);
		u32 reset = 0;

		अगर (vf->असल_vfid < 32)
			reset = bp->vfdb->flrd_vfs[0] & (1 << vf->असल_vfid);
		अन्यथा
			reset = bp->vfdb->flrd_vfs[1] &
				(1 << (vf->असल_vfid - 32));

		अगर (reset) अणु
			/* set as reset and पढ़ोy क्रम cleanup */
			vf->state = VF_RESET;
			vf->flr_clnup_stage = true;

			DP(BNX2X_MSG_IOV,
			   "Initiating Final cleanup for VF %d\n",
			   vf->असल_vfid);
		पूर्ण
	पूर्ण

	/* करो the FLR cleanup क्रम all marked VFs*/
	bnx2x_vf_flr_clnup(bp);
पूर्ण

/* IOV global initialization routines  */
व्योम bnx2x_iov_init_dq(काष्ठा bnx2x *bp)
अणु
	अगर (!IS_SRIOV(bp))
		वापस;

	/* Set the DQ such that the CID reflect the असल_vfid */
	REG_WR(bp, DORQ_REG_VF_NORM_VF_BASE, 0);
	REG_WR(bp, DORQ_REG_MAX_RVFID_SIZE, ilog2(BNX2X_MAX_NUM_OF_VFS));

	/* Set VFs starting CID. If its > 0 the preceding CIDs are beदीर्घ to
	 * the PF L2 queues
	 */
	REG_WR(bp, DORQ_REG_VF_NORM_CID_BASE, BNX2X_FIRST_VF_CID);

	/* The VF winकरोw size is the log2 of the max number of CIDs per VF */
	REG_WR(bp, DORQ_REG_VF_NORM_CID_WND_SIZE, BNX2X_VF_CID_WND);

	/* The VF करोorbell size  0 - *B, 4 - 128B. We set it here to match
	 * the Pf करोorbell size although the 2 are independent.
	 */
	REG_WR(bp, DORQ_REG_VF_NORM_CID_OFST, 3);

	/* No security checks क्रम now -
	 * configure single rule (out of 16) mask = 0x1, value = 0x0,
	 * CID range 0 - 0x1ffff
	 */
	REG_WR(bp, DORQ_REG_VF_TYPE_MASK_0, 1);
	REG_WR(bp, DORQ_REG_VF_TYPE_VALUE_0, 0);
	REG_WR(bp, DORQ_REG_VF_TYPE_MIN_MCID_0, 0);
	REG_WR(bp, DORQ_REG_VF_TYPE_MAX_MCID_0, 0x1ffff);

	/* set the VF करोorbell threshold. This threshold represents the amount
	 * of करोorbells allowed in the मुख्य DORQ fअगरo क्रम a specअगरic VF.
	 */
	REG_WR(bp, DORQ_REG_VF_USAGE_CT_LIMIT, 64);
पूर्ण

व्योम bnx2x_iov_init_dmae(काष्ठा bnx2x *bp)
अणु
	अगर (pci_find_ext_capability(bp->pdev, PCI_EXT_CAP_ID_SRIOV))
		REG_WR(bp, DMAE_REG_BACKWARD_COMP_EN, 0);
पूर्ण

अटल पूर्णांक bnx2x_vf_करोमुख्य(काष्ठा bnx2x *bp, पूर्णांक vfid)
अणु
	काष्ठा pci_dev *dev = bp->pdev;

	वापस pci_करोमुख्य_nr(dev->bus);
पूर्ण

अटल पूर्णांक bnx2x_vf_bus(काष्ठा bnx2x *bp, पूर्णांक vfid)
अणु
	काष्ठा pci_dev *dev = bp->pdev;
	काष्ठा bnx2x_sriov *iov = &bp->vfdb->sriov;

	वापस dev->bus->number + ((dev->devfn + iov->offset +
				    iov->stride * vfid) >> 8);
पूर्ण

अटल पूर्णांक bnx2x_vf_devfn(काष्ठा bnx2x *bp, पूर्णांक vfid)
अणु
	काष्ठा pci_dev *dev = bp->pdev;
	काष्ठा bnx2x_sriov *iov = &bp->vfdb->sriov;

	वापस (dev->devfn + iov->offset + iov->stride * vfid) & 0xff;
पूर्ण

अटल व्योम bnx2x_vf_set_bars(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	पूर्णांक i, n;
	काष्ठा pci_dev *dev = bp->pdev;
	काष्ठा bnx2x_sriov *iov = &bp->vfdb->sriov;

	क्रम (i = 0, n = 0; i < PCI_SRIOV_NUM_BARS; i += 2, n++) अणु
		u64 start = pci_resource_start(dev, PCI_IOV_RESOURCES + i);
		u32 size = pci_resource_len(dev, PCI_IOV_RESOURCES + i);

		size /= iov->total;
		vf->bars[n].bar = start + size * vf->असल_vfid;
		vf->bars[n].size = size;
	पूर्ण
पूर्ण

अटल पूर्णांक
bnx2x_get_vf_igu_cam_info(काष्ठा bnx2x *bp)
अणु
	पूर्णांक sb_id;
	u32 val;
	u8 fid, current_pf = 0;

	/* IGU in normal mode - पढ़ो CAM */
	क्रम (sb_id = 0; sb_id < IGU_REG_MAPPING_MEMORY_SIZE; sb_id++) अणु
		val = REG_RD(bp, IGU_REG_MAPPING_MEMORY + sb_id * 4);
		अगर (!(val & IGU_REG_MAPPING_MEMORY_VALID))
			जारी;
		fid = GET_FIELD((val), IGU_REG_MAPPING_MEMORY_FID);
		अगर (fid & IGU_FID_ENCODE_IS_PF)
			current_pf = fid & IGU_FID_PF_NUM_MASK;
		अन्यथा अगर (current_pf == BP_FUNC(bp))
			bnx2x_vf_set_igu_info(bp, sb_id,
					      (fid & IGU_FID_VF_NUM_MASK));
		DP(BNX2X_MSG_IOV, "%s[%d], igu_sb_id=%d, msix=%d\n",
		   ((fid & IGU_FID_ENCODE_IS_PF) ? "PF" : "VF"),
		   ((fid & IGU_FID_ENCODE_IS_PF) ? (fid & IGU_FID_PF_NUM_MASK) :
		   (fid & IGU_FID_VF_NUM_MASK)), sb_id,
		   GET_FIELD((val), IGU_REG_MAPPING_MEMORY_VECTOR));
	पूर्ण
	DP(BNX2X_MSG_IOV, "vf_sbs_pool is %d\n", BP_VFDB(bp)->vf_sbs_pool);
	वापस BP_VFDB(bp)->vf_sbs_pool;
पूर्ण

अटल व्योम __bnx2x_iov_मुक्त_vfdb(काष्ठा bnx2x *bp)
अणु
	अगर (bp->vfdb) अणु
		kमुक्त(bp->vfdb->vfqs);
		kमुक्त(bp->vfdb->vfs);
		kमुक्त(bp->vfdb);
	पूर्ण
	bp->vfdb = शून्य;
पूर्ण

अटल पूर्णांक bnx2x_sriov_pci_cfg_info(काष्ठा bnx2x *bp, काष्ठा bnx2x_sriov *iov)
अणु
	पूर्णांक pos;
	काष्ठा pci_dev *dev = bp->pdev;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_SRIOV);
	अगर (!pos) अणु
		BNX2X_ERR("failed to find SRIOV capability in device\n");
		वापस -ENODEV;
	पूर्ण

	iov->pos = pos;
	DP(BNX2X_MSG_IOV, "sriov ext pos %d\n", pos);
	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_CTRL, &iov->ctrl);
	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_TOTAL_VF, &iov->total);
	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_INITIAL_VF, &iov->initial);
	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_VF_OFFSET, &iov->offset);
	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_VF_STRIDE, &iov->stride);
	pci_पढ़ो_config_dword(dev, pos + PCI_SRIOV_SUP_PGSIZE, &iov->pgsz);
	pci_पढ़ो_config_dword(dev, pos + PCI_SRIOV_CAP, &iov->cap);
	pci_पढ़ो_config_byte(dev, pos + PCI_SRIOV_FUNC_LINK, &iov->link);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_sriov_info(काष्ठा bnx2x *bp, काष्ठा bnx2x_sriov *iov)
अणु
	u32 val;

	/* पढ़ो the SRIOV capability काष्ठाure
	 * The fields can be पढ़ो via configuration पढ़ो or
	 * directly from the device (starting at offset PCICFG_OFFSET)
	 */
	अगर (bnx2x_sriov_pci_cfg_info(bp, iov))
		वापस -ENODEV;

	/* get the number of SRIOV bars */
	iov->nres = 0;

	/* पढ़ो the first_vfid */
	val = REG_RD(bp, PCICFG_OFFSET + GRC_CONFIG_REG_PF_INIT_VF);
	iov->first_vf_in_pf = ((val & GRC_CR_PF_INIT_VF_PF_FIRST_VF_NUM_MASK)
			       * 8) - (BNX2X_MAX_NUM_OF_VFS * BP_PATH(bp));

	DP(BNX2X_MSG_IOV,
	   "IOV info[%d]: first vf %d, nres %d, cap 0x%x, ctrl 0x%x, total %d, initial %d, num vfs %d, offset %d, stride %d, page size 0x%x\n",
	   BP_FUNC(bp),
	   iov->first_vf_in_pf, iov->nres, iov->cap, iov->ctrl, iov->total,
	   iov->initial, iov->nr_virtfn, iov->offset, iov->stride, iov->pgsz);

	वापस 0;
पूर्ण

/* must be called after PF bars are mapped */
पूर्णांक bnx2x_iov_init_one(काष्ठा bnx2x *bp, पूर्णांक पूर्णांक_mode_param,
		       पूर्णांक num_vfs_param)
अणु
	पूर्णांक err, i;
	काष्ठा bnx2x_sriov *iov;
	काष्ठा pci_dev *dev = bp->pdev;

	bp->vfdb = शून्य;

	/* verअगरy is pf */
	अगर (IS_VF(bp))
		वापस 0;

	/* verअगरy sriov capability is present in configuration space */
	अगर (!pci_find_ext_capability(dev, PCI_EXT_CAP_ID_SRIOV))
		वापस 0;

	/* verअगरy chip revision */
	अगर (CHIP_IS_E1x(bp))
		वापस 0;

	/* check अगर SRIOV support is turned off */
	अगर (!num_vfs_param)
		वापस 0;

	/* SRIOV assumes that num of PF CIDs < BNX2X_FIRST_VF_CID */
	अगर (BNX2X_L2_MAX_CID(bp) >= BNX2X_FIRST_VF_CID) अणु
		BNX2X_ERR("PF cids %d are overspilling into vf space (starts at %d). Abort SRIOV\n",
			  BNX2X_L2_MAX_CID(bp), BNX2X_FIRST_VF_CID);
		वापस 0;
	पूर्ण

	/* SRIOV can be enabled only with MSIX */
	अगर (पूर्णांक_mode_param == BNX2X_INT_MODE_MSI ||
	    पूर्णांक_mode_param == BNX2X_INT_MODE_INTX) अणु
		BNX2X_ERR("Forced MSI/INTx mode is incompatible with SRIOV\n");
		वापस 0;
	पूर्ण

	/* verअगरy ari is enabled */
	अगर (!pci_ari_enabled(bp->pdev->bus)) अणु
		BNX2X_ERR("ARI not supported (check pci bridge ARI forwarding), SRIOV can not be enabled\n");
		वापस 0;
	पूर्ण

	/* verअगरy igu is in normal mode */
	अगर (CHIP_INT_MODE_IS_BC(bp)) अणु
		BNX2X_ERR("IGU not normal mode,  SRIOV can not be enabled\n");
		वापस 0;
	पूर्ण

	/* allocate the vfs database */
	bp->vfdb = kzalloc(माप(*(bp->vfdb)), GFP_KERNEL);
	अगर (!bp->vfdb) अणु
		BNX2X_ERR("failed to allocate vf database\n");
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	/* get the sriov info - Linux alपढ़ोy collected all the pertinent
	 * inक्रमmation, however the sriov काष्ठाure is क्रम the निजी use
	 * of the pci module. Also we want this inक्रमmation regardless
	 * of the hyper-visor.
	 */
	iov = &(bp->vfdb->sriov);
	err = bnx2x_sriov_info(bp, iov);
	अगर (err)
		जाओ failed;

	/* SR-IOV capability was enabled but there are no VFs*/
	अगर (iov->total == 0) अणु
		err = -EINVAL;
		जाओ failed;
	पूर्ण

	iov->nr_virtfn = min_t(u16, iov->total, num_vfs_param);

	DP(BNX2X_MSG_IOV, "num_vfs_param was %d, nr_virtfn was %d\n",
	   num_vfs_param, iov->nr_virtfn);

	/* allocate the vf array */
	bp->vfdb->vfs = kसुस्मृति(BNX2X_NR_VIRTFN(bp),
				माप(काष्ठा bnx2x_virtf),
				GFP_KERNEL);
	अगर (!bp->vfdb->vfs) अणु
		BNX2X_ERR("failed to allocate vf array\n");
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	/* Initial VF init - index and असल_vfid - nr_virtfn must be set */
	क्रम_each_vf(bp, i) अणु
		bnx2x_vf(bp, i, index) = i;
		bnx2x_vf(bp, i, असल_vfid) = iov->first_vf_in_pf + i;
		bnx2x_vf(bp, i, state) = VF_FREE;
		mutex_init(&bnx2x_vf(bp, i, op_mutex));
		bnx2x_vf(bp, i, op_current) = CHANNEL_TLV_NONE;
		/* enable spoofchk by शेष */
		bnx2x_vf(bp, i, spoofchk) = 1;
	पूर्ण

	/* re-पढ़ो the IGU CAM क्रम VFs - index and असल_vfid must be set */
	अगर (!bnx2x_get_vf_igu_cam_info(bp)) अणु
		BNX2X_ERR("No entries in IGU CAM for vfs\n");
		err = -EINVAL;
		जाओ failed;
	पूर्ण

	/* allocate the queue arrays क्रम all VFs */
	bp->vfdb->vfqs = kसुस्मृति(BNX2X_MAX_NUM_VF_QUEUES,
				 माप(काष्ठा bnx2x_vf_queue),
				 GFP_KERNEL);

	अगर (!bp->vfdb->vfqs) अणु
		BNX2X_ERR("failed to allocate vf queue array\n");
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	/* Prepare the VFs event synchronization mechanism */
	mutex_init(&bp->vfdb->event_mutex);

	mutex_init(&bp->vfdb->bulletin_mutex);

	अगर (SHMEM2_HAS(bp, sriov_चयन_mode))
		SHMEM2_WR(bp, sriov_चयन_mode, SRIOV_SWITCH_MODE_VEB);

	वापस 0;
failed:
	DP(BNX2X_MSG_IOV, "Failed err=%d\n", err);
	__bnx2x_iov_मुक्त_vfdb(bp);
	वापस err;
पूर्ण

व्योम bnx2x_iov_हटाओ_one(काष्ठा bnx2x *bp)
अणु
	पूर्णांक vf_idx;

	/* अगर SRIOV is not enabled there's nothing to करो */
	अगर (!IS_SRIOV(bp))
		वापस;

	bnx2x_disable_sriov(bp);

	/* disable access to all VFs */
	क्रम (vf_idx = 0; vf_idx < bp->vfdb->sriov.total; vf_idx++) अणु
		bnx2x_pretend_func(bp,
				   HW_VF_HANDLE(bp,
						bp->vfdb->sriov.first_vf_in_pf +
						vf_idx));
		DP(BNX2X_MSG_IOV, "disabling internal access for vf %d\n",
		   bp->vfdb->sriov.first_vf_in_pf + vf_idx);
		bnx2x_vf_enable_पूर्णांकernal(bp, 0);
		bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));
	पूर्ण

	/* मुक्त vf database */
	__bnx2x_iov_मुक्त_vfdb(bp);
पूर्ण

व्योम bnx2x_iov_मुक्त_mem(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	अगर (!IS_SRIOV(bp))
		वापस;

	/* मुक्त vfs hw contexts */
	क्रम (i = 0; i < BNX2X_VF_CIDS/ILT_PAGE_CIDS; i++) अणु
		काष्ठा hw_dma *cxt = &bp->vfdb->context[i];
		BNX2X_PCI_FREE(cxt->addr, cxt->mapping, cxt->size);
	पूर्ण

	BNX2X_PCI_FREE(BP_VFDB(bp)->sp_dma.addr,
		       BP_VFDB(bp)->sp_dma.mapping,
		       BP_VFDB(bp)->sp_dma.size);

	BNX2X_PCI_FREE(BP_VF_MBX_DMA(bp)->addr,
		       BP_VF_MBX_DMA(bp)->mapping,
		       BP_VF_MBX_DMA(bp)->size);

	BNX2X_PCI_FREE(BP_VF_BULLETIN_DMA(bp)->addr,
		       BP_VF_BULLETIN_DMA(bp)->mapping,
		       BP_VF_BULLETIN_DMA(bp)->size);
पूर्ण

पूर्णांक bnx2x_iov_alloc_mem(काष्ठा bnx2x *bp)
अणु
	माप_प्रकार tot_size;
	पूर्णांक i, rc = 0;

	अगर (!IS_SRIOV(bp))
		वापस rc;

	/* allocate vfs hw contexts */
	tot_size = (BP_VFDB(bp)->sriov.first_vf_in_pf + BNX2X_NR_VIRTFN(bp)) *
		BNX2X_CIDS_PER_VF * माप(जोड़ cdu_context);

	क्रम (i = 0; i < BNX2X_VF_CIDS/ILT_PAGE_CIDS; i++) अणु
		काष्ठा hw_dma *cxt = BP_VF_CXT_PAGE(bp, i);
		cxt->size = min_t(माप_प्रकार, tot_size, CDU_ILT_PAGE_SZ);

		अगर (cxt->size) अणु
			cxt->addr = BNX2X_PCI_ALLOC(&cxt->mapping, cxt->size);
			अगर (!cxt->addr)
				जाओ alloc_mem_err;
		पूर्ण अन्यथा अणु
			cxt->addr = शून्य;
			cxt->mapping = 0;
		पूर्ण
		tot_size -= cxt->size;
	पूर्ण

	/* allocate vfs ramrods dma memory - client_init and set_mac */
	tot_size = BNX2X_NR_VIRTFN(bp) * माप(काष्ठा bnx2x_vf_sp);
	BP_VFDB(bp)->sp_dma.addr = BNX2X_PCI_ALLOC(&BP_VFDB(bp)->sp_dma.mapping,
						   tot_size);
	अगर (!BP_VFDB(bp)->sp_dma.addr)
		जाओ alloc_mem_err;
	BP_VFDB(bp)->sp_dma.size = tot_size;

	/* allocate mailboxes */
	tot_size = BNX2X_NR_VIRTFN(bp) * MBX_MSG_ALIGNED_SIZE;
	BP_VF_MBX_DMA(bp)->addr = BNX2X_PCI_ALLOC(&BP_VF_MBX_DMA(bp)->mapping,
						  tot_size);
	अगर (!BP_VF_MBX_DMA(bp)->addr)
		जाओ alloc_mem_err;

	BP_VF_MBX_DMA(bp)->size = tot_size;

	/* allocate local bulletin boards */
	tot_size = BNX2X_NR_VIRTFN(bp) * BULLETIN_CONTENT_SIZE;
	BP_VF_BULLETIN_DMA(bp)->addr = BNX2X_PCI_ALLOC(&BP_VF_BULLETIN_DMA(bp)->mapping,
						       tot_size);
	अगर (!BP_VF_BULLETIN_DMA(bp)->addr)
		जाओ alloc_mem_err;

	BP_VF_BULLETIN_DMA(bp)->size = tot_size;

	वापस 0;

alloc_mem_err:
	वापस -ENOMEM;
पूर्ण

अटल व्योम bnx2x_vfq_init(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			   काष्ठा bnx2x_vf_queue *q)
अणु
	u8 cl_id = vfq_cl_id(vf, q);
	u8 func_id = FW_VF_HANDLE(vf->असल_vfid);
	अचिन्हित दीर्घ q_type = 0;

	set_bit(BNX2X_Q_TYPE_HAS_TX, &q_type);
	set_bit(BNX2X_Q_TYPE_HAS_RX, &q_type);

	/* Queue State object */
	bnx2x_init_queue_obj(bp, &q->sp_obj,
			     cl_id, &q->cid, 1, func_id,
			     bnx2x_vf_sp(bp, vf, q_data),
			     bnx2x_vf_sp_map(bp, vf, q_data),
			     q_type);

	/* sp indication is set only when vlan/mac/etc. are initialized */
	q->sp_initialized = false;

	DP(BNX2X_MSG_IOV,
	   "initialized vf %d's queue object. func id set to %d. cid set to 0x%x\n",
	   vf->असल_vfid, q->sp_obj.func_id, q->cid);
पूर्ण

अटल पूर्णांक bnx2x_max_speed_cap(काष्ठा bnx2x *bp)
अणु
	u32 supported = bp->port.supported[bnx2x_get_link_cfg_idx(bp)];

	अगर (supported &
	    (SUPPORTED_20000baseMLD2_Full | SUPPORTED_20000baseKR2_Full))
		वापस 20000;

	वापस 10000; /* assume lowest supported speed is 10G */
पूर्ण

पूर्णांक bnx2x_iov_link_update_vf(काष्ठा bnx2x *bp, पूर्णांक idx)
अणु
	काष्ठा bnx2x_link_report_data *state = &bp->last_reported_link;
	काष्ठा pf_vf_bulletin_content *bulletin;
	काष्ठा bnx2x_virtf *vf;
	bool update = true;
	पूर्णांक rc = 0;

	/* sanity and init */
	rc = bnx2x_vf_op_prep(bp, idx, &vf, &bulletin, false);
	अगर (rc)
		वापस rc;

	mutex_lock(&bp->vfdb->bulletin_mutex);

	अगर (vf->link_cfg == IFLA_VF_LINK_STATE_AUTO) अणु
		bulletin->valid_biपंचांगap |= 1 << LINK_VALID;

		bulletin->link_speed = state->line_speed;
		bulletin->link_flags = 0;
		अगर (test_bit(BNX2X_LINK_REPORT_LINK_DOWN,
			     &state->link_report_flags))
			bulletin->link_flags |= VFPF_LINK_REPORT_LINK_DOWN;
		अगर (test_bit(BNX2X_LINK_REPORT_FD,
			     &state->link_report_flags))
			bulletin->link_flags |= VFPF_LINK_REPORT_FULL_DUPLEX;
		अगर (test_bit(BNX2X_LINK_REPORT_RX_FC_ON,
			     &state->link_report_flags))
			bulletin->link_flags |= VFPF_LINK_REPORT_RX_FC_ON;
		अगर (test_bit(BNX2X_LINK_REPORT_TX_FC_ON,
			     &state->link_report_flags))
			bulletin->link_flags |= VFPF_LINK_REPORT_TX_FC_ON;
	पूर्ण अन्यथा अगर (vf->link_cfg == IFLA_VF_LINK_STATE_DISABLE &&
		   !(bulletin->link_flags & VFPF_LINK_REPORT_LINK_DOWN)) अणु
		bulletin->valid_biपंचांगap |= 1 << LINK_VALID;
		bulletin->link_flags |= VFPF_LINK_REPORT_LINK_DOWN;
	पूर्ण अन्यथा अगर (vf->link_cfg == IFLA_VF_LINK_STATE_ENABLE &&
		   (bulletin->link_flags & VFPF_LINK_REPORT_LINK_DOWN)) अणु
		bulletin->valid_biपंचांगap |= 1 << LINK_VALID;
		bulletin->link_speed = bnx2x_max_speed_cap(bp);
		bulletin->link_flags &= ~VFPF_LINK_REPORT_LINK_DOWN;
	पूर्ण अन्यथा अणु
		update = false;
	पूर्ण

	अगर (update) अणु
		DP(NETIF_MSG_LINK | BNX2X_MSG_IOV,
		   "vf %d mode %u speed %d flags %x\n", idx,
		   vf->link_cfg, bulletin->link_speed, bulletin->link_flags);

		/* Post update on VF's bulletin board */
		rc = bnx2x_post_vf_bulletin(bp, idx);
		अगर (rc) अणु
			BNX2X_ERR("failed to update VF[%d] bulletin\n", idx);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&bp->vfdb->bulletin_mutex);
	वापस rc;
पूर्ण

पूर्णांक bnx2x_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक idx, पूर्णांक link_state)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा bnx2x_virtf *vf = BP_VF(bp, idx);

	अगर (!vf)
		वापस -EINVAL;

	अगर (vf->link_cfg == link_state)
		वापस 0; /* nothing toकरो */

	vf->link_cfg = link_state;

	वापस bnx2x_iov_link_update_vf(bp, idx);
पूर्ण

व्योम bnx2x_iov_link_update(काष्ठा bnx2x *bp)
अणु
	पूर्णांक vfid;

	अगर (!IS_SRIOV(bp))
		वापस;

	क्रम_each_vf(bp, vfid)
		bnx2x_iov_link_update_vf(bp, vfid);
पूर्ण

/* called by bnx2x_nic_load */
पूर्णांक bnx2x_iov_nic_init(काष्ठा bnx2x *bp)
अणु
	पूर्णांक vfid;

	अगर (!IS_SRIOV(bp)) अणु
		DP(BNX2X_MSG_IOV, "vfdb was not allocated\n");
		वापस 0;
	पूर्ण

	DP(BNX2X_MSG_IOV, "num of vfs: %d\n", (bp)->vfdb->sriov.nr_virtfn);

	/* let FLR complete ... */
	msleep(100);

	/* initialize vf database */
	क्रम_each_vf(bp, vfid) अणु
		काष्ठा bnx2x_virtf *vf = BP_VF(bp, vfid);

		पूर्णांक base_vf_cid = (BP_VFDB(bp)->sriov.first_vf_in_pf + vfid) *
			BNX2X_CIDS_PER_VF;

		जोड़ cdu_context *base_cxt = (जोड़ cdu_context *)
			BP_VF_CXT_PAGE(bp, base_vf_cid/ILT_PAGE_CIDS)->addr +
			(base_vf_cid & (ILT_PAGE_CIDS-1));

		DP(BNX2X_MSG_IOV,
		   "VF[%d] Max IGU SBs: %d, base vf cid 0x%x, base cid 0x%x, base cxt %p\n",
		   vf->असल_vfid, vf_sb_count(vf), base_vf_cid,
		   BNX2X_FIRST_VF_CID + base_vf_cid, base_cxt);

		/* init अटलally provisioned resources */
		bnx2x_iov_अटल_resc(bp, vf);

		/* queues are initialized during VF-ACQUIRE */
		vf->filter_state = 0;
		vf->sp_cl_id = bnx2x_fp(bp, 0, cl_id);

		bnx2x_init_credit_pool(&vf->vf_vlans_pool, 0,
				       vf_vlan_rules_cnt(vf));
		bnx2x_init_credit_pool(&vf->vf_macs_pool, 0,
				       vf_mac_rules_cnt(vf));

		/*  init mcast object - This object will be re-initialized
		 *  during VF-ACQUIRE with the proper cl_id and cid.
		 *  It needs to be initialized here so that it can be safely
		 *  handled by a subsequent FLR flow.
		 */
		bnx2x_init_mcast_obj(bp, &vf->mcast_obj, 0xFF,
				     0xFF, 0xFF, 0xFF,
				     bnx2x_vf_sp(bp, vf, mcast_rdata),
				     bnx2x_vf_sp_map(bp, vf, mcast_rdata),
				     BNX2X_FILTER_MCAST_PENDING,
				     &vf->filter_state,
				     BNX2X_OBJ_TYPE_RX_TX);

		/* set the mailbox message addresses */
		BP_VF_MBX(bp, vfid)->msg = (काष्ठा bnx2x_vf_mbx_msg *)
			(((u8 *)BP_VF_MBX_DMA(bp)->addr) + vfid *
			MBX_MSG_ALIGNED_SIZE);

		BP_VF_MBX(bp, vfid)->msg_mapping = BP_VF_MBX_DMA(bp)->mapping +
			vfid * MBX_MSG_ALIGNED_SIZE;

		/* Enable vf mailbox */
		bnx2x_vf_enable_mbx(bp, vf->असल_vfid);
	पूर्ण

	/* Final VF init */
	क्रम_each_vf(bp, vfid) अणु
		काष्ठा bnx2x_virtf *vf = BP_VF(bp, vfid);

		/* fill in the BDF and bars */
		vf->करोमुख्य = bnx2x_vf_करोमुख्य(bp, vfid);
		vf->bus = bnx2x_vf_bus(bp, vfid);
		vf->devfn = bnx2x_vf_devfn(bp, vfid);
		bnx2x_vf_set_bars(bp, vf);

		DP(BNX2X_MSG_IOV,
		   "VF info[%d]: bus 0x%x, devfn 0x%x, bar0 [0x%x, %d], bar1 [0x%x, %d], bar2 [0x%x, %d]\n",
		   vf->असल_vfid, vf->bus, vf->devfn,
		   (अचिन्हित)vf->bars[0].bar, vf->bars[0].size,
		   (अचिन्हित)vf->bars[1].bar, vf->bars[1].size,
		   (अचिन्हित)vf->bars[2].bar, vf->bars[2].size);
	पूर्ण

	वापस 0;
पूर्ण

/* called by bnx2x_chip_cleanup */
पूर्णांक bnx2x_iov_chip_cleanup(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;

	अगर (!IS_SRIOV(bp))
		वापस 0;

	/* release all the VFs */
	क्रम_each_vf(bp, i)
		bnx2x_vf_release(bp, BP_VF(bp, i));

	वापस 0;
पूर्ण

/* called by bnx2x_init_hw_func, वापसs the next ilt line */
पूर्णांक bnx2x_iov_init_ilt(काष्ठा bnx2x *bp, u16 line)
अणु
	पूर्णांक i;
	काष्ठा bnx2x_ilt *ilt = BP_ILT(bp);

	अगर (!IS_SRIOV(bp))
		वापस line;

	/* set vfs ilt lines */
	क्रम (i = 0; i < BNX2X_VF_CIDS/ILT_PAGE_CIDS; i++) अणु
		काष्ठा hw_dma *hw_cxt = BP_VF_CXT_PAGE(bp, i);

		ilt->lines[line+i].page = hw_cxt->addr;
		ilt->lines[line+i].page_mapping = hw_cxt->mapping;
		ilt->lines[line+i].size = hw_cxt->size; /* करोesn't matter */
	पूर्ण
	वापस line + i;
पूर्ण

अटल u8 bnx2x_iov_is_vf_cid(काष्ठा bnx2x *bp, u16 cid)
अणु
	वापस ((cid >= BNX2X_FIRST_VF_CID) &&
		((cid - BNX2X_FIRST_VF_CID) < BNX2X_VF_CIDS));
पूर्ण

अटल
व्योम bnx2x_vf_handle_classअगरication_eqe(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_vf_queue *vfq,
					जोड़ event_ring_elem *elem)
अणु
	अचिन्हित दीर्घ ramrod_flags = 0;
	पूर्णांक rc = 0;
	u32 echo = le32_to_cpu(elem->message.data.eth_event.echo);

	/* Always push next commands out, करोn't रुको here */
	set_bit(RAMROD_CONT, &ramrod_flags);

	चयन (echo >> BNX2X_SWCID_SHIFT) अणु
	हाल BNX2X_FILTER_MAC_PENDING:
		rc = vfq->mac_obj.complete(bp, &vfq->mac_obj, elem,
					   &ramrod_flags);
		अवरोध;
	हाल BNX2X_FILTER_VLAN_PENDING:
		rc = vfq->vlan_obj.complete(bp, &vfq->vlan_obj, elem,
					    &ramrod_flags);
		अवरोध;
	शेष:
		BNX2X_ERR("Unsupported classification command: 0x%x\n", echo);
		वापस;
	पूर्ण
	अगर (rc < 0)
		BNX2X_ERR("Failed to schedule new commands: %d\n", rc);
	अन्यथा अगर (rc > 0)
		DP(BNX2X_MSG_IOV, "Scheduled next pending commands...\n");
पूर्ण

अटल
व्योम bnx2x_vf_handle_mcast_eqe(काष्ठा bnx2x *bp,
			       काष्ठा bnx2x_virtf *vf)
अणु
	काष्ठा bnx2x_mcast_ramrod_params rparam = अणुशून्यपूर्ण;
	पूर्णांक rc;

	rparam.mcast_obj = &vf->mcast_obj;
	vf->mcast_obj.raw.clear_pending(&vf->mcast_obj.raw);

	/* If there are pending mcast commands - send them */
	अगर (vf->mcast_obj.check_pending(&vf->mcast_obj)) अणु
		rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_CONT);
		अगर (rc < 0)
			BNX2X_ERR("Failed to send pending mcast commands: %d\n",
				  rc);
	पूर्ण
पूर्ण

अटल
व्योम bnx2x_vf_handle_filters_eqe(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_virtf *vf)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(BNX2X_FILTER_RX_MODE_PENDING, &vf->filter_state);
	smp_mb__after_atomic();
पूर्ण

अटल व्योम bnx2x_vf_handle_rss_update_eqe(काष्ठा bnx2x *bp,
					   काष्ठा bnx2x_virtf *vf)
अणु
	vf->rss_conf_obj.raw.clear_pending(&vf->rss_conf_obj.raw);
पूर्ण

पूर्णांक bnx2x_iov_eq_sp_event(काष्ठा bnx2x *bp, जोड़ event_ring_elem *elem)
अणु
	काष्ठा bnx2x_virtf *vf;
	पूर्णांक qidx = 0, असल_vfid;
	u8 opcode;
	u16 cid = 0xffff;

	अगर (!IS_SRIOV(bp))
		वापस 1;

	/* first get the cid - the only events we handle here are cfc-delete
	 * and set-mac completion
	 */
	opcode = elem->message.opcode;

	चयन (opcode) अणु
	हाल EVENT_RING_OPCODE_CFC_DEL:
		cid = SW_CID(elem->message.data.cfc_del_event.cid);
		DP(BNX2X_MSG_IOV, "checking cfc-del comp cid=%d\n", cid);
		अवरोध;
	हाल EVENT_RING_OPCODE_CLASSIFICATION_RULES:
	हाल EVENT_RING_OPCODE_MULTICAST_RULES:
	हाल EVENT_RING_OPCODE_FILTERS_RULES:
	हाल EVENT_RING_OPCODE_RSS_UPDATE_RULES:
		cid = SW_CID(elem->message.data.eth_event.echo);
		DP(BNX2X_MSG_IOV, "checking filtering comp cid=%d\n", cid);
		अवरोध;
	हाल EVENT_RING_OPCODE_VF_FLR:
		असल_vfid = elem->message.data.vf_flr_event.vf_id;
		DP(BNX2X_MSG_IOV, "Got VF FLR notification abs_vfid=%d\n",
		   असल_vfid);
		जाओ get_vf;
	हाल EVENT_RING_OPCODE_MALICIOUS_VF:
		असल_vfid = elem->message.data.malicious_vf_event.vf_id;
		BNX2X_ERR("Got VF MALICIOUS notification abs_vfid=%d err_id=0x%x\n",
			  असल_vfid,
			  elem->message.data.malicious_vf_event.err_id);
		जाओ get_vf;
	शेष:
		वापस 1;
	पूर्ण

	/* check अगर the cid is the VF range */
	अगर (!bnx2x_iov_is_vf_cid(bp, cid)) अणु
		DP(BNX2X_MSG_IOV, "cid is outside vf range: %d\n", cid);
		वापस 1;
	पूर्ण

	/* extract vf and rxq index from vf_cid - relies on the following:
	 * 1. vfid on cid reflects the true असल_vfid
	 * 2. The max number of VFs (per path) is 64
	 */
	qidx = cid & ((1 << BNX2X_VF_CID_WND)-1);
	असल_vfid = (cid >> BNX2X_VF_CID_WND) & (BNX2X_MAX_NUM_OF_VFS-1);
get_vf:
	vf = bnx2x_vf_by_असल_fid(bp, असल_vfid);

	अगर (!vf) अणु
		BNX2X_ERR("EQ completion for unknown VF, cid %d, abs_vfid %d\n",
			  cid, असल_vfid);
		वापस 0;
	पूर्ण

	चयन (opcode) अणु
	हाल EVENT_RING_OPCODE_CFC_DEL:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] cfc delete ramrod\n",
		   vf->असल_vfid, qidx);
		vfq_get(vf, qidx)->sp_obj.complete_cmd(bp,
						       &vfq_get(vf,
								qidx)->sp_obj,
						       BNX2X_Q_CMD_CFC_DEL);
		अवरोध;
	हाल EVENT_RING_OPCODE_CLASSIFICATION_RULES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] set mac/vlan ramrod\n",
		   vf->असल_vfid, qidx);
		bnx2x_vf_handle_classअगरication_eqe(bp, vfq_get(vf, qidx), elem);
		अवरोध;
	हाल EVENT_RING_OPCODE_MULTICAST_RULES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] set mcast ramrod\n",
		   vf->असल_vfid, qidx);
		bnx2x_vf_handle_mcast_eqe(bp, vf);
		अवरोध;
	हाल EVENT_RING_OPCODE_FILTERS_RULES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] set rx-mode ramrod\n",
		   vf->असल_vfid, qidx);
		bnx2x_vf_handle_filters_eqe(bp, vf);
		अवरोध;
	हाल EVENT_RING_OPCODE_RSS_UPDATE_RULES:
		DP(BNX2X_MSG_IOV, "got VF [%d:%d] RSS update ramrod\n",
		   vf->असल_vfid, qidx);
		bnx2x_vf_handle_rss_update_eqe(bp, vf);
		fallthrough;
	हाल EVENT_RING_OPCODE_VF_FLR:
		/* Do nothing क्रम now */
		वापस 0;
	हाल EVENT_RING_OPCODE_MALICIOUS_VF:
		vf->malicious = true;
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा bnx2x_virtf *bnx2x_vf_by_cid(काष्ठा bnx2x *bp, पूर्णांक vf_cid)
अणु
	/* extract the vf from vf_cid - relies on the following:
	 * 1. vfid on cid reflects the true असल_vfid
	 * 2. The max number of VFs (per path) is 64
	 */
	पूर्णांक असल_vfid = (vf_cid >> BNX2X_VF_CID_WND) & (BNX2X_MAX_NUM_OF_VFS-1);
	वापस bnx2x_vf_by_असल_fid(bp, असल_vfid);
पूर्ण

व्योम bnx2x_iov_set_queue_sp_obj(काष्ठा bnx2x *bp, पूर्णांक vf_cid,
				काष्ठा bnx2x_queue_sp_obj **q_obj)
अणु
	काष्ठा bnx2x_virtf *vf;

	अगर (!IS_SRIOV(bp))
		वापस;

	vf = bnx2x_vf_by_cid(bp, vf_cid);

	अगर (vf) अणु
		/* extract queue index from vf_cid - relies on the following:
		 * 1. vfid on cid reflects the true असल_vfid
		 * 2. The max number of VFs (per path) is 64
		 */
		पूर्णांक q_index = vf_cid & ((1 << BNX2X_VF_CID_WND)-1);
		*q_obj = &bnx2x_vfq(vf, q_index, sp_obj);
	पूर्ण अन्यथा अणु
		BNX2X_ERR("No vf matching cid %d\n", vf_cid);
	पूर्ण
पूर्ण

व्योम bnx2x_iov_adjust_stats_req(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	पूर्णांक first_queue_query_index, num_queues_req;
	dma_addr_t cur_data_offset;
	काष्ठा stats_query_entry *cur_query_entry;
	u8 stats_count = 0;
	bool is_fcoe = false;

	अगर (!IS_SRIOV(bp))
		वापस;

	अगर (!NO_FCOE(bp))
		is_fcoe = true;

	/* fcoe adds one global request and one queue request */
	num_queues_req = BNX2X_NUM_ETH_QUEUES(bp) + is_fcoe;
	first_queue_query_index = BNX2X_FIRST_QUEUE_QUERY_IDX -
		(is_fcoe ? 0 : 1);

	DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
	       "BNX2X_NUM_ETH_QUEUES %d, is_fcoe %d, first_queue_query_index %d => determined the last non virtual statistics query index is %d. Will add queries on top of that\n",
	       BNX2X_NUM_ETH_QUEUES(bp), is_fcoe, first_queue_query_index,
	       first_queue_query_index + num_queues_req);

	cur_data_offset = bp->fw_stats_data_mapping +
		दुरत्व(काष्ठा bnx2x_fw_stats_data, queue_stats) +
		num_queues_req * माप(काष्ठा per_queue_stats);

	cur_query_entry = &bp->fw_stats_req->
		query[first_queue_query_index + num_queues_req];

	क्रम_each_vf(bp, i) अणु
		पूर्णांक j;
		काष्ठा bnx2x_virtf *vf = BP_VF(bp, i);

		अगर (vf->state != VF_ENABLED) अणु
			DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
			       "vf %d not enabled so no stats for it\n",
			       vf->असल_vfid);
			जारी;
		पूर्ण

		अगर (vf->malicious) अणु
			DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
			       "vf %d malicious so no stats for it\n",
			       vf->असल_vfid);
			जारी;
		पूर्ण

		DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
		       "add addresses for vf %d\n", vf->असल_vfid);
		क्रम_each_vfq(vf, j) अणु
			काष्ठा bnx2x_vf_queue *rxq = vfq_get(vf, j);

			dma_addr_t q_stats_addr =
				vf->fw_stat_map + j * vf->stats_stride;

			/* collect stats fro active queues only */
			अगर (bnx2x_get_q_logical_state(bp, &rxq->sp_obj) ==
			    BNX2X_Q_LOGICAL_STATE_STOPPED)
				जारी;

			/* create stats query entry क्रम this queue */
			cur_query_entry->kind = STATS_TYPE_QUEUE;
			cur_query_entry->index = vfq_stat_id(vf, rxq);
			cur_query_entry->funcID =
				cpu_to_le16(FW_VF_HANDLE(vf->असल_vfid));
			cur_query_entry->address.hi =
				cpu_to_le32(U64_HI(q_stats_addr));
			cur_query_entry->address.lo =
				cpu_to_le32(U64_LO(q_stats_addr));
			DP_AND((BNX2X_MSG_IOV | BNX2X_MSG_STATS),
			       "added address %x %x for vf %d queue %d client %d\n",
			       cur_query_entry->address.hi,
			       cur_query_entry->address.lo,
			       cur_query_entry->funcID,
			       j, cur_query_entry->index);
			cur_query_entry++;
			cur_data_offset += माप(काष्ठा per_queue_stats);
			stats_count++;

			/* all stats are coalesced to the leading queue */
			अगर (vf->cfg_flags & VF_CFG_STATS_COALESCE)
				अवरोध;
		पूर्ण
	पूर्ण
	bp->fw_stats_req->hdr.cmd_num = bp->fw_stats_num + stats_count;
पूर्ण

/* VF API helpers */
अटल व्योम bnx2x_vf_qtbl_set_q(काष्ठा bnx2x *bp, u8 असल_vfid, u8 qid,
				u8 enable)
अणु
	u32 reg = PXP_REG_HST_ZONE_PERMISSION_TABLE + qid * 4;
	u32 val = enable ? (असल_vfid | (1 << 6)) : 0;

	REG_WR(bp, reg, val);
पूर्ण

अटल व्योम bnx2x_vf_clr_qtbl(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	पूर्णांक i;

	क्रम_each_vfq(vf, i)
		bnx2x_vf_qtbl_set_q(bp, vf->असल_vfid,
				    vfq_qzone_id(vf, vfq_get(vf, i)), false);
पूर्ण

अटल व्योम bnx2x_vf_igu_disable(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	u32 val;

	/* clear the VF configuration - pretend */
	bnx2x_pretend_func(bp, HW_VF_HANDLE(bp, vf->असल_vfid));
	val = REG_RD(bp, IGU_REG_VF_CONFIGURATION);
	val &= ~(IGU_VF_CONF_MSI_MSIX_EN | IGU_VF_CONF_SINGLE_ISR_EN |
		 IGU_VF_CONF_FUNC_EN | IGU_VF_CONF_PARENT_MASK);
	REG_WR(bp, IGU_REG_VF_CONFIGURATION, val);
	bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));
पूर्ण

u8 bnx2x_vf_max_queue_cnt(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	वापस min_t(u8, min_t(u8, vf_sb_count(vf), BNX2X_CIDS_PER_VF),
		     BNX2X_VF_MAX_QUEUES);
पूर्ण

अटल
पूर्णांक bnx2x_vf_chk_avail_resc(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			    काष्ठा vf_pf_resc_request *req_resc)
अणु
	u8 rxq_cnt = vf_rxq_count(vf) ? : bnx2x_vf_max_queue_cnt(bp, vf);
	u8 txq_cnt = vf_txq_count(vf) ? : bnx2x_vf_max_queue_cnt(bp, vf);

	वापस ((req_resc->num_rxqs <= rxq_cnt) &&
		(req_resc->num_txqs <= txq_cnt) &&
		(req_resc->num_sbs <= vf_sb_count(vf))   &&
		(req_resc->num_mac_filters <= vf_mac_rules_cnt(vf)) &&
		(req_resc->num_vlan_filters <= vf_vlan_rules_cnt(vf)));
पूर्ण

/* CORE VF API */
पूर्णांक bnx2x_vf_acquire(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
		     काष्ठा vf_pf_resc_request *resc)
अणु
	पूर्णांक base_vf_cid = (BP_VFDB(bp)->sriov.first_vf_in_pf + vf->index) *
		BNX2X_CIDS_PER_VF;

	जोड़ cdu_context *base_cxt = (जोड़ cdu_context *)
		BP_VF_CXT_PAGE(bp, base_vf_cid/ILT_PAGE_CIDS)->addr +
		(base_vf_cid & (ILT_PAGE_CIDS-1));
	पूर्णांक i;

	/* अगर state is 'acquired' the VF was not released or FLR'd, in
	 * this हाल the वापसed resources match the acquired alपढ़ोy
	 * acquired resources. Verअगरy that the requested numbers करो
	 * not exceed the alपढ़ोy acquired numbers.
	 */
	अगर (vf->state == VF_ACQUIRED) अणु
		DP(BNX2X_MSG_IOV, "VF[%d] Trying to re-acquire resources (VF was not released or FLR'd)\n",
		   vf->असल_vfid);

		अगर (!bnx2x_vf_chk_avail_resc(bp, vf, resc)) अणु
			BNX2X_ERR("VF[%d] When re-acquiring resources, requested numbers must be <= then previously acquired numbers\n",
				  vf->असल_vfid);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	/* Otherwise vf state must be 'free' or 'reset' */
	अगर (vf->state != VF_FREE && vf->state != VF_RESET) अणु
		BNX2X_ERR("VF[%d] Can not acquire a VF with state %d\n",
			  vf->असल_vfid, vf->state);
		वापस -EINVAL;
	पूर्ण

	/* अटल allocation:
	 * the global maximum number are fixed per VF. Fail the request अगर
	 * requested number exceed these globals
	 */
	अगर (!bnx2x_vf_chk_avail_resc(bp, vf, resc)) अणु
		DP(BNX2X_MSG_IOV,
		   "cannot fulfill vf resource request. Placing maximal available values in response\n");
		/* set the max resource in the vf */
		वापस -ENOMEM;
	पूर्ण

	/* Set resources counters - 0 request means max available */
	vf_sb_count(vf) = resc->num_sbs;
	vf_rxq_count(vf) = resc->num_rxqs ? : bnx2x_vf_max_queue_cnt(bp, vf);
	vf_txq_count(vf) = resc->num_txqs ? : bnx2x_vf_max_queue_cnt(bp, vf);

	DP(BNX2X_MSG_IOV,
	   "Fulfilling vf request: sb count %d, tx_count %d, rx_count %d, mac_rules_count %d, vlan_rules_count %d\n",
	   vf_sb_count(vf), vf_rxq_count(vf),
	   vf_txq_count(vf), vf_mac_rules_cnt(vf),
	   vf_vlan_rules_cnt(vf));

	/* Initialize the queues */
	अगर (!vf->vfqs) अणु
		DP(BNX2X_MSG_IOV, "vf->vfqs was not allocated\n");
		वापस -EINVAL;
	पूर्ण

	क्रम_each_vfq(vf, i) अणु
		काष्ठा bnx2x_vf_queue *q = vfq_get(vf, i);

		अगर (!q) अणु
			BNX2X_ERR("q number %d was not allocated\n", i);
			वापस -EINVAL;
		पूर्ण

		q->index = i;
		q->cxt = &((base_cxt + i)->eth);
		q->cid = BNX2X_FIRST_VF_CID + base_vf_cid + i;

		DP(BNX2X_MSG_IOV, "VFQ[%d:%d]: index %d, cid 0x%x, cxt %p\n",
		   vf->असल_vfid, i, q->index, q->cid, q->cxt);

		/* init SP objects */
		bnx2x_vfq_init(bp, vf, q);
	पूर्ण
	vf->state = VF_ACQUIRED;
	वापस 0;
पूर्ण

पूर्णांक bnx2x_vf_init(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf, dma_addr_t *sb_map)
अणु
	काष्ठा bnx2x_func_init_params func_init = अणु0पूर्ण;
	पूर्णांक i;

	/* the sb resources are initialized at this poपूर्णांक, करो the
	 * FW/HW initializations
	 */
	क्रम_each_vf_sb(vf, i)
		bnx2x_init_sb(bp, (dma_addr_t)sb_map[i], vf->असल_vfid, true,
			      vf_igu_sb(vf, i), vf_igu_sb(vf, i));

	/* Sanity checks */
	अगर (vf->state != VF_ACQUIRED) अणु
		DP(BNX2X_MSG_IOV, "VF[%d] is not in VF_ACQUIRED, but %d\n",
		   vf->असल_vfid, vf->state);
		वापस -EINVAL;
	पूर्ण

	/* let FLR complete ... */
	msleep(100);

	/* FLR cleanup epilogue */
	अगर (bnx2x_vf_flr_clnup_epilog(bp, vf->असल_vfid))
		वापस -EBUSY;

	/* reset IGU VF statistics: MSIX */
	REG_WR(bp, IGU_REG_STATISTIC_NUM_MESSAGE_SENT + vf->असल_vfid * 4 , 0);

	/* function setup */
	func_init.pf_id = BP_FUNC(bp);
	func_init.func_id = FW_VF_HANDLE(vf->असल_vfid);
	bnx2x_func_init(bp, &func_init);

	/* Enable the vf */
	bnx2x_vf_enable_access(bp, vf->असल_vfid);
	bnx2x_vf_enable_traffic(bp, vf);

	/* queue protection table */
	क्रम_each_vfq(vf, i)
		bnx2x_vf_qtbl_set_q(bp, vf->असल_vfid,
				    vfq_qzone_id(vf, vfq_get(vf, i)), true);

	vf->state = VF_ENABLED;

	/* update vf bulletin board */
	bnx2x_post_vf_bulletin(bp, vf->index);

	वापस 0;
पूर्ण

काष्ठा set_vf_state_cookie अणु
	काष्ठा bnx2x_virtf *vf;
	u8 state;
पूर्ण;

अटल व्योम bnx2x_set_vf_state(व्योम *cookie)
अणु
	काष्ठा set_vf_state_cookie *p = (काष्ठा set_vf_state_cookie *)cookie;

	p->vf->state = p->state;
पूर्ण

पूर्णांक bnx2x_vf_बंद(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	पूर्णांक rc = 0, i;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->असल_vfid);

	/* Close all queues */
	क्रम (i = 0; i < vf_rxq_count(vf); i++) अणु
		rc = bnx2x_vf_queue_tearकरोwn(bp, vf, i);
		अगर (rc)
			जाओ op_err;
	पूर्ण

	/* disable the पूर्णांकerrupts */
	DP(BNX2X_MSG_IOV, "disabling igu\n");
	bnx2x_vf_igu_disable(bp, vf);

	/* disable the VF */
	DP(BNX2X_MSG_IOV, "clearing qtbl\n");
	bnx2x_vf_clr_qtbl(bp, vf);

	/* need to make sure there are no outstanding stats ramrods which may
	 * cause the device to access the VF's stats buffer which it will मुक्त
	 * as soon as we वापस from the बंद flow.
	 */
	अणु
		काष्ठा set_vf_state_cookie cookie;

		cookie.vf = vf;
		cookie.state = VF_ACQUIRED;
		rc = bnx2x_stats_safe_exec(bp, bnx2x_set_vf_state, &cookie);
		अगर (rc)
			जाओ op_err;
	पूर्ण

	DP(BNX2X_MSG_IOV, "set state to acquired\n");

	वापस 0;
op_err:
	BNX2X_ERR("vf[%d] CLOSE error: rc %d\n", vf->असल_vfid, rc);
	वापस rc;
पूर्ण

/* VF release can be called either: 1. The VF was acquired but
 * not enabled 2. the vf was enabled or in the process of being
 * enabled
 */
पूर्णांक bnx2x_vf_मुक्त(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "VF[%d] STATE: %s\n", vf->असल_vfid,
	   vf->state == VF_FREE ? "Free" :
	   vf->state == VF_ACQUIRED ? "Acquired" :
	   vf->state == VF_ENABLED ? "Enabled" :
	   vf->state == VF_RESET ? "Reset" :
	   "Unknown");

	चयन (vf->state) अणु
	हाल VF_ENABLED:
		rc = bnx2x_vf_बंद(bp, vf);
		अगर (rc)
			जाओ op_err;
		fallthrough;	/* to release resources */
	हाल VF_ACQUIRED:
		DP(BNX2X_MSG_IOV, "about to free resources\n");
		bnx2x_vf_मुक्त_resc(bp, vf);
		अवरोध;

	हाल VF_FREE:
	हाल VF_RESET:
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
op_err:
	BNX2X_ERR("VF[%d] RELEASE error: rc %d\n", vf->असल_vfid, rc);
	वापस rc;
पूर्ण

पूर्णांक bnx2x_vf_rss_update(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			काष्ठा bnx2x_config_rss_params *rss)
अणु
	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->असल_vfid);
	set_bit(RAMROD_COMP_WAIT, &rss->ramrod_flags);
	वापस bnx2x_config_rss(bp, rss);
पूर्ण

पूर्णांक bnx2x_vf_tpa_update(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			काष्ठा vfpf_tpa_tlv *tlv,
			काष्ठा bnx2x_queue_update_tpa_params *params)
अणु
	aligned_u64 *sge_addr = tlv->tpa_client_info.sge_addr;
	काष्ठा bnx2x_queue_state_params qstate;
	पूर्णांक qid, rc = 0;

	DP(BNX2X_MSG_IOV, "vf[%d]\n", vf->असल_vfid);

	/* Set ramrod params */
	स_रखो(&qstate, 0, माप(काष्ठा bnx2x_queue_state_params));
	स_नकल(&qstate.params.update_tpa, params,
	       माप(काष्ठा bnx2x_queue_update_tpa_params));
	qstate.cmd = BNX2X_Q_CMD_UPDATE_TPA;
	set_bit(RAMROD_COMP_WAIT, &qstate.ramrod_flags);

	क्रम (qid = 0; qid < vf_rxq_count(vf); qid++) अणु
		qstate.q_obj = &bnx2x_vfq(vf, qid, sp_obj);
		qstate.params.update_tpa.sge_map = sge_addr[qid];
		DP(BNX2X_MSG_IOV, "sge_addr[%d:%d] %08x:%08x\n",
		   vf->असल_vfid, qid, U64_HI(sge_addr[qid]),
		   U64_LO(sge_addr[qid]));
		rc = bnx2x_queue_state_change(bp, &qstate);
		अगर (rc) अणु
			BNX2X_ERR("Failed to configure sge_addr %08x:%08x for [%d:%d]\n",
				  U64_HI(sge_addr[qid]), U64_LO(sge_addr[qid]),
				  vf->असल_vfid, qid);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/* VF release ~ VF बंद + VF release-resources
 * Release is the ultimate SW shutकरोwn and is called whenever an
 * irrecoverable error is encountered.
 */
पूर्णांक bnx2x_vf_release(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf)
अणु
	पूर्णांक rc;

	DP(BNX2X_MSG_IOV, "PF releasing vf %d\n", vf->असल_vfid);
	bnx2x_lock_vf_pf_channel(bp, vf, CHANNEL_TLV_PF_RELEASE_VF);

	rc = bnx2x_vf_मुक्त(bp, vf);
	अगर (rc)
		WARN(rc,
		     "VF[%d] Failed to allocate resources for release op- rc=%d\n",
		     vf->असल_vfid, rc);
	bnx2x_unlock_vf_pf_channel(bp, vf, CHANNEL_TLV_PF_RELEASE_VF);
	वापस rc;
पूर्ण

व्योम bnx2x_lock_vf_pf_channel(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			      क्रमागत channel_tlvs tlv)
अणु
	/* we करोn't lock the channel क्रम unsupported tlvs */
	अगर (!bnx2x_tlv_supported(tlv)) अणु
		BNX2X_ERR("attempting to lock with unsupported tlv. Aborting\n");
		वापस;
	पूर्ण

	/* lock the channel */
	mutex_lock(&vf->op_mutex);

	/* record the locking op */
	vf->op_current = tlv;

	/* log the lock */
	DP(BNX2X_MSG_IOV, "VF[%d]: vf pf channel locked by %d\n",
	   vf->असल_vfid, tlv);
पूर्ण

व्योम bnx2x_unlock_vf_pf_channel(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				क्रमागत channel_tlvs expected_tlv)
अणु
	क्रमागत channel_tlvs current_tlv;

	अगर (!vf) अणु
		BNX2X_ERR("VF was %p\n", vf);
		वापस;
	पूर्ण

	current_tlv = vf->op_current;

	/* we करोn't unlock the channel क्रम unsupported tlvs */
	अगर (!bnx2x_tlv_supported(expected_tlv))
		वापस;

	WARN(expected_tlv != vf->op_current,
	     "lock mismatch: expected %d found %d", expected_tlv,
	     vf->op_current);

	/* record the locking op */
	vf->op_current = CHANNEL_TLV_NONE;

	/* lock the channel */
	mutex_unlock(&vf->op_mutex);

	/* log the unlock */
	DP(BNX2X_MSG_IOV, "VF[%d]: vf pf channel unlocked by %d\n",
	   vf->असल_vfid, current_tlv);
पूर्ण

अटल पूर्णांक bnx2x_set_pf_tx_चयनing(काष्ठा bnx2x *bp, bool enable)
अणु
	काष्ठा bnx2x_queue_state_params q_params;
	u32 prev_flags;
	पूर्णांक i, rc;

	/* Verअगरy changes are needed and record current Tx चयनing state */
	prev_flags = bp->flags;
	अगर (enable)
		bp->flags |= TX_SWITCHING;
	अन्यथा
		bp->flags &= ~TX_SWITCHING;
	अगर (prev_flags == bp->flags)
		वापस 0;

	/* Verअगरy state enables the sending of queue ramrods */
	अगर ((bp->state != BNX2X_STATE_OPEN) ||
	    (bnx2x_get_q_logical_state(bp,
				      &bnx2x_sp_obj(bp, &bp->fp[0]).q_obj) !=
	     BNX2X_Q_LOGICAL_STATE_ACTIVE))
		वापस 0;

	/* send q. update ramrod to configure Tx चयनing */
	स_रखो(&q_params, 0, माप(q_params));
	__set_bit(RAMROD_COMP_WAIT, &q_params.ramrod_flags);
	q_params.cmd = BNX2X_Q_CMD_UPDATE;
	__set_bit(BNX2X_Q_UPDATE_TX_SWITCHING_CHNG,
		  &q_params.params.update.update_flags);
	अगर (enable)
		__set_bit(BNX2X_Q_UPDATE_TX_SWITCHING,
			  &q_params.params.update.update_flags);
	अन्यथा
		__clear_bit(BNX2X_Q_UPDATE_TX_SWITCHING,
			    &q_params.params.update.update_flags);

	/* send the ramrod on all the queues of the PF */
	क्रम_each_eth_queue(bp, i) अणु
		काष्ठा bnx2x_fastpath *fp = &bp->fp[i];
		पूर्णांक tx_idx;

		/* Set the appropriate Queue object */
		q_params.q_obj = &bnx2x_sp_obj(bp, fp).q_obj;

		क्रम (tx_idx = FIRST_TX_COS_INDEX;
		     tx_idx < fp->max_cos; tx_idx++) अणु
			q_params.params.update.cid_index = tx_idx;

			/* Update the Queue state */
			rc = bnx2x_queue_state_change(bp, &q_params);
			अगर (rc) अणु
				BNX2X_ERR("Failed to configure Tx switching\n");
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण

	DP(BNX2X_MSG_IOV, "%s Tx Switching\n", enable ? "Enabled" : "Disabled");
	वापस 0;
पूर्ण

पूर्णांक bnx2x_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs_param)
अणु
	काष्ठा bnx2x *bp = netdev_priv(pci_get_drvdata(dev));

	अगर (!IS_SRIOV(bp)) अणु
		BNX2X_ERR("failed to configure SR-IOV since vfdb was not allocated. Check dmesg for errors in probe stage\n");
		वापस -EINVAL;
	पूर्ण

	DP(BNX2X_MSG_IOV, "bnx2x_sriov_configure called with %d, BNX2X_NR_VIRTFN(bp) was %d\n",
	   num_vfs_param, BNX2X_NR_VIRTFN(bp));

	/* HW channel is only operational when PF is up */
	अगर (bp->state != BNX2X_STATE_OPEN) अणु
		BNX2X_ERR("VF num configuration via sysfs not supported while PF is down\n");
		वापस -EINVAL;
	पूर्ण

	/* we are always bound by the total_vfs in the configuration space */
	अगर (num_vfs_param > BNX2X_NR_VIRTFN(bp)) अणु
		BNX2X_ERR("truncating requested number of VFs (%d) down to maximum allowed (%d)\n",
			  num_vfs_param, BNX2X_NR_VIRTFN(bp));
		num_vfs_param = BNX2X_NR_VIRTFN(bp);
	पूर्ण

	bp->requested_nr_virtfn = num_vfs_param;
	अगर (num_vfs_param == 0) अणु
		bnx2x_set_pf_tx_चयनing(bp, false);
		bnx2x_disable_sriov(bp);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस bnx2x_enable_sriov(bp);
	पूर्ण
पूर्ण

#घोषणा IGU_ENTRY_SIZE 4

पूर्णांक bnx2x_enable_sriov(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc = 0, req_vfs = bp->requested_nr_virtfn;
	पूर्णांक vf_idx, sb_idx, vfq_idx, qcount, first_vf;
	u32 igu_entry, address;
	u16 num_vf_queues;

	अगर (req_vfs == 0)
		वापस 0;

	first_vf = bp->vfdb->sriov.first_vf_in_pf;

	/* अटलally distribute vf sb pool between VFs */
	num_vf_queues = min_t(u16, BNX2X_VF_MAX_QUEUES,
			      BP_VFDB(bp)->vf_sbs_pool / req_vfs);

	/* zero previous values learned from igu cam */
	क्रम (vf_idx = 0; vf_idx < req_vfs; vf_idx++) अणु
		काष्ठा bnx2x_virtf *vf = BP_VF(bp, vf_idx);

		vf->sb_count = 0;
		vf_sb_count(BP_VF(bp, vf_idx)) = 0;
	पूर्ण
	bp->vfdb->vf_sbs_pool = 0;

	/* prepare IGU cam */
	sb_idx = BP_VFDB(bp)->first_vf_igu_entry;
	address = IGU_REG_MAPPING_MEMORY + sb_idx * IGU_ENTRY_SIZE;
	क्रम (vf_idx = first_vf; vf_idx < first_vf + req_vfs; vf_idx++) अणु
		क्रम (vfq_idx = 0; vfq_idx < num_vf_queues; vfq_idx++) अणु
			igu_entry = vf_idx << IGU_REG_MAPPING_MEMORY_FID_SHIFT |
				vfq_idx << IGU_REG_MAPPING_MEMORY_VECTOR_SHIFT |
				IGU_REG_MAPPING_MEMORY_VALID;
			DP(BNX2X_MSG_IOV, "assigning sb %d to vf %d\n",
			   sb_idx, vf_idx);
			REG_WR(bp, address, igu_entry);
			sb_idx++;
			address += IGU_ENTRY_SIZE;
		पूर्ण
	पूर्ण

	/* Reinitialize vf database according to igu cam */
	bnx2x_get_vf_igu_cam_info(bp);

	DP(BNX2X_MSG_IOV, "vf_sbs_pool %d, num_vf_queues %d\n",
	   BP_VFDB(bp)->vf_sbs_pool, num_vf_queues);

	qcount = 0;
	क्रम_each_vf(bp, vf_idx) अणु
		काष्ठा bnx2x_virtf *vf = BP_VF(bp, vf_idx);

		/* set local queue arrays */
		vf->vfqs = &bp->vfdb->vfqs[qcount];
		qcount += vf_sb_count(vf);
		bnx2x_iov_अटल_resc(bp, vf);
	पूर्ण

	/* prepare msix vectors in VF configuration space - the value in the
	 * PCI configuration space should be the index of the last entry,
	 * namely one less than the actual size of the table
	 */
	क्रम (vf_idx = first_vf; vf_idx < first_vf + req_vfs; vf_idx++) अणु
		bnx2x_pretend_func(bp, HW_VF_HANDLE(bp, vf_idx));
		REG_WR(bp, PCICFG_OFFSET + GRC_CONFIG_REG_VF_MSIX_CONTROL,
		       num_vf_queues - 1);
		DP(BNX2X_MSG_IOV, "set msix vec num in VF %d cfg space to %d\n",
		   vf_idx, num_vf_queues - 1);
	पूर्ण
	bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));

	/* enable sriov. This will probe all the VFs, and consequentially cause
	 * the "acquire" messages to appear on the VF PF channel.
	 */
	DP(BNX2X_MSG_IOV, "about to call enable sriov\n");
	bnx2x_disable_sriov(bp);

	rc = bnx2x_set_pf_tx_चयनing(bp, true);
	अगर (rc)
		वापस rc;

	rc = pci_enable_sriov(bp->pdev, req_vfs);
	अगर (rc) अणु
		BNX2X_ERR("pci_enable_sriov failed with %d\n", rc);
		वापस rc;
	पूर्ण
	DP(BNX2X_MSG_IOV, "sriov enabled (%d vfs)\n", req_vfs);
	वापस req_vfs;
पूर्ण

व्योम bnx2x_pf_set_vfs_vlan(काष्ठा bnx2x *bp)
अणु
	पूर्णांक vfidx;
	काष्ठा pf_vf_bulletin_content *bulletin;

	DP(BNX2X_MSG_IOV, "configuring vlan for VFs from sp-task\n");
	क्रम_each_vf(bp, vfidx) अणु
		bulletin = BP_VF_BULLETIN(bp, vfidx);
		अगर (bulletin->valid_biपंचांगap & (1 << VLAN_VALID))
			bnx2x_set_vf_vlan(bp->dev, vfidx, bulletin->vlan, 0,
					  htons(ETH_P_8021Q));
	पूर्ण
पूर्ण

व्योम bnx2x_disable_sriov(काष्ठा bnx2x *bp)
अणु
	अगर (pci_vfs_asचिन्हित(bp->pdev)) अणु
		DP(BNX2X_MSG_IOV,
		   "Unloading driver while VFs are assigned - VFs will not be deallocated\n");
		वापस;
	पूर्ण

	pci_disable_sriov(bp->pdev);
पूर्ण

अटल पूर्णांक bnx2x_vf_op_prep(काष्ठा bnx2x *bp, पूर्णांक vfidx,
			    काष्ठा bnx2x_virtf **vf,
			    काष्ठा pf_vf_bulletin_content **bulletin,
			    bool test_queue)
अणु
	अगर (bp->state != BNX2X_STATE_OPEN) अणु
		BNX2X_ERR("PF is down - can't utilize iov-related functionality\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!IS_SRIOV(bp)) अणु
		BNX2X_ERR("sriov is disabled - can't utilize iov-related functionality\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vfidx >= BNX2X_NR_VIRTFN(bp)) अणु
		BNX2X_ERR("VF is uninitialized - can't utilize iov-related functionality. vfidx was %d BNX2X_NR_VIRTFN was %d\n",
			  vfidx, BNX2X_NR_VIRTFN(bp));
		वापस -EINVAL;
	पूर्ण

	/* init members */
	*vf = BP_VF(bp, vfidx);
	*bulletin = BP_VF_BULLETIN(bp, vfidx);

	अगर (!*vf) अणु
		BNX2X_ERR("Unable to get VF structure for vfidx %d\n", vfidx);
		वापस -EINVAL;
	पूर्ण

	अगर (test_queue && !(*vf)->vfqs) अणु
		BNX2X_ERR("vfqs struct is null. Was this invoked before dynamically enabling SR-IOV? vfidx was %d\n",
			  vfidx);
		वापस -EINVAL;
	पूर्ण

	अगर (!*bulletin) अणु
		BNX2X_ERR("Bulletin Board struct is null for vfidx %d\n",
			  vfidx);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bnx2x_get_vf_config(काष्ठा net_device *dev, पूर्णांक vfidx,
			काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा bnx2x_virtf *vf = शून्य;
	काष्ठा pf_vf_bulletin_content *bulletin = शून्य;
	काष्ठा bnx2x_vlan_mac_obj *mac_obj;
	काष्ठा bnx2x_vlan_mac_obj *vlan_obj;
	पूर्णांक rc;

	/* sanity and init */
	rc = bnx2x_vf_op_prep(bp, vfidx, &vf, &bulletin, true);
	अगर (rc)
		वापस rc;

	mac_obj = &bnx2x_leading_vfq(vf, mac_obj);
	vlan_obj = &bnx2x_leading_vfq(vf, vlan_obj);
	अगर (!mac_obj || !vlan_obj) अणु
		BNX2X_ERR("VF partially initialized\n");
		वापस -EINVAL;
	पूर्ण

	ivi->vf = vfidx;
	ivi->qos = 0;
	ivi->max_tx_rate = 10000; /* always 10G. TBA take from link काष्ठा */
	ivi->min_tx_rate = 0;
	ivi->spoofchk = vf->spoofchk ? 1 : 0;
	ivi->linkstate = vf->link_cfg;
	अगर (vf->state == VF_ENABLED) अणु
		/* mac and vlan are in vlan_mac objects */
		अगर (bnx2x_validate_vf_sp_objs(bp, vf, false)) अणु
			mac_obj->get_n_elements(bp, mac_obj, 1, (u8 *)&ivi->mac,
						0, ETH_ALEN);
			vlan_obj->get_n_elements(bp, vlan_obj, 1,
						 (u8 *)&ivi->vlan, 0,
						 VLAN_HLEN);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&bp->vfdb->bulletin_mutex);
		/* mac */
		अगर (bulletin->valid_biपंचांगap & (1 << MAC_ADDR_VALID))
			/* mac configured by nकरो so its in bulletin board */
			स_नकल(&ivi->mac, bulletin->mac, ETH_ALEN);
		अन्यथा
			/* function has not been loaded yet. Show mac as 0s */
			eth_zero_addr(ivi->mac);

		/* vlan */
		अगर (bulletin->valid_biपंचांगap & (1 << VLAN_VALID))
			/* vlan configured by nकरो so its in bulletin board */
			स_नकल(&ivi->vlan, &bulletin->vlan, VLAN_HLEN);
		अन्यथा
			/* function has not been loaded yet. Show vlans as 0s */
			स_रखो(&ivi->vlan, 0, VLAN_HLEN);

		mutex_unlock(&bp->vfdb->bulletin_mutex);
	पूर्ण

	वापस 0;
पूर्ण

/* New mac क्रम VF. Consider these हालs:
 * 1. VF hasn't been acquired yet - save the mac in local bulletin board and
 *    supply at acquire.
 * 2. VF has alपढ़ोy been acquired but has not yet initialized - store in local
 *    bulletin board. mac will be posted on VF bulletin board after VF init. VF
 *    will configure this mac when it is पढ़ोy.
 * 3. VF has alपढ़ोy initialized but has not yet setup a queue - post the new
 *    mac on VF's bulletin board right now. VF will configure this mac when it
 *    is पढ़ोy.
 * 4. VF has alपढ़ोy set a queue - delete any macs alपढ़ोy configured क्रम this
 *    queue and manually config the new mac.
 * In any event, once this function has been called refuse any attempts by the
 * VF to configure any mac क्रम itself except क्रम this mac. In हाल of a race
 * where the VF fails to see the new post on its bulletin board beक्रमe sending a
 * mac configuration request, the PF will simply fail the request and VF can try
 * again after consulting its bulletin board.
 */
पूर्णांक bnx2x_set_vf_mac(काष्ठा net_device *dev, पूर्णांक vfidx, u8 *mac)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक rc, q_logical_state;
	काष्ठा bnx2x_virtf *vf = शून्य;
	काष्ठा pf_vf_bulletin_content *bulletin = शून्य;

	अगर (!is_valid_ether_addr(mac)) अणु
		BNX2X_ERR("mac address invalid\n");
		वापस -EINVAL;
	पूर्ण

	/* sanity and init */
	rc = bnx2x_vf_op_prep(bp, vfidx, &vf, &bulletin, true);
	अगर (rc)
		वापस rc;

	mutex_lock(&bp->vfdb->bulletin_mutex);

	/* update PF's copy of the VF's bulletin. Will no दीर्घer accept mac
	 * configuration requests from vf unless match this mac
	 */
	bulletin->valid_biपंचांगap |= 1 << MAC_ADDR_VALID;
	स_नकल(bulletin->mac, mac, ETH_ALEN);

	/* Post update on VF's bulletin board */
	rc = bnx2x_post_vf_bulletin(bp, vfidx);

	/* release lock beक्रमe checking वापस code */
	mutex_unlock(&bp->vfdb->bulletin_mutex);

	अगर (rc) अणु
		BNX2X_ERR("failed to update VF[%d] bulletin\n", vfidx);
		वापस rc;
	पूर्ण

	q_logical_state =
		bnx2x_get_q_logical_state(bp, &bnx2x_leading_vfq(vf, sp_obj));
	अगर (vf->state == VF_ENABLED &&
	    q_logical_state == BNX2X_Q_LOGICAL_STATE_ACTIVE) अणु
		/* configure the mac in device on this vf's queue */
		अचिन्हित दीर्घ ramrod_flags = 0;
		काष्ठा bnx2x_vlan_mac_obj *mac_obj;

		/* User should be able to see failure reason in प्रणाली logs */
		अगर (!bnx2x_validate_vf_sp_objs(bp, vf, true))
			वापस -EINVAL;

		/* must lock vfpf channel to protect against vf flows */
		bnx2x_lock_vf_pf_channel(bp, vf, CHANNEL_TLV_PF_SET_MAC);

		/* हटाओ existing eth macs */
		mac_obj = &bnx2x_leading_vfq(vf, mac_obj);
		rc = bnx2x_del_all_macs(bp, mac_obj, BNX2X_ETH_MAC, true);
		अगर (rc) अणु
			BNX2X_ERR("failed to delete eth macs\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		/* हटाओ existing uc list macs */
		rc = bnx2x_del_all_macs(bp, mac_obj, BNX2X_UC_LIST_MAC, true);
		अगर (rc) अणु
			BNX2X_ERR("failed to delete uc_list macs\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		/* configure the new mac to device */
		__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
		bnx2x_set_mac_one(bp, (u8 *)&bulletin->mac, mac_obj, true,
				  BNX2X_ETH_MAC, &ramrod_flags);

out:
		bnx2x_unlock_vf_pf_channel(bp, vf, CHANNEL_TLV_PF_SET_MAC);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम bnx2x_set_vf_vlan_acceptance(काष्ठा bnx2x *bp,
					 काष्ठा bnx2x_virtf *vf, bool accept)
अणु
	काष्ठा bnx2x_rx_mode_ramrod_params rx_ramrod;
	अचिन्हित दीर्घ accept_flags;

	/* need to हटाओ/add the VF's accept_any_vlan bit */
	accept_flags = bnx2x_leading_vfq(vf, accept_flags);
	अगर (accept)
		set_bit(BNX2X_ACCEPT_ANY_VLAN, &accept_flags);
	अन्यथा
		clear_bit(BNX2X_ACCEPT_ANY_VLAN, &accept_flags);

	bnx2x_vf_prep_rx_mode(bp, LEADING_IDX, &rx_ramrod, vf,
			      accept_flags);
	bnx2x_leading_vfq(vf, accept_flags) = accept_flags;
	bnx2x_config_rx_mode(bp, &rx_ramrod);
पूर्ण

अटल पूर्णांक bnx2x_set_vf_vlan_filter(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				    u16 vlan, bool add)
अणु
	काष्ठा bnx2x_vlan_mac_ramrod_params ramrod_param;
	अचिन्हित दीर्घ ramrod_flags = 0;
	पूर्णांक rc = 0;

	/* configure the new vlan to device */
	स_रखो(&ramrod_param, 0, माप(ramrod_param));
	__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
	ramrod_param.vlan_mac_obj = &bnx2x_leading_vfq(vf, vlan_obj);
	ramrod_param.ramrod_flags = ramrod_flags;
	ramrod_param.user_req.u.vlan.vlan = vlan;
	ramrod_param.user_req.cmd = add ? BNX2X_VLAN_MAC_ADD
					: BNX2X_VLAN_MAC_DEL;
	rc = bnx2x_config_vlan_mac(bp, &ramrod_param);
	अगर (rc) अणु
		BNX2X_ERR("failed to configure vlan\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bnx2x_set_vf_vlan(काष्ठा net_device *dev, पूर्णांक vfidx, u16 vlan, u8 qos,
		      __be16 vlan_proto)
अणु
	काष्ठा pf_vf_bulletin_content *bulletin = शून्य;
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा bnx2x_vlan_mac_obj *vlan_obj;
	अचिन्हित दीर्घ vlan_mac_flags = 0;
	अचिन्हित दीर्घ ramrod_flags = 0;
	काष्ठा bnx2x_virtf *vf = शून्य;
	पूर्णांक i, rc;

	अगर (vlan > 4095) अणु
		BNX2X_ERR("illegal vlan value %d\n", vlan);
		वापस -EINVAL;
	पूर्ण

	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EPROTONOSUPPORT;

	DP(BNX2X_MSG_IOV, "configuring VF %d with VLAN %d qos %d\n",
	   vfidx, vlan, 0);

	/* sanity and init */
	rc = bnx2x_vf_op_prep(bp, vfidx, &vf, &bulletin, true);
	अगर (rc)
		वापस rc;

	/* update PF's copy of the VF's bulletin. No poपूर्णांक in posting the vlan
	 * to the VF since it करोesn't have anything to करो with it. But it useful
	 * to store it here in हाल the VF is not up yet and we can only
	 * configure the vlan later when it करोes. Treat vlan id 0 as हटाओ the
	 * Host tag.
	 */
	mutex_lock(&bp->vfdb->bulletin_mutex);

	अगर (vlan > 0)
		bulletin->valid_biपंचांगap |= 1 << VLAN_VALID;
	अन्यथा
		bulletin->valid_biपंचांगap &= ~(1 << VLAN_VALID);
	bulletin->vlan = vlan;

	/* Post update on VF's bulletin board */
	rc = bnx2x_post_vf_bulletin(bp, vfidx);
	अगर (rc)
		BNX2X_ERR("failed to update VF[%d] bulletin\n", vfidx);
	mutex_unlock(&bp->vfdb->bulletin_mutex);

	/* is vf initialized and queue set up? */
	अगर (vf->state != VF_ENABLED ||
	    bnx2x_get_q_logical_state(bp, &bnx2x_leading_vfq(vf, sp_obj)) !=
	    BNX2X_Q_LOGICAL_STATE_ACTIVE)
		वापस rc;

	/* User should be able to see error in प्रणाली logs */
	अगर (!bnx2x_validate_vf_sp_objs(bp, vf, true))
		वापस -EINVAL;

	/* must lock vfpf channel to protect against vf flows */
	bnx2x_lock_vf_pf_channel(bp, vf, CHANNEL_TLV_PF_SET_VLAN);

	/* हटाओ existing vlans */
	__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
	vlan_obj = &bnx2x_leading_vfq(vf, vlan_obj);
	rc = vlan_obj->delete_all(bp, vlan_obj, &vlan_mac_flags,
				  &ramrod_flags);
	अगर (rc) अणु
		BNX2X_ERR("failed to delete vlans\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* clear accept_any_vlan when HV क्रमces vlan, otherwise
	 * according to VF capabilities
	 */
	अगर (vlan || !(vf->cfg_flags & VF_CFG_VLAN_FILTER))
		bnx2x_set_vf_vlan_acceptance(bp, vf, !vlan);

	rc = bnx2x_set_vf_vlan_filter(bp, vf, vlan, true);
	अगर (rc)
		जाओ out;

	/* send queue update ramrods to configure शेष vlan and
	 * silent vlan removal
	 */
	क्रम_each_vfq(vf, i) अणु
		काष्ठा bnx2x_queue_state_params q_params = अणुशून्यपूर्ण;
		काष्ठा bnx2x_queue_update_params *update_params;

		q_params.q_obj = &bnx2x_vfq(vf, i, sp_obj);

		/* validate the Q is UP */
		अगर (bnx2x_get_q_logical_state(bp, q_params.q_obj) !=
		    BNX2X_Q_LOGICAL_STATE_ACTIVE)
			जारी;

		__set_bit(RAMROD_COMP_WAIT, &q_params.ramrod_flags);
		q_params.cmd = BNX2X_Q_CMD_UPDATE;
		update_params = &q_params.params.update;
		__set_bit(BNX2X_Q_UPDATE_DEF_VLAN_EN_CHNG,
			  &update_params->update_flags);
		__set_bit(BNX2X_Q_UPDATE_SILENT_VLAN_REM_CHNG,
			  &update_params->update_flags);
		अगर (vlan == 0) अणु
			/* अगर vlan is 0 then we want to leave the VF traffic
			 * untagged, and leave the incoming traffic untouched
			 * (i.e. करो not हटाओ any vlan tags).
			 */
			__clear_bit(BNX2X_Q_UPDATE_DEF_VLAN_EN,
				    &update_params->update_flags);
			__clear_bit(BNX2X_Q_UPDATE_SILENT_VLAN_REM,
				    &update_params->update_flags);
		पूर्ण अन्यथा अणु
			/* configure शेष vlan to vf queue and set silent
			 * vlan removal (the vf reमुख्यs unaware of this vlan).
			 */
			__set_bit(BNX2X_Q_UPDATE_DEF_VLAN_EN,
				  &update_params->update_flags);
			__set_bit(BNX2X_Q_UPDATE_SILENT_VLAN_REM,
				  &update_params->update_flags);
			update_params->def_vlan = vlan;
			update_params->silent_removal_value =
				vlan & VLAN_VID_MASK;
			update_params->silent_removal_mask = VLAN_VID_MASK;
		पूर्ण

		/* Update the Queue state */
		rc = bnx2x_queue_state_change(bp, &q_params);
		अगर (rc) अणु
			BNX2X_ERR("Failed to configure default VLAN queue %d\n",
				  i);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	bnx2x_unlock_vf_pf_channel(bp, vf, CHANNEL_TLV_PF_SET_VLAN);

	अगर (rc)
		DP(BNX2X_MSG_IOV,
		   "updated VF[%d] vlan configuration (vlan = %d)\n",
		   vfidx, vlan);

	वापस rc;
पूर्ण

पूर्णांक bnx2x_set_vf_spoofchk(काष्ठा net_device *dev, पूर्णांक idx, bool val)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा bnx2x_virtf *vf;
	पूर्णांक i, rc = 0;

	vf = BP_VF(bp, idx);
	अगर (!vf)
		वापस -EINVAL;

	/* nothing to करो */
	अगर (vf->spoofchk == val)
		वापस 0;

	vf->spoofchk = val ? 1 : 0;

	DP(BNX2X_MSG_IOV, "%s spoofchk for VF %d\n",
	   val ? "enabling" : "disabling", idx);

	/* is vf initialized and queue set up? */
	अगर (vf->state != VF_ENABLED ||
	    bnx2x_get_q_logical_state(bp, &bnx2x_leading_vfq(vf, sp_obj)) !=
	    BNX2X_Q_LOGICAL_STATE_ACTIVE)
		वापस rc;

	/* User should be able to see error in प्रणाली logs */
	अगर (!bnx2x_validate_vf_sp_objs(bp, vf, true))
		वापस -EINVAL;

	/* send queue update ramrods to configure spoofchk */
	क्रम_each_vfq(vf, i) अणु
		काष्ठा bnx2x_queue_state_params q_params = अणुशून्यपूर्ण;
		काष्ठा bnx2x_queue_update_params *update_params;

		q_params.q_obj = &bnx2x_vfq(vf, i, sp_obj);

		/* validate the Q is UP */
		अगर (bnx2x_get_q_logical_state(bp, q_params.q_obj) !=
		    BNX2X_Q_LOGICAL_STATE_ACTIVE)
			जारी;

		__set_bit(RAMROD_COMP_WAIT, &q_params.ramrod_flags);
		q_params.cmd = BNX2X_Q_CMD_UPDATE;
		update_params = &q_params.params.update;
		__set_bit(BNX2X_Q_UPDATE_ANTI_SPOOF_CHNG,
			  &update_params->update_flags);
		अगर (val) अणु
			__set_bit(BNX2X_Q_UPDATE_ANTI_SPOOF,
				  &update_params->update_flags);
		पूर्ण अन्यथा अणु
			__clear_bit(BNX2X_Q_UPDATE_ANTI_SPOOF,
				    &update_params->update_flags);
		पूर्ण

		/* Update the Queue state */
		rc = bnx2x_queue_state_change(bp, &q_params);
		अगर (rc) अणु
			BNX2X_ERR("Failed to %s spoofchk on VF %d - vfq %d\n",
				  val ? "enable" : "disable", idx, i);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (!rc)
		DP(BNX2X_MSG_IOV,
		   "%s spoofchk for VF[%d]\n", val ? "Enabled" : "Disabled",
		   idx);

	वापस rc;
पूर्ण

/* crc is the first field in the bulletin board. Compute the crc over the
 * entire bulletin board excluding the crc field itself. Use the length field
 * as the Bulletin Board was posted by a PF with possibly a dअगरferent version
 * from the vf which will sample it. Thereक्रमe, the length is computed by the
 * PF and then used blindly by the VF.
 */
u32 bnx2x_crc_vf_bulletin(काष्ठा pf_vf_bulletin_content *bulletin)
अणु
	वापस crc32(BULLETIN_CRC_SEED,
		 ((u8 *)bulletin) + माप(bulletin->crc),
		 bulletin->length - माप(bulletin->crc));
पूर्ण

/* Check क्रम new posts on the bulletin board */
क्रमागत sample_bulletin_result bnx2x_sample_bulletin(काष्ठा bnx2x *bp)
अणु
	काष्ठा pf_vf_bulletin_content *bulletin;
	पूर्णांक attempts;

	/* sampling काष्ठाure in mid post may result with corrupted data
	 * validate crc to ensure coherency.
	 */
	क्रम (attempts = 0; attempts < BULLETIN_ATTEMPTS; attempts++) अणु
		u32 crc;

		/* sample the bulletin board */
		स_नकल(&bp->shaकरोw_bulletin, bp->pf2vf_bulletin,
		       माप(जोड़ pf_vf_bulletin));

		crc = bnx2x_crc_vf_bulletin(&bp->shaकरोw_bulletin.content);

		अगर (bp->shaकरोw_bulletin.content.crc == crc)
			अवरोध;

		BNX2X_ERR("bad crc on bulletin board. Contained %x computed %x\n",
			  bp->shaकरोw_bulletin.content.crc, crc);
	पूर्ण

	अगर (attempts >= BULLETIN_ATTEMPTS) अणु
		BNX2X_ERR("pf to vf bulletin board crc was wrong %d consecutive times. Aborting\n",
			  attempts);
		वापस PFVF_BULLETIN_CRC_ERR;
	पूर्ण
	bulletin = &bp->shaकरोw_bulletin.content;

	/* bulletin board hasn't changed since last sample */
	अगर (bp->old_bulletin.version == bulletin->version)
		वापस PFVF_BULLETIN_UNCHANGED;

	/* the mac address in bulletin board is valid and is new */
	अगर (bulletin->valid_biपंचांगap & 1 << MAC_ADDR_VALID &&
	    !ether_addr_equal(bulletin->mac, bp->old_bulletin.mac)) अणु
		/* update new mac to net device */
		स_नकल(bp->dev->dev_addr, bulletin->mac, ETH_ALEN);
	पूर्ण

	अगर (bulletin->valid_biपंचांगap & (1 << LINK_VALID)) अणु
		DP(BNX2X_MSG_IOV, "link update speed %d flags %x\n",
		   bulletin->link_speed, bulletin->link_flags);

		bp->vf_link_vars.line_speed = bulletin->link_speed;
		bp->vf_link_vars.link_report_flags = 0;
		/* Link is करोwn */
		अगर (bulletin->link_flags & VFPF_LINK_REPORT_LINK_DOWN)
			__set_bit(BNX2X_LINK_REPORT_LINK_DOWN,
				  &bp->vf_link_vars.link_report_flags);
		/* Full DUPLEX */
		अगर (bulletin->link_flags & VFPF_LINK_REPORT_FULL_DUPLEX)
			__set_bit(BNX2X_LINK_REPORT_FD,
				  &bp->vf_link_vars.link_report_flags);
		/* Rx Flow Control is ON */
		अगर (bulletin->link_flags & VFPF_LINK_REPORT_RX_FC_ON)
			__set_bit(BNX2X_LINK_REPORT_RX_FC_ON,
				  &bp->vf_link_vars.link_report_flags);
		/* Tx Flow Control is ON */
		अगर (bulletin->link_flags & VFPF_LINK_REPORT_TX_FC_ON)
			__set_bit(BNX2X_LINK_REPORT_TX_FC_ON,
				  &bp->vf_link_vars.link_report_flags);
		__bnx2x_link_report(bp);
	पूर्ण

	/* copy new bulletin board to bp */
	स_नकल(&bp->old_bulletin, bulletin,
	       माप(काष्ठा pf_vf_bulletin_content));

	वापस PFVF_BULLETIN_UPDATED;
पूर्ण

व्योम bnx2x_समयr_sriov(काष्ठा bnx2x *bp)
अणु
	bnx2x_sample_bulletin(bp);

	/* अगर channel is करोwn we need to self deकाष्ठा */
	अगर (bp->old_bulletin.valid_biपंचांगap & 1 << CHANNEL_DOWN)
		bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_VFPF_CHANNEL_DOWN,
				       BNX2X_MSG_IOV);
पूर्ण

व्योम __iomem *bnx2x_vf_करोorbells(काष्ठा bnx2x *bp)
अणु
	/* vf करोorbells are embedded within the regview */
	वापस bp->regview + PXP_VF_ADDR_DB_START;
पूर्ण

व्योम bnx2x_vf_pci_dealloc(काष्ठा bnx2x *bp)
अणु
	BNX2X_PCI_FREE(bp->vf2pf_mbox, bp->vf2pf_mbox_mapping,
		       माप(काष्ठा bnx2x_vf_mbx_msg));
	BNX2X_PCI_FREE(bp->pf2vf_bulletin, bp->pf2vf_bulletin_mapping,
		       माप(जोड़ pf_vf_bulletin));
पूर्ण

पूर्णांक bnx2x_vf_pci_alloc(काष्ठा bnx2x *bp)
अणु
	mutex_init(&bp->vf2pf_mutex);

	/* allocate vf2pf mailbox क्रम vf to pf channel */
	bp->vf2pf_mbox = BNX2X_PCI_ALLOC(&bp->vf2pf_mbox_mapping,
					 माप(काष्ठा bnx2x_vf_mbx_msg));
	अगर (!bp->vf2pf_mbox)
		जाओ alloc_mem_err;

	/* allocate pf 2 vf bulletin board */
	bp->pf2vf_bulletin = BNX2X_PCI_ALLOC(&bp->pf2vf_bulletin_mapping,
					     माप(जोड़ pf_vf_bulletin));
	अगर (!bp->pf2vf_bulletin)
		जाओ alloc_mem_err;

	bnx2x_vf_bulletin_finalize(&bp->pf2vf_bulletin->content, true);

	वापस 0;

alloc_mem_err:
	bnx2x_vf_pci_dealloc(bp);
	वापस -ENOMEM;
पूर्ण

व्योम bnx2x_iov_channel_करोwn(काष्ठा bnx2x *bp)
अणु
	पूर्णांक vf_idx;
	काष्ठा pf_vf_bulletin_content *bulletin;

	अगर (!IS_SRIOV(bp))
		वापस;

	क्रम_each_vf(bp, vf_idx) अणु
		/* locate this VFs bulletin board and update the channel करोwn
		 * bit
		 */
		bulletin = BP_VF_BULLETIN(bp, vf_idx);
		bulletin->valid_biपंचांगap |= 1 << CHANNEL_DOWN;

		/* update vf bulletin board */
		bnx2x_post_vf_bulletin(bp, vf_idx);
	पूर्ण
पूर्ण

व्योम bnx2x_iov_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnx2x *bp = container_of(work, काष्ठा bnx2x, iov_task.work);

	अगर (!netअगर_running(bp->dev))
		वापस;

	अगर (test_and_clear_bit(BNX2X_IOV_HANDLE_FLR,
			       &bp->iov_task_state))
		bnx2x_vf_handle_flr_event(bp);

	अगर (test_and_clear_bit(BNX2X_IOV_HANDLE_VF_MSG,
			       &bp->iov_task_state))
		bnx2x_vf_mbx(bp);
पूर्ण

व्योम bnx2x_schedule_iov_task(काष्ठा bnx2x *bp, क्रमागत bnx2x_iov_flag flag)
अणु
	smp_mb__beक्रमe_atomic();
	set_bit(flag, &bp->iov_task_state);
	smp_mb__after_atomic();
	DP(BNX2X_MSG_IOV, "Scheduling iov task [Flag: %d]\n", flag);
	queue_delayed_work(bnx2x_iov_wq, &bp->iov_task, 0);
पूर्ण
