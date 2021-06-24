<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2020 Intel Corporation */
#समावेश <adf_accel_devices.h>
#समावेश <adf_common_drv.h>
#समावेश <adf_pf2vf_msg.h>
#समावेश <adf_gen4_hw_data.h>
#समावेश "adf_4xxx_hw_data.h"
#समावेश "icp_qat_hw.h"

काष्ठा adf_fw_config अणु
	u32 ae_mask;
	अक्षर *obj_name;
पूर्ण;

अटल काष्ठा adf_fw_config adf_4xxx_fw_config[] = अणु
	अणु0xF0, ADF_4XXX_SYM_OBJपूर्ण,
	अणु0xF, ADF_4XXX_ASYM_OBJपूर्ण,
	अणु0x100, ADF_4XXX_ADMIN_OBJपूर्ण,
पूर्ण;

/* Worker thपढ़ो to service arbiter mappings */
अटल स्थिर u32 thrd_to_arb_map[ADF_4XXX_MAX_ACCELENGINES] = अणु
	0x5555555, 0x5555555, 0x5555555, 0x5555555,
	0xAAAAAAA, 0xAAAAAAA, 0xAAAAAAA, 0xAAAAAAA,
	0x0
पूर्ण;

अटल काष्ठा adf_hw_device_class adf_4xxx_class = अणु
	.name = ADF_4XXX_DEVICE_NAME,
	.type = DEV_4XXX,
	.instances = 0,
पूर्ण;

अटल u32 get_accel_mask(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_4XXX_ACCELERATORS_MASK;
पूर्ण

अटल u32 get_ae_mask(काष्ठा adf_hw_device_data *self)
अणु
	u32 me_disable = self->fuses;

	वापस ~me_disable & ADF_4XXX_ACCELENGINES_MASK;
पूर्ण

अटल u32 get_num_accels(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_4XXX_MAX_ACCELERATORS;
पूर्ण

अटल u32 get_num_aes(काष्ठा adf_hw_device_data *self)
अणु
	अगर (!self || !self->ae_mask)
		वापस 0;

	वापस hweight32(self->ae_mask);
पूर्ण

अटल u32 get_misc_bar_id(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_4XXX_PMISC_BAR;
पूर्ण

अटल u32 get_etr_bar_id(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_4XXX_ETR_BAR;
पूर्ण

अटल u32 get_sram_bar_id(काष्ठा adf_hw_device_data *self)
अणु
	वापस ADF_4XXX_SRAM_BAR;
पूर्ण

/*
 * The vector routing table is used to select the MSI-X entry to use क्रम each
 * पूर्णांकerrupt source.
 * The first ADF_4XXX_ETR_MAX_BANKS entries correspond to ring पूर्णांकerrupts.
 * The final entry corresponds to VF2PF or error पूर्णांकerrupts.
 * This vector table could be used to configure one MSI-X entry to be shared
 * between multiple पूर्णांकerrupt sources.
 *
 * The शेष routing is set to have a one to one correspondence between the
 * पूर्णांकerrupt source and the MSI-X entry used.
 */
अटल व्योम set_msix_शेष_rttable(काष्ठा adf_accel_dev *accel_dev)
अणु
	व्योम __iomem *csr;
	पूर्णांक i;

	csr = (&GET_BARS(accel_dev)[ADF_4XXX_PMISC_BAR])->virt_addr;
	क्रम (i = 0; i <= ADF_4XXX_ETR_MAX_BANKS; i++)
		ADF_CSR_WR(csr, ADF_4XXX_MSIX_RTTABLE_OFFSET(i), i);
पूर्ण

अटल u32 get_accel_cap(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा pci_dev *pdev = accel_dev->accel_pci_dev.pci_dev;
	u32 fusectl1;
	u32 capabilities = ICP_ACCEL_CAPABILITIES_CRYPTO_SYMMETRIC |
			   ICP_ACCEL_CAPABILITIES_CRYPTO_ASYMMETRIC |
			   ICP_ACCEL_CAPABILITIES_AUTHENTICATION |
			   ICP_ACCEL_CAPABILITIES_AES_V2;

	/* Read accelerator capabilities mask */
	pci_पढ़ो_config_dword(pdev, ADF_4XXX_FUSECTL1_OFFSET, &fusectl1);

	अगर (fusectl1 & ICP_ACCEL_4XXX_MASK_CIPHER_SLICE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_CRYPTO_SYMMETRIC;
	अगर (fusectl1 & ICP_ACCEL_4XXX_MASK_AUTH_SLICE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_AUTHENTICATION;
	अगर (fusectl1 & ICP_ACCEL_4XXX_MASK_PKE_SLICE)
		capabilities &= ~ICP_ACCEL_CAPABILITIES_CRYPTO_ASYMMETRIC;

	वापस capabilities;
पूर्ण

अटल क्रमागत dev_sku_info get_sku(काष्ठा adf_hw_device_data *self)
अणु
	वापस DEV_SKU_1;
पूर्ण

अटल स्थिर u32 *adf_get_arbiter_mapping(व्योम)
अणु
	वापस thrd_to_arb_map;
पूर्ण

अटल व्योम get_arb_info(काष्ठा arb_info *arb_info)
अणु
	arb_info->arb_cfg = ADF_4XXX_ARB_CONFIG;
	arb_info->arb_offset = ADF_4XXX_ARB_OFFSET;
	arb_info->wt2sam_offset = ADF_4XXX_ARB_WRK_2_SER_MAP_OFFSET;
पूर्ण

अटल व्योम get_admin_info(काष्ठा admin_info *admin_csrs_info)
अणु
	admin_csrs_info->mailbox_offset = ADF_4XXX_MAILBOX_BASE_OFFSET;
	admin_csrs_info->admin_msg_ur = ADF_4XXX_ADMINMSGUR_OFFSET;
	admin_csrs_info->admin_msg_lr = ADF_4XXX_ADMINMSGLR_OFFSET;
पूर्ण

अटल व्योम adf_enable_error_correction(काष्ठा adf_accel_dev *accel_dev)
अणु
	काष्ठा adf_bar *misc_bar = &GET_BARS(accel_dev)[ADF_4XXX_PMISC_BAR];
	व्योम __iomem *csr = misc_bar->virt_addr;

	/* Enable all in errsou3 except VFLR notअगरication on host */
	ADF_CSR_WR(csr, ADF_4XXX_ERRMSK3, ADF_4XXX_VFLNOTIFY);
पूर्ण

अटल व्योम adf_enable_पूर्णांकs(काष्ठा adf_accel_dev *accel_dev)
अणु
	व्योम __iomem *addr;

	addr = (&GET_BARS(accel_dev)[ADF_4XXX_PMISC_BAR])->virt_addr;

	/* Enable bundle पूर्णांकerrupts */
	ADF_CSR_WR(addr, ADF_4XXX_SMIAPF_RP_X0_MASK_OFFSET, 0);
	ADF_CSR_WR(addr, ADF_4XXX_SMIAPF_RP_X1_MASK_OFFSET, 0);

	/* Enable misc पूर्णांकerrupts */
	ADF_CSR_WR(addr, ADF_4XXX_SMIAPF_MASK_OFFSET, 0);
पूर्ण

अटल पूर्णांक adf_pf_enable_vf2pf_comms(काष्ठा adf_accel_dev *accel_dev)
अणु
	वापस 0;
पूर्ण

अटल u32 uof_get_num_objs(व्योम)
अणु
	वापस ARRAY_SIZE(adf_4xxx_fw_config);
पूर्ण

अटल अक्षर *uof_get_name(u32 obj_num)
अणु
	वापस adf_4xxx_fw_config[obj_num].obj_name;
पूर्ण

अटल u32 uof_get_ae_mask(u32 obj_num)
अणु
	वापस adf_4xxx_fw_config[obj_num].ae_mask;
पूर्ण

व्योम adf_init_hw_data_4xxx(काष्ठा adf_hw_device_data *hw_data)
अणु
	hw_data->dev_class = &adf_4xxx_class;
	hw_data->instance_id = adf_4xxx_class.instances++;
	hw_data->num_banks = ADF_4XXX_ETR_MAX_BANKS;
	hw_data->num_rings_per_bank = ADF_4XXX_NUM_RINGS_PER_BANK;
	hw_data->num_accel = ADF_4XXX_MAX_ACCELERATORS;
	hw_data->num_engines = ADF_4XXX_MAX_ACCELENGINES;
	hw_data->num_logical_accel = 1;
	hw_data->tx_rx_gap = ADF_4XXX_RX_RINGS_OFFSET;
	hw_data->tx_rings_mask = ADF_4XXX_TX_RINGS_MASK;
	hw_data->alloc_irq = adf_isr_resource_alloc;
	hw_data->मुक्त_irq = adf_isr_resource_मुक्त;
	hw_data->enable_error_correction = adf_enable_error_correction;
	hw_data->get_accel_mask = get_accel_mask;
	hw_data->get_ae_mask = get_ae_mask;
	hw_data->get_num_accels = get_num_accels;
	hw_data->get_num_aes = get_num_aes;
	hw_data->get_sram_bar_id = get_sram_bar_id;
	hw_data->get_etr_bar_id = get_etr_bar_id;
	hw_data->get_misc_bar_id = get_misc_bar_id;
	hw_data->get_arb_info = get_arb_info;
	hw_data->get_admin_info = get_admin_info;
	hw_data->get_accel_cap = get_accel_cap;
	hw_data->get_sku = get_sku;
	hw_data->fw_name = ADF_4XXX_FW;
	hw_data->fw_mmp_name = ADF_4XXX_MMP;
	hw_data->init_admin_comms = adf_init_admin_comms;
	hw_data->निकास_admin_comms = adf_निकास_admin_comms;
	hw_data->disable_iov = adf_disable_sriov;
	hw_data->send_admin_init = adf_send_admin_init;
	hw_data->init_arb = adf_init_arb;
	hw_data->निकास_arb = adf_निकास_arb;
	hw_data->get_arb_mapping = adf_get_arbiter_mapping;
	hw_data->enable_पूर्णांकs = adf_enable_पूर्णांकs;
	hw_data->enable_vf2pf_comms = adf_pf_enable_vf2pf_comms;
	hw_data->reset_device = adf_reset_flr;
	hw_data->min_iov_compat_ver = ADF_PFVF_COMPATIBILITY_VERSION;
	hw_data->admin_ae_mask = ADF_4XXX_ADMIN_AE_MASK;
	hw_data->uof_get_num_objs = uof_get_num_objs;
	hw_data->uof_get_name = uof_get_name;
	hw_data->uof_get_ae_mask = uof_get_ae_mask;
	hw_data->set_msix_rttable = set_msix_शेष_rttable;
	hw_data->set_ssm_wdसमयr = adf_gen4_set_ssm_wdसमयr;

	adf_gen4_init_hw_csr_ops(&hw_data->csr_ops);
पूर्ण

व्योम adf_clean_hw_data_4xxx(काष्ठा adf_hw_device_data *hw_data)
अणु
	hw_data->dev_class->instances--;
पूर्ण
