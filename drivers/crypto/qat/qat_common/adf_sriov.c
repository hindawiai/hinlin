<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2015 - 2020 Intel Corporation */
#समावेश <linux/workqueue.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/iommu.h>
#समावेश "adf_common_drv.h"
#समावेश "adf_cfg.h"
#समावेश "adf_pf2vf_msg.h"

अटल काष्ठा workqueue_काष्ठा *pf2vf_resp_wq;

काष्ठा adf_pf2vf_resp अणु
	काष्ठा work_काष्ठा pf2vf_resp_work;
	काष्ठा adf_accel_vf_info *vf_info;
पूर्ण;

अटल व्योम adf_iov_send_resp(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा adf_pf2vf_resp *pf2vf_resp =
		container_of(work, काष्ठा adf_pf2vf_resp, pf2vf_resp_work);

	adf_vf2pf_req_hndl(pf2vf_resp->vf_info);
	kमुक्त(pf2vf_resp);
पूर्ण

अटल व्योम adf_vf2pf_bh_handler(व्योम *data)
अणु
	काष्ठा adf_accel_vf_info *vf_info = (काष्ठा adf_accel_vf_info *)data;
	काष्ठा adf_pf2vf_resp *pf2vf_resp;

	pf2vf_resp = kzalloc(माप(*pf2vf_resp), GFP_ATOMIC);
	अगर (!pf2vf_resp)
		वापस;

	pf2vf_resp->vf_info = vf_info;
	INIT_WORK(&pf2vf_resp->pf2vf_resp_work, adf_iov_send_resp);
	queue_work(pf2vf_resp_wq, &pf2vf_resp->pf2vf_resp_work);
पूर्ण

अटल पूर्णांक adf_enable_sriov(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा pci_dev *pdev = accel_to_pci_dev(accel_dev);
	पूर्णांक totalvfs = pci_sriov_get_totalvfs(pdev);
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	काष्ठा adf_accel_vf_info *vf_info;
	पूर्णांक i;

	क्रम (i = 0, vf_info = accel_dev->pf.vf_info; i < totalvfs;
	     i++, vf_info++) अणु
		/* This ptr will be populated when VFs will be created */
		vf_info->accel_dev = accel_dev;
		vf_info->vf_nr = i;

		tasklet_init(&vf_info->vf2pf_bh_tasklet,
			     (व्योम *)adf_vf2pf_bh_handler,
			     (अचिन्हित दीर्घ)vf_info);
		mutex_init(&vf_info->pf2vf_lock);
		ratelimit_state_init(&vf_info->vf2pf_ratelimit,
				     DEFAULT_RATELIMIT_INTERVAL,
				     DEFAULT_RATELIMIT_BURST);
	पूर्ण

	/* Set Valid bits in AE Thपढ़ो to PCIe Function Mapping */
	अगर (hw_data->configure_iov_thपढ़ोs)
		hw_data->configure_iov_thपढ़ोs(accel_dev, true);

	/* Enable VF to PF पूर्णांकerrupts क्रम all VFs */
	अगर (hw_data->get_pf2vf_offset)
		adf_enable_vf2pf_पूर्णांकerrupts(accel_dev, BIT_ULL(totalvfs) - 1);

	/*
	 * Due to the hardware design, when SR-IOV and the ring arbiter
	 * are enabled all the VFs supported in hardware must be enabled in
	 * order क्रम all the hardware resources (i.e. bundles) to be usable.
	 * When SR-IOV is enabled, each of the VFs will own one bundle.
	 */
	वापस pci_enable_sriov(pdev, totalvfs);
पूर्ण

/**
 * adf_disable_sriov() - Disable SRIOV क्रम the device
 * @accel_dev:  Poपूर्णांकer to accel device.
 *
 * Function disables SRIOV क्रम the accel device.
 *
 * Return: 0 on success, error code otherwise.
 */
व्योम adf_disable_sriov(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	पूर्णांक totalvfs = pci_sriov_get_totalvfs(accel_to_pci_dev(accel_dev));
	काष्ठा adf_accel_vf_info *vf;
	पूर्णांक i;

	अगर (!accel_dev->pf.vf_info)
		वापस;

	अगर (hw_data->get_pf2vf_offset)
		adf_pf2vf_notअगरy_restarting(accel_dev);

	pci_disable_sriov(accel_to_pci_dev(accel_dev));

	/* Disable VF to PF पूर्णांकerrupts */
	अगर (hw_data->get_pf2vf_offset)
		adf_disable_vf2pf_पूर्णांकerrupts(accel_dev, GENMASK(31, 0));

	/* Clear Valid bits in AE Thपढ़ो to PCIe Function Mapping */
	अगर (hw_data->configure_iov_thपढ़ोs)
		hw_data->configure_iov_thपढ़ोs(accel_dev, false);

	क्रम (i = 0, vf = accel_dev->pf.vf_info; i < totalvfs; i++, vf++) अणु
		tasklet_disable(&vf->vf2pf_bh_tasklet);
		tasklet_समाप्त(&vf->vf2pf_bh_tasklet);
		mutex_destroy(&vf->pf2vf_lock);
	पूर्ण

	kमुक्त(accel_dev->pf.vf_info);
	accel_dev->pf.vf_info = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(adf_disable_sriov);

/**
 * adf_sriov_configure() - Enable SRIOV क्रम the device
 * @pdev:  Poपूर्णांकer to PCI device.
 * @numvfs: Number of भव functions (VFs) to enable.
 *
 * Note that the @numvfs parameter is ignored and all VFs supported by the
 * device are enabled due to the design of the hardware.
 *
 * Function enables SRIOV क्रम the PCI device.
 *
 * Return: number of VFs enabled on success, error code otherwise.
 */
पूर्णांक adf_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक numvfs)
अणु
	काष्ठा adf_accel_dev *accel_dev = adf_devmgr_pci_to_accel_dev(pdev);
	पूर्णांक totalvfs = pci_sriov_get_totalvfs(pdev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (!accel_dev) अणु
		dev_err(&pdev->dev, "Failed to find accel_dev\n");
		वापस -EFAULT;
	पूर्ण

	अगर (!iommu_present(&pci_bus_type))
		dev_warn(&pdev->dev, "IOMMU should be enabled for SR-IOV to work correctly\n");

	अगर (accel_dev->pf.vf_info) अणु
		dev_info(&pdev->dev, "Already enabled for this device\n");
		वापस -EINVAL;
	पूर्ण

	अगर (adf_dev_started(accel_dev)) अणु
		अगर (adf_devmgr_in_reset(accel_dev) ||
		    adf_dev_in_use(accel_dev)) अणु
			dev_err(&GET_DEV(accel_dev), "Device busy\n");
			वापस -EBUSY;
		पूर्ण

		adf_dev_stop(accel_dev);
		adf_dev_shutकरोwn(accel_dev);
	पूर्ण

	अगर (adf_cfg_section_add(accel_dev, ADF_KERNEL_SEC))
		वापस -EFAULT;
	val = 0;
	अगर (adf_cfg_add_key_value_param(accel_dev, ADF_KERNEL_SEC,
					ADF_NUM_CY, (व्योम *)&val, ADF_DEC))
		वापस -EFAULT;

	set_bit(ADF_STATUS_CONFIGURED, &accel_dev->status);

	/* Allocate memory क्रम VF info काष्ठाs */
	accel_dev->pf.vf_info = kसुस्मृति(totalvfs,
					माप(काष्ठा adf_accel_vf_info),
					GFP_KERNEL);
	अगर (!accel_dev->pf.vf_info)
		वापस -ENOMEM;

	अगर (adf_dev_init(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to init qat_dev%d\n",
			accel_dev->accel_id);
		वापस -EFAULT;
	पूर्ण

	अगर (adf_dev_start(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to start qat_dev%d\n",
			accel_dev->accel_id);
		वापस -EFAULT;
	पूर्ण

	ret = adf_enable_sriov(accel_dev);
	अगर (ret)
		वापस ret;

	वापस numvfs;
पूर्ण
EXPORT_SYMBOL_GPL(adf_sriov_configure);

पूर्णांक __init adf_init_pf_wq(व्योम)
अणु
	/* Workqueue क्रम PF2VF responses */
	pf2vf_resp_wq = alloc_workqueue("qat_pf2vf_resp_wq", WQ_MEM_RECLAIM, 0);

	वापस !pf2vf_resp_wq ? -ENOMEM : 0;
पूर्ण

व्योम adf_निकास_pf_wq(व्योम)
अणु
	अगर (pf2vf_resp_wq) अणु
		destroy_workqueue(pf2vf_resp_wq);
		pf2vf_resp_wq = शून्य;
	पूर्ण
पूर्ण
