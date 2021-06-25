<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_ODM_H__
#घोषणा __RTW_ODM_H__

#समावेश <drv_types.h>

/*
* This file provides utilities/wrappers क्रम rtw driver to use ODM
*/

व्योम rtw_odm_dbg_comp_msg(काष्ठा adapter *adapter);
व्योम rtw_odm_dbg_comp_set(काष्ठा adapter *adapter, u64 comps);
व्योम rtw_odm_dbg_level_msg(व्योम *sel, काष्ठा adapter *adapter);
व्योम rtw_odm_dbg_level_set(काष्ठा adapter *adapter, u32 level);

व्योम rtw_odm_ability_msg(व्योम *sel, काष्ठा adapter *adapter);
व्योम rtw_odm_ability_set(काष्ठा adapter *adapter, u32 ability);

व्योम rtw_odm_adaptivity_parm_msg(व्योम *sel, काष्ठा adapter *adapter);
व्योम rtw_odm_adaptivity_parm_set(काष्ठा adapter *adapter, s8 TH_L2H_ini, s8 TH_EDCCA_HL_dअगरf,
	s8 IGI_Base, bool ForceEDCCA, u8 AdapEn_RSSI, u8 IGI_LowerBound);
व्योम rtw_odm_get_perpkt_rssi(व्योम *sel, काष्ठा adapter *adapter);
#पूर्ण_अगर /*  __RTW_ODM_H__ */
