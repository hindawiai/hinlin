<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 */

/*
 * This file has definitions related to Host and AMD-TEE Trusted OS पूर्णांकerface.
 * These definitions must match the definitions on the TEE side.
 */

#अगर_अघोषित AMDTEE_IF_H
#घोषणा AMDTEE_IF_H

#समावेश <linux/types.h>

/*****************************************************************************
 ** TEE Param
 ******************************************************************************/
#घोषणा TEE_MAX_PARAMS		4

/**
 * काष्ठा memref - memory reference काष्ठाure
 * @buf_id:    buffer ID of the buffer mapped by TEE_CMD_ID_MAP_SHARED_MEM
 * @offset:    offset in bytes from beginning of the buffer
 * @size:      data size in bytes
 */
काष्ठा memref अणु
	u32 buf_id;
	u32 offset;
	u32 size;
पूर्ण;

काष्ठा value अणु
	u32 a;
	u32 b;
पूर्ण;

/*
 * Parameters passed to खोलो_session or invoke_command
 */
जोड़ tee_op_param अणु
	काष्ठा memref mref;
	काष्ठा value val;
पूर्ण;

काष्ठा tee_operation अणु
	u32 param_types;
	जोड़ tee_op_param params[TEE_MAX_PARAMS];
पूर्ण;

/* Must be same as in GP TEE specअगरication */
#घोषणा TEE_OP_PARAM_TYPE_NONE                  0
#घोषणा TEE_OP_PARAM_TYPE_VALUE_INPUT           1
#घोषणा TEE_OP_PARAM_TYPE_VALUE_OUTPUT          2
#घोषणा TEE_OP_PARAM_TYPE_VALUE_INOUT           3
#घोषणा TEE_OP_PARAM_TYPE_INVALID               4
#घोषणा TEE_OP_PARAM_TYPE_MEMREF_INPUT          5
#घोषणा TEE_OP_PARAM_TYPE_MEMREF_OUTPUT         6
#घोषणा TEE_OP_PARAM_TYPE_MEMREF_INOUT          7

#घोषणा TEE_PARAM_TYPE_GET(t, i)        (((t) >> ((i) * 4)) & 0xF)
#घोषणा TEE_PARAM_TYPES(t0, t1, t2, t3) \
	((t0) | ((t1) << 4) | ((t2) << 8) | ((t3) << 12))

/*****************************************************************************
 ** TEE Commands
 *****************************************************************************/

/*
 * The shared memory between rich world and secure world may be physically
 * non-contiguous. Below काष्ठाures are meant to describe a shared memory region
 * via scatter/gather (sg) list
 */

/**
 * काष्ठा tee_sg_desc - sg descriptor क्रम a physically contiguous buffer
 * @low_addr: [in] bits[31:0] of buffer's physical address. Must be 4KB aligned
 * @hi_addr:  [in] bits[63:32] of the buffer's physical address
 * @size:     [in] size in bytes (must be multiple of 4KB)
 */
काष्ठा tee_sg_desc अणु
	u32 low_addr;
	u32 hi_addr;
	u32 size;
पूर्ण;

/**
 * काष्ठा tee_sg_list - काष्ठाure describing a scatter/gather list
 * @count:   [in] number of sg descriptors
 * @size:    [in] total size of all buffers in the list. Must be multiple of 4KB
 * @buf:     [in] list of sg buffer descriptors
 */
#घोषणा TEE_MAX_SG_DESC 64
काष्ठा tee_sg_list अणु
	u32 count;
	u32 size;
	काष्ठा tee_sg_desc buf[TEE_MAX_SG_DESC];
पूर्ण;

/**
 * काष्ठा tee_cmd_map_shared_mem - command to map shared memory
 * @buf_id:    [out] वापस buffer ID value
 * @sg_list:   [in] list describing memory to be mapped
 */
काष्ठा tee_cmd_map_shared_mem अणु
	u32 buf_id;
	काष्ठा tee_sg_list sg_list;
पूर्ण;

/**
 * काष्ठा tee_cmd_unmap_shared_mem - command to unmap shared memory
 * @buf_id:    [in] buffer ID of memory to be unmapped
 */
काष्ठा tee_cmd_unmap_shared_mem अणु
	u32 buf_id;
पूर्ण;

/**
 * काष्ठा tee_cmd_load_ta - load Trusted Application (TA) binary पूर्णांकo TEE
 * @low_addr:    [in] bits [31:0] of the physical address of the TA binary
 * @hi_addr:     [in] bits [63:32] of the physical address of the TA binary
 * @size:        [in] size of TA binary in bytes
 * @ta_handle:   [out] वापस handle of the loaded TA
 */
काष्ठा tee_cmd_load_ta अणु
	u32 low_addr;
	u32 hi_addr;
	u32 size;
	u32 ta_handle;
पूर्ण;

/**
 * काष्ठा tee_cmd_unload_ta - command to unload TA binary from TEE environment
 * @ta_handle:    [in] handle of the loaded TA to be unloaded
 */
काष्ठा tee_cmd_unload_ta अणु
	u32 ta_handle;
पूर्ण;

/**
 * काष्ठा tee_cmd_खोलो_session - command to call TA_OpenSessionEntryPoपूर्णांक in TA
 * @ta_handle:      [in] handle of the loaded TA
 * @session_info:   [out] poपूर्णांकer to TA allocated session data
 * @op:             [in/out] operation parameters
 * @वापस_origin:  [out] origin of वापस code after TEE processing
 */
काष्ठा tee_cmd_खोलो_session अणु
	u32 ta_handle;
	u32 session_info;
	काष्ठा tee_operation op;
	u32 वापस_origin;
पूर्ण;

/**
 * काष्ठा tee_cmd_बंद_session - command to call TA_CloseSessionEntryPoपूर्णांक()
 *                                in TA
 * @ta_handle:      [in] handle of the loaded TA
 * @session_info:   [in] poपूर्णांकer to TA allocated session data
 */
काष्ठा tee_cmd_बंद_session अणु
	u32 ta_handle;
	u32 session_info;
पूर्ण;

/**
 * काष्ठा tee_cmd_invoke_cmd - command to call TA_InvokeCommandEntryPoपूर्णांक() in
 *                             TA
 * @ta_handle:     [in] handle of the loaded TA
 * @cmd_id:        [in] TA command ID
 * @session_info:  [in] poपूर्णांकer to TA allocated session data
 * @op:            [in/out] operation parameters
 * @वापस_origin: [out] origin of वापस code after TEE processing
 */
काष्ठा tee_cmd_invoke_cmd अणु
	u32 ta_handle;
	u32 cmd_id;
	u32 session_info;
	काष्ठा tee_operation op;
	u32 वापस_origin;
पूर्ण;

#पूर्ण_अगर /*AMDTEE_IF_H*/
