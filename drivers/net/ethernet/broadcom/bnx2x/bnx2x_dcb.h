<शैली गुरु>
/* bnx2x_dcb.h: QLogic Everest network driver.
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
#अगर_अघोषित BNX2X_DCB_H
#घोषणा BNX2X_DCB_H

#समावेश "bnx2x_hsi.h"

#घोषणा LLFC_DRIVER_TRAFFIC_TYPE_MAX 3 /* NW, iSCSI, FCoE */
काष्ठा bnx2x_dcbx_app_params अणु
	u32 enabled;
	u32 traffic_type_priority[LLFC_DRIVER_TRAFFIC_TYPE_MAX];
पूर्ण;

#घोषणा DCBX_COS_MAX_NUM_E2	DCBX_E2E3_MAX_NUM_COS
/* bnx2x currently limits numbers of supported COSes to 3 to be extended to 6 */
#घोषणा BNX2X_MAX_COS_SUPPORT	3
#घोषणा DCBX_COS_MAX_NUM_E3B0	BNX2X_MAX_COS_SUPPORT
#घोषणा DCBX_COS_MAX_NUM	BNX2X_MAX_COS_SUPPORT

काष्ठा bnx2x_dcbx_cos_params अणु
	u32	bw_tbl;
	u32	pri_biपंचांगask;
	/*
	 * strict priority: valid values are 0..5; 0 is highest priority.
	 * There can't be two COSes with the same priority.
	 */
	u8	strict;
#घोषणा BNX2X_DCBX_STRICT_INVALID			DCBX_COS_MAX_NUM
#घोषणा BNX2X_DCBX_STRICT_COS_HIGHEST			0
#घोषणा BNX2X_DCBX_STRICT_COS_NEXT_LOWER_PRI(sp)	((sp) + 1)
	u8	छोड़ोable;
पूर्ण;

काष्ठा bnx2x_dcbx_pg_params अणु
	u32 enabled;
	u8 num_of_cos; /* valid COS entries */
	काष्ठा bnx2x_dcbx_cos_params	cos_params[DCBX_COS_MAX_NUM];
पूर्ण;

काष्ठा bnx2x_dcbx_pfc_params अणु
	u32 enabled;
	u32 priority_non_छोड़ोable_mask;
पूर्ण;

काष्ठा bnx2x_dcbx_port_params अणु
	काष्ठा bnx2x_dcbx_pfc_params pfc;
	काष्ठा bnx2x_dcbx_pg_params  ets;
	काष्ठा bnx2x_dcbx_app_params app;
पूर्ण;

#घोषणा BNX2X_DCBX_CONFIG_INV_VALUE			(0xFFFFFFFF)
#घोषणा BNX2X_DCBX_OVERWRITE_SETTINGS_DISABLE		0
#घोषणा BNX2X_DCBX_OVERWRITE_SETTINGS_ENABLE		1
#घोषणा BNX2X_DCBX_OVERWRITE_SETTINGS_INVALID	(BNX2X_DCBX_CONFIG_INV_VALUE)
#घोषणा BNX2X_IS_ETS_ENABLED(bp) ((bp)->dcb_state == BNX2X_DCB_STATE_ON &&\
				  (bp)->dcbx_port_params.ets.enabled)

काष्ठा bnx2x_config_lldp_params अणु
	u32 overग_लिखो_settings;
	u32 msg_tx_hold;
	u32 msg_fast_tx;
	u32 tx_credit_max;
	u32 msg_tx_पूर्णांकerval;
	u32 tx_fast;
पूर्ण;

काष्ठा bnx2x_admin_priority_app_table अणु
		u32 valid;
		u32 priority;
#घोषणा INVALID_TRAFFIC_TYPE_PRIORITY	(0xFFFFFFFF)
		u32 traffic_type;
#घोषणा TRAFFIC_TYPE_ETH		0
#घोषणा TRAFFIC_TYPE_PORT		1
		u32 app_id;
पूर्ण;

#घोषणा DCBX_CONFIG_MAX_APP_PROTOCOL 4
काष्ठा bnx2x_config_dcbx_params अणु
	u32 overग_लिखो_settings;
	u32 admin_dcbx_version;
	u32 admin_ets_enable;
	u32 admin_pfc_enable;
	u32 admin_tc_supported_tx_enable;
	u32 admin_ets_configuration_tx_enable;
	u32 admin_ets_recommendation_tx_enable;
	u32 admin_pfc_tx_enable;
	u32 admin_application_priority_tx_enable;
	u32 admin_ets_willing;
	u32 admin_ets_reco_valid;
	u32 admin_pfc_willing;
	u32 admin_app_priority_willing;
	u32 admin_configuration_bw_precentage[8];
	u32 admin_configuration_ets_pg[8];
	u32 admin_recommendation_bw_precentage[8];
	u32 admin_recommendation_ets_pg[8];
	u32 admin_pfc_biपंचांगap;
	काष्ठा bnx2x_admin_priority_app_table
		admin_priority_app_table[DCBX_CONFIG_MAX_APP_PROTOCOL];
	u32 admin_शेष_priority;
पूर्ण;

#घोषणा GET_FLAGS(flags, bits)		((flags) & (bits))
#घोषणा SET_FLAGS(flags, bits)		((flags) |= (bits))
#घोषणा RESET_FLAGS(flags, bits)	((flags) &= ~(bits))

क्रमागत अणु
	DCBX_READ_LOCAL_MIB,
	DCBX_READ_REMOTE_MIB
पूर्ण;

#घोषणा ETH_TYPE_FCOE		(0x8906)
#घोषणा TCP_PORT_ISCSI		(0xCBC)

#घोषणा PFC_VALUE_FRAME_SIZE				(512)
#घोषणा PFC_QUANTA_IN_न_अंकOSEC_FROM_SPEED_MEGA(mega_speed)  \
				((1000 * PFC_VALUE_FRAME_SIZE)/(mega_speed))

#घोषणा PFC_BRB1_REG_HIGH_LLFC_LOW_THRESHOLD			130
#घोषणा PFC_BRB1_REG_HIGH_LLFC_HIGH_THRESHOLD			170

काष्ठा cos_entry_help_data अणु
	u32			pri_join_mask;
	u32			cos_bw;
	u8			strict;
	bool			pausable;
पूर्ण;

काष्ठा cos_help_data अणु
	काष्ठा cos_entry_help_data	data[DCBX_COS_MAX_NUM];
	u8				num_of_cos;
पूर्ण;

#घोषणा DCBX_ILLEGAL_PG				(0xFF)
#घोषणा DCBX_PFC_PRI_MASK			(0xFF)
#घोषणा DCBX_STRICT_PRIORITY			(15)
#घोषणा DCBX_INVALID_COS_BW			(0xFFFFFFFF)
#घोषणा DCBX_PFC_PRI_NON_PAUSE_MASK(bp)		\
			((bp)->dcbx_port_params.pfc.priority_non_छोड़ोable_mask)
#घोषणा DCBX_PFC_PRI_PAUSE_MASK(bp)		\
					((u8)~DCBX_PFC_PRI_NON_PAUSE_MASK(bp))
#घोषणा DCBX_PFC_PRI_GET_PAUSE(bp, pg_pri)	\
				((pg_pri) & (DCBX_PFC_PRI_PAUSE_MASK(bp)))
#घोषणा DCBX_PFC_PRI_GET_NON_PAUSE(bp, pg_pri)	\
			(DCBX_PFC_PRI_NON_PAUSE_MASK(bp) & (pg_pri))
#घोषणा DCBX_IS_PFC_PRI_SOME_PAUSE(bp, pg_pri)	\
			(0 != DCBX_PFC_PRI_GET_PAUSE(bp, pg_pri))
#घोषणा IS_DCBX_PFC_PRI_ONLY_PAUSE(bp, pg_pri)	\
			(pg_pri == DCBX_PFC_PRI_GET_PAUSE((bp), (pg_pri)))
#घोषणा IS_DCBX_PFC_PRI_ONLY_NON_PAUSE(bp, pg_pri)\
			((pg_pri) == DCBX_PFC_PRI_GET_NON_PAUSE((bp), (pg_pri)))
#घोषणा IS_DCBX_PFC_PRI_MIX_PAUSE(bp, pg_pri)	\
			(!(IS_DCBX_PFC_PRI_ONLY_NON_PAUSE((bp), (pg_pri)) || \
			 IS_DCBX_PFC_PRI_ONLY_PAUSE((bp), (pg_pri))))

काष्ठा pg_entry_help_data अणु
	u8	num_of_dअगर_pri;
	u8	pg;
	u32	pg_priority;
पूर्ण;

काष्ठा pg_help_data अणु
	काष्ठा pg_entry_help_data	data[LLFC_DRIVER_TRAFFIC_TYPE_MAX];
	u8				num_of_pg;
पूर्ण;

/* क्रमward DCB/PFC related declarations */
काष्ठा bnx2x;
व्योम bnx2x_dcbx_update(काष्ठा work_काष्ठा *work);
व्योम bnx2x_dcbx_init_params(काष्ठा bnx2x *bp);
व्योम bnx2x_dcbx_set_state(काष्ठा bnx2x *bp, bool dcb_on, u32 dcbx_enabled);

क्रमागत अणु
	BNX2X_DCBX_STATE_NEG_RECEIVED = 0x1,
	BNX2X_DCBX_STATE_TX_PAUSED,
	BNX2X_DCBX_STATE_TX_RELEASED
पूर्ण;

व्योम bnx2x_dcbx_set_params(काष्ठा bnx2x *bp, u32 state);
व्योम bnx2x_dcbx_pmf_update(काष्ठा bnx2x *bp);
/* DCB netlink */
#अगर_घोषित BCM_DCBNL
बाह्य स्थिर काष्ठा dcbnl_rtnl_ops bnx2x_dcbnl_ops;
पूर्णांक bnx2x_dcbnl_update_applist(काष्ठा bnx2x *bp, bool delall);
#पूर्ण_अगर /* BCM_DCBNL */

पूर्णांक bnx2x_dcbx_stop_hw_tx(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_dcbx_resume_hw_tx(काष्ठा bnx2x *bp);

#पूर्ण_अगर /* BNX2X_DCB_H */
