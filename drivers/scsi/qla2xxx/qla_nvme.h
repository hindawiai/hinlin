<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2017 QLogic Corporation
 */
#अगर_अघोषित __QLA_NVME_H
#घोषणा __QLA_NVME_H

#समावेश <uapi/scsi/fc/fc_fs.h>
#समावेश <uapi/scsi/fc/fc_els.h>
#समावेश <linux/nvme-fc-driver.h>

#समावेश "qla_def.h"
#समावेश "qla_dsd.h"

#घोषणा NVME_ATIO_CMD_OFF 32
#घोषणा NVME_FIRST_PACKET_CMDLEN (64 - NVME_ATIO_CMD_OFF)
#घोषणा Q2T_NVME_NUM_TAGS 2048
#घोषणा QLA_MAX_FC_SEGMENTS 64

काष्ठा scsi_qla_host;
काष्ठा qla_hw_data;
काष्ठा req_que;
काष्ठा srb;

काष्ठा nvme_निजी अणु
	काष्ठा srb	*sp;
	काष्ठा nvmefc_ls_req *fd;
	काष्ठा work_काष्ठा ls_work;
	काष्ठा work_काष्ठा पात_work;
	पूर्णांक comp_status;
	spinlock_t cmd_lock;
पूर्ण;

काष्ठा qla_nvme_rport अणु
	काष्ठा fc_port *fcport;
पूर्ण;

#घोषणा COMMAND_NVME    0x88            /* Command Type FC-NVMe IOCB */
काष्ठा cmd_nvme अणु
	uपूर्णांक8_t entry_type;             /* Entry type. */
	uपूर्णांक8_t entry_count;            /* Entry count. */
	uपूर्णांक8_t sys_define;             /* System defined. */
	uपूर्णांक8_t entry_status;           /* Entry Status. */

	uपूर्णांक32_t handle;                /* System handle. */
	__le16	nport_handle;		/* N_PORT handle. */
	__le16	समयout;		/* Command समयout. */

	__le16	dseg_count;		/* Data segment count. */
	__le16	nvme_rsp_dsd_len;	/* NVMe RSP DSD length */

	uपूर्णांक64_t rsvd;

	__le16	control_flags;		/* Control Flags */
#घोषणा CF_ADMIN_ASYNC_EVENT		BIT_13
#घोषणा CF_NVME_FIRST_BURST_ENABLE	BIT_11
#घोषणा CF_DIF_SEG_DESCR_ENABLE         BIT_3
#घोषणा CF_DATA_SEG_DESCR_ENABLE        BIT_2
#घोषणा CF_READ_DATA                    BIT_1
#घोषणा CF_WRITE_DATA                   BIT_0

	__le16	nvme_cmnd_dseg_len;             /* Data segment length. */
	__le64	 nvme_cmnd_dseg_address __packed;/* Data segment address. */
	__le64	 nvme_rsp_dseg_address __packed; /* Data segment address. */

	__le32	byte_count;		/* Total byte count. */

	uपूर्णांक8_t port_id[3];             /* PortID of destination port. */
	uपूर्णांक8_t vp_index;

	काष्ठा dsd64 nvme_dsd;
पूर्ण;

#घोषणा PT_LS4_REQUEST 0x89	/* Link Service pass-through IOCB (request) */
काष्ठा pt_ls4_request अणु
	uपूर्णांक8_t entry_type;
	uपूर्णांक8_t entry_count;
	uपूर्णांक8_t sys_define;
	uपूर्णांक8_t entry_status;
	uपूर्णांक32_t handle;
	__le16	status;
	__le16	nport_handle;
	__le16	tx_dseg_count;
	uपूर्णांक8_t  vp_index;
	uपूर्णांक8_t  rsvd;
	__le16	समयout;
	__le16	control_flags;
#घोषणा CF_LS4_SHIFT		13
#घोषणा CF_LS4_ORIGINATOR	0
#घोषणा CF_LS4_RESPONDER	1
#घोषणा CF_LS4_RESPONDER_TERM	2

	__le16	rx_dseg_count;
	__le16	rsvd2;
	__le32	exchange_address;
	__le32	rsvd3;
	__le32	rx_byte_count;
	__le32	tx_byte_count;
	काष्ठा dsd64 dsd[2];
पूर्ण;

#घोषणा PT_LS4_UNSOL 0x56	/* pass-up unsolicited rec FC-NVMe request */
काष्ठा pt_ls4_rx_unsol अणु
	uपूर्णांक8_t entry_type;
	uपूर्णांक8_t entry_count;
	__le16	rsvd0;
	__le16	rsvd1;
	uपूर्णांक8_t vp_index;
	uपूर्णांक8_t rsvd2;
	__le16	rsvd3;
	__le16	nport_handle;
	__le16	frame_size;
	__le16	rsvd4;
	__le32	exchange_address;
	uपूर्णांक8_t d_id[3];
	uपूर्णांक8_t r_ctl;
	be_id_t s_id;
	uपूर्णांक8_t cs_ctl;
	uपूर्णांक8_t f_ctl[3];
	uपूर्णांक8_t type;
	__le16	seq_cnt;
	uपूर्णांक8_t df_ctl;
	uपूर्णांक8_t seq_id;
	__le16	rx_id;
	__le16	ox_id;
	__le32	param;
	__le32	desc0;
#घोषणा PT_LS4_PAYLOAD_OFFSET 0x2c
#घोषणा PT_LS4_FIRST_PACKET_LEN 20
	__le32	desc_len;
	__le32	payload[3];
पूर्ण;

/*
 * Global functions prototype in qla_nvme.c source file.
 */
पूर्णांक qla_nvme_रेजिस्टर_hba(काष्ठा scsi_qla_host *);
पूर्णांक  qla_nvme_रेजिस्टर_remote(काष्ठा scsi_qla_host *, काष्ठा fc_port *);
व्योम qla_nvme_delete(काष्ठा scsi_qla_host *);
व्योम qla24xx_nvme_ls4_iocb(काष्ठा scsi_qla_host *, काष्ठा pt_ls4_request *,
    काष्ठा req_que *);
व्योम qla24xx_async_gffid_sp_करोne(काष्ठा srb *sp, पूर्णांक);
#पूर्ण_अगर
