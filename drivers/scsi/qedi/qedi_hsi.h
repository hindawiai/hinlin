<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */
#अगर_अघोषित __QEDI_HSI__
#घोषणा __QEDI_HSI__
/*
 * Add include to common target
 */
#समावेश <linux/qed/common_hsi.h>

/*
 * Add include to common storage target
 */
#समावेश <linux/qed/storage_common.h>

/*
 * Add include to common TCP target
 */
#समावेश <linux/qed/tcp_common.h>

/*
 * Add include to common iSCSI target क्रम both eCore and protocol driver
 */
#समावेश <linux/qed/iscsi_common.h>

/*
 * iSCSI CMDQ element
 */
काष्ठा iscsi_cmdqe अणु
	__le16 conn_id;
	u8 invalid_command;
	u8 cmd_hdr_type;
	__le32 reserved1[2];
	__le32 cmd_payload[13];
पूर्ण;

/*
 * iSCSI CMD header type
 */
क्रमागत iscsi_cmd_hdr_type अणु
	ISCSI_CMD_HDR_TYPE_BHS_ONLY /* iSCSI BHS with no expected AHS */,
	ISCSI_CMD_HDR_TYPE_BHS_W_AHS /* iSCSI BHS with expected AHS */,
	ISCSI_CMD_HDR_TYPE_AHS /* iSCSI AHS */,
	MAX_ISCSI_CMD_HDR_TYPE
पूर्ण;

#पूर्ण_अगर /* __QEDI_HSI__ */
