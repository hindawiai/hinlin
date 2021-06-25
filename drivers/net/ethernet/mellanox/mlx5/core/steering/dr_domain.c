<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश <linux/mlx5/eचयन.h>
#समावेश "dr_types.h"

#घोषणा DR_DOMAIN_SW_STEERING_SUPPORTED(dmn, dmn_type)	\
	((dmn)->info.caps.dmn_type##_sw_owner ||	\
	 ((dmn)->info.caps.dmn_type##_sw_owner_v2 &&	\
	  (dmn)->info.caps.sw_क्रमmat_ver <= MLX5_STEERING_FORMAT_CONNECTX_6DX))

अटल पूर्णांक dr_करोमुख्य_init_cache(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	/* Per vport cached FW FT क्रम checksum recalculation, this
	 * recalculation is needed due to a HW bug.
	 */
	dmn->cache.recalc_cs_ft = kसुस्मृति(dmn->info.caps.num_vports,
					  माप(dmn->cache.recalc_cs_ft[0]),
					  GFP_KERNEL);
	अगर (!dmn->cache.recalc_cs_ft)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम dr_करोमुख्य_uninit_cache(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dmn->info.caps.num_vports; i++) अणु
		अगर (!dmn->cache.recalc_cs_ft[i])
			जारी;

		mlx5dr_fw_destroy_recalc_cs_ft(dmn, dmn->cache.recalc_cs_ft[i]);
	पूर्ण

	kमुक्त(dmn->cache.recalc_cs_ft);
पूर्ण

पूर्णांक mlx5dr_करोमुख्य_cache_get_recalc_cs_ft_addr(काष्ठा mlx5dr_करोमुख्य *dmn,
					      u32 vport_num,
					      u64 *rx_icm_addr)
अणु
	काष्ठा mlx5dr_fw_recalc_cs_ft *recalc_cs_ft;

	recalc_cs_ft = dmn->cache.recalc_cs_ft[vport_num];
	अगर (!recalc_cs_ft) अणु
		/* Table not in cache, need to allocate a new one */
		recalc_cs_ft = mlx5dr_fw_create_recalc_cs_ft(dmn, vport_num);
		अगर (!recalc_cs_ft)
			वापस -EINVAL;

		dmn->cache.recalc_cs_ft[vport_num] = recalc_cs_ft;
	पूर्ण

	*rx_icm_addr = recalc_cs_ft->rx_icm_addr;

	वापस 0;
पूर्ण

अटल पूर्णांक dr_करोमुख्य_init_resources(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	पूर्णांक ret;

	dmn->ste_ctx = mlx5dr_ste_get_ctx(dmn->info.caps.sw_क्रमmat_ver);
	अगर (!dmn->ste_ctx) अणु
		mlx5dr_err(dmn, "SW Steering on this device is unsupported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = mlx5_core_alloc_pd(dmn->mdev, &dmn->pdn);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Couldn't allocate PD, ret: %d", ret);
		वापस ret;
	पूर्ण

	dmn->uar = mlx5_get_uars_page(dmn->mdev);
	अगर (!dmn->uar) अणु
		mlx5dr_err(dmn, "Couldn't allocate UAR\n");
		ret = -ENOMEM;
		जाओ clean_pd;
	पूर्ण

	dmn->ste_icm_pool = mlx5dr_icm_pool_create(dmn, DR_ICM_TYPE_STE);
	अगर (!dmn->ste_icm_pool) अणु
		mlx5dr_err(dmn, "Couldn't get icm memory\n");
		ret = -ENOMEM;
		जाओ clean_uar;
	पूर्ण

	dmn->action_icm_pool = mlx5dr_icm_pool_create(dmn, DR_ICM_TYPE_MODIFY_ACTION);
	अगर (!dmn->action_icm_pool) अणु
		mlx5dr_err(dmn, "Couldn't get action icm memory\n");
		ret = -ENOMEM;
		जाओ मुक्त_ste_icm_pool;
	पूर्ण

	ret = mlx5dr_send_ring_alloc(dmn);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Couldn't create send-ring\n");
		जाओ मुक्त_action_icm_pool;
	पूर्ण

	वापस 0;

मुक्त_action_icm_pool:
	mlx5dr_icm_pool_destroy(dmn->action_icm_pool);
मुक्त_ste_icm_pool:
	mlx5dr_icm_pool_destroy(dmn->ste_icm_pool);
clean_uar:
	mlx5_put_uars_page(dmn->mdev, dmn->uar);
clean_pd:
	mlx5_core_dealloc_pd(dmn->mdev, dmn->pdn);

	वापस ret;
पूर्ण

अटल व्योम dr_करोमुख्य_uninit_resources(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	mlx5dr_send_ring_मुक्त(dmn, dmn->send_ring);
	mlx5dr_icm_pool_destroy(dmn->action_icm_pool);
	mlx5dr_icm_pool_destroy(dmn->ste_icm_pool);
	mlx5_put_uars_page(dmn->mdev, dmn->uar);
	mlx5_core_dealloc_pd(dmn->mdev, dmn->pdn);
पूर्ण

अटल पूर्णांक dr_करोमुख्य_query_vport(काष्ठा mlx5dr_करोमुख्य *dmn,
				 bool other_vport,
				 u16 vport_number)
अणु
	काष्ठा mlx5dr_cmd_vport_cap *vport_caps;
	पूर्णांक ret;

	vport_caps = &dmn->info.caps.vports_caps[vport_number];

	ret = mlx5dr_cmd_query_esw_vport_context(dmn->mdev,
						 other_vport,
						 vport_number,
						 &vport_caps->icm_address_rx,
						 &vport_caps->icm_address_tx);
	अगर (ret)
		वापस ret;

	ret = mlx5dr_cmd_query_gvmi(dmn->mdev,
				    other_vport,
				    vport_number,
				    &vport_caps->vport_gvmi);
	अगर (ret)
		वापस ret;

	vport_caps->num = vport_number;
	vport_caps->vhca_gvmi = dmn->info.caps.gvmi;

	वापस 0;
पूर्ण

अटल पूर्णांक dr_करोमुख्य_query_vports(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	काष्ठा mlx5dr_esw_caps *esw_caps = &dmn->info.caps.esw_caps;
	काष्ठा mlx5dr_cmd_vport_cap *wire_vport;
	पूर्णांक vport;
	पूर्णांक ret;

	/* Query vports (except wire vport) */
	क्रम (vport = 0; vport < dmn->info.caps.num_esw_ports - 1; vport++) अणु
		ret = dr_करोमुख्य_query_vport(dmn, !!vport, vport);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Last vport is the wire port */
	wire_vport = &dmn->info.caps.vports_caps[vport];
	wire_vport->num = WIRE_PORT;
	wire_vport->icm_address_rx = esw_caps->uplink_icm_address_rx;
	wire_vport->icm_address_tx = esw_caps->uplink_icm_address_tx;
	wire_vport->vport_gvmi = 0;
	wire_vport->vhca_gvmi = dmn->info.caps.gvmi;

	वापस 0;
पूर्ण

अटल पूर्णांक dr_करोमुख्य_query_fdb_caps(काष्ठा mlx5_core_dev *mdev,
				    काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	पूर्णांक ret;

	अगर (!dmn->info.caps.eचयन_manager)
		वापस -EOPNOTSUPP;

	ret = mlx5dr_cmd_query_esw_caps(mdev, &dmn->info.caps.esw_caps);
	अगर (ret)
		वापस ret;

	dmn->info.caps.fdb_sw_owner = dmn->info.caps.esw_caps.sw_owner;
	dmn->info.caps.fdb_sw_owner_v2 = dmn->info.caps.esw_caps.sw_owner_v2;
	dmn->info.caps.esw_rx_drop_address = dmn->info.caps.esw_caps.drop_icm_address_rx;
	dmn->info.caps.esw_tx_drop_address = dmn->info.caps.esw_caps.drop_icm_address_tx;

	dmn->info.caps.vports_caps = kसुस्मृति(dmn->info.caps.num_esw_ports,
					     माप(dmn->info.caps.vports_caps[0]),
					     GFP_KERNEL);
	अगर (!dmn->info.caps.vports_caps)
		वापस -ENOMEM;

	ret = dr_करोमुख्य_query_vports(dmn);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed to query vports caps (err: %d)", ret);
		जाओ मुक्त_vports_caps;
	पूर्ण

	dmn->info.caps.num_vports = dmn->info.caps.num_esw_ports - 1;

	वापस 0;

मुक्त_vports_caps:
	kमुक्त(dmn->info.caps.vports_caps);
	dmn->info.caps.vports_caps = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक dr_करोमुख्य_caps_init(काष्ठा mlx5_core_dev *mdev,
			       काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	काष्ठा mlx5dr_cmd_vport_cap *vport_cap;
	पूर्णांक ret;

	अगर (MLX5_CAP_GEN(mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH) अणु
		mlx5dr_err(dmn, "Failed to allocate domain, bad link type\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	dmn->info.caps.num_esw_ports = mlx5_eचयन_get_total_vports(mdev);

	ret = mlx5dr_cmd_query_device(mdev, &dmn->info.caps);
	अगर (ret)
		वापस ret;

	ret = dr_करोमुख्य_query_fdb_caps(mdev, dmn);
	अगर (ret)
		वापस ret;

	चयन (dmn->type) अणु
	हाल MLX5DR_DOMAIN_TYPE_NIC_RX:
		अगर (!DR_DOMAIN_SW_STEERING_SUPPORTED(dmn, rx))
			वापस -ENOTSUPP;

		dmn->info.supp_sw_steering = true;
		dmn->info.rx.ste_type = MLX5DR_STE_TYPE_RX;
		dmn->info.rx.शेष_icm_addr = dmn->info.caps.nic_rx_drop_address;
		dmn->info.rx.drop_icm_addr = dmn->info.caps.nic_rx_drop_address;
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_NIC_TX:
		अगर (!DR_DOMAIN_SW_STEERING_SUPPORTED(dmn, tx))
			वापस -ENOTSUPP;

		dmn->info.supp_sw_steering = true;
		dmn->info.tx.ste_type = MLX5DR_STE_TYPE_TX;
		dmn->info.tx.शेष_icm_addr = dmn->info.caps.nic_tx_allow_address;
		dmn->info.tx.drop_icm_addr = dmn->info.caps.nic_tx_drop_address;
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_FDB:
		अगर (!dmn->info.caps.eचयन_manager)
			वापस -ENOTSUPP;

		अगर (!DR_DOMAIN_SW_STEERING_SUPPORTED(dmn, fdb))
			वापस -ENOTSUPP;

		dmn->info.rx.ste_type = MLX5DR_STE_TYPE_RX;
		dmn->info.tx.ste_type = MLX5DR_STE_TYPE_TX;
		vport_cap = mlx5dr_get_vport_cap(&dmn->info.caps, 0);
		अगर (!vport_cap) अणु
			mlx5dr_err(dmn, "Failed to get esw manager vport\n");
			वापस -ENOENT;
		पूर्ण

		dmn->info.supp_sw_steering = true;
		dmn->info.tx.शेष_icm_addr = vport_cap->icm_address_tx;
		dmn->info.rx.शेष_icm_addr = vport_cap->icm_address_rx;
		dmn->info.rx.drop_icm_addr = dmn->info.caps.esw_rx_drop_address;
		dmn->info.tx.drop_icm_addr = dmn->info.caps.esw_tx_drop_address;
		अवरोध;
	शेष:
		mlx5dr_err(dmn, "Invalid domain\n");
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dr_करोमुख्य_caps_uninit(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	kमुक्त(dmn->info.caps.vports_caps);
पूर्ण

काष्ठा mlx5dr_करोमुख्य *
mlx5dr_करोमुख्य_create(काष्ठा mlx5_core_dev *mdev, क्रमागत mlx5dr_करोमुख्य_type type)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn;
	पूर्णांक ret;

	अगर (type > MLX5DR_DOMAIN_TYPE_FDB)
		वापस शून्य;

	dmn = kzalloc(माप(*dmn), GFP_KERNEL);
	अगर (!dmn)
		वापस शून्य;

	dmn->mdev = mdev;
	dmn->type = type;
	refcount_set(&dmn->refcount, 1);
	mutex_init(&dmn->info.rx.mutex);
	mutex_init(&dmn->info.tx.mutex);

	अगर (dr_करोमुख्य_caps_init(mdev, dmn)) अणु
		mlx5dr_err(dmn, "Failed init domain, no caps\n");
		जाओ मुक्त_करोमुख्य;
	पूर्ण

	dmn->info.max_log_action_icm_sz = DR_CHUNK_SIZE_4K;
	dmn->info.max_log_sw_icm_sz = min_t(u32, DR_CHUNK_SIZE_1024K,
					    dmn->info.caps.log_icm_size);

	अगर (!dmn->info.supp_sw_steering) अणु
		mlx5dr_err(dmn, "SW steering is not supported\n");
		जाओ uninit_caps;
	पूर्ण

	/* Allocate resources */
	ret = dr_करोमुख्य_init_resources(dmn);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed init domain resources\n");
		जाओ uninit_caps;
	पूर्ण

	ret = dr_करोमुख्य_init_cache(dmn);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed initialize domain cache\n");
		जाओ uninit_resourses;
	पूर्ण

	वापस dmn;

uninit_resourses:
	dr_करोमुख्य_uninit_resources(dmn);
uninit_caps:
	dr_करोमुख्य_caps_uninit(dmn);
मुक्त_करोमुख्य:
	kमुक्त(dmn);
	वापस शून्य;
पूर्ण

/* Assure synchronization of the device steering tables with updates made by SW
 * insertion.
 */
पूर्णांक mlx5dr_करोमुख्य_sync(काष्ठा mlx5dr_करोमुख्य *dmn, u32 flags)
अणु
	पूर्णांक ret = 0;

	अगर (flags & MLX5DR_DOMAIN_SYNC_FLAGS_SW) अणु
		mlx5dr_करोमुख्य_lock(dmn);
		ret = mlx5dr_send_ring_क्रमce_drain(dmn);
		mlx5dr_करोमुख्य_unlock(dmn);
		अगर (ret) अणु
			mlx5dr_err(dmn, "Force drain failed flags: %d, ret: %d\n",
				   flags, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (flags & MLX5DR_DOMAIN_SYNC_FLAGS_HW)
		ret = mlx5dr_cmd_sync_steering(dmn->mdev);

	वापस ret;
पूर्ण

पूर्णांक mlx5dr_करोमुख्य_destroy(काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	अगर (refcount_पढ़ो(&dmn->refcount) > 1)
		वापस -EBUSY;

	/* make sure resources are not used by the hardware */
	mlx5dr_cmd_sync_steering(dmn->mdev);
	dr_करोमुख्य_uninit_cache(dmn);
	dr_करोमुख्य_uninit_resources(dmn);
	dr_करोमुख्य_caps_uninit(dmn);
	mutex_destroy(&dmn->info.tx.mutex);
	mutex_destroy(&dmn->info.rx.mutex);
	kमुक्त(dmn);
	वापस 0;
पूर्ण

व्योम mlx5dr_करोमुख्य_set_peer(काष्ठा mlx5dr_करोमुख्य *dmn,
			    काष्ठा mlx5dr_करोमुख्य *peer_dmn)
अणु
	mlx5dr_करोमुख्य_lock(dmn);

	अगर (dmn->peer_dmn)
		refcount_dec(&dmn->peer_dmn->refcount);

	dmn->peer_dmn = peer_dmn;

	अगर (dmn->peer_dmn)
		refcount_inc(&dmn->peer_dmn->refcount);

	mlx5dr_करोमुख्य_unlock(dmn);
पूर्ण
