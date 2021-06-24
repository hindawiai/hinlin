<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश "core.h"
#समावेश "peer.h"
#समावेश "debug.h"

काष्ठा ath11k_peer *ath11k_peer_find(काष्ठा ath11k_base *ab, पूर्णांक vdev_id,
				     स्थिर u8 *addr)
अणु
	काष्ठा ath11k_peer *peer;

	lockdep_निश्चित_held(&ab->base_lock);

	list_क्रम_each_entry(peer, &ab->peers, list) अणु
		अगर (peer->vdev_id != vdev_id)
			जारी;
		अगर (!ether_addr_equal(peer->addr, addr))
			जारी;

		वापस peer;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा ath11k_peer *ath11k_peer_find_by_pdev_idx(काष्ठा ath11k_base *ab,
							u8 pdev_idx, स्थिर u8 *addr)
अणु
	काष्ठा ath11k_peer *peer;

	lockdep_निश्चित_held(&ab->base_lock);

	list_क्रम_each_entry(peer, &ab->peers, list) अणु
		अगर (peer->pdev_idx != pdev_idx)
			जारी;
		अगर (!ether_addr_equal(peer->addr, addr))
			जारी;

		वापस peer;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ath11k_peer *ath11k_peer_find_by_addr(काष्ठा ath11k_base *ab,
					     स्थिर u8 *addr)
अणु
	काष्ठा ath11k_peer *peer;

	lockdep_निश्चित_held(&ab->base_lock);

	list_क्रम_each_entry(peer, &ab->peers, list) अणु
		अगर (!ether_addr_equal(peer->addr, addr))
			जारी;

		वापस peer;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ath11k_peer *ath11k_peer_find_by_id(काष्ठा ath11k_base *ab,
					   पूर्णांक peer_id)
अणु
	काष्ठा ath11k_peer *peer;

	lockdep_निश्चित_held(&ab->base_lock);

	list_क्रम_each_entry(peer, &ab->peers, list)
		अगर (peer_id == peer->peer_id)
			वापस peer;

	वापस शून्य;
पूर्ण

काष्ठा ath11k_peer *ath11k_peer_find_by_vdev_id(काष्ठा ath11k_base *ab,
						पूर्णांक vdev_id)
अणु
	काष्ठा ath11k_peer *peer;

	spin_lock_bh(&ab->base_lock);

	list_क्रम_each_entry(peer, &ab->peers, list) अणु
		अगर (vdev_id == peer->vdev_id) अणु
			spin_unlock_bh(&ab->base_lock);
			वापस peer;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ab->base_lock);
	वापस शून्य;
पूर्ण

व्योम ath11k_peer_unmap_event(काष्ठा ath11k_base *ab, u16 peer_id)
अणु
	काष्ठा ath11k_peer *peer;

	spin_lock_bh(&ab->base_lock);

	peer = ath11k_peer_find_by_id(ab, peer_id);
	अगर (!peer) अणु
		ath11k_warn(ab, "peer-unmap-event: unknown peer id %d\n",
			    peer_id);
		जाओ निकास;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_DP_HTT, "htt peer unmap vdev %d peer %pM id %d\n",
		   peer->vdev_id, peer->addr, peer_id);

	list_del(&peer->list);
	kमुक्त(peer);
	wake_up(&ab->peer_mapping_wq);

निकास:
	spin_unlock_bh(&ab->base_lock);
पूर्ण

व्योम ath11k_peer_map_event(काष्ठा ath11k_base *ab, u8 vdev_id, u16 peer_id,
			   u8 *mac_addr, u16 ast_hash, u16 hw_peer_id)
अणु
	काष्ठा ath11k_peer *peer;

	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find(ab, vdev_id, mac_addr);
	अगर (!peer) अणु
		peer = kzalloc(माप(*peer), GFP_ATOMIC);
		अगर (!peer)
			जाओ निकास;

		peer->vdev_id = vdev_id;
		peer->peer_id = peer_id;
		peer->ast_hash = ast_hash;
		peer->hw_peer_id = hw_peer_id;
		ether_addr_copy(peer->addr, mac_addr);
		list_add(&peer->list, &ab->peers);
		wake_up(&ab->peer_mapping_wq);
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_DP_HTT, "htt peer map vdev %d peer %pM id %d\n",
		   vdev_id, mac_addr, peer_id);

निकास:
	spin_unlock_bh(&ab->base_lock);
पूर्ण

अटल पूर्णांक ath11k_रुको_क्रम_peer_common(काष्ठा ath11k_base *ab, पूर्णांक vdev_id,
				       स्थिर u8 *addr, bool expect_mapped)
अणु
	पूर्णांक ret;

	ret = रुको_event_समयout(ab->peer_mapping_wq, (अणु
				bool mapped;

				spin_lock_bh(&ab->base_lock);
				mapped = !!ath11k_peer_find(ab, vdev_id, addr);
				spin_unlock_bh(&ab->base_lock);

				(mapped == expect_mapped ||
				 test_bit(ATH11K_FLAG_CRASH_FLUSH, &ab->dev_flags));
				पूर्ण), 3 * HZ);

	अगर (ret <= 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

व्योम ath11k_peer_cleanup(काष्ठा ath11k *ar, u32 vdev_id)
अणु
	काष्ठा ath11k_peer *peer, *पंचांगp;
	काष्ठा ath11k_base *ab = ar->ab;

	lockdep_निश्चित_held(&ar->conf_mutex);

	spin_lock_bh(&ab->base_lock);
	list_क्रम_each_entry_safe(peer, पंचांगp, &ab->peers, list) अणु
		अगर (peer->vdev_id != vdev_id)
			जारी;

		ath11k_warn(ab, "removing stale peer %pM from vdev_id %d\n",
			    peer->addr, vdev_id);

		list_del(&peer->list);
		kमुक्त(peer);
		ar->num_peers--;
	पूर्ण

	spin_unlock_bh(&ab->base_lock);
पूर्ण

अटल पूर्णांक ath11k_रुको_क्रम_peer_deleted(काष्ठा ath11k *ar, पूर्णांक vdev_id, स्थिर u8 *addr)
अणु
	वापस ath11k_रुको_क्रम_peer_common(ar->ab, vdev_id, addr, false);
पूर्ण

पूर्णांक ath11k_रुको_क्रम_peer_delete_करोne(काष्ठा ath11k *ar, u32 vdev_id,
				     स्थिर u8 *addr)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;

	ret = ath11k_रुको_क्रम_peer_deleted(ar, vdev_id, addr);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed wait for peer deleted");
		वापस ret;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->peer_delete_करोne,
						3 * HZ);
	अगर (समय_left == 0) अणु
		ath11k_warn(ar->ab, "Timeout in receiving peer delete response\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath11k_peer_delete(काष्ठा ath11k *ar, u32 vdev_id, u8 *addr)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->peer_delete_करोne);

	ret = ath11k_wmi_send_peer_delete_cmd(ar, addr, vdev_id);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to delete peer vdev_id %d addr %pM ret %d\n",
			    vdev_id, addr, ret);
		वापस ret;
	पूर्ण

	ret = ath11k_रुको_क्रम_peer_delete_करोne(ar, vdev_id, addr);
	अगर (ret)
		वापस ret;

	ar->num_peers--;

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_रुको_क्रम_peer_created(काष्ठा ath11k *ar, पूर्णांक vdev_id, स्थिर u8 *addr)
अणु
	वापस ath11k_रुको_क्रम_peer_common(ar->ab, vdev_id, addr, true);
पूर्ण

पूर्णांक ath11k_peer_create(काष्ठा ath11k *ar, काष्ठा ath11k_vअगर *arvअगर,
		       काष्ठा ieee80211_sta *sta, काष्ठा peer_create_params *param)
अणु
	काष्ठा ath11k_peer *peer;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (ar->num_peers > (ar->max_num_peers - 1)) अणु
		ath11k_warn(ar->ab,
			    "failed to create peer due to insufficient peer entry resource in firmware\n");
		वापस -ENOBUFS;
	पूर्ण

	spin_lock_bh(&ar->ab->base_lock);
	peer = ath11k_peer_find_by_pdev_idx(ar->ab, ar->pdev_idx, param->peer_addr);
	अगर (peer) अणु
		spin_unlock_bh(&ar->ab->base_lock);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_bh(&ar->ab->base_lock);

	ret = ath11k_wmi_send_peer_create_cmd(ar, param);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send peer create vdev_id %d ret %d\n",
			    param->vdev_id, ret);
		वापस ret;
	पूर्ण

	ret = ath11k_रुको_क्रम_peer_created(ar, param->vdev_id,
					   param->peer_addr);
	अगर (ret)
		वापस ret;

	spin_lock_bh(&ar->ab->base_lock);

	peer = ath11k_peer_find(ar->ab, param->vdev_id, param->peer_addr);
	अगर (!peer) अणु
		spin_unlock_bh(&ar->ab->base_lock);
		ath11k_warn(ar->ab, "failed to find peer %pM on vdev %i after creation\n",
			    param->peer_addr, param->vdev_id);

		reinit_completion(&ar->peer_delete_करोne);

		ret = ath11k_wmi_send_peer_delete_cmd(ar, param->peer_addr,
						      param->vdev_id);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to delete peer vdev_id %d addr %pM\n",
				    param->vdev_id, param->peer_addr);
			वापस ret;
		पूर्ण

		ret = ath11k_रुको_क्रम_peer_delete_करोne(ar, param->vdev_id,
						       param->peer_addr);
		अगर (ret)
			वापस ret;

		वापस -ENOENT;
	पूर्ण

	peer->pdev_idx = ar->pdev_idx;
	peer->sta = sta;

	अगर (arvअगर->vअगर->type == NL80211_IFTYPE_STATION) अणु
		arvअगर->ast_hash = peer->ast_hash;
		arvअगर->ast_idx = peer->hw_peer_id;
	पूर्ण

	peer->sec_type = HAL_ENCRYPT_TYPE_OPEN;
	peer->sec_type_grp = HAL_ENCRYPT_TYPE_OPEN;

	ar->num_peers++;

	spin_unlock_bh(&ar->ab->base_lock);

	वापस 0;
पूर्ण
