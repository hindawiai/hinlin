<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 IBM Corporation
 *
 * Author: Ashley Lai <ashleydlai@gmail.com>
 *
 * Maपूर्णांकained by: <tpmdd-devel@lists.sourceक्रमge.net>
 *
 * Device driver क्रम TCG/TCPA TPM (trusted platक्रमm module).
 * Specअगरications at www.trustedcomputinggroup.org
 */

#अगर_अघोषित __TPM_IBMVTPM_H__
#घोषणा __TPM_IBMVTPM_H__

/* vTPM Message Format 1 */
काष्ठा ibmvtpm_crq अणु
	u8 valid;
	u8 msg;
	__be16 len;
	__be32 data;
	__be64 reserved;
पूर्ण __attribute__((packed, aligned(8)));

काष्ठा ibmvtpm_crq_queue अणु
	काष्ठा ibmvtpm_crq *crq_addr;
	u32 index;
	u32 num_entry;
	रुको_queue_head_t wq;
पूर्ण;

काष्ठा ibmvtpm_dev अणु
	काष्ठा device *dev;
	काष्ठा vio_dev *vdev;
	काष्ठा ibmvtpm_crq_queue crq_queue;
	dma_addr_t crq_dma_handle;
	u32 rtce_size;
	व्योम __iomem *rtce_buf;
	dma_addr_t rtce_dma_handle;
	spinlock_t rtce_lock;
	रुको_queue_head_t wq;
	u16 res_len;
	u32 vtpm_version;
	bool tpm_processing_cmd;
पूर्ण;

#घोषणा CRQ_RES_BUF_SIZE	PAGE_SIZE

/* Initialize CRQ */
#घोषणा INIT_CRQ_CMD		0xC001000000000000LL /* Init cmd */
#घोषणा INIT_CRQ_COMP_CMD	0xC002000000000000LL /* Init complete cmd */
#घोषणा INIT_CRQ_RES		0x01	/* Init respond */
#घोषणा INIT_CRQ_COMP_RES	0x02	/* Init complete respond */
#घोषणा VALID_INIT_CRQ		0xC0	/* Valid command क्रम init crq */

/* vTPM CRQ response is the message type | 0x80 */
#घोषणा VTPM_MSG_RES		0x80
#घोषणा IBMVTPM_VALID_CMD	0x80

/* vTPM CRQ message types */
#घोषणा VTPM_GET_VERSION			0x01
#घोषणा VTPM_GET_VERSION_RES			(0x01 | VTPM_MSG_RES)

#घोषणा VTPM_TPM_COMMAND			0x02
#घोषणा VTPM_TPM_COMMAND_RES			(0x02 | VTPM_MSG_RES)

#घोषणा VTPM_GET_RTCE_BUFFER_SIZE		0x03
#घोषणा VTPM_GET_RTCE_BUFFER_SIZE_RES		(0x03 | VTPM_MSG_RES)

#घोषणा VTPM_PREPARE_TO_SUSPEND			0x04
#घोषणा VTPM_PREPARE_TO_SUSPEND_RES		(0x04 | VTPM_MSG_RES)

#पूर्ण_अगर
