<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#अगर_अघोषित __BFA_MSGQ_H__
#घोषणा __BFA_MSGQ_H__

#समावेश "bfa_defs.h"
#समावेश "bfi.h"
#समावेश "bfa_ioc.h"
#समावेश "bfa_cs.h"

#घोषणा BFA_MSGQ_FREE_CNT(_q)						\
	(((_q)->consumer_index - (_q)->producer_index - 1) & ((_q)->depth - 1))

#घोषणा BFA_MSGQ_INDX_ADD(_q_indx, _qe_num, _q_depth)			\
	((_q_indx) = (((_q_indx) + (_qe_num)) & ((_q_depth) - 1)))

#घोषणा BFA_MSGQ_CMDQ_NUM_ENTRY		128
#घोषणा BFA_MSGQ_CMDQ_SIZE						\
	(BFI_MSGQ_CMD_ENTRY_SIZE * BFA_MSGQ_CMDQ_NUM_ENTRY)

#घोषणा BFA_MSGQ_RSPQ_NUM_ENTRY		128
#घोषणा BFA_MSGQ_RSPQ_SIZE						\
	(BFI_MSGQ_RSP_ENTRY_SIZE * BFA_MSGQ_RSPQ_NUM_ENTRY)

#घोषणा bfa_msgq_cmd_set(_cmd, _cbfn, _cbarg, _msg_size, _msg_hdr)	\
करो अणु									\
	(_cmd)->cbfn = (_cbfn);						\
	(_cmd)->cbarg = (_cbarg);					\
	(_cmd)->msg_size = (_msg_size);					\
	(_cmd)->msg_hdr = (_msg_hdr);					\
पूर्ण जबतक (0)

काष्ठा bfa_msgq;

प्रकार व्योम (*bfa_msgq_cmdcbfn_t)(व्योम *cbarg, क्रमागत bfa_status status);

काष्ठा bfa_msgq_cmd_entry अणु
	काष्ठा list_head				qe;
	bfa_msgq_cmdcbfn_t		cbfn;
	व्योम				*cbarg;
	माप_प्रकार				msg_size;
	काष्ठा bfi_msgq_mhdr *msg_hdr;
पूर्ण;

क्रमागत bfa_msgq_cmdq_flags अणु
	BFA_MSGQ_CMDQ_F_DB_UPDATE	= 1,
पूर्ण;

काष्ठा bfa_msgq_cmdq अणु
	bfa_fsm_t			fsm;
	क्रमागत bfa_msgq_cmdq_flags flags;

	u16			producer_index;
	u16			consumer_index;
	u16			depth; /* FW Q depth is 16 bits */
	काष्ठा bfa_dma addr;
	काष्ठा bfa_mbox_cmd dbell_mb;

	u16			token;
	पूर्णांक				offset;
	पूर्णांक				bytes_to_copy;
	काष्ठा bfa_mbox_cmd copy_mb;

	काष्ठा list_head		pending_q; /* pending command queue */

	काष्ठा bfa_msgq *msgq;
पूर्ण;

क्रमागत bfa_msgq_rspq_flags अणु
	BFA_MSGQ_RSPQ_F_DB_UPDATE	= 1,
पूर्ण;

प्रकार व्योम (*bfa_msgq_mcfunc_t)(व्योम *cbarg, काष्ठा bfi_msgq_mhdr *mhdr);

काष्ठा bfa_msgq_rspq अणु
	bfa_fsm_t			fsm;
	क्रमागत bfa_msgq_rspq_flags flags;

	u16			producer_index;
	u16			consumer_index;
	u16			depth; /* FW Q depth is 16 bits */
	काष्ठा bfa_dma addr;
	काष्ठा bfa_mbox_cmd dbell_mb;

	पूर्णांक				nmclass;
	काष्ठा अणु
		bfa_msgq_mcfunc_t	cbfn;
		व्योम			*cbarg;
	पूर्ण rsphdlr[BFI_MC_MAX];

	काष्ठा bfa_msgq *msgq;
पूर्ण;

काष्ठा bfa_msgq अणु
	काष्ठा bfa_msgq_cmdq cmdq;
	काष्ठा bfa_msgq_rspq rspq;

	काष्ठा bfa_wc			init_wc;
	काष्ठा bfa_mbox_cmd init_mb;

	काष्ठा bfa_ioc_notअगरy ioc_notअगरy;
	काष्ठा bfa_ioc *ioc;
पूर्ण;

u32 bfa_msgq_meminfo(व्योम);
व्योम bfa_msgq_memclaim(काष्ठा bfa_msgq *msgq, u8 *kva, u64 pa);
व्योम bfa_msgq_attach(काष्ठा bfa_msgq *msgq, काष्ठा bfa_ioc *ioc);
व्योम bfa_msgq_regisr(काष्ठा bfa_msgq *msgq, क्रमागत bfi_mclass mc,
		     bfa_msgq_mcfunc_t cbfn, व्योम *cbarg);
व्योम bfa_msgq_cmd_post(काष्ठा bfa_msgq *msgq,
		       काष्ठा bfa_msgq_cmd_entry *cmd);
व्योम bfa_msgq_rsp_copy(काष्ठा bfa_msgq *msgq, u8 *buf, माप_प्रकार buf_len);

#पूर्ण_अगर
