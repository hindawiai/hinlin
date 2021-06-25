<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright (C) 2019,2021 Advanced Micro Devices, Inc.
 *
 * Author: Rijo Thomas <Rijo-john.Thomas@amd.com>
 * Author: Devaraj Rangasamy <Devaraj.Rangasamy@amd.com>
 *
 */

/* This file describes the TEE communication पूर्णांकerface between host and AMD
 * Secure Processor
 */

#अगर_अघोषित __TEE_DEV_H__
#घोषणा __TEE_DEV_H__

#समावेश <linux/device.h>
#समावेश <linux/mutex.h>

#घोषणा TEE_DEFAULT_TIMEOUT		10
#घोषणा MAX_BUFFER_SIZE			988

/**
 * क्रमागत tee_ring_cmd_id - TEE पूर्णांकerface commands क्रम ring buffer configuration
 * @TEE_RING_INIT_CMD:		Initialize ring buffer
 * @TEE_RING_DESTROY_CMD:	Destroy ring buffer
 * @TEE_RING_MAX_CMD:		Maximum command id
 */
क्रमागत tee_ring_cmd_id अणु
	TEE_RING_INIT_CMD		= 0x00010000,
	TEE_RING_DESTROY_CMD		= 0x00020000,
	TEE_RING_MAX_CMD		= 0x000F0000,
पूर्ण;

/**
 * काष्ठा tee_init_ring_cmd - Command to init TEE ring buffer
 * @low_addr:  bits [31:0] of the physical address of ring buffer
 * @hi_addr:   bits [63:32] of the physical address of ring buffer
 * @size:      size of ring buffer in bytes
 */
काष्ठा tee_init_ring_cmd अणु
	u32 low_addr;
	u32 hi_addr;
	u32 size;
पूर्ण;

#घोषणा MAX_RING_BUFFER_ENTRIES		32

/**
 * काष्ठा ring_buf_manager - Helper काष्ठाure to manage ring buffer.
 * @ring_start:  starting address of ring buffer
 * @ring_size:   size of ring buffer in bytes
 * @ring_pa:     physical address of ring buffer
 * @wptr:        index to the last written entry in ring buffer
 */
काष्ठा ring_buf_manager अणु
	काष्ठा mutex mutex;	/* synchronizes access to ring buffer */
	व्योम *ring_start;
	u32 ring_size;
	phys_addr_t ring_pa;
	u32 wptr;
पूर्ण;

काष्ठा psp_tee_device अणु
	काष्ठा device *dev;
	काष्ठा psp_device *psp;
	व्योम __iomem *io_regs;
	काष्ठा tee_vdata *vdata;
	काष्ठा ring_buf_manager rb_mgr;
पूर्ण;

/**
 * क्रमागत tee_cmd_state - TEE command states क्रम the ring buffer पूर्णांकerface
 * @TEE_CMD_STATE_INIT:      initial state of command when sent from host
 * @TEE_CMD_STATE_PROCESS:   command being processed by TEE environment
 * @TEE_CMD_STATE_COMPLETED: command processing completed
 */
क्रमागत tee_cmd_state अणु
	TEE_CMD_STATE_INIT,
	TEE_CMD_STATE_PROCESS,
	TEE_CMD_STATE_COMPLETED,
पूर्ण;

/**
 * क्रमागत cmd_resp_state - TEE command's response status मुख्यtained by driver
 * @CMD_RESPONSE_INVALID:      initial state when no command is written to ring
 * @CMD_WAITING_FOR_RESPONSE:  driver रुकोing क्रम response from TEE
 * @CMD_RESPONSE_TIMEDOUT:     failed to get response from TEE
 * @CMD_RESPONSE_COPIED:       driver has copied response from TEE
 */
क्रमागत cmd_resp_state अणु
	CMD_RESPONSE_INVALID,
	CMD_WAITING_FOR_RESPONSE,
	CMD_RESPONSE_TIMEDOUT,
	CMD_RESPONSE_COPIED,
पूर्ण;

/**
 * काष्ठा tee_ring_cmd - Structure of the command buffer in TEE ring
 * @cmd_id:      refers to &क्रमागत tee_cmd_id. Command id क्रम the ring buffer
 *               पूर्णांकerface
 * @cmd_state:   refers to &क्रमागत tee_cmd_state
 * @status:      status of TEE command execution
 * @res0:        reserved region
 * @pdata:       निजी data (currently unused)
 * @res1:        reserved region
 * @buf:         TEE command specअगरic buffer
 * @flag:	 refers to &क्रमागत cmd_resp_state
 */
काष्ठा tee_ring_cmd अणु
	u32 cmd_id;
	u32 cmd_state;
	u32 status;
	u32 res0[1];
	u64 pdata;
	u32 res1[2];
	u8 buf[MAX_BUFFER_SIZE];
	u32 flag;

	/* Total size: 1024 bytes */
पूर्ण __packed;

पूर्णांक tee_dev_init(काष्ठा psp_device *psp);
व्योम tee_dev_destroy(काष्ठा psp_device *psp);

#पूर्ण_अगर /* __TEE_DEV_H__ */
