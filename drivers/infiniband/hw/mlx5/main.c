<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2013-2020, Mellanox Technologies inc. All rights reserved.
 * Copyright (c) 2020, Intel Corporation. All rights reserved.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/delay.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>
#समावेश <linux/mlx5/port.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/mlx5/eचयन.h>
#समावेश <linux/list.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/lag.h>
#समावेश <linux/in.h>
#समावेश <linux/etherdevice.h>
#समावेश "mlx5_ib.h"
#समावेश "ib_rep.h"
#समावेश "cmd.h"
#समावेश "devx.h"
#समावेश "dm.h"
#समावेश "fs.h"
#समावेश "srq.h"
#समावेश "qp.h"
#समावेश "wr.h"
#समावेश "restrack.h"
#समावेश "counters.h"
#समावेश <linux/mlx5/accel.h>
#समावेश <rdma/uverbs_std_types.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/mlx5_user_ioctl_verbs.h>
#समावेश <rdma/mlx5_user_ioctl_cmds.h>
#समावेश <rdma/ib_umem_odp.h>

#घोषणा UVERBS_MODULE_NAME mlx5_ib
#समावेश <rdma/uverbs_named_ioctl.h>

MODULE_AUTHOR("Eli Cohen <eli@mellanox.com>");
MODULE_DESCRIPTION("Mellanox 5th generation network adapters (ConnectX series) IB driver");
MODULE_LICENSE("Dual BSD/GPL");

काष्ठा mlx5_ib_event_work अणु
	काष्ठा work_काष्ठा	work;
	जोड़ अणु
		काष्ठा mlx5_ib_dev	      *dev;
		काष्ठा mlx5_ib_multiport_info *mpi;
	पूर्ण;
	bool			is_slave;
	अचिन्हित पूर्णांक		event;
	व्योम			*param;
पूर्ण;

क्रमागत अणु
	MLX5_ATOMIC_SIZE_QP_8BYTES = 1 << 3,
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *mlx5_ib_event_wq;
अटल LIST_HEAD(mlx5_ib_unaffiliated_port_list);
अटल LIST_HEAD(mlx5_ib_dev_list);
/*
 * This mutex should be held when accessing either of the above lists
 */
अटल DEFINE_MUTEX(mlx5_ib_multiport_mutex);

काष्ठा mlx5_ib_dev *mlx5_ib_get_ibdev_from_mpi(काष्ठा mlx5_ib_multiport_info *mpi)
अणु
	काष्ठा mlx5_ib_dev *dev;

	mutex_lock(&mlx5_ib_multiport_mutex);
	dev = mpi->ibdev;
	mutex_unlock(&mlx5_ib_multiport_mutex);
	वापस dev;
पूर्ण

अटल क्रमागत rdma_link_layer
mlx5_port_type_cap_to_rdma_ll(पूर्णांक port_type_cap)
अणु
	चयन (port_type_cap) अणु
	हाल MLX5_CAP_PORT_TYPE_IB:
		वापस IB_LINK_LAYER_INFINIBAND;
	हाल MLX5_CAP_PORT_TYPE_ETH:
		वापस IB_LINK_LAYER_ETHERNET;
	शेष:
		वापस IB_LINK_LAYER_UNSPECIFIED;
	पूर्ण
पूर्ण

अटल क्रमागत rdma_link_layer
mlx5_ib_port_link_layer(काष्ठा ib_device *device, u32 port_num)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);
	पूर्णांक port_type_cap = MLX5_CAP_GEN(dev->mdev, port_type);

	वापस mlx5_port_type_cap_to_rdma_ll(port_type_cap);
पूर्ण

अटल पूर्णांक get_port_state(काष्ठा ib_device *ibdev,
			  u32 port_num,
			  क्रमागत ib_port_state *state)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक ret;

	स_रखो(&attr, 0, माप(attr));
	ret = ibdev->ops.query_port(ibdev, port_num, &attr);
	अगर (!ret)
		*state = attr.state;
	वापस ret;
पूर्ण

अटल काष्ठा mlx5_roce *mlx5_get_rep_roce(काष्ठा mlx5_ib_dev *dev,
					   काष्ठा net_device *ndev,
					   u32 *port_num)
अणु
	काष्ठा net_device *rep_ndev;
	काष्ठा mlx5_ib_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < dev->num_ports; i++) अणु
		port  = &dev->port[i];
		अगर (!port->rep)
			जारी;

		पढ़ो_lock(&port->roce.netdev_lock);
		rep_ndev = mlx5_ib_get_rep_netdev(port->rep->esw,
						  port->rep->vport);
		अगर (rep_ndev == ndev) अणु
			पढ़ो_unlock(&port->roce.netdev_lock);
			*port_num = i + 1;
			वापस &port->roce;
		पूर्ण
		पढ़ो_unlock(&port->roce.netdev_lock);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक mlx5_netdev_event(काष्ठा notअगरier_block *this,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा mlx5_roce *roce = container_of(this, काष्ठा mlx5_roce, nb);
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	u32 port_num = roce->native_port_num;
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5_ib_dev *ibdev;

	ibdev = roce->dev;
	mdev = mlx5_ib_get_native_port_mdev(ibdev, port_num, शून्य);
	अगर (!mdev)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		/* Should alपढ़ोy be रेजिस्टरed during the load */
		अगर (ibdev->is_rep)
			अवरोध;
		ग_लिखो_lock(&roce->netdev_lock);
		अगर (ndev->dev.parent == mdev->device)
			roce->netdev = ndev;
		ग_लिखो_unlock(&roce->netdev_lock);
		अवरोध;

	हाल NETDEV_UNREGISTER:
		/* In हाल of reps, ib device goes away beक्रमe the netdevs */
		ग_लिखो_lock(&roce->netdev_lock);
		अगर (roce->netdev == ndev)
			roce->netdev = शून्य;
		ग_लिखो_unlock(&roce->netdev_lock);
		अवरोध;

	हाल NETDEV_CHANGE:
	हाल NETDEV_UP:
	हाल NETDEV_DOWN: अणु
		काष्ठा net_device *lag_ndev = mlx5_lag_get_roce_netdev(mdev);
		काष्ठा net_device *upper = शून्य;

		अगर (lag_ndev) अणु
			upper = netdev_master_upper_dev_get(lag_ndev);
			dev_put(lag_ndev);
		पूर्ण

		अगर (ibdev->is_rep)
			roce = mlx5_get_rep_roce(ibdev, ndev, &port_num);
		अगर (!roce)
			वापस NOTIFY_DONE;
		अगर ((upper == ndev || (!upper && ndev == roce->netdev))
		    && ibdev->ib_active) अणु
			काष्ठा ib_event ibev = अणु पूर्ण;
			क्रमागत ib_port_state port_state;

			अगर (get_port_state(&ibdev->ib_dev, port_num,
					   &port_state))
				जाओ करोne;

			अगर (roce->last_port_state == port_state)
				जाओ करोne;

			roce->last_port_state = port_state;
			ibev.device = &ibdev->ib_dev;
			अगर (port_state == IB_PORT_DOWN)
				ibev.event = IB_EVENT_PORT_ERR;
			अन्यथा अगर (port_state == IB_PORT_ACTIVE)
				ibev.event = IB_EVENT_PORT_ACTIVE;
			अन्यथा
				जाओ करोne;

			ibev.element.port_num = port_num;
			ib_dispatch_event(&ibev);
		पूर्ण
		अवरोध;
	पूर्ण

	शेष:
		अवरोध;
	पूर्ण
करोne:
	mlx5_ib_put_native_port_mdev(ibdev, port_num);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा net_device *mlx5_ib_get_netdev(काष्ठा ib_device *device,
					     u32 port_num)
अणु
	काष्ठा mlx5_ib_dev *ibdev = to_mdev(device);
	काष्ठा net_device *ndev;
	काष्ठा mlx5_core_dev *mdev;

	mdev = mlx5_ib_get_native_port_mdev(ibdev, port_num, शून्य);
	अगर (!mdev)
		वापस शून्य;

	ndev = mlx5_lag_get_roce_netdev(mdev);
	अगर (ndev)
		जाओ out;

	/* Ensure ndev करोes not disappear beक्रमe we invoke dev_hold()
	 */
	पढ़ो_lock(&ibdev->port[port_num - 1].roce.netdev_lock);
	ndev = ibdev->port[port_num - 1].roce.netdev;
	अगर (ndev)
		dev_hold(ndev);
	पढ़ो_unlock(&ibdev->port[port_num - 1].roce.netdev_lock);

out:
	mlx5_ib_put_native_port_mdev(ibdev, port_num);
	वापस ndev;
पूर्ण

काष्ठा mlx5_core_dev *mlx5_ib_get_native_port_mdev(काष्ठा mlx5_ib_dev *ibdev,
						   u32 ib_port_num,
						   u32 *native_port_num)
अणु
	क्रमागत rdma_link_layer ll = mlx5_ib_port_link_layer(&ibdev->ib_dev,
							  ib_port_num);
	काष्ठा mlx5_core_dev *mdev = शून्य;
	काष्ठा mlx5_ib_multiport_info *mpi;
	काष्ठा mlx5_ib_port *port;

	अगर (!mlx5_core_mp_enabled(ibdev->mdev) ||
	    ll != IB_LINK_LAYER_ETHERNET) अणु
		अगर (native_port_num)
			*native_port_num = ib_port_num;
		वापस ibdev->mdev;
	पूर्ण

	अगर (native_port_num)
		*native_port_num = 1;

	port = &ibdev->port[ib_port_num - 1];
	spin_lock(&port->mp.mpi_lock);
	mpi = ibdev->port[ib_port_num - 1].mp.mpi;
	अगर (mpi && !mpi->unaffiliate) अणु
		mdev = mpi->mdev;
		/* If it's the master no need to refcount, it'll exist
		 * as दीर्घ as the ib_dev exists.
		 */
		अगर (!mpi->is_master)
			mpi->mdev_refcnt++;
	पूर्ण
	spin_unlock(&port->mp.mpi_lock);

	वापस mdev;
पूर्ण

व्योम mlx5_ib_put_native_port_mdev(काष्ठा mlx5_ib_dev *ibdev, u32 port_num)
अणु
	क्रमागत rdma_link_layer ll = mlx5_ib_port_link_layer(&ibdev->ib_dev,
							  port_num);
	काष्ठा mlx5_ib_multiport_info *mpi;
	काष्ठा mlx5_ib_port *port;

	अगर (!mlx5_core_mp_enabled(ibdev->mdev) || ll != IB_LINK_LAYER_ETHERNET)
		वापस;

	port = &ibdev->port[port_num - 1];

	spin_lock(&port->mp.mpi_lock);
	mpi = ibdev->port[port_num - 1].mp.mpi;
	अगर (mpi->is_master)
		जाओ out;

	mpi->mdev_refcnt--;
	अगर (mpi->unaffiliate)
		complete(&mpi->unref_comp);
out:
	spin_unlock(&port->mp.mpi_lock);
पूर्ण

अटल पूर्णांक translate_eth_legacy_proto_oper(u32 eth_proto_oper,
					   u16 *active_speed, u8 *active_width)
अणु
	चयन (eth_proto_oper) अणु
	हाल MLX5E_PROT_MASK(MLX5E_1000BASE_CX_SGMII):
	हाल MLX5E_PROT_MASK(MLX5E_1000BASE_KX):
	हाल MLX5E_PROT_MASK(MLX5E_100BASE_TX):
	हाल MLX5E_PROT_MASK(MLX5E_1000BASE_T):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_SDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_10GBASE_T):
	हाल MLX5E_PROT_MASK(MLX5E_10GBASE_CX4):
	हाल MLX5E_PROT_MASK(MLX5E_10GBASE_KX4):
	हाल MLX5E_PROT_MASK(MLX5E_10GBASE_KR):
	हाल MLX5E_PROT_MASK(MLX5E_10GBASE_CR):
	हाल MLX5E_PROT_MASK(MLX5E_10GBASE_SR):
	हाल MLX5E_PROT_MASK(MLX5E_10GBASE_ER):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_QDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_25GBASE_CR):
	हाल MLX5E_PROT_MASK(MLX5E_25GBASE_KR):
	हाल MLX5E_PROT_MASK(MLX5E_25GBASE_SR):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_EDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_40GBASE_CR4):
	हाल MLX5E_PROT_MASK(MLX5E_40GBASE_KR4):
	हाल MLX5E_PROT_MASK(MLX5E_40GBASE_SR4):
	हाल MLX5E_PROT_MASK(MLX5E_40GBASE_LR4):
		*active_width = IB_WIDTH_4X;
		*active_speed = IB_SPEED_QDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_50GBASE_CR2):
	हाल MLX5E_PROT_MASK(MLX5E_50GBASE_KR2):
	हाल MLX5E_PROT_MASK(MLX5E_50GBASE_SR2):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_HDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_56GBASE_R4):
		*active_width = IB_WIDTH_4X;
		*active_speed = IB_SPEED_FDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_100GBASE_CR4):
	हाल MLX5E_PROT_MASK(MLX5E_100GBASE_SR4):
	हाल MLX5E_PROT_MASK(MLX5E_100GBASE_KR4):
	हाल MLX5E_PROT_MASK(MLX5E_100GBASE_LR4):
		*active_width = IB_WIDTH_4X;
		*active_speed = IB_SPEED_EDR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक translate_eth_ext_proto_oper(u32 eth_proto_oper, u16 *active_speed,
					u8 *active_width)
अणु
	चयन (eth_proto_oper) अणु
	हाल MLX5E_PROT_MASK(MLX5E_SGMII_100M):
	हाल MLX5E_PROT_MASK(MLX5E_1000BASE_X_SGMII):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_SDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_5GBASE_R):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_DDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_10GBASE_XFI_XAUI_1):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_QDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_40GBASE_XLAUI_4_XLPPI_4):
		*active_width = IB_WIDTH_4X;
		*active_speed = IB_SPEED_QDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_25GAUI_1_25GBASE_CR_KR):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_EDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_50GAUI_2_LAUI_2_50GBASE_CR2_KR2):
		*active_width = IB_WIDTH_2X;
		*active_speed = IB_SPEED_EDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_50GAUI_1_LAUI_1_50GBASE_CR_KR):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_HDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_CAUI_4_100GBASE_CR4_KR4):
		*active_width = IB_WIDTH_4X;
		*active_speed = IB_SPEED_EDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_100GAUI_2_100GBASE_CR2_KR2):
		*active_width = IB_WIDTH_2X;
		*active_speed = IB_SPEED_HDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_100GAUI_1_100GBASE_CR_KR):
		*active_width = IB_WIDTH_1X;
		*active_speed = IB_SPEED_NDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_200GAUI_4_200GBASE_CR4_KR4):
		*active_width = IB_WIDTH_4X;
		*active_speed = IB_SPEED_HDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_200GAUI_2_200GBASE_CR2_KR2):
		*active_width = IB_WIDTH_2X;
		*active_speed = IB_SPEED_NDR;
		अवरोध;
	हाल MLX5E_PROT_MASK(MLX5E_400GAUI_4_400GBASE_CR4_KR4):
		*active_width = IB_WIDTH_4X;
		*active_speed = IB_SPEED_NDR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक translate_eth_proto_oper(u32 eth_proto_oper, u16 *active_speed,
				    u8 *active_width, bool ext)
अणु
	वापस ext ?
		translate_eth_ext_proto_oper(eth_proto_oper, active_speed,
					     active_width) :
		translate_eth_legacy_proto_oper(eth_proto_oper, active_speed,
						active_width);
पूर्ण

अटल पूर्णांक mlx5_query_port_roce(काष्ठा ib_device *device, u32 port_num,
				काष्ठा ib_port_attr *props)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);
	u32 out[MLX5_ST_SZ_DW(ptys_reg)] = अणु0पूर्ण;
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा net_device *ndev, *upper;
	क्रमागत ib_mtu ndev_ib_mtu;
	bool put_mdev = true;
	u32 eth_prot_oper;
	u32 mdev_port_num;
	bool ext;
	पूर्णांक err;

	mdev = mlx5_ib_get_native_port_mdev(dev, port_num, &mdev_port_num);
	अगर (!mdev) अणु
		/* This means the port isn't affiliated yet. Get the
		 * info क्रम the master port instead.
		 */
		put_mdev = false;
		mdev = dev->mdev;
		mdev_port_num = 1;
		port_num = 1;
	पूर्ण

	/* Possible bad flows are checked beक्रमe filling out props so in हाल
	 * of an error it will still be zeroed out.
	 * Use native port in हाल of reps
	 */
	अगर (dev->is_rep)
		err = mlx5_query_port_ptys(mdev, out, माप(out), MLX5_PTYS_EN,
					   1);
	अन्यथा
		err = mlx5_query_port_ptys(mdev, out, माप(out), MLX5_PTYS_EN,
					   mdev_port_num);
	अगर (err)
		जाओ out;
	ext = !!MLX5_GET_ETH_PROTO(ptys_reg, out, true, eth_proto_capability);
	eth_prot_oper = MLX5_GET_ETH_PROTO(ptys_reg, out, ext, eth_proto_oper);

	props->active_width     = IB_WIDTH_4X;
	props->active_speed     = IB_SPEED_QDR;

	translate_eth_proto_oper(eth_prot_oper, &props->active_speed,
				 &props->active_width, ext);

	अगर (!dev->is_rep && dev->mdev->roce.roce_en) अणु
		u16 qkey_viol_cntr;

		props->port_cap_flags |= IB_PORT_CM_SUP;
		props->ip_gids = true;
		props->gid_tbl_len = MLX5_CAP_ROCE(dev->mdev,
						   roce_address_table_size);
		mlx5_query_nic_vport_qkey_viol_cntr(mdev, &qkey_viol_cntr);
		props->qkey_viol_cntr = qkey_viol_cntr;
	पूर्ण
	props->max_mtu          = IB_MTU_4096;
	props->max_msg_sz       = 1 << MLX5_CAP_GEN(dev->mdev, log_max_msg);
	props->pkey_tbl_len     = 1;
	props->state            = IB_PORT_DOWN;
	props->phys_state       = IB_PORT_PHYS_STATE_DISABLED;

	/* If this is a stub query क्रम an unaffiliated port stop here */
	अगर (!put_mdev)
		जाओ out;

	ndev = mlx5_ib_get_netdev(device, port_num);
	अगर (!ndev)
		जाओ out;

	अगर (dev->lag_active) अणु
		rcu_पढ़ो_lock();
		upper = netdev_master_upper_dev_get_rcu(ndev);
		अगर (upper) अणु
			dev_put(ndev);
			ndev = upper;
			dev_hold(ndev);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (netअगर_running(ndev) && netअगर_carrier_ok(ndev)) अणु
		props->state      = IB_PORT_ACTIVE;
		props->phys_state = IB_PORT_PHYS_STATE_LINK_UP;
	पूर्ण

	ndev_ib_mtu = iboe_get_mtu(ndev->mtu);

	dev_put(ndev);

	props->active_mtu	= min(props->max_mtu, ndev_ib_mtu);
out:
	अगर (put_mdev)
		mlx5_ib_put_native_port_mdev(dev, port_num);
	वापस err;
पूर्ण

अटल पूर्णांक set_roce_addr(काष्ठा mlx5_ib_dev *dev, u32 port_num,
			 अचिन्हित पूर्णांक index, स्थिर जोड़ ib_gid *gid,
			 स्थिर काष्ठा ib_gid_attr *attr)
अणु
	क्रमागत ib_gid_type gid_type;
	u16 vlan_id = 0xffff;
	u8 roce_version = 0;
	u8 roce_l3_type = 0;
	u8 mac[ETH_ALEN];
	पूर्णांक ret;

	gid_type = attr->gid_type;
	अगर (gid) अणु
		ret = rdma_पढ़ो_gid_l2_fields(attr, &vlan_id, &mac[0]);
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (gid_type) अणु
	हाल IB_GID_TYPE_ROCE:
		roce_version = MLX5_ROCE_VERSION_1;
		अवरोध;
	हाल IB_GID_TYPE_ROCE_UDP_ENCAP:
		roce_version = MLX5_ROCE_VERSION_2;
		अगर (gid && ipv6_addr_v4mapped((व्योम *)gid))
			roce_l3_type = MLX5_ROCE_L3_TYPE_IPV4;
		अन्यथा
			roce_l3_type = MLX5_ROCE_L3_TYPE_IPV6;
		अवरोध;

	शेष:
		mlx5_ib_warn(dev, "Unexpected GID type %u\n", gid_type);
	पूर्ण

	वापस mlx5_core_roce_gid_set(dev->mdev, index, roce_version,
				      roce_l3_type, gid->raw, mac,
				      vlan_id < VLAN_CFI_MASK, vlan_id,
				      port_num);
पूर्ण

अटल पूर्णांक mlx5_ib_add_gid(स्थिर काष्ठा ib_gid_attr *attr,
			   __always_unused व्योम **context)
अणु
	वापस set_roce_addr(to_mdev(attr->device), attr->port_num,
			     attr->index, &attr->gid, attr);
पूर्ण

अटल पूर्णांक mlx5_ib_del_gid(स्थिर काष्ठा ib_gid_attr *attr,
			   __always_unused व्योम **context)
अणु
	वापस set_roce_addr(to_mdev(attr->device), attr->port_num,
			     attr->index, शून्य, attr);
पूर्ण

__be16 mlx5_get_roce_udp_sport_min(स्थिर काष्ठा mlx5_ib_dev *dev,
				   स्थिर काष्ठा ib_gid_attr *attr)
अणु
	अगर (attr->gid_type != IB_GID_TYPE_ROCE_UDP_ENCAP)
		वापस 0;

	वापस cpu_to_be16(MLX5_CAP_ROCE(dev->mdev, r_roce_min_src_udp_port));
पूर्ण

अटल पूर्णांक mlx5_use_mad_अगरc(काष्ठा mlx5_ib_dev *dev)
अणु
	अगर (MLX5_CAP_GEN(dev->mdev, port_type) == MLX5_CAP_PORT_TYPE_IB)
		वापस !MLX5_CAP_GEN(dev->mdev, ib_virt);
	वापस 0;
पूर्ण

क्रमागत अणु
	MLX5_VPORT_ACCESS_METHOD_MAD,
	MLX5_VPORT_ACCESS_METHOD_HCA,
	MLX5_VPORT_ACCESS_METHOD_NIC,
पूर्ण;

अटल पूर्णांक mlx5_get_vport_access_method(काष्ठा ib_device *ibdev)
अणु
	अगर (mlx5_use_mad_अगरc(to_mdev(ibdev)))
		वापस MLX5_VPORT_ACCESS_METHOD_MAD;

	अगर (mlx5_ib_port_link_layer(ibdev, 1) ==
	    IB_LINK_LAYER_ETHERNET)
		वापस MLX5_VPORT_ACCESS_METHOD_NIC;

	वापस MLX5_VPORT_ACCESS_METHOD_HCA;
पूर्ण

अटल व्योम get_atomic_caps(काष्ठा mlx5_ib_dev *dev,
			    u8 atomic_size_qp,
			    काष्ठा ib_device_attr *props)
अणु
	u8 पंचांगp;
	u8 atomic_operations = MLX5_CAP_ATOMIC(dev->mdev, atomic_operations);
	u8 atomic_req_8B_endianness_mode =
		MLX5_CAP_ATOMIC(dev->mdev, atomic_req_8B_endianness_mode);

	/* Check अगर HW supports 8 bytes standard atomic operations and capable
	 * of host endianness respond
	 */
	पंचांगp = MLX5_ATOMIC_OPS_CMP_SWAP | MLX5_ATOMIC_OPS_FETCH_ADD;
	अगर (((atomic_operations & पंचांगp) == पंचांगp) &&
	    (atomic_size_qp & MLX5_ATOMIC_SIZE_QP_8BYTES) &&
	    (atomic_req_8B_endianness_mode)) अणु
		props->atomic_cap = IB_ATOMIC_HCA;
	पूर्ण अन्यथा अणु
		props->atomic_cap = IB_ATOMIC_NONE;
	पूर्ण
पूर्ण

अटल व्योम get_atomic_caps_qp(काष्ठा mlx5_ib_dev *dev,
			       काष्ठा ib_device_attr *props)
अणु
	u8 atomic_size_qp = MLX5_CAP_ATOMIC(dev->mdev, atomic_size_qp);

	get_atomic_caps(dev, atomic_size_qp, props);
पूर्ण

अटल पूर्णांक mlx5_query_प्रणाली_image_guid(काष्ठा ib_device *ibdev,
					__be64 *sys_image_guid)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	u64 पंचांगp;
	पूर्णांक err;

	चयन (mlx5_get_vport_access_method(ibdev)) अणु
	हाल MLX5_VPORT_ACCESS_METHOD_MAD:
		वापस mlx5_query_mad_अगरc_प्रणाली_image_guid(ibdev,
							    sys_image_guid);

	हाल MLX5_VPORT_ACCESS_METHOD_HCA:
		err = mlx5_query_hca_vport_प्रणाली_image_guid(mdev, &पंचांगp);
		अवरोध;

	हाल MLX5_VPORT_ACCESS_METHOD_NIC:
		err = mlx5_query_nic_vport_प्रणाली_image_guid(mdev, &पंचांगp);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!err)
		*sys_image_guid = cpu_to_be64(पंचांगp);

	वापस err;

पूर्ण

अटल पूर्णांक mlx5_query_max_pkeys(काष्ठा ib_device *ibdev,
				u16 *max_pkeys)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;

	चयन (mlx5_get_vport_access_method(ibdev)) अणु
	हाल MLX5_VPORT_ACCESS_METHOD_MAD:
		वापस mlx5_query_mad_अगरc_max_pkeys(ibdev, max_pkeys);

	हाल MLX5_VPORT_ACCESS_METHOD_HCA:
	हाल MLX5_VPORT_ACCESS_METHOD_NIC:
		*max_pkeys = mlx5_to_sw_pkey_sz(MLX5_CAP_GEN(mdev,
						pkey_table_size));
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_query_venकरोr_id(काष्ठा ib_device *ibdev,
				u32 *venकरोr_id)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);

	चयन (mlx5_get_vport_access_method(ibdev)) अणु
	हाल MLX5_VPORT_ACCESS_METHOD_MAD:
		वापस mlx5_query_mad_अगरc_venकरोr_id(ibdev, venकरोr_id);

	हाल MLX5_VPORT_ACCESS_METHOD_HCA:
	हाल MLX5_VPORT_ACCESS_METHOD_NIC:
		वापस mlx5_core_query_venकरोr_id(dev->mdev, venकरोr_id);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_query_node_guid(काष्ठा mlx5_ib_dev *dev,
				__be64 *node_guid)
अणु
	u64 पंचांगp;
	पूर्णांक err;

	चयन (mlx5_get_vport_access_method(&dev->ib_dev)) अणु
	हाल MLX5_VPORT_ACCESS_METHOD_MAD:
		वापस mlx5_query_mad_अगरc_node_guid(dev, node_guid);

	हाल MLX5_VPORT_ACCESS_METHOD_HCA:
		err = mlx5_query_hca_vport_node_guid(dev->mdev, &पंचांगp);
		अवरोध;

	हाल MLX5_VPORT_ACCESS_METHOD_NIC:
		err = mlx5_query_nic_vport_node_guid(dev->mdev, &पंचांगp);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!err)
		*node_guid = cpu_to_be64(पंचांगp);

	वापस err;
पूर्ण

काष्ठा mlx5_reg_node_desc अणु
	u8	desc[IB_DEVICE_NODE_DESC_MAX];
पूर्ण;

अटल पूर्णांक mlx5_query_node_desc(काष्ठा mlx5_ib_dev *dev, अक्षर *node_desc)
अणु
	काष्ठा mlx5_reg_node_desc in;

	अगर (mlx5_use_mad_अगरc(dev))
		वापस mlx5_query_mad_अगरc_node_desc(dev, node_desc);

	स_रखो(&in, 0, माप(in));

	वापस mlx5_core_access_reg(dev->mdev, &in, माप(in), node_desc,
				    माप(काष्ठा mlx5_reg_node_desc),
				    MLX5_REG_NODE_DESC, 0, 0);
पूर्ण

अटल पूर्णांक mlx5_ib_query_device(काष्ठा ib_device *ibdev,
				काष्ठा ib_device_attr *props,
				काष्ठा ib_udata *uhw)
अणु
	माप_प्रकार uhw_outlen = (uhw) ? uhw->outlen : 0;
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	पूर्णांक err = -ENOMEM;
	पूर्णांक max_sq_desc;
	पूर्णांक max_rq_sg;
	पूर्णांक max_sq_sg;
	u64 min_page_size = 1ull << MLX5_CAP_GEN(mdev, log_pg_sz);
	bool raw_support = !mlx5_core_mp_enabled(mdev);
	काष्ठा mlx5_ib_query_device_resp resp = अणुपूर्ण;
	माप_प्रकार resp_len;
	u64 max_tso;

	resp_len = माप(resp.comp_mask) + माप(resp.response_length);
	अगर (uhw_outlen && uhw_outlen < resp_len)
		वापस -EINVAL;

	resp.response_length = resp_len;

	अगर (uhw && uhw->inlen && !ib_is_udata_cleared(uhw, 0, uhw->inlen))
		वापस -EINVAL;

	स_रखो(props, 0, माप(*props));
	err = mlx5_query_प्रणाली_image_guid(ibdev,
					   &props->sys_image_guid);
	अगर (err)
		वापस err;

	props->max_pkeys = dev->pkey_table_len;

	err = mlx5_query_venकरोr_id(ibdev, &props->venकरोr_id);
	अगर (err)
		वापस err;

	props->fw_ver = ((u64)fw_rev_maj(dev->mdev) << 32) |
		(fw_rev_min(dev->mdev) << 16) |
		fw_rev_sub(dev->mdev);
	props->device_cap_flags    = IB_DEVICE_CHANGE_PHY_PORT |
		IB_DEVICE_PORT_ACTIVE_EVENT		|
		IB_DEVICE_SYS_IMAGE_GUID		|
		IB_DEVICE_RC_RNR_NAK_GEN;

	अगर (MLX5_CAP_GEN(mdev, pkv))
		props->device_cap_flags |= IB_DEVICE_BAD_PKEY_CNTR;
	अगर (MLX5_CAP_GEN(mdev, qkv))
		props->device_cap_flags |= IB_DEVICE_BAD_QKEY_CNTR;
	अगर (MLX5_CAP_GEN(mdev, apm))
		props->device_cap_flags |= IB_DEVICE_AUTO_PATH_MIG;
	अगर (MLX5_CAP_GEN(mdev, xrc))
		props->device_cap_flags |= IB_DEVICE_XRC;
	अगर (MLX5_CAP_GEN(mdev, imaicl)) अणु
		props->device_cap_flags |= IB_DEVICE_MEM_WINDOW |
					   IB_DEVICE_MEM_WINDOW_TYPE_2B;
		props->max_mw = 1 << MLX5_CAP_GEN(mdev, log_max_mkey);
		/* We support 'Gappy' memory registration too */
		props->device_cap_flags |= IB_DEVICE_SG_GAPS_REG;
	पूर्ण
	/* IB_WR_REG_MR always requires changing the entity size with UMR */
	अगर (!MLX5_CAP_GEN(dev->mdev, umr_modअगरy_entity_size_disabled))
		props->device_cap_flags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
	अगर (MLX5_CAP_GEN(mdev, sho)) अणु
		props->device_cap_flags |= IB_DEVICE_INTEGRITY_HANDOVER;
		/* At this stage no support क्रम signature hanकरोver */
		props->sig_prot_cap = IB_PROT_T10DIF_TYPE_1 |
				      IB_PROT_T10DIF_TYPE_2 |
				      IB_PROT_T10DIF_TYPE_3;
		props->sig_guard_cap = IB_GUARD_T10DIF_CRC |
				       IB_GUARD_T10DIF_CSUM;
	पूर्ण
	अगर (MLX5_CAP_GEN(mdev, block_lb_mc))
		props->device_cap_flags |= IB_DEVICE_BLOCK_MULTICAST_LOOPBACK;

	अगर (MLX5_CAP_GEN(dev->mdev, eth_net_offloads) && raw_support) अणु
		अगर (MLX5_CAP_ETH(mdev, csum_cap)) अणु
			/* Legacy bit to support old userspace libraries */
			props->device_cap_flags |= IB_DEVICE_RAW_IP_CSUM;
			props->raw_packet_caps |= IB_RAW_PACKET_CAP_IP_CSUM;
		पूर्ण

		अगर (MLX5_CAP_ETH(dev->mdev, vlan_cap))
			props->raw_packet_caps |=
				IB_RAW_PACKET_CAP_CVLAN_STRIPPING;

		अगर (दुरत्वend(typeof(resp), tso_caps) <= uhw_outlen) अणु
			max_tso = MLX5_CAP_ETH(mdev, max_lso_cap);
			अगर (max_tso) अणु
				resp.tso_caps.max_tso = 1 << max_tso;
				resp.tso_caps.supported_qpts |=
					1 << IB_QPT_RAW_PACKET;
				resp.response_length += माप(resp.tso_caps);
			पूर्ण
		पूर्ण

		अगर (दुरत्वend(typeof(resp), rss_caps) <= uhw_outlen) अणु
			resp.rss_caps.rx_hash_function =
						MLX5_RX_HASH_FUNC_TOEPLITZ;
			resp.rss_caps.rx_hash_fields_mask =
						MLX5_RX_HASH_SRC_IPV4 |
						MLX5_RX_HASH_DST_IPV4 |
						MLX5_RX_HASH_SRC_IPV6 |
						MLX5_RX_HASH_DST_IPV6 |
						MLX5_RX_HASH_SRC_PORT_TCP |
						MLX5_RX_HASH_DST_PORT_TCP |
						MLX5_RX_HASH_SRC_PORT_UDP |
						MLX5_RX_HASH_DST_PORT_UDP |
						MLX5_RX_HASH_INNER;
			अगर (mlx5_accel_ipsec_device_caps(dev->mdev) &
			    MLX5_ACCEL_IPSEC_CAP_DEVICE)
				resp.rss_caps.rx_hash_fields_mask |=
					MLX5_RX_HASH_IPSEC_SPI;
			resp.response_length += माप(resp.rss_caps);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (दुरत्वend(typeof(resp), tso_caps) <= uhw_outlen)
			resp.response_length += माप(resp.tso_caps);
		अगर (दुरत्वend(typeof(resp), rss_caps) <= uhw_outlen)
			resp.response_length += माप(resp.rss_caps);
	पूर्ण

	अगर (MLX5_CAP_GEN(mdev, ipoib_basic_offloads)) अणु
		props->device_cap_flags |= IB_DEVICE_UD_IP_CSUM;
		props->device_cap_flags |= IB_DEVICE_UD_TSO;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev->mdev, rq_delay_drop) &&
	    MLX5_CAP_GEN(dev->mdev, general_notअगरication_event) &&
	    raw_support)
		props->raw_packet_caps |= IB_RAW_PACKET_CAP_DELAY_DROP;

	अगर (MLX5_CAP_GEN(mdev, ipoib_enhanced_offloads) &&
	    MLX5_CAP_IPOIB_ENHANCED(mdev, csum_cap))
		props->device_cap_flags |= IB_DEVICE_UD_IP_CSUM;

	अगर (MLX5_CAP_GEN(dev->mdev, eth_net_offloads) &&
	    MLX5_CAP_ETH(dev->mdev, scatter_fcs) &&
	    raw_support) अणु
		/* Legacy bit to support old userspace libraries */
		props->device_cap_flags |= IB_DEVICE_RAW_SCATTER_FCS;
		props->raw_packet_caps |= IB_RAW_PACKET_CAP_SCATTER_FCS;
	पूर्ण

	अगर (MLX5_CAP_DEV_MEM(mdev, memic)) अणु
		props->max_dm_size =
			MLX5_CAP_DEV_MEM(mdev, max_memic_size);
	पूर्ण

	अगर (mlx5_get_flow_namespace(dev->mdev, MLX5_FLOW_NAMESPACE_BYPASS))
		props->device_cap_flags |= IB_DEVICE_MANAGED_FLOW_STEERING;

	अगर (MLX5_CAP_GEN(mdev, end_pad))
		props->device_cap_flags |= IB_DEVICE_PCI_WRITE_END_PADDING;

	props->venकरोr_part_id	   = mdev->pdev->device;
	props->hw_ver		   = mdev->pdev->revision;

	props->max_mr_size	   = ~0ull;
	props->page_size_cap	   = ~(min_page_size - 1);
	props->max_qp		   = 1 << MLX5_CAP_GEN(mdev, log_max_qp);
	props->max_qp_wr	   = 1 << MLX5_CAP_GEN(mdev, log_max_qp_sz);
	max_rq_sg =  MLX5_CAP_GEN(mdev, max_wqe_sz_rq) /
		     माप(काष्ठा mlx5_wqe_data_seg);
	max_sq_desc = min_t(पूर्णांक, MLX5_CAP_GEN(mdev, max_wqe_sz_sq), 512);
	max_sq_sg = (max_sq_desc - माप(काष्ठा mlx5_wqe_ctrl_seg) -
		     माप(काष्ठा mlx5_wqe_raddr_seg)) /
		माप(काष्ठा mlx5_wqe_data_seg);
	props->max_send_sge = max_sq_sg;
	props->max_recv_sge = max_rq_sg;
	props->max_sge_rd	   = MLX5_MAX_SGE_RD;
	props->max_cq		   = 1 << MLX5_CAP_GEN(mdev, log_max_cq);
	props->max_cqe = (1 << MLX5_CAP_GEN(mdev, log_max_cq_sz)) - 1;
	props->max_mr		   = 1 << MLX5_CAP_GEN(mdev, log_max_mkey);
	props->max_pd		   = 1 << MLX5_CAP_GEN(mdev, log_max_pd);
	props->max_qp_rd_atom	   = 1 << MLX5_CAP_GEN(mdev, log_max_ra_req_qp);
	props->max_qp_init_rd_atom = 1 << MLX5_CAP_GEN(mdev, log_max_ra_res_qp);
	props->max_srq		   = 1 << MLX5_CAP_GEN(mdev, log_max_srq);
	props->max_srq_wr = (1 << MLX5_CAP_GEN(mdev, log_max_srq_sz)) - 1;
	props->local_ca_ack_delay  = MLX5_CAP_GEN(mdev, local_ca_ack_delay);
	props->max_res_rd_atom	   = props->max_qp_rd_atom * props->max_qp;
	props->max_srq_sge	   = max_rq_sg - 1;
	props->max_fast_reg_page_list_len =
		1 << MLX5_CAP_GEN(mdev, log_max_klm_list_size);
	props->max_pi_fast_reg_page_list_len =
		props->max_fast_reg_page_list_len / 2;
	props->max_sgl_rd =
		MLX5_CAP_GEN(mdev, max_sgl_क्रम_optimized_perक्रमmance);
	get_atomic_caps_qp(dev, props);
	props->masked_atomic_cap   = IB_ATOMIC_NONE;
	props->max_mcast_grp	   = 1 << MLX5_CAP_GEN(mdev, log_max_mcg);
	props->max_mcast_qp_attach = MLX5_CAP_GEN(mdev, max_qp_mcg);
	props->max_total_mcast_qp_attach = props->max_mcast_qp_attach *
					   props->max_mcast_grp;
	props->max_ah = पूर्णांक_उच्च;
	props->hca_core_घड़ी = MLX5_CAP_GEN(mdev, device_frequency_khz);
	props->बारtamp_mask = 0x7FFFFFFFFFFFFFFFULL;

	अगर (IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING)) अणु
		अगर (dev->odp_caps.general_caps & IB_ODP_SUPPORT)
			props->device_cap_flags |= IB_DEVICE_ON_DEMAND_PAGING;
		props->odp_caps = dev->odp_caps;
		अगर (!uhw) अणु
			/* ODP क्रम kernel QPs is not implemented क्रम receive
			 * WQEs and SRQ WQEs
			 */
			props->odp_caps.per_transport_caps.rc_odp_caps &=
				~(IB_ODP_SUPPORT_READ |
				  IB_ODP_SUPPORT_SRQ_RECV);
			props->odp_caps.per_transport_caps.uc_odp_caps &=
				~(IB_ODP_SUPPORT_READ |
				  IB_ODP_SUPPORT_SRQ_RECV);
			props->odp_caps.per_transport_caps.ud_odp_caps &=
				~(IB_ODP_SUPPORT_READ |
				  IB_ODP_SUPPORT_SRQ_RECV);
			props->odp_caps.per_transport_caps.xrc_odp_caps &=
				~(IB_ODP_SUPPORT_READ |
				  IB_ODP_SUPPORT_SRQ_RECV);
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_GEN(mdev, cd))
		props->device_cap_flags |= IB_DEVICE_CROSS_CHANNEL;

	अगर (mlx5_core_is_vf(mdev))
		props->device_cap_flags |= IB_DEVICE_VIRTUAL_FUNCTION;

	अगर (mlx5_ib_port_link_layer(ibdev, 1) ==
	    IB_LINK_LAYER_ETHERNET && raw_support) अणु
		props->rss_caps.max_rwq_indirection_tables =
			1 << MLX5_CAP_GEN(dev->mdev, log_max_rqt);
		props->rss_caps.max_rwq_indirection_table_size =
			1 << MLX5_CAP_GEN(dev->mdev, log_max_rqt_size);
		props->rss_caps.supported_qpts = 1 << IB_QPT_RAW_PACKET;
		props->max_wq_type_rq =
			1 << MLX5_CAP_GEN(dev->mdev, log_max_rq);
	पूर्ण

	अगर (MLX5_CAP_GEN(mdev, tag_matching)) अणु
		props->पंचांग_caps.max_num_tags =
			(1 << MLX5_CAP_GEN(mdev, log_tag_matching_list_sz)) - 1;
		props->पंचांग_caps.max_ops =
			1 << MLX5_CAP_GEN(mdev, log_max_qp_sz);
		props->पंचांग_caps.max_sge = MLX5_TM_MAX_SGE;
	पूर्ण

	अगर (MLX5_CAP_GEN(mdev, tag_matching) &&
	    MLX5_CAP_GEN(mdev, rndv_offload_rc)) अणु
		props->पंचांग_caps.flags = IB_TM_CAP_RNDV_RC;
		props->पंचांग_caps.max_rndv_hdr_size = MLX5_TM_MAX_RNDV_MSG_SIZE;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev->mdev, cq_moderation)) अणु
		props->cq_caps.max_cq_moderation_count =
						MLX5_MAX_CQ_COUNT;
		props->cq_caps.max_cq_moderation_period =
						MLX5_MAX_CQ_PERIOD;
	पूर्ण

	अगर (दुरत्वend(typeof(resp), cqe_comp_caps) <= uhw_outlen) अणु
		resp.response_length += माप(resp.cqe_comp_caps);

		अगर (MLX5_CAP_GEN(dev->mdev, cqe_compression)) अणु
			resp.cqe_comp_caps.max_num =
				MLX5_CAP_GEN(dev->mdev,
					     cqe_compression_max_num);

			resp.cqe_comp_caps.supported_क्रमmat =
				MLX5_IB_CQE_RES_FORMAT_HASH |
				MLX5_IB_CQE_RES_FORMAT_CSUM;

			अगर (MLX5_CAP_GEN(dev->mdev, mini_cqe_resp_stride_index))
				resp.cqe_comp_caps.supported_क्रमmat |=
					MLX5_IB_CQE_RES_FORMAT_CSUM_STRIDX;
		पूर्ण
	पूर्ण

	अगर (दुरत्वend(typeof(resp), packet_pacing_caps) <= uhw_outlen &&
	    raw_support) अणु
		अगर (MLX5_CAP_QOS(mdev, packet_pacing) &&
		    MLX5_CAP_GEN(mdev, qos)) अणु
			resp.packet_pacing_caps.qp_rate_limit_max =
				MLX5_CAP_QOS(mdev, packet_pacing_max_rate);
			resp.packet_pacing_caps.qp_rate_limit_min =
				MLX5_CAP_QOS(mdev, packet_pacing_min_rate);
			resp.packet_pacing_caps.supported_qpts |=
				1 << IB_QPT_RAW_PACKET;
			अगर (MLX5_CAP_QOS(mdev, packet_pacing_burst_bound) &&
			    MLX5_CAP_QOS(mdev, packet_pacing_typical_size))
				resp.packet_pacing_caps.cap_flags |=
					MLX5_IB_PP_SUPPORT_BURST;
		पूर्ण
		resp.response_length += माप(resp.packet_pacing_caps);
	पूर्ण

	अगर (दुरत्वend(typeof(resp), mlx5_ib_support_multi_pkt_send_wqes) <=
	    uhw_outlen) अणु
		अगर (MLX5_CAP_ETH(mdev, multi_pkt_send_wqe))
			resp.mlx5_ib_support_multi_pkt_send_wqes =
				MLX5_IB_ALLOW_MPW;

		अगर (MLX5_CAP_ETH(mdev, enhanced_multi_pkt_send_wqe))
			resp.mlx5_ib_support_multi_pkt_send_wqes |=
				MLX5_IB_SUPPORT_EMPW;

		resp.response_length +=
			माप(resp.mlx5_ib_support_multi_pkt_send_wqes);
	पूर्ण

	अगर (दुरत्वend(typeof(resp), flags) <= uhw_outlen) अणु
		resp.response_length += माप(resp.flags);

		अगर (MLX5_CAP_GEN(mdev, cqe_compression_128))
			resp.flags |=
				MLX5_IB_QUERY_DEV_RESP_FLAGS_CQE_128B_COMP;

		अगर (MLX5_CAP_GEN(mdev, cqe_128_always))
			resp.flags |= MLX5_IB_QUERY_DEV_RESP_FLAGS_CQE_128B_PAD;
		अगर (MLX5_CAP_GEN(mdev, qp_packet_based))
			resp.flags |=
				MLX5_IB_QUERY_DEV_RESP_PACKET_BASED_CREDIT_MODE;

		resp.flags |= MLX5_IB_QUERY_DEV_RESP_FLAGS_SCAT2CQE_DCT;
	पूर्ण

	अगर (दुरत्वend(typeof(resp), sw_parsing_caps) <= uhw_outlen) अणु
		resp.response_length += माप(resp.sw_parsing_caps);
		अगर (MLX5_CAP_ETH(mdev, swp)) अणु
			resp.sw_parsing_caps.sw_parsing_offloads |=
				MLX5_IB_SW_PARSING;

			अगर (MLX5_CAP_ETH(mdev, swp_csum))
				resp.sw_parsing_caps.sw_parsing_offloads |=
					MLX5_IB_SW_PARSING_CSUM;

			अगर (MLX5_CAP_ETH(mdev, swp_lso))
				resp.sw_parsing_caps.sw_parsing_offloads |=
					MLX5_IB_SW_PARSING_LSO;

			अगर (resp.sw_parsing_caps.sw_parsing_offloads)
				resp.sw_parsing_caps.supported_qpts =
					BIT(IB_QPT_RAW_PACKET);
		पूर्ण
	पूर्ण

	अगर (दुरत्वend(typeof(resp), striding_rq_caps) <= uhw_outlen &&
	    raw_support) अणु
		resp.response_length += माप(resp.striding_rq_caps);
		अगर (MLX5_CAP_GEN(mdev, striding_rq)) अणु
			resp.striding_rq_caps.min_single_stride_log_num_of_bytes =
				MLX5_MIN_SINGLE_STRIDE_LOG_NUM_BYTES;
			resp.striding_rq_caps.max_single_stride_log_num_of_bytes =
				MLX5_MAX_SINGLE_STRIDE_LOG_NUM_BYTES;
			अगर (MLX5_CAP_GEN(dev->mdev, ext_stride_num_range))
				resp.striding_rq_caps
					.min_single_wqe_log_num_of_strides =
					MLX5_EXT_MIN_SINGLE_WQE_LOG_NUM_STRIDES;
			अन्यथा
				resp.striding_rq_caps
					.min_single_wqe_log_num_of_strides =
					MLX5_MIN_SINGLE_WQE_LOG_NUM_STRIDES;
			resp.striding_rq_caps.max_single_wqe_log_num_of_strides =
				MLX5_MAX_SINGLE_WQE_LOG_NUM_STRIDES;
			resp.striding_rq_caps.supported_qpts =
				BIT(IB_QPT_RAW_PACKET);
		पूर्ण
	पूर्ण

	अगर (दुरत्वend(typeof(resp), tunnel_offloads_caps) <= uhw_outlen) अणु
		resp.response_length += माप(resp.tunnel_offloads_caps);
		अगर (MLX5_CAP_ETH(mdev, tunnel_stateless_vxlan))
			resp.tunnel_offloads_caps |=
				MLX5_IB_TUNNELED_OFFLOADS_VXLAN;
		अगर (MLX5_CAP_ETH(mdev, tunnel_stateless_geneve_rx))
			resp.tunnel_offloads_caps |=
				MLX5_IB_TUNNELED_OFFLOADS_GENEVE;
		अगर (MLX5_CAP_ETH(mdev, tunnel_stateless_gre))
			resp.tunnel_offloads_caps |=
				MLX5_IB_TUNNELED_OFFLOADS_GRE;
		अगर (MLX5_CAP_ETH(mdev, tunnel_stateless_mpls_over_gre))
			resp.tunnel_offloads_caps |=
				MLX5_IB_TUNNELED_OFFLOADS_MPLS_GRE;
		अगर (MLX5_CAP_ETH(mdev, tunnel_stateless_mpls_over_udp))
			resp.tunnel_offloads_caps |=
				MLX5_IB_TUNNELED_OFFLOADS_MPLS_UDP;
	पूर्ण

	अगर (uhw_outlen) अणु
		err = ib_copy_to_udata(uhw, &resp, resp.response_length);

		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम translate_active_width(काष्ठा ib_device *ibdev, u16 active_width,
				   u8 *ib_width)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);

	अगर (active_width & MLX5_PTYS_WIDTH_1X)
		*ib_width = IB_WIDTH_1X;
	अन्यथा अगर (active_width & MLX5_PTYS_WIDTH_2X)
		*ib_width = IB_WIDTH_2X;
	अन्यथा अगर (active_width & MLX5_PTYS_WIDTH_4X)
		*ib_width = IB_WIDTH_4X;
	अन्यथा अगर (active_width & MLX5_PTYS_WIDTH_8X)
		*ib_width = IB_WIDTH_8X;
	अन्यथा अगर (active_width & MLX5_PTYS_WIDTH_12X)
		*ib_width = IB_WIDTH_12X;
	अन्यथा अणु
		mlx5_ib_dbg(dev, "Invalid active_width %d, setting width to default value: 4x\n",
			    active_width);
		*ib_width = IB_WIDTH_4X;
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक mlx5_mtu_to_ib_mtu(पूर्णांक mtu)
अणु
	चयन (mtu) अणु
	हाल 256: वापस 1;
	हाल 512: वापस 2;
	हाल 1024: वापस 3;
	हाल 2048: वापस 4;
	हाल 4096: वापस 5;
	शेष:
		pr_warn("invalid mtu\n");
		वापस -1;
	पूर्ण
पूर्ण

क्रमागत ib_max_vl_num अणु
	__IB_MAX_VL_0		= 1,
	__IB_MAX_VL_0_1		= 2,
	__IB_MAX_VL_0_3		= 3,
	__IB_MAX_VL_0_7		= 4,
	__IB_MAX_VL_0_14	= 5,
पूर्ण;

क्रमागत mlx5_vl_hw_cap अणु
	MLX5_VL_HW_0	= 1,
	MLX5_VL_HW_0_1	= 2,
	MLX5_VL_HW_0_2	= 3,
	MLX5_VL_HW_0_3	= 4,
	MLX5_VL_HW_0_4	= 5,
	MLX5_VL_HW_0_5	= 6,
	MLX5_VL_HW_0_6	= 7,
	MLX5_VL_HW_0_7	= 8,
	MLX5_VL_HW_0_14	= 15
पूर्ण;

अटल पूर्णांक translate_max_vl_num(काष्ठा ib_device *ibdev, u8 vl_hw_cap,
				u8 *max_vl_num)
अणु
	चयन (vl_hw_cap) अणु
	हाल MLX5_VL_HW_0:
		*max_vl_num = __IB_MAX_VL_0;
		अवरोध;
	हाल MLX5_VL_HW_0_1:
		*max_vl_num = __IB_MAX_VL_0_1;
		अवरोध;
	हाल MLX5_VL_HW_0_3:
		*max_vl_num = __IB_MAX_VL_0_3;
		अवरोध;
	हाल MLX5_VL_HW_0_7:
		*max_vl_num = __IB_MAX_VL_0_7;
		अवरोध;
	हाल MLX5_VL_HW_0_14:
		*max_vl_num = __IB_MAX_VL_0_14;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_query_hca_port(काष्ठा ib_device *ibdev, u32 port,
			       काष्ठा ib_port_attr *props)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_hca_vport_context *rep;
	u16 max_mtu;
	u16 oper_mtu;
	पूर्णांक err;
	u16 ib_link_width_oper;
	u8 vl_hw_cap;

	rep = kzalloc(माप(*rep), GFP_KERNEL);
	अगर (!rep) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* props being zeroed by the caller, aव्योम zeroing it here */

	err = mlx5_query_hca_vport_context(mdev, 0, port, 0, rep);
	अगर (err)
		जाओ out;

	props->lid		= rep->lid;
	props->lmc		= rep->lmc;
	props->sm_lid		= rep->sm_lid;
	props->sm_sl		= rep->sm_sl;
	props->state		= rep->vport_state;
	props->phys_state	= rep->port_physical_state;
	props->port_cap_flags	= rep->cap_mask1;
	props->gid_tbl_len	= mlx5_get_gid_table_len(MLX5_CAP_GEN(mdev, gid_table_size));
	props->max_msg_sz	= 1 << MLX5_CAP_GEN(mdev, log_max_msg);
	props->pkey_tbl_len	= mlx5_to_sw_pkey_sz(MLX5_CAP_GEN(mdev, pkey_table_size));
	props->bad_pkey_cntr	= rep->pkey_violation_counter;
	props->qkey_viol_cntr	= rep->qkey_violation_counter;
	props->subnet_समयout	= rep->subnet_समयout;
	props->init_type_reply	= rep->init_type_reply;

	अगर (props->port_cap_flags & IB_PORT_CAP_MASK2_SUP)
		props->port_cap_flags2 = rep->cap_mask2;

	err = mlx5_query_ib_port_oper(mdev, &ib_link_width_oper,
				      &props->active_speed, port);
	अगर (err)
		जाओ out;

	translate_active_width(ibdev, ib_link_width_oper, &props->active_width);

	mlx5_query_port_max_mtu(mdev, &max_mtu, port);

	props->max_mtu = mlx5_mtu_to_ib_mtu(max_mtu);

	mlx5_query_port_oper_mtu(mdev, &oper_mtu, port);

	props->active_mtu = mlx5_mtu_to_ib_mtu(oper_mtu);

	err = mlx5_query_port_vl_hw_cap(mdev, &vl_hw_cap, port);
	अगर (err)
		जाओ out;

	err = translate_max_vl_num(ibdev, vl_hw_cap,
				   &props->max_vl_num);
out:
	kमुक्त(rep);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_query_port(काष्ठा ib_device *ibdev, u32 port,
		       काष्ठा ib_port_attr *props)
अणु
	अचिन्हित पूर्णांक count;
	पूर्णांक ret;

	चयन (mlx5_get_vport_access_method(ibdev)) अणु
	हाल MLX5_VPORT_ACCESS_METHOD_MAD:
		ret = mlx5_query_mad_अगरc_port(ibdev, port, props);
		अवरोध;

	हाल MLX5_VPORT_ACCESS_METHOD_HCA:
		ret = mlx5_query_hca_port(ibdev, port, props);
		अवरोध;

	हाल MLX5_VPORT_ACCESS_METHOD_NIC:
		ret = mlx5_query_port_roce(ibdev, port, props);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (!ret && props) अणु
		काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
		काष्ठा mlx5_core_dev *mdev;
		bool put_mdev = true;

		mdev = mlx5_ib_get_native_port_mdev(dev, port, शून्य);
		अगर (!mdev) अणु
			/* If the port isn't affiliated yet query the master.
			 * The master and slave will have the same values.
			 */
			mdev = dev->mdev;
			port = 1;
			put_mdev = false;
		पूर्ण
		count = mlx5_core_reserved_gids_count(mdev);
		अगर (put_mdev)
			mlx5_ib_put_native_port_mdev(dev, port);
		props->gid_tbl_len -= count;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_ib_rep_query_port(काष्ठा ib_device *ibdev, u32 port,
				  काष्ठा ib_port_attr *props)
अणु
	वापस mlx5_query_port_roce(ibdev, port, props);
पूर्ण

अटल पूर्णांक mlx5_ib_rep_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
				  u16 *pkey)
अणु
	/* Default special Pkey क्रम representor device port as per the
	 * IB specअगरication 1.3 section 10.9.1.2.
	 */
	*pkey = 0xffff;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
			     जोड़ ib_gid *gid)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;

	चयन (mlx5_get_vport_access_method(ibdev)) अणु
	हाल MLX5_VPORT_ACCESS_METHOD_MAD:
		वापस mlx5_query_mad_अगरc_gids(ibdev, port, index, gid);

	हाल MLX5_VPORT_ACCESS_METHOD_HCA:
		वापस mlx5_query_hca_vport_gid(mdev, 0, port, 0, index, gid);

	शेष:
		वापस -EINVAL;
	पूर्ण

पूर्ण

अटल पूर्णांक mlx5_query_hca_nic_pkey(काष्ठा ib_device *ibdev, u32 port,
				   u16 index, u16 *pkey)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_core_dev *mdev;
	bool put_mdev = true;
	u32 mdev_port_num;
	पूर्णांक err;

	mdev = mlx5_ib_get_native_port_mdev(dev, port, &mdev_port_num);
	अगर (!mdev) अणु
		/* The port isn't affiliated yet, get the PKey from the master
		 * port. For RoCE the PKey tables will be the same.
		 */
		put_mdev = false;
		mdev = dev->mdev;
		mdev_port_num = 1;
	पूर्ण

	err = mlx5_query_hca_vport_pkey(mdev, 0, mdev_port_num, 0,
					index, pkey);
	अगर (put_mdev)
		mlx5_ib_put_native_port_mdev(dev, port);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_ib_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
			      u16 *pkey)
अणु
	चयन (mlx5_get_vport_access_method(ibdev)) अणु
	हाल MLX5_VPORT_ACCESS_METHOD_MAD:
		वापस mlx5_query_mad_अगरc_pkey(ibdev, port, index, pkey);

	हाल MLX5_VPORT_ACCESS_METHOD_HCA:
	हाल MLX5_VPORT_ACCESS_METHOD_NIC:
		वापस mlx5_query_hca_nic_pkey(ibdev, port, index, pkey);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_ib_modअगरy_device(काष्ठा ib_device *ibdev, पूर्णांक mask,
				 काष्ठा ib_device_modअगरy *props)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_reg_node_desc in;
	काष्ठा mlx5_reg_node_desc out;
	पूर्णांक err;

	अगर (mask & ~IB_DEVICE_MODIFY_NODE_DESC)
		वापस -EOPNOTSUPP;

	अगर (!(mask & IB_DEVICE_MODIFY_NODE_DESC))
		वापस 0;

	/*
	 * If possible, pass node desc to FW, so it can generate
	 * a 144 trap.  If cmd fails, just ignore.
	 */
	स_नकल(&in, props->node_desc, IB_DEVICE_NODE_DESC_MAX);
	err = mlx5_core_access_reg(dev->mdev, &in, माप(in), &out,
				   माप(out), MLX5_REG_NODE_DESC, 0, 1);
	अगर (err)
		वापस err;

	स_नकल(ibdev->node_desc, props->node_desc, IB_DEVICE_NODE_DESC_MAX);

	वापस err;
पूर्ण

अटल पूर्णांक set_port_caps_atomic(काष्ठा mlx5_ib_dev *dev, u32 port_num, u32 mask,
				u32 value)
अणु
	काष्ठा mlx5_hca_vport_context ctx = अणुपूर्ण;
	काष्ठा mlx5_core_dev *mdev;
	u32 mdev_port_num;
	पूर्णांक err;

	mdev = mlx5_ib_get_native_port_mdev(dev, port_num, &mdev_port_num);
	अगर (!mdev)
		वापस -ENODEV;

	err = mlx5_query_hca_vport_context(mdev, 0, mdev_port_num, 0, &ctx);
	अगर (err)
		जाओ out;

	अगर (~ctx.cap_mask1_perm & mask) अणु
		mlx5_ib_warn(dev, "trying to change bitmask 0x%X but change supported 0x%X\n",
			     mask, ctx.cap_mask1_perm);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	ctx.cap_mask1 = value;
	ctx.cap_mask1_perm = mask;
	err = mlx5_core_modअगरy_hca_vport_context(mdev, 0, mdev_port_num,
						 0, &ctx);

out:
	mlx5_ib_put_native_port_mdev(dev, port_num);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_ib_modअगरy_port(काष्ठा ib_device *ibdev, u32 port, पूर्णांक mask,
			       काष्ठा ib_port_modअगरy *props)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा ib_port_attr attr;
	u32 पंचांगp;
	पूर्णांक err;
	u32 change_mask;
	u32 value;
	bool is_ib = (mlx5_ib_port_link_layer(ibdev, port) ==
		      IB_LINK_LAYER_INFINIBAND);

	/* CM layer calls ib_modअगरy_port() regardless of the link layer. For
	 * Ethernet ports, qkey violation and Port capabilities are meaningless.
	 */
	अगर (!is_ib)
		वापस 0;

	अगर (MLX5_CAP_GEN(dev->mdev, ib_virt) && is_ib) अणु
		change_mask = props->clr_port_cap_mask | props->set_port_cap_mask;
		value = ~props->clr_port_cap_mask | props->set_port_cap_mask;
		वापस set_port_caps_atomic(dev, port, change_mask, value);
	पूर्ण

	mutex_lock(&dev->cap_mask_mutex);

	err = ib_query_port(ibdev, port, &attr);
	अगर (err)
		जाओ out;

	पंचांगp = (attr.port_cap_flags | props->set_port_cap_mask) &
		~props->clr_port_cap_mask;

	err = mlx5_set_port_caps(dev->mdev, port, पंचांगp);

out:
	mutex_unlock(&dev->cap_mask_mutex);
	वापस err;
पूर्ण

अटल व्योम prपूर्णांक_lib_caps(काष्ठा mlx5_ib_dev *dev, u64 caps)
अणु
	mlx5_ib_dbg(dev, "MLX5_LIB_CAP_4K_UAR = %s\n",
		    caps & MLX5_LIB_CAP_4K_UAR ? "y" : "n");
पूर्ण

अटल u16 calc_dynamic_bfregs(पूर्णांक uars_per_sys_page)
अणु
	/* Large page with non 4k uar support might limit the dynamic size */
	अगर (uars_per_sys_page == 1  && PAGE_SIZE > 4096)
		वापस MLX5_MIN_DYN_BFREGS;

	वापस MLX5_MAX_DYN_BFREGS;
पूर्ण

अटल पूर्णांक calc_total_bfregs(काष्ठा mlx5_ib_dev *dev, bool lib_uar_4k,
			     काष्ठा mlx5_ib_alloc_ucontext_req_v2 *req,
			     काष्ठा mlx5_bfreg_info *bfregi)
अणु
	पूर्णांक uars_per_sys_page;
	पूर्णांक bfregs_per_sys_page;
	पूर्णांक ref_bfregs = req->total_num_bfregs;

	अगर (req->total_num_bfregs == 0)
		वापस -EINVAL;

	BUILD_BUG_ON(MLX5_MAX_BFREGS % MLX5_NON_FP_BFREGS_IN_PAGE);
	BUILD_BUG_ON(MLX5_MAX_BFREGS < MLX5_NON_FP_BFREGS_IN_PAGE);

	अगर (req->total_num_bfregs > MLX5_MAX_BFREGS)
		वापस -ENOMEM;

	uars_per_sys_page = get_uars_per_sys_page(dev, lib_uar_4k);
	bfregs_per_sys_page = uars_per_sys_page * MLX5_NON_FP_BFREGS_PER_UAR;
	/* This holds the required अटल allocation asked by the user */
	req->total_num_bfregs = ALIGN(req->total_num_bfregs, bfregs_per_sys_page);
	अगर (req->num_low_latency_bfregs > req->total_num_bfregs - 1)
		वापस -EINVAL;

	bfregi->num_अटल_sys_pages = req->total_num_bfregs / bfregs_per_sys_page;
	bfregi->num_dyn_bfregs = ALIGN(calc_dynamic_bfregs(uars_per_sys_page), bfregs_per_sys_page);
	bfregi->total_num_bfregs = req->total_num_bfregs + bfregi->num_dyn_bfregs;
	bfregi->num_sys_pages = bfregi->total_num_bfregs / bfregs_per_sys_page;

	mlx5_ib_dbg(dev, "uar_4k: fw support %s, lib support %s, user requested %d bfregs, allocated %d, total bfregs %d, using %d sys pages\n",
		    MLX5_CAP_GEN(dev->mdev, uar_4k) ? "yes" : "no",
		    lib_uar_4k ? "yes" : "no", ref_bfregs,
		    req->total_num_bfregs, bfregi->total_num_bfregs,
		    bfregi->num_sys_pages);

	वापस 0;
पूर्ण

अटल पूर्णांक allocate_uars(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_ucontext *context)
अणु
	काष्ठा mlx5_bfreg_info *bfregi;
	पूर्णांक err;
	पूर्णांक i;

	bfregi = &context->bfregi;
	क्रम (i = 0; i < bfregi->num_अटल_sys_pages; i++) अणु
		err = mlx5_cmd_alloc_uar(dev->mdev, &bfregi->sys_pages[i]);
		अगर (err)
			जाओ error;

		mlx5_ib_dbg(dev, "allocated uar %d\n", bfregi->sys_pages[i]);
	पूर्ण

	क्रम (i = bfregi->num_अटल_sys_pages; i < bfregi->num_sys_pages; i++)
		bfregi->sys_pages[i] = MLX5_IB_INVALID_UAR_INDEX;

	वापस 0;

error:
	क्रम (--i; i >= 0; i--)
		अगर (mlx5_cmd_मुक्त_uar(dev->mdev, bfregi->sys_pages[i]))
			mlx5_ib_warn(dev, "failed to free uar %d\n", i);

	वापस err;
पूर्ण

अटल व्योम deallocate_uars(काष्ठा mlx5_ib_dev *dev,
			    काष्ठा mlx5_ib_ucontext *context)
अणु
	काष्ठा mlx5_bfreg_info *bfregi;
	पूर्णांक i;

	bfregi = &context->bfregi;
	क्रम (i = 0; i < bfregi->num_sys_pages; i++)
		अगर (i < bfregi->num_अटल_sys_pages ||
		    bfregi->sys_pages[i] != MLX5_IB_INVALID_UAR_INDEX)
			mlx5_cmd_मुक्त_uar(dev->mdev, bfregi->sys_pages[i]);
पूर्ण

पूर्णांक mlx5_ib_enable_lb(काष्ठा mlx5_ib_dev *dev, bool td, bool qp)
अणु
	पूर्णांक err = 0;

	mutex_lock(&dev->lb.mutex);
	अगर (td)
		dev->lb.user_td++;
	अगर (qp)
		dev->lb.qps++;

	अगर (dev->lb.user_td == 2 ||
	    dev->lb.qps == 1) अणु
		अगर (!dev->lb.enabled) अणु
			err = mlx5_nic_vport_update_local_lb(dev->mdev, true);
			dev->lb.enabled = true;
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->lb.mutex);

	वापस err;
पूर्ण

व्योम mlx5_ib_disable_lb(काष्ठा mlx5_ib_dev *dev, bool td, bool qp)
अणु
	mutex_lock(&dev->lb.mutex);
	अगर (td)
		dev->lb.user_td--;
	अगर (qp)
		dev->lb.qps--;

	अगर (dev->lb.user_td == 1 &&
	    dev->lb.qps == 0) अणु
		अगर (dev->lb.enabled) अणु
			mlx5_nic_vport_update_local_lb(dev->mdev, false);
			dev->lb.enabled = false;
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->lb.mutex);
पूर्ण

अटल पूर्णांक mlx5_ib_alloc_transport_करोमुख्य(काष्ठा mlx5_ib_dev *dev, u32 *tdn,
					  u16 uid)
अणु
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(dev->mdev, log_max_transport_करोमुख्य))
		वापस 0;

	err = mlx5_cmd_alloc_transport_करोमुख्य(dev->mdev, tdn, uid);
	अगर (err)
		वापस err;

	अगर ((MLX5_CAP_GEN(dev->mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH) ||
	    (!MLX5_CAP_GEN(dev->mdev, disable_local_lb_uc) &&
	     !MLX5_CAP_GEN(dev->mdev, disable_local_lb_mc)))
		वापस err;

	वापस mlx5_ib_enable_lb(dev, true, false);
पूर्ण

अटल व्योम mlx5_ib_dealloc_transport_करोमुख्य(काष्ठा mlx5_ib_dev *dev, u32 tdn,
					     u16 uid)
अणु
	अगर (!MLX5_CAP_GEN(dev->mdev, log_max_transport_करोमुख्य))
		वापस;

	mlx5_cmd_dealloc_transport_करोमुख्य(dev->mdev, tdn, uid);

	अगर ((MLX5_CAP_GEN(dev->mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH) ||
	    (!MLX5_CAP_GEN(dev->mdev, disable_local_lb_uc) &&
	     !MLX5_CAP_GEN(dev->mdev, disable_local_lb_mc)))
		वापस;

	mlx5_ib_disable_lb(dev, true, false);
पूर्ण

अटल पूर्णांक set_ucontext_resp(काष्ठा ib_ucontext *uctx,
			     काष्ठा mlx5_ib_alloc_ucontext_resp *resp)
अणु
	काष्ठा ib_device *ibdev = uctx->device;
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_ib_ucontext *context = to_mucontext(uctx);
	काष्ठा mlx5_bfreg_info *bfregi = &context->bfregi;
	पूर्णांक err;

	अगर (MLX5_CAP_GEN(dev->mdev, dump_fill_mkey)) अणु
		err = mlx5_cmd_dump_fill_mkey(dev->mdev,
					      &resp->dump_fill_mkey);
		अगर (err)
			वापस err;
		resp->comp_mask |=
			MLX5_IB_ALLOC_UCONTEXT_RESP_MASK_DUMP_FILL_MKEY;
	पूर्ण

	resp->qp_tab_size = 1 << MLX5_CAP_GEN(dev->mdev, log_max_qp);
	अगर (dev->wc_support)
		resp->bf_reg_size = 1 << MLX5_CAP_GEN(dev->mdev,
						      log_bf_reg_size);
	resp->cache_line_size = cache_line_size();
	resp->max_sq_desc_sz = MLX5_CAP_GEN(dev->mdev, max_wqe_sz_sq);
	resp->max_rq_desc_sz = MLX5_CAP_GEN(dev->mdev, max_wqe_sz_rq);
	resp->max_send_wqebb = 1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz);
	resp->max_recv_wr = 1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz);
	resp->max_srq_recv_wr = 1 << MLX5_CAP_GEN(dev->mdev, log_max_srq_sz);
	resp->cqe_version = context->cqe_version;
	resp->log_uar_size = MLX5_CAP_GEN(dev->mdev, uar_4k) ?
				MLX5_ADAPTER_PAGE_SHIFT : PAGE_SHIFT;
	resp->num_uars_per_page = MLX5_CAP_GEN(dev->mdev, uar_4k) ?
					MLX5_CAP_GEN(dev->mdev,
						     num_of_uars_per_page) : 1;

	अगर (mlx5_accel_ipsec_device_caps(dev->mdev) &
				MLX5_ACCEL_IPSEC_CAP_DEVICE) अणु
		अगर (mlx5_get_flow_namespace(dev->mdev,
				MLX5_FLOW_NAMESPACE_EGRESS))
			resp->flow_action_flags |= MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM;
		अगर (mlx5_accel_ipsec_device_caps(dev->mdev) &
				MLX5_ACCEL_IPSEC_CAP_REQUIRED_METADATA)
			resp->flow_action_flags |= MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM_REQ_METADATA;
		अगर (MLX5_CAP_FLOWTABLE(dev->mdev, flow_table_properties_nic_receive.ft_field_support.outer_esp_spi))
			resp->flow_action_flags |= MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM_SPI_STEERING;
		अगर (mlx5_accel_ipsec_device_caps(dev->mdev) &
				MLX5_ACCEL_IPSEC_CAP_TX_IV_IS_ESN)
			resp->flow_action_flags |= MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM_TX_IV_IS_ESN;
		/* MLX5_USER_ALLOC_UCONTEXT_FLOW_ACTION_FLAGS_ESP_AES_GCM_FULL_OFFLOAD is currently always 0 */
	पूर्ण

	resp->tot_bfregs = bfregi->lib_uar_dyn ? 0 :
			bfregi->total_num_bfregs - bfregi->num_dyn_bfregs;
	resp->num_ports = dev->num_ports;
	resp->cmds_supp_uhw |= MLX5_USER_CMDS_SUPP_UHW_QUERY_DEVICE |
				      MLX5_USER_CMDS_SUPP_UHW_CREATE_AH;

	अगर (mlx5_ib_port_link_layer(ibdev, 1) == IB_LINK_LAYER_ETHERNET) अणु
		mlx5_query_min_अंतरभूत(dev->mdev, &resp->eth_min_अंतरभूत);
		resp->eth_min_अंतरभूत++;
	पूर्ण

	अगर (dev->mdev->घड़ी_info)
		resp->घड़ी_info_versions = BIT(MLX5_IB_CLOCK_INFO_V1);

	/*
	 * We करोn't want to expose inक्रमmation from the PCI bar that is located
	 * after 4096 bytes, so अगर the arch only supports larger pages, let's
	 * pretend we करोn't support reading the HCA's core घड़ी. This is also
	 * क्रमced by mmap function.
	 */
	अगर (PAGE_SIZE <= 4096) अणु
		resp->comp_mask |=
			MLX5_IB_ALLOC_UCONTEXT_RESP_MASK_CORE_CLOCK_OFFSET;
		resp->hca_core_घड़ी_offset =
			दुरत्व(काष्ठा mlx5_init_seg,
				 पूर्णांकernal_समयr_h) % PAGE_SIZE;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev->mdev, ece_support))
		resp->comp_mask |= MLX5_IB_ALLOC_UCONTEXT_RESP_MASK_ECE;

	resp->num_dyn_bfregs = bfregi->num_dyn_bfregs;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_alloc_ucontext(काष्ठा ib_ucontext *uctx,
				  काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = uctx->device;
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx5_ib_alloc_ucontext_req_v2 req = अणुपूर्ण;
	काष्ठा mlx5_ib_alloc_ucontext_resp resp = अणुपूर्ण;
	काष्ठा mlx5_ib_ucontext *context = to_mucontext(uctx);
	काष्ठा mlx5_bfreg_info *bfregi;
	पूर्णांक ver;
	पूर्णांक err;
	माप_प्रकार min_req_v2 = दुरत्व(काष्ठा mlx5_ib_alloc_ucontext_req_v2,
				     max_cqe_version);
	bool lib_uar_4k;
	bool lib_uar_dyn;

	अगर (!dev->ib_active)
		वापस -EAGAIN;

	अगर (udata->inlen == माप(काष्ठा mlx5_ib_alloc_ucontext_req))
		ver = 0;
	अन्यथा अगर (udata->inlen >= min_req_v2)
		ver = 2;
	अन्यथा
		वापस -EINVAL;

	err = ib_copy_from_udata(&req, udata, min(udata->inlen, माप(req)));
	अगर (err)
		वापस err;

	अगर (req.flags & ~MLX5_IB_ALLOC_UCTX_DEVX)
		वापस -EOPNOTSUPP;

	अगर (req.comp_mask || req.reserved0 || req.reserved1 || req.reserved2)
		वापस -EOPNOTSUPP;

	req.total_num_bfregs = ALIGN(req.total_num_bfregs,
				    MLX5_NON_FP_BFREGS_PER_UAR);
	अगर (req.num_low_latency_bfregs > req.total_num_bfregs - 1)
		वापस -EINVAL;

	lib_uar_4k = req.lib_caps & MLX5_LIB_CAP_4K_UAR;
	lib_uar_dyn = req.lib_caps & MLX5_LIB_CAP_DYN_UAR;
	bfregi = &context->bfregi;

	अगर (lib_uar_dyn) अणु
		bfregi->lib_uar_dyn = lib_uar_dyn;
		जाओ uar_करोne;
	पूर्ण

	/* updates req->total_num_bfregs */
	err = calc_total_bfregs(dev, lib_uar_4k, &req, bfregi);
	अगर (err)
		जाओ out_ctx;

	mutex_init(&bfregi->lock);
	bfregi->lib_uar_4k = lib_uar_4k;
	bfregi->count = kसुस्मृति(bfregi->total_num_bfregs, माप(*bfregi->count),
				GFP_KERNEL);
	अगर (!bfregi->count) अणु
		err = -ENOMEM;
		जाओ out_ctx;
	पूर्ण

	bfregi->sys_pages = kसुस्मृति(bfregi->num_sys_pages,
				    माप(*bfregi->sys_pages),
				    GFP_KERNEL);
	अगर (!bfregi->sys_pages) अणु
		err = -ENOMEM;
		जाओ out_count;
	पूर्ण

	err = allocate_uars(dev, context);
	अगर (err)
		जाओ out_sys_pages;

uar_करोne:
	अगर (req.flags & MLX5_IB_ALLOC_UCTX_DEVX) अणु
		err = mlx5_ib_devx_create(dev, true);
		अगर (err < 0)
			जाओ out_uars;
		context->devx_uid = err;
	पूर्ण

	err = mlx5_ib_alloc_transport_करोमुख्य(dev, &context->tdn,
					     context->devx_uid);
	अगर (err)
		जाओ out_devx;

	INIT_LIST_HEAD(&context->db_page_list);
	mutex_init(&context->db_page_mutex);

	context->cqe_version = min_t(__u8,
				 (__u8)MLX5_CAP_GEN(dev->mdev, cqe_version),
				 req.max_cqe_version);

	err = set_ucontext_resp(uctx, &resp);
	अगर (err)
		जाओ out_mdev;

	resp.response_length = min(udata->outlen, माप(resp));
	err = ib_copy_to_udata(udata, &resp, resp.response_length);
	अगर (err)
		जाओ out_mdev;

	bfregi->ver = ver;
	bfregi->num_low_latency_bfregs = req.num_low_latency_bfregs;
	context->lib_caps = req.lib_caps;
	prपूर्णांक_lib_caps(dev, context->lib_caps);

	अगर (mlx5_ib_lag_should_assign_affinity(dev)) अणु
		u32 port = mlx5_core_native_port_num(dev->mdev) - 1;

		atomic_set(&context->tx_port_affinity,
			   atomic_add_वापस(
				   1, &dev->port[port].roce.tx_port_affinity));
	पूर्ण

	वापस 0;

out_mdev:
	mlx5_ib_dealloc_transport_करोमुख्य(dev, context->tdn, context->devx_uid);
out_devx:
	अगर (req.flags & MLX5_IB_ALLOC_UCTX_DEVX)
		mlx5_ib_devx_destroy(dev, context->devx_uid);

out_uars:
	deallocate_uars(dev, context);

out_sys_pages:
	kमुक्त(bfregi->sys_pages);

out_count:
	kमुक्त(bfregi->count);

out_ctx:
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_ib_query_ucontext(काष्ठा ib_ucontext *ibcontext,
				  काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_alloc_ucontext_resp uctx_resp = अणुपूर्ण;
	पूर्णांक ret;

	ret = set_ucontext_resp(ibcontext, &uctx_resp);
	अगर (ret)
		वापस ret;

	uctx_resp.response_length =
		min_t(माप_प्रकार,
		      uverbs_attr_get_len(attrs,
				MLX5_IB_ATTR_QUERY_CONTEXT_RESP_UCTX),
		      माप(uctx_resp));

	ret = uverbs_copy_to_काष्ठा_or_zero(attrs,
					MLX5_IB_ATTR_QUERY_CONTEXT_RESP_UCTX,
					&uctx_resp,
					माप(uctx_resp));
	वापस ret;
पूर्ण

अटल व्योम mlx5_ib_dealloc_ucontext(काष्ठा ib_ucontext *ibcontext)
अणु
	काष्ठा mlx5_ib_ucontext *context = to_mucontext(ibcontext);
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibcontext->device);
	काष्ठा mlx5_bfreg_info *bfregi;

	bfregi = &context->bfregi;
	mlx5_ib_dealloc_transport_करोमुख्य(dev, context->tdn, context->devx_uid);

	अगर (context->devx_uid)
		mlx5_ib_devx_destroy(dev, context->devx_uid);

	deallocate_uars(dev, context);
	kमुक्त(bfregi->sys_pages);
	kमुक्त(bfregi->count);
पूर्ण

अटल phys_addr_t uar_index2pfn(काष्ठा mlx5_ib_dev *dev,
				 पूर्णांक uar_idx)
अणु
	पूर्णांक fw_uars_per_page;

	fw_uars_per_page = MLX5_CAP_GEN(dev->mdev, uar_4k) ? MLX5_UARS_IN_PAGE : 1;

	वापस (dev->mdev->bar_addr >> PAGE_SHIFT) + uar_idx / fw_uars_per_page;
पूर्ण

अटल u64 uar_index2paddress(काष्ठा mlx5_ib_dev *dev,
				 पूर्णांक uar_idx)
अणु
	अचिन्हित पूर्णांक fw_uars_per_page;

	fw_uars_per_page = MLX5_CAP_GEN(dev->mdev, uar_4k) ?
				MLX5_UARS_IN_PAGE : 1;

	वापस (dev->mdev->bar_addr + (uar_idx / fw_uars_per_page) * PAGE_SIZE);
पूर्ण

अटल पूर्णांक get_command(अचिन्हित दीर्घ offset)
अणु
	वापस (offset >> MLX5_IB_MMAP_CMD_SHIFT) & MLX5_IB_MMAP_CMD_MASK;
पूर्ण

अटल पूर्णांक get_arg(अचिन्हित दीर्घ offset)
अणु
	वापस offset & ((1 << MLX5_IB_MMAP_CMD_SHIFT) - 1);
पूर्ण

अटल पूर्णांक get_index(अचिन्हित दीर्घ offset)
अणु
	वापस get_arg(offset);
पूर्ण

/* Index resides in an extra byte to enable larger values than 255 */
अटल पूर्णांक get_extended_index(अचिन्हित दीर्घ offset)
अणु
	वापस get_arg(offset) | ((offset >> 16) & 0xff) << 8;
पूर्ण


अटल व्योम mlx5_ib_disassociate_ucontext(काष्ठा ib_ucontext *ibcontext)
अणु
पूर्ण

अटल अंतरभूत अक्षर *mmap_cmd2str(क्रमागत mlx5_ib_mmap_cmd cmd)
अणु
	चयन (cmd) अणु
	हाल MLX5_IB_MMAP_WC_PAGE:
		वापस "WC";
	हाल MLX5_IB_MMAP_REGULAR_PAGE:
		वापस "best effort WC";
	हाल MLX5_IB_MMAP_NC_PAGE:
		वापस "NC";
	हाल MLX5_IB_MMAP_DEVICE_MEM:
		वापस "Device Memory";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_ib_mmap_घड़ी_info_page(काष्ठा mlx5_ib_dev *dev,
					काष्ठा vm_area_काष्ठा *vma,
					काष्ठा mlx5_ib_ucontext *context)
अणु
	अगर ((vma->vm_end - vma->vm_start != PAGE_SIZE) ||
	    !(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	अगर (get_index(vma->vm_pgoff) != MLX5_IB_CLOCK_INFO_V1)
		वापस -EOPNOTSUPP;

	अगर (vma->vm_flags & (VM_WRITE | VM_EXEC))
		वापस -EPERM;
	vma->vm_flags &= ~VM_MAYWRITE;

	अगर (!dev->mdev->घड़ी_info)
		वापस -EOPNOTSUPP;

	वापस vm_insert_page(vma, vma->vm_start,
			      virt_to_page(dev->mdev->घड़ी_info));
पूर्ण

अटल व्योम mlx5_ib_mmap_मुक्त(काष्ठा rdma_user_mmap_entry *entry)
अणु
	काष्ठा mlx5_user_mmap_entry *mentry = to_mmmap(entry);
	काष्ठा mlx5_ib_dev *dev = to_mdev(entry->ucontext->device);
	काष्ठा mlx5_var_table *var_table = &dev->var_table;

	चयन (mentry->mmap_flag) अणु
	हाल MLX5_IB_MMAP_TYPE_MEMIC:
	हाल MLX5_IB_MMAP_TYPE_MEMIC_OP:
		mlx5_ib_dm_mmap_मुक्त(dev, mentry);
		अवरोध;
	हाल MLX5_IB_MMAP_TYPE_VAR:
		mutex_lock(&var_table->biपंचांगap_lock);
		clear_bit(mentry->page_idx, var_table->biपंचांगap);
		mutex_unlock(&var_table->biपंचांगap_lock);
		kमुक्त(mentry);
		अवरोध;
	हाल MLX5_IB_MMAP_TYPE_UAR_WC:
	हाल MLX5_IB_MMAP_TYPE_UAR_NC:
		mlx5_cmd_मुक्त_uar(dev->mdev, mentry->page_idx);
		kमुक्त(mentry);
		अवरोध;
	शेष:
		WARN_ON(true);
	पूर्ण
पूर्ण

अटल पूर्णांक uar_mmap(काष्ठा mlx5_ib_dev *dev, क्रमागत mlx5_ib_mmap_cmd cmd,
		    काष्ठा vm_area_काष्ठा *vma,
		    काष्ठा mlx5_ib_ucontext *context)
अणु
	काष्ठा mlx5_bfreg_info *bfregi = &context->bfregi;
	पूर्णांक err;
	अचिन्हित दीर्घ idx;
	phys_addr_t pfn;
	pgprot_t prot;
	u32 bfreg_dyn_idx = 0;
	u32 uar_index;
	पूर्णांक dyn_uar = (cmd == MLX5_IB_MMAP_ALLOC_WC);
	पूर्णांक max_valid_idx = dyn_uar ? bfregi->num_sys_pages :
				bfregi->num_अटल_sys_pages;

	अगर (bfregi->lib_uar_dyn)
		वापस -EINVAL;

	अगर (vma->vm_end - vma->vm_start != PAGE_SIZE)
		वापस -EINVAL;

	अगर (dyn_uar)
		idx = get_extended_index(vma->vm_pgoff) + bfregi->num_अटल_sys_pages;
	अन्यथा
		idx = get_index(vma->vm_pgoff);

	अगर (idx >= max_valid_idx) अणु
		mlx5_ib_warn(dev, "invalid uar index %lu, max=%d\n",
			     idx, max_valid_idx);
		वापस -EINVAL;
	पूर्ण

	चयन (cmd) अणु
	हाल MLX5_IB_MMAP_WC_PAGE:
	हाल MLX5_IB_MMAP_ALLOC_WC:
	हाल MLX5_IB_MMAP_REGULAR_PAGE:
		/* For MLX5_IB_MMAP_REGULAR_PAGE करो the best efक्रमt to get WC */
		prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
		अवरोध;
	हाल MLX5_IB_MMAP_NC_PAGE:
		prot = pgprot_noncached(vma->vm_page_prot);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (dyn_uar) अणु
		पूर्णांक uars_per_page;

		uars_per_page = get_uars_per_sys_page(dev, bfregi->lib_uar_4k);
		bfreg_dyn_idx = idx * (uars_per_page * MLX5_NON_FP_BFREGS_PER_UAR);
		अगर (bfreg_dyn_idx >= bfregi->total_num_bfregs) अणु
			mlx5_ib_warn(dev, "invalid bfreg_dyn_idx %u, max=%u\n",
				     bfreg_dyn_idx, bfregi->total_num_bfregs);
			वापस -EINVAL;
		पूर्ण

		mutex_lock(&bfregi->lock);
		/* Fail अगर uar alपढ़ोy allocated, first bfreg index of each
		 * page holds its count.
		 */
		अगर (bfregi->count[bfreg_dyn_idx]) अणु
			mlx5_ib_warn(dev, "wrong offset, idx %lu is busy, bfregn=%u\n", idx, bfreg_dyn_idx);
			mutex_unlock(&bfregi->lock);
			वापस -EINVAL;
		पूर्ण

		bfregi->count[bfreg_dyn_idx]++;
		mutex_unlock(&bfregi->lock);

		err = mlx5_cmd_alloc_uar(dev->mdev, &uar_index);
		अगर (err) अणु
			mlx5_ib_warn(dev, "UAR alloc failed\n");
			जाओ मुक्त_bfreg;
		पूर्ण
	पूर्ण अन्यथा अणु
		uar_index = bfregi->sys_pages[idx];
	पूर्ण

	pfn = uar_index2pfn(dev, uar_index);
	mlx5_ib_dbg(dev, "uar idx 0x%lx, pfn %pa\n", idx, &pfn);

	err = rdma_user_mmap_io(&context->ibucontext, vma, pfn, PAGE_SIZE,
				prot, शून्य);
	अगर (err) अणु
		mlx5_ib_err(dev,
			    "rdma_user_mmap_io failed with error=%d, mmap_cmd=%s\n",
			    err, mmap_cmd2str(cmd));
		जाओ err;
	पूर्ण

	अगर (dyn_uar)
		bfregi->sys_pages[idx] = uar_index;
	वापस 0;

err:
	अगर (!dyn_uar)
		वापस err;

	mlx5_cmd_मुक्त_uar(dev->mdev, idx);

मुक्त_bfreg:
	mlx5_ib_मुक्त_bfreg(dev, bfregi, bfreg_dyn_idx);

	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ mlx5_vma_to_pgoff(काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ idx;
	u8 command;

	command = get_command(vma->vm_pgoff);
	idx = get_extended_index(vma->vm_pgoff);

	वापस (command << 16 | idx);
पूर्ण

अटल पूर्णांक mlx5_ib_mmap_offset(काष्ठा mlx5_ib_dev *dev,
			       काष्ठा vm_area_काष्ठा *vma,
			       काष्ठा ib_ucontext *ucontext)
अणु
	काष्ठा mlx5_user_mmap_entry *mentry;
	काष्ठा rdma_user_mmap_entry *entry;
	अचिन्हित दीर्घ pgoff;
	pgprot_t prot;
	phys_addr_t pfn;
	पूर्णांक ret;

	pgoff = mlx5_vma_to_pgoff(vma);
	entry = rdma_user_mmap_entry_get_pgoff(ucontext, pgoff);
	अगर (!entry)
		वापस -EINVAL;

	mentry = to_mmmap(entry);
	pfn = (mentry->address >> PAGE_SHIFT);
	अगर (mentry->mmap_flag == MLX5_IB_MMAP_TYPE_VAR ||
	    mentry->mmap_flag == MLX5_IB_MMAP_TYPE_UAR_NC)
		prot = pgprot_noncached(vma->vm_page_prot);
	अन्यथा
		prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
	ret = rdma_user_mmap_io(ucontext, vma, pfn,
				entry->npages * PAGE_SIZE,
				prot,
				entry);
	rdma_user_mmap_entry_put(&mentry->rdma_entry);
	वापस ret;
पूर्ण

अटल u64 mlx5_entry_to_mmap_offset(काष्ठा mlx5_user_mmap_entry *entry)
अणु
	u64 cmd = (entry->rdma_entry.start_pgoff >> 16) & 0xFFFF;
	u64 index = entry->rdma_entry.start_pgoff & 0xFFFF;

	वापस (((index >> 8) << 16) | (cmd << MLX5_IB_MMAP_CMD_SHIFT) |
		(index & 0xFF)) << PAGE_SHIFT;
पूर्ण

अटल पूर्णांक mlx5_ib_mmap(काष्ठा ib_ucontext *ibcontext, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mlx5_ib_ucontext *context = to_mucontext(ibcontext);
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibcontext->device);
	अचिन्हित दीर्घ command;
	phys_addr_t pfn;

	command = get_command(vma->vm_pgoff);
	चयन (command) अणु
	हाल MLX5_IB_MMAP_WC_PAGE:
	हाल MLX5_IB_MMAP_ALLOC_WC:
		अगर (!dev->wc_support)
			वापस -EPERM;
		fallthrough;
	हाल MLX5_IB_MMAP_NC_PAGE:
	हाल MLX5_IB_MMAP_REGULAR_PAGE:
		वापस uar_mmap(dev, command, vma, context);

	हाल MLX5_IB_MMAP_GET_CONTIGUOUS_PAGES:
		वापस -ENOSYS;

	हाल MLX5_IB_MMAP_CORE_CLOCK:
		अगर (vma->vm_end - vma->vm_start != PAGE_SIZE)
			वापस -EINVAL;

		अगर (vma->vm_flags & VM_WRITE)
			वापस -EPERM;
		vma->vm_flags &= ~VM_MAYWRITE;

		/* Don't expose to user-space information it shouldn't have */
		अगर (PAGE_SIZE > 4096)
			वापस -EOPNOTSUPP;

		pfn = (dev->mdev->iseg_base +
		       दुरत्व(काष्ठा mlx5_init_seg, पूर्णांकernal_समयr_h)) >>
			PAGE_SHIFT;
		वापस rdma_user_mmap_io(&context->ibucontext, vma, pfn,
					 PAGE_SIZE,
					 pgprot_noncached(vma->vm_page_prot),
					 शून्य);
	हाल MLX5_IB_MMAP_CLOCK_INFO:
		वापस mlx5_ib_mmap_घड़ी_info_page(dev, vma, context);

	शेष:
		वापस mlx5_ib_mmap_offset(dev, vma, ibcontext);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_pd *pd = to_mpd(ibpd);
	काष्ठा ib_device *ibdev = ibpd->device;
	काष्ठा mlx5_ib_alloc_pd_resp resp;
	पूर्णांक err;
	u32 out[MLX5_ST_SZ_DW(alloc_pd_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_pd_in)] = अणुपूर्ण;
	u16 uid = 0;
	काष्ठा mlx5_ib_ucontext *context = rdma_udata_to_drv_context(
		udata, काष्ठा mlx5_ib_ucontext, ibucontext);

	uid = context ? context->devx_uid : 0;
	MLX5_SET(alloc_pd_in, in, opcode, MLX5_CMD_OP_ALLOC_PD);
	MLX5_SET(alloc_pd_in, in, uid, uid);
	err = mlx5_cmd_exec_inout(to_mdev(ibdev)->mdev, alloc_pd, in, out);
	अगर (err)
		वापस err;

	pd->pdn = MLX5_GET(alloc_pd_out, out, pd);
	pd->uid = uid;
	अगर (udata) अणु
		resp.pdn = pd->pdn;
		अगर (ib_copy_to_udata(udata, &resp, माप(resp))) अणु
			mlx5_cmd_dealloc_pd(to_mdev(ibdev)->mdev, pd->pdn, uid);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *mdev = to_mdev(pd->device);
	काष्ठा mlx5_ib_pd *mpd = to_mpd(pd);

	वापस mlx5_cmd_dealloc_pd(mdev->mdev, mpd->pdn, mpd->uid);
पूर्ण

अटल पूर्णांक mlx5_ib_mcg_attach(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibqp->device);
	काष्ठा mlx5_ib_qp *mqp = to_mqp(ibqp);
	पूर्णांक err;
	u16 uid;

	uid = ibqp->pd ?
		to_mpd(ibqp->pd)->uid : 0;

	अगर (mqp->flags & IB_QP_CREATE_SOURCE_QPN) अणु
		mlx5_ib_dbg(dev, "Attaching a multi cast group to underlay QP is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	err = mlx5_cmd_attach_mcg(dev->mdev, gid, ibqp->qp_num, uid);
	अगर (err)
		mlx5_ib_warn(dev, "failed attaching QPN 0x%x, MGID %pI6\n",
			     ibqp->qp_num, gid->raw);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_ib_mcg_detach(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibqp->device);
	पूर्णांक err;
	u16 uid;

	uid = ibqp->pd ?
		to_mpd(ibqp->pd)->uid : 0;
	err = mlx5_cmd_detach_mcg(dev->mdev, gid, ibqp->qp_num, uid);
	अगर (err)
		mlx5_ib_warn(dev, "failed detaching QPN 0x%x, MGID %pI6\n",
			     ibqp->qp_num, gid->raw);

	वापस err;
पूर्ण

अटल पूर्णांक init_node_data(काष्ठा mlx5_ib_dev *dev)
अणु
	पूर्णांक err;

	err = mlx5_query_node_desc(dev, dev->ib_dev.node_desc);
	अगर (err)
		वापस err;

	dev->mdev->rev_id = dev->mdev->pdev->revision;

	वापस mlx5_query_node_guid(dev, &dev->ib_dev.node_guid);
पूर्ण

अटल sमाप_प्रकार fw_pages_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx5_ib_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mlx5_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "%d\n", dev->mdev->priv.fw_pages);
पूर्ण
अटल DEVICE_ATTR_RO(fw_pages);

अटल sमाप_प्रकार reg_pages_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx5_ib_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mlx5_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "%d\n", atomic_पढ़ो(&dev->mdev->priv.reg_pages));
पूर्ण
अटल DEVICE_ATTR_RO(reg_pages);

अटल sमाप_प्रकार hca_type_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx5_ib_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mlx5_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "MT%d\n", dev->mdev->pdev->device);
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);

अटल sमाप_प्रकार hw_rev_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx5_ib_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mlx5_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "%x\n", dev->mdev->rev_id);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार board_id_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx5_ib_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mlx5_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "%.*s\n", MLX5_BOARD_ID_LEN,
			  dev->mdev->board_id);
पूर्ण
अटल DEVICE_ATTR_RO(board_id);

अटल काष्ठा attribute *mlx5_class_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	&dev_attr_board_id.attr,
	&dev_attr_fw_pages.attr,
	&dev_attr_reg_pages.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mlx5_attr_group = अणु
	.attrs = mlx5_class_attributes,
पूर्ण;

अटल व्योम pkey_change_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_ib_port_resources *ports =
		container_of(work, काष्ठा mlx5_ib_port_resources,
			     pkey_change_work);

	mlx5_ib_gsi_pkey_change(ports->gsi);
पूर्ण

अटल व्योम mlx5_ib_handle_पूर्णांकernal_error(काष्ठा mlx5_ib_dev *ibdev)
अणु
	काष्ठा mlx5_ib_qp *mqp;
	काष्ठा mlx5_ib_cq *send_mcq, *recv_mcq;
	काष्ठा mlx5_core_cq *mcq;
	काष्ठा list_head cq_armed_list;
	अचिन्हित दीर्घ flags_qp;
	अचिन्हित दीर्घ flags_cq;
	अचिन्हित दीर्घ flags;

	INIT_LIST_HEAD(&cq_armed_list);

	/* Go over qp list reside on that ibdev, sync with create/destroy qp.*/
	spin_lock_irqsave(&ibdev->reset_flow_resource_lock, flags);
	list_क्रम_each_entry(mqp, &ibdev->qp_list, qps_list) अणु
		spin_lock_irqsave(&mqp->sq.lock, flags_qp);
		अगर (mqp->sq.tail != mqp->sq.head) अणु
			send_mcq = to_mcq(mqp->ibqp.send_cq);
			spin_lock_irqsave(&send_mcq->lock, flags_cq);
			अगर (send_mcq->mcq.comp &&
			    mqp->ibqp.send_cq->comp_handler) अणु
				अगर (!send_mcq->mcq.reset_notअगरy_added) अणु
					send_mcq->mcq.reset_notअगरy_added = 1;
					list_add_tail(&send_mcq->mcq.reset_notअगरy,
						      &cq_armed_list);
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(&send_mcq->lock, flags_cq);
		पूर्ण
		spin_unlock_irqrestore(&mqp->sq.lock, flags_qp);
		spin_lock_irqsave(&mqp->rq.lock, flags_qp);
		/* no handling is needed क्रम SRQ */
		अगर (!mqp->ibqp.srq) अणु
			अगर (mqp->rq.tail != mqp->rq.head) अणु
				recv_mcq = to_mcq(mqp->ibqp.recv_cq);
				spin_lock_irqsave(&recv_mcq->lock, flags_cq);
				अगर (recv_mcq->mcq.comp &&
				    mqp->ibqp.recv_cq->comp_handler) अणु
					अगर (!recv_mcq->mcq.reset_notअगरy_added) अणु
						recv_mcq->mcq.reset_notअगरy_added = 1;
						list_add_tail(&recv_mcq->mcq.reset_notअगरy,
							      &cq_armed_list);
					पूर्ण
				पूर्ण
				spin_unlock_irqrestore(&recv_mcq->lock,
						       flags_cq);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&mqp->rq.lock, flags_qp);
	पूर्ण
	/*At that poपूर्णांक all inflight post send were put to be executed as of we
	 * lock/unlock above locks Now need to arm all involved CQs.
	 */
	list_क्रम_each_entry(mcq, &cq_armed_list, reset_notअगरy) अणु
		mcq->comp(mcq, शून्य);
	पूर्ण
	spin_unlock_irqrestore(&ibdev->reset_flow_resource_lock, flags);
पूर्ण

अटल व्योम delay_drop_handler(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक err;
	काष्ठा mlx5_ib_delay_drop *delay_drop =
		container_of(work, काष्ठा mlx5_ib_delay_drop,
			     delay_drop_work);

	atomic_inc(&delay_drop->events_cnt);

	mutex_lock(&delay_drop->lock);
	err = mlx5_core_set_delay_drop(delay_drop->dev, delay_drop->समयout);
	अगर (err) अणु
		mlx5_ib_warn(delay_drop->dev, "Failed to set delay drop, timeout=%u\n",
			     delay_drop->समयout);
		delay_drop->activate = false;
	पूर्ण
	mutex_unlock(&delay_drop->lock);
पूर्ण

अटल व्योम handle_general_event(काष्ठा mlx5_ib_dev *ibdev, काष्ठा mlx5_eqe *eqe,
				 काष्ठा ib_event *ibev)
अणु
	u32 port = (eqe->data.port.port >> 4) & 0xf;

	चयन (eqe->sub_type) अणु
	हाल MLX5_GENERAL_SUBTYPE_DELAY_DROP_TIMEOUT:
		अगर (mlx5_ib_port_link_layer(&ibdev->ib_dev, port) ==
					    IB_LINK_LAYER_ETHERNET)
			schedule_work(&ibdev->delay_drop.delay_drop_work);
		अवरोध;
	शेष: /* करो nothing */
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक handle_port_change(काष्ठा mlx5_ib_dev *ibdev, काष्ठा mlx5_eqe *eqe,
			      काष्ठा ib_event *ibev)
अणु
	u32 port = (eqe->data.port.port >> 4) & 0xf;

	ibev->element.port_num = port;

	चयन (eqe->sub_type) अणु
	हाल MLX5_PORT_CHANGE_SUBTYPE_ACTIVE:
	हाल MLX5_PORT_CHANGE_SUBTYPE_DOWN:
	हाल MLX5_PORT_CHANGE_SUBTYPE_INITIALIZED:
		/* In RoCE, port up/करोwn events are handled in
		 * mlx5_netdev_event().
		 */
		अगर (mlx5_ib_port_link_layer(&ibdev->ib_dev, port) ==
					    IB_LINK_LAYER_ETHERNET)
			वापस -EINVAL;

		ibev->event = (eqe->sub_type == MLX5_PORT_CHANGE_SUBTYPE_ACTIVE) ?
				IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;
		अवरोध;

	हाल MLX5_PORT_CHANGE_SUBTYPE_LID:
		ibev->event = IB_EVENT_LID_CHANGE;
		अवरोध;

	हाल MLX5_PORT_CHANGE_SUBTYPE_PKEY:
		ibev->event = IB_EVENT_PKEY_CHANGE;
		schedule_work(&ibdev->devr.ports[port - 1].pkey_change_work);
		अवरोध;

	हाल MLX5_PORT_CHANGE_SUBTYPE_GUID:
		ibev->event = IB_EVENT_GID_CHANGE;
		अवरोध;

	हाल MLX5_PORT_CHANGE_SUBTYPE_CLIENT_REREG:
		ibev->event = IB_EVENT_CLIENT_REREGISTER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx5_ib_handle_event(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा mlx5_ib_event_work *work =
		container_of(_work, काष्ठा mlx5_ib_event_work, work);
	काष्ठा mlx5_ib_dev *ibdev;
	काष्ठा ib_event ibev;
	bool fatal = false;

	अगर (work->is_slave) अणु
		ibdev = mlx5_ib_get_ibdev_from_mpi(work->mpi);
		अगर (!ibdev)
			जाओ out;
	पूर्ण अन्यथा अणु
		ibdev = work->dev;
	पूर्ण

	चयन (work->event) अणु
	हाल MLX5_DEV_EVENT_SYS_ERROR:
		ibev.event = IB_EVENT_DEVICE_FATAL;
		mlx5_ib_handle_पूर्णांकernal_error(ibdev);
		ibev.element.port_num  = (u8)(अचिन्हित दीर्घ)work->param;
		fatal = true;
		अवरोध;
	हाल MLX5_EVENT_TYPE_PORT_CHANGE:
		अगर (handle_port_change(ibdev, work->param, &ibev))
			जाओ out;
		अवरोध;
	हाल MLX5_EVENT_TYPE_GENERAL_EVENT:
		handle_general_event(ibdev, work->param, &ibev);
		fallthrough;
	शेष:
		जाओ out;
	पूर्ण

	ibev.device = &ibdev->ib_dev;

	अगर (!rdma_is_port_valid(&ibdev->ib_dev, ibev.element.port_num)) अणु
		mlx5_ib_warn(ibdev, "warning: event on port %d\n",  ibev.element.port_num);
		जाओ out;
	पूर्ण

	अगर (ibdev->ib_active)
		ib_dispatch_event(&ibev);

	अगर (fatal)
		ibdev->ib_active = false;
out:
	kमुक्त(work);
पूर्ण

अटल पूर्णांक mlx5_ib_event(काष्ठा notअगरier_block *nb,
			 अचिन्हित दीर्घ event, व्योम *param)
अणु
	काष्ठा mlx5_ib_event_work *work;

	work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
	अगर (!work)
		वापस NOTIFY_DONE;

	INIT_WORK(&work->work, mlx5_ib_handle_event);
	work->dev = container_of(nb, काष्ठा mlx5_ib_dev, mdev_events);
	work->is_slave = false;
	work->param = param;
	work->event = event;

	queue_work(mlx5_ib_event_wq, &work->work);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक mlx5_ib_event_slave_port(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ event, व्योम *param)
अणु
	काष्ठा mlx5_ib_event_work *work;

	work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
	अगर (!work)
		वापस NOTIFY_DONE;

	INIT_WORK(&work->work, mlx5_ib_handle_event);
	work->mpi = container_of(nb, काष्ठा mlx5_ib_multiport_info, mdev_events);
	work->is_slave = true;
	work->param = param;
	work->event = event;
	queue_work(mlx5_ib_event_wq, &work->work);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक set_has_smi_cap(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_hca_vport_context vport_ctx;
	पूर्णांक err;
	पूर्णांक port;

	क्रम (port = 1; port <= ARRAY_SIZE(dev->port_caps); port++) अणु
		dev->port_caps[port - 1].has_smi = false;
		अगर (MLX5_CAP_GEN(dev->mdev, port_type) ==
		    MLX5_CAP_PORT_TYPE_IB) अणु
			अगर (MLX5_CAP_GEN(dev->mdev, ib_virt)) अणु
				err = mlx5_query_hca_vport_context(dev->mdev, 0,
								   port, 0,
								   &vport_ctx);
				अगर (err) अणु
					mlx5_ib_err(dev, "query_hca_vport_context for port=%d failed %d\n",
						    port, err);
					वापस err;
				पूर्ण
				dev->port_caps[port - 1].has_smi =
					vport_ctx.has_smi;
			पूर्ण अन्यथा अणु
				dev->port_caps[port - 1].has_smi = true;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम get_ext_port_caps(काष्ठा mlx5_ib_dev *dev)
अणु
	अचिन्हित पूर्णांक port;

	rdma_क्रम_each_port (&dev->ib_dev, port)
		mlx5_query_ext_port_caps(dev, port);
पूर्ण

अटल u8 mlx5_get_umr_fence(u8 umr_fence_cap)
अणु
	चयन (umr_fence_cap) अणु
	हाल MLX5_CAP_UMR_FENCE_NONE:
		वापस MLX5_FENCE_MODE_NONE;
	हाल MLX5_CAP_UMR_FENCE_SMALL:
		वापस MLX5_FENCE_MODE_INITIATOR_SMALL;
	शेष:
		वापस MLX5_FENCE_MODE_STRONG_ORDERING;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_ib_dev_res_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_ib_resources *devr = &dev->devr;
	काष्ठा ib_srq_init_attr attr;
	काष्ठा ib_device *ibdev;
	काष्ठा ib_cq_init_attr cq_attr = अणु.cqe = 1पूर्ण;
	पूर्णांक port;
	पूर्णांक ret = 0;

	ibdev = &dev->ib_dev;

	अगर (!MLX5_CAP_GEN(dev->mdev, xrc))
		वापस -EOPNOTSUPP;

	mutex_init(&devr->mutex);

	devr->p0 = rdma_zalloc_drv_obj(ibdev, ib_pd);
	अगर (!devr->p0)
		वापस -ENOMEM;

	devr->p0->device  = ibdev;
	devr->p0->uobject = शून्य;
	atomic_set(&devr->p0->usecnt, 0);

	ret = mlx5_ib_alloc_pd(devr->p0, शून्य);
	अगर (ret)
		जाओ error0;

	devr->c0 = rdma_zalloc_drv_obj(ibdev, ib_cq);
	अगर (!devr->c0) अणु
		ret = -ENOMEM;
		जाओ error1;
	पूर्ण

	devr->c0->device = &dev->ib_dev;
	atomic_set(&devr->c0->usecnt, 0);

	ret = mlx5_ib_create_cq(devr->c0, &cq_attr, शून्य);
	अगर (ret)
		जाओ err_create_cq;

	ret = mlx5_cmd_xrcd_alloc(dev->mdev, &devr->xrcdn0, 0);
	अगर (ret)
		जाओ error2;

	ret = mlx5_cmd_xrcd_alloc(dev->mdev, &devr->xrcdn1, 0);
	अगर (ret)
		जाओ error3;

	स_रखो(&attr, 0, माप(attr));
	attr.attr.max_sge = 1;
	attr.attr.max_wr = 1;
	attr.srq_type = IB_SRQT_XRC;
	attr.ext.cq = devr->c0;

	devr->s0 = rdma_zalloc_drv_obj(ibdev, ib_srq);
	अगर (!devr->s0) अणु
		ret = -ENOMEM;
		जाओ error4;
	पूर्ण

	devr->s0->device	= &dev->ib_dev;
	devr->s0->pd		= devr->p0;
	devr->s0->srq_type      = IB_SRQT_XRC;
	devr->s0->ext.cq	= devr->c0;
	ret = mlx5_ib_create_srq(devr->s0, &attr, शून्य);
	अगर (ret)
		जाओ err_create;

	atomic_inc(&devr->s0->ext.cq->usecnt);
	atomic_inc(&devr->p0->usecnt);
	atomic_set(&devr->s0->usecnt, 0);

	स_रखो(&attr, 0, माप(attr));
	attr.attr.max_sge = 1;
	attr.attr.max_wr = 1;
	attr.srq_type = IB_SRQT_BASIC;
	devr->s1 = rdma_zalloc_drv_obj(ibdev, ib_srq);
	अगर (!devr->s1) अणु
		ret = -ENOMEM;
		जाओ error5;
	पूर्ण

	devr->s1->device	= &dev->ib_dev;
	devr->s1->pd		= devr->p0;
	devr->s1->srq_type      = IB_SRQT_BASIC;
	devr->s1->ext.cq	= devr->c0;

	ret = mlx5_ib_create_srq(devr->s1, &attr, शून्य);
	अगर (ret)
		जाओ error6;

	atomic_inc(&devr->p0->usecnt);
	atomic_set(&devr->s1->usecnt, 0);

	क्रम (port = 0; port < ARRAY_SIZE(devr->ports); ++port)
		INIT_WORK(&devr->ports[port].pkey_change_work,
			  pkey_change_handler);

	वापस 0;

error6:
	kमुक्त(devr->s1);
error5:
	mlx5_ib_destroy_srq(devr->s0, शून्य);
err_create:
	kमुक्त(devr->s0);
error4:
	mlx5_cmd_xrcd_dealloc(dev->mdev, devr->xrcdn1, 0);
error3:
	mlx5_cmd_xrcd_dealloc(dev->mdev, devr->xrcdn0, 0);
error2:
	mlx5_ib_destroy_cq(devr->c0, शून्य);
err_create_cq:
	kमुक्त(devr->c0);
error1:
	mlx5_ib_dealloc_pd(devr->p0, शून्य);
error0:
	kमुक्त(devr->p0);
	वापस ret;
पूर्ण

अटल व्योम mlx5_ib_dev_res_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_ib_resources *devr = &dev->devr;
	पूर्णांक port;

	mlx5_ib_destroy_srq(devr->s1, शून्य);
	kमुक्त(devr->s1);
	mlx5_ib_destroy_srq(devr->s0, शून्य);
	kमुक्त(devr->s0);
	mlx5_cmd_xrcd_dealloc(dev->mdev, devr->xrcdn1, 0);
	mlx5_cmd_xrcd_dealloc(dev->mdev, devr->xrcdn0, 0);
	mlx5_ib_destroy_cq(devr->c0, शून्य);
	kमुक्त(devr->c0);
	mlx5_ib_dealloc_pd(devr->p0, शून्य);
	kमुक्त(devr->p0);

	/* Make sure no change P_Key work items are still executing */
	क्रम (port = 0; port < ARRAY_SIZE(devr->ports); ++port)
		cancel_work_sync(&devr->ports[port].pkey_change_work);
पूर्ण

अटल u32 get_core_cap_flags(काष्ठा ib_device *ibdev,
			      काष्ठा mlx5_hca_vport_context *rep)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	क्रमागत rdma_link_layer ll = mlx5_ib_port_link_layer(ibdev, 1);
	u8 l3_type_cap = MLX5_CAP_ROCE(dev->mdev, l3_type);
	u8 roce_version_cap = MLX5_CAP_ROCE(dev->mdev, roce_version);
	bool raw_support = !mlx5_core_mp_enabled(dev->mdev);
	u32 ret = 0;

	अगर (rep->grh_required)
		ret |= RDMA_CORE_CAP_IB_GRH_REQUIRED;

	अगर (ll == IB_LINK_LAYER_INFINIBAND)
		वापस ret | RDMA_CORE_PORT_IBA_IB;

	अगर (raw_support)
		ret |= RDMA_CORE_PORT_RAW_PACKET;

	अगर (!(l3_type_cap & MLX5_ROCE_L3_TYPE_IPV4_CAP))
		वापस ret;

	अगर (!(l3_type_cap & MLX5_ROCE_L3_TYPE_IPV6_CAP))
		वापस ret;

	अगर (roce_version_cap & MLX5_ROCE_VERSION_1_CAP)
		ret |= RDMA_CORE_PORT_IBA_ROCE;

	अगर (roce_version_cap & MLX5_ROCE_VERSION_2_CAP)
		ret |= RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP;

	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			       काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	क्रमागत rdma_link_layer ll = mlx5_ib_port_link_layer(ibdev, port_num);
	काष्ठा mlx5_hca_vport_context rep = अणु0पूर्ण;
	पूर्णांक err;

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	अगर (ll == IB_LINK_LAYER_INFINIBAND) अणु
		err = mlx5_query_hca_vport_context(dev->mdev, 0, port_num, 0,
						   &rep);
		अगर (err)
			वापस err;
	पूर्ण

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->core_cap_flags = get_core_cap_flags(ibdev, &rep);
	immutable->max_mad_size = IB_MGMT_MAD_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_port_rep_immutable(काष्ठा ib_device *ibdev, u32 port_num,
				   काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	पूर्णांक err;

	immutable->core_cap_flags = RDMA_CORE_PORT_RAW_PACKET;

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->core_cap_flags = RDMA_CORE_PORT_RAW_PACKET;

	वापस 0;
पूर्ण

अटल व्योम get_dev_fw_str(काष्ठा ib_device *ibdev, अक्षर *str)
अणु
	काष्ठा mlx5_ib_dev *dev =
		container_of(ibdev, काष्ठा mlx5_ib_dev, ib_dev);
	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%d.%d.%04d",
		 fw_rev_maj(dev->mdev), fw_rev_min(dev->mdev),
		 fw_rev_sub(dev->mdev));
पूर्ण

अटल पूर्णांक mlx5_eth_lag_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_flow_namespace *ns = mlx5_get_flow_namespace(mdev,
								 MLX5_FLOW_NAMESPACE_LAG);
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक err;

	अगर (!ns || !mlx5_lag_is_roce(mdev))
		वापस 0;

	err = mlx5_cmd_create_vport_lag(mdev);
	अगर (err)
		वापस err;

	ft = mlx5_create_lag_demux_flow_table(ns, 0, 0);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		जाओ err_destroy_vport_lag;
	पूर्ण

	dev->flow_db->lag_demux_ft = ft;
	dev->lag_active = true;
	वापस 0;

err_destroy_vport_lag:
	mlx5_cmd_destroy_vport_lag(mdev);
	वापस err;
पूर्ण

अटल व्योम mlx5_eth_lag_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;

	अगर (dev->lag_active) अणु
		dev->lag_active = false;

		mlx5_destroy_flow_table(dev->flow_db->lag_demux_ft);
		dev->flow_db->lag_demux_ft = शून्य;

		mlx5_cmd_destroy_vport_lag(mdev);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_add_netdev_notअगरier(काष्ठा mlx5_ib_dev *dev, u32 port_num)
अणु
	पूर्णांक err;

	dev->port[port_num].roce.nb.notअगरier_call = mlx5_netdev_event;
	err = रेजिस्टर_netdevice_notअगरier(&dev->port[port_num].roce.nb);
	अगर (err) अणु
		dev->port[port_num].roce.nb.notअगरier_call = शून्य;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx5_हटाओ_netdev_notअगरier(काष्ठा mlx5_ib_dev *dev, u32 port_num)
अणु
	अगर (dev->port[port_num].roce.nb.notअगरier_call) अणु
		unरेजिस्टर_netdevice_notअगरier(&dev->port[port_num].roce.nb);
		dev->port[port_num].roce.nb.notअगरier_call = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_enable_eth(काष्ठा mlx5_ib_dev *dev)
अणु
	पूर्णांक err;

	err = mlx5_nic_vport_enable_roce(dev->mdev);
	अगर (err)
		वापस err;

	err = mlx5_eth_lag_init(dev);
	अगर (err)
		जाओ err_disable_roce;

	वापस 0;

err_disable_roce:
	mlx5_nic_vport_disable_roce(dev->mdev);

	वापस err;
पूर्ण

अटल व्योम mlx5_disable_eth(काष्ठा mlx5_ib_dev *dev)
अणु
	mlx5_eth_lag_cleanup(dev);
	mlx5_nic_vport_disable_roce(dev->mdev);
पूर्ण

अटल पूर्णांक mlx5_ib_rn_get_params(काष्ठा ib_device *device, u32 port_num,
				 क्रमागत rdma_netdev_t type,
				 काष्ठा rdma_netdev_alloc_params *params)
अणु
	अगर (type != RDMA_NETDEV_IPOIB)
		वापस -EOPNOTSUPP;

	वापस mlx5_rdma_rn_get_params(to_mdev(device)->mdev, device, params);
पूर्ण

अटल sमाप_प्रकार delay_drop_समयout_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
				       माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mlx5_ib_delay_drop *delay_drop = filp->निजी_data;
	अक्षर lbuf[20];
	पूर्णांक len;

	len = snम_लिखो(lbuf, माप(lbuf), "%u\n", delay_drop->समयout);
	वापस simple_पढ़ो_from_buffer(buf, count, pos, lbuf, len);
पूर्ण

अटल sमाप_प्रकार delay_drop_समयout_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mlx5_ib_delay_drop *delay_drop = filp->निजी_data;
	u32 समयout;
	u32 var;

	अगर (kstrtouपूर्णांक_from_user(buf, count, 0, &var))
		वापस -EFAULT;

	समयout = min_t(u32, roundup(var, 100), MLX5_MAX_DELAY_DROP_TIMEOUT_MS *
			1000);
	अगर (समयout != var)
		mlx5_ib_dbg(delay_drop->dev, "Round delay drop timeout to %u usec\n",
			    समयout);

	delay_drop->समयout = समयout;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_delay_drop_समयout = अणु
	.owner	= THIS_MODULE,
	.खोलो	= simple_खोलो,
	.ग_लिखो	= delay_drop_समयout_ग_लिखो,
	.पढ़ो	= delay_drop_समयout_पढ़ो,
पूर्ण;

अटल व्योम mlx5_ib_unbind_slave_port(काष्ठा mlx5_ib_dev *ibdev,
				      काष्ठा mlx5_ib_multiport_info *mpi)
अणु
	u32 port_num = mlx5_core_native_port_num(mpi->mdev) - 1;
	काष्ठा mlx5_ib_port *port = &ibdev->port[port_num];
	पूर्णांक comps;
	पूर्णांक err;
	पूर्णांक i;

	lockdep_निश्चित_held(&mlx5_ib_multiport_mutex);

	mlx5_ib_cleanup_cong_debugfs(ibdev, port_num);

	spin_lock(&port->mp.mpi_lock);
	अगर (!mpi->ibdev) अणु
		spin_unlock(&port->mp.mpi_lock);
		वापस;
	पूर्ण

	mpi->ibdev = शून्य;

	spin_unlock(&port->mp.mpi_lock);
	अगर (mpi->mdev_events.notअगरier_call)
		mlx5_notअगरier_unरेजिस्टर(mpi->mdev, &mpi->mdev_events);
	mpi->mdev_events.notअगरier_call = शून्य;
	mlx5_हटाओ_netdev_notअगरier(ibdev, port_num);
	spin_lock(&port->mp.mpi_lock);

	comps = mpi->mdev_refcnt;
	अगर (comps) अणु
		mpi->unaffiliate = true;
		init_completion(&mpi->unref_comp);
		spin_unlock(&port->mp.mpi_lock);

		क्रम (i = 0; i < comps; i++)
			रुको_क्रम_completion(&mpi->unref_comp);

		spin_lock(&port->mp.mpi_lock);
		mpi->unaffiliate = false;
	पूर्ण

	port->mp.mpi = शून्य;

	list_add_tail(&mpi->list, &mlx5_ib_unaffiliated_port_list);

	spin_unlock(&port->mp.mpi_lock);

	err = mlx5_nic_vport_unaffiliate_multiport(mpi->mdev);

	mlx5_ib_dbg(ibdev, "unaffiliated port %u\n", port_num + 1);
	/* Log an error, still needed to cleanup the poपूर्णांकers and add
	 * it back to the list.
	 */
	अगर (err)
		mlx5_ib_err(ibdev, "Failed to unaffiliate port %u\n",
			    port_num + 1);

	ibdev->port[port_num].roce.last_port_state = IB_PORT_DOWN;
पूर्ण

अटल bool mlx5_ib_bind_slave_port(काष्ठा mlx5_ib_dev *ibdev,
				    काष्ठा mlx5_ib_multiport_info *mpi)
अणु
	u32 port_num = mlx5_core_native_port_num(mpi->mdev) - 1;
	पूर्णांक err;

	lockdep_निश्चित_held(&mlx5_ib_multiport_mutex);

	spin_lock(&ibdev->port[port_num].mp.mpi_lock);
	अगर (ibdev->port[port_num].mp.mpi) अणु
		mlx5_ib_dbg(ibdev, "port %u already affiliated.\n",
			    port_num + 1);
		spin_unlock(&ibdev->port[port_num].mp.mpi_lock);
		वापस false;
	पूर्ण

	ibdev->port[port_num].mp.mpi = mpi;
	mpi->ibdev = ibdev;
	mpi->mdev_events.notअगरier_call = शून्य;
	spin_unlock(&ibdev->port[port_num].mp.mpi_lock);

	err = mlx5_nic_vport_affiliate_multiport(ibdev->mdev, mpi->mdev);
	अगर (err)
		जाओ unbind;

	err = mlx5_add_netdev_notअगरier(ibdev, port_num);
	अगर (err) अणु
		mlx5_ib_err(ibdev, "failed adding netdev notifier for port %u\n",
			    port_num + 1);
		जाओ unbind;
	पूर्ण

	mpi->mdev_events.notअगरier_call = mlx5_ib_event_slave_port;
	mlx5_notअगरier_रेजिस्टर(mpi->mdev, &mpi->mdev_events);

	mlx5_ib_init_cong_debugfs(ibdev, port_num);

	वापस true;

unbind:
	mlx5_ib_unbind_slave_port(ibdev, mpi);
	वापस false;
पूर्ण

अटल पूर्णांक mlx5_ib_init_multiport_master(काष्ठा mlx5_ib_dev *dev)
अणु
	u32 port_num = mlx5_core_native_port_num(dev->mdev) - 1;
	क्रमागत rdma_link_layer ll = mlx5_ib_port_link_layer(&dev->ib_dev,
							  port_num + 1);
	काष्ठा mlx5_ib_multiport_info *mpi;
	पूर्णांक err;
	u32 i;

	अगर (!mlx5_core_is_mp_master(dev->mdev) || ll != IB_LINK_LAYER_ETHERNET)
		वापस 0;

	err = mlx5_query_nic_vport_प्रणाली_image_guid(dev->mdev,
						     &dev->sys_image_guid);
	अगर (err)
		वापस err;

	err = mlx5_nic_vport_enable_roce(dev->mdev);
	अगर (err)
		वापस err;

	mutex_lock(&mlx5_ib_multiport_mutex);
	क्रम (i = 0; i < dev->num_ports; i++) अणु
		bool bound = false;

		/* build a stub multiport info काष्ठा क्रम the native port. */
		अगर (i == port_num) अणु
			mpi = kzalloc(माप(*mpi), GFP_KERNEL);
			अगर (!mpi) अणु
				mutex_unlock(&mlx5_ib_multiport_mutex);
				mlx5_nic_vport_disable_roce(dev->mdev);
				वापस -ENOMEM;
			पूर्ण

			mpi->is_master = true;
			mpi->mdev = dev->mdev;
			mpi->sys_image_guid = dev->sys_image_guid;
			dev->port[i].mp.mpi = mpi;
			mpi->ibdev = dev;
			mpi = शून्य;
			जारी;
		पूर्ण

		list_क्रम_each_entry(mpi, &mlx5_ib_unaffiliated_port_list,
				    list) अणु
			अगर (dev->sys_image_guid == mpi->sys_image_guid &&
			    (mlx5_core_native_port_num(mpi->mdev) - 1) == i) अणु
				bound = mlx5_ib_bind_slave_port(dev, mpi);
			पूर्ण

			अगर (bound) अणु
				dev_dbg(mpi->mdev->device,
					"removing port from unaffiliated list.\n");
				mlx5_ib_dbg(dev, "port %d bound\n", i + 1);
				list_del(&mpi->list);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!bound)
			mlx5_ib_dbg(dev, "no free port found for port %d\n",
				    i + 1);
	पूर्ण

	list_add_tail(&dev->ib_dev_list, &mlx5_ib_dev_list);
	mutex_unlock(&mlx5_ib_multiport_mutex);
	वापस err;
पूर्ण

अटल व्योम mlx5_ib_cleanup_multiport_master(काष्ठा mlx5_ib_dev *dev)
अणु
	u32 port_num = mlx5_core_native_port_num(dev->mdev) - 1;
	क्रमागत rdma_link_layer ll = mlx5_ib_port_link_layer(&dev->ib_dev,
							  port_num + 1);
	u32 i;

	अगर (!mlx5_core_is_mp_master(dev->mdev) || ll != IB_LINK_LAYER_ETHERNET)
		वापस;

	mutex_lock(&mlx5_ib_multiport_mutex);
	क्रम (i = 0; i < dev->num_ports; i++) अणु
		अगर (dev->port[i].mp.mpi) अणु
			/* Destroy the native port stub */
			अगर (i == port_num) अणु
				kमुक्त(dev->port[i].mp.mpi);
				dev->port[i].mp.mpi = शून्य;
			पूर्ण अन्यथा अणु
				mlx5_ib_dbg(dev, "unbinding port_num: %u\n",
					    i + 1);
				mlx5_ib_unbind_slave_port(dev, dev->port[i].mp.mpi);
			पूर्ण
		पूर्ण
	पूर्ण

	mlx5_ib_dbg(dev, "removing from devlist\n");
	list_del(&dev->ib_dev_list);
	mutex_unlock(&mlx5_ib_multiport_mutex);

	mlx5_nic_vport_disable_roce(dev->mdev);
पूर्ण

अटल पूर्णांक mmap_obj_cleanup(काष्ठा ib_uobject *uobject,
			    क्रमागत rdma_हटाओ_reason why,
			    काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_user_mmap_entry *obj = uobject->object;

	rdma_user_mmap_entry_हटाओ(&obj->rdma_entry);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_rdma_user_mmap_entry_insert(काष्ठा mlx5_ib_ucontext *c,
					    काष्ठा mlx5_user_mmap_entry *entry,
					    माप_प्रकार length)
अणु
	वापस rdma_user_mmap_entry_insert_range(
		&c->ibucontext, &entry->rdma_entry, length,
		(MLX5_IB_MMAP_OFFSET_START << 16),
		((MLX5_IB_MMAP_OFFSET_END << 16) + (1UL << 16) - 1));
पूर्ण

अटल काष्ठा mlx5_user_mmap_entry *
alloc_var_entry(काष्ठा mlx5_ib_ucontext *c)
अणु
	काष्ठा mlx5_user_mmap_entry *entry;
	काष्ठा mlx5_var_table *var_table;
	u32 page_idx;
	पूर्णांक err;

	var_table = &to_mdev(c->ibucontext.device)->var_table;
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&var_table->biपंचांगap_lock);
	page_idx = find_first_zero_bit(var_table->biपंचांगap,
				       var_table->num_var_hw_entries);
	अगर (page_idx >= var_table->num_var_hw_entries) अणु
		err = -ENOSPC;
		mutex_unlock(&var_table->biपंचांगap_lock);
		जाओ end;
	पूर्ण

	set_bit(page_idx, var_table->biपंचांगap);
	mutex_unlock(&var_table->biपंचांगap_lock);

	entry->address = var_table->hw_start_addr +
				(page_idx * var_table->stride_size);
	entry->page_idx = page_idx;
	entry->mmap_flag = MLX5_IB_MMAP_TYPE_VAR;

	err = mlx5_rdma_user_mmap_entry_insert(c, entry,
					       var_table->stride_size);
	अगर (err)
		जाओ err_insert;

	वापस entry;

err_insert:
	mutex_lock(&var_table->biपंचांगap_lock);
	clear_bit(page_idx, var_table->biपंचांगap);
	mutex_unlock(&var_table->biपंचांगap_lock);
end:
	kमुक्त(entry);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_VAR_OBJ_ALLOC)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, MLX5_IB_ATTR_VAR_OBJ_ALLOC_HANDLE);
	काष्ठा mlx5_ib_ucontext *c;
	काष्ठा mlx5_user_mmap_entry *entry;
	u64 mmap_offset;
	u32 length;
	पूर्णांक err;

	c = to_mucontext(ib_uverbs_get_ucontext(attrs));
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);

	entry = alloc_var_entry(c);
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);

	mmap_offset = mlx5_entry_to_mmap_offset(entry);
	length = entry->rdma_entry.npages * PAGE_SIZE;
	uobj->object = entry;
	uverbs_finalize_uobj_create(attrs, MLX5_IB_ATTR_VAR_OBJ_ALLOC_HANDLE);

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_VAR_OBJ_ALLOC_MMAP_OFFSET,
			     &mmap_offset, माप(mmap_offset));
	अगर (err)
		वापस err;

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_VAR_OBJ_ALLOC_PAGE_ID,
			     &entry->page_idx, माप(entry->page_idx));
	अगर (err)
		वापस err;

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_VAR_OBJ_ALLOC_MMAP_LENGTH,
			     &length, माप(length));
	वापस err;
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_VAR_OBJ_ALLOC,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_VAR_OBJ_ALLOC_HANDLE,
			MLX5_IB_OBJECT_VAR,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_VAR_OBJ_ALLOC_PAGE_ID,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_VAR_OBJ_ALLOC_MMAP_LENGTH,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_VAR_OBJ_ALLOC_MMAP_OFFSET,
			    UVERBS_ATTR_TYPE(u64),
			    UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	MLX5_IB_METHOD_VAR_OBJ_DESTROY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_VAR_OBJ_DESTROY_HANDLE,
			MLX5_IB_OBJECT_VAR,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(MLX5_IB_OBJECT_VAR,
			    UVERBS_TYPE_ALLOC_IDR(mmap_obj_cleanup),
			    &UVERBS_METHOD(MLX5_IB_METHOD_VAR_OBJ_ALLOC),
			    &UVERBS_METHOD(MLX5_IB_METHOD_VAR_OBJ_DESTROY));

अटल bool var_is_supported(काष्ठा ib_device *device)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);

	वापस (MLX5_CAP_GEN_64(dev->mdev, general_obj_types) &
			MLX5_GENERAL_OBJ_TYPES_CAP_VIRTIO_NET_Q);
पूर्ण

अटल काष्ठा mlx5_user_mmap_entry *
alloc_uar_entry(काष्ठा mlx5_ib_ucontext *c,
		क्रमागत mlx5_ib_uapi_uar_alloc_type alloc_type)
अणु
	काष्ठा mlx5_user_mmap_entry *entry;
	काष्ठा mlx5_ib_dev *dev;
	u32 uar_index;
	पूर्णांक err;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस ERR_PTR(-ENOMEM);

	dev = to_mdev(c->ibucontext.device);
	err = mlx5_cmd_alloc_uar(dev->mdev, &uar_index);
	अगर (err)
		जाओ end;

	entry->page_idx = uar_index;
	entry->address = uar_index2paddress(dev, uar_index);
	अगर (alloc_type == MLX5_IB_UAPI_UAR_ALLOC_TYPE_BF)
		entry->mmap_flag = MLX5_IB_MMAP_TYPE_UAR_WC;
	अन्यथा
		entry->mmap_flag = MLX5_IB_MMAP_TYPE_UAR_NC;

	err = mlx5_rdma_user_mmap_entry_insert(c, entry, PAGE_SIZE);
	अगर (err)
		जाओ err_insert;

	वापस entry;

err_insert:
	mlx5_cmd_मुक्त_uar(dev->mdev, uar_index);
end:
	kमुक्त(entry);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_UAR_OBJ_ALLOC)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, MLX5_IB_ATTR_UAR_OBJ_ALLOC_HANDLE);
	क्रमागत mlx5_ib_uapi_uar_alloc_type alloc_type;
	काष्ठा mlx5_ib_ucontext *c;
	काष्ठा mlx5_user_mmap_entry *entry;
	u64 mmap_offset;
	u32 length;
	पूर्णांक err;

	c = to_mucontext(ib_uverbs_get_ucontext(attrs));
	अगर (IS_ERR(c))
		वापस PTR_ERR(c);

	err = uverbs_get_स्थिर(&alloc_type, attrs,
			       MLX5_IB_ATTR_UAR_OBJ_ALLOC_TYPE);
	अगर (err)
		वापस err;

	अगर (alloc_type != MLX5_IB_UAPI_UAR_ALLOC_TYPE_BF &&
	    alloc_type != MLX5_IB_UAPI_UAR_ALLOC_TYPE_NC)
		वापस -EOPNOTSUPP;

	अगर (!to_mdev(c->ibucontext.device)->wc_support &&
	    alloc_type == MLX5_IB_UAPI_UAR_ALLOC_TYPE_BF)
		वापस -EOPNOTSUPP;

	entry = alloc_uar_entry(c, alloc_type);
	अगर (IS_ERR(entry))
		वापस PTR_ERR(entry);

	mmap_offset = mlx5_entry_to_mmap_offset(entry);
	length = entry->rdma_entry.npages * PAGE_SIZE;
	uobj->object = entry;
	uverbs_finalize_uobj_create(attrs, MLX5_IB_ATTR_UAR_OBJ_ALLOC_HANDLE);

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_UAR_OBJ_ALLOC_MMAP_OFFSET,
			     &mmap_offset, माप(mmap_offset));
	अगर (err)
		वापस err;

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_UAR_OBJ_ALLOC_PAGE_ID,
			     &entry->page_idx, माप(entry->page_idx));
	अगर (err)
		वापस err;

	err = uverbs_copy_to(attrs, MLX5_IB_ATTR_UAR_OBJ_ALLOC_MMAP_LENGTH,
			     &length, माप(length));
	वापस err;
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_UAR_OBJ_ALLOC,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_UAR_OBJ_ALLOC_HANDLE,
			MLX5_IB_OBJECT_UAR,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_CONST_IN(MLX5_IB_ATTR_UAR_OBJ_ALLOC_TYPE,
			     क्रमागत mlx5_ib_uapi_uar_alloc_type,
			     UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_UAR_OBJ_ALLOC_PAGE_ID,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_UAR_OBJ_ALLOC_MMAP_LENGTH,
			   UVERBS_ATTR_TYPE(u32),
			   UA_MANDATORY),
	UVERBS_ATTR_PTR_OUT(MLX5_IB_ATTR_UAR_OBJ_ALLOC_MMAP_OFFSET,
			    UVERBS_ATTR_TYPE(u64),
			    UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	MLX5_IB_METHOD_UAR_OBJ_DESTROY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_UAR_OBJ_DESTROY_HANDLE,
			MLX5_IB_OBJECT_UAR,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(MLX5_IB_OBJECT_UAR,
			    UVERBS_TYPE_ALLOC_IDR(mmap_obj_cleanup),
			    &UVERBS_METHOD(MLX5_IB_METHOD_UAR_OBJ_ALLOC),
			    &UVERBS_METHOD(MLX5_IB_METHOD_UAR_OBJ_DESTROY));

ADD_UVERBS_ATTRIBUTES_SIMPLE(
	mlx5_ib_flow_action,
	UVERBS_OBJECT_FLOW_ACTION,
	UVERBS_METHOD_FLOW_ACTION_ESP_CREATE,
	UVERBS_ATTR_FLAGS_IN(MLX5_IB_ATTR_CREATE_FLOW_ACTION_FLAGS,
			     क्रमागत mlx5_ib_uapi_flow_action_flags));

ADD_UVERBS_ATTRIBUTES_SIMPLE(
	mlx5_ib_query_context,
	UVERBS_OBJECT_DEVICE,
	UVERBS_METHOD_QUERY_CONTEXT,
	UVERBS_ATTR_PTR_OUT(
		MLX5_IB_ATTR_QUERY_CONTEXT_RESP_UCTX,
		UVERBS_ATTR_STRUCT(काष्ठा mlx5_ib_alloc_ucontext_resp,
				   dump_fill_mkey),
		UA_MANDATORY));

अटल स्थिर काष्ठा uapi_definition mlx5_ib_defs[] = अणु
	UAPI_DEF_CHAIN(mlx5_ib_devx_defs),
	UAPI_DEF_CHAIN(mlx5_ib_flow_defs),
	UAPI_DEF_CHAIN(mlx5_ib_qos_defs),
	UAPI_DEF_CHAIN(mlx5_ib_std_types_defs),
	UAPI_DEF_CHAIN(mlx5_ib_dm_defs),

	UAPI_DEF_CHAIN_OBJ_TREE(UVERBS_OBJECT_FLOW_ACTION,
				&mlx5_ib_flow_action),
	UAPI_DEF_CHAIN_OBJ_TREE(UVERBS_OBJECT_DEVICE, &mlx5_ib_query_context),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(MLX5_IB_OBJECT_VAR,
				UAPI_DEF_IS_OBJ_SUPPORTED(var_is_supported)),
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(MLX5_IB_OBJECT_UAR),
	अणुपूर्ण
पूर्ण;

अटल व्योम mlx5_ib_stage_init_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	mlx5_ib_cleanup_multiport_master(dev);
	WARN_ON(!xa_empty(&dev->odp_mkeys));
	mutex_destroy(&dev->cap_mask_mutex);
	WARN_ON(!xa_empty(&dev->sig_mrs));
	WARN_ON(!biपंचांगap_empty(dev->dm.memic_alloc_pages, MLX5_MAX_MEMIC_PAGES));
पूर्ण

अटल पूर्णांक mlx5_ib_stage_init_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	पूर्णांक err;
	पूर्णांक i;

	dev->ib_dev.node_type = RDMA_NODE_IB_CA;
	dev->ib_dev.local_dma_lkey = 0 /* not supported क्रम now */;
	dev->ib_dev.phys_port_cnt = dev->num_ports;
	dev->ib_dev.dev.parent = mdev->device;
	dev->ib_dev.lag_flags = RDMA_LAG_FLAGS_HASH_ALL_SLAVES;

	क्रम (i = 0; i < dev->num_ports; i++) अणु
		spin_lock_init(&dev->port[i].mp.mpi_lock);
		rwlock_init(&dev->port[i].roce.netdev_lock);
		dev->port[i].roce.dev = dev;
		dev->port[i].roce.native_port_num = i + 1;
		dev->port[i].roce.last_port_state = IB_PORT_DOWN;
	पूर्ण

	err = mlx5_ib_init_multiport_master(dev);
	अगर (err)
		वापस err;

	err = set_has_smi_cap(dev);
	अगर (err)
		जाओ err_mp;

	err = mlx5_query_max_pkeys(&dev->ib_dev, &dev->pkey_table_len);
	अगर (err)
		जाओ err_mp;

	अगर (mlx5_use_mad_अगरc(dev))
		get_ext_port_caps(dev);

	dev->ib_dev.num_comp_vectors    = mlx5_comp_vectors_count(mdev);

	mutex_init(&dev->cap_mask_mutex);
	INIT_LIST_HEAD(&dev->qp_list);
	spin_lock_init(&dev->reset_flow_resource_lock);
	xa_init(&dev->odp_mkeys);
	xa_init(&dev->sig_mrs);
	atomic_set(&dev->mkey_var, 0);

	spin_lock_init(&dev->dm.lock);
	dev->dm.dev = mdev;
	वापस 0;

err_mp:
	mlx5_ib_cleanup_multiport_master(dev);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_ib_enable_driver(काष्ठा ib_device *dev)
अणु
	काष्ठा mlx5_ib_dev *mdev = to_mdev(dev);
	पूर्णांक ret;

	ret = mlx5_ib_test_wc(mdev);
	mlx5_ib_dbg(mdev, "Write-Combining %s",
		    mdev->wc_support ? "supported" : "not supported");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops mlx5_ib_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_MLX5,
	.uverbs_abi_ver	= MLX5_IB_UVERBS_ABI_VERSION,

	.add_gid = mlx5_ib_add_gid,
	.alloc_mr = mlx5_ib_alloc_mr,
	.alloc_mr_पूर्णांकegrity = mlx5_ib_alloc_mr_पूर्णांकegrity,
	.alloc_pd = mlx5_ib_alloc_pd,
	.alloc_ucontext = mlx5_ib_alloc_ucontext,
	.attach_mcast = mlx5_ib_mcg_attach,
	.check_mr_status = mlx5_ib_check_mr_status,
	.create_ah = mlx5_ib_create_ah,
	.create_cq = mlx5_ib_create_cq,
	.create_qp = mlx5_ib_create_qp,
	.create_srq = mlx5_ib_create_srq,
	.create_user_ah = mlx5_ib_create_ah,
	.dealloc_pd = mlx5_ib_dealloc_pd,
	.dealloc_ucontext = mlx5_ib_dealloc_ucontext,
	.del_gid = mlx5_ib_del_gid,
	.dereg_mr = mlx5_ib_dereg_mr,
	.destroy_ah = mlx5_ib_destroy_ah,
	.destroy_cq = mlx5_ib_destroy_cq,
	.destroy_qp = mlx5_ib_destroy_qp,
	.destroy_srq = mlx5_ib_destroy_srq,
	.detach_mcast = mlx5_ib_mcg_detach,
	.disassociate_ucontext = mlx5_ib_disassociate_ucontext,
	.drain_rq = mlx5_ib_drain_rq,
	.drain_sq = mlx5_ib_drain_sq,
	.enable_driver = mlx5_ib_enable_driver,
	.get_dev_fw_str = get_dev_fw_str,
	.get_dma_mr = mlx5_ib_get_dma_mr,
	.get_link_layer = mlx5_ib_port_link_layer,
	.map_mr_sg = mlx5_ib_map_mr_sg,
	.map_mr_sg_pi = mlx5_ib_map_mr_sg_pi,
	.mmap = mlx5_ib_mmap,
	.mmap_मुक्त = mlx5_ib_mmap_मुक्त,
	.modअगरy_cq = mlx5_ib_modअगरy_cq,
	.modअगरy_device = mlx5_ib_modअगरy_device,
	.modअगरy_port = mlx5_ib_modअगरy_port,
	.modअगरy_qp = mlx5_ib_modअगरy_qp,
	.modअगरy_srq = mlx5_ib_modअगरy_srq,
	.poll_cq = mlx5_ib_poll_cq,
	.post_recv = mlx5_ib_post_recv_nodrain,
	.post_send = mlx5_ib_post_send_nodrain,
	.post_srq_recv = mlx5_ib_post_srq_recv,
	.process_mad = mlx5_ib_process_mad,
	.query_ah = mlx5_ib_query_ah,
	.query_device = mlx5_ib_query_device,
	.query_gid = mlx5_ib_query_gid,
	.query_pkey = mlx5_ib_query_pkey,
	.query_qp = mlx5_ib_query_qp,
	.query_srq = mlx5_ib_query_srq,
	.query_ucontext = mlx5_ib_query_ucontext,
	.reg_user_mr = mlx5_ib_reg_user_mr,
	.reg_user_mr_dmabuf = mlx5_ib_reg_user_mr_dmabuf,
	.req_notअगरy_cq = mlx5_ib_arm_cq,
	.rereg_user_mr = mlx5_ib_rereg_user_mr,
	.resize_cq = mlx5_ib_resize_cq,

	INIT_RDMA_OBJ_SIZE(ib_ah, mlx5_ib_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_counters, mlx5_ib_mcounters, ibcntrs),
	INIT_RDMA_OBJ_SIZE(ib_cq, mlx5_ib_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_pd, mlx5_ib_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_srq, mlx5_ib_srq, ibsrq),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, mlx5_ib_ucontext, ibucontext),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mlx5_ib_dev_ipoib_enhanced_ops = अणु
	.rdma_netdev_get_params = mlx5_ib_rn_get_params,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mlx5_ib_dev_sriov_ops = अणु
	.get_vf_config = mlx5_ib_get_vf_config,
	.get_vf_guid = mlx5_ib_get_vf_guid,
	.get_vf_stats = mlx5_ib_get_vf_stats,
	.set_vf_guid = mlx5_ib_set_vf_guid,
	.set_vf_link_state = mlx5_ib_set_vf_link_state,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mlx5_ib_dev_mw_ops = अणु
	.alloc_mw = mlx5_ib_alloc_mw,
	.dealloc_mw = mlx5_ib_dealloc_mw,

	INIT_RDMA_OBJ_SIZE(ib_mw, mlx5_ib_mw, ibmw),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mlx5_ib_dev_xrc_ops = अणु
	.alloc_xrcd = mlx5_ib_alloc_xrcd,
	.dealloc_xrcd = mlx5_ib_dealloc_xrcd,

	INIT_RDMA_OBJ_SIZE(ib_xrcd, mlx5_ib_xrcd, ibxrcd),
पूर्ण;

अटल पूर्णांक mlx5_ib_init_var_table(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_var_table *var_table = &dev->var_table;
	u8 log_करोorbell_bar_size;
	u8 log_करोorbell_stride;
	u64 bar_size;

	log_करोorbell_bar_size = MLX5_CAP_DEV_VDPA_EMULATION(mdev,
					log_करोorbell_bar_size);
	log_करोorbell_stride = MLX5_CAP_DEV_VDPA_EMULATION(mdev,
					log_करोorbell_stride);
	var_table->hw_start_addr = dev->mdev->bar_addr +
				MLX5_CAP64_DEV_VDPA_EMULATION(mdev,
					करोorbell_bar_offset);
	bar_size = (1ULL << log_करोorbell_bar_size) * 4096;
	var_table->stride_size = 1ULL << log_करोorbell_stride;
	var_table->num_var_hw_entries = भाग_u64(bar_size,
						var_table->stride_size);
	mutex_init(&var_table->biपंचांगap_lock);
	var_table->biपंचांगap = biपंचांगap_zalloc(var_table->num_var_hw_entries,
					  GFP_KERNEL);
	वापस (var_table->biपंचांगap) ? 0 : -ENOMEM;
पूर्ण

अटल व्योम mlx5_ib_stage_caps_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	biपंचांगap_मुक्त(dev->var_table.biपंचांगap);
पूर्ण

अटल पूर्णांक mlx5_ib_stage_caps_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	पूर्णांक err;

	अगर (MLX5_CAP_GEN(mdev, ipoib_enhanced_offloads) &&
	    IS_ENABLED(CONFIG_MLX5_CORE_IPOIB))
		ib_set_device_ops(&dev->ib_dev,
				  &mlx5_ib_dev_ipoib_enhanced_ops);

	अगर (mlx5_core_is_pf(mdev))
		ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_sriov_ops);

	dev->umr_fence = mlx5_get_umr_fence(MLX5_CAP_GEN(mdev, umr_fence));

	अगर (MLX5_CAP_GEN(mdev, imaicl))
		ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_mw_ops);

	अगर (MLX5_CAP_GEN(mdev, xrc))
		ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_xrc_ops);

	अगर (MLX5_CAP_DEV_MEM(mdev, memic) ||
	    MLX5_CAP_GEN_64(dev->mdev, general_obj_types) &
	    MLX5_GENERAL_OBJ_TYPES_CAP_SW_ICM)
		ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_dm_ops);

	ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_ops);

	अगर (IS_ENABLED(CONFIG_INFINIBAND_USER_ACCESS))
		dev->ib_dev.driver_def = mlx5_ib_defs;

	err = init_node_data(dev);
	अगर (err)
		वापस err;

	अगर ((MLX5_CAP_GEN(dev->mdev, port_type) == MLX5_CAP_PORT_TYPE_ETH) &&
	    (MLX5_CAP_GEN(dev->mdev, disable_local_lb_uc) ||
	     MLX5_CAP_GEN(dev->mdev, disable_local_lb_mc)))
		mutex_init(&dev->lb.mutex);

	अगर (MLX5_CAP_GEN_64(dev->mdev, general_obj_types) &
			MLX5_GENERAL_OBJ_TYPES_CAP_VIRTIO_NET_Q) अणु
		err = mlx5_ib_init_var_table(dev);
		अगर (err)
			वापस err;
	पूर्ण

	dev->ib_dev.use_cq_dim = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops mlx5_ib_dev_port_ops = अणु
	.get_port_immutable = mlx5_port_immutable,
	.query_port = mlx5_ib_query_port,
पूर्ण;

अटल पूर्णांक mlx5_ib_stage_non_शेष_cb(काष्ठा mlx5_ib_dev *dev)
अणु
	ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_port_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops mlx5_ib_dev_port_rep_ops = अणु
	.get_port_immutable = mlx5_port_rep_immutable,
	.query_port = mlx5_ib_rep_query_port,
	.query_pkey = mlx5_ib_rep_query_pkey,
पूर्ण;

अटल पूर्णांक mlx5_ib_stage_raw_eth_non_शेष_cb(काष्ठा mlx5_ib_dev *dev)
अणु
	ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_port_rep_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ib_device_ops mlx5_ib_dev_common_roce_ops = अणु
	.create_rwq_ind_table = mlx5_ib_create_rwq_ind_table,
	.create_wq = mlx5_ib_create_wq,
	.destroy_rwq_ind_table = mlx5_ib_destroy_rwq_ind_table,
	.destroy_wq = mlx5_ib_destroy_wq,
	.get_netdev = mlx5_ib_get_netdev,
	.modअगरy_wq = mlx5_ib_modअगरy_wq,

	INIT_RDMA_OBJ_SIZE(ib_rwq_ind_table, mlx5_ib_rwq_ind_table,
			   ib_rwq_ind_tbl),
पूर्ण;

अटल पूर्णांक mlx5_ib_roce_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	क्रमागत rdma_link_layer ll;
	पूर्णांक port_type_cap;
	u32 port_num = 0;
	पूर्णांक err;

	port_type_cap = MLX5_CAP_GEN(mdev, port_type);
	ll = mlx5_port_type_cap_to_rdma_ll(port_type_cap);

	अगर (ll == IB_LINK_LAYER_ETHERNET) अणु
		ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_common_roce_ops);

		port_num = mlx5_core_native_port_num(dev->mdev) - 1;

		/* Register only क्रम native ports */
		err = mlx5_add_netdev_notअगरier(dev, port_num);
		अगर (err || dev->is_rep || !mlx5_is_roce_init_enabled(mdev))
			/*
			 * We करोn't enable ETH पूर्णांकerface क्रम
			 * 1. IB representors
			 * 2. User disabled ROCE through devlink पूर्णांकerface
			 */
			वापस err;

		err = mlx5_enable_eth(dev);
		अगर (err)
			जाओ cleanup;
	पूर्ण

	वापस 0;
cleanup:
	mlx5_हटाओ_netdev_notअगरier(dev, port_num);
	वापस err;
पूर्ण

अटल व्योम mlx5_ib_roce_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	क्रमागत rdma_link_layer ll;
	पूर्णांक port_type_cap;
	u32 port_num;

	port_type_cap = MLX5_CAP_GEN(mdev, port_type);
	ll = mlx5_port_type_cap_to_rdma_ll(port_type_cap);

	अगर (ll == IB_LINK_LAYER_ETHERNET) अणु
		अगर (!dev->is_rep)
			mlx5_disable_eth(dev);

		port_num = mlx5_core_native_port_num(dev->mdev) - 1;
		mlx5_हटाओ_netdev_notअगरier(dev, port_num);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_ib_stage_cong_debugfs_init(काष्ठा mlx5_ib_dev *dev)
अणु
	mlx5_ib_init_cong_debugfs(dev,
				  mlx5_core_native_port_num(dev->mdev) - 1);
	वापस 0;
पूर्ण

अटल व्योम mlx5_ib_stage_cong_debugfs_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	mlx5_ib_cleanup_cong_debugfs(dev,
				     mlx5_core_native_port_num(dev->mdev) - 1);
पूर्ण

अटल पूर्णांक mlx5_ib_stage_uar_init(काष्ठा mlx5_ib_dev *dev)
अणु
	dev->mdev->priv.uar = mlx5_get_uars_page(dev->mdev);
	वापस PTR_ERR_OR_ZERO(dev->mdev->priv.uar);
पूर्ण

अटल व्योम mlx5_ib_stage_uar_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	mlx5_put_uars_page(dev->mdev, dev->mdev->priv.uar);
पूर्ण

अटल पूर्णांक mlx5_ib_stage_bfrag_init(काष्ठा mlx5_ib_dev *dev)
अणु
	पूर्णांक err;

	err = mlx5_alloc_bfreg(dev->mdev, &dev->bfreg, false, false);
	अगर (err)
		वापस err;

	err = mlx5_alloc_bfreg(dev->mdev, &dev->fp_bfreg, false, true);
	अगर (err)
		mlx5_मुक्त_bfreg(dev->mdev, &dev->bfreg);

	वापस err;
पूर्ण

अटल व्योम mlx5_ib_stage_bfrag_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	mlx5_मुक्त_bfreg(dev->mdev, &dev->fp_bfreg);
	mlx5_मुक्त_bfreg(dev->mdev, &dev->bfreg);
पूर्ण

अटल पूर्णांक mlx5_ib_stage_ib_reg_init(काष्ठा mlx5_ib_dev *dev)
अणु
	स्थिर अक्षर *name;

	rdma_set_device_sysfs_group(&dev->ib_dev, &mlx5_attr_group);
	अगर (!mlx5_lag_is_roce(dev->mdev))
		name = "mlx5_%d";
	अन्यथा
		name = "mlx5_bond_%d";
	वापस ib_रेजिस्टर_device(&dev->ib_dev, name, &dev->mdev->pdev->dev);
पूर्ण

अटल व्योम mlx5_ib_stage_pre_ib_reg_umr_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	पूर्णांक err;

	err = mlx5_mr_cache_cleanup(dev);
	अगर (err)
		mlx5_ib_warn(dev, "mr cache cleanup failed\n");

	अगर (dev->umrc.qp)
		mlx5_ib_destroy_qp(dev->umrc.qp, शून्य);
	अगर (dev->umrc.cq)
		ib_मुक्त_cq(dev->umrc.cq);
	अगर (dev->umrc.pd)
		ib_dealloc_pd(dev->umrc.pd);
पूर्ण

अटल व्योम mlx5_ib_stage_ib_reg_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	ib_unरेजिस्टर_device(&dev->ib_dev);
पूर्ण

क्रमागत अणु
	MAX_UMR_WR = 128,
पूर्ण;

अटल पूर्णांक mlx5_ib_stage_post_ib_reg_umr_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा ib_qp_init_attr *init_attr = शून्य;
	काष्ठा ib_qp_attr *attr = शून्य;
	काष्ठा ib_pd *pd;
	काष्ठा ib_cq *cq;
	काष्ठा ib_qp *qp;
	पूर्णांक ret;

	attr = kzalloc(माप(*attr), GFP_KERNEL);
	init_attr = kzalloc(माप(*init_attr), GFP_KERNEL);
	अगर (!attr || !init_attr) अणु
		ret = -ENOMEM;
		जाओ error_0;
	पूर्ण

	pd = ib_alloc_pd(&dev->ib_dev, 0);
	अगर (IS_ERR(pd)) अणु
		mlx5_ib_dbg(dev, "Couldn't create PD for sync UMR QP\n");
		ret = PTR_ERR(pd);
		जाओ error_0;
	पूर्ण

	cq = ib_alloc_cq(&dev->ib_dev, शून्य, 128, 0, IB_POLL_SOFTIRQ);
	अगर (IS_ERR(cq)) अणु
		mlx5_ib_dbg(dev, "Couldn't create CQ for sync UMR QP\n");
		ret = PTR_ERR(cq);
		जाओ error_2;
	पूर्ण

	init_attr->send_cq = cq;
	init_attr->recv_cq = cq;
	init_attr->sq_sig_type = IB_SIGNAL_ALL_WR;
	init_attr->cap.max_send_wr = MAX_UMR_WR;
	init_attr->cap.max_send_sge = 1;
	init_attr->qp_type = MLX5_IB_QPT_REG_UMR;
	init_attr->port_num = 1;
	qp = mlx5_ib_create_qp(pd, init_attr, शून्य);
	अगर (IS_ERR(qp)) अणु
		mlx5_ib_dbg(dev, "Couldn't create sync UMR QP\n");
		ret = PTR_ERR(qp);
		जाओ error_3;
	पूर्ण
	qp->device     = &dev->ib_dev;
	qp->real_qp    = qp;
	qp->uobject    = शून्य;
	qp->qp_type    = MLX5_IB_QPT_REG_UMR;
	qp->send_cq    = init_attr->send_cq;
	qp->recv_cq    = init_attr->recv_cq;

	attr->qp_state = IB_QPS_INIT;
	attr->port_num = 1;
	ret = mlx5_ib_modअगरy_qp(qp, attr, IB_QP_STATE | IB_QP_PKEY_INDEX |
				IB_QP_PORT, शून्य);
	अगर (ret) अणु
		mlx5_ib_dbg(dev, "Couldn't modify UMR QP\n");
		जाओ error_4;
	पूर्ण

	स_रखो(attr, 0, माप(*attr));
	attr->qp_state = IB_QPS_RTR;
	attr->path_mtu = IB_MTU_256;

	ret = mlx5_ib_modअगरy_qp(qp, attr, IB_QP_STATE, शून्य);
	अगर (ret) अणु
		mlx5_ib_dbg(dev, "Couldn't modify umr QP to rtr\n");
		जाओ error_4;
	पूर्ण

	स_रखो(attr, 0, माप(*attr));
	attr->qp_state = IB_QPS_RTS;
	ret = mlx5_ib_modअगरy_qp(qp, attr, IB_QP_STATE, शून्य);
	अगर (ret) अणु
		mlx5_ib_dbg(dev, "Couldn't modify umr QP to rts\n");
		जाओ error_4;
	पूर्ण

	dev->umrc.qp = qp;
	dev->umrc.cq = cq;
	dev->umrc.pd = pd;

	sema_init(&dev->umrc.sem, MAX_UMR_WR);
	ret = mlx5_mr_cache_init(dev);
	अगर (ret) अणु
		mlx5_ib_warn(dev, "mr cache init failed %d\n", ret);
		जाओ error_4;
	पूर्ण

	kमुक्त(attr);
	kमुक्त(init_attr);

	वापस 0;

error_4:
	mlx5_ib_destroy_qp(qp, शून्य);
	dev->umrc.qp = शून्य;

error_3:
	ib_मुक्त_cq(cq);
	dev->umrc.cq = शून्य;

error_2:
	ib_dealloc_pd(pd);
	dev->umrc.pd = शून्य;

error_0:
	kमुक्त(attr);
	kमुक्त(init_attr);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_ib_stage_delay_drop_init(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा dentry *root;

	अगर (!(dev->ib_dev.attrs.raw_packet_caps & IB_RAW_PACKET_CAP_DELAY_DROP))
		वापस 0;

	mutex_init(&dev->delay_drop.lock);
	dev->delay_drop.dev = dev;
	dev->delay_drop.activate = false;
	dev->delay_drop.समयout = MLX5_MAX_DELAY_DROP_TIMEOUT_MS * 1000;
	INIT_WORK(&dev->delay_drop.delay_drop_work, delay_drop_handler);
	atomic_set(&dev->delay_drop.rqs_cnt, 0);
	atomic_set(&dev->delay_drop.events_cnt, 0);

	अगर (!mlx5_debugfs_root)
		वापस 0;

	root = debugfs_create_dir("delay_drop", dev->mdev->priv.dbg_root);
	dev->delay_drop.dir_debugfs = root;

	debugfs_create_atomic_t("num_timeout_events", 0400, root,
				&dev->delay_drop.events_cnt);
	debugfs_create_atomic_t("num_rqs", 0400, root,
				&dev->delay_drop.rqs_cnt);
	debugfs_create_file("timeout", 0600, root, &dev->delay_drop,
			    &fops_delay_drop_समयout);
	वापस 0;
पूर्ण

अटल व्योम mlx5_ib_stage_delay_drop_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	अगर (!(dev->ib_dev.attrs.raw_packet_caps & IB_RAW_PACKET_CAP_DELAY_DROP))
		वापस;

	cancel_work_sync(&dev->delay_drop.delay_drop_work);
	अगर (!dev->delay_drop.dir_debugfs)
		वापस;

	debugfs_हटाओ_recursive(dev->delay_drop.dir_debugfs);
	dev->delay_drop.dir_debugfs = शून्य;
पूर्ण

अटल पूर्णांक mlx5_ib_stage_dev_notअगरier_init(काष्ठा mlx5_ib_dev *dev)
अणु
	dev->mdev_events.notअगरier_call = mlx5_ib_event;
	mlx5_notअगरier_रेजिस्टर(dev->mdev, &dev->mdev_events);
	वापस 0;
पूर्ण

अटल व्योम mlx5_ib_stage_dev_notअगरier_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	mlx5_notअगरier_unरेजिस्टर(dev->mdev, &dev->mdev_events);
पूर्ण

व्योम __mlx5_ib_हटाओ(काष्ठा mlx5_ib_dev *dev,
		      स्थिर काष्ठा mlx5_ib_profile *profile,
		      पूर्णांक stage)
अणु
	dev->ib_active = false;

	/* Number of stages to cleanup */
	जबतक (stage) अणु
		stage--;
		अगर (profile->stage[stage].cleanup)
			profile->stage[stage].cleanup(dev);
	पूर्ण

	kमुक्त(dev->port);
	ib_dealloc_device(&dev->ib_dev);
पूर्ण

पूर्णांक __mlx5_ib_add(काष्ठा mlx5_ib_dev *dev,
		  स्थिर काष्ठा mlx5_ib_profile *profile)
अणु
	पूर्णांक err;
	पूर्णांक i;

	dev->profile = profile;

	क्रम (i = 0; i < MLX5_IB_STAGE_MAX; i++) अणु
		अगर (profile->stage[i].init) अणु
			err = profile->stage[i].init(dev);
			अगर (err)
				जाओ err_out;
		पूर्ण
	पूर्ण

	dev->ib_active = true;
	वापस 0;

err_out:
	/* Clean up stages which were initialized */
	जबतक (i) अणु
		i--;
		अगर (profile->stage[i].cleanup)
			profile->stage[i].cleanup(dev);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल स्थिर काष्ठा mlx5_ib_profile pf_profile = अणु
	STAGE_CREATE(MLX5_IB_STAGE_INIT,
		     mlx5_ib_stage_init_init,
		     mlx5_ib_stage_init_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_FS,
		     mlx5_ib_fs_init,
		     mlx5_ib_fs_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_CAPS,
		     mlx5_ib_stage_caps_init,
		     mlx5_ib_stage_caps_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_NON_DEFAULT_CB,
		     mlx5_ib_stage_non_शेष_cb,
		     शून्य),
	STAGE_CREATE(MLX5_IB_STAGE_ROCE,
		     mlx5_ib_roce_init,
		     mlx5_ib_roce_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_QP,
		     mlx5_init_qp_table,
		     mlx5_cleanup_qp_table),
	STAGE_CREATE(MLX5_IB_STAGE_SRQ,
		     mlx5_init_srq_table,
		     mlx5_cleanup_srq_table),
	STAGE_CREATE(MLX5_IB_STAGE_DEVICE_RESOURCES,
		     mlx5_ib_dev_res_init,
		     mlx5_ib_dev_res_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_DEVICE_NOTIFIER,
		     mlx5_ib_stage_dev_notअगरier_init,
		     mlx5_ib_stage_dev_notअगरier_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_ODP,
		     mlx5_ib_odp_init_one,
		     mlx5_ib_odp_cleanup_one),
	STAGE_CREATE(MLX5_IB_STAGE_COUNTERS,
		     mlx5_ib_counters_init,
		     mlx5_ib_counters_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_CONG_DEBUGFS,
		     mlx5_ib_stage_cong_debugfs_init,
		     mlx5_ib_stage_cong_debugfs_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_UAR,
		     mlx5_ib_stage_uar_init,
		     mlx5_ib_stage_uar_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_BFREG,
		     mlx5_ib_stage_bfrag_init,
		     mlx5_ib_stage_bfrag_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_PRE_IB_REG_UMR,
		     शून्य,
		     mlx5_ib_stage_pre_ib_reg_umr_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_WHITELIST_UID,
		     mlx5_ib_devx_init,
		     mlx5_ib_devx_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_IB_REG,
		     mlx5_ib_stage_ib_reg_init,
		     mlx5_ib_stage_ib_reg_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_POST_IB_REG_UMR,
		     mlx5_ib_stage_post_ib_reg_umr_init,
		     शून्य),
	STAGE_CREATE(MLX5_IB_STAGE_DELAY_DROP,
		     mlx5_ib_stage_delay_drop_init,
		     mlx5_ib_stage_delay_drop_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_RESTRACK,
		     mlx5_ib_restrack_init,
		     शून्य),
पूर्ण;

स्थिर काष्ठा mlx5_ib_profile raw_eth_profile = अणु
	STAGE_CREATE(MLX5_IB_STAGE_INIT,
		     mlx5_ib_stage_init_init,
		     mlx5_ib_stage_init_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_FS,
		     mlx5_ib_fs_init,
		     mlx5_ib_fs_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_CAPS,
		     mlx5_ib_stage_caps_init,
		     mlx5_ib_stage_caps_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_NON_DEFAULT_CB,
		     mlx5_ib_stage_raw_eth_non_शेष_cb,
		     शून्य),
	STAGE_CREATE(MLX5_IB_STAGE_ROCE,
		     mlx5_ib_roce_init,
		     mlx5_ib_roce_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_QP,
		     mlx5_init_qp_table,
		     mlx5_cleanup_qp_table),
	STAGE_CREATE(MLX5_IB_STAGE_SRQ,
		     mlx5_init_srq_table,
		     mlx5_cleanup_srq_table),
	STAGE_CREATE(MLX5_IB_STAGE_DEVICE_RESOURCES,
		     mlx5_ib_dev_res_init,
		     mlx5_ib_dev_res_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_DEVICE_NOTIFIER,
		     mlx5_ib_stage_dev_notअगरier_init,
		     mlx5_ib_stage_dev_notअगरier_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_COUNTERS,
		     mlx5_ib_counters_init,
		     mlx5_ib_counters_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_CONG_DEBUGFS,
		     mlx5_ib_stage_cong_debugfs_init,
		     mlx5_ib_stage_cong_debugfs_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_UAR,
		     mlx5_ib_stage_uar_init,
		     mlx5_ib_stage_uar_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_BFREG,
		     mlx5_ib_stage_bfrag_init,
		     mlx5_ib_stage_bfrag_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_PRE_IB_REG_UMR,
		     शून्य,
		     mlx5_ib_stage_pre_ib_reg_umr_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_WHITELIST_UID,
		     mlx5_ib_devx_init,
		     mlx5_ib_devx_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_IB_REG,
		     mlx5_ib_stage_ib_reg_init,
		     mlx5_ib_stage_ib_reg_cleanup),
	STAGE_CREATE(MLX5_IB_STAGE_POST_IB_REG_UMR,
		     mlx5_ib_stage_post_ib_reg_umr_init,
		     शून्य),
	STAGE_CREATE(MLX5_IB_STAGE_RESTRACK,
		     mlx5_ib_restrack_init,
		     शून्य),
पूर्ण;

अटल पूर्णांक mlx5r_mp_probe(काष्ठा auxiliary_device *adev,
			  स्थिर काष्ठा auxiliary_device_id *id)
अणु
	काष्ठा mlx5_adev *idev = container_of(adev, काष्ठा mlx5_adev, adev);
	काष्ठा mlx5_core_dev *mdev = idev->mdev;
	काष्ठा mlx5_ib_multiport_info *mpi;
	काष्ठा mlx5_ib_dev *dev;
	bool bound = false;
	पूर्णांक err;

	mpi = kzalloc(माप(*mpi), GFP_KERNEL);
	अगर (!mpi)
		वापस -ENOMEM;

	mpi->mdev = mdev;
	err = mlx5_query_nic_vport_प्रणाली_image_guid(mdev,
						     &mpi->sys_image_guid);
	अगर (err) अणु
		kमुक्त(mpi);
		वापस err;
	पूर्ण

	mutex_lock(&mlx5_ib_multiport_mutex);
	list_क्रम_each_entry(dev, &mlx5_ib_dev_list, ib_dev_list) अणु
		अगर (dev->sys_image_guid == mpi->sys_image_guid)
			bound = mlx5_ib_bind_slave_port(dev, mpi);

		अगर (bound) अणु
			rdma_roce_rescan_device(&dev->ib_dev);
			mpi->ibdev->ib_active = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!bound) अणु
		list_add_tail(&mpi->list, &mlx5_ib_unaffiliated_port_list);
		dev_dbg(mdev->device,
			"no suitable IB device found to bind to, added to unaffiliated list.\n");
	पूर्ण
	mutex_unlock(&mlx5_ib_multiport_mutex);

	dev_set_drvdata(&adev->dev, mpi);
	वापस 0;
पूर्ण

अटल व्योम mlx5r_mp_हटाओ(काष्ठा auxiliary_device *adev)
अणु
	काष्ठा mlx5_ib_multiport_info *mpi;

	mpi = dev_get_drvdata(&adev->dev);
	mutex_lock(&mlx5_ib_multiport_mutex);
	अगर (mpi->ibdev)
		mlx5_ib_unbind_slave_port(mpi->ibdev, mpi);
	list_del(&mpi->list);
	mutex_unlock(&mlx5_ib_multiport_mutex);
	kमुक्त(mpi);
पूर्ण

अटल पूर्णांक mlx5r_probe(काष्ठा auxiliary_device *adev,
		       स्थिर काष्ठा auxiliary_device_id *id)
अणु
	काष्ठा mlx5_adev *idev = container_of(adev, काष्ठा mlx5_adev, adev);
	काष्ठा mlx5_core_dev *mdev = idev->mdev;
	स्थिर काष्ठा mlx5_ib_profile *profile;
	पूर्णांक port_type_cap, num_ports, ret;
	क्रमागत rdma_link_layer ll;
	काष्ठा mlx5_ib_dev *dev;

	port_type_cap = MLX5_CAP_GEN(mdev, port_type);
	ll = mlx5_port_type_cap_to_rdma_ll(port_type_cap);

	num_ports = max(MLX5_CAP_GEN(mdev, num_ports),
			MLX5_CAP_GEN(mdev, num_vhca_ports));
	dev = ib_alloc_device(mlx5_ib_dev, ib_dev);
	अगर (!dev)
		वापस -ENOMEM;
	dev->port = kसुस्मृति(num_ports, माप(*dev->port),
			     GFP_KERNEL);
	अगर (!dev->port) अणु
		ib_dealloc_device(&dev->ib_dev);
		वापस -ENOMEM;
	पूर्ण

	dev->mdev = mdev;
	dev->num_ports = num_ports;

	अगर (ll == IB_LINK_LAYER_ETHERNET && !mlx5_is_roce_init_enabled(mdev))
		profile = &raw_eth_profile;
	अन्यथा
		profile = &pf_profile;

	ret = __mlx5_ib_add(dev, profile);
	अगर (ret) अणु
		kमुक्त(dev->port);
		ib_dealloc_device(&dev->ib_dev);
		वापस ret;
	पूर्ण

	dev_set_drvdata(&adev->dev, dev);
	वापस 0;
पूर्ण

अटल व्योम mlx5r_हटाओ(काष्ठा auxiliary_device *adev)
अणु
	काष्ठा mlx5_ib_dev *dev;

	dev = dev_get_drvdata(&adev->dev);
	__mlx5_ib_हटाओ(dev, dev->profile, MLX5_IB_STAGE_MAX);
पूर्ण

अटल स्थिर काष्ठा auxiliary_device_id mlx5r_mp_id_table[] = अणु
	अणु .name = MLX5_ADEV_NAME ".multiport", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा auxiliary_device_id mlx5r_id_table[] = अणु
	अणु .name = MLX5_ADEV_NAME ".rdma", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(auxiliary, mlx5r_mp_id_table);
MODULE_DEVICE_TABLE(auxiliary, mlx5r_id_table);

अटल काष्ठा auxiliary_driver mlx5r_mp_driver = अणु
	.name = "multiport",
	.probe = mlx5r_mp_probe,
	.हटाओ = mlx5r_mp_हटाओ,
	.id_table = mlx5r_mp_id_table,
पूर्ण;

अटल काष्ठा auxiliary_driver mlx5r_driver = अणु
	.name = "rdma",
	.probe = mlx5r_probe,
	.हटाओ = mlx5r_हटाओ,
	.id_table = mlx5r_id_table,
पूर्ण;

अटल पूर्णांक __init mlx5_ib_init(व्योम)
अणु
	पूर्णांक ret;

	xlt_emergency_page = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!xlt_emergency_page)
		वापस -ENOMEM;

	mlx5_ib_event_wq = alloc_ordered_workqueue("mlx5_ib_event_wq", 0);
	अगर (!mlx5_ib_event_wq) अणु
		मुक्त_page((अचिन्हित दीर्घ)xlt_emergency_page);
		वापस -ENOMEM;
	पूर्ण

	mlx5_ib_odp_init();
	ret = mlx5r_rep_init();
	अगर (ret)
		जाओ rep_err;
	ret = auxiliary_driver_रेजिस्टर(&mlx5r_mp_driver);
	अगर (ret)
		जाओ mp_err;
	ret = auxiliary_driver_रेजिस्टर(&mlx5r_driver);
	अगर (ret)
		जाओ drv_err;
	वापस 0;

drv_err:
	auxiliary_driver_unरेजिस्टर(&mlx5r_mp_driver);
mp_err:
	mlx5r_rep_cleanup();
rep_err:
	destroy_workqueue(mlx5_ib_event_wq);
	मुक्त_page((अचिन्हित दीर्घ)xlt_emergency_page);
	वापस ret;
पूर्ण

अटल व्योम __निकास mlx5_ib_cleanup(व्योम)
अणु
	auxiliary_driver_unरेजिस्टर(&mlx5r_driver);
	auxiliary_driver_unरेजिस्टर(&mlx5r_mp_driver);
	mlx5r_rep_cleanup();

	destroy_workqueue(mlx5_ib_event_wq);
	मुक्त_page((अचिन्हित दीर्घ)xlt_emergency_page);
पूर्ण

module_init(mlx5_ib_init);
module_निकास(mlx5_ib_cleanup);
