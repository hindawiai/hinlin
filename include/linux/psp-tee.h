<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * AMD Trusted Execution Environment (TEE) पूर्णांकerface
 *
 * Author: Rijo Thomas <Rijo-john.Thomas@amd.com>
 *
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 */

#अगर_अघोषित __PSP_TEE_H_
#घोषणा __PSP_TEE_H_

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

/* This file defines the Trusted Execution Environment (TEE) पूर्णांकerface commands
 * and the API exported by AMD Secure Processor driver to communicate with
 * AMD-TEE Trusted OS.
 */

/**
 * क्रमागत tee_cmd_id - TEE Interface Command IDs
 * @TEE_CMD_ID_LOAD_TA:          Load Trusted Application (TA) binary पूर्णांकo
 *                               TEE environment
 * @TEE_CMD_ID_UNLOAD_TA:        Unload TA binary from TEE environment
 * @TEE_CMD_ID_OPEN_SESSION:     Open session with loaded TA
 * @TEE_CMD_ID_CLOSE_SESSION:    Close session with loaded TA
 * @TEE_CMD_ID_INVOKE_CMD:       Invoke a command with loaded TA
 * @TEE_CMD_ID_MAP_SHARED_MEM:   Map shared memory
 * @TEE_CMD_ID_UNMAP_SHARED_MEM: Unmap shared memory
 */
क्रमागत tee_cmd_id अणु
	TEE_CMD_ID_LOAD_TA = 1,
	TEE_CMD_ID_UNLOAD_TA,
	TEE_CMD_ID_OPEN_SESSION,
	TEE_CMD_ID_CLOSE_SESSION,
	TEE_CMD_ID_INVOKE_CMD,
	TEE_CMD_ID_MAP_SHARED_MEM,
	TEE_CMD_ID_UNMAP_SHARED_MEM,
पूर्ण;

#अगर_घोषित CONFIG_CRYPTO_DEV_SP_PSP
/**
 * psp_tee_process_cmd() - Process command in Trusted Execution Environment
 * @cmd_id:     TEE command ID (&क्रमागत tee_cmd_id)
 * @buf:        Command buffer क्रम TEE processing. On success, is updated
 *              with the response
 * @len:        Length of command buffer in bytes
 * @status:     On success, holds the TEE command execution status
 *
 * This function submits a command to the Trusted OS क्रम processing in the
 * TEE environment and रुकोs क्रम a response or until the command बार out.
 *
 * Returns:
 * 0 अगर TEE successfully processed the command
 * -%ENODEV    अगर PSP device not available
 * -%EINVAL    अगर invalid input
 * -%ETIMEDOUT अगर TEE command समयd out
 * -%EBUSY     अगर PSP device is not responsive
 */
पूर्णांक psp_tee_process_cmd(क्रमागत tee_cmd_id cmd_id, व्योम *buf, माप_प्रकार len,
			u32 *status);

/**
 * psp_check_tee_status() - Checks whether there is a TEE which a driver can
 * talk to.
 *
 * This function can be used by AMD-TEE driver to query अगर there is TEE with
 * which it can communicate.
 *
 * Returns:
 * 0          अगर the device has TEE
 * -%ENODEV   अगर there is no TEE available
 */
पूर्णांक psp_check_tee_status(व्योम);

#अन्यथा /* !CONFIG_CRYPTO_DEV_SP_PSP */

अटल अंतरभूत पूर्णांक psp_tee_process_cmd(क्रमागत tee_cmd_id cmd_id, व्योम *buf,
				      माप_प्रकार len, u32 *status)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक psp_check_tee_status(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_SP_PSP */
#पूर्ण_अगर /* __PSP_TEE_H_ */
