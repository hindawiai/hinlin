<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* QLogic FCoE Offload Driver
 * Copyright (c) 2016-2018 Cavium Inc.
 */
#अगर_अघोषित _SCSI_FW_FUNCS_H
#घोषणा _SCSI_FW_FUNCS_H
#समावेश <linux/qed/common_hsi.h>
#समावेश <linux/qed/storage_common.h>
#समावेश <linux/qed/fcoe_common.h>

काष्ठा scsi_sgl_task_params अणु
	काष्ठा scsi_sge *sgl;
	काष्ठा regpair sgl_phys_addr;
	u32 total_buffer_size;
	u16 num_sges;

	 /* true अगर SGL contains a small (< 4KB) SGE in middle(not 1st or last)
	  * -> relevant क्रम tx only
	  */
	bool small_mid_sge;
पूर्ण;

काष्ठा scsi_dअगर_task_params अणु
	u32 initial_ref_tag;
	bool initial_ref_tag_is_valid;
	u16 application_tag;
	u16 application_tag_mask;
	u16 dअगर_block_size_log;
	bool dअगर_on_network;
	bool dअगर_on_host;
	u8 host_guard_type;
	u8 protection_type;
	u8 ref_tag_mask;
	bool crc_seed;

	 /* Enable Connection error upon DIF error (segments with DIF errors are
	  * dropped)
	  */
	bool tx_dअगर_conn_err_en;
	bool ignore_app_tag;
	bool keep_ref_tag_स्थिर;
	bool validate_guard;
	bool validate_app_tag;
	bool validate_ref_tag;
	bool क्रमward_guard;
	bool क्रमward_app_tag;
	bool क्रमward_ref_tag;
	bool क्रमward_app_tag_with_mask;
	bool क्रमward_ref_tag_with_mask;
पूर्ण;

काष्ठा scsi_initiator_cmd_params अणु
	 /* क्रम cdb_size > शेष CDB size (extended CDB > 16 bytes) ->
	  * poपूर्णांकer to the CDB buffer SGE
	  */
	काष्ठा scsi_sge extended_cdb_sge;

	/* Physical address of sense data buffer क्रम sense data - 256B buffer */
	काष्ठा regpair sense_data_buffer_phys_addr;
पूर्ण;

/**
 * @brief scsi_is_slow_sgl - checks क्रम slow SGL
 *
 * @param num_sges - number of sges in SGL
 * @param small_mid_sge - True is the SGL contains an SGE which is smaller than
 * 4KB and its not the 1st or last SGE in the SGL
 */
bool scsi_is_slow_sgl(u16 num_sges, bool small_mid_sge);

/**
 * @brief init_scsi_sgl_context - initializes SGL task context
 *
 * @param sgl_params - SGL context parameters to initialize (output parameter)
 * @param data_desc - context काष्ठा containing SGEs array to set (output
 * parameter)
 * @param sgl_task_params - SGL parameters (input)
 */
व्योम init_scsi_sgl_context(काष्ठा scsi_sgl_params *sgl_params,
	काष्ठा scsi_cached_sges *ctx_data_desc,
	काष्ठा scsi_sgl_task_params *sgl_task_params);
#पूर्ण_अगर
