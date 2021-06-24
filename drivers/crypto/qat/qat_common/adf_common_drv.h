<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_DRV_H
#घोषणा ADF_DRV_H

#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश "adf_accel_devices.h"
#समावेश "icp_qat_fw_loader_handle.h"
#समावेश "icp_qat_hal.h"

#घोषणा ADF_MAJOR_VERSION	0
#घोषणा ADF_MINOR_VERSION	6
#घोषणा ADF_BUILD_VERSION	0
#घोषणा ADF_DRV_VERSION		__stringअगरy(ADF_MAJOR_VERSION) "." \
				__stringअगरy(ADF_MINOR_VERSION) "." \
				__stringअगरy(ADF_BUILD_VERSION)

#घोषणा ADF_STATUS_RESTARTING 0
#घोषणा ADF_STATUS_STARTING 1
#घोषणा ADF_STATUS_CONFIGURED 2
#घोषणा ADF_STATUS_STARTED 3
#घोषणा ADF_STATUS_AE_INITIALISED 4
#घोषणा ADF_STATUS_AE_UCODE_LOADED 5
#घोषणा ADF_STATUS_AE_STARTED 6
#घोषणा ADF_STATUS_PF_RUNNING 7
#घोषणा ADF_STATUS_IRQ_ALLOCATED 8

क्रमागत adf_dev_reset_mode अणु
	ADF_DEV_RESET_ASYNC = 0,
	ADF_DEV_RESET_SYNC
पूर्ण;

क्रमागत adf_event अणु
	ADF_EVENT_INIT = 0,
	ADF_EVENT_START,
	ADF_EVENT_STOP,
	ADF_EVENT_SHUTDOWN,
	ADF_EVENT_RESTARTING,
	ADF_EVENT_RESTARTED,
पूर्ण;

काष्ठा service_hndl अणु
	पूर्णांक (*event_hld)(काष्ठा adf_accel_dev *accel_dev,
			 क्रमागत adf_event event);
	अचिन्हित दीर्घ init_status[ADF_DEVS_ARRAY_SIZE];
	अचिन्हित दीर्घ start_status[ADF_DEVS_ARRAY_SIZE];
	अक्षर *name;
	काष्ठा list_head list;
पूर्ण;

अटल अंतरभूत पूर्णांक get_current_node(व्योम)
अणु
	वापस topology_physical_package_id(raw_smp_processor_id());
पूर्ण

पूर्णांक adf_service_रेजिस्टर(काष्ठा service_hndl *service);
पूर्णांक adf_service_unरेजिस्टर(काष्ठा service_hndl *service);

पूर्णांक adf_dev_init(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_dev_start(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_dev_stop(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_dev_shutकरोwn(काष्ठा adf_accel_dev *accel_dev);

पूर्णांक adf_iov_puपंचांगsg(काष्ठा adf_accel_dev *accel_dev, u32 msg, u8 vf_nr);
व्योम adf_pf2vf_notअगरy_restarting(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_enable_vf2pf_comms(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_vf2pf_req_hndl(काष्ठा adf_accel_vf_info *vf_info);
व्योम adf_devmgr_update_class_index(काष्ठा adf_hw_device_data *hw_data);
व्योम adf_clean_vf_map(bool);

पूर्णांक adf_ctl_dev_रेजिस्टर(व्योम);
व्योम adf_ctl_dev_unरेजिस्टर(व्योम);
पूर्णांक adf_processes_dev_रेजिस्टर(व्योम);
व्योम adf_processes_dev_unरेजिस्टर(व्योम);

पूर्णांक adf_devmgr_add_dev(काष्ठा adf_accel_dev *accel_dev,
		       काष्ठा adf_accel_dev *pf);
व्योम adf_devmgr_rm_dev(काष्ठा adf_accel_dev *accel_dev,
		       काष्ठा adf_accel_dev *pf);
काष्ठा list_head *adf_devmgr_get_head(व्योम);
काष्ठा adf_accel_dev *adf_devmgr_get_dev_by_id(u32 id);
काष्ठा adf_accel_dev *adf_devmgr_get_first(व्योम);
काष्ठा adf_accel_dev *adf_devmgr_pci_to_accel_dev(काष्ठा pci_dev *pci_dev);
पूर्णांक adf_devmgr_verअगरy_id(u32 id);
व्योम adf_devmgr_get_num_dev(u32 *num);
पूर्णांक adf_devmgr_in_reset(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_dev_started(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_dev_restarting_notअगरy(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_dev_restarted_notअगरy(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_ae_init(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_ae_shutकरोwn(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_ae_fw_load(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_ae_fw_release(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_ae_start(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_ae_stop(काष्ठा adf_accel_dev *accel_dev);

पूर्णांक adf_enable_aer(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_disable_aer(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_reset_sbr(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_reset_flr(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_dev_restore(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_init_aer(व्योम);
व्योम adf_निकास_aer(व्योम);
पूर्णांक adf_init_admin_comms(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_निकास_admin_comms(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_send_admin_init(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_init_arb(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_निकास_arb(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_update_ring_arb(काष्ठा adf_etr_ring_data *ring);

पूर्णांक adf_dev_get(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_dev_put(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_dev_in_use(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_init_etr_data(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_cleanup_etr_data(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक qat_crypto_रेजिस्टर(व्योम);
पूर्णांक qat_crypto_unरेजिस्टर(व्योम);
पूर्णांक qat_crypto_dev_config(काष्ठा adf_accel_dev *accel_dev);
काष्ठा qat_crypto_instance *qat_crypto_get_instance_node(पूर्णांक node);
व्योम qat_crypto_put_instance(काष्ठा qat_crypto_instance *inst);
व्योम qat_alg_callback(व्योम *resp);
व्योम qat_alg_asym_callback(व्योम *resp);
पूर्णांक qat_algs_रेजिस्टर(व्योम);
व्योम qat_algs_unरेजिस्टर(व्योम);
पूर्णांक qat_asym_algs_रेजिस्टर(व्योम);
व्योम qat_asym_algs_unरेजिस्टर(व्योम);

पूर्णांक adf_isr_resource_alloc(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_isr_resource_मुक्त(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_vf_isr_resource_alloc(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_vf_isr_resource_मुक्त(काष्ठा adf_accel_dev *accel_dev);

पूर्णांक qat_hal_init(काष्ठा adf_accel_dev *accel_dev);
व्योम qat_hal_deinit(काष्ठा icp_qat_fw_loader_handle *handle);
पूर्णांक qat_hal_start(काष्ठा icp_qat_fw_loader_handle *handle);
व्योम qat_hal_stop(काष्ठा icp_qat_fw_loader_handle *handle, अचिन्हित अक्षर ae,
		  अचिन्हित पूर्णांक ctx_mask);
व्योम qat_hal_reset(काष्ठा icp_qat_fw_loader_handle *handle);
पूर्णांक qat_hal_clr_reset(काष्ठा icp_qat_fw_loader_handle *handle);
व्योम qat_hal_set_live_ctx(काष्ठा icp_qat_fw_loader_handle *handle,
			  अचिन्हित अक्षर ae, अचिन्हित पूर्णांक ctx_mask);
पूर्णांक qat_hal_check_ae_active(काष्ठा icp_qat_fw_loader_handle *handle,
			    अचिन्हित पूर्णांक ae);
पूर्णांक qat_hal_set_ae_lm_mode(काष्ठा icp_qat_fw_loader_handle *handle,
			   अचिन्हित अक्षर ae, क्रमागत icp_qat_uof_regtype lm_type,
			   अचिन्हित अक्षर mode);
पूर्णांक qat_hal_set_ae_ctx_mode(काष्ठा icp_qat_fw_loader_handle *handle,
			    अचिन्हित अक्षर ae, अचिन्हित अक्षर mode);
पूर्णांक qat_hal_set_ae_nn_mode(काष्ठा icp_qat_fw_loader_handle *handle,
			   अचिन्हित अक्षर ae, अचिन्हित अक्षर mode);
व्योम qat_hal_set_pc(काष्ठा icp_qat_fw_loader_handle *handle,
		    अचिन्हित अक्षर ae, अचिन्हित पूर्णांक ctx_mask, अचिन्हित पूर्णांक upc);
व्योम qat_hal_wr_uwords(काष्ठा icp_qat_fw_loader_handle *handle,
		       अचिन्हित अक्षर ae, अचिन्हित पूर्णांक uaddr,
		       अचिन्हित पूर्णांक words_num, u64 *uword);
व्योम qat_hal_wr_umem(काष्ठा icp_qat_fw_loader_handle *handle, अचिन्हित अक्षर ae,
		     अचिन्हित पूर्णांक uword_addr, अचिन्हित पूर्णांक words_num,
		     अचिन्हित पूर्णांक *data);
पूर्णांक qat_hal_get_ins_num(व्योम);
पूर्णांक qat_hal_batch_wr_lm(काष्ठा icp_qat_fw_loader_handle *handle,
			अचिन्हित अक्षर ae,
			काष्ठा icp_qat_uof_batch_init *lm_init_header);
पूर्णांक qat_hal_init_gpr(काष्ठा icp_qat_fw_loader_handle *handle,
		     अचिन्हित अक्षर ae, अचिन्हित दीर्घ ctx_mask,
		     क्रमागत icp_qat_uof_regtype reg_type,
		     अचिन्हित लघु reg_num, अचिन्हित पूर्णांक regdata);
पूर्णांक qat_hal_init_wr_xfer(काष्ठा icp_qat_fw_loader_handle *handle,
			 अचिन्हित अक्षर ae, अचिन्हित दीर्घ ctx_mask,
			 क्रमागत icp_qat_uof_regtype reg_type,
			 अचिन्हित लघु reg_num, अचिन्हित पूर्णांक regdata);
पूर्णांक qat_hal_init_rd_xfer(काष्ठा icp_qat_fw_loader_handle *handle,
			 अचिन्हित अक्षर ae, अचिन्हित दीर्घ ctx_mask,
			 क्रमागत icp_qat_uof_regtype reg_type,
			 अचिन्हित लघु reg_num, अचिन्हित पूर्णांक regdata);
पूर्णांक qat_hal_init_nn(काष्ठा icp_qat_fw_loader_handle *handle,
		    अचिन्हित अक्षर ae, अचिन्हित दीर्घ ctx_mask,
		    अचिन्हित लघु reg_num, अचिन्हित पूर्णांक regdata);
पूर्णांक qat_hal_wr_lm(काष्ठा icp_qat_fw_loader_handle *handle,
		  अचिन्हित अक्षर ae, अचिन्हित लघु lm_addr, अचिन्हित पूर्णांक value);
व्योम qat_hal_set_ae_tindex_mode(काष्ठा icp_qat_fw_loader_handle *handle,
				अचिन्हित अक्षर ae, अचिन्हित अक्षर mode);
पूर्णांक qat_uclo_wr_all_uimage(काष्ठा icp_qat_fw_loader_handle *handle);
व्योम qat_uclo_del_obj(काष्ठा icp_qat_fw_loader_handle *handle);
पूर्णांक qat_uclo_wr_mimage(काष्ठा icp_qat_fw_loader_handle *handle, व्योम *addr_ptr,
		       पूर्णांक mem_size);
पूर्णांक qat_uclo_map_obj(काष्ठा icp_qat_fw_loader_handle *handle,
		     व्योम *addr_ptr, u32 mem_size, अक्षर *obj_name);
पूर्णांक qat_uclo_set_cfg_ae_mask(काष्ठा icp_qat_fw_loader_handle *handle,
			     अचिन्हित पूर्णांक cfg_ae_mask);
#अगर defined(CONFIG_PCI_IOV)
पूर्णांक adf_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक numvfs);
व्योम adf_disable_sriov(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_disable_vf2pf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev,
				  u32 vf_mask);
व्योम adf_enable_vf2pf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev,
				 u32 vf_mask);
व्योम adf_enable_pf2vf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_disable_pf2vf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev);

पूर्णांक adf_vf2pf_init(काष्ठा adf_accel_dev *accel_dev);
व्योम adf_vf2pf_shutकरोwn(काष्ठा adf_accel_dev *accel_dev);
पूर्णांक adf_init_pf_wq(व्योम);
व्योम adf_निकास_pf_wq(व्योम);
पूर्णांक adf_init_vf_wq(व्योम);
व्योम adf_निकास_vf_wq(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक adf_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक numvfs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम adf_disable_sriov(काष्ठा adf_accel_dev *accel_dev)
अणु
पूर्ण

अटल अंतरभूत व्योम adf_enable_pf2vf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev)
अणु
पूर्ण

अटल अंतरभूत व्योम adf_disable_pf2vf_पूर्णांकerrupts(काष्ठा adf_accel_dev *accel_dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक adf_vf2pf_init(काष्ठा adf_accel_dev *accel_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम adf_vf2pf_shutकरोwn(काष्ठा adf_accel_dev *accel_dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक adf_init_pf_wq(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम adf_निकास_pf_wq(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक adf_init_vf_wq(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम adf_निकास_vf_wq(व्योम)
अणु
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
