<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#अगर_अघोषित _QEDI_FW_SCSI_H_
#घोषणा _QEDI_FW_SCSI_H_

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "qedi_hsi.h"
#समावेश <linux/qed/qed_अगर.h>

काष्ठा scsi_sgl_task_params अणु
	काष्ठा scsi_sge	*sgl;
	काष्ठा regpair	sgl_phys_addr;
	u32		total_buffer_size;
	u16		num_sges;
	bool		small_mid_sge;
पूर्ण;

काष्ठा scsi_dअगर_task_params अणु
	u32	initial_ref_tag;
	bool	initial_ref_tag_is_valid;
	u16	application_tag;
	u16	application_tag_mask;
	u16	dअगर_block_size_log;
	bool	dअगर_on_network;
	bool	dअगर_on_host;
	u8	host_guard_type;
	u8	protection_type;
	u8	ref_tag_mask;
	bool	crc_seed;
	bool	tx_dअगर_conn_err_en;
	bool	ignore_app_tag;
	bool	keep_ref_tag_स्थिर;
	bool	validate_guard;
	bool	validate_app_tag;
	bool	validate_ref_tag;
	bool	क्रमward_guard;
	bool	क्रमward_app_tag;
	bool	क्रमward_ref_tag;
	bool	क्रमward_app_tag_with_mask;
	bool	क्रमward_ref_tag_with_mask;
पूर्ण;

काष्ठा scsi_initiator_cmd_params अणु
	काष्ठा scsi_sge	extended_cdb_sge;
	काष्ठा regpair	sense_data_buffer_phys_addr;
पूर्ण;
#पूर्ण_अगर
