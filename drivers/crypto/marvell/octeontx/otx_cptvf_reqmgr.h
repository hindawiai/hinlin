<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Marvell OcteonTX CPT driver
 *
 * Copyright (C) 2019 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __OTX_CPTVF_REQUEST_MANAGER_H
#घोषणा __OTX_CPTVF_REQUEST_MANAGER_H

#समावेश <linux/types.h>
#समावेश <linux/crypto.h>
#समावेश <linux/pci.h>
#समावेश "otx_cpt_hw_types.h"

/*
 * Maximum total number of SG buffers is 100, we भागide it equally
 * between input and output
 */
#घोषणा OTX_CPT_MAX_SG_IN_CNT		50
#घोषणा OTX_CPT_MAX_SG_OUT_CNT		50

/* DMA mode direct or SG */
#घोषणा OTX_CPT_DMA_सूचीECT_सूचीECT	0
#घोषणा OTX_CPT_DMA_GATHER_SCATTER	1

/* Context source CPTR or DPTR */
#घोषणा OTX_CPT_FROM_CPTR		0
#घोषणा OTX_CPT_FROM_DPTR		1

/* CPT inकाष्ठाion queue alignment */
#घोषणा OTX_CPT_INST_Q_ALIGNMENT	128
#घोषणा OTX_CPT_MAX_REQ_SIZE		65535

/* Default command समयout in seconds */
#घोषणा OTX_CPT_COMMAND_TIMEOUT		4
#घोषणा OTX_CPT_TIMER_HOLD		0x03F
#घोषणा OTX_CPT_COUNT_HOLD		32
#घोषणा OTX_CPT_TIME_IN_RESET_COUNT     5

/* Minimum and maximum values क्रम पूर्णांकerrupt coalescing */
#घोषणा OTX_CPT_COALESC_MIN_TIME_WAIT	0x0
#घोषणा OTX_CPT_COALESC_MAX_TIME_WAIT	((1<<16)-1)
#घोषणा OTX_CPT_COALESC_MIN_NUM_WAIT	0x0
#घोषणा OTX_CPT_COALESC_MAX_NUM_WAIT	((1<<20)-1)

जोड़ otx_cpt_opcode_info अणु
	u16 flags;
	काष्ठा अणु
		u8 major;
		u8 minor;
	पूर्ण s;
पूर्ण;

काष्ठा otx_cptvf_request अणु
	u32 param1;
	u32 param2;
	u16 dlen;
	जोड़ otx_cpt_opcode_info opcode;
पूर्ण;

काष्ठा otx_cpt_buf_ptr अणु
	u8 *vptr;
	dma_addr_t dma_addr;
	u16 size;
पूर्ण;

जोड़ otx_cpt_ctrl_info अणु
	u32 flags;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u32 reserved0:26;
		u32 grp:3;	/* Group bits */
		u32 dma_mode:2;	/* DMA mode */
		u32 se_req:1;	/* To SE core */
#अन्यथा
		u32 se_req:1;	/* To SE core */
		u32 dma_mode:2;	/* DMA mode */
		u32 grp:3;	/* Group bits */
		u32 reserved0:26;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/*
 * CPT_INST_S software command definitions
 * Words EI (0-3)
 */
जोड़ otx_cpt_iq_cmd_word0 अणु
	u64 u64;
	काष्ठा अणु
		__be16 opcode;
		__be16 param1;
		__be16 param2;
		__be16 dlen;
	पूर्ण s;
पूर्ण;

जोड़ otx_cpt_iq_cmd_word3 अणु
	u64 u64;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u64 grp:3;
		u64 cptr:61;
#अन्यथा
		u64 cptr:61;
		u64 grp:3;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

काष्ठा otx_cpt_iq_cmd अणु
	जोड़ otx_cpt_iq_cmd_word0 cmd;
	u64 dptr;
	u64 rptr;
	जोड़ otx_cpt_iq_cmd_word3 cptr;
पूर्ण;

काष्ठा otx_cpt_sglist_component अणु
	जोड़ अणु
		u64 len;
		काष्ठा अणु
			__be16 len0;
			__be16 len1;
			__be16 len2;
			__be16 len3;
		पूर्ण s;
	पूर्ण u;
	__be64 ptr0;
	__be64 ptr1;
	__be64 ptr2;
	__be64 ptr3;
पूर्ण;

काष्ठा otx_cpt_pending_entry अणु
	u64 *completion_addr;	/* Completion address */
	काष्ठा otx_cpt_info_buffer *info;
	/* Kernel async request callback */
	व्योम (*callback)(पूर्णांक status, व्योम *arg1, व्योम *arg2);
	काष्ठा crypto_async_request *areq; /* Async request callback arg */
	u8 resume_sender;	/* Notअगरy sender to resume sending requests */
	u8 busy;		/* Entry status (मुक्त/busy) */
पूर्ण;

काष्ठा otx_cpt_pending_queue अणु
	काष्ठा otx_cpt_pending_entry *head;	/* Head of the queue */
	u32 front;			/* Process work from here */
	u32 rear;			/* Append new work here */
	u32 pending_count;		/* Pending requests count */
	u32 qlen;			/* Queue length */
	spinlock_t lock;		/* Queue lock */
पूर्ण;

काष्ठा otx_cpt_req_info अणु
	/* Kernel async request callback */
	व्योम (*callback)(पूर्णांक status, व्योम *arg1, व्योम *arg2);
	काष्ठा crypto_async_request *areq; /* Async request callback arg */
	काष्ठा otx_cptvf_request req;/* Request inक्रमmation (core specअगरic) */
	जोड़ otx_cpt_ctrl_info ctrl;/* User control inक्रमmation */
	काष्ठा otx_cpt_buf_ptr in[OTX_CPT_MAX_SG_IN_CNT];
	काष्ठा otx_cpt_buf_ptr out[OTX_CPT_MAX_SG_OUT_CNT];
	u8 *iv_out;     /* IV to send back */
	u16 rlen;	/* Output length */
	u8 incnt;	/* Number of input buffers */
	u8 outcnt;	/* Number of output buffers */
	u8 req_type;	/* Type of request */
	u8 is_enc;	/* Is a request an encryption request */
	u8 is_trunc_hmac;/* Is truncated hmac used */
पूर्ण;

काष्ठा otx_cpt_info_buffer अणु
	काष्ठा otx_cpt_pending_entry *pentry;
	काष्ठा otx_cpt_req_info *req;
	काष्ठा pci_dev *pdev;
	u64 *completion_addr;
	u8 *out_buffer;
	u8 *in_buffer;
	dma_addr_t dptr_baddr;
	dma_addr_t rptr_baddr;
	dma_addr_t comp_baddr;
	अचिन्हित दीर्घ समय_in;
	u32 dlen;
	u32 dma_len;
	u8 extra_समय;
पूर्ण;

अटल अंतरभूत व्योम करो_request_cleanup(काष्ठा pci_dev *pdev,
				      काष्ठा otx_cpt_info_buffer *info)
अणु
	काष्ठा otx_cpt_req_info *req;
	पूर्णांक i;

	अगर (info->dptr_baddr)
		dma_unmap_single(&pdev->dev, info->dptr_baddr,
				 info->dma_len, DMA_BIसूचीECTIONAL);

	अगर (info->req) अणु
		req = info->req;
		क्रम (i = 0; i < req->outcnt; i++) अणु
			अगर (req->out[i].dma_addr)
				dma_unmap_single(&pdev->dev,
						 req->out[i].dma_addr,
						 req->out[i].size,
						 DMA_BIसूचीECTIONAL);
		पूर्ण

		क्रम (i = 0; i < req->incnt; i++) अणु
			अगर (req->in[i].dma_addr)
				dma_unmap_single(&pdev->dev,
						 req->in[i].dma_addr,
						 req->in[i].size,
						 DMA_BIसूचीECTIONAL);
		पूर्ण
	पूर्ण
	kमुक्त_sensitive(info);
पूर्ण

काष्ठा otx_cptvf_wqe;
व्योम otx_cpt_dump_sg_list(काष्ठा pci_dev *pdev, काष्ठा otx_cpt_req_info *req);
व्योम otx_cpt_post_process(काष्ठा otx_cptvf_wqe *wqe);
पूर्णांक otx_cpt_करो_request(काष्ठा pci_dev *pdev, काष्ठा otx_cpt_req_info *req,
		       पूर्णांक cpu_num);

#पूर्ण_अगर /* __OTX_CPTVF_REQUEST_MANAGER_H */
