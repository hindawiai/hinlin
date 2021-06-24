<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#अगर_अघोषित __iwl_fw_runसमय_h__
#घोषणा __iwl_fw_runसमय_h__

#समावेश "iwl-config.h"
#समावेश "iwl-trans.h"
#समावेश "img.h"
#समावेश "fw/api/debug.h"
#समावेश "fw/api/paging.h"
#समावेश "fw/api/power.h"
#समावेश "iwl-eeprom-parse.h"
#समावेश "fw/acpi.h"

काष्ठा iwl_fw_runसमय_ops अणु
	पूर्णांक (*dump_start)(व्योम *ctx);
	व्योम (*dump_end)(व्योम *ctx);
	bool (*fw_running)(व्योम *ctx);
	पूर्णांक (*send_hcmd)(व्योम *ctx, काष्ठा iwl_host_cmd *host_cmd);
	bool (*d3_debug_enable)(व्योम *ctx);
पूर्ण;

#घोषणा MAX_NUM_LMAC 2
काष्ठा iwl_fwrt_shared_mem_cfg अणु
	पूर्णांक num_lmacs;
	पूर्णांक num_txfअगरo_entries;
	काष्ठा अणु
		u32 txfअगरo_size[TX_FIFO_MAX_NUM];
		u32 rxfअगरo1_size;
	पूर्ण lmac[MAX_NUM_LMAC];
	u32 rxfअगरo2_size;
	u32 rxfअगरo2_control_size;
	u32 पूर्णांकernal_txfअगरo_addr;
	u32 पूर्णांकernal_txfअगरo_size[TX_FIFO_INTERNAL_MAX_NUM];
पूर्ण;

#घोषणा IWL_FW_RUNTIME_DUMP_WK_NUM 5

/**
 * काष्ठा iwl_fwrt_dump_data - dump data
 * @trig: trigger the worker was scheduled upon
 * @fw_pkt: packet received from FW
 */
काष्ठा iwl_fwrt_dump_data अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा iwl_fw_ini_trigger_tlv *trig;
			काष्ठा iwl_rx_packet *fw_pkt;
		पूर्ण;
		काष्ठा अणु
			स्थिर काष्ठा iwl_fw_dump_desc *desc;
			bool monitor_only;
		पूर्ण;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा iwl_fwrt_wk_data - dump worker data काष्ठा
 * @idx: index of the worker
 * @wk: worker
 */
काष्ठा iwl_fwrt_wk_data  अणु
	u8 idx;
	काष्ठा delayed_work wk;
	काष्ठा iwl_fwrt_dump_data dump_data;
पूर्ण;

/**
 * काष्ठा iwl_txf_iter_data - Tx fअगरo iterator data काष्ठा
 * @fअगरo: fअगरo number
 * @lmac: lmac number
 * @fअगरo_size: fअगरo size
 * @पूर्णांकernal_txf: non zero अगर fअगरo is  पूर्णांकernal Tx fअगरo
 */
काष्ठा iwl_txf_iter_data अणु
	पूर्णांक fअगरo;
	पूर्णांक lmac;
	u32 fअगरo_size;
	u8 पूर्णांकernal_txf;
पूर्ण;

/**
 * काष्ठा iwl_fw_runसमय - runसमय data क्रम firmware
 * @fw: firmware image
 * @cfg: NIC configuration
 * @dev: device poपूर्णांकer
 * @ops: user ops
 * @ops_ctx: user ops context
 * @fw_paging_db: paging database
 * @num_of_paging_blk: number of paging blocks
 * @num_of_pages_in_last_blk: number of pages in the last block
 * @smem_cfg: saved firmware SMEM configuration
 * @cur_fw_img: current firmware image, must be मुख्यtained by
 *	the driver by calling &iwl_fw_set_current_image()
 * @dump: debug dump data
 */
काष्ठा iwl_fw_runसमय अणु
	काष्ठा iwl_trans *trans;
	स्थिर काष्ठा iwl_fw *fw;
	काष्ठा device *dev;

	स्थिर काष्ठा iwl_fw_runसमय_ops *ops;
	व्योम *ops_ctx;

	/* Paging */
	काष्ठा iwl_fw_paging fw_paging_db[NUM_OF_FW_PAGING_BLOCKS];
	u16 num_of_paging_blk;
	u16 num_of_pages_in_last_blk;

	क्रमागत iwl_ucode_type cur_fw_img;

	/* memory configuration */
	काष्ठा iwl_fwrt_shared_mem_cfg smem_cfg;

	/* debug */
	काष्ठा अणु
		काष्ठा iwl_fwrt_wk_data wks[IWL_FW_RUNTIME_DUMP_WK_NUM];
		अचिन्हित दीर्घ active_wks;

		u8 conf;

		/* ts of the beginning of a non-collect fw dbg data period */
		अचिन्हित दीर्घ non_collect_ts_start[IWL_FW_INI_TIME_POINT_NUM];
		u32 *d3_debug_data;
		u32 lmac_err_id[MAX_NUM_LMAC];
		u32 umac_err_id;

		काष्ठा iwl_txf_iter_data txf_iter_data;

		काष्ठा अणु
			u8 type;
			u8 subtype;
			u32 lmac_major;
			u32 lmac_minor;
			u32 umac_major;
			u32 umac_minor;
		पूर्ण fw_ver;
	पूर्ण dump;
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	काष्ठा अणु
		काष्ठा delayed_work wk;
		u32 delay;
		u64 seq;
	पूर्ण बारtamp;
	bool tpc_enabled;
#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUGFS */
#अगर_घोषित CONFIG_ACPI
	काष्ठा iwl_sar_profile sar_profiles[ACPI_SAR_PROखाता_NUM];
	u8 sar_chain_a_profile;
	u8 sar_chain_b_profile;
	काष्ठा iwl_geo_profile geo_profiles[ACPI_NUM_GEO_PROखाताS];
	u32 geo_rev;
	जोड़ iwl_ppag_table_cmd ppag_table;
	u32 ppag_ver;
#पूर्ण_अगर
पूर्ण;

व्योम iwl_fw_runसमय_init(काष्ठा iwl_fw_runसमय *fwrt, काष्ठा iwl_trans *trans,
			स्थिर काष्ठा iwl_fw *fw,
			स्थिर काष्ठा iwl_fw_runसमय_ops *ops, व्योम *ops_ctx,
			काष्ठा dentry *dbgfs_dir);

अटल अंतरभूत व्योम iwl_fw_runसमय_मुक्त(काष्ठा iwl_fw_runसमय *fwrt)
अणु
	पूर्णांक i;

	kमुक्त(fwrt->dump.d3_debug_data);
	fwrt->dump.d3_debug_data = शून्य;

	iwl_dbg_tlv_del_समयrs(fwrt->trans);
	क्रम (i = 0; i < IWL_FW_RUNTIME_DUMP_WK_NUM; i++)
		cancel_delayed_work_sync(&fwrt->dump.wks[i].wk);
पूर्ण

व्योम iwl_fw_runसमय_suspend(काष्ठा iwl_fw_runसमय *fwrt);

व्योम iwl_fw_runसमय_resume(काष्ठा iwl_fw_runसमय *fwrt);

अटल अंतरभूत व्योम iwl_fw_set_current_image(काष्ठा iwl_fw_runसमय *fwrt,
					    क्रमागत iwl_ucode_type cur_fw_img)
अणु
	fwrt->cur_fw_img = cur_fw_img;
पूर्ण

पूर्णांक iwl_init_paging(काष्ठा iwl_fw_runसमय *fwrt, क्रमागत iwl_ucode_type type);
व्योम iwl_मुक्त_fw_paging(काष्ठा iwl_fw_runसमय *fwrt);

व्योम iwl_get_shared_mem_conf(काष्ठा iwl_fw_runसमय *fwrt);
पूर्णांक iwl_set_soc_latency(काष्ठा iwl_fw_runसमय *fwrt);
पूर्णांक iwl_configure_rxq(काष्ठा iwl_fw_runसमय *fwrt);

#पूर्ण_अगर /* __iwl_fw_runसमय_h__ */
