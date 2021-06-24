<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित	__ODM_RTL8188E_H__
#घोषणा __ODM_RTL8188E_H__

#घोषणा	MAIN_ANT	0
#घोषणा	AUX_ANT	1
#घोषणा	MAIN_ANT_CG_TRX	1
#घोषणा	AUX_ANT_CG_TRX	0
#घोषणा	MAIN_ANT_CGCS_RX	0
#घोषणा	AUX_ANT_CGCS_RX	1

व्योम ODM_DIG_LowerBound_88E(काष्ठा odm_dm_काष्ठा *pDM_Odm);

व्योम rtl88eu_dm_antenna_भाग_init(काष्ठा odm_dm_काष्ठा *dm_odm);

व्योम rtl88eu_dm_antenna_भागersity(काष्ठा odm_dm_काष्ठा *dm_odm);

व्योम rtl88eu_dm_set_tx_ant_by_tx_info(काष्ठा odm_dm_काष्ठा *dm_odm, u8 *desc,
				      u8 mac_id);

व्योम rtl88eu_dm_update_rx_idle_ant(काष्ठा odm_dm_काष्ठा *dm_odm, u8 ant);

व्योम rtl88eu_dm_ant_sel_statistics(काष्ठा odm_dm_काष्ठा *dm_odm, u8 antsel_tr_mux,
				   u32 mac_id, u8 rx_pwdb_all);

व्योम odm_FastAntTraining(काष्ठा odm_dm_काष्ठा *pDM_Odm);

व्योम odm_FastAntTrainingCallback(काष्ठा odm_dm_काष्ठा *pDM_Odm);

व्योम odm_FastAntTrainingWorkItemCallback(काष्ठा odm_dm_काष्ठा *pDM_Odm);

bool ODM_DynamicPrimaryCCA_DupRTS(काष्ठा odm_dm_काष्ठा *pDM_Odm);

#पूर्ण_अगर
