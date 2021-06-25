<शैली गुरु>
/* bnx2x_dcb.c: QLogic Everest network driver.
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
 * Written by: Dmitry Kravkov
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/rtnetlink.h>
#समावेश <net/dcbnl.h>

#समावेश "bnx2x.h"
#समावेश "bnx2x_cmn.h"
#समावेश "bnx2x_dcb.h"

/* क्रमward declarations of dcbx related functions */
अटल व्योम bnx2x_pfc_set_pfc(काष्ठा bnx2x *bp);
अटल व्योम bnx2x_dcbx_update_ets_params(काष्ठा bnx2x *bp);
अटल व्योम bnx2x_dcbx_get_ets_pri_pg_tbl(काष्ठा bnx2x *bp,
					  u32 *set_configuration_ets_pg,
					  u32 *pri_pg_tbl);
अटल व्योम bnx2x_dcbx_get_num_pg_traf_type(काष्ठा bnx2x *bp,
					    u32 *pg_pri_orginal_spपढ़ो,
					    काष्ठा pg_help_data *help_data);
अटल व्योम bnx2x_dcbx_fill_cos_params(काष्ठा bnx2x *bp,
				       काष्ठा pg_help_data *help_data,
				       काष्ठा dcbx_ets_feature *ets,
				       u32 *pg_pri_orginal_spपढ़ो);
अटल व्योम bnx2x_dcbx_separate_छोड़ोable_from_non(काष्ठा bnx2x *bp,
				काष्ठा cos_help_data *cos_data,
				u32 *pg_pri_orginal_spपढ़ो,
				काष्ठा dcbx_ets_feature *ets);
अटल व्योम bnx2x_dcbx_fw_काष्ठा(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_func_tx_start_params*);

/* helpers: पढ़ो/ग_लिखो len bytes from addr पूर्णांकo buff by REG_RD/REG_WR */
अटल व्योम bnx2x_पढ़ो_data(काष्ठा bnx2x *bp, u32 *buff,
				   u32 addr, u32 len)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < len; i += 4, buff++)
		*buff = REG_RD(bp, addr + i);
पूर्ण

अटल व्योम bnx2x_ग_लिखो_data(काष्ठा bnx2x *bp, u32 *buff,
				    u32 addr, u32 len)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < len; i += 4, buff++)
		REG_WR(bp, addr + i, *buff);
पूर्ण

अटल व्योम bnx2x_pfc_set(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_nig_brb_pfc_port_params pfc_params = अणु0पूर्ण;
	u32 pri_bit, val = 0;
	पूर्णांक i;

	pfc_params.num_of_rx_cos_priority_mask =
					bp->dcbx_port_params.ets.num_of_cos;

	/* Tx COS configuration */
	क्रम (i = 0; i < bp->dcbx_port_params.ets.num_of_cos; i++)
		/*
		 * We configure only the छोड़ोable bits (non छोड़ोable aren't
		 * configured at all) it's करोne to aव्योम false छोड़ोs from
		 * network
		 */
		pfc_params.rx_cos_priority_mask[i] =
			bp->dcbx_port_params.ets.cos_params[i].pri_biपंचांगask
				& DCBX_PFC_PRI_PAUSE_MASK(bp);

	/*
	 * Rx COS configuration
	 * Changing PFC RX configuration .
	 * In RX COS0 will always be configured to lossless and COS1 to lossy
	 */
	क्रम (i = 0 ; i < MAX_PFC_PRIORITIES ; i++) अणु
		pri_bit = 1 << i;

		अगर (!(pri_bit & DCBX_PFC_PRI_PAUSE_MASK(bp)))
			val |= 1 << (i * 4);
	पूर्ण

	pfc_params.pkt_priority_to_cos = val;

	/* RX COS0 */
	pfc_params.llfc_low_priority_classes = DCBX_PFC_PRI_PAUSE_MASK(bp);
	/* RX COS1 */
	pfc_params.llfc_high_priority_classes = 0;

	bnx2x_acquire_phy_lock(bp);
	bp->link_params.feature_config_flags |= FEATURE_CONFIG_PFC_ENABLED;
	bnx2x_update_pfc(&bp->link_params, &bp->link_vars, &pfc_params);
	bnx2x_release_phy_lock(bp);
पूर्ण

अटल व्योम bnx2x_pfc_clear(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_nig_brb_pfc_port_params nig_params = अणु0पूर्ण;
	nig_params.छोड़ो_enable = 1;
	bnx2x_acquire_phy_lock(bp);
	bp->link_params.feature_config_flags &= ~FEATURE_CONFIG_PFC_ENABLED;
	bnx2x_update_pfc(&bp->link_params, &bp->link_vars, &nig_params);
	bnx2x_release_phy_lock(bp);
पूर्ण

अटल व्योम  bnx2x_dump_dcbx_drv_param(काष्ठा bnx2x *bp,
				       काष्ठा dcbx_features *features,
				       u32 error)
अणु
	u8 i = 0;
	DP(NETIF_MSG_LINK, "local_mib.error %x\n", error);

	/* PG */
	DP(NETIF_MSG_LINK,
	   "local_mib.features.ets.enabled %x\n", features->ets.enabled);
	क्रम (i = 0; i < DCBX_MAX_NUM_PG_BW_ENTRIES; i++)
		DP(NETIF_MSG_LINK,
		   "local_mib.features.ets.pg_bw_tbl[%d] %d\n", i,
		   DCBX_PG_BW_GET(features->ets.pg_bw_tbl, i));
	क्रम (i = 0; i < DCBX_MAX_NUM_PRI_PG_ENTRIES; i++)
		DP(NETIF_MSG_LINK,
		   "local_mib.features.ets.pri_pg_tbl[%d] %d\n", i,
		   DCBX_PRI_PG_GET(features->ets.pri_pg_tbl, i));

	/* pfc */
	DP(BNX2X_MSG_DCB, "dcbx_features.pfc.pri_en_bitmap %x\n",
					features->pfc.pri_en_biपंचांगap);
	DP(BNX2X_MSG_DCB, "dcbx_features.pfc.pfc_caps %x\n",
					features->pfc.pfc_caps);
	DP(BNX2X_MSG_DCB, "dcbx_features.pfc.enabled %x\n",
					features->pfc.enabled);

	DP(BNX2X_MSG_DCB, "dcbx_features.app.default_pri %x\n",
					features->app.शेष_pri);
	DP(BNX2X_MSG_DCB, "dcbx_features.app.tc_supported %x\n",
					features->app.tc_supported);
	DP(BNX2X_MSG_DCB, "dcbx_features.app.enabled %x\n",
					features->app.enabled);
	क्रम (i = 0; i < DCBX_MAX_APP_PROTOCOL; i++) अणु
		DP(BNX2X_MSG_DCB,
		   "dcbx_features.app.app_pri_tbl[%x].app_id %x\n",
		   i, features->app.app_pri_tbl[i].app_id);
		DP(BNX2X_MSG_DCB,
		   "dcbx_features.app.app_pri_tbl[%x].pri_bitmap %x\n",
		   i, features->app.app_pri_tbl[i].pri_biपंचांगap);
		DP(BNX2X_MSG_DCB,
		   "dcbx_features.app.app_pri_tbl[%x].appBitfield %x\n",
		   i, features->app.app_pri_tbl[i].appBitfield);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_dcbx_get_ap_priority(काष्ठा bnx2x *bp,
				       u8 pri_biपंचांगap,
				       u8 llfc_traf_type)
अणु
	u32 pri = MAX_PFC_PRIORITIES;
	u32 index = MAX_PFC_PRIORITIES - 1;
	u32 pri_mask;
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;

	/* Choose the highest priority */
	जबतक ((MAX_PFC_PRIORITIES == pri) && (0 != index)) अणु
		pri_mask = 1 << index;
		अगर (GET_FLAGS(pri_biपंचांगap, pri_mask))
			pri = index ;
		index--;
	पूर्ण

	अगर (pri < MAX_PFC_PRIORITIES)
		ttp[llfc_traf_type] = max_t(u32, ttp[llfc_traf_type], pri);
पूर्ण

अटल व्योम bnx2x_dcbx_get_ap_feature(काष्ठा bnx2x *bp,
				   काष्ठा dcbx_app_priority_feature *app,
				   u32 error) अणु
	u8 index;
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;
	u8 iscsi_pri_found = 0, fcoe_pri_found = 0;

	अगर (GET_FLAGS(error, DCBX_LOCAL_APP_ERROR))
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_APP_ERROR\n");

	अगर (GET_FLAGS(error, DCBX_LOCAL_APP_MISMATCH))
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_APP_MISMATCH\n");

	अगर (GET_FLAGS(error, DCBX_REMOTE_APP_TLV_NOT_FOUND))
		DP(BNX2X_MSG_DCB, "DCBX_REMOTE_APP_TLV_NOT_FOUND\n");
	अगर (app->enabled &&
	    !GET_FLAGS(error, DCBX_LOCAL_APP_ERROR | DCBX_LOCAL_APP_MISMATCH |
			      DCBX_REMOTE_APP_TLV_NOT_FOUND)) अणु

		bp->dcbx_port_params.app.enabled = true;

		/* Use 0 as the शेष application priority क्रम all. */
		क्रम (index = 0 ; index < LLFC_DRIVER_TRAFFIC_TYPE_MAX; index++)
			ttp[index] = 0;

		क्रम (index = 0 ; index < DCBX_MAX_APP_PROTOCOL; index++) अणु
			काष्ठा dcbx_app_priority_entry *entry =
							app->app_pri_tbl;
			क्रमागत traffic_type type = MAX_TRAFFIC_TYPE;

			अगर (GET_FLAGS(entry[index].appBitfield,
				      DCBX_APP_SF_DEFAULT) &&
			    GET_FLAGS(entry[index].appBitfield,
				      DCBX_APP_SF_ETH_TYPE)) अणु
				type = LLFC_TRAFFIC_TYPE_NW;
			पूर्ण अन्यथा अगर (GET_FLAGS(entry[index].appBitfield,
					     DCBX_APP_SF_PORT) &&
				   TCP_PORT_ISCSI == entry[index].app_id) अणु
				type = LLFC_TRAFFIC_TYPE_ISCSI;
				iscsi_pri_found = 1;
			पूर्ण अन्यथा अगर (GET_FLAGS(entry[index].appBitfield,
					     DCBX_APP_SF_ETH_TYPE) &&
				   ETH_TYPE_FCOE == entry[index].app_id) अणु
				type = LLFC_TRAFFIC_TYPE_FCOE;
				fcoe_pri_found = 1;
			पूर्ण

			अगर (type == MAX_TRAFFIC_TYPE)
				जारी;

			bnx2x_dcbx_get_ap_priority(bp,
						   entry[index].pri_biपंचांगap,
						   type);
		पूर्ण

		/* If we have received a non-zero शेष application
		 * priority, then use that क्रम applications which are
		 * not configured with any priority.
		 */
		अगर (ttp[LLFC_TRAFFIC_TYPE_NW] != 0) अणु
			अगर (!iscsi_pri_found) अणु
				ttp[LLFC_TRAFFIC_TYPE_ISCSI] =
					ttp[LLFC_TRAFFIC_TYPE_NW];
				DP(BNX2X_MSG_DCB,
				   "ISCSI is using default priority.\n");
			पूर्ण
			अगर (!fcoe_pri_found) अणु
				ttp[LLFC_TRAFFIC_TYPE_FCOE] =
					ttp[LLFC_TRAFFIC_TYPE_NW];
				DP(BNX2X_MSG_DCB,
				   "FCoE is using default priority.\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_APP_DISABLED\n");
		bp->dcbx_port_params.app.enabled = false;
		क्रम (index = 0 ; index < LLFC_DRIVER_TRAFFIC_TYPE_MAX; index++)
			ttp[index] = INVALID_TRAFFIC_TYPE_PRIORITY;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_dcbx_get_ets_feature(काष्ठा bnx2x *bp,
				       काष्ठा dcbx_ets_feature *ets,
				       u32 error) अणु
	पूर्णांक i = 0;
	u32 pg_pri_orginal_spपढ़ो[DCBX_MAX_NUM_PG_BW_ENTRIES] = अणु0पूर्ण;
	काष्ठा pg_help_data pg_help_data;
	काष्ठा bnx2x_dcbx_cos_params *cos_params =
			bp->dcbx_port_params.ets.cos_params;

	स_रखो(&pg_help_data, 0, माप(काष्ठा pg_help_data));

	अगर (GET_FLAGS(error, DCBX_LOCAL_ETS_ERROR))
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_ETS_ERROR\n");

	अगर (GET_FLAGS(error, DCBX_REMOTE_ETS_TLV_NOT_FOUND))
		DP(BNX2X_MSG_DCB, "DCBX_REMOTE_ETS_TLV_NOT_FOUND\n");

	/* Clean up old settings of ets on COS */
	क्रम (i = 0; i < ARRAY_SIZE(bp->dcbx_port_params.ets.cos_params) ; i++) अणु
		cos_params[i].छोड़ोable = false;
		cos_params[i].strict = BNX2X_DCBX_STRICT_INVALID;
		cos_params[i].bw_tbl = DCBX_INVALID_COS_BW;
		cos_params[i].pri_biपंचांगask = 0;
	पूर्ण

	अगर (bp->dcbx_port_params.app.enabled && ets->enabled &&
	   !GET_FLAGS(error,
		      DCBX_LOCAL_ETS_ERROR | DCBX_REMOTE_ETS_TLV_NOT_FOUND)) अणु
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_ETS_ENABLE\n");
		bp->dcbx_port_params.ets.enabled = true;

		bnx2x_dcbx_get_ets_pri_pg_tbl(bp,
					      pg_pri_orginal_spपढ़ो,
					      ets->pri_pg_tbl);

		bnx2x_dcbx_get_num_pg_traf_type(bp,
						pg_pri_orginal_spपढ़ो,
						&pg_help_data);

		bnx2x_dcbx_fill_cos_params(bp, &pg_help_data,
					   ets, pg_pri_orginal_spपढ़ो);

	पूर्ण अन्यथा अणु
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_ETS_DISABLED\n");
		bp->dcbx_port_params.ets.enabled = false;
		ets->pri_pg_tbl[0] = 0;

		क्रम (i = 0; i < DCBX_MAX_NUM_PRI_PG_ENTRIES ; i++)
			DCBX_PG_BW_SET(ets->pg_bw_tbl, i, 1);
	पूर्ण
पूर्ण

अटल व्योम  bnx2x_dcbx_get_pfc_feature(काष्ठा bnx2x *bp,
					काष्ठा dcbx_pfc_feature *pfc, u32 error)
अणु
	अगर (GET_FLAGS(error, DCBX_LOCAL_PFC_ERROR))
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_PFC_ERROR\n");

	अगर (GET_FLAGS(error, DCBX_REMOTE_PFC_TLV_NOT_FOUND))
		DP(BNX2X_MSG_DCB, "DCBX_REMOTE_PFC_TLV_NOT_FOUND\n");
	अगर (bp->dcbx_port_params.app.enabled && pfc->enabled &&
	   !GET_FLAGS(error, DCBX_LOCAL_PFC_ERROR | DCBX_LOCAL_PFC_MISMATCH |
			     DCBX_REMOTE_PFC_TLV_NOT_FOUND)) अणु
		bp->dcbx_port_params.pfc.enabled = true;
		bp->dcbx_port_params.pfc.priority_non_छोड़ोable_mask =
			~(pfc->pri_en_biपंचांगap);
	पूर्ण अन्यथा अणु
		DP(BNX2X_MSG_DCB, "DCBX_LOCAL_PFC_DISABLED\n");
		bp->dcbx_port_params.pfc.enabled = false;
		bp->dcbx_port_params.pfc.priority_non_छोड़ोable_mask = 0;
	पूर्ण
पूर्ण

/* maps unmapped priorities to to the same COS as L2 */
अटल व्योम bnx2x_dcbx_map_nw(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i;
	u32 unmapped = (1 << MAX_PFC_PRIORITIES) - 1; /* all ones */
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;
	u32 nw_prio = 1 << ttp[LLFC_TRAFFIC_TYPE_NW];
	काष्ठा bnx2x_dcbx_cos_params *cos_params =
			bp->dcbx_port_params.ets.cos_params;

	/* get unmapped priorities by clearing mapped bits */
	क्रम (i = 0; i < LLFC_DRIVER_TRAFFIC_TYPE_MAX; i++)
		unmapped &= ~(1 << ttp[i]);

	/* find cos क्रम nw prio and extend it with unmapped */
	क्रम (i = 0; i < ARRAY_SIZE(bp->dcbx_port_params.ets.cos_params); i++) अणु
		अगर (cos_params[i].pri_biपंचांगask & nw_prio) अणु
			/* extend the biपंचांगask with unmapped */
			DP(BNX2X_MSG_DCB,
			   "cos %d extended with 0x%08x\n", i, unmapped);
			cos_params[i].pri_biपंचांगask |= unmapped;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnx2x_get_dcbx_drv_param(काष्ठा bnx2x *bp,
				     काष्ठा dcbx_features *features,
				     u32 error)
अणु
	bnx2x_dcbx_get_ap_feature(bp, &features->app, error);

	bnx2x_dcbx_get_pfc_feature(bp, &features->pfc, error);

	bnx2x_dcbx_get_ets_feature(bp, &features->ets, error);

	bnx2x_dcbx_map_nw(bp);
पूर्ण

#घोषणा DCBX_LOCAL_MIB_MAX_TRY_READ		(100)
अटल पूर्णांक bnx2x_dcbx_पढ़ो_mib(काष्ठा bnx2x *bp,
			       u32 *base_mib_addr,
			       u32 offset,
			       पूर्णांक पढ़ो_mib_type)
अणु
	पूर्णांक max_try_पढ़ो = 0;
	u32 mib_size, prefix_seq_num, suffix_seq_num;
	काष्ठा lldp_remote_mib *remote_mib ;
	काष्ठा lldp_local_mib  *local_mib;

	चयन (पढ़ो_mib_type) अणु
	हाल DCBX_READ_LOCAL_MIB:
		mib_size = माप(काष्ठा lldp_local_mib);
		अवरोध;
	हाल DCBX_READ_REMOTE_MIB:
		mib_size = माप(काष्ठा lldp_remote_mib);
		अवरोध;
	शेष:
		वापस 1; /*error*/
	पूर्ण

	offset += BP_PORT(bp) * mib_size;

	करो अणु
		bnx2x_पढ़ो_data(bp, base_mib_addr, offset, mib_size);

		max_try_पढ़ो++;

		चयन (पढ़ो_mib_type) अणु
		हाल DCBX_READ_LOCAL_MIB:
			local_mib = (काष्ठा lldp_local_mib *) base_mib_addr;
			prefix_seq_num = local_mib->prefix_seq_num;
			suffix_seq_num = local_mib->suffix_seq_num;
			अवरोध;
		हाल DCBX_READ_REMOTE_MIB:
			remote_mib = (काष्ठा lldp_remote_mib *) base_mib_addr;
			prefix_seq_num = remote_mib->prefix_seq_num;
			suffix_seq_num = remote_mib->suffix_seq_num;
			अवरोध;
		शेष:
			वापस 1; /*error*/
		पूर्ण
	पूर्ण जबतक ((prefix_seq_num != suffix_seq_num) &&
	       (max_try_पढ़ो < DCBX_LOCAL_MIB_MAX_TRY_READ));

	अगर (max_try_पढ़ो >= DCBX_LOCAL_MIB_MAX_TRY_READ) अणु
		BNX2X_ERR("MIB could not be read\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2x_pfc_set_pfc(काष्ठा bnx2x *bp)
अणु
	पूर्णांक mfw_configured = SHMEM2_HAS(bp, drv_flags) &&
			     GET_FLAGS(SHMEM2_RD(bp, drv_flags),
				       1 << DRV_FLAGS_DCB_MFW_CONFIGURED);

	अगर (bp->dcbx_port_params.pfc.enabled &&
	    (!(bp->dcbx_error & DCBX_REMOTE_MIB_ERROR) || mfw_configured))
		/*
		 * 1. Fills up common PFC काष्ठाures अगर required
		 * 2. Configure NIG, MAC and BRB via the elink
		 */
		bnx2x_pfc_set(bp);
	अन्यथा
		bnx2x_pfc_clear(bp);
पूर्ण

पूर्णांक bnx2x_dcbx_stop_hw_tx(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	पूर्णांक rc;

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_TX_STOP;

	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	DP(BNX2X_MSG_DCB, "STOP TRAFFIC\n");

	rc = bnx2x_func_state_change(bp, &func_params);
	अगर (rc) अणु
		BNX2X_ERR("Unable to hold traffic for HW configuration\n");
		bnx2x_panic();
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक bnx2x_dcbx_resume_hw_tx(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_func_state_params func_params = अणुशून्यपूर्ण;
	काष्ठा bnx2x_func_tx_start_params *tx_params =
		&func_params.params.tx_start;
	पूर्णांक rc;

	func_params.f_obj = &bp->func_obj;
	func_params.cmd = BNX2X_F_CMD_TX_START;

	__set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);
	__set_bit(RAMROD_RETRY, &func_params.ramrod_flags);

	bnx2x_dcbx_fw_काष्ठा(bp, tx_params);

	DP(BNX2X_MSG_DCB, "START TRAFFIC\n");

	rc = bnx2x_func_state_change(bp, &func_params);
	अगर (rc) अणु
		BNX2X_ERR("Unable to resume traffic after HW configuration\n");
		bnx2x_panic();
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम bnx2x_dcbx_2cos_limit_update_ets_config(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_dcbx_pg_params *ets = &(bp->dcbx_port_params.ets);
	पूर्णांक rc = 0;

	अगर (ets->num_of_cos == 0 || ets->num_of_cos > DCBX_COS_MAX_NUM_E2) अणु
		BNX2X_ERR("Illegal number of COSes %d\n", ets->num_of_cos);
		वापस;
	पूर्ण

	/* valid COS entries */
	अगर (ets->num_of_cos == 1)   /* no ETS */
		वापस;

	/* sanity */
	अगर (((BNX2X_DCBX_STRICT_INVALID == ets->cos_params[0].strict) &&
	     (DCBX_INVALID_COS_BW == ets->cos_params[0].bw_tbl)) ||
	    ((BNX2X_DCBX_STRICT_INVALID == ets->cos_params[1].strict) &&
	     (DCBX_INVALID_COS_BW == ets->cos_params[1].bw_tbl))) अणु
		BNX2X_ERR("all COS should have at least bw_limit or strict"
			    "ets->cos_params[0].strict= %x"
			    "ets->cos_params[0].bw_tbl= %x"
			    "ets->cos_params[1].strict= %x"
			    "ets->cos_params[1].bw_tbl= %x",
			  ets->cos_params[0].strict,
			  ets->cos_params[0].bw_tbl,
			  ets->cos_params[1].strict,
			  ets->cos_params[1].bw_tbl);
		वापस;
	पूर्ण
	/* If we join a group and there is bw_tbl and strict then bw rules */
	अगर ((DCBX_INVALID_COS_BW != ets->cos_params[0].bw_tbl) &&
	    (DCBX_INVALID_COS_BW != ets->cos_params[1].bw_tbl)) अणु
		u32 bw_tbl_0 = ets->cos_params[0].bw_tbl;
		u32 bw_tbl_1 = ets->cos_params[1].bw_tbl;
		/* Do not allow 0-100 configuration
		 * since PBF करोes not support it
		 * क्रमce 1-99 instead
		 */
		अगर (bw_tbl_0 == 0) अणु
			bw_tbl_0 = 1;
			bw_tbl_1 = 99;
		पूर्ण अन्यथा अगर (bw_tbl_1 == 0) अणु
			bw_tbl_1 = 1;
			bw_tbl_0 = 99;
		पूर्ण

		bnx2x_ets_bw_limit(&bp->link_params, bw_tbl_0, bw_tbl_1);
	पूर्ण अन्यथा अणु
		अगर (ets->cos_params[0].strict == BNX2X_DCBX_STRICT_COS_HIGHEST)
			rc = bnx2x_ets_strict(&bp->link_params, 0);
		अन्यथा अगर (ets->cos_params[1].strict
					== BNX2X_DCBX_STRICT_COS_HIGHEST)
			rc = bnx2x_ets_strict(&bp->link_params, 1);
		अगर (rc)
			BNX2X_ERR("update_ets_params failed\n");
	पूर्ण
पूर्ण

/*
 * In E3B0 the configuration may have more than 2 COS.
 */
अटल व्योम bnx2x_dcbx_update_ets_config(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_dcbx_pg_params *ets = &(bp->dcbx_port_params.ets);
	काष्ठा bnx2x_ets_params ets_params = अणु 0 पूर्ण;
	u8 i;

	ets_params.num_of_cos = ets->num_of_cos;

	क्रम (i = 0; i < ets->num_of_cos; i++) अणु
		/* COS is SP */
		अगर (ets->cos_params[i].strict != BNX2X_DCBX_STRICT_INVALID) अणु
			अगर (ets->cos_params[i].bw_tbl != DCBX_INVALID_COS_BW) अणु
				BNX2X_ERR("COS can't be not BW and not SP\n");
				वापस;
			पूर्ण

			ets_params.cos[i].state = bnx2x_cos_state_strict;
			ets_params.cos[i].params.sp_params.pri =
						ets->cos_params[i].strict;
		पूर्ण अन्यथा अणु /* COS is BW */
			अगर (ets->cos_params[i].bw_tbl == DCBX_INVALID_COS_BW) अणु
				BNX2X_ERR("COS can't be not BW and not SP\n");
				वापस;
			पूर्ण
			ets_params.cos[i].state = bnx2x_cos_state_bw;
			ets_params.cos[i].params.bw_params.bw =
						(u8)ets->cos_params[i].bw_tbl;
		पूर्ण
	पूर्ण

	/* Configure the ETS in HW */
	अगर (bnx2x_ets_e3b0_config(&bp->link_params, &bp->link_vars,
				  &ets_params)) अणु
		BNX2X_ERR("bnx2x_ets_e3b0_config failed\n");
		bnx2x_ets_disabled(&bp->link_params, &bp->link_vars);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_dcbx_update_ets_params(काष्ठा bnx2x *bp)
अणु
	पूर्णांक mfw_configured = SHMEM2_HAS(bp, drv_flags) &&
			     GET_FLAGS(SHMEM2_RD(bp, drv_flags),
				       1 << DRV_FLAGS_DCB_MFW_CONFIGURED);

	bnx2x_ets_disabled(&bp->link_params, &bp->link_vars);

	अगर (!bp->dcbx_port_params.ets.enabled ||
	    ((bp->dcbx_error & DCBX_REMOTE_MIB_ERROR) && !mfw_configured))
		वापस;

	अगर (CHIP_IS_E3B0(bp))
		bnx2x_dcbx_update_ets_config(bp);
	अन्यथा
		bnx2x_dcbx_2cos_limit_update_ets_config(bp);
पूर्ण

#अगर_घोषित BCM_DCBNL
अटल पूर्णांक bnx2x_dcbx_पढ़ो_shmem_remote_mib(काष्ठा bnx2x *bp)
अणु
	काष्ठा lldp_remote_mib remote_mib = अणु0पूर्ण;
	u32 dcbx_remote_mib_offset = SHMEM2_RD(bp, dcbx_remote_mib_offset);
	पूर्णांक rc;

	DP(BNX2X_MSG_DCB, "dcbx_remote_mib_offset 0x%x\n",
	   dcbx_remote_mib_offset);

	अगर (SHMEM_DCBX_REMOTE_MIB_NONE == dcbx_remote_mib_offset) अणु
		BNX2X_ERR("FW doesn't support dcbx_remote_mib_offset\n");
		वापस -EINVAL;
	पूर्ण

	rc = bnx2x_dcbx_पढ़ो_mib(bp, (u32 *)&remote_mib, dcbx_remote_mib_offset,
				 DCBX_READ_REMOTE_MIB);

	अगर (rc) अणु
		BNX2X_ERR("Failed to read remote mib from FW\n");
		वापस rc;
	पूर्ण

	/* save features and flags */
	bp->dcbx_remote_feat = remote_mib.features;
	bp->dcbx_remote_flags = remote_mib.flags;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक bnx2x_dcbx_पढ़ो_shmem_neg_results(काष्ठा bnx2x *bp)
अणु
	काष्ठा lldp_local_mib local_mib = अणु0पूर्ण;
	u32 dcbx_neg_res_offset = SHMEM2_RD(bp, dcbx_neg_res_offset);
	पूर्णांक rc;

	DP(BNX2X_MSG_DCB, "dcbx_neg_res_offset 0x%x\n", dcbx_neg_res_offset);

	अगर (SHMEM_DCBX_NEG_RES_NONE == dcbx_neg_res_offset) अणु
		BNX2X_ERR("FW doesn't support dcbx_neg_res_offset\n");
		वापस -EINVAL;
	पूर्ण

	rc = bnx2x_dcbx_पढ़ो_mib(bp, (u32 *)&local_mib, dcbx_neg_res_offset,
				 DCBX_READ_LOCAL_MIB);

	अगर (rc) अणु
		BNX2X_ERR("Failed to read local mib from FW\n");
		वापस rc;
	पूर्ण

	/* save features and error */
	bp->dcbx_local_feat = local_mib.features;
	bp->dcbx_error = local_mib.error;
	वापस 0;
पूर्ण

#अगर_घोषित BCM_DCBNL
अटल अंतरभूत
u8 bnx2x_dcbx_dcbnl_app_up(काष्ठा dcbx_app_priority_entry *ent)
अणु
	u8 pri;

	/* Choose the highest priority */
	क्रम (pri = MAX_PFC_PRIORITIES - 1; pri > 0; pri--)
		अगर (ent->pri_biपंचांगap & (1 << pri))
			अवरोध;
	वापस pri;
पूर्ण

अटल अंतरभूत
u8 bnx2x_dcbx_dcbnl_app_idtype(काष्ठा dcbx_app_priority_entry *ent)
अणु
	वापस ((ent->appBitfield & DCBX_APP_ENTRY_SF_MASK) ==
		DCBX_APP_SF_PORT) ? DCB_APP_IDTYPE_PORTNUM :
		DCB_APP_IDTYPE_ETHTYPE;
पूर्ण

पूर्णांक bnx2x_dcbnl_update_applist(काष्ठा bnx2x *bp, bool delall)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < DCBX_MAX_APP_PROTOCOL && err == 0; i++) अणु
		काष्ठा dcbx_app_priority_entry *ent =
			&bp->dcbx_local_feat.app.app_pri_tbl[i];

		अगर (ent->appBitfield & DCBX_APP_ENTRY_VALID) अणु
			u8 up = bnx2x_dcbx_dcbnl_app_up(ent);

			/* aव्योम invalid user-priority */
			अगर (up) अणु
				काष्ठा dcb_app app;
				app.selector = bnx2x_dcbx_dcbnl_app_idtype(ent);
				app.protocol = ent->app_id;
				app.priority = delall ? 0 : up;
				err = dcb_setapp(bp->dev, &app);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम bnx2x_dcbx_update_tc_mapping(काष्ठा bnx2x *bp)
अणु
	u8 prio, cos;
	क्रम (cos = 0; cos < bp->dcbx_port_params.ets.num_of_cos; cos++) अणु
		क्रम (prio = 0; prio < BNX2X_MAX_PRIORITY; prio++) अणु
			अगर (bp->dcbx_port_params.ets.cos_params[cos].pri_biपंचांगask
			    & (1 << prio)) अणु
				bp->prio_to_cos[prio] = cos;
				DP(BNX2X_MSG_DCB,
				   "tx_mapping %d --> %d\n", prio, cos);
			पूर्ण
		पूर्ण
	पूर्ण

	/* setup tc must be called under rtnl lock, but we can't take it here
	 * as we are handling an attention on a work queue which must be
	 * flushed at some rtnl-locked contexts (e.g. अगर करोwn)
	 */
	bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_SETUP_TC, 0);
पूर्ण

व्योम bnx2x_dcbx_set_params(काष्ठा bnx2x *bp, u32 state)
अणु
	चयन (state) अणु
	हाल BNX2X_DCBX_STATE_NEG_RECEIVED:
		अणु
			DP(BNX2X_MSG_DCB, "BNX2X_DCBX_STATE_NEG_RECEIVED\n");
#अगर_घोषित BCM_DCBNL
			/**
			 * Delete app tlvs from dcbnl beक्रमe पढ़ोing new
			 * negotiation results
			 */
			bnx2x_dcbnl_update_applist(bp, true);

			/* Read remote mib अगर dcbx is in the FW */
			अगर (bnx2x_dcbx_पढ़ो_shmem_remote_mib(bp))
				वापस;
#पूर्ण_अगर
			/* Read neg results अगर dcbx is in the FW */
			अगर (bnx2x_dcbx_पढ़ो_shmem_neg_results(bp))
				वापस;

			bnx2x_dump_dcbx_drv_param(bp, &bp->dcbx_local_feat,
						  bp->dcbx_error);

			bnx2x_get_dcbx_drv_param(bp, &bp->dcbx_local_feat,
						 bp->dcbx_error);

			/* mark DCBX result क्रम PMF migration */
			bnx2x_update_drv_flags(bp,
					       1 << DRV_FLAGS_DCB_CONFIGURED,
					       1);
#अगर_घोषित BCM_DCBNL
			/*
			 * Add new app tlvs to dcbnl
			 */
			bnx2x_dcbnl_update_applist(bp, false);
#पूर्ण_अगर
			/*
			 * reconfigure the netdevice with the results of the new
			 * dcbx negotiation.
			 */
			bnx2x_dcbx_update_tc_mapping(bp);

			/*
			 * allow other functions to update their netdevices
			 * accordingly
			 */
			अगर (IS_MF(bp))
				bnx2x_link_sync_notअगरy(bp);

			bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_TX_STOP, 0);
			वापस;
		पूर्ण
	हाल BNX2X_DCBX_STATE_TX_PAUSED:
		DP(BNX2X_MSG_DCB, "BNX2X_DCBX_STATE_TX_PAUSED\n");
		bnx2x_pfc_set_pfc(bp);

		bnx2x_dcbx_update_ets_params(bp);

		/* ets may affect cmng configuration: reinit it in hw */
		bnx2x_set_local_cmng(bp);
		वापस;
	हाल BNX2X_DCBX_STATE_TX_RELEASED:
		DP(BNX2X_MSG_DCB, "BNX2X_DCBX_STATE_TX_RELEASED\n");
		bnx2x_fw_command(bp, DRV_MSG_CODE_DCBX_PMF_DRV_OK, 0);
#अगर_घोषित BCM_DCBNL
		/*
		 * Send a notअगरication क्रम the new negotiated parameters
		 */
		dcbnl_cee_notअगरy(bp->dev, RTM_GETDCB, DCB_CMD_CEE_GET, 0, 0);
#पूर्ण_अगर
		वापस;
	शेष:
		BNX2X_ERR("Unknown DCBX_STATE\n");
	पूर्ण
पूर्ण

#घोषणा LLDP_ADMIN_MIB_OFFSET(bp)	(PORT_MAX*माप(काष्ठा lldp_params) + \
				      BP_PORT(bp)*माप(काष्ठा lldp_admin_mib))

अटल व्योम bnx2x_dcbx_admin_mib_updated_params(काष्ठा bnx2x *bp,
				u32 dcbx_lldp_params_offset)
अणु
	काष्ठा lldp_admin_mib admin_mib;
	u32 i, other_traf_type = PREDEFINED_APP_IDX_MAX, traf_type = 0;
	u32 offset = dcbx_lldp_params_offset + LLDP_ADMIN_MIB_OFFSET(bp);

	/*लघुcuts*/
	काष्ठा dcbx_features *af = &admin_mib.features;
	काष्ठा bnx2x_config_dcbx_params *dp = &bp->dcbx_config_params;

	स_रखो(&admin_mib, 0, माप(काष्ठा lldp_admin_mib));

	/* Read the data first */
	bnx2x_पढ़ो_data(bp, (u32 *)&admin_mib, offset,
			माप(काष्ठा lldp_admin_mib));

	अगर (bp->dcbx_enabled == BNX2X_DCBX_ENABLED_ON_NEG_ON)
		SET_FLAGS(admin_mib.ver_cfg_flags, DCBX_DCBX_ENABLED);
	अन्यथा
		RESET_FLAGS(admin_mib.ver_cfg_flags, DCBX_DCBX_ENABLED);

	अगर (dp->overग_लिखो_settings == BNX2X_DCBX_OVERWRITE_SETTINGS_ENABLE) अणु

		RESET_FLAGS(admin_mib.ver_cfg_flags, DCBX_CEE_VERSION_MASK);
		admin_mib.ver_cfg_flags |=
			(dp->admin_dcbx_version << DCBX_CEE_VERSION_SHIFT) &
			 DCBX_CEE_VERSION_MASK;

		af->ets.enabled = (u8)dp->admin_ets_enable;

		af->pfc.enabled = (u8)dp->admin_pfc_enable;

		/* FOR IEEE dp->admin_tc_supported_tx_enable */
		अगर (dp->admin_ets_configuration_tx_enable)
			SET_FLAGS(admin_mib.ver_cfg_flags,
				  DCBX_ETS_CONFIG_TX_ENABLED);
		अन्यथा
			RESET_FLAGS(admin_mib.ver_cfg_flags,
				    DCBX_ETS_CONFIG_TX_ENABLED);
		/* For IEEE admin_ets_recommendation_tx_enable */
		अगर (dp->admin_pfc_tx_enable)
			SET_FLAGS(admin_mib.ver_cfg_flags,
				  DCBX_PFC_CONFIG_TX_ENABLED);
		अन्यथा
			RESET_FLAGS(admin_mib.ver_cfg_flags,
				  DCBX_PFC_CONFIG_TX_ENABLED);

		अगर (dp->admin_application_priority_tx_enable)
			SET_FLAGS(admin_mib.ver_cfg_flags,
				  DCBX_APP_CONFIG_TX_ENABLED);
		अन्यथा
			RESET_FLAGS(admin_mib.ver_cfg_flags,
				  DCBX_APP_CONFIG_TX_ENABLED);

		अगर (dp->admin_ets_willing)
			SET_FLAGS(admin_mib.ver_cfg_flags, DCBX_ETS_WILLING);
		अन्यथा
			RESET_FLAGS(admin_mib.ver_cfg_flags, DCBX_ETS_WILLING);
		/* For IEEE admin_ets_reco_valid */
		अगर (dp->admin_pfc_willing)
			SET_FLAGS(admin_mib.ver_cfg_flags, DCBX_PFC_WILLING);
		अन्यथा
			RESET_FLAGS(admin_mib.ver_cfg_flags, DCBX_PFC_WILLING);

		अगर (dp->admin_app_priority_willing)
			SET_FLAGS(admin_mib.ver_cfg_flags, DCBX_APP_WILLING);
		अन्यथा
			RESET_FLAGS(admin_mib.ver_cfg_flags, DCBX_APP_WILLING);

		क्रम (i = 0 ; i < DCBX_MAX_NUM_PG_BW_ENTRIES; i++) अणु
			DCBX_PG_BW_SET(af->ets.pg_bw_tbl, i,
				(u8)dp->admin_configuration_bw_precentage[i]);

			DP(BNX2X_MSG_DCB, "pg_bw_tbl[%d] = %02x\n",
			   i, DCBX_PG_BW_GET(af->ets.pg_bw_tbl, i));
		पूर्ण

		क्रम (i = 0; i < DCBX_MAX_NUM_PRI_PG_ENTRIES; i++) अणु
			DCBX_PRI_PG_SET(af->ets.pri_pg_tbl, i,
					(u8)dp->admin_configuration_ets_pg[i]);

			DP(BNX2X_MSG_DCB, "pri_pg_tbl[%d] = %02x\n",
			   i, DCBX_PRI_PG_GET(af->ets.pri_pg_tbl, i));
		पूर्ण

		/*For IEEE admin_recommendation_bw_percentage
		 *For IEEE admin_recommendation_ets_pg */
		af->pfc.pri_en_biपंचांगap = (u8)dp->admin_pfc_biपंचांगap;
		क्रम (i = 0; i < DCBX_CONFIG_MAX_APP_PROTOCOL; i++) अणु
			अगर (dp->admin_priority_app_table[i].valid) अणु
				काष्ठा bnx2x_admin_priority_app_table *table =
					dp->admin_priority_app_table;
				अगर ((ETH_TYPE_FCOE == table[i].app_id) &&
				   (TRAFFIC_TYPE_ETH == table[i].traffic_type))
					traf_type = FCOE_APP_IDX;
				अन्यथा अगर ((TCP_PORT_ISCSI == table[i].app_id) &&
				   (TRAFFIC_TYPE_PORT == table[i].traffic_type))
					traf_type = ISCSI_APP_IDX;
				अन्यथा
					traf_type = other_traf_type++;

				af->app.app_pri_tbl[traf_type].app_id =
					table[i].app_id;

				af->app.app_pri_tbl[traf_type].pri_biपंचांगap =
					(u8)(1 << table[i].priority);

				af->app.app_pri_tbl[traf_type].appBitfield =
				    (DCBX_APP_ENTRY_VALID);

				af->app.app_pri_tbl[traf_type].appBitfield |=
				   (TRAFFIC_TYPE_ETH == table[i].traffic_type) ?
					DCBX_APP_SF_ETH_TYPE : DCBX_APP_SF_PORT;
			पूर्ण
		पूर्ण

		af->app.शेष_pri = (u8)dp->admin_शेष_priority;
	पूर्ण

	/* Write the data. */
	bnx2x_ग_लिखो_data(bp, (u32 *)&admin_mib, offset,
			 माप(काष्ठा lldp_admin_mib));
पूर्ण

व्योम bnx2x_dcbx_set_state(काष्ठा bnx2x *bp, bool dcb_on, u32 dcbx_enabled)
अणु
	अगर (!CHIP_IS_E1x(bp)) अणु
		bp->dcb_state = dcb_on;
		bp->dcbx_enabled = dcbx_enabled;
	पूर्ण अन्यथा अणु
		bp->dcb_state = false;
		bp->dcbx_enabled = BNX2X_DCBX_ENABLED_INVALID;
	पूर्ण
	DP(BNX2X_MSG_DCB, "DCB state [%s:%s]\n",
	   dcb_on ? "ON" : "OFF",
	   dcbx_enabled == BNX2X_DCBX_ENABLED_OFF ? "user-mode" :
	   dcbx_enabled == BNX2X_DCBX_ENABLED_ON_NEG_OFF ? "on-chip static" :
	   dcbx_enabled == BNX2X_DCBX_ENABLED_ON_NEG_ON ?
	   "on-chip with negotiation" : "invalid");
पूर्ण

व्योम bnx2x_dcbx_init_params(काष्ठा bnx2x *bp)
अणु
	bp->dcbx_config_params.admin_dcbx_version = 0x0; /* 0 - CEE; 1 - IEEE */
	bp->dcbx_config_params.admin_ets_willing = 1;
	bp->dcbx_config_params.admin_pfc_willing = 1;
	bp->dcbx_config_params.overग_लिखो_settings = 1;
	bp->dcbx_config_params.admin_ets_enable = 1;
	bp->dcbx_config_params.admin_pfc_enable = 1;
	bp->dcbx_config_params.admin_tc_supported_tx_enable = 1;
	bp->dcbx_config_params.admin_ets_configuration_tx_enable = 1;
	bp->dcbx_config_params.admin_pfc_tx_enable = 1;
	bp->dcbx_config_params.admin_application_priority_tx_enable = 1;
	bp->dcbx_config_params.admin_ets_reco_valid = 1;
	bp->dcbx_config_params.admin_app_priority_willing = 1;
	bp->dcbx_config_params.admin_configuration_bw_precentage[0] = 100;
	bp->dcbx_config_params.admin_configuration_bw_precentage[1] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[2] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[3] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[4] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[5] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[6] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[7] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[0] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[1] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[2] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[3] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[4] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[5] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[6] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[7] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[0] = 100;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[1] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[2] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[3] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[4] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[5] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[6] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[7] = 0;
	bp->dcbx_config_params.admin_recommendation_ets_pg[0] = 0;
	bp->dcbx_config_params.admin_recommendation_ets_pg[1] = 1;
	bp->dcbx_config_params.admin_recommendation_ets_pg[2] = 2;
	bp->dcbx_config_params.admin_recommendation_ets_pg[3] = 3;
	bp->dcbx_config_params.admin_recommendation_ets_pg[4] = 4;
	bp->dcbx_config_params.admin_recommendation_ets_pg[5] = 5;
	bp->dcbx_config_params.admin_recommendation_ets_pg[6] = 6;
	bp->dcbx_config_params.admin_recommendation_ets_pg[7] = 7;
	bp->dcbx_config_params.admin_pfc_biपंचांगap = 0x0;
	bp->dcbx_config_params.admin_priority_app_table[0].valid = 0;
	bp->dcbx_config_params.admin_priority_app_table[1].valid = 0;
	bp->dcbx_config_params.admin_priority_app_table[2].valid = 0;
	bp->dcbx_config_params.admin_priority_app_table[3].valid = 0;
	bp->dcbx_config_params.admin_शेष_priority = 0;
पूर्ण

व्योम bnx2x_dcbx_init(काष्ठा bnx2x *bp, bool update_shmem)
अणु
	u32 dcbx_lldp_params_offset = SHMEM_LLDP_DCBX_PARAMS_NONE;

	/* only PMF can send ADMIN msg to MFW in old MFW versions */
	अगर ((!bp->port.pmf) && (!(bp->flags & BC_SUPPORTS_DCBX_MSG_NON_PMF)))
		वापस;

	अगर (bp->dcbx_enabled <= 0)
		वापस;

	/* validate:
	 * chip of good क्रम dcbx version,
	 * dcb is wanted
	 * shmem2 contains DCBX support fields
	 */
	DP(BNX2X_MSG_DCB, "dcb_state %d bp->port.pmf %d\n",
	   bp->dcb_state, bp->port.pmf);

	अगर (bp->dcb_state == BNX2X_DCB_STATE_ON &&
	    SHMEM2_HAS(bp, dcbx_lldp_params_offset)) अणु
		dcbx_lldp_params_offset =
			SHMEM2_RD(bp, dcbx_lldp_params_offset);

		DP(BNX2X_MSG_DCB, "dcbx_lldp_params_offset 0x%x\n",
		   dcbx_lldp_params_offset);

		bnx2x_update_drv_flags(bp, 1 << DRV_FLAGS_DCB_CONFIGURED, 0);

		अगर (SHMEM_LLDP_DCBX_PARAMS_NONE != dcbx_lldp_params_offset) अणु
			/* need HW lock to aव्योम scenario of two drivers
			 * writing in parallel to shmem
			 */
			bnx2x_acquire_hw_lock(bp,
					      HW_LOCK_RESOURCE_DCBX_ADMIN_MIB);
			अगर (update_shmem)
				bnx2x_dcbx_admin_mib_updated_params(bp,
					dcbx_lldp_params_offset);

			/* Let HW start negotiation */
			bnx2x_fw_command(bp,
					 DRV_MSG_CODE_DCBX_ADMIN_PMF_MSG, 0);
			/* release HW lock only after MFW acks that it finished
			 * पढ़ोing values from shmem
			 */
			bnx2x_release_hw_lock(bp,
					      HW_LOCK_RESOURCE_DCBX_ADMIN_MIB);
		पूर्ण
	पूर्ण
पूर्ण
अटल व्योम
bnx2x_dcbx_prपूर्णांक_cos_params(काष्ठा bnx2x *bp,
			    काष्ठा bnx2x_func_tx_start_params *pfc_fw_cfg)
अणु
	u8 pri = 0;
	u8 cos = 0;

	DP(BNX2X_MSG_DCB,
	   "pfc_fw_cfg->dcb_version %x\n", pfc_fw_cfg->dcb_version);
	DP(BNX2X_MSG_DCB,
	   "pdev->params.dcbx_port_params.pfc.priority_non_pauseable_mask %x\n",
	   bp->dcbx_port_params.pfc.priority_non_छोड़ोable_mask);

	क्रम (cos = 0 ; cos < bp->dcbx_port_params.ets.num_of_cos ; cos++) अणु
		DP(BNX2X_MSG_DCB,
		   "pdev->params.dcbx_port_params.ets.cos_params[%d].pri_bitmask %x\n",
		   cos, bp->dcbx_port_params.ets.cos_params[cos].pri_biपंचांगask);

		DP(BNX2X_MSG_DCB,
		   "pdev->params.dcbx_port_params.ets.cos_params[%d].bw_tbl %x\n",
		   cos, bp->dcbx_port_params.ets.cos_params[cos].bw_tbl);

		DP(BNX2X_MSG_DCB,
		   "pdev->params.dcbx_port_params.ets.cos_params[%d].strict %x\n",
		   cos, bp->dcbx_port_params.ets.cos_params[cos].strict);

		DP(BNX2X_MSG_DCB,
		   "pdev->params.dcbx_port_params.ets.cos_params[%d].pauseable %x\n",
		   cos, bp->dcbx_port_params.ets.cos_params[cos].छोड़ोable);
	पूर्ण

	क्रम (pri = 0; pri < LLFC_DRIVER_TRAFFIC_TYPE_MAX; pri++) अणु
		DP(BNX2X_MSG_DCB,
		   "pfc_fw_cfg->traffic_type_to_priority_cos[%d].priority %x\n",
		   pri, pfc_fw_cfg->traffic_type_to_priority_cos[pri].priority);

		DP(BNX2X_MSG_DCB,
		   "pfc_fw_cfg->traffic_type_to_priority_cos[%d].cos %x\n",
		   pri, pfc_fw_cfg->traffic_type_to_priority_cos[pri].cos);
	पूर्ण
पूर्ण

/* fills help_data according to pg_info */
अटल व्योम bnx2x_dcbx_get_num_pg_traf_type(काष्ठा bnx2x *bp,
					    u32 *pg_pri_orginal_spपढ़ो,
					    काष्ठा pg_help_data *help_data)
अणु
	bool pg_found  = false;
	u32 i, traf_type, add_traf_type, add_pg;
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;
	काष्ठा pg_entry_help_data *data = help_data->data; /*लघुcut*/

	/* Set to invalid */
	क्रम (i = 0; i < LLFC_DRIVER_TRAFFIC_TYPE_MAX; i++)
		data[i].pg = DCBX_ILLEGAL_PG;

	क्रम (add_traf_type = 0;
	     add_traf_type < LLFC_DRIVER_TRAFFIC_TYPE_MAX; add_traf_type++) अणु
		pg_found = false;
		अगर (ttp[add_traf_type] < MAX_PFC_PRIORITIES) अणु
			add_pg = (u8)pg_pri_orginal_spपढ़ो[ttp[add_traf_type]];
			क्रम (traf_type = 0;
			     traf_type < LLFC_DRIVER_TRAFFIC_TYPE_MAX;
			     traf_type++) अणु
				अगर (data[traf_type].pg == add_pg) अणु
					अगर (!(data[traf_type].pg_priority &
					     (1 << ttp[add_traf_type])))
						data[traf_type].
							num_of_dअगर_pri++;
					data[traf_type].pg_priority |=
						(1 << ttp[add_traf_type]);
					pg_found = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!pg_found) अणु
				data[help_data->num_of_pg].pg = add_pg;
				data[help_data->num_of_pg].pg_priority =
						(1 << ttp[add_traf_type]);
				data[help_data->num_of_pg].num_of_dअगर_pri = 1;
				help_data->num_of_pg++;
			पूर्ण
		पूर्ण
		DP(BNX2X_MSG_DCB,
		   "add_traf_type %d pg_found %s num_of_pg %d\n",
		   add_traf_type, !pg_found ? "NO" : "YES",
		   help_data->num_of_pg);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_dcbx_ets_disabled_entry_data(काष्ठा bnx2x *bp,
					       काष्ठा cos_help_data *cos_data,
					       u32 pri_join_mask)
अणु
	/* Only one priority than only one COS */
	cos_data->data[0].pausable =
		IS_DCBX_PFC_PRI_ONLY_PAUSE(bp, pri_join_mask);
	cos_data->data[0].pri_join_mask = pri_join_mask;
	cos_data->data[0].cos_bw = 100;
	cos_data->num_of_cos = 1;
पूर्ण

अटल अंतरभूत व्योम bnx2x_dcbx_add_to_cos_bw(काष्ठा bnx2x *bp,
					    काष्ठा cos_entry_help_data *data,
					    u8 pg_bw)
अणु
	अगर (data->cos_bw == DCBX_INVALID_COS_BW)
		data->cos_bw = pg_bw;
	अन्यथा
		data->cos_bw += pg_bw;
पूर्ण

अटल व्योम bnx2x_dcbx_separate_छोड़ोable_from_non(काष्ठा bnx2x *bp,
			काष्ठा cos_help_data *cos_data,
			u32 *pg_pri_orginal_spपढ़ो,
			काष्ठा dcbx_ets_feature *ets)
अणु
	u32	pri_tested	= 0;
	u8	i		= 0;
	u8	entry		= 0;
	u8	pg_entry	= 0;
	u8	num_of_pri	= LLFC_DRIVER_TRAFFIC_TYPE_MAX;

	cos_data->data[0].pausable = true;
	cos_data->data[1].pausable = false;
	cos_data->data[0].pri_join_mask = cos_data->data[1].pri_join_mask = 0;

	क्रम (i = 0 ; i < num_of_pri ; i++) अणु
		pri_tested = 1 << bp->dcbx_port_params.
					app.traffic_type_priority[i];

		अगर (pri_tested & DCBX_PFC_PRI_NON_PAUSE_MASK(bp)) अणु
			cos_data->data[1].pri_join_mask |= pri_tested;
			entry = 1;
		पूर्ण अन्यथा अणु
			cos_data->data[0].pri_join_mask |= pri_tested;
			entry = 0;
		पूर्ण
		pg_entry = (u8)pg_pri_orginal_spपढ़ो[bp->dcbx_port_params.
						app.traffic_type_priority[i]];
		/* There can be only one strict pg */
		अगर (pg_entry < DCBX_MAX_NUM_PG_BW_ENTRIES)
			bnx2x_dcbx_add_to_cos_bw(bp, &cos_data->data[entry],
				DCBX_PG_BW_GET(ets->pg_bw_tbl, pg_entry));
		अन्यथा
			/* If we join a group and one is strict
			 * than the bw rules
			 */
			cos_data->data[entry].strict =
						BNX2X_DCBX_STRICT_COS_HIGHEST;
	पूर्ण
	अगर ((0 == cos_data->data[0].pri_join_mask) &&
	    (0 == cos_data->data[1].pri_join_mask))
		BNX2X_ERR("dcbx error: Both groups must have priorities\n");
पूर्ण

#अगर_अघोषित POWER_OF_2
#घोषणा POWER_OF_2(x)	((0 != x) && (0 == (x & (x-1))))
#पूर्ण_अगर

अटल व्योम bnx2x_dcbx_2cos_limit_cee_single_pg_to_cos_params(काष्ठा bnx2x *bp,
					      काष्ठा pg_help_data *pg_help_data,
					      काष्ठा cos_help_data *cos_data,
					      u32 pri_join_mask,
					      u8 num_of_dअगर_pri)
अणु
	u8 i = 0;
	u32 pri_tested = 0;
	u32 pri_mask_without_pri = 0;
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;
	/*debug*/
	अगर (num_of_dअगर_pri == 1) अणु
		bnx2x_dcbx_ets_disabled_entry_data(bp, cos_data, pri_join_mask);
		वापस;
	पूर्ण
	/* single priority group */
	अगर (pg_help_data->data[0].pg < DCBX_MAX_NUM_PG_BW_ENTRIES) अणु
		/* If there are both छोड़ोable and non-छोड़ोable priorities,
		 * the छोड़ोable priorities go to the first queue and
		 * the non-छोड़ोable priorities go to the second queue.
		 */
		अगर (IS_DCBX_PFC_PRI_MIX_PAUSE(bp, pri_join_mask)) अणु
			/* Pauseable */
			cos_data->data[0].pausable = true;
			/* Non छोड़ोable.*/
			cos_data->data[1].pausable = false;

			अगर (2 == num_of_dअगर_pri) अणु
				cos_data->data[0].cos_bw = 50;
				cos_data->data[1].cos_bw = 50;
			पूर्ण

			अगर (3 == num_of_dअगर_pri) अणु
				अगर (POWER_OF_2(DCBX_PFC_PRI_GET_PAUSE(bp,
							pri_join_mask))) अणु
					cos_data->data[0].cos_bw = 33;
					cos_data->data[1].cos_bw = 67;
				पूर्ण अन्यथा अणु
					cos_data->data[0].cos_bw = 67;
					cos_data->data[1].cos_bw = 33;
				पूर्ण
			पूर्ण

		पूर्ण अन्यथा अगर (IS_DCBX_PFC_PRI_ONLY_PAUSE(bp, pri_join_mask)) अणु
			/* If there are only छोड़ोable priorities,
			 * then one/two priorities go to the first queue
			 * and one priority goes to the second queue.
			 */
			अगर (2 == num_of_dअगर_pri) अणु
				cos_data->data[0].cos_bw = 50;
				cos_data->data[1].cos_bw = 50;
			पूर्ण अन्यथा अणु
				cos_data->data[0].cos_bw = 67;
				cos_data->data[1].cos_bw = 33;
			पूर्ण
			cos_data->data[1].pausable = true;
			cos_data->data[0].pausable = true;
			/* All priorities except FCOE */
			cos_data->data[0].pri_join_mask = (pri_join_mask &
				((u8)~(1 << ttp[LLFC_TRAFFIC_TYPE_FCOE])));
			/* Only FCOE priority.*/
			cos_data->data[1].pri_join_mask =
				(1 << ttp[LLFC_TRAFFIC_TYPE_FCOE]);
		पूर्ण अन्यथा
			/* If there are only non-छोड़ोable priorities,
			 * they will all go to the same queue.
			 */
			bnx2x_dcbx_ets_disabled_entry_data(bp,
						cos_data, pri_join_mask);
	पूर्ण अन्यथा अणु
		/* priority group which is not BW limited (PG#15):*/
		अगर (IS_DCBX_PFC_PRI_MIX_PAUSE(bp, pri_join_mask)) अणु
			/* If there are both छोड़ोable and non-छोड़ोable
			 * priorities, the छोड़ोable priorities go to the first
			 * queue and the non-छोड़ोable priorities
			 * go to the second queue.
			 */
			अगर (DCBX_PFC_PRI_GET_PAUSE(bp, pri_join_mask) >
			    DCBX_PFC_PRI_GET_NON_PAUSE(bp, pri_join_mask)) अणु
				cos_data->data[0].strict =
					BNX2X_DCBX_STRICT_COS_HIGHEST;
				cos_data->data[1].strict =
					BNX2X_DCBX_STRICT_COS_NEXT_LOWER_PRI(
						BNX2X_DCBX_STRICT_COS_HIGHEST);
			पूर्ण अन्यथा अणु
				cos_data->data[0].strict =
					BNX2X_DCBX_STRICT_COS_NEXT_LOWER_PRI(
						BNX2X_DCBX_STRICT_COS_HIGHEST);
				cos_data->data[1].strict =
					BNX2X_DCBX_STRICT_COS_HIGHEST;
			पूर्ण
			/* Pauseable */
			cos_data->data[0].pausable = true;
			/* Non छोड़ो-able.*/
			cos_data->data[1].pausable = false;
		पूर्ण अन्यथा अणु
			/* If there are only छोड़ोable priorities or
			 * only non-छोड़ोable,* the lower priorities go
			 * to the first queue and the higher priorities go
			 * to the second queue.
			 */
			cos_data->data[0].pausable =
				cos_data->data[1].pausable =
				IS_DCBX_PFC_PRI_ONLY_PAUSE(bp, pri_join_mask);

			क्रम (i = 0 ; i < LLFC_DRIVER_TRAFFIC_TYPE_MAX; i++) अणु
				pri_tested = 1 << bp->dcbx_port_params.
					app.traffic_type_priority[i];
				/* Remove priority tested */
				pri_mask_without_pri =
					(pri_join_mask & ((u8)(~pri_tested)));
				अगर (pri_mask_without_pri < pri_tested)
					अवरोध;
			पूर्ण

			अगर (i == LLFC_DRIVER_TRAFFIC_TYPE_MAX)
				BNX2X_ERR("Invalid value for pri_join_mask - could not find a priority\n");

			cos_data->data[0].pri_join_mask = pri_mask_without_pri;
			cos_data->data[1].pri_join_mask = pri_tested;
			/* Both queues are strict priority,
			 * and that with the highest priority
			 * माला_लो the highest strict priority in the arbiter.
			 */
			cos_data->data[0].strict =
					BNX2X_DCBX_STRICT_COS_NEXT_LOWER_PRI(
						BNX2X_DCBX_STRICT_COS_HIGHEST);
			cos_data->data[1].strict =
					BNX2X_DCBX_STRICT_COS_HIGHEST;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnx2x_dcbx_2cos_limit_cee_two_pg_to_cos_params(
			    काष्ठा bnx2x		*bp,
			    काष्ठा  pg_help_data	*pg_help_data,
			    काष्ठा dcbx_ets_feature	*ets,
			    काष्ठा cos_help_data	*cos_data,
			    u32			*pg_pri_orginal_spपढ़ो,
			    u32				pri_join_mask,
			    u8				num_of_dअगर_pri)
अणु
	u8 i = 0;
	u8 pg[DCBX_COS_MAX_NUM_E2] = अणु 0 पूर्ण;

	/* If there are both छोड़ोable and non-छोड़ोable priorities,
	 * the छोड़ोable priorities go to the first queue and
	 * the non-छोड़ोable priorities go to the second queue.
	 */
	अगर (IS_DCBX_PFC_PRI_MIX_PAUSE(bp, pri_join_mask)) अणु
		अगर (IS_DCBX_PFC_PRI_MIX_PAUSE(bp,
					 pg_help_data->data[0].pg_priority) ||
		    IS_DCBX_PFC_PRI_MIX_PAUSE(bp,
					 pg_help_data->data[1].pg_priority)) अणु
			/* If one PG contains both छोड़ोable and
			 * non-छोड़ोable priorities then ETS is disabled.
			 */
			bnx2x_dcbx_separate_छोड़ोable_from_non(bp, cos_data,
					pg_pri_orginal_spपढ़ो, ets);
			bp->dcbx_port_params.ets.enabled = false;
			वापस;
		पूर्ण

		/* Pauseable */
		cos_data->data[0].pausable = true;
		/* Non छोड़ोable. */
		cos_data->data[1].pausable = false;
		अगर (IS_DCBX_PFC_PRI_ONLY_PAUSE(bp,
				pg_help_data->data[0].pg_priority)) अणु
			/* 0 is छोड़ोable */
			cos_data->data[0].pri_join_mask =
				pg_help_data->data[0].pg_priority;
			pg[0] = pg_help_data->data[0].pg;
			cos_data->data[1].pri_join_mask =
				pg_help_data->data[1].pg_priority;
			pg[1] = pg_help_data->data[1].pg;
		पूर्ण अन्यथा अणु/* 1 is छोड़ोable */
			cos_data->data[0].pri_join_mask =
				pg_help_data->data[1].pg_priority;
			pg[0] = pg_help_data->data[1].pg;
			cos_data->data[1].pri_join_mask =
				pg_help_data->data[0].pg_priority;
			pg[1] = pg_help_data->data[0].pg;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If there are only छोड़ोable priorities or
		 * only non-छोड़ोable, each PG goes to a queue.
		 */
		cos_data->data[0].pausable = cos_data->data[1].pausable =
			IS_DCBX_PFC_PRI_ONLY_PAUSE(bp, pri_join_mask);
		cos_data->data[0].pri_join_mask =
			pg_help_data->data[0].pg_priority;
		pg[0] = pg_help_data->data[0].pg;
		cos_data->data[1].pri_join_mask =
			pg_help_data->data[1].pg_priority;
		pg[1] = pg_help_data->data[1].pg;
	पूर्ण

	/* There can be only one strict pg */
	क्रम (i = 0 ; i < ARRAY_SIZE(pg); i++) अणु
		अगर (pg[i] < DCBX_MAX_NUM_PG_BW_ENTRIES)
			cos_data->data[i].cos_bw =
				DCBX_PG_BW_GET(ets->pg_bw_tbl, pg[i]);
		अन्यथा
			cos_data->data[i].strict =
						BNX2X_DCBX_STRICT_COS_HIGHEST;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_dcbx_join_pgs(
			      काष्ठा bnx2x            *bp,
			      काष्ठा dcbx_ets_feature *ets,
			      काष्ठा pg_help_data     *pg_help_data,
			      u8                      required_num_of_pg)
अणु
	u8 entry_joined    = pg_help_data->num_of_pg - 1;
	u8 entry_हटाओd   = entry_joined + 1;
	u8 pg_joined       = 0;

	अगर (required_num_of_pg == 0 || ARRAY_SIZE(pg_help_data->data)
						<= pg_help_data->num_of_pg) अणु

		BNX2X_ERR("required_num_of_pg can't be zero\n");
		वापस -EINVAL;
	पूर्ण

	जबतक (required_num_of_pg < pg_help_data->num_of_pg) अणु
		entry_joined = pg_help_data->num_of_pg - 2;
		entry_हटाओd = entry_joined + 1;
		/* protect index */
		entry_हटाओd %= ARRAY_SIZE(pg_help_data->data);

		pg_help_data->data[entry_joined].pg_priority |=
			pg_help_data->data[entry_हटाओd].pg_priority;

		pg_help_data->data[entry_joined].num_of_dअगर_pri +=
			pg_help_data->data[entry_हटाओd].num_of_dअगर_pri;

		अगर (pg_help_data->data[entry_joined].pg == DCBX_STRICT_PRI_PG ||
		    pg_help_data->data[entry_हटाओd].pg == DCBX_STRICT_PRI_PG)
			/* Entries joined strict priority rules */
			pg_help_data->data[entry_joined].pg =
							DCBX_STRICT_PRI_PG;
		अन्यथा अणु
			/* Entries can be joined join BW */
			pg_joined = DCBX_PG_BW_GET(ets->pg_bw_tbl,
					pg_help_data->data[entry_joined].pg) +
				    DCBX_PG_BW_GET(ets->pg_bw_tbl,
					pg_help_data->data[entry_हटाओd].pg);

			DCBX_PG_BW_SET(ets->pg_bw_tbl,
				pg_help_data->data[entry_joined].pg, pg_joined);
		पूर्ण
		/* Joined the entries */
		pg_help_data->num_of_pg--;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2x_dcbx_2cos_limit_cee_three_pg_to_cos_params(
			      काष्ठा bnx2x		*bp,
			      काष्ठा pg_help_data	*pg_help_data,
			      काष्ठा dcbx_ets_feature	*ets,
			      काष्ठा cos_help_data	*cos_data,
			      u32			*pg_pri_orginal_spपढ़ो,
			      u32			pri_join_mask,
			      u8			num_of_dअगर_pri)
अणु
	u8 i = 0;
	u32 pri_tested = 0;
	u8 entry = 0;
	u8 pg_entry = 0;
	bool b_found_strict = false;
	u8 num_of_pri = LLFC_DRIVER_TRAFFIC_TYPE_MAX;

	cos_data->data[0].pri_join_mask = cos_data->data[1].pri_join_mask = 0;
	/* If there are both छोड़ोable and non-छोड़ोable priorities,
	 * the छोड़ोable priorities go to the first queue and the
	 * non-छोड़ोable priorities go to the second queue.
	 */
	अगर (IS_DCBX_PFC_PRI_MIX_PAUSE(bp, pri_join_mask))
		bnx2x_dcbx_separate_छोड़ोable_from_non(bp,
				cos_data, pg_pri_orginal_spपढ़ो, ets);
	अन्यथा अणु
		/* If two BW-limited PG-s were combined to one queue,
		 * the BW is their sum.
		 *
		 * If there are only छोड़ोable priorities or only non-छोड़ोable,
		 * and there are both BW-limited and non-BW-limited PG-s,
		 * the BW-limited PG/s go to one queue and the non-BW-limited
		 * PG/s go to the second queue.
		 *
		 * If there are only छोड़ोable priorities or only non-छोड़ोable
		 * and all are BW limited, then	two priorities go to the first
		 * queue and one priority goes to the second queue.
		 *
		 * We will join this two हालs:
		 * अगर one is BW limited it will go to the second queue
		 * otherwise the last priority will get it
		 */

		cos_data->data[0].pausable = cos_data->data[1].pausable =
			IS_DCBX_PFC_PRI_ONLY_PAUSE(bp, pri_join_mask);

		क्रम (i = 0 ; i < num_of_pri; i++) अणु
			pri_tested = 1 << bp->dcbx_port_params.
				app.traffic_type_priority[i];
			pg_entry = (u8)pg_pri_orginal_spपढ़ो[bp->
				dcbx_port_params.app.traffic_type_priority[i]];

			अगर (pg_entry < DCBX_MAX_NUM_PG_BW_ENTRIES) अणु
				entry = 0;

				अगर (i == (num_of_pri-1) && !b_found_strict)
					/* last entry will be handled separately
					 * If no priority is strict than last
					 * entry goes to last queue.
					 */
					entry = 1;
				cos_data->data[entry].pri_join_mask |=
								pri_tested;
				bnx2x_dcbx_add_to_cos_bw(bp,
					&cos_data->data[entry],
					DCBX_PG_BW_GET(ets->pg_bw_tbl,
						       pg_entry));
			पूर्ण अन्यथा अणु
				b_found_strict = true;
				cos_data->data[1].pri_join_mask |= pri_tested;
				/* If we join a group and one is strict
				 * than the bw rules
				 */
				cos_data->data[1].strict =
					BNX2X_DCBX_STRICT_COS_HIGHEST;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnx2x_dcbx_2cos_limit_cee_fill_cos_params(काष्ठा bnx2x *bp,
				       काष्ठा pg_help_data *help_data,
				       काष्ठा dcbx_ets_feature *ets,
				       काष्ठा cos_help_data *cos_data,
				       u32 *pg_pri_orginal_spपढ़ो,
				       u32 pri_join_mask,
				       u8 num_of_dअगर_pri)
अणु
	/* शेष E2 settings */
	cos_data->num_of_cos = DCBX_COS_MAX_NUM_E2;

	चयन (help_data->num_of_pg) अणु
	हाल 1:
		bnx2x_dcbx_2cos_limit_cee_single_pg_to_cos_params(
					       bp,
					       help_data,
					       cos_data,
					       pri_join_mask,
					       num_of_dअगर_pri);
		अवरोध;
	हाल 2:
		bnx2x_dcbx_2cos_limit_cee_two_pg_to_cos_params(
					    bp,
					    help_data,
					    ets,
					    cos_data,
					    pg_pri_orginal_spपढ़ो,
					    pri_join_mask,
					    num_of_dअगर_pri);
		अवरोध;

	हाल 3:
		bnx2x_dcbx_2cos_limit_cee_three_pg_to_cos_params(
					      bp,
					      help_data,
					      ets,
					      cos_data,
					      pg_pri_orginal_spपढ़ो,
					      pri_join_mask,
					      num_of_dअगर_pri);
		अवरोध;
	शेष:
		BNX2X_ERR("Wrong pg_help_data.num_of_pg\n");
		bnx2x_dcbx_ets_disabled_entry_data(bp,
						   cos_data, pri_join_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_dcbx_spपढ़ो_strict_pri(काष्ठा bnx2x *bp,
					काष्ठा cos_help_data *cos_data,
					u8 entry,
					u8 num_spपढ़ो_of_entries,
					u8 strict_app_pris)
अणु
	u8 strict_pri = BNX2X_DCBX_STRICT_COS_HIGHEST;
	u8 num_of_app_pri = MAX_PFC_PRIORITIES;
	u8 app_pri_bit = 0;

	जबतक (num_spपढ़ो_of_entries && num_of_app_pri > 0) अणु
		app_pri_bit = 1 << (num_of_app_pri - 1);
		अगर (app_pri_bit & strict_app_pris) अणु
			काष्ठा cos_entry_help_data *data = &cos_data->
								data[entry];
			num_spपढ़ो_of_entries--;
			अगर (num_spपढ़ो_of_entries == 0) अणु
				/* last entry needed put all the entries left */
				data->cos_bw = DCBX_INVALID_COS_BW;
				data->strict = strict_pri;
				data->pri_join_mask = strict_app_pris;
				data->pausable = DCBX_IS_PFC_PRI_SOME_PAUSE(bp,
							data->pri_join_mask);
			पूर्ण अन्यथा अणु
				strict_app_pris &= ~app_pri_bit;

				data->cos_bw = DCBX_INVALID_COS_BW;
				data->strict = strict_pri;
				data->pri_join_mask = app_pri_bit;
				data->pausable = DCBX_IS_PFC_PRI_SOME_PAUSE(bp,
							data->pri_join_mask);
			पूर्ण

			strict_pri =
			    BNX2X_DCBX_STRICT_COS_NEXT_LOWER_PRI(strict_pri);
			entry++;
		पूर्ण

		num_of_app_pri--;
	पूर्ण

	अगर (num_spपढ़ो_of_entries) अणु
		BNX2X_ERR("Didn't succeed to spread strict priorities\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 bnx2x_dcbx_cee_fill_strict_pri(काष्ठा bnx2x *bp,
					 काष्ठा cos_help_data *cos_data,
					 u8 entry,
					 u8 num_spपढ़ो_of_entries,
					 u8 strict_app_pris)
अणु
	अगर (bnx2x_dcbx_spपढ़ो_strict_pri(bp, cos_data, entry,
					 num_spपढ़ो_of_entries,
					 strict_app_pris)) अणु
		काष्ठा cos_entry_help_data *data = &cos_data->
						    data[entry];
		/* Fill BW entry */
		data->cos_bw = DCBX_INVALID_COS_BW;
		data->strict = BNX2X_DCBX_STRICT_COS_HIGHEST;
		data->pri_join_mask = strict_app_pris;
		data->pausable = DCBX_IS_PFC_PRI_SOME_PAUSE(bp,
				 data->pri_join_mask);
		वापस 1;
	पूर्ण

	वापस num_spपढ़ो_of_entries;
पूर्ण

अटल व्योम bnx2x_dcbx_cee_fill_cos_params(काष्ठा bnx2x *bp,
					   काष्ठा pg_help_data *help_data,
					   काष्ठा dcbx_ets_feature *ets,
					   काष्ठा cos_help_data *cos_data,
					   u32 pri_join_mask)

अणु
	u8 need_num_of_entries = 0;
	u8 i = 0;
	u8 entry = 0;

	/*
	 * अगर the number of requested PG-s in CEE is greater than 3
	 * then the results are not determined since this is a violation
	 * of the standard.
	 */
	अगर (help_data->num_of_pg > DCBX_COS_MAX_NUM_E3B0) अणु
		अगर (bnx2x_dcbx_join_pgs(bp, ets, help_data,
					DCBX_COS_MAX_NUM_E3B0)) अणु
			BNX2X_ERR("Unable to reduce the number of PGs - we will disables ETS\n");
			bnx2x_dcbx_ets_disabled_entry_data(bp, cos_data,
							   pri_join_mask);
			वापस;
		पूर्ण
	पूर्ण

	क्रम (i = 0 ; i < help_data->num_of_pg; i++) अणु
		काष्ठा pg_entry_help_data *pg =  &help_data->data[i];
		अगर (pg->pg < DCBX_MAX_NUM_PG_BW_ENTRIES) अणु
			काष्ठा cos_entry_help_data *data = &cos_data->
							    data[entry];
			/* Fill BW entry */
			data->cos_bw = DCBX_PG_BW_GET(ets->pg_bw_tbl, pg->pg);
			data->strict = BNX2X_DCBX_STRICT_INVALID;
			data->pri_join_mask = pg->pg_priority;
			data->pausable = DCBX_IS_PFC_PRI_SOME_PAUSE(bp,
						data->pri_join_mask);

			entry++;
		पूर्ण अन्यथा अणु
			need_num_of_entries =  min_t(u8,
				(u8)pg->num_of_dअगर_pri,
				(u8)DCBX_COS_MAX_NUM_E3B0 -
						 help_data->num_of_pg + 1);
			/*
			 * If there are still VOQ-s which have no associated PG,
			 * then associate these VOQ-s to PG15. These PG-s will
			 * be used क्रम SP between priorities on PG15.
			 */
			entry += bnx2x_dcbx_cee_fill_strict_pri(bp, cos_data,
				entry, need_num_of_entries, pg->pg_priority);
		पूर्ण
	पूर्ण

	/* the entry will represent the number of COSes used */
	cos_data->num_of_cos = entry;
पूर्ण
अटल व्योम bnx2x_dcbx_fill_cos_params(काष्ठा bnx2x *bp,
				       काष्ठा pg_help_data *help_data,
				       काष्ठा dcbx_ets_feature *ets,
				       u32 *pg_pri_orginal_spपढ़ो)
अणु
	काष्ठा cos_help_data         cos_data;
	u8                    i                           = 0;
	u32                   pri_join_mask               = 0;
	u8                    num_of_dअगर_pri              = 0;

	स_रखो(&cos_data, 0, माप(cos_data));

	/* Validate the pg value */
	क्रम (i = 0; i < help_data->num_of_pg ; i++) अणु
		अगर (DCBX_STRICT_PRIORITY != help_data->data[i].pg &&
		    DCBX_MAX_NUM_PG_BW_ENTRIES <= help_data->data[i].pg)
			BNX2X_ERR("Invalid pg[%d] data %x\n", i,
				  help_data->data[i].pg);
		pri_join_mask   |=  help_data->data[i].pg_priority;
		num_of_dअगर_pri  += help_data->data[i].num_of_dअगर_pri;
	पूर्ण

	/* शेषs */
	cos_data.num_of_cos = 1;
	क्रम (i = 0; i < ARRAY_SIZE(cos_data.data); i++) अणु
		cos_data.data[i].pri_join_mask = 0;
		cos_data.data[i].pausable = false;
		cos_data.data[i].strict = BNX2X_DCBX_STRICT_INVALID;
		cos_data.data[i].cos_bw = DCBX_INVALID_COS_BW;
	पूर्ण

	अगर (CHIP_IS_E3B0(bp))
		bnx2x_dcbx_cee_fill_cos_params(bp, help_data, ets,
					       &cos_data, pri_join_mask);
	अन्यथा /* E2 + E3A0 */
		bnx2x_dcbx_2cos_limit_cee_fill_cos_params(bp,
							  help_data, ets,
							  &cos_data,
							  pg_pri_orginal_spपढ़ो,
							  pri_join_mask,
							  num_of_dअगर_pri);

	क्रम (i = 0; i < cos_data.num_of_cos ; i++) अणु
		काष्ठा bnx2x_dcbx_cos_params *p =
			&bp->dcbx_port_params.ets.cos_params[i];

		p->strict = cos_data.data[i].strict;
		p->bw_tbl = cos_data.data[i].cos_bw;
		p->pri_biपंचांगask = cos_data.data[i].pri_join_mask;
		p->छोड़ोable = cos_data.data[i].pausable;

		/* sanity */
		अगर (p->bw_tbl != DCBX_INVALID_COS_BW ||
		    p->strict != BNX2X_DCBX_STRICT_INVALID) अणु
			अगर (p->pri_biपंचांगask == 0)
				BNX2X_ERR("Invalid pri_bitmask for %d\n", i);

			अगर (CHIP_IS_E2(bp) || CHIP_IS_E3A0(bp)) अणु

				अगर (p->छोड़ोable &&
				    DCBX_PFC_PRI_GET_NON_PAUSE(bp,
						p->pri_biपंचांगask) != 0)
					BNX2X_ERR("Inconsistent config for pausable COS %d\n",
						  i);

				अगर (!p->छोड़ोable &&
				    DCBX_PFC_PRI_GET_PAUSE(bp,
						p->pri_biपंचांगask) != 0)
					BNX2X_ERR("Inconsistent config for nonpausable COS %d\n",
						  i);
			पूर्ण
		पूर्ण

		अगर (p->छोड़ोable)
			DP(BNX2X_MSG_DCB, "COS %d PAUSABLE prijoinmask 0x%x\n",
				  i, cos_data.data[i].pri_join_mask);
		अन्यथा
			DP(BNX2X_MSG_DCB,
			   "COS %d NONPAUSABLE prijoinmask 0x%x\n",
			   i, cos_data.data[i].pri_join_mask);
	पूर्ण

	bp->dcbx_port_params.ets.num_of_cos = cos_data.num_of_cos ;
पूर्ण

अटल व्योम bnx2x_dcbx_get_ets_pri_pg_tbl(काष्ठा bnx2x *bp,
				u32 *set_configuration_ets_pg,
				u32 *pri_pg_tbl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DCBX_MAX_NUM_PRI_PG_ENTRIES; i++) अणु
		set_configuration_ets_pg[i] = DCBX_PRI_PG_GET(pri_pg_tbl, i);

		DP(BNX2X_MSG_DCB, "set_configuration_ets_pg[%d] = 0x%x\n",
		   i, set_configuration_ets_pg[i]);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_dcbx_fw_काष्ठा(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_func_tx_start_params *pfc_fw_cfg)
अणु
	u16 pri_bit = 0;
	u8 cos = 0, pri = 0;
	काष्ठा priority_cos *tt2cos;
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;
	पूर्णांक mfw_configured = SHMEM2_HAS(bp, drv_flags) &&
			     GET_FLAGS(SHMEM2_RD(bp, drv_flags),
				       1 << DRV_FLAGS_DCB_MFW_CONFIGURED);

	स_रखो(pfc_fw_cfg, 0, माप(*pfc_fw_cfg));

	/* to disable DCB - the काष्ठाure must be zeroed */
	अगर ((bp->dcbx_error & DCBX_REMOTE_MIB_ERROR) && !mfw_configured)
		वापस;

	/*लघुcut*/
	tt2cos = pfc_fw_cfg->traffic_type_to_priority_cos;

	/* Fw version should be incremented each update */
	pfc_fw_cfg->dcb_version = ++bp->dcb_version;
	pfc_fw_cfg->dcb_enabled = 1;

	/* Fill priority parameters */
	क्रम (pri = 0; pri < LLFC_DRIVER_TRAFFIC_TYPE_MAX; pri++) अणु
		tt2cos[pri].priority = ttp[pri];
		pri_bit = 1 << tt2cos[pri].priority;

		/* Fill COS parameters based on COS calculated to
		 * make it more general क्रम future use */
		क्रम (cos = 0; cos < bp->dcbx_port_params.ets.num_of_cos; cos++)
			अगर (bp->dcbx_port_params.ets.cos_params[cos].
						pri_biपंचांगask & pri_bit)
					tt2cos[pri].cos = cos;

		pfc_fw_cfg->dcb_outer_pri[pri]  = ttp[pri];
	पूर्ण

	/* we never want the FW to add a 0 vlan tag */
	pfc_fw_cfg->करोnt_add_pri_0_en = 1;

	bnx2x_dcbx_prपूर्णांक_cos_params(bp,	pfc_fw_cfg);
पूर्ण

व्योम bnx2x_dcbx_pmf_update(काष्ठा bnx2x *bp)
अणु
	/* अगर we need to synchronize DCBX result from prev PMF
	 * पढ़ो it from shmem and update bp and netdev accordingly
	 */
	अगर (SHMEM2_HAS(bp, drv_flags) &&
	   GET_FLAGS(SHMEM2_RD(bp, drv_flags), 1 << DRV_FLAGS_DCB_CONFIGURED)) अणु
		/* Read neg results अगर dcbx is in the FW */
		अगर (bnx2x_dcbx_पढ़ो_shmem_neg_results(bp))
			वापस;

		bnx2x_dump_dcbx_drv_param(bp, &bp->dcbx_local_feat,
					  bp->dcbx_error);
		bnx2x_get_dcbx_drv_param(bp, &bp->dcbx_local_feat,
					 bp->dcbx_error);
#अगर_घोषित BCM_DCBNL
		/*
		 * Add new app tlvs to dcbnl
		 */
		bnx2x_dcbnl_update_applist(bp, false);
		/*
		 * Send a notअगरication क्रम the new negotiated parameters
		 */
		dcbnl_cee_notअगरy(bp->dev, RTM_GETDCB, DCB_CMD_CEE_GET, 0, 0);
#पूर्ण_अगर
		/*
		 * reconfigure the netdevice with the results of the new
		 * dcbx negotiation.
		 */
		bnx2x_dcbx_update_tc_mapping(bp);
	पूर्ण
पूर्ण

/* DCB netlink */
#अगर_घोषित BCM_DCBNL

#घोषणा BNX2X_DCBX_CAPS		(DCB_CAP_DCBX_LLD_MANAGED | \
				DCB_CAP_DCBX_VER_CEE | DCB_CAP_DCBX_STATIC)

अटल अंतरभूत bool bnx2x_dcbnl_set_valid(काष्ठा bnx2x *bp)
अणु
	/* validate dcbnl call that may change HW state:
	 * DCB is on and DCBX mode was SUCCESSFULLY set by the user.
	 */
	वापस bp->dcb_state && bp->dcbx_mode_uset;
पूर्ण

अटल u8 bnx2x_dcbnl_get_state(काष्ठा net_device *netdev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "state = %d\n", bp->dcb_state);
	वापस bp->dcb_state;
पूर्ण

अटल u8 bnx2x_dcbnl_set_state(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "state = %s\n", state ? "on" : "off");

	/* Fail to set state to "enabled" अगर dcbx is disabled in nvram */
	अगर (state && ((bp->dcbx_enabled == BNX2X_DCBX_ENABLED_OFF) ||
		      (bp->dcbx_enabled == BNX2X_DCBX_ENABLED_INVALID))) अणु
		DP(BNX2X_MSG_DCB, "Can not set dcbx to enabled while it is disabled in nvm\n");
		वापस 1;
	पूर्ण

	bnx2x_dcbx_set_state(bp, (state ? true : false), bp->dcbx_enabled);
	वापस 0;
पूर्ण

अटल व्योम bnx2x_dcbnl_get_perm_hw_addr(काष्ठा net_device *netdev,
					 u8 *perm_addr)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "GET-PERM-ADDR\n");

	/* first the HW mac address */
	स_नकल(perm_addr, netdev->dev_addr, netdev->addr_len);

	अगर (CNIC_LOADED(bp))
		/* second SAN address */
		स_नकल(perm_addr+netdev->addr_len, bp->fip_mac,
		       netdev->addr_len);
पूर्ण

अटल व्योम bnx2x_dcbnl_set_pg_tccfg_tx(काष्ठा net_device *netdev, पूर्णांक prio,
					u8 prio_type, u8 pgid, u8 bw_pct,
					u8 up_map)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);

	DP(BNX2X_MSG_DCB, "prio[%d] = %d\n", prio, pgid);
	अगर (!bnx2x_dcbnl_set_valid(bp) || prio >= DCBX_MAX_NUM_PRI_PG_ENTRIES)
		वापस;

	/**
	 * bw_pct ignored -	band-width percentage devision between user
	 *			priorities within the same group is not
	 *			standard and hence not supported
	 *
	 * prio_type ignored -	priority levels within the same group are not
	 *			standard and hence are not supported. According
	 *			to the standard pgid 15 is dedicated to strict
	 *			priority traffic (on the port level).
	 *
	 * up_map ignored
	 */

	bp->dcbx_config_params.admin_configuration_ets_pg[prio] = pgid;
	bp->dcbx_config_params.admin_ets_configuration_tx_enable = 1;
पूर्ण

अटल व्योम bnx2x_dcbnl_set_pg_bwgcfg_tx(काष्ठा net_device *netdev,
					 पूर्णांक pgid, u8 bw_pct)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "pgid[%d] = %d\n", pgid, bw_pct);

	अगर (!bnx2x_dcbnl_set_valid(bp) || pgid >= DCBX_MAX_NUM_PG_BW_ENTRIES)
		वापस;

	bp->dcbx_config_params.admin_configuration_bw_precentage[pgid] = bw_pct;
	bp->dcbx_config_params.admin_ets_configuration_tx_enable = 1;
पूर्ण

अटल व्योम bnx2x_dcbnl_set_pg_tccfg_rx(काष्ठा net_device *netdev, पूर्णांक prio,
					u8 prio_type, u8 pgid, u8 bw_pct,
					u8 up_map)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "Nothing to set; No RX support\n");
पूर्ण

अटल व्योम bnx2x_dcbnl_set_pg_bwgcfg_rx(काष्ठा net_device *netdev,
					 पूर्णांक pgid, u8 bw_pct)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "Nothing to set; No RX support\n");
पूर्ण

अटल व्योम bnx2x_dcbnl_get_pg_tccfg_tx(काष्ठा net_device *netdev, पूर्णांक prio,
					u8 *prio_type, u8 *pgid, u8 *bw_pct,
					u8 *up_map)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "prio = %d\n", prio);

	/**
	 * bw_pct ignored -	band-width percentage devision between user
	 *			priorities within the same group is not
	 *			standard and hence not supported
	 *
	 * prio_type ignored -	priority levels within the same group are not
	 *			standard and hence are not supported. According
	 *			to the standard pgid 15 is dedicated to strict
	 *			priority traffic (on the port level).
	 *
	 * up_map ignored
	 */
	*up_map = *bw_pct = *prio_type = *pgid = 0;

	अगर (!bp->dcb_state || prio >= DCBX_MAX_NUM_PRI_PG_ENTRIES)
		वापस;

	*pgid = DCBX_PRI_PG_GET(bp->dcbx_local_feat.ets.pri_pg_tbl, prio);
पूर्ण

अटल व्योम bnx2x_dcbnl_get_pg_bwgcfg_tx(काष्ठा net_device *netdev,
					 पूर्णांक pgid, u8 *bw_pct)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "pgid = %d\n", pgid);

	*bw_pct = 0;

	अगर (!bp->dcb_state || pgid >= DCBX_MAX_NUM_PG_BW_ENTRIES)
		वापस;

	*bw_pct = DCBX_PG_BW_GET(bp->dcbx_local_feat.ets.pg_bw_tbl, pgid);
पूर्ण

अटल व्योम bnx2x_dcbnl_get_pg_tccfg_rx(काष्ठा net_device *netdev, पूर्णांक prio,
					u8 *prio_type, u8 *pgid, u8 *bw_pct,
					u8 *up_map)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "Nothing to get; No RX support\n");

	*prio_type = *pgid = *bw_pct = *up_map = 0;
पूर्ण

अटल व्योम bnx2x_dcbnl_get_pg_bwgcfg_rx(काष्ठा net_device *netdev,
					 पूर्णांक pgid, u8 *bw_pct)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "Nothing to get; No RX support\n");

	*bw_pct = 0;
पूर्ण

अटल व्योम bnx2x_dcbnl_set_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक prio,
				    u8 setting)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "prio[%d] = %d\n", prio, setting);

	अगर (!bnx2x_dcbnl_set_valid(bp) || prio >= MAX_PFC_PRIORITIES)
		वापस;

	अगर (setting) अणु
		bp->dcbx_config_params.admin_pfc_biपंचांगap |= (1 << prio);
		bp->dcbx_config_params.admin_pfc_tx_enable = 1;
	पूर्ण अन्यथा अणु
		bp->dcbx_config_params.admin_pfc_biपंचांगap &= ~(1 << prio);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_dcbnl_get_pfc_cfg(काष्ठा net_device *netdev, पूर्णांक prio,
				    u8 *setting)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "prio = %d\n", prio);

	*setting = 0;

	अगर (!bp->dcb_state || prio >= MAX_PFC_PRIORITIES)
		वापस;

	*setting = (bp->dcbx_local_feat.pfc.pri_en_biपंचांगap >> prio) & 0x1;
पूर्ण

अटल u8 bnx2x_dcbnl_set_all(काष्ठा net_device *netdev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);

	DP(BNX2X_MSG_DCB, "SET-ALL\n");

	अगर (!bnx2x_dcbnl_set_valid(bp))
		वापस 1;

	अगर (bp->recovery_state != BNX2X_RECOVERY_DONE) अणु
		netdev_err(bp->dev,
			   "Handling parity error recovery. Try again later\n");
		वापस 1;
	पूर्ण
	अगर (netअगर_running(bp->dev)) अणु
		bnx2x_update_drv_flags(bp,
				       1 << DRV_FLAGS_DCB_MFW_CONFIGURED,
				       1);
		bnx2x_dcbx_init(bp, true);
	पूर्ण
	DP(BNX2X_MSG_DCB, "set_dcbx_params done\n");

	वापस 0;
पूर्ण

अटल u8 bnx2x_dcbnl_get_cap(काष्ठा net_device *netdev, पूर्णांक capid, u8 *cap)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	u8 rval = 0;

	अगर (bp->dcb_state) अणु
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
			*cap = 0x80;	/* 8 priorities क्रम PGs */
			अवरोध;
		हाल DCB_CAP_ATTR_PFC_TCS:
			*cap = 0x80;	/* 8 priorities क्रम PFC */
			अवरोध;
		हाल DCB_CAP_ATTR_GSP:
			*cap = true;
			अवरोध;
		हाल DCB_CAP_ATTR_BCN:
			*cap = false;
			अवरोध;
		हाल DCB_CAP_ATTR_DCBX:
			*cap = BNX2X_DCBX_CAPS;
			अवरोध;
		शेष:
			BNX2X_ERR("Non valid capability ID\n");
			rval = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		DP(BNX2X_MSG_DCB, "DCB disabled\n");
		rval = 1;
	पूर्ण

	DP(BNX2X_MSG_DCB, "capid %d:%x\n", capid, *cap);
	वापस rval;
पूर्ण

अटल पूर्णांक bnx2x_dcbnl_get_numtcs(काष्ठा net_device *netdev, पूर्णांक tcid, u8 *num)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	u8 rval = 0;

	DP(BNX2X_MSG_DCB, "tcid %d\n", tcid);

	अगर (bp->dcb_state) अणु
		चयन (tcid) अणु
		हाल DCB_NUMTCS_ATTR_PG:
			*num = CHIP_IS_E3B0(bp) ? DCBX_COS_MAX_NUM_E3B0 :
						  DCBX_COS_MAX_NUM_E2;
			अवरोध;
		हाल DCB_NUMTCS_ATTR_PFC:
			*num = CHIP_IS_E3B0(bp) ? DCBX_COS_MAX_NUM_E3B0 :
						  DCBX_COS_MAX_NUM_E2;
			अवरोध;
		शेष:
			BNX2X_ERR("Non valid TC-ID\n");
			rval = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		DP(BNX2X_MSG_DCB, "DCB disabled\n");
		rval = 1;
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक bnx2x_dcbnl_set_numtcs(काष्ठा net_device *netdev, पूर्णांक tcid, u8 num)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "num tcs = %d; Not supported\n", num);
	वापस -EINVAL;
पूर्ण

अटल u8 bnx2x_dcbnl_get_pfc_state(काष्ठा net_device *netdev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "state = %d\n", bp->dcbx_local_feat.pfc.enabled);

	अगर (!bp->dcb_state)
		वापस 0;

	वापस bp->dcbx_local_feat.pfc.enabled;
पूर्ण

अटल व्योम bnx2x_dcbnl_set_pfc_state(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "state = %s\n", state ? "on" : "off");

	अगर (!bnx2x_dcbnl_set_valid(bp))
		वापस;

	bp->dcbx_config_params.admin_pfc_tx_enable =
	bp->dcbx_config_params.admin_pfc_enable = (state ? 1 : 0);
पूर्ण

अटल व्योम bnx2x_admin_app_set_ent(
	काष्ठा bnx2x_admin_priority_app_table *app_ent,
	u8 idtype, u16 idval, u8 up)
अणु
	app_ent->valid = 1;

	चयन (idtype) अणु
	हाल DCB_APP_IDTYPE_ETHTYPE:
		app_ent->traffic_type = TRAFFIC_TYPE_ETH;
		अवरोध;
	हाल DCB_APP_IDTYPE_PORTNUM:
		app_ent->traffic_type = TRAFFIC_TYPE_PORT;
		अवरोध;
	शेष:
		अवरोध; /* never माला_लो here */
	पूर्ण
	app_ent->app_id = idval;
	app_ent->priority = up;
पूर्ण

अटल bool bnx2x_admin_app_is_equal(
	काष्ठा bnx2x_admin_priority_app_table *app_ent,
	u8 idtype, u16 idval)
अणु
	अगर (!app_ent->valid)
		वापस false;

	चयन (idtype) अणु
	हाल DCB_APP_IDTYPE_ETHTYPE:
		अगर (app_ent->traffic_type != TRAFFIC_TYPE_ETH)
			वापस false;
		अवरोध;
	हाल DCB_APP_IDTYPE_PORTNUM:
		अगर (app_ent->traffic_type != TRAFFIC_TYPE_PORT)
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	अगर (app_ent->app_id != idval)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक bnx2x_set_admin_app_up(काष्ठा bnx2x *bp, u8 idtype, u16 idval, u8 up)
अणु
	पूर्णांक i, ff;

	/* iterate over the app entries looking क्रम idtype and idval */
	क्रम (i = 0, ff = -1; i < DCBX_CONFIG_MAX_APP_PROTOCOL; i++) अणु
		काष्ठा bnx2x_admin_priority_app_table *app_ent =
			&bp->dcbx_config_params.admin_priority_app_table[i];
		अगर (bnx2x_admin_app_is_equal(app_ent, idtype, idval))
			अवरोध;

		अगर (ff < 0 && !app_ent->valid)
			ff = i;
	पूर्ण
	अगर (i < DCBX_CONFIG_MAX_APP_PROTOCOL)
		/* अगर found overग_लिखो up */
		bp->dcbx_config_params.
			admin_priority_app_table[i].priority = up;
	अन्यथा अगर (ff >= 0)
		/* not found use first-मुक्त */
		bnx2x_admin_app_set_ent(
			&bp->dcbx_config_params.admin_priority_app_table[ff],
			idtype, idval, up);
	अन्यथा अणु
		/* app table is full */
		BNX2X_ERR("Application table is too large\n");
		वापस -EBUSY;
	पूर्ण

	/* up configured, अगर not 0 make sure feature is enabled */
	अगर (up)
		bp->dcbx_config_params.admin_application_priority_tx_enable = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_dcbnl_set_app_up(काष्ठा net_device *netdev, u8 idtype,
				  u16 idval, u8 up)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);

	DP(BNX2X_MSG_DCB, "app_type %d, app_id %x, prio bitmap %d\n",
	   idtype, idval, up);

	अगर (!bnx2x_dcbnl_set_valid(bp)) अणु
		DP(BNX2X_MSG_DCB, "dcbnl call not valid\n");
		वापस -EINVAL;
	पूर्ण

	/* verअगरy idtype */
	चयन (idtype) अणु
	हाल DCB_APP_IDTYPE_ETHTYPE:
	हाल DCB_APP_IDTYPE_PORTNUM:
		अवरोध;
	शेष:
		DP(BNX2X_MSG_DCB, "Wrong ID type\n");
		वापस -EINVAL;
	पूर्ण
	वापस bnx2x_set_admin_app_up(bp, idtype, idval, up);
पूर्ण

अटल u8 bnx2x_dcbnl_get_dcbx(काष्ठा net_device *netdev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	u8 state;

	state = DCB_CAP_DCBX_LLD_MANAGED | DCB_CAP_DCBX_VER_CEE;

	अगर (bp->dcbx_enabled == BNX2X_DCBX_ENABLED_ON_NEG_OFF)
		state |= DCB_CAP_DCBX_STATIC;

	वापस state;
पूर्ण

अटल u8 bnx2x_dcbnl_set_dcbx(काष्ठा net_device *netdev, u8 state)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	DP(BNX2X_MSG_DCB, "state = %02x\n", state);

	/* set dcbx mode */

	अगर ((state & BNX2X_DCBX_CAPS) != state) अणु
		BNX2X_ERR("Requested DCBX mode %x is beyond advertised capabilities\n",
			  state);
		वापस 1;
	पूर्ण

	अगर (bp->dcb_state != BNX2X_DCB_STATE_ON) अणु
		BNX2X_ERR("DCB turned off, DCBX configuration is invalid\n");
		वापस 1;
	पूर्ण

	अगर (state & DCB_CAP_DCBX_STATIC)
		bp->dcbx_enabled = BNX2X_DCBX_ENABLED_ON_NEG_OFF;
	अन्यथा
		bp->dcbx_enabled = BNX2X_DCBX_ENABLED_ON_NEG_ON;

	bp->dcbx_mode_uset = true;
	वापस 0;
पूर्ण

अटल u8 bnx2x_dcbnl_get_featcfg(काष्ठा net_device *netdev, पूर्णांक featid,
				  u8 *flags)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	u8 rval = 0;

	DP(BNX2X_MSG_DCB, "featid %d\n", featid);

	अगर (bp->dcb_state) अणु
		*flags = 0;
		चयन (featid) अणु
		हाल DCB_FEATCFG_ATTR_PG:
			अगर (bp->dcbx_local_feat.ets.enabled)
				*flags |= DCB_FEATCFG_ENABLE;
			अगर (bp->dcbx_error & (DCBX_LOCAL_ETS_ERROR |
					      DCBX_REMOTE_MIB_ERROR))
				*flags |= DCB_FEATCFG_ERROR;
			अवरोध;
		हाल DCB_FEATCFG_ATTR_PFC:
			अगर (bp->dcbx_local_feat.pfc.enabled)
				*flags |= DCB_FEATCFG_ENABLE;
			अगर (bp->dcbx_error & (DCBX_LOCAL_PFC_ERROR |
					      DCBX_LOCAL_PFC_MISMATCH |
					      DCBX_REMOTE_MIB_ERROR))
				*flags |= DCB_FEATCFG_ERROR;
			अवरोध;
		हाल DCB_FEATCFG_ATTR_APP:
			अगर (bp->dcbx_local_feat.app.enabled)
				*flags |= DCB_FEATCFG_ENABLE;
			अगर (bp->dcbx_error & (DCBX_LOCAL_APP_ERROR |
					      DCBX_LOCAL_APP_MISMATCH |
					      DCBX_REMOTE_MIB_ERROR))
				*flags |= DCB_FEATCFG_ERROR;
			अवरोध;
		शेष:
			BNX2X_ERR("Non valid feature-ID\n");
			rval = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		DP(BNX2X_MSG_DCB, "DCB disabled\n");
		rval = 1;
	पूर्ण

	वापस rval;
पूर्ण

अटल u8 bnx2x_dcbnl_set_featcfg(काष्ठा net_device *netdev, पूर्णांक featid,
				  u8 flags)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	u8 rval = 0;

	DP(BNX2X_MSG_DCB, "featid = %d flags = %02x\n", featid, flags);

	/* ignore the 'advertise' flag */
	अगर (bnx2x_dcbnl_set_valid(bp)) अणु
		चयन (featid) अणु
		हाल DCB_FEATCFG_ATTR_PG:
			bp->dcbx_config_params.admin_ets_enable =
				flags & DCB_FEATCFG_ENABLE ? 1 : 0;
			bp->dcbx_config_params.admin_ets_willing =
				flags & DCB_FEATCFG_WILLING ? 1 : 0;
			अवरोध;
		हाल DCB_FEATCFG_ATTR_PFC:
			bp->dcbx_config_params.admin_pfc_enable =
				flags & DCB_FEATCFG_ENABLE ? 1 : 0;
			bp->dcbx_config_params.admin_pfc_willing =
				flags & DCB_FEATCFG_WILLING ? 1 : 0;
			अवरोध;
		हाल DCB_FEATCFG_ATTR_APP:
			/* ignore enable, always enabled */
			bp->dcbx_config_params.admin_app_priority_willing =
				flags & DCB_FEATCFG_WILLING ? 1 : 0;
			अवरोध;
		शेष:
			BNX2X_ERR("Non valid feature-ID\n");
			rval = 1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		DP(BNX2X_MSG_DCB, "dcbnl call not valid\n");
		rval = 1;
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक bnx2x_peer_appinfo(काष्ठा net_device *netdev,
			      काष्ठा dcb_peer_app_info *info, u16* app_count)
अणु
	पूर्णांक i;
	काष्ठा bnx2x *bp = netdev_priv(netdev);

	DP(BNX2X_MSG_DCB, "APP-INFO\n");

	info->willing = (bp->dcbx_remote_flags & DCBX_APP_REM_WILLING) ?: 0;
	info->error = (bp->dcbx_remote_flags & DCBX_APP_RX_ERROR) ?: 0;
	*app_count = 0;

	क्रम (i = 0; i < DCBX_MAX_APP_PROTOCOL; i++)
		अगर (bp->dcbx_remote_feat.app.app_pri_tbl[i].appBitfield &
		    DCBX_APP_ENTRY_VALID)
			(*app_count)++;
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_peer_apptable(काष्ठा net_device *netdev,
			       काष्ठा dcb_app *table)
अणु
	पूर्णांक i, j;
	काष्ठा bnx2x *bp = netdev_priv(netdev);

	DP(BNX2X_MSG_DCB, "APP-TABLE\n");

	क्रम (i = 0, j = 0; i < DCBX_MAX_APP_PROTOCOL; i++) अणु
		काष्ठा dcbx_app_priority_entry *ent =
			&bp->dcbx_remote_feat.app.app_pri_tbl[i];

		अगर (ent->appBitfield & DCBX_APP_ENTRY_VALID) अणु
			table[j].selector = bnx2x_dcbx_dcbnl_app_idtype(ent);
			table[j].priority = bnx2x_dcbx_dcbnl_app_up(ent);
			table[j++].protocol = ent->app_id;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_cee_peer_getpg(काष्ठा net_device *netdev, काष्ठा cee_pg *pg)
अणु
	पूर्णांक i;
	काष्ठा bnx2x *bp = netdev_priv(netdev);

	pg->willing = (bp->dcbx_remote_flags & DCBX_ETS_REM_WILLING) ?: 0;

	क्रम (i = 0; i < CEE_DCBX_MAX_PGS; i++) अणु
		pg->pg_bw[i] =
			DCBX_PG_BW_GET(bp->dcbx_remote_feat.ets.pg_bw_tbl, i);
		pg->prio_pg[i] =
			DCBX_PRI_PG_GET(bp->dcbx_remote_feat.ets.pri_pg_tbl, i);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_cee_peer_getpfc(काष्ठा net_device *netdev,
				 काष्ठा cee_pfc *pfc)
अणु
	काष्ठा bnx2x *bp = netdev_priv(netdev);
	pfc->tcs_supported = bp->dcbx_remote_feat.pfc.pfc_caps;
	pfc->pfc_en = bp->dcbx_remote_feat.pfc.pri_en_biपंचांगap;
	वापस 0;
पूर्ण

स्थिर काष्ठा dcbnl_rtnl_ops bnx2x_dcbnl_ops = अणु
	.माला_लोtate		= bnx2x_dcbnl_get_state,
	.setstate		= bnx2x_dcbnl_set_state,
	.getpermhwaddr		= bnx2x_dcbnl_get_perm_hw_addr,
	.setpgtccfgtx		= bnx2x_dcbnl_set_pg_tccfg_tx,
	.setpgbwgcfgtx		= bnx2x_dcbnl_set_pg_bwgcfg_tx,
	.setpgtccfgrx		= bnx2x_dcbnl_set_pg_tccfg_rx,
	.setpgbwgcfgrx		= bnx2x_dcbnl_set_pg_bwgcfg_rx,
	.getpgtccfgtx		= bnx2x_dcbnl_get_pg_tccfg_tx,
	.getpgbwgcfgtx		= bnx2x_dcbnl_get_pg_bwgcfg_tx,
	.getpgtccfgrx		= bnx2x_dcbnl_get_pg_tccfg_rx,
	.getpgbwgcfgrx		= bnx2x_dcbnl_get_pg_bwgcfg_rx,
	.setpfccfg		= bnx2x_dcbnl_set_pfc_cfg,
	.getpfccfg		= bnx2x_dcbnl_get_pfc_cfg,
	.setall			= bnx2x_dcbnl_set_all,
	.अ_लोap			= bnx2x_dcbnl_get_cap,
	.getnumtcs		= bnx2x_dcbnl_get_numtcs,
	.setnumtcs		= bnx2x_dcbnl_set_numtcs,
	.getpfcstate		= bnx2x_dcbnl_get_pfc_state,
	.setpfcstate		= bnx2x_dcbnl_set_pfc_state,
	.setapp			= bnx2x_dcbnl_set_app_up,
	.getdcbx		= bnx2x_dcbnl_get_dcbx,
	.setdcbx		= bnx2x_dcbnl_set_dcbx,
	.getfeatcfg		= bnx2x_dcbnl_get_featcfg,
	.setfeatcfg		= bnx2x_dcbnl_set_featcfg,
	.peer_getappinfo	= bnx2x_peer_appinfo,
	.peer_getapptable	= bnx2x_peer_apptable,
	.cee_peer_getpg		= bnx2x_cee_peer_getpg,
	.cee_peer_getpfc	= bnx2x_cee_peer_getpfc,
पूर्ण;

#पूर्ण_अगर /* BCM_DCBNL */
