<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <adf_accel_devices.h>
#समावेश <adf_pf2vf_msg.h>
#समावेश <adf_common_drv.h>
#समावेश <adf_gen2_hw_data.h>
#समावेश "adf_dh895xcc_hw_data.h"
#समावेश "icp_qat_hw.h"

/* Worker thपढ़ो to service arbiter mappings */
अटल स्थिर u32 thrd_to_arb_map[ADF_DH895XCC_MAX_ACCELENGINES] = अणु
	0x12222AAA, 0x11666666, 0x12222AAA, 0x11666666,
	0x12222AAA, 0x11222222, 0x12222AAA, 0x11222222,
	0x12222AAA, 0x11222222, 0x12222AAA, 0x11222222
पूर्ण;

अटल काष्ठा adf_hw_device_class dh895xcc_class = अणु
	.name = ADF_DH895XCC_DEVICE_NAME,
	.type = DEV_DH895XCC,
	.instances = 0
पूर्ण;

अटल u32 get_accel_mask(काष्ठा adf_hw_device_data *self)
अणु
	u32 fuses = self->fuses;

	वापस ~fuses >> ADF_DH895XCC_ACCELERATORS_REG_OFFSET &
			 ADF_DH895XCC_ACCELERATORS_MASK;
पूर्ण

अटल u32 get_ae_mask(काष्ठा adf_hw_device_data *self)
अणु
	u32 fuses = self->fuses;

	वापस ~fuses & ADF_DH895XCC_ACCELENGINES_MASK;
पूर्ण

अटल u32 get_num_accels(काष्ठा adf_hw_device_data *self)
अणु
	u32 i, ctr = 0;

	अगर (!self || !self->accel_mask)
		वापस 0;

	क्रम (i = 0; i < ADF_DH895XCC_MAX_ACCELERATORS; i++) अणु
		अगर (self->accel_mask & (1 << i))
			ctr++;
	पूर्ण
	वापस ctr;
पूर्ण

अटल u32 get_num_aes(काष्ठा adf_hw_device_data *self)
अणु
	u32 i, ctr = 0;

	अगर (!self || !self->ae_mask)
		वापस 0;

	क्रम (i = 0; i < ADF_DH895XCC_MAX_ACCELENGINES; i++) अणु
		अगर (self->ae_mask & (1 << i))
			ctr++;
	पूर्ण
	वापस ctr;
पूर्ण

अटल u32 get_misc_bar_id(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_DH895XCC_PMISC_BAR;
पूर्ण

अटल u32 get_etr_bar_id(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_DH895XCC_ETR_BAR;
पूर्ण

अटल u32 get_sram_bar_id(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_DH895XCC_SRAM_BAR;
पूर्ण

अटल u32 get_accel_cap(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा pci_dev *pdev = accel_dev->accel_pci_dev.pci_dev;
	u32 capabilities;
	u32 legfuses;

	capabilities = ICP_ACCEL_CAPABILITIES_CRYPTO_SYMMETRIC |
		       ICP_ACCEL_CAPABILITIES_CRYPTO_ASYMMETRIC |
		       ICP_ACCEL_CAPABILITIES_AUTHENTICATION;

	/* Read accelerator capabilities mask */
	pci_पढ़ो_config_dword(pdev, ADF_DEVICE_LEGFUSE_OFFSET, &legfuses);

	अगर (legfuses & ICP_ACCEL_MASK_CIPHER_SLICE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_CRYPTO_SYMMETRIC;
	अगर (legfuses & ICP_ACCEL_MASK_PKE_SLICE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_CRYPTO_ASYMMETRIC;
	अगर (legfuses & ICP_ACCEL_MASK_AUTH_SLICE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_AUTHENTICATION;

	वापस capabilities;
पूर्ण

अटल क्रमागत dev_sku_info get_sku(काष्ठा adf_hw_device_data *self)
अणु
	पूर्णांक sku = (self->fuses & ADF_DH895XCC_FUSECTL_SKU_MASK)
	    >> ADF_DH895XCC_FUSECTL_SKU_SHIFT;

	चयन (sku) अणु
	हाल ADF_DH895XCC_FUSECTL_SKU_1:
		वापस DEV_SKU_1;
	हाल ADF_DH895XCC_FUSECTL_SKU_2:
		वापस DEV_SKU_2;
	हाल ADF_DH895XCC_FUSECTL_SKU_3:
		वापस DEV_SKU_3;
	हाल ADF_DH895XCC_FUSECTL_SKU_4:
		वापस DEV_SKU_4;
	शेष:
		वापस DEV_SKU_UNKNOWN;
	पूर्ण
	वापस DEV_SKU_UNKNOWN;
पूर्ण

अटल स्थिर u32 *adf_get_arbiter_mapping(व्योम)
अणु
	वापस thrd_to_arb_map;
पूर्ण

अटल u32 get_pf2vf_offset(u32 i)
अणु
	वापस ADF_DH895XCC_PF2VF_OFFSET(i);
पूर्ण

अटल u32 get_vपूर्णांकmsk_offset(u32 i)
अणु
	वापस ADF_DH895XCC_VINTMSK_OFFSET(i);
पूर्ण

अटल व्योम adf_enable_error_correction(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_hw_device_data *hw_device = accel_dev->hw_device;
	काष्ठा adf_bar *misc_bar = &GET_BARS(accel_dev)[ADF_DH895XCC_PMISC_BAR];
	अचिन्हित दीर्घ accel_mask = hw_device->accel_mask;
	अचिन्हित दीर्घ ae_mask = hw_device->ae_mask;
	व्योम __iomem *csr = misc_bar->virt_addr;
	अचिन्हित पूर्णांक val, i;

	/* Enable Accel Engine error detection & correction */
	क्रम_each_set_bit(i, &ae_mask, GET_MAX_ACCELENGINES(accel_dev)) अणु
		val = ADF_CSR_RD(csr, ADF_DH895XCC_AE_CTX_ENABLES(i));
		val |= ADF_DH895XCC_ENABLE_AE_ECC_ERR;
		ADF_CSR_WR(csr, ADF_DH895XCC_AE_CTX_ENABLES(i), val);
		val = ADF_CSR_RD(csr, ADF_DH895XCC_AE_MISC_CONTROL(i));
		val |= ADF_DH895XCC_ENABLE_AE_ECC_PARITY_CORR;
		ADF_CSR_WR(csr, ADF_DH895XCC_AE_MISC_CONTROL(i), val);
	पूर्ण

	/* Enable shared memory error detection & correction */
	क्रम_each_set_bit(i, &accel_mask, ADF_DH895XCC_MAX_ACCELERATORS) अणु
		val = ADF_CSR_RD(csr, ADF_DH895XCC_UERRSSMSH(i));
		val |= ADF_DH895XCC_ERRSSMSH_EN;
		ADF_CSR_WR(csr, ADF_DH895XCC_UERRSSMSH(i), val);
		val = ADF_CSR_RD(csr, ADF_DH895XCC_CERRSSMSH(i));
		val |= ADF_DH895XCC_ERRSSMSH_EN;
		ADF_CSR_WR(csr, ADF_DH895XCC_CERRSSMSH(i), val);
	पूर्ण
पूर्ण

अटल व्योम adf_enable_पूर्णांकs(काष्ठा adf_accel_dev *accel_dev)
अणु
	व्योम __iomem *addr;

	addr = (&GET_BARS(accel_dev)[ADF_DH895XCC_PMISC_BAR])->virt_addr;

	/* Enable bundle and misc पूर्णांकerrupts */
	ADF_CSR_WR(addr, ADF_DH895XCC_SMIAPF0_MASK_OFFSET,
		   accel_dev->pf.vf_info ? 0 :
			BIT_ULL(GET_MAX_BANKS(accel_dev)) - 1);
	ADF_CSR_WR(addr, ADF_DH895XCC_SMIAPF1_MASK_OFFSET,
		   ADF_DH895XCC_SMIA1_MASK);
पूर्ण

अटल पूर्णांक adf_pf_enable_vf2pf_comms(काष्ठा adf_accel_dev *accel_dev)
अणु
	वापस 0;
पूर्ण

अटल व्योम configure_iov_thपढ़ोs(काष्ठा adf_accel_dev *accel_dev, bool enable)
अणु
	adf_gen2_cfg_iov_thds(accel_dev, enable,
			      ADF_DH895XCC_AE2FUNC_MAP_GRP_A_NUM_REGS,
			      ADF_DH895XCC_AE2FUNC_MAP_GRP_B_NUM_REGS);
पूर्ण

व्योम adf_init_hw_data_dh895xcc(काष्ठा adf_hw_device_data *hw_data)
अणु
	hw_data->dev_class = &dh895xcc_class;
	hw_data->instance_id = dh895xcc_class.instances++;
	hw_data->num_banks = ADF_DH895XCC_ETR_MAX_BANKS;
	hw_data->num_rings_per_bank = ADF_ETR_MAX_RINGS_PER_BANK;
	hw_data->num_accel = ADF_DH895XCC_MAX_ACCELERATORS;
	hw_data->num_logical_accel = 1;
	hw_data->num_engines = ADF_DH895XCC_MAX_ACCELENGINES;
	hw_data->tx_rx_gap = ADF_DH895XCC_RX_RINGS_OFFSET;
	hw_data->tx_rings_mask = ADF_DH895XCC_TX_RINGS_MASK;
	hw_data->alloc_irq = adf_isr_resource_alloc;
	hw_data->मुक्त_irq = adf_isr_resource_मुक्त;
	hw_data->enable_error_correction = adf_enable_error_correction;
	hw_data->get_accel_mask = get_accel_mask;
	hw_data->get_ae_mask = get_ae_mask;
	hw_data->get_accel_cap = get_accel_cap;
	hw_data->get_num_accels = get_num_accels;
	hw_data->get_num_aes = get_num_aes;
	hw_data->get_etr_bar_id = get_etr_bar_id;
	hw_data->get_misc_bar_id = get_misc_bar_id;
	hw_data->get_pf2vf_offset = get_pf2vf_offset;
	hw_data->get_vपूर्णांकmsk_offset = get_vपूर्णांकmsk_offset;
	hw_data->get_admin_info = adf_gen2_get_admin_info;
	hw_data->get_arb_info = adf_gen2_get_arb_info;
	hw_data->get_sram_bar_id = get_sram_bar_id;
	hw_data->get_sku = get_sku;
	hw_data->fw_name = ADF_DH895XCC_FW;
	hw_data->fw_mmp_name = ADF_DH895XCC_MMP;
	hw_data->init_admin_comms = adf_init_admin_comms;
	hw_data->निकास_admin_comms = adf_निकास_admin_comms;
	hw_data->configure_iov_thपढ़ोs = configure_iov_thपढ़ोs;
	hw_data->disable_iov = adf_disable_sriov;
	hw_data->send_admin_init = adf_send_admin_init;
	hw_data->init_arb = adf_init_arb;
	hw_data->निकास_arb = adf_निकास_arb;
	hw_data->get_arb_mapping = adf_get_arbiter_mapping;
	hw_data->enable_पूर्णांकs = adf_enable_पूर्णांकs;
	hw_data->enable_vf2pf_comms = adf_pf_enable_vf2pf_comms;
	hw_data->reset_device = adf_reset_sbr;
	hw_data->min_iov_compat_ver = ADF_PFVF_COMPATIBILITY_VERSION;
	adf_gen2_init_hw_csr_ops(&hw_data->csr_ops);
पूर्ण

व्योम adf_clean_hw_data_dh895xcc(काष्ठा adf_hw_device_data *hw_data)
अणु
	hw_data->dev_class->instances--;
पूर्ण
