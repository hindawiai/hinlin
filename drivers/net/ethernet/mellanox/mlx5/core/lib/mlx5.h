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

#अगर_अघोषित __LIB_MLX5_H__
#घोषणा __LIB_MLX5_H__

#समावेश "mlx5_core.h"

व्योम mlx5_init_reserved_gids(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cleanup_reserved_gids(काष्ठा mlx5_core_dev *dev);
पूर्णांक  mlx5_core_reserve_gids(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक count);
व्योम mlx5_core_unreserve_gids(काष्ठा mlx5_core_dev *dev, अचिन्हित पूर्णांक count);
पूर्णांक  mlx5_core_reserved_gid_alloc(काष्ठा mlx5_core_dev *dev, पूर्णांक *gid_index);
व्योम mlx5_core_reserved_gid_मुक्त(काष्ठा mlx5_core_dev *dev, पूर्णांक gid_index);
पूर्णांक mlx5_crdump_enable(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_crdump_disable(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_crdump_collect(काष्ठा mlx5_core_dev *dev, u32 *cr_data);

/* TODO move to lib/events.h */

#घोषणा PORT_MODULE_EVENT_MODULE_STATUS_MASK 0xF
#घोषणा PORT_MODULE_EVENT_ERROR_TYPE_MASK    0xF

क्रमागत port_module_event_status_type अणु
	MLX5_MODULE_STATUS_PLUGGED   = 0x1,
	MLX5_MODULE_STATUS_UNPLUGGED = 0x2,
	MLX5_MODULE_STATUS_ERROR     = 0x3,
	MLX5_MODULE_STATUS_DISABLED  = 0x4,
	MLX5_MODULE_STATUS_NUM,
पूर्ण;

क्रमागत  port_module_event_error_type अणु
	MLX5_MODULE_EVENT_ERROR_POWER_BUDGET_EXCEEDED    = 0x0,
	MLX5_MODULE_EVENT_ERROR_LONG_RANGE_FOR_NON_MLNX  = 0x1,
	MLX5_MODULE_EVENT_ERROR_BUS_STUCK                = 0x2,
	MLX5_MODULE_EVENT_ERROR_NO_EEPROM_RETRY_TIMEOUT  = 0x3,
	MLX5_MODULE_EVENT_ERROR_ENFORCE_PART_NUMBER_LIST = 0x4,
	MLX5_MODULE_EVENT_ERROR_UNKNOWN_IDENTIFIER       = 0x5,
	MLX5_MODULE_EVENT_ERROR_HIGH_TEMPERATURE         = 0x6,
	MLX5_MODULE_EVENT_ERROR_BAD_CABLE                = 0x7,
	MLX5_MODULE_EVENT_ERROR_PCIE_POWER_SLOT_EXCEEDED = 0xc,
	MLX5_MODULE_EVENT_ERROR_NUM,
पूर्ण;

काष्ठा mlx5_pme_stats अणु
	u64 status_counters[MLX5_MODULE_STATUS_NUM];
	u64 error_counters[MLX5_MODULE_EVENT_ERROR_NUM];
पूर्ण;

व्योम mlx5_get_pme_stats(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_pme_stats *stats);
पूर्णांक mlx5_notअगरier_call_chain(काष्ठा mlx5_events *events, अचिन्हित पूर्णांक event, व्योम *data);

/* Crypto */
क्रमागत अणु
	MLX5_ACCEL_OBJ_TLS_KEY = MLX5_GENERAL_OBJECT_TYPE_ENCRYPTION_KEY_TYPE_TLS,
	MLX5_ACCEL_OBJ_IPSEC_KEY = MLX5_GENERAL_OBJECT_TYPE_ENCRYPTION_KEY_TYPE_IPSEC,
पूर्ण;

पूर्णांक mlx5_create_encryption_key(काष्ठा mlx5_core_dev *mdev,
			       व्योम *key, u32 sz_bytes,
			       u32 key_type, u32 *p_key_id);
व्योम mlx5_destroy_encryption_key(काष्ठा mlx5_core_dev *mdev, u32 key_id);

अटल अंतरभूत काष्ठा net *mlx5_core_net(काष्ठा mlx5_core_dev *dev)
अणु
	वापस devlink_net(priv_to_devlink(dev));
पूर्ण

अटल अंतरभूत व्योम mlx5_uplink_netdev_set(काष्ठा mlx5_core_dev *mdev, काष्ठा net_device *netdev)
अणु
	mdev->mlx5e_res.uplink_netdev = netdev;
पूर्ण

अटल अंतरभूत काष्ठा net_device *mlx5_uplink_netdev_get(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mdev->mlx5e_res.uplink_netdev;
पूर्ण
#पूर्ण_अगर
