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

#अगर_अघोषित __MLX5_CORE_H__
#घोषणा __MLX5_CORE_H__

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/firmware.h>
#समावेश <linux/mlx5/cq.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/mlx5/driver.h>

बाह्य uपूर्णांक mlx5_core_debug_mask;

#घोषणा mlx5_core_dbg(__dev, क्रमmat, ...)				\
	dev_dbg((__dev)->device, "%s:%d:(pid %d): " क्रमmat,		\
		 __func__, __LINE__, current->pid,			\
		 ##__VA_ARGS__)

#घोषणा mlx5_core_dbg_once(__dev, क्रमmat, ...)		\
	dev_dbg_once((__dev)->device,		\
		     "%s:%d:(pid %d): " क्रमmat,		\
		     __func__, __LINE__, current->pid,	\
		     ##__VA_ARGS__)

#घोषणा mlx5_core_dbg_mask(__dev, mask, क्रमmat, ...)		\
करो अणु								\
	अगर ((mask) & mlx5_core_debug_mask)			\
		mlx5_core_dbg(__dev, क्रमmat, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा mlx5_core_err(__dev, क्रमmat, ...)			\
	dev_err((__dev)->device, "%s:%d:(pid %d): " क्रमmat,	\
		__func__, __LINE__, current->pid,		\
	       ##__VA_ARGS__)

#घोषणा mlx5_core_err_rl(__dev, क्रमmat, ...)			\
	dev_err_ratelimited((__dev)->device,			\
			    "%s:%d:(pid %d): " क्रमmat,		\
			    __func__, __LINE__, current->pid,	\
			    ##__VA_ARGS__)

#घोषणा mlx5_core_warn(__dev, क्रमmat, ...)			\
	dev_warn((__dev)->device, "%s:%d:(pid %d): " क्रमmat,	\
		 __func__, __LINE__, current->pid,		\
		 ##__VA_ARGS__)

#घोषणा mlx5_core_warn_once(__dev, क्रमmat, ...)				\
	dev_warn_once((__dev)->device, "%s:%d:(pid %d): " क्रमmat,	\
		      __func__, __LINE__, current->pid,			\
		      ##__VA_ARGS__)

#घोषणा mlx5_core_warn_rl(__dev, क्रमmat, ...)			\
	dev_warn_ratelimited((__dev)->device,			\
			     "%s:%d:(pid %d): " क्रमmat,		\
			     __func__, __LINE__, current->pid,	\
			     ##__VA_ARGS__)

#घोषणा mlx5_core_info(__dev, क्रमmat, ...)		\
	dev_info((__dev)->device, क्रमmat, ##__VA_ARGS__)

#घोषणा mlx5_core_info_rl(__dev, क्रमmat, ...)			\
	dev_info_ratelimited((__dev)->device,			\
			     "%s:%d:(pid %d): " क्रमmat,		\
			     __func__, __LINE__, current->pid,	\
			     ##__VA_ARGS__)

अटल अंतरभूत काष्ठा device *mlx5_core_dma_dev(काष्ठा mlx5_core_dev *dev)
अणु
	वापस &dev->pdev->dev;
पूर्ण

क्रमागत अणु
	MLX5_CMD_DATA, /* prपूर्णांक command payload only */
	MLX5_CMD_TIME, /* prपूर्णांक command execution समय */
पूर्ण;

क्रमागत अणु
	MLX5_DRIVER_STATUS_ABORTED = 0xfe,
	MLX5_DRIVER_SYND = 0xbadd00de,
पूर्ण;

क्रमागत mlx5_semaphore_space_address अणु
	MLX5_SEMAPHORE_SPACE_DOMAIN     = 0xA,
	MLX5_SEMAPHORE_SW_RESET         = 0x20,
पूर्ण;

#घोषणा MLX5_DEFAULT_PROF       2

पूर्णांक mlx5_query_hca_caps(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_query_board_id(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_cmd_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cmd_cleanup(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cmd_set_state(काष्ठा mlx5_core_dev *dev,
			क्रमागत mlx5_cmdअगर_state cmdअगर_state);
पूर्णांक mlx5_cmd_init_hca(काष्ठा mlx5_core_dev *dev, uपूर्णांक32_t *sw_owner_id);
पूर्णांक mlx5_cmd_tearकरोwn_hca(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_cmd_क्रमce_tearकरोwn_hca(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_cmd_fast_tearकरोwn_hca(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_enter_error_state(काष्ठा mlx5_core_dev *dev, bool क्रमce);
व्योम mlx5_error_sw_reset(काष्ठा mlx5_core_dev *dev);
u32 mlx5_health_check_fatal_sensors(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_health_रुको_pci_up(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_disable_device(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_recover_device(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_sriov_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_sriov_cleanup(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_sriov_attach(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_sriov_detach(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_core_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs);
पूर्णांक mlx5_core_sriov_set_msix_vec_count(काष्ठा pci_dev *vf, पूर्णांक msix_vec_count);
पूर्णांक mlx5_core_enable_hca(काष्ठा mlx5_core_dev *dev, u16 func_id);
पूर्णांक mlx5_core_disable_hca(काष्ठा mlx5_core_dev *dev, u16 func_id);
पूर्णांक mlx5_create_scheduling_element_cmd(काष्ठा mlx5_core_dev *dev, u8 hierarchy,
				       व्योम *context, u32 *element_id);
पूर्णांक mlx5_modअगरy_scheduling_element_cmd(काष्ठा mlx5_core_dev *dev, u8 hierarchy,
				       व्योम *context, u32 element_id,
				       u32 modअगरy_biपंचांगask);
पूर्णांक mlx5_destroy_scheduling_element_cmd(काष्ठा mlx5_core_dev *dev, u8 hierarchy,
					u32 element_id);
पूर्णांक mlx5_रुको_क्रम_pages(काष्ठा mlx5_core_dev *dev, पूर्णांक *pages);

व्योम mlx5_cmd_trigger_completions(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cmd_flush(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cq_debugfs_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_cq_debugfs_cleanup(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_query_pcam_reg(काष्ठा mlx5_core_dev *dev, u32 *pcam, u8 feature_group,
			u8 access_reg_group);
पूर्णांक mlx5_query_mcam_reg(काष्ठा mlx5_core_dev *dev, u32 *mcap, u8 feature_group,
			u8 access_reg_group);
पूर्णांक mlx5_query_qcam_reg(काष्ठा mlx5_core_dev *mdev, u32 *qcam,
			u8 feature_group, u8 access_reg_group);

व्योम mlx5_lag_add(काष्ठा mlx5_core_dev *dev, काष्ठा net_device *netdev);
व्योम mlx5_lag_हटाओ(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_irq_table_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_irq_table_cleanup(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_irq_table_create(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_irq_table_destroy(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_irq_attach_nb(काष्ठा mlx5_irq_table *irq_table, पूर्णांक vecidx,
		       काष्ठा notअगरier_block *nb);
पूर्णांक mlx5_irq_detach_nb(काष्ठा mlx5_irq_table *irq_table, पूर्णांक vecidx,
		       काष्ठा notअगरier_block *nb);

पूर्णांक mlx5_set_msix_vec_count(काष्ठा mlx5_core_dev *dev, पूर्णांक devfn,
			    पूर्णांक msix_vec_count);
पूर्णांक mlx5_get_शेष_msix_vec_count(काष्ठा mlx5_core_dev *dev, पूर्णांक num_vfs);

काष्ठा cpumask *
mlx5_irq_get_affinity_mask(काष्ठा mlx5_irq_table *irq_table, पूर्णांक vecidx);
काष्ठा cpu_rmap *mlx5_irq_get_rmap(काष्ठा mlx5_irq_table *table);
पूर्णांक mlx5_irq_get_num_comp(काष्ठा mlx5_irq_table *table);
काष्ठा mlx5_irq_table *mlx5_irq_table_get(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_events_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_events_cleanup(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_events_start(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_events_stop(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_adev_idx_alloc(व्योम);
व्योम mlx5_adev_idx_मुक्त(पूर्णांक idx);
व्योम mlx5_adev_cleanup(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_adev_init(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_attach_device(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_detach_device(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_रेजिस्टर_device(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_unरेजिस्टर_device(काष्ठा mlx5_core_dev *dev);
काष्ठा mlx5_core_dev *mlx5_get_next_phys_dev(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_dev_list_lock(व्योम);
व्योम mlx5_dev_list_unlock(व्योम);
पूर्णांक mlx5_dev_list_trylock(व्योम);

पूर्णांक mlx5_query_mtpps(काष्ठा mlx5_core_dev *dev, u32 *mtpps, u32 mtpps_size);
पूर्णांक mlx5_set_mtpps(काष्ठा mlx5_core_dev *mdev, u32 *mtpps, u32 mtpps_size);
पूर्णांक mlx5_query_mtppse(काष्ठा mlx5_core_dev *mdev, u8 pin, u8 *arm, u8 *mode);
पूर्णांक mlx5_set_mtppse(काष्ठा mlx5_core_dev *mdev, u8 pin, u8 arm, u8 mode);

काष्ठा mlx5_dm *mlx5_dm_create(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_dm_cleanup(काष्ठा mlx5_core_dev *dev);

#घोषणा MLX5_PPS_CAP(mdev) (MLX5_CAP_GEN((mdev), pps) &&		\
			    MLX5_CAP_GEN((mdev), pps_modअगरy) &&		\
			    MLX5_CAP_MCAM_FEATURE((mdev), mtpps_fs) &&	\
			    MLX5_CAP_MCAM_FEATURE((mdev), mtpps_enh_out_per_adj))

पूर्णांक mlx5_firmware_flash(काष्ठा mlx5_core_dev *dev, स्थिर काष्ठा firmware *fw,
			काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5_fw_version_query(काष्ठा mlx5_core_dev *dev,
			  u32 *running_ver, u32 *stored_ver);

पूर्णांक mlx5e_init(व्योम);
व्योम mlx5e_cleanup(व्योम);

अटल अंतरभूत bool mlx5_sriov_is_enabled(काष्ठा mlx5_core_dev *dev)
अणु
	वापस pci_num_vf(dev->pdev) ? true : false;
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_lag_is_lacp_owner(काष्ठा mlx5_core_dev *dev)
अणु
	/* LACP owner conditions:
	 * 1) Function is physical.
	 * 2) LAG is supported by FW.
	 * 3) LAG is managed by driver (currently the only option).
	 */
	वापस  MLX5_CAP_GEN(dev, vport_group_manager) &&
		   (MLX5_CAP_GEN(dev, num_lag_ports) > 1) &&
		    MLX5_CAP_GEN(dev, lag_master);
पूर्ण

पूर्णांक mlx5_rescan_drivers_locked(काष्ठा mlx5_core_dev *dev);
अटल अंतरभूत पूर्णांक mlx5_rescan_drivers(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक ret;

	mlx5_dev_list_lock();
	ret = mlx5_rescan_drivers_locked(dev);
	mlx5_dev_list_unlock();
	वापस ret;
पूर्ण

व्योम mlx5_lag_update(काष्ठा mlx5_core_dev *dev);

क्रमागत अणु
	MLX5_NIC_IFC_FULL		= 0,
	MLX5_NIC_IFC_DISABLED		= 1,
	MLX5_NIC_IFC_NO_DRAM_NIC	= 2,
	MLX5_NIC_IFC_SW_RESET		= 7
पूर्ण;

u8 mlx5_get_nic_state(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_set_nic_state(काष्ठा mlx5_core_dev *dev, u8 state);

अटल अंतरभूत bool mlx5_core_is_sf(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->coredev_type == MLX5_COREDEV_SF;
पूर्ण

पूर्णांक mlx5_mdev_init(काष्ठा mlx5_core_dev *dev, पूर्णांक profile_idx);
व्योम mlx5_mdev_uninit(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_init_one(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_uninit_one(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_unload_one(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_load_one(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_vport_get_other_func_cap(काष्ठा mlx5_core_dev *dev, u16 function_id, व्योम *out);

व्योम mlx5_events_work_enqueue(काष्ठा mlx5_core_dev *dev, काष्ठा work_काष्ठा *work);
अटल अंतरभूत u32 mlx5_sriov_get_vf_total_msix(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx5_core_dev *dev = pci_get_drvdata(pdev);

	वापस MLX5_CAP_GEN_MAX(dev, num_total_dynamic_vf_msix);
पूर्ण
#पूर्ण_अगर /* __MLX5_CORE_H__ */
