<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: RDMA Controller HW पूर्णांकerface (header)
 */

#अगर_अघोषित __BNXT_QPLIB_RCFW_H__
#घोषणा __BNXT_QPLIB_RCFW_H__

#घोषणा RCFW_CMDQ_TRIG_VAL		1
#घोषणा RCFW_COMM_PCI_BAR_REGION	0
#घोषणा RCFW_COMM_CONS_PCI_BAR_REGION	2
#घोषणा RCFW_COMM_BASE_OFFSET		0x600
#घोषणा RCFW_PF_COMM_PROD_OFFSET	0xc
#घोषणा RCFW_VF_COMM_PROD_OFFSET	0xc
#घोषणा RCFW_COMM_TRIG_OFFSET		0x100
#घोषणा RCFW_COMM_SIZE			0x104

#घोषणा RCFW_DBR_PCI_BAR_REGION		2
#घोषणा RCFW_DBR_BASE_PAGE_SHIFT	12

#घोषणा RCFW_CMD_PREP(req, CMD, cmd_flags)				\
	करो अणु								\
		स_रखो(&(req), 0, माप((req)));			\
		(req).opcode = CMDQ_BASE_OPCODE_##CMD;			\
		(req).cmd_size = माप((req));				\
		(req).flags = cpu_to_le16(cmd_flags);			\
	पूर्ण जबतक (0)

#घोषणा RCFW_CMD_WAIT_TIME_MS		20000 /* 20 Seconds समयout */

/* Cmdq contains a fix number of a 16-Byte slots */
काष्ठा bnxt_qplib_cmdqe अणु
	u8		data[16];
पूर्ण;

/* CMDQ elements */
#घोषणा BNXT_QPLIB_CMDQE_MAX_CNT_256	256
#घोषणा BNXT_QPLIB_CMDQE_MAX_CNT_8192	8192
#घोषणा BNXT_QPLIB_CMDQE_UNITS		माप(काष्ठा bnxt_qplib_cmdqe)
#घोषणा BNXT_QPLIB_CMDQE_BYTES(depth)	((depth) * BNXT_QPLIB_CMDQE_UNITS)

अटल अंतरभूत u32 bnxt_qplib_cmdqe_npages(u32 depth)
अणु
	u32 npages;

	npages = BNXT_QPLIB_CMDQE_BYTES(depth) / PAGE_SIZE;
	अगर (BNXT_QPLIB_CMDQE_BYTES(depth) % PAGE_SIZE)
		npages++;
	वापस npages;
पूर्ण

अटल अंतरभूत u32 bnxt_qplib_cmdqe_page_size(u32 depth)
अणु
	वापस (bnxt_qplib_cmdqe_npages(depth) * PAGE_SIZE);
पूर्ण

/* Set the cmd_size to a factor of CMDQE unit */
अटल अंतरभूत व्योम bnxt_qplib_set_cmd_slots(काष्ठा cmdq_base *req)
अणु
	req->cmd_size = (req->cmd_size + BNXT_QPLIB_CMDQE_UNITS - 1) /
			 BNXT_QPLIB_CMDQE_UNITS;
पूर्ण

#घोषणा RCFW_MAX_COOKIE_VALUE		0x7FFF
#घोषणा RCFW_CMD_IS_BLOCKING		0x8000
#घोषणा RCFW_BLOCKED_CMD_WAIT_COUNT	0x4E20

#घोषणा HWRM_VERSION_RCFW_CMDQ_DEPTH_CHECK 0x1000900020011ULL

/* Crsq buf is 1024-Byte */
काष्ठा bnxt_qplib_crsbe अणु
	u8			data[1024];
पूर्ण;

/* CREQ */
/* Allocate 1 per QP क्रम async error notअगरication क्रम now */
#घोषणा BNXT_QPLIB_CREQE_MAX_CNT	(64 * 1024)
#घोषणा BNXT_QPLIB_CREQE_UNITS		16	/* 16-Bytes per prod unit */
#घोषणा CREQ_CMP_VALID(hdr, raw_cons, cp_bit)			\
	(!!((hdr)->v & CREQ_BASE_V) ==				\
	   !((raw_cons) & (cp_bit)))
#घोषणा CREQ_ENTRY_POLL_BUDGET		0x100

/* HWQ */
प्रकार पूर्णांक (*aeq_handler_t)(काष्ठा bnxt_qplib_rcfw *, व्योम *, व्योम *);

काष्ठा bnxt_qplib_crsqe अणु
	काष्ठा creq_qp_event	*resp;
	u32			req_size;
पूर्ण;

काष्ठा bnxt_qplib_rcfw_sbuf अणु
	व्योम *sb;
	dma_addr_t dma_addr;
	u32 size;
पूर्ण;

काष्ठा bnxt_qplib_qp_node अणु
	u32 qp_id;              /* QP id */
	व्योम *qp_handle;        /* ptr to qplib_qp */
पूर्ण;

#घोषणा BNXT_QPLIB_OOS_COUNT_MASK 0xFFFFFFFF

#घोषणा FIRMWARE_INITIALIZED_FLAG	(0)
#घोषणा FIRMWARE_FIRST_FLAG		(31)
#घोषणा FIRMWARE_TIMED_OUT		(3)
#घोषणा ERR_DEVICE_DETACHED             (4)

काष्ठा bnxt_qplib_cmdq_mbox अणु
	काष्ठा bnxt_qplib_reg_desc	reg;
	व्योम __iomem			*prod;
	व्योम __iomem			*db;
पूर्ण;

काष्ठा bnxt_qplib_cmdq_ctx अणु
	काष्ठा bnxt_qplib_hwq		hwq;
	काष्ठा bnxt_qplib_cmdq_mbox	cmdq_mbox;
	रुको_queue_head_t		रुकोq;
	अचिन्हित दीर्घ			flags;
	अचिन्हित दीर्घ			*cmdq_biपंचांगap;
	u32				bmap_size;
	u32				seq_num;
पूर्ण;

काष्ठा bnxt_qplib_creq_db अणु
	काष्ठा bnxt_qplib_reg_desc	reg;
	काष्ठा bnxt_qplib_db_info	dbinfo;
पूर्ण;

काष्ठा bnxt_qplib_creq_stat अणु
	u64	creq_qp_event_processed;
	u64	creq_func_event_processed;
पूर्ण;

काष्ठा bnxt_qplib_creq_ctx अणु
	काष्ठा bnxt_qplib_hwq		hwq;
	काष्ठा bnxt_qplib_creq_db	creq_db;
	काष्ठा bnxt_qplib_creq_stat	stats;
	काष्ठा tasklet_काष्ठा		creq_tasklet;
	aeq_handler_t			aeq_handler;
	u16				ring_id;
	पूर्णांक				msix_vec;
	bool				requested; /*irq handler installed */
पूर्ण;

/* RCFW Communication Channels */
काष्ठा bnxt_qplib_rcfw अणु
	काष्ठा pci_dev		*pdev;
	काष्ठा bnxt_qplib_res	*res;
	काष्ठा bnxt_qplib_cmdq_ctx	cmdq;
	काष्ठा bnxt_qplib_creq_ctx	creq;
	काष्ठा bnxt_qplib_crsqe		*crsqe_tbl;
	पूर्णांक qp_tbl_size;
	काष्ठा bnxt_qplib_qp_node *qp_tbl;
	u64 oos_prev;
	u32 init_oos_stats;
	u32 cmdq_depth;
पूर्ण;

व्योम bnxt_qplib_मुक्त_rcfw_channel(काष्ठा bnxt_qplib_rcfw *rcfw);
पूर्णांक bnxt_qplib_alloc_rcfw_channel(काष्ठा bnxt_qplib_res *res,
				  काष्ठा bnxt_qplib_rcfw *rcfw,
				  काष्ठा bnxt_qplib_ctx *ctx,
				  पूर्णांक qp_tbl_sz);
व्योम bnxt_qplib_rcfw_stop_irq(काष्ठा bnxt_qplib_rcfw *rcfw, bool समाप्त);
व्योम bnxt_qplib_disable_rcfw_channel(काष्ठा bnxt_qplib_rcfw *rcfw);
पूर्णांक bnxt_qplib_rcfw_start_irq(काष्ठा bnxt_qplib_rcfw *rcfw, पूर्णांक msix_vector,
			      bool need_init);
पूर्णांक bnxt_qplib_enable_rcfw_channel(काष्ठा bnxt_qplib_rcfw *rcfw,
				   पूर्णांक msix_vector,
				   पूर्णांक cp_bar_reg_off, पूर्णांक virt_fn,
				   aeq_handler_t aeq_handler);

काष्ठा bnxt_qplib_rcfw_sbuf *bnxt_qplib_rcfw_alloc_sbuf(
				काष्ठा bnxt_qplib_rcfw *rcfw,
				u32 size);
व्योम bnxt_qplib_rcfw_मुक्त_sbuf(काष्ठा bnxt_qplib_rcfw *rcfw,
			       काष्ठा bnxt_qplib_rcfw_sbuf *sbuf);
पूर्णांक bnxt_qplib_rcfw_send_message(काष्ठा bnxt_qplib_rcfw *rcfw,
				 काष्ठा cmdq_base *req, काष्ठा creq_base *resp,
				 व्योम *sbuf, u8 is_block);

पूर्णांक bnxt_qplib_deinit_rcfw(काष्ठा bnxt_qplib_rcfw *rcfw);
पूर्णांक bnxt_qplib_init_rcfw(काष्ठा bnxt_qplib_rcfw *rcfw,
			 काष्ठा bnxt_qplib_ctx *ctx, पूर्णांक is_virtfn);
व्योम bnxt_qplib_mark_qp_error(व्योम *qp_handle);
अटल अंतरभूत u32 map_qp_id_to_tbl_indx(u32 qid, काष्ठा bnxt_qplib_rcfw *rcfw)
अणु
	/* Last index of the qp_tbl is क्रम QP1 ie. qp_tbl_size - 1*/
	वापस (qid == 1) ? rcfw->qp_tbl_size - 1 : qid % rcfw->qp_tbl_size - 2;
पूर्ण
#पूर्ण_अगर /* __BNXT_QPLIB_RCFW_H__ */
