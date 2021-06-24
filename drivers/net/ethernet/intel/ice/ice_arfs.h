<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018-2020, Intel Corporation. */

#अगर_अघोषित _ICE_ARFS_H_
#घोषणा _ICE_ARFS_H_
क्रमागत ice_arfs_fltr_state अणु
	ICE_ARFS_INACTIVE,
	ICE_ARFS_ACTIVE,
	ICE_ARFS_TODEL,
पूर्ण;

काष्ठा ice_arfs_entry अणु
	काष्ठा ice_fdir_fltr fltr_info;
	काष्ठा hlist_node list_entry;
	u64 समय_activated;	/* only valid क्रम UDP flows */
	u32 flow_id;
	/* fltr_state = 0 - ICE_ARFS_INACTIVE:
	 *	filter needs to be updated or programmed in HW.
	 * fltr_state = 1 - ICE_ARFS_ACTIVE:
	 *	filter is active and programmed in HW.
	 * fltr_state = 2 - ICE_ARFS_TODEL:
	 *	filter has been deleted from HW and needs to be हटाओd from
	 *	the aRFS hash table.
	 */
	u8 fltr_state;
पूर्ण;

काष्ठा ice_arfs_entry_ptr अणु
	काष्ठा ice_arfs_entry *arfs_entry;
	काष्ठा hlist_node list_entry;
पूर्ण;

काष्ठा ice_arfs_active_fltr_cntrs अणु
	atomic_t active_tcpv4_cnt;
	atomic_t active_tcpv6_cnt;
	atomic_t active_udpv4_cnt;
	atomic_t active_udpv6_cnt;
पूर्ण;

#अगर_घोषित CONFIG_RFS_ACCEL
पूर्णांक
ice_rx_flow_steer(काष्ठा net_device *netdev, स्थिर काष्ठा sk_buff *skb,
		  u16 rxq_idx, u32 flow_id);
व्योम ice_clear_arfs(काष्ठा ice_vsi *vsi);
व्योम ice_मुक्त_cpu_rx_rmap(काष्ठा ice_vsi *vsi);
व्योम ice_init_arfs(काष्ठा ice_vsi *vsi);
व्योम ice_sync_arfs_fltrs(काष्ठा ice_pf *pf);
पूर्णांक ice_set_cpu_rx_rmap(काष्ठा ice_vsi *vsi);
व्योम ice_हटाओ_arfs(काष्ठा ice_pf *pf);
व्योम ice_rebuild_arfs(काष्ठा ice_pf *pf);
bool
ice_is_arfs_using_perfect_flow(काष्ठा ice_hw *hw,
			       क्रमागत ice_fltr_ptype flow_type);
#अन्यथा
#घोषणा ice_sync_arfs_fltrs(pf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_init_arfs(vsi) करो अणुपूर्ण जबतक (0)
#घोषणा ice_clear_arfs(vsi) करो अणुपूर्ण जबतक (0)
#घोषणा ice_हटाओ_arfs(pf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_मुक्त_cpu_rx_rmap(vsi) करो अणुपूर्ण जबतक (0)
#घोषणा ice_rebuild_arfs(pf) करो अणुपूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक ice_set_cpu_rx_rmap(काष्ठा ice_vsi __always_unused *vsi)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_rx_flow_steer(काष्ठा net_device __always_unused *netdev,
		  स्थिर काष्ठा sk_buff __always_unused *skb,
		  u16 __always_unused rxq_idx, u32 __always_unused flow_id)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool
ice_is_arfs_using_perfect_flow(काष्ठा ice_hw __always_unused *hw,
			       क्रमागत ice_fltr_ptype __always_unused flow_type)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_RFS_ACCEL */
#पूर्ण_अगर /* _ICE_ARFS_H_ */
