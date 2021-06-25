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

#समावेश <linux/etherdevice.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/mlx5_अगरc.h>
#समावेश <linux/mlx5/mpfs.h>
#समावेश <linux/mlx5/eचयन.h>
#समावेश "mlx5_core.h"
#समावेश "lib/mpfs.h"

/* HW L2 Table (MPFS) management */
अटल पूर्णांक set_l2table_entry_cmd(काष्ठा mlx5_core_dev *dev, u32 index, u8 *mac)
अणु
	u32 in[MLX5_ST_SZ_DW(set_l2_table_entry_in)] = अणुपूर्ण;
	u8 *in_mac_addr;

	MLX5_SET(set_l2_table_entry_in, in, opcode, MLX5_CMD_OP_SET_L2_TABLE_ENTRY);
	MLX5_SET(set_l2_table_entry_in, in, table_index, index);

	in_mac_addr = MLX5_ADDR_OF(set_l2_table_entry_in, in, mac_address);
	ether_addr_copy(&in_mac_addr[2], mac);

	वापस mlx5_cmd_exec_in(dev, set_l2_table_entry, in);
पूर्ण

अटल पूर्णांक del_l2table_entry_cmd(काष्ठा mlx5_core_dev *dev, u32 index)
अणु
	u32 in[MLX5_ST_SZ_DW(delete_l2_table_entry_in)] = अणुपूर्ण;

	MLX5_SET(delete_l2_table_entry_in, in, opcode, MLX5_CMD_OP_DELETE_L2_TABLE_ENTRY);
	MLX5_SET(delete_l2_table_entry_in, in, table_index, index);
	वापस mlx5_cmd_exec_in(dev, delete_l2_table_entry, in);
पूर्ण

/* UC L2 table hash node */
काष्ठा l2table_node अणु
	काष्ठा l2addr_node node;
	u32                index; /* index in HW l2 table */
	पूर्णांक                ref_count;
पूर्ण;

काष्ठा mlx5_mpfs अणु
	काष्ठा hlist_head    hash[MLX5_L2_ADDR_HASH_SIZE];
	काष्ठा mutex         lock; /* Synchronize l2 table access */
	u32                  size;
	अचिन्हित दीर्घ        *biपंचांगap;
पूर्ण;

अटल पूर्णांक alloc_l2table_index(काष्ठा mlx5_mpfs *l2table, u32 *ix)
अणु
	पूर्णांक err = 0;

	*ix = find_first_zero_bit(l2table->biपंचांगap, l2table->size);
	अगर (*ix >= l2table->size)
		err = -ENOSPC;
	अन्यथा
		__set_bit(*ix, l2table->biपंचांगap);

	वापस err;
पूर्ण

अटल व्योम मुक्त_l2table_index(काष्ठा mlx5_mpfs *l2table, u32 ix)
अणु
	__clear_bit(ix, l2table->biपंचांगap);
पूर्ण

पूर्णांक mlx5_mpfs_init(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक l2table_size = 1 << MLX5_CAP_GEN(dev, log_max_l2_table);
	काष्ठा mlx5_mpfs *mpfs;

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		वापस 0;

	mpfs = kzalloc(माप(*mpfs), GFP_KERNEL);
	अगर (!mpfs)
		वापस -ENOMEM;

	mutex_init(&mpfs->lock);
	mpfs->size   = l2table_size;
	mpfs->biपंचांगap = biपंचांगap_zalloc(l2table_size, GFP_KERNEL);
	अगर (!mpfs->biपंचांगap) अणु
		kमुक्त(mpfs);
		वापस -ENOMEM;
	पूर्ण

	dev->priv.mpfs = mpfs;
	वापस 0;
पूर्ण

व्योम mlx5_mpfs_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_mpfs *mpfs = dev->priv.mpfs;

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		वापस;

	WARN_ON(!hlist_empty(mpfs->hash));
	biपंचांगap_मुक्त(mpfs->biपंचांगap);
	kमुक्त(mpfs);
पूर्ण

पूर्णांक mlx5_mpfs_add_mac(काष्ठा mlx5_core_dev *dev, u8 *mac)
अणु
	काष्ठा mlx5_mpfs *mpfs = dev->priv.mpfs;
	काष्ठा l2table_node *l2addr;
	पूर्णांक err = 0;
	u32 index;

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		वापस 0;

	mutex_lock(&mpfs->lock);

	l2addr = l2addr_hash_find(mpfs->hash, mac, काष्ठा l2table_node);
	अगर (l2addr) अणु
		l2addr->ref_count++;
		जाओ out;
	पूर्ण

	err = alloc_l2table_index(mpfs, &index);
	अगर (err)
		जाओ out;

	l2addr = l2addr_hash_add(mpfs->hash, mac, काष्ठा l2table_node, GFP_KERNEL);
	अगर (!l2addr) अणु
		err = -ENOMEM;
		जाओ hash_add_err;
	पूर्ण

	err = set_l2table_entry_cmd(dev, index, mac);
	अगर (err)
		जाओ set_table_entry_err;

	l2addr->index = index;
	l2addr->ref_count = 1;

	mlx5_core_dbg(dev, "MPFS mac added %pM, index (%d)\n", mac, index);
	जाओ out;

set_table_entry_err:
	l2addr_hash_del(l2addr);
hash_add_err:
	मुक्त_l2table_index(mpfs, index);
out:
	mutex_unlock(&mpfs->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_mpfs_add_mac);

पूर्णांक mlx5_mpfs_del_mac(काष्ठा mlx5_core_dev *dev, u8 *mac)
अणु
	काष्ठा mlx5_mpfs *mpfs = dev->priv.mpfs;
	काष्ठा l2table_node *l2addr;
	पूर्णांक err = 0;
	u32 index;

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		वापस 0;

	mutex_lock(&mpfs->lock);

	l2addr = l2addr_hash_find(mpfs->hash, mac, काष्ठा l2table_node);
	अगर (!l2addr) अणु
		err = -ENOENT;
		जाओ unlock;
	पूर्ण

	अगर (--l2addr->ref_count > 0)
		जाओ unlock;

	index = l2addr->index;
	del_l2table_entry_cmd(dev, index);
	l2addr_hash_del(l2addr);
	मुक्त_l2table_index(mpfs, index);
	mlx5_core_dbg(dev, "MPFS mac deleted %pM, index (%d)\n", mac, index);
unlock:
	mutex_unlock(&mpfs->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_mpfs_del_mac);
