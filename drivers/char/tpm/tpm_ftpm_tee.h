<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) Microsoft Corporation
 */

#अगर_अघोषित __TPM_FTPM_TEE_H__
#घोषणा __TPM_FTPM_TEE_H__

#समावेश <linux/tee_drv.h>
#समावेश <linux/tpm.h>
#समावेश <linux/uuid.h>

/* The TAFs ID implemented in this TA */
#घोषणा FTPM_OPTEE_TA_SUBMIT_COMMAND  (0)
#घोषणा FTPM_OPTEE_TA_EMULATE_PPI     (1)

/* max. buffer size supported by fTPM  */
#घोषणा MAX_COMMAND_SIZE       4096
#घोषणा MAX_RESPONSE_SIZE      4096

/**
 * काष्ठा ftpm_tee_निजी - fTPM's निजी data
 * @chip:     काष्ठा tpm_chip instance रेजिस्टरed with tpm framework.
 * @state:    पूर्णांकernal state
 * @session:  fTPM TA session identअगरier.
 * @resp_len: cached response buffer length.
 * @resp_buf: cached response buffer.
 * @ctx:      TEE context handler.
 * @shm:      Memory pool shared with fTPM TA in TEE.
 */
काष्ठा ftpm_tee_निजी अणु
	काष्ठा tpm_chip *chip;
	u32 session;
	माप_प्रकार resp_len;
	u8 resp_buf[MAX_RESPONSE_SIZE];
	काष्ठा tee_context *ctx;
	काष्ठा tee_shm *shm;
पूर्ण;

#पूर्ण_अगर /* __TPM_FTPM_TEE_H__ */
