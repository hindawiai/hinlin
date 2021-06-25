<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/idr.h>
#समावेश "mlx5_core.h"
#समावेश "lib/mlx5.h"

व्योम mlx5_init_reserved_gids(काष्ठा mlx5_core_dev *dev)
अणु
	अचिन्हित पूर्णांक tblsz = MLX5_CAP_ROCE(dev, roce_address_table_size);

	ida_init(&dev->roce.reserved_gids.ida);
	dev->roce.reserved_gids.start = tblsz;
	dev->roce.reserved_gids.count = 0;
पूर्ण

व्योम mlx5_cleanup_reserved_gids(काष्ठा mlx5_core_dev *dev)
अणु
	WARN_ON(!ida_is_empty(&dev->roce.reserved_gids.ida));
	dev->roce.reserved_gids.start = 0;
	dev->roce.reserved_gids.count = 0;
	ida_destroy(&dev->roce.reserved_gids.ida);
पूर्ण

पूर्णांक mlx5_core_reserve_gids(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक count)
अणु
	अगर (dev->roce.reserved_gids.start < count) अणु
		mlx5_core_warn(dev, "GID table exhausted attempting to reserve %d more GIDs\n",
			       count);
		वापस -ENOMEM;
	पूर्ण
	अगर (dev->roce.reserved_gids.count + count > MLX5_MAX_RESERVED_GIDS) अणु
		mlx5_core_warn(dev, "Unable to reserve %d more GIDs\n", count);
		वापस -ENOMEM;
	पूर्ण

	dev->roce.reserved_gids.start -= count;
	dev->roce.reserved_gids.count += count;
	mlx5_core_dbg(dev, "Reserved %u GIDs starting at %u\n",
		      dev->roce.reserved_gids.count,
		      dev->roce.reserved_gids.start);
	वापस 0;
पूर्ण

व्योम mlx5_core_unreserve_gids(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक count)
अणु
	WARN(count > dev->roce.reserved_gids.count, "Unreserving %u GIDs when only %u reserved",
	     count, dev->roce.reserved_gids.count);

	dev->roce.reserved_gids.start += count;
	dev->roce.reserved_gids.count -= count;
	mlx5_core_dbg(dev, "%u GIDs starting at %u left reserved\n",
		      dev->roce.reserved_gids.count,
		      dev->roce.reserved_gids.start);
पूर्ण

पूर्णांक mlx5_core_reserved_gid_alloc(काष्ठा mlx5_core_dev *dev, पूर्णांक *gid_index)
अणु
	पूर्णांक end = dev->roce.reserved_gids.start +
		  dev->roce.reserved_gids.count - 1;
	पूर्णांक index = 0;

	index = ida_alloc_range(&dev->roce.reserved_gids.ida,
				dev->roce.reserved_gids.start, end,
				GFP_KERNEL);
	अगर (index < 0)
		वापस index;

	mlx5_core_dbg(dev, "Allocating reserved GID %u\n", index);
	*gid_index = index;
	वापस 0;
पूर्ण

व्योम mlx5_core_reserved_gid_मुक्त(काष्ठा mlx5_core_dev *dev, पूर्णांक gid_index)
अणु
	mlx5_core_dbg(dev, "Freeing reserved GID %u\n", gid_index);
	ida_मुक्त(&dev->roce.reserved_gids.ida, gid_index);
पूर्ण

अचिन्हित पूर्णांक mlx5_core_reserved_gids_count(काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->roce.reserved_gids.count;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_core_reserved_gids_count);

पूर्णांक mlx5_core_roce_gid_set(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक index,
			   u8 roce_version, u8 roce_l3_type, स्थिर u8 *gid,
			   स्थिर u8 *mac, bool vlan, u16 vlan_id, u8 port_num)
अणु
#घोषणा MLX5_SET_RA(p, f, v) MLX5_SET(roce_addr_layout, p, f, v)
	u32 in[MLX5_ST_SZ_DW(set_roce_address_in)] = अणुपूर्ण;
	व्योम *in_addr = MLX5_ADDR_OF(set_roce_address_in, in, roce_address);
	अक्षर *addr_l3_addr = MLX5_ADDR_OF(roce_addr_layout, in_addr,
					  source_l3_address);
	व्योम *addr_mac = MLX5_ADDR_OF(roce_addr_layout, in_addr,
				      source_mac_47_32);
	पूर्णांक gidsz = MLX5_FLD_SZ_BYTES(roce_addr_layout, source_l3_address);

	अगर (MLX5_CAP_GEN(dev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		वापस -EINVAL;

	अगर (gid) अणु
		अगर (vlan) अणु
			MLX5_SET_RA(in_addr, vlan_valid, 1);
			MLX5_SET_RA(in_addr, vlan_id, vlan_id);
		पूर्ण

		ether_addr_copy(addr_mac, mac);
		स_नकल(addr_l3_addr, gid, gidsz);
	पूर्ण
	MLX5_SET_RA(in_addr, roce_version, roce_version);
	MLX5_SET_RA(in_addr, roce_l3_type, roce_l3_type);

	अगर (MLX5_CAP_GEN(dev, num_vhca_ports) > 0)
		MLX5_SET(set_roce_address_in, in, vhca_port_num, port_num);

	MLX5_SET(set_roce_address_in, in, roce_address_index, index);
	MLX5_SET(set_roce_address_in, in, opcode, MLX5_CMD_OP_SET_ROCE_ADDRESS);
	वापस mlx5_cmd_exec_in(dev, set_roce_address, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_roce_gid_set);
