<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies, Ltd.  All rights reserved.
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

#अगर_अघोषित __MLX5_VPORT_H__
#घोषणा __MLX5_VPORT_H__

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/device.h>

#घोषणा MLX5_VPORT_MANAGER(mdev)					\
	(MLX5_CAP_GEN(mdev, vport_group_manager) &&			\
	 (MLX5_CAP_GEN(mdev, port_type) == MLX5_CAP_PORT_TYPE_ETH) &&	\
	 mlx5_core_is_pf(mdev))

क्रमागत अणु
	MLX5_CAP_INLINE_MODE_L2,
	MLX5_CAP_INLINE_MODE_VPORT_CONTEXT,
	MLX5_CAP_INLINE_MODE_NOT_REQUIRED,
पूर्ण;

/* Vport number क्रम each function must keep unchanged */
क्रमागत अणु
	MLX5_VPORT_PF			= 0x0,
	MLX5_VPORT_FIRST_VF		= 0x1,
	MLX5_VPORT_ECPF			= 0xfffe,
	MLX5_VPORT_UPLINK		= 0xffff
पूर्ण;

u8 mlx5_query_vport_state(काष्ठा mlx5_core_dev *mdev, u8 opmod, u16 vport);
पूर्णांक mlx5_modअगरy_vport_admin_state(काष्ठा mlx5_core_dev *mdev, u8 opmod,
				  u16 vport, u8 other_vport, u8 state);
पूर्णांक mlx5_query_nic_vport_mac_address(काष्ठा mlx5_core_dev *mdev,
				     u16 vport, bool other, u8 *addr);
पूर्णांक mlx5_query_mac_address(काष्ठा mlx5_core_dev *mdev, u8 *addr);
पूर्णांक mlx5_query_nic_vport_min_अंतरभूत(काष्ठा mlx5_core_dev *mdev,
				    u16 vport, u8 *min_अंतरभूत);
व्योम mlx5_query_min_अंतरभूत(काष्ठा mlx5_core_dev *mdev, u8 *min_अंतरभूत);
पूर्णांक mlx5_modअगरy_nic_vport_min_अंतरभूत(काष्ठा mlx5_core_dev *mdev,
				     u16 vport, u8 min_अंतरभूत);
पूर्णांक mlx5_modअगरy_nic_vport_mac_address(काष्ठा mlx5_core_dev *dev,
				      u16 vport, स्थिर u8 *addr);
पूर्णांक mlx5_query_nic_vport_mtu(काष्ठा mlx5_core_dev *mdev, u16 *mtu);
पूर्णांक mlx5_modअगरy_nic_vport_mtu(काष्ठा mlx5_core_dev *mdev, u16 mtu);
पूर्णांक mlx5_query_nic_vport_प्रणाली_image_guid(काष्ठा mlx5_core_dev *mdev,
					   u64 *प्रणाली_image_guid);
पूर्णांक mlx5_query_nic_vport_node_guid(काष्ठा mlx5_core_dev *mdev, u64 *node_guid);
पूर्णांक mlx5_modअगरy_nic_vport_node_guid(काष्ठा mlx5_core_dev *mdev,
				    u16 vport, u64 node_guid);
पूर्णांक mlx5_query_nic_vport_qkey_viol_cntr(काष्ठा mlx5_core_dev *mdev,
					u16 *qkey_viol_cntr);
पूर्णांक mlx5_query_hca_vport_gid(काष्ठा mlx5_core_dev *dev, u8 other_vport,
			     u8 port_num, u16  vf_num, u16 gid_index,
			     जोड़ ib_gid *gid);
पूर्णांक mlx5_query_hca_vport_pkey(काष्ठा mlx5_core_dev *dev, u8 other_vport,
			      u8 port_num, u16 vf_num, u16 pkey_index,
			      u16 *pkey);
पूर्णांक mlx5_query_hca_vport_context(काष्ठा mlx5_core_dev *dev,
				 u8 other_vport, u8 port_num,
				 u16 vf_num,
				 काष्ठा mlx5_hca_vport_context *rep);
पूर्णांक mlx5_query_hca_vport_प्रणाली_image_guid(काष्ठा mlx5_core_dev *dev,
					   u64 *sys_image_guid);
पूर्णांक mlx5_query_hca_vport_node_guid(काष्ठा mlx5_core_dev *dev,
				   u64 *node_guid);
पूर्णांक mlx5_query_nic_vport_mac_list(काष्ठा mlx5_core_dev *dev,
				  u16 vport,
				  क्रमागत mlx5_list_type list_type,
				  u8 addr_list[][ETH_ALEN],
				  पूर्णांक *list_size);
पूर्णांक mlx5_modअगरy_nic_vport_mac_list(काष्ठा mlx5_core_dev *dev,
				   क्रमागत mlx5_list_type list_type,
				   u8 addr_list[][ETH_ALEN],
				   पूर्णांक list_size);
पूर्णांक mlx5_query_nic_vport_promisc(काष्ठा mlx5_core_dev *mdev,
				 u16 vport,
				 पूर्णांक *promisc_uc,
				 पूर्णांक *promisc_mc,
				 पूर्णांक *promisc_all);
पूर्णांक mlx5_modअगरy_nic_vport_promisc(काष्ठा mlx5_core_dev *mdev,
				  पूर्णांक promisc_uc,
				  पूर्णांक promisc_mc,
				  पूर्णांक promisc_all);
पूर्णांक mlx5_modअगरy_nic_vport_vlans(काष्ठा mlx5_core_dev *dev,
				u16 vlans[],
				पूर्णांक list_size);

पूर्णांक mlx5_nic_vport_enable_roce(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5_nic_vport_disable_roce(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5_query_vport_करोwn_stats(काष्ठा mlx5_core_dev *mdev, u16 vport,
				u8 other_vport, u64 *rx_discard_vport_करोwn,
				u64 *tx_discard_vport_करोwn);
पूर्णांक mlx5_core_query_vport_counter(काष्ठा mlx5_core_dev *dev, u8 other_vport,
				  पूर्णांक vf, u8 port_num, व्योम *out);
पूर्णांक mlx5_core_modअगरy_hca_vport_context(काष्ठा mlx5_core_dev *dev,
				       u8 other_vport, u8 port_num,
				       पूर्णांक vf,
				       काष्ठा mlx5_hca_vport_context *req);
पूर्णांक mlx5_nic_vport_update_local_lb(काष्ठा mlx5_core_dev *mdev, bool enable);
पूर्णांक mlx5_nic_vport_query_local_lb(काष्ठा mlx5_core_dev *mdev, bool *status);

पूर्णांक mlx5_nic_vport_affiliate_multiport(काष्ठा mlx5_core_dev *master_mdev,
				       काष्ठा mlx5_core_dev *port_mdev);
पूर्णांक mlx5_nic_vport_unaffiliate_multiport(काष्ठा mlx5_core_dev *port_mdev);

u64 mlx5_query_nic_प्रणाली_image_guid(काष्ठा mlx5_core_dev *mdev);
#पूर्ण_अगर /* __MLX5_VPORT_H__ */
