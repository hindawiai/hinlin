<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_HEADER_H__
#घोषणा __INCLUDE_SOUND_SOF_HEADER_H__

#समावेश <linux/types.h>
#समावेश <uapi/sound/sof/abi.h>

/** \चddtogroup sof_uapi uAPI
 *  SOF uAPI specअगरication.
 *  @अणु
 */

/*
 * IPC messages have a prefixed 32 bit identअगरier made up as follows :-
 *
 * 0xGCCCNNNN where
 * G is global cmd type (4 bits)
 * C is command type (12 bits)
 * I is the ID number (16 bits) - monotonic and overflows
 *
 * This is sent at the start of the IPM message in the mailbox. Messages should
 * not be sent in the करोorbell (special exceptions क्रम firmware .
 */

/* Global Message - Generic */
#घोषणा SOF_GLB_TYPE_SHIFT			28
#घोषणा SOF_GLB_TYPE_MASK			(0xfL << SOF_GLB_TYPE_SHIFT)
#घोषणा SOF_GLB_TYPE(x)				((x) << SOF_GLB_TYPE_SHIFT)

/* Command Message - Generic */
#घोषणा SOF_CMD_TYPE_SHIFT			16
#घोषणा SOF_CMD_TYPE_MASK			(0xfffL << SOF_CMD_TYPE_SHIFT)
#घोषणा SOF_CMD_TYPE(x)				((x) << SOF_CMD_TYPE_SHIFT)

/* Global Message Types */
#घोषणा SOF_IPC_GLB_REPLY			SOF_GLB_TYPE(0x1U)
#घोषणा SOF_IPC_GLB_COMPOUND			SOF_GLB_TYPE(0x2U)
#घोषणा SOF_IPC_GLB_TPLG_MSG			SOF_GLB_TYPE(0x3U)
#घोषणा SOF_IPC_GLB_PM_MSG			SOF_GLB_TYPE(0x4U)
#घोषणा SOF_IPC_GLB_COMP_MSG			SOF_GLB_TYPE(0x5U)
#घोषणा SOF_IPC_GLB_STREAM_MSG			SOF_GLB_TYPE(0x6U)
#घोषणा SOF_IPC_FW_READY			SOF_GLB_TYPE(0x7U)
#घोषणा SOF_IPC_GLB_DAI_MSG			SOF_GLB_TYPE(0x8U)
#घोषणा SOF_IPC_GLB_TRACE_MSG			SOF_GLB_TYPE(0x9U)
#घोषणा SOF_IPC_GLB_GDB_DEBUG			SOF_GLB_TYPE(0xAU)
#घोषणा SOF_IPC_GLB_TEST_MSG			SOF_GLB_TYPE(0xBU)
#घोषणा SOF_IPC_GLB_PROBE			SOF_GLB_TYPE(0xCU)
#घोषणा SOF_IPC_GLB_DEBUG			SOF_GLB_TYPE(0xDU)

/*
 * DSP Command Message Types
 */

/* topology */
#घोषणा SOF_IPC_TPLG_COMP_NEW			SOF_CMD_TYPE(0x001)
#घोषणा SOF_IPC_TPLG_COMP_FREE			SOF_CMD_TYPE(0x002)
#घोषणा SOF_IPC_TPLG_COMP_CONNECT		SOF_CMD_TYPE(0x003)
#घोषणा SOF_IPC_TPLG_PIPE_NEW			SOF_CMD_TYPE(0x010)
#घोषणा SOF_IPC_TPLG_PIPE_FREE			SOF_CMD_TYPE(0x011)
#घोषणा SOF_IPC_TPLG_PIPE_CONNECT		SOF_CMD_TYPE(0x012)
#घोषणा SOF_IPC_TPLG_PIPE_COMPLETE		SOF_CMD_TYPE(0x013)
#घोषणा SOF_IPC_TPLG_BUFFER_NEW			SOF_CMD_TYPE(0x020)
#घोषणा SOF_IPC_TPLG_BUFFER_FREE		SOF_CMD_TYPE(0x021)

/* PM */
#घोषणा SOF_IPC_PM_CTX_SAVE			SOF_CMD_TYPE(0x001)
#घोषणा SOF_IPC_PM_CTX_RESTORE			SOF_CMD_TYPE(0x002)
#घोषणा SOF_IPC_PM_CTX_SIZE			SOF_CMD_TYPE(0x003)
#घोषणा SOF_IPC_PM_CLK_SET			SOF_CMD_TYPE(0x004)
#घोषणा SOF_IPC_PM_CLK_GET			SOF_CMD_TYPE(0x005)
#घोषणा SOF_IPC_PM_CLK_REQ			SOF_CMD_TYPE(0x006)
#घोषणा SOF_IPC_PM_CORE_ENABLE			SOF_CMD_TYPE(0x007)
#घोषणा SOF_IPC_PM_GATE				SOF_CMD_TYPE(0x008)

/* component runसमय config - multiple dअगरferent types */
#घोषणा SOF_IPC_COMP_SET_VALUE			SOF_CMD_TYPE(0x001)
#घोषणा SOF_IPC_COMP_GET_VALUE			SOF_CMD_TYPE(0x002)
#घोषणा SOF_IPC_COMP_SET_DATA			SOF_CMD_TYPE(0x003)
#घोषणा SOF_IPC_COMP_GET_DATA			SOF_CMD_TYPE(0x004)
#घोषणा SOF_IPC_COMP_NOTIFICATION		SOF_CMD_TYPE(0x005)

/* DAI messages */
#घोषणा SOF_IPC_DAI_CONFIG			SOF_CMD_TYPE(0x001)
#घोषणा SOF_IPC_DAI_LOOPBACK			SOF_CMD_TYPE(0x002)

/* stream */
#घोषणा SOF_IPC_STREAM_PCM_PARAMS		SOF_CMD_TYPE(0x001)
#घोषणा SOF_IPC_STREAM_PCM_PARAMS_REPLY		SOF_CMD_TYPE(0x002)
#घोषणा SOF_IPC_STREAM_PCM_FREE			SOF_CMD_TYPE(0x003)
#घोषणा SOF_IPC_STREAM_TRIG_START		SOF_CMD_TYPE(0x004)
#घोषणा SOF_IPC_STREAM_TRIG_STOP		SOF_CMD_TYPE(0x005)
#घोषणा SOF_IPC_STREAM_TRIG_PAUSE		SOF_CMD_TYPE(0x006)
#घोषणा SOF_IPC_STREAM_TRIG_RELEASE		SOF_CMD_TYPE(0x007)
#घोषणा SOF_IPC_STREAM_TRIG_DRAIN		SOF_CMD_TYPE(0x008)
#घोषणा SOF_IPC_STREAM_TRIG_XRUN		SOF_CMD_TYPE(0x009)
#घोषणा SOF_IPC_STREAM_POSITION			SOF_CMD_TYPE(0x00a)
#घोषणा SOF_IPC_STREAM_VORBIS_PARAMS		SOF_CMD_TYPE(0x010)
#घोषणा SOF_IPC_STREAM_VORBIS_FREE		SOF_CMD_TYPE(0x011)

/* probe */
#घोषणा SOF_IPC_PROBE_INIT			SOF_CMD_TYPE(0x001)
#घोषणा SOF_IPC_PROBE_DEINIT			SOF_CMD_TYPE(0x002)
#घोषणा SOF_IPC_PROBE_DMA_ADD			SOF_CMD_TYPE(0x003)
#घोषणा SOF_IPC_PROBE_DMA_INFO			SOF_CMD_TYPE(0x004)
#घोषणा SOF_IPC_PROBE_DMA_REMOVE		SOF_CMD_TYPE(0x005)
#घोषणा SOF_IPC_PROBE_POINT_ADD			SOF_CMD_TYPE(0x006)
#घोषणा SOF_IPC_PROBE_POINT_INFO		SOF_CMD_TYPE(0x007)
#घोषणा SOF_IPC_PROBE_POINT_REMOVE		SOF_CMD_TYPE(0x008)

/* trace */
#घोषणा SOF_IPC_TRACE_DMA_PARAMS		SOF_CMD_TYPE(0x001)
#घोषणा SOF_IPC_TRACE_DMA_POSITION		SOF_CMD_TYPE(0x002)
#घोषणा SOF_IPC_TRACE_DMA_PARAMS_EXT		SOF_CMD_TYPE(0x003)
#घोषणा SOF_IPC_TRACE_FILTER_UPDATE		SOF_CMD_TYPE(0x004) /**< ABI3.17 */

/* debug */
#घोषणा SOF_IPC_DEBUG_MEM_USAGE			SOF_CMD_TYPE(0x001)

/* test */
#घोषणा SOF_IPC_TEST_IPC_FLOOD			SOF_CMD_TYPE(0x001)

/* Get message component id */
#घोषणा SOF_IPC_MESSAGE_ID(x)			((x) & 0xffff)

/* maximum message size क्रम mailbox Tx/Rx */
#घोषणा SOF_IPC_MSG_MAX_SIZE			384

/*
 * Structure Header - Header क्रम all IPC काष्ठाures except command काष्ठाs.
 * The size can be greater than the काष्ठाure size and that means there is
 * extended bespoke data beyond the end of the काष्ठाure including variable
 * arrays.
 */

काष्ठा sof_ipc_hdr अणु
	uपूर्णांक32_t size;			/**< size of काष्ठाure */
पूर्ण __packed;

/*
 * Command Header - Header क्रम all IPC commands. Identअगरies IPC message.
 * The size can be greater than the काष्ठाure size and that means there is
 * extended bespoke data beyond the end of the काष्ठाure including variable
 * arrays.
 */

काष्ठा sof_ipc_cmd_hdr अणु
	uपूर्णांक32_t size;			/**< size of काष्ठाure */
	uपूर्णांक32_t cmd;			/**< SOF_IPC_GLB_ + cmd */
पूर्ण __packed;

/*
 * Generic reply message. Some commands override this with their own reply
 * types that must include this at start.
 */
काष्ठा sof_ipc_reply अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	पूर्णांक32_t error;			/**< negative error numbers */
पूर्ण  __packed;

/*
 * Compound commands - SOF_IPC_GLB_COMPOUND.
 *
 * Compound commands are sent to the DSP as a single IPC operation. The
 * commands are split पूर्णांकo blocks and each block has a header. This header
 * identअगरies the command type and the number of commands beक्रमe the next
 * header.
 */

काष्ठा sof_ipc_compound_hdr अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t count;		/**< count of 0 means end of compound sequence */
पूर्ण  __packed;

/**
 * OOPS header architecture specअगरic data.
 */
काष्ठा sof_ipc_dsp_oops_arch_hdr अणु
	uपूर्णांक32_t arch;		/* Identअगरier of architecture */
	uपूर्णांक32_t totalsize;	/* Total size of oops message */
पूर्ण  __packed;

/**
 * OOPS header platक्रमm specअगरic data.
 */
काष्ठा sof_ipc_dsp_oops_plat_hdr अणु
	uपूर्णांक32_t configidhi;	/* ConfigID hi 32bits */
	uपूर्णांक32_t configidlo;	/* ConfigID lo 32bits */
	uपूर्णांक32_t numaregs;	/* Special regs num */
	uपूर्णांक32_t stackoffset;	/* Offset to stack poपूर्णांकer from beginning of
				 * oops message
				 */
	uपूर्णांक32_t stackptr;	/* Stack ptr */
पूर्ण  __packed;

/** @पूर्ण*/

#पूर्ण_अगर
