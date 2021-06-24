<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 */

#समावेश <linux/mlx5/vport.h>
#समावेश "ib_rep.h"
#समावेश "srq.h"

अटल पूर्णांक
mlx5_ib_set_vport_rep(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eचयन_rep *rep)
अणु
	काष्ठा mlx5_ib_dev *ibdev;
	पूर्णांक vport_index;

	ibdev = mlx5_eचयन_uplink_get_proto_dev(dev->priv.eचयन, REP_IB);
	vport_index = rep->vport_index;

	ibdev->port[vport_index].rep = rep;
	rep->rep_data[REP_IB].priv = ibdev;
	ग_लिखो_lock(&ibdev->port[vport_index].roce.netdev_lock);
	ibdev->port[vport_index].roce.netdev =
		mlx5_ib_get_rep_netdev(rep->esw, rep->vport);
	ग_लिखो_unlock(&ibdev->port[vport_index].roce.netdev_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_ib_vport_rep_load(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eचयन_rep *rep)
अणु
	u32 num_ports = mlx5_eचयन_get_total_vports(dev);
	स्थिर काष्ठा mlx5_ib_profile *profile;
	काष्ठा mlx5_ib_dev *ibdev;
	पूर्णांक vport_index;
	पूर्णांक ret;

	अगर (rep->vport == MLX5_VPORT_UPLINK)
		profile = &raw_eth_profile;
	अन्यथा
		वापस mlx5_ib_set_vport_rep(dev, rep);

	ibdev = ib_alloc_device(mlx5_ib_dev, ib_dev);
	अगर (!ibdev)
		वापस -ENOMEM;

	ibdev->port = kसुस्मृति(num_ports, माप(*ibdev->port),
			      GFP_KERNEL);
	अगर (!ibdev->port) अणु
		ret = -ENOMEM;
		जाओ fail_port;
	पूर्ण

	ibdev->is_rep = true;
	vport_index = rep->vport_index;
	ibdev->port[vport_index].rep = rep;
	ibdev->port[vport_index].roce.netdev =
		mlx5_ib_get_rep_netdev(dev->priv.eचयन, rep->vport);
	ibdev->mdev = dev;
	ibdev->num_ports = num_ports;

	ret = __mlx5_ib_add(ibdev, profile);
	अगर (ret)
		जाओ fail_add;

	rep->rep_data[REP_IB].priv = ibdev;

	वापस 0;

fail_add:
	kमुक्त(ibdev->port);
fail_port:
	ib_dealloc_device(&ibdev->ib_dev);
	वापस ret;
पूर्ण

अटल व्योम *mlx5_ib_rep_to_dev(काष्ठा mlx5_eचयन_rep *rep)
अणु
	वापस rep->rep_data[REP_IB].priv;
पूर्ण

अटल व्योम
mlx5_ib_vport_rep_unload(काष्ठा mlx5_eचयन_rep *rep)
अणु
	काष्ठा mlx5_ib_dev *dev = mlx5_ib_rep_to_dev(rep);
	काष्ठा mlx5_ib_port *port;

	port = &dev->port[rep->vport_index];
	ग_लिखो_lock(&port->roce.netdev_lock);
	port->roce.netdev = शून्य;
	ग_लिखो_unlock(&port->roce.netdev_lock);
	rep->rep_data[REP_IB].priv = शून्य;
	port->rep = शून्य;

	अगर (rep->vport == MLX5_VPORT_UPLINK)
		__mlx5_ib_हटाओ(dev, dev->profile, MLX5_IB_STAGE_MAX);
पूर्ण

अटल स्थिर काष्ठा mlx5_eचयन_rep_ops rep_ops = अणु
	.load = mlx5_ib_vport_rep_load,
	.unload = mlx5_ib_vport_rep_unload,
	.get_proto_dev = mlx5_ib_rep_to_dev,
पूर्ण;

काष्ठा net_device *mlx5_ib_get_rep_netdev(काष्ठा mlx5_eचयन *esw,
					  u16 vport_num)
अणु
	वापस mlx5_eचयन_get_proto_dev(esw, vport_num, REP_ETH);
पूर्ण

काष्ठा mlx5_flow_handle *create_flow_rule_vport_sq(काष्ठा mlx5_ib_dev *dev,
						   काष्ठा mlx5_ib_sq *sq,
						   u32 port)
अणु
	काष्ठा mlx5_eचयन *esw = dev->mdev->priv.eचयन;
	काष्ठा mlx5_eचयन_rep *rep;

	अगर (!dev->is_rep || !port)
		वापस शून्य;

	अगर (!dev->port[port - 1].rep)
		वापस ERR_PTR(-EINVAL);

	rep = dev->port[port - 1].rep;

	वापस mlx5_eचयन_add_send_to_vport_rule(esw, rep, sq->base.mqp.qpn);
पूर्ण

अटल पूर्णांक mlx5r_rep_probe(काष्ठा auxiliary_device *adev,
			   स्थिर काष्ठा auxiliary_device_id *id)
अणु
	काष्ठा mlx5_adev *idev = container_of(adev, काष्ठा mlx5_adev, adev);
	काष्ठा mlx5_core_dev *mdev = idev->mdev;
	काष्ठा mlx5_eचयन *esw;

	esw = mdev->priv.eचयन;
	mlx5_eचयन_रेजिस्टर_vport_reps(esw, &rep_ops, REP_IB);
	वापस 0;
पूर्ण

अटल व्योम mlx5r_rep_हटाओ(काष्ठा auxiliary_device *adev)
अणु
	काष्ठा mlx5_adev *idev = container_of(adev, काष्ठा mlx5_adev, adev);
	काष्ठा mlx5_core_dev *mdev = idev->mdev;
	काष्ठा mlx5_eचयन *esw;

	esw = mdev->priv.eचयन;
	mlx5_eचयन_unरेजिस्टर_vport_reps(esw, REP_IB);
पूर्ण

अटल स्थिर काष्ठा auxiliary_device_id mlx5r_rep_id_table[] = अणु
	अणु .name = MLX5_ADEV_NAME ".rdma-rep", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(auxiliary, mlx5r_rep_id_table);

अटल काष्ठा auxiliary_driver mlx5r_rep_driver = अणु
	.name = "rep",
	.probe = mlx5r_rep_probe,
	.हटाओ = mlx5r_rep_हटाओ,
	.id_table = mlx5r_rep_id_table,
पूर्ण;

पूर्णांक mlx5r_rep_init(व्योम)
अणु
	वापस auxiliary_driver_रेजिस्टर(&mlx5r_rep_driver);
पूर्ण

व्योम mlx5r_rep_cleanup(व्योम)
अणु
	auxiliary_driver_unरेजिस्टर(&mlx5r_rep_driver);
पूर्ण
