<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *  Bluetooth support क्रम Intel devices
 *
 *  Copyright (C) 2015  Intel Corporation
 */

/* List of tlv type */
क्रमागत अणु
	INTEL_TLV_CNVI_TOP = 0x10,
	INTEL_TLV_CNVR_TOP,
	INTEL_TLV_CNVI_BT,
	INTEL_TLV_CNVR_BT,
	INTEL_TLV_CNVI_OTP,
	INTEL_TLV_CNVR_OTP,
	INTEL_TLV_DEV_REV_ID,
	INTEL_TLV_USB_VENDOR_ID,
	INTEL_TLV_USB_PRODUCT_ID,
	INTEL_TLV_PCIE_VENDOR_ID,
	INTEL_TLV_PCIE_DEVICE_ID,
	INTEL_TLV_PCIE_SUBSYSTEM_ID,
	INTEL_TLV_IMAGE_TYPE,
	INTEL_TLV_TIME_STAMP,
	INTEL_TLV_BUILD_TYPE,
	INTEL_TLV_BUILD_NUM,
	INTEL_TLV_FW_BUILD_PRODUCT,
	INTEL_TLV_FW_BUILD_HW,
	INTEL_TLV_FW_STEP,
	INTEL_TLV_BT_SPEC,
	INTEL_TLV_MFG_NAME,
	INTEL_TLV_HCI_REV,
	INTEL_TLV_LMP_SUBVER,
	INTEL_TLV_OTP_PATCH_VER,
	INTEL_TLV_SECURE_BOOT,
	INTEL_TLV_KEY_FROM_HDR,
	INTEL_TLV_OTP_LOCK,
	INTEL_TLV_API_LOCK,
	INTEL_TLV_DEBUG_LOCK,
	INTEL_TLV_MIN_FW,
	INTEL_TLV_LIMITED_CCE,
	INTEL_TLV_SBE_TYPE,
	INTEL_TLV_OTP_BDADDR,
	INTEL_TLV_UNLOCKED_STATE
पूर्ण;

काष्ठा पूर्णांकel_tlv अणु
	u8 type;
	u8 len;
	u8 val[];
पूर्ण __packed;

काष्ठा पूर्णांकel_version_tlv अणु
	u32	cnvi_top;
	u32	cnvr_top;
	u32	cnvi_bt;
	u32	cnvr_bt;
	u16	dev_rev_id;
	u8	img_type;
	u16	बारtamp;
	u8	build_type;
	u32	build_num;
	u8	secure_boot;
	u8	otp_lock;
	u8	api_lock;
	u8	debug_lock;
	u8	min_fw_build_nn;
	u8	min_fw_build_cw;
	u8	min_fw_build_yy;
	u8	limited_cce;
	u8	sbe_type;
	bdaddr_t otp_bd_addr;
पूर्ण;

काष्ठा पूर्णांकel_version अणु
	u8 status;
	u8 hw_platक्रमm;
	u8 hw_variant;
	u8 hw_revision;
	u8 fw_variant;
	u8 fw_revision;
	u8 fw_build_num;
	u8 fw_build_ww;
	u8 fw_build_yy;
	u8 fw_patch_num;
पूर्ण __packed;

काष्ठा पूर्णांकel_boot_params अणु
	__u8     status;
	__u8     otp_क्रमmat;
	__u8     otp_content;
	__u8     otp_patch;
	__le16   dev_revid;
	__u8     secure_boot;
	__u8     key_from_hdr;
	__u8     key_type;
	__u8     otp_lock;
	__u8     api_lock;
	__u8     debug_lock;
	bdaddr_t otp_bdaddr;
	__u8     min_fw_build_nn;
	__u8     min_fw_build_cw;
	__u8     min_fw_build_yy;
	__u8     limited_cce;
	__u8     unlocked_state;
पूर्ण __packed;

काष्ठा पूर्णांकel_bootup अणु
	__u8     zero;
	__u8     num_cmds;
	__u8     source;
	__u8     reset_type;
	__u8     reset_reason;
	__u8     ddc_status;
पूर्ण __packed;

काष्ठा पूर्णांकel_secure_send_result अणु
	__u8     result;
	__le16   opcode;
	__u8     status;
पूर्ण __packed;

काष्ठा पूर्णांकel_reset अणु
	__u8     reset_type;
	__u8     patch_enable;
	__u8     ddc_reload;
	__u8     boot_option;
	__le32   boot_param;
पूर्ण __packed;

काष्ठा पूर्णांकel_debug_features अणु
	__u8    page1[16];
पूर्ण __packed;

#घोषणा INTEL_HW_PLATFORM(cnvx_bt)	((u8)(((cnvx_bt) & 0x0000ff00) >> 8))
#घोषणा INTEL_HW_VARIANT(cnvx_bt)	((u8)(((cnvx_bt) & 0x003f0000) >> 16))
#घोषणा INTEL_CNVX_TOP_TYPE(cnvx_top)	((cnvx_top) & 0x00000fff)
#घोषणा INTEL_CNVX_TOP_STEP(cnvx_top)	(((cnvx_top) & 0x0f000000) >> 24)
#घोषणा INTEL_CNVX_TOP_PACK_SWAB(t, s)	__swab16(((__u16)(((t) << 4) | (s))))

#अगर IS_ENABLED(CONFIG_BT_INTEL)

पूर्णांक btपूर्णांकel_check_bdaddr(काष्ठा hci_dev *hdev);
पूर्णांक btपूर्णांकel_enter_mfg(काष्ठा hci_dev *hdev);
पूर्णांक btपूर्णांकel_निकास_mfg(काष्ठा hci_dev *hdev, bool reset, bool patched);
पूर्णांक btपूर्णांकel_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr);
पूर्णांक btपूर्णांकel_set_diag(काष्ठा hci_dev *hdev, bool enable);
पूर्णांक btपूर्णांकel_set_diag_mfg(काष्ठा hci_dev *hdev, bool enable);
व्योम btपूर्णांकel_hw_error(काष्ठा hci_dev *hdev, u8 code);

पूर्णांक btपूर्णांकel_version_info(काष्ठा hci_dev *hdev, काष्ठा पूर्णांकel_version *ver);
पूर्णांक btपूर्णांकel_version_info_tlv(काष्ठा hci_dev *hdev, काष्ठा पूर्णांकel_version_tlv *version);
पूर्णांक btपूर्णांकel_secure_send(काष्ठा hci_dev *hdev, u8 fragment_type, u32 plen,
			स्थिर व्योम *param);
पूर्णांक btपूर्णांकel_load_ddc_config(काष्ठा hci_dev *hdev, स्थिर अक्षर *ddc_name);
पूर्णांक btपूर्णांकel_set_event_mask(काष्ठा hci_dev *hdev, bool debug);
पूर्णांक btपूर्णांकel_set_event_mask_mfg(काष्ठा hci_dev *hdev, bool debug);
पूर्णांक btपूर्णांकel_पढ़ो_version(काष्ठा hci_dev *hdev, काष्ठा पूर्णांकel_version *ver);
पूर्णांक btपूर्णांकel_पढ़ो_version_tlv(काष्ठा hci_dev *hdev, काष्ठा पूर्णांकel_version_tlv *ver);

काष्ठा regmap *btपूर्णांकel_regmap_init(काष्ठा hci_dev *hdev, u16 opcode_पढ़ो,
				   u16 opcode_ग_लिखो);
पूर्णांक btपूर्णांकel_send_पूर्णांकel_reset(काष्ठा hci_dev *hdev, u32 boot_param);
पूर्णांक btपूर्णांकel_पढ़ो_boot_params(काष्ठा hci_dev *hdev,
			     काष्ठा पूर्णांकel_boot_params *params);
पूर्णांक btपूर्णांकel_करोwnload_firmware(काष्ठा hci_dev *dev, काष्ठा पूर्णांकel_version *ver,
			      स्थिर काष्ठा firmware *fw, u32 *boot_param);
पूर्णांक btपूर्णांकel_करोwnload_firmware_newgen(काष्ठा hci_dev *hdev,
				     काष्ठा पूर्णांकel_version_tlv *ver,
				     स्थिर काष्ठा firmware *fw,
				     u32 *boot_param, u8 hw_variant,
				     u8 sbe_type);
व्योम btपूर्णांकel_reset_to_bootloader(काष्ठा hci_dev *hdev);
पूर्णांक btपूर्णांकel_पढ़ो_debug_features(काष्ठा hci_dev *hdev,
				काष्ठा पूर्णांकel_debug_features *features);
पूर्णांक btपूर्णांकel_set_debug_features(काष्ठा hci_dev *hdev,
			       स्थिर काष्ठा पूर्णांकel_debug_features *features);
#अन्यथा

अटल अंतरभूत पूर्णांक btपूर्णांकel_check_bdaddr(काष्ठा hci_dev *hdev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_enter_mfg(काष्ठा hci_dev *hdev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_निकास_mfg(काष्ठा hci_dev *hdev, bool reset, bool patched)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_set_diag(काष्ठा hci_dev *hdev, bool enable)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_set_diag_mfg(काष्ठा hci_dev *hdev, bool enable)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम btपूर्णांकel_hw_error(काष्ठा hci_dev *hdev, u8 code)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_version_info(काष्ठा hci_dev *hdev,
				       काष्ठा पूर्णांकel_version *ver)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_version_info_tlv(काष्ठा hci_dev *hdev,
					   काष्ठा पूर्णांकel_version_tlv *version)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_secure_send(काष्ठा hci_dev *hdev, u8 fragment_type,
				      u32 plen, स्थिर व्योम *param)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_load_ddc_config(काष्ठा hci_dev *hdev,
					  स्थिर अक्षर *ddc_name)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_set_event_mask(काष्ठा hci_dev *hdev, bool debug)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_set_event_mask_mfg(काष्ठा hci_dev *hdev, bool debug)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_पढ़ो_version(काष्ठा hci_dev *hdev,
				       काष्ठा पूर्णांकel_version *ver)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_पढ़ो_version_tlv(काष्ठा hci_dev *hdev,
					   काष्ठा पूर्णांकel_version_tlv *ver)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत काष्ठा regmap *btपूर्णांकel_regmap_init(काष्ठा hci_dev *hdev,
						 u16 opcode_पढ़ो,
						 u16 opcode_ग_लिखो)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_send_पूर्णांकel_reset(काष्ठा hci_dev *hdev,
					   u32 reset_param)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_पढ़ो_boot_params(काष्ठा hci_dev *hdev,
					   काष्ठा पूर्णांकel_boot_params *params)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_करोwnload_firmware(काष्ठा hci_dev *dev,
					    स्थिर काष्ठा firmware *fw,
					    u32 *boot_param)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_करोwnload_firmware_newgen(काष्ठा hci_dev *hdev,
						   स्थिर काष्ठा firmware *fw,
						   u32 *boot_param,
						   u8 hw_variant, u8 sbe_type)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम btपूर्णांकel_reset_to_bootloader(काष्ठा hci_dev *hdev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_पढ़ो_debug_features(काष्ठा hci_dev *hdev,
					      काष्ठा पूर्णांकel_debug_features *features)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक btपूर्णांकel_set_debug_features(काष्ठा hci_dev *hdev,
					     स्थिर काष्ठा पूर्णांकel_debug_features *features)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर
