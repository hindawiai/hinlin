<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_PM_H__
#घोषणा __INCLUDE_SOUND_SOF_PM_H__

#समावेश <sound/sof/header.h>

/*
 * PM
 */

/* PM context element */
काष्ठा sof_ipc_pm_ctx_elem अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक32_t type;
	uपूर्णांक32_t size;
	uपूर्णांक64_t addr;
पूर्ण  __packed;

/*
 * PM context - SOF_IPC_PM_CTX_SAVE, SOF_IPC_PM_CTX_RESTORE,
 * SOF_IPC_PM_CTX_SIZE
 */
काष्ठा sof_ipc_pm_ctx अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	काष्ठा sof_ipc_host_buffer buffer;
	uपूर्णांक32_t num_elems;
	uपूर्णांक32_t size;

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[8];

	काष्ठा sof_ipc_pm_ctx_elem elems[];
पूर्ण __packed;

/* enable or disable cores - SOF_IPC_PM_CORE_ENABLE */
काष्ठा sof_ipc_pm_core_config अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t enable_mask;
पूर्ण __packed;

काष्ठा sof_ipc_pm_gate अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t flags;	/* platक्रमm specअगरic */

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[5];
पूर्ण __packed;

#पूर्ण_अगर
