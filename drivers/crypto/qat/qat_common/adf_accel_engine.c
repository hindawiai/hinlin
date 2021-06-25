<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश "adf_cfg.h"
#समावेश "adf_accel_devices.h"
#समावेश "adf_common_drv.h"
#समावेश "icp_qat_uclo.h"

अटल पूर्णांक adf_ae_fw_load_images(काष्ठा adf_accel_dev *accel_dev, व्योम *fw_addr,
				 u32 fw_size)
अणु
	काष्ठा adf_fw_loader_data *loader_data = accel_dev->fw_loader;
	काष्ठा adf_hw_device_data *hw_device = accel_dev->hw_device;
	काष्ठा icp_qat_fw_loader_handle *loader;
	अक्षर *obj_name;
	u32 num_objs;
	u32 ae_mask;
	पूर्णांक i;

	loader = loader_data->fw_loader;
	num_objs = hw_device->uof_get_num_objs();

	क्रम (i = 0; i < num_objs; i++) अणु
		obj_name = hw_device->uof_get_name(i);
		ae_mask = hw_device->uof_get_ae_mask(i);

		अगर (qat_uclo_set_cfg_ae_mask(loader, ae_mask)) अणु
			dev_err(&GET_DEV(accel_dev),
				"Invalid mask for UOF image\n");
			जाओ out_err;
		पूर्ण
		अगर (qat_uclo_map_obj(loader, fw_addr, fw_size, obj_name)) अणु
			dev_err(&GET_DEV(accel_dev),
				"Failed to map UOF firmware\n");
			जाओ out_err;
		पूर्ण
		अगर (qat_uclo_wr_all_uimage(loader)) अणु
			dev_err(&GET_DEV(accel_dev),
				"Failed to load UOF firmware\n");
			जाओ out_err;
		पूर्ण
		qat_uclo_del_obj(loader);
	पूर्ण

	वापस 0;

out_err:
	adf_ae_fw_release(accel_dev);
	वापस -EFAULT;
पूर्ण

पूर्णांक adf_ae_fw_load(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_fw_loader_data *loader_data = accel_dev->fw_loader;
	काष्ठा adf_hw_device_data *hw_device = accel_dev->hw_device;
	व्योम *fw_addr, *mmp_addr;
	u32 fw_size, mmp_size;

	अगर (!hw_device->fw_name)
		वापस 0;

	अगर (request_firmware(&loader_data->mmp_fw, hw_device->fw_mmp_name,
			     &accel_dev->accel_pci_dev.pci_dev->dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to load MMP firmware %s\n",
			hw_device->fw_mmp_name);
		वापस -EFAULT;
	पूर्ण
	अगर (request_firmware(&loader_data->uof_fw, hw_device->fw_name,
			     &accel_dev->accel_pci_dev.pci_dev->dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to load UOF firmware %s\n",
			hw_device->fw_name);
		जाओ out_err;
	पूर्ण

	fw_size = loader_data->uof_fw->size;
	fw_addr = (व्योम *)loader_data->uof_fw->data;
	mmp_size = loader_data->mmp_fw->size;
	mmp_addr = (व्योम *)loader_data->mmp_fw->data;

	अगर (qat_uclo_wr_mimage(loader_data->fw_loader, mmp_addr, mmp_size)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to load MMP\n");
		जाओ out_err;
	पूर्ण

	अगर (hw_device->uof_get_num_objs)
		वापस adf_ae_fw_load_images(accel_dev, fw_addr, fw_size);

	अगर (qat_uclo_map_obj(loader_data->fw_loader, fw_addr, fw_size, शून्य)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to map FW\n");
		जाओ out_err;
	पूर्ण
	अगर (qat_uclo_wr_all_uimage(loader_data->fw_loader)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to load UOF\n");
		जाओ out_err;
	पूर्ण
	वापस 0;

out_err:
	adf_ae_fw_release(accel_dev);
	वापस -EFAULT;
पूर्ण

व्योम adf_ae_fw_release(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_fw_loader_data *loader_data = accel_dev->fw_loader;
	काष्ठा adf_hw_device_data *hw_device = accel_dev->hw_device;

	अगर (!hw_device->fw_name)
		वापस;

	qat_uclo_del_obj(loader_data->fw_loader);
	qat_hal_deinit(loader_data->fw_loader);
	release_firmware(loader_data->uof_fw);
	release_firmware(loader_data->mmp_fw);
	loader_data->uof_fw = शून्य;
	loader_data->mmp_fw = शून्य;
	loader_data->fw_loader = शून्य;
पूर्ण

पूर्णांक adf_ae_start(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_fw_loader_data *loader_data = accel_dev->fw_loader;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	u32 ae_ctr;

	अगर (!hw_data->fw_name)
		वापस 0;

	ae_ctr = qat_hal_start(loader_data->fw_loader);
	dev_info(&GET_DEV(accel_dev),
		 "qat_dev%d started %d acceleration engines\n",
		 accel_dev->accel_id, ae_ctr);
	वापस 0;
पूर्ण

पूर्णांक adf_ae_stop(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_fw_loader_data *loader_data = accel_dev->fw_loader;
	काष्ठा adf_hw_device_data *hw_data = accel_dev->hw_device;
	u32 ae_ctr, ae, max_aes = GET_MAX_ACCELENGINES(accel_dev);

	अगर (!hw_data->fw_name)
		वापस 0;

	क्रम (ae = 0, ae_ctr = 0; ae < max_aes; ae++) अणु
		अगर (hw_data->ae_mask & (1 << ae)) अणु
			qat_hal_stop(loader_data->fw_loader, ae, 0xFF);
			ae_ctr++;
		पूर्ण
	पूर्ण
	dev_info(&GET_DEV(accel_dev),
		 "qat_dev%d stopped %d acceleration engines\n",
		 accel_dev->accel_id, ae_ctr);
	वापस 0;
पूर्ण

अटल पूर्णांक adf_ae_reset(काष्ठा adf_accel_dev *accel_dev, पूर्णांक ae)
अणु
	काष्ठा adf_fw_loader_data *loader_data = accel_dev->fw_loader;

	qat_hal_reset(loader_data->fw_loader);
	अगर (qat_hal_clr_reset(loader_data->fw_loader))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक adf_ae_init(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_fw_loader_data *loader_data;
	काष्ठा adf_hw_device_data *hw_device = accel_dev->hw_device;

	अगर (!hw_device->fw_name)
		वापस 0;

	loader_data = kzalloc(माप(*loader_data), GFP_KERNEL);
	अगर (!loader_data)
		वापस -ENOMEM;

	accel_dev->fw_loader = loader_data;
	अगर (qat_hal_init(accel_dev)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to init the AEs\n");
		kमुक्त(loader_data);
		वापस -EFAULT;
	पूर्ण
	अगर (adf_ae_reset(accel_dev, 0)) अणु
		dev_err(&GET_DEV(accel_dev), "Failed to reset the AEs\n");
		qat_hal_deinit(loader_data->fw_loader);
		kमुक्त(loader_data);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक adf_ae_shutकरोwn(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_fw_loader_data *loader_data = accel_dev->fw_loader;
	काष्ठा adf_hw_device_data *hw_device = accel_dev->hw_device;

	अगर (!hw_device->fw_name)
		वापस 0;

	qat_hal_deinit(loader_data->fw_loader);
	kमुक्त(accel_dev->fw_loader);
	accel_dev->fw_loader = शून्य;
	वापस 0;
पूर्ण
