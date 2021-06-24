<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_TRACE_H__
#घोषणा __INCLUDE_SOUND_SOF_TRACE_H__

#समावेश <sound/sof/header.h>
#समावेश <sound/sof/stream.h>

/*
 * DMA क्रम Trace
 */

#घोषणा SOF_TRACE_खाताNAME_SIZE		32

/* DMA क्रम Trace params info - SOF_IPC_DEBUG_DMA_PARAMS */
/* Deprecated - use sof_ipc_dma_trace_params_ext */
काष्ठा sof_ipc_dma_trace_params अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	काष्ठा sof_ipc_host_buffer buffer;
	uपूर्णांक32_t stream_tag;
पूर्ण  __packed;

/* DMA क्रम Trace params info - SOF_IPC_DEBUG_DMA_PARAMS_EXT */
काष्ठा sof_ipc_dma_trace_params_ext अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	काष्ठा sof_ipc_host_buffer buffer;
	uपूर्णांक32_t stream_tag;
	uपूर्णांक64_t बारtamp_ns; /* in nanosecond */
	uपूर्णांक32_t reserved[8];
पूर्ण  __packed;

/* DMA क्रम Trace params info - SOF_IPC_DEBUG_DMA_PARAMS */
काष्ठा sof_ipc_dma_trace_posn अणु
	काष्ठा sof_ipc_reply rhdr;
	uपूर्णांक32_t host_offset;	/* Offset of DMA host buffer */
	uपूर्णांक32_t overflow;	/* overflow bytes अगर any */
	uपूर्णांक32_t messages;	/* total trace messages */
पूर्ण  __packed;

/* Values used in sof_ipc_trace_filter_elem: */

/* bits 6..0 */
#घोषणा SOF_IPC_TRACE_FILTER_ELEM_SET_LEVEL	0x01	/**< trace level क्रम selected components */
#घोषणा SOF_IPC_TRACE_FILTER_ELEM_BY_UUID	0x02	/**< filter by uuid key */
#घोषणा SOF_IPC_TRACE_FILTER_ELEM_BY_PIPE	0x03	/**< filter by pipeline */
#घोषणा SOF_IPC_TRACE_FILTER_ELEM_BY_COMP	0x04	/**< filter by component id */

/* bit 7 */
#घोषणा SOF_IPC_TRACE_FILTER_ELEM_FIN		0x80	/**< mark last filter in set */

/* bits 31..8: Unused */

/** part of sof_ipc_trace_filter, ABI3.17 */
काष्ठा sof_ipc_trace_filter_elem अणु
	uपूर्णांक32_t key;		/**< SOF_IPC_TRACE_FILTER_ELEM_ अणुLEVEL, UUID, COMP, PIPEपूर्ण */
	uपूर्णांक32_t value;		/**< element value */
पूर्ण __packed;

/** Runसमय tracing filtration data - SOF_IPC_TRACE_FILTER_UPDATE, ABI3.17 */
काष्ठा sof_ipc_trace_filter अणु
	काष्ठा sof_ipc_cmd_hdr hdr;	/**< IPC command header */
	uपूर्णांक32_t elem_cnt;		/**< number of entries in elems[] array */
	uपूर्णांक32_t reserved[8];		/**< reserved क्रम future usage */
	/** variable size array with new filtering settings */
	काष्ठा sof_ipc_trace_filter_elem elems[];
पूर्ण __packed;

/*
 * Commom debug
 */

/*
 * SOF panic codes
 */
#घोषणा SOF_IPC_PANIC_MAGIC			0x0dead000
#घोषणा SOF_IPC_PANIC_MAGIC_MASK		0x0ffff000
#घोषणा SOF_IPC_PANIC_CODE_MASK			0x00000fff
#घोषणा SOF_IPC_PANIC_MEM			(SOF_IPC_PANIC_MAGIC | 0x0)
#घोषणा SOF_IPC_PANIC_WORK			(SOF_IPC_PANIC_MAGIC | 0x1)
#घोषणा SOF_IPC_PANIC_IPC			(SOF_IPC_PANIC_MAGIC | 0x2)
#घोषणा SOF_IPC_PANIC_ARCH			(SOF_IPC_PANIC_MAGIC | 0x3)
#घोषणा SOF_IPC_PANIC_PLATFORM			(SOF_IPC_PANIC_MAGIC | 0x4)
#घोषणा SOF_IPC_PANIC_TASK			(SOF_IPC_PANIC_MAGIC | 0x5)
#घोषणा SOF_IPC_PANIC_EXCEPTION			(SOF_IPC_PANIC_MAGIC | 0x6)
#घोषणा SOF_IPC_PANIC_DEADLOCK			(SOF_IPC_PANIC_MAGIC | 0x7)
#घोषणा SOF_IPC_PANIC_STACK			(SOF_IPC_PANIC_MAGIC | 0x8)
#घोषणा SOF_IPC_PANIC_IDLE			(SOF_IPC_PANIC_MAGIC | 0x9)
#घोषणा SOF_IPC_PANIC_WFI			(SOF_IPC_PANIC_MAGIC | 0xa)
#घोषणा SOF_IPC_PANIC_ASSERT			(SOF_IPC_PANIC_MAGIC | 0xb)

/* panic info include filename and line number
 * filename array will not include null terminator अगर fully filled
 */
काष्ठा sof_ipc_panic_info अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक32_t code;			/* SOF_IPC_PANIC_ */
	uपूर्णांक8_t filename[SOF_TRACE_खाताNAME_SIZE];
	uपूर्णांक32_t linक्रमागत;
पूर्ण  __packed;

#पूर्ण_अगर
