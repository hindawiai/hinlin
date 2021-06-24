<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*****************************************************************************/
/* srp.h -- SCSI RDMA Protocol definitions                                   */
/*                                                                           */
/* Written By: Colin Devilbis, IBM Corporation                               */
/*                                                                           */
/* Copyright (C) 2003 IBM Corporation                                        */
/*                                                                           */
/*                                                                           */
/* This file contains काष्ठाures and definitions क्रम IBM RPA (RS/6000        */
/* platक्रमm architecture) implementation of the SRP (SCSI RDMA Protocol)     */
/* standard.  SRP is used on IBM iSeries and pSeries platक्रमms to send SCSI  */
/* commands between logical partitions.                                      */
/*                                                                           */
/* SRP Inक्रमmation Units (IUs) are sent on a "Command/Response Queue" (CRQ)  */
/* between partitions.  The definitions in this file are architected,        */
/* and cannot be changed without अवरोधing compatibility with other versions  */
/* of Linux and other operating प्रणालीs (AIX, OS/400) that talk this protocol*/
/* between logical partitions                                                */
/*****************************************************************************/
#अगर_अघोषित VIOSRP_H
#घोषणा VIOSRP_H
#समावेश <scsi/srp.h>

#घोषणा SRP_VERSION "16.a"
#घोषणा SRP_MAX_IU_LEN	256
#घोषणा SRP_MAX_LOC_LEN 32

जोड़ srp_iu अणु
	काष्ठा srp_login_req login_req;
	काष्ठा srp_login_rsp login_rsp;
	काष्ठा srp_login_rej login_rej;
	काष्ठा srp_i_logout i_logout;
	काष्ठा srp_t_logout t_logout;
	काष्ठा srp_tsk_mgmt tsk_mgmt;
	काष्ठा srp_cmd cmd;
	काष्ठा srp_rsp rsp;
	u8 reserved[SRP_MAX_IU_LEN];
पूर्ण;

क्रमागत viosrp_crq_headers अणु
	VIOSRP_CRQ_FREE = 0x00,
	VIOSRP_CRQ_CMD_RSP = 0x80,
	VIOSRP_CRQ_INIT_RSP = 0xC0,
	VIOSRP_CRQ_XPORT_EVENT = 0xFF
पूर्ण;

क्रमागत viosrp_crq_init_क्रमmats अणु
	VIOSRP_CRQ_INIT = 0x01,
	VIOSRP_CRQ_INIT_COMPLETE = 0x02
पूर्ण;

क्रमागत viosrp_crq_क्रमmats अणु
	VIOSRP_SRP_FORMAT = 0x01,
	VIOSRP_MAD_FORMAT = 0x02,
	VIOSRP_OS400_FORMAT = 0x03,
	VIOSRP_AIX_FORMAT = 0x04,
	VIOSRP_LINUX_FORMAT = 0x05,
	VIOSRP_INLINE_FORMAT = 0x06
पूर्ण;

क्रमागत viosrp_crq_status अणु
	VIOSRP_OK = 0x0,
	VIOSRP_NONRECOVERABLE_ERR = 0x1,
	VIOSRP_VIOLATES_MAX_XFER = 0x2,
	VIOSRP_PARTNER_PANIC = 0x3,
	VIOSRP_DEVICE_BUSY = 0x8,
	VIOSRP_ADAPTER_FAIL = 0x10,
	VIOSRP_OK2 = 0x99,
पूर्ण;

काष्ठा viosrp_crq अणु
	u8 valid;		/* used by RPA */
	u8 क्रमmat;		/* SCSI vs out-of-band */
	u8 reserved;
	u8 status;		/* non-scsi failure? (e.g. DMA failure) */
	__be16 समयout;		/* in seconds */
	__be16 IU_length;		/* in bytes */
	__be64 IU_data_ptr;	/* the TCE क्रम transferring data */
पूर्ण;

/* MADs are Management requests above and beyond the IUs defined in the SRP
 * standard.
 */
क्रमागत viosrp_mad_types अणु
	VIOSRP_EMPTY_IU_TYPE = 0x01,
	VIOSRP_ERROR_LOG_TYPE = 0x02,
	VIOSRP_ADAPTER_INFO_TYPE = 0x03,
	VIOSRP_CAPABILITIES_TYPE = 0x05,
	VIOSRP_ENABLE_FAST_FAIL = 0x08,
पूर्ण;

क्रमागत viosrp_mad_status अणु
	VIOSRP_MAD_SUCCESS = 0x00,
	VIOSRP_MAD_NOT_SUPPORTED = 0xF1,
	VIOSRP_MAD_FAILED = 0xF7,
पूर्ण;

क्रमागत viosrp_capability_type अणु
	MIGRATION_CAPABILITIES = 0x01,
	RESERVATION_CAPABILITIES = 0x02,
पूर्ण;

क्रमागत viosrp_capability_support अणु
	SERVER_DOES_NOT_SUPPORTS_CAP = 0x0,
	SERVER_SUPPORTS_CAP = 0x01,
	SERVER_CAP_DATA = 0x02,
पूर्ण;

क्रमागत viosrp_reserve_type अणु
	CLIENT_RESERVE_SCSI_2 = 0x01,
पूर्ण;

क्रमागत viosrp_capability_flag अणु
	CLIENT_MIGRATED = 0x01,
	CLIENT_RECONNECT = 0x02,
	CAP_LIST_SUPPORTED = 0x04,
	CAP_LIST_DATA = 0x08,
पूर्ण;

/*
 * Common MAD header
 */
काष्ठा mad_common अणु
	__be32 type;
	__be16 status;
	__be16 length;
	__be64 tag;
पूर्ण;

/*
 * All SRP (and MAD) requests normally flow from the
 * client to the server.  There is no way क्रम the server to send
 * an asynchronous message back to the client.  The Empty IU is used
 * to hang out a meaningless request to the server so that it can respond
 * asynchrouously with something like a SCSI AER
 */
काष्ठा viosrp_empty_iu अणु
	काष्ठा mad_common common;
	__be64 buffer;
	__be32 port;
पूर्ण;

काष्ठा viosrp_error_log अणु
	काष्ठा mad_common common;
	__be64 buffer;
पूर्ण;

काष्ठा viosrp_adapter_info अणु
	काष्ठा mad_common common;
	__be64 buffer;
पूर्ण;

काष्ठा viosrp_fast_fail अणु
	काष्ठा mad_common common;
पूर्ण;

काष्ठा viosrp_capabilities अणु
	काष्ठा mad_common common;
	__be64 buffer;
पूर्ण;

काष्ठा mad_capability_common अणु
	__be32 cap_type;
	__be16 length;
	__be16 server_support;
पूर्ण;

काष्ठा mad_reserve_cap अणु
	काष्ठा mad_capability_common common;
	__be32 type;
पूर्ण;

काष्ठा mad_migration_cap अणु
	काष्ठा mad_capability_common common;
	__be32 ecl;
पूर्ण;

काष्ठा capabilities अणु
	__be32 flags;
	अक्षर name[SRP_MAX_LOC_LEN];
	अक्षर loc[SRP_MAX_LOC_LEN];
	काष्ठा mad_migration_cap migration;
	काष्ठा mad_reserve_cap reserve;
पूर्ण;

जोड़ mad_iu अणु
	काष्ठा viosrp_empty_iu empty_iu;
	काष्ठा viosrp_error_log error_log;
	काष्ठा viosrp_adapter_info adapter_info;
	काष्ठा viosrp_fast_fail fast_fail;
	काष्ठा viosrp_capabilities capabilities;
पूर्ण;

जोड़ viosrp_iu अणु
	जोड़ srp_iu srp;
	जोड़ mad_iu mad;
पूर्ण;

काष्ठा mad_adapter_info_data अणु
	अक्षर srp_version[8];
	अक्षर partition_name[96];
	__be32 partition_number;
#घोषणा SRP_MAD_VERSION_1 1
	__be32 mad_version;
#घोषणा SRP_MAD_OS_LINUX 2
#घोषणा SRP_MAD_OS_AIX 3
	__be32 os_type;
	__be32 port_max_txu[8];	/* per-port maximum transfer */
पूर्ण;

#पूर्ण_अगर
