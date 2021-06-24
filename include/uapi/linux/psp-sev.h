<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Userspace पूर्णांकerface क्रम AMD Secure Encrypted Virtualization (SEV)
 * platक्रमm management commands.
 *
 * Copyright (C) 2016-2017 Advanced Micro Devices, Inc.
 *
 * Author: Brijesh Singh <brijesh.singh@amd.com>
 *
 * SEV API specअगरication is available at: https://developer.amd.com/sev/
 */

#अगर_अघोषित __PSP_SEV_USER_H__
#घोषणा __PSP_SEV_USER_H__

#समावेश <linux/types.h>

/**
 * SEV platक्रमm commands
 */
क्रमागत अणु
	SEV_FACTORY_RESET = 0,
	SEV_PLATFORM_STATUS,
	SEV_PEK_GEN,
	SEV_PEK_CSR,
	SEV_PDH_GEN,
	SEV_PDH_CERT_EXPORT,
	SEV_PEK_CERT_IMPORT,
	SEV_GET_ID,	/* This command is deprecated, use SEV_GET_ID2 */
	SEV_GET_ID2,

	SEV_MAX,
पूर्ण;

/**
 * SEV Firmware status code
 */
प्रकार क्रमागत अणु
	SEV_RET_SUCCESS = 0,
	SEV_RET_INVALID_PLATFORM_STATE,
	SEV_RET_INVALID_GUEST_STATE,
	SEV_RET_INAVLID_CONFIG,
	SEV_RET_INVALID_LEN,
	SEV_RET_ALREADY_OWNED,
	SEV_RET_INVALID_CERTIFICATE,
	SEV_RET_POLICY_FAILURE,
	SEV_RET_INACTIVE,
	SEV_RET_INVALID_ADDRESS,
	SEV_RET_BAD_SIGNATURE,
	SEV_RET_BAD_MEASUREMENT,
	SEV_RET_ASID_OWNED,
	SEV_RET_INVALID_ASID,
	SEV_RET_WBINVD_REQUIRED,
	SEV_RET_DFFLUSH_REQUIRED,
	SEV_RET_INVALID_GUEST,
	SEV_RET_INVALID_COMMAND,
	SEV_RET_ACTIVE,
	SEV_RET_HWSEV_RET_PLATFORM,
	SEV_RET_HWSEV_RET_UNSAFE,
	SEV_RET_UNSUPPORTED,
	SEV_RET_INVALID_PARAM,
	SEV_RET_RESOURCE_LIMIT,
	SEV_RET_SECURE_DATA_INVALID,
	SEV_RET_MAX,
पूर्ण sev_ret_code;

/**
 * काष्ठा sev_user_data_status - PLATFORM_STATUS command parameters
 *
 * @major: major API version
 * @minor: minor API version
 * @state: platक्रमm state
 * @flags: platक्रमm config flags
 * @build: firmware build id क्रम API version
 * @guest_count: number of active guests
 */
काष्ठा sev_user_data_status अणु
	__u8 api_major;				/* Out */
	__u8 api_minor;				/* Out */
	__u8 state;				/* Out */
	__u32 flags;				/* Out */
	__u8 build;				/* Out */
	__u32 guest_count;			/* Out */
पूर्ण __packed;

#घोषणा SEV_STATUS_FLAGS_CONFIG_ES	0x0100

/**
 * काष्ठा sev_user_data_pek_csr - PEK_CSR command parameters
 *
 * @address: PEK certअगरicate chain
 * @length: length of certअगरicate
 */
काष्ठा sev_user_data_pek_csr अणु
	__u64 address;				/* In */
	__u32 length;				/* In/Out */
पूर्ण __packed;

/**
 * काष्ठा sev_user_data_cert_import - PEK_CERT_IMPORT command parameters
 *
 * @pek_address: PEK certअगरicate chain
 * @pek_len: length of PEK certअगरicate
 * @oca_address: OCA certअगरicate chain
 * @oca_len: length of OCA certअगरicate
 */
काष्ठा sev_user_data_pek_cert_import अणु
	__u64 pek_cert_address;			/* In */
	__u32 pek_cert_len;			/* In */
	__u64 oca_cert_address;			/* In */
	__u32 oca_cert_len;			/* In */
पूर्ण __packed;

/**
 * काष्ठा sev_user_data_pdh_cert_export - PDH_CERT_EXPORT command parameters
 *
 * @pdh_address: PDH certअगरicate address
 * @pdh_len: length of PDH certअगरicate
 * @cert_chain_address: PDH certअगरicate chain
 * @cert_chain_len: length of PDH certअगरicate chain
 */
काष्ठा sev_user_data_pdh_cert_export अणु
	__u64 pdh_cert_address;			/* In */
	__u32 pdh_cert_len;			/* In/Out */
	__u64 cert_chain_address;		/* In */
	__u32 cert_chain_len;			/* In/Out */
पूर्ण __packed;

/**
 * काष्ठा sev_user_data_get_id - GET_ID command parameters (deprecated)
 *
 * @socket1: Buffer to pass unique ID of first socket
 * @socket2: Buffer to pass unique ID of second socket
 */
काष्ठा sev_user_data_get_id अणु
	__u8 socket1[64];			/* Out */
	__u8 socket2[64];			/* Out */
पूर्ण __packed;

/**
 * काष्ठा sev_user_data_get_id2 - GET_ID command parameters
 * @address: Buffer to store unique ID
 * @length: length of the unique ID
 */
काष्ठा sev_user_data_get_id2 अणु
	__u64 address;				/* In */
	__u32 length;				/* In/Out */
पूर्ण __packed;

/**
 * काष्ठा sev_issue_cmd - SEV ioctl parameters
 *
 * @cmd: SEV commands to execute
 * @opaque: poपूर्णांकer to the command काष्ठाure
 * @error: SEV FW वापस code on failure
 */
काष्ठा sev_issue_cmd अणु
	__u32 cmd;				/* In */
	__u64 data;				/* In */
	__u32 error;				/* Out */
पूर्ण __packed;

#घोषणा SEV_IOC_TYPE		'S'
#घोषणा SEV_ISSUE_CMD	_IOWR(SEV_IOC_TYPE, 0x0, काष्ठा sev_issue_cmd)

#पूर्ण_अगर /* __PSP_USER_SEV_H */
