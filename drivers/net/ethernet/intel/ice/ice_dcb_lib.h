<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_DCB_LIB_H_
#घोषणा _ICE_DCB_LIB_H_

#समावेश "ice.h"
#समावेश "ice_base.h"
#समावेश "ice_lib.h"

#अगर_घोषित CONFIG_DCB
#घोषणा ICE_TC_MAX_BW		100 /* Default Max BW percentage */
#घोषणा ICE_DCB_HW_CHG_RST	0 /* DCB configuration changed with reset */
#घोषणा ICE_DCB_NO_HW_CHG	1 /* DCB configuration did not change */
#घोषणा ICE_DCB_HW_CHG		2 /* DCB configuration changed, no reset */

व्योम ice_dcb_rebuild(काष्ठा ice_pf *pf);
u8 ice_dcb_get_ena_tc(काष्ठा ice_dcbx_cfg *dcbcfg);
u8 ice_dcb_get_num_tc(काष्ठा ice_dcbx_cfg *dcbcfg);
व्योम ice_vsi_set_dcb_tc_cfg(काष्ठा ice_vsi *vsi);
bool ice_is_pfc_causing_hung_q(काष्ठा ice_pf *pf, अचिन्हित पूर्णांक txqueue);
u8 ice_dcb_get_tc(काष्ठा ice_vsi *vsi, पूर्णांक queue_index);
पूर्णांक
ice_pf_dcb_cfg(काष्ठा ice_pf *pf, काष्ठा ice_dcbx_cfg *new_cfg, bool locked);
पूर्णांक ice_dcb_bwchk(काष्ठा ice_pf *pf, काष्ठा ice_dcbx_cfg *dcbcfg);
व्योम ice_pf_dcb_recfg(काष्ठा ice_pf *pf);
व्योम ice_vsi_cfg_dcb_rings(काष्ठा ice_vsi *vsi);
पूर्णांक ice_init_pf_dcb(काष्ठा ice_pf *pf, bool locked);
व्योम ice_update_dcb_stats(काष्ठा ice_pf *pf);
व्योम
ice_tx_prepare_vlan_flags_dcb(काष्ठा ice_ring *tx_ring,
			      काष्ठा ice_tx_buf *first);
व्योम
ice_dcb_process_lldp_set_mib_change(काष्ठा ice_pf *pf,
				    काष्ठा ice_rq_event_info *event);
व्योम ice_vsi_cfg_netdev_tc(काष्ठा ice_vsi *vsi, u8 ena_tc);

/**
 * ice_find_q_in_range
 * @low: start of queue range क्रम a TC i.e. offset of TC
 * @high: start of queue क्रम next TC
 * @tx_q: hung_queue/tx_queue
 *
 * finds अगर queue 'tx_q' falls between the two offsets of any given TC
 */
अटल अंतरभूत bool ice_find_q_in_range(u16 low, u16 high, अचिन्हित पूर्णांक tx_q)
अणु
	वापस (tx_q >= low) && (tx_q < high);
पूर्ण

अटल अंतरभूत व्योम
ice_set_cgd_num(काष्ठा ice_tlan_ctx *tlan_ctx, काष्ठा ice_ring *ring)
अणु
	tlan_ctx->cgd_num = ring->dcb_tc;
पूर्ण

अटल अंतरभूत bool ice_is_dcb_active(काष्ठा ice_pf *pf)
अणु
	वापस (test_bit(ICE_FLAG_FW_LLDP_AGENT, pf->flags) ||
		test_bit(ICE_FLAG_DCB_ENA, pf->flags));
पूर्ण
#अन्यथा
#घोषणा ice_dcb_rebuild(pf) करो अणुपूर्ण जबतक (0)

अटल अंतरभूत u8 ice_dcb_get_ena_tc(काष्ठा ice_dcbx_cfg __always_unused *dcbcfg)
अणु
	वापस ICE_DFLT_TRAFFIC_CLASS;
पूर्ण

अटल अंतरभूत u8 ice_dcb_get_num_tc(काष्ठा ice_dcbx_cfg __always_unused *dcbcfg)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत u8
ice_dcb_get_tc(काष्ठा ice_vsi __always_unused *vsi,
	       पूर्णांक __always_unused queue_index)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_init_pf_dcb(काष्ठा ice_pf *pf, bool __always_unused locked)
अणु
	dev_dbg(ice_pf_to_dev(pf), "DCB not supported\n");
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_pf_dcb_cfg(काष्ठा ice_pf __always_unused *pf,
	       काष्ठा ice_dcbx_cfg __always_unused *new_cfg,
	       bool __always_unused locked)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_tx_prepare_vlan_flags_dcb(काष्ठा ice_ring __always_unused *tx_ring,
			      काष्ठा ice_tx_buf __always_unused *first)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool ice_is_dcb_active(काष्ठा ice_pf __always_unused *pf)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
ice_is_pfc_causing_hung_q(काष्ठा ice_pf __always_unused *pf,
			  अचिन्हित पूर्णांक __always_unused txqueue)
अणु
	वापस false;
पूर्ण

#घोषणा ice_update_dcb_stats(pf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_pf_dcb_recfg(pf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_vsi_cfg_dcb_rings(vsi) करो अणुपूर्ण जबतक (0)
#घोषणा ice_dcb_process_lldp_set_mib_change(pf, event) करो अणुपूर्ण जबतक (0)
#घोषणा ice_set_cgd_num(tlan_ctx, ring) करो अणुपूर्ण जबतक (0)
#घोषणा ice_vsi_cfg_netdev_tc(vsi, ena_tc) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_DCB */
#पूर्ण_अगर /* _ICE_DCB_LIB_H_ */
