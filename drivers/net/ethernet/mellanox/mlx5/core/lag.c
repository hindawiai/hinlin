<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
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
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/vport.h>
#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "lag.h"
#समावेश "lag_mp.h"

/* General purpose, use क्रम लघु periods of समय.
 * Beware of lock dependencies (preferably, no locks should be acquired
 * under it).
 */
अटल DEFINE_SPINLOCK(lag_lock);

अटल पूर्णांक mlx5_cmd_create_lag(काष्ठा mlx5_core_dev *dev, u8 remap_port1,
			       u8 remap_port2)
अणु
	u32 in[MLX5_ST_SZ_DW(create_lag_in)] = अणुपूर्ण;
	व्योम *lag_ctx = MLX5_ADDR_OF(create_lag_in, in, ctx);

	MLX5_SET(create_lag_in, in, opcode, MLX5_CMD_OP_CREATE_LAG);

	MLX5_SET(lagc, lag_ctx, tx_remap_affinity_1, remap_port1);
	MLX5_SET(lagc, lag_ctx, tx_remap_affinity_2, remap_port2);

	वापस mlx5_cmd_exec_in(dev, create_lag, in);
पूर्ण

अटल पूर्णांक mlx5_cmd_modअगरy_lag(काष्ठा mlx5_core_dev *dev, u8 remap_port1,
			       u8 remap_port2)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_lag_in)] = अणुपूर्ण;
	व्योम *lag_ctx = MLX5_ADDR_OF(modअगरy_lag_in, in, ctx);

	MLX5_SET(modअगरy_lag_in, in, opcode, MLX5_CMD_OP_MODIFY_LAG);
	MLX5_SET(modअगरy_lag_in, in, field_select, 0x1);

	MLX5_SET(lagc, lag_ctx, tx_remap_affinity_1, remap_port1);
	MLX5_SET(lagc, lag_ctx, tx_remap_affinity_2, remap_port2);

	वापस mlx5_cmd_exec_in(dev, modअगरy_lag, in);
पूर्ण

पूर्णांक mlx5_cmd_create_vport_lag(काष्ठा mlx5_core_dev *dev)
अणु
	u32 in[MLX5_ST_SZ_DW(create_vport_lag_in)] = अणुपूर्ण;

	MLX5_SET(create_vport_lag_in, in, opcode, MLX5_CMD_OP_CREATE_VPORT_LAG);

	वापस mlx5_cmd_exec_in(dev, create_vport_lag, in);
पूर्ण
EXPORT_SYMBOL(mlx5_cmd_create_vport_lag);

पूर्णांक mlx5_cmd_destroy_vport_lag(काष्ठा mlx5_core_dev *dev)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_vport_lag_in)] = अणुपूर्ण;

	MLX5_SET(destroy_vport_lag_in, in, opcode, MLX5_CMD_OP_DESTROY_VPORT_LAG);

	वापस mlx5_cmd_exec_in(dev, destroy_vport_lag, in);
पूर्ण
EXPORT_SYMBOL(mlx5_cmd_destroy_vport_lag);

पूर्णांक mlx5_lag_dev_get_netdev_idx(काष्ठा mlx5_lag *ldev,
				काष्ठा net_device *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5_MAX_PORTS; i++)
		अगर (ldev->pf[i].netdev == ndev)
			वापस i;

	वापस -ENOENT;
पूर्ण

अटल bool __mlx5_lag_is_roce(काष्ठा mlx5_lag *ldev)
अणु
	वापस !!(ldev->flags & MLX5_LAG_FLAG_ROCE);
पूर्ण

अटल bool __mlx5_lag_is_sriov(काष्ठा mlx5_lag *ldev)
अणु
	वापस !!(ldev->flags & MLX5_LAG_FLAG_SRIOV);
पूर्ण

अटल व्योम mlx5_infer_tx_affinity_mapping(काष्ठा lag_tracker *tracker,
					   u8 *port1, u8 *port2)
अणु
	*port1 = 1;
	*port2 = 2;
	अगर (!tracker->netdev_state[MLX5_LAG_P1].tx_enabled ||
	    !tracker->netdev_state[MLX5_LAG_P1].link_up) अणु
		*port1 = 2;
		वापस;
	पूर्ण

	अगर (!tracker->netdev_state[MLX5_LAG_P2].tx_enabled ||
	    !tracker->netdev_state[MLX5_LAG_P2].link_up)
		*port2 = 1;
पूर्ण

व्योम mlx5_modअगरy_lag(काष्ठा mlx5_lag *ldev,
		     काष्ठा lag_tracker *tracker)
अणु
	काष्ठा mlx5_core_dev *dev0 = ldev->pf[MLX5_LAG_P1].dev;
	u8 v2p_port1, v2p_port2;
	पूर्णांक err;

	mlx5_infer_tx_affinity_mapping(tracker, &v2p_port1,
				       &v2p_port2);

	अगर (v2p_port1 != ldev->v2p_map[MLX5_LAG_P1] ||
	    v2p_port2 != ldev->v2p_map[MLX5_LAG_P2]) अणु
		ldev->v2p_map[MLX5_LAG_P1] = v2p_port1;
		ldev->v2p_map[MLX5_LAG_P2] = v2p_port2;

		mlx5_core_info(dev0, "modify lag map port 1:%d port 2:%d",
			       ldev->v2p_map[MLX5_LAG_P1],
			       ldev->v2p_map[MLX5_LAG_P2]);

		err = mlx5_cmd_modअगरy_lag(dev0, v2p_port1, v2p_port2);
		अगर (err)
			mlx5_core_err(dev0,
				      "Failed to modify LAG (%d)\n",
				      err);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_create_lag(काष्ठा mlx5_lag *ldev,
			   काष्ठा lag_tracker *tracker)
अणु
	काष्ठा mlx5_core_dev *dev0 = ldev->pf[MLX5_LAG_P1].dev;
	पूर्णांक err;

	mlx5_infer_tx_affinity_mapping(tracker, &ldev->v2p_map[MLX5_LAG_P1],
				       &ldev->v2p_map[MLX5_LAG_P2]);

	mlx5_core_info(dev0, "lag map port 1:%d port 2:%d",
		       ldev->v2p_map[MLX5_LAG_P1], ldev->v2p_map[MLX5_LAG_P2]);

	err = mlx5_cmd_create_lag(dev0, ldev->v2p_map[MLX5_LAG_P1],
				  ldev->v2p_map[MLX5_LAG_P2]);
	अगर (err)
		mlx5_core_err(dev0,
			      "Failed to create LAG (%d)\n",
			      err);
	वापस err;
पूर्ण

पूर्णांक mlx5_activate_lag(काष्ठा mlx5_lag *ldev,
		      काष्ठा lag_tracker *tracker,
		      u8 flags)
अणु
	bool roce_lag = !!(flags & MLX5_LAG_FLAG_ROCE);
	काष्ठा mlx5_core_dev *dev0 = ldev->pf[MLX5_LAG_P1].dev;
	पूर्णांक err;

	err = mlx5_create_lag(ldev, tracker);
	अगर (err) अणु
		अगर (roce_lag) अणु
			mlx5_core_err(dev0,
				      "Failed to activate RoCE LAG\n");
		पूर्ण अन्यथा अणु
			mlx5_core_err(dev0,
				      "Failed to activate VF LAG\n"
				      "Make sure all VFs are unbound prior to VF LAG activation or deactivation\n");
		पूर्ण
		वापस err;
	पूर्ण

	ldev->flags |= flags;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_deactivate_lag(काष्ठा mlx5_lag *ldev)
अणु
	काष्ठा mlx5_core_dev *dev0 = ldev->pf[MLX5_LAG_P1].dev;
	u32 in[MLX5_ST_SZ_DW(destroy_lag_in)] = अणुपूर्ण;
	bool roce_lag = __mlx5_lag_is_roce(ldev);
	पूर्णांक err;

	ldev->flags &= ~MLX5_LAG_MODE_FLAGS;

	MLX5_SET(destroy_lag_in, in, opcode, MLX5_CMD_OP_DESTROY_LAG);
	err = mlx5_cmd_exec_in(dev0, destroy_lag, in);
	अगर (err) अणु
		अगर (roce_lag) अणु
			mlx5_core_err(dev0,
				      "Failed to deactivate RoCE LAG; driver restart required\n");
		पूर्ण अन्यथा अणु
			mlx5_core_err(dev0,
				      "Failed to deactivate VF LAG; driver restart required\n"
				      "Make sure all VFs are unbound prior to VF LAG activation or deactivation\n");
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल bool mlx5_lag_check_prereq(काष्ठा mlx5_lag *ldev)
अणु
	अगर (!ldev->pf[MLX5_LAG_P1].dev || !ldev->pf[MLX5_LAG_P2].dev)
		वापस false;

#अगर_घोषित CONFIG_MLX5_ESWITCH
	वापस mlx5_esw_lag_prereq(ldev->pf[MLX5_LAG_P1].dev,
				   ldev->pf[MLX5_LAG_P2].dev);
#अन्यथा
	वापस (!mlx5_sriov_is_enabled(ldev->pf[MLX5_LAG_P1].dev) &&
		!mlx5_sriov_is_enabled(ldev->pf[MLX5_LAG_P2].dev));
#पूर्ण_अगर
पूर्ण

अटल व्योम mlx5_lag_add_devices(काष्ठा mlx5_lag *ldev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5_MAX_PORTS; i++) अणु
		अगर (!ldev->pf[i].dev)
			जारी;

		ldev->pf[i].dev->priv.flags &= ~MLX5_PRIV_FLAGS_DISABLE_IB_ADEV;
		mlx5_rescan_drivers_locked(ldev->pf[i].dev);
	पूर्ण
पूर्ण

अटल व्योम mlx5_lag_हटाओ_devices(काष्ठा mlx5_lag *ldev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5_MAX_PORTS; i++) अणु
		अगर (!ldev->pf[i].dev)
			जारी;

		ldev->pf[i].dev->priv.flags |= MLX5_PRIV_FLAGS_DISABLE_IB_ADEV;
		mlx5_rescan_drivers_locked(ldev->pf[i].dev);
	पूर्ण
पूर्ण

अटल व्योम mlx5_करो_bond(काष्ठा mlx5_lag *ldev)
अणु
	काष्ठा mlx5_core_dev *dev0 = ldev->pf[MLX5_LAG_P1].dev;
	काष्ठा mlx5_core_dev *dev1 = ldev->pf[MLX5_LAG_P2].dev;
	काष्ठा lag_tracker tracker;
	bool करो_bond, roce_lag;
	पूर्णांक err;

	अगर (!mlx5_lag_is_पढ़ोy(ldev))
		वापस;

	spin_lock(&lag_lock);
	tracker = ldev->tracker;
	spin_unlock(&lag_lock);

	करो_bond = tracker.is_bonded && mlx5_lag_check_prereq(ldev);

	अगर (करो_bond && !__mlx5_lag_is_active(ldev)) अणु
		roce_lag = !mlx5_sriov_is_enabled(dev0) &&
			   !mlx5_sriov_is_enabled(dev1);

#अगर_घोषित CONFIG_MLX5_ESWITCH
		roce_lag &= dev0->priv.eचयन->mode == MLX5_ESWITCH_NONE &&
			    dev1->priv.eचयन->mode == MLX5_ESWITCH_NONE;
#पूर्ण_अगर

		अगर (roce_lag)
			mlx5_lag_हटाओ_devices(ldev);

		err = mlx5_activate_lag(ldev, &tracker,
					roce_lag ? MLX5_LAG_FLAG_ROCE :
					MLX5_LAG_FLAG_SRIOV);
		अगर (err) अणु
			अगर (roce_lag)
				mlx5_lag_add_devices(ldev);

			वापस;
		पूर्ण

		अगर (roce_lag) अणु
			dev0->priv.flags &= ~MLX5_PRIV_FLAGS_DISABLE_IB_ADEV;
			mlx5_rescan_drivers_locked(dev0);
			mlx5_nic_vport_enable_roce(dev1);
		पूर्ण
	पूर्ण अन्यथा अगर (करो_bond && __mlx5_lag_is_active(ldev)) अणु
		mlx5_modअगरy_lag(ldev, &tracker);
	पूर्ण अन्यथा अगर (!करो_bond && __mlx5_lag_is_active(ldev)) अणु
		roce_lag = __mlx5_lag_is_roce(ldev);

		अगर (roce_lag) अणु
			dev0->priv.flags |= MLX5_PRIV_FLAGS_DISABLE_IB_ADEV;
			mlx5_rescan_drivers_locked(dev0);
			mlx5_nic_vport_disable_roce(dev1);
		पूर्ण

		err = mlx5_deactivate_lag(ldev);
		अगर (err)
			वापस;

		अगर (roce_lag)
			mlx5_lag_add_devices(ldev);
	पूर्ण
पूर्ण

अटल व्योम mlx5_queue_bond_work(काष्ठा mlx5_lag *ldev, अचिन्हित दीर्घ delay)
अणु
	queue_delayed_work(ldev->wq, &ldev->bond_work, delay);
पूर्ण

अटल व्योम mlx5_करो_bond_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा mlx5_lag *ldev = container_of(delayed_work, काष्ठा mlx5_lag,
					     bond_work);
	पूर्णांक status;

	status = mlx5_dev_list_trylock();
	अगर (!status) अणु
		/* 1 sec delay. */
		mlx5_queue_bond_work(ldev, HZ);
		वापस;
	पूर्ण

	mlx5_करो_bond(ldev);
	mlx5_dev_list_unlock();
पूर्ण

अटल पूर्णांक mlx5_handle_changeupper_event(काष्ठा mlx5_lag *ldev,
					 काष्ठा lag_tracker *tracker,
					 काष्ठा net_device *ndev,
					 काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा net_device *upper = info->upper_dev, *ndev_पंचांगp;
	काष्ठा netdev_lag_upper_info *lag_upper_info = शून्य;
	bool is_bonded, is_in_lag, mode_supported;
	पूर्णांक bond_status = 0;
	पूर्णांक num_slaves = 0;
	पूर्णांक idx;

	अगर (!netअगर_is_lag_master(upper))
		वापस 0;

	अगर (info->linking)
		lag_upper_info = info->upper_info;

	/* The event may still be of पूर्णांकerest अगर the slave करोes not beदीर्घ to
	 * us, but is enslaved to a master which has one or more of our netdevs
	 * as slaves (e.g., अगर a new slave is added to a master that bonds two
	 * of our netdevs, we should unbond).
	 */
	rcu_पढ़ो_lock();
	क्रम_each_netdev_in_bond_rcu(upper, ndev_पंचांगp) अणु
		idx = mlx5_lag_dev_get_netdev_idx(ldev, ndev_पंचांगp);
		अगर (idx >= 0)
			bond_status |= (1 << idx);

		num_slaves++;
	पूर्ण
	rcu_पढ़ो_unlock();

	/* None of this lagdev's netdevs are slaves of this master. */
	अगर (!(bond_status & 0x3))
		वापस 0;

	अगर (lag_upper_info)
		tracker->tx_type = lag_upper_info->tx_type;

	/* Determine bonding status:
	 * A device is considered bonded अगर both its physical ports are slaves
	 * of the same lag master, and only them.
	 */
	is_in_lag = num_slaves == MLX5_MAX_PORTS && bond_status == 0x3;

	अगर (!mlx5_lag_is_पढ़ोy(ldev) && is_in_lag) अणु
		NL_SET_ERR_MSG_MOD(info->info.extack,
				   "Can't activate LAG offload, PF is configured with more than 64 VFs");
		वापस 0;
	पूर्ण

	/* Lag mode must be activebackup or hash. */
	mode_supported = tracker->tx_type == NETDEV_LAG_TX_TYPE_ACTIVEBACKUP ||
			 tracker->tx_type == NETDEV_LAG_TX_TYPE_HASH;

	अगर (is_in_lag && !mode_supported)
		NL_SET_ERR_MSG_MOD(info->info.extack,
				   "Can't activate LAG offload, TX type isn't supported");

	is_bonded = is_in_lag && mode_supported;
	अगर (tracker->is_bonded != is_bonded) अणु
		tracker->is_bonded = is_bonded;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_handle_changelowerstate_event(काष्ठा mlx5_lag *ldev,
					      काष्ठा lag_tracker *tracker,
					      काष्ठा net_device *ndev,
					      काष्ठा netdev_notअगरier_changelowerstate_info *info)
अणु
	काष्ठा netdev_lag_lower_state_info *lag_lower_info;
	पूर्णांक idx;

	अगर (!netअगर_is_lag_port(ndev))
		वापस 0;

	idx = mlx5_lag_dev_get_netdev_idx(ldev, ndev);
	अगर (idx < 0)
		वापस 0;

	/* This inक्रमmation is used to determine भव to physical
	 * port mapping.
	 */
	lag_lower_info = info->lower_state_info;
	अगर (!lag_lower_info)
		वापस 0;

	tracker->netdev_state[idx] = *lag_lower_info;

	वापस 1;
पूर्ण

अटल पूर्णांक mlx5_lag_netdev_event(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा lag_tracker tracker;
	काष्ठा mlx5_lag *ldev;
	पूर्णांक changed = 0;

	अगर ((event != NETDEV_CHANGEUPPER) && (event != NETDEV_CHANGELOWERSTATE))
		वापस NOTIFY_DONE;

	ldev    = container_of(this, काष्ठा mlx5_lag, nb);

	अगर (!mlx5_lag_is_पढ़ोy(ldev) && event == NETDEV_CHANGELOWERSTATE)
		वापस NOTIFY_DONE;

	tracker = ldev->tracker;

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		changed = mlx5_handle_changeupper_event(ldev, &tracker, ndev,
							ptr);
		अवरोध;
	हाल NETDEV_CHANGELOWERSTATE:
		changed = mlx5_handle_changelowerstate_event(ldev, &tracker,
							     ndev, ptr);
		अवरोध;
	पूर्ण

	spin_lock(&lag_lock);
	ldev->tracker = tracker;
	spin_unlock(&lag_lock);

	अगर (changed)
		mlx5_queue_bond_work(ldev, 0);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा mlx5_lag *mlx5_lag_dev_alloc(व्योम)
अणु
	काष्ठा mlx5_lag *ldev;

	ldev = kzalloc(माप(*ldev), GFP_KERNEL);
	अगर (!ldev)
		वापस शून्य;

	ldev->wq = create_singlethपढ़ो_workqueue("mlx5_lag");
	अगर (!ldev->wq) अणु
		kमुक्त(ldev);
		वापस शून्य;
	पूर्ण

	INIT_DELAYED_WORK(&ldev->bond_work, mlx5_करो_bond_work);

	वापस ldev;
पूर्ण

अटल व्योम mlx5_lag_dev_मुक्त(काष्ठा mlx5_lag *ldev)
अणु
	destroy_workqueue(ldev->wq);
	kमुक्त(ldev);
पूर्ण

अटल पूर्णांक mlx5_lag_dev_add_pf(काष्ठा mlx5_lag *ldev,
			       काष्ठा mlx5_core_dev *dev,
			       काष्ठा net_device *netdev)
अणु
	अचिन्हित पूर्णांक fn = PCI_FUNC(dev->pdev->devfn);

	अगर (fn >= MLX5_MAX_PORTS)
		वापस -EPERM;

	spin_lock(&lag_lock);
	ldev->pf[fn].dev    = dev;
	ldev->pf[fn].netdev = netdev;
	ldev->tracker.netdev_state[fn].link_up = 0;
	ldev->tracker.netdev_state[fn].tx_enabled = 0;

	dev->priv.lag = ldev;

	spin_unlock(&lag_lock);

	वापस fn;
पूर्ण

अटल व्योम mlx5_lag_dev_हटाओ_pf(काष्ठा mlx5_lag *ldev,
				   काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX5_MAX_PORTS; i++)
		अगर (ldev->pf[i].dev == dev)
			अवरोध;

	अगर (i == MLX5_MAX_PORTS)
		वापस;

	spin_lock(&lag_lock);
	स_रखो(&ldev->pf[i], 0, माप(*ldev->pf));

	dev->priv.lag = शून्य;
	spin_unlock(&lag_lock);
पूर्ण

/* Must be called with पूर्णांकf_mutex held */
व्योम mlx5_lag_add(काष्ठा mlx5_core_dev *dev, काष्ठा net_device *netdev)
अणु
	काष्ठा mlx5_lag *ldev = शून्य;
	काष्ठा mlx5_core_dev *पंचांगp_dev;
	पूर्णांक i, err;

	अगर (!MLX5_CAP_GEN(dev, vport_group_manager) ||
	    !MLX5_CAP_GEN(dev, lag_master) ||
	    MLX5_CAP_GEN(dev, num_lag_ports) != MLX5_MAX_PORTS)
		वापस;

	पंचांगp_dev = mlx5_get_next_phys_dev(dev);
	अगर (पंचांगp_dev)
		ldev = पंचांगp_dev->priv.lag;

	अगर (!ldev) अणु
		ldev = mlx5_lag_dev_alloc();
		अगर (!ldev) अणु
			mlx5_core_err(dev, "Failed to alloc lag dev\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (mlx5_lag_dev_add_pf(ldev, dev, netdev) < 0)
		वापस;

	क्रम (i = 0; i < MLX5_MAX_PORTS; i++)
		अगर (!ldev->pf[i].dev)
			अवरोध;

	अगर (i >= MLX5_MAX_PORTS)
		ldev->flags |= MLX5_LAG_FLAG_READY;

	अगर (!ldev->nb.notअगरier_call) अणु
		ldev->nb.notअगरier_call = mlx5_lag_netdev_event;
		अगर (रेजिस्टर_netdevice_notअगरier_net(&init_net, &ldev->nb)) अणु
			ldev->nb.notअगरier_call = शून्य;
			mlx5_core_err(dev, "Failed to register LAG netdev notifier\n");
		पूर्ण
	पूर्ण

	err = mlx5_lag_mp_init(ldev);
	अगर (err)
		mlx5_core_err(dev, "Failed to init multipath lag err=%d\n",
			      err);
पूर्ण

/* Must be called with पूर्णांकf_mutex held */
व्योम mlx5_lag_हटाओ(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_lag *ldev;
	पूर्णांक i;

	ldev = mlx5_lag_dev_get(dev);
	अगर (!ldev)
		वापस;

	अगर (__mlx5_lag_is_active(ldev))
		mlx5_deactivate_lag(ldev);

	mlx5_lag_dev_हटाओ_pf(ldev, dev);

	ldev->flags &= ~MLX5_LAG_FLAG_READY;

	क्रम (i = 0; i < MLX5_MAX_PORTS; i++)
		अगर (ldev->pf[i].dev)
			अवरोध;

	अगर (i == MLX5_MAX_PORTS) अणु
		अगर (ldev->nb.notअगरier_call) अणु
			unरेजिस्टर_netdevice_notअगरier_net(&init_net, &ldev->nb);
			ldev->nb.notअगरier_call = शून्य;
		पूर्ण
		mlx5_lag_mp_cleanup(ldev);
		cancel_delayed_work_sync(&ldev->bond_work);
		mlx5_lag_dev_मुक्त(ldev);
	पूर्ण
पूर्ण

bool mlx5_lag_is_roce(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_lag *ldev;
	bool res;

	spin_lock(&lag_lock);
	ldev = mlx5_lag_dev_get(dev);
	res  = ldev && __mlx5_lag_is_roce(ldev);
	spin_unlock(&lag_lock);

	वापस res;
पूर्ण
EXPORT_SYMBOL(mlx5_lag_is_roce);

bool mlx5_lag_is_active(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_lag *ldev;
	bool res;

	spin_lock(&lag_lock);
	ldev = mlx5_lag_dev_get(dev);
	res  = ldev && __mlx5_lag_is_active(ldev);
	spin_unlock(&lag_lock);

	वापस res;
पूर्ण
EXPORT_SYMBOL(mlx5_lag_is_active);

bool mlx5_lag_is_sriov(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_lag *ldev;
	bool res;

	spin_lock(&lag_lock);
	ldev = mlx5_lag_dev_get(dev);
	res  = ldev && __mlx5_lag_is_sriov(ldev);
	spin_unlock(&lag_lock);

	वापस res;
पूर्ण
EXPORT_SYMBOL(mlx5_lag_is_sriov);

व्योम mlx5_lag_update(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_lag *ldev;

	mlx5_dev_list_lock();
	ldev = mlx5_lag_dev_get(dev);
	अगर (!ldev)
		जाओ unlock;

	mlx5_करो_bond(ldev);

unlock:
	mlx5_dev_list_unlock();
पूर्ण

काष्ठा net_device *mlx5_lag_get_roce_netdev(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा net_device *ndev = शून्य;
	काष्ठा mlx5_lag *ldev;

	spin_lock(&lag_lock);
	ldev = mlx5_lag_dev_get(dev);

	अगर (!(ldev && __mlx5_lag_is_roce(ldev)))
		जाओ unlock;

	अगर (ldev->tracker.tx_type == NETDEV_LAG_TX_TYPE_ACTIVEBACKUP) अणु
		ndev = ldev->tracker.netdev_state[MLX5_LAG_P1].tx_enabled ?
		       ldev->pf[MLX5_LAG_P1].netdev :
		       ldev->pf[MLX5_LAG_P2].netdev;
	पूर्ण अन्यथा अणु
		ndev = ldev->pf[MLX5_LAG_P1].netdev;
	पूर्ण
	अगर (ndev)
		dev_hold(ndev);

unlock:
	spin_unlock(&lag_lock);

	वापस ndev;
पूर्ण
EXPORT_SYMBOL(mlx5_lag_get_roce_netdev);

u8 mlx5_lag_get_slave_port(काष्ठा mlx5_core_dev *dev,
			   काष्ठा net_device *slave)
अणु
	काष्ठा mlx5_lag *ldev;
	u8 port = 0;

	spin_lock(&lag_lock);
	ldev = mlx5_lag_dev_get(dev);
	अगर (!(ldev && __mlx5_lag_is_roce(ldev)))
		जाओ unlock;

	अगर (ldev->pf[MLX5_LAG_P1].netdev == slave)
		port = MLX5_LAG_P1;
	अन्यथा
		port = MLX5_LAG_P2;

	port = ldev->v2p_map[port];

unlock:
	spin_unlock(&lag_lock);
	वापस port;
पूर्ण
EXPORT_SYMBOL(mlx5_lag_get_slave_port);

पूर्णांक mlx5_lag_query_cong_counters(काष्ठा mlx5_core_dev *dev,
				 u64 *values,
				 पूर्णांक num_counters,
				 माप_प्रकार *offsets)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_cong_statistics_out);
	काष्ठा mlx5_core_dev *mdev[MLX5_MAX_PORTS];
	काष्ठा mlx5_lag *ldev;
	पूर्णांक num_ports;
	पूर्णांक ret, i, j;
	व्योम *out;

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	स_रखो(values, 0, माप(*values) * num_counters);

	spin_lock(&lag_lock);
	ldev = mlx5_lag_dev_get(dev);
	अगर (ldev && __mlx5_lag_is_active(ldev)) अणु
		num_ports = MLX5_MAX_PORTS;
		mdev[MLX5_LAG_P1] = ldev->pf[MLX5_LAG_P1].dev;
		mdev[MLX5_LAG_P2] = ldev->pf[MLX5_LAG_P2].dev;
	पूर्ण अन्यथा अणु
		num_ports = 1;
		mdev[MLX5_LAG_P1] = dev;
	पूर्ण
	spin_unlock(&lag_lock);

	क्रम (i = 0; i < num_ports; ++i) अणु
		u32 in[MLX5_ST_SZ_DW(query_cong_statistics_in)] = अणुपूर्ण;

		MLX5_SET(query_cong_statistics_in, in, opcode,
			 MLX5_CMD_OP_QUERY_CONG_STATISTICS);
		ret = mlx5_cmd_exec_inout(mdev[i], query_cong_statistics, in,
					  out);
		अगर (ret)
			जाओ मुक्त;

		क्रम (j = 0; j < num_counters; ++j)
			values[j] += be64_to_cpup((__be64 *)(out + offsets[j]));
	पूर्ण

मुक्त:
	kvमुक्त(out);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mlx5_lag_query_cong_counters);
