<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_img_h__
#घोषणा __iwl_fw_img_h__
#समावेश <linux/types.h>

#समावेश "api/dbg-tlv.h"

#समावेश "file.h"
#समावेश "error-dump.h"

/**
 * क्रमागत iwl_ucode_type
 *
 * The type of ucode.
 *
 * @IWL_UCODE_REGULAR: Normal runसमय ucode
 * @IWL_UCODE_INIT: Initial ucode
 * @IWL_UCODE_WOWLAN: Wake on Wireless enabled ucode
 * @IWL_UCODE_REGULAR_USNIFFER: Normal runसमय ucode when using usnअगरfer image
 */
क्रमागत iwl_ucode_type अणु
	IWL_UCODE_REGULAR,
	IWL_UCODE_INIT,
	IWL_UCODE_WOWLAN,
	IWL_UCODE_REGULAR_USNIFFER,
	IWL_UCODE_TYPE_MAX,
पूर्ण;

/*
 * क्रमागतeration of ucode section.
 * This क्रमागतeration is used directly क्रम older firmware (beक्रमe 16.0).
 * For new firmware, there can be up to 4 sections (see below) but the
 * first one packaged पूर्णांकo the firmware file is the DATA section and
 * some debugging code accesses that.
 */
क्रमागत iwl_ucode_sec अणु
	IWL_UCODE_SECTION_DATA,
	IWL_UCODE_SECTION_INST,
पूर्ण;

काष्ठा iwl_ucode_capabilities अणु
	u32 max_probe_length;
	u32 n_scan_channels;
	u32 standard_phy_calibration_size;
	u32 flags;
	u32 error_log_addr;
	u32 error_log_size;
	u32 num_stations;
	अचिन्हित दीर्घ _api[BITS_TO_LONGS(NUM_IWL_UCODE_TLV_API)];
	अचिन्हित दीर्घ _capa[BITS_TO_LONGS(NUM_IWL_UCODE_TLV_CAPA)];

	स्थिर काष्ठा iwl_fw_cmd_version *cmd_versions;
	u32 n_cmd_versions;
पूर्ण;

अटल अंतरभूत bool
fw_has_api(स्थिर काष्ठा iwl_ucode_capabilities *capabilities,
	   iwl_ucode_tlv_api_t api)
अणु
	वापस test_bit((__क्रमce दीर्घ)api, capabilities->_api);
पूर्ण

अटल अंतरभूत bool
fw_has_capa(स्थिर काष्ठा iwl_ucode_capabilities *capabilities,
	    iwl_ucode_tlv_capa_t capa)
अणु
	वापस test_bit((__क्रमce दीर्घ)capa, capabilities->_capa);
पूर्ण

/* one क्रम each uCode image (inst/data, init/runसमय/wowlan) */
काष्ठा fw_desc अणु
	स्थिर व्योम *data;	/* vदो_स्मृति'ed data */
	u32 len;		/* size in bytes */
	u32 offset;		/* offset in the device */
पूर्ण;

काष्ठा fw_img अणु
	काष्ठा fw_desc *sec;
	पूर्णांक num_sec;
	bool is_dual_cpus;
	u32 paging_mem_size;
पूर्ण;

/*
 * Block paging calculations
 */
#घोषणा PAGE_2_EXP_SIZE 12 /* 4K == 2^12 */
#घोषणा FW_PAGING_SIZE BIT(PAGE_2_EXP_SIZE) /* page size is 4KB */
#घोषणा PAGE_PER_GROUP_2_EXP_SIZE 3
/* 8 pages per group */
#घोषणा NUM_OF_PAGE_PER_GROUP BIT(PAGE_PER_GROUP_2_EXP_SIZE)
/* करोn't change, support only 32KB size */
#घोषणा PAGING_BLOCK_SIZE (NUM_OF_PAGE_PER_GROUP * FW_PAGING_SIZE)
/* 32K == 2^15 */
#घोषणा BLOCK_2_EXP_SIZE (PAGE_2_EXP_SIZE + PAGE_PER_GROUP_2_EXP_SIZE)

/*
 * Image paging calculations
 */
#घोषणा BLOCK_PER_IMAGE_2_EXP_SIZE 5
/* 2^5 == 32 blocks per image */
#घोषणा NUM_OF_BLOCK_PER_IMAGE BIT(BLOCK_PER_IMAGE_2_EXP_SIZE)
/* maximum image size 1024KB */
#घोषणा MAX_PAGING_IMAGE_SIZE (NUM_OF_BLOCK_PER_IMAGE * PAGING_BLOCK_SIZE)

/* Virtual address signature */
#घोषणा PAGING_ADDR_SIG 0xAA000000

#घोषणा PAGING_CMD_IS_SECURED BIT(9)
#घोषणा PAGING_CMD_IS_ENABLED BIT(8)
#घोषणा PAGING_CMD_NUM_OF_PAGES_IN_LAST_GRP_POS	0
#घोषणा PAGING_TLV_SECURE_MASK 1

/* FW MSB Mask क्रम regions/cache_control */
#घोषणा FW_ADDR_CACHE_CONTROL 0xC0000000UL

/**
 * काष्ठा iwl_fw_paging
 * @fw_paging_phys: page phy poपूर्णांकer
 * @fw_paging_block: poपूर्णांकer to the allocated block
 * @fw_paging_size: page size
 */
काष्ठा iwl_fw_paging अणु
	dma_addr_t fw_paging_phys;
	काष्ठा page *fw_paging_block;
	u32 fw_paging_size;
पूर्ण;

/**
 * काष्ठा iwl_fw_cscheme_list - a cipher scheme list
 * @size: a number of entries
 * @cs: cipher scheme entries
 */
काष्ठा iwl_fw_cscheme_list अणु
	u8 size;
	काष्ठा iwl_fw_cipher_scheme cs[];
पूर्ण __packed;

/**
 * क्रमागत iwl_fw_type - iwlwअगरi firmware type
 * @IWL_FW_DVM: DVM firmware
 * @IWL_FW_MVM: MVM firmware
 */
क्रमागत iwl_fw_type अणु
	IWL_FW_DVM,
	IWL_FW_MVM,
पूर्ण;

/**
 * काष्ठा iwl_fw_dbg - debug data
 *
 * @dest_tlv: poपूर्णांकs to debug destination TLV (typically SRAM or DRAM)
 * @n_dest_reg: num of reg_ops in dest_tlv
 * @conf_tlv: array of poपूर्णांकers to configuration HCMDs
 * @trigger_tlv: array of poपूर्णांकers to triggers TLVs
 * @trigger_tlv_len: lengths of the @dbg_trigger_tlv entries
 * @mem_tlv: Runसमय addresses to dump
 * @n_mem_tlv: number of runसमय addresses
 * @dump_mask: biपंचांगask of dump regions
*/
काष्ठा iwl_fw_dbg अणु
	काष्ठा iwl_fw_dbg_dest_tlv_v1 *dest_tlv;
	u8 n_dest_reg;
	काष्ठा iwl_fw_dbg_conf_tlv *conf_tlv[FW_DBG_CONF_MAX];
	काष्ठा iwl_fw_dbg_trigger_tlv *trigger_tlv[FW_DBG_TRIGGER_MAX];
	माप_प्रकार trigger_tlv_len[FW_DBG_TRIGGER_MAX];
	काष्ठा iwl_fw_dbg_mem_seg_tlv *mem_tlv;
	माप_प्रकार n_mem_tlv;
	u32 dump_mask;
पूर्ण;

/**
 * काष्ठा iwl_fw - variables associated with the firmware
 *
 * @ucode_ver: ucode version from the ucode file
 * @fw_version: firmware version string
 * @img: ucode image like ucode_rt, ucode_init, ucode_wowlan.
 * @iml_len: length of the image loader image
 * @iml: image loader fw image
 * @ucode_capa: capabilities parsed from the ucode file.
 * @enhance_sensitivity_table: device can करो enhanced sensitivity.
 * @init_evtlog_ptr: event log offset क्रम init ucode.
 * @init_evtlog_size: event log size क्रम init ucode.
 * @init_errlog_ptr: error log offfset क्रम init ucode.
 * @inst_evtlog_ptr: event log offset क्रम runसमय ucode.
 * @inst_evtlog_size: event log size क्रम runसमय ucode.
 * @inst_errlog_ptr: error log offfset क्रम runसमय ucode.
 * @type: firmware type (&क्रमागत iwl_fw_type)
 * @cipher_scheme: optional बाह्यal cipher scheme.
 * @human_पढ़ोable: human पढ़ोable version
 *	we get the ALIVE from the uCode
 */
काष्ठा iwl_fw अणु
	u32 ucode_ver;

	अक्षर fw_version[64];

	/* ucode images */
	काष्ठा fw_img img[IWL_UCODE_TYPE_MAX];
	माप_प्रकार iml_len;
	u8 *iml;

	काष्ठा iwl_ucode_capabilities ucode_capa;
	bool enhance_sensitivity_table;

	u32 init_evtlog_ptr, init_evtlog_size, init_errlog_ptr;
	u32 inst_evtlog_ptr, inst_evtlog_size, inst_errlog_ptr;

	काष्ठा iwl_tlv_calib_ctrl शेष_calib[IWL_UCODE_TYPE_MAX];
	u32 phy_config;
	u8 valid_tx_ant;
	u8 valid_rx_ant;

	क्रमागत iwl_fw_type type;

	काष्ठा iwl_fw_cipher_scheme cs[IWL_UCODE_MAX_CS];
	u8 human_पढ़ोable[FW_VER_HUMAN_READABLE_SZ];

	काष्ठा iwl_fw_dbg dbg;

	u8 *phy_पूर्णांकegration_ver;
	u32 phy_पूर्णांकegration_ver_len;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *get_fw_dbg_mode_string(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल SMEM_MODE:
		वापस "SMEM";
	हाल EXTERNAL_MODE:
		वापस "EXTERNAL_DRAM";
	हाल MARBH_MODE:
		वापस "MARBH";
	हाल MIPI_MODE:
		वापस "MIPI";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल अंतरभूत bool
iwl_fw_dbg_conf_usnअगरfer(स्थिर काष्ठा iwl_fw *fw, u8 id)
अणु
	स्थिर काष्ठा iwl_fw_dbg_conf_tlv *conf_tlv = fw->dbg.conf_tlv[id];

	अगर (!conf_tlv)
		वापस false;

	वापस conf_tlv->usnअगरfer;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा fw_img *
iwl_get_ucode_image(स्थिर काष्ठा iwl_fw *fw, क्रमागत iwl_ucode_type ucode_type)
अणु
	अगर (ucode_type >= IWL_UCODE_TYPE_MAX)
		वापस शून्य;

	वापस &fw->img[ucode_type];
पूर्ण

u8 iwl_fw_lookup_cmd_ver(स्थिर काष्ठा iwl_fw *fw, u8 grp, u8 cmd, u8 def);

u8 iwl_fw_lookup_notअगर_ver(स्थिर काष्ठा iwl_fw *fw, u8 grp, u8 cmd, u8 def);
स्थिर अक्षर *iwl_fw_lookup_निश्चित_desc(u32 num);
#पूर्ण_अगर  /* __iwl_fw_img_h__ */
