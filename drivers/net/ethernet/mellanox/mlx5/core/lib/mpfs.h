<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies, Ltd.  All rights reserved.
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

#अगर_अघोषित __MLX5_MPFS_H__
#घोषणा __MLX5_MPFS_H__

#समावेश <linux/अगर_ether.h>
#समावेश <linux/mlx5/device.h>

/* L2 -mac address based- hash helpers */
#घोषणा MLX5_L2_ADDR_HASH_SIZE (BIT(BITS_PER_BYTE))
#घोषणा MLX5_L2_ADDR_HASH(addr) (addr[5])

काष्ठा l2addr_node अणु
	काष्ठा hlist_node hlist;
	u8                addr[ETH_ALEN];
पूर्ण;

#घोषणा क्रम_each_l2hash_node(hn, पंचांगp, hash, i) \
	क्रम (i = 0; i < MLX5_L2_ADDR_HASH_SIZE; i++) \
		hlist_क्रम_each_entry_safe(hn, पंचांगp, &(hash)[i], hlist)

#घोषणा l2addr_hash_find(hash, mac, type) (अणु                \
	पूर्णांक ix = MLX5_L2_ADDR_HASH(mac);                    \
	bool found = false;                                 \
	type *ptr = शून्य;                                   \
							    \
	hlist_क्रम_each_entry(ptr, &(hash)[ix], node.hlist)  \
		अगर (ether_addr_equal(ptr->node.addr, mac)) अणु\
			found = true;                       \
			अवरोध;                              \
		पूर्ण                                           \
	अगर (!found)                                         \
		ptr = शून्य;                                 \
	ptr;                                                \
पूर्ण)

#घोषणा l2addr_hash_add(hash, mac, type, gfp) (अणु            \
	पूर्णांक ix = MLX5_L2_ADDR_HASH(mac);                    \
	type *ptr = शून्य;                                   \
							    \
	ptr = kzalloc(माप(type), gfp);                   \
	अगर (ptr) अणु                                          \
		ether_addr_copy(ptr->node.addr, mac);       \
		hlist_add_head(&ptr->node.hlist, &(hash)[ix]);\
	पूर्ण                                                   \
	ptr;                                                \
पूर्ण)

#घोषणा l2addr_hash_del(ptr) (अणु                             \
	hlist_del(&(ptr)->node.hlist);                      \
	kमुक्त(ptr);                                         \
पूर्ण)

#अगर_घोषित CONFIG_MLX5_MPFS
पूर्णांक  mlx5_mpfs_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_mpfs_cleanup(काष्ठा mlx5_core_dev *dev);
#अन्यथा /* #अगर_अघोषित CONFIG_MLX5_MPFS */
अटल अंतरभूत पूर्णांक  mlx5_mpfs_init(काष्ठा mlx5_core_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5_mpfs_cleanup(काष्ठा mlx5_core_dev *dev) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
