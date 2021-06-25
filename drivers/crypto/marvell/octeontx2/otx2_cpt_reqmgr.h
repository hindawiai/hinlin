<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (C) 2020 Marvell.
 */

#अगर_अघोषित __OTX2_CPT_REQMGR_H
#घोषणा __OTX2_CPT_REQMGR_H

#समावेश "otx2_cpt_common.h"

/* Completion code size and initial value */
#घोषणा OTX2_CPT_COMPLETION_CODE_SIZE 8
#घोषणा OTX2_CPT_COMPLETION_CODE_INIT OTX2_CPT_COMP_E_NOTDONE
/*
 * Maximum total number of SG buffers is 100, we भागide it equally
 * between input and output
 */
#घोषणा OTX2_CPT_MAX_SG_IN_CNT  50
#घोषणा OTX2_CPT_MAX_SG_OUT_CNT 50

/* DMA mode direct or SG */
#घोषणा OTX2_CPT_DMA_MODE_सूचीECT 0
#घोषणा OTX2_CPT_DMA_MODE_SG     1

/* Context source CPTR or DPTR */
#घोषणा OTX2_CPT_FROM_CPTR 0
#घोषणा OTX2_CPT_FROM_DPTR 1

#घोषणा OTX2_CPT_MAX_REQ_SIZE 65535

जोड़ otx2_cpt_opcode अणु
	u16 flags;
	काष्ठा अणु
		u8 major;
		u8 minor;
	पूर्ण s;
पूर्ण;

काष्ठा otx2_cptvf_request अणु
	u32 param1;
	u32 param2;
	u16 dlen;
	जोड़ otx2_cpt_opcode opcode;
पूर्ण;

/*
 * CPT_INST_S software command definitions
 * Words EI (0-3)
 */
जोड़ otx2_cpt_iq_cmd_word0 अणु
	u64 u;
	काष्ठा अणु
		__be16 opcode;
		__be16 param1;
		__be16 param2;
		__be16 dlen;
	पूर्ण s;
पूर्ण;

जोड़ otx2_cpt_iq_cmd_word3 अणु
	u64 u;
	काष्ठा अणु
		u64 cptr:61;
		u64 grp:3;
	पूर्ण s;
पूर्ण;

काष्ठा otx2_cpt_iq_command अणु
	जोड़ otx2_cpt_iq_cmd_word0 cmd;
	u64 dptr;
	u64 rptr;
	जोड़ otx2_cpt_iq_cmd_word3 cptr;
पूर्ण;

काष्ठा otx2_cpt_pending_entry अणु
	व्योम *completion_addr;	/* Completion address */
	व्योम *info;
	/* Kernel async request callback */
	व्योम (*callback)(पूर्णांक status, व्योम *arg1, व्योम *arg2);
	काष्ठा crypto_async_request *areq; /* Async request callback arg */
	u8 resume_sender;	/* Notअगरy sender to resume sending requests */
	u8 busy;		/* Entry status (मुक्त/busy) */
पूर्ण;

काष्ठा otx2_cpt_pending_queue अणु
	काष्ठा otx2_cpt_pending_entry *head; /* Head of the queue */
	u32 front;		/* Process work from here */
	u32 rear;		/* Append new work here */
	u32 pending_count;	/* Pending requests count */
	u32 qlen;		/* Queue length */
	spinlock_t lock;	/* Queue lock */
पूर्ण;

काष्ठा otx2_cpt_buf_ptr अणु
	u8 *vptr;
	dma_addr_t dma_addr;
	u16 size;
पूर्ण;

जोड़ otx2_cpt_ctrl_info अणु
	u32 flags;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u32 reserved_6_31:26;
		u32 grp:3;	/* Group bits */
		u32 dma_mode:2;	/* DMA mode */
		u32 se_req:1;	/* To SE core */
#अन्यथा
		u32 se_req:1;	/* To SE core */
		u32 dma_mode:2;	/* DMA mode */
		u32 grp:3;	/* Group bits */
		u32 reserved_6_31:26;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

काष्ठा otx2_cpt_req_info अणु
	/* Kernel async request callback */
	व्योम (*callback)(पूर्णांक status, व्योम *arg1, व्योम *arg2);
	काष्ठा crypto_async_request *areq; /* Async request callback arg */
	काष्ठा otx2_cptvf_request req;/* Request inक्रमmation (core specअगरic) */
	जोड़ otx2_cpt_ctrl_info ctrl;/* User control inक्रमmation */
	काष्ठा otx2_cpt_buf_ptr in[OTX2_CPT_MAX_SG_IN_CNT];
	काष्ठा otx2_cpt_buf_ptr out[OTX2_CPT_MAX_SG_OUT_CNT];
	u8 *iv_out;     /* IV to send back */
	u16 rlen;	/* Output length */
	u8 in_cnt;	/* Number of input buffers */
	u8 out_cnt;	/* Number of output buffers */
	u8 req_type;	/* Type of request */
	u8 is_enc;	/* Is a request an encryption request */
	u8 is_trunc_hmac;/* Is truncated hmac used */
पूर्ण;

काष्ठा otx2_cpt_inst_info अणु
	काष्ठा otx2_cpt_pending_entry *pentry;
	काष्ठा otx2_cpt_req_info *req;
	काष्ठा pci_dev *pdev;
	व्योम *completion_addr;
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

काष्ठा otx2_cpt_sglist_component अणु
	__be16 len0;
	__be16 len1;
	__be16 len2;
	__be16 len3;
	__be64 ptr0;
	__be64 ptr1;
	__be64 ptr2;
	__be64 ptr3;
पूर्ण;

अटल अंतरभूत व्योम otx2_cpt_info_destroy(काष्ठा pci_dev *pdev,
					 काष्ठा otx2_cpt_inst_info *info)
अणु
	काष्ठा otx2_cpt_req_info *req;
	पूर्णांक i;

	अगर (info->dptr_baddr)
		dma_unmap_single(&pdev->dev, info->dptr_baddr,
				 info->dma_len, DMA_BIसूचीECTIONAL);

	अगर (info->req) अणु
		req = info->req;
		क्रम (i = 0; i < req->out_cnt; i++) अणु
			अगर (req->out[i].dma_addr)
				dma_unmap_single(&pdev->dev,
						 req->out[i].dma_addr,
						 req->out[i].size,
						 DMA_BIसूचीECTIONAL);
		पूर्ण

		क्रम (i = 0; i < req->in_cnt; i++) अणु
			अगर (req->in[i].dma_addr)
				dma_unmap_single(&pdev->dev,
						 req->in[i].dma_addr,
						 req->in[i].size,
						 DMA_BIसूचीECTIONAL);
		पूर्ण
	पूर्ण
	kमुक्त(info);
पूर्ण

काष्ठा otx2_cptlf_wqe;
पूर्णांक otx2_cpt_करो_request(काष्ठा pci_dev *pdev, काष्ठा otx2_cpt_req_info *req,
			पूर्णांक cpu_num);
व्योम otx2_cpt_post_process(काष्ठा otx2_cptlf_wqe *wqe);
पूर्णांक otx2_cpt_get_kcrypto_eng_grp_num(काष्ठा pci_dev *pdev);

#पूर्ण_अगर /* __OTX2_CPT_REQMGR_H */
