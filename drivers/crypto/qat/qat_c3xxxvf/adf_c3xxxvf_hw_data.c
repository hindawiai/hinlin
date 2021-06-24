<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2015 - 2020 Intel Corporation */
#समावेश <adf_accel_devices.h>
#समावेश <adf_pf2vf_msg.h>
#समावेश <adf_common_drv.h>
#समावेश <adf_gen2_hw_data.h>
#समावेश "adf_c3xxxvf_hw_data.h"

अटल काष्ठा adf_hw_device_class c3xxxiov_class = अणु
	.name = ADF_C3XXXVF_DEVICE_NAME,
	.type = DEV_C3XXXVF,
	.instances = 0
पूर्ण;

अटल u32 get_accel_mask(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_C3XXXIOV_ACCELERATORS_MASK;
पूर्ण

अटल u32 get_ae_mask(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_C3XXXIOV_ACCELENGINES_MASK;
पूर्ण

अटल u32 get_num_accels(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_C3XXXIOV_MAX_ACCELERATORS;
पूर्ण

अटल u32 get_num_aes(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_C3XXXIOV_MAX_ACCELENGINES;
पूर्ण

अटल u32 get_misc_bar_id(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_C3XXXIOV_PMISC_BAR;
पूर्ण

अटल u32 get_etr_bar_id(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_C3XXXIOV_ETR_BAR;
पूर्ण

अटल क्रमागत dev_sku_info get_sku(काष्ठा adf_hw_device_data *self)
अणु
	वापस DEV_SKU_VF;
पूर्ण

अटल u32 get_pf2vf_offset(u32 i)
अणु
	वापस ADF_C3XXXIOV_PF2VF_OFFSET;
पूर्ण

अटल u32 get_vपूर्णांकmsk_offset(u32 i)
अणु
	वापस ADF_C3XXXIOV_VINTMSK_OFFSET;
पूर्ण

अटल पूर्णांक adf_vf_पूर्णांक_noop(काष्ठा adf_accel_dev *accel_dev)
अणु
	वापस 0;
पूर्ण

अटल व्योम adf_vf_व्योम_noop(काष्ठा adf_accel_dev *accel_dev)
अणु
पूर्ण

व्योम adf_init_hw_data_c3xxxiov(काष्ठा adf_hw_device_data *hw_data)
अणु
	hw_data->dev_class = &c3xxxiov_class;
	hw_data->num_banks = ADF_C3XXXIOV_ETR_MAX_BANKS;
	hw_data->num_rings_per_bank = ADF_ETR_MAX_RINGS_PER_BANK;
	hw_data->num_accel = ADF_C3XXXIOV_MAX_ACCELERATORS;
	hw_data->num_logical_accel = 1;
	hw_data->num_engines = ADF_C3XXXIOV_MAX_ACCELENGINES;
	hw_data->tx_rx_gap = ADF_C3XXXIOV_RX_RINGS_OFFSET;
	hw_data->tx_rings_mask = ADF_C3XXXIOV_TX_RINGS_MASK;
	hw_data->alloc_irq = adf_vf_isr_resource_alloc;
	hw_data->मुक्त_irq = adf_vf_isr_resource_मुक्त;
	hw_data->enable_error_correction = adf_vf_व्योम_noop;
	hw_data->init_admin_comms = adf_vf_पूर्णांक_noop;
	hw_data->निकास_admin_comms = adf_vf_व्योम_noop;
	hw_data->send_admin_init = adf_vf2pf_init;
	hw_data->init_arb = adf_vf_पूर्णांक_noop;
	hw_data->निकास_arb = adf_vf_व्योम_noop;
	hw_data->disable_iov = adf_vf2pf_shutकरोwn;
	hw_data->get_accel_mask = get_accel_mask;
	hw_data->get_ae_mask = get_ae_mask;
	hw_data->get_num_accels = get_num_accels;
	hw_data->get_num_aes = get_num_aes;
	hw_data->get_etr_bar_id = get_etr_bar_id;
	hw_data->get_misc_bar_id = get_misc_bar_id;
	hw_data->get_pf2vf_offset = get_pf2vf_offset;
	hw_data->get_vपूर्णांकmsk_offset = get_vपूर्णांकmsk_offset;
	hw_data->get_sku = get_sku;
	hw_data->enable_पूर्णांकs = adf_vf_व्योम_noop;
	hw_data->enable_vf2pf_comms = adf_enable_vf2pf_comms;
	hw_data->min_iov_compat_ver = ADF_PFVF_COMPATIBILITY_VERSION;
	hw_data->dev_class->instances++;
	adf_devmgr_update_class_index(hw_data);
	adf_gen2_init_hw_csr_ops(&hw_data->csr_ops);
पूर्ण

व्योम adf_clean_hw_data_c3xxxiov(काष्ठा adf_hw_device_data *hw_data)
अणु
	hw_data->dev_class->instances--;
	adf_devmgr_update_class_index(hw_data);
पूर्ण
