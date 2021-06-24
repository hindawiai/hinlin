<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2020 Intel Corporation. All rights reserved.
 *
 * Author: Karol Trzcinski <karolx.trzcinski@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_DEBUG_H__
#घोषणा __INCLUDE_SOUND_SOF_DEBUG_H__

#समावेश <sound/sof/header.h>

/** ABI3.18 */
क्रमागत sof_ipc_dbg_mem_zone अणु
	SOF_IPC_MEM_ZONE_SYS		= 0,	/**< System zone */
	SOF_IPC_MEM_ZONE_SYS_RUNTIME	= 1,	/**< System-runसमय zone */
	SOF_IPC_MEM_ZONE_RUNTIME	= 2,	/**< Runसमय zone */
	SOF_IPC_MEM_ZONE_BUFFER		= 3,	/**< Buffer zone */
पूर्ण;

/** ABI3.18 */
काष्ठा sof_ipc_dbg_mem_usage_elem अणु
	uपूर्णांक32_t zone;		/**< see sof_ipc_dbg_mem_zone */
	uपूर्णांक32_t id;		/**< heap index within zone */
	uपूर्णांक32_t used;		/**< number of bytes used in zone */
	uपूर्णांक32_t मुक्त;		/**< number of bytes मुक्त to use within zone */
	uपूर्णांक32_t reserved;	/**< क्रम future use */
पूर्ण __packed;

/** ABI3.18 */
काष्ठा sof_ipc_dbg_mem_usage अणु
	काष्ठा sof_ipc_reply rhdr;			/**< generic IPC reply header */
	uपूर्णांक32_t reserved[4];				/**< reserved क्रम future use */
	uपूर्णांक32_t num_elems;				/**< elems[] counter */
	काष्ठा sof_ipc_dbg_mem_usage_elem elems[];	/**< memory usage inक्रमmation */
पूर्ण __packed;

#पूर्ण_अगर
