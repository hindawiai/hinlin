<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_PEER_H
#घोषणा ATH11K_PEER_H

काष्ठा ath11k_peer अणु
	काष्ठा list_head list;
	काष्ठा ieee80211_sta *sta;
	पूर्णांक vdev_id;
	u8 addr[ETH_ALEN];
	पूर्णांक peer_id;
	u16 ast_hash;
	u8 pdev_idx;
	u16 hw_peer_id;

	/* रक्षित by ab->data_lock */
	काष्ठा ieee80211_key_conf *keys[WMI_MAX_KEY_INDEX + 1];
	काष्ठा dp_rx_tid rx_tid[IEEE80211_NUM_TIDS + 1];

	/* Info used in MMIC verअगरication of
	 * RX fragments
	 */
	काष्ठा crypto_shash *tfm_mmic;
	u8 mcast_keyidx;
	u8 ucast_keyidx;
	u16 sec_type;
	u16 sec_type_grp;
पूर्ण;

व्योम ath11k_peer_unmap_event(काष्ठा ath11k_base *ab, u16 peer_id);
व्योम ath11k_peer_map_event(काष्ठा ath11k_base *ab, u8 vdev_id, u16 peer_id,
			   u8 *mac_addr, u16 ast_hash, u16 hw_peer_id);
काष्ठा ath11k_peer *ath11k_peer_find(काष्ठा ath11k_base *ab, पूर्णांक vdev_id,
				     स्थिर u8 *addr);
काष्ठा ath11k_peer *ath11k_peer_find_by_addr(काष्ठा ath11k_base *ab,
					     स्थिर u8 *addr);
काष्ठा ath11k_peer *ath11k_peer_find_by_id(काष्ठा ath11k_base *ab, पूर्णांक peer_id);
व्योम ath11k_peer_cleanup(काष्ठा ath11k *ar, u32 vdev_id);
पूर्णांक ath11k_peer_delete(काष्ठा ath11k *ar, u32 vdev_id, u8 *addr);
पूर्णांक ath11k_peer_create(काष्ठा ath11k *ar, काष्ठा ath11k_vअगर *arvअगर,
		       काष्ठा ieee80211_sta *sta, काष्ठा peer_create_params *param);
पूर्णांक ath11k_रुको_क्रम_peer_delete_करोne(काष्ठा ath11k *ar, u32 vdev_id,
				     स्थिर u8 *addr);
काष्ठा ath11k_peer *ath11k_peer_find_by_vdev_id(काष्ठा ath11k_base *ab,
						पूर्णांक vdev_id);

#पूर्ण_अगर /* _PEER_H_ */
