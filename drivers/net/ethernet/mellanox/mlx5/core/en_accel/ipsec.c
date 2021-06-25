<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <crypto/पूर्णांकernal/geniv.h>
#समावेश <crypto/aead.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>

#समावेश "en.h"
#समावेश "en_accel/ipsec.h"
#समावेश "en_accel/ipsec_rxtx.h"
#समावेश "en_accel/ipsec_fs.h"

अटल काष्ठा mlx5e_ipsec_sa_entry *to_ipsec_sa_entry(काष्ठा xfrm_state *x)
अणु
	काष्ठा mlx5e_ipsec_sa_entry *sa;

	अगर (!x)
		वापस शून्य;

	sa = (काष्ठा mlx5e_ipsec_sa_entry *)x->xso.offload_handle;
	अगर (!sa)
		वापस शून्य;

	WARN_ON(sa->x != x);
	वापस sa;
पूर्ण

काष्ठा xfrm_state *mlx5e_ipsec_sadb_rx_lookup(काष्ठा mlx5e_ipsec *ipsec,
					      अचिन्हित पूर्णांक handle)
अणु
	काष्ठा mlx5e_ipsec_sa_entry *sa_entry;
	काष्ठा xfrm_state *ret = शून्य;

	rcu_पढ़ो_lock();
	hash_क्रम_each_possible_rcu(ipsec->sadb_rx, sa_entry, hlist, handle)
		अगर (sa_entry->handle == handle) अणु
			ret = sa_entry->x;
			xfrm_state_hold(ret);
			अवरोध;
		पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक  mlx5e_ipsec_sadb_rx_add(काष्ठा mlx5e_ipsec_sa_entry *sa_entry,
				    अचिन्हित पूर्णांक handle)
अणु
	काष्ठा mlx5e_ipsec *ipsec = sa_entry->ipsec;
	काष्ठा mlx5e_ipsec_sa_entry *_sa_entry;
	अचिन्हित दीर्घ flags;

	rcu_पढ़ो_lock();
	hash_क्रम_each_possible_rcu(ipsec->sadb_rx, _sa_entry, hlist, handle)
		अगर (_sa_entry->handle == handle) अणु
			rcu_पढ़ो_unlock();
			वापस  -EEXIST;
		पूर्ण
	rcu_पढ़ो_unlock();

	spin_lock_irqsave(&ipsec->sadb_rx_lock, flags);
	sa_entry->handle = handle;
	hash_add_rcu(ipsec->sadb_rx, &sa_entry->hlist, sa_entry->handle);
	spin_unlock_irqrestore(&ipsec->sadb_rx_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम mlx5e_ipsec_sadb_rx_del(काष्ठा mlx5e_ipsec_sa_entry *sa_entry)
अणु
	काष्ठा mlx5e_ipsec *ipsec = sa_entry->ipsec;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipsec->sadb_rx_lock, flags);
	hash_del_rcu(&sa_entry->hlist);
	spin_unlock_irqrestore(&ipsec->sadb_rx_lock, flags);
पूर्ण

अटल bool mlx5e_ipsec_update_esn_state(काष्ठा mlx5e_ipsec_sa_entry *sa_entry)
अणु
	काष्ठा xfrm_replay_state_esn *replay_esn;
	u32 seq_bottom = 0;
	u8 overlap;
	u32 *esn;

	अगर (!(sa_entry->x->props.flags & XFRM_STATE_ESN)) अणु
		sa_entry->esn_state.trigger = 0;
		वापस false;
	पूर्ण

	replay_esn = sa_entry->x->replay_esn;
	अगर (replay_esn->seq >= replay_esn->replay_winकरोw)
		seq_bottom = replay_esn->seq - replay_esn->replay_winकरोw + 1;

	overlap = sa_entry->esn_state.overlap;

	sa_entry->esn_state.esn = xfrm_replay_seqhi(sa_entry->x,
						    htonl(seq_bottom));
	esn = &sa_entry->esn_state.esn;

	sa_entry->esn_state.trigger = 1;
	अगर (unlikely(overlap && seq_bottom < MLX5E_IPSEC_ESN_SCOPE_MID)) अणु
		++(*esn);
		sa_entry->esn_state.overlap = 0;
		वापस true;
	पूर्ण अन्यथा अगर (unlikely(!overlap &&
			    (seq_bottom >= MLX5E_IPSEC_ESN_SCOPE_MID))) अणु
		sa_entry->esn_state.overlap = 1;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम
mlx5e_ipsec_build_accel_xfrm_attrs(काष्ठा mlx5e_ipsec_sa_entry *sa_entry,
				   काष्ठा mlx5_accel_esp_xfrm_attrs *attrs)
अणु
	काष्ठा xfrm_state *x = sa_entry->x;
	काष्ठा aes_gcm_keymat *aes_gcm = &attrs->keymat.aes_gcm;
	काष्ठा aead_geniv_ctx *geniv_ctx;
	काष्ठा crypto_aead *aead;
	अचिन्हित पूर्णांक crypto_data_len, key_len;
	पूर्णांक ivsize;

	स_रखो(attrs, 0, माप(*attrs));

	/* key */
	crypto_data_len = (x->aead->alg_key_len + 7) / 8;
	key_len = crypto_data_len - 4; /* 4 bytes salt at end */

	स_नकल(aes_gcm->aes_key, x->aead->alg_key, key_len);
	aes_gcm->key_len = key_len * 8;

	/* salt and seq_iv */
	aead = x->data;
	geniv_ctx = crypto_aead_ctx(aead);
	ivsize = crypto_aead_ivsize(aead);
	स_नकल(&aes_gcm->seq_iv, &geniv_ctx->salt, ivsize);
	स_नकल(&aes_gcm->salt, x->aead->alg_key + key_len,
	       माप(aes_gcm->salt));

	/* iv len */
	aes_gcm->icv_len = x->aead->alg_icv_len;

	/* esn */
	अगर (sa_entry->esn_state.trigger) अणु
		attrs->flags |= MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED;
		attrs->esn = sa_entry->esn_state.esn;
		अगर (sa_entry->esn_state.overlap)
			attrs->flags |= MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP;
	पूर्ण

	/* rx handle */
	attrs->sa_handle = sa_entry->handle;

	/* algo type */
	attrs->keymat_type = MLX5_ACCEL_ESP_KEYMAT_AES_GCM;

	/* action */
	attrs->action = (!(x->xso.flags & XFRM_OFFLOAD_INBOUND)) ?
			MLX5_ACCEL_ESP_ACTION_ENCRYPT :
			MLX5_ACCEL_ESP_ACTION_DECRYPT;
	/* flags */
	attrs->flags |= (x->props.mode == XFRM_MODE_TRANSPORT) ?
			MLX5_ACCEL_ESP_FLAGS_TRANSPORT :
			MLX5_ACCEL_ESP_FLAGS_TUNNEL;

	/* spi */
	attrs->spi = x->id.spi;

	/* source , destination ips */
	स_नकल(&attrs->saddr, x->props.saddr.a6, माप(attrs->saddr));
	स_नकल(&attrs->daddr, x->id.daddr.a6, माप(attrs->daddr));
	attrs->is_ipv6 = (x->props.family != AF_INET);
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_xfrm_validate_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा net_device *netdev = x->xso.real_dev;
	काष्ठा mlx5e_priv *priv;

	priv = netdev_priv(netdev);

	अगर (x->props.aalgo != SADB_AALG_NONE) अणु
		netdev_info(netdev, "Cannot offload authenticated xfrm states\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.ealgo != SADB_X_EALG_AES_GCM_ICV16) अणु
		netdev_info(netdev, "Only AES-GCM-ICV16 xfrm state may be offloaded\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.calgo != SADB_X_CALG_NONE) अणु
		netdev_info(netdev, "Cannot offload compressed xfrm states\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.flags & XFRM_STATE_ESN &&
	    !(mlx5_accel_ipsec_device_caps(priv->mdev) &
	    MLX5_ACCEL_IPSEC_CAP_ESN)) अणु
		netdev_info(netdev, "Cannot offload ESN xfrm states\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.family != AF_INET &&
	    x->props.family != AF_INET6) अणु
		netdev_info(netdev, "Only IPv4/6 xfrm states may be offloaded\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.mode != XFRM_MODE_TRANSPORT &&
	    x->props.mode != XFRM_MODE_TUNNEL) अणु
		dev_info(&netdev->dev, "Only transport and tunnel xfrm states may be offloaded\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->id.proto != IPPROTO_ESP) अणु
		netdev_info(netdev, "Only ESP xfrm state may be offloaded\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->encap) अणु
		netdev_info(netdev, "Encapsulated xfrm state may not be offloaded\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!x->aead) अणु
		netdev_info(netdev, "Cannot offload xfrm states without aead\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->aead->alg_icv_len != 128) अणु
		netdev_info(netdev, "Cannot offload xfrm states with AEAD ICV length other than 128bit\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((x->aead->alg_key_len != 128 + 32) &&
	    (x->aead->alg_key_len != 256 + 32)) अणु
		netdev_info(netdev, "Cannot offload xfrm states with AEAD key length other than 128/256 bit\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->tfcpad) अणु
		netdev_info(netdev, "Cannot offload xfrm states with tfc padding\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!x->geniv) अणु
		netdev_info(netdev, "Cannot offload xfrm states without geniv\n");
		वापस -EINVAL;
	पूर्ण
	अगर (म_भेद(x->geniv, "seqiv")) अणु
		netdev_info(netdev, "Cannot offload xfrm states with geniv other than seqiv\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.family == AF_INET6 &&
	    !(mlx5_accel_ipsec_device_caps(priv->mdev) &
	     MLX5_ACCEL_IPSEC_CAP_IPV6)) अणु
		netdev_info(netdev, "IPv6 xfrm state offload is not supported by this device\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_xfrm_fs_add_rule(काष्ठा mlx5e_priv *priv,
				  काष्ठा mlx5e_ipsec_sa_entry *sa_entry)
अणु
	अगर (!mlx5_is_ipsec_device(priv->mdev))
		वापस 0;

	वापस mlx5e_accel_ipsec_fs_add_rule(priv, &sa_entry->xfrm->attrs,
					     sa_entry->ipsec_obj_id,
					     &sa_entry->ipsec_rule);
पूर्ण

अटल व्योम mlx5e_xfrm_fs_del_rule(काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5e_ipsec_sa_entry *sa_entry)
अणु
	अगर (!mlx5_is_ipsec_device(priv->mdev))
		वापस;

	mlx5e_accel_ipsec_fs_del_rule(priv, &sa_entry->xfrm->attrs,
				      &sa_entry->ipsec_rule);
पूर्ण

अटल पूर्णांक mlx5e_xfrm_add_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा mlx5e_ipsec_sa_entry *sa_entry = शून्य;
	काष्ठा net_device *netdev = x->xso.real_dev;
	काष्ठा mlx5_accel_esp_xfrm_attrs attrs;
	काष्ठा mlx5e_priv *priv;
	अचिन्हित पूर्णांक sa_handle;
	पूर्णांक err;

	priv = netdev_priv(netdev);

	err = mlx5e_xfrm_validate_state(x);
	अगर (err)
		वापस err;

	sa_entry = kzalloc(माप(*sa_entry), GFP_KERNEL);
	अगर (!sa_entry) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	sa_entry->x = x;
	sa_entry->ipsec = priv->ipsec;

	/* check esn */
	mlx5e_ipsec_update_esn_state(sa_entry);

	/* create xfrm */
	mlx5e_ipsec_build_accel_xfrm_attrs(sa_entry, &attrs);
	sa_entry->xfrm =
		mlx5_accel_esp_create_xfrm(priv->mdev, &attrs,
					   MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA);
	अगर (IS_ERR(sa_entry->xfrm)) अणु
		err = PTR_ERR(sa_entry->xfrm);
		जाओ err_sa_entry;
	पूर्ण

	/* create hw context */
	sa_entry->hw_context =
			mlx5_accel_esp_create_hw_context(priv->mdev,
							 sa_entry->xfrm,
							 &sa_handle);
	अगर (IS_ERR(sa_entry->hw_context)) अणु
		err = PTR_ERR(sa_entry->hw_context);
		जाओ err_xfrm;
	पूर्ण

	sa_entry->ipsec_obj_id = sa_handle;
	err = mlx5e_xfrm_fs_add_rule(priv, sa_entry);
	अगर (err)
		जाओ err_hw_ctx;

	अगर (x->xso.flags & XFRM_OFFLOAD_INBOUND) अणु
		err = mlx5e_ipsec_sadb_rx_add(sa_entry, sa_handle);
		अगर (err)
			जाओ err_add_rule;
	पूर्ण अन्यथा अणु
		sa_entry->set_iv_op = (x->props.flags & XFRM_STATE_ESN) ?
				mlx5e_ipsec_set_iv_esn : mlx5e_ipsec_set_iv;
	पूर्ण

	x->xso.offload_handle = (अचिन्हित दीर्घ)sa_entry;
	जाओ out;

err_add_rule:
	mlx5e_xfrm_fs_del_rule(priv, sa_entry);
err_hw_ctx:
	mlx5_accel_esp_मुक्त_hw_context(priv->mdev, sa_entry->hw_context);
err_xfrm:
	mlx5_accel_esp_destroy_xfrm(sa_entry->xfrm);
err_sa_entry:
	kमुक्त(sa_entry);

out:
	वापस err;
पूर्ण

अटल व्योम mlx5e_xfrm_del_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा mlx5e_ipsec_sa_entry *sa_entry = to_ipsec_sa_entry(x);

	अगर (!sa_entry)
		वापस;

	अगर (x->xso.flags & XFRM_OFFLOAD_INBOUND)
		mlx5e_ipsec_sadb_rx_del(sa_entry);
पूर्ण

अटल व्योम mlx5e_xfrm_मुक्त_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा mlx5e_ipsec_sa_entry *sa_entry = to_ipsec_sa_entry(x);
	काष्ठा mlx5e_priv *priv = netdev_priv(x->xso.dev);

	अगर (!sa_entry)
		वापस;

	अगर (sa_entry->hw_context) अणु
		flush_workqueue(sa_entry->ipsec->wq);
		mlx5e_xfrm_fs_del_rule(priv, sa_entry);
		mlx5_accel_esp_मुक्त_hw_context(sa_entry->xfrm->mdev, sa_entry->hw_context);
		mlx5_accel_esp_destroy_xfrm(sa_entry->xfrm);
	पूर्ण

	kमुक्त(sa_entry);
पूर्ण

पूर्णांक mlx5e_ipsec_init(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ipsec *ipsec = शून्य;

	अगर (!MLX5_IPSEC_DEV(priv->mdev)) अणु
		netdev_dbg(priv->netdev, "Not an IPSec offload device\n");
		वापस 0;
	पूर्ण

	ipsec = kzalloc(माप(*ipsec), GFP_KERNEL);
	अगर (!ipsec)
		वापस -ENOMEM;

	hash_init(ipsec->sadb_rx);
	spin_lock_init(&ipsec->sadb_rx_lock);
	ida_init(&ipsec->halloc);
	ipsec->en_priv = priv;
	ipsec->en_priv->ipsec = ipsec;
	ipsec->no_trailer = !!(mlx5_accel_ipsec_device_caps(priv->mdev) &
			       MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER);
	ipsec->wq = alloc_ordered_workqueue("mlx5e_ipsec: %s", 0,
					    priv->netdev->name);
	अगर (!ipsec->wq) अणु
		kमुक्त(ipsec);
		वापस -ENOMEM;
	पूर्ण

	mlx5e_accel_ipsec_fs_init(priv);
	netdev_dbg(priv->netdev, "IPSec attached to netdevice\n");
	वापस 0;
पूर्ण

व्योम mlx5e_ipsec_cleanup(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ipsec *ipsec = priv->ipsec;

	अगर (!ipsec)
		वापस;

	mlx5e_accel_ipsec_fs_cleanup(priv);
	destroy_workqueue(ipsec->wq);

	ida_destroy(&ipsec->halloc);
	kमुक्त(ipsec);
	priv->ipsec = शून्य;
पूर्ण

अटल bool mlx5e_ipsec_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x)
अणु
	अगर (x->props.family == AF_INET) अणु
		/* Offload with IPv4 options is not supported yet */
		अगर (ip_hdr(skb)->ihl > 5)
			वापस false;
	पूर्ण अन्यथा अणु
		/* Offload with IPv6 extension headers is not support yet */
		अगर (ipv6_ext_hdr(ipv6_hdr(skb)->nexthdr))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा mlx5e_ipsec_modअगरy_state_work अणु
	काष्ठा work_काष्ठा		work;
	काष्ठा mlx5_accel_esp_xfrm_attrs attrs;
	काष्ठा mlx5e_ipsec_sa_entry	*sa_entry;
पूर्ण;

अटल व्योम _update_xfrm_state(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा mlx5e_ipsec_modअगरy_state_work *modअगरy_work =
		container_of(work, काष्ठा mlx5e_ipsec_modअगरy_state_work, work);
	काष्ठा mlx5e_ipsec_sa_entry *sa_entry = modअगरy_work->sa_entry;

	ret = mlx5_accel_esp_modअगरy_xfrm(sa_entry->xfrm,
					 &modअगरy_work->attrs);
	अगर (ret)
		netdev_warn(sa_entry->ipsec->en_priv->netdev,
			    "Not an IPSec offload device\n");

	kमुक्त(modअगरy_work);
पूर्ण

अटल व्योम mlx5e_xfrm_advance_esn_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा mlx5e_ipsec_sa_entry *sa_entry = to_ipsec_sa_entry(x);
	काष्ठा mlx5e_ipsec_modअगरy_state_work *modअगरy_work;
	bool need_update;

	अगर (!sa_entry)
		वापस;

	need_update = mlx5e_ipsec_update_esn_state(sa_entry);
	अगर (!need_update)
		वापस;

	modअगरy_work = kzalloc(माप(*modअगरy_work), GFP_ATOMIC);
	अगर (!modअगरy_work)
		वापस;

	mlx5e_ipsec_build_accel_xfrm_attrs(sa_entry, &modअगरy_work->attrs);
	modअगरy_work->sa_entry = sa_entry;

	INIT_WORK(&modअगरy_work->work, _update_xfrm_state);
	WARN_ON(!queue_work(sa_entry->ipsec->wq, &modअगरy_work->work));
पूर्ण

अटल स्थिर काष्ठा xfrmdev_ops mlx5e_ipsec_xfrmdev_ops = अणु
	.xकरो_dev_state_add	= mlx5e_xfrm_add_state,
	.xकरो_dev_state_delete	= mlx5e_xfrm_del_state,
	.xकरो_dev_state_मुक्त	= mlx5e_xfrm_मुक्त_state,
	.xकरो_dev_offload_ok	= mlx5e_ipsec_offload_ok,
	.xकरो_dev_state_advance_esn = mlx5e_xfrm_advance_esn_state,
पूर्ण;

व्योम mlx5e_ipsec_build_netdev(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा net_device *netdev = priv->netdev;

	अगर (!(mlx5_accel_ipsec_device_caps(mdev) & MLX5_ACCEL_IPSEC_CAP_ESP) ||
	    !MLX5_CAP_ETH(mdev, swp)) अणु
		mlx5_core_dbg(mdev, "mlx5e: ESP and SWP offload not supported\n");
		वापस;
	पूर्ण

	mlx5_core_info(mdev, "mlx5e: IPSec ESP acceleration enabled\n");
	netdev->xfrmdev_ops = &mlx5e_ipsec_xfrmdev_ops;
	netdev->features |= NETIF_F_HW_ESP;
	netdev->hw_enc_features |= NETIF_F_HW_ESP;

	अगर (!MLX5_CAP_ETH(mdev, swp_csum)) अणु
		mlx5_core_dbg(mdev, "mlx5e: SWP checksum not supported\n");
		वापस;
	पूर्ण

	netdev->features |= NETIF_F_HW_ESP_TX_CSUM;
	netdev->hw_enc_features |= NETIF_F_HW_ESP_TX_CSUM;

	अगर (!(mlx5_accel_ipsec_device_caps(mdev) & MLX5_ACCEL_IPSEC_CAP_LSO) ||
	    !MLX5_CAP_ETH(mdev, swp_lso)) अणु
		mlx5_core_dbg(mdev, "mlx5e: ESP LSO not supported\n");
		वापस;
	पूर्ण

	अगर (mlx5_is_ipsec_device(mdev))
		netdev->gso_partial_features |= NETIF_F_GSO_ESP;

	mlx5_core_dbg(mdev, "mlx5e: ESP GSO capability turned on\n");
	netdev->features |= NETIF_F_GSO_ESP;
	netdev->hw_features |= NETIF_F_GSO_ESP;
	netdev->hw_enc_features |= NETIF_F_GSO_ESP;
पूर्ण
