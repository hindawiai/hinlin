<शैली गुरु>
/*
 * Copyright (c) 2007 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/export.h>

#समावेश <linux/mlx4/cmd.h>

#समावेश "mlx4.h"
#समावेश "mlx4_stats.h"

#घोषणा MLX4_MAC_VALID		(1ull << 63)

#घोषणा MLX4_VLAN_VALID		(1u << 31)
#घोषणा MLX4_VLAN_MASK		0xfff

#घोषणा MLX4_STATS_TRAFFIC_COUNTERS_MASK	0xfULL
#घोषणा MLX4_STATS_TRAFFIC_DROPS_MASK		0xc0ULL
#घोषणा MLX4_STATS_ERROR_COUNTERS_MASK		0x1ffc30ULL
#घोषणा MLX4_STATS_PORT_COUNTERS_MASK		0x1fe00000ULL

#घोषणा MLX4_FLAG2_V_IGNORE_FCS_MASK		BIT(1)
#घोषणा MLX4_FLAG2_V_USER_MTU_MASK		BIT(5)
#घोषणा MLX4_FLAG2_V_USER_MAC_MASK		BIT(6)
#घोषणा MLX4_FLAG_V_MTU_MASK			BIT(0)
#घोषणा MLX4_FLAG_V_PPRX_MASK			BIT(1)
#घोषणा MLX4_FLAG_V_PPTX_MASK			BIT(2)
#घोषणा MLX4_IGNORE_FCS_MASK			0x1
#घोषणा MLX4_TC_MAX_NUMBER			8

व्योम mlx4_init_mac_table(काष्ठा mlx4_dev *dev, काष्ठा mlx4_mac_table *table)
अणु
	पूर्णांक i;

	mutex_init(&table->mutex);
	क्रम (i = 0; i < MLX4_MAX_MAC_NUM; i++) अणु
		table->entries[i] = 0;
		table->refs[i]	 = 0;
		table->is_dup[i] = false;
	पूर्ण
	table->max   = 1 << dev->caps.log_num_macs;
	table->total = 0;
पूर्ण

व्योम mlx4_init_vlan_table(काष्ठा mlx4_dev *dev, काष्ठा mlx4_vlan_table *table)
अणु
	पूर्णांक i;

	mutex_init(&table->mutex);
	क्रम (i = 0; i < MLX4_MAX_VLAN_NUM; i++) अणु
		table->entries[i] = 0;
		table->refs[i]	 = 0;
		table->is_dup[i] = false;
	पूर्ण
	table->max   = (1 << dev->caps.log_num_vlans) - MLX4_VLAN_REGULAR;
	table->total = 0;
पूर्ण

व्योम mlx4_init_roce_gid_table(काष्ठा mlx4_dev *dev,
			      काष्ठा mlx4_roce_gid_table *table)
अणु
	पूर्णांक i;

	mutex_init(&table->mutex);
	क्रम (i = 0; i < MLX4_ROCE_MAX_GIDS; i++)
		स_रखो(table->roce_gids[i].raw, 0, MLX4_ROCE_GID_ENTRY_SIZE);
पूर्ण

अटल पूर्णांक validate_index(काष्ठा mlx4_dev *dev,
			  काष्ठा mlx4_mac_table *table, पूर्णांक index)
अणु
	पूर्णांक err = 0;

	अगर (index < 0 || index >= table->max || !table->entries[index]) अणु
		mlx4_warn(dev, "No valid Mac entry for the given index\n");
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक find_index(काष्ठा mlx4_dev *dev,
		      काष्ठा mlx4_mac_table *table, u64 mac)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLX4_MAX_MAC_NUM; i++) अणु
		अगर (table->refs[i] &&
		    (MLX4_MAC_MASK & mac) ==
		    (MLX4_MAC_MASK & be64_to_cpu(table->entries[i])))
			वापस i;
	पूर्ण
	/* Mac not found */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mlx4_set_port_mac_table(काष्ठा mlx4_dev *dev, u8 port,
				   __be64 *entries)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 in_mod;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	स_नकल(mailbox->buf, entries, MLX4_MAC_TABLE_SIZE);

	in_mod = MLX4_SET_PORT_MAC_TABLE << 8 | port;

	err = mlx4_cmd(dev, mailbox->dma, in_mod, MLX4_SET_PORT_ETH_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mlx4_find_cached_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac, पूर्णांक *idx)
अणु
	काष्ठा mlx4_port_info *info = &mlx4_priv(dev)->port[port];
	काष्ठा mlx4_mac_table *table = &info->mac_table;
	पूर्णांक i;

	क्रम (i = 0; i < MLX4_MAX_MAC_NUM; i++) अणु
		अगर (!table->refs[i])
			जारी;

		अगर (mac == (MLX4_MAC_MASK & be64_to_cpu(table->entries[i]))) अणु
			*idx = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_find_cached_mac);

अटल bool mlx4_need_mf_bond(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक i, num_eth_ports = 0;

	अगर (!mlx4_is_mfunc(dev))
		वापस false;
	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_ETH)
		++num_eth_ports;

	वापस (num_eth_ports ==  2) ? true : false;
पूर्ण

पूर्णांक __mlx4_रेजिस्टर_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac)
अणु
	काष्ठा mlx4_port_info *info = &mlx4_priv(dev)->port[port];
	काष्ठा mlx4_mac_table *table = &info->mac_table;
	पूर्णांक i, err = 0;
	पूर्णांक मुक्त = -1;
	पूर्णांक मुक्त_क्रम_dup = -1;
	bool dup = mlx4_is_mf_bonded(dev);
	u8 dup_port = (port == 1) ? 2 : 1;
	काष्ठा mlx4_mac_table *dup_table = &mlx4_priv(dev)->port[dup_port].mac_table;
	bool need_mf_bond = mlx4_need_mf_bond(dev);
	bool can_mf_bond = true;

	mlx4_dbg(dev, "Registering MAC: 0x%llx for port %d %s duplicate\n",
		 (अचिन्हित दीर्घ दीर्घ)mac, port,
		 dup ? "with" : "without");

	अगर (need_mf_bond) अणु
		अगर (port == 1) अणु
			mutex_lock(&table->mutex);
			mutex_lock_nested(&dup_table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण अन्यथा अणु
			mutex_lock(&dup_table->mutex);
			mutex_lock_nested(&table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&table->mutex);
	पूर्ण

	अगर (need_mf_bond) अणु
		पूर्णांक index_at_port = -1;
		पूर्णांक index_at_dup_port = -1;

		क्रम (i = 0; i < MLX4_MAX_MAC_NUM; i++) अणु
			अगर (((MLX4_MAC_MASK & mac) == (MLX4_MAC_MASK & be64_to_cpu(table->entries[i]))))
				index_at_port = i;
			अगर (((MLX4_MAC_MASK & mac) == (MLX4_MAC_MASK & be64_to_cpu(dup_table->entries[i]))))
				index_at_dup_port = i;
		पूर्ण

		/* check that same mac is not in the tables at dअगरferent indices */
		अगर ((index_at_port != index_at_dup_port) &&
		    (index_at_port >= 0) &&
		    (index_at_dup_port >= 0))
			can_mf_bond = false;

		/* If the mac is alपढ़ोy in the primary table, the slot must be
		 * available in the duplicate table as well.
		 */
		अगर (index_at_port >= 0 && index_at_dup_port < 0 &&
		    dup_table->refs[index_at_port]) अणु
			can_mf_bond = false;
		पूर्ण
		/* If the mac is alपढ़ोy in the duplicate table, check that the
		 * corresponding index is not occupied in the primary table, or
		 * the primary table alपढ़ोy contains the mac at the same index.
		 * Otherwise, you cannot bond (primary contains a dअगरferent mac
		 * at that index).
		 */
		अगर (index_at_dup_port >= 0) अणु
			अगर (!table->refs[index_at_dup_port] ||
			    ((MLX4_MAC_MASK & mac) == (MLX4_MAC_MASK & be64_to_cpu(table->entries[index_at_dup_port]))))
				मुक्त_क्रम_dup = index_at_dup_port;
			अन्यथा
				can_mf_bond = false;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MLX4_MAX_MAC_NUM; i++) अणु
		अगर (!table->refs[i]) अणु
			अगर (मुक्त < 0)
				मुक्त = i;
			अगर (मुक्त_क्रम_dup < 0 && need_mf_bond && can_mf_bond) अणु
				अगर (!dup_table->refs[i])
					मुक्त_क्रम_dup = i;
			पूर्ण
			जारी;
		पूर्ण

		अगर ((MLX4_MAC_MASK & mac) ==
		     (MLX4_MAC_MASK & be64_to_cpu(table->entries[i]))) अणु
			/* MAC alपढ़ोy रेजिस्टरed, increment ref count */
			err = i;
			++table->refs[i];
			अगर (dup) अणु
				u64 dup_mac = MLX4_MAC_MASK & be64_to_cpu(dup_table->entries[i]);

				अगर (dup_mac != mac || !dup_table->is_dup[i]) अणु
					mlx4_warn(dev, "register mac: expect duplicate mac 0x%llx on port %d index %d\n",
						  mac, dup_port, i);
				पूर्ण
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (need_mf_bond && (मुक्त_क्रम_dup < 0)) अणु
		अगर (dup) अणु
			mlx4_warn(dev, "Fail to allocate duplicate MAC table entry\n");
			mlx4_warn(dev, "High Availability for virtual functions may not work as expected\n");
			dup = false;
		पूर्ण
		can_mf_bond = false;
	पूर्ण

	अगर (need_mf_bond && can_mf_bond)
		मुक्त = मुक्त_क्रम_dup;

	mlx4_dbg(dev, "Free MAC index is %d\n", मुक्त);

	अगर (table->total == table->max) अणु
		/* No मुक्त mac entries */
		err = -ENOSPC;
		जाओ out;
	पूर्ण

	/* Register new MAC */
	table->entries[मुक्त] = cpu_to_be64(mac | MLX4_MAC_VALID);

	err = mlx4_set_port_mac_table(dev, port, table->entries);
	अगर (unlikely(err)) अणु
		mlx4_err(dev, "Failed adding MAC: 0x%llx\n",
			 (अचिन्हित दीर्घ दीर्घ) mac);
		table->entries[मुक्त] = 0;
		जाओ out;
	पूर्ण
	table->refs[मुक्त] = 1;
	table->is_dup[मुक्त] = false;
	++table->total;
	अगर (dup) अणु
		dup_table->refs[मुक्त] = 0;
		dup_table->is_dup[मुक्त] = true;
		dup_table->entries[मुक्त] = cpu_to_be64(mac | MLX4_MAC_VALID);

		err = mlx4_set_port_mac_table(dev, dup_port, dup_table->entries);
		अगर (unlikely(err)) अणु
			mlx4_warn(dev, "Failed adding duplicate mac: 0x%llx\n", mac);
			dup_table->is_dup[मुक्त] = false;
			dup_table->entries[मुक्त] = 0;
			जाओ out;
		पूर्ण
		++dup_table->total;
	पूर्ण
	err = मुक्त;
out:
	अगर (need_mf_bond) अणु
		अगर (port == 2) अणु
			mutex_unlock(&table->mutex);
			mutex_unlock(&dup_table->mutex);
		पूर्ण अन्यथा अणु
			mutex_unlock(&dup_table->mutex);
			mutex_unlock(&table->mutex);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_unlock(&table->mutex);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__mlx4_रेजिस्टर_mac);

पूर्णांक mlx4_रेजिस्टर_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac)
अणु
	u64 out_param = 0;
	पूर्णांक err = -EINVAL;

	अगर (mlx4_is_mfunc(dev)) अणु
		अगर (!(dev->flags & MLX4_FLAG_OLD_REG_MAC)) अणु
			err = mlx4_cmd_imm(dev, mac, &out_param,
					   ((u32) port) << 8 | (u32) RES_MAC,
					   RES_OP_RESERVE_AND_MAP, MLX4_CMD_ALLOC_RES,
					   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		पूर्ण
		अगर (err && err == -EINVAL && mlx4_is_slave(dev)) अणु
			/* retry using old REG_MAC क्रमmat */
			set_param_l(&out_param, port);
			err = mlx4_cmd_imm(dev, mac, &out_param, RES_MAC,
					   RES_OP_RESERVE_AND_MAP, MLX4_CMD_ALLOC_RES,
					   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
			अगर (!err)
				dev->flags |= MLX4_FLAG_OLD_REG_MAC;
		पूर्ण
		अगर (err)
			वापस err;

		वापस get_param_l(&out_param);
	पूर्ण
	वापस __mlx4_रेजिस्टर_mac(dev, port, mac);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_रेजिस्टर_mac);

पूर्णांक mlx4_get_base_qpn(काष्ठा mlx4_dev *dev, u8 port)
अणु
	वापस dev->caps.reserved_qps_base[MLX4_QP_REGION_ETH_ADDR] +
			(port - 1) * (1 << dev->caps.log_num_macs);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_base_qpn);

व्योम __mlx4_unरेजिस्टर_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac)
अणु
	काष्ठा mlx4_port_info *info;
	काष्ठा mlx4_mac_table *table;
	पूर्णांक index;
	bool dup = mlx4_is_mf_bonded(dev);
	u8 dup_port = (port == 1) ? 2 : 1;
	काष्ठा mlx4_mac_table *dup_table = &mlx4_priv(dev)->port[dup_port].mac_table;

	अगर (port < 1 || port > dev->caps.num_ports) अणु
		mlx4_warn(dev, "invalid port number (%d), aborting...\n", port);
		वापस;
	पूर्ण
	info = &mlx4_priv(dev)->port[port];
	table = &info->mac_table;

	अगर (dup) अणु
		अगर (port == 1) अणु
			mutex_lock(&table->mutex);
			mutex_lock_nested(&dup_table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण अन्यथा अणु
			mutex_lock(&dup_table->mutex);
			mutex_lock_nested(&table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&table->mutex);
	पूर्ण

	index = find_index(dev, table, mac);

	अगर (validate_index(dev, table, index))
		जाओ out;

	अगर (--table->refs[index] || table->is_dup[index]) अणु
		mlx4_dbg(dev, "Have more references for index %d, no need to modify mac table\n",
			 index);
		अगर (!table->refs[index])
			dup_table->is_dup[index] = false;
		जाओ out;
	पूर्ण

	table->entries[index] = 0;
	अगर (mlx4_set_port_mac_table(dev, port, table->entries))
		mlx4_warn(dev, "Fail to set mac in port %d during unregister\n", port);
	--table->total;

	अगर (dup) अणु
		dup_table->is_dup[index] = false;
		अगर (dup_table->refs[index])
			जाओ out;
		dup_table->entries[index] = 0;
		अगर (mlx4_set_port_mac_table(dev, dup_port, dup_table->entries))
			mlx4_warn(dev, "Fail to set mac in duplicate port %d during unregister\n", dup_port);

		--table->total;
	पूर्ण
out:
	अगर (dup) अणु
		अगर (port == 2) अणु
			mutex_unlock(&table->mutex);
			mutex_unlock(&dup_table->mutex);
		पूर्ण अन्यथा अणु
			mutex_unlock(&dup_table->mutex);
			mutex_unlock(&table->mutex);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_unlock(&table->mutex);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__mlx4_unरेजिस्टर_mac);

व्योम mlx4_unरेजिस्टर_mac(काष्ठा mlx4_dev *dev, u8 port, u64 mac)
अणु
	u64 out_param = 0;

	अगर (mlx4_is_mfunc(dev)) अणु
		अगर (!(dev->flags & MLX4_FLAG_OLD_REG_MAC)) अणु
			(व्योम) mlx4_cmd_imm(dev, mac, &out_param,
					    ((u32) port) << 8 | (u32) RES_MAC,
					    RES_OP_RESERVE_AND_MAP, MLX4_CMD_FREE_RES,
					    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		पूर्ण अन्यथा अणु
			/* use old unरेजिस्टर mac क्रमmat */
			set_param_l(&out_param, port);
			(व्योम) mlx4_cmd_imm(dev, mac, &out_param, RES_MAC,
					    RES_OP_RESERVE_AND_MAP, MLX4_CMD_FREE_RES,
					    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		पूर्ण
		वापस;
	पूर्ण
	__mlx4_unरेजिस्टर_mac(dev, port, mac);
	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_unरेजिस्टर_mac);

पूर्णांक __mlx4_replace_mac(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक qpn, u64 new_mac)
अणु
	काष्ठा mlx4_port_info *info = &mlx4_priv(dev)->port[port];
	काष्ठा mlx4_mac_table *table = &info->mac_table;
	पूर्णांक index = qpn - info->base_qpn;
	पूर्णांक err = 0;
	bool dup = mlx4_is_mf_bonded(dev);
	u8 dup_port = (port == 1) ? 2 : 1;
	काष्ठा mlx4_mac_table *dup_table = &mlx4_priv(dev)->port[dup_port].mac_table;

	/* CX1 करोesn't support multi-functions */
	अगर (dup) अणु
		अगर (port == 1) अणु
			mutex_lock(&table->mutex);
			mutex_lock_nested(&dup_table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण अन्यथा अणु
			mutex_lock(&dup_table->mutex);
			mutex_lock_nested(&table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&table->mutex);
	पूर्ण

	err = validate_index(dev, table, index);
	अगर (err)
		जाओ out;

	table->entries[index] = cpu_to_be64(new_mac | MLX4_MAC_VALID);

	err = mlx4_set_port_mac_table(dev, port, table->entries);
	अगर (unlikely(err)) अणु
		mlx4_err(dev, "Failed adding MAC: 0x%llx\n",
			 (अचिन्हित दीर्घ दीर्घ) new_mac);
		table->entries[index] = 0;
	पूर्ण अन्यथा अणु
		अगर (dup) अणु
			dup_table->entries[index] = cpu_to_be64(new_mac | MLX4_MAC_VALID);

			err = mlx4_set_port_mac_table(dev, dup_port, dup_table->entries);
			अगर (unlikely(err)) अणु
				mlx4_err(dev, "Failed adding duplicate MAC: 0x%llx\n",
					 (अचिन्हित दीर्घ दीर्घ)new_mac);
				dup_table->entries[index] = 0;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	अगर (dup) अणु
		अगर (port == 2) अणु
			mutex_unlock(&table->mutex);
			mutex_unlock(&dup_table->mutex);
		पूर्ण अन्यथा अणु
			mutex_unlock(&dup_table->mutex);
			mutex_unlock(&table->mutex);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_unlock(&table->mutex);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__mlx4_replace_mac);

अटल पूर्णांक mlx4_set_port_vlan_table(काष्ठा mlx4_dev *dev, u8 port,
				    __be32 *entries)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 in_mod;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	स_नकल(mailbox->buf, entries, MLX4_VLAN_TABLE_SIZE);
	in_mod = MLX4_SET_PORT_VLAN_TABLE << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, MLX4_SET_PORT_ETH_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	वापस err;
पूर्ण

पूर्णांक mlx4_find_cached_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vid, पूर्णांक *idx)
अणु
	काष्ठा mlx4_vlan_table *table = &mlx4_priv(dev)->port[port].vlan_table;
	पूर्णांक i;

	क्रम (i = 0; i < MLX4_MAX_VLAN_NUM; ++i) अणु
		अगर (table->refs[i] &&
		    (vid == (MLX4_VLAN_MASK &
			      be32_to_cpu(table->entries[i])))) अणु
			/* VLAN alपढ़ोy रेजिस्टरed, increase reference count */
			*idx = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_find_cached_vlan);

पूर्णांक __mlx4_रेजिस्टर_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vlan,
				पूर्णांक *index)
अणु
	काष्ठा mlx4_vlan_table *table = &mlx4_priv(dev)->port[port].vlan_table;
	पूर्णांक i, err = 0;
	पूर्णांक मुक्त = -1;
	पूर्णांक मुक्त_क्रम_dup = -1;
	bool dup = mlx4_is_mf_bonded(dev);
	u8 dup_port = (port == 1) ? 2 : 1;
	काष्ठा mlx4_vlan_table *dup_table = &mlx4_priv(dev)->port[dup_port].vlan_table;
	bool need_mf_bond = mlx4_need_mf_bond(dev);
	bool can_mf_bond = true;

	mlx4_dbg(dev, "Registering VLAN: %d for port %d %s duplicate\n",
		 vlan, port,
		 dup ? "with" : "without");

	अगर (need_mf_bond) अणु
		अगर (port == 1) अणु
			mutex_lock(&table->mutex);
			mutex_lock_nested(&dup_table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण अन्यथा अणु
			mutex_lock(&dup_table->mutex);
			mutex_lock_nested(&table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&table->mutex);
	पूर्ण

	अगर (table->total == table->max) अणु
		/* No मुक्त vlan entries */
		err = -ENOSPC;
		जाओ out;
	पूर्ण

	अगर (need_mf_bond) अणु
		पूर्णांक index_at_port = -1;
		पूर्णांक index_at_dup_port = -1;

		क्रम (i = MLX4_VLAN_REGULAR; i < MLX4_MAX_VLAN_NUM; i++) अणु
			अगर (vlan == (MLX4_VLAN_MASK & be32_to_cpu(table->entries[i])))
				index_at_port = i;
			अगर (vlan == (MLX4_VLAN_MASK & be32_to_cpu(dup_table->entries[i])))
				index_at_dup_port = i;
		पूर्ण
		/* check that same vlan is not in the tables at dअगरferent indices */
		अगर ((index_at_port != index_at_dup_port) &&
		    (index_at_port >= 0) &&
		    (index_at_dup_port >= 0))
			can_mf_bond = false;

		/* If the vlan is alपढ़ोy in the primary table, the slot must be
		 * available in the duplicate table as well.
		 */
		अगर (index_at_port >= 0 && index_at_dup_port < 0 &&
		    dup_table->refs[index_at_port]) अणु
			can_mf_bond = false;
		पूर्ण
		/* If the vlan is alपढ़ोy in the duplicate table, check that the
		 * corresponding index is not occupied in the primary table, or
		 * the primary table alपढ़ोy contains the vlan at the same index.
		 * Otherwise, you cannot bond (primary contains a dअगरferent vlan
		 * at that index).
		 */
		अगर (index_at_dup_port >= 0) अणु
			अगर (!table->refs[index_at_dup_port] ||
			    (vlan == (MLX4_VLAN_MASK & be32_to_cpu(dup_table->entries[index_at_dup_port]))))
				मुक्त_क्रम_dup = index_at_dup_port;
			अन्यथा
				can_mf_bond = false;
		पूर्ण
	पूर्ण

	क्रम (i = MLX4_VLAN_REGULAR; i < MLX4_MAX_VLAN_NUM; i++) अणु
		अगर (!table->refs[i]) अणु
			अगर (मुक्त < 0)
				मुक्त = i;
			अगर (मुक्त_क्रम_dup < 0 && need_mf_bond && can_mf_bond) अणु
				अगर (!dup_table->refs[i])
					मुक्त_क्रम_dup = i;
			पूर्ण
		पूर्ण

		अगर ((table->refs[i] || table->is_dup[i]) &&
		    (vlan == (MLX4_VLAN_MASK &
			      be32_to_cpu(table->entries[i])))) अणु
			/* Vlan alपढ़ोy रेजिस्टरed, increase references count */
			mlx4_dbg(dev, "vlan %u is already registered.\n", vlan);
			*index = i;
			++table->refs[i];
			अगर (dup) अणु
				u16 dup_vlan = MLX4_VLAN_MASK & be32_to_cpu(dup_table->entries[i]);

				अगर (dup_vlan != vlan || !dup_table->is_dup[i]) अणु
					mlx4_warn(dev, "register vlan: expected duplicate vlan %u on port %d index %d\n",
						  vlan, dup_port, i);
				पूर्ण
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (need_mf_bond && (मुक्त_क्रम_dup < 0)) अणु
		अगर (dup) अणु
			mlx4_warn(dev, "Fail to allocate duplicate VLAN table entry\n");
			mlx4_warn(dev, "High Availability for virtual functions may not work as expected\n");
			dup = false;
		पूर्ण
		can_mf_bond = false;
	पूर्ण

	अगर (need_mf_bond && can_mf_bond)
		मुक्त = मुक्त_क्रम_dup;

	अगर (मुक्त < 0) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Register new VLAN */
	table->refs[मुक्त] = 1;
	table->is_dup[मुक्त] = false;
	table->entries[मुक्त] = cpu_to_be32(vlan | MLX4_VLAN_VALID);

	err = mlx4_set_port_vlan_table(dev, port, table->entries);
	अगर (unlikely(err)) अणु
		mlx4_warn(dev, "Failed adding vlan: %u\n", vlan);
		table->refs[मुक्त] = 0;
		table->entries[मुक्त] = 0;
		जाओ out;
	पूर्ण
	++table->total;
	अगर (dup) अणु
		dup_table->refs[मुक्त] = 0;
		dup_table->is_dup[मुक्त] = true;
		dup_table->entries[मुक्त] = cpu_to_be32(vlan | MLX4_VLAN_VALID);

		err = mlx4_set_port_vlan_table(dev, dup_port, dup_table->entries);
		अगर (unlikely(err)) अणु
			mlx4_warn(dev, "Failed adding duplicate vlan: %u\n", vlan);
			dup_table->is_dup[मुक्त] = false;
			dup_table->entries[मुक्त] = 0;
			जाओ out;
		पूर्ण
		++dup_table->total;
	पूर्ण

	*index = मुक्त;
out:
	अगर (need_mf_bond) अणु
		अगर (port == 2) अणु
			mutex_unlock(&table->mutex);
			mutex_unlock(&dup_table->mutex);
		पूर्ण अन्यथा अणु
			mutex_unlock(&dup_table->mutex);
			mutex_unlock(&table->mutex);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_unlock(&table->mutex);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक mlx4_रेजिस्टर_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vlan, पूर्णांक *index)
अणु
	u64 out_param = 0;
	पूर्णांक err;

	अगर (vlan > 4095)
		वापस -EINVAL;

	अगर (mlx4_is_mfunc(dev)) अणु
		err = mlx4_cmd_imm(dev, vlan, &out_param,
				   ((u32) port) << 8 | (u32) RES_VLAN,
				   RES_OP_RESERVE_AND_MAP, MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		अगर (!err)
			*index = get_param_l(&out_param);

		वापस err;
	पूर्ण
	वापस __mlx4_रेजिस्टर_vlan(dev, port, vlan, index);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_रेजिस्टर_vlan);

व्योम __mlx4_unरेजिस्टर_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vlan)
अणु
	काष्ठा mlx4_vlan_table *table = &mlx4_priv(dev)->port[port].vlan_table;
	पूर्णांक index;
	bool dup = mlx4_is_mf_bonded(dev);
	u8 dup_port = (port == 1) ? 2 : 1;
	काष्ठा mlx4_vlan_table *dup_table = &mlx4_priv(dev)->port[dup_port].vlan_table;

	अगर (dup) अणु
		अगर (port == 1) अणु
			mutex_lock(&table->mutex);
			mutex_lock_nested(&dup_table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण अन्यथा अणु
			mutex_lock(&dup_table->mutex);
			mutex_lock_nested(&table->mutex, SINGLE_DEPTH_NESTING);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&table->mutex);
	पूर्ण

	अगर (mlx4_find_cached_vlan(dev, port, vlan, &index)) अणु
		mlx4_warn(dev, "vlan 0x%x is not in the vlan table\n", vlan);
		जाओ out;
	पूर्ण

	अगर (index < MLX4_VLAN_REGULAR) अणु
		mlx4_warn(dev, "Trying to free special vlan index %d\n", index);
		जाओ out;
	पूर्ण

	अगर (--table->refs[index] || table->is_dup[index]) अणु
		mlx4_dbg(dev, "Have %d more references for index %d, no need to modify vlan table\n",
			 table->refs[index], index);
		अगर (!table->refs[index])
			dup_table->is_dup[index] = false;
		जाओ out;
	पूर्ण
	table->entries[index] = 0;
	अगर (mlx4_set_port_vlan_table(dev, port, table->entries))
		mlx4_warn(dev, "Fail to set vlan in port %d during unregister\n", port);
	--table->total;
	अगर (dup) अणु
		dup_table->is_dup[index] = false;
		अगर (dup_table->refs[index])
			जाओ out;
		dup_table->entries[index] = 0;
		अगर (mlx4_set_port_vlan_table(dev, dup_port, dup_table->entries))
			mlx4_warn(dev, "Fail to set vlan in duplicate port %d during unregister\n", dup_port);
		--dup_table->total;
	पूर्ण
out:
	अगर (dup) अणु
		अगर (port == 2) अणु
			mutex_unlock(&table->mutex);
			mutex_unlock(&dup_table->mutex);
		पूर्ण अन्यथा अणु
			mutex_unlock(&dup_table->mutex);
			mutex_unlock(&table->mutex);
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_unlock(&table->mutex);
	पूर्ण
पूर्ण

व्योम mlx4_unरेजिस्टर_vlan(काष्ठा mlx4_dev *dev, u8 port, u16 vlan)
अणु
	u64 out_param = 0;

	अगर (mlx4_is_mfunc(dev)) अणु
		(व्योम) mlx4_cmd_imm(dev, vlan, &out_param,
				    ((u32) port) << 8 | (u32) RES_VLAN,
				    RES_OP_RESERVE_AND_MAP,
				    MLX4_CMD_FREE_RES, MLX4_CMD_TIME_CLASS_A,
				    MLX4_CMD_WRAPPED);
		वापस;
	पूर्ण
	__mlx4_unरेजिस्टर_vlan(dev, port, vlan);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_unरेजिस्टर_vlan);

पूर्णांक mlx4_bond_mac_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_mac_table *t1 = &mlx4_priv(dev)->port[1].mac_table;
	काष्ठा mlx4_mac_table *t2 = &mlx4_priv(dev)->port[2].mac_table;
	पूर्णांक ret = 0;
	पूर्णांक i;
	bool update1 = false;
	bool update2 = false;

	mutex_lock(&t1->mutex);
	mutex_lock(&t2->mutex);
	क्रम (i = 0; i < MLX4_MAX_MAC_NUM; i++) अणु
		अगर ((t1->entries[i] != t2->entries[i]) &&
		    t1->entries[i] && t2->entries[i]) अणु
			mlx4_warn(dev, "can't duplicate entry %d in mac table\n", i);
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MLX4_MAX_MAC_NUM; i++) अणु
		अगर (t1->entries[i] && !t2->entries[i]) अणु
			t2->entries[i] = t1->entries[i];
			t2->is_dup[i] = true;
			update2 = true;
		पूर्ण अन्यथा अगर (!t1->entries[i] && t2->entries[i]) अणु
			t1->entries[i] = t2->entries[i];
			t1->is_dup[i] = true;
			update1 = true;
		पूर्ण अन्यथा अगर (t1->entries[i] && t2->entries[i]) अणु
			t1->is_dup[i] = true;
			t2->is_dup[i] = true;
		पूर्ण
	पूर्ण

	अगर (update1) अणु
		ret = mlx4_set_port_mac_table(dev, 1, t1->entries);
		अगर (ret)
			mlx4_warn(dev, "failed to set MAC table for port 1 (%d)\n", ret);
	पूर्ण
	अगर (!ret && update2) अणु
		ret = mlx4_set_port_mac_table(dev, 2, t2->entries);
		अगर (ret)
			mlx4_warn(dev, "failed to set MAC table for port 2 (%d)\n", ret);
	पूर्ण

	अगर (ret)
		mlx4_warn(dev, "failed to create mirror MAC tables\n");
unlock:
	mutex_unlock(&t2->mutex);
	mutex_unlock(&t1->mutex);
	वापस ret;
पूर्ण

पूर्णांक mlx4_unbond_mac_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_mac_table *t1 = &mlx4_priv(dev)->port[1].mac_table;
	काष्ठा mlx4_mac_table *t2 = &mlx4_priv(dev)->port[2].mac_table;
	पूर्णांक ret = 0;
	पूर्णांक ret1;
	पूर्णांक i;
	bool update1 = false;
	bool update2 = false;

	mutex_lock(&t1->mutex);
	mutex_lock(&t2->mutex);
	क्रम (i = 0; i < MLX4_MAX_MAC_NUM; i++) अणु
		अगर (t1->entries[i] != t2->entries[i]) अणु
			mlx4_warn(dev, "mac table is in an unexpected state when trying to unbond\n");
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MLX4_MAX_MAC_NUM; i++) अणु
		अगर (!t1->entries[i])
			जारी;
		t1->is_dup[i] = false;
		अगर (!t1->refs[i]) अणु
			t1->entries[i] = 0;
			update1 = true;
		पूर्ण
		t2->is_dup[i] = false;
		अगर (!t2->refs[i]) अणु
			t2->entries[i] = 0;
			update2 = true;
		पूर्ण
	पूर्ण

	अगर (update1) अणु
		ret = mlx4_set_port_mac_table(dev, 1, t1->entries);
		अगर (ret)
			mlx4_warn(dev, "failed to unmirror MAC tables for port 1(%d)\n", ret);
	पूर्ण
	अगर (update2) अणु
		ret1 = mlx4_set_port_mac_table(dev, 2, t2->entries);
		अगर (ret1) अणु
			mlx4_warn(dev, "failed to unmirror MAC tables for port 2(%d)\n", ret1);
			ret = ret1;
		पूर्ण
	पूर्ण
unlock:
	mutex_unlock(&t2->mutex);
	mutex_unlock(&t1->mutex);
	वापस ret;
पूर्ण

पूर्णांक mlx4_bond_vlan_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_vlan_table *t1 = &mlx4_priv(dev)->port[1].vlan_table;
	काष्ठा mlx4_vlan_table *t2 = &mlx4_priv(dev)->port[2].vlan_table;
	पूर्णांक ret = 0;
	पूर्णांक i;
	bool update1 = false;
	bool update2 = false;

	mutex_lock(&t1->mutex);
	mutex_lock(&t2->mutex);
	क्रम (i = 0; i < MLX4_MAX_VLAN_NUM; i++) अणु
		अगर ((t1->entries[i] != t2->entries[i]) &&
		    t1->entries[i] && t2->entries[i]) अणु
			mlx4_warn(dev, "can't duplicate entry %d in vlan table\n", i);
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MLX4_MAX_VLAN_NUM; i++) अणु
		अगर (t1->entries[i] && !t2->entries[i]) अणु
			t2->entries[i] = t1->entries[i];
			t2->is_dup[i] = true;
			update2 = true;
		पूर्ण अन्यथा अगर (!t1->entries[i] && t2->entries[i]) अणु
			t1->entries[i] = t2->entries[i];
			t1->is_dup[i] = true;
			update1 = true;
		पूर्ण अन्यथा अगर (t1->entries[i] && t2->entries[i]) अणु
			t1->is_dup[i] = true;
			t2->is_dup[i] = true;
		पूर्ण
	पूर्ण

	अगर (update1) अणु
		ret = mlx4_set_port_vlan_table(dev, 1, t1->entries);
		अगर (ret)
			mlx4_warn(dev, "failed to set VLAN table for port 1 (%d)\n", ret);
	पूर्ण
	अगर (!ret && update2) अणु
		ret = mlx4_set_port_vlan_table(dev, 2, t2->entries);
		अगर (ret)
			mlx4_warn(dev, "failed to set VLAN table for port 2 (%d)\n", ret);
	पूर्ण

	अगर (ret)
		mlx4_warn(dev, "failed to create mirror VLAN tables\n");
unlock:
	mutex_unlock(&t2->mutex);
	mutex_unlock(&t1->mutex);
	वापस ret;
पूर्ण

पूर्णांक mlx4_unbond_vlan_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_vlan_table *t1 = &mlx4_priv(dev)->port[1].vlan_table;
	काष्ठा mlx4_vlan_table *t2 = &mlx4_priv(dev)->port[2].vlan_table;
	पूर्णांक ret = 0;
	पूर्णांक ret1;
	पूर्णांक i;
	bool update1 = false;
	bool update2 = false;

	mutex_lock(&t1->mutex);
	mutex_lock(&t2->mutex);
	क्रम (i = 0; i < MLX4_MAX_VLAN_NUM; i++) अणु
		अगर (t1->entries[i] != t2->entries[i]) अणु
			mlx4_warn(dev, "vlan table is in an unexpected state when trying to unbond\n");
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MLX4_MAX_VLAN_NUM; i++) अणु
		अगर (!t1->entries[i])
			जारी;
		t1->is_dup[i] = false;
		अगर (!t1->refs[i]) अणु
			t1->entries[i] = 0;
			update1 = true;
		पूर्ण
		t2->is_dup[i] = false;
		अगर (!t2->refs[i]) अणु
			t2->entries[i] = 0;
			update2 = true;
		पूर्ण
	पूर्ण

	अगर (update1) अणु
		ret = mlx4_set_port_vlan_table(dev, 1, t1->entries);
		अगर (ret)
			mlx4_warn(dev, "failed to unmirror VLAN tables for port 1(%d)\n", ret);
	पूर्ण
	अगर (update2) अणु
		ret1 = mlx4_set_port_vlan_table(dev, 2, t2->entries);
		अगर (ret1) अणु
			mlx4_warn(dev, "failed to unmirror VLAN tables for port 2(%d)\n", ret1);
			ret = ret1;
		पूर्ण
	पूर्ण
unlock:
	mutex_unlock(&t2->mutex);
	mutex_unlock(&t1->mutex);
	वापस ret;
पूर्ण

पूर्णांक mlx4_get_port_ib_caps(काष्ठा mlx4_dev *dev, u8 port, __be32 *caps)
अणु
	काष्ठा mlx4_cmd_mailbox *inmailbox, *ouपंचांगailbox;
	u8 *inbuf, *outbuf;
	पूर्णांक err;

	inmailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(inmailbox))
		वापस PTR_ERR(inmailbox);

	ouपंचांगailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(ouपंचांगailbox)) अणु
		mlx4_मुक्त_cmd_mailbox(dev, inmailbox);
		वापस PTR_ERR(ouपंचांगailbox);
	पूर्ण

	inbuf = inmailbox->buf;
	outbuf = ouपंचांगailbox->buf;
	inbuf[0] = 1;
	inbuf[1] = 1;
	inbuf[2] = 1;
	inbuf[3] = 1;
	*(__be16 *) (&inbuf[16]) = cpu_to_be16(0x0015);
	*(__be32 *) (&inbuf[20]) = cpu_to_be32(port);

	err = mlx4_cmd_box(dev, inmailbox->dma, ouपंचांगailbox->dma, port, 3,
			   MLX4_CMD_MAD_IFC, MLX4_CMD_TIME_CLASS_C,
			   MLX4_CMD_NATIVE);
	अगर (!err)
		*caps = *(__be32 *) (outbuf + 84);
	mlx4_मुक्त_cmd_mailbox(dev, inmailbox);
	mlx4_मुक्त_cmd_mailbox(dev, ouपंचांगailbox);
	वापस err;
पूर्ण
अटल काष्ठा mlx4_roce_gid_entry zgid_entry;

पूर्णांक mlx4_get_slave_num_gids(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port)
अणु
	पूर्णांक vfs;
	पूर्णांक slave_gid = slave;
	अचिन्हित i;
	काष्ठा mlx4_slaves_pport slaves_pport;
	काष्ठा mlx4_active_ports actv_ports;
	अचिन्हित max_port_p_one;

	अगर (slave == 0)
		वापस MLX4_ROCE_PF_GIDS;

	/* Slave is a VF */
	slaves_pport = mlx4_phys_to_slaves_pport(dev, port);
	actv_ports = mlx4_get_active_ports(dev, slave);
	max_port_p_one = find_first_bit(actv_ports.ports, dev->caps.num_ports) +
		biपंचांगap_weight(actv_ports.ports, dev->caps.num_ports) + 1;

	क्रम (i = 1; i < max_port_p_one; i++) अणु
		काष्ठा mlx4_active_ports exclusive_ports;
		काष्ठा mlx4_slaves_pport slaves_pport_actv;
		biपंचांगap_zero(exclusive_ports.ports, dev->caps.num_ports);
		set_bit(i - 1, exclusive_ports.ports);
		अगर (i == port)
			जारी;
		slaves_pport_actv = mlx4_phys_to_slaves_pport_actv(
				    dev, &exclusive_ports);
		slave_gid -= biपंचांगap_weight(slaves_pport_actv.slaves,
					   dev->persist->num_vfs + 1);
	पूर्ण
	vfs = biपंचांगap_weight(slaves_pport.slaves, dev->persist->num_vfs + 1) - 1;
	अगर (slave_gid <= ((MLX4_ROCE_MAX_GIDS - MLX4_ROCE_PF_GIDS) % vfs))
		वापस ((MLX4_ROCE_MAX_GIDS - MLX4_ROCE_PF_GIDS) / vfs) + 1;
	वापस (MLX4_ROCE_MAX_GIDS - MLX4_ROCE_PF_GIDS) / vfs;
पूर्ण

पूर्णांक mlx4_get_base_gid_ix(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port)
अणु
	पूर्णांक gids;
	अचिन्हित i;
	पूर्णांक slave_gid = slave;
	पूर्णांक vfs;

	काष्ठा mlx4_slaves_pport slaves_pport;
	काष्ठा mlx4_active_ports actv_ports;
	अचिन्हित max_port_p_one;

	अगर (slave == 0)
		वापस 0;

	slaves_pport = mlx4_phys_to_slaves_pport(dev, port);
	actv_ports = mlx4_get_active_ports(dev, slave);
	max_port_p_one = find_first_bit(actv_ports.ports, dev->caps.num_ports) +
		biपंचांगap_weight(actv_ports.ports, dev->caps.num_ports) + 1;

	क्रम (i = 1; i < max_port_p_one; i++) अणु
		काष्ठा mlx4_active_ports exclusive_ports;
		काष्ठा mlx4_slaves_pport slaves_pport_actv;
		biपंचांगap_zero(exclusive_ports.ports, dev->caps.num_ports);
		set_bit(i - 1, exclusive_ports.ports);
		अगर (i == port)
			जारी;
		slaves_pport_actv = mlx4_phys_to_slaves_pport_actv(
				    dev, &exclusive_ports);
		slave_gid -= biपंचांगap_weight(slaves_pport_actv.slaves,
					   dev->persist->num_vfs + 1);
	पूर्ण
	gids = MLX4_ROCE_MAX_GIDS - MLX4_ROCE_PF_GIDS;
	vfs = biपंचांगap_weight(slaves_pport.slaves, dev->persist->num_vfs + 1) - 1;
	अगर (slave_gid <= gids % vfs)
		वापस MLX4_ROCE_PF_GIDS + ((gids / vfs) + 1) * (slave_gid - 1);

	वापस MLX4_ROCE_PF_GIDS + (gids % vfs) +
		((gids / vfs) * (slave_gid - 1));
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_get_base_gid_ix);

अटल पूर्णांक mlx4_reset_roce_port_gids(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				     पूर्णांक port, काष्ठा mlx4_cmd_mailbox *mailbox)
अणु
	काष्ठा mlx4_roce_gid_entry *gid_entry_mbox;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक num_gids, base, offset;
	पूर्णांक i, err;

	num_gids = mlx4_get_slave_num_gids(dev, slave, port);
	base = mlx4_get_base_gid_ix(dev, slave, port);

	स_रखो(mailbox->buf, 0, MLX4_MAILBOX_SIZE);

	mutex_lock(&(priv->port[port].gid_table.mutex));
	/* Zero-out gids beदीर्घing to that slave in the port GID table */
	क्रम (i = 0, offset = base; i < num_gids; offset++, i++)
		स_नकल(priv->port[port].gid_table.roce_gids[offset].raw,
		       zgid_entry.raw, MLX4_ROCE_GID_ENTRY_SIZE);

	/* Now, copy roce port gids table to mailbox क्रम passing to FW */
	gid_entry_mbox = (काष्ठा mlx4_roce_gid_entry *)mailbox->buf;
	क्रम (i = 0; i < MLX4_ROCE_MAX_GIDS; gid_entry_mbox++, i++)
		स_नकल(gid_entry_mbox->raw,
		       priv->port[port].gid_table.roce_gids[i].raw,
		       MLX4_ROCE_GID_ENTRY_SIZE);

	err = mlx4_cmd(dev, mailbox->dma,
		       ((u32)port) | (MLX4_SET_PORT_GID_TABLE << 8),
		       MLX4_SET_PORT_ETH_OPCODE, MLX4_CMD_SET_PORT,
		       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
	mutex_unlock(&(priv->port[port].gid_table.mutex));
	वापस err;
पूर्ण


व्योम mlx4_reset_roce_gids(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_active_ports actv_ports;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक num_eth_ports, err;
	पूर्णांक i;

	अगर (slave < 0 || slave > dev->persist->num_vfs)
		वापस;

	actv_ports = mlx4_get_active_ports(dev, slave);

	क्रम (i = 0, num_eth_ports = 0; i < dev->caps.num_ports; i++) अणु
		अगर (test_bit(i, actv_ports.ports)) अणु
			अगर (dev->caps.port_type[i + 1] != MLX4_PORT_TYPE_ETH)
				जारी;
			num_eth_ports++;
		पूर्ण
	पूर्ण

	अगर (!num_eth_ports)
		वापस;

	/* have ETH ports.  Alloc mailbox क्रम SET_PORT command */
	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस;

	क्रम (i = 0; i < dev->caps.num_ports; i++) अणु
		अगर (test_bit(i, actv_ports.ports)) अणु
			अगर (dev->caps.port_type[i + 1] != MLX4_PORT_TYPE_ETH)
				जारी;
			err = mlx4_reset_roce_port_gids(dev, slave, i + 1, mailbox);
			अगर (err)
				mlx4_warn(dev, "Could not reset ETH port GID table for slave %d, port %d (%d)\n",
					  slave, i + 1, err);
		पूर्ण
	पूर्ण

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस;
पूर्ण

अटल व्योम
mlx4_en_set_port_mtu(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port,
		     काष्ठा mlx4_set_port_general_context *gen_context)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_mfunc_master_ctx *master = &priv->mfunc.master;
	काष्ठा mlx4_slave_state *slave_st = &master->slave_state[slave];
	u16 mtu, prev_mtu;

	/* Mtu is configured as the max USER_MTU among all
	 * the functions on the port.
	 */
	mtu = be16_to_cpu(gen_context->mtu);
	mtu = min_t(पूर्णांक, mtu, dev->caps.eth_mtu_cap[port] +
		    ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN);
	prev_mtu = slave_st->mtu[port];
	slave_st->mtu[port] = mtu;
	अगर (mtu > master->max_mtu[port])
		master->max_mtu[port] = mtu;
	अगर (mtu < prev_mtu && prev_mtu == master->max_mtu[port]) अणु
		पूर्णांक i;

		slave_st->mtu[port] = mtu;
		master->max_mtu[port] = mtu;
		क्रम (i = 0; i < dev->num_slaves; i++)
			master->max_mtu[port] =
				max_t(u16, master->max_mtu[port],
				      master->slave_state[i].mtu[port]);
	पूर्ण
	gen_context->mtu = cpu_to_be16(master->max_mtu[port]);
पूर्ण

अटल व्योम
mlx4_en_set_port_user_mtu(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port,
			  काष्ठा mlx4_set_port_general_context *gen_context)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_mfunc_master_ctx *master = &priv->mfunc.master;
	काष्ठा mlx4_slave_state *slave_st = &master->slave_state[slave];
	u16 user_mtu, prev_user_mtu;

	/* User Mtu is configured as the max USER_MTU among all
	 * the functions on the port.
	 */
	user_mtu = be16_to_cpu(gen_context->user_mtu);
	user_mtu = min_t(पूर्णांक, user_mtu, dev->caps.eth_mtu_cap[port]);
	prev_user_mtu = slave_st->user_mtu[port];
	slave_st->user_mtu[port] = user_mtu;
	अगर (user_mtu > master->max_user_mtu[port])
		master->max_user_mtu[port] = user_mtu;
	अगर (user_mtu < prev_user_mtu &&
	    prev_user_mtu == master->max_user_mtu[port]) अणु
		पूर्णांक i;

		slave_st->user_mtu[port] = user_mtu;
		master->max_user_mtu[port] = user_mtu;
		क्रम (i = 0; i < dev->num_slaves; i++)
			master->max_user_mtu[port] =
				max_t(u16, master->max_user_mtu[port],
				      master->slave_state[i].user_mtu[port]);
	पूर्ण
	gen_context->user_mtu = cpu_to_be16(master->max_user_mtu[port]);
पूर्ण

अटल व्योम
mlx4_en_set_port_global_छोड़ो(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			      काष्ठा mlx4_set_port_general_context *gen_context)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_mfunc_master_ctx *master = &priv->mfunc.master;

	/* Slave cannot change Global Pause configuration */
	अगर (slave != mlx4_master_func_num(dev) &&
	    (gen_context->pptx != master->pptx ||
	     gen_context->pprx != master->pprx)) अणु
		gen_context->pptx = master->pptx;
		gen_context->pprx = master->pprx;
		mlx4_warn(dev, "denying Global Pause change for slave:%d\n",
			  slave);
	पूर्ण अन्यथा अणु
		master->pptx = gen_context->pptx;
		master->pprx = gen_context->pprx;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_common_set_port(काष्ठा mlx4_dev *dev, पूर्णांक slave, u32 in_mod,
				u8 op_mod, काष्ठा mlx4_cmd_mailbox *inbox)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_port_info *port_info;
	काष्ठा mlx4_set_port_rqp_calc_context *qpn_context;
	काष्ठा mlx4_set_port_general_context *gen_context;
	काष्ठा mlx4_roce_gid_entry *gid_entry_tbl, *gid_entry_mbox, *gid_entry_mb1;
	पूर्णांक reset_qkey_viols;
	पूर्णांक port;
	पूर्णांक is_eth;
	पूर्णांक num_gids;
	पूर्णांक base;
	u32 in_modअगरier;
	u32 promisc;
	पूर्णांक err;
	पूर्णांक i, j;
	पूर्णांक offset;
	__be32 agg_cap_mask;
	__be32 slave_cap_mask;
	__be32 new_cap_mask;

	port = in_mod & 0xff;
	in_modअगरier = in_mod >> 8;
	is_eth = op_mod;
	port_info = &priv->port[port];

	/* Slaves cannot perक्रमm SET_PORT operations,
	 * except क्रम changing MTU and USER_MTU.
	 */
	अगर (is_eth) अणु
		अगर (slave != dev->caps.function &&
		    in_modअगरier != MLX4_SET_PORT_GENERAL &&
		    in_modअगरier != MLX4_SET_PORT_GID_TABLE) अणु
			mlx4_warn(dev, "denying SET_PORT for slave:%d\n",
					slave);
			वापस -EINVAL;
		पूर्ण
		चयन (in_modअगरier) अणु
		हाल MLX4_SET_PORT_RQP_CALC:
			qpn_context = inbox->buf;
			qpn_context->base_qpn =
				cpu_to_be32(port_info->base_qpn);
			qpn_context->n_mac = 0x7;
			promisc = be32_to_cpu(qpn_context->promisc) >>
				SET_PORT_PROMISC_SHIFT;
			qpn_context->promisc = cpu_to_be32(
				promisc << SET_PORT_PROMISC_SHIFT |
				port_info->base_qpn);
			promisc = be32_to_cpu(qpn_context->mcast) >>
				SET_PORT_MC_PROMISC_SHIFT;
			qpn_context->mcast = cpu_to_be32(
				promisc << SET_PORT_MC_PROMISC_SHIFT |
				port_info->base_qpn);
			अवरोध;
		हाल MLX4_SET_PORT_GENERAL:
			gen_context = inbox->buf;

			अगर (gen_context->flags & MLX4_FLAG_V_MTU_MASK)
				mlx4_en_set_port_mtu(dev, slave, port,
						     gen_context);

			अगर (gen_context->flags2 & MLX4_FLAG2_V_USER_MTU_MASK)
				mlx4_en_set_port_user_mtu(dev, slave, port,
							  gen_context);

			अगर (gen_context->flags &
			    (MLX4_FLAG_V_PPRX_MASK | MLX4_FLAG_V_PPTX_MASK))
				mlx4_en_set_port_global_छोड़ो(dev, slave,
							      gen_context);

			अवरोध;
		हाल MLX4_SET_PORT_GID_TABLE:
			/* change to MULTIPLE entries: number of guest's gids
			 * need a FOR-loop here over number of gids the guest has.
			 * 1. Check no duplicates in gids passed by slave
			 */
			num_gids = mlx4_get_slave_num_gids(dev, slave, port);
			base = mlx4_get_base_gid_ix(dev, slave, port);
			gid_entry_mbox = (काष्ठा mlx4_roce_gid_entry *)(inbox->buf);
			क्रम (i = 0; i < num_gids; gid_entry_mbox++, i++) अणु
				अगर (!स_भेद(gid_entry_mbox->raw, zgid_entry.raw,
					    माप(zgid_entry)))
					जारी;
				gid_entry_mb1 = gid_entry_mbox + 1;
				क्रम (j = i + 1; j < num_gids; gid_entry_mb1++, j++) अणु
					अगर (!स_भेद(gid_entry_mb1->raw,
						    zgid_entry.raw, माप(zgid_entry)))
						जारी;
					अगर (!स_भेद(gid_entry_mb1->raw, gid_entry_mbox->raw,
						    माप(gid_entry_mbox->raw))) अणु
						/* found duplicate */
						वापस -EINVAL;
					पूर्ण
				पूर्ण
			पूर्ण

			/* 2. Check that करो not have duplicates in OTHER
			 *    entries in the port GID table
			 */

			mutex_lock(&(priv->port[port].gid_table.mutex));
			क्रम (i = 0; i < MLX4_ROCE_MAX_GIDS; i++) अणु
				अगर (i >= base && i < base + num_gids)
					जारी; /* करोn't compare to slave's current gids */
				gid_entry_tbl = &priv->port[port].gid_table.roce_gids[i];
				अगर (!स_भेद(gid_entry_tbl->raw, zgid_entry.raw, माप(zgid_entry)))
					जारी;
				gid_entry_mbox = (काष्ठा mlx4_roce_gid_entry *)(inbox->buf);
				क्रम (j = 0; j < num_gids; gid_entry_mbox++, j++) अणु
					अगर (!स_भेद(gid_entry_mbox->raw, zgid_entry.raw,
						    माप(zgid_entry)))
						जारी;
					अगर (!स_भेद(gid_entry_mbox->raw, gid_entry_tbl->raw,
						    माप(gid_entry_tbl->raw))) अणु
						/* found duplicate */
						mlx4_warn(dev, "requested gid entry for slave:%d is a duplicate of gid at index %d\n",
							  slave, i);
						mutex_unlock(&(priv->port[port].gid_table.mutex));
						वापस -EINVAL;
					पूर्ण
				पूर्ण
			पूर्ण

			/* insert slave GIDs with स_नकल, starting at slave's base index */
			gid_entry_mbox = (काष्ठा mlx4_roce_gid_entry *)(inbox->buf);
			क्रम (i = 0, offset = base; i < num_gids; gid_entry_mbox++, offset++, i++)
				स_नकल(priv->port[port].gid_table.roce_gids[offset].raw,
				       gid_entry_mbox->raw, MLX4_ROCE_GID_ENTRY_SIZE);

			/* Now, copy roce port gids table to current mailbox क्रम passing to FW */
			gid_entry_mbox = (काष्ठा mlx4_roce_gid_entry *)(inbox->buf);
			क्रम (i = 0; i < MLX4_ROCE_MAX_GIDS; gid_entry_mbox++, i++)
				स_नकल(gid_entry_mbox->raw,
				       priv->port[port].gid_table.roce_gids[i].raw,
				       MLX4_ROCE_GID_ENTRY_SIZE);

			err = mlx4_cmd(dev, inbox->dma, in_mod & 0xffff, op_mod,
				       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
				       MLX4_CMD_NATIVE);
			mutex_unlock(&(priv->port[port].gid_table.mutex));
			वापस err;
		पूर्ण

		वापस mlx4_cmd(dev, inbox->dma, in_mod & 0xffff, op_mod,
				MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
				MLX4_CMD_NATIVE);
	पूर्ण

	/* Slaves are not allowed to SET_PORT beacon (LED) blink */
	अगर (op_mod == MLX4_SET_PORT_BEACON_OPCODE) अणु
		mlx4_warn(dev, "denying SET_PORT Beacon slave:%d\n", slave);
		वापस -EPERM;
	पूर्ण

	/* For IB, we only consider:
	 * - The capability mask, which is set to the aggregate of all
	 *   slave function capabilities
	 * - The QKey violatin counter - reset according to each request.
	 */

	अगर (dev->flags & MLX4_FLAG_OLD_PORT_CMDS) अणु
		reset_qkey_viols = (*(u8 *) inbox->buf) & 0x40;
		new_cap_mask = ((__be32 *) inbox->buf)[2];
	पूर्ण अन्यथा अणु
		reset_qkey_viols = ((u8 *) inbox->buf)[3] & 0x1;
		new_cap_mask = ((__be32 *) inbox->buf)[1];
	पूर्ण

	/* slave may not set the IS_SM capability क्रम the port */
	अगर (slave != mlx4_master_func_num(dev) &&
	    (be32_to_cpu(new_cap_mask) & MLX4_PORT_CAP_IS_SM))
		वापस -EINVAL;

	/* No DEV_MGMT in multअगरunc mode */
	अगर (mlx4_is_mfunc(dev) &&
	    (be32_to_cpu(new_cap_mask) & MLX4_PORT_CAP_DEV_MGMT_SUP))
		वापस -EINVAL;

	agg_cap_mask = 0;
	slave_cap_mask =
		priv->mfunc.master.slave_state[slave].ib_cap_mask[port];
	priv->mfunc.master.slave_state[slave].ib_cap_mask[port] = new_cap_mask;
	क्रम (i = 0; i < dev->num_slaves; i++)
		agg_cap_mask |=
			priv->mfunc.master.slave_state[i].ib_cap_mask[port];

	/* only clear mailbox क्रम guests.  Master may be setting
	* MTU or PKEY table size
	*/
	अगर (slave != dev->caps.function)
		स_रखो(inbox->buf, 0, 256);
	अगर (dev->flags & MLX4_FLAG_OLD_PORT_CMDS) अणु
		*(u8 *) inbox->buf	   |= !!reset_qkey_viols << 6;
		((__be32 *) inbox->buf)[2] = agg_cap_mask;
	पूर्ण अन्यथा अणु
		((u8 *) inbox->buf)[3]     |= !!reset_qkey_viols;
		((__be32 *) inbox->buf)[1] = agg_cap_mask;
	पूर्ण

	err = mlx4_cmd(dev, inbox->dma, port, is_eth, MLX4_CMD_SET_PORT,
		       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);
	अगर (err)
		priv->mfunc.master.slave_state[slave].ib_cap_mask[port] =
			slave_cap_mask;
	वापस err;
पूर्ण

पूर्णांक mlx4_SET_PORT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक port = mlx4_slave_convert_port(
			dev, slave, vhcr->in_modअगरier & 0xFF);

	अगर (port < 0)
		वापस -EINVAL;

	vhcr->in_modअगरier = (vhcr->in_modअगरier & ~0xFF) |
			    (port & 0xFF);

	वापस mlx4_common_set_port(dev, slave, vhcr->in_modअगरier,
				    vhcr->op_modअगरier, inbox);
पूर्ण

/* bit locations क्रम set port command with zero op modअगरier */
क्रमागत अणु
	MLX4_SET_PORT_VL_CAP	 = 4, /* bits 7:4 */
	MLX4_SET_PORT_MTU_CAP	 = 12, /* bits 15:12 */
	MLX4_CHANGE_PORT_PKEY_TBL_SZ = 20,
	MLX4_CHANGE_PORT_VL_CAP	 = 21,
	MLX4_CHANGE_PORT_MTU_CAP = 22,
पूर्ण;

पूर्णांक mlx4_SET_PORT(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक pkey_tbl_sz)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err, vl_cap, pkey_tbl_flag = 0;

	अगर (dev->caps.port_type[port] == MLX4_PORT_TYPE_ETH)
		वापस 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	((__be32 *) mailbox->buf)[1] = dev->caps.ib_port_def_cap[port];

	अगर (pkey_tbl_sz >= 0 && mlx4_is_master(dev)) अणु
		pkey_tbl_flag = 1;
		((__be16 *) mailbox->buf)[20] = cpu_to_be16(pkey_tbl_sz);
	पूर्ण

	/* IB VL CAP क्रमागत isn't used by the firmware, just numerical values */
	क्रम (vl_cap = 8; vl_cap >= 1; vl_cap >>= 1) अणु
		((__be32 *) mailbox->buf)[0] = cpu_to_be32(
			(1 << MLX4_CHANGE_PORT_MTU_CAP) |
			(1 << MLX4_CHANGE_PORT_VL_CAP)  |
			(pkey_tbl_flag << MLX4_CHANGE_PORT_PKEY_TBL_SZ) |
			(dev->caps.port_ib_mtu[port] << MLX4_SET_PORT_MTU_CAP) |
			(vl_cap << MLX4_SET_PORT_VL_CAP));
		err = mlx4_cmd(dev, mailbox->dma, port,
			       MLX4_SET_PORT_IB_OPCODE, MLX4_CMD_SET_PORT,
			       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_WRAPPED);
		अगर (err != -ENOMEM)
			अवरोध;
	पूर्ण

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

#घोषणा SET_PORT_ROCE_2_FLAGS          0x10
#घोषणा MLX4_SET_PORT_ROCE_V1_V2       0x2
पूर्णांक mlx4_SET_PORT_general(काष्ठा mlx4_dev *dev, u8 port, पूर्णांक mtu,
			  u8 pptx, u8 pfctx, u8 pprx, u8 pfcrx)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_set_port_general_context *context;
	पूर्णांक err;
	u32 in_mod;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	context = mailbox->buf;
	context->flags = SET_PORT_GEN_ALL_VALID;
	context->mtu = cpu_to_be16(mtu);
	context->pptx = (pptx * (!pfctx)) << 7;
	context->pfctx = pfctx;
	context->pprx = (pprx * (!pfcrx)) << 7;
	context->pfcrx = pfcrx;

	अगर (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ROCE_V1_V2) अणु
		context->flags |= SET_PORT_ROCE_2_FLAGS;
		context->roce_mode |=
			MLX4_SET_PORT_ROCE_V1_V2 << 4;
	पूर्ण
	in_mod = MLX4_SET_PORT_GENERAL << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, MLX4_SET_PORT_ETH_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_WRAPPED);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_SET_PORT_general);

पूर्णांक mlx4_SET_PORT_qpn_calc(काष्ठा mlx4_dev *dev, u8 port, u32 base_qpn,
			   u8 promisc)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_set_port_rqp_calc_context *context;
	पूर्णांक err;
	u32 in_mod;
	u32 m_promisc = (dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_MC_STEER) ?
		MCAST_सूचीECT : MCAST_DEFAULT;

	अगर (dev->caps.steering_mode != MLX4_STEERING_MODE_A0)
		वापस 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	context = mailbox->buf;
	context->base_qpn = cpu_to_be32(base_qpn);
	context->n_mac = dev->caps.log_num_macs;
	context->promisc = cpu_to_be32(promisc << SET_PORT_PROMISC_SHIFT |
				       base_qpn);
	context->mcast = cpu_to_be32(m_promisc << SET_PORT_MC_PROMISC_SHIFT |
				     base_qpn);
	context->पूर्णांकra_no_vlan = 0;
	context->no_vlan = MLX4_NO_VLAN_IDX;
	context->पूर्णांकra_vlan_miss = 0;
	context->vlan_miss = MLX4_VLAN_MISS_IDX;

	in_mod = MLX4_SET_PORT_RQP_CALC << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, MLX4_SET_PORT_ETH_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_WRAPPED);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_SET_PORT_qpn_calc);

पूर्णांक mlx4_SET_PORT_user_mtu(काष्ठा mlx4_dev *dev, u8 port, u16 user_mtu)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_set_port_general_context *context;
	u32 in_mod;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	context = mailbox->buf;
	context->flags2 |= MLX4_FLAG2_V_USER_MTU_MASK;
	context->user_mtu = cpu_to_be16(user_mtu);

	in_mod = MLX4_SET_PORT_GENERAL << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, MLX4_SET_PORT_ETH_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_WRAPPED);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_SET_PORT_user_mtu);

पूर्णांक mlx4_SET_PORT_user_mac(काष्ठा mlx4_dev *dev, u8 port, u8 *user_mac)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_set_port_general_context *context;
	u32 in_mod;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	context = mailbox->buf;
	context->flags2 |= MLX4_FLAG2_V_USER_MAC_MASK;
	स_नकल(context->user_mac, user_mac, माप(context->user_mac));

	in_mod = MLX4_SET_PORT_GENERAL << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, MLX4_SET_PORT_ETH_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_SET_PORT_user_mac);

पूर्णांक mlx4_SET_PORT_fcs_check(काष्ठा mlx4_dev *dev, u8 port, u8 ignore_fcs_value)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_set_port_general_context *context;
	u32 in_mod;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	context = mailbox->buf;
	context->flags2 |= MLX4_FLAG2_V_IGNORE_FCS_MASK;
	अगर (ignore_fcs_value)
		context->ignore_fcs |= MLX4_IGNORE_FCS_MASK;
	अन्यथा
		context->ignore_fcs &= ~MLX4_IGNORE_FCS_MASK;

	in_mod = MLX4_SET_PORT_GENERAL << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, 1, MLX4_CMD_SET_PORT,
		       MLX4_CMD_TIME_CLASS_B, MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_SET_PORT_fcs_check);

क्रमागत अणु
	VXLAN_ENABLE_MODIFY	= 1 << 7,
	VXLAN_STEERING_MODIFY	= 1 << 6,

	VXLAN_ENABLE		= 1 << 7,
पूर्ण;

काष्ठा mlx4_set_port_vxlan_context अणु
	u32	reserved1;
	u8	modअगरy_flags;
	u8	reserved2;
	u8	enable_flags;
	u8	steering;
पूर्ण;

पूर्णांक mlx4_SET_PORT_VXLAN(काष्ठा mlx4_dev *dev, u8 port, u8 steering, पूर्णांक enable)
अणु
	पूर्णांक err;
	u32 in_mod;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_set_port_vxlan_context  *context;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	context = mailbox->buf;
	स_रखो(context, 0, माप(*context));

	context->modअगरy_flags = VXLAN_ENABLE_MODIFY | VXLAN_STEERING_MODIFY;
	अगर (enable)
		context->enable_flags = VXLAN_ENABLE;
	context->steering  = steering;

	in_mod = MLX4_SET_PORT_VXLAN << 8 | port;
	err = mlx4_cmd(dev, mailbox->dma, in_mod, MLX4_SET_PORT_ETH_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_SET_PORT_VXLAN);

पूर्णांक mlx4_SET_PORT_BEACON(काष्ठा mlx4_dev *dev, u8 port, u16 समय)
अणु
	पूर्णांक err;
	काष्ठा mlx4_cmd_mailbox *mailbox;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	*((__be32 *)mailbox->buf) = cpu_to_be32(समय);

	err = mlx4_cmd(dev, mailbox->dma, port, MLX4_SET_PORT_BEACON_OPCODE,
		       MLX4_CMD_SET_PORT, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_NATIVE);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_SET_PORT_BEACON);

पूर्णांक mlx4_SET_MCAST_FLTR_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				काष्ठा mlx4_vhcr *vhcr,
				काष्ठा mlx4_cmd_mailbox *inbox,
				काष्ठा mlx4_cmd_mailbox *outbox,
				काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err = 0;

	वापस err;
पूर्ण

पूर्णांक mlx4_SET_MCAST_FLTR(काष्ठा mlx4_dev *dev, u8 port,
			u64 mac, u64 clear, u8 mode)
अणु
	वापस mlx4_cmd(dev, (mac | (clear << 63)), port, mode,
			MLX4_CMD_SET_MCAST_FLTR, MLX4_CMD_TIME_CLASS_B,
			MLX4_CMD_WRAPPED);
पूर्ण
EXPORT_SYMBOL(mlx4_SET_MCAST_FLTR);

पूर्णांक mlx4_SET_VLAN_FLTR_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			       काष्ठा mlx4_vhcr *vhcr,
			       काष्ठा mlx4_cmd_mailbox *inbox,
			       काष्ठा mlx4_cmd_mailbox *outbox,
			       काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err = 0;

	वापस err;
पूर्ण

पूर्णांक mlx4_DUMP_ETH_STATS_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				काष्ठा mlx4_vhcr *vhcr,
				काष्ठा mlx4_cmd_mailbox *inbox,
				काष्ठा mlx4_cmd_mailbox *outbox,
				काष्ठा mlx4_cmd_info *cmd)
अणु
	वापस 0;
पूर्ण

पूर्णांक mlx4_get_slave_from_roce_gid(काष्ठा mlx4_dev *dev, पूर्णांक port, u8 *gid,
				 पूर्णांक *slave_id)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक i, found_ix = -1;
	पूर्णांक vf_gids = MLX4_ROCE_MAX_GIDS - MLX4_ROCE_PF_GIDS;
	काष्ठा mlx4_slaves_pport slaves_pport;
	अचिन्हित num_vfs;
	पूर्णांक slave_gid;

	अगर (!mlx4_is_mfunc(dev))
		वापस -EINVAL;

	slaves_pport = mlx4_phys_to_slaves_pport(dev, port);
	num_vfs = biपंचांगap_weight(slaves_pport.slaves,
				dev->persist->num_vfs + 1) - 1;

	क्रम (i = 0; i < MLX4_ROCE_MAX_GIDS; i++) अणु
		अगर (!स_भेद(priv->port[port].gid_table.roce_gids[i].raw, gid,
			    MLX4_ROCE_GID_ENTRY_SIZE)) अणु
			found_ix = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found_ix >= 0) अणु
		/* Calculate a slave_gid which is the slave number in the gid
		 * table and not a globally unique slave number.
		 */
		अगर (found_ix < MLX4_ROCE_PF_GIDS)
			slave_gid = 0;
		अन्यथा अगर (found_ix < MLX4_ROCE_PF_GIDS + (vf_gids % num_vfs) *
			 (vf_gids / num_vfs + 1))
			slave_gid = ((found_ix - MLX4_ROCE_PF_GIDS) /
				     (vf_gids / num_vfs + 1)) + 1;
		अन्यथा
			slave_gid =
			((found_ix - MLX4_ROCE_PF_GIDS -
			  ((vf_gids % num_vfs) * ((vf_gids / num_vfs + 1)))) /
			 (vf_gids / num_vfs)) + vf_gids % num_vfs + 1;

		/* Calculate the globally unique slave id */
		अगर (slave_gid) अणु
			काष्ठा mlx4_active_ports exclusive_ports;
			काष्ठा mlx4_active_ports actv_ports;
			काष्ठा mlx4_slaves_pport slaves_pport_actv;
			अचिन्हित max_port_p_one;
			पूर्णांक num_vfs_beक्रमe = 0;
			पूर्णांक candidate_slave_gid;

			/* Calculate how many VFs are on the previous port, अगर exists */
			क्रम (i = 1; i < port; i++) अणु
				biपंचांगap_zero(exclusive_ports.ports, dev->caps.num_ports);
				set_bit(i - 1, exclusive_ports.ports);
				slaves_pport_actv =
					mlx4_phys_to_slaves_pport_actv(
							dev, &exclusive_ports);
				num_vfs_beक्रमe += biपंचांगap_weight(
						slaves_pport_actv.slaves,
						dev->persist->num_vfs + 1);
			पूर्ण

			/* candidate_slave_gid isn't necessarily the correct slave, but
			 * it has the same number of ports and is asचिन्हित to the same
			 * ports as the real slave we're looking क्रम. On dual port VF,
			 * slave_gid = [single port VFs on port <port>] +
			 * [offset of the current slave from the first dual port VF] +
			 * 1 (क्रम the PF).
			 */
			candidate_slave_gid = slave_gid + num_vfs_beक्रमe;

			actv_ports = mlx4_get_active_ports(dev, candidate_slave_gid);
			max_port_p_one = find_first_bit(
				actv_ports.ports, dev->caps.num_ports) +
				biपंचांगap_weight(actv_ports.ports,
					      dev->caps.num_ports) + 1;

			/* Calculate the real slave number */
			क्रम (i = 1; i < max_port_p_one; i++) अणु
				अगर (i == port)
					जारी;
				biपंचांगap_zero(exclusive_ports.ports,
					    dev->caps.num_ports);
				set_bit(i - 1, exclusive_ports.ports);
				slaves_pport_actv =
					mlx4_phys_to_slaves_pport_actv(
						dev, &exclusive_ports);
				slave_gid += biपंचांगap_weight(
						slaves_pport_actv.slaves,
						dev->persist->num_vfs + 1);
			पूर्ण
		पूर्ण
		*slave_id = slave_gid;
	पूर्ण

	वापस (found_ix >= 0) ? 0 : -EINVAL;
पूर्ण
EXPORT_SYMBOL(mlx4_get_slave_from_roce_gid);

पूर्णांक mlx4_get_roce_gid_from_slave(काष्ठा mlx4_dev *dev, पूर्णांक port, पूर्णांक slave_id,
				 u8 *gid)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (!mlx4_is_master(dev))
		वापस -EINVAL;

	स_नकल(gid, priv->port[port].gid_table.roce_gids[slave_id].raw,
	       MLX4_ROCE_GID_ENTRY_SIZE);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlx4_get_roce_gid_from_slave);

/* Cable Module Info */
#घोषणा MODULE_INFO_MAX_READ 48

#घोषणा I2C_ADDR_LOW  0x50
#घोषणा I2C_ADDR_HIGH 0x51
#घोषणा I2C_PAGE_SIZE 256
#घोषणा I2C_HIGH_PAGE_SIZE 128

/* Module Info Data */
काष्ठा mlx4_cable_info अणु
	u8	i2c_addr;
	u8	page_num;
	__be16	dev_mem_address;
	__be16	reserved1;
	__be16	size;
	__be32	reserved2[2];
	u8	data[MODULE_INFO_MAX_READ];
पूर्ण;

क्रमागत cable_info_err अणु
	 CABLE_INF_INV_PORT      = 0x1,
	 CABLE_INF_OP_NOSUP      = 0x2,
	 CABLE_INF_NOT_CONN      = 0x3,
	 CABLE_INF_NO_EEPRM      = 0x4,
	 CABLE_INF_PAGE_ERR      = 0x5,
	 CABLE_INF_INV_ADDR      = 0x6,
	 CABLE_INF_I2C_ADDR      = 0x7,
	 CABLE_INF_QSFP_VIO      = 0x8,
	 CABLE_INF_I2C_BUSY      = 0x9,
पूर्ण;

#घोषणा MAD_STATUS_2_CABLE_ERR(mad_status) ((mad_status >> 8) & 0xFF)

अटल अंतरभूत स्थिर अक्षर *cable_info_mad_err_str(u16 mad_status)
अणु
	u8 err = MAD_STATUS_2_CABLE_ERR(mad_status);

	चयन (err) अणु
	हाल CABLE_INF_INV_PORT:
		वापस "invalid port selected";
	हाल CABLE_INF_OP_NOSUP:
		वापस "operation not supported for this port (the port is of type CX4 or internal)";
	हाल CABLE_INF_NOT_CONN:
		वापस "cable is not connected";
	हाल CABLE_INF_NO_EEPRM:
		वापस "the connected cable has no EPROM (passive copper cable)";
	हाल CABLE_INF_PAGE_ERR:
		वापस "page number is greater than 15";
	हाल CABLE_INF_INV_ADDR:
		वापस "invalid device_address or size (that is, size equals 0 or address+size is greater than 256)";
	हाल CABLE_INF_I2C_ADDR:
		वापस "invalid I2C slave address";
	हाल CABLE_INF_QSFP_VIO:
		वापस "at least one cable violates the QSFP specification and ignores the modsel signal";
	हाल CABLE_INF_I2C_BUSY:
		वापस "I2C bus is constantly busy";
	पूर्ण
	वापस "Unknown Error";
पूर्ण

अटल पूर्णांक mlx4_get_module_id(काष्ठा mlx4_dev *dev, u8 port, u8 *module_id)
अणु
	काष्ठा mlx4_cmd_mailbox *inbox, *outbox;
	काष्ठा mlx4_mad_अगरc *inmad, *ouपंचांगad;
	काष्ठा mlx4_cable_info *cable_info;
	पूर्णांक ret;

	inbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(inbox))
		वापस PTR_ERR(inbox);

	outbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(outbox)) अणु
		mlx4_मुक्त_cmd_mailbox(dev, inbox);
		वापस PTR_ERR(outbox);
	पूर्ण

	inmad = (काष्ठा mlx4_mad_अगरc *)(inbox->buf);
	ouपंचांगad = (काष्ठा mlx4_mad_अगरc *)(outbox->buf);

	inmad->method = 0x1; /* Get */
	inmad->class_version = 0x1;
	inmad->mgmt_class = 0x1;
	inmad->base_version = 0x1;
	inmad->attr_id = cpu_to_be16(0xFF60); /* Module Info */

	cable_info = (काष्ठा mlx4_cable_info *)inmad->data;
	cable_info->dev_mem_address = 0;
	cable_info->page_num = 0;
	cable_info->i2c_addr = I2C_ADDR_LOW;
	cable_info->size = cpu_to_be16(1);

	ret = mlx4_cmd_box(dev, inbox->dma, outbox->dma, port, 3,
			   MLX4_CMD_MAD_IFC, MLX4_CMD_TIME_CLASS_C,
			   MLX4_CMD_NATIVE);
	अगर (ret)
		जाओ out;

	अगर (be16_to_cpu(ouपंचांगad->status)) अणु
		/* Mad वापसed with bad status */
		ret = be16_to_cpu(ouपंचांगad->status);
		mlx4_warn(dev,
			  "MLX4_CMD_MAD_IFC Get Module ID attr(%x) port(%d) i2c_addr(%x) offset(%d) size(%d): Response Mad Status(%x) - %s\n",
			  0xFF60, port, I2C_ADDR_LOW, 0, 1, ret,
			  cable_info_mad_err_str(ret));
		ret = -ret;
		जाओ out;
	पूर्ण
	cable_info = (काष्ठा mlx4_cable_info *)ouपंचांगad->data;
	*module_id = cable_info->data[0];
out:
	mlx4_मुक्त_cmd_mailbox(dev, inbox);
	mlx4_मुक्त_cmd_mailbox(dev, outbox);
	वापस ret;
पूर्ण

अटल व्योम mlx4_sfp_eeprom_params_set(u8 *i2c_addr, u8 *page_num, u16 *offset)
अणु
	*i2c_addr = I2C_ADDR_LOW;
	*page_num = 0;

	अगर (*offset < I2C_PAGE_SIZE)
		वापस;

	*i2c_addr = I2C_ADDR_HIGH;
	*offset -= I2C_PAGE_SIZE;
पूर्ण

अटल व्योम mlx4_qsfp_eeprom_params_set(u8 *i2c_addr, u8 *page_num, u16 *offset)
अणु
	/* Offsets 0-255 beदीर्घ to page 0.
	 * Offsets 256-639 beदीर्घ to pages 01, 02, 03.
	 * For example, offset 400 is page 02: 1 + (400 - 256) / 128 = 2
	 */
	अगर (*offset < I2C_PAGE_SIZE)
		*page_num = 0;
	अन्यथा
		*page_num = 1 + (*offset - I2C_PAGE_SIZE) / I2C_HIGH_PAGE_SIZE;
	*i2c_addr = I2C_ADDR_LOW;
	*offset -= *page_num * I2C_HIGH_PAGE_SIZE;
पूर्ण

/**
 * mlx4_get_module_info - Read cable module eeprom data
 * @dev: mlx4_dev.
 * @port: port number.
 * @offset: byte offset in eeprom to start पढ़ोing data from.
 * @size: num of bytes to पढ़ो.
 * @data: output buffer to put the requested data पूर्णांकo.
 *
 * Reads cable module eeprom data, माला_दो the outcome data पूर्णांकo
 * data poपूर्णांकer paramer.
 * Returns num of पढ़ो bytes on success or a negative error
 * code.
 */
पूर्णांक mlx4_get_module_info(काष्ठा mlx4_dev *dev, u8 port,
			 u16 offset, u16 size, u8 *data)
अणु
	काष्ठा mlx4_cmd_mailbox *inbox, *outbox;
	काष्ठा mlx4_mad_अगरc *inmad, *ouपंचांगad;
	काष्ठा mlx4_cable_info *cable_info;
	u8 module_id, i2c_addr, page_num;
	पूर्णांक ret;

	अगर (size > MODULE_INFO_MAX_READ)
		size = MODULE_INFO_MAX_READ;

	ret = mlx4_get_module_id(dev, port, &module_id);
	अगर (ret)
		वापस ret;

	चयन (module_id) अणु
	हाल MLX4_MODULE_ID_SFP:
		mlx4_sfp_eeprom_params_set(&i2c_addr, &page_num, &offset);
		अवरोध;
	हाल MLX4_MODULE_ID_QSFP:
	हाल MLX4_MODULE_ID_QSFP_PLUS:
	हाल MLX4_MODULE_ID_QSFP28:
		mlx4_qsfp_eeprom_params_set(&i2c_addr, &page_num, &offset);
		अवरोध;
	शेष:
		mlx4_err(dev, "Module ID not recognized: %#x\n", module_id);
		वापस -EINVAL;
	पूर्ण

	inbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(inbox))
		वापस PTR_ERR(inbox);

	outbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(outbox)) अणु
		mlx4_मुक्त_cmd_mailbox(dev, inbox);
		वापस PTR_ERR(outbox);
	पूर्ण

	inmad = (काष्ठा mlx4_mad_अगरc *)(inbox->buf);
	ouपंचांगad = (काष्ठा mlx4_mad_अगरc *)(outbox->buf);

	inmad->method = 0x1; /* Get */
	inmad->class_version = 0x1;
	inmad->mgmt_class = 0x1;
	inmad->base_version = 0x1;
	inmad->attr_id = cpu_to_be16(0xFF60); /* Module Info */

	अगर (offset < I2C_PAGE_SIZE && offset + size > I2C_PAGE_SIZE)
		/* Cross pages पढ़ोs are not allowed
		 * पढ़ो until offset 256 in low page
		 */
		size -= offset + size - I2C_PAGE_SIZE;

	cable_info = (काष्ठा mlx4_cable_info *)inmad->data;
	cable_info->dev_mem_address = cpu_to_be16(offset);
	cable_info->page_num = page_num;
	cable_info->i2c_addr = i2c_addr;
	cable_info->size = cpu_to_be16(size);

	ret = mlx4_cmd_box(dev, inbox->dma, outbox->dma, port, 3,
			   MLX4_CMD_MAD_IFC, MLX4_CMD_TIME_CLASS_C,
			   MLX4_CMD_NATIVE);
	अगर (ret)
		जाओ out;

	अगर (be16_to_cpu(ouपंचांगad->status)) अणु
		/* Mad वापसed with bad status */
		ret = be16_to_cpu(ouपंचांगad->status);
		mlx4_warn(dev,
			  "MLX4_CMD_MAD_IFC Get Module info attr(%x) port(%d) i2c_addr(%x) offset(%d) size(%d): Response Mad Status(%x) - %s\n",
			  0xFF60, port, i2c_addr, offset, size,
			  ret, cable_info_mad_err_str(ret));

		अगर (i2c_addr == I2C_ADDR_HIGH &&
		    MAD_STATUS_2_CABLE_ERR(ret) == CABLE_INF_I2C_ADDR)
			/* Some SFP cables करो not support i2c slave
			 * address 0x51 (high page), पात silently.
			 */
			ret = 0;
		अन्यथा
			ret = -ret;
		जाओ out;
	पूर्ण
	cable_info = (काष्ठा mlx4_cable_info *)ouपंचांगad->data;
	स_नकल(data, cable_info->data, size);
	ret = size;
out:
	mlx4_मुक्त_cmd_mailbox(dev, inbox);
	mlx4_मुक्त_cmd_mailbox(dev, outbox);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mlx4_get_module_info);

पूर्णांक mlx4_max_tc(काष्ठा mlx4_dev *dev)
अणु
	u8 num_tc = dev->caps.max_tc_eth;

	अगर (!num_tc)
		num_tc = MLX4_TC_MAX_NUMBER;

	वापस num_tc;
पूर्ण
EXPORT_SYMBOL(mlx4_max_tc);
