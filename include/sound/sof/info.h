<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_INFO_H__
#घोषणा __INCLUDE_SOUND_SOF_INFO_H__

#समावेश <sound/sof/header.h>
#समावेश <sound/sof/stream.h>

/*
 * Firmware boot and version
 */

#घोषणा SOF_IPC_MAX_ELEMS	16

/*
 * Firmware boot info flag bits (64-bit)
 */
#घोषणा SOF_IPC_INFO_BUILD		BIT(0)
#घोषणा SOF_IPC_INFO_LOCKS		BIT(1)
#घोषणा SOF_IPC_INFO_LOCKSV		BIT(2)
#घोषणा SOF_IPC_INFO_GDB		BIT(3)

/* extended data types that can be appended onto end of sof_ipc_fw_पढ़ोy */
क्रमागत sof_ipc_ext_data अणु
	SOF_IPC_EXT_UNUSED		= 0,
	SOF_IPC_EXT_WINDOW		= 1,
	SOF_IPC_EXT_CC_INFO		= 2,
	SOF_IPC_EXT_PROBE_INFO		= 3,
	SOF_IPC_EXT_USER_ABI_INFO	= 4,
पूर्ण;

/* FW version - SOF_IPC_GLB_VERSION */
काष्ठा sof_ipc_fw_version अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक16_t major;
	uपूर्णांक16_t minor;
	uपूर्णांक16_t micro;
	uपूर्णांक16_t build;
	uपूर्णांक8_t date[12];
	uपूर्णांक8_t समय[10];
	uपूर्णांक8_t tag[6];
	uपूर्णांक32_t abi_version;
	/* used to check FW and ldc file compatibility, reproducible value */
	uपूर्णांक32_t src_hash;

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[3];
पूर्ण __packed;

/* FW पढ़ोy Message - sent by firmware when boot has completed */
काष्ठा sof_ipc_fw_पढ़ोy अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t dspbox_offset;	 /* dsp initiated IPC mailbox */
	uपूर्णांक32_t hostbox_offset; /* host initiated IPC mailbox */
	uपूर्णांक32_t dspbox_size;
	uपूर्णांक32_t hostbox_size;
	काष्ठा sof_ipc_fw_version version;

	/* Miscellaneous flags */
	uपूर्णांक64_t flags;

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[4];
पूर्ण __packed;

/*
 * Extended Firmware data. All optional, depends on platक्रमm/arch.
 */
क्रमागत sof_ipc_region अणु
	SOF_IPC_REGION_DOWNBOX	= 0,
	SOF_IPC_REGION_UPBOX,
	SOF_IPC_REGION_TRACE,
	SOF_IPC_REGION_DEBUG,
	SOF_IPC_REGION_STREAM,
	SOF_IPC_REGION_REGS,
	SOF_IPC_REGION_EXCEPTION,
पूर्ण;

काष्ठा sof_ipc_ext_data_hdr अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t type;		/**< SOF_IPC_EXT_ */
पूर्ण __packed;

काष्ठा sof_ipc_winकरोw_elem अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक32_t type;		/**< SOF_IPC_REGION_ */
	uपूर्णांक32_t id;		/**< platक्रमm specअगरic - used to map to host memory */
	uपूर्णांक32_t flags;		/**< R, W, RW, etc - to define */
	uपूर्णांक32_t size;		/**< size of region in bytes */
	/* offset in winकरोw region as winकरोws can be partitioned */
	uपूर्णांक32_t offset;
पूर्ण __packed;

/* extended data memory winकरोws क्रम IPC, trace and debug */
काष्ठा sof_ipc_winकरोw अणु
	काष्ठा sof_ipc_ext_data_hdr ext_hdr;
	uपूर्णांक32_t num_winकरोws;
	काष्ठा sof_ipc_winकरोw_elem winकरोw[SOF_IPC_MAX_ELEMS];
पूर्ण  __packed;

काष्ठा sof_ipc_cc_version अणु
	काष्ठा sof_ipc_ext_data_hdr ext_hdr;
	uपूर्णांक32_t major;
	uपूर्णांक32_t minor;
	uपूर्णांक32_t micro;

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[4];

	uपूर्णांक8_t name[16]; /* null terminated compiler name */
	uपूर्णांक8_t optim[4]; /* null terminated compiler -O flag value */
	uपूर्णांक8_t desc[32]; /* null terminated compiler description */
पूर्ण __packed;

/* extended data: Probe setup */
काष्ठा sof_ipc_probe_support अणु
	काष्ठा sof_ipc_ext_data_hdr ext_hdr;

	uपूर्णांक32_t probe_poपूर्णांकs_max;
	uपूर्णांक32_t injection_dmas_max;

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[2];
पूर्ण __packed;

/* extended data: user abi version(s) */
काष्ठा sof_ipc_user_abi_version अणु
	काष्ठा sof_ipc_ext_data_hdr ext_hdr;

	uपूर्णांक32_t abi_dbg_version;
पूर्ण  __packed;

#पूर्ण_अगर
