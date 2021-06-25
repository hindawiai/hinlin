<शैली गुरु>
/*
 * Copyright (c) 2006, 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>

#समावेश <net/ipv6.h>
#समावेश <net/addrconf.h>
#समावेश <net/devlink.h>

#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>

#समावेश <net/bonding.h>

#समावेश <linux/mlx4/driver.h>
#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/mlx4/qp.h>

#समावेश "mlx4_ib.h"
#समावेश <rdma/mlx4-abi.h>

#घोषणा DRV_NAME	MLX4_IB_DRV_NAME
#घोषणा DRV_VERSION	"4.0-0"

#घोषणा MLX4_IB_FLOW_MAX_PRIO 0xFFF
#घोषणा MLX4_IB_FLOW_QPN_MASK 0xFFFFFF
#घोषणा MLX4_IB_CARD_REV_A0   0xA0

MODULE_AUTHOR("Roland Dreier");
MODULE_DESCRIPTION("Mellanox ConnectX HCA InfiniBand driver");
MODULE_LICENSE("Dual BSD/GPL");

पूर्णांक mlx4_ib_sm_guid_assign = 0;
module_param_named(sm_guid_assign, mlx4_ib_sm_guid_assign, पूर्णांक, 0444);
MODULE_PARM_DESC(sm_guid_assign, "Enable SM alias_GUID assignment if sm_guid_assign > 0 (Default: 0)");

अटल स्थिर अक्षर mlx4_ib_version[] =
	DRV_NAME ": Mellanox ConnectX InfiniBand driver v"
	DRV_VERSION "\n";

अटल व्योम करो_slave_init(काष्ठा mlx4_ib_dev *ibdev, पूर्णांक slave, पूर्णांक करो_init);
अटल क्रमागत rdma_link_layer mlx4_ib_port_link_layer(काष्ठा ib_device *device,
						    u32 port_num);

अटल काष्ठा workqueue_काष्ठा *wq;

अटल व्योम init_query_mad(काष्ठा ib_smp *mad)
अणु
	mad->base_version  = 1;
	mad->mgmt_class    = IB_MGMT_CLASS_SUBN_LID_ROUTED;
	mad->class_version = 1;
	mad->method	   = IB_MGMT_METHOD_GET;
पूर्ण

अटल पूर्णांक check_flow_steering_support(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक eth_num_ports = 0;
	पूर्णांक ib_num_ports = 0;

	पूर्णांक dmfs = dev->caps.steering_mode == MLX4_STEERING_MODE_DEVICE_MANAGED;

	अगर (dmfs) अणु
		पूर्णांक i;
		mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_ETH)
			eth_num_ports++;
		mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_IB)
			ib_num_ports++;
		dmfs &= (!ib_num_ports ||
			 (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_DMFS_IPOIB)) &&
			(!eth_num_ports ||
			 (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_FS_EN));
		अगर (ib_num_ports && mlx4_is_mfunc(dev)) अणु
			pr_warn("Device managed flow steering is unavailable for IB port in multifunction env.\n");
			dmfs = 0;
		पूर्ण
	पूर्ण
	वापस dmfs;
पूर्ण

अटल पूर्णांक num_ib_ports(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक ib_ports = 0;
	पूर्णांक i;

	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_IB)
		ib_ports++;

	वापस ib_ports;
पूर्ण

अटल काष्ठा net_device *mlx4_ib_get_netdev(काष्ठा ib_device *device,
					     u32 port_num)
अणु
	काष्ठा mlx4_ib_dev *ibdev = to_mdev(device);
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	dev = mlx4_get_protocol_dev(ibdev->dev, MLX4_PROT_ETH, port_num);

	अगर (dev) अणु
		अगर (mlx4_is_bonded(ibdev->dev)) अणु
			काष्ठा net_device *upper = शून्य;

			upper = netdev_master_upper_dev_get_rcu(dev);
			अगर (upper) अणु
				काष्ठा net_device *active;

				active = bond_option_active_slave_get_rcu(netdev_priv(upper));
				अगर (active)
					dev = active;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (dev)
		dev_hold(dev);

	rcu_पढ़ो_unlock();
	वापस dev;
पूर्ण

अटल पूर्णांक mlx4_ib_update_gids_v1(काष्ठा gid_entry *gids,
				  काष्ठा mlx4_ib_dev *ibdev,
				  u32 port_num)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err;
	काष्ठा mlx4_dev *dev = ibdev->dev;
	पूर्णांक i;
	जोड़ ib_gid *gid_tbl;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस -ENOMEM;

	gid_tbl = mailbox->buf;

	क्रम (i = 0; i < MLX4_MAX_PORT_GIDS; ++i)
		स_नकल(&gid_tbl[i], &gids[i].gid, माप(जोड़ ib_gid));

	err = mlx4_cmd(dev, mailbox->dma,
		       MLX4_SET_PORT_GID_TABLE << 8 | port_num,
		       1, MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_WRAPPED);
	अगर (mlx4_is_bonded(dev))
		err += mlx4_cmd(dev, mailbox->dma,
				MLX4_SET_PORT_GID_TABLE << 8 | 2,
				1, MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
				MLX4_CMD_WRAPPED);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_update_gids_v1_v2(काष्ठा gid_entry *gids,
				     काष्ठा mlx4_ib_dev *ibdev,
				     u32 port_num)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err;
	काष्ठा mlx4_dev *dev = ibdev->dev;
	पूर्णांक i;
	काष्ठा अणु
		जोड़ ib_gid	gid;
		__be32		rsrvd1[2];
		__be16		rsrvd2;
		u8		type;
		u8		version;
		__be32		rsrvd3;
	पूर्ण *gid_tbl;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस -ENOMEM;

	gid_tbl = mailbox->buf;
	क्रम (i = 0; i < MLX4_MAX_PORT_GIDS; ++i) अणु
		स_नकल(&gid_tbl[i].gid, &gids[i].gid, माप(जोड़ ib_gid));
		अगर (gids[i].gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) अणु
			gid_tbl[i].version = 2;
			अगर (!ipv6_addr_v4mapped((काष्ठा in6_addr *)&gids[i].gid))
				gid_tbl[i].type = 1;
		पूर्ण
	पूर्ण

	err = mlx4_cmd(dev, mailbox->dma,
		       MLX4_SET_PORT_ROCE_ADDR << 8 | port_num,
		       1, MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_WRAPPED);
	अगर (mlx4_is_bonded(dev))
		err += mlx4_cmd(dev, mailbox->dma,
				MLX4_SET_PORT_ROCE_ADDR << 8 | 2,
				1, MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
				MLX4_CMD_WRAPPED);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_update_gids(काष्ठा gid_entry *gids,
			       काष्ठा mlx4_ib_dev *ibdev,
			       u32 port_num)
अणु
	अगर (ibdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ROCE_V1_V2)
		वापस mlx4_ib_update_gids_v1_v2(gids, ibdev, port_num);

	वापस mlx4_ib_update_gids_v1(gids, ibdev, port_num);
पूर्ण

अटल व्योम मुक्त_gid_entry(काष्ठा gid_entry *entry)
अणु
	स_रखो(&entry->gid, 0, माप(entry->gid));
	kमुक्त(entry->ctx);
	entry->ctx = शून्य;
पूर्ण

अटल पूर्णांक mlx4_ib_add_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context)
अणु
	काष्ठा mlx4_ib_dev *ibdev = to_mdev(attr->device);
	काष्ठा mlx4_ib_iboe *iboe = &ibdev->iboe;
	काष्ठा mlx4_port_gid_table   *port_gid_table;
	पूर्णांक मुक्त = -1, found = -1;
	पूर्णांक ret = 0;
	पूर्णांक hw_update = 0;
	पूर्णांक i;
	काष्ठा gid_entry *gids = शून्य;
	u16 vlan_id = 0xffff;
	u8 mac[ETH_ALEN];

	अगर (!rdma_cap_roce_gid_table(attr->device, attr->port_num))
		वापस -EINVAL;

	अगर (attr->port_num > MLX4_MAX_PORTS)
		वापस -EINVAL;

	अगर (!context)
		वापस -EINVAL;

	ret = rdma_पढ़ो_gid_l2_fields(attr, &vlan_id, &mac[0]);
	अगर (ret)
		वापस ret;
	port_gid_table = &iboe->gids[attr->port_num - 1];
	spin_lock_bh(&iboe->lock);
	क्रम (i = 0; i < MLX4_MAX_PORT_GIDS; ++i) अणु
		अगर (!स_भेद(&port_gid_table->gids[i].gid,
			    &attr->gid, माप(attr->gid)) &&
		    port_gid_table->gids[i].gid_type == attr->gid_type &&
		    port_gid_table->gids[i].vlan_id == vlan_id)  अणु
			found = i;
			अवरोध;
		पूर्ण
		अगर (मुक्त < 0 && rdma_is_zero_gid(&port_gid_table->gids[i].gid))
			मुक्त = i; /* HW has space */
	पूर्ण

	अगर (found < 0) अणु
		अगर (मुक्त < 0) अणु
			ret = -ENOSPC;
		पूर्ण अन्यथा अणु
			port_gid_table->gids[मुक्त].ctx = kदो_स्मृति(माप(*port_gid_table->gids[मुक्त].ctx), GFP_ATOMIC);
			अगर (!port_gid_table->gids[मुक्त].ctx) अणु
				ret = -ENOMEM;
			पूर्ण अन्यथा अणु
				*context = port_gid_table->gids[मुक्त].ctx;
				स_नकल(&port_gid_table->gids[मुक्त].gid,
				       &attr->gid, माप(attr->gid));
				port_gid_table->gids[मुक्त].gid_type = attr->gid_type;
				port_gid_table->gids[मुक्त].vlan_id = vlan_id;
				port_gid_table->gids[मुक्त].ctx->real_index = मुक्त;
				port_gid_table->gids[मुक्त].ctx->refcount = 1;
				hw_update = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा gid_cache_context *ctx = port_gid_table->gids[found].ctx;
		*context = ctx;
		ctx->refcount++;
	पूर्ण
	अगर (!ret && hw_update) अणु
		gids = kदो_स्मृति_array(MLX4_MAX_PORT_GIDS, माप(*gids),
				     GFP_ATOMIC);
		अगर (!gids) अणु
			ret = -ENOMEM;
			*context = शून्य;
			मुक्त_gid_entry(&port_gid_table->gids[मुक्त]);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < MLX4_MAX_PORT_GIDS; i++) अणु
				स_नकल(&gids[i].gid, &port_gid_table->gids[i].gid, माप(जोड़ ib_gid));
				gids[i].gid_type = port_gid_table->gids[i].gid_type;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&iboe->lock);

	अगर (!ret && hw_update) अणु
		ret = mlx4_ib_update_gids(gids, ibdev, attr->port_num);
		अगर (ret) अणु
			spin_lock_bh(&iboe->lock);
			*context = शून्य;
			मुक्त_gid_entry(&port_gid_table->gids[मुक्त]);
			spin_unlock_bh(&iboe->lock);
		पूर्ण
		kमुक्त(gids);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_ib_del_gid(स्थिर काष्ठा ib_gid_attr *attr, व्योम **context)
अणु
	काष्ठा gid_cache_context *ctx = *context;
	काष्ठा mlx4_ib_dev *ibdev = to_mdev(attr->device);
	काष्ठा mlx4_ib_iboe *iboe = &ibdev->iboe;
	काष्ठा mlx4_port_gid_table   *port_gid_table;
	पूर्णांक ret = 0;
	पूर्णांक hw_update = 0;
	काष्ठा gid_entry *gids = शून्य;

	अगर (!rdma_cap_roce_gid_table(attr->device, attr->port_num))
		वापस -EINVAL;

	अगर (attr->port_num > MLX4_MAX_PORTS)
		वापस -EINVAL;

	port_gid_table = &iboe->gids[attr->port_num - 1];
	spin_lock_bh(&iboe->lock);
	अगर (ctx) अणु
		ctx->refcount--;
		अगर (!ctx->refcount) अणु
			अचिन्हित पूर्णांक real_index = ctx->real_index;

			मुक्त_gid_entry(&port_gid_table->gids[real_index]);
			hw_update = 1;
		पूर्ण
	पूर्ण
	अगर (!ret && hw_update) अणु
		पूर्णांक i;

		gids = kदो_स्मृति_array(MLX4_MAX_PORT_GIDS, माप(*gids),
				     GFP_ATOMIC);
		अगर (!gids) अणु
			ret = -ENOMEM;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < MLX4_MAX_PORT_GIDS; i++) अणु
				स_नकल(&gids[i].gid,
				       &port_gid_table->gids[i].gid,
				       माप(जोड़ ib_gid));
				gids[i].gid_type =
				    port_gid_table->gids[i].gid_type;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&iboe->lock);

	अगर (!ret && hw_update) अणु
		ret = mlx4_ib_update_gids(gids, ibdev, attr->port_num);
		kमुक्त(gids);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक mlx4_ib_gid_index_to_real_index(काष्ठा mlx4_ib_dev *ibdev,
				    स्थिर काष्ठा ib_gid_attr *attr)
अणु
	काष्ठा mlx4_ib_iboe *iboe = &ibdev->iboe;
	काष्ठा gid_cache_context *ctx = शून्य;
	काष्ठा mlx4_port_gid_table   *port_gid_table;
	पूर्णांक real_index = -EINVAL;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	u32 port_num = attr->port_num;

	अगर (port_num > MLX4_MAX_PORTS)
		वापस -EINVAL;

	अगर (mlx4_is_bonded(ibdev->dev))
		port_num = 1;

	अगर (!rdma_cap_roce_gid_table(&ibdev->ib_dev, port_num))
		वापस attr->index;

	spin_lock_irqsave(&iboe->lock, flags);
	port_gid_table = &iboe->gids[port_num - 1];

	क्रम (i = 0; i < MLX4_MAX_PORT_GIDS; ++i)
		अगर (!स_भेद(&port_gid_table->gids[i].gid,
			    &attr->gid, माप(attr->gid)) &&
		    attr->gid_type == port_gid_table->gids[i].gid_type) अणु
			ctx = port_gid_table->gids[i].ctx;
			अवरोध;
		पूर्ण
	अगर (ctx)
		real_index = ctx->real_index;
	spin_unlock_irqrestore(&iboe->lock, flags);
	वापस real_index;
पूर्ण

अटल पूर्णांक mlx4_ib_query_device(काष्ठा ib_device *ibdev,
				काष्ठा ib_device_attr *props,
				काष्ठा ib_udata *uhw)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err;
	पूर्णांक have_ib_ports;
	काष्ठा mlx4_uverbs_ex_query_device cmd;
	काष्ठा mlx4_uverbs_ex_query_device_resp resp = अणुपूर्ण;
	काष्ठा mlx4_घड़ी_params घड़ी_params;

	अगर (uhw->inlen) अणु
		अगर (uhw->inlen < माप(cmd))
			वापस -EINVAL;

		err = ib_copy_from_udata(&cmd, uhw, माप(cmd));
		अगर (err)
			वापस err;

		अगर (cmd.comp_mask)
			वापस -EINVAL;

		अगर (cmd.reserved)
			वापस -EINVAL;
	पूर्ण

	resp.response_length = दुरत्व(typeof(resp), response_length) +
		माप(resp.response_length);
	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	err = -ENOMEM;
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mlx4_MAD_IFC(to_mdev(ibdev), MLX4_MAD_IFC_IGNORE_KEYS,
			   1, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	स_रखो(props, 0, माप *props);

	have_ib_ports = num_ib_ports(dev->dev);

	props->fw_ver = dev->dev->caps.fw_ver;
	props->device_cap_flags    = IB_DEVICE_CHANGE_PHY_PORT |
		IB_DEVICE_PORT_ACTIVE_EVENT		|
		IB_DEVICE_SYS_IMAGE_GUID		|
		IB_DEVICE_RC_RNR_NAK_GEN		|
		IB_DEVICE_BLOCK_MULTICAST_LOOPBACK;
	अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_BAD_PKEY_CNTR)
		props->device_cap_flags |= IB_DEVICE_BAD_PKEY_CNTR;
	अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_BAD_QKEY_CNTR)
		props->device_cap_flags |= IB_DEVICE_BAD_QKEY_CNTR;
	अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_APM && have_ib_ports)
		props->device_cap_flags |= IB_DEVICE_AUTO_PATH_MIG;
	अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_UD_AV_PORT)
		props->device_cap_flags |= IB_DEVICE_UD_AV_PORT_ENFORCE;
	अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_IPOIB_CSUM)
		props->device_cap_flags |= IB_DEVICE_UD_IP_CSUM;
	अगर (dev->dev->caps.max_gso_sz &&
	    (dev->dev->rev_id != MLX4_IB_CARD_REV_A0) &&
	    (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_BLH))
		props->device_cap_flags |= IB_DEVICE_UD_TSO;
	अगर (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_RESERVED_LKEY)
		props->device_cap_flags |= IB_DEVICE_LOCAL_DMA_LKEY;
	अगर ((dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_LOCAL_INV) &&
	    (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_REMOTE_INV) &&
	    (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_FAST_REG_WR))
		props->device_cap_flags |= IB_DEVICE_MEM_MGT_EXTENSIONS;
	अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_XRC)
		props->device_cap_flags |= IB_DEVICE_XRC;
	अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_MEM_WINDOW)
		props->device_cap_flags |= IB_DEVICE_MEM_WINDOW;
	अगर (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_TYPE_2_WIN) अणु
		अगर (dev->dev->caps.bmme_flags & MLX4_BMME_FLAG_WIN_TYPE_2B)
			props->device_cap_flags |= IB_DEVICE_MEM_WINDOW_TYPE_2B;
		अन्यथा
			props->device_cap_flags |= IB_DEVICE_MEM_WINDOW_TYPE_2A;
	पूर्ण
	अगर (dev->steering_support == MLX4_STEERING_MODE_DEVICE_MANAGED)
		props->device_cap_flags |= IB_DEVICE_MANAGED_FLOW_STEERING;

	props->device_cap_flags |= IB_DEVICE_RAW_IP_CSUM;

	props->venकरोr_id	   = be32_to_cpup((__be32 *) (out_mad->data + 36)) &
		0xffffff;
	props->venकरोr_part_id	   = dev->dev->persist->pdev->device;
	props->hw_ver		   = be32_to_cpup((__be32 *) (out_mad->data + 32));
	स_नकल(&props->sys_image_guid, out_mad->data +	4, 8);

	props->max_mr_size	   = ~0ull;
	props->page_size_cap	   = dev->dev->caps.page_size_cap;
	props->max_qp		   = dev->dev->quotas.qp;
	props->max_qp_wr	   = dev->dev->caps.max_wqes - MLX4_IB_SQ_MAX_SPARE;
	props->max_send_sge =
		min(dev->dev->caps.max_sq_sg, dev->dev->caps.max_rq_sg);
	props->max_recv_sge =
		min(dev->dev->caps.max_sq_sg, dev->dev->caps.max_rq_sg);
	props->max_sge_rd = MLX4_MAX_SGE_RD;
	props->max_cq		   = dev->dev->quotas.cq;
	props->max_cqe		   = dev->dev->caps.max_cqes;
	props->max_mr		   = dev->dev->quotas.mpt;
	props->max_pd		   = dev->dev->caps.num_pds - dev->dev->caps.reserved_pds;
	props->max_qp_rd_atom	   = dev->dev->caps.max_qp_dest_rdma;
	props->max_qp_init_rd_atom = dev->dev->caps.max_qp_init_rdma;
	props->max_res_rd_atom	   = props->max_qp_rd_atom * props->max_qp;
	props->max_srq		   = dev->dev->quotas.srq;
	props->max_srq_wr	   = dev->dev->caps.max_srq_wqes - 1;
	props->max_srq_sge	   = dev->dev->caps.max_srq_sge;
	props->max_fast_reg_page_list_len = MLX4_MAX_FAST_REG_PAGES;
	props->local_ca_ack_delay  = dev->dev->caps.local_ca_ack_delay;
	props->atomic_cap	   = dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_ATOMIC ?
		IB_ATOMIC_HCA : IB_ATOMIC_NONE;
	props->masked_atomic_cap   = props->atomic_cap;
	props->max_pkeys	   = dev->dev->caps.pkey_table_len[1];
	props->max_mcast_grp	   = dev->dev->caps.num_mgms + dev->dev->caps.num_amgms;
	props->max_mcast_qp_attach = dev->dev->caps.num_qp_per_mgm;
	props->max_total_mcast_qp_attach = props->max_mcast_qp_attach *
					   props->max_mcast_grp;
	props->hca_core_घड़ी = dev->dev->caps.hca_core_घड़ी * 1000UL;
	props->बारtamp_mask = 0xFFFFFFFFFFFFULL;
	props->max_ah = पूर्णांक_उच्च;

	अगर (mlx4_ib_port_link_layer(ibdev, 1) == IB_LINK_LAYER_ETHERNET ||
	    mlx4_ib_port_link_layer(ibdev, 2) == IB_LINK_LAYER_ETHERNET) अणु
		अगर (dev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS) अणु
			props->rss_caps.max_rwq_indirection_tables =
				props->max_qp;
			props->rss_caps.max_rwq_indirection_table_size =
				dev->dev->caps.max_rss_tbl_sz;
			props->rss_caps.supported_qpts = 1 << IB_QPT_RAW_PACKET;
			props->max_wq_type_rq = props->max_qp;
		पूर्ण

		अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_FCS_KEEP)
			props->raw_packet_caps |= IB_RAW_PACKET_CAP_SCATTER_FCS;
	पूर्ण

	props->cq_caps.max_cq_moderation_count = MLX4_MAX_CQ_COUNT;
	props->cq_caps.max_cq_moderation_period = MLX4_MAX_CQ_PERIOD;

	अगर (uhw->outlen >= resp.response_length + माप(resp.hca_core_घड़ी_offset)) अणु
		resp.response_length += माप(resp.hca_core_घड़ी_offset);
		अगर (!mlx4_get_पूर्णांकernal_घड़ी_params(dev->dev, &घड़ी_params)) अणु
			resp.comp_mask |= MLX4_IB_QUERY_DEV_RESP_MASK_CORE_CLOCK_OFFSET;
			resp.hca_core_घड़ी_offset = घड़ी_params.offset % PAGE_SIZE;
		पूर्ण
	पूर्ण

	अगर (uhw->outlen >= resp.response_length +
	    माप(resp.max_inl_recv_sz)) अणु
		resp.response_length += माप(resp.max_inl_recv_sz);
		resp.max_inl_recv_sz  = dev->dev->caps.max_rq_sg *
			माप(काष्ठा mlx4_wqe_data_seg);
	पूर्ण

	अगर (दुरत्वend(typeof(resp), rss_caps) <= uhw->outlen) अणु
		अगर (props->rss_caps.supported_qpts) अणु
			resp.rss_caps.rx_hash_function =
				MLX4_IB_RX_HASH_FUNC_TOEPLITZ;

			resp.rss_caps.rx_hash_fields_mask =
				MLX4_IB_RX_HASH_SRC_IPV4 |
				MLX4_IB_RX_HASH_DST_IPV4 |
				MLX4_IB_RX_HASH_SRC_IPV6 |
				MLX4_IB_RX_HASH_DST_IPV6 |
				MLX4_IB_RX_HASH_SRC_PORT_TCP |
				MLX4_IB_RX_HASH_DST_PORT_TCP |
				MLX4_IB_RX_HASH_SRC_PORT_UDP |
				MLX4_IB_RX_HASH_DST_PORT_UDP;

			अगर (dev->dev->caps.tunnel_offload_mode ==
			    MLX4_TUNNEL_OFFLOAD_MODE_VXLAN)
				resp.rss_caps.rx_hash_fields_mask |=
					MLX4_IB_RX_HASH_INNER;
		पूर्ण
		resp.response_length = दुरत्व(typeof(resp), rss_caps) +
				       माप(resp.rss_caps);
	पूर्ण

	अगर (दुरत्वend(typeof(resp), tso_caps) <= uhw->outlen) अणु
		अगर (dev->dev->caps.max_gso_sz &&
		    ((mlx4_ib_port_link_layer(ibdev, 1) ==
		    IB_LINK_LAYER_ETHERNET) ||
		    (mlx4_ib_port_link_layer(ibdev, 2) ==
		    IB_LINK_LAYER_ETHERNET))) अणु
			resp.tso_caps.max_tso = dev->dev->caps.max_gso_sz;
			resp.tso_caps.supported_qpts |=
				1 << IB_QPT_RAW_PACKET;
		पूर्ण
		resp.response_length = दुरत्व(typeof(resp), tso_caps) +
				       माप(resp.tso_caps);
	पूर्ण

	अगर (uhw->outlen) अणु
		err = ib_copy_to_udata(uhw, &resp, resp.response_length);
		अगर (err)
			जाओ out;
	पूर्ण
out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);

	वापस err;
पूर्ण

अटल क्रमागत rdma_link_layer
mlx4_ib_port_link_layer(काष्ठा ib_device *device, u32 port_num)
अणु
	काष्ठा mlx4_dev *dev = to_mdev(device)->dev;

	वापस dev->caps.port_mask[port_num] == MLX4_PORT_TYPE_IB ?
		IB_LINK_LAYER_INFINIBAND : IB_LINK_LAYER_ETHERNET;
पूर्ण

अटल पूर्णांक ib_link_query_port(काष्ठा ib_device *ibdev, u32 port,
			      काष्ठा ib_port_attr *props, पूर्णांक netw_view)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक ext_active_speed;
	पूर्णांक mad_अगरc_flags = MLX4_MAD_IFC_IGNORE_KEYS;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	अगर (mlx4_is_mfunc(to_mdev(ibdev)->dev) && netw_view)
		mad_अगरc_flags |= MLX4_MAD_IFC_NET_VIEW;

	err = mlx4_MAD_IFC(to_mdev(ibdev), mad_अगरc_flags, port, शून्य, शून्य,
				in_mad, out_mad);
	अगर (err)
		जाओ out;


	props->lid		= be16_to_cpup((__be16 *) (out_mad->data + 16));
	props->lmc		= out_mad->data[34] & 0x7;
	props->sm_lid		= be16_to_cpup((__be16 *) (out_mad->data + 18));
	props->sm_sl		= out_mad->data[36] & 0xf;
	props->state		= out_mad->data[32] & 0xf;
	props->phys_state	= out_mad->data[33] >> 4;
	props->port_cap_flags	= be32_to_cpup((__be32 *) (out_mad->data + 20));
	अगर (netw_view)
		props->gid_tbl_len = out_mad->data[50];
	अन्यथा
		props->gid_tbl_len = to_mdev(ibdev)->dev->caps.gid_table_len[port];
	props->max_msg_sz	= to_mdev(ibdev)->dev->caps.max_msg_sz;
	props->pkey_tbl_len	= to_mdev(ibdev)->dev->caps.pkey_table_len[port];
	props->bad_pkey_cntr	= be16_to_cpup((__be16 *) (out_mad->data + 46));
	props->qkey_viol_cntr	= be16_to_cpup((__be16 *) (out_mad->data + 48));
	props->active_width	= out_mad->data[31] & 0xf;
	props->active_speed	= out_mad->data[35] >> 4;
	props->max_mtu		= out_mad->data[41] & 0xf;
	props->active_mtu	= out_mad->data[36] >> 4;
	props->subnet_समयout	= out_mad->data[51] & 0x1f;
	props->max_vl_num	= out_mad->data[37] >> 4;
	props->init_type_reply	= out_mad->data[41] >> 4;

	/* Check अगर extended speeds (EDR/FDR/...) are supported */
	अगर (props->port_cap_flags & IB_PORT_EXTENDED_SPEEDS_SUP) अणु
		ext_active_speed = out_mad->data[62] >> 4;

		चयन (ext_active_speed) अणु
		हाल 1:
			props->active_speed = IB_SPEED_FDR;
			अवरोध;
		हाल 2:
			props->active_speed = IB_SPEED_EDR;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If reported active speed is QDR, check अगर is FDR-10 */
	अगर (props->active_speed == IB_SPEED_QDR) अणु
		init_query_mad(in_mad);
		in_mad->attr_id = MLX4_ATTR_EXTENDED_PORT_INFO;
		in_mad->attr_mod = cpu_to_be32(port);

		err = mlx4_MAD_IFC(to_mdev(ibdev), mad_अगरc_flags, port,
				   शून्य, शून्य, in_mad, out_mad);
		अगर (err)
			जाओ out;

		/* Checking LinkSpeedActive क्रम FDR-10 */
		अगर (out_mad->data[15] & 0x1)
			props->active_speed = IB_SPEED_FDR10;
	पूर्ण

	/* Aव्योम wrong speed value वापसed by FW अगर the IB link is करोwn. */
	अगर (props->state == IB_PORT_DOWN)
		 props->active_speed = IB_SPEED_SDR;

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल u8 state_to_phys_state(क्रमागत ib_port_state state)
अणु
	वापस state == IB_PORT_ACTIVE ?
		IB_PORT_PHYS_STATE_LINK_UP : IB_PORT_PHYS_STATE_DISABLED;
पूर्ण

अटल पूर्णांक eth_link_query_port(काष्ठा ib_device *ibdev, u32 port,
			       काष्ठा ib_port_attr *props)
अणु

	काष्ठा mlx4_ib_dev *mdev = to_mdev(ibdev);
	काष्ठा mlx4_ib_iboe *iboe = &mdev->iboe;
	काष्ठा net_device *ndev;
	क्रमागत ib_mtu पंचांगp;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err = 0;
	पूर्णांक is_bonded = mlx4_is_bonded(mdev->dev);

	mailbox = mlx4_alloc_cmd_mailbox(mdev->dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	err = mlx4_cmd_box(mdev->dev, 0, mailbox->dma, port, 0,
			   MLX4_CMD_QUERY_PORT, MLX4_CMD_TIME_CLASS_B,
			   MLX4_CMD_WRAPPED);
	अगर (err)
		जाओ out;

	props->active_width	=  (((u8 *)mailbox->buf)[5] == 0x40) ||
				   (((u8 *)mailbox->buf)[5] == 0x20 /*56Gb*/) ?
					   IB_WIDTH_4X : IB_WIDTH_1X;
	props->active_speed	=  (((u8 *)mailbox->buf)[5] == 0x20 /*56Gb*/) ?
					   IB_SPEED_FDR : IB_SPEED_QDR;
	props->port_cap_flags	= IB_PORT_CM_SUP;
	props->ip_gids = true;
	props->gid_tbl_len	= mdev->dev->caps.gid_table_len[port];
	props->max_msg_sz	= mdev->dev->caps.max_msg_sz;
	अगर (mdev->dev->caps.pkey_table_len[port])
		props->pkey_tbl_len = 1;
	props->max_mtu		= IB_MTU_4096;
	props->max_vl_num	= 2;
	props->state		= IB_PORT_DOWN;
	props->phys_state	= state_to_phys_state(props->state);
	props->active_mtu	= IB_MTU_256;
	spin_lock_bh(&iboe->lock);
	ndev = iboe->netdevs[port - 1];
	अगर (ndev && is_bonded) अणु
		rcu_पढ़ो_lock(); /* required to get upper dev */
		ndev = netdev_master_upper_dev_get_rcu(ndev);
		rcu_पढ़ो_unlock();
	पूर्ण
	अगर (!ndev)
		जाओ out_unlock;

	पंचांगp = iboe_get_mtu(ndev->mtu);
	props->active_mtu = पंचांगp ? min(props->max_mtu, पंचांगp) : IB_MTU_256;

	props->state		= (netअगर_running(ndev) && netअगर_carrier_ok(ndev)) ?
					IB_PORT_ACTIVE : IB_PORT_DOWN;
	props->phys_state	= state_to_phys_state(props->state);
out_unlock:
	spin_unlock_bh(&iboe->lock);
out:
	mlx4_मुक्त_cmd_mailbox(mdev->dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक __mlx4_ib_query_port(काष्ठा ib_device *ibdev, u32 port,
			 काष्ठा ib_port_attr *props, पूर्णांक netw_view)
अणु
	पूर्णांक err;

	/* props being zeroed by the caller, aव्योम zeroing it here */

	err = mlx4_ib_port_link_layer(ibdev, port) == IB_LINK_LAYER_INFINIBAND ?
		ib_link_query_port(ibdev, port, props, netw_view) :
				eth_link_query_port(ibdev, port, props);

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_query_port(काष्ठा ib_device *ibdev, u32 port,
			      काष्ठा ib_port_attr *props)
अणु
	/* वापसs host view */
	वापस __mlx4_ib_query_port(ibdev, port, props, 0);
पूर्ण

पूर्णांक __mlx4_ib_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
			जोड़ ib_gid *gid, पूर्णांक netw_view)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक err = -ENOMEM;
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	पूर्णांक clear = 0;
	पूर्णांक mad_अगरc_flags = MLX4_MAD_IFC_IGNORE_KEYS;

	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PORT_INFO;
	in_mad->attr_mod = cpu_to_be32(port);

	अगर (mlx4_is_mfunc(dev->dev) && netw_view)
		mad_अगरc_flags |= MLX4_MAD_IFC_NET_VIEW;

	err = mlx4_MAD_IFC(dev, mad_अगरc_flags, port, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	स_नकल(gid->raw, out_mad->data + 8, 8);

	अगर (mlx4_is_mfunc(dev->dev) && !netw_view) अणु
		अगर (index) अणु
			/* For any index > 0, वापस the null guid */
			err = 0;
			clear = 1;
			जाओ out;
		पूर्ण
	पूर्ण

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_GUID_INFO;
	in_mad->attr_mod = cpu_to_be32(index / 8);

	err = mlx4_MAD_IFC(dev, mad_अगरc_flags, port,
			   शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	स_नकल(gid->raw + 8, out_mad->data + (index % 8) * 8, 8);

out:
	अगर (clear)
		स_रखो(gid->raw + 8, 0, 8);
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_query_gid(काष्ठा ib_device *ibdev, u32 port, पूर्णांक index,
			     जोड़ ib_gid *gid)
अणु
	अगर (rdma_protocol_ib(ibdev, port))
		वापस __mlx4_ib_query_gid(ibdev, port, index, gid, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_ib_query_sl2vl(काष्ठा ib_device *ibdev, u32 port,
			       u64 *sl2vl_tbl)
अणु
	जोड़ sl2vl_tbl_to_u64 sl2vl64;
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक mad_अगरc_flags = MLX4_MAD_IFC_IGNORE_KEYS;
	पूर्णांक err = -ENOMEM;
	पूर्णांक jj;

	अगर (mlx4_is_slave(to_mdev(ibdev)->dev)) अणु
		*sl2vl_tbl = 0;
		वापस 0;
	पूर्ण

	in_mad  = kzalloc(माप(*in_mad), GFP_KERNEL);
	out_mad = kदो_स्मृति(माप(*out_mad), GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_SL_TO_VL_TABLE;
	in_mad->attr_mod = 0;

	अगर (mlx4_is_mfunc(to_mdev(ibdev)->dev))
		mad_अगरc_flags |= MLX4_MAD_IFC_NET_VIEW;

	err = mlx4_MAD_IFC(to_mdev(ibdev), mad_अगरc_flags, port, शून्य, शून्य,
			   in_mad, out_mad);
	अगर (err)
		जाओ out;

	क्रम (jj = 0; jj < 8; jj++)
		sl2vl64.sl8[jj] = ((काष्ठा ib_smp *)out_mad)->data[jj];
	*sl2vl_tbl = sl2vl64.sl64;

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल व्योम mlx4_init_sl2vl_tbl(काष्ठा mlx4_ib_dev *mdev)
अणु
	u64 sl2vl;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 1; i <= mdev->dev->caps.num_ports; i++) अणु
		अगर (mdev->dev->caps.port_type[i] == MLX4_PORT_TYPE_ETH)
			जारी;
		err = mlx4_ib_query_sl2vl(&mdev->ib_dev, i, &sl2vl);
		अगर (err) अणु
			pr_err("Unable to get default sl to vl mapping for port %d.  Using all zeroes (%d)\n",
			       i, err);
			sl2vl = 0;
		पूर्ण
		atomic64_set(&mdev->sl2vl[i - 1], sl2vl);
	पूर्ण
पूर्ण

पूर्णांक __mlx4_ib_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
			 u16 *pkey, पूर्णांक netw_view)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक mad_अगरc_flags = MLX4_MAD_IFC_IGNORE_KEYS;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id  = IB_SMP_ATTR_PKEY_TABLE;
	in_mad->attr_mod = cpu_to_be32(index / 32);

	अगर (mlx4_is_mfunc(to_mdev(ibdev)->dev) && netw_view)
		mad_अगरc_flags |= MLX4_MAD_IFC_NET_VIEW;

	err = mlx4_MAD_IFC(to_mdev(ibdev), mad_अगरc_flags, port, शून्य, शून्य,
			   in_mad, out_mad);
	अगर (err)
		जाओ out;

	*pkey = be16_to_cpu(((__be16 *) out_mad->data)[index % 32]);

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_query_pkey(काष्ठा ib_device *ibdev, u32 port, u16 index,
			      u16 *pkey)
अणु
	वापस __mlx4_ib_query_pkey(ibdev, port, index, pkey, 0);
पूर्ण

अटल पूर्णांक mlx4_ib_modअगरy_device(काष्ठा ib_device *ibdev, पूर्णांक mask,
				 काष्ठा ib_device_modअगरy *props)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	अचिन्हित दीर्घ flags;

	अगर (mask & ~IB_DEVICE_MODIFY_NODE_DESC)
		वापस -EOPNOTSUPP;

	अगर (!(mask & IB_DEVICE_MODIFY_NODE_DESC))
		वापस 0;

	अगर (mlx4_is_slave(to_mdev(ibdev)->dev))
		वापस -EOPNOTSUPP;

	spin_lock_irqsave(&to_mdev(ibdev)->sm_lock, flags);
	स_नकल(ibdev->node_desc, props->node_desc, IB_DEVICE_NODE_DESC_MAX);
	spin_unlock_irqrestore(&to_mdev(ibdev)->sm_lock, flags);

	/*
	 * If possible, pass node desc to FW, so it can generate
	 * a 144 trap.  If cmd fails, just ignore.
	 */
	mailbox = mlx4_alloc_cmd_mailbox(to_mdev(ibdev)->dev);
	अगर (IS_ERR(mailbox))
		वापस 0;

	स_नकल(mailbox->buf, props->node_desc, IB_DEVICE_NODE_DESC_MAX);
	mlx4_cmd(to_mdev(ibdev)->dev, mailbox->dma, 1, 0,
		 MLX4_CMD_SET_NODE, MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(to_mdev(ibdev)->dev, mailbox);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_ib_SET_PORT(काष्ठा mlx4_ib_dev *dev, u32 port,
			    पूर्णांक reset_qkey_viols, u32 cap_mask)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev->dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	अगर (dev->dev->flags & MLX4_FLAG_OLD_PORT_CMDS) अणु
		*(u8 *) mailbox->buf	     = !!reset_qkey_viols << 6;
		((__be32 *) mailbox->buf)[2] = cpu_to_be32(cap_mask);
	पूर्ण अन्यथा अणु
		((u8 *) mailbox->buf)[3]     = !!reset_qkey_viols;
		((__be32 *) mailbox->buf)[1] = cpu_to_be32(cap_mask);
	पूर्ण

	err = mlx4_cmd(dev->dev, mailbox->dma, port, MLX4_SET_PORT_IB_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_WRAPPED);

	mlx4_मुक्त_cmd_mailbox(dev->dev, mailbox);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_modअगरy_port(काष्ठा ib_device *ibdev, u32 port, पूर्णांक mask,
			       काष्ठा ib_port_modअगरy *props)
अणु
	काष्ठा mlx4_ib_dev *mdev = to_mdev(ibdev);
	u8 is_eth = mdev->dev->caps.port_type[port] == MLX4_PORT_TYPE_ETH;
	काष्ठा ib_port_attr attr;
	u32 cap_mask;
	पूर्णांक err;

	/* वापस OK अगर this is RoCE. CM calls ib_modअगरy_port() regardless
	 * of whether port link layer is ETH or IB. For ETH ports, qkey
	 * violations and port capabilities are not meaningful.
	 */
	अगर (is_eth)
		वापस 0;

	mutex_lock(&mdev->cap_mask_mutex);

	err = ib_query_port(ibdev, port, &attr);
	अगर (err)
		जाओ out;

	cap_mask = (attr.port_cap_flags | props->set_port_cap_mask) &
		~props->clr_port_cap_mask;

	err = mlx4_ib_SET_PORT(mdev, port,
			       !!(mask & IB_PORT_RESET_QKEY_CNTR),
			       cap_mask);

out:
	mutex_unlock(&to_mdev(ibdev)->cap_mask_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_alloc_ucontext(काष्ठा ib_ucontext *uctx,
				  काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = uctx->device;
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx4_ib_ucontext *context = to_mucontext(uctx);
	काष्ठा mlx4_ib_alloc_ucontext_resp_v3 resp_v3;
	काष्ठा mlx4_ib_alloc_ucontext_resp resp;
	पूर्णांक err;

	अगर (!dev->ib_active)
		वापस -EAGAIN;

	अगर (ibdev->ops.uverbs_abi_ver ==
	    MLX4_IB_UVERBS_NO_DEV_CAPS_ABI_VERSION) अणु
		resp_v3.qp_tab_size      = dev->dev->caps.num_qps;
		resp_v3.bf_reg_size      = dev->dev->caps.bf_reg_size;
		resp_v3.bf_regs_per_page = dev->dev->caps.bf_regs_per_page;
	पूर्ण अन्यथा अणु
		resp.dev_caps	      = dev->dev->caps.userspace_caps;
		resp.qp_tab_size      = dev->dev->caps.num_qps;
		resp.bf_reg_size      = dev->dev->caps.bf_reg_size;
		resp.bf_regs_per_page = dev->dev->caps.bf_regs_per_page;
		resp.cqe_size	      = dev->dev->caps.cqe_size;
	पूर्ण

	err = mlx4_uar_alloc(to_mdev(ibdev)->dev, &context->uar);
	अगर (err)
		वापस err;

	INIT_LIST_HEAD(&context->db_page_list);
	mutex_init(&context->db_page_mutex);

	INIT_LIST_HEAD(&context->wqn_ranges_list);
	mutex_init(&context->wqn_ranges_mutex);

	अगर (ibdev->ops.uverbs_abi_ver == MLX4_IB_UVERBS_NO_DEV_CAPS_ABI_VERSION)
		err = ib_copy_to_udata(udata, &resp_v3, माप(resp_v3));
	अन्यथा
		err = ib_copy_to_udata(udata, &resp, माप(resp));

	अगर (err) अणु
		mlx4_uar_मुक्त(to_mdev(ibdev)->dev, &context->uar);
		वापस -EFAULT;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mlx4_ib_dealloc_ucontext(काष्ठा ib_ucontext *ibcontext)
अणु
	काष्ठा mlx4_ib_ucontext *context = to_mucontext(ibcontext);

	mlx4_uar_मुक्त(to_mdev(ibcontext->device)->dev, &context->uar);
पूर्ण

अटल व्योम mlx4_ib_disassociate_ucontext(काष्ठा ib_ucontext *ibcontext)
अणु
पूर्ण

अटल पूर्णांक mlx4_ib_mmap(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(context->device);

	चयन (vma->vm_pgoff) अणु
	हाल 0:
		वापस rdma_user_mmap_io(context, vma,
					 to_mucontext(context)->uar.pfn,
					 PAGE_SIZE,
					 pgprot_noncached(vma->vm_page_prot),
					 शून्य);

	हाल 1:
		अगर (dev->dev->caps.bf_reg_size == 0)
			वापस -EINVAL;
		वापस rdma_user_mmap_io(
			context, vma,
			to_mucontext(context)->uar.pfn +
				dev->dev->caps.num_uars,
			PAGE_SIZE, pgprot_ग_लिखोcombine(vma->vm_page_prot),
			शून्य);

	हाल 3: अणु
		काष्ठा mlx4_घड़ी_params params;
		पूर्णांक ret;

		ret = mlx4_get_पूर्णांकernal_घड़ी_params(dev->dev, &params);
		अगर (ret)
			वापस ret;

		वापस rdma_user_mmap_io(
			context, vma,
			(pci_resource_start(dev->dev->persist->pdev,
					    params.bar) +
			 params.offset) >>
				PAGE_SHIFT,
			PAGE_SIZE, pgprot_noncached(vma->vm_page_prot),
			शून्य);
	पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_ib_alloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_pd *pd = to_mpd(ibpd);
	काष्ठा ib_device *ibdev = ibpd->device;
	पूर्णांक err;

	err = mlx4_pd_alloc(to_mdev(ibdev)->dev, &pd->pdn);
	अगर (err)
		वापस err;

	अगर (udata && ib_copy_to_udata(udata, &pd->pdn, माप(__u32))) अणु
		mlx4_pd_मुक्त(to_mdev(ibdev)->dev, pd->pdn);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_ib_dealloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata)
अणु
	mlx4_pd_मुक्त(to_mdev(pd->device)->dev, to_mpd(pd)->pdn);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_ib_alloc_xrcd(काष्ठा ib_xrcd *ibxrcd, काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibxrcd->device);
	काष्ठा mlx4_ib_xrcd *xrcd = to_mxrcd(ibxrcd);
	काष्ठा ib_cq_init_attr cq_attr = अणुपूर्ण;
	पूर्णांक err;

	अगर (!(dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_XRC))
		वापस -EOPNOTSUPP;

	err = mlx4_xrcd_alloc(dev->dev, &xrcd->xrcdn);
	अगर (err)
		वापस err;

	xrcd->pd = ib_alloc_pd(ibxrcd->device, 0);
	अगर (IS_ERR(xrcd->pd)) अणु
		err = PTR_ERR(xrcd->pd);
		जाओ err2;
	पूर्ण

	cq_attr.cqe = 1;
	xrcd->cq = ib_create_cq(ibxrcd->device, शून्य, शून्य, xrcd, &cq_attr);
	अगर (IS_ERR(xrcd->cq)) अणु
		err = PTR_ERR(xrcd->cq);
		जाओ err3;
	पूर्ण

	वापस 0;

err3:
	ib_dealloc_pd(xrcd->pd);
err2:
	mlx4_xrcd_मुक्त(dev->dev, xrcd->xrcdn);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_dealloc_xrcd(काष्ठा ib_xrcd *xrcd, काष्ठा ib_udata *udata)
अणु
	ib_destroy_cq(to_mxrcd(xrcd)->cq);
	ib_dealloc_pd(to_mxrcd(xrcd)->pd);
	mlx4_xrcd_मुक्त(to_mdev(xrcd->device)->dev, to_mxrcd(xrcd)->xrcdn);
	वापस 0;
पूर्ण

अटल पूर्णांक add_gid_entry(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid)
अणु
	काष्ठा mlx4_ib_qp *mqp = to_mqp(ibqp);
	काष्ठा mlx4_ib_dev *mdev = to_mdev(ibqp->device);
	काष्ठा mlx4_ib_gid_entry *ge;

	ge = kzalloc(माप *ge, GFP_KERNEL);
	अगर (!ge)
		वापस -ENOMEM;

	ge->gid = *gid;
	अगर (mlx4_ib_add_mc(mdev, mqp, gid)) अणु
		ge->port = mqp->port;
		ge->added = 1;
	पूर्ण

	mutex_lock(&mqp->mutex);
	list_add_tail(&ge->list, &mqp->gid_list);
	mutex_unlock(&mqp->mutex);

	वापस 0;
पूर्ण

अटल व्योम mlx4_ib_delete_counters_table(काष्ठा mlx4_ib_dev *ibdev,
					  काष्ठा mlx4_ib_counters *ctr_table)
अणु
	काष्ठा counter_index *counter, *पंचांगp_count;

	mutex_lock(&ctr_table->mutex);
	list_क्रम_each_entry_safe(counter, पंचांगp_count, &ctr_table->counters_list,
				 list) अणु
		अगर (counter->allocated)
			mlx4_counter_मुक्त(ibdev->dev, counter->index);
		list_del(&counter->list);
		kमुक्त(counter);
	पूर्ण
	mutex_unlock(&ctr_table->mutex);
पूर्ण

पूर्णांक mlx4_ib_add_mc(काष्ठा mlx4_ib_dev *mdev, काष्ठा mlx4_ib_qp *mqp,
		   जोड़ ib_gid *gid)
अणु
	काष्ठा net_device *ndev;
	पूर्णांक ret = 0;

	अगर (!mqp->port)
		वापस 0;

	spin_lock_bh(&mdev->iboe.lock);
	ndev = mdev->iboe.netdevs[mqp->port - 1];
	अगर (ndev)
		dev_hold(ndev);
	spin_unlock_bh(&mdev->iboe.lock);

	अगर (ndev) अणु
		ret = 1;
		dev_put(ndev);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा mlx4_ib_steering अणु
	काष्ठा list_head list;
	काष्ठा mlx4_flow_reg_id reg_id;
	जोड़ ib_gid gid;
पूर्ण;

#घोषणा LAST_ETH_FIELD vlan_tag
#घोषणा LAST_IB_FIELD sl
#घोषणा LAST_IPV4_FIELD dst_ip
#घोषणा LAST_TCP_UDP_FIELD src_port

/* Field is the last supported field */
#घोषणा FIELDS_NOT_SUPPORTED(filter, field)\
	स_प्रथम_inv((व्योम *)&filter.field  +\
		   माप(filter.field), 0,\
		   माप(filter) -\
		   दुरत्व(typeof(filter), field) -\
		   माप(filter.field))

अटल पूर्णांक parse_flow_attr(काष्ठा mlx4_dev *dev,
			   u32 qp_num,
			   जोड़ ib_flow_spec *ib_spec,
			   काष्ठा _rule_hw *mlx4_spec)
अणु
	क्रमागत mlx4_net_trans_rule_id type;

	चयन (ib_spec->type) अणु
	हाल IB_FLOW_SPEC_ETH:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->eth.mask, LAST_ETH_FIELD))
			वापस -ENOTSUPP;

		type = MLX4_NET_TRANS_RULE_ID_ETH;
		स_नकल(mlx4_spec->eth.dst_mac, ib_spec->eth.val.dst_mac,
		       ETH_ALEN);
		स_नकल(mlx4_spec->eth.dst_mac_msk, ib_spec->eth.mask.dst_mac,
		       ETH_ALEN);
		mlx4_spec->eth.vlan_tag = ib_spec->eth.val.vlan_tag;
		mlx4_spec->eth.vlan_tag_msk = ib_spec->eth.mask.vlan_tag;
		अवरोध;
	हाल IB_FLOW_SPEC_IB:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->ib.mask, LAST_IB_FIELD))
			वापस -ENOTSUPP;

		type = MLX4_NET_TRANS_RULE_ID_IB;
		mlx4_spec->ib.l3_qpn =
			cpu_to_be32(qp_num);
		mlx4_spec->ib.qpn_mask =
			cpu_to_be32(MLX4_IB_FLOW_QPN_MASK);
		अवरोध;


	हाल IB_FLOW_SPEC_IPV4:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->ipv4.mask, LAST_IPV4_FIELD))
			वापस -ENOTSUPP;

		type = MLX4_NET_TRANS_RULE_ID_IPV4;
		mlx4_spec->ipv4.src_ip = ib_spec->ipv4.val.src_ip;
		mlx4_spec->ipv4.src_ip_msk = ib_spec->ipv4.mask.src_ip;
		mlx4_spec->ipv4.dst_ip = ib_spec->ipv4.val.dst_ip;
		mlx4_spec->ipv4.dst_ip_msk = ib_spec->ipv4.mask.dst_ip;
		अवरोध;

	हाल IB_FLOW_SPEC_TCP:
	हाल IB_FLOW_SPEC_UDP:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->tcp_udp.mask, LAST_TCP_UDP_FIELD))
			वापस -ENOTSUPP;

		type = ib_spec->type == IB_FLOW_SPEC_TCP ?
					MLX4_NET_TRANS_RULE_ID_TCP :
					MLX4_NET_TRANS_RULE_ID_UDP;
		mlx4_spec->tcp_udp.dst_port = ib_spec->tcp_udp.val.dst_port;
		mlx4_spec->tcp_udp.dst_port_msk = ib_spec->tcp_udp.mask.dst_port;
		mlx4_spec->tcp_udp.src_port = ib_spec->tcp_udp.val.src_port;
		mlx4_spec->tcp_udp.src_port_msk = ib_spec->tcp_udp.mask.src_port;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (mlx4_map_sw_to_hw_steering_id(dev, type) < 0 ||
	    mlx4_hw_rule_sz(dev, type) < 0)
		वापस -EINVAL;
	mlx4_spec->id = cpu_to_be16(mlx4_map_sw_to_hw_steering_id(dev, type));
	mlx4_spec->size = mlx4_hw_rule_sz(dev, type) >> 2;
	वापस mlx4_hw_rule_sz(dev, type);
पूर्ण

काष्ठा शेष_rules अणु
	__u32 mandatory_fields[IB_FLOW_SPEC_SUPPORT_LAYERS];
	__u32 mandatory_not_fields[IB_FLOW_SPEC_SUPPORT_LAYERS];
	__u32 rules_create_list[IB_FLOW_SPEC_SUPPORT_LAYERS];
	__u8  link_layer;
पूर्ण;
अटल स्थिर काष्ठा शेष_rules शेष_table[] = अणु
	अणु
		.mandatory_fields = अणुIB_FLOW_SPEC_IPV4पूर्ण,
		.mandatory_not_fields = अणुIB_FLOW_SPEC_ETHपूर्ण,
		.rules_create_list = अणुIB_FLOW_SPEC_IBपूर्ण,
		.link_layer = IB_LINK_LAYER_INFINIBAND
	पूर्ण
पूर्ण;

अटल पूर्णांक __mlx4_ib_शेष_rules_match(काष्ठा ib_qp *qp,
					 काष्ठा ib_flow_attr *flow_attr)
अणु
	पूर्णांक i, j, k;
	व्योम *ib_flow;
	स्थिर काष्ठा शेष_rules *pशेष_rules = शेष_table;
	u8 link_layer = rdma_port_get_link_layer(qp->device, flow_attr->port);

	क्रम (i = 0; i < ARRAY_SIZE(शेष_table); i++, pशेष_rules++) अणु
		__u32 field_types[IB_FLOW_SPEC_SUPPORT_LAYERS];
		स_रखो(&field_types, 0, माप(field_types));

		अगर (link_layer != pशेष_rules->link_layer)
			जारी;

		ib_flow = flow_attr + 1;
		/* we assume the specs are sorted */
		क्रम (j = 0, k = 0; k < IB_FLOW_SPEC_SUPPORT_LAYERS &&
		     j < flow_attr->num_of_specs; k++) अणु
			जोड़ ib_flow_spec *current_flow =
				(जोड़ ib_flow_spec *)ib_flow;

			/* same layer but dअगरferent type */
			अगर (((current_flow->type & IB_FLOW_SPEC_LAYER_MASK) ==
			     (pशेष_rules->mandatory_fields[k] &
			      IB_FLOW_SPEC_LAYER_MASK)) &&
			    (current_flow->type !=
			     pशेष_rules->mandatory_fields[k]))
				जाओ out;

			/* same layer, try match next one */
			अगर (current_flow->type ==
			    pशेष_rules->mandatory_fields[k]) अणु
				j++;
				ib_flow +=
					((जोड़ ib_flow_spec *)ib_flow)->size;
			पूर्ण
		पूर्ण

		ib_flow = flow_attr + 1;
		क्रम (j = 0; j < flow_attr->num_of_specs;
		     j++, ib_flow += ((जोड़ ib_flow_spec *)ib_flow)->size)
			क्रम (k = 0; k < IB_FLOW_SPEC_SUPPORT_LAYERS; k++)
				/* same layer and same type */
				अगर (((जोड़ ib_flow_spec *)ib_flow)->type ==
				    pशेष_rules->mandatory_not_fields[k])
					जाओ out;

		वापस i;
	पूर्ण
out:
	वापस -1;
पूर्ण

अटल पूर्णांक __mlx4_ib_create_शेष_rules(
		काष्ठा mlx4_ib_dev *mdev,
		काष्ठा ib_qp *qp,
		स्थिर काष्ठा शेष_rules *pशेष_rules,
		काष्ठा _rule_hw *mlx4_spec) अणु
	पूर्णांक size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pशेष_rules->rules_create_list); i++) अणु
		जोड़ ib_flow_spec ib_spec = अणुपूर्ण;
		पूर्णांक ret;

		चयन (pशेष_rules->rules_create_list[i]) अणु
		हाल 0:
			/* no rule */
			जारी;
		हाल IB_FLOW_SPEC_IB:
			ib_spec.type = IB_FLOW_SPEC_IB;
			ib_spec.size = माप(काष्ठा ib_flow_spec_ib);

			अवरोध;
		शेष:
			/* invalid rule */
			वापस -EINVAL;
		पूर्ण
		/* We must put empty rule, qpn is being ignored */
		ret = parse_flow_attr(mdev->dev, 0, &ib_spec,
				      mlx4_spec);
		अगर (ret < 0) अणु
			pr_info("invalid parsing\n");
			वापस -EINVAL;
		पूर्ण

		mlx4_spec = (व्योम *)mlx4_spec + ret;
		size += ret;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक __mlx4_ib_create_flow(काष्ठा ib_qp *qp, काष्ठा ib_flow_attr *flow_attr,
			  पूर्णांक करोमुख्य,
			  क्रमागत mlx4_net_trans_promisc_mode flow_type,
			  u64 *reg_id)
अणु
	पूर्णांक ret, i;
	पूर्णांक size = 0;
	व्योम *ib_flow;
	काष्ठा mlx4_ib_dev *mdev = to_mdev(qp->device);
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_net_trans_rule_hw_ctrl *ctrl;
	पूर्णांक शेष_flow;

	अगर (flow_attr->priority > MLX4_IB_FLOW_MAX_PRIO) अणु
		pr_err("Invalid priority value %d\n", flow_attr->priority);
		वापस -EINVAL;
	पूर्ण

	अगर (mlx4_map_sw_to_hw_steering_mode(mdev->dev, flow_type) < 0)
		वापस -EINVAL;

	mailbox = mlx4_alloc_cmd_mailbox(mdev->dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	ctrl = mailbox->buf;

	ctrl->prio = cpu_to_be16(करोमुख्य | flow_attr->priority);
	ctrl->type = mlx4_map_sw_to_hw_steering_mode(mdev->dev, flow_type);
	ctrl->port = flow_attr->port;
	ctrl->qpn = cpu_to_be32(qp->qp_num);

	ib_flow = flow_attr + 1;
	size += माप(काष्ठा mlx4_net_trans_rule_hw_ctrl);
	/* Add शेष flows */
	शेष_flow = __mlx4_ib_शेष_rules_match(qp, flow_attr);
	अगर (शेष_flow >= 0) अणु
		ret = __mlx4_ib_create_शेष_rules(
				mdev, qp, शेष_table + शेष_flow,
				mailbox->buf + size);
		अगर (ret < 0) अणु
			mlx4_मुक्त_cmd_mailbox(mdev->dev, mailbox);
			वापस -EINVAL;
		पूर्ण
		size += ret;
	पूर्ण
	क्रम (i = 0; i < flow_attr->num_of_specs; i++) अणु
		ret = parse_flow_attr(mdev->dev, qp->qp_num, ib_flow,
				      mailbox->buf + size);
		अगर (ret < 0) अणु
			mlx4_मुक्त_cmd_mailbox(mdev->dev, mailbox);
			वापस -EINVAL;
		पूर्ण
		ib_flow += ((जोड़ ib_flow_spec *) ib_flow)->size;
		size += ret;
	पूर्ण

	अगर (mlx4_is_master(mdev->dev) && flow_type == MLX4_FS_REGULAR &&
	    flow_attr->num_of_specs == 1) अणु
		काष्ठा _rule_hw *rule_header = (काष्ठा _rule_hw *)(ctrl + 1);
		क्रमागत ib_flow_spec_type header_spec =
			((जोड़ ib_flow_spec *)(flow_attr + 1))->type;

		अगर (header_spec == IB_FLOW_SPEC_ETH)
			mlx4_handle_eth_header_mcast_prio(ctrl, rule_header);
	पूर्ण

	ret = mlx4_cmd_imm(mdev->dev, mailbox->dma, reg_id, size >> 2, 0,
			   MLX4_QP_FLOW_STEERING_ATTACH, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	अगर (ret == -ENOMEM)
		pr_err("mcg table is full. Fail to register network rule.\n");
	अन्यथा अगर (ret == -ENXIO)
		pr_err("Device managed flow steering is disabled. Fail to register network rule.\n");
	अन्यथा अगर (ret)
		pr_err("Invalid argument. Fail to register network rule.\n");

	mlx4_मुक्त_cmd_mailbox(mdev->dev, mailbox);
	वापस ret;
पूर्ण

अटल पूर्णांक __mlx4_ib_destroy_flow(काष्ठा mlx4_dev *dev, u64 reg_id)
अणु
	पूर्णांक err;
	err = mlx4_cmd(dev, reg_id, 0, 0,
		       MLX4_QP_FLOW_STEERING_DETACH, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_NATIVE);
	अगर (err)
		pr_err("Fail to detach network rule. registration id = 0x%llx\n",
		       reg_id);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_tunnel_steer_add(काष्ठा ib_qp *qp, काष्ठा ib_flow_attr *flow_attr,
				    u64 *reg_id)
अणु
	व्योम *ib_flow;
	जोड़ ib_flow_spec *ib_spec;
	काष्ठा mlx4_dev	*dev = to_mdev(qp->device)->dev;
	पूर्णांक err = 0;

	अगर (dev->caps.tunnel_offload_mode != MLX4_TUNNEL_OFFLOAD_MODE_VXLAN ||
	    dev->caps.dmfs_high_steer_mode == MLX4_STEERING_DMFS_A0_STATIC)
		वापस 0; /* करो nothing */

	ib_flow = flow_attr + 1;
	ib_spec = (जोड़ ib_flow_spec *)ib_flow;

	अगर (ib_spec->type !=  IB_FLOW_SPEC_ETH || flow_attr->num_of_specs != 1)
		वापस 0; /* करो nothing */

	err = mlx4_tunnel_steer_add(to_mdev(qp->device)->dev, ib_spec->eth.val.dst_mac,
				    flow_attr->port, qp->qp_num,
				    MLX4_DOMAIN_UVERBS | (flow_attr->priority & 0xff),
				    reg_id);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_ib_add_करोnt_trap_rule(काष्ठा mlx4_dev *dev,
				      काष्ठा ib_flow_attr *flow_attr,
				      क्रमागत mlx4_net_trans_promisc_mode *type)
अणु
	पूर्णांक err = 0;

	अगर (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_DMFS_UC_MC_SNIFFER) ||
	    (dev->caps.dmfs_high_steer_mode == MLX4_STEERING_DMFS_A0_STATIC) ||
	    (flow_attr->num_of_specs > 1) || (flow_attr->priority != 0)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_attr->num_of_specs == 0) अणु
		type[0] = MLX4_FS_MC_SNIFFER;
		type[1] = MLX4_FS_UC_SNIFFER;
	पूर्ण अन्यथा अणु
		जोड़ ib_flow_spec *ib_spec;

		ib_spec = (जोड़ ib_flow_spec *)(flow_attr + 1);
		अगर (ib_spec->type !=  IB_FLOW_SPEC_ETH)
			वापस -EINVAL;

		/* अगर all is zero than MC and UC */
		अगर (is_zero_ether_addr(ib_spec->eth.mask.dst_mac)) अणु
			type[0] = MLX4_FS_MC_SNIFFER;
			type[1] = MLX4_FS_UC_SNIFFER;
		पूर्ण अन्यथा अणु
			u8 mac[ETH_ALEN] = अणुib_spec->eth.mask.dst_mac[0] ^ 0x01,
					    ib_spec->eth.mask.dst_mac[1],
					    ib_spec->eth.mask.dst_mac[2],
					    ib_spec->eth.mask.dst_mac[3],
					    ib_spec->eth.mask.dst_mac[4],
					    ib_spec->eth.mask.dst_mac[5]पूर्ण;

			/* Above xor was only on MC bit, non empty mask is valid
			 * only अगर this bit is set and rest are zero.
			 */
			अगर (!is_zero_ether_addr(&mac[0]))
				वापस -EINVAL;

			अगर (is_multicast_ether_addr(ib_spec->eth.val.dst_mac))
				type[0] = MLX4_FS_MC_SNIFFER;
			अन्यथा
				type[0] = MLX4_FS_UC_SNIFFER;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल काष्ठा ib_flow *mlx4_ib_create_flow(काष्ठा ib_qp *qp,
					   काष्ठा ib_flow_attr *flow_attr,
					   काष्ठा ib_udata *udata)
अणु
	पूर्णांक err = 0, i = 0, j = 0;
	काष्ठा mlx4_ib_flow *mflow;
	क्रमागत mlx4_net_trans_promisc_mode type[2];
	काष्ठा mlx4_dev *dev = (to_mdev(qp->device))->dev;
	पूर्णांक is_bonded = mlx4_is_bonded(dev);

	अगर (flow_attr->flags & ~IB_FLOW_ATTR_FLAGS_DONT_TRAP)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर ((flow_attr->flags & IB_FLOW_ATTR_FLAGS_DONT_TRAP) &&
	    (flow_attr->type != IB_FLOW_ATTR_NORMAL))
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (udata &&
	    udata->inlen && !ib_is_udata_cleared(udata, 0, udata->inlen))
		वापस ERR_PTR(-EOPNOTSUPP);

	स_रखो(type, 0, माप(type));

	mflow = kzalloc(माप(*mflow), GFP_KERNEL);
	अगर (!mflow) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	चयन (flow_attr->type) अणु
	हाल IB_FLOW_ATTR_NORMAL:
		/* If करोnt trap flag (जारी match) is set, under specअगरic
		 * condition traffic be replicated to given qp,
		 * without stealing it
		 */
		अगर (unlikely(flow_attr->flags & IB_FLOW_ATTR_FLAGS_DONT_TRAP)) अणु
			err = mlx4_ib_add_करोnt_trap_rule(dev,
							 flow_attr,
							 type);
			अगर (err)
				जाओ err_मुक्त;
		पूर्ण अन्यथा अणु
			type[0] = MLX4_FS_REGULAR;
		पूर्ण
		अवरोध;

	हाल IB_FLOW_ATTR_ALL_DEFAULT:
		type[0] = MLX4_FS_ALL_DEFAULT;
		अवरोध;

	हाल IB_FLOW_ATTR_MC_DEFAULT:
		type[0] = MLX4_FS_MC_DEFAULT;
		अवरोध;

	हाल IB_FLOW_ATTR_SNIFFER:
		type[0] = MLX4_FS_MIRROR_RX_PORT;
		type[1] = MLX4_FS_MIRROR_SX_PORT;
		अवरोध;

	शेष:
		err = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	जबतक (i < ARRAY_SIZE(type) && type[i]) अणु
		err = __mlx4_ib_create_flow(qp, flow_attr, MLX4_DOMAIN_UVERBS,
					    type[i], &mflow->reg_id[i].id);
		अगर (err)
			जाओ err_create_flow;
		अगर (is_bonded) अणु
			/* Application always sees one port so the mirror rule
			 * must be on port #2
			 */
			flow_attr->port = 2;
			err = __mlx4_ib_create_flow(qp, flow_attr,
						    MLX4_DOMAIN_UVERBS, type[j],
						    &mflow->reg_id[j].mirror);
			flow_attr->port = 1;
			अगर (err)
				जाओ err_create_flow;
			j++;
		पूर्ण

		i++;
	पूर्ण

	अगर (i < ARRAY_SIZE(type) && flow_attr->type == IB_FLOW_ATTR_NORMAL) अणु
		err = mlx4_ib_tunnel_steer_add(qp, flow_attr,
					       &mflow->reg_id[i].id);
		अगर (err)
			जाओ err_create_flow;

		अगर (is_bonded) अणु
			flow_attr->port = 2;
			err = mlx4_ib_tunnel_steer_add(qp, flow_attr,
						       &mflow->reg_id[j].mirror);
			flow_attr->port = 1;
			अगर (err)
				जाओ err_create_flow;
			j++;
		पूर्ण
		/* function to create mirror rule */
		i++;
	पूर्ण

	वापस &mflow->ibflow;

err_create_flow:
	जबतक (i) अणु
		(व्योम)__mlx4_ib_destroy_flow(to_mdev(qp->device)->dev,
					     mflow->reg_id[i].id);
		i--;
	पूर्ण

	जबतक (j) अणु
		(व्योम)__mlx4_ib_destroy_flow(to_mdev(qp->device)->dev,
					     mflow->reg_id[j].mirror);
		j--;
	पूर्ण
err_मुक्त:
	kमुक्त(mflow);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक mlx4_ib_destroy_flow(काष्ठा ib_flow *flow_id)
अणु
	पूर्णांक err, ret = 0;
	पूर्णांक i = 0;
	काष्ठा mlx4_ib_dev *mdev = to_mdev(flow_id->qp->device);
	काष्ठा mlx4_ib_flow *mflow = to_mflow(flow_id);

	जबतक (i < ARRAY_SIZE(mflow->reg_id) && mflow->reg_id[i].id) अणु
		err = __mlx4_ib_destroy_flow(mdev->dev, mflow->reg_id[i].id);
		अगर (err)
			ret = err;
		अगर (mflow->reg_id[i].mirror) अणु
			err = __mlx4_ib_destroy_flow(mdev->dev,
						     mflow->reg_id[i].mirror);
			अगर (err)
				ret = err;
		पूर्ण
		i++;
	पूर्ण

	kमुक्त(mflow);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_ib_mcg_attach(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid)
अणु
	पूर्णांक err;
	काष्ठा mlx4_ib_dev *mdev = to_mdev(ibqp->device);
	काष्ठा mlx4_dev	*dev = mdev->dev;
	काष्ठा mlx4_ib_qp *mqp = to_mqp(ibqp);
	काष्ठा mlx4_ib_steering *ib_steering = शून्य;
	क्रमागत mlx4_protocol prot = MLX4_PROT_IB_IPV6;
	काष्ठा mlx4_flow_reg_id	reg_id;

	अगर (mdev->dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		ib_steering = kदो_स्मृति(माप(*ib_steering), GFP_KERNEL);
		अगर (!ib_steering)
			वापस -ENOMEM;
	पूर्ण

	err = mlx4_multicast_attach(mdev->dev, &mqp->mqp, gid->raw, mqp->port,
				    !!(mqp->flags &
				       MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK),
				    prot, &reg_id.id);
	अगर (err) अणु
		pr_err("multicast attach op failed, err %d\n", err);
		जाओ err_दो_स्मृति;
	पूर्ण

	reg_id.mirror = 0;
	अगर (mlx4_is_bonded(dev)) अणु
		err = mlx4_multicast_attach(mdev->dev, &mqp->mqp, gid->raw,
					    (mqp->port == 1) ? 2 : 1,
					    !!(mqp->flags &
					    MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK),
					    prot, &reg_id.mirror);
		अगर (err)
			जाओ err_add;
	पूर्ण

	err = add_gid_entry(ibqp, gid);
	अगर (err)
		जाओ err_add;

	अगर (ib_steering) अणु
		स_नकल(ib_steering->gid.raw, gid->raw, 16);
		ib_steering->reg_id = reg_id;
		mutex_lock(&mqp->mutex);
		list_add(&ib_steering->list, &mqp->steering_rules);
		mutex_unlock(&mqp->mutex);
	पूर्ण
	वापस 0;

err_add:
	mlx4_multicast_detach(mdev->dev, &mqp->mqp, gid->raw,
			      prot, reg_id.id);
	अगर (reg_id.mirror)
		mlx4_multicast_detach(mdev->dev, &mqp->mqp, gid->raw,
				      prot, reg_id.mirror);
err_दो_स्मृति:
	kमुक्त(ib_steering);

	वापस err;
पूर्ण

अटल काष्ठा mlx4_ib_gid_entry *find_gid_entry(काष्ठा mlx4_ib_qp *qp, u8 *raw)
अणु
	काष्ठा mlx4_ib_gid_entry *ge;
	काष्ठा mlx4_ib_gid_entry *पंचांगp;
	काष्ठा mlx4_ib_gid_entry *ret = शून्य;

	list_क्रम_each_entry_safe(ge, पंचांगp, &qp->gid_list, list) अणु
		अगर (!स_भेद(raw, ge->gid.raw, 16)) अणु
			ret = ge;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_ib_mcg_detach(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid)
अणु
	पूर्णांक err;
	काष्ठा mlx4_ib_dev *mdev = to_mdev(ibqp->device);
	काष्ठा mlx4_dev *dev = mdev->dev;
	काष्ठा mlx4_ib_qp *mqp = to_mqp(ibqp);
	काष्ठा net_device *ndev;
	काष्ठा mlx4_ib_gid_entry *ge;
	काष्ठा mlx4_flow_reg_id reg_id = अणु0, 0पूर्ण;
	क्रमागत mlx4_protocol prot =  MLX4_PROT_IB_IPV6;

	अगर (mdev->dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		काष्ठा mlx4_ib_steering *ib_steering;

		mutex_lock(&mqp->mutex);
		list_क्रम_each_entry(ib_steering, &mqp->steering_rules, list) अणु
			अगर (!स_भेद(ib_steering->gid.raw, gid->raw, 16)) अणु
				list_del(&ib_steering->list);
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&mqp->mutex);
		अगर (&ib_steering->list == &mqp->steering_rules) अणु
			pr_err("Couldn't find reg_id for mgid. Steering rule is left attached\n");
			वापस -EINVAL;
		पूर्ण
		reg_id = ib_steering->reg_id;
		kमुक्त(ib_steering);
	पूर्ण

	err = mlx4_multicast_detach(mdev->dev, &mqp->mqp, gid->raw,
				    prot, reg_id.id);
	अगर (err)
		वापस err;

	अगर (mlx4_is_bonded(dev)) अणु
		err = mlx4_multicast_detach(mdev->dev, &mqp->mqp, gid->raw,
					    prot, reg_id.mirror);
		अगर (err)
			वापस err;
	पूर्ण

	mutex_lock(&mqp->mutex);
	ge = find_gid_entry(mqp, gid->raw);
	अगर (ge) अणु
		spin_lock_bh(&mdev->iboe.lock);
		ndev = ge->added ? mdev->iboe.netdevs[ge->port - 1] : शून्य;
		अगर (ndev)
			dev_hold(ndev);
		spin_unlock_bh(&mdev->iboe.lock);
		अगर (ndev)
			dev_put(ndev);
		list_del(&ge->list);
		kमुक्त(ge);
	पूर्ण अन्यथा
		pr_warn("could not find mgid entry\n");

	mutex_unlock(&mqp->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक init_node_data(काष्ठा mlx4_ib_dev *dev)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad = शून्य;
	पूर्णांक mad_अगरc_flags = MLX4_MAD_IFC_IGNORE_KEYS;
	पूर्णांक err = -ENOMEM;

	in_mad  = kzalloc(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	init_query_mad(in_mad);
	in_mad->attr_id = IB_SMP_ATTR_NODE_DESC;
	अगर (mlx4_is_master(dev->dev))
		mad_अगरc_flags |= MLX4_MAD_IFC_NET_VIEW;

	err = mlx4_MAD_IFC(dev, mad_अगरc_flags, 1, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	स_नकल(dev->ib_dev.node_desc, out_mad->data, IB_DEVICE_NODE_DESC_MAX);

	in_mad->attr_id = IB_SMP_ATTR_NODE_INFO;

	err = mlx4_MAD_IFC(dev, mad_अगरc_flags, 1, शून्य, शून्य, in_mad, out_mad);
	अगर (err)
		जाओ out;

	dev->dev->rev_id = be32_to_cpup((__be32 *) (out_mad->data + 32));
	स_नकल(&dev->ib_dev.node_guid, out_mad->data + 12, 8);

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस err;
पूर्ण

अटल sमाप_प्रकार hca_type_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx4_ib_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mlx4_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "MT%d\n", dev->dev->persist->pdev->device);
पूर्ण
अटल DEVICE_ATTR_RO(hca_type);

अटल sमाप_प्रकार hw_rev_show(काष्ठा device *device,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx4_ib_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mlx4_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "%x\n", dev->dev->rev_id);
पूर्ण
अटल DEVICE_ATTR_RO(hw_rev);

अटल sमाप_प्रकार board_id_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mlx4_ib_dev *dev =
		rdma_device_to_drv_device(device, काष्ठा mlx4_ib_dev, ib_dev);

	वापस sysfs_emit(buf, "%.*s\n", MLX4_BOARD_ID_LEN, dev->dev->board_id);
पूर्ण
अटल DEVICE_ATTR_RO(board_id);

अटल काष्ठा attribute *mlx4_class_attributes[] = अणु
	&dev_attr_hw_rev.attr,
	&dev_attr_hca_type.attr,
	&dev_attr_board_id.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mlx4_attr_group = अणु
	.attrs = mlx4_class_attributes,
पूर्ण;

काष्ठा diag_counter अणु
	स्थिर अक्षर *name;
	u32 offset;
पूर्ण;

#घोषणा DIAG_COUNTER(_name, _offset)			\
	अणु .name = #_name, .offset = _offset पूर्ण

अटल स्थिर काष्ठा diag_counter diag_basic[] = अणु
	DIAG_COUNTER(rq_num_lle, 0x00),
	DIAG_COUNTER(sq_num_lle, 0x04),
	DIAG_COUNTER(rq_num_lqpoe, 0x08),
	DIAG_COUNTER(sq_num_lqpoe, 0x0C),
	DIAG_COUNTER(rq_num_lpe, 0x18),
	DIAG_COUNTER(sq_num_lpe, 0x1C),
	DIAG_COUNTER(rq_num_wrfe, 0x20),
	DIAG_COUNTER(sq_num_wrfe, 0x24),
	DIAG_COUNTER(sq_num_mwbe, 0x2C),
	DIAG_COUNTER(sq_num_bre, 0x34),
	DIAG_COUNTER(sq_num_rire, 0x44),
	DIAG_COUNTER(rq_num_rire, 0x48),
	DIAG_COUNTER(sq_num_rae, 0x4C),
	DIAG_COUNTER(rq_num_rae, 0x50),
	DIAG_COUNTER(sq_num_roe, 0x54),
	DIAG_COUNTER(sq_num_tree, 0x5C),
	DIAG_COUNTER(sq_num_rree, 0x64),
	DIAG_COUNTER(rq_num_rnr, 0x68),
	DIAG_COUNTER(sq_num_rnr, 0x6C),
	DIAG_COUNTER(rq_num_oos, 0x100),
	DIAG_COUNTER(sq_num_oos, 0x104),
पूर्ण;

अटल स्थिर काष्ठा diag_counter diag_ext[] = अणु
	DIAG_COUNTER(rq_num_dup, 0x130),
	DIAG_COUNTER(sq_num_to, 0x134),
पूर्ण;

अटल स्थिर काष्ठा diag_counter diag_device_only[] = अणु
	DIAG_COUNTER(num_cqovf, 0x1A0),
	DIAG_COUNTER(rq_num_udsdprd, 0x118),
पूर्ण;

अटल काष्ठा rdma_hw_stats *mlx4_ib_alloc_hw_stats(काष्ठा ib_device *ibdev,
						    u32 port_num)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx4_ib_diag_counters *diag = dev->diag_counters;

	अगर (!diag[!!port_num].name)
		वापस शून्य;

	वापस rdma_alloc_hw_stats_काष्ठा(diag[!!port_num].name,
					  diag[!!port_num].num_counters,
					  RDMA_HW_STATS_DEFAULT_LIFESPAN);
पूर्ण

अटल पूर्णांक mlx4_ib_get_hw_stats(काष्ठा ib_device *ibdev,
				काष्ठा rdma_hw_stats *stats,
				u32 port, पूर्णांक index)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	काष्ठा mlx4_ib_diag_counters *diag = dev->diag_counters;
	u32 hw_value[ARRAY_SIZE(diag_device_only) +
		ARRAY_SIZE(diag_ext) + ARRAY_SIZE(diag_basic)] = अणुपूर्ण;
	पूर्णांक ret;
	पूर्णांक i;

	ret = mlx4_query_diag_counters(dev->dev,
				       MLX4_OP_MOD_QUERY_TRANSPORT_CI_ERRORS,
				       diag[!!port].offset, hw_value,
				       diag[!!port].num_counters, port);

	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < diag[!!port].num_counters; i++)
		stats->value[i] = hw_value[i];

	वापस diag[!!port].num_counters;
पूर्ण

अटल पूर्णांक __mlx4_ib_alloc_diag_counters(काष्ठा mlx4_ib_dev *ibdev,
					 स्थिर अक्षर ***name,
					 u32 **offset,
					 u32 *num,
					 bool port)
अणु
	u32 num_counters;

	num_counters = ARRAY_SIZE(diag_basic);

	अगर (ibdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_DIAG_PER_PORT)
		num_counters += ARRAY_SIZE(diag_ext);

	अगर (!port)
		num_counters += ARRAY_SIZE(diag_device_only);

	*name = kसुस्मृति(num_counters, माप(**name), GFP_KERNEL);
	अगर (!*name)
		वापस -ENOMEM;

	*offset = kसुस्मृति(num_counters, माप(**offset), GFP_KERNEL);
	अगर (!*offset)
		जाओ err_name;

	*num = num_counters;

	वापस 0;

err_name:
	kमुक्त(*name);
	वापस -ENOMEM;
पूर्ण

अटल व्योम mlx4_ib_fill_diag_counters(काष्ठा mlx4_ib_dev *ibdev,
				       स्थिर अक्षर **name,
				       u32 *offset,
				       bool port)
अणु
	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(diag_basic); i++, j++) अणु
		name[i] = diag_basic[i].name;
		offset[i] = diag_basic[i].offset;
	पूर्ण

	अगर (ibdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_DIAG_PER_PORT) अणु
		क्रम (i = 0; i < ARRAY_SIZE(diag_ext); i++, j++) अणु
			name[j] = diag_ext[i].name;
			offset[j] = diag_ext[i].offset;
		पूर्ण
	पूर्ण

	अगर (!port) अणु
		क्रम (i = 0; i < ARRAY_SIZE(diag_device_only); i++, j++) अणु
			name[j] = diag_device_only[i].name;
			offset[j] = diag_device_only[i].offset;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ib_device_ops mlx4_ib_hw_stats_ops = अणु
	.alloc_hw_stats = mlx4_ib_alloc_hw_stats,
	.get_hw_stats = mlx4_ib_get_hw_stats,
पूर्ण;

अटल पूर्णांक mlx4_ib_alloc_diag_counters(काष्ठा mlx4_ib_dev *ibdev)
अणु
	काष्ठा mlx4_ib_diag_counters *diag = ibdev->diag_counters;
	पूर्णांक i;
	पूर्णांक ret;
	bool per_port = !!(ibdev->dev->caps.flags2 &
		MLX4_DEV_CAP_FLAG2_DIAG_PER_PORT);

	अगर (mlx4_is_slave(ibdev->dev))
		वापस 0;

	क्रम (i = 0; i < MLX4_DIAG_COUNTERS_TYPES; i++) अणु
		/* i == 1 means we are building port counters */
		अगर (i && !per_port)
			जारी;

		ret = __mlx4_ib_alloc_diag_counters(ibdev, &diag[i].name,
						    &diag[i].offset,
						    &diag[i].num_counters, i);
		अगर (ret)
			जाओ err_alloc;

		mlx4_ib_fill_diag_counters(ibdev, diag[i].name,
					   diag[i].offset, i);
	पूर्ण

	ib_set_device_ops(&ibdev->ib_dev, &mlx4_ib_hw_stats_ops);

	वापस 0;

err_alloc:
	अगर (i) अणु
		kमुक्त(diag[i - 1].name);
		kमुक्त(diag[i - 1].offset);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mlx4_ib_diag_cleanup(काष्ठा mlx4_ib_dev *ibdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX4_DIAG_COUNTERS_TYPES; i++) अणु
		kमुक्त(ibdev->diag_counters[i].offset);
		kमुक्त(ibdev->diag_counters[i].name);
	पूर्ण
पूर्ण

#घोषणा MLX4_IB_INVALID_MAC	((u64)-1)
अटल व्योम mlx4_ib_update_qps(काष्ठा mlx4_ib_dev *ibdev,
			       काष्ठा net_device *dev,
			       पूर्णांक port)
अणु
	u64 new_smac = 0;
	u64 release_mac = MLX4_IB_INVALID_MAC;
	काष्ठा mlx4_ib_qp *qp;

	new_smac = mlx4_mac_to_u64(dev->dev_addr);
	atomic64_set(&ibdev->iboe.mac[port - 1], new_smac);

	/* no need क्रम update QP1 and mac registration in non-SRIOV */
	अगर (!mlx4_is_mfunc(ibdev->dev))
		वापस;

	mutex_lock(&ibdev->qp1_proxy_lock[port - 1]);
	qp = ibdev->qp1_proxy[port - 1];
	अगर (qp) अणु
		पूर्णांक new_smac_index;
		u64 old_smac;
		काष्ठा mlx4_update_qp_params update_params;

		mutex_lock(&qp->mutex);
		old_smac = qp->pri.smac;
		अगर (new_smac == old_smac)
			जाओ unlock;

		new_smac_index = mlx4_रेजिस्टर_mac(ibdev->dev, port, new_smac);

		अगर (new_smac_index < 0)
			जाओ unlock;

		update_params.smac_index = new_smac_index;
		अगर (mlx4_update_qp(ibdev->dev, qp->mqp.qpn, MLX4_UPDATE_QP_SMAC,
				   &update_params)) अणु
			release_mac = new_smac;
			जाओ unlock;
		पूर्ण
		/* अगर old port was zero, no mac was yet रेजिस्टरed क्रम this QP */
		अगर (qp->pri.smac_port)
			release_mac = old_smac;
		qp->pri.smac = new_smac;
		qp->pri.smac_port = port;
		qp->pri.smac_index = new_smac_index;
	पूर्ण

unlock:
	अगर (release_mac != MLX4_IB_INVALID_MAC)
		mlx4_unरेजिस्टर_mac(ibdev->dev, port, release_mac);
	अगर (qp)
		mutex_unlock(&qp->mutex);
	mutex_unlock(&ibdev->qp1_proxy_lock[port - 1]);
पूर्ण

अटल व्योम mlx4_ib_scan_netdevs(काष्ठा mlx4_ib_dev *ibdev,
				 काष्ठा net_device *dev,
				 अचिन्हित दीर्घ event)

अणु
	काष्ठा mlx4_ib_iboe *iboe;
	पूर्णांक update_qps_port = -1;
	पूर्णांक port;

	ASSERT_RTNL();

	iboe = &ibdev->iboe;

	spin_lock_bh(&iboe->lock);
	mlx4_क्रमeach_ib_transport_port(port, ibdev->dev) अणु

		iboe->netdevs[port - 1] =
			mlx4_get_protocol_dev(ibdev->dev, MLX4_PROT_ETH, port);

		अगर (dev == iboe->netdevs[port - 1] &&
		    (event == NETDEV_CHANGEADDR || event == NETDEV_REGISTER ||
		     event == NETDEV_UP || event == NETDEV_CHANGE))
			update_qps_port = port;

		अगर (dev == iboe->netdevs[port - 1] &&
		    (event == NETDEV_UP || event == NETDEV_DOWN)) अणु
			क्रमागत ib_port_state port_state;
			काष्ठा ib_event ibev = अणु पूर्ण;

			अगर (ib_get_cached_port_state(&ibdev->ib_dev, port,
						     &port_state))
				जारी;

			अगर (event == NETDEV_UP &&
			    (port_state != IB_PORT_ACTIVE ||
			     iboe->last_port_state[port - 1] != IB_PORT_DOWN))
				जारी;
			अगर (event == NETDEV_DOWN &&
			    (port_state != IB_PORT_DOWN ||
			     iboe->last_port_state[port - 1] != IB_PORT_ACTIVE))
				जारी;
			iboe->last_port_state[port - 1] = port_state;

			ibev.device = &ibdev->ib_dev;
			ibev.element.port_num = port;
			ibev.event = event == NETDEV_UP ? IB_EVENT_PORT_ACTIVE :
							  IB_EVENT_PORT_ERR;
			ib_dispatch_event(&ibev);
		पूर्ण

	पूर्ण
	spin_unlock_bh(&iboe->lock);

	अगर (update_qps_port > 0)
		mlx4_ib_update_qps(ibdev, dev, update_qps_port);
पूर्ण

अटल पूर्णांक mlx4_ib_netdev_event(काष्ठा notअगरier_block *this,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा mlx4_ib_dev *ibdev;

	अगर (!net_eq(dev_net(dev), &init_net))
		वापस NOTIFY_DONE;

	ibdev = container_of(this, काष्ठा mlx4_ib_dev, iboe.nb);
	mlx4_ib_scan_netdevs(ibdev, dev, event);

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम init_pkeys(काष्ठा mlx4_ib_dev *ibdev)
अणु
	पूर्णांक port;
	पूर्णांक slave;
	पूर्णांक i;

	अगर (mlx4_is_master(ibdev->dev)) अणु
		क्रम (slave = 0; slave <= ibdev->dev->persist->num_vfs;
		     ++slave) अणु
			क्रम (port = 1; port <= ibdev->dev->caps.num_ports; ++port) अणु
				क्रम (i = 0;
				     i < ibdev->dev->phys_caps.pkey_phys_table_len[port];
				     ++i) अणु
					ibdev->pkeys.virt2phys_pkey[slave][port - 1][i] =
					/* master has the identity virt2phys pkey mapping */
						(slave == mlx4_master_func_num(ibdev->dev) || !i) ? i :
							ibdev->dev->phys_caps.pkey_phys_table_len[port] - 1;
					mlx4_sync_pkey_table(ibdev->dev, slave, port, i,
							     ibdev->pkeys.virt2phys_pkey[slave][port - 1][i]);
				पूर्ण
			पूर्ण
		पूर्ण
		/* initialize pkey cache */
		क्रम (port = 1; port <= ibdev->dev->caps.num_ports; ++port) अणु
			क्रम (i = 0;
			     i < ibdev->dev->phys_caps.pkey_phys_table_len[port];
			     ++i)
				ibdev->pkeys.phys_pkey_cache[port-1][i] =
					(i) ? 0 : 0xFFFF;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_alloc_eqs(काष्ठा mlx4_dev *dev, काष्ठा mlx4_ib_dev *ibdev)
अणु
	पूर्णांक i, j, eq = 0, total_eqs = 0;

	ibdev->eq_table = kसुस्मृति(dev->caps.num_comp_vectors,
				  माप(ibdev->eq_table[0]), GFP_KERNEL);
	अगर (!ibdev->eq_table)
		वापस;

	क्रम (i = 1; i <= dev->caps.num_ports; i++) अणु
		क्रम (j = 0; j < mlx4_get_eqs_per_port(dev, i);
		     j++, total_eqs++) अणु
			अगर (i > 1 &&  mlx4_is_eq_shared(dev, total_eqs))
				जारी;
			ibdev->eq_table[eq] = total_eqs;
			अगर (!mlx4_assign_eq(dev, i,
					    &ibdev->eq_table[eq]))
				eq++;
			अन्यथा
				ibdev->eq_table[eq] = -1;
		पूर्ण
	पूर्ण

	क्रम (i = eq; i < dev->caps.num_comp_vectors;
	     ibdev->eq_table[i++] = -1)
		;

	/* Advertise the new number of EQs to clients */
	ibdev->ib_dev.num_comp_vectors = eq;
पूर्ण

अटल व्योम mlx4_ib_मुक्त_eqs(काष्ठा mlx4_dev *dev, काष्ठा mlx4_ib_dev *ibdev)
अणु
	पूर्णांक i;
	पूर्णांक total_eqs = ibdev->ib_dev.num_comp_vectors;

	/* no eqs were allocated */
	अगर (!ibdev->eq_table)
		वापस;

	/* Reset the advertised EQ number */
	ibdev->ib_dev.num_comp_vectors = 0;

	क्रम (i = 0; i < total_eqs; i++)
		mlx4_release_eq(dev, ibdev->eq_table[i]);

	kमुक्त(ibdev->eq_table);
	ibdev->eq_table = शून्य;
पूर्ण

अटल पूर्णांक mlx4_port_immutable(काष्ठा ib_device *ibdev, u32 port_num,
			       काष्ठा ib_port_immutable *immutable)
अणु
	काष्ठा ib_port_attr attr;
	काष्ठा mlx4_ib_dev *mdev = to_mdev(ibdev);
	पूर्णांक err;

	अगर (mlx4_ib_port_link_layer(ibdev, port_num) == IB_LINK_LAYER_INFINIBAND) अणु
		immutable->core_cap_flags = RDMA_CORE_PORT_IBA_IB;
		immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	पूर्ण अन्यथा अणु
		अगर (mdev->dev->caps.flags & MLX4_DEV_CAP_FLAG_IBOE)
			immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE;
		अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ROCE_V1_V2)
			immutable->core_cap_flags = RDMA_CORE_PORT_IBA_ROCE |
				RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP;
		immutable->core_cap_flags |= RDMA_CORE_PORT_RAW_PACKET;
		अगर (immutable->core_cap_flags & (RDMA_CORE_PORT_IBA_ROCE |
		    RDMA_CORE_PORT_IBA_ROCE_UDP_ENCAP))
			immutable->max_mad_size = IB_MGMT_MAD_SIZE;
	पूर्ण

	err = ib_query_port(ibdev, port_num, &attr);
	अगर (err)
		वापस err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;

	वापस 0;
पूर्ण

अटल व्योम get_fw_ver_str(काष्ठा ib_device *device, अक्षर *str)
अणु
	काष्ठा mlx4_ib_dev *dev =
		container_of(device, काष्ठा mlx4_ib_dev, ib_dev);
	snम_लिखो(str, IB_FW_VERSION_NAME_MAX, "%d.%d.%d",
		 (पूर्णांक) (dev->dev->caps.fw_ver >> 32),
		 (पूर्णांक) (dev->dev->caps.fw_ver >> 16) & 0xffff,
		 (पूर्णांक) dev->dev->caps.fw_ver & 0xffff);
पूर्ण

अटल स्थिर काष्ठा ib_device_ops mlx4_ib_dev_ops = अणु
	.owner = THIS_MODULE,
	.driver_id = RDMA_DRIVER_MLX4,
	.uverbs_abi_ver = MLX4_IB_UVERBS_ABI_VERSION,

	.add_gid = mlx4_ib_add_gid,
	.alloc_mr = mlx4_ib_alloc_mr,
	.alloc_pd = mlx4_ib_alloc_pd,
	.alloc_ucontext = mlx4_ib_alloc_ucontext,
	.attach_mcast = mlx4_ib_mcg_attach,
	.create_ah = mlx4_ib_create_ah,
	.create_cq = mlx4_ib_create_cq,
	.create_qp = mlx4_ib_create_qp,
	.create_srq = mlx4_ib_create_srq,
	.dealloc_pd = mlx4_ib_dealloc_pd,
	.dealloc_ucontext = mlx4_ib_dealloc_ucontext,
	.del_gid = mlx4_ib_del_gid,
	.dereg_mr = mlx4_ib_dereg_mr,
	.destroy_ah = mlx4_ib_destroy_ah,
	.destroy_cq = mlx4_ib_destroy_cq,
	.destroy_qp = mlx4_ib_destroy_qp,
	.destroy_srq = mlx4_ib_destroy_srq,
	.detach_mcast = mlx4_ib_mcg_detach,
	.disassociate_ucontext = mlx4_ib_disassociate_ucontext,
	.drain_rq = mlx4_ib_drain_rq,
	.drain_sq = mlx4_ib_drain_sq,
	.get_dev_fw_str = get_fw_ver_str,
	.get_dma_mr = mlx4_ib_get_dma_mr,
	.get_link_layer = mlx4_ib_port_link_layer,
	.get_netdev = mlx4_ib_get_netdev,
	.get_port_immutable = mlx4_port_immutable,
	.map_mr_sg = mlx4_ib_map_mr_sg,
	.mmap = mlx4_ib_mmap,
	.modअगरy_cq = mlx4_ib_modअगरy_cq,
	.modअगरy_device = mlx4_ib_modअगरy_device,
	.modअगरy_port = mlx4_ib_modअगरy_port,
	.modअगरy_qp = mlx4_ib_modअगरy_qp,
	.modअगरy_srq = mlx4_ib_modअगरy_srq,
	.poll_cq = mlx4_ib_poll_cq,
	.post_recv = mlx4_ib_post_recv,
	.post_send = mlx4_ib_post_send,
	.post_srq_recv = mlx4_ib_post_srq_recv,
	.process_mad = mlx4_ib_process_mad,
	.query_ah = mlx4_ib_query_ah,
	.query_device = mlx4_ib_query_device,
	.query_gid = mlx4_ib_query_gid,
	.query_pkey = mlx4_ib_query_pkey,
	.query_port = mlx4_ib_query_port,
	.query_qp = mlx4_ib_query_qp,
	.query_srq = mlx4_ib_query_srq,
	.reg_user_mr = mlx4_ib_reg_user_mr,
	.req_notअगरy_cq = mlx4_ib_arm_cq,
	.rereg_user_mr = mlx4_ib_rereg_user_mr,
	.resize_cq = mlx4_ib_resize_cq,

	INIT_RDMA_OBJ_SIZE(ib_ah, mlx4_ib_ah, ibah),
	INIT_RDMA_OBJ_SIZE(ib_cq, mlx4_ib_cq, ibcq),
	INIT_RDMA_OBJ_SIZE(ib_pd, mlx4_ib_pd, ibpd),
	INIT_RDMA_OBJ_SIZE(ib_srq, mlx4_ib_srq, ibsrq),
	INIT_RDMA_OBJ_SIZE(ib_ucontext, mlx4_ib_ucontext, ibucontext),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mlx4_ib_dev_wq_ops = अणु
	.create_rwq_ind_table = mlx4_ib_create_rwq_ind_table,
	.create_wq = mlx4_ib_create_wq,
	.destroy_rwq_ind_table = mlx4_ib_destroy_rwq_ind_table,
	.destroy_wq = mlx4_ib_destroy_wq,
	.modअगरy_wq = mlx4_ib_modअगरy_wq,

	INIT_RDMA_OBJ_SIZE(ib_rwq_ind_table, mlx4_ib_rwq_ind_table,
			   ib_rwq_ind_tbl),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mlx4_ib_dev_mw_ops = अणु
	.alloc_mw = mlx4_ib_alloc_mw,
	.dealloc_mw = mlx4_ib_dealloc_mw,

	INIT_RDMA_OBJ_SIZE(ib_mw, mlx4_ib_mw, ibmw),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mlx4_ib_dev_xrc_ops = अणु
	.alloc_xrcd = mlx4_ib_alloc_xrcd,
	.dealloc_xrcd = mlx4_ib_dealloc_xrcd,

	INIT_RDMA_OBJ_SIZE(ib_xrcd, mlx4_ib_xrcd, ibxrcd),
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops mlx4_ib_dev_fs_ops = अणु
	.create_flow = mlx4_ib_create_flow,
	.destroy_flow = mlx4_ib_destroy_flow,
पूर्ण;

अटल व्योम *mlx4_ib_add(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_ib_dev *ibdev;
	पूर्णांक num_ports = 0;
	पूर्णांक i, j;
	पूर्णांक err;
	काष्ठा mlx4_ib_iboe *iboe;
	पूर्णांक ib_num_ports = 0;
	पूर्णांक num_req_counters;
	पूर्णांक allocated;
	u32 counter_index;
	काष्ठा counter_index *new_counter_index = शून्य;

	pr_info_once("%s", mlx4_ib_version);

	num_ports = 0;
	mlx4_क्रमeach_ib_transport_port(i, dev)
		num_ports++;

	/* No poपूर्णांक in रेजिस्टरing a device with no ports... */
	अगर (num_ports == 0)
		वापस शून्य;

	ibdev = ib_alloc_device(mlx4_ib_dev, ib_dev);
	अगर (!ibdev) अणु
		dev_err(&dev->persist->pdev->dev,
			"Device struct alloc failed\n");
		वापस शून्य;
	पूर्ण

	iboe = &ibdev->iboe;

	अगर (mlx4_pd_alloc(dev, &ibdev->priv_pdn))
		जाओ err_dealloc;

	अगर (mlx4_uar_alloc(dev, &ibdev->priv_uar))
		जाओ err_pd;

	ibdev->uar_map = ioremap((phys_addr_t) ibdev->priv_uar.pfn << PAGE_SHIFT,
				 PAGE_SIZE);
	अगर (!ibdev->uar_map)
		जाओ err_uar;
	MLX4_INIT_DOORBELL_LOCK(&ibdev->uar_lock);

	ibdev->dev = dev;
	ibdev->bond_next_port	= 0;

	ibdev->ib_dev.node_type		= RDMA_NODE_IB_CA;
	ibdev->ib_dev.local_dma_lkey	= dev->caps.reserved_lkey;
	ibdev->num_ports		= num_ports;
	ibdev->ib_dev.phys_port_cnt     = mlx4_is_bonded(dev) ?
						1 : ibdev->num_ports;
	ibdev->ib_dev.num_comp_vectors	= dev->caps.num_comp_vectors;
	ibdev->ib_dev.dev.parent	= &dev->persist->pdev->dev;

	ib_set_device_ops(&ibdev->ib_dev, &mlx4_ib_dev_ops);

	अगर ((dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS) &&
	    ((mlx4_ib_port_link_layer(&ibdev->ib_dev, 1) ==
	    IB_LINK_LAYER_ETHERNET) ||
	    (mlx4_ib_port_link_layer(&ibdev->ib_dev, 2) ==
	    IB_LINK_LAYER_ETHERNET)))
		ib_set_device_ops(&ibdev->ib_dev, &mlx4_ib_dev_wq_ops);

	अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_MEM_WINDOW ||
	    dev->caps.bmme_flags & MLX4_BMME_FLAG_TYPE_2_WIN)
		ib_set_device_ops(&ibdev->ib_dev, &mlx4_ib_dev_mw_ops);

	अगर (dev->caps.flags & MLX4_DEV_CAP_FLAG_XRC) अणु
		ib_set_device_ops(&ibdev->ib_dev, &mlx4_ib_dev_xrc_ops);
	पूर्ण

	अगर (check_flow_steering_support(dev)) अणु
		ibdev->steering_support = MLX4_STEERING_MODE_DEVICE_MANAGED;
		ib_set_device_ops(&ibdev->ib_dev, &mlx4_ib_dev_fs_ops);
	पूर्ण

	अगर (!dev->caps.userspace_caps)
		ibdev->ib_dev.ops.uverbs_abi_ver =
			MLX4_IB_UVERBS_NO_DEV_CAPS_ABI_VERSION;

	mlx4_ib_alloc_eqs(dev, ibdev);

	spin_lock_init(&iboe->lock);

	अगर (init_node_data(ibdev))
		जाओ err_map;
	mlx4_init_sl2vl_tbl(ibdev);

	क्रम (i = 0; i < ibdev->num_ports; ++i) अणु
		mutex_init(&ibdev->counters_table[i].mutex);
		INIT_LIST_HEAD(&ibdev->counters_table[i].counters_list);
		iboe->last_port_state[i] = IB_PORT_DOWN;
	पूर्ण

	num_req_counters = mlx4_is_bonded(dev) ? 1 : ibdev->num_ports;
	क्रम (i = 0; i < num_req_counters; ++i) अणु
		mutex_init(&ibdev->qp1_proxy_lock[i]);
		allocated = 0;
		अगर (mlx4_ib_port_link_layer(&ibdev->ib_dev, i + 1) ==
						IB_LINK_LAYER_ETHERNET) अणु
			err = mlx4_counter_alloc(ibdev->dev, &counter_index,
						 MLX4_RES_USAGE_DRIVER);
			/* अगर failed to allocate a new counter, use शेष */
			अगर (err)
				counter_index =
					mlx4_get_शेष_counter_index(dev,
								       i + 1);
			अन्यथा
				allocated = 1;
		पूर्ण अन्यथा अणु /* IB_LINK_LAYER_INFINIBAND use the शेष counter */
			counter_index = mlx4_get_शेष_counter_index(dev,
								       i + 1);
		पूर्ण
		new_counter_index = kदो_स्मृति(माप(*new_counter_index),
					    GFP_KERNEL);
		अगर (!new_counter_index) अणु
			अगर (allocated)
				mlx4_counter_मुक्त(ibdev->dev, counter_index);
			जाओ err_counter;
		पूर्ण
		new_counter_index->index = counter_index;
		new_counter_index->allocated = allocated;
		list_add_tail(&new_counter_index->list,
			      &ibdev->counters_table[i].counters_list);
		ibdev->counters_table[i].शेष_counter = counter_index;
		pr_info("counter index %d for port %d allocated %d\n",
			counter_index, i + 1, allocated);
	पूर्ण
	अगर (mlx4_is_bonded(dev))
		क्रम (i = 1; i < ibdev->num_ports ; ++i) अणु
			new_counter_index =
					kदो_स्मृति(माप(काष्ठा counter_index),
						GFP_KERNEL);
			अगर (!new_counter_index)
				जाओ err_counter;
			new_counter_index->index = counter_index;
			new_counter_index->allocated = 0;
			list_add_tail(&new_counter_index->list,
				      &ibdev->counters_table[i].counters_list);
			ibdev->counters_table[i].शेष_counter =
								counter_index;
		पूर्ण

	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_IB)
		ib_num_ports++;

	spin_lock_init(&ibdev->sm_lock);
	mutex_init(&ibdev->cap_mask_mutex);
	INIT_LIST_HEAD(&ibdev->qp_list);
	spin_lock_init(&ibdev->reset_flow_resource_lock);

	अगर (ibdev->steering_support == MLX4_STEERING_MODE_DEVICE_MANAGED &&
	    ib_num_ports) अणु
		ibdev->steer_qpn_count = MLX4_IB_UC_MAX_NUM_QPS;
		err = mlx4_qp_reserve_range(dev, ibdev->steer_qpn_count,
					    MLX4_IB_UC_STEER_QPN_ALIGN,
					    &ibdev->steer_qpn_base, 0,
					    MLX4_RES_USAGE_DRIVER);
		अगर (err)
			जाओ err_counter;

		ibdev->ib_uc_qpns_biपंचांगap =
			kदो_स्मृति_array(BITS_TO_LONGS(ibdev->steer_qpn_count),
				      माप(दीर्घ),
				      GFP_KERNEL);
		अगर (!ibdev->ib_uc_qpns_biपंचांगap)
			जाओ err_steer_qp_release;

		अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_DMFS_IPOIB) अणु
			biपंचांगap_zero(ibdev->ib_uc_qpns_biपंचांगap,
				    ibdev->steer_qpn_count);
			err = mlx4_FLOW_STEERING_IB_UC_QP_RANGE(
					dev, ibdev->steer_qpn_base,
					ibdev->steer_qpn_base +
					ibdev->steer_qpn_count - 1);
			अगर (err)
				जाओ err_steer_मुक्त_biपंचांगap;
		पूर्ण अन्यथा अणु
			biपंचांगap_fill(ibdev->ib_uc_qpns_biपंचांगap,
				    ibdev->steer_qpn_count);
		पूर्ण
	पूर्ण

	क्रम (j = 1; j <= ibdev->dev->caps.num_ports; j++)
		atomic64_set(&iboe->mac[j - 1], ibdev->dev->caps.def_mac[j]);

	अगर (mlx4_ib_alloc_diag_counters(ibdev))
		जाओ err_steer_मुक्त_biपंचांगap;

	rdma_set_device_sysfs_group(&ibdev->ib_dev, &mlx4_attr_group);
	अगर (ib_रेजिस्टर_device(&ibdev->ib_dev, "mlx4_%d",
			       &dev->persist->pdev->dev))
		जाओ err_diag_counters;

	अगर (mlx4_ib_mad_init(ibdev))
		जाओ err_reg;

	अगर (mlx4_ib_init_sriov(ibdev))
		जाओ err_mad;

	अगर (!iboe->nb.notअगरier_call) अणु
		iboe->nb.notअगरier_call = mlx4_ib_netdev_event;
		err = रेजिस्टर_netdevice_notअगरier(&iboe->nb);
		अगर (err) अणु
			iboe->nb.notअगरier_call = शून्य;
			जाओ err_notअगर;
		पूर्ण
	पूर्ण
	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ROCE_V1_V2) अणु
		err = mlx4_config_roce_v2_port(dev, ROCE_V2_UDP_DPORT);
		अगर (err)
			जाओ err_notअगर;
	पूर्ण

	ibdev->ib_active = true;
	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_IB)
		devlink_port_type_ib_set(mlx4_get_devlink_port(dev, i),
					 &ibdev->ib_dev);

	अगर (mlx4_is_mfunc(ibdev->dev))
		init_pkeys(ibdev);

	/* create paravirt contexts क्रम any VFs which are active */
	अगर (mlx4_is_master(ibdev->dev)) अणु
		क्रम (j = 0; j < MLX4_MFUNC_MAX; j++) अणु
			अगर (j == mlx4_master_func_num(ibdev->dev))
				जारी;
			अगर (mlx4_is_slave_active(ibdev->dev, j))
				करो_slave_init(ibdev, j, 1);
		पूर्ण
	पूर्ण
	वापस ibdev;

err_notअगर:
	अगर (ibdev->iboe.nb.notअगरier_call) अणु
		अगर (unरेजिस्टर_netdevice_notअगरier(&ibdev->iboe.nb))
			pr_warn("failure unregistering notifier\n");
		ibdev->iboe.nb.notअगरier_call = शून्य;
	पूर्ण
	flush_workqueue(wq);

	mlx4_ib_बंद_sriov(ibdev);

err_mad:
	mlx4_ib_mad_cleanup(ibdev);

err_reg:
	ib_unरेजिस्टर_device(&ibdev->ib_dev);

err_diag_counters:
	mlx4_ib_diag_cleanup(ibdev);

err_steer_मुक्त_biपंचांगap:
	kमुक्त(ibdev->ib_uc_qpns_biपंचांगap);

err_steer_qp_release:
	mlx4_qp_release_range(dev, ibdev->steer_qpn_base,
			      ibdev->steer_qpn_count);
err_counter:
	क्रम (i = 0; i < ibdev->num_ports; ++i)
		mlx4_ib_delete_counters_table(ibdev, &ibdev->counters_table[i]);

err_map:
	mlx4_ib_मुक्त_eqs(dev, ibdev);
	iounmap(ibdev->uar_map);

err_uar:
	mlx4_uar_मुक्त(dev, &ibdev->priv_uar);

err_pd:
	mlx4_pd_मुक्त(dev, ibdev->priv_pdn);

err_dealloc:
	ib_dealloc_device(&ibdev->ib_dev);

	वापस शून्य;
पूर्ण

पूर्णांक mlx4_ib_steer_qp_alloc(काष्ठा mlx4_ib_dev *dev, पूर्णांक count, पूर्णांक *qpn)
अणु
	पूर्णांक offset;

	WARN_ON(!dev->ib_uc_qpns_biपंचांगap);

	offset = biपंचांगap_find_मुक्त_region(dev->ib_uc_qpns_biपंचांगap,
					 dev->steer_qpn_count,
					 get_count_order(count));
	अगर (offset < 0)
		वापस offset;

	*qpn = dev->steer_qpn_base + offset;
	वापस 0;
पूर्ण

व्योम mlx4_ib_steer_qp_मुक्त(काष्ठा mlx4_ib_dev *dev, u32 qpn, पूर्णांक count)
अणु
	अगर (!qpn ||
	    dev->steering_support != MLX4_STEERING_MODE_DEVICE_MANAGED)
		वापस;

	अगर (WARN(qpn < dev->steer_qpn_base, "qpn = %u, steer_qpn_base = %u\n",
		 qpn, dev->steer_qpn_base))
		/* not supposed to be here */
		वापस;

	biपंचांगap_release_region(dev->ib_uc_qpns_biपंचांगap,
			      qpn - dev->steer_qpn_base,
			      get_count_order(count));
पूर्ण

पूर्णांक mlx4_ib_steer_qp_reg(काष्ठा mlx4_ib_dev *mdev, काष्ठा mlx4_ib_qp *mqp,
			 पूर्णांक is_attach)
अणु
	पूर्णांक err;
	माप_प्रकार flow_size;
	काष्ठा ib_flow_attr *flow = शून्य;
	काष्ठा ib_flow_spec_ib *ib_spec;

	अगर (is_attach) अणु
		flow_size = माप(काष्ठा ib_flow_attr) +
			    माप(काष्ठा ib_flow_spec_ib);
		flow = kzalloc(flow_size, GFP_KERNEL);
		अगर (!flow)
			वापस -ENOMEM;
		flow->port = mqp->port;
		flow->num_of_specs = 1;
		flow->size = flow_size;
		ib_spec = (काष्ठा ib_flow_spec_ib *)(flow + 1);
		ib_spec->type = IB_FLOW_SPEC_IB;
		ib_spec->size = माप(काष्ठा ib_flow_spec_ib);
		/* Add an empty rule क्रम IB L2 */
		स_रखो(&ib_spec->mask, 0, माप(ib_spec->mask));

		err = __mlx4_ib_create_flow(&mqp->ibqp, flow, MLX4_DOMAIN_NIC,
					    MLX4_FS_REGULAR, &mqp->reg_id);
	पूर्ण अन्यथा अणु
		err = __mlx4_ib_destroy_flow(mdev->dev, mqp->reg_id);
	पूर्ण
	kमुक्त(flow);
	वापस err;
पूर्ण

अटल व्योम mlx4_ib_हटाओ(काष्ठा mlx4_dev *dev, व्योम *ibdev_ptr)
अणु
	काष्ठा mlx4_ib_dev *ibdev = ibdev_ptr;
	पूर्णांक p;
	पूर्णांक i;

	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_IB)
		devlink_port_type_clear(mlx4_get_devlink_port(dev, i));
	ibdev->ib_active = false;
	flush_workqueue(wq);

	अगर (ibdev->iboe.nb.notअगरier_call) अणु
		अगर (unरेजिस्टर_netdevice_notअगरier(&ibdev->iboe.nb))
			pr_warn("failure unregistering notifier\n");
		ibdev->iboe.nb.notअगरier_call = शून्य;
	पूर्ण

	mlx4_ib_बंद_sriov(ibdev);
	mlx4_ib_mad_cleanup(ibdev);
	ib_unरेजिस्टर_device(&ibdev->ib_dev);
	mlx4_ib_diag_cleanup(ibdev);

	mlx4_qp_release_range(dev, ibdev->steer_qpn_base,
			      ibdev->steer_qpn_count);
	kमुक्त(ibdev->ib_uc_qpns_biपंचांगap);

	iounmap(ibdev->uar_map);
	क्रम (p = 0; p < ibdev->num_ports; ++p)
		mlx4_ib_delete_counters_table(ibdev, &ibdev->counters_table[p]);

	mlx4_क्रमeach_port(p, dev, MLX4_PORT_TYPE_IB)
		mlx4_CLOSE_PORT(dev, p);

	mlx4_ib_मुक्त_eqs(dev, ibdev);

	mlx4_uar_मुक्त(dev, &ibdev->priv_uar);
	mlx4_pd_मुक्त(dev, ibdev->priv_pdn);
	ib_dealloc_device(&ibdev->ib_dev);
पूर्ण

अटल व्योम करो_slave_init(काष्ठा mlx4_ib_dev *ibdev, पूर्णांक slave, पूर्णांक करो_init)
अणु
	काष्ठा mlx4_ib_demux_work **dm = शून्य;
	काष्ठा mlx4_dev *dev = ibdev->dev;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा mlx4_active_ports actv_ports;
	अचिन्हित पूर्णांक ports;
	अचिन्हित पूर्णांक first_port;

	अगर (!mlx4_is_master(dev))
		वापस;

	actv_ports = mlx4_get_active_ports(dev, slave);
	ports = biपंचांगap_weight(actv_ports.ports, dev->caps.num_ports);
	first_port = find_first_bit(actv_ports.ports, dev->caps.num_ports);

	dm = kसुस्मृति(ports, माप(*dm), GFP_ATOMIC);
	अगर (!dm)
		वापस;

	क्रम (i = 0; i < ports; i++) अणु
		dm[i] = kदो_स्मृति(माप (काष्ठा mlx4_ib_demux_work), GFP_ATOMIC);
		अगर (!dm[i]) अणु
			जबतक (--i >= 0)
				kमुक्त(dm[i]);
			जाओ out;
		पूर्ण
		INIT_WORK(&dm[i]->work, mlx4_ib_tunnels_update_work);
		dm[i]->port = first_port + i + 1;
		dm[i]->slave = slave;
		dm[i]->करो_init = करो_init;
		dm[i]->dev = ibdev;
	पूर्ण
	/* initialize or tear करोwn tunnel QPs क्रम the slave */
	spin_lock_irqsave(&ibdev->sriov.going_करोwn_lock, flags);
	अगर (!ibdev->sriov.is_going_करोwn) अणु
		क्रम (i = 0; i < ports; i++)
			queue_work(ibdev->sriov.demux[i].ud_wq, &dm[i]->work);
		spin_unlock_irqrestore(&ibdev->sriov.going_करोwn_lock, flags);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&ibdev->sriov.going_करोwn_lock, flags);
		क्रम (i = 0; i < ports; i++)
			kमुक्त(dm[i]);
	पूर्ण
out:
	kमुक्त(dm);
	वापस;
पूर्ण

अटल व्योम mlx4_ib_handle_catas_error(काष्ठा mlx4_ib_dev *ibdev)
अणु
	काष्ठा mlx4_ib_qp *mqp;
	अचिन्हित दीर्घ flags_qp;
	अचिन्हित दीर्घ flags_cq;
	काष्ठा mlx4_ib_cq *send_mcq, *recv_mcq;
	काष्ठा list_head    cq_notअगरy_list;
	काष्ठा mlx4_cq *mcq;
	अचिन्हित दीर्घ flags;

	pr_warn("mlx4_ib_handle_catas_error was started\n");
	INIT_LIST_HEAD(&cq_notअगरy_list);

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
						      &cq_notअगरy_list);
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(&send_mcq->lock, flags_cq);
		पूर्ण
		spin_unlock_irqrestore(&mqp->sq.lock, flags_qp);
		/* Now, handle the QP's receive queue */
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
							      &cq_notअगरy_list);
					पूर्ण
				पूर्ण
				spin_unlock_irqrestore(&recv_mcq->lock,
						       flags_cq);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&mqp->rq.lock, flags_qp);
	पूर्ण

	list_क्रम_each_entry(mcq, &cq_notअगरy_list, reset_notअगरy) अणु
		mcq->comp(mcq);
	पूर्ण
	spin_unlock_irqrestore(&ibdev->reset_flow_resource_lock, flags);
	pr_warn("mlx4_ib_handle_catas_error ended\n");
पूर्ण

अटल व्योम handle_bonded_port_state_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_event_work *ew =
		container_of(work, काष्ठा ib_event_work, work);
	काष्ठा mlx4_ib_dev *ibdev = ew->ib_dev;
	क्रमागत ib_port_state bonded_port_state = IB_PORT_NOP;
	पूर्णांक i;
	काष्ठा ib_event ibev;

	kमुक्त(ew);
	spin_lock_bh(&ibdev->iboe.lock);
	क्रम (i = 0; i < MLX4_MAX_PORTS; ++i) अणु
		काष्ठा net_device *curr_netdev = ibdev->iboe.netdevs[i];
		क्रमागत ib_port_state curr_port_state;

		अगर (!curr_netdev)
			जारी;

		curr_port_state =
			(netअगर_running(curr_netdev) &&
			 netअगर_carrier_ok(curr_netdev)) ?
			IB_PORT_ACTIVE : IB_PORT_DOWN;

		bonded_port_state = (bonded_port_state != IB_PORT_ACTIVE) ?
			curr_port_state : IB_PORT_ACTIVE;
	पूर्ण
	spin_unlock_bh(&ibdev->iboe.lock);

	ibev.device = &ibdev->ib_dev;
	ibev.element.port_num = 1;
	ibev.event = (bonded_port_state == IB_PORT_ACTIVE) ?
		IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;

	ib_dispatch_event(&ibev);
पूर्ण

व्योम mlx4_ib_sl2vl_update(काष्ठा mlx4_ib_dev *mdev, पूर्णांक port)
अणु
	u64 sl2vl;
	पूर्णांक err;

	err = mlx4_ib_query_sl2vl(&mdev->ib_dev, port, &sl2vl);
	अगर (err) अणु
		pr_err("Unable to get current sl to vl mapping for port %d.  Using all zeroes (%d)\n",
		       port, err);
		sl2vl = 0;
	पूर्ण
	atomic64_set(&mdev->sl2vl[port - 1], sl2vl);
पूर्ण

अटल व्योम ib_sl2vl_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_event_work *ew = container_of(work, काष्ठा ib_event_work, work);
	काष्ठा mlx4_ib_dev *mdev = ew->ib_dev;
	पूर्णांक port = ew->port;

	mlx4_ib_sl2vl_update(mdev, port);

	kमुक्त(ew);
पूर्ण

व्योम mlx4_sched_ib_sl2vl_update_work(काष्ठा mlx4_ib_dev *ibdev,
				     पूर्णांक port)
अणु
	काष्ठा ib_event_work *ew;

	ew = kदो_स्मृति(माप(*ew), GFP_ATOMIC);
	अगर (ew) अणु
		INIT_WORK(&ew->work, ib_sl2vl_update_work);
		ew->port = port;
		ew->ib_dev = ibdev;
		queue_work(wq, &ew->work);
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_event(काष्ठा mlx4_dev *dev, व्योम *ibdev_ptr,
			  क्रमागत mlx4_dev_event event, अचिन्हित दीर्घ param)
अणु
	काष्ठा ib_event ibev;
	काष्ठा mlx4_ib_dev *ibdev = to_mdev((काष्ठा ib_device *) ibdev_ptr);
	काष्ठा mlx4_eqe *eqe = शून्य;
	काष्ठा ib_event_work *ew;
	पूर्णांक p = 0;

	अगर (mlx4_is_bonded(dev) &&
	    ((event == MLX4_DEV_EVENT_PORT_UP) ||
	    (event == MLX4_DEV_EVENT_PORT_DOWN))) अणु
		ew = kदो_स्मृति(माप(*ew), GFP_ATOMIC);
		अगर (!ew)
			वापस;
		INIT_WORK(&ew->work, handle_bonded_port_state_event);
		ew->ib_dev = ibdev;
		queue_work(wq, &ew->work);
		वापस;
	पूर्ण

	अगर (event == MLX4_DEV_EVENT_PORT_MGMT_CHANGE)
		eqe = (काष्ठा mlx4_eqe *)param;
	अन्यथा
		p = (पूर्णांक) param;

	चयन (event) अणु
	हाल MLX4_DEV_EVENT_PORT_UP:
		अगर (p > ibdev->num_ports)
			वापस;
		अगर (!mlx4_is_slave(dev) &&
		    rdma_port_get_link_layer(&ibdev->ib_dev, p) ==
			IB_LINK_LAYER_INFINIBAND) अणु
			अगर (mlx4_is_master(dev))
				mlx4_ib_invalidate_all_guid_record(ibdev, p);
			अगर (ibdev->dev->flags & MLX4_FLAG_SECURE_HOST &&
			    !(ibdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SL_TO_VL_CHANGE_EVENT))
				mlx4_sched_ib_sl2vl_update_work(ibdev, p);
		पूर्ण
		ibev.event = IB_EVENT_PORT_ACTIVE;
		अवरोध;

	हाल MLX4_DEV_EVENT_PORT_DOWN:
		अगर (p > ibdev->num_ports)
			वापस;
		ibev.event = IB_EVENT_PORT_ERR;
		अवरोध;

	हाल MLX4_DEV_EVENT_CATASTROPHIC_ERROR:
		ibdev->ib_active = false;
		ibev.event = IB_EVENT_DEVICE_FATAL;
		mlx4_ib_handle_catas_error(ibdev);
		अवरोध;

	हाल MLX4_DEV_EVENT_PORT_MGMT_CHANGE:
		ew = kदो_स्मृति(माप *ew, GFP_ATOMIC);
		अगर (!ew)
			अवरोध;

		INIT_WORK(&ew->work, handle_port_mgmt_change_event);
		स_नकल(&ew->ib_eqe, eqe, माप *eqe);
		ew->ib_dev = ibdev;
		/* need to queue only क्रम port owner, which uses GEN_EQE */
		अगर (mlx4_is_master(dev))
			queue_work(wq, &ew->work);
		अन्यथा
			handle_port_mgmt_change_event(&ew->work);
		वापस;

	हाल MLX4_DEV_EVENT_SLAVE_INIT:
		/* here, p is the slave id */
		करो_slave_init(ibdev, p, 1);
		अगर (mlx4_is_master(dev)) अणु
			पूर्णांक i;

			क्रम (i = 1; i <= ibdev->num_ports; i++) अणु
				अगर (rdma_port_get_link_layer(&ibdev->ib_dev, i)
					== IB_LINK_LAYER_INFINIBAND)
					mlx4_ib_slave_alias_guid_event(ibdev,
								       p, i,
								       1);
			पूर्ण
		पूर्ण
		वापस;

	हाल MLX4_DEV_EVENT_SLAVE_SHUTDOWN:
		अगर (mlx4_is_master(dev)) अणु
			पूर्णांक i;

			क्रम (i = 1; i <= ibdev->num_ports; i++) अणु
				अगर (rdma_port_get_link_layer(&ibdev->ib_dev, i)
					== IB_LINK_LAYER_INFINIBAND)
					mlx4_ib_slave_alias_guid_event(ibdev,
								       p, i,
								       0);
			पूर्ण
		पूर्ण
		/* here, p is the slave id */
		करो_slave_init(ibdev, p, 0);
		वापस;

	शेष:
		वापस;
	पूर्ण

	ibev.device	      = ibdev_ptr;
	ibev.element.port_num = mlx4_is_bonded(ibdev->dev) ? 1 : (u8)p;

	ib_dispatch_event(&ibev);
पूर्ण

अटल काष्ठा mlx4_पूर्णांकerface mlx4_ib_पूर्णांकerface = अणु
	.add		= mlx4_ib_add,
	.हटाओ		= mlx4_ib_हटाओ,
	.event		= mlx4_ib_event,
	.protocol	= MLX4_PROT_IB_IPV6,
	.flags		= MLX4_INTFF_BONDING
पूर्ण;

अटल पूर्णांक __init mlx4_ib_init(व्योम)
अणु
	पूर्णांक err;

	wq = alloc_ordered_workqueue("mlx4_ib", WQ_MEM_RECLAIM);
	अगर (!wq)
		वापस -ENOMEM;

	err = mlx4_ib_mcg_init();
	अगर (err)
		जाओ clean_wq;

	err = mlx4_रेजिस्टर_पूर्णांकerface(&mlx4_ib_पूर्णांकerface);
	अगर (err)
		जाओ clean_mcg;

	वापस 0;

clean_mcg:
	mlx4_ib_mcg_destroy();

clean_wq:
	destroy_workqueue(wq);
	वापस err;
पूर्ण

अटल व्योम __निकास mlx4_ib_cleanup(व्योम)
अणु
	mlx4_unरेजिस्टर_पूर्णांकerface(&mlx4_ib_पूर्णांकerface);
	mlx4_ib_mcg_destroy();
	destroy_workqueue(wq);
पूर्ण

module_init(mlx4_ib_init);
module_निकास(mlx4_ib_cleanup);
