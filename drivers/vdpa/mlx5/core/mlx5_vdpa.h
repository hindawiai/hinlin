<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies Ltd. */

#अगर_अघोषित __MLX5_VDPA_H__
#घोषणा __MLX5_VDPA_H__

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/vdpa.h>
#समावेश <linux/mlx5/driver.h>

#घोषणा MLX5V_ETH_HARD_MTU (ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN)

काष्ठा mlx5_vdpa_direct_mr अणु
	u64 start;
	u64 end;
	u32 perm;
	काष्ठा mlx5_core_mkey mr;
	काष्ठा sg_table sg_head;
	पूर्णांक log_size;
	पूर्णांक nsg;
	पूर्णांक nent;
	काष्ठा list_head list;
	u64 offset;
पूर्ण;

काष्ठा mlx5_vdpa_mr अणु
	काष्ठा mlx5_core_mkey mkey;

	/* list of direct MRs descendants of this indirect mr */
	काष्ठा list_head head;
	अचिन्हित दीर्घ num_directs;
	अचिन्हित दीर्घ num_klms;
	bool initialized;

	/* serialize mkey creation and deकाष्ठाion */
	काष्ठा mutex mkey_mtx;
पूर्ण;

काष्ठा mlx5_vdpa_resources अणु
	u32 pdn;
	काष्ठा mlx5_uars_page *uar;
	व्योम __iomem *kick_addr;
	u16 uid;
	u32 null_mkey;
	bool valid;
पूर्ण;

काष्ठा mlx5_vdpa_dev अणु
	काष्ठा vdpa_device vdev;
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा mlx5_vdpa_resources res;

	u64 mlx_features;
	u64 actual_features;
	u8 status;
	u32 max_vqs;
	u32 generation;

	काष्ठा mlx5_vdpa_mr mr;
पूर्ण;

पूर्णांक mlx5_vdpa_alloc_pd(काष्ठा mlx5_vdpa_dev *dev, u32 *pdn, u16 uid);
पूर्णांक mlx5_vdpa_dealloc_pd(काष्ठा mlx5_vdpa_dev *dev, u32 pdn, u16 uid);
पूर्णांक mlx5_vdpa_get_null_mkey(काष्ठा mlx5_vdpa_dev *dev, u32 *null_mkey);
पूर्णांक mlx5_vdpa_create_tis(काष्ठा mlx5_vdpa_dev *mvdev, व्योम *in, u32 *tisn);
व्योम mlx5_vdpa_destroy_tis(काष्ठा mlx5_vdpa_dev *mvdev, u32 tisn);
पूर्णांक mlx5_vdpa_create_rqt(काष्ठा mlx5_vdpa_dev *mvdev, व्योम *in, पूर्णांक inlen, u32 *rqtn);
व्योम mlx5_vdpa_destroy_rqt(काष्ठा mlx5_vdpa_dev *mvdev, u32 rqtn);
पूर्णांक mlx5_vdpa_create_tir(काष्ठा mlx5_vdpa_dev *mvdev, व्योम *in, u32 *tirn);
व्योम mlx5_vdpa_destroy_tir(काष्ठा mlx5_vdpa_dev *mvdev, u32 tirn);
पूर्णांक mlx5_vdpa_alloc_transport_करोमुख्य(काष्ठा mlx5_vdpa_dev *mvdev, u32 *tdn);
व्योम mlx5_vdpa_dealloc_transport_करोमुख्य(काष्ठा mlx5_vdpa_dev *mvdev, u32 tdn);
पूर्णांक mlx5_vdpa_alloc_resources(काष्ठा mlx5_vdpa_dev *mvdev);
व्योम mlx5_vdpa_मुक्त_resources(काष्ठा mlx5_vdpa_dev *mvdev);
पूर्णांक mlx5_vdpa_create_mkey(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_core_mkey *mkey, u32 *in,
			  पूर्णांक inlen);
पूर्णांक mlx5_vdpa_destroy_mkey(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा mlx5_core_mkey *mkey);
पूर्णांक mlx5_vdpa_handle_set_map(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा vhost_iotlb *iotlb,
			     bool *change_map);
पूर्णांक mlx5_vdpa_create_mr(काष्ठा mlx5_vdpa_dev *mvdev, काष्ठा vhost_iotlb *iotlb);
व्योम mlx5_vdpa_destroy_mr(काष्ठा mlx5_vdpa_dev *mvdev);

#घोषणा mlx5_vdpa_warn(__dev, क्रमmat, ...)                                                         \
	dev_warn((__dev)->mdev->device, "%s:%d:(pid %d) warning: " क्रमmat, __func__, __LINE__,     \
		 current->pid, ##__VA_ARGS__)

#घोषणा mlx5_vdpa_info(__dev, क्रमmat, ...)                                                         \
	dev_info((__dev)->mdev->device, "%s:%d:(pid %d): " क्रमmat, __func__, __LINE__,             \
		 current->pid, ##__VA_ARGS__)

#घोषणा mlx5_vdpa_dbg(__dev, क्रमmat, ...)                                                          \
	dev_debug((__dev)->mdev->device, "%s:%d:(pid %d): " क्रमmat, __func__, __LINE__,            \
		  current->pid, ##__VA_ARGS__)

#पूर्ण_अगर /* __MLX5_VDPA_H__ */
