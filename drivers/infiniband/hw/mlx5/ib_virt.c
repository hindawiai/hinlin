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

#समावेश <linux/module.h>
#समावेश <linux/mlx5/vport.h>
#समावेश "mlx5_ib.h"

अटल अंतरभूत u32 mlx_to_net_policy(क्रमागत port_state_policy mlx_policy)
अणु
	चयन (mlx_policy) अणु
	हाल MLX5_POLICY_DOWN:
		वापस IFLA_VF_LINK_STATE_DISABLE;
	हाल MLX5_POLICY_UP:
		वापस IFLA_VF_LINK_STATE_ENABLE;
	हाल MLX5_POLICY_FOLLOW:
		वापस IFLA_VF_LINK_STATE_AUTO;
	शेष:
		वापस __IFLA_VF_LINK_STATE_MAX;
	पूर्ण
पूर्ण

पूर्णांक mlx5_ib_get_vf_config(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			  काष्ठा अगरla_vf_info *info)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_hca_vport_context *rep;
	पूर्णांक err;

	rep = kzalloc(माप(*rep), GFP_KERNEL);
	अगर (!rep)
		वापस -ENOMEM;

	err = mlx5_query_hca_vport_context(mdev, 1, 1,  vf + 1, rep);
	अगर (err) अणु
		mlx5_ib_warn(dev, "failed to query port policy for vf %d (%d)\n",
			     vf, err);
		जाओ मुक्त;
	पूर्ण
	स_रखो(info, 0, माप(*info));
	info->linkstate = mlx_to_net_policy(rep->policy);
	अगर (info->linkstate == __IFLA_VF_LINK_STATE_MAX)
		err = -EINVAL;

मुक्त:
	kमुक्त(rep);
	वापस err;
पूर्ण

अटल अंतरभूत क्रमागत port_state_policy net_to_mlx_policy(पूर्णांक policy)
अणु
	चयन (policy) अणु
	हाल IFLA_VF_LINK_STATE_DISABLE:
		वापस MLX5_POLICY_DOWN;
	हाल IFLA_VF_LINK_STATE_ENABLE:
		वापस MLX5_POLICY_UP;
	हाल IFLA_VF_LINK_STATE_AUTO:
		वापस MLX5_POLICY_FOLLOW;
	शेष:
		वापस MLX5_POLICY_INVALID;
	पूर्ण
पूर्ण

पूर्णांक mlx5_ib_set_vf_link_state(काष्ठा ib_device *device, पूर्णांक vf,
			      u32 port, पूर्णांक state)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_hca_vport_context *in;
	काष्ठा mlx5_vf_context *vfs_ctx = mdev->priv.sriov.vfs_ctx;
	पूर्णांक err;

	in = kzalloc(माप(*in), GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	in->policy = net_to_mlx_policy(state);
	अगर (in->policy == MLX5_POLICY_INVALID) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण
	in->field_select = MLX5_HCA_VPORT_SEL_STATE_POLICY;
	err = mlx5_core_modअगरy_hca_vport_context(mdev, 1, 1, vf + 1, in);
	अगर (!err)
		vfs_ctx[vf].policy = in->policy;

out:
	kमुक्त(in);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_get_vf_stats(काष्ठा ib_device *device, पूर्णांक vf,
			 u32 port, काष्ठा अगरla_vf_stats *stats)
अणु
	पूर्णांक out_sz = MLX5_ST_SZ_BYTES(query_vport_counter_out);
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5_ib_dev *dev;
	व्योम *out;
	पूर्णांक err;

	dev = to_mdev(device);
	mdev = dev->mdev;

	out = kzalloc(out_sz, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	err = mlx5_core_query_vport_counter(mdev, true, vf, port, out);
	अगर (err)
		जाओ ex;

	stats->rx_packets = MLX5_GET64_PR(query_vport_counter_out, out, received_ib_unicast.packets);
	stats->tx_packets = MLX5_GET64_PR(query_vport_counter_out, out, transmitted_ib_unicast.packets);
	stats->rx_bytes = MLX5_GET64_PR(query_vport_counter_out, out, received_ib_unicast.octets);
	stats->tx_bytes = MLX5_GET64_PR(query_vport_counter_out, out, transmitted_ib_unicast.octets);
	stats->multicast = MLX5_GET64_PR(query_vport_counter_out, out, received_ib_multicast.packets);

ex:
	kमुक्त(out);
	वापस err;
पूर्ण

अटल पूर्णांक set_vf_node_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			    u64 guid)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_hca_vport_context *in;
	काष्ठा mlx5_vf_context *vfs_ctx = mdev->priv.sriov.vfs_ctx;
	पूर्णांक err;

	in = kzalloc(माप(*in), GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	in->field_select = MLX5_HCA_VPORT_SEL_NODE_GUID;
	in->node_guid = guid;
	err = mlx5_core_modअगरy_hca_vport_context(mdev, 1, 1, vf + 1, in);
	अगर (!err) अणु
		vfs_ctx[vf].node_guid = guid;
		vfs_ctx[vf].node_guid_valid = 1;
	पूर्ण
	kमुक्त(in);
	वापस err;
पूर्ण

अटल पूर्णांक set_vf_port_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			    u64 guid)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_hca_vport_context *in;
	काष्ठा mlx5_vf_context *vfs_ctx = mdev->priv.sriov.vfs_ctx;
	पूर्णांक err;

	in = kzalloc(माप(*in), GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	in->field_select = MLX5_HCA_VPORT_SEL_PORT_GUID;
	in->port_guid = guid;
	err = mlx5_core_modअगरy_hca_vport_context(mdev, 1, 1, vf + 1, in);
	अगर (!err) अणु
		vfs_ctx[vf].port_guid = guid;
		vfs_ctx[vf].port_guid_valid = 1;
	पूर्ण
	kमुक्त(in);
	वापस err;
पूर्ण

पूर्णांक mlx5_ib_set_vf_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			u64 guid, पूर्णांक type)
अणु
	अगर (type == IFLA_VF_IB_NODE_GUID)
		वापस set_vf_node_guid(device, vf, port, guid);
	अन्यथा अगर (type == IFLA_VF_IB_PORT_GUID)
		वापस set_vf_port_guid(device, vf, port, guid);

	वापस -EINVAL;
पूर्ण

पूर्णांक mlx5_ib_get_vf_guid(काष्ठा ib_device *device, पूर्णांक vf, u32 port,
			काष्ठा अगरla_vf_guid *node_guid,
			काष्ठा अगरla_vf_guid *port_guid)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(device);
	काष्ठा mlx5_core_dev *mdev = dev->mdev;
	काष्ठा mlx5_vf_context *vfs_ctx = mdev->priv.sriov.vfs_ctx;

	node_guid->guid =
		vfs_ctx[vf].node_guid_valid ? vfs_ctx[vf].node_guid : 0;
	port_guid->guid =
		vfs_ctx[vf].port_guid_valid ? vfs_ctx[vf].port_guid : 0;

	वापस 0;
पूर्ण
