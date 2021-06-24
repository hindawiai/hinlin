<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_ACCEL_DEVICES_H_
#घोषणा ADF_ACCEL_DEVICES_H_
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/ratelimit.h>
#समावेश "adf_cfg_common.h"

#घोषणा ADF_DH895XCC_DEVICE_NAME "dh895xcc"
#घोषणा ADF_DH895XCCVF_DEVICE_NAME "dh895xccvf"
#घोषणा ADF_C62X_DEVICE_NAME "c6xx"
#घोषणा ADF_C62XVF_DEVICE_NAME "c6xxvf"
#घोषणा ADF_C3XXX_DEVICE_NAME "c3xxx"
#घोषणा ADF_C3XXXVF_DEVICE_NAME "c3xxxvf"
#घोषणा ADF_4XXX_DEVICE_NAME "4xxx"
#घोषणा ADF_4XXX_PCI_DEVICE_ID 0x4940
#घोषणा ADF_4XXXIOV_PCI_DEVICE_ID 0x4941
#घोषणा ADF_ERRSOU3 (0x3A000 + 0x0C)
#घोषणा ADF_ERRSOU5 (0x3A000 + 0xD8)
#घोषणा ADF_DEVICE_FUSECTL_OFFSET 0x40
#घोषणा ADF_DEVICE_LEGFUSE_OFFSET 0x4C
#घोषणा ADF_DEVICE_FUSECTL_MASK 0x80000000
#घोषणा ADF_PCI_MAX_BARS 3
#घोषणा ADF_DEVICE_NAME_LENGTH 32
#घोषणा ADF_ETR_MAX_RINGS_PER_BANK 16
#घोषणा ADF_MAX_MSIX_VECTOR_NAME 16
#घोषणा ADF_DEVICE_NAME_PREFIX "qat_"

क्रमागत adf_accel_capabilities अणु
	ADF_ACCEL_CAPABILITIES_शून्य = 0,
	ADF_ACCEL_CAPABILITIES_CRYPTO_SYMMETRIC = 1,
	ADF_ACCEL_CAPABILITIES_CRYPTO_ASYMMETRIC = 2,
	ADF_ACCEL_CAPABILITIES_CIPHER = 4,
	ADF_ACCEL_CAPABILITIES_AUTHENTICATION = 8,
	ADF_ACCEL_CAPABILITIES_COMPRESSION = 32,
	ADF_ACCEL_CAPABILITIES_LZS_COMPRESSION = 64,
	ADF_ACCEL_CAPABILITIES_RANDOM_NUMBER = 128
पूर्ण;

काष्ठा adf_bar अणु
	resource_माप_प्रकार base_addr;
	व्योम __iomem *virt_addr;
	resource_माप_प्रकार size;
पूर्ण __packed;

काष्ठा adf_accel_msix अणु
	काष्ठा msix_entry *entries;
	अक्षर **names;
	u32 num_entries;
पूर्ण __packed;

काष्ठा adf_accel_pci अणु
	काष्ठा pci_dev *pci_dev;
	काष्ठा adf_accel_msix msix_entries;
	काष्ठा adf_bar pci_bars[ADF_PCI_MAX_BARS];
	u8 revid;
	u8 sku;
पूर्ण __packed;

क्रमागत dev_state अणु
	DEV_DOWN = 0,
	DEV_UP
पूर्ण;

क्रमागत dev_sku_info अणु
	DEV_SKU_1 = 0,
	DEV_SKU_2,
	DEV_SKU_3,
	DEV_SKU_4,
	DEV_SKU_VF,
	DEV_SKU_UNKNOWN,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *get_sku_info(क्रमागत dev_sku_info info)
अणु
	चयन (info) अणु
	हाल DEV_SKU_1:
		वापस "SKU1";
	हाल DEV_SKU_2:
		वापस "SKU2";
	हाल DEV_SKU_3:
		वापस "SKU3";
	हाल DEV_SKU_4:
		वापस "SKU4";
	हाल DEV_SKU_VF:
		वापस "SKUVF";
	हाल DEV_SKU_UNKNOWN:
	शेष:
		अवरोध;
	पूर्ण
	वापस "Unknown SKU";
पूर्ण

काष्ठा adf_hw_device_class अणु
	स्थिर अक्षर *name;
	स्थिर क्रमागत adf_device_type type;
	u32 instances;
पूर्ण __packed;

काष्ठा arb_info अणु
	u32 arb_cfg;
	u32 arb_offset;
	u32 wt2sam_offset;
पूर्ण;

काष्ठा admin_info अणु
	u32 admin_msg_ur;
	u32 admin_msg_lr;
	u32 mailbox_offset;
पूर्ण;

काष्ठा adf_hw_csr_ops अणु
	u64 (*build_csr_ring_base_addr)(dma_addr_t addr, u32 size);
	u32 (*पढ़ो_csr_ring_head)(व्योम __iomem *csr_base_addr, u32 bank,
				  u32 ring);
	व्योम (*ग_लिखो_csr_ring_head)(व्योम __iomem *csr_base_addr, u32 bank,
				    u32 ring, u32 value);
	u32 (*पढ़ो_csr_ring_tail)(व्योम __iomem *csr_base_addr, u32 bank,
				  u32 ring);
	व्योम (*ग_लिखो_csr_ring_tail)(व्योम __iomem *csr_base_addr, u32 bank,
				    u32 ring, u32 value);
	u32 (*पढ़ो_csr_e_stat)(व्योम __iomem *csr_base_addr, u32 bank);
	व्योम (*ग_लिखो_csr_ring_config)(व्योम __iomem *csr_base_addr, u32 bank,
				      u32 ring, u32 value);
	व्योम (*ग_लिखो_csr_ring_base)(व्योम __iomem *csr_base_addr, u32 bank,
				    u32 ring, dma_addr_t addr);
	व्योम (*ग_लिखो_csr_पूर्णांक_flag)(व्योम __iomem *csr_base_addr, u32 bank,
				   u32 value);
	व्योम (*ग_लिखो_csr_पूर्णांक_srcsel)(व्योम __iomem *csr_base_addr, u32 bank);
	व्योम (*ग_लिखो_csr_पूर्णांक_col_en)(व्योम __iomem *csr_base_addr, u32 bank,
				     u32 value);
	व्योम (*ग_लिखो_csr_पूर्णांक_col_ctl)(व्योम __iomem *csr_base_addr, u32 bank,
				      u32 value);
	व्योम (*ग_लिखो_csr_पूर्णांक_flag_and_col)(व्योम __iomem *csr_base_addr,
					   u32 bank, u32 value);
	व्योम (*ग_लिखो_csr_ring_srv_arb_en)(व्योम __iomem *csr_base_addr, u32 bank,
					  u32 value);
पूर्ण;

काष्ठा adf_cfg_device_data;
काष्ठा adf_accel_dev;
काष्ठा adf_etr_data;
काष्ठा adf_etr_ring_data;

काष्ठा adf_hw_device_data अणु
	काष्ठा adf_hw_device_class *dev_class;
	u32 (*get_accel_mask)(काष्ठा adf_hw_device_data *self);
	u32 (*get_ae_mask)(काष्ठा adf_hw_device_data *self);
	u32 (*get_accel_cap)(काष्ठा adf_accel_dev *accel_dev);
	u32 (*get_sram_bar_id)(काष्ठा adf_hw_device_data *self);
	u32 (*get_misc_bar_id)(काष्ठा adf_hw_device_data *self);
	u32 (*get_etr_bar_id)(काष्ठा adf_hw_device_data *self);
	u32 (*get_num_aes)(काष्ठा adf_hw_device_data *self);
	u32 (*get_num_accels)(काष्ठा adf_hw_device_data *self);
	u32 (*get_pf2vf_offset)(u32 i);
	u32 (*get_vपूर्णांकmsk_offset)(u32 i);
	व्योम (*get_arb_info)(काष्ठा arb_info *arb_csrs_info);
	व्योम (*get_admin_info)(काष्ठा admin_info *admin_csrs_info);
	क्रमागत dev_sku_info (*get_sku)(काष्ठा adf_hw_device_data *self);
	पूर्णांक (*alloc_irq)(काष्ठा adf_accel_dev *accel_dev);
	व्योम (*मुक्त_irq)(काष्ठा adf_accel_dev *accel_dev);
	व्योम (*enable_error_correction)(काष्ठा adf_accel_dev *accel_dev);
	पूर्णांक (*init_admin_comms)(काष्ठा adf_accel_dev *accel_dev);
	व्योम (*निकास_admin_comms)(काष्ठा adf_accel_dev *accel_dev);
	पूर्णांक (*send_admin_init)(काष्ठा adf_accel_dev *accel_dev);
	पूर्णांक (*init_arb)(काष्ठा adf_accel_dev *accel_dev);
	व्योम (*निकास_arb)(काष्ठा adf_accel_dev *accel_dev);
	स्थिर u32 *(*get_arb_mapping)(व्योम);
	व्योम (*disable_iov)(काष्ठा adf_accel_dev *accel_dev);
	व्योम (*configure_iov_thपढ़ोs)(काष्ठा adf_accel_dev *accel_dev,
				      bool enable);
	व्योम (*enable_पूर्णांकs)(काष्ठा adf_accel_dev *accel_dev);
	व्योम (*set_ssm_wdसमयr)(काष्ठा adf_accel_dev *accel_dev);
	पूर्णांक (*enable_vf2pf_comms)(काष्ठा adf_accel_dev *accel_dev);
	व्योम (*reset_device)(काष्ठा adf_accel_dev *accel_dev);
	व्योम (*set_msix_rttable)(काष्ठा adf_accel_dev *accel_dev);
	अक्षर *(*uof_get_name)(u32 obj_num);
	u32 (*uof_get_num_objs)(व्योम);
	u32 (*uof_get_ae_mask)(u32 obj_num);
	काष्ठा adf_hw_csr_ops csr_ops;
	स्थिर अक्षर *fw_name;
	स्थिर अक्षर *fw_mmp_name;
	u32 fuses;
	u32 straps;
	u32 accel_capabilities_mask;
	u32 instance_id;
	u16 accel_mask;
	u32 ae_mask;
	u32 admin_ae_mask;
	u16 tx_rings_mask;
	u8 tx_rx_gap;
	u8 num_banks;
	u8 num_rings_per_bank;
	u8 num_accel;
	u8 num_logical_accel;
	u8 num_engines;
	u8 min_iov_compat_ver;
पूर्ण __packed;

/* CSR ग_लिखो macro */
#घोषणा ADF_CSR_WR(csr_base, csr_offset, val) \
	__raw_ग_लिखोl(val, csr_base + csr_offset)

/* CSR पढ़ो macro */
#घोषणा ADF_CSR_RD(csr_base, csr_offset) __raw_पढ़ोl(csr_base + csr_offset)

#घोषणा GET_DEV(accel_dev) ((accel_dev)->accel_pci_dev.pci_dev->dev)
#घोषणा GET_BARS(accel_dev) ((accel_dev)->accel_pci_dev.pci_bars)
#घोषणा GET_HW_DATA(accel_dev) (accel_dev->hw_device)
#घोषणा GET_MAX_BANKS(accel_dev) (GET_HW_DATA(accel_dev)->num_banks)
#घोषणा GET_NUM_RINGS_PER_BANK(accel_dev) \
	GET_HW_DATA(accel_dev)->num_rings_per_bank
#घोषणा GET_MAX_ACCELENGINES(accel_dev) (GET_HW_DATA(accel_dev)->num_engines)
#घोषणा GET_CSR_OPS(accel_dev) (&(accel_dev)->hw_device->csr_ops)
#घोषणा accel_to_pci_dev(accel_ptr) accel_ptr->accel_pci_dev.pci_dev

काष्ठा adf_admin_comms;
काष्ठा icp_qat_fw_loader_handle;
काष्ठा adf_fw_loader_data अणु
	काष्ठा icp_qat_fw_loader_handle *fw_loader;
	स्थिर काष्ठा firmware *uof_fw;
	स्थिर काष्ठा firmware *mmp_fw;
पूर्ण;

काष्ठा adf_accel_vf_info अणु
	काष्ठा adf_accel_dev *accel_dev;
	काष्ठा tasklet_काष्ठा vf2pf_bh_tasklet;
	काष्ठा mutex pf2vf_lock; /* protect CSR access क्रम PF2VF messages */
	काष्ठा ratelimit_state vf2pf_ratelimit;
	u32 vf_nr;
	bool init;
पूर्ण;

काष्ठा adf_accel_dev अणु
	काष्ठा adf_etr_data *transport;
	काष्ठा adf_hw_device_data *hw_device;
	काष्ठा adf_cfg_device_data *cfg;
	काष्ठा adf_fw_loader_data *fw_loader;
	काष्ठा adf_admin_comms *admin;
	काष्ठा list_head crypto_list;
	अचिन्हित दीर्घ status;
	atomic_t ref_count;
	काष्ठा dentry *debugfs_dir;
	काष्ठा list_head list;
	काष्ठा module *owner;
	काष्ठा adf_accel_pci accel_pci_dev;
	जोड़ अणु
		काष्ठा अणु
			/* vf_info is non-zero when SR-IOV is init'ed */
			काष्ठा adf_accel_vf_info *vf_info;
		पूर्ण pf;
		काष्ठा अणु
			अक्षर *irq_name;
			काष्ठा tasklet_काष्ठा pf2vf_bh_tasklet;
			काष्ठा mutex vf2pf_lock; /* protect CSR access */
			काष्ठा completion iov_msg_completion;
			u8 compatible;
			u8 pf_version;
		पूर्ण vf;
	पूर्ण;
	bool is_vf;
	u32 accel_id;
पूर्ण __packed;
#पूर्ण_अगर
