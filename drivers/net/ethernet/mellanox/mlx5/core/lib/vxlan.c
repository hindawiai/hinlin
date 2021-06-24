<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies, Ltd.  All rights reserved.
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/refcount.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <net/vxlan.h>
#समावेश "mlx5_core.h"
#समावेश "vxlan.h"

काष्ठा mlx5_vxlan अणु
	काष्ठा mlx5_core_dev		*mdev;
	/* max_num_ports is usuallly 4, 16 buckets is more than enough */
	DECLARE_HASHTABLE(htable, 4);
	काष्ठा mutex                    sync_lock; /* sync add/del port HW operations */
पूर्ण;

काष्ठा mlx5_vxlan_port अणु
	काष्ठा hlist_node hlist;
	u16 udp_port;
पूर्ण;

अटल पूर्णांक mlx5_vxlan_core_add_port_cmd(काष्ठा mlx5_core_dev *mdev, u16 port)
अणु
	u32 in[MLX5_ST_SZ_DW(add_vxlan_udp_dport_in)] = अणुपूर्ण;

	MLX5_SET(add_vxlan_udp_dport_in, in, opcode,
		 MLX5_CMD_OP_ADD_VXLAN_UDP_DPORT);
	MLX5_SET(add_vxlan_udp_dport_in, in, vxlan_udp_port, port);
	वापस mlx5_cmd_exec_in(mdev, add_vxlan_udp_dport, in);
पूर्ण

अटल पूर्णांक mlx5_vxlan_core_del_port_cmd(काष्ठा mlx5_core_dev *mdev, u16 port)
अणु
	u32 in[MLX5_ST_SZ_DW(delete_vxlan_udp_dport_in)] = अणुपूर्ण;

	MLX5_SET(delete_vxlan_udp_dport_in, in, opcode,
		 MLX5_CMD_OP_DELETE_VXLAN_UDP_DPORT);
	MLX5_SET(delete_vxlan_udp_dport_in, in, vxlan_udp_port, port);
	वापस mlx5_cmd_exec_in(mdev, delete_vxlan_udp_dport, in);
पूर्ण

bool mlx5_vxlan_lookup_port(काष्ठा mlx5_vxlan *vxlan, u16 port)
अणु
	काष्ठा mlx5_vxlan_port *vxlanp;
	bool found = false;

	अगर (!mlx5_vxlan_allowed(vxlan))
		वापस शून्य;

	rcu_पढ़ो_lock();
	hash_क्रम_each_possible_rcu(vxlan->htable, vxlanp, hlist, port)
		अगर (vxlanp->udp_port == port) अणु
			found = true;
			अवरोध;
		पूर्ण
	rcu_पढ़ो_unlock();

	वापस found;
पूर्ण

अटल काष्ठा mlx5_vxlan_port *vxlan_lookup_port(काष्ठा mlx5_vxlan *vxlan, u16 port)
अणु
	काष्ठा mlx5_vxlan_port *vxlanp;

	hash_क्रम_each_possible(vxlan->htable, vxlanp, hlist, port)
		अगर (vxlanp->udp_port == port)
			वापस vxlanp;
	वापस शून्य;
पूर्ण

पूर्णांक mlx5_vxlan_add_port(काष्ठा mlx5_vxlan *vxlan, u16 port)
अणु
	काष्ठा mlx5_vxlan_port *vxlanp;
	पूर्णांक ret;

	vxlanp = kzalloc(माप(*vxlanp), GFP_KERNEL);
	अगर (!vxlanp)
		वापस -ENOMEM;
	vxlanp->udp_port = port;

	ret = mlx5_vxlan_core_add_port_cmd(vxlan->mdev, port);
	अगर (ret) अणु
		kमुक्त(vxlanp);
		वापस ret;
	पूर्ण

	mutex_lock(&vxlan->sync_lock);
	hash_add_rcu(vxlan->htable, &vxlanp->hlist, port);
	mutex_unlock(&vxlan->sync_lock);

	वापस 0;
पूर्ण

पूर्णांक mlx5_vxlan_del_port(काष्ठा mlx5_vxlan *vxlan, u16 port)
अणु
	काष्ठा mlx5_vxlan_port *vxlanp;
	पूर्णांक ret = 0;

	mutex_lock(&vxlan->sync_lock);

	vxlanp = vxlan_lookup_port(vxlan, port);
	अगर (WARN_ON(!vxlanp)) अणु
		ret = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	hash_del_rcu(&vxlanp->hlist);
	synchronize_rcu();
	mlx5_vxlan_core_del_port_cmd(vxlan->mdev, port);
	kमुक्त(vxlanp);

out_unlock:
	mutex_unlock(&vxlan->sync_lock);
	वापस ret;
पूर्ण

काष्ठा mlx5_vxlan *mlx5_vxlan_create(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_vxlan *vxlan;

	अगर (!MLX5_CAP_ETH(mdev, tunnel_stateless_vxlan) || !mlx5_core_is_pf(mdev))
		वापस ERR_PTR(-ENOTSUPP);

	vxlan = kzalloc(माप(*vxlan), GFP_KERNEL);
	अगर (!vxlan)
		वापस ERR_PTR(-ENOMEM);

	vxlan->mdev = mdev;
	mutex_init(&vxlan->sync_lock);
	hash_init(vxlan->htable);

	/* Hardware adds 4789 (IANA_VXLAN_UDP_PORT) by शेष */
	mlx5_vxlan_add_port(vxlan, IANA_VXLAN_UDP_PORT);

	वापस vxlan;
पूर्ण

व्योम mlx5_vxlan_destroy(काष्ठा mlx5_vxlan *vxlan)
अणु
	अगर (!mlx5_vxlan_allowed(vxlan))
		वापस;

	mlx5_vxlan_del_port(vxlan, IANA_VXLAN_UDP_PORT);
	WARN_ON(!hash_empty(vxlan->htable));

	kमुक्त(vxlan);
पूर्ण

व्योम mlx5_vxlan_reset_to_शेष(काष्ठा mlx5_vxlan *vxlan)
अणु
	काष्ठा mlx5_vxlan_port *vxlanp;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक bkt;

	अगर (!mlx5_vxlan_allowed(vxlan))
		वापस;

	hash_क्रम_each_safe(vxlan->htable, bkt, पंचांगp, vxlanp, hlist) अणु
		/* Don't delete शेष UDP port added by the HW.
		 * Remove only user configured ports
		 */
		अगर (vxlanp->udp_port == IANA_VXLAN_UDP_PORT)
			जारी;
		mlx5_vxlan_del_port(vxlan, vxlanp->udp_port);
	पूर्ण
पूर्ण
