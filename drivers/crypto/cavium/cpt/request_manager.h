<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 Cavium, Inc.
 */

#अगर_अघोषित __REQUEST_MANAGER_H
#घोषणा __REQUEST_MANAGER_H

#समावेश "cpt_common.h"

#घोषणा TIME_IN_RESET_COUNT  5
#घोषणा COMPLETION_CODE_SIZE 8
#घोषणा COMPLETION_CODE_INIT 0
#घोषणा PENDING_THOLD  100
#घोषणा MAX_SG_IN_CNT 12
#घोषणा MAX_SG_OUT_CNT 13
#घोषणा SG_LIST_HDR_SIZE  8
#घोषणा MAX_BUF_CNT	16

जोड़ ctrl_info अणु
	u32 flags;
	काष्ठा अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
		u32 reserved0:26;
		u32 grp:3; /* Group bits */
		u32 dma_mode:2; /* DMA mode */
		u32 se_req:1;/* To SE core */
#अन्यथा
		u32 se_req:1; /* To SE core */
		u32 dma_mode:2; /* DMA mode */
		u32 grp:3; /* Group bits */
		u32 reserved0:26;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ opcode_info अणु
	u16 flags;
	काष्ठा अणु
		u8 major;
		u8 minor;
	पूर्ण s;
पूर्ण;

काष्ठा cptvf_request अणु
	जोड़ opcode_info opcode;
	u16 param1;
	u16 param2;
	u16 dlen;
पूर्ण;

काष्ठा buf_ptr अणु
	u8 *vptr;
	dma_addr_t dma_addr;
	u16 size;
पूर्ण;

काष्ठा cpt_request_info अणु
	u8 incnt; /* Number of input buffers */
	u8 outcnt; /* Number of output buffers */
	u16 rlen; /* Output length */
	जोड़ ctrl_info ctrl; /* User control inक्रमmation */
	काष्ठा cptvf_request req; /* Request Inक्रमmation (Core specअगरic) */

	bool may_sleep;

	काष्ठा buf_ptr in[MAX_BUF_CNT];
	काष्ठा buf_ptr out[MAX_BUF_CNT];

	व्योम (*callback)(पूर्णांक, व्योम *); /* Kernel ASYNC request callabck */
	व्योम *callback_arg; /* Kernel ASYNC request callabck arg */
पूर्ण;

काष्ठा sglist_component अणु
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

काष्ठा cpt_info_buffer अणु
	काष्ठा cpt_vf *cptvf;
	अचिन्हित दीर्घ समय_in;
	u8 extra_समय;

	काष्ठा cpt_request_info *req;
	dma_addr_t dptr_baddr;
	u32 dlen;
	dma_addr_t rptr_baddr;
	dma_addr_t comp_baddr;
	u8 *in_buffer;
	u8 *out_buffer;
	u8 *gather_components;
	u8 *scatter_components;

	काष्ठा pending_entry *pentry;
	अस्थिर u64 *completion_addr;
	अस्थिर u64 *alternate_caddr;
पूर्ण;

/*
 * CPT_INST_S software command definitions
 * Words EI (0-3)
 */
जोड़ vq_cmd_word0 अणु
	u64 u64;
	काष्ठा अणु
		__be16 opcode;
		__be16 param1;
		__be16 param2;
		__be16 dlen;
	पूर्ण s;
पूर्ण;

जोड़ vq_cmd_word3 अणु
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

काष्ठा cpt_vq_command अणु
	जोड़ vq_cmd_word0 cmd;
	u64 dptr;
	u64 rptr;
	जोड़ vq_cmd_word3 cptr;
पूर्ण;

व्योम vq_post_process(काष्ठा cpt_vf *cptvf, u32 qno);
पूर्णांक process_request(काष्ठा cpt_vf *cptvf, काष्ठा cpt_request_info *req);
#पूर्ण_अगर /* __REQUEST_MANAGER_H */
